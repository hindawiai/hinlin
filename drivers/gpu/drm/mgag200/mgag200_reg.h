<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MGA Millennium (MGA2064W) functions
 * MGA Mystique (MGA1064SG) functions
 *
 * Copyright 1996 The XFree86 Project, Inc.
 *
 * Authors
 *		Dirk Hohndel
 *			hohndel@XFree86.Org
 *		David Dawes
 *			dawes@XFree86.Org
 * Contributors:
 *		Guy DESBIEF, Aix-en-provence, France
 *			g.desbief@aix.pacwan.net
 *		MGA1064SG Mystique रेजिस्टर file
 */

#अगर_अघोषित _MGA_REG_H_
#घोषणा _MGA_REG_H_

#समावेश <linux/bits.h>

#घोषणा	MGAREG_DWGCTL		0x1c00
#घोषणा	MGAREG_MACCESS		0x1c04
/* the following is a mystique only रेजिस्टर */
#घोषणा MGAREG_MCTLWTST		0x1c08
#घोषणा	MGAREG_ZORG		0x1c0c

#घोषणा	MGAREG_PAT0		0x1c10
#घोषणा	MGAREG_PAT1		0x1c14
#घोषणा	MGAREG_PLNWT		0x1c1c

#घोषणा	MGAREG_BCOL		0x1c20
#घोषणा	MGAREG_FCOL		0x1c24

#घोषणा	MGAREG_SRC0		0x1c30
#घोषणा	MGAREG_SRC1		0x1c34
#घोषणा	MGAREG_SRC2		0x1c38
#घोषणा	MGAREG_SRC3		0x1c3c

#घोषणा	MGAREG_XYSTRT		0x1c40
#घोषणा	MGAREG_XYEND		0x1c44

#घोषणा	MGAREG_SHIFT		0x1c50
/* the following is a mystique only रेजिस्टर */
#घोषणा MGAREG_DMAPAD		0x1c54
#घोषणा	MGAREG_SGN		0x1c58
#घोषणा	MGAREG_LEN		0x1c5c

#घोषणा	MGAREG_AR0		0x1c60
#घोषणा	MGAREG_AR1		0x1c64
#घोषणा	MGAREG_AR2		0x1c68
#घोषणा	MGAREG_AR3		0x1c6c
#घोषणा	MGAREG_AR4		0x1c70
#घोषणा	MGAREG_AR5		0x1c74
#घोषणा	MGAREG_AR6		0x1c78

#घोषणा	MGAREG_CXBNDRY		0x1c80
#घोषणा	MGAREG_FXBNDRY		0x1c84
#घोषणा	MGAREG_YDSTLEN		0x1c88
#घोषणा	MGAREG_PITCH		0x1c8c

#घोषणा	MGAREG_YDST		0x1c90
#घोषणा	MGAREG_YDSTORG		0x1c94
#घोषणा	MGAREG_YTOP		0x1c98
#घोषणा	MGAREG_YBOT		0x1c9c

#घोषणा	MGAREG_CXLEFT		0x1ca0
#घोषणा	MGAREG_CXRIGHT		0x1ca4
#घोषणा	MGAREG_FXLEFT		0x1ca8
#घोषणा	MGAREG_FXRIGHT		0x1cac

#घोषणा	MGAREG_XDST		0x1cb0

#घोषणा	MGAREG_DR0		0x1cc0
#घोषणा	MGAREG_DR1		0x1cc4
#घोषणा	MGAREG_DR2		0x1cc8
#घोषणा	MGAREG_DR3		0x1ccc

#घोषणा	MGAREG_DR4		0x1cd0
#घोषणा	MGAREG_DR5		0x1cd4
#घोषणा	MGAREG_DR6		0x1cd8
#घोषणा	MGAREG_DR7		0x1cdc

#घोषणा	MGAREG_DR8		0x1ce0
#घोषणा	MGAREG_DR9		0x1ce4
#घोषणा	MGAREG_DR10		0x1ce8
#घोषणा	MGAREG_DR11		0x1cec

#घोषणा	MGAREG_DR12		0x1cf0
#घोषणा	MGAREG_DR13		0x1cf4
#घोषणा	MGAREG_DR14		0x1cf8
#घोषणा	MGAREG_DR15		0x1cfc

#घोषणा MGAREG_SRCORG		0x2cb4
#घोषणा MGAREG_DSTORG		0x2cb8

/* add or or this to one of the previous "power registers" to start
   the drawing engine */

#घोषणा MGAREG_EXEC		0x0100

#घोषणा	MGAREG_FIFOSTATUS	0x1e10
#घोषणा	MGAREG_Status		0x1e14
#घोषणा MGAREG_CACHEFLUSH       0x1fff
#घोषणा	MGAREG_ICLEAR		0x1e18
#घोषणा	MGAREG_IEN		0x1e1c

#घोषणा	MGAREG_VCOUNT		0x1e20

#घोषणा	MGAREG_Reset		0x1e40

#घोषणा	MGAREG_OPMODE		0x1e54

/* Warp Registers */
#घोषणा MGAREG_WIADDR           0x1dc0
#घोषणा MGAREG_WIADDR2          0x1dd8
#घोषणा MGAREG_WGETMSB          0x1dc8
#घोषणा MGAREG_WVRTXSZ          0x1dcc
#घोषणा MGAREG_WACCEPTSEQ       0x1dd4
#घोषणा MGAREG_WMISC            0x1e70

#घोषणा MGAREG_MEMCTL           0x2e08

/* OPMODE रेजिस्टर additives */

#घोषणा MGAOPM_DMA_GENERAL	(0x00 << 2)
#घोषणा MGAOPM_DMA_BLIT		(0x01 << 2)
#घोषणा MGAOPM_DMA_VECTOR	(0x10 << 2)

/* MACCESS रेजिस्टर additives */
#घोषणा MGAMAC_PW8               0x00
#घोषणा MGAMAC_PW16              0x01
#घोषणा MGAMAC_PW24              0x03 /* not a typo */
#घोषणा MGAMAC_PW32              0x02 /* not a typo */
#घोषणा MGAMAC_BYPASS332         0x10000000
#घोषणा MGAMAC_NODITHER          0x40000000
#घोषणा MGAMAC_DIT555            0x80000000

/* DWGCTL रेजिस्टर additives */

/* Lines */

#घोषणा MGADWG_LINE_OPEN	0x00
#घोषणा MGADWG_AUTOLINE_OPEN	0x01
#घोषणा MGADWG_LINE_CLOSE	0x02
#घोषणा MGADWG_AUTOLINE_CLOSE	0x03

/* Trapezoids */
#घोषणा MGADWG_TRAP		0x04
#घोषणा MGADWG_TEXTURE_TRAP	0x06

/* BitBlts */

#घोषणा MGADWG_BITBLT		0x08
#घोषणा MGADWG_FBITBLT		0x0c
#घोषणा MGADWG_ILOAD		0x09
#घोषणा MGADWG_ILOAD_SCALE	0x0d
#घोषणा MGADWG_ILOAD_FILTER	0x0f
#घोषणा MGADWG_ILOAD_HIQH	0x07
#घोषणा MGADWG_ILOAD_HIQHV	0x0e
#घोषणा MGADWG_IDUMP		0x0a

/* atype access to WRAM */

#घोषणा MGADWG_RPL		( 0x00 << 4 )
#घोषणा MGADWG_RSTR		( 0x01 << 4 )
#घोषणा MGADWG_ZI		( 0x03 << 4 )
#घोषणा MGADWG_BLK 		( 0x04 << 4 )
#घोषणा MGADWG_I		( 0x07 << 4 )

/* specअगरies whether bit blits are linear or xy */
#घोषणा MGADWG_LINEAR		( 0x01 << 7 )

/* z drawing mode. use MGADWG_NOZCMP क्रम always */

#घोषणा MGADWG_NOZCMP		( 0x00 << 8 )
#घोषणा MGADWG_ZE		( 0x02 << 8 )
#घोषणा MGADWG_ZNE		( 0x03 << 8 )
#घोषणा MGADWG_ZLT		( 0x04 << 8 )
#घोषणा MGADWG_ZLTE		( 0x05 << 8 )
#घोषणा MGADWG_GT		( 0x06 << 8 )
#घोषणा MGADWG_GTE		( 0x07 << 8 )

/* use this to क्रमce colour expansion circuitry to करो its stuff */

#घोषणा MGADWG_SOLID		( 0x01 << 11 )

/* ar रेजिस्टर at zero */

#घोषणा MGADWG_ARZERO		( 0x01 << 12 )

#घोषणा MGADWG_SGNZERO		( 0x01 << 13 )

#घोषणा MGADWG_SHIFTZERO	( 0x01 << 14 )

/* See table on 4-43 क्रम bop ALU operations */

/* See table on 4-44 क्रम translucidity masks */

#घोषणा MGADWG_BMONOLEF		( 0x00 << 25 )
#घोषणा MGADWG_BMONOWF		( 0x04 << 25 )
#घोषणा MGADWG_BPLAN		( 0x01 << 25 )

/* note that अगर bfcol is specअगरied and you're करोing a bitblt, it causes
   a fbitblt to be perक्रमmed, so check that you obey the fbitblt rules */

#घोषणा MGADWG_BFCOL   		( 0x02 << 25 )
#घोषणा MGADWG_BUYUV		( 0x0e << 25 )
#घोषणा MGADWG_BU32BGR		( 0x03 << 25 )
#घोषणा MGADWG_BU32RGB		( 0x07 << 25 )
#घोषणा MGADWG_BU24BGR		( 0x0b << 25 )
#घोषणा MGADWG_BU24RGB		( 0x0f << 25 )

#घोषणा MGADWG_PATTERN		( 0x01 << 29 )
#घोषणा MGADWG_TRANSC		( 0x01 << 30 )
#घोषणा MGAREG_MISC_WRITE	0x3c2
#घोषणा MGAREG_MISC_READ	0x3cc
#घोषणा MGAREG_MEM_MISC_WRITE       0x1fc2
#घोषणा MGAREG_MEM_MISC_READ        0x1fcc

#घोषणा MGAREG_MISC_IOADSEL	(0x1 << 0)
#घोषणा MGAREG_MISC_RAMMAPEN	(0x1 << 1)
#घोषणा MGAREG_MISC_CLK_SEL_MASK	GENMASK(3, 2)
#घोषणा MGAREG_MISC_CLK_SEL_VGA25	(0x0 << 2)
#घोषणा MGAREG_MISC_CLK_SEL_VGA28	(0x1 << 2)
#घोषणा MGAREG_MISC_CLK_SEL_MGA_PIX	(0x2 << 2)
#घोषणा MGAREG_MISC_CLK_SEL_MGA_MSK	(0x3 << 2)
#घोषणा MGAREG_MISC_VIDEO_DIS	(0x1 << 4)
#घोषणा MGAREG_MISC_HIGH_PG_SEL	(0x1 << 5)
#घोषणा MGAREG_MISC_HSYNCPOL		BIT(6)
#घोषणा MGAREG_MISC_VSYNCPOL		BIT(7)

/* MMIO VGA रेजिस्टरs */
#घोषणा MGAREG_SEQ_INDEX	0x1fc4
#घोषणा MGAREG_SEQ_DATA		0x1fc5

#घोषणा MGAREG_SEQ0_ASYNCRST	BIT(0)
#घोषणा MGAREG_SEQ0_SYNCRST	BIT(1)

#घोषणा MGAREG_SEQ1_SCROFF	BIT(5)

#घोषणा MGAREG_CRTC_INDEX	0x1fd4
#घोषणा MGAREG_CRTC_DATA	0x1fd5

#घोषणा MGAREG_CRTC11_VINTCLR		BIT(4)
#घोषणा MGAREG_CRTC11_VINTEN		BIT(5)
#घोषणा MGAREG_CRTC11_CRTCPROTECT	BIT(7)

#घोषणा MGAREG_CRTCEXT_INDEX	0x1fde
#घोषणा MGAREG_CRTCEXT_DATA	0x1fdf

#घोषणा MGAREG_CRTCEXT0_OFFSET_MASK	GENMASK(5, 4)

#घोषणा MGAREG_CRTCEXT1_VSYNCOFF	BIT(5)
#घोषणा MGAREG_CRTCEXT1_HSYNCOFF	BIT(4)

#घोषणा MGAREG_CRTCEXT3_MGAMODE		BIT(7)

/* Cursor X and Y position */
#घोषणा MGA_CURPOSXL 0x3c0c
#घोषणा MGA_CURPOSXH 0x3c0d
#घोषणा MGA_CURPOSYL 0x3c0e
#घोषणा MGA_CURPOSYH 0x3c0f

/* MGA bits क्रम रेजिस्टरs PCI_OPTION_REG */
#घोषणा MGA1064_OPT_SYS_CLK_PCI   		( 0x00 << 0 )
#घोषणा MGA1064_OPT_SYS_CLK_PLL   		( 0x01 << 0 )
#घोषणा MGA1064_OPT_SYS_CLK_EXT   		( 0x02 << 0 )
#घोषणा MGA1064_OPT_SYS_CLK_MSK   		( 0x03 << 0 )

#घोषणा MGA1064_OPT_SYS_CLK_DIS   		( 0x01 << 2 )
#घोषणा MGA1064_OPT_G_CLK_DIV_1   		( 0x01 << 3 )
#घोषणा MGA1064_OPT_M_CLK_DIV_1   		( 0x01 << 4 )

#घोषणा MGA1064_OPT_SYS_PLL_PDN   		( 0x01 << 5 )
#घोषणा MGA1064_OPT_VGA_ION   		( 0x01 << 8 )

/* MGA रेजिस्टरs in PCI config space */
#घोषणा PCI_MGA_INDEX		0x44
#घोषणा PCI_MGA_DATA		0x48
#घोषणा PCI_MGA_OPTION		0x40
#घोषणा PCI_MGA_OPTION2		0x50
#घोषणा PCI_MGA_OPTION3		0x54

#घोषणा PCI_MGA_OPTION_HARDPWMSK	BIT(14)

#घोषणा RAMDAC_OFFSET		0x3c00

/* TVP3026 direct रेजिस्टरs */

#घोषणा TVP3026_INDEX		0x00
#घोषणा TVP3026_WADR_PAL	0x00
#घोषणा TVP3026_COL_PAL		0x01
#घोषणा TVP3026_PIX_RD_MSK	0x02
#घोषणा TVP3026_RADR_PAL	0x03
#घोषणा TVP3026_CUR_COL_ADDR	0x04
#घोषणा TVP3026_CUR_COL_DATA	0x05
#घोषणा TVP3026_DATA		0x0a
#घोषणा TVP3026_CUR_RAM		0x0b
#घोषणा TVP3026_CUR_XLOW	0x0c
#घोषणा TVP3026_CUR_XHI		0x0d
#घोषणा TVP3026_CUR_YLOW	0x0e
#घोषणा TVP3026_CUR_YHI		0x0f

/* TVP3026 indirect रेजिस्टरs */

#घोषणा TVP3026_SILICON_REV	0x01
#घोषणा TVP3026_CURSOR_CTL	0x06
#घोषणा TVP3026_LATCH_CTL	0x0f
#घोषणा TVP3026_TRUE_COLOR_CTL	0x18
#घोषणा TVP3026_MUX_CTL		0x19
#घोषणा TVP3026_CLK_SEL		0x1a
#घोषणा TVP3026_PAL_PAGE	0x1c
#घोषणा TVP3026_GEN_CTL		0x1d
#घोषणा TVP3026_MISC_CTL	0x1e
#घोषणा TVP3026_GEN_IO_CTL	0x2a
#घोषणा TVP3026_GEN_IO_DATA	0x2b
#घोषणा TVP3026_PLL_ADDR	0x2c
#घोषणा TVP3026_PIX_CLK_DATA	0x2d
#घोषणा TVP3026_MEM_CLK_DATA	0x2e
#घोषणा TVP3026_LOAD_CLK_DATA	0x2f
#घोषणा TVP3026_KEY_RED_LOW	0x32
#घोषणा TVP3026_KEY_RED_HI	0x33
#घोषणा TVP3026_KEY_GREEN_LOW	0x34
#घोषणा TVP3026_KEY_GREEN_HI	0x35
#घोषणा TVP3026_KEY_BLUE_LOW	0x36
#घोषणा TVP3026_KEY_BLUE_HI	0x37
#घोषणा TVP3026_KEY_CTL		0x38
#घोषणा TVP3026_MCLK_CTL	0x39
#घोषणा TVP3026_SENSE_TEST	0x3a
#घोषणा TVP3026_TEST_DATA	0x3b
#घोषणा TVP3026_CRC_LSB		0x3c
#घोषणा TVP3026_CRC_MSB		0x3d
#घोषणा TVP3026_CRC_CTL		0x3e
#घोषणा TVP3026_ID		0x3f
#घोषणा TVP3026_RESET		0xff


/* MGA1064 DAC Register file */
/* MGA1064 direct रेजिस्टरs */

#घोषणा MGA1064_INDEX		0x00
#घोषणा MGA1064_WADR_PAL	0x00
#घोषणा MGA1064_SPAREREG        0x00
#घोषणा MGA1064_COL_PAL		0x01
#घोषणा MGA1064_PIX_RD_MSK	0x02
#घोषणा MGA1064_RADR_PAL	0x03
#घोषणा MGA1064_DATA		0x0a

#घोषणा MGA1064_CUR_XLOW	0x0c
#घोषणा MGA1064_CUR_XHI		0x0d
#घोषणा MGA1064_CUR_YLOW	0x0e
#घोषणा MGA1064_CUR_YHI		0x0f

/* MGA1064 indirect रेजिस्टरs */
#घोषणा MGA1064_DVI_PIPE_CTL    0x03
#घोषणा MGA1064_CURSOR_BASE_ADR_LOW	0x04
#घोषणा MGA1064_CURSOR_BASE_ADR_HI	0x05
#घोषणा MGA1064_CURSOR_CTL	0x06
#घोषणा MGA1064_CURSOR_COL0_RED	0x08
#घोषणा MGA1064_CURSOR_COL0_GREEN	0x09
#घोषणा MGA1064_CURSOR_COL0_BLUE	0x0a

#घोषणा MGA1064_CURSOR_COL1_RED	0x0c
#घोषणा MGA1064_CURSOR_COL1_GREEN	0x0d
#घोषणा MGA1064_CURSOR_COL1_BLUE	0x0e

#घोषणा MGA1064_CURSOR_COL2_RED	0x010
#घोषणा MGA1064_CURSOR_COL2_GREEN	0x011
#घोषणा MGA1064_CURSOR_COL2_BLUE	0x012

#घोषणा MGA1064_VREF_CTL	0x018

#घोषणा MGA1064_MUL_CTL		0x19
#घोषणा MGA1064_MUL_CTL_8bits		0x0
#घोषणा MGA1064_MUL_CTL_15bits		0x01
#घोषणा MGA1064_MUL_CTL_16bits		0x02
#घोषणा MGA1064_MUL_CTL_24bits		0x03
#घोषणा MGA1064_MUL_CTL_32bits		0x04
#घोषणा MGA1064_MUL_CTL_2G8V16bits		0x05
#घोषणा MGA1064_MUL_CTL_G16V16bits		0x06
#घोषणा MGA1064_MUL_CTL_32_24bits		0x07

#घोषणा MGA1064_PIX_CLK_CTL		0x1a
#घोषणा MGA1064_PIX_CLK_CTL_CLK_DIS		( 0x01 << 2 )
#घोषणा MGA1064_PIX_CLK_CTL_CLK_POW_DOWN	( 0x01 << 3 )
#घोषणा MGA1064_PIX_CLK_CTL_SEL_PCI		( 0x00 << 0 )
#घोषणा MGA1064_PIX_CLK_CTL_SEL_PLL		( 0x01 << 0 )
#घोषणा MGA1064_PIX_CLK_CTL_SEL_EXT		( 0x02 << 0 )
#घोषणा MGA1064_PIX_CLK_CTL_SEL_MSK		( 0x03 << 0 )

#घोषणा MGA1064_GEN_CTL		0x1d
#घोषणा MGA1064_GEN_CTL_SYNC_ON_GREEN_DIS      (0x01 << 5)
#घोषणा MGA1064_MISC_CTL	0x1e
#घोषणा MGA1064_MISC_CTL_DAC_EN                ( 0x01 << 0 )
#घोषणा MGA1064_MISC_CTL_VGA   		( 0x01 << 1 )
#घोषणा MGA1064_MISC_CTL_DIS_CON   		( 0x03 << 1 )
#घोषणा MGA1064_MISC_CTL_MAFC   		( 0x02 << 1 )
#घोषणा MGA1064_MISC_CTL_VGA8   		( 0x01 << 3 )
#घोषणा MGA1064_MISC_CTL_DAC_RAM_CS   		( 0x01 << 4 )

#घोषणा MGA1064_GEN_IO_CTL2	0x29
#घोषणा MGA1064_GEN_IO_CTL	0x2a
#घोषणा MGA1064_GEN_IO_DATA	0x2b
#घोषणा MGA1064_SYS_PLL_M	0x2c
#घोषणा MGA1064_SYS_PLL_N	0x2d
#घोषणा MGA1064_SYS_PLL_P	0x2e
#घोषणा MGA1064_SYS_PLL_STAT	0x2f

#घोषणा MGA1064_REMHEADCTL     0x30
#घोषणा MGA1064_REMHEADCTL_CLKDIS ( 0x01 << 0 )
#घोषणा MGA1064_REMHEADCTL_CLKSL_OFF ( 0x00 << 1 )
#घोषणा MGA1064_REMHEADCTL_CLKSL_PLL ( 0x01 << 1 )
#घोषणा MGA1064_REMHEADCTL_CLKSL_PCI ( 0x02 << 1 )
#घोषणा MGA1064_REMHEADCTL_CLKSL_MSK ( 0x03 << 1 )

#घोषणा MGA1064_REMHEADCTL2     0x31

#घोषणा MGA1064_ZOOM_CTL	0x38
#घोषणा MGA1064_SENSE_TST	0x3a

#घोषणा MGA1064_CRC_LSB		0x3c
#घोषणा MGA1064_CRC_MSB		0x3d
#घोषणा MGA1064_CRC_CTL		0x3e
#घोषणा MGA1064_COL_KEY_MSK_LSB		0x40
#घोषणा MGA1064_COL_KEY_MSK_MSB		0x41
#घोषणा MGA1064_COL_KEY_LSB		0x42
#घोषणा MGA1064_COL_KEY_MSB		0x43
#घोषणा MGA1064_PIX_PLLA_M	0x44
#घोषणा MGA1064_PIX_PLLA_N	0x45
#घोषणा MGA1064_PIX_PLLA_P	0x46
#घोषणा MGA1064_PIX_PLLB_M	0x48
#घोषणा MGA1064_PIX_PLLB_N	0x49
#घोषणा MGA1064_PIX_PLLB_P	0x4a
#घोषणा MGA1064_PIX_PLLC_M	0x4c
#घोषणा MGA1064_PIX_PLLC_N	0x4d
#घोषणा MGA1064_PIX_PLLC_P	0x4e

#घोषणा MGA1064_PIX_PLL_STAT	0x4f

/*Added क्रम G450 dual head*/

#घोषणा MGA1064_VID_PLL_STAT    0x8c
#घोषणा MGA1064_VID_PLL_P       0x8D
#घोषणा MGA1064_VID_PLL_M       0x8E
#घोषणा MGA1064_VID_PLL_N       0x8F

/* Modअगरied PLL क्रम G200 Winbond (G200WB) */
#घोषणा MGA1064_WB_PIX_PLLC_M	0xb7
#घोषणा MGA1064_WB_PIX_PLLC_N	0xb6
#घोषणा MGA1064_WB_PIX_PLLC_P	0xb8

/* Modअगरied PLL क्रम G200 Maxim (G200EV) */
#घोषणा MGA1064_EV_PIX_PLLC_M	0xb6
#घोषणा MGA1064_EV_PIX_PLLC_N	0xb7
#घोषणा MGA1064_EV_PIX_PLLC_P	0xb8

/* Modअगरied PLL क्रम G200 EH */
#घोषणा MGA1064_EH_PIX_PLLC_M   0xb6
#घोषणा MGA1064_EH_PIX_PLLC_N   0xb7
#घोषणा MGA1064_EH_PIX_PLLC_P   0xb8

/* Modअगरied PLL क्रम G200 Maxim (G200ER) */
#घोषणा MGA1064_ER_PIX_PLLC_M	0xb7
#घोषणा MGA1064_ER_PIX_PLLC_N	0xb6
#घोषणा MGA1064_ER_PIX_PLLC_P	0xb8

#घोषणा MGA1064_DISP_CTL        0x8a
#घोषणा MGA1064_DISP_CTL_DAC1OUTSEL_MASK       0x01
#घोषणा MGA1064_DISP_CTL_DAC1OUTSEL_DIS        0x00
#घोषणा MGA1064_DISP_CTL_DAC1OUTSEL_EN         0x01
#घोषणा MGA1064_DISP_CTL_DAC2OUTSEL_MASK       (0x03 << 2)
#घोषणा MGA1064_DISP_CTL_DAC2OUTSEL_DIS        0x00
#घोषणा MGA1064_DISP_CTL_DAC2OUTSEL_CRTC1      (0x01 << 2)
#घोषणा MGA1064_DISP_CTL_DAC2OUTSEL_CRTC2      (0x02 << 2)
#घोषणा MGA1064_DISP_CTL_DAC2OUTSEL_TVE        (0x03 << 2)
#घोषणा MGA1064_DISP_CTL_PANOUTSEL_MASK        (0x03 << 5)
#घोषणा MGA1064_DISP_CTL_PANOUTSEL_DIS         0x00
#घोषणा MGA1064_DISP_CTL_PANOUTSEL_CRTC1       (0x01 << 5)
#घोषणा MGA1064_DISP_CTL_PANOUTSEL_CRTC2RGB    (0x02 << 5)
#घोषणा MGA1064_DISP_CTL_PANOUTSEL_CRTC2656    (0x03 << 5)

#घोषणा MGA1064_SYNC_CTL        0x8b

#घोषणा MGA1064_PWR_CTL         0xa0
#घोषणा MGA1064_PWR_CTL_DAC2_EN                (0x01 << 0)
#घोषणा MGA1064_PWR_CTL_VID_PLL_EN             (0x01 << 1)
#घोषणा MGA1064_PWR_CTL_PANEL_EN               (0x01 << 2)
#घोषणा MGA1064_PWR_CTL_RFIFO_EN               (0x01 << 3)
#घोषणा MGA1064_PWR_CTL_CFIFO_EN               (0x01 << 4)

#घोषणा MGA1064_PAN_CTL         0xa2

/* Using crtc2 */
#घोषणा MGAREG2_C2CTL            0x10
#घोषणा MGAREG2_C2HPARAM         0x14
#घोषणा MGAREG2_C2HSYNC          0x18
#घोषणा MGAREG2_C2VPARAM         0x1c
#घोषणा MGAREG2_C2VSYNC          0x20
#घोषणा MGAREG2_C2STARTADD0      0x28

#घोषणा MGAREG2_C2OFFSET         0x40
#घोषणा MGAREG2_C2DATACTL        0x4c

#घोषणा MGAREG_C2CTL            0x3c10
#घोषणा MGAREG_C2CTL_C2_EN                     0x01

#घोषणा MGAREG_C2_HIPRILVL_M                   (0x07 << 4)
#घोषणा MGAREG_C2_MAXHIPRI_M                   (0x07 << 8)

#घोषणा MGAREG_C2CTL_PIXCLKSEL_MASK            (0x03 << 1)
#घोषणा MGAREG_C2CTL_PIXCLKSELH_MASK           (0x01 << 14)
#घोषणा MGAREG_C2CTL_PIXCLKSEL_PCICLK          0x00
#घोषणा MGAREG_C2CTL_PIXCLKSEL_VDOCLK          (0x01 << 1)
#घोषणा MGAREG_C2CTL_PIXCLKSEL_PIXELPLL        (0x02 << 1)
#घोषणा MGAREG_C2CTL_PIXCLKSEL_VIDEOPLL        (0x03 << 1)
#घोषणा MGAREG_C2CTL_PIXCLKSEL_VDCLK           (0x01 << 14)

#घोषणा MGAREG_C2CTL_PIXCLKSEL_CRISTAL         (0x01 << 1) | (0x01 << 14)
#घोषणा MGAREG_C2CTL_PIXCLKSEL_SYSTEMPLL       (0x02 << 1) | (0x01 << 14)

#घोषणा MGAREG_C2CTL_PIXCLKDIS_MASK            (0x01 << 3)
#घोषणा MGAREG_C2CTL_PIXCLKDIS_DISABLE         (0x01 << 3)

#घोषणा MGAREG_C2CTL_CRTCDACSEL_MASK           (0x01 << 20)
#घोषणा MGAREG_C2CTL_CRTCDACSEL_CRTC1          0x00
#घोषणा MGAREG_C2CTL_CRTCDACSEL_CRTC2          (0x01 << 20)

#घोषणा MGAREG_C2HPARAM         0x3c14
#घोषणा MGAREG_C2HSYNC          0x3c18
#घोषणा MGAREG_C2VPARAM         0x3c1c
#घोषणा MGAREG_C2VSYNC          0x3c20
#घोषणा MGAREG_C2STARTADD0      0x3c28

#घोषणा MGAREG_C2OFFSET         0x3c40
#घोषणा MGAREG_C2DATACTL        0x3c4c

/* video रेजिस्टर */

#घोषणा MGAREG_BESA1C3ORG	0x3d60
#घोषणा MGAREG_BESA1CORG	0x3d10
#घोषणा MGAREG_BESA1ORG		0x3d00
#घोषणा MGAREG_BESCTL		0x3d20
#घोषणा MGAREG_BESGLOBCTL	0x3dc0
#घोषणा MGAREG_BESHCOORD	0x3d28
#घोषणा MGAREG_BESHISCAL	0x3d30
#घोषणा MGAREG_BESHSRCEND	0x3d3c
#घोषणा MGAREG_BESHSRCLST	0x3d50
#घोषणा MGAREG_BESHSRCST	0x3d38
#घोषणा MGAREG_BESLUMACTL	0x3d40
#घोषणा MGAREG_BESPITCH		0x3d24
#घोषणा MGAREG_BESV1SRCLST	0x3d54
#घोषणा MGAREG_BESV1WGHT	0x3d48
#घोषणा MGAREG_BESVCOORD	0x3d2c
#घोषणा MGAREG_BESVISCAL	0x3d34

/* texture engine रेजिस्टरs */

#घोषणा MGAREG_TMR0		0x2c00
#घोषणा MGAREG_TMR1		0x2c04
#घोषणा MGAREG_TMR2		0x2c08
#घोषणा MGAREG_TMR3		0x2c0c
#घोषणा MGAREG_TMR4		0x2c10
#घोषणा MGAREG_TMR5		0x2c14
#घोषणा MGAREG_TMR6		0x2c18
#घोषणा MGAREG_TMR7		0x2c1c
#घोषणा MGAREG_TMR8		0x2c20
#घोषणा MGAREG_TEXORG		0x2c24
#घोषणा MGAREG_TEXWIDTH		0x2c28
#घोषणा MGAREG_TEXHEIGHT	0x2c2c
#घोषणा MGAREG_TEXCTL		0x2c30
#    define MGA_TW4                             (0x00000000)
#    define MGA_TW8                             (0x00000001)
#    define MGA_TW15                            (0x00000002)
#    define MGA_TW16                            (0x00000003)
#    define MGA_TW12                            (0x00000004)
#    define MGA_TW32                            (0x00000006)
#    define MGA_TW8A                            (0x00000007)
#    define MGA_TW8AL                           (0x00000008)
#    define MGA_TW422                           (0x0000000A)
#    define MGA_TW422UYVY                       (0x0000000B)
#    define MGA_PITCHLIN                        (0x00000100)
#    define MGA_NOPERSPECTIVE                   (0x00200000)
#    define MGA_TAKEY                           (0x02000000)
#    define MGA_TAMASK                          (0x04000000)
#    define MGA_CLAMPUV                         (0x18000000)
#    define MGA_TEXMODULATE                     (0x20000000)
#घोषणा MGAREG_TEXCTL2		0x2c3c
#    define MGA_G400_TC2_MAGIC                  (0x00008000)
#    define MGA_TC2_DECALBLEND                  (0x00000001)
#    define MGA_TC2_IDECAL                      (0x00000002)
#    define MGA_TC2_DECALDIS                    (0x00000004)
#    define MGA_TC2_CKSTRANSDIS                 (0x00000010)
#    define MGA_TC2_BORDEREN                    (0x00000020)
#    define MGA_TC2_SPECEN                      (0x00000040)
#    define MGA_TC2_DUALTEX                     (0x00000080)
#    define MGA_TC2_TABLEFOG                    (0x00000100)
#    define MGA_TC2_BUMPMAP                     (0x00000200)
#    define MGA_TC2_SELECT_TMU1                 (0x80000000)
#घोषणा MGAREG_TEXTRANS		0x2c34
#घोषणा MGAREG_TEXTRANSHIGH	0x2c38
#घोषणा MGAREG_TEXFILTER	0x2c58
#    define MGA_MIN_NRST                        (0x00000000)
#    define MGA_MIN_BILIN                       (0x00000002)
#    define MGA_MIN_ANISO                       (0x0000000D)
#    define MGA_MAG_NRST                        (0x00000000)
#    define MGA_MAG_BILIN                       (0x00000020)
#    define MGA_FILTERALPHA                     (0x00100000)
#घोषणा MGAREG_ALPHASTART	0x2c70
#घोषणा MGAREG_ALPHAXINC	0x2c74
#घोषणा MGAREG_ALPHAYINC	0x2c78
#घोषणा MGAREG_ALPHACTRL	0x2c7c
#    define MGA_SRC_ZERO                        (0x00000000)
#    define MGA_SRC_ONE                         (0x00000001)
#    define MGA_SRC_DST_COLOR                   (0x00000002)
#    define MGA_SRC_ONE_MINUS_DST_COLOR         (0x00000003)
#    define MGA_SRC_ALPHA                       (0x00000004)
#    define MGA_SRC_ONE_MINUS_SRC_ALPHA         (0x00000005)
#    define MGA_SRC_DST_ALPHA                   (0x00000006)
#    define MGA_SRC_ONE_MINUS_DST_ALPHA         (0x00000007)
#    define MGA_SRC_SRC_ALPHA_SATURATE          (0x00000008)
#    define MGA_SRC_BLEND_MASK                  (0x0000000f)
#    define MGA_DST_ZERO                        (0x00000000)
#    define MGA_DST_ONE                         (0x00000010)
#    define MGA_DST_SRC_COLOR                   (0x00000020)
#    define MGA_DST_ONE_MINUS_SRC_COLOR         (0x00000030)
#    define MGA_DST_SRC_ALPHA                   (0x00000040)
#    define MGA_DST_ONE_MINUS_SRC_ALPHA         (0x00000050)
#    define MGA_DST_DST_ALPHA                   (0x00000060)
#    define MGA_DST_ONE_MINUS_DST_ALPHA         (0x00000070)
#    define MGA_DST_BLEND_MASK                  (0x00000070)
#    define MGA_ALPHACHANNEL                    (0x00000100)
#    define MGA_VIDEOALPHA                      (0x00000200)
#    define MGA_DIFFUSEDALPHA                   (0x01000000)
#    define MGA_MODULATEDALPHA                  (0x02000000)
#घोषणा MGAREG_TDUALSTAGE0                      (0x2CF8)
#घोषणा MGAREG_TDUALSTAGE1                      (0x2CFC)
#    define MGA_TDS_COLOR_ARG2_DIFFUSE          (0x00000000)
#    define MGA_TDS_COLOR_ARG2_SPECULAR         (0x00000001)
#    define MGA_TDS_COLOR_ARG2_FCOL             (0x00000002)
#    define MGA_TDS_COLOR_ARG2_PREVSTAGE        (0x00000003)
#    define MGA_TDS_COLOR_ALPHA_DIFFUSE         (0x00000000)
#    define MGA_TDS_COLOR_ALPHA_FCOL            (0x00000004)
#    define MGA_TDS_COLOR_ALPHA_CURRTEX         (0x00000008)
#    define MGA_TDS_COLOR_ALPHA_PREVTEX         (0x0000000c)
#    define MGA_TDS_COLOR_ALPHA_PREVSTAGE       (0x00000010)
#    define MGA_TDS_COLOR_ARG1_REPLICATEALPHA   (0x00000020)
#    define MGA_TDS_COLOR_ARG1_INV              (0x00000040)
#    define MGA_TDS_COLOR_ARG2_REPLICATEALPHA   (0x00000080)
#    define MGA_TDS_COLOR_ARG2_INV              (0x00000100)
#    define MGA_TDS_COLOR_ALPHA1INV             (0x00000200)
#    define MGA_TDS_COLOR_ALPHA2INV             (0x00000400)
#    define MGA_TDS_COLOR_ARG1MUL_ALPHA1        (0x00000800)
#    define MGA_TDS_COLOR_ARG2MUL_ALPHA2        (0x00001000)
#    define MGA_TDS_COLOR_ARG1ADD_MULOUT        (0x00002000)
#    define MGA_TDS_COLOR_ARG2ADD_MULOUT        (0x00004000)
#    define MGA_TDS_COLOR_MODBRIGHT_2X          (0x00008000)
#    define MGA_TDS_COLOR_MODBRIGHT_4X          (0x00010000)
#    define MGA_TDS_COLOR_ADD_SUB               (0x00000000)
#    define MGA_TDS_COLOR_ADD_ADD               (0x00020000)
#    define MGA_TDS_COLOR_ADD2X                 (0x00040000)
#    define MGA_TDS_COLOR_ADDBIAS               (0x00080000)
#    define MGA_TDS_COLOR_BLEND                 (0x00100000)
#    define MGA_TDS_COLOR_SEL_ARG1              (0x00000000)
#    define MGA_TDS_COLOR_SEL_ARG2              (0x00200000)
#    define MGA_TDS_COLOR_SEL_ADD               (0x00400000)
#    define MGA_TDS_COLOR_SEL_MUL               (0x00600000)
#    define MGA_TDS_ALPHA_ARG1_INV              (0x00800000)
#    define MGA_TDS_ALPHA_ARG2_DIFFUSE          (0x00000000)
#    define MGA_TDS_ALPHA_ARG2_FCOL             (0x01000000)
#    define MGA_TDS_ALPHA_ARG2_PREVTEX          (0x02000000)
#    define MGA_TDS_ALPHA_ARG2_PREVSTAGE        (0x03000000)
#    define MGA_TDS_ALPHA_ARG2_INV              (0x04000000)
#    define MGA_TDS_ALPHA_ADD                   (0x08000000)
#    define MGA_TDS_ALPHA_ADDBIAS               (0x10000000)
#    define MGA_TDS_ALPHA_ADD2X                 (0x20000000)
#    define MGA_TDS_ALPHA_SEL_ARG1              (0x00000000)
#    define MGA_TDS_ALPHA_SEL_ARG2              (0x40000000)
#    define MGA_TDS_ALPHA_SEL_ADD               (0x80000000)
#    define MGA_TDS_ALPHA_SEL_MUL               (0xc0000000)

#घोषणा MGAREG_DWGSYNC		0x2c4c

#घोषणा MGAREG_AGP_PLL		0x1e4c
#घोषणा MGA_AGP2XPLL_ENABLE		0x1
#घोषणा MGA_AGP2XPLL_DISABLE		0x0

#पूर्ण_अगर
