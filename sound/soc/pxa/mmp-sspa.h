<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/sound/soc/pxa/mmp-sspa.h
 *
 * Copyright (C) 2011 Marvell International Ltd.
 */
#अगर_अघोषित _MMP_SSPA_H
#घोषणा _MMP_SSPA_H

/*
 * SSPA Registers
 */
#घोषणा SSPA_D			(0x00)
#घोषणा SSPA_ID			(0x04)
#घोषणा SSPA_CTL		(0x08)
#घोषणा SSPA_SP			(0x0c)
#घोषणा SSPA_FIFO_UL		(0x10)
#घोषणा SSPA_INT_MASK		(0x14)
#घोषणा SSPA_C			(0x18)
#घोषणा SSPA_FIFO_NOFS		(0x1c)
#घोषणा SSPA_FIFO_SIZE		(0x20)

/* SSPA Control Register */
#घोषणा	SSPA_CTL_XPH		(1 << 31)	/* Read Phase */
#घोषणा	SSPA_CTL_XFIG		(1 << 15)	/* Transmit Zeros when FIFO Empty */
#घोषणा	SSPA_CTL_JST		(1 << 3)	/* Audio Sample Justअगरication */
#घोषणा	SSPA_CTL_XFRLEN2_MASK	(7 << 24)
#घोषणा	SSPA_CTL_XFRLEN2(x)	((x) << 24)	/* Transmit Frame Length in Phase 2 */
#घोषणा	SSPA_CTL_XWDLEN2_MASK	(7 << 21)
#घोषणा	SSPA_CTL_XWDLEN2(x)	((x) << 21)	/* Transmit Word Length in Phase 2 */
#घोषणा	SSPA_CTL_XDATDLY(x)	((x) << 19)	/* Transmit Data Delay */
#घोषणा	SSPA_CTL_XSSZ2_MASK	(7 << 16)
#घोषणा	SSPA_CTL_XSSZ2(x)	((x) << 16)	/* Transmit Sample Audio Size */
#घोषणा	SSPA_CTL_XFRLEN1_MASK	(7 << 8)
#घोषणा	SSPA_CTL_XFRLEN1(x)	((x) << 8)	/* Transmit Frame Length in Phase 1 */
#घोषणा	SSPA_CTL_XWDLEN1_MASK	(7 << 5)
#घोषणा	SSPA_CTL_XWDLEN1(x)	((x) << 5)	/* Transmit Word Length in Phase 1 */
#घोषणा	SSPA_CTL_XSSZ1_MASK	(7 << 0)
#घोषणा	SSPA_CTL_XSSZ1(x)	((x) << 0)	/* XSSZ1 */

#घोषणा SSPA_CTL_8_BITS		(0x0)		/* Sample Size */
#घोषणा SSPA_CTL_12_BITS	(0x1)
#घोषणा SSPA_CTL_16_BITS	(0x2)
#घोषणा SSPA_CTL_20_BITS	(0x3)
#घोषणा SSPA_CTL_24_BITS	(0x4)
#घोषणा SSPA_CTL_32_BITS	(0x5)

/* SSPA Serial Port Register */
#घोषणा	SSPA_SP_WEN		(1 << 31)	/* Write Configuration Enable */
#घोषणा	SSPA_SP_MSL		(1 << 18)	/* Master Slave Configuration */
#घोषणा	SSPA_SP_CLKP		(1 << 17)	/* CLKP Polarity Clock Edge Select */
#घोषणा	SSPA_SP_FSP		(1 << 16)	/* FSP Polarity Clock Edge Select */
#घोषणा	SSPA_SP_FFLUSH		(1 << 2)	/* FIFO Flush */
#घोषणा	SSPA_SP_S_RST		(1 << 1)	/* Active High Reset Signal */
#घोषणा	SSPA_SP_S_EN		(1 << 0)	/* Serial Clock Doमुख्य Enable */
#घोषणा	SSPA_SP_FWID_MASK	(0x3f << 20)
#घोषणा	SSPA_SP_FWID(x)		((x) << 20)	/* Frame-Sync Width */
#घोषणा	SSPA_TXSP_FPER_MASK	(0x3f << 4)
#घोषणा	SSPA_TXSP_FPER(x)	((x) << 4)	/* Frame-Sync Active */

/* sspa घड़ी sources */
#घोषणा MMP_SSPA_CLK_PLL	0
#घोषणा MMP_SSPA_CLK_VCXO	1
#घोषणा MMP_SSPA_CLK_AUDIO	3

/* sspa pll id */
#घोषणा MMP_SYSCLK		0
#घोषणा MMP_SSPA_CLK		1

#पूर्ण_अगर /* _MMP_SSPA_H */
