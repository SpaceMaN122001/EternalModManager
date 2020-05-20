#pragma once
#include "windows.h"
#include <tlhelp32.h>
#include <string>

class Process
{
public:
	Process();
	~Process();
	static void run();
	static void runGame();
	static bool isProcessRun(const WCHAR*);
	static void killUnpackingArchiveProcess();
};

