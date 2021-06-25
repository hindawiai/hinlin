<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * fsl_spdअगर.h - ALSA S/PDIF पूर्णांकerface क्रम the Freescale i.MX SoC
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 *
 * Author: Nicolin Chen <b42378@मुक्तscale.com>
 *
 * Based on fsl_ssi.h
 * Author: Timur Tabi <timur@मुक्तscale.com>
 * Copyright 2007-2008 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित _FSL_SPDIF_DAI_H
#घोषणा _FSL_SPDIF_DAI_H

/* S/PDIF Register Map */
#घोषणा REG_SPDIF_SCR 			0x0	/* SPDIF Configuration Register */
#घोषणा REG_SPDIF_SRCD		 	0x4	/* CDText Control Register */
#घोषणा REG_SPDIF_SRPC			0x8	/* PhaseConfig Register */
#घोषणा REG_SPDIF_SIE			0xc	/* InterruptEn Register */
#घोषणा REG_SPDIF_SIS			0x10	/* InterruptStat Register */
#घोषणा REG_SPDIF_SIC			0x10	/* InterruptClear Register */
#घोषणा REG_SPDIF_SRL			0x14	/* SPDIFRxLeft Register */
#घोषणा REG_SPDIF_SRR			0x18	/* SPDIFRxRight Register */
#घोषणा REG_SPDIF_SRCSH			0x1c	/* SPDIFRxCChannel_h Register */
#घोषणा REG_SPDIF_SRCSL			0x20	/* SPDIFRxCChannel_l Register */
#घोषणा REG_SPDIF_SRU			0x24	/* UchannelRx Register */
#घोषणा REG_SPDIF_SRQ			0x28	/* QchannelRx Register */
#घोषणा REG_SPDIF_STL			0x2C	/* SPDIFTxLeft Register */
#घोषणा REG_SPDIF_STR			0x30	/* SPDIFTxRight Register */
#घोषणा REG_SPDIF_STCSCH		0x34	/* SPDIFTxCChannelCons_h Register */
#घोषणा REG_SPDIF_STCSCL		0x38	/* SPDIFTxCChannelCons_l Register */
#घोषणा REG_SPDIF_SRFM			0x44	/* FreqMeas Register */
#घोषणा REG_SPDIF_STC			0x50	/* SPDIFTxClk Register */


/* SPDIF Configuration रेजिस्टर */
#घोषणा SCR_RXFIFO_CTL_OFFSET		23
#घोषणा SCR_RXFIFO_CTL_MASK		(1 << SCR_RXFIFO_CTL_OFFSET)
#घोषणा SCR_RXFIFO_CTL_ZERO		(1 << SCR_RXFIFO_CTL_OFFSET)
#घोषणा SCR_RXFIFO_OFF_OFFSET		22
#घोषणा SCR_RXFIFO_OFF_MASK		(1 << SCR_RXFIFO_OFF_OFFSET)
#घोषणा SCR_RXFIFO_OFF			(1 << SCR_RXFIFO_OFF_OFFSET)
#घोषणा SCR_RXFIFO_RST_OFFSET		21
#घोषणा SCR_RXFIFO_RST_MASK		(1 << SCR_RXFIFO_RST_OFFSET)
#घोषणा SCR_RXFIFO_RST			(1 << SCR_RXFIFO_RST_OFFSET)
#घोषणा SCR_RXFIFO_FSEL_OFFSET		19
#घोषणा SCR_RXFIFO_FSEL_MASK		(0x3 << SCR_RXFIFO_FSEL_OFFSET)
#घोषणा SCR_RXFIFO_FSEL_IF0		(0x0 << SCR_RXFIFO_FSEL_OFFSET)
#घोषणा SCR_RXFIFO_FSEL_IF4		(0x1 << SCR_RXFIFO_FSEL_OFFSET)
#घोषणा SCR_RXFIFO_FSEL_IF8		(0x2 << SCR_RXFIFO_FSEL_OFFSET)
#घोषणा SCR_RXFIFO_FSEL_IF12		(0x3 << SCR_RXFIFO_FSEL_OFFSET)
#घोषणा SCR_RXFIFO_AUTOSYNC_OFFSET	18
#घोषणा SCR_RXFIFO_AUTOSYNC_MASK	(1 << SCR_RXFIFO_AUTOSYNC_OFFSET)
#घोषणा SCR_RXFIFO_AUTOSYNC		(1 << SCR_RXFIFO_AUTOSYNC_OFFSET)
#घोषणा SCR_TXFIFO_AUTOSYNC_OFFSET	17
#घोषणा SCR_TXFIFO_AUTOSYNC_MASK	(1 << SCR_TXFIFO_AUTOSYNC_OFFSET)
#घोषणा SCR_TXFIFO_AUTOSYNC		(1 << SCR_TXFIFO_AUTOSYNC_OFFSET)
#घोषणा SCR_TXFIFO_FSEL_OFFSET		15
#घोषणा SCR_TXFIFO_FSEL_MASK		(0x3 << SCR_TXFIFO_FSEL_OFFSET)
#घोषणा SCR_TXFIFO_FSEL_IF0		(0x0 << SCR_TXFIFO_FSEL_OFFSET)
#घोषणा SCR_TXFIFO_FSEL_IF4		(0x1 << SCR_TXFIFO_FSEL_OFFSET)
#घोषणा SCR_TXFIFO_FSEL_IF8		(0x2 << SCR_TXFIFO_FSEL_OFFSET)
#घोषणा SCR_TXFIFO_FSEL_IF12		(0x3 << SCR_TXFIFO_FSEL_OFFSET)
#घोषणा SCR_LOW_POWER			(1 << 13)
#घोषणा SCR_SOFT_RESET			(1 << 12)
#घोषणा SCR_TXFIFO_CTRL_OFFSET		10
#घोषणा SCR_TXFIFO_CTRL_MASK		(0x3 << SCR_TXFIFO_CTRL_OFFSET)
#घोषणा SCR_TXFIFO_CTRL_ZERO		(0x0 << SCR_TXFIFO_CTRL_OFFSET)
#घोषणा SCR_TXFIFO_CTRL_NORMAL		(0x1 << SCR_TXFIFO_CTRL_OFFSET)
#घोषणा SCR_TXFIFO_CTRL_ONESAMPLE	(0x2 << SCR_TXFIFO_CTRL_OFFSET)
#घोषणा SCR_DMA_RX_EN_OFFSET		9
#घोषणा SCR_DMA_RX_EN_MASK		(1 << SCR_DMA_RX_EN_OFFSET)
#घोषणा SCR_DMA_RX_EN			(1 << SCR_DMA_RX_EN_OFFSET)
#घोषणा SCR_DMA_TX_EN_OFFSET		8
#घोषणा SCR_DMA_TX_EN_MASK		(1 << SCR_DMA_TX_EN_OFFSET)
#घोषणा SCR_DMA_TX_EN			(1 << SCR_DMA_TX_EN_OFFSET)
#घोषणा SCR_VAL_OFFSET			5
#घोषणा SCR_VAL_MASK			(1 << SCR_VAL_OFFSET)
#घोषणा SCR_VAL_CLEAR			(1 << SCR_VAL_OFFSET)
#घोषणा SCR_TXSEL_OFFSET		2
#घोषणा SCR_TXSEL_MASK			(0x7 << SCR_TXSEL_OFFSET)
#घोषणा SCR_TXSEL_OFF			(0 << SCR_TXSEL_OFFSET)
#घोषणा SCR_TXSEL_RX			(1 << SCR_TXSEL_OFFSET)
#घोषणा SCR_TXSEL_NORMAL		(0x5 << SCR_TXSEL_OFFSET)
#घोषणा SCR_USRC_SEL_OFFSET		0x0
#घोषणा SCR_USRC_SEL_MASK		(0x3 << SCR_USRC_SEL_OFFSET)
#घोषणा SCR_USRC_SEL_NONE		(0x0 << SCR_USRC_SEL_OFFSET)
#घोषणा SCR_USRC_SEL_RECV		(0x1 << SCR_USRC_SEL_OFFSET)
#घोषणा SCR_USRC_SEL_CHIP		(0x3 << SCR_USRC_SEL_OFFSET)

#घोषणा SCR_DMA_xX_EN(tx)		(tx ? SCR_DMA_TX_EN : SCR_DMA_RX_EN)

/* SPDIF CDText control */
#घोषणा SRCD_CD_USER_OFFSET		1
#घोषणा SRCD_CD_USER			(1 << SRCD_CD_USER_OFFSET)

/* SPDIF Phase Configuration रेजिस्टर */
#घोषणा SRPC_DPLL_LOCKED		(1 << 6)
#घोषणा SRPC_CLKSRC_SEL_OFFSET		7
#घोषणा SRPC_CLKSRC_SEL_MASK		(0xf << SRPC_CLKSRC_SEL_OFFSET)
#घोषणा SRPC_CLKSRC_SEL_SET(x)		((x << SRPC_CLKSRC_SEL_OFFSET) & SRPC_CLKSRC_SEL_MASK)
#घोषणा SRPC_CLKSRC_SEL_LOCKED_OFFSET1	5
#घोषणा SRPC_CLKSRC_SEL_LOCKED_OFFSET2	2
#घोषणा SRPC_GAINSEL_OFFSET		3
#घोषणा SRPC_GAINSEL_MASK		(0x7 << SRPC_GAINSEL_OFFSET)
#घोषणा SRPC_GAINSEL_SET(x)		((x << SRPC_GAINSEL_OFFSET) & SRPC_GAINSEL_MASK)

#घोषणा SRPC_CLKSRC_MAX			16

क्रमागत spdअगर_gainsel अणु
	GAINSEL_MULTI_24 = 0,
	GAINSEL_MULTI_16,
	GAINSEL_MULTI_12,
	GAINSEL_MULTI_8,
	GAINSEL_MULTI_6,
	GAINSEL_MULTI_4,
	GAINSEL_MULTI_3,
पूर्ण;
#घोषणा GAINSEL_MULTI_MAX		(GAINSEL_MULTI_3 + 1)
#घोषणा SPDIF_DEFAULT_GAINSEL		GAINSEL_MULTI_8

/* SPDIF पूर्णांकerrupt mask define */
#घोषणा INT_DPLL_LOCKED			(1 << 20)
#घोषणा INT_TXFIFO_UNOV			(1 << 19)
#घोषणा INT_TXFIFO_RESYNC		(1 << 18)
#घोषणा INT_CNEW			(1 << 17)
#घोषणा INT_VAL_NOGOOD			(1 << 16)
#घोषणा INT_SYM_ERR			(1 << 15)
#घोषणा INT_BIT_ERR			(1 << 14)
#घोषणा INT_URX_FUL			(1 << 10)
#घोषणा INT_URX_OV			(1 << 9)
#घोषणा INT_QRX_FUL			(1 << 8)
#घोषणा INT_QRX_OV			(1 << 7)
#घोषणा INT_UQ_SYNC			(1 << 6)
#घोषणा INT_UQ_ERR			(1 << 5)
#घोषणा INT_RXFIFO_UNOV			(1 << 4)
#घोषणा INT_RXFIFO_RESYNC		(1 << 3)
#घोषणा INT_LOSS_LOCK			(1 << 2)
#घोषणा INT_TX_EM			(1 << 1)
#घोषणा INT_RXFIFO_FUL			(1 << 0)

/* SPDIF Clock रेजिस्टर */
#घोषणा STC_SYSCLK_DF_OFFSET		11
#घोषणा STC_SYSCLK_DF_MASK		(0x1ff << STC_SYSCLK_DF_OFFSET)
#घोषणा STC_SYSCLK_DF(x)		((((x) - 1) << STC_SYSCLK_DF_OFFSET) & STC_SYSCLK_DF_MASK)
#घोषणा STC_TXCLK_SRC_OFFSET		8
#घोषणा STC_TXCLK_SRC_MASK		(0x7 << STC_TXCLK_SRC_OFFSET)
#घोषणा STC_TXCLK_SRC_SET(x)		((x << STC_TXCLK_SRC_OFFSET) & STC_TXCLK_SRC_MASK)
#घोषणा STC_TXCLK_ALL_EN_OFFSET		7
#घोषणा STC_TXCLK_ALL_EN_MASK		(1 << STC_TXCLK_ALL_EN_OFFSET)
#घोषणा STC_TXCLK_ALL_EN		(1 << STC_TXCLK_ALL_EN_OFFSET)
#घोषणा STC_TXCLK_DF_OFFSET		0
#घोषणा STC_TXCLK_DF_MASK		(0x7f << STC_TXCLK_DF_OFFSET)
#घोषणा STC_TXCLK_DF(x)		((((x) - 1) << STC_TXCLK_DF_OFFSET) & STC_TXCLK_DF_MASK)
#घोषणा STC_TXCLK_SRC_MAX		8

#घोषणा STC_TXCLK_SPDIF_ROOT		1

/* SPDIF tx rate */
क्रमागत spdअगर_txrate अणु
	SPDIF_TXRATE_32000 = 0,
	SPDIF_TXRATE_44100,
	SPDIF_TXRATE_48000,
	SPDIF_TXRATE_88200,
	SPDIF_TXRATE_96000,
	SPDIF_TXRATE_176400,
	SPDIF_TXRATE_192000,
पूर्ण;
#घोषणा SPDIF_TXRATE_MAX		(SPDIF_TXRATE_192000 + 1)


#घोषणा SPDIF_CSTATUS_BYTE		6
#घोषणा SPDIF_UBITS_SIZE		96
#घोषणा SPDIF_QSUB_SIZE			(SPDIF_UBITS_SIZE / 8)


#घोषणा FSL_SPDIF_RATES_PLAYBACK	(SNDRV_PCM_RATE_32000 |	\
					 SNDRV_PCM_RATE_44100 |	\
					 SNDRV_PCM_RATE_48000 |	\
					 SNDRV_PCM_RATE_88200 | \
					 SNDRV_PCM_RATE_96000 |	\
					 SNDRV_PCM_RATE_176400 | \
					 SNDRV_PCM_RATE_192000)

#घोषणा FSL_SPDIF_RATES_CAPTURE		(SNDRV_PCM_RATE_16000 | \
					 SNDRV_PCM_RATE_32000 |	\
					 SNDRV_PCM_RATE_44100 | \
					 SNDRV_PCM_RATE_48000 |	\
					 SNDRV_PCM_RATE_88200 | \
					 SNDRV_PCM_RATE_64000 | \
					 SNDRV_PCM_RATE_96000 | \
					 SNDRV_PCM_RATE_176400 | \
					 SNDRV_PCM_RATE_192000)

#घोषणा FSL_SPDIF_FORMATS_PLAYBACK	(SNDRV_PCM_FMTBIT_S16_LE | \
					 SNDRV_PCM_FMTBIT_S20_3LE | \
					 SNDRV_PCM_FMTBIT_S24_LE)

#घोषणा FSL_SPDIF_FORMATS_CAPTURE	(SNDRV_PCM_FMTBIT_S24_LE)

#पूर्ण_अगर /* _FSL_SPDIF_DAI_H */
