<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A driver क्रम the Integrated Circuits ICS932S401
 * Copyright (C) 2008 IBM
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x69, I2C_CLIENT_END पूर्ण;

/* ICS932S401 रेजिस्टरs */
#घोषणा ICS932S401_REG_CFG2			0x01
#घोषणा		ICS932S401_CFG1_SPREAD		0x01
#घोषणा ICS932S401_REG_CFG7			0x06
#घोषणा		ICS932S401_FS_MASK		0x07
#घोषणा	ICS932S401_REG_VENDOR_REV		0x07
#घोषणा		ICS932S401_VENDOR		1
#घोषणा		ICS932S401_VENDOR_MASK		0x0F
#घोषणा		ICS932S401_REV			4
#घोषणा		ICS932S401_REV_SHIFT		4
#घोषणा ICS932S401_REG_DEVICE			0x09
#घोषणा		ICS932S401_DEVICE		11
#घोषणा	ICS932S401_REG_CTRL			0x0A
#घोषणा		ICS932S401_MN_ENABLED		0x80
#घोषणा		ICS932S401_CPU_ALT		0x04
#घोषणा		ICS932S401_SRC_ALT		0x08
#घोषणा ICS932S401_REG_CPU_M_CTRL		0x0B
#घोषणा		ICS932S401_M_MASK		0x3F
#घोषणा	ICS932S401_REG_CPU_N_CTRL		0x0C
#घोषणा	ICS932S401_REG_CPU_SPREAD1		0x0D
#घोषणा ICS932S401_REG_CPU_SPREAD2		0x0E
#घोषणा		ICS932S401_SPREAD_MASK		0x7FFF
#घोषणा ICS932S401_REG_SRC_M_CTRL		0x0F
#घोषणा ICS932S401_REG_SRC_N_CTRL		0x10
#घोषणा	ICS932S401_REG_SRC_SPREAD1		0x11
#घोषणा ICS932S401_REG_SRC_SPREAD2		0x12
#घोषणा ICS932S401_REG_CPU_DIVISOR		0x13
#घोषणा		ICS932S401_CPU_DIVISOR_SHIFT	4
#घोषणा ICS932S401_REG_PCISRC_DIVISOR		0x14
#घोषणा		ICS932S401_SRC_DIVISOR_MASK	0x0F
#घोषणा		ICS932S401_PCI_DIVISOR_SHIFT	4

/* Base घड़ी is 14.318MHz */
#घोषणा BASE_CLOCK				14318

#घोषणा NUM_REGS				21
#घोषणा NUM_MIRRORED_REGS			15

अटल पूर्णांक regs_to_copy[NUM_MIRRORED_REGS] = अणु
	ICS932S401_REG_CFG2,
	ICS932S401_REG_CFG7,
	ICS932S401_REG_VENDOR_REV,
	ICS932S401_REG_DEVICE,
	ICS932S401_REG_CTRL,
	ICS932S401_REG_CPU_M_CTRL,
	ICS932S401_REG_CPU_N_CTRL,
	ICS932S401_REG_CPU_SPREAD1,
	ICS932S401_REG_CPU_SPREAD2,
	ICS932S401_REG_SRC_M_CTRL,
	ICS932S401_REG_SRC_N_CTRL,
	ICS932S401_REG_SRC_SPREAD1,
	ICS932S401_REG_SRC_SPREAD2,
	ICS932S401_REG_CPU_DIVISOR,
	ICS932S401_REG_PCISRC_DIVISOR,
पूर्ण;

/* How often करो we reपढ़ो sensors values? (In jअगरfies) */
#घोषणा SENSOR_REFRESH_INTERVAL	(2 * HZ)

/* How often करो we reपढ़ो sensor limit values? (In jअगरfies) */
#घोषणा LIMIT_REFRESH_INTERVAL	(60 * HZ)

काष्ठा ics932s401_data अणु
	काष्ठा attribute_group	attrs;
	काष्ठा mutex		lock;
	अक्षर			sensors_valid;
	अचिन्हित दीर्घ		sensors_last_updated;	/* In jअगरfies */

	u8			regs[NUM_REGS];
पूर्ण;

अटल पूर्णांक ics932s401_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id);
अटल पूर्णांक ics932s401_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info);
अटल पूर्णांक ics932s401_हटाओ(काष्ठा i2c_client *client);

अटल स्थिर काष्ठा i2c_device_id ics932s401_id[] = अणु
	अणु "ics932s401", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ics932s401_id);

अटल काष्ठा i2c_driver ics932s401_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "ics932s401",
	पूर्ण,
	.probe		= ics932s401_probe,
	.हटाओ		= ics932s401_हटाओ,
	.id_table	= ics932s401_id,
	.detect		= ics932s401_detect,
	.address_list	= normal_i2c,
पूर्ण;

अटल काष्ठा ics932s401_data *ics932s401_update_device(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा ics932s401_data *data = i2c_get_clientdata(client);
	अचिन्हित दीर्घ local_jअगरfies = jअगरfies;
	पूर्णांक i, temp;

	mutex_lock(&data->lock);
	अगर (समय_beक्रमe(local_jअगरfies, data->sensors_last_updated +
		SENSOR_REFRESH_INTERVAL)
		&& data->sensors_valid)
		जाओ out;

	/*
	 * Each रेजिस्टर must be पढ़ो as a word and then right shअगरted 8 bits.
	 * Not really sure why this is; setting the "byte count programming"
	 * रेजिस्टर to 1 करोes not fix this problem.
	 */
	क्रम (i = 0; i < NUM_MIRRORED_REGS; i++) अणु
		temp = i2c_smbus_पढ़ो_word_data(client, regs_to_copy[i]);
		अगर (temp < 0)
			temp = 0;
		data->regs[regs_to_copy[i]] = temp >> 8;
	पूर्ण

	data->sensors_last_updated = local_jअगरfies;
	data->sensors_valid = 1;

out:
	mutex_unlock(&data->lock);
	वापस data;
पूर्ण

अटल sमाप_प्रकार show_spपढ़ो_enabled(काष्ठा device *dev,
				   काष्ठा device_attribute *devattr,
				   अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);

	अगर (data->regs[ICS932S401_REG_CFG2] & ICS932S401_CFG1_SPREAD)
		वापस प्र_लिखो(buf, "1\n");

	वापस प्र_लिखो(buf, "0\n");
पूर्ण

/* bit to cpu khz map */
अटल स्थिर पूर्णांक fs_speeds[] = अणु
	266666,
	133333,
	200000,
	166666,
	333333,
	100000,
	400000,
	0,
पूर्ण;

/* घड़ी भागisor map */
अटल स्थिर पूर्णांक भागisors[] = अणु2, 3, 5, 15, 4, 6, 10, 30, 8, 12, 20, 60, 16,
			       24, 40, 120पूर्ण;

/* Calculate CPU frequency from the M/N रेजिस्टरs. */
अटल पूर्णांक calculate_cpu_freq(काष्ठा ics932s401_data *data)
अणु
	पूर्णांक m, n, freq;

	m = data->regs[ICS932S401_REG_CPU_M_CTRL] & ICS932S401_M_MASK;
	n = data->regs[ICS932S401_REG_CPU_N_CTRL];

	/* Pull in bits 8 & 9 from the M रेजिस्टर */
	n |= ((पूर्णांक)data->regs[ICS932S401_REG_CPU_M_CTRL] & 0x80) << 1;
	n |= ((पूर्णांक)data->regs[ICS932S401_REG_CPU_M_CTRL] & 0x40) << 3;

	freq = BASE_CLOCK * (n + 8) / (m + 2);
	freq /= भागisors[data->regs[ICS932S401_REG_CPU_DIVISOR] >>
			 ICS932S401_CPU_DIVISOR_SHIFT];

	वापस freq;
पूर्ण

अटल sमाप_प्रकार show_cpu_घड़ी(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", calculate_cpu_freq(data));
पूर्ण

अटल sमाप_प्रकार show_cpu_घड़ी_sel(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr,
				  अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);
	पूर्णांक freq;

	अगर (data->regs[ICS932S401_REG_CTRL] & ICS932S401_MN_ENABLED)
		freq = calculate_cpu_freq(data);
	अन्यथा अणु
		/* Freq is neatly wrapped up क्रम us */
		पूर्णांक fid = data->regs[ICS932S401_REG_CFG7] & ICS932S401_FS_MASK;

		freq = fs_speeds[fid];
		अगर (data->regs[ICS932S401_REG_CTRL] & ICS932S401_CPU_ALT) अणु
			चयन (freq) अणु
			हाल 166666:
				freq = 160000;
				अवरोध;
			हाल 333333:
				freq = 320000;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", freq);
पूर्ण

/* Calculate SRC frequency from the M/N रेजिस्टरs. */
अटल पूर्णांक calculate_src_freq(काष्ठा ics932s401_data *data)
अणु
	पूर्णांक m, n, freq;

	m = data->regs[ICS932S401_REG_SRC_M_CTRL] & ICS932S401_M_MASK;
	n = data->regs[ICS932S401_REG_SRC_N_CTRL];

	/* Pull in bits 8 & 9 from the M रेजिस्टर */
	n |= ((पूर्णांक)data->regs[ICS932S401_REG_SRC_M_CTRL] & 0x80) << 1;
	n |= ((पूर्णांक)data->regs[ICS932S401_REG_SRC_M_CTRL] & 0x40) << 3;

	freq = BASE_CLOCK * (n + 8) / (m + 2);
	freq /= भागisors[data->regs[ICS932S401_REG_PCISRC_DIVISOR] &
			 ICS932S401_SRC_DIVISOR_MASK];

	वापस freq;
पूर्ण

अटल sमाप_प्रकार show_src_घड़ी(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", calculate_src_freq(data));
पूर्ण

अटल sमाप_प्रकार show_src_घड़ी_sel(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr,
				  अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);
	पूर्णांक freq;

	अगर (data->regs[ICS932S401_REG_CTRL] & ICS932S401_MN_ENABLED)
		freq = calculate_src_freq(data);
	अन्यथा
		/* Freq is neatly wrapped up क्रम us */
		अगर (data->regs[ICS932S401_REG_CTRL] & ICS932S401_CPU_ALT &&
		    data->regs[ICS932S401_REG_CTRL] & ICS932S401_SRC_ALT)
			freq = 96000;
		अन्यथा
			freq = 100000;

	वापस प्र_लिखो(buf, "%d\n", freq);
पूर्ण

/* Calculate PCI frequency from the SRC M/N रेजिस्टरs. */
अटल पूर्णांक calculate_pci_freq(काष्ठा ics932s401_data *data)
अणु
	पूर्णांक m, n, freq;

	m = data->regs[ICS932S401_REG_SRC_M_CTRL] & ICS932S401_M_MASK;
	n = data->regs[ICS932S401_REG_SRC_N_CTRL];

	/* Pull in bits 8 & 9 from the M रेजिस्टर */
	n |= ((पूर्णांक)data->regs[ICS932S401_REG_SRC_M_CTRL] & 0x80) << 1;
	n |= ((पूर्णांक)data->regs[ICS932S401_REG_SRC_M_CTRL] & 0x40) << 3;

	freq = BASE_CLOCK * (n + 8) / (m + 2);
	freq /= भागisors[data->regs[ICS932S401_REG_PCISRC_DIVISOR] >>
			 ICS932S401_PCI_DIVISOR_SHIFT];

	वापस freq;
पूर्ण

अटल sमाप_प्रकार show_pci_घड़ी(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr,
			      अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);

	वापस प्र_लिखो(buf, "%d\n", calculate_pci_freq(data));
पूर्ण

अटल sमाप_प्रकार show_pci_घड़ी_sel(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr,
				  अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);
	पूर्णांक freq;

	अगर (data->regs[ICS932S401_REG_CTRL] & ICS932S401_MN_ENABLED)
		freq = calculate_pci_freq(data);
	अन्यथा
		freq = 33333;

	वापस प्र_लिखो(buf, "%d\n", freq);
पूर्ण

अटल sमाप_प्रकार show_value(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr,
			  अक्षर *buf);

अटल sमाप_प्रकार show_spपढ़ो(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr,
			   अक्षर *buf);

अटल DEVICE_ATTR(spपढ़ो_enabled, S_IRUGO, show_spपढ़ो_enabled, शून्य);
अटल DEVICE_ATTR(cpu_घड़ी_selection, S_IRUGO, show_cpu_घड़ी_sel, शून्य);
अटल DEVICE_ATTR(cpu_घड़ी, S_IRUGO, show_cpu_घड़ी, शून्य);
अटल DEVICE_ATTR(src_घड़ी_selection, S_IRUGO, show_src_घड़ी_sel, शून्य);
अटल DEVICE_ATTR(src_घड़ी, S_IRUGO, show_src_घड़ी, शून्य);
अटल DEVICE_ATTR(pci_घड़ी_selection, S_IRUGO, show_pci_घड़ी_sel, शून्य);
अटल DEVICE_ATTR(pci_घड़ी, S_IRUGO, show_pci_घड़ी, शून्य);
अटल DEVICE_ATTR(usb_घड़ी, S_IRUGO, show_value, शून्य);
अटल DEVICE_ATTR(ref_घड़ी, S_IRUGO, show_value, शून्य);
अटल DEVICE_ATTR(cpu_spपढ़ो, S_IRUGO, show_spपढ़ो, शून्य);
अटल DEVICE_ATTR(src_spपढ़ो, S_IRUGO, show_spपढ़ो, शून्य);

अटल काष्ठा attribute *ics932s401_attr[] = अणु
	&dev_attr_spपढ़ो_enabled.attr,
	&dev_attr_cpu_घड़ी_selection.attr,
	&dev_attr_cpu_घड़ी.attr,
	&dev_attr_src_घड़ी_selection.attr,
	&dev_attr_src_घड़ी.attr,
	&dev_attr_pci_घड़ी_selection.attr,
	&dev_attr_pci_घड़ी.attr,
	&dev_attr_usb_घड़ी.attr,
	&dev_attr_ref_घड़ी.attr,
	&dev_attr_cpu_spपढ़ो.attr,
	&dev_attr_src_spपढ़ो.attr,
	शून्य
पूर्ण;

अटल sमाप_प्रकार show_value(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr,
			  अक्षर *buf)
अणु
	पूर्णांक x;

	अगर (devattr == &dev_attr_usb_घड़ी)
		x = 48000;
	अन्यथा अगर (devattr == &dev_attr_ref_घड़ी)
		x = BASE_CLOCK;
	अन्यथा
		BUG();

	वापस प्र_लिखो(buf, "%d\n", x);
पूर्ण

अटल sमाप_प्रकार show_spपढ़ो(काष्ठा device *dev,
			   काष्ठा device_attribute *devattr,
			   अक्षर *buf)
अणु
	काष्ठा ics932s401_data *data = ics932s401_update_device(dev);
	पूर्णांक reg;
	अचिन्हित दीर्घ val;

	अगर (!(data->regs[ICS932S401_REG_CFG2] & ICS932S401_CFG1_SPREAD))
		वापस प्र_लिखो(buf, "0%%\n");

	अगर (devattr == &dev_attr_src_spपढ़ो)
		reg = ICS932S401_REG_SRC_SPREAD1;
	अन्यथा अगर (devattr == &dev_attr_cpu_spपढ़ो)
		reg = ICS932S401_REG_CPU_SPREAD1;
	अन्यथा
		BUG();

	val = data->regs[reg] | (data->regs[reg + 1] << 8);
	val &= ICS932S401_SPREAD_MASK;

	/* Scale 0..2^14 to -0.5. */
	val = 500000 * val / 16384;
	वापस प्र_लिखो(buf, "-0.%lu%%\n", val);
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक ics932s401_detect(काष्ठा i2c_client *client,
			  काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक venकरोr, device, revision;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	venकरोr = i2c_smbus_पढ़ो_word_data(client, ICS932S401_REG_VENDOR_REV);
	venकरोr >>= 8;
	revision = venकरोr >> ICS932S401_REV_SHIFT;
	venकरोr &= ICS932S401_VENDOR_MASK;
	अगर (venकरोr != ICS932S401_VENDOR)
		वापस -ENODEV;

	device = i2c_smbus_पढ़ो_word_data(client, ICS932S401_REG_DEVICE);
	device >>= 8;
	अगर (device != ICS932S401_DEVICE)
		वापस -ENODEV;

	अगर (revision != ICS932S401_REV)
		dev_info(&adapter->dev, "Unknown revision %d\n", revision);

	strlcpy(info->type, "ics932s401", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक ics932s401_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ics932s401_data *data;
	पूर्णांक err;

	data = kzalloc(माप(काष्ठा ics932s401_data), GFP_KERNEL);
	अगर (!data) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण

	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);

	dev_info(&client->dev, "%s chip found\n", client->name);

	/* Register sysfs hooks */
	data->attrs.attrs = ics932s401_attr;
	err = sysfs_create_group(&client->dev.kobj, &data->attrs);
	अगर (err)
		जाओ निकास_मुक्त;

	वापस 0;

निकास_मुक्त:
	kमुक्त(data);
निकास:
	वापस err;
पूर्ण

अटल पूर्णांक ics932s401_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा ics932s401_data *data = i2c_get_clientdata(client);

	sysfs_हटाओ_group(&client->dev.kobj, &data->attrs);
	kमुक्त(data);
	वापस 0;
पूर्ण

module_i2c_driver(ics932s401_driver);

MODULE_AUTHOR("Darrick J. Wong <darrick.wong@oracle.com>");
MODULE_DESCRIPTION("ICS932S401 driver");
MODULE_LICENSE("GPL");

/* IBM IntelliStation Z30 */
MODULE_ALIAS("dmi:bvnIBM:*:rn9228:*");
MODULE_ALIAS("dmi:bvnIBM:*:rn9232:*");

/* IBM x3650/x3550 */
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3650*");
MODULE_ALIAS("dmi:bvnIBM:*:pnIBMSystemx3550*");
