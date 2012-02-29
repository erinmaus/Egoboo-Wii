#ifndef ADVENTURE_DISPLAY_WII_HPP_
#define ADVENTURE_DISPLAY_WII_HPP_

#include <ogc/gx.h>
#include <ogc/video.h>

namespace Adventure
{
	class WiiDisplay
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
			
			static const DefaultGraphicsFifoSize = 65536;
			
			// Model vertex formats
			enum Formats
			{
				// Models
				ModelFormat = GX_VTXFMT0,
				ModelCompressedFormat = GX_VTXFMT1,
				
				// Particles
				ParticleFormat = GX_VTXFMT2,
				ParticleCompressedFormat = GX_VTXFMT3,
				
				// Sprites
				SpriteFormat = GX_VTXFMT4,
				SpriteCompressedFormat = GX_VTXFMT5
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
