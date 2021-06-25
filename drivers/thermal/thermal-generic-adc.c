<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic ADC thermal driver
 *
 * Copyright (C) 2016 NVIDIA CORPORATION. All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */
#समावेश <linux/iio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

काष्ठा gadc_thermal_info अणु
	काष्ठा device *dev;
	काष्ठा thermal_zone_device *tz_dev;
	काष्ठा iio_channel *channel;
	s32 *lookup_table;
	पूर्णांक nlookup_table;
पूर्ण;

अटल पूर्णांक gadc_thermal_adc_to_temp(काष्ठा gadc_thermal_info *gti, पूर्णांक val)
अणु
	पूर्णांक temp, temp_hi, temp_lo, adc_hi, adc_lo;
	पूर्णांक i;

	अगर (!gti->lookup_table)
		वापस val;

	क्रम (i = 0; i < gti->nlookup_table; i++) अणु
		अगर (val >= gti->lookup_table[2 * i + 1])
			अवरोध;
	पूर्ण

	अगर (i == 0) अणु
		temp = gti->lookup_table[0];
	पूर्ण अन्यथा अगर (i >= gti->nlookup_table) अणु
		temp = gti->lookup_table[2 * (gti->nlookup_table - 1)];
	पूर्ण अन्यथा अणु
		adc_hi = gti->lookup_table[2 * i - 1];
		adc_lo = gti->lookup_table[2 * i + 1];

		temp_hi = gti->lookup_table[2 * i - 2];
		temp_lo = gti->lookup_table[2 * i];

		temp = temp_hi + mult_frac(temp_lo - temp_hi, val - adc_hi,
					   adc_lo - adc_hi);
	पूर्ण

	वापस temp;
पूर्ण

अटल पूर्णांक gadc_thermal_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा gadc_thermal_info *gti = data;
	पूर्णांक val;
	पूर्णांक ret;

	ret = iio_पढ़ो_channel_processed(gti->channel, &val);
	अगर (ret < 0) अणु
		dev_err(gti->dev, "IIO channel read failed %d\n", ret);
		वापस ret;
	पूर्ण
	*temp = gadc_thermal_adc_to_temp(gti, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops gadc_thermal_ops = अणु
	.get_temp = gadc_thermal_get_temp,
पूर्ण;

अटल पूर्णांक gadc_thermal_पढ़ो_linear_lookup_table(काष्ठा device *dev,
						 काष्ठा gadc_thermal_info *gti)
अणु
	काष्ठा device_node *np = dev->of_node;
	क्रमागत iio_chan_type chan_type;
	पूर्णांक ntable;
	पूर्णांक ret;

	ntable = of_property_count_elems_of_size(np, "temperature-lookup-table",
						 माप(u32));
	अगर (ntable <= 0) अणु
		ret = iio_get_channel_type(gti->channel, &chan_type);
		अगर (ret || chan_type != IIO_TEMP)
			dev_notice(dev,
				   "no lookup table, assuming DAC channel returns milliCelcius\n");
		वापस 0;
	पूर्ण

	अगर (ntable % 2) अणु
		dev_err(dev, "Pair of temperature vs ADC read value missing\n");
		वापस -EINVAL;
	पूर्ण

	gti->lookup_table = devm_kसुस्मृति(dev,
					 ntable, माप(*gti->lookup_table),
					 GFP_KERNEL);
	अगर (!gti->lookup_table)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32_array(np, "temperature-lookup-table",
					 (u32 *)gti->lookup_table, ntable);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read temperature lookup table: %d\n",
			ret);
		वापस ret;
	पूर्ण

	gti->nlookup_table = ntable / 2;

	वापस 0;
पूर्ण

अटल पूर्णांक gadc_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gadc_thermal_info *gti;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "Only DT based supported\n");
		वापस -ENODEV;
	पूर्ण

	gti = devm_kzalloc(&pdev->dev, माप(*gti), GFP_KERNEL);
	अगर (!gti)
		वापस -ENOMEM;

	gti->channel = devm_iio_channel_get(&pdev->dev, "sensor-channel");
	अगर (IS_ERR(gti->channel)) अणु
		ret = PTR_ERR(gti->channel);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "IIO channel not found: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = gadc_thermal_पढ़ो_linear_lookup_table(&pdev->dev, gti);
	अगर (ret < 0)
		वापस ret;

	gti->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, gti);

	gti->tz_dev = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, 0, gti,
							   &gadc_thermal_ops);
	अगर (IS_ERR(gti->tz_dev)) अणु
		ret = PTR_ERR(gti->tz_dev);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"Thermal zone sensor register failed: %d\n",
				ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_adc_thermal_match[] = अणु
	अणु .compatible = "generic-adc-thermal", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_adc_thermal_match);

अटल काष्ठा platक्रमm_driver gadc_thermal_driver = अणु
	.driver = अणु
		.name = "generic-adc-thermal",
		.of_match_table = of_adc_thermal_match,
	पूर्ण,
	.probe = gadc_thermal_probe,
पूर्ण;

module_platक्रमm_driver(gadc_thermal_driver);

MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_DESCRIPTION("Generic ADC thermal driver using IIO framework with DT");
MODULE_LICENSE("GPL v2");
