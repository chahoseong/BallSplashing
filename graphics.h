#pragma once

int InitGraphics(int width, int height);
void CloseGraphics();

void ClearFrameBuffer();
void WriteFrameBuffer(char* string, int size, int x, int y);
void SwapFrameBuffer();