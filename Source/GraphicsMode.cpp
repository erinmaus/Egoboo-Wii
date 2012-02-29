#include "GraphicsMode.hpp"

Adventure::GraphicsMode::GraphicsMode(int width, int height, bool fullscreen)
{
	Width = width;
	Height = height;
	IsFullscreen = fullscreen;
}

Adventure::GraphicsMode::GraphicsMode(const GraphicsMode& other)
{
	Width = other.Width;
	Height = other.Height;
	IsFullscreen = other.IsFullscreen;
}
