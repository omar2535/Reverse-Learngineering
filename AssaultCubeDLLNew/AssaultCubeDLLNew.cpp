// AssaultCubeDLLNew.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include <ctime>
#include <string>
#include <iostream>

void WriteToMemory(DWORD addressToWrite, char* valueToWrite, int numberOfBytes);
DWORD FindDMAddy(int pointerLevel, DWORD offsets[], DWORD baseAddress);
char *StringToCharArr(std::string strToConvert);

void processMain() {
	std::string nops[] = {
		"\x90",
		"\x90\x90",
		"\x90\x90\x90",
		"\x90\x90\x90\x90",
	};
	
	// infinite ammo
	bool ammoStatus = false;
	char ammoOpCode[] = "\xFF\x06";
	char ammoDefaultOpCode[] = "\xFF\x0E";
	DWORD ammoOpcodeAddress = 0x004637E9;

	// rapid fire
	bool rapidFireStatus = false;
	char rapidFireOpCode[] = "\x90\x90";
	char rapidFireDefaultOpCode[] = "\x89\x0A";
	DWORD rapidFireOpcodeAddress = 0x004637E4;

	// automatic weapon
	bool automaticStatus = false;
	char automaticOpCode[] = "\xEB\x09";
	char automaticDefaultOpCode[] = "\x75\x09";
	DWORD automaticOpcodeAddress = 0x463716;

	// health
	bool healthStatus = false;
	char healthValue[] = "\x39\x05";
	char healthDefaultValue[] = "\x64\x00";
	DWORD healthBaseAddress = 0x50f4f4;
	DWORD healthOffsets[] = { 0xF8 };
	DWORD healthAddressToWrite;

	// recoil 
	bool recoilStatus = false;
	int recoilNoOfBytes[] = { 2,3,1,4,1,2,2 };
	std::string recoilDefaultOpCodes[] = {
		"\x8B\x16",
		"\x8B\x52\x14",
		"\x50",
		"\x8D\x4C\x24\x1C",
		"\x51",
		"\x8B\xCE",
		"\xFF\xD2",
	};
	DWORD recoilOpcodeAddress[] = {
		0x00463781,
		0x00463783,
		0x00463786,
		0x00463787,
		0x0046378B,
		0x0046378C,
		0x0046378E
	};

	int lastActivatedTimer = clock();
	while (true) {
		system("cls");
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		printf("Debugging Window:\n");
		printf("(F1) Infinite Ammo: %d \n", ammoStatus);
		printf("(F2) Infinite Health: %d \n", healthStatus);
		printf("(F3) Rapid Fire: %d \n", rapidFireStatus);
		printf("(F4) No Recoil: %d \n", recoilStatus);
		printf("(F5) Automatic All Weapons: %d \n", automaticStatus);

		
		// check for activations
		if (clock() - lastActivatedTimer > 400) {
			// Ammo
			if (GetAsyncKeyState(VK_F1)) {
				lastActivatedTimer = clock();
				ammoStatus = !ammoStatus;
				if (ammoStatus) {
					WriteToMemory(ammoOpcodeAddress, ammoOpCode, 2);
				}
				else {
					WriteToMemory(ammoOpcodeAddress, ammoDefaultOpCode, 2);
				}
			}
			// Health
			if (GetAsyncKeyState(VK_F2)) {
				lastActivatedTimer = clock();
				healthStatus = !healthStatus;
				healthAddressToWrite = FindDMAddy(1, healthOffsets, healthBaseAddress);
				if (healthStatus) {
					if (healthAddressToWrite != NULL) {
						WriteToMemory(healthAddressToWrite, healthValue, 2);
					}
				}
				else {
					WriteToMemory(healthAddressToWrite, healthDefaultValue, 2);
				}
			}
			// rapid fire
			if (GetAsyncKeyState(VK_F3)) {
				lastActivatedTimer = clock();
				rapidFireStatus = !rapidFireStatus;
				if (rapidFireStatus) {
					WriteToMemory(rapidFireOpcodeAddress, rapidFireOpCode, 2);
				}
				else {
					WriteToMemory(rapidFireOpcodeAddress, rapidFireDefaultOpCode, 2);
				}
			}
			//recoil
			if (GetAsyncKeyState(VK_F4)) {
				lastActivatedTimer = clock();
				recoilStatus = !recoilStatus;
				if (recoilStatus) {
					for (int i = 0; i < 7; i++) {
						WriteToMemory(recoilOpcodeAddress[i], StringToCharArr(nops[recoilNoOfBytes[i] - 1]), recoilNoOfBytes[i]);
					}
				}
				else {
					for (int i = 0; i < 7; i++) {
						WriteToMemory(recoilOpcodeAddress[i], StringToCharArr(recoilDefaultOpCodes[i]), recoilNoOfBytes[i]);
					}
				}
			}
			//automatic
			if (GetAsyncKeyState(VK_F5)) {
				lastActivatedTimer = clock();
				automaticStatus = !automaticStatus;
				if (automaticStatus) {
					WriteToMemory(automaticOpcodeAddress, automaticOpCode, 2);
				}
				else {
					WriteToMemory(automaticOpcodeAddress, automaticDefaultOpCode, 2);
				}
			}

		}
		Sleep(100);
	}
}

// converts string to character array
char *StringToCharArr(std::string strToConvert) {
	char *charRet = new char[strToConvert.length() + 1];
	std::strcpy(charRet, strToConvert.c_str());
	return charRet;
}
// write to memory
void WriteToMemory(DWORD addressToWrite, char* valueToWrite, int numberOfBytes) {
	unsigned long oldProtection;
	// gives us permission to read & write to the address, and grab the old protection to that part in memory
	// and store it in oldProtection
	VirtualProtect((LPVOID)addressToWrite, numberOfBytes, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy((LPVOID)addressToWrite, valueToWrite, numberOfBytes);
	// reset type of protection at the address back to old protection to leave everything as it was
	VirtualProtect((LPVOID)addressToWrite, numberOfBytes, oldProtection, NULL);
}



DWORD FindDMAddy(int pointerLevel, DWORD offsets[], DWORD baseAddress) {
	DWORD pointer = *(DWORD*)(baseAddress);
	if (pointer == 0) return NULL;

	for (int i = 0; i < pointerLevel; i++) {
		if (i == pointerLevel - 1) {
			pointer = (DWORD)(pointer + offsets[i]);
			if (pointer == 0) return NULL;
			return pointer;
		}
		else {
			pointer = *(DWORD*)(pointer + offsets[i]);
			if (pointer == 0) return NULL;
		}
	}
	return pointer;
}