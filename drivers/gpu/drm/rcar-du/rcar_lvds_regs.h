<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rcar_lvds_regs.h  --  R-Car LVDS Interface Registers Definitions
 *
 * Copyright (C) 2013-2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __RCAR_LVDS_REGS_H__
#घोषणा __RCAR_LVDS_REGS_H__

#घोषणा LVDCR0				0x0000
#घोषणा LVDCR0_DUSEL			(1 << 15)
#घोषणा LVDCR0_DMD			(1 << 12)		/* Gen2 only */
#घोषणा LVDCR0_LVMD_MASK		(0xf << 8)
#घोषणा LVDCR0_LVMD_SHIFT		8
#घोषणा LVDCR0_PLLON			(1 << 4)
#घोषणा LVDCR0_PWD			(1 << 2)		/* Gen3 only */
#घोषणा LVDCR0_BEN			(1 << 2)		/* Gen2 only */
#घोषणा LVDCR0_LVEN			(1 << 1)
#घोषणा LVDCR0_LVRES			(1 << 0)

#घोषणा LVDCR1				0x0004
#घोषणा LVDCR1_CKSEL			(1 << 15)		/* Gen2 only */
#घोषणा LVDCR1_CHSTBY(n)		(3 << (2 + (n) * 2))
#घोषणा LVDCR1_CLKSTBY			(3 << 0)

#घोषणा LVDPLLCR			0x0008
/* Gen2 & V3M */
#घोषणा LVDPLLCR_CEEN			(1 << 14)
#घोषणा LVDPLLCR_FBEN			(1 << 13)
#घोषणा LVDPLLCR_COSEL			(1 << 12)
#घोषणा LVDPLLCR_PLLDLYCNT_150M		(0x1bf << 0)
#घोषणा LVDPLLCR_PLLDLYCNT_121M		(0x22c << 0)
#घोषणा LVDPLLCR_PLLDLYCNT_60M		(0x77b << 0)
#घोषणा LVDPLLCR_PLLDLYCNT_38M		(0x69a << 0)
#घोषणा LVDPLLCR_PLLDLYCNT_MASK		(0x7ff << 0)
/* Gen3 but V3M,D3 and E3 */
#घोषणा LVDPLLCR_PLLDIVCNT_42M		(0x014cb << 0)
#घोषणा LVDPLLCR_PLLDIVCNT_85M		(0x00a45 << 0)
#घोषणा LVDPLLCR_PLLDIVCNT_128M		(0x006c3 << 0)
#घोषणा LVDPLLCR_PLLDIVCNT_148M		(0x046c1 << 0)
#घोषणा LVDPLLCR_PLLDIVCNT_MASK		(0x7ffff << 0)
/* D3 and E3 */
#घोषणा LVDPLLCR_PLLON			(1 << 22)
#घोषणा LVDPLLCR_PLLSEL_PLL0		(0 << 20)
#घोषणा LVDPLLCR_PLLSEL_LVX		(1 << 20)
#घोषणा LVDPLLCR_PLLSEL_PLL1		(2 << 20)
#घोषणा LVDPLLCR_CKSEL_LVX		(1 << 17)
#घोषणा LVDPLLCR_CKSEL_EXTAL		(3 << 17)
#घोषणा LVDPLLCR_CKSEL_DU_DOTCLKIN(n)	((5 + (n) * 2) << 17)
#घोषणा LVDPLLCR_OCKSEL			(1 << 16)
#घोषणा LVDPLLCR_STP_CLKOUTE		(1 << 14)
#घोषणा LVDPLLCR_OUTCLKSEL		(1 << 12)
#घोषणा LVDPLLCR_CLKOUT			(1 << 11)
#घोषणा LVDPLLCR_PLLE(n)		((n) << 10)
#घोषणा LVDPLLCR_PLLN(n)		((n) << 3)
#घोषणा LVDPLLCR_PLLM(n)		((n) << 0)

#घोषणा LVDCTRCR			0x000c
#घोषणा LVDCTRCR_CTR3SEL_ZERO		(0 << 12)
#घोषणा LVDCTRCR_CTR3SEL_ODD		(1 << 12)
#घोषणा LVDCTRCR_CTR3SEL_CDE		(2 << 12)
#घोषणा LVDCTRCR_CTR3SEL_MASK		(7 << 12)
#घोषणा LVDCTRCR_CTR2SEL_DISP		(0 << 8)
#घोषणा LVDCTRCR_CTR2SEL_ODD		(1 << 8)
#घोषणा LVDCTRCR_CTR2SEL_CDE		(2 << 8)
#घोषणा LVDCTRCR_CTR2SEL_HSYNC		(3 << 8)
#घोषणा LVDCTRCR_CTR2SEL_VSYNC		(4 << 8)
#घोषणा LVDCTRCR_CTR2SEL_MASK		(7 << 8)
#घोषणा LVDCTRCR_CTR1SEL_VSYNC		(0 << 4)
#घोषणा LVDCTRCR_CTR1SEL_DISP		(1 << 4)
#घोषणा LVDCTRCR_CTR1SEL_ODD		(2 << 4)
#घोषणा LVDCTRCR_CTR1SEL_CDE		(3 << 4)
#घोषणा LVDCTRCR_CTR1SEL_HSYNC		(4 << 4)
#घोषणा LVDCTRCR_CTR1SEL_MASK		(7 << 4)
#घोषणा LVDCTRCR_CTR0SEL_HSYNC		(0 << 0)
#घोषणा LVDCTRCR_CTR0SEL_VSYNC		(1 << 0)
#घोषणा LVDCTRCR_CTR0SEL_DISP		(2 << 0)
#घोषणा LVDCTRCR_CTR0SEL_ODD		(3 << 0)
#घोषणा LVDCTRCR_CTR0SEL_CDE		(4 << 0)
#घोषणा LVDCTRCR_CTR0SEL_MASK		(7 << 0)

#घोषणा LVDCHCR				0x0010
#घोषणा LVDCHCR_CHSEL_CH(n, c)		((((c) - (n)) & 3) << ((n) * 4))
#घोषणा LVDCHCR_CHSEL_MASK(n)		(3 << ((n) * 4))

/* All रेजिस्टरs below are specअगरic to D3 and E3 */
#घोषणा LVDSTRIPE			0x0014
#घोषणा LVDSTRIPE_ST_TRGSEL_DISP	(0 << 2)
#घोषणा LVDSTRIPE_ST_TRGSEL_HSYNC_R	(1 << 2)
#घोषणा LVDSTRIPE_ST_TRGSEL_HSYNC_F	(2 << 2)
#घोषणा LVDSTRIPE_ST_SWAP		(1 << 1)
#घोषणा LVDSTRIPE_ST_ON			(1 << 0)

#घोषणा LVDSCR				0x0018
#घोषणा LVDSCR_DEPTH(n)			(((n) - 1) << 29)
#घोषणा LVDSCR_BANDSET			(1 << 28)
#घोषणा LVDSCR_TWGCNT(n)		((((n) - 256) / 16) << 24)
#घोषणा LVDSCR_SDIV(n)			((n) << 22)
#घोषणा LVDSCR_MODE			(1 << 21)
#घोषणा LVDSCR_RSTN			(1 << 20)

#घोषणा LVDDIV				0x001c
#घोषणा LVDDIV_DIVSEL			(1 << 8)
#घोषणा LVDDIV_DIVRESET			(1 << 7)
#घोषणा LVDDIV_DIVSTP			(1 << 6)
#घोषणा LVDDIV_DIV(n)			((n) << 0)

#पूर्ण_अगर /* __RCAR_LVDS_REGS_H__ */
