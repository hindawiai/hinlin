<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra_cअगर.h - TEGRA Audio CIF Programming
 *
 * Copyright (c) 2020 NVIDIA CORPORATION.  All rights reserved.
 *
 */

#अगर_अघोषित __TEGRA_CIF_H__
#घोषणा __TEGRA_CIF_H__

#समावेश <linux/regmap.h>

#घोषणा TEGRA_ACIF_CTRL_FIFO_TH_SHIFT		24
#घोषणा TEGRA_ACIF_CTRL_AUDIO_CH_SHIFT		20
#घोषणा TEGRA_ACIF_CTRL_CLIENT_CH_SHIFT		16
#घोषणा TEGRA_ACIF_CTRL_AUDIO_BITS_SHIFT	12
#घोषणा TEGRA_ACIF_CTRL_CLIENT_BITS_SHIFT	8
#घोषणा TEGRA_ACIF_CTRL_EXPAND_SHIFT		6
#घोषणा TEGRA_ACIF_CTRL_STEREO_CONV_SHIFT	4
#घोषणा TEGRA_ACIF_CTRL_REPLICATE_SHIFT		3
#घोषणा TEGRA_ACIF_CTRL_TRUNCATE_SHIFT		1
#घोषणा TEGRA_ACIF_CTRL_MONO_CONV_SHIFT		0

/* AUDIO/CLIENT_BITS values */
#घोषणा TEGRA_ACIF_BITS_8			1
#घोषणा TEGRA_ACIF_BITS_16			3
#घोषणा TEGRA_ACIF_BITS_24			5
#घोषणा TEGRA_ACIF_BITS_32			7

#घोषणा TEGRA_ACIF_UPDATE_MASK			0x3ffffffb

काष्ठा tegra_cअगर_conf अणु
	अचिन्हित पूर्णांक threshold;
	अचिन्हित पूर्णांक audio_ch;
	अचिन्हित पूर्णांक client_ch;
	अचिन्हित पूर्णांक audio_bits;
	अचिन्हित पूर्णांक client_bits;
	अचिन्हित पूर्णांक expand;
	अचिन्हित पूर्णांक stereo_conv;
	अचिन्हित पूर्णांक replicate;
	अचिन्हित पूर्णांक truncate;
	अचिन्हित पूर्णांक mono_conv;
पूर्ण;

अटल अंतरभूत व्योम tegra_set_cअगर(काष्ठा regmap *regmap, अचिन्हित पूर्णांक reg,
				 काष्ठा tegra_cअगर_conf *conf)
अणु
	अचिन्हित पूर्णांक value;

	value = (conf->threshold << TEGRA_ACIF_CTRL_FIFO_TH_SHIFT) |
		((conf->audio_ch - 1) << TEGRA_ACIF_CTRL_AUDIO_CH_SHIFT) |
		((conf->client_ch - 1) << TEGRA_ACIF_CTRL_CLIENT_CH_SHIFT) |
		(conf->audio_bits << TEGRA_ACIF_CTRL_AUDIO_BITS_SHIFT) |
		(conf->client_bits << TEGRA_ACIF_CTRL_CLIENT_BITS_SHIFT) |
		(conf->expand << TEGRA_ACIF_CTRL_EXPAND_SHIFT) |
		(conf->stereo_conv << TEGRA_ACIF_CTRL_STEREO_CONV_SHIFT) |
		(conf->replicate << TEGRA_ACIF_CTRL_REPLICATE_SHIFT) |
		(conf->truncate << TEGRA_ACIF_CTRL_TRUNCATE_SHIFT) |
		(conf->mono_conv << TEGRA_ACIF_CTRL_MONO_CONV_SHIFT);

	regmap_update_bits(regmap, reg, TEGRA_ACIF_UPDATE_MASK, value);
पूर्ण

#पूर्ण_अगर
