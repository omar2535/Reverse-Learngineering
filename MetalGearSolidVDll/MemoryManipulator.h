#pragma once

// Writes to address in memory
void WriteToMemory(uintptr_t addressToWrite, char* valueToWrite, int numberOfBytes);
uintptr_t FindDMAddy(int pointerLevel, uintptr_t offsets[], uintptr_t baseAddress);
void WriteProcessToMemory(HANDLE handle, uintptr_t address, std::vector<BYTE> byteSequence);
void WriteBlockNopsToMemory(HANDLE handle, std::vector<uintptr_t> addresses_to_write, std::vector<std::vector<BYTE> > defaultOpCodes);
void WriteBlockToMemory(HANDLE handle, std::vector<uintptr_t> addresses_to_write, std::vector<std::vector<BYTE> > opcodes_to_write);