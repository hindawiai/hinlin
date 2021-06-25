<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Honeywell HIH-6130/HIH-6131 humidity and temperature sensor driver
 *
 * Copyright (C) 2012 Iain Paton <ipaton0@gmail.com>
 *
 * heavily based on the sht21 driver
 * Copyright (C) 2010 Urs Fleisch <urs.fleisch@sensirion.com>
 *
 * Data sheets available (2012-06-22) at
 * http://sensing.honeywell.com/index.php?ci_id=3106&la_id=1&defId=44872
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
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>

/**
 * काष्ठा hih6130 - HIH-6130 device specअगरic data
 * @client: poपूर्णांकer to I2C client device
 * @lock: mutex to protect measurement values
 * @valid: only false beक्रमe first measurement is taken
 * @last_update: समय of last update (jअगरfies)
 * @temperature: cached temperature measurement value
 * @humidity: cached humidity measurement value
 * @ग_लिखो_length: length क्रम I2C measurement request
 */
काष्ठा hih6130 अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	bool valid;
	अचिन्हित दीर्घ last_update;
	पूर्णांक temperature;
	पूर्णांक humidity;
	माप_प्रकार ग_लिखो_length;
पूर्ण;

/**
 * hih6130_temp_ticks_to_millicelsius() - convert raw temperature ticks to
 * milli celsius
 * @ticks: temperature ticks value received from sensor
 */
अटल अंतरभूत पूर्णांक hih6130_temp_ticks_to_millicelsius(पूर्णांक ticks)
अणु
	ticks = ticks >> 2;
	/*
	 * from data sheet section 5.0
	 * Formula T = ( ticks / ( 2^14 - 2 ) ) * 165 -40
	 */
	वापस (DIV_ROUND_CLOSEST(ticks * 1650, 16382) - 400) * 100;
पूर्ण

/**
 * hih6130_rh_ticks_to_per_cent_mille() - convert raw humidity ticks to
 * one-thousandths of a percent relative humidity
 * @ticks: humidity ticks value received from sensor
 */
अटल अंतरभूत पूर्णांक hih6130_rh_ticks_to_per_cent_mille(पूर्णांक ticks)
अणु
	ticks &= ~0xC000; /* clear status bits */
	/*
	 * from data sheet section 4.0
	 * Formula RH = ( ticks / ( 2^14 -2 ) ) * 100
	 */
	वापस DIV_ROUND_CLOSEST(ticks * 1000, 16382) * 100;
पूर्ण

/**
 * hih6130_update_measurements() - get updated measurements from device
 * @dev: device
 *
 * Returns 0 on success, अन्यथा negative त्रुटि_सं.
 */
अटल पूर्णांक hih6130_update_measurements(काष्ठा device *dev)
अणु
	काष्ठा hih6130 *hih6130 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = hih6130->client;
	पूर्णांक ret = 0;
	पूर्णांक t;
	अचिन्हित अक्षर पंचांगp[4];
	काष्ठा i2c_msg msgs[1] = अणु
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = 4,
			.buf = पंचांगp,
		पूर्ण
	पूर्ण;

	mutex_lock(&hih6130->lock);

	/*
	 * While the measurement can be completed in ~40ms the sensor takes
	 * much दीर्घer to react to a change in बाह्यal conditions. How quickly
	 * it reacts depends on airflow and other factors outwith our control.
	 * The datasheet specअगरies maximum 'Response time' क्रम humidity at 8s
	 * and temperature at 30s under specअगरied conditions.
	 * We thereक्रमe choose to only पढ़ो the sensor at most once per second.
	 * This trades off poपूर्णांकless activity polling the sensor much faster
	 * than it can react against better response बार in conditions more
	 * favourable than specअगरied in the datasheet.
	 */
	अगर (समय_after(jअगरfies, hih6130->last_update + HZ) || !hih6130->valid) अणु

		/*
		 * Write to slave address to request a measurement.
		 * According with the datasheet it should be with no data, but
		 * क्रम प्रणालीs with I2C bus drivers that करो not allow zero
		 * length packets we ग_लिखो one dummy byte to allow sensor
		 * measurements on them.
		 */
		पंचांगp[0] = 0;
		ret = i2c_master_send(client, पंचांगp, hih6130->ग_लिखो_length);
		अगर (ret < 0)
			जाओ out;

		/* measurement cycle समय is ~36.65msec */
		msleep(40);

		ret = i2c_transfer(client->adapter, msgs, 1);
		अगर (ret < 0)
			जाओ out;

		अगर ((पंचांगp[0] & 0xC0) != 0) अणु
			dev_err(&client->dev, "Error while reading measurement result\n");
			ret = -EIO;
			जाओ out;
		पूर्ण

		t = (पंचांगp[0] << 8) + पंचांगp[1];
		hih6130->humidity = hih6130_rh_ticks_to_per_cent_mille(t);

		t = (पंचांगp[2] << 8) + पंचांगp[3];
		hih6130->temperature = hih6130_temp_ticks_to_millicelsius(t);

		hih6130->last_update = jअगरfies;
		hih6130->valid = true;
	पूर्ण
out:
	mutex_unlock(&hih6130->lock);

	वापस ret >= 0 ? 0 : ret;
पूर्ण

/**
 * hih6130_show_temperature() - show temperature measurement value in sysfs
 * @dev: device
 * @attr: device attribute
 * @buf: sysfs buffer (PAGE_SIZE) where measurement values are written to
 *
 * Will be called on पढ़ो access to temp1_input sysfs attribute.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार hih6130_temperature_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा hih6130 *hih6130 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = hih6130_update_measurements(dev);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", hih6130->temperature);
पूर्ण

/**
 * hih6130_show_humidity() - show humidity measurement value in sysfs
 * @dev: device
 * @attr: device attribute
 * @buf: sysfs buffer (PAGE_SIZE) where measurement values are written to
 *
 * Will be called on पढ़ो access to humidity1_input sysfs attribute.
 * Returns number of bytes written पूर्णांकo buffer, negative त्रुटि_सं on error.
 */
अटल sमाप_प्रकार hih6130_humidity_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hih6130 *hih6130 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = hih6130_update_measurements(dev);
	अगर (ret < 0)
		वापस ret;
	वापस प्र_लिखो(buf, "%d\n", hih6130->humidity);
पूर्ण

/* sysfs attributes */
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, hih6130_temperature, 0);
अटल SENSOR_DEVICE_ATTR_RO(humidity1_input, hih6130_humidity, 0);

अटल काष्ठा attribute *hih6130_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_humidity1_input.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(hih6130);

अटल पूर्णांक hih6130_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा hih6130 *hih6130;
	काष्ठा device *hwmon_dev;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "adapter does not support true I2C\n");
		वापस -ENODEV;
	पूर्ण

	hih6130 = devm_kzalloc(dev, माप(*hih6130), GFP_KERNEL);
	अगर (!hih6130)
		वापस -ENOMEM;

	hih6130->client = client;
	mutex_init(&hih6130->lock);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_QUICK))
		hih6130->ग_लिखो_length = 1;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   hih6130,
							   hih6130_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/* Device ID table */
अटल स्थिर काष्ठा i2c_device_id hih6130_id[] = अणु
	अणु "hih6130", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hih6130_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused hih6130_of_match[] = अणु
	अणु .compatible = "honeywell,hih6130", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hih6130_of_match);

अटल काष्ठा i2c_driver hih6130_driver = अणु
	.driver = अणु
		.name = "hih6130",
		.of_match_table = of_match_ptr(hih6130_of_match),
	पूर्ण,
	.probe_new   = hih6130_probe,
	.id_table    = hih6130_id,
पूर्ण;

module_i2c_driver(hih6130_driver);

MODULE_AUTHOR("Iain Paton <ipaton0@gmail.com>");
MODULE_DESCRIPTION("Honeywell HIH-6130 humidity and temperature sensor driver");
MODULE_LICENSE("GPL");
