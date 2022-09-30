#pragma once
HANDLE hProc;

class mem {
public: 
	template <class C>
	C read(DWORD_PTR(Add)) {
		C c;
		ReadProcessMemory(hProc, reinterpret_cast<LPCVOID>(Add), &c, sizeof(c), nullptr);//reading the Process's memory
		return c;
	}
	template <typename TYPE>
	void write(DWORD Add, TYPE dataToWrite) {
		TYPE buffer = dataToWrite;
		WriteProcessMemory(hProc, (LPVOID)Add, &buffer, sizeof(buffer), 0);
	}
};