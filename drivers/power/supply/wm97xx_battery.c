<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Battery measurement code क्रम WM97xx
 *
 * based on tosa_battery.c
 *
 * Copyright (C) 2008 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/wm97xx.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>

अटल काष्ठा work_काष्ठा bat_work;
अटल काष्ठा gpio_desc *अक्षरge_gpiod;
अटल DEFINE_MUTEX(work_lock);
अटल पूर्णांक bat_status = POWER_SUPPLY_STATUS_UNKNOWN;
अटल क्रमागत घातer_supply_property *prop;

अटल अचिन्हित दीर्घ wm97xx_पढ़ो_bat(काष्ठा घातer_supply *bat_ps)
अणु
	काष्ठा wm97xx_batt_pdata *pdata = घातer_supply_get_drvdata(bat_ps);

	वापस wm97xx_पढ़ो_aux_adc(dev_get_drvdata(bat_ps->dev.parent),
					pdata->batt_aux) * pdata->batt_mult /
					pdata->batt_भाग;
पूर्ण

अटल अचिन्हित दीर्घ wm97xx_पढ़ो_temp(काष्ठा घातer_supply *bat_ps)
अणु
	काष्ठा wm97xx_batt_pdata *pdata = घातer_supply_get_drvdata(bat_ps);

	वापस wm97xx_पढ़ो_aux_adc(dev_get_drvdata(bat_ps->dev.parent),
					pdata->temp_aux) * pdata->temp_mult /
					pdata->temp_भाग;
पूर्ण

अटल पूर्णांक wm97xx_bat_get_property(काष्ठा घातer_supply *bat_ps,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा wm97xx_batt_pdata *pdata = घातer_supply_get_drvdata(bat_ps);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = bat_status;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = pdata->batt_tech;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		अगर (pdata->batt_aux >= 0)
			val->पूर्णांकval = wm97xx_पढ़ो_bat(bat_ps);
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		अगर (pdata->temp_aux >= 0)
			val->पूर्णांकval = wm97xx_पढ़ो_temp(bat_ps);
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX:
		अगर (pdata->max_voltage >= 0)
			val->पूर्णांकval = pdata->max_voltage;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		अगर (pdata->min_voltage >= 0)
			val->पूर्णांकval = pdata->min_voltage;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम wm97xx_bat_बाह्यal_घातer_changed(काष्ठा घातer_supply *bat_ps)
अणु
	schedule_work(&bat_work);
पूर्ण

अटल व्योम wm97xx_bat_update(काष्ठा घातer_supply *bat_ps)
अणु
	पूर्णांक old_status = bat_status;

	mutex_lock(&work_lock);

	bat_status = (अक्षरge_gpiod) ?
			(gpiod_get_value(अक्षरge_gpiod) ?
			POWER_SUPPLY_STATUS_DISCHARGING :
			POWER_SUPPLY_STATUS_CHARGING) :
			POWER_SUPPLY_STATUS_UNKNOWN;

	अगर (old_status != bat_status) अणु
		pr_debug("%s: %i -> %i\n", bat_ps->desc->name, old_status,
					bat_status);
		घातer_supply_changed(bat_ps);
	पूर्ण

	mutex_unlock(&work_lock);
पूर्ण

अटल काष्ठा घातer_supply *bat_psy;
अटल काष्ठा घातer_supply_desc bat_psy_desc = अणु
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.get_property		= wm97xx_bat_get_property,
	.बाह्यal_घातer_changed = wm97xx_bat_बाह्यal_घातer_changed,
	.use_क्रम_apm		= 1,
पूर्ण;

अटल व्योम wm97xx_bat_work(काष्ठा work_काष्ठा *work)
अणु
	wm97xx_bat_update(bat_psy);
पूर्ण

अटल irqवापस_t wm97xx_chrg_irq(पूर्णांक irq, व्योम *data)
अणु
	schedule_work(&bat_work);
	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक wm97xx_bat_suspend(काष्ठा device *dev)
अणु
	flush_work(&bat_work);
	वापस 0;
पूर्ण

अटल पूर्णांक wm97xx_bat_resume(काष्ठा device *dev)
अणु
	schedule_work(&bat_work);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wm97xx_bat_pm_ops = अणु
	.suspend	= wm97xx_bat_suspend,
	.resume		= wm97xx_bat_resume,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक wm97xx_bat_probe(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक ret = 0;
	पूर्णांक props = 1;	/* POWER_SUPPLY_PROP_PRESENT */
	पूर्णांक i = 0;
	काष्ठा wm97xx_batt_pdata *pdata = dev->dev.platक्रमm_data;
	काष्ठा घातer_supply_config cfg = अणुपूर्ण;

	अगर (!pdata) अणु
		dev_err(&dev->dev, "No platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	cfg.drv_data = pdata;

	अगर (dev->id != -1)
		वापस -EINVAL;

	अक्षरge_gpiod = devm_gpiod_get_optional(&dev->dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(अक्षरge_gpiod))
		वापस dev_err_probe(&dev->dev,
				     PTR_ERR(अक्षरge_gpiod),
				     "failed to get charge GPIO\n");
	अगर (अक्षरge_gpiod) अणु
		gpiod_set_consumer_name(अक्षरge_gpiod, "BATT CHRG");
		ret = request_irq(gpiod_to_irq(अक्षरge_gpiod),
				wm97xx_chrg_irq, 0,
				"AC Detect", dev);
		अगर (ret)
			वापस dev_err_probe(&dev->dev, ret,
					     "failed to request GPIO irq\n");
		props++;	/* POWER_SUPPLY_PROP_STATUS */
	पूर्ण

	अगर (pdata->batt_tech >= 0)
		props++;	/* POWER_SUPPLY_PROP_TECHNOLOGY */
	अगर (pdata->temp_aux >= 0)
		props++;	/* POWER_SUPPLY_PROP_TEMP */
	अगर (pdata->batt_aux >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_NOW */
	अगर (pdata->max_voltage >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_MAX */
	अगर (pdata->min_voltage >= 0)
		props++;	/* POWER_SUPPLY_PROP_VOLTAGE_MIN */

	prop = kसुस्मृति(props, माप(*prop), GFP_KERNEL);
	अगर (!prop) अणु
		ret = -ENOMEM;
		जाओ err3;
	पूर्ण

	prop[i++] = POWER_SUPPLY_PROP_PRESENT;
	अगर (अक्षरge_gpiod)
		prop[i++] = POWER_SUPPLY_PROP_STATUS;
	अगर (pdata->batt_tech >= 0)
		prop[i++] = POWER_SUPPLY_PROP_TECHNOLOGY;
	अगर (pdata->temp_aux >= 0)
		prop[i++] = POWER_SUPPLY_PROP_TEMP;
	अगर (pdata->batt_aux >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_NOW;
	अगर (pdata->max_voltage >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_MAX;
	अगर (pdata->min_voltage >= 0)
		prop[i++] = POWER_SUPPLY_PROP_VOLTAGE_MIN;

	INIT_WORK(&bat_work, wm97xx_bat_work);

	अगर (!pdata->batt_name) अणु
		dev_info(&dev->dev, "Please consider setting proper battery "
				"name in platform definition file, falling "
				"back to name \"wm97xx-batt\"\n");
		bat_psy_desc.name = "wm97xx-batt";
	पूर्ण अन्यथा
		bat_psy_desc.name = pdata->batt_name;

	bat_psy_desc.properties = prop;
	bat_psy_desc.num_properties = props;

	bat_psy = घातer_supply_रेजिस्टर(&dev->dev, &bat_psy_desc, &cfg);
	अगर (!IS_ERR(bat_psy)) अणु
		schedule_work(&bat_work);
	पूर्ण अन्यथा अणु
		ret = PTR_ERR(bat_psy);
		जाओ err4;
	पूर्ण

	वापस 0;
err4:
	kमुक्त(prop);
err3:
	अगर (अक्षरge_gpiod)
		मुक्त_irq(gpiod_to_irq(अक्षरge_gpiod), dev);
	वापस ret;
पूर्ण

अटल पूर्णांक wm97xx_bat_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	अगर (अक्षरge_gpiod)
		मुक्त_irq(gpiod_to_irq(अक्षरge_gpiod), dev);
	cancel_work_sync(&bat_work);
	घातer_supply_unरेजिस्टर(bat_psy);
	kमुक्त(prop);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm97xx_bat_driver = अणु
	.driver	= अणु
		.name	= "wm97xx-battery",
#अगर_घोषित CONFIG_PM
		.pm	= &wm97xx_bat_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.probe		= wm97xx_bat_probe,
	.हटाओ		= wm97xx_bat_हटाओ,
पूर्ण;

module_platक्रमm_driver(wm97xx_bat_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marek Vasut <marek.vasut@gmail.com>");
MODULE_DESCRIPTION("WM97xx battery driver");
