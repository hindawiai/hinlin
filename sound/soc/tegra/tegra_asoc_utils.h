<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra_asoc_utils.h - Definitions क्रम Tegra DAS driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010,2012 - NVIDIA, Inc.
 */

#अगर_अघोषित __TEGRA_ASOC_UTILS_H__
#घोषणा __TEGRA_ASOC_UTILS_H__

काष्ठा clk;
काष्ठा device;

क्रमागत tegra_asoc_utils_soc अणु
	TEGRA_ASOC_UTILS_SOC_TEGRA20,
	TEGRA_ASOC_UTILS_SOC_TEGRA30,
	TEGRA_ASOC_UTILS_SOC_TEGRA114,
	TEGRA_ASOC_UTILS_SOC_TEGRA124,
पूर्ण;

काष्ठा tegra_asoc_utils_data अणु
	काष्ठा device *dev;
	क्रमागत tegra_asoc_utils_soc soc;
	काष्ठा clk *clk_pll_a;
	काष्ठा clk *clk_pll_a_out0;
	काष्ठा clk *clk_cdev1;
	पूर्णांक set_baseघड़ी;
	पूर्णांक set_mclk;
पूर्ण;

पूर्णांक tegra_asoc_utils_set_rate(काष्ठा tegra_asoc_utils_data *data, पूर्णांक srate,
			      पूर्णांक mclk);
पूर्णांक tegra_asoc_utils_set_ac97_rate(काष्ठा tegra_asoc_utils_data *data);
पूर्णांक tegra_asoc_utils_init(काष्ठा tegra_asoc_utils_data *data,
			  काष्ठा device *dev);

#पूर्ण_अगर
