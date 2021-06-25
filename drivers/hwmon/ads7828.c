<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ads7828.c - driver क्रम TI ADS7828 8-channel A/D converter and compatibles
 * (C) 2007 EADS Astrium
 *
 * This driver is based on the lm75 and other lm_sensors/hwmon drivers
 *
 * Written by Steve Hardy <shardy@redhat.com>
 *
 * ADS7830 support, by Guillaume Roguez <guillaume.roguez@savoirfairelinux.com>
 *
 * For further inक्रमmation, see the Documentation/hwmon/ads7828.rst file.
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_data/ads7828.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>

/* The ADS7828 रेजिस्टरs */
#घोषणा ADS7828_CMD_SD_SE	0x80	/* Single ended inमाला_दो */
#घोषणा ADS7828_CMD_PD1		0x04	/* Internal vref OFF && A/D ON */
#घोषणा ADS7828_CMD_PD3		0x0C	/* Internal vref ON && A/D ON */
#घोषणा ADS7828_INT_VREF_MV	2500	/* Internal vref is 2.5V, 2500mV */
#घोषणा ADS7828_EXT_VREF_MV_MIN	50	/* External vref min value 0.05V */
#घोषणा ADS7828_EXT_VREF_MV_MAX	5250	/* External vref max value 5.25V */

/* List of supported devices */
क्रमागत ads7828_chips अणु ads7828, ads7830 पूर्ण;

/* Client specअगरic data */
काष्ठा ads7828_data अणु
	काष्ठा regmap *regmap;
	u8 cmd_byte;			/* Command byte without channel bits */
	अचिन्हित पूर्णांक lsb_resol;		/* Resolution of the ADC sample LSB */
पूर्ण;

/* Command byte C2,C1,C0 - see datasheet */
अटल अंतरभूत u8 ads7828_cmd_byte(u8 cmd, पूर्णांक ch)
अणु
	वापस cmd | (((ch >> 1) | (ch & 0x01) << 2) << 4);
पूर्ण

/* sysfs callback function */
अटल sमाप_प्रकार ads7828_in_show(काष्ठा device *dev,
			       काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा ads7828_data *data = dev_get_drvdata(dev);
	u8 cmd = ads7828_cmd_byte(data->cmd_byte, attr->index);
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, cmd, &regval);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n",
		       DIV_ROUND_CLOSEST(regval * data->lsb_resol, 1000));
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, ads7828_in, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, ads7828_in, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, ads7828_in, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, ads7828_in, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, ads7828_in, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, ads7828_in, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, ads7828_in, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, ads7828_in, 7);

अटल काष्ठा attribute *ads7828_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(ads7828);

अटल स्थिर काष्ठा regmap_config ads2828_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ads2830_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id ads7828_device_ids[];

अटल पूर्णांक ads7828_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ads7828_platक्रमm_data *pdata = dev_get_platdata(dev);
	काष्ठा ads7828_data *data;
	काष्ठा device *hwmon_dev;
	अचिन्हित पूर्णांक vref_mv = ADS7828_INT_VREF_MV;
	अचिन्हित पूर्णांक vref_uv;
	bool dअगरf_input = false;
	bool ext_vref = false;
	अचिन्हित पूर्णांक regval;
	क्रमागत ads7828_chips chip;
	काष्ठा regulator *reg;

	data = devm_kzalloc(dev, माप(काष्ठा ads7828_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	अगर (pdata) अणु
		dअगरf_input = pdata->dअगरf_input;
		ext_vref = pdata->ext_vref;
		अगर (ext_vref && pdata->vref_mv)
			vref_mv = pdata->vref_mv;
	पूर्ण अन्यथा अगर (dev->of_node) अणु
		dअगरf_input = of_property_पढ़ो_bool(dev->of_node,
						   "ti,differential-input");
		reg = devm_regulator_get_optional(dev, "vref");
		अगर (!IS_ERR(reg)) अणु
			vref_uv = regulator_get_voltage(reg);
			vref_mv = DIV_ROUND_CLOSEST(vref_uv, 1000);
			अगर (vref_mv < ADS7828_EXT_VREF_MV_MIN ||
			    vref_mv > ADS7828_EXT_VREF_MV_MAX)
				वापस -EINVAL;
			ext_vref = true;
		पूर्ण
	पूर्ण

	अगर (client->dev.of_node)
		chip = (क्रमागत ads7828_chips)
			of_device_get_match_data(&client->dev);
	अन्यथा
		chip = i2c_match_id(ads7828_device_ids, client)->driver_data;

	/* Bound Vref with min/max values */
	vref_mv = clamp_val(vref_mv, ADS7828_EXT_VREF_MV_MIN,
			    ADS7828_EXT_VREF_MV_MAX);

	/* ADS7828 uses 12-bit samples, जबतक ADS7830 is 8-bit */
	अगर (chip == ads7828) अणु
		data->lsb_resol = DIV_ROUND_CLOSEST(vref_mv * 1000, 4096);
		data->regmap = devm_regmap_init_i2c(client,
						    &ads2828_regmap_config);
	पूर्ण अन्यथा अणु
		data->lsb_resol = DIV_ROUND_CLOSEST(vref_mv * 1000, 256);
		data->regmap = devm_regmap_init_i2c(client,
						    &ads2830_regmap_config);
	पूर्ण

	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	data->cmd_byte = ext_vref ? ADS7828_CMD_PD1 : ADS7828_CMD_PD3;
	अगर (!dअगरf_input)
		data->cmd_byte |= ADS7828_CMD_SD_SE;

	/*
	 * Datasheet specअगरies पूर्णांकernal reference voltage is disabled by
	 * शेष. The पूर्णांकernal reference voltage needs to be enabled and
	 * voltage needs to settle beक्रमe getting valid ADC data. So perक्रमm a
	 * dummy पढ़ो to enable the पूर्णांकernal reference voltage.
	 */
	अगर (!ext_vref)
		regmap_पढ़ो(data->regmap, data->cmd_byte, &regval);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   ads7828_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ads7828_device_ids[] = अणु
	अणु "ads7828", ads7828 पूर्ण,
	अणु "ads7830", ads7830 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ads7828_device_ids);

अटल स्थिर काष्ठा of_device_id __maybe_unused ads7828_of_match[] = अणु
	अणु
		.compatible = "ti,ads7828",
		.data = (व्योम *)ads7828
	पूर्ण,
	अणु
		.compatible = "ti,ads7830",
		.data = (व्योम *)ads7830
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ads7828_of_match);

अटल काष्ठा i2c_driver ads7828_driver = अणु
	.driver = अणु
		.name = "ads7828",
		.of_match_table = of_match_ptr(ads7828_of_match),
	पूर्ण,

	.id_table = ads7828_device_ids,
	.probe_new = ads7828_probe,
पूर्ण;

module_i2c_driver(ads7828_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steve Hardy <shardy@redhat.com>");
MODULE_DESCRIPTION("Driver for TI ADS7828 A/D converter and compatibles");
