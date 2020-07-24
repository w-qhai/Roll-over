#include "SuperSound.h"
/// <summary>
/// 配置文件位置(相对路径或绝对路径)
/// </summary>

const char* SuperSound::configPath = "pvzConfig.ini";

/// <summary>
/// 发送一个音乐指令(仅打开或仅关闭)
/// </summary>
/// <param name="key">配置KEY</param>
/// <returns></returns>

void SuperSound::sendASoundCommand(const char* key) {

	std::string szSoundContent = ConfigConvert::getConfig(configPath, key);

	mciSendStringW(stringToLPCWSTR(szSoundContent), NULL, 0, NULL);

}

/// <summary>
/// 特效音乐播放
/// 开辟线程，不会阻塞UI，推荐特效音乐用此函数播放
/// </summary>
/// <param name="openkey">配置打开KEY</param>
/// <param name="playkey">配置播放KEY</param>
/// <param name="closekey">配置关闭KEY</param>
/// <returns></returns>

void SuperSound::closeAndPlay(const char* openkey, const char* playkey, const char* closekey) {

	std::thread t([=] {

		SuperSound::sendASoundCommand(closekey);

		SuperSound::sendASoundCommand(openkey);

		SuperSound::sendASoundCommand(playkey);


	});

	t.detach();

}




LPCWSTR stringToLPCWSTR(std::string orig)
{
	size_t origsize = orig.length() + 1;

	const size_t newsize = 100;

	size_t convertedChars = 0;

	wchar_t* wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));

	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);

	return wcstring;
}

