<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Keem Bay USB PHY driver
 * Copyright (C) 2020 Intel Corporation
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* USS (USB Subप्रणाली) घड़ी control रेजिस्टरs */
#घोषणा USS_CPR_CLK_EN		0x00
#घोषणा USS_CPR_CLK_SET		0x04
#घोषणा USS_CPR_CLK_CLR		0x08
#घोषणा USS_CPR_RST_EN		0x10
#घोषणा USS_CPR_RST_SET		0x14
#घोषणा USS_CPR_RST_CLR		0x18

/* USS घड़ी/reset bit fields */
#घोषणा USS_CPR_PHY_TST		BIT(6)
#घोषणा USS_CPR_LOW_JIT		BIT(5)
#घोषणा USS_CPR_CORE		BIT(4)
#घोषणा USS_CPR_SUSPEND		BIT(3)
#घोषणा USS_CPR_ALT_REF		BIT(2)
#घोषणा USS_CPR_REF		BIT(1)
#घोषणा USS_CPR_SYS		BIT(0)
#घोषणा USS_CPR_MASK		GENMASK(6, 0)

/* USS APB slave रेजिस्टरs */
#घोषणा USS_USB_CTRL_CFG0		0x10
#घोषणा  VCC_RESET_N_MASK		BIT(31)

#घोषणा USS_USB_PHY_CFG0		0x30
#घोषणा  POR_MASK			BIT(15)
#घोषणा  PHY_RESET_MASK			BIT(14)
#घोषणा  PHY_REF_USE_PAD_MASK		BIT(5)

#घोषणा USS_USB_PHY_CFG6		0x64
#घोषणा  PHY0_SRAM_EXT_LD_DONE_MASK	BIT(23)

#घोषणा USS_USB_PARALLEL_IF_CTRL	0xa0
#घोषणा  USB_PHY_CR_PARA_SEL_MASK	BIT(2)

#घोषणा USS_USB_TSET_SIGNALS_AND_GLOB	0xac
#घोषणा  USB_PHY_CR_PARA_CLK_EN_MASK	BIT(7)

#घोषणा USS_USB_STATUS_REG		0xb8
#घोषणा  PHY0_SRAM_INIT_DONE_MASK	BIT(3)

#घोषणा USS_USB_TIखातापूर्णFS_CONSTANTS_REG1	0xc0
#घोषणा  IDDQ_ENABLE_MASK		BIT(10)

काष्ठा keembay_usb_phy अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap_cpr;
	काष्ठा regmap *regmap_slv;
पूर्ण;

अटल स्थिर काष्ठा regmap_config keembay_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = USS_USB_TIखातापूर्णFS_CONSTANTS_REG1,
पूर्ण;

अटल पूर्णांक keembay_usb_घड़ीs_on(काष्ठा keembay_usb_phy *priv)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap_cpr, USS_CPR_CLK_SET,
				 USS_CPR_MASK, USS_CPR_MASK);
	अगर (ret) अणु
		dev_err(priv->dev, "error clock set: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(priv->regmap_cpr, USS_CPR_RST_SET,
				 USS_CPR_MASK, USS_CPR_MASK);
	अगर (ret) अणु
		dev_err(priv->dev, "error reset set: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(priv->regmap_slv,
				 USS_USB_TIखातापूर्णFS_CONSTANTS_REG1,
				 IDDQ_ENABLE_MASK,
				 FIELD_PREP(IDDQ_ENABLE_MASK, 0));
	अगर (ret) अणु
		dev_err(priv->dev, "error iddq disable: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Wait 30us to ensure all analog blocks are घातered up. */
	usleep_range(30, 60);

	ret = regmap_update_bits(priv->regmap_slv, USS_USB_PHY_CFG0,
				 PHY_REF_USE_PAD_MASK,
				 FIELD_PREP(PHY_REF_USE_PAD_MASK, 1));
	अगर (ret)
		dev_err(priv->dev, "error ref clock select: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक keembay_usb_core_off(काष्ठा keembay_usb_phy *priv)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap_slv, USS_USB_CTRL_CFG0,
				 VCC_RESET_N_MASK,
				 FIELD_PREP(VCC_RESET_N_MASK, 0));
	अगर (ret)
		dev_err(priv->dev, "error core reset: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक keembay_usb_core_on(काष्ठा keembay_usb_phy *priv)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap_slv, USS_USB_CTRL_CFG0,
				 VCC_RESET_N_MASK,
				 FIELD_PREP(VCC_RESET_N_MASK, 1));
	अगर (ret)
		dev_err(priv->dev, "error core on: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक keembay_usb_phys_on(काष्ठा keembay_usb_phy *priv)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(priv->regmap_slv, USS_USB_PHY_CFG0,
				 POR_MASK | PHY_RESET_MASK,
				 FIELD_PREP(POR_MASK | PHY_RESET_MASK, 0));
	अगर (ret)
		dev_err(priv->dev, "error phys on: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक keembay_usb_phy_init(काष्ठा phy *phy)
अणु
	काष्ठा keembay_usb_phy *priv = phy_get_drvdata(phy);
	u32 val;
	पूर्णांक ret;

	ret = keembay_usb_core_off(priv);
	अगर (ret)
		वापस ret;

	/*
	 * According to Keem Bay datasheet, रुको minimum 20us after घड़ी
	 * enable beक्रमe bringing PHYs out of reset.
	 */
	usleep_range(20, 40);

	ret = keembay_usb_phys_on(priv);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(priv->regmap_slv,
				 USS_USB_TSET_SIGNALS_AND_GLOB,
				 USB_PHY_CR_PARA_CLK_EN_MASK,
				 FIELD_PREP(USB_PHY_CR_PARA_CLK_EN_MASK, 0));
	अगर (ret) अणु
		dev_err(priv->dev, "error cr clock disable: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * According to Keem Bay datasheet, रुको 2us after disabling the
	 * घड़ी पूर्णांकo the USB 3.x parallel पूर्णांकerface.
	 */
	udelay(2);

	ret = regmap_update_bits(priv->regmap_slv,
				 USS_USB_PARALLEL_IF_CTRL,
				 USB_PHY_CR_PARA_SEL_MASK,
				 FIELD_PREP(USB_PHY_CR_PARA_SEL_MASK, 1));
	अगर (ret) अणु
		dev_err(priv->dev, "error cr select: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(priv->regmap_slv,
				 USS_USB_TSET_SIGNALS_AND_GLOB,
				 USB_PHY_CR_PARA_CLK_EN_MASK,
				 FIELD_PREP(USB_PHY_CR_PARA_CLK_EN_MASK, 1));
	अगर (ret) अणु
		dev_err(priv->dev, "error cr clock enable: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो_poll_समयout(priv->regmap_slv, USS_USB_STATUS_REG,
				       val, val & PHY0_SRAM_INIT_DONE_MASK,
				       USEC_PER_MSEC, 10 * USEC_PER_MSEC);
	अगर (ret) अणु
		dev_err(priv->dev, "SRAM init not done: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(priv->regmap_slv, USS_USB_PHY_CFG6,
				 PHY0_SRAM_EXT_LD_DONE_MASK,
				 FIELD_PREP(PHY0_SRAM_EXT_LD_DONE_MASK, 1));
	अगर (ret) अणु
		dev_err(priv->dev, "error SRAM init done set: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * According to Keem Bay datasheet, रुको 20us after setting the
	 * SRAM load करोne bit, beक्रमe releasing the controller reset.
	 */
	usleep_range(20, 40);

	वापस keembay_usb_core_on(priv);
पूर्ण

अटल स्थिर काष्ठा phy_ops ops = अणु
	.init		= keembay_usb_phy_init,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक keembay_usb_phy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा keembay_usb_phy *priv;
	काष्ठा phy *generic_phy;
	काष्ठा phy_provider *phy_provider;
	व्योम __iomem *base;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource_byname(pdev, "cpr-apb-base");
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap_cpr = devm_regmap_init_mmio(dev, base,
						 &keembay_regmap_config);
	अगर (IS_ERR(priv->regmap_cpr))
		वापस PTR_ERR(priv->regmap_cpr);

	base = devm_platक्रमm_ioremap_resource_byname(pdev, "slv-apb-base");
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	priv->regmap_slv = devm_regmap_init_mmio(dev, base,
						 &keembay_regmap_config);
	अगर (IS_ERR(priv->regmap_slv))
		वापस PTR_ERR(priv->regmap_slv);

	generic_phy = devm_phy_create(dev, dev->of_node, &ops);
	अगर (IS_ERR(generic_phy))
		वापस dev_err_probe(dev, PTR_ERR(generic_phy),
				     "failed to create PHY\n");

	phy_set_drvdata(generic_phy, priv);
	phy_provider = devm_of_phy_provider_रेजिस्टर(dev, of_phy_simple_xlate);
	अगर (IS_ERR(phy_provider))
		वापस dev_err_probe(dev, PTR_ERR(phy_provider),
				     "failed to register phy provider\n");

	/* Setup USB subप्रणाली घड़ीs */
	ret = keembay_usb_घड़ीs_on(priv);
	अगर (ret)
		वापस ret;

	/* and turn on the DWC3 core, prior to DWC3 driver init. */
	वापस keembay_usb_core_on(priv);
पूर्ण

अटल स्थिर काष्ठा of_device_id keembay_usb_phy_dt_ids[] = अणु
	अणु .compatible = "intel,keembay-usb-phy" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, keembay_usb_phy_dt_ids);

अटल काष्ठा platक्रमm_driver keembay_usb_phy_driver = अणु
	.probe		= keembay_usb_phy_probe,
	.driver		= अणु
		.name	= "keembay-usb-phy",
		.of_match_table = keembay_usb_phy_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(keembay_usb_phy_driver);

MODULE_AUTHOR("Wan Ahmad Zainie <wan.ahmad.zainie.wan.mohamad@intel.com>");
MODULE_DESCRIPTION("Intel Keem Bay USB PHY driver");
MODULE_LICENSE("GPL v2");
