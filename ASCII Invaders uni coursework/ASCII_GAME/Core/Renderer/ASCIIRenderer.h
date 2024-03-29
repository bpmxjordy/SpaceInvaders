#ifndef _ASCII_RENDERER_H_
#define _ASCII_RENDERER_H_

#include <Windows.h>
#include "ConsoleColours.h"

class ASCIIRenderer
{
public:
	ASCIIRenderer();
	~ASCIIRenderer();

	void Initialise(int width, int height);
	void InitialisePixelSize();


	void Render();

	void SetPixel(int x, int y, CHAR_INFO* pPixelData);
	void ClearScreen(WORD clearColour = BACKGROUND_WHITE);	

private:

	void SetWindow(int width, int height);
	

	HANDLE m_hConsole;
	CHAR_INFO* m_ScreenData;
	int m_Width;
	int m_Height;

	bool m_bInitialised;
};

#endif
