<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2011-2015, 2017, 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

#समावेश "../thermal_core.h"

#घोषणा QPNP_TM_REG_DIG_MAJOR		0x01
#घोषणा QPNP_TM_REG_TYPE		0x04
#घोषणा QPNP_TM_REG_SUBTYPE		0x05
#घोषणा QPNP_TM_REG_STATUS		0x08
#घोषणा QPNP_TM_REG_SHUTDOWN_CTRL1	0x40
#घोषणा QPNP_TM_REG_ALARM_CTRL		0x46

#घोषणा QPNP_TM_TYPE			0x09
#घोषणा QPNP_TM_SUBTYPE_GEN1		0x08
#घोषणा QPNP_TM_SUBTYPE_GEN2		0x09

#घोषणा STATUS_GEN1_STAGE_MASK		GENMASK(1, 0)
#घोषणा STATUS_GEN2_STATE_MASK		GENMASK(6, 4)
#घोषणा STATUS_GEN2_STATE_SHIFT		4

#घोषणा SHUTDOWN_CTRL1_OVERRIDE_S2	BIT(6)
#घोषणा SHUTDOWN_CTRL1_THRESHOLD_MASK	GENMASK(1, 0)

#घोषणा SHUTDOWN_CTRL1_RATE_25HZ	BIT(3)

#घोषणा ALARM_CTRL_FORCE_ENABLE		BIT(7)

#घोषणा THRESH_COUNT			4
#घोषणा STAGE_COUNT			3

/* Over-temperature trip poपूर्णांक values in mC */
अटल स्थिर दीर्घ temp_map_gen1[THRESH_COUNT][STAGE_COUNT] = अणु
	अणु 105000, 125000, 145000 पूर्ण,
	अणु 110000, 130000, 150000 पूर्ण,
	अणु 115000, 135000, 155000 पूर्ण,
	अणु 120000, 140000, 160000 पूर्ण,
पूर्ण;

अटल स्थिर दीर्घ temp_map_gen2_v1[THRESH_COUNT][STAGE_COUNT] = अणु
	अणु  90000, 110000, 140000 पूर्ण,
	अणु  95000, 115000, 145000 पूर्ण,
	अणु 100000, 120000, 150000 पूर्ण,
	अणु 105000, 125000, 155000 पूर्ण,
पूर्ण;

#घोषणा TEMP_THRESH_STEP		5000 /* Threshold step: 5 C */

#घोषणा THRESH_MIN			0
#घोषणा THRESH_MAX			3

#घोषणा TEMP_STAGE_HYSTERESIS		2000

/* Temperature in Milli Celsius reported during stage 0 अगर no ADC is present */
#घोषणा DEFAULT_TEMP			37000

काष्ठा qpnp_पंचांग_chip अणु
	काष्ठा regmap			*map;
	काष्ठा device			*dev;
	काष्ठा thermal_zone_device	*tz_dev;
	अचिन्हित पूर्णांक			subtype;
	दीर्घ				temp;
	अचिन्हित पूर्णांक			thresh;
	अचिन्हित पूर्णांक			stage;
	अचिन्हित पूर्णांक			prev_stage;
	अचिन्हित पूर्णांक			base;
	/* protects .thresh, .stage and chip रेजिस्टरs */
	काष्ठा mutex			lock;
	bool				initialized;

	काष्ठा iio_channel		*adc;
	स्थिर दीर्घ			(*temp_map)[THRESH_COUNT][STAGE_COUNT];
पूर्ण;

/* This array maps from GEN2 alarm state to GEN1 alarm stage */
अटल स्थिर अचिन्हित पूर्णांक alarm_state_map[8] = अणु0, 1, 1, 2, 2, 3, 3, 3पूर्ण;

अटल पूर्णांक qpnp_पंचांग_पढ़ो(काष्ठा qpnp_पंचांग_chip *chip, u16 addr, u8 *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->map, chip->base + addr, &val);
	अगर (ret < 0)
		वापस ret;

	*data = val;
	वापस 0;
पूर्ण

अटल पूर्णांक qpnp_पंचांग_ग_लिखो(काष्ठा qpnp_पंचांग_chip *chip, u16 addr, u8 data)
अणु
	वापस regmap_ग_लिखो(chip->map, chip->base + addr, data);
पूर्ण

/**
 * qpnp_पंचांग_decode_temp() - वापस temperature in mC corresponding to the
 *		specअगरied over-temperature stage
 * @chip:		Poपूर्णांकer to the qpnp_पंचांग chip
 * @stage:		Over-temperature stage
 *
 * Return: temperature in mC
 */
अटल दीर्घ qpnp_पंचांग_decode_temp(काष्ठा qpnp_पंचांग_chip *chip, अचिन्हित पूर्णांक stage)
अणु
	अगर (!chip->temp_map || chip->thresh >= THRESH_COUNT || stage == 0 ||
	    stage > STAGE_COUNT)
		वापस 0;

	वापस (*chip->temp_map)[chip->thresh][stage - 1];
पूर्ण

/**
 * qpnp_पंचांग_get_temp_stage() - वापस over-temperature stage
 * @chip:		Poपूर्णांकer to the qpnp_पंचांग chip
 *
 * Return: stage (GEN1) or state (GEN2) on success, or त्रुटि_सं on failure.
 */
अटल पूर्णांक qpnp_पंचांग_get_temp_stage(काष्ठा qpnp_पंचांग_chip *chip)
अणु
	पूर्णांक ret;
	u8 reg = 0;

	ret = qpnp_पंचांग_पढ़ो(chip, QPNP_TM_REG_STATUS, &reg);
	अगर (ret < 0)
		वापस ret;

	अगर (chip->subtype == QPNP_TM_SUBTYPE_GEN1)
		ret = reg & STATUS_GEN1_STAGE_MASK;
	अन्यथा
		ret = (reg & STATUS_GEN2_STATE_MASK) >> STATUS_GEN2_STATE_SHIFT;

	वापस ret;
पूर्ण

/*
 * This function updates the पूर्णांकernal temp value based on the
 * current thermal stage and threshold as well as the previous stage
 */
अटल पूर्णांक qpnp_पंचांग_update_temp_no_adc(काष्ठा qpnp_पंचांग_chip *chip)
अणु
	अचिन्हित पूर्णांक stage, stage_new, stage_old;
	पूर्णांक ret;

	WARN_ON(!mutex_is_locked(&chip->lock));

	ret = qpnp_पंचांग_get_temp_stage(chip);
	अगर (ret < 0)
		वापस ret;
	stage = ret;

	अगर (chip->subtype == QPNP_TM_SUBTYPE_GEN1) अणु
		stage_new = stage;
		stage_old = chip->stage;
	पूर्ण अन्यथा अणु
		stage_new = alarm_state_map[stage];
		stage_old = alarm_state_map[chip->stage];
	पूर्ण

	अगर (stage_new > stage_old) अणु
		/* increasing stage, use lower bound */
		chip->temp = qpnp_पंचांग_decode_temp(chip, stage_new)
				+ TEMP_STAGE_HYSTERESIS;
	पूर्ण अन्यथा अगर (stage_new < stage_old) अणु
		/* decreasing stage, use upper bound */
		chip->temp = qpnp_पंचांग_decode_temp(chip, stage_new + 1)
				- TEMP_STAGE_HYSTERESIS;
	पूर्ण

	chip->stage = stage;

	वापस 0;
पूर्ण

अटल पूर्णांक qpnp_पंचांग_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा qpnp_पंचांग_chip *chip = data;
	पूर्णांक ret, mili_celsius;

	अगर (!temp)
		वापस -EINVAL;

	अगर (!chip->initialized) अणु
		*temp = DEFAULT_TEMP;
		वापस 0;
	पूर्ण

	अगर (!chip->adc) अणु
		mutex_lock(&chip->lock);
		ret = qpnp_पंचांग_update_temp_no_adc(chip);
		mutex_unlock(&chip->lock);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = iio_पढ़ो_channel_processed(chip->adc, &mili_celsius);
		अगर (ret < 0)
			वापस ret;

		chip->temp = mili_celsius;
	पूर्ण

	*temp = chip->temp;

	वापस 0;
पूर्ण

अटल पूर्णांक qpnp_पंचांग_update_critical_trip_temp(काष्ठा qpnp_पंचांग_chip *chip,
					     पूर्णांक temp)
अणु
	दीर्घ stage2_threshold_min = (*chip->temp_map)[THRESH_MIN][1];
	दीर्घ stage2_threshold_max = (*chip->temp_map)[THRESH_MAX][1];
	bool disable_s2_shutकरोwn = false;
	u8 reg;

	WARN_ON(!mutex_is_locked(&chip->lock));

	/*
	 * Default: S2 and S3 shutकरोwn enabled, thresholds at
	 * lowest threshold set, monitoring at 25Hz
	 */
	reg = SHUTDOWN_CTRL1_RATE_25HZ;

	अगर (temp == THERMAL_TEMP_INVALID ||
	    temp < stage2_threshold_min) अणु
		chip->thresh = THRESH_MIN;
		जाओ skip;
	पूर्ण

	अगर (temp <= stage2_threshold_max) अणु
		chip->thresh = THRESH_MAX -
			((stage2_threshold_max - temp) /
			 TEMP_THRESH_STEP);
		disable_s2_shutकरोwn = true;
	पूर्ण अन्यथा अणु
		chip->thresh = THRESH_MAX;

		अगर (chip->adc)
			disable_s2_shutकरोwn = true;
		अन्यथा
			dev_warn(chip->dev,
				 "No ADC is configured and critical temperature is above the maximum stage 2 threshold of 140 C! Configuring stage 2 shutdown at 140 C.\n");
	पूर्ण

skip:
	reg |= chip->thresh;
	अगर (disable_s2_shutकरोwn)
		reg |= SHUTDOWN_CTRL1_OVERRIDE_S2;

	वापस qpnp_पंचांग_ग_लिखो(chip, QPNP_TM_REG_SHUTDOWN_CTRL1, reg);
पूर्ण

अटल पूर्णांक qpnp_पंचांग_set_trip_temp(व्योम *data, पूर्णांक trip, पूर्णांक temp)
अणु
	काष्ठा qpnp_पंचांग_chip *chip = data;
	स्थिर काष्ठा thermal_trip *trip_poपूर्णांकs;
	पूर्णांक ret;

	trip_poपूर्णांकs = of_thermal_get_trip_poपूर्णांकs(chip->tz_dev);
	अगर (!trip_poपूर्णांकs)
		वापस -EINVAL;

	अगर (trip_poपूर्णांकs[trip].type != THERMAL_TRIP_CRITICAL)
		वापस 0;

	mutex_lock(&chip->lock);
	ret = qpnp_पंचांग_update_critical_trip_temp(chip, temp);
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops qpnp_पंचांग_sensor_ops = अणु
	.get_temp = qpnp_पंचांग_get_temp,
	.set_trip_temp = qpnp_पंचांग_set_trip_temp,
पूर्ण;

अटल irqवापस_t qpnp_पंचांग_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qpnp_पंचांग_chip *chip = data;

	thermal_zone_device_update(chip->tz_dev, THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qpnp_पंचांग_get_critical_trip_temp(काष्ठा qpnp_पंचांग_chip *chip)
अणु
	पूर्णांक ntrips;
	स्थिर काष्ठा thermal_trip *trips;
	पूर्णांक i;

	ntrips = of_thermal_get_ntrips(chip->tz_dev);
	अगर (ntrips <= 0)
		वापस THERMAL_TEMP_INVALID;

	trips = of_thermal_get_trip_poपूर्णांकs(chip->tz_dev);
	अगर (!trips)
		वापस THERMAL_TEMP_INVALID;

	क्रम (i = 0; i < ntrips; i++) अणु
		अगर (of_thermal_is_trip_valid(chip->tz_dev, i) &&
		    trips[i].type == THERMAL_TRIP_CRITICAL)
			वापस trips[i].temperature;
	पूर्ण

	वापस THERMAL_TEMP_INVALID;
पूर्ण

/*
 * This function initializes the पूर्णांकernal temp value based on only the
 * current thermal stage and threshold. Setup threshold control and
 * disable shutकरोwn override.
 */
अटल पूर्णांक qpnp_पंचांग_init(काष्ठा qpnp_पंचांग_chip *chip)
अणु
	अचिन्हित पूर्णांक stage;
	पूर्णांक ret;
	u8 reg = 0;
	पूर्णांक crit_temp;

	mutex_lock(&chip->lock);

	ret = qpnp_पंचांग_पढ़ो(chip, QPNP_TM_REG_SHUTDOWN_CTRL1, &reg);
	अगर (ret < 0)
		जाओ out;

	chip->thresh = reg & SHUTDOWN_CTRL1_THRESHOLD_MASK;
	chip->temp = DEFAULT_TEMP;

	ret = qpnp_पंचांग_get_temp_stage(chip);
	अगर (ret < 0)
		जाओ out;
	chip->stage = ret;

	stage = chip->subtype == QPNP_TM_SUBTYPE_GEN1
		? chip->stage : alarm_state_map[chip->stage];

	अगर (stage)
		chip->temp = qpnp_पंचांग_decode_temp(chip, stage);

	crit_temp = qpnp_पंचांग_get_critical_trip_temp(chip);
	ret = qpnp_पंचांग_update_critical_trip_temp(chip, crit_temp);
	अगर (ret < 0)
		जाओ out;

	/* Enable the thermal alarm PMIC module in always-on mode. */
	reg = ALARM_CTRL_FORCE_ENABLE;
	ret = qpnp_पंचांग_ग_लिखो(chip, QPNP_TM_REG_ALARM_CTRL, reg);

	chip->initialized = true;

out:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक qpnp_पंचांग_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा qpnp_पंचांग_chip *chip;
	काष्ठा device_node *node;
	u8 type, subtype, dig_major;
	u32 res;
	पूर्णांक ret, irq;

	node = pdev->dev.of_node;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, chip);
	chip->dev = &pdev->dev;

	mutex_init(&chip->lock);

	chip->map = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!chip->map)
		वापस -ENXIO;

	ret = of_property_पढ़ो_u32(node, "reg", &res);
	अगर (ret < 0)
		वापस ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	/* ADC based measurements are optional */
	chip->adc = devm_iio_channel_get(&pdev->dev, "thermal");
	अगर (IS_ERR(chip->adc)) अणु
		ret = PTR_ERR(chip->adc);
		chip->adc = शून्य;
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
	पूर्ण

	chip->base = res;

	ret = qpnp_पंचांग_पढ़ो(chip, QPNP_TM_REG_TYPE, &type);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not read type\n");
		वापस ret;
	पूर्ण

	ret = qpnp_पंचांग_पढ़ो(chip, QPNP_TM_REG_SUBTYPE, &subtype);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not read subtype\n");
		वापस ret;
	पूर्ण

	ret = qpnp_पंचांग_पढ़ो(chip, QPNP_TM_REG_DIG_MAJOR, &dig_major);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not read dig_major\n");
		वापस ret;
	पूर्ण

	अगर (type != QPNP_TM_TYPE || (subtype != QPNP_TM_SUBTYPE_GEN1
				     && subtype != QPNP_TM_SUBTYPE_GEN2)) अणु
		dev_err(&pdev->dev, "invalid type 0x%02x or subtype 0x%02x\n",
			type, subtype);
		वापस -ENODEV;
	पूर्ण

	chip->subtype = subtype;
	अगर (subtype == QPNP_TM_SUBTYPE_GEN2 && dig_major >= 1)
		chip->temp_map = &temp_map_gen2_v1;
	अन्यथा
		chip->temp_map = &temp_map_gen1;

	/*
	 * Register the sensor beक्रमe initializing the hardware to be able to
	 * पढ़ो the trip poपूर्णांकs. get_temp() वापसs the शेष temperature
	 * beक्रमe the hardware initialization is completed.
	 */
	chip->tz_dev = devm_thermal_zone_of_sensor_रेजिस्टर(
		&pdev->dev, 0, chip, &qpnp_पंचांग_sensor_ops);
	अगर (IS_ERR(chip->tz_dev)) अणु
		dev_err(&pdev->dev, "failed to register sensor\n");
		वापस PTR_ERR(chip->tz_dev);
	पूर्ण

	ret = qpnp_पंचांग_init(chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "init failed\n");
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य, qpnp_पंचांग_isr,
					IRQF_ONESHOT, node->name, chip);
	अगर (ret < 0)
		वापस ret;

	thermal_zone_device_update(chip->tz_dev, THERMAL_EVENT_UNSPECIFIED);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qpnp_पंचांग_match_table[] = अणु
	अणु .compatible = "qcom,spmi-temp-alarm" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qpnp_पंचांग_match_table);

अटल काष्ठा platक्रमm_driver qpnp_पंचांग_driver = अणु
	.driver = अणु
		.name = "spmi-temp-alarm",
		.of_match_table = qpnp_पंचांग_match_table,
	पूर्ण,
	.probe  = qpnp_पंचांग_probe,
पूर्ण;
module_platक्रमm_driver(qpnp_पंचांग_driver);

MODULE_ALIAS("platform:spmi-temp-alarm");
MODULE_DESCRIPTION("QPNP PMIC Temperature Alarm driver");
MODULE_LICENSE("GPL v2");
