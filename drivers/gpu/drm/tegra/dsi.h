<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2013 NVIDIA Corporation
 */

#अगर_अघोषित DRM_TEGRA_DSI_H
#घोषणा DRM_TEGRA_DSI_H

#घोषणा DSI_INCR_SYNCPT			0x00
#घोषणा DSI_INCR_SYNCPT_CONTROL		0x01
#घोषणा DSI_INCR_SYNCPT_ERROR		0x02
#घोषणा DSI_CTXSW			0x08
#घोषणा DSI_RD_DATA			0x09
#घोषणा DSI_WR_DATA			0x0a
#घोषणा DSI_POWER_CONTROL		0x0b
#घोषणा DSI_POWER_CONTROL_ENABLE	(1 << 0)
#घोषणा DSI_INT_ENABLE			0x0c
#घोषणा DSI_INT_STATUS			0x0d
#घोषणा DSI_INT_MASK			0x0e
#घोषणा DSI_HOST_CONTROL		0x0f
#घोषणा DSI_HOST_CONTROL_FIFO_RESET	(1 << 21)
#घोषणा DSI_HOST_CONTROL_CRC_RESET	(1 << 20)
#घोषणा DSI_HOST_CONTROL_TX_TRIG_SOL	(0 << 12)
#घोषणा DSI_HOST_CONTROL_TX_TRIG_FIFO	(1 << 12)
#घोषणा DSI_HOST_CONTROL_TX_TRIG_HOST	(2 << 12)
#घोषणा DSI_HOST_CONTROL_RAW		(1 << 6)
#घोषणा DSI_HOST_CONTROL_HS		(1 << 5)
#घोषणा DSI_HOST_CONTROL_FIFO_SEL	(1 << 4)
#घोषणा DSI_HOST_CONTROL_IMM_BTA	(1 << 3)
#घोषणा DSI_HOST_CONTROL_PKT_BTA	(1 << 2)
#घोषणा DSI_HOST_CONTROL_CS		(1 << 1)
#घोषणा DSI_HOST_CONTROL_ECC		(1 << 0)
#घोषणा DSI_CONTROL			0x10
#घोषणा DSI_CONTROL_HS_CLK_CTRL		(1 << 20)
#घोषणा DSI_CONTROL_CHANNEL(c)		(((c) & 0x3) << 16)
#घोषणा DSI_CONTROL_FORMAT(f)		(((f) & 0x3) << 12)
#घोषणा DSI_CONTROL_TX_TRIG(x)		(((x) & 0x3) <<  8)
#घोषणा DSI_CONTROL_LANES(n)		(((n) & 0x3) <<  4)
#घोषणा DSI_CONTROL_DCS_ENABLE		(1 << 3)
#घोषणा DSI_CONTROL_SOURCE(s)		(((s) & 0x1) <<  2)
#घोषणा DSI_CONTROL_VIDEO_ENABLE	(1 << 1)
#घोषणा DSI_CONTROL_HOST_ENABLE		(1 << 0)
#घोषणा DSI_SOL_DELAY			0x11
#घोषणा DSI_MAX_THRESHOLD		0x12
#घोषणा DSI_TRIGGER			0x13
#घोषणा DSI_TRIGGER_HOST		(1 << 1)
#घोषणा DSI_TRIGGER_VIDEO		(1 << 0)
#घोषणा DSI_TX_CRC			0x14
#घोषणा DSI_STATUS			0x15
#घोषणा DSI_STATUS_IDLE			(1 << 10)
#घोषणा DSI_STATUS_UNDERFLOW		(1 <<  9)
#घोषणा DSI_STATUS_OVERFLOW		(1 <<  8)
#घोषणा DSI_INIT_SEQ_CONTROL		0x1a
#घोषणा DSI_INIT_SEQ_DATA_0		0x1b
#घोषणा DSI_INIT_SEQ_DATA_1		0x1c
#घोषणा DSI_INIT_SEQ_DATA_2		0x1d
#घोषणा DSI_INIT_SEQ_DATA_3		0x1e
#घोषणा DSI_INIT_SEQ_DATA_4		0x1f
#घोषणा DSI_INIT_SEQ_DATA_5		0x20
#घोषणा DSI_INIT_SEQ_DATA_6		0x21
#घोषणा DSI_INIT_SEQ_DATA_7		0x22
#घोषणा DSI_PKT_SEQ_0_LO		0x23
#घोषणा DSI_PKT_SEQ_0_HI		0x24
#घोषणा DSI_PKT_SEQ_1_LO		0x25
#घोषणा DSI_PKT_SEQ_1_HI		0x26
#घोषणा DSI_PKT_SEQ_2_LO		0x27
#घोषणा DSI_PKT_SEQ_2_HI		0x28
#घोषणा DSI_PKT_SEQ_3_LO		0x29
#घोषणा DSI_PKT_SEQ_3_HI		0x2a
#घोषणा DSI_PKT_SEQ_4_LO		0x2b
#घोषणा DSI_PKT_SEQ_4_HI		0x2c
#घोषणा DSI_PKT_SEQ_5_LO		0x2d
#घोषणा DSI_PKT_SEQ_5_HI		0x2e
#घोषणा DSI_DCS_CMDS			0x33
#घोषणा DSI_PKT_LEN_0_1			0x34
#घोषणा DSI_PKT_LEN_2_3			0x35
#घोषणा DSI_PKT_LEN_4_5			0x36
#घोषणा DSI_PKT_LEN_6_7			0x37
#घोषणा DSI_PHY_TIMING_0		0x3c
#घोषणा DSI_PHY_TIMING_1		0x3d
#घोषणा DSI_PHY_TIMING_2		0x3e
#घोषणा DSI_BTA_TIMING			0x3f

#घोषणा DSI_TIMING_FIELD(value, period, hwinc) \
	((DIV_ROUND_CLOSEST(value, period) - (hwinc)) & 0xff)

#घोषणा DSI_TIMEOUT_0			0x44
#घोषणा DSI_TIMEOUT_LRX(x)		(((x) & 0xffff) << 16)
#घोषणा DSI_TIMEOUT_HTX(x)		(((x) & 0xffff) <<  0)
#घोषणा DSI_TIMEOUT_1			0x45
#घोषणा DSI_TIMEOUT_PR(x)		(((x) & 0xffff) << 16)
#घोषणा DSI_TIMEOUT_TA(x)		(((x) & 0xffff) <<  0)
#घोषणा DSI_TO_TALLY			0x46
#घोषणा DSI_TALLY_TA(x)			(((x) & 0xff) << 16)
#घोषणा DSI_TALLY_LRX(x)		(((x) & 0xff) <<  8)
#घोषणा DSI_TALLY_HTX(x)		(((x) & 0xff) <<  0)
#घोषणा DSI_PAD_CONTROL_0		0x4b
#घोषणा DSI_PAD_CONTROL_VS1_PDIO(x)	(((x) & 0xf) <<  0)
#घोषणा DSI_PAD_CONTROL_VS1_PDIO_CLK	(1 <<  8)
#घोषणा DSI_PAD_CONTROL_VS1_PULLDN(x)	(((x) & 0xf) << 16)
#घोषणा DSI_PAD_CONTROL_VS1_PULLDN_CLK	(1 << 24)
#घोषणा DSI_PAD_CONTROL_CD		0x4c
#घोषणा DSI_PAD_CD_STATUS		0x4d
#घोषणा DSI_VIDEO_MODE_CONTROL		0x4e
#घोषणा DSI_PAD_CONTROL_1		0x4f
#घोषणा DSI_PAD_CONTROL_2		0x50
#घोषणा DSI_PAD_OUT_CLK(x)		(((x) & 0x7) <<  0)
#घोषणा DSI_PAD_LP_DN(x)		(((x) & 0x7) <<  4)
#घोषणा DSI_PAD_LP_UP(x)		(((x) & 0x7) <<  8)
#घोषणा DSI_PAD_SLEW_DN(x)		(((x) & 0x7) << 12)
#घोषणा DSI_PAD_SLEW_UP(x)		(((x) & 0x7) << 16)
#घोषणा DSI_PAD_CONTROL_3		0x51
#घोषणा  DSI_PAD_PREEMP_PD_CLK(x)	(((x) & 0x3) << 12)
#घोषणा  DSI_PAD_PREEMP_PU_CLK(x)	(((x) & 0x3) << 8)
#घोषणा  DSI_PAD_PREEMP_PD(x)		(((x) & 0x3) << 4)
#घोषणा  DSI_PAD_PREEMP_PU(x)		(((x) & 0x3) << 0)
#घोषणा DSI_PAD_CONTROL_4		0x52
#घोषणा DSI_GANGED_MODE_CONTROL		0x53
#घोषणा DSI_GANGED_MODE_CONTROL_ENABLE	(1 << 0)
#घोषणा DSI_GANGED_MODE_START		0x54
#घोषणा DSI_GANGED_MODE_SIZE		0x55
#घोषणा DSI_RAW_DATA_BYTE_COUNT		0x56
#घोषणा DSI_ULTRA_LOW_POWER_CONTROL	0x57
#घोषणा DSI_INIT_SEQ_DATA_8		0x58
#घोषणा DSI_INIT_SEQ_DATA_9		0x59
#घोषणा DSI_INIT_SEQ_DATA_10		0x5a
#घोषणा DSI_INIT_SEQ_DATA_11		0x5b
#घोषणा DSI_INIT_SEQ_DATA_12		0x5c
#घोषणा DSI_INIT_SEQ_DATA_13		0x5d
#घोषणा DSI_INIT_SEQ_DATA_14		0x5e
#घोषणा DSI_INIT_SEQ_DATA_15		0x5f

/*
 * pixel क्रमmat as used in the DSI_CONTROL_FORMAT field
 */
क्रमागत tegra_dsi_क्रमmat अणु
	TEGRA_DSI_FORMAT_16P,
	TEGRA_DSI_FORMAT_18NP,
	TEGRA_DSI_FORMAT_18P,
	TEGRA_DSI_FORMAT_24P,
पूर्ण;

#पूर्ण_अगर
