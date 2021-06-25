<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max8907.c - mfd driver क्रम MAX8907
 *
 * Copyright (C) 2010 Gyungoh Yoo <jack.yoo@maxim-ic.com>
 * Copyright (C) 2010-2012, NVIDIA CORPORATION. All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max8907.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल स्थिर काष्ठा mfd_cell max8907_cells[] = अणु
	अणु .name = "max8907-regulator", पूर्ण,
	अणु .name = "max8907-rtc", पूर्ण,
पूर्ण;

अटल bool max8907_gen_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX8907_REG_ON_OFF_IRQ1:
	हाल MAX8907_REG_ON_OFF_STAT:
	हाल MAX8907_REG_ON_OFF_IRQ2:
	हाल MAX8907_REG_CHG_IRQ1:
	हाल MAX8907_REG_CHG_IRQ2:
	हाल MAX8907_REG_CHG_STAT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max8907_gen_is_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX8907_REG_ON_OFF_IRQ1:
	हाल MAX8907_REG_ON_OFF_IRQ2:
	हाल MAX8907_REG_CHG_IRQ1:
	हाल MAX8907_REG_CHG_IRQ2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max8907_gen_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस !max8907_gen_is_अस्थिर_reg(dev, reg);
पूर्ण

अटल स्थिर काष्ठा regmap_config max8907_regmap_gen_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = max8907_gen_is_अस्थिर_reg,
	.precious_reg = max8907_gen_is_precious_reg,
	.ग_लिखोable_reg = max8907_gen_is_ग_लिखोable_reg,
	.max_रेजिस्टर = MAX8907_REG_LDO20VOUT,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल bool max8907_rtc_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg <= MAX8907_REG_RTC_YEAR2)
		वापस true;

	चयन (reg) अणु
	हाल MAX8907_REG_RTC_STATUS:
	हाल MAX8907_REG_RTC_IRQ:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max8907_rtc_is_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX8907_REG_RTC_IRQ:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max8907_rtc_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX8907_REG_RTC_STATUS:
	हाल MAX8907_REG_RTC_IRQ:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config max8907_regmap_rtc_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = max8907_rtc_is_अस्थिर_reg,
	.precious_reg = max8907_rtc_is_precious_reg,
	.ग_लिखोable_reg = max8907_rtc_is_ग_लिखोable_reg,
	.max_रेजिस्टर = MAX8907_REG_MPL_CNTL,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max8907_chg_irqs[] = अणु
	अणु .reg_offset = 0, .mask = 1 << 0, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 1, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 2, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 0, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 1, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 2, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 3, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 4, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 5, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 6, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 7, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max8907_chg_irq_chip = अणु
	.name = "max8907 chg",
	.status_base = MAX8907_REG_CHG_IRQ1,
	.mask_base = MAX8907_REG_CHG_IRQ1_MASK,
	.wake_base = MAX8907_REG_CHG_IRQ1_MASK,
	.irq_reg_stride = MAX8907_REG_CHG_IRQ2 - MAX8907_REG_CHG_IRQ1,
	.num_regs = 2,
	.irqs = max8907_chg_irqs,
	.num_irqs = ARRAY_SIZE(max8907_chg_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max8907_on_off_irqs[] = अणु
	अणु .reg_offset = 0, .mask = 1 << 0, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 1, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 2, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 3, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 4, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 5, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 6, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 7, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 0, पूर्ण,
	अणु .reg_offset = 1, .mask = 1 << 1, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max8907_on_off_irq_chip = अणु
	.name = "max8907 on_off",
	.status_base = MAX8907_REG_ON_OFF_IRQ1,
	.mask_base = MAX8907_REG_ON_OFF_IRQ1_MASK,
	.irq_reg_stride = MAX8907_REG_ON_OFF_IRQ2 - MAX8907_REG_ON_OFF_IRQ1,
	.num_regs = 2,
	.irqs = max8907_on_off_irqs,
	.num_irqs = ARRAY_SIZE(max8907_on_off_irqs),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max8907_rtc_irqs[] = अणु
	अणु .reg_offset = 0, .mask = 1 << 2, पूर्ण,
	अणु .reg_offset = 0, .mask = 1 << 3, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max8907_rtc_irq_chip = अणु
	.name = "max8907 rtc",
	.status_base = MAX8907_REG_RTC_IRQ,
	.mask_base = MAX8907_REG_RTC_IRQ_MASK,
	.num_regs = 1,
	.irqs = max8907_rtc_irqs,
	.num_irqs = ARRAY_SIZE(max8907_rtc_irqs),
पूर्ण;

अटल काष्ठा max8907 *max8907_pm_off;
अटल व्योम max8907_घातer_off(व्योम)
अणु
	regmap_update_bits(max8907_pm_off->regmap_gen, MAX8907_REG_RESET_CNFG,
			MAX8907_MASK_POWER_OFF, MAX8907_MASK_POWER_OFF);
पूर्ण

अटल पूर्णांक max8907_i2c_probe(काष्ठा i2c_client *i2c,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max8907 *max8907;
	पूर्णांक ret;
	काष्ठा max8907_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	bool pm_off = false;

	अगर (pdata)
		pm_off = pdata->pm_off;
	अन्यथा अगर (i2c->dev.of_node)
		pm_off = of_property_पढ़ो_bool(i2c->dev.of_node,
					"maxim,system-power-controller");

	max8907 = devm_kzalloc(&i2c->dev, माप(काष्ठा max8907), GFP_KERNEL);
	अगर (!max8907) अणु
		ret = -ENOMEM;
		जाओ err_alloc_drvdata;
	पूर्ण

	max8907->dev = &i2c->dev;
	dev_set_drvdata(max8907->dev, max8907);

	max8907->i2c_gen = i2c;
	i2c_set_clientdata(i2c, max8907);
	max8907->regmap_gen = devm_regmap_init_i2c(i2c,
						&max8907_regmap_gen_config);
	अगर (IS_ERR(max8907->regmap_gen)) अणु
		ret = PTR_ERR(max8907->regmap_gen);
		dev_err(&i2c->dev, "gen regmap init failed: %d\n", ret);
		जाओ err_regmap_gen;
	पूर्ण

	max8907->i2c_rtc = i2c_new_dummy_device(i2c->adapter, MAX8907_RTC_I2C_ADDR);
	अगर (IS_ERR(max8907->i2c_rtc)) अणु
		ret = PTR_ERR(max8907->i2c_rtc);
		जाओ err_dummy_rtc;
	पूर्ण
	i2c_set_clientdata(max8907->i2c_rtc, max8907);
	max8907->regmap_rtc = devm_regmap_init_i2c(max8907->i2c_rtc,
						&max8907_regmap_rtc_config);
	अगर (IS_ERR(max8907->regmap_rtc)) अणु
		ret = PTR_ERR(max8907->regmap_rtc);
		dev_err(&i2c->dev, "rtc regmap init failed: %d\n", ret);
		जाओ err_regmap_rtc;
	पूर्ण

	irq_set_status_flags(max8907->i2c_gen->irq, IRQ_NOAUTOEN);

	ret = regmap_add_irq_chip(max8907->regmap_gen, max8907->i2c_gen->irq,
				  IRQF_ONESHOT | IRQF_SHARED, -1,
				  &max8907_chg_irq_chip,
				  &max8907->irqc_chg);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "failed to add chg irq chip: %d\n", ret);
		जाओ err_irqc_chg;
	पूर्ण
	ret = regmap_add_irq_chip(max8907->regmap_gen, max8907->i2c_gen->irq,
				  IRQF_ONESHOT | IRQF_SHARED, -1,
				  &max8907_on_off_irq_chip,
				  &max8907->irqc_on_off);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "failed to add on off irq chip: %d\n", ret);
		जाओ err_irqc_on_off;
	पूर्ण
	ret = regmap_add_irq_chip(max8907->regmap_rtc, max8907->i2c_gen->irq,
				  IRQF_ONESHOT | IRQF_SHARED, -1,
				  &max8907_rtc_irq_chip,
				  &max8907->irqc_rtc);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "failed to add rtc irq chip: %d\n", ret);
		जाओ err_irqc_rtc;
	पूर्ण

	enable_irq(max8907->i2c_gen->irq);

	ret = mfd_add_devices(max8907->dev, -1, max8907_cells,
			      ARRAY_SIZE(max8907_cells), शून्य, 0, शून्य);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "failed to add MFD devices %d\n", ret);
		जाओ err_add_devices;
	पूर्ण

	अगर (pm_off && !pm_घातer_off) अणु
		max8907_pm_off = max8907;
		pm_घातer_off = max8907_घातer_off;
	पूर्ण

	वापस 0;

err_add_devices:
	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_rtc);
err_irqc_rtc:
	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_on_off);
err_irqc_on_off:
	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_chg);
err_irqc_chg:
err_regmap_rtc:
	i2c_unरेजिस्टर_device(max8907->i2c_rtc);
err_dummy_rtc:
err_regmap_gen:
err_alloc_drvdata:
	वापस ret;
पूर्ण

अटल पूर्णांक max8907_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा max8907 *max8907 = i2c_get_clientdata(i2c);

	mfd_हटाओ_devices(max8907->dev);

	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_rtc);
	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_on_off);
	regmap_del_irq_chip(max8907->i2c_gen->irq, max8907->irqc_chg);

	i2c_unरेजिस्टर_device(max8907->i2c_rtc);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max8907_of_match[] = अणु
	अणु .compatible = "maxim,max8907" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max8907_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id max8907_i2c_id[] = अणु
	अणु"max8907", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max8907_i2c_id);

अटल काष्ठा i2c_driver max8907_i2c_driver = अणु
	.driver = अणु
		.name = "max8907",
		.of_match_table = of_match_ptr(max8907_of_match),
	पूर्ण,
	.probe = max8907_i2c_probe,
	.हटाओ = max8907_i2c_हटाओ,
	.id_table = max8907_i2c_id,
पूर्ण;

अटल पूर्णांक __init max8907_i2c_init(व्योम)
अणु
	पूर्णांक ret = -ENODEV;

	ret = i2c_add_driver(&max8907_i2c_driver);
	अगर (ret != 0)
		pr_err("Failed to register I2C driver: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(max8907_i2c_init);

अटल व्योम __निकास max8907_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&max8907_i2c_driver);
पूर्ण
module_निकास(max8907_i2c_निकास);

MODULE_DESCRIPTION("MAX8907 multi-function core driver");
MODULE_AUTHOR("Gyungoh Yoo <jack.yoo@maxim-ic.com>");
MODULE_LICENSE("GPL v2");
