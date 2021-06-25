<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Sensirion SHT21 humidity and temperature sensor driver
 *
 * Copyright (C) 2010 Urs Fleisch <urs.fleisch@sensirion.com>
 *
 * Data sheet available at https://www.sensirion.com/file/datasheet_sht21
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>

/* I2C command bytes */
#घोषणा SHT21_TRIG_T_MEASUREMENT_HM  0xe3
#घोषणा SHT21_TRIG_RH_MEASUREMENT_HM 0xe5
#घोषणा SHT21_READ_SNB_CMD1 0xFA
#घोषणा SHT21_READ_SNB_CMD2 0x0F
#घोषणा SHT21_READ_SNAC_CMD1 0xFC
#घोषणा SHT21_READ_SNAC_CMD2 0xC9

/**
 * काष्ठा sht21 - SHT21 device specअगरic data
 * @client: I2C client device
 * @lock: mutex to protect measurement values
 * @last_update: समय of last update (jअगरfies)
 * @temperature: cached temperature measurement value
 * @humidity: cached humidity measurement value
 * @valid: only 0 beक्रमe first measurement is taken
 * @eic: cached electronic identअगरication code text
 */
काष्ठा sht21 अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	अचिन्हित दीर्घ last_update;
	पूर्णांक temperature;
	पूर्णांक humidity;
	अक्षर valid;
	अक्षर eic[18];
पूर्ण;

/**
 * sht21_temp_ticks_to_millicelsius() - convert raw temperature ticks to
 * milli celsius
 * @ticks: temperature ticks value received from sensor
 */
अटल अंतरभूत पूर्णांक sht21_temp_ticks_to_millicelsius(पूर्णांक ticks)
अणु
	ticks &= ~0x0003; /* clear status bits */
	/*
	 * Formula T = -46.85 + 175.72 * ST / 2^16 from data sheet 6.2,
	 * optimized क्रम पूर्णांकeger fixed poपूर्णांक (3 digits) arithmetic
	 */
	वापस ((21965 * ticks) >> 13) - 46850;
पूर्ण

/**
 * sht21_rh_ticks_to_per_cent_mille() - convert raw humidity ticks to
 * one-thousandths of a percent relative humidity
 * @ticks: humidity ticks value received from sensor
 */
अटल अंतरभूत पूर्णांक sht21_rh_ticks_to_per_cent_mille(पूर्णांक ticks)
अणु
	ticks &= ~0x0003; /* clear status bits */
	/*
	 * Formula RH = -6 + 125 * SRH / 2^16 from data sheet 6.1,
	 * optimized क्रम पूर्णांकeger fixed poपूर्णांक (3 digits) arithmetic
	 */
	वापस ((15625 * ticks) >> 13) - 6000;
पूर्ण

/**
 * sht21_update_measurements() - get updated measurements from device
 * @dev: device
 *
 * Returns 0 on success, अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक sht21_update_measurements(काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा sht21 *sht21 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = sht21->client;

	mutex_lock(&sht21->lock);
	/*
	 * Data sheet 2.4:
	 * SHT2x should not be active क्रम more than 10% of the समय - e.g.
	 * maximum two measurements per second at 12bit accuracy shall be made.
	 */
	अगर (समय_after(jअगरfies, sht21->last_update + HZ / 2) || !sht21->valid) अणु
		ret = i2c_smbus_पढ़ो_word_swapped(client,
						  SHT21_TRIG_T_MEASUREMENT_HM);
		अगर (ret < 0)
			जाओ out;
		sht21->temperature = sht21_temp_ticks_to_millicelsius(ret);
		ret = i2c_smbus_पढ़ो_word_swapped(client,
						  SHT21_TRIG_RH_MEASUREMENT_HM);
		अगर (ret < 0)
			जाओ out;
		sht21->humidity = sht21_rh_ticks_to_per_cent_mille(ret);
		sht21->last_update = jअगरfies;
		sht21->valid = 1;
	पूर्ण
out:
	mutex_unlock(&sht21->lock);

	वापस ret >= 0 ? 0 : ret;
पूर्ण

/**
 * sht21_show_temperature() - show temperature measurement value in sysfs
 * @dev: device
 * @attr: device attribute
 * @buf: sysfs buffer (PAGE_SIZE) where measurement values are written to
 *
 * Will be called on पढ़ो access to temp1_input sysfs attribute.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार sht21_temperature_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा sht21 *sht21 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sht21_update_measurements(dev);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", sht21->temperature);
पूर्ण

/**
 * sht21_show_humidity() - show humidity measurement value in sysfs
 * @dev: device
 * @attr: device attribute
 * @buf: sysfs buffer (PAGE_SIZE) where measurement values are written to
 *
 * Will be called on पढ़ो access to humidity1_input sysfs attribute.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार sht21_humidity_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sht21 *sht21 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = sht21_update_measurements(dev);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", sht21->humidity);
पूर्ण

अटल sमाप_प्रकार eic_पढ़ो(काष्ठा sht21 *sht21)
अणु
	काष्ठा i2c_client *client = sht21->client;
	u8 tx[2];
	u8 rx[8];
	u8 eic[8];
	काष्ठा i2c_msg msgs[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = 2,
			.buf = tx,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 8,
			.buf = rx,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	tx[0] = SHT21_READ_SNB_CMD1;
	tx[1] = SHT21_READ_SNB_CMD2;
	ret = i2c_transfer(client->adapter, msgs, 2);
	अगर (ret < 0)
		जाओ out;
	eic[2] = rx[0];
	eic[3] = rx[2];
	eic[4] = rx[4];
	eic[5] = rx[6];

	tx[0] = SHT21_READ_SNAC_CMD1;
	tx[1] = SHT21_READ_SNAC_CMD2;
	msgs[1].len = 6;
	ret = i2c_transfer(client->adapter, msgs, 2);
	अगर (ret < 0)
		जाओ out;
	eic[0] = rx[3];
	eic[1] = rx[4];
	eic[6] = rx[0];
	eic[7] = rx[1];

	ret = snम_लिखो(sht21->eic, माप(sht21->eic),
		       "%02x%02x%02x%02x%02x%02x%02x%02x\n",
		       eic[0], eic[1], eic[2], eic[3],
		       eic[4], eic[5], eic[6], eic[7]);
out:
	अगर (ret < 0)
		sht21->eic[0] = 0;

	वापस ret;
पूर्ण

/**
 * eic_show() - show Electronic Identअगरication Code in sysfs
 * @dev: device
 * @attr: device attribute
 * @buf: sysfs buffer (PAGE_SIZE) where EIC is written
 *
 * Will be called on पढ़ो access to eic sysfs attribute.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार eic_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा sht21 *sht21 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = माप(sht21->eic) - 1;
	mutex_lock(&sht21->lock);
	अगर (!sht21->eic[0])
		ret = eic_पढ़ो(sht21);
	अगर (ret > 0)
		स_नकल(buf, sht21->eic, ret);
	mutex_unlock(&sht21->lock);
	वापस ret;
पूर्ण

/* sysfs attributes */
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, sht21_temperature, 0);
अटल SENSOR_DEVICE_ATTR_RO(humidity1_input, sht21_humidity, 0);
अटल DEVICE_ATTR_RO(eic);

अटल काष्ठा attribute *sht21_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_humidity1_input.dev_attr.attr,
	&dev_attr_eic.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(sht21);

अटल पूर्णांक sht21_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा sht21 *sht21;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA)) अणु
		dev_err(&client->dev,
			"adapter does not support SMBus word transactions\n");
		वापस -ENODEV;
	पूर्ण

	sht21 = devm_kzalloc(dev, माप(*sht21), GFP_KERNEL);
	अगर (!sht21)
		वापस -ENOMEM;

	sht21->client = client;

	mutex_init(&sht21->lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   sht21, sht21_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/* Device ID table */
अटल स्थिर काष्ठा i2c_device_id sht21_id[] = अणु
	अणु "sht21", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sht21_id);

अटल काष्ठा i2c_driver sht21_driver = अणु
	.driver.name = "sht21",
	.probe_new   = sht21_probe,
	.id_table    = sht21_id,
पूर्ण;

module_i2c_driver(sht21_driver);

MODULE_AUTHOR("Urs Fleisch <urs.fleisch@sensirion.com>");
MODULE_DESCRIPTION("Sensirion SHT21 humidity and temperature sensor driver");
MODULE_LICENSE("GPL");
