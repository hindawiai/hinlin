<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *            au88x0_cxtalk.c
 *
 *  Wed Nov 19 16:29:47 2003
 *  Copyright  2003  mjander
 *  mjander@users.sourceक्रमge.org
 ****************************************************************************/

/*
 */

#समावेश "au88x0_xtalk.h"

/* Data (a whole lot of data.... ) */

अटल लघु स्थिर sXtalkWideKLeftEq = 0x269C;
अटल लघु स्थिर sXtalkWideKRightEq = 0x269C;
अटल लघु स्थिर sXtalkWideKLeftXt = 0xF25E;
अटल __maybe_unused लघु स्थिर sXtalkWideKRightXt = 0xF25E;
अटल लघु स्थिर sXtalkWideShअगरtLeftEq = 1;
अटल लघु स्थिर sXtalkWideShअगरtRightEq = 1;
अटल लघु स्थिर sXtalkWideShअगरtLeftXt = 0;
अटल __maybe_unused लघु स्थिर sXtalkWideShअगरtRightXt = 0;
अटल अचिन्हित लघु स्थिर wXtalkWideLeftDelay = 0xd;
अटल अचिन्हित लघु स्थिर wXtalkWideRightDelay = 0xd;
अटल लघु स्थिर sXtalkNarrowKLeftEq = 0x468D;
अटल लघु स्थिर sXtalkNarrowKRightEq = 0x468D;
अटल लघु स्थिर sXtalkNarrowKLeftXt = 0xF82E;
अटल __maybe_unused लघु स्थिर sXtalkNarrowKRightXt = 0xF82E;
अटल लघु स्थिर sXtalkNarrowShअगरtLeftEq = 0x3;
अटल लघु स्थिर sXtalkNarrowShअगरtRightEq = 0x3;
अटल लघु स्थिर sXtalkNarrowShअगरtLeftXt = 0;
अटल __maybe_unused लघु स्थिर sXtalkNarrowShअगरtRightXt = 0;
अटल अचिन्हित लघु स्थिर wXtalkNarrowLeftDelay = 0x7;
अटल अचिन्हित लघु स्थिर wXtalkNarrowRightDelay = 0x7;

अटल __maybe_unused xtalk_gains_t स्थिर asXtalkGainsDefault = अणु
	0x4000, 0x4000, 0x4000, 0x4000, 0x4000,
	0x4000, 0x4000, 0x4000, 0x4000,	0x4000
पूर्ण;

अटल __maybe_unused xtalk_gains_t स्थिर asXtalkGainsTest = अणु
	0x7fff, 0x8000, 0x0000, 0x0000, 0x0001,
	0xffff, 0x4000, 0xc000, 0x0002, 0xfffe
पूर्ण;

अटल __maybe_unused xtalk_gains_t स्थिर asXtalkGains1Chan = अणु
	0x7FFF, 0, 0, 0, 0,
	0x7FFF, 0, 0, 0, 0,
पूर्ण;

// Input gain क्रम 4 A3D slices. One possible input pair is left zero.
अटल xtalk_gains_t स्थिर asXtalkGainsAllChan = अणु
	0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0,
	0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,	0
पूर्ण;

अटल xtalk_gains_t स्थिर asXtalkGainsZeros = अणु
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

अटल xtalk_dline_t स्थिर alXtalkDlineZeros = अणु
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;
अटल __maybe_unused xtalk_dline_t स्थिर alXtalkDlineTest = अणु
	0x0000fc18, 0xfff03e8, 0x000186a0, 0xfffe7960, 1, 0xffffffff, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

अटल xtalk_instate_t स्थिर asXtalkInStateZeros = अणु
	0, 0, 0, 0
पूर्ण;

अटल __maybe_unused xtalk_instate_t स्थिर asXtalkInStateTest = अणु
	0x0080, 0xff80, 0x0001, 0xffff
पूर्ण;

अटल xtalk_state_t स्थिर asXtalkOutStateZeros = अणु
	अणु0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0पूर्ण
पूर्ण;

अटल लघु स्थिर sDiamondKLeftEq = 0x401d;
अटल लघु स्थिर sDiamondKRightEq = 0x401d;
अटल लघु स्थिर sDiamondKLeftXt = 0xF90E;
अटल __maybe_unused लघु स्थिर sDiamondKRightXt = 0xF90E;
अटल लघु स्थिर sDiamondShअगरtLeftEq = 1;
अटल लघु स्थिर sDiamondShअगरtRightEq = 1;
अटल लघु स्थिर sDiamondShअगरtLeftXt = 0;
अटल __maybe_unused लघु स्थिर sDiamondShअगरtRightXt = 0;
अटल अचिन्हित लघु स्थिर wDiamondLeftDelay = 0xb;
अटल अचिन्हित लघु स्थिर wDiamondRightDelay = 0xb;

अटल xtalk_coefs_t स्थिर asXtalkWideCoefsLeftEq = अणु
	अणु0xEC4C, 0xDCE9, 0xFDC2, 0xFEEC, 0पूर्ण,
	अणु0x5F60, 0xCBCB, 0xFC26, 0x0305, 0पूर्ण,
	अणु0x340B, 0xe8f5, 0x236c, 0xe40d, 0पूर्ण,
	अणु0x76d5, 0xc78d, 0x05ac, 0xfa5b, 0पूर्ण,
	अणु0x7F04, 0xC0FA, 0x0263, 0xFDA2, 0पूर्ण
पूर्ण;
अटल xtalk_coefs_t स्थिर asXtalkWideCoefsRightEq = अणु
	अणु0xEC4C, 0xDCE9, 0xFDC2, 0xFEEC, 0पूर्ण,
	अणु0x5F60, 0xCBCB, 0xFC26, 0x0305, 0पूर्ण,
	अणु0x340B, 0xe8f5, 0x236c, 0xe40d, 0पूर्ण,
	अणु0x76d5, 0xc78d, 0x05ac, 0xfa5b, 0पूर्ण,
	अणु0x7F04, 0xC0FA, 0x0263, 0xFDA2, 0पूर्ण
पूर्ण;
अटल xtalk_coefs_t स्थिर asXtalkWideCoefsLeftXt = अणु
	अणु0x55c6, 0xc97b, 0x005b, 0x0047, 0पूर्ण,
	अणु0x6a60, 0xca20, 0xffc6, 0x0040, 0पूर्ण,
	अणु0x6411, 0xd711, 0xfca1, 0x0190, 0पूर्ण,
	अणु0x77dc, 0xc79e, 0xffb8, 0x000a, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;
अटल __maybe_unused xtalk_coefs_t स्थिर asXtalkWideCoefsRightXt = अणु
	अणु0x55c6, 0xc97b, 0x005b, 0x0047, 0पूर्ण,
	अणु0x6a60, 0xca20, 0xffc6, 0x0040, 0पूर्ण,
	अणु0x6411, 0xd711, 0xfca1, 0x0190, 0पूर्ण,
	अणु0x77dc, 0xc79e, 0xffb8, 0x000a, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;
अटल xtalk_coefs_t स्थिर asXtalkNarrowCoefsLeftEq = अणु
	अणु0x50B5, 0xD07C, 0x026D, 0xFD21, 0पूर्ण,
	अणु0x460F, 0xE44F, 0xF75E, 0xEFA6, 0पूर्ण,
	अणु0x556D, 0xDCAB, 0x2098, 0xF0F2, 0पूर्ण,
	अणु0x7E03, 0xC1F0, 0x007D, 0xFF89, 0पूर्ण,
	अणु0x383E, 0xFD9D, 0xB278, 0x4547, 0पूर्ण
पूर्ण;

अटल xtalk_coefs_t स्थिर asXtalkNarrowCoefsRightEq = अणु
	अणु0x50B5, 0xD07C, 0x026D, 0xFD21, 0पूर्ण,
	अणु0x460F, 0xE44F, 0xF75E, 0xEFA6, 0पूर्ण,
	अणु0x556D, 0xDCAB, 0x2098, 0xF0F2, 0पूर्ण,
	अणु0x7E03, 0xC1F0, 0x007D, 0xFF89, 0पूर्ण,
	अणु0x383E, 0xFD9D, 0xB278, 0x4547, 0पूर्ण
पूर्ण;

अटल xtalk_coefs_t स्थिर asXtalkNarrowCoefsLeftXt = अणु
	अणु0x3CB2, 0xDF49, 0xF6EA, 0x095B, 0पूर्ण,
	अणु0x6777, 0xC915, 0xFEAF, 0x00B1, 0पूर्ण,
	अणु0x7762, 0xC7D9, 0x025B, 0xFDA6, 0पूर्ण,
	अणु0x6B7A, 0xD2AA, 0xF2FB, 0x0B64, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल __maybe_unused xtalk_coefs_t स्थिर asXtalkNarrowCoefsRightXt = अणु
	अणु0x3CB2, 0xDF49, 0xF6EA, 0x095B, 0पूर्ण,
	अणु0x6777, 0xC915, 0xFEAF, 0x00B1, 0पूर्ण,
	अणु0x7762, 0xC7D9, 0x025B, 0xFDA6, 0पूर्ण,
	अणु0x6B7A, 0xD2AA, 0xF2FB, 0x0B64, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल xtalk_coefs_t स्थिर asXtalkCoefsZeros = अणु
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल xtalk_coefs_t स्थिर asXtalkCoefsPipe = अणु
	अणु0, 0, 0x0FA0, 0, 0पूर्ण,
	अणु0, 0, 0x0FA0, 0, 0पूर्ण,
	अणु0, 0, 0x0FA0, 0, 0पूर्ण,
	अणु0, 0, 0x0FA0, 0, 0पूर्ण,
	अणु0, 0, 0x1180, 0, 0पूर्ण,
पूर्ण;
अटल __maybe_unused xtalk_coefs_t स्थिर asXtalkCoefsNegPipe = अणु
	अणु0, 0, 0xF380, 0, 0पूर्ण,
	अणु0, 0, 0xF380, 0, 0पूर्ण,
	अणु0, 0, 0xF380, 0, 0पूर्ण,
	अणु0, 0, 0xF380, 0, 0पूर्ण,
	अणु0, 0, 0xF200, 0, 0पूर्ण
पूर्ण;

अटल __maybe_unused xtalk_coefs_t स्थिर asXtalkCoefsNumTest = अणु
	अणु0, 0, 0xF380, 0x8000, 0x6D60पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल __maybe_unused xtalk_coefs_t स्थिर asXtalkCoefsDenTest = अणु
	अणु0xC000, 0x2000, 0x4000, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल __maybe_unused xtalk_state_t स्थिर asXtalkOutStateTest = अणु
	अणु0x7FFF, 0x0004, 0xFFFC, 0पूर्ण,
	अणु0xFE00, 0x0008, 0xFFF8, 0x4000पूर्ण,
	अणु0x0200, 0x0010, 0xFFF0, 0xC000पूर्ण,
	अणु0x8000, 0x0020, 0xFFE0, 0पूर्ण,
	अणु0, 0, 0, 0पूर्ण
पूर्ण;

अटल xtalk_coefs_t स्थिर asDiamondCoefsLeftEq = अणु
	अणु0x0F1E, 0x2D05, 0xF8E3, 0x07C8, 0पूर्ण,
	अणु0x45E2, 0xCA51, 0x0448, 0xFCE7, 0पूर्ण,
	अणु0xA93E, 0xDBD5, 0x022C, 0x028A, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल xtalk_coefs_t स्थिर asDiamondCoefsRightEq = अणु
	अणु0x0F1E, 0x2D05, 0xF8E3, 0x07C8, 0पूर्ण,
	अणु0x45E2, 0xCA51, 0x0448, 0xFCE7, 0पूर्ण,
	अणु0xA93E, 0xDBD5, 0x022C, 0x028A, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल xtalk_coefs_t स्थिर asDiamondCoefsLeftXt = अणु
	अणु0x3B50, 0xFE08, 0xF959, 0x0060, 0पूर्ण,
	अणु0x9FCB, 0xD8F1, 0x00A2, 0x003A, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

अटल __maybe_unused xtalk_coefs_t स्थिर asDiamondCoefsRightXt = अणु
	अणु0x3B50, 0xFE08, 0xF959, 0x0060, 0पूर्ण,
	अणु0x9FCB, 0xD8F1, 0x00A2, 0x003A, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण,
	अणु0, 0, 0, 0, 0पूर्ण
पूर्ण;

 /**/
/* XTalk EQ and XT */
अटल व्योम
vortex_XtalkHw_SetLeftEQ(vortex_t * vortex, लघु arg_0, लघु arg_4,
			 xtalk_coefs_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x24200 + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x24204 + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x24208 + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x2420c + i * 0x24, coefs[i][3]);
		hwग_लिखो(vortex->mmio, 0x24210 + i * 0x24, coefs[i][4]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x24538, arg_0 & 0xffff);
	hwग_लिखो(vortex->mmio, 0x2453C, arg_4 & 0xffff);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetRightEQ(vortex_t * vortex, लघु arg_0, लघु arg_4,
			  xtalk_coefs_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x242b4 + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x242b8 + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x242bc + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x242c0 + i * 0x24, coefs[i][3]);
		hwग_लिखो(vortex->mmio, 0x242c4 + i * 0x24, coefs[i][4]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x24540, arg_0 & 0xffff);
	hwग_लिखो(vortex->mmio, 0x24544, arg_4 & 0xffff);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetLeftXT(vortex_t * vortex, लघु arg_0, लघु arg_4,
			 xtalk_coefs_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x24368 + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x2436c + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x24370 + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x24374 + i * 0x24, coefs[i][3]);
		hwग_लिखो(vortex->mmio, 0x24378 + i * 0x24, coefs[i][4]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x24548, arg_0 & 0xffff);
	hwग_लिखो(vortex->mmio, 0x2454C, arg_4 & 0xffff);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetRightXT(vortex_t * vortex, लघु arg_0, लघु arg_4,
			  xtalk_coefs_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x2441C + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x24420 + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x24424 + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x24428 + i * 0x24, coefs[i][3]);
		hwग_लिखो(vortex->mmio, 0x2442C + i * 0x24, coefs[i][4]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x24550, arg_0 & 0xffff);
	hwग_लिखो(vortex->mmio, 0x24554, arg_4 & 0xffff);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetLeftEQStates(vortex_t * vortex,
			       xtalk_instate_t स्थिर arg_0,
			       xtalk_state_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x24214 + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x24218 + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x2421C + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x24220 + i * 0x24, coefs[i][3]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x244F8, arg_0[0]);
	hwग_लिखो(vortex->mmio, 0x244FC, arg_0[1]);
	hwग_लिखो(vortex->mmio, 0x24500, arg_0[2]);
	hwग_लिखो(vortex->mmio, 0x24504, arg_0[3]);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetRightEQStates(vortex_t * vortex,
				xtalk_instate_t स्थिर arg_0,
				xtalk_state_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x242C8 + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x242CC + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x242D0 + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x244D4 + i * 0x24, coefs[i][3]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x24508, arg_0[0]);
	hwग_लिखो(vortex->mmio, 0x2450C, arg_0[1]);
	hwग_लिखो(vortex->mmio, 0x24510, arg_0[2]);
	hwग_लिखो(vortex->mmio, 0x24514, arg_0[3]);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetLeftXTStates(vortex_t * vortex,
			       xtalk_instate_t स्थिर arg_0,
			       xtalk_state_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x2437C + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x24380 + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x24384 + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x24388 + i * 0x24, coefs[i][3]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x24518, arg_0[0]);
	hwग_लिखो(vortex->mmio, 0x2451C, arg_0[1]);
	hwग_लिखो(vortex->mmio, 0x24520, arg_0[2]);
	hwग_लिखो(vortex->mmio, 0x24524, arg_0[3]);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetRightXTStates(vortex_t * vortex,
				xtalk_instate_t स्थिर arg_0,
				xtalk_state_t स्थिर coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		hwग_लिखो(vortex->mmio, 0x24430 + i * 0x24, coefs[i][0]);
		hwग_लिखो(vortex->mmio, 0x24434 + i * 0x24, coefs[i][1]);
		hwग_लिखो(vortex->mmio, 0x24438 + i * 0x24, coefs[i][2]);
		hwग_लिखो(vortex->mmio, 0x2443C + i * 0x24, coefs[i][3]);
	पूर्ण
	hwग_लिखो(vortex->mmio, 0x24528, arg_0[0]);
	hwग_लिखो(vortex->mmio, 0x2452C, arg_0[1]);
	hwग_लिखो(vortex->mmio, 0x24530, arg_0[2]);
	hwग_लिखो(vortex->mmio, 0x24534, arg_0[3]);
पूर्ण

#अगर 0
अटल व्योम
vortex_XtalkHw_GetLeftEQ(vortex_t * vortex, लघु *arg_0, लघु *arg_4,
			 xtalk_coefs_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x24200 + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x24204 + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x24208 + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x2420c + i * 0x24);
		coefs[i][4] = hwपढ़ो(vortex->mmio, 0x24210 + i * 0x24);
	पूर्ण
	*arg_0 = hwपढ़ो(vortex->mmio, 0x24538) & 0xffff;
	*arg_4 = hwपढ़ो(vortex->mmio, 0x2453c) & 0xffff;
पूर्ण

अटल व्योम
vortex_XtalkHw_GetRightEQ(vortex_t * vortex, लघु *arg_0, लघु *arg_4,
			  xtalk_coefs_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x242b4 + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x242b8 + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x242bc + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x242c0 + i * 0x24);
		coefs[i][4] = hwपढ़ो(vortex->mmio, 0x242c4 + i * 0x24);
	पूर्ण
	*arg_0 = hwपढ़ो(vortex->mmio, 0x24540) & 0xffff;
	*arg_4 = hwपढ़ो(vortex->mmio, 0x24544) & 0xffff;
पूर्ण

अटल व्योम
vortex_XtalkHw_GetLeftXT(vortex_t * vortex, लघु *arg_0, लघु *arg_4,
			 xtalk_coefs_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x24368 + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x2436C + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x24370 + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x24374 + i * 0x24);
		coefs[i][4] = hwपढ़ो(vortex->mmio, 0x24378 + i * 0x24);
	पूर्ण
	*arg_0 = hwपढ़ो(vortex->mmio, 0x24548) & 0xffff;
	*arg_4 = hwपढ़ो(vortex->mmio, 0x2454C) & 0xffff;
पूर्ण

अटल व्योम
vortex_XtalkHw_GetRightXT(vortex_t * vortex, लघु *arg_0, लघु *arg_4,
			  xtalk_coefs_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x2441C + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x24420 + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x24424 + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x24428 + i * 0x24);
		coefs[i][4] = hwपढ़ो(vortex->mmio, 0x2442C + i * 0x24);
	पूर्ण
	*arg_0 = hwपढ़ो(vortex->mmio, 0x24550) & 0xffff;
	*arg_4 = hwपढ़ो(vortex->mmio, 0x24554) & 0xffff;
पूर्ण

अटल व्योम
vortex_XtalkHw_GetLeftEQStates(vortex_t * vortex, xtalk_instate_t arg_0,
			       xtalk_state_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x24214 + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x24218 + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x2421C + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x24220 + i * 0x24);
	पूर्ण
	arg_0[0] = hwपढ़ो(vortex->mmio, 0x244F8);
	arg_0[1] = hwपढ़ो(vortex->mmio, 0x244FC);
	arg_0[2] = hwपढ़ो(vortex->mmio, 0x24500);
	arg_0[3] = hwपढ़ो(vortex->mmio, 0x24504);
पूर्ण

अटल व्योम
vortex_XtalkHw_GetRightEQStates(vortex_t * vortex, xtalk_instate_t arg_0,
				xtalk_state_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x242C8 + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x242CC + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x242D0 + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x242D4 + i * 0x24);
	पूर्ण
	arg_0[0] = hwपढ़ो(vortex->mmio, 0x24508);
	arg_0[1] = hwपढ़ो(vortex->mmio, 0x2450C);
	arg_0[2] = hwपढ़ो(vortex->mmio, 0x24510);
	arg_0[3] = hwपढ़ो(vortex->mmio, 0x24514);
पूर्ण

अटल व्योम
vortex_XtalkHw_GetLeftXTStates(vortex_t * vortex, xtalk_instate_t arg_0,
			       xtalk_state_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x2437C + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x24380 + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x24384 + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x24388 + i * 0x24);
	पूर्ण
	arg_0[0] = hwपढ़ो(vortex->mmio, 0x24518);
	arg_0[1] = hwपढ़ो(vortex->mmio, 0x2451C);
	arg_0[2] = hwपढ़ो(vortex->mmio, 0x24520);
	arg_0[3] = hwपढ़ो(vortex->mmio, 0x24524);
पूर्ण

अटल व्योम
vortex_XtalkHw_GetRightXTStates(vortex_t * vortex, xtalk_instate_t arg_0,
				xtalk_state_t coefs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 5; i++) अणु
		coefs[i][0] = hwपढ़ो(vortex->mmio, 0x24430 + i * 0x24);
		coefs[i][1] = hwपढ़ो(vortex->mmio, 0x24434 + i * 0x24);
		coefs[i][2] = hwपढ़ो(vortex->mmio, 0x24438 + i * 0x24);
		coefs[i][3] = hwपढ़ो(vortex->mmio, 0x2443C + i * 0x24);
	पूर्ण
	arg_0[0] = hwपढ़ो(vortex->mmio, 0x24528);
	arg_0[1] = hwपढ़ो(vortex->mmio, 0x2452C);
	arg_0[2] = hwपढ़ो(vortex->mmio, 0x24530);
	arg_0[3] = hwपढ़ो(vortex->mmio, 0x24534);
पूर्ण

#पूर्ण_अगर
/* Gains */

अटल व्योम
vortex_XtalkHw_SetGains(vortex_t * vortex, xtalk_gains_t स्थिर gains)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < XTGAINS_SZ; i++) अणु
		hwग_लिखो(vortex->mmio, 0x244D0 + (i * 4), gains[i]);
	पूर्ण
पूर्ण

अटल व्योम
vortex_XtalkHw_SetGainsAllChan(vortex_t * vortex)
अणु
	vortex_XtalkHw_SetGains(vortex, asXtalkGainsAllChan);
पूर्ण

#अगर 0
अटल व्योम vortex_XtalkHw_GetGains(vortex_t * vortex, xtalk_gains_t gains)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < XTGAINS_SZ; i++)
		gains[i] = hwपढ़ो(vortex->mmio, 0x244D0 + i * 4);
पूर्ण

#पूर्ण_अगर
/* Delay parameters */

अटल व्योम
vortex_XtalkHw_SetDelay(vortex_t * vortex, अचिन्हित लघु right,
			अचिन्हित लघु left)
अणु
	u32 esp0 = 0;

	esp0 &= 0x1FFFFFFF;
	esp0 |= 0xA0000000;
	esp0 = (esp0 & 0xffffE0ff) | ((right & 0x1F) << 8);
	esp0 = (esp0 & 0xfffc1fff) | ((left & 0x1F) << 0xd);

	hwग_लिखो(vortex->mmio, 0x24660, esp0);
पूर्ण

अटल व्योम
vortex_XtalkHw_SetLeftDline(vortex_t * vortex, xtalk_dline_t स्थिर dline)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x20; i++) अणु
		hwग_लिखो(vortex->mmio, 0x24000 + (i << 2), dline[i] & 0xffff);
		hwग_लिखो(vortex->mmio, 0x24080 + (i << 2), dline[i] >> 0x10);
	पूर्ण
पूर्ण

अटल व्योम
vortex_XtalkHw_SetRightDline(vortex_t * vortex, xtalk_dline_t स्थिर dline)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x20; i++) अणु
		hwग_लिखो(vortex->mmio, 0x24100 + (i << 2), dline[i] & 0xffff);
		hwग_लिखो(vortex->mmio, 0x24180 + (i << 2), dline[i] >> 0x10);
	पूर्ण
पूर्ण

#अगर 0
अटल व्योम
vortex_XtalkHw_GetDelay(vortex_t * vortex, अचिन्हित लघु *right,
			अचिन्हित लघु *left)
अणु
	पूर्णांक esp0;

	esp0 = hwपढ़ो(vortex->mmio, 0x24660);
	*right = (esp0 >> 8) & 0x1f;
	*left = (esp0 >> 0xd) & 0x1f;
पूर्ण

अटल व्योम vortex_XtalkHw_GetLeftDline(vortex_t * vortex, xtalk_dline_t dline)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x20; i++) अणु
		dline[i] =
		    (hwपढ़ो(vortex->mmio, 0x24000 + (i << 2)) & 0xffff) |
		    (hwपढ़ो(vortex->mmio, 0x24080 + (i << 2)) << 0x10);
	पूर्ण
पूर्ण

अटल व्योम vortex_XtalkHw_GetRightDline(vortex_t * vortex, xtalk_dline_t dline)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x20; i++) अणु
		dline[i] =
		    (hwपढ़ो(vortex->mmio, 0x24100 + (i << 2)) & 0xffff) |
		    (hwपढ़ो(vortex->mmio, 0x24180 + (i << 2)) << 0x10);
	पूर्ण
पूर्ण

#पूर्ण_अगर
/* Control/Global stuff */

#अगर 0
अटल व्योम vortex_XtalkHw_SetControlReg(vortex_t * vortex, u32 ctrl)
अणु
	hwग_लिखो(vortex->mmio, 0x24660, ctrl);
पूर्ण
अटल व्योम vortex_XtalkHw_GetControlReg(vortex_t * vortex, u32 *ctrl)
अणु
	*ctrl = hwपढ़ो(vortex->mmio, 0x24660);
पूर्ण
#पूर्ण_अगर
अटल व्योम vortex_XtalkHw_SetSampleRate(vortex_t * vortex, u32 sr)
अणु
	u32 temp;

	temp = (hwपढ़ो(vortex->mmio, 0x24660) & 0x1FFFFFFF) | 0xC0000000;
	temp = (temp & 0xffffff07) | ((sr & 0x1f) << 3);
	hwग_लिखो(vortex->mmio, 0x24660, temp);
पूर्ण

#अगर 0
अटल व्योम vortex_XtalkHw_GetSampleRate(vortex_t * vortex, u32 *sr)
अणु
	*sr = (hwपढ़ो(vortex->mmio, 0x24660) >> 3) & 0x1f;
पूर्ण

#पूर्ण_अगर
अटल व्योम vortex_XtalkHw_Enable(vortex_t * vortex)
अणु
	u32 temp;

	temp = (hwपढ़ो(vortex->mmio, 0x24660) & 0x1FFFFFFF) | 0xC0000000;
	temp |= 1;
	hwग_लिखो(vortex->mmio, 0x24660, temp);

पूर्ण

अटल व्योम vortex_XtalkHw_Disable(vortex_t * vortex)
अणु
	u32 temp;

	temp = (hwपढ़ो(vortex->mmio, 0x24660) & 0x1FFFFFFF) | 0xC0000000;
	temp &= 0xfffffffe;
	hwग_लिखो(vortex->mmio, 0x24660, temp);

पूर्ण

अटल व्योम vortex_XtalkHw_ZeroIO(vortex_t * vortex)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 20; i++)
		hwग_लिखो(vortex->mmio, 0x24600 + (i << 2), 0);
	क्रम (i = 0; i < 4; i++)
		hwग_लिखो(vortex->mmio, 0x24650 + (i << 2), 0);
पूर्ण

अटल व्योम vortex_XtalkHw_ZeroState(vortex_t * vortex)
अणु
	vortex_XtalkHw_ZeroIO(vortex);	// अंतरभूतd

	vortex_XtalkHw_SetLeftEQ(vortex, 0, 0, asXtalkCoefsZeros);
	vortex_XtalkHw_SetRightEQ(vortex, 0, 0, asXtalkCoefsZeros);

	vortex_XtalkHw_SetLeftXT(vortex, 0, 0, asXtalkCoefsZeros);
	vortex_XtalkHw_SetRightXT(vortex, 0, 0, asXtalkCoefsZeros);

	vortex_XtalkHw_SetGains(vortex, asXtalkGainsZeros);	// अंतरभूतd

	vortex_XtalkHw_SetDelay(vortex, 0, 0);	// अंतरभूतd

	vortex_XtalkHw_SetLeftDline(vortex, alXtalkDlineZeros);	// अंतरभूतd
	vortex_XtalkHw_SetRightDline(vortex, alXtalkDlineZeros);	// अंतरभूतd
	vortex_XtalkHw_SetLeftDline(vortex, alXtalkDlineZeros);	// अंतरभूतd
	vortex_XtalkHw_SetRightDline(vortex, alXtalkDlineZeros);	// अंतरभूतd

	vortex_XtalkHw_SetLeftEQStates(vortex, asXtalkInStateZeros,
				       asXtalkOutStateZeros);
	vortex_XtalkHw_SetRightEQStates(vortex, asXtalkInStateZeros,
					asXtalkOutStateZeros);
	vortex_XtalkHw_SetLeftXTStates(vortex, asXtalkInStateZeros,
				       asXtalkOutStateZeros);
	vortex_XtalkHw_SetRightXTStates(vortex, asXtalkInStateZeros,
					asXtalkOutStateZeros);
पूर्ण

अटल व्योम vortex_XtalkHw_ProgramPipe(vortex_t * vortex)
अणु

	vortex_XtalkHw_SetLeftEQ(vortex, 0, 1, asXtalkCoefsPipe);
	vortex_XtalkHw_SetRightEQ(vortex, 0, 1, asXtalkCoefsPipe);
	vortex_XtalkHw_SetLeftXT(vortex, 0, 0, asXtalkCoefsZeros);
	vortex_XtalkHw_SetRightXT(vortex, 0, 0, asXtalkCoefsZeros);

	vortex_XtalkHw_SetDelay(vortex, 0, 0);	// अंतरभूतd
पूर्ण

अटल व्योम vortex_XtalkHw_ProgramXtalkWide(vortex_t * vortex)
अणु

	vortex_XtalkHw_SetLeftEQ(vortex, sXtalkWideKLeftEq,
				 sXtalkWideShअगरtLeftEq, asXtalkWideCoefsLeftEq);
	vortex_XtalkHw_SetRightEQ(vortex, sXtalkWideKRightEq,
				  sXtalkWideShअगरtRightEq,
				  asXtalkWideCoefsRightEq);
	vortex_XtalkHw_SetLeftXT(vortex, sXtalkWideKLeftXt,
				 sXtalkWideShअगरtLeftXt, asXtalkWideCoefsLeftXt);
	vortex_XtalkHw_SetRightXT(vortex, sXtalkWideKLeftXt,
				  sXtalkWideShअगरtLeftXt,
				  asXtalkWideCoefsLeftXt);

	vortex_XtalkHw_SetDelay(vortex, wXtalkWideRightDelay, wXtalkWideLeftDelay);	// अंतरभूतd
पूर्ण

अटल व्योम vortex_XtalkHw_ProgramXtalkNarrow(vortex_t * vortex)
अणु

	vortex_XtalkHw_SetLeftEQ(vortex, sXtalkNarrowKLeftEq,
				 sXtalkNarrowShअगरtLeftEq,
				 asXtalkNarrowCoefsLeftEq);
	vortex_XtalkHw_SetRightEQ(vortex, sXtalkNarrowKRightEq,
				  sXtalkNarrowShअगरtRightEq,
				  asXtalkNarrowCoefsRightEq);
	vortex_XtalkHw_SetLeftXT(vortex, sXtalkNarrowKLeftXt,
				 sXtalkNarrowShअगरtLeftXt,
				 asXtalkNarrowCoefsLeftXt);
	vortex_XtalkHw_SetRightXT(vortex, sXtalkNarrowKLeftXt,
				  sXtalkNarrowShअगरtLeftXt,
				  asXtalkNarrowCoefsLeftXt);

	vortex_XtalkHw_SetDelay(vortex, wXtalkNarrowRightDelay, wXtalkNarrowLeftDelay);	// अंतरभूतd
पूर्ण

अटल व्योम vortex_XtalkHw_ProgramDiamondXtalk(vortex_t * vortex)
अणु

	//sDiamondKLeftEq,sDiamondKRightXt,asDiamondCoefsLeftEq
	vortex_XtalkHw_SetLeftEQ(vortex, sDiamondKLeftEq,
				 sDiamondShअगरtLeftEq, asDiamondCoefsLeftEq);
	vortex_XtalkHw_SetRightEQ(vortex, sDiamondKRightEq,
				  sDiamondShअगरtRightEq, asDiamondCoefsRightEq);
	vortex_XtalkHw_SetLeftXT(vortex, sDiamondKLeftXt,
				 sDiamondShअगरtLeftXt, asDiamondCoefsLeftXt);
	vortex_XtalkHw_SetRightXT(vortex, sDiamondKLeftXt,
				  sDiamondShअगरtLeftXt, asDiamondCoefsLeftXt);

	vortex_XtalkHw_SetDelay(vortex, wDiamondRightDelay, wDiamondLeftDelay);	// अंतरभूतd
पूर्ण

अटल व्योम vortex_XtalkHw_init(vortex_t * vortex)
अणु
	vortex_XtalkHw_ZeroState(vortex);
पूर्ण

/* End of file */
