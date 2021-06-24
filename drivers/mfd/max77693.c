<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max77693.c - mfd core driver क्रम the MAX 77693
//
// Copyright (C) 2012 Samsung Electronics
// SangYoung Son <hello.son@samsung.com>
//
// This program is not provided / owned by Maxim Integrated Products.
//
// This driver is based on max8997.c

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max77693.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77693-निजी.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regmap.h>

#घोषणा I2C_ADDR_PMIC	(0xCC >> 1)	/* Charger, Flash LED */
#घोषणा I2C_ADDR_MUIC	(0x4A >> 1)
#घोषणा I2C_ADDR_HAPTIC	(0x90 >> 1)

अटल स्थिर काष्ठा mfd_cell max77693_devs[] = अणु
	अणु .name = "max77693-pmic", पूर्ण,
	अणु
		.name = "max77693-charger",
		.of_compatible = "maxim,max77693-charger",
	पूर्ण,
	अणु
		.name = "max77693-muic",
		.of_compatible = "maxim,max77693-muic",
	पूर्ण,
	अणु
		.name = "max77693-haptic",
		.of_compatible = "maxim,max77693-haptic",
	पूर्ण,
	अणु
		.name = "max77693-led",
		.of_compatible = "maxim,max77693-led",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77693_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX77693_PMIC_REG_END,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77693_led_irqs[] = अणु
	अणु .mask = LED_IRQ_FLED2_OPEN,  पूर्ण,
	अणु .mask = LED_IRQ_FLED2_SHORT, पूर्ण,
	अणु .mask = LED_IRQ_FLED1_OPEN,  पूर्ण,
	अणु .mask = LED_IRQ_FLED1_SHORT, पूर्ण,
	अणु .mask = LED_IRQ_MAX_FLASH,   पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77693_led_irq_chip = अणु
	.name			= "max77693-led",
	.status_base		= MAX77693_LED_REG_FLASH_INT,
	.mask_base		= MAX77693_LED_REG_FLASH_INT_MASK,
	.mask_invert		= false,
	.num_regs		= 1,
	.irqs			= max77693_led_irqs,
	.num_irqs		= ARRAY_SIZE(max77693_led_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77693_topsys_irqs[] = अणु
	अणु .mask = TOPSYS_IRQ_T120C_INT,  पूर्ण,
	अणु .mask = TOPSYS_IRQ_T140C_INT,  पूर्ण,
	अणु .mask = TOPSYS_IRQ_LOWSYS_INT, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77693_topsys_irq_chip = अणु
	.name			= "max77693-topsys",
	.status_base		= MAX77693_PMIC_REG_TOPSYS_INT,
	.mask_base		= MAX77693_PMIC_REG_TOPSYS_INT_MASK,
	.mask_invert		= false,
	.num_regs		= 1,
	.irqs			= max77693_topsys_irqs,
	.num_irqs		= ARRAY_SIZE(max77693_topsys_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77693_अक्षरger_irqs[] = अणु
	अणु .mask = CHG_IRQ_BYP_I,   पूर्ण,
	अणु .mask = CHG_IRQ_THM_I,   पूर्ण,
	अणु .mask = CHG_IRQ_BAT_I,   पूर्ण,
	अणु .mask = CHG_IRQ_CHG_I,   पूर्ण,
	अणु .mask = CHG_IRQ_CHGIN_I, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77693_अक्षरger_irq_chip = अणु
	.name			= "max77693-charger",
	.status_base		= MAX77693_CHG_REG_CHG_INT,
	.mask_base		= MAX77693_CHG_REG_CHG_INT_MASK,
	.mask_invert		= false,
	.num_regs		= 1,
	.irqs			= max77693_अक्षरger_irqs,
	.num_irqs		= ARRAY_SIZE(max77693_अक्षरger_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77693_regmap_muic_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX77693_MUIC_REG_END,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77693_muic_irqs[] = अणु
	अणु .reg_offset = 0, .mask = MUIC_IRQ_INT1_ADC,		पूर्ण,
	अणु .reg_offset = 0, .mask = MUIC_IRQ_INT1_ADC_LOW,	पूर्ण,
	अणु .reg_offset = 0, .mask = MUIC_IRQ_INT1_ADC_ERR,	पूर्ण,
	अणु .reg_offset = 0, .mask = MUIC_IRQ_INT1_ADC1K,		पूर्ण,

	अणु .reg_offset = 1, .mask = MUIC_IRQ_INT2_CHGTYP,	पूर्ण,
	अणु .reg_offset = 1, .mask = MUIC_IRQ_INT2_CHGDETREUN,	पूर्ण,
	अणु .reg_offset = 1, .mask = MUIC_IRQ_INT2_DCDTMR,	पूर्ण,
	अणु .reg_offset = 1, .mask = MUIC_IRQ_INT2_DXOVP,		पूर्ण,
	अणु .reg_offset = 1, .mask = MUIC_IRQ_INT2_VBVOLT,	पूर्ण,
	अणु .reg_offset = 1, .mask = MUIC_IRQ_INT2_VIDRM,		पूर्ण,

	अणु .reg_offset = 2, .mask = MUIC_IRQ_INT3_EOC,		पूर्ण,
	अणु .reg_offset = 2, .mask = MUIC_IRQ_INT3_CGMBC,		पूर्ण,
	अणु .reg_offset = 2, .mask = MUIC_IRQ_INT3_OVP,		पूर्ण,
	अणु .reg_offset = 2, .mask = MUIC_IRQ_INT3_MBCCHG_ERR,	पूर्ण,
	अणु .reg_offset = 2, .mask = MUIC_IRQ_INT3_CHG_ENABLED,	पूर्ण,
	अणु .reg_offset = 2, .mask = MUIC_IRQ_INT3_BAT_DET,	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77693_muic_irq_chip = अणु
	.name			= "max77693-muic",
	.status_base		= MAX77693_MUIC_REG_INT1,
	.mask_base		= MAX77693_MUIC_REG_INTMASK1,
	.mask_invert		= true,
	.num_regs		= 3,
	.irqs			= max77693_muic_irqs,
	.num_irqs		= ARRAY_SIZE(max77693_muic_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77693_regmap_haptic_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MAX77693_HAPTIC_REG_END,
पूर्ण;

अटल पूर्णांक max77693_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max77693_dev *max77693;
	अचिन्हित पूर्णांक reg_data;
	पूर्णांक ret = 0;

	max77693 = devm_kzalloc(&i2c->dev,
			माप(काष्ठा max77693_dev), GFP_KERNEL);
	अगर (max77693 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max77693);
	max77693->dev = &i2c->dev;
	max77693->i2c = i2c;
	max77693->irq = i2c->irq;
	max77693->type = id->driver_data;

	max77693->regmap = devm_regmap_init_i2c(i2c, &max77693_regmap_config);
	अगर (IS_ERR(max77693->regmap)) अणु
		ret = PTR_ERR(max77693->regmap);
		dev_err(max77693->dev, "failed to allocate register map: %d\n",
				ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(max77693->regmap, MAX77693_PMIC_REG_PMIC_ID2,
				&reg_data);
	अगर (ret < 0) अणु
		dev_err(max77693->dev, "device not found on this channel\n");
		वापस ret;
	पूर्ण अन्यथा
		dev_info(max77693->dev, "device ID: 0x%x\n", reg_data);

	max77693->i2c_muic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_MUIC);
	अगर (IS_ERR(max77693->i2c_muic)) अणु
		dev_err(max77693->dev, "Failed to allocate I2C device for MUIC\n");
		वापस PTR_ERR(max77693->i2c_muic);
	पूर्ण
	i2c_set_clientdata(max77693->i2c_muic, max77693);

	max77693->i2c_haptic = i2c_new_dummy_device(i2c->adapter, I2C_ADDR_HAPTIC);
	अगर (IS_ERR(max77693->i2c_haptic)) अणु
		dev_err(max77693->dev, "Failed to allocate I2C device for Haptic\n");
		ret = PTR_ERR(max77693->i2c_haptic);
		जाओ err_i2c_haptic;
	पूर्ण
	i2c_set_clientdata(max77693->i2c_haptic, max77693);

	max77693->regmap_haptic = devm_regmap_init_i2c(max77693->i2c_haptic,
					&max77693_regmap_haptic_config);
	अगर (IS_ERR(max77693->regmap_haptic)) अणु
		ret = PTR_ERR(max77693->regmap_haptic);
		dev_err(max77693->dev,
			"failed to initialize haptic register map: %d\n", ret);
		जाओ err_regmap;
	पूर्ण

	/*
	 * Initialize रेजिस्टर map क्रम MUIC device because use regmap-muic
	 * instance of MUIC device when irq of max77693 is initialized
	 * beक्रमe call max77693-muic probe() function.
	 */
	max77693->regmap_muic = devm_regmap_init_i2c(max77693->i2c_muic,
					 &max77693_regmap_muic_config);
	अगर (IS_ERR(max77693->regmap_muic)) अणु
		ret = PTR_ERR(max77693->regmap_muic);
		dev_err(max77693->dev,
			"failed to allocate register map: %d\n", ret);
		जाओ err_regmap;
	पूर्ण

	ret = regmap_add_irq_chip(max77693->regmap, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_led_irq_chip,
				&max77693->irq_data_led);
	अगर (ret) अणु
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		जाओ err_regmap;
	पूर्ण

	ret = regmap_add_irq_chip(max77693->regmap, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_topsys_irq_chip,
				&max77693->irq_data_topsys);
	अगर (ret) अणु
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		जाओ err_irq_topsys;
	पूर्ण

	ret = regmap_add_irq_chip(max77693->regmap, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_अक्षरger_irq_chip,
				&max77693->irq_data_chg);
	अगर (ret) अणु
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		जाओ err_irq_अक्षरger;
	पूर्ण

	ret = regmap_add_irq_chip(max77693->regmap_muic, max77693->irq,
				IRQF_ONESHOT | IRQF_SHARED |
				IRQF_TRIGGER_FALLING, 0,
				&max77693_muic_irq_chip,
				&max77693->irq_data_muic);
	अगर (ret) अणु
		dev_err(max77693->dev, "failed to add irq chip: %d\n", ret);
		जाओ err_irq_muic;
	पूर्ण

	/* Unmask पूर्णांकerrupts from all blocks in पूर्णांकerrupt source रेजिस्टर */
	ret = regmap_update_bits(max77693->regmap,
				MAX77693_PMIC_REG_INTSRC_MASK,
				SRC_IRQ_ALL, (अचिन्हित पूर्णांक)~SRC_IRQ_ALL);
	अगर (ret < 0) अणु
		dev_err(max77693->dev,
			"Could not unmask interrupts in INTSRC: %d\n",
			ret);
		जाओ err_पूर्णांकsrc;
	पूर्ण

	pm_runसमय_set_active(max77693->dev);

	ret = mfd_add_devices(max77693->dev, -1, max77693_devs,
			      ARRAY_SIZE(max77693_devs), शून्य, 0, शून्य);
	अगर (ret < 0)
		जाओ err_mfd;

	वापस ret;

err_mfd:
	mfd_हटाओ_devices(max77693->dev);
err_पूर्णांकsrc:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_muic);
err_irq_muic:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_chg);
err_irq_अक्षरger:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_topsys);
err_irq_topsys:
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_led);
err_regmap:
	i2c_unरेजिस्टर_device(max77693->i2c_haptic);
err_i2c_haptic:
	i2c_unरेजिस्टर_device(max77693->i2c_muic);
	वापस ret;
पूर्ण

अटल पूर्णांक max77693_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा max77693_dev *max77693 = i2c_get_clientdata(i2c);

	mfd_हटाओ_devices(max77693->dev);

	regmap_del_irq_chip(max77693->irq, max77693->irq_data_muic);
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_chg);
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_topsys);
	regmap_del_irq_chip(max77693->irq, max77693->irq_data_led);

	i2c_unरेजिस्टर_device(max77693->i2c_muic);
	i2c_unरेजिस्टर_device(max77693->i2c_haptic);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max77693_i2c_id[] = अणु
	अणु "max77693", TYPE_MAX77693 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max77693_i2c_id);

अटल पूर्णांक max77693_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max77693_dev *max77693 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev)) अणु
		enable_irq_wake(max77693->irq);
		disable_irq(max77693->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max77693_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max77693_dev *max77693 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev)) अणु
		disable_irq_wake(max77693->irq);
		enable_irq(max77693->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops max77693_pm = अणु
	.suspend = max77693_suspend,
	.resume = max77693_resume,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max77693_dt_match[] = अणु
	अणु .compatible = "maxim,max77693" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max77693_dt_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max77693_i2c_driver = अणु
	.driver = अणु
		   .name = "max77693",
		   .pm = &max77693_pm,
		   .of_match_table = of_match_ptr(max77693_dt_match),
	पूर्ण,
	.probe = max77693_i2c_probe,
	.हटाओ = max77693_i2c_हटाओ,
	.id_table = max77693_i2c_id,
पूर्ण;

module_i2c_driver(max77693_i2c_driver);

MODULE_DESCRIPTION("MAXIM 77693 multi-function core driver");
MODULE_AUTHOR("SangYoung, Son <hello.son@samsung.com>");
MODULE_LICENSE("GPL");
