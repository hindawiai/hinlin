<शैली गुरु>
/* $XFree86$ */
/* $XकरोtOrg$ */
/*
 * Mode initializing code (CRT2 section)
 * क्रम SiS 300/305/540/630/730,
 *     SiS 315/550/[M]650/651/[M]661[FGM]X/[M]74x[GX]/330/[M]76x[GX],
 *     XGI V3XT/V5/V8, Z7
 * (Universal module क्रम Linux kernel framebuffer and X.org/XFree86 4.x)
 *
 * Copyright (C) 2001-2005 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is मुक्त software; you can redistribute it and/or modअगरy
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation; either version 2 of the named License,
 * * or any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License क्रम more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary क्रमms, with or without
 * * modअगरication, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary क्रमm must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    करोcumentation and/or other materials provided with the distribution.
 * * 3) The name of the author may not be used to enकरोrse or promote products
 * *    derived from this software without specअगरic prior written permission.
 * *
 * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: 	Thomas Winischhofer <thomas@winischhofer.net>
 *
 * Formerly based on non-functional code-fragements क्रम 300 series by SiS, Inc.
 * Used by permission.
 *
 */

#अगर 1
#घोषणा SET_EMI		/* 302LV/ELV: Set EMI values */
#पूर्ण_अगर

#अगर 1
#घोषणा SET_PWD		/* 301/302LV: Set PWD */
#पूर्ण_अगर

#घोषणा COMPAL_HACK	/* Needed क्रम Compal 1400x1050 (EMI) */
#घोषणा COMPAQ_HACK	/* Needed क्रम Inventec/Compaq 1280x1024 (EMI) */
#घोषणा ASUS_HACK	/* Needed क्रम Asus A2H 1024x768 (EMI) */

#समावेश "init301.h"

#अगर_घोषित CONFIG_FB_SIS_300
#समावेश "oem300.h"
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
#समावेश "oem310.h"
#पूर्ण_अगर

#घोषणा SiS_I2CDELAY      1000
#घोषणा SiS_I2CDELAYSHORT  150

अटल स्थिर अचिन्हित अक्षर SiS_YPbPrTable[3][64] = अणु
  अणु
    0x17,0x1d,0x03,0x09,0x05,0x06,0x0c,0x0c,
    0x94,0x49,0x01,0x0a,0x06,0x0d,0x04,0x0a,
    0x06,0x14,0x0d,0x04,0x0a,0x00,0x85,0x1b,
    0x0c,0x50,0x00,0x97,0x00,0xda,0x4a,0x17,
    0x7d,0x05,0x4b,0x00,0x00,0xe2,0x00,0x02,
    0x03,0x0a,0x65,0x9d /*0x8d*/,0x08,0x92,0x8f,0x40,
    0x60,0x80,0x14,0x90,0x8c,0x60,0x14,0x53 /*0x50*/,
    0x00,0x40,0x44,0x00,0xdb,0x02,0x3b,0x00
  पूर्ण,
  अणु
    0x33,0x06,0x06,0x09,0x0b,0x0c,0x0c,0x0c,
    0x98,0x0a,0x01,0x0d,0x06,0x0d,0x04,0x0a,
    0x06,0x14,0x0d,0x04,0x0a,0x00,0x85,0x3f,
    0x0c,0x50,0xb2,0x9f,0x16,0x59,0x4f,0x13,
    0xad,0x11,0xad,0x1d,0x40,0x8a,0x3d,0xb8,
    0x51,0x5e,0x60,0x49,0x7d,0x92,0x0f,0x40,
    0x60,0x80,0x14,0x90,0x8c,0x60,0x14,0x4e,
    0x43,0x41,0x11,0x00,0xfc,0xff,0x32,0x00
  पूर्ण,
  अणु
#अगर 0 /* OK, but sticks to left edge */
    0x13,0x1d,0xe8,0x09,0x09,0xed,0x0c,0x0c,
    0x98,0x0a,0x01,0x0c,0x06,0x0d,0x04,0x0a,
    0x06,0x14,0x0d,0x04,0x0a,0x00,0x85,0x3f,
    0xed,0x50,0x70,0x9f,0x16,0x59,0x21 /*0x2b*/,0x13,
    0x27,0x0b,0x27,0xfc,0x30,0x27,0x1c,0xb0,
    0x4b,0x4b,0x65 /*0x6f*/,0x2f,0x63,0x92,0x0f,0x40,
    0x60,0x80,0x14,0x90,0x8c,0x60,0x14,0x27,
    0x00,0x40,0x11,0x00,0xfc,0xff,0x32,0x00
#पूर्ण_अगर
#अगर 1 /* Perfect */
    0x23,0x2d,0xe8,0x09,0x09,0xed,0x0c,0x0c,
    0x98,0x0a,0x01,0x0c,0x06,0x0d,0x04,0x0a,
    0x06,0x14,0x0d,0x04,0x0a,0x00,0x85,0x3f,
    0xed,0x50,0x70,0x9f,0x16,0x59,0x60,0x13,
    0x27,0x0b,0x27,0xfc,0x30,0x27,0x1c,0xb0,
    0x4b,0x4b,0x6f,0x2f,0x63,0x92,0x0f,0x40,
    0x60,0x80,0x14,0x90,0x8c,0x60,0x14,0x73,
    0x00,0x40,0x11,0x00,0xfc,0xff,0x32,0x00
#पूर्ण_अगर
  पूर्ण
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_TVPhase[] =
अणु
	0x21,0xED,0xBA,0x08,	/* 0x00 SiS_NTSCPhase */
	0x2A,0x05,0xE3,0x00,	/* 0x01 SiS_PALPhase */
	0x21,0xE4,0x2E,0x9B,	/* 0x02 SiS_PALMPhase */
	0x21,0xF4,0x3E,0xBA,	/* 0x03 SiS_PALNPhase */
	0x1E,0x8B,0xA2,0xA7,
	0x1E,0x83,0x0A,0xE0,	/* 0x05 SiS_SpecialPhaseM */
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x21,0xF0,0x7B,0xD6,	/* 0x08 SiS_NTSCPhase2 */
	0x2A,0x09,0x86,0xE9,	/* 0x09 SiS_PALPhase2 */
	0x21,0xE6,0xEF,0xA4,	/* 0x0a SiS_PALMPhase2 */
	0x21,0xF6,0x94,0x46,	/* 0x0b SiS_PALNPhase2 */
	0x1E,0x8B,0xA2,0xA7,
	0x1E,0x83,0x0A,0xE0,	/* 0x0d SiS_SpecialPhaseM */
	0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,
	0x1e,0x8c,0x5c,0x7a,	/* 0x10 SiS_SpecialPhase */
	0x25,0xd4,0xfd,0x5e	/* 0x11 SiS_SpecialPhaseJ */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_HiTVGroup3_1[] = अणु
    0x00, 0x14, 0x15, 0x25, 0x55, 0x15, 0x0b, 0x13,
    0xb1, 0x41, 0x62, 0x62, 0xff, 0xf4, 0x45, 0xa6,
    0x25, 0x2f, 0x67, 0xf6, 0xbf, 0xff, 0x8e, 0x20,
    0xac, 0xda, 0x60, 0xfe, 0x6a, 0x9a, 0x06, 0x10,
    0xd1, 0x04, 0x18, 0x0a, 0xff, 0x80, 0x00, 0x80,
    0x3b, 0x77, 0x00, 0xef, 0xe0, 0x10, 0xb0, 0xe0,
    0x10, 0x4f, 0x0f, 0x0f, 0x05, 0x0f, 0x08, 0x6e,
    0x1a, 0x1f, 0x25, 0x2a, 0x4c, 0xaa, 0x01
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_HiTVGroup3_2[] = अणु
    0x00, 0x14, 0x15, 0x25, 0x55, 0x15, 0x0b, 0x7a,
    0x54, 0x41, 0xe7, 0xe7, 0xff, 0xf4, 0x45, 0xa6,
    0x25, 0x2f, 0x67, 0xf6, 0xbf, 0xff, 0x8e, 0x20,
    0xac, 0x6a, 0x60, 0x2b, 0x52, 0xcd, 0x61, 0x10,
    0x51, 0x04, 0x18, 0x0a, 0x1f, 0x80, 0x00, 0x80,
    0xff, 0xa4, 0x04, 0x2b, 0x94, 0x21, 0x72, 0x94,
    0x26, 0x05, 0x01, 0x0f, 0xed, 0x0f, 0x0a, 0x64,
    0x18, 0x1d, 0x23, 0x28, 0x4c, 0xaa, 0x01
पूर्ण;

/* 301C / 302ELV extended Part2 TV रेजिस्टरs (4 tap scaler) */

अटल स्थिर अचिन्हित अक्षर SiS_Part2CLVX_1[] = अणु
    0x00,0x00,
    0x00,0x20,0x00,0x00,0x7F,0x20,0x02,0x7F,0x7D,0x20,0x04,0x7F,0x7D,0x1F,0x06,0x7E,
    0x7C,0x1D,0x09,0x7E,0x7C,0x1B,0x0B,0x7E,0x7C,0x19,0x0E,0x7D,0x7C,0x17,0x11,0x7C,
    0x7C,0x14,0x14,0x7C,0x7C,0x11,0x17,0x7C,0x7D,0x0E,0x19,0x7C,0x7E,0x0B,0x1B,0x7C,
    0x7E,0x09,0x1D,0x7C,0x7F,0x06,0x1F,0x7C,0x7F,0x04,0x20,0x7D,0x00,0x02,0x20,0x7E
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_Part2CLVX_2[] = अणु
    0x00,0x00,
    0x00,0x20,0x00,0x00,0x7F,0x20,0x02,0x7F,0x7D,0x20,0x04,0x7F,0x7D,0x1F,0x06,0x7E,
    0x7C,0x1D,0x09,0x7E,0x7C,0x1B,0x0B,0x7E,0x7C,0x19,0x0E,0x7D,0x7C,0x17,0x11,0x7C,
    0x7C,0x14,0x14,0x7C,0x7C,0x11,0x17,0x7C,0x7D,0x0E,0x19,0x7C,0x7E,0x0B,0x1B,0x7C,
    0x7E,0x09,0x1D,0x7C,0x7F,0x06,0x1F,0x7C,0x7F,0x04,0x20,0x7D,0x00,0x02,0x20,0x7E
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_Part2CLVX_3[] = अणु  /* NTSC, 525i, 525p */
    0xE0,0x01,
    0x04,0x1A,0x04,0x7E,0x03,0x1A,0x06,0x7D,0x01,0x1A,0x08,0x7D,0x00,0x19,0x0A,0x7D,
    0x7F,0x19,0x0C,0x7C,0x7E,0x18,0x0E,0x7C,0x7E,0x17,0x10,0x7B,0x7D,0x15,0x12,0x7C,
    0x7D,0x13,0x13,0x7D,0x7C,0x12,0x15,0x7D,0x7C,0x10,0x17,0x7D,0x7C,0x0E,0x18,0x7E,
    0x7D,0x0C,0x19,0x7E,0x7D,0x0A,0x19,0x00,0x7D,0x08,0x1A,0x01,0x7E,0x06,0x1A,0x02,
    0x58,0x02,
    0x07,0x14,0x07,0x7E,0x06,0x14,0x09,0x7D,0x05,0x14,0x0A,0x7D,0x04,0x13,0x0B,0x7E,
    0x03,0x13,0x0C,0x7E,0x02,0x12,0x0D,0x7F,0x01,0x12,0x0E,0x7F,0x01,0x11,0x0F,0x7F,
    0x00,0x10,0x10,0x00,0x7F,0x0F,0x11,0x01,0x7F,0x0E,0x12,0x01,0x7E,0x0D,0x12,0x03,
    0x7E,0x0C,0x13,0x03,0x7E,0x0B,0x13,0x04,0x7E,0x0A,0x14,0x04,0x7D,0x09,0x14,0x06,
    0x00,0x03,
    0x09,0x0F,0x09,0x7F,0x08,0x0F,0x09,0x00,0x07,0x0F,0x0A,0x00,0x06,0x0F,0x0A,0x01,
    0x06,0x0E,0x0B,0x01,0x05,0x0E,0x0B,0x02,0x04,0x0E,0x0C,0x02,0x04,0x0D,0x0C,0x03,
    0x03,0x0D,0x0D,0x03,0x02,0x0C,0x0D,0x05,0x02,0x0C,0x0E,0x04,0x01,0x0B,0x0E,0x06,
    0x01,0x0B,0x0E,0x06,0x00,0x0A,0x0F,0x07,0x00,0x0A,0x0F,0x07,0x00,0x09,0x0F,0x08,
    0xFF,0xFF
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_Part2CLVX_4[] = अणु   /* PAL */
    0x58,0x02,
    0x05,0x19,0x05,0x7D,0x03,0x19,0x06,0x7E,0x02,0x19,0x08,0x7D,0x01,0x18,0x0A,0x7D,
    0x00,0x18,0x0C,0x7C,0x7F,0x17,0x0E,0x7C,0x7E,0x16,0x0F,0x7D,0x7E,0x14,0x11,0x7D,
    0x7D,0x13,0x13,0x7D,0x7D,0x11,0x14,0x7E,0x7D,0x0F,0x16,0x7E,0x7D,0x0E,0x17,0x7E,
    0x7D,0x0C,0x18,0x7F,0x7D,0x0A,0x18,0x01,0x7D,0x08,0x19,0x02,0x7D,0x06,0x19,0x04,
    0x00,0x03,
    0x08,0x12,0x08,0x7E,0x07,0x12,0x09,0x7E,0x06,0x12,0x0A,0x7E,0x05,0x11,0x0B,0x7F,
    0x04,0x11,0x0C,0x7F,0x03,0x11,0x0C,0x00,0x03,0x10,0x0D,0x00,0x02,0x0F,0x0E,0x01,
    0x01,0x0F,0x0F,0x01,0x01,0x0E,0x0F,0x02,0x00,0x0D,0x10,0x03,0x7F,0x0C,0x11,0x04,
    0x7F,0x0C,0x11,0x04,0x7F,0x0B,0x11,0x05,0x7E,0x0A,0x12,0x06,0x7E,0x09,0x12,0x07,
    0x40,0x02,
    0x04,0x1A,0x04,0x7E,0x02,0x1B,0x05,0x7E,0x01,0x1A,0x07,0x7E,0x00,0x1A,0x09,0x7D,
    0x7F,0x19,0x0B,0x7D,0x7E,0x18,0x0D,0x7D,0x7D,0x17,0x10,0x7C,0x7D,0x15,0x12,0x7C,
    0x7C,0x14,0x14,0x7C,0x7C,0x12,0x15,0x7D,0x7C,0x10,0x17,0x7D,0x7C,0x0D,0x18,0x7F,
    0x7D,0x0B,0x19,0x7F,0x7D,0x09,0x1A,0x00,0x7D,0x07,0x1A,0x02,0x7E,0x05,0x1B,0x02,
    0xFF,0xFF
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_Part2CLVX_5[] = अणु   /* 750p */
    0x00,0x03,
    0x05,0x19,0x05,0x7D,0x03,0x19,0x06,0x7E,0x02,0x19,0x08,0x7D,0x01,0x18,0x0A,0x7D,
    0x00,0x18,0x0C,0x7C,0x7F,0x17,0x0E,0x7C,0x7E,0x16,0x0F,0x7D,0x7E,0x14,0x11,0x7D,
    0x7D,0x13,0x13,0x7D,0x7D,0x11,0x14,0x7E,0x7D,0x0F,0x16,0x7E,0x7D,0x0E,0x17,0x7E,
    0x7D,0x0C,0x18,0x7F,0x7D,0x0A,0x18,0x01,0x7D,0x08,0x19,0x02,0x7D,0x06,0x19,0x04,
    0xFF,0xFF
पूर्ण;

अटल स्थिर अचिन्हित अक्षर SiS_Part2CLVX_6[] = अणु   /* 1080i */
    0x00,0x04,
    0x04,0x1A,0x04,0x7E,0x02,0x1B,0x05,0x7E,0x01,0x1A,0x07,0x7E,0x00,0x1A,0x09,0x7D,
    0x7F,0x19,0x0B,0x7D,0x7E,0x18,0x0D,0x7D,0x7D,0x17,0x10,0x7C,0x7D,0x15,0x12,0x7C,
    0x7C,0x14,0x14,0x7C,0x7C,0x12,0x15,0x7D,0x7C,0x10,0x17,0x7D,0x7C,0x0D,0x18,0x7F,
    0x7D,0x0B,0x19,0x7F,0x7D,0x09,0x1A,0x00,0x7D,0x07,0x1A,0x02,0x7E,0x05,0x1B,0x02,
    0xFF,0xFF,
पूर्ण;

#अगर_घोषित CONFIG_FB_SIS_315
/* 661 et al LCD data काष्ठाure (2.03.00) */
अटल स्थिर अचिन्हित अक्षर SiS_LCDStruct661[] = अणु
    /* 1024x768 */
/*  type|CR37|   HDE   |   VDE   |    HT   |    VT   |   hss    | hse   */
    0x02,0xC0,0x00,0x04,0x00,0x03,0x40,0x05,0x26,0x03,0x10,0x00,0x88,
    0x00,0x02,0x00,0x06,0x00,0x41,0x5A,0x64,0x00,0x00,0x00,0x00,0x04,
    /*  | vss     |    vse  |clck|  घड़ी  |CRT2DataP|CRT2DataP|idx     */
    /*					      VESA    non-VESA  noscale */
    /* 1280x1024 */
    0x03,0xC0,0x00,0x05,0x00,0x04,0x98,0x06,0x2A,0x04,0x30,0x00,0x70,
    0x00,0x01,0x00,0x03,0x00,0x6C,0xF8,0x2F,0x00,0x00,0x00,0x00,0x08,
    /* 1400x1050 */
    0x09,0x20,0x78,0x05,0x1A,0x04,0x98,0x06,0x2A,0x04,0x18,0x00,0x38,
    0x00,0x01,0x00,0x03,0x00,0x6C,0xF8,0x2F,0x00,0x00,0x00,0x00,0x09,
    /* 1600x1200 */
    0x0B,0xE0,0x40,0x06,0xB0,0x04,0x70,0x08,0xE2,0x04,0x40,0x00,0xC0,
    0x00,0x01,0x00,0x03,0x00,0xA2,0x70,0x24,0x00,0x00,0x00,0x00,0x0A,
    /* 1280x768 (_2) */
    0x0A,0xE0,0x00,0x05,0x00,0x03,0x7C,0x06,0x26,0x03,0x30,0x00,0x70,
    0x00,0x03,0x00,0x06,0x00,0x4D,0xC8,0x48,0x00,0x00,0x00,0x00,0x06,
    /* 1280x720 */
    0x0E,0xE0,0x00,0x05,0xD0,0x02,0x80,0x05,0x26,0x03,0x10,0x00,0x20,
    0x00,0x01,0x00,0x06,0x00,0x45,0x9C,0x62,0x00,0x00,0x00,0x00,0x05,
    /* 1280x800 (_2) */
    0x0C,0xE0,0x00,0x05,0x20,0x03,0x10,0x06,0x2C,0x03,0x30,0x00,0x70,
    0x00,0x04,0x00,0x03,0x00,0x49,0xCE,0x1E,0x00,0x00,0x00,0x00,0x09,
    /* 1680x1050 */
    0x0D,0xE0,0x90,0x06,0x1A,0x04,0x6C,0x07,0x2A,0x04,0x1A,0x00,0x4C,
    0x00,0x03,0x00,0x06,0x00,0x79,0xBE,0x44,0x00,0x00,0x00,0x00,0x06,
    /* 1280x800_3 */
    0x0C,0xE0,0x00,0x05,0x20,0x03,0xAA,0x05,0x2E,0x03,0x30,0x00,0x50,
    0x00,0x04,0x00,0x03,0x00,0x47,0xA9,0x10,0x00,0x00,0x00,0x00,0x07,
    /* 800x600 */
    0x01,0xC0,0x20,0x03,0x58,0x02,0x20,0x04,0x74,0x02,0x2A,0x00,0x80,
    0x00,0x06,0x00,0x04,0x00,0x28,0x63,0x4B,0x00,0x00,0x00,0x00,0x00,
    /* 1280x854 */
    0x08,0xE0,0x00,0x05,0x56,0x03,0x80,0x06,0x5d,0x03,0x10,0x00,0x70,
    0x00,0x01,0x00,0x03,0x00,0x54,0x75,0x13,0x00,0x00,0x00,0x00,0x08
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_300
अटल अचिन्हित अक्षर SiS300_TrumpionData[14][80] = अणु
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x0D,0x00,0x0D,0x10,0x7F,0x00,0x80,0x02,
    0x20,0x03,0x0B,0x00,0x90,0x01,0xC1,0x01,0x60,0x0C,0x30,0x10,0x00,0x00,0x04,0x23,
    0x00,0x00,0x03,0x28,0x03,0x10,0x05,0x08,0x40,0x10,0x00,0x10,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xBC,0x01,0xFF,0x03,0xFF,0x19,0x01,0x00,0x05,0x09,0x04,0x04,0x05,
    0x04,0x0C,0x09,0x05,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x5A,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x0D,0x00,0x0D,0x10,0x27,0x00,0x80,0x02,
    0x20,0x03,0x07,0x00,0x5E,0x01,0x0D,0x02,0x60,0x0C,0x30,0x11,0x00,0x00,0x04,0x23,
    0x00,0x00,0x03,0x80,0x03,0x28,0x06,0x08,0x40,0x11,0x00,0x11,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0x90,0x01,0xFF,0x0F,0xF4,0x19,0x01,0x00,0x05,0x01,0x00,0x04,0x05,
    0x04,0x0C,0x02,0x01,0x02,0xB0,0x00,0x00,0x02,0xBA,0xEC,0x57,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x0D,0x00,0x0D,0x10,0x8A,0x00,0xD8,0x02,
    0x84,0x03,0x16,0x00,0x90,0x01,0xC1,0x01,0x60,0x0C,0x30,0x1C,0x00,0x20,0x04,0x23,
    0x00,0x01,0x03,0x53,0x03,0x28,0x06,0x08,0x40,0x1C,0x00,0x16,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xD9,0x01,0xFF,0x0F,0xF4,0x18,0x07,0x05,0x05,0x13,0x04,0x04,0x05,
    0x01,0x0B,0x13,0x0A,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x59,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x0D,0x00,0x0D,0x10,0x72,0x00,0xD8,0x02,
    0x84,0x03,0x16,0x00,0x90,0x01,0xC1,0x01,0x60,0x0C,0x30,0x1C,0x00,0x20,0x04,0x23,
    0x00,0x01,0x03,0x53,0x03,0x28,0x06,0x08,0x40,0x1C,0x00,0x16,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xDA,0x01,0xFF,0x0F,0xF4,0x18,0x07,0x05,0x05,0x13,0x04,0x04,0x05,
    0x01,0x0B,0x13,0x0A,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x55,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x02,0x00,0x04,0x01,0x00,0x03,0x0D,0x00,0x0D,0x10,0x7F,0x00,0x80,0x02,
    0x20,0x03,0x16,0x00,0xE0,0x01,0x0D,0x02,0x60,0x0C,0x30,0x98,0x00,0x00,0x04,0x23,
    0x00,0x01,0x03,0x45,0x03,0x48,0x06,0x08,0x40,0x98,0x00,0x98,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xF4,0x01,0xFF,0x0F,0xF4,0x18,0x01,0x00,0x05,0x01,0x00,0x05,0x05,
    0x04,0x0C,0x08,0x05,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x5B,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x02,0x01,0x04,0x01,0x00,0x03,0x0D,0x00,0x0D,0x10,0xBF,0x00,0x20,0x03,
    0x20,0x04,0x0D,0x00,0x58,0x02,0x71,0x02,0x80,0x0C,0x30,0x9A,0x00,0xFA,0x03,0x1D,
    0x00,0x01,0x03,0x22,0x03,0x28,0x06,0x08,0x40,0x98,0x00,0x98,0x04,0x1D,0x00,0x1D,
    0x03,0x11,0x60,0x39,0x03,0x40,0x05,0xF4,0x18,0x07,0x02,0x06,0x04,0x01,0x06,0x0B,
    0x02,0x0A,0x20,0x19,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x5B,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x0D,0x00,0x0D,0x10,0xEF,0x00,0x00,0x04,
    0x40,0x05,0x13,0x00,0x00,0x03,0x26,0x03,0x88,0x0C,0x30,0x90,0x00,0x00,0x04,0x23,
    0x00,0x01,0x03,0x24,0x03,0x28,0x06,0x08,0x40,0x90,0x00,0x90,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0x40,0x05,0xFF,0x0F,0xF4,0x18,0x01,0x00,0x08,0x01,0x00,0x08,0x01,
    0x00,0x08,0x01,0x01,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x5B,0x01,0xBE,0x01,0x00 पूर्ण,
  /* variant 2 */
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x11,0x00,0x0D,0x10,0x7F,0x00,0x80,0x02,
    0x20,0x03,0x15,0x00,0x90,0x01,0xC1,0x01,0x60,0x0C,0x30,0x18,0x00,0x00,0x04,0x23,
    0x00,0x01,0x03,0x44,0x03,0x28,0x06,0x08,0x40,0x18,0x00,0x18,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xA6,0x01,0xFF,0x03,0xFF,0x19,0x01,0x00,0x05,0x13,0x04,0x04,0x05,
    0x04,0x0C,0x13,0x0A,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x55,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x11,0x00,0x0D,0x10,0x7F,0x00,0x80,0x02,
    0x20,0x03,0x15,0x00,0x90,0x01,0xC1,0x01,0x60,0x0C,0x30,0x18,0x00,0x00,0x04,0x23,
    0x00,0x01,0x03,0x44,0x03,0x28,0x06,0x08,0x40,0x18,0x00,0x18,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xA6,0x01,0xFF,0x03,0xFF,0x19,0x01,0x00,0x05,0x13,0x04,0x04,0x05,
    0x04,0x0C,0x13,0x0A,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x55,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x11,0x00,0x0D,0x10,0x8A,0x00,0xD8,0x02,
    0x84,0x03,0x16,0x00,0x90,0x01,0xC1,0x01,0x60,0x0C,0x30,0x1C,0x00,0x20,0x04,0x23,
    0x00,0x01,0x03,0x53,0x03,0x28,0x06,0x08,0x40,0x1C,0x00,0x16,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xDA,0x01,0xFF,0x0F,0xF4,0x18,0x07,0x05,0x05,0x13,0x04,0x04,0x05,
    0x01,0x0B,0x13,0x0A,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x55,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x11,0x00,0x0D,0x10,0x72,0x00,0xD8,0x02,
    0x84,0x03,0x16,0x00,0x90,0x01,0xC1,0x01,0x60,0x0C,0x30,0x1C,0x00,0x20,0x04,0x23,
    0x00,0x01,0x03,0x53,0x03,0x28,0x06,0x08,0x40,0x1C,0x00,0x16,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xDA,0x01,0xFF,0x0F,0xF4,0x18,0x07,0x05,0x05,0x13,0x04,0x04,0x05,
    0x01,0x0B,0x13,0x0A,0x02,0xB0,0x00,0x00,0x02,0xBA,0xF0,0x55,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x02,0x00,0x04,0x01,0x00,0x03,0x11,0x00,0x0D,0x10,0x7F,0x00,0x80,0x02,
    0x20,0x03,0x16,0x00,0xE0,0x01,0x0D,0x02,0x60,0x0C,0x30,0x98,0x00,0x00,0x04,0x23,
    0x00,0x01,0x03,0x45,0x03,0x48,0x06,0x08,0x40,0x98,0x00,0x98,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0xF4,0x01,0xFF,0x0F,0xF4,0x18,0x01,0x00,0x05,0x01,0x00,0x05,0x05,
    0x04,0x0C,0x08,0x05,0x02,0xB0,0x00,0x00,0x02,0xBA,0xEA,0x58,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x02,0x01,0x04,0x01,0x00,0x03,0x11,0x00,0x0D,0x10,0xBF,0x00,0x20,0x03,
    0x20,0x04,0x0D,0x00,0x58,0x02,0x71,0x02,0x80,0x0C,0x30,0x9A,0x00,0xFA,0x03,0x1D,
    0x00,0x01,0x03,0x22,0x03,0x28,0x06,0x08,0x40,0x98,0x00,0x98,0x04,0x1D,0x00,0x1D,
    0x03,0x11,0x60,0x39,0x03,0x40,0x05,0xF4,0x18,0x07,0x02,0x06,0x04,0x01,0x06,0x0B,
    0x02,0x0A,0x20,0x19,0x02,0xB0,0x00,0x00,0x02,0xBA,0xEA,0x58,0x01,0xBE,0x01,0x00 पूर्ण,
  अणु 0x02,0x0A,0x0A,0x01,0x04,0x01,0x00,0x03,0x11,0x00,0x0D,0x10,0xEF,0x00,0x00,0x04,
    0x40,0x05,0x13,0x00,0x00,0x03,0x26,0x03,0x88,0x0C,0x30,0x90,0x00,0x00,0x04,0x23,
    0x00,0x01,0x03,0x24,0x03,0x28,0x06,0x08,0x40,0x90,0x00,0x90,0x04,0x23,0x00,0x23,
    0x03,0x11,0x60,0x40,0x05,0xFF,0x0F,0xF4,0x18,0x01,0x00,0x08,0x01,0x00,0x08,0x01,
    0x00,0x08,0x01,0x01,0x02,0xB0,0x00,0x00,0x02,0xBA,0xEA,0x58,0x01,0xBE,0x01,0x00 पूर्ण
पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम	SiS_Chrontel701xOn(काष्ठा SiS_Private *SiS_Pr);
अटल व्योम	SiS_Chrontel701xOff(काष्ठा SiS_Private *SiS_Pr);
अटल व्योम	SiS_ChrontelInitTVVSync(काष्ठा SiS_Private *SiS_Pr);
अटल व्योम	SiS_ChrontelDoSomething1(काष्ठा SiS_Private *SiS_Pr);
#पूर्ण_अगर /* 315 */

#अगर_घोषित CONFIG_FB_SIS_300
अटल  bool	SiS_SetTrumpionBlock(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर *dataptr);
#पूर्ण_अगर

अटल अचिन्हित लघु	SiS_InitDDCRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित पूर्णांक VBFlags,
				पूर्णांक VGAEngine, अचिन्हित लघु adaptnum, अचिन्हित लघु DDCdatatype,
				bool checkcr32, अचिन्हित पूर्णांक VBFlags2);
अटल अचिन्हित लघु	SiS_ProbeDDC(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_ReadDDC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु DDCdatatype,
				अचिन्हित अक्षर *buffer);
अटल व्योम		SiS_SetSwitchDDC2(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_SetStart(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_SetStop(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_SetSCLKLow(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_SetSCLKHigh(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_ReadDDC2Data(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_WriteDDC2Data(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempax);
अटल अचिन्हित लघु	SiS_CheckACK(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_WriteDABDDC(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_PrepareReadDDC(काष्ठा SiS_Private *SiS_Pr);
अटल अचिन्हित लघु	SiS_PrepareDDC(काष्ठा SiS_Private *SiS_Pr);
अटल व्योम		SiS_SendACK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु yesno);
अटल अचिन्हित लघु	SiS_DoProbeDDC(काष्ठा SiS_Private *SiS_Pr);

#अगर_घोषित CONFIG_FB_SIS_300
अटल व्योम		SiS_OEM300Setting(काष्ठा SiS_Private *SiS_Pr,
				अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RefTabindex);
अटल व्योम		SetOEMLCDData2(काष्ठा SiS_Private *SiS_Pr,
				अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,अचिन्हित लघु RefTableIndex);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम		SiS_OEM310Setting(काष्ठा SiS_Private *SiS_Pr,
				अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI);
अटल व्योम		SiS_OEM661Setting(काष्ठा SiS_Private *SiS_Pr,
				अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI);
अटल व्योम		SiS_FinalizeLCD(काष्ठा SiS_Private *, अचिन्हित लघु, अचिन्हित लघु);
#पूर्ण_अगर

अटल अचिन्हित लघु	SiS_GetBIOSLCDResInfo(काष्ठा SiS_Private *SiS_Pr);
अटल व्योम		SiS_SetCH70xx(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg, अचिन्हित अक्षर val);

/*********************************************/
/*         HELPER: Lock/Unlock CRT2          */
/*********************************************/

व्योम
SiS_UnLockCRT2(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType == XGI_20)
      वापस;
   अन्यथा अगर(SiS_Pr->ChipType >= SIS_315H)
      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2f,0x01);
   अन्यथा
      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x24,0x01);
पूर्ण

अटल
व्योम
SiS_LockCRT2(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType == XGI_20)
      वापस;
   अन्यथा अगर(SiS_Pr->ChipType >= SIS_315H)
      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2F,0xFE);
   अन्यथा
      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x24,0xFE);
पूर्ण

/*********************************************/
/*            HELPER: Write SR11             */
/*********************************************/

अटल व्योम
SiS_SetRegSR11ANDOR(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु DataAND, अचिन्हित लघु DataOR)
अणु
   अगर(SiS_Pr->ChipType >= SIS_661) अणु
      DataAND &= 0x0f;
      DataOR  &= 0x0f;
   पूर्ण
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x11,DataAND,DataOR);
पूर्ण

/*********************************************/
/*    HELPER: Get Poपूर्णांकer to LCD काष्ठाure   */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_315
अटल अचिन्हित अक्षर *
GetLCDStructPtr661(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित अक्षर  *myptr = शून्य;
   अचिन्हित लघु romindex = 0, reg = 0, idx = 0;

   /* Use the BIOS tables only क्रम LVDS panels; TMDS is unreliable
    * due to the variaty of panels the BIOS करोesn't know about.
    * Exception: If the BIOS has better knowledge (such as in हाल
    * of machines with a 301C and a panel that करोes not support DDC)
    * use the BIOS data as well.
    */

   अगर((SiS_Pr->SiS_ROMNew) &&
      ((SiS_Pr->SiS_VBType & VB_SISLVDS) || (!SiS_Pr->PanelSelfDetected))) अणु

      अगर(SiS_Pr->ChipType < SIS_661) reg = 0x3c;
      अन्यथा                           reg = 0x7d;

      idx = (SiS_GetReg(SiS_Pr->SiS_P3d4,reg) & 0x1f) * 26;

      अगर(idx < (8*26)) अणु
         myptr = (अचिन्हित अक्षर *)&SiS_LCDStruct661[idx];
      पूर्ण
      romindex = SISGETROMW(0x100);
      अगर(romindex) अणु
         romindex += idx;
         myptr = &ROMAddr[romindex];
      पूर्ण
   पूर्ण
   वापस myptr;
पूर्ण

अटल अचिन्हित लघु
GetLCDStructPtr661_2(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु romptr = 0;

   /* Use the BIOS tables only क्रम LVDS panels; TMDS is unreliable
    * due to the variaty of panels the BIOS करोesn't know about.
    * Exception: If the BIOS has better knowledge (such as in हाल
    * of machines with a 301C and a panel that करोes not support DDC)
    * use the BIOS data as well.
    */

   अगर((SiS_Pr->SiS_ROMNew) &&
      ((SiS_Pr->SiS_VBType & VB_SISLVDS) || (!SiS_Pr->PanelSelfDetected))) अणु
      romptr = SISGETROMW(0x102);
      romptr += ((SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4) * SiS_Pr->SiS661LCD2TableSize);
   पूर्ण

   वापस romptr;
पूर्ण
#पूर्ण_अगर

/*********************************************/
/*           Adjust Rate क्रम CRT2            */
/*********************************************/

अटल bool
SiS_AdjustCRT2Rate(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RRTI, अचिन्हित लघु *i)
अणु
   अचिन्हित लघु checkmask=0, modeid, infoflag;

   modeid = SiS_Pr->SiS_RefIndex[RRTI + (*i)].ModeID;

   अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) अणु

	 checkmask |= SupportRAMDAC2;
	 अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	    checkmask |= SupportRAMDAC2_135;
	    अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	       checkmask |= SupportRAMDAC2_162;
	       अगर(SiS_Pr->SiS_VBType & VB_SISRAMDAC202) अणु
		  checkmask |= SupportRAMDAC2_202;
	       पूर्ण
	    पूर्ण
	 पूर्ण

      पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु

	 checkmask |= SupportLCD;
	 अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	    अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	       अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
	          अगर(modeid == 0x2e) checkmask |= Support64048060Hz;
	       पूर्ण
	    पूर्ण
	 पूर्ण

      पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु

	 checkmask |= SupportHiVision;

      पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToYPbPr525750|SetCRT2ToAVIDEO|SetCRT2ToSVIDEO|SetCRT2ToSCART)) अणु

	 checkmask |= SupportTV;
	 अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	    checkmask |= SupportTV1024;
	    अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
	       अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) अणु
	          checkmask |= SupportYPbPr750p;
	       पूर्ण
	    पूर्ण
	 पूर्ण

      पूर्ण

   पूर्ण अन्यथा अणु	/* LVDS */

      अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	    checkmask |= SupportCHTV;
	 पूर्ण
      पूर्ण

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	 checkmask |= SupportLCD;
      पूर्ण

   पूर्ण

   /* Look backwards in table क्रम matching CRT2 mode */
   क्रम(; SiS_Pr->SiS_RefIndex[RRTI + (*i)].ModeID == modeid; (*i)--) अणु
      infoflag = SiS_Pr->SiS_RefIndex[RRTI + (*i)].Ext_InfoFlag;
      अगर(infoflag & checkmask) वापस true;
      अगर((*i) == 0) अवरोध;
   पूर्ण

   /* Look through the whole mode-section of the table from the beginning
    * क्रम a matching CRT2 mode अगर no mode was found yet.
    */
   क्रम((*i) = 0; ; (*i)++) अणु
      अगर(SiS_Pr->SiS_RefIndex[RRTI + (*i)].ModeID != modeid) अवरोध;
      infoflag = SiS_Pr->SiS_RefIndex[RRTI + (*i)].Ext_InfoFlag;
      अगर(infoflag & checkmask) वापस true;
   पूर्ण
   वापस false;
पूर्ण

/*********************************************/
/*              Get rate index               */
/*********************************************/

अचिन्हित लघु
SiS_GetRatePtr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु RRTI,i,backup_i;
   अचिन्हित लघु modeflag,index,temp,backupindex;
   अटल स्थिर अचिन्हित लघु LCDRefreshIndex[] = अणु
		0x00, 0x00, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,
		0x01, 0x01, 0x01, 0x01,
		0x00, 0x00, 0x00, 0x00
   पूर्ण;

   /* Do NOT check क्रम UseCustomMode here, will skrew up FIFO */
   अगर(ModeNo == 0xfe) वापस 0;

   अगर(ModeNo <= 0x13) अणु
      modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
   पूर्ण अन्यथा अणु
      modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   पूर्ण

   अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	 अगर(modeflag & HalfDCLK) वापस 0;
      पूर्ण
   पूर्ण

   अगर(ModeNo < 0x14) वापस 0xFFFF;

   index = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x33) >> SiS_Pr->SiS_SelectCRT2Rate) & 0x0F;
   backupindex = index;

   अगर(index > 0) index--;

   अगर(SiS_Pr->SiS_SetFlag & ProgrammingCRT2) अणु
      अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	    अगर(SiS_Pr->SiS_VBType & VB_NoLCD)		 index = 0;
	    अन्यथा अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) index = backupindex = 0;
	 पूर्ण
	 अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
	    अगर(!(SiS_Pr->SiS_VBType & VB_NoLCD)) अणु
	       temp = LCDRefreshIndex[SiS_GetBIOSLCDResInfo(SiS_Pr)];
	       अगर(index > temp) index = temp;
	    पूर्ण
	 पूर्ण
      पूर्ण अन्यथा अणु
	 अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) index = 0;
	 अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	    अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) index = 0;
	 पूर्ण
      पूर्ण
   पूर्ण

   RRTI = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].REFindex;
   ModeNo = SiS_Pr->SiS_RefIndex[RRTI].ModeID;

   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      अगर(!(SiS_Pr->SiS_VBInfo & DriverMode)) अणु
	 अगर( (SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_VESAID == 0x105) ||
	     (SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_VESAID == 0x107) ) अणु
	    अगर(backupindex <= 1) RRTI++;
	 पूर्ण
      पूर्ण
   पूर्ण

   i = 0;
   करो अणु
      अगर(SiS_Pr->SiS_RefIndex[RRTI + i].ModeID != ModeNo) अवरोध;
      temp = SiS_Pr->SiS_RefIndex[RRTI + i].Ext_InfoFlag;
      temp &= ModeTypeMask;
      अगर(temp < SiS_Pr->SiS_ModeType) अवरोध;
      i++;
      index--;
   पूर्ण जबतक(index != 0xFFFF);

   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) अणु
      अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	 temp = SiS_Pr->SiS_RefIndex[RRTI + i - 1].Ext_InfoFlag;
	 अगर(temp & InterlaceMode) i++;
      पूर्ण
   पूर्ण

   i--;

   अगर((SiS_Pr->SiS_SetFlag & ProgrammingCRT2) && (!(SiS_Pr->SiS_VBInfo & DisableCRT2Display))) अणु
      backup_i = i;
      अगर(!(SiS_AdjustCRT2Rate(SiS_Pr, ModeNo, ModeIdIndex, RRTI, &i))) अणु
	 i = backup_i;
      पूर्ण
   पूर्ण

   वापस (RRTI + i);
पूर्ण

/*********************************************/
/*            STORE CRT2 INFO in CR34        */
/*********************************************/

अटल व्योम
SiS_SaveCRT2Info(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
   अचिन्हित लघु temp1, temp2;

   /* Store CRT1 ModeNo in CR34 */
   SiS_SetReg(SiS_Pr->SiS_P3d4,0x34,ModeNo);
   temp1 = (SiS_Pr->SiS_VBInfo & SetInSlaveMode) >> 8;
   temp2 = ~(SetInSlaveMode >> 8);
   SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x31,temp2,temp1);
पूर्ण

/*********************************************/
/*    HELPER: GET SOME DATA FROM BIOS ROM    */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_300
अटल bool
SiS_CR36BIOSWord23b(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु temp,temp1;

   अगर(SiS_Pr->SiS_UseROM) अणु
      अगर((ROMAddr[0x233] == 0x12) && (ROMAddr[0x234] == 0x34)) अणु
	 temp = 1 << ((SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4) & 0x0f);
	 temp1 = SISGETROMW(0x23b);
	 अगर(temp1 & temp) वापस true;
      पूर्ण
   पूर्ण
   वापस false;
पूर्ण

अटल bool
SiS_CR36BIOSWord23d(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु temp,temp1;

   अगर(SiS_Pr->SiS_UseROM) अणु
      अगर((ROMAddr[0x233] == 0x12) && (ROMAddr[0x234] == 0x34)) अणु
	 temp = 1 << ((SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4) & 0x0f);
	 temp1 = SISGETROMW(0x23d);
	 अगर(temp1 & temp) वापस true;
      पूर्ण
   पूर्ण
   वापस false;
पूर्ण
#पूर्ण_अगर

/*********************************************/
/*          HELPER: DELAY FUNCTIONS          */
/*********************************************/

व्योम
SiS_DDC2Delay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित पूर्णांक delayसमय)
अणु
   जबतक (delayसमय-- > 0)
      SiS_GetReg(SiS_Pr->SiS_P3c4, 0x05);
पूर्ण

#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
अटल व्योम
SiS_GenericDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु delay)
अणु
   SiS_DDC2Delay(SiS_Pr, delay * 36);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
SiS_LongDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु delay)
अणु
   जबतक(delay--) अणु
      SiS_GenericDelay(SiS_Pr, 6623);
   पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
अटल व्योम
SiS_ShortDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु delay)
अणु
   जबतक(delay--) अणु
      SiS_GenericDelay(SiS_Pr, 66);
   पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम
SiS_PanelDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु DelayTime)
अणु
#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु PanelID, DelayIndex, Delay=0;
#पूर्ण_अगर

   अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300

      PanelID = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36);
      अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	 अगर(SiS_Pr->SiS_VBType & VB_SIS301) PanelID &= 0xf7;
	 अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x18) & 0x10)) PanelID = 0x12;
      पूर्ण
      DelayIndex = PanelID >> 4;
      अगर((DelayTime >= 2) && ((PanelID & 0x0f) == 1))  अणु
	 Delay = 3;
      पूर्ण अन्यथा अणु
	 अगर(DelayTime >= 2) DelayTime -= 2;
	 अगर(!(DelayTime & 0x01)) अणु
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].समयr[0];
	 पूर्ण अन्यथा अणु
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].समयr[1];
	 पूर्ण
	 अगर(SiS_Pr->SiS_UseROM) अणु
	    अगर(ROMAddr[0x220] & 0x40) अणु
	       अगर(!(DelayTime & 0x01)) Delay = (अचिन्हित लघु)ROMAddr[0x225];
	       अन्यथा 	    	       Delay = (अचिन्हित लघु)ROMAddr[0x226];
	    पूर्ण
	 पूर्ण
      पूर्ण
      SiS_ShortDelay(SiS_Pr, Delay);

#पूर्ण_अगर  /* CONFIG_FB_SIS_300 */

   पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315

      अगर((SiS_Pr->ChipType >= SIS_661)    ||
	 (SiS_Pr->ChipType <= SIS_315PRO) ||
	 (SiS_Pr->ChipType == SIS_330)    ||
	 (SiS_Pr->SiS_ROMNew)) अणु

	 अगर(!(DelayTime & 0x01)) अणु
	    SiS_DDC2Delay(SiS_Pr, 0x1000);
	 पूर्ण अन्यथा अणु
	    SiS_DDC2Delay(SiS_Pr, 0x4000);
	 पूर्ण

      पूर्ण अन्यथा अगर (SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु			/* 315 series, LVDS; Special */

	 अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 0) अणु
	    PanelID = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36);
	    अगर(SiS_Pr->SiS_CustomT == CUT_CLEVO1400) अणु
	       अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x1b) & 0x10)) PanelID = 0x12;
	    पूर्ण
	    अगर(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) अणु
	       DelayIndex = PanelID & 0x0f;
	    पूर्ण अन्यथा अणु
	       DelayIndex = PanelID >> 4;
	    पूर्ण
	    अगर((DelayTime >= 2) && ((PanelID & 0x0f) == 1))  अणु
	       Delay = 3;
	    पूर्ण अन्यथा अणु
	       अगर(DelayTime >= 2) DelayTime -= 2;
	       अगर(!(DelayTime & 0x01)) अणु
		  Delay = SiS_Pr->SiS_PanelDelayTblLVDS[DelayIndex].समयr[0];
		पूर्ण अन्यथा अणु
		  Delay = SiS_Pr->SiS_PanelDelayTblLVDS[DelayIndex].समयr[1];
	       पूर्ण
	       अगर((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) अणु
		  अगर(ROMAddr[0x13c] & 0x40) अणु
		     अगर(!(DelayTime & 0x01)) अणु
			Delay = (अचिन्हित लघु)ROMAddr[0x17e];
		     पूर्ण अन्यथा अणु
			Delay = (अचिन्हित लघु)ROMAddr[0x17f];
		     पूर्ण
		  पूर्ण
	       पूर्ण
	    पूर्ण
	    SiS_ShortDelay(SiS_Pr, Delay);
	 पूर्ण

      पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु			/* 315 series, all bridges */

	 DelayIndex = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4;
	 अगर(!(DelayTime & 0x01)) अणु
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].समयr[0];
	 पूर्ण अन्यथा अणु
	    Delay = SiS_Pr->SiS_PanelDelayTbl[DelayIndex].समयr[1];
	 पूर्ण
	 Delay <<= 8;
	 SiS_DDC2Delay(SiS_Pr, Delay);

      पूर्ण

#पूर्ण_अगर /* CONFIG_FB_SIS_315 */

   पूर्ण
पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
SiS_PanelDelayLoop(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु DelayTime, अचिन्हित लघु DelayLoop)
अणु
   पूर्णांक i;
   क्रम(i = 0; i < DelayLoop; i++) अणु
      SiS_PanelDelay(SiS_Pr, DelayTime);
   पूर्ण
पूर्ण
#पूर्ण_अगर

/*********************************************/
/*    HELPER: WAIT-FOR-RETRACE FUNCTIONS     */
/*********************************************/

व्योम
SiS_WaitRetrace1(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु watchकरोg;

   अगर(SiS_GetReg(SiS_Pr->SiS_P3c4,0x1f) & 0xc0) वापस;
   अगर(!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x17) & 0x80)) वापस;

   watchकरोg = 65535;
   जबतक((SiS_GetRegByte(SiS_Pr->SiS_P3da) & 0x08) && --watchकरोg);
   watchकरोg = 65535;
   जबतक((!(SiS_GetRegByte(SiS_Pr->SiS_P3da) & 0x08)) && --watchकरोg);
पूर्ण

#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
अटल व्योम
SiS_WaitRetrace2(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg)
अणु
   अचिन्हित लघु watchकरोg;

   watchकरोg = 65535;
   जबतक((SiS_GetReg(SiS_Pr->SiS_Part1Port,reg) & 0x02) && --watchकरोg);
   watchकरोg = 65535;
   जबतक((!(SiS_GetReg(SiS_Pr->SiS_Part1Port,reg) & 0x02)) && --watchकरोg);
पूर्ण
#पूर्ण_अगर

अटल व्योम
SiS_WaitVBRetrace(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
      अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	 अगर(!(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x20)) वापस;
      पूर्ण
      अगर(!(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x80)) अणु
	 SiS_WaitRetrace1(SiS_Pr);
      पूर्ण अन्यथा अणु
	 SiS_WaitRetrace2(SiS_Pr, 0x25);
      पूर्ण
#पूर्ण_अगर
   पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
      अगर(!(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x40)) अणु
	 SiS_WaitRetrace1(SiS_Pr);
      पूर्ण अन्यथा अणु
	 SiS_WaitRetrace2(SiS_Pr, 0x30);
      पूर्ण
#पूर्ण_अगर
   पूर्ण
पूर्ण

अटल व्योम
SiS_VBWait(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु tempal,temp,i,j;

   temp = 0;
   क्रम(i = 0; i < 3; i++) अणु
     क्रम(j = 0; j < 100; j++) अणु
        tempal = SiS_GetRegByte(SiS_Pr->SiS_P3da);
        अगर(temp & 0x01) अणु
	   अगर((tempal & 0x08))  जारी;
	   अन्यथा अवरोध;
        पूर्ण अन्यथा अणु
	   अगर(!(tempal & 0x08)) जारी;
	   अन्यथा अवरोध;
        पूर्ण
     पूर्ण
     temp ^= 0x01;
   पूर्ण
पूर्ण

अटल व्योम
SiS_VBLongWait(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
      SiS_VBWait(SiS_Pr);
   पूर्ण अन्यथा अणु
      SiS_WaitRetrace1(SiS_Pr);
   पूर्ण
पूर्ण

/*********************************************/
/*               HELPER: MISC                */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_300
अटल bool
SiS_Is301B(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x01) >= 0xb0) वापस true;
   वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool
SiS_CRT2IsLCD(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType == SIS_730) अणु
      अगर(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x20) वापस true;
   पूर्ण
   अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x30) & 0x20) वापस true;
   वापस false;
पूर्ण

bool
SiS_IsDualEdge(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर_घोषित CONFIG_FB_SIS_315
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      अगर((SiS_Pr->ChipType != SIS_650) || (SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0xf0)) अणु
	 अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & EnableDualEdge) वापस true;
      पूर्ण
   पूर्ण
#पूर्ण_अगर
   वापस false;
पूर्ण

bool
SiS_IsVAMode(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर_घोषित CONFIG_FB_SIS_315
   अचिन्हित लघु flag;

   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
      अगर((flag & EnableDualEdge) && (flag & SetToLCDA)) वापस true;
   पूर्ण
#पूर्ण_अगर
   वापस false;
पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_IsVAorLCD(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_IsVAMode(SiS_Pr))  वापस true;
   अगर(SiS_CRT2IsLCD(SiS_Pr)) वापस true;
   वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool
SiS_IsDualLink(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर_घोषित CONFIG_FB_SIS_315
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      अगर((SiS_CRT2IsLCD(SiS_Pr)) ||
         (SiS_IsVAMode(SiS_Pr))) अणु
	 अगर(SiS_Pr->SiS_LCDInfo & LCDDualLink) वापस true;
      पूर्ण
   पूर्ण
#पूर्ण_अगर
   वापस false;
पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_TVEnabled(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर((SiS_GetReg(SiS_Pr->SiS_Part2Port,0x00) & 0x0f) != 0x0c) वापस true;
   अगर(SiS_Pr->SiS_VBType & VB_SISYPBPR) अणु
      अगर(SiS_GetReg(SiS_Pr->SiS_Part2Port,0x4d) & 0x10) वापस true;
   पूर्ण
   वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_LCDAEnabled(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x13) & 0x04) वापस true;
   वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_WeHaveBacklightCtrl(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->ChipType < SIS_661)) अणु
      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x79) & 0x10) वापस true;
   पूर्ण
   वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_IsNotM650orLater(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag;

   अगर(SiS_Pr->ChipType == SIS_650) अणु
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0xf0;
      /* Check क्रम revision != A0 only */
      अगर((flag == 0xe0) || (flag == 0xc0) ||
         (flag == 0xb0) || (flag == 0x90)) वापस false;
   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_661) वापस false;
   वापस true;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_IsYPbPr(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      /* YPrPb = 0x08 */
      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & EnableCHYPbPr) वापस true;
   पूर्ण
   वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_IsChScart(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      /* Scart = 0x04 */
      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & EnableCHScart) वापस true;
   पूर्ण
   वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_IsTVOrYPbPrOrScart(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag;

   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
      अगर(flag & SetCRT2ToTV)        वापस true;
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
      अगर(flag & EnableCHYPbPr)      वापस true;  /* = YPrPb = 0x08 */
      अगर(flag & EnableCHScart)      वापस true;  /* = Scart = 0x04 - TW */
   पूर्ण अन्यथा अणु
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
      अगर(flag & SetCRT2ToTV)        वापस true;
   पूर्ण
   वापस false;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
अटल bool
SiS_IsLCDOrLCDA(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag;

   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
      अगर(flag & SetCRT2ToLCD) वापस true;
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
      अगर(flag & SetToLCDA)    वापस true;
   पूर्ण अन्यथा अणु
      flag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
      अगर(flag & SetCRT2ToLCD) वापस true;
   पूर्ण
   वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool
SiS_HaveBridge(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag;

   अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
      वापस true;
   पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
      flag = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x00);
      अगर((flag == 1) || (flag == 2)) वापस true;
   पूर्ण
   वापस false;
पूर्ण

अटल bool
SiS_BridgeIsEnabled(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag;

   अगर(SiS_HaveBridge(SiS_Pr)) अणु
      flag = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00);
      अगर(SiS_Pr->ChipType < SIS_315H) अणु
	flag &= 0xa0;
	अगर((flag == 0x80) || (flag == 0x20)) वापस true;
      पूर्ण अन्यथा अणु
	flag &= 0x50;
	अगर((flag == 0x40) || (flag == 0x10)) वापस true;
      पूर्ण
   पूर्ण
   वापस false;
पूर्ण

अटल bool
SiS_BridgeInSlavemode(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag1;

   flag1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x31);
   अगर(flag1 & (SetInSlaveMode >> 8)) वापस true;
   वापस false;
पूर्ण

/*********************************************/
/*       GET VIDEO BRIDGE CONFIG INFO        */
/*********************************************/

/* Setup general purpose IO क्रम Chrontel communication */
#अगर_घोषित CONFIG_FB_SIS_300
व्योम
SiS_SetChrontelGPIO(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु myvbinfo)
अणु
   अचिन्हित पूर्णांक   acpibase;
   अचिन्हित लघु temp;

   अगर(!(SiS_Pr->SiS_ChSW)) वापस;

   acpibase = sisfb_पढ़ो_lpc_pci_dword(SiS_Pr, 0x74);
   acpibase &= 0xFFFF;
   अगर(!acpibase) वापस;
   temp = SiS_GetRegShort((acpibase + 0x3c));	/* ACPI रेजिस्टर 0x3c: GP Event 1 I/O mode select */
   temp &= 0xFEFF;
   SiS_SetRegShort((acpibase + 0x3c), temp);
   temp = SiS_GetRegShort((acpibase + 0x3c));
   temp = SiS_GetRegShort((acpibase + 0x3a));	/* ACPI रेजिस्टर 0x3a: GP Pin Level (low/high) */
   temp &= 0xFEFF;
   अगर(!(myvbinfo & SetCRT2ToTV)) temp |= 0x0100;
   SiS_SetRegShort((acpibase + 0x3a), temp);
   temp = SiS_GetRegShort((acpibase + 0x3a));
पूर्ण
#पूर्ण_अगर

व्योम
SiS_GetVBInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, पूर्णांक checkcrt2mode)
अणु
   अचिन्हित लघु tempax, tempbx, temp;
   अचिन्हित लघु modeflag, resinfo = 0;

   SiS_Pr->SiS_SetFlag = 0;

   modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

   SiS_Pr->SiS_ModeType = modeflag & ModeTypeMask;

   अगर((ModeNo > 0x13) && (!SiS_Pr->UseCustomMode)) अणु
      resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
   पूर्ण

   tempbx = 0;

   अगर(SiS_HaveBridge(SiS_Pr)) अणु

	temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	tempbx |= temp;
	tempax = SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) << 8;
	tempax &= (DriverMode | LoadDACFlag | SetNotSimuMode | SetPALTV);
	tempbx |= tempax;

#अगर_घोषित CONFIG_FB_SIS_315
	अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	   अगर(SiS_Pr->SiS_VBType & VB_SISLCDA) अणु
	      अगर(ModeNo == 0x03) अणु
		 /* Mode 0x03 is never in driver mode */
		 SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x31,0xbf);
	      पूर्ण
	      अगर(!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & (DriverMode >> 8))) अणु
		 /* Reset LCDA setting अगर not driver mode */
		 SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x38,0xfc);
	      पूर्ण
	      अगर(IS_SIS650) अणु
		 अगर(SiS_Pr->SiS_UseLCDA) अणु
		    अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x5f) & 0xF0) अणु
		       अगर((ModeNo <= 0x13) || (!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & (DriverMode >> 8)))) अणु
			  SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x38,(EnableDualEdge | SetToLCDA));
		       पूर्ण
		    पूर्ण
		 पूर्ण
	      पूर्ण
	      temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	      अगर((temp & (EnableDualEdge | SetToLCDA)) == (EnableDualEdge | SetToLCDA)) अणु
		 tempbx |= SetCRT2ToLCDA;
	      पूर्ण
	   पूर्ण

	   अगर(SiS_Pr->ChipType >= SIS_661) अणु /* New CR layout */
	      tempbx &= ~(SetCRT2ToYPbPr525750 | SetCRT2ToHiVision);
	      अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x38) & 0x04) अणु
		 temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35) & 0xe0;
		 अगर(temp == 0x60) tempbx |= SetCRT2ToHiVision;
		 अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISYPBPR) अणु
		    tempbx |= SetCRT2ToYPbPr525750;
		 पूर्ण
	      पूर्ण
	   पूर्ण

	   अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
	      temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	      अगर(temp & SetToLCDA) अणु
		 tempbx |= SetCRT2ToLCDA;
	      पूर्ण
	      अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
		 अगर(temp & EnableCHYPbPr) अणु
		    tempbx |= SetCRT2ToCHYPbPr;
		 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण

#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */

        अगर(!(SiS_Pr->SiS_VBType & VB_SISVGA2)) अणु
	   tempbx &= ~(SetCRT2ToRAMDAC);
	पूर्ण

	अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	   temp = SetCRT2ToSVIDEO   |
		  SetCRT2ToAVIDEO   |
		  SetCRT2ToSCART    |
		  SetCRT2ToLCDA     |
		  SetCRT2ToLCD      |
		  SetCRT2ToRAMDAC   |
		  SetCRT2ToHiVision |
		  SetCRT2ToYPbPr525750;
	पूर्ण अन्यथा अणु
	   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	      अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
		 temp = SetCRT2ToAVIDEO |
		        SetCRT2ToSVIDEO |
		        SetCRT2ToSCART  |
		        SetCRT2ToLCDA   |
		        SetCRT2ToLCD    |
		        SetCRT2ToCHYPbPr;
	      पूर्ण अन्यथा अणु
		 temp = SetCRT2ToLCDA   |
		        SetCRT2ToLCD;
	      पूर्ण
	   पूर्ण अन्यथा अणु
	      अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
		 temp = SetCRT2ToTV | SetCRT2ToLCD;
	      पूर्ण अन्यथा अणु
		 temp = SetCRT2ToLCD;
	      पूर्ण
	   पूर्ण
	पूर्ण

	अगर(!(tempbx & temp)) अणु
	   tempax = DisableCRT2Display;
	   tempbx = 0;
	पूर्ण

	अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

	   अचिन्हित लघु clearmask = ( DriverMode |
				DisableCRT2Display |
				LoadDACFlag 	   |
				SetNotSimuMode 	   |
				SetInSlaveMode 	   |
				SetPALTV 	   |
				SwitchCRT2	   |
				SetSimuScanMode );

	   अगर(tempbx & SetCRT2ToLCDA)        tempbx &= (clearmask | SetCRT2ToLCDA);
	   अगर(tempbx & SetCRT2ToRAMDAC)      tempbx &= (clearmask | SetCRT2ToRAMDAC);
	   अगर(tempbx & SetCRT2ToLCD)         tempbx &= (clearmask | SetCRT2ToLCD);
	   अगर(tempbx & SetCRT2ToSCART)       tempbx &= (clearmask | SetCRT2ToSCART);
	   अगर(tempbx & SetCRT2ToHiVision)    tempbx &= (clearmask | SetCRT2ToHiVision);
	   अगर(tempbx & SetCRT2ToYPbPr525750) tempbx &= (clearmask | SetCRT2ToYPbPr525750);

	पूर्ण अन्यथा अणु

	   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	      अगर(tempbx & SetCRT2ToLCDA) अणु
		 tempbx &= (0xFF00|SwitchCRT2|SetSimuScanMode);
	      पूर्ण
	   पूर्ण
	   अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	      अगर(tempbx & SetCRT2ToTV) अणु
		 tempbx &= (0xFF00|SetCRT2ToTV|SwitchCRT2|SetSimuScanMode);
	      पूर्ण
	   पूर्ण
	   अगर(tempbx & SetCRT2ToLCD) अणु
	      tempbx &= (0xFF00|SetCRT2ToLCD|SwitchCRT2|SetSimuScanMode);
	   पूर्ण
	   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	      अगर(tempbx & SetCRT2ToLCDA) अणु
	         tempbx |= SetCRT2ToLCD;
	      पूर्ण
	   पूर्ण

	पूर्ण

	अगर(tempax & DisableCRT2Display) अणु
	   अगर(!(tempbx & (SwitchCRT2 | SetSimuScanMode))) अणु
	      tempbx = SetSimuScanMode | DisableCRT2Display;
	   पूर्ण
	पूर्ण

	अगर(!(tempbx & DriverMode)) tempbx |= SetSimuScanMode;

	/* LVDS/CHRONTEL (LCD/TV) and 301BDH (LCD) can only be slave in 8bpp modes */
	अगर(SiS_Pr->SiS_ModeType <= ModeVGA) अणु
	   अगर( (SiS_Pr->SiS_IF_DEF_LVDS == 1) ||
	       ((SiS_Pr->SiS_VBType & VB_NoLCD) && (tempbx & SetCRT2ToLCD)) ) अणु
	      modeflag &= (~CRT2Mode);
	   पूर्ण
	पूर्ण

	अगर(!(tempbx & SetSimuScanMode)) अणु
	   अगर(tempbx & SwitchCRT2) अणु
	      अगर((!(modeflag & CRT2Mode)) && (checkcrt2mode)) अणु
		 अगर(resinfo != SIS_RI_1600x1200) अणु
		    tempbx |= SetSimuScanMode;
		 पूर्ण
              पूर्ण
	   पूर्ण अन्यथा अणु
	      अगर(SiS_BridgeIsEnabled(SiS_Pr)) अणु
		 अगर(!(tempbx & DriverMode)) अणु
		    अगर(SiS_BridgeInSlavemode(SiS_Pr)) अणु
		       tempbx |= SetSimuScanMode;
		    पूर्ण
		 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण

	अगर(!(tempbx & DisableCRT2Display)) अणु
	   अगर(tempbx & DriverMode) अणु
	      अगर(tempbx & SetSimuScanMode) अणु
		 अगर((!(modeflag & CRT2Mode)) && (checkcrt2mode)) अणु
		    अगर(resinfo != SIS_RI_1600x1200) अणु
		       tempbx |= SetInSlaveMode;
		    पूर्ण
		 पूर्ण
	      पूर्ण
	   पूर्ण अन्यथा अणु
	      tempbx |= SetInSlaveMode;
	   पूर्ण
	पूर्ण

   पूर्ण

   SiS_Pr->SiS_VBInfo = tempbx;

#अगर_घोषित CONFIG_FB_SIS_300
   अगर(SiS_Pr->ChipType == SIS_630) अणु
      SiS_SetChrontelGPIO(SiS_Pr, SiS_Pr->SiS_VBInfo);
   पूर्ण
#पूर्ण_अगर

#अगर 0
   prपूर्णांकk(KERN_DEBUG "sisfb: (init301: VBInfo= 0x%04x, SetFlag=0x%04x)\n",
      SiS_Pr->SiS_VBInfo, SiS_Pr->SiS_SetFlag);
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*           DETERMINE YPbPr MODE            */
/*********************************************/

व्योम
SiS_SetYPbPr(काष्ठा SiS_Private *SiS_Pr)
अणु

   अचिन्हित अक्षर temp;

   /* Note: This variable is only used on 30xLV प्रणालीs.
    * CR38 has a dअगरferent meaning on LVDS/CH7019 प्रणालीs.
    * On 661 and later, these bits moved to CR35.
    *
    * On 301, 301B, only HiVision 1080i is supported.
    * On 30xLV, 301C, only YPbPr 1080i is supported.
    */

   SiS_Pr->SiS_YPbPr = 0;
   अगर(SiS_Pr->ChipType >= SIS_661) वापस;

   अगर(SiS_Pr->SiS_VBType) अणु
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	 SiS_Pr->SiS_YPbPr = YPbPrHiVision;
      पूर्ण
   पूर्ण

   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      अगर(SiS_Pr->SiS_VBType & VB_SISYPBPR) अणु
	 temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	 अगर(temp & 0x08) अणु
	    चयन((temp >> 4)) अणु
	    हाल 0x00: SiS_Pr->SiS_YPbPr = YPbPr525i;     अवरोध;
	    हाल 0x01: SiS_Pr->SiS_YPbPr = YPbPr525p;     अवरोध;
	    हाल 0x02: SiS_Pr->SiS_YPbPr = YPbPr750p;     अवरोध;
	    हाल 0x03: SiS_Pr->SiS_YPbPr = YPbPrHiVision; अवरोध;
	    पूर्ण
	 पूर्ण
      पूर्ण
   पूर्ण

पूर्ण

/*********************************************/
/*           DETERMINE TVMode flag           */
/*********************************************/

व्योम
SiS_SetTVMode(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु temp, temp1, resinfo = 0, romindex = 0;
   अचिन्हित अक्षर  OutputSelect = *SiS_Pr->pSiS_OutputSelect;

   SiS_Pr->SiS_TVMode = 0;

   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) वापस;
   अगर(SiS_Pr->UseCustomMode) वापस;

   अगर(ModeNo > 0x13) अणु
      resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
   पूर्ण

   अगर(SiS_Pr->ChipType < SIS_661) अणु

      अगर(SiS_Pr->SiS_VBInfo & SetPALTV) SiS_Pr->SiS_TVMode |= TVSetPAL;

      अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	 temp = 0;
	 अगर((SiS_Pr->ChipType == SIS_630) ||
	    (SiS_Pr->ChipType == SIS_730)) अणु
	    temp = 0x35;
	    romindex = 0xfe;
	 पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	    temp = 0x38;
	    अगर(SiS_Pr->ChipType < XGI_20) अणु
	       romindex = 0xf3;
	       अगर(SiS_Pr->ChipType >= SIS_330) romindex = 0x11b;
	    पूर्ण
	 पूर्ण
	 अगर(temp) अणु
	    अगर(romindex && SiS_Pr->SiS_UseROM && (!(SiS_Pr->SiS_ROMNew))) अणु
	       OutputSelect = ROMAddr[romindex];
	       अगर(!(OutputSelect & EnablePALMN)) अणु
		  SiS_SetRegAND(SiS_Pr->SiS_P3d4,temp,0x3F);
	       पूर्ण
	    पूर्ण
	    temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,temp);
	    अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
	       अगर(temp1 & EnablePALM) अणु		/* 0x40 */
		  SiS_Pr->SiS_TVMode |= TVSetPALM;
		  SiS_Pr->SiS_TVMode &= ~TVSetPAL;
	       पूर्ण अन्यथा अगर(temp1 & EnablePALN) अणु	/* 0x80 */
		  SiS_Pr->SiS_TVMode |= TVSetPALN;
	       पूर्ण
	    पूर्ण अन्यथा अणु
	       अगर(temp1 & EnableNTSCJ) अणु	/* 0x40 */
		  SiS_Pr->SiS_TVMode |= TVSetNTSCJ;
	       पूर्ण
	    पूर्ण
	 पूर्ण
	 /* Translate HiVision/YPbPr to our new flags */
	 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	    अगर(SiS_Pr->SiS_YPbPr == YPbPr750p)          SiS_Pr->SiS_TVMode |= TVSetYPbPr750p;
	    अन्यथा अगर(SiS_Pr->SiS_YPbPr == YPbPr525p)     SiS_Pr->SiS_TVMode |= TVSetYPbPr525p;
	    अन्यथा अगर(SiS_Pr->SiS_YPbPr == YPbPrHiVision) SiS_Pr->SiS_TVMode |= TVSetHiVision;
	    अन्यथा				        SiS_Pr->SiS_TVMode |= TVSetYPbPr525i;
	    अगर(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p | TVSetYPbPr525p | TVSetYPbPr525i)) अणु
	       SiS_Pr->SiS_VBInfo &= ~SetCRT2ToHiVision;
	       SiS_Pr->SiS_VBInfo |= SetCRT2ToYPbPr525750;
	    पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetHiVision) अणु
	       SiS_Pr->SiS_TVMode |= TVSetPAL;
	    पूर्ण
	 पूर्ण
      पूर्ण अन्यथा अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	 अगर(SiS_Pr->SiS_CHOverScan) अणु
	    अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 1) अणु
	       temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35);
	       अगर((temp & TVOverScan) || (SiS_Pr->SiS_CHOverScan == 1)) अणु
		  SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	       पूर्ण
	    पूर्ण अन्यथा अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	       temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x79);
	       अगर((temp & 0x80) || (SiS_Pr->SiS_CHOverScan == 1)) अणु
		  SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	       पूर्ण
	    पूर्ण
	    अगर(SiS_Pr->SiS_CHSOverScan) अणु
	       SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	    पूर्ण
	 पूर्ण
	 अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	    temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x38);
	    अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
	       अगर(temp & EnablePALM)      SiS_Pr->SiS_TVMode |= TVSetPALM;
	       अन्यथा अगर(temp & EnablePALN) SiS_Pr->SiS_TVMode |= TVSetPALN;
	    पूर्ण अन्यथा अणु
	       अगर(temp & EnableNTSCJ) अणु
		  SiS_Pr->SiS_TVMode |= TVSetNTSCJ;
	       पूर्ण
	    पूर्ण
	 पूर्ण
      पूर्ण

   पूर्ण अन्यथा अणु  /* 661 and later */

      temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35);
      अगर(temp1 & 0x01) अणु
	 SiS_Pr->SiS_TVMode |= TVSetPAL;
	 अगर(temp1 & 0x08) अणु
	    SiS_Pr->SiS_TVMode |= TVSetPALN;
	 पूर्ण अन्यथा अगर(temp1 & 0x04) अणु
	    अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	       SiS_Pr->SiS_TVMode &= ~TVSetPAL;
	    पूर्ण
	    SiS_Pr->SiS_TVMode |= TVSetPALM;
	 पूर्ण
      पूर्ण अन्यथा अणु
	 अगर(temp1 & 0x02) अणु
	    SiS_Pr->SiS_TVMode |= TVSetNTSCJ;
	 पूर्ण
      पूर्ण
      अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	 अगर(SiS_Pr->SiS_CHOverScan) अणु
	    अगर((temp1 & 0x10) || (SiS_Pr->SiS_CHOverScan == 1)) अणु
	       SiS_Pr->SiS_TVMode |= TVSetCHOverScan;
	    पूर्ण
	 पूर्ण
      पूर्ण
      अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
	    temp1 &= 0xe0;
	    अगर(temp1 == 0x00)      SiS_Pr->SiS_TVMode |= TVSetYPbPr525i;
	    अन्यथा अगर(temp1 == 0x20) SiS_Pr->SiS_TVMode |= TVSetYPbPr525p;
	    अन्यथा अगर(temp1 == 0x40) SiS_Pr->SiS_TVMode |= TVSetYPbPr750p;
	 पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	    SiS_Pr->SiS_TVMode |= (TVSetHiVision | TVSetPAL);
	 पूर्ण
	 अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToYPbPr525750 | SetCRT2ToHiVision)) अणु
	    अगर(resinfo == SIS_RI_800x480 || resinfo == SIS_RI_1024x576 || resinfo == SIS_RI_1280x720) अणु
	       SiS_Pr->SiS_TVMode |= TVAspect169;
	    पूर्ण अन्यथा अणु
	       temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x39);
	       अगर(temp1 & 0x02) अणु
		  अगर(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p | TVSetHiVision)) अणु
		     SiS_Pr->SiS_TVMode |= TVAspect169;
		  पूर्ण अन्यथा अणु
		     SiS_Pr->SiS_TVMode |= TVAspect43LB;
		  पूर्ण
	       पूर्ण अन्यथा अणु
		  SiS_Pr->SiS_TVMode |= TVAspect43;
	       पूर्ण
	    पूर्ण
	 पूर्ण
      पूर्ण
   पूर्ण

   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToSCART) SiS_Pr->SiS_TVMode |= TVSetPAL;

   अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	 SiS_Pr->SiS_TVMode |= TVSetPAL;
	 SiS_Pr->SiS_TVMode &= ~(TVSetPALM | TVSetPALN | TVSetNTSCJ);
      पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
	 अगर(SiS_Pr->SiS_TVMode & (TVSetYPbPr525i | TVSetYPbPr525p | TVSetYPbPr750p)) अणु
	    SiS_Pr->SiS_TVMode &= ~(TVSetPAL | TVSetNTSCJ | TVSetPALM | TVSetPALN);
	 पूर्ण
      पूर्ण

      अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	 अगर(!(SiS_Pr->SiS_VBInfo & SetNotSimuMode)) अणु
	    SiS_Pr->SiS_TVMode |= TVSetTVSimuMode;
	 पूर्ण
      पूर्ण

      अगर(!(SiS_Pr->SiS_TVMode & TVSetPAL)) अणु
	 अगर(resinfo == SIS_RI_1024x768) अणु
	    अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) अणु
	       SiS_Pr->SiS_TVMode |= TVSet525p1024;
	    पूर्ण अन्यथा अगर(!(SiS_Pr->SiS_TVMode & (TVSetHiVision | TVSetYPbPr750p))) अणु
	       SiS_Pr->SiS_TVMode |= TVSetNTSC1024;
	    पूर्ण
	 पूर्ण
      पूर्ण

      SiS_Pr->SiS_TVMode |= TVRPLLDIV2XO;
      अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) &&
	 (SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
	 SiS_Pr->SiS_TVMode &= ~TVRPLLDIV2XO;
      पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p)) अणु
	 SiS_Pr->SiS_TVMode &= ~TVRPLLDIV2XO;
      पूर्ण अन्यथा अगर(!(SiS_Pr->SiS_VBType & VB_SIS30xBLV)) अणु
	 अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) अणु
	    SiS_Pr->SiS_TVMode &= ~TVRPLLDIV2XO;
	 पूर्ण
      पूर्ण

   पूर्ण

   SiS_Pr->SiS_VBInfo &= ~SetPALTV;
पूर्ण

/*********************************************/
/*               GET LCD INFO                */
/*********************************************/

अटल अचिन्हित लघु
SiS_GetBIOSLCDResInfo(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु temp = SiS_Pr->SiS_LCDResInfo;
   /* Translate my LCDResInfo to BIOS value */
   चयन(temp) अणु
   हाल Panel_1280x768_2: temp = Panel_1280x768;    अवरोध;
   हाल Panel_1280x800_2: temp = Panel_1280x800;    अवरोध;
   हाल Panel_1280x854:   temp = Panel661_1280x854; अवरोध;
   पूर्ण
   वापस temp;
पूर्ण

अटल व्योम
SiS_GetLCDInfoBIOS(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर_घोषित CONFIG_FB_SIS_315
   अचिन्हित अक्षर  *ROMAddr;
   अचिन्हित लघु temp;

   अगर((ROMAddr = GetLCDStructPtr661(SiS_Pr))) अणु
      अगर((temp = SISGETROMW(6)) != SiS_Pr->PanelHT) अणु
	 SiS_Pr->SiS_NeedRomModeData = true;
	 SiS_Pr->PanelHT  = temp;
      पूर्ण
      अगर((temp = SISGETROMW(8)) != SiS_Pr->PanelVT) अणु
	 SiS_Pr->SiS_NeedRomModeData = true;
	 SiS_Pr->PanelVT  = temp;
      पूर्ण
      SiS_Pr->PanelHRS = SISGETROMW(10);
      SiS_Pr->PanelHRE = SISGETROMW(12);
      SiS_Pr->PanelVRS = SISGETROMW(14);
      SiS_Pr->PanelVRE = SISGETROMW(16);
      SiS_Pr->PanelVCLKIdx315 = VCLK_CUSTOM_315;
      SiS_Pr->SiS_VCLKData[VCLK_CUSTOM_315].CLOCK =
	 SiS_Pr->SiS_VBVCLKData[VCLK_CUSTOM_315].CLOCK = (अचिन्हित लघु)((अचिन्हित अक्षर)ROMAddr[18]);
      SiS_Pr->SiS_VCLKData[VCLK_CUSTOM_315].SR2B =
	 SiS_Pr->SiS_VBVCLKData[VCLK_CUSTOM_315].Part4_A = ROMAddr[19];
      SiS_Pr->SiS_VCLKData[VCLK_CUSTOM_315].SR2C =
	 SiS_Pr->SiS_VBVCLKData[VCLK_CUSTOM_315].Part4_B = ROMAddr[20];

   पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम
SiS_CheckScaling(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु resinfo,
			स्थिर अचिन्हित अक्षर *nonscalingmodes)
अणु
   पूर्णांक i = 0;
   जबतक(nonscalingmodes[i] != 0xff) अणु
      अगर(nonscalingmodes[i++] == resinfo) अणु
	 अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) ||
	    (SiS_Pr->UsePanelScaler == -1)) अणु
	    SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
	 पूर्ण
	 अवरोध;
      पूर्ण
   पूर्ण
पूर्ण

व्योम
SiS_GetLCDResInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित लघु temp,modeflag,resinfo=0,modexres=0,modeyres=0;
  bool panelcanscale = false;
#अगर_घोषित CONFIG_FB_SIS_300
  अचिन्हित अक्षर *ROMAddr = SiS_Pr->VirtualRomBase;
  अटल स्थिर अचिन्हित अक्षर SiS300SeriesLCDRes[] =
          अणु 0,  1,  2,  3,  7,  4,  5,  8,
	    0,  0, 10,  0,  0,  0,  0, 15 पूर्ण;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
  अचिन्हित अक्षर   *myptr = शून्य;
#पूर्ण_अगर

  SiS_Pr->SiS_LCDResInfo  = 0;
  SiS_Pr->SiS_LCDTypeInfo = 0;
  SiS_Pr->SiS_LCDInfo     = 0;
  SiS_Pr->PanelHRS        = 999; /* HSync start */
  SiS_Pr->PanelHRE        = 999; /* HSync end */
  SiS_Pr->PanelVRS        = 999; /* VSync start */
  SiS_Pr->PanelVRE        = 999; /* VSync end */
  SiS_Pr->SiS_NeedRomModeData = false;

  /* Alternative 1600x1200@60 timing क्रम 1600x1200 LCDA */
  SiS_Pr->Alternate1600x1200 = false;

  अगर(!(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA))) वापस;

  modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

  अगर((ModeNo > 0x13) && (!SiS_Pr->UseCustomMode)) अणु
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
     modexres = SiS_Pr->SiS_ModeResInfo[resinfo].HTotal;
     modeyres = SiS_Pr->SiS_ModeResInfo[resinfo].VTotal;
  पूर्ण

  temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36);

  /* For broken BIOSes: Assume 1024x768 */
  अगर(temp == 0) temp = 0x02;

  अगर((SiS_Pr->ChipType >= SIS_661) || (SiS_Pr->SiS_ROMNew)) अणु
     SiS_Pr->SiS_LCDTypeInfo = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x39) & 0x7c) >> 2;
  पूर्ण अन्यथा अगर((SiS_Pr->ChipType < SIS_315H) || (SiS_Pr->ChipType >= SIS_661)) अणु
     SiS_Pr->SiS_LCDTypeInfo = temp >> 4;
  पूर्ण अन्यथा अणु
     SiS_Pr->SiS_LCDTypeInfo = (temp & 0x0F) - 1;
  पूर्ण
  temp &= 0x0f;
#अगर_घोषित CONFIG_FB_SIS_300
  अगर(SiS_Pr->ChipType < SIS_315H) अणु
     /* Very old BIOSes only know 7 sizes (NetVista 2179, 1.01g) */
     अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
        अगर(temp < 0x0f) temp &= 0x07;
     पूर्ण
     /* Translate 300 series LCDRes to 315 series क्रम unअगरied usage */
     temp = SiS300SeriesLCDRes[temp];
  पूर्ण
#पूर्ण_अगर

  /* Translate to our पूर्णांकernal types */
#अगर_घोषित CONFIG_FB_SIS_315
  अगर(SiS_Pr->ChipType == SIS_550) अणु
     अगर     (temp == Panel310_1152x768)  temp = Panel_320x240_2; /* Verअगरied working */
     अन्यथा अगर(temp == Panel310_320x240_2) temp = Panel_320x240_2;
     अन्यथा अगर(temp == Panel310_320x240_3) temp = Panel_320x240_3;
  पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_661) अणु
     अगर(temp == Panel661_1280x854)       temp = Panel_1280x854;
  पूर्ण
#पूर्ण_अगर

  अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु		/* SiS LVDS */
     अगर(temp == Panel310_1280x768) अणु
        temp = Panel_1280x768_2;
     पूर्ण
     अगर(SiS_Pr->SiS_ROMNew) अणु
	अगर(temp == Panel661_1280x800) अणु
	   temp = Panel_1280x800_2;
	पूर्ण
     पूर्ण
  पूर्ण

  SiS_Pr->SiS_LCDResInfo = temp;

#अगर_घोषित CONFIG_FB_SIS_300
  अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
     अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1366) अणु
	SiS_Pr->SiS_LCDResInfo = Panel_Barco1366;
     पूर्ण अन्यथा अगर(SiS_Pr->SiS_CustomT == CUT_PANEL848) अणु
	SiS_Pr->SiS_LCDResInfo = Panel_848x480;
     पूर्ण अन्यथा अगर(SiS_Pr->SiS_CustomT == CUT_PANEL856) अणु
	SiS_Pr->SiS_LCDResInfo = Panel_856x480;
     पूर्ण
  पूर्ण
#पूर्ण_अगर

  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
     अगर(SiS_Pr->SiS_LCDResInfo < SiS_Pr->SiS_PanelMin301)
	SiS_Pr->SiS_LCDResInfo = SiS_Pr->SiS_PanelMin301;
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_LCDResInfo < SiS_Pr->SiS_PanelMinLVDS)
	SiS_Pr->SiS_LCDResInfo = SiS_Pr->SiS_PanelMinLVDS;
  पूर्ण

  temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x37);
  SiS_Pr->SiS_LCDInfo = temp & ~0x000e;
  /* Need temp below! */

  /* These must/can't scale no matter what */
  चयन(SiS_Pr->SiS_LCDResInfo) अणु
  हाल Panel_320x240_1:
  हाल Panel_320x240_2:
  हाल Panel_320x240_3:
  हाल Panel_1280x960:
      SiS_Pr->SiS_LCDInfo &= ~DontExpandLCD;
      अवरोध;
  हाल Panel_640x480:
      SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
  पूर्ण

  panelcanscale = (bool)(SiS_Pr->SiS_LCDInfo & DontExpandLCD);

  अगर(!SiS_Pr->UsePanelScaler)          SiS_Pr->SiS_LCDInfo &= ~DontExpandLCD;
  अन्यथा अगर(SiS_Pr->UsePanelScaler == 1) SiS_Pr->SiS_LCDInfo |= DontExpandLCD;

  /* Dual link, Pass 1:1 BIOS शेष, etc. */
#अगर_घोषित CONFIG_FB_SIS_315
  अगर(SiS_Pr->ChipType >= SIS_661) अणु
     अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	अगर(temp & 0x08) SiS_Pr->SiS_LCDInfo |= LCDPass11;
     पूर्ण
     अगर(SiS_Pr->SiS_VBType & VB_SISDUALLINK) अणु
	अगर(SiS_Pr->SiS_ROMNew) अणु
	   अगर(temp & 0x02) SiS_Pr->SiS_LCDInfo |= LCDDualLink;
	पूर्ण अन्यथा अगर((myptr = GetLCDStructPtr661(SiS_Pr))) अणु
	   अगर(myptr[2] & 0x01) SiS_Pr->SiS_LCDInfo |= LCDDualLink;
	पूर्ण
     पूर्ण
  पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x39) & 0x01) SiS_Pr->SiS_LCDInfo |= LCDPass11;
     पूर्ण
     अगर((SiS_Pr->SiS_ROMNew) && (!(SiS_Pr->PanelSelfDetected))) अणु
	SiS_Pr->SiS_LCDInfo &= ~(LCDRGB18Bit);
	temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x35);
	अगर(temp & 0x01) SiS_Pr->SiS_LCDInfo |= LCDRGB18Bit;
	अगर(SiS_Pr->SiS_VBType & VB_SISDUALLINK) अणु
	   अगर(temp & 0x02) SiS_Pr->SiS_LCDInfo |= LCDDualLink;
	पूर्ण
     पूर्ण अन्यथा अगर(!(SiS_Pr->SiS_ROMNew)) अणु
	अगर(SiS_Pr->SiS_VBType & VB_SISDUALLINK) अणु
	   अगर((SiS_Pr->SiS_CustomT == CUT_CLEVO1024) &&
	      (SiS_Pr->SiS_LCDResInfo == Panel_1024x768)) अणु
	      SiS_Pr->SiS_LCDInfo |= LCDDualLink;
	   पूर्ण
	   अगर((SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) ||
	      (SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) ||
	      (SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) ||
	      (SiS_Pr->SiS_LCDResInfo == Panel_1680x1050)) अणु
	      SiS_Pr->SiS_LCDInfo |= LCDDualLink;
	   पूर्ण
	पूर्ण
     पूर्ण
  पूर्ण
#पूर्ण_अगर

  /* Pass 1:1 */
  अगर((SiS_Pr->SiS_IF_DEF_LVDS == 1) || (SiS_Pr->SiS_VBType & VB_NoLCD)) अणु
     /* Always center screen on LVDS (अगर scaling is disabled) */
     SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
     अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	/* Always center screen on SiS LVDS (अगर scaling is disabled) */
	SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
     पूर्ण अन्यथा अणु
	/* By शेष, pass 1:1 on SiS TMDS (अगर scaling is supported) */
	अगर(panelcanscale)             SiS_Pr->SiS_LCDInfo |= LCDPass11;
	अगर(SiS_Pr->CenterScreen == 1) SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
     पूर्ण
  पूर्ण

  SiS_Pr->PanelVCLKIdx300 = VCLK65_300;
  SiS_Pr->PanelVCLKIdx315 = VCLK108_2_315;

  चयन(SiS_Pr->SiS_LCDResInfo) अणु
     हाल Panel_320x240_1:
     हाल Panel_320x240_2:
     हाल Panel_320x240_3:  SiS_Pr->PanelXRes =  640; SiS_Pr->PanelYRes =  480;
			    SiS_Pr->PanelVRS  =   24; SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx300 = VCLK28;
			    SiS_Pr->PanelVCLKIdx315 = VCLK28;
			    अवरोध;
     हाल Panel_640x480:    SiS_Pr->PanelXRes =  640; SiS_Pr->PanelYRes =  480;
						      SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx300 = VCLK28;
			    SiS_Pr->PanelVCLKIdx315 = VCLK28;
			    अवरोध;
     हाल Panel_800x600:    SiS_Pr->PanelXRes =  800; SiS_Pr->PanelYRes =  600;
     			    SiS_Pr->PanelHT   = 1056; SiS_Pr->PanelVT   =  628;
			    SiS_Pr->PanelHRS  =   40; SiS_Pr->PanelHRE  =  128;
			    SiS_Pr->PanelVRS  =    1; SiS_Pr->PanelVRE  =    4;
			    SiS_Pr->PanelVCLKIdx300 = VCLK40;
			    SiS_Pr->PanelVCLKIdx315 = VCLK40;
			    अवरोध;
     हाल Panel_1024x600:   SiS_Pr->PanelXRes = 1024; SiS_Pr->PanelYRes =  600;
			    SiS_Pr->PanelHT   = 1344; SiS_Pr->PanelVT   =  800;
			    SiS_Pr->PanelHRS  =   24; SiS_Pr->PanelHRE  =  136;
			    SiS_Pr->PanelVRS  =    2 /* 88 */ ; SiS_Pr->PanelVRE  =    6;
			    SiS_Pr->PanelVCLKIdx300 = VCLK65_300;
			    SiS_Pr->PanelVCLKIdx315 = VCLK65_315;
			    अवरोध;
     हाल Panel_1024x768:   SiS_Pr->PanelXRes = 1024; SiS_Pr->PanelYRes =  768;
			    SiS_Pr->PanelHT   = 1344; SiS_Pr->PanelVT   =  806;
			    SiS_Pr->PanelHRS  =   24; SiS_Pr->PanelHRE  =  136;
			    SiS_Pr->PanelVRS  =    3; SiS_Pr->PanelVRE  =    6;
			    अगर(SiS_Pr->ChipType < SIS_315H) अणु
			       SiS_Pr->PanelHRS = 23;
						      SiS_Pr->PanelVRE  =    5;
			    पूर्ण
			    SiS_Pr->PanelVCLKIdx300 = VCLK65_300;
			    SiS_Pr->PanelVCLKIdx315 = VCLK65_315;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1152x768:   SiS_Pr->PanelXRes = 1152; SiS_Pr->PanelYRes =  768;
			    SiS_Pr->PanelHT   = 1344; SiS_Pr->PanelVT   =  806;
			    SiS_Pr->PanelHRS  =   24; SiS_Pr->PanelHRE  =  136;
			    SiS_Pr->PanelVRS  =    3; SiS_Pr->PanelVRE  =    6;
			    अगर(SiS_Pr->ChipType < SIS_315H) अणु
			       SiS_Pr->PanelHRS = 23;
						      SiS_Pr->PanelVRE  =    5;
			    पूर्ण
			    SiS_Pr->PanelVCLKIdx300 = VCLK65_300;
			    SiS_Pr->PanelVCLKIdx315 = VCLK65_315;
			    अवरोध;
     हाल Panel_1152x864:   SiS_Pr->PanelXRes = 1152; SiS_Pr->PanelYRes =  864;
			    अवरोध;
     हाल Panel_1280x720:   SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes =  720;
			    SiS_Pr->PanelHT   = 1650; SiS_Pr->PanelVT   =  750;
			    SiS_Pr->PanelHRS  =  110; SiS_Pr->PanelHRE  =   40;
			    SiS_Pr->PanelVRS  =    5; SiS_Pr->PanelVRE  =    5;
			    SiS_Pr->PanelVCLKIdx315 = VCLK_1280x720;
			    /* Data above क्रम TMDS (projector); get from BIOS क्रम LVDS */
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1280x768:   SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes =  768;
			    अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
			       SiS_Pr->PanelHT   = 1408; SiS_Pr->PanelVT   =  806;
			       SiS_Pr->PanelVCLKIdx300 = VCLK81_300; /* ? */
			       SiS_Pr->PanelVCLKIdx315 = VCLK81_315; /* ? */
			    पूर्ण अन्यथा अणु
			       SiS_Pr->PanelHT   = 1688; SiS_Pr->PanelVT   =  802;
			       SiS_Pr->PanelHRS  =   48; SiS_Pr->PanelHRE  =  112;
			       SiS_Pr->PanelVRS  =    3; SiS_Pr->PanelVRE  =    6;
			       SiS_Pr->PanelVCLKIdx300 = VCLK81_300;
			       SiS_Pr->PanelVCLKIdx315 = VCLK81_315;
			    पूर्ण
			    अवरोध;
     हाल Panel_1280x768_2: SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes =  768;
			    SiS_Pr->PanelHT   = 1660; SiS_Pr->PanelVT   =  806;
			    SiS_Pr->PanelHRS  =   48; SiS_Pr->PanelHRE  =  112;
			    SiS_Pr->PanelVRS  =    3; SiS_Pr->PanelVRE  =    6;
			    SiS_Pr->PanelVCLKIdx315 = VCLK_1280x768_2;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1280x800:   SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes =  800;
			    SiS_Pr->PanelHT   = 1408; SiS_Pr->PanelVT   =  816;
			    SiS_Pr->PanelHRS   =  21; SiS_Pr->PanelHRE  =   24;
			    SiS_Pr->PanelVRS   =   4; SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx315 = VCLK_1280x800_315;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1280x800_2: SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes =  800;
			    SiS_Pr->PanelHT   = 1552; SiS_Pr->PanelVT   =  812;
			    SiS_Pr->PanelHRS   =  48; SiS_Pr->PanelHRE  =  112;
			    SiS_Pr->PanelVRS   =   4; SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx315 = VCLK_1280x800_315_2;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1280x854:   SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes =  854;
			    SiS_Pr->PanelHT   = 1664; SiS_Pr->PanelVT   =  861;
			    SiS_Pr->PanelHRS   =  16; SiS_Pr->PanelHRE  =  112;
			    SiS_Pr->PanelVRS   =   1; SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx315 = VCLK_1280x854;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1280x960:   SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes =  960;
			    SiS_Pr->PanelHT   = 1800; SiS_Pr->PanelVT   = 1000;
			    SiS_Pr->PanelVCLKIdx300 = VCLK108_3_300;
			    SiS_Pr->PanelVCLKIdx315 = VCLK108_3_315;
			    अगर(resinfo == SIS_RI_1280x1024) अणु
			       SiS_Pr->PanelVCLKIdx300 = VCLK100_300;
			       SiS_Pr->PanelVCLKIdx315 = VCLK100_315;
			    पूर्ण
			    अवरोध;
     हाल Panel_1280x1024:  SiS_Pr->PanelXRes = 1280; SiS_Pr->PanelYRes = 1024;
			    SiS_Pr->PanelHT   = 1688; SiS_Pr->PanelVT   = 1066;
			    SiS_Pr->PanelHRS  =   48; SiS_Pr->PanelHRE  =  112;
			    SiS_Pr->PanelVRS  =    1; SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx300 = VCLK108_3_300;
			    SiS_Pr->PanelVCLKIdx315 = VCLK108_2_315;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1400x1050:  SiS_Pr->PanelXRes = 1400; SiS_Pr->PanelYRes = 1050;
			    SiS_Pr->PanelHT   = 1688; SiS_Pr->PanelVT   = 1066;
			    SiS_Pr->PanelHRS  =   48; SiS_Pr->PanelHRE  =  112;
			    SiS_Pr->PanelVRS  =    1; SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx315 = VCLK108_2_315;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1600x1200:  SiS_Pr->PanelXRes = 1600; SiS_Pr->PanelYRes = 1200;
			    SiS_Pr->PanelHT   = 2160; SiS_Pr->PanelVT   = 1250;
			    SiS_Pr->PanelHRS  =   64; SiS_Pr->PanelHRE  =  192;
			    SiS_Pr->PanelVRS  =    1; SiS_Pr->PanelVRE  =    3;
			    SiS_Pr->PanelVCLKIdx315 = VCLK162_315;
			    अगर(SiS_Pr->SiS_VBType & VB_SISTMDSLCDA) अणु
			       अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
				  SiS_Pr->PanelHT  = 1760; SiS_Pr->PanelVT  = 1235;
				  SiS_Pr->PanelHRS =   48; SiS_Pr->PanelHRE =   32;
				  SiS_Pr->PanelVRS =    2; SiS_Pr->PanelVRE =    4;
				  SiS_Pr->PanelVCLKIdx315 = VCLK130_315;
				  SiS_Pr->Alternate1600x1200 = true;
			       पूर्ण
			    पूर्ण अन्यथा अगर(SiS_Pr->SiS_IF_DEF_LVDS) अणु
			       SiS_Pr->PanelHT  = 2048; SiS_Pr->PanelVT  = 1320;
			       SiS_Pr->PanelHRS = SiS_Pr->PanelHRE = 999;
			       SiS_Pr->PanelVRS = SiS_Pr->PanelVRE = 999;
			    पूर्ण
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_1680x1050:  SiS_Pr->PanelXRes = 1680; SiS_Pr->PanelYRes = 1050;
			    SiS_Pr->PanelHT   = 1900; SiS_Pr->PanelVT   = 1066;
			    SiS_Pr->PanelHRS  =   26; SiS_Pr->PanelHRE  =   76;
			    SiS_Pr->PanelVRS  =    3; SiS_Pr->PanelVRE  =    6;
			    SiS_Pr->PanelVCLKIdx315 = VCLK121_315;
			    SiS_GetLCDInfoBIOS(SiS_Pr);
			    अवरोध;
     हाल Panel_Barco1366:  SiS_Pr->PanelXRes = 1360; SiS_Pr->PanelYRes = 1024;
			    SiS_Pr->PanelHT   = 1688; SiS_Pr->PanelVT   = 1066;
			    अवरोध;
     हाल Panel_848x480:    SiS_Pr->PanelXRes =  848; SiS_Pr->PanelYRes =  480;
			    SiS_Pr->PanelHT   = 1088; SiS_Pr->PanelVT   =  525;
			    अवरोध;
     हाल Panel_856x480:    SiS_Pr->PanelXRes =  856; SiS_Pr->PanelYRes =  480;
			    SiS_Pr->PanelHT   = 1088; SiS_Pr->PanelVT   =  525;
			    अवरोध;
     हाल Panel_Custom:     SiS_Pr->PanelXRes = SiS_Pr->CP_MaxX;
			    SiS_Pr->PanelYRes = SiS_Pr->CP_MaxY;
			    SiS_Pr->PanelHT   = SiS_Pr->CHTotal;
			    SiS_Pr->PanelVT   = SiS_Pr->CVTotal;
			    अगर(SiS_Pr->CP_PreferredIndex != -1) अणु
			       SiS_Pr->PanelXRes = SiS_Pr->CP_HDisplay[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelYRes = SiS_Pr->CP_VDisplay[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelHT   = SiS_Pr->CP_HTotal[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelVT   = SiS_Pr->CP_VTotal[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelHRS  = SiS_Pr->CP_HSyncStart[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelHRE  = SiS_Pr->CP_HSyncEnd[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelVRS  = SiS_Pr->CP_VSyncStart[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelVRE  = SiS_Pr->CP_VSyncEnd[SiS_Pr->CP_PreferredIndex];
			       SiS_Pr->PanelHRS -= SiS_Pr->PanelXRes;
			       SiS_Pr->PanelHRE -= SiS_Pr->PanelHRS;
			       SiS_Pr->PanelVRS -= SiS_Pr->PanelYRes;
			       SiS_Pr->PanelVRE -= SiS_Pr->PanelVRS;
			       अगर(SiS_Pr->CP_PrefClock) अणु
				  पूर्णांक idx;
				  SiS_Pr->PanelVCLKIdx315 = VCLK_CUSTOM_315;
				  SiS_Pr->PanelVCLKIdx300 = VCLK_CUSTOM_300;
				  अगर(SiS_Pr->ChipType < SIS_315H) idx = VCLK_CUSTOM_300;
				  अन्यथा				   idx = VCLK_CUSTOM_315;
				  SiS_Pr->SiS_VCLKData[idx].CLOCK =
				     SiS_Pr->SiS_VBVCLKData[idx].CLOCK = SiS_Pr->CP_PrefClock;
				  SiS_Pr->SiS_VCLKData[idx].SR2B =
				     SiS_Pr->SiS_VBVCLKData[idx].Part4_A = SiS_Pr->CP_PrefSR2B;
				  SiS_Pr->SiS_VCLKData[idx].SR2C =
				     SiS_Pr->SiS_VBVCLKData[idx].Part4_B = SiS_Pr->CP_PrefSR2C;
			       पूर्ण
			    पूर्ण
			    अवरोध;
     शेष:		    SiS_Pr->PanelXRes = 1024; SiS_Pr->PanelYRes =  768;
			    SiS_Pr->PanelHT   = 1344; SiS_Pr->PanelVT   =  806;
			    अवरोध;
  पूर्ण

  /* Special हालs */
  अगर( (SiS_Pr->SiS_IF_DEF_FSTN)              ||
      (SiS_Pr->SiS_IF_DEF_DSTN)              ||
      (SiS_Pr->SiS_CustomT == CUT_BARCO1366) ||
      (SiS_Pr->SiS_CustomT == CUT_BARCO1024) ||
      (SiS_Pr->SiS_CustomT == CUT_PANEL848)  ||
      (SiS_Pr->SiS_CustomT == CUT_PANEL856) ) अणु
     SiS_Pr->PanelHRS = 999;
     SiS_Pr->PanelHRE = 999;
  पूर्ण

  अगर( (SiS_Pr->SiS_CustomT == CUT_BARCO1366) ||
      (SiS_Pr->SiS_CustomT == CUT_BARCO1024) ||
      (SiS_Pr->SiS_CustomT == CUT_PANEL848)  ||
      (SiS_Pr->SiS_CustomT == CUT_PANEL856) ) अणु
     SiS_Pr->PanelVRS = 999;
     SiS_Pr->PanelVRE = 999;
  पूर्ण

  /* DontExpand overrule */
  अगर((SiS_Pr->SiS_VBType & VB_SISVB) && (!(SiS_Pr->SiS_VBType & VB_NoLCD))) अणु

     अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) && (modeflag & NoSupportLCDScale)) अणु
	/* No scaling क्रम this mode on any panel (LCD=CRT2)*/
	SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
     पूर्ण

     चयन(SiS_Pr->SiS_LCDResInfo) अणु

     हाल Panel_Custom:
     हाल Panel_1152x864:
     हाल Panel_1280x768:	/* TMDS only */
	SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
	अवरोध;

     हाल Panel_800x600: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, 0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अवरोध;
     पूर्ण
     हाल Panel_1024x768: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अवरोध;
     पूर्ण
     हाल Panel_1280x720: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अगर(SiS_Pr->PanelHT == 1650) अणु
	   SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
	पूर्ण
	अवरोध;
     पूर्ण
     हाल Panel_1280x768_2: अणु  /* LVDS only */
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   SIS_RI_1152x768,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	चयन(resinfo) अणु
	हाल SIS_RI_1280x720:  अगर(SiS_Pr->UsePanelScaler == -1) अणु
				  SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
			       पूर्ण
			       अवरोध;
	पूर्ण
	अवरोध;
     पूर्ण
     हाल Panel_1280x800: अणु  	/* SiS TMDS special (Averatec 6200 series) */
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   SIS_RI_1152x768,SIS_RI_1280x720,SIS_RI_1280x768,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अवरोध;
     पूर्ण
     हाल Panel_1280x800_2:  अणु 	/* SiS LVDS */
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   SIS_RI_1152x768,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	चयन(resinfo) अणु
	हाल SIS_RI_1280x720:
	हाल SIS_RI_1280x768:  अगर(SiS_Pr->UsePanelScaler == -1) अणु
				  SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
			       पूर्ण
			       अवरोध;
	पूर्ण
	अवरोध;
     पूर्ण
     हाल Panel_1280x854: अणु  	/* SiS LVDS */
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   SIS_RI_1152x768,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	चयन(resinfo) अणु
	हाल SIS_RI_1280x720:
	हाल SIS_RI_1280x768:
	हाल SIS_RI_1280x800:  अगर(SiS_Pr->UsePanelScaler == -1) अणु
				  SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
			       पूर्ण
			       अवरोध;
	पूर्ण
	अवरोध;
     पूर्ण
     हाल Panel_1280x960: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   SIS_RI_1152x768,SIS_RI_1152x864,SIS_RI_1280x720,SIS_RI_1280x768,SIS_RI_1280x800,
	   SIS_RI_1280x854,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अवरोध;
     पूर्ण
     हाल Panel_1280x1024: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	   SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	   SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	   SIS_RI_1152x768,SIS_RI_1152x864,SIS_RI_1280x720,SIS_RI_1280x768,SIS_RI_1280x800,
	   SIS_RI_1280x854,SIS_RI_1280x960,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अवरोध;
     पूर्ण
     हाल Panel_1400x1050: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	     SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	     SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	     SIS_RI_1152x768,SIS_RI_1152x864,SIS_RI_1280x768,SIS_RI_1280x800,SIS_RI_1280x854,
	     SIS_RI_1280x960,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	चयन(resinfo) अणु
	हाल SIS_RI_1280x720:  अगर(SiS_Pr->UsePanelScaler == -1) अणु
				  SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
			       पूर्ण
			       अवरोध;
	हाल SIS_RI_1280x1024: SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
			       अवरोध;
	पूर्ण
	अवरोध;
     पूर्ण
     हाल Panel_1600x1200: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	     SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	     SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	     SIS_RI_1152x768,SIS_RI_1152x864,SIS_RI_1280x720,SIS_RI_1280x768,SIS_RI_1280x800,
	     SIS_RI_1280x854,SIS_RI_1280x960,SIS_RI_1360x768,SIS_RI_1360x1024,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अवरोध;
     पूर्ण
     हाल Panel_1680x1050: अणु
	अटल स्थिर अचिन्हित अक्षर nonscalingmodes[] = अणु
	     SIS_RI_720x480, SIS_RI_720x576, SIS_RI_768x576, SIS_RI_800x480, SIS_RI_848x480,
	     SIS_RI_856x480, SIS_RI_960x540, SIS_RI_960x600, SIS_RI_1024x576,SIS_RI_1024x600,
	     SIS_RI_1152x768,SIS_RI_1152x864,SIS_RI_1280x854,SIS_RI_1280x960,SIS_RI_1360x768,
	     SIS_RI_1360x1024,0xff
	पूर्ण;
	SiS_CheckScaling(SiS_Pr, resinfo, nonscalingmodes);
	अवरोध;
     पूर्ण
     पूर्ण
  पूर्ण

#अगर_घोषित CONFIG_FB_SIS_300
  अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
     अगर(SiS_Pr->SiS_CustomT == CUT_PANEL848 || SiS_Pr->SiS_CustomT == CUT_PANEL856) अणु
	SiS_Pr->SiS_LCDInfo = 0x80 | 0x40 | 0x20;   /* neg h/v sync, RGB24(D0 = 0) */
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->ChipType < SIS_315H) अणु
     अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
	अगर(SiS_Pr->SiS_UseROM) अणु
	   अगर((ROMAddr[0x233] == 0x12) && (ROMAddr[0x234] == 0x34)) अणु
	      अगर(!(ROMAddr[0x235] & 0x02)) अणु
		 SiS_Pr->SiS_LCDInfo &= (~DontExpandLCD);
	      पूर्ण
	   पूर्ण
	पूर्ण
     पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	अगर((SiS_Pr->SiS_SetFlag & SetDOSMode) && ((ModeNo == 0x03) || (ModeNo == 0x10))) अणु
	   SiS_Pr->SiS_LCDInfo &= (~DontExpandLCD);
	पूर्ण
     पूर्ण
  पूर्ण
#पूर्ण_अगर

  /* Special हालs */

  अगर(modexres == SiS_Pr->PanelXRes && modeyres == SiS_Pr->PanelYRes) अणु
     SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
  पूर्ण

  अगर(SiS_Pr->SiS_IF_DEF_TRUMPION) अणु
     SiS_Pr->SiS_LCDInfo |= (DontExpandLCD | LCDPass11);
  पूर्ण

  चयन(SiS_Pr->SiS_LCDResInfo) अणु
  हाल Panel_640x480:
     SiS_Pr->SiS_LCDInfo |= (DontExpandLCD | LCDPass11);
     अवरोध;
  हाल Panel_1280x800:
     /* Don't pass 1:1 by शेष (TMDS special) */
     अगर(SiS_Pr->CenterScreen == -1) SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
     अवरोध;
  हाल Panel_1280x960:
     SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
     अवरोध;
  हाल Panel_Custom:
     अगर((!SiS_Pr->CP_PrefClock) ||
        (modexres > SiS_Pr->PanelXRes) || (modeyres > SiS_Pr->PanelYRes)) अणु
        SiS_Pr->SiS_LCDInfo |= LCDPass11;
     पूर्ण
     अवरोध;
  पूर्ण

  अगर((SiS_Pr->UseCustomMode) || (SiS_Pr->SiS_CustomT == CUT_UNKNOWNLCD)) अणु
     SiS_Pr->SiS_LCDInfo |= (DontExpandLCD | LCDPass11);
  पूर्ण

  /* (In)validate LCDPass11 flag */
  अगर(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) अणु
     SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
  पूर्ण

  /* LVDS DDA */
  अगर(!((SiS_Pr->ChipType < SIS_315H) && (SiS_Pr->SiS_SetFlag & SetDOSMode))) अणु

     अगर((SiS_Pr->SiS_IF_DEF_LVDS == 1) || (SiS_Pr->SiS_VBType & VB_NoLCD)) अणु
	अगर(SiS_Pr->SiS_IF_DEF_TRUMPION == 0) अणु
	   अगर(ModeNo == 0x12) अणु
	      अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) अणु
		 SiS_Pr->SiS_SetFlag |= EnableLVDSDDA;
	      पूर्ण
	   पूर्ण अन्यथा अगर(ModeNo > 0x13) अणु
	      अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x600) अणु
		 अगर(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) अणु
		    अगर((resinfo == SIS_RI_800x600) || (resinfo == SIS_RI_400x300)) अणु
		       SiS_Pr->SiS_SetFlag |= EnableLVDSDDA;
		    पूर्ण
		 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण
     पूर्ण

     अगर(modeflag & HalfDCLK) अणु
	अगर(SiS_Pr->SiS_IF_DEF_TRUMPION == 1) अणु
	   SiS_Pr->SiS_SetFlag |= EnableLVDSDDA;
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	   SiS_Pr->SiS_SetFlag |= EnableLVDSDDA;
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_640x480) अणु
	   SiS_Pr->SiS_SetFlag |= EnableLVDSDDA;
	पूर्ण अन्यथा अगर(ModeNo > 0x13) अणु
	   अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	      अगर(resinfo == SIS_RI_512x384) SiS_Pr->SiS_SetFlag |= EnableLVDSDDA;
	   पूर्ण अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_800x600) अणु
	      अगर(resinfo == SIS_RI_400x300) SiS_Pr->SiS_SetFlag |= EnableLVDSDDA;
	   पूर्ण
	पूर्ण
     पूर्ण

  पूर्ण

  /* VESA timing */
  अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
     अगर(SiS_Pr->SiS_VBInfo & SetNotSimuMode) अणु
	SiS_Pr->SiS_SetFlag |= LCDVESATiming;
     पूर्ण
  पूर्ण अन्यथा अणु
     SiS_Pr->SiS_SetFlag |= LCDVESATiming;
  पूर्ण

#अगर 0
  prपूर्णांकk(KERN_DEBUG "sisfb: (LCDInfo=0x%04x LCDResInfo=0x%02x LCDTypeInfo=0x%02x)\n",
	SiS_Pr->SiS_LCDInfo, SiS_Pr->SiS_LCDResInfo, SiS_Pr->SiS_LCDTypeInfo);
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*                 GET VCLK                  */
/*********************************************/

अचिन्हित लघु
SiS_GetVCLK2Ptr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु CRT2Index, VCLKIndex = 0, VCLKIndexGEN = 0, VCLKIndexGENCRT = 0;
  अचिन्हित लघु resinfo, tempbx;
  स्थिर अचिन्हित अक्षर *CHTVVCLKPtr = शून्य;

  अगर(ModeNo <= 0x13) अणु
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
     CRT2Index = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
     VCLKIndexGEN = (SiS_GetRegByte((SiS_Pr->SiS_P3ca+0x02)) >> 2) & 0x03;
     VCLKIndexGENCRT = VCLKIndexGEN;
  पूर्ण अन्यथा अणु
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
     CRT2Index = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
     VCLKIndexGEN = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK;
     VCLKIndexGENCRT = SiS_GetRefCRTVCLK(SiS_Pr, RefreshRateTableIndex,
		(SiS_Pr->SiS_SetFlag & ProgrammingCRT2) ? SiS_Pr->SiS_UseWideCRT2 : SiS_Pr->SiS_UseWide);
  पूर्ण

  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु    /* 30x/B/LV */

     अगर(SiS_Pr->SiS_SetFlag & ProgrammingCRT2) अणु

	CRT2Index >>= 6;
	अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु      	/*  LCD */

	   अगर(SiS_Pr->ChipType < SIS_315H) अणु
	      VCLKIndex = SiS_Pr->PanelVCLKIdx300;
	      अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
		 VCLKIndex = VCLKIndexGEN;
	      पूर्ण
	   पूर्ण अन्यथा अणु
	      VCLKIndex = SiS_Pr->PanelVCLKIdx315;
	      अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
		 चयन(resinfo) अणु
		 /* Correct those whose IndexGEN करोesn't match VBVCLK array */
		 हाल SIS_RI_720x480:  VCLKIndex = VCLK_720x480;  अवरोध;
		 हाल SIS_RI_720x576:  VCLKIndex = VCLK_720x576;  अवरोध;
		 हाल SIS_RI_768x576:  VCLKIndex = VCLK_768x576;  अवरोध;
		 हाल SIS_RI_848x480:  VCLKIndex = VCLK_848x480;  अवरोध;
		 हाल SIS_RI_856x480:  VCLKIndex = VCLK_856x480;  अवरोध;
		 हाल SIS_RI_800x480:  VCLKIndex = VCLK_800x480;  अवरोध;
		 हाल SIS_RI_1024x576: VCLKIndex = VCLK_1024x576; अवरोध;
		 हाल SIS_RI_1152x864: VCLKIndex = VCLK_1152x864; अवरोध;
		 हाल SIS_RI_1280x720: VCLKIndex = VCLK_1280x720; अवरोध;
		 हाल SIS_RI_1360x768: VCLKIndex = VCLK_1360x768; अवरोध;
		 शेष:              VCLKIndex = VCLKIndexGEN;
		 पूर्ण

		 अगर(ModeNo <= 0x13) अणु
		    अगर(SiS_Pr->ChipType <= SIS_315PRO) अणु
		       अगर(SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC == 1) VCLKIndex = 0x42;
		    पूर्ण अन्यथा अणु
		       अगर(SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC == 1) VCLKIndex = 0x00;
		    पूर्ण
		 पूर्ण
		 अगर(SiS_Pr->ChipType <= SIS_315PRO) अणु
		    अगर(VCLKIndex == 0) VCLKIndex = 0x41;
		    अगर(VCLKIndex == 1) VCLKIndex = 0x43;
		    अगर(VCLKIndex == 4) VCLKIndex = 0x44;
		 पूर्ण
	      पूर्ण
	   पूर्ण

	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु                 	/*  TV */

	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	      अगर(SiS_Pr->SiS_TVMode & TVRPLLDIV2XO) 	   VCLKIndex = HiTVVCLKDIV2;
	      अन्यथा                                  	   VCLKIndex = HiTVVCLK;
	      अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)     VCLKIndex = HiTVSimuVCLK;
	   पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)  VCLKIndex = YPbPr750pVCLK;
	   अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p)    VCLKIndex = TVVCLKDIV2;
	   अन्यथा अगर(SiS_Pr->SiS_TVMode & TVRPLLDIV2XO)      VCLKIndex = TVVCLKDIV2;
	   अन्यथा						   VCLKIndex = TVVCLK;

	   अगर(SiS_Pr->ChipType < SIS_315H) VCLKIndex += TVCLKBASE_300;
	   अन्यथा				   VCLKIndex += TVCLKBASE_315;

	पूर्ण अन्यथा अणु							/* VGA2 */

	   VCLKIndex = VCLKIndexGENCRT;
	   अगर(SiS_Pr->ChipType < SIS_315H) अणु
	      अगर(ModeNo > 0x13) अणु
		 अगर( (SiS_Pr->ChipType == SIS_630) &&
		     (SiS_Pr->ChipRevision >= 0x30)) अणु
		    अगर(VCLKIndex == 0x14) VCLKIndex = 0x34;
		 पूर्ण
		 /* Better VGA2 घड़ी क्रम 1280x1024@75 */
		 अगर(VCLKIndex == 0x17) VCLKIndex = 0x45;
	      पूर्ण
	   पूर्ण
	पूर्ण

     पूर्ण अन्यथा अणु   /* If not programming CRT2 */

	VCLKIndex = VCLKIndexGENCRT;
	अगर(SiS_Pr->ChipType < SIS_315H) अणु
	   अगर(ModeNo > 0x13) अणु
	      अगर( (SiS_Pr->ChipType != SIS_630) &&
		  (SiS_Pr->ChipType != SIS_300) ) अणु
		 अगर(VCLKIndex == 0x1b) VCLKIndex = 0x48;
	      पूर्ण
	   पूर्ण
	पूर्ण
     पूर्ण

  पूर्ण अन्यथा अणु       /*   LVDS  */

     VCLKIndex = CRT2Index;

     अगर(SiS_Pr->SiS_SetFlag & ProgrammingCRT2) अणु

	अगर( (SiS_Pr->SiS_IF_DEF_CH70xx != 0) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV) ) अणु

	   VCLKIndex &= 0x1f;
	   tempbx = 0;
	   अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) tempbx += 1;
	   अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
	      tempbx += 2;
	      अगर(SiS_Pr->SiS_ModeType > ModeVGA) अणु
		 अगर(SiS_Pr->SiS_CHSOverScan) tempbx = 8;
	      पूर्ण
	      अगर(SiS_Pr->SiS_TVMode & TVSetPALM) अणु
		 tempbx = 4;
		 अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) tempbx += 1;
	      पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPALN) अणु
		 tempbx = 6;
		 अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) tempbx += 1;
	      पूर्ण
	   पूर्ण
	   चयन(tempbx) अणु
	     हाल  0: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKUNTSC;  अवरोध;
	     हाल  1: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKONTSC;  अवरोध;
	     हाल  2: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKUPAL;   अवरोध;
	     हाल  3: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKOPAL;   अवरोध;
	     हाल  4: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKUPALM;  अवरोध;
	     हाल  5: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKOPALM;  अवरोध;
	     हाल  6: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKUPALN;  अवरोध;
	     हाल  7: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKOPALN;  अवरोध;
	     हाल  8: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKSOPAL;  अवरोध;
	     शेष: CHTVVCLKPtr = SiS_Pr->SiS_CHTVVCLKOPAL;   अवरोध;
	   पूर्ण
	   VCLKIndex = CHTVVCLKPtr[VCLKIndex];

	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु

	   अगर(SiS_Pr->ChipType < SIS_315H) अणु
	      VCLKIndex = SiS_Pr->PanelVCLKIdx300;
	   पूर्ण अन्यथा अणु
	      VCLKIndex = SiS_Pr->PanelVCLKIdx315;
	   पूर्ण

#अगर_घोषित CONFIG_FB_SIS_300
	   /* Special Timing: Barco iQ Pro R series */
	   अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1366) VCLKIndex = 0x44;

	   /* Special Timing: 848x480 and 856x480 parallel lvds panels */
	   अगर(SiS_Pr->SiS_CustomT == CUT_PANEL848 || SiS_Pr->SiS_CustomT == CUT_PANEL856) अणु
	      अगर(SiS_Pr->ChipType < SIS_315H) अणु
		 VCLKIndex = VCLK34_300;
		 /* अगर(resinfo == SIS_RI_1360x768) VCLKIndex = ?; */
	      पूर्ण अन्यथा अणु
		 VCLKIndex = VCLK34_315;
		 /* अगर(resinfo == SIS_RI_1360x768) VCLKIndex = ?; */
	      पूर्ण
	   पूर्ण
#पूर्ण_अगर

	पूर्ण अन्यथा अणु

	   VCLKIndex = VCLKIndexGENCRT;
	   अगर(SiS_Pr->ChipType < SIS_315H) अणु
	      अगर(ModeNo > 0x13) अणु
		 अगर( (SiS_Pr->ChipType == SIS_630) &&
		     (SiS_Pr->ChipRevision >= 0x30) ) अणु
		    अगर(VCLKIndex == 0x14) VCLKIndex = 0x2e;
		 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण

     पूर्ण अन्यथा अणु  /* अगर not programming CRT2 */

	VCLKIndex = VCLKIndexGENCRT;
	अगर(SiS_Pr->ChipType < SIS_315H) अणु
	   अगर(ModeNo > 0x13) अणु
	      अगर( (SiS_Pr->ChipType != SIS_630) &&
		  (SiS_Pr->ChipType != SIS_300) ) अणु
		 अगर(VCLKIndex == 0x1b) VCLKIndex = 0x48;
	      पूर्ण
#अगर 0
	      अगर(SiS_Pr->ChipType == SIS_730) अणु
		 अगर(VCLKIndex == 0x0b) VCLKIndex = 0x40;   /* 1024x768-70 */
		 अगर(VCLKIndex == 0x0d) VCLKIndex = 0x41;   /* 1024x768-75 */
	      पूर्ण
#पूर्ण_अगर
	   पूर्ण
        पूर्ण

     पूर्ण

  पूर्ण

  वापस VCLKIndex;
पूर्ण

/*********************************************/
/*        SET CRT2 MODE TYPE REGISTERS       */
/*********************************************/

अटल व्योम
SiS_SetCRT2ModeRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित लघु i, j, modeflag, tempah=0;
  लघु tempcl;
#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
  अचिन्हित लघु tempbl;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु tempah2, tempbl2;
#पूर्ण_अगर

  modeflag = SiS_GetModeFlag(SiS_Pr, ModeNo, ModeIdIndex);

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु

     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x00,0xAF,0x40);
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2E,0xF7);

  पूर्ण अन्यथा अणु

     क्रम(i=0,j=4; i<3; i++,j++) SiS_SetReg(SiS_Pr->SiS_Part1Port,j,0);
     अगर(SiS_Pr->ChipType >= SIS_315H) अणु
        SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0x7F);
     पूर्ण

     tempcl = SiS_Pr->SiS_ModeType;

     अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300    /* ---- 300 series ---- */

	/* For 301BDH: (with LCD via LVDS) */
	अगर(SiS_Pr->SiS_VBType & VB_NoLCD) अणु
	   tempbl = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32);
	   tempbl &= 0xef;
	   tempbl |= 0x02;
	   अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToTV) || (SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) अणु
	      tempbl |= 0x10;
	      tempbl &= 0xfd;
	   पूर्ण
	   SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,tempbl);
	पूर्ण

	अगर(ModeNo > 0x13) अणु
	   tempcl -= ModeVGA;
	   अगर(tempcl >= 0) अणु
	      tempah = ((0x10 >> tempcl) | 0x80);
	   पूर्ण
	पूर्ण अन्यथा tempah = 0x80;

	अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode)  tempah ^= 0xA0;

#पूर्ण_अगर  /* CONFIG_FB_SIS_300 */

     पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315    /* ------- 315/330 series ------ */

	अगर(ModeNo > 0x13) अणु
	   tempcl -= ModeVGA;
	   अगर(tempcl >= 0) अणु
	      tempah = (0x08 >> tempcl);
	      अगर (tempah == 0) tempah = 1;
	      tempah |= 0x40;
	   पूर्ण
	पूर्ण अन्यथा tempah = 0x40;

	अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) tempah ^= 0x50;

#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */

     पूर्ण

     अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 0;

     अगर(SiS_Pr->ChipType < SIS_315H) अणु
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,tempah);
     पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
	अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x00,0xa0,tempah);
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	   अगर(IS_SIS740) अणु
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,tempah);
	   पूर्ण अन्यथा अणु
	      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x00,0xa0,tempah);
	   पूर्ण
	पूर्ण
#पूर्ण_अगर
     पूर्ण

     अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

	tempah = 0x01;
	अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
	   tempah |= 0x02;
	पूर्ण
	अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) अणु
	   tempah ^= 0x05;
	   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) अणु
	      tempah ^= 0x01;
	   पूर्ण
	पूर्ण

	अगर(SiS_Pr->ChipType < SIS_315H) अणु

	   अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display)  tempah = 0;

	   tempah = (tempah << 5) & 0xFF;
	   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x01,tempah);
	   tempah = (tempah >> 5) & 0xFF;

	पूर्ण अन्यथा अणु

	   अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display)  tempah = 0x08;
	   अन्यथा अगर(!(SiS_IsDualEdge(SiS_Pr)))           tempah |= 0x08;
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2E,0xF0,tempah);
	   tempah &= ~0x08;

	पूर्ण

	अगर((SiS_Pr->SiS_ModeType == ModeVGA) && (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))) अणु
	   tempah |= 0x10;
	पूर्ण

	tempah |= 0x80;
	अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
	   अगर(SiS_Pr->PanelXRes < 1280 && SiS_Pr->PanelYRes < 960) tempah &= ~0x80;
	पूर्ण

	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	   अगर(!(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p | TVSetYPbPr525p))) अणु
	      अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
		 tempah |= 0x20;
	      पूर्ण
	   पूर्ण
	पूर्ण

	SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x0D,0x40,tempah);

	tempah = 0x80;
	अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
	   अगर(SiS_Pr->PanelXRes < 1280 && SiS_Pr->PanelYRes < 960) tempah = 0;
	पूर्ण

	अगर(SiS_IsDualLink(SiS_Pr)) tempah |= 0x40;

	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	   अगर(SiS_Pr->SiS_TVMode & TVRPLLDIV2XO) अणु
	      tempah |= 0x40;
	   पूर्ण
	पूर्ण

	SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0C,tempah);

     पूर्ण अन्यथा अणु  /* LVDS */

	अगर(SiS_Pr->ChipType >= SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_315
	   /* LVDS can only be slave in 8bpp modes */
	   tempah = 0x80;
	   अगर((modeflag & CRT2Mode) && (SiS_Pr->SiS_ModeType > ModeVGA)) अणु
	      अगर(SiS_Pr->SiS_VBInfo & DriverMode) अणु
	         tempah |= 0x02;
	      पूर्ण
	   पूर्ण

	   अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))  tempah |= 0x02;

	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)        tempah ^= 0x01;

	   अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 1;

	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2e,0xF0,tempah);
#पूर्ण_अगर

	पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_300
	   tempah = 0;
	   अगर( (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) && (SiS_Pr->SiS_ModeType > ModeVGA) ) अणु
	      tempah |= 0x02;
	   पूर्ण
	   tempah <<= 5;

	   अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 0;

	   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x01,tempah);
#पूर्ण_अगर

	पूर्ण

     पूर्ण

  पूर्ण  /* LCDA */

  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

     अगर(SiS_Pr->ChipType >= SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_315
	/* अचिन्हित अक्षर bridgerev = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x01); */

	/* The following is nearly unpreditable and varies from machine
	 * to machine. Especially the 301DH seems to be a real trouble
	 * maker. Some BIOSes simply set the रेजिस्टरs (like in the
	 * NoLCD-अगर-statements here), some set them according to the
	 * LCDA stuff. It is very likely that some machines are not
	 * treated correctly in the following, very हाल-orientated
	 * code. What करो I करो then...?
	 */

	/* 740 variants match क्रम 30xB, 301B-DH, 30xLV */

	अगर(!(IS_SIS740)) अणु
	   tempah = 0x04;						   /* For all bridges */
	   tempbl = 0xfb;
	   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
	      tempah = 0x00;
	      अगर(SiS_IsDualEdge(SiS_Pr)) अणु
	         tempbl = 0xff;
	      पूर्ण
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,tempbl,tempah);
	पूर्ण

	/* The following two are responsible क्रम eventually wrong colors
	 * in TV output. The DH (VB_NoLCD) conditions are unknown; the
	 * b0 was found in some 651 machine (Pim; P4_23=0xe5); the b1 version
	 * in a 650 box (Jake). What is the criteria?
	 * Addendum: Another combination 651+301B-DH(b1) (Rapo) needs same
	 * treaपंचांगent like the 651+301B-DH(b0) हाल. Seems more to be the
	 * chipset than the bridge revision.
	 */

	अगर((IS_SIS740) || (SiS_Pr->ChipType >= SIS_661) || (SiS_Pr->SiS_ROMNew)) अणु
	   tempah = 0x30;
	   tempbl = 0xc0;
	   अगर((SiS_Pr->SiS_VBInfo & DisableCRT2Display) ||
	      ((SiS_Pr->SiS_ROMNew) && (!(ROMAddr[0x5b] & 0x04)))) अणु
	      tempah = 0x00;
	      tempbl = 0x00;
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2c,0xcf,tempah);
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,0x3f,tempbl);
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
	   /* Fixes "TV-blue-bug" on 315+301 */
	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2c,0xcf);	/* For 301   */
	   SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x21,0x3f);
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2c,0x30);	/* For 30xLV */
	   SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x21,0xc0);
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_NoLCD) अणु		/* For 301B-DH */
	   tempah = 0x30; tempah2 = 0xc0;
	   tempbl = 0xcf; tempbl2 = 0x3f;
	   अगर(SiS_Pr->SiS_TVBlue == 0) अणु
	         tempah = tempah2 = 0x00;
	   पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVBlue == -1) अणु
	      /* Set on 651/M650, clear on 315/650 */
	      अगर(!(IS_SIS65x)) /* (bridgerev != 0xb0) */ अणु
	         tempah = tempah2 = 0x00;
	      पूर्ण
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2c,tempbl,tempah);
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,tempbl2,tempah2);
	पूर्ण अन्यथा अणु
	   tempah = 0x30; tempah2 = 0xc0;		       /* For 30xB, 301C */
	   tempbl = 0xcf; tempbl2 = 0x3f;
	   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
	      tempah = tempah2 = 0x00;
	      अगर(SiS_IsDualEdge(SiS_Pr)) अणु
		 tempbl = tempbl2 = 0xff;
	      पूर्ण
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2c,tempbl,tempah);
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,tempbl2,tempah2);
	पूर्ण

	अगर(IS_SIS740) अणु
	   tempah = 0x80;
	   अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display) tempah = 0x00;
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x23,0x7f,tempah);
	पूर्ण अन्यथा अणु
	   tempah = 0x00;
	   tempbl = 0x7f;
	   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
	      tempbl = 0xff;
	      अगर(!(SiS_IsDualEdge(SiS_Pr))) tempah = 0x80;
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x23,tempbl,tempah);
	पूर्ण

#पूर्ण_अगर /* CONFIG_FB_SIS_315 */

     पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु

#अगर_घोषित CONFIG_FB_SIS_300
	SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x21,0x3f);

	अगर((SiS_Pr->SiS_VBInfo & DisableCRT2Display) ||
	   ((SiS_Pr->SiS_VBType & VB_NoLCD) &&
	    (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD))) अणु
	   SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x23,0x7F);
	पूर्ण अन्यथा अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x23,0x80);
	पूर्ण
#पूर्ण_अगर

     पूर्ण

     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x0D,0x80);
	अगर(SiS_Pr->SiS_VBType & VB_SIS30xCLV) अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x3A,0xC0);
        पूर्ण
     पूर्ण

  पूर्ण अन्यथा अणु  /* LVDS */

#अगर_घोषित CONFIG_FB_SIS_315
     अगर(SiS_Pr->ChipType >= SIS_315H) अणु

	अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु

	   tempah = 0x04;
	   tempbl = 0xfb;
	   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
	      tempah = 0x00;
	      अगर(SiS_IsDualEdge(SiS_Pr)) tempbl = 0xff;
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,tempbl,tempah);

	   अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display) अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	   पूर्ण

	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2c,0x30);

	पूर्ण अन्यथा अगर(SiS_Pr->ChipType == SIS_550) अणु

	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2c,0x30);

	पूर्ण

     पूर्ण
#पूर्ण_अगर

  पूर्ण

पूर्ण

/*********************************************/
/*            GET RESOLUTION DATA            */
/*********************************************/

अचिन्हित लघु
SiS_GetResInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अगर(ModeNo <= 0x13)
      वापस ((अचिन्हित लघु)SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo);
   अन्यथा
      वापस ((अचिन्हित लघु)SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO);
पूर्ण

अटल व्योम
SiS_GetCRT2ResInfo(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु xres, yres, modeflag=0, resindex;

   अगर(SiS_Pr->UseCustomMode) अणु
      xres = SiS_Pr->CHDisplay;
      अगर(SiS_Pr->CModeFlag & HalfDCLK) xres <<= 1;
      SiS_Pr->SiS_VGAHDE = SiS_Pr->SiS_HDE = xres;
      /* DoubleScanMode-check करोne in CheckCalcCustomMode()! */
      SiS_Pr->SiS_VGAVDE = SiS_Pr->SiS_VDE = SiS_Pr->CVDisplay;
      वापस;
   पूर्ण

   resindex = SiS_GetResInfo(SiS_Pr,ModeNo,ModeIdIndex);

   अगर(ModeNo <= 0x13) अणु
      xres = SiS_Pr->SiS_StResInfo[resindex].HTotal;
      yres = SiS_Pr->SiS_StResInfo[resindex].VTotal;
   पूर्ण अन्यथा अणु
      xres = SiS_Pr->SiS_ModeResInfo[resindex].HTotal;
      yres = SiS_Pr->SiS_ModeResInfo[resindex].VTotal;
      modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   पूर्ण

   अगर(!SiS_Pr->SiS_IF_DEF_DSTN && !SiS_Pr->SiS_IF_DEF_FSTN) अणु

      अगर((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->SiS_IF_DEF_LVDS == 1)) अणु
	 अगर((ModeNo != 0x03) && (SiS_Pr->SiS_SetFlag & SetDOSMode)) अणु
	    अगर(yres == 350) yres = 400;
	 पूर्ण
	 अगर(SiS_GetReg(SiS_Pr->SiS_P3d4,0x3a) & 0x01) अणु
	    अगर(ModeNo == 0x12) yres = 400;
	 पूर्ण
      पूर्ण

      अगर(modeflag & HalfDCLK)       xres <<= 1;
      अगर(modeflag & DoubleScanMode) yres <<= 1;

   पूर्ण

   अगर((SiS_Pr->SiS_VBType & VB_SISVB) && (!(SiS_Pr->SiS_VBType & VB_NoLCD))) अणु

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	 चयन(SiS_Pr->SiS_LCDResInfo) अणु
	   हाल Panel_1024x768:
	      अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) अणु
		 अगर(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) अणु
		    अगर(yres == 350) yres = 357;
		    अगर(yres == 400) yres = 420;
		    अगर(yres == 480) yres = 525;
		 पूर्ण
	      पूर्ण
	      अवरोध;
	   हाल Panel_1280x1024:
	      अगर(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) अणु
		 /* BIOS bug - करोes this regardless of scaling */
		 अगर(yres == 400) yres = 405;
	      पूर्ण
	      अगर(yres == 350) yres = 360;
	      अगर(SiS_Pr->SiS_SetFlag & LCDVESATiming) अणु
		 अगर(yres == 360) yres = 375;
	      पूर्ण
	      अवरोध;
	   हाल Panel_1600x1200:
	      अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) अणु
		 अगर(yres == 1024) yres = 1056;
	      पूर्ण
	      अवरोध;
	 पूर्ण
      पूर्ण

   पूर्ण अन्यथा अणु

      अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	 अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToHiVision)) अणु
	    अगर(xres == 720) xres = 640;
	 पूर्ण
      पूर्ण अन्यथा अगर(xres == 720) xres = 640;

      अगर(SiS_Pr->SiS_SetFlag & SetDOSMode) अणु
	 yres = 400;
	 अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	    अगर(SiS_GetReg(SiS_Pr->SiS_P3c4,0x17) & 0x80) yres = 480;
	 पूर्ण अन्यथा अणु
	    अगर(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x80) yres = 480;
	 पूर्ण
	 अगर(SiS_Pr->SiS_IF_DEF_DSTN || SiS_Pr->SiS_IF_DEF_FSTN) yres = 480;
      पूर्ण

   पूर्ण
   SiS_Pr->SiS_VGAHDE = SiS_Pr->SiS_HDE = xres;
   SiS_Pr->SiS_VGAVDE = SiS_Pr->SiS_VDE = yres;
पूर्ण

/*********************************************/
/*           GET CRT2 TIMING DATA            */
/*********************************************/

अटल व्योम
SiS_GetCRT2Ptr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
	       अचिन्हित लघु RefreshRateTableIndex, अचिन्हित लघु *CRT2Index,
	       अचिन्हित लघु *ResIndex)
अणु
  अचिन्हित लघु tempbx=0, tempal=0, resinfo=0;

  अगर(ModeNo <= 0x13) अणु
     tempal = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  पूर्ण अन्यथा अणु
     tempal = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
  पूर्ण

  अगर((SiS_Pr->SiS_VBType & VB_SISVB) && (SiS_Pr->SiS_IF_DEF_LVDS == 0)) अणु

     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु                            /* LCD */

	tempbx = SiS_Pr->SiS_LCDResInfo;
	अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) tempbx += 32;

	/* patch index */
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_1680x1050) अणु
	   अगर     (resinfo == SIS_RI_1280x800)  tempal =  9;
	   अन्यथा अगर(resinfo == SIS_RI_1400x1050) tempal = 11;
	पूर्ण अन्यथा अगर((SiS_Pr->SiS_LCDResInfo == Panel_1280x800) ||
		  (SiS_Pr->SiS_LCDResInfo == Panel_1280x800_2) ||
		  (SiS_Pr->SiS_LCDResInfo == Panel_1280x854)) अणु
	   अगर     (resinfo == SIS_RI_1280x768)  tempal =  9;
	पूर्ण

	अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	   /* Pass 1:1 only (center-screen handled outside) */
	   /* This is never called क्रम the panel's native resolution */
	   /* since Pass1:1 will not be set in this हाल */
	   tempbx = 100;
	   अगर(ModeNo >= 0x13) अणु
	      tempal = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC_NS;
	   पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
	अगर(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) अणु
	   अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) अणु
	      अगर(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) अणु
		 tempbx = 200;
		 अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) tempbx++;
	      पूर्ण
	   पूर्ण
	पूर्ण
#पूर्ण_अगर

     पूर्ण अन्यथा अणु						  	/* TV */

	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	   /* अगर(SiS_Pr->SiS_VGAVDE > 480) SiS_Pr->SiS_TVMode &= (~TVSetTVSimuMode); */
	   tempbx = 2;
	   अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	      tempbx = 13;
	      अगर(!(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)) tempbx = 14;
	   पूर्ण
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
	   अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)	tempbx = 7;
	   अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p)	tempbx = 6;
	   अन्यथा						tempbx = 5;
	   अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)	tempbx += 5;
	पूर्ण अन्यथा अणु
	   अगर(SiS_Pr->SiS_TVMode & TVSetPAL)		tempbx = 3;
	   अन्यथा						tempbx = 4;
	   अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)	tempbx += 5;
	पूर्ण

     पूर्ण

     tempal &= 0x3F;

     अगर(ModeNo > 0x13) अणु
        अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoHiVision) अणु
	   चयन(resinfo) अणु
	   हाल SIS_RI_720x480:
	      tempal = 6;
	      अगर(SiS_Pr->SiS_TVMode & (TVSetPAL | TVSetPALN))	tempal = 9;
	      अवरोध;
	   हाल SIS_RI_720x576:
	   हाल SIS_RI_768x576:
	   हाल SIS_RI_1024x576: /* Not in NTSC or YPBPR mode (except 1080i)! */
	      tempal = 6;
	      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
		 अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)	tempal = 8;
	      पूर्ण
	      अवरोध;
	   हाल SIS_RI_800x480:
	      tempal = 4;
	      अवरोध;
	   हाल SIS_RI_512x384:
	   हाल SIS_RI_1024x768:
	      tempal = 7;
	      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
		 अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p)	tempal = 8;
	      पूर्ण
	      अवरोध;
	   हाल SIS_RI_1280x720:
	      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
		 अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)	tempal = 9;
	      पूर्ण
	      अवरोध;
	   पूर्ण
	पूर्ण
     पूर्ण

     *CRT2Index = tempbx;
     *ResIndex = tempal;

  पूर्ण अन्यथा अणु   /* LVDS, 301B-DH (अगर running on LCD) */

     tempbx = 0;
     अगर((SiS_Pr->SiS_IF_DEF_CH70xx) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) अणु

	tempbx = 90;
	अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
	   tempbx = 92;
	   अगर(SiS_Pr->SiS_ModeType > ModeVGA) अणु
	      अगर(SiS_Pr->SiS_CHSOverScan) tempbx = 99;
	   पूर्ण
	   अगर(SiS_Pr->SiS_TVMode & TVSetPALM)      tempbx = 94;
	   अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPALN) tempbx = 96;
	पूर्ण
	अगर(tempbx != 99) अणु
	   अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) tempbx++;
	पूर्ण

     पूर्ण अन्यथा अणु

	चयन(SiS_Pr->SiS_LCDResInfo) अणु
	हाल Panel_640x480:   tempbx = 12; अवरोध;
	हाल Panel_320x240_1: tempbx = 10; अवरोध;
	हाल Panel_320x240_2:
	हाल Panel_320x240_3: tempbx = 14; अवरोध;
	हाल Panel_800x600:   tempbx = 16; अवरोध;
	हाल Panel_1024x600:  tempbx = 18; अवरोध;
	हाल Panel_1152x768:
	हाल Panel_1024x768:  tempbx = 20; अवरोध;
	हाल Panel_1280x768:  tempbx = 22; अवरोध;
	हाल Panel_1280x1024: tempbx = 24; अवरोध;
	हाल Panel_1400x1050: tempbx = 26; अवरोध;
	हाल Panel_1600x1200: tempbx = 28; अवरोध;
#अगर_घोषित CONFIG_FB_SIS_300
	हाल Panel_Barco1366: tempbx = 80; अवरोध;
#पूर्ण_अगर
	पूर्ण

	चयन(SiS_Pr->SiS_LCDResInfo) अणु
	हाल Panel_320x240_1:
	हाल Panel_320x240_2:
	हाल Panel_320x240_3:
	हाल Panel_640x480:
	   अवरोध;
	शेष:
	   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;
	पूर्ण

	अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) tempbx = 30;

#अगर_घोषित CONFIG_FB_SIS_300
	अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1024) अणु
	   tempbx = 82;
	   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_CustomT == CUT_PANEL848 || SiS_Pr->SiS_CustomT == CUT_PANEL856) अणु
	   tempbx = 84;
	   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;
	पूर्ण
#पूर्ण_अगर

     पूर्ण

     (*CRT2Index) = tempbx;
     (*ResIndex) = tempal & 0x1F;
  पूर्ण
पूर्ण

अटल व्योम
SiS_GetRAMDAC2DATA(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु tempax=0, tempbx=0, index, करोtघड़ी;
  अचिन्हित लघु temp1=0, modeflag=0, tempcx=0;

  SiS_Pr->SiS_RVBHCMAX  = 1;
  SiS_Pr->SiS_RVBHCFACT = 1;

  अगर(ModeNo <= 0x13) अणु

     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     index = SiS_GetModePtr(SiS_Pr,ModeNo,ModeIdIndex);

     tempax = SiS_Pr->SiS_StandTable[index].CRTC[0];
     tempbx = SiS_Pr->SiS_StandTable[index].CRTC[6];
     temp1 = SiS_Pr->SiS_StandTable[index].CRTC[7];

     करोtघड़ी = (modeflag & Charx8Dot) ? 8 : 9;

  पूर्ण अन्यथा अणु

     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     index = SiS_GetRefCRT1CRTC(SiS_Pr, RefreshRateTableIndex, SiS_Pr->SiS_UseWideCRT2);

     tempax = SiS_Pr->SiS_CRT1Table[index].CR[0];
     tempax |= (SiS_Pr->SiS_CRT1Table[index].CR[14] << 8);
     tempax &= 0x03FF;
     tempbx = SiS_Pr->SiS_CRT1Table[index].CR[6];
     tempcx = SiS_Pr->SiS_CRT1Table[index].CR[13] << 8;
     tempcx &= 0x0100;
     tempcx <<= 2;
     tempbx |= tempcx;
     temp1  = SiS_Pr->SiS_CRT1Table[index].CR[7];

     करोtघड़ी = 8;

  पूर्ण

  अगर(temp1 & 0x01) tempbx |= 0x0100;
  अगर(temp1 & 0x20) tempbx |= 0x0200;

  tempax += 5;
  tempax *= करोtघड़ी;
  अगर(modeflag & HalfDCLK) tempax <<= 1;

  tempbx++;

  SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = tempax;
  SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = tempbx;
पूर्ण

अटल व्योम
SiS_CalcPanelLinkTiming(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
		अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RefreshRateTableIndex)
अणु
   अचिन्हित लघु ResIndex;

   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
      अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) अणु
	 अगर(SiS_Pr->UseCustomMode) अणु
	    ResIndex = SiS_Pr->CHTotal;
	    अगर(SiS_Pr->CModeFlag & HalfDCLK) ResIndex <<= 1;
	    SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = ResIndex;
	    SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = SiS_Pr->CVTotal;
	 पूर्ण अन्यथा अणु
	    अगर(ModeNo < 0x13) अणु
	       ResIndex = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
	    पूर्ण अन्यथा अणु
	       ResIndex = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC_NS;
	    पूर्ण
	    अगर(ResIndex == 0x09) अणु
	       अगर(SiS_Pr->Alternate1600x1200)        ResIndex = 0x20; /* 1600x1200 LCDA */
	       अन्यथा अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) ResIndex = 0x21; /* 1600x1200 LVDS */
	    पूर्ण
	    SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_NoScaleData[ResIndex].VGAHT;
	    SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_NoScaleData[ResIndex].VGAVT;
	    SiS_Pr->SiS_HT    = SiS_Pr->SiS_NoScaleData[ResIndex].LCDHT;
	    SiS_Pr->SiS_VT    = SiS_Pr->SiS_NoScaleData[ResIndex].LCDVT;
	 पूर्ण
      पूर्ण अन्यथा अणु
	 SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = SiS_Pr->PanelHT;
	 SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = SiS_Pr->PanelVT;
      पूर्ण
   पूर्ण अन्यथा अणु
      /* This handles custom modes and custom panels */
      SiS_Pr->SiS_HDE = SiS_Pr->PanelXRes;
      SiS_Pr->SiS_VDE = SiS_Pr->PanelYRes;
      SiS_Pr->SiS_HT  = SiS_Pr->PanelHT;
      SiS_Pr->SiS_VT  = SiS_Pr->PanelVT;
      SiS_Pr->SiS_VGAHT = SiS_Pr->PanelHT - (SiS_Pr->PanelXRes - SiS_Pr->SiS_VGAHDE);
      SiS_Pr->SiS_VGAVT = SiS_Pr->PanelVT - (SiS_Pr->PanelYRes - SiS_Pr->SiS_VGAVDE);
   पूर्ण
पूर्ण

अटल व्योम
SiS_GetCRT2DataLVDS(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
                    अचिन्हित लघु RefreshRateTableIndex)
अणु
   अचिन्हित लघु CRT2Index, ResIndex, backup;
   स्थिर काष्ठा SiS_LVDSData *LVDSData = शून्य;

   SiS_GetCRT2ResInfo(SiS_Pr, ModeNo, ModeIdIndex);

   अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
      SiS_Pr->SiS_RVBHCMAX  = 1;
      SiS_Pr->SiS_RVBHCFACT = 1;
      SiS_Pr->SiS_NewFlickerMode = 0;
      SiS_Pr->SiS_RVBHRS = 50;
      SiS_Pr->SiS_RY1COE = 0;
      SiS_Pr->SiS_RY2COE = 0;
      SiS_Pr->SiS_RY3COE = 0;
      SiS_Pr->SiS_RY4COE = 0;
      SiS_Pr->SiS_RVBHRS2 = 0;
   पूर्ण

   अगर((SiS_Pr->SiS_VBType & VB_SISVB) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु

#अगर_घोषित CONFIG_FB_SIS_315
      SiS_CalcPanelLinkTiming(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      SiS_CalcLCDACRT1Timing(SiS_Pr, ModeNo, ModeIdIndex);
#पूर्ण_अगर

   पूर्ण अन्यथा अणु

      /* 301BDH needs LVDS Data */
      backup = SiS_Pr->SiS_IF_DEF_LVDS;
      अगर((SiS_Pr->SiS_VBType & VB_NoLCD) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) अणु
	 SiS_Pr->SiS_IF_DEF_LVDS = 1;
      पूर्ण

      SiS_GetCRT2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex,
                     		            &CRT2Index, &ResIndex);

      SiS_Pr->SiS_IF_DEF_LVDS = backup;

      चयन(CRT2Index) अणु
	 हाल 10: LVDSData = SiS_Pr->SiS_LVDS320x240Data_1;    अवरोध;
	 हाल 14: LVDSData = SiS_Pr->SiS_LVDS320x240Data_2;    अवरोध;
	 हाल 12: LVDSData = SiS_Pr->SiS_LVDS640x480Data_1;    अवरोध;
	 हाल 16: LVDSData = SiS_Pr->SiS_LVDS800x600Data_1;    अवरोध;
	 हाल 18: LVDSData = SiS_Pr->SiS_LVDS1024x600Data_1;   अवरोध;
	 हाल 20: LVDSData = SiS_Pr->SiS_LVDS1024x768Data_1;   अवरोध;
#अगर_घोषित CONFIG_FB_SIS_300
	 हाल 80: LVDSData = SiS_Pr->SiS_LVDSBARCO1366Data_1;  अवरोध;
	 हाल 81: LVDSData = SiS_Pr->SiS_LVDSBARCO1366Data_2;  अवरोध;
	 हाल 82: LVDSData = SiS_Pr->SiS_LVDSBARCO1024Data_1;  अवरोध;
	 हाल 84: LVDSData = SiS_Pr->SiS_LVDS848x480Data_1;    अवरोध;
	 हाल 85: LVDSData = SiS_Pr->SiS_LVDS848x480Data_2;    अवरोध;
#पूर्ण_अगर
	 हाल 90: LVDSData = SiS_Pr->SiS_CHTVUNTSCData;        अवरोध;
	 हाल 91: LVDSData = SiS_Pr->SiS_CHTVONTSCData;        अवरोध;
	 हाल 92: LVDSData = SiS_Pr->SiS_CHTVUPALData;         अवरोध;
	 हाल 93: LVDSData = SiS_Pr->SiS_CHTVOPALData;         अवरोध;
	 हाल 94: LVDSData = SiS_Pr->SiS_CHTVUPALMData;        अवरोध;
	 हाल 95: LVDSData = SiS_Pr->SiS_CHTVOPALMData;        अवरोध;
	 हाल 96: LVDSData = SiS_Pr->SiS_CHTVUPALNData;        अवरोध;
	 हाल 97: LVDSData = SiS_Pr->SiS_CHTVOPALNData;        अवरोध;
	 हाल 99: LVDSData = SiS_Pr->SiS_CHTVSOPALData;	       अवरोध;
      पूर्ण

      अगर(LVDSData) अणु
	 SiS_Pr->SiS_VGAHT = (LVDSData+ResIndex)->VGAHT;
	 SiS_Pr->SiS_VGAVT = (LVDSData+ResIndex)->VGAVT;
	 SiS_Pr->SiS_HT    = (LVDSData+ResIndex)->LCDHT;
	 SiS_Pr->SiS_VT    = (LVDSData+ResIndex)->LCDVT;
      पूर्ण अन्यथा अणु
	 SiS_CalcPanelLinkTiming(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      पूर्ण

      अगर( (!(SiS_Pr->SiS_VBType & VB_SISVB)) &&
	  (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) &&
	  (!(SiS_Pr->SiS_LCDInfo & LCDPass11)) ) अणु
	 अगर( (!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) ||
	     (SiS_Pr->SiS_SetFlag & SetDOSMode) ) अणु
	    SiS_Pr->SiS_HDE = SiS_Pr->PanelXRes;
            SiS_Pr->SiS_VDE = SiS_Pr->PanelYRes;
#अगर_घोषित CONFIG_FB_SIS_300
	    अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1366) अणु
	       अगर(ResIndex < 0x08) अणु
		  SiS_Pr->SiS_HDE = 1280;
		  SiS_Pr->SiS_VDE = 1024;
	       पूर्ण
	    पूर्ण
#पूर्ण_अगर
         पूर्ण
      पूर्ण
   पूर्ण
पूर्ण

अटल व्योम
SiS_GetCRT2Data301(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = शून्य;
  अचिन्हित लघु tempax, tempbx, modeflag, romptr=0;
  अचिन्हित लघु resinfo, CRT2Index, ResIndex;
  स्थिर काष्ठा SiS_LCDData *LCDPtr = शून्य;
  स्थिर काष्ठा SiS_TVData  *TVPtr  = शून्य;
#अगर_घोषित CONFIG_FB_SIS_315
  लघु resinfo661;
#पूर्ण_अगर

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
  पूर्ण अन्यथा अगर(SiS_Pr->UseCustomMode) अणु
     modeflag = SiS_Pr->CModeFlag;
     resinfo = 0;
  पूर्ण अन्यथा अणु
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
#अगर_घोषित CONFIG_FB_SIS_315
     resinfo661 = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].ROMMODEIDX661;
     अगर( (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)   &&
	 (SiS_Pr->SiS_SetFlag & LCDVESATiming) &&
	 (resinfo661 >= 0)                     &&
	 (SiS_Pr->SiS_NeedRomModeData) ) अणु
	अगर((ROMAddr = GetLCDStructPtr661(SiS_Pr))) अणु
	   अगर((romptr = (SISGETROMW(21)))) अणु
	      romptr += (resinfo661 * 10);
	      ROMAddr = SiS_Pr->VirtualRomBase;
	   पूर्ण
	पूर्ण
     पूर्ण
#पूर्ण_अगर
  पूर्ण

  SiS_Pr->SiS_NewFlickerMode = 0;
  SiS_Pr->SiS_RVBHRS = 50;
  SiS_Pr->SiS_RY1COE = 0;
  SiS_Pr->SiS_RY2COE = 0;
  SiS_Pr->SiS_RY3COE = 0;
  SiS_Pr->SiS_RY4COE = 0;
  SiS_Pr->SiS_RVBHRS2 = 0;

  SiS_GetCRT2ResInfo(SiS_Pr,ModeNo,ModeIdIndex);

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) अणु

     अगर(SiS_Pr->UseCustomMode) अणु

	SiS_Pr->SiS_RVBHCMAX  = 1;
	SiS_Pr->SiS_RVBHCFACT = 1;
	SiS_Pr->SiS_HDE       = SiS_Pr->SiS_VGAHDE;
	SiS_Pr->SiS_VDE       = SiS_Pr->SiS_VGAVDE;

	tempax = SiS_Pr->CHTotal;
	अगर(modeflag & HalfDCLK) tempax <<= 1;
	SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = tempax;
	SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = SiS_Pr->CVTotal;

     पूर्ण अन्यथा अणु

	SiS_GetRAMDAC2DATA(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);

     पूर्ण

  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु

     SiS_GetCRT2Ptr(SiS_Pr,ModeNo,ModeIdIndex,RefreshRateTableIndex,
		    &CRT2Index,&ResIndex);

     चयन(CRT2Index) अणु
	हाल  2: TVPtr = SiS_Pr->SiS_ExtHiTVData;   अवरोध;
	हाल  3: TVPtr = SiS_Pr->SiS_ExtPALData;    अवरोध;
	हाल  4: TVPtr = SiS_Pr->SiS_ExtNTSCData;   अवरोध;
	हाल  5: TVPtr = SiS_Pr->SiS_Ext525iData;   अवरोध;
	हाल  6: TVPtr = SiS_Pr->SiS_Ext525pData;   अवरोध;
	हाल  7: TVPtr = SiS_Pr->SiS_Ext750pData;   अवरोध;
	हाल  8: TVPtr = SiS_Pr->SiS_StPALData;     अवरोध;
	हाल  9: TVPtr = SiS_Pr->SiS_StNTSCData;    अवरोध;
	हाल 10: TVPtr = SiS_Pr->SiS_St525iData;    अवरोध;
	हाल 11: TVPtr = SiS_Pr->SiS_St525pData;    अवरोध;
	हाल 12: TVPtr = SiS_Pr->SiS_St750pData;    अवरोध;
	हाल 13: TVPtr = SiS_Pr->SiS_St1HiTVData;   अवरोध;
	हाल 14: TVPtr = SiS_Pr->SiS_St2HiTVData;   अवरोध;
	शेष: TVPtr = SiS_Pr->SiS_StPALData;     अवरोध;
     पूर्ण

     SiS_Pr->SiS_RVBHCMAX  = (TVPtr+ResIndex)->RVBHCMAX;
     SiS_Pr->SiS_RVBHCFACT = (TVPtr+ResIndex)->RVBHCFACT;
     SiS_Pr->SiS_VGAHT     = (TVPtr+ResIndex)->VGAHT;
     SiS_Pr->SiS_VGAVT     = (TVPtr+ResIndex)->VGAVT;
     SiS_Pr->SiS_HDE       = (TVPtr+ResIndex)->TVHDE;
     SiS_Pr->SiS_VDE       = (TVPtr+ResIndex)->TVVDE;
     SiS_Pr->SiS_RVBHRS2   = (TVPtr+ResIndex)->RVBHRS2 & 0x0fff;
     अगर(modeflag & HalfDCLK) अणु
	SiS_Pr->SiS_RVBHRS = (TVPtr+ResIndex)->HALFRVBHRS;
	अगर(SiS_Pr->SiS_RVBHRS2) अणु
	   SiS_Pr->SiS_RVBHRS2 = ((SiS_Pr->SiS_RVBHRS2 + 3) >> 1) - 3;
	   tempax = ((TVPtr+ResIndex)->RVBHRS2 >> 12) & 0x07;
	   अगर((TVPtr+ResIndex)->RVBHRS2 & 0x8000) SiS_Pr->SiS_RVBHRS2 -= tempax;
	   अन्यथा                                   SiS_Pr->SiS_RVBHRS2 += tempax;
	पूर्ण
     पूर्ण अन्यथा अणु
	SiS_Pr->SiS_RVBHRS    = (TVPtr+ResIndex)->RVBHRS;
     पूर्ण
     SiS_Pr->SiS_NewFlickerMode = ((TVPtr+ResIndex)->FlickerMode) << 7;

     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु

	अगर((resinfo == SIS_RI_960x600)   ||
	   (resinfo == SIS_RI_1024x768)  ||
	   (resinfo == SIS_RI_1280x1024) ||
	   (resinfo == SIS_RI_1280x720)) अणु
	   SiS_Pr->SiS_NewFlickerMode = 0x40;
	पूर्ण

	अगर(SiS_Pr->SiS_VGAVDE == 350) SiS_Pr->SiS_TVMode |= TVSetTVSimuMode;

	SiS_Pr->SiS_HT = ExtHiTVHT;
	SiS_Pr->SiS_VT = ExtHiTVVT;
	अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	   अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) अणु
	      SiS_Pr->SiS_HT = StHiTVHT;
	      SiS_Pr->SiS_VT = StHiTVVT;
	   पूर्ण
	पूर्ण

     पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु

	अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) अणु
	   SiS_Pr->SiS_HT = 1650;
	   SiS_Pr->SiS_VT = 750;
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) अणु
	   SiS_Pr->SiS_HT = NTSCHT;
	   अगर(SiS_Pr->SiS_TVMode & TVSet525p1024) SiS_Pr->SiS_HT = NTSC2HT;
	   SiS_Pr->SiS_VT = NTSCVT;
	पूर्ण अन्यथा अणु
	   SiS_Pr->SiS_HT = NTSCHT;
	   अगर(SiS_Pr->SiS_TVMode & TVSetNTSC1024) SiS_Pr->SiS_HT = NTSC2HT;
	   SiS_Pr->SiS_VT = NTSCVT;
	पूर्ण

     पूर्ण अन्यथा अणु

	SiS_Pr->SiS_RY1COE = (TVPtr+ResIndex)->RY1COE;
	SiS_Pr->SiS_RY2COE = (TVPtr+ResIndex)->RY2COE;
	SiS_Pr->SiS_RY3COE = (TVPtr+ResIndex)->RY3COE;
	SiS_Pr->SiS_RY4COE = (TVPtr+ResIndex)->RY4COE;

	अगर(modeflag & HalfDCLK) अणु
	   SiS_Pr->SiS_RY1COE = 0x00;
	   SiS_Pr->SiS_RY2COE = 0xf4;
	   SiS_Pr->SiS_RY3COE = 0x10;
	   SiS_Pr->SiS_RY4COE = 0x38;
	पूर्ण

	अगर(!(SiS_Pr->SiS_TVMode & TVSetPAL)) अणु
	   SiS_Pr->SiS_HT = NTSCHT;
	   अगर(SiS_Pr->SiS_TVMode & TVSetNTSC1024) SiS_Pr->SiS_HT = NTSC2HT;
	   SiS_Pr->SiS_VT = NTSCVT;
	पूर्ण अन्यथा अणु
	   SiS_Pr->SiS_HT = PALHT;
	   SiS_Pr->SiS_VT = PALVT;
	पूर्ण

     पूर्ण

  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु

     SiS_Pr->SiS_RVBHCMAX  = 1;
     SiS_Pr->SiS_RVBHCFACT = 1;

     अगर(SiS_Pr->UseCustomMode) अणु

	SiS_Pr->SiS_HDE   = SiS_Pr->SiS_VGAHDE;
	SiS_Pr->SiS_VDE   = SiS_Pr->SiS_VGAVDE;

	tempax = SiS_Pr->CHTotal;
	अगर(modeflag & HalfDCLK) tempax <<= 1;
	SiS_Pr->SiS_VGAHT = SiS_Pr->SiS_HT = tempax;
	SiS_Pr->SiS_VGAVT = SiS_Pr->SiS_VT = SiS_Pr->CVTotal;

     पूर्ण अन्यथा अणु

	bool gotit = false;

	अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) अणु

	   SiS_Pr->SiS_VGAHT = SiS_Pr->PanelHT;
	   SiS_Pr->SiS_VGAVT = SiS_Pr->PanelVT;
	   SiS_Pr->SiS_HT    = SiS_Pr->PanelHT;
	   SiS_Pr->SiS_VT    = SiS_Pr->PanelVT;
	   gotit = true;

	पूर्ण अन्यथा अगर( (!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) && (romptr) && (ROMAddr) ) अणु

#अगर_घोषित CONFIG_FB_SIS_315
	   SiS_Pr->SiS_RVBHCMAX  = ROMAddr[romptr];
	   SiS_Pr->SiS_RVBHCFACT = ROMAddr[romptr+1];
	   SiS_Pr->SiS_VGAHT     = ROMAddr[romptr+2] | ((ROMAddr[romptr+3] & 0x0f) << 8);
	   SiS_Pr->SiS_VGAVT     = (ROMAddr[romptr+4] << 4) | ((ROMAddr[romptr+3] & 0xf0) >> 4);
	   SiS_Pr->SiS_HT        = ROMAddr[romptr+5] | ((ROMAddr[romptr+6] & 0x0f) << 8);
	   SiS_Pr->SiS_VT        = (ROMAddr[romptr+7] << 4) | ((ROMAddr[romptr+6] & 0xf0) >> 4);
	   SiS_Pr->SiS_RVBHRS2   = ROMAddr[romptr+8] | ((ROMAddr[romptr+9] & 0x0f) << 8);
	   अगर((SiS_Pr->SiS_RVBHRS2) && (modeflag & HalfDCLK)) अणु
	      SiS_Pr->SiS_RVBHRS2 = ((SiS_Pr->SiS_RVBHRS2 + 3) >> 1) - 3;
	      tempax = (ROMAddr[romptr+9] >> 4) & 0x07;
	      अगर(ROMAddr[romptr+9] & 0x80) SiS_Pr->SiS_RVBHRS2 -= tempax;
	      अन्यथा                         SiS_Pr->SiS_RVBHRS2 += tempax;
	   पूर्ण
	   अगर(SiS_Pr->SiS_VGAHT) gotit = true;
	   अन्यथा अणु
	      SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
	      SiS_Pr->SiS_LCDInfo &= ~LCDPass11;
	      SiS_Pr->SiS_RVBHCMAX  = 1;
	      SiS_Pr->SiS_RVBHCFACT = 1;
	      SiS_Pr->SiS_VGAHT   = SiS_Pr->PanelHT;
	      SiS_Pr->SiS_VGAVT   = SiS_Pr->PanelVT;
	      SiS_Pr->SiS_HT      = SiS_Pr->PanelHT;
	      SiS_Pr->SiS_VT      = SiS_Pr->PanelVT;
	      SiS_Pr->SiS_RVBHRS2 = 0;
	      gotit = true;
	   पूर्ण
#पूर्ण_अगर

	पूर्ण

	अगर(!gotit) अणु

	   SiS_GetCRT2Ptr(SiS_Pr,ModeNo,ModeIdIndex,RefreshRateTableIndex,
			  &CRT2Index,&ResIndex);

	   चयन(CRT2Index) अणु
	      हाल Panel_1024x768      : LCDPtr = SiS_Pr->SiS_ExtLCD1024x768Data;   अवरोध;
	      हाल Panel_1024x768  + 32: LCDPtr = SiS_Pr->SiS_St2LCD1024x768Data;   अवरोध;
	      हाल Panel_1280x720      :
	      हाल Panel_1280x720  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x720Data;      अवरोध;
	      हाल Panel_1280x768_2    : LCDPtr = SiS_Pr->SiS_ExtLCD1280x768_2Data; अवरोध;
	      हाल Panel_1280x768_2+ 32: LCDPtr = SiS_Pr->SiS_StLCD1280x768_2Data;  अवरोध;
	      हाल Panel_1280x800      :
	      हाल Panel_1280x800  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x800Data;      अवरोध;
	      हाल Panel_1280x800_2    :
	      हाल Panel_1280x800_2+ 32: LCDPtr = SiS_Pr->SiS_LCD1280x800_2Data;    अवरोध;
	      हाल Panel_1280x854      :
	      हाल Panel_1280x854  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x854Data;      अवरोध;
	      हाल Panel_1280x960      :
	      हाल Panel_1280x960  + 32: LCDPtr = SiS_Pr->SiS_LCD1280x960Data;      अवरोध;
	      हाल Panel_1280x1024     : LCDPtr = SiS_Pr->SiS_ExtLCD1280x1024Data;  अवरोध;
	      हाल Panel_1280x1024 + 32: LCDPtr = SiS_Pr->SiS_St2LCD1280x1024Data;  अवरोध;
	      हाल Panel_1400x1050     : LCDPtr = SiS_Pr->SiS_ExtLCD1400x1050Data;  अवरोध;
	      हाल Panel_1400x1050 + 32: LCDPtr = SiS_Pr->SiS_StLCD1400x1050Data;   अवरोध;
	      हाल Panel_1600x1200     : LCDPtr = SiS_Pr->SiS_ExtLCD1600x1200Data;  अवरोध;
	      हाल Panel_1600x1200 + 32: LCDPtr = SiS_Pr->SiS_StLCD1600x1200Data;   अवरोध;
	      हाल Panel_1680x1050     :
	      हाल Panel_1680x1050 + 32: LCDPtr = SiS_Pr->SiS_LCD1680x1050Data;     अवरोध;
	      हाल 100		       : LCDPtr = SiS_Pr->SiS_NoScaleData;	    अवरोध;
#अगर_घोषित CONFIG_FB_SIS_315
	      हाल 200                 : LCDPtr = SiS310_ExtCompaq1280x1024Data;    अवरोध;
	      हाल 201                 : LCDPtr = SiS_Pr->SiS_St2LCD1280x1024Data;  अवरोध;
#पूर्ण_अगर
	      शेष                  : LCDPtr = SiS_Pr->SiS_ExtLCD1024x768Data;   अवरोध;
	   पूर्ण

	   SiS_Pr->SiS_RVBHCMAX  = (LCDPtr+ResIndex)->RVBHCMAX;
	   SiS_Pr->SiS_RVBHCFACT = (LCDPtr+ResIndex)->RVBHCFACT;
	   SiS_Pr->SiS_VGAHT     = (LCDPtr+ResIndex)->VGAHT;
	   SiS_Pr->SiS_VGAVT     = (LCDPtr+ResIndex)->VGAVT;
	   SiS_Pr->SiS_HT        = (LCDPtr+ResIndex)->LCDHT;
	   SiS_Pr->SiS_VT        = (LCDPtr+ResIndex)->LCDVT;

        पूर्ण

	tempax = SiS_Pr->PanelXRes;
	tempbx = SiS_Pr->PanelYRes;

	चयन(SiS_Pr->SiS_LCDResInfo) अणु
	हाल Panel_1024x768:
	   अगर(SiS_Pr->SiS_SetFlag & LCDVESATiming) अणु
	      अगर(SiS_Pr->ChipType < SIS_315H) अणु
		 अगर     (SiS_Pr->SiS_VGAVDE == 350) tempbx = 560;
		 अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 400) tempbx = 640;
	      पूर्ण
	   पूर्ण अन्यथा अणु
	      अगर     (SiS_Pr->SiS_VGAVDE == 357) tempbx = 527;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 420) tempbx = 620;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 525) tempbx = 775;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 600) tempbx = 775;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 350) tempbx = 560;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 400) tempbx = 640;
	   पूर्ण
	   अवरोध;
	हाल Panel_1280x960:
	   अगर     (SiS_Pr->SiS_VGAVDE == 350)  tempbx = 700;
	   अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 400)  tempbx = 800;
	   अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 1024) tempbx = 960;
	   अवरोध;
	हाल Panel_1280x1024:
	   अगर     (SiS_Pr->SiS_VGAVDE == 360) tempbx = 768;
	   अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 375) tempbx = 800;
	   अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 405) tempbx = 864;
	   अवरोध;
	हाल Panel_1600x1200:
	   अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) अणु
	      अगर     (SiS_Pr->SiS_VGAVDE == 350)  tempbx = 875;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 400)  tempbx = 1000;
	   पूर्ण
	   अवरोध;
	पूर्ण

	अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	   tempax = SiS_Pr->SiS_VGAHDE;
	   tempbx = SiS_Pr->SiS_VGAVDE;
	पूर्ण

	SiS_Pr->SiS_HDE = tempax;
	SiS_Pr->SiS_VDE = tempbx;
     पूर्ण
  पूर्ण
पूर्ण

अटल व्योम
SiS_GetCRT2Data(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
                अचिन्हित लघु RefreshRateTableIndex)
अणु

   अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
         SiS_GetCRT2DataLVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
      पूर्ण अन्यथा अणु
	 अगर((SiS_Pr->SiS_VBType & VB_NoLCD) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) अणु
	    /* Need LVDS Data क्रम LCD on 301B-DH */
	    SiS_GetCRT2DataLVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	 पूर्ण अन्यथा अणु
	    SiS_GetCRT2Data301(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	 पूर्ण
      पूर्ण

   पूर्ण अन्यथा अणु

      SiS_GetCRT2DataLVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);

   पूर्ण
पूर्ण

/*********************************************/
/*         GET LVDS DES (SKEW) DATA          */
/*********************************************/

अटल स्थिर काष्ठा SiS_LVDSDes *
SiS_GetLVDSDesPtr(काष्ठा SiS_Private *SiS_Pr)
अणु
   स्थिर काष्ठा SiS_LVDSDes *PanelDesPtr = शून्य;

#अगर_घोषित CONFIG_FB_SIS_300
   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु

      अगर(SiS_Pr->ChipType < SIS_315H) अणु
	 अगर(SiS_Pr->SiS_LCDTypeInfo == 4) अणु
	    अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1366) अणु
	       PanelDesPtr = SiS_Pr->SiS_PanelType04_1a;
	       अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
		  PanelDesPtr = SiS_Pr->SiS_PanelType04_2a;
	       पूर्ण
            पूर्ण अन्यथा अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1024) अणु
	       PanelDesPtr = SiS_Pr->SiS_PanelType04_1b;
	       अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
		  PanelDesPtr = SiS_Pr->SiS_PanelType04_2b;
	       पूर्ण
	    पूर्ण
	 पूर्ण
      पूर्ण
   पूर्ण
#पूर्ण_अगर
   वापस PanelDesPtr;
पूर्ण

अटल व्योम
SiS_GetLVDSDesData(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
                   अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु modeflag, ResIndex;
  स्थिर काष्ठा SiS_LVDSDes *PanelDesPtr = शून्य;

  SiS_Pr->SiS_LCDHDES = 0;
  SiS_Pr->SiS_LCDVDES = 0;

  /* Some special हालs */
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु

     /* Trumpion */
     अगर(SiS_Pr->SiS_IF_DEF_TRUMPION) अणु
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	   अगर(SiS_Pr->SiS_VGAVDE == SiS_Pr->PanelYRes) अणु
	      SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	   पूर्ण
	पूर्ण
	वापस;
     पूर्ण

     /* 640x480 on LVDS */
     अगर(SiS_Pr->ChipType < SIS_315H) अणु
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_640x480 && SiS_Pr->SiS_LCDTypeInfo == 3) अणु
	   SiS_Pr->SiS_LCDHDES = 8;
	   अगर     (SiS_Pr->SiS_VGAVDE >= 480) SiS_Pr->SiS_LCDVDES = 512;
	   अन्यथा अगर(SiS_Pr->SiS_VGAVDE >= 400) SiS_Pr->SiS_LCDVDES = 436;
	   अन्यथा अगर(SiS_Pr->SiS_VGAVDE >= 350) SiS_Pr->SiS_LCDVDES = 440;
	   वापस;
	पूर्ण
     पूर्ण

  पूर्ण /* LCD */

  अगर( (SiS_Pr->UseCustomMode) 		         ||
      (SiS_Pr->SiS_LCDResInfo == Panel_Custom)   ||
      (SiS_Pr->SiS_CustomT == CUT_PANEL848)      ||
      (SiS_Pr->SiS_CustomT == CUT_PANEL856)      ||
      (SiS_Pr->SiS_LCDInfo & LCDPass11) ) अणु
     वापस;
  पूर्ण

  अगर(ModeNo <= 0x13) ResIndex = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  अन्यथा               ResIndex = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;

  अगर((SiS_Pr->SiS_VBType & VB_SIS30xBLV) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु

#अगर_घोषित CONFIG_FB_SIS_315
     अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	/* non-pass 1:1 only, see above */
	अगर(SiS_Pr->SiS_VGAHDE != SiS_Pr->PanelXRes) अणु
	   SiS_Pr->SiS_LCDHDES = SiS_Pr->SiS_HT - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_VGAHDE) / 2);
	पूर्ण
	अगर(SiS_Pr->SiS_VGAVDE != SiS_Pr->PanelYRes) अणु
	   SiS_Pr->SiS_LCDVDES = SiS_Pr->SiS_VT - ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VGAVDE) / 2);
	पूर्ण
     पूर्ण
     अगर(SiS_Pr->SiS_VGAVDE == SiS_Pr->PanelYRes) अणु
	चयन(SiS_Pr->SiS_CustomT) अणु
	हाल CUT_UNIWILL1024:
	हाल CUT_UNIWILL10242:
	हाल CUT_CLEVO1400:
	   अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	      SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	   पूर्ण
	   अवरोध;
	पूर्ण
	चयन(SiS_Pr->SiS_LCDResInfo) अणु
	हाल Panel_1280x1024:
	   अगर(SiS_Pr->SiS_CustomT != CUT_COMPAQ1280) अणु
	      SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	   पूर्ण
	   अवरोध;
	हाल Panel_1280x800:	/* Verअगरied क्रम Averatec 6240 */
	हाल Panel_1280x800_2:	/* Verअगरied क्रम Asus A4L */
	हाल Panel_1280x854:    /* Not verअगरied yet FIXME */
	   SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	   अवरोध;
	पूर्ण
     पूर्ण
#पूर्ण_अगर

  पूर्ण अन्यथा अणु

     अगर((SiS_Pr->SiS_IF_DEF_CH70xx != 0) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) अणु

	अगर((SiS_Pr->SiS_TVMode & TVSetPAL) && (!(SiS_Pr->SiS_TVMode & TVSetPALM))) अणु
	   अगर(ResIndex <= 3) SiS_Pr->SiS_LCDHDES = 256;
	पूर्ण

     पूर्ण अन्यथा अगर((PanelDesPtr = SiS_GetLVDSDesPtr(SiS_Pr))) अणु

	SiS_Pr->SiS_LCDHDES = (PanelDesPtr+ResIndex)->LCDHDES;
	SiS_Pr->SiS_LCDVDES = (PanelDesPtr+ResIndex)->LCDVDES;

     पूर्ण अन्यथा अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु

	अगर(SiS_Pr->SiS_VGAHDE != SiS_Pr->PanelXRes) अणु
	   SiS_Pr->SiS_LCDHDES = SiS_Pr->SiS_HT - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_VGAHDE) / 2);
	पूर्ण
	अगर(SiS_Pr->SiS_VGAVDE != SiS_Pr->PanelYRes) अणु
	   SiS_Pr->SiS_LCDVDES = SiS_Pr->SiS_VT - ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VGAVDE) / 2);
	पूर्ण अन्यथा अणु
	   अगर(SiS_Pr->ChipType < SIS_315H) अणु
	      SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	   पूर्ण अन्यथा अणु
	      चयन(SiS_Pr->SiS_LCDResInfo) अणु
	      हाल Panel_800x600:
	      हाल Panel_1024x768:
	      हाल Panel_1280x1024:
		 SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT;
		 अवरोध;
	      हाल Panel_1400x1050:
		 SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
		 अवरोध;
	      पूर्ण
	   पूर्ण
	पूर्ण

     पूर्ण अन्यथा अणु

        अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
	   चयन(SiS_Pr->SiS_LCDResInfo) अणु
	   हाल Panel_800x600:
	      अगर(SiS_Pr->SiS_VGAVDE == SiS_Pr->PanelYRes) अणु
		 SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	      पूर्ण अन्यथा अणु
		 SiS_Pr->SiS_LCDHDES = SiS_Pr->PanelHT + 3;
		 SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT;
		 अगर(SiS_Pr->SiS_VGAVDE == 400) SiS_Pr->SiS_LCDVDES -= 2;
		 अन्यथा                          SiS_Pr->SiS_LCDVDES -= 4;
	      पूर्ण
	      अवरोध;
	   हाल Panel_1024x768:
	      अगर(SiS_Pr->SiS_VGAVDE == SiS_Pr->PanelYRes) अणु
		 SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	      पूर्ण अन्यथा अणु
		 SiS_Pr->SiS_LCDHDES = SiS_Pr->PanelHT - 1;
		 अगर(SiS_Pr->SiS_VGAVDE <= 400) SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 8;
		 अगर(SiS_Pr->SiS_VGAVDE <= 350) SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 12;
	      पूर्ण
	      अवरोध;
	   हाल Panel_1024x600:
	   शेष:
	      अगर( (SiS_Pr->SiS_VGAHDE == SiS_Pr->PanelXRes) &&
		  (SiS_Pr->SiS_VGAVDE == SiS_Pr->PanelYRes) ) अणु
		 SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	      पूर्ण अन्यथा अणु
		 SiS_Pr->SiS_LCDHDES = SiS_Pr->PanelHT - 1;
	      पूर्ण
	      अवरोध;
	   पूर्ण

	   चयन(SiS_Pr->SiS_LCDTypeInfo) अणु
	   हाल 1:
	      SiS_Pr->SiS_LCDHDES = SiS_Pr->SiS_LCDVDES = 0;
	      अवरोध;
	   हाल 3: /* 640x480 only? */
	      SiS_Pr->SiS_LCDHDES = 8;
	      अगर     (SiS_Pr->SiS_VGAVDE >= 480) SiS_Pr->SiS_LCDVDES = 512;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE >= 400) SiS_Pr->SiS_LCDVDES = 436;
	      अन्यथा अगर(SiS_Pr->SiS_VGAVDE >= 350) SiS_Pr->SiS_LCDVDES = 440;
	      अवरोध;
	   पूर्ण
#पूर्ण_अगर
        पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
	   चयन(SiS_Pr->SiS_LCDResInfo) अणु
	   हाल Panel_1024x768:
	   हाल Panel_1280x1024:
	      अगर(SiS_Pr->SiS_VGAVDE == SiS_Pr->PanelYRes) अणु
	         SiS_Pr->SiS_LCDVDES = SiS_Pr->PanelVT - 1;
	      पूर्ण
	      अवरोध;
	   हाल Panel_320x240_1:
	   हाल Panel_320x240_2:
	   हाल Panel_320x240_3:
	      SiS_Pr->SiS_LCDVDES = 524;
	      अवरोध;
	   पूर्ण
#पूर्ण_अगर
	पूर्ण
     पूर्ण

     अगर((ModeNo <= 0x13) && (SiS_Pr->SiS_LCDInfo & DontExpandLCD)) अणु
	modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
	अगर((SiS_Pr->SiS_VBType & VB_SIS30xBLV) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
	   अगर(!(modeflag & HalfDCLK)) SiS_Pr->SiS_LCDHDES = 632;
	पूर्ण अन्यथा अगर(!(SiS_Pr->SiS_SetFlag & SetDOSMode)) अणु
	   अगर(SiS_Pr->SiS_LCDResInfo != Panel_1280x1024) अणु
	      अगर(SiS_Pr->SiS_LCDResInfo >= Panel_1024x768) अणु
	         अगर(SiS_Pr->ChipType < SIS_315H) अणु
	            अगर(!(modeflag & HalfDCLK)) SiS_Pr->SiS_LCDHDES = 320;
	         पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
		    अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768)  SiS_Pr->SiS_LCDHDES = 480;
		    अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) SiS_Pr->SiS_LCDHDES = 804;
		    अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) SiS_Pr->SiS_LCDHDES = 704;
		    अगर(!(modeflag & HalfDCLK)) अणु
		       SiS_Pr->SiS_LCDHDES = 320;
		       अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) SiS_Pr->SiS_LCDHDES = 632;
		       अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) SiS_Pr->SiS_LCDHDES = 542;
        	    पूर्ण
#पूर्ण_अगर
		 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण
     पूर्ण
  पूर्ण
पूर्ण

/*********************************************/
/*           DISABLE VIDEO BRIDGE            */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_315
अटल पूर्णांक
SiS_HandlePWD(काष्ठा SiS_Private *SiS_Pr)
अणु
   पूर्णांक ret = 0;
#अगर_घोषित SET_PWD
   अचिन्हित अक्षर *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु romptr = GetLCDStructPtr661_2(SiS_Pr);
   अचिन्हित अक्षर  drivermode = SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40;
   अचिन्हित लघु temp;

   अगर( (SiS_Pr->SiS_VBType & VB_SISPWD) &&
       (romptr)				&&
       (SiS_Pr->SiS_PWDOffset) ) अणु
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x2b,ROMAddr[romptr + SiS_Pr->SiS_PWDOffset + 0]);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x2c,ROMAddr[romptr + SiS_Pr->SiS_PWDOffset + 1]);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x2d,ROMAddr[romptr + SiS_Pr->SiS_PWDOffset + 2]);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x2e,ROMAddr[romptr + SiS_Pr->SiS_PWDOffset + 3]);
      SiS_SetReg(SiS_Pr->SiS_Part4Port,0x2f,ROMAddr[romptr + SiS_Pr->SiS_PWDOffset + 4]);
      temp = 0x00;
      अगर((ROMAddr[romptr + 2] & (0x06 << 1)) && !drivermode) अणु
         temp = 0x80;
	 ret = 1;
      पूर्ण
      SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x27,0x7f,temp);
   पूर्ण
#पूर्ण_अगर
   वापस ret;
पूर्ण
#पूर्ण_अगर

/* NEVER use any variables (VBInfo), this will be called
 * from outside the context of modeचयन!
 * MUST call getVBType beक्रमe calling this
 */
व्योम
SiS_DisableBridge(काष्ठा SiS_Private *SiS_Pr)
अणु
#अगर_घोषित CONFIG_FB_SIS_315
  अचिन्हित लघु tempah, pushax=0, modक्रमागत;
#पूर्ण_अगर
  अचिन्हित लघु temp=0;

  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु		/* ===== For 30xB/C/LV ===== */

	अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300	   /* 300 series */

	   अगर(!(SiS_CR36BIOSWord23b(SiS_Pr))) अणु
	      अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
		 SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFE);
	      पूर्ण अन्यथा अणु
		 SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	      पूर्ण
	      SiS_PanelDelay(SiS_Pr, 3);
	   पूर्ण
	   अगर(SiS_Is301B(SiS_Pr)) अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1f,0x3f);
	      SiS_ShortDelay(SiS_Pr,1);
	   पूर्ण
	   SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xDF);
	   SiS_DisplayOff(SiS_Pr);
	   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);
	   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	   SiS_UnLockCRT2(SiS_Pr);
	   अगर(!(SiS_Pr->SiS_VBType & VB_SISLVDS)) अणु
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x01,0x80);
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40);
	   पूर्ण
	   अगर( (!(SiS_CRT2IsLCD(SiS_Pr))) ||
	       (!(SiS_CR36BIOSWord23d(SiS_Pr))) ) अणु
	      SiS_PanelDelay(SiS_Pr, 2);
	      अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	         SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFD);
	      पूर्ण अन्यथा अणु
		 SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	      पूर्ण
	   पूर्ण

#पूर्ण_अगर  /* CONFIG_FB_SIS_300 */

        पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315	   /* 315 series */

	   पूर्णांक didpwd = 0;
	   bool custom1 = (SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) ||
	                  (SiS_Pr->SiS_CustomT == CUT_CLEVO1400);

	   modक्रमागत = SiS_GetReg(SiS_Pr->SiS_P3d4,0x34) & 0x7f;

	   अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु

#अगर_घोषित SET_EMI
	      अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
		 अगर(SiS_Pr->SiS_CustomT != CUT_CLEVO1400) अणु
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
		 पूर्ण
	      पूर्ण
#पूर्ण_अगर

	      didpwd = SiS_HandlePWD(SiS_Pr);

	      अगर( (modक्रमागत <= 0x13)           ||
		  (SiS_IsVAMode(SiS_Pr))      ||
		  (!(SiS_IsDualEdge(SiS_Pr))) ) अणु
		 अगर(!didpwd) अणु
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xfe);
		    अगर(custom1) SiS_PanelDelay(SiS_Pr, 3);
		 पूर्ण अन्यथा अणु
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xfc);
		 पूर्ण
	      पूर्ण

	      अगर(!custom1) अणु
		 SiS_DDC2Delay(SiS_Pr,0xff00);
		 SiS_DDC2Delay(SiS_Pr,0xe000);
		 SiS_SetRegByte(SiS_Pr->SiS_P3c6,0x00);
		 pushax = SiS_GetReg(SiS_Pr->SiS_P3c4,0x06);
		 अगर(IS_SIS740) अणु
		    SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x06,0xE3);
		 पूर्ण
	         SiS_PanelDelay(SiS_Pr, 3);
	      पूर्ण

	   पूर्ण

	   अगर(!(SiS_IsNotM650orLater(SiS_Pr))) अणु
	      /* अगर(SiS_Pr->ChipType < SIS_340) अणु*/
		 tempah = 0xef;
		 अगर(SiS_IsVAMode(SiS_Pr)) tempah = 0xf7;
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x4c,tempah);
	      /*पूर्ण*/
	   पूर्ण

	   अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1F,~0x10);
	   पूर्ण

	   tempah = 0x3f;
	   अगर(SiS_IsDualEdge(SiS_Pr)) अणु
	      tempah = 0x7f;
	      अगर(!(SiS_IsVAMode(SiS_Pr))) tempah = 0xbf;
	   पूर्ण
	   SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1F,tempah);

	   अगर((SiS_IsVAMode(SiS_Pr)) ||
	      ((SiS_Pr->SiS_VBType & VB_SISLVDS) && (modक्रमागत <= 0x13))) अणु

	      SiS_DisplayOff(SiS_Pr);
	      अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
		 SiS_PanelDelay(SiS_Pr, 2);
	      पूर्ण
	      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1E,0xDF);

	   पूर्ण

	   अगर((!(SiS_IsVAMode(SiS_Pr))) ||
	      ((SiS_Pr->SiS_VBType & VB_SISLVDS) && (modक्रमागत <= 0x13))) अणु

	      अगर(!(SiS_IsDualEdge(SiS_Pr))) अणु
		 SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xdf);
		 SiS_DisplayOff(SiS_Pr);
	      पूर्ण
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x80);

	      अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
		 SiS_PanelDelay(SiS_Pr, 2);
	      पूर्ण

	      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);
	      temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00);
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x10);
	      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,temp);

	   पूर्ण

	   अगर(SiS_IsNotM650orLater(SiS_Pr)) अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
	   पूर्ण

	   अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु

	      अगर( (!(SiS_IsVAMode(SiS_Pr)))  &&
		  (!(SiS_CRT2IsLCD(SiS_Pr))) &&
		  (!(SiS_IsDualEdge(SiS_Pr))) ) अणु

		 अगर(custom1) SiS_PanelDelay(SiS_Pr, 2);
		 अगर(!didpwd) अणु
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFD);
		 पूर्ण
		 अगर(custom1) SiS_PanelDelay(SiS_Pr, 4);
	      पूर्ण

	      अगर(!custom1) अणु
		 SiS_SetReg(SiS_Pr->SiS_P3c4,0x06,pushax);
		 अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
		    अगर(SiS_IsVAorLCD(SiS_Pr)) अणु
		       SiS_PanelDelayLoop(SiS_Pr, 3, 20);
		    पूर्ण
		 पूर्ण
	      पूर्ण

	   पूर्ण

#पूर्ण_अगर /* CONFIG_FB_SIS_315 */

	पूर्ण

     पूर्ण अन्यथा अणु     /* ============ For 301 ================ */

        अगर(SiS_Pr->ChipType < SIS_315H) अणु
#अगर_घोषित CONFIG_FB_SIS_300
	   अगर(!(SiS_CR36BIOSWord23b(SiS_Pr))) अणु
	      SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	      SiS_PanelDelay(SiS_Pr, 3);
	   पूर्ण
#पूर्ण_अगर
	पूर्ण

	SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xDF);           /* disable VB */
	SiS_DisplayOff(SiS_Pr);

	अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x80);
	पूर्ण

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);                /* disable lock mode */

	अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	    temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00);
	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x10);
	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
	    SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,temp);
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_300
	    SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);            /* disable CRT2 */
	    अगर( (!(SiS_CRT2IsLCD(SiS_Pr))) ||
		(!(SiS_CR36BIOSWord23d(SiS_Pr))) ) अणु
		SiS_PanelDelay(SiS_Pr, 2);
		SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	    पूर्ण
#पूर्ण_अगर
	पूर्ण

      पूर्ण

  पूर्ण अन्यथा अणु     /* ============ For LVDS =============*/

    अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300	/* 300 series */

	अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 1) अणु
	   SiS_SetCH700x(SiS_Pr,0x0E,0x09);
	पूर्ण

	अगर(SiS_Pr->ChipType == SIS_730) अणु
	   अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x11) & 0x08)) अणु
	      SiS_WaitVBRetrace(SiS_Pr);
	   पूर्ण
	   अगर(!(SiS_CR36BIOSWord23b(SiS_Pr))) अणु
	      SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	      SiS_PanelDelay(SiS_Pr, 3);
	   पूर्ण
	पूर्ण अन्यथा अणु
	   अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x11) & 0x08)) अणु
	      अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x40)) अणु
		 अगर(!(SiS_CR36BIOSWord23b(SiS_Pr))) अणु
		    SiS_WaitVBRetrace(SiS_Pr);
		    अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x06) & 0x1c)) अणु
		       SiS_DisplayOff(SiS_Pr);
		    पूर्ण
		    SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
		    SiS_PanelDelay(SiS_Pr, 3);
		 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण

	SiS_DisplayOff(SiS_Pr);

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	SiS_UnLockCRT2(SiS_Pr);
	SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x01,0x80);
	SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40);

	अगर( (!(SiS_CRT2IsLCD(SiS_Pr))) ||
	    (!(SiS_CR36BIOSWord23d(SiS_Pr))) ) अणु
	   SiS_PanelDelay(SiS_Pr, 2);
	   SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	पूर्ण

#पूर्ण_अगर  /* CONFIG_FB_SIS_300 */

    पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315	/* 315 series */

	अगर(!(SiS_IsNotM650orLater(SiS_Pr))) अणु
	   /*अगर(SiS_Pr->ChipType < SIS_340) अणु */ /* XGI needs this */
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x4c,~0x18);
	   /* पूर्ण */
	पूर्ण

	अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु

	   अगर(SiS_Pr->ChipType == SIS_740) अणु
	      temp = SiS_GetCH701x(SiS_Pr,0x61);
	      अगर(temp < 1) अणु
		 SiS_SetCH701x(SiS_Pr,0x76,0xac);
		 SiS_SetCH701x(SiS_Pr,0x66,0x00);
	      पूर्ण

	      अगर( (!(SiS_IsDualEdge(SiS_Pr))) ||
		  (SiS_IsTVOrYPbPrOrScart(SiS_Pr)) ) अणु
		 SiS_SetCH701x(SiS_Pr,0x49,0x3e);
	      पूर्ण
	   पूर्ण

	   अगर( (!(SiS_IsDualEdge(SiS_Pr))) ||
	       (SiS_IsVAMode(SiS_Pr)) ) अणु
	      SiS_Chrontel701xBLOff(SiS_Pr);
	      SiS_Chrontel701xOff(SiS_Pr);
	   पूर्ण

	   अगर(SiS_Pr->ChipType != SIS_740) अणु
	      अगर( (!(SiS_IsDualEdge(SiS_Pr))) ||
		  (SiS_IsTVOrYPbPrOrScart(SiS_Pr)) ) अणु
		 SiS_SetCH701x(SiS_Pr,0x49,0x01);
	      पूर्ण
	   पूर्ण

	पूर्ण

	अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 0) अणु
	   SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	   SiS_PanelDelay(SiS_Pr, 3);
	पूर्ण

	अगर( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
	    (!(SiS_IsDualEdge(SiS_Pr))) ||
	    (!(SiS_IsTVOrYPbPrOrScart(SiS_Pr))) ) अणु
	   SiS_DisplayOff(SiS_Pr);
	पूर्ण

	अगर( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
	    (!(SiS_IsDualEdge(SiS_Pr))) ||
	    (!(SiS_IsVAMode(SiS_Pr))) ) अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x80);
	पूर्ण

	अगर(SiS_Pr->ChipType == SIS_740) अणु
	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
	पूर्ण

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);

	अगर( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
	    (!(SiS_IsDualEdge(SiS_Pr))) ||
	    (!(SiS_IsVAMode(SiS_Pr))) ) अणु
	   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	पूर्ण

	अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 0) अणु
	   अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xdf);
	      अगर(SiS_Pr->ChipType == SIS_550) अणु
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xbf);
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xef);
	      पूर्ण
	   पूर्ण
	पूर्ण अन्यथा अणु
	   अगर(SiS_Pr->ChipType == SIS_740) अणु
	      अगर(SiS_IsLCDOrLCDA(SiS_Pr)) अणु
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xdf);
	      पूर्ण
	   पूर्ण अन्यथा अगर(SiS_IsVAMode(SiS_Pr)) अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xdf);
	   पूर्ण
	पूर्ण

	अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	   अगर(SiS_IsDualEdge(SiS_Pr)) अणु
	      /* SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xff); */
	   पूर्ण अन्यथा अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	   पूर्ण
	पूर्ण

	SiS_UnLockCRT2(SiS_Pr);

	अगर(SiS_Pr->ChipType == SIS_550) अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x01,0x80); /* DirectDVD PAL?*/
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40); /* VB घड़ी / 4 ? */
	पूर्ण अन्यथा अगर( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
		   (!(SiS_IsDualEdge(SiS_Pr))) ||
		   (!(SiS_IsVAMode(SiS_Pr))) ) अणु
	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0xf7);
	पूर्ण

        अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 0) अणु
	   अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	      अगर(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) अणु
		 SiS_PanelDelay(SiS_Pr, 2);
		 SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	      पूर्ण
	   पूर्ण
        पूर्ण

#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */

    पूर्ण  /* 315 series */

  पूर्ण  /* LVDS */

पूर्ण

/*********************************************/
/*            ENABLE VIDEO BRIDGE            */
/*********************************************/

/* NEVER use any variables (VBInfo), this will be called
 * from outside the context of a mode चयन!
 * MUST call getVBType beक्रमe calling this
 */
अटल
व्योम
SiS_EnableBridge(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु temp=0, tempah;
#अगर_घोषित CONFIG_FB_SIS_315
  अचिन्हित लघु temp1, pushax=0;
  bool delayदीर्घ = false;
#पूर्ण_अगर

  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

    अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु		/* ====== For 301B et al  ====== */

      अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300     /* 300 series */

	 अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	    अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	       SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x02);
	    पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_NoLCD) अणु
	       SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	    पूर्ण
	    अगर(SiS_Pr->SiS_VBType & (VB_SISLVDS | VB_NoLCD)) अणु
	       अगर(!(SiS_CR36BIOSWord23d(SiS_Pr))) अणु
		  SiS_PanelDelay(SiS_Pr, 0);
	       पूर्ण
	    पूर्ण
	 पूर्ण

	 अगर((SiS_Pr->SiS_VBType & VB_NoLCD) &&
	    (SiS_CRT2IsLCD(SiS_Pr))) अणु

	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);   		/* Enable CRT2 */
	    SiS_DisplayOn(SiS_Pr);
	    SiS_UnLockCRT2(SiS_Pr);
	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0xBF);
	    अगर(SiS_BridgeInSlavemode(SiS_Pr)) अणु
	       SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x01,0x1F);
	    पूर्ण अन्यथा अणु
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x01,0x1F,0x40);
	    पूर्ण
	    अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x40)) अणु
	       अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x10)) अणु
		  अगर(!(SiS_CR36BIOSWord23b(SiS_Pr))) अणु
		     SiS_PanelDelay(SiS_Pr, 1);
		  पूर्ण
		  SiS_WaitVBRetrace(SiS_Pr);
		  SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	       पूर्ण
	    पूर्ण

	 पूर्ण अन्यथा अणु

	    temp = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32) & 0xDF;             /* lock mode */
	    अगर(SiS_BridgeInSlavemode(SiS_Pr)) अणु
	       tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	       अगर(!(tempah & SetCRT2ToRAMDAC)) temp |= 0x20;
	    पूर्ण
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,temp);
	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x00,0x1F,0x20);        /* enable VB processor */
	    SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x1F,0xC0);
	    SiS_DisplayOn(SiS_Pr);
	    अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	       अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
		  अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x10)) अणु
		     अगर(!(SiS_CR36BIOSWord23b(SiS_Pr))) अणु
		        SiS_PanelDelay(SiS_Pr, 1);
		     पूर्ण
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x01);
		  पूर्ण
	       पूर्ण
	    पूर्ण

	 पूर्ण


#पूर्ण_अगर /* CONFIG_FB_SIS_300 */

      पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315    /* 315 series */

#अगर_घोषित SET_EMI
	 अचिन्हित अक्षर   r30=0, r31=0, r32=0, r33=0, cr36=0;
	 पूर्णांक didpwd = 0;
	 /* अचिन्हित लघु  emidelay=0; */
#पूर्ण_अगर

	 अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1f,0xef);
#अगर_घोषित SET_EMI
	    अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
	       SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
	    पूर्ण
#पूर्ण_अगर
	 पूर्ण

	 अगर(!(SiS_IsNotM650orLater(SiS_Pr))) अणु
	    /*अगर(SiS_Pr->ChipType < SIS_340) अणु */
	       tempah = 0x10;
	       अगर(SiS_LCDAEnabled(SiS_Pr)) अणु
		  अगर(SiS_TVEnabled(SiS_Pr)) tempah = 0x18;
		  अन्यथा			    tempah = 0x08;
	       पूर्ण
	       SiS_SetReg(SiS_Pr->SiS_Part1Port,0x4c,tempah);
	    /*पूर्ण*/
	 पूर्ण

	 अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु

	    SiS_SetRegByte(SiS_Pr->SiS_P3c6,0x00);
	    SiS_DisplayOff(SiS_Pr);
	    pushax = SiS_GetReg(SiS_Pr->SiS_P3c4,0x06);
	    अगर(IS_SIS740) अणु
	       SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x06,0xE3);
	    पूर्ण

	    didpwd = SiS_HandlePWD(SiS_Pr);

	    अगर(SiS_IsVAorLCD(SiS_Pr)) अणु
	       अगर(!didpwd) अणु
		  अगर(!(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x02)) अणु
		     SiS_PanelDelayLoop(SiS_Pr, 3, 2);
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x02);
		     SiS_PanelDelayLoop(SiS_Pr, 3, 2);
		     अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
		        SiS_GenericDelay(SiS_Pr, 17664);
		     पूर्ण
		  पूर्ण
	       पूर्ण अन्यथा अणु
		  SiS_PanelDelayLoop(SiS_Pr, 3, 2);
		  अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
		     SiS_GenericDelay(SiS_Pr, 17664);
		  पूर्ण
	       पूर्ण
	    पूर्ण

	    अगर(!(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40)) अणु
	       SiS_PanelDelayLoop(SiS_Pr, 3, 10);
	       delayदीर्घ = true;
	    पूर्ण

	 पूर्ण

	 अगर(!(SiS_IsVAMode(SiS_Pr))) अणु

	    temp = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32) & 0xDF;
	    अगर(SiS_BridgeInSlavemode(SiS_Pr)) अणु
	       tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	       अगर(!(tempah & SetCRT2ToRAMDAC)) अणु
		  अगर(!(SiS_LCDAEnabled(SiS_Pr))) temp |= 0x20;
	       पूर्ण
	    पूर्ण
	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,temp);

	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);                   /* enable CRT2 */

	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2e,0x80);

	    अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	       SiS_PanelDelay(SiS_Pr, 2);
	    पूर्ण

	 पूर्ण अन्यथा अणु

	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1e,0x20);

	 पूर्ण

	 SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x00,0x1f,0x20);
	 SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2e,0x80);

	 अगर(SiS_Pr->SiS_VBType & VB_SISPOWER) अणु
	    अगर( (SiS_LCDAEnabled(SiS_Pr)) ||
	        (SiS_CRT2IsLCD(SiS_Pr)) ) अणु
	       /* Enable "LVDS PLL power on" (even on 301C) */
	       SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x2a,0x7f);
	       /* Enable "LVDS Driver Power on" (even on 301C) */
	       SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x7f);
	    पूर्ण
	 पूर्ण

	 tempah = 0xc0;
	 अगर(SiS_IsDualEdge(SiS_Pr)) अणु
	    tempah = 0x80;
	    अगर(!(SiS_IsVAMode(SiS_Pr))) tempah = 0x40;
	 पूर्ण
	 SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x1F,tempah);

	 अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु

	    SiS_PanelDelay(SiS_Pr, 2);

	    SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x1f,0x10);
	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2e,0x80);

	    अगर(SiS_Pr->SiS_CustomT != CUT_CLEVO1400) अणु
#अगर_घोषित SET_EMI
	       अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
		  SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
		  SiS_GenericDelay(SiS_Pr, 2048);
	       पूर्ण
#पूर्ण_अगर
	       SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x27,0x0c);

	       अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
#अगर_घोषित SET_EMI
		  cr36 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36);

		  अगर(SiS_Pr->SiS_ROMNew) अणु
		     अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
		     अचिन्हित लघु romptr = GetLCDStructPtr661_2(SiS_Pr);
		     अगर(romptr) अणु
			SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x30,0x20); /* Reset */
			SiS_Pr->EMI_30 = 0;
			SiS_Pr->EMI_31 = ROMAddr[romptr + SiS_Pr->SiS_EMIOffset + 0];
			SiS_Pr->EMI_32 = ROMAddr[romptr + SiS_Pr->SiS_EMIOffset + 1];
			SiS_Pr->EMI_33 = ROMAddr[romptr + SiS_Pr->SiS_EMIOffset + 2];
			अगर(ROMAddr[romptr + 1] & 0x10) SiS_Pr->EMI_30 = 0x40;
			/* emidelay = SISGETROMW((romptr + 0x22)); */
			SiS_Pr->HaveEMI = SiS_Pr->HaveEMILCD = SiS_Pr->OverruleEMI = true;
		     पूर्ण
		  पूर्ण

		  /*                                              (P4_30|0x40)  */
		  /* Compal 1400x1050: 0x05, 0x60, 0x00                YES  (1.10.7w;  CR36=69)      */
		  /* Compal 1400x1050: 0x0d, 0x70, 0x40                YES  (1.10.7x;  CR36=69)      */
		  /* Acer   1280x1024: 0x12, 0xd0, 0x6b                NO   (1.10.9k;  CR36=73)      */
		  /* Compaq 1280x1024: 0x0d, 0x70, 0x6b                YES  (1.12.04b; CR36=03)      */
		  /* Clevo   1024x768: 0x05, 0x60, 0x33                NO   (1.10.8e;  CR36=12, DL!) */
		  /* Clevo   1024x768: 0x0d, 0x70, 0x40 (अगर type == 3) YES  (1.10.8y;  CR36=?2)      */
		  /* Clevo   1024x768: 0x05, 0x60, 0x33 (अगर type != 3) YES  (1.10.8y;  CR36=?2)      */
		  /* Asus    1024x768: ?                                ?   (1.10.8o;  CR36=?2)      */
		  /* Asus    1024x768: 0x08, 0x10, 0x3c (problematic)  YES  (1.10.8q;  CR36=22)      */

		  अगर(SiS_Pr->HaveEMI) अणु
		     r30 = SiS_Pr->EMI_30; r31 = SiS_Pr->EMI_31;
		     r32 = SiS_Pr->EMI_32; r33 = SiS_Pr->EMI_33;
		  पूर्ण अन्यथा अणु
		     r30 = 0;
		  पूर्ण

		  /* EMI_30 is पढ़ो at driver start; however, the BIOS sets this
		   * (अगर it is used) only अगर the LCD is in use. In हाल we caught
		   * the machine जबतक on TV output, this bit is not set and we
		   * करोn't know अगर it should be set - hence our detection is wrong.
		   * Work-around this here:
		   */

		  अगर((!SiS_Pr->HaveEMI) || (!SiS_Pr->HaveEMILCD)) अणु
		     चयन((cr36 & 0x0f)) अणु
		     हाल 2:
			r30 |= 0x40;
			अगर(SiS_Pr->SiS_CustomT == CUT_CLEVO1024) r30 &= ~0x40;
			अगर(!SiS_Pr->HaveEMI) अणु
			   r31 = 0x05; r32 = 0x60; r33 = 0x33;
			   अगर((cr36 & 0xf0) == 0x30) अणु
			      r31 = 0x0d; r32 = 0x70; r33 = 0x40;
			   पूर्ण
			पूर्ण
			अवरोध;
		     हाल 3:  /* 1280x1024 */
			अगर(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) r30 |= 0x40;
			अगर(!SiS_Pr->HaveEMI) अणु
			   r31 = 0x12; r32 = 0xd0; r33 = 0x6b;
			   अगर(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) अणु
			      r31 = 0x0d; r32 = 0x70; r33 = 0x6b;
			   पूर्ण
			पूर्ण
			अवरोध;
		     हाल 9:  /* 1400x1050 */
			r30 |= 0x40;
			अगर(!SiS_Pr->HaveEMI) अणु
			   r31 = 0x05; r32 = 0x60; r33 = 0x00;
			   अगर(SiS_Pr->SiS_CustomT == CUT_COMPAL1400_2) अणु
			      r31 = 0x0d; r32 = 0x70; r33 = 0x40;  /* BIOS values */
			   पूर्ण
			पूर्ण
			अवरोध;
		     हाल 11: /* 1600x1200 - unknown */
			r30 |= 0x40;
			अगर(!SiS_Pr->HaveEMI) अणु
			   r31 = 0x05; r32 = 0x60; r33 = 0x00;
			पूर्ण
		     पूर्ण
                  पूर्ण

		  /* BIOS values करोn't work so well someबार */
		  अगर(!SiS_Pr->OverruleEMI) अणु
#अगर_घोषित COMPAL_HACK
		     अगर(SiS_Pr->SiS_CustomT == CUT_COMPAL1400_2) अणु
			अगर((cr36 & 0x0f) == 0x09) अणु
			   r30 = 0x60; r31 = 0x05; r32 = 0x60; r33 = 0x00;
			पूर्ण
 		     पूर्ण
#पूर्ण_अगर
#अगर_घोषित COMPAQ_HACK
		     अगर(SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) अणु
			अगर((cr36 & 0x0f) == 0x03) अणु
			   r30 = 0x20; r31 = 0x12; r32 = 0xd0; r33 = 0x6b;
			पूर्ण
		     पूर्ण
#पूर्ण_अगर
#अगर_घोषित ASUS_HACK
		     अगर(SiS_Pr->SiS_CustomT == CUT_ASUSA2H_2) अणु
			अगर((cr36 & 0x0f) == 0x02) अणु
			   /* r30 = 0x60; r31 = 0x05; r32 = 0x60; r33 = 0x33;  */   /* rev 2 */
			   /* r30 = 0x20; r31 = 0x05; r32 = 0x60; r33 = 0x33;  */   /* rev 3 */
			   /* r30 = 0x60; r31 = 0x0d; r32 = 0x70; r33 = 0x40;  */   /* rev 4 */
			   /* r30 = 0x20; r31 = 0x0d; r32 = 0x70; r33 = 0x40;  */   /* rev 5 */
			पूर्ण
		     पूर्ण
#पूर्ण_अगर
		  पूर्ण

		  अगर(!(SiS_Pr->OverruleEMI && (!r30) && (!r31) && (!r32) && (!r33))) अणु
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x30,0x20); /* Reset */
		     SiS_GenericDelay(SiS_Pr, 2048);
		  पूर्ण
		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x31,r31);
		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x32,r32);
		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x33,r33);
#पूर्ण_अगर	/* SET_EMI */

		  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x34,0x10);

#अगर_घोषित SET_EMI
		  अगर( (SiS_LCDAEnabled(SiS_Pr)) ||
		      (SiS_CRT2IsLCD(SiS_Pr)) ) अणु
		     अगर(r30 & 0x40) अणु
			/*SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x2a,0x80);*/
			SiS_PanelDelayLoop(SiS_Pr, 3, 5);
			अगर(delayदीर्घ) अणु
			   SiS_PanelDelayLoop(SiS_Pr, 3, 5);
			   delayदीर्घ = false;
			पूर्ण
			SiS_WaitVBRetrace(SiS_Pr);
			SiS_WaitVBRetrace(SiS_Pr);
			अगर(SiS_Pr->SiS_CustomT == CUT_ASUSA2H_2) अणु
			   SiS_GenericDelay(SiS_Pr, 1280);
			पूर्ण
			SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x30,0x40);   /* Enable */
			/*SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x2a,0x7f);*/
		     पूर्ण
		  पूर्ण
#पूर्ण_अगर
	       पूर्ण
	    पूर्ण

	    अगर(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) अणु
	       अगर(SiS_IsVAorLCD(SiS_Pr)) अणु
		  SiS_PanelDelayLoop(SiS_Pr, 3, 10);
		  अगर(delayदीर्घ) अणु
		     SiS_PanelDelayLoop(SiS_Pr, 3, 10);
		  पूर्ण
		  SiS_WaitVBRetrace(SiS_Pr);
		  अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
		     SiS_GenericDelay(SiS_Pr, 2048);
		     SiS_WaitVBRetrace(SiS_Pr);
		  पूर्ण
		  अगर(!didpwd) अणु
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x01);
		  पूर्ण अन्यथा अणु
		     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x03);
		  पूर्ण
	       पूर्ण
	    पूर्ण

	    SiS_SetReg(SiS_Pr->SiS_P3c4,0x06,pushax);
	    SiS_DisplayOn(SiS_Pr);
	    SiS_SetRegByte(SiS_Pr->SiS_P3c6,0xff);

	 पूर्ण

	 अगर(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) अणु
	    SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x00,0x7f);
	 पूर्ण

#पूर्ण_अगर /* CONFIG_FB_SIS_315 */

      पूर्ण

    पूर्ण अन्यथा अणु	/* ============  For 301 ================ */

       अगर(SiS_Pr->ChipType < SIS_315H) अणु
	  अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	     SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	     SiS_PanelDelay(SiS_Pr, 0);
	  पूर्ण
       पूर्ण

       temp = SiS_GetReg(SiS_Pr->SiS_P3c4,0x32) & 0xDF;          /* lock mode */
       अगर(SiS_BridgeInSlavemode(SiS_Pr)) अणु
	  tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x30);
	  अगर(!(tempah & SetCRT2ToRAMDAC)) temp |= 0x20;
       पूर्ण
       SiS_SetReg(SiS_Pr->SiS_P3c4,0x32,temp);

       SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);                  /* enable CRT2 */

       अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	  temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x2E);
	  अगर(!(temp & 0x80)) अणु
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2E,0x80);         /* BVBDOENABLE=1 */
	  पूर्ण
       पूर्ण

       SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x00,0x1F,0x20);     /* enable VB processor */

       SiS_VBLongWait(SiS_Pr);
       SiS_DisplayOn(SiS_Pr);
       अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x00,0x7f);
       पूर्ण
       SiS_VBLongWait(SiS_Pr);

       अगर(SiS_Pr->ChipType < SIS_315H) अणु
	  अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	     SiS_PanelDelay(SiS_Pr, 1);
	     SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	  पूर्ण
       पूर्ण

    पूर्ण

  पूर्ण अन्यथा अणु   /* =================== For LVDS ================== */

    अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300    /* 300 series */

       अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	  अगर(SiS_Pr->ChipType == SIS_730) अणु
	     SiS_PanelDelay(SiS_Pr, 1);
	     SiS_PanelDelay(SiS_Pr, 1);
	     SiS_PanelDelay(SiS_Pr, 1);
	  पूर्ण
	  SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	  अगर(!(SiS_CR36BIOSWord23d(SiS_Pr))) अणु
	     SiS_PanelDelay(SiS_Pr, 0);
	  पूर्ण
       पूर्ण

       SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
       SiS_DisplayOn(SiS_Pr);
       SiS_UnLockCRT2(SiS_Pr);
       SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0xBF);
       अगर(SiS_BridgeInSlavemode(SiS_Pr)) अणु
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x01,0x1F);
       पूर्ण अन्यथा अणु
	  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x01,0x1F,0x40);
       पूर्ण

       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 1) अणु
	  अगर(!(SiS_CRT2IsLCD(SiS_Pr))) अणु
	     SiS_WaitVBRetrace(SiS_Pr);
	     SiS_SetCH700x(SiS_Pr,0x0E,0x0B);
	  पूर्ण
       पूर्ण

       अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	  अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x40)) अणु
	     अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x16) & 0x10)) अणु
		अगर(!(SiS_CR36BIOSWord23b(SiS_Pr))) अणु
		   SiS_PanelDelay(SiS_Pr, 1);
		   SiS_PanelDelay(SiS_Pr, 1);
		पूर्ण
		SiS_WaitVBRetrace(SiS_Pr);
		SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	     पूर्ण
	  पूर्ण
       पूर्ण

#पूर्ण_अगर  /* CONFIG_FB_SIS_300 */

    पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315    /* 315 series */

       अगर(!(SiS_IsNotM650orLater(SiS_Pr))) अणु
	  /*अगर(SiS_Pr->ChipType < SIS_340) अणु*/  /* XGI needs this */
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x4c,0x18);
	  /*पूर्ण*/
       पूर्ण

       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 0) अणु
	  अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	     SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x00);
	     SiS_PanelDelay(SiS_Pr, 0);
	  पूर्ण
       पूर्ण

       SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
       SiS_UnLockCRT2(SiS_Pr);

       SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0xf7);

       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	  temp = SiS_GetCH701x(SiS_Pr,0x66);
	  temp &= 0x20;
	  SiS_Chrontel701xBLOff(SiS_Pr);
       पूर्ण

       अगर(SiS_Pr->ChipType != SIS_550) अणु
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
       पूर्ण

       अगर(SiS_Pr->ChipType == SIS_740) अणु
	  अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	     अगर(SiS_IsLCDOrLCDA(SiS_Pr)) अणु
		SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x20);
	     पूर्ण
	  पूर्ण
       पूर्ण

       temp1 = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x2E);
       अगर(!(temp1 & 0x80)) अणु
	  SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2E,0x80);
       पूर्ण

       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	  अगर(temp) अणु
	     SiS_Chrontel701xBLOn(SiS_Pr);
	  पूर्ण
       पूर्ण

       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 0) अणु
	  अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x20);
	     अगर(SiS_Pr->ChipType == SIS_550) अणु
		SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x40);
		SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x10);
	     पूर्ण
	  पूर्ण
       पूर्ण अन्यथा अगर(SiS_IsVAMode(SiS_Pr)) अणु
	  अगर(SiS_Pr->ChipType != SIS_740) अणु
	     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1E,0x20);
	  पूर्ण
       पूर्ण

       अगर(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) अणु
	  SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x00,0x7f);
       पूर्ण

       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	  अगर(SiS_IsTVOrYPbPrOrScart(SiS_Pr)) अणु
	     SiS_Chrontel701xOn(SiS_Pr);
	  पूर्ण
	  अगर( (SiS_IsVAMode(SiS_Pr)) ||
	      (SiS_IsLCDOrLCDA(SiS_Pr)) ) अणु
	     SiS_ChrontelDoSomething1(SiS_Pr);
	  पूर्ण
       पूर्ण

       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
	  अगर(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) अणु
	     अगर( (SiS_IsVAMode(SiS_Pr)) ||
		 (SiS_IsLCDOrLCDA(SiS_Pr)) ) अणु
		SiS_Chrontel701xBLOn(SiS_Pr);
		SiS_ChrontelInitTVVSync(SiS_Pr);
	     पूर्ण
	  पूर्ण
       पूर्ण अन्यथा अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 0) अणु
	  अगर(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) अणु
	     अगर(SiS_CRT2IsLCD(SiS_Pr)) अणु
		SiS_PanelDelay(SiS_Pr, 1);
		SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x00);
	     पूर्ण
	  पूर्ण
       पूर्ण

#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */

    पूर्ण /* 310 series */

  पूर्ण  /* LVDS */

पूर्ण

/*********************************************/
/*         SET PART 1 REGISTER GROUP         */
/*********************************************/

/* Set CRT2 OFFSET / PITCH */
अटल व्योम
SiS_SetCRT2Offset(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RRTI)
अणु
   अचिन्हित लघु offset;
   अचिन्हित अक्षर  temp;

   अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) वापस;

   offset = SiS_GetOffset(SiS_Pr,ModeNo,ModeIdIndex,RRTI);

   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x07,(offset & 0xFF));
   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x09,(offset >> 8));

   temp = (अचिन्हित अक्षर)(((offset >> 3) & 0xFF) + 1);
   अगर(offset & 0x07) temp++;
   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x03,temp);
पूर्ण

/* Set CRT2 sync and PanelLink mode */
अटल व्योम
SiS_SetCRT2Sync(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु RefreshRateTableIndex)
अणु
   अचिन्हित लघु tempah=0, tempbl, infoflag;

   tempbl = 0xC0;

   अगर(SiS_Pr->UseCustomMode) अणु
      infoflag = SiS_Pr->CInfoFlag;
   पूर्ण अन्यथा अणु
      infoflag = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;
   पूर्ण

   अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु					/* LVDS */

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	 tempah = 0;
      पूर्ण अन्यथा अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) && (SiS_Pr->SiS_LCDInfo & LCDSync)) अणु
	 tempah = SiS_Pr->SiS_LCDInfo;
      पूर्ण अन्यथा tempah = infoflag >> 8;
      tempah &= 0xC0;
      tempah |= 0x20;
      अगर(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	 अगर((SiS_Pr->SiS_CustomT == CUT_BARCO1366) ||
	    (SiS_Pr->SiS_CustomT == CUT_BARCO1024)) अणु
	    tempah |= 0xf0;
	 पूर्ण
	 अगर( (SiS_Pr->SiS_IF_DEF_FSTN) ||
	     (SiS_Pr->SiS_IF_DEF_DSTN) ||
	     (SiS_Pr->SiS_IF_DEF_TRUMPION) ||
	     (SiS_Pr->SiS_CustomT == CUT_PANEL848) ||
	     (SiS_Pr->SiS_CustomT == CUT_PANEL856) ) अणु
	    tempah |= 0x30;
	 पूर्ण
	 अगर( (SiS_Pr->SiS_IF_DEF_FSTN) ||
	     (SiS_Pr->SiS_IF_DEF_DSTN) ) अणु
	    tempah &= ~0xc0;
	 पूर्ण
      पूर्ण
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	 अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	    tempah >>= 3;
	    tempah &= 0x18;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xE7,tempah);
	    /* Don't care about 12/18/24 bit mode - TV is via VGA, not PL */
	 पूर्ण अन्यथा अणु
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,0xe0);
	 पूर्ण
      पूर्ण अन्यथा अणु
	 SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
      पूर्ण

   पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

      अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300  /* ---- 300 series --- */

	 अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु			/* 630 - 301B(-DH) */

	    tempah = infoflag >> 8;
	    tempbl = 0;
	    अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	       अगर(SiS_Pr->SiS_LCDInfo & LCDSync) अणु
		  tempah = SiS_Pr->SiS_LCDInfo;
		  tempbl = (tempah >> 6) & 0x03;
	       पूर्ण
	    पूर्ण
	    tempah &= 0xC0;
	    tempah |= 0x20;
	    अगर(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    tempah |= 0xc0;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
	    अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) && (!(SiS_Pr->SiS_VBType & VB_NoLCD))) अणु
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1a,0xf0,tempbl);
	    पूर्ण

	 पूर्ण अन्यथा अणु							/* 630 - 301 */

	    tempah = ((infoflag >> 8) & 0xc0) | 0x20;
	    अगर(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);

	 पूर्ण

#पूर्ण_अगर /* CONFIG_FB_SIS_300 */

      पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315  /* ------- 315 series ------ */

	 अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु	  		/* 315 - LVDS */

	    tempbl = 0;
	    अगर((SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) &&
	       (SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)) अणु
	       tempah = infoflag >> 8;
	       अगर(SiS_Pr->SiS_LCDInfo & LCDSync) अणु
		 tempbl = ((SiS_Pr->SiS_LCDInfo & 0xc0) >> 6);
	       पूर्ण
	    पूर्ण अन्यथा अगर((SiS_Pr->SiS_CustomT == CUT_CLEVO1400)  &&
		      (SiS_Pr->SiS_LCDResInfo == Panel_1400x1050)) अणु
	       tempah = infoflag >> 8;
	       tempbl = 0x03;
	    पूर्ण अन्यथा अणु
	       tempah = SiS_GetReg(SiS_Pr->SiS_P3d4,0x37);
	       tempbl = (tempah >> 6) & 0x03;
	       tempbl |= 0x08;
	       अगर(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempbl |= 0x04;
	    पूर्ण
	    tempah &= 0xC0;
	    tempah |= 0x20;
	    अगर(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)   tempah |= 0xc0;
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
	    अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	       अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
		  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1a,0xf0,tempbl);
	       पूर्ण
	    पूर्ण

	 पूर्ण अन्यथा अणु							/* 315 - TMDS */

	    tempah = tempbl = infoflag >> 8;
	    अगर(!SiS_Pr->UseCustomMode) अणु
	       tempbl = 0;
	       अगर((SiS_Pr->SiS_VBType & VB_SIS30xC) && (SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) अणु
		  अगर(ModeNo <= 0x13) अणु
		     tempah = SiS_GetRegByte((SiS_Pr->SiS_P3ca+0x02));
		  पूर्ण
	       पूर्ण
	       अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
		  अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
		    अगर(SiS_Pr->SiS_LCDInfo & LCDSync) अणु
		       tempah = SiS_Pr->SiS_LCDInfo;
		       tempbl = (tempah >> 6) & 0x03;
		    पूर्ण
		  पूर्ण
	       पूर्ण
	    पूर्ण
	    tempah &= 0xC0;
	    tempah |= 0x20;
	    अगर(!(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit)) tempah |= 0x10;
	    अगर(SiS_Pr->SiS_VBType & VB_NoLCD) अणु
	       /* Imitate BIOS bug */
	       अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)  tempah |= 0xc0;
	    पूर्ण
	    अगर((SiS_Pr->SiS_VBType & VB_SIS30xC) && (SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC)) अणु
	       tempah >>= 3;
	       tempah &= 0x18;
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xe7,tempah);
	    पूर्ण अन्यथा अणु
	       SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0F,tempah);
	       अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
		  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
		     SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1a,0xf0,tempbl);
		  पूर्ण
	       पूर्ण
	    पूर्ण

         पूर्ण
#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */
      पूर्ण
   पूर्ण
पूर्ण

/* Set CRT2 FIFO on 300/540/630/730 */
#अगर_घोषित CONFIG_FB_SIS_300
अटल व्योम
SiS_SetCRT2FIFO_300(काष्ठा SiS_Private *SiS_Pr,अचिन्हित लघु ModeNo)
अणु
  अचिन्हित अक्षर  *ROMAddr  = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु temp, index, modeidindex, refreshratetableindex;
  अचिन्हित लघु VCLK = 0, MCLK, colorth = 0, data2 = 0;
  अचिन्हित लघु tempbx, tempcl, CRT1ModeNo, CRT2ModeNo, SelectRate_backup;
  अचिन्हित पूर्णांक   data, pci50, pciA0;
  अटल स्थिर अचिन्हित अक्षर colortharray[] = अणु
  	1, 1, 2, 2, 3, 4
  पूर्ण;

  SelectRate_backup = SiS_Pr->SiS_SelectCRT2Rate;

  अगर(!SiS_Pr->CRT1UsesCustomMode) अणु

     CRT1ModeNo = SiS_Pr->SiS_CRT1Mode;                                 /* get CRT1 ModeNo */
     SiS_SearchModeID(SiS_Pr, &CRT1ModeNo, &modeidindex);
     SiS_Pr->SiS_SetFlag &= (~ProgrammingCRT2);
     SiS_Pr->SiS_SelectCRT2Rate = 0;
     refreshratetableindex = SiS_GetRatePtr(SiS_Pr, CRT1ModeNo, modeidindex);

     अगर(CRT1ModeNo >= 0x13) अणु
        /* Get VCLK */
	index = SiS_GetRefCRTVCLK(SiS_Pr, refreshratetableindex, SiS_Pr->SiS_UseWide);
	VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;

	/* Get colordepth */
	colorth = SiS_GetColorDepth(SiS_Pr,CRT1ModeNo,modeidindex) >> 1;
	अगर(!colorth) colorth++;
     पूर्ण

  पूर्ण अन्यथा अणु

     CRT1ModeNo = 0xfe;

     /* Get VCLK */
     VCLK = SiS_Pr->CSRClock_CRT1;

     /* Get color depth */
     colorth = colortharray[((SiS_Pr->CModeFlag_CRT1 & ModeTypeMask) - 2)];

  पूर्ण

  अगर(CRT1ModeNo >= 0x13) अणु
     /* Get MCLK */
     अगर(SiS_Pr->ChipType == SIS_300) अणु
        index = SiS_GetReg(SiS_Pr->SiS_P3c4,0x3A);
     पूर्ण अन्यथा अणु
        index = SiS_GetReg(SiS_Pr->SiS_P3c4,0x1A);
     पूर्ण
     index &= 0x07;
     MCLK = SiS_Pr->SiS_MCLKData_0[index].CLOCK;

     temp = ((SiS_GetReg(SiS_Pr->SiS_P3c4,0x14) >> 6) & 0x03) << 1;
     अगर(!temp) temp++;
     temp <<= 2;

     data2 = temp - ((colorth * VCLK) / MCLK);

     temp = (28 * 16) % data2;
     data2 = (28 * 16) / data2;
     अगर(temp) data2++;

     अगर(SiS_Pr->ChipType == SIS_300) अणु

	SiS_GetFIFOThresholdIndex300(SiS_Pr, &tempbx, &tempcl);
	data = SiS_GetFIFOThresholdB300(tempbx, tempcl);

     पूर्ण अन्यथा अणु

	pci50 = sisfb_पढ़ो_nbridge_pci_dword(SiS_Pr, 0x50);
	pciA0 = sisfb_पढ़ो_nbridge_pci_dword(SiS_Pr, 0xa0);

        अगर(SiS_Pr->ChipType == SIS_730) अणु

	   index = (अचिन्हित लघु)(((pciA0 >> 28) & 0x0f) * 3);
	   index += (अचिन्हित लघु)(((pci50 >> 9)) & 0x03);

	   /* BIOS BUG (2.04.5d, 2.04.6a use ah here, which is unset!) */
	   index = 0;  /* -- करो it like the BIOS anyway... */

	पूर्ण अन्यथा अणु

	   pci50 >>= 24;
	   pciA0 >>= 24;

	   index = (pci50 >> 1) & 0x07;

	   अगर(pci50 & 0x01)    index += 6;
	   अगर(!(pciA0 & 0x01)) index += 24;

	   अगर(SiS_GetReg(SiS_Pr->SiS_P3c4,0x14) & 0x80) index += 12;

	पूर्ण

	data = SiS_GetLatencyFactor630(SiS_Pr, index) + 15;
	अगर(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x14) & 0x80)) data += 5;

     पूर्ण

     data += data2;						/* CRT1 Request Period */

     SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
     SiS_Pr->SiS_SelectCRT2Rate = SelectRate_backup;

     अगर(!SiS_Pr->UseCustomMode) अणु

	CRT2ModeNo = ModeNo;
	SiS_SearchModeID(SiS_Pr, &CRT2ModeNo, &modeidindex);

	refreshratetableindex = SiS_GetRatePtr(SiS_Pr, CRT2ModeNo, modeidindex);

	/* Get VCLK  */
	index = SiS_GetVCLK2Ptr(SiS_Pr, CRT2ModeNo, modeidindex, refreshratetableindex);
	VCLK = SiS_Pr->SiS_VCLKData[index].CLOCK;

	अगर((SiS_Pr->SiS_CustomT == CUT_BARCO1366) || (SiS_Pr->SiS_CustomT == CUT_BARCO1024)) अणु
	   अगर(SiS_Pr->SiS_UseROM) अणु
	      अगर(ROMAddr[0x220] & 0x01) अणु
		 VCLK = ROMAddr[0x229] | (ROMAddr[0x22a] << 8);
	      पूर्ण
           पूर्ण
        पूर्ण

     पूर्ण अन्यथा अणु

	/* Get VCLK */
	CRT2ModeNo = 0xfe;
	VCLK = SiS_Pr->CSRClock;

     पूर्ण

     /* Get colordepth */
     colorth = SiS_GetColorDepth(SiS_Pr,CRT2ModeNo,modeidindex) >> 1;
     अगर(!colorth) colorth++;

     data = data * VCLK * colorth;
     temp = data % (MCLK << 4);
     data = data / (MCLK << 4);
     अगर(temp) data++;

     अगर(data < 6) data = 6;
     अन्यथा अगर(data > 0x14) data = 0x14;

     अगर(SiS_Pr->ChipType == SIS_300) अणु
        temp = 0x16;
	अगर((data <= 0x0f) || (SiS_Pr->SiS_LCDResInfo == Panel_1280x1024))
	   temp = 0x13;
     पूर्ण अन्यथा अणु
        temp = 0x16;
	अगर(( (SiS_Pr->ChipType == SIS_630) ||
	     (SiS_Pr->ChipType == SIS_730) )  &&
	   (SiS_Pr->ChipRevision >= 0x30))
	   temp = 0x1b;
     पूर्ण
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x01,0xe0,temp);

     अगर((SiS_Pr->ChipType == SIS_630) &&
	(SiS_Pr->ChipRevision >= 0x30)) अणु
	अगर(data > 0x13) data = 0x13;
     पूर्ण
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x02,0xe0,data);

  पूर्ण अन्यथा अणु  /* If mode <= 0x13, we just restore everything */

     SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
     SiS_Pr->SiS_SelectCRT2Rate = SelectRate_backup;

  पूर्ण
पूर्ण
#पूर्ण_अगर

/* Set CRT2 FIFO on 315/330 series */
#अगर_घोषित CONFIG_FB_SIS_315
अटल व्योम
SiS_SetCRT2FIFO_310(काष्ठा SiS_Private *SiS_Pr)
अणु
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x01,0x3B);
  अगर( (SiS_Pr->ChipType == SIS_760)      &&
      (SiS_Pr->SiS_SysFlags & SF_760LFB)  &&
      (SiS_Pr->SiS_ModeType == Mode32Bpp) &&
      (SiS_Pr->SiS_VGAHDE >= 1280)	  &&
      (SiS_Pr->SiS_VGAVDE >= 1024) ) अणु
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2f,0x03);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x01,0x3b);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x4d,0xc0);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2f,0x01);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x4d,0xc0);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x02,0x6e);
  पूर्ण अन्यथा अणु
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x02,~0x3f,0x04);
  पूर्ण

पूर्ण
#पूर्ण_अगर

अटल अचिन्हित लघु
SiS_GetVGAHT2(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित पूर्णांक tempax,tempbx;

  tempbx = (SiS_Pr->SiS_VGAVT - SiS_Pr->SiS_VGAVDE) * SiS_Pr->SiS_RVBHCMAX;
  tempax = (SiS_Pr->SiS_VT - SiS_Pr->SiS_VDE) * SiS_Pr->SiS_RVBHCFACT;
  tempax = (tempax * SiS_Pr->SiS_HT) / tempbx;
  वापस (अचिन्हित लघु)tempax;
पूर्ण

/* Set Part 1 / SiS bridge slave mode */
अटल व्योम
SiS_SetGroup1_301(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex,
                  अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु temp, modeflag, i, j, xres=0, VGAVDE;
  अटल स्थिर अचिन्हित लघु CRTranslation[] = अणु
       /* CR0   CR1   CR2   CR3   CR4   CR5   CR6   CR7   */
	  0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
       /* CR8   CR9   SR0A  SR0B  SR0C  SR0D  SR0E  CR0F  */
	  0x00, 0x0b, 0x17, 0x18, 0x19, 0x00, 0x1a, 0x00,
       /* CR10  CR11  CR12  CR13  CR14  CR15  CR16  CR17  */
	  0x0c, 0x0d, 0x0e, 0x00, 0x0f, 0x10, 0x11, 0x00
  पूर्ण;

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
  पूर्ण अन्यथा अगर(SiS_Pr->UseCustomMode) अणु
     modeflag = SiS_Pr->CModeFlag;
     xres = SiS_Pr->CHDisplay;
  पूर्ण अन्यथा अणु
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     xres = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].XRes;
  पूर्ण

  /* The following is only करोne अगर bridge is in slave mode: */

  अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     अगर(xres >= 1600) अणु  /* BIOS: == 1600 */
        SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x31,0x04);
     पूर्ण
  पूर्ण

  SiS_Pr->CHTotal = 8224;  /* Max HT, 0x2020, results in 0x3ff in रेजिस्टरs */

  SiS_Pr->CHDisplay = SiS_Pr->SiS_VGAHDE;
  अगर(modeflag & HalfDCLK) SiS_Pr->CHDisplay >>= 1;

  SiS_Pr->CHBlankStart = SiS_Pr->CHDisplay;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
     SiS_Pr->CHBlankStart += 16;
  पूर्ण

  SiS_Pr->CHBlankEnd = 32;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
     अगर(xres == 1600) SiS_Pr->CHBlankEnd += 80;
  पूर्ण

  temp = SiS_Pr->SiS_VGAHT - 96;
  अगर(!(modeflag & HalfDCLK)) temp -= 32;
  अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) अणु
     temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x04);
     temp |= ((SiS_GetReg(SiS_Pr->SiS_P3c4,0x0b) & 0xc0) << 2);
     temp -= 3;
     temp <<= 3;
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_RVBHRS2) temp = SiS_Pr->SiS_RVBHRS2;
  पूर्ण
  SiS_Pr->CHSyncStart = temp;

  SiS_Pr->CHSyncEnd = 0xffe8; 	/* results in 0x2000 in रेजिस्टरs */

  SiS_Pr->CVTotal = 2049;  	/* Max VT, 0x0801, results in 0x7ff in रेजिस्टरs */

  VGAVDE = SiS_Pr->SiS_VGAVDE;
  अगर     (VGAVDE ==  357) VGAVDE =  350;
  अन्यथा अगर(VGAVDE ==  360) VGAVDE =  350;
  अन्यथा अगर(VGAVDE ==  375) VGAVDE =  350;
  अन्यथा अगर(VGAVDE ==  405) VGAVDE =  400;
  अन्यथा अगर(VGAVDE ==  420) VGAVDE =  400;
  अन्यथा अगर(VGAVDE ==  525) VGAVDE =  480;
  अन्यथा अगर(VGAVDE == 1056) VGAVDE = 1024;
  SiS_Pr->CVDisplay = VGAVDE;

  SiS_Pr->CVBlankStart = SiS_Pr->CVDisplay;

  SiS_Pr->CVBlankEnd = 1;
  अगर(ModeNo == 0x3c) SiS_Pr->CVBlankEnd = 226;

  temp = (SiS_Pr->SiS_VGAVT - VGAVDE) >> 1;
  SiS_Pr->CVSyncStart = VGAVDE + temp;

  temp >>= 3;
  SiS_Pr->CVSyncEnd = SiS_Pr->CVSyncStart + temp;

  SiS_CalcCRRegisters(SiS_Pr, 0);
  SiS_Pr->CCRT1CRTC[16] &= ~0xE0;

  क्रम(i = 0; i <= 7; i++) अणु
     SiS_SetReg(SiS_Pr->SiS_Part1Port,CRTranslation[i],SiS_Pr->CCRT1CRTC[i]);
  पूर्ण
  क्रम(i = 0x10, j = 8; i <= 0x12; i++, j++) अणु
     SiS_SetReg(SiS_Pr->SiS_Part1Port,CRTranslation[i],SiS_Pr->CCRT1CRTC[j]);
  पूर्ण
  क्रम(i = 0x15, j = 11; i <= 0x16; i++, j++) अणु
     SiS_SetReg(SiS_Pr->SiS_Part1Port,CRTranslation[i],SiS_Pr->CCRT1CRTC[j]);
  पूर्ण
  क्रम(i = 0x0a, j = 13; i <= 0x0c; i++, j++) अणु
     SiS_SetReg(SiS_Pr->SiS_Part1Port,CRTranslation[i],SiS_Pr->CCRT1CRTC[j]);
  पूर्ण

  temp = SiS_Pr->CCRT1CRTC[16] & 0xE0;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,CRTranslation[0x0E],0x1F,temp);

  temp = (SiS_Pr->CCRT1CRTC[16] & 0x01) << 5;
  अगर(modeflag & DoubleScanMode) temp |= 0x80;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,CRTranslation[0x09],0x5F,temp);

  temp = 0;
  temp |= (SiS_GetReg(SiS_Pr->SiS_P3c4,0x01) & 0x01);
  अगर(modeflag & HalfDCLK) temp |= 0x08;
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x16,temp);              	/* SR01: HalfDCLK[3], 8/9 भाग करोtघड़ी[0] */

  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0F,0x00);              	/* CR14: (text mode: underline location) */
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x12,0x00);              	/* CR17: n/a */

  temp = 0;
  अगर(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) अणु
     temp = (SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x01) << 7;
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1A,temp);                	/* SR0E, dither[7] */

  temp = SiS_GetRegByte((SiS_Pr->SiS_P3ca+0x02));
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,temp);			/* ? */
पूर्ण

/* Setup panel link
 * This is used क्रम LVDS, LCDA and Chrontel TV output
 * 300/LVDS+TV, 300/301B-DH, 315/LVDS+TV, 315/LCDA
 */
अटल व्योम
SiS_SetGroup1_LVDS(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु modeflag, resinfo = 0;
  अचिन्हित लघु push2, tempax, tempbx, tempcx, temp;
  अचिन्हित पूर्णांक   tempeax = 0, tempebx, tempecx, tempvcfact = 0;
  bool islvds = false, issis  = false, chkdclkfirst = false;
#अगर_घोषित CONFIG_FB_SIS_300
  अचिन्हित लघु crt2crtc = 0;
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
  अचिन्हित लघु pushcx;
#पूर्ण_अगर

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
#अगर_घोषित CONFIG_FB_SIS_300
     crt2crtc = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
#पूर्ण_अगर
  पूर्ण अन्यथा अगर(SiS_Pr->UseCustomMode) अणु
     modeflag = SiS_Pr->CModeFlag;
  पूर्ण अन्यथा अणु
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
#अगर_घोषित CONFIG_FB_SIS_300
     crt2crtc = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
#पूर्ण_अगर
  पूर्ण

  /* is lvds अगर really LVDS, or 301B-DH with बाह्यal LVDS transmitter */
  अगर((SiS_Pr->SiS_IF_DEF_LVDS == 1) || (SiS_Pr->SiS_VBType & VB_NoLCD)) अणु
     islvds = true;
  पूर्ण

  /* is really sis अगर sis bridge, but not 301B-DH */
  अगर((SiS_Pr->SiS_VBType & VB_SISVB) && (!(SiS_Pr->SiS_VBType & VB_NoLCD))) अणु
     issis = true;
  पूर्ण

  अगर((SiS_Pr->ChipType >= SIS_315H) && (islvds) && (!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA))) अणु
     अगर((!SiS_Pr->SiS_IF_DEF_FSTN) && (!SiS_Pr->SiS_IF_DEF_DSTN)) अणु
        chkdclkfirst = true;
     पूर्ण
  पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315
  अगर((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
     अगर(IS_SIS330) अणु
        SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x10);
     पूर्ण अन्यथा अगर(IS_SIS740) अणु
        अगर(islvds) अणु
           SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xfb,0x04);
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x03);
        पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
           SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x10);
        पूर्ण
     पूर्ण अन्यथा अणु
        अगर(islvds) अणु
           SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,0xfb,0x04);
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x00);
        पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
           SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2D,0x0f);
	   अगर(SiS_Pr->SiS_VBType & VB_SIS30xC) अणु
	      अगर((SiS_Pr->SiS_LCDResInfo == Panel_1024x768) ||
	         (SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)) अणु
	         SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x2D,0x20);
	      पूर्ण
	   पूर्ण
        पूर्ण
     पूर्ण
  पूर्ण
#पूर्ण_अगर

  /* Horizontal */

  tempax = SiS_Pr->SiS_LCDHDES;
  अगर(islvds) अणु
     अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
	अगर(!SiS_Pr->SiS_IF_DEF_FSTN && !SiS_Pr->SiS_IF_DEF_DSTN) अणु
	   अगर((SiS_Pr->SiS_LCDResInfo == Panel_640x480) &&
	      (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))) अणु
	      tempax -= 8;
	   पूर्ण
	पूर्ण
     पूर्ण
  पूर्ण

  temp = (tempax & 0x0007);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1A,temp);			/* BPLHDESKEW[2:0]   */
  temp = (tempax >> 3) & 0x00FF;
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x16,temp);			/* BPLHDESKEW[10:3]  */

  tempbx = SiS_Pr->SiS_HDE;
  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
        tempbx = SiS_Pr->PanelXRes;
     पूर्ण
     अगर((SiS_Pr->SiS_LCDResInfo == Panel_320x240_1) ||
        (SiS_Pr->SiS_LCDResInfo == Panel_320x240_2) ||
        (SiS_Pr->SiS_LCDResInfo == Panel_320x240_3)) अणु
        tempbx >>= 1;
     पूर्ण
  पूर्ण

  tempax += tempbx;
  अगर(tempax >= SiS_Pr->SiS_HT) tempax -= SiS_Pr->SiS_HT;

  temp = tempax;
  अगर(temp & 0x07) temp += 8;
  temp >>= 3;
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x17,temp);			/* BPLHDEE  */

  tempcx = (SiS_Pr->SiS_HT - tempbx) >> 2;

  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
        अगर(SiS_Pr->PanelHRS != 999) tempcx = SiS_Pr->PanelHRS;
     पूर्ण
  पूर्ण

  tempcx += tempax;
  अगर(tempcx >= SiS_Pr->SiS_HT) tempcx -= SiS_Pr->SiS_HT;

  temp = (tempcx >> 3) & 0x00FF;
  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     अगर(SiS_Pr->SiS_IF_DEF_TRUMPION) अणु
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	   चयन(ModeNo) अणु
	   हाल 0x04:
	   हाल 0x05:
	   हाल 0x0d: temp = 0x56; अवरोध;
	   हाल 0x10: temp = 0x60; अवरोध;
	   हाल 0x13: temp = 0x5f; अवरोध;
	   हाल 0x40:
	   हाल 0x41:
	   हाल 0x4f:
	   हाल 0x43:
	   हाल 0x44:
	   हाल 0x62:
	   हाल 0x56:
	   हाल 0x53:
	   हाल 0x5d:
	   हाल 0x5e: temp = 0x54; अवरोध;
	   पूर्ण
	पूर्ण
     पूर्ण
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x14,temp);			/* BPLHRS */

  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     temp += 2;
     अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
	temp += 8;
	अगर(SiS_Pr->PanelHRE != 999) अणु
	   temp = tempcx + SiS_Pr->PanelHRE;
	   अगर(temp >= SiS_Pr->SiS_HT) temp -= SiS_Pr->SiS_HT;
	   temp >>= 3;
	पूर्ण
     पूर्ण
  पूर्ण अन्यथा अणु
     temp += 10;
  पूर्ण

  temp &= 0x1F;
  temp |= ((tempcx & 0x07) << 5);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x15,temp);			/* BPLHRE */

  /* Vertical */

  tempax = SiS_Pr->SiS_VGAVDE;
  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
	tempax = SiS_Pr->PanelYRes;
     पूर्ण
  पूर्ण

  tempbx = SiS_Pr->SiS_LCDVDES + tempax;
  अगर(tempbx >= SiS_Pr->SiS_VT) tempbx -= SiS_Pr->SiS_VT;

  push2 = tempbx;

  tempcx = SiS_Pr->SiS_VGAVT - SiS_Pr->SiS_VGAVDE;
  अगर(SiS_Pr->ChipType < SIS_315H) अणु
     अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
	अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
	   tempcx = SiS_Pr->SiS_VGAVT - SiS_Pr->PanelYRes;
	पूर्ण
     पूर्ण
  पूर्ण
  अगर(islvds) tempcx >>= 1;
  अन्यथा       tempcx >>= 2;

  अगर( (SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) &&
      (!(SiS_Pr->SiS_LCDInfo & LCDPass11)) 		    &&
      (SiS_Pr->PanelVRS != 999) ) अणु
     tempcx = SiS_Pr->PanelVRS;
     tempbx += tempcx;
     अगर(issis) tempbx++;
  पूर्ण अन्यथा अणु
     tempbx += tempcx;
     अगर(SiS_Pr->ChipType < SIS_315H) tempbx++;
     अन्यथा अगर(issis)                   tempbx++;
  पूर्ण

  अगर(tempbx >= SiS_Pr->SiS_VT) tempbx -= SiS_Pr->SiS_VT;

  temp = tempbx & 0x00FF;
  अगर(SiS_Pr->SiS_IF_DEF_TRUMPION) अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	अगर(ModeNo == 0x10) temp = 0xa9;
     पूर्ण
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,temp);			/* BPLVRS */

  tempcx >>= 3;
  tempcx++;

  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
        अगर(SiS_Pr->PanelVRE != 999) tempcx = SiS_Pr->PanelVRE;
     पूर्ण
  पूर्ण

  tempcx += tempbx;
  temp = tempcx & 0x000F;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0xF0,temp);	/* BPLVRE  */

  temp = ((tempbx >> 8) & 0x07) << 3;
  अगर(SiS_Pr->SiS_IF_DEF_FSTN || SiS_Pr->SiS_IF_DEF_DSTN) अणु
     अगर(SiS_Pr->SiS_HDE != 640) अणु
        अगर(SiS_Pr->SiS_VGAVDE != SiS_Pr->SiS_VDE)  temp |= 0x40;
     पूर्ण
  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VGAVDE != SiS_Pr->SiS_VDE) temp |= 0x40;
  अगर(SiS_Pr->SiS_SetFlag & EnableLVDSDDA)          temp |= 0x40;
  tempbx = 0x87;
  अगर((SiS_Pr->ChipType >= SIS_315H) ||
     (SiS_Pr->ChipRevision >= 0x30)) अणु
     tempbx = 0x07;
     अगर((SiS_Pr->SiS_IF_DEF_CH70xx == 1) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) अणु
	अगर(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x03)    temp |= 0x80;
     पूर्ण
     /* Chrontel 701x operates in 24bit mode (8-8-8, 2x12bit multiplexed) via VGA2 */
     अगर(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) अणु
	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	   अगर(SiS_GetReg(SiS_Pr->SiS_P3c4,0x06) & 0x10)      temp |= 0x80;
	पूर्ण अन्यथा अणु
	   अगर(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x01) temp |= 0x80;
	पूर्ण
     पूर्ण
  पूर्ण
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x1A,tempbx,temp);

  tempbx = push2;						/* BPLVDEE */

  tempcx = SiS_Pr->SiS_LCDVDES;					/* BPLVDES */

  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     चयन(SiS_Pr->SiS_LCDResInfo) अणु
     हाल Panel_640x480:
	tempbx = SiS_Pr->SiS_VGAVDE - 1;
	tempcx = SiS_Pr->SiS_VGAVDE;
	अवरोध;
     हाल Panel_800x600:
	अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
	   अगर(resinfo == SIS_RI_800x600) tempcx++;
	पूर्ण
	अवरोध;
     हाल Panel_1024x600:
	अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
	   अगर(resinfo == SIS_RI_1024x600) tempcx++;
	   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	      अगर(resinfo == SIS_RI_800x600) tempcx++;
	   पूर्ण
	पूर्ण
	अवरोध;
     हाल Panel_1024x768:
	अगर(SiS_Pr->ChipType < SIS_315H) अणु
	   अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
	      अगर(resinfo == SIS_RI_1024x768) tempcx++;
	   पूर्ण
	पूर्ण
	अवरोध;
     पूर्ण
  पूर्ण

  temp = ((tempbx >> 8) & 0x07) << 3;
  temp |= ((tempcx >> 8) & 0x07);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1D,temp);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1C,tempbx);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1B,tempcx);

  /* Vertical scaling */

  अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300      /* 300 series */
     tempeax = SiS_Pr->SiS_VGAVDE << 6;
     temp = (tempeax % (अचिन्हित पूर्णांक)SiS_Pr->SiS_VDE);
     tempeax = tempeax / (अचिन्हित पूर्णांक)SiS_Pr->SiS_VDE;
     अगर(temp) tempeax++;

     अगर(SiS_Pr->SiS_SetFlag & EnableLVDSDDA) tempeax = 0x3F;

     temp = (अचिन्हित लघु)(tempeax & 0x00FF);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1E,temp);      	/* BPLVCFACT */
     tempvcfact = temp;
#पूर्ण_अगर /* CONFIG_FB_SIS_300 */

  पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315  /* 315 series */
     tempeax = SiS_Pr->SiS_VGAVDE << 18;
     tempebx = SiS_Pr->SiS_VDE;
     temp = (tempeax % tempebx);
     tempeax = tempeax / tempebx;
     अगर(temp) tempeax++;
     tempvcfact = tempeax;

     temp = (अचिन्हित लघु)(tempeax & 0x00FF);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x37,temp);
     temp = (अचिन्हित लघु)((tempeax & 0x00FF00) >> 8);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x36,temp);
     temp = (अचिन्हित लघु)((tempeax & 0x00030000) >> 16);
     अगर(SiS_Pr->SiS_VDE == SiS_Pr->SiS_VGAVDE) temp |= 0x04;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x35,temp);

     अगर(SiS_Pr->SiS_VBType & VB_SISPART4SCALER) अणु
        temp = (अचिन्हित लघु)(tempeax & 0x00FF);
        SiS_SetReg(SiS_Pr->SiS_Part4Port,0x3c,temp);
        temp = (अचिन्हित लघु)((tempeax & 0x00FF00) >> 8);
        SiS_SetReg(SiS_Pr->SiS_Part4Port,0x3b,temp);
        temp = (अचिन्हित लघु)(((tempeax & 0x00030000) >> 16) << 6);
        SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x3a,0x3f,temp);
        temp = 0;
        अगर(SiS_Pr->SiS_VDE != SiS_Pr->SiS_VGAVDE) temp |= 0x08;
        SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x30,0xf3,temp);
     पूर्ण
#पूर्ण_अगर

  पूर्ण

  /* Horizontal scaling */

  tempeax = SiS_Pr->SiS_VGAHDE;		/* 1f = ( (VGAHDE * 65536) / ( (VGAHDE * 65536) / HDE ) ) - 1*/
  अगर(chkdclkfirst) अणु
     अगर(modeflag & HalfDCLK) tempeax >>= 1;
  पूर्ण
  tempebx = tempeax << 16;
  अगर(SiS_Pr->SiS_HDE == tempeax) अणु
     tempecx = 0xFFFF;
  पूर्ण अन्यथा अणु
     tempecx = tempebx / SiS_Pr->SiS_HDE;
     अगर(SiS_Pr->ChipType >= SIS_315H) अणु
        अगर(tempebx % SiS_Pr->SiS_HDE) tempecx++;
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     tempeax = (tempebx / tempecx) - 1;
  पूर्ण अन्यथा अणु
     tempeax = ((SiS_Pr->SiS_VGAHT << 16) / tempecx) - 1;
  पूर्ण
  tempecx = (tempecx << 16) | (tempeax & 0xFFFF);
  temp = (अचिन्हित लघु)(tempecx & 0x00FF);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1F,temp);

  अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     tempeax = (SiS_Pr->SiS_VGAVDE << 18) / tempvcfact;
     tempbx = (अचिन्हित लघु)(tempeax & 0xFFFF);
  पूर्ण अन्यथा अणु
     tempeax = SiS_Pr->SiS_VGAVDE << 6;
     tempbx = tempvcfact & 0x3f;
     अगर(tempbx == 0) tempbx = 64;
     tempeax /= tempbx;
     tempbx = (अचिन्हित लघु)(tempeax & 0xFFFF);
  पूर्ण
  अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) tempbx--;
  अगर(SiS_Pr->SiS_SetFlag & EnableLVDSDDA) अणु
     अगर((!SiS_Pr->SiS_IF_DEF_FSTN) && (!SiS_Pr->SiS_IF_DEF_DSTN)) tempbx = 1;
     अन्यथा अगर(SiS_Pr->SiS_LCDResInfo != Panel_640x480)             tempbx = 1;
  पूर्ण

  temp = ((tempbx >> 8) & 0x07) << 3;
  temp = temp | ((tempecx >> 8) & 0x07);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x20,temp);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x21,tempbx);

  tempecx >>= 16;						/* BPLHCFACT  */
  अगर(!chkdclkfirst) अणु
     अगर(modeflag & HalfDCLK) tempecx >>= 1;
  पूर्ण
  temp = (अचिन्हित लघु)((tempecx & 0xFF00) >> 8);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x22,temp);
  temp = (अचिन्हित लघु)(tempecx & 0x00FF);
  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x23,temp);

#अगर_घोषित CONFIG_FB_SIS_315
  अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
        अगर((islvds) || (SiS_Pr->SiS_VBInfo & VB_SISLVDS)) अणु
           SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1e,0x20);
	पूर्ण
     पूर्ण अन्यथा अणु
        अगर(islvds) अणु
           अगर(SiS_Pr->ChipType == SIS_740) अणु
              SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1e,0x03);
           पूर्ण अन्यथा अणु
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1e,0x23);
           पूर्ण
        पूर्ण
     पूर्ण
  पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_300
  अगर(SiS_Pr->SiS_IF_DEF_TRUMPION) अणु
     अचिन्हित अक्षर *ROMAddr = SiS_Pr->VirtualRomBase;
     अचिन्हित अक्षर *trumpdata;
     पूर्णांक   i, j = crt2crtc;
     अचिन्हित अक्षर TrumpMode13[4]   = अणु 0x01, 0x10, 0x2c, 0x00 पूर्ण;
     अचिन्हित अक्षर TrumpMode10_1[4] = अणु 0x01, 0x10, 0x27, 0x00 पूर्ण;
     अचिन्हित अक्षर TrumpMode10_2[4] = अणु 0x01, 0x16, 0x10, 0x00 पूर्ण;

     अगर(SiS_Pr->SiS_UseROM) अणु
	trumpdata = &ROMAddr[0x8001 + (j * 80)];
     पूर्ण अन्यथा अणु
	अगर(SiS_Pr->SiS_LCDTypeInfo == 0x0e) j += 7;
	trumpdata = &SiS300_TrumpionData[j][0];
     पूर्ण

     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x02,0xbf);
     क्रम(i=0; i<5; i++) अणु
	SiS_SetTrumpionBlock(SiS_Pr, trumpdata);
     पूर्ण
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	अगर(ModeNo == 0x13) अणु
	   क्रम(i=0; i<4; i++) अणु
	      SiS_SetTrumpionBlock(SiS_Pr, &TrumpMode13[0]);
	   पूर्ण
	पूर्ण अन्यथा अगर(ModeNo == 0x10) अणु
	   क्रम(i=0; i<4; i++) अणु
	      SiS_SetTrumpionBlock(SiS_Pr, &TrumpMode10_1[0]);
	      SiS_SetTrumpionBlock(SiS_Pr, &TrumpMode10_2[0]);
	   पूर्ण
	पूर्ण
     पूर्ण
     SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40);
  पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
  अगर(SiS_Pr->SiS_IF_DEF_FSTN || SiS_Pr->SiS_IF_DEF_DSTN) अणु
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x25,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x26,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x27,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x28,0x87);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x29,0x5A);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2A,0x4B);
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x44,~0x07,0x03);
     tempax = SiS_Pr->SiS_HDE;					/* Blps = lcdhdee(lcdhdes+HDE) + 64 */
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempax += 64;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x38,tempax & 0xff);
     temp = (tempax >> 8) << 3;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x35,~0x078,temp);
     tempax += 32;						/* Blpe = lBlps+32 */
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x39,tempax & 0xff);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3A,0x00);		/* Bflml = 0 */
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x3C,~0x007);

     tempax = SiS_Pr->SiS_VDE;
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempax >>= 1;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3B,tempax & 0xff);
     temp = (tempax >> 8) << 3;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x3C,~0x038,temp);

     tempeax = SiS_Pr->SiS_HDE;
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempeax >>= 1;
     tempeax <<= 2;			 			/* BDxFIFOSTOP = (HDE*4)/128 */
     temp = tempeax & 0x7f;
     tempeax >>= 7;
     अगर(temp) tempeax++;
     temp = tempeax & 0x3f;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x45,temp);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3F,0x00);		/* BDxWadrst0 */
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3E,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3D,0x10);
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x3C,~0x040);

     tempax = SiS_Pr->SiS_HDE;
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempax >>= 4;						/* BDxWadroff = HDE*4/8/8 */
     pushcx = tempax;
     temp = tempax & 0x00FF;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x43,temp);
     temp = ((tempax & 0xFF00) >> 8) << 3;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port, 0x44, 0x07, temp);

     tempax = SiS_Pr->SiS_VDE;				 	/* BDxWadrst1 = BDxWadrst0 + BDxWadroff * VDE */
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_320x240_1 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_2 ||
        SiS_Pr->SiS_LCDResInfo == Panel_320x240_3) tempax >>= 1;
     tempeax = tempax * pushcx;
     temp = tempeax & 0xFF;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x42,temp);
     temp = (tempeax & 0xFF00) >> 8;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x41,temp);
     temp = ((tempeax & 0xFF0000) >> 16) | 0x10;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x40,temp);
     temp = ((tempeax & 0x01000000) >> 24) << 7;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port, 0x3C, 0x7F, temp);

     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2F,0x03);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x03,0x50);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x04,0x00);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2F,0x01);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x19,0x38);

     अगर(SiS_Pr->SiS_IF_DEF_FSTN) अणु
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2b,0x02);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2c,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2d,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x35,0x0c);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x36,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x37,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x38,0x80);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x39,0xA0);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3a,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3b,0xf0);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3c,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3d,0x10);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3e,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x3f,0x00);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x40,0x10);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x41,0x25);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x42,0x80);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x43,0x14);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x44,0x03);
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x45,0x0a);
     पूर्ण
  पूर्ण
#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */
पूर्ण

/* Set Part 1 */
अटल व्योम
SiS_SetGroup1(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
#अगर defined(CONFIG_FB_SIS_300) || defined(CONFIG_FB_SIS_315)
  अचिन्हित अक्षर   *ROMAddr = SiS_Pr->VirtualRomBase;
#पूर्ण_अगर
  अचिन्हित लघु  temp=0, tempax=0, tempbx=0, tempcx=0, bridgeadd=0;
  अचिन्हित लघु  pushbx=0, CRT1Index=0, modeflag, resinfo=0;
#अगर_घोषित CONFIG_FB_SIS_315
  अचिन्हित लघु  tempbl=0;
#पूर्ण_अगर

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
     SiS_SetGroup1_LVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     वापस;
  पूर्ण

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
  पूर्ण अन्यथा अगर(SiS_Pr->UseCustomMode) अणु
     modeflag = SiS_Pr->CModeFlag;
  पूर्ण अन्यथा अणु
     CRT1Index = SiS_GetRefCRT1CRTC(SiS_Pr, RefreshRateTableIndex, SiS_Pr->SiS_UseWideCRT2);
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
  पूर्ण

  SiS_SetCRT2Offset(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);

  अगर( ! ((SiS_Pr->ChipType >= SIS_315H) &&
         (SiS_Pr->SiS_IF_DEF_LVDS == 1) &&
         (SiS_Pr->SiS_VBInfo & SetInSlaveMode)) ) अणु

     अगर(SiS_Pr->ChipType < SIS_315H ) अणु
#अगर_घोषित CONFIG_FB_SIS_300
	SiS_SetCRT2FIFO_300(SiS_Pr, ModeNo);
#पूर्ण_अगर
     पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_FB_SIS_315
	SiS_SetCRT2FIFO_310(SiS_Pr);
#पूर्ण_अगर
     पूर्ण

     /* 1. Horizontal setup */

     अगर(SiS_Pr->ChipType < SIS_315H ) अणु

#अगर_घोषित CONFIG_FB_SIS_300   /* ------------- 300 series --------------*/

	temp = (SiS_Pr->SiS_VGAHT - 1) & 0x0FF;   		  /* BTVGA2HT 0x08,0x09 */
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x08,temp);              /* CRT2 Horizontal Total */

	temp = (((SiS_Pr->SiS_VGAHT - 1) & 0xFF00) >> 8) << 4;
	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x09,0x0f,temp);    /* CRT2 Horizontal Total Overflow [7:4] */

	temp = (SiS_Pr->SiS_VGAHDE + 12) & 0x0FF;                 /* BTVGA2HDEE 0x0A,0x0C */
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0A,temp);              /* CRT2 Horizontal Display Enable End */

	pushbx = SiS_Pr->SiS_VGAHDE + 12;                         /* bx  BTVGA2HRS 0x0B,0x0C */
	tempcx = (SiS_Pr->SiS_VGAHT - SiS_Pr->SiS_VGAHDE) >> 2;
	tempbx = pushbx + tempcx;
	tempcx <<= 1;
	tempcx += tempbx;

	bridgeadd = 12;

#पूर्ण_अगर /* CONFIG_FB_SIS_300 */

     पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315  /* ------------------- 315/330 series --------------- */

	tempcx = SiS_Pr->SiS_VGAHT;				  /* BTVGA2HT 0x08,0x09 */
	अगर(modeflag & HalfDCLK) अणु
	   अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	      tempcx >>= 1;
	   पूर्ण अन्यथा अणु
	      tempax = SiS_Pr->SiS_VGAHDE >> 1;
	      tempcx = SiS_Pr->SiS_HT - SiS_Pr->SiS_HDE + tempax;
	      अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
	         tempcx = SiS_Pr->SiS_HT - tempax;
	      पूर्ण
	   पूर्ण
	पूर्ण
	tempcx--;
	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x08,tempcx);            /* CRT2 Horizontal Total */
	temp = (tempcx >> 4) & 0xF0;
	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x09,0x0F,temp);    /* CRT2 Horizontal Total Overflow [7:4] */

	tempcx = SiS_Pr->SiS_VGAHT;				  /* BTVGA2HDEE 0x0A,0x0C */
	tempbx = SiS_Pr->SiS_VGAHDE;
	tempcx -= tempbx;
	tempcx >>= 2;
	अगर(modeflag & HalfDCLK) अणु
	   tempbx >>= 1;
	   tempcx >>= 1;
	पूर्ण
	tempbx += 16;

	SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0A,tempbx);            /* CRT2 Horizontal Display Enable End */

	pushbx = tempbx;
	tempcx >>= 1;
	tempbx += tempcx;
	tempcx += tempbx;

	bridgeadd = 16;

	अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	   अगर(SiS_Pr->ChipType >= SIS_661) अणु
	      अगर((SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) ||
		 (SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)) अणु
		 अगर(resinfo == SIS_RI_1280x1024) अणु
		    tempcx = (tempcx & 0xff00) | 0x30;
		 पूर्ण अन्यथा अगर(resinfo == SIS_RI_1600x1200) अणु
		    tempcx = (tempcx & 0xff00) | 0xff;
		 पूर्ण
	      पूर्ण
	   पूर्ण
        पूर्ण

#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */

     पूर्ण  /* 315/330 series */

     अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

	अगर(SiS_Pr->UseCustomMode) अणु
	   tempbx = SiS_Pr->CHSyncStart + bridgeadd;
	   tempcx = SiS_Pr->CHSyncEnd + bridgeadd;
	   tempax = SiS_Pr->SiS_VGAHT;
	   अगर(modeflag & HalfDCLK) tempax >>= 1;
	   tempax--;
	   अगर(tempcx > tempax) tempcx = tempax;
	पूर्ण

	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) अणु
	   अचिन्हित अक्षर cr4, cr14, cr5, cr15;
	   अगर(SiS_Pr->UseCustomMode) अणु
	      cr4  = SiS_Pr->CCRT1CRTC[4];
	      cr14 = SiS_Pr->CCRT1CRTC[14];
	      cr5  = SiS_Pr->CCRT1CRTC[5];
	      cr15 = SiS_Pr->CCRT1CRTC[15];
	   पूर्ण अन्यथा अणु
	      cr4  = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[4];
	      cr14 = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[14];
	      cr5  = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[5];
	      cr15 = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[15];
	   पूर्ण
	   tempbx = ((cr4 | ((cr14 & 0xC0) << 2)) - 3) << 3; 		    /* (VGAHRS-3)*8 */
	   tempcx = (((cr5 & 0x1f) | ((cr15 & 0x04) << (5-2))) - 3) << 3;   /* (VGAHRE-3)*8 */
	   tempcx &= 0x00FF;
	   tempcx |= (tempbx & 0xFF00);
	   tempbx += bridgeadd;
	   tempcx += bridgeadd;
	   tempax = SiS_Pr->SiS_VGAHT;
	   अगर(modeflag & HalfDCLK) tempax >>= 1;
	   tempax--;
	   अगर(tempcx > tempax) tempcx = tempax;
	पूर्ण

	अगर(SiS_Pr->SiS_TVMode & (TVSetNTSC1024 | TVSet525p1024)) अणु
	   tempbx = 1040;
	   tempcx = 1044;   /* HWCursor bug! */
	पूर्ण

     पूर्ण

     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0B,tempbx);            	  /* CRT2 Horizontal Retrace Start */

     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0D,tempcx);               /* CRT2 Horizontal Retrace End */

     temp = ((tempbx >> 8) & 0x0F) | ((pushbx >> 4) & 0xF0);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0C,temp);		  /* Overflow */

     /* 2. Vertical setup */

     tempcx = SiS_Pr->SiS_VGAVT - 1;
     temp = tempcx & 0x00FF;

     अगर(SiS_Pr->ChipType < SIS_661) अणु
        अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
	   अगर(SiS_Pr->ChipType < SIS_315H) अणु
	      अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	         अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)) अणु
	            temp--;
	         पूर्ण
	      पूर्ण
	   पूर्ण अन्यथा अणु
	      temp--;
	   पूर्ण
	पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_315H) अणु
	   temp--;
	पूर्ण
     पूर्ण
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0E,temp);                 /* CRT2 Vertical Total */

     tempbx = SiS_Pr->SiS_VGAVDE - 1;
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x0F,tempbx);               /* CRT2 Vertical Display Enable End */

     temp = ((tempbx >> 5) & 0x38) | ((tempcx >> 8) & 0x07);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x12,temp);                 /* Overflow */

     अगर((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->ChipType < SIS_661)) अणु
	tempbx++;
	tempax = tempbx;
	tempcx++;
	tempcx -= tempax;
	tempcx >>= 2;
	tempbx += tempcx;
	अगर(tempcx < 4) tempcx = 4;
	tempcx >>= 2;
	tempcx += tempbx;
	tempcx++;
     पूर्ण अन्यथा अणु
	tempbx = (SiS_Pr->SiS_VGAVT + SiS_Pr->SiS_VGAVDE) >> 1;                 /*  BTVGA2VRS     0x10,0x11   */
	tempcx = ((SiS_Pr->SiS_VGAVT - SiS_Pr->SiS_VGAVDE) >> 4) + tempbx + 1;  /*  BTVGA2VRE     0x11        */
     पूर्ण

     अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	अगर(SiS_Pr->UseCustomMode) अणु
	   tempbx = SiS_Pr->CVSyncStart;
	   tempcx = SiS_Pr->CVSyncEnd;
	पूर्ण
	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) अणु
	   अचिन्हित अक्षर cr8, cr7, cr13;
	   अगर(SiS_Pr->UseCustomMode) अणु
	      cr8    = SiS_Pr->CCRT1CRTC[8];
	      cr7    = SiS_Pr->CCRT1CRTC[7];
	      cr13   = SiS_Pr->CCRT1CRTC[13];
	      tempcx = SiS_Pr->CCRT1CRTC[9];
	   पूर्ण अन्यथा अणु
	      cr8    = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[8];
	      cr7    = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[7];
	      cr13   = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[13];
	      tempcx = SiS_Pr->SiS_CRT1Table[CRT1Index].CR[9];
	   पूर्ण
	   tempbx = cr8;
	   अगर(cr7  & 0x04) tempbx |= 0x0100;
	   अगर(cr7  & 0x80) tempbx |= 0x0200;
	   अगर(cr13 & 0x08) tempbx |= 0x0400;
	पूर्ण
     पूर्ण
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x10,tempbx);               /* CRT2 Vertical Retrace Start */

     temp = ((tempbx >> 4) & 0x70) | (tempcx & 0x0F);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x11,temp);                 /* CRT2 Vert. Retrace End; Overflow */

     /* 3. Panel delay compensation */

     अगर(SiS_Pr->ChipType < SIS_315H) अणु

#अगर_घोषित CONFIG_FB_SIS_300  /* ---------- 300 series -------------- */

	अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
	   temp = 0x20;
	   अगर(SiS_Pr->ChipType == SIS_300) अणु
	      temp = 0x10;
	      अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768)  temp = 0x2c;
	      अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) temp = 0x20;
	   पूर्ण
	   अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
	      अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) temp = 0x20;
	   पूर्ण
	   अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x960)     temp = 0x24;
	   अगर(SiS_Pr->SiS_LCDResInfo == Panel_Custom)       temp = 0x2c;
	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) 	    temp = 0x08;
	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	      अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) 	    temp = 0x2c;
	      अन्यथा 					    temp = 0x20;
	   पूर्ण
	   अगर(SiS_Pr->SiS_UseROM) अणु
	      अगर(ROMAddr[0x220] & 0x80) अणु
		 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoYPbPrHiVision)
		    temp = ROMAddr[0x221];
		 अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision)
		    temp = ROMAddr[0x222];
		 अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024)
		    temp = ROMAddr[0x223];
		 अन्यथा
		    temp = ROMAddr[0x224];
	      पूर्ण
	   पूर्ण
	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	      अगर(SiS_Pr->PDC != -1)  temp = SiS_Pr->PDC;
	   पूर्ण

	पूर्ण अन्यथा अणु
	   temp = 0x20;
	   अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) अणु
	      अगर(SiS_Pr->SiS_LCDResInfo == Panel_640x480) temp = 0x04;
	   पूर्ण
	   अगर(SiS_Pr->SiS_UseROM) अणु
	      अगर(ROMAddr[0x220] & 0x80) अणु
	         temp = ROMAddr[0x220];
	      पूर्ण
	   पूर्ण
	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	      अगर(SiS_Pr->PDC != -1) temp = SiS_Pr->PDC;
	   पूर्ण
	पूर्ण

	temp &= 0x3c;

	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,~0x3C,temp);   /* Panel Link Delay Compensation; (Software Command Reset; Power Saving) */

#पूर्ण_अगर  /* CONFIG_FB_SIS_300 */

     पूर्ण अन्यथा अणु

#अगर_घोषित CONFIG_FB_SIS_315   /* --------------- 315/330 series ---------------*/

	अगर(SiS_Pr->ChipType < SIS_661) अणु

	   अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु

	      अगर(SiS_Pr->ChipType == SIS_740) temp = 0x03;
	      अन्यथा 		              temp = 0x00;

	      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) temp = 0x0a;
	      tempbl = 0xF0;
	      अगर(SiS_Pr->ChipType == SIS_650) अणु
		 अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
		    अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) tempbl = 0x0F;
		 पूर्ण
	      पूर्ण

	      अगर(SiS_Pr->SiS_IF_DEF_DSTN || SiS_Pr->SiS_IF_DEF_FSTN) अणु
		 temp = 0x08;
		 tempbl = 0;
		 अगर((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) अणु
		    अगर(ROMAddr[0x13c] & 0x80) tempbl = 0xf0;
		 पूर्ण
	      पूर्ण

	      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2D,tempbl,temp);	    /* Panel Link Delay Compensation */
	   पूर्ण

	पूर्ण /* < 661 */

	tempax = 0;
	अगर(modeflag & DoubleScanMode) tempax |= 0x80;
	अगर(modeflag & HalfDCLK)       tempax |= 0x40;
	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2C,0x3f,tempax);

#पूर्ण_अगर  /* CONFIG_FB_SIS_315 */

     पूर्ण

  पूर्ण  /* Slavemode */

  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
     अगर((SiS_Pr->SiS_VBType & VB_NoLCD) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) अणु
	/* For 301BDH with LCD, we set up the Panel Link */
	SiS_SetGroup1_LVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	SiS_SetGroup1_301(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     पूर्ण
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->ChipType < SIS_315H) अणु
	SiS_SetGroup1_LVDS(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     पूर्ण अन्यथा अणु
	अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	   अगर((!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) || (SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
	      SiS_SetGroup1_LVDS(SiS_Pr, ModeNo,ModeIdIndex,RefreshRateTableIndex);
	   पूर्ण
	पूर्ण अन्यथा अणु
	   SiS_SetGroup1_LVDS(SiS_Pr, ModeNo,ModeIdIndex,RefreshRateTableIndex);
	पूर्ण
     पूर्ण
  पूर्ण
पूर्ण

/*********************************************/
/*         SET PART 2 REGISTER GROUP         */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_315
अटल अचिन्हित अक्षर *
SiS_GetGroup2CLVXPtr(काष्ठा SiS_Private *SiS_Pr, पूर्णांक tabletype)
अणु
   स्थिर अचिन्हित अक्षर *tableptr = शून्य;
   अचिन्हित लघु      a, b, p = 0;

   a = SiS_Pr->SiS_VGAHDE;
   b = SiS_Pr->SiS_HDE;
   अगर(tabletype) अणु
      a = SiS_Pr->SiS_VGAVDE;
      b = SiS_Pr->SiS_VDE;
   पूर्ण

   अगर(a < b) अणु
      tableptr = SiS_Part2CLVX_1;
   पूर्ण अन्यथा अगर(a == b) अणु
      tableptr = SiS_Part2CLVX_2;
   पूर्ण अन्यथा अणु
      अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
	 tableptr = SiS_Part2CLVX_4;
      पूर्ण अन्यथा अणु
	 tableptr = SiS_Part2CLVX_3;
      पूर्ण
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
	 अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525i) 	tableptr = SiS_Part2CLVX_3;
	 अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) 	tableptr = SiS_Part2CLVX_3;
	 अन्यथा 				         	tableptr = SiS_Part2CLVX_5;
      पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	 tableptr = SiS_Part2CLVX_6;
      पूर्ण
      करो अणु
	 अगर((tableptr[p] | tableptr[p+1] << 8) == a) अवरोध;
	 p += 0x42;
      पूर्ण जबतक((tableptr[p] | tableptr[p+1] << 8) != 0xffff);
      अगर((tableptr[p] | tableptr[p+1] << 8) == 0xffff) p -= 0x42;
   पूर्ण
   p += 2;
   वापस ((अचिन्हित अक्षर *)&tableptr[p]);
पूर्ण

अटल व्योम
SiS_SetGroup2_C_ELV(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
	      	    अचिन्हित लघु RefreshRateTableIndex)
अणु
   अचिन्हित अक्षर *tableptr;
   अचिन्हित अक्षर temp;
   पूर्णांक i, j;

   अगर(!(SiS_Pr->SiS_VBType & VB_SISTAP4SCALER)) वापस;

   tableptr = SiS_GetGroup2CLVXPtr(SiS_Pr, 0);
   क्रम(i = 0x80, j = 0; i <= 0xbf; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_Part2Port, i, tableptr[j]);
   पूर्ण
   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
      tableptr = SiS_GetGroup2CLVXPtr(SiS_Pr, 1);
      क्रम(i = 0xc0, j = 0; i <= 0xff; i++, j++) अणु
         SiS_SetReg(SiS_Pr->SiS_Part2Port, i, tableptr[j]);
      पूर्ण
   पूर्ण
   temp = 0x10;
   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) temp |= 0x04;
   SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x4e,0xeb,temp);
पूर्ण

अटल bool
SiS_GetCRT2Part2Ptr(काष्ठा SiS_Private *SiS_Pr,अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex,
		    अचिन्हित लघु RefreshRateTableIndex,अचिन्हित लघु *CRT2Index,
		    अचिन्हित लघु *ResIndex)
अणु

  अगर(SiS_Pr->ChipType < SIS_315H) वापस false;

  अगर(ModeNo <= 0x13)
     (*ResIndex) = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  अन्यथा
     (*ResIndex) = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;

  (*ResIndex) &= 0x3f;
  (*CRT2Index) = 0;

  अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
     अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) अणु
        (*CRT2Index) = 200;
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_CustomT == CUT_ASUSA2H_2) अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
        अगर(SiS_Pr->SiS_SetFlag & LCDVESATiming) (*CRT2Index) = 206;
     पूर्ण
  पूर्ण
  वापस (((*CRT2Index) != 0));
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_300
अटल व्योम
SiS_Group2LCDSpecial(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु crt2crtc)
अणु
   अचिन्हित लघु tempcx;
   अटल स्थिर अचिन्हित अक्षर atable[] = अणु
       0xc3,0x9e,0xc3,0x9e,0x02,0x02,0x02,
       0xab,0x87,0xab,0x9e,0xe7,0x02,0x02
   पूर्ण;

   अगर(!SiS_Pr->UseCustomMode) अणु
      अगर( ( ( (SiS_Pr->ChipType == SIS_630) ||
	      (SiS_Pr->ChipType == SIS_730) ) &&
	    (SiS_Pr->ChipRevision > 2) )  &&
	  (SiS_Pr->SiS_LCDResInfo == Panel_1024x768) &&
	  (!(SiS_Pr->SiS_SetFlag & LCDVESATiming))  &&
	  (!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) ) अणु
	 अगर(ModeNo == 0x13) अणु
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x04,0xB9);
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x05,0xCC);
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x06,0xA6);
	 पूर्ण अन्यथा अगर((crt2crtc & 0x3F) == 4) अणु
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x2B);
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x13);
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x04,0xE5);
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x05,0x08);
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x06,0xE2);
	 पूर्ण
      पूर्ण

      अगर(SiS_Pr->ChipType < SIS_315H) अणु
	 अगर(SiS_Pr->SiS_LCDTypeInfo == 0x0c) अणु
	    crt2crtc &= 0x1f;
	    tempcx = 0;
	    अगर(!(SiS_Pr->SiS_VBInfo & SetNotSimuMode)) अणु
	       अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
		  tempcx += 7;
	       पूर्ण
	    पूर्ण
	    tempcx += crt2crtc;
	    अगर(crt2crtc >= 4) अणु
	       SiS_SetReg(SiS_Pr->SiS_Part2Port,0x06,0xff);
	    पूर्ण

	    अगर(!(SiS_Pr->SiS_VBInfo & SetNotSimuMode)) अणु
	       अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
		  अगर(crt2crtc == 4) अणु
		     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x28);
		  पूर्ण
	       पूर्ण
	    पूर्ण
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x18);
	    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x04,atable[tempcx]);
	 पूर्ण
      पूर्ण
   पूर्ण
पूर्ण

/* For ECS A907. Highly preliminary. */
अटल व्योम
SiS_Set300Part2Regs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RefreshRateTableIndex,
		    अचिन्हित लघु ModeNo)
अणु
  स्थिर काष्ठा SiS_Part2PortTbl *CRT2Part2Ptr = शून्य;
  अचिन्हित लघु crt2crtc, resindex;
  पूर्णांक i, j;

  अगर(SiS_Pr->ChipType != SIS_300) वापस;
  अगर(!(SiS_Pr->SiS_VBType & VB_SIS30xBLV)) वापस;
  अगर(SiS_Pr->UseCustomMode) वापस;

  अगर(ModeNo <= 0x13) अणु
     crt2crtc = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  पूर्ण अन्यथा अणु
     crt2crtc = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
  पूर्ण

  resindex = crt2crtc & 0x3F;
  अगर(SiS_Pr->SiS_SetFlag & LCDVESATiming) CRT2Part2Ptr = SiS_Pr->SiS_CRT2Part2_1024x768_1;
  अन्यथा                                    CRT2Part2Ptr = SiS_Pr->SiS_CRT2Part2_1024x768_2;

  /* The BIOS code (1.16.51,56) is obviously a fragment! */
  अगर(ModeNo > 0x13) अणु
     CRT2Part2Ptr = SiS_Pr->SiS_CRT2Part2_1024x768_1;
     resindex = 4;
  पूर्ण

  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x01,0x80,(CRT2Part2Ptr+resindex)->CR[0]);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x02,0x80,(CRT2Part2Ptr+resindex)->CR[1]);
  क्रम(i = 2, j = 0x04; j <= 0x06; i++, j++ ) अणु
     SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
  पूर्ण
  क्रम(j = 0x1c; j <= 0x1d; i++, j++ ) अणु
     SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
  पूर्ण
  क्रम(j = 0x1f; j <= 0x21; i++, j++ ) अणु
     SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x23,(CRT2Part2Ptr+resindex)->CR[10]);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0x0f,(CRT2Part2Ptr+resindex)->CR[11]);
पूर्ण
#पूर्ण_अगर

अटल व्योम
SiS_SetTVSpecial(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
  अगर(!(SiS_Pr->SiS_VBType & VB_SIS30xBLV)) वापस;
  अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoHiVision)) वापस;
  अगर(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p)) वापस;

  अगर(!(SiS_Pr->SiS_TVMode & TVSetPAL)) अणु
     अगर(SiS_Pr->SiS_TVMode & TVSetNTSC1024) अणु
        अटल स्थिर अचिन्हित अक्षर specialtv[] = अणु
		0xa7,0x07,0xf2,0x6e,0x17,0x8b,0x73,0x53,
		0x13,0x40,0x34,0xf4,0x63,0xbb,0xcc,0x7a,
		0x58,0xe4,0x73,0xda,0x13
	पूर्ण;
	पूर्णांक i, j;
	क्रम(i = 0x1c, j = 0; i <= 0x30; i++, j++) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,i,specialtv[j]);
	पूर्ण
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x43,0x72);
	अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750)) अणु
	   अगर(SiS_Pr->SiS_TVMode & TVSetPALM) अणु
	      SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x14);
	      SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x1b);
	   पूर्ण अन्यथा अणु
	      SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x14);  /* 15 */
	      SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x1a);  /* 1b */
	   पूर्ण
	पूर्ण
     पूर्ण
  पूर्ण अन्यथा अणु
     अगर((ModeNo == 0x38) || (ModeNo == 0x4a) || (ModeNo == 0x64) ||
        (ModeNo == 0x52) || (ModeNo == 0x58) || (ModeNo == 0x5c)) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x1b);  /* 21 */
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x54);  /* 5a */
     पूर्ण अन्यथा अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x1a);  /* 21 */
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x53);  /* 5a */
     पूर्ण
  पूर्ण
पूर्ण

अटल व्योम
SiS_SetGroup2_Tail(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
  अचिन्हित लघु temp;

  अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) अणु
     अगर(SiS_Pr->SiS_VGAVDE == 525) अणु
	temp = 0xc3;
	अगर(SiS_Pr->SiS_ModeType <= ModeVGA) अणु
	   temp++;
	   अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) temp += 2;
	पूर्ण
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2f,temp);
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x30,0xb3);
     पूर्ण अन्यथा अगर(SiS_Pr->SiS_VGAVDE == 420) अणु
	temp = 0x4d;
	अगर(SiS_Pr->SiS_ModeType <= ModeVGA) अणु
	   temp++;
	   अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) temp++;
	पूर्ण
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2f,temp);
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) अणु
	अगर(SiS_Pr->SiS_VBType & VB_SIS30xB) अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part2Port,0x1a,0x03);
	   /* Not always क्रम LV, see SetGrp2 */
	पूर्ण
	temp = 1;
	अगर(ModeNo <= 0x13) temp = 3;
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x0b,temp);
     पूर्ण
#अगर 0
     /* 651+301C, क्रम 1280x768 - करो I really need that? */
     अगर((SiS_Pr->SiS_PanelXRes == 1280) && (SiS_Pr->SiS_PanelYRes == 768)) अणु
        अगर(SiS_Pr->SiS_VBInfo & SetSimuScanMode) अणु
	   अगर(((SiS_Pr->SiS_HDE == 640) && (SiS_Pr->SiS_VDE == 480)) ||
	      ((SiS_Pr->SiS_HDE == 320) && (SiS_Pr->SiS_VDE == 240))) अणु
	      SiS_SetReg(SiS_Part2Port,0x01,0x2b);
	      SiS_SetReg(SiS_Part2Port,0x02,0x13);
	      SiS_SetReg(SiS_Part2Port,0x04,0xe5);
	      SiS_SetReg(SiS_Part2Port,0x05,0x08);
	      SiS_SetReg(SiS_Part2Port,0x06,0xe2);
	      SiS_SetReg(SiS_Part2Port,0x1c,0x21);
	      SiS_SetReg(SiS_Part2Port,0x1d,0x45);
	      SiS_SetReg(SiS_Part2Port,0x1f,0x0b);
	      SiS_SetReg(SiS_Part2Port,0x20,0x00);
	      SiS_SetReg(SiS_Part2Port,0x21,0xa9);
	      SiS_SetReg(SiS_Part2Port,0x23,0x0b);
	      SiS_SetReg(SiS_Part2Port,0x25,0x04);
	   पूर्ण
	पूर्ण
     पूर्ण
#पूर्ण_अगर
  पूर्ण
पूर्ण

अटल व्योम
SiS_SetGroup2(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु i, j, tempax, tempbx, tempcx, tempch, tempcl, temp;
  अचिन्हित लघु push2, modeflag, crt2crtc, bridgeoffset;
  अचिन्हित पूर्णांक   दीर्घtemp, PhaseIndex;
  bool           newtvphase;
  स्थिर अचिन्हित अक्षर *TimingPoपूर्णांक;
#अगर_घोषित CONFIG_FB_SIS_315
  अचिन्हित लघु resindex, CRT2Index;
  स्थिर काष्ठा SiS_Part2PortTbl *CRT2Part2Ptr = शून्य;

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) वापस;
#पूर्ण_अगर

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     crt2crtc = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  पूर्ण अन्यथा अगर(SiS_Pr->UseCustomMode) अणु
     modeflag = SiS_Pr->CModeFlag;
     crt2crtc = 0;
  पूर्ण अन्यथा अणु
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     crt2crtc = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
  पूर्ण

  temp = 0;
  अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToAVIDEO)) temp |= 0x08;
  अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToSVIDEO)) temp |= 0x04;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToSCART)     temp |= 0x02;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision)  temp |= 0x01;

  अगर(!(SiS_Pr->SiS_TVMode & TVSetPAL)) 	      temp |= 0x10;

  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x00,temp);

  PhaseIndex  = 0x01; /* SiS_PALPhase */
  TimingPoपूर्णांक = SiS_Pr->SiS_PALTiming;

  newtvphase = false;
  अगर( (SiS_Pr->SiS_VBType & VB_SIS30xBLV) &&
      ( (!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) ||
	(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) ) ) अणु
     newtvphase = true;
  पूर्ण

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु

     TimingPoपूर्णांक = SiS_Pr->SiS_HiTVExtTiming;
     अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
        TimingPoपूर्णांक = SiS_Pr->SiS_HiTVSt2Timing;
        अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) अणु
	   TimingPoपूर्णांक = SiS_Pr->SiS_HiTVSt1Timing;
        पूर्ण
     पूर्ण

  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु

     i = 0;
     अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)      i = 2;
     अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) i = 1;

     TimingPoपूर्णांक = &SiS_YPbPrTable[i][0];

     PhaseIndex = 0x00; /* SiS_NTSCPhase */

  पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु

     अगर(newtvphase) PhaseIndex = 0x09; /* SiS_PALPhase2 */

  पूर्ण अन्यथा अणु

     TimingPoपूर्णांक = SiS_Pr->SiS_NTSCTiming;
     PhaseIndex  = (SiS_Pr->SiS_TVMode & TVSetNTSCJ) ? 0x01 : 0x00;	/* SiS_PALPhase : SiS_NTSCPhase */
     अगर(newtvphase) PhaseIndex += 8;					/* SiS_PALPhase2 : SiS_NTSCPhase2 */

  पूर्ण

  अगर(SiS_Pr->SiS_TVMode & (TVSetPALM | TVSetPALN)) अणु
     PhaseIndex = (SiS_Pr->SiS_TVMode & TVSetPALM) ? 0x02 : 0x03;	/* SiS_PALMPhase : SiS_PALNPhase */
     अगर(newtvphase) PhaseIndex += 8;					/* SiS_PALMPhase2 : SiS_PALNPhase2 */
  पूर्ण

  अगर(SiS_Pr->SiS_TVMode & TVSetNTSC1024) अणु
     अगर(SiS_Pr->SiS_TVMode & TVSetPALM) अणु
        PhaseIndex = 0x05; /* SiS_SpecialPhaseM */
     पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetNTSCJ) अणु
        PhaseIndex = 0x11; /* SiS_SpecialPhaseJ */
     पूर्ण अन्यथा अणु
        PhaseIndex = 0x10; /* SiS_SpecialPhase */
     पूर्ण
  पूर्ण

  क्रम(i = 0x31, j = 0; i <= 0x34; i++, j++) अणु
     SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS_TVPhase[(PhaseIndex * 4) + j]);
  पूर्ण

  क्रम(i = 0x01, j = 0; i <= 0x2D; i++, j++) अणु
     SiS_SetReg(SiS_Pr->SiS_Part2Port,i,TimingPoपूर्णांक[j]);
  पूर्ण
  क्रम(i = 0x39; i <= 0x45; i++, j++) अणु
     SiS_SetReg(SiS_Pr->SiS_Part2Port,i,TimingPoपूर्णांक[j]);
  पूर्ण

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
     अगर(SiS_Pr->SiS_ModeType != ModeText) अणु
        SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x3A,0x1F);
     पूर्ण
  पूर्ण

  SiS_SetRegOR(SiS_Pr->SiS_Part2Port,0x0A,SiS_Pr->SiS_NewFlickerMode);

  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x35,SiS_Pr->SiS_RY1COE);
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x36,SiS_Pr->SiS_RY2COE);
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x37,SiS_Pr->SiS_RY3COE);
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x38,SiS_Pr->SiS_RY4COE);

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision)	tempax = 950;
  अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)  tempax = 680;
  अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPAL)	tempax = 520;
  अन्यथा						tempax = 440; /* NTSC, YPbPr 525 */

  अगर( ((SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) && (SiS_Pr->SiS_VDE <= tempax)) ||
      ( (SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoHiVision) &&
        ((SiS_Pr->SiS_VGAHDE == 1024) || (SiS_Pr->SiS_VDE <= tempax)) ) ) अणु

     tempax -= SiS_Pr->SiS_VDE;
     tempax >>= 1;
     अगर(!(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p))) अणु
        tempax >>= 1;
     पूर्ण
     tempax &= 0x00ff;

     temp = tempax + (अचिन्हित लघु)TimingPoपूर्णांक[0];
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,temp);

     temp = tempax + (अचिन्हित लघु)TimingPoपूर्णांक[1];
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,temp);

     अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToTVNoYPbPrHiVision) && (SiS_Pr->SiS_VGAHDE >= 1024)) अणु
        अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x1b);
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x54);
        पूर्ण अन्यथा अणु
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,0x17);
           SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,0x1d);
        पूर्ण
     पूर्ण

  पूर्ण

  tempcx = SiS_Pr->SiS_HT;
  अगर(SiS_IsDualLink(SiS_Pr)) tempcx >>= 1;
  tempcx--;
  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) tempcx--;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1B,tempcx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1D,0xF0,((tempcx >> 8) & 0x0f));

  tempcx = SiS_Pr->SiS_HT >> 1;
  अगर(SiS_IsDualLink(SiS_Pr)) tempcx >>= 1;
  tempcx += 7;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) tempcx -= 4;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x22,0x0F,((tempcx << 4) & 0xf0));

  tempbx = TimingPoपूर्णांक[j] | (TimingPoपूर्णांक[j+1] << 8);
  tempbx += tempcx;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x24,tempbx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0x0F,((tempbx >> 4) & 0xf0));

  tempbx += 8;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
     tempbx -= 4;
     tempcx = tempbx;
  पूर्ण
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x29,0x0F,((tempbx << 4) & 0xf0));

  j += 2;
  tempcx += (TimingPoपूर्णांक[j] | (TimingPoपूर्णांक[j+1] << 8));
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x27,tempcx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x28,0x0F,((tempcx >> 4) & 0xf0));

  tempcx += 8;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) tempcx -= 4;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x2A,0x0F,((tempcx << 4) & 0xf0));

  tempcx = SiS_Pr->SiS_HT >> 1;
  अगर(SiS_IsDualLink(SiS_Pr)) tempcx >>= 1;
  j += 2;
  tempcx -= (TimingPoपूर्णांक[j] | ((TimingPoपूर्णांक[j+1]) << 8));
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x2D,0x0F,((tempcx << 4) & 0xf0));

  tempcx -= 11;
  अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) अणु
     tempcx = SiS_GetVGAHT2(SiS_Pr) - 1;
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2E,tempcx);

  tempbx = SiS_Pr->SiS_VDE;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
     अगर(SiS_Pr->SiS_VGAVDE == 360) tempbx = 746;
     अगर(SiS_Pr->SiS_VGAVDE == 375) tempbx = 746;
     अगर(SiS_Pr->SiS_VGAVDE == 405) tempbx = 853;
  पूर्ण अन्यथा अगर( (SiS_Pr->SiS_VBInfo & SetCRT2ToTV) &&
             (!(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p|TVSetYPbPr750p))) ) अणु
     tempbx >>= 1;
     अगर(SiS_Pr->ChipType >= SIS_315H) अणु
        अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) अणु
	   अगर((ModeNo <= 0x13) && (crt2crtc == 1)) tempbx++;
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	   अगर(SiS_Pr->SiS_ModeType <= ModeVGA) अणु
	      अगर(crt2crtc == 4) tempbx++;
	   पूर्ण
	पूर्ण
     पूर्ण
     अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
        अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	   अगर((ModeNo == 0x2f) || (ModeNo == 0x5d) || (ModeNo == 0x5e)) tempbx++;
	पूर्ण
	अगर(!(SiS_Pr->SiS_TVMode & TVSetPAL)) अणु
	   अगर(ModeNo == 0x03) tempbx++; /* From 1.10.7w - करोesn't make sense */
        पूर्ण
     पूर्ण
  पूर्ण
  tempbx -= 2;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2F,tempbx);

  temp = (tempcx >> 8) & 0x0F;
  temp |= ((tempbx >> 2) & 0xC0);
  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToSVIDEO | SetCRT2ToAVIDEO)) अणु
     temp |= 0x10;
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToAVIDEO) temp |= 0x20;
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x30,temp);

  अगर(SiS_Pr->SiS_VBType & VB_SISPART4OVERFLOW) अणु
     SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x10,0xdf,((tempbx & 0x0400) >> 5));
  पूर्ण

  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
     tempbx = SiS_Pr->SiS_VDE;
     अगर( (SiS_Pr->SiS_VBInfo & SetCRT2ToTV) &&
         (!(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p))) ) अणु
        tempbx >>= 1;
     पूर्ण
     tempbx -= 3;
     temp = ((tempbx >> 3) & 0x60) | 0x18;
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x46,temp);
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x47,tempbx);

     अगर(SiS_Pr->SiS_VBType & VB_SISPART4OVERFLOW) अणु
	SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x10,0xbf,((tempbx & 0x0400) >> 4));
     पूर्ण
  पूर्ण

  tempbx = 0;
  अगर(!(modeflag & HalfDCLK)) अणु
     अगर(SiS_Pr->SiS_VGAHDE >= SiS_Pr->SiS_HDE) अणु
        tempax = 0;
        tempbx |= 0x20;
     पूर्ण
  पूर्ण

  tempch = tempcl = 0x01;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
     अगर(SiS_Pr->SiS_VGAHDE >= 960) अणु
        अगर((!(modeflag & HalfDCLK)) || (SiS_Pr->ChipType < SIS_315H)) अणु
	   tempcl = 0x20;
	   अगर(SiS_Pr->SiS_VGAHDE >= 1280) अणु
              tempch = 20;
              tempbx &= ~0x20;
           पूर्ण अन्यथा अणु
	      tempch = 25; /* OK */
	   पूर्ण
        पूर्ण
     पूर्ण
  पूर्ण

  अगर(!(tempbx & 0x20)) अणु
     अगर(modeflag & HalfDCLK) tempcl <<= 1;
     दीर्घtemp = ((SiS_Pr->SiS_VGAHDE * tempch) / tempcl) << 13;
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) दीर्घtemp <<= 3;
     tempax = दीर्घtemp / SiS_Pr->SiS_HDE;
     अगर(दीर्घtemp % SiS_Pr->SiS_HDE) tempax++;
     tempbx |= ((tempax >> 8) & 0x1F);
     tempcx = tempax >> 13;
  पूर्ण

  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x44,tempax);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x45,0xC0,tempbx);

  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु

     tempcx &= 0x07;
     अगर(tempbx & 0x20) tempcx = 0;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x46,0xF8,tempcx);

     अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
        tempbx = 0x0382;
        tempcx = 0x007e;
     पूर्ण अन्यथा अणु
        tempbx = 0x0369;
        tempcx = 0x0061;
     पूर्ण
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x4B,tempbx);
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x4C,tempcx);
     temp = (tempcx & 0x0300) >> 6;
     temp |= ((tempbx >> 8) & 0x03);
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
        temp |= 0x10;
	अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p)      temp |= 0x20;
	अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) temp |= 0x40;
     पूर्ण
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x4D,temp);

     temp = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x43);
     SiS_SetReg(SiS_Pr->SiS_Part2Port,0x43,(temp - 3));

     SiS_SetTVSpecial(SiS_Pr, ModeNo);

     अगर(SiS_Pr->SiS_VBType & VB_SIS30xCLV) अणु
        temp = 0;
        अगर(SiS_Pr->SiS_TVMode & TVSetPALM) temp = 8;
        SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x4e,0xf7,temp);
     पूर्ण

  पूर्ण

  अगर(SiS_Pr->SiS_TVMode & TVSetPALM) अणु
     अगर(!(SiS_Pr->SiS_TVMode & TVSetNTSC1024)) अणु
        temp = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x01);
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,(temp - 1));
     पूर्ण
     SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xEF);
  पूर्ण

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
     अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,0x0B,0x00);
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) वापस;

  /* From here: Part2 LCD setup */

  tempbx = SiS_Pr->SiS_HDE;
  अगर(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
  tempbx--;			         	/* RHACTE = HDE - 1 */
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x2C,tempbx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x2B,0x0F,((tempbx >> 4) & 0xf0));

  temp = 0x01;
  अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) अणु
     अगर(SiS_Pr->SiS_ModeType == ModeEGA) अणु
        अगर(SiS_Pr->SiS_VGAHDE >= 1024) अणु
           temp = 0x02;
           अगर(SiS_Pr->SiS_SetFlag & LCDVESATiming) अणु
              temp = 0x01;
	   पूर्ण
        पूर्ण
     पूर्ण
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x0B,temp);

  tempbx = SiS_Pr->SiS_VDE - 1;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x03,tempbx);
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x0C,0xF8,((tempbx >> 8) & 0x07));

  tempcx = SiS_Pr->SiS_VT - 1;
  SiS_SetReg(SiS_Pr->SiS_Part2Port,0x19,tempcx);
  temp = (tempcx >> 3) & 0xE0;
  अगर(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) अणु
     /* Enable dithering; only करो this क्रम 32bpp mode */
     अगर(SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00) & 0x01) अणु
        temp |= 0x10;
     पूर्ण
  पूर्ण
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1A,0x0f,temp);

  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x09,0xF0);
  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x0A,0xF0);

  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x17,0xFB);
  SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x18,0xDF);

#अगर_घोषित CONFIG_FB_SIS_315
  अगर(SiS_GetCRT2Part2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex,
                          			&CRT2Index, &resindex)) अणु
      चयन(CRT2Index) अणु
        हाल 206: CRT2Part2Ptr = SiS310_CRT2Part2_Asus1024x768_3;    अवरोध;
	शेष:
        हाल 200: CRT2Part2Ptr = SiS_Pr->SiS_CRT2Part2_1024x768_1;   अवरोध;
      पूर्ण

      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x01,0x80,(CRT2Part2Ptr+resindex)->CR[0]);
      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x02,0x80,(CRT2Part2Ptr+resindex)->CR[1]);
      क्रम(i = 2, j = 0x04; j <= 0x06; i++, j++ ) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      पूर्ण
      क्रम(j = 0x1c; j <= 0x1d; i++, j++ ) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      पूर्ण
      क्रम(j = 0x1f; j <= 0x21; i++, j++ ) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,j,(CRT2Part2Ptr+resindex)->CR[i]);
      पूर्ण
      SiS_SetReg(SiS_Pr->SiS_Part2Port,0x23,(CRT2Part2Ptr+resindex)->CR[10]);
      SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0x0f,(CRT2Part2Ptr+resindex)->CR[11]);

      SiS_SetGroup2_Tail(SiS_Pr, ModeNo);

  पूर्ण अन्यथा अणु
#पूर्ण_अगर

    /* Checked क्रम 1024x768, 1280x1024, 1400x1050, 1600x1200 */
    /*             Clevo dual-link 1024x768 */
    /* 		   Compaq 1280x1024 has HT 1696 someबार (calculation OK, अगर given HT is correct)  */
    /*		   Acer: OK, but uses dअगरferent setting क्रम VESA timing at 640/800/1024 and 640x400 */

    अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
       अगर((SiS_Pr->SiS_LCDInfo & LCDPass11) || (SiS_Pr->PanelYRes == SiS_Pr->SiS_VDE)) अणु
          tempbx = SiS_Pr->SiS_VDE - 1;
          tempcx = SiS_Pr->SiS_VT - 1;
       पूर्ण अन्यथा अणु
          tempbx = SiS_Pr->SiS_VDE + ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VDE) / 2);
	  tempcx = SiS_Pr->SiS_VT - ((SiS_Pr->PanelYRes - SiS_Pr->SiS_VDE) / 2);
       पूर्ण
    पूर्ण अन्यथा अणु
       tempbx = SiS_Pr->PanelYRes;
       tempcx = SiS_Pr->SiS_VT;
       tempax = 1;
       अगर(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) अणु
          tempax = SiS_Pr->PanelYRes;
	  /* अगर(SiS_Pr->SiS_VGAVDE == 525) tempax += 0x3c;   */  /* 651+301C */
          अगर(SiS_Pr->PanelYRes < SiS_Pr->SiS_VDE) अणु
             tempax = tempcx = 0;
          पूर्ण अन्यथा अणु
             tempax -= SiS_Pr->SiS_VDE;
          पूर्ण
          tempax >>= 1;
       पूर्ण
       tempcx -= tempax; /* lcdvdes */
       tempbx -= tempax; /* lcdvdee */
    पूर्ण

    /* Non-expanding: lcdvdes = tempcx = VT-1; lcdvdee = tempbx = VDE-1 */

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x05,tempcx);	/* lcdvdes  */
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x06,tempbx);	/* lcdvdee  */

    temp = (tempbx >> 5) & 0x38;
    temp |= ((tempcx >> 8) & 0x07);
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x02,temp);

    tempax = SiS_Pr->SiS_VDE;
    अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) अणु
       tempax = SiS_Pr->PanelYRes;
    पूर्ण
    tempcx = (SiS_Pr->SiS_VT - tempax) >> 4;
    अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) अणु
       अगर(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) अणु
	  tempcx = (SiS_Pr->SiS_VT - tempax) / 10;
       पूर्ण
    पूर्ण

    tempbx = ((SiS_Pr->SiS_VT + SiS_Pr->SiS_VDE) >> 1) - 1;
    अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
       अगर(SiS_Pr->PanelYRes != SiS_Pr->SiS_VDE) अणु
          अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु /* ? */
             tempax = SiS_Pr->SiS_VT - SiS_Pr->PanelYRes;
	     अगर(tempax % 4) अणु tempax >>= 2; tempax++; पूर्ण
	     अन्यथा           अणु tempax >>= 2;           पूर्ण
             tempbx -= (tempax - 1);
	  पूर्ण अन्यथा अणु
	     tempbx -= 10;
	     अगर(tempbx <= SiS_Pr->SiS_VDE) tempbx = SiS_Pr->SiS_VDE + 1;
	  पूर्ण
       पूर्ण
    पूर्ण
    अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
       tempbx++;
       अगर((!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) || (crt2crtc == 6)) अणु
          अगर(SiS_Pr->SiS_SetFlag & LCDVESATiming) अणु
	     tempbx = 770;
	     tempcx = 3;
	  पूर्ण
       पूर्ण
    पूर्ण

    /* non-expanding: lcdvrs = ((VT + VDE) / 2) - 10 */

    अगर(SiS_Pr->UseCustomMode) अणु
       tempbx = SiS_Pr->CVSyncStart;
    पूर्ण

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x04,tempbx);	    /* lcdvrs */

    temp = (tempbx >> 4) & 0xF0;
    tempbx += (tempcx + 1);
    temp |= (tempbx & 0x0F);

    अगर(SiS_Pr->UseCustomMode) अणु
       temp &= 0xf0;
       temp |= (SiS_Pr->CVSyncEnd & 0x0f);
    पूर्ण

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x01,temp);

#अगर_घोषित CONFIG_FB_SIS_300
    SiS_Group2LCDSpecial(SiS_Pr, ModeNo, crt2crtc);
#पूर्ण_अगर

    bridgeoffset = 7;
    अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV)	bridgeoffset += 2;
    अगर(SiS_Pr->SiS_VBType & VB_SIS30xCLV)	bridgeoffset += 2; /* OK क्रम Averatec 1280x800 (301C) */
    अगर(SiS_IsDualLink(SiS_Pr))			bridgeoffset++;
    अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SIS302LV)	bridgeoffset++;    /* OK क्रम Asus A4L 1280x800 */
    /* Higher bridgeoffset shअगरts to the LEFT */

    temp = 0;
    अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) अणु
       अगर(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) अणु
	  temp = SiS_Pr->SiS_HT - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_HDE) / 2);
	  अगर(SiS_IsDualLink(SiS_Pr)) temp >>= 1;
       पूर्ण
    पूर्ण
    temp += bridgeoffset;
    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1F,temp);  	     /* lcdhdes */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x20,0x0F,((temp >> 4) & 0xf0));

    tempcx = SiS_Pr->SiS_HT;
    tempax = tempbx = SiS_Pr->SiS_HDE;
    अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) अणु
       अगर(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) अणु
          tempax = SiS_Pr->PanelXRes;
          tempbx = SiS_Pr->PanelXRes - ((SiS_Pr->PanelXRes - SiS_Pr->SiS_HDE) / 2);
       पूर्ण
    पूर्ण
    अगर(SiS_IsDualLink(SiS_Pr)) अणु
       tempcx >>= 1;
       tempbx >>= 1;
       tempax >>= 1;
    पूर्ण

    tempbx += bridgeoffset;

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x23,tempbx);	    /* lcdhdee */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x25,0xF0,((tempbx >> 8) & 0x0f));

    tempcx = (tempcx - tempax) >> 2;

    tempbx += tempcx;
    push2 = tempbx;

    अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) अणु
       अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) अणु
          अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) अणु
             अगर(SiS_Pr->SiS_HDE == 1280) tempbx = (tempbx & 0xff00) | 0x47;
	  पूर्ण
       पूर्ण
    पूर्ण

    अगर(SiS_Pr->UseCustomMode) अणु
       tempbx = SiS_Pr->CHSyncStart;
       अगर(modeflag & HalfDCLK) tempbx <<= 1;
       अगर(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
       tempbx += bridgeoffset;
    पूर्ण

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1C,tempbx);	    /* lcdhrs */
    SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1D,0x0F,((tempbx >> 4) & 0xf0));

    tempbx = push2;

    tempcx <<= 1;
    अगर((SiS_Pr->SiS_LCDInfo & DontExpandLCD) && (!(SiS_Pr->SiS_LCDInfo & LCDPass11))) अणु
       अगर(SiS_Pr->PanelXRes != SiS_Pr->SiS_HDE) tempcx >>= 2;
    पूर्ण
    tempbx += tempcx;

    अगर(SiS_Pr->UseCustomMode) अणु
       tempbx = SiS_Pr->CHSyncEnd;
       अगर(modeflag & HalfDCLK) tempbx <<= 1;
       अगर(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
       tempbx += bridgeoffset;
    पूर्ण

    SiS_SetReg(SiS_Pr->SiS_Part2Port,0x21,tempbx);	    /* lcdhre */

    SiS_SetGroup2_Tail(SiS_Pr, ModeNo);

#अगर_घोषित CONFIG_FB_SIS_300
    SiS_Set300Part2Regs(SiS_Pr, ModeIdIndex, RefreshRateTableIndex, ModeNo);
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_SIS_315
  पूर्ण /* CRT2-LCD from table */
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*         SET PART 3 REGISTER GROUP         */
/*********************************************/

अटल व्योम
SiS_SetGroup3(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित लघु i;
  स्थिर अचिन्हित अक्षर *tempdi;

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) वापस;

#अगर_अघोषित SIS_CP
  SiS_SetReg(SiS_Pr->SiS_Part3Port,0x00,0x00);
#अन्यथा
  SIS_CP_INIT301_CP
#पूर्ण_अगर

  अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x13,0xFA);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x14,0xC8);
  पूर्ण अन्यथा अणु
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x13,0xF5);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x14,0xB7);
  पूर्ण

  अगर(SiS_Pr->SiS_TVMode & TVSetPALM) अणु
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x13,0xFA);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x14,0xC8);
     SiS_SetReg(SiS_Pr->SiS_Part3Port,0x3D,0xA8);
  पूर्ण

  tempdi = शून्य;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
     tempdi = SiS_Pr->SiS_HiTVGroup3Data;
     अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) अणु
        tempdi = SiS_Pr->SiS_HiTVGroup3Simu;
     पूर्ण
  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) अणु
     अगर(!(SiS_Pr->SiS_TVMode & TVSetYPbPr525i)) अणु
        tempdi = SiS_HiTVGroup3_1;
        अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) tempdi = SiS_HiTVGroup3_2;
     पूर्ण
  पूर्ण
  अगर(tempdi) अणु
     क्रम(i=0; i<=0x3E; i++) अणु
        SiS_SetReg(SiS_Pr->SiS_Part3Port,i,tempdi[i]);
     पूर्ण
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xCLV) अणु
	अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part3Port,0x28,0x3f);
	पूर्ण
     पूर्ण
  पूर्ण

#अगर_घोषित SIS_CP
  SIS_CP_INIT301_CP2
#पूर्ण_अगर
पूर्ण

/*********************************************/
/*         SET PART 4 REGISTER GROUP         */
/*********************************************/

#अगर_घोषित CONFIG_FB_SIS_315
#अगर 0
अटल व्योम
SiS_ShअगरtXPos(काष्ठा SiS_Private *SiS_Pr, पूर्णांक shअगरt)
अणु
   अचिन्हित लघु temp, temp1, temp2;

   temp1 = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x1f);
   temp2 = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x20);
   temp = (अचिन्हित लघु)((पूर्णांक)((temp1 | ((temp2 & 0xf0) << 4))) + shअगरt);
   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x1f,temp);
   SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x20,0x0f,((temp >> 4) & 0xf0));
   temp = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x2b) & 0x0f;
   temp = (अचिन्हित लघु)((पूर्णांक)(temp) + shअगरt);
   SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x2b,0xf0,(temp & 0x0f));
   temp1 = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x43);
   temp2 = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x42);
   temp = (अचिन्हित लघु)((पूर्णांक)((temp1 | ((temp2 & 0xf0) << 4))) + shअगरt);
   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x43,temp);
   SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x42,0x0f,((temp >> 4) & 0xf0));
पूर्ण
#पूर्ण_अगर

अटल व्योम
SiS_SetGroup4_C_ELV(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
   अचिन्हित लघु temp, temp1;
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;

   अगर(!(SiS_Pr->SiS_VBType & VB_SIS30xCLV)) वापस;
   अगर(!(SiS_Pr->SiS_VBInfo & (SetCRT2ToHiVision | SetCRT2ToYPbPr525750))) वापस;

   अगर(SiS_Pr->ChipType >= XGI_20) वापस;

   अगर((SiS_Pr->ChipType >= SIS_661) && (SiS_Pr->SiS_ROMNew)) अणु
      अगर(!(ROMAddr[0x61] & 0x04)) वापस;
   पूर्ण

   SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x3a,0x08);
   temp = SiS_GetReg(SiS_Pr->SiS_Part4Port,0x3a);
   अगर(!(temp & 0x01)) अणु
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x3a,0xdf);
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x25,0xfc);
      अगर((SiS_Pr->ChipType < SIS_661) && (!(SiS_Pr->SiS_ROMNew))) अणु
         SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x25,0xf8);
      पूर्ण
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x0f,0xfb);
      अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p)      temp = 0x0000;
      अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) temp = 0x0002;
      अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetHiVision)  temp = 0x0400;
      अन्यथा					   temp = 0x0402;
      अगर((SiS_Pr->ChipType >= SIS_661) || (SiS_Pr->SiS_ROMNew)) अणु
         temp1 = 0;
	 अगर(SiS_Pr->SiS_TVMode & TVAspect43) temp1 = 4;
	 SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x0f,0xfb,temp1);
	 अगर(SiS_Pr->SiS_TVMode & TVAspect43LB) temp |= 0x01;
	 SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x26,0x7c,(temp & 0xff));
	 SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x3a,0xfb,(temp >> 8));
	 अगर(ModeNo > 0x13) अणु
            SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x39,0xfd);
         पूर्ण
      पूर्ण अन्यथा अणु
         temp1 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x3b) & 0x03;
	 अगर(temp1 == 0x01) temp |= 0x01;
	 अगर(temp1 == 0x03) temp |= 0x04;  /* ? why not 0x10? */
	 SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x26,0xf8,(temp & 0xff));
	 SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x3a,0xfb,(temp >> 8));
	 अगर(ModeNo > 0x13) अणु
            SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x3b,0xfd);
         पूर्ण
      पूर्ण

#अगर 0
      अगर(SiS_Pr->ChipType >= SIS_661) अणु 		/* ? */
         अगर(SiS_Pr->SiS_TVMode & TVAspect43) अणु
            अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) अणु
	       अगर(resinfo == SIS_RI_1024x768) अणु
	          SiS_ShअगरtXPos(SiS_Pr, 97);
	       पूर्ण अन्यथा अणु
	          SiS_ShअगरtXPos(SiS_Pr, 111);
	       पूर्ण
	    पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetHiVision) अणु
	       SiS_ShअगरtXPos(SiS_Pr, 136);
	    पूर्ण
         पूर्ण
      पूर्ण
#पूर्ण_अगर

   पूर्ण

पूर्ण
#पूर्ण_अगर

अटल व्योम
SiS_SetCRT2VCLK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
                 अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु vclkindex, temp, reg1, reg2;

  अगर(SiS_Pr->UseCustomMode) अणु
     reg1 = SiS_Pr->CSR2B;
     reg2 = SiS_Pr->CSR2C;
  पूर्ण अन्यथा अणु
     vclkindex = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
     reg1 = SiS_Pr->SiS_VBVCLKData[vclkindex].Part4_A;
     reg2 = SiS_Pr->SiS_VBVCLKData[vclkindex].Part4_B;
  पूर्ण

  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
     अगर(SiS_Pr->SiS_TVMode & (TVSetNTSC1024 | TVSet525p1024)) अणु
        SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0a,0x57);
 	SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0b,0x46);
	SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1f,0xf6);
     पूर्ण अन्यथा अणु
        SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0a,reg1);
        SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0b,reg2);
     पूर्ण
  पूर्ण अन्यथा अणु
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0a,0x01);
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0b,reg2);
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x0a,reg1);
  पूर्ण
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x12,0x00);
  temp = 0x08;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) temp |= 0x20;
  SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x12,temp);
पूर्ण

अटल व्योम
SiS_SetDualLinkEtc(काष्ठा SiS_Private *SiS_Pr)
अणु
  अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     अगर(SiS_Pr->SiS_VBType & VB_SISDUALLINK) अणु
	अगर((SiS_CRT2IsLCD(SiS_Pr)) ||
	   (SiS_IsVAMode(SiS_Pr))) अणु
	   अगर(SiS_Pr->SiS_LCDInfo & LCDDualLink) अणु
	      SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x27,0x2c);
	   पूर्ण अन्यथा अणु
	      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x27,~0x20);
	   पूर्ण
	पूर्ण
     पूर्ण
  पूर्ण
  अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x2a,0x00);
#अगर_घोषित SET_EMI
     SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
#पूर्ण_अगर
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x34,0x10);
  पूर्ण
पूर्ण

अटल व्योम
SiS_SetGroup4(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु tempax, tempcx, tempbx, modeflag, temp, resinfo;
  अचिन्हित पूर्णांक   tempebx, tempeax, tempदीर्घ;

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
  पूर्ण अन्यथा अगर(SiS_Pr->UseCustomMode) अणु
     modeflag = SiS_Pr->CModeFlag;
     resinfo = 0;
  पूर्ण अन्यथा अणु
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
  पूर्ण

  अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part4Port,0x24,0x0e);
	पूर्ण
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_VBType & (VB_SIS30xCLV | VB_SIS302LV)) अणु
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x10,0x9f);
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->ChipType >= SIS_315H) अणु
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	SiS_SetDualLinkEtc(SiS_Pr);
	वापस;
     पूर्ण
  पूर्ण

  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x13,SiS_Pr->SiS_RVBHCFACT);

  tempbx = SiS_Pr->SiS_RVBHCMAX;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x14,tempbx);

  temp = (tempbx >> 1) & 0x80;

  tempcx = SiS_Pr->SiS_VGAHT - 1;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x16,tempcx);

  temp |= ((tempcx >> 5) & 0x78);

  tempcx = SiS_Pr->SiS_VGAVT - 1;
  अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) tempcx -= 5;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x17,tempcx);

  temp |= ((tempcx >> 8) & 0x07);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x15,temp);

  tempbx = SiS_Pr->SiS_VGAHDE;
  अगर(modeflag & HalfDCLK)    tempbx >>= 1;
  अगर(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
     temp = 0;
     अगर(tempbx > 800)        temp = 0x60;
  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
     temp = 0;
     अगर(tempbx > 1024)       temp = 0xC0;
     अन्यथा अगर(tempbx >= 960)  temp = 0xA0;
  पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & (TVSetYPbPr525p | TVSetYPbPr750p)) अणु
     temp = 0;
     अगर(tempbx >= 1280)      temp = 0x40;
     अन्यथा अगर(tempbx >= 1024) temp = 0x20;
  पूर्ण अन्यथा अणु
     temp = 0x80;
     अगर(tempbx >= 1024)      temp = 0xA0;
  पूर्ण

  temp |= SiS_Pr->Init_P4_0E;

  अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
     अगर(SiS_Pr->SiS_LCDResInfo != Panel_1280x1024) अणु
        temp &= 0xf0;
        temp |= 0x0A;
     पूर्ण
  पूर्ण

  SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x0E,0x10,temp);

  tempeax = SiS_Pr->SiS_VGAVDE;
  tempebx = SiS_Pr->SiS_VDE;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
     अगर(!(temp & 0xE0)) tempebx >>=1;
  पूर्ण

  tempcx = SiS_Pr->SiS_RVBHRS;
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x18,tempcx);
  tempcx >>= 8;
  tempcx |= 0x40;

  अगर(tempeax <= tempebx) अणु
     tempcx ^= 0x40;
  पूर्ण अन्यथा अणु
     tempeax -= tempebx;
  पूर्ण

  tempeax *= (256 * 1024);
  tempदीर्घ = tempeax % tempebx;
  tempeax /= tempebx;
  अगर(tempदीर्घ) tempeax++;

  temp = (अचिन्हित लघु)(tempeax & 0x000000FF);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1B,temp);
  temp = (अचिन्हित लघु)((tempeax & 0x0000FF00) >> 8);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1A,temp);
  temp = (अचिन्हित लघु)((tempeax >> 12) & 0x70); /* sic! */
  temp |= (tempcx & 0x4F);
  SiS_SetReg(SiS_Pr->SiS_Part4Port,0x19,temp);

  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु

     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1C,0x28);

     /* Calc Linebuffer max address and set/clear decimode */
     tempbx = 0;
     अगर(SiS_Pr->SiS_TVMode & (TVSetHiVision | TVSetYPbPr750p)) tempbx = 0x08;
     tempax = SiS_Pr->SiS_VGAHDE;
     अगर(modeflag & HalfDCLK)    tempax >>= 1;
     अगर(SiS_IsDualLink(SiS_Pr)) tempax >>= 1;
     अगर(tempax > 800) अणु
        अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	   tempax -= 800;
	पूर्ण अन्यथा अणु
	   tempbx = 0x08;
	   अगर(tempax == 960)	   tempax *= 25; /* Correct */
           अन्यथा अगर(tempax == 1024) tempax *= 25;
           अन्यथा			   tempax *= 20;
	   temp = tempax % 32;
	   tempax /= 32;
	   अगर(temp) tempax++;
	   tempax++;
	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	      अगर(resinfo == SIS_RI_1024x768 ||
	         resinfo == SIS_RI_1024x576 ||
		 resinfo == SIS_RI_1280x1024 ||
		 resinfo == SIS_RI_1280x720) अणु
	         /* Otherwise white line or garbage at right edge */
	         tempax = (tempax & 0xff00) | 0x20;
	      पूर्ण
	   पूर्ण
	पूर्ण
     पूर्ण
     tempax--;
     temp = ((tempax >> 4) & 0x30) | tempbx;
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1D,tempax);
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x1E,temp);

     temp = 0x0036; tempbx = 0xD0;
     अगर((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->SiS_VBType & VB_SISLVDS)) अणु
	temp = 0x0026; tempbx = 0xC0; /* See En/DisableBridge() */
     पूर्ण
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
        अगर(!(SiS_Pr->SiS_TVMode & (TVSetNTSC1024 | TVSetHiVision | TVSetYPbPr750p | TVSetYPbPr525p))) अणु
	   temp |= 0x01;
	   अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
	      अगर(!(SiS_Pr->SiS_TVMode & TVSetTVSimuMode)) अणु
  	         temp &= ~0x01;
	      पूर्ण
	   पूर्ण
	पूर्ण
     पूर्ण
     SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x1F,tempbx,temp);

     tempbx = SiS_Pr->SiS_HT >> 1;
     अगर(SiS_IsDualLink(SiS_Pr)) tempbx >>= 1;
     tempbx -= 2;
     SiS_SetReg(SiS_Pr->SiS_Part4Port,0x22,tempbx);
     temp = (tempbx >> 5) & 0x38;
     SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x21,0xC0,temp);

     अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
           SiS_SetReg(SiS_Pr->SiS_Part4Port,0x24,0x0e);
	   /* LCD-too-dark-error-source, see FinalizeLCD() */
	पूर्ण
     पूर्ण

     SiS_SetDualLinkEtc(SiS_Pr);

  पूर्ण  /* 301B */

  SiS_SetCRT2VCLK(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
पूर्ण

/*********************************************/
/*         SET PART 5 REGISTER GROUP         */
/*********************************************/

अटल व्योम
SiS_SetGroup5(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)  वापस;

  अगर(SiS_Pr->SiS_ModeType == ModeVGA) अणु
     अगर(!(SiS_Pr->SiS_VBInfo & (SetInSlaveMode | LoadDACFlag))) अणु
        SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
        SiS_LoadDAC(SiS_Pr, ModeNo, ModeIdIndex);
     पूर्ण
  पूर्ण
पूर्ण

/*********************************************/
/*     MODIFY CRT1 GROUP FOR SLAVE MODE      */
/*********************************************/

अटल bool
SiS_GetLVDSCRT1Ptr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		   अचिन्हित लघु RefreshRateTableIndex, अचिन्हित लघु *ResIndex,
		   अचिन्हित लघु *DisplayType)
 अणु
  अचिन्हित लघु modeflag = 0;
  bool checkhd = true;

  /* Pass 1:1 not supported here */

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     (*ResIndex) = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  पूर्ण अन्यथा अणु
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     (*ResIndex) = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;
  पूर्ण

  (*ResIndex) &= 0x3F;

  अगर((SiS_Pr->SiS_IF_DEF_CH70xx) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) अणु

     (*DisplayType) = 80;
     अगर((SiS_Pr->SiS_TVMode & TVSetPAL) && (!(SiS_Pr->SiS_TVMode & TVSetPALM))) अणु
      	(*DisplayType) = 82;
	अगर(SiS_Pr->SiS_ModeType > ModeVGA) अणु
	   अगर(SiS_Pr->SiS_CHSOverScan) (*DisplayType) = 84;
	पूर्ण
     पूर्ण
     अगर((*DisplayType) != 84) अणु
        अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) (*DisplayType)++;
     पूर्ण

  पूर्ण अन्यथा अणु

     (*DisplayType = 0);
     चयन(SiS_Pr->SiS_LCDResInfo) अणु
     हाल Panel_320x240_1: (*DisplayType) = 50;
			   checkhd = false;
			   अवरोध;
     हाल Panel_320x240_2: (*DisplayType) = 14;
			   अवरोध;
     हाल Panel_320x240_3: (*DisplayType) = 18;
			   अवरोध;
     हाल Panel_640x480:   (*DisplayType) = 10;
			   अवरोध;
     हाल Panel_1024x600:  (*DisplayType) = 26;
			   अवरोध;
     शेष: वापस true;
     पूर्ण

     अगर(checkhd) अणु
        अगर(modeflag & HalfDCLK) (*DisplayType)++;
     पूर्ण

     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x600) अणु
        अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) (*DisplayType) += 2;
     पूर्ण

  पूर्ण

  वापस true;
पूर्ण

अटल व्योम
SiS_ModCRT1CRTC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
                अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित लघु tempah, i, modeflag, j, ResIndex, DisplayType;
  स्थिर काष्ठा SiS_LVDSCRT1Data *LVDSCRT1Ptr=शून्य;
  अटल स्थिर अचिन्हित लघु CRIdx[] = अणु
	0x00, 0x02, 0x03, 0x04, 0x05, 0x06,
	0x07, 0x10, 0x11, 0x15, 0x16
  पूर्ण;

  अगर((SiS_Pr->SiS_CustomT == CUT_BARCO1366) ||
     (SiS_Pr->SiS_CustomT == CUT_BARCO1024) ||
     (SiS_Pr->SiS_CustomT == CUT_PANEL848)  ||
     (SiS_Pr->SiS_CustomT == CUT_PANEL856) )
     वापस;

  अगर(SiS_Pr->SiS_IF_DEF_LVDS) अणु
     अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
        अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) वापस;
     पूर्ण
  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
     अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) वापस;
  पूर्ण अन्यथा वापस;

  अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) वापस;

  अगर(SiS_Pr->ChipType < SIS_315H) अणु
     अगर(SiS_Pr->SiS_SetFlag & SetDOSMode) वापस;
  पूर्ण

  अगर(!(SiS_GetLVDSCRT1Ptr(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex,
                          &ResIndex, &DisplayType))) अणु
     वापस;
  पूर्ण

  चयन(DisplayType) अणु
    हाल 50: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_1;           अवरोध; /* xSTN */
    हाल 14: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_2;           अवरोध; /* xSTN */
    हाल 15: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_2_H;         अवरोध; /* xSTN */
    हाल 18: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_3;           अवरोध; /* xSTN */
    हाल 19: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1320x240_3_H;         अवरोध; /* xSTN */
    हाल 10: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1640x480_1;           अवरोध;
    हाल 11: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT1640x480_1_H;         अवरोध;
#अगर 0 /* Works better with calculated numbers */
    हाल 26: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_1;          अवरोध;
    हाल 27: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_1_H;        अवरोध;
    हाल 28: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_2;          अवरोध;
    हाल 29: LVDSCRT1Ptr = SiS_Pr->SiS_LVDSCRT11024x600_2_H;        अवरोध;
#पूर्ण_अगर
    हाल 80: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1UNTSC;               अवरोध;
    हाल 81: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1ONTSC;               अवरोध;
    हाल 82: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1UPAL;                अवरोध;
    हाल 83: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1OPAL;                अवरोध;
    हाल 84: LVDSCRT1Ptr = SiS_Pr->SiS_CHTVCRT1SOPAL;               अवरोध;
  पूर्ण

  अगर(LVDSCRT1Ptr) अणु

     SiS_SetRegAND(SiS_Pr->SiS_P3d4,0x11,0x7f);

     क्रम(i = 0; i <= 10; i++) अणु
        tempah = (LVDSCRT1Ptr + ResIndex)->CR[i];
        SiS_SetReg(SiS_Pr->SiS_P3d4,CRIdx[i],tempah);
     पूर्ण

     क्रम(i = 0x0A, j = 11; i <= 0x0C; i++, j++) अणु
        tempah = (LVDSCRT1Ptr + ResIndex)->CR[j];
        SiS_SetReg(SiS_Pr->SiS_P3c4,i,tempah);
     पूर्ण

     tempah = (LVDSCRT1Ptr + ResIndex)->CR[14] & 0xE0;
     SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x0E,0x1f,tempah);

     अगर(ModeNo <= 0x13) modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     अन्यथा               modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

     tempah = ((LVDSCRT1Ptr + ResIndex)->CR[14] & 0x01) << 5;
     अगर(modeflag & DoubleScanMode) tempah |= 0x80;
     SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x09,~0x020,tempah);

  पूर्ण अन्यथा अणु

     SiS_CalcLCDACRT1Timing(SiS_Pr, ModeNo, ModeIdIndex);

  पूर्ण
पूर्ण

/*********************************************/
/*              SET CRT2 ECLK                */
/*********************************************/

अटल व्योम
SiS_SetCRT2ECLK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
           अचिन्हित लघु RefreshRateTableIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु clkbase, vclkindex = 0;
  अचिन्हित अक्षर  sr2b, sr2c;

  अगर(SiS_Pr->SiS_LCDInfo & LCDPass11) अणु
     SiS_Pr->SiS_SetFlag &= (~ProgrammingCRT2);
     अगर(SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRTVCLK == 2) अणु
	RefreshRateTableIndex--;
     पूर्ण
     vclkindex = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex,
                                    RefreshRateTableIndex);
     SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;
  पूर्ण अन्यथा अणु
     vclkindex = SiS_GetVCLK2Ptr(SiS_Pr, ModeNo, ModeIdIndex,
                                    RefreshRateTableIndex);
  पूर्ण

  sr2b = SiS_Pr->SiS_VCLKData[vclkindex].SR2B;
  sr2c = SiS_Pr->SiS_VCLKData[vclkindex].SR2C;

  अगर((SiS_Pr->SiS_CustomT == CUT_BARCO1366) || (SiS_Pr->SiS_CustomT == CUT_BARCO1024)) अणु
     अगर(SiS_Pr->SiS_UseROM) अणु
	अगर(ROMAddr[0x220] & 0x01) अणु
	   sr2b = ROMAddr[0x227];
	   sr2c = ROMAddr[0x228];
	पूर्ण
     पूर्ण
  पूर्ण

  clkbase = 0x02B;
  अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA)) अणु
     अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) अणु
	clkbase += 3;
     पूर्ण
  पूर्ण

  SiS_SetReg(SiS_Pr->SiS_P3c4,0x31,0x20);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase,sr2b);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase+1,sr2c);
  SiS_SetReg(SiS_Pr->SiS_P3c4,0x31,0x10);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase,sr2b);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase+1,sr2c);
  SiS_SetReg(SiS_Pr->SiS_P3c4,0x31,0x00);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase,sr2b);
  SiS_SetReg(SiS_Pr->SiS_P3c4,clkbase+1,sr2c);
पूर्ण

/*********************************************/
/*           SET UP CHRONTEL CHIPS           */
/*********************************************/

अटल व्योम
SiS_SetCHTVReg(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
               अचिन्हित लघु RefreshRateTableIndex)
अणु
   अचिन्हित लघु TVType, resindex;
   स्थिर काष्ठा SiS_CHTVRegData *CHTVRegData = शून्य;

   अगर(ModeNo <= 0x13)
      resindex = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
   अन्यथा
      resindex = SiS_Pr->SiS_RefIndex[RefreshRateTableIndex].Ext_CRT2CRTC;

   resindex &= 0x3F;

   TVType = 0;
   अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) TVType += 1;
   अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
      TVType += 2;
      अगर(SiS_Pr->SiS_ModeType > ModeVGA) अणु
	 अगर(SiS_Pr->SiS_CHSOverScan) TVType = 8;
      पूर्ण
      अगर(SiS_Pr->SiS_TVMode & TVSetPALM) अणु
	 TVType = 4;
	 अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) TVType += 1;
      पूर्ण अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPALN) अणु
	 TVType = 6;
	 अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) TVType += 1;
      पूर्ण
   पूर्ण

   चयन(TVType) अणु
      हाल  0: CHTVRegData = SiS_Pr->SiS_CHTVReg_UNTSC; अवरोध;
      हाल  1: CHTVRegData = SiS_Pr->SiS_CHTVReg_ONTSC; अवरोध;
      हाल  2: CHTVRegData = SiS_Pr->SiS_CHTVReg_UPAL;  अवरोध;
      हाल  3: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPAL;  अवरोध;
      हाल  4: CHTVRegData = SiS_Pr->SiS_CHTVReg_UPALM; अवरोध;
      हाल  5: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPALM; अवरोध;
      हाल  6: CHTVRegData = SiS_Pr->SiS_CHTVReg_UPALN; अवरोध;
      हाल  7: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPALN; अवरोध;
      हाल  8: CHTVRegData = SiS_Pr->SiS_CHTVReg_SOPAL; अवरोध;
      शेष: CHTVRegData = SiS_Pr->SiS_CHTVReg_OPAL;  अवरोध;
   पूर्ण


   अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 1) अणु

#अगर_घोषित CONFIG_FB_SIS_300

      /* Chrontel 7005 - I assume that it करोes not come with a 315 series chip */

      /* We करोn't support modes >800x600 */
      अगर (resindex > 5) वापस;

      अगर(SiS_Pr->SiS_TVMode & TVSetPAL) अणु
	 SiS_SetCH700x(SiS_Pr,0x04,0x43);  /* 0x40=76uA (PAL); 0x03=15bit non-multi RGB*/
	 SiS_SetCH700x(SiS_Pr,0x09,0x69);  /* Black level क्रम PAL (105)*/
      पूर्ण अन्यथा अणु
	 SiS_SetCH700x(SiS_Pr,0x04,0x03);   /* upper nibble=71uA (NTSC), 0x03=15bit non-multi RGB*/
	 SiS_SetCH700x(SiS_Pr,0x09,0x71);   /* Black level क्रम NTSC (113)*/
      पूर्ण

      SiS_SetCH700x(SiS_Pr,0x00,CHTVRegData[resindex].Reg[0]);	/* Mode रेजिस्टर */
      SiS_SetCH700x(SiS_Pr,0x07,CHTVRegData[resindex].Reg[1]);	/* Start active video रेजिस्टर */
      SiS_SetCH700x(SiS_Pr,0x08,CHTVRegData[resindex].Reg[2]);	/* Position overflow रेजिस्टर */
      SiS_SetCH700x(SiS_Pr,0x0a,CHTVRegData[resindex].Reg[3]);	/* Horiz Position रेजिस्टर */
      SiS_SetCH700x(SiS_Pr,0x0b,CHTVRegData[resindex].Reg[4]);	/* Vertical Position रेजिस्टर */

      /* Set minimum flicker filter क्रम Luma channel (SR1-0=00),
                minimum text enhancement (S3-2=10),
   	        maximum flicker filter क्रम Chroma channel (S5-4=10)
	        =00101000=0x28 (When पढ़ोing, S1-0->S3-2, and S3-2->S1-0!)
       */
      SiS_SetCH700x(SiS_Pr,0x01,0x28);

      /* Set video bandwidth
            High bandwidth Luma composite video filter(S0=1)
            low bandwidth Luma S-video filter (S2-1=00)
	    disable peak filter in S-video channel (S3=0)
	    high bandwidth Chroma Filter (S5-4=11)
	    =00110001=0x31
      */
      SiS_SetCH700x(SiS_Pr,0x03,0xb1);       /* old: 3103 */

      /* Register 0x3D करोes not exist in non-macrovision रेजिस्टर map
            (Maybe this is a macrovision रेजिस्टर?)
       */
#अगर_अघोषित SIS_CP
      SiS_SetCH70xx(SiS_Pr,0x3d,0x00);
#पूर्ण_अगर

      /* Register 0x10 only contains 1 writable bit (S0) क्रम sensing,
             all other bits a पढ़ो-only. Macrovision?
       */
      SiS_SetCH70xxANDOR(SiS_Pr,0x10,0x00,0x1F);

      /* Register 0x11 only contains 3 writable bits (S0-S2) क्रम
             contrast enhancement (set to 010 -> gain 1 Yout = 17/16*(Yin-30) )
       */
      SiS_SetCH70xxANDOR(SiS_Pr,0x11,0x02,0xF8);

      /* Clear DSEN
       */
      SiS_SetCH70xxANDOR(SiS_Pr,0x1c,0x00,0xEF);

      अगर(!(SiS_Pr->SiS_TVMode & TVSetPAL)) अणु		/* ---- NTSC ---- */
         अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) अणु
            अगर(resindex == 0x04) अणु   			/* 640x480 overscan: Mode 16 */
      	       SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	/* loop filter off */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x01,0xFE);	/* ACIV on, no need to set FSCI */
            पूर्ण अन्यथा अगर(resindex == 0x05) अणु    		/* 800x600 overscan: Mode 23 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x18,0x01,0xF0);	/* 0x18-0x1f: FSCI 469,762,048 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x19,0x0C,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1a,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1b,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1c,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1d,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1e,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1f,0x00,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x01,0xEF);	/* Loop filter on क्रम mode 23 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x00,0xFE);	/* ACIV off, need to set FSCI */
            पूर्ण
         पूर्ण अन्यथा अणु
            अगर(resindex == 0x04) अणु     			/* ----- 640x480 underscan; Mode 17 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	/* loop filter off */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x01,0xFE);
            पूर्ण अन्यथा अगर(resindex == 0x05) अणु   		/* ----- 800x600 underscan: Mode 24 */
#अगर 0
               SiS_SetCH70xxANDOR(SiS_Pr,0x18,0x01,0xF0);	/* (FSCI was 0x1f1c71c7 - this is क्रम mode 22) */
               SiS_SetCH70xxANDOR(SiS_Pr,0x19,0x09,0xF0);	/* FSCI क्रम mode 24 is 428,554,851 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x1a,0x08,0xF0);       /* 198b3a63 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x1b,0x0b,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1c,0x04,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1d,0x01,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1e,0x06,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x1f,0x05,0xF0);
               SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	/* loop filter off क्रम mode 24 */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x00,0xFE);	* ACIV off, need to set FSCI */
#पूर्ण_अगर         /* All alternatives wrong (datasheet wrong?), करोn't use FSCI */
	       SiS_SetCH70xxANDOR(SiS_Pr,0x20,0x00,0xEF);	 /* loop filter off */
               SiS_SetCH70xxANDOR(SiS_Pr,0x21,0x01,0xFE);
            पूर्ण
         पूर्ण
      पूर्ण अन्यथा अणु						/* ---- PAL ---- */
	/* We करोn't play around with FSCI in PAL mode */
	SiS_SetCH70xxANDOR(SiS_Pr, 0x20, 0x00, 0xEF);	/* loop filter off */
	SiS_SetCH70xxANDOR(SiS_Pr, 0x21, 0x01, 0xFE);	/* ACIV on */
      पूर्ण

#पूर्ण_अगर  /* 300 */

   पूर्ण अन्यथा अणु

      /* Chrontel 7019 - assumed that it करोes not come with a 300 series chip */

#अगर_घोषित CONFIG_FB_SIS_315

      अचिन्हित लघु temp;

      /* We करोn't support modes >1024x768 */
      अगर (resindex > 6) वापस;

      temp = CHTVRegData[resindex].Reg[0];
      अगर(SiS_Pr->SiS_TVMode & TVSetNTSCJ) temp |= 0x10;
      SiS_SetCH701x(SiS_Pr,0x00,temp);

      SiS_SetCH701x(SiS_Pr,0x01,CHTVRegData[resindex].Reg[1]);
      SiS_SetCH701x(SiS_Pr,0x02,CHTVRegData[resindex].Reg[2]);
      SiS_SetCH701x(SiS_Pr,0x04,CHTVRegData[resindex].Reg[3]);
      SiS_SetCH701x(SiS_Pr,0x03,CHTVRegData[resindex].Reg[4]);
      SiS_SetCH701x(SiS_Pr,0x05,CHTVRegData[resindex].Reg[5]);
      SiS_SetCH701x(SiS_Pr,0x06,CHTVRegData[resindex].Reg[6]);

      temp = CHTVRegData[resindex].Reg[7];
      अगर(SiS_Pr->SiS_TVMode & TVSetNTSCJ) temp = 0x66;
      SiS_SetCH701x(SiS_Pr,0x07,temp);

      SiS_SetCH701x(SiS_Pr,0x08,CHTVRegData[resindex].Reg[8]);
      SiS_SetCH701x(SiS_Pr,0x15,CHTVRegData[resindex].Reg[9]);
      SiS_SetCH701x(SiS_Pr,0x1f,CHTVRegData[resindex].Reg[10]);
      SiS_SetCH701x(SiS_Pr,0x0c,CHTVRegData[resindex].Reg[11]);
      SiS_SetCH701x(SiS_Pr,0x0d,CHTVRegData[resindex].Reg[12]);
      SiS_SetCH701x(SiS_Pr,0x0e,CHTVRegData[resindex].Reg[13]);
      SiS_SetCH701x(SiS_Pr,0x0f,CHTVRegData[resindex].Reg[14]);
      SiS_SetCH701x(SiS_Pr,0x10,CHTVRegData[resindex].Reg[15]);

      temp = SiS_GetCH701x(SiS_Pr,0x21) & ~0x02;
      /* D1 should be set क्रम PAL, PAL-N and NTSC-J,
         but I won't करो that क्रम PAL unless somebody
	 tells me to करो so. Since the BIOS uses
	 non-शेष CIV values and blacklevels,
	 this might be compensated anyway.
       */
      अगर(SiS_Pr->SiS_TVMode & (TVSetPALN | TVSetNTSCJ)) temp |= 0x02;
      SiS_SetCH701x(SiS_Pr,0x21,temp);

#पूर्ण_अगर	/* 315 */

   पूर्ण

#अगर_घोषित SIS_CP
   SIS_CP_INIT301_CP3
#पूर्ण_अगर

पूर्ण

#अगर_घोषित CONFIG_FB_SIS_315  /* ----------- 315 series only ---------- */

व्योम
SiS_Chrontel701xBLOn(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु temp;

   /* Enable Chrontel 7019 LCD panel backlight */
   अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
      अगर(SiS_Pr->ChipType == SIS_740) अणु
	 SiS_SetCH701x(SiS_Pr,0x66,0x65);
      पूर्ण अन्यथा अणु
	 temp = SiS_GetCH701x(SiS_Pr,0x66);
	 temp |= 0x20;
	 SiS_SetCH701x(SiS_Pr,0x66,temp);
      पूर्ण
   पूर्ण
पूर्ण

व्योम
SiS_Chrontel701xBLOff(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु temp;

   /* Disable Chrontel 7019 LCD panel backlight */
   अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
      temp = SiS_GetCH701x(SiS_Pr,0x66);
      temp &= 0xDF;
      SiS_SetCH701x(SiS_Pr,0x66,temp);
   पूर्ण
पूर्ण

अटल व्योम
SiS_ChrontelPowerSequencing(काष्ठा SiS_Private *SiS_Pr)
अणु
  अटल स्थिर अचिन्हित अक्षर regtable[]      = अणु 0x67, 0x68, 0x69, 0x6a, 0x6b पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1024_740[] = अणु 0x01, 0x02, 0x01, 0x01, 0x01 पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1400_740[] = अणु 0x01, 0x6e, 0x01, 0x01, 0x01 पूर्ण;
  अटल स्थिर अचिन्हित अक्षर asus1024_740[]  = अणु 0x19, 0x6e, 0x01, 0x19, 0x09 पूर्ण;
  अटल स्थिर अचिन्हित अक्षर asus1400_740[]  = अणु 0x19, 0x6e, 0x01, 0x19, 0x09 पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1024_650[] = अणु 0x01, 0x02, 0x01, 0x01, 0x02 पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1400_650[] = अणु 0x01, 0x02, 0x01, 0x01, 0x02 पूर्ण;
  स्थिर अचिन्हित अक्षर *tableptr = शून्य;
  पूर्णांक i;

  /* Set up Power up/करोwn timing */

  अगर(SiS_Pr->ChipType == SIS_740) अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	अगर(SiS_Pr->SiS_CustomT == CUT_ASUSL3000D) tableptr = asus1024_740;
	अन्यथा    			          tableptr = table1024_740;
     पूर्ण अन्यथा अगर((SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) ||
	       (SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) ||
	       (SiS_Pr->SiS_LCDResInfo == Panel_1600x1200)) अणु
	अगर(SiS_Pr->SiS_CustomT == CUT_ASUSL3000D) tableptr = asus1400_740;
        अन्यथा					  tableptr = table1400_740;
     पूर्ण अन्यथा वापस;
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	tableptr = table1024_650;
     पूर्ण अन्यथा अगर((SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) ||
	       (SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) ||
	       (SiS_Pr->SiS_LCDResInfo == Panel_1600x1200)) अणु
	tableptr = table1400_650;
     पूर्ण अन्यथा वापस;
  पूर्ण

  क्रम(i=0; i<5; i++) अणु
     SiS_SetCH701x(SiS_Pr, regtable[i], tableptr[i]);
  पूर्ण
पूर्ण

अटल व्योम
SiS_SetCH701xForLCD(काष्ठा SiS_Private *SiS_Pr)
अणु
  स्थिर अचिन्हित अक्षर *tableptr = शून्य;
  अचिन्हित लघु tempbh;
  पूर्णांक i;
  अटल स्थिर अचिन्हित अक्षर regtable[] = अणु
		0x1c, 0x5f, 0x64, 0x6f, 0x70, 0x71,
		0x72, 0x73, 0x74, 0x76, 0x78, 0x7d, 0x66
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1024_740[] = अणु
		0x60, 0x02, 0x00, 0x07, 0x40, 0xed,
		0xa3, 0xc8, 0xc7, 0xac, 0xe0, 0x02, 0x44
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1280_740[] = अणु
		0x60, 0x03, 0x11, 0x00, 0x40, 0xe3,
		0xad, 0xdb, 0xf6, 0xac, 0xe0, 0x02, 0x44
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1400_740[] = अणु
		0x60, 0x03, 0x11, 0x00, 0x40, 0xe3,
		0xad, 0xdb, 0xf6, 0xac, 0xe0, 0x02, 0x44
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1600_740[] = अणु
		0x60, 0x04, 0x11, 0x00, 0x40, 0xe3,
		0xad, 0xde, 0xf6, 0xac, 0x60, 0x1a, 0x44
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1024_650[] = अणु
		0x60, 0x02, 0x00, 0x07, 0x40, 0xed,
		0xa3, 0xc8, 0xc7, 0xac, 0x60, 0x02
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1280_650[] = अणु
		0x60, 0x03, 0x11, 0x00, 0x40, 0xe3,
		0xad, 0xdb, 0xf6, 0xac, 0xe0, 0x02
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1400_650[] = अणु
		0x60, 0x03, 0x11, 0x00, 0x40, 0xef,
		0xad, 0xdb, 0xf6, 0xac, 0x60, 0x02
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर table1600_650[] = अणु
		0x60, 0x04, 0x11, 0x00, 0x40, 0xe3,
		0xad, 0xde, 0xf6, 0xac, 0x60, 0x1a
  पूर्ण;

  अगर(SiS_Pr->ChipType == SIS_740) अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768)       tableptr = table1024_740;
     अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) tableptr = table1280_740;
     अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) tableptr = table1400_740;
     अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) tableptr = table1600_740;
     अन्यथा वापस;
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768)       tableptr = table1024_650;
     अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) tableptr = table1280_650;
     अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) tableptr = table1400_650;
     अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) tableptr = table1600_650;
     अन्यथा वापस;
  पूर्ण

  tempbh = SiS_GetCH701x(SiS_Pr,0x74);
  अगर((tempbh == 0xf6) || (tempbh == 0xc7)) अणु
     tempbh = SiS_GetCH701x(SiS_Pr,0x73);
     अगर(tempbh == 0xc8) अणु
        अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) वापस;
     पूर्ण अन्यथा अगर(tempbh == 0xdb) अणु
        अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) वापस;
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) वापस;
     पूर्ण अन्यथा अगर(tempbh == 0xde) अणु
        अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) वापस;
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->ChipType == SIS_740) tempbh = 0x0d;
  अन्यथा     			  tempbh = 0x0c;

  क्रम(i = 0; i < tempbh; i++) अणु
     SiS_SetCH701x(SiS_Pr, regtable[i], tableptr[i]);
  पूर्ण
  SiS_ChrontelPowerSequencing(SiS_Pr);
  tempbh = SiS_GetCH701x(SiS_Pr,0x1e);
  tempbh |= 0xc0;
  SiS_SetCH701x(SiS_Pr,0x1e,tempbh);

  अगर(SiS_Pr->ChipType == SIS_740) अणु
     tempbh = SiS_GetCH701x(SiS_Pr,0x1c);
     tempbh &= 0xfb;
     SiS_SetCH701x(SiS_Pr,0x1c,tempbh);
     SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2d,0x03);
     tempbh = SiS_GetCH701x(SiS_Pr,0x64);
     tempbh |= 0x40;
     SiS_SetCH701x(SiS_Pr,0x64,tempbh);
     tempbh = SiS_GetCH701x(SiS_Pr,0x03);
     tempbh &= 0x3f;
     SiS_SetCH701x(SiS_Pr,0x03,tempbh);
  पूर्ण
पूर्ण

अटल व्योम
SiS_ChrontelResetVSync(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित अक्षर temp, temp1;

  temp1 = SiS_GetCH701x(SiS_Pr,0x49);
  SiS_SetCH701x(SiS_Pr,0x49,0x3e);
  temp = SiS_GetCH701x(SiS_Pr,0x47);
  temp &= 0x7f;	/* Use बाह्यal VSYNC */
  SiS_SetCH701x(SiS_Pr,0x47,temp);
  SiS_LongDelay(SiS_Pr, 3);
  temp = SiS_GetCH701x(SiS_Pr,0x47);
  temp |= 0x80;	/* Use पूर्णांकernal VSYNC */
  SiS_SetCH701x(SiS_Pr,0x47,temp);
  SiS_SetCH701x(SiS_Pr,0x49,temp1);
पूर्ण

अटल व्योम
SiS_Chrontel701xOn(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु temp;

  अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
     अगर(SiS_Pr->ChipType == SIS_740) अणु
        temp = SiS_GetCH701x(SiS_Pr,0x1c);
        temp |= 0x04;	/* Invert XCLK phase */
        SiS_SetCH701x(SiS_Pr,0x1c,temp);
     पूर्ण
     अगर(SiS_IsYPbPr(SiS_Pr)) अणु
        temp = SiS_GetCH701x(SiS_Pr,0x01);
	temp &= 0x3f;
	temp |= 0x80;	/* Enable YPrPb (HDTV) */
	SiS_SetCH701x(SiS_Pr,0x01,temp);
     पूर्ण
     अगर(SiS_IsChScart(SiS_Pr)) अणु
        temp = SiS_GetCH701x(SiS_Pr,0x01);
	temp &= 0x3f;
	temp |= 0xc0;	/* Enable SCART + CVBS */
	SiS_SetCH701x(SiS_Pr,0x01,temp);
     पूर्ण
     अगर(SiS_Pr->ChipType == SIS_740) अणु
        SiS_ChrontelResetVSync(SiS_Pr);
        SiS_SetCH701x(SiS_Pr,0x49,0x20);   /* Enable TV path */
     पूर्ण अन्यथा अणु
        SiS_SetCH701x(SiS_Pr,0x49,0x20);   /* Enable TV path */
        temp = SiS_GetCH701x(SiS_Pr,0x49);
        अगर(SiS_IsYPbPr(SiS_Pr)) अणु
           temp = SiS_GetCH701x(SiS_Pr,0x73);
	   temp |= 0x60;
	   SiS_SetCH701x(SiS_Pr,0x73,temp);
        पूर्ण
        temp = SiS_GetCH701x(SiS_Pr,0x47);
        temp &= 0x7f;
        SiS_SetCH701x(SiS_Pr,0x47,temp);
        SiS_LongDelay(SiS_Pr, 2);
        temp = SiS_GetCH701x(SiS_Pr,0x47);
        temp |= 0x80;
        SiS_SetCH701x(SiS_Pr,0x47,temp);
     पूर्ण
  पूर्ण
पूर्ण

अटल व्योम
SiS_Chrontel701xOff(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु temp;

  /* Complete घातer करोwn of LVDS */
  अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
     अगर(SiS_Pr->ChipType == SIS_740) अणु
        SiS_LongDelay(SiS_Pr, 1);
	SiS_GenericDelay(SiS_Pr, 5887);
	SiS_SetCH701x(SiS_Pr,0x76,0xac);
	SiS_SetCH701x(SiS_Pr,0x66,0x00);
     पूर्ण अन्यथा अणु
        SiS_LongDelay(SiS_Pr, 2);
	temp = SiS_GetCH701x(SiS_Pr,0x76);
	temp &= 0xfc;
	SiS_SetCH701x(SiS_Pr,0x76,temp);
	SiS_SetCH701x(SiS_Pr,0x66,0x00);
     पूर्ण
  पूर्ण
पूर्ण

अटल व्योम
SiS_ChrontelResetDB(काष्ठा SiS_Private *SiS_Pr)
अणु
     अचिन्हित लघु temp;

     अगर(SiS_Pr->ChipType == SIS_740) अणु

        temp = SiS_GetCH701x(SiS_Pr,0x4a);  /* Version ID */
        temp &= 0x01;
        अगर(!temp) अणु

           अगर(SiS_WeHaveBacklightCtrl(SiS_Pr)) अणु
	      temp = SiS_GetCH701x(SiS_Pr,0x49);
	      SiS_SetCH701x(SiS_Pr,0x49,0x3e);
	   पूर्ण

	   /* Reset Chrontel 7019 datapath */
           SiS_SetCH701x(SiS_Pr,0x48,0x10);
           SiS_LongDelay(SiS_Pr, 1);
           SiS_SetCH701x(SiS_Pr,0x48,0x18);

	   अगर(SiS_WeHaveBacklightCtrl(SiS_Pr)) अणु
	      SiS_ChrontelResetVSync(SiS_Pr);
	      SiS_SetCH701x(SiS_Pr,0x49,temp);
	   पूर्ण

        पूर्ण अन्यथा अणु

	   /* Clear/set/clear GPIO */
           temp = SiS_GetCH701x(SiS_Pr,0x5c);
	   temp &= 0xef;
	   SiS_SetCH701x(SiS_Pr,0x5c,temp);
	   temp = SiS_GetCH701x(SiS_Pr,0x5c);
	   temp |= 0x10;
	   SiS_SetCH701x(SiS_Pr,0x5c,temp);
	   temp = SiS_GetCH701x(SiS_Pr,0x5c);
	   temp &= 0xef;
	   SiS_SetCH701x(SiS_Pr,0x5c,temp);
	   temp = SiS_GetCH701x(SiS_Pr,0x61);
	   अगर(!temp) अणु
	      SiS_SetCH701xForLCD(SiS_Pr);
	   पूर्ण
        पूर्ण

     पूर्ण अन्यथा अणु /* 650 */
        /* Reset Chrontel 7019 datapath */
        SiS_SetCH701x(SiS_Pr,0x48,0x10);
        SiS_LongDelay(SiS_Pr, 1);
        SiS_SetCH701x(SiS_Pr,0x48,0x18);
     पूर्ण
पूर्ण

अटल व्योम
SiS_ChrontelInitTVVSync(काष्ठा SiS_Private *SiS_Pr)
अणु
     अचिन्हित लघु temp;

     अगर(SiS_Pr->ChipType == SIS_740) अणु

        अगर(SiS_WeHaveBacklightCtrl(SiS_Pr)) अणु
           SiS_ChrontelResetVSync(SiS_Pr);
        पूर्ण

     पूर्ण अन्यथा अणु

        SiS_SetCH701x(SiS_Pr,0x76,0xaf);  /* Power up LVDS block */
        temp = SiS_GetCH701x(SiS_Pr,0x49);
        temp &= 1;
        अगर(temp != 1) अणु  /* TV block घातered? (0 = yes, 1 = no) */
	   temp = SiS_GetCH701x(SiS_Pr,0x47);
	   temp &= 0x70;
	   SiS_SetCH701x(SiS_Pr,0x47,temp);  /* enable VSYNC */
	   SiS_LongDelay(SiS_Pr, 3);
	   temp = SiS_GetCH701x(SiS_Pr,0x47);
	   temp |= 0x80;
	   SiS_SetCH701x(SiS_Pr,0x47,temp);  /* disable VSYNC */
        पूर्ण

     पूर्ण
पूर्ण

अटल व्योम
SiS_ChrontelDoSomething3(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
     अचिन्हित लघु temp,temp1;

     अगर(SiS_Pr->ChipType == SIS_740) अणु

        temp = SiS_GetCH701x(SiS_Pr,0x61);
        अगर(temp < 1) अणु
           temp++;
	   SiS_SetCH701x(SiS_Pr,0x61,temp);
        पूर्ण
        SiS_SetCH701x(SiS_Pr,0x66,0x45);  /* Panel घातer on */
        SiS_SetCH701x(SiS_Pr,0x76,0xaf);  /* All घातer on */
        SiS_LongDelay(SiS_Pr, 1);
        SiS_GenericDelay(SiS_Pr, 5887);

     पूर्ण अन्यथा अणु  /* 650 */

        temp1 = 0;
        temp = SiS_GetCH701x(SiS_Pr,0x61);
        अगर(temp < 2) अणु
           temp++;
	   SiS_SetCH701x(SiS_Pr,0x61,temp);
	   temp1 = 1;
        पूर्ण
        SiS_SetCH701x(SiS_Pr,0x76,0xac);
        temp = SiS_GetCH701x(SiS_Pr,0x66);
        temp |= 0x5f;
        SiS_SetCH701x(SiS_Pr,0x66,temp);
        अगर(ModeNo > 0x13) अणु
           अगर(SiS_WeHaveBacklightCtrl(SiS_Pr)) अणु
	      SiS_GenericDelay(SiS_Pr, 1023);
	   पूर्ण अन्यथा अणु
	      SiS_GenericDelay(SiS_Pr, 767);
	   पूर्ण
        पूर्ण अन्यथा अणु
           अगर(!temp1)
	      SiS_GenericDelay(SiS_Pr, 767);
        पूर्ण
        temp = SiS_GetCH701x(SiS_Pr,0x76);
        temp |= 0x03;
        SiS_SetCH701x(SiS_Pr,0x76,temp);
        temp = SiS_GetCH701x(SiS_Pr,0x66);
        temp &= 0x7f;
        SiS_SetCH701x(SiS_Pr,0x66,temp);
        SiS_LongDelay(SiS_Pr, 1);

     पूर्ण
पूर्ण

अटल व्योम
SiS_ChrontelDoSomething2(काष्ठा SiS_Private *SiS_Pr)
अणु
     अचिन्हित लघु temp;

     SiS_LongDelay(SiS_Pr, 1);

     करो अणु
       temp = SiS_GetCH701x(SiS_Pr,0x66);
       temp &= 0x04;  /* PLL stable? -> bail out */
       अगर(temp == 0x04) अवरोध;

       अगर(SiS_Pr->ChipType == SIS_740) अणु
          /* Power करोwn LVDS output, PLL normal operation */
          SiS_SetCH701x(SiS_Pr,0x76,0xac);
       पूर्ण

       SiS_SetCH701xForLCD(SiS_Pr);

       temp = SiS_GetCH701x(SiS_Pr,0x76);
       temp &= 0xfb;  /* Reset PLL */
       SiS_SetCH701x(SiS_Pr,0x76,temp);
       SiS_LongDelay(SiS_Pr, 2);
       temp = SiS_GetCH701x(SiS_Pr,0x76);
       temp |= 0x04;  /* PLL normal operation */
       SiS_SetCH701x(SiS_Pr,0x76,temp);
       अगर(SiS_Pr->ChipType == SIS_740) अणु
          SiS_SetCH701x(SiS_Pr,0x78,0xe0);	/* PLL loop filter */
       पूर्ण अन्यथा अणु
          SiS_SetCH701x(SiS_Pr,0x78,0x60);
       पूर्ण
       SiS_LongDelay(SiS_Pr, 2);
    पूर्ण जबतक(0);

    SiS_SetCH701x(SiS_Pr,0x77,0x00);  /* MV? */
पूर्ण

अटल व्योम
SiS_ChrontelDoSomething1(काष्ठा SiS_Private *SiS_Pr)
अणु
     अचिन्हित लघु temp;

     temp = SiS_GetCH701x(SiS_Pr,0x03);
     temp |= 0x80;	/* Set datapath 1 to TV   */
     temp &= 0xbf;	/* Set datapath 2 to LVDS */
     SiS_SetCH701x(SiS_Pr,0x03,temp);

     अगर(SiS_Pr->ChipType == SIS_740) अणु

        temp = SiS_GetCH701x(SiS_Pr,0x1c);
        temp &= 0xfb;	/* Normal XCLK phase */
        SiS_SetCH701x(SiS_Pr,0x1c,temp);

        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2d,0x03);

        temp = SiS_GetCH701x(SiS_Pr,0x64);
        temp |= 0x40;	/* ? Bit not defined */
        SiS_SetCH701x(SiS_Pr,0x64,temp);

        temp = SiS_GetCH701x(SiS_Pr,0x03);
        temp &= 0x3f;	/* D1 input to both LVDS and TV */
        SiS_SetCH701x(SiS_Pr,0x03,temp);

	अगर(SiS_Pr->SiS_CustomT == CUT_ASUSL3000D) अणु
	   SiS_SetCH701x(SiS_Pr,0x63,0x40); /* LVDS off */
	   SiS_LongDelay(SiS_Pr, 1);
	   SiS_SetCH701x(SiS_Pr,0x63,0x00); /* LVDS on */
	   SiS_ChrontelResetDB(SiS_Pr);
	   SiS_ChrontelDoSomething2(SiS_Pr);
	   SiS_ChrontelDoSomething3(SiS_Pr, 0);
	पूर्ण अन्यथा अणु
           temp = SiS_GetCH701x(SiS_Pr,0x66);
           अगर(temp != 0x45) अणु
              SiS_ChrontelResetDB(SiS_Pr);
              SiS_ChrontelDoSomething2(SiS_Pr);
              SiS_ChrontelDoSomething3(SiS_Pr, 0);
           पूर्ण
	पूर्ण

     पूर्ण अन्यथा अणु /* 650 */

        SiS_ChrontelResetDB(SiS_Pr);
        SiS_ChrontelDoSomething2(SiS_Pr);
        temp = SiS_GetReg(SiS_Pr->SiS_P3d4,0x34);
        SiS_ChrontelDoSomething3(SiS_Pr,temp);
        SiS_SetCH701x(SiS_Pr,0x76,0xaf);  /* All घातer on, LVDS normal operation */

     पूर्ण

पूर्ण
#पूर्ण_अगर  /* 315 series  */

/*********************************************/
/*      MAIN: SET CRT2 REGISTER GROUP        */
/*********************************************/

bool
SiS_SetCRT2Group(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
#अगर_घोषित CONFIG_FB_SIS_300
   अचिन्हित अक्षर  *ROMAddr  = SiS_Pr->VirtualRomBase;
#पूर्ण_अगर
   अचिन्हित लघु ModeIdIndex, RefreshRateTableIndex;

   SiS_Pr->SiS_SetFlag |= ProgrammingCRT2;

   अगर(!SiS_Pr->UseCustomMode) अणु
      SiS_SearchModeID(SiS_Pr, &ModeNo, &ModeIdIndex);
   पूर्ण अन्यथा अणु
      ModeIdIndex = 0;
   पूर्ण

   /* Used क्रम shअगरting CR33 */
   SiS_Pr->SiS_SelectCRT2Rate = 4;

   SiS_UnLockCRT2(SiS_Pr);

   RefreshRateTableIndex = SiS_GetRatePtr(SiS_Pr, ModeNo, ModeIdIndex);

   SiS_SaveCRT2Info(SiS_Pr,ModeNo);

   अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
      SiS_DisableBridge(SiS_Pr);
      अगर((SiS_Pr->SiS_IF_DEF_LVDS == 1) && (SiS_Pr->ChipType == SIS_730)) अणु
         SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,0x80);
      पूर्ण
      SiS_SetCRT2ModeRegs(SiS_Pr, ModeNo, ModeIdIndex);
   पूर्ण

   अगर(SiS_Pr->SiS_VBInfo & DisableCRT2Display) अणु
      SiS_LockCRT2(SiS_Pr);
      SiS_DisplayOn(SiS_Pr);
      वापस true;
   पूर्ण

   SiS_GetCRT2Data(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);

   /* Set up Panel Link क्रम LVDS and LCDA */
   SiS_Pr->SiS_LCDHDES = SiS_Pr->SiS_LCDVDES = 0;
   अगर( (SiS_Pr->SiS_IF_DEF_LVDS == 1) ||
       ((SiS_Pr->SiS_VBType & VB_NoLCD) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) ||
       ((SiS_Pr->ChipType >= SIS_315H) && (SiS_Pr->SiS_VBType & VB_SIS30xBLV)) ) अणु
      SiS_GetLVDSDesData(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
   पूर्ण

   अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
      SiS_SetGroup1(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
   पूर्ण

   अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

      अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु

	 SiS_SetGroup2(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
#अगर_घोषित CONFIG_FB_SIS_315
	 SiS_SetGroup2_C_ELV(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
#पूर्ण_अगर
	 SiS_SetGroup3(SiS_Pr, ModeNo, ModeIdIndex);
	 SiS_SetGroup4(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
#अगर_घोषित CONFIG_FB_SIS_315
	 SiS_SetGroup4_C_ELV(SiS_Pr, ModeNo, ModeIdIndex);
#पूर्ण_अगर
	 SiS_SetGroup5(SiS_Pr, ModeNo, ModeIdIndex);

	 SiS_SetCRT2Sync(SiS_Pr, ModeNo, RefreshRateTableIndex);

	 /* For 301BDH (Panel link initialization): */
	 अगर((SiS_Pr->SiS_VBType & VB_NoLCD) && (SiS_Pr->SiS_VBInfo & SetCRT2ToLCD)) अणु

	    अगर(!((SiS_Pr->SiS_SetFlag & SetDOSMode) && ((ModeNo == 0x03) || (ModeNo == 0x10)))) अणु
	       अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) अणु
		  SiS_ModCRT1CRTC(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	       पूर्ण
            पूर्ण
	    SiS_SetCRT2ECLK(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	 पूर्ण
      पूर्ण

   पूर्ण अन्यथा अणु

      SiS_SetCRT2Sync(SiS_Pr, ModeNo, RefreshRateTableIndex);

      SiS_ModCRT1CRTC(SiS_Pr,ModeNo,ModeIdIndex,RefreshRateTableIndex);

      SiS_SetCRT2ECLK(SiS_Pr,ModeNo,ModeIdIndex,RefreshRateTableIndex);

      अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
	 अगर(SiS_Pr->SiS_IF_DEF_CH70xx != 0) अणु
	    अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
	       अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 2) अणु
#अगर_घोषित CONFIG_FB_SIS_315
		  SiS_SetCH701xForLCD(SiS_Pr);
#पूर्ण_अगर
	       पूर्ण
	    पूर्ण
	    अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	       SiS_SetCHTVReg(SiS_Pr,ModeNo,ModeIdIndex,RefreshRateTableIndex);
	    पूर्ण
	 पूर्ण
      पूर्ण

   पूर्ण

#अगर_घोषित CONFIG_FB_SIS_300
   अगर(SiS_Pr->ChipType < SIS_315H) अणु
      अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
	 अगर(SiS_Pr->SiS_UseOEM) अणु
	    अगर((SiS_Pr->SiS_UseROM) && (SiS_Pr->SiS_UseOEM == -1)) अणु
	       अगर((ROMAddr[0x233] == 0x12) && (ROMAddr[0x234] == 0x34)) अणु
		  SiS_OEM300Setting(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	       पूर्ण
	    पूर्ण अन्यथा अणु
	       SiS_OEM300Setting(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	    पूर्ण
	 पूर्ण
	 अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
	    अगर((SiS_Pr->SiS_CustomT == CUT_BARCO1366) ||
	       (SiS_Pr->SiS_CustomT == CUT_BARCO1024)) अणु
	       SetOEMLCDData2(SiS_Pr, ModeNo, ModeIdIndex,RefreshRateTableIndex);
	    पूर्ण
	    SiS_DisplayOn(SiS_Pr);
         पूर्ण
      पूर्ण
   पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_FB_SIS_315
   अगर(SiS_Pr->ChipType >= SIS_315H) अणु
      अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
	 अगर(SiS_Pr->ChipType < SIS_661) अणु
	    SiS_FinalizeLCD(SiS_Pr, ModeNo, ModeIdIndex);
	    SiS_OEM310Setting(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	 पूर्ण अन्यथा अणु
	    SiS_OEM661Setting(SiS_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex);
	 पूर्ण
	 SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x01,0x40);
      पूर्ण
   पूर्ण
#पूर्ण_अगर

   अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
      SiS_EnableBridge(SiS_Pr);
   पूर्ण

   SiS_DisplayOn(SiS_Pr);

   अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 1) अणु
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
	 /* Disable LCD panel when using TV */
	 SiS_SetRegSR11ANDOR(SiS_Pr,0xFF,0x0C);
      पूर्ण अन्यथा अणु
	 /* Disable TV when using LCD */
	 SiS_SetCH70xxANDOR(SiS_Pr,0x0e,0x01,0xf8);
      पूर्ण
   पूर्ण

   अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
      SiS_LockCRT2(SiS_Pr);
   पूर्ण

   वापस true;
पूर्ण


/*********************************************/
/*     ENABLE/DISABLE LCD BACKLIGHT (SIS)    */
/*********************************************/

व्योम
SiS_SiS30xBLOn(काष्ठा SiS_Private *SiS_Pr)
अणु
  /* Switch on LCD backlight on SiS30xLV */
  SiS_DDC2Delay(SiS_Pr,0xff00);
  अगर(!(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x02)) अणु
     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x02);
     SiS_WaitVBRetrace(SiS_Pr);
  पूर्ण
  अगर(!(SiS_GetReg(SiS_Pr->SiS_Part4Port,0x26) & 0x01)) अणु
     SiS_SetRegOR(SiS_Pr->SiS_Part4Port,0x26,0x01);
  पूर्ण
पूर्ण

व्योम
SiS_SiS30xBLOff(काष्ठा SiS_Private *SiS_Pr)
अणु
  /* Switch off LCD backlight on SiS30xLV */
  SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFE);
  SiS_DDC2Delay(SiS_Pr,0xff00);
पूर्ण

/*********************************************/
/*          DDC RELATED FUNCTIONS            */
/*********************************************/

अटल व्योम
SiS_SetupDDCN(काष्ठा SiS_Private *SiS_Pr)
अणु
  SiS_Pr->SiS_DDC_NData = ~SiS_Pr->SiS_DDC_Data;
  SiS_Pr->SiS_DDC_NClk  = ~SiS_Pr->SiS_DDC_Clk;
  अगर((SiS_Pr->SiS_DDC_Index == 0x11) && (SiS_Pr->SiS_SensibleSR11)) अणु
     SiS_Pr->SiS_DDC_NData &= 0x0f;
     SiS_Pr->SiS_DDC_NClk  &= 0x0f;
  पूर्ण
पूर्ण

#अगर_घोषित CONFIG_FB_SIS_300
अटल अचिन्हित अक्षर *
SiS_SetTrumpBlockLoop(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर *dataptr)
अणु
  पूर्णांक i, j, num;
  अचिन्हित लघु tempah,temp;
  अचिन्हित अक्षर *mydataptr;

  क्रम(i=0; i<20; i++) अणु				/* Do 20 attempts to ग_लिखो */
     mydataptr = dataptr;
     num = *mydataptr++;
     अगर(!num) वापस mydataptr;
     अगर(i) अणु
        SiS_SetStop(SiS_Pr);
	SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT * 2);
     पूर्ण
     अगर(SiS_SetStart(SiS_Pr)) जारी;		/* Set start condition */
     tempah = SiS_Pr->SiS_DDC_DeviceAddr;
     temp = SiS_WriteDDC2Data(SiS_Pr,tempah);	/* Write DAB (S0=0=ग_लिखो) */
     अगर(temp) जारी;				/*    (ERROR: no ack) */
     tempah = *mydataptr++;
     temp = SiS_WriteDDC2Data(SiS_Pr,tempah);	/* Write रेजिस्टर number */
     अगर(temp) जारी;				/*    (ERROR: no ack) */
     क्रम(j=0; j<num; j++) अणु
        tempah = *mydataptr++;
        temp = SiS_WriteDDC2Data(SiS_Pr,tempah);/* Write DAB (S0=0=ग_लिखो) */
	अगर(temp) अवरोध;
     पूर्ण
     अगर(temp) जारी;
     अगर(SiS_SetStop(SiS_Pr)) जारी;
     वापस mydataptr;
  पूर्ण
  वापस शून्य;
पूर्ण

अटल bool
SiS_SetTrumpionBlock(काष्ठा SiS_Private *SiS_Pr, अचिन्हित अक्षर *dataptr)
अणु
  SiS_Pr->SiS_DDC_DeviceAddr = 0xF0;  		/* DAB (Device Address Byte) */
  SiS_Pr->SiS_DDC_Index = 0x11;			/* Bit 0 = SC;  Bit 1 = SD */
  SiS_Pr->SiS_DDC_Data  = 0x02;			/* Biपंचांगask in IndexReg क्रम Data */
  SiS_Pr->SiS_DDC_Clk   = 0x01;			/* Biपंचांगask in IndexReg क्रम Clk */
  SiS_SetupDDCN(SiS_Pr);

  SiS_SetSwitchDDC2(SiS_Pr);

  जबतक(*dataptr) अणु
     dataptr = SiS_SetTrumpBlockLoop(SiS_Pr, dataptr);
     अगर(!dataptr) वापस false;
  पूर्ण
  वापस true;
पूर्ण
#पूर्ण_अगर

/* The Chrontel 700x is connected to the 630/730 via
 * the 630/730's DDC/I2C port.
 *
 * On 630(S)T chipset, the index changed from 0x11 to
 * 0x0a, possibly क्रम working around the DDC problems
 */

अटल bool
SiS_SetChReg(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg, अचिन्हित अक्षर val, अचिन्हित लघु myor)
अणु
  अचिन्हित लघु temp, i;

  क्रम(i=0; i<20; i++) अणु				/* Do 20 attempts to ग_लिखो */
     अगर(i) अणु
	SiS_SetStop(SiS_Pr);
	SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT * 4);
     पूर्ण
     अगर(SiS_SetStart(SiS_Pr)) जारी;					/* Set start condition */
     temp = SiS_WriteDDC2Data(SiS_Pr, SiS_Pr->SiS_DDC_DeviceAddr);	/* Write DAB (S0=0=ग_लिखो) */
     अगर(temp) जारी;							/*    (ERROR: no ack) */
     temp = SiS_WriteDDC2Data(SiS_Pr, (reg | myor));			/* Write RAB (700x: set bit 7, see datasheet) */
     अगर(temp) जारी;							/*    (ERROR: no ack) */
     temp = SiS_WriteDDC2Data(SiS_Pr, val);				/* Write data */
     अगर(temp) जारी;							/*    (ERROR: no ack) */
     अगर(SiS_SetStop(SiS_Pr)) जारी;					/* Set stop condition */
     SiS_Pr->SiS_ChrontelInit = 1;
     वापस true;
  पूर्ण
  वापस false;
पूर्ण

/* Write to Chrontel 700x */
व्योम
SiS_SetCH700x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg, अचिन्हित अक्षर val)
अणु
  SiS_Pr->SiS_DDC_DeviceAddr = 0xEA;  		/* DAB (Device Address Byte) */

  SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT);

  अगर(!(SiS_Pr->SiS_ChrontelInit)) अणु
     SiS_Pr->SiS_DDC_Index = 0x11;		/* Bit 0 = SC;  Bit 1 = SD */
     SiS_Pr->SiS_DDC_Data  = 0x02;		/* Biपंचांगask in IndexReg क्रम Data */
     SiS_Pr->SiS_DDC_Clk   = 0x01;		/* Biपंचांगask in IndexReg क्रम Clk */
     SiS_SetupDDCN(SiS_Pr);
  पूर्ण

  अगर( (!(SiS_SetChReg(SiS_Pr, reg, val, 0x80))) &&
      (!(SiS_Pr->SiS_ChrontelInit)) ) अणु
     SiS_Pr->SiS_DDC_Index = 0x0a;
     SiS_Pr->SiS_DDC_Data  = 0x80;
     SiS_Pr->SiS_DDC_Clk   = 0x40;
     SiS_SetupDDCN(SiS_Pr);

     SiS_SetChReg(SiS_Pr, reg, val, 0x80);
  पूर्ण
पूर्ण

/* Write to Chrontel 701x */
/* Parameter is [Data (S15-S8) | Register no (S7-S0)] */
व्योम
SiS_SetCH701x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg, अचिन्हित अक्षर val)
अणु
  SiS_Pr->SiS_DDC_Index = 0x11;			/* Bit 0 = SC;  Bit 1 = SD */
  SiS_Pr->SiS_DDC_Data  = 0x08;			/* Biपंचांगask in IndexReg क्रम Data */
  SiS_Pr->SiS_DDC_Clk   = 0x04;			/* Biपंचांगask in IndexReg क्रम Clk */
  SiS_SetupDDCN(SiS_Pr);
  SiS_Pr->SiS_DDC_DeviceAddr = 0xEA;		/* DAB (Device Address Byte) */
  SiS_SetChReg(SiS_Pr, reg, val, 0);
पूर्ण

अटल
व्योम
SiS_SetCH70xx(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg, अचिन्हित अक्षर val)
अणु
  अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 1)
     SiS_SetCH700x(SiS_Pr, reg, val);
  अन्यथा
     SiS_SetCH701x(SiS_Pr, reg, val);
पूर्ण

अटल अचिन्हित लघु
SiS_GetChReg(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु myor)
अणु
  अचिन्हित लघु tempah, temp, i;

  क्रम(i=0; i<20; i++) अणु				/* Do 20 attempts to पढ़ो */
     अगर(i) अणु
	SiS_SetStop(SiS_Pr);
	SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT * 4);
     पूर्ण
     अगर(SiS_SetStart(SiS_Pr)) जारी;					/* Set start condition */
     temp = SiS_WriteDDC2Data(SiS_Pr,SiS_Pr->SiS_DDC_DeviceAddr);	/* Write DAB (S0=0=ग_लिखो) */
     अगर(temp) जारी;							/*        (ERROR: no ack) */
     temp = SiS_WriteDDC2Data(SiS_Pr,SiS_Pr->SiS_DDC_ReadAddr | myor);	/* Write RAB (700x: | 0x80) */
     अगर(temp) जारी;							/*        (ERROR: no ack) */
     अगर (SiS_SetStart(SiS_Pr)) जारी;				/* Re-start */
     temp = SiS_WriteDDC2Data(SiS_Pr,SiS_Pr->SiS_DDC_DeviceAddr | 0x01);/* DAB (S0=1=पढ़ो) */
     अगर(temp) जारी;							/*        (ERROR: no ack) */
     tempah = SiS_ReadDDC2Data(SiS_Pr);					/* Read byte */
     अगर(SiS_SetStop(SiS_Pr)) जारी;					/* Stop condition */
     SiS_Pr->SiS_ChrontelInit = 1;
     वापस tempah;
  पूर्ण
  वापस 0xFFFF;
पूर्ण

/* Read from Chrontel 700x */
/* Parameter is [Register no (S7-S0)] */
अचिन्हित लघु
SiS_GetCH700x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempbx)
अणु
  अचिन्हित लघु result;

  SiS_Pr->SiS_DDC_DeviceAddr = 0xEA;		/* DAB */

  SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT);

  अगर(!(SiS_Pr->SiS_ChrontelInit)) अणु
     SiS_Pr->SiS_DDC_Index = 0x11;		/* Bit 0 = SC;  Bit 1 = SD */
     SiS_Pr->SiS_DDC_Data  = 0x02;		/* Biपंचांगask in IndexReg क्रम Data */
     SiS_Pr->SiS_DDC_Clk   = 0x01;		/* Biपंचांगask in IndexReg क्रम Clk */
     SiS_SetupDDCN(SiS_Pr);
  पूर्ण

  SiS_Pr->SiS_DDC_ReadAddr = tempbx;

  अगर( ((result = SiS_GetChReg(SiS_Pr,0x80)) == 0xFFFF) &&
      (!SiS_Pr->SiS_ChrontelInit) ) अणु

     SiS_Pr->SiS_DDC_Index = 0x0a;
     SiS_Pr->SiS_DDC_Data  = 0x80;
     SiS_Pr->SiS_DDC_Clk   = 0x40;
     SiS_SetupDDCN(SiS_Pr);

     result = SiS_GetChReg(SiS_Pr,0x80);
  पूर्ण
  वापस result;
पूर्ण

/* Read from Chrontel 701x */
/* Parameter is [Register no (S7-S0)] */
अचिन्हित लघु
SiS_GetCH701x(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempbx)
अणु
  SiS_Pr->SiS_DDC_Index = 0x11;			/* Bit 0 = SC;  Bit 1 = SD */
  SiS_Pr->SiS_DDC_Data  = 0x08;			/* Biपंचांगask in IndexReg क्रम Data */
  SiS_Pr->SiS_DDC_Clk   = 0x04;			/* Biपंचांगask in IndexReg क्रम Clk */
  SiS_SetupDDCN(SiS_Pr);
  SiS_Pr->SiS_DDC_DeviceAddr = 0xEA;		/* DAB */

  SiS_Pr->SiS_DDC_ReadAddr = tempbx;

  वापस SiS_GetChReg(SiS_Pr,0);
पूर्ण

/* Read from Chrontel 70xx */
/* Parameter is [Register no (S7-S0)] */
अटल
अचिन्हित लघु
SiS_GetCH70xx(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempbx)
अणु
  अगर(SiS_Pr->SiS_IF_DEF_CH70xx == 1)
     वापस SiS_GetCH700x(SiS_Pr, tempbx);
  अन्यथा
     वापस SiS_GetCH701x(SiS_Pr, tempbx);
पूर्ण

व्योम
SiS_SetCH70xxANDOR(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु reg,
		अचिन्हित अक्षर myor, अचिन्हित लघु myand)
अणु
  अचिन्हित लघु tempbl;

  tempbl = (SiS_GetCH70xx(SiS_Pr, (reg & 0xFF)) & myand) | myor;
  SiS_SetCH70xx(SiS_Pr, reg, tempbl);
पूर्ण

/* Our own DDC functions */
अटल
अचिन्हित लघु
SiS_InitDDCRegs(काष्ठा SiS_Private *SiS_Pr, अचिन्हित पूर्णांक VBFlags, पूर्णांक VGAEngine,
                अचिन्हित लघु adaptnum, अचिन्हित लघु DDCdatatype, bool checkcr32,
		अचिन्हित पूर्णांक VBFlags2)
अणु
     अचिन्हित अक्षर ddcdtype[] = अणु 0xa0, 0xa0, 0xa0, 0xa2, 0xa6 पूर्ण;
     अचिन्हित अक्षर flag, cr32;
     अचिन्हित लघु        temp = 0, myadaptnum = adaptnum;

     अगर(adaptnum != 0) अणु
	अगर(!(VBFlags2 & VB2_SISTMDSBRIDGE)) वापस 0xFFFF;
	अगर((VBFlags2 & VB2_30xBDH) && (adaptnum == 1)) वापस 0xFFFF;
     पूर्ण

     /* adapternum क्रम SiS bridges: 0 = CRT1, 1 = LCD, 2 = VGA2 */

     SiS_Pr->SiS_ChrontelInit = 0;   /* क्रमce re-detection! */

     SiS_Pr->SiS_DDC_SecAddr = 0;
     SiS_Pr->SiS_DDC_DeviceAddr = ddcdtype[DDCdatatype];
     SiS_Pr->SiS_DDC_Port = SiS_Pr->SiS_P3c4;
     SiS_Pr->SiS_DDC_Index = 0x11;
     flag = 0xff;

     cr32 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x32);

#अगर 0
     अगर(VBFlags2 & VB2_SISBRIDGE) अणु
	अगर(myadaptnum == 0) अणु
	   अगर(!(cr32 & 0x20)) अणु
	      myadaptnum = 2;
	      अगर(!(cr32 & 0x10)) अणु
	         myadaptnum = 1;
		 अगर(!(cr32 & 0x08)) अणु
		    myadaptnum = 0;
		 पूर्ण
	      पूर्ण
	   पूर्ण
        पूर्ण
     पूर्ण
#पूर्ण_अगर

     अगर(VGAEngine == SIS_300_VGA) अणु		/* 300 series */

        अगर(myadaptnum != 0) अणु
	   flag = 0;
	   अगर(VBFlags2 & VB2_SISBRIDGE) अणु
	      SiS_Pr->SiS_DDC_Port = SiS_Pr->SiS_Part4Port;
              SiS_Pr->SiS_DDC_Index = 0x0f;
	   पूर्ण
        पूर्ण

	अगर(!(VBFlags2 & VB2_301)) अणु
	   अगर((cr32 & 0x80) && (checkcr32)) अणु
              अगर(myadaptnum >= 1) अणु
	         अगर(!(cr32 & 0x08)) अणु
		     myadaptnum = 1;
		     अगर(!(cr32 & 0x10)) वापस 0xFFFF;
                 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण

	temp = 4 - (myadaptnum * 2);
	अगर(flag) temp = 0;

     पूर्ण अन्यथा अणु						/* 315/330 series */

	/* here we simplअगरy: 0 = CRT1, 1 = CRT2 (VGA, LCD) */

	अगर(VBFlags2 & VB2_SISBRIDGE) अणु
	   अगर(myadaptnum == 2) अणु
	      myadaptnum = 1;
	   पूर्ण
	पूर्ण

        अगर(myadaptnum == 1) अणु
	   flag = 0;
	   अगर(VBFlags2 & VB2_SISBRIDGE) अणु
	      SiS_Pr->SiS_DDC_Port = SiS_Pr->SiS_Part4Port;
              SiS_Pr->SiS_DDC_Index = 0x0f;
	   पूर्ण
        पूर्ण

        अगर((cr32 & 0x80) && (checkcr32)) अणु
           अगर(myadaptnum >= 1) अणु
	      अगर(!(cr32 & 0x08)) अणु
	         myadaptnum = 1;
		 अगर(!(cr32 & 0x10)) वापस 0xFFFF;
	      पूर्ण
	   पूर्ण
        पूर्ण

        temp = myadaptnum;
        अगर(myadaptnum == 1) अणु
           temp = 0;
	   अगर(VBFlags2 & VB2_LVDS) flag = 0xff;
        पूर्ण

	अगर(flag) temp = 0;
    पूर्ण

    SiS_Pr->SiS_DDC_Data = 0x02 << temp;
    SiS_Pr->SiS_DDC_Clk  = 0x01 << temp;

    SiS_SetupDDCN(SiS_Pr);

    वापस 0;
पूर्ण

अटल अचिन्हित लघु
SiS_WriteDABDDC(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_SetStart(SiS_Pr)) वापस 0xFFFF;
   अगर(SiS_WriteDDC2Data(SiS_Pr, SiS_Pr->SiS_DDC_DeviceAddr)) अणु
      वापस 0xFFFF;
   पूर्ण
   अगर(SiS_WriteDDC2Data(SiS_Pr, SiS_Pr->SiS_DDC_SecAddr)) अणु
      वापस 0xFFFF;
   पूर्ण
   वापस 0;
पूर्ण

अटल अचिन्हित लघु
SiS_PrepareReadDDC(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_SetStart(SiS_Pr)) वापस 0xFFFF;
   अगर(SiS_WriteDDC2Data(SiS_Pr, (SiS_Pr->SiS_DDC_DeviceAddr | 0x01))) अणु
      वापस 0xFFFF;
   पूर्ण
   वापस 0;
पूर्ण

अटल अचिन्हित लघु
SiS_PrepareDDC(काष्ठा SiS_Private *SiS_Pr)
अणु
   अगर(SiS_WriteDABDDC(SiS_Pr)) SiS_WriteDABDDC(SiS_Pr);
   अगर(SiS_PrepareReadDDC(SiS_Pr)) वापस (SiS_PrepareReadDDC(SiS_Pr));
   वापस 0;
पूर्ण

अटल व्योम
SiS_SendACK(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु yesno)
अणु
   SiS_SetSCLKLow(SiS_Pr);
   अगर(yesno) अणु
      SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		      SiS_Pr->SiS_DDC_Index,
		      SiS_Pr->SiS_DDC_NData,
		      SiS_Pr->SiS_DDC_Data);
   पूर्ण अन्यथा अणु
      SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		      SiS_Pr->SiS_DDC_Index,
		      SiS_Pr->SiS_DDC_NData,
		      0);
   पूर्ण
   SiS_SetSCLKHigh(SiS_Pr);
पूर्ण

अटल अचिन्हित लघु
SiS_DoProbeDDC(काष्ठा SiS_Private *SiS_Pr)
अणु
    अचिन्हित अक्षर mask, value;
    अचिन्हित लघु  temp, ret=0;
    bool failed = false;

    SiS_SetSwitchDDC2(SiS_Pr);
    अगर(SiS_PrepareDDC(SiS_Pr)) अणु
         SiS_SetStop(SiS_Pr);
         वापस 0xFFFF;
    पूर्ण
    mask = 0xf0;
    value = 0x20;
    अगर(SiS_Pr->SiS_DDC_DeviceAddr == 0xa0) अणु
       temp = (अचिन्हित अक्षर)SiS_ReadDDC2Data(SiS_Pr);
       SiS_SendACK(SiS_Pr, 0);
       अगर(temp == 0) अणु
           mask = 0xff;
	   value = 0xff;
       पूर्ण अन्यथा अणु
           failed = true;
	   ret = 0xFFFF;
       पूर्ण
    पूर्ण
    अगर(!failed) अणु
       temp = (अचिन्हित अक्षर)SiS_ReadDDC2Data(SiS_Pr);
       SiS_SendACK(SiS_Pr, 1);
       temp &= mask;
       अगर(temp == value) ret = 0;
       अन्यथा अणु
          ret = 0xFFFF;
          अगर(SiS_Pr->SiS_DDC_DeviceAddr == 0xa0) अणु
             अगर(temp == 0x30) ret = 0;
          पूर्ण
       पूर्ण
    पूर्ण
    SiS_SetStop(SiS_Pr);
    वापस ret;
पूर्ण

अटल
अचिन्हित लघु
SiS_ProbeDDC(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित लघु flag;

   flag = 0x180;
   SiS_Pr->SiS_DDC_DeviceAddr = 0xa0;
   अगर(!(SiS_DoProbeDDC(SiS_Pr))) flag |= 0x02;
   SiS_Pr->SiS_DDC_DeviceAddr = 0xa2;
   अगर(!(SiS_DoProbeDDC(SiS_Pr))) flag |= 0x08;
   SiS_Pr->SiS_DDC_DeviceAddr = 0xa6;
   अगर(!(SiS_DoProbeDDC(SiS_Pr))) flag |= 0x10;
   अगर(!(flag & 0x1a)) flag = 0;
   वापस flag;
पूर्ण

अटल
अचिन्हित लघु
SiS_ReadDDC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु DDCdatatype, अचिन्हित अक्षर *buffer)
अणु
   अचिन्हित लघु flag, length, i;
   अचिन्हित अक्षर chksum,gotcha;

   अगर(DDCdatatype > 4) वापस 0xFFFF;

   flag = 0;
   SiS_SetSwitchDDC2(SiS_Pr);
   अगर(!(SiS_PrepareDDC(SiS_Pr))) अणु
      length = 127;
      अगर(DDCdatatype != 1) length = 255;
      chksum = 0;
      gotcha = 0;
      क्रम(i=0; i<length; i++) अणु
	 buffer[i] = (अचिन्हित अक्षर)SiS_ReadDDC2Data(SiS_Pr);
	 chksum += buffer[i];
	 gotcha |= buffer[i];
	 SiS_SendACK(SiS_Pr, 0);
      पूर्ण
      buffer[i] = (अचिन्हित अक्षर)SiS_ReadDDC2Data(SiS_Pr);
      chksum += buffer[i];
      SiS_SendACK(SiS_Pr, 1);
      अगर(gotcha) flag = (अचिन्हित लघु)chksum;
      अन्यथा flag = 0xFFFF;
   पूर्ण अन्यथा अणु
      flag = 0xFFFF;
   पूर्ण
   SiS_SetStop(SiS_Pr);
   वापस flag;
पूर्ण

/* Our निजी DDC functions

   It complies somewhat with the corresponding VESA function
   in arguments and वापस values.

   Since this is probably called beक्रमe the mode is changed,
   we use our pre-detected pSiS-values instead of SiS_Pr as
   regards chipset and video bridge type.

   Arguments:
       adaptnum: 0=CRT1(analog), 1=CRT2/LCD(digital), 2=CRT2/VGA2(analog)
                 CRT2 DDC is only supported on SiS301, 301B, 301C, 302B.
		 LCDA is CRT1, but DDC is पढ़ो from CRT2 port.
       DDCdatatype: 0=Probe, 1=EDID, 2=EDID+VDIF, 3=EDID V2 (P&D), 4=EDID V2 (FPDI-2)
       buffer: ptr to 256 data bytes which will be filled with पढ़ो data.

   Returns 0xFFFF अगर error, otherwise
       अगर DDCdatatype > 0:  Returns 0 अगर पढ़ोing OK (included a correct checksum)
       अगर DDCdatatype = 0:  Returns supported DDC modes

 */
अचिन्हित लघु
SiS_HandleDDC(काष्ठा SiS_Private *SiS_Pr, अचिन्हित पूर्णांक VBFlags, पूर्णांक VGAEngine,
              अचिन्हित लघु adaptnum, अचिन्हित लघु DDCdatatype, अचिन्हित अक्षर *buffer,
	      अचिन्हित पूर्णांक VBFlags2)
अणु
   अचिन्हित अक्षर  sr1f, cr17=1;
   अचिन्हित लघु result;

   अगर(adaptnum > 2)
      वापस 0xFFFF;

   अगर(DDCdatatype > 4)
      वापस 0xFFFF;

   अगर((!(VBFlags2 & VB2_VIDEOBRIDGE)) && (adaptnum > 0))
      वापस 0xFFFF;

   अगर(SiS_InitDDCRegs(SiS_Pr, VBFlags, VGAEngine, adaptnum, DDCdatatype, false, VBFlags2) == 0xFFFF)
      वापस 0xFFFF;

   sr1f = SiS_GetReg(SiS_Pr->SiS_P3c4,0x1f);
   SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x1f,0x3f,0x04);
   अगर(VGAEngine == SIS_300_VGA) अणु
      cr17 = SiS_GetReg(SiS_Pr->SiS_P3d4,0x17) & 0x80;
      अगर(!cr17) अणु
         SiS_SetRegOR(SiS_Pr->SiS_P3d4,0x17,0x80);
         SiS_SetReg(SiS_Pr->SiS_P3c4,0x00,0x01);
         SiS_SetReg(SiS_Pr->SiS_P3c4,0x00,0x03);
      पूर्ण
   पूर्ण
   अगर((sr1f) || (!cr17)) अणु
      SiS_WaitRetrace1(SiS_Pr);
      SiS_WaitRetrace1(SiS_Pr);
      SiS_WaitRetrace1(SiS_Pr);
      SiS_WaitRetrace1(SiS_Pr);
   पूर्ण

   अगर(DDCdatatype == 0) अणु
      result = SiS_ProbeDDC(SiS_Pr);
   पूर्ण अन्यथा अणु
      result = SiS_ReadDDC(SiS_Pr, DDCdatatype, buffer);
      अगर((!result) && (DDCdatatype == 1)) अणु
         अगर((buffer[0] == 0x00) && (buffer[1] == 0xff) &&
	    (buffer[2] == 0xff) && (buffer[3] == 0xff) &&
	    (buffer[4] == 0xff) && (buffer[5] == 0xff) &&
	    (buffer[6] == 0xff) && (buffer[7] == 0x00) &&
	    (buffer[0x12] == 1)) अणु
	    अगर(!SiS_Pr->DDCPortMixup) अणु
	       अगर(adaptnum == 1) अणु
	          अगर(!(buffer[0x14] & 0x80)) result = 0xFFFE;
	       पूर्ण अन्यथा अणु
	          अगर(buffer[0x14] & 0x80)    result = 0xFFFE;
	       पूर्ण
	    पूर्ण
	 पूर्ण
      पूर्ण
   पूर्ण
   SiS_SetReg(SiS_Pr->SiS_P3c4,0x1f,sr1f);
   अगर(VGAEngine == SIS_300_VGA) अणु
      SiS_SetRegANDOR(SiS_Pr->SiS_P3d4,0x17,0x7f,cr17);
   पूर्ण
   वापस result;
पूर्ण

/* Generic I2C functions क्रम Chrontel & DDC --------- */

अटल व्योम
SiS_SetSwitchDDC2(काष्ठा SiS_Private *SiS_Pr)
अणु
  SiS_SetSCLKHigh(SiS_Pr);
  SiS_WaitRetrace1(SiS_Pr);

  SiS_SetSCLKLow(SiS_Pr);
  SiS_WaitRetrace1(SiS_Pr);
पूर्ण

अचिन्हित लघु
SiS_ReadDDC1Bit(काष्ठा SiS_Private *SiS_Pr)
अणु
   SiS_WaitRetrace1(SiS_Pr);
   वापस ((SiS_GetReg(SiS_Pr->SiS_P3c4,0x11) & 0x02) >> 1);
पूर्ण

/* Set I2C start condition */
/* This is करोne by a SD high-to-low transition जबतक SC is high */
अटल अचिन्हित लघु
SiS_SetStart(काष्ठा SiS_Private *SiS_Pr)
अणु
  अगर(SiS_SetSCLKLow(SiS_Pr)) वापस 0xFFFF;			/* (SC->low)  */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  SiS_Pr->SiS_DDC_Data);        		/* SD->high */
  अगर(SiS_SetSCLKHigh(SiS_Pr)) वापस 0xFFFF;			/* SC->high */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  0x00);					/* SD->low = start condition */
  अगर(SiS_SetSCLKHigh(SiS_Pr)) वापस 0xFFFF;			/* (SC->low) */
  वापस 0;
पूर्ण

/* Set I2C stop condition */
/* This is करोne by a SD low-to-high transition जबतक SC is high */
अटल अचिन्हित लघु
SiS_SetStop(काष्ठा SiS_Private *SiS_Pr)
अणु
  अगर(SiS_SetSCLKLow(SiS_Pr)) वापस 0xFFFF;			/* (SC->low) */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  0x00);					/* SD->low   */
  अगर(SiS_SetSCLKHigh(SiS_Pr)) वापस 0xFFFF;			/* SC->high  */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  SiS_Pr->SiS_DDC_Data);			/* SD->high = stop condition */
  अगर(SiS_SetSCLKHigh(SiS_Pr)) वापस 0xFFFF;			/* (SC->high) */
  वापस 0;
पूर्ण

/* Write 8 bits of data */
अटल अचिन्हित लघु
SiS_WriteDDC2Data(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु tempax)
अणु
  अचिन्हित लघु i,flag,temp;

  flag = 0x80;
  क्रम(i = 0; i < 8; i++) अणु
    SiS_SetSCLKLow(SiS_Pr);					/* SC->low */
    अगर(tempax & flag) अणु
      SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		      SiS_Pr->SiS_DDC_Index,
		      SiS_Pr->SiS_DDC_NData,
		      SiS_Pr->SiS_DDC_Data);			/* Write bit (1) to SD */
    पूर्ण अन्यथा अणु
      SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		      SiS_Pr->SiS_DDC_Index,
		      SiS_Pr->SiS_DDC_NData,
		      0x00);					/* Write bit (0) to SD */
    पूर्ण
    SiS_SetSCLKHigh(SiS_Pr);					/* SC->high */
    flag >>= 1;
  पूर्ण
  temp = SiS_CheckACK(SiS_Pr);					/* Check acknowledge */
  वापस temp;
पूर्ण

अटल अचिन्हित लघु
SiS_ReadDDC2Data(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु i, temp, getdata;

  getdata = 0;
  क्रम(i = 0; i < 8; i++) अणु
    getdata <<= 1;
    SiS_SetSCLKLow(SiS_Pr);
    SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		    SiS_Pr->SiS_DDC_Index,
		    SiS_Pr->SiS_DDC_NData,
		    SiS_Pr->SiS_DDC_Data);
    SiS_SetSCLKHigh(SiS_Pr);
    temp = SiS_GetReg(SiS_Pr->SiS_DDC_Port,SiS_Pr->SiS_DDC_Index);
    अगर(temp & SiS_Pr->SiS_DDC_Data) getdata |= 0x01;
  पूर्ण
  वापस getdata;
पूर्ण

अटल अचिन्हित लघु
SiS_SetSCLKLow(काष्ठा SiS_Private *SiS_Pr)
अणु
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NClk,
		  0x00);					/* SetSCLKLow()  */
  SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT);
  वापस 0;
पूर्ण

अटल अचिन्हित लघु
SiS_SetSCLKHigh(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु temp, watchकरोg=1000;

  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NClk,
		  SiS_Pr->SiS_DDC_Clk);  			/* SetSCLKHigh()  */
  करो अणु
    temp = SiS_GetReg(SiS_Pr->SiS_DDC_Port,SiS_Pr->SiS_DDC_Index);
  पूर्ण जबतक((!(temp & SiS_Pr->SiS_DDC_Clk)) && --watchकरोg);
  अगर (!watchकरोg) अणु
  	वापस 0xFFFF;
  पूर्ण
  SiS_DDC2Delay(SiS_Pr,SiS_I2CDELAYSHORT);
  वापस 0;
पूर्ण

/* Check I2C acknowledge */
/* Returns 0 अगर ack ok, non-0 अगर ack not ok */
अटल अचिन्हित लघु
SiS_CheckACK(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु tempah;

  SiS_SetSCLKLow(SiS_Pr);				           /* (SC->low) */
  SiS_SetRegANDOR(SiS_Pr->SiS_DDC_Port,
		  SiS_Pr->SiS_DDC_Index,
		  SiS_Pr->SiS_DDC_NData,
		  SiS_Pr->SiS_DDC_Data);			   /* (SD->high) */
  SiS_SetSCLKHigh(SiS_Pr);				           /* SC->high = घड़ी impulse क्रम ack */
  tempah = SiS_GetReg(SiS_Pr->SiS_DDC_Port,SiS_Pr->SiS_DDC_Index); /* Read SD */
  SiS_SetSCLKLow(SiS_Pr);				           /* SC->low = end of घड़ी impulse */
  अगर(tempah & SiS_Pr->SiS_DDC_Data) वापस 1;			   /* Ack OK अगर bit = 0 */
  वापस 0;
पूर्ण

/* End of I2C functions ----------------------- */


/* =============== SiS 315/330 O.E.M. ================= */

#अगर_घोषित CONFIG_FB_SIS_315

अटल अचिन्हित लघु
GetRAMDACromptr(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु romptr;

  अगर(SiS_Pr->ChipType < SIS_330) अणु
     romptr = SISGETROMW(0x128);
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xB)
        romptr = SISGETROMW(0x12a);
  पूर्ण अन्यथा अणु
     romptr = SISGETROMW(0x1a8);
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xB)
        romptr = SISGETROMW(0x1aa);
  पूर्ण
  वापस romptr;
पूर्ण

अटल अचिन्हित लघु
GetLCDromptr(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु romptr;

  अगर(SiS_Pr->ChipType < SIS_330) अणु
     romptr = SISGETROMW(0x120);
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV)
        romptr = SISGETROMW(0x122);
  पूर्ण अन्यथा अणु
     romptr = SISGETROMW(0x1a0);
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV)
        romptr = SISGETROMW(0x1a2);
  पूर्ण
  वापस romptr;
पूर्ण

अटल अचिन्हित लघु
GetTVromptr(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु romptr;

  अगर(SiS_Pr->ChipType < SIS_330) अणु
     romptr = SISGETROMW(0x114);
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV)
        romptr = SISGETROMW(0x11a);
  पूर्ण अन्यथा अणु
     romptr = SISGETROMW(0x194);
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV)
        romptr = SISGETROMW(0x19a);
  पूर्ण
  वापस romptr;
पूर्ण

अटल अचिन्हित लघु
GetLCDPtrIndexBIOS(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु index;

  अगर((IS_SIS650) && (SiS_Pr->SiS_VBType & VB_SISLVDS)) अणु
     अगर(!(SiS_IsNotM650orLater(SiS_Pr))) अणु
        अगर((index = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) & 0xf0)) अणु
	   index >>= 4;
	   index *= 3;
	   अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) index += 2;
           अन्यथा अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) index++;
           वापस index;
	पूर्ण
     पूर्ण
  पूर्ण

  index = SiS_GetBIOSLCDResInfo(SiS_Pr) & 0x0F;
  अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050)      index -= 5;
  अगर(SiS_Pr->SiS_VBType & VB_SIS301C) अणु  /* 1.15.20 and later (not VB specअगरic) */
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) index -= 5;
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x768) index -= 5;
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) index -= 6;
  पूर्ण
  index--;
  index *= 3;
  अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) index += 2;
  अन्यथा अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) index++;
  वापस index;
पूर्ण

अटल अचिन्हित लघु
GetLCDPtrIndex(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु index;

  index = ((SiS_GetBIOSLCDResInfo(SiS_Pr) & 0x0F) - 1) * 3;
  अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD)         index += 2;
  अन्यथा अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) index++;
  वापस index;
पूर्ण

अटल अचिन्हित लघु
GetTVPtrIndex(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु index;

  index = 0;
  अगर(SiS_Pr->SiS_TVMode & TVSetPAL) index = 1;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) index = 2;

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToYPbPr525750) index = 0;

  index <<= 1;

  अगर((SiS_Pr->SiS_VBInfo & SetInSlaveMode) &&
     (SiS_Pr->SiS_TVMode & TVSetTVSimuMode)) अणु
     index++;
  पूर्ण

  वापस index;
पूर्ण

अटल अचिन्हित पूर्णांक
GetOEMTVPtr661_2_GEN(काष्ठा SiS_Private *SiS_Pr, पूर्णांक addme)
अणु
   अचिन्हित लघु index = 0, temp = 0;

   अगर(SiS_Pr->SiS_TVMode & TVSetPAL)   index = 1;
   अगर(SiS_Pr->SiS_TVMode & TVSetPALM)  index = 2;
   अगर(SiS_Pr->SiS_TVMode & TVSetPALN)  index = 3;
   अगर(SiS_Pr->SiS_TVMode & TVSetNTSCJ) index = 6;
   अगर(SiS_Pr->SiS_TVMode & TVSetNTSC1024) अणु
      index = 4;
      अगर(SiS_Pr->SiS_TVMode & TVSetPALM)  index++;
      अगर(SiS_Pr->SiS_TVMode & TVSetNTSCJ) index = 7;
   पूर्ण

   अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
      अगर((!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) ||
         (SiS_Pr->SiS_TVMode & TVSetTVSimuMode)) अणु
	 index += addme;
	 temp++;
      पूर्ण
      temp += 0x0100;
   पूर्ण
   वापस (अचिन्हित पूर्णांक)(index | (temp << 16));
पूर्ण

अटल अचिन्हित पूर्णांक
GetOEMTVPtr661_2_OLD(काष्ठा SiS_Private *SiS_Pr)
अणु
   वापस (GetOEMTVPtr661_2_GEN(SiS_Pr, 8));
पूर्ण

#अगर 0
अटल अचिन्हित पूर्णांक
GetOEMTVPtr661_2_NEW(काष्ठा SiS_Private *SiS_Pr)
अणु
   वापस (GetOEMTVPtr661_2_GEN(SiS_Pr, 6));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
GetOEMTVPtr661(काष्ठा SiS_Private *SiS_Pr)
अणु
   पूर्णांक index = 0;

   अगर(SiS_Pr->SiS_TVMode & TVSetPAL)          index = 2;
   अगर(SiS_Pr->SiS_ROMNew) अणु
      अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525i) index = 4;
      अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) index = 6;
      अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) index = 8;
      अगर(SiS_Pr->SiS_TVMode & TVSetHiVision)  index = 10;
   पूर्ण अन्यथा अणु
      अगर(SiS_Pr->SiS_TVMode & TVSetHiVision)  index = 4;
      अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525i) index = 6;
      अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr525p) index = 8;
      अगर(SiS_Pr->SiS_TVMode & TVSetYPbPr750p) index = 10;
   पूर्ण

   अगर(SiS_Pr->SiS_TVMode & TVSetTVSimuMode) index++;

   वापस index;
पूर्ण

अटल व्योम
SetDelayComp(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु delay=0,index,myindex,temp,romptr=0;
  bool करोchiptest = true;

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x20,0xbf);
  पूर्ण अन्यथा अणु
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x35,0x7f);
  पूर्ण

  /* Find delay (from ROM, पूर्णांकernal tables, PCI subप्रणाली) */

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) अणु			/* ------------ VGA */

     अगर((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) अणु
        romptr = GetRAMDACromptr(SiS_Pr);
     पूर्ण
     अगर(romptr) delay = ROMAddr[romptr];
     अन्यथा अणु
        delay = 0x04;
        अगर(SiS_Pr->SiS_VBType & VB_SIS30xB) अणु
	   अगर(IS_SIS650) अणु
	      delay = 0x0a;
	   पूर्ण अन्यथा अगर(IS_SIS740) अणु
	      delay = 0x00;
	   पूर्ण अन्यथा अणु
	      delay = 0x0c;
	   पूर्ण
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
           delay = 0x00;
	पूर्ण
     पूर्ण

  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD|SetCRT2ToLCDA)) अणु  /* ----------	LCD/LCDA */

     bool gotitfrompci = false;

     /* Could we detect a PDC क्रम LCD or did we get a user-defined? If yes, use it */

     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
	अगर(SiS_Pr->PDC != -1) अणु
           SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0xf0,((SiS_Pr->PDC >> 1) & 0x0f));
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x35,0x7f,((SiS_Pr->PDC & 0x01) << 7));
	   वापस;
	पूर्ण
     पूर्ण अन्यथा अणु
	अगर(SiS_Pr->PDCA != -1) अणु
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0x0f,((SiS_Pr->PDCA << 3) & 0xf0));
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x20,0xbf,((SiS_Pr->PDCA & 0x01) << 6));
	   वापस;
	पूर्ण
     पूर्ण

     /* Custom Panel? */

     अगर(SiS_Pr->SiS_LCDResInfo == Panel_Custom) अणु
        अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	   delay = 0x00;
	   अगर((SiS_Pr->PanelXRes <= 1280) && (SiS_Pr->PanelYRes <= 1024)) अणु
	      delay = 0x20;
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0x0f,delay);
	पूर्ण अन्यथा अणु
	   delay = 0x0c;
	   अगर(SiS_Pr->SiS_VBType & VB_SIS301C) अणु
	      delay = 0x03;
	      अगर((SiS_Pr->PanelXRes > 1280) && (SiS_Pr->PanelYRes > 1024)) अणु
	         delay = 0x00;
	      पूर्ण
	   पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	      अगर(IS_SIS740) delay = 0x01;
	      अन्यथा          delay = 0x03;
	   पूर्ण
	   SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0xf0,delay);
	पूर्ण
        वापस;
     पूर्ण

     /* This is a piece of typical SiS crap: They code the OEM LCD
      * delay पूर्णांकo the code, at no defined place in the BIOS.
      * We now have to start करोing a PCI subप्रणाली check here.
      */

     चयन(SiS_Pr->SiS_CustomT) अणु
     हाल CUT_COMPAQ1280:
     हाल CUT_COMPAQ12802:
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) अणु
	   gotitfrompci = true;
	   करोchiptest = false;
	   delay = 0x03;
	पूर्ण
	अवरोध;
     हाल CUT_CLEVO1400:
     हाल CUT_CLEVO14002:
	gotitfrompci = true;
	करोchiptest = false;
	delay = 0x02;
	अवरोध;
     हाल CUT_CLEVO1024:
     हाल CUT_CLEVO10242:
        अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	   gotitfrompci = true;
	   करोchiptest = false;
	   delay = 0x33;
	   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2D,delay);
	   delay &= 0x0f;
	पूर्ण
	अवरोध;
     पूर्ण

     /* Could we find it through the PCI ID? If no, use ROM or table */

     अगर(!gotitfrompci) अणु

        index = GetLCDPtrIndexBIOS(SiS_Pr);
        myindex = GetLCDPtrIndex(SiS_Pr);

        अगर(IS_SIS650 && (SiS_Pr->SiS_VBType & VB_SISLVDS)) अणु

           अगर(SiS_IsNotM650orLater(SiS_Pr)) अणु

              अगर((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) अणु
	         /* Always use the second poपूर्णांकer on 650; some BIOSes */
                 /* still carry old 301 data at the first location    */
	         /* romptr = SISGETROMW(0x120);                       */
	         /* अगर(SiS_Pr->SiS_VBType & VB_SIS302LV)              */
	         romptr = SISGETROMW(0x122);
	         अगर(!romptr) वापस;
	         delay = ROMAddr[(romptr + index)];
	      पूर्ण अन्यथा अणु
                 delay = SiS310_LCDDelayCompensation_650301LV[myindex];
	      पूर्ण

          पूर्ण अन्यथा अणु

             delay = SiS310_LCDDelayCompensation_651301LV[myindex];
	     अगर(SiS_Pr->SiS_VBType & (VB_SIS302LV | VB_SIS302ELV))
	        delay = SiS310_LCDDelayCompensation_651302LV[myindex];

          पूर्ण

        पूर्ण अन्यथा अगर(SiS_Pr->SiS_UseROM 			      &&
		  (!(SiS_Pr->SiS_ROMNew))		      &&
	          (SiS_Pr->SiS_LCDResInfo != Panel_1280x1024) &&
		  (SiS_Pr->SiS_LCDResInfo != Panel_1280x768)  &&
		  (SiS_Pr->SiS_LCDResInfo != Panel_1280x960)  &&
		  (SiS_Pr->SiS_LCDResInfo != Panel_1600x1200)  &&
		  ((romptr = GetLCDromptr(SiS_Pr)))) अणु

	   /* Data क्रम 1280x1024 wrong in 301B BIOS */
	   /* Data क्रम 1600x1200 wrong in 301C BIOS */
	   delay = ROMAddr[(romptr + index)];

        पूर्ण अन्यथा अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु

	   अगर(IS_SIS740) delay = 0x03;
	   अन्यथा          delay = 0x00;

	पूर्ण अन्यथा अणु

           delay = SiS310_LCDDelayCompensation_301[myindex];
	   अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
	      अगर(IS_SIS740) delay = 0x01;
	      अन्यथा अगर(SiS_Pr->ChipType <= SIS_315PRO) delay = SiS310_LCDDelayCompensation_3xx301LV[myindex];
	      अन्यथा          delay = SiS310_LCDDelayCompensation_650301LV[myindex];
	   पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SIS301C) अणु
	      अगर(IS_SIS740) delay = 0x01;  /* ? */
	      अन्यथा          delay = 0x03;
	      अगर(SiS_Pr->SiS_LCDResInfo == Panel_1600x1200) delay = 0x00; /* experience */
	   पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBType & VB_SIS30xB) अणु
	      अगर(IS_SIS740) delay = 0x01;
	      अन्यथा          delay = SiS310_LCDDelayCompensation_3xx301B[myindex];
	   पूर्ण

        पूर्ण

     पूर्ण  /* got it from PCI */

     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2D,0x0F,((delay << 4) & 0xf0));
	करोchiptest = false;
     पूर्ण

  पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु			/* ------------ TV */

     index = GetTVPtrIndex(SiS_Pr);

     अगर(IS_SIS650 && (SiS_Pr->SiS_VBType & VB_SISLVDS)) अणु

        अगर(SiS_IsNotM650orLater(SiS_Pr)) अणु

           अगर((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) अणु
	      /* Always use the second poपूर्णांकer on 650; some BIOSes */
              /* still carry old 301 data at the first location    */
              /* romptr = SISGETROMW(0x114);			   */
	      /* अगर(SiS_Pr->SiS_VBType & VB_SIS302LV)              */
	      romptr = SISGETROMW(0x11a);
	      अगर(!romptr) वापस;
	      delay = ROMAddr[romptr + index];

	   पूर्ण अन्यथा अणु

	      delay = SiS310_TVDelayCompensation_301B[index];

	   पूर्ण

        पूर्ण अन्यथा अणु

           चयन(SiS_Pr->SiS_CustomT) अणु
	   हाल CUT_COMPAQ1280:
	   हाल CUT_COMPAQ12802:
	   हाल CUT_CLEVO1400:
	   हाल CUT_CLEVO14002:
	      delay = 0x02;
	      करोchiptest = false;
	      अवरोध;
	   हाल CUT_CLEVO1024:
	   हाल CUT_CLEVO10242:
	      delay = 0x03;
	      करोchiptest = false;
   	      अवरोध;
	   शेष:
              delay = SiS310_TVDelayCompensation_651301LV[index];
	      अगर(SiS_Pr->SiS_VBType & VB_SIS302LV) अणु
	         delay = SiS310_TVDelayCompensation_651302LV[index];
	      पूर्ण
	   पूर्ण
        पूर्ण

     पूर्ण अन्यथा अगर((SiS_Pr->SiS_UseROM) && (!(SiS_Pr->SiS_ROMNew))) अणु

        romptr = GetTVromptr(SiS_Pr);
	अगर(!romptr) वापस;
	delay = ROMAddr[romptr + index];

     पूर्ण अन्यथा अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु

        delay = SiS310_TVDelayCompensation_LVDS[index];

     पूर्ण अन्यथा अणु

	delay = SiS310_TVDelayCompensation_301[index];
        अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
	   अगर(IS_SIS740) अणु
	      delay = SiS310_TVDelayCompensation_740301B[index];
	      /* LV: use 301 data? BIOS bug? */
	   पूर्ण अन्यथा अणु
              delay = SiS310_TVDelayCompensation_301B[index];
	      अगर(SiS_Pr->SiS_VBType & VB_SIS301C) delay = 0x02;
	   पूर्ण
	पूर्ण

     पूर्ण

     अगर(SiS_LCDAEnabled(SiS_Pr)) अणु
	delay &= 0x0f;
	करोchiptest = false;
     पूर्ण

  पूर्ण अन्यथा वापस;

  /* Write delay */

  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

     अगर(IS_SIS650 && (SiS_Pr->SiS_VBType & VB_SISLVDS) && करोchiptest) अणु

        temp = (SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) & 0xf0) >> 4;
        अगर(temp == 8) अणु		/* 1400x1050 BIOS (COMPAL) */
	   delay &= 0x0f;
	   delay |= 0xb0;
        पूर्ण अन्यथा अगर(temp == 6) अणु
           delay &= 0x0f;
	   delay |= 0xc0;
        पूर्ण अन्यथा अगर(temp > 7) अणु	/* 1280x1024 BIOS (which one?) */
	   delay = 0x35;
        पूर्ण
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x2D,delay);

     पूर्ण अन्यथा अणु

        SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2D,0xF0,delay);

     पूर्ण

  पूर्ण अन्यथा अणु  /* LVDS */

     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
        SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2D,0xF0,delay);
     पूर्ण अन्यथा अणु
        अगर(IS_SIS650 && (SiS_Pr->SiS_IF_DEF_CH70xx != 0)) अणु
           delay <<= 4;
           SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2D,0x0F,delay);
        पूर्ण अन्यथा अणु
           SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2D,0xF0,delay);
        पूर्ण
     पूर्ण

  पूर्ण

पूर्ण

अटल व्योम
SetAntiFlicker(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp,temp1,romptr=0;

  अगर(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p|TVSetYPbPr525p)) वापस;

  अगर(ModeNo<=0x13)
     index = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].VB_StTVFlickerIndex;
  अन्यथा
     index = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].VB_ExtTVFlickerIndex;

  temp = GetTVPtrIndex(SiS_Pr);
  temp >>= 1;  	  /* 0: NTSC/YPbPr, 1: PAL, 2: HiTV */
  temp1 = temp;

  अगर(SiS_Pr->SiS_UseROM && (!(SiS_Pr->SiS_ROMNew))) अणु
     अगर(SiS_Pr->ChipType >= SIS_661) अणु
        temp1 = GetOEMTVPtr661(SiS_Pr);
        temp1 >>= 1;
        romptr = SISGETROMW(0x260);
        अगर(SiS_Pr->ChipType >= SIS_760) अणु
	   romptr = SISGETROMW(0x360);
	पूर्ण
     पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_330) अणु
        romptr = SISGETROMW(0x192);
     पूर्ण अन्यथा अणु
        romptr = SISGETROMW(0x112);
     पूर्ण
  पूर्ण

  अगर(romptr) अणु
     temp1 <<= 1;
     temp = ROMAddr[romptr + temp1 + index];
  पूर्ण अन्यथा अणु
     temp = SiS310_TVAntiFlick1[temp][index];
  पूर्ण
  temp <<= 4;

  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x0A,0x8f,temp);  /* index 0A D[6:4] */
पूर्ण

अटल व्योम
SetEdgeEnhance(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp,temp1,romptr=0;

  temp = temp1 = GetTVPtrIndex(SiS_Pr) >> 1; 	/* 0: NTSC/YPbPr, 1: PAL, 2: HiTV */

  अगर(ModeNo <= 0x13)
     index = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].VB_StTVEdgeIndex;
  अन्यथा
     index = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].VB_ExtTVEdgeIndex;

  अगर(SiS_Pr->SiS_UseROM && (!(SiS_Pr->SiS_ROMNew))) अणु
     अगर(SiS_Pr->ChipType >= SIS_661) अणु
        romptr = SISGETROMW(0x26c);
        अगर(SiS_Pr->ChipType >= SIS_760) अणु
	   romptr = SISGETROMW(0x36c);
	पूर्ण
	temp1 = GetOEMTVPtr661(SiS_Pr);
        temp1 >>= 1;
     पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_330) अणु
        romptr = SISGETROMW(0x1a4);
     पूर्ण अन्यथा अणु
        romptr = SISGETROMW(0x124);
     पूर्ण
  पूर्ण

  अगर(romptr) अणु
     temp1 <<= 1;
     temp = ROMAddr[romptr + temp1 + index];
  पूर्ण अन्यथा अणु
     temp = SiS310_TVEdge1[temp][index];
  पूर्ण
  temp <<= 5;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x3A,0x1F,temp);  /* index 0A D[7:5] */
पूर्ण

अटल व्योम
SetYFilter(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित लघु index, temp, i, j;

  अगर(ModeNo <= 0x13) अणु
     index = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].VB_StTVYFilterIndex;
  पूर्ण अन्यथा अणु
     index = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].VB_ExtTVYFilterIndex;
  पूर्ण

  temp = GetTVPtrIndex(SiS_Pr) >> 1;  /* 0: NTSC/YPbPr, 1: PAL, 2: HiTV */

  अगर(SiS_Pr->SiS_TVMode & TVSetNTSCJ)	     temp = 1;  /* NTSC-J uses PAL */
  अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPALM)    temp = 3;  /* PAL-M */
  अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPALN)    temp = 4;  /* PAL-N */
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) temp = 1;  /* HiVision uses PAL */

  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
     क्रम(i=0x35, j=0; i<=0x38; i++, j++) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS310_TVYFilter2[temp][index][j]);
     पूर्ण
     क्रम(i=0x48; i<=0x4A; i++, j++) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS310_TVYFilter2[temp][index][j]);
     पूर्ण
  पूर्ण अन्यथा अणु
     क्रम(i=0x35, j=0; i<=0x38; i++, j++) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS310_TVYFilter1[temp][index][j]);
     पूर्ण
  पूर्ण
पूर्ण

अटल व्योम
SetPhaseIncr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp,i,j,resinfo,romptr=0;
  अचिन्हित पूर्णांक  lindex;

  अगर(!(SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) वापस;

  /* NTSC-J data not in BIOS, and alपढ़ोy set in SetGroup2 */
  अगर(SiS_Pr->SiS_TVMode & TVSetNTSCJ) वापस;

  अगर((SiS_Pr->ChipType >= SIS_661) || SiS_Pr->SiS_ROMNew) अणु
     lindex = GetOEMTVPtr661_2_OLD(SiS_Pr) & 0xffff;
     lindex <<= 2;
     क्रम(j=0, i=0x31; i<=0x34; i++, j++) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS_TVPhase[lindex + j]);
     पूर्ण
     वापस;
  पूर्ण

  /* PAL-M, PAL-N not in BIOS, and alपढ़ोy set in SetGroup2 */
  अगर(SiS_Pr->SiS_TVMode & (TVSetPALM | TVSetPALN)) वापस;

  अगर(ModeNo<=0x13) अणु
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
  पूर्ण अन्यथा अणु
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
  पूर्ण

  temp = GetTVPtrIndex(SiS_Pr);
  /* 0: NTSC Graphics, 1: NTSC Text,    2: PAL Graphics,
   * 3: PAL Text,      4: HiTV Graphics 5: HiTV Text
   */
  अगर(SiS_Pr->SiS_UseROM) अणु
     romptr = SISGETROMW(0x116);
     अगर(SiS_Pr->ChipType >= SIS_330) अणु
        romptr = SISGETROMW(0x196);
     पूर्ण
     अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
        romptr = SISGETROMW(0x11c);
	अगर(SiS_Pr->ChipType >= SIS_330) अणु
	   romptr = SISGETROMW(0x19c);
	पूर्ण
	अगर((SiS_Pr->SiS_VBInfo & SetInSlaveMode) && (!(SiS_Pr->SiS_TVMode & TVSetTVSimuMode))) अणु
	   romptr = SISGETROMW(0x116);
	   अगर(SiS_Pr->ChipType >= SIS_330) अणु
              romptr = SISGETROMW(0x196);
           पूर्ण
	पूर्ण
     पूर्ण
  पूर्ण
  अगर(romptr) अणु
     romptr += (temp << 2);
     क्रम(j=0, i=0x31; i<=0x34; i++, j++) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,i,ROMAddr[romptr + j]);
     पूर्ण
  पूर्ण अन्यथा अणु
     index = temp % 2;
     temp >>= 1;          /* 0:NTSC, 1:PAL, 2:HiTV */
     क्रम(j=0, i=0x31; i<=0x34; i++, j++) अणु
        अगर(!(SiS_Pr->SiS_VBType & VB_SIS30xBLV))
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS310_TVPhaseIncr1[temp][index][j]);
        अन्यथा अगर((!(SiS_Pr->SiS_VBInfo & SetInSlaveMode)) || (SiS_Pr->SiS_TVMode & TVSetTVSimuMode))
           SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS310_TVPhaseIncr2[temp][index][j]);
        अन्यथा
           SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS310_TVPhaseIncr1[temp][index][j]);
     पूर्ण
  पूर्ण

  अगर((SiS_Pr->SiS_VBType & VB_SIS30xBLV) && (!(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision))) अणु
     अगर((!(SiS_Pr->SiS_TVMode & (TVSetPAL | TVSetYPbPr525p | TVSetYPbPr750p))) && (ModeNo > 0x13)) अणु
        अगर((resinfo == SIS_RI_640x480) ||
	   (resinfo == SIS_RI_800x600)) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x31,0x21);
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x32,0xf0);
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x33,0xf5);
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x34,0x7f);
	पूर्ण अन्यथा अगर(resinfo == SIS_RI_1024x768) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x31,0x1e);
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x32,0x8b);
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x33,0xfb);
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,0x34,0x7b);
	पूर्ण
     पूर्ण
  पूर्ण
पूर्ण

अटल व्योम
SetDelayComp661(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
                अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RTI)
अणु
   अचिन्हित लघु delay = 0, romptr = 0, index, lcdpdcindex;
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;

   अगर(!(SiS_Pr->SiS_VBInfo & (SetCRT2ToTV | SetCRT2ToLCD | SetCRT2ToLCDA | SetCRT2ToRAMDAC)))
      वापस;

   /* 1. New ROM: VGA2 and LCD/LCDA-Pass1:1 */
   /* (If a custom mode is used, Pass1:1 is always set; hence we करो this:) */

   अगर(SiS_Pr->SiS_ROMNew) अणु
      अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToRAMDAC) 			||
         ((SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) &&
	  (SiS_Pr->SiS_LCDInfo & LCDPass11))) अणु
         index = 25;
         अगर(SiS_Pr->UseCustomMode) अणु
	    index = SiS_Pr->CSRClock;
         पूर्ण अन्यथा अगर(ModeNo > 0x13) अणु
            index = SiS_GetVCLK2Ptr(SiS_Pr,ModeNo,ModeIdIndex,RTI);
            index = SiS_Pr->SiS_VCLKData[index].CLOCK;
         पूर्ण
	 अगर(index < 25) index = 25;
         index = ((index / 25) - 1) << 1;
         अगर((ROMAddr[0x5b] & 0x80) || (SiS_Pr->SiS_VBInfo & (SetCRT2ToRAMDAC | SetCRT2ToLCD))) अणु
	    index++;
	 पूर्ण
	 romptr = SISGETROMW(0x104);
         delay = ROMAddr[romptr + index];
         अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToRAMDAC | SetCRT2ToLCD)) अणु
            SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0xf0,((delay >> 1) & 0x0f));
            SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x35,0x7f,((delay & 0x01) << 7));
         पूर्ण अन्यथा अणु
            SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0x0f,((delay << 3) & 0xf0));
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x20,0xbf,((delay & 0x01) << 6));
         पूर्ण
         वापस;
      पूर्ण
   पूर्ण

   /* 2. Old ROM: VGA2 and LCD/LCDA-Pass 1:1 */

   अगर(SiS_Pr->UseCustomMode) delay = 0x04;
   अन्यथा अगर(ModeNo <= 0x13)   delay = 0x04;
   अन्यथा                      delay = (SiS_Pr->SiS_RefIndex[RTI].Ext_PDC >> 4);
   delay |= (delay << 8);

   अगर(SiS_Pr->ChipType >= XGI_20) अणु

      delay = 0x0606;
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु

	 delay = 0x0404;
         अगर(SiS_Pr->SiS_XGIROM) अणु
	     index = GetTVPtrIndex(SiS_Pr);
	     अगर((romptr = SISGETROMW(0x35e))) अणु
	        delay = (ROMAddr[romptr + index] & 0x0f) << 1;
		delay |= (delay << 8);
	     पूर्ण
	 पूर्ण

	 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) अणु
	    अगर(SiS_Pr->ChipType == XGI_40 && SiS_Pr->ChipRevision == 0x02) अणु
	       delay -= 0x0404;
	    पूर्ण
	 पूर्ण
      पूर्ण

   पूर्ण अन्यथा अगर(SiS_Pr->ChipType >= SIS_340) अणु

      delay = 0x0606;
      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
         delay = 0x0404;
      पूर्ण
      /* TODO (eventually) */

   पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु

      /* 3. TV */

      index = GetOEMTVPtr661(SiS_Pr);
      अगर(SiS_Pr->SiS_ROMNew) अणु
         romptr = SISGETROMW(0x106);
	 अगर(SiS_Pr->SiS_VBType & VB_UMC) romptr += 12;
         delay = ROMAddr[romptr + index];
      पूर्ण अन्यथा अणु
         delay = 0x04;
	 अगर(index > 3) delay = 0;
      पूर्ण

   पूर्ण अन्यथा अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु

      /* 4. LCD, LCDA (क्रम new ROM only LV and non-Pass 1:1) */

      अगर( (SiS_Pr->SiS_LCDResInfo != Panel_Custom) &&
          ((romptr = GetLCDStructPtr661_2(SiS_Pr))) ) अणु

	 lcdpdcindex = (SiS_Pr->SiS_VBType & VB_UMC) ? 14 : 12;

	 /* For LVDS (and someबार TMDS), the BIOS must know about the correct value */
	 delay = ROMAddr[romptr + lcdpdcindex + 1];	/* LCD  */
	 delay |= (ROMAddr[romptr + lcdpdcindex] << 8);	/* LCDA */

      पूर्ण अन्यथा अणु

         /* TMDS: Set our own, since BIOS has no idea */
	 /* (This is करोne on >=661 only, since <661 is calling this only क्रम LVDS) */
         अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
	    चयन(SiS_Pr->SiS_LCDResInfo) अणु
	    हाल Panel_1024x768:  delay = 0x0008; अवरोध;
	    हाल Panel_1280x720:  delay = 0x0004; अवरोध;
	    हाल Panel_1280x768:
	    हाल Panel_1280x768_2:delay = 0x0004; अवरोध;
	    हाल Panel_1280x800:
	    हाल Panel_1280x800_2:delay = 0x0004; अवरोध; /* Verअगरied क्रम 1280x800 */
	    हाल Panel_1280x854:  delay = 0x0004; अवरोध; /* FIXME */
	    हाल Panel_1280x1024: delay = 0x1e04; अवरोध;
	    हाल Panel_1400x1050: delay = 0x0004; अवरोध;
	    हाल Panel_1600x1200: delay = 0x0400; अवरोध;
	    हाल Panel_1680x1050: delay = 0x0e04; अवरोध;
	    शेष:
               अगर((SiS_Pr->PanelXRes <= 1024) && (SiS_Pr->PanelYRes <= 768)) अणु
	          delay = 0x0008;
	       पूर्ण अन्यथा अगर((SiS_Pr->PanelXRes == 1280) && (SiS_Pr->PanelYRes == 1024)) अणु
	          delay = 0x1e04;
               पूर्ण अन्यथा अगर((SiS_Pr->PanelXRes <= 1400) && (SiS_Pr->PanelYRes <= 1050)) अणु
	          delay = 0x0004;
	       पूर्ण अन्यथा अगर((SiS_Pr->PanelXRes <= 1600) && (SiS_Pr->PanelYRes <= 1200)) अणु
	          delay = 0x0400;
               पूर्ण अन्यथा
	          delay = 0x0e04;
	       अवरोध;
	    पूर्ण
         पूर्ण

	 /* Override by detected or user-set values */
	 /* (but only अगर, क्रम some reason, we can't पढ़ो value from BIOS) */
         अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) && (SiS_Pr->PDC != -1)) अणु
            delay = SiS_Pr->PDC & 0x1f;
         पूर्ण
         अगर((SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) && (SiS_Pr->PDCA != -1)) अणु
            delay = (SiS_Pr->PDCA & 0x1f) << 8;
         पूर्ण

      पूर्ण

   पूर्ण

   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
      delay >>= 8;
      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0x0f,((delay << 3) & 0xf0));
      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x20,0xbf,((delay & 0x01) << 6));
   पूर्ण अन्यथा अणु
      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x2d,0xf0,((delay >> 1) & 0x0f));
      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x35,0x7f,((delay & 0x01) << 7));
   पूर्ण
पूर्ण

अटल व्योम
SetCRT2SyncDither661(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु RTI)
अणु
   अचिन्हित लघु infoflag;
   अचिन्हित अक्षर  temp;

   अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु

      अगर(ModeNo <= 0x13) अणु
         infoflag = SiS_GetRegByte(SiS_Pr->SiS_P3ca+2);
      पूर्ण अन्यथा अगर(SiS_Pr->UseCustomMode) अणु
         infoflag = SiS_Pr->CInfoFlag;
      पूर्ण अन्यथा अणु
         infoflag = SiS_Pr->SiS_RefIndex[RTI].Ext_InfoFlag;
      पूर्ण

      अगर(!(SiS_Pr->SiS_LCDInfo & LCDPass11)) अणु
         infoflag = SiS_GetReg(SiS_Pr->SiS_P3d4,0x37); /* No दीर्घer check D5 */
      पूर्ण

      infoflag &= 0xc0;

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
         temp = (infoflag >> 6) | 0x0c;
         अगर(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) अणु
	    temp ^= 0x04;
	    अगर(SiS_Pr->SiS_ModeType >= Mode24Bpp) temp |= 0x10;
	 पूर्ण
         SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x1a,0xe0,temp);
      पूर्ण अन्यथा अणु
         temp = 0x30;
         अगर(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) temp = 0x20;
         temp |= infoflag;
         SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x19,0x0f,temp);
         temp = 0;
         अगर(SiS_Pr->SiS_LCDInfo & LCDRGB18Bit) अणु
	    अगर(SiS_Pr->SiS_ModeType >= Mode24Bpp) temp |= 0x80;
	 पूर्ण
         SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x1a,0x7f,temp);
      पूर्ण

   पूर्ण
पूर्ण

अटल व्योम
SetPanelParms661(काष्ठा SiS_Private *SiS_Pr)
अणु
   अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
   अचिन्हित लघु romptr, temp1, temp2;

   अगर(SiS_Pr->SiS_VBType & (VB_SISLVDS | VB_SIS30xC)) अणु
      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x24,0x0f);
   पूर्ण

   अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
      अगर(SiS_Pr->LVDSHL != -1) अणु
         SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x24,0xfc,SiS_Pr->LVDSHL);
      पूर्ण
   पूर्ण

   अगर(SiS_Pr->SiS_ROMNew) अणु

      अगर((romptr = GetLCDStructPtr661_2(SiS_Pr))) अणु
         अगर(SiS_Pr->SiS_VBType & VB_SISLVDS) अणु
            temp1 = (ROMAddr[romptr] & 0x03) | 0x0c;
	    temp2 = 0xfc;
	    अगर(SiS_Pr->LVDSHL != -1) अणु
	      temp1 &= 0xfc;
	      temp2 = 0xf3;
	    पूर्ण
	    SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x24,temp2,temp1);
         पूर्ण
	 अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
            temp1 = (ROMAddr[romptr + 1] & 0x80) >> 1;
            SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x0d,0xbf,temp1);
	 पूर्ण
      पूर्ण

   पूर्ण
पूर्ण

अटल व्योम
SiS_OEM310Setting(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI)
अणु
   अगर((SiS_Pr->SiS_ROMNew) && (SiS_Pr->SiS_VBType & VB_SISLVDS)) अणु
      SetDelayComp661(SiS_Pr, ModeNo, ModeIdIndex, RRTI);
      अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
         SetCRT2SyncDither661(SiS_Pr, ModeNo, RRTI);
         SetPanelParms661(SiS_Pr);
      पूर्ण
   पूर्ण अन्यथा अणु
      SetDelayComp(SiS_Pr,ModeNo);
   पूर्ण

   अगर((SiS_Pr->SiS_VBType & VB_SISVB) && (SiS_Pr->SiS_VBInfo & SetCRT2ToTV)) अणु
      SetAntiFlicker(SiS_Pr,ModeNo,ModeIdIndex);
      SetPhaseIncr(SiS_Pr,ModeNo,ModeIdIndex);
      SetYFilter(SiS_Pr,ModeNo,ModeIdIndex);
      अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
         SetEdgeEnhance(SiS_Pr,ModeNo,ModeIdIndex);
      पूर्ण
   पूर्ण
पूर्ण

अटल व्योम
SiS_OEM661Setting(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,
			अचिन्हित लघु ModeIdIndex, अचिन्हित लघु RRTI)
अणु
   अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु

      SetDelayComp661(SiS_Pr, ModeNo, ModeIdIndex, RRTI);

      अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
         SetCRT2SyncDither661(SiS_Pr, ModeNo, RRTI);
         SetPanelParms661(SiS_Pr);
      पूर्ण

      अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
         SetPhaseIncr(SiS_Pr, ModeNo, ModeIdIndex);
         SetYFilter(SiS_Pr, ModeNo, ModeIdIndex);
         SetAntiFlicker(SiS_Pr, ModeNo, ModeIdIndex);
         अगर(SiS_Pr->SiS_VBType & VB_SIS301) अणु
            SetEdgeEnhance(SiS_Pr, ModeNo, ModeIdIndex);
         पूर्ण
      पूर्ण
   पूर्ण
पूर्ण

/* FinalizeLCD
 * This finalizes some CRT2 रेजिस्टरs क्रम the very panel used.
 * If we have a backup अगर these रेजिस्टरs, we use it; otherwise
 * we set the रेजिस्टर according to most BIOSes. However, this
 * function looks quite dअगरferent in every BIOS, so you better
 * pray that we have a backup...
 */
अटल व्योम
SiS_FinalizeLCD(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित लघु tempcl,tempch,tempbl,tempbh,tempbx,tempax,temp;
  अचिन्हित लघु resinfo,modeflag;

  अगर(!(SiS_Pr->SiS_VBType & VB_SISLVDS)) वापस;
  अगर(SiS_Pr->SiS_ROMNew) वापस;

  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     अगर(SiS_Pr->LVDSHL != -1) अणु
        SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x24,0xfc,SiS_Pr->LVDSHL);
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_LCDResInfo == Panel_Custom) वापस;
  अगर(SiS_Pr->UseCustomMode) वापस;

  चयन(SiS_Pr->SiS_CustomT) अणु
  हाल CUT_COMPAQ1280:
  हाल CUT_COMPAQ12802:
  हाल CUT_CLEVO1400:
  हाल CUT_CLEVO14002:
     वापस;
  पूर्ण

  अगर(ModeNo <= 0x13) अणु
     resinfo = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ResInfo;
     modeflag =  SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
  पूर्ण अन्यथा अणु
     resinfo = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_RESINFO;
     modeflag =  SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
  पूर्ण

  अगर(IS_SIS650) अणु
     अगर(!(SiS_GetReg(SiS_Pr->SiS_P3d4, 0x5f) & 0xf0)) अणु
        अगर(SiS_Pr->SiS_CustomT == CUT_CLEVO1024) अणु
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1e,0x02);
	पूर्ण अन्यथा अणु
           SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x1e,0x03);
	पूर्ण
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_CustomT == CUT_CLEVO1024) अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
        /* Maybe all panels? */
        अगर(SiS_Pr->LVDSHL == -1) अणु
           SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x24,0xfc,0x01);
	पूर्ण
	वापस;
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_CustomT == CUT_CLEVO10242) अणु
     अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
        अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	   अगर(SiS_Pr->LVDSHL == -1) अणु
	      /* Maybe all panels? */
              SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x24,0xfc,0x01);
	   पूर्ण
	   अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	      tempch = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4;
	      अगर(tempch == 3) अणु
	         SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x02);
	         SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,0x25);
	         SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1c,0x00);
	         SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1d,0x1b);
	      पूर्ण
	   पूर्ण
	   वापस;
	पूर्ण
     पूर्ण
  पूर्ण

  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToLCD | SetCRT2ToLCDA)) अणु
     अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	अगर(SiS_Pr->SiS_VBType & VB_SISEMI) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part4Port,0x2a,0x00);
#अगर_घोषित SET_EMI
	   SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
#पूर्ण_अगर
	   SiS_SetReg(SiS_Pr->SiS_Part4Port,0x34,0x10);
	पूर्ण
     पूर्ण अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1280x1024) अणु
        अगर(SiS_Pr->LVDSHL == -1) अणु
           /* Maybe ACER only? */
           SiS_SetRegANDOR(SiS_Pr->SiS_Part4Port,0x24,0xfc,0x01);
	पूर्ण
     पूर्ण
     tempch = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) >> 4;
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCDA) अणु
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_1400x1050) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1f,0x76);
	पूर्ण अन्यथा अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	   अगर(tempch == 0x03) अणु
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x02);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,0x25);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1c,0x00);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1d,0x1b);
	   पूर्ण
	   अगर(SiS_Pr->Backup && (SiS_Pr->Backup_Mode == ModeNo)) अणु
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x14,SiS_Pr->Backup_14);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x15,SiS_Pr->Backup_15);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x16,SiS_Pr->Backup_16);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x17,SiS_Pr->Backup_17);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,SiS_Pr->Backup_18);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x19,SiS_Pr->Backup_19);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1a,SiS_Pr->Backup_1a);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,SiS_Pr->Backup_1b);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1c,SiS_Pr->Backup_1c);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1d,SiS_Pr->Backup_1d);
	   पूर्ण अन्यथा अगर(!(SiS_Pr->SiS_LCDInfo & DontExpandLCD)) अणु	/* 1.10.8w */
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x14,0x90);
	      अगर(ModeNo <= 0x13) अणु
	         SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x11);
		 अगर((resinfo == 0) || (resinfo == 2)) वापस;
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x18);
		 अगर((resinfo == 1) || (resinfo == 3)) वापस;
	      पूर्ण
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x02);
	      अगर((ModeNo > 0x13) && (resinfo == SIS_RI_1024x768)) अणु
	         SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x02);  /* 1.10.7u */
#अगर 0
	         tempbx = 806;  /* 0x326 */			 /* other older BIOSes */
		 tempbx--;
		 temp = tempbx & 0xff;
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,temp);
		 temp = (tempbx >> 8) & 0x03;
		 SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x1d,0xf8,temp);
#पूर्ण_अगर
	      पूर्ण
	   पूर्ण अन्यथा अगर(ModeNo <= 0x13) अणु
	      अगर(ModeNo <= 1) अणु
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x70);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x19,0xff);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,0x48);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1d,0x12);
	      पूर्ण
	      अगर(!(modeflag & HalfDCLK)) अणु
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x14,0x20);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x15,0x1a);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x16,0x28);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x17,0x00);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x4c);
		 SiS_SetReg(SiS_Pr->SiS_Part1Port,0x19,0xdc);
		 अगर(ModeNo == 0x12) अणु
		    चयन(tempch) अणु
		       हाल 0:
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x95);
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x19,0xdc);
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1a,0x10);
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,0x95);
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1c,0x48);
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1d,0x12);
			  अवरोध;
		       हाल 2:
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,0x95);
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,0x48);
			  अवरोध;
		       हाल 3:
			  SiS_SetReg(SiS_Pr->SiS_Part1Port,0x1b,0x95);
			  अवरोध;
		    पूर्ण
		 पूर्ण
	      पूर्ण
	   पूर्ण
	पूर्ण
     पूर्ण अन्यथा अणु
        tempcl = tempbh = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x01);
	tempcl &= 0x0f;
	tempbh &= 0x70;
	tempbh >>= 4;
	tempbl = SiS_GetReg(SiS_Pr->SiS_Part2Port,0x04);
	tempbx = (tempbh << 8) | tempbl;
	अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
	   अगर((resinfo == SIS_RI_1024x768) || (!(SiS_Pr->SiS_LCDInfo & DontExpandLCD))) अणु
	      अगर(SiS_Pr->SiS_SetFlag & LCDVESATiming) अणु
	      	 tempbx = 770;
	      पूर्ण अन्यथा अणु
	         अगर(tempbx > 770) tempbx = 770;
		 अगर(SiS_Pr->SiS_VGAVDE < 600) अणु
		    tempax = 768 - SiS_Pr->SiS_VGAVDE;
		    tempax >>= 4;  				 /* 1.10.7w; 1.10.6s: 3;  */
		    अगर(SiS_Pr->SiS_VGAVDE <= 480)  tempax >>= 4; /* 1.10.7w; 1.10.6s: < 480; >>=1; */
		    tempbx -= tempax;
		 पूर्ण
	      पूर्ण
	   पूर्ण अन्यथा वापस;
	पूर्ण
	temp = tempbx & 0xff;
	SiS_SetReg(SiS_Pr->SiS_Part2Port,0x04,temp);
	temp = ((tempbx & 0xff00) >> 4) | tempcl;
	SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x01,0x80,temp);
     पूर्ण
  पूर्ण
पूर्ण

#पूर्ण_अगर

/*  =================  SiS 300 O.E.M. ================== */

#अगर_घोषित CONFIG_FB_SIS_300

अटल व्योम
SetOEMLCDData2(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex,
		अचिन्हित लघु RefTabIndex)
अणु
  अचिन्हित लघु crt2crtc=0, modeflag, myindex=0;
  अचिन्हित अक्षर  temp;
  पूर्णांक i;

  अगर(ModeNo <= 0x13) अणु
     modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
     crt2crtc = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_CRT2CRTC;
  पूर्ण अन्यथा अणु
     modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     crt2crtc = SiS_Pr->SiS_RefIndex[RefTabIndex].Ext_CRT2CRTC;
  पूर्ण

  crt2crtc &= 0x3f;

  अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1024) अणु
     SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xdf);
  पूर्ण

  अगर(SiS_Pr->SiS_CustomT == CUT_BARCO1366) अणु
     अगर(modeflag & HalfDCLK) myindex = 1;

     अगर(SiS_Pr->SiS_SetFlag & LowModeTests) अणु
        क्रम(i=0; i<7; i++) अणु
           अगर(barco_p1[myindex][crt2crtc][i][0]) अणु
	      SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,
	                      barco_p1[myindex][crt2crtc][i][0],
	   	   	      barco_p1[myindex][crt2crtc][i][2],
			      barco_p1[myindex][crt2crtc][i][1]);
	   पूर्ण
        पूर्ण
     पूर्ण
     temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00);
     अगर(temp & 0x80) अणु
        temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x18);
        temp++;
        SiS_SetReg(SiS_Pr->SiS_Part1Port,0x18,temp);
     पूर्ण
  पूर्ण
पूर्ण

अटल अचिन्हित लघु
GetOEMLCDPtr(काष्ठा SiS_Private *SiS_Pr, पूर्णांक Flag)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु tempbx=0,romptr=0;
  अटल स्थिर अचिन्हित अक्षर customtable300[] = अणु
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
  पूर्ण;
  अटल स्थिर अचिन्हित अक्षर customtable630[] = अणु
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
  पूर्ण;

  अगर(SiS_Pr->ChipType == SIS_300) अणु

    tempbx = SiS_GetReg(SiS_Pr->SiS_P3d4,0x36) & 0x0f;
    अगर(SiS_Pr->SiS_VBType & VB_SIS301) tempbx &= 0x07;
    tempbx -= 2;
    अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) tempbx += 4;
    अगर(SiS_Pr->SiS_LCDResInfo == Panel_1024x768) अणु
       अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx += 3;
    पूर्ण
    अगर(SiS_Pr->SiS_UseROM) अणु
       अगर(ROMAddr[0x235] & 0x80) अणु
          tempbx = SiS_Pr->SiS_LCDTypeInfo;
          अगर(Flag) अणु
	     romptr = SISGETROMW(0x255);
	     अगर(romptr) tempbx = ROMAddr[romptr + SiS_Pr->SiS_LCDTypeInfo];
	     अन्यथा       tempbx = customtable300[SiS_Pr->SiS_LCDTypeInfo];
             अगर(tempbx == 0xFF) वापस 0xFFFF;
          पूर्ण
	  tempbx <<= 1;
	  अगर(!(SiS_Pr->SiS_SetFlag & LCDVESATiming)) tempbx++;
       पूर्ण
    पूर्ण

  पूर्ण अन्यथा अणु

    अगर(Flag) अणु
       अगर(SiS_Pr->SiS_UseROM) अणु
          romptr = SISGETROMW(0x255);
	  अगर(romptr) tempbx = ROMAddr[romptr + SiS_Pr->SiS_LCDTypeInfo];
	  अन्यथा 	     tempbx = 0xff;
       पूर्ण अन्यथा अणु
          tempbx = customtable630[SiS_Pr->SiS_LCDTypeInfo];
       पूर्ण
       अगर(tempbx == 0xFF) वापस 0xFFFF;
       tempbx <<= 2;
       अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) tempbx += 2;
       अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;
       वापस tempbx;
    पूर्ण
    tempbx = SiS_Pr->SiS_LCDTypeInfo << 2;
    अगर(SiS_Pr->SiS_VBInfo & SetInSlaveMode) tempbx += 2;
    अगर(SiS_Pr->SiS_LCDInfo & DontExpandLCD) tempbx++;

  पूर्ण

  वापस tempbx;
पूर्ण

अटल व्योम
SetOEMLCDDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp,romptr=0;

  अगर(SiS_Pr->SiS_LCDResInfo == Panel_Custom) वापस;

  अगर(SiS_Pr->SiS_UseROM) अणु
     अगर(!(ROMAddr[0x237] & 0x01)) वापस;
     अगर(!(ROMAddr[0x237] & 0x02)) वापस;
     romptr = SISGETROMW(0x24b);
  पूर्ण

  /* The Panel Compensation Delay should be set according to tables
   * here. Unक्रमtunately, various BIOS versions करोn't care about
   * a unअगरorm way using eg. ROM byte 0x220, but use dअगरferent
   * hard coded delays (0x04, 0x20, 0x18) in SetGroup1().
   * Thus we करोn't set this अगर the user selected a custom pdc or अगर
   * we otherwise detected a valid pdc.
   */
  अगर(SiS_Pr->PDC != -1) वापस;

  temp = GetOEMLCDPtr(SiS_Pr, 0);

  अगर(SiS_Pr->UseCustomMode)
     index = 0;
  अन्यथा
     index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].VB_LCDDelayIndex;

  अगर(SiS_Pr->ChipType != SIS_300) अणु
     अगर(romptr) अणु
	romptr += (temp * 2);
	romptr = SISGETROMW(romptr);
	romptr += index;
	temp = ROMAddr[romptr];
     पूर्ण अन्यथा अणु
	अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
    	   temp = SiS300_OEMLCDDelay2[temp][index];
	पूर्ण अन्यथा अणु
           temp = SiS300_OEMLCDDelay3[temp][index];
        पूर्ण
     पूर्ण
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_UseROM && (ROMAddr[0x235] & 0x80)) अणु
	अगर(romptr) अणु
	   romptr += (temp * 2);
	   romptr = SISGETROMW(romptr);
	   romptr += index;
	   temp = ROMAddr[romptr];
	पूर्ण अन्यथा अणु
	   temp = SiS300_OEMLCDDelay5[temp][index];
	पूर्ण
     पूर्ण अन्यथा अणु
        अगर(SiS_Pr->SiS_UseROM) अणु
	   romptr = ROMAddr[0x249] | (ROMAddr[0x24a] << 8);
	   अगर(romptr) अणु
	      romptr += (temp * 2);
	      romptr = SISGETROMW(romptr);
	      romptr += index;
	      temp = ROMAddr[romptr];
	   पूर्ण अन्यथा अणु
	      temp = SiS300_OEMLCDDelay4[temp][index];
	   पूर्ण
	पूर्ण अन्यथा अणु
	   temp = SiS300_OEMLCDDelay4[temp][index];
	पूर्ण
     पूर्ण
  पूर्ण
  temp &= 0x3c;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,~0x3C,temp);  /* index 0A D[6:4] */
पूर्ण

अटल व्योम
SetOEMLCDData(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
#अगर 0  /* Unfinished; Data table missing */
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp;

  अगर((SiS_Pr->SiS_UseROM) अणु
     अगर(!(ROMAddr[0x237] & 0x01)) वापस;
     अगर(!(ROMAddr[0x237] & 0x04)) वापस;
     /* No rom poपूर्णांकer in BIOS header! */
  पूर्ण

  temp = GetOEMLCDPtr(SiS_Pr, 1);
  अगर(temp == 0xFFFF) वापस;

  index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex]._VB_LCDHIndex;
  क्रम(i=0x14, j=0; i<=0x17; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_Part1Port,i,SiS300_LCDHData[temp][index][j]);
  पूर्ण
  SiS_SetRegANDOR(SiS_SiS_Part1Port,0x1a, 0xf8, (SiS300_LCDHData[temp][index][j] & 0x07));

  index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex]._VB_LCDVIndex;
  SiS_SetReg(SiS_SiS_Part1Port,0x18, SiS300_LCDVData[temp][index][0]);
  SiS_SetRegANDOR(SiS_SiS_Part1Port,0x19, 0xF0, SiS300_LCDVData[temp][index][1]);
  SiS_SetRegANDOR(SiS_SiS_Part1Port,0x1A, 0xC7, (SiS300_LCDVData[temp][index][2] & 0x38));
  क्रम(i=0x1b, j=3; i<=0x1d; i++, j++) अणु
      SiS_SetReg(SiS_Pr->SiS_Part1Port,i,SiS300_LCDVData[temp][index][j]);
  पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित लघु
GetOEMTVPtr(काष्ठा SiS_Private *SiS_Pr)
अणु
  अचिन्हित लघु index;

  index = 0;
  अगर(!(SiS_Pr->SiS_VBInfo & SetInSlaveMode))  index += 4;
  अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
     अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToSCART)  index += 2;
     अन्यथा अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) index += 3;
     अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPAL)   index += 1;
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_TVMode & TVSetCHOverScan) index += 2;
     अगर(SiS_Pr->SiS_TVMode & TVSetPAL)        index += 1;
  पूर्ण
  वापस index;
पूर्ण

अटल व्योम
SetOEMTVDelay(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp,romptr=0;

  अगर(SiS_Pr->SiS_UseROM) अणु
     अगर(!(ROMAddr[0x238] & 0x01)) वापस;
     अगर(!(ROMAddr[0x238] & 0x02)) वापस;
     romptr = SISGETROMW(0x241);
  पूर्ण

  temp = GetOEMTVPtr(SiS_Pr);

  index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].VB_TVDelayIndex;

  अगर(romptr) अणु
     romptr += (temp * 2);
     romptr = SISGETROMW(romptr);
     romptr += index;
     temp = ROMAddr[romptr];
  पूर्ण अन्यथा अणु
     अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
        temp = SiS300_OEMTVDelay301[temp][index];
     पूर्ण अन्यथा अणु
        temp = SiS300_OEMTVDelayLVDS[temp][index];
     पूर्ण
  पूर्ण
  temp &= 0x3c;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part1Port,0x13,~0x3C,temp);
पूर्ण

अटल व्योम
SetOEMAntiFlicker(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp,romptr=0;

  अगर(SiS_Pr->SiS_UseROM) अणु
     अगर(!(ROMAddr[0x238] & 0x01)) वापस;
     अगर(!(ROMAddr[0x238] & 0x04)) वापस;
     romptr = SISGETROMW(0x243);
  पूर्ण

  temp = GetOEMTVPtr(SiS_Pr);

  index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].VB_TVFlickerIndex;

  अगर(romptr) अणु
     romptr += (temp * 2);
     romptr = SISGETROMW(romptr);
     romptr += index;
     temp = ROMAddr[romptr];
  पूर्ण अन्यथा अणु
     temp = SiS300_OEMTVFlicker[temp][index];
  पूर्ण
  temp &= 0x70;
  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x0A,0x8F,temp);
पूर्ण

अटल व्योम
SetOEMPhaseIncr(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo,अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,i,j,temp,romptr=0;

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) वापस;

  अगर(SiS_Pr->SiS_TVMode & (TVSetNTSC1024 | TVSetNTSCJ | TVSetPALM | TVSetPALN)) वापस;

  अगर(SiS_Pr->SiS_UseROM) अणु
     अगर(!(ROMAddr[0x238] & 0x01)) वापस;
     अगर(!(ROMAddr[0x238] & 0x08)) वापस;
     romptr = SISGETROMW(0x245);
  पूर्ण

  temp = GetOEMTVPtr(SiS_Pr);

  index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].VB_TVPhaseIndex;

  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
     क्रम(i=0x31, j=0; i<=0x34; i++, j++) अणु
        SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS300_Phase2[temp][index][j]);
     पूर्ण
  पूर्ण अन्यथा अणु
     अगर(romptr) अणु
        romptr += (temp * 2);
	romptr = SISGETROMW(romptr);
	romptr += (index * 4);
        क्रम(i=0x31, j=0; i<=0x34; i++, j++) अणु
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,i,ROMAddr[romptr + j]);
	पूर्ण
     पूर्ण अन्यथा अणु
        क्रम(i=0x31, j=0; i<=0x34; i++, j++) अणु
           SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS300_Phase1[temp][index][j]);
	पूर्ण
     पूर्ण
  पूर्ण
पूर्ण

अटल व्योम
SetOEMYFilter(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex)
अणु
  अचिन्हित अक्षर  *ROMAddr = SiS_Pr->VirtualRomBase;
  अचिन्हित लघु index,temp,i,j,romptr=0;

  अगर(SiS_Pr->SiS_VBInfo & (SetCRT2ToSCART | SetCRT2ToHiVision | SetCRT2ToYPbPr525750)) वापस;

  अगर(SiS_Pr->SiS_UseROM) अणु
     अगर(!(ROMAddr[0x238] & 0x01)) वापस;
     अगर(!(ROMAddr[0x238] & 0x10)) वापस;
     romptr = SISGETROMW(0x247);
  पूर्ण

  temp = GetOEMTVPtr(SiS_Pr);

  अगर(SiS_Pr->SiS_TVMode & TVSetPALM)      temp = 8;
  अन्यथा अगर(SiS_Pr->SiS_TVMode & TVSetPALN) temp = 9;
  /* NTSCJ uses NTSC filters */

  index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].VB_TVYFilterIndex;

  अगर(SiS_Pr->SiS_VBType & VB_SIS30xBLV) अणु
      क्रम(i=0x35, j=0; i<=0x38; i++, j++) अणु
       	SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS300_Filter2[temp][index][j]);
      पूर्ण
      क्रम(i=0x48; i<=0x4A; i++, j++) अणु
     	SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS300_Filter2[temp][index][j]);
      पूर्ण
  पूर्ण अन्यथा अणु
      अगर((romptr) && (!(SiS_Pr->SiS_TVMode & (TVSetPALM|TVSetPALN)))) अणु
         romptr += (temp * 2);
	 romptr = SISGETROMW(romptr);
	 romptr += (index * 4);
	 क्रम(i=0x35, j=0; i<=0x38; i++, j++) अणु
       	    SiS_SetReg(SiS_Pr->SiS_Part2Port,i,ROMAddr[romptr + j]);
         पूर्ण
      पूर्ण अन्यथा अणु
         क्रम(i=0x35, j=0; i<=0x38; i++, j++) अणु
       	    SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS300_Filter1[temp][index][j]);
         पूर्ण
      पूर्ण
  पूर्ण
पूर्ण

अटल अचिन्हित लघु
SiS_SearchVBModeID(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु *ModeNo)
अणु
   अचिन्हित लघु ModeIdIndex;
   अचिन्हित अक्षर  VGAINFO = SiS_Pr->SiS_VGAINFO;

   अगर(*ModeNo <= 5) *ModeNo |= 1;

   क्रम(ModeIdIndex=0; ; ModeIdIndex++) अणु
      अगर(SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].ModeID == *ModeNo) अवरोध;
      अगर(SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].ModeID == 0xFF)    वापस 0;
   पूर्ण

   अगर(*ModeNo != 0x07) अणु
      अगर(*ModeNo > 0x03) वापस ModeIdIndex;
      अगर(VGAINFO & 0x80) वापस ModeIdIndex;
      ModeIdIndex++;
   पूर्ण

   अगर(VGAINFO & 0x10) ModeIdIndex++;   /* 400 lines */
	                               /* अन्यथा 350 lines */
   वापस ModeIdIndex;
पूर्ण

अटल व्योम
SiS_OEM300Setting(काष्ठा SiS_Private *SiS_Pr, अचिन्हित लघु ModeNo, अचिन्हित लघु ModeIdIndex,
		  अचिन्हित लघु RefTableIndex)
अणु
  अचिन्हित लघु OEMModeIdIndex = 0;

  अगर(!SiS_Pr->UseCustomMode) अणु
     OEMModeIdIndex = SiS_SearchVBModeID(SiS_Pr,&ModeNo);
     अगर(!(OEMModeIdIndex)) वापस;
  पूर्ण

  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) अणु
     SetOEMLCDDelay(SiS_Pr, ModeNo, OEMModeIdIndex);
     अगर(SiS_Pr->SiS_IF_DEF_LVDS == 1) अणु
        SetOEMLCDData(SiS_Pr, ModeNo, OEMModeIdIndex);
     पूर्ण
  पूर्ण
  अगर(SiS_Pr->UseCustomMode) वापस;
  अगर(SiS_Pr->SiS_VBInfo & SetCRT2ToTV) अणु
     SetOEMTVDelay(SiS_Pr, ModeNo,OEMModeIdIndex);
     अगर(SiS_Pr->SiS_VBType & VB_SISVB) अणु
        SetOEMAntiFlicker(SiS_Pr, ModeNo, OEMModeIdIndex);
    	SetOEMPhaseIncr(SiS_Pr, ModeNo, OEMModeIdIndex);
       	SetOEMYFilter(SiS_Pr, ModeNo, OEMModeIdIndex);
     पूर्ण
  पूर्ण
पूर्ण
#पूर्ण_अगर

