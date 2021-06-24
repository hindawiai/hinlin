<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Nokia RX-51 battery driver
 *
 * Copyright (C) 2012  Pali Rohथँr <pali@kernel.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/param.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/of.h>

काष्ठा rx51_device_info अणु
	काष्ठा device *dev;
	काष्ठा घातer_supply *bat;
	काष्ठा घातer_supply_desc bat_desc;
	काष्ठा iio_channel *channel_temp;
	काष्ठा iio_channel *channel_bsi;
	काष्ठा iio_channel *channel_vbat;
पूर्ण;

/*
 * Read ADCIN channel value, code copied from maemo kernel
 */
अटल पूर्णांक rx51_battery_पढ़ो_adc(काष्ठा iio_channel *channel)
अणु
	पूर्णांक val, err;
	err = iio_पढ़ो_channel_average_raw(channel, &val);
	अगर (err < 0)
		वापस err;
	वापस val;
पूर्ण

/*
 * Read ADCIN channel 12 (voltage) and convert RAW value to micro voltage
 * This conversion क्रमmula was extracted from maemo program bsi-पढ़ो
 */
अटल पूर्णांक rx51_battery_पढ़ो_voltage(काष्ठा rx51_device_info *di)
अणु
	पूर्णांक voltage = rx51_battery_पढ़ो_adc(di->channel_vbat);

	अगर (voltage < 0) अणु
		dev_err(di->dev, "Could not read ADC: %d\n", voltage);
		वापस voltage;
	पूर्ण

	वापस 1000 * (10000 * voltage / 1705);
पूर्ण

/*
 * Temperature look-up tables
 * TEMP = (1/(t1 + 1/298) - 273.15)
 * Where t1 = (1/B) * ln((RAW_ADC_U * 2.5)/(R * I * 255))
 * Formula is based on experimental data, RX-51 CAL data, maemo program bme
 * and क्रमmula from da9052 driver with values R = 100, B = 3380, I = 0.00671
 */

/*
 * Table1 (temperature क्रम first 25 RAW values)
 * Usage: TEMP = rx51_temp_table1[RAW]
 *   RAW is between 1 and 24
 *   TEMP is between 201 C and 55 C
 */
अटल u8 rx51_temp_table1[] = अणु
	255, 201, 159, 138, 124, 114, 106,  99,  94,  89,  85,  82,  78,  75,
	 73,  70,  68,  66,  64,  62,  61,  59,  57,  56,  55
पूर्ण;

/*
 * Table2 (lowest RAW value क्रम temperature)
 * Usage: RAW = rx51_temp_table2[TEMP-rx51_temp_table2_first]
 *   TEMP is between 53 C and -32 C
 *   RAW is between 25 and 993
 */
#घोषणा rx51_temp_table2_first 53
अटल u16 rx51_temp_table2[] = अणु
	 25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  39,
	 40,  41,  43,  44,  46,  48,  49,  51,  53,  55,  57,  59,  61,  64,
	 66,  69,  71,  74,  77,  80,  83,  86,  90,  94,  97, 101, 106, 110,
	115, 119, 125, 130, 136, 141, 148, 154, 161, 168, 176, 184, 202, 211,
	221, 231, 242, 254, 266, 279, 293, 308, 323, 340, 357, 375, 395, 415,
	437, 460, 485, 511, 539, 568, 600, 633, 669, 706, 747, 790, 836, 885,
	937, 993, 1024
पूर्ण;

/*
 * Read ADCIN channel 0 (battery temp) and convert value to tenths of Celsius
 * Use Temperature look-up tables क्रम conversation
 */
अटल पूर्णांक rx51_battery_पढ़ो_temperature(काष्ठा rx51_device_info *di)
अणु
	पूर्णांक min = 0;
	पूर्णांक max = ARRAY_SIZE(rx51_temp_table2) - 1;
	पूर्णांक raw = rx51_battery_पढ़ो_adc(di->channel_temp);

	अगर (raw < 0)
		dev_err(di->dev, "Could not read ADC: %d\n", raw);

	/* Zero and negative values are undefined */
	अगर (raw <= 0)
		वापस पूर्णांक_उच्च;

	/* ADC channels are 10 bit, higher value are undefined */
	अगर (raw >= (1 << 10))
		वापस पूर्णांक_न्यून;

	/* First check क्रम temperature in first direct table */
	अगर (raw < ARRAY_SIZE(rx51_temp_table1))
		वापस rx51_temp_table1[raw] * 10;

	/* Binary search RAW value in second inverse table */
	जबतक (max - min > 1) अणु
		पूर्णांक mid = (max + min) / 2;
		अगर (rx51_temp_table2[mid] <= raw)
			min = mid;
		अन्यथा अगर (rx51_temp_table2[mid] > raw)
			max = mid;
		अगर (rx51_temp_table2[mid] == raw)
			अवरोध;
	पूर्ण

	वापस (rx51_temp_table2_first - min) * 10;
पूर्ण

/*
 * Read ADCIN channel 4 (BSI) and convert RAW value to micro Ah
 * This conversion क्रमmula was extracted from maemo program bsi-पढ़ो
 */
अटल पूर्णांक rx51_battery_पढ़ो_capacity(काष्ठा rx51_device_info *di)
अणु
	पूर्णांक capacity = rx51_battery_पढ़ो_adc(di->channel_bsi);

	अगर (capacity < 0) अणु
		dev_err(di->dev, "Could not read ADC: %d\n", capacity);
		वापस capacity;
	पूर्ण

	वापस 1280 * (1200 * capacity)/(1024 - capacity);
पूर्ण

/*
 * Return घातer_supply property
 */
अटल पूर्णांक rx51_battery_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा rx51_device_info *di = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->पूर्णांकval = 4200000;
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = rx51_battery_पढ़ो_voltage(di) ? 1 : 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = rx51_battery_पढ़ो_voltage(di);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP:
		val->पूर्णांकval = rx51_battery_पढ़ो_temperature(di);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval = rx51_battery_पढ़ो_capacity(di);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (val->पूर्णांकval == पूर्णांक_उच्च || val->पूर्णांकval == पूर्णांक_न्यून)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property rx51_battery_props[] = अणु
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
पूर्ण;

अटल पूर्णांक rx51_battery_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा rx51_device_info *di;
	पूर्णांक ret;

	di = devm_kzalloc(&pdev->dev, माप(*di), GFP_KERNEL);
	अगर (!di)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, di);

	di->dev = &pdev->dev;
	di->bat_desc.name = "rx51-battery";
	di->bat_desc.type = POWER_SUPPLY_TYPE_BATTERY;
	di->bat_desc.properties = rx51_battery_props;
	di->bat_desc.num_properties = ARRAY_SIZE(rx51_battery_props);
	di->bat_desc.get_property = rx51_battery_get_property;

	psy_cfg.drv_data = di;

	di->channel_temp = iio_channel_get(di->dev, "temp");
	अगर (IS_ERR(di->channel_temp)) अणु
		ret = PTR_ERR(di->channel_temp);
		जाओ error;
	पूर्ण

	di->channel_bsi  = iio_channel_get(di->dev, "bsi");
	अगर (IS_ERR(di->channel_bsi)) अणु
		ret = PTR_ERR(di->channel_bsi);
		जाओ error_channel_temp;
	पूर्ण

	di->channel_vbat = iio_channel_get(di->dev, "vbat");
	अगर (IS_ERR(di->channel_vbat)) अणु
		ret = PTR_ERR(di->channel_vbat);
		जाओ error_channel_bsi;
	पूर्ण

	di->bat = घातer_supply_रेजिस्टर(di->dev, &di->bat_desc, &psy_cfg);
	अगर (IS_ERR(di->bat)) अणु
		ret = PTR_ERR(di->bat);
		जाओ error_channel_vbat;
	पूर्ण

	वापस 0;

error_channel_vbat:
	iio_channel_release(di->channel_vbat);
error_channel_bsi:
	iio_channel_release(di->channel_bsi);
error_channel_temp:
	iio_channel_release(di->channel_temp);
error:

	वापस ret;
पूर्ण

अटल पूर्णांक rx51_battery_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rx51_device_info *di = platक्रमm_get_drvdata(pdev);

	घातer_supply_unरेजिस्टर(di->bat);

	iio_channel_release(di->channel_vbat);
	iio_channel_release(di->channel_bsi);
	iio_channel_release(di->channel_temp);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id n900_battery_of_match[] = अणु
	अणु.compatible = "nokia,n900-battery", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, n900_battery_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver rx51_battery_driver = अणु
	.probe = rx51_battery_probe,
	.हटाओ = rx51_battery_हटाओ,
	.driver = अणु
		.name = "rx51-battery",
		.of_match_table = of_match_ptr(n900_battery_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rx51_battery_driver);

MODULE_ALIAS("platform:rx51-battery");
MODULE_AUTHOR("Pali Rohथँr <pali@kernel.org>");
MODULE_DESCRIPTION("Nokia RX-51 battery driver");
MODULE_LICENSE("GPL");
