<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery and Power Management code क्रम the Sharp SL-5x00
 *
 * Copyright (C) 2009 Thomas Kunze
 *
 * based on tosa_battery.c
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mfd/ucb1x00.h>

#समावेश <यंत्र/mach/sharpsl_param.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/collie.h>

अटल DEFINE_MUTEX(bat_lock); /* protects gpio pins */
अटल काष्ठा work_काष्ठा bat_work;
अटल काष्ठा ucb1x00 *ucb;

काष्ठा collie_bat अणु
	पूर्णांक status;
	काष्ठा घातer_supply *psy;
	पूर्णांक full_chrg;

	काष्ठा mutex work_lock; /* protects data */

	bool (*is_present)(काष्ठा collie_bat *bat);
	काष्ठा gpio_desc *gpio_full;
	काष्ठा gpio_desc *gpio_अक्षरge_on;

	पूर्णांक technology;

	काष्ठा gpio_desc *gpio_bat;
	पूर्णांक adc_bat;
	पूर्णांक adc_bat_भागider;
	पूर्णांक bat_max;
	पूर्णांक bat_min;

	काष्ठा gpio_desc *gpio_temp;
	पूर्णांक adc_temp;
	पूर्णांक adc_temp_भागider;
पूर्ण;

अटल काष्ठा collie_bat collie_bat_मुख्य;

अटल अचिन्हित दीर्घ collie_पढ़ो_bat(काष्ठा collie_bat *bat)
अणु
	अचिन्हित दीर्घ value = 0;

	अगर (!bat->gpio_bat || bat->adc_bat < 0)
		वापस 0;
	mutex_lock(&bat_lock);
	gpiod_set_value(bat->gpio_bat, 1);
	msleep(5);
	ucb1x00_adc_enable(ucb);
	value = ucb1x00_adc_पढ़ो(ucb, bat->adc_bat, UCB_SYNC);
	ucb1x00_adc_disable(ucb);
	gpiod_set_value(bat->gpio_bat, 0);
	mutex_unlock(&bat_lock);
	value = value * 1000000 / bat->adc_bat_भागider;

	वापस value;
पूर्ण

अटल अचिन्हित दीर्घ collie_पढ़ो_temp(काष्ठा collie_bat *bat)
अणु
	अचिन्हित दीर्घ value = 0;
	अगर (!bat->gpio_temp || bat->adc_temp < 0)
		वापस 0;

	mutex_lock(&bat_lock);
	gpiod_set_value(bat->gpio_temp, 1);
	msleep(5);
	ucb1x00_adc_enable(ucb);
	value = ucb1x00_adc_पढ़ो(ucb, bat->adc_temp, UCB_SYNC);
	ucb1x00_adc_disable(ucb);
	gpiod_set_value(bat->gpio_temp, 0);
	mutex_unlock(&bat_lock);

	value = value * 10000 / bat->adc_temp_भागider;

	वापस value;
पूर्ण

अटल पूर्णांक collie_bat_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा collie_bat *bat = घातer_supply_get_drvdata(psy);

	अगर (bat->is_present && !bat->is_present(bat)
			&& psp != POWER_SUPPLY_PROP_PRESENT) अणु
		वापस -ENODEV;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = bat->status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = bat->technology;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = collie_पढ़ो_bat(bat);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		अगर (bat->full_chrg == -1)
			val->पूर्णांकval = bat->bat_max;
		अन्यथा
			val->पूर्णांकval = bat->full_chrg;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = bat->bat_max;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = bat->bat_min;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = collie_पढ़ो_temp(bat);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = bat->is_present ? bat->is_present(bat) : 1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम collie_bat_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	schedule_work(&bat_work);
पूर्ण

अटल irqवापस_t collie_bat_gpio_isr(पूर्णांक irq, व्योम *data)
अणु
	pr_info("collie_bat_gpio irq\n");
	schedule_work(&bat_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम collie_bat_update(काष्ठा collie_bat *bat)
अणु
	पूर्णांक old;
	काष्ठा घातer_supply *psy = bat->psy;

	mutex_lock(&bat->work_lock);

	old = bat->status;

	अगर (bat->is_present && !bat->is_present(bat)) अणु
		prपूर्णांकk(KERN_NOTICE "%s not present\n", psy->desc->name);
		bat->status = POWER_SUPPLY_STATUS_UNKNOWN;
		bat->full_chrg = -1;
	पूर्ण अन्यथा अगर (घातer_supply_am_i_supplied(psy)) अणु
		अगर (bat->status == POWER_SUPPLY_STATUS_DISCHARGING) अणु
			gpiod_set_value(bat->gpio_अक्षरge_on, 1);
			mdelay(15);
		पूर्ण

		अगर (gpiod_get_value(bat->gpio_full)) अणु
			अगर (old == POWER_SUPPLY_STATUS_CHARGING ||
					bat->full_chrg == -1)
				bat->full_chrg = collie_पढ़ो_bat(bat);

			gpiod_set_value(bat->gpio_अक्षरge_on, 0);
			bat->status = POWER_SUPPLY_STATUS_FULL;
		पूर्ण अन्यथा अणु
			gpiod_set_value(bat->gpio_अक्षरge_on, 1);
			bat->status = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण
	पूर्ण अन्यथा अणु
		gpiod_set_value(bat->gpio_अक्षरge_on, 0);
		bat->status = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	अगर (old != bat->status)
		घातer_supply_changed(psy);

	mutex_unlock(&bat->work_lock);
पूर्ण

अटल व्योम collie_bat_work(काष्ठा work_काष्ठा *work)
अणु
	collie_bat_update(&collie_bat_मुख्य);
पूर्ण


अटल क्रमागत घातer_supply_property collie_bat_मुख्य_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TEMP,
पूर्ण;

अटल क्रमागत घातer_supply_property collie_bat_bu_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_PRESENT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc collie_bat_मुख्य_desc = अणु
	.name		= "main-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= collie_bat_मुख्य_props,
	.num_properties	= ARRAY_SIZE(collie_bat_मुख्य_props),
	.get_property	= collie_bat_get_property,
	.बाह्यal_घातer_changed = collie_bat_बाह्यal_घातer_changed,
	.use_क्रम_apm	= 1,
पूर्ण;

अटल काष्ठा collie_bat collie_bat_मुख्य = अणु
	.status = POWER_SUPPLY_STATUS_DISCHARGING,
	.full_chrg = -1,
	.psy = शून्य,

	.gpio_full = शून्य,
	.gpio_अक्षरge_on = शून्य,

	.technology = POWER_SUPPLY_TECHNOLOGY_LIPO,

	.gpio_bat = शून्य,
	.adc_bat = UCB_ADC_INP_AD1,
	.adc_bat_भागider = 155,
	.bat_max = 4310000,
	.bat_min = 1551 * 1000000 / 414,

	.gpio_temp = शून्य,
	.adc_temp = UCB_ADC_INP_AD0,
	.adc_temp_भागider = 10000,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc collie_bat_bu_desc = अणु
	.name		= "backup-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= collie_bat_bu_props,
	.num_properties	= ARRAY_SIZE(collie_bat_bu_props),
	.get_property	= collie_bat_get_property,
	.बाह्यal_घातer_changed = collie_bat_बाह्यal_घातer_changed,
पूर्ण;

अटल काष्ठा collie_bat collie_bat_bu = अणु
	.status = POWER_SUPPLY_STATUS_UNKNOWN,
	.full_chrg = -1,
	.psy = शून्य,

	.gpio_full = शून्य,
	.gpio_अक्षरge_on = शून्य,

	.technology = POWER_SUPPLY_TECHNOLOGY_LiMn,

	.gpio_bat = शून्य,
	.adc_bat = UCB_ADC_INP_AD1,
	.adc_bat_भागider = 155,
	.bat_max = 3000000,
	.bat_min = 1900000,

	.gpio_temp = शून्य,
	.adc_temp = -1,
	.adc_temp_भागider = -1,
पूर्ण;

/* Obtained but unused GPIO */
अटल काष्ठा gpio_desc *collie_mbat_low;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wakeup_enabled;

अटल पूर्णांक collie_bat_suspend(काष्ठा ucb1x00_dev *dev)
अणु
	/* flush all pending status updates */
	flush_work(&bat_work);

	अगर (device_may_wakeup(&dev->ucb->dev) &&
	    collie_bat_मुख्य.status == POWER_SUPPLY_STATUS_CHARGING)
		wakeup_enabled = !enable_irq_wake(gpiod_to_irq(collie_bat_मुख्य.gpio_full));
	अन्यथा
		wakeup_enabled = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक collie_bat_resume(काष्ठा ucb1x00_dev *dev)
अणु
	अगर (wakeup_enabled)
		disable_irq_wake(gpiod_to_irq(collie_bat_मुख्य.gpio_full));

	/* things may have changed जबतक we were away */
	schedule_work(&bat_work);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा collie_bat_suspend शून्य
#घोषणा collie_bat_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक collie_bat_probe(काष्ठा ucb1x00_dev *dev)
अणु
	पूर्णांक ret;
	काष्ठा घातer_supply_config psy_मुख्य_cfg = अणुपूर्ण, psy_bu_cfg = अणुपूर्ण;
	काष्ठा gpio_chip *gc = &dev->ucb->gpio;

	अगर (!machine_is_collie())
		वापस -ENODEV;

	ucb = dev->ucb;

	/* Obtain all the मुख्य battery GPIOs */
	collie_bat_मुख्य.gpio_full = gpiod_get(&dev->ucb->dev,
					      "main battery full",
					      GPIOD_IN);
	अगर (IS_ERR(collie_bat_मुख्य.gpio_full))
		वापस PTR_ERR(collie_bat_मुख्य.gpio_full);

	collie_mbat_low = gpiod_get(&dev->ucb->dev,
				    "main battery low",
				    GPIOD_IN);
	अगर (IS_ERR(collie_mbat_low)) अणु
		ret = PTR_ERR(collie_mbat_low);
		जाओ err_put_gpio_full;
	पूर्ण

	collie_bat_मुख्य.gpio_अक्षरge_on = gpiod_get(&dev->ucb->dev,
						   "main charge on",
						   GPIOD_OUT_LOW);
	अगर (IS_ERR(collie_bat_मुख्य.gpio_अक्षरge_on)) अणु
		ret = PTR_ERR(collie_bat_मुख्य.gpio_अक्षरge_on);
		जाओ err_put_mbat_low;
	पूर्ण

	/* COLLIE_GPIO_MBAT_ON = GPIO 7 on the UCB (TC35143) */
	collie_bat_मुख्य.gpio_bat = gpiochip_request_own_desc(gc,
						7,
						"main battery",
						GPIO_ACTIVE_HIGH,
						GPIOD_OUT_LOW);
	अगर (IS_ERR(collie_bat_मुख्य.gpio_bat)) अणु
		ret = PTR_ERR(collie_bat_मुख्य.gpio_bat);
		जाओ err_put_gpio_अक्षरge_on;
	पूर्ण

	/* COLLIE_GPIO_TMP_ON = GPIO 9 on the UCB (TC35143) */
	collie_bat_मुख्य.gpio_temp = gpiochip_request_own_desc(gc,
						9,
						"main battery temp",
						GPIO_ACTIVE_HIGH,
						GPIOD_OUT_LOW);
	अगर (IS_ERR(collie_bat_मुख्य.gpio_temp)) अणु
		ret = PTR_ERR(collie_bat_मुख्य.gpio_temp);
		जाओ err_मुक्त_gpio_bat;
	पूर्ण

	/*
	 * Obtain the backup battery COLLIE_GPIO_BBAT_ON which is
	 * GPIO 8 on the UCB (TC35143)
	 */
	collie_bat_bu.gpio_bat = gpiochip_request_own_desc(gc,
						8,
						"backup battery",
						GPIO_ACTIVE_HIGH,
						GPIOD_OUT_LOW);
	अगर (IS_ERR(collie_bat_bu.gpio_bat)) अणु
		ret = PTR_ERR(collie_bat_bu.gpio_bat);
		जाओ err_मुक्त_gpio_temp;
	पूर्ण

	mutex_init(&collie_bat_मुख्य.work_lock);

	INIT_WORK(&bat_work, collie_bat_work);

	psy_मुख्य_cfg.drv_data = &collie_bat_मुख्य;
	collie_bat_मुख्य.psy = घातer_supply_रेजिस्टर(&dev->ucb->dev,
						    &collie_bat_मुख्य_desc,
						    &psy_मुख्य_cfg);
	अगर (IS_ERR(collie_bat_मुख्य.psy)) अणु
		ret = PTR_ERR(collie_bat_मुख्य.psy);
		जाओ err_psy_reg_मुख्य;
	पूर्ण

	psy_bu_cfg.drv_data = &collie_bat_bu;
	collie_bat_bu.psy = घातer_supply_रेजिस्टर(&dev->ucb->dev,
						  &collie_bat_bu_desc,
						  &psy_bu_cfg);
	अगर (IS_ERR(collie_bat_bu.psy)) अणु
		ret = PTR_ERR(collie_bat_bu.psy);
		जाओ err_psy_reg_bu;
	पूर्ण

	ret = request_irq(gpio_to_irq(COLLIE_GPIO_CO),
				collie_bat_gpio_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"main full", &collie_bat_मुख्य);
	अगर (ret)
		जाओ err_irq;

	device_init_wakeup(&ucb->dev, 1);
	schedule_work(&bat_work);

	वापस 0;

err_irq:
	घातer_supply_unरेजिस्टर(collie_bat_bu.psy);
err_psy_reg_bu:
	घातer_supply_unरेजिस्टर(collie_bat_मुख्य.psy);
err_psy_reg_मुख्य:
	/* see comment in collie_bat_हटाओ */
	cancel_work_sync(&bat_work);
	gpiochip_मुक्त_own_desc(collie_bat_bu.gpio_bat);
err_मुक्त_gpio_temp:
	gpiochip_मुक्त_own_desc(collie_bat_मुख्य.gpio_temp);
err_मुक्त_gpio_bat:
	gpiochip_मुक्त_own_desc(collie_bat_मुख्य.gpio_bat);
err_put_gpio_अक्षरge_on:
	gpiod_put(collie_bat_मुख्य.gpio_अक्षरge_on);
err_put_mbat_low:
	gpiod_put(collie_mbat_low);
err_put_gpio_full:
	gpiod_put(collie_bat_मुख्य.gpio_full);

	वापस ret;
पूर्ण

अटल व्योम collie_bat_हटाओ(काष्ठा ucb1x00_dev *dev)
अणु
	मुक्त_irq(gpio_to_irq(COLLIE_GPIO_CO), &collie_bat_मुख्य);
	घातer_supply_unरेजिस्टर(collie_bat_bu.psy);
	घातer_supply_unरेजिस्टर(collie_bat_मुख्य.psy);

	/* These are obtained from the machine */
	gpiod_put(collie_bat_मुख्य.gpio_full);
	gpiod_put(collie_mbat_low);
	gpiod_put(collie_bat_मुख्य.gpio_अक्षरge_on);
	/* These are directly from the UCB so let's मुक्त them */
	gpiochip_मुक्त_own_desc(collie_bat_मुख्य.gpio_bat);
	gpiochip_मुक्त_own_desc(collie_bat_मुख्य.gpio_temp);
	gpiochip_मुक्त_own_desc(collie_bat_bu.gpio_bat);
	/*
	 * Now cancel the bat_work.  We won't get any more schedules,
	 * since all sources (isr and बाह्यal_घातer_changed) are
	 * unरेजिस्टरed now.
	 */
	cancel_work_sync(&bat_work);
पूर्ण

अटल काष्ठा ucb1x00_driver collie_bat_driver = अणु
	.add		= collie_bat_probe,
	.हटाओ		= collie_bat_हटाओ,
	.suspend	= collie_bat_suspend,
	.resume		= collie_bat_resume,
पूर्ण;

अटल पूर्णांक __init collie_bat_init(व्योम)
अणु
	वापस ucb1x00_रेजिस्टर_driver(&collie_bat_driver);
पूर्ण

अटल व्योम __निकास collie_bat_निकास(व्योम)
अणु
	ucb1x00_unरेजिस्टर_driver(&collie_bat_driver);
पूर्ण

module_init(collie_bat_init);
module_निकास(collie_bat_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Kunze");
MODULE_DESCRIPTION("Collie battery driver");
