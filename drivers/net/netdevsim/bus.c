<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2017 Netronome Systems, Inc.
 * Copyright (C) 2019 Mellanox Technologies. All rights reserved
 */

#समावेश <linux/device.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश "netdevsim.h"

अटल DEFINE_IDA(nsim_bus_dev_ids);
अटल LIST_HEAD(nsim_bus_dev_list);
अटल DEFINE_MUTEX(nsim_bus_dev_list_lock);
अटल bool nsim_bus_enable;

अटल काष्ठा nsim_bus_dev *to_nsim_bus_dev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा nsim_bus_dev, dev);
पूर्ण

अटल पूर्णांक nsim_bus_dev_vfs_enable(काष्ठा nsim_bus_dev *nsim_bus_dev,
				   अचिन्हित पूर्णांक num_vfs)
अणु
	nsim_bus_dev->vfconfigs = kसुस्मृति(num_vfs,
					  माप(काष्ठा nsim_vf_config),
					  GFP_KERNEL | __GFP_NOWARN);
	अगर (!nsim_bus_dev->vfconfigs)
		वापस -ENOMEM;
	nsim_bus_dev->num_vfs = num_vfs;

	वापस 0;
पूर्ण

अटल व्योम nsim_bus_dev_vfs_disable(काष्ठा nsim_bus_dev *nsim_bus_dev)
अणु
	kमुक्त(nsim_bus_dev->vfconfigs);
	nsim_bus_dev->vfconfigs = शून्य;
	nsim_bus_dev->num_vfs = 0;
पूर्ण

अटल sमाप_प्रकार
nsim_bus_dev_numvfs_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	अचिन्हित पूर्णांक num_vfs;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &num_vfs);
	अगर (ret)
		वापस ret;

	rtnl_lock();
	अगर (nsim_bus_dev->num_vfs == num_vfs)
		जाओ निकास_good;
	अगर (nsim_bus_dev->num_vfs && num_vfs) अणु
		ret = -EBUSY;
		जाओ निकास_unlock;
	पूर्ण

	अगर (num_vfs) अणु
		ret = nsim_bus_dev_vfs_enable(nsim_bus_dev, num_vfs);
		अगर (ret)
			जाओ निकास_unlock;
	पूर्ण अन्यथा अणु
		nsim_bus_dev_vfs_disable(nsim_bus_dev);
	पूर्ण
निकास_good:
	ret = count;
निकास_unlock:
	rtnl_unlock();

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
nsim_bus_dev_numvfs_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	वापस प्र_लिखो(buf, "%u\n", nsim_bus_dev->num_vfs);
पूर्ण

अटल काष्ठा device_attribute nsim_bus_dev_numvfs_attr =
	__ATTR(sriov_numvfs, 0664, nsim_bus_dev_numvfs_show,
	       nsim_bus_dev_numvfs_store);

अटल sमाप_प्रकार
new_port_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	काष्ठा nsim_dev *nsim_dev = dev_get_drvdata(dev);
	काष्ठा devlink *devlink;
	अचिन्हित पूर्णांक port_index;
	पूर्णांक ret;

	/* Prevent to use nsim_bus_dev beक्रमe initialization. */
	अगर (!smp_load_acquire(&nsim_bus_dev->init))
		वापस -EBUSY;
	ret = kstrtouपूर्णांक(buf, 0, &port_index);
	अगर (ret)
		वापस ret;

	devlink = priv_to_devlink(nsim_dev);

	mutex_lock(&nsim_bus_dev->nsim_bus_reload_lock);
	devlink_reload_disable(devlink);
	ret = nsim_dev_port_add(nsim_bus_dev, port_index);
	devlink_reload_enable(devlink);
	mutex_unlock(&nsim_bus_dev->nsim_bus_reload_lock);
	वापस ret ? ret : count;
पूर्ण

अटल काष्ठा device_attribute nsim_bus_dev_new_port_attr = __ATTR_WO(new_port);

अटल sमाप_प्रकार
del_port_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
	       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	काष्ठा nsim_dev *nsim_dev = dev_get_drvdata(dev);
	काष्ठा devlink *devlink;
	अचिन्हित पूर्णांक port_index;
	पूर्णांक ret;

	/* Prevent to use nsim_bus_dev beक्रमe initialization. */
	अगर (!smp_load_acquire(&nsim_bus_dev->init))
		वापस -EBUSY;
	ret = kstrtouपूर्णांक(buf, 0, &port_index);
	अगर (ret)
		वापस ret;

	devlink = priv_to_devlink(nsim_dev);

	mutex_lock(&nsim_bus_dev->nsim_bus_reload_lock);
	devlink_reload_disable(devlink);
	ret = nsim_dev_port_del(nsim_bus_dev, port_index);
	devlink_reload_enable(devlink);
	mutex_unlock(&nsim_bus_dev->nsim_bus_reload_lock);
	वापस ret ? ret : count;
पूर्ण

अटल काष्ठा device_attribute nsim_bus_dev_del_port_attr = __ATTR_WO(del_port);

अटल काष्ठा attribute *nsim_bus_dev_attrs[] = अणु
	&nsim_bus_dev_numvfs_attr.attr,
	&nsim_bus_dev_new_port_attr.attr,
	&nsim_bus_dev_del_port_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group nsim_bus_dev_attr_group = अणु
	.attrs = nsim_bus_dev_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nsim_bus_dev_attr_groups[] = अणु
	&nsim_bus_dev_attr_group,
	शून्य,
पूर्ण;

अटल व्योम nsim_bus_dev_release(काष्ठा device *dev)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	nsim_bus_dev_vfs_disable(nsim_bus_dev);
पूर्ण

अटल काष्ठा device_type nsim_bus_dev_type = अणु
	.groups = nsim_bus_dev_attr_groups,
	.release = nsim_bus_dev_release,
पूर्ण;

अटल काष्ठा nsim_bus_dev *
nsim_bus_dev_new(अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक port_count);

अटल sमाप_प्रकार
new_device_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev;
	अचिन्हित पूर्णांक port_count;
	अचिन्हित पूर्णांक id;
	पूर्णांक err;

	err = माला_पूछो(buf, "%u %u", &id, &port_count);
	चयन (err) अणु
	हाल 1:
		port_count = 1;
		fallthrough;
	हाल 2:
		अगर (id > पूर्णांक_उच्च) अणु
			pr_err("Value of \"id\" is too big.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("Format for adding new device is \"id port_count\" (uint uint).\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&nsim_bus_dev_list_lock);
	/* Prevent to use resource beक्रमe initialization. */
	अगर (!smp_load_acquire(&nsim_bus_enable)) अणु
		err = -EBUSY;
		जाओ err;
	पूर्ण

	nsim_bus_dev = nsim_bus_dev_new(id, port_count);
	अगर (IS_ERR(nsim_bus_dev)) अणु
		err = PTR_ERR(nsim_bus_dev);
		जाओ err;
	पूर्ण

	/* Allow using nsim_bus_dev */
	smp_store_release(&nsim_bus_dev->init, true);

	list_add_tail(&nsim_bus_dev->list, &nsim_bus_dev_list);
	mutex_unlock(&nsim_bus_dev_list_lock);

	वापस count;
err:
	mutex_unlock(&nsim_bus_dev_list_lock);
	वापस err;
पूर्ण
अटल BUS_ATTR_WO(new_device);

अटल व्योम nsim_bus_dev_del(काष्ठा nsim_bus_dev *nsim_bus_dev);

अटल sमाप_प्रकार
del_device_store(काष्ठा bus_type *bus, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev, *पंचांगp;
	अचिन्हित पूर्णांक id;
	पूर्णांक err;

	err = माला_पूछो(buf, "%u", &id);
	चयन (err) अणु
	हाल 1:
		अगर (id > पूर्णांक_उच्च) अणु
			pr_err("Value of \"id\" is too big.\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		pr_err("Format for deleting device is \"id\" (uint).\n");
		वापस -EINVAL;
	पूर्ण

	err = -ENOENT;
	mutex_lock(&nsim_bus_dev_list_lock);
	/* Prevent to use resource beक्रमe initialization. */
	अगर (!smp_load_acquire(&nsim_bus_enable)) अणु
		mutex_unlock(&nsim_bus_dev_list_lock);
		वापस -EBUSY;
	पूर्ण
	list_क्रम_each_entry_safe(nsim_bus_dev, पंचांगp, &nsim_bus_dev_list, list) अणु
		अगर (nsim_bus_dev->dev.id != id)
			जारी;
		list_del(&nsim_bus_dev->list);
		nsim_bus_dev_del(nsim_bus_dev);
		err = 0;
		अवरोध;
	पूर्ण
	mutex_unlock(&nsim_bus_dev_list_lock);
	वापस !err ? count : err;
पूर्ण
अटल BUS_ATTR_WO(del_device);

अटल काष्ठा attribute *nsim_bus_attrs[] = अणु
	&bus_attr_new_device.attr,
	&bus_attr_del_device.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(nsim_bus);

अटल पूर्णांक nsim_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	वापस nsim_dev_probe(nsim_bus_dev);
पूर्ण

अटल पूर्णांक nsim_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	nsim_dev_हटाओ(nsim_bus_dev);
	वापस 0;
पूर्ण

अटल पूर्णांक nsim_num_vf(काष्ठा device *dev)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	वापस nsim_bus_dev->num_vfs;
पूर्ण

अटल काष्ठा bus_type nsim_bus = अणु
	.name		= DRV_NAME,
	.dev_name	= DRV_NAME,
	.bus_groups	= nsim_bus_groups,
	.probe		= nsim_bus_probe,
	.हटाओ		= nsim_bus_हटाओ,
	.num_vf		= nsim_num_vf,
पूर्ण;

अटल काष्ठा nsim_bus_dev *
nsim_bus_dev_new(अचिन्हित पूर्णांक id, अचिन्हित पूर्णांक port_count)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev;
	पूर्णांक err;

	nsim_bus_dev = kzalloc(माप(*nsim_bus_dev), GFP_KERNEL);
	अगर (!nsim_bus_dev)
		वापस ERR_PTR(-ENOMEM);

	err = ida_alloc_range(&nsim_bus_dev_ids, id, id, GFP_KERNEL);
	अगर (err < 0)
		जाओ err_nsim_bus_dev_मुक्त;
	nsim_bus_dev->dev.id = err;
	nsim_bus_dev->dev.bus = &nsim_bus;
	nsim_bus_dev->dev.type = &nsim_bus_dev_type;
	nsim_bus_dev->port_count = port_count;
	nsim_bus_dev->initial_net = current->nsproxy->net_ns;
	mutex_init(&nsim_bus_dev->nsim_bus_reload_lock);
	/* Disallow using nsim_bus_dev */
	smp_store_release(&nsim_bus_dev->init, false);

	err = device_रेजिस्टर(&nsim_bus_dev->dev);
	अगर (err)
		जाओ err_nsim_bus_dev_id_मुक्त;
	वापस nsim_bus_dev;

err_nsim_bus_dev_id_मुक्त:
	ida_मुक्त(&nsim_bus_dev_ids, nsim_bus_dev->dev.id);
err_nsim_bus_dev_मुक्त:
	kमुक्त(nsim_bus_dev);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम nsim_bus_dev_del(काष्ठा nsim_bus_dev *nsim_bus_dev)
अणु
	/* Disallow using nsim_bus_dev */
	smp_store_release(&nsim_bus_dev->init, false);
	device_unरेजिस्टर(&nsim_bus_dev->dev);
	ida_मुक्त(&nsim_bus_dev_ids, nsim_bus_dev->dev.id);
	kमुक्त(nsim_bus_dev);
पूर्ण

अटल काष्ठा device_driver nsim_driver = अणु
	.name		= DRV_NAME,
	.bus		= &nsim_bus,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक nsim_bus_init(व्योम)
अणु
	पूर्णांक err;

	err = bus_रेजिस्टर(&nsim_bus);
	अगर (err)
		वापस err;
	err = driver_रेजिस्टर(&nsim_driver);
	अगर (err)
		जाओ err_bus_unरेजिस्टर;
	/* Allow using resources */
	smp_store_release(&nsim_bus_enable, true);
	वापस 0;

err_bus_unरेजिस्टर:
	bus_unरेजिस्टर(&nsim_bus);
	वापस err;
पूर्ण

व्योम nsim_bus_निकास(व्योम)
अणु
	काष्ठा nsim_bus_dev *nsim_bus_dev, *पंचांगp;

	/* Disallow using resources */
	smp_store_release(&nsim_bus_enable, false);

	mutex_lock(&nsim_bus_dev_list_lock);
	list_क्रम_each_entry_safe(nsim_bus_dev, पंचांगp, &nsim_bus_dev_list, list) अणु
		list_del(&nsim_bus_dev->list);
		nsim_bus_dev_del(nsim_bus_dev);
	पूर्ण
	mutex_unlock(&nsim_bus_dev_list_lock);

	driver_unरेजिस्टर(&nsim_driver);
	bus_unरेजिस्टर(&nsim_bus);
पूर्ण
