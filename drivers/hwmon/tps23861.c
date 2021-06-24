<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 Sartura Ltd.
 *
 * Driver क्रम the TI TPS23861 PoE PSE.
 *
 * Author: Robert Marko <robert.marko@sartura.hr>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#घोषणा TEMPERATURE			0x2c
#घोषणा INPUT_VOLTAGE_LSB		0x2e
#घोषणा INPUT_VOLTAGE_MSB		0x2f
#घोषणा PORT_1_CURRENT_LSB		0x30
#घोषणा PORT_1_CURRENT_MSB		0x31
#घोषणा PORT_1_VOLTAGE_LSB		0x32
#घोषणा PORT_1_VOLTAGE_MSB		0x33
#घोषणा PORT_2_CURRENT_LSB		0x34
#घोषणा PORT_2_CURRENT_MSB		0x35
#घोषणा PORT_2_VOLTAGE_LSB		0x36
#घोषणा PORT_2_VOLTAGE_MSB		0x37
#घोषणा PORT_3_CURRENT_LSB		0x38
#घोषणा PORT_3_CURRENT_MSB		0x39
#घोषणा PORT_3_VOLTAGE_LSB		0x3a
#घोषणा PORT_3_VOLTAGE_MSB		0x3b
#घोषणा PORT_4_CURRENT_LSB		0x3c
#घोषणा PORT_4_CURRENT_MSB		0x3d
#घोषणा PORT_4_VOLTAGE_LSB		0x3e
#घोषणा PORT_4_VOLTAGE_MSB		0x3f
#घोषणा PORT_N_CURRENT_LSB_OFFSET	0x04
#घोषणा PORT_N_VOLTAGE_LSB_OFFSET	0x04
#घोषणा VOLTAGE_CURRENT_MASK		GENMASK(13, 0)
#घोषणा PORT_1_RESISTANCE_LSB		0x60
#घोषणा PORT_1_RESISTANCE_MSB		0x61
#घोषणा PORT_2_RESISTANCE_LSB		0x62
#घोषणा PORT_2_RESISTANCE_MSB		0x63
#घोषणा PORT_3_RESISTANCE_LSB		0x64
#घोषणा PORT_3_RESISTANCE_MSB		0x65
#घोषणा PORT_4_RESISTANCE_LSB		0x66
#घोषणा PORT_4_RESISTANCE_MSB		0x67
#घोषणा PORT_N_RESISTANCE_LSB_OFFSET	0x02
#घोषणा PORT_RESISTANCE_MASK		GENMASK(13, 0)
#घोषणा PORT_RESISTANCE_RSN_MASK	GENMASK(15, 14)
#घोषणा PORT_RESISTANCE_RSN_OTHER	0
#घोषणा PORT_RESISTANCE_RSN_LOW		1
#घोषणा PORT_RESISTANCE_RSN_OPEN	2
#घोषणा PORT_RESISTANCE_RSN_SHORT	3
#घोषणा PORT_1_STATUS			0x0c
#घोषणा PORT_2_STATUS			0x0d
#घोषणा PORT_3_STATUS			0x0e
#घोषणा PORT_4_STATUS			0x0f
#घोषणा PORT_STATUS_CLASS_MASK		GENMASK(7, 4)
#घोषणा PORT_STATUS_DETECT_MASK		GENMASK(3, 0)
#घोषणा PORT_CLASS_UNKNOWN		0
#घोषणा PORT_CLASS_1			1
#घोषणा PORT_CLASS_2			2
#घोषणा PORT_CLASS_3			3
#घोषणा PORT_CLASS_4			4
#घोषणा PORT_CLASS_RESERVED		5
#घोषणा PORT_CLASS_0			6
#घोषणा PORT_CLASS_OVERCURRENT		7
#घोषणा PORT_CLASS_MISMATCH		8
#घोषणा PORT_DETECT_UNKNOWN		0
#घोषणा PORT_DETECT_SHORT		1
#घोषणा PORT_DETECT_RESERVED		2
#घोषणा PORT_DETECT_RESISTANCE_LOW	3
#घोषणा PORT_DETECT_RESISTANCE_OK	4
#घोषणा PORT_DETECT_RESISTANCE_HIGH	5
#घोषणा PORT_DETECT_OPEN_CIRCUIT	6
#घोषणा PORT_DETECT_RESERVED_2		7
#घोषणा PORT_DETECT_MOSFET_FAULT	8
#घोषणा PORT_DETECT_LEGACY		9
/* Measurment beyond clamp voltage */
#घोषणा PORT_DETECT_CAPACITANCE_INVALID_BEYOND	10
/* Insufficient voltage delta */
#घोषणा PORT_DETECT_CAPACITANCE_INVALID_DELTA	11
#घोषणा PORT_DETECT_CAPACITANCE_OUT_OF_RANGE	12
#घोषणा POE_PLUS			0x40
#घोषणा OPERATING_MODE			0x12
#घोषणा OPERATING_MODE_OFF		0
#घोषणा OPERATING_MODE_MANUAL		1
#घोषणा OPERATING_MODE_SEMI		2
#घोषणा OPERATING_MODE_AUTO		3
#घोषणा OPERATING_MODE_PORT_1_MASK	GENMASK(1, 0)
#घोषणा OPERATING_MODE_PORT_2_MASK	GENMASK(3, 2)
#घोषणा OPERATING_MODE_PORT_3_MASK	GENMASK(5, 4)
#घोषणा OPERATING_MODE_PORT_4_MASK	GENMASK(7, 6)

#घोषणा DETECT_CLASS_RESTART		0x18
#घोषणा POWER_ENABLE			0x19
#घोषणा TPS23861_NUM_PORTS		4

#घोषणा TPS23861_GENERAL_MASK_1		0x17
#घोषणा TPS23861_CURRENT_SHUNT_MASK	BIT(0)

#घोषणा TEMPERATURE_LSB			652 /* 0.652 degrees Celsius */
#घोषणा VOLTAGE_LSB			3662 /* 3.662 mV */
#घोषणा SHUNT_RESISTOR_DEFAULT		255000 /* 255 mOhm */
#घोषणा CURRENT_LSB_250			62260 /* 62.260 uA */
#घोषणा CURRENT_LSB_255			61039 /* 61.039 uA */
#घोषणा RESISTANCE_LSB			110966 /* 11.0966 Ohm*/
#घोषणा RESISTANCE_LSB_LOW		157216 /* 15.7216 Ohm*/

काष्ठा tps23861_data अणु
	काष्ठा regmap *regmap;
	u32 shunt_resistor;
	काष्ठा i2c_client *client;
	काष्ठा dentry *debugfs_dir;
पूर्ण;

अटल काष्ठा regmap_config tps23861_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0x6f,
पूर्ण;

अटल पूर्णांक tps23861_पढ़ो_temp(काष्ठा tps23861_data *data, दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	err = regmap_पढ़ो(data->regmap, TEMPERATURE, &regval);
	अगर (err < 0)
		वापस err;

	*val = (regval * TEMPERATURE_LSB) - 20000;

	वापस 0;
पूर्ण

अटल पूर्णांक tps23861_पढ़ो_voltage(काष्ठा tps23861_data *data, पूर्णांक channel,
				 दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	अगर (channel < TPS23861_NUM_PORTS) अणु
		err = regmap_bulk_पढ़ो(data->regmap,
				       PORT_1_VOLTAGE_LSB + channel * PORT_N_VOLTAGE_LSB_OFFSET,
				       &regval, 2);
	पूर्ण अन्यथा अणु
		err = regmap_bulk_पढ़ो(data->regmap,
				       INPUT_VOLTAGE_LSB,
				       &regval, 2);
	पूर्ण
	अगर (err < 0)
		वापस err;

	*val = (FIELD_GET(VOLTAGE_CURRENT_MASK, regval) * VOLTAGE_LSB) / 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक tps23861_पढ़ो_current(काष्ठा tps23861_data *data, पूर्णांक channel,
				 दीर्घ *val)
अणु
	अचिन्हित पूर्णांक current_lsb;
	अचिन्हित पूर्णांक regval;
	पूर्णांक err;

	अगर (data->shunt_resistor == SHUNT_RESISTOR_DEFAULT)
		current_lsb = CURRENT_LSB_255;
	अन्यथा
		current_lsb = CURRENT_LSB_250;

	err = regmap_bulk_पढ़ो(data->regmap,
			       PORT_1_CURRENT_LSB + channel * PORT_N_CURRENT_LSB_OFFSET,
			       &regval, 2);
	अगर (err < 0)
		वापस err;

	*val = (FIELD_GET(VOLTAGE_CURRENT_MASK, regval) * current_lsb) / 1000000;

	वापस 0;
पूर्ण

अटल पूर्णांक tps23861_port_disable(काष्ठा tps23861_data *data, पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक regval = 0;
	पूर्णांक err;

	regval |= BIT(channel + 4);
	err = regmap_ग_लिखो(data->regmap, POWER_ENABLE, regval);

	वापस err;
पूर्ण

अटल पूर्णांक tps23861_port_enable(काष्ठा tps23861_data *data, पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक regval = 0;
	पूर्णांक err;

	regval |= BIT(channel);
	regval |= BIT(channel + 4);
	err = regmap_ग_लिखो(data->regmap, DETECT_CLASS_RESTART, regval);

	वापस err;
पूर्ण

अटल umode_t tps23861_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				   u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_label:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
		हाल hwmon_in_label:
			वापस 0444;
		हाल hwmon_in_enable:
			वापस 0200;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
		हाल hwmon_curr_label:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tps23861_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			  u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा tps23861_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	चयन (type) अणु
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_enable:
			अगर (val == 0)
				err = tps23861_port_disable(data, channel);
			अन्यथा अगर (val == 1)
				err = tps23861_port_enable(data, channel);
			अन्यथा
				err = -EINVAL;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक tps23861_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा tps23861_data *data = dev_get_drvdata(dev);
	पूर्णांक err;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			err = tps23861_पढ़ो_temp(data, val);
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
			err = tps23861_पढ़ो_voltage(data, channel, val);
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
			err = tps23861_पढ़ो_current(data, channel, val);
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर अक्षर * स्थिर tps23861_port_label[] = अणु
	"Port1",
	"Port2",
	"Port3",
	"Port4",
	"Input",
पूर्ण;

अटल पूर्णांक tps23861_पढ़ो_string(काष्ठा device *dev,
				क्रमागत hwmon_sensor_types type,
				u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_in:
	हाल hwmon_curr:
		*str = tps23861_port_label[channel];
		अवरोध;
	हाल hwmon_temp:
		*str = "Die";
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *tps23861_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_LABEL),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_ENABLE | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_ENABLE | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_ENABLE | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_ENABLE | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL,
			   HWMON_C_INPUT | HWMON_C_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops tps23861_hwmon_ops = अणु
	.is_visible = tps23861_is_visible,
	.ग_लिखो = tps23861_ग_लिखो,
	.पढ़ो = tps23861_पढ़ो,
	.पढ़ो_string = tps23861_पढ़ो_string,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info tps23861_chip_info = अणु
	.ops = &tps23861_hwmon_ops,
	.info = tps23861_info,
पूर्ण;

अटल अक्षर *tps23861_port_operating_mode(काष्ठा tps23861_data *data, पूर्णांक port)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक mode;

	regmap_पढ़ो(data->regmap, OPERATING_MODE, &regval);

	चयन (port) अणु
	हाल 1:
		mode = FIELD_GET(OPERATING_MODE_PORT_1_MASK, regval);
		अवरोध;
	हाल 2:
		mode = FIELD_GET(OPERATING_MODE_PORT_2_MASK, regval);
		अवरोध;
	हाल 3:
		mode = FIELD_GET(OPERATING_MODE_PORT_3_MASK, regval);
		अवरोध;
	हाल 4:
		mode = FIELD_GET(OPERATING_MODE_PORT_4_MASK, regval);
		अवरोध;
	शेष:
		mode = -EINVAL;
	पूर्ण

	चयन (mode) अणु
	हाल OPERATING_MODE_OFF:
		वापस "Off";
	हाल OPERATING_MODE_MANUAL:
		वापस "Manual";
	हाल OPERATING_MODE_SEMI:
		वापस "Semi-Auto";
	हाल OPERATING_MODE_AUTO:
		वापस "Auto";
	शेष:
		वापस "Invalid";
	पूर्ण
पूर्ण

अटल अक्षर *tps23861_port_detect_status(काष्ठा tps23861_data *data, पूर्णांक port)
अणु
	अचिन्हित पूर्णांक regval;

	regmap_पढ़ो(data->regmap,
		    PORT_1_STATUS + (port - 1),
		    &regval);

	चयन (FIELD_GET(PORT_STATUS_DETECT_MASK, regval)) अणु
	हाल PORT_DETECT_UNKNOWN:
		वापस "Unknown device";
	हाल PORT_DETECT_SHORT:
		वापस "Short circuit";
	हाल PORT_DETECT_RESISTANCE_LOW:
		वापस "Too low resistance";
	हाल PORT_DETECT_RESISTANCE_OK:
		वापस "Valid resistance";
	हाल PORT_DETECT_RESISTANCE_HIGH:
		वापस "Too high resistance";
	हाल PORT_DETECT_OPEN_CIRCUIT:
		वापस "Open circuit";
	हाल PORT_DETECT_MOSFET_FAULT:
		वापस "MOSFET fault";
	हाल PORT_DETECT_LEGACY:
		वापस "Legacy device";
	हाल PORT_DETECT_CAPACITANCE_INVALID_BEYOND:
		वापस "Invalid capacitance, beyond clamp voltage";
	हाल PORT_DETECT_CAPACITANCE_INVALID_DELTA:
		वापस "Invalid capacitance, insufficient voltage delta";
	हाल PORT_DETECT_CAPACITANCE_OUT_OF_RANGE:
		वापस "Valid capacitance, outside of legacy range";
	हाल PORT_DETECT_RESERVED:
	हाल PORT_DETECT_RESERVED_2:
	शेष:
		वापस "Invalid";
	पूर्ण
पूर्ण

अटल अक्षर *tps23861_port_class_status(काष्ठा tps23861_data *data, पूर्णांक port)
अणु
	अचिन्हित पूर्णांक regval;

	regmap_पढ़ो(data->regmap,
		    PORT_1_STATUS + (port - 1),
		    &regval);

	चयन (FIELD_GET(PORT_STATUS_CLASS_MASK, regval)) अणु
	हाल PORT_CLASS_UNKNOWN:
		वापस "Unknown";
	हाल PORT_CLASS_RESERVED:
	हाल PORT_CLASS_0:
		वापस "0";
	हाल PORT_CLASS_1:
		वापस "1";
	हाल PORT_CLASS_2:
		वापस "2";
	हाल PORT_CLASS_3:
		वापस "3";
	हाल PORT_CLASS_4:
		वापस "4";
	हाल PORT_CLASS_OVERCURRENT:
		वापस "Overcurrent";
	हाल PORT_CLASS_MISMATCH:
		वापस "Mismatch";
	शेष:
		वापस "Invalid";
	पूर्ण
पूर्ण

अटल अक्षर *tps23861_port_poe_plus_status(काष्ठा tps23861_data *data, पूर्णांक port)
अणु
	अचिन्हित पूर्णांक regval;

	regmap_पढ़ो(data->regmap, POE_PLUS, &regval);

	अगर (BIT(port + 3) & regval)
		वापस "Yes";
	अन्यथा
		वापस "No";
पूर्ण

अटल पूर्णांक tps23861_port_resistance(काष्ठा tps23861_data *data, पूर्णांक port)
अणु
	u16 regval;

	regmap_bulk_पढ़ो(data->regmap,
			 PORT_1_RESISTANCE_LSB + PORT_N_RESISTANCE_LSB_OFFSET * (port - 1),
			 &regval,
			 2);

	चयन (FIELD_GET(PORT_RESISTANCE_RSN_MASK, regval)) अणु
	हाल PORT_RESISTANCE_RSN_OTHER:
		वापस (FIELD_GET(PORT_RESISTANCE_MASK, regval) * RESISTANCE_LSB) / 10000;
	हाल PORT_RESISTANCE_RSN_LOW:
		वापस (FIELD_GET(PORT_RESISTANCE_MASK, regval) * RESISTANCE_LSB_LOW) / 10000;
	हाल PORT_RESISTANCE_RSN_SHORT:
	हाल PORT_RESISTANCE_RSN_OPEN:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक tps23861_port_status_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा tps23861_data *priv = s->निजी;
	पूर्णांक i;

	क्रम (i = 1; i < TPS23861_NUM_PORTS + 1; i++) अणु
		seq_म_लिखो(s, "Port: \t\t%d\n", i);
		seq_म_लिखो(s, "Operating mode: %s\n", tps23861_port_operating_mode(priv, i));
		seq_म_लिखो(s, "Detected: \t%s\n", tps23861_port_detect_status(priv, i));
		seq_म_लिखो(s, "Class: \t\t%s\n", tps23861_port_class_status(priv, i));
		seq_म_लिखो(s, "PoE Plus: \t%s\n", tps23861_port_poe_plus_status(priv, i));
		seq_म_लिखो(s, "Resistance: \t%d\n", tps23861_port_resistance(priv, i));
		seq_अ_दो(s, '\n');
	पूर्ण

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(tps23861_port_status);

अटल व्योम tps23861_init_debugfs(काष्ठा tps23861_data *data)
अणु
	data->debugfs_dir = debugfs_create_dir(data->client->name, शून्य);

	debugfs_create_file("port_status",
			    0400,
			    data->debugfs_dir,
			    data,
			    &tps23861_port_status_fops);
पूर्ण

अटल पूर्णांक tps23861_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा tps23861_data *data;
	काष्ठा device *hwmon_dev;
	u32 shunt_resistor;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	i2c_set_clientdata(client, data);

	data->regmap = devm_regmap_init_i2c(client, &tps23861_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(dev->of_node, "shunt-resistor-micro-ohms", &shunt_resistor))
		data->shunt_resistor = shunt_resistor;
	अन्यथा
		data->shunt_resistor = SHUNT_RESISTOR_DEFAULT;

	अगर (data->shunt_resistor == SHUNT_RESISTOR_DEFAULT)
		regmap_clear_bits(data->regmap,
				  TPS23861_GENERAL_MASK_1,
				  TPS23861_CURRENT_SHUNT_MASK);
	अन्यथा
		regmap_set_bits(data->regmap,
				TPS23861_GENERAL_MASK_1,
				TPS23861_CURRENT_SHUNT_MASK);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data, &tps23861_chip_info,
							 शून्य);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	tps23861_init_debugfs(data);

	वापस 0;
पूर्ण

अटल पूर्णांक tps23861_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tps23861_data *data = i2c_get_clientdata(client);

	debugfs_हटाओ_recursive(data->debugfs_dir);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused tps23861_of_match[] = अणु
	अणु .compatible = "ti,tps23861", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tps23861_of_match);

अटल काष्ठा i2c_driver tps23861_driver = अणु
	.probe_new		= tps23861_probe,
	.हटाओ			= tps23861_हटाओ,
	.driver = अणु
		.name		= "tps23861",
		.of_match_table	= of_match_ptr(tps23861_of_match),
	पूर्ण,
पूर्ण;
module_i2c_driver(tps23861_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert Marko <robert.marko@sartura.hr>");
MODULE_DESCRIPTION("TI TPS23861 PoE PSE");
