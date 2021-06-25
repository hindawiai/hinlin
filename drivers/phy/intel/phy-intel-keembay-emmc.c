<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Keem Bay eMMC PHY driver
 * Copyright (C) 2020 Intel Corporation
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* eMMC/SD/SDIO core/phy configuration रेजिस्टरs */
#घोषणा PHY_CFG_0		0x24
#घोषणा  SEL_DLY_TXCLK_MASK	BIT(29)
#घोषणा  OTAP_DLY_ENA_MASK	BIT(27)
#घोषणा  OTAP_DLY_SEL_MASK	GENMASK(26, 23)
#घोषणा  DLL_EN_MASK		BIT(10)
#घोषणा  PWR_DOWN_MASK		BIT(0)

#घोषणा PHY_CFG_2		0x2c
#घोषणा  SEL_FREQ_MASK		GENMASK(12, 10)

#घोषणा PHY_STAT		0x40
#घोषणा  CAL_DONE_MASK		BIT(6)
#घोषणा  IS_CALDONE(x)		((x) & CAL_DONE_MASK)
#घोषणा  DLL_RDY_MASK		BIT(5)
#घोषणा  IS_DLLRDY(x)		((x) & DLL_RDY_MASK)

/* From ACS_eMMC51_16nFFC_RO1100_Userguide_v1p0.pdf p17 */
#घोषणा FREQSEL_200M_170M	0x0
#घोषणा FREQSEL_170M_140M	0x1
#घोषणा FREQSEL_140M_110M	0x2
#घोषणा FREQSEL_110M_80M	0x3
#घोषणा FREQSEL_80M_50M		0x4

काष्ठा keembay_emmc_phy अणु
	काष्ठा regmap *syscfg;
	काष्ठा clk *emmcclk;
पूर्ण;

अटल स्थिर काष्ठा regmap_config keembay_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
पूर्ण;

अटल पूर्णांक keembay_emmc_phy_घातer(काष्ठा phy *phy, bool on_off)
अणु
	काष्ठा keembay_emmc_phy *priv = phy_get_drvdata(phy);
	अचिन्हित पूर्णांक calकरोne;
	अचिन्हित पूर्णांक dllrdy;
	अचिन्हित पूर्णांक freqsel;
	अचिन्हित पूर्णांक mhz;
	पूर्णांक ret;

	/*
	 * Keep phyctrl_pdb and phyctrl_endll low to allow
	 * initialization of CALIO state M/C DFFs
	 */
	ret = regmap_update_bits(priv->syscfg, PHY_CFG_0, PWR_DOWN_MASK,
				 FIELD_PREP(PWR_DOWN_MASK, 0));
	अगर (ret) अणु
		dev_err(&phy->dev, "CALIO power down bar failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(priv->syscfg, PHY_CFG_0, DLL_EN_MASK,
				 FIELD_PREP(DLL_EN_MASK, 0));
	अगर (ret) अणु
		dev_err(&phy->dev, "turn off the dll failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Alपढ़ोy finish घातer off above */
	अगर (!on_off)
		वापस 0;

	mhz = DIV_ROUND_CLOSEST(clk_get_rate(priv->emmcclk), 1000000);
	अगर (mhz <= 200 && mhz >= 170)
		freqsel = FREQSEL_200M_170M;
	अन्यथा अगर (mhz <= 170 && mhz >= 140)
		freqsel = FREQSEL_170M_140M;
	अन्यथा अगर (mhz <= 140 && mhz >= 110)
		freqsel = FREQSEL_140M_110M;
	अन्यथा अगर (mhz <= 110 && mhz >= 80)
		freqsel = FREQSEL_110M_80M;
	अन्यथा अगर (mhz <= 80 && mhz >= 50)
		freqsel = FREQSEL_80M_50M;
	अन्यथा
		freqsel = 0x0;

	अगर (mhz < 50 || mhz > 200)
		dev_warn(&phy->dev, "Unsupported rate: %d MHz\n", mhz);

	/*
	 * According to the user manual, calpad calibration
	 * cycle takes more than 2us without the minimal recommended
	 * value, so we may need a little margin here
	 */
	udelay(5);

	ret = regmap_update_bits(priv->syscfg, PHY_CFG_0, PWR_DOWN_MASK,
				 FIELD_PREP(PWR_DOWN_MASK, 1));
	अगर (ret) अणु
		dev_err(&phy->dev, "CALIO power down bar failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * According to the user manual, it asks driver to रुको 5us क्रम
	 * calpad busy trimming. However it is करोcumented that this value is
	 * PVT(A.K.A. process, voltage and temperature) relevant, so some
	 * failure हालs are found which indicates we should be more tolerant
	 * to calpad busy trimming.
	 */
	ret = regmap_पढ़ो_poll_समयout(priv->syscfg, PHY_STAT,
				       calकरोne, IS_CALDONE(calकरोne),
				       0, 50);
	अगर (ret) अणु
		dev_err(&phy->dev, "caldone failed, ret=%d\n", ret);
		वापस ret;
	पूर्ण

	/* Set the frequency of the DLL operation */
	ret = regmap_update_bits(priv->syscfg, PHY_CFG_2, SEL_FREQ_MASK,
				 FIELD_PREP(SEL_FREQ_MASK, freqsel));
	अगर (ret) अणु
		dev_err(&phy->dev, "set the frequency of dll failed:%d\n", ret);
		वापस ret;
	पूर्ण

	/* Turn on the DLL */
	ret = regmap_update_bits(priv->syscfg, PHY_CFG_0, DLL_EN_MASK,
				 FIELD_PREP(DLL_EN_MASK, 1));
	अगर (ret) अणु
		dev_err(&phy->dev, "turn on the dll failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * We turned on the DLL even though the rate was 0 because we the
	 * घड़ी might be turned on later.  ...but we can't रुको क्रम the DLL
	 * to lock when the rate is 0 because it will never lock with no
	 * input घड़ी.
	 *
	 * Technically we should be checking the lock later when the घड़ी
	 * is turned on, but क्रम now we won't.
	 */
	अगर (mhz == 0)
		वापस 0;

	/*
	 * After enabling analog DLL circuits करोcs say that we need 10.2 us अगर
	 * our source घड़ी is at 50 MHz and that lock समय scales linearly
	 * with घड़ी speed. If we are घातering on the PHY and the card घड़ी
	 * is super slow (like 100kHz) this could take as दीर्घ as 5.1 ms as
	 * per the math: 10.2 us * (50000000 Hz / 100000 Hz) => 5.1 ms
	 * hopefully we won't be running at 100 kHz, but we should still make
	 * sure we रुको दीर्घ enough.
	 *
	 * NOTE: There appear to be corner हालs where the DLL seems to take
	 * extra दीर्घ to lock क्रम reasons that aren't understood. In some
	 * extreme हालs we've seen it take up to over 10ms (!). We'll be
	 * generous and give it 50ms.
	 */
	ret = regmap_पढ़ो_poll_समयout(priv->syscfg, PHY_STAT,
				       dllrdy, IS_DLLRDY(dllrdy),
				       0, 50 * USEC_PER_MSEC);
	अगर (ret)
		dev_err(&phy->dev, "dllrdy failed, ret=%d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक keembay_emmc_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा keembay_emmc_phy *priv = phy_get_drvdata(phy);

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
	 */
	priv->emmcclk = clk_get_optional(&phy->dev, "emmcclk");

	वापस PTR_ERR_OR_ZERO(priv->emmcclk);
पूर्ण

अटल पूर्णांक keembay_emmc_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा keembay_emmc_phy *priv = phy_get_drvdata(phy);

	clk_put(priv->emmcclk);

	वापस 0;
पूर्ण;

अटल पूर्णांक keembay_emmc_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा keembay_emmc_phy *priv = phy_get_drvdata(phy);
	पूर्णांक ret;

	/* Delay chain based txclk: enable */
	ret = regmap_update_bits(priv->syscfg, PHY_CFG_0, SEL_DLY_TXCLK_MASK,
				 FIELD_PREP(SEL_DLY_TXCLK_MASK, 1));
	अगर (ret) अणु
		dev_err(&phy->dev, "ERROR: delay chain txclk set: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Output tap delay: enable */
	ret = regmap_update_bits(priv->syscfg, PHY_CFG_0, OTAP_DLY_ENA_MASK,
				 FIELD_PREP(OTAP_DLY_ENA_MASK, 1));
	अगर (ret) अणु
		dev_err(&phy->dev, "ERROR: output tap delay set: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Output tap delay */
	ret = regmap_update_bits(priv->syscfg, PHY_CFG_0, OTAP_DLY_SEL_MASK,
				 FIELD_PREP(OTAP_DLY_SEL_MASK, 2));
	अगर (ret) अणु
		dev_err(&phy->dev, "ERROR: output tap delay select: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Power up eMMC phy analog blocks */
	वापस keembay_emmc_phy_घातer(phy, true);
पूर्ण

अटल पूर्णांक keembay_emmc_phy_घातer_off(काष्ठा phy *phy)
अणु
	/* Power करोwn eMMC phy analog blocks */
	वापस keembay_emmc_phy_घातer(phy, false);
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= keembay_emmc_phy_init,
	.निकास		= keembay_emmc_phy_निकास,
	.घातer_on	= keembay_emmc_phy_घातer_on,
	.घातer_off	= keembay_emmc_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक keembay_emmc_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा keembay_emmc_phy *priv;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	व्योम __iomem *base;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->syscfg = devm_regmap_init_mmio(dev, base, &keembay_regmap_config);
	अगर (IS_ERR(priv->syscfg))
		वापस PTR_ERR(priv->syscfg);

	generic_phy = devm_phy_create(dev, np, &ops);
	अगर (IS_ERR(generic_phy))
		वापस dev_err_probe(dev, PTR_ERR(generic_phy),
				     "failed to create PHY\n");

	phy_set_drvdata(generic_phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id keembay_emmc_phy_dt_ids[] = अणु
	अणु .compatible = "intel,keembay-emmc-phy" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, keembay_emmc_phy_dt_ids);

अटल काष्ठा platक्रमm_driver keembay_emmc_phy_driver = अणु
	.probe		= keembay_emmc_phy_probe,
	.driver		= अणु
		.name	= "keembay-emmc-phy",
		.of_match_table = keembay_emmc_phy_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(keembay_emmc_phy_driver);

MODULE_AUTHOR("Wan Ahmad Zainie <wan.ahmad.zainie.wan.mohamad@intel.com>");
MODULE_DESCRIPTION("Intel Keem Bay eMMC PHY driver");
MODULE_LICENSE("GPL v2");
