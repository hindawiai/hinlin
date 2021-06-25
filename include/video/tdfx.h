<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TDFX_H
#घोषणा _TDFX_H

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

/* membase0 रेजिस्टर offsets */
#घोषणा STATUS		0x00
#घोषणा PCIINIT0	0x04
#घोषणा SIPMONITOR	0x08
#घोषणा LFBMEMORYCONFIG	0x0c
#घोषणा MISCINIT0	0x10
#घोषणा MISCINIT1	0x14
#घोषणा DRAMINIT0	0x18
#घोषणा DRAMINIT1	0x1c
#घोषणा AGPINIT		0x20
#घोषणा TMUGBEINIT	0x24
#घोषणा VGAINIT0	0x28
#घोषणा VGAINIT1	0x2c
#घोषणा DRAMCOMMAND	0x30
#घोषणा DRAMDATA	0x34
/* reserved	0x38 */
/* reserved	0x3c */
#घोषणा PLLCTRL0	0x40
#घोषणा PLLCTRL1	0x44
#घोषणा PLLCTRL2	0x48
#घोषणा DACMODE		0x4c
#घोषणा DACADDR		0x50
#घोषणा DACDATA		0x54
#घोषणा RGBMAXDELTA	0x58
#घोषणा VIDPROCCFG	0x5c
#घोषणा HWCURPATADDR	0x60
#घोषणा HWCURLOC	0x64
#घोषणा HWCURC0		0x68
#घोषणा HWCURC1		0x6c
#घोषणा VIDINFORMAT	0x70
#घोषणा VIDINSTATUS	0x74
#घोषणा VIDSERPARPORT	0x78
#घोषणा VIDINXDELTA	0x7c
#घोषणा VIDININITERR	0x80
#घोषणा VIDINYDELTA	0x84
#घोषणा VIDPIXBUFTHOLD	0x88
#घोषणा VIDCHRMIN	0x8c
#घोषणा VIDCHRMAX	0x90
#घोषणा VIDCURLIN	0x94
#घोषणा VIDSCREENSIZE	0x98
#घोषणा VIDOVRSTARTCRD	0x9c
#घोषणा VIDOVRENDCRD	0xa0
#घोषणा VIDOVRDUDX	0xa4
#घोषणा VIDOVRDUDXOFF	0xa8
#घोषणा VIDOVRDVDY	0xac
/* ... */
#घोषणा VIDOVRDVDYOFF	0xe0
#घोषणा VIDDESKSTART	0xe4
#घोषणा VIDDESKSTRIDE	0xe8
#घोषणा VIDINADDR0	0xec
#घोषणा VIDINADDR1	0xf0
#घोषणा VIDINADDR2	0xf4
#घोषणा VIDINSTRIDE	0xf8
#घोषणा VIDCUROVRSTART	0xfc

#घोषणा INTCTRL		(0x00100000 + 0x04)
#घोषणा CLIP0MIN	(0x00100000 + 0x08)
#घोषणा CLIP0MAX	(0x00100000 + 0x0c)
#घोषणा DSTBASE		(0x00100000 + 0x10)
#घोषणा DSTFORMAT	(0x00100000 + 0x14)
#घोषणा SRCBASE		(0x00100000 + 0x34)
#घोषणा COMMANDEXTRA_2D	(0x00100000 + 0x38)
#घोषणा CLIP1MIN	(0x00100000 + 0x4c)
#घोषणा CLIP1MAX	(0x00100000 + 0x50)
#घोषणा SRCFORMAT	(0x00100000 + 0x54)
#घोषणा SRCSIZE		(0x00100000 + 0x58)
#घोषणा SRCXY		(0x00100000 + 0x5c)
#घोषणा COLORBACK	(0x00100000 + 0x60)
#घोषणा COLORFORE	(0x00100000 + 0x64)
#घोषणा DSTSIZE		(0x00100000 + 0x68)
#घोषणा DSTXY		(0x00100000 + 0x6c)
#घोषणा COMMAND_2D	(0x00100000 + 0x70)
#घोषणा LAUNCH_2D	(0x00100000 + 0x80)

#घोषणा COMMAND_3D	(0x00200000 + 0x120)

/* रेजिस्टर bitfields (not all, only as needed) */

/* COMMAND_2D reg. values */
#घोषणा TDFX_ROP_COPY		0xcc	/* src */
#घोषणा TDFX_ROP_INVERT		0x55	/* NOT dst */
#घोषणा TDFX_ROP_XOR		0x66	/* src XOR dst */

#घोषणा AUTOINC_DSTX			BIT(10)
#घोषणा AUTOINC_DSTY			BIT(11)
#घोषणा COMMAND_2D_FILLRECT		0x05
#घोषणा COMMAND_2D_S2S_BITBLT		0x01	/* screen to screen */
#घोषणा COMMAND_2D_H2S_BITBLT		0x03	/* host to screen */

#घोषणा COMMAND_3D_NOP			0x00
#घोषणा STATUS_RETRACE			BIT(6)
#घोषणा STATUS_BUSY			BIT(9)
#घोषणा MISCINIT1_CLUT_INV		BIT(0)
#घोषणा MISCINIT1_2DBLOCK_DIS		BIT(15)
#घोषणा DRAMINIT0_SGRAM_NUM		BIT(26)
#घोषणा DRAMINIT0_SGRAM_TYPE		BIT(27)
#घोषणा DRAMINIT0_SGRAM_TYPE_MASK       (BIT(27) | BIT(28) | BIT(29))
#घोषणा DRAMINIT0_SGRAM_TYPE_SHIFT      27
#घोषणा DRAMINIT1_MEM_SDRAM		BIT(30)
#घोषणा VGAINIT0_VGA_DISABLE		BIT(0)
#घोषणा VGAINIT0_EXT_TIMING		BIT(1)
#घोषणा VGAINIT0_8BIT_DAC		BIT(2)
#घोषणा VGAINIT0_EXT_ENABLE		BIT(6)
#घोषणा VGAINIT0_WAKEUP_3C3		BIT(8)
#घोषणा VGAINIT0_LEGACY_DISABLE		BIT(9)
#घोषणा VGAINIT0_ALT_READBACK		BIT(10)
#घोषणा VGAINIT0_FAST_BLINK		BIT(11)
#घोषणा VGAINIT0_EXTSHIFTOUT		BIT(12)
#घोषणा VGAINIT0_DECODE_3C6		BIT(13)
#घोषणा VGAINIT0_SGRAM_HBLANK_DISABLE	BIT(22)
#घोषणा VGAINIT1_MASK			0x1fffff
#घोषणा VIDCFG_VIDPROC_ENABLE		BIT(0)
#घोषणा VIDCFG_CURS_X11			BIT(1)
#घोषणा VIDCFG_INTERLACE		BIT(3)
#घोषणा VIDCFG_HALF_MODE		BIT(4)
#घोषणा VIDCFG_DESK_ENABLE		BIT(7)
#घोषणा VIDCFG_CLUT_BYPASS		BIT(10)
#घोषणा VIDCFG_2X			BIT(26)
#घोषणा VIDCFG_HWCURSOR_ENABLE		BIT(27)
#घोषणा VIDCFG_PIXFMT_SHIFT             18
#घोषणा DACMODE_2X			BIT(0)

/* I2C bit locations in the VIDSERPARPORT रेजिस्टर */
#घोषणा DDC_ENAB	0x00040000
#घोषणा DDC_SCL_OUT	0x00080000
#घोषणा DDC_SDA_OUT	0x00100000
#घोषणा DDC_SCL_IN	0x00200000
#घोषणा DDC_SDA_IN	0x00400000
#घोषणा I2C_ENAB	0x00800000
#घोषणा I2C_SCL_OUT	0x01000000
#घोषणा I2C_SDA_OUT	0x02000000
#घोषणा I2C_SCL_IN	0x04000000
#घोषणा I2C_SDA_IN	0x08000000

/* VGA rubbish, need to change this क्रम multihead support */
#घोषणा MISC_W		0x3c2
#घोषणा MISC_R		0x3cc
#घोषणा SEQ_I		0x3c4
#घोषणा SEQ_D		0x3c5
#घोषणा CRT_I		0x3d4
#घोषणा CRT_D		0x3d5
#घोषणा ATT_IW		0x3c0
#घोषणा IS1_R		0x3da
#घोषणा GRA_I		0x3ce
#घोषणा GRA_D		0x3cf

#अगर_घोषित __KERNEL__

काष्ठा banshee_reg अणु
	/* VGA rubbish */
	अचिन्हित अक्षर att[21];
	अचिन्हित अक्षर crt[25];
	अचिन्हित अक्षर gra[9];
	अचिन्हित अक्षर misc[1];
	अचिन्हित अक्षर seq[5];

	/* Banshee extensions */
	अचिन्हित अक्षर ext[2];
	अचिन्हित दीर्घ vidcfg;
	अचिन्हित दीर्घ vidpll;
	अचिन्हित दीर्घ mempll;
	अचिन्हित दीर्घ gfxpll;
	अचिन्हित दीर्घ dacmode;
	अचिन्हित दीर्घ vgainit0;
	अचिन्हित दीर्घ vgainit1;
	अचिन्हित दीर्घ screensize;
	अचिन्हित दीर्घ stride;
	अचिन्हित दीर्घ cursloc;
	अचिन्हित दीर्घ curspataddr;
	अचिन्हित दीर्घ cursc0;
	अचिन्हित दीर्घ cursc1;
	अचिन्हित दीर्घ startaddr;
	अचिन्हित दीर्घ clip0min;
	अचिन्हित दीर्घ clip0max;
	अचिन्हित दीर्घ clip1min;
	अचिन्हित दीर्घ clip1max;
	अचिन्हित दीर्घ miscinit0;
पूर्ण;

काष्ठा tdfx_par;

काष्ठा tdfxfb_i2c_chan अणु
	काष्ठा tdfx_par *par;
	काष्ठा i2c_adapter adapter;
	काष्ठा i2c_algo_bit_data algo;
पूर्ण;

काष्ठा tdfx_par अणु
	u32 max_pixघड़ी;
	u32 palette[16];
	व्योम __iomem *regbase_virt;
	अचिन्हित दीर्घ iobase;
	पूर्णांक wc_cookie;
#अगर_घोषित CONFIG_FB_3DFX_I2C
	काष्ठा tdfxfb_i2c_chan chan[2];
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर	/* __KERNEL__ */

#पूर्ण_अगर	/* _TDFX_H */

