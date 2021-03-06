#ifndef EMULATOR_GLOBALS_H
#define EMULATOR_GLOBALS_H

#include "EMULATOR.H"

#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0
#endif

#include <stdint.h>

#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

extern int(*printf_)(const char * format, ...);

#define eprintf(fmt, ...) printf_("[EMU] " fmt, ##__VA_ARGS__)
#define eprinterr(fmt, ...) eprintf("[%s] - " fmt, FUNCNAME, ##__VA_ARGS__);

#define UNIMPLEMENTED() eprinterr("Unimplemented!\n");

extern GLuint nullWhiteTexture;
extern GLuint vramFrameBuffer;
extern int screenWidth;
extern int screenHeight;
extern int windowWidth;
extern int windowHeight;
extern uint32_t DMAControlRegister;
extern int assetsLoaded;
extern unsigned short GlobalTpageTexture;
#if defined(OGLES) || defined(CORE_PROF_3_3)
extern GLuint g_defaultShaderProgram;
#endif
extern GLint g_defaultFBO;


struct CachedTexture
{
	GLuint textureID;
	unsigned short tpage;
	unsigned short clut;
	unsigned int lastAccess;
};

extern struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

#endif