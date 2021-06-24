<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/uio/uio.c
 *
 * Copyright(C) 2005, Benedikt Spranger <b.spranger@linutronix.de>
 * Copyright(C) 2005, Thomas Gleixner <tglx@linutronix.de>
 * Copyright(C) 2006, Hans J. Koch <hjk@hansjkoch.de>
 * Copyright(C) 2006, Greg Kroah-Harपंचांगan <greg@kroah.com>
 *
 * Userspace IO
 *
 * Base Functions
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/idr.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/kobject.h>
#समावेश <linux/cdev.h>
#समावेश <linux/uio_driver.h>

#घोषणा UIO_MAX_DEVICES		(1U << MINORBITS)

अटल पूर्णांक uio_major;
अटल काष्ठा cdev *uio_cdev;
अटल DEFINE_IDR(uio_idr);
अटल स्थिर काष्ठा file_operations uio_fops;

/* Protect idr accesses */
अटल DEFINE_MUTEX(minor_lock);

/*
 * attributes
 */

काष्ठा uio_map अणु
	काष्ठा kobject kobj;
	काष्ठा uio_mem *mem;
पूर्ण;
#घोषणा to_map(map) container_of(map, काष्ठा uio_map, kobj)

अटल sमाप_प्रकार map_name_show(काष्ठा uio_mem *mem, अक्षर *buf)
अणु
	अगर (unlikely(!mem->name))
		mem->name = "";

	वापस प्र_लिखो(buf, "%s\n", mem->name);
पूर्ण

अटल sमाप_प्रकार map_addr_show(काष्ठा uio_mem *mem, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%pa\n", &mem->addr);
पूर्ण

अटल sमाप_प्रकार map_size_show(काष्ठा uio_mem *mem, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%pa\n", &mem->size);
पूर्ण

अटल sमाप_प्रकार map_offset_show(काष्ठा uio_mem *mem, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%llx\n", (अचिन्हित दीर्घ दीर्घ)mem->offs);
पूर्ण

काष्ठा map_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा uio_mem *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा uio_mem *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल काष्ठा map_sysfs_entry name_attribute =
	__ATTR(name, S_IRUGO, map_name_show, शून्य);
अटल काष्ठा map_sysfs_entry addr_attribute =
	__ATTR(addr, S_IRUGO, map_addr_show, शून्य);
अटल काष्ठा map_sysfs_entry size_attribute =
	__ATTR(size, S_IRUGO, map_size_show, शून्य);
अटल काष्ठा map_sysfs_entry offset_attribute =
	__ATTR(offset, S_IRUGO, map_offset_show, शून्य);

अटल काष्ठा attribute *attrs[] = अणु
	&name_attribute.attr,
	&addr_attribute.attr,
	&size_attribute.attr,
	&offset_attribute.attr,
	शून्य,	/* need to शून्य terminate the list of attributes */
पूर्ण;

अटल व्योम map_release(काष्ठा kobject *kobj)
अणु
	काष्ठा uio_map *map = to_map(kobj);
	kमुक्त(map);
पूर्ण

अटल sमाप_प्रकार map_type_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा uio_map *map = to_map(kobj);
	काष्ठा uio_mem *mem = map->mem;
	काष्ठा map_sysfs_entry *entry;

	entry = container_of(attr, काष्ठा map_sysfs_entry, attr);

	अगर (!entry->show)
		वापस -EIO;

	वापस entry->show(mem, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops map_sysfs_ops = अणु
	.show = map_type_show,
पूर्ण;

अटल काष्ठा kobj_type map_attr_type = अणु
	.release	= map_release,
	.sysfs_ops	= &map_sysfs_ops,
	.शेष_attrs	= attrs,
पूर्ण;

काष्ठा uio_portio अणु
	काष्ठा kobject kobj;
	काष्ठा uio_port *port;
पूर्ण;
#घोषणा to_portio(portio) container_of(portio, काष्ठा uio_portio, kobj)

अटल sमाप_प्रकार portio_name_show(काष्ठा uio_port *port, अक्षर *buf)
अणु
	अगर (unlikely(!port->name))
		port->name = "";

	वापस प्र_लिखो(buf, "%s\n", port->name);
पूर्ण

अटल sमाप_प्रकार portio_start_show(काष्ठा uio_port *port, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%lx\n", port->start);
पूर्ण

अटल sमाप_प्रकार portio_size_show(काष्ठा uio_port *port, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0x%lx\n", port->size);
पूर्ण

अटल sमाप_प्रकार portio_porttype_show(काष्ठा uio_port *port, अक्षर *buf)
अणु
	स्थिर अक्षर *porttypes[] = अणु"none", "x86", "gpio", "other"पूर्ण;

	अगर ((port->porttype < 0) || (port->porttype > UIO_PORT_OTHER))
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "port_%s\n", porttypes[port->porttype]);
पूर्ण

काष्ठा portio_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा uio_port *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा uio_port *, स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल काष्ठा portio_sysfs_entry portio_name_attribute =
	__ATTR(name, S_IRUGO, portio_name_show, शून्य);
अटल काष्ठा portio_sysfs_entry portio_start_attribute =
	__ATTR(start, S_IRUGO, portio_start_show, शून्य);
अटल काष्ठा portio_sysfs_entry portio_size_attribute =
	__ATTR(size, S_IRUGO, portio_size_show, शून्य);
अटल काष्ठा portio_sysfs_entry portio_porttype_attribute =
	__ATTR(porttype, S_IRUGO, portio_porttype_show, शून्य);

अटल काष्ठा attribute *portio_attrs[] = अणु
	&portio_name_attribute.attr,
	&portio_start_attribute.attr,
	&portio_size_attribute.attr,
	&portio_porttype_attribute.attr,
	शून्य,
पूर्ण;

अटल व्योम portio_release(काष्ठा kobject *kobj)
अणु
	काष्ठा uio_portio *portio = to_portio(kobj);
	kमुक्त(portio);
पूर्ण

अटल sमाप_प्रकार portio_type_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा uio_portio *portio = to_portio(kobj);
	काष्ठा uio_port *port = portio->port;
	काष्ठा portio_sysfs_entry *entry;

	entry = container_of(attr, काष्ठा portio_sysfs_entry, attr);

	अगर (!entry->show)
		वापस -EIO;

	वापस entry->show(port, buf);
पूर्ण

अटल स्थिर काष्ठा sysfs_ops portio_sysfs_ops = अणु
	.show = portio_type_show,
पूर्ण;

अटल काष्ठा kobj_type portio_attr_type = अणु
	.release	= portio_release,
	.sysfs_ops	= &portio_sysfs_ops,
	.शेष_attrs	= portio_attrs,
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uio_device *idev = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&idev->info_lock);
	अगर (!idev->info) अणु
		ret = -EINVAL;
		dev_err(dev, "the device has been unregistered\n");
		जाओ out;
	पूर्ण

	ret = प्र_लिखो(buf, "%s\n", idev->info->name);

out:
	mutex_unlock(&idev->info_lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार version_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uio_device *idev = dev_get_drvdata(dev);
	पूर्णांक ret;

	mutex_lock(&idev->info_lock);
	अगर (!idev->info) अणु
		ret = -EINVAL;
		dev_err(dev, "the device has been unregistered\n");
		जाओ out;
	पूर्ण

	ret = प्र_लिखो(buf, "%s\n", idev->info->version);

out:
	mutex_unlock(&idev->info_lock);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(version);

अटल sमाप_प्रकार event_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uio_device *idev = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%u\n", (अचिन्हित पूर्णांक)atomic_पढ़ो(&idev->event));
पूर्ण
अटल DEVICE_ATTR_RO(event);

अटल काष्ठा attribute *uio_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_version.attr,
	&dev_attr_event.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(uio);

/* UIO class infraकाष्ठाure */
अटल काष्ठा class uio_class = अणु
	.name = "uio",
	.dev_groups = uio_groups,
पूर्ण;

अटल bool uio_class_रेजिस्टरed;

/*
 * device functions
 */
अटल पूर्णांक uio_dev_add_attributes(काष्ठा uio_device *idev)
अणु
	पूर्णांक ret;
	पूर्णांक mi, pi;
	पूर्णांक map_found = 0;
	पूर्णांक portio_found = 0;
	काष्ठा uio_mem *mem;
	काष्ठा uio_map *map;
	काष्ठा uio_port *port;
	काष्ठा uio_portio *portio;

	क्रम (mi = 0; mi < MAX_UIO_MAPS; mi++) अणु
		mem = &idev->info->mem[mi];
		अगर (mem->size == 0)
			अवरोध;
		अगर (!map_found) अणु
			map_found = 1;
			idev->map_dir = kobject_create_and_add("maps",
							&idev->dev.kobj);
			अगर (!idev->map_dir) अणु
				ret = -ENOMEM;
				जाओ err_map;
			पूर्ण
		पूर्ण
		map = kzalloc(माप(*map), GFP_KERNEL);
		अगर (!map) अणु
			ret = -ENOMEM;
			जाओ err_map;
		पूर्ण
		kobject_init(&map->kobj, &map_attr_type);
		map->mem = mem;
		mem->map = map;
		ret = kobject_add(&map->kobj, idev->map_dir, "map%d", mi);
		अगर (ret)
			जाओ err_map_kobj;
		ret = kobject_uevent(&map->kobj, KOBJ_ADD);
		अगर (ret)
			जाओ err_map_kobj;
	पूर्ण

	क्रम (pi = 0; pi < MAX_UIO_PORT_REGIONS; pi++) अणु
		port = &idev->info->port[pi];
		अगर (port->size == 0)
			अवरोध;
		अगर (!portio_found) अणु
			portio_found = 1;
			idev->portio_dir = kobject_create_and_add("portio",
							&idev->dev.kobj);
			अगर (!idev->portio_dir) अणु
				ret = -ENOMEM;
				जाओ err_portio;
			पूर्ण
		पूर्ण
		portio = kzalloc(माप(*portio), GFP_KERNEL);
		अगर (!portio) अणु
			ret = -ENOMEM;
			जाओ err_portio;
		पूर्ण
		kobject_init(&portio->kobj, &portio_attr_type);
		portio->port = port;
		port->portio = portio;
		ret = kobject_add(&portio->kobj, idev->portio_dir,
							"port%d", pi);
		अगर (ret)
			जाओ err_portio_kobj;
		ret = kobject_uevent(&portio->kobj, KOBJ_ADD);
		अगर (ret)
			जाओ err_portio_kobj;
	पूर्ण

	वापस 0;

err_portio:
	pi--;
err_portio_kobj:
	क्रम (; pi >= 0; pi--) अणु
		port = &idev->info->port[pi];
		portio = port->portio;
		kobject_put(&portio->kobj);
	पूर्ण
	kobject_put(idev->portio_dir);
err_map:
	mi--;
err_map_kobj:
	क्रम (; mi >= 0; mi--) अणु
		mem = &idev->info->mem[mi];
		map = mem->map;
		kobject_put(&map->kobj);
	पूर्ण
	kobject_put(idev->map_dir);
	dev_err(&idev->dev, "error creating sysfs files (%d)\n", ret);
	वापस ret;
पूर्ण

अटल व्योम uio_dev_del_attributes(काष्ठा uio_device *idev)
अणु
	पूर्णांक i;
	काष्ठा uio_mem *mem;
	काष्ठा uio_port *port;

	क्रम (i = 0; i < MAX_UIO_MAPS; i++) अणु
		mem = &idev->info->mem[i];
		अगर (mem->size == 0)
			अवरोध;
		kobject_put(&mem->map->kobj);
	पूर्ण
	kobject_put(idev->map_dir);

	क्रम (i = 0; i < MAX_UIO_PORT_REGIONS; i++) अणु
		port = &idev->info->port[i];
		अगर (port->size == 0)
			अवरोध;
		kobject_put(&port->portio->kobj);
	पूर्ण
	kobject_put(idev->portio_dir);
पूर्ण

अटल पूर्णांक uio_get_minor(काष्ठा uio_device *idev)
अणु
	पूर्णांक retval;

	mutex_lock(&minor_lock);
	retval = idr_alloc(&uio_idr, idev, 0, UIO_MAX_DEVICES, GFP_KERNEL);
	अगर (retval >= 0) अणु
		idev->minor = retval;
		retval = 0;
	पूर्ण अन्यथा अगर (retval == -ENOSPC) अणु
		dev_err(&idev->dev, "too many uio devices\n");
		retval = -EINVAL;
	पूर्ण
	mutex_unlock(&minor_lock);
	वापस retval;
पूर्ण

अटल व्योम uio_मुक्त_minor(अचिन्हित दीर्घ minor)
अणु
	mutex_lock(&minor_lock);
	idr_हटाओ(&uio_idr, minor);
	mutex_unlock(&minor_lock);
पूर्ण

/**
 * uio_event_notअगरy - trigger an पूर्णांकerrupt event
 * @info: UIO device capabilities
 */
व्योम uio_event_notअगरy(काष्ठा uio_info *info)
अणु
	काष्ठा uio_device *idev = info->uio_dev;

	atomic_inc(&idev->event);
	wake_up_पूर्णांकerruptible(&idev->रुको);
	समाप्त_fasync(&idev->async_queue, SIGIO, POLL_IN);
पूर्ण
EXPORT_SYMBOL_GPL(uio_event_notअगरy);

/**
 * uio_पूर्णांकerrupt - hardware पूर्णांकerrupt handler
 * @irq: IRQ number, can be UIO_IRQ_CYCLIC क्रम cyclic समयr
 * @dev_id: Poपूर्णांकer to the devices uio_device काष्ठाure
 */
अटल irqवापस_t uio_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uio_device *idev = (काष्ठा uio_device *)dev_id;
	irqवापस_t ret;

	ret = idev->info->handler(irq, idev->info);
	अगर (ret == IRQ_HANDLED)
		uio_event_notअगरy(idev->info);

	वापस ret;
पूर्ण

काष्ठा uio_listener अणु
	काष्ठा uio_device *dev;
	s32 event_count;
पूर्ण;

अटल पूर्णांक uio_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा uio_device *idev;
	काष्ठा uio_listener *listener;
	पूर्णांक ret = 0;

	mutex_lock(&minor_lock);
	idev = idr_find(&uio_idr, iminor(inode));
	mutex_unlock(&minor_lock);
	अगर (!idev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	get_device(&idev->dev);

	अगर (!try_module_get(idev->owner)) अणु
		ret = -ENODEV;
		जाओ err_module_get;
	पूर्ण

	listener = kदो_स्मृति(माप(*listener), GFP_KERNEL);
	अगर (!listener) अणु
		ret = -ENOMEM;
		जाओ err_alloc_listener;
	पूर्ण

	listener->dev = idev;
	listener->event_count = atomic_पढ़ो(&idev->event);
	filep->निजी_data = listener;

	mutex_lock(&idev->info_lock);
	अगर (!idev->info) अणु
		mutex_unlock(&idev->info_lock);
		ret = -EINVAL;
		जाओ err_infoखोलो;
	पूर्ण

	अगर (idev->info->खोलो)
		ret = idev->info->खोलो(idev->info, inode);
	mutex_unlock(&idev->info_lock);
	अगर (ret)
		जाओ err_infoखोलो;

	वापस 0;

err_infoखोलो:
	kमुक्त(listener);

err_alloc_listener:
	module_put(idev->owner);

err_module_get:
	put_device(&idev->dev);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक uio_fasync(पूर्णांक fd, काष्ठा file *filep, पूर्णांक on)
अणु
	काष्ठा uio_listener *listener = filep->निजी_data;
	काष्ठा uio_device *idev = listener->dev;

	वापस fasync_helper(fd, filep, on, &idev->async_queue);
पूर्ण

अटल पूर्णांक uio_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	पूर्णांक ret = 0;
	काष्ठा uio_listener *listener = filep->निजी_data;
	काष्ठा uio_device *idev = listener->dev;

	mutex_lock(&idev->info_lock);
	अगर (idev->info && idev->info->release)
		ret = idev->info->release(idev->info, inode);
	mutex_unlock(&idev->info_lock);

	module_put(idev->owner);
	kमुक्त(listener);
	put_device(&idev->dev);
	वापस ret;
पूर्ण

अटल __poll_t uio_poll(काष्ठा file *filep, poll_table *रुको)
अणु
	काष्ठा uio_listener *listener = filep->निजी_data;
	काष्ठा uio_device *idev = listener->dev;
	__poll_t ret = 0;

	mutex_lock(&idev->info_lock);
	अगर (!idev->info || !idev->info->irq)
		ret = -EIO;
	mutex_unlock(&idev->info_lock);

	अगर (ret)
		वापस ret;

	poll_रुको(filep, &idev->रुको, रुको);
	अगर (listener->event_count != atomic_पढ़ो(&idev->event))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार uio_पढ़ो(काष्ठा file *filep, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uio_listener *listener = filep->निजी_data;
	काष्ठा uio_device *idev = listener->dev;
	DECLARE_WAITQUEUE(रुको, current);
	sमाप_प्रकार retval = 0;
	s32 event_count;

	अगर (count != माप(s32))
		वापस -EINVAL;

	add_रुको_queue(&idev->रुको, &रुको);

	करो अणु
		mutex_lock(&idev->info_lock);
		अगर (!idev->info || !idev->info->irq) अणु
			retval = -EIO;
			mutex_unlock(&idev->info_lock);
			अवरोध;
		पूर्ण
		mutex_unlock(&idev->info_lock);

		set_current_state(TASK_INTERRUPTIBLE);

		event_count = atomic_पढ़ो(&idev->event);
		अगर (event_count != listener->event_count) अणु
			__set_current_state(TASK_RUNNING);
			अगर (copy_to_user(buf, &event_count, count))
				retval = -EFAULT;
			अन्यथा अणु
				listener->event_count = event_count;
				retval = count;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (filep->f_flags & O_NONBLOCK) अणु
			retval = -EAGAIN;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			retval = -ERESTARTSYS;
			अवरोध;
		पूर्ण
		schedule();
	पूर्ण जबतक (1);

	__set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(&idev->रुको, &रुको);

	वापस retval;
पूर्ण

अटल sमाप_प्रकार uio_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा uio_listener *listener = filep->निजी_data;
	काष्ठा uio_device *idev = listener->dev;
	sमाप_प्रकार retval;
	s32 irq_on;

	अगर (count != माप(s32))
		वापस -EINVAL;

	अगर (copy_from_user(&irq_on, buf, count))
		वापस -EFAULT;

	mutex_lock(&idev->info_lock);
	अगर (!idev->info) अणु
		retval = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!idev->info->irq) अणु
		retval = -EIO;
		जाओ out;
	पूर्ण

	अगर (!idev->info->irqcontrol) अणु
		retval = -ENOSYS;
		जाओ out;
	पूर्ण

	retval = idev->info->irqcontrol(idev->info, irq_on);

out:
	mutex_unlock(&idev->info_lock);
	वापस retval ? retval : माप(s32);
पूर्ण

अटल पूर्णांक uio_find_mem_index(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा uio_device *idev = vma->vm_निजी_data;

	अगर (vma->vm_pgoff < MAX_UIO_MAPS) अणु
		अगर (idev->info->mem[vma->vm_pgoff].size == 0)
			वापस -1;
		वापस (पूर्णांक)vma->vm_pgoff;
	पूर्ण
	वापस -1;
पूर्ण

अटल vm_fault_t uio_vma_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा uio_device *idev = vmf->vma->vm_निजी_data;
	काष्ठा page *page;
	अचिन्हित दीर्घ offset;
	व्योम *addr;
	vm_fault_t ret = 0;
	पूर्णांक mi;

	mutex_lock(&idev->info_lock);
	अगर (!idev->info) अणु
		ret = VM_FAULT_SIGBUS;
		जाओ out;
	पूर्ण

	mi = uio_find_mem_index(vmf->vma);
	अगर (mi < 0) अणु
		ret = VM_FAULT_SIGBUS;
		जाओ out;
	पूर्ण

	/*
	 * We need to subtract mi because userspace uses offset = N*PAGE_SIZE
	 * to use mem[N].
	 */
	offset = (vmf->pgoff - mi) << PAGE_SHIFT;

	addr = (व्योम *)(अचिन्हित दीर्घ)idev->info->mem[mi].addr + offset;
	अगर (idev->info->mem[mi].memtype == UIO_MEM_LOGICAL)
		page = virt_to_page(addr);
	अन्यथा
		page = vदो_स्मृति_to_page(addr);
	get_page(page);
	vmf->page = page;

out:
	mutex_unlock(&idev->info_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा uio_logical_vm_ops = अणु
	.fault = uio_vma_fault,
पूर्ण;

अटल पूर्णांक uio_mmap_logical(काष्ठा vm_area_काष्ठा *vma)
अणु
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_ops = &uio_logical_vm_ops;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा uio_physical_vm_ops = अणु
#अगर_घोषित CONFIG_HAVE_IOREMAP_PROT
	.access = generic_access_phys,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक uio_mmap_physical(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा uio_device *idev = vma->vm_निजी_data;
	पूर्णांक mi = uio_find_mem_index(vma);
	काष्ठा uio_mem *mem;

	अगर (mi < 0)
		वापस -EINVAL;
	mem = idev->info->mem + mi;

	अगर (mem->addr & ~PAGE_MASK)
		वापस -ENODEV;
	अगर (vma->vm_end - vma->vm_start > mem->size)
		वापस -EINVAL;

	vma->vm_ops = &uio_physical_vm_ops;
	अगर (idev->info->mem[mi].memtype == UIO_MEM_PHYS)
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	/*
	 * We cannot use the vm_iomap_memory() helper here,
	 * because vma->vm_pgoff is the map index we looked
	 * up above in uio_find_mem_index(), rather than an
	 * actual page offset पूर्णांकo the mmap.
	 *
	 * So we just करो the physical mmap without a page
	 * offset.
	 */
	वापस remap_pfn_range(vma,
			       vma->vm_start,
			       mem->addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
पूर्ण

अटल पूर्णांक uio_mmap(काष्ठा file *filep, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा uio_listener *listener = filep->निजी_data;
	काष्ठा uio_device *idev = listener->dev;
	पूर्णांक mi;
	अचिन्हित दीर्घ requested_pages, actual_pages;
	पूर्णांक ret = 0;

	अगर (vma->vm_end < vma->vm_start)
		वापस -EINVAL;

	vma->vm_निजी_data = idev;

	mutex_lock(&idev->info_lock);
	अगर (!idev->info) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	mi = uio_find_mem_index(vma);
	अगर (mi < 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	requested_pages = vma_pages(vma);
	actual_pages = ((idev->info->mem[mi].addr & ~PAGE_MASK)
			+ idev->info->mem[mi].size + PAGE_SIZE -1) >> PAGE_SHIFT;
	अगर (requested_pages > actual_pages) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (idev->info->mmap) अणु
		ret = idev->info->mmap(idev->info, vma);
		जाओ out;
	पूर्ण

	चयन (idev->info->mem[mi].memtype) अणु
	हाल UIO_MEM_IOVA:
	हाल UIO_MEM_PHYS:
		ret = uio_mmap_physical(vma);
		अवरोध;
	हाल UIO_MEM_LOGICAL:
	हाल UIO_MEM_VIRTUAL:
		ret = uio_mmap_logical(vma);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

 out:
	mutex_unlock(&idev->info_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations uio_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= uio_खोलो,
	.release	= uio_release,
	.पढ़ो		= uio_पढ़ो,
	.ग_लिखो		= uio_ग_लिखो,
	.mmap		= uio_mmap,
	.poll		= uio_poll,
	.fasync		= uio_fasync,
	.llseek		= noop_llseek,
पूर्ण;

अटल पूर्णांक uio_major_init(व्योम)
अणु
	अटल स्थिर अक्षर name[] = "uio";
	काष्ठा cdev *cdev = शून्य;
	dev_t uio_dev = 0;
	पूर्णांक result;

	result = alloc_chrdev_region(&uio_dev, 0, UIO_MAX_DEVICES, name);
	अगर (result)
		जाओ out;

	result = -ENOMEM;
	cdev = cdev_alloc();
	अगर (!cdev)
		जाओ out_unरेजिस्टर;

	cdev->owner = THIS_MODULE;
	cdev->ops = &uio_fops;
	kobject_set_name(&cdev->kobj, "%s", name);

	result = cdev_add(cdev, uio_dev, UIO_MAX_DEVICES);
	अगर (result)
		जाओ out_put;

	uio_major = MAJOR(uio_dev);
	uio_cdev = cdev;
	वापस 0;
out_put:
	kobject_put(&cdev->kobj);
out_unरेजिस्टर:
	unरेजिस्टर_chrdev_region(uio_dev, UIO_MAX_DEVICES);
out:
	वापस result;
पूर्ण

अटल व्योम uio_major_cleanup(व्योम)
अणु
	unरेजिस्टर_chrdev_region(MKDEV(uio_major, 0), UIO_MAX_DEVICES);
	cdev_del(uio_cdev);
पूर्ण

अटल पूर्णांक init_uio_class(व्योम)
अणु
	पूर्णांक ret;

	/* This is the first समय in here, set everything up properly */
	ret = uio_major_init();
	अगर (ret)
		जाओ निकास;

	ret = class_रेजिस्टर(&uio_class);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "class_register failed for uio\n");
		जाओ err_class_रेजिस्टर;
	पूर्ण

	uio_class_रेजिस्टरed = true;

	वापस 0;

err_class_रेजिस्टर:
	uio_major_cleanup();
निकास:
	वापस ret;
पूर्ण

अटल व्योम release_uio_class(व्योम)
अणु
	uio_class_रेजिस्टरed = false;
	class_unरेजिस्टर(&uio_class);
	uio_major_cleanup();
पूर्ण

अटल व्योम uio_device_release(काष्ठा device *dev)
अणु
	काष्ठा uio_device *idev = dev_get_drvdata(dev);

	kमुक्त(idev);
पूर्ण

/**
 * __uio_रेजिस्टर_device - रेजिस्टर a new userspace IO device
 * @owner:	module that creates the new device
 * @parent:	parent device
 * @info:	UIO device capabilities
 *
 * वापसs zero on success or a negative error code.
 */
पूर्णांक __uio_रेजिस्टर_device(काष्ठा module *owner,
			  काष्ठा device *parent,
			  काष्ठा uio_info *info)
अणु
	काष्ठा uio_device *idev;
	पूर्णांक ret = 0;

	अगर (!uio_class_रेजिस्टरed)
		वापस -EPROBE_DEFER;

	अगर (!parent || !info || !info->name || !info->version)
		वापस -EINVAL;

	info->uio_dev = शून्य;

	idev = kzalloc(माप(*idev), GFP_KERNEL);
	अगर (!idev) अणु
		वापस -ENOMEM;
	पूर्ण

	idev->owner = owner;
	idev->info = info;
	mutex_init(&idev->info_lock);
	init_रुकोqueue_head(&idev->रुको);
	atomic_set(&idev->event, 0);

	ret = uio_get_minor(idev);
	अगर (ret) अणु
		kमुक्त(idev);
		वापस ret;
	पूर्ण

	device_initialize(&idev->dev);
	idev->dev.devt = MKDEV(uio_major, idev->minor);
	idev->dev.class = &uio_class;
	idev->dev.parent = parent;
	idev->dev.release = uio_device_release;
	dev_set_drvdata(&idev->dev, idev);

	ret = dev_set_name(&idev->dev, "uio%d", idev->minor);
	अगर (ret)
		जाओ err_device_create;

	ret = device_add(&idev->dev);
	अगर (ret)
		जाओ err_device_create;

	ret = uio_dev_add_attributes(idev);
	अगर (ret)
		जाओ err_uio_dev_add_attributes;

	info->uio_dev = idev;

	अगर (info->irq && (info->irq != UIO_IRQ_CUSTOM)) अणु
		/*
		 * Note that we deliberately करोn't use devm_request_irq
		 * here. The parent module can unरेजिस्टर the UIO device
		 * and call pci_disable_msi, which requires that this
		 * irq has been मुक्तd. However, the device may have खोलो
		 * FDs at the समय of unरेजिस्टर and thereक्रमe may not be
		 * मुक्तd until they are released.
		 */
		ret = request_irq(info->irq, uio_पूर्णांकerrupt,
				  info->irq_flags, info->name, idev);
		अगर (ret) अणु
			info->uio_dev = शून्य;
			जाओ err_request_irq;
		पूर्ण
	पूर्ण

	वापस 0;

err_request_irq:
	uio_dev_del_attributes(idev);
err_uio_dev_add_attributes:
	device_del(&idev->dev);
err_device_create:
	uio_मुक्त_minor(idev->minor);
	put_device(&idev->dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__uio_रेजिस्टर_device);

अटल व्योम devm_uio_unरेजिस्टर_device(काष्ठा device *dev, व्योम *res)
अणु
	uio_unरेजिस्टर_device(*(काष्ठा uio_info **)res);
पूर्ण

/**
 * __devm_uio_रेजिस्टर_device - Resource managed uio_रेजिस्टर_device()
 * @owner:	module that creates the new device
 * @parent:	parent device
 * @info:	UIO device capabilities
 *
 * वापसs zero on success or a negative error code.
 */
पूर्णांक __devm_uio_रेजिस्टर_device(काष्ठा module *owner,
			       काष्ठा device *parent,
			       काष्ठा uio_info *info)
अणु
	काष्ठा uio_info **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_uio_unरेजिस्टर_device, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	*ptr = info;
	ret = __uio_रेजिस्टर_device(owner, parent, info);
	अगर (ret) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	devres_add(parent, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_uio_रेजिस्टर_device);

/**
 * uio_unरेजिस्टर_device - unरेजिस्टर a industrial IO device
 * @info:	UIO device capabilities
 *
 */
व्योम uio_unरेजिस्टर_device(काष्ठा uio_info *info)
अणु
	काष्ठा uio_device *idev;
	अचिन्हित दीर्घ minor;

	अगर (!info || !info->uio_dev)
		वापस;

	idev = info->uio_dev;
	minor = idev->minor;

	mutex_lock(&idev->info_lock);
	uio_dev_del_attributes(idev);

	अगर (info->irq && info->irq != UIO_IRQ_CUSTOM)
		मुक्त_irq(info->irq, idev);

	idev->info = शून्य;
	mutex_unlock(&idev->info_lock);

	wake_up_पूर्णांकerruptible(&idev->रुको);
	समाप्त_fasync(&idev->async_queue, SIGIO, POLL_HUP);

	device_unरेजिस्टर(&idev->dev);

	uio_मुक्त_minor(minor);

	वापस;
पूर्ण
EXPORT_SYMBOL_GPL(uio_unरेजिस्टर_device);

अटल पूर्णांक __init uio_init(व्योम)
अणु
	वापस init_uio_class();
पूर्ण

अटल व्योम __निकास uio_निकास(व्योम)
अणु
	release_uio_class();
	idr_destroy(&uio_idr);
पूर्ण

module_init(uio_init)
module_निकास(uio_निकास)
MODULE_LICENSE("GPL v2");
