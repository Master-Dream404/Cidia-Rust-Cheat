#include "BasePlayer.h"
#include "driver.h"
#include <m_includes/XorStr/XR.hpp>
#include <iostream>
#include "unity.h"
#include <immintrin.h>
#include "global.h"
struct Vec4
{
	float x, y, z, w;
};

struct Matrix34
{
	Vec4 vec0;
	Vec4 vec1;
	Vec4 vec2;
};

BasePlayer::BasePlayer(uint64_t address)
{
	this->Class = address;
	if (address == 0)
		return; // invalid

	BaseMovementOffset = driver::read<uint64_t>(Class + BaseMovementOffset);
	global::print(XR("BaseMovement: 0x%llX"), BaseMovementOffset);
	ActiveItemID = driver::read<uint64_t>(Class + ActiveItemIDOffset);
	global::print(XR("ActiveItemID: 0x%llX"), ActiveItemID);
	PlayerInventory = driver::read<uint64_t>(Class + PlayerInventoryOffset);
	global::print(XR("PlayerInventory: 0x%llX"), PlayerInventory);
	PlayerModel = driver::read<uint64_t>(Class + PlayerModel);
	global::print(XR("PlayerModel: 0x%llX"), PlayerModel);
	DisplayName = driver::read<uint64_t>(Class + DisplayName);
	global::print(XR("DisplayName: 0x%llX"), DisplayName);
	PlayerInput = driver::read<uint64_t>(Class + PlayerInputoffset);
	global::print(XR("PlayerInput: 0x%llX"), PlayerInput);
	/*
		TargetProcess.AddScatterReadRequest(handle, Class + BaseMovementOffset, reinterpret_cast<void*>(&BaseMovementOffset), sizeof(uint64_t));
		TargetProcess.AddScatterReadRequest(handle, Class + ActiveItemIDOffset, reinterpret_cast<void*>(&ActiveItemID), sizeof(uint32_t));
		TargetProcess.AddScatterReadRequest(handle, Class + PlayerInventory, reinterpret_cast<void*>(&PlayerInventory), sizeof(uint64_t));
		TargetProcess.AddScatterReadRequest(handle, Class + PlayerModel, reinterpret_cast<void*>(&PlayerModel), sizeof(uint64_t));
		TargetProcess.AddScatterReadRequest(handle, Class + DisplayName, reinterpret_cast<void*>(&DisplayName), sizeof(uint64_t));
	*/

}
void BasePlayer::InitializePlayerList()
{
	//GameAssembly.dll
	uint64_t staticclass = driver::read<uint64_t>(driver::GetGameAssembly() + StaticClass);
	std::cout << "staticclass: " << std::hex << staticclass << std::endl;
	uint64_t staticfield = driver::read<uint64_t>(staticclass + 0xb8); // access static fields
	std::cout << "staticfield: " << std::hex << staticfield << std::endl;
	uint64_t playerlist = driver::read<uint64_t>(staticfield + 0x20);
	std::cout << "playerlist: " << std::hex << playerlist << std::endl;
	VisiblePlayerList = driver::read<uint64_t>(playerlist + 0x28);
	std::cout << "VisiblePlayerList: " << VisiblePlayerList << std::endl;

}
int BasePlayer::GetPlayerListSize()
{
	return PlayerListSize;
}
void BasePlayer::CacheStage1()
{
	TransformPosition = driver::read<Vector3>(PlayerModel + Position);


	//driver::read_out( DisplayName + 0x14, &PlayerName );


	PlayerName = driver::read_unicode(DisplayName + 0x14, 32);

	//PlayerName = (void*)driver::read<const char*>(DisplayName + 0x14);

	//TargetProcess.AddScatterReadRequest(handle, DisplayName + 0x14, reinterpret_cast<void*>(&PlayerName), sizeof(PlayerName));

	NPC = driver::read<bool>(PlayerModel + IsNPCOffset);
	ContainerBelt = driver::read<uint64_t>(PlayerInventory + ContainerBelt);
	this->BaseMovementInstance = std::make_shared<BaseMovement>(BaseMovementOffset);

}
void BasePlayer::CachePlayers()
{

	if (VisiblePlayerList == 0)
	{
		PlayerListSize = 0;
		PlayerList.clear();
		return;
	}
	std::vector< std::shared_ptr<BasePlayer>> templayerlist;
	uint32_t size;
	size = driver::read<uint32_t>(VisiblePlayerList + 0x10);
	uint64_t buffer;
	buffer = driver::read<uint64_t>(VisiblePlayerList + 0x18);

	PlayerListSize = size;
	if (size == 0 || buffer == 0)
		return;
	std::vector<uint64_t> playerlist;
	playerlist.resize(size);
	for (int i = 0; i < size; i++)
	{
		playerlist[i] = driver::read<uint64_t>(buffer + (0x20 + (i * 8)));
		//TargetProcess.AddScatterReadRequest(handle, buffer + (0x20 + (i * 8)), reinterpret_cast<void*>(&playerlist[i]), sizeof(uint64_t));
	}

	for (int i = 0; i < size; i++)
	{
		if (playerlist[i] == NULL)
			continue;
		templayerlist.push_back(std::make_shared<BasePlayer>(playerlist[i]));

	}

	for (int i = 0; i < templayerlist.size(); i++)
	{
		std::shared_ptr<BasePlayer> player = templayerlist[i];
		player->CacheStage1();

	}

	PlayerList = templayerlist;
}
BasePlayer::~BasePlayer()
{
}
PlayerFlags BasePlayer::GetPlayerFlag()
{
	if (!IsPlayerValid())
		return PlayerFlags::Connected;
	PlayerFlags flag = driver::read<PlayerFlags>(Class + PlayerFlag);
	return flag;
}
void BasePlayer::WritePlayerFlag(PlayerFlags flag)
{
	if (!IsPlayerValid())
		return;

	driver::write(Class + PlayerFlag, flag);
}
uint32_t BasePlayer::GetActiveItemID()
{
	return ActiveItemID;
}
// call this in the local player loop to keep the value updated as it changes depending on the item
void BasePlayer::UpdateActiveItemID()
{
	ActiveItemID = driver::read<uint64_t>(Class + ActiveItemIDOffset);
}
std::shared_ptr<BaseMovement> BasePlayer::GetBaseMovement()
{
	return BaseMovementInstance;
}
void BasePlayer::SetupBeltContainerList()
{
	if (!IsPlayerValid())
		return;
	BeltContainerList.clear();
	uint64_t itemlist = driver::read<uint64_t>(ContainerBelt + ItemList); // yeah you need to reread this constantly, if you don't hell breaks loose. 
	uint64_t items = 0;
	items = driver::read<uint64_t>(itemlist + ItemListContents);

	//TargetProcess.AddScatterReadRequest(handle, itemlist + ItemListContents, reinterpret_cast<void*>(&items), sizeof(uint64_t));

	uint32_t itemsize = 0;

	itemsize = driver::read<uint32_t>(itemlist + ItemListSize);

	//TargetProcess.AddScatterReadRequest(handle, itemlist + ItemListSize, reinterpret_cast<void*>(&itemsize), sizeof(uint32_t));
	//TargetProcess.ExecuteScatterRead(handle);
	//TargetProcess.CloseScatterHandle(handle);
	BeltContainerList.resize(itemsize);

	std::vector<uint64_t> objectpointrs;
	objectpointrs.resize(itemsize);



	for (int i = 0; i < itemsize; i++)
	{
		objectpointrs[i] = driver::read<uint64_t>(items + 0x20 + (i * 0x8));
		//TargetProcess.AddScatterReadRequest(handle, items + 0x20 + (i * 0x8), reinterpret_cast<void*>(&objectpointrs[i]), sizeof(uint64_t));
	}
	for (int i = 0; i < itemsize; i++)
	{
		if (objectpointrs[i] == NULL)
			continue;
		BeltContainerList.push_back(std::make_shared<Item>(objectpointrs[i]));
	}
}
// it appears that we cant get the item class correctly, no idea where the issue lies. 
std::shared_ptr<Item> BasePlayer::GetActiveItem()
{
	if (ActiveItemID == 0)
	{
		return nullptr;
	}
	if (!IsPlayerValid())
	{
		return nullptr;
	}
	std::shared_ptr<Item> founditem = nullptr;
	for (std::shared_ptr<Item> item : BeltContainerList)
	{
		if (item == NULL)
			continue; // no wasting reads and writes on null pointers

		int activeweaponid = item->GetItemID();

		if (ActiveItemID == activeweaponid)
		{

			founditem = item;
			break;
		}

	}
	return founditem;

}

bool BasePlayer::IsPlayerValid()
{
	return Class != 0 && PlayerInventory != 0;
}

bool BasePlayer::IsSleeping()
{
	if (!IsPlayerValid())
		return false;

	return (ActiveFlag & (int)16) == (int)16;
}
bool BasePlayer::IsNPC()
{
	if (!IsPlayerValid())
		return false;
	return NPC;
}

bool BasePlayer::IsDead() {
	return false;
	//return driver::read<bool>(Class + wasDead);
}

std::string BasePlayer::GetNameS()
{
	if (!IsNPC())
		return PlayerName;
	else
		return XR("Scientist");
}
std::vector<std::shared_ptr<BasePlayer>> BasePlayer::GetPlayerList()
{
	return PlayerList;
}
uint64_t BasePlayer::GetClass()
{
	return Class;

}

void BasePlayer::UpdatePosition()
{
	TransformPosition = driver::read<Vector3>(PlayerModel + Position);
	//TargetProcess.AddScatterReadRequest(handle, PlayerModel + Position, reinterpret_cast<void*>(&TransformPosition), sizeof(Vector3));
}
void BasePlayer::UpdateDestroyed()
{
	Destroyed = driver::read<bool>(Class + DestroyedOffset);
	//TargetProcess.AddScatterReadRequest(handle, Class + DestroyedOffset, reinterpret_cast<void*>(&Destroyed), sizeof(bool));
}
Vector3 BasePlayer::GetPosition()
{
	return TransformPosition;
}
void BasePlayer::UpdateActiveFlag()
{
	ActiveFlag = driver::read<int>(Class + PlayerFlag);
	//TargetProcess.AddScatterReadRequest(handle, Class + PlayerFlag, reinterpret_cast<void*>(&ActiveFlag), sizeof(int));
}
void BasePlayer::WriteActiveFlag(int flag)
{
	if (!IsPlayerValid())
		return;

	driver::write(Class + PlayerFlag, flag);

	//if (!TargetProcess.Write<int>(Class + PlayerFlag, flag))
	//	printf("[BasePlayer] Failed to write flag\n");
}
int BasePlayer::GetActiveFlag()
{
	return ActiveFlag;
}

float BasePlayer::GetHealth() {
	return driver::read<float>(Class + 0x50);
}

void BasePlayer::SetbodyAngles(Vector2 angle) {

	// constexpr ::std::ptrdiff_t AimAngles = 0x1A0; // Quaternion
	driver::write(PlayerInput + bodyAngles, angle);
	//driver::write(PlayerInput + 0x8C, angle);
}

Vector2 BasePlayer::GetBodyAngles() {
	return driver::read<Vector2>(PlayerInput + bodyAngles);
}

Vector2 BasePlayer::GetRecoilAngles() {
	return driver::read<Vector2>(PlayerInput + 0x80);
}

Vector3 BasePlayer::GetBonePosition(int bone, uintptr_t transform) {

	uintptr_t model = driver::read<uintptr_t>(Class + 0xC8);
	if (model)
	{
		uintptr_t boneTransforms = driver::read<uintptr_t>(model + 0x50);//constexpr ::std::ptrdiff_t boneTransforms = 0x50; // Transform[]
		if (boneTransforms)
		{
			uintptr_t BoneValue = driver::read<uintptr_t>(boneTransforms + (0x20 + (bone * 0x8)));
			if (BoneValue)
			{
				uintptr_t bone = driver::read<uintptr_t>(BoneValue + 0x10);
				//Vector3 result = driver::read< Vector3 >(bones);
				return unity::get_position_injected(bone);
			}
			else
			{
				//std::cout << "No BoneValue" << std::endl;
			}
		}
		else
		{
			//std::cout << "no boneTransforms " << std::endl;
		}
	}
	else
	{
		//std::cout << "No model" << std::endl;
	}
}

Vector3 BasePlayer::GetCameraPosition() {
	return driver::read<Vector3>(driver::GetGameAssembly() + 0x3BFD2E0);
}

int BasePlayer::GetMaxProjectileID() {
	return driver::read<int>(Class + maxProjectileID);
}

Vector3 BasePlayer::GetVelocity() {
	return driver::read<Vector3>(PlayerModel + 0x1D4);//PlayerModel -> velocity = 0x1D4; // Vector3
}

double ToRad(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}
Vector4 ToQuat(Vector3 Euler) {

	double heading = ToRad(Euler.x);
	double attitude = ToRad(Euler.y);
	double bank = ToRad(Euler.z);

	double c1 = cos(heading / 2);
	double s1 = sin(heading / 2);
	double c2 = cos(attitude / 2);
	double s2 = sin(attitude / 2);
	double c3 = cos(bank / 2);
	double s3 = sin(bank / 2);
	double c1c2 = c1 * c2;
	double s1s2 = s1 * s2;
	Vector4 Quat;
	Quat.w = c1c2 * c3 - s1s2 * s3;
	Quat.x = c1c2 * s3 + s1s2 * c3;
	Quat.y = s1 * c2 * c3 + c1 * s2 * s3;
	Quat.z = c1 * s2 * c3 - s1 * c2 * s3;
	Vector4 Quat2;
	Quat2 = { Quat.y, Quat.z, (Quat.x * -1), Quat.w };
	return Quat2;
}

void BasePlayer::SetPlayerEyesView(Vector4 angle) {
	uintptr_t PlayerEyes = driver::read<uintptr_t>(Class + eyes);
	//Vector4 QuatAngles = ToQuat({ angle.x, angle.y, 0.0f });

	//Vector4 quaternionangle = Vector4::QuaternionLookRotation(angle, { 0,1,0 });

	driver::write<Vector4>(PlayerEyes + 0x68, angle);
	driver::write<Vector4>(PlayerEyes + 0x4C, angle);
	//private Quaternion <bodyRotation>k__BackingField; // 0x4C 
}