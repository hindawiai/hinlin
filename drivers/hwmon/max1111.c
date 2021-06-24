<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max1111.c - +2.7V, Low-Power, Multichannel, Serial 8-bit ADCs
 *
 * Based on arch/arm/mach-pxa/corgi_ssp.c
 *
 * Copyright (C) 2004-2005 Riअक्षरd Purdie
 *
 * Copyright (C) 2008 Marvell International Ltd.
 *	Eric Miao <eric.miao@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>

क्रमागत chips अणु max1110, max1111, max1112, max1113 पूर्ण;

#घोषणा MAX1111_TX_BUF_SIZE	1
#घोषणा MAX1111_RX_BUF_SIZE	2

/* MAX1111 Commands */
#घोषणा MAX1111_CTRL_PD0      (1u << 0)
#घोषणा MAX1111_CTRL_PD1      (1u << 1)
#घोषणा MAX1111_CTRL_SGL      (1u << 2)
#घोषणा MAX1111_CTRL_UNI      (1u << 3)
#घोषणा MAX1110_CTRL_SEL_SH   (4)
#घोषणा MAX1111_CTRL_SEL_SH   (5)	/* NOTE: bit 4 is ignored */
#घोषणा MAX1111_CTRL_STR      (1u << 7)

काष्ठा max1111_data अणु
	काष्ठा spi_device	*spi;
	काष्ठा device		*hwmon_dev;
	काष्ठा spi_message	msg;
	काष्ठा spi_transfer	xfer[2];
	uपूर्णांक8_t tx_buf[MAX1111_TX_BUF_SIZE];
	uपूर्णांक8_t rx_buf[MAX1111_RX_BUF_SIZE];
	काष्ठा mutex		drvdata_lock;
	/* protect msg, xfer and buffers from multiple access */
	पूर्णांक			sel_sh;
	पूर्णांक			lsb;
पूर्ण;

अटल पूर्णांक max1111_पढ़ो(काष्ठा device *dev, पूर्णांक channel)
अणु
	काष्ठा max1111_data *data = dev_get_drvdata(dev);
	uपूर्णांक8_t v1, v2;
	पूर्णांक err;

	/* writing to drvdata काष्ठा is not thपढ़ो safe, रुको on mutex */
	mutex_lock(&data->drvdata_lock);

	data->tx_buf[0] = (channel << data->sel_sh) |
		MAX1111_CTRL_PD0 | MAX1111_CTRL_PD1 |
		MAX1111_CTRL_SGL | MAX1111_CTRL_UNI | MAX1111_CTRL_STR;

	err = spi_sync(data->spi, &data->msg);
	अगर (err < 0) अणु
		dev_err(dev, "spi_sync failed with %d\n", err);
		mutex_unlock(&data->drvdata_lock);
		वापस err;
	पूर्ण

	v1 = data->rx_buf[0];
	v2 = data->rx_buf[1];

	mutex_unlock(&data->drvdata_lock);

	अगर ((v1 & 0xc0) || (v2 & 0x3f))
		वापस -EINVAL;

	वापस (v1 << 2) | (v2 >> 6);
पूर्ण

#अगर_घोषित CONFIG_SHARPSL_PM
अटल काष्ठा max1111_data *the_max1111;

पूर्णांक max1111_पढ़ो_channel(पूर्णांक channel)
अणु
	अगर (!the_max1111 || !the_max1111->spi)
		वापस -ENODEV;

	वापस max1111_पढ़ो(&the_max1111->spi->dev, channel);
पूर्ण
EXPORT_SYMBOL(max1111_पढ़ो_channel);
#पूर्ण_अगर

/*
 * NOTE: SPI devices करो not have a शेष 'name' attribute, which is
 * likely to be used by hwmon applications to distinguish between
 * dअगरferent devices, explicitly add a name attribute here.
 */
अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", to_spi_device(dev)->modalias);
पूर्ण

अटल sमाप_प्रकार show_adc(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा max1111_data *data = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;
	पूर्णांक ret;

	ret = max1111_पढ़ो(dev, channel);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Assume the reference voltage to be 2.048V or 4.096V, with an 8-bit
	 * sample. The LSB weight is 8mV or 16mV depending on the chip type.
	 */
	वापस प्र_लिखो(buf, "%d\n", ret * data->lsb);
पूर्ण

#घोषणा MAX1111_ADC_ATTR(_id)		\
	SENSOR_DEVICE_ATTR(in##_id##_input, S_IRUGO, show_adc, शून्य, _id)

अटल DEVICE_ATTR_RO(name);
अटल MAX1111_ADC_ATTR(0);
अटल MAX1111_ADC_ATTR(1);
अटल MAX1111_ADC_ATTR(2);
अटल MAX1111_ADC_ATTR(3);
अटल MAX1111_ADC_ATTR(4);
अटल MAX1111_ADC_ATTR(5);
अटल MAX1111_ADC_ATTR(6);
अटल MAX1111_ADC_ATTR(7);

अटल काष्ठा attribute *max1111_attributes[] = अणु
	&dev_attr_name.attr,
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max1111_attr_group = अणु
	.attrs	= max1111_attributes,
पूर्ण;

अटल काष्ठा attribute *max1110_attributes[] = अणु
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max1110_attr_group = अणु
	.attrs	= max1110_attributes,
पूर्ण;

अटल पूर्णांक setup_transfer(काष्ठा max1111_data *data)
अणु
	काष्ठा spi_message *m;
	काष्ठा spi_transfer *x;

	m = &data->msg;
	x = &data->xfer[0];

	spi_message_init(m);

	x->tx_buf = &data->tx_buf[0];
	x->len = MAX1111_TX_BUF_SIZE;
	spi_message_add_tail(x, m);

	x++;
	x->rx_buf = &data->rx_buf[0];
	x->len = MAX1111_RX_BUF_SIZE;
	spi_message_add_tail(x, m);

	वापस 0;
पूर्ण

अटल पूर्णांक max1111_probe(काष्ठा spi_device *spi)
अणु
	क्रमागत chips chip = spi_get_device_id(spi)->driver_data;
	काष्ठा max1111_data *data;
	पूर्णांक err;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	err = spi_setup(spi);
	अगर (err < 0)
		वापस err;

	data = devm_kzalloc(&spi->dev, माप(काष्ठा max1111_data), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	चयन (chip) अणु
	हाल max1110:
		data->lsb = 8;
		data->sel_sh = MAX1110_CTRL_SEL_SH;
		अवरोध;
	हाल max1111:
		data->lsb = 8;
		data->sel_sh = MAX1111_CTRL_SEL_SH;
		अवरोध;
	हाल max1112:
		data->lsb = 16;
		data->sel_sh = MAX1110_CTRL_SEL_SH;
		अवरोध;
	हाल max1113:
		data->lsb = 16;
		data->sel_sh = MAX1111_CTRL_SEL_SH;
		अवरोध;
	पूर्ण
	err = setup_transfer(data);
	अगर (err)
		वापस err;

	mutex_init(&data->drvdata_lock);

	data->spi = spi;
	spi_set_drvdata(spi, data);

	err = sysfs_create_group(&spi->dev.kobj, &max1111_attr_group);
	अगर (err) अणु
		dev_err(&spi->dev, "failed to create attribute group\n");
		वापस err;
	पूर्ण
	अगर (chip == max1110 || chip == max1112) अणु
		err = sysfs_create_group(&spi->dev.kobj, &max1110_attr_group);
		अगर (err) अणु
			dev_err(&spi->dev,
				"failed to create extended attribute group\n");
			जाओ err_हटाओ;
		पूर्ण
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&spi->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		dev_err(&spi->dev, "failed to create hwmon device\n");
		err = PTR_ERR(data->hwmon_dev);
		जाओ err_हटाओ;
	पूर्ण

#अगर_घोषित CONFIG_SHARPSL_PM
	the_max1111 = data;
#पूर्ण_अगर
	वापस 0;

err_हटाओ:
	sysfs_हटाओ_group(&spi->dev.kobj, &max1110_attr_group);
	sysfs_हटाओ_group(&spi->dev.kobj, &max1111_attr_group);
	वापस err;
पूर्ण

अटल पूर्णांक max1111_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा max1111_data *data = spi_get_drvdata(spi);

#अगर_घोषित CONFIG_SHARPSL_PM
	the_max1111 = शून्य;
#पूर्ण_अगर
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&spi->dev.kobj, &max1110_attr_group);
	sysfs_हटाओ_group(&spi->dev.kobj, &max1111_attr_group);
	mutex_destroy(&data->drvdata_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id max1111_ids[] = अणु
	अणु "max1110", max1110 पूर्ण,
	अणु "max1111", max1111 पूर्ण,
	अणु "max1112", max1112 पूर्ण,
	अणु "max1113", max1113 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, max1111_ids);

अटल काष्ठा spi_driver max1111_driver = अणु
	.driver		= अणु
		.name	= "max1111",
	पूर्ण,
	.id_table	= max1111_ids,
	.probe		= max1111_probe,
	.हटाओ		= max1111_हटाओ,
पूर्ण;

module_spi_driver(max1111_driver);

MODULE_AUTHOR("Eric Miao <eric.miao@marvell.com>");
MODULE_DESCRIPTION("MAX1110/MAX1111/MAX1112/MAX1113 ADC Driver");
MODULE_LICENSE("GPL");
