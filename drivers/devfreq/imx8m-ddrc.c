<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/pm_opp.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/arm-smccc.h>

#घोषणा IMX_SIP_DDR_DVFS			0xc2000004

/* Query available frequencies. */
#घोषणा IMX_SIP_DDR_DVFS_GET_FREQ_COUNT		0x10
#घोषणा IMX_SIP_DDR_DVFS_GET_FREQ_INFO		0x11

/*
 * This should be in a 1:1 mapping with devicetree OPPs but
 * firmware provides additional info.
 */
काष्ठा imx8m_ddrc_freq अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ smcarg;
	पूर्णांक dram_core_parent_index;
	पूर्णांक dram_alt_parent_index;
	पूर्णांक dram_apb_parent_index;
पूर्ण;

/* Hardware limitation */
#घोषणा IMX8M_DDRC_MAX_FREQ_COUNT 4

/*
 * i.MX8M DRAM Controller घड़ीs have the following काष्ठाure (abridged):
 *
 * +----------+       |\            +------+
 * | dram_pll |-------|M| dram_core |      |
 * +----------+       |U|---------->| D    |
 *                 /--|X|           |  D   |
 *   dram_alt_root |  |/            |   R  |
 *                 |                |    C |
 *            +---------+           |      |
 *            |FIX DIV/4|           |      |
 *            +---------+           |      |
 *  composite:     |                |      |
 * +----------+    |                |      |
 * | dram_alt |----/                |      |
 * +----------+                     |      |
 * | dram_apb |-------------------->|      |
 * +----------+                     +------+
 *
 * The dram_pll is used क्रम higher rates and dram_alt is used क्रम lower rates.
 *
 * Frequency चयनing is implemented in TF-A (via SMC call) and can change the
 * configuration of the घड़ीs, including mux parents. The dram_alt and
 * dram_apb घड़ीs are "imx composite" and their parent can change too.
 *
 * We need to prepare/enable the new mux parents head of चयनing and update
 * their inक्रमmation afterwards.
 */
काष्ठा imx8m_ddrc अणु
	काष्ठा devfreq_dev_profile profile;
	काष्ठा devfreq *devfreq;

	/* For frequency चयनing: */
	काष्ठा clk *dram_core;
	काष्ठा clk *dram_pll;
	काष्ठा clk *dram_alt;
	काष्ठा clk *dram_apb;

	पूर्णांक freq_count;
	काष्ठा imx8m_ddrc_freq freq_table[IMX8M_DDRC_MAX_FREQ_COUNT];
पूर्ण;

अटल काष्ठा imx8m_ddrc_freq *imx8m_ddrc_find_freq(काष्ठा imx8m_ddrc *priv,
						    अचिन्हित दीर्घ rate)
अणु
	काष्ठा imx8m_ddrc_freq *freq;
	पूर्णांक i;

	/*
	 * Firmware reports values in MT/s, so we round-करोwn from Hz
	 * Rounding is extra generous to ensure a match.
	 */
	rate = DIV_ROUND_CLOSEST(rate, 250000);
	क्रम (i = 0; i < priv->freq_count; ++i) अणु
		freq = &priv->freq_table[i];
		अगर (freq->rate == rate ||
				freq->rate + 1 == rate ||
				freq->rate - 1 == rate)
			वापस freq;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम imx8m_ddrc_smc_set_freq(पूर्णांक target_freq)
अणु
	काष्ठा arm_smccc_res res;
	u32 online_cpus = 0;
	पूर्णांक cpu;

	local_irq_disable();

	क्रम_each_online_cpu(cpu)
		online_cpus |= (1 << (cpu * 8));

	/* change the ddr freqency */
	arm_smccc_smc(IMX_SIP_DDR_DVFS, target_freq, online_cpus,
			0, 0, 0, 0, 0, &res);

	local_irq_enable();
पूर्ण

अटल काष्ठा clk *clk_get_parent_by_index(काष्ठा clk *clk, पूर्णांक index)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_get_parent_by_index(__clk_get_hw(clk), index);

	वापस hw ? hw->clk : शून्य;
पूर्ण

अटल पूर्णांक imx8m_ddrc_set_freq(काष्ठा device *dev, काष्ठा imx8m_ddrc_freq *freq)
अणु
	काष्ठा imx8m_ddrc *priv = dev_get_drvdata(dev);
	काष्ठा clk *new_dram_core_parent;
	काष्ठा clk *new_dram_alt_parent;
	काष्ठा clk *new_dram_apb_parent;
	पूर्णांक ret;

	/*
	 * Fetch new parents
	 *
	 * new_dram_alt_parent and new_dram_apb_parent are optional but
	 * new_dram_core_parent is not.
	 */
	new_dram_core_parent = clk_get_parent_by_index(
			priv->dram_core, freq->dram_core_parent_index - 1);
	अगर (!new_dram_core_parent) अणु
		dev_err(dev, "failed to fetch new dram_core parent\n");
		वापस -EINVAL;
	पूर्ण
	अगर (freq->dram_alt_parent_index) अणु
		new_dram_alt_parent = clk_get_parent_by_index(
				priv->dram_alt,
				freq->dram_alt_parent_index - 1);
		अगर (!new_dram_alt_parent) अणु
			dev_err(dev, "failed to fetch new dram_alt parent\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		new_dram_alt_parent = शून्य;

	अगर (freq->dram_apb_parent_index) अणु
		new_dram_apb_parent = clk_get_parent_by_index(
				priv->dram_apb,
				freq->dram_apb_parent_index - 1);
		अगर (!new_dram_apb_parent) अणु
			dev_err(dev, "failed to fetch new dram_apb parent\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		new_dram_apb_parent = शून्य;

	/* increase reference counts and ensure clks are ON beक्रमe चयन */
	ret = clk_prepare_enable(new_dram_core_parent);
	अगर (ret) अणु
		dev_err(dev, "failed to enable new dram_core parent: %d\n",
			ret);
		जाओ out;
	पूर्ण
	ret = clk_prepare_enable(new_dram_alt_parent);
	अगर (ret) अणु
		dev_err(dev, "failed to enable new dram_alt parent: %d\n",
			ret);
		जाओ out_disable_core_parent;
	पूर्ण
	ret = clk_prepare_enable(new_dram_apb_parent);
	अगर (ret) अणु
		dev_err(dev, "failed to enable new dram_apb parent: %d\n",
			ret);
		जाओ out_disable_alt_parent;
	पूर्ण

	imx8m_ddrc_smc_set_freq(freq->smcarg);

	/* update parents in clk tree after चयन. */
	ret = clk_set_parent(priv->dram_core, new_dram_core_parent);
	अगर (ret)
		dev_warn(dev, "failed to set dram_core parent: %d\n", ret);
	अगर (new_dram_alt_parent) अणु
		ret = clk_set_parent(priv->dram_alt, new_dram_alt_parent);
		अगर (ret)
			dev_warn(dev, "failed to set dram_alt parent: %d\n",
				 ret);
	पूर्ण
	अगर (new_dram_apb_parent) अणु
		ret = clk_set_parent(priv->dram_apb, new_dram_apb_parent);
		अगर (ret)
			dev_warn(dev, "failed to set dram_apb parent: %d\n",
				 ret);
	पूर्ण

	/*
	 * Explicitly refresh dram PLL rate.
	 *
	 * Even अगर it's marked with CLK_GET_RATE_NOCACHE the rate will not be
	 * स्वतःmatically refreshed when clk_get_rate is called on children.
	 */
	clk_get_rate(priv->dram_pll);

	/*
	 * clk_set_parent transfer the reference count from old parent.
	 * now we drop extra reference counts used during the चयन
	 */
	clk_disable_unprepare(new_dram_apb_parent);
out_disable_alt_parent:
	clk_disable_unprepare(new_dram_alt_parent);
out_disable_core_parent:
	clk_disable_unprepare(new_dram_core_parent);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक imx8m_ddrc_target(काष्ठा device *dev, अचिन्हित दीर्घ *freq, u32 flags)
अणु
	काष्ठा imx8m_ddrc *priv = dev_get_drvdata(dev);
	काष्ठा imx8m_ddrc_freq *freq_info;
	काष्ठा dev_pm_opp *new_opp;
	अचिन्हित दीर्घ old_freq, new_freq;
	पूर्णांक ret;

	new_opp = devfreq_recommended_opp(dev, freq, flags);
	अगर (IS_ERR(new_opp)) अणु
		ret = PTR_ERR(new_opp);
		dev_err(dev, "failed to get recommended opp: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_pm_opp_put(new_opp);

	old_freq = clk_get_rate(priv->dram_core);
	अगर (*freq == old_freq)
		वापस 0;

	freq_info = imx8m_ddrc_find_freq(priv, *freq);
	अगर (!freq_info)
		वापस -EINVAL;

	/*
	 * Read back the clk rate to verअगरy चयन was correct and so that
	 * we can report it on all error paths.
	 */
	ret = imx8m_ddrc_set_freq(dev, freq_info);

	new_freq = clk_get_rate(priv->dram_core);
	अगर (ret)
		dev_err(dev, "ddrc failed freq switch to %lu from %lu: error %d. now at %lu\n",
			*freq, old_freq, ret, new_freq);
	अन्यथा अगर (*freq != new_freq)
		dev_err(dev, "ddrc failed freq update to %lu from %lu, now at %lu\n",
			*freq, old_freq, new_freq);
	अन्यथा
		dev_dbg(dev, "ddrc freq set to %lu (was %lu)\n",
			*freq, old_freq);

	वापस ret;
पूर्ण

अटल पूर्णांक imx8m_ddrc_get_cur_freq(काष्ठा device *dev, अचिन्हित दीर्घ *freq)
अणु
	काष्ठा imx8m_ddrc *priv = dev_get_drvdata(dev);

	*freq = clk_get_rate(priv->dram_core);

	वापस 0;
पूर्ण

अटल पूर्णांक imx8m_ddrc_init_freq_info(काष्ठा device *dev)
अणु
	काष्ठा imx8m_ddrc *priv = dev_get_drvdata(dev);
	काष्ठा arm_smccc_res res;
	पूर्णांक index;

	/* An error here means DDR DVFS API not supported by firmware */
	arm_smccc_smc(IMX_SIP_DDR_DVFS, IMX_SIP_DDR_DVFS_GET_FREQ_COUNT,
			0, 0, 0, 0, 0, 0, &res);
	priv->freq_count = res.a0;
	अगर (priv->freq_count <= 0 ||
			priv->freq_count > IMX8M_DDRC_MAX_FREQ_COUNT)
		वापस -ENODEV;

	क्रम (index = 0; index < priv->freq_count; ++index) अणु
		काष्ठा imx8m_ddrc_freq *freq = &priv->freq_table[index];

		arm_smccc_smc(IMX_SIP_DDR_DVFS, IMX_SIP_DDR_DVFS_GET_FREQ_INFO,
			      index, 0, 0, 0, 0, 0, &res);
		/* Result should be strictly positive */
		अगर ((दीर्घ)res.a0 <= 0)
			वापस -ENODEV;

		freq->rate = res.a0;
		freq->smcarg = index;
		freq->dram_core_parent_index = res.a1;
		freq->dram_alt_parent_index = res.a2;
		freq->dram_apb_parent_index = res.a3;

		/* dram_core has 2 options: dram_pll or dram_alt_root */
		अगर (freq->dram_core_parent_index != 1 &&
				freq->dram_core_parent_index != 2)
			वापस -ENODEV;
		/* dram_apb and dram_alt have exactly 8 possible parents */
		अगर (freq->dram_alt_parent_index > 8 ||
				freq->dram_apb_parent_index > 8)
			वापस -ENODEV;
		/* dram_core from alt requires explicit dram_alt parent */
		अगर (freq->dram_core_parent_index == 2 &&
				freq->dram_alt_parent_index == 0)
			वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक imx8m_ddrc_check_opps(काष्ठा device *dev)
अणु
	काष्ठा imx8m_ddrc *priv = dev_get_drvdata(dev);
	काष्ठा imx8m_ddrc_freq *freq_info;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ freq;
	पूर्णांक i, opp_count;

	/* Enumerate DT OPPs and disable those not supported by firmware */
	opp_count = dev_pm_opp_get_opp_count(dev);
	अगर (opp_count < 0)
		वापस opp_count;
	क्रम (i = 0, freq = 0; i < opp_count; ++i, ++freq) अणु
		opp = dev_pm_opp_find_freq_उच्चमान(dev, &freq);
		अगर (IS_ERR(opp)) अणु
			dev_err(dev, "Failed enumerating OPPs: %ld\n",
				PTR_ERR(opp));
			वापस PTR_ERR(opp);
		पूर्ण
		dev_pm_opp_put(opp);

		freq_info = imx8m_ddrc_find_freq(priv, freq);
		अगर (!freq_info) अणु
			dev_info(dev, "Disable unsupported OPP %luHz %luMT/s\n",
					freq, DIV_ROUND_CLOSEST(freq, 250000));
			dev_pm_opp_disable(dev, freq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx8m_ddrc_निकास(काष्ठा device *dev)
अणु
	dev_pm_opp_of_हटाओ_table(dev);
पूर्ण

अटल पूर्णांक imx8m_ddrc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा imx8m_ddrc *priv;
	स्थिर अक्षर *gov = DEVFREQ_GOV_USERSPACE;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	ret = imx8m_ddrc_init_freq_info(dev);
	अगर (ret) अणु
		dev_err(dev, "failed to init firmware freq info: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->dram_core = devm_clk_get(dev, "core");
	अगर (IS_ERR(priv->dram_core)) अणु
		ret = PTR_ERR(priv->dram_core);
		dev_err(dev, "failed to fetch core clock: %d\n", ret);
		वापस ret;
	पूर्ण
	priv->dram_pll = devm_clk_get(dev, "pll");
	अगर (IS_ERR(priv->dram_pll)) अणु
		ret = PTR_ERR(priv->dram_pll);
		dev_err(dev, "failed to fetch pll clock: %d\n", ret);
		वापस ret;
	पूर्ण
	priv->dram_alt = devm_clk_get(dev, "alt");
	अगर (IS_ERR(priv->dram_alt)) अणु
		ret = PTR_ERR(priv->dram_alt);
		dev_err(dev, "failed to fetch alt clock: %d\n", ret);
		वापस ret;
	पूर्ण
	priv->dram_apb = devm_clk_get(dev, "apb");
	अगर (IS_ERR(priv->dram_apb)) अणु
		ret = PTR_ERR(priv->dram_apb);
		dev_err(dev, "failed to fetch apb clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = dev_pm_opp_of_add_table(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get OPP table\n");
		वापस ret;
	पूर्ण

	ret = imx8m_ddrc_check_opps(dev);
	अगर (ret < 0)
		जाओ err;

	priv->profile.target = imx8m_ddrc_target;
	priv->profile.निकास = imx8m_ddrc_निकास;
	priv->profile.get_cur_freq = imx8m_ddrc_get_cur_freq;
	priv->profile.initial_freq = clk_get_rate(priv->dram_core);

	priv->devfreq = devm_devfreq_add_device(dev, &priv->profile,
						gov, शून्य);
	अगर (IS_ERR(priv->devfreq)) अणु
		ret = PTR_ERR(priv->devfreq);
		dev_err(dev, "failed to add devfreq device: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	dev_pm_opp_of_हटाओ_table(dev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id imx8m_ddrc_of_match[] = अणु
	अणु .compatible = "fsl,imx8m-ddrc", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx8m_ddrc_of_match);

अटल काष्ठा platक्रमm_driver imx8m_ddrc_platdrv = अणु
	.probe		= imx8m_ddrc_probe,
	.driver = अणु
		.name	= "imx8m-ddrc-devfreq",
		.of_match_table = imx8m_ddrc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx8m_ddrc_platdrv);

MODULE_DESCRIPTION("i.MX8M DDR Controller frequency driver");
MODULE_AUTHOR("Leonard Crestez <leonard.crestez@nxp.com>");
MODULE_LICENSE("GPL v2");
