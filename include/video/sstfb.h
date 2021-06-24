<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/drivers/video/sstfb.h -- vooकरोo graphics frame buffer
 *
 *     Copyright (c) 2000,2001 Ghozlane Toumi <gtoumi@messel.emse.fr>
 *
 *     Created 28 Aug 2001 by Ghozlane Toumi
 */


#अगर_अघोषित _SSTFB_H_
#घोषणा _SSTFB_H_

/*
 *
 *  Debug Stuff
 *
 */

#अगर_घोषित SST_DEBUG
#  define dprपूर्णांकk(X...)		prपूर्णांकk("sstfb: " X)
#  define SST_DEBUG_REG  1
#  define SST_DEBUG_FUNC 1
#  define SST_DEBUG_VAR  1
#अन्यथा
#  define dprपूर्णांकk(X...)		no_prपूर्णांकk(X)
#  define SST_DEBUG_REG  0
#  define SST_DEBUG_FUNC 0
#  define SST_DEBUG_VAR  0
#पूर्ण_अगर

#अगर (SST_DEBUG_REG > 0)
#  define r_dprपूर्णांकk(X...)	dprपूर्णांकk(X)
#अन्यथा
#  define r_dprपूर्णांकk(X...)
#पूर्ण_अगर
#अगर (SST_DEBUG_REG > 1)
#  define r_ddprपूर्णांकk(X...)	dprपूर्णांकk(" " X)
#अन्यथा
#  define r_ddprपूर्णांकk(X...)
#पूर्ण_अगर

#अगर (SST_DEBUG_FUNC > 0)
#  define f_dprपूर्णांकk(X...)	dprपूर्णांकk(X)
#अन्यथा
#  define f_dprपूर्णांकk(X...)
#पूर्ण_अगर
#अगर (SST_DEBUG_FUNC > 1)
#  define f_ddprपूर्णांकk(X...)	dprपूर्णांकk(" " X)
#अन्यथा
#  define f_ddprपूर्णांकk(X...)	no_prपूर्णांकk(X)
#पूर्ण_अगर
#अगर (SST_DEBUG_FUNC > 2)
#  define f_dddprपूर्णांकk(X...)	dprपूर्णांकk(" " X)
#अन्यथा
#  define f_dddprपूर्णांकk(X...)
#पूर्ण_अगर

#अगर (SST_DEBUG_VAR > 0)
#  define v_dprपूर्णांकk(X...)	dprपूर्णांकk(X)
#  define prपूर्णांक_var(V, X...)	\
   अणु				\
     dprपूर्णांकk(X);		\
     prपूर्णांकk(" :\n");		\
     sst_dbg_prपूर्णांक_var(V);	\
   पूर्ण
#अन्यथा
#  define v_dprपूर्णांकk(X...)
#  define prपूर्णांक_var(X,Y...)
#पूर्ण_अगर

#घोषणा POW2(x)		(1ul<<(x))

/*
 *
 *  Const
 *
 */

/* pci stuff */
#घोषणा PCI_INIT_ENABLE		0x40
#  define PCI_EN_INIT_WR	  BIT(0)
#  define PCI_EN_FIFO_WR	  BIT(1)
#  define PCI_REMAP_DAC		  BIT(2)
#घोषणा PCI_VCLK_ENABLE		0xc0	/* enable video */
#घोषणा PCI_VCLK_DISABLE	0xe0

/* रेजिस्टर offsets from memBaseAddr */
#घोषणा STATUS			0x0000
#  define STATUS_FBI_BUSY	  BIT(7)
#घोषणा FBZMODE			0x0110
#  define EN_CLIPPING		  BIT(0)	/* enable clipping */
#  define EN_RGB_WRITE		  BIT(9)	/* enable ग_लिखोs to rgb area */
#  define EN_ALPHA_WRITE	  BIT(10)
#  define ENGINE_INVERT_Y	  BIT(17)	/* invert Y origin (pipe) */
#घोषणा LFBMODE			0x0114
#  define LFB_565		  0		/* bits 3:0 .16 bits RGB */
#  define LFB_888		  4		/* 24 bits RGB */
#  define LFB_8888		  5		/* 32 bits ARGB */
#  define WR_BUFF_FRONT		  0		/* ग_लिखो buf select (front) */
#  define WR_BUFF_BACK		  (1 << 4)	/* back */
#  define RD_BUFF_FRONT		  0		/* पढ़ो buff select (front) */
#  define RD_BUFF_BACK		  (1 << 6)	/* back */
#  define EN_PXL_PIPELINE	  BIT(8)	/* pixel pipeline (clip..)*/
#  define LFB_WORD_SWIZZLE_WR	  BIT(11)	/* enable ग_लिखो-wordswap (big-endian) */
#  define LFB_BYTE_SWIZZLE_WR	  BIT(12)	/* enable ग_लिखो-byteswap (big-endian) */
#  define LFB_INVERT_Y		  BIT(13)	/* invert Y origin (LFB) */
#  define LFB_WORD_SWIZZLE_RD	  BIT(15)	/* enable पढ़ो-wordswap (big-endian) */
#  define LFB_BYTE_SWIZZLE_RD	  BIT(16)	/* enable पढ़ो-byteswap (big-endian) */
#घोषणा CLIP_LEFT_RIGHT		0x0118
#घोषणा CLIP_LOWY_HIGHY		0x011c
#घोषणा NOPCMD			0x0120
#घोषणा FASTFILLCMD		0x0124
#घोषणा SWAPBUFFCMD		0x0128
#घोषणा FBIINIT4		0x0200		/* misc controls */
#  define FAST_PCI_READS	  0		/* 1 रुकोstate */
#  define SLOW_PCI_READS	  BIT(0)	/* 2 ws */
#  define LFB_READ_AHEAD	  BIT(1)
#घोषणा BACKPORCH		0x0208
#घोषणा VIDEODIMENSIONS		0x020c
#घोषणा FBIINIT0		0x0210		/* misc+fअगरo  controls */
#  define DIS_VGA_PASSTHROUGH	  BIT(0)
#  define FBI_RESET		  BIT(1)
#  define FIFO_RESET		  BIT(2)
#घोषणा FBIINIT1		0x0214		/* PCI + video controls */
#  define VIDEO_MASK		  0x8080010f	/* masks video related bits V1+V2*/
#  define FAST_PCI_WRITES	  0		/* 0 ws */
#  define SLOW_PCI_WRITES	  BIT(1)	/* 1 ws */
#  define EN_LFB_READ		  BIT(3)
#  define TILES_IN_X_SHIFT	  4
#  define VIDEO_RESET		  BIT(8)
#  define EN_BLANKING		  BIT(12)
#  define EN_DATA_OE		  BIT(13)
#  define EN_BLANK_OE		  BIT(14)
#  define EN_HVSYNC_OE		  BIT(15)
#  define EN_DCLK_OE		  BIT(16)
#  define SEL_INPUT_VCLK_2X	  0		/* bit 17 */
#  define SEL_INPUT_VCLK_SLAVE	  BIT(17)
#  define SEL_SOURCE_VCLK_SLAVE	  0		/* bits 21:20 */
#  define SEL_SOURCE_VCLK_2X_DIV2 (0x01 << 20)
#  define SEL_SOURCE_VCLK_2X_SEL  (0x02 << 20)
#  define EN_24BPP		  BIT(22)
#  define TILES_IN_X_MSB_SHIFT	  24		/* v2 */
#  define VCLK_2X_SEL_DEL_SHIFT	  27		/* vclk out delay 0,4,6,8ns */
#  define VCLK_DEL_SHIFT	  29		/* vclk in delay */
#घोषणा FBIINIT2		0x0218		/* Dram controls */
#  define EN_FAST_RAS_READ	  BIT(5)
#  define EN_DRAM_OE		  BIT(6)
#  define EN_FAST_RD_AHEAD_WR	  BIT(7)
#  define VIDEO_OFFSET_SHIFT	  11		/* unit: #rows tile 64x16/2 */
#  define SWAP_DACVSYNC		  0
#  define SWAP_DACDATA0		  (1 << 9)
#  define SWAP_FIFO_STALL	  (2 << 9)
#  define EN_RD_AHEAD_FIFO	  BIT(21)
#  define EN_DRAM_REFRESH	  BIT(22)
#  define DRAM_REFRESH_16	  (0x30 << 23)	/* dram 16 ms */
#घोषणा DAC_READ		FBIINIT2	/* in remap mode */
#घोषणा FBIINIT3		0x021c		/* fbi controls */
#  define DISABLE_TEXTURE	  BIT(6)
#  define Y_SWAP_ORIGIN_SHIFT	  22		/* Y swap subtraction value */
#घोषणा HSYNC			0x0220
#घोषणा VSYNC			0x0224
#घोषणा DAC_DATA		0x022c
#  define DAC_READ_CMD		  BIT(11)	/* set पढ़ो dacreg mode */
#घोषणा FBIINIT5		0x0244		/* v2 specअगरic */
#  define FBIINIT5_MASK		  0xfa40ffff    /* mask video bits*/
#  define HDOUBLESCAN		  BIT(20)
#  define VDOUBLESCAN		  BIT(21)
#  define HSYNC_HIGH 		  BIT(23)
#  define VSYNC_HIGH 		  BIT(24)
#  define INTERLACE		  BIT(26)
#घोषणा FBIINIT6		0x0248		/* v2 specअगरic */
#  define TILES_IN_X_LSB_SHIFT	  30		/* v2 */
#घोषणा FBIINIT7		0x024c		/* v2 specअगरic */

#घोषणा BLTSRCBASEADDR		0x02c0	/* BitBLT Source base address */
#घोषणा BLTDSTBASEADDR		0x02c4	/* BitBLT Destination base address */
#घोषणा BLTXYSTRIDES		0x02c8	/* BitBLT Source and Destination strides */
#घोषणा BLTSRCCHROMARANGE	0x02cc	/* BitBLT Source Chroma key range */
#घोषणा BLTDSTCHROMARANGE	0x02d0	/* BitBLT Destination Chroma key range */
#घोषणा BLTCLIPX		0x02d4	/* BitBLT Min/Max X clip values */
#घोषणा BLTCLIPY		0x02d8	/* BitBLT Min/Max Y clip values */
#घोषणा BLTSRCXY		0x02e0	/* BitBLT Source starting XY coordinates */
#घोषणा BLTDSTXY		0x02e4	/* BitBLT Destination starting XY coordinates */
#घोषणा BLTSIZE			0x02e8	/* BitBLT width and height */
#घोषणा BLTROP			0x02ec	/* BitBLT Raster operations */
#  define BLTROP_COPY		  0x0cccc
#  define BLTROP_INVERT		  0x05555
#  define BLTROP_XOR		  0x06666
#घोषणा BLTCOLOR		0x02f0	/* BitBLT and क्रमeground background colors */
#घोषणा BLTCOMMAND		0x02f8	/* BitBLT command mode (v2 specअगरic) */
# define BLT_SCR2SCR_BITBLT	  0	  /* Screen-to-Screen BitBLT */
# define BLT_CPU2SCR_BITBLT	  1	  /* CPU-to-screen BitBLT */
# define BLT_RECFILL_BITBLT	  2	  /* BitBLT Rectangle Fill */
# define BLT_16BPP_FMT		  2	  /* 16 BPP (5-6-5 RGB) */
#घोषणा BLTDATA			0x02fc	/* BitBLT data क्रम CPU-to-Screen BitBLTs */
#  define LAUNCH_BITBLT		  BIT(31) /* Launch BitBLT in BltCommand, bltDstXY or bltSize */

/* Dac Registers */
#घोषणा DACREG_WMA		0x0	/* pixel ग_लिखो mode address */
#घोषणा DACREG_LUT		0x01	/* color value */
#घोषणा DACREG_RMR		0x02	/* pixel mask */
#घोषणा DACREG_RMA		0x03	/* pixel पढ़ो mode address */
/*Dac रेजिस्टरs in indexed mode (TI, ATT dacs) */
#घोषणा DACREG_ADDR_I		DACREG_WMA
#घोषणा DACREG_DATA_I		DACREG_RMR
#घोषणा DACREG_RMR_I		0x00
#घोषणा DACREG_CR0_I		0x01
#  define DACREG_CR0_EN_INDEXED	  BIT(0)	/* enable indexec mode */
#  define DACREG_CR0_8BIT	  BIT(1)	/* set dac to 8 bits/पढ़ो */
#  define DACREG_CR0_PWDOWN	  BIT(3)	/* घातerकरोwn dac */
#  define DACREG_CR0_16BPP	  0x30		/* mode 3 */
#  define DACREG_CR0_24BPP	  0x50		/* mode 5 */
#घोषणा	DACREG_CR1_I		0x05
#घोषणा DACREG_CC_I		0x06
#  define DACREG_CC_CLKA	  BIT(7)	/* clk A controlled by regs */
#  define DACREG_CC_CLKA_C	  (2<<4)	/* clk A uses reg C */
#  define DACREG_CC_CLKB	  BIT(3)	/* clk B controlled by regs */
#  define DACREG_CC_CLKB_D	  3		/* clkB uses reg D */
#घोषणा DACREG_AC0_I		0x48		/* घड़ी A reg C */
#घोषणा DACREG_AC1_I		0x49
#घोषणा DACREG_BD0_I		0x6c		/* घड़ी B reg D */
#घोषणा DACREG_BD1_I		0x6d

/* identअगरication स्थिरants */
#घोषणा DACREG_MIR_TI		0x97
#घोषणा DACREG_सूची_TI		0x09
#घोषणा DACREG_MIR_ATT		0x84
#घोषणा DACREG_सूची_ATT		0x09
/* ics dac specअगरic रेजिस्टरs */
#घोषणा DACREG_ICS_PLLWMA	0x04	/* PLL ग_लिखो mode address */
#घोषणा DACREG_ICS_PLLDATA	0x05	/* PLL data /parameter */
#घोषणा DACREG_ICS_CMD		0x06	/* command */
#  define DACREG_ICS_CMD_16BPP	  0x50	/* ics color mode 6 (16bpp bypass)*/
#  define DACREG_ICS_CMD_24BPP	  0x70	/* ics color mode 7 (24bpp bypass)*/
#  define DACREG_ICS_CMD_PWDOWN BIT(0)	/* घातerकरोwn dac */
#घोषणा DACREG_ICS_PLLRMA	0x07	/* PLL पढ़ो mode address */
/*
 * pll parameter रेजिस्टर:
 * indexed : ग_लिखो addr to PLLWMA, ग_लिखो data in PLLDATA.
 * क्रम पढ़ोs use PLLRMA .
 * 8 freq रेजिस्टरs (0-7) क्रम video घड़ी (CLK0)
 * 2 freq रेजिस्टरs (a-b) क्रम graphic घड़ी (CLK1)
 */
#घोषणा DACREG_ICS_PLL_CLK0_1_INI 0x55	/* initial pll M value क्रम freq f1  */
#घोषणा DACREG_ICS_PLL_CLK0_7_INI 0x71	/* f7 */
#घोषणा DACREG_ICS_PLL_CLK1_B_INI 0x79	/* fb */
#घोषणा DACREG_ICS_PLL_CTRL	0x0e
#  define DACREG_ICS_CLK0	  BIT(5)
#  define DACREG_ICS_CLK0_0	  0
#  define DACREG_ICS_CLK1_A	  0	/* bit4 */

/* sst शेष init रेजिस्टरs */
#घोषणा FBIINIT0_DEFAULT DIS_VGA_PASSTHROUGH

#घोषणा FBIINIT1_DEFAULT 	\
	(			\
	  FAST_PCI_WRITES	\
/*	  SLOW_PCI_WRITES*/	\
	| VIDEO_RESET		\
	| 10 << TILES_IN_X_SHIFT\
	| SEL_SOURCE_VCLK_2X_SEL\
	| EN_LFB_READ		\
	)

#घोषणा FBIINIT2_DEFAULT	\
	(			\
	 SWAP_DACVSYNC		\
	| EN_DRAM_OE		\
	| DRAM_REFRESH_16	\
	| EN_DRAM_REFRESH	\
	| EN_FAST_RAS_READ	\
	| EN_RD_AHEAD_FIFO	\
	| EN_FAST_RD_AHEAD_WR	\
	)

#घोषणा FBIINIT3_DEFAULT 	\
	( DISABLE_TEXTURE )

#घोषणा FBIINIT4_DEFAULT	\
	(			\
	  FAST_PCI_READS	\
/*	  SLOW_PCI_READS*/	\
	| LFB_READ_AHEAD	\
	)
/* Careful with this one : writing back the data just पढ़ो will trash the DAC
   पढ़ोing some fields give logic value on pins, but setting this field will
   set the source संकेत driving the pin. conclusion : just use the शेष
   as a base beक्रमe writing back .
*/
#घोषणा FBIINIT6_DEFAULT	(0x0)

/*
 *
 * Misc Const
 *
 */

/* ioctl to enable/disable VGA passthrough */
#घोषणा SSTFB_SET_VGAPASS	_IOW('F', 0xdd, __u32)
#घोषणा SSTFB_GET_VGAPASS	_IOR('F', 0xdd, __u32)


/* used to know witch घड़ी to set */
क्रमागत अणु
	VID_CLOCK=0,
	GFX_CLOCK=1,
पूर्ण;

/* freq max */
#घोषणा DAC_FREF	14318	/* DAC reference freq (Khz) */
#घोषणा VCO_MAX		260000

/*
 *  driver काष्ठाs
 */

काष्ठा pll_timing अणु
	अचिन्हित पूर्णांक m;
	अचिन्हित पूर्णांक n;
	अचिन्हित पूर्णांक p;
पूर्ण;

काष्ठा dac_चयन अणु
	स्थिर अक्षर *name;
	पूर्णांक (*detect) (काष्ठा fb_info *info);
	पूर्णांक (*set_pll) (काष्ठा fb_info *info, स्थिर काष्ठा pll_timing *t, स्थिर पूर्णांक घड़ी);
	व्योम (*set_vidmod) (काष्ठा fb_info *info, स्थिर पूर्णांक bpp);
पूर्ण;

काष्ठा sst_spec अणु
	अक्षर * name;
	पूर्णांक शेष_gfx_घड़ी;	/* 50000 क्रम vooकरोo1, 75000 क्रम vooकरोo2 */
	पूर्णांक max_gfxclk; 	/* ! in Mhz ie 60 क्रम vooकरोo 1 */
पूर्ण;

काष्ठा sstfb_par अणु
	u32 palette[16];
	अचिन्हित पूर्णांक yDim;
	अचिन्हित पूर्णांक hSyncOn;	/* hsync_len */
	अचिन्हित पूर्णांक hSyncOff;	/* left_margin + xres + right_margin */
	अचिन्हित पूर्णांक hBackPorch;/* left_margin */
	अचिन्हित पूर्णांक vSyncOn;
	अचिन्हित पूर्णांक vSyncOff;
	अचिन्हित पूर्णांक vBackPorch;
	काष्ठा pll_timing pll;
	अचिन्हित पूर्णांक tiles_in_X;/* num of tiles in X res */
	u8 __iomem *mmio_vbase;
	काष्ठा dac_चयन 	dac_sw;	/* dac specअगरic functions */
	काष्ठा pci_dev		*dev;
	पूर्णांक	type;
	u8	revision;
	u8	vgapass;	/* VGA pass through: 1=enabled, 0=disabled */
पूर्ण;

#पूर्ण_अगर /* _SSTFB_H_ */
