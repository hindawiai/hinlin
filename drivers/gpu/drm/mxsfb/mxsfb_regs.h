<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2010 Juergen Beisert, Pengutronix
 * Copyright (C) 2016 Marek Vasut <marex@denx.de>
 *
 * i.MX23/i.MX28/i.MX6SX MXSFB LCD controller driver.
 */

#अगर_अघोषित __MXSFB_REGS_H__
#घोषणा __MXSFB_REGS_H__

#घोषणा REG_SET	4
#घोषणा REG_CLR	8

#घोषणा LCDC_CTRL			0x00
#घोषणा LCDC_CTRL1			0x10
#घोषणा LCDC_V3_TRANSFER_COUNT		0x20
#घोषणा LCDC_V4_TRANSFER_COUNT		0x30
#घोषणा LCDC_V4_CUR_BUF			0x40
#घोषणा LCDC_V4_NEXT_BUF		0x50
#घोषणा LCDC_V3_CUR_BUF			0x30
#घोषणा LCDC_V3_NEXT_BUF		0x40
#घोषणा LCDC_VDCTRL0			0x70
#घोषणा LCDC_VDCTRL1			0x80
#घोषणा LCDC_VDCTRL2			0x90
#घोषणा LCDC_VDCTRL3			0xa0
#घोषणा LCDC_VDCTRL4			0xb0
#घोषणा LCDC_V4_DEBUG0			0x1d0
#घोषणा LCDC_V3_DEBUG0			0x1f0
#घोषणा LCDC_AS_CTRL			0x210
#घोषणा LCDC_AS_BUF			0x220
#घोषणा LCDC_AS_NEXT_BUF		0x230
#घोषणा LCDC_AS_CLRKEYLOW		0x240
#घोषणा LCDC_AS_CLRKEYHIGH		0x250

#घोषणा CTRL_SFTRST			BIT(31)
#घोषणा CTRL_CLKGATE			BIT(30)
#घोषणा CTRL_BYPASS_COUNT		BIT(19)
#घोषणा CTRL_VSYNC_MODE			BIT(18)
#घोषणा CTRL_DOTCLK_MODE		BIT(17)
#घोषणा CTRL_DATA_SELECT		BIT(16)
#घोषणा CTRL_BUS_WIDTH_16		(0 << 10)
#घोषणा CTRL_BUS_WIDTH_8		(1 << 10)
#घोषणा CTRL_BUS_WIDTH_18		(2 << 10)
#घोषणा CTRL_BUS_WIDTH_24		(3 << 10)
#घोषणा CTRL_BUS_WIDTH_MASK		(0x3 << 10)
#घोषणा CTRL_WORD_LENGTH_16		(0 << 8)
#घोषणा CTRL_WORD_LENGTH_8		(1 << 8)
#घोषणा CTRL_WORD_LENGTH_18		(2 << 8)
#घोषणा CTRL_WORD_LENGTH_24		(3 << 8)
#घोषणा CTRL_MASTER			BIT(5)
#घोषणा CTRL_DF16			BIT(3)
#घोषणा CTRL_DF18			BIT(2)
#घोषणा CTRL_DF24			BIT(1)
#घोषणा CTRL_RUN			BIT(0)

#घोषणा CTRL1_FIFO_CLEAR		BIT(21)
#घोषणा CTRL1_SET_BYTE_PACKAGING(x)	(((x) & 0xf) << 16)
#घोषणा CTRL1_GET_BYTE_PACKAGING(x)	(((x) >> 16) & 0xf)
#घोषणा CTRL1_CUR_FRAME_DONE_IRQ_EN	BIT(13)
#घोषणा CTRL1_CUR_FRAME_DONE_IRQ	BIT(9)

#घोषणा TRANSFER_COUNT_SET_VCOUNT(x)	(((x) & 0xffff) << 16)
#घोषणा TRANSFER_COUNT_GET_VCOUNT(x)	(((x) >> 16) & 0xffff)
#घोषणा TRANSFER_COUNT_SET_HCOUNT(x)	((x) & 0xffff)
#घोषणा TRANSFER_COUNT_GET_HCOUNT(x)	((x) & 0xffff)

#घोषणा VDCTRL0_ENABLE_PRESENT		BIT(28)
#घोषणा VDCTRL0_VSYNC_ACT_HIGH		BIT(27)
#घोषणा VDCTRL0_HSYNC_ACT_HIGH		BIT(26)
#घोषणा VDCTRL0_DOTCLK_ACT_FALLING	BIT(25)
#घोषणा VDCTRL0_ENABLE_ACT_HIGH		BIT(24)
#घोषणा VDCTRL0_VSYNC_PERIOD_UNIT	BIT(21)
#घोषणा VDCTRL0_VSYNC_PULSE_WIDTH_UNIT	BIT(20)
#घोषणा VDCTRL0_HALF_LINE		BIT(19)
#घोषणा VDCTRL0_HALF_LINE_MODE		BIT(18)
#घोषणा VDCTRL0_SET_VSYNC_PULSE_WIDTH(x) ((x) & 0x3ffff)
#घोषणा VDCTRL0_GET_VSYNC_PULSE_WIDTH(x) ((x) & 0x3ffff)

#घोषणा VDCTRL2_SET_HSYNC_PERIOD(x)	((x) & 0x3ffff)
#घोषणा VDCTRL2_GET_HSYNC_PERIOD(x)	((x) & 0x3ffff)

#घोषणा VDCTRL3_MUX_SYNC_SIGNALS	BIT(29)
#घोषणा VDCTRL3_VSYNC_ONLY		BIT(28)
#घोषणा SET_HOR_WAIT_CNT(x)		(((x) & 0xfff) << 16)
#घोषणा GET_HOR_WAIT_CNT(x)		(((x) >> 16) & 0xfff)
#घोषणा SET_VERT_WAIT_CNT(x)		((x) & 0xffff)
#घोषणा GET_VERT_WAIT_CNT(x)		((x) & 0xffff)

#घोषणा VDCTRL4_SET_DOTCLK_DLY(x)	(((x) & 0x7) << 29) /* v4 only */
#घोषणा VDCTRL4_GET_DOTCLK_DLY(x)	(((x) >> 29) & 0x7) /* v4 only */
#घोषणा VDCTRL4_SYNC_SIGNALS_ON		BIT(18)
#घोषणा SET_DOTCLK_H_VALID_DATA_CNT(x)	((x) & 0x3ffff)

#घोषणा DEBUG0_HSYNC			BIT(26)
#घोषणा DEBUG0_VSYNC			BIT(25)

#घोषणा AS_CTRL_PS_DISABLE		BIT(23)
#घोषणा AS_CTRL_ALPHA_INVERT		BIT(20)
#घोषणा AS_CTRL_ALPHA(a)		(((a) & 0xff) << 8)
#घोषणा AS_CTRL_FORMAT_RGB565		(0xe << 4)
#घोषणा AS_CTRL_FORMAT_RGB444		(0xd << 4)
#घोषणा AS_CTRL_FORMAT_RGB555		(0xc << 4)
#घोषणा AS_CTRL_FORMAT_ARGB4444		(0x9 << 4)
#घोषणा AS_CTRL_FORMAT_ARGB1555		(0x8 << 4)
#घोषणा AS_CTRL_FORMAT_RGB888		(0x4 << 4)
#घोषणा AS_CTRL_FORMAT_ARGB8888		(0x0 << 4)
#घोषणा AS_CTRL_ENABLE_COLORKEY		BIT(3)
#घोषणा AS_CTRL_ALPHA_CTRL_ROP		(3 << 1)
#घोषणा AS_CTRL_ALPHA_CTRL_MULTIPLY	(2 << 1)
#घोषणा AS_CTRL_ALPHA_CTRL_OVERRIDE	(1 << 1)
#घोषणा AS_CTRL_ALPHA_CTRL_EMBEDDED	(0 << 1)
#घोषणा AS_CTRL_AS_ENABLE		BIT(0)

#घोषणा MXSFB_MIN_XRES			120
#घोषणा MXSFB_MIN_YRES			120
#घोषणा MXSFB_MAX_XRES			0xffff
#घोषणा MXSFB_MAX_YRES			0xffff

#पूर्ण_अगर /* __MXSFB_REGS_H__ */
