<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ADM1177 Hot Swap Controller and Digital Power Monitor with Soft Start Pin
 *
 * Copyright 2015-2019 Analog Devices Inc.
 */

#समावेश <linux/bits.h>
#समावेश <linux/device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>

/*  Command Byte Operations */
#घोषणा ADM1177_CMD_V_CONT	BIT(0)
#घोषणा ADM1177_CMD_I_CONT	BIT(2)
#घोषणा ADM1177_CMD_VRANGE	BIT(4)

/* Extended Register */
#घोषणा ADM1177_REG_ALERT_TH	2

#घोषणा ADM1177_BITS		12

/**
 * काष्ठा adm1177_state - driver instance specअगरic data
 * @client:		poपूर्णांकer to i2c client
 * @reg:		regulator info क्रम the घातer supply of the device
 * @r_sense_uohm:	current sense resistor value
 * @alert_threshold_ua:	current limit क्रम shutकरोwn
 * @vrange_high:	पूर्णांकernal voltage भागider
 */
काष्ठा adm1177_state अणु
	काष्ठा i2c_client	*client;
	काष्ठा regulator	*reg;
	u32			r_sense_uohm;
	u32			alert_threshold_ua;
	bool			vrange_high;
पूर्ण;

अटल पूर्णांक adm1177_पढ़ो_raw(काष्ठा adm1177_state *st, u8 num, u8 *data)
अणु
	वापस i2c_master_recv(st->client, data, num);
पूर्ण

अटल पूर्णांक adm1177_ग_लिखो_cmd(काष्ठा adm1177_state *st, u8 cmd)
अणु
	वापस i2c_smbus_ग_लिखो_byte(st->client, cmd);
पूर्ण

अटल पूर्णांक adm1177_ग_लिखो_alert_thr(काष्ठा adm1177_state *st,
				   u32 alert_threshold_ua)
अणु
	u64 val;
	पूर्णांक ret;

	val = 0xFFULL * alert_threshold_ua * st->r_sense_uohm;
	val = भाग_u64(val, 105840000U);
	val = भाग_u64(val, 1000U);
	अगर (val > 0xFF)
		val = 0xFF;

	ret = i2c_smbus_ग_लिखो_byte_data(st->client, ADM1177_REG_ALERT_TH,
					val);
	अगर (ret)
		वापस ret;

	st->alert_threshold_ua = alert_threshold_ua;
	वापस 0;
पूर्ण

अटल पूर्णांक adm1177_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा adm1177_state *st = dev_get_drvdata(dev);
	u8 data[3];
	दीर्घ dummy;
	पूर्णांक ret;

	चयन (type) अणु
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
			ret = adm1177_पढ़ो_raw(st, 3, data);
			अगर (ret < 0)
				वापस ret;
			dummy = (data[1] << 4) | (data[2] & 0xF);
			/*
			 * convert to milliamperes
			 * ((105.84mV / 4096) x raw) / senseResistor(ohm)
			 */
			*val = भाग_u64((105840000ull * dummy),
				       4096 * st->r_sense_uohm);
			वापस 0;
		हाल hwmon_curr_max_alarm:
			*val = st->alert_threshold_ua;
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	हाल hwmon_in:
		ret = adm1177_पढ़ो_raw(st, 3, data);
		अगर (ret < 0)
			वापस ret;
		dummy = (data[0] << 4) | (data[2] >> 4);
		/*
		 * convert to millivolts based on resistor devision
		 * (V_fullscale / 4096) * raw
		 */
		अगर (st->vrange_high)
			dummy *= 26350;
		अन्यथा
			dummy *= 6650;

		*val = DIV_ROUND_CLOSEST(dummy, 4096);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक adm1177_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा adm1177_state *st = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_max_alarm:
			adm1177_ग_लिखो_alert_thr(st, val);
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t adm1177_is_visible(स्थिर व्योम *data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा adm1177_state *st = data;

	चयन (type) अणु
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_input:
			वापस 0444;
		पूर्ण
		अवरोध;
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
			अगर (st->r_sense_uohm)
				वापस 0444;
			वापस 0;
		हाल hwmon_curr_max_alarm:
			अगर (st->r_sense_uohm)
				वापस 0644;
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *adm1177_info[] = अणु
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_MAX_ALARM),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops adm1177_hwmon_ops = अणु
	.is_visible = adm1177_is_visible,
	.पढ़ो = adm1177_पढ़ो,
	.ग_लिखो = adm1177_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info adm1177_chip_info = अणु
	.ops = &adm1177_hwmon_ops,
	.info = adm1177_info,
पूर्ण;

अटल व्योम adm1177_हटाओ(व्योम *data)
अणु
	काष्ठा adm1177_state *st = data;

	regulator_disable(st->reg);
पूर्ण

अटल पूर्णांक adm1177_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा adm1177_state *st;
	u32 alert_threshold_ua;
	पूर्णांक ret;

	st = devm_kzalloc(dev, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->client = client;

	st->reg = devm_regulator_get_optional(&client->dev, "vref");
	अगर (IS_ERR(st->reg)) अणु
		अगर (PTR_ERR(st->reg) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;

		st->reg = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(&client->dev, adm1177_हटाओ,
					       st);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "shunt-resistor-micro-ohms",
				     &st->r_sense_uohm))
		st->r_sense_uohm = 0;
	अगर (device_property_पढ़ो_u32(dev, "adi,shutdown-threshold-microamp",
				     &alert_threshold_ua)) अणु
		अगर (st->r_sense_uohm)
			/*
			 * set maximum शेष value from datasheet based on
			 * shunt-resistor
			 */
			alert_threshold_ua = भाग_u64(105840000000,
						     st->r_sense_uohm);
		अन्यथा
			alert_threshold_ua = 0;
	पूर्ण
	st->vrange_high = device_property_पढ़ो_bool(dev,
						    "adi,vrange-high-enable");
	अगर (alert_threshold_ua && st->r_sense_uohm)
		adm1177_ग_लिखो_alert_thr(st, alert_threshold_ua);

	ret = adm1177_ग_लिखो_cmd(st, ADM1177_CMD_V_CONT |
				    ADM1177_CMD_I_CONT |
				    (st->vrange_high ? 0 : ADM1177_CMD_VRANGE));
	अगर (ret)
		वापस ret;

	hwmon_dev =
		devm_hwmon_device_रेजिस्टर_with_info(dev, client->name, st,
						     &adm1177_chip_info, शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adm1177_id[] = अणु
	अणु"adm1177", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adm1177_id);

अटल स्थिर काष्ठा of_device_id adm1177_dt_ids[] = अणु
	अणु .compatible = "adi,adm1177" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adm1177_dt_ids);

अटल काष्ठा i2c_driver adm1177_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "adm1177",
		.of_match_table = adm1177_dt_ids,
	पूर्ण,
	.probe_new = adm1177_probe,
	.id_table = adm1177_id,
पूर्ण;
module_i2c_driver(adm1177_driver);

MODULE_AUTHOR("Beniamin Bia <beniamin.bia@analog.com>");
MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADM1177 ADC driver");
MODULE_LICENSE("GPL v2");
