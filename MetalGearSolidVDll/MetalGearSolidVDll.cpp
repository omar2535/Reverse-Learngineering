// MetalGearSolidVDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MetalGearSolidVDll.h"
#include "MemoryManipulator.h"

void processMain() {
	
	// nops table
	std::string nops[] = {
		"\x90",
		"\x90\x90",
		"\x90\x90\x90",
		"\x90\x90\x90\x90",
	};
	
	// health
	bool healthActivationStatus = false;
	std::string HealthActivationStatusString = "off";
	std::vector<std::string> healthDefaultOpCodes = { "\xF3\x0F\x11\x0F", "\xF3\x45\x0F\x58\xD8" };
	std::vector<uintptr_t> healthAddresses = { 0x01411f15da, 0x01411f15de };
	// timer & main loop
	int lastActivationTimer = clock();
	while (true) {
		if (clock() - lastActivationTimer > 300) {
			// activation
			// activate health
			if (GetAsyncKeyState(VK_F1)) {
				lastActivationTimer = clock();
				healthActivationStatus = !healthActivationStatus;
				switch (healthActivationStatus) {
					case FALSE: 
						HealthActivationStatusString = "off";
						break;
					case TRUE: 
						HealthActivationStatusString = "on";
						break;
				}
			}

			// memory writing logic
			if (healthActivationStatus) {
				// TODO: use write to block memory
			}
			
		}
		Sleep(200);
	}
}

