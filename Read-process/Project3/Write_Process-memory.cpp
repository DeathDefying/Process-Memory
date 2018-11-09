using namespace std;
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>

void Error_Message_Write()
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
	int intToWrite = 987654;
	int processID;
	string varString = "Default String";
	char arrChar[128] = "Long char array right there";
	int *ptr2int;
	int **ptr2ptr;
	int ***ptr2ptr2;

	ptr2int = &varInt;
	ptr2ptr = &ptr2int;
	ptr2ptr2 = &ptr2ptr;

	processID = GetCurrentProcessId();

	cout << "Process ID:		" << processID;

	cout << "\nvarInt			[" << &varInt;
	cout << "] = " << varInt;

	cout << "\nvarString		[" << &varString;
	cout << "] = " << varString;

	cout << "\narrChar[128]		[" << &arrChar;
	cout << "] = " << arrChar;

	cout << "\n\nptr2int			[" << &ptr2int;
	cout << "] = " << ptr2int;

	cout << "\nptr2ptr			[" << &ptr2ptr;
	cout << "] = " << ptr2ptr;

	cout << "\nptr2ptr2		[" << &ptr2ptr2;
	cout << "] = " << ptr2ptr2;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID); //(all possible access rights for the process object, INHERIT rights for children processes, the processID of the object)

	if (hProcess == NULL)
	{
		cout << "OpenProcess failed. GetLastError = " << dec << GetLastError() << endl;
		system("pause");
		return EXIT_FAILURE;
	}
	else
	{
		if (WriteProcessMemory(hProcess,&varInt,&intToWrite,sizeof(int),NULL))//(Handle to the proccess with memory - need at least VM_READ rights,
																			   //(Memory address of the target,A pointer to a buffer that receive the contents of the target,size of bytes being read,total number of bytes)
		{
			cout << "Overwritten successfully";
			system("pause");
		}
		else
		{
			Error_Message_Write();
			return EXIT_FAILURE;
		}

	}
}

