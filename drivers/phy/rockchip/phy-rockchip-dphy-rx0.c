<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR MIT)
/*
 * Rockchip MIPI Synopsys DPHY RX0 driver
 *
 * Copyright (C) 2019 Collabora, Ltd.
 *
 * Based on:
 *
 * drivers/media/platक्रमm/rockchip/isp1/mipi_dphy_sy.c
 * in https://chromium.googlesource.com/chromiumos/third_party/kernel,
 * chromeos-4.4 branch.
 *
 * Copyright (C) 2017 Fuzhou Rockchip Electronics Co., Ltd.
 *   Jacob Chen <jacob2.chen@rock-chips.com>
 *   Shunqian Zheng <zhengsq@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#घोषणा RK3399_GRF_SOC_CON9		0x6224
#घोषणा RK3399_GRF_SOC_CON21		0x6254
#घोषणा RK3399_GRF_SOC_CON22		0x6258
#घोषणा RK3399_GRF_SOC_CON23		0x625c
#घोषणा RK3399_GRF_SOC_CON24		0x6260
#घोषणा RK3399_GRF_SOC_CON25		0x6264
#घोषणा RK3399_GRF_SOC_STATUS1		0xe2a4

#घोषणा CLOCK_LANE_HS_RX_CONTROL	0x34
#घोषणा LANE0_HS_RX_CONTROL		0x44
#घोषणा LANE1_HS_RX_CONTROL		0x54
#घोषणा LANE2_HS_RX_CONTROL		0x84
#घोषणा LANE3_HS_RX_CONTROL		0x94
#घोषणा LANES_THS_SETTLE_CONTROL	0x75
#घोषणा THS_SETTLE_COUNTER_THRESHOLD	0x04

काष्ठा hsfreq_range अणु
	u16 range_h;
	u8 cfg_bit;
पूर्ण;

अटल स्थिर काष्ठा hsfreq_range rk3399_mipidphy_hsfreq_ranges[] = अणु
	अणु   89, 0x00 पूर्ण, अणु   99, 0x10 पूर्ण, अणु  109, 0x20 पूर्ण, अणु  129, 0x01 पूर्ण,
	अणु  139, 0x11 पूर्ण, अणु  149, 0x21 पूर्ण, अणु  169, 0x02 पूर्ण, अणु  179, 0x12 पूर्ण,
	अणु  199, 0x22 पूर्ण, अणु  219, 0x03 पूर्ण, अणु  239, 0x13 पूर्ण, अणु  249, 0x23 पूर्ण,
	अणु  269, 0x04 पूर्ण, अणु  299, 0x14 पूर्ण, अणु  329, 0x05 पूर्ण, अणु  359, 0x15 पूर्ण,
	अणु  399, 0x25 पूर्ण, अणु  449, 0x06 पूर्ण, अणु  499, 0x16 पूर्ण, अणु  549, 0x07 पूर्ण,
	अणु  599, 0x17 पूर्ण, अणु  649, 0x08 पूर्ण, अणु  699, 0x18 पूर्ण, अणु  749, 0x09 पूर्ण,
	अणु  799, 0x19 पूर्ण, अणु  849, 0x29 पूर्ण, अणु  899, 0x39 पूर्ण, अणु  949, 0x0a पूर्ण,
	अणु  999, 0x1a पूर्ण, अणु 1049, 0x2a पूर्ण, अणु 1099, 0x3a पूर्ण, अणु 1149, 0x0b पूर्ण,
	अणु 1199, 0x1b पूर्ण, अणु 1249, 0x2b पूर्ण, अणु 1299, 0x3b पूर्ण, अणु 1349, 0x0c पूर्ण,
	अणु 1399, 0x1c पूर्ण, अणु 1449, 0x2c पूर्ण, अणु 1500, 0x3c पूर्ण
पूर्ण;

अटल स्थिर अक्षर * स्थिर rk3399_mipidphy_clks[] = अणु
	"dphy-ref",
	"dphy-cfg",
	"grf",
पूर्ण;

क्रमागत dphy_reg_id अणु
	GRF_DPHY_RX0_TURNDISABLE = 0,
	GRF_DPHY_RX0_FORCERXMODE,
	GRF_DPHY_RX0_FORCETXSTOPMODE,
	GRF_DPHY_RX0_ENABLE,
	GRF_DPHY_RX0_TESTCLR,
	GRF_DPHY_RX0_TESTCLK,
	GRF_DPHY_RX0_TESTEN,
	GRF_DPHY_RX0_TESTDIN,
	GRF_DPHY_RX0_TURNREQUEST,
	GRF_DPHY_RX0_TESTDOUT,
	GRF_DPHY_TX0_TURNDISABLE,
	GRF_DPHY_TX0_FORCERXMODE,
	GRF_DPHY_TX0_FORCETXSTOPMODE,
	GRF_DPHY_TX0_TURNREQUEST,
	GRF_DPHY_TX1RX1_TURNDISABLE,
	GRF_DPHY_TX1RX1_FORCERXMODE,
	GRF_DPHY_TX1RX1_FORCETXSTOPMODE,
	GRF_DPHY_TX1RX1_ENABLE,
	GRF_DPHY_TX1RX1_MASTERSLAVEZ,
	GRF_DPHY_TX1RX1_BASEसूची,
	GRF_DPHY_TX1RX1_ENABLECLK,
	GRF_DPHY_TX1RX1_TURNREQUEST,
	GRF_DPHY_RX1_SRC_SEL,
	/* rk3288 only */
	GRF_CON_DISABLE_ISP,
	GRF_CON_ISP_DPHY_SEL,
	GRF_DSI_CSI_TESTBUS_SEL,
	GRF_DVP_V18SEL,
	/* below is क्रम rk3399 only */
	GRF_DPHY_RX0_CLK_INV_SEL,
	GRF_DPHY_RX1_CLK_INV_SEL,
पूर्ण;

काष्ठा dphy_reg अणु
	u16 offset;
	u8 mask;
	u8 shअगरt;
पूर्ण;

#घोषणा PHY_REG(_offset, _width, _shअगरt) \
	अणु .offset = _offset, .mask = BIT(_width) - 1, .shअगरt = _shअगरt, पूर्ण

अटल स्थिर काष्ठा dphy_reg rk3399_grf_dphy_regs[] = अणु
	[GRF_DPHY_RX0_TURNREQUEST] = PHY_REG(RK3399_GRF_SOC_CON9, 4, 0),
	[GRF_DPHY_RX0_CLK_INV_SEL] = PHY_REG(RK3399_GRF_SOC_CON9, 1, 10),
	[GRF_DPHY_RX1_CLK_INV_SEL] = PHY_REG(RK3399_GRF_SOC_CON9, 1, 11),
	[GRF_DPHY_RX0_ENABLE] = PHY_REG(RK3399_GRF_SOC_CON21, 4, 0),
	[GRF_DPHY_RX0_FORCERXMODE] = PHY_REG(RK3399_GRF_SOC_CON21, 4, 4),
	[GRF_DPHY_RX0_FORCETXSTOPMODE] = PHY_REG(RK3399_GRF_SOC_CON21, 4, 8),
	[GRF_DPHY_RX0_TURNDISABLE] = PHY_REG(RK3399_GRF_SOC_CON21, 4, 12),
	[GRF_DPHY_TX0_FORCERXMODE] = PHY_REG(RK3399_GRF_SOC_CON22, 4, 0),
	[GRF_DPHY_TX0_FORCETXSTOPMODE] = PHY_REG(RK3399_GRF_SOC_CON22, 4, 4),
	[GRF_DPHY_TX0_TURNDISABLE] = PHY_REG(RK3399_GRF_SOC_CON22, 4, 8),
	[GRF_DPHY_TX0_TURNREQUEST] = PHY_REG(RK3399_GRF_SOC_CON22, 4, 12),
	[GRF_DPHY_TX1RX1_ENABLE] = PHY_REG(RK3399_GRF_SOC_CON23, 4, 0),
	[GRF_DPHY_TX1RX1_FORCERXMODE] = PHY_REG(RK3399_GRF_SOC_CON23, 4, 4),
	[GRF_DPHY_TX1RX1_FORCETXSTOPMODE] = PHY_REG(RK3399_GRF_SOC_CON23, 4, 8),
	[GRF_DPHY_TX1RX1_TURNDISABLE] = PHY_REG(RK3399_GRF_SOC_CON23, 4, 12),
	[GRF_DPHY_TX1RX1_TURNREQUEST] = PHY_REG(RK3399_GRF_SOC_CON24, 4, 0),
	[GRF_DPHY_RX1_SRC_SEL] = PHY_REG(RK3399_GRF_SOC_CON24, 1, 4),
	[GRF_DPHY_TX1RX1_BASEसूची] = PHY_REG(RK3399_GRF_SOC_CON24, 1, 5),
	[GRF_DPHY_TX1RX1_ENABLECLK] = PHY_REG(RK3399_GRF_SOC_CON24, 1, 6),
	[GRF_DPHY_TX1RX1_MASTERSLAVEZ] = PHY_REG(RK3399_GRF_SOC_CON24, 1, 7),
	[GRF_DPHY_RX0_TESTDIN] = PHY_REG(RK3399_GRF_SOC_CON25, 8, 0),
	[GRF_DPHY_RX0_TESTEN] = PHY_REG(RK3399_GRF_SOC_CON25, 1, 8),
	[GRF_DPHY_RX0_TESTCLK] = PHY_REG(RK3399_GRF_SOC_CON25, 1, 9),
	[GRF_DPHY_RX0_TESTCLR] = PHY_REG(RK3399_GRF_SOC_CON25, 1, 10),
	[GRF_DPHY_RX0_TESTDOUT] = PHY_REG(RK3399_GRF_SOC_STATUS1, 8, 0),
पूर्ण;

काष्ठा rk_dphy_drv_data अणु
	स्थिर अक्षर * स्थिर *clks;
	अचिन्हित पूर्णांक num_clks;
	स्थिर काष्ठा hsfreq_range *hsfreq_ranges;
	अचिन्हित पूर्णांक num_hsfreq_ranges;
	स्थिर काष्ठा dphy_reg *regs;
पूर्ण;

काष्ठा rk_dphy अणु
	काष्ठा device *dev;
	काष्ठा regmap *grf;
	काष्ठा clk_bulk_data *clks;

	स्थिर काष्ठा rk_dphy_drv_data *drv_data;
	काष्ठा phy_configure_opts_mipi_dphy config;

	u8 hsfreq;
पूर्ण;

अटल अंतरभूत व्योम rk_dphy_ग_लिखो_grf(काष्ठा rk_dphy *priv,
				     अचिन्हित पूर्णांक index, u8 value)
अणु
	स्थिर काष्ठा dphy_reg *reg = &priv->drv_data->regs[index];
	/* Update high word */
	अचिन्हित पूर्णांक val = (value << reg->shअगरt) |
			   (reg->mask << (reg->shअगरt + 16));

	अगर (WARN_ON(!reg->offset))
		वापस;
	regmap_ग_लिखो(priv->grf, reg->offset, val);
पूर्ण

अटल व्योम rk_dphy_ग_लिखो(काष्ठा rk_dphy *priv, u8 test_code, u8 test_data)
अणु
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTDIN, test_code);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTEN, 1);
	/*
	 * With the falling edge on TESTCLK, the TESTDIN[7:0] संकेत content
	 * is latched पूर्णांकernally as the current test code. Test data is
	 * programmed पूर्णांकernally by rising edge on TESTCLK.
	 * This code assumes that TESTCLK is alपढ़ोy 1.
	 */
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTCLK, 0);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTEN, 0);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTDIN, test_data);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTCLK, 1);
पूर्ण

अटल व्योम rk_dphy_enable(काष्ठा rk_dphy *priv)
अणु
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_FORCERXMODE, 0);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_FORCETXSTOPMODE, 0);

	/* Disable lane turn around, which is ignored in receive mode */
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TURNREQUEST, 0);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TURNDISABLE, 0xf);

	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_ENABLE,
			  GENMASK(priv->config.lanes - 1, 0));

	/* dphy start */
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTCLK, 1);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTCLR, 1);
	usleep_range(100, 150);
	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_TESTCLR, 0);
	usleep_range(100, 150);

	/* set घड़ी lane */
	/* HS hsfreq_range & lane 0  settle bypass */
	rk_dphy_ग_लिखो(priv, CLOCK_LANE_HS_RX_CONTROL, 0);
	/* HS RX Control of lane0 */
	rk_dphy_ग_लिखो(priv, LANE0_HS_RX_CONTROL, priv->hsfreq << 1);
	/* HS RX Control of lane1 */
	rk_dphy_ग_लिखो(priv, LANE1_HS_RX_CONTROL, priv->hsfreq << 1);
	/* HS RX Control of lane2 */
	rk_dphy_ग_लिखो(priv, LANE2_HS_RX_CONTROL, priv->hsfreq << 1);
	/* HS RX Control of lane3 */
	rk_dphy_ग_लिखो(priv, LANE3_HS_RX_CONTROL, priv->hsfreq << 1);
	/* HS RX Data Lanes Settle State Time Control */
	rk_dphy_ग_लिखो(priv, LANES_THS_SETTLE_CONTROL,
		      THS_SETTLE_COUNTER_THRESHOLD);

	/* Normal operation */
	rk_dphy_ग_लिखो(priv, 0x0, 0);
पूर्ण

अटल पूर्णांक rk_dphy_configure(काष्ठा phy *phy, जोड़ phy_configure_opts *opts)
अणु
	काष्ठा rk_dphy *priv = phy_get_drvdata(phy);
	स्थिर काष्ठा rk_dphy_drv_data *drv_data = priv->drv_data;
	काष्ठा phy_configure_opts_mipi_dphy *config = &opts->mipi_dphy;
	अचिन्हित पूर्णांक hsfreq = 0;
	अचिन्हित पूर्णांक i;
	u64 data_rate_mbps;
	पूर्णांक ret;

	/* pass with phy_mipi_dphy_get_शेष_config (with pixel rate?) */
	ret = phy_mipi_dphy_config_validate(config);
	अगर (ret)
		वापस ret;

	data_rate_mbps = भाग_u64(config->hs_clk_rate, 1000 * 1000);

	dev_dbg(priv->dev, "lanes %d - data_rate_mbps %llu\n",
		config->lanes, data_rate_mbps);
	क्रम (i = 0; i < drv_data->num_hsfreq_ranges; i++) अणु
		अगर (drv_data->hsfreq_ranges[i].range_h >= data_rate_mbps) अणु
			hsfreq = drv_data->hsfreq_ranges[i].cfg_bit;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!hsfreq)
		वापस -EINVAL;

	priv->hsfreq = hsfreq;
	priv->config = *config;
	वापस 0;
पूर्ण

अटल पूर्णांक rk_dphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा rk_dphy *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = clk_bulk_enable(priv->drv_data->num_clks, priv->clks);
	अगर (ret)
		वापस ret;

	rk_dphy_enable(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक rk_dphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा rk_dphy *priv = phy_get_drvdata(phy);

	rk_dphy_ग_लिखो_grf(priv, GRF_DPHY_RX0_ENABLE, 0);
	clk_bulk_disable(priv->drv_data->num_clks, priv->clks);
	वापस 0;
पूर्ण

अटल पूर्णांक rk_dphy_init(काष्ठा phy *phy)
अणु
	काष्ठा rk_dphy *priv = phy_get_drvdata(phy);

	वापस clk_bulk_prepare(priv->drv_data->num_clks, priv->clks);
पूर्ण

अटल पूर्णांक rk_dphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा rk_dphy *priv = phy_get_drvdata(phy);

	clk_bulk_unprepare(priv->drv_data->num_clks, priv->clks);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops rk_dphy_ops = अणु
	.घातer_on	= rk_dphy_घातer_on,
	.घातer_off	= rk_dphy_घातer_off,
	.init		= rk_dphy_init,
	.निकास		= rk_dphy_निकास,
	.configure	= rk_dphy_configure,
	.owner		= THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा rk_dphy_drv_data rk3399_mipidphy_drv_data = अणु
	.clks = rk3399_mipidphy_clks,
	.num_clks = ARRAY_SIZE(rk3399_mipidphy_clks),
	.hsfreq_ranges = rk3399_mipidphy_hsfreq_ranges,
	.num_hsfreq_ranges = ARRAY_SIZE(rk3399_mipidphy_hsfreq_ranges),
	.regs = rk3399_grf_dphy_regs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rk_dphy_dt_ids[] = अणु
	अणु
		.compatible = "rockchip,rk3399-mipi-dphy-rx0",
		.data = &rk3399_mipidphy_drv_data,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rk_dphy_dt_ids);

अटल पूर्णांक rk_dphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा rk_dphy_drv_data *drv_data;
	काष्ठा phy_provider *phy_provider;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा rk_dphy *priv;
	काष्ठा phy *phy;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!dev->parent || !dev->parent->of_node)
		वापस -ENODEV;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	priv->dev = dev;

	priv->grf = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(priv->grf)) अणु
		dev_err(dev, "Can't find GRF syscon\n");
		वापस -ENODEV;
	पूर्ण

	of_id = of_match_device(rk_dphy_dt_ids, dev);
	अगर (!of_id)
		वापस -EINVAL;

	drv_data = of_id->data;
	priv->drv_data = drv_data;
	priv->clks = devm_kसुस्मृति(&pdev->dev, drv_data->num_clks,
				  माप(*priv->clks), GFP_KERNEL);
	अगर (!priv->clks)
		वापस -ENOMEM;
	क्रम (i = 0; i < drv_data->num_clks; i++)
		priv->clks[i].id = drv_data->clks[i];
	ret = devm_clk_bulk_get(&pdev->dev, drv_data->num_clks, priv->clks);
	अगर (ret)
		वापस ret;

	phy = devm_phy_create(dev, np, &rk_dphy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "failed to create phy\n");
		वापस PTR_ERR(phy);
	पूर्ण
	phy_set_drvdata(phy, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver rk_dphy_driver = अणु
	.probe = rk_dphy_probe,
	.driver = अणु
		.name	= "rockchip-mipi-dphy-rx0",
		.of_match_table = rk_dphy_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rk_dphy_driver);

MODULE_AUTHOR("Ezequiel Garcia <ezequiel@collabora.com>");
MODULE_DESCRIPTION("Rockchip MIPI Synopsys DPHY RX0 driver");
MODULE_LICENSE("Dual MIT/GPL");
