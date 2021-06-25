<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MFD core driver क्रम Ricoh RN5T618 PMIC
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 * Copyright (C) 2016 Toradex AG
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/rn5t618.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा mfd_cell rn5t618_cells[] = अणु
	अणु .name = "rn5t618-regulator" पूर्ण,
	अणु .name = "rn5t618-wdt" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell rc5t619_cells[] = अणु
	अणु .name = "rn5t618-adc" पूर्ण,
	अणु .name = "rn5t618-power" पूर्ण,
	अणु .name = "rn5t618-regulator" पूर्ण,
	अणु .name = "rc5t619-rtc" पूर्ण,
	अणु .name = "rn5t618-wdt" पूर्ण,
पूर्ण;

अटल bool rn5t618_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल RN5T618_WATCHDOGCNT:
	हाल RN5T618_DCIRQ:
	हाल RN5T618_ILIMDATAH ... RN5T618_AIN0DATAL:
	हाल RN5T618_ADCCNT3:
	हाल RN5T618_IR_ADC1 ... RN5T618_IR_ADC3:
	हाल RN5T618_IR_GPR:
	हाल RN5T618_IR_GPF:
	हाल RN5T618_MON_IOIN:
	हाल RN5T618_INTMON:
	हाल RN5T618_RTC_CTRL1 ... RN5T618_RTC_CTRL2:
	हाल RN5T618_RTC_SECONDS ... RN5T618_RTC_YEAR:
	हाल RN5T618_CHGCTL1:
	हाल RN5T618_REGISET1 ... RN5T618_REGISET2:
	हाल RN5T618_CHGSTATE:
	हाल RN5T618_CHGCTRL_IRR ... RN5T618_CHGERR_MONI:
	हाल RN5T618_GCHGDET:
	हाल RN5T618_CONTROL ... RN5T618_CC_AVEREG0:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config rn5t618_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.अस्थिर_reg	= rn5t618_अस्थिर_reg,
	.max_रेजिस्टर	= RN5T618_MAX_REG,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq rc5t619_irqs[] = अणु
	REGMAP_IRQ_REG(RN5T618_IRQ_SYS, 0, BIT(0)),
	REGMAP_IRQ_REG(RN5T618_IRQ_DCDC, 0, BIT(1)),
	REGMAP_IRQ_REG(RN5T618_IRQ_RTC, 0, BIT(2)),
	REGMAP_IRQ_REG(RN5T618_IRQ_ADC, 0, BIT(3)),
	REGMAP_IRQ_REG(RN5T618_IRQ_GPIO, 0, BIT(4)),
	REGMAP_IRQ_REG(RN5T618_IRQ_CHG, 0, BIT(6)),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip rc5t619_irq_chip = अणु
	.name = "rc5t619",
	.irqs = rc5t619_irqs,
	.num_irqs = ARRAY_SIZE(rc5t619_irqs),
	.num_regs = 1,
	.status_base = RN5T618_INTMON,
	.mask_base = RN5T618_INTEN,
	.mask_invert = true,
पूर्ण;

अटल काष्ठा i2c_client *rn5t618_pm_घातer_off;
अटल काष्ठा notअगरier_block rn5t618_restart_handler;

अटल पूर्णांक rn5t618_irq_init(काष्ठा rn5t618 *rn5t618)
अणु
	स्थिर काष्ठा regmap_irq_chip *irq_chip = शून्य;
	पूर्णांक ret;

	अगर (!rn5t618->irq)
		वापस 0;

	चयन (rn5t618->variant) अणु
	हाल RC5T619:
		irq_chip = &rc5t619_irq_chip;
		अवरोध;
	शेष:
		dev_err(rn5t618->dev, "Currently no IRQ support for variant %d\n",
			(पूर्णांक)rn5t618->variant);
		वापस -ENOENT;
	पूर्ण

	ret = devm_regmap_add_irq_chip(rn5t618->dev, rn5t618->regmap,
				       rn5t618->irq,
				       IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				       0, irq_chip, &rn5t618->irq_data);
	अगर (ret)
		dev_err(rn5t618->dev, "Failed to register IRQ chip\n");

	वापस ret;
पूर्ण

अटल व्योम rn5t618_trigger_घातeroff_sequence(bool reघातer)
अणु
	पूर्णांक ret;

	/* disable स्वतःmatic reघातer-on */
	ret = i2c_smbus_पढ़ो_byte_data(rn5t618_pm_घातer_off, RN5T618_REPCNT);
	अगर (ret < 0)
		जाओ err;

	ret &= ~RN5T618_REPCNT_REPWRON;
	अगर (reघातer)
		ret |= RN5T618_REPCNT_REPWRON;

	ret = i2c_smbus_ग_लिखो_byte_data(rn5t618_pm_घातer_off,
					RN5T618_REPCNT, (u8)ret);
	अगर (ret < 0)
		जाओ err;

	/* start घातer-off sequence */
	ret = i2c_smbus_पढ़ो_byte_data(rn5t618_pm_घातer_off, RN5T618_SLPCNT);
	अगर (ret < 0)
		जाओ err;

	ret |= RN5T618_SLPCNT_SWPWROFF;

	ret = i2c_smbus_ग_लिखो_byte_data(rn5t618_pm_घातer_off,
					RN5T618_SLPCNT, (u8)ret);
	अगर (ret < 0)
		जाओ err;

	वापस;

err:
	dev_alert(&rn5t618_pm_घातer_off->dev, "Failed to shutdown (err = %d)\n", ret);
पूर्ण

अटल व्योम rn5t618_घातer_off(व्योम)
अणु
	rn5t618_trigger_घातeroff_sequence(false);
पूर्ण

अटल पूर्णांक rn5t618_restart(काष्ठा notअगरier_block *this,
			    अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	rn5t618_trigger_घातeroff_sequence(true);

	/*
	 * Re-घातer factor detection on PMIC side is not instant. 1ms
	 * proved to be enough समय until reset takes effect.
	 */
	mdelay(1);

	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा of_device_id rn5t618_of_match[] = अणु
	अणु .compatible = "ricoh,rn5t567", .data = (व्योम *)RN5T567 पूर्ण,
	अणु .compatible = "ricoh,rn5t618", .data = (व्योम *)RN5T618 पूर्ण,
	अणु .compatible = "ricoh,rc5t619", .data = (व्योम *)RC5T619 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rn5t618_of_match);

अटल पूर्णांक rn5t618_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा rn5t618 *priv;
	पूर्णांक ret;

	of_id = of_match_device(rn5t618_of_match, &i2c->dev);
	अगर (!of_id) अणु
		dev_err(&i2c->dev, "Failed to find matching DT ID\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&i2c->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, priv);
	priv->variant = (दीर्घ)of_id->data;
	priv->irq = i2c->irq;
	priv->dev = &i2c->dev;

	priv->regmap = devm_regmap_init_i2c(i2c, &rn5t618_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (priv->variant == RC5T619)
		ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_NONE,
					   rc5t619_cells,
					   ARRAY_SIZE(rc5t619_cells),
					   शून्य, 0, शून्य);
	अन्यथा
		ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_NONE,
					   rn5t618_cells,
					   ARRAY_SIZE(rn5t618_cells),
					   शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&i2c->dev, "failed to add sub-devices: %d\n", ret);
		वापस ret;
	पूर्ण

	rn5t618_pm_घातer_off = i2c;
	अगर (of_device_is_प्रणाली_घातer_controller(i2c->dev.of_node)) अणु
		अगर (!pm_घातer_off)
			pm_घातer_off = rn5t618_घातer_off;
		अन्यथा
			dev_warn(&i2c->dev, "Poweroff callback already assigned\n");
	पूर्ण

	rn5t618_restart_handler.notअगरier_call = rn5t618_restart;
	rn5t618_restart_handler.priority = 192;

	ret = रेजिस्टर_restart_handler(&rn5t618_restart_handler);
	अगर (ret) अणु
		dev_err(&i2c->dev, "cannot register restart handler, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस rn5t618_irq_init(priv);
पूर्ण

अटल पूर्णांक rn5t618_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	अगर (i2c == rn5t618_pm_घातer_off) अणु
		rn5t618_pm_घातer_off = शून्य;
		pm_घातer_off = शून्य;
	पूर्ण

	unरेजिस्टर_restart_handler(&rn5t618_restart_handler);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rn5t618_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा rn5t618 *priv = dev_get_drvdata(dev);

	अगर (priv->irq)
		disable_irq(priv->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused rn5t618_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा rn5t618 *priv = dev_get_drvdata(dev);

	अगर (priv->irq)
		enable_irq(priv->irq);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rn5t618_i2c_dev_pm_ops,
			rn5t618_i2c_suspend,
			rn5t618_i2c_resume);

अटल काष्ठा i2c_driver rn5t618_i2c_driver = अणु
	.driver = अणु
		.name = "rn5t618",
		.of_match_table = of_match_ptr(rn5t618_of_match),
		.pm = &rn5t618_i2c_dev_pm_ops,
	पूर्ण,
	.probe_new = rn5t618_i2c_probe,
	.हटाओ = rn5t618_i2c_हटाओ,
पूर्ण;

module_i2c_driver(rn5t618_i2c_driver);

MODULE_AUTHOR("Beniamino Galvani <b.galvani@gmail.com>");
MODULE_DESCRIPTION("Ricoh RN5T567/618 MFD driver");
MODULE_LICENSE("GPL v2");
