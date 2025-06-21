#pragma once
#include "BaseMovement.h"
#include "Item.h"
#include <cstdint>
#include "Vectors.h"
#include <vector>
#include <memory>
#include <string>

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};

enum class PlayerFlags : uint32_t
{
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Incapacitated = 524288,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
	VoiceRangeBoost = 8388608,
	ModifyClan = 16777216,
	LoadingAfterTransfer = 33554432,
	NoRespawnZone = 67108864,
	IsInTutorial = 134217728
};
static enum StanceFlags : int
{
	Ducked = 1,
	Jumped = 2,
	OnGround = 4,
	Sleeper = 8,
	Sprinting = 16,
	OnLadder = 32,
	Flying = 64,
	Aim = 128,
	Prone = 256,
	Mounted = 512,
	Relax = 1024,
	OnPhone = 2048,
	Crawling = 4096,
	Loading = 8192,
	HeadLook = 16384,
	HasParachute = 32768
};
class BasePlayer
{
	/*

  "Name": "BasePlayer_TypeInfo",
  "Signature": "BasePlayer_c*"
*/
	uint64_t StaticClass = 0x554FC98;
	uint64_t camera_instance = 0;
	uint64_t PlayerInputoffset = 0xA50; //public PlayerInput %0ab8801a8b82b131d9ea1633b99cf0d49fadb319;
	uint64_t PlayerInput = 0;
	uint64_t Class = 0;
	uint64_t PlayerFlag = 0xB40; // 	public global::BasePlayer.PlayerFlags playerFlags; 
	uint64_t BaseMovementOffset = 0x9C0; // public BaseMovement movement; 	public BaseMovement %6d0b56ccdbff2af1ffe5daf9da208a4e85ccce71;
	uint64_t PlayerInventory = 0; // public global::PlayerInventory inventory;
	uint64_t PlayerInventoryOffset = 0x8F0; // public global::PlayerInventory inventory; //private BasePlayer<PlayerInventory>.%48368ea274e73962c2a6e3ce6481023676a0f549 %e0e264bfe80be7900bdf96e00c291aa6c29a7ae6;
	uint64_t ActiveItemIDOffset = 0x9E8; // private ItemId clActiveItem; private private BasePlayer<ItemId>.%f13d4bd62fedff18345d3a672287f0e575780783 %b774379123226f056d2f1233532a4523b92c079f;
	uint64_t PlayerModel = 0x958; //public PlayerModel playerModel; public PlayerModel %18d88518913392cf92e3d389103c729c14f610b1;
	uint64_t Position = 0x1DC;// PlayerModel -> internal Vector3 position; 	internal Vector3 %35734c3555db465c445ce0cb658900e60351484b;
	uint64_t visible = 0x23C;//PlayerModel-> internal bool visible; 	internal bool %06871fc864311dd2c236e0fda928e00ec1f01c56;
	Vector3 TransformPosition = Vector3::Zero();
	uint64_t DisplayName = 0xAE8; // protected string _displayName; protected string %ab548960eb0af59377b862675956cdfa39f62474;
	uint64_t VisiblePlayerList = 0x38; // 	private static ListDictionary<ulong, global::BasePlayer> visiblePlayerList; private static BasePlayer<ListDictionary<ulong, BasePlayer>>.%48368ea274e73962c2a6e3ce6481023676a0f549 %7588f86ed54fc2f3294b913f86edea2f4024fe53;
	uint64_t DestroyedOffset = 0x40; // basenetworkable -> private bool <IsDestroyed>k__BackingField;
	uint32_t IsNPCOffset = 0x2E2; // 	private bool <IsNpc>k__BackingField;
	uint64_t wasDead = 0x8AB; // bool 		private bool %5dac88f7415585eec9ec86bf9637c531e10659fa;
	uint64_t eyes = 0xAB8;// PlayerEyes // 	private %f4fcdf85d1b93204bf773ccba340d1274c47bdaf<PlayerEyes> %1694340cec9e8094030cfe6e2db41643e930d2f5;

	uint64_t bodyAngles = 0x5C; //PlayerInput -> bodyAngles 0x44 	private Vector3 %ff5a56dff01728bb764f403f6b0b4329500332db;
	uint64_t bodyAnglesOverride = 0x5C; //PlayerInput -> bodyAnglesOverride 0x50 private Vector3 %d43c28028361f3bc54011c963bcddbe9ba1c05d9;
	std::shared_ptr<BaseMovement> BaseMovementInstance;
	uint64_t maxProjectileID = 0x89C;

	uint32_t ActiveItemID = 0;

	// these are offsets outside of baseplayer. I just don't want the hassle of 1000 classes. The Class is before the "->"
	uint64_t ContainerBelt = 0x50; // PlayerInventory -> public global::ItemContainer containerBelt; 	public %641ec1d8e843b5f0532c59206589090305a43b95 %653da87b9b2dae4692e696899abcf273d1fae639;
	uint64_t ItemList = 0x38; // ItemContainer -> 	public List<global::Item> itemList; 	public List<%eead1f60087cbc2f30ea45003245e96b04ad0491> %8f6257c5a1c0a447196835fc9efc78bbac40e343;
	uint64_t ItemListContents = 0x10; // ItemList + 0x10 is the actual contents of the c# list
	uint64_t ItemListSize = 0x18; // ItemList + 0x18 is the size of a c# list
	std::vector<std::shared_ptr<BasePlayer>> PlayerList;
	std::vector<std::shared_ptr<Item>> BeltContainerList;
	int PlayerListSize = 0;
	//const char* PlayerName;
	std::string PlayerName;

	bool Destroyed = false;
	bool NPC = false;
	int ActiveFlag = 0;

public:
	BasePlayer(uint64_t address);
	~BasePlayer();
	uint64_t GetClass();
	PlayerFlags GetPlayerFlag();
	void WritePlayerFlag(PlayerFlags flag);
	std::shared_ptr<BaseMovement> GetBaseMovement();

	bool IsDead();
	void UpdateActiveItemID();
	uint32_t GetActiveItemID();
	std::shared_ptr<Item> GetActiveItem();
	bool IsPlayerValid();
	void SetupBeltContainerList();
	void InitializePlayerList();
	void CachePlayers();
	int GetPlayerListSize();
	void CacheStage1();
	bool IsSleeping();
	bool IsNPC();
	//std::wstring GetName();
	std::string GetNameS();
	std::vector<std::shared_ptr<BasePlayer>> GetPlayerList();
	void UpdatePosition();
	void UpdateDestroyed();
	Vector3 GetPosition();
	void UpdateActiveFlag();
	int GetActiveFlag();
	void WriteActiveFlag(int pose);
	float GetHealth();
	void SetbodyAngles(Vector2 angle);
	Vector2 GetBodyAngles();
	Vector3 GetBonePosition(int bone, uintptr_t transform = 0);
	Vector2 GetRecoilAngles();
	Vector3 GetCameraPosition();
	Vector3 GetVelocity();
	int GetMaxProjectileID();
	void SetPlayerEyesView(Vector4 angle);
};
