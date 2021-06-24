<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung I2S driver's रेजिस्टर header
 */

#अगर_अघोषित __SND_SOC_SAMSUNG_I2S_REGS_H
#घोषणा __SND_SOC_SAMSUNG_I2S_REGS_H

#घोषणा I2SCON		0x0
#घोषणा I2SMOD		0x4
#घोषणा I2SFIC		0x8
#घोषणा I2SPSR		0xc
#घोषणा I2STXD		0x10
#घोषणा I2SRXD		0x14
#घोषणा I2SFICS		0x18
#घोषणा I2STXDS		0x1c
#घोषणा I2SAHB		0x20
#घोषणा I2SSTR0		0x24
#घोषणा I2SSIZE		0x28
#घोषणा I2STRNCNT	0x2c
#घोषणा I2SLVL0ADDR	0x30
#घोषणा I2SLVL1ADDR	0x34
#घोषणा I2SLVL2ADDR	0x38
#घोषणा I2SLVL3ADDR	0x3c
#घोषणा I2SSTR1		0x40
#घोषणा I2SVER		0x44
#घोषणा I2SFIC1		0x48
#घोषणा I2STDM		0x4c
#घोषणा I2SFSTA		0x50

#घोषणा CON_RSTCLR		(1 << 31)
#घोषणा CON_FRXOFSTATUS		(1 << 26)
#घोषणा CON_FRXORINTEN		(1 << 25)
#घोषणा CON_FTXSURSTAT		(1 << 24)
#घोषणा CON_FTXSURINTEN		(1 << 23)
#घोषणा CON_TXSDMA_PAUSE	(1 << 20)
#घोषणा CON_TXSDMA_ACTIVE	(1 << 18)

#घोषणा CON_FTXURSTATUS		(1 << 17)
#घोषणा CON_FTXURINTEN		(1 << 16)
#घोषणा CON_TXFIFO2_EMPTY	(1 << 15)
#घोषणा CON_TXFIFO1_EMPTY	(1 << 14)
#घोषणा CON_TXFIFO2_FULL	(1 << 13)
#घोषणा CON_TXFIFO1_FULL	(1 << 12)

#घोषणा CON_LRINDEX		(1 << 11)
#घोषणा CON_TXFIFO_EMPTY	(1 << 10)
#घोषणा CON_RXFIFO_EMPTY	(1 << 9)
#घोषणा CON_TXFIFO_FULL		(1 << 8)
#घोषणा CON_RXFIFO_FULL		(1 << 7)
#घोषणा CON_TXDMA_PAUSE		(1 << 6)
#घोषणा CON_RXDMA_PAUSE		(1 << 5)
#घोषणा CON_TXCH_PAUSE		(1 << 4)
#घोषणा CON_RXCH_PAUSE		(1 << 3)
#घोषणा CON_TXDMA_ACTIVE	(1 << 2)
#घोषणा CON_RXDMA_ACTIVE	(1 << 1)
#घोषणा CON_ACTIVE		(1 << 0)

#घोषणा MOD_OPCLK_SHIFT		30
#घोषणा MOD_OPCLK_CDCLK_OUT	(0 << MOD_OPCLK_SHIFT)
#घोषणा MOD_OPCLK_CDCLK_IN	(1 << MOD_OPCLK_SHIFT)
#घोषणा MOD_OPCLK_BCLK_OUT	(2 << MOD_OPCLK_SHIFT)
#घोषणा MOD_OPCLK_PCLK		(3 << MOD_OPCLK_SHIFT)
#घोषणा MOD_OPCLK_MASK		(3 << MOD_OPCLK_SHIFT)
#घोषणा MOD_TXS_IDMA		(1 << 28) /* Sec_TXFIFO use I-DMA */

#घोषणा MOD_BLCS_SHIFT		26
#घोषणा MOD_BLCS_16BIT		(0 << MOD_BLCS_SHIFT)
#घोषणा MOD_BLCS_8BIT		(1 << MOD_BLCS_SHIFT)
#घोषणा MOD_BLCS_24BIT		(2 << MOD_BLCS_SHIFT)
#घोषणा MOD_BLCS_MASK		(3 << MOD_BLCS_SHIFT)
#घोषणा MOD_BLCP_SHIFT		24
#घोषणा MOD_BLCP_16BIT		(0 << MOD_BLCP_SHIFT)
#घोषणा MOD_BLCP_8BIT		(1 << MOD_BLCP_SHIFT)
#घोषणा MOD_BLCP_24BIT		(2 << MOD_BLCP_SHIFT)
#घोषणा MOD_BLCP_MASK		(3 << MOD_BLCP_SHIFT)

#घोषणा MOD_C2DD_HHALF		(1 << 21) /* Discard Higher-half */
#घोषणा MOD_C2DD_LHALF		(1 << 20) /* Discard Lower-half */
#घोषणा MOD_C1DD_HHALF		(1 << 19)
#घोषणा MOD_C1DD_LHALF		(1 << 18)
#घोषणा MOD_DC2_EN		(1 << 17)
#घोषणा MOD_DC1_EN		(1 << 16)
#घोषणा MOD_BLC_16BIT		(0 << 13)
#घोषणा MOD_BLC_8BIT		(1 << 13)
#घोषणा MOD_BLC_24BIT		(2 << 13)
#घोषणा MOD_BLC_MASK		(3 << 13)

#घोषणा MOD_TXONLY		(0 << 8)
#घोषणा MOD_RXONLY		(1 << 8)
#घोषणा MOD_TXRX		(2 << 8)
#घोषणा MOD_MASK		(3 << 8)
#घोषणा MOD_LRP_SHIFT		7
#घोषणा MOD_LR_LLOW		0
#घोषणा MOD_LR_RLOW		1
#घोषणा MOD_SDF_SHIFT		5
#घोषणा MOD_SDF_IIS		0
#घोषणा MOD_SDF_MSB		1
#घोषणा MOD_SDF_LSB		2
#घोषणा MOD_SDF_MASK		3
#घोषणा MOD_RCLK_SHIFT		3
#घोषणा MOD_RCLK_256FS		0
#घोषणा MOD_RCLK_512FS		1
#घोषणा MOD_RCLK_384FS		2
#घोषणा MOD_RCLK_768FS		3
#घोषणा MOD_RCLK_MASK		3
#घोषणा MOD_BCLK_SHIFT		1
#घोषणा MOD_BCLK_32FS		0
#घोषणा MOD_BCLK_48FS		1
#घोषणा MOD_BCLK_16FS		2
#घोषणा MOD_BCLK_24FS		3
#घोषणा MOD_BCLK_MASK		3
#घोषणा MOD_8BIT		(1 << 0)

#घोषणा EXYNOS5420_MOD_LRP_SHIFT	15
#घोषणा EXYNOS5420_MOD_SDF_SHIFT	6
#घोषणा EXYNOS5420_MOD_RCLK_SHIFT	4
#घोषणा EXYNOS5420_MOD_BCLK_SHIFT	0
#घोषणा EXYNOS5420_MOD_BCLK_64FS	4
#घोषणा EXYNOS5420_MOD_BCLK_96FS	5
#घोषणा EXYNOS5420_MOD_BCLK_128FS	6
#घोषणा EXYNOS5420_MOD_BCLK_192FS	7
#घोषणा EXYNOS5420_MOD_BCLK_256FS	8
#घोषणा EXYNOS5420_MOD_BCLK_MASK	0xf

#घोषणा EXYNOS7_MOD_RCLK_64FS	4
#घोषणा EXYNOS7_MOD_RCLK_128FS	5
#घोषणा EXYNOS7_MOD_RCLK_96FS	6
#घोषणा EXYNOS7_MOD_RCLK_192FS	7

#घोषणा PSR_PSREN		(1 << 15)

#घोषणा FIC_TX2COUNT(x)		(((x) >>  24) & 0xf)
#घोषणा FIC_TX1COUNT(x)		(((x) >>  16) & 0xf)

#घोषणा FIC_TXFLUSH		(1 << 15)
#घोषणा FIC_RXFLUSH		(1 << 7)

#घोषणा FIC_TXCOUNT(x)		(((x) >>  8) & 0xf)
#घोषणा FIC_RXCOUNT(x)		(((x) >>  0) & 0xf)
#घोषणा FICS_TXCOUNT(x)		(((x) >>  8) & 0x7f)

#घोषणा AHB_INTENLVL0		(1 << 24)
#घोषणा AHB_LVL0INT		(1 << 20)
#घोषणा AHB_CLRLVL0INT		(1 << 16)
#घोषणा AHB_DMARLD		(1 << 5)
#घोषणा AHB_INTMASK		(1 << 3)
#घोषणा AHB_DMAEN		(1 << 0)
#घोषणा AHB_LVLINTMASK		(0xf << 20)

#घोषणा I2SSIZE_TRNMSK		(0xffff)
#घोषणा I2SSIZE_SHIFT		(16)

#पूर्ण_अगर /* __SND_SOC_SAMSUNG_I2S_REGS_H */
