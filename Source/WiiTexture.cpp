// This file is part of Egoboo-Wii.
//
// Egoboo-Wii is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Egoboo-Wii is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Egoboo-Wii.  If not, see <http:// www.gnu.org/licenses/>.

#include <cstdlib>
#include <cstring>
#include <ogc/cache.h>
#include <malloc.h>

#include "WiiDisplay.hpp"
#include "WiiTexture.hpp"

#include "Color.hpp"
#include <fstream>

// Converts a Rgba8 texture to the native Wii format
// Note: Refer to YAGCD for specifics on why this code is so ugly
void * ConvertRgba8(const void * data, int width, int height)
{
	const unsigned char * input = (const unsigned char *)data;
	unsigned char * output = (unsigned char *)memalign(32, width * height * 4);
	
	if (output == NULL)
		return NULL;
	
	unsigned char * pixels = output;
	for (int block = 0; block < height; block += 4)
	{
		for (int x = 0; x < width; x += 4)
		{
			// Alpha and red values
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					int index = (x + j + (block + i) * width) * 4;
					
					*pixels++ = input[index + 3];
					*pixels++ = input[index];
				}	
			}
			
			// Green and blue values
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					int index = (x + j + (block + i) * width) * 4;
					
					*pixels++ = (int)input[index + 1];
					*pixels++ = (int)input[index + 2];
				}
			}
		}
	}
	
	DCFlushRange(output, width * height * 4);
	
	return output;
}

Adventure::WiiTexture::WiiTexture(WiiDisplay& display)
	: display(display)
{
	textureData = NULL;
	
	width = 0;
	height = 0;
	format = Rgba8;
	quality = Point;
}

Adventure::WiiTexture::~WiiTexture()
{
	if (textureData != NULL)
		free(textureData);
}

bool Adventure::WiiTexture::SetData(const void * data, int width, int height, Format format, Quality quality)
{
	unsigned char dataFormat, textureFilter;
	
	// Free the previous texture, if valid
	if (textureData != NULL)
		free(textureData);
	
	switch (format)
	{
		case Rgba8:
		default:
			dataFormat = GX_TF_RGBA8;
			textureData = ConvertRgba8(data, width, height);
			
			if (textureData == NULL)
				return false;
			break;
	}
	
	switch (quality)
	{
		case Linear:
			textureFilter = GX_LINEAR;
			break;
			
		case Point:
		default:
			textureFilter = GX_NEAR;
			break;
	}
	
	GX_InitTexObj(&textureObject, textureData, (unsigned short int)width, (unsigned short int)height, dataFormat, GX_CLAMP, GX_CLAMP, GX_FALSE);
	GX_InitTexObjFilterMode(&textureObject, textureFilter, textureFilter);
	
	// Store important details
	this->width = width;
	this->height = height;
	this->format = format;
	this->quality = quality;
	
	return true;
}

bool Adventure::WiiTexture::Bind()
{
	if (!textureData)
		return false;
	
	GX_LoadTexObj(&textureObject, GX_TEXMAP0);
	
	return true;
}
