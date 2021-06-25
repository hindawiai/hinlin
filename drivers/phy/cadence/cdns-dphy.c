<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright: 2017-2018 Cadence Design Systems, Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश <linux/phy/phy.h>
#समावेश <linux/phy/phy-mipi-dphy.h>

#घोषणा REG_WAKEUP_TIME_NS		800
#घोषणा DPHY_PLL_RATE_HZ		108000000

/* DPHY रेजिस्टरs */
#घोषणा DPHY_PMA_CMN(reg)		(reg)
#घोषणा DPHY_PMA_LCLK(reg)		(0x100 + (reg))
#घोषणा DPHY_PMA_LDATA(lane, reg)	(0x200 + ((lane) * 0x100) + (reg))
#घोषणा DPHY_PMA_RCLK(reg)		(0x600 + (reg))
#घोषणा DPHY_PMA_RDATA(lane, reg)	(0x700 + ((lane) * 0x100) + (reg))
#घोषणा DPHY_PCS(reg)			(0xb00 + (reg))

#घोषणा DPHY_CMN_SSM			DPHY_PMA_CMN(0x20)
#घोषणा DPHY_CMN_SSM_EN			BIT(0)
#घोषणा DPHY_CMN_TX_MODE_EN		BIT(9)

#घोषणा DPHY_CMN_PWM			DPHY_PMA_CMN(0x40)
#घोषणा DPHY_CMN_PWM_DIV(x)		((x) << 20)
#घोषणा DPHY_CMN_PWM_LOW(x)		((x) << 10)
#घोषणा DPHY_CMN_PWM_HIGH(x)		(x)

#घोषणा DPHY_CMN_FBDIV			DPHY_PMA_CMN(0x4c)
#घोषणा DPHY_CMN_FBDIV_VAL(low, high)	(((high) << 11) | ((low) << 22))
#घोषणा DPHY_CMN_FBDIV_FROM_REG		(BIT(10) | BIT(21))

#घोषणा DPHY_CMN_OPIPDIV		DPHY_PMA_CMN(0x50)
#घोषणा DPHY_CMN_IPDIV_FROM_REG		BIT(0)
#घोषणा DPHY_CMN_IPDIV(x)		((x) << 1)
#घोषणा DPHY_CMN_OPDIV_FROM_REG		BIT(6)
#घोषणा DPHY_CMN_OPDIV(x)		((x) << 7)

#घोषणा DPHY_PSM_CFG			DPHY_PCS(0x4)
#घोषणा DPHY_PSM_CFG_FROM_REG		BIT(0)
#घोषणा DPHY_PSM_CLK_DIV(x)		((x) << 1)

#घोषणा DSI_HBP_FRAME_OVERHEAD		12
#घोषणा DSI_HSA_FRAME_OVERHEAD		14
#घोषणा DSI_HFP_FRAME_OVERHEAD		6
#घोषणा DSI_HSS_VSS_VSE_FRAME_OVERHEAD	4
#घोषणा DSI_BLANKING_FRAME_OVERHEAD	6
#घोषणा DSI_शून्य_FRAME_OVERHEAD		6
#घोषणा DSI_EOT_PKT_SIZE		4

काष्ठा cdns_dphy_cfg अणु
	u8 pll_ipभाग;
	u8 pll_opभाग;
	u16 pll_fbभाग;
	अचिन्हित पूर्णांक nlanes;
पूर्ण;

क्रमागत cdns_dphy_clk_lane_cfg अणु
	DPHY_CLK_CFG_LEFT_DRIVES_ALL = 0,
	DPHY_CLK_CFG_LEFT_DRIVES_RIGHT = 1,
	DPHY_CLK_CFG_LEFT_DRIVES_LEFT = 2,
	DPHY_CLK_CFG_RIGHT_DRIVES_ALL = 3,
पूर्ण;

काष्ठा cdns_dphy;
काष्ठा cdns_dphy_ops अणु
	पूर्णांक (*probe)(काष्ठा cdns_dphy *dphy);
	व्योम (*हटाओ)(काष्ठा cdns_dphy *dphy);
	व्योम (*set_psm_भाग)(काष्ठा cdns_dphy *dphy, u8 भाग);
	व्योम (*set_clk_lane_cfg)(काष्ठा cdns_dphy *dphy,
				 क्रमागत cdns_dphy_clk_lane_cfg cfg);
	व्योम (*set_pll_cfg)(काष्ठा cdns_dphy *dphy,
			    स्थिर काष्ठा cdns_dphy_cfg *cfg);
	अचिन्हित दीर्घ (*get_wakeup_समय_ns)(काष्ठा cdns_dphy *dphy);
पूर्ण;

काष्ठा cdns_dphy अणु
	काष्ठा cdns_dphy_cfg cfg;
	व्योम __iomem *regs;
	काष्ठा clk *psm_clk;
	काष्ठा clk *pll_ref_clk;
	स्थिर काष्ठा cdns_dphy_ops *ops;
	काष्ठा phy *phy;
पूर्ण;

अटल पूर्णांक cdns_dsi_get_dphy_pll_cfg(काष्ठा cdns_dphy *dphy,
				     काष्ठा cdns_dphy_cfg *cfg,
				     काष्ठा phy_configure_opts_mipi_dphy *opts,
				     अचिन्हित पूर्णांक *dsi_hfp_ext)
अणु
	अचिन्हित दीर्घ pll_ref_hz = clk_get_rate(dphy->pll_ref_clk);
	u64 dlane_bps;

	स_रखो(cfg, 0, माप(*cfg));

	अगर (pll_ref_hz < 9600000 || pll_ref_hz >= 150000000)
		वापस -EINVAL;
	अन्यथा अगर (pll_ref_hz < 19200000)
		cfg->pll_ipभाग = 1;
	अन्यथा अगर (pll_ref_hz < 38400000)
		cfg->pll_ipभाग = 2;
	अन्यथा अगर (pll_ref_hz < 76800000)
		cfg->pll_ipभाग = 4;
	अन्यथा
		cfg->pll_ipभाग = 8;

	dlane_bps = opts->hs_clk_rate;

	अगर (dlane_bps > 2500000000UL || dlane_bps < 160000000UL)
		वापस -EINVAL;
	अन्यथा अगर (dlane_bps >= 1250000000)
		cfg->pll_opभाग = 1;
	अन्यथा अगर (dlane_bps >= 630000000)
		cfg->pll_opभाग = 2;
	अन्यथा अगर (dlane_bps >= 320000000)
		cfg->pll_opभाग = 4;
	अन्यथा अगर (dlane_bps >= 160000000)
		cfg->pll_opभाग = 8;

	cfg->pll_fbभाग = DIV_ROUND_UP_ULL(dlane_bps * 2 * cfg->pll_opभाग *
					  cfg->pll_ipभाग,
					  pll_ref_hz);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dphy_setup_psm(काष्ठा cdns_dphy *dphy)
अणु
	अचिन्हित दीर्घ psm_clk_hz = clk_get_rate(dphy->psm_clk);
	अचिन्हित दीर्घ psm_भाग;

	अगर (!psm_clk_hz || psm_clk_hz > 100000000)
		वापस -EINVAL;

	psm_भाग = DIV_ROUND_CLOSEST(psm_clk_hz, 1000000);
	अगर (dphy->ops->set_psm_भाग)
		dphy->ops->set_psm_भाग(dphy, psm_भाग);

	वापस 0;
पूर्ण

अटल व्योम cdns_dphy_set_clk_lane_cfg(काष्ठा cdns_dphy *dphy,
				       क्रमागत cdns_dphy_clk_lane_cfg cfg)
अणु
	अगर (dphy->ops->set_clk_lane_cfg)
		dphy->ops->set_clk_lane_cfg(dphy, cfg);
पूर्ण

अटल व्योम cdns_dphy_set_pll_cfg(काष्ठा cdns_dphy *dphy,
				  स्थिर काष्ठा cdns_dphy_cfg *cfg)
अणु
	अगर (dphy->ops->set_pll_cfg)
		dphy->ops->set_pll_cfg(dphy, cfg);
पूर्ण

अटल अचिन्हित दीर्घ cdns_dphy_get_wakeup_समय_ns(काष्ठा cdns_dphy *dphy)
अणु
	वापस dphy->ops->get_wakeup_समय_ns(dphy);
पूर्ण

अटल अचिन्हित दीर्घ cdns_dphy_ref_get_wakeup_समय_ns(काष्ठा cdns_dphy *dphy)
अणु
	/* Default wakeup समय is 800 ns (in a simulated environment). */
	वापस 800;
पूर्ण

अटल व्योम cdns_dphy_ref_set_pll_cfg(काष्ठा cdns_dphy *dphy,
				      स्थिर काष्ठा cdns_dphy_cfg *cfg)
अणु
	u32 fbभाग_low, fbभाग_high;

	fbभाग_low = (cfg->pll_fbभाग / 4) - 2;
	fbभाग_high = cfg->pll_fbभाग - fbभाग_low - 2;

	ग_लिखोl(DPHY_CMN_IPDIV_FROM_REG | DPHY_CMN_OPDIV_FROM_REG |
	       DPHY_CMN_IPDIV(cfg->pll_ipभाग) |
	       DPHY_CMN_OPDIV(cfg->pll_opभाग),
	       dphy->regs + DPHY_CMN_OPIPDIV);
	ग_लिखोl(DPHY_CMN_FBDIV_FROM_REG |
	       DPHY_CMN_FBDIV_VAL(fbभाग_low, fbभाग_high),
	       dphy->regs + DPHY_CMN_FBDIV);
	ग_लिखोl(DPHY_CMN_PWM_HIGH(6) | DPHY_CMN_PWM_LOW(0x101) |
	       DPHY_CMN_PWM_DIV(0x8),
	       dphy->regs + DPHY_CMN_PWM);
पूर्ण

अटल व्योम cdns_dphy_ref_set_psm_भाग(काष्ठा cdns_dphy *dphy, u8 भाग)
अणु
	ग_लिखोl(DPHY_PSM_CFG_FROM_REG | DPHY_PSM_CLK_DIV(भाग),
	       dphy->regs + DPHY_PSM_CFG);
पूर्ण

/*
 * This is the reference implementation of DPHY hooks. Specअगरic पूर्णांकegration of
 * this IP may have to re-implement some of them depending on how they decided
 * to wire things in the SoC.
 */
अटल स्थिर काष्ठा cdns_dphy_ops ref_dphy_ops = अणु
	.get_wakeup_समय_ns = cdns_dphy_ref_get_wakeup_समय_ns,
	.set_pll_cfg = cdns_dphy_ref_set_pll_cfg,
	.set_psm_भाग = cdns_dphy_ref_set_psm_भाग,
पूर्ण;

अटल पूर्णांक cdns_dphy_config_from_opts(काष्ठा phy *phy,
				      काष्ठा phy_configure_opts_mipi_dphy *opts,
				      काष्ठा cdns_dphy_cfg *cfg)
अणु
	काष्ठा cdns_dphy *dphy = phy_get_drvdata(phy);
	अचिन्हित पूर्णांक dsi_hfp_ext = 0;
	पूर्णांक ret;

	ret = phy_mipi_dphy_config_validate(opts);
	अगर (ret)
		वापस ret;

	ret = cdns_dsi_get_dphy_pll_cfg(dphy, cfg,
					opts, &dsi_hfp_ext);
	अगर (ret)
		वापस ret;

	opts->wakeup = cdns_dphy_get_wakeup_समय_ns(dphy) / 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dphy_validate(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode,
			      जोड़ phy_configure_opts *opts)
अणु
	काष्ठा cdns_dphy_cfg cfg = अणु 0 पूर्ण;

	अगर (mode != PHY_MODE_MIPI_DPHY)
		वापस -EINVAL;

	वापस cdns_dphy_config_from_opts(phy, &opts->mipi_dphy, &cfg);
पूर्ण

अटल पूर्णांक cdns_dphy_configure(काष्ठा phy *phy, जोड़ phy_configure_opts *opts)
अणु
	काष्ठा cdns_dphy *dphy = phy_get_drvdata(phy);
	काष्ठा cdns_dphy_cfg cfg = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = cdns_dphy_config_from_opts(phy, &opts->mipi_dphy, &cfg);
	अगर (ret)
		वापस ret;

	/*
	 * Configure the पूर्णांकernal PSM clk भागider so that the DPHY has a
	 * 1MHz clk (or something बंद).
	 */
	ret = cdns_dphy_setup_psm(dphy);
	अगर (ret)
		वापस ret;

	/*
	 * Configure attach clk lanes to data lanes: the DPHY has 2 clk lanes
	 * and 8 data lanes, each clk lane can be attache dअगरferent set of
	 * data lanes. The 2 groups are named 'left' and 'right', so here we
	 * just say that we want the 'left' clk lane to drive the 'left' data
	 * lanes.
	 */
	cdns_dphy_set_clk_lane_cfg(dphy, DPHY_CLK_CFG_LEFT_DRIVES_LEFT);

	/*
	 * Configure the DPHY PLL that will be used to generate the TX byte
	 * clk.
	 */
	cdns_dphy_set_pll_cfg(dphy, &cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा cdns_dphy *dphy = phy_get_drvdata(phy);

	clk_prepare_enable(dphy->psm_clk);
	clk_prepare_enable(dphy->pll_ref_clk);

	/* Start TX state machine. */
	ग_लिखोl(DPHY_CMN_SSM_EN | DPHY_CMN_TX_MODE_EN,
	       dphy->regs + DPHY_CMN_SSM);

	वापस 0;
पूर्ण

अटल पूर्णांक cdns_dphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा cdns_dphy *dphy = phy_get_drvdata(phy);

	clk_disable_unprepare(dphy->pll_ref_clk);
	clk_disable_unprepare(dphy->psm_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops cdns_dphy_ops = अणु
	.configure	= cdns_dphy_configure,
	.validate	= cdns_dphy_validate,
	.घातer_on	= cdns_dphy_घातer_on,
	.घातer_off	= cdns_dphy_घातer_off,
पूर्ण;

अटल पूर्णांक cdns_dphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा cdns_dphy *dphy;
	पूर्णांक ret;

	dphy = devm_kzalloc(&pdev->dev, माप(*dphy), GFP_KERNEL);
	अगर (!dphy)
		वापस -ENOMEM;
	dev_set_drvdata(&pdev->dev, dphy);

	dphy->ops = of_device_get_match_data(&pdev->dev);
	अगर (!dphy->ops)
		वापस -EINVAL;

	dphy->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dphy->regs))
		वापस PTR_ERR(dphy->regs);

	dphy->psm_clk = devm_clk_get(&pdev->dev, "psm");
	अगर (IS_ERR(dphy->psm_clk))
		वापस PTR_ERR(dphy->psm_clk);

	dphy->pll_ref_clk = devm_clk_get(&pdev->dev, "pll_ref");
	अगर (IS_ERR(dphy->pll_ref_clk))
		वापस PTR_ERR(dphy->pll_ref_clk);

	अगर (dphy->ops->probe) अणु
		ret = dphy->ops->probe(dphy);
		अगर (ret)
			वापस ret;
	पूर्ण

	dphy->phy = devm_phy_create(&pdev->dev, शून्य, &cdns_dphy_ops);
	अगर (IS_ERR(dphy->phy)) अणु
		dev_err(&pdev->dev, "failed to create PHY\n");
		अगर (dphy->ops->हटाओ)
			dphy->ops->हटाओ(dphy);
		वापस PTR_ERR(dphy->phy);
	पूर्ण

	phy_set_drvdata(dphy->phy, dphy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(&pdev->dev,
						     of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल पूर्णांक cdns_dphy_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cdns_dphy *dphy = dev_get_drvdata(&pdev->dev);

	अगर (dphy->ops->हटाओ)
		dphy->ops->हटाओ(dphy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cdns_dphy_of_match[] = अणु
	अणु .compatible = "cdns,dphy", .data = &ref_dphy_ops पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cdns_dphy_of_match);

अटल काष्ठा platक्रमm_driver cdns_dphy_platक्रमm_driver = अणु
	.probe		= cdns_dphy_probe,
	.हटाओ		= cdns_dphy_हटाओ,
	.driver		= अणु
		.name		= "cdns-mipi-dphy",
		.of_match_table	= cdns_dphy_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cdns_dphy_platक्रमm_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@bootlin.com>");
MODULE_DESCRIPTION("Cadence MIPI D-PHY Driver");
MODULE_LICENSE("GPL");
