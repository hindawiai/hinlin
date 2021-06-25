<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * atxp1.c - kernel module क्रम setting CPU VID and general purpose
 *	     I/Os using the Attansic ATXP1 chip.
 *
 * The ATXP1 can reside on I2C addresses 0x37 or 0x4e. The chip is
 * not स्वतः-detected by the driver and must be instantiated explicitly.
 * See Documentation/i2c/instantiating-devices.rst क्रम more inक्रमmation.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-vid.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("System voltages control via Attansic ATXP1");
MODULE_VERSION("0.6.3");
MODULE_AUTHOR("Sebastian Witt <se.witt@gmx.net>");

#घोषणा ATXP1_VID	0x00
#घोषणा ATXP1_CVID	0x01
#घोषणा ATXP1_GPIO1	0x06
#घोषणा ATXP1_GPIO2	0x0a
#घोषणा ATXP1_VIDENA	0x20
#घोषणा ATXP1_VIDMASK	0x1f
#घोषणा ATXP1_GPIO1MASK	0x0f

काष्ठा atxp1_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_updated;
	u8 valid;
	काष्ठा अणु
		u8 vid;		/* VID output रेजिस्टर */
		u8 cpu_vid; /* VID input from CPU */
		u8 gpio1;   /* General purpose I/O रेजिस्टर 1 */
		u8 gpio2;   /* General purpose I/O रेजिस्टर 2 */
	पूर्ण reg;
	u8 vrm;			/* Detected CPU VRM */
पूर्ण;

अटल काष्ठा atxp1_data *atxp1_update_device(काष्ठा device *dev)
अणु
	काष्ठा atxp1_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु

		/* Update local रेजिस्टर data */
		data->reg.vid = i2c_smbus_पढ़ो_byte_data(client, ATXP1_VID);
		data->reg.cpu_vid = i2c_smbus_पढ़ो_byte_data(client,
							     ATXP1_CVID);
		data->reg.gpio1 = i2c_smbus_पढ़ो_byte_data(client, ATXP1_GPIO1);
		data->reg.gpio2 = i2c_smbus_पढ़ो_byte_data(client, ATXP1_GPIO2);

		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* sys file functions क्रम cpu0_vid */
अटल sमाप_प्रकार cpu0_vid_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक size;
	काष्ठा atxp1_data *data;

	data = atxp1_update_device(dev);

	size = प्र_लिखो(buf, "%d\n", vid_from_reg(data->reg.vid & ATXP1_VIDMASK,
						 data->vrm));

	वापस size;
पूर्ण

अटल sमाप_प्रकार cpu0_vid_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा atxp1_data *data = atxp1_update_device(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक vid, cvid;
	अचिन्हित दीर्घ vcore;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &vcore);
	अगर (err)
		वापस err;

	vcore /= 25;
	vcore *= 25;

	/* Calculate VID */
	vid = vid_to_reg(vcore, data->vrm);
	अगर (vid < 0) अणु
		dev_err(dev, "VID calculation failed.\n");
		वापस vid;
	पूर्ण

	/*
	 * If output enabled, use control रेजिस्टर value.
	 * Otherwise original CPU VID
	 */
	अगर (data->reg.vid & ATXP1_VIDENA)
		cvid = data->reg.vid & ATXP1_VIDMASK;
	अन्यथा
		cvid = data->reg.cpu_vid;

	/* Nothing changed, पातing */
	अगर (vid == cvid)
		वापस count;

	dev_dbg(dev, "Setting VCore to %d mV (0x%02x)\n", (पूर्णांक)vcore, vid);

	/* Write every 25 mV step to increase stability */
	अगर (cvid > vid) अणु
		क्रम (; cvid >= vid; cvid--)
			i2c_smbus_ग_लिखो_byte_data(client,
						ATXP1_VID, cvid | ATXP1_VIDENA);
	पूर्ण अन्यथा अणु
		क्रम (; cvid <= vid; cvid++)
			i2c_smbus_ग_लिखो_byte_data(client,
						ATXP1_VID, cvid | ATXP1_VIDENA);
	पूर्ण

	data->valid = 0;

	वापस count;
पूर्ण

/*
 * CPU core reference voltage
 * unit: millivolt
 */
अटल DEVICE_ATTR_RW(cpu0_vid);

/* sys file functions क्रम GPIO1 */
अटल sमाप_प्रकार gpio1_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक size;
	काष्ठा atxp1_data *data;

	data = atxp1_update_device(dev);

	size = प्र_लिखो(buf, "0x%02x\n", data->reg.gpio1 & ATXP1_GPIO1MASK);

	वापस size;
पूर्ण

अटल sमाप_प्रकार gpio1_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा atxp1_data *data = atxp1_update_device(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ value;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 16, &value);
	अगर (err)
		वापस err;

	value &= ATXP1_GPIO1MASK;

	अगर (value != (data->reg.gpio1 & ATXP1_GPIO1MASK)) अणु
		dev_info(dev, "Writing 0x%x to GPIO1.\n", (अचिन्हित पूर्णांक)value);

		i2c_smbus_ग_लिखो_byte_data(client, ATXP1_GPIO1, value);

		data->valid = 0;
	पूर्ण

	वापस count;
पूर्ण

/*
 * GPIO1 data रेजिस्टर
 * unit: Four bit as hex (e.g. 0x0f)
 */
अटल DEVICE_ATTR_RW(gpio1);

/* sys file functions क्रम GPIO2 */
अटल sमाप_प्रकार gpio2_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक size;
	काष्ठा atxp1_data *data;

	data = atxp1_update_device(dev);

	size = प्र_लिखो(buf, "0x%02x\n", data->reg.gpio2);

	वापस size;
पूर्ण

अटल sमाप_प्रकार gpio2_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा atxp1_data *data = atxp1_update_device(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ value;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 16, &value);
	अगर (err)
		वापस err;
	value &= 0xff;

	अगर (value != data->reg.gpio2) अणु
		dev_info(dev, "Writing 0x%x to GPIO1.\n", (अचिन्हित पूर्णांक)value);

		i2c_smbus_ग_लिखो_byte_data(client, ATXP1_GPIO2, value);

		data->valid = 0;
	पूर्ण

	वापस count;
पूर्ण

/*
 * GPIO2 data रेजिस्टर
 * unit: Eight bit as hex (e.g. 0xff)
 */
अटल DEVICE_ATTR_RW(gpio2);

अटल काष्ठा attribute *atxp1_attrs[] = अणु
	&dev_attr_gpio1.attr,
	&dev_attr_gpio2.attr,
	&dev_attr_cpu0_vid.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(atxp1);

अटल पूर्णांक atxp1_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा atxp1_data *data;
	काष्ठा device *hwmon_dev;

	data = devm_kzalloc(dev, माप(काष्ठा atxp1_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* Get VRM */
	data->vrm = vid_which_vrm();
	अगर (data->vrm != 90 && data->vrm != 91) अणु
		dev_err(dev, "atxp1: Not supporting VRM %d.%d\n",
			data->vrm / 10, data->vrm % 10);
		वापस -ENODEV;
	पूर्ण

	data->client = client;
	mutex_init(&data->update_lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   atxp1_groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(dev, "Using VRM: %d.%d\n", data->vrm / 10, data->vrm % 10);

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id atxp1_id[] = अणु
	अणु "atxp1", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, atxp1_id);

अटल काष्ठा i2c_driver atxp1_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "atxp1",
	पूर्ण,
	.probe_new	= atxp1_probe,
	.id_table	= atxp1_id,
पूर्ण;

module_i2c_driver(atxp1_driver);
