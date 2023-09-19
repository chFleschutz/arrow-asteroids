#include "CharSet.h"
#include <iostream>

const CharSet CharSet::instance;

using namespace std;

void CharSet::drawString(ViewPortGL* vp, string s, int x, int y, int width, int height, int red, int green, int blue) const
{
	// Split String in Chars
	int CharWidth = width / s.length();
	int xPos = x;
	for (int i = 0; i < s.length(); i++)
	{
		drawChar(vp, s[i], xPos, y, CharWidth, height, red, green, blue);
		xPos = xPos + CharWidth;
	}
}

void CharSet::drawChar(ViewPortGL* vp, char c, int x, int y, int width, int height, int red, int green, int blue) const
{
	// Convert char to number	
	int num = static_cast<int>(c);
	if (num < 48 || num > 57)
	{
		if (c == '0') num = 0;
		else if (c == ' ') num = -6;
		else num = num - 64;
	}
	int charByteOffset = num * 8;

	// Split in lines
	int lineHeight = height / 8;
	int yPos = y;

	// For each line drawByte()
	for (int i = 0; i < 8; i++)
	{
		drawByte(vp, charByteOffset, x, yPos, width, lineHeight, red, green, blue);
		charByteOffset++;
		yPos = yPos + lineHeight;
	}
}

void CharSet::drawByte(ViewPortGL* vp, int index, int x, int y, int width, int height, int red, int green, int blue) const
{
	// Get Value from Table
	int value = charBitTable[index];

	float xPos = x;
	float blockWidth = width / 8.f;

	// Create Mask for Bit operation
	int mask = 1 << 7;

	for (int i = 0; i < 8; i++)
	{
		// Check Bit at Position i with mask
		if ((mask & value) != 0)
		{
			// if Bit is set draw Block
			vp->prepareBlock(xPos, y, blockWidth, height, red, green, blue);
		}
		xPos = xPos + blockWidth;
		mask = mask >> 1;
	}
}
