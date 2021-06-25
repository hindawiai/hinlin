<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip emmc PHY driver
 *
 * Copyright (C) 2016 Shawn Lin <shawn.lin@rock-chips.com>
 * Copyright (C) 2016 ROCKCHIP, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/*
 * The higher 16-bit of this रेजिस्टर is used क्रम ग_लिखो protection
 * only अगर BIT(x + 16) set to 1 the BIT(x) can be written.
 */
#घोषणा HIWORD_UPDATE(val, mask, shअगरt) \
		((val) << (shअगरt) | (mask) << ((shअगरt) + 16))

/* Register definition */
#घोषणा GRF_EMMCPHY_CON0		0x0
#घोषणा GRF_EMMCPHY_CON1		0x4
#घोषणा GRF_EMMCPHY_CON2		0x8
#घोषणा GRF_EMMCPHY_CON3		0xc
#घोषणा GRF_EMMCPHY_CON4		0x10
#घोषणा GRF_EMMCPHY_CON5		0x14
#घोषणा GRF_EMMCPHY_CON6		0x18
#घोषणा GRF_EMMCPHY_STATUS		0x20

#घोषणा PHYCTRL_PDB_MASK		0x1
#घोषणा PHYCTRL_PDB_SHIFT		0x0
#घोषणा PHYCTRL_PDB_PWR_ON		0x1
#घोषणा PHYCTRL_PDB_PWR_OFF		0x0
#घोषणा PHYCTRL_ENDLL_MASK		0x1
#घोषणा PHYCTRL_ENDLL_SHIFT		0x1
#घोषणा PHYCTRL_ENDLL_ENABLE		0x1
#घोषणा PHYCTRL_ENDLL_DISABLE		0x0
#घोषणा PHYCTRL_CALDONE_MASK		0x1
#घोषणा PHYCTRL_CALDONE_SHIFT		0x6
#घोषणा PHYCTRL_CALDONE_DONE		0x1
#घोषणा PHYCTRL_CALDONE_GOING		0x0
#घोषणा PHYCTRL_DLLRDY_MASK		0x1
#घोषणा PHYCTRL_DLLRDY_SHIFT		0x5
#घोषणा PHYCTRL_DLLRDY_DONE		0x1
#घोषणा PHYCTRL_DLLRDY_GOING		0x0
#घोषणा PHYCTRL_FREQSEL_200M		0x0
#घोषणा PHYCTRL_FREQSEL_50M		0x1
#घोषणा PHYCTRL_FREQSEL_100M		0x2
#घोषणा PHYCTRL_FREQSEL_150M		0x3
#घोषणा PHYCTRL_FREQSEL_MASK		0x3
#घोषणा PHYCTRL_FREQSEL_SHIFT		0xc
#घोषणा PHYCTRL_DR_MASK			0x7
#घोषणा PHYCTRL_DR_SHIFT		0x4
#घोषणा PHYCTRL_DR_50OHM		0x0
#घोषणा PHYCTRL_DR_33OHM		0x1
#घोषणा PHYCTRL_DR_66OHM		0x2
#घोषणा PHYCTRL_DR_100OHM		0x3
#घोषणा PHYCTRL_DR_40OHM		0x4
#घोषणा PHYCTRL_OTAPDLYENA		0x1
#घोषणा PHYCTRL_OTAPDLYENA_MASK		0x1
#घोषणा PHYCTRL_OTAPDLYENA_SHIFT	0xb
#घोषणा PHYCTRL_OTAPDLYSEL_DEFAULT	0x4
#घोषणा PHYCTRL_OTAPDLYSEL_MAXVALUE	0xf
#घोषणा PHYCTRL_OTAPDLYSEL_MASK		0xf
#घोषणा PHYCTRL_OTAPDLYSEL_SHIFT	0x7
#घोषणा PHYCTRL_REN_STRB_DISABLE	0x0
#घोषणा PHYCTRL_REN_STRB_ENABLE		0x1
#घोषणा PHYCTRL_REN_STRB_MASK		0x1
#घोषणा PHYCTRL_REN_STRB_SHIFT		0x9

#घोषणा PHYCTRL_IS_CALDONE(x) \
	((((x) >> PHYCTRL_CALDONE_SHIFT) & \
	  PHYCTRL_CALDONE_MASK) == PHYCTRL_CALDONE_DONE)
#घोषणा PHYCTRL_IS_DLLRDY(x) \
	((((x) >> PHYCTRL_DLLRDY_SHIFT) & \
	  PHYCTRL_DLLRDY_MASK) == PHYCTRL_DLLRDY_DONE)

काष्ठा rockchip_emmc_phy अणु
	अचिन्हित पूर्णांक	reg_offset;
	काष्ठा regmap	*reg_base;
	काष्ठा clk	*emmcclk;
	अचिन्हित पूर्णांक drive_impedance;
	अचिन्हित पूर्णांक enable_strobe_pullकरोwn;
	अचिन्हित पूर्णांक output_tapdelay_select;
पूर्ण;

अटल पूर्णांक rockchip_emmc_phy_घातer(काष्ठा phy *phy, bool on_off)
अणु
	काष्ठा rockchip_emmc_phy *rk_phy = phy_get_drvdata(phy);
	अचिन्हित पूर्णांक calकरोne;
	अचिन्हित पूर्णांक dllrdy;
	अचिन्हित पूर्णांक freqsel = PHYCTRL_FREQSEL_200M;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	/*
	 * Keep phyctrl_pdb and phyctrl_endll low to allow
	 * initialization of CALIO state M/C DFFs
	 */
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON6,
		     HIWORD_UPDATE(PHYCTRL_PDB_PWR_OFF,
				   PHYCTRL_PDB_MASK,
				   PHYCTRL_PDB_SHIFT));
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON6,
		     HIWORD_UPDATE(PHYCTRL_ENDLL_DISABLE,
				   PHYCTRL_ENDLL_MASK,
				   PHYCTRL_ENDLL_SHIFT));

	/* Alपढ़ोy finish घातer_off above */
	अगर (on_off == PHYCTRL_PDB_PWR_OFF)
		वापस 0;

	rate = clk_get_rate(rk_phy->emmcclk);

	अगर (rate != 0) अणु
		अचिन्हित दीर्घ ideal_rate;
		अचिन्हित दीर्घ dअगरf;

		चयन (rate) अणु
		हाल 1 ... 74999999:
			ideal_rate = 50000000;
			freqsel = PHYCTRL_FREQSEL_50M;
			अवरोध;
		हाल 75000000 ... 124999999:
			ideal_rate = 100000000;
			freqsel = PHYCTRL_FREQSEL_100M;
			अवरोध;
		हाल 125000000 ... 174999999:
			ideal_rate = 150000000;
			freqsel = PHYCTRL_FREQSEL_150M;
			अवरोध;
		शेष:
			ideal_rate = 200000000;
			अवरोध;
		पूर्ण

		dअगरf = (rate > ideal_rate) ?
			rate - ideal_rate : ideal_rate - rate;

		/*
		 * In order क्रम tuning delays to be accurate we need to be
		 * pretty spot on क्रम the DLL range, so warn अगर we're too
		 * far off.  Also warn अगर we're above the 200 MHz max.  Don't
		 * warn क्रम really slow rates since we won't be tuning then.
		 */
		अगर ((rate > 50000000 && dअगरf > 15000000) || (rate > 200000000))
			dev_warn(&phy->dev, "Unsupported rate: %lu\n", rate);
	पूर्ण

	/*
	 * According to the user manual, calpad calibration
	 * cycle takes more than 2us without the minimal recommended
	 * value, so we may need a little margin here
	 */
	udelay(3);
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON6,
		     HIWORD_UPDATE(PHYCTRL_PDB_PWR_ON,
				   PHYCTRL_PDB_MASK,
				   PHYCTRL_PDB_SHIFT));

	/*
	 * According to the user manual, it asks driver to रुको 5us क्रम
	 * calpad busy trimming. However it is करोcumented that this value is
	 * PVT(A.K.A process,voltage and temperature) relevant, so some
	 * failure हालs are found which indicates we should be more tolerant
	 * to calpad busy trimming.
	 */
	ret = regmap_पढ़ो_poll_समयout(rk_phy->reg_base,
				       rk_phy->reg_offset + GRF_EMMCPHY_STATUS,
				       calकरोne, PHYCTRL_IS_CALDONE(calकरोne),
				       0, 50);
	अगर (ret) अणु
		pr_err("%s: caldone failed, ret=%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	/* Set the frequency of the DLL operation */
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON0,
		     HIWORD_UPDATE(freqsel, PHYCTRL_FREQSEL_MASK,
				   PHYCTRL_FREQSEL_SHIFT));

	/* Turn on the DLL */
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON6,
		     HIWORD_UPDATE(PHYCTRL_ENDLL_ENABLE,
				   PHYCTRL_ENDLL_MASK,
				   PHYCTRL_ENDLL_SHIFT));

	/*
	 * We turned on the DLL even though the rate was 0 because we the
	 * घड़ी might be turned on later.  ...but we can't रुको क्रम the DLL
	 * to lock when the rate is 0 because it will never lock with no
	 * input घड़ी.
	 *
	 * Technically we should be checking the lock later when the घड़ी
	 * is turned on, but क्रम now we won't.
	 */
	अगर (rate == 0)
		वापस 0;

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
	ret = regmap_पढ़ो_poll_समयout(rk_phy->reg_base,
				       rk_phy->reg_offset + GRF_EMMCPHY_STATUS,
				       dllrdy, PHYCTRL_IS_DLLRDY(dllrdy),
				       0, 50 * USEC_PER_MSEC);
	अगर (ret) अणु
		pr_err("%s: dllrdy failed. ret=%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_emmc_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_emmc_phy *rk_phy = phy_get_drvdata(phy);
	पूर्णांक ret = 0;

	/*
	 * We purposely get the घड़ी here and not in probe to aव्योम the
	 * circular dependency problem.  We expect:
	 * - PHY driver to probe
	 * - SDHCI driver to start probe
	 * - SDHCI driver to रेजिस्टर it's घड़ी
	 * - SDHCI driver to get the PHY
	 * - SDHCI driver to init the PHY
	 *
	 * The घड़ी is optional, using clk_get_optional() to get the घड़ी
	 * and करो error processing अगर the वापस value != शून्य
	 *
	 * NOTE: we करोn't करो anything special क्रम EPROBE_DEFER here.  Given the
	 * above expected use हाल, EPROBE_DEFER isn't sensible to expect, so
	 * it's just like any other error.
	 */
	rk_phy->emmcclk = clk_get_optional(&phy->dev, "emmcclk");
	अगर (IS_ERR(rk_phy->emmcclk)) अणु
		ret = PTR_ERR(rk_phy->emmcclk);
		dev_err(&phy->dev, "Error getting emmcclk: %d\n", ret);
		rk_phy->emmcclk = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_emmc_phy_निकास(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_emmc_phy *rk_phy = phy_get_drvdata(phy);

	clk_put(rk_phy->emmcclk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_emmc_phy_घातer_off(काष्ठा phy *phy)
अणु
	/* Power करोwn emmc phy analog blocks */
	वापस rockchip_emmc_phy_घातer(phy, PHYCTRL_PDB_PWR_OFF);
पूर्ण

अटल पूर्णांक rockchip_emmc_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा rockchip_emmc_phy *rk_phy = phy_get_drvdata(phy);

	/* Drive impedance: from DTS */
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON6,
		     HIWORD_UPDATE(rk_phy->drive_impedance,
				   PHYCTRL_DR_MASK,
				   PHYCTRL_DR_SHIFT));

	/* Output tap delay: enable */
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON0,
		     HIWORD_UPDATE(PHYCTRL_OTAPDLYENA,
				   PHYCTRL_OTAPDLYENA_MASK,
				   PHYCTRL_OTAPDLYENA_SHIFT));

	/* Output tap delay */
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON0,
		     HIWORD_UPDATE(rk_phy->output_tapdelay_select,
				   PHYCTRL_OTAPDLYSEL_MASK,
				   PHYCTRL_OTAPDLYSEL_SHIFT));

	/* Internal pull-करोwn क्रम strobe line */
	regmap_ग_लिखो(rk_phy->reg_base,
		     rk_phy->reg_offset + GRF_EMMCPHY_CON2,
		     HIWORD_UPDATE(rk_phy->enable_strobe_pullकरोwn,
				   PHYCTRL_REN_STRB_MASK,
				   PHYCTRL_REN_STRB_SHIFT));

	/* Power up emmc phy analog blocks */
	वापस rockchip_emmc_phy_घातer(phy, PHYCTRL_PDB_PWR_ON);
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= rockchip_emmc_phy_init,
	.निकास		= rockchip_emmc_phy_निकास,
	.घातer_on	= rockchip_emmc_phy_घातer_on,
	.घातer_off	= rockchip_emmc_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल u32 convert_drive_impedance_ohm(काष्ठा platक्रमm_device *pdev, u32 dr_ohm)
अणु
	चयन (dr_ohm) अणु
	हाल 100:
		वापस PHYCTRL_DR_100OHM;
	हाल 66:
		वापस PHYCTRL_DR_66OHM;
	हाल 50:
		वापस PHYCTRL_DR_50OHM;
	हाल 40:
		वापस PHYCTRL_DR_40OHM;
	हाल 33:
		वापस PHYCTRL_DR_33OHM;
	पूर्ण

	dev_warn(&pdev->dev, "Invalid value %u for drive-impedance-ohm.\n",
		 dr_ohm);
	वापस PHYCTRL_DR_50OHM;
पूर्ण

अटल पूर्णांक rockchip_emmc_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rockchip_emmc_phy *rk_phy;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	काष्ठा regmap *grf;
	अचिन्हित पूर्णांक reg_offset;
	u32 val;

	अगर (!dev->parent || !dev->parent->of_node)
		वापस -ENODEV;

	grf = syscon_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(grf)) अणु
		dev_err(dev, "Missing rockchip,grf property\n");
		वापस PTR_ERR(grf);
	पूर्ण

	rk_phy = devm_kzalloc(dev, माप(*rk_phy), GFP_KERNEL);
	अगर (!rk_phy)
		वापस -ENOMEM;

	अगर (of_property_पढ़ो_u32(dev->of_node, "reg", &reg_offset)) अणु
		dev_err(dev, "missing reg property in node %pOFn\n",
			dev->of_node);
		वापस -EINVAL;
	पूर्ण

	rk_phy->reg_offset = reg_offset;
	rk_phy->reg_base = grf;
	rk_phy->drive_impedance = PHYCTRL_DR_50OHM;
	rk_phy->enable_strobe_pullकरोwn = PHYCTRL_REN_STRB_DISABLE;
	rk_phy->output_tapdelay_select = PHYCTRL_OTAPDLYSEL_DEFAULT;

	अगर (!of_property_पढ़ो_u32(dev->of_node, "drive-impedance-ohm", &val))
		rk_phy->drive_impedance = convert_drive_impedance_ohm(pdev, val);

	अगर (of_property_पढ़ो_bool(dev->of_node, "rockchip,enable-strobe-pulldown"))
		rk_phy->enable_strobe_pullकरोwn = PHYCTRL_REN_STRB_ENABLE;

	अगर (!of_property_पढ़ो_u32(dev->of_node, "rockchip,output-tapdelay-select", &val)) अणु
		अगर (val <= PHYCTRL_OTAPDLYSEL_MAXVALUE)
			rk_phy->output_tapdelay_select = val;
		अन्यथा
			dev_err(dev, "output-tapdelay-select exceeds limit, apply default\n");
	पूर्ण

	generic_phy = devm_phy_create(dev, dev->of_node, &ops);
	अगर (IS_ERR(generic_phy)) अणु
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(generic_phy);
	पूर्ण

	phy_set_drvdata(generic_phy, rk_phy);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);

	वापस PTR_ERR_OR_ZERO(phy_provider);
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_emmc_phy_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk3399-emmc-phy" पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_emmc_phy_dt_ids);

अटल काष्ठा platक्रमm_driver rockchip_emmc_driver = अणु
	.probe		= rockchip_emmc_phy_probe,
	.driver		= अणु
		.name	= "rockchip-emmc-phy",
		.of_match_table = rockchip_emmc_phy_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_emmc_driver);

MODULE_AUTHOR("Shawn Lin <shawn.lin@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip EMMC PHY driver");
MODULE_LICENSE("GPL v2");
