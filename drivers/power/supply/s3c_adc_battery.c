<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// iPAQ h1930/h1940/rx1950 battery controller driver
// Copyright (c) Vasily Khoruzhick
// Based on h1940_battery.c by Arnaud Patard

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/s3c_adc_battery.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

#समावेश <linux/soc/samsung/s3c-adc.h>

#घोषणा BAT_POLL_INTERVAL		10000 /* ms */
#घोषणा JITTER_DELAY			500 /* ms */

काष्ठा s3c_adc_bat अणु
	काष्ठा घातer_supply		*psy;
	काष्ठा s3c_adc_client		*client;
	काष्ठा s3c_adc_bat_pdata	*pdata;
	काष्ठा gpio_desc		*अक्षरge_finished;
	पूर्णांक				volt_value;
	पूर्णांक				cur_value;
	अचिन्हित पूर्णांक			बारtamp;
	पूर्णांक				level;
	पूर्णांक				status;
	पूर्णांक				cable_plugged:1;
पूर्ण;

अटल काष्ठा delayed_work bat_work;

अटल व्योम s3c_adc_bat_ext_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	schedule_delayed_work(&bat_work,
		msecs_to_jअगरfies(JITTER_DELAY));
पूर्ण

अटल पूर्णांक gather_samples(काष्ठा s3c_adc_client *client, पूर्णांक num, पूर्णांक channel)
अणु
	पूर्णांक value, i;

	/* शेष to 1 अगर nothing is set */
	अगर (num < 1)
		num = 1;

	value = 0;
	क्रम (i = 0; i < num; i++)
		value += s3c_adc_पढ़ो(client, channel);
	value /= num;

	वापस value;
पूर्ण

अटल क्रमागत घातer_supply_property s3c_adc_backup_bat_props[] = अणु
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MIN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
पूर्ण;

अटल पूर्णांक s3c_adc_backup_bat_get_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा s3c_adc_bat *bat = घातer_supply_get_drvdata(psy);

	अगर (!bat) अणु
		dev_err(&psy->dev, "%s: no battery infos ?!\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (bat->volt_value < 0 ||
		jअगरfies_to_msecs(jअगरfies - bat->बारtamp) >
			BAT_POLL_INTERVAL) अणु
		bat->volt_value = gather_samples(bat->client,
			bat->pdata->backup_volt_samples,
			bat->pdata->backup_volt_channel);
		bat->volt_value *= bat->pdata->backup_volt_mult;
		bat->बारtamp = jअगरfies;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = bat->volt_value;
		वापस 0;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN:
		val->पूर्णांकval = bat->pdata->backup_volt_min;
		वापस 0;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = bat->pdata->backup_volt_max;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc backup_bat_desc = अणु
	.name		= "backup-battery",
	.type		= POWER_SUPPLY_TYPE_BATTERY,
	.properties	= s3c_adc_backup_bat_props,
	.num_properties = ARRAY_SIZE(s3c_adc_backup_bat_props),
	.get_property	= s3c_adc_backup_bat_get_property,
	.use_क्रम_apm	= 1,
पूर्ण;

अटल काष्ठा s3c_adc_bat backup_bat;

अटल क्रमागत घातer_supply_property s3c_adc_मुख्य_bat_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
पूर्ण;

अटल पूर्णांक calc_full_volt(पूर्णांक volt_val, पूर्णांक cur_val, पूर्णांक impedance)
अणु
	वापस volt_val + cur_val * impedance / 1000;
पूर्ण

अटल पूर्णांक अक्षरge_finished(काष्ठा s3c_adc_bat *bat)
अणु
	वापस gpiod_get_value(bat->अक्षरge_finished);
पूर्ण

अटल पूर्णांक s3c_adc_bat_get_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा s3c_adc_bat *bat = घातer_supply_get_drvdata(psy);

	पूर्णांक new_level;
	पूर्णांक full_volt;
	स्थिर काष्ठा s3c_adc_bat_thresh *lut;
	अचिन्हित पूर्णांक lut_size;

	अगर (!bat) अणु
		dev_err(&psy->dev, "no battery infos ?!\n");
		वापस -EINVAL;
	पूर्ण

	lut = bat->pdata->lut_noac;
	lut_size = bat->pdata->lut_noac_cnt;

	अगर (bat->volt_value < 0 || bat->cur_value < 0 ||
		jअगरfies_to_msecs(jअगरfies - bat->बारtamp) >
			BAT_POLL_INTERVAL) अणु
		bat->volt_value = gather_samples(bat->client,
			bat->pdata->volt_samples,
			bat->pdata->volt_channel) * bat->pdata->volt_mult;
		bat->cur_value = gather_samples(bat->client,
			bat->pdata->current_samples,
			bat->pdata->current_channel) * bat->pdata->current_mult;
		bat->बारtamp = jअगरfies;
	पूर्ण

	अगर (bat->cable_plugged &&
		(!bat->अक्षरge_finished ||
		!अक्षरge_finished(bat))) अणु
		lut = bat->pdata->lut_acin;
		lut_size = bat->pdata->lut_acin_cnt;
	पूर्ण

	new_level = 100000;
	full_volt = calc_full_volt((bat->volt_value / 1000),
		(bat->cur_value / 1000), bat->pdata->पूर्णांकernal_impedance);

	अगर (full_volt < calc_full_volt(lut->volt, lut->cur,
		bat->pdata->पूर्णांकernal_impedance)) अणु
		lut_size--;
		जबतक (lut_size--) अणु
			पूर्णांक lut_volt1;
			पूर्णांक lut_volt2;

			lut_volt1 = calc_full_volt(lut[0].volt, lut[0].cur,
				bat->pdata->पूर्णांकernal_impedance);
			lut_volt2 = calc_full_volt(lut[1].volt, lut[1].cur,
				bat->pdata->पूर्णांकernal_impedance);
			अगर (full_volt < lut_volt1 && full_volt >= lut_volt2) अणु
				new_level = (lut[1].level +
					(lut[0].level - lut[1].level) *
					(full_volt - lut_volt2) /
					(lut_volt1 - lut_volt2)) * 1000;
				अवरोध;
			पूर्ण
			new_level = lut[1].level * 1000;
			lut++;
		पूर्ण
	पूर्ण

	bat->level = new_level;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (!bat->अक्षरge_finished)
			val->पूर्णांकval = bat->level == 100000 ?
				POWER_SUPPLY_STATUS_FULL : bat->status;
		अन्यथा
			val->पूर्णांकval = bat->status;
		वापस 0;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = 100000;
		वापस 0;
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN:
		val->पूर्णांकval = 0;
		वापस 0;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		val->पूर्णांकval = bat->level;
		वापस 0;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = bat->volt_value;
		वापस 0;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = bat->cur_value;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc मुख्य_bat_desc = अणु
	.name			= "main-battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= s3c_adc_मुख्य_bat_props,
	.num_properties		= ARRAY_SIZE(s3c_adc_मुख्य_bat_props),
	.get_property		= s3c_adc_bat_get_property,
	.बाह्यal_घातer_changed = s3c_adc_bat_ext_घातer_changed,
	.use_क्रम_apm		= 1,
पूर्ण;

अटल काष्ठा s3c_adc_bat मुख्य_bat;

अटल व्योम s3c_adc_bat_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा s3c_adc_bat *bat = &मुख्य_bat;
	पूर्णांक is_अक्षरged;
	पूर्णांक is_plugged;
	अटल पूर्णांक was_plugged;

	is_plugged = घातer_supply_am_i_supplied(bat->psy);
	bat->cable_plugged = is_plugged;
	अगर (is_plugged != was_plugged) अणु
		was_plugged = is_plugged;
		अगर (is_plugged) अणु
			अगर (bat->pdata->enable_अक्षरger)
				bat->pdata->enable_अक्षरger();
			bat->status = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण अन्यथा अणु
			अगर (bat->pdata->disable_अक्षरger)
				bat->pdata->disable_अक्षरger();
			bat->status = POWER_SUPPLY_STATUS_DISCHARGING;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bat->अक्षरge_finished && is_plugged) अणु
			is_अक्षरged = अक्षरge_finished(&मुख्य_bat);
			अगर (is_अक्षरged) अणु
				अगर (bat->pdata->disable_अक्षरger)
					bat->pdata->disable_अक्षरger();
				bat->status = POWER_SUPPLY_STATUS_FULL;
			पूर्ण अन्यथा अणु
				अगर (bat->pdata->enable_अक्षरger)
					bat->pdata->enable_अक्षरger();
				bat->status = POWER_SUPPLY_STATUS_CHARGING;
			पूर्ण
		पूर्ण
	पूर्ण

	घातer_supply_changed(bat->psy);
पूर्ण

अटल irqवापस_t s3c_adc_bat_अक्षरged(पूर्णांक irq, व्योम *dev_id)
अणु
	schedule_delayed_work(&bat_work,
		msecs_to_jअगरfies(JITTER_DELAY));
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक s3c_adc_bat_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_adc_client	*client;
	काष्ठा s3c_adc_bat_pdata *pdata = pdev->dev.platक्रमm_data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा gpio_desc *gpiod;
	पूर्णांक ret;

	client = s3c_adc_रेजिस्टर(pdev, शून्य, शून्य, 0);
	अगर (IS_ERR(client)) अणु
		dev_err(&pdev->dev, "cannot register adc\n");
		वापस PTR_ERR(client);
	पूर्ण

	platक्रमm_set_drvdata(pdev, client);

	gpiod = devm_gpiod_get_optional(&pdev->dev, "charge-status", GPIOD_IN);
	अगर (IS_ERR(gpiod)) अणु
		/* Could be probe deferral etc */
		ret = PTR_ERR(gpiod);
		dev_err(&pdev->dev, "no GPIO %d\n", ret);
		वापस ret;
	पूर्ण

	मुख्य_bat.client = client;
	मुख्य_bat.pdata = pdata;
	मुख्य_bat.अक्षरge_finished = gpiod;
	मुख्य_bat.volt_value = -1;
	मुख्य_bat.cur_value = -1;
	मुख्य_bat.cable_plugged = 0;
	मुख्य_bat.status = POWER_SUPPLY_STATUS_DISCHARGING;
	psy_cfg.drv_data = &मुख्य_bat;

	मुख्य_bat.psy = घातer_supply_रेजिस्टर(&pdev->dev, &मुख्य_bat_desc, &psy_cfg);
	अगर (IS_ERR(मुख्य_bat.psy)) अणु
		ret = PTR_ERR(मुख्य_bat.psy);
		जाओ err_reg_मुख्य;
	पूर्ण
	अगर (pdata->backup_volt_mult) अणु
		स्थिर काष्ठा घातer_supply_config backup_psy_cfg
						= अणु .drv_data = &backup_bat, पूर्ण;

		backup_bat.client = client;
		backup_bat.pdata = pdev->dev.platक्रमm_data;
		backup_bat.अक्षरge_finished = gpiod;
		backup_bat.volt_value = -1;
		backup_bat.psy = घातer_supply_रेजिस्टर(&pdev->dev,
						       &backup_bat_desc,
						       &backup_psy_cfg);
		अगर (IS_ERR(backup_bat.psy)) अणु
			ret = PTR_ERR(backup_bat.psy);
			जाओ err_reg_backup;
		पूर्ण
	पूर्ण

	INIT_DELAYED_WORK(&bat_work, s3c_adc_bat_work);

	अगर (gpiod) अणु
		ret = request_irq(gpiod_to_irq(gpiod),
				s3c_adc_bat_अक्षरged,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"battery charged", शून्य);
		अगर (ret)
			जाओ err_irq;
	पूर्ण

	अगर (pdata->init) अणु
		ret = pdata->init();
		अगर (ret)
			जाओ err_platक्रमm;
	पूर्ण

	dev_info(&pdev->dev, "successfully loaded\n");
	device_init_wakeup(&pdev->dev, 1);

	/* Schedule समयr to check current status */
	schedule_delayed_work(&bat_work,
		msecs_to_jअगरfies(JITTER_DELAY));

	वापस 0;

err_platक्रमm:
	अगर (gpiod)
		मुक्त_irq(gpiod_to_irq(gpiod), शून्य);
err_irq:
	अगर (pdata->backup_volt_mult)
		घातer_supply_unरेजिस्टर(backup_bat.psy);
err_reg_backup:
	घातer_supply_unरेजिस्टर(मुख्य_bat.psy);
err_reg_मुख्य:
	वापस ret;
पूर्ण

अटल पूर्णांक s3c_adc_bat_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c_adc_client *client = platक्रमm_get_drvdata(pdev);
	काष्ठा s3c_adc_bat_pdata *pdata = pdev->dev.platक्रमm_data;

	घातer_supply_unरेजिस्टर(मुख्य_bat.psy);
	अगर (pdata->backup_volt_mult)
		घातer_supply_unरेजिस्टर(backup_bat.psy);

	s3c_adc_release(client);

	अगर (मुख्य_bat.अक्षरge_finished)
		मुक्त_irq(gpiod_to_irq(मुख्य_bat.अक्षरge_finished), शून्य);

	cancel_delayed_work_sync(&bat_work);

	अगर (pdata->निकास)
		pdata->निकास();

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक s3c_adc_bat_suspend(काष्ठा platक्रमm_device *pdev,
	pm_message_t state)
अणु
	अगर (मुख्य_bat.अक्षरge_finished) अणु
		अगर (device_may_wakeup(&pdev->dev))
			enable_irq_wake(
				gpiod_to_irq(मुख्य_bat.अक्षरge_finished));
		अन्यथा अणु
			disable_irq(gpiod_to_irq(मुख्य_bat.अक्षरge_finished));
			मुख्य_bat.pdata->disable_अक्षरger();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c_adc_bat_resume(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (मुख्य_bat.अक्षरge_finished) अणु
		अगर (device_may_wakeup(&pdev->dev))
			disable_irq_wake(
				gpiod_to_irq(मुख्य_bat.अक्षरge_finished));
		अन्यथा
			enable_irq(gpiod_to_irq(मुख्य_bat.अक्षरge_finished));
	पूर्ण

	/* Schedule समयr to check current status */
	schedule_delayed_work(&bat_work,
		msecs_to_jअगरfies(JITTER_DELAY));

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा s3c_adc_bat_suspend शून्य
#घोषणा s3c_adc_bat_resume शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver s3c_adc_bat_driver = अणु
	.driver		= अणु
		.name	= "s3c-adc-battery",
	पूर्ण,
	.probe		= s3c_adc_bat_probe,
	.हटाओ		= s3c_adc_bat_हटाओ,
	.suspend	= s3c_adc_bat_suspend,
	.resume		= s3c_adc_bat_resume,
पूर्ण;

module_platक्रमm_driver(s3c_adc_bat_driver);

MODULE_AUTHOR("Vasily Khoruzhick <anarsoul@gmail.com>");
MODULE_DESCRIPTION("iPAQ H1930/H1940/RX1950 battery controller driver");
MODULE_LICENSE("GPL");
