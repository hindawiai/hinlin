<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Capella Microप्रणालीs Inc.
 * Author: Kevin Tsai <ktsai@capellamicro.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/init.h>

/* Registers Address */
#घोषणा CM32181_REG_ADDR_CMD		0x00
#घोषणा CM32181_REG_ADDR_WH		0x01
#घोषणा CM32181_REG_ADDR_WL		0x02
#घोषणा CM32181_REG_ADDR_TEST		0x03
#घोषणा CM32181_REG_ADDR_ALS		0x04
#घोषणा CM32181_REG_ADDR_STATUS		0x06
#घोषणा CM32181_REG_ADDR_ID		0x07

/* Number of Configurable Registers */
#घोषणा CM32181_CONF_REG_NUM		4

/* CMD रेजिस्टर */
#घोषणा CM32181_CMD_ALS_DISABLE		BIT(0)
#घोषणा CM32181_CMD_ALS_INT_EN		BIT(1)
#घोषणा CM32181_CMD_ALS_THRES_WINDOW	BIT(2)

#घोषणा CM32181_CMD_ALS_PERS_SHIFT	4
#घोषणा CM32181_CMD_ALS_PERS_MASK	(0x03 << CM32181_CMD_ALS_PERS_SHIFT)
#घोषणा CM32181_CMD_ALS_PERS_DEFAULT	(0x01 << CM32181_CMD_ALS_PERS_SHIFT)

#घोषणा CM32181_CMD_ALS_IT_SHIFT	6
#घोषणा CM32181_CMD_ALS_IT_MASK		(0x0F << CM32181_CMD_ALS_IT_SHIFT)
#घोषणा CM32181_CMD_ALS_IT_DEFAULT	(0x00 << CM32181_CMD_ALS_IT_SHIFT)

#घोषणा CM32181_CMD_ALS_SM_SHIFT	11
#घोषणा CM32181_CMD_ALS_SM_MASK		(0x03 << CM32181_CMD_ALS_SM_SHIFT)
#घोषणा CM32181_CMD_ALS_SM_DEFAULT	(0x01 << CM32181_CMD_ALS_SM_SHIFT)

#घोषणा CM32181_LUX_PER_BIT		500	/* ALS_SM=01 IT=800ms */
#घोषणा CM32181_LUX_PER_BIT_RESOLUTION	100000
#घोषणा CM32181_LUX_PER_BIT_BASE_IT	800000	/* Based on IT=800ms */
#घोषणा CM32181_CALIBSCALE_DEFAULT	100000
#घोषणा CM32181_CALIBSCALE_RESOLUTION	100000

#घोषणा SMBUS_ALERT_RESPONSE_ADDRESS	0x0c

/* CPM0 Index 0: device-id (3218 or 32181), 1: Unknown, 2: init_regs_biपंचांगap */
#घोषणा CPM0_REGS_BITMAP		2
#घोषणा CPM0_HEADER_SIZE		3

/* CPM1 Index 0: lux_per_bit, 1: calibscale, 2: resolution (100000) */
#घोषणा CPM1_LUX_PER_BIT		0
#घोषणा CPM1_CALIBSCALE			1
#घोषणा CPM1_SIZE			3

/* CM3218 Family */
अटल स्थिर पूर्णांक cm3218_als_it_bits[] = अणु 0, 1, 2, 3 पूर्ण;
अटल स्थिर पूर्णांक cm3218_als_it_values[] = अणु 100000, 200000, 400000, 800000 पूर्ण;

/* CM32181 Family */
अटल स्थिर पूर्णांक cm32181_als_it_bits[] = अणु 12, 8, 0, 1, 2, 3 पूर्ण;
अटल स्थिर पूर्णांक cm32181_als_it_values[] = अणु
	25000, 50000, 100000, 200000, 400000, 800000
पूर्ण;

काष्ठा cm32181_chip अणु
	काष्ठा i2c_client *client;
	काष्ठा device *dev;
	काष्ठा mutex lock;
	u16 conf_regs[CM32181_CONF_REG_NUM];
	अचिन्हित दीर्घ init_regs_biपंचांगap;
	पूर्णांक calibscale;
	पूर्णांक lux_per_bit;
	पूर्णांक lux_per_bit_base_it;
	पूर्णांक num_als_it;
	स्थिर पूर्णांक *als_it_bits;
	स्थिर पूर्णांक *als_it_values;
पूर्ण;

अटल पूर्णांक cm32181_पढ़ो_als_it(काष्ठा cm32181_chip *cm32181, पूर्णांक *val2);

#अगर_घोषित CONFIG_ACPI
/**
 * cm32181_acpi_get_cpm() - Get CPM object from ACPI
 * @dev:	poपूर्णांकer of काष्ठा device.
 * @obj_name:	poपूर्णांकer of ACPI object name.
 * @values:	poपूर्णांकer of array क्रम वापस elements.
 * @count:	maximum size of वापस array.
 *
 * Convert ACPI CPM table to array.
 *
 * Return: -ENODEV क्रम fail.  Otherwise is number of elements.
 */
अटल पूर्णांक cm32181_acpi_get_cpm(काष्ठा device *dev, अक्षर *obj_name,
				u64 *values, पूर्णांक count)
अणु
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *cpm, *elem;
	acpi_handle handle;
	acpi_status status;
	पूर्णांक i;

	handle = ACPI_HANDLE(dev);
	अगर (!handle)
		वापस -ENODEV;

	status = acpi_evaluate_object(handle, obj_name, शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "object %s not found\n", obj_name);
		वापस -ENODEV;
	पूर्ण

	cpm = buffer.poपूर्णांकer;
	अगर (cpm->package.count > count)
		dev_warn(dev, "%s table contains %u values, only using first %d values\n",
			 obj_name, cpm->package.count, count);

	count = min_t(पूर्णांक, cpm->package.count, count);
	क्रम (i = 0; i < count; i++) अणु
		elem = &(cpm->package.elements[i]);
		values[i] = elem->पूर्णांकeger.value;
	पूर्ण

	kमुक्त(buffer.poपूर्णांकer);

	वापस count;
पूर्ण

अटल व्योम cm32181_acpi_parse_cpm_tables(काष्ठा cm32181_chip *cm32181)
अणु
	u64 vals[CPM0_HEADER_SIZE + CM32181_CONF_REG_NUM];
	काष्ठा device *dev = cm32181->dev;
	पूर्णांक i, count;

	count = cm32181_acpi_get_cpm(dev, "CPM0", vals, ARRAY_SIZE(vals));
	अगर (count <= CPM0_HEADER_SIZE)
		वापस;

	count -= CPM0_HEADER_SIZE;

	cm32181->init_regs_biपंचांगap = vals[CPM0_REGS_BITMAP];
	cm32181->init_regs_biपंचांगap &= GENMASK(count - 1, 0);
	क्रम_each_set_bit(i, &cm32181->init_regs_biपंचांगap, count)
		cm32181->conf_regs[i] =	vals[CPM0_HEADER_SIZE + i];

	count = cm32181_acpi_get_cpm(dev, "CPM1", vals, ARRAY_SIZE(vals));
	अगर (count != CPM1_SIZE)
		वापस;

	cm32181->lux_per_bit = vals[CPM1_LUX_PER_BIT];

	/* Check क्रम uncalibrated devices */
	अगर (vals[CPM1_CALIBSCALE] == CM32181_CALIBSCALE_DEFAULT)
		वापस;

	cm32181->calibscale = vals[CPM1_CALIBSCALE];
	/* CPM1 lux_per_bit is क्रम the current it value */
	cm32181_पढ़ो_als_it(cm32181, &cm32181->lux_per_bit_base_it);
पूर्ण
#अन्यथा
अटल व्योम cm32181_acpi_parse_cpm_tables(काष्ठा cm32181_chip *cm32181)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

/**
 * cm32181_reg_init() - Initialize CM32181 रेजिस्टरs
 * @cm32181:	poपूर्णांकer of काष्ठा cm32181.
 *
 * Initialize CM32181 ambient light sensor रेजिस्टर to शेष values.
 *
 * Return: 0 क्रम success; otherwise क्रम error code.
 */
अटल पूर्णांक cm32181_reg_init(काष्ठा cm32181_chip *cm32181)
अणु
	काष्ठा i2c_client *client = cm32181->client;
	पूर्णांक i;
	s32 ret;

	ret = i2c_smbus_पढ़ो_word_data(client, CM32181_REG_ADDR_ID);
	अगर (ret < 0)
		वापस ret;

	/* check device ID */
	चयन (ret & 0xFF) अणु
	हाल 0x18: /* CM3218 */
		cm32181->num_als_it = ARRAY_SIZE(cm3218_als_it_bits);
		cm32181->als_it_bits = cm3218_als_it_bits;
		cm32181->als_it_values = cm3218_als_it_values;
		अवरोध;
	हाल 0x81: /* CM32181 */
	हाल 0x82: /* CM32182, fully compat. with CM32181 */
		cm32181->num_als_it = ARRAY_SIZE(cm32181_als_it_bits);
		cm32181->als_it_bits = cm32181_als_it_bits;
		cm32181->als_it_values = cm32181_als_it_values;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	/* Default Values */
	cm32181->conf_regs[CM32181_REG_ADDR_CMD] =
			CM32181_CMD_ALS_IT_DEFAULT | CM32181_CMD_ALS_SM_DEFAULT;
	cm32181->init_regs_biपंचांगap = BIT(CM32181_REG_ADDR_CMD);
	cm32181->calibscale = CM32181_CALIBSCALE_DEFAULT;
	cm32181->lux_per_bit = CM32181_LUX_PER_BIT;
	cm32181->lux_per_bit_base_it = CM32181_LUX_PER_BIT_BASE_IT;

	अगर (ACPI_HANDLE(cm32181->dev))
		cm32181_acpi_parse_cpm_tables(cm32181);

	/* Initialize रेजिस्टरs*/
	क्रम_each_set_bit(i, &cm32181->init_regs_biपंचांगap, CM32181_CONF_REG_NUM) अणु
		ret = i2c_smbus_ग_लिखो_word_data(client, i,
						cm32181->conf_regs[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  cm32181_पढ़ो_als_it() - Get sensor पूर्णांकegration समय (ms)
 *  @cm32181:	poपूर्णांकer of काष्ठा cm32181
 *  @val2:	poपूर्णांकer of पूर्णांक to load the als_it value.
 *
 *  Report the current पूर्णांकegration समय in milliseconds.
 *
 *  Return: IIO_VAL_INT_PLUS_MICRO क्रम success, otherwise -EINVAL.
 */
अटल पूर्णांक cm32181_पढ़ो_als_it(काष्ठा cm32181_chip *cm32181, पूर्णांक *val2)
अणु
	u16 als_it;
	पूर्णांक i;

	als_it = cm32181->conf_regs[CM32181_REG_ADDR_CMD];
	als_it &= CM32181_CMD_ALS_IT_MASK;
	als_it >>= CM32181_CMD_ALS_IT_SHIFT;
	क्रम (i = 0; i < cm32181->num_als_it; i++) अणु
		अगर (als_it == cm32181->als_it_bits[i]) अणु
			*val2 = cm32181->als_it_values[i];
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * cm32181_ग_लिखो_als_it() - Write sensor पूर्णांकegration समय
 * @cm32181:	poपूर्णांकer of काष्ठा cm32181.
 * @val:	पूर्णांकegration समय by millisecond.
 *
 * Convert पूर्णांकegration समय (ms) to sensor value.
 *
 * Return: i2c_smbus_ग_लिखो_word_data command वापस value.
 */
अटल पूर्णांक cm32181_ग_लिखो_als_it(काष्ठा cm32181_chip *cm32181, पूर्णांक val)
अणु
	काष्ठा i2c_client *client = cm32181->client;
	u16 als_it;
	पूर्णांक ret, i, n;

	n = cm32181->num_als_it;
	क्रम (i = 0; i < n; i++)
		अगर (val <= cm32181->als_it_values[i])
			अवरोध;
	अगर (i >= n)
		i = n - 1;

	als_it = cm32181->als_it_bits[i];
	als_it <<= CM32181_CMD_ALS_IT_SHIFT;

	mutex_lock(&cm32181->lock);
	cm32181->conf_regs[CM32181_REG_ADDR_CMD] &=
		~CM32181_CMD_ALS_IT_MASK;
	cm32181->conf_regs[CM32181_REG_ADDR_CMD] |=
		als_it;
	ret = i2c_smbus_ग_लिखो_word_data(client, CM32181_REG_ADDR_CMD,
			cm32181->conf_regs[CM32181_REG_ADDR_CMD]);
	mutex_unlock(&cm32181->lock);

	वापस ret;
पूर्ण

/**
 * cm32181_get_lux() - report current lux value
 * @cm32181:	poपूर्णांकer of काष्ठा cm32181.
 *
 * Convert sensor raw data to lux.  It depends on पूर्णांकegration
 * समय and calibscale variable.
 *
 * Return: Positive value is lux, otherwise is error code.
 */
अटल पूर्णांक cm32181_get_lux(काष्ठा cm32181_chip *cm32181)
अणु
	काष्ठा i2c_client *client = cm32181->client;
	पूर्णांक ret;
	पूर्णांक als_it;
	u64 lux;

	ret = cm32181_पढ़ो_als_it(cm32181, &als_it);
	अगर (ret < 0)
		वापस -EINVAL;

	lux = cm32181->lux_per_bit;
	lux *= cm32181->lux_per_bit_base_it;
	lux = भाग_u64(lux, als_it);

	ret = i2c_smbus_पढ़ो_word_data(client, CM32181_REG_ADDR_ALS);
	अगर (ret < 0)
		वापस ret;

	lux *= ret;
	lux *= cm32181->calibscale;
	lux = भाग_u64(lux, CM32181_CALIBSCALE_RESOLUTION);
	lux = भाग_u64(lux, CM32181_LUX_PER_BIT_RESOLUTION);

	अगर (lux > 0xFFFF)
		lux = 0xFFFF;

	वापस lux;
पूर्ण

अटल पूर्णांक cm32181_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cm32181_chip *cm32181 = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = cm32181_get_lux(cm32181);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		*val = cm32181->calibscale;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		ret = cm32181_पढ़ो_als_it(cm32181, val2);
		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cm32181_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा cm32181_chip *cm32181 = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		cm32181->calibscale = val;
		वापस val;
	हाल IIO_CHAN_INFO_INT_TIME:
		ret = cm32181_ग_लिखो_als_it(cm32181, val2);
		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * cm32181_get_it_available() - Get available ALS IT value
 * @dev:	poपूर्णांकer of काष्ठा device.
 * @attr:	poपूर्णांकer of काष्ठा device_attribute.
 * @buf:	poपूर्णांकer of वापस string buffer.
 *
 * Display the available पूर्णांकegration समय values by millisecond.
 *
 * Return: string length.
 */
अटल sमाप_प्रकार cm32181_get_it_available(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cm32181_chip *cm32181 = iio_priv(dev_to_iio_dev(dev));
	पूर्णांक i, n, len;

	n = cm32181->num_als_it;
	क्रम (i = 0, len = 0; i < n; i++)
		len += प्र_लिखो(buf + len, "0.%06u ", cm32181->als_it_values[i]);
	वापस len + प्र_लिखो(buf + len, "\n");
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec cm32181_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_PROCESSED) |
			BIT(IIO_CHAN_INFO_CALIBSCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण
पूर्ण;

अटल IIO_DEVICE_ATTR(in_illuminance_पूर्णांकegration_समय_available,
			S_IRUGO, cm32181_get_it_available, शून्य, 0);

अटल काष्ठा attribute *cm32181_attributes[] = अणु
	&iio_dev_attr_in_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cm32181_attribute_group = अणु
	.attrs = cm32181_attributes
पूर्ण;

अटल स्थिर काष्ठा iio_info cm32181_info = अणु
	.पढ़ो_raw		= &cm32181_पढ़ो_raw,
	.ग_लिखो_raw		= &cm32181_ग_लिखो_raw,
	.attrs			= &cm32181_attribute_group,
पूर्ण;

अटल पूर्णांक cm32181_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा cm32181_chip *cm32181;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*cm32181));
	अगर (!indio_dev)
		वापस -ENOMEM;

	/*
	 * Some ACPI प्रणालीs list 2 I2C resources क्रम the CM3218 sensor, the
	 * SMBus Alert Response Address (ARA, 0x0c) and the actual I2C address.
	 * Detect this and take the following step to deal with it:
	 * 1. When a SMBus Alert capable sensor has an Alert निश्चितed, it will
	 *    not respond on its actual I2C address. Read a byte from the ARA
	 *    to clear any pending Alerts.
	 * 2. Create a "dummy" client क्रम the actual I2C address and
	 *    use that client to communicate with the sensor.
	 */
	अगर (ACPI_HANDLE(dev) && client->addr == SMBUS_ALERT_RESPONSE_ADDRESS) अणु
		काष्ठा i2c_board_info board_info = अणु .type = "dummy" पूर्ण;

		i2c_smbus_पढ़ो_byte(client);

		client = i2c_acpi_new_device(dev, 1, &board_info);
		अगर (IS_ERR(client))
			वापस PTR_ERR(client);
	पूर्ण

	cm32181 = iio_priv(indio_dev);
	cm32181->client = client;
	cm32181->dev = dev;

	mutex_init(&cm32181->lock);
	indio_dev->channels = cm32181_channels;
	indio_dev->num_channels = ARRAY_SIZE(cm32181_channels);
	indio_dev->info = &cm32181_info;
	indio_dev->name = dev_name(dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = cm32181_reg_init(cm32181);
	अगर (ret) अणु
		dev_err(dev, "%s: register init failed\n", __func__);
		वापस ret;
	पूर्ण

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret) अणु
		dev_err(dev, "%s: regist device failed\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cm32181_of_match[] = अणु
	अणु .compatible = "capella,cm3218" पूर्ण,
	अणु .compatible = "capella,cm32181" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cm32181_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cm32181_acpi_match[] = अणु
	अणु "CPLM3218", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cm32181_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver cm32181_driver = अणु
	.driver = अणु
		.name	= "cm32181",
		.acpi_match_table = ACPI_PTR(cm32181_acpi_match),
		.of_match_table = cm32181_of_match,
	पूर्ण,
	.probe_new	= cm32181_probe,
पूर्ण;

module_i2c_driver(cm32181_driver);

MODULE_AUTHOR("Kevin Tsai <ktsai@capellamicro.com>");
MODULE_DESCRIPTION("CM32181 ambient light sensor driver");
MODULE_LICENSE("GPL");
