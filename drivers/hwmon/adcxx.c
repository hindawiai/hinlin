<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * adcxx.c
 *
 * The adcxx4s is an AD converter family from National Semiconductor (NS).
 *
 * Copyright (c) 2008 Marc Pignat <marc.pignat@hevs.ch>
 *
 * The adcxx4s communicates with a host processor via an SPI/Microwire Bus
 * पूर्णांकerface. This driver supports the whole family of devices with name
 * ADC<bb><c>S<sss>, where
 * * bb is the resolution in number of bits (8, 10, 12)
 * * c is the number of channels (1, 2, 4, 8)
 * * sss is the maximum conversion speed (021 क्रम 200 kSPS, 051 क्रम 500 kSPS
 *   and 101 क्रम 1 MSPS)
 *
 * Complete datasheets are available at National's website here:
 * http://www.national.com/ds/DC/ADC<bb><c>S<sss>.pdf
 *
 * Handling of 8, 10 and 12 bits converters are the same, the
 * unavailable bits are 0 :)
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>

#घोषणा DRVNAME		"adcxx"

काष्ठा adcxx अणु
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;
	u32 channels;
	u32 reference; /* in millivolts */
पूर्ण;

/* sysfs hook function */
अटल sमाप_प्रकार adcxx_show(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा adcxx *adc = spi_get_drvdata(spi);
	u8 tx_buf[2];
	u8 rx_buf[2];
	पूर्णांक status;
	u32 value;

	अगर (mutex_lock_पूर्णांकerruptible(&adc->lock))
		वापस -ERESTARTSYS;

	अगर (adc->channels == 1) अणु
		status = spi_पढ़ो(spi, rx_buf, माप(rx_buf));
	पूर्ण अन्यथा अणु
		tx_buf[0] = attr->index << 3; /* other bits are करोn't care */
		status = spi_ग_लिखो_then_पढ़ो(spi, tx_buf, माप(tx_buf),
						rx_buf, माप(rx_buf));
	पूर्ण
	अगर (status < 0) अणु
		dev_warn(dev, "SPI synch. transfer failed with status %d\n",
				status);
		जाओ out;
	पूर्ण

	value = (rx_buf[0] << 8) + rx_buf[1];
	dev_dbg(dev, "raw value = 0x%x\n", value);

	value = value * adc->reference >> 12;
	status = प्र_लिखो(buf, "%d\n", value);
out:
	mutex_unlock(&adc->lock);
	वापस status;
पूर्ण

अटल sमाप_प्रकार adcxx_min_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	/* The minimum reference is 0 क्रम this chip family */
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल sमाप_प्रकार adcxx_max_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा adcxx *adc = spi_get_drvdata(spi);
	u32 reference;

	अगर (mutex_lock_पूर्णांकerruptible(&adc->lock))
		वापस -ERESTARTSYS;

	reference = adc->reference;

	mutex_unlock(&adc->lock);

	वापस प्र_लिखो(buf, "%d\n", reference);
पूर्ण

अटल sमाप_प्रकार adcxx_max_store(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा adcxx *adc = spi_get_drvdata(spi);
	अचिन्हित दीर्घ value;

	अगर (kम_से_अदीर्घ(buf, 10, &value))
		वापस -EINVAL;

	अगर (mutex_lock_पूर्णांकerruptible(&adc->lock))
		वापस -ERESTARTSYS;

	adc->reference = value;

	mutex_unlock(&adc->lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार adcxx_name_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", to_spi_device(dev)->modalias);
पूर्ण

अटल काष्ठा sensor_device_attribute ad_input[] = अणु
	SENSOR_ATTR_RO(name, adcxx_name, 0),
	SENSOR_ATTR_RO(in_min, adcxx_min, 0),
	SENSOR_ATTR_RW(in_max, adcxx_max, 0),
	SENSOR_ATTR_RO(in0_input, adcxx, 0),
	SENSOR_ATTR_RO(in1_input, adcxx, 1),
	SENSOR_ATTR_RO(in2_input, adcxx, 2),
	SENSOR_ATTR_RO(in3_input, adcxx, 3),
	SENSOR_ATTR_RO(in4_input, adcxx, 4),
	SENSOR_ATTR_RO(in5_input, adcxx, 5),
	SENSOR_ATTR_RO(in6_input, adcxx, 6),
	SENSOR_ATTR_RO(in7_input, adcxx, 7),
पूर्ण;

/*----------------------------------------------------------------------*/

अटल पूर्णांक adcxx_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक channels = spi_get_device_id(spi)->driver_data;
	काष्ठा adcxx *adc;
	पूर्णांक status;
	पूर्णांक i;

	adc = devm_kzalloc(&spi->dev, माप(*adc), GFP_KERNEL);
	अगर (!adc)
		वापस -ENOMEM;

	/* set a शेष value क्रम the reference */
	adc->reference = 3300;
	adc->channels = channels;
	mutex_init(&adc->lock);

	mutex_lock(&adc->lock);

	spi_set_drvdata(spi, adc);

	क्रम (i = 0; i < 3 + adc->channels; i++) अणु
		status = device_create_file(&spi->dev, &ad_input[i].dev_attr);
		अगर (status) अणु
			dev_err(&spi->dev, "device_create_file failed.\n");
			जाओ out_err;
		पूर्ण
	पूर्ण

	adc->hwmon_dev = hwmon_device_रेजिस्टर(&spi->dev);
	अगर (IS_ERR(adc->hwmon_dev)) अणु
		dev_err(&spi->dev, "hwmon_device_register failed.\n");
		status = PTR_ERR(adc->hwmon_dev);
		जाओ out_err;
	पूर्ण

	mutex_unlock(&adc->lock);
	वापस 0;

out_err:
	क्रम (i--; i >= 0; i--)
		device_हटाओ_file(&spi->dev, &ad_input[i].dev_attr);

	mutex_unlock(&adc->lock);
	वापस status;
पूर्ण

अटल पूर्णांक adcxx_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा adcxx *adc = spi_get_drvdata(spi);
	पूर्णांक i;

	mutex_lock(&adc->lock);
	hwmon_device_unरेजिस्टर(adc->hwmon_dev);
	क्रम (i = 0; i < 3 + adc->channels; i++)
		device_हटाओ_file(&spi->dev, &ad_input[i].dev_attr);

	mutex_unlock(&adc->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adcxx_ids[] = अणु
	अणु "adcxx1s", 1 पूर्ण,
	अणु "adcxx2s", 2 पूर्ण,
	अणु "adcxx4s", 4 पूर्ण,
	अणु "adcxx8s", 8 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, adcxx_ids);

अटल काष्ठा spi_driver adcxx_driver = अणु
	.driver = अणु
		.name	= "adcxx",
	पूर्ण,
	.id_table = adcxx_ids,
	.probe	= adcxx_probe,
	.हटाओ	= adcxx_हटाओ,
पूर्ण;

module_spi_driver(adcxx_driver);

MODULE_AUTHOR("Marc Pignat");
MODULE_DESCRIPTION("National Semiconductor adcxx8sxxx Linux driver");
MODULE_LICENSE("GPL");
