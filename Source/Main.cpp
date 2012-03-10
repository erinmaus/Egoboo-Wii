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

#include "DiffuseEffect.hpp"
#include "SpecularEffect.hpp"
#include "ElementArray.hpp"
#include "File.hpp"
#include "Image.hpp"
#include "ITexture.hpp"
#include "Matrix.hpp"
#include "Md2Model.hpp"
#include "PooledAllocator.hpp"
#include "Vector3.hpp"
#include "WiiDisplay.hpp"
#include "WiiSystem.hpp"
#include "WiiAllocator.hpp"

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
	Adventure::WiiSystem system;
	Adventure::WiiAllocator baseAllocator;
	Adventure::PooledAllocator texturePool(&baseAllocator, 32, 0x40000);
	Adventure::PooledAllocator elementPool(&baseAllocator, 32, 0x40000);
	Adventure::PooledAllocator scratchPool(&baseAllocator, 32, 0x40000);
	
	system.SetArguments(argumentCount, (const char**)arguments);
	
	if (!system.Initialize())
	{
		TRACE(DEBUG_GENERAL, "System initialized failed!");
		
		return 1;
	}
	TRACE(DEBUG_GENERAL, "System initialized");
	
	Adventure::IDisplay& display = system.GetDisplay();
	display.SetTextureAllocator(&texturePool);
	
	Character character;
	if (!LoadCharacter(character, system, &elementPool, &scratchPool))
	{
		TRACE(DEBUG_GENERAL, "Could not create Loggy!");
		TRACE(DEBUG_GENERAL, "Element pool usage: %d out of %d", elementPool.GetMemoryUsage(), elementPool.GetSize() * elementPool.GetBlockSize());
		TRACE(DEBUG_GENERAL, "Scratch pool usage: %d", scratchPool.GetMemoryUsage());
		
		return 1;
	}
	
	character.Animator->SetInterval(1.0f / 8.0f);
	if (!character.Animator->SwitchTo("DA"))
	{
		TRACE(DEBUG_GENERAL, "Could not switch to animation DA");
	}
	
	Adventure::ModelFrame diffuseFrame, specularFrame;
	if (!character.Animator->InitializeFrame(diffuseFrame, &elementPool))
	{
		TRACE(DEBUG_GENERAL, "Could not intialize diffuse frame");
		
		return 1;
	}
	
	if (!character.Animator->InitializeFrame(specularFrame, &elementPool))
	{
		TRACE(DEBUG_GENERAL, "Could not initialize specular frame");
		
		return 1;
	}
	
	TRACE(DEBUG_GENERAL, "Memory usage for texture pool: %ld bytes", texturePool.GetMemoryUsage());
	TRACE(DEBUG_GENERAL, "Memory usage for element pool: %ld bytes", elementPool.GetMemoryUsage());
	TRACE(DEBUG_GENERAL, "Memory usage for scratch pool: %ld bytes", scratchPool.GetMemoryUsage());
	
	Adventure::GraphicsMode mode = display.GetGraphicsMode();
	Adventure::Matrix projection = Adventure::Matrix::Perspective(M_PI * 0.25f, (float)mode.Width / (float)mode.Height, 1.0f, 1000.0f);
	Adventure::Matrix camera = Adventure::Matrix::LookAt(Adventure::Vector3(0.0f, 8.0f, -64.0f), Adventure::Vector3(0.0f, 8.0f, 0.0f), Adventure::Vector3(0.0f, 1.0f, 0.0f));
	float rotation = 0.0f;
	
	while (true)
	{
		rotation += 0.005f;
		
		// Calculate camera
		Adventure::Vector3 eye = Adventure::Vector3(cos(rotation * M_PI * 2) * 64.0f, 8.0f, sin(rotation * M_PI * 2) * 64.0f);
		Adventure::Vector3 target = Adventure::Vector3(0.0f, 8.0f, 0.0f);
		Adventure::Matrix view = Adventure::Matrix::LookAt(eye, target, Adventure::Vector3(0.0f, 1.0f, 0.0f));
		Adventure::Matrix x = Adventure::Matrix::Rotate(Adventure::Vector3(1.0f, 0.0f, 0.0f), M_PI * 0.5f);
		Adventure::Matrix y = Adventure::Matrix::Rotate(Adventure::Vector3(0.0f, 1.0f, 0.0f), M_PI * 1.5f);
		Adventure::Matrix world = y * x;
		
		character.Animator->UpdateAnimation(1.0f / 60.0f);
		character.Animator->Render();
		
		// Create diffuse light
		Adventure::DiffuseEffect diffuseLight;
		diffuseLight.SetWorld(world);
		diffuseLight.SetCameraPosition(eye - target);
		diffuseLight.SetPosition(Adventure::Vector3(0.0f, 8.0f, -16.0f));
		diffuseLight.SetColor(Adventure::Color(1.0f, 1.0f, 1.0f));
		diffuseLight.SetAttenuation(Adventure::LightAttenuation::FromRadius(256.0f));
		
		// Create specular light
		Adventure::SpecularEffect specularLight;
		specularLight.SetWorld(world);
		specularLight.SetCameraPosition(eye - target);
		specularLight.SetPosition(Adventure::Vector3(0.0f, 16.0f, -24.0f));
		specularLight.SetColor(Adventure::Color(1.0f, 1.0f, 1.0f));
		specularLight.SetAttenuation(Adventure::LightAttenuation::FromRadius(128.0f));
		specularLight.SetPower(0.0f);
		
		display.Begin();
		
		display.SetProjectionMatrix(projection);
		display.SetModelViewMatrix(view * world);
		character.Texture->Bind();
		
		display.SetLightingMode(Adventure::IDisplay::Diffuse);
		character.Animator->BuildCurrentFrame(diffuseFrame, diffuseLight);
		diffuseFrame.Draw(display);
		
		display.SetLightingMode(Adventure::IDisplay::Specular);
		character.Animator->BuildCurrentFrame(specularFrame, specularLight);
		//specularFrame.Draw(display);
				
		display.End();
	}
	
	return 0;
}
