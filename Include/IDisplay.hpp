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

#ifndef ADVENTURE_DISPLAY_INTERFACE_HPP_
#define ADVENTURE_DISPLAY_INTERFACE_HPP_

#include "ElementArray.hpp"

namespace Adventure
{
	// Forward declarations
	class ITexture;
	struct Matrix;
	
	struct GraphicsMode
	{
		public:
			GraphicsMode(int width, int height, bool fullscreen = false)
			{
				Width = width;
				Height = height;
				IsFullscreen = fullscreen;
			}
			
			GraphicsMode(const GraphicsMode& other)
			{
				Width = other.Width;
				Height = other.Height;
				IsFullscreen = other.IsFullscreen;
			}
			
			// Members
			int Width;
			int Height;
			bool IsFullscreen;
	};
	
	class IDisplay
	{
		public:
			virtual ~IDisplay() { };
			
			// Sets a preferred graphics mode.
			// Returns false if the mode was failed to set, true otherwise
			// Note: This method returns true if the mode was ignored (e.g., on the Wii).
			virtual bool SetGraphicsMode(const GraphicsMode& mode) = 0;
			
			// Gets the actual graphics mode
			virtual GraphicsMode GetGraphicsMode() const = 0;
			
			// Initializes the display to a default state
			virtual bool Initialize() = 0;
			
			// Prepares the display to render a scene.
			// This should be called once per frame, right before drawing.
			virtual void Begin() = 0;
			
			// Presents the display to the screen.
			// As with Begin(), this should only be called once per frame, right after drawing.
			virtual void End() = 0;
			
			// Creates a texture object
			virtual ITexture* CreateTexture() = 0;
			
			// An enumeration that provides the value type of an index
			enum IndexSize
			{
				// unsigned short
				LargeIndex,
				
				// unsigned char
				SmallIndex
			};
			
			// Draws a model
			virtual void DrawModel(const void* positions, const void* normals, const void* materials, const void* uvs, const ModelIndexArray& indexArray, bool compressed = true) = 0;
			
			// An enumeration that provides a hint as to the projection matrix type
			enum ProjectionHint
			{
				Ortho,
				Perspective
			};
			
			// Sets the projection matrix
			virtual void SetProjectionMatrix(const Matrix& matrix, ProjectionHint hint = Perspective) = 0;
			
			// Sets the model view matrix
			virtual void SetModelViewMatrix(const Matrix& matrix) = 0;
	};
}

#endif
