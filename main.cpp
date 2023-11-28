#define WIN32_LEAN_AND_MEAN 

#include <windows.h>

#include "gui/overlay.hpp"
#include "util/MemMan.hpp"
#include "util/attributes.hpp"
#include <vxlib.h>

std::string username;
std::string password;

LRESULT Wndproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
		return 0;
	}

	switch (msg) {
	case WM_SYSCOMMAND: {
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		return 0;
	}
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void loginfunction() {
	VL_VIRTUALIZATION_BEGIN;


	if (!authenticate(username, password)) {

		std::cout << "\n\n < Login Failure > ";

		Sleep(1000);
		exit(0);
	}

	VL_VIRTUALIZATION_END;

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	VL_VIRTUALIZATION_BEGIN;

	// Memory and game related vars (used in entry and passed through overlay)
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);


	std::cout << "\n\n username : ";
	std::cin >> username;
	std::cout << "\n password : ";
	std::cin >> password;

	loginfunction();





	int procId = MemMan.getPid(L"cs2.exe");
	if (procId == 0) exit(-1);
	
	MemoryManagement::moduleData client;
	client.module = MemMan.getModule(procId, L"client.dll");
	client.base = MemMan.getModuleBase(procId, L"client.dll");

	// Overlay
	overlayESP overlayClass;
	WNDCLASSEXW windowClass = overlayClass.createWindowClass(hInstance, Wndproc, L"methane");
	HWND window = overlayClass.createWindow(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

	overlayClass.makeFrameIntoClientArea();
	overlayClass.makeDeviceAndSwapChain();
	overlayClass.initWindow(nShowCmd);
	overlayClass.renderLoop(client);

	return 0;
	VL_VIRTUALIZATION_END;

}