<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip DP PHY driver
 *
 * Copyright (C) 2016 FuZhou Rockchip Co., Ltd.
 * Author: Yakir Yang <ykk@@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा GRF_SOC_CON12                           0x0274

#घोषणा GRF_EDP_REF_CLK_SEL_INTER_HIWORD_MASK   BIT(20)
#घोषणा GRF_EDP_REF_CLK_SEL_INTER               BIT(4)

#घोषणा GRF_EDP_PHY_SIDDQ_HIWORD_MASK           BIT(21)
#घोषणा GRF_EDP_PHY_SIDDQ_ON                    0
#घोषणा GRF_EDP_PHY_SIDDQ_OFF                   BIT(5)

काष्ठा rockchip_dp_phy अणु
	काष्ठा device  *dev;
	काष्ठा regmap  *grf;
	काष्ठा clk     *phy_24m;
पूर्ण;

अटल पूर्णांक rockchip_set_phy_state(काष्ठा phy *phy, bool enable)
अणु
	काष्ठा rockchip_dp_phy *dp = phy_get_drvdata(phy);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = regmap_ग_लिखो(dp->grf, GRF_SOC_CON12,
				   GRF_EDP_PHY_SIDDQ_HIWORD_MASK |
				   GRF_EDP_PHY_SIDDQ_ON);
		अगर (ret < 0) अणु
			dev_err(dp->dev, "Can't enable PHY power %d\n", ret);
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(dp->phy_24m);
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(dp->phy_24m);

		ret = regmap_ग_लिखो(dp->grf, GRF_SOC_CON12,
				   GRF_EDP_PHY_SIDDQ_HIWORD_MASK |
				   GRF_EDP_PHY_SIDDQ_OFF);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_dp_phy_घातer_on(काष्ठा phy *phy)
अणु
	वापस rockchip_set_phy_state(phy, true);
पूर्ण

अटल पूर्णांक rockchip_dp_phy_घातer_off(काष्ठा phy *phy)
अणु
	वापस rockchip_set_phy_state(phy, false);
पूर्ण

अटल स्थिर काष्ठा phy_ops rockchip_dp_phy_ops = अणु
	.घातer_on	= rockchip_dp_phy_घातer_on,
	.घातer_off	= rockchip_dp_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक rockchip_dp_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा phy_provider *phy_provider;
	काष्ठा rockchip_dp_phy *dp;
	काष्ठा phy *phy;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	अगर (!dev->parent || !dev->parent->of_node)
		वापस -ENODEV;

	dp = devm_kzalloc(dev, माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	dp->dev = dev;

	dp->phy_24m = devm_clk_get(dev, "24m");
	अगर (IS_ERR(dp->phy_24m)) अणु
		dev_err(dev, "cannot get clock 24m\n");
		वापस PTR_ERR(dp->phy_24m);
	पूर्ण

	ret = clk_set_rate(dp->phy_24m, 24000000);
	अगर (ret < 0) अणु
		dev_err(dp->dev, "cannot set clock phy_24m %d\n", ret);
		वापस ret;
	पूर्ण

	dp->grf = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(dp->grf)) अणु
		dev_err(dev, "rk3288-dp needs the General Register Files syscon\n");
		वापस PTR_ERR(dp->grf);
	पूर्ण

	ret = regmap_ग_लिखो(dp->grf, GRF_SOC_CON12, GRF_EDP_REF_CLK_SEL_INTER |
			   GRF_EDP_REF_CLK_SEL_INTER_HIWORD_MASK);
	अगर (ret != 0) अणु
		dev_err(dp->dev, "Could not config GRF edp ref clk: %d\n", ret);
		वापस ret;
	पूर्ण

	phy = devm_phy_create(dev, np, &rockchip_dp_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create phy\n");
		वापस PTR_ERR(phy);
	पूर्ण
	phy_set_drvdata(phy, dp);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_dp_phy_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk3288-dp-phy" पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_dp_phy_dt_ids);

अटल काष्ठा platक्रमm_driver rockchip_dp_phy_driver = अणु
	.probe		= rockchip_dp_phy_probe,
	.driver		= अणु
		.name	= "rockchip-dp-phy",
		.of_match_table = rockchip_dp_phy_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_dp_phy_driver);

MODULE_AUTHOR("Yakir Yang <ykk@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip DP PHY driver");
MODULE_LICENSE("GPL v2");
