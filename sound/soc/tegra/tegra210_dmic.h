<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra210_dmic.h - Definitions क्रम Tegra210 DMIC driver
 *
 * Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.
 *
 */

#अगर_अघोषित __TEGRA210_DMIC_H__
#घोषणा __TEGRA210_DMIC_H__

/* Register offsets from DMIC BASE */
#घोषणा TEGRA210_DMIC_TX_STATUS				0x0c
#घोषणा TEGRA210_DMIC_TX_INT_STATUS			0x10
#घोषणा TEGRA210_DMIC_TX_INT_MASK			0x14
#घोषणा TEGRA210_DMIC_TX_INT_SET			0x18
#घोषणा TEGRA210_DMIC_TX_INT_CLEAR			0x1c
#घोषणा TEGRA210_DMIC_TX_CIF_CTRL			0x20
#घोषणा TEGRA210_DMIC_ENABLE				0x40
#घोषणा TEGRA210_DMIC_SOFT_RESET			0x44
#घोषणा TEGRA210_DMIC_CG				0x48
#घोषणा TEGRA210_DMIC_STATUS				0x4c
#घोषणा TEGRA210_DMIC_INT_STATUS			0x50
#घोषणा TEGRA210_DMIC_CTRL				0x64
#घोषणा TEGRA210_DMIC_DBG_CTRL				0x70
#घोषणा TEGRA210_DMIC_DCR_BIQUAD_0_COEF_4		0x88
#घोषणा TEGRA210_DMIC_LP_FILTER_GAIN			0x8c
#घोषणा TEGRA210_DMIC_LP_BIQUAD_0_COEF_0		0x90
#घोषणा TEGRA210_DMIC_LP_BIQUAD_0_COEF_1		0x94
#घोषणा TEGRA210_DMIC_LP_BIQUAD_0_COEF_2		0x98
#घोषणा TEGRA210_DMIC_LP_BIQUAD_0_COEF_3		0x9c
#घोषणा TEGRA210_DMIC_LP_BIQUAD_0_COEF_4		0xa0
#घोषणा TEGRA210_DMIC_LP_BIQUAD_1_COEF_0		0xa4
#घोषणा TEGRA210_DMIC_LP_BIQUAD_1_COEF_1		0xa8
#घोषणा TEGRA210_DMIC_LP_BIQUAD_1_COEF_2		0xac
#घोषणा TEGRA210_DMIC_LP_BIQUAD_1_COEF_3		0xb0
#घोषणा TEGRA210_DMIC_LP_BIQUAD_1_COEF_4		0xb4

/* Fields in TEGRA210_DMIC_CTRL */
#घोषणा CH_SEL_SHIFT					8
#घोषणा TEGRA210_DMIC_CTRL_CHANNEL_SELECT_MASK		(0x3 << CH_SEL_SHIFT)
#घोषणा LRSEL_POL_SHIFT					4
#घोषणा TEGRA210_DMIC_CTRL_LRSEL_POLARITY_MASK		(0x1 << LRSEL_POL_SHIFT)
#घोषणा OSR_SHIFT					0
#घोषणा TEGRA210_DMIC_CTRL_OSR_MASK			(0x3 << OSR_SHIFT)

#घोषणा DMIC_OSR_FACTOR					64

#घोषणा DEFAULT_GAIN_Q23				0x800000

/* Max boost gain factor used क्रम mixer control */
#घोषणा MAX_BOOST_GAIN 25599

क्रमागत tegra_dmic_ch_select अणु
	DMIC_CH_SELECT_LEFT,
	DMIC_CH_SELECT_RIGHT,
	DMIC_CH_SELECT_STEREO,
पूर्ण;

क्रमागत tegra_dmic_osr अणु
	DMIC_OSR_64,
	DMIC_OSR_128,
	DMIC_OSR_256,
पूर्ण;

क्रमागत tegra_dmic_lrsel अणु
	DMIC_LRSEL_LEFT,
	DMIC_LRSEL_RIGHT,
पूर्ण;

काष्ठा tegra210_dmic अणु
	काष्ठा clk *clk_dmic;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक mono_to_stereo;
	अचिन्हित पूर्णांक stereo_to_mono;
	अचिन्हित पूर्णांक boost_gain;
	अचिन्हित पूर्णांक ch_select;
	अचिन्हित पूर्णांक osr_val;
	अचिन्हित पूर्णांक lrsel;
पूर्ण;

#पूर्ण_अगर
