// MetalGearSolidVDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MetalGearSolidVDll.h"
#include "MemoryManipulator.h"
#include "utils.h"

void processMain() {
	
	// health
	bool healthActivationStatus = false;
	std::string healthActivationStatusString = "off";
	// std::vector<std::string> healthDefaultOpCodes = { "\xF3\x0F\x11\x0F", "\xF3\x45\x0F\x58\xD8" };
	// BYTE version
	std::vector<std::vector<BYTE> > healthDefaultOpCodes = { {0xF3, 0x0F, 0x11, 0x0F}, {0xF3, 0x45, 0x0F,0x58,0xD8} };
	int healthNumberOfBytes[] = { 4, 5 };
	std::vector<uintptr_t> healthAddresses = { 0x01411f15da, 0x01411f15de };
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
		printf("(F1) Infinite Health: %d \n", healthActivationStatus);
		if (clock() - lastActivationTimer > 300) {
			// activation
			// activate health
			if (GetAsyncKeyState(VK_F1)) {
				lastActivationTimer = clock();
				healthActivationStatus = !healthActivationStatus;
				switch (healthActivationStatus) {
					case FALSE: 
						healthActivationStatusString = "off";
						break;
					case TRUE: 
						healthActivationStatusString = "on";
						break;
				}
			}

			// memory writing logic
			if (healthActivationStatus) {
				
			}
			else {
				for (int i = 0; i < healthAddresses.size(); i++) {
					// WriteToMemory(healthAddresses[i], StringToCharArr(healthDefaultOpCodes[i]), healthNumberOfBytes[i]);
					WriteProcessToMemory(hProcess, healthAddresses[i], healthDefaultOpCodes[i]);
				}
			}
			
		}
		Sleep(200);
	}
}

