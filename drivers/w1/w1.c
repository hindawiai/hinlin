<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/list.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/of.h>

#समावेश <linux/atomic.h>

#समावेश "w1_internal.h"
#समावेश "w1_netlink.h"

#घोषणा W1_FAMILY_DEFAULT	0
#घोषणा W1_FAMILY_DS28E04       0x1C /* क्रम crc quirk */


अटल पूर्णांक w1_समयout = 10;
module_param_named(समयout, w1_समयout, पूर्णांक, 0);
MODULE_PARM_DESC(समयout, "time in seconds between automatic slave searches");

अटल पूर्णांक w1_समयout_us = 0;
module_param_named(समयout_us, w1_समयout_us, पूर्णांक, 0);
MODULE_PARM_DESC(समयout_us,
		 "time in microseconds between automatic slave searches");

/* A search stops when w1_max_slave_count devices have been found in that
 * search.  The next search will start over and detect the same set of devices
 * on a अटल 1-wire bus.  Memory is not allocated based on this number, just
 * on the number of devices known to the kernel.  Having a high number करोes not
 * consume additional resources.  As a special हाल, अगर there is only one
 * device on the network and w1_max_slave_count is set to 1, the device id can
 * be पढ़ो directly skipping the normal slower search process.
 */
पूर्णांक w1_max_slave_count = 64;
module_param_named(max_slave_count, w1_max_slave_count, पूर्णांक, 0);
MODULE_PARM_DESC(max_slave_count,
	"maximum number of slaves detected in a search");

पूर्णांक w1_max_slave_ttl = 10;
module_param_named(slave_ttl, w1_max_slave_ttl, पूर्णांक, 0);
MODULE_PARM_DESC(slave_ttl,
	"Number of searches not seeing a slave before it will be removed");

DEFINE_MUTEX(w1_mlock);
LIST_HEAD(w1_masters);

अटल पूर्णांक w1_master_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक w1_master_probe(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम w1_master_release(काष्ठा device *dev)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);

	dev_dbg(dev, "%s: Releasing %s.\n", __func__, md->name);
	स_रखो(md, 0, माप(काष्ठा w1_master) + माप(काष्ठा w1_bus_master));
	kमुक्त(md);
पूर्ण

अटल व्योम w1_slave_release(काष्ठा device *dev)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(dev);

	dev_dbg(dev, "%s: Releasing %s [%p]\n", __func__, sl->name, sl);

	w1_family_put(sl->family);
	sl->master->slave_count--;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(dev);

	वापस प्र_लिखो(buf, "%s\n", sl->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार id_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_slave *sl = dev_to_w1_slave(dev);
	sमाप_प्रकार count = माप(sl->reg_num);

	स_नकल(buf, (u8 *)&sl->reg_num, count);
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RO(id);

अटल काष्ठा attribute *w1_slave_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_id.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(w1_slave);

/* Default family */

अटल sमाप_प्रकार rw_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
			माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);

	mutex_lock(&sl->master->mutex);
	अगर (w1_reset_select_slave(sl)) अणु
		count = 0;
		जाओ out_up;
	पूर्ण

	w1_ग_लिखो_block(sl->master, buf, count);

out_up:
	mutex_unlock(&sl->master->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार rw_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
		       काष्ठा bin_attribute *bin_attr, अक्षर *buf, loff_t off,
		       माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = kobj_to_w1_slave(kobj);

	mutex_lock(&sl->master->mutex);
	w1_पढ़ो_block(sl->master, buf, count);
	mutex_unlock(&sl->master->mutex);
	वापस count;
पूर्ण

अटल BIN_ATTR_RW(rw, PAGE_SIZE);

अटल काष्ठा bin_attribute *w1_slave_bin_attrs[] = अणु
	&bin_attr_rw,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_slave_शेष_group = अणु
	.bin_attrs = w1_slave_bin_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *w1_slave_शेष_groups[] = अणु
	&w1_slave_शेष_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा w1_family_ops w1_शेष_fops = अणु
	.groups		= w1_slave_शेष_groups,
पूर्ण;

अटल काष्ठा w1_family w1_शेष_family = अणु
	.fops = &w1_शेष_fops,
पूर्ण;

अटल पूर्णांक w1_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env);

अटल काष्ठा bus_type w1_bus_type = अणु
	.name = "w1",
	.match = w1_master_match,
	.uevent = w1_uevent,
पूर्ण;

काष्ठा device_driver w1_master_driver = अणु
	.name = "w1_master_driver",
	.bus = &w1_bus_type,
	.probe = w1_master_probe,
पूर्ण;

काष्ठा device w1_master_device = अणु
	.parent = शून्य,
	.bus = &w1_bus_type,
	.init_name = "w1 bus master",
	.driver = &w1_master_driver,
	.release = &w1_master_release
पूर्ण;

अटल काष्ठा device_driver w1_slave_driver = अणु
	.name = "w1_slave_driver",
	.bus = &w1_bus_type,
पूर्ण;

#अगर 0
काष्ठा device w1_slave_device = अणु
	.parent = शून्य,
	.bus = &w1_bus_type,
	.init_name = "w1 bus slave",
	.driver = &w1_slave_driver,
	.release = &w1_slave_release
पूर्ण;
#पूर्ण_अगर  /*  0  */

अटल sमाप_प्रकार w1_master_attribute_show_name(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	sमाप_प्रकार count;

	mutex_lock(&md->mutex);
	count = प्र_लिखो(buf, "%s\n", md->name);
	mutex_unlock(&md->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_store_search(काष्ठा device * dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर * buf, माप_प्रकार count)
अणु
	दीर्घ पंचांगp;
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 0, &पंचांगp);
	अगर (ret)
		वापस ret;

	mutex_lock(&md->mutex);
	md->search_count = पंचांगp;
	mutex_unlock(&md->mutex);
	/* Only wake अगर it is going to be searching. */
	अगर (पंचांगp)
		wake_up_process(md->thपढ़ो);

	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_search(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	sमाप_प्रकार count;

	mutex_lock(&md->mutex);
	count = प्र_लिखो(buf, "%d\n", md->search_count);
	mutex_unlock(&md->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_store_pullup(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	दीर्घ पंचांगp;
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 0, &पंचांगp);
	अगर (ret)
		वापस ret;

	mutex_lock(&md->mutex);
	md->enable_pullup = पंचांगp;
	mutex_unlock(&md->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_pullup(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	sमाप_प्रकार count;

	mutex_lock(&md->mutex);
	count = प्र_लिखो(buf, "%d\n", md->enable_pullup);
	mutex_unlock(&md->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_poपूर्णांकer(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	sमाप_प्रकार count;

	mutex_lock(&md->mutex);
	count = प्र_लिखो(buf, "0x%p\n", md->bus_master);
	mutex_unlock(&md->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_समयout(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार count;
	count = प्र_लिखो(buf, "%d\n", w1_समयout);
	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_समयout_us(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार count;
	count = प्र_लिखो(buf, "%d\n", w1_समयout_us);
	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_store_max_slave_count(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक पंचांगp;
	काष्ठा w1_master *md = dev_to_w1_master(dev);

	अगर (kstrtoपूर्णांक(buf, 0, &पंचांगp) || पंचांगp < 1)
		वापस -EINVAL;

	mutex_lock(&md->mutex);
	md->max_slave_count = पंचांगp;
	/* allow each समय the max_slave_count is updated */
	clear_bit(W1_WARN_MAX_COUNT, &md->flags);
	mutex_unlock(&md->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_max_slave_count(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	sमाप_प्रकार count;

	mutex_lock(&md->mutex);
	count = प्र_लिखो(buf, "%d\n", md->max_slave_count);
	mutex_unlock(&md->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_attempts(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	sमाप_प्रकार count;

	mutex_lock(&md->mutex);
	count = प्र_लिखो(buf, "%lu\n", md->attempts);
	mutex_unlock(&md->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_slave_count(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	sमाप_प्रकार count;

	mutex_lock(&md->mutex);
	count = प्र_लिखो(buf, "%d\n", md->slave_count);
	mutex_unlock(&md->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_slaves(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	पूर्णांक c = PAGE_SIZE;
	काष्ठा list_head *ent, *n;
	काष्ठा w1_slave *sl = शून्य;

	mutex_lock(&md->list_mutex);

	list_क्रम_each_safe(ent, n, &md->slist) अणु
		sl = list_entry(ent, काष्ठा w1_slave, w1_slave_entry);

		c -= snम_लिखो(buf + PAGE_SIZE - c, c, "%s\n", sl->name);
	पूर्ण
	अगर (!sl)
		c -= snम_लिखो(buf + PAGE_SIZE - c, c, "not found.\n");

	mutex_unlock(&md->list_mutex);

	वापस PAGE_SIZE - c;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_add(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक c = PAGE_SIZE;
	c -= snम_लिखो(buf+PAGE_SIZE - c, c,
		"write device id xx-xxxxxxxxxxxx to add slave\n");
	वापस PAGE_SIZE - c;
पूर्ण

अटल पूर्णांक w1_atoreg_num(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार count,
	काष्ठा w1_reg_num *rn)
अणु
	अचिन्हित पूर्णांक family;
	अचिन्हित दीर्घ दीर्घ id;
	पूर्णांक i;
	u64 rn64_le;

	/* The CRC value isn't पढ़ो from the user because the sysfs directory
	 * करोesn't include it and most messages from the bus search don't
	 * prपूर्णांक it either.  It would be unreasonable क्रम the user to then
	 * provide it.
	 */
	स्थिर अक्षर *error_msg = "bad slave string format, expecting "
		"ff-dddddddddddd\n";

	अगर (buf[2] != '-') अणु
		dev_err(dev, "%s", error_msg);
		वापस -EINVAL;
	पूर्ण
	i = माला_पूछो(buf, "%02x-%012llx", &family, &id);
	अगर (i != 2) अणु
		dev_err(dev, "%s", error_msg);
		वापस -EINVAL;
	पूर्ण
	rn->family = family;
	rn->id = id;

	rn64_le = cpu_to_le64(*(u64 *)rn);
	rn->crc = w1_calc_crc8((u8 *)&rn64_le, 7);

#अगर 0
	dev_info(dev, "With CRC device is %02x.%012llx.%02x.\n",
		  rn->family, (अचिन्हित दीर्घ दीर्घ)rn->id, rn->crc);
#पूर्ण_अगर

	वापस 0;
पूर्ण

/* Searches the slaves in the w1_master and वापसs a poपूर्णांकer or शून्य.
 * Note: must not hold list_mutex
 */
काष्ठा w1_slave *w1_slave_search_device(काष्ठा w1_master *dev,
	काष्ठा w1_reg_num *rn)
अणु
	काष्ठा w1_slave *sl;
	mutex_lock(&dev->list_mutex);
	list_क्रम_each_entry(sl, &dev->slist, w1_slave_entry) अणु
		अगर (sl->reg_num.family == rn->family &&
				sl->reg_num.id == rn->id &&
				sl->reg_num.crc == rn->crc) अणु
			mutex_unlock(&dev->list_mutex);
			वापस sl;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->list_mutex);
	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_store_add(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	काष्ठा w1_reg_num rn;
	काष्ठा w1_slave *sl;
	sमाप_प्रकार result = count;

	अगर (w1_atoreg_num(dev, buf, count, &rn))
		वापस -EINVAL;

	mutex_lock(&md->mutex);
	sl = w1_slave_search_device(md, &rn);
	/* It would be nice to करो a targeted search one the one-wire bus
	 * क्रम the new device to see अगर it is out there or not.  But the
	 * current search करोesn't support that.
	 */
	अगर (sl) अणु
		dev_info(dev, "Device %s already exists\n", sl->name);
		result = -EINVAL;
	पूर्ण अन्यथा अणु
		w1_attach_slave_device(md, &rn);
	पूर्ण
	mutex_unlock(&md->mutex);

	वापस result;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_show_हटाओ(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक c = PAGE_SIZE;
	c -= snम_लिखो(buf+PAGE_SIZE - c, c,
		"write device id xx-xxxxxxxxxxxx to remove slave\n");
	वापस PAGE_SIZE - c;
पूर्ण

अटल sमाप_प्रकार w1_master_attribute_store_हटाओ(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा w1_master *md = dev_to_w1_master(dev);
	काष्ठा w1_reg_num rn;
	काष्ठा w1_slave *sl;
	sमाप_प्रकार result = count;

	अगर (w1_atoreg_num(dev, buf, count, &rn))
		वापस -EINVAL;

	mutex_lock(&md->mutex);
	sl = w1_slave_search_device(md, &rn);
	अगर (sl) अणु
		result = w1_slave_detach(sl);
		/* refcnt 0 means it was detached in the call */
		अगर (result == 0)
			result = count;
	पूर्ण अन्यथा अणु
		dev_info(dev, "Device %02x-%012llx doesn't exists\n", rn.family,
			(अचिन्हित दीर्घ दीर्घ)rn.id);
		result = -EINVAL;
	पूर्ण
	mutex_unlock(&md->mutex);

	वापस result;
पूर्ण

#घोषणा W1_MASTER_ATTR_RO(_name, _mode)				\
	काष्ठा device_attribute w1_master_attribute_##_name =	\
		__ATTR(w1_master_##_name, _mode,		\
		       w1_master_attribute_show_##_name, शून्य)

#घोषणा W1_MASTER_ATTR_RW(_name, _mode)				\
	काष्ठा device_attribute w1_master_attribute_##_name =	\
		__ATTR(w1_master_##_name, _mode,		\
		       w1_master_attribute_show_##_name,	\
		       w1_master_attribute_store_##_name)

अटल W1_MASTER_ATTR_RO(name, S_IRUGO);
अटल W1_MASTER_ATTR_RO(slaves, S_IRUGO);
अटल W1_MASTER_ATTR_RO(slave_count, S_IRUGO);
अटल W1_MASTER_ATTR_RW(max_slave_count, S_IRUGO | S_IWUSR | S_IWGRP);
अटल W1_MASTER_ATTR_RO(attempts, S_IRUGO);
अटल W1_MASTER_ATTR_RO(समयout, S_IRUGO);
अटल W1_MASTER_ATTR_RO(समयout_us, S_IRUGO);
अटल W1_MASTER_ATTR_RO(poपूर्णांकer, S_IRUGO);
अटल W1_MASTER_ATTR_RW(search, S_IRUGO | S_IWUSR | S_IWGRP);
अटल W1_MASTER_ATTR_RW(pullup, S_IRUGO | S_IWUSR | S_IWGRP);
अटल W1_MASTER_ATTR_RW(add, S_IRUGO | S_IWUSR | S_IWGRP);
अटल W1_MASTER_ATTR_RW(हटाओ, S_IRUGO | S_IWUSR | S_IWGRP);

अटल काष्ठा attribute *w1_master_शेष_attrs[] = अणु
	&w1_master_attribute_name.attr,
	&w1_master_attribute_slaves.attr,
	&w1_master_attribute_slave_count.attr,
	&w1_master_attribute_max_slave_count.attr,
	&w1_master_attribute_attempts.attr,
	&w1_master_attribute_समयout.attr,
	&w1_master_attribute_समयout_us.attr,
	&w1_master_attribute_poपूर्णांकer.attr,
	&w1_master_attribute_search.attr,
	&w1_master_attribute_pullup.attr,
	&w1_master_attribute_add.attr,
	&w1_master_attribute_हटाओ.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group w1_master_defattr_group = अणु
	.attrs = w1_master_शेष_attrs,
पूर्ण;

पूर्णांक w1_create_master_attributes(काष्ठा w1_master *master)
अणु
	वापस sysfs_create_group(&master->dev.kobj, &w1_master_defattr_group);
पूर्ण

व्योम w1_destroy_master_attributes(काष्ठा w1_master *master)
अणु
	sysfs_हटाओ_group(&master->dev.kobj, &w1_master_defattr_group);
पूर्ण

अटल पूर्णांक w1_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा w1_master *md = शून्य;
	काष्ठा w1_slave *sl = शून्य;
	अक्षर *event_owner, *name;
	पूर्णांक err = 0;

	अगर (dev->driver == &w1_master_driver) अणु
		md = container_of(dev, काष्ठा w1_master, dev);
		event_owner = "master";
		name = md->name;
	पूर्ण अन्यथा अगर (dev->driver == &w1_slave_driver) अणु
		sl = container_of(dev, काष्ठा w1_slave, dev);
		event_owner = "slave";
		name = sl->name;
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "Unknown event.\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev, "Hotplug event for %s %s, bus_id=%s.\n",
			event_owner, name, dev_name(dev));

	अगर (dev->driver != &w1_slave_driver || !sl)
		जाओ end;

	err = add_uevent_var(env, "W1_FID=%02X", sl->reg_num.family);
	अगर (err)
		जाओ end;

	err = add_uevent_var(env, "W1_SLAVE_ID=%024LX",
			     (अचिन्हित दीर्घ दीर्घ)sl->reg_num.id);
end:
	वापस err;
पूर्ण

अटल पूर्णांक w1_family_notअगरy(अचिन्हित दीर्घ action, काष्ठा w1_slave *sl)
अणु
	स्थिर काष्ठा w1_family_ops *fops;
	पूर्णांक err;

	fops = sl->family->fops;

	अगर (!fops)
		वापस 0;

	चयन (action) अणु
	हाल BUS_NOTIFY_ADD_DEVICE:
		/* अगर the family driver needs to initialize something... */
		अगर (fops->add_slave) अणु
			err = fops->add_slave(sl);
			अगर (err < 0) अणु
				dev_err(&sl->dev,
					"add_slave() call failed. err=%d\n",
					err);
				वापस err;
			पूर्ण
		पूर्ण
		अगर (fops->groups) अणु
			err = sysfs_create_groups(&sl->dev.kobj, fops->groups);
			अगर (err) अणु
				dev_err(&sl->dev,
					"sysfs group creation failed. err=%d\n",
					err);
				वापस err;
			पूर्ण
		पूर्ण
		अगर (IS_REACHABLE(CONFIG_HWMON) && fops->chip_info) अणु
			काष्ठा device *hwmon
				= hwmon_device_रेजिस्टर_with_info(&sl->dev,
						"w1_slave_temp", sl,
						fops->chip_info,
						शून्य);
			अगर (IS_ERR(hwmon)) अणु
				dev_warn(&sl->dev,
					 "could not create hwmon device\n");
			पूर्ण अन्यथा अणु
				sl->hwmon = hwmon;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल BUS_NOTIFY_DEL_DEVICE:
		अगर (IS_REACHABLE(CONFIG_HWMON) && fops->chip_info &&
			    sl->hwmon)
			hwmon_device_unरेजिस्टर(sl->hwmon);
		अगर (fops->हटाओ_slave)
			sl->family->fops->हटाओ_slave(sl);
		अगर (fops->groups)
			sysfs_हटाओ_groups(&sl->dev.kobj, fops->groups);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __w1_attach_slave_device(काष्ठा w1_slave *sl)
अणु
	पूर्णांक err;

	sl->dev.parent = &sl->master->dev;
	sl->dev.driver = &w1_slave_driver;
	sl->dev.bus = &w1_bus_type;
	sl->dev.release = &w1_slave_release;
	sl->dev.groups = w1_slave_groups;
	sl->dev.of_node = of_find_matching_node(sl->master->dev.of_node,
						sl->family->of_match_table);

	dev_set_name(&sl->dev, "%02x-%012llx",
		 (अचिन्हित पूर्णांक) sl->reg_num.family,
		 (अचिन्हित दीर्घ दीर्घ) sl->reg_num.id);
	snम_लिखो(&sl->name[0], माप(sl->name),
		 "%02x-%012llx",
		 (अचिन्हित पूर्णांक) sl->reg_num.family,
		 (अचिन्हित दीर्घ दीर्घ) sl->reg_num.id);

	dev_dbg(&sl->dev, "%s: registering %s as %p.\n", __func__,
		dev_name(&sl->dev), sl);

	/* suppress क्रम w1_family_notअगरy beक्रमe sending KOBJ_ADD */
	dev_set_uevent_suppress(&sl->dev, true);

	err = device_रेजिस्टर(&sl->dev);
	अगर (err < 0) अणु
		dev_err(&sl->dev,
			"Device registration [%s] failed. err=%d\n",
			dev_name(&sl->dev), err);
		put_device(&sl->dev);
		वापस err;
	पूर्ण
	w1_family_notअगरy(BUS_NOTIFY_ADD_DEVICE, sl);

	dev_set_uevent_suppress(&sl->dev, false);
	kobject_uevent(&sl->dev.kobj, KOBJ_ADD);

	mutex_lock(&sl->master->list_mutex);
	list_add_tail(&sl->w1_slave_entry, &sl->master->slist);
	mutex_unlock(&sl->master->list_mutex);

	वापस 0;
पूर्ण

पूर्णांक w1_attach_slave_device(काष्ठा w1_master *dev, काष्ठा w1_reg_num *rn)
अणु
	काष्ठा w1_slave *sl;
	काष्ठा w1_family *f;
	पूर्णांक err;
	काष्ठा w1_netlink_msg msg;

	sl = kzalloc(माप(काष्ठा w1_slave), GFP_KERNEL);
	अगर (!sl) अणु
		dev_err(&dev->dev,
			 "%s: failed to allocate new slave device.\n",
			 __func__);
		वापस -ENOMEM;
	पूर्ण


	sl->owner = THIS_MODULE;
	sl->master = dev;
	set_bit(W1_SLAVE_ACTIVE, &sl->flags);

	स_रखो(&msg, 0, माप(msg));
	स_नकल(&sl->reg_num, rn, माप(sl->reg_num));
	atomic_set(&sl->refcnt, 1);
	atomic_inc(&sl->master->refcnt);
	dev->slave_count++;
	dev_info(&dev->dev, "Attaching one wire slave %02x.%012llx crc %02x\n",
		  rn->family, (अचिन्हित दीर्घ दीर्घ)rn->id, rn->crc);

	/* slave modules need to be loaded in a context with unlocked mutex */
	mutex_unlock(&dev->mutex);
	request_module("w1-family-0x%02X", rn->family);
	mutex_lock(&dev->mutex);

	spin_lock(&w1_flock);
	f = w1_family_रेजिस्टरed(rn->family);
	अगर (!f) अणु
		f= &w1_शेष_family;
		dev_info(&dev->dev, "Family %x for %02x.%012llx.%02x is not registered.\n",
			  rn->family, rn->family,
			  (अचिन्हित दीर्घ दीर्घ)rn->id, rn->crc);
	पूर्ण
	__w1_family_get(f);
	spin_unlock(&w1_flock);

	sl->family = f;

	err = __w1_attach_slave_device(sl);
	अगर (err < 0) अणु
		dev_err(&dev->dev, "%s: Attaching %s failed.\n", __func__,
			 sl->name);
		dev->slave_count--;
		w1_family_put(sl->family);
		atomic_dec(&sl->master->refcnt);
		kमुक्त(sl);
		वापस err;
	पूर्ण

	sl->ttl = dev->slave_ttl;

	स_नकल(msg.id.id, rn, माप(msg.id));
	msg.type = W1_SLAVE_ADD;
	w1_netlink_send(dev, &msg);

	वापस 0;
पूर्ण

पूर्णांक w1_unref_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_master *dev = sl->master;
	पूर्णांक refcnt;
	mutex_lock(&dev->list_mutex);
	refcnt = atomic_sub_वापस(1, &sl->refcnt);
	अगर (refcnt == 0) अणु
		काष्ठा w1_netlink_msg msg;

		dev_dbg(&sl->dev, "%s: detaching %s [%p].\n", __func__,
			sl->name, sl);

		list_del(&sl->w1_slave_entry);

		स_रखो(&msg, 0, माप(msg));
		स_नकल(msg.id.id, &sl->reg_num, माप(msg.id));
		msg.type = W1_SLAVE_REMOVE;
		w1_netlink_send(sl->master, &msg);

		w1_family_notअगरy(BUS_NOTIFY_DEL_DEVICE, sl);
		device_unरेजिस्टर(&sl->dev);
		#अगर_घोषित DEBUG
		स_रखो(sl, 0, माप(*sl));
		#पूर्ण_अगर
		kमुक्त(sl);
	पूर्ण
	atomic_dec(&dev->refcnt);
	mutex_unlock(&dev->list_mutex);
	वापस refcnt;
पूर्ण

पूर्णांक w1_slave_detach(काष्ठा w1_slave *sl)
अणु
	/* Only detach a slave once as it decreases the refcnt each समय. */
	पूर्णांक destroy_now;
	mutex_lock(&sl->master->list_mutex);
	destroy_now = !test_bit(W1_SLAVE_DETACH, &sl->flags);
	set_bit(W1_SLAVE_DETACH, &sl->flags);
	mutex_unlock(&sl->master->list_mutex);

	अगर (destroy_now)
		destroy_now = !w1_unref_slave(sl);
	वापस destroy_now ? 0 : -EBUSY;
पूर्ण

काष्ठा w1_master *w1_search_master_id(u32 id)
अणु
	काष्ठा w1_master *dev;
	पूर्णांक found = 0;

	mutex_lock(&w1_mlock);
	list_क्रम_each_entry(dev, &w1_masters, w1_master_entry) अणु
		अगर (dev->id == id) अणु
			found = 1;
			atomic_inc(&dev->refcnt);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&w1_mlock);

	वापस (found)?dev:शून्य;
पूर्ण

काष्ठा w1_slave *w1_search_slave(काष्ठा w1_reg_num *id)
अणु
	काष्ठा w1_master *dev;
	काष्ठा w1_slave *sl = शून्य;
	पूर्णांक found = 0;

	mutex_lock(&w1_mlock);
	list_क्रम_each_entry(dev, &w1_masters, w1_master_entry) अणु
		mutex_lock(&dev->list_mutex);
		list_क्रम_each_entry(sl, &dev->slist, w1_slave_entry) अणु
			अगर (sl->reg_num.family == id->family &&
					sl->reg_num.id == id->id &&
					sl->reg_num.crc == id->crc) अणु
				found = 1;
				atomic_inc(&dev->refcnt);
				atomic_inc(&sl->refcnt);
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&dev->list_mutex);

		अगर (found)
			अवरोध;
	पूर्ण
	mutex_unlock(&w1_mlock);

	वापस (found)?sl:शून्य;
पूर्ण

व्योम w1_reconnect_slaves(काष्ठा w1_family *f, पूर्णांक attach)
अणु
	काष्ठा w1_slave *sl, *sln;
	काष्ठा w1_master *dev;

	mutex_lock(&w1_mlock);
	list_क्रम_each_entry(dev, &w1_masters, w1_master_entry) अणु
		dev_dbg(&dev->dev, "Reconnecting slaves in device %s "
			"for family %02x.\n", dev->name, f->fid);
		mutex_lock(&dev->mutex);
		mutex_lock(&dev->list_mutex);
		list_क्रम_each_entry_safe(sl, sln, &dev->slist, w1_slave_entry) अणु
			/* If it is a new family, slaves with the शेष
			 * family driver and are that family will be
			 * connected.  If the family is going away, devices
			 * matching that family are reconneced.
			 */
			अगर ((attach && sl->family->fid == W1_FAMILY_DEFAULT
				&& sl->reg_num.family == f->fid) ||
				(!attach && sl->family->fid == f->fid)) अणु
				काष्ठा w1_reg_num rn;

				mutex_unlock(&dev->list_mutex);
				स_नकल(&rn, &sl->reg_num, माप(rn));
				/* If it was alपढ़ोy in use let the स्वतःmatic
				 * scan pick it up again later.
				 */
				अगर (!w1_slave_detach(sl))
					w1_attach_slave_device(dev, &rn);
				mutex_lock(&dev->list_mutex);
			पूर्ण
		पूर्ण
		dev_dbg(&dev->dev, "Reconnecting slaves in device %s "
			"has been finished.\n", dev->name);
		mutex_unlock(&dev->list_mutex);
		mutex_unlock(&dev->mutex);
	पूर्ण
	mutex_unlock(&w1_mlock);
पूर्ण

अटल पूर्णांक w1_addr_crc_is_valid(काष्ठा w1_master *dev, u64 rn)
अणु
	u64 rn_le = cpu_to_le64(rn);
	काष्ठा w1_reg_num *पंचांगp = (काष्ठा w1_reg_num *)&rn;
	u8 crc;

	crc = w1_calc_crc8((u8 *)&rn_le, 7);

	/* quirk:
	 *   DS28E04 (1w eeprom) has strapping pins to change
	 *   address, but will not update the crc. So normal rules
	 *   क्रम consistent w1 addresses are violated. We test
	 *   with the 7 LSBs of the address क्रमced high.
	 *
	 *   (अक्षर*)&rn_le = अणु family, addr_lsb, ..., addr_msb, crc पूर्ण.
	 */
	अगर (crc != पंचांगp->crc && पंचांगp->family == W1_FAMILY_DS28E04) अणु
		u64 corr_le = rn_le;

		((u8 *)&corr_le)[1] |= 0x7f;
		crc = w1_calc_crc8((u8 *)&corr_le, 7);

		dev_info(&dev->dev, "DS28E04 crc workaround on %02x.%012llx.%02x\n",
			पंचांगp->family, (अचिन्हित दीर्घ दीर्घ)पंचांगp->id, पंचांगp->crc);
	पूर्ण

	अगर (crc != पंचांगp->crc) अणु
		dev_dbg(&dev->dev, "w1 addr crc mismatch: %02x.%012llx.%02x != 0x%02x.\n",
			पंचांगp->family, (अचिन्हित दीर्घ दीर्घ)पंचांगp->id, पंचांगp->crc, crc);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

व्योम w1_slave_found(काष्ठा w1_master *dev, u64 rn)
अणु
	काष्ठा w1_slave *sl;
	काष्ठा w1_reg_num *पंचांगp;

	atomic_inc(&dev->refcnt);

	पंचांगp = (काष्ठा w1_reg_num *) &rn;

	sl = w1_slave_search_device(dev, पंचांगp);
	अगर (sl) अणु
		set_bit(W1_SLAVE_ACTIVE, &sl->flags);
	पूर्ण अन्यथा अणु
		अगर (rn && w1_addr_crc_is_valid(dev, rn))
			w1_attach_slave_device(dev, पंचांगp);
	पूर्ण

	atomic_dec(&dev->refcnt);
पूर्ण

/**
 * w1_search() - Perक्रमms a ROM Search & रेजिस्टरs any devices found.
 * @dev: The master device to search
 * @search_type: W1_SEARCH to search all devices, or W1_ALARM_SEARCH
 * to वापस only devices in the alarmed state
 * @cb: Function to call when a device is found
 *
 * The 1-wire search is a simple binary tree search.
 * For each bit of the address, we पढ़ो two bits and ग_लिखो one bit.
 * The bit written will put to sleep all devies that करोn't match that bit.
 * When the two पढ़ोs dअगरfer, the direction choice is obvious.
 * When both bits are 0, we must choose a path to take.
 * When we can scan all 64 bits without having to choose a path, we are करोne.
 *
 * See "Application note 187 1-wire search algorithm" at www.maxim-ic.com
 *
 */
व्योम w1_search(काष्ठा w1_master *dev, u8 search_type, w1_slave_found_callback cb)
अणु
	u64 last_rn, rn, पंचांगp64;
	पूर्णांक i, slave_count = 0;
	पूर्णांक last_zero, last_device;
	पूर्णांक search_bit, desc_bit;
	u8  triplet_ret = 0;

	search_bit = 0;
	rn = dev->search_id;
	last_rn = 0;
	last_device = 0;
	last_zero = -1;

	desc_bit = 64;

	जबतक ( !last_device && (slave_count++ < dev->max_slave_count) ) अणु
		last_rn = rn;
		rn = 0;

		/*
		 * Reset bus and all 1-wire device state machines
		 * so they can respond to our requests.
		 *
		 * Return 0 - device(s) present, 1 - no devices present.
		 */
		mutex_lock(&dev->bus_mutex);
		अगर (w1_reset_bus(dev)) अणु
			mutex_unlock(&dev->bus_mutex);
			dev_dbg(&dev->dev, "No devices present on the wire.\n");
			अवरोध;
		पूर्ण

		/* Do fast search on single slave bus */
		अगर (dev->max_slave_count == 1) अणु
			पूर्णांक rv;
			w1_ग_लिखो_8(dev, W1_READ_ROM);
			rv = w1_पढ़ो_block(dev, (u8 *)&rn, 8);
			mutex_unlock(&dev->bus_mutex);

			अगर (rv == 8 && rn)
				cb(dev, rn);

			अवरोध;
		पूर्ण

		/* Start the search */
		w1_ग_लिखो_8(dev, search_type);
		क्रम (i = 0; i < 64; ++i) अणु
			/* Determine the direction/search bit */
			अगर (i == desc_bit)
				search_bit = 1;	  /* took the 0 path last समय, so take the 1 path */
			अन्यथा अगर (i > desc_bit)
				search_bit = 0;	  /* take the 0 path on the next branch */
			अन्यथा
				search_bit = ((last_rn >> i) & 0x1);

			/* Read two bits and ग_लिखो one bit */
			triplet_ret = w1_triplet(dev, search_bit);

			/* quit अगर no device responded */
			अगर ( (triplet_ret & 0x03) == 0x03 )
				अवरोध;

			/* If both directions were valid, and we took the 0 path... */
			अगर (triplet_ret == 0)
				last_zero = i;

			/* extract the direction taken & update the device number */
			पंचांगp64 = (triplet_ret >> 2);
			rn |= (पंचांगp64 << i);

			अगर (test_bit(W1_ABORT_SEARCH, &dev->flags)) अणु
				mutex_unlock(&dev->bus_mutex);
				dev_dbg(&dev->dev, "Abort w1_search\n");
				वापस;
			पूर्ण
		पूर्ण
		mutex_unlock(&dev->bus_mutex);

		अगर ( (triplet_ret & 0x03) != 0x03 ) अणु
			अगर ((desc_bit == last_zero) || (last_zero < 0)) अणु
				last_device = 1;
				dev->search_id = 0;
			पूर्ण अन्यथा अणु
				dev->search_id = rn;
			पूर्ण
			desc_bit = last_zero;
			cb(dev, rn);
		पूर्ण

		अगर (!last_device && slave_count == dev->max_slave_count &&
			!test_bit(W1_WARN_MAX_COUNT, &dev->flags)) अणु
			/* Only max_slave_count will be scanned in a search,
			 * but it will start where it left off next search
			 * until all ids are identअगरied and then it will start
			 * over.  A जारीd search will report the previous
			 * last id as the first id (provided it is still on the
			 * bus).
			 */
			dev_info(&dev->dev, "%s: max_slave_count %d reached, "
				"will continue next search.\n", __func__,
				dev->max_slave_count);
			set_bit(W1_WARN_MAX_COUNT, &dev->flags);
		पूर्ण
	पूर्ण
पूर्ण

व्योम w1_search_process_cb(काष्ठा w1_master *dev, u8 search_type,
	w1_slave_found_callback cb)
अणु
	काष्ठा w1_slave *sl, *sln;

	mutex_lock(&dev->list_mutex);
	list_क्रम_each_entry(sl, &dev->slist, w1_slave_entry)
		clear_bit(W1_SLAVE_ACTIVE, &sl->flags);
	mutex_unlock(&dev->list_mutex);

	w1_search_devices(dev, search_type, cb);

	mutex_lock(&dev->list_mutex);
	list_क्रम_each_entry_safe(sl, sln, &dev->slist, w1_slave_entry) अणु
		अगर (!test_bit(W1_SLAVE_ACTIVE, &sl->flags) && !--sl->ttl) अणु
			mutex_unlock(&dev->list_mutex);
			w1_slave_detach(sl);
			mutex_lock(&dev->list_mutex);
		पूर्ण
		अन्यथा अगर (test_bit(W1_SLAVE_ACTIVE, &sl->flags))
			sl->ttl = dev->slave_ttl;
	पूर्ण
	mutex_unlock(&dev->list_mutex);

	अगर (dev->search_count > 0)
		dev->search_count--;
पूर्ण

अटल व्योम w1_search_process(काष्ठा w1_master *dev, u8 search_type)
अणु
	w1_search_process_cb(dev, search_type, w1_slave_found);
पूर्ण

/**
 * w1_process_callbacks() - execute each dev->async_list callback entry
 * @dev: w1_master device
 *
 * The w1 master list_mutex must be held.
 *
 * Return: 1 अगर there were commands to executed 0 otherwise
 */
पूर्णांक w1_process_callbacks(काष्ठा w1_master *dev)
अणु
	पूर्णांक ret = 0;
	काष्ठा w1_async_cmd *async_cmd, *async_n;

	/* The list can be added to in another thपढ़ो, loop until it is empty */
	जबतक (!list_empty(&dev->async_list)) अणु
		list_क्रम_each_entry_safe(async_cmd, async_n, &dev->async_list,
			async_entry) अणु
			/* drop the lock, अगर it is a search it can take a दीर्घ
			 * समय */
			mutex_unlock(&dev->list_mutex);
			async_cmd->cb(dev, async_cmd);
			ret = 1;
			mutex_lock(&dev->list_mutex);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक w1_process(व्योम *data)
अणु
	काष्ठा w1_master *dev = (काष्ठा w1_master *) data;
	/* As दीर्घ as w1_समयout is only set by a module parameter the sleep
	 * समय can be calculated in jअगरfies once.
	 */
	स्थिर अचिन्हित दीर्घ jसमय =
	  usecs_to_jअगरfies(w1_समयout * 1000000 + w1_समयout_us);
	/* reमुख्यder अगर it woke up early */
	अचिन्हित दीर्घ jreमुख्य = 0;

	क्रम (;;) अणु

		अगर (!jreमुख्य && dev->search_count) अणु
			mutex_lock(&dev->mutex);
			w1_search_process(dev, W1_SEARCH);
			mutex_unlock(&dev->mutex);
		पूर्ण

		mutex_lock(&dev->list_mutex);
		/* Note, w1_process_callback drops the lock जबतक processing,
		 * but locks it again beक्रमe वापसing.
		 */
		अगर (!w1_process_callbacks(dev) && jreमुख्य) अणु
			/* a wake up is either to stop the thपढ़ो, process
			 * callbacks, or search, it isn't process callbacks, so
			 * schedule a search.
			 */
			jreमुख्य = 1;
		पूर्ण

		__set_current_state(TASK_INTERRUPTIBLE);

		/* hold list_mutex until after पूर्णांकerruptible to prevent loosing
		 * the wakeup संकेत when async_cmd is added.
		 */
		mutex_unlock(&dev->list_mutex);

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		/* Only sleep when the search is active. */
		अगर (dev->search_count) अणु
			अगर (!jreमुख्य)
				jreमुख्य = jसमय;
			jreमुख्य = schedule_समयout(jreमुख्य);
		पूर्ण
		अन्यथा
			schedule();
	पूर्ण

	atomic_dec(&dev->refcnt);

	वापस 0;
पूर्ण

अटल पूर्णांक __init w1_init(व्योम)
अणु
	पूर्णांक retval;

	pr_info("Driver for 1-wire Dallas network protocol.\n");

	w1_init_netlink();

	retval = bus_रेजिस्टर(&w1_bus_type);
	अगर (retval) अणु
		pr_err("Failed to register bus. err=%d.\n", retval);
		जाओ err_out_निकास_init;
	पूर्ण

	retval = driver_रेजिस्टर(&w1_master_driver);
	अगर (retval) अणु
		pr_err("Failed to register master driver. err=%d.\n",
			retval);
		जाओ err_out_bus_unरेजिस्टर;
	पूर्ण

	retval = driver_रेजिस्टर(&w1_slave_driver);
	अगर (retval) अणु
		pr_err("Failed to register slave driver. err=%d.\n",
			retval);
		जाओ err_out_master_unरेजिस्टर;
	पूर्ण

	वापस 0;

#अगर 0
/* For unकरोing the slave रेजिस्टर अगर there was a step after it. */
err_out_slave_unरेजिस्टर:
	driver_unरेजिस्टर(&w1_slave_driver);
#पूर्ण_अगर

err_out_master_unरेजिस्टर:
	driver_unरेजिस्टर(&w1_master_driver);

err_out_bus_unरेजिस्टर:
	bus_unरेजिस्टर(&w1_bus_type);

err_out_निकास_init:
	वापस retval;
पूर्ण

अटल व्योम __निकास w1_fini(व्योम)
अणु
	काष्ठा w1_master *dev;

	/* Set netlink removal messages and some cleanup */
	list_क्रम_each_entry(dev, &w1_masters, w1_master_entry)
		__w1_हटाओ_master_device(dev);

	w1_fini_netlink();

	driver_unरेजिस्टर(&w1_slave_driver);
	driver_unरेजिस्टर(&w1_master_driver);
	bus_unरेजिस्टर(&w1_bus_type);
पूर्ण

module_init(w1_init);
module_निकास(w1_fini);

MODULE_AUTHOR("Evgeniy Polyakov <zbr@ioremap.net>");
MODULE_DESCRIPTION("Driver for 1-wire Dallas network protocol.");
MODULE_LICENSE("GPL");
