<शैली गुरु>
/*
 *  drivers/video/imsttfb.c -- frame buffer device क्रम IMS TwinTurbo
 *
 *  This file is derived from the घातermac console "imstt" driver:
 *  Copyright (C) 1997 Sigurdur Asgeirsson
 *  With additional hacking by Jeffrey Kuskin (jsk@mojave.stanक्रमd.edu)
 *  Modअगरied by Danilo Beuche 1998
 *  Some रेजिस्टर values added by Damien Doligez, INRIA Rocquencourt
 *  Various cleanups by Paul Mundt (lethal@chaoticdreams.org)
 *
 *  This file was written by Ryan Niअन्यथाn (ran@krazynet.com)
 *  Most of the frame buffer device stuff was copied from atyfb.c
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

#अगर defined(CONFIG_PPC_PMAC)
#समावेश <linux/nvram.h>
#समावेश "macmodes.h"
#पूर्ण_अगर

#अगर_अघोषित __घातerpc__
#घोषणा eieio()		/* Enक्रमce In-order Execution of I/O */
#पूर्ण_अगर

/* TwinTurbo (Cosmo) रेजिस्टरs */
क्रमागत अणु
	S1SA	=  0, /* 0x00 */
	S2SA	=  1, /* 0x04 */
	SP	=  2, /* 0x08 */
	DSA	=  3, /* 0x0C */
	CNT	=  4, /* 0x10 */
	DP_OCTL	=  5, /* 0x14 */
	CLR	=  6, /* 0x18 */
	BI	=  8, /* 0x20 */
	MBC	=  9, /* 0x24 */
	BLTCTL	= 10, /* 0x28 */

	/* Scan Timing Generator Registers */
	HES	= 12, /* 0x30 */
	HEB	= 13, /* 0x34 */
	HSB	= 14, /* 0x38 */
	HT	= 15, /* 0x3C */
	VES	= 16, /* 0x40 */
	VEB	= 17, /* 0x44 */
	VSB	= 18, /* 0x48 */
	VT	= 19, /* 0x4C */
	HCIV	= 20, /* 0x50 */
	VCIV	= 21, /* 0x54 */
	TCDR	= 22, /* 0x58 */
	VIL	= 23, /* 0x5C */
	STGCTL	= 24, /* 0x60 */

	/* Screen Refresh Generator Registers */
	SSR	= 25, /* 0x64 */
	HRIR	= 26, /* 0x68 */
	SPR	= 27, /* 0x6C */
	CMR	= 28, /* 0x70 */
	SRGCTL	= 29, /* 0x74 */

	/* RAM Refresh Generator Registers */
	RRCIV	= 30, /* 0x78 */
	RRSC	= 31, /* 0x7C */
	RRCR	= 34, /* 0x88 */

	/* System Registers */
	GIOE	= 32, /* 0x80 */
	GIO	= 33, /* 0x84 */
	SCR	= 35, /* 0x8C */
	SSTATUS	= 36, /* 0x90 */
	PRC	= 37, /* 0x94 */

#अगर 0	
	/* PCI Registers */
	DVID	= 0x00000000L,
	SC	= 0x00000004L,
	CCR	= 0x00000008L,
	OG	= 0x0000000CL,
	BARM	= 0x00000010L,
	BARER	= 0x00000030L,
#पूर्ण_अगर
पूर्ण;

/* IBM 624 RAMDAC Direct Registers */
क्रमागत अणु
	PADDRW	= 0x00,
	PDATA	= 0x04,
	PPMASK	= 0x08,
	PADDRR	= 0x0c,
	PIDXLO	= 0x10,	
	PIDXHI	= 0x14,	
	PIDXDATA= 0x18,
	PIDXCTL	= 0x1c
पूर्ण;

/* IBM 624 RAMDAC Indirect Registers */
क्रमागत अणु
	CLKCTL		= 0x02,	/* (0x01) Miscellaneous Clock Control */
	SYNCCTL		= 0x03,	/* (0x00) Sync Control */
	HSYNCPOS	= 0x04,	/* (0x00) Horizontal Sync Position */
	PWRMNGMT	= 0x05,	/* (0x00) Power Management */
	DACOP		= 0x06,	/* (0x02) DAC Operation */
	PALETCTL	= 0x07,	/* (0x00) Palette Control */
	SYSCLKCTL	= 0x08,	/* (0x01) System Clock Control */
	PIXFMT		= 0x0a,	/* () Pixel Format  [bpp >> 3 + 2] */
	BPP8		= 0x0b,	/* () 8 Bits/Pixel Control */
	BPP16		= 0x0c, /* () 16 Bits/Pixel Control  [bit 1=1 क्रम 565] */
	BPP24		= 0x0d,	/* () 24 Bits/Pixel Control */
	BPP32		= 0x0e,	/* () 32 Bits/Pixel Control */
	PIXCTL1		= 0x10, /* (0x05) Pixel PLL Control 1 */
	PIXCTL2		= 0x11,	/* (0x00) Pixel PLL Control 2 */
	SYSCLKN		= 0x15,	/* () System Clock N (System PLL Reference Divider) */
	SYSCLKM		= 0x16,	/* () System Clock M (System PLL VCO Divider) */
	SYSCLKP		= 0x17,	/* () System Clock P */
	SYSCLKC		= 0x18,	/* () System Clock C */
	/*
	 * Dot घड़ी rate is 20MHz * (m + 1) / ((n + 1) * (p ? 2 * p : 1)
	 * c is अक्षरge pump bias which depends on the VCO frequency  
	 */
	PIXM0		= 0x20,	/* () Pixel M 0 */
	PIXN0		= 0x21,	/* () Pixel N 0 */
	PIXP0		= 0x22,	/* () Pixel P 0 */
	PIXC0		= 0x23,	/* () Pixel C 0 */
	CURSCTL		= 0x30,	/* (0x00) Cursor Control */
	CURSXLO		= 0x31,	/* () Cursor X position, low 8 bits */
	CURSXHI		= 0x32,	/* () Cursor X position, high 8 bits */
	CURSYLO		= 0x33,	/* () Cursor Y position, low 8 bits */
	CURSYHI		= 0x34,	/* () Cursor Y position, high 8 bits */
	CURSHOTX	= 0x35,	/* () Cursor Hot Spot X */
	CURSHOTY	= 0x36,	/* () Cursor Hot Spot Y */
	CURSACCTL	= 0x37,	/* () Advanced Cursor Control Enable */
	CURSACATTR	= 0x38,	/* () Advanced Cursor Attribute */
	CURS1R		= 0x40,	/* () Cursor 1 Red */
	CURS1G		= 0x41,	/* () Cursor 1 Green */
	CURS1B		= 0x42,	/* () Cursor 1 Blue */
	CURS2R		= 0x43,	/* () Cursor 2 Red */
	CURS2G		= 0x44,	/* () Cursor 2 Green */
	CURS2B		= 0x45,	/* () Cursor 2 Blue */
	CURS3R		= 0x46,	/* () Cursor 3 Red */
	CURS3G		= 0x47,	/* () Cursor 3 Green */
	CURS3B		= 0x48,	/* () Cursor 3 Blue */
	BORDR		= 0x60,	/* () Border Color Red */
	BORDG		= 0x61,	/* () Border Color Green */
	BORDB		= 0x62,	/* () Border Color Blue */
	MISCTL1		= 0x70,	/* (0x00) Miscellaneous Control 1 */
	MISCTL2		= 0x71,	/* (0x00) Miscellaneous Control 2 */
	MISCTL3		= 0x72,	/* (0x00) Miscellaneous Control 3 */
	KEYCTL		= 0x78	/* (0x00) Key Control/DB Operation */
पूर्ण;

/* TI TVP 3030 RAMDAC Direct Registers */
क्रमागत अणु
	TVPADDRW = 0x00,	/* 0  Palette/Cursor RAM Write Address/Index */
	TVPPDATA = 0x04,	/* 1  Palette Data RAM Data */
	TVPPMASK = 0x08,	/* 2  Pixel Read-Mask */
	TVPPADRR = 0x0c,	/* 3  Palette/Cursor RAM Read Address */
	TVPCADRW = 0x10,	/* 4  Cursor/Overscan Color Write Address */
	TVPCDATA = 0x14,	/* 5  Cursor/Overscan Color Data */
				/* 6  reserved */
	TVPCADRR = 0x1c,	/* 7  Cursor/Overscan Color Read Address */
				/* 8  reserved */
	TVPDCCTL = 0x24,	/* 9  Direct Cursor Control */
	TVPIDATA = 0x28,	/* 10 Index Data */
	TVPCRDAT = 0x2c,	/* 11 Cursor RAM Data */
	TVPCXPOL = 0x30,	/* 12 Cursor-Position X LSB */
	TVPCXPOH = 0x34,	/* 13 Cursor-Position X MSB */
	TVPCYPOL = 0x38,	/* 14 Cursor-Position Y LSB */
	TVPCYPOH = 0x3c,	/* 15 Cursor-Position Y MSB */
पूर्ण;

/* TI TVP 3030 RAMDAC Indirect Registers */
क्रमागत अणु
	TVPIRREV = 0x01,	/* Silicon Revision [RO] */
	TVPIRICC = 0x06,	/* Indirect Cursor Control 	(0x00) */
	TVPIRBRC = 0x07,	/* Byte Router Control 	(0xe4) */
	TVPIRLAC = 0x0f,	/* Latch Control 		(0x06) */
	TVPIRTCC = 0x18,	/* True Color Control  	(0x80) */
	TVPIRMXC = 0x19,	/* Multiplex Control		(0x98) */
	TVPIRCLS = 0x1a,	/* Clock Selection		(0x07) */
	TVPIRPPG = 0x1c,	/* Palette Page		(0x00) */
	TVPIRGEC = 0x1d,	/* General Control 		(0x00) */
	TVPIRMIC = 0x1e,	/* Miscellaneous Control	(0x00) */
	TVPIRPLA = 0x2c,	/* PLL Address */
	TVPIRPPD = 0x2d,	/* Pixel Clock PLL Data */
	TVPIRMPD = 0x2e,	/* Memory Clock PLL Data */
	TVPIRLPD = 0x2f,	/* Loop Clock PLL Data */
	TVPIRCKL = 0x30,	/* Color-Key Overlay Low */
	TVPIRCKH = 0x31,	/* Color-Key Overlay High */
	TVPIRCRL = 0x32,	/* Color-Key Red Low */
	TVPIRCRH = 0x33,	/* Color-Key Red High */
	TVPIRCGL = 0x34,	/* Color-Key Green Low */
	TVPIRCGH = 0x35,	/* Color-Key Green High */
	TVPIRCBL = 0x36,	/* Color-Key Blue Low */
	TVPIRCBH = 0x37,	/* Color-Key Blue High */
	TVPIRCKC = 0x38,	/* Color-Key Control 		(0x00) */
	TVPIRMLC = 0x39,	/* MCLK/Loop Clock Control	(0x18) */
	TVPIRSEN = 0x3a,	/* Sense Test			(0x00) */
	TVPIRTMD = 0x3b,	/* Test Mode Data */
	TVPIRRML = 0x3c,	/* CRC Reमुख्यder LSB [RO] */
	TVPIRRMM = 0x3d,	/* CRC Reमुख्यder MSB [RO] */
	TVPIRRMS = 0x3e,	/* CRC  Bit Select [WO] */
	TVPIRDID = 0x3f,	/* Device ID [RO] 		(0x30) */
	TVPIRRES = 0xff		/* Software Reset [WO] */
पूर्ण;

काष्ठा initvalues अणु
	__u8 addr, value;
पूर्ण;

अटल काष्ठा initvalues ibm_initregs[] = अणु
	अणु CLKCTL,	0x21 पूर्ण,
	अणु SYNCCTL,	0x00 पूर्ण,
	अणु HSYNCPOS,	0x00 पूर्ण,
	अणु PWRMNGMT,	0x00 पूर्ण,
	अणु DACOP,	0x02 पूर्ण,
	अणु PALETCTL,	0x00 पूर्ण,
	अणु SYSCLKCTL,	0x01 पूर्ण,

	/*
	 * Note that colors in X are correct only अगर all video data is
	 * passed through the palette in the DAC.  That is, "indirect
	 * color" must be configured.  This is the हाल क्रम the IBM DAC
	 * used in the 2MB and 4MB cards, at least.
	 */
	अणु BPP8,		0x00 पूर्ण,
	अणु BPP16,	0x01 पूर्ण,
	अणु BPP24,	0x00 पूर्ण,
	अणु BPP32,	0x00 पूर्ण,

	अणु PIXCTL1,	0x05 पूर्ण,
	अणु PIXCTL2,	0x00 पूर्ण,
	अणु SYSCLKN,	0x08 पूर्ण,
	अणु SYSCLKM,	0x4f पूर्ण,
	अणु SYSCLKP,	0x00 पूर्ण,
	अणु SYSCLKC,	0x00 पूर्ण,
	अणु CURSCTL,	0x00 पूर्ण,
	अणु CURSACCTL,	0x01 पूर्ण,
	अणु CURSACATTR,	0xa8 पूर्ण,
	अणु CURS1R,	0xff पूर्ण,
	अणु CURS1G,	0xff पूर्ण,
	अणु CURS1B,	0xff पूर्ण,
	अणु CURS2R,	0xff पूर्ण,
	अणु CURS2G,	0xff पूर्ण,
	अणु CURS2B,	0xff पूर्ण,
	अणु CURS3R,	0xff पूर्ण,
	अणु CURS3G,	0xff पूर्ण,
	अणु CURS3B,	0xff पूर्ण,
	अणु BORDR,	0xff पूर्ण,
	अणु BORDG,	0xff पूर्ण,
	अणु BORDB,	0xff पूर्ण,
	अणु MISCTL1,	0x01 पूर्ण,
	अणु MISCTL2,	0x45 पूर्ण,
	अणु MISCTL3,	0x00 पूर्ण,
	अणु KEYCTL,	0x00 पूर्ण
पूर्ण;

अटल काष्ठा initvalues tvp_initregs[] = अणु
	अणु TVPIRICC,	0x00 पूर्ण,
	अणु TVPIRBRC,	0xe4 पूर्ण,
	अणु TVPIRLAC,	0x06 पूर्ण,
	अणु TVPIRTCC,	0x80 पूर्ण,
	अणु TVPIRMXC,	0x4d पूर्ण,
	अणु TVPIRCLS,	0x05 पूर्ण,
	अणु TVPIRPPG,	0x00 पूर्ण,
	अणु TVPIRGEC,	0x00 पूर्ण,
	अणु TVPIRMIC,	0x08 पूर्ण,
	अणु TVPIRCKL,	0xff पूर्ण,
	अणु TVPIRCKH,	0xff पूर्ण,
	अणु TVPIRCRL,	0xff पूर्ण,
	अणु TVPIRCRH,	0xff पूर्ण,
	अणु TVPIRCGL,	0xff पूर्ण,
	अणु TVPIRCGH,	0xff पूर्ण,
	अणु TVPIRCBL,	0xff पूर्ण,
	अणु TVPIRCBH,	0xff पूर्ण,
	अणु TVPIRCKC,	0x00 पूर्ण,
	अणु TVPIRPLA,	0x00 पूर्ण,
	अणु TVPIRPPD,	0xc0 पूर्ण,
	अणु TVPIRPPD,	0xd5 पूर्ण,
	अणु TVPIRPPD,	0xea पूर्ण,
	अणु TVPIRPLA,	0x00 पूर्ण,
	अणु TVPIRMPD,	0xb9 पूर्ण,
	अणु TVPIRMPD,	0x3a पूर्ण,
	अणु TVPIRMPD,	0xb1 पूर्ण,
	अणु TVPIRPLA,	0x00 पूर्ण,
	अणु TVPIRLPD,	0xc1 पूर्ण,
	अणु TVPIRLPD,	0x3d पूर्ण,
	अणु TVPIRLPD,	0xf3 पूर्ण,
पूर्ण;

काष्ठा imstt_regvals अणु
	__u32 pitch;
	__u16 hes, heb, hsb, ht, ves, veb, vsb, vt, vil;
	__u8 pclk_m, pclk_n, pclk_p;
	/* Values of the tvp which change depending on colormode x resolution */
	__u8 mlc[3];	/* Memory Loop Config 0x39 */
	__u8 lckl_p[3];	/* P value of LCKL PLL */
पूर्ण;

काष्ठा imstt_par अणु
	काष्ठा imstt_regvals init;
	__u32 __iomem *dc_regs;
	अचिन्हित दीर्घ cmap_regs_phys;
	__u8 *cmap_regs;
	__u32 ramdac;
	__u32 palette[16];
पूर्ण;
 
क्रमागत अणु
	IBM = 0,
	TVP = 1
पूर्ण;

#घोषणा INIT_BPP		8
#घोषणा INIT_XRES		640
#घोषणा INIT_YRES		480

अटल पूर्णांक inverse = 0;
अटल अक्षर fontname[40] __initdata = अणु 0 पूर्ण;
#अगर defined(CONFIG_PPC_PMAC)
अटल चिन्हित अक्षर init_vmode = -1, init_cmode = -1;
#पूर्ण_अगर

अटल काष्ठा imstt_regvals tvp_reg_init_2 = अणु
	512,
	0x0002, 0x0006, 0x0026, 0x0028, 0x0003, 0x0016, 0x0196, 0x0197, 0x0196,
	0xec, 0x2a, 0xf3,
	अणु 0x3c, 0x3b, 0x39 पूर्ण, अणु 0xf3, 0xf3, 0xf3 पूर्ण
पूर्ण;

अटल काष्ठा imstt_regvals tvp_reg_init_6 = अणु
	640,
	0x0004, 0x0009, 0x0031, 0x0036, 0x0003, 0x002a, 0x020a, 0x020d, 0x020a,
	0xef, 0x2e, 0xb2,
	अणु 0x39, 0x39, 0x38 पूर्ण, अणु 0xf3, 0xf3, 0xf3 पूर्ण
पूर्ण;

अटल काष्ठा imstt_regvals tvp_reg_init_12 = अणु
	800,
	0x0005, 0x000e, 0x0040, 0x0042, 0x0003, 0x018, 0x270, 0x271, 0x270,
	0xf6, 0x2e, 0xf2,
	अणु 0x3a, 0x39, 0x38 पूर्ण, अणु 0xf3, 0xf3, 0xf3 पूर्ण
पूर्ण;

अटल काष्ठा imstt_regvals tvp_reg_init_13 = अणु
	832,
	0x0004, 0x0011, 0x0045, 0x0048, 0x0003, 0x002a, 0x029a, 0x029b, 0x0000,
	0xfe, 0x3e, 0xf1,
	अणु 0x39, 0x38, 0x38 पूर्ण, अणु 0xf3, 0xf3, 0xf2 पूर्ण
पूर्ण;

अटल काष्ठा imstt_regvals tvp_reg_init_17 = अणु
	1024,
	0x0006, 0x0210, 0x0250, 0x0053, 0x1003, 0x0021, 0x0321, 0x0324, 0x0000,
	0xfc, 0x3a, 0xf1,
	अणु 0x39, 0x38, 0x38 पूर्ण, अणु 0xf3, 0xf3, 0xf2 पूर्ण
पूर्ण;

अटल काष्ठा imstt_regvals tvp_reg_init_18 = अणु
	1152,
  	0x0009, 0x0011, 0x059, 0x5b, 0x0003, 0x0031, 0x0397, 0x039a, 0x0000, 
	0xfd, 0x3a, 0xf1,
	अणु 0x39, 0x38, 0x38 पूर्ण, अणु 0xf3, 0xf3, 0xf2 पूर्ण
पूर्ण;

अटल काष्ठा imstt_regvals tvp_reg_init_19 = अणु
	1280,
	0x0009, 0x0016, 0x0066, 0x0069, 0x0003, 0x0027, 0x03e7, 0x03e8, 0x03e7,
	0xf7, 0x36, 0xf0,
	अणु 0x38, 0x38, 0x38 पूर्ण, अणु 0xf3, 0xf2, 0xf1 पूर्ण
पूर्ण;

अटल काष्ठा imstt_regvals tvp_reg_init_20 = अणु
	1280,
	0x0009, 0x0018, 0x0068, 0x006a, 0x0003, 0x0029, 0x0429, 0x042a, 0x0000,
	0xf0, 0x2d, 0xf0,
	अणु 0x38, 0x38, 0x38 पूर्ण, अणु 0xf3, 0xf2, 0xf1 पूर्ण
पूर्ण;

/*
 * PCI driver prototypes
 */
अटल पूर्णांक imsttfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent);
अटल व्योम imsttfb_हटाओ(काष्ठा pci_dev *pdev);

/*
 * Register access
 */
अटल अंतरभूत u32 पढ़ो_reg_le32(अस्थिर u32 __iomem *base, पूर्णांक regindex)
अणु
#अगर_घोषित __घातerpc__
	वापस in_le32(base + regindex);
#अन्यथा
	वापस पढ़ोl(base + regindex);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_reg_le32(अस्थिर u32 __iomem *base, पूर्णांक regindex, u32 val)
अणु
#अगर_घोषित __घातerpc__
	out_le32(base + regindex, val);
#अन्यथा
	ग_लिखोl(val, base + regindex);
#पूर्ण_अगर
पूर्ण

अटल __u32
अ_लोlkMHz(काष्ठा imstt_par *par)
अणु
	__u32 clk_m, clk_n, clk_p;

	clk_m = par->init.pclk_m;
	clk_n = par->init.pclk_n;
	clk_p = par->init.pclk_p;

	वापस 20 * (clk_m + 1) / ((clk_n + 1) * (clk_p ? 2 * clk_p : 1));
पूर्ण

अटल व्योम
setclkMHz(काष्ठा imstt_par *par, __u32 MHz)
अणु
	__u32 clk_m, clk_n, x, stage, spilled;

	clk_m = clk_n = 0;
	stage = spilled = 0;
	क्रम (;;) अणु
		चयन (stage) अणु
			हाल 0:
				clk_m++;
				अवरोध;
			हाल 1:
				clk_n++;
				अवरोध;
		पूर्ण
		x = 20 * (clk_m + 1) / (clk_n + 1);
		अगर (x == MHz)
			अवरोध;
		अगर (x > MHz) अणु
			spilled = 1;
			stage = 1;
		पूर्ण अन्यथा अगर (spilled && x < MHz) अणु
			stage = 0;
		पूर्ण
	पूर्ण

	par->init.pclk_m = clk_m;
	par->init.pclk_n = clk_n;
	par->init.pclk_p = 0;
पूर्ण

अटल काष्ठा imstt_regvals *
compute_imstt_regvals_ibm(काष्ठा imstt_par *par, पूर्णांक xres, पूर्णांक yres)
अणु
	काष्ठा imstt_regvals *init = &par->init;
	__u32 MHz, hes, heb, veb, htp, vtp;

	चयन (xres) अणु
		हाल 640:
			hes = 0x0008; heb = 0x0012; veb = 0x002a; htp = 10; vtp = 2;
			MHz = 30 /* .25 */ ;
			अवरोध;
		हाल 832:
			hes = 0x0005; heb = 0x0020; veb = 0x0028; htp = 8; vtp = 3;
			MHz = 57 /* .27_ */ ;
			अवरोध;
		हाल 1024:
			hes = 0x000a; heb = 0x001c; veb = 0x0020; htp = 8; vtp = 3;
			MHz = 80;
			अवरोध;
		हाल 1152:
			hes = 0x0012; heb = 0x0022; veb = 0x0031; htp = 4; vtp = 3;
			MHz = 101 /* .6_ */ ;
			अवरोध;
		हाल 1280:
			hes = 0x0012; heb = 0x002f; veb = 0x0029; htp = 4; vtp = 1;
			MHz = yres == 960 ? 126 : 135;
			अवरोध;
		हाल 1600:
			hes = 0x0018; heb = 0x0040; veb = 0x002a; htp = 4; vtp = 3;
			MHz = 200;
			अवरोध;
		शेष:
			वापस शून्य;
	पूर्ण

	setclkMHz(par, MHz);

	init->hes = hes;
	init->heb = heb;
	init->hsb = init->heb + (xres >> 3);
	init->ht = init->hsb + htp;
	init->ves = 0x0003;
	init->veb = veb;
	init->vsb = init->veb + yres;
	init->vt = init->vsb + vtp;
	init->vil = init->vsb;

	init->pitch = xres;
	वापस init;
पूर्ण

अटल काष्ठा imstt_regvals *
compute_imstt_regvals_tvp(काष्ठा imstt_par *par, पूर्णांक xres, पूर्णांक yres)
अणु
	काष्ठा imstt_regvals *init;

	चयन (xres) अणु
		हाल 512:
			init = &tvp_reg_init_2;
			अवरोध;
		हाल 640:
			init = &tvp_reg_init_6;
			अवरोध;
		हाल 800:
			init = &tvp_reg_init_12;
			अवरोध;
		हाल 832:
			init = &tvp_reg_init_13;
			अवरोध;
		हाल 1024:
			init = &tvp_reg_init_17;
			अवरोध;
		हाल 1152:
			init = &tvp_reg_init_18;
			अवरोध;
		हाल 1280:
			init = yres == 960 ? &tvp_reg_init_19 : &tvp_reg_init_20;
			अवरोध;
		शेष:
			वापस शून्य;
	पूर्ण
	par->init = *init;
	वापस init;
पूर्ण

अटल काष्ठा imstt_regvals *
compute_imstt_regvals (काष्ठा imstt_par *par, u_पूर्णांक xres, u_पूर्णांक yres)
अणु
	अगर (par->ramdac == IBM)
		वापस compute_imstt_regvals_ibm(par, xres, yres);
	अन्यथा
		वापस compute_imstt_regvals_tvp(par, xres, yres);
पूर्ण

अटल व्योम
set_imstt_regvals_ibm (काष्ठा imstt_par *par, u_पूर्णांक bpp)
अणु
	काष्ठा imstt_regvals *init = &par->init;
	__u8 pक्रमmat = (bpp >> 3) + 2;

	par->cmap_regs[PIDXHI] = 0;		eieio();
	par->cmap_regs[PIDXLO] = PIXM0;		eieio();
	par->cmap_regs[PIDXDATA] = init->pclk_m;eieio();
	par->cmap_regs[PIDXLO] = PIXN0;		eieio();
	par->cmap_regs[PIDXDATA] = init->pclk_n;eieio();
	par->cmap_regs[PIDXLO] = PIXP0;		eieio();
	par->cmap_regs[PIDXDATA] = init->pclk_p;eieio();
	par->cmap_regs[PIDXLO] = PIXC0;		eieio();
	par->cmap_regs[PIDXDATA] = 0x02;	eieio();

	par->cmap_regs[PIDXLO] = PIXFMT;	eieio();
	par->cmap_regs[PIDXDATA] = pक्रमmat;	eieio();
पूर्ण

अटल व्योम
set_imstt_regvals_tvp (काष्ठा imstt_par *par, u_पूर्णांक bpp)
अणु
	काष्ठा imstt_regvals *init = &par->init;
	__u8 tcc, mxc, lckl_n, mic;
	__u8 mlc, lckl_p;

	चयन (bpp) अणु
		शेष:
		हाल 8:
			tcc = 0x80;
			mxc = 0x4d;
			lckl_n = 0xc1;
			mlc = init->mlc[0];
			lckl_p = init->lckl_p[0];
			अवरोध;
		हाल 16:
			tcc = 0x44;
			mxc = 0x55;
			lckl_n = 0xe1;
			mlc = init->mlc[1];
			lckl_p = init->lckl_p[1];
			अवरोध;
		हाल 24:
			tcc = 0x5e;
			mxc = 0x5d;
			lckl_n = 0xf1;
			mlc = init->mlc[2];
			lckl_p = init->lckl_p[2];
			अवरोध;
		हाल 32:
			tcc = 0x46;
			mxc = 0x5d;
			lckl_n = 0xf1;
			mlc = init->mlc[2];
			lckl_p = init->lckl_p[2];
			अवरोध;
	पूर्ण
	mic = 0x08;

	par->cmap_regs[TVPADDRW] = TVPIRPLA;		eieio();
	par->cmap_regs[TVPIDATA] = 0x00;		eieio();
	par->cmap_regs[TVPADDRW] = TVPIRPPD;		eieio();
	par->cmap_regs[TVPIDATA] = init->pclk_m;	eieio();
	par->cmap_regs[TVPADDRW] = TVPIRPPD;		eieio();
	par->cmap_regs[TVPIDATA] = init->pclk_n;	eieio();
	par->cmap_regs[TVPADDRW] = TVPIRPPD;		eieio();
	par->cmap_regs[TVPIDATA] = init->pclk_p;	eieio();

	par->cmap_regs[TVPADDRW] = TVPIRTCC;		eieio();
	par->cmap_regs[TVPIDATA] = tcc;			eieio();
	par->cmap_regs[TVPADDRW] = TVPIRMXC;		eieio();
	par->cmap_regs[TVPIDATA] = mxc;			eieio();
	par->cmap_regs[TVPADDRW] = TVPIRMIC;		eieio();
	par->cmap_regs[TVPIDATA] = mic;			eieio();

	par->cmap_regs[TVPADDRW] = TVPIRPLA;		eieio();
	par->cmap_regs[TVPIDATA] = 0x00;		eieio();
	par->cmap_regs[TVPADDRW] = TVPIRLPD;		eieio();
	par->cmap_regs[TVPIDATA] = lckl_n;		eieio();

	par->cmap_regs[TVPADDRW] = TVPIRPLA;		eieio();
	par->cmap_regs[TVPIDATA] = 0x15;		eieio();
	par->cmap_regs[TVPADDRW] = TVPIRMLC;		eieio();
	par->cmap_regs[TVPIDATA] = mlc;			eieio();

	par->cmap_regs[TVPADDRW] = TVPIRPLA;		eieio();
	par->cmap_regs[TVPIDATA] = 0x2a;		eieio();
	par->cmap_regs[TVPADDRW] = TVPIRLPD;		eieio();
	par->cmap_regs[TVPIDATA] = lckl_p;		eieio();
पूर्ण

अटल व्योम
set_imstt_regvals (काष्ठा fb_info *info, u_पूर्णांक bpp)
अणु
	काष्ठा imstt_par *par = info->par;
	काष्ठा imstt_regvals *init = &par->init;
	__u32 ctl, pitch, byteswap, scr;

	अगर (par->ramdac == IBM)
		set_imstt_regvals_ibm(par, bpp);
	अन्यथा
		set_imstt_regvals_tvp(par, bpp);

  /*
   * From what I (jsk) can gather poking around with MacsBug,
   * bits 8 and 9 in the SCR रेजिस्टर control endianness
   * correction (byte swapping).  These bits must be set according
   * to the color depth as follows:
   *     Color depth    Bit 9   Bit 8
   *     ==========     =====   =====
   *        8bpp          0       0
   *       16bpp          0       1
   *       32bpp          1       1
   */
	चयन (bpp) अणु
		शेष:
		हाल 8:
			ctl = 0x17b1;
			pitch = init->pitch >> 2;
			byteswap = 0x000;
			अवरोध;
		हाल 16:
			ctl = 0x17b3;
			pitch = init->pitch >> 1;
			byteswap = 0x100;
			अवरोध;
		हाल 24:
			ctl = 0x17b9;
			pitch = init->pitch - (init->pitch >> 2);
			byteswap = 0x200;
			अवरोध;
		हाल 32:
			ctl = 0x17b5;
			pitch = init->pitch;
			byteswap = 0x300;
			अवरोध;
	पूर्ण
	अगर (par->ramdac == TVP)
		ctl -= 0x30;

	ग_लिखो_reg_le32(par->dc_regs, HES, init->hes);
	ग_लिखो_reg_le32(par->dc_regs, HEB, init->heb);
	ग_लिखो_reg_le32(par->dc_regs, HSB, init->hsb);
	ग_लिखो_reg_le32(par->dc_regs, HT, init->ht);
	ग_लिखो_reg_le32(par->dc_regs, VES, init->ves);
	ग_लिखो_reg_le32(par->dc_regs, VEB, init->veb);
	ग_लिखो_reg_le32(par->dc_regs, VSB, init->vsb);
	ग_लिखो_reg_le32(par->dc_regs, VT, init->vt);
	ग_लिखो_reg_le32(par->dc_regs, VIL, init->vil);
	ग_लिखो_reg_le32(par->dc_regs, HCIV, 1);
	ग_लिखो_reg_le32(par->dc_regs, VCIV, 1);
	ग_लिखो_reg_le32(par->dc_regs, TCDR, 4);
	ग_लिखो_reg_le32(par->dc_regs, RRCIV, 1);
	ग_लिखो_reg_le32(par->dc_regs, RRSC, 0x980);
	ग_लिखो_reg_le32(par->dc_regs, RRCR, 0x11);

	अगर (par->ramdac == IBM) अणु
		ग_लिखो_reg_le32(par->dc_regs, HRIR, 0x0100);
		ग_लिखो_reg_le32(par->dc_regs, CMR, 0x00ff);
		ग_लिखो_reg_le32(par->dc_regs, SRGCTL, 0x0073);
	पूर्ण अन्यथा अणु
		ग_लिखो_reg_le32(par->dc_regs, HRIR, 0x0200);
		ग_लिखो_reg_le32(par->dc_regs, CMR, 0x01ff);
		ग_लिखो_reg_le32(par->dc_regs, SRGCTL, 0x0003);
	पूर्ण

	चयन (info->fix.smem_len) अणु
		हाल 0x200000:
			scr = 0x059d | byteswap;
			अवरोध;
		/* हाल 0x400000:
		   हाल 0x800000: */
		शेष:
			pitch >>= 1;
			scr = 0x150dd | byteswap;
			अवरोध;
	पूर्ण

	ग_लिखो_reg_le32(par->dc_regs, SCR, scr);
	ग_लिखो_reg_le32(par->dc_regs, SPR, pitch);
	ग_लिखो_reg_le32(par->dc_regs, STGCTL, ctl);
पूर्ण

अटल अंतरभूत व्योम
set_offset (काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	काष्ठा imstt_par *par = info->par;
	__u32 off = var->yoffset * (info->fix.line_length >> 3)
		    + ((var->xoffset * (info->var.bits_per_pixel >> 3)) >> 3);
	ग_लिखो_reg_le32(par->dc_regs, SSR, off);
पूर्ण

अटल अंतरभूत व्योम
set_555 (काष्ठा imstt_par *par)
अणु
	अगर (par->ramdac == IBM) अणु
		par->cmap_regs[PIDXHI] = 0;		eieio();
		par->cmap_regs[PIDXLO] = BPP16;		eieio();
		par->cmap_regs[PIDXDATA] = 0x01;	eieio();
	पूर्ण अन्यथा अणु
		par->cmap_regs[TVPADDRW] = TVPIRTCC;	eieio();
		par->cmap_regs[TVPIDATA] = 0x44;	eieio();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
set_565 (काष्ठा imstt_par *par)
अणु
	अगर (par->ramdac == IBM) अणु
		par->cmap_regs[PIDXHI] = 0;		eieio();
		par->cmap_regs[PIDXLO] = BPP16;		eieio();
		par->cmap_regs[PIDXDATA] = 0x03;	eieio();
	पूर्ण अन्यथा अणु
		par->cmap_regs[TVPADDRW] = TVPIRTCC;	eieio();
		par->cmap_regs[TVPIDATA] = 0x45;	eieio();
	पूर्ण
पूर्ण

अटल पूर्णांक
imsttfb_check_var(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	अगर ((var->bits_per_pixel != 8 && var->bits_per_pixel != 16
	    && var->bits_per_pixel != 24 && var->bits_per_pixel != 32)
	    || var->xres_भव < var->xres || var->yres_भव < var->yres
	    || var->nonstd
	    || (var->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTERLACED)
		वापस -EINVAL;

	अगर ((var->xres * var->yres) * (var->bits_per_pixel >> 3) > info->fix.smem_len
	    || (var->xres_भव * var->yres_भव) * (var->bits_per_pixel >> 3) > info->fix.smem_len)
		वापस -EINVAL;

	चयन (var->bits_per_pixel) अणु
		हाल 8:
			var->red.offset = 0;
			var->red.length = 8;
			var->green.offset = 0;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 0;
			var->transp.length = 0;
			अवरोध;
		हाल 16:	/* RGB 555 or 565 */
			अगर (var->green.length != 6)
				var->red.offset = 10;
			var->red.length = 5;
			var->green.offset = 5;
			अगर (var->green.length != 6)
				var->green.length = 5;
			var->blue.offset = 0;
			var->blue.length = 5;
			var->transp.offset = 0;
			var->transp.length = 0;
			अवरोध;
		हाल 24:	/* RGB 888 */
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 0;
			var->transp.length = 0;
			अवरोध;
		हाल 32:	/* RGBA 8888 */
			var->red.offset = 16;
			var->red.length = 8;
			var->green.offset = 8;
			var->green.length = 8;
			var->blue.offset = 0;
			var->blue.length = 8;
			var->transp.offset = 24;
			var->transp.length = 8;
			अवरोध;
	पूर्ण

	अगर (var->yres == var->yres_भव) अणु
		__u32 vram = (info->fix.smem_len - (PAGE_SIZE << 2));
		var->yres_भव = ((vram << 3) / var->bits_per_pixel) / var->xres_भव;
		अगर (var->yres_भव < var->yres)
			var->yres_भव = var->yres;
	पूर्ण

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;
	var->height = -1;
	var->width = -1;
	var->vmode = FB_VMODE_NONINTERLACED;
	var->left_margin = var->right_margin = 16;
	var->upper_margin = var->lower_margin = 16;
	var->hsync_len = var->vsync_len = 8;
	वापस 0;
पूर्ण

अटल पूर्णांक
imsttfb_set_par(काष्ठा fb_info *info) 
अणु
	काष्ठा imstt_par *par = info->par;
		
	अगर (!compute_imstt_regvals(par, info->var.xres, info->var.yres))
		वापस -EINVAL;

	अगर (info->var.green.length == 6)
		set_565(par);
	अन्यथा
		set_555(par);
	set_imstt_regvals(info, info->var.bits_per_pixel);
	info->var.pixघड़ी = 1000000 / अ_लोlkMHz(par);
	वापस 0;
पूर्ण

अटल पूर्णांक
imsttfb_setcolreg (u_पूर्णांक regno, u_पूर्णांक red, u_पूर्णांक green, u_पूर्णांक blue,
		   u_पूर्णांक transp, काष्ठा fb_info *info)
अणु
	काष्ठा imstt_par *par = info->par;
	u_पूर्णांक bpp = info->var.bits_per_pixel;

	अगर (regno > 255)
		वापस 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	/* PADDRW/PDATA are the same as TVPPADDRW/TVPPDATA */
	अगर (0 && bpp == 16)	/* screws up X */
		par->cmap_regs[PADDRW] = regno << 3;
	अन्यथा
		par->cmap_regs[PADDRW] = regno;
	eieio();

	par->cmap_regs[PDATA] = red;	eieio();
	par->cmap_regs[PDATA] = green;	eieio();
	par->cmap_regs[PDATA] = blue;	eieio();

	अगर (regno < 16)
		चयन (bpp) अणु
			हाल 16:
				par->palette[regno] =
					(regno << (info->var.green.length ==
					5 ? 10 : 11)) | (regno << 5) | regno;
				अवरोध;
			हाल 24:
				par->palette[regno] =
					(regno << 16) | (regno << 8) | regno;
				अवरोध;
			हाल 32: अणु
				पूर्णांक i = (regno << 8) | regno;
				par->palette[regno] = (i << 16) |i;
				अवरोध;
			पूर्ण
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
imsttfb_pan_display(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info)
अणु
	अगर (var->xoffset + info->var.xres > info->var.xres_भव
	    || var->yoffset + info->var.yres > info->var.yres_भव)
		वापस -EINVAL;

	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;
	set_offset(var, info);
	वापस 0;
पूर्ण

अटल पूर्णांक 
imsttfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	काष्ठा imstt_par *par = info->par;
	__u32 ctrl;

	ctrl = पढ़ो_reg_le32(par->dc_regs, STGCTL);
	अगर (blank > 0) अणु
		चयन (blank) अणु
		हाल FB_BLANK_NORMAL:
		हाल FB_BLANK_POWERDOWN:
			ctrl &= ~0x00000380;
			अगर (par->ramdac == IBM) अणु
				par->cmap_regs[PIDXHI] = 0;		eieio();
				par->cmap_regs[PIDXLO] = MISCTL2;	eieio();
				par->cmap_regs[PIDXDATA] = 0x55;	eieio();
				par->cmap_regs[PIDXLO] = MISCTL1;	eieio();
				par->cmap_regs[PIDXDATA] = 0x11;	eieio();
				par->cmap_regs[PIDXLO] = SYNCCTL;	eieio();
				par->cmap_regs[PIDXDATA] = 0x0f;	eieio();
				par->cmap_regs[PIDXLO] = PWRMNGMT;	eieio();
				par->cmap_regs[PIDXDATA] = 0x1f;	eieio();
				par->cmap_regs[PIDXLO] = CLKCTL;	eieio();
				par->cmap_regs[PIDXDATA] = 0xc0;
			पूर्ण
			अवरोध;
		हाल FB_BLANK_VSYNC_SUSPEND:
			ctrl &= ~0x00000020;
			अवरोध;
		हाल FB_BLANK_HSYNC_SUSPEND:
			ctrl &= ~0x00000010;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (par->ramdac == IBM) अणु
			ctrl |= 0x000017b0;
			par->cmap_regs[PIDXHI] = 0;		eieio();
			par->cmap_regs[PIDXLO] = CLKCTL;	eieio();
			par->cmap_regs[PIDXDATA] = 0x01;	eieio();
			par->cmap_regs[PIDXLO] = PWRMNGMT;	eieio();
			par->cmap_regs[PIDXDATA] = 0x00;	eieio();
			par->cmap_regs[PIDXLO] = SYNCCTL;	eieio();
			par->cmap_regs[PIDXDATA] = 0x00;	eieio();
			par->cmap_regs[PIDXLO] = MISCTL1;	eieio();
			par->cmap_regs[PIDXDATA] = 0x01;	eieio();
			par->cmap_regs[PIDXLO] = MISCTL2;	eieio();
			par->cmap_regs[PIDXDATA] = 0x45;	eieio();
		पूर्ण अन्यथा
			ctrl |= 0x00001780;
	पूर्ण
	ग_लिखो_reg_le32(par->dc_regs, STGCTL, ctrl);
	वापस 0;
पूर्ण

अटल व्योम
imsttfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु 
	काष्ठा imstt_par *par = info->par;
	__u32 Bpp, line_pitch, bgc, dx, dy, width, height;

	bgc = rect->color;
	bgc |= (bgc << 8);
	bgc |= (bgc << 16);

	Bpp = info->var.bits_per_pixel >> 3,
	line_pitch = info->fix.line_length;

	dy = rect->dy * line_pitch;
	dx = rect->dx * Bpp;
	height = rect->height;
	height--;
	width = rect->width * Bpp;
	width--;

	अगर (rect->rop == ROP_COPY) अणु
		जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x80);
		ग_लिखो_reg_le32(par->dc_regs, DSA, dy + dx);
		ग_लिखो_reg_le32(par->dc_regs, CNT, (height << 16) | width);
		ग_लिखो_reg_le32(par->dc_regs, DP_OCTL, line_pitch);
		ग_लिखो_reg_le32(par->dc_regs, BI, 0xffffffff);
		ग_लिखो_reg_le32(par->dc_regs, MBC, 0xffffffff);
		ग_लिखो_reg_le32(par->dc_regs, CLR, bgc);
		ग_लिखो_reg_le32(par->dc_regs, BLTCTL, 0x840); /* 0x200000 */
		जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x80);
		जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x40);
	पूर्ण अन्यथा अणु
		जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x80);
		ग_लिखो_reg_le32(par->dc_regs, DSA, dy + dx);
		ग_लिखो_reg_le32(par->dc_regs, S1SA, dy + dx);
		ग_लिखो_reg_le32(par->dc_regs, CNT, (height << 16) | width);
		ग_लिखो_reg_le32(par->dc_regs, DP_OCTL, line_pitch);
		ग_लिखो_reg_le32(par->dc_regs, SP, line_pitch);
		ग_लिखो_reg_le32(par->dc_regs, BLTCTL, 0x40005);
		जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x80);
		जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x40);
	पूर्ण
पूर्ण

अटल व्योम
imsttfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area)
अणु
	काष्ठा imstt_par *par = info->par;
	__u32 Bpp, line_pitch, fb_offset_old, fb_offset_new, sp, dp_octl;
 	__u32 cnt, bltctl, sx, sy, dx, dy, height, width;

	Bpp = info->var.bits_per_pixel >> 3,

	sx = area->sx * Bpp;
	sy = area->sy;
	dx = area->dx * Bpp;
	dy = area->dy;
	height = area->height;
	height--;
	width = area->width * Bpp;
	width--;

	line_pitch = info->fix.line_length;
	bltctl = 0x05;
	sp = line_pitch << 16;
	cnt = height << 16;

	अगर (sy < dy) अणु
		sy += height;
		dy += height;
		sp |= -(line_pitch) & 0xffff;
		dp_octl = -(line_pitch) & 0xffff;
	पूर्ण अन्यथा अणु
		sp |= line_pitch;
		dp_octl = line_pitch;
	पूर्ण
	अगर (sx < dx) अणु
		sx += width;
		dx += width;
		bltctl |= 0x80;
		cnt |= -(width) & 0xffff;
	पूर्ण अन्यथा अणु
		cnt |= width;
	पूर्ण
	fb_offset_old = sy * line_pitch + sx;
	fb_offset_new = dy * line_pitch + dx;

	जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x80);
	ग_लिखो_reg_le32(par->dc_regs, S1SA, fb_offset_old);
	ग_लिखो_reg_le32(par->dc_regs, SP, sp);
	ग_लिखो_reg_le32(par->dc_regs, DSA, fb_offset_new);
	ग_लिखो_reg_le32(par->dc_regs, CNT, cnt);
	ग_लिखो_reg_le32(par->dc_regs, DP_OCTL, dp_octl);
	ग_लिखो_reg_le32(par->dc_regs, BLTCTL, bltctl);
	जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x80);
	जबतक(पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x40);
पूर्ण

#अगर 0
अटल पूर्णांक
imsttfb_load_cursor_image(काष्ठा imstt_par *par, पूर्णांक width, पूर्णांक height, __u8 fgc)
अणु
	u_पूर्णांक x, y;

	अगर (width > 32 || height > 32)
		वापस -EINVAL;

	अगर (par->ramdac == IBM) अणु
		par->cmap_regs[PIDXHI] = 1;	eieio();
		क्रम (x = 0; x < 0x100; x++) अणु
			par->cmap_regs[PIDXLO] = x;		eieio();
			par->cmap_regs[PIDXDATA] = 0x00;	eieio();
		पूर्ण
		par->cmap_regs[PIDXHI] = 1;	eieio();
		क्रम (y = 0; y < height; y++)
			क्रम (x = 0; x < width >> 2; x++) अणु
				par->cmap_regs[PIDXLO] = x + y * 8;	eieio();
				par->cmap_regs[PIDXDATA] = 0xff;	eieio();
			पूर्ण
		par->cmap_regs[PIDXHI] = 0;		eieio();
		par->cmap_regs[PIDXLO] = CURS1R;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS1G;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS1B;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS2R;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS2G;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS2B;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS3R;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS3G;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
		par->cmap_regs[PIDXLO] = CURS3B;	eieio();
		par->cmap_regs[PIDXDATA] = fgc;		eieio();
	पूर्ण अन्यथा अणु
		par->cmap_regs[TVPADDRW] = TVPIRICC;	eieio();
		par->cmap_regs[TVPIDATA] &= 0x03;	eieio();
		par->cmap_regs[TVPADDRW] = 0;		eieio();
		क्रम (x = 0; x < 0x200; x++) अणु
			par->cmap_regs[TVPCRDAT] = 0x00;	eieio();
		पूर्ण
		क्रम (x = 0; x < 0x200; x++) अणु
			par->cmap_regs[TVPCRDAT] = 0xff;	eieio();
		पूर्ण
		par->cmap_regs[TVPADDRW] = TVPIRICC;	eieio();
		par->cmap_regs[TVPIDATA] &= 0x03;	eieio();
		क्रम (y = 0; y < height; y++)
			क्रम (x = 0; x < width >> 3; x++) अणु
				par->cmap_regs[TVPADDRW] = x + y * 8;	eieio();
				par->cmap_regs[TVPCRDAT] = 0xff;		eieio();
			पूर्ण
		par->cmap_regs[TVPADDRW] = TVPIRICC;	eieio();
		par->cmap_regs[TVPIDATA] |= 0x08;	eieio();
		क्रम (y = 0; y < height; y++)
			क्रम (x = 0; x < width >> 3; x++) अणु
				par->cmap_regs[TVPADDRW] = x + y * 8;	eieio();
				par->cmap_regs[TVPCRDAT] = 0xff;		eieio();
			पूर्ण
		par->cmap_regs[TVPCADRW] = 0x00;	eieio();
		क्रम (x = 0; x < 12; x++) अणु
			par->cmap_regs[TVPCDATA] = fgc;
			eieio();
		पूर्ण
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम
imstt_set_cursor(काष्ठा imstt_par *par, काष्ठा fb_image *d, पूर्णांक on)
अणु
	अगर (par->ramdac == IBM) अणु
		par->cmap_regs[PIDXHI] = 0;	eieio();
		अगर (!on) अणु
			par->cmap_regs[PIDXLO] = CURSCTL;	eieio();
			par->cmap_regs[PIDXDATA] = 0x00;	eieio();
		पूर्ण अन्यथा अणु
			par->cmap_regs[PIDXLO] = CURSXHI;	eieio();
			par->cmap_regs[PIDXDATA] = d->dx >> 8;	eieio();
			par->cmap_regs[PIDXLO] = CURSXLO;	eieio();
			par->cmap_regs[PIDXDATA] = d->dx & 0xff;eieio();
			par->cmap_regs[PIDXLO] = CURSYHI;	eieio();
			par->cmap_regs[PIDXDATA] = d->dy >> 8;	eieio();
			par->cmap_regs[PIDXLO] = CURSYLO;	eieio();
			par->cmap_regs[PIDXDATA] = d->dy & 0xff;eieio();
			par->cmap_regs[PIDXLO] = CURSCTL;	eieio();
			par->cmap_regs[PIDXDATA] = 0x02;	eieio();
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!on) अणु
			par->cmap_regs[TVPADDRW] = TVPIRICC;	eieio();
			par->cmap_regs[TVPIDATA] = 0x00;	eieio();
		पूर्ण अन्यथा अणु
			__u16 x = d->dx + 0x40, y = d->dy + 0x40;

			par->cmap_regs[TVPCXPOH] = x >> 8;	eieio();
			par->cmap_regs[TVPCXPOL] = x & 0xff;	eieio();
			par->cmap_regs[TVPCYPOH] = y >> 8;	eieio();
			par->cmap_regs[TVPCYPOL] = y & 0xff;	eieio();
			par->cmap_regs[TVPADDRW] = TVPIRICC;	eieio();
			par->cmap_regs[TVPIDATA] = 0x02;	eieio();
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक 
imsttfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा imstt_par *par = info->par;
        u32 flags = cursor->set, fg, bg, xx, yy;

	अगर (cursor->dest == शून्य && cursor->rop == ROP_XOR)
		वापस 1;
	
	imstt_set_cursor(info, cursor, 0);

	अगर (flags & FB_CUR_SETPOS) अणु
		xx = cursor->image.dx - info->var.xoffset;
		yy = cursor->image.dy - info->var.yoffset;
	पूर्ण

	अगर (flags & FB_CUR_SETSIZE) अणु
        पूर्ण

        अगर (flags & (FB_CUR_SETSHAPE | FB_CUR_SETCMAP)) अणु
                पूर्णांक fg_idx = cursor->image.fg_color;
                पूर्णांक width = (cursor->image.width+7)/8;
                u8 *dat = (u8 *) cursor->image.data;
                u8 *dst = (u8 *) cursor->dest;
                u8 *msk = (u8 *) cursor->mask;

                चयन (cursor->rop) अणु
                हाल ROP_XOR:
                        क्रम (i = 0; i < cursor->image.height; i++) अणु
                                क्रम (j = 0; j < width; j++) अणु
                                        d_idx = i * MAX_CURS/8  + j;
                                        data[d_idx] =  byte_rev[dat[s_idx] ^
                                                                dst[s_idx]];
                                        mask[d_idx] = byte_rev[msk[s_idx]];
                                        s_idx++;
                                पूर्ण
                        पूर्ण
                        अवरोध;
                हाल ROP_COPY:
                शेष:
                        क्रम (i = 0; i < cursor->image.height; i++) अणु
                                क्रम (j = 0; j < width; j++) अणु
                                        d_idx = i * MAX_CURS/8 + j;
                                        data[d_idx] = byte_rev[dat[s_idx]];
                                        mask[d_idx] = byte_rev[msk[s_idx]];
                                        s_idx++;
                                पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण

		fg = ((info->cmap.red[fg_idx] & 0xf8) << 7) |
                     ((info->cmap.green[fg_idx] & 0xf8) << 2) |
                     ((info->cmap.blue[fg_idx] & 0xf8) >> 3) | 1 << 15;

		imsttfb_load_cursor_image(par, xx, yy, fgc);
	पूर्ण
	अगर (cursor->enable)
		imstt_set_cursor(info, cursor, 1);
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा FBIMSTT_SETREG		0x545401
#घोषणा FBIMSTT_GETREG		0x545402
#घोषणा FBIMSTT_SETCMAPREG	0x545403
#घोषणा FBIMSTT_GETCMAPREG	0x545404
#घोषणा FBIMSTT_SETIDXREG	0x545405
#घोषणा FBIMSTT_GETIDXREG	0x545406

अटल पूर्णांक
imsttfb_ioctl(काष्ठा fb_info *info, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा imstt_par *par = info->par;
	व्योम __user *argp = (व्योम __user *)arg;
	__u32 reg[2];
	__u8 idx[2];

	चयन (cmd) अणु
		हाल FBIMSTT_SETREG:
			अगर (copy_from_user(reg, argp, 8) || reg[0] > (0x1000 - माप(reg[0])) / माप(reg[0]))
				वापस -EFAULT;
			ग_लिखो_reg_le32(par->dc_regs, reg[0], reg[1]);
			वापस 0;
		हाल FBIMSTT_GETREG:
			अगर (copy_from_user(reg, argp, 4) || reg[0] > (0x1000 - माप(reg[0])) / माप(reg[0]))
				वापस -EFAULT;
			reg[1] = पढ़ो_reg_le32(par->dc_regs, reg[0]);
			अगर (copy_to_user((व्योम __user *)(arg + 4), &reg[1], 4))
				वापस -EFAULT;
			वापस 0;
		हाल FBIMSTT_SETCMAPREG:
			अगर (copy_from_user(reg, argp, 8) || reg[0] > (0x1000 - माप(reg[0])) / माप(reg[0]))
				वापस -EFAULT;
			ग_लिखो_reg_le32(((u_पूर्णांक __iomem *)par->cmap_regs), reg[0], reg[1]);
			वापस 0;
		हाल FBIMSTT_GETCMAPREG:
			अगर (copy_from_user(reg, argp, 4) || reg[0] > (0x1000 - माप(reg[0])) / माप(reg[0]))
				वापस -EFAULT;
			reg[1] = पढ़ो_reg_le32(((u_पूर्णांक __iomem *)par->cmap_regs), reg[0]);
			अगर (copy_to_user((व्योम __user *)(arg + 4), &reg[1], 4))
				वापस -EFAULT;
			वापस 0;
		हाल FBIMSTT_SETIDXREG:
			अगर (copy_from_user(idx, argp, 2))
				वापस -EFAULT;
			par->cmap_regs[PIDXHI] = 0;		eieio();
			par->cmap_regs[PIDXLO] = idx[0];	eieio();
			par->cmap_regs[PIDXDATA] = idx[1];	eieio();
			वापस 0;
		हाल FBIMSTT_GETIDXREG:
			अगर (copy_from_user(idx, argp, 1))
				वापस -EFAULT;
			par->cmap_regs[PIDXHI] = 0;		eieio();
			par->cmap_regs[PIDXLO] = idx[0];	eieio();
			idx[1] = par->cmap_regs[PIDXDATA];
			अगर (copy_to_user((व्योम __user *)(arg + 1), &idx[1], 1))
				वापस -EFAULT;
			वापस 0;
		शेष:
			वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pci_device_id imsttfb_pci_tbl[] = अणु
	अणु PCI_VENDOR_ID_IMS, PCI_DEVICE_ID_IMS_TT128,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IBM पूर्ण,
	अणु PCI_VENDOR_ID_IMS, PCI_DEVICE_ID_IMS_TT3D,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, TVP पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, imsttfb_pci_tbl);

अटल काष्ठा pci_driver imsttfb_pci_driver = अणु
	.name =		"imsttfb",
	.id_table =	imsttfb_pci_tbl,
	.probe =	imsttfb_probe,
	.हटाओ =	imsttfb_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा fb_ops imsttfb_ops = अणु
	.owner 		= THIS_MODULE,
	.fb_check_var	= imsttfb_check_var,
	.fb_set_par 	= imsttfb_set_par,
	.fb_setcolreg 	= imsttfb_setcolreg,
	.fb_pan_display = imsttfb_pan_display,
	.fb_blank 	= imsttfb_blank,
	.fb_fillrect	= imsttfb_fillrect,
	.fb_copyarea	= imsttfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_ioctl 	= imsttfb_ioctl,
पूर्ण;

अटल व्योम init_imstt(काष्ठा fb_info *info)
अणु
	काष्ठा imstt_par *par = info->par;
	__u32 i, पंचांगp, *ip, *end;

	पंचांगp = पढ़ो_reg_le32(par->dc_regs, PRC);
	अगर (par->ramdac == IBM)
		info->fix.smem_len = (पंचांगp & 0x0004) ? 0x400000 : 0x200000;
	अन्यथा
		info->fix.smem_len = 0x800000;

	ip = (__u32 *)info->screen_base;
	end = (__u32 *)(info->screen_base + info->fix.smem_len);
	जबतक (ip < end)
		*ip++ = 0;

	/* initialize the card */
	पंचांगp = पढ़ो_reg_le32(par->dc_regs, STGCTL);
	ग_लिखो_reg_le32(par->dc_regs, STGCTL, पंचांगp & ~0x1);
	ग_लिखो_reg_le32(par->dc_regs, SSR, 0);

	/* set शेष values क्रम DAC रेजिस्टरs */
	अगर (par->ramdac == IBM) अणु
		par->cmap_regs[PPMASK] = 0xff;
		eieio();
		par->cmap_regs[PIDXHI] = 0;
		eieio();
		क्रम (i = 0; i < ARRAY_SIZE(ibm_initregs); i++) अणु
			par->cmap_regs[PIDXLO] = ibm_initregs[i].addr;
			eieio();
			par->cmap_regs[PIDXDATA] = ibm_initregs[i].value;
			eieio();
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(tvp_initregs); i++) अणु
			par->cmap_regs[TVPADDRW] = tvp_initregs[i].addr;
			eieio();
			par->cmap_regs[TVPIDATA] = tvp_initregs[i].value;
			eieio();
		पूर्ण
	पूर्ण

#अगर defined(CONFIG_PPC_PMAC) && defined(CONFIG_PPC32)
	अगर (IS_REACHABLE(CONFIG_NVRAM) && machine_is(घातermac)) अणु
		पूर्णांक vmode = init_vmode, cmode = init_cmode;

		अगर (vmode == -1) अणु
			vmode = nvram_पढ़ो_byte(NV_VMODE);
			अगर (vmode <= 0 || vmode > VMODE_MAX)
				vmode = VMODE_640_480_67;
		पूर्ण
		अगर (cmode == -1) अणु
			cmode = nvram_पढ़ो_byte(NV_CMODE);
			अगर (cmode < CMODE_8 || cmode > CMODE_32)
				cmode = CMODE_8;
		पूर्ण
		अगर (mac_vmode_to_var(vmode, cmode, &info->var)) अणु
			info->var.xres = info->var.xres_भव = INIT_XRES;
			info->var.yres = info->var.yres_भव = INIT_YRES;
			info->var.bits_per_pixel = INIT_BPP;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		info->var.xres = info->var.xres_भव = INIT_XRES;
		info->var.yres = info->var.yres_भव = INIT_YRES;
		info->var.bits_per_pixel = INIT_BPP;
	पूर्ण

	अगर ((info->var.xres * info->var.yres) * (info->var.bits_per_pixel >> 3) > info->fix.smem_len
	    || !(compute_imstt_regvals(par, info->var.xres, info->var.yres))) अणु
		prपूर्णांकk("imsttfb: %ux%ux%u not supported\n", info->var.xres, info->var.yres, info->var.bits_per_pixel);
		framebuffer_release(info);
		वापस;
	पूर्ण

	प्र_लिखो(info->fix.id, "IMS TT (%s)", par->ramdac == IBM ? "IBM" : "TVP");
	info->fix.mmio_len = 0x1000;
	info->fix.accel = FB_ACCEL_IMS_TWINTURBO;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = info->var.bits_per_pixel == 8 ? FB_VISUAL_PSEUDOCOLOR
							: FB_VISUAL_सूचीECTCOLOR;
	info->fix.line_length = info->var.xres * (info->var.bits_per_pixel >> 3);
	info->fix.xpanstep = 8;
	info->fix.ypanstep = 1;
	info->fix.ywrapstep = 0;

	info->var.accel_flags = FB_ACCELF_TEXT;

//	अगर (par->ramdac == IBM)
//		imstt_cursor_init(info);
	अगर (info->var.green.length == 6)
		set_565(par);
	अन्यथा
		set_555(par);
	set_imstt_regvals(info, info->var.bits_per_pixel);

	info->var.pixघड़ी = 1000000 / अ_लोlkMHz(par);

	info->fbops = &imsttfb_ops;
	info->flags = FBINFO_DEFAULT |
                      FBINFO_HWACCEL_COPYAREA |
	              FBINFO_HWACCEL_FILLRECT |
	              FBINFO_HWACCEL_YPAN;

	fb_alloc_cmap(&info->cmap, 0, 0);

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		framebuffer_release(info);
		वापस;
	पूर्ण

	पंचांगp = (पढ़ो_reg_le32(par->dc_regs, SSTATUS) & 0x0f00) >> 8;
	fb_info(info, "%s frame buffer; %uMB vram; chip version %u\n",
		info->fix.id, info->fix.smem_len >> 20, पंचांगp);
पूर्ण

अटल पूर्णांक imsttfb_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित दीर्घ addr, size;
	काष्ठा imstt_par *par;
	काष्ठा fb_info *info;
	काष्ठा device_node *dp;
	पूर्णांक ret = -ENOMEM;
	
	dp = pci_device_to_OF_node(pdev);
	अगर(dp)
		prपूर्णांकk(KERN_INFO "%s: OF name %pOFn\n",__func__, dp);
	अन्यथा अगर (IS_ENABLED(CONFIG_OF))
		prपूर्णांकk(KERN_ERR "imsttfb: no OF node for pci device\n");

	info = framebuffer_alloc(माप(काष्ठा imstt_par), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	par = info->par;

	addr = pci_resource_start (pdev, 0);
	size = pci_resource_len (pdev, 0);

	अगर (!request_mem_region(addr, size, "imsttfb")) अणु
		prपूर्णांकk(KERN_ERR "imsttfb: Can't reserve memory region\n");
		framebuffer_release(info);
		वापस -ENODEV;
	पूर्ण

	चयन (pdev->device) अणु
		हाल PCI_DEVICE_ID_IMS_TT128: /* IMS,tt128mbA */
			par->ramdac = IBM;
			अगर (of_node_name_eq(dp, "IMS,tt128mb8") ||
			    of_node_name_eq(dp, "IMS,tt128mb8A"))
				par->ramdac = TVP;
			अवरोध;
		हाल PCI_DEVICE_ID_IMS_TT3D:  /* IMS,tt3d */
			par->ramdac = TVP;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_INFO "imsttfb: Device 0x%x unknown, "
					 "contact maintainer.\n", pdev->device);
			ret = -ENODEV;
			जाओ error;
	पूर्ण

	info->fix.smem_start = addr;
	info->screen_base = (__u8 *)ioremap(addr, par->ramdac == IBM ?
					    0x400000 : 0x800000);
	अगर (!info->screen_base)
		जाओ error;
	info->fix.mmio_start = addr + 0x800000;
	par->dc_regs = ioremap(addr + 0x800000, 0x1000);
	अगर (!par->dc_regs)
		जाओ error;
	par->cmap_regs_phys = addr + 0x840000;
	par->cmap_regs = (__u8 *)ioremap(addr + 0x840000, 0x1000);
	अगर (!par->cmap_regs)
		जाओ error;
	info->pseuकरो_palette = par->palette;
	init_imstt(info);

	pci_set_drvdata(pdev, info);
	वापस 0;

error:
	अगर (par->dc_regs)
		iounmap(par->dc_regs);
	अगर (info->screen_base)
		iounmap(info->screen_base);
	release_mem_region(addr, size);
	framebuffer_release(info);
	वापस ret;
पूर्ण

अटल व्योम imsttfb_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा fb_info *info = pci_get_drvdata(pdev);
	काष्ठा imstt_par *par = info->par;
	पूर्णांक size = pci_resource_len(pdev, 0);

	unरेजिस्टर_framebuffer(info);
	iounmap(par->cmap_regs);
	iounmap(par->dc_regs);
	iounmap(info->screen_base);
	release_mem_region(info->fix.smem_start, size);
	framebuffer_release(info);
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init
imsttfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!म_भेदन(this_opt, "font:", 5)) अणु
			अक्षर *p;
			पूर्णांक i;

			p = this_opt + 5;
			क्रम (i = 0; i < माप(fontname) - 1; i++)
				अगर (!*p || *p == ' ' || *p == ',')
					अवरोध;
			स_नकल(fontname, this_opt + 5, i);
			fontname[i] = 0;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "inverse", 7)) अणु
			inverse = 1;
			fb_invert_cmaps();
		पूर्ण
#अगर defined(CONFIG_PPC_PMAC)
		अन्यथा अगर (!म_भेदन(this_opt, "vmode:", 6)) अणु
			पूर्णांक vmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			अगर (vmode > 0 && vmode <= VMODE_MAX)
				init_vmode = vmode;
		पूर्ण अन्यथा अगर (!म_भेदन(this_opt, "cmode:", 6)) अणु
			पूर्णांक cmode = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			चयन (cmode) अणु
				हाल CMODE_8:
				हाल 8:
					init_cmode = CMODE_8;
					अवरोध;
				हाल CMODE_16:
				हाल 15:
				हाल 16:
					init_cmode = CMODE_16;
					अवरोध;
				हाल CMODE_32:
				हाल 24:
				हाल 32:
					init_cmode = CMODE_32;
					अवरोध;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर /* MODULE */

अटल पूर्णांक __init imsttfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;

	अगर (fb_get_options("imsttfb", &option))
		वापस -ENODEV;

	imsttfb_setup(option);
#पूर्ण_अगर
	वापस pci_रेजिस्टर_driver(&imsttfb_pci_driver);
पूर्ण
 
अटल व्योम __निकास imsttfb_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&imsttfb_pci_driver);
पूर्ण

MODULE_LICENSE("GPL");

module_init(imsttfb_init);
module_निकास(imsttfb_निकास);

