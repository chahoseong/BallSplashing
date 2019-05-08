#include "sound.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

void OpenAudio(const wchar_t* filename, const wchar_t* alias)
{
	wchar_t command[128];
	swprintf_s(command, 128, L"open %s type mpegvideo alias %s", filename, alias);
	mciSendString(command, NULL, 0, NULL);
}

void PlayAudio(const wchar_t* alias)
{
	wchar_t command[128];
	swprintf_s(command, 128, L"play %s from 0", alias);
	mciSendString(command, NULL, 0, NULL);
}

void PlayRepeatAudio(const wchar_t* alias)
{
	wchar_t command[128];
	swprintf_s(command, 128, L"play %s repeat", alias);
	mciSendString(command, NULL, 0, NULL);
}

void PauseAudio(const wchar_t* alias)
{
	wchar_t command[128];
	swprintf_s(command, 128, L"pause %s", alias);
	mciSendString(command, NULL, 0, NULL);
}

void CloseAudio(const wchar_t* alias)
{
	wchar_t command[128];
	swprintf_s(command, 128, L"close %s", alias);
	mciSendString(command, NULL, 0, NULL);
}