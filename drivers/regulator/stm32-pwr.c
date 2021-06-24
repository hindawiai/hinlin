<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) STMicroelectronics 2019
// Authors: Gabriel Fernandez <gabriel.fernandez@st.com>
//          Pascal Paillet <p.paillet@st.com>.

#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

/*
 * Registers description
 */
#घोषणा REG_PWR_CR3 0x0C

#घोषणा USB_3_3_EN BIT(24)
#घोषणा USB_3_3_RDY BIT(26)
#घोषणा REG_1_8_EN BIT(28)
#घोषणा REG_1_8_RDY BIT(29)
#घोषणा REG_1_1_EN BIT(30)
#घोषणा REG_1_1_RDY BIT(31)

/* list of supported regulators */
क्रमागत अणु
	PWR_REG11,
	PWR_REG18,
	PWR_USB33,
	STM32PWR_REG_NUM_REGS
पूर्ण;

अटल u32 पढ़ोy_mask_table[STM32PWR_REG_NUM_REGS] = अणु
	[PWR_REG11] = REG_1_1_RDY,
	[PWR_REG18] = REG_1_8_RDY,
	[PWR_USB33] = USB_3_3_RDY,
पूर्ण;

काष्ठा sपंचांग32_pwr_reg अणु
	व्योम __iomem *base;
	u32 पढ़ोy_mask;
पूर्ण;

अटल पूर्णांक sपंचांग32_pwr_reg_is_पढ़ोy(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_pwr_reg *priv = rdev_get_drvdata(rdev);
	u32 val;

	val = पढ़ोl_relaxed(priv->base + REG_PWR_CR3);

	वापस (val & priv->पढ़ोy_mask);
पूर्ण

अटल पूर्णांक sपंचांग32_pwr_reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_pwr_reg *priv = rdev_get_drvdata(rdev);
	u32 val;

	val = पढ़ोl_relaxed(priv->base + REG_PWR_CR3);

	वापस (val & rdev->desc->enable_mask);
पूर्ण

अटल पूर्णांक sपंचांग32_pwr_reg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_pwr_reg *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	u32 val;

	val = पढ़ोl_relaxed(priv->base + REG_PWR_CR3);
	val |= rdev->desc->enable_mask;
	ग_लिखोl_relaxed(val, priv->base + REG_PWR_CR3);

	/* use an arbitrary समयout of 20ms */
	ret = पढ़ोx_poll_समयout(sपंचांग32_pwr_reg_is_पढ़ोy, rdev, val, val,
				 100, 20 * 1000);
	अगर (ret)
		dev_err(&rdev->dev, "regulator enable timed out!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_pwr_reg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा sपंचांग32_pwr_reg *priv = rdev_get_drvdata(rdev);
	पूर्णांक ret;
	u32 val;

	val = पढ़ोl_relaxed(priv->base + REG_PWR_CR3);
	val &= ~rdev->desc->enable_mask;
	ग_लिखोl_relaxed(val, priv->base + REG_PWR_CR3);

	/* use an arbitrary समयout of 20ms */
	ret = पढ़ोx_poll_समयout(sपंचांग32_pwr_reg_is_पढ़ोy, rdev, val, !val,
				 100, 20 * 1000);
	अगर (ret)
		dev_err(&rdev->dev, "regulator disable timed out!\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops sपंचांग32_pwr_reg_ops = अणु
	.enable		= sपंचांग32_pwr_reg_enable,
	.disable	= sपंचांग32_pwr_reg_disable,
	.is_enabled	= sपंचांग32_pwr_reg_is_enabled,
पूर्ण;

#घोषणा PWR_REG(_id, _name, _volt, _en, _supply) \
	[_id] = अणु \
		.id = _id, \
		.name = _name, \
		.of_match = of_match_ptr(_name), \
		.n_voltages = 1, \
		.type = REGULATOR_VOLTAGE, \
		.fixed_uV = _volt, \
		.ops = &sपंचांग32_pwr_reg_ops, \
		.enable_mask = _en, \
		.owner = THIS_MODULE, \
		.supply_name = _supply, \
	पूर्ण \

अटल स्थिर काष्ठा regulator_desc sपंचांग32_pwr_desc[] = अणु
	PWR_REG(PWR_REG11, "reg11", 1100000, REG_1_1_EN, "vdd"),
	PWR_REG(PWR_REG18, "reg18", 1800000, REG_1_8_EN, "vdd"),
	PWR_REG(PWR_USB33, "usb33", 3300000, USB_3_3_EN, "vdd_3v3_usbfs"),
पूर्ण;

अटल पूर्णांक sपंचांग32_pwr_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sपंचांग32_pwr_reg *priv;
	व्योम __iomem *base;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक i, ret = 0;

	base = of_iomap(np, 0);
	अगर (!base) अणु
		dev_err(&pdev->dev, "Unable to map IO memory\n");
		वापस -ENOMEM;
	पूर्ण

	config.dev = &pdev->dev;

	क्रम (i = 0; i < STM32PWR_REG_NUM_REGS; i++) अणु
		priv = devm_kzalloc(&pdev->dev, माप(काष्ठा sपंचांग32_pwr_reg),
				    GFP_KERNEL);
		अगर (!priv)
			वापस -ENOMEM;
		priv->base = base;
		priv->पढ़ोy_mask = पढ़ोy_mask_table[i];
		config.driver_data = priv;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
					       &sपंचांग32_pwr_desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(&pdev->dev,
				"Failed to register regulator: %d\n", ret);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused sपंचांग32_pwr_of_match[] = अणु
	अणु .compatible = "st,stm32mp1,pwr-reg", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_pwr_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_pwr_driver = अणु
	.probe = sपंचांग32_pwr_regulator_probe,
	.driver = अणु
		.name  = "stm32-pwr-regulator",
		.of_match_table = of_match_ptr(sपंचांग32_pwr_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_pwr_driver);

MODULE_DESCRIPTION("STM32MP1 PWR voltage regulator driver");
MODULE_AUTHOR("Pascal Paillet <p.paillet@st.com>");
MODULE_LICENSE("GPL v2");
