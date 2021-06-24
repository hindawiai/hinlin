<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery and Power Management code क्रम the Sharp SL-6000x
 *
 * Copyright (c) 2005 Dirk Opfer
 * Copyright (c) 2008 Dmitry Baryshkov
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/wm97xx.h>
#समावेश <linux/delay.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/tosa.h>

अटल DEFINE_MUTEX(bat_lock); /* protects gpio pins */
अटल काष्ठा work_काष्ठा bat_work;

काष्ठा tosa_bat अणु
	पूर्णांक status;
	काष्ठा घातer_supply *psy;
	पूर्णांक full_chrg;

	काष्ठा mutex work_lock; /* protects data */

	bool (*is_present)(काष्ठा tosa_bat *bat);
	पूर्णांक gpio_full;
	पूर्णांक gpio_अक्षरge_off;

	पूर्णांक technology;

	पूर्णांक gpio_bat;
	पूर्णांक adc_bat;
	पूर्णांक adc_bat_भागider;
	पूर्णांक bat_max;
	पूर्णांक bat_min;

	पूर्णांक gpio_temp;
	पूर्णांक adc_temp;
	पूर्णांक adc_temp_भागider;
पूर्ण;

अटल काष्ठा tosa_bat tosa_bat_मुख्य;
अटल काष्ठा tosa_bat tosa_bat_jacket;

अटल अचिन्हित दीर्घ tosa_पढ़ो_bat(काष्ठा tosa_bat *bat)
अणु
	अचिन्हित दीर्घ value = 0;

	अगर (bat->gpio_bat < 0 || bat->adc_bat < 0)
		वापस 0;

	mutex_lock(&bat_lock);
	gpio_set_value(bat->gpio_bat, 1);
	msleep(5);
	value = wm97xx_पढ़ो_aux_adc(dev_get_drvdata(bat->psy->dev.parent),
			bat->adc_bat);
	gpio_set_value(bat->gpio_bat, 0);
	mutex_unlock(&bat_lock);

	value = value * 1000000 / bat->adc_bat_भागider;

	वापस value;
पूर्ण

अटल अचिन्हित दीर्घ tosa_पढ़ो_temp(काष्ठा tosa_bat *bat)
अणु
	अचिन्हित दीर्घ value = 0;

	अगर (bat->gpio_temp < 0 || bat->adc_temp < 0)
		वापस 0;

	mutex_lock(&bat_lock);
	gpio_set_value(bat->gpio_temp, 1);
	msleep(5);
	value = wm97xx_पढ़ो_aux_adc(dev_get_drvdata(bat->psy->dev.parent),
			bat->adc_temp);
	gpio_set_value(bat->gpio_temp, 0);
	mutex_unlock(&bat_lock);

	value = value * 10000 / bat->adc_temp_भागider;

	वापस value;
पूर्ण

अटल पूर्णांक tosa_bat_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा tosa_bat *bat = घातer_supply_get_drvdata(psy);

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
		val->पूर्णांकval = tosa_पढ़ो_bat(bat);
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
		val->पूर्णांकval = tosa_पढ़ो_temp(bat);
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

अटल bool tosa_jacket_bat_is_present(काष्ठा tosa_bat *bat)
अणु
	वापस gpio_get_value(TOSA_GPIO_JACKET_DETECT) == 0;
पूर्ण

अटल व्योम tosa_bat_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	schedule_work(&bat_work);
पूर्ण

अटल irqवापस_t tosa_bat_gpio_isr(पूर्णांक irq, व्योम *data)
अणु
	pr_info("tosa_bat_gpio irq\n");
	schedule_work(&bat_work);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम tosa_bat_update(काष्ठा tosa_bat *bat)
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
			gpio_set_value(bat->gpio_अक्षरge_off, 0);
			mdelay(15);
		पूर्ण

		अगर (gpio_get_value(bat->gpio_full)) अणु
			अगर (old == POWER_SUPPLY_STATUS_CHARGING ||
					bat->full_chrg == -1)
				bat->full_chrg = tosa_पढ़ो_bat(bat);

			gpio_set_value(bat->gpio_अक्षरge_off, 1);
			bat->status = POWER_SUPPLY_STATUS_FULL;
		पूर्ण अन्यथा अणु
			gpio_set_value(bat->gpio_अक्षरge_off, 0);
			bat->status = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण
	पूर्ण अन्यथा अणु
		gpio_set_value(bat->gpio_अक्षरge_off, 1);
		bat->status = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	अगर (old != bat->status)
		घातer_supply_changed(psy);

	mutex_unlock(&bat->work_lock);
पूर्ण

अटल व्योम tosa_bat_work(काष्ठा work_काष्ठा *work)
अणु
	tosa_bat_update(&tosa_bat_मुख्य);
	tosa_bat_update(&tosa_bat_jacket);
पूर्ण


अटल क्रमागत घातer_supply_property tosa_bat_मुख्य_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_PRESENT,
पूर्ण;

अटल क्रमागत घातer_supply_property tosa_bat_bu_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_PRESENT,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc tosa_bat_मुख्य_desc = अणु
	.name		= "main-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= tosa_bat_मुख्य_props,
	.num_properties	= ARRAY_SIZE(tosa_bat_मुख्य_props),
	.get_property	= tosa_bat_get_property,
	.बाह्यal_घातer_changed = tosa_bat_बाह्यal_घातer_changed,
	.use_क्रम_apm	= 1,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc tosa_bat_jacket_desc = अणु
	.name		= "jacket-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= tosa_bat_मुख्य_props,
	.num_properties	= ARRAY_SIZE(tosa_bat_मुख्य_props),
	.get_property	= tosa_bat_get_property,
	.बाह्यal_घातer_changed = tosa_bat_बाह्यal_घातer_changed,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc tosa_bat_bu_desc = अणु
	.name		= "backup-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= tosa_bat_bu_props,
	.num_properties	= ARRAY_SIZE(tosa_bat_bu_props),
	.get_property	= tosa_bat_get_property,
	.बाह्यal_घातer_changed = tosa_bat_बाह्यal_घातer_changed,
पूर्ण;

अटल काष्ठा tosa_bat tosa_bat_मुख्य = अणु
	.status = POWER_SUPPLY_STATUS_DISCHARGING,
	.full_chrg = -1,
	.psy = शून्य,

	.gpio_full = TOSA_GPIO_BAT0_CRG,
	.gpio_अक्षरge_off = TOSA_GPIO_CHARGE_OFF,

	.technology = POWER_SUPPLY_TECHNOLOGY_LIPO,

	.gpio_bat = TOSA_GPIO_BAT0_V_ON,
	.adc_bat = WM97XX_AUX_ID3,
	.adc_bat_भागider = 414,
	.bat_max = 4310000,
	.bat_min = 1551 * 1000000 / 414,

	.gpio_temp = TOSA_GPIO_BAT1_TH_ON,
	.adc_temp = WM97XX_AUX_ID2,
	.adc_temp_भागider = 10000,
पूर्ण;

अटल काष्ठा tosa_bat tosa_bat_jacket = अणु
	.status = POWER_SUPPLY_STATUS_DISCHARGING,
	.full_chrg = -1,
	.psy = शून्य,

	.is_present = tosa_jacket_bat_is_present,
	.gpio_full = TOSA_GPIO_BAT1_CRG,
	.gpio_अक्षरge_off = TOSA_GPIO_CHARGE_OFF_JC,

	.technology = POWER_SUPPLY_TECHNOLOGY_LIPO,

	.gpio_bat = TOSA_GPIO_BAT1_V_ON,
	.adc_bat = WM97XX_AUX_ID3,
	.adc_bat_भागider = 414,
	.bat_max = 4310000,
	.bat_min = 1551 * 1000000 / 414,

	.gpio_temp = TOSA_GPIO_BAT0_TH_ON,
	.adc_temp = WM97XX_AUX_ID2,
	.adc_temp_भागider = 10000,
पूर्ण;

अटल काष्ठा tosa_bat tosa_bat_bu = अणु
	.status = POWER_SUPPLY_STATUS_UNKNOWN,
	.full_chrg = -1,
	.psy = शून्य,

	.gpio_full = -1,
	.gpio_अक्षरge_off = -1,

	.technology = POWER_SUPPLY_TECHNOLOGY_LiMn,

	.gpio_bat = TOSA_GPIO_BU_CHRG_ON,
	.adc_bat = WM97XX_AUX_ID4,
	.adc_bat_भागider = 1266,

	.gpio_temp = -1,
	.adc_temp = -1,
	.adc_temp_भागider = -1,
पूर्ण;

अटल काष्ठा gpio tosa_bat_gpios[] = अणु
	अणु TOSA_GPIO_CHARGE_OFF,	   GPIOF_OUT_INIT_HIGH, "main charge off" पूर्ण,
	अणु TOSA_GPIO_CHARGE_OFF_JC, GPIOF_OUT_INIT_HIGH, "jacket charge off" पूर्ण,
	अणु TOSA_GPIO_BAT_SW_ON,	   GPIOF_OUT_INIT_LOW,	"battery switch" पूर्ण,
	अणु TOSA_GPIO_BAT0_V_ON,	   GPIOF_OUT_INIT_LOW,	"main battery" पूर्ण,
	अणु TOSA_GPIO_BAT1_V_ON,	   GPIOF_OUT_INIT_LOW,	"jacket battery" पूर्ण,
	अणु TOSA_GPIO_BAT1_TH_ON,	   GPIOF_OUT_INIT_LOW,	"main battery temp" पूर्ण,
	अणु TOSA_GPIO_BAT0_TH_ON,	   GPIOF_OUT_INIT_LOW,	"jacket battery temp" पूर्ण,
	अणु TOSA_GPIO_BU_CHRG_ON,	   GPIOF_OUT_INIT_LOW,	"backup battery" पूर्ण,
	अणु TOSA_GPIO_BAT0_CRG,	   GPIOF_IN,		"main battery full" पूर्ण,
	अणु TOSA_GPIO_BAT1_CRG,	   GPIOF_IN,		"jacket battery full" पूर्ण,
	अणु TOSA_GPIO_BAT0_LOW,	   GPIOF_IN,		"main battery low" पूर्ण,
	अणु TOSA_GPIO_BAT1_LOW,	   GPIOF_IN,		"jacket battery low" पूर्ण,
	अणु TOSA_GPIO_JACKET_DETECT, GPIOF_IN,		"jacket detect" पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tosa_bat_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	/* flush all pending status updates */
	flush_work(&bat_work);
	वापस 0;
पूर्ण

अटल पूर्णांक tosa_bat_resume(काष्ठा platक्रमm_device *dev)
अणु
	/* things may have changed जबतक we were away */
	schedule_work(&bat_work);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा tosa_bat_suspend शून्य
#घोषणा tosa_bat_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक tosa_bat_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret;
	काष्ठा घातer_supply_config मुख्य_psy_cfg = अणुपूर्ण,
				   jacket_psy_cfg = अणुपूर्ण,
				   bu_psy_cfg = अणुपूर्ण;

	अगर (!machine_is_tosa())
		वापस -ENODEV;

	ret = gpio_request_array(tosa_bat_gpios, ARRAY_SIZE(tosa_bat_gpios));
	अगर (ret)
		वापस ret;

	mutex_init(&tosa_bat_मुख्य.work_lock);
	mutex_init(&tosa_bat_jacket.work_lock);

	INIT_WORK(&bat_work, tosa_bat_work);

	मुख्य_psy_cfg.drv_data = &tosa_bat_मुख्य;
	tosa_bat_मुख्य.psy = घातer_supply_रेजिस्टर(&dev->dev,
						  &tosa_bat_मुख्य_desc,
						  &मुख्य_psy_cfg);
	अगर (IS_ERR(tosa_bat_मुख्य.psy)) अणु
		ret = PTR_ERR(tosa_bat_मुख्य.psy);
		जाओ err_psy_reg_मुख्य;
	पूर्ण

	jacket_psy_cfg.drv_data = &tosa_bat_jacket;
	tosa_bat_jacket.psy = घातer_supply_रेजिस्टर(&dev->dev,
						    &tosa_bat_jacket_desc,
						    &jacket_psy_cfg);
	अगर (IS_ERR(tosa_bat_jacket.psy)) अणु
		ret = PTR_ERR(tosa_bat_jacket.psy);
		जाओ err_psy_reg_jacket;
	पूर्ण

	bu_psy_cfg.drv_data = &tosa_bat_bu;
	tosa_bat_bu.psy = घातer_supply_रेजिस्टर(&dev->dev, &tosa_bat_bu_desc,
						&bu_psy_cfg);
	अगर (IS_ERR(tosa_bat_bu.psy)) अणु
		ret = PTR_ERR(tosa_bat_bu.psy);
		जाओ err_psy_reg_bu;
	पूर्ण

	ret = request_irq(gpio_to_irq(TOSA_GPIO_BAT0_CRG),
				tosa_bat_gpio_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"main full", &tosa_bat_मुख्य);
	अगर (ret)
		जाओ err_req_मुख्य;

	ret = request_irq(gpio_to_irq(TOSA_GPIO_BAT1_CRG),
				tosa_bat_gpio_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"jacket full", &tosa_bat_jacket);
	अगर (ret)
		जाओ err_req_jacket;

	ret = request_irq(gpio_to_irq(TOSA_GPIO_JACKET_DETECT),
				tosa_bat_gpio_isr,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"jacket detect", &tosa_bat_jacket);
	अगर (!ret) अणु
		schedule_work(&bat_work);
		वापस 0;
	पूर्ण

	मुक्त_irq(gpio_to_irq(TOSA_GPIO_BAT1_CRG), &tosa_bat_jacket);
err_req_jacket:
	मुक्त_irq(gpio_to_irq(TOSA_GPIO_BAT0_CRG), &tosa_bat_मुख्य);
err_req_मुख्य:
	घातer_supply_unरेजिस्टर(tosa_bat_bu.psy);
err_psy_reg_bu:
	घातer_supply_unरेजिस्टर(tosa_bat_jacket.psy);
err_psy_reg_jacket:
	घातer_supply_unरेजिस्टर(tosa_bat_मुख्य.psy);
err_psy_reg_मुख्य:

	/* see comment in tosa_bat_हटाओ */
	cancel_work_sync(&bat_work);

	gpio_मुक्त_array(tosa_bat_gpios, ARRAY_SIZE(tosa_bat_gpios));
	वापस ret;
पूर्ण

अटल पूर्णांक tosa_bat_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	मुक्त_irq(gpio_to_irq(TOSA_GPIO_JACKET_DETECT), &tosa_bat_jacket);
	मुक्त_irq(gpio_to_irq(TOSA_GPIO_BAT1_CRG), &tosa_bat_jacket);
	मुक्त_irq(gpio_to_irq(TOSA_GPIO_BAT0_CRG), &tosa_bat_मुख्य);

	घातer_supply_unरेजिस्टर(tosa_bat_bu.psy);
	घातer_supply_unरेजिस्टर(tosa_bat_jacket.psy);
	घातer_supply_unरेजिस्टर(tosa_bat_मुख्य.psy);

	/*
	 * Now cancel the bat_work.  We won't get any more schedules,
	 * since all sources (isr and बाह्यal_घातer_changed) are
	 * unरेजिस्टरed now.
	 */
	cancel_work_sync(&bat_work);
	gpio_मुक्त_array(tosa_bat_gpios, ARRAY_SIZE(tosa_bat_gpios));
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tosa_bat_driver = अणु
	.driver.name	= "wm97xx-battery",
	.driver.owner	= THIS_MODULE,
	.probe		= tosa_bat_probe,
	.हटाओ		= tosa_bat_हटाओ,
	.suspend	= tosa_bat_suspend,
	.resume		= tosa_bat_resume,
पूर्ण;

module_platक्रमm_driver(tosa_bat_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dmitry Baryshkov");
MODULE_DESCRIPTION("Tosa battery driver");
MODULE_ALIAS("platform:wm97xx-battery");
