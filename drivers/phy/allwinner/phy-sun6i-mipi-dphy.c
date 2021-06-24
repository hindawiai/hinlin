<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2016 Allwinnertech Co., Ltd.
 * Copyright (C) 2017-2018 Bootlin
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>

#घोषणा SUN6I_DPHY_GCTL_REG		0x00
#घोषणा SUN6I_DPHY_GCTL_LANE_NUM(n)		((((n) - 1) & 3) << 4)
#घोषणा SUN6I_DPHY_GCTL_EN			BIT(0)

#घोषणा SUN6I_DPHY_TX_CTL_REG		0x04
#घोषणा SUN6I_DPHY_TX_CTL_HS_TX_CLK_CONT	BIT(28)

#घोषणा SUN6I_DPHY_TX_TIME0_REG		0x10
#घोषणा SUN6I_DPHY_TX_TIME0_HS_TRAIL(n)		(((n) & 0xff) << 24)
#घोषणा SUN6I_DPHY_TX_TIME0_HS_PREPARE(n)	(((n) & 0xff) << 16)
#घोषणा SUN6I_DPHY_TX_TIME0_LP_CLK_DIV(n)	((n) & 0xff)

#घोषणा SUN6I_DPHY_TX_TIME1_REG		0x14
#घोषणा SUN6I_DPHY_TX_TIME1_CLK_POST(n)		(((n) & 0xff) << 24)
#घोषणा SUN6I_DPHY_TX_TIME1_CLK_PRE(n)		(((n) & 0xff) << 16)
#घोषणा SUN6I_DPHY_TX_TIME1_CLK_ZERO(n)		(((n) & 0xff) << 8)
#घोषणा SUN6I_DPHY_TX_TIME1_CLK_PREPARE(n)	((n) & 0xff)

#घोषणा SUN6I_DPHY_TX_TIME2_REG		0x18
#घोषणा SUN6I_DPHY_TX_TIME2_CLK_TRAIL(n)	((n) & 0xff)

#घोषणा SUN6I_DPHY_TX_TIME3_REG		0x1c

#घोषणा SUN6I_DPHY_TX_TIME4_REG		0x20
#घोषणा SUN6I_DPHY_TX_TIME4_HS_TX_ANA1(n)	(((n) & 0xff) << 8)
#घोषणा SUN6I_DPHY_TX_TIME4_HS_TX_ANA0(n)	((n) & 0xff)

#घोषणा SUN6I_DPHY_ANA0_REG		0x4c
#घोषणा SUN6I_DPHY_ANA0_REG_PWS			BIT(31)
#घोषणा SUN6I_DPHY_ANA0_REG_DMPC		BIT(28)
#घोषणा SUN6I_DPHY_ANA0_REG_DMPD(n)		(((n) & 0xf) << 24)
#घोषणा SUN6I_DPHY_ANA0_REG_SLV(n)		(((n) & 7) << 12)
#घोषणा SUN6I_DPHY_ANA0_REG_DEN(n)		(((n) & 0xf) << 8)

#घोषणा SUN6I_DPHY_ANA1_REG		0x50
#घोषणा SUN6I_DPHY_ANA1_REG_VTTMODE		BIT(31)
#घोषणा SUN6I_DPHY_ANA1_REG_CSMPS(n)		(((n) & 3) << 28)
#घोषणा SUN6I_DPHY_ANA1_REG_SVTT(n)		(((n) & 0xf) << 24)

#घोषणा SUN6I_DPHY_ANA2_REG		0x54
#घोषणा SUN6I_DPHY_ANA2_EN_P2S_CPU(n)		(((n) & 0xf) << 24)
#घोषणा SUN6I_DPHY_ANA2_EN_P2S_CPU_MASK		GENMASK(27, 24)
#घोषणा SUN6I_DPHY_ANA2_EN_CK_CPU		BIT(4)
#घोषणा SUN6I_DPHY_ANA2_REG_ENIB		BIT(1)

#घोषणा SUN6I_DPHY_ANA3_REG		0x58
#घोषणा SUN6I_DPHY_ANA3_EN_VTTD(n)		(((n) & 0xf) << 28)
#घोषणा SUN6I_DPHY_ANA3_EN_VTTD_MASK		GENMASK(31, 28)
#घोषणा SUN6I_DPHY_ANA3_EN_VTTC			BIT(27)
#घोषणा SUN6I_DPHY_ANA3_EN_DIV			BIT(26)
#घोषणा SUN6I_DPHY_ANA3_EN_LDOC			BIT(25)
#घोषणा SUN6I_DPHY_ANA3_EN_LDOD			BIT(24)
#घोषणा SUN6I_DPHY_ANA3_EN_LDOR			BIT(18)

#घोषणा SUN6I_DPHY_ANA4_REG		0x5c
#घोषणा SUN6I_DPHY_ANA4_REG_DMPLVC		BIT(24)
#घोषणा SUN6I_DPHY_ANA4_REG_DMPLVD(n)		(((n) & 0xf) << 20)
#घोषणा SUN6I_DPHY_ANA4_REG_CKDV(n)		(((n) & 0x1f) << 12)
#घोषणा SUN6I_DPHY_ANA4_REG_TMSC(n)		(((n) & 3) << 10)
#घोषणा SUN6I_DPHY_ANA4_REG_TMSD(n)		(((n) & 3) << 8)
#घोषणा SUN6I_DPHY_ANA4_REG_TXDNSC(n)		(((n) & 3) << 6)
#घोषणा SUN6I_DPHY_ANA4_REG_TXDNSD(n)		(((n) & 3) << 4)
#घोषणा SUN6I_DPHY_ANA4_REG_TXPUSC(n)		(((n) & 3) << 2)
#घोषणा SUN6I_DPHY_ANA4_REG_TXPUSD(n)		((n) & 3)

#घोषणा SUN6I_DPHY_DBG5_REG		0xf4

काष्ठा sun6i_dphy अणु
	काष्ठा clk				*bus_clk;
	काष्ठा clk				*mod_clk;
	काष्ठा regmap				*regs;
	काष्ठा reset_control			*reset;

	काष्ठा phy				*phy;
	काष्ठा phy_configure_opts_mipi_dphy	config;
पूर्ण;

अटल पूर्णांक sun6i_dphy_init(काष्ठा phy *phy)
अणु
	काष्ठा sun6i_dphy *dphy = phy_get_drvdata(phy);

	reset_control_deनिश्चित(dphy->reset);
	clk_prepare_enable(dphy->mod_clk);
	clk_set_rate_exclusive(dphy->mod_clk, 150000000);

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dphy_configure(काष्ठा phy *phy, जोड़ phy_configure_opts *opts)
अणु
	काष्ठा sun6i_dphy *dphy = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = phy_mipi_dphy_config_validate(&opts->mipi_dphy);
	अगर (ret)
		वापस ret;

	स_नकल(&dphy->config, opts, माप(dphy->config));

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा sun6i_dphy *dphy = phy_get_drvdata(phy);
	u8 lanes_mask = GENMASK(dphy->config.lanes - 1, 0);

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_TX_CTL_REG,
		     SUN6I_DPHY_TX_CTL_HS_TX_CLK_CONT);

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_TX_TIME0_REG,
		     SUN6I_DPHY_TX_TIME0_LP_CLK_DIV(14) |
		     SUN6I_DPHY_TX_TIME0_HS_PREPARE(6) |
		     SUN6I_DPHY_TX_TIME0_HS_TRAIL(10));

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_TX_TIME1_REG,
		     SUN6I_DPHY_TX_TIME1_CLK_PREPARE(7) |
		     SUN6I_DPHY_TX_TIME1_CLK_ZERO(50) |
		     SUN6I_DPHY_TX_TIME1_CLK_PRE(3) |
		     SUN6I_DPHY_TX_TIME1_CLK_POST(10));

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_TX_TIME2_REG,
		     SUN6I_DPHY_TX_TIME2_CLK_TRAIL(30));

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_TX_TIME3_REG, 0);

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_TX_TIME4_REG,
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA0(3) |
		     SUN6I_DPHY_TX_TIME4_HS_TX_ANA1(3));

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_GCTL_REG,
		     SUN6I_DPHY_GCTL_LANE_NUM(dphy->config.lanes) |
		     SUN6I_DPHY_GCTL_EN);

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_ANA0_REG,
		     SUN6I_DPHY_ANA0_REG_PWS |
		     SUN6I_DPHY_ANA0_REG_DMPC |
		     SUN6I_DPHY_ANA0_REG_SLV(7) |
		     SUN6I_DPHY_ANA0_REG_DMPD(lanes_mask) |
		     SUN6I_DPHY_ANA0_REG_DEN(lanes_mask));

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_ANA1_REG,
		     SUN6I_DPHY_ANA1_REG_CSMPS(1) |
		     SUN6I_DPHY_ANA1_REG_SVTT(7));

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_ANA4_REG,
		     SUN6I_DPHY_ANA4_REG_CKDV(1) |
		     SUN6I_DPHY_ANA4_REG_TMSC(1) |
		     SUN6I_DPHY_ANA4_REG_TMSD(1) |
		     SUN6I_DPHY_ANA4_REG_TXDNSC(1) |
		     SUN6I_DPHY_ANA4_REG_TXDNSD(1) |
		     SUN6I_DPHY_ANA4_REG_TXPUSC(1) |
		     SUN6I_DPHY_ANA4_REG_TXPUSD(1) |
		     SUN6I_DPHY_ANA4_REG_DMPLVC |
		     SUN6I_DPHY_ANA4_REG_DMPLVD(lanes_mask));

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_ANA2_REG,
		     SUN6I_DPHY_ANA2_REG_ENIB);
	udelay(5);

	regmap_ग_लिखो(dphy->regs, SUN6I_DPHY_ANA3_REG,
		     SUN6I_DPHY_ANA3_EN_LDOR |
		     SUN6I_DPHY_ANA3_EN_LDOC |
		     SUN6I_DPHY_ANA3_EN_LDOD);
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA3_REG,
			   SUN6I_DPHY_ANA3_EN_VTTC |
			   SUN6I_DPHY_ANA3_EN_VTTD_MASK,
			   SUN6I_DPHY_ANA3_EN_VTTC |
			   SUN6I_DPHY_ANA3_EN_VTTD(lanes_mask));
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA3_REG,
			   SUN6I_DPHY_ANA3_EN_DIV,
			   SUN6I_DPHY_ANA3_EN_DIV);
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA2_REG,
			   SUN6I_DPHY_ANA2_EN_CK_CPU,
			   SUN6I_DPHY_ANA2_EN_CK_CPU);
	udelay(1);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA1_REG,
			   SUN6I_DPHY_ANA1_REG_VTTMODE,
			   SUN6I_DPHY_ANA1_REG_VTTMODE);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA2_REG,
			   SUN6I_DPHY_ANA2_EN_P2S_CPU_MASK,
			   SUN6I_DPHY_ANA2_EN_P2S_CPU(lanes_mask));

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा sun6i_dphy *dphy = phy_get_drvdata(phy);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA1_REG,
			   SUN6I_DPHY_ANA1_REG_VTTMODE, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dphy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा sun6i_dphy *dphy = phy_get_drvdata(phy);

	clk_rate_exclusive_put(dphy->mod_clk);
	clk_disable_unprepare(dphy->mod_clk);
	reset_control_निश्चित(dphy->reset);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा phy_ops sun6i_dphy_ops = अणु
	.configure	= sun6i_dphy_configure,
	.घातer_on	= sun6i_dphy_घातer_on,
	.घातer_off	= sun6i_dphy_घातer_off,
	.init		= sun6i_dphy_init,
	.निकास		= sun6i_dphy_निकास,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun6i_dphy_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= SUN6I_DPHY_DBG5_REG,
	.name		= "mipi-dphy",
पूर्ण;

अटल पूर्णांक sun6i_dphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा sun6i_dphy *dphy;
	व्योम __iomem *regs;

	dphy = devm_kzalloc(&pdev->dev, माप(*dphy), GFP_KERNEL);
	अगर (!dphy)
		वापस -ENOMEM;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs)) अणु
		dev_err(&pdev->dev, "Couldn't map the DPHY encoder registers\n");
		वापस PTR_ERR(regs);
	पूर्ण

	dphy->regs = devm_regmap_init_mmio_clk(&pdev->dev, "bus",
					       regs, &sun6i_dphy_regmap_config);
	अगर (IS_ERR(dphy->regs)) अणु
		dev_err(&pdev->dev, "Couldn't create the DPHY encoder regmap\n");
		वापस PTR_ERR(dphy->regs);
	पूर्ण

	dphy->reset = devm_reset_control_get_shared(&pdev->dev, शून्य);
	अगर (IS_ERR(dphy->reset)) अणु
		dev_err(&pdev->dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(dphy->reset);
	पूर्ण

	dphy->mod_clk = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(dphy->mod_clk)) अणु
		dev_err(&pdev->dev, "Couldn't get the DPHY mod clock\n");
		वापस PTR_ERR(dphy->mod_clk);
	पूर्ण

	dphy->phy = devm_phy_create(&pdev->dev, शून्य, &sun6i_dphy_ops);
	अगर (IS_ERR(dphy->phy)) अणु
		dev_err(&pdev->dev, "failed to create PHY\n");
		वापस PTR_ERR(dphy->phy);
	पूर्ण

	phy_set_drvdata(dphy->phy, dphy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id sun6i_dphy_of_table[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-mipi-dphy" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_dphy_of_table);

अटल काष्ठा platक्रमm_driver sun6i_dphy_platक्रमm_driver = अणु
	.probe		= sun6i_dphy_probe,
	.driver		= अणु
		.name		= "sun6i-mipi-dphy",
		.of_match_table	= sun6i_dphy_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun6i_dphy_platक्रमm_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@bootlin>");
MODULE_DESCRIPTION("Allwinner A31 MIPI D-PHY Driver");
MODULE_LICENSE("GPL");
