using namespace std;
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <tlhelp32.h>

void Error_Message()
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);
	cout << "\nErro: " << (LPCTSTR)lpMsgBuf;
	system("pause");
}


int main()
{
	int varInt = 123456;
	int count = 0;
	int intToWrite=0;
	string processName;

	cout << "\nvarInt [0x" << hex << uppercase << (uintptr_t)&varInt << "] = " << dec << varInt << endl;
	cout << "Type the process's name: ";
	cin >> processName;

	PROCESSENTRY32 entry,write;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry))
	{
		while (Process32Next(snapshot, &entry))
		{
			if (_stricmp(entry.szExeFile, processName.c_str()) == 0) 
			{
				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
				write.th32ProcessID = entry.th32ProcessID; 
				cout<< "\nProcess ID being hooked: " << entry.th32ProcessID;
				count++;
			}
		}
	}
	if(count<=0)
	{
		cout << "\nProcess selected not found\n";
		system("pause");
		return EXIT_FAILURE;
	}
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, write.th32ProcessID);
	if (hProcess == NULL)
	{
		cout << "\nOpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else
	{
		uintptr_t memoryAddress = 0x0;
		cout << "\nMemory address of the integer to overwrite (in hexadecimal): 0x";
		cin >> hex >> memoryAddress;

		cout << "\nInteger to write (in decimal): ";
		cin >> dec >> intToWrite;

		if (WriteProcessMemory(hProcess, (LPVOID)memoryAddress, &intToWrite, sizeof(int), NULL))//(Handle to the proccess with memory - need at least VM_READ rights,
																			   //(Memory address of the target,A pointer to a buffer that receive the contents of the target,size of bytes being read,total number of bytes)
		{
			cout << "\nOverwritten successfully\n";
			CloseHandle(hProcess);
			system("pause");
		}
		else
		{
			Error_Message();
			return EXIT_FAILURE;
		}

	}
}

