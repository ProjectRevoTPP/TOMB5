#include "LIBGTE.H"
#include "EMULATOR_GLOBALS.H"

GTERegisters gteRegs;

#define GTE_SF(op) ((op >> 19) & 1)
#define GTE_MX(op) ((op >> 17) & 3)
#define GTE_V(op) ((op >> 15) & 3)
#define GTE_CV(op) ((op >> 13) & 3)
#define GTE_LM(op) ((op >> 10) & 1)
#define GTE_FUNCT(op) (op & 63)

#define gteop(code) (code & 0x1ffffff)

/* Data Registers mtc2 mfc2 */
#define VX0  (gteRegs.CP2D.p[ 0 ].sw.l)
#define VY0  (gteRegs.CP2D.p[ 0 ].sw.h)
#define VZ0  (gteRegs.CP2D.p[ 1 ].sw.l)
#define VX1  (gteRegs.CP2D.p[ 2 ].w.l)
#define VY1  (gteRegs.CP2D.p[ 2 ].w.h)
#define VZ1  (gteRegs.CP2D.p[ 3 ].w.l)
#define VX2  (gteRegs.CP2D.p[ 4 ].w.l)
#define VY2  (gteRegs.CP2D.p[ 4 ].w.h)
#define VZ2  (gteRegs.CP2D.p[ 5 ].w.l)
#define R    (gteRegs.CP2D.p[ 6 ].b.l)
#define G    (gteRegs.CP2D.p[ 6 ].b.h)
#define B    (gteRegs.CP2D.p[ 6 ].b.h2)
#define CODE (gteRegs.CP2D.p[ 6 ].b.h3)
#define OTZ  (gteRegs.CP2D.p[ 7 ].w.l)
#define IR0  (gteRegs.CP2D.p[ 8 ].sw.l)
#define IR1  (gteRegs.CP2D.p[ 9 ].sw.l)
#define IR2  (gteRegs.CP2D.p[ 10 ].sw.l)
#define IR3  (gteRegs.CP2D.p[ 11 ].sw.l)
#define SXY0 (gteRegs.CP2D.p[ 12 ].d)
#define SX0  (gteRegs.CP2D.p[ 12 ].sw.l)
#define SY0  (gteRegs.CP2D.p[ 12 ].sw.h)
#define SXY1 (gteRegs.CP2D.p[ 13 ].d)
#define SX1  (gteRegs.CP2D.p[ 13 ].sw.l)
#define SY1  (gteRegs.CP2D.p[ 13 ].sw.h)
#define SXY2 (gteRegs.CP2D.p[ 14 ].d)
#define SX2  (gteRegs.CP2D.p[ 14 ].sw.l)
#define SY2  (gteRegs.CP2D.p[ 14 ].sw.h)
#define SXYP (gteRegs.CP2D.p[ 15 ].d)
#define SXP  (gteRegs.CP2D.p[ 15 ].sw.l)
#define SYP  (gteRegs.CP2D.p[ 15 ].sw.h)
#define SZ0  (gteRegs.CP2D.p[ 16 ].w.l)
#define SZ1  (gteRegs.CP2D.p[ 17 ].w.l)
#define SZ2  (gteRegs.CP2D.p[ 18 ].w.l)
#define SZ3  (gteRegs.CP2D.p[ 19 ].w.l)
#define RGB0 (gteRegs.CP2D.p[ 20 ].d)
#define R0   (gteRegs.CP2D.p[ 20 ].b.l)
#define G0   (gteRegs.CP2D.p[ 20 ].b.h)
#define B0   (gteRegs.CP2D.p[ 20 ].b.h2)
#define CD0  (gteRegs.CP2D.p[ 20 ].b.h3)
#define RGB1 (gteRegs.CP2D.p[ 21 ].d)
#define R1   (gteRegs.CP2D.p[ 21 ].b.l)
#define G1   (gteRegs.CP2D.p[ 21 ].b.h)
#define B1   (gteRegs.CP2D.p[ 21 ].b.h2)
#define CD1  (gteRegs.CP2D.p[ 21 ].b.h3)
#define RGB2 (gteRegs.CP2D.p[ 22 ].d)
#define R2   (gteRegs.CP2D.p[ 22 ].b.l)
#define G2   (gteRegs.CP2D.p[ 22 ].b.h)
#define B2   (gteRegs.CP2D.p[ 22 ].b.h2)
#define CD2  (gteRegs.CP2D.p[ 22 ].b.h3)
#define RES1 (gteRegs.CP2D.p[ 23 ].d)
#define MAC0 (gteRegs.CP2D.p[ 24 ].sd)
#define MAC1 (gteRegs.CP2D.p[ 25 ].sd)
#define MAC2 (gteRegs.CP2D.p[ 26 ].sd)
#define MAC3 (gteRegs.CP2D.p[ 27 ].sd)
#define IRGB (gteRegs.CP2D.p[ 28 ].d)
#define ORGB (gteRegs.CP2D.p[ 29 ].d)
#define LZCS (gteRegs.CP2D.p[ 30 ].d)
#define LZCR (gteRegs.CP2D.p[ 31 ].d)

/* Control Registers ctc2 cfc2*/
#define R11 (gteRegs.CP2C.p[ 0 ].sw.l)
#define R12 (gteRegs.CP2C.p[ 0 ].sw.h)
#define R13 (gteRegs.CP2C.p[ 1 ].sw.l)
#define R21 (gteRegs.CP2C.p[ 1 ].sw.h)
#define R22 (gteRegs.CP2C.p[ 2 ].sw.l)
#define R23 (gteRegs.CP2C.p[ 2 ].sw.h)
#define R31 (gteRegs.CP2C.p[ 3 ].sw.l)
#define R32 (gteRegs.CP2C.p[ 3 ].sw.h)
#define R33 (gteRegs.CP2C.p[ 4 ].sw.l)
#define TRX (gteRegs.CP2C.p[ 5 ].sd)
#define TRY (gteRegs.CP2C.p[ 6 ].sd)
#define TRZ (gteRegs.CP2C.p[ 7 ].sd)
#define L11 (gteRegs.CP2C.p[ 8 ].sw.l)
#define L12 (gteRegs.CP2C.p[ 8 ].sw.h)
#define L13 (gteRegs.CP2C.p[ 9 ].sw.l)
#define L21 (gteRegs.CP2C.p[ 9 ].sw.h)
#define L22 (gteRegs.CP2C.p[ 10 ].sw.l)
#define L23 (gteRegs.CP2C.p[ 10 ].sw.h)
#define L31 (gteRegs.CP2C.p[ 11 ].sw.l)
#define L32 (gteRegs.CP2C.p[ 11 ].sw.h)
#define L33 (gteRegs.CP2C.p[ 12 ].sw.l)
#define RBK (gteRegs.CP2C.p[ 13 ].sd)
#define GBK (gteRegs.CP2C.p[ 14 ].sd)
#define BBK (gteRegs.CP2C.p[ 15 ].sd)
#define LR1 (gteRegs.CP2C.p[ 16 ].sw.l)
#define LR2 (gteRegs.CP2C.p[ 16 ].sw.h)
#define LR3 (gteRegs.CP2C.p[ 17 ].sw.l)
#define LG1 (gteRegs.CP2C.p[ 17 ].sw.h)
#define LG2 (gteRegs.CP2C.p[ 18 ].sw.l)
#define LG3 (gteRegs.CP2C.p[ 18 ].sw.h)
#define LB1 (gteRegs.CP2C.p[ 19 ].sw.l)
#define LB2 (gteRegs.CP2C.p[ 19 ].sw.h)
#define LB3 (gteRegs.CP2C.p[ 20 ].sw.l)
#define RFC (gteRegs.CP2C.p[ 21 ].sd)
#define GFC (gteRegs.CP2C.p[ 22 ].sd)
#define BFC (gteRegs.CP2C.p[ 23 ].sd)
#define OFX (gteRegs.CP2C.p[ 24 ].sd)
#define OFY (gteRegs.CP2C.p[ 25 ].sd)
#define H   (gteRegs.CP2C.p[ 26 ].sw.l)
#define DQA (gteRegs.CP2C.p[ 27 ].sw.l)
#define DQB (gteRegs.CP2C.p[ 28 ].sd)
#define ZSF3 (gteRegs.CP2C.p[ 29 ].sw.l)
#define ZSF4 (gteRegs.CP2C.p[ 30 ].sw.l)
#define FLAG (gteRegs.CP2C.p[ 31 ].d)

#define VX(n) (n < 3 ? gteRegs.CP2D.p[ n << 1 ].sw.l : IR1)
#define VY(n) (n < 3 ? gteRegs.CP2D.p[ n << 1 ].sw.h : IR2)
#define VZ(n) (n < 3 ? gteRegs.CP2D.p[ (n << 1) + 1 ].sw.l : IR3)
#define MX11(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) ].sw.l : -R << 4)
#define MX12(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) ].sw.h : R << 4)
#define MX13(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 1 ].sw.l : IR0)
#define MX21(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 1 ].sw.h : R13)
#define MX22(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 2 ].sw.l : R13)
#define MX23(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 2 ].sw.h : R13)
#define MX31(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 3 ].sw.l : R22)
#define MX32(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 3 ].sw.h : R22)
#define MX33(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 4 ].sw.l : R22)
#define CV1(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 5 ].sd : 0)
#define CV2(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 6 ].sd : 0)
#define CV3(n) (n < 3 ? gteRegs.CP2C.p[ (n << 3) + 7 ].sd : 0)

void InitGeom()
{
	VX0 = 0;
	VY0 = 0;
	VZ0 = 0;
	VX1 = 0;
	VY1 = 0;
	VZ1 = 0;
	VX2 = 0;
	VY2 = 0;
	VZ2 = 0;
	R = 0;
	G = 0;
	B = 0;
	CODE = 0;
	OTZ = 0;
	IR0 = 0;
	IR1 = 0;
	IR2 = 0;
	IR3 = 0;
	SXY0 = 0;
	SX0 = 0;
	SY0 = 0;
	SXY1 = 0;
	SX1 = 0;
	SY1 = 0;
	SXY2 = 0;
	SX2 = 0;
	SY2 = 0;
	SXYP = 0;
	SXP = 0;
	SYP = 0;
	SZ0 = 0;
	SZ1 = 0;
	SZ2 = 0;
	SZ3 = 0;
	RGB0 = 0;
	R0 = 0;
	G0 = 0;
	B0 = 0;
	CD0 = 0;
	RGB1 = 0;
	R1 = 0;
	G1 = 0;
	B1 = 0;
	CD1 = 0;
	RGB2 = 0;
	R2 = 0;
	G2 = 0;
	B2 = 0;
	CD2 = 0;
	RES1 = 0;
	MAC0 = 0;
	MAC1 = 0;
	MAC2 = 0;
	MAC3 = 0;
	IRGB = 0;
	ORGB = 0;
	LZCS = 0;
	LZCR = 0;
	R11 = 0;
	R12 = 0;
	R13 = 0;
	R21 = 0;
	R22 = 0;
	R23 = 0;
	R31 = 0;
	R32 = 0;
	R33 = 0;
	TRX = 0;
	TRY = 0;
	TRZ = 0;
	L11 = 0;
	L12 = 0;
	L13 = 0;
	L21 = 0;
	L22 = 0;
	L23 = 0;
	L31 = 0;
	L32 = 0;
	L33 = 0;
	RBK = 0;
	GBK = 0;
	BBK = 0;
	LR1 = 0;
	LR2 = 0;
	LR3 = 0;
	LG1 = 0;
	LG2 = 0;
	LG3 = 0;
	LB1 = 0;
	LB2 = 0;
	LB3 = 0;
	RFC = 0;
	GFC = 0;
	BFC = 0;
	OFX = 0;
	OFY = 0;
	H = 0;
	DQA = 0;
	DQB = 0;
	ZSF3 = 0;
	ZSF4 = 0;
	FLAG = 0;
}

void SetGeomOffset(int ofx, int ofy)
{
	OFX = ofx << 16;
	OFY = ofy << 16;
}

void SetGeomScreen(int h)
{
	H = h;
}

static int m_sf;
static long long m_mac0;
static long long m_mac3;

unsigned int gte_leadingzerocount(unsigned int lzcs) {
	unsigned int lzcr = 0;

	if ((lzcs & 0x80000000) == 0)
		lzcs = ~lzcs;

	while ((lzcs & 0x80000000) != 0) {
		lzcr++;
		lzcs <<= 1;
	}

	return lzcr;
}

int LIM(int value, int max, int min, unsigned int flag) {
	if (value > max) {
		FLAG |= flag;
		return max;
	}
	else if (value < min) {
		FLAG |= flag;
		return min;
	}

	return value;
}

static unsigned int MFC2(int reg) {
	switch (reg) {
	case 1:
	case 3:
	case 5:
	case 8:
	case 9:
	case 10:
	case 11:
		gteRegs.CP2D.p[reg].d = (int)gteRegs.CP2D.p[reg].sw.l;
		break;

	case 7:
	case 16:
	case 17:
	case 18:
	case 19:
		gteRegs.CP2D.p[reg].d = (unsigned int)gteRegs.CP2D.p[reg].w.l;
		break;

	case 15:
		gteRegs.CP2D.p[reg].d = SXY2;
		break;

	case 28:
	case 29:
		gteRegs.CP2D.p[reg].d = LIM(IR1 >> 7, 0x1f, 0, 0) | (LIM(IR2 >> 7, 0x1f, 0, 0) << 5) | (LIM(IR3 >> 7, 0x1f, 0, 0) << 10);
		break;
	}

	return gteRegs.CP2D.p[reg].d;
}

static void MTC2(unsigned int value, int reg) {
	switch (reg) {
	case 15:
		SXY0 = SXY1;
		SXY1 = SXY2;
		SXY2 = value;
		break;

	case 28:
		IR1 = (value & 0x1f) << 7;
		IR2 = (value & 0x3e0) << 2;
		IR3 = (value & 0x7c00) >> 3;
		break;

	case 30:
		LZCR = gte_leadingzerocount(value);
		break;

	case 31:
		return;
	}

	gteRegs.CP2D.p[reg].d = value;
}

static void CTC2(unsigned int value, int reg) {
	switch (reg) {
	case 4:
	case 12:
	case 20:
	case 26:
	case 27:
	case 29:
	case 30:
		value = (int)(short)value;
		break;

	case 31:
		value = value & 0x7ffff000;
		if ((value & 0x7f87e000) != 0)
			value |= 0x80000000;
		break;
	}

	gteRegs.CP2C.p[reg].d = value;
}

#define _oB_ (gteRegs.GPR.r[_Rs_] + _Imm_)

inline long long gte_shift(long long a, int sf) {
	if (sf > 0)
		return a >> 12;
	else if (sf < 0)
		return a << 12;

	return a;
}

typedef int64_t s64;

int BOUNDS(/*int44*/long long value, int max_flag, int min_flag) {
	if (value/*.positive_overflow()*/ > s64(0x7ffffffffff))
		FLAG |= max_flag;

	if (value/*.negative_overflow()*/ < s64(-0x80000000000))
		FLAG |= min_flag;

	return gte_shift(value/*.value()*/, m_sf);
}

unsigned int gte_divide(unsigned short numerator, unsigned short denominator)
{
	if (numerator < (denominator * 2))
	{
		static unsigned char table[] =
		{
			0xff, 0xfd, 0xfb, 0xf9, 0xf7, 0xf5, 0xf3, 0xf1, 0xef, 0xee, 0xec, 0xea, 0xe8, 0xe6, 0xe4, 0xe3,
			0xe1, 0xdf, 0xdd, 0xdc, 0xda, 0xd8, 0xd6, 0xd5, 0xd3, 0xd1, 0xd0, 0xce, 0xcd, 0xcb, 0xc9, 0xc8,
			0xc6, 0xc5, 0xc3, 0xc1, 0xc0, 0xbe, 0xbd, 0xbb, 0xba, 0xb8, 0xb7, 0xb5, 0xb4, 0xb2, 0xb1, 0xb0,
			0xae, 0xad, 0xab, 0xaa, 0xa9, 0xa7, 0xa6, 0xa4, 0xa3, 0xa2, 0xa0, 0x9f, 0x9e, 0x9c, 0x9b, 0x9a,
			0x99, 0x97, 0x96, 0x95, 0x94, 0x92, 0x91, 0x90, 0x8f, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x87, 0x86,
			0x85, 0x84, 0x83, 0x82, 0x81, 0x7f, 0x7e, 0x7d, 0x7c, 0x7b, 0x7a, 0x79, 0x78, 0x77, 0x75, 0x74,
			0x73, 0x72, 0x71, 0x70, 0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64,
			0x63, 0x62, 0x61, 0x60, 0x5f, 0x5e, 0x5d, 0x5d, 0x5c, 0x5b, 0x5a, 0x59, 0x58, 0x57, 0x56, 0x55,
			0x54, 0x53, 0x53, 0x52, 0x51, 0x50, 0x4f, 0x4e, 0x4d, 0x4d, 0x4c, 0x4b, 0x4a, 0x49, 0x48, 0x48,
			0x47, 0x46, 0x45, 0x44, 0x43, 0x43, 0x42, 0x41, 0x40, 0x3f, 0x3f, 0x3e, 0x3d, 0x3c, 0x3c, 0x3b,
			0x3a, 0x39, 0x39, 0x38, 0x37, 0x36, 0x36, 0x35, 0x34, 0x33, 0x33, 0x32, 0x31, 0x31, 0x30, 0x2f,
			0x2e, 0x2e, 0x2d, 0x2c, 0x2c, 0x2b, 0x2a, 0x2a, 0x29, 0x28, 0x28, 0x27, 0x26, 0x26, 0x25, 0x24,
			0x24, 0x23, 0x22, 0x22, 0x21, 0x20, 0x20, 0x1f, 0x1e, 0x1e, 0x1d, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a,
			0x19, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13, 0x12, 0x12, 0x11, 0x11,
			0x10, 0x0f, 0x0f, 0x0e, 0x0e, 0x0d, 0x0d, 0x0c, 0x0c, 0x0b, 0x0a, 0x0a, 0x09, 0x09, 0x08, 0x08,
			0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00,
			0x00
		};

		int shift = gte_leadingzerocount(denominator) - 16;

		int r1 = (denominator << shift) & 0x7fff;
		int r2 = table[((r1 + 0x40) >> 7)] + 0x101;
		int r3 = ((0x80 - (r2 * (r1 + 0x8000))) >> 8) & 0x1ffff;
		unsigned int reciprocal = ((r2 * r3) + 0x80) >> 8;

		return (unsigned int)((((unsigned long long)reciprocal * (numerator << shift)) + 0x8000) >> 16);
	}

	return 0xffffffff;
}

/* Setting bits 12 & 19-22 in FLAG does not set bit 31 */

int A1(/*int44*/long long a) { return BOUNDS(a, (1 << 31) | (1 << 30), (1 << 31) | (1 << 27)); }
int A2(/*int44*/long long a) { return BOUNDS(a, (1 << 31) | (1 << 29), (1 << 31) | (1 << 26)); }
int A3(/*int44*/long long a) { m_mac3 = a; return BOUNDS(a, (1 << 31) | (1 << 28), (1 << 31) | (1 << 25)); }
int Lm_B1(int a, int lm) { return LIM(a, 0x7fff, -0x8000 * !lm, (1 << 31) | (1 << 24)); }
int Lm_B2(int a, int lm) { return LIM(a, 0x7fff, -0x8000 * !lm, (1 << 31) | (1 << 23)); }
int Lm_B3(int a, int lm) { return LIM(a, 0x7fff, -0x8000 * !lm, (1 << 22)); }

int Lm_B3_sf(long long value, int sf, int lm) {
	int value_sf = gte_shift(value, sf);
	int value_12 = gte_shift(value, 1);
	int max = 0x7fff;
	int min = 0;
	if (lm == 0)
		min = -0x8000;

	if (value_12 < -0x8000 || value_12 > 0x7fff)
		FLAG |= (1 << 22);

	if (value_sf > max)
		return max;
	else if (value_sf < min)
		return min;

	return value_sf;
}

int Lm_C1(int a) { return LIM(a, 0x00ff, 0x0000, (1 << 21)); }
int Lm_C2(int a) { return LIM(a, 0x00ff, 0x0000, (1 << 20)); }
int Lm_C3(int a) { return LIM(a, 0x00ff, 0x0000, (1 << 19)); }
int Lm_D(long long a, int sf) { return LIM(gte_shift(a, sf), 0xffff, 0x0000, (1 << 31) | (1 << 18)); }

unsigned int Lm_E(unsigned int result) {
	if (result == 0xffffffff) {
		FLAG |= (1 << 31) | (1 << 17);
		return 0x1ffff;
	}

	if (result > 0x1ffff)
		return 0x1ffff;

	return result;
}

long long F(long long a) {
	m_mac0 = a;

	if (a > s64(0x7fffffff))
		FLAG |= (1 << 31) | (1 << 16);

	if (a < s64(-0x80000000))
		FLAG |= (1 << 31) | (1 << 15);

	return a;
}

int Lm_G1(long long a) {
	if (a > 0x3ff) {
		FLAG |= (1 << 31) | (1 << 14);
		return 0x3ff;
	}
	if (a < -0x400) {
		FLAG |= (1 << 31) | (1 << 14);
		return -0x400;
	}

	return a;
}

int Lm_G2(long long a) {
	if (a > 0x3ff) {
		FLAG |= (1 << 31) | (1 << 13);
		return 0x3ff;
	}

	if (a < -0x400) {
		FLAG |= (1 << 31) | (1 << 13);
		return -0x400;
	}

	return a;
}

int Lm_G1_ia(long long a) {
	if (a > 0x3ffffff)
		return 0x3ffffff;

	if (a < -0x4000000)
		return -0x4000000;

	return a;
}

int Lm_G2_ia(long long a) {
	if (a > 0x3ffffff)
		return 0x3ffffff;

	if (a < -0x4000000)
		return -0x4000000;

	return a;
}

int Lm_H(long long value, int sf) {
	long long value_sf = gte_shift(value, sf);
	int value_12 = gte_shift(value, 1);
	int max = 0x1000;
	int min = 0x0000;

	if (value_sf < min || value_sf > max)
		FLAG |= (1 << 12);

	if (value_12 > max)
		return max;

	if (value_12 < min)
		return min;

	return value_12;
}

int docop2(int op) {
	int v;
	int lm;
	int cv;
	int mx;
	int h_over_sz3 = 0;

	lm = GTE_LM(gteop(op));
	m_sf = GTE_SF(gteop(op));

	FLAG = 0;

	switch (GTE_FUNCT(gteop(op))) {
	case 0x00:
	case 0x01:
#ifdef GTE_LOG
		GTELOG("%08x RTPS", op);
#endif

		MAC1 = A1(/*int44*/(long long)((long long)TRX << 12) + (R11 * VX0) + (R12 * VY0) + (R13 * VZ0));
		MAC2 = A2(/*int44*/(long long)((long long)TRY << 12) + (R21 * VX0) + (R22 * VY0) + (R23 * VZ0));
		MAC3 = A3(/*int44*/(long long)((long long)TRZ << 12) + (R31 * VX0) + (R32 * VY0) + (R33 * VZ0));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3_sf(m_mac3, m_sf, lm);
		SZ0 = SZ1;
		SZ1 = SZ2;
		SZ2 = SZ3;
		SZ3 = Lm_D(m_mac3, 1);
		h_over_sz3 = Lm_E(gte_divide(H, SZ3));
		SXY0 = SXY1;
		SXY1 = SXY2;
		SX2 = Lm_G1(F((long long)OFX + ((long long)IR1 * h_over_sz3) * (false ? 0.75 : 1)) >> 16);
		SY2 = Lm_G2(F((long long)OFY + ((long long)IR2 * h_over_sz3)) >> 16);
		MAC0 = F((long long)DQB + ((long long)DQA * h_over_sz3));
		IR0 = Lm_H(m_mac0, 1);
		return 1;

	case 0x06:
#ifdef GTE_LOG
		GTELOG("%08x NCLIP", op);
#endif

		MAC0 = F((long long)(SX0 * SY1) + (SX1 * SY2) + (SX2 * SY0) - (SX0 * SY2) - (SX1 * SY0) - (SX2 * SY1));
		return 1;

	case 0x0c:
#ifdef GTE_LOG
		GTELOG("%08x OP", op);
#endif

		MAC1 = A1((long long)(R22 * IR3) - (R33 * IR2));
		MAC2 = A2((long long)(R33 * IR1) - (R11 * IR3));
		MAC3 = A3((long long)(R11 * IR2) - (R22 * IR1));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		return 1;

	case 0x10:
#ifdef GTE_LOG
		GTELOG("%08x DPCS", op);
#endif

		MAC1 = A1((R << 16) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - (R << 16)), 0)));
		MAC2 = A2((G << 16) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - (G << 16)), 0)));
		MAC3 = A3((B << 16) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - (B << 16)), 0)));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x11:
#ifdef GTE_LOG
		GTELOG("%08x INTPL", op);
#endif

		MAC1 = A1((IR1 << 12) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - (IR1 << 12)), 0)));
		MAC2 = A2((IR2 << 12) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - (IR2 << 12)), 0)));
		MAC3 = A3((IR3 << 12) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - (IR3 << 12)), 0)));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x12:
#ifdef GTE_LOG
		GTELOG("%08x MVMVA", op);
#endif

		mx = GTE_MX(gteop(op));
		v = GTE_V(gteop(op));
		cv = GTE_CV(gteop(op));

		switch (cv) {
		case 2:
			MAC1 = A1((long long)(MX12(mx) * VY(v)) + (MX13(mx) * VZ(v)));
			MAC2 = A2((long long)(MX22(mx) * VY(v)) + (MX23(mx) * VZ(v)));
			MAC3 = A3((long long)(MX32(mx) * VY(v)) + (MX33(mx) * VZ(v)));
			Lm_B1(A1(((long long)CV1(cv) << 12) + (MX11(mx) * VX(v))), 0);
			Lm_B2(A2(((long long)CV2(cv) << 12) + (MX21(mx) * VX(v))), 0);
			Lm_B3(A3(((long long)CV3(cv) << 12) + (MX31(mx) * VX(v))), 0);
			break;

		default:
			MAC1 = A1(/*int44*/(long long)((long long)CV1(cv) << 12) + (MX11(mx) * VX(v)) + (MX12(mx) * VY(v)) + (MX13(mx) * VZ(v)));
			MAC2 = A2(/*int44*/(long long)((long long)CV2(cv) << 12) + (MX21(mx) * VX(v)) + (MX22(mx) * VY(v)) + (MX23(mx) * VZ(v)));
			MAC3 = A3(/*int44*/(long long)((long long)CV3(cv) << 12) + (MX31(mx) * VX(v)) + (MX32(mx) * VY(v)) + (MX33(mx) * VZ(v)));
			break;
		}

		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		return 1;

	case 0x13:
#ifdef GTE_LOG
		GTELOG("%08x NCDS", op);
#endif

		MAC1 = A1((long long)(L11 * VX0) + (L12 * VY0) + (L13 * VZ0));
		MAC2 = A2((long long)(L21 * VX0) + (L22 * VY0) + (L23 * VZ0));
		MAC3 = A3((long long)(L31 * VX0) + (L32 * VY0) + (L33 * VZ0));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
		MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
		MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
		MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
		MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x14:
#ifdef GTE_LOG
		GTELOG("%08x CDP", op);
#endif

		MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
		MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
		MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
		MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
		MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x16:
#ifdef GTE_LOG
		GTELOG("%08x NCDT", op);
#endif

		for (v = 0; v < 3; v++) {
			MAC1 = A1((long long)(L11 * VX(v)) + (L12 * VY(v)) + (L13 * VZ(v)));
			MAC2 = A2((long long)(L21 * VX(v)) + (L22 * VY(v)) + (L23 * VZ(v)));
			MAC3 = A3((long long)(L31 * VX(v)) + (L32 * VY(v)) + (L33 * VZ(v)));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
			MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
			MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
			MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
			MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			RGB0 = RGB1;
			RGB1 = RGB2;
			CD2 = CODE;
			R2 = Lm_C1(MAC1 >> 4);
			G2 = Lm_C2(MAC2 >> 4);
			B2 = Lm_C3(MAC3 >> 4);
		}
		return 1;

	case 0x1b:
#ifdef GTE_LOG
		GTELOG("%08x NCCS", op);
#endif

		MAC1 = A1((long long)(L11 * VX0) + (L12 * VY0) + (L13 * VZ0));
		MAC2 = A2((long long)(L21 * VX0) + (L22 * VY0) + (L23 * VZ0));
		MAC3 = A3((long long)(L31 * VX0) + (L32 * VY0) + (L33 * VZ0));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
		MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
		MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		MAC1 = A1((R << 4) * IR1);
		MAC2 = A2((G << 4) * IR2);
		MAC3 = A3((B << 4) * IR3);
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x1c:
#ifdef GTE_LOG
		GTELOG("%08x CC", op);
#endif

		MAC1 = A1(/*int44*/(long long)(((long long)RBK) << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
		MAC2 = A2(/*int44*/(long long)(((long long)GBK) << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
		MAC3 = A3(/*int44*/(long long)(((long long)BBK) << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		MAC1 = A1((R << 4) * IR1);
		MAC2 = A2((G << 4) * IR2);
		MAC3 = A3((B << 4) * IR3);
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x1e:
#ifdef GTE_LOG
		GTELOG("%08x NCS", op);
#endif

		MAC1 = A1((long long)(L11 * VX0) + (L12 * VY0) + (L13 * VZ0));
		MAC2 = A2((long long)(L21 * VX0) + (L22 * VY0) + (L23 * VZ0));
		MAC3 = A3((long long)(L31 * VX0) + (L32 * VY0) + (L33 * VZ0));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
		MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
		MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x20:
#ifdef GTE_LOG
		GTELOG("%08x NCT", op);
#endif

		for (v = 0; v < 3; v++) {
			MAC1 = A1((long long)(L11 * VX(v)) + (L12 * VY(v)) + (L13 * VZ(v)));
			MAC2 = A2((long long)(L21 * VX(v)) + (L22 * VY(v)) + (L23 * VZ(v)));
			MAC3 = A3((long long)(L31 * VX(v)) + (L32 * VY(v)) + (L33 * VZ(v)));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
			MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
			MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			RGB0 = RGB1;
			RGB1 = RGB2;
			CD2 = CODE;
			R2 = Lm_C1(MAC1 >> 4);
			G2 = Lm_C2(MAC2 >> 4);
			B2 = Lm_C3(MAC3 >> 4);
		}
		return 1;

	case 0x28:
#ifdef GTE_LOG
		GTELOG("%08x SQR", op);
#endif

		MAC1 = A1(IR1 * IR1);
		MAC2 = A2(IR2 * IR2);
		MAC3 = A3(IR3 * IR3);
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		return 1;

	case 0x29:
#ifdef GTE_LOG
		GTELOG("%08x DPCL", op);
#endif

		MAC1 = A1(((R << 4) * IR1) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - ((R << 4) * IR1)), 0)));
		MAC2 = A2(((G << 4) * IR2) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - ((G << 4) * IR2)), 0)));
		MAC3 = A3(((B << 4) * IR3) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - ((B << 4) * IR3)), 0)));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x2a:
#ifdef GTE_LOG
		GTELOG("%08x DPCT", op);
#endif

		for (v = 0; v < 3; v++) {
			MAC1 = A1((R0 << 16) + (IR0 * Lm_B1(A1(((long long)RFC << 12) - (R0 << 16)), 0)));
			MAC2 = A2((G0 << 16) + (IR0 * Lm_B2(A2(((long long)GFC << 12) - (G0 << 16)), 0)));
			MAC3 = A3((B0 << 16) + (IR0 * Lm_B3(A3(((long long)BFC << 12) - (B0 << 16)), 0)));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			RGB0 = RGB1;
			RGB1 = RGB2;
			CD2 = CODE;
			R2 = Lm_C1(MAC1 >> 4);
			G2 = Lm_C2(MAC2 >> 4);
			B2 = Lm_C3(MAC3 >> 4);
		}
		return 1;

	case 0x2d:
#ifdef GTE_LOG
		GTELOG("%08x AVSZ3", op);
#endif

		MAC0 = F((long long)(ZSF3 * SZ1) + (ZSF3 * SZ2) + (ZSF3 * SZ3));
		OTZ = Lm_D(m_mac0, 1);
		return 1;

	case 0x2e:
#ifdef GTE_LOG
		GTELOG("%08x AVSZ4", op);
#endif

		MAC0 = F((long long)(ZSF4 * SZ0) + (ZSF4 * SZ1) + (ZSF4 * SZ2) + (ZSF4 * SZ3));
		OTZ = Lm_D(m_mac0, 1);
		return 1;

	case 0x30:
#ifdef GTE_LOG
		GTELOG("%08x RTPT", op);
#endif

		for (v = 0; v < 3; v++) {
			MAC1 = A1(/*int44*/(long long)((long long)TRX << 12) + (R11 * VX(v)) + (R12 * VY(v)) + (R13 * VZ(v)));
			MAC2 = A2(/*int44*/(long long)((long long)TRY << 12) + (R21 * VX(v)) + (R22 * VY(v)) + (R23 * VZ(v)));
			MAC3 = A3(/*int44*/(long long)((long long)TRZ << 12) + (R31 * VX(v)) + (R32 * VY(v)) + (R33 * VZ(v)));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3_sf(m_mac3, m_sf, lm);
			SZ0 = SZ1;
			SZ1 = SZ2;
			SZ2 = SZ3;
			SZ3 = Lm_D(m_mac3, 1);
			h_over_sz3 = Lm_E(gte_divide(H, SZ3));
			SXY0 = SXY1;
			SXY1 = SXY2;
			SX2 = Lm_G1(F((long long)OFX + ((long long)IR1 * h_over_sz3) * (false ? 0.75 : 1)) >> 16);
			SY2 = Lm_G2(F((long long)OFY + ((long long)IR2 * h_over_sz3)) >> 16);
		}

		MAC0 = F((long long)DQB + ((long long)DQA * h_over_sz3));
		IR0 = Lm_H(m_mac0, 1);
		return 1;

	case 0x3d:
#ifdef GTE_LOG
		GTELOG("%08x GPF", op);
#endif

		MAC1 = A1(IR0 * IR1);
		MAC2 = A2(IR0 * IR2);
		MAC3 = A3(IR0 * IR3);
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x3e:
#ifdef GTE_LOG
		GTELOG("%08x GPL", op);
#endif

		MAC1 = A1(gte_shift(MAC1, -m_sf) + (IR0 * IR1));
		MAC2 = A2(gte_shift(MAC2, -m_sf) + (IR0 * IR2));
		MAC3 = A3(gte_shift(MAC3, -m_sf) + (IR0 * IR3));
		IR1 = Lm_B1(MAC1, lm);
		IR2 = Lm_B2(MAC2, lm);
		IR3 = Lm_B3(MAC3, lm);
		RGB0 = RGB1;
		RGB1 = RGB2;
		CD2 = CODE;
		R2 = Lm_C1(MAC1 >> 4);
		G2 = Lm_C2(MAC2 >> 4);
		B2 = Lm_C3(MAC3 >> 4);
		return 1;

	case 0x3f:
#ifdef GTE_LOG
		GTELOG("%08x NCCT", op);
#endif

		for (v = 0; v < 3; v++) {
			MAC1 = A1((long long)(L11 * VX(v)) + (L12 * VY(v)) + (L13 * VZ(v)));
			MAC2 = A2((long long)(L21 * VX(v)) + (L22 * VY(v)) + (L23 * VZ(v)));
			MAC3 = A3((long long)(L31 * VX(v)) + (L32 * VY(v)) + (L33 * VZ(v)));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			MAC1 = A1(/*int44*/(long long)((long long)RBK << 12) + (LR1 * IR1) + (LR2 * IR2) + (LR3 * IR3));
			MAC2 = A2(/*int44*/(long long)((long long)GBK << 12) + (LG1 * IR1) + (LG2 * IR2) + (LG3 * IR3));
			MAC3 = A3(/*int44*/(long long)((long long)BBK << 12) + (LB1 * IR1) + (LB2 * IR2) + (LB3 * IR3));
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			MAC1 = A1((R << 4) * IR1);
			MAC2 = A2((G << 4) * IR2);
			MAC3 = A3((B << 4) * IR3);
			IR1 = Lm_B1(MAC1, lm);
			IR2 = Lm_B2(MAC2, lm);
			IR3 = Lm_B3(MAC3, lm);
			RGB0 = RGB1;
			RGB1 = RGB2;
			CD2 = CODE;
			R2 = Lm_C1(MAC1 >> 4);
			G2 = Lm_C2(MAC2 >> 4);
			B2 = Lm_C3(MAC3 >> 4);
		}
		return 1;
	}

	return 0;
}