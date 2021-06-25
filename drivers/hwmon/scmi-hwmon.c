<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * System Control and Management Interface(SCMI) based hwmon sensor driver
 *
 * Copyright (C) 2018-2021 ARM Ltd.
 * Sudeep Holla <sudeep.holla@arm.com>
 */

#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/scmi_protocol.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>

अटल स्थिर काष्ठा scmi_sensor_proto_ops *sensor_ops;

काष्ठा scmi_sensors अणु
	स्थिर काष्ठा scmi_protocol_handle *ph;
	स्थिर काष्ठा scmi_sensor_info **info[hwmon_max];
पूर्ण;

अटल अंतरभूत u64 __घात10(u8 x)
अणु
	u64 r = 1;

	जबतक (x--)
		r *= 10;

	वापस r;
पूर्ण

अटल पूर्णांक scmi_hwmon_scale(स्थिर काष्ठा scmi_sensor_info *sensor, u64 *value)
अणु
	पूर्णांक scale = sensor->scale;
	u64 f;

	चयन (sensor->type) अणु
	हाल TEMPERATURE_C:
	हाल VOLTAGE:
	हाल CURRENT:
		scale += 3;
		अवरोध;
	हाल POWER:
	हाल ENERGY:
		scale += 6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (scale == 0)
		वापस 0;

	अगर (असल(scale) > 19)
		वापस -E2BIG;

	f = __घात10(असल(scale));
	अगर (scale > 0)
		*value *= f;
	अन्यथा
		*value = भाग64_u64(*value, f);

	वापस 0;
पूर्ण

अटल पूर्णांक scmi_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			   u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	पूर्णांक ret;
	u64 value;
	स्थिर काष्ठा scmi_sensor_info *sensor;
	काष्ठा scmi_sensors *scmi_sensors = dev_get_drvdata(dev);

	sensor = *(scmi_sensors->info[type] + channel);
	ret = sensor_ops->पढ़ोing_get(scmi_sensors->ph, sensor->id, &value);
	अगर (ret)
		वापस ret;

	ret = scmi_hwmon_scale(sensor, &value);
	अगर (!ret)
		*val = value;

	वापस ret;
पूर्ण

अटल पूर्णांक
scmi_hwmon_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	स्थिर काष्ठा scmi_sensor_info *sensor;
	काष्ठा scmi_sensors *scmi_sensors = dev_get_drvdata(dev);

	sensor = *(scmi_sensors->info[type] + channel);
	*str = sensor->name;

	वापस 0;
पूर्ण

अटल umode_t
scmi_hwmon_is_visible(स्थिर व्योम *drvdata, क्रमागत hwmon_sensor_types type,
		      u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा scmi_sensor_info *sensor;
	स्थिर काष्ठा scmi_sensors *scmi_sensors = drvdata;

	sensor = *(scmi_sensors->info[type] + channel);
	अगर (sensor)
		वापस 0444;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops scmi_hwmon_ops = अणु
	.is_visible = scmi_hwmon_is_visible,
	.पढ़ो = scmi_hwmon_पढ़ो,
	.पढ़ो_string = scmi_hwmon_पढ़ो_string,
पूर्ण;

अटल काष्ठा hwmon_chip_info scmi_chip_info = अणु
	.ops = &scmi_hwmon_ops,
	.info = शून्य,
पूर्ण;

अटल पूर्णांक scmi_hwmon_add_chan_info(काष्ठा hwmon_channel_info *scmi_hwmon_chan,
				    काष्ठा device *dev, पूर्णांक num,
				    क्रमागत hwmon_sensor_types type, u32 config)
अणु
	पूर्णांक i;
	u32 *cfg = devm_kसुस्मृति(dev, num + 1, माप(*cfg), GFP_KERNEL);

	अगर (!cfg)
		वापस -ENOMEM;

	scmi_hwmon_chan->type = type;
	scmi_hwmon_chan->config = cfg;
	क्रम (i = 0; i < num; i++, cfg++)
		*cfg = config;

	वापस 0;
पूर्ण

अटल क्रमागत hwmon_sensor_types scmi_types[] = अणु
	[TEMPERATURE_C] = hwmon_temp,
	[VOLTAGE] = hwmon_in,
	[CURRENT] = hwmon_curr,
	[POWER] = hwmon_घातer,
	[ENERGY] = hwmon_energy,
पूर्ण;

अटल u32 hwmon_attributes[hwmon_max] = अणु
	[hwmon_chip] = HWMON_C_REGISTER_TZ,
	[hwmon_temp] = HWMON_T_INPUT | HWMON_T_LABEL,
	[hwmon_in] = HWMON_I_INPUT | HWMON_I_LABEL,
	[hwmon_curr] = HWMON_C_INPUT | HWMON_C_LABEL,
	[hwmon_घातer] = HWMON_P_INPUT | HWMON_P_LABEL,
	[hwmon_energy] = HWMON_E_INPUT | HWMON_E_LABEL,
पूर्ण;

अटल पूर्णांक scmi_hwmon_probe(काष्ठा scmi_device *sdev)
अणु
	पूर्णांक i, idx;
	u16 nr_sensors;
	क्रमागत hwmon_sensor_types type;
	काष्ठा scmi_sensors *scmi_sensors;
	स्थिर काष्ठा scmi_sensor_info *sensor;
	पूर्णांक nr_count[hwmon_max] = अणु0पूर्ण, nr_types = 0;
	स्थिर काष्ठा hwmon_chip_info *chip_info;
	काष्ठा device *hwdev, *dev = &sdev->dev;
	काष्ठा hwmon_channel_info *scmi_hwmon_chan;
	स्थिर काष्ठा hwmon_channel_info **ptr_scmi_ci;
	स्थिर काष्ठा scmi_handle *handle = sdev->handle;
	काष्ठा scmi_protocol_handle *ph;

	अगर (!handle)
		वापस -ENODEV;

	sensor_ops = handle->devm_protocol_get(sdev, SCMI_PROTOCOL_SENSOR, &ph);
	अगर (IS_ERR(sensor_ops))
		वापस PTR_ERR(sensor_ops);

	nr_sensors = sensor_ops->count_get(ph);
	अगर (!nr_sensors)
		वापस -EIO;

	scmi_sensors = devm_kzalloc(dev, माप(*scmi_sensors), GFP_KERNEL);
	अगर (!scmi_sensors)
		वापस -ENOMEM;

	scmi_sensors->ph = ph;

	क्रम (i = 0; i < nr_sensors; i++) अणु
		sensor = sensor_ops->info_get(ph, i);
		अगर (!sensor)
			वापस -EINVAL;

		चयन (sensor->type) अणु
		हाल TEMPERATURE_C:
		हाल VOLTAGE:
		हाल CURRENT:
		हाल POWER:
		हाल ENERGY:
			type = scmi_types[sensor->type];
			अगर (!nr_count[type])
				nr_types++;
			nr_count[type]++;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nr_count[hwmon_temp]) अणु
		nr_count[hwmon_chip]++;
		nr_types++;
	पूर्ण

	scmi_hwmon_chan = devm_kसुस्मृति(dev, nr_types, माप(*scmi_hwmon_chan),
				       GFP_KERNEL);
	अगर (!scmi_hwmon_chan)
		वापस -ENOMEM;

	ptr_scmi_ci = devm_kसुस्मृति(dev, nr_types + 1, माप(*ptr_scmi_ci),
				   GFP_KERNEL);
	अगर (!ptr_scmi_ci)
		वापस -ENOMEM;

	scmi_chip_info.info = ptr_scmi_ci;
	chip_info = &scmi_chip_info;

	क्रम (type = 0; type < hwmon_max; type++) अणु
		अगर (!nr_count[type])
			जारी;

		scmi_hwmon_add_chan_info(scmi_hwmon_chan, dev, nr_count[type],
					 type, hwmon_attributes[type]);
		*ptr_scmi_ci++ = scmi_hwmon_chan++;

		scmi_sensors->info[type] =
			devm_kसुस्मृति(dev, nr_count[type],
				     माप(*scmi_sensors->info), GFP_KERNEL);
		अगर (!scmi_sensors->info[type])
			वापस -ENOMEM;
	पूर्ण

	क्रम (i = nr_sensors - 1; i >= 0 ; i--) अणु
		sensor = sensor_ops->info_get(ph, i);
		अगर (!sensor)
			जारी;

		चयन (sensor->type) अणु
		हाल TEMPERATURE_C:
		हाल VOLTAGE:
		हाल CURRENT:
		हाल POWER:
		हाल ENERGY:
			type = scmi_types[sensor->type];
			idx = --nr_count[type];
			*(scmi_sensors->info[type] + idx) = sensor;
			अवरोध;
		पूर्ण
	पूर्ण

	hwdev = devm_hwmon_device_रेजिस्टर_with_info(dev, "scmi_sensors",
						     scmi_sensors, chip_info,
						     शून्य);

	वापस PTR_ERR_OR_ZERO(hwdev);
पूर्ण

अटल स्थिर काष्ठा scmi_device_id scmi_id_table[] = अणु
	अणु SCMI_PROTOCOL_SENSOR, "hwmon" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(scmi, scmi_id_table);

अटल काष्ठा scmi_driver scmi_hwmon_drv = अणु
	.name		= "scmi-hwmon",
	.probe		= scmi_hwmon_probe,
	.id_table	= scmi_id_table,
पूर्ण;
module_scmi_driver(scmi_hwmon_drv);

MODULE_AUTHOR("Sudeep Holla <sudeep.holla@arm.com>");
MODULE_DESCRIPTION("ARM SCMI HWMON interface driver");
MODULE_LICENSE("GPL v2");
