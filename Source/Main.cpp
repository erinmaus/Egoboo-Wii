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

#include <cmath>
#include <fstream>

#include "Standard.hpp"

#include "DiffuseEffect.hpp"
#include "SpecularEffect.hpp"
#include "ElementArray.hpp"
#include "File.hpp"
#include "FileSystem.hpp"
#include "Image.hpp"
#include "ITexture.hpp"
#include "Matrix.hpp"
#include "Md2Model.hpp"
#include "PooledAllocator.hpp"
#include "Vector3.hpp"
#include "WiiDisplay.hpp"
#include "WiiSystem.hpp"
#include "WiiAllocator.hpp"

#define CHARACTERS_ROW 10
#define CHARACTER_COUNT CHARACTERS_ROW * CHARACTERS_ROW

struct Character
{
	Adventure::IModel* Model;
	Adventure::IModelAnimator* Animator;
	
	Adventure::ITexture* Texture;
};

bool LoadCharacter(Character& character, Adventure::ISystem& system, Adventure::Allocator* element, Adventure::Allocator* scratch)
{
	std::fstream modelStream(system.BuildPath("/Content/Loggy/tris.md2").c_str(), std::ios::in | std::ios::binary);
	Adventure::File modelFile(modelStream, Adventure::File::BigEndian);
	character.Model = Adventure::Md2Model::LoadFromFile(modelFile, element);
	
	if (character.Model == NULL)
	{
		TRACE(DEBUG_GENERAL, "Could not load model");
		
		return false;
	}
	
	character.Animator = character.Model->CreateAnimator();
	
	if (character.Animator == NULL || !character.Animator->Initialize(element))
	{
		TRACE(DEBUG_GENERAL, "Could not create animator");
		
		return false;
	}
	
	std::fstream imageStream(system.BuildPath("/Content/Loggy/tris0.bmp").c_str(), std::ios::in | std::ios::binary);
	Adventure::File imageFile(imageStream, Adventure::File::BigEndian);
	character.Texture = Adventure::Image::LoadBmpFromFile(imageFile, system.GetDisplay(), scratch);
	
	if (character.Texture == NULL)
	{
		TRACE(DEBUG_GENERAL, "Could not load texture");
		
		return false;
	}
	
	return true;
}

int main(int argumentCount, char** arguments)
{
	// Initialize file system services
	Adventure::FileSystem fileSystem;
	
	// Create allocators
	Adventure::WiiAllocator baseAllocator;
	Adventure::PooledAllocator texturePool(&baseAllocator, 32, 0x40000, "texture");
	Adventure::PooledAllocator elementPool(&baseAllocator, 32, 0x40000, "element");
	Adventure::PooledAllocator scratchPool(&baseAllocator, 32, 0x40000, "scratch");
	Adventure::PooledAllocator standardPool(&baseAllocator, 32, 0xFFFF, "standard");
	
	Adventure::StdAllocatorBase::SetBase(&standardPool);
	
	//ASSERT(false);
	
	Adventure::WiiSystem system;
	
	if (!system.Initialize())
	{
		TRACE(DEBUG_GENERAL, "System initialized failed!");
		
		return 1;
	}
	TRACE(DEBUG_GENERAL, "System initialized");
	
	system.SetArguments(argumentCount, (const char**)arguments);
	
	Adventure::IDisplay& display = system.GetDisplay();
	display.SetTextureAllocator(&texturePool);
	
	Character character;
	if (!LoadCharacter(character, system, &elementPool, &scratchPool))
	{
		TRACE(DEBUG_GENERAL, "Could not create Loggy!");
		TRACE(DEBUG_GENERAL, "Element pool usage: %d out of %d", elementPool.GetMemoryUsage(), elementPool.GetAvailableMemory());
		TRACE(DEBUG_GENERAL, "Scratch pool usage: %d", scratchPool.GetMemoryUsage());
		
		return 1;
	}
	
	character.Animator->SetInterval(1.0f / 8.0f);
	ASSERT(character.Animator->SwitchTo("WB"));
	//if (!character.Animator->SwitchTo("WB"))
	//{
		//TRACE(DEBUG_GENERAL, "Could not switch to animation WB");
	//}
	
	Adventure::ModelFrame diffuseFrame[CHARACTER_COUNT], specularFrame[CHARACTER_COUNT];
	//Adventure::ModelFrame diffuseFrame[CHARACTER_COUNT];
	
	for (int i = 0; i < CHARACTER_COUNT; i++)
	{
		if (!character.Animator->InitializeFrame(diffuseFrame[i], &elementPool))
		{
			TRACE(DEBUG_GENERAL, "Could not intialize diffuse frame %d", i);
			
			return 1;
		}
		TRACE(DEBUG_GENERAL, "Initialized diffuse frame %d", i);
		
		if (!character.Animator->InitializeFrame(specularFrame[i], &elementPool))
		{
			TRACE(DEBUG_GENERAL, "Could not initialize specular frame %d", i);
			
			return 1;
		}
		TRACE(DEBUG_GENERAL, "Initialize specular frame %d", i);
	}
	
	TRACE(DEBUG_GENERAL, "Memory usage for standard pool: %ld bytes", standardPool.GetMemoryUsage());
	TRACE(DEBUG_GENERAL, "Memory usage for texture pool: %ld bytes", texturePool.GetMemoryUsage());
	TRACE(DEBUG_GENERAL, "Memory usage for element pool: %ld bytes", elementPool.GetMemoryUsage());
	TRACE(DEBUG_GENERAL, "Memory usage for scratch pool: %ld bytes", scratchPool.GetMemoryUsage());
	
	Adventure::GraphicsMode mode = display.GetGraphicsMode();
	Adventure::Matrix projection = Adventure::Matrix::Perspective(M_PI * 0.25f, (float)mode.Width / (float)mode.Height, 1.0f, 1000.0f);
	float rotation = 0.0f;
	int frames = 120;
	profile_int_t bestFrame = (profile_int_t)-1;
	
	PROFILE_BEGIN(1);
	
	while(frames--)
	{
		rotation += 0.005f;
		
		// Calculate camera
		Adventure::Vector3 eye = Adventure::Vector3(cos(rotation * M_PI * 2) * 256.0f, 128.0f, sin(rotation * M_PI * 2) * 256.0f);
		Adventure::Vector3 target = Adventure::Vector3(0.0f, -32.0f, 0.0f);
		Adventure::Matrix view = Adventure::Matrix::LookAt(eye, target, Adventure::Vector3(0.0f, 1.0f, 0.0f));
		Adventure::Matrix x = Adventure::Matrix::Rotate(Adventure::Vector3(1.0f, 0.0f, 0.0f), M_PI * 0.5f);
		Adventure::Matrix y = Adventure::Matrix::Rotate(Adventure::Vector3(0.0f, 1.0f, 0.0f), M_PI * 1.5f);
		Adventure::Matrix modelRotation = y * x;
		
		character.Animator->UpdateAnimation(1.0f / 60.0f);
		character.Animator->Render();
		
		display.Begin();
		PROFILE_BEGIN(2);
		for (int i = 0; i < CHARACTERS_ROW; i++)
		{
			for (int j = 0; j < CHARACTERS_ROW; j++)
			{
				float posX = i * 32 - CHARACTERS_ROW / 2 * 32;
				float posZ = j * 32 - CHARACTERS_ROW / 2 * 32;
				int index = j * CHARACTERS_ROW + i;
				Adventure::Matrix world = Adventure::Matrix::Translate(Adventure::Vector3(posX, 0.0f, posZ)) * modelRotation;
				
				// Create diffuse light
				Adventure::DiffuseEffect diffuseLight;
				diffuseLight.SetWorld(world);
				diffuseLight.SetCameraPosition(eye - target);
				diffuseLight.SetPosition(Adventure::Vector3(0.0f, 8.0f, -16.0f));
				diffuseLight.SetColor(Adventure::Color(1.0f, 1.0f, 1.0f));
				diffuseLight.SetAttenuation(Adventure::LightAttenuation::FromRadius(128.0f));
				
				// Create specular light
				Adventure::SpecularEffect specularLight;
				specularLight.SetWorld(world);
				specularLight.SetCameraPosition(eye - target);
				specularLight.SetPosition(Adventure::Vector3(0.0f, 16.0f, 0.0f));
				specularLight.SetColor(Adventure::Color(1.0f, 1.0f, 1.0f));
				specularLight.SetAttenuation(Adventure::LightAttenuation::FromRadius(128.0f));
				specularLight.SetPower(0.0f);
				
				display.SetProjectionMatrix(projection);
				display.SetModelViewMatrix(view * world);
				character.Texture->Bind();
				
				display.SetLightingMode(Adventure::IDisplay::Diffuse);
				character.Animator->BuildCurrentFrame(diffuseFrame[index], diffuseLight);
				diffuseFrame[index].Draw(display);
				
				display.SetLightingMode(Adventure::IDisplay::Specular);
				character.Animator->BuildCurrentFrame(specularFrame[index], specularLight);
				specularFrame[index].Draw(display);
			}
		}
		PROFILE_END(2);
		display.End();
		
		profile_int_t previous;
		PROFILE_GET_DIFFERENCE(2, previous);
		
		if (previous < bestFrame)
			bestFrame = previous;
	}
	
	PROFILE_END(1);
	
	profile_int_t elapsed;
	PROFILE_GET_DIFFERENCE(1, elapsed);
	
	FILE* output = fopen("sd:/Profile.txt", "w");
	fprintf(output, "Profile run: %llu milliseconds\n", elapsed);
	fflush(output);
	
	fprintf(output, "Average profile frame length: %f milliseconds\n", elapsed / 120.0f);
	fflush(output);
	
	fprintf(output, "Best draw time: %llu milliseconds\n", bestFrame);
	fflush(output);
	
	fprintf(output, "Element pool memory usage: %lu of %lu (%f%%)\n",
		elementPool.GetMemoryUsage(),
		elementPool.GetAvailableMemory(),
		(float)elementPool.GetMemoryUsage() / elementPool.GetAvailableMemory() * 100);
	fflush(output);
	
	fprintf(output, "Texture pool memory usage: %lu of %lu (%f%%)\n",
		texturePool.GetMemoryUsage(),
		texturePool.GetAvailableMemory(),
		(float)texturePool.GetMemoryUsage() / texturePool.GetAvailableMemory() * 100);
	fflush(output);
	
	fprintf(output, "Scratch pool memory usage: %lu of %lu (%f%%)\n",
		scratchPool.GetMemoryUsage(),
		scratchPool.GetAvailableMemory(),
		(float)scratchPool.GetMemoryUsage() / scratchPool.GetAvailableMemory() * 100);
	fflush(output);
	
	fprintf(output, "Standard pool memory usage: %lu of %lu (%f%%)\n",
		standardPool.GetMemoryUsage(),
		standardPool.GetAvailableMemory(),
		(float)standardPool.GetMemoryUsage() / standardPool.GetAvailableMemory() * 100);
	fflush(output);
	
	fclose(output);
	
	return 0;
}
