<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dumb driver क्रम LiIon batteries using TWL4030 madc.
 *
 * Copyright 2013 Golden Delicious Computers
 * Lukas Mथअrdian <lukas@goldelico.com>
 *
 * Based on dumb driver क्रम gta01 battery
 * Copyright 2009 Openmoko, Inc
 * Balaji Rao <balajirrao@खोलोmoko.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/sort.h>
#समावेश <linux/घातer/twl4030_madc_battery.h>
#समावेश <linux/iio/consumer.h>

काष्ठा twl4030_madc_battery अणु
	काष्ठा घातer_supply *psy;
	काष्ठा twl4030_madc_bat_platक्रमm_data *pdata;
	काष्ठा iio_channel *channel_temp;
	काष्ठा iio_channel *channel_ichg;
	काष्ठा iio_channel *channel_vbat;
पूर्ण;

अटल क्रमागत घातer_supply_property twl4030_madc_bat_props[] = अणु
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW,
पूर्ण;

अटल पूर्णांक madc_पढ़ो(काष्ठा iio_channel *channel)
अणु
	पूर्णांक val, err;
	err = iio_पढ़ो_channel_processed(channel, &val);
	अगर (err < 0)
		वापस err;

	वापस val;
पूर्ण

अटल पूर्णांक twl4030_madc_bat_get_अक्षरging_status(काष्ठा twl4030_madc_battery *bt)
अणु
	वापस (madc_पढ़ो(bt->channel_ichg) > 0) ? 1 : 0;
पूर्ण

अटल पूर्णांक twl4030_madc_bat_get_voltage(काष्ठा twl4030_madc_battery *bt)
अणु
	वापस madc_पढ़ो(bt->channel_vbat);
पूर्ण

अटल पूर्णांक twl4030_madc_bat_get_current(काष्ठा twl4030_madc_battery *bt)
अणु
	वापस madc_पढ़ो(bt->channel_ichg) * 1000;
पूर्ण

अटल पूर्णांक twl4030_madc_bat_get_temp(काष्ठा twl4030_madc_battery *bt)
अणु
	वापस madc_पढ़ो(bt->channel_temp) * 10;
पूर्ण

अटल पूर्णांक twl4030_madc_bat_voltscale(काष्ठा twl4030_madc_battery *bat,
					पूर्णांक volt)
अणु
	काष्ठा twl4030_madc_bat_calibration *calibration;
	पूर्णांक i, res = 0;

	/* choose अक्षरging curve */
	अगर (twl4030_madc_bat_get_अक्षरging_status(bat))
		calibration = bat->pdata->अक्षरging;
	अन्यथा
		calibration = bat->pdata->disअक्षरging;

	अगर (volt > calibration[0].voltage) अणु
		res = calibration[0].level;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; calibration[i+1].voltage >= 0; i++) अणु
			अगर (volt <= calibration[i].voltage &&
					volt >= calibration[i+1].voltage) अणु
				/* पूर्णांकerval found - पूर्णांकerpolate within range */
				res = calibration[i].level -
					((calibration[i].voltage - volt) *
					(calibration[i].level -
					calibration[i+1].level)) /
					(calibration[i].voltage -
					calibration[i+1].voltage);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक twl4030_madc_bat_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा twl4030_madc_battery *bat = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (twl4030_madc_bat_voltscale(bat,
				twl4030_madc_bat_get_voltage(bat)) > 95)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा अणु
			अगर (twl4030_madc_bat_get_अक्षरging_status(bat))
				val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अन्यथा
				val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		पूर्ण
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = twl4030_madc_bat_get_voltage(bat) * 1000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
		val->पूर्णांकval = twl4030_madc_bat_get_current(bat);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		/* assume battery is always present */
		val->पूर्णांकval = 1;
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_NOW: अणु
			पूर्णांक percent = twl4030_madc_bat_voltscale(bat,
					twl4030_madc_bat_get_voltage(bat));
			val->पूर्णांकval = (percent * bat->pdata->capacity) / 100;
			अवरोध;
		पूर्ण
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = twl4030_madc_bat_voltscale(bat,
					twl4030_madc_bat_get_voltage(bat));
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
		val->पूर्णांकval = bat->pdata->capacity;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = twl4030_madc_bat_get_temp(bat);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW: अणु
			पूर्णांक percent = twl4030_madc_bat_voltscale(bat,
					twl4030_madc_bat_get_voltage(bat));
			/* in mAh */
			पूर्णांक chg = (percent * (bat->pdata->capacity/1000))/100;

			/* assume disअक्षरge with 400 mA (ca. 1.5W) */
			val->पूर्णांकval = (3600l * chg) / 400;
			अवरोध;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twl4030_madc_bat_ext_changed(काष्ठा घातer_supply *psy)
अणु
	घातer_supply_changed(psy);
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc twl4030_madc_bat_desc = अणु
	.name			= "twl4030_battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= twl4030_madc_bat_props,
	.num_properties		= ARRAY_SIZE(twl4030_madc_bat_props),
	.get_property		= twl4030_madc_bat_get_property,
	.बाह्यal_घातer_changed	= twl4030_madc_bat_ext_changed,

पूर्ण;

अटल पूर्णांक twl4030_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस ((काष्ठा twl4030_madc_bat_calibration *)b)->voltage -
		((काष्ठा twl4030_madc_bat_calibration *)a)->voltage;
पूर्ण

अटल पूर्णांक twl4030_madc_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_madc_battery *twl4030_madc_bat;
	काष्ठा twl4030_madc_bat_platक्रमm_data *pdata = pdev->dev.platक्रमm_data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक ret = 0;

	twl4030_madc_bat = devm_kzalloc(&pdev->dev, माप(*twl4030_madc_bat),
				GFP_KERNEL);
	अगर (!twl4030_madc_bat)
		वापस -ENOMEM;

	twl4030_madc_bat->channel_temp = iio_channel_get(&pdev->dev, "temp");
	अगर (IS_ERR(twl4030_madc_bat->channel_temp)) अणु
		ret = PTR_ERR(twl4030_madc_bat->channel_temp);
		जाओ err;
	पूर्ण

	twl4030_madc_bat->channel_ichg = iio_channel_get(&pdev->dev, "ichg");
	अगर (IS_ERR(twl4030_madc_bat->channel_ichg)) अणु
		ret = PTR_ERR(twl4030_madc_bat->channel_ichg);
		जाओ err_temp;
	पूर्ण

	twl4030_madc_bat->channel_vbat = iio_channel_get(&pdev->dev, "vbat");
	अगर (IS_ERR(twl4030_madc_bat->channel_vbat)) अणु
		ret = PTR_ERR(twl4030_madc_bat->channel_vbat);
		जाओ err_ichg;
	पूर्ण

	/* sort अक्षरging and disअक्षरging calibration data */
	sort(pdata->अक्षरging, pdata->अक्षरging_size,
		माप(काष्ठा twl4030_madc_bat_calibration),
		twl4030_cmp, शून्य);
	sort(pdata->disअक्षरging, pdata->disअक्षरging_size,
		माप(काष्ठा twl4030_madc_bat_calibration),
		twl4030_cmp, शून्य);

	twl4030_madc_bat->pdata = pdata;
	platक्रमm_set_drvdata(pdev, twl4030_madc_bat);
	psy_cfg.drv_data = twl4030_madc_bat;
	twl4030_madc_bat->psy = घातer_supply_रेजिस्टर(&pdev->dev,
						      &twl4030_madc_bat_desc,
						      &psy_cfg);
	अगर (IS_ERR(twl4030_madc_bat->psy)) अणु
		ret = PTR_ERR(twl4030_madc_bat->psy);
		जाओ err_vbat;
	पूर्ण

	वापस 0;

err_vbat:
	iio_channel_release(twl4030_madc_bat->channel_vbat);
err_ichg:
	iio_channel_release(twl4030_madc_bat->channel_ichg);
err_temp:
	iio_channel_release(twl4030_madc_bat->channel_temp);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_madc_battery_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_madc_battery *bat = platक्रमm_get_drvdata(pdev);

	घातer_supply_unरेजिस्टर(bat->psy);

	iio_channel_release(bat->channel_vbat);
	iio_channel_release(bat->channel_ichg);
	iio_channel_release(bat->channel_temp);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver twl4030_madc_battery_driver = अणु
	.driver = अणु
		.name = "twl4030_madc_battery",
	पूर्ण,
	.probe  = twl4030_madc_battery_probe,
	.हटाओ = twl4030_madc_battery_हटाओ,
पूर्ण;
module_platक्रमm_driver(twl4030_madc_battery_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lukas Mथअrdian <lukas@goldelico.com>");
MODULE_DESCRIPTION("twl4030_madc battery driver");
MODULE_ALIAS("platform:twl4030_madc_battery");
