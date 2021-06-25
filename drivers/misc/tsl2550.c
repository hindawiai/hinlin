<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  tsl2550.c - Linux kernel modules क्रम ambient light sensor
 *
 *  Copyright (C) 2007 Roकरोlfo Giometti <giometti@linux.it>
 *  Copyright (C) 2007 Eurotech S.p.A. <info@eurotech.it>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>

#घोषणा TSL2550_DRV_NAME	"tsl2550"
#घोषणा DRIVER_VERSION		"1.2"

/*
 * Defines
 */

#घोषणा TSL2550_POWER_DOWN		0x00
#घोषणा TSL2550_POWER_UP		0x03
#घोषणा TSL2550_STANDARD_RANGE		0x18
#घोषणा TSL2550_EXTENDED_RANGE		0x1d
#घोषणा TSL2550_READ_ADC0		0x43
#घोषणा TSL2550_READ_ADC1		0x83

/*
 * Structs
 */

काष्ठा tsl2550_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;

	अचिन्हित पूर्णांक घातer_state:1;
	अचिन्हित पूर्णांक operating_mode:1;
पूर्ण;

/*
 * Global data
 */

अटल स्थिर u8 TSL2550_MODE_RANGE[2] = अणु
	TSL2550_STANDARD_RANGE, TSL2550_EXTENDED_RANGE,
पूर्ण;

/*
 * Management functions
 */

अटल पूर्णांक tsl2550_set_operating_mode(काष्ठा i2c_client *client, पूर्णांक mode)
अणु
	काष्ठा tsl2550_data *data = i2c_get_clientdata(client);

	पूर्णांक ret = i2c_smbus_ग_लिखो_byte(client, TSL2550_MODE_RANGE[mode]);

	data->operating_mode = mode;

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2550_set_घातer_state(काष्ठा i2c_client *client, पूर्णांक state)
अणु
	काष्ठा tsl2550_data *data = i2c_get_clientdata(client);
	पूर्णांक ret;

	अगर (state == 0)
		ret = i2c_smbus_ग_लिखो_byte(client, TSL2550_POWER_DOWN);
	अन्यथा अणु
		ret = i2c_smbus_ग_लिखो_byte(client, TSL2550_POWER_UP);

		/* On घातer up we should reset operating mode also... */
		tsl2550_set_operating_mode(client, data->operating_mode);
	पूर्ण

	data->घातer_state = state;

	वापस ret;
पूर्ण

अटल पूर्णांक tsl2550_get_adc_value(काष्ठा i2c_client *client, u8 cmd)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, cmd);
	अगर (ret < 0)
		वापस ret;
	अगर (!(ret & 0x80))
		वापस -EAGAIN;
	वापस ret & 0x7f;	/* हटाओ the "valid" bit */
पूर्ण

/*
 * LUX calculation
 */

#घोषणा	TSL2550_MAX_LUX		1846

अटल स्थिर u8 ratio_lut[] = अणु
	100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 98, 98, 98, 98, 98,
	98, 98, 97, 97, 97, 97, 97, 96,
	96, 96, 96, 95, 95, 95, 94, 94,
	93, 93, 93, 92, 92, 91, 91, 90,
	89, 89, 88, 87, 87, 86, 85, 84,
	83, 82, 81, 80, 79, 78, 77, 75,
	74, 73, 71, 69, 68, 66, 64, 62,
	60, 58, 56, 54, 52, 49, 47, 44,
	42, 41, 40, 40, 39, 39, 38, 38,
	37, 37, 37, 36, 36, 36, 35, 35,
	35, 35, 34, 34, 34, 34, 33, 33,
	33, 33, 32, 32, 32, 32, 32, 31,
	31, 31, 31, 31, 30, 30, 30, 30,
	30,
पूर्ण;

अटल स्थिर u16 count_lut[] = अणु
	0, 1, 2, 3, 4, 5, 6, 7,
	8, 9, 10, 11, 12, 13, 14, 15,
	16, 18, 20, 22, 24, 26, 28, 30,
	32, 34, 36, 38, 40, 42, 44, 46,
	49, 53, 57, 61, 65, 69, 73, 77,
	81, 85, 89, 93, 97, 101, 105, 109,
	115, 123, 131, 139, 147, 155, 163, 171,
	179, 187, 195, 203, 211, 219, 227, 235,
	247, 263, 279, 295, 311, 327, 343, 359,
	375, 391, 407, 423, 439, 455, 471, 487,
	511, 543, 575, 607, 639, 671, 703, 735,
	767, 799, 831, 863, 895, 927, 959, 991,
	1039, 1103, 1167, 1231, 1295, 1359, 1423, 1487,
	1551, 1615, 1679, 1743, 1807, 1871, 1935, 1999,
	2095, 2223, 2351, 2479, 2607, 2735, 2863, 2991,
	3119, 3247, 3375, 3503, 3631, 3759, 3887, 4015,
पूर्ण;

/*
 * This function is described पूर्णांकo Taos TSL2550 Designer's Notebook
 * pages 2, 3.
 */
अटल पूर्णांक tsl2550_calculate_lux(u8 ch0, u8 ch1)
अणु
	अचिन्हित पूर्णांक lux;

	/* Look up count from channel values */
	u16 c0 = count_lut[ch0];
	u16 c1 = count_lut[ch1];

	/* Aव्योम भागision by 0 and count 1 cannot be greater than count 0 */
	अगर (c1 <= c0)
		अगर (c0) अणु
			/*
			 * Calculate ratio.
			 * Note: the "128" is a scaling factor
			 */
			u8 r = c1 * 128 / c0;

			/* Calculate LUX */
			lux = ((c0 - c1) * ratio_lut[r]) / 256;
		पूर्ण अन्यथा
			lux = 0;
	अन्यथा
		वापस 0;

	/* LUX range check */
	वापस lux > TSL2550_MAX_LUX ? TSL2550_MAX_LUX : lux;
पूर्ण

/*
 * SysFS support
 */

अटल sमाप_प्रकार tsl2550_show_घातer_state(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tsl2550_data *data = i2c_get_clientdata(to_i2c_client(dev));

	वापस प्र_लिखो(buf, "%u\n", data->घातer_state);
पूर्ण

अटल sमाप_प्रकार tsl2550_store_घातer_state(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा tsl2550_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(buf, शून्य, 10);
	पूर्णांक ret;

	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	ret = tsl2550_set_घातer_state(client, val);
	mutex_unlock(&data->update_lock);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(घातer_state, S_IWUSR | S_IRUGO,
		   tsl2550_show_घातer_state, tsl2550_store_घातer_state);

अटल sमाप_प्रकार tsl2550_show_operating_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा tsl2550_data *data = i2c_get_clientdata(to_i2c_client(dev));

	वापस प्र_लिखो(buf, "%u\n", data->operating_mode);
पूर्ण

अटल sमाप_प्रकार tsl2550_store_operating_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा tsl2550_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val = simple_म_से_अदीर्घ(buf, शून्य, 10);
	पूर्णांक ret;

	अगर (val > 1)
		वापस -EINVAL;

	अगर (data->घातer_state == 0)
		वापस -EBUSY;

	mutex_lock(&data->update_lock);
	ret = tsl2550_set_operating_mode(client, val);
	mutex_unlock(&data->update_lock);

	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(operating_mode, S_IWUSR | S_IRUGO,
		   tsl2550_show_operating_mode, tsl2550_store_operating_mode);

अटल sमाप_प्रकार __tsl2550_show_lux(काष्ठा i2c_client *client, अक्षर *buf)
अणु
	काष्ठा tsl2550_data *data = i2c_get_clientdata(client);
	u8 ch0, ch1;
	पूर्णांक ret;

	ret = tsl2550_get_adc_value(client, TSL2550_READ_ADC0);
	अगर (ret < 0)
		वापस ret;
	ch0 = ret;

	ret = tsl2550_get_adc_value(client, TSL2550_READ_ADC1);
	अगर (ret < 0)
		वापस ret;
	ch1 = ret;

	/* Do the job */
	ret = tsl2550_calculate_lux(ch0, ch1);
	अगर (ret < 0)
		वापस ret;
	अगर (data->operating_mode == 1)
		ret *= 5;

	वापस प्र_लिखो(buf, "%d\n", ret);
पूर्ण

अटल sमाप_प्रकार tsl2550_show_lux1_input(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा tsl2550_data *data = i2c_get_clientdata(client);
	पूर्णांक ret;

	/* No LUX data अगर not operational */
	अगर (!data->घातer_state)
		वापस -EBUSY;

	mutex_lock(&data->update_lock);
	ret = __tsl2550_show_lux(client, buf);
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

अटल DEVICE_ATTR(lux1_input, S_IRUGO,
		   tsl2550_show_lux1_input, शून्य);

अटल काष्ठा attribute *tsl2550_attributes[] = अणु
	&dev_attr_घातer_state.attr,
	&dev_attr_operating_mode.attr,
	&dev_attr_lux1_input.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group tsl2550_attr_group = अणु
	.attrs = tsl2550_attributes,
पूर्ण;

/*
 * Initialization function
 */

अटल पूर्णांक tsl2550_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा tsl2550_data *data = i2c_get_clientdata(client);
	पूर्णांक err;

	/*
	 * Probe the chip. To करो so we try to घातer up the device and then to
	 * पढ़ो back the 0x03 code
	 */
	err = i2c_smbus_पढ़ो_byte_data(client, TSL2550_POWER_UP);
	अगर (err < 0)
		वापस err;
	अगर (err != TSL2550_POWER_UP)
		वापस -ENODEV;
	data->घातer_state = 1;

	/* Set the शेष operating mode */
	err = i2c_smbus_ग_लिखो_byte(client,
				   TSL2550_MODE_RANGE[data->operating_mode]);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

/*
 * I2C init/probing/निकास functions
 */

अटल काष्ठा i2c_driver tsl2550_driver;
अटल पूर्णांक tsl2550_probe(काष्ठा i2c_client *client,
				   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा tsl2550_data *data;
	पूर्णांक *opmode, err = 0;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WRITE_BYTE
					    | I2C_FUNC_SMBUS_READ_BYTE_DATA)) अणु
		err = -EIO;
		जाओ निकास;
	पूर्ण

	data = kzalloc(माप(काष्ठा tsl2550_data), GFP_KERNEL);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	data->client = client;
	i2c_set_clientdata(client, data);

	/* Check platक्रमm data */
	opmode = client->dev.platक्रमm_data;
	अगर (opmode) अणु
		अगर (*opmode < 0 || *opmode > 1) अणु
			dev_err(&client->dev, "invalid operating_mode (%d)\n",
					*opmode);
			err = -EINVAL;
			जाओ निकास_kमुक्त;
		पूर्ण
		data->operating_mode = *opmode;
	पूर्ण अन्यथा
		data->operating_mode = 0;	/* शेष mode is standard */
	dev_info(&client->dev, "%s operating mode\n",
			data->operating_mode ? "extended" : "standard");

	mutex_init(&data->update_lock);

	/* Initialize the TSL2550 chip */
	err = tsl2550_init_client(client);
	अगर (err)
		जाओ निकास_kमुक्त;

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &tsl2550_attr_group);
	अगर (err)
		जाओ निकास_kमुक्त;

	dev_info(&client->dev, "support ver. %s enabled\n", DRIVER_VERSION);

	वापस 0;

निकास_kमुक्त:
	kमुक्त(data);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक tsl2550_हटाओ(काष्ठा i2c_client *client)
अणु
	sysfs_हटाओ_group(&client->dev.kobj, &tsl2550_attr_group);

	/* Power करोwn the device */
	tsl2550_set_घातer_state(client, 0);

	kमुक्त(i2c_get_clientdata(client));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक tsl2550_suspend(काष्ठा device *dev)
अणु
	वापस tsl2550_set_घातer_state(to_i2c_client(dev), 0);
पूर्ण

अटल पूर्णांक tsl2550_resume(काष्ठा device *dev)
अणु
	वापस tsl2550_set_घातer_state(to_i2c_client(dev), 1);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(tsl2550_pm_ops, tsl2550_suspend, tsl2550_resume);
#घोषणा TSL2550_PM_OPS (&tsl2550_pm_ops)

#अन्यथा

#घोषणा TSL2550_PM_OPS शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा i2c_device_id tsl2550_id[] = अणु
	अणु "tsl2550", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tsl2550_id);

अटल स्थिर काष्ठा of_device_id tsl2550_of_match[] = अणु
	अणु .compatible = "taos,tsl2550" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tsl2550_of_match);

अटल काष्ठा i2c_driver tsl2550_driver = अणु
	.driver = अणु
		.name	= TSL2550_DRV_NAME,
		.of_match_table = tsl2550_of_match,
		.pm	= TSL2550_PM_OPS,
	पूर्ण,
	.probe	= tsl2550_probe,
	.हटाओ	= tsl2550_हटाओ,
	.id_table = tsl2550_id,
पूर्ण;

module_i2c_driver(tsl2550_driver);

MODULE_AUTHOR("Rodolfo Giometti <giometti@linux.it>");
MODULE_DESCRIPTION("TSL2550 ambient light sensor driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRIVER_VERSION);
