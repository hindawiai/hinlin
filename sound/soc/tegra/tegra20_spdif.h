<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra20_spdअगर.h - Definitions क्रम Tegra20 SPDIF driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2011 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 * Copyright (c) 2008-2009, NVIDIA Corporation
 */

#अगर_अघोषित __TEGRA20_SPDIF_H__
#घोषणा __TEGRA20_SPDIF_H__

#समावेश "tegra_pcm.h"

/* Offsets from TEGRA20_SPDIF_BASE */

#घोषणा TEGRA20_SPDIF_CTRL					0x0
#घोषणा TEGRA20_SPDIF_STATUS					0x4
#घोषणा TEGRA20_SPDIF_STROBE_CTRL				0x8
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR				0x0C
#घोषणा TEGRA20_SPDIF_DATA_OUT					0x40
#घोषणा TEGRA20_SPDIF_DATA_IN					0x80
#घोषणा TEGRA20_SPDIF_CH_STA_RX_A				0x100
#घोषणा TEGRA20_SPDIF_CH_STA_RX_B				0x104
#घोषणा TEGRA20_SPDIF_CH_STA_RX_C				0x108
#घोषणा TEGRA20_SPDIF_CH_STA_RX_D				0x10C
#घोषणा TEGRA20_SPDIF_CH_STA_RX_E				0x110
#घोषणा TEGRA20_SPDIF_CH_STA_RX_F				0x114
#घोषणा TEGRA20_SPDIF_CH_STA_TX_A				0x140
#घोषणा TEGRA20_SPDIF_CH_STA_TX_B				0x144
#घोषणा TEGRA20_SPDIF_CH_STA_TX_C				0x148
#घोषणा TEGRA20_SPDIF_CH_STA_TX_D				0x14C
#घोषणा TEGRA20_SPDIF_CH_STA_TX_E				0x150
#घोषणा TEGRA20_SPDIF_CH_STA_TX_F				0x154
#घोषणा TEGRA20_SPDIF_USR_STA_RX_A				0x180
#घोषणा TEGRA20_SPDIF_USR_DAT_TX_A				0x1C0

/* Fields in TEGRA20_SPDIF_CTRL */

/* Start capturing from 0=right, 1=left channel */
#घोषणा TEGRA20_SPDIF_CTRL_CAP_LC				(1 << 30)

/* SPDIF receiver(RX) enable */
#घोषणा TEGRA20_SPDIF_CTRL_RX_EN				(1 << 29)

/* SPDIF Transmitter(TX) enable */
#घोषणा TEGRA20_SPDIF_CTRL_TX_EN				(1 << 28)

/* Transmit Channel status */
#घोषणा TEGRA20_SPDIF_CTRL_TC_EN				(1 << 27)

/* Transmit user Data */
#घोषणा TEGRA20_SPDIF_CTRL_TU_EN				(1 << 26)

/* Interrupt on transmit error */
#घोषणा TEGRA20_SPDIF_CTRL_IE_TXE				(1 << 25)

/* Interrupt on receive error */
#घोषणा TEGRA20_SPDIF_CTRL_IE_RXE				(1 << 24)

/* Interrupt on invalid preamble */
#घोषणा TEGRA20_SPDIF_CTRL_IE_P					(1 << 23)

/* Interrupt on "B" preamble */
#घोषणा TEGRA20_SPDIF_CTRL_IE_B					(1 << 22)

/* Interrupt when block of channel status received */
#घोषणा TEGRA20_SPDIF_CTRL_IE_C					(1 << 21)

/* Interrupt when a valid inक्रमmation unit (IU) is received */
#घोषणा TEGRA20_SPDIF_CTRL_IE_U					(1 << 20)

/* Interrupt when RX user FIFO attention level is reached */
#घोषणा TEGRA20_SPDIF_CTRL_QE_RU				(1 << 19)

/* Interrupt when TX user FIFO attention level is reached */
#घोषणा TEGRA20_SPDIF_CTRL_QE_TU				(1 << 18)

/* Interrupt when RX data FIFO attention level is reached */
#घोषणा TEGRA20_SPDIF_CTRL_QE_RX				(1 << 17)

/* Interrupt when TX data FIFO attention level is reached */
#घोषणा TEGRA20_SPDIF_CTRL_QE_TX				(1 << 16)

/* Loopback test mode enable */
#घोषणा TEGRA20_SPDIF_CTRL_LBK_EN				(1 << 15)

/*
 * Pack data mode:
 * 0 = Single data (16 bit needs to be  padded to match the
 *     पूर्णांकerface data bit size).
 * 1 = Packeted left/right channel data पूर्णांकo a single word.
 */
#घोषणा TEGRA20_SPDIF_CTRL_PACK					(1 << 14)

/*
 * 00 = 16bit data
 * 01 = 20bit data
 * 10 = 24bit data
 * 11 = raw data
 */
#घोषणा TEGRA20_SPDIF_BIT_MODE_16BIT				0
#घोषणा TEGRA20_SPDIF_BIT_MODE_20BIT				1
#घोषणा TEGRA20_SPDIF_BIT_MODE_24BIT				2
#घोषणा TEGRA20_SPDIF_BIT_MODE_RAW				3

#घोषणा TEGRA20_SPDIF_CTRL_BIT_MODE_SHIFT			12
#घोषणा TEGRA20_SPDIF_CTRL_BIT_MODE_MASK			(3                            << TEGRA20_SPDIF_CTRL_BIT_MODE_SHIFT)
#घोषणा TEGRA20_SPDIF_CTRL_BIT_MODE_16BIT			(TEGRA20_SPDIF_BIT_MODE_16BIT << TEGRA20_SPDIF_CTRL_BIT_MODE_SHIFT)
#घोषणा TEGRA20_SPDIF_CTRL_BIT_MODE_20BIT			(TEGRA20_SPDIF_BIT_MODE_20BIT << TEGRA20_SPDIF_CTRL_BIT_MODE_SHIFT)
#घोषणा TEGRA20_SPDIF_CTRL_BIT_MODE_24BIT			(TEGRA20_SPDIF_BIT_MODE_24BIT << TEGRA20_SPDIF_CTRL_BIT_MODE_SHIFT)
#घोषणा TEGRA20_SPDIF_CTRL_BIT_MODE_RAW				(TEGRA20_SPDIF_BIT_MODE_RAW   << TEGRA20_SPDIF_CTRL_BIT_MODE_SHIFT)

/* Fields in TEGRA20_SPDIF_STATUS */

/*
 * Note: IS_P, IS_B, IS_C, and IS_U are sticky bits. Software must
 * ग_लिखो a 1 to the corresponding bit location to clear the status.
 */

/*
 * Receiver(RX) shअगरter is busy receiving data.
 * This bit is निश्चितed when the receiver first locked onto the
 * preamble of the data stream after RX_EN is निश्चितed. This bit is
 * deनिश्चितed when either,
 * (a) the end of a frame is reached after RX_EN is deeनिश्चितed, or
 * (b) the SPDIF data stream becomes inactive.
 */
#घोषणा TEGRA20_SPDIF_STATUS_RX_BSY				(1 << 29)

/*
 * Transmitter(TX) shअगरter is busy transmitting data.
 * This bit is निश्चितed when TX_EN is निश्चितed.
 * This bit is deनिश्चितed when the end of a frame is reached after
 * TX_EN is deनिश्चितed.
 */
#घोषणा TEGRA20_SPDIF_STATUS_TX_BSY				(1 << 28)

/*
 * TX is busy shअगरting out channel status.
 * This bit is निश्चितed when both TX_EN and TC_EN are निश्चितed and
 * data from CH_STA_TX_A रेजिस्टर is loaded पूर्णांकo the पूर्णांकernal shअगरter.
 * This bit is deनिश्चितed when either,
 * (a) the end of a frame is reached after TX_EN is deनिश्चितed, or
 * (b) CH_STA_TX_F रेजिस्टर is loaded पूर्णांकo the पूर्णांकernal shअगरter.
 */
#घोषणा TEGRA20_SPDIF_STATUS_TC_BSY				(1 << 27)

/*
 * TX User data FIFO busy.
 * This bit is निश्चितed when TX_EN and TXU_EN are निश्चितed and
 * there's data in the TX user FIFO.  This bit is deनिश्चित when either,
 * (a) the end of a frame is reached after TX_EN is deनिश्चितed, or
 * (b) there's no data left in the TX user FIFO.
 */
#घोषणा TEGRA20_SPDIF_STATUS_TU_BSY				(1 << 26)

/* TX FIFO Underrun error status */
#घोषणा TEGRA20_SPDIF_STATUS_TX_ERR				(1 << 25)

/* RX FIFO Overrun error status */
#घोषणा TEGRA20_SPDIF_STATUS_RX_ERR				(1 << 24)

/* Preamble status: 0=Preamble OK, 1=bad/missing preamble */
#घोषणा TEGRA20_SPDIF_STATUS_IS_P				(1 << 23)

/* B-preamble detection status: 0=not detected, 1=B-preamble detected */
#घोषणा TEGRA20_SPDIF_STATUS_IS_B				(1 << 22)

/*
 * RX channel block data receive status:
 * 0=entire block not recieved yet.
 * 1=received entire block of channel status,
 */
#घोषणा TEGRA20_SPDIF_STATUS_IS_C				(1 << 21)

/* RX User Data Valid flag:  1=valid IU detected, 0 = no IU detected. */
#घोषणा TEGRA20_SPDIF_STATUS_IS_U				(1 << 20)

/*
 * RX User FIFO Status:
 * 1=attention level reached, 0=attention level not reached.
 */
#घोषणा TEGRA20_SPDIF_STATUS_QS_RU				(1 << 19)

/*
 * TX User FIFO Status:
 * 1=attention level reached, 0=attention level not reached.
 */
#घोषणा TEGRA20_SPDIF_STATUS_QS_TU				(1 << 18)

/*
 * RX Data FIFO Status:
 * 1=attention level reached, 0=attention level not reached.
 */
#घोषणा TEGRA20_SPDIF_STATUS_QS_RX				(1 << 17)

/*
 * TX Data FIFO Status:
 * 1=attention level reached, 0=attention level not reached.
 */
#घोषणा TEGRA20_SPDIF_STATUS_QS_TX				(1 << 16)

/* Fields in TEGRA20_SPDIF_STROBE_CTRL */

/*
 * Indicates the approximate number of detected SPDIFIN घड़ीs within a
 * bi-phase period.
 */
#घोषणा TEGRA20_SPDIF_STROBE_CTRL_PERIOD_SHIFT			16
#घोषणा TEGRA20_SPDIF_STROBE_CTRL_PERIOD_MASK			(0xff << TEGRA20_SPDIF_STROBE_CTRL_PERIOD_SHIFT)

/* Data strobe mode: 0=Auto-locked 1=Manual locked */
#घोषणा TEGRA20_SPDIF_STROBE_CTRL_STROBE			(1 << 15)

/*
 * Manual data strobe समय within the bi-phase घड़ी period (in terms of
 * the number of over-sampling घड़ीs).
 */
#घोषणा TEGRA20_SPDIF_STROBE_CTRL_DATA_STROBES_SHIFT		8
#घोषणा TEGRA20_SPDIF_STROBE_CTRL_DATA_STROBES_MASK		(0x1f << TEGRA20_SPDIF_STROBE_CTRL_DATA_STROBES_SHIFT)

/*
 * Manual SPDIFIN bi-phase घड़ी period (in terms of the number of
 * over-sampling घड़ीs).
 */
#घोषणा TEGRA20_SPDIF_STROBE_CTRL_CLOCK_PERIOD_SHIFT		0
#घोषणा TEGRA20_SPDIF_STROBE_CTRL_CLOCK_PERIOD_MASK		(0x3f << TEGRA20_SPDIF_STROBE_CTRL_CLOCK_PERIOD_SHIFT)

/* Fields in SPDIF_DATA_FIFO_CSR */

/* Clear Receiver User FIFO (RX USR.FIFO) */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_CLR			(1 << 31)

#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_U_ONE_SLOT			0
#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_U_TWO_SLOTS			1
#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_U_THREE_SLOTS		2
#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_U_FOUR_SLOTS			3

/* RU FIFO attention level */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_SHIFT		29
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_MASK		\
		(0x3                                      << TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_RU1_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_ONE_SLOT    << TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_RU2_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_TWO_SLOTS   << TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_RU3_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_THREE_SLOTS << TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_RU4_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_FOUR_SLOTS  << TEGRA20_SPDIF_DATA_FIFO_CSR_RU_ATN_LVL_SHIFT)

/* Number of RX USR.FIFO levels with valid data. */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_FULL_COUNT_SHIFT		24
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RU_FULL_COUNT_MASK		(0x1f << TEGRA20_SPDIF_DATA_FIFO_CSR_RU_FULL_COUNT_SHIFT)

/* Clear Transmitter User FIFO (TX USR.FIFO) */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_CLR			(1 << 23)

/* TU FIFO attention level */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_SHIFT		21
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_MASK		\
		(0x3                                      << TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_TU1_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_ONE_SLOT    << TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_TU2_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_TWO_SLOTS   << TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_TU3_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_THREE_SLOTS << TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_TU4_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_U_FOUR_SLOTS  << TEGRA20_SPDIF_DATA_FIFO_CSR_TU_ATN_LVL_SHIFT)

/* Number of TX USR.FIFO levels that could be filled. */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_EMPTY_COUNT_SHIFT	16
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TU_EMPTY_COUNT_MASK		(0x1f << SPDIF_DATA_FIFO_CSR_TU_EMPTY_COUNT_SHIFT)

/* Clear Receiver Data FIFO (RX DATA.FIFO) */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_CLR			(1 << 15)

#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_D_ONE_SLOT			0
#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_D_FOUR_SLOTS			1
#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_D_EIGHT_SLOTS		2
#घोषणा TEGRA20_SPDIF_FIFO_ATN_LVL_D_TWELVE_SLOTS		3

/* RU FIFO attention level */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_SHIFT		13
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_MASK		\
		(0x3                                       << TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_RU1_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_ONE_SLOT     << TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_RU4_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_FOUR_SLOTS   << TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_RU8_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_EIGHT_SLOTS  << TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_RU12_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_TWELVE_SLOTS << TEGRA20_SPDIF_DATA_FIFO_CSR_RX_ATN_LVL_SHIFT)

/* Number of RX DATA.FIFO levels with valid data. */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_FULL_COUNT_SHIFT		8
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_RX_FULL_COUNT_MASK		(0x1f << TEGRA20_SPDIF_DATA_FIFO_CSR_RX_FULL_COUNT_SHIFT)

/* Clear Transmitter Data FIFO (TX DATA.FIFO) */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_CLR			(1 << 7)

/* TU FIFO attention level */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_SHIFT		5
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_MASK		\
		(0x3                                       << TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_TU1_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_ONE_SLOT     << TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_TU4_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_FOUR_SLOTS   << TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_TU8_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_EIGHT_SLOTS  << TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_SHIFT)
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_TU12_WORD_FULL	\
		(TEGRA20_SPDIF_FIFO_ATN_LVL_D_TWELVE_SLOTS << TEGRA20_SPDIF_DATA_FIFO_CSR_TX_ATN_LVL_SHIFT)

/* Number of TX DATA.FIFO levels that could be filled. */
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_EMPTY_COUNT_SHIFT	0
#घोषणा TEGRA20_SPDIF_DATA_FIFO_CSR_TX_EMPTY_COUNT_MASK		(0x1f << SPDIF_DATA_FIFO_CSR_TX_EMPTY_COUNT_SHIFT)

/* Fields in TEGRA20_SPDIF_DATA_OUT */

/*
 * This रेजिस्टर has 5 dअगरferent क्रमmats:
 * 16-bit        (BIT_MODE=00, PACK=0)
 * 20-bit        (BIT_MODE=01, PACK=0)
 * 24-bit        (BIT_MODE=10, PACK=0)
 * raw           (BIT_MODE=11, PACK=0)
 * 16-bit packed (BIT_MODE=00, PACK=1)
 */

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_16_SHIFT			0
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_16_MASK			(0xffff << TEGRA20_SPDIF_DATA_OUT_DATA_16_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_20_SHIFT			0
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_20_MASK			(0xfffff << TEGRA20_SPDIF_DATA_OUT_DATA_20_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_24_SHIFT			0
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_24_MASK			(0xffffff << TEGRA20_SPDIF_DATA_OUT_DATA_24_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_P			(1 << 31)
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_C			(1 << 30)
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_U			(1 << 29)
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_V			(1 << 28)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_DATA_SHIFT		8
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_DATA_MASK		(0xfffff << TEGRA20_SPDIF_DATA_OUT_DATA_RAW_DATA_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_AUX_SHIFT		4
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_AUX_MASK		(0xf << TEGRA20_SPDIF_DATA_OUT_DATA_RAW_AUX_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_PREAMBLE_SHIFT		0
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_RAW_PREAMBLE_MASK		(0xf << TEGRA20_SPDIF_DATA_OUT_DATA_RAW_PREAMBLE_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_16_PACKED_RIGHT_SHIFT	16
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_16_PACKED_RIGHT_MASK	(0xffff << TEGRA20_SPDIF_DATA_OUT_DATA_16_PACKED_RIGHT_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_16_PACKED_LEFT_SHIFT	0
#घोषणा TEGRA20_SPDIF_DATA_OUT_DATA_16_PACKED_LEFT_MASK		(0xffff << TEGRA20_SPDIF_DATA_OUT_DATA_16_PACKED_LEFT_SHIFT)

/* Fields in TEGRA20_SPDIF_DATA_IN */

/*
 * This रेजिस्टर has 5 dअगरferent क्रमmats:
 * 16-bit        (BIT_MODE=00, PACK=0)
 * 20-bit        (BIT_MODE=01, PACK=0)
 * 24-bit        (BIT_MODE=10, PACK=0)
 * raw           (BIT_MODE=11, PACK=0)
 * 16-bit packed (BIT_MODE=00, PACK=1)
 *
 * Bits 31:24 are common to all modes except 16-bit packed
 */

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_P				(1 << 31)
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_C				(1 << 30)
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_U				(1 << 29)
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_V				(1 << 28)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_PREAMBLE_SHIFT		24
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_PREAMBLE_MASK		(0xf << TEGRA20_SPDIF_DATA_IN_DATA_PREAMBLE_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_16_SHIFT			0
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_16_MASK			(0xffff << TEGRA20_SPDIF_DATA_IN_DATA_16_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_20_SHIFT			0
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_20_MASK			(0xfffff << TEGRA20_SPDIF_DATA_IN_DATA_20_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_24_SHIFT			0
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_24_MASK			(0xffffff << TEGRA20_SPDIF_DATA_IN_DATA_24_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_RAW_DATA_SHIFT		8
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_RAW_DATA_MASK		(0xfffff << TEGRA20_SPDIF_DATA_IN_DATA_RAW_DATA_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_RAW_AUX_SHIFT		4
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_RAW_AUX_MASK			(0xf << TEGRA20_SPDIF_DATA_IN_DATA_RAW_AUX_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_RAW_PREAMBLE_SHIFT		0
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_RAW_PREAMBLE_MASK		(0xf << TEGRA20_SPDIF_DATA_IN_DATA_RAW_PREAMBLE_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_16_PACKED_RIGHT_SHIFT	16
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_16_PACKED_RIGHT_MASK		(0xffff << TEGRA20_SPDIF_DATA_IN_DATA_16_PACKED_RIGHT_SHIFT)

#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_16_PACKED_LEFT_SHIFT		0
#घोषणा TEGRA20_SPDIF_DATA_IN_DATA_16_PACKED_LEFT_MASK		(0xffff << TEGRA20_SPDIF_DATA_IN_DATA_16_PACKED_LEFT_SHIFT)

/* Fields in TEGRA20_SPDIF_CH_STA_RX_A */
/* Fields in TEGRA20_SPDIF_CH_STA_RX_B */
/* Fields in TEGRA20_SPDIF_CH_STA_RX_C */
/* Fields in TEGRA20_SPDIF_CH_STA_RX_D */
/* Fields in TEGRA20_SPDIF_CH_STA_RX_E */
/* Fields in TEGRA20_SPDIF_CH_STA_RX_F */

/*
 * The 6-word receive channel data page buffer holds a block (192 frames) of
 * channel status inक्रमmation. The order of receive is from LSB to MSB
 * bit, and from CH_STA_RX_A to CH_STA_RX_F then back to CH_STA_RX_A.
 */

/* Fields in TEGRA20_SPDIF_CH_STA_TX_A */
/* Fields in TEGRA20_SPDIF_CH_STA_TX_B */
/* Fields in TEGRA20_SPDIF_CH_STA_TX_C */
/* Fields in TEGRA20_SPDIF_CH_STA_TX_D */
/* Fields in TEGRA20_SPDIF_CH_STA_TX_E */
/* Fields in TEGRA20_SPDIF_CH_STA_TX_F */

/*
 * The 6-word transmit channel data page buffer holds a block (192 frames) of
 * channel status inक्रमmation. The order of transmission is from LSB to MSB
 * bit, and from CH_STA_TX_A to CH_STA_TX_F then back to CH_STA_TX_A.
 */

/* Fields in TEGRA20_SPDIF_USR_STA_RX_A */

/*
 * This 4-word deep FIFO receives user FIFO field inक्रमmation. The order of
 * receive is from LSB to MSB bit.
 */

/* Fields in TEGRA20_SPDIF_USR_DAT_TX_A */

/*
 * This 4-word deep FIFO transmits user FIFO field inक्रमmation. The order of
 * transmission is from LSB to MSB bit.
 */

काष्ठा tegra20_spdअगर अणु
	काष्ठा clk *clk_spdअगर_out;
	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data playback_dma_data;
	काष्ठा regmap *regmap;
पूर्ण;

#पूर्ण_अगर
