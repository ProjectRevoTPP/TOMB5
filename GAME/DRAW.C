#include "DRAW.H"

#include "CONTROL.H"
#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
#include "DRAWSPKS.H"
#include "SETUP.H"
#include "MATHS.H"
#endif

#include "OBJECTS.H"

#include "SPECIFIC.H"
#include "STYPES.H"
#include "TOMB4FX.H"
#include <stddef.h>
//#include <INLINE_O.H>
#if PSX_VERSION || PSXPC_VERSION || SAT_VERSION
#include "MISC.H"
#endif


short LightningSFXDelay;
struct room_info* room;
short number_rooms;
long* bones;
struct ANIM_STRUCT* anims;
struct RANGE_STRUCT* ranges;
struct CHANGE_STRUCT* changes;
short** meshes;
short* commands;
short* frames;
short* binoculars_mesh_ptr;
short* target_mesh_ptr;
short SkyPos;
short SkyPos2;
int number_draw_rooms;
short draw_rooms[100];
int number_dynamics;
long camera_underwater;
long gfMirrorZPlane;
unsigned short LightningRGBs[3];
unsigned short LightningRGB[3];
short LightningCount;
short LightningRand;
short dLightningRand;
short interpolated_bounds[6];
short* GLOBAL_gunflash_meshptr;
int CurrentRoom;
unsigned char CreditsDone;
short GlobalRoomNumber;
long outside;
long outside_left;
long outside_right;
long outside_top;
long outside_bottom;
short HorizonClip;
struct door_vbuf vbufdoor[4];
short Sback_gun;
short* SRhandPtr;
short* SLhandPtr;

#if PC_VERSION
long GetFrames(struct ITEM_INFO* item/*$a0*/, short* frames[]/*a1*/, int* rate/*$a2*/)//8582C
{
	struct ANIM_STRUCT* anim = &anims[item->anim_number];
	int t3;
	short* t4;

	rate[0] = anim->interpolation;

	t3 = ((item->frame_number - anim->frame_base) / anim->interpolation) * anim->interpolation >> 8;
	t4 = &anim->frame_ptr[t3];

	frames[0] = &anim->frame_ptr[t3];
	frames[1] = &t4[anim->interpolation >> 8];
	if (anim->interpolation == 0)
	{
		return 0;
	}

	t3 = ((item->frame_number - anim->frame_base) / anim->interpolation) * anim->interpolation;

	if (!(anim->frame_end < (t3 + anim->interpolation)))
	{
		return (t3 + anim->interpolation) - anim->interpolation;
	}

	rate[0] = anim->frame_end - anim->interpolation;
	return (item->frame_number - anim->frame_base) / anim->interpolation;
}
#endif

void UpdateSkyLightning()//2C0D0(<), ? (F)
{
	long lp;

	if (LightningCount > 0)
	{
		--LightningCount;

		if ((LightningCount << 16) == 0)
		{
			LightningRand = (GetRandomDraw() & 0x7F) + 400;
			dLightningRand = 0;
		}
		else
		{
			//loc_2C118
			dLightningRand = (GetRandomDraw() & 0x1FF);
			LightningRand = ((dLightningRand - LightningRand) >> 1) + LightningRand;
		}
	}
	else
	{
		//loc_2C148
		if (LightningRand < 4)
		{
			//loc_2C174
			LightningRand = 0;
		}
		else
		{
			LightningRand = LightningRand - (LightningRand >> 2);
		}
	}

	//loc_2C18C
	for (lp = 2; lp >= 0; lp--)
	{
		LightningRGBs[lp] += ((LightningRGBs[lp] * LightningRand) >> 8);
		if ((LightningRGBs[lp] & 0xFFFF) > 255)
		{
			LightningRGBs[lp] = 255;
		}
	}
}

#if PC_VERSION && !PSXPC_TEST
void DrawSkyMesh(short* mesh)
{
	UNIMPLEMENTED();
}
#endif

#if PC_VERSION || PSXPC_TEST

void DrawMoon()
{
	UNIMPLEMENTED();
}

#endif
void DrawGunflashes()//8A924(<) 8C968(<)
{
#ifdef PC_VERSION
	UNIMPLEMENTED();
#else
	long rand;
	long i;
	short* mesh;

	if (!Gunflashes[0].on)
	{
		return;
	}

	mPushMatrix();
	rand = (GetRandomDraw() & 0x1F);
	
	/*SetInventoryLighting(((GetRandomDraw() & 0xF) + 72) | 0x4000,
		((GetRandomDraw() & 0xF) + 72) | 0x4000,
		((GetRandomDraw() & 0xF) + 72) | 0x4000,
		rand << 16 | rand << 8 | rand);*/

	for (i = 0; i < 4; i++)
	{
		if (Gunflashes[i].on)
		{
			mCopyMatrix(&Gunflashes[i].matrix);
			//mRotZ(GetRandomDraw() << 1);
			mesh = meshes[objects[GUN_FLASH].mesh_index];
			//phd_PutPolygons(mesh[0], -1);
			mesh[16] = 0;
		}
	}

	mPopMatrix();
#endif
}

short* GetBestFrame(struct ITEM_INFO* item)// (F)s
{
	short* frm[2];
	int rate;
	const int ret = GetFrames(item, frm, &rate);

	if (ret > (rate >> 1))
		return frm[1];
	else
		return frm[0];
}

void DrawAnimatingItem(struct ITEM_INFO *item)
{
	UNIMPLEMENTED();
}