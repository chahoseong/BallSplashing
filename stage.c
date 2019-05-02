#include "stage.h"
#include "graphics.h"

#include <stdlib.h>

wchar_t* LoadStage(const char* name)
{
	FILE* fp;
	fopen_s(&fp, name, "r");

	if (!fp)
		return NULL;

	Vector2 window_size = GetWindowSize();
	size_t buffer_size = sizeof(wchar_t) * window_size.x * window_size.y;

	fseek(fp, 0, SEEK_END);
	size_t data_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	wchar_t* buffer = (wchar_t*)malloc(buffer_size);
	if (!buffer)
		return NULL;

	fread_s(buffer, buffer_size, data_size, 1, fp);
	
	return buffer;
}