<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * axp288_adc.c - X-Powers AXP288 PMIC ADC Driver
 *
 * Copyright (C) 2014 Intel Corporation
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/driver.h>

/*
 * This mask enables all ADCs except क्रम the battery temp-sensor (TS), that is
 * left as-is to aव्योम अवरोधing अक्षरging on devices without a temp-sensor.
 */
#घोषणा AXP288_ADC_EN_MASK				0xF0
#घोषणा AXP288_ADC_TS_ENABLE				0x01

#घोषणा AXP288_ADC_TS_BIAS_MASK				GENMASK(5, 4)
#घोषणा AXP288_ADC_TS_BIAS_20UA				(0 << 4)
#घोषणा AXP288_ADC_TS_BIAS_40UA				(1 << 4)
#घोषणा AXP288_ADC_TS_BIAS_60UA				(2 << 4)
#घोषणा AXP288_ADC_TS_BIAS_80UA				(3 << 4)
#घोषणा AXP288_ADC_TS_CURRENT_ON_OFF_MASK		GENMASK(1, 0)
#घोषणा AXP288_ADC_TS_CURRENT_OFF			(0 << 0)
#घोषणा AXP288_ADC_TS_CURRENT_ON_WHEN_CHARGING		(1 << 0)
#घोषणा AXP288_ADC_TS_CURRENT_ON_ONDEMAND		(2 << 0)
#घोषणा AXP288_ADC_TS_CURRENT_ON			(3 << 0)

क्रमागत axp288_adc_id अणु
	AXP288_ADC_TS,
	AXP288_ADC_PMIC,
	AXP288_ADC_GP,
	AXP288_ADC_BATT_CHRG_I,
	AXP288_ADC_BATT_DISCHRG_I,
	AXP288_ADC_BATT_V,
	AXP288_ADC_NR_CHAN,
पूर्ण;

काष्ठा axp288_adc_info अणु
	पूर्णांक irq;
	काष्ठा regmap *regmap;
	bool ts_enabled;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec axp288_adc_channels[] = अणु
	अणु
		.indexed = 1,
		.type = IIO_TEMP,
		.channel = 0,
		.address = AXP288_TS_ADC_H,
		.datasheet_name = "TS_PIN",
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण, अणु
		.indexed = 1,
		.type = IIO_TEMP,
		.channel = 1,
		.address = AXP288_PMIC_ADC_H,
		.datasheet_name = "PMIC_TEMP",
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण, अणु
		.indexed = 1,
		.type = IIO_TEMP,
		.channel = 2,
		.address = AXP288_GP_ADC_H,
		.datasheet_name = "GPADC",
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण, अणु
		.indexed = 1,
		.type = IIO_CURRENT,
		.channel = 3,
		.address = AXP20X_BATT_CHRG_I_H,
		.datasheet_name = "BATT_CHG_I",
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण, अणु
		.indexed = 1,
		.type = IIO_CURRENT,
		.channel = 4,
		.address = AXP20X_BATT_DISCHRG_I_H,
		.datasheet_name = "BATT_DISCHRG_I",
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण, अणु
		.indexed = 1,
		.type = IIO_VOLTAGE,
		.channel = 5,
		.address = AXP20X_BATT_V_H,
		.datasheet_name = "BATT_V",
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
	पूर्ण,
पूर्ण;

/* क्रम consumer drivers */
अटल काष्ठा iio_map axp288_adc_शेष_maps[] = अणु
	IIO_MAP("TS_PIN", "axp288-batt", "axp288-batt-temp"),
	IIO_MAP("PMIC_TEMP", "axp288-pmic", "axp288-pmic-temp"),
	IIO_MAP("GPADC", "axp288-gpadc", "axp288-system-temp"),
	IIO_MAP("BATT_CHG_I", "axp288-chrg", "axp288-chrg-curr"),
	IIO_MAP("BATT_DISCHRG_I", "axp288-chrg", "axp288-chrg-d-curr"),
	IIO_MAP("BATT_V", "axp288-batt", "axp288-batt-volt"),
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक axp288_adc_पढ़ो_channel(पूर्णांक *val, अचिन्हित दीर्घ address,
				काष्ठा regmap *regmap)
अणु
	u8 buf[2];

	अगर (regmap_bulk_पढ़ो(regmap, address, buf, 2))
		वापस -EIO;
	*val = (buf[0] << 4) + ((buf[1] >> 4) & 0x0F);

	वापस IIO_VAL_INT;
पूर्ण

/*
 * The current-source used क्रम the battery temp-sensor (TS) is shared
 * with the GPADC. For proper fuel-gauge and अक्षरger operation the TS
 * current-source needs to be permanently on. But to पढ़ो the GPADC we
 * need to temporary चयन the TS current-source to ondemand, so that
 * the GPADC can use it, otherwise we will always पढ़ो an all 0 value.
 */
अटल पूर्णांक axp288_adc_set_ts(काष्ठा axp288_adc_info *info,
			     अचिन्हित पूर्णांक mode, अचिन्हित दीर्घ address)
अणु
	पूर्णांक ret;

	/* No need to चयन the current-source अगर the TS pin is disabled */
	अगर (!info->ts_enabled)
		वापस 0;

	/* Channels other than GPADC करो not need the current source */
	अगर (address != AXP288_GP_ADC_H)
		वापस 0;

	ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
				 AXP288_ADC_TS_CURRENT_ON_OFF_MASK, mode);
	अगर (ret)
		वापस ret;

	/* When चयनing to the GPADC pin give things some समय to settle */
	अगर (mode == AXP288_ADC_TS_CURRENT_ON_ONDEMAND)
		usleep_range(6000, 10000);

	वापस 0;
पूर्ण

अटल पूर्णांक axp288_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा axp288_adc_info *info = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (axp288_adc_set_ts(info, AXP288_ADC_TS_CURRENT_ON_ONDEMAND,
					chan->address)) अणु
			dev_err(&indio_dev->dev, "GPADC mode\n");
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = axp288_adc_पढ़ो_channel(val, chan->address, info->regmap);
		अगर (axp288_adc_set_ts(info, AXP288_ADC_TS_CURRENT_ON,
						chan->address))
			dev_err(&indio_dev->dev, "TS pin restore\n");
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&indio_dev->mlock);

	वापस ret;
पूर्ण

/*
 * We rely on the machine's firmware to correctly setup the TS pin bias current
 * at boot. This lists प्रणालीs with broken fw where we need to set it ourselves.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id axp288_adc_ts_bias_override[] = अणु
	अणु
		/* Lenovo Ideapad 100S (11 inch) */
		.matches = अणु
		  DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		  DMI_MATCH(DMI_PRODUCT_VERSION, "Lenovo ideapad 100S-11IBY"),
		पूर्ण,
		.driver_data = (व्योम *)(uपूर्णांकptr_t)AXP288_ADC_TS_BIAS_80UA,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक axp288_adc_initialize(काष्ठा axp288_adc_info *info)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *bias_override;
	पूर्णांक ret, adc_enable_val;

	bias_override = dmi_first_match(axp288_adc_ts_bias_override);
	अगर (bias_override) अणु
		ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
					 AXP288_ADC_TS_BIAS_MASK,
					 (uपूर्णांकptr_t)bias_override->driver_data);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * Determine अगर the TS pin is enabled and set the TS current-source
	 * accordingly.
	 */
	ret = regmap_पढ़ो(info->regmap, AXP20X_ADC_EN1, &adc_enable_val);
	अगर (ret)
		वापस ret;

	अगर (adc_enable_val & AXP288_ADC_TS_ENABLE) अणु
		info->ts_enabled = true;
		ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
					 AXP288_ADC_TS_CURRENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CURRENT_ON);
	पूर्ण अन्यथा अणु
		info->ts_enabled = false;
		ret = regmap_update_bits(info->regmap, AXP288_ADC_TS_PIN_CTRL,
					 AXP288_ADC_TS_CURRENT_ON_OFF_MASK,
					 AXP288_ADC_TS_CURRENT_OFF);
	पूर्ण
	अगर (ret)
		वापस ret;

	/* Turn on the ADC क्रम all channels except TS, leave TS as is */
	वापस regmap_update_bits(info->regmap, AXP20X_ADC_EN1,
				  AXP288_ADC_EN_MASK, AXP288_ADC_EN_MASK);
पूर्ण

अटल स्थिर काष्ठा iio_info axp288_adc_iio_info = अणु
	.पढ़ो_raw = &axp288_adc_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक axp288_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा axp288_adc_info *info;
	काष्ठा iio_dev *indio_dev;
	काष्ठा axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*info));
	अगर (!indio_dev)
		वापस -ENOMEM;

	info = iio_priv(indio_dev);
	info->irq = platक्रमm_get_irq(pdev, 0);
	अगर (info->irq < 0)
		वापस info->irq;
	platक्रमm_set_drvdata(pdev, indio_dev);
	info->regmap = axp20x->regmap;
	/*
	 * Set ADC to enabled state at all समय, including प्रणाली suspend.
	 * otherwise पूर्णांकernal fuel gauge functionality may be affected.
	 */
	ret = axp288_adc_initialize(info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable ADC device\n");
		वापस ret;
	पूर्ण

	indio_dev->name = pdev->name;
	indio_dev->channels = axp288_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(axp288_adc_channels);
	indio_dev->info = &axp288_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	ret = iio_map_array_रेजिस्टर(indio_dev, axp288_adc_शेष_maps);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "unable to register iio device\n");
		जाओ err_array_unरेजिस्टर;
	पूर्ण
	वापस 0;

err_array_unरेजिस्टर:
	iio_map_array_unरेजिस्टर(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक axp288_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_map_array_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id axp288_adc_id_table[] = अणु
	अणु .name = "axp288_adc" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver axp288_adc_driver = अणु
	.probe = axp288_adc_probe,
	.हटाओ = axp288_adc_हटाओ,
	.id_table = axp288_adc_id_table,
	.driver = अणु
		.name = "axp288_adc",
	पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, axp288_adc_id_table);

module_platक्रमm_driver(axp288_adc_driver);

MODULE_AUTHOR("Jacob Pan <jacob.jun.pan@linux.intel.com>");
MODULE_DESCRIPTION("X-Powers AXP288 ADC Driver");
MODULE_LICENSE("GPL");
