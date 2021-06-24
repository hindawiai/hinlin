<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) STMicroelectronics 2018
// Author: Pascal Paillet <p.paillet@st.com>

#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/stpmic1.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/mfd/st,stpmic1.h>

#घोषणा STPMIC1_MAIN_IRQ 0

अटल स्थिर काष्ठा regmap_range stpmic1_पढ़ोable_ranges[] = अणु
	regmap_reg_range(TURN_ON_SR, VERSION_SR),
	regmap_reg_range(SWOFF_PWRCTRL_CR, LDO6_STDBY_CR),
	regmap_reg_range(BST_SW_CR, BST_SW_CR),
	regmap_reg_range(INT_PENDING_R1, INT_PENDING_R4),
	regmap_reg_range(INT_CLEAR_R1, INT_CLEAR_R4),
	regmap_reg_range(INT_MASK_R1, INT_MASK_R4),
	regmap_reg_range(INT_SET_MASK_R1, INT_SET_MASK_R4),
	regmap_reg_range(INT_CLEAR_MASK_R1, INT_CLEAR_MASK_R4),
	regmap_reg_range(INT_SRC_R1, INT_SRC_R1),
पूर्ण;

अटल स्थिर काष्ठा regmap_range stpmic1_ग_लिखोable_ranges[] = अणु
	regmap_reg_range(SWOFF_PWRCTRL_CR, LDO6_STDBY_CR),
	regmap_reg_range(BST_SW_CR, BST_SW_CR),
	regmap_reg_range(INT_CLEAR_R1, INT_CLEAR_R4),
	regmap_reg_range(INT_SET_MASK_R1, INT_SET_MASK_R4),
	regmap_reg_range(INT_CLEAR_MASK_R1, INT_CLEAR_MASK_R4),
पूर्ण;

अटल स्थिर काष्ठा regmap_range stpmic1_अस्थिर_ranges[] = अणु
	regmap_reg_range(TURN_ON_SR, VERSION_SR),
	regmap_reg_range(WCHDG_CR, WCHDG_CR),
	regmap_reg_range(INT_PENDING_R1, INT_PENDING_R4),
	regmap_reg_range(INT_SRC_R1, INT_SRC_R4),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table stpmic1_पढ़ोable_table = अणु
	.yes_ranges = stpmic1_पढ़ोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(stpmic1_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table stpmic1_ग_लिखोable_table = अणु
	.yes_ranges = stpmic1_ग_लिखोable_ranges,
	.n_yes_ranges = ARRAY_SIZE(stpmic1_ग_लिखोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table stpmic1_अस्थिर_table = अणु
	.yes_ranges = stpmic1_अस्थिर_ranges,
	.n_yes_ranges = ARRAY_SIZE(stpmic1_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config stpmic1_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.max_रेजिस्टर = PMIC_MAX_REGISTER_ADDRESS,
	.rd_table = &stpmic1_पढ़ोable_table,
	.wr_table = &stpmic1_ग_लिखोable_table,
	.अस्थिर_table = &stpmic1_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq stpmic1_irqs[] = अणु
	REGMAP_IRQ_REG(IT_PONKEY_F, 0, 0x01),
	REGMAP_IRQ_REG(IT_PONKEY_R, 0, 0x02),
	REGMAP_IRQ_REG(IT_WAKEUP_F, 0, 0x04),
	REGMAP_IRQ_REG(IT_WAKEUP_R, 0, 0x08),
	REGMAP_IRQ_REG(IT_VBUS_OTG_F, 0, 0x10),
	REGMAP_IRQ_REG(IT_VBUS_OTG_R, 0, 0x20),
	REGMAP_IRQ_REG(IT_SWOUT_F, 0, 0x40),
	REGMAP_IRQ_REG(IT_SWOUT_R, 0, 0x80),

	REGMAP_IRQ_REG(IT_CURLIM_BUCK1, 1, 0x01),
	REGMAP_IRQ_REG(IT_CURLIM_BUCK2, 1, 0x02),
	REGMAP_IRQ_REG(IT_CURLIM_BUCK3, 1, 0x04),
	REGMAP_IRQ_REG(IT_CURLIM_BUCK4, 1, 0x08),
	REGMAP_IRQ_REG(IT_OCP_OTG, 1, 0x10),
	REGMAP_IRQ_REG(IT_OCP_SWOUT, 1, 0x20),
	REGMAP_IRQ_REG(IT_OCP_BOOST, 1, 0x40),
	REGMAP_IRQ_REG(IT_OVP_BOOST, 1, 0x80),

	REGMAP_IRQ_REG(IT_CURLIM_LDO1, 2, 0x01),
	REGMAP_IRQ_REG(IT_CURLIM_LDO2, 2, 0x02),
	REGMAP_IRQ_REG(IT_CURLIM_LDO3, 2, 0x04),
	REGMAP_IRQ_REG(IT_CURLIM_LDO4, 2, 0x08),
	REGMAP_IRQ_REG(IT_CURLIM_LDO5, 2, 0x10),
	REGMAP_IRQ_REG(IT_CURLIM_LDO6, 2, 0x20),
	REGMAP_IRQ_REG(IT_SHORT_SWOTG, 2, 0x40),
	REGMAP_IRQ_REG(IT_SHORT_SWOUT, 2, 0x80),

	REGMAP_IRQ_REG(IT_TWARN_F, 3, 0x01),
	REGMAP_IRQ_REG(IT_TWARN_R, 3, 0x02),
	REGMAP_IRQ_REG(IT_VINLOW_F, 3, 0x04),
	REGMAP_IRQ_REG(IT_VINLOW_R, 3, 0x08),
	REGMAP_IRQ_REG(IT_SWIN_F, 3, 0x40),
	REGMAP_IRQ_REG(IT_SWIN_R, 3, 0x80),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip stpmic1_regmap_irq_chip = अणु
	.name = "pmic_irq",
	.status_base = INT_PENDING_R1,
	.mask_base = INT_CLEAR_MASK_R1,
	.unmask_base = INT_SET_MASK_R1,
	.ack_base = INT_CLEAR_R1,
	.num_regs = STPMIC1_PMIC_NUM_IRQ_REGS,
	.irqs = stpmic1_irqs,
	.num_irqs = ARRAY_SIZE(stpmic1_irqs),
पूर्ण;

अटल पूर्णांक stpmic1_probe(काष्ठा i2c_client *i2c,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा stpmic1 *ddata;
	काष्ठा device *dev = &i2c->dev;
	पूर्णांक ret;
	काष्ठा device_node *np = dev->of_node;
	u32 reg;

	ddata = devm_kzalloc(dev, माप(काष्ठा stpmic1), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, ddata);
	ddata->dev = dev;

	ddata->regmap = devm_regmap_init_i2c(i2c, &stpmic1_regmap_config);
	अगर (IS_ERR(ddata->regmap))
		वापस PTR_ERR(ddata->regmap);

	ddata->irq = of_irq_get(np, STPMIC1_MAIN_IRQ);
	अगर (ddata->irq < 0) अणु
		dev_err(dev, "Failed to get main IRQ: %d\n", ddata->irq);
		वापस ddata->irq;
	पूर्ण

	ret = regmap_पढ़ो(ddata->regmap, VERSION_SR, &reg);
	अगर (ret) अणु
		dev_err(dev, "Unable to read PMIC version\n");
		वापस ret;
	पूर्ण
	dev_info(dev, "PMIC Chip Version: 0x%x\n", reg);

	/* Initialize PMIC IRQ Chip & associated IRQ करोमुख्यs */
	ret = devm_regmap_add_irq_chip(dev, ddata->regmap, ddata->irq,
				       IRQF_ONESHOT | IRQF_SHARED,
				       0, &stpmic1_regmap_irq_chip,
				       &ddata->irq_data);
	अगर (ret) अणु
		dev_err(dev, "IRQ Chip registration failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक stpmic1_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा stpmic1 *pmic_dev = i2c_get_clientdata(i2c);

	disable_irq(pmic_dev->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक stpmic1_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा stpmic1 *pmic_dev = i2c_get_clientdata(i2c);
	पूर्णांक ret;

	ret = regcache_sync(pmic_dev->regmap);
	अगर (ret)
		वापस ret;

	enable_irq(pmic_dev->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(stpmic1_pm, stpmic1_suspend, stpmic1_resume);

अटल स्थिर काष्ठा of_device_id stpmic1_of_match[] = अणु
	अणु .compatible = "st,stpmic1", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stpmic1_of_match);

अटल काष्ठा i2c_driver stpmic1_driver = अणु
	.driver = अणु
		.name = "stpmic1",
		.of_match_table = of_match_ptr(stpmic1_of_match),
		.pm = &stpmic1_pm,
	पूर्ण,
	.probe = stpmic1_probe,
पूर्ण;

module_i2c_driver(stpmic1_driver);

MODULE_DESCRIPTION("STPMIC1 PMIC Driver");
MODULE_AUTHOR("Pascal Paillet <p.paillet@st.com>");
MODULE_LICENSE("GPL v2");
