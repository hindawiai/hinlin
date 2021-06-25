<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra210_i2s.h - Definitions क्रम Tegra210 I2S driver
 *
 * Copyright (c) 2020 NVIDIA CORPORATION. All rights reserved.
 *
 */

#अगर_अघोषित __TEGRA210_I2S_H__
#घोषणा __TEGRA210_I2S_H__

/* Register offsets from I2S*_BASE */
#घोषणा TEGRA210_I2S_RX_ENABLE			0x0
#घोषणा TEGRA210_I2S_RX_SOFT_RESET		0x4
#घोषणा TEGRA210_I2S_RX_STATUS			0x0c
#घोषणा TEGRA210_I2S_RX_INT_STATUS		0x10
#घोषणा TEGRA210_I2S_RX_INT_MASK		0x14
#घोषणा TEGRA210_I2S_RX_INT_SET			0x18
#घोषणा TEGRA210_I2S_RX_INT_CLEAR		0x1c
#घोषणा TEGRA210_I2S_RX_CIF_CTRL		0x20
#घोषणा TEGRA210_I2S_RX_CTRL			0x24
#घोषणा TEGRA210_I2S_RX_SLOT_CTRL		0x28
#घोषणा TEGRA210_I2S_RX_CLK_TRIM		0x2c
#घोषणा TEGRA210_I2S_RX_CYA			0x30
#घोषणा TEGRA210_I2S_RX_CIF_FIFO_STATUS		0x34
#घोषणा TEGRA210_I2S_TX_ENABLE			0x40
#घोषणा TEGRA210_I2S_TX_SOFT_RESET		0x44
#घोषणा TEGRA210_I2S_TX_STATUS			0x4c
#घोषणा TEGRA210_I2S_TX_INT_STATUS		0x50
#घोषणा TEGRA210_I2S_TX_INT_MASK		0x54
#घोषणा TEGRA210_I2S_TX_INT_SET			0x58
#घोषणा TEGRA210_I2S_TX_INT_CLEAR		0x5c
#घोषणा TEGRA210_I2S_TX_CIF_CTRL		0x60
#घोषणा TEGRA210_I2S_TX_CTRL			0x64
#घोषणा TEGRA210_I2S_TX_SLOT_CTRL		0x68
#घोषणा TEGRA210_I2S_TX_CLK_TRIM		0x6c
#घोषणा TEGRA210_I2S_TX_CYA			0x70
#घोषणा TEGRA210_I2S_TX_CIF_FIFO_STATUS		0x74
#घोषणा TEGRA210_I2S_ENABLE			0x80
#घोषणा TEGRA210_I2S_SOFT_RESET			0x84
#घोषणा TEGRA210_I2S_CG				0x88
#घोषणा TEGRA210_I2S_STATUS			0x8c
#घोषणा TEGRA210_I2S_INT_STATUS			0x90
#घोषणा TEGRA210_I2S_CTRL			0xa0
#घोषणा TEGRA210_I2S_TIMING			0xa4
#घोषणा TEGRA210_I2S_SLOT_CTRL			0xa8
#घोषणा TEGRA210_I2S_CLK_TRIM			0xac
#घोषणा TEGRA210_I2S_CYA			0xb0

/* Bit fields, shअगरts and masks */
#घोषणा I2S_DATA_SHIFT				8
#घोषणा I2S_CTRL_DATA_OFFSET_MASK		(0x7ff << I2S_DATA_SHIFT)

#घोषणा I2S_EN_SHIFT				0
#घोषणा I2S_EN_MASK				BIT(I2S_EN_SHIFT)
#घोषणा I2S_EN					BIT(I2S_EN_SHIFT)

#घोषणा I2S_FSYNC_WIDTH_SHIFT			24
#घोषणा I2S_CTRL_FSYNC_WIDTH_MASK		(0xff << I2S_FSYNC_WIDTH_SHIFT)

#घोषणा I2S_POS_EDGE				0
#घोषणा I2S_NEG_EDGE				1
#घोषणा I2S_EDGE_SHIFT				20
#घोषणा I2S_CTRL_EDGE_CTRL_MASK			BIT(I2S_EDGE_SHIFT)
#घोषणा I2S_CTRL_EDGE_CTRL_POS_EDGE		(I2S_POS_EDGE << I2S_EDGE_SHIFT)
#घोषणा I2S_CTRL_EDGE_CTRL_NEG_EDGE		(I2S_NEG_EDGE << I2S_EDGE_SHIFT)

#घोषणा I2S_FMT_LRCK				0
#घोषणा I2S_FMT_FSYNC				1
#घोषणा I2S_FMT_SHIFT				12
#घोषणा I2S_CTRL_FRAME_FMT_MASK			(7 << I2S_FMT_SHIFT)
#घोषणा I2S_CTRL_FRAME_FMT_LRCK_MODE		(I2S_FMT_LRCK << I2S_FMT_SHIFT)
#घोषणा I2S_CTRL_FRAME_FMT_FSYNC_MODE		(I2S_FMT_FSYNC << I2S_FMT_SHIFT)

#घोषणा I2S_CTRL_MASTER_EN_SHIFT		10
#घोषणा I2S_CTRL_MASTER_EN_MASK			BIT(I2S_CTRL_MASTER_EN_SHIFT)
#घोषणा I2S_CTRL_MASTER_EN			BIT(I2S_CTRL_MASTER_EN_SHIFT)

#घोषणा I2S_CTRL_LRCK_POL_SHIFT			9
#घोषणा I2S_CTRL_LRCK_POL_MASK			BIT(I2S_CTRL_LRCK_POL_SHIFT)
#घोषणा I2S_CTRL_LRCK_POL_LOW			(0 << I2S_CTRL_LRCK_POL_SHIFT)
#घोषणा I2S_CTRL_LRCK_POL_HIGH			BIT(I2S_CTRL_LRCK_POL_SHIFT)

#घोषणा I2S_CTRL_LPBK_SHIFT			8
#घोषणा I2S_CTRL_LPBK_MASK			BIT(I2S_CTRL_LPBK_SHIFT)
#घोषणा I2S_CTRL_LPBK_EN			BIT(I2S_CTRL_LPBK_SHIFT)

#घोषणा I2S_BITS_8				1
#घोषणा I2S_BITS_16				3
#घोषणा I2S_BITS_32				7
#घोषणा I2S_CTRL_BIT_SIZE_MASK			0x7

#घोषणा I2S_TIMING_CH_BIT_CNT_MASK		0x7ff
#घोषणा I2S_TIMING_CH_BIT_CNT_SHIFT		0

#घोषणा I2S_SOFT_RESET_SHIFT			0
#घोषणा I2S_SOFT_RESET_MASK			BIT(I2S_SOFT_RESET_SHIFT)
#घोषणा I2S_SOFT_RESET_EN			BIT(I2S_SOFT_RESET_SHIFT)

#घोषणा I2S_RX_FIFO_DEPTH			64
#घोषणा DEFAULT_I2S_RX_FIFO_THRESHOLD		3

#घोषणा DEFAULT_I2S_SLOT_MASK			0xffff

क्रमागत tegra210_i2s_path अणु
	I2S_RX_PATH,
	I2S_TX_PATH,
	I2S_PATHS,
पूर्ण;

काष्ठा tegra210_i2s अणु
	काष्ठा clk *clk_i2s;
	काष्ठा clk *clk_sync_input;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक stereo_to_mono[I2S_PATHS];
	अचिन्हित पूर्णांक mono_to_stereo[I2S_PATHS];
	अचिन्हित पूर्णांक dai_fmt;
	अचिन्हित पूर्णांक fsync_width;
	अचिन्हित पूर्णांक bclk_ratio;
	अचिन्हित पूर्णांक tx_mask;
	अचिन्हित पूर्णांक rx_mask;
	अचिन्हित पूर्णांक rx_fअगरo_th;
	bool loopback;
पूर्ण;

#पूर्ण_अगर
