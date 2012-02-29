#ifndef ADVENTURE_DISPLAY_INTERFACE_HPP_
#define ADVENTURE_DISPLAY_INTERFACE_HPP_

namespace Adventure
{
	struct GraphicsMode
	{
		public:
			GraphicsMode(int width, int height, bool fullscreen = false);
			GraphicsMode(const GraphicsMode& other);
			
			// Members
			int Width;
			int Height;
			bool IsFullscreen;
	};
	
	class IDisplay
	{
		public:
			virtual ~IDisplay() = 0;
			
			// Sets a preferred graphics mode.
			// Returns false if the mode was failed to set, true otherwise
			// Note: This method returns true if the mode was ignored (e.g., on the Wii).
			virtual bool SetGraphicsMode(const GraphicsMode& mode) = 0;
			
			// Initializes the display to a default state
			virtual bool Initialize() = 0;
			
			// Prepares the display to render a scene.
			// This should be called once per frame, right before drawing.
			void Begin();
			
			// Presents the display to the screen.
			// As with Begin(), this should only be called once per frame, right after drawing.
			void End();
	};
}

#endif
