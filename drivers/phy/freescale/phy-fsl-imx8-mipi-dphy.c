<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2017,2018 NXP
 * Copyright 2019 Purism SPC
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* DPHY रेजिस्टरs */
#घोषणा DPHY_PD_DPHY			0x00
#घोषणा DPHY_M_PRG_HS_PREPARE		0x04
#घोषणा DPHY_MC_PRG_HS_PREPARE		0x08
#घोषणा DPHY_M_PRG_HS_ZERO		0x0c
#घोषणा DPHY_MC_PRG_HS_ZERO		0x10
#घोषणा DPHY_M_PRG_HS_TRAIL		0x14
#घोषणा DPHY_MC_PRG_HS_TRAIL		0x18
#घोषणा DPHY_PD_PLL			0x1c
#घोषणा DPHY_TST			0x20
#घोषणा DPHY_CN				0x24
#घोषणा DPHY_CM				0x28
#घोषणा DPHY_CO				0x2c
#घोषणा DPHY_LOCK			0x30
#घोषणा DPHY_LOCK_BYP			0x34
#घोषणा DPHY_REG_BYPASS_PLL		0x4C

#घोषणा MBPS(x) ((x) * 1000000)

#घोषणा DATA_RATE_MAX_SPEED MBPS(1500)
#घोषणा DATA_RATE_MIN_SPEED MBPS(80)

#घोषणा PLL_LOCK_SLEEP 10
#घोषणा PLL_LOCK_TIMEOUT 1000

#घोषणा CN_BUF	0xcb7a89c0
#घोषणा CO_BUF	0x63
#घोषणा CM(x)	(				  \
		((x) <	32) ? 0xe0 | ((x) - 16) : \
		((x) <	64) ? 0xc0 | ((x) - 32) : \
		((x) < 128) ? 0x80 | ((x) - 64) : \
		((x) - 128))
#घोषणा CN(x)	(((x) == 1) ? 0x1f : (((CN_BUF) >> ((x) - 1)) & 0x1f))
#घोषणा CO(x)	((CO_BUF) >> (8 - (x)) & 0x03)

/* PHY घातer on is active low */
#घोषणा PWR_ON	0
#घोषणा PWR_OFF	1

क्रमागत mixel_dphy_devtype अणु
	MIXEL_IMX8MQ,
पूर्ण;

काष्ठा mixel_dphy_devdata अणु
	u8 reg_tx_rcal;
	u8 reg_स्वतः_pd_en;
	u8 reg_rxlprp;
	u8 reg_rxcdrp;
	u8 reg_rxhs_settle;
पूर्ण;

अटल स्थिर काष्ठा mixel_dphy_devdata mixel_dphy_devdata[] = अणु
	[MIXEL_IMX8MQ] = अणु
		.reg_tx_rcal = 0x38,
		.reg_स्वतः_pd_en = 0x3c,
		.reg_rxlprp = 0x40,
		.reg_rxcdrp = 0x44,
		.reg_rxhs_settle = 0x48,
	पूर्ण,
पूर्ण;

काष्ठा mixel_dphy_cfg अणु
	/* DPHY PLL parameters */
	u32 cm;
	u32 cn;
	u32 co;
	/* DPHY रेजिस्टर values */
	u8 mc_prg_hs_prepare;
	u8 m_prg_hs_prepare;
	u8 mc_prg_hs_zero;
	u8 m_prg_hs_zero;
	u8 mc_prg_hs_trail;
	u8 m_prg_hs_trail;
	u8 rxhs_settle;
पूर्ण;

काष्ठा mixel_dphy_priv अणु
	काष्ठा mixel_dphy_cfg cfg;
	काष्ठा regmap *regmap;
	काष्ठा clk *phy_ref_clk;
	स्थिर काष्ठा mixel_dphy_devdata *devdata;
पूर्ण;

अटल स्थिर काष्ठा regmap_config mixel_dphy_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = DPHY_REG_BYPASS_PLL,
	.name = "mipi-dphy",
पूर्ण;

अटल पूर्णांक phy_ग_लिखो(काष्ठा phy *phy, u32 value, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा mixel_dphy_priv *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	ret = regmap_ग_लिखो(priv->regmap, reg, value);
	अगर (ret < 0)
		dev_err(&phy->dev, "Failed to write DPHY reg %d: %d\n", reg,
			ret);
	वापस ret;
पूर्ण

/*
 * Find a ratio बंद to the desired one using जारीd fraction
 * approximation ending either at exact match or maximum allowed
 * nominator, denominator.
 */
अटल व्योम get_best_ratio(u32 *pnum, u32 *pdenom, u32 max_n, u32 max_d)
अणु
	u32 a = *pnum;
	u32 b = *pdenom;
	u32 c;
	u32 n[] = अणु0, 1पूर्ण;
	u32 d[] = अणु1, 0पूर्ण;
	u32 whole;
	अचिन्हित पूर्णांक i = 1;

	जबतक (b) अणु
		i ^= 1;
		whole = a / b;
		n[i] += (n[i ^ 1] * whole);
		d[i] += (d[i ^ 1] * whole);
		अगर ((n[i] > max_n) || (d[i] > max_d)) अणु
			i ^= 1;
			अवरोध;
		पूर्ण
		c = a - (b * whole);
		a = b;
		b = c;
	पूर्ण
	*pnum = n[i];
	*pdenom = d[i];
पूर्ण

अटल पूर्णांक mixel_dphy_config_from_opts(काष्ठा phy *phy,
	       काष्ठा phy_configure_opts_mipi_dphy *dphy_opts,
	       काष्ठा mixel_dphy_cfg *cfg)
अणु
	काष्ठा mixel_dphy_priv *priv = dev_get_drvdata(phy->dev.parent);
	अचिन्हित दीर्घ ref_clk = clk_get_rate(priv->phy_ref_clk);
	u32 lp_t, numerator, denominator;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	u32 n;
	पूर्णांक i;

	अगर (dphy_opts->hs_clk_rate > DATA_RATE_MAX_SPEED ||
	    dphy_opts->hs_clk_rate < DATA_RATE_MIN_SPEED)
		वापस -EINVAL;

	numerator = dphy_opts->hs_clk_rate;
	denominator = ref_clk;
	get_best_ratio(&numerator, &denominator, 255, 256);
	अगर (!numerator || !denominator) अणु
		dev_err(&phy->dev, "Invalid %d/%d for %ld/%ld\n",
			numerator, denominator,
			dphy_opts->hs_clk_rate, ref_clk);
		वापस -EINVAL;
	पूर्ण

	जबतक ((numerator < 16) && (denominator <= 128)) अणु
		numerator <<= 1;
		denominator <<= 1;
	पूर्ण
	/*
	 * CM ranges between 16 and 255
	 * CN ranges between 1 and 32
	 * CO is घातer of 2: 1, 2, 4, 8
	 */
	i = __ffs(denominator);
	अगर (i > 3)
		i = 3;
	cfg->cn = denominator >> i;
	cfg->co = 1 << i;
	cfg->cm = numerator;

	अगर (cfg->cm < 16 || cfg->cm > 255 ||
	    cfg->cn < 1 || cfg->cn > 32 ||
	    cfg->co < 1 || cfg->co > 8) अणु
		dev_err(&phy->dev, "Invalid CM/CN/CO values: %u/%u/%u\n",
			cfg->cm, cfg->cn, cfg->co);
		dev_err(&phy->dev, "for hs_clk/ref_clk=%ld/%ld ~ %d/%d\n",
			dphy_opts->hs_clk_rate, ref_clk,
			numerator, denominator);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&phy->dev, "hs_clk/ref_clk=%ld/%ld ~ %d/%d\n",
		dphy_opts->hs_clk_rate, ref_clk, numerator, denominator);

	/* LP घड़ी period */
	पंचांगp = 1000000000000LL;
	करो_भाग(पंचांगp, dphy_opts->lp_clk_rate); /* ps */
	अगर (पंचांगp > अच_दीर्घ_उच्च)
		वापस -EINVAL;

	lp_t = पंचांगp;
	dev_dbg(&phy->dev, "LP clock %lu, period: %u ps\n",
		dphy_opts->lp_clk_rate, lp_t);

	/* hs_prepare: in lp घड़ी periods */
	अगर (2 * dphy_opts->hs_prepare > 5 * lp_t) अणु
		dev_err(&phy->dev,
			"hs_prepare (%u) > 2.5 * lp clock period (%u)\n",
			dphy_opts->hs_prepare, lp_t);
		वापस -EINVAL;
	पूर्ण
	/* 00: lp_t, 01: 1.5 * lp_t, 10: 2 * lp_t, 11: 2.5 * lp_t */
	अगर (dphy_opts->hs_prepare < lp_t) अणु
		n = 0;
	पूर्ण अन्यथा अणु
		पंचांगp = 2 * (dphy_opts->hs_prepare - lp_t);
		करो_भाग(पंचांगp, lp_t);
		n = पंचांगp;
	पूर्ण
	cfg->m_prg_hs_prepare = n;

	/* clk_prepare: in lp घड़ी periods */
	अगर (2 * dphy_opts->clk_prepare > 3 * lp_t) अणु
		dev_err(&phy->dev,
			"clk_prepare (%u) > 1.5 * lp clock period (%u)\n",
			dphy_opts->clk_prepare, lp_t);
		वापस -EINVAL;
	पूर्ण
	/* 00: lp_t, 01: 1.5 * lp_t */
	cfg->mc_prg_hs_prepare = dphy_opts->clk_prepare > lp_t ? 1 : 0;

	/* hs_zero: क्रमmula from NXP BSP */
	n = (144 * (dphy_opts->hs_clk_rate / 1000000) - 47500) / 10000;
	cfg->m_prg_hs_zero = n < 1 ? 1 : n;

	/* clk_zero: क्रमmula from NXP BSP */
	n = (34 * (dphy_opts->hs_clk_rate / 1000000) - 2500) / 1000;
	cfg->mc_prg_hs_zero = n < 1 ? 1 : n;

	/* clk_trail, hs_trail: क्रमmula from NXP BSP */
	n = (103 * (dphy_opts->hs_clk_rate / 1000000) + 10000) / 10000;
	अगर (n > 15)
		n = 15;
	अगर (n < 1)
		n = 1;
	cfg->m_prg_hs_trail = n;
	cfg->mc_prg_hs_trail = n;

	/* rxhs_settle: क्रमmula from NXP BSP */
	अगर (dphy_opts->hs_clk_rate < MBPS(80))
		cfg->rxhs_settle = 0x0d;
	अन्यथा अगर (dphy_opts->hs_clk_rate < MBPS(90))
		cfg->rxhs_settle = 0x0c;
	अन्यथा अगर (dphy_opts->hs_clk_rate < MBPS(125))
		cfg->rxhs_settle = 0x0b;
	अन्यथा अगर (dphy_opts->hs_clk_rate < MBPS(150))
		cfg->rxhs_settle = 0x0a;
	अन्यथा अगर (dphy_opts->hs_clk_rate < MBPS(225))
		cfg->rxhs_settle = 0x09;
	अन्यथा अगर (dphy_opts->hs_clk_rate < MBPS(500))
		cfg->rxhs_settle = 0x08;
	अन्यथा
		cfg->rxhs_settle = 0x07;

	dev_dbg(&phy->dev, "phy_config: %u %u %u %u %u %u %u\n",
		cfg->m_prg_hs_prepare, cfg->mc_prg_hs_prepare,
		cfg->m_prg_hs_zero, cfg->mc_prg_hs_zero,
		cfg->m_prg_hs_trail, cfg->mc_prg_hs_trail,
		cfg->rxhs_settle);

	वापस 0;
पूर्ण

अटल व्योम mixel_phy_set_hs_timings(काष्ठा phy *phy)
अणु
	काष्ठा mixel_dphy_priv *priv = phy_get_drvdata(phy);

	phy_ग_लिखो(phy, priv->cfg.m_prg_hs_prepare, DPHY_M_PRG_HS_PREPARE);
	phy_ग_लिखो(phy, priv->cfg.mc_prg_hs_prepare, DPHY_MC_PRG_HS_PREPARE);
	phy_ग_लिखो(phy, priv->cfg.m_prg_hs_zero, DPHY_M_PRG_HS_ZERO);
	phy_ग_लिखो(phy, priv->cfg.mc_prg_hs_zero, DPHY_MC_PRG_HS_ZERO);
	phy_ग_लिखो(phy, priv->cfg.m_prg_hs_trail, DPHY_M_PRG_HS_TRAIL);
	phy_ग_लिखो(phy, priv->cfg.mc_prg_hs_trail, DPHY_MC_PRG_HS_TRAIL);
	phy_ग_लिखो(phy, priv->cfg.rxhs_settle, priv->devdata->reg_rxhs_settle);
पूर्ण

अटल पूर्णांक mixel_dphy_set_pll_params(काष्ठा phy *phy)
अणु
	काष्ठा mixel_dphy_priv *priv = dev_get_drvdata(phy->dev.parent);

	अगर (priv->cfg.cm < 16 || priv->cfg.cm > 255 ||
	    priv->cfg.cn < 1 || priv->cfg.cn > 32 ||
	    priv->cfg.co < 1 || priv->cfg.co > 8) अणु
		dev_err(&phy->dev, "Invalid CM/CN/CO values! (%u/%u/%u)\n",
			priv->cfg.cm, priv->cfg.cn, priv->cfg.co);
		वापस -EINVAL;
	पूर्ण
	dev_dbg(&phy->dev, "Using CM:%u CN:%u CO:%u\n",
		priv->cfg.cm, priv->cfg.cn, priv->cfg.co);
	phy_ग_लिखो(phy, CM(priv->cfg.cm), DPHY_CM);
	phy_ग_लिखो(phy, CN(priv->cfg.cn), DPHY_CN);
	phy_ग_लिखो(phy, CO(priv->cfg.co), DPHY_CO);
	वापस 0;
पूर्ण

अटल पूर्णांक mixel_dphy_configure(काष्ठा phy *phy, जोड़ phy_configure_opts *opts)
अणु
	काष्ठा mixel_dphy_priv *priv = phy_get_drvdata(phy);
	काष्ठा mixel_dphy_cfg cfg = अणु 0 पूर्ण;
	पूर्णांक ret;

	ret = mixel_dphy_config_from_opts(phy, &opts->mipi_dphy, &cfg);
	अगर (ret)
		वापस ret;

	/* Update the configuration */
	स_नकल(&priv->cfg, &cfg, माप(काष्ठा mixel_dphy_cfg));

	phy_ग_लिखो(phy, 0x00, DPHY_LOCK_BYP);
	phy_ग_लिखो(phy, 0x01, priv->devdata->reg_tx_rcal);
	phy_ग_लिखो(phy, 0x00, priv->devdata->reg_स्वतः_pd_en);
	phy_ग_लिखो(phy, 0x02, priv->devdata->reg_rxlprp);
	phy_ग_लिखो(phy, 0x02, priv->devdata->reg_rxcdrp);
	phy_ग_लिखो(phy, 0x25, DPHY_TST);

	mixel_phy_set_hs_timings(phy);
	ret = mixel_dphy_set_pll_params(phy);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mixel_dphy_validate(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode,
			       जोड़ phy_configure_opts *opts)
अणु
	काष्ठा mixel_dphy_cfg cfg = अणु 0 पूर्ण;

	अगर (mode != PHY_MODE_MIPI_DPHY)
		वापस -EINVAL;

	वापस mixel_dphy_config_from_opts(phy, &opts->mipi_dphy, &cfg);
पूर्ण

अटल पूर्णांक mixel_dphy_init(काष्ठा phy *phy)
अणु
	phy_ग_लिखो(phy, PWR_OFF, DPHY_PD_PLL);
	phy_ग_लिखो(phy, PWR_OFF, DPHY_PD_DPHY);

	वापस 0;
पूर्ण

अटल पूर्णांक mixel_dphy_निकास(काष्ठा phy *phy)
अणु
	phy_ग_लिखो(phy, 0, DPHY_CM);
	phy_ग_लिखो(phy, 0, DPHY_CN);
	phy_ग_लिखो(phy, 0, DPHY_CO);

	वापस 0;
पूर्ण

अटल पूर्णांक mixel_dphy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा mixel_dphy_priv *priv = phy_get_drvdata(phy);
	u32 locked;
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->phy_ref_clk);
	अगर (ret < 0)
		वापस ret;

	phy_ग_लिखो(phy, PWR_ON, DPHY_PD_PLL);
	ret = regmap_पढ़ो_poll_समयout(priv->regmap, DPHY_LOCK, locked,
				       locked, PLL_LOCK_SLEEP,
				       PLL_LOCK_TIMEOUT);
	अगर (ret < 0) अणु
		dev_err(&phy->dev, "Could not get DPHY lock (%d)!\n", ret);
		जाओ घड़ी_disable;
	पूर्ण
	phy_ग_लिखो(phy, PWR_ON, DPHY_PD_DPHY);

	वापस 0;
घड़ी_disable:
	clk_disable_unprepare(priv->phy_ref_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक mixel_dphy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा mixel_dphy_priv *priv = phy_get_drvdata(phy);

	phy_ग_लिखो(phy, PWR_OFF, DPHY_PD_PLL);
	phy_ग_लिखो(phy, PWR_OFF, DPHY_PD_DPHY);

	clk_disable_unprepare(priv->phy_ref_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा phy_ops mixel_dphy_phy_ops = अणु
	.init = mixel_dphy_init,
	.निकास = mixel_dphy_निकास,
	.घातer_on = mixel_dphy_घातer_on,
	.घातer_off = mixel_dphy_घातer_off,
	.configure = mixel_dphy_configure,
	.validate = mixel_dphy_validate,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mixel_dphy_of_match[] = अणु
	अणु .compatible = "fsl,imx8mq-mipi-dphy",
	  .data = &mixel_dphy_devdata[MIXEL_IMX8MQ] पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mixel_dphy_of_match);

अटल पूर्णांक mixel_dphy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा phy_provider *phy_provider;
	काष्ठा mixel_dphy_priv *priv;
	काष्ठा phy *phy;
	व्योम __iomem *base;

	अगर (!np)
		वापस -ENODEV;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->devdata = of_device_get_match_data(&pdev->dev);
	अगर (!priv->devdata)
		वापस -EINVAL;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					     &mixel_dphy_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(dev, "Couldn't create the DPHY regmap\n");
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	priv->phy_ref_clk = devm_clk_get(&pdev->dev, "phy_ref");
	अगर (IS_ERR(priv->phy_ref_clk)) अणु
		dev_err(dev, "No phy_ref clock found\n");
		वापस PTR_ERR(priv->phy_ref_clk);
	पूर्ण
	dev_dbg(dev, "phy_ref clock rate: %lu\n",
		clk_get_rate(priv->phy_ref_clk));

	dev_set_drvdata(dev, priv);

	phy = devm_phy_create(dev, np, &mixel_dphy_phy_ops);
	अगर (IS_ERR(phy)) अणु
		dev_err(dev, "Failed to create phy %ld\n", PTR_ERR(phy));
		वापस PTR_ERR(phy);
	पूर्ण
	phy_set_drvdata(phy, priv);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल काष्ठा platक्रमm_driver mixel_dphy_driver = अणु
	.probe	= mixel_dphy_probe,
	.driver = अणु
		.name = "mixel-mipi-dphy",
		.of_match_table	= mixel_dphy_of_match,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(mixel_dphy_driver);

MODULE_AUTHOR("NXP Semiconductor");
MODULE_DESCRIPTION("Mixel MIPI-DSI PHY driver");
MODULE_LICENSE("GPL");
