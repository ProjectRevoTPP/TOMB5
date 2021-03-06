#include "CALCLARA.H"

#include "SPECIFIC.H"
#include "DRAW.H"
#include "MATHS.H"
#include "LARA.H"
#include "GTEREG.H"

void S_SetupClutAdder(long underwater)
{
	DQB = underwater;
}

void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag)
{
#if 0//Nope
	S_Warn("[DEL_CalcLaraMatrices_Normal_ASM] - Unimplemented!\n");

	mPushMatrix();

	if (flag != 0 && flag != 2)
		mSetTrans(0, 0, 0);
	else
		mTranslateAbsXYZ(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos);

	mRotYXZ(lara_item->pos.y_rot, lara_item->pos.x_rot, lara_item->pos.z_rot);

	if (flag == 2)
	{
		ScaleCurrentMatrix({ -4096, -4096, -4096 });
	}

	mPushMatrix();

	mTranslateXYZ(frame[6], frame[7], frame[8]);
	/**/
	mPopMatrix();
	mPopMatrix();
#endif
}

void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate)
{
	S_Warn("[DEL_CalcLaraMatrices_Interpolated_ASM] - Unimplemented!\n");
}

short* GetBoundsAccurate(struct ITEM_INFO* item)//858F8, 8793C
{
	int rate;
	short* frmptr[2];
	int frac = GetFrames(item, frmptr, &rate);

	if (frac == 0)
		return frmptr[0];

	short* bptr = interpolated_bounds;

	for (int i = 0; i < 6; i++, bptr++, frmptr[0]++, frmptr[1]++)
	{
		*bptr = *frmptr[0] + (*frmptr[1] - *frmptr[0]) * frac / rate;
	}

	return interpolated_bounds;
}

void snaff_current_gte_matrix_V1(MATRIX3D* m)
{
}
