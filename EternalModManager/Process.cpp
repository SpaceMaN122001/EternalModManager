#include "Process.h"

Process::Process()
{
}

Process::~Process()
{
}

void Process::run()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	TCHAR czCommandLine[] = TEXT("C:\\WINDOWS\\system32\\cmd.exe");
	TCHAR transport_to_folder[] = TEXT("cmd/k \"C:\\Program Files\\WinRAR\\rar.exe\" ");

	CreateProcess(czCommandLine, transport_to_folder, NULL, NULL, FALSE, 0, NULL, NULL, LPSTARTUPINFOW(&si), &pi);
}

void Process::runGame()
{
	PROCESS_INFORMATION ProcessInfo; //This is what we get as an [out] parameter

	STARTUPINFO StartupInfo; //This is an [in] parameter

	ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof StartupInfo; //Only compulsory field

	if (CreateProcess(L"C:\\Program Files (x86)\\Bandicam\\bdcam.exe", NULL,
		NULL, NULL, FALSE, 0, NULL,
		NULL, &StartupInfo, &ProcessInfo)) {
		WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
		CloseHandle(ProcessInfo.hThread);
		CloseHandle(ProcessInfo.hProcess);
	}
}

bool Process::isProcessRun(const WCHAR* processName)
{
   HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

   PROCESSENTRY32 pe;
   pe.dwSize = sizeof(PROCESSENTRY32);
   Process32First(hSnapshot, &pe);

   while (1) {

      if (wcscmp(pe.szExeFile, processName) == 0) {
          return true;
      }

      if (!Process32Next(hSnapshot, &pe)) return false;
   }
}

void Process::killUnpackingArchiveProcess()
{
	system("taskkill /IM UnpackingArchive.exe");
}
