<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 1-Wire implementation क्रम the ds2781 chip
 *
 * Author: Renata Sayakhova <renata@oktetद_असल.ru>
 *
 * Based on w1-ds2780 driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>

#समावेश <linux/w1.h>

#समावेश "w1_ds2781.h"

#घोषणा W1_FAMILY_DS2781	0x3D

अटल पूर्णांक w1_ds2781_करो_io(काष्ठा device *dev, अक्षर *buf, पूर्णांक addr,
			माप_प्रकार count, पूर्णांक io)
अणु
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);

	अगर (addr > DS2781_DATA_SIZE || addr < 0)
		वापस 0;

	count = min_t(पूर्णांक, count, DS2781_DATA_SIZE - addr);

	अगर (w1_reset_select_slave(sl) == 0) अणु
		अगर (io) अणु
			w1_ग_लिखो_8(sl->master, W1_DS2781_WRITE_DATA);
			w1_ग_लिखो_8(sl->master, addr);
			w1_ग_लिखो_block(sl->master, buf, count);
		पूर्ण अन्यथा अणु
			w1_ग_लिखो_8(sl->master, W1_DS2781_READ_DATA);
			w1_ग_लिखो_8(sl->master, addr);
			count = w1_पढ़ो_block(sl->master, buf, count);
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

पूर्णांक w1_ds2781_io(काष्ठा device *dev, अक्षर *buf, पूर्णांक addr, माप_प्रकार count,
			पूर्णांक io)
अणु
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);
	पूर्णांक ret;

	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&sl->master->bus_mutex);

	ret = w1_ds2781_करो_io(dev, buf, addr, count, io);

	mutex_unlock(&sl->master->bus_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(w1_ds2781_io);

पूर्णांक w1_ds2781_eeprom_cmd(काष्ठा device *dev, पूर्णांक addr, पूर्णांक cmd)
अणु
	काष्ठा w1_slave *sl = container_of(dev, काष्ठा w1_slave, dev);

	अगर (!dev)
		वापस -EINVAL;

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_reset_select_slave(sl) == 0) अणु
		w1_ग_लिखो_8(sl->master, cmd);
		w1_ग_लिखो_8(sl->master, addr);
	पूर्ण

	mutex_unlock(&sl->master->bus_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(w1_ds2781_eeprom_cmd);

अटल sमाप_प्रकार w1_slave_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			     काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			     loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	वापस w1_ds2781_io(dev, buf, off, count, 0);
पूर्ण

अटल BIN_ATTR_RO(w1_slave, DS2781_DATA_SIZE);

अटल काष्ठा bin_attribute *w1_ds2781_bin_attrs[] = अणु
	&bin_attr_w1_slave,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_ds2781_group = अणु
	.bin_attrs = w1_ds2781_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_ds2781_groups[] = अणु
	&w1_ds2781_group,
	शून्य,
पूर्ण;

अटल पूर्णांक w1_ds2781_add_slave(काष्ठा w1_slave *sl)
अणु
	पूर्णांक ret;
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_alloc("ds2781-battery", PLATFORM_DEVID_AUTO);
	अगर (!pdev)
		वापस -ENOMEM;
	pdev->dev.parent = &sl->dev;

	ret = platक्रमm_device_add(pdev);
	अगर (ret)
		जाओ pdev_add_failed;

	dev_set_drvdata(&sl->dev, pdev);

	वापस 0;

pdev_add_failed:
	platक्रमm_device_put(pdev);

	वापस ret;
पूर्ण

अटल व्योम w1_ds2781_हटाओ_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा platक्रमm_device *pdev = dev_get_drvdata(&sl->dev);

	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

अटल स्थिर काष्ठा w1_family_ops w1_ds2781_fops = अणु
	.add_slave    = w1_ds2781_add_slave,
	.हटाओ_slave = w1_ds2781_हटाओ_slave,
	.groups       = w1_ds2781_groups,
पूर्ण;

अटल काष्ठा w1_family w1_ds2781_family = अणु
	.fid = W1_FAMILY_DS2781,
	.fops = &w1_ds2781_fops,
पूर्ण;
module_w1_family(w1_ds2781_family);

MODULE_AUTHOR("Renata Sayakhova <renata@oktetlabs.ru>");
MODULE_DESCRIPTION("1-wire Driver for Maxim/Dallas DS2781 Stand-Alone Fuel Gauge IC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_FAMILY_DS2781));
