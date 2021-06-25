<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel eMMC PHY driver
 * Copyright (C) 2019 Intel, Corp.
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* eMMC phy रेजिस्टर definitions */
#घोषणा EMMC_PHYCTRL0_REG	0xa8
#घोषणा DR_TY_MASK		GENMASK(30, 28)
#घोषणा DR_TY_SHIFT(x)		(((x) << 28) & DR_TY_MASK)
#घोषणा OTAPDLYENA		BIT(14)
#घोषणा OTAPDLYSEL_MASK		GENMASK(13, 10)
#घोषणा OTAPDLYSEL_SHIFT(x)	(((x) << 10) & OTAPDLYSEL_MASK)

#घोषणा EMMC_PHYCTRL1_REG	0xac
#घोषणा PDB_MASK		BIT(0)
#घोषणा PDB_SHIFT(x)		(((x) << 0) & PDB_MASK)
#घोषणा ENDLL_MASK		BIT(7)
#घोषणा ENDLL_SHIFT(x)		(((x) << 7) & ENDLL_MASK)

#घोषणा EMMC_PHYCTRL2_REG	0xb0
#घोषणा FRQSEL_25M		0
#घोषणा FRQSEL_50M		1
#घोषणा FRQSEL_100M		2
#घोषणा FRQSEL_150M		3
#घोषणा FRQSEL_MASK		GENMASK(24, 22)
#घोषणा FRQSEL_SHIFT(x)		(((x) << 22) & FRQSEL_MASK)

#घोषणा EMMC_PHYSTAT_REG	0xbc
#घोषणा CALDONE_MASK		BIT(9)
#घोषणा DLLRDY_MASK		BIT(8)
#घोषणा IS_CALDONE(x)	((x) & CALDONE_MASK)
#घोषणा IS_DLLRDY(x)	((x) & DLLRDY_MASK)

काष्ठा पूर्णांकel_emmc_phy अणु
	काष्ठा regmap *syscfg;
	काष्ठा clk *emmcclk;
पूर्ण;

अटल पूर्णांक पूर्णांकel_emmc_phy_घातer(काष्ठा phy *phy, bool on_off)
अणु
	काष्ठा पूर्णांकel_emmc_phy *priv = phy_get_drvdata(phy);
	अचिन्हित पूर्णांक calकरोne;
	अचिन्हित पूर्णांक dllrdy;
	अचिन्हित पूर्णांक freqsel;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret, quot;

	/*
	 * Keep phyctrl_pdb and phyctrl_endll low to allow
	 * initialization of CALIO state M/C DFFs
	 */
	ret = regmap_update_bits(priv->syscfg, EMMC_PHYCTRL1_REG, PDB_MASK,
				 PDB_SHIFT(0));
	अगर (ret) अणु
		dev_err(&phy->dev, "CALIO power down bar failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Alपढ़ोy finish घातer_off above */
	अगर (!on_off)
		वापस 0;

	rate = clk_get_rate(priv->emmcclk);
	quot = DIV_ROUND_CLOSEST(rate, 50000000);
	अगर (quot > FRQSEL_150M)
		dev_warn(&phy->dev, "Unsupported rate: %lu\n", rate);
	freqsel = clamp_t(पूर्णांक, quot, FRQSEL_25M, FRQSEL_150M);

	/*
	 * According to the user manual, calpad calibration
	 * cycle takes more than 2us without the minimal recommended
	 * value, so we may need a little margin here
	 */
	udelay(5);

	ret = regmap_update_bits(priv->syscfg, EMMC_PHYCTRL1_REG, PDB_MASK,
				 PDB_SHIFT(1));
	अगर (ret) अणु
		dev_err(&phy->dev, "CALIO power down bar failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * According to the user manual, it asks driver to रुको 5us क्रम
	 * calpad busy trimming. However it is करोcumented that this value is
	 * PVT(A.K.A process,voltage and temperature) relevant, so some
	 * failure हालs are found which indicates we should be more tolerant
	 * to calpad busy trimming.
	 */
	ret = regmap_पढ़ो_poll_समयout(priv->syscfg, EMMC_PHYSTAT_REG,
				       calकरोne, IS_CALDONE(calकरोne),
				       0, 50);
	अगर (ret) अणु
		dev_err(&phy->dev, "caldone failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	/* Set the frequency of the DLL operation */
	ret = regmap_update_bits(priv->syscfg, EMMC_PHYCTRL2_REG, FRQSEL_MASK,
				 FRQSEL_SHIFT(freqsel));
	अगर (ret) अणु
		dev_err(&phy->dev, "set the frequency of dll failed:%d\n", ret);
		वापस ret;
	पूर्ण

	/* Turn on the DLL */
	ret = regmap_update_bits(priv->syscfg, EMMC_PHYCTRL1_REG, ENDLL_MASK,
				 ENDLL_SHIFT(1));
	अगर (ret) अणु
		dev_err(&phy->dev, "turn on the dll failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * After enabling analog DLL circuits करोcs say that we need 10.2 us अगर
	 * our source घड़ी is at 50 MHz and that lock समय scales linearly
	 * with घड़ी speed.  If we are घातering on the PHY and the card घड़ी
	 * is super slow (like 100 kHZ) this could take as दीर्घ as 5.1 ms as
	 * per the math: 10.2 us * (50000000 Hz / 100000 Hz) => 5.1 ms
	 * Hopefully we won't be running at 100 kHz, but we should still make
	 * sure we रुको दीर्घ enough.
	 *
	 * NOTE: There appear to be corner हालs where the DLL seems to take
	 * extra दीर्घ to lock क्रम reasons that aren't understood.  In some
	 * extreme हालs we've seen it take up to over 10ms (!).  We'll be
	 * generous and give it 50ms.
	 */
	ret = regmap_पढ़ो_poll_समयout(priv->syscfg,
				       EMMC_PHYSTAT_REG,
				       dllrdy, IS_DLLRDY(dllrdy),
				       0, 50 * USEC_PER_MSEC);
	अगर (ret) अणु
		dev_err(&phy->dev, "dllrdy failed. ret=%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_emmc_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा पूर्णांकel_emmc_phy *priv = phy_get_drvdata(phy);

	/*
	 * We purposely get the घड़ी here and not in probe to aव्योम the
	 * circular dependency problem. We expect:
	 * - PHY driver to probe
	 * - SDHCI driver to start probe
	 * - SDHCI driver to रेजिस्टर it's घड़ी
	 * - SDHCI driver to get the PHY
	 * - SDHCI driver to init the PHY
	 *
	 * The घड़ी is optional, so upon any error just वापस it like
	 * any other error to user.
	 *
	 */
	priv->emmcclk = clk_get_optional(&phy->dev, "emmcclk");
	अगर (IS_ERR(priv->emmcclk)) अणु
		dev_err(&phy->dev, "ERROR: getting emmcclk\n");
		वापस PTR_ERR(priv->emmcclk);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_emmc_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा पूर्णांकel_emmc_phy *priv = phy_get_drvdata(phy);

	clk_put(priv->emmcclk);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_emmc_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा पूर्णांकel_emmc_phy *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	/* Drive impedance: 50 Ohm */
	ret = regmap_update_bits(priv->syscfg, EMMC_PHYCTRL0_REG, DR_TY_MASK,
				 DR_TY_SHIFT(6));
	अगर (ret) अणु
		dev_err(&phy->dev, "ERROR set drive-impednce-50ohm: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Output tap delay: disable */
	ret = regmap_update_bits(priv->syscfg, EMMC_PHYCTRL0_REG, OTAPDLYENA,
				 0);
	अगर (ret) अणु
		dev_err(&phy->dev, "ERROR Set output tap delay : %d\n", ret);
		वापस ret;
	पूर्ण

	/* Output tap delay */
	ret = regmap_update_bits(priv->syscfg, EMMC_PHYCTRL0_REG,
				 OTAPDLYSEL_MASK, OTAPDLYSEL_SHIFT(4));
	अगर (ret) अणु
		dev_err(&phy->dev, "ERROR: output tap dly select: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Power up eMMC phy analog blocks */
	वापस पूर्णांकel_emmc_phy_घातer(phy, true);
पूर्ण

अटल पूर्णांक पूर्णांकel_emmc_phy_घातer_off(काष्ठा phy *phy)
अणु
	/* Power करोwn eMMC phy analog blocks */
	वापस पूर्णांकel_emmc_phy_घातer(phy, false);
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= पूर्णांकel_emmc_phy_init,
	.निकास		= पूर्णांकel_emmc_phy_निकास,
	.घातer_on	= पूर्णांकel_emmc_phy_घातer_on,
	.घातer_off	= पूर्णांकel_emmc_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक पूर्णांकel_emmc_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा पूर्णांकel_emmc_phy *priv;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Get eMMC phy (accessed via chiptop) regmap */
	priv->syscfg = syscon_regmap_lookup_by_phandle(np, "intel,syscon");
	अगर (IS_ERR(priv->syscfg)) अणु
		dev_err(dev, "failed to find syscon\n");
		वापस PTR_ERR(priv->syscfg);
	पूर्ण

	generic_phy = devm_phy_create(dev, np, &ops);
	अगर (IS_ERR(generic_phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(generic_phy);
	पूर्ण

	phy_set_drvdata(generic_phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id पूर्णांकel_emmc_phy_dt_ids[] = अणु
	अणु .compatible = "intel,lgm-emmc-phy" पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, पूर्णांकel_emmc_phy_dt_ids);

अटल काष्ठा platक्रमm_driver पूर्णांकel_emmc_driver = अणु
	.probe		= पूर्णांकel_emmc_phy_probe,
	.driver		= अणु
		.name	= "intel-emmc-phy",
		.of_match_table = पूर्णांकel_emmc_phy_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_emmc_driver);

MODULE_AUTHOR("Peter Harliman Liem <peter.harliman.liem@intel.com>");
MODULE_DESCRIPTION("Intel eMMC PHY driver");
MODULE_LICENSE("GPL v2");
