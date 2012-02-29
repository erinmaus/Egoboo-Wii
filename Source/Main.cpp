#include <gccore.h>

void InitializeConsole()
{
	VIDEO_Init();
	
	GXRModeObj * mode = VIDEO_GetPreferredMode(NULL);
	void * frameBuffer = MEM_K0_TO_K1(SYS_AllocateFramebufer(mode));
	
	CON_InitEx(mode, 32, 32, mode->xfbHeight, mode->fbWidth * VI_DISPLAY_PIX_SZ);
	
	VIDEO_Configure(mode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);

	VIDEO_Flush();

	VIDEO_WaitVSync();
	
	if(rmode->viTVMode & VI_NON_INTERLACE)
		VIDEO_WaitVSync();
}

int main(int argumentCount, char ** arguments)
{
	InitializeConsole();
}