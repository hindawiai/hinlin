<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max77686.c - mfd core driver क्रम the Maxim 77686/802
//
// Copyright (C) 2012 Samsung Electronics
// Chiwoong Byun <woong.byun@samsung.com>
// Jonghwa Lee <jonghwa3.lee@samsung.com>
//
//This driver is based on max8997.c

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max77686.h>
#समावेश <linux/mfd/max77686-निजी.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

अटल स्थिर काष्ठा mfd_cell max77686_devs[] = अणु
	अणु .name = "max77686-pmic", पूर्ण,
	अणु .name = "max77686-rtc", पूर्ण,
	अणु .name = "max77686-clk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell max77802_devs[] = अणु
	अणु .name = "max77802-pmic", पूर्ण,
	अणु .name = "max77802-clk", पूर्ण,
	अणु .name = "max77802-rtc", पूर्ण,
पूर्ण;

अटल bool max77802_pmic_is_accessible_reg(काष्ठा device *dev,
					    अचिन्हित पूर्णांक reg)
अणु
	वापस reg < MAX77802_REG_PMIC_END;
पूर्ण

अटल bool max77802_rtc_is_accessible_reg(काष्ठा device *dev,
					   अचिन्हित पूर्णांक reg)
अणु
	वापस (reg >= MAX77802_RTC_INT && reg < MAX77802_RTC_END);
पूर्ण

अटल bool max77802_is_accessible_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (max77802_pmic_is_accessible_reg(dev, reg) ||
		max77802_rtc_is_accessible_reg(dev, reg));
पूर्ण

अटल bool max77802_pmic_is_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == MAX77802_REG_INTSRC || reg == MAX77802_REG_INT1 ||
		reg == MAX77802_REG_INT2);
पूर्ण

अटल bool max77802_rtc_is_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (reg == MAX77802_RTC_INT ||
		reg == MAX77802_RTC_UPDATE0 ||
		reg == MAX77802_RTC_UPDATE1);
पूर्ण

अटल bool max77802_is_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (max77802_pmic_is_precious_reg(dev, reg) ||
		max77802_rtc_is_precious_reg(dev, reg));
पूर्ण

अटल bool max77802_pmic_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (max77802_is_precious_reg(dev, reg) ||
		reg == MAX77802_REG_STATUS1 || reg == MAX77802_REG_STATUS2 ||
		reg == MAX77802_REG_PWRON);
पूर्ण

अटल bool max77802_rtc_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (max77802_rtc_is_precious_reg(dev, reg) ||
		reg == MAX77802_RTC_SEC ||
		reg == MAX77802_RTC_MIN ||
		reg == MAX77802_RTC_HOUR ||
		reg == MAX77802_RTC_WEEKDAY ||
		reg == MAX77802_RTC_MONTH ||
		reg == MAX77802_RTC_YEAR ||
		reg == MAX77802_RTC_DATE);
पूर्ण

अटल bool max77802_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस (max77802_pmic_is_अस्थिर_reg(dev, reg) ||
		max77802_rtc_is_अस्थिर_reg(dev, reg));
पूर्ण

अटल स्थिर काष्ठा regmap_config max77686_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77802_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखोable_reg = max77802_is_accessible_reg,
	.पढ़ोable_reg = max77802_is_accessible_reg,
	.precious_reg = max77802_is_precious_reg,
	.अस्थिर_reg = max77802_is_अस्थिर_reg,
	.name = "max77802-pmic",
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77686_irqs[] = अणु
	/* INT1 पूर्णांकerrupts */
	अणु .reg_offset = 0, .mask = MAX77686_INT1_PWRONF_MSK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77686_INT1_PWRONR_MSK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77686_INT1_JIGONBF_MSK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77686_INT1_JIGONBR_MSK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77686_INT1_ACOKBF_MSK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77686_INT1_ACOKBR_MSK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77686_INT1_ONKEY1S_MSK, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77686_INT1_MRSTB_MSK, पूर्ण,
	/* INT2 पूर्णांकerrupts */
	अणु .reg_offset = 1, .mask = MAX77686_INT2_140C_MSK, पूर्ण,
	अणु .reg_offset = 1, .mask = MAX77686_INT2_120C_MSK, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77686_irq_chip = अणु
	.name			= "max77686-pmic",
	.status_base		= MAX77686_REG_INT1,
	.mask_base		= MAX77686_REG_INT1MSK,
	.num_regs		= 2,
	.irqs			= max77686_irqs,
	.num_irqs		= ARRAY_SIZE(max77686_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77802_irq_chip = अणु
	.name			= "max77802-pmic",
	.status_base		= MAX77802_REG_INT1,
	.mask_base		= MAX77802_REG_INT1MSK,
	.num_regs		= 2,
	.irqs			= max77686_irqs, /* same masks as 77686 */
	.num_irqs		= ARRAY_SIZE(max77686_irqs),
पूर्ण;

अटल स्थिर काष्ठा of_device_id max77686_pmic_dt_match[] = अणु
	अणु
		.compatible = "maxim,max77686",
		.data = (व्योम *)TYPE_MAX77686,
	पूर्ण,
	अणु
		.compatible = "maxim,max77802",
		.data = (व्योम *)TYPE_MAX77802,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max77686_pmic_dt_match);

अटल पूर्णांक max77686_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा max77686_dev *max77686 = शून्य;
	अचिन्हित पूर्णांक data;
	पूर्णांक ret = 0;
	स्थिर काष्ठा regmap_config *config;
	स्थिर काष्ठा regmap_irq_chip *irq_chip;
	स्थिर काष्ठा mfd_cell *cells;
	पूर्णांक n_devs;

	max77686 = devm_kzalloc(&i2c->dev,
				माप(काष्ठा max77686_dev), GFP_KERNEL);
	अगर (!max77686)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max77686);
	max77686->type = (अचिन्हित दीर्घ)of_device_get_match_data(&i2c->dev);
	max77686->dev = &i2c->dev;
	max77686->i2c = i2c;

	max77686->irq = i2c->irq;

	अगर (max77686->type == TYPE_MAX77686) अणु
		config = &max77686_regmap_config;
		irq_chip = &max77686_irq_chip;
		cells =  max77686_devs;
		n_devs = ARRAY_SIZE(max77686_devs);
	पूर्ण अन्यथा अणु
		config = &max77802_regmap_config;
		irq_chip = &max77802_irq_chip;
		cells =  max77802_devs;
		n_devs = ARRAY_SIZE(max77802_devs);
	पूर्ण

	max77686->regmap = devm_regmap_init_i2c(i2c, config);
	अगर (IS_ERR(max77686->regmap)) अणु
		ret = PTR_ERR(max77686->regmap);
		dev_err(max77686->dev, "Failed to allocate register map: %d\n",
				ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(max77686->regmap, MAX77686_REG_DEVICE_ID, &data);
	अगर (ret < 0) अणु
		dev_err(max77686->dev,
			"device not found on this channel (this is not an error)\n");
		वापस -ENODEV;
	पूर्ण

	ret = devm_regmap_add_irq_chip(&i2c->dev, max77686->regmap,
				       max77686->irq,
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT |
				       IRQF_SHARED, 0, irq_chip,
				       &max77686->irq_data);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "failed to add PMIC irq chip: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(max77686->dev, -1, cells, n_devs, शून्य,
				   0, शून्य);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "failed to add MFD devices: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक max77686_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max77686_dev *max77686 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		enable_irq_wake(max77686->irq);

	/*
	 * IRQ must be disabled during suspend because अगर it happens
	 * जबतक suspended it will be handled beक्रमe resuming I2C.
	 *
	 * When device is woken up from suspend (e.g. by RTC wake alarm),
	 * an पूर्णांकerrupt occurs beक्रमe resuming I2C bus controller.
	 * Interrupt handler tries to पढ़ो रेजिस्टरs but this पढ़ो
	 * will fail because I2C is still suspended.
	 */
	disable_irq(max77686->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक max77686_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max77686_dev *max77686 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(max77686->irq);

	enable_irq(max77686->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(max77686_pm, max77686_suspend, max77686_resume);

अटल काष्ठा i2c_driver max77686_i2c_driver = अणु
	.driver = अणु
		   .name = "max77686",
		   .pm = &max77686_pm,
		   .of_match_table = max77686_pmic_dt_match,
	पूर्ण,
	.probe_new = max77686_i2c_probe,
पूर्ण;

module_i2c_driver(max77686_i2c_driver);

MODULE_DESCRIPTION("MAXIM 77686/802 multi-function core driver");
MODULE_AUTHOR("Chiwoong Byun <woong.byun@samsung.com>");
MODULE_LICENSE("GPL");
