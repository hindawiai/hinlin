<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Power Interface(SCPI) based hwmon sensor driver
 *
 * Copyright (C) 2015 ARM Ltd.
 * Punit Agrawal <punit.agrawal@arm.com>
 */

#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scpi_protocol.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>

काष्ठा sensor_data अणु
	अचिन्हित पूर्णांक scale;
	काष्ठा scpi_sensor_info info;
	काष्ठा device_attribute dev_attr_input;
	काष्ठा device_attribute dev_attr_label;
	अक्षर input[20];
	अक्षर label[20];
पूर्ण;

काष्ठा scpi_thermal_zone अणु
	पूर्णांक sensor_id;
	काष्ठा scpi_sensors *scpi_sensors;
पूर्ण;

काष्ठा scpi_sensors अणु
	काष्ठा scpi_ops *scpi_ops;
	काष्ठा sensor_data *data;
	काष्ठा list_head thermal_zones;
	काष्ठा attribute **attrs;
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];
पूर्ण;

अटल स्थिर u32 gxbb_scpi_scale[] = अणु
	[TEMPERATURE]	= 1,		/* (celsius)		*/
	[VOLTAGE]	= 1000,		/* (millivolts)		*/
	[CURRENT]	= 1000,		/* (milliamperes)	*/
	[POWER]		= 1000000,	/* (microwatts)		*/
	[ENERGY]	= 1000000,	/* (microjoules)	*/
पूर्ण;

अटल स्थिर u32 scpi_scale[] = अणु
	[TEMPERATURE]	= 1000,		/* (millicelsius)	*/
	[VOLTAGE]	= 1000,		/* (millivolts)		*/
	[CURRENT]	= 1000,		/* (milliamperes)	*/
	[POWER]		= 1000000,	/* (microwatts)		*/
	[ENERGY]	= 1000000,	/* (microjoules)	*/
पूर्ण;

अटल व्योम scpi_scale_पढ़ोing(u64 *value, काष्ठा sensor_data *sensor)
अणु
	अगर (scpi_scale[sensor->info.class] != sensor->scale) अणु
		*value *= scpi_scale[sensor->info.class];
		करो_भाग(*value, sensor->scale);
	पूर्ण
पूर्ण

अटल पूर्णांक scpi_पढ़ो_temp(व्योम *dev, पूर्णांक *temp)
अणु
	काष्ठा scpi_thermal_zone *zone = dev;
	काष्ठा scpi_sensors *scpi_sensors = zone->scpi_sensors;
	काष्ठा scpi_ops *scpi_ops = scpi_sensors->scpi_ops;
	काष्ठा sensor_data *sensor = &scpi_sensors->data[zone->sensor_id];
	u64 value;
	पूर्णांक ret;

	ret = scpi_ops->sensor_get_value(sensor->info.sensor_id, &value);
	अगर (ret)
		वापस ret;

	scpi_scale_पढ़ोing(&value, sensor);

	*temp = value;
	वापस 0;
पूर्ण

/* hwmon callback functions */
अटल sमाप_प्रकार
scpi_show_sensor(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा scpi_sensors *scpi_sensors = dev_get_drvdata(dev);
	काष्ठा scpi_ops *scpi_ops = scpi_sensors->scpi_ops;
	काष्ठा sensor_data *sensor;
	u64 value;
	पूर्णांक ret;

	sensor = container_of(attr, काष्ठा sensor_data, dev_attr_input);

	ret = scpi_ops->sensor_get_value(sensor->info.sensor_id, &value);
	अगर (ret)
		वापस ret;

	scpi_scale_पढ़ोing(&value, sensor);

	/*
	 * Temperature sensor values are treated as चिन्हित values based on
	 * observation even though that is not explicitly specअगरied, and
	 * because an अचिन्हित u64 temperature करोes not really make practical
	 * sense especially when the temperature is below zero degrees Celsius.
	 */
	अगर (sensor->info.class == TEMPERATURE)
		वापस प्र_लिखो(buf, "%lld\n", (s64)value);

	वापस प्र_लिखो(buf, "%llu\n", value);
पूर्ण

अटल sमाप_प्रकार
scpi_show_label(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sensor_data *sensor;

	sensor = container_of(attr, काष्ठा sensor_data, dev_attr_label);

	वापस प्र_लिखो(buf, "%s\n", sensor->info.name);
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops scpi_sensor_ops = अणु
	.get_temp = scpi_पढ़ो_temp,
पूर्ण;

अटल स्थिर काष्ठा of_device_id scpi_of_match[] = अणु
	अणु.compatible = "arm,scpi-sensors", .data = &scpi_scaleपूर्ण,
	अणु.compatible = "amlogic,meson-gxbb-scpi-sensors", .data = &gxbb_scpi_scaleपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, scpi_of_match);

अटल पूर्णांक scpi_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	u16 nr_sensors, i;
	स्थिर u32 *scale;
	पूर्णांक num_temp = 0, num_volt = 0, num_current = 0, num_घातer = 0;
	पूर्णांक num_energy = 0;
	काष्ठा scpi_ops *scpi_ops;
	काष्ठा device *hwdev, *dev = &pdev->dev;
	काष्ठा scpi_sensors *scpi_sensors;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक idx, ret;

	scpi_ops = get_scpi_ops();
	अगर (!scpi_ops)
		वापस -EPROBE_DEFER;

	ret = scpi_ops->sensor_get_capability(&nr_sensors);
	अगर (ret)
		वापस ret;

	अगर (!nr_sensors)
		वापस -ENODEV;

	scpi_sensors = devm_kzalloc(dev, माप(*scpi_sensors), GFP_KERNEL);
	अगर (!scpi_sensors)
		वापस -ENOMEM;

	scpi_sensors->data = devm_kसुस्मृति(dev, nr_sensors,
				   माप(*scpi_sensors->data), GFP_KERNEL);
	अगर (!scpi_sensors->data)
		वापस -ENOMEM;

	scpi_sensors->attrs = devm_kसुस्मृति(dev, (nr_sensors * 2) + 1,
				   माप(*scpi_sensors->attrs), GFP_KERNEL);
	अगर (!scpi_sensors->attrs)
		वापस -ENOMEM;

	scpi_sensors->scpi_ops = scpi_ops;

	of_id = of_match_device(scpi_of_match, &pdev->dev);
	अगर (!of_id) अणु
		dev_err(&pdev->dev, "Unable to initialize scpi-hwmon data\n");
		वापस -ENODEV;
	पूर्ण
	scale = of_id->data;

	क्रम (i = 0, idx = 0; i < nr_sensors; i++) अणु
		काष्ठा sensor_data *sensor = &scpi_sensors->data[idx];

		ret = scpi_ops->sensor_get_info(i, &sensor->info);
		अगर (ret)
			वापस ret;

		चयन (sensor->info.class) अणु
		हाल TEMPERATURE:
			snम_लिखो(sensor->input, माप(sensor->input),
				 "temp%d_input", num_temp + 1);
			snम_लिखो(sensor->label, माप(sensor->input),
				 "temp%d_label", num_temp + 1);
			num_temp++;
			अवरोध;
		हाल VOLTAGE:
			snम_लिखो(sensor->input, माप(sensor->input),
				 "in%d_input", num_volt);
			snम_लिखो(sensor->label, माप(sensor->input),
				 "in%d_label", num_volt);
			num_volt++;
			अवरोध;
		हाल CURRENT:
			snम_लिखो(sensor->input, माप(sensor->input),
				 "curr%d_input", num_current + 1);
			snम_लिखो(sensor->label, माप(sensor->input),
				 "curr%d_label", num_current + 1);
			num_current++;
			अवरोध;
		हाल POWER:
			snम_लिखो(sensor->input, माप(sensor->input),
				 "power%d_input", num_घातer + 1);
			snम_लिखो(sensor->label, माप(sensor->input),
				 "power%d_label", num_घातer + 1);
			num_घातer++;
			अवरोध;
		हाल ENERGY:
			snम_लिखो(sensor->input, माप(sensor->input),
				 "energy%d_input", num_energy + 1);
			snम_लिखो(sensor->label, माप(sensor->input),
				 "energy%d_label", num_energy + 1);
			num_energy++;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		sensor->scale = scale[sensor->info.class];

		sensor->dev_attr_input.attr.mode = 0444;
		sensor->dev_attr_input.show = scpi_show_sensor;
		sensor->dev_attr_input.attr.name = sensor->input;

		sensor->dev_attr_label.attr.mode = 0444;
		sensor->dev_attr_label.show = scpi_show_label;
		sensor->dev_attr_label.attr.name = sensor->label;

		scpi_sensors->attrs[idx << 1] = &sensor->dev_attr_input.attr;
		scpi_sensors->attrs[(idx << 1) + 1] = &sensor->dev_attr_label.attr;

		sysfs_attr_init(scpi_sensors->attrs[idx << 1]);
		sysfs_attr_init(scpi_sensors->attrs[(idx << 1) + 1]);
		idx++;
	पूर्ण

	scpi_sensors->group.attrs = scpi_sensors->attrs;
	scpi_sensors->groups[0] = &scpi_sensors->group;

	platक्रमm_set_drvdata(pdev, scpi_sensors);

	hwdev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
			"scpi_sensors", scpi_sensors, scpi_sensors->groups);

	अगर (IS_ERR(hwdev))
		वापस PTR_ERR(hwdev);

	/*
	 * Register the temperature sensors with the thermal framework
	 * to allow their usage in setting up the thermal zones from
	 * device tree.
	 *
	 * NOTE: Not all temperature sensors maybe used क्रम thermal
	 * control
	 */
	INIT_LIST_HEAD(&scpi_sensors->thermal_zones);
	क्रम (i = 0; i < nr_sensors; i++) अणु
		काष्ठा sensor_data *sensor = &scpi_sensors->data[i];
		काष्ठा thermal_zone_device *z;
		काष्ठा scpi_thermal_zone *zone;

		अगर (sensor->info.class != TEMPERATURE)
			जारी;

		zone = devm_kzalloc(dev, माप(*zone), GFP_KERNEL);
		अगर (!zone)
			वापस -ENOMEM;

		zone->sensor_id = i;
		zone->scpi_sensors = scpi_sensors;
		z = devm_thermal_zone_of_sensor_रेजिस्टर(dev,
							 sensor->info.sensor_id,
							 zone,
							 &scpi_sensor_ops);
		/*
		 * The call to thermal_zone_of_sensor_रेजिस्टर वापसs
		 * an error क्रम sensors that are not associated with
		 * any thermal zones or अगर the thermal subप्रणाली is
		 * not configured.
		 */
		अगर (IS_ERR(z))
			devm_kमुक्त(dev, zone);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver scpi_hwmon_platdrv = अणु
	.driver = अणु
		.name	= "scpi-hwmon",
		.of_match_table = scpi_of_match,
	पूर्ण,
	.probe		= scpi_hwmon_probe,
पूर्ण;
module_platक्रमm_driver(scpi_hwmon_platdrv);

MODULE_AUTHOR("Punit Agrawal <punit.agrawal@arm.com>");
MODULE_DESCRIPTION("ARM SCPI HWMON interface driver");
MODULE_LICENSE("GPL v2");
