// MetalGearSolidVDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MetalGearSolidVDll.h"
#include "MemoryManipulator.h"
#include "utils.h"

void processMain() {
	
	// activation status bools
	bool healthActivationStatus = false;
	bool ammoActivationStatus = false;
	bool recoilActivationStatus = false;
	bool specialAmmoActivationStatus = false;

	// activation status strings
	std::string healthActivationStatusString = "off";
	std::string ammoActivationStatusString = "off";
	std::string recoilActivationStatusString = "off";
	std::string specialAmmoActivationStatusString = "off";

	// assembly locations
	std::vector<uintptr_t> healthAddresses = { 0x01411f15da, 0x01411f15de };
	std::vector<uintptr_t> ammoAddresses = { 0x0000000147CF0A50 };
	std::vector<uintptr_t> recoilAddresses = { 0x0000000148432A3B };
	std::vector<uintptr_t> swayAddresses = { 0x0000000148437FD6 };
	std::vector<uintptr_t> specialAmmoAddresses = { 0x0000000147CF0CF2 };

	// default op codes, so that when we
	// turn it off the default state will
	// be returned
	std::vector<std::vector<BYTE> > healthDefaultOpCodes = { {0xF3, 0x0F, 0x11, 0x0F}, {0xF3, 0x45, 0x0F,0x58,0xD8} };
	std::vector<std::vector<BYTE> > ammoDefaultOpCodes = { { 0x66, 0x44, 0x89, 0x1C, 0x48 } };


	HANDLE hProcess = GetCurrentProcess();

	// timer & main loop
	int lastActivationTimer = clock();
	while (true) {
		system("cls");
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		// printf("Debugging Window:\n");
		printf("(F1) Infinite Health: %S \n", healthActivationStatusString);
		printf("(F2) Infinite Ammo: %S \n", ammoActivationStatusString);

		if (clock() - lastActivationTimer > 300) {
			// activation
			// activate health
			if (GetAsyncKeyState(VK_F1)) {
				lastActivationTimer = clock();
				healthActivationStatus = !healthActivationStatus;
				switch (healthActivationStatus) {
					case TRUE: 
						healthActivationStatusString = "on";
						WriteBlockNopsToMemory(hProcess, healthAddresses, healthDefaultOpCodes);
						break;
					case FALSE: 
						healthActivationStatusString = "off";
						WriteBlockToMemory(hProcess, healthAddresses, healthDefaultOpCodes);
						break;
				}
			}
			// activate infinite ammo
			if (GetAsyncKeyState(VK_F2)) {
				lastActivationTimer = clock();
				ammoActivationStatus = !ammoActivationStatus;
				switch (ammoActivationStatus) {
					case TRUE:
						ammoActivationStatusString = "on";
						WriteBlockNopsToMemory(hProcess, ammoAddresses, ammoDefaultOpCodes);
						break;
					case FALSE:
						ammoActivationStatusString = "off";
						WriteBlockToMemory(hProcess, ammoAddresses, ammoDefaultOpCodes);
						break;
				}
			}
		}
		Sleep(200);
	}
}

