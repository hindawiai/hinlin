<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ST Thermal Sensor Driver core routines
 * Author: Ajit Pal Singh <ajitpal.singh@st.com>
 *
 * Copyright (C) 2003-2014 STMicroelectronics (R&D) Limited
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश "st_thermal.h"

/* The Thermal Framework expects millidegrees */
#घोषणा mcelsius(temp)			((temp) * 1000)

/*
 * Function to allocate regfields which are common
 * between syscfg and memory mapped based sensors
 */
अटल पूर्णांक st_thermal_alloc_regfields(काष्ठा st_thermal_sensor *sensor)
अणु
	काष्ठा device *dev = sensor->dev;
	काष्ठा regmap *regmap = sensor->regmap;
	स्थिर काष्ठा reg_field *reg_fields = sensor->cdata->reg_fields;

	sensor->dcorrect = devm_regmap_field_alloc(dev, regmap,
						   reg_fields[DCORRECT]);

	sensor->overflow = devm_regmap_field_alloc(dev, regmap,
						   reg_fields[OVERFLOW]);

	sensor->temp_data = devm_regmap_field_alloc(dev, regmap,
						    reg_fields[DATA]);

	अगर (IS_ERR(sensor->dcorrect) ||
	    IS_ERR(sensor->overflow) ||
	    IS_ERR(sensor->temp_data)) अणु
		dev_err(dev, "failed to allocate common regfields\n");
		वापस -EINVAL;
	पूर्ण

	वापस sensor->ops->alloc_regfields(sensor);
पूर्ण

अटल पूर्णांक st_thermal_sensor_on(काष्ठा st_thermal_sensor *sensor)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = sensor->dev;

	ret = clk_prepare_enable(sensor->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clk\n");
		वापस ret;
	पूर्ण

	ret = sensor->ops->घातer_ctrl(sensor, POWER_ON);
	अगर (ret) अणु
		dev_err(dev, "failed to power on sensor\n");
		clk_disable_unprepare(sensor->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक st_thermal_sensor_off(काष्ठा st_thermal_sensor *sensor)
अणु
	पूर्णांक ret;

	ret = sensor->ops->घातer_ctrl(sensor, POWER_OFF);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(sensor->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक st_thermal_calibration(काष्ठा st_thermal_sensor *sensor)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;
	काष्ठा device *dev = sensor->dev;

	/* Check अगर sensor calibration data is alपढ़ोy written */
	ret = regmap_field_पढ़ो(sensor->dcorrect, &val);
	अगर (ret) अणु
		dev_err(dev, "failed to read calibration data\n");
		वापस ret;
	पूर्ण

	अगर (!val) अणु
		/*
		 * Sensor calibration value not set by bootloader,
		 * शेष calibration data to be used
		 */
		ret = regmap_field_ग_लिखो(sensor->dcorrect,
					 sensor->cdata->calibration_val);
		अगर (ret)
			dev_err(dev, "failed to set calibration data\n");
	पूर्ण

	वापस ret;
पूर्ण

/* Callback to get temperature from HW*/
अटल पूर्णांक st_thermal_get_temp(काष्ठा thermal_zone_device *th, पूर्णांक *temperature)
अणु
	काष्ठा st_thermal_sensor *sensor = th->devdata;
	काष्ठा device *dev = sensor->dev;
	अचिन्हित पूर्णांक temp;
	अचिन्हित पूर्णांक overflow;
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(sensor->overflow, &overflow);
	अगर (ret)
		वापस ret;
	अगर (overflow)
		वापस -EIO;

	ret = regmap_field_पढ़ो(sensor->temp_data, &temp);
	अगर (ret)
		वापस ret;

	temp += sensor->cdata->temp_adjust_val;
	temp = mcelsius(temp);

	dev_dbg(dev, "temperature: %d\n", temp);

	*temperature = temp;

	वापस 0;
पूर्ण

अटल पूर्णांक st_thermal_get_trip_type(काष्ठा thermal_zone_device *th,
				पूर्णांक trip, क्रमागत thermal_trip_type *type)
अणु
	काष्ठा st_thermal_sensor *sensor = th->devdata;
	काष्ठा device *dev = sensor->dev;

	चयन (trip) अणु
	हाल 0:
		*type = THERMAL_TRIP_CRITICAL;
		अवरोध;
	शेष:
		dev_err(dev, "invalid trip point\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक st_thermal_get_trip_temp(काष्ठा thermal_zone_device *th,
				    पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा st_thermal_sensor *sensor = th->devdata;
	काष्ठा device *dev = sensor->dev;

	चयन (trip) अणु
	हाल 0:
		*temp = mcelsius(sensor->cdata->crit_temp);
		अवरोध;
	शेष:
		dev_err(dev, "Invalid trip point\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops st_tz_ops = अणु
	.get_temp	= st_thermal_get_temp,
	.get_trip_type	= st_thermal_get_trip_type,
	.get_trip_temp	= st_thermal_get_trip_temp,
पूर्ण;

पूर्णांक st_thermal_रेजिस्टर(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा of_device_id *st_thermal_of_match)
अणु
	काष्ठा st_thermal_sensor *sensor;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा of_device_id *match;

	पूर्णांक polling_delay;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(dev, "device tree node not found\n");
		वापस -EINVAL;
	पूर्ण

	sensor = devm_kzalloc(dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	sensor->dev = dev;

	match = of_match_device(st_thermal_of_match, dev);
	अगर (!(match && match->data))
		वापस -EINVAL;

	sensor->cdata = match->data;
	अगर (!sensor->cdata->ops)
		वापस -EINVAL;

	sensor->ops = sensor->cdata->ops;

	ret = (sensor->ops->regmap_init)(sensor);
	अगर (ret)
		वापस ret;

	ret = st_thermal_alloc_regfields(sensor);
	अगर (ret)
		वापस ret;

	sensor->clk = devm_clk_get(dev, "thermal");
	अगर (IS_ERR(sensor->clk)) अणु
		dev_err(dev, "failed to fetch clock\n");
		वापस PTR_ERR(sensor->clk);
	पूर्ण

	अगर (sensor->ops->रेजिस्टर_enable_irq) अणु
		ret = sensor->ops->रेजिस्टर_enable_irq(sensor);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = st_thermal_sensor_on(sensor);
	अगर (ret)
		वापस ret;

	ret = st_thermal_calibration(sensor);
	अगर (ret)
		जाओ sensor_off;

	polling_delay = sensor->ops->रेजिस्टर_enable_irq ? 0 : 1000;

	sensor->thermal_dev =
		thermal_zone_device_रेजिस्टर(dev_name(dev), 1, 0, sensor,
					     &st_tz_ops, शून्य, 0, polling_delay);
	अगर (IS_ERR(sensor->thermal_dev)) अणु
		dev_err(dev, "failed to register thermal zone device\n");
		ret = PTR_ERR(sensor->thermal_dev);
		जाओ sensor_off;
	पूर्ण
	ret = thermal_zone_device_enable(sensor->thermal_dev);
	अगर (ret)
		जाओ tzd_unरेजिस्टर;

	platक्रमm_set_drvdata(pdev, sensor);

	वापस 0;

tzd_unरेजिस्टर:
	thermal_zone_device_unरेजिस्टर(sensor->thermal_dev);
sensor_off:
	st_thermal_sensor_off(sensor);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(st_thermal_रेजिस्टर);

पूर्णांक st_thermal_unरेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_thermal_sensor *sensor = platक्रमm_get_drvdata(pdev);

	st_thermal_sensor_off(sensor);
	thermal_zone_device_unरेजिस्टर(sensor->thermal_dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(st_thermal_unरेजिस्टर);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक st_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा st_thermal_sensor *sensor = dev_get_drvdata(dev);

	वापस st_thermal_sensor_off(sensor);
पूर्ण

अटल पूर्णांक st_thermal_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा st_thermal_sensor *sensor = dev_get_drvdata(dev);

	ret = st_thermal_sensor_on(sensor);
	अगर (ret)
		वापस ret;

	ret = st_thermal_calibration(sensor);
	अगर (ret)
		वापस ret;

	अगर (sensor->ops->enable_irq) अणु
		ret = sensor->ops->enable_irq(sensor);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

SIMPLE_DEV_PM_OPS(st_thermal_pm_ops, st_thermal_suspend, st_thermal_resume);
EXPORT_SYMBOL_GPL(st_thermal_pm_ops);

MODULE_AUTHOR("STMicroelectronics (R&D) Limited <ajitpal.singh@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STi SoC Thermal Sensor Driver");
MODULE_LICENSE("GPL v2");
