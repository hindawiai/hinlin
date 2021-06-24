<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Sensirion SHTC1 humidity and temperature sensor driver
 *
 * Copyright (C) 2014 Sensirion AG, Switzerland
 * Author: Johannes Winkelmann <johannes.winkelmann@sensirion.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_data/shtc1.h>
#समावेश <linux/of.h>

/* commands (high precision mode) */
अटल स्थिर अचिन्हित अक्षर shtc1_cmd_measure_blocking_hpm[]    = अणु 0x7C, 0xA2 पूर्ण;
अटल स्थिर अचिन्हित अक्षर shtc1_cmd_measure_nonblocking_hpm[] = अणु 0x78, 0x66 पूर्ण;

/* commands (low precision mode) */
अटल स्थिर अचिन्हित अक्षर shtc1_cmd_measure_blocking_lpm[]    = अणु 0x64, 0x58 पूर्ण;
अटल स्थिर अचिन्हित अक्षर shtc1_cmd_measure_nonblocking_lpm[] = अणु 0x60, 0x9c पूर्ण;

/* command क्रम पढ़ोing the ID रेजिस्टर */
अटल स्थिर अचिन्हित अक्षर shtc1_cmd_पढ़ो_id_reg[]             = अणु 0xef, 0xc8 पूर्ण;

/*
 * स्थिरants क्रम पढ़ोing the ID रेजिस्टर
 * SHTC1: 0x0007 with mask 0x003f
 * SHTW1: 0x0007 with mask 0x003f
 * SHTC3: 0x0807 with mask 0x083f
 */
#घोषणा SHTC3_ID      0x0807
#घोषणा SHTC3_ID_MASK 0x083f
#घोषणा SHTC1_ID      0x0007
#घोषणा SHTC1_ID_MASK 0x003f

/* delays क्रम non-blocking i2c commands, both in us */
#घोषणा SHTC1_NONBLOCKING_WAIT_TIME_HPM  14400
#घोषणा SHTC1_NONBLOCKING_WAIT_TIME_LPM   1000
#घोषणा SHTC3_NONBLOCKING_WAIT_TIME_HPM  12100
#घोषणा SHTC3_NONBLOCKING_WAIT_TIME_LPM    800

#घोषणा SHTC1_CMD_LENGTH      2
#घोषणा SHTC1_RESPONSE_LENGTH 6

क्रमागत shtcx_chips अणु
	shtc1,
	shtc3,
पूर्ण;

काष्ठा shtc1_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	स्थिर अचिन्हित अक्षर *command;
	अचिन्हित पूर्णांक nonblocking_रुको_समय; /* in us */

	काष्ठा shtc1_platक्रमm_data setup;
	क्रमागत shtcx_chips chip;

	पूर्णांक temperature; /* 1000 * temperature in dgr C */
	पूर्णांक humidity; /* 1000 * relative humidity in %RH */
पूर्ण;

अटल पूर्णांक shtc1_update_values(काष्ठा i2c_client *client,
			       काष्ठा shtc1_data *data,
			       अक्षर *buf, पूर्णांक bufsize)
अणु
	पूर्णांक ret = i2c_master_send(client, data->command, SHTC1_CMD_LENGTH);
	अगर (ret != SHTC1_CMD_LENGTH) अणु
		dev_err(&client->dev, "failed to send command: %d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	/*
	 * In blocking mode (घड़ी stretching mode) the I2C bus
	 * is blocked क्रम other traffic, thus the call to i2c_master_recv()
	 * will रुको until the data is पढ़ोy. For non blocking mode, we
	 * have to रुको ourselves.
	 */
	अगर (!data->setup.blocking_io)
		usleep_range(data->nonblocking_रुको_समय,
			     data->nonblocking_रुको_समय + 1000);

	ret = i2c_master_recv(client, buf, bufsize);
	अगर (ret != bufsize) अणु
		dev_err(&client->dev, "failed to read values: %d\n", ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* sysfs attributes */
अटल काष्ठा shtc1_data *shtc1_update_client(काष्ठा device *dev)
अणु
	काष्ठा shtc1_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित अक्षर buf[SHTC1_RESPONSE_LENGTH];
	पूर्णांक val;
	पूर्णांक ret = 0;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ / 10) || !data->valid) अणु
		ret = shtc1_update_values(client, data, buf, माप(buf));
		अगर (ret)
			जाओ out;

		/*
		 * From datasheet:
		 * T = -45 + 175 * ST / 2^16
		 * RH = 100 * SRH / 2^16
		 *
		 * Adapted क्रम पूर्णांकeger fixed poपूर्णांक (3 digit) arithmetic.
		 */
		val = be16_to_cpup((__be16 *)buf);
		data->temperature = ((21875 * val) >> 13) - 45000;
		val = be16_to_cpup((__be16 *)(buf + 3));
		data->humidity = ((12500 * val) >> 13);

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण

out:
	mutex_unlock(&data->update_lock);

	वापस ret == 0 ? data : ERR_PTR(ret);
पूर्ण

अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा shtc1_data *data = shtc1_update_client(dev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->temperature);
पूर्ण

अटल sमाप_प्रकार humidity1_input_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा shtc1_data *data = shtc1_update_client(dev);
	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->humidity);
पूर्ण

अटल DEVICE_ATTR_RO(temp1_input);
अटल DEVICE_ATTR_RO(humidity1_input);

अटल काष्ठा attribute *shtc1_attrs[] = अणु
	&dev_attr_temp1_input.attr,
	&dev_attr_humidity1_input.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(shtc1);

अटल व्योम shtc1_select_command(काष्ठा shtc1_data *data)
अणु
	अगर (data->setup.high_precision) अणु
		data->command = data->setup.blocking_io ?
				shtc1_cmd_measure_blocking_hpm :
				shtc1_cmd_measure_nonblocking_hpm;
		data->nonblocking_रुको_समय = (data->chip == shtc1) ?
				SHTC1_NONBLOCKING_WAIT_TIME_HPM :
				SHTC3_NONBLOCKING_WAIT_TIME_HPM;
	पूर्ण अन्यथा अणु
		data->command = data->setup.blocking_io ?
				shtc1_cmd_measure_blocking_lpm :
				shtc1_cmd_measure_nonblocking_lpm;
		data->nonblocking_रुको_समय = (data->chip == shtc1) ?
				SHTC1_NONBLOCKING_WAIT_TIME_LPM :
				SHTC3_NONBLOCKING_WAIT_TIME_LPM;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा i2c_device_id shtc1_id[];

अटल पूर्णांक shtc1_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	u16 id_reg;
	अक्षर id_reg_buf[2];
	काष्ठा shtc1_data *data;
	काष्ठा device *hwmon_dev;
	क्रमागत shtcx_chips chip = i2c_match_id(shtc1_id, client)->driver_data;
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;

	अगर (!i2c_check_functionality(adap, I2C_FUNC_I2C)) अणु
		dev_err(dev, "plain i2c transactions not supported\n");
		वापस -ENODEV;
	पूर्ण

	ret = i2c_master_send(client, shtc1_cmd_पढ़ो_id_reg, SHTC1_CMD_LENGTH);
	अगर (ret != SHTC1_CMD_LENGTH) अणु
		dev_err(dev, "could not send read_id_reg command: %d\n", ret);
		वापस ret < 0 ? ret : -ENODEV;
	पूर्ण
	ret = i2c_master_recv(client, id_reg_buf, माप(id_reg_buf));
	अगर (ret != माप(id_reg_buf)) अणु
		dev_err(dev, "could not read ID register: %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	id_reg = be16_to_cpup((__be16 *)id_reg_buf);
	अगर (chip == shtc3) अणु
		अगर ((id_reg & SHTC3_ID_MASK) != SHTC3_ID) अणु
			dev_err(dev, "SHTC3 ID register does not match\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर ((id_reg & SHTC1_ID_MASK) != SHTC1_ID) अणु
		dev_err(dev, "SHTC1 ID register does not match\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->setup.blocking_io = false;
	data->setup.high_precision = true;
	data->client = client;
	data->chip = chip;

	अगर (np) अणु
		data->setup.blocking_io = of_property_पढ़ो_bool(np, "sensirion,blocking-io");
		data->setup.high_precision = !of_property_पढ़ो_bool(np, "sensicon,low-precision");
	पूर्ण अन्यथा अणु
		अगर (client->dev.platक्रमm_data)
			data->setup = *(काष्ठा shtc1_platक्रमm_data *)dev->platक्रमm_data;
	पूर्ण

	shtc1_select_command(data);
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
							   client->name,
							   data,
							   shtc1_groups);
	अगर (IS_ERR(hwmon_dev))
		dev_dbg(dev, "unable to register hwmon device\n");

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/* device ID table */
अटल स्थिर काष्ठा i2c_device_id shtc1_id[] = अणु
	अणु "shtc1", shtc1 पूर्ण,
	अणु "shtw1", shtc1 पूर्ण,
	अणु "shtc3", shtc3 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, shtc1_id);

अटल स्थिर काष्ठा of_device_id shtc1_of_match[] = अणु
	अणु .compatible = "sensirion,shtc1" पूर्ण,
	अणु .compatible = "sensirion,shtw1" पूर्ण,
	अणु .compatible = "sensirion,shtc3" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, shtc1_of_match);

अटल काष्ठा i2c_driver shtc1_i2c_driver = अणु
	.driver = अणु
		.name = "shtc1",
		.of_match_table = shtc1_of_match,
	पूर्ण,
	.probe_new    = shtc1_probe,
	.id_table     = shtc1_id,
पूर्ण;

module_i2c_driver(shtc1_i2c_driver);

MODULE_AUTHOR("Johannes Winkelmann <johannes.winkelmann@sensirion.com>");
MODULE_DESCRIPTION("Sensirion SHTC1 humidity and temperature sensor driver");
MODULE_LICENSE("GPL");
