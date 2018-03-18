/*
 * Exported with nin10kit v1.7
 * Invocation command was nin10kit --mode=sprites --bpp=8 --for_bitmap monkey monkey.png enemyShipLeft.png enemyShipRight.png --transparent=FFFFFF 
 * Time-stamp: Sunday 11/12/2017, 21:48:18
 * 
 * Image Information
 * -----------------
 * monkey.png 16@16
 * enemyShipLeft.png 16@16
 * enemyShipRight.png 16@16
 * Transparent color: (255, 255, 255)
 * 
 * All bug reports / feature requests are to be filed here https://github.com/TricksterGuy/nin10kit/issues
 */

#include "monkey.h"

const unsigned short monkey_palette[110] =
{
	0x7fff,0x0000,0x0821,0x0c42,0x0029,0x1063,0x1484,0x1085,
	0x1085,0x1885,0x0015,0x0016,0x0016,0x14a4,0x1488,0x10a5,
	0x1089,0x18a5,0x0018,0x14a6,0x0435,0x10a7,0x1ca6,0x0436,
	0x18a7,0x001a,0x0437,0x0437,0x14c5,0x0038,0x0c8d,0x0c8e,
	0x1cc6,0x001d,0x003a,0x003a,0x1cc7,0x001e,0x001e,0x1ce5,
	0x043c,0x0859,0x043d,0x20e7,0x003e,0x0877,0x083e,0x20e8,
	0x0cce,0x085c,0x10ce,0x0c5c,0x1d08,0x2508,0x4123,0x14ee,
	0x14ee,0x4d40,0x4143,0x2529,0x150e,0x2929,0x4960,0x4d60,
	0x150f,0x150f,0x4961,0x1d0f,0x1d30,0x1d4f,0x214f,0x316b,
	0x256f,0x256f,0x358c,0x558a,0x558b,0x69e0,0x31ac,0x71e1,
	0x2d91,0x51ab,0x39cd,0x7202,0x3dce,0x41ce,0x35b3,0x39ed,
	0x39ee,0x3dee,0x39ef,0x45ee,0x41ef,0x31d4,0x45ef,0x420d,
	0x462e,0x462f,0x4630,0x4630,0x4631,0x4a31,0x6e69,0x5273,
	0x5694,0x62f7,0x6718,0x6b39,0x779c,0x7bbc
};

const unsigned short monkey[384] =
{
	0x0000,0x0000,0x0000,0x6800,0x0000,0x0000,0x0000,0x2b00,
	0x0000,0x0000,0x0000,0x0300,0x0000,0x0000,0x0000,0x5c52,
	0x0000,0x0000,0x0000,0x513b,0x0000,0x0000,0x0000,0x513b,
	0x0000,0x0000,0x0000,0x513b,0x0000,0x0000,0x6a00,0x4e35,
	0x0068,0x0000,0x0000,0x0000,0x002b,0x0000,0x0000,0x0000,
	0x0003,0x0000,0x0000,0x0000,0x525c,0x0000,0x0000,0x0000,
	0x3b51,0x0000,0x0000,0x0000,0x3b51,0x0000,0x0000,0x0000,
	0x3b51,0x0000,0x0000,0x0000,0x354e,0x006a,0x0000,0x0000,
	0x0064,0x0000,0x6b00,0x3b35,0x5201,0x6468,0x0301,0x4a64,
	0x0501,0x1308,0x545c,0x3b3b,0x3b01,0x5454,0x4a5c,0x6805,
	0x006d,0x0000,0x0864,0x6b64,0x0000,0x0000,0x0152,0x6d68,
	0x0000,0x0000,0x6a64,0x0552,0x0000,0x0000,0x0000,0x686b,
	0x353b,0x006b,0x0000,0x6400,0x644a,0x0103,0x6864,0x0152,
	0x3b3b,0x5c54,0x0813,0x0105,0x0568,0x5c4a,0x5454,0x013b,
	0x646b,0x6408,0x0000,0x6d00,0x686d,0x5201,0x0000,0x0000,
	0x5205,0x646a,0x0000,0x0000,0x6b68,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x4044,0x0032,
	0x0000,0x4900,0x281b,0x0004,0x0000,0x1a49,0x2a2a,0x1c2c,
	0x4900,0x261b,0x423a,0x643f,0x1d5d,0x3a2a,0x534d,0x6442,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x4400,0x5d44,0x0000,
	0x0000,0x1938,0x411d,0x0000,0x1f00,0x3123,0x4929,0x646d,
	0x0820,0x1018,0x2d2a,0x5c27,0x5a5a,0x5f62,0x2413,0x5c13,
	0x6261,0x2b13,0x245a,0x643b,0x1365,0x632b,0x1859,0x6420,
	0x1d5d,0x3a2c,0x5366,0x643f,0x4900,0x2c1b,0x423a,0x5a42,
	0x0000,0x1b49,0x2a2a,0x1c2c,0x0000,0x4900,0x291b,0x0004,
	0x0000,0x0000,0x3844,0x001f,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x135c,0x632b,0x2059,0x6420,0x6261,0x2b1c,0x245f,0x6435,
	0x6161,0x5f61,0x2413,0x5c13,0x1518,0x1018,0x2d2e,0x5c27,
	0x3000,0x3328,0x491b,0x5a6d,0x0000,0x2341,0x4417,0x0000,
	0x0000,0x4500,0x5d44,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x445d,0x0045,0x0000,
	0x0000,0x1744,0x4123,0x0000,0x6d5a,0x1b49,0x2833,0x0030,
	0x275c,0x2e2d,0x1810,0x1815,0x135c,0x1324,0x615f,0x6161,
	0x3564,0x5f24,0x1c2b,0x6162,0x2064,0x5920,0x2b63,0x5c13,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x1f00,0x4438,0x0000,0x0000,
	0x0400,0x1b29,0x0049,0x0000,0x2c1c,0x2a2a,0x491b,0x0000,
	0x425a,0x3a42,0x1b2c,0x0049,0x3f64,0x6653,0x2c3a,0x5d1d,
	0x2064,0x5918,0x2b63,0x6513,0x3b64,0x5a24,0x132b,0x6162,
	0x135c,0x1324,0x625f,0x5a5a,0x275c,0x2a2d,0x1810,0x2008,
	0x6d64,0x2949,0x2331,0x001f,0x0000,0x1d41,0x3819,0x0000,
	0x0000,0x445d,0x0044,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x4264,0x4d53,0x2a3a,0x5d1d,0x3f64,0x3a42,0x1b26,0x0049,
	0x2c1c,0x2a2a,0x491a,0x0000,0x0400,0x1b28,0x0049,0x0000,
	0x3200,0x4440,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};

