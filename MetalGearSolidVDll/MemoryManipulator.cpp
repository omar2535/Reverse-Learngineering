#include "stdafx.h"
#include "MemoryManipulator.h"
#include "utils.h"

using namespace std;

// write to memory
// takes in an address to write, the byte sequence to write, and the size of the byte sequence
void WriteToMemory(uintptr_t addressToWrite, char* valueToWrite, int numberOfBytes) {
	unsigned long oldProtection;
	// gives us permission to read & write to the address, and grab the old protection to that part in memory
	// and store it in oldProtection
	VirtualProtect((LPVOID)addressToWrite, numberOfBytes, PAGE_EXECUTE_READWRITE, &oldProtection);
	memcpy((LPVOID)addressToWrite, valueToWrite, numberOfBytes);
	// reset type of protection at the address back to old protection to leave everything as it was
	VirtualProtect((LPVOID)addressToWrite, numberOfBytes, oldProtection, NULL);
}

// Adds up offsets until you hit direct memory
uintptr_t FindDMAddy(int pointerLevel, uintptr_t offsets[], uintptr_t baseAddress) {
	uintptr_t pointer = *(uintptr_t*)(baseAddress);
	if (pointer == 0) return NULL;

	for (int i = 0; i < pointerLevel; i++) {
		if (i == pointerLevel - 1) {
			pointer = (uintptr_t)(pointer + offsets[i]);
			if (pointer == 0) return NULL;
			return pointer;
		}
		else {
			pointer = *(uintptr_t*)(pointer + offsets[i]);
			if (pointer == 0) return NULL;
		}
	}
	return pointer;
}

// writes into a block of memory
// addresses_to_write: an array of addresses in which the information is stored at
// value to write: a array of byte sequences that should total up to the same number of bytes
//				   stored within the original addresses
// eg. WriteBlockMemory({0x10000,0x10002}, [{0x90, 0x90}, {0x90, 0x90}], {2, 2})
void WriteBlockToMemory(HANDLE handle, vector<uintptr_t> addresses_to_write, vector<vector<BYTE> > opcodes_to_write) {
	for (int i = 0; i < addresses_to_write.size(); i++) {
		WriteProcessToMemory(handle, addresses_to_write[i], opcodes_to_write[i]);
	}
}

// will write a block of nops to memory
// length of addresses_to_write should be the same as length of defaultOpCodes
// requires the default opcodes to determine number of nops to write
// this is to keep consistent size accross instructions
void WriteBlockNopsToMemory(HANDLE handle, vector<uintptr_t> addresses_to_write, vector<vector<BYTE> > defaultOpCodes) {
	for (int i = 0; i < addresses_to_write.size(); i++) {
		WriteProcessToMemory(handle, addresses_to_write[i], NoOpsBuilderByte(defaultOpCodes[i].size()));
	}
}

void WriteProcessToMemory(HANDLE handle, uintptr_t address, vector<BYTE> byteSequence) {
	BYTE* bytesToInject = &byteSequence[0];
	WriteProcessMemory(handle, (BYTE*)address, bytesToInject, byteSequence.size(), 0);
}