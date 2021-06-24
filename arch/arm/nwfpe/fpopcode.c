<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.COM, 1998,1999

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#समावेश "fpa11.h"
#समावेश "softfloat.h"
#समावेश "fpopcode.h"
#समावेश "fpsr.h"
#समावेश "fpmodule.h"
#समावेश "fpmodule.inl"

#अगर_घोषित CONFIG_FPE_NWFPE_XP
स्थिर भग्नx80 भग्नx80Constant[] = अणु
	अणु .high = 0x0000, .low = 0x0000000000000000ULLपूर्ण,/* extended 0.0 */
	अणु .high = 0x3fff, .low = 0x8000000000000000ULLपूर्ण,/* extended 1.0 */
	अणु .high = 0x4000, .low = 0x8000000000000000ULLपूर्ण,/* extended 2.0 */
	अणु .high = 0x4000, .low = 0xc000000000000000ULLपूर्ण,/* extended 3.0 */
	अणु .high = 0x4001, .low = 0x8000000000000000ULLपूर्ण,/* extended 4.0 */
	अणु .high = 0x4001, .low = 0xa000000000000000ULLपूर्ण,/* extended 5.0 */
	अणु .high = 0x3ffe, .low = 0x8000000000000000ULLपूर्ण,/* extended 0.5 */
	अणु .high = 0x4002, .low = 0xa000000000000000ULLपूर्ण,/* extended 10.0 */
पूर्ण;
#पूर्ण_अगर

स्थिर भग्न64 भग्न64Constant[] = अणु
	0x0000000000000000ULL,	/* द्विगुन 0.0 */
	0x3ff0000000000000ULL,	/* द्विगुन 1.0 */
	0x4000000000000000ULL,	/* द्विगुन 2.0 */
	0x4008000000000000ULL,	/* द्विगुन 3.0 */
	0x4010000000000000ULL,	/* द्विगुन 4.0 */
	0x4014000000000000ULL,	/* द्विगुन 5.0 */
	0x3fe0000000000000ULL,	/* द्विगुन 0.5 */
	0x4024000000000000ULL	/* द्विगुन 10.0 */
पूर्ण;

स्थिर भग्न32 भग्न32Constant[] = अणु
	0x00000000,		/* single 0.0 */
	0x3f800000,		/* single 1.0 */
	0x40000000,		/* single 2.0 */
	0x40400000,		/* single 3.0 */
	0x40800000,		/* single 4.0 */
	0x40a00000,		/* single 5.0 */
	0x3f000000,		/* single 0.5 */
	0x41200000		/* single 10.0 */
पूर्ण;

