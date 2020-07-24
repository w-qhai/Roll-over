#pragma once

#include <thread>
#include <Windows.h>
#include <mmsystem.h>
#include "ConfigConvert.h"
#pragma comment(lib, "winmm.lib")

LPCWSTR stringToLPCWSTR(std::string orig);

class SuperSound {

private:
	static const char* configPath;
	
public:

	static void sendASoundCommand(const char* key);
	static void closeAndPlay(const char* openkey, const char* playkey, const char* closekey);
};