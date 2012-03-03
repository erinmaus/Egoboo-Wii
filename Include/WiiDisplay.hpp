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

#ifndef ADVENTURE_DISPLAY_WII_HPP_
#define ADVENTURE_DISPLAY_WII_HPP_

#include <ogc/gx.h>
#include <ogc/video.h>

#include "IDisplay.hpp"

namespace Adventure
{
	class WiiDisplay : public IDisplay
	{
		public:
			WiiDisplay();
			~WiiDisplay();
			
			// Initialization
			bool SetGraphicsMode(const GraphicsMode& mode);
			bool Initialize();
			
			// Rendering pair
			void Begin();
			void End();
			
			// Graphic object creation methods
			ITexture* CreateTexture();
			
			// Drawing routines
			void DrawModel(const void* positions, const void* normals, const void* materials, const void* uvs, const ModelIndexArray& indexArray, bool compressed);
			
			void SetProjectionMatrix(const Matrix& matrix, ProjectionHint hint);
			void SetModelViewMatrix(const Matrix& matrix);
			
			static const int DefaultGraphicsFifoSize = 65536;
			
			// Model vertex formats
			enum Formats
			{
				// Models
				ModelFormat = GX_VTXFMT0,
				CompressedModelFormat = GX_VTXFMT1,
				
				// Particles
				ParticleFormat = GX_VTXFMT2,
				CompressedParticleFormat = GX_VTXFMT3,
				
				// Sprites
				SpriteFormat = GX_VTXFMT4,
				CompressedSpriteFormat = GX_VTXFMT5
			};
			
		private:
			WiiDisplay(const WiiDisplay& other) { }
			
			GXRModeObj * renderMode;
			
			void * framebuffers[2];
			int framebufferIndex;
			
			void * graphicsFifo;
	};
}

#endif
