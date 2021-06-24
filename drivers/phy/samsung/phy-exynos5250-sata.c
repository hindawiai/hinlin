<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Samsung SATA SerDes(PHY) driver
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 * Authors: Girish K S <ks.giri@samsung.com>
 *         Yuvaraj Kumar C D <yuvaraj.cd@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mfd/syscon.h>

#घोषणा SATAPHY_CONTROL_OFFSET		0x0724
#घोषणा EXYNOS5_SATAPHY_PMU_ENABLE	BIT(0)
#घोषणा EXYNOS5_SATA_RESET		0x4
#घोषणा RESET_GLOBAL_RST_N		BIT(0)
#घोषणा RESET_CMN_RST_N			BIT(1)
#घोषणा RESET_CMN_BLOCK_RST_N		BIT(2)
#घोषणा RESET_CMN_I2C_RST_N		BIT(3)
#घोषणा RESET_TX_RX_PIPE_RST_N		BIT(4)
#घोषणा RESET_TX_RX_BLOCK_RST_N		BIT(5)
#घोषणा RESET_TX_RX_I2C_RST_N		(BIT(6) | BIT(7))
#घोषणा LINK_RESET			0xf0000
#घोषणा EXYNOS5_SATA_MODE0		0x10
#घोषणा SATA_SPD_GEN3			BIT(1)
#घोषणा EXYNOS5_SATA_CTRL0		0x14
#घोषणा CTRL0_P0_PHY_CALIBRATED_SEL	BIT(9)
#घोषणा CTRL0_P0_PHY_CALIBRATED		BIT(8)
#घोषणा EXYNOS5_SATA_PHSATA_CTRLM	0xe0
#घोषणा PHCTRLM_REF_RATE		BIT(1)
#घोषणा PHCTRLM_HIGH_SPEED		BIT(0)
#घोषणा EXYNOS5_SATA_PHSATA_STATM	0xf0
#घोषणा PHSTATM_PLL_LOCKED		BIT(0)

#घोषणा PHY_PLL_TIMEOUT (usecs_to_jअगरfies(1000))

काष्ठा exynos_sata_phy अणु
	काष्ठा phy *phy;
	काष्ठा clk *phyclk;
	व्योम __iomem *regs;
	काष्ठा regmap *pmureg;
	काष्ठा i2c_client *client;
पूर्ण;

अटल पूर्णांक रुको_क्रम_reg_status(व्योम __iomem *base, u32 reg, u32 checkbit,
				u32 status)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + PHY_PLL_TIMEOUT;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर ((पढ़ोl(base + reg) & checkbit) == status)
			वापस 0;
	पूर्ण

	वापस -EFAULT;
पूर्ण

अटल पूर्णांक exynos_sata_phy_घातer_on(काष्ठा phy *phy)
अणु
	काष्ठा exynos_sata_phy *sata_phy = phy_get_drvdata(phy);

	वापस regmap_update_bits(sata_phy->pmureg, SATAPHY_CONTROL_OFFSET,
			EXYNOS5_SATAPHY_PMU_ENABLE, true);

पूर्ण

अटल पूर्णांक exynos_sata_phy_घातer_off(काष्ठा phy *phy)
अणु
	काष्ठा exynos_sata_phy *sata_phy = phy_get_drvdata(phy);

	वापस regmap_update_bits(sata_phy->pmureg, SATAPHY_CONTROL_OFFSET,
			EXYNOS5_SATAPHY_PMU_ENABLE, false);

पूर्ण

अटल पूर्णांक exynos_sata_phy_init(काष्ठा phy *phy)
अणु
	u32 val = 0;
	पूर्णांक ret = 0;
	u8 buf[] = अणु 0x3a, 0x0b पूर्ण;
	काष्ठा exynos_sata_phy *sata_phy = phy_get_drvdata(phy);

	ret = regmap_update_bits(sata_phy->pmureg, SATAPHY_CONTROL_OFFSET,
			EXYNOS5_SATAPHY_PMU_ENABLE, true);
	अगर (ret != 0)
		dev_err(&sata_phy->phy->dev, "phy init failed\n");

	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= RESET_GLOBAL_RST_N | RESET_CMN_RST_N | RESET_CMN_BLOCK_RST_N
		| RESET_CMN_I2C_RST_N | RESET_TX_RX_PIPE_RST_N
		| RESET_TX_RX_BLOCK_RST_N | RESET_TX_RX_I2C_RST_N;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= LINK_RESET;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= RESET_CMN_RST_N;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);
	val &= ~PHCTRLM_REF_RATE;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);

	/* High speed enable क्रम Gen3 */
	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);
	val |= PHCTRLM_HIGH_SPEED;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_PHSATA_CTRLM);

	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_CTRL0);
	val |= CTRL0_P0_PHY_CALIBRATED_SEL | CTRL0_P0_PHY_CALIBRATED;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_CTRL0);

	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_MODE0);
	val |= SATA_SPD_GEN3;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_MODE0);

	ret = i2c_master_send(sata_phy->client, buf, माप(buf));
	अगर (ret < 0)
		वापस ret;

	/* release cmu reset */
	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val &= ~RESET_CMN_RST_N;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	val = पढ़ोl(sata_phy->regs + EXYNOS5_SATA_RESET);
	val |= RESET_CMN_RST_N;
	ग_लिखोl(val, sata_phy->regs + EXYNOS5_SATA_RESET);

	ret = रुको_क्रम_reg_status(sata_phy->regs,
				EXYNOS5_SATA_PHSATA_STATM,
				PHSTATM_PLL_LOCKED, 1);
	अगर (ret < 0)
		dev_err(&sata_phy->phy->dev,
			"PHY PLL locking failed\n");
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा phy_ops exynos_sata_phy_ops = अणु
	.init		= exynos_sata_phy_init,
	.घातer_on	= exynos_sata_phy_घातer_on,
	.घातer_off	= exynos_sata_phy_घातer_off,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक exynos_sata_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा exynos_sata_phy *sata_phy;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा phy_provider *phy_provider;
	काष्ठा device_node *node;
	पूर्णांक ret = 0;

	sata_phy = devm_kzalloc(dev, माप(*sata_phy), GFP_KERNEL);
	अगर (!sata_phy)
		वापस -ENOMEM;

	sata_phy->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sata_phy->regs))
		वापस PTR_ERR(sata_phy->regs);

	sata_phy->pmureg = syscon_regmap_lookup_by_phandle(dev->of_node,
					"samsung,syscon-phandle");
	अगर (IS_ERR(sata_phy->pmureg)) अणु
		dev_err(dev, "syscon regmap lookup failed.\n");
		वापस PTR_ERR(sata_phy->pmureg);
	पूर्ण

	node = of_parse_phandle(dev->of_node,
			"samsung,exynos-sataphy-i2c-phandle", 0);
	अगर (!node)
		वापस -EINVAL;

	sata_phy->client = of_find_i2c_device_by_node(node);
	अगर (!sata_phy->client)
		वापस -EPROBE_DEFER;

	dev_set_drvdata(dev, sata_phy);

	sata_phy->phyclk = devm_clk_get(dev, "sata_phyctrl");
	अगर (IS_ERR(sata_phy->phyclk)) अणु
		dev_err(dev, "failed to get clk for PHY\n");
		वापस PTR_ERR(sata_phy->phyclk);
	पूर्ण

	ret = clk_prepare_enable(sata_phy->phyclk);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to enable source clk\n");
		वापस ret;
	पूर्ण

	sata_phy->phy = devm_phy_create(dev, शून्य, &exynos_sata_phy_ops);
	अगर (IS_ERR(sata_phy->phy)) अणु
		clk_disable_unprepare(sata_phy->phyclk);
		dev_err(dev, "failed to create PHY\n");
		वापस PTR_ERR(sata_phy->phy);
	पूर्ण

	phy_set_drvdata(sata_phy->phy, sata_phy);

	phy_provider = devm_of_phy_provider_रेजिस्टर(dev,
					of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider)) अणु
		clk_disable_unprepare(sata_phy->phyclk);
		वापस PTR_ERR(phy_provider);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id exynos_sata_phy_of_match[] = अणु
	अणु .compatible = "samsung,exynos5250-sata-phy" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos_sata_phy_of_match);

अटल काष्ठा platक्रमm_driver exynos_sata_phy_driver = अणु
	.probe	= exynos_sata_phy_probe,
	.driver = अणु
		.of_match_table	= exynos_sata_phy_of_match,
		.name  = "samsung,sata-phy",
		.suppress_bind_attrs = true,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(exynos_sata_phy_driver);

MODULE_DESCRIPTION("Samsung SerDes PHY driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Girish K S <ks.giri@samsung.com>");
MODULE_AUTHOR("Yuvaraj C D <yuvaraj.cd@samsung.com>");
