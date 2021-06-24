<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra186_dspk.h - Definitions क्रम Tegra186 DSPK driver
 *
 * Copyright (c) 2020 NVIDIA CORPORATION. All rights reserved.
 *
 */

#अगर_अघोषित __TEGRA186_DSPK_H__
#घोषणा __TEGRA186_DSPK_H__

/* Register offsets from DSPK BASE */
#घोषणा TEGRA186_DSPK_RX_STATUS			0x0c
#घोषणा TEGRA186_DSPK_RX_INT_STATUS		0x10
#घोषणा TEGRA186_DSPK_RX_INT_MASK		0x14
#घोषणा TEGRA186_DSPK_RX_INT_SET		0x18
#घोषणा TEGRA186_DSPK_RX_INT_CLEAR		0x1c
#घोषणा TEGRA186_DSPK_RX_CIF_CTRL		0x20
#घोषणा TEGRA186_DSPK_ENABLE			0x40
#घोषणा TEGRA186_DSPK_SOFT_RESET		0x44
#घोषणा TEGRA186_DSPK_CG			0x48
#घोषणा TEGRA186_DSPK_STATUS			0x4c
#घोषणा TEGRA186_DSPK_INT_STATUS		0x50
#घोषणा TEGRA186_DSPK_CORE_CTRL			0x60
#घोषणा TEGRA186_DSPK_CODEC_CTRL		0x64

/* DSPK CORE CONTROL fields */
#घोषणा CH_SEL_SHIFT				8
#घोषणा TEGRA186_DSPK_CHANNEL_SELECT_MASK	(0x3 << CH_SEL_SHIFT)
#घोषणा DSPK_OSR_SHIFT				4
#घोषणा TEGRA186_DSPK_OSR_MASK			(0x3 << DSPK_OSR_SHIFT)
#घोषणा LRSEL_POL_SHIFT				0
#घोषणा TEGRA186_DSPK_CTRL_LRSEL_POLARITY_MASK	(0x1 << LRSEL_POL_SHIFT)
#घोषणा TEGRA186_DSPK_RX_FIFO_DEPTH		64

#घोषणा DSPK_OSR_FACTOR				32

/* DSPK पूर्णांकerface घड़ी ratio */
#घोषणा DSPK_CLK_RATIO				4

क्रमागत tegra_dspk_osr अणु
	DSPK_OSR_32,
	DSPK_OSR_64,
	DSPK_OSR_128,
	DSPK_OSR_256,
पूर्ण;

क्रमागत tegra_dspk_ch_sel अणु
	DSPK_CH_SELECT_LEFT,
	DSPK_CH_SELECT_RIGHT,
	DSPK_CH_SELECT_STEREO,
पूर्ण;

क्रमागत tegra_dspk_lrsel अणु
	DSPK_LRSEL_LEFT,
	DSPK_LRSEL_RIGHT,
पूर्ण;

काष्ठा tegra186_dspk अणु
	अचिन्हित पूर्णांक rx_fअगरo_th;
	अचिन्हित पूर्णांक osr_val;
	अचिन्हित पूर्णांक lrsel;
	अचिन्हित पूर्णांक ch_sel;
	अचिन्हित पूर्णांक mono_to_stereo;
	अचिन्हित पूर्णांक stereo_to_mono;
	काष्ठा clk *clk_dspk;
	काष्ठा regmap *regmap;
पूर्ण;

#पूर्ण_अगर
