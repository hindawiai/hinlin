<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * UFS PHY driver क्रम Samsung SoC
 *
 * Copyright (C) 2020 Samsung Electronics Co., Ltd.
 * Author: Seungwon Jeon <essuuj@gmail.com>
 * Author: Alim Akhtar <alim.akhtar@samsung.com>
 *
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश "phy-samsung-ufs.h"

#घोषणा क्रम_each_phy_lane(phy, i) \
	क्रम (i = 0; i < (phy)->lane_cnt; i++)
#घोषणा क्रम_each_phy_cfg(cfg) \
	क्रम (; (cfg)->id; (cfg)++)

#घोषणा PHY_DEF_LANE_CNT	1

अटल व्योम samsung_ufs_phy_config(काष्ठा samsung_ufs_phy *phy,
				   स्थिर काष्ठा samsung_ufs_phy_cfg *cfg,
				   u8 lane)
अणु
	क्रमागत अणुLANE_0, LANE_1पूर्ण; /* lane index */

	चयन (lane) अणु
	हाल LANE_0:
		ग_लिखोl(cfg->val, (phy)->reg_pma + cfg->off_0);
		अवरोध;
	हाल LANE_1:
		अगर (cfg->id == PHY_TRSV_BLK)
			ग_लिखोl(cfg->val, (phy)->reg_pma + cfg->off_1);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक samsung_ufs_phy_रुको_क्रम_lock_acq(काष्ठा phy *phy)
अणु
	काष्ठा samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	स्थिर अचिन्हित पूर्णांक समयout_us = 100000;
	स्थिर अचिन्हित पूर्णांक sleep_us = 10;
	u32 val;
	पूर्णांक err;

	err = पढ़ोl_poll_समयout(
			ufs_phy->reg_pma + PHY_APB_ADDR(PHY_PLL_LOCK_STATUS),
			val, (val & PHY_PLL_LOCK_BIT), sleep_us, समयout_us);
	अगर (err) अणु
		dev_err(ufs_phy->dev,
			"failed to get phy pll lock acquisition %d\n", err);
		जाओ out;
	पूर्ण

	err = पढ़ोl_poll_समयout(
			ufs_phy->reg_pma + PHY_APB_ADDR(PHY_CDR_LOCK_STATUS),
			val, (val & PHY_CDR_LOCK_BIT), sleep_us, समयout_us);
	अगर (err)
		dev_err(ufs_phy->dev,
			"failed to get phy cdr lock acquisition %d\n", err);
out:
	वापस err;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_calibrate(काष्ठा phy *phy)
अणु
	काष्ठा samsung_ufs_phy *ufs_phy = get_samsung_ufs_phy(phy);
	काष्ठा samsung_ufs_phy_cfg **cfgs = ufs_phy->cfg;
	स्थिर काष्ठा samsung_ufs_phy_cfg *cfg;
	पूर्णांक err = 0;
	पूर्णांक i;

	अगर (unlikely(ufs_phy->ufs_phy_state < CFG_PRE_INIT ||
		     ufs_phy->ufs_phy_state >= CFG_TAG_MAX)) अणु
		dev_err(ufs_phy->dev, "invalid phy config index %d\n", ufs_phy->ufs_phy_state);
		वापस -EINVAL;
	पूर्ण

	cfg = cfgs[ufs_phy->ufs_phy_state];
	अगर (!cfg)
		जाओ out;

	क्रम_each_phy_cfg(cfg) अणु
		क्रम_each_phy_lane(ufs_phy, i) अणु
			samsung_ufs_phy_config(ufs_phy, cfg, i);
		पूर्ण
	पूर्ण

	अगर (ufs_phy->ufs_phy_state == CFG_POST_PWR_HS)
		err = samsung_ufs_phy_रुको_क्रम_lock_acq(phy);

	/**
	 * In Samsung ufshci, PHY need to be calibrated at dअगरferent
	 * stages / state मुख्यly beक्रमe Linkstartup, after Linkstartup,
	 * beक्रमe घातer mode change and after घातer mode change.
	 * Below state machine to make sure to calibrate PHY in each
	 * state. Here after configuring PHY in a given state, will
	 * change the state to next state so that next state phy
	 * calibration value can be programed
	 */
out:
	चयन (ufs_phy->ufs_phy_state) अणु
	हाल CFG_PRE_INIT:
		ufs_phy->ufs_phy_state = CFG_POST_INIT;
		अवरोध;
	हाल CFG_POST_INIT:
		ufs_phy->ufs_phy_state = CFG_PRE_PWR_HS;
		अवरोध;
	हाल CFG_PRE_PWR_HS:
		ufs_phy->ufs_phy_state = CFG_POST_PWR_HS;
		अवरोध;
	हाल CFG_POST_PWR_HS:
		/* Change back to INIT state */
		ufs_phy->ufs_phy_state = CFG_PRE_INIT;
		अवरोध;
	शेष:
		dev_err(ufs_phy->dev, "wrong state for phy calibration\n");
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_symbol_clk_init(काष्ठा samsung_ufs_phy *phy)
अणु
	पूर्णांक ret;

	phy->tx0_symbol_clk = devm_clk_get(phy->dev, "tx0_symbol_clk");
	अगर (IS_ERR(phy->tx0_symbol_clk)) अणु
		dev_err(phy->dev, "failed to get tx0_symbol_clk clock\n");
		वापस PTR_ERR(phy->tx0_symbol_clk);
	पूर्ण

	phy->rx0_symbol_clk = devm_clk_get(phy->dev, "rx0_symbol_clk");
	अगर (IS_ERR(phy->rx0_symbol_clk)) अणु
		dev_err(phy->dev, "failed to get rx0_symbol_clk clock\n");
		वापस PTR_ERR(phy->rx0_symbol_clk);
	पूर्ण

	phy->rx1_symbol_clk = devm_clk_get(phy->dev, "rx1_symbol_clk");
	अगर (IS_ERR(phy->rx1_symbol_clk)) अणु
		dev_err(phy->dev, "failed to get rx1_symbol_clk clock\n");
		वापस PTR_ERR(phy->rx1_symbol_clk);
	पूर्ण

	ret = clk_prepare_enable(phy->tx0_symbol_clk);
	अगर (ret) अणु
		dev_err(phy->dev, "%s: tx0_symbol_clk enable failed %d\n", __func__, ret);
		जाओ out;
	पूर्ण

	ret = clk_prepare_enable(phy->rx0_symbol_clk);
	अगर (ret) अणु
		dev_err(phy->dev, "%s: rx0_symbol_clk enable failed %d\n", __func__, ret);
		जाओ out_disable_tx0_clk;
	पूर्ण

	ret = clk_prepare_enable(phy->rx1_symbol_clk);
	अगर (ret) अणु
		dev_err(phy->dev, "%s: rx1_symbol_clk enable failed %d\n", __func__, ret);
		जाओ out_disable_rx0_clk;
	पूर्ण

	वापस 0;

out_disable_rx0_clk:
	clk_disable_unprepare(phy->rx0_symbol_clk);
out_disable_tx0_clk:
	clk_disable_unprepare(phy->tx0_symbol_clk);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_clks_init(काष्ठा samsung_ufs_phy *phy)
अणु
	पूर्णांक ret;

	phy->ref_clk = devm_clk_get(phy->dev, "ref_clk");
	अगर (IS_ERR(phy->ref_clk))
		dev_err(phy->dev, "failed to get ref_clk clock\n");

	ret = clk_prepare_enable(phy->ref_clk);
	अगर (ret) अणु
		dev_err(phy->dev, "%s: ref_clk enable failed %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	dev_dbg(phy->dev, "UFS MPHY ref_clk_rate = %ld\n", clk_get_rate(phy->ref_clk));

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);
	पूर्णांक ret;

	ss_phy->lane_cnt = phy->attrs.bus_width;
	ss_phy->ufs_phy_state = CFG_PRE_INIT;

	अगर (ss_phy->drvdata->has_symbol_clk) अणु
		ret = samsung_ufs_phy_symbol_clk_init(ss_phy);
		अगर (ret)
			dev_err(ss_phy->dev, "failed to set ufs phy symbol clocks\n");
	पूर्ण

	ret = samsung_ufs_phy_clks_init(ss_phy);
	अगर (ret)
		dev_err(ss_phy->dev, "failed to set ufs phy clocks\n");

	ret = samsung_ufs_phy_calibrate(phy);
	अगर (ret)
		dev_err(ss_phy->dev, "ufs phy calibration failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);

	samsung_ufs_phy_ctrl_isol(ss_phy, false);
	वापस 0;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);

	samsung_ufs_phy_ctrl_isol(ss_phy, true);
	वापस 0;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_set_mode(काष्ठा phy *generic_phy,
				    क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	काष्ठा samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(generic_phy);

	ss_phy->mode = PHY_MODE_INVALID;

	अगर (mode > 0)
		ss_phy->mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक samsung_ufs_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा samsung_ufs_phy *ss_phy = get_samsung_ufs_phy(phy);

	clk_disable_unprepare(ss_phy->ref_clk);

	अगर (ss_phy->drvdata->has_symbol_clk) अणु
		clk_disable_unprepare(ss_phy->tx0_symbol_clk);
		clk_disable_unprepare(ss_phy->rx0_symbol_clk);
		clk_disable_unprepare(ss_phy->rx1_symbol_clk);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops samsung_ufs_phy_ops = अणु
	.init		= samsung_ufs_phy_init,
	.निकास		= samsung_ufs_phy_निकास,
	.घातer_on	= samsung_ufs_phy_घातer_on,
	.घातer_off	= samsung_ufs_phy_घातer_off,
	.calibrate	= samsung_ufs_phy_calibrate,
	.set_mode	= samsung_ufs_phy_set_mode,
	.owner          = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id samsung_ufs_phy_match[];

अटल पूर्णांक samsung_ufs_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा samsung_ufs_phy *phy;
	काष्ठा phy *gen_phy;
	काष्ठा phy_provider *phy_provider;
	स्थिर काष्ठा samsung_ufs_phy_drvdata *drvdata;
	पूर्णांक err = 0;

	match = of_match_node(samsung_ufs_phy_match, dev->of_node);
	अगर (!match) अणु
		err = -EINVAL;
		dev_err(dev, "failed to get match_node\n");
		जाओ out;
	पूर्ण

	phy = devm_kzalloc(dev, माप(*phy), GFP_KERNEL);
	अगर (!phy) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	phy->reg_pma = devm_platक्रमm_ioremap_resource_byname(pdev, "phy-pma");
	अगर (IS_ERR(phy->reg_pma)) अणु
		err = PTR_ERR(phy->reg_pma);
		जाओ out;
	पूर्ण

	phy->reg_pmu = syscon_regmap_lookup_by_phandle(
				dev->of_node, "samsung,pmu-syscon");
	अगर (IS_ERR(phy->reg_pmu)) अणु
		err = PTR_ERR(phy->reg_pmu);
		dev_err(dev, "failed syscon remap for pmu\n");
		जाओ out;
	पूर्ण

	gen_phy = devm_phy_create(dev, शून्य, &samsung_ufs_phy_ops);
	अगर (IS_ERR(gen_phy)) अणु
		err = PTR_ERR(gen_phy);
		dev_err(dev, "failed to create PHY for ufs-phy\n");
		जाओ out;
	पूर्ण

	drvdata = match->data;
	phy->dev = dev;
	phy->drvdata = drvdata;
	phy->cfg = (काष्ठा samsung_ufs_phy_cfg **)drvdata->cfg;
	phy->isol = &drvdata->isol;
	phy->lane_cnt = PHY_DEF_LANE_CNT;

	phy_set_drvdata(gen_phy, phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		err = PTR_ERR(phy_provider);
		dev_err(dev, "failed to register phy-provider\n");
		जाओ out;
	पूर्ण
out:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id samsung_ufs_phy_match[] = अणु
	अणु
		.compatible = "samsung,exynos7-ufs-phy",
		.data = &exynos7_ufs_phy,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, samsung_ufs_phy_match);

अटल काष्ठा platक्रमm_driver samsung_ufs_phy_driver = अणु
	.probe  = samsung_ufs_phy_probe,
	.driver = अणु
		.name = "samsung-ufs-phy",
		.of_match_table = samsung_ufs_phy_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(samsung_ufs_phy_driver);
MODULE_DESCRIPTION("Samsung SoC UFS PHY Driver");
MODULE_AUTHOR("Seungwon Jeon <essuuj@gmail.com>");
MODULE_AUTHOR("Alim Akhtar <alim.akhtar@samsung.com>");
MODULE_LICENSE("GPL v2");
