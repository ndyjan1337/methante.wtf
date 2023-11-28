#pragma once
#pragma warning (disable: 26495)

#include <cstdint>
#include <string>

#include "Vectors.h"
#include "MemMan.hpp"

#include "../json/jsonOps.hpp"

struct C_UTL_VECTOR
{
	DWORD_PTR count = 0;
	DWORD_PTR data = 0;
};


inline MemoryManagement MemMan;

namespace clientDLL {
	inline nlohmann::json clientDLLOffsets = (jsonn::clientDLLFile);

	inline nlohmann::json C_BaseEntity_ = clientDLLOffsets["C_BaseEntity"]["data"];
	inline nlohmann::json CCSPlayerController_ = clientDLLOffsets["CCSPlayerController"]["data"];
	inline nlohmann::json C_BasePlayerPawn_ = clientDLLOffsets["C_BasePlayerPawn"]["data"];
	inline nlohmann::json C_CSPlayerPawn_ = clientDLLOffsets["C_CSPlayerPawn"]["data"];
	inline nlohmann::json C_CSPlayerPawnBase_ = clientDLLOffsets["C_CSPlayerPawnBase"]["data"];
	inline nlohmann::json CBaseAnimGraph_ = clientDLLOffsets["CBaseAnimGraph"]["data"];
	inline nlohmann::json C_EconItemView_ = clientDLLOffsets["C_EconItemView"]["data"];
	inline nlohmann::json C_AttributeContainer_ = clientDLLOffsets["C_AttributeContainer"]["data"];
	inline nlohmann::json C_EconEntity_ = clientDLLOffsets["C_EconEntity"]["data"];
	inline nlohmann::json CSkeletonInstance_ = clientDLLOffsets["CSkeletonInstance"]["data"];
	inline nlohmann::json CGameSceneNode_ = clientDLLOffsets["CGameSceneNode"]["data"];
	inline nlohmann::json EntitySpottedState_t_ = clientDLLOffsets["EntitySpottedState_t"]["data"];
	inline nlohmann::json C_CSGameRules_= clientDLLOffsets["C_CSGameRules"]["data"];
};


namespace offsets {
	inline nlohmann::json clientDLL = (jsonn::offsetFile)["client_dll"]["data"];
};



class CCSPlayerController{
public:
	uintptr_t entityList;
	int id;

	CCSPlayerController(uintptr_t base) {
		entityList = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwEntityList"]["value"]);
	}

	uintptr_t listEntry;
	uintptr_t getListEntry();

	uintptr_t value;
	uintptr_t getController();

	int pawnHealth;
	int getPawnHealth();

	uintptr_t pawnTeam;
	uintptr_t getPawnTeam();

	uintptr_t pawnNameAddress;
	std::string pawnName;
	std::string getPawnName();

	// C_CSPlayerPawn
	std::uint32_t C_CSPlayerPawn_;
	std::uint32_t getC_CSPlayerPawn();
};


class C_CSPlayerPawn {
public:
	std::uint32_t value;
	uintptr_t entityList;

	C_CSPlayerPawn(uintptr_t base) {
		entityList = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwEntityList"]["value"]);
	}

	uintptr_t listEntry;
	uintptr_t getListEntry();

	uintptr_t playerPawn;
	uintptr_t getPlayerPawn();
	uintptr_t getPlayerPawnByCrossHairID(int crossHairEntity);

	Vector3 origin;
	Vector3 getOrigin();

	Vector3 cameraPos;
	Vector3 getCameraPos();

	Vector3 viewAngles;
	Vector3 getViewAngles();

	Vector3 position;
	Vector3 getPosition();

	int pawnHealth;
	int getPawnHealth();

	uintptr_t pawnTeam;
	uintptr_t getPawnTeam();


	/*
	TODO: Define classes to properly get weapon data
		C_CSWeaponBase (look at offsets for inheritance)
		uint16_t getC_CSWeaponBase();
		uint16_t C_CSWeaponBase;
	*/
	uint64_t C_CSWeaponBase;
	uint16_t weaponID;
	uint16_t getWeaponID();

	int spotted;
	int getEntitySpotted();

	// CGameSceneNode
	uintptr_t CGameSceneNode;
	uintptr_t getCGameSceneNode();

};

class CGameSceneNode {
public:
	uintptr_t value;

	uintptr_t boneArray;
	uintptr_t getBoneArray();
};


class LocalPlayer {
public:
	uintptr_t localPlayer;
	uintptr_t base;

	LocalPlayer(uintptr_t baseAddy) {
		base = baseAddy;
		localPlayer = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwLocalPlayerController"]["value"]);
	}

	uintptr_t playerPawn;
	uintptr_t getPlayerPawn();

	uintptr_t team;
	uintptr_t getTeam();

	Vector3 cameraPos;
	Vector3 getCameraPos();

	Vector3 origin;
	Vector3 getOrigin();

	Vector3 viewAngles;
	Vector3 getViewAngles();

	Vector3 position;
	Vector3 getPosition();

	int flags;
	int getFlags();

	C_UTL_VECTOR aimPunchCache;
	C_UTL_VECTOR getAimPunchCache();

	Vector2 aimPunchAngle;
	Vector2 getAimPunchAngle();

	int shotsFired;
	int getShotsFired();

	void noFlash();

	int spotted;
	int getEntitySpotted();
};


// This is unrelated to all the other classes, but this is the most convenient way to share functions between features
class SharedFunctions {
public:
	static bool spottedCheck(C_CSPlayerPawn C_CSPlayerPawn, LocalPlayer localPlayer);
	static bool inGame(DWORD_PTR base);
};