<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001-2004 Aurelien Jarno <aurelien@aurel32.net>
 * Ported to Linux 2.6 by Aurelien Jarno <aurelien@aurel32.net> with
 * the help of Jean Delvare <jdelvare@suse.de>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>

/* Insmod parameters */

अटल पूर्णांक input_mode;
module_param(input_mode, पूर्णांक, 0);
MODULE_PARM_DESC(input_mode,
	"Analog input mode:\n"
	" 0 = four single ended inputs\n"
	" 1 = three differential inputs\n"
	" 2 = single ended and differential mixed\n"
	" 3 = two differential inputs\n");

/*
 * The PCF8591 control byte
 *      7    6    5    4    3    2    1    0
 *   |  0 |AOEF|   AIP   |  0 |AINC|  AICH   |
 */

/* Analog Output Enable Flag (analog output active अगर 1) */
#घोषणा PCF8591_CONTROL_AOEF		0x40

/*
 * Analog Input Programming
 * 0x00 = four single ended inमाला_दो
 * 0x10 = three dअगरferential inमाला_दो
 * 0x20 = single ended and dअगरferential mixed
 * 0x30 = two dअगरferential inमाला_दो
 */
#घोषणा PCF8591_CONTROL_AIP_MASK	0x30

/* Autoincrement Flag (चयन on अगर 1) */
#घोषणा PCF8591_CONTROL_AINC		0x04

/*
 * Channel selection
 * 0x00 = channel 0
 * 0x01 = channel 1
 * 0x02 = channel 2
 * 0x03 = channel 3
 */
#घोषणा PCF8591_CONTROL_AICH_MASK	0x03

/* Initial values */
#घोषणा PCF8591_INIT_CONTROL	((input_mode << 4) | PCF8591_CONTROL_AOEF)
#घोषणा PCF8591_INIT_AOUT	0	/* DAC out = 0 */

/* Conversions */
#घोषणा REG_TO_SIGNED(reg)	(((reg) & 0x80) ? ((reg) - 256) : (reg))

काष्ठा pcf8591_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा mutex update_lock;

	u8 control;
	u8 aout;
पूर्ण;

अटल व्योम pcf8591_init_client(काष्ठा i2c_client *client);
अटल पूर्णांक pcf8591_पढ़ो_channel(काष्ठा device *dev, पूर्णांक channel);

/* following are the sysfs callback functions */
#घोषणा show_in_channel(channel)					\
अटल sमाप_प्रकार show_in##channel##_input(काष्ठा device *dev,		\
					काष्ठा device_attribute *attr,	\
					अक्षर *buf)			\
अणु									\
	वापस प्र_लिखो(buf, "%d\n", pcf8591_पढ़ो_channel(dev, channel));\
पूर्ण									\
अटल DEVICE_ATTR(in##channel##_input, S_IRUGO,			\
		   show_in##channel##_input, शून्य);

show_in_channel(0);
show_in_channel(1);
show_in_channel(2);
show_in_channel(3);

अटल sमाप_प्रकार out0_output_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcf8591_data *data = i2c_get_clientdata(to_i2c_client(dev));
	वापस प्र_लिखो(buf, "%d\n", data->aout * 10);
पूर्ण

अटल sमाप_प्रकार out0_output_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pcf8591_data *data = i2c_get_clientdata(client);
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	val /= 10;
	अगर (val > 255)
		वापस -EINVAL;

	data->aout = val;
	i2c_smbus_ग_लिखो_byte_data(client, data->control, data->aout);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(out0_output);

अटल sमाप_प्रकार out0_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcf8591_data *data = i2c_get_clientdata(to_i2c_client(dev));
	वापस प्र_लिखो(buf, "%u\n", !(!(data->control & PCF8591_CONTROL_AOEF)));
पूर्ण

अटल sमाप_प्रकार out0_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pcf8591_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	अगर (val)
		data->control |= PCF8591_CONTROL_AOEF;
	अन्यथा
		data->control &= ~PCF8591_CONTROL_AOEF;
	i2c_smbus_ग_लिखो_byte(client, data->control);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(out0_enable);

अटल काष्ठा attribute *pcf8591_attributes[] = अणु
	&dev_attr_out0_enable.attr,
	&dev_attr_out0_output.attr,
	&dev_attr_in0_input.attr,
	&dev_attr_in1_input.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pcf8591_attr_group = अणु
	.attrs = pcf8591_attributes,
पूर्ण;

अटल काष्ठा attribute *pcf8591_attributes_opt[] = अणु
	&dev_attr_in2_input.attr,
	&dev_attr_in3_input.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pcf8591_attr_group_opt = अणु
	.attrs = pcf8591_attributes_opt,
पूर्ण;

/*
 * Real code
 */

अटल पूर्णांक pcf8591_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pcf8591_data *data;
	पूर्णांक err;

	data = devm_kzalloc(&client->dev, माप(काष्ठा pcf8591_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the PCF8591 chip */
	pcf8591_init_client(client);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &pcf8591_attr_group);
	अगर (err)
		वापस err;

	/* Register input2 अगर not in "two differential inputs" mode */
	अगर (input_mode != 3) अणु
		err = device_create_file(&client->dev, &dev_attr_in2_input);
		अगर (err)
			जाओ निकास_sysfs_हटाओ;
	पूर्ण

	/* Register input3 only in "four single ended inputs" mode */
	अगर (input_mode == 0) अणु
		err = device_create_file(&client->dev, &dev_attr_in3_input);
		अगर (err)
			जाओ निकास_sysfs_हटाओ;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&client->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		जाओ निकास_sysfs_हटाओ;
	पूर्ण

	वापस 0;

निकास_sysfs_हटाओ:
	sysfs_हटाओ_group(&client->dev.kobj, &pcf8591_attr_group_opt);
	sysfs_हटाओ_group(&client->dev.kobj, &pcf8591_attr_group);
	वापस err;
पूर्ण

अटल पूर्णांक pcf8591_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा pcf8591_data *data = i2c_get_clientdata(client);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&client->dev.kobj, &pcf8591_attr_group_opt);
	sysfs_हटाओ_group(&client->dev.kobj, &pcf8591_attr_group);
	वापस 0;
पूर्ण

/* Called when we have found a new PCF8591. */
अटल व्योम pcf8591_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा pcf8591_data *data = i2c_get_clientdata(client);
	data->control = PCF8591_INIT_CONTROL;
	data->aout = PCF8591_INIT_AOUT;

	i2c_smbus_ग_लिखो_byte_data(client, data->control, data->aout);

	/*
	 * The first byte transmitted contains the conversion code of the
	 * previous पढ़ो cycle. FLUSH IT!
	 */
	i2c_smbus_पढ़ो_byte(client);
पूर्ण

अटल पूर्णांक pcf8591_पढ़ो_channel(काष्ठा device *dev, पूर्णांक channel)
अणु
	u8 value;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pcf8591_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	अगर ((data->control & PCF8591_CONTROL_AICH_MASK) != channel) अणु
		data->control = (data->control & ~PCF8591_CONTROL_AICH_MASK)
			      | channel;
		i2c_smbus_ग_लिखो_byte(client, data->control);

		/*
		 * The first byte transmitted contains the conversion code of
		 * the previous पढ़ो cycle. FLUSH IT!
		 */
		i2c_smbus_पढ़ो_byte(client);
	पूर्ण
	value = i2c_smbus_पढ़ो_byte(client);

	mutex_unlock(&data->update_lock);

	अगर ((channel == 2 && input_mode == 2) ||
	    (channel != 3 && (input_mode == 1 || input_mode == 3)))
		वापस 10 * REG_TO_SIGNED(value);
	अन्यथा
		वापस 10 * value;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcf8591_id[] = अणु
	अणु "pcf8591", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf8591_id);

अटल काष्ठा i2c_driver pcf8591_driver = अणु
	.driver = अणु
		.name	= "pcf8591",
	पूर्ण,
	.probe_new	= pcf8591_probe,
	.हटाओ		= pcf8591_हटाओ,
	.id_table	= pcf8591_id,
पूर्ण;

अटल पूर्णांक __init pcf8591_init(व्योम)
अणु
	अगर (input_mode < 0 || input_mode > 3) अणु
		pr_warn("invalid input_mode (%d)\n", input_mode);
		input_mode = 0;
	पूर्ण
	वापस i2c_add_driver(&pcf8591_driver);
पूर्ण

अटल व्योम __निकास pcf8591_निकास(व्योम)
अणु
	i2c_del_driver(&pcf8591_driver);
पूर्ण

MODULE_AUTHOR("Aurelien Jarno <aurelien@aurel32.net>");
MODULE_DESCRIPTION("PCF8591 driver");
MODULE_LICENSE("GPL");

module_init(pcf8591_init);
module_निकास(pcf8591_निकास);
