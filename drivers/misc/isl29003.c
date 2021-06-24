<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  isl29003.c - Linux kernel module क्रम
 * 	Intersil ISL29003 ambient light sensor
 *
 *  See file:Documentation/misc-devices/isl29003.rst
 *
 *  Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 *
 *  Based on code written by
 *  	Roकरोlfo Giometti <giometti@linux.it>
 *  	Eurotech S.p.A. <info@eurotech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>

#घोषणा ISL29003_DRV_NAME	"isl29003"
#घोषणा DRIVER_VERSION		"1.0"

#घोषणा ISL29003_REG_COMMAND		0x00
#घोषणा ISL29003_ADC_ENABLED		(1 << 7)
#घोषणा ISL29003_ADC_PD			(1 << 6)
#घोषणा ISL29003_TIMING_INT		(1 << 5)
#घोषणा ISL29003_MODE_SHIFT		(2)
#घोषणा ISL29003_MODE_MASK		(0x3 << ISL29003_MODE_SHIFT)
#घोषणा ISL29003_RES_SHIFT		(0)
#घोषणा ISL29003_RES_MASK		(0x3 << ISL29003_RES_SHIFT)

#घोषणा ISL29003_REG_CONTROL		0x01
#घोषणा ISL29003_INT_FLG		(1 << 5)
#घोषणा ISL29003_RANGE_SHIFT		(2)
#घोषणा ISL29003_RANGE_MASK		(0x3 << ISL29003_RANGE_SHIFT)
#घोषणा ISL29003_INT_PERSISTS_SHIFT	(0)
#घोषणा ISL29003_INT_PERSISTS_MASK	(0xf << ISL29003_INT_PERSISTS_SHIFT)

#घोषणा ISL29003_REG_IRQ_THRESH_HI	0x02
#घोषणा ISL29003_REG_IRQ_THRESH_LO	0x03
#घोषणा ISL29003_REG_LSB_SENSOR		0x04
#घोषणा ISL29003_REG_MSB_SENSOR		0x05
#घोषणा ISL29003_REG_LSB_TIMER		0x06
#घोषणा ISL29003_REG_MSB_TIMER		0x07

#घोषणा ISL29003_NUM_CACHABLE_REGS	4

काष्ठा isl29003_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 reg_cache[ISL29003_NUM_CACHABLE_REGS];
	u8 घातer_state_beक्रमe_suspend;
पूर्ण;

अटल पूर्णांक gain_range[] = अणु
	1000, 4000, 16000, 64000
पूर्ण;

/*
 * रेजिस्टर access helpers
 */

अटल पूर्णांक __isl29003_पढ़ो_reg(काष्ठा i2c_client *client,
			       u32 reg, u8 mask, u8 shअगरt)
अणु
	काष्ठा isl29003_data *data = i2c_get_clientdata(client);

	वापस (data->reg_cache[reg] & mask) >> shअगरt;
पूर्ण

अटल पूर्णांक __isl29003_ग_लिखो_reg(काष्ठा i2c_client *client,
				u32 reg, u8 mask, u8 shअगरt, u8 val)
अणु
	काष्ठा isl29003_data *data = i2c_get_clientdata(client);
	पूर्णांक ret = 0;
	u8 पंचांगp;

	अगर (reg >= ISL29003_NUM_CACHABLE_REGS)
		वापस -EINVAL;

	mutex_lock(&data->lock);

	पंचांगp = data->reg_cache[reg];
	पंचांगp &= ~mask;
	पंचांगp |= val << shअगरt;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, पंचांगp);
	अगर (!ret)
		data->reg_cache[reg] = पंचांगp;

	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

/*
 * पूर्णांकernally used functions
 */

/* range */
अटल पूर्णांक isl29003_get_range(काष्ठा i2c_client *client)
अणु
	वापस __isl29003_पढ़ो_reg(client, ISL29003_REG_CONTROL,
		ISL29003_RANGE_MASK, ISL29003_RANGE_SHIFT);
पूर्ण

अटल पूर्णांक isl29003_set_range(काष्ठा i2c_client *client, पूर्णांक range)
अणु
	वापस __isl29003_ग_लिखो_reg(client, ISL29003_REG_CONTROL,
		ISL29003_RANGE_MASK, ISL29003_RANGE_SHIFT, range);
पूर्ण

/* resolution */
अटल पूर्णांक isl29003_get_resolution(काष्ठा i2c_client *client)
अणु
	वापस __isl29003_पढ़ो_reg(client, ISL29003_REG_COMMAND,
		ISL29003_RES_MASK, ISL29003_RES_SHIFT);
पूर्ण

अटल पूर्णांक isl29003_set_resolution(काष्ठा i2c_client *client, पूर्णांक res)
अणु
	वापस __isl29003_ग_लिखो_reg(client, ISL29003_REG_COMMAND,
		ISL29003_RES_MASK, ISL29003_RES_SHIFT, res);
पूर्ण

/* mode */
अटल पूर्णांक isl29003_get_mode(काष्ठा i2c_client *client)
अणु
	वापस __isl29003_पढ़ो_reg(client, ISL29003_REG_COMMAND,
		ISL29003_MODE_MASK, ISL29003_MODE_SHIFT);
पूर्ण

अटल पूर्णांक isl29003_set_mode(काष्ठा i2c_client *client, पूर्णांक mode)
अणु
	वापस __isl29003_ग_लिखो_reg(client, ISL29003_REG_COMMAND,
		ISL29003_MODE_MASK, ISL29003_MODE_SHIFT, mode);
पूर्ण

/* घातer_state */
अटल पूर्णांक isl29003_set_घातer_state(काष्ठा i2c_client *client, पूर्णांक state)
अणु
	वापस __isl29003_ग_लिखो_reg(client, ISL29003_REG_COMMAND,
				ISL29003_ADC_ENABLED | ISL29003_ADC_PD, 0,
				state ? ISL29003_ADC_ENABLED : ISL29003_ADC_PD);
पूर्ण

अटल पूर्णांक isl29003_get_घातer_state(काष्ठा i2c_client *client)
अणु
	काष्ठा isl29003_data *data = i2c_get_clientdata(client);
	u8 cmdreg = data->reg_cache[ISL29003_REG_COMMAND];

	वापस ~cmdreg & ISL29003_ADC_PD;
पूर्ण

अटल पूर्णांक isl29003_get_adc_value(काष्ठा i2c_client *client)
अणु
	काष्ठा isl29003_data *data = i2c_get_clientdata(client);
	पूर्णांक lsb, msb, range, bitdepth;

	mutex_lock(&data->lock);
	lsb = i2c_smbus_पढ़ो_byte_data(client, ISL29003_REG_LSB_SENSOR);

	अगर (lsb < 0) अणु
		mutex_unlock(&data->lock);
		वापस lsb;
	पूर्ण

	msb = i2c_smbus_पढ़ो_byte_data(client, ISL29003_REG_MSB_SENSOR);
	mutex_unlock(&data->lock);

	अगर (msb < 0)
		वापस msb;

	range = isl29003_get_range(client);
	bitdepth = (4 - isl29003_get_resolution(client)) * 4;
	वापस (((msb << 8) | lsb) * gain_range[range]) >> bitdepth;
पूर्ण

/*
 * sysfs layer
 */

/* range */
अटल sमाप_प्रकार isl29003_show_range(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस प्र_लिखो(buf, "%i\n", isl29003_get_range(client));
पूर्ण

अटल sमाप_प्रकार isl29003_store_range(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 3)
		वापस -EINVAL;

	ret = isl29003_set_range(client, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(range, S_IWUSR | S_IRUGO,
		   isl29003_show_range, isl29003_store_range);


/* resolution */
अटल sमाप_प्रकार isl29003_show_resolution(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस प्र_लिखो(buf, "%d\n", isl29003_get_resolution(client));
पूर्ण

अटल sमाप_प्रकार isl29003_store_resolution(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 3)
		वापस -EINVAL;

	ret = isl29003_set_resolution(client, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(resolution, S_IWUSR | S_IRUGO,
		   isl29003_show_resolution, isl29003_store_resolution);

/* mode */
अटल sमाप_प्रकार isl29003_show_mode(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस प्र_लिखो(buf, "%d\n", isl29003_get_mode(client));
पूर्ण

अटल sमाप_प्रकार isl29003_store_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 2)
		वापस -EINVAL;

	ret = isl29003_set_mode(client, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(mode, S_IWUSR | S_IRUGO,
		   isl29003_show_mode, isl29003_store_mode);


/* घातer state */
अटल sमाप_प्रकार isl29003_show_घातer_state(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	वापस प्र_लिखो(buf, "%d\n", isl29003_get_घातer_state(client));
पूर्ण

अटल sमाप_प्रकार isl29003_store_घातer_state(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 1)
		वापस -EINVAL;

	ret = isl29003_set_घातer_state(client, val);
	वापस ret ? ret : count;
पूर्ण

अटल DEVICE_ATTR(घातer_state, S_IWUSR | S_IRUGO,
		   isl29003_show_घातer_state, isl29003_store_घातer_state);


/* lux */
अटल sमाप_प्रकार isl29003_show_lux(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	/* No LUX data अगर not operational */
	अगर (!isl29003_get_घातer_state(client))
		वापस -EBUSY;

	वापस प्र_लिखो(buf, "%d\n", isl29003_get_adc_value(client));
पूर्ण

अटल DEVICE_ATTR(lux, S_IRUGO, isl29003_show_lux, शून्य);

अटल काष्ठा attribute *isl29003_attributes[] = अणु
	&dev_attr_range.attr,
	&dev_attr_resolution.attr,
	&dev_attr_mode.attr,
	&dev_attr_घातer_state.attr,
	&dev_attr_lux.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl29003_attr_group = अणु
	.attrs = isl29003_attributes,
पूर्ण;

अटल पूर्णांक isl29003_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा isl29003_data *data = i2c_get_clientdata(client);
	पूर्णांक i;

	/* पढ़ो all the रेजिस्टरs once to fill the cache.
	 * अगर one of the पढ़ोs fails, we consider the init failed */
	क्रम (i = 0; i < ARRAY_SIZE(data->reg_cache); i++) अणु
		पूर्णांक v = i2c_smbus_पढ़ो_byte_data(client, i);

		अगर (v < 0)
			वापस -ENODEV;

		data->reg_cache[i] = v;
	पूर्ण

	/* set शेषs */
	isl29003_set_range(client, 0);
	isl29003_set_resolution(client, 0);
	isl29003_set_mode(client, 0);
	isl29003_set_घातer_state(client, 0);

	वापस 0;
पूर्ण

/*
 * I2C layer
 */

अटल पूर्णांक isl29003_probe(काष्ठा i2c_client *client,
				    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा isl29003_data *data;
	पूर्णांक err = 0;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		वापस -EIO;

	data = kzalloc(माप(काष्ठा isl29003_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);

	/* initialize the ISL29003 chip */
	err = isl29003_init_client(client);
	अगर (err)
		जाओ निकास_kमुक्त;

	/* रेजिस्टर sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &isl29003_attr_group);
	अगर (err)
		जाओ निकास_kमुक्त;

	dev_info(&client->dev, "driver version %s enabled\n", DRIVER_VERSION);
	वापस 0;

निकास_kमुक्त:
	kमुक्त(data);
	वापस err;
पूर्ण

अटल पूर्णांक isl29003_हटाओ(काष्ठा i2c_client *client)
अणु
	sysfs_हटाओ_group(&client->dev.kobj, &isl29003_attr_group);
	isl29003_set_घातer_state(client, 0);
	kमुक्त(i2c_get_clientdata(client));
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक isl29003_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा isl29003_data *data = i2c_get_clientdata(client);

	data->घातer_state_beक्रमe_suspend = isl29003_get_घातer_state(client);
	वापस isl29003_set_घातer_state(client, 0);
पूर्ण

अटल पूर्णांक isl29003_resume(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा isl29003_data *data = i2c_get_clientdata(client);

	/* restore रेजिस्टरs from cache */
	क्रम (i = 0; i < ARRAY_SIZE(data->reg_cache); i++)
		अगर (i2c_smbus_ग_लिखो_byte_data(client, i, data->reg_cache[i]))
			वापस -EIO;

	वापस isl29003_set_घातer_state(client,
		data->घातer_state_beक्रमe_suspend);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(isl29003_pm_ops, isl29003_suspend, isl29003_resume);
#घोषणा ISL29003_PM_OPS (&isl29003_pm_ops)

#अन्यथा
#घोषणा ISL29003_PM_OPS शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा i2c_device_id isl29003_id[] = अणु
	अणु "isl29003", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isl29003_id);

अटल काष्ठा i2c_driver isl29003_driver = अणु
	.driver = अणु
		.name	= ISL29003_DRV_NAME,
		.pm	= ISL29003_PM_OPS,
	पूर्ण,
	.probe	= isl29003_probe,
	.हटाओ	= isl29003_हटाओ,
	.id_table = isl29003_id,
पूर्ण;

module_i2c_driver(isl29003_driver);

MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>");
MODULE_DESCRIPTION("ISL29003 ambient light sensor driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION(DRIVER_VERSION);
