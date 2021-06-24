<शैली गुरु>
/*
 * Copyright (c) 2005 ASPEED Technology Inc.
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * करोcumentation, and that the name of the authors not be used in
 * advertising or खुलाity pertaining to distribution of the software without
 * specअगरic, written prior permission.  The authors makes no representations
 * about the suitability of this software क्रम any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * THE AUTHORS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE AUTHORS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */
/* Ported from xf86-video-ast driver */

#अगर_अघोषित AST_TABLES_H
#घोषणा AST_TABLES_H

/* Std. Table Index Definition */
#घोषणा TextModeIndex		0
#घोषणा EGAModeIndex		1
#घोषणा VGAModeIndex		2
#घोषणा HiCModeIndex		3
#घोषणा TrueCModeIndex		4

#घोषणा Charx8Dot               0x00000001
#घोषणा HalfDCLK                0x00000002
#घोषणा DoubleScanMode          0x00000004
#घोषणा LineCompareOff          0x00000008
#घोषणा HBorder                 0x00000020
#घोषणा VBorder                 0x00000010
#घोषणा WideScreenMode		0x00000100
#घोषणा NewModeInfo		0x00000200
#घोषणा NHSync			0x00000400
#घोषणा PHSync			0x00000800
#घोषणा NVSync			0x00001000
#घोषणा PVSync			0x00002000
#घोषणा SyncPP			(PVSync | PHSync)
#घोषणा SyncPN			(PVSync | NHSync)
#घोषणा SyncNP			(NVSync | PHSync)
#घोषणा SyncNN			(NVSync | NHSync)
#घोषणा AST2500PreCatchCRT		0x00004000

/* DCLK Index */
#घोषणा VCLK25_175     		0x00
#घोषणा VCLK28_322     		0x01
#घोषणा VCLK31_5       		0x02
#घोषणा VCLK36         		0x03
#घोषणा VCLK40         		0x04
#घोषणा VCLK49_5       		0x05
#घोषणा VCLK50         		0x06
#घोषणा VCLK56_25      		0x07
#घोषणा VCLK65		 	0x08
#घोषणा VCLK75	        	0x09
#घोषणा VCLK78_75      		0x0A
#घोषणा VCLK94_5       		0x0B
#घोषणा VCLK108        		0x0C
#घोषणा VCLK135        		0x0D
#घोषणा VCLK157_5      		0x0E
#घोषणा VCLK162        		0x0F
/* #घोषणा VCLK193_25     		0x10 */
#घोषणा VCLK154     		0x10
#घोषणा VCLK83_5    		0x11
#घोषणा VCLK106_5   		0x12
#घोषणा VCLK146_25  		0x13
#घोषणा VCLK148_5   		0x14
#घोषणा VCLK71      		0x15
#घोषणा VCLK88_75   		0x16
#घोषणा VCLK119     		0x17
#घोषणा VCLK85_5     		0x18
#घोषणा VCLK97_75     		0x19
#घोषणा VCLK118_25			0x1A

अटल स्थिर काष्ठा ast_vbios_dclk_info dclk_table[] = अणु
	अणु0x2C, 0xE7, 0x03पूर्ण,			/* 00: VCLK25_175	*/
	अणु0x95, 0x62, 0x03पूर्ण,			/* 01: VCLK28_322	*/
	अणु0x67, 0x63, 0x01पूर्ण,			/* 02: VCLK31_5		*/
	अणु0x76, 0x63, 0x01पूर्ण,			/* 03: VCLK36		*/
	अणु0xEE, 0x67, 0x01पूर्ण,			/* 04: VCLK40		*/
	अणु0x82, 0x62, 0x01पूर्ण,			/* 05: VCLK49_5		*/
	अणु0xC6, 0x64, 0x01पूर्ण,			/* 06: VCLK50		*/
	अणु0x94, 0x62, 0x01पूर्ण,			/* 07: VCLK56_25	*/
	अणु0x80, 0x64, 0x00पूर्ण,			/* 08: VCLK65		*/
	अणु0x7B, 0x63, 0x00पूर्ण,			/* 09: VCLK75		*/
	अणु0x67, 0x62, 0x00पूर्ण,			/* 0A: VCLK78_75	*/
	अणु0x7C, 0x62, 0x00पूर्ण,			/* 0B: VCLK94_5		*/
	अणु0x8E, 0x62, 0x00पूर्ण,			/* 0C: VCLK108		*/
	अणु0x85, 0x24, 0x00पूर्ण,			/* 0D: VCLK135		*/
	अणु0x67, 0x22, 0x00पूर्ण,			/* 0E: VCLK157_5	*/
	अणु0x6A, 0x22, 0x00पूर्ण,			/* 0F: VCLK162		*/
	अणु0x4d, 0x4c, 0x80पूर्ण,			/* 10: VCLK154		*/
	अणु0x68, 0x6f, 0x80पूर्ण,			/* 11: VCLK83.5		*/
	अणु0x28, 0x49, 0x80पूर्ण,			/* 12: VCLK106.5	*/
	अणु0x37, 0x49, 0x80पूर्ण,			/* 13: VCLK146.25	*/
	अणु0x1f, 0x45, 0x80पूर्ण,			/* 14: VCLK148.5	*/
	अणु0x47, 0x6c, 0x80पूर्ण,			/* 15: VCLK71		*/
	अणु0x25, 0x65, 0x80पूर्ण,			/* 16: VCLK88.75	*/
	अणु0x77, 0x58, 0x80पूर्ण,			/* 17: VCLK119		*/
	अणु0x32, 0x67, 0x80पूर्ण,			/* 18: VCLK85_5		*/
	अणु0x6a, 0x6d, 0x80पूर्ण,			/* 19: VCLK97_75	*/
	अणु0x3b, 0x2c, 0x81पूर्ण,			/* 1A: VCLK118_25	*/
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_dclk_info dclk_table_ast2500[] = अणु
	अणु0x2C, 0xE7, 0x03पूर्ण,			/* 00: VCLK25_175	*/
	अणु0x95, 0x62, 0x03पूर्ण,			/* 01: VCLK28_322	*/
	अणु0x67, 0x63, 0x01पूर्ण,			/* 02: VCLK31_5		*/
	अणु0x76, 0x63, 0x01पूर्ण,			/* 03: VCLK36		*/
	अणु0xEE, 0x67, 0x01पूर्ण,			/* 04: VCLK40		*/
	अणु0x82, 0x62, 0x01पूर्ण,			/* 05: VCLK49_5		*/
	अणु0xC6, 0x64, 0x01पूर्ण,			/* 06: VCLK50		*/
	अणु0x94, 0x62, 0x01पूर्ण,			/* 07: VCLK56_25	*/
	अणु0x80, 0x64, 0x00पूर्ण,			/* 08: VCLK65		*/
	अणु0x7B, 0x63, 0x00पूर्ण,			/* 09: VCLK75		*/
	अणु0x67, 0x62, 0x00पूर्ण,			/* 0A: VCLK78_75	*/
	अणु0x7C, 0x62, 0x00पूर्ण,			/* 0B: VCLK94_5		*/
	अणु0x8E, 0x62, 0x00पूर्ण,			/* 0C: VCLK108		*/
	अणु0x85, 0x24, 0x00पूर्ण,			/* 0D: VCLK135		*/
	अणु0x67, 0x22, 0x00पूर्ण,			/* 0E: VCLK157_5	*/
	अणु0x6A, 0x22, 0x00पूर्ण,			/* 0F: VCLK162		*/
	अणु0x4d, 0x4c, 0x80पूर्ण,			/* 10: VCLK154		*/
	अणु0x68, 0x6f, 0x80पूर्ण,			/* 11: VCLK83.5		*/
	अणु0x28, 0x49, 0x80पूर्ण,			/* 12: VCLK106.5	*/
	अणु0x37, 0x49, 0x80पूर्ण,			/* 13: VCLK146.25	*/
	अणु0x1f, 0x45, 0x80पूर्ण,			/* 14: VCLK148.5	*/
	अणु0x47, 0x6c, 0x80पूर्ण,			/* 15: VCLK71		*/
	अणु0x25, 0x65, 0x80पूर्ण,			/* 16: VCLK88.75	*/
	अणु0x58, 0x01, 0x42पूर्ण,			/* 17: VCLK119		*/
	अणु0x32, 0x67, 0x80पूर्ण,			/* 18: VCLK85_5		*/
	अणु0x6a, 0x6d, 0x80पूर्ण,			/* 19: VCLK97_75	*/
	अणु0x44, 0x20, 0x43पूर्ण,			/* 1A: VCLK118_25	*/
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_stdtable vbios_stdtable[] = अणु
	/* MD_2_3_400 */
	अणु
		0x67,
		अणु0x00,0x03,0x00,0x02पूर्ण,
		अणु0x5f,0x4f,0x50,0x82,0x55,0x81,0xbf,0x1f,
		 0x00,0x4f,0x0d,0x0e,0x00,0x00,0x00,0x00,
		 0x9c,0x8e,0x8f,0x28,0x1f,0x96,0xb9,0xa3,
		 0xffपूर्ण,
		अणु0x00,0x01,0x02,0x03,0x04,0x05,0x14,0x07,
		 0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		 0x0c,0x00,0x0f,0x08पूर्ण,
		अणु0x00,0x00,0x00,0x00,0x00,0x10,0x0e,0x00,
		 0xffपूर्ण
	पूर्ण,
	/* Mode12/ExtEGATable */
	अणु
		0xe3,
		अणु0x01,0x0f,0x00,0x06पूर्ण,
		अणु0x5f,0x4f,0x50,0x82,0x55,0x81,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xe9,0x8b,0xdf,0x28,0x00,0xe7,0x04,0xe3,
		 0xffपूर्ण,
		अणु0x00,0x01,0x02,0x03,0x04,0x05,0x14,0x07,
		 0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
		 0x01,0x00,0x0f,0x00पूर्ण,
		अणु0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0f,
		 0xffपूर्ण
	पूर्ण,
	/* ExtVGATable */
	अणु
		0x2f,
		अणु0x01,0x0f,0x00,0x0eपूर्ण,
		अणु0x5f,0x4f,0x50,0x82,0x54,0x80,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xea,0x8c,0xdf,0x28,0x40,0xe7,0x04,0xa3,
		 0xffपूर्ण,
		अणु0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
		 0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		 0x01,0x00,0x00,0x00पूर्ण,
		अणु0x00,0x00,0x00,0x00,0x00,0x40,0x05,0x0f,
		 0xffपूर्ण
	पूर्ण,
	/* ExtHiCTable */
	अणु
		0x2f,
		अणु0x01,0x0f,0x00,0x0eपूर्ण,
		अणु0x5f,0x4f,0x50,0x82,0x54,0x80,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xea,0x8c,0xdf,0x28,0x40,0xe7,0x04,0xa3,
		 0xffपूर्ण,
		अणु0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
		 0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		 0x01,0x00,0x00,0x00पूर्ण,
		अणु0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0f,
		 0xffपूर्ण
	पूर्ण,
	/* ExtTrueCTable */
	अणु
		0x2f,
		अणु0x01,0x0f,0x00,0x0eपूर्ण,
		अणु0x5f,0x4f,0x50,0x82,0x54,0x80,0x0b,0x3e,
		 0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,
		 0xea,0x8c,0xdf,0x28,0x40,0xe7,0x04,0xa3,
		 0xffपूर्ण,
		अणु0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
		 0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
		 0x01,0x00,0x00,0x00पूर्ण,
		अणु0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x0f,
		 0xffपूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_640x480[] = अणु
	अणु 800, 640, 8, 96, 525, 480, 2, 2, VCLK25_175,	/* 60Hz */
	  (SyncNN | HBorder | VBorder | Charx8Dot), 60, 1, 0x2E पूर्ण,
	अणु 832, 640, 16, 40, 520, 480, 1, 3, VCLK31_5,	/* 72Hz */
	  (SyncNN | HBorder | VBorder | Charx8Dot), 72, 2, 0x2E  पूर्ण,
	अणु 840, 640, 16, 64, 500, 480, 1, 3, VCLK31_5,	/* 75Hz */
	  (SyncNN | Charx8Dot) , 75, 3, 0x2E पूर्ण,
	अणु 832, 640, 56, 56, 509, 480, 1, 3, VCLK36,	/* 85Hz */
	  (SyncNN | Charx8Dot) , 85, 4, 0x2E पूर्ण,
	अणु 832, 640, 56, 56, 509, 480, 1, 3, VCLK36,	/* end */
	  (SyncNN | Charx8Dot) , 0xFF, 4, 0x2E पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_800x600[] = अणु
	अणु1024, 800, 24, 72, 625, 600, 1, 2, VCLK36,	/* 56Hz */
	 (SyncPP | Charx8Dot), 56, 1, 0x30 पूर्ण,
	अणु1056, 800, 40, 128, 628, 600, 1, 4, VCLK40,	/* 60Hz */
	 (SyncPP | Charx8Dot), 60, 2, 0x30 पूर्ण,
	अणु1040, 800, 56, 120, 666, 600, 37, 6, VCLK50,	/* 72Hz */
	 (SyncPP | Charx8Dot), 72, 3, 0x30 पूर्ण,
	अणु1056, 800, 16, 80, 625, 600, 1, 3, VCLK49_5,	/* 75Hz */
	 (SyncPP | Charx8Dot), 75, 4, 0x30 पूर्ण,
	अणु1048, 800, 32, 64, 631, 600, 1, 3, VCLK56_25,	/* 85Hz */
	 (SyncPP | Charx8Dot), 84, 5, 0x30 पूर्ण,
	अणु1048, 800, 32, 64, 631, 600, 1, 3, VCLK56_25,	/* end */
	 (SyncPP | Charx8Dot), 0xFF, 5, 0x30 पूर्ण,
पूर्ण;


अटल स्थिर काष्ठा ast_vbios_enhtable res_1024x768[] = अणु
	अणु1344, 1024, 24, 136, 806, 768, 3, 6, VCLK65,	/* 60Hz */
	 (SyncNN | Charx8Dot), 60, 1, 0x31 पूर्ण,
	अणु1328, 1024, 24, 136, 806, 768, 3, 6, VCLK75,	/* 70Hz */
	 (SyncNN | Charx8Dot), 70, 2, 0x31 पूर्ण,
	अणु1312, 1024, 16, 96, 800, 768, 1, 3, VCLK78_75,	/* 75Hz */
	 (SyncPP | Charx8Dot), 75, 3, 0x31 पूर्ण,
	अणु1376, 1024, 48, 96, 808, 768, 1, 3, VCLK94_5,	/* 85Hz */
	 (SyncPP | Charx8Dot), 84, 4, 0x31 पूर्ण,
	अणु1376, 1024, 48, 96, 808, 768, 1, 3, VCLK94_5,	/* end */
	 (SyncPP | Charx8Dot), 0xFF, 4, 0x31 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_1280x1024[] = अणु
	अणु1688, 1280, 48, 112, 1066, 1024, 1, 3, VCLK108,	/* 60Hz */
	 (SyncPP | Charx8Dot), 60, 1, 0x32 पूर्ण,
	अणु1688, 1280, 16, 144, 1066, 1024, 1, 3, VCLK135,	/* 75Hz */
	 (SyncPP | Charx8Dot), 75, 2, 0x32 पूर्ण,
	अणु1728, 1280, 64, 160, 1072, 1024, 1, 3, VCLK157_5,	/* 85Hz */
	 (SyncPP | Charx8Dot), 85, 3, 0x32 पूर्ण,
	अणु1728, 1280, 64, 160, 1072, 1024, 1, 3, VCLK157_5,	/* end */
	 (SyncPP | Charx8Dot), 0xFF, 3, 0x32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_1600x1200[] = अणु
	अणु2160, 1600, 64, 192, 1250, 1200, 1, 3, VCLK162,	/* 60Hz */
	 (SyncPP | Charx8Dot), 60, 1, 0x33 पूर्ण,
	अणु2160, 1600, 64, 192, 1250, 1200, 1, 3, VCLK162,	/* end */
	 (SyncPP | Charx8Dot), 0xFF, 1, 0x33 पूर्ण,
पूर्ण;

/* 16:9 */
अटल स्थिर काष्ठा ast_vbios_enhtable res_1360x768[] = अणु
	अणु1792, 1360, 64, 112, 795, 768, 3, 6, VCLK85_5,		/* 60Hz */
	 (SyncPP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 60, 1, 0x39 पूर्ण,
	अणु1792, 1360, 64, 112, 795, 768, 3, 6, VCLK85_5,	         /* end */
	 (SyncPP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 0xFF, 1, 0x39 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_1600x900[] = अणु
	अणु1800, 1600, 24, 80, 1000,  900, 1, 3, VCLK108,		/* 60Hz */
	 (SyncPP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 60, 3, 0x3A पूर्ण,
	अणु1760, 1600, 48, 32, 926, 900, 3, 5, VCLK97_75,		/* 60Hz CVT RB */
	 (SyncNP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 60, 1, 0x3A पूर्ण,
	अणु2112, 1600, 88, 168, 934, 900, 3, 5, VCLK118_25,	/* 60Hz CVT */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 60, 2, 0x3A पूर्ण,
	अणु2112, 1600, 88, 168, 934, 900, 3, 5, VCLK118_25,	/* 60Hz CVT */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 0xFF, 2, 0x3A पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_1920x1080[] = अणु
	अणु2200, 1920, 88, 44, 1125, 1080, 4, 5, VCLK148_5,	/* 60Hz */
	 (SyncPP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 60, 1, 0x38 पूर्ण,
	अणु2200, 1920, 88, 44, 1125, 1080, 4, 5, VCLK148_5,	/* 60Hz */
	 (SyncPP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 0xFF, 1, 0x38 पूर्ण,
पूर्ण;


/* 16:10 */
अटल स्थिर काष्ठा ast_vbios_enhtable res_1280x800[] = अणु
	अणु1440, 1280, 48, 32,  823,  800, 3, 6, VCLK71,		/* 60Hz RB */
	 (SyncNP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 60, 1, 0x35 पूर्ण,
	अणु1680, 1280, 72,128,  831,  800, 3, 6, VCLK83_5,	/* 60Hz */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 60, 2, 0x35 पूर्ण,
	अणु1680, 1280, 72,128,  831,  800, 3, 6, VCLK83_5,	/* 60Hz */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 0xFF, 2, 0x35 पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_1440x900[] = अणु
	अणु1600, 1440, 48, 32,  926,  900, 3, 6, VCLK88_75,	/* 60Hz RB */
	 (SyncNP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 60, 1, 0x36 पूर्ण,
	अणु1904, 1440, 80,152,  934,  900, 3, 6, VCLK106_5,	/* 60Hz */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 60, 2, 0x36 पूर्ण,
	अणु1904, 1440, 80,152,  934,  900, 3, 6, VCLK106_5,	/* 60Hz */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 0xFF, 2, 0x36 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_1680x1050[] = अणु
	अणु1840, 1680, 48, 32, 1080, 1050, 3, 6, VCLK119,		/* 60Hz RB */
	 (SyncNP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 60, 1, 0x37 पूर्ण,
	अणु2240, 1680,104,176, 1089, 1050, 3, 6, VCLK146_25,	/* 60Hz */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 60, 2, 0x37 पूर्ण,
	अणु2240, 1680,104,176, 1089, 1050, 3, 6, VCLK146_25,	/* 60Hz */
	 (SyncPN | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo), 0xFF, 2, 0x37 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ast_vbios_enhtable res_1920x1200[] = अणु
	अणु2080, 1920, 48, 32, 1235, 1200, 3, 6, VCLK154,		/* 60Hz RB*/
	 (SyncNP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 60, 1, 0x34 पूर्ण,
	अणु2080, 1920, 48, 32, 1235, 1200, 3, 6, VCLK154,		/* 60Hz RB */
	 (SyncNP | Charx8Dot | LineCompareOff | WideScreenMode | NewModeInfo |
	  AST2500PreCatchCRT), 0xFF, 1, 0x34 पूर्ण,
पूर्ण;

#पूर्ण_अगर
