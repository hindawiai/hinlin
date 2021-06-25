<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * sh7760fb.h -- platक्रमm data क्रम SH7760/SH7763 LCDC framebuffer driver.
 *
 * (c) 2006-2008 MSC Vertriebsges.m.b.H.,
 * 			Manuel Lauss <mano@roarinelk.homelinux.net>
 * (c) 2008 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 */

#अगर_अघोषित _ASM_SH_SH7760FB_H
#घोषणा _ASM_SH_SH7760FB_H

/*
 * some bits of the colormap रेजिस्टरs should be written as zero.
 * create a mask क्रम that.
 */
#घोषणा SH7760FB_PALETTE_MASK 0x00f8fcf8

/* The LCDC dma engine always sets bits 27-26 to 1: this is Area3 */
#घोषणा SH7760FB_DMA_MASK 0x0C000000

/* palette */
#घोषणा LDPR(x) (((x) << 2))

/* framebuffer रेजिस्टरs and bits */
#घोषणा LDICKR 0x400
#घोषणा LDMTR 0x402
/* see sh7760fb.h क्रम LDMTR bits */
#घोषणा LDDFR 0x404
#घोषणा LDDFR_PABD (1 << 8)
#घोषणा LDDFR_COLOR_MASK 0x7F
#घोषणा LDSMR 0x406
#घोषणा LDSMR_ROT (1 << 13)
#घोषणा LDSARU 0x408
#घोषणा LDSARL 0x40c
#घोषणा LDLAOR 0x410
#घोषणा LDPALCR 0x412
#घोषणा LDPALCR_PALS (1 << 4)
#घोषणा LDPALCR_PALEN (1 << 0)
#घोषणा LDHCNR 0x414
#घोषणा LDHSYNR 0x416
#घोषणा LDVDLNR 0x418
#घोषणा LDVTLNR 0x41a
#घोषणा LDVSYNR 0x41c
#घोषणा LDACLNR 0x41e
#घोषणा LDINTR 0x420
#घोषणा LDPMMR 0x424
#घोषणा LDPSPR 0x426
#घोषणा LDCNTR 0x428
#घोषणा LDCNTR_DON (1 << 0)
#घोषणा LDCNTR_DON2 (1 << 4)

#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7763
# define LDLIRNR       0x440
/* LDINTR bit */
# define LDINTR_MINTEN (1 << 15)
# define LDINTR_FINTEN (1 << 14)
# define LDINTR_VSINTEN (1 << 13)
# define LDINTR_VEINTEN (1 << 12)
# define LDINTR_MINTS (1 << 11)
# define LDINTR_FINTS (1 << 10)
# define LDINTR_VSINTS (1 << 9)
# define LDINTR_VEINTS (1 << 8)
# define VINT_START (LDINTR_VSINTEN)
# define VINT_CHECK (LDINTR_VSINTS)
#अन्यथा
/* LDINTR bit */
# define LDINTR_VINTSEL (1 << 12)
# define LDINTR_VINTE (1 << 8)
# define LDINTR_VINTS (1 << 0)
# define VINT_START (LDINTR_VINTSEL)
# define VINT_CHECK (LDINTR_VINTS)
#पूर्ण_अगर

/* HSYNC polarity inversion */
#घोषणा LDMTR_FLMPOL (1 << 15)

/* VSYNC polarity inversion */
#घोषणा LDMTR_CL1POL (1 << 14)

/* DISPLAY-ENABLE polarity inversion */
#घोषणा LDMTR_DISPEN_LOWACT (1 << 13)

/* DISPLAY DATA BUS polarity inversion */
#घोषणा LDMTR_DPOL_LOWACT (1 << 12)

/* AC modulation संकेत enable */
#घोषणा LDMTR_MCNT (1 << 10)

/* Disable output of HSYNC during VSYNC period */
#घोषणा LDMTR_CL1CNT (1 << 9)

/* Disable output of VSYNC during VSYNC period */
#घोषणा LDMTR_CL2CNT (1 << 8)

/* Display types supported by the LCDC */
#घोषणा LDMTR_STN_MONO_4       0x00
#घोषणा LDMTR_STN_MONO_8       0x01
#घोषणा LDMTR_STN_COLOR_4      0x08
#घोषणा LDMTR_STN_COLOR_8      0x09
#घोषणा LDMTR_STN_COLOR_12     0x0A
#घोषणा LDMTR_STN_COLOR_16     0x0B
#घोषणा LDMTR_DSTN_MONO_8      0x11
#घोषणा LDMTR_DSTN_MONO_16     0x13
#घोषणा LDMTR_DSTN_COLOR_8     0x19
#घोषणा LDMTR_DSTN_COLOR_12    0x1A
#घोषणा LDMTR_DSTN_COLOR_16    0x1B
#घोषणा LDMTR_TFT_COLOR_16     0x2B

/* framebuffer color layout */
#घोषणा LDDFR_1BPP_MONO 0x00
#घोषणा LDDFR_2BPP_MONO 0x01
#घोषणा LDDFR_4BPP_MONO 0x02
#घोषणा LDDFR_6BPP_MONO 0x04
#घोषणा LDDFR_4BPP 0x0A
#घोषणा LDDFR_8BPP 0x0C
#घोषणा LDDFR_16BPP_RGB555 0x1D
#घोषणा LDDFR_16BPP_RGB565 0x2D

/* LCDC Pixघड़ी sources */
#घोषणा LCDC_CLKSRC_BUSCLOCK 0
#घोषणा LCDC_CLKSRC_PERIPHERAL 1
#घोषणा LCDC_CLKSRC_EXTERNAL 2

#घोषणा LDICKR_CLKSRC(x) \
       (((x) & 3) << 12)

/* LCDC pixघड़ी input भागider. Set to 1 at a minimum! */
#घोषणा LDICKR_CLKDIV(x) \
       ((x) & 0x1f)

काष्ठा sh7760fb_platdata अणु

	/* Set this member to a valid fb_videmode क्रम the display you
	 * wish to use.  The following members must be initialized:
	 * xres, yres, hsync_len, vsync_len, sync,
	 * अणुleft,right,upper,lowerपूर्ण_margin.
	 * The driver uses the above members to calculate रेजिस्टर values
	 * and memory requirements. Other members are ignored but may
	 * be used by other framebuffer layer components.
	 */
	काष्ठा fb_videomode *def_mode;

	/* LDMTR includes display type and संकेत polarity.  The
	 * HSYNC/VSYNC polarities are derived from the fb_var_screeninfo
	 * data above; however the polarities of the following संकेतs
	 * must be encoded in the ldmtr member:
	 * Display Enable संकेत (शेष high-active)  DISPEN_LOWACT
	 * Display Data संकेतs (शेष high-active)   DPOL_LOWACT
	 * AC Modulation संकेत (शेष off)           MCNT
	 * Hsync-During-Vsync suppression (शेष off) CL1CNT
	 * Vsync-during-vsync suppression (शेष off) CL2CNT
	 * NOTE: also set a display type!
	 * (one of LDMTR_अणुSTN,DSTN,TFTपूर्ण_अणुMONO,COLORपूर्ण_अणु4,8,12,16पूर्ण)
	 */
	u16 ldmtr;

	/* LDDFR controls framebuffer image क्रमmat (depth, organization)
	 * Use ONE of the LDDFR_?BPP_* macros!
	 */
	u16 lddfr;

	/* LDPMMR and LDPSPR control the timing of the घातer संकेतs
	 * क्रम the display. Please पढ़ो the SH7760 Hardware Manual,
	 * Chapters 30.3.17, 30.3.18 and 30.4.6!
	 */
	u16 ldpmmr;
	u16 ldpspr;

	/* LDACLNR contains the line numbers after which the AC modulation
	 * संकेत is to toggle. Set to ZERO क्रम TFTs or displays which
	 * करो not need it. (Chapter 30.3.15 in SH7760 Hardware Manual).
	 */
	u16 ldaclnr;

	/* LDICKR contains inक्रमmation on pixelघड़ी source and config.
	 * Please use the LDICKR_CLKSRC() and LDICKR_CLKDIV() macros.
	 * minimal value क्रम CLKDIV() must be 1!.
	 */
	u16 ldickr;

	/* set this member to 1 अगर you wish to use the LCDC's hardware
	 * rotation function.  This is limited to displays <= 320x200
	 * pixels resolution!
	 */
	पूर्णांक rotate;		/* set to 1 to rotate 90 CCW */

	/* set this to 1 to suppress vsync irq use. */
	पूर्णांक novsync;

	/* blanking hook क्रम platक्रमm. Set this अगर your platक्रमm can करो
	 * more than the LCDC in terms of blanking (e.g. disable घड़ी
	 * generator / backlight घातer supply / etc.
	 */
	व्योम (*blank) (पूर्णांक);
पूर्ण;

#पूर्ण_अगर /* _ASM_SH_SH7760FB_H */
