<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* DMA controller रेजिस्टरs */
#घोषणा REG8_1(a0) ((स्थिर u16[8]) अणु a0, a0 + 1, a0 + 2, a0 + 3, \
				     a0 + 4, a0 + 5, a0 + 6, a0 + 7पूर्ण)
#घोषणा REG8_2(a0) ((स्थिर u16[8]) अणु a0, a0 + 2, a0 + 4, a0 + 6,	\
				     a0 + 8, a0 + 0xa, a0 + 0xc, a0 + 0xeपूर्ण)
#घोषणा REG8_8(a0) ((स्थिर u16[8]) अणु a0, a0 + 8, a0 + 0x10, a0 + 0x18, \
				     a0 + 0x20, a0 + 0x28, a0 + 0x30, \
				     a0 + 0x38पूर्ण)
#घोषणा INT_STATUS		0x00
#घोषणा PB_STATUS		0x01
#घोषणा DMA_CMD			0x02
#घोषणा VIDEO_FIFO_STATUS	0x03
#घोषणा VIDEO_CHANNEL_ID	0x04
#घोषणा VIDEO_PARSER_STATUS	0x05
#घोषणा SYS_SOFT_RST		0x06
#घोषणा DMA_PAGE_TABLE0_ADDR	((स्थिर u16[8]) अणु 0x08, 0xd0, 0xd2, 0xd4, \
						  0xd6, 0xd8, 0xda, 0xdc पूर्ण)
#घोषणा DMA_PAGE_TABLE1_ADDR	((स्थिर u16[8]) अणु 0x09, 0xd1, 0xd3, 0xd5, \
						  0xd7, 0xd9, 0xdb, 0xdd पूर्ण)
#घोषणा DMA_CHANNEL_ENABLE	0x0a
#घोषणा DMA_CONFIG		0x0b
#घोषणा DMA_TIMER_INTERVAL	0x0c
#घोषणा DMA_CHANNEL_TIMEOUT	0x0d
#घोषणा VDMA_CHANNEL_CONFIG	REG8_1(0x10)
#घोषणा ADMA_P_ADDR		REG8_2(0x18)
#घोषणा ADMA_B_ADDR		REG8_2(0x19)
#घोषणा DMA10_P_ADDR		0x28
#घोषणा DMA10_B_ADDR		0x29
#घोषणा VIDEO_CONTROL1		0x2a
#घोषणा VIDEO_CONTROL2		0x2b
#घोषणा AUDIO_CONTROL1		0x2c
#घोषणा AUDIO_CONTROL2		0x2d
#घोषणा PHASE_REF		0x2e
#घोषणा GPIO_REG		0x2f
#घोषणा INTL_HBAR_CTRL		REG8_1(0x30)
#घोषणा AUDIO_CONTROL3		0x38
#घोषणा VIDEO_FIELD_CTRL	REG8_1(0x39)
#घोषणा HSCALER_CTRL		REG8_1(0x42)
#घोषणा VIDEO_SIZE		REG8_1(0x4A)
#घोषणा VIDEO_SIZE_F2		REG8_1(0x52)
#घोषणा MD_CONF			REG8_1(0x60)
#घोषणा MD_INIT			REG8_1(0x68)
#घोषणा MD_MAP0			REG8_1(0x70)
#घोषणा VDMA_P_ADDR		REG8_8(0x80) /* not used in DMA SG mode */
#घोषणा VDMA_WHP		REG8_8(0x81)
#घोषणा VDMA_B_ADDR		REG8_8(0x82)
#घोषणा VDMA_F2_P_ADDR		REG8_8(0x84)
#घोषणा VDMA_F2_WHP		REG8_8(0x85)
#घोषणा VDMA_F2_B_ADDR		REG8_8(0x86)
#घोषणा EP_REG_ADDR		0xfe
#घोषणा EP_REG_DATA		0xff

/* Video decoder रेजिस्टरs */
#घोषणा VDREG8(a0) ((स्थिर u16[8]) अणु \
	a0 + 0x000, a0 + 0x010, a0 + 0x020, a0 + 0x030,	\
	a0 + 0x100, a0 + 0x110, a0 + 0x120, a0 + 0x130पूर्ण)
#घोषणा VIDSTAT			VDREG8(0x100)
#घोषणा BRIGHT			VDREG8(0x101)
#घोषणा CONTRAST		VDREG8(0x102)
#घोषणा SHARPNESS		VDREG8(0x103)
#घोषणा SAT_U			VDREG8(0x104)
#घोषणा SAT_V			VDREG8(0x105)
#घोषणा HUE			VDREG8(0x106)
#घोषणा CROP_HI			VDREG8(0x107)
#घोषणा VDELAY_LO		VDREG8(0x108)
#घोषणा VACTIVE_LO		VDREG8(0x109)
#घोषणा HDELAY_LO		VDREG8(0x10a)
#घोषणा HACTIVE_LO		VDREG8(0x10b)
#घोषणा MVSN			VDREG8(0x10c)
#घोषणा STATUS2			VDREG8(0x10d)
#घोषणा SDT			VDREG8(0x10e)
#घोषणा SDT_EN			VDREG8(0x10f)

#घोषणा VSCALE_LO		VDREG8(0x144)
#घोषणा SCALE_HI		VDREG8(0x145)
#घोषणा HSCALE_LO		VDREG8(0x146)
#घोषणा F2CROP_HI		VDREG8(0x147)
#घोषणा F2VDELAY_LO		VDREG8(0x148)
#घोषणा F2VACTIVE_LO		VDREG8(0x149)
#घोषणा F2HDELAY_LO		VDREG8(0x14a)
#घोषणा F2HACTIVE_LO		VDREG8(0x14b)
#घोषणा F2VSCALE_LO		VDREG8(0x14c)
#घोषणा F2SCALE_HI		VDREG8(0x14d)
#घोषणा F2HSCALE_LO		VDREG8(0x14e)
#घोषणा F2CNT			VDREG8(0x14f)

#घोषणा VDREG2(a0) ((स्थिर u16[2]) अणु a0, a0 + 0x100 पूर्ण)
#घोषणा SRST			VDREG2(0x180)
#घोषणा ACNTL			VDREG2(0x181)
#घोषणा ACNTL2			VDREG2(0x182)
#घोषणा CNTRL1			VDREG2(0x183)
#घोषणा CKHY			VDREG2(0x184)
#घोषणा SHCOR			VDREG2(0x185)
#घोषणा CORING			VDREG2(0x186)
#घोषणा CLMPG			VDREG2(0x187)
#घोषणा IAGC			VDREG2(0x188)
#घोषणा VCTRL1			VDREG2(0x18f)
#घोषणा MISC1			VDREG2(0x194)
#घोषणा LOOP			VDREG2(0x195)
#घोषणा MISC2			VDREG2(0x196)

#घोषणा CLMD			VDREG2(0x197)
#घोषणा ANPWRDOWN		VDREG2(0x1ce)
#घोषणा AIGAIN			((स्थिर u16[8]) अणु 0x1d0, 0x1d1, 0x1d2, 0x1d3, \
						  0x2d0, 0x2d1, 0x2d2, 0x2d3 पूर्ण)

#घोषणा SYS_MODE_DMA_SHIFT	13
#घोषणा AUDIO_DMA_SIZE_SHIFT	19
#घोषणा AUDIO_DMA_SIZE_MIN	SZ_512
#घोषणा AUDIO_DMA_SIZE_MAX	SZ_4K
#घोषणा AUDIO_DMA_SIZE_MASK	(SZ_8K - 1)

#घोषणा DMA_CMD_ENABLE		BIT(31)
#घोषणा INT_STATUS_DMA_TOUT	BIT(17)
#घोषणा TW686X_VIDSTAT_HLOCK	BIT(6)
#घोषणा TW686X_VIDSTAT_VDLOSS	BIT(7)

#घोषणा TW686X_STD_NTSC_M	0
#घोषणा TW686X_STD_PAL		1
#घोषणा TW686X_STD_SECAM	2
#घोषणा TW686X_STD_NTSC_443	3
#घोषणा TW686X_STD_PAL_M	4
#घोषणा TW686X_STD_PAL_CN	5
#घोषणा TW686X_STD_PAL_60	6

#घोषणा TW686X_FIELD_MODE	0x3
#घोषणा TW686X_FRAME_MODE	0x2
/* 0x1 is reserved */
#घोषणा TW686X_SG_MODE		0x0

#घोषणा TW686X_FIFO_ERROR(x)	(x & ~(0xff))
