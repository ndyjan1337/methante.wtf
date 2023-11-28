#include "attributes.hpp"



uintptr_t CCSPlayerController::getListEntry() {
	listEntry = MemMan.ReadMem<uintptr_t>(entityList + (0x8 * (id & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t CCSPlayerController::getController() {
	value = MemMan.ReadMem<uintptr_t>(listEntry + 0x78 * (id & 0x1FF));
	return value;
}

int CCSPlayerController::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(value + clientDLL::CCSPlayerController_["m_iPawnHealth"]["value"]);
	return pawnHealth;
}

std::uint32_t CCSPlayerController::getC_CSPlayerPawn() {
	C_CSPlayerPawn_ = MemMan.ReadMem<std::uint32_t>(value + clientDLL::CCSPlayerController_["m_hPlayerPawn"]["value"]);
	return C_CSPlayerPawn_;
}

uintptr_t CCSPlayerController::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + clientDLL::C_BaseEntity_["m_iTeamNum"]["value"]);
	return pawnTeam;
}

std::string CCSPlayerController::getPawnName() {
	pawnNameAddress = MemMan.ReadMem<uintptr_t>(value + clientDLL::CCSPlayerController_["m_sSanitizedPlayerName"]["value"]);
	if (pawnNameAddress) {
		char buf[MAX_PATH] = {};
		MemMan.ReadRawMem(pawnNameAddress, buf, MAX_PATH);
		pawnName = std::string(buf);
	}
	else {
		pawnName = "Unknown";
	}
	return pawnName;
}



uintptr_t C_CSPlayerPawn::getListEntry() {
	listEntry = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * ((value & 0x7FFF) >> 9) + 0x10);
	return listEntry;
}

uintptr_t C_CSPlayerPawn::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(listEntry + 0x78 * (value & 0x1FF));
	return playerPawn;
}

uintptr_t C_CSPlayerPawn::getPlayerPawnByCrossHairID(int crossHairEntity) {
	uintptr_t crosshairEntityEntry = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * (crossHairEntity >> 9) + 0x10);
	playerPawn = MemMan.ReadMem<uintptr_t>(crosshairEntityEntry + 0x78 * (crossHairEntity & 0x1FF));
	return playerPawn;
}

Vector3 C_CSPlayerPawn::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["m_vOldOrigin"]["value"]);
	return origin;
}

Vector3 C_CSPlayerPawn::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_vecLastClipCameraPos"]["value"]);
	return cameraPos;
}

uintptr_t C_CSPlayerPawn::getCGameSceneNode() {
	CGameSceneNode = MemMan.ReadMem<uintptr_t>(playerPawn + clientDLL::C_BaseEntity_["m_pGameSceneNode"]["value"]);
	return CGameSceneNode;
}

Vector3 C_CSPlayerPawn::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_angEyeAngles"]["value"]);
	return viewAngles;
}

Vector3 C_CSPlayerPawn::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::CBaseAnimGraph_["m_vLastSlopeCheckPos"]["value"]);
	return position;
}

uint16_t C_CSPlayerPawn::getWeaponID() {
	C_CSWeaponBase = MemMan.ReadMem<uint64_t>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_pClippingWeapon"]["value"]);
	weaponID = MemMan.ReadMem<uint16_t>(C_CSWeaponBase + clientDLL::C_EconItemView_["m_iItemDefinitionIndex"]["value"] + clientDLL::C_AttributeContainer_["m_Item"]["value"] + clientDLL::C_EconEntity_["m_AttributeManager"]["value"]);
	return weaponID;
}

int C_CSPlayerPawn::getPawnHealth() {
	pawnHealth = MemMan.ReadMem<int>(playerPawn + clientDLL::C_BaseEntity_["m_iHealth"]["value"]);
	return pawnHealth;
}

uintptr_t C_CSPlayerPawn::getPawnTeam() {
	pawnTeam = MemMan.ReadMem<uintptr_t>(value + clientDLL::C_BaseEntity_["m_iTeamNum"]["value"]);
	return pawnTeam;
}

int C_CSPlayerPawn::getEntitySpotted() {
	spotted = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_entitySpottedState"]["value"] + clientDLL::EntitySpottedState_t_["m_bSpottedByMask"]["value"]);
	return spotted;
}




uintptr_t LocalPlayer::getPlayerPawn() {
	playerPawn = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwLocalPlayerPawn"]["value"]);
	return playerPawn;
}

uintptr_t LocalPlayer::getTeam() {
	team = MemMan.ReadMem<uintptr_t>(localPlayer + clientDLL::C_BaseEntity_["m_iTeamNum"]["value"]);
	return team;
}

Vector3 LocalPlayer::getCameraPos() {
	cameraPos = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_vecLastClipCameraPos"]["value"]);
	return cameraPos;
}

Vector3 LocalPlayer::getViewAngles() {
	viewAngles = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["v_angle"]["value"]);
	return viewAngles;
}

Vector3 LocalPlayer::getPosition() {
	position = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::CBaseAnimGraph_["m_vLastSlopeCheckPos"]["value"]);
	return position;
}

Vector3 LocalPlayer::getOrigin() {
	origin = MemMan.ReadMem<Vector3>(playerPawn + clientDLL::C_BasePlayerPawn_["m_vOldOrigin"]["value"]);
	return origin;
}

int LocalPlayer::getFlags() {
	flags = MemMan.ReadMem<int>(playerPawn + clientDLL::C_BaseEntity_["m_fFlags"]["value"]);
	return flags;
}

C_UTL_VECTOR LocalPlayer::getAimPunchCache() {
	aimPunchCache = MemMan.ReadMem<C_UTL_VECTOR>(playerPawn + clientDLL::C_CSPlayerPawn_["m_aimPunchCache"]["value"]);
	return aimPunchCache;
}

Vector2 LocalPlayer::getAimPunchAngle() {
	aimPunchAngle = MemMan.ReadMem<Vector2>(playerPawn + clientDLL::C_CSPlayerPawn_["m_aimPunchAngle"]["value"]);
	return aimPunchAngle;
}

int LocalPlayer::getShotsFired() {
	shotsFired = MemMan.ReadMem<int>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_iShotsFired"]["value"]);
	return shotsFired;
}

void LocalPlayer::noFlash() {
	MemMan.WriteMem<float>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_flFlashDuration"]["value"], 0.f);
}

int LocalPlayer::getEntitySpotted() {
	spotted = MemMan.ReadMem<DWORD_PTR>(playerPawn + clientDLL::C_CSPlayerPawnBase_["m_entitySpottedState"]["value"] + clientDLL::EntitySpottedState_t_["m_bSpottedByMask"]["value"]);
	return spotted;
}



uintptr_t CGameSceneNode::getBoneArray() {
	boneArray = MemMan.ReadMem<uintptr_t>(value + clientDLL::CSkeletonInstance_["m_modelState"]["value"] + clientDLL::CGameSceneNode_["m_vecOrigin"]["value"]);
	return boneArray;
}




bool SharedFunctions::spottedCheck(C_CSPlayerPawn C_CSPlayerPawn, LocalPlayer localPlayer) {
	if (C_CSPlayerPawn.getEntitySpotted() & (1 << (localPlayer.playerPawn)) || localPlayer.getEntitySpotted() & (1 << (C_CSPlayerPawn.playerPawn))) return 1;
	return 0;
}

bool SharedFunctions::inGame(DWORD_PTR base) {
	uintptr_t gameRules = MemMan.ReadMem<uintptr_t>(base + offsets::clientDLL["dwGameRules"]["value"]);

	bool warmup = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bWarmupPeriod"]["value"]);
	bool match = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bHasMatchStarted"]["value"]);
	bool freeze = MemMan.ReadMem<bool>(gameRules + clientDLL::C_CSGameRules_["m_bFreezePeriod"]["value"]);

	return match;
}