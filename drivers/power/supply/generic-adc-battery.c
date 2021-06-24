<शैली गुरु>
/*
 * Generic battery driver code using IIO
 * Copyright (C) 2012, Anish Kumar <anish198519851985@gmail.com>
 * based on jz4740-battery.c
 * based on s3c_adc_battery.c
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
 */
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/समयr.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/घातer/generic-adc-battery.h>

#घोषणा JITTER_DEFAULT 10 /* hope 10ms is enough */

क्रमागत gab_chan_type अणु
	GAB_VOLTAGE = 0,
	GAB_CURRENT,
	GAB_POWER,
	GAB_MAX_CHAN_TYPE
पूर्ण;

/*
 * gab_chan_name suggests the standard channel names क्रम commonly used
 * channel types.
 */
अटल स्थिर अक्षर *स्थिर gab_chan_name[] = अणु
	[GAB_VOLTAGE]	= "voltage",
	[GAB_CURRENT]	= "current",
	[GAB_POWER]		= "power",
पूर्ण;

काष्ठा gab अणु
	काष्ठा घातer_supply		*psy;
	काष्ठा घातer_supply_desc	psy_desc;
	काष्ठा iio_channel	*channel[GAB_MAX_CHAN_TYPE];
	काष्ठा gab_platक्रमm_data	*pdata;
	काष्ठा delayed_work bat_work;
	पूर्णांक	level;
	पूर्णांक	status;
	bool cable_plugged;
	काष्ठा gpio_desc *अक्षरge_finished;
पूर्ण;

अटल काष्ठा gab *to_generic_bat(काष्ठा घातer_supply *psy)
अणु
	वापस घातer_supply_get_drvdata(psy);
पूर्ण

अटल व्योम gab_ext_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा gab *adc_bat = to_generic_bat(psy);

	schedule_delayed_work(&adc_bat->bat_work, msecs_to_jअगरfies(0));
पूर्ण

अटल स्थिर क्रमागत घातer_supply_property gab_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_MODEL_NAME,
पूर्ण;

/*
 * This properties are set based on the received platक्रमm data and this
 * should correspond one-to-one with क्रमागत chan_type.
 */
अटल स्थिर क्रमागत घातer_supply_property gab_dyn_props[] = अणु
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_POWER_NOW,
पूर्ण;

अटल bool gab_अक्षरge_finished(काष्ठा gab *adc_bat)
अणु
	अगर (!adc_bat->अक्षरge_finished)
		वापस false;
	वापस gpiod_get_value(adc_bat->अक्षरge_finished);
पूर्ण

अटल पूर्णांक gab_get_status(काष्ठा gab *adc_bat)
अणु
	काष्ठा gab_platक्रमm_data *pdata = adc_bat->pdata;
	काष्ठा घातer_supply_info *bat_info;

	bat_info = &pdata->battery_info;
	अगर (adc_bat->level == bat_info->अक्षरge_full_design)
		वापस POWER_SUPPLY_STATUS_FULL;
	वापस adc_bat->status;
पूर्ण

अटल क्रमागत gab_chan_type gab_prop_to_chan(क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		वापस GAB_POWER;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		वापस GAB_VOLTAGE;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		वापस GAB_CURRENT;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
	वापस GAB_POWER;
पूर्ण

अटल पूर्णांक पढ़ो_channel(काष्ठा gab *adc_bat, क्रमागत घातer_supply_property psp,
		पूर्णांक *result)
अणु
	पूर्णांक ret;
	पूर्णांक chan_index;

	chan_index = gab_prop_to_chan(psp);
	ret = iio_पढ़ो_channel_processed(adc_bat->channel[chan_index],
			result);
	अगर (ret < 0)
		pr_err("read channel error\n");
	वापस ret;
पूर्ण

अटल पूर्णांक gab_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
	काष्ठा gab *adc_bat;
	काष्ठा gab_platक्रमm_data *pdata;
	काष्ठा घातer_supply_info *bat_info;
	पूर्णांक result = 0;
	पूर्णांक ret = 0;

	adc_bat = to_generic_bat(psy);
	अगर (!adc_bat) अणु
		dev_err(&psy->dev, "no battery infos ?!\n");
		वापस -EINVAL;
	पूर्ण
	pdata = adc_bat->pdata;
	bat_info = &pdata->battery_info;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = gab_get_status(adc_bat);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_EMPTY_DESIGN:
		val->पूर्णांकval = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
		val->पूर्णांकval = pdata->cal_अक्षरge(result);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_POWER_NOW:
		ret = पढ़ो_channel(adc_bat, psp, &result);
		अगर (ret < 0)
			जाओ err;
		val->पूर्णांकval = result;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = bat_info->technology;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->पूर्णांकval = bat_info->voltage_min_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = bat_info->voltage_max_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = bat_info->अक्षरge_full_design;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bat_info->name;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
err:
	वापस ret;
पूर्ण

अटल व्योम gab_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gab *adc_bat;
	काष्ठा delayed_work *delayed_work;
	bool is_plugged;
	पूर्णांक status;

	delayed_work = to_delayed_work(work);
	adc_bat = container_of(delayed_work, काष्ठा gab, bat_work);
	status = adc_bat->status;

	is_plugged = घातer_supply_am_i_supplied(adc_bat->psy);
	adc_bat->cable_plugged = is_plugged;

	अगर (!is_plugged)
		adc_bat->status =  POWER_SUPPLY_STATUS_DISCHARGING;
	अन्यथा अगर (gab_अक्षरge_finished(adc_bat))
		adc_bat->status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	अन्यथा
		adc_bat->status = POWER_SUPPLY_STATUS_CHARGING;

	अगर (status != adc_bat->status)
		घातer_supply_changed(adc_bat->psy);
पूर्ण

अटल irqवापस_t gab_अक्षरged(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा gab *adc_bat = dev_id;
	काष्ठा gab_platक्रमm_data *pdata = adc_bat->pdata;
	पूर्णांक delay;

	delay = pdata->jitter_delay ? pdata->jitter_delay : JITTER_DEFAULT;
	schedule_delayed_work(&adc_bat->bat_work,
			msecs_to_jअगरfies(delay));
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gab_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gab *adc_bat;
	काष्ठा घातer_supply_desc *psy_desc;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा gab_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	क्रमागत घातer_supply_property *properties;
	पूर्णांक ret = 0;
	पूर्णांक chan;
	पूर्णांक index = ARRAY_SIZE(gab_props);
	bool any = false;

	adc_bat = devm_kzalloc(&pdev->dev, माप(*adc_bat), GFP_KERNEL);
	अगर (!adc_bat) अणु
		dev_err(&pdev->dev, "failed to allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	psy_cfg.drv_data = adc_bat;
	psy_desc = &adc_bat->psy_desc;
	psy_desc->name = pdata->battery_info.name;

	/* bootup शेष values क्रम the battery */
	adc_bat->cable_plugged = false;
	adc_bat->status = POWER_SUPPLY_STATUS_DISCHARGING;
	psy_desc->type = POWER_SUPPLY_TYPE_BATTERY;
	psy_desc->get_property = gab_get_property;
	psy_desc->बाह्यal_घातer_changed = gab_ext_घातer_changed;
	adc_bat->pdata = pdata;

	/*
	 * copying the अटल properties and allocating extra memory क्रम holding
	 * the extra configurable properties received from platक्रमm data.
	 */
	properties = kसुस्मृति(ARRAY_SIZE(gab_props) +
			     ARRAY_SIZE(gab_chan_name),
			     माप(*properties),
			     GFP_KERNEL);
	अगर (!properties) अणु
		ret = -ENOMEM;
		जाओ first_mem_fail;
	पूर्ण

	स_नकल(properties, gab_props, माप(gab_props));

	/*
	 * getting channel from iio and copying the battery properties
	 * based on the channel supported by consumer device.
	 */
	क्रम (chan = 0; chan < ARRAY_SIZE(gab_chan_name); chan++) अणु
		adc_bat->channel[chan] = iio_channel_get(&pdev->dev,
							 gab_chan_name[chan]);
		अगर (IS_ERR(adc_bat->channel[chan])) अणु
			ret = PTR_ERR(adc_bat->channel[chan]);
			adc_bat->channel[chan] = शून्य;
		पूर्ण अन्यथा अणु
			/* copying properties क्रम supported channels only */
			पूर्णांक index2;

			क्रम (index2 = 0; index2 < index; index2++) अणु
				अगर (properties[index2] == gab_dyn_props[chan])
					अवरोध;	/* alपढ़ोy known */
			पूर्ण
			अगर (index2 == index)	/* really new */
				properties[index++] = gab_dyn_props[chan];
			any = true;
		पूर्ण
	पूर्ण

	/* none of the channels are supported so let's bail out */
	अगर (!any) अणु
		ret = -ENODEV;
		जाओ second_mem_fail;
	पूर्ण

	/*
	 * Total number of properties is equal to अटल properties
	 * plus the dynamic properties.Some properties may not be set
	 * as come channels may be not be supported by the device.So
	 * we need to take care of that.
	 */
	psy_desc->properties = properties;
	psy_desc->num_properties = index;

	adc_bat->psy = घातer_supply_रेजिस्टर(&pdev->dev, psy_desc, &psy_cfg);
	अगर (IS_ERR(adc_bat->psy)) अणु
		ret = PTR_ERR(adc_bat->psy);
		जाओ err_reg_fail;
	पूर्ण

	INIT_DELAYED_WORK(&adc_bat->bat_work, gab_work);

	adc_bat->अक्षरge_finished = devm_gpiod_get_optional(&pdev->dev,
							   "charged", GPIOD_IN);
	अगर (adc_bat->अक्षरge_finished) अणु
		पूर्णांक irq;

		irq = gpiod_to_irq(adc_bat->अक्षरge_finished);
		ret = request_any_context_irq(irq, gab_अक्षरged,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				"battery charged", adc_bat);
		अगर (ret < 0)
			जाओ gpio_req_fail;
	पूर्ण

	platक्रमm_set_drvdata(pdev, adc_bat);

	/* Schedule समयr to check current status */
	schedule_delayed_work(&adc_bat->bat_work,
			msecs_to_jअगरfies(0));
	वापस 0;

gpio_req_fail:
	घातer_supply_unरेजिस्टर(adc_bat->psy);
err_reg_fail:
	क्रम (chan = 0; chan < ARRAY_SIZE(gab_chan_name); chan++) अणु
		अगर (adc_bat->channel[chan])
			iio_channel_release(adc_bat->channel[chan]);
	पूर्ण
second_mem_fail:
	kमुक्त(properties);
first_mem_fail:
	वापस ret;
पूर्ण

अटल पूर्णांक gab_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक chan;
	काष्ठा gab *adc_bat = platक्रमm_get_drvdata(pdev);

	घातer_supply_unरेजिस्टर(adc_bat->psy);

	अगर (adc_bat->अक्षरge_finished)
		मुक्त_irq(gpiod_to_irq(adc_bat->अक्षरge_finished), adc_bat);

	क्रम (chan = 0; chan < ARRAY_SIZE(gab_chan_name); chan++) अणु
		अगर (adc_bat->channel[chan])
			iio_channel_release(adc_bat->channel[chan]);
	पूर्ण

	kमुक्त(adc_bat->psy_desc.properties);
	cancel_delayed_work_sync(&adc_bat->bat_work);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gab_suspend(काष्ठा device *dev)
अणु
	काष्ठा gab *adc_bat = dev_get_drvdata(dev);

	cancel_delayed_work_sync(&adc_bat->bat_work);
	adc_bat->status = POWER_SUPPLY_STATUS_UNKNOWN;
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused gab_resume(काष्ठा device *dev)
अणु
	काष्ठा gab *adc_bat = dev_get_drvdata(dev);
	काष्ठा gab_platक्रमm_data *pdata = adc_bat->pdata;
	पूर्णांक delay;

	delay = pdata->jitter_delay ? pdata->jitter_delay : JITTER_DEFAULT;

	/* Schedule समयr to check current status */
	schedule_delayed_work(&adc_bat->bat_work,
			msecs_to_jअगरfies(delay));
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(gab_pm_ops, gab_suspend, gab_resume);

अटल काष्ठा platक्रमm_driver gab_driver = अणु
	.driver		= अणु
		.name	= "generic-adc-battery",
		.pm	= &gab_pm_ops,
	पूर्ण,
	.probe		= gab_probe,
	.हटाओ		= gab_हटाओ,
पूर्ण;
module_platक्रमm_driver(gab_driver);

MODULE_AUTHOR("anish kumar <anish198519851985@gmail.com>");
MODULE_DESCRIPTION("generic battery driver using IIO");
MODULE_LICENSE("GPL");
