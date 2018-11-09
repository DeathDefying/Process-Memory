
using namespace std;
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>

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
	int intRead = 0;
	int processID;

	processID = GetCurrentProcessId();

	cout << "Process ID: "<<processID;

	cout << "\nvarInt [0x" << hex << uppercase << (uintptr_t)&varInt << "] = " << dec << varInt << endl;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID); //(all possible access rights for the process object, INHERIT rights for children processes, the processID of the object)

	uintptr_t memoryAddress = 0x0;
	cout << "\nMemory address of the integer to read (in hexadecimal): 0x";
	cin >> hex >> memoryAddress;
	cout << "Reading 0x" << hex << uppercase << memoryAddress << " ..." << endl;

	if (hProcess == NULL)
	{
		cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else
	{
		if (ReadProcessMemory(hProcess, (LPCVOID)memoryAddress, &intRead, sizeof(int), NULL)) //(Handle to the proccess with memory - need at least VM_READ rights,
																			   //(Memory address of the target,A pointer to a buffer that receive the contents of the target,size of bytes being read,total number of bytes)
		{
			cout << "\nintRead = " << dec << intRead << endl;
			system("pause");
		}
		else 
		{
			Error_Message();	
			return EXIT_FAILURE;
		}
		
	}

	cout << "\nvarInt       [0x" << hex << uppercase << (uintptr_t)&varInt << "] = " << dec << varInt << endl;

	system("pause");
}

