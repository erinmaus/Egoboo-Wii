#include <cstdlib>
#include <cstring>
#include <malloc.h>
#include <ogc/system.h>

#include "WiiDisplay.hpp"

Adventure::WiiDisplay::WiiDisplay()
{
	renderMode = NULL;
	
	framebuffers[0] = NULL;
	framebuffers[1] = NULL;
	framebufferIndex = 0;
	
	graphicsFifo = 0;
}

Adventure::WiiDisplay::~WiiDisplay()
{
}

bool Adventure::WiiDisplay::SetGraphicsMode(const GraphicsMode& mode)
{
	// There is only one graphics mode on the Wii, which is set by the console itself
	return true;
}

bool Adventure::WiiDisplay::Initialize()
{
	VIDEO_Init();
	
	renderMode = VIDEO_GetPreferredMode(NULL);
	
	framebuffers[0] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(renderMode));
	framebuffers[1] = MEM_K0_TO_K1(SYS_AllocateFramebuffer(renderMode));
	
	VIDEO_Configure(renderMode);
	VIDEO_SetNextFramebuffer(framebuffers[framebufferIndex]);
	VIDEO_SetBlack(false);
	VIDEO_Flush();
	
	VIDEO_WaitVSync();
	
	if (renderMode->viTVMode & VI_NON_INTERLACE)
		VIDEO_WaitVSync();
	
	graphicsFifo = memalign(32, DefaultGraphicsFifoSize);
	memset(graphicsFifo, 0, DefaultGraphicsFifoSize);
	
	GX_Init(graphicsFifo, DefaultGraphicsFifoSize);
	
	// Routine GX initialization
	GXColor backgroundColor = { 0, 0, 0, 0xFF };
	GX_SetCopyClear(backgroundColor, 0x00FFFFFF);
	
	int yScale = GX_GetYScaleFactor(renderMode->efbHeight, renderMode->xfbHeight);
	int externalFramebufferHeight = GX_SetDispCopyYScale(yScale);
	
	GX_SetScissor(0, 0, renderMode->fbWidth, renderMode->efbHeight);
	
	GX_SetDispCopySrc(0, 0, renderMode->fbWidth, renderMode->efbHeight);
	GX_SetDispCopyDst(renderMode->fbWidth, externalFramebufferHeight);
	GX_SetCopyFilter(renderMode->aa, renderMode->sample_pattern, GX_TRUE, renderMode->vfilter);
	
	bool halfAspect = (renderMode->viHeight == renderMode->xfbHeight * 2);
	GX_SetFieldMode(renderMode->field_rendering, halfAspect ? GX_ENABLE : GX_DISABLE);
	
	if (renderMode->aa)
		GX_SetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
	else
		GX_SetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
		
	// Prepare the three vertex format types
	GX_ClearVtxDesc();
	
	GX_SetVtxAttrFmt(ModelFormat, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(ModelFormat, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(ModelFormat, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(ModelFormat, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	
	GX_SetVtxAttrFmt(ModelCompressedFormat, GX_VA_POS, GX_POS_XYZ, GX_S16, 7);
	GX_SetVtxAttrFmt(ModelCompressedFormat, GX_VA_NRM, GX_NRM_XYZ, GX_S16, 14);
	GX_SetVtxAttrFmt(ModelCompressedFormat, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(ModelCompressedFormat, GX_VA_TEX0, GX_TEX_ST, GX_S16, 7);
	
	GX_SetVtxAttrFmt(ParticleFormat, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GX_SetVtxAttrFmt(ParticleFormat, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(ParticleFormat, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	
	GX_SetVtxAttrFmt(ParticleCompressedFormat, GX_VA_POS, GX_POS_XYZ, GX_S16, 7);
	GX_SetVtxAttrFmt(ParticleCompressedFormat, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(ParticleCompressedFormat, GX_VA_TEX0, GX_TEX_ST, GX_S16, 7);
	
	GX_SetVtxAttrFmt(SpriteFormat, GX_VA_POS, GX_POS_XY, GX_F32, 0);
	GX_SetVtxAttrFmt(SpriteFormat, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(SpriteFormat, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	
	GX_SetVtxAttrFmt(SpriteCompressedFormat, GX_VA_POS, GX_POS_XY, GX_S16, 7);
	GX_SetVtxAttrFmt(SpriteCompressedFormat, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GX_SetVtxAttrFmt(SpriteCompressedFormat, GX_VA_TEX0, GX_TEX_ST, GX_S16, 7);
	
	return true;
}

void Adventure::WiiDisplay::Begin()
{
	if (renderMode->field_rendering)
		GX_SetViewportJitter(0.0f, 0.0f, renderMode->fbWidth, renderMode->efbHeight, 0.0f, 1.0f, VIDEO_GetNextField());
	else
		GX_SetViewport(0.0f, 0.0f, renderMode->fbWidth, renderMode->efbHeight, 0.0f, 1.0f);
}

void Adventure::WiiDisplay::End()
{
	// Swap the buffers
	framebufferIndex ^= 1;
	
	// Copy the scene to the provided framebuffer
	GX_CopyDisp(framebuffers[framebufferIndex], GX_TRUE);
	GX_DrawDone();
	
	// Tell the video subsystem to use the provided buffer for the next frame
	VIDEO_SetNextFramebuffer(framebuffers[framebufferIndex]);
	VIDEO_Flush();
	VIDEO_WaitVSync();
}
