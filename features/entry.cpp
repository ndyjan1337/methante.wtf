#include "esp.hpp"


#include "../util/utilFunctions.hpp"

void mainLoop(bool state, MemoryManagement::moduleData client) {
	// Classes
	CCSPlayerController		CCSPlayerController(client.base);
	C_CSPlayerPawn			C_CSPlayerPawn(client.base);
	CGameSceneNode			CGameSceneNode;
	LocalPlayer				localPlayer(client.base);


	// Shared variables (between features)
	view_matrix_t viewMatrix = MemMan.ReadMem<view_matrix_t>(client.base + offsets::clientDLL["dwViewMatrix"]["value"]);
	Vector3 baseViewAngles = MemMan.ReadMem<Vector3>(client.base + offsets::clientDLL["dwViewAngles"]["value"]);
	DWORD_PTR baseViewAnglesAddy = client.base + offsets::clientDLL["dwViewAngles"]["value"];

	// NOTE: Cheats that only need local player / visuals that don't relate to gameplay
	localPlayer.getPlayerPawn();
	// Aimbot FOV circle





	// Main loop
	for (int i = 0; i < 64; i++) {

		// Player controller
		CCSPlayerController.id = i;
		CCSPlayerController.getListEntry();
		CCSPlayerController.getController();
		if (CCSPlayerController.value == 0) continue;

		// Player pawn
		C_CSPlayerPawn.value = CCSPlayerController.getC_CSPlayerPawn();
		C_CSPlayerPawn.getListEntry();
		C_CSPlayerPawn.getPlayerPawn();
		C_CSPlayerPawn.getPawnHealth();

		// Checks
		if ((C_CSPlayerPawn.getPawnHealth() <= 0 || C_CSPlayerPawn.getPawnHealth() > 100) || localPlayer.getTeam() == CCSPlayerController.getPawnTeam() || strcmp(CCSPlayerController.getPawnName().c_str(), "DemoRecorder") == 0) continue;

		// Game scene node
		CGameSceneNode.value = C_CSPlayerPawn.getCGameSceneNode();

		// ESP
		if (espConf.state) {
			esp::sharedData::weaponID = C_CSPlayerPawn.getWeaponID();
			esp::sharedData::localOrigin = localPlayer.getOrigin();
			esp::sharedData::entityOrigin = C_CSPlayerPawn.getOrigin();
			esp::sharedData::distance = (int)(utils::getDistance(esp::sharedData::localOrigin, esp::sharedData::entityOrigin)) / 100;

			if (espConf.checkSpotted) {
				if (SharedFunctions::spottedCheck(C_CSPlayerPawn, localPlayer)) {
					esp::boundingBox(C_CSPlayerPawn.getOrigin(), viewMatrix, CCSPlayerController.getPawnName(), C_CSPlayerPawn.pawnHealth, CGameSceneNode.getBoneArray(),true);
				}
			}
			else {
				esp::boundingBox(C_CSPlayerPawn.getOrigin(), viewMatrix, CCSPlayerController.getPawnName(), C_CSPlayerPawn.pawnHealth, CGameSceneNode.getBoneArray(),SharedFunctions::spottedCheck(C_CSPlayerPawn, localPlayer));
			}
		}

		// Aim

	}
}