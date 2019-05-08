#pragma once

#include <stdio.h>

void OpenAudio(const wchar_t* filename, const wchar_t* alias);
void PlayAudio(const wchar_t* alias);
void PlayRepeatAudio(const wchar_t* alias);
void PauseAudio(const wchar_t* alias);
void CloseAudio(const wchar_t* alias);