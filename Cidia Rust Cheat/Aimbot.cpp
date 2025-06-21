#include "Aimbot.h"
#include "imgui/imgui.h"
#include <m_includes/XorStr/XR.hpp>
#include "CheatFunction.h"
#include <memory>
#include "rust.h"
#include <Windows.h>
#include <d3dx9math.h>
#include "XRINT.h"
#include "unity.h"
#include "Hotkey.h"
namespace config
{
	ImVec2 WindowSize = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	bool enable = false;
	HotKeys* HotKey = new HotKeys();
	bool eoka = false;
	bool fastbow = false;
	bool compoundbow = false;
	bool force_automatic = false;
	bool force_semiautomatic = false;
	bool target_npc = false;
	bool fov = false;
	bool filled_fov = false;
	float fov_value = 0;
	bool slientaim = false;
	bool recoil = false;
	int recoil_value = 0;
	bool spread = false;
	int spread_value = 0;
	int Smoothness = 0;
	bool aimline = false;
	int MaxDistance = 300;
	int aimbot_bone = 0;
	const char* aimbot_bones_list[]{ "Head", "Chest" };
	ImColor aimline_color = ImColor(0, 166, 255);
	float aimline_f[4] = { 255.f, 255.f, 255.f, 255.f };
	bool nosway = false;
	bool noshotgunspread = false;
	bool jumpshoot = false;
	bool targetf = false;
	bool hitboxoverride = false;
	bool thickbullet = false;
	int thicknullet = 1;
}

namespace function
{
	ImVec2 WindowSize = ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	float get2DDistance(D3DXVECTOR2 a, D3DXVECTOR2 b) {
		return sqrt(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
	}

	/*
	bool inFOV2(double x, double y, float fov)
	{
		double centerX = WindowSize.x / 2.0;
		double centerY = WindowSize.y / 2.0;
		double distance = get2DDistance(D3DXVECTOR2(centerX, centerY), D3DXVECTOR2(x, y));

		return distance < (fov * 10);
	}
	*/


	bool inFOV(double x, double y, float fov)
	{
		double centerX = WindowSize.x / 2.0;
		double centerY = WindowSize.y / 2.0;
		double distance = get2DDistance(D3DXVECTOR2(centerX, centerY), D3DXVECTOR2(x, y));

		return distance < (fov * 10);
	}

	D3DXVECTOR2 calcmyangles(D3DXVECTOR3* LocalPos, D3DXVECTOR3* EnemyPos) {
		D3DXVECTOR2 toWrite;
		D3DXVECTOR3 relative;
		D3DXVec3Subtract(&relative, LocalPos, EnemyPos);
		float magnitude = D3DXVec3Length(&relative);
		double pitch = asin(relative[1] / magnitude);
		double yaw = -atan2(relative[0], -relative[2]);

		yaw = D3DXToDegree(yaw);
		pitch = D3DXToDegree(pitch);

		toWrite.x = pitch;
		toWrite.y = yaw;
		return toWrite;
	}

	float GetBulletDrop(float distance, float projectile_speed, float projectile_gravity)
	{
		if (distance < xf(0.001f))
			return -1;

		float m_gravity = xf(9.81f) * projectile_gravity;
		float m_time = distance / std::fabs(projectile_speed);

		return static_cast<float>(xf(0.5f) * m_gravity * m_time * m_time);
	}

	float to_degree(float radian)
	{
		return radian * 180.f / 3.141592f;
	}

	Vector2 CalcAngle(Vector3 LocalPos, Vector3 EnemyPos)
	{
		Vector3 dir = LocalPos - EnemyPos;

		float Yaw = to_degree(-atan2(dir.x, -dir.z));
		float Pitch = to_degree(asin(dir.y / dir.Length()));

		return { Pitch, Yaw };// 공식이 YAW ROLL PITCH 순임
	}

	void Normalize(float& Yaw, float& Pitch) { // OnlyDegree // 위 일때 pitch 은 음수값 아래일때 pitch + 값 yaw 은 -360~360
		if (Pitch < -89)
			Pitch = -89;

		else if (Pitch > 89)
			Pitch = 89;

		if (Yaw < -360)
			Yaw += 360;

		else if (Yaw > 360)
			Yaw -= 360;
	}
	void SmoothAim(Vector2& Angle, float smooth) {
		Angle.x /= 2;
		Angle.y /= smooth;
	}

	inline float Length(Vector3 v) {
		return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	static bool Normalizex2(float& Yaw, float& Pitch) {
		//Vector2 CurrentViewAngles = LocalPlayer.BasePlayer->GetVA();
		if (Pitch < -89)
			Pitch = -89;

		else if (Pitch > 89)
			Pitch = 89;

		if (Yaw < -360)
			Yaw += 360;

		else if (Yaw > 360)
			Yaw -= 360;

		return true;
	}

	static Vector3 CalcAnglex2(Vector3 LocalPos, Vector3 EnemyPos)
	{
		/*
			Vector2 smoothedAngles;
											smoothedAngles.x = LocalPlayerBonePos.x + config::Smoothness * (finalTargetAngles.x - LocalPlayerBonePos.x);
											smoothedAngles.y = LocalPlayerBonePos.y + config::Smoothness * (finalTargetAngles.y - targetAngles.y);
		*/
		Vector3 dir;/* = Vector3(LocalPos.x - EnemyPos.x, LocalPos.y - EnemyPos.y, LocalPos.z - EnemyPos.z);*/

		dir.x = LocalPos.x - EnemyPos.x;
		dir.y = LocalPos.y - EnemyPos.y;
		dir.z = LocalPos.z - EnemyPos.z;

		float Pitch = to_degree(asin(dir.y / Length(dir)));
		float Yaw = to_degree(-atan2(dir.x, -dir.z));

		//Normalize(Yaw, Pitch);

		Vector3 Return;
		Return.x = Pitch;
		Return.y = Yaw;

		//return { Pitch, Yaw };
		return Return;
	}

	static void smooth_angle(Vector2& angles, Vector2& localViewAngles)
	{
		Vector2 delta = Vector2(angles.x - localViewAngles.x, angles.y - localViewAngles.y);
		Normalizex2(delta.x, delta.y);

		float smoothing_value = ((config::Smoothness / 3) / 100.f);
		float smooth = powf(0.81f + smoothing_value, 0.4f);

		smooth = min(0.98f, smooth);

		Vector2 toChange = Vector2();

		float coeff = (1.0f - smooth) / delta.length() * 4.f;

		// fast end
		coeff = powf(coeff, 2.f) * 80.f / config::Smoothness;

		coeff = min(1.f, coeff);

		delta.x *= coeff;
		delta.y *= coeff;

		toChange = delta;

		angles = Vector2(localViewAngles.x, localViewAngles.y) + toChange;
	}

}

namespace Aimbot
{
	void Render() {
		ImGui::BeginChild(XR("AimbotCgild1"), ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y));
		ImGui::Checkbox(XR("Aimbot"), &config::enable);
		if (config::enable)
		{
			ImGui::SameLine();
			GUI::HotKey(config::HotKey, ImVec2(23, 23));
		}
		ImGui::SliderInt(XR("Smoothness"), &config::Smoothness, 0, 100);
		ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x / 2);
		ImGui::Combo(XR("Aim Bone"), &config::aimbot_bone, config::aimbot_bones_list, IM_ARRAYSIZE(config::aimbot_bones_list));
		ImGui::PopItemWidth();
		ImGui::Checkbox(XR("Slient Aim"), &config::slientaim);
		ImGui::Checkbox(XR("Target NPC"), &config::target_npc);
		ImGui::Checkbox(XR("Target friends"), &config::targetf);
		ImGui::Checkbox(XR("Fov"), &config::fov);
		if (config::fov)
		{
			ImGui::SameLine();
			ImGui::Checkbox(XR("Filled Fov"), &config::filled_fov);
			ImGui::SliderFloat(XR("FOV"), &config::fov_value, 0, 100);
		}

		ImGui::Checkbox(XR("Aim Line"), &config::aimline);
		ImGui::SameLine();
		float col[4] = { config::aimline_color.Value.x, config::aimline_color.Value.y, config::aimline_color.Value.z, config::aimline_color.Value.w };
		if (ImGui::ColorEdit4(XR("Aim Line"), col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar)) {
			config::aimline_color = ImColor(col[0], col[1], col[2], col[3]);
		}
/*
		ImGui::SameLine();
		ImGui::ColorEdit4(((XR("##Aimline"))), config::aimline_f, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		config::aimline_color.Value.x = config::aimline_f[0];
		config::aimline_color.Value.y = config::aimline_f[1];
		config::aimline_color.Value.z = config::aimline_f[2];
		config::aimline_color.Value.w = config::aimline_f[3];
*/

		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild(XR("AimbotChild2"), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false, ImGuiWindowFlags_NoScrollbar);
		//ImGui::SliderInt(XR("MaxDistance"), &config::MaxDistance, 1, 300);
		ImGui::Checkbox(XR("No Recoil"), &config::recoil);
		if (config::recoil)
		{
			ImGui::SliderInt(XR("##recoil"), &config::recoil_value, 0, 100);
		}
		ImGui::Checkbox(XR("No Spread"), &config::spread);
		if (config::spread)
		{
			ImGui::SliderInt(XR("##spread"), &config::spread_value, 0, 100);
		}

/*
* ImGui::Checkbox(XR("Override Hitbox"), &config::hitboxoverride);
		ImGui::Checkbox(XR("Thick Bullet"), &config::thickbullet);

		if (config::thickbullet)
		{
			ImGui::SliderInt(XR("##ThickBullet"), &config::thicknullet, 1, 100);
		}
*/
		ImGui::Checkbox(XR("No sway"), &config::nosway);
		ImGui::SameLine();
		//ImGui::Checkbox(XR("No shotgun spread"), &config::noshotgunspread);
		//ImGui::Checkbox(XR("Shoot while midair"), &config::jumpshoot);

		ImGui::Checkbox(XR("Insta eoka"), &config::eoka);
		ImGui::Checkbox(XR("Insta compound bow"), &config::compoundbow);
		ImGui::SameLine();
		ImGui::Checkbox(XR("Fast bow"), &config::fastbow);
		ImGui::Checkbox(XR("Force automatic"), &config::force_automatic);
		ImGui::Checkbox(XR("Force semi automatic"), &config::force_semiautomatic);

/*bool fastbow = false;
		bool compoundbow = false;
		ImGui::SliderFloat(XR("X"), &config::test_x, -1000, 1000);
		ImGui::SliderFloat(XR("Y"), &config::test_y, -1000, 1000);
*/

		ImGui::EndChild();
	}

	std::shared_ptr<BasePlayer> GetClosePlayer() {
		using namespace rust;
		using namespace config;
		std::shared_ptr<BasePlayer> entity = 0;
		float closestdist = FLT_MAX;
		float Distance2;
		for (std::shared_ptr<BasePlayer> player : BaseLocalPlayer->GetPlayerList())
		{

			if (!config::targetf)
			{
				if (global::PlayerClasses.find(player->GetNameS()) != global::PlayerClasses.end())
				{
					if (global::PlayerClasses[player->GetNameS()] == global::PlayerClass::friends)
						continue;
				}
			}

			if (!player->IsPlayerValid())
				continue;
			if (player->GetClass() == BaseLocalPlayer->GetClass())
				continue;

			player->UpdateDestroyed();
			player->UpdateActiveFlag();

			if (player->IsSleeping())
				continue;

			if (player->IsDead())
				continue;

			if (!target_npc)
			{
				if (player->IsNPC())
					continue;
			}

			player->UpdateDestroyed();
			player->UpdateActiveFlag();

			BaseLocalPlayer->UpdatePosition();
			player->UpdatePosition();
			int distance = (int)Vector3::Distance(player->GetPosition(), BaseLocalPlayer->GetPosition());

			if (distance <= MaxDistance) {


				Vector2 line_pos;
				if (WorldToScreen2(player->GetBonePosition(BoneList::neck), line_pos, false))
				{
					if (function::inFOV(line_pos.x, line_pos.y, config::fov_value))
					{
						BaseLocalPlayer->UpdatePosition();
						player->UpdatePosition();
						Distance2 = Vector3::Distance(player->GetPosition(), BaseLocalPlayer->GetPosition());
						if (Distance2 < closestdist) {
							{
								closestdist = Distance2;
								entity = player;
							}
						}
					}
				}


			}
		}

		return entity;
	}

	void Thread() {
		using namespace config;

		if (recoil || spread || eoka || force_automatic || force_semiautomatic || fastbow || compoundbow || nosway)
		{
			rust::BaseLocalPlayer->SetupBeltContainerList();
			rust::BaseLocalPlayer->UpdateActiveItemID();
			rust::BaseLocalPlayer->UpdateActiveFlag();
			std::shared_ptr <Item> helditem = rust::BaseLocalPlayer->GetActiveItem();
			if (helditem != nullptr)
			{
				std::string weapon_name;
				if (helditem->IsWeapon(helditem->GetItemName(), &weapon_name))
				{
					std::shared_ptr <BaseProjectile> weapon = helditem->GetBaseProjectile();
					if (weapon != 0)
					{
						if (weapon->IsValidWeapon() || helditem->GetItemName() == XR("pistol.eoka"))
						{
							if (config::thickbullet)
							{
								weapon->SetBulletThick(config::thicknullet);
							}

							if (nosway)
							{
								weapon->NoSway(helditem->GetItemID());
							}
							if (force_automatic)
							{
								weapon->SetAutomatic(helditem->GetItemID());
							}
							if (force_semiautomatic)
							{
								weapon->SetSimiAutomatic(helditem->GetItemID());
							}
							if (fastbow)
							{
								if (helditem->GetItemName() == XR("bow.hunting"))
								{
									weapon->FastBow();
								}
							}
							if (compoundbow)
							{
								if (helditem->GetItemName() == XR("bow.compound"))
								{
									weapon->InstentCompoundBow();
								}
							}
							if (eoka)
							{
								if (helditem->GetItemName() == XR("pistol.eoka"))
								{
									weapon->InstentEoka();
								}
							}
							if (recoil)
							{
								weapon->WriteRecoilPitch(helditem->GetItemID(), recoil_value);
								weapon->WriteRecoilYaw(helditem->GetItemID(), recoil_value);
							}
							if (spread)
							{
								weapon->WriteSpread(helditem->GetItemID(), spread_value);
							}
						}
					}
				}
			}
		}
		//rust::BaseLocalPlayer->SetbodyAngles(Vector2(config::test_x, config::test_y));

		if (enable)
		{
			BoneList aimbone = BoneList::head;
			if (config::aimbot_bone == 0)
			{
				aimbone == BoneList::head;
			}
			if (config::aimbot_bone == 1)
			{
				aimbone == BoneList::spine2;
			}

			rust::BaseLocalPlayer->InitializePlayerList();
			rust::BaseLocalPlayer->CachePlayers();
			std::shared_ptr<BasePlayer> entity = GetClosePlayer();

			if (entity != 0)
			{
				entity->UpdatePosition();

				Vector2 bonePos;
				if (rust::WorldToScreen2(entity->GetBonePosition(aimbone), bonePos, false))
				{
					if (aimline)
					{
						if (function::inFOV(bonePos.x, bonePos.y, config::fov_value))
						{
							auto draw = ImGui::GetBackgroundDrawList();
							draw->AddLine(ImVec2(WindowSize.x / 2, WindowSize.y / 2), ImVec2(bonePos.x, bonePos.y), ImColor(config::aimline_color));
						}
					}
					entity->UpdatePosition();
					Vector2 a;
					rust::WorldToScreen2(entity->GetPosition(), a, false);
					if (function::inFOV(bonePos.x, bonePos.y, config::fov_value))
					{
						if (config::HotKey->key != 0)
						{
							if (GetAsyncKeyState(config::HotKey->key))
							{
								rust::BaseLocalPlayer->SetupBeltContainerList();
								rust::BaseLocalPlayer->UpdateActiveItemID();
								rust::BaseLocalPlayer->UpdateActiveFlag();

								std::shared_ptr<Item> helditem = rust::BaseLocalPlayer->GetActiveItem();
								if (helditem != nullptr)
								{
									std::string item;
									if (helditem->IsWeapon(helditem->GetItemName(), &item))
									{
										std::shared_ptr<BaseProjectile> weapon = helditem->GetBaseProjectile();
										if (weapon != nullptr && weapon->IsValidWeapon())
										{

											if (config::slientaim)
											{
												//LocalPlayerBonePos = rust::BaseLocalPlayer->GetBonePosition(BoneList::head);
												Vector3 aimDirection = entity->GetBonePosition(BoneList::head) - rust::BaseLocalPlayer->GetBonePosition(BoneList::head);
												aimDirection.normalize();
/*
												global::print(XR("X: %f"), aimDirection.x);
												global::print(XR("y: %f"), aimDirection.y);
												global::print(XR("z: %f"), aimDirection.z);
*/

/*
												if (hitboxoverride)
												{

													//Vector3 finalTargetAngles = function::CalcAnglex2(rust::BaseLocalPlayer->GetBonePosition(BoneList::head), entity->GetBonePosition(BoneList::head));
													//weapon->GetProjectile()->MoveProjectileShoot(finalTargetAngles);

													weapon->OverrideHitBox(finalTargetAngles);
													weapon->SetMaxDistance(finalTargetAngles//);

												}
*/

												Vector4 quaternionAngle = Vector4::QuaternionLookRotation(aimDirection, { 0, 1, 0 });
												rust::BaseLocalPlayer->SetPlayerEyesView(quaternionAngle);
												//std::cout << "Quaternion Angle: " << quaternionAngle.x << ", " << quaternionAngle.y << ", " << quaternionAngle.z << ", " << quaternionAngle.w << std::endl;
											}

											if (!config::slientaim)
											{

												Vector3 TargetBonePos = entity->GetBonePosition(aimbone /*BoneList::head*/);
												Vector3 LocalPlayerBonePos = rust::BaseLocalPlayer->GetBonePosition(BoneList::head);

												Vector3 targetAngles = function::CalcAnglex2(LocalPlayerBonePos, TargetBonePos);

												rust::BaseLocalPlayer->UpdatePosition();

												float distance = Vector3::Distance(TargetBonePos, LocalPlayerBonePos);
												float bulletSpeed = weapon->GetBulletSpeed(helditem->GetItemName().c_str(), weapon->GetBulletName().c_str()) * weapon->GetProjectileVelocityScale();
												float bulletGravity = weapon->GetBulletGravity(weapon->GetBulletName().c_str());
												float bulletTime = distance / bulletSpeed;
												float bulletDrag = weapon->GetBulletDrag(weapon->GetBulletName().c_str());

												float bulletDrop = function::GetBulletDrop(distance, bulletSpeed, bulletGravity);

												const float timeStep = 0.015625f;
												float yTravelled = 0.0f;
												float ySpeed = 0.0f;
												float bulletTimeElapsed = 0.0f;
												float distanceToTravel = 0.0f;

												for (; distanceToTravel < distance;)
												{
													float speedModifier = 1.0f - timeStep * bulletDrag;
													bulletSpeed *= speedModifier;

													if (bulletSpeed <= 0.0f || bulletSpeed >= 10000.0f || yTravelled >= 10000.0f || yTravelled < 0.0f)
														break;

													if (bulletTimeElapsed > 8.0f)
														break;

													ySpeed += (9.81f * bulletGravity) * timeStep;
													ySpeed *= speedModifier;

													distanceToTravel += bulletSpeed * timeStep;
													yTravelled += ySpeed * timeStep;
													bulletTimeElapsed += timeStep;
												}

												Vector3 velocity = entity->GetVelocity();
												if (velocity.y > 0.0f)
													velocity.y /= 3.25f;

												//TargetBonePos += (velocity * bulletTimeElapsed);

												TargetBonePos = (TargetBonePos + (velocity * bulletTimeElapsed));

												Vector3 finalTargetAngles = function::CalcAnglex2(LocalPlayerBonePos, TargetBonePos);


												Vector2 Angles;
												Angles.x = targetAngles.x;// +config::Smoothness * (finalTargetAngles.x - LocalPlayerBonePos.x);
												Angles.y = targetAngles.y;// +config::Smoothness * (finalTargetAngles.y - targetAngles.y);

												if (config::Smoothness >= 1)
												{
													Vector2 currentAngles = rust::BaseLocalPlayer->GetBodyAngles();
													function::smooth_angle(Angles, currentAngles);
												}

												/*
												Vector2 smoothedAngles;
												smoothedAngles.x = LocalPlayerBonePos.x + config::Smoothness * (finalTargetAngles.x - LocalPlayerBonePos.x);
												smoothedAngles.y = LocalPlayerBonePos.y + config::Smoothness * (finalTargetAngles.y - targetAngles.y);

												*/
												rust::BaseLocalPlayer->SetbodyAngles(Angles);
											}
										}
									}
								}
							}
						}
					}

				}

			}

			if (fov)
			{
				if (filled_fov)
				{
					ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(WindowSize.x / 2, WindowSize.y / 2), fov_value * 10, ImColor(0, 0, 0, 90), 100.0f);
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(WindowSize.x / 2, WindowSize.y / 2), fov_value * 10, ImColor(255, 255, 255, 255), 100.0f);
				}
				else
				{
					ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(WindowSize.x / 2, WindowSize.y / 2), fov_value * 10, ImColor(255, 255, 255, 255), 100.0f);
				}
			}
		}

	}
}
