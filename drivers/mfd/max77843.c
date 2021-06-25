<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// MFD core driver क्रम the Maxim MAX77843
//
// Copyright (C) 2015 Samsung Electronics
// Author: Jaewon Kim <jaewon02.kim@samsung.com>
// Author: Beomho Seo <beomho.seo@samsung.com>

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/max77693-common.h>
#समावेश <linux/mfd/max77843-निजी.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर काष्ठा mfd_cell max77843_devs[] = अणु
	अणु
		.name = "max77843-muic",
		.of_compatible = "maxim,max77843-muic",
	पूर्ण, अणु
		.name = "max77843-regulator",
		.of_compatible = "maxim,max77843-regulator",
	पूर्ण, अणु
		.name = "max77843-charger",
		.of_compatible = "maxim,max77843-charger"
	पूर्ण, अणु
		.name = "max77843-fuelgauge",
		.of_compatible = "maxim,max77843-fuelgauge",
	पूर्ण, अणु
		.name = "max77843-haptic",
		.of_compatible = "maxim,max77843-haptic",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77843_अक्षरger_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= MAX77843_CHG_REG_END,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max77843_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= MAX77843_SYS_REG_END,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq max77843_irqs[] = अणु
	/* TOPSYS पूर्णांकerrupts */
	अणु .reg_offset = 0, .mask = MAX77843_SYS_IRQ_SYSUVLO_INT, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77843_SYS_IRQ_SYSOVLO_INT, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77843_SYS_IRQ_TSHDN_INT, पूर्ण,
	अणु .reg_offset = 0, .mask = MAX77843_SYS_IRQ_TM_INT, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip max77843_irq_chip = अणु
	.name		= "max77843",
	.status_base	= MAX77843_SYS_REG_SYSINTSRC,
	.mask_base	= MAX77843_SYS_REG_SYSINTMASK,
	.mask_invert	= false,
	.num_regs	= 1,
	.irqs		= max77843_irqs,
	.num_irqs	= ARRAY_SIZE(max77843_irqs),
पूर्ण;

/* Charger and Charger regulator use same regmap. */
अटल पूर्णांक max77843_chg_init(काष्ठा max77693_dev *max77843)
अणु
	पूर्णांक ret;

	max77843->i2c_chg = i2c_new_dummy_device(max77843->i2c->adapter, I2C_ADDR_CHG);
	अगर (IS_ERR(max77843->i2c_chg)) अणु
		dev_err(&max77843->i2c->dev,
				"Cannot allocate I2C device for Charger\n");
		वापस PTR_ERR(max77843->i2c_chg);
	पूर्ण
	i2c_set_clientdata(max77843->i2c_chg, max77843);

	max77843->regmap_chg = devm_regmap_init_i2c(max77843->i2c_chg,
			&max77843_अक्षरger_regmap_config);
	अगर (IS_ERR(max77843->regmap_chg)) अणु
		ret = PTR_ERR(max77843->regmap_chg);
		जाओ err_chg_i2c;
	पूर्ण

	वापस 0;

err_chg_i2c:
	i2c_unरेजिस्टर_device(max77843->i2c_chg);

	वापस ret;
पूर्ण

अटल पूर्णांक max77843_probe(काष्ठा i2c_client *i2c,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max77693_dev *max77843;
	अचिन्हित पूर्णांक reg_data;
	पूर्णांक ret;

	max77843 = devm_kzalloc(&i2c->dev, माप(*max77843), GFP_KERNEL);
	अगर (!max77843)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max77843);
	max77843->dev = &i2c->dev;
	max77843->i2c = i2c;
	max77843->irq = i2c->irq;
	max77843->type = id->driver_data;

	max77843->regmap = devm_regmap_init_i2c(i2c,
			&max77843_regmap_config);
	अगर (IS_ERR(max77843->regmap)) अणु
		dev_err(&i2c->dev, "Failed to allocate topsys register map\n");
		वापस PTR_ERR(max77843->regmap);
	पूर्ण

	ret = regmap_add_irq_chip(max77843->regmap, max77843->irq,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT | IRQF_SHARED,
			0, &max77843_irq_chip, &max77843->irq_data_topsys);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to add TOPSYS IRQ chip\n");
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(max77843->regmap,
			MAX77843_SYS_REG_PMICID, &reg_data);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read PMIC ID\n");
		जाओ err_pmic_id;
	पूर्ण
	dev_info(&i2c->dev, "device ID: 0x%x\n", reg_data);

	ret = max77843_chg_init(max77843);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to init Charger\n");
		जाओ err_pmic_id;
	पूर्ण

	ret = regmap_update_bits(max77843->regmap,
				 MAX77843_SYS_REG_INTSRCMASK,
				 MAX77843_INTSRC_MASK_MASK,
				 (अचिन्हित पूर्णांक)~MAX77843_INTSRC_MASK_MASK);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to unmask interrupt source\n");
		जाओ err_pmic_id;
	पूर्ण

	ret = mfd_add_devices(max77843->dev, -1, max77843_devs,
			      ARRAY_SIZE(max77843_devs), शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to add mfd device\n");
		जाओ err_pmic_id;
	पूर्ण

	device_init_wakeup(max77843->dev, true);

	वापस 0;

err_pmic_id:
	regmap_del_irq_chip(max77843->irq, max77843->irq_data_topsys);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id max77843_dt_match[] = अणु
	अणु .compatible = "maxim,max77843", पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id max77843_id[] = अणु
	अणु "max77843", TYPE_MAX77843, पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक __maybe_unused max77843_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max77693_dev *max77843 = i2c_get_clientdata(i2c);

	disable_irq(max77843->irq);
	अगर (device_may_wakeup(dev))
		enable_irq_wake(max77843->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max77843_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(dev);
	काष्ठा max77693_dev *max77843 = i2c_get_clientdata(i2c);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(max77843->irq);
	enable_irq(max77843->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max77843_pm, max77843_suspend, max77843_resume);

अटल काष्ठा i2c_driver max77843_i2c_driver = अणु
	.driver	= अणु
		.name = "max77843",
		.pm = &max77843_pm,
		.of_match_table = max77843_dt_match,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = max77843_probe,
	.id_table = max77843_id,
पूर्ण;

अटल पूर्णांक __init max77843_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&max77843_i2c_driver);
पूर्ण
subsys_initcall(max77843_i2c_init);
