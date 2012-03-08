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

#ifndef ADVENTURE_MD2_MODEL_HPP_
#define ADVENTURE_MD2_MODEL_HPP_

#include "IModel.hpp"
#include "IModelAnimator.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

#include <map>
#include <string>

namespace Adventure
{
	class File;
	class Allocator;
	
	struct Md2Vertex
	{
		typedef unsigned char Element;
		
		Element X;
		Element Y;
		Element Z;
		
		Element Normal;
	};
	
	struct Md2TexCoord
	{
		typedef short Element;
		
		Element U;
		Element V;
	};
	
	struct Md2Frame
	{
		Vector3 Scale;
		Vector3 Translation;
		std::string Name;
		
		Md2Vertex* Vertices;
	};
	
	struct Md2Triangle
	{
		typedef unsigned short Index;
		
		Index Vertex[3];
		Index TexCoord[3];
	};
	
	struct Md2CacheVertex
	{
		Vector3 Position;
		Vector3 Normal;
	};
	
	struct Md2Normal
	{
		float X;
		float Y;
		float Z;
	};
	
	class Md2Model : public IModel
	{
		public:
			~Md2Model();
			
			IModelAnimator* CreateAnimator();
			void DestroyAnimator(IModelAnimator* animator);
			
			inline const Md2TexCoord* GetTexCoords() const 
			{
				return texCoords;
			}
			
			inline int GetTexCoordCount() const
			{
				return texCoordCount;
			}
			
			inline const Md2Triangle* GetTriangles() const
			{
				return triangles;
			}
			
			inline int GetTriangleCount() const
			{
				return triangleCount;
			}
			
			inline const Md2Frame* GetFrames() const
			{
				return frames;
			}
			
			inline int GetFrameCount() const
			{
				return frameCount;
			}
			
			inline const Vector2& GetInverseTexCoordScale() const
			{ 
				return inverseTexCoordScale;
			}
			
			inline int GetPositionCount() const
			{
				return vertexCount;
			}
			
			static Md2Model* LoadFromFile(File& file, Allocator* allocator);
		
		private:
			Md2Model();
			Md2Model(const Md2Model& other);
			
			Md2TexCoord* texCoords;
			int texCoordCount;
			
			Md2Triangle* triangles;
			int triangleCount;
			
			Md2Frame* frames;
			int frameCount;
			
			int vertexCount;
			Vector2 inverseTexCoordScale;
			
			Allocator* allocator;
	};
	
	class Md2Animator : public IModelAnimator
	{
		public:
			explicit Md2Animator(Md2Model* model);
			~Md2Animator();
			
			bool Initialize(Allocator* allocator);
			
			bool GetAnimation(const std::string& name, Animation& animation) const;
			
			void SetInterval(float newInterval);
			void UpdateAnimation(float delta);
			
			bool SwitchTo(const std::string& name);
			
			bool Render();
			ModelFrame* GetCurrentFrame();
			
			Matrix GetGrip(const std::string& name) const;
		
		private:
			std::map<std::string, Animation> animations;
			bool initialized;
			Allocator* allocator;
			Md2Model* model;
			
			Md2CacheVertex* vertexCache;
			ModelFrame frame;
			
			float interval;
			float currentDelta;
			
			int currentFrame, nextFrame;
			Animation currentAnimation;
	};
}

#endif
