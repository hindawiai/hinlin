<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  tw68-reg.h - TW68xx रेजिस्टर offsets
 *
 *  Much of this code is derived from the cx88 and sa7134 drivers, which
 *  were in turn derived from the bt87x driver.  The original work was by
 *  Gerd Knorr; more recently the code was enhanced by Mauro Carvalho Chehab,
 *  Hans Verkuil, Andy Walls and many others.  Their work is gratefully
 *  acknowledged.  Full credit goes to them - any problems within this code
 *  are mine.
 *
 *  Copyright (C) William M. Brack
 *
 *  Refactored and updated to the latest v4l core frameworks:
 *
 *  Copyright (C) 2014 Hans Verkuil <hverkuil@xs4all.nl>
*/

#अगर_अघोषित _TW68_REG_H_
#घोषणा _TW68_REG_H_

/* ---------------------------------------------------------------------- */
#घोषणा	TW68_DMAC		0x000
#घोषणा	TW68_DMAP_SA		0x004
#घोषणा	TW68_DMAP_EXE		0x008
#घोषणा	TW68_DMAP_PP		0x00c
#घोषणा	TW68_VBIC		0x010
#घोषणा	TW68_SBUSC		0x014
#घोषणा	TW68_SBUSSD		0x018
#घोषणा	TW68_INTSTAT		0x01C
#घोषणा	TW68_INTMASK		0x020
#घोषणा	TW68_GPIOC		0x024
#घोषणा	TW68_GPOE		0x028
#घोषणा	TW68_TESTREG		0x02C
#घोषणा	TW68_SBUSRD		0x030
#घोषणा	TW68_SBUS_TRIG		0x034
#घोषणा	TW68_CAP_CTL		0x040
#घोषणा	TW68_SUBSYS		0x054
#घोषणा	TW68_I2C_RST		0x064
#घोषणा	TW68_VBIINST		0x06C
/* define bits in FIFO and DMAP Control reg */
#घोषणा	TW68_DMAP_EN		(1 << 0)
#घोषणा	TW68_FIFO_EN		(1 << 1)
/* define the Interrupt Status Register bits */
#घोषणा	TW68_SBDONE		(1 << 0)
#घोषणा	TW68_DMAPI		(1 << 1)
#घोषणा	TW68_GPINT		(1 << 2)
#घोषणा	TW68_FFOF		(1 << 3)
#घोषणा	TW68_FDMIS		(1 << 4)
#घोषणा	TW68_DMAPERR		(1 << 5)
#घोषणा	TW68_PABORT		(1 << 6)
#घोषणा	TW68_SBDONE2		(1 << 12)
#घोषणा	TW68_SBERR2		(1 << 13)
#घोषणा	TW68_PPERR		(1 << 14)
#घोषणा	TW68_FFERR		(1 << 15)
#घोषणा	TW68_DET50		(1 << 16)
#घोषणा	TW68_FLOCK		(1 << 17)
#घोषणा	TW68_CCVALID		(1 << 18)
#घोषणा	TW68_VLOCK		(1 << 19)
#घोषणा	TW68_FIELD		(1 << 20)
#घोषणा	TW68_SLOCK		(1 << 21)
#घोषणा	TW68_HLOCK		(1 << 22)
#घोषणा	TW68_VDLOSS		(1 << 23)
#घोषणा	TW68_SBERR		(1 << 24)
/* define the i2c control रेजिस्टर bits */
#घोषणा	TW68_SBMODE		(0)
#घोषणा	TW68_WREN		(1)
#घोषणा	TW68_SSCLK		(6)
#घोषणा	TW68_SSDAT		(7)
#घोषणा	TW68_SBCLK		(8)
#घोषणा	TW68_WDLEN		(16)
#घोषणा	TW68_RDLEN		(20)
#घोषणा	TW68_SBRW		(24)
#घोषणा	TW68_SBDEV		(25)

#घोषणा	TW68_SBMODE_B		(1 << TW68_SBMODE)
#घोषणा	TW68_WREN_B		(1 << TW68_WREN)
#घोषणा	TW68_SSCLK_B		(1 << TW68_SSCLK)
#घोषणा	TW68_SSDAT_B		(1 << TW68_SSDAT)
#घोषणा	TW68_SBRW_B		(1 << TW68_SBRW)

#घोषणा	TW68_GPDATA		0x100
#घोषणा	TW68_STATUS1		0x204
#घोषणा	TW68_INFORM		0x208
#घोषणा	TW68_OPFORM		0x20C
#घोषणा	TW68_HSYNC		0x210
#घोषणा	TW68_ACNTL		0x218
#घोषणा	TW68_CROP_HI		0x21C
#घोषणा	TW68_VDELAY_LO		0x220
#घोषणा	TW68_VACTIVE_LO		0x224
#घोषणा	TW68_HDELAY_LO		0x228
#घोषणा	TW68_HACTIVE_LO		0x22C
#घोषणा	TW68_CNTRL1		0x230
#घोषणा	TW68_VSCALE_LO		0x234
#घोषणा	TW68_SCALE_HI		0x238
#घोषणा	TW68_HSCALE_LO		0x23C
#घोषणा	TW68_BRIGHT		0x240
#घोषणा	TW68_CONTRAST		0x244
#घोषणा	TW68_SHARPNESS		0x248
#घोषणा	TW68_SAT_U		0x24C
#घोषणा	TW68_SAT_V		0x250
#घोषणा	TW68_HUE		0x254
#घोषणा	TW68_SHARP2		0x258
#घोषणा	TW68_VSHARP		0x25C
#घोषणा	TW68_CORING		0x260
#घोषणा	TW68_VBICNTL		0x264
#घोषणा	TW68_CNTRL2		0x268
#घोषणा	TW68_CC_DATA		0x26C
#घोषणा	TW68_SDT		0x270
#घोषणा	TW68_SDTR		0x274
#घोषणा	TW68_RESERV2		0x278
#घोषणा	TW68_RESERV3		0x27C
#घोषणा	TW68_CLMPG		0x280
#घोषणा	TW68_IAGC		0x284
#घोषणा	TW68_AGCGAIN		0x288
#घोषणा	TW68_PEAKWT		0x28C
#घोषणा	TW68_CLMPL		0x290
#घोषणा	TW68_SYNCT		0x294
#घोषणा	TW68_MISSCNT		0x298
#घोषणा	TW68_PCLAMP		0x29C
#घोषणा	TW68_VCNTL1		0x2A0
#घोषणा	TW68_VCNTL2		0x2A4
#घोषणा	TW68_CKILL		0x2A8
#घोषणा	TW68_COMB		0x2AC
#घोषणा	TW68_LDLY		0x2B0
#घोषणा	TW68_MISC1		0x2B4
#घोषणा	TW68_LOOP		0x2B8
#घोषणा	TW68_MISC2		0x2BC
#घोषणा	TW68_MVSN		0x2C0
#घोषणा	TW68_STATUS2		0x2C4
#घोषणा	TW68_HFREF		0x2C8
#घोषणा	TW68_CLMD		0x2CC
#घोषणा	TW68_IDCNTL		0x2D0
#घोषणा	TW68_CLCNTL1		0x2D4

/* Audio */
#घोषणा	TW68_ACKI1		0x300
#घोषणा	TW68_ACKI2		0x304
#घोषणा	TW68_ACKI3		0x308
#घोषणा	TW68_ACKN1		0x30C
#घोषणा	TW68_ACKN2		0x310
#घोषणा	TW68_ACKN3		0x314
#घोषणा	TW68_SDIV		0x318
#घोषणा	TW68_LRDIV		0x31C
#घोषणा	TW68_ACCNTL		0x320

#घोषणा	TW68_VSCTL		0x3B8
#घोषणा	TW68_CHROMAGVAL		0x3BC

#घोषणा	TW68_F2CROP_HI		0x3DC
#घोषणा	TW68_F2VDELAY_LO	0x3E0
#घोषणा	TW68_F2VACTIVE_LO	0x3E4
#घोषणा	TW68_F2HDELAY_LO	0x3E8
#घोषणा	TW68_F2HACTIVE_LO	0x3EC
#घोषणा	TW68_F2CNT		0x3F0
#घोषणा	TW68_F2VSCALE_LO	0x3F4
#घोषणा	TW68_F2SCALE_HI		0x3F8
#घोषणा	TW68_F2HSCALE_LO	0x3FC

#घोषणा	RISC_INT_BIT		0x08000000
#घोषणा	RISC_SYNCO		0xC0000000
#घोषणा	RISC_SYNCE		0xD0000000
#घोषणा	RISC_JUMP		0xB0000000
#घोषणा	RISC_LINESTART		0x90000000
#घोषणा	RISC_INLINE		0xA0000000

#घोषणा VideoFormatNTSC		 0
#घोषणा VideoFormatNTSCJapan	 0
#घोषणा VideoFormatPALBDGHI	 1
#घोषणा VideoFormatSECAM	 2
#घोषणा VideoFormatNTSC443	 3
#घोषणा VideoFormatPALM		 4
#घोषणा VideoFormatPALN		 5
#घोषणा VideoFormatPALNC	 5
#घोषणा VideoFormatPAL60	 6
#घोषणा VideoFormatAuto		 7

#घोषणा ColorFormatRGB32	 0x00
#घोषणा ColorFormatRGB24	 0x10
#घोषणा ColorFormatRGB16	 0x20
#घोषणा ColorFormatRGB15	 0x30
#घोषणा ColorFormatYUY2		 0x40
#घोषणा ColorFormatBSWAP         0x04
#घोषणा ColorFormatWSWAP         0x08
#घोषणा ColorFormatGamma         0x80
#पूर्ण_अगर
