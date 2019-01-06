#pragma once

// Writes to address in memory
void WriteToMemory(uintptr_t addressToWrite, char* valueToWrite, int numberOfBytes);
uintptr_t FindDMAddy(int pointerLevel, uintptr_t offsets[], uintptr_t baseAddress);
void WriteProcessToMemory(HANDLE handle, uintptr_t address, std::vector<BYTE> byteSequence);