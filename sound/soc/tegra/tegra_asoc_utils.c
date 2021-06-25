<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra_asoc_utils.c - Harmony machine ASoC driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010,2012 - NVIDIA, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश "tegra_asoc_utils.h"

पूर्णांक tegra_asoc_utils_set_rate(काष्ठा tegra_asoc_utils_data *data, पूर्णांक srate,
			      पूर्णांक mclk)
अणु
	पूर्णांक new_baseघड़ी;
	bool clk_change;
	पूर्णांक err;

	चयन (srate) अणु
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		अगर (data->soc == TEGRA_ASOC_UTILS_SOC_TEGRA20)
			new_baseघड़ी = 56448000;
		अन्यथा अगर (data->soc == TEGRA_ASOC_UTILS_SOC_TEGRA30)
			new_baseघड़ी = 564480000;
		अन्यथा
			new_baseघड़ी = 282240000;
		अवरोध;
	हाल 8000:
	हाल 16000:
	हाल 32000:
	हाल 48000:
	हाल 64000:
	हाल 96000:
		अगर (data->soc == TEGRA_ASOC_UTILS_SOC_TEGRA20)
			new_baseघड़ी = 73728000;
		अन्यथा अगर (data->soc == TEGRA_ASOC_UTILS_SOC_TEGRA30)
			new_baseघड़ी = 552960000;
		अन्यथा
			new_baseघड़ी = 368640000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	clk_change = ((new_baseघड़ी != data->set_baseघड़ी) ||
			(mclk != data->set_mclk));
	अगर (!clk_change)
		वापस 0;

	data->set_baseघड़ी = 0;
	data->set_mclk = 0;

	clk_disable_unprepare(data->clk_cdev1);

	err = clk_set_rate(data->clk_pll_a, new_baseघड़ी);
	अगर (err) अणु
		dev_err(data->dev, "Can't set pll_a rate: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_set_rate(data->clk_pll_a_out0, mclk);
	अगर (err) अणु
		dev_err(data->dev, "Can't set pll_a_out0 rate: %d\n", err);
		वापस err;
	पूर्ण

	/* Don't set cdev1/extern1 rate; it's locked to pll_a_out0 */

	err = clk_prepare_enable(data->clk_cdev1);
	अगर (err) अणु
		dev_err(data->dev, "Can't enable cdev1: %d\n", err);
		वापस err;
	पूर्ण

	data->set_baseघड़ी = new_baseघड़ी;
	data->set_mclk = mclk;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_asoc_utils_set_rate);

पूर्णांक tegra_asoc_utils_set_ac97_rate(काष्ठा tegra_asoc_utils_data *data)
अणु
	स्थिर पूर्णांक pll_rate = 73728000;
	स्थिर पूर्णांक ac97_rate = 24576000;
	पूर्णांक err;

	clk_disable_unprepare(data->clk_cdev1);

	/*
	 * AC97 rate is fixed at 24.576MHz and is used क्रम both the host
	 * controller and the बाह्यal codec
	 */
	err = clk_set_rate(data->clk_pll_a, pll_rate);
	अगर (err) अणु
		dev_err(data->dev, "Can't set pll_a rate: %d\n", err);
		वापस err;
	पूर्ण

	err = clk_set_rate(data->clk_pll_a_out0, ac97_rate);
	अगर (err) अणु
		dev_err(data->dev, "Can't set pll_a_out0 rate: %d\n", err);
		वापस err;
	पूर्ण

	/* Don't set cdev1/extern1 rate; it's locked to pll_a_out0 */

	err = clk_prepare_enable(data->clk_cdev1);
	अगर (err) अणु
		dev_err(data->dev, "Can't enable cdev1: %d\n", err);
		वापस err;
	पूर्ण

	data->set_baseघड़ी = pll_rate;
	data->set_mclk = ac97_rate;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_asoc_utils_set_ac97_rate);

पूर्णांक tegra_asoc_utils_init(काष्ठा tegra_asoc_utils_data *data,
			  काष्ठा device *dev)
अणु
	काष्ठा clk *clk_out_1, *clk_बाह्य1;
	पूर्णांक ret;

	data->dev = dev;

	अगर (of_machine_is_compatible("nvidia,tegra20"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA20;
	अन्यथा अगर (of_machine_is_compatible("nvidia,tegra30"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA30;
	अन्यथा अगर (of_machine_is_compatible("nvidia,tegra114"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA114;
	अन्यथा अगर (of_machine_is_compatible("nvidia,tegra124"))
		data->soc = TEGRA_ASOC_UTILS_SOC_TEGRA124;
	अन्यथा अणु
		dev_err(data->dev, "SoC unknown to Tegra ASoC utils\n");
		वापस -EINVAL;
	पूर्ण

	data->clk_pll_a = devm_clk_get(dev, "pll_a");
	अगर (IS_ERR(data->clk_pll_a)) अणु
		dev_err(data->dev, "Can't retrieve clk pll_a\n");
		वापस PTR_ERR(data->clk_pll_a);
	पूर्ण

	data->clk_pll_a_out0 = devm_clk_get(dev, "pll_a_out0");
	अगर (IS_ERR(data->clk_pll_a_out0)) अणु
		dev_err(data->dev, "Can't retrieve clk pll_a_out0\n");
		वापस PTR_ERR(data->clk_pll_a_out0);
	पूर्ण

	data->clk_cdev1 = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(data->clk_cdev1)) अणु
		dev_err(data->dev, "Can't retrieve clk cdev1\n");
		वापस PTR_ERR(data->clk_cdev1);
	पूर्ण

	/*
	 * If घड़ी parents are not set in DT, configure here to use clk_out_1
	 * as mclk and बाह्य1 as parent क्रम Tegra30 and higher.
	 */
	अगर (!of_find_property(dev->of_node, "assigned-clock-parents", शून्य) &&
	    data->soc > TEGRA_ASOC_UTILS_SOC_TEGRA20) अणु
		dev_warn(data->dev,
			 "Configuring clocks for a legacy device-tree\n");
		dev_warn(data->dev,
			 "Please update DT to use assigned-clock-parents\n");
		clk_बाह्य1 = devm_clk_get(dev, "extern1");
		अगर (IS_ERR(clk_बाह्य1)) अणु
			dev_err(data->dev, "Can't retrieve clk extern1\n");
			वापस PTR_ERR(clk_बाह्य1);
		पूर्ण

		ret = clk_set_parent(clk_बाह्य1, data->clk_pll_a_out0);
		अगर (ret < 0) अणु
			dev_err(data->dev,
				"Set parent failed for clk extern1\n");
			वापस ret;
		पूर्ण

		clk_out_1 = devm_clk_get(dev, "pmc_clk_out_1");
		अगर (IS_ERR(clk_out_1)) अणु
			dev_err(data->dev, "Can't retrieve pmc_clk_out_1\n");
			वापस PTR_ERR(clk_out_1);
		पूर्ण

		ret = clk_set_parent(clk_out_1, clk_बाह्य1);
		अगर (ret < 0) अणु
			dev_err(data->dev,
				"Set parent failed for pmc_clk_out_1\n");
			वापस ret;
		पूर्ण

		data->clk_cdev1 = clk_out_1;
	पूर्ण

	/*
	 * FIXME: There is some unknown dependency between audio mclk disable
	 * and suspend-resume functionality on Tegra30, although audio mclk is
	 * only needed क्रम audio.
	 */
	ret = clk_prepare_enable(data->clk_cdev1);
	अगर (ret) अणु
		dev_err(data->dev, "Can't enable cdev1: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_asoc_utils_init);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra ASoC utility code");
MODULE_LICENSE("GPL");
