<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "internals.h"

अटल DEFINE_IDR(i3c_bus_idr);
अटल DEFINE_MUTEX(i3c_core_lock);

/**
 * i3c_bus_मुख्यtenance_lock - Lock the bus क्रम a मुख्यtenance operation
 * @bus: I3C bus to take the lock on
 *
 * This function takes the bus lock so that no other operations can occur on
 * the bus. This is needed क्रम all kind of bus मुख्यtenance operation, like
 * - enabling/disabling slave events
 * - re-triggering DAA
 * - changing the dynamic address of a device
 * - relinquishing mastership
 * - ...
 *
 * The reason क्रम this kind of locking is that we करोn't want drivers and core
 * logic to rely on I3C device inक्रमmation that could be changed behind their
 * back.
 */
अटल व्योम i3c_bus_मुख्यtenance_lock(काष्ठा i3c_bus *bus)
अणु
	करोwn_ग_लिखो(&bus->lock);
पूर्ण

/**
 * i3c_bus_मुख्यtenance_unlock - Release the bus lock after a मुख्यtenance
 *			      operation
 * @bus: I3C bus to release the lock on
 *
 * Should be called when the bus मुख्यtenance operation is करोne. See
 * i3c_bus_मुख्यtenance_lock() क्रम more details on what these मुख्यtenance
 * operations are.
 */
अटल व्योम i3c_bus_मुख्यtenance_unlock(काष्ठा i3c_bus *bus)
अणु
	up_ग_लिखो(&bus->lock);
पूर्ण

/**
 * i3c_bus_normaluse_lock - Lock the bus क्रम a normal operation
 * @bus: I3C bus to take the lock on
 *
 * This function takes the bus lock क्रम any operation that is not a मुख्यtenance
 * operation (see i3c_bus_मुख्यtenance_lock() क्रम a non-exhaustive list of
 * मुख्यtenance operations). Basically all communications with I3C devices are
 * normal operations (HDR, SDR transfers or CCC commands that करो not change bus
 * state or I3C dynamic address).
 *
 * Note that this lock is not guaranteeing serialization of normal operations.
 * In other words, transfer requests passed to the I3C master can be submitted
 * in parallel and I3C master drivers have to use their own locking to make
 * sure two dअगरferent communications are not पूर्णांकer-mixed, or access to the
 * output/input queue is not करोne जबतक the engine is busy.
 */
व्योम i3c_bus_normaluse_lock(काष्ठा i3c_bus *bus)
अणु
	करोwn_पढ़ो(&bus->lock);
पूर्ण

/**
 * i3c_bus_normaluse_unlock - Release the bus lock after a normal operation
 * @bus: I3C bus to release the lock on
 *
 * Should be called when a normal operation is करोne. See
 * i3c_bus_normaluse_lock() क्रम more details on what these normal operations
 * are.
 */
व्योम i3c_bus_normaluse_unlock(काष्ठा i3c_bus *bus)
अणु
	up_पढ़ो(&bus->lock);
पूर्ण

अटल काष्ठा i3c_master_controller *
i3c_bus_to_i3c_master(काष्ठा i3c_bus *i3cbus)
अणु
	वापस container_of(i3cbus, काष्ठा i3c_master_controller, bus);
पूर्ण

अटल काष्ठा i3c_master_controller *dev_to_i3cmaster(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा i3c_master_controller, dev);
पूर्ण

अटल स्थिर काष्ठा device_type i3c_device_type;

अटल काष्ठा i3c_bus *dev_to_i3cbus(काष्ठा device *dev)
अणु
	काष्ठा i3c_master_controller *master;

	अगर (dev->type == &i3c_device_type)
		वापस dev_to_i3cdev(dev)->bus;

	master = dev_to_i3cmaster(dev);

	वापस &master->bus;
पूर्ण

अटल काष्ठा i3c_dev_desc *dev_to_i3cdesc(काष्ठा device *dev)
अणु
	काष्ठा i3c_master_controller *master;

	अगर (dev->type == &i3c_device_type)
		वापस dev_to_i3cdev(dev)->desc;

	master = dev_to_i3cmaster(dev);

	वापस master->this;
पूर्ण

अटल sमाप_प्रकार bcr_show(काष्ठा device *dev,
			काष्ठा device_attribute *da,
			अक्षर *buf)
अणु
	काष्ठा i3c_bus *bus = dev_to_i3cbus(dev);
	काष्ठा i3c_dev_desc *desc;
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(bus);
	desc = dev_to_i3cdesc(dev);
	ret = प्र_लिखो(buf, "%x\n", desc->info.bcr);
	i3c_bus_normaluse_unlock(bus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(bcr);

अटल sमाप_प्रकार dcr_show(काष्ठा device *dev,
			काष्ठा device_attribute *da,
			अक्षर *buf)
अणु
	काष्ठा i3c_bus *bus = dev_to_i3cbus(dev);
	काष्ठा i3c_dev_desc *desc;
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(bus);
	desc = dev_to_i3cdesc(dev);
	ret = प्र_लिखो(buf, "%x\n", desc->info.dcr);
	i3c_bus_normaluse_unlock(bus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(dcr);

अटल sमाप_प्रकार pid_show(काष्ठा device *dev,
			काष्ठा device_attribute *da,
			अक्षर *buf)
अणु
	काष्ठा i3c_bus *bus = dev_to_i3cbus(dev);
	काष्ठा i3c_dev_desc *desc;
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(bus);
	desc = dev_to_i3cdesc(dev);
	ret = प्र_लिखो(buf, "%llx\n", desc->info.pid);
	i3c_bus_normaluse_unlock(bus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(pid);

अटल sमाप_प्रकार dynamic_address_show(काष्ठा device *dev,
				    काष्ठा device_attribute *da,
				    अक्षर *buf)
अणु
	काष्ठा i3c_bus *bus = dev_to_i3cbus(dev);
	काष्ठा i3c_dev_desc *desc;
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(bus);
	desc = dev_to_i3cdesc(dev);
	ret = प्र_लिखो(buf, "%02x\n", desc->info.dyn_addr);
	i3c_bus_normaluse_unlock(bus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(dynamic_address);

अटल स्थिर अक्षर * स्थिर hdrcap_strings[] = अणु
	"hdr-ddr", "hdr-tsp", "hdr-tsl",
पूर्ण;

अटल sमाप_प्रकार hdrcap_show(काष्ठा device *dev,
			   काष्ठा device_attribute *da,
			   अक्षर *buf)
अणु
	काष्ठा i3c_bus *bus = dev_to_i3cbus(dev);
	काष्ठा i3c_dev_desc *desc;
	sमाप_प्रकार offset = 0, ret;
	अचिन्हित दीर्घ caps;
	पूर्णांक mode;

	i3c_bus_normaluse_lock(bus);
	desc = dev_to_i3cdesc(dev);
	caps = desc->info.hdr_cap;
	क्रम_each_set_bit(mode, &caps, 8) अणु
		अगर (mode >= ARRAY_SIZE(hdrcap_strings))
			अवरोध;

		अगर (!hdrcap_strings[mode])
			जारी;

		ret = प्र_लिखो(buf + offset, offset ? " %s" : "%s",
			      hdrcap_strings[mode]);
		अगर (ret < 0)
			जाओ out;

		offset += ret;
	पूर्ण

	ret = प्र_लिखो(buf + offset, "\n");
	अगर (ret < 0)
		जाओ out;

	ret = offset + ret;

out:
	i3c_bus_normaluse_unlock(bus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(hdrcap);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा i3c_device *i3c = dev_to_i3cdev(dev);
	काष्ठा i3c_device_info devinfo;
	u16 manuf, part, ext;

	i3c_device_get_info(i3c, &devinfo);
	manuf = I3C_PID_MANUF_ID(devinfo.pid);
	part = I3C_PID_PART_ID(devinfo.pid);
	ext = I3C_PID_EXTRA_INFO(devinfo.pid);

	अगर (I3C_PID_RND_LOWER_32BITS(devinfo.pid))
		वापस प्र_लिखो(buf, "i3c:dcr%02Xmanuf%04X", devinfo.dcr,
			       manuf);

	वापस प्र_लिखो(buf, "i3c:dcr%02Xmanuf%04Xpart%04Xext%04X",
		       devinfo.dcr, manuf, part, ext);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *i3c_device_attrs[] = अणु
	&dev_attr_bcr.attr,
	&dev_attr_dcr.attr,
	&dev_attr_pid.attr,
	&dev_attr_dynamic_address.attr,
	&dev_attr_hdrcap.attr,
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(i3c_device);

अटल पूर्णांक i3c_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा i3c_device *i3cdev = dev_to_i3cdev(dev);
	काष्ठा i3c_device_info devinfo;
	u16 manuf, part, ext;

	i3c_device_get_info(i3cdev, &devinfo);
	manuf = I3C_PID_MANUF_ID(devinfo.pid);
	part = I3C_PID_PART_ID(devinfo.pid);
	ext = I3C_PID_EXTRA_INFO(devinfo.pid);

	अगर (I3C_PID_RND_LOWER_32BITS(devinfo.pid))
		वापस add_uevent_var(env, "MODALIAS=i3c:dcr%02Xmanuf%04X",
				      devinfo.dcr, manuf);

	वापस add_uevent_var(env,
			      "MODALIAS=i3c:dcr%02Xmanuf%04Xpart%04Xext%04X",
			      devinfo.dcr, manuf, part, ext);
पूर्ण

अटल स्थिर काष्ठा device_type i3c_device_type = अणु
	.groups	= i3c_device_groups,
	.uevent = i3c_device_uevent,
पूर्ण;

अटल पूर्णांक i3c_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा i3c_device *i3cdev;
	काष्ठा i3c_driver *i3cdrv;

	अगर (dev->type != &i3c_device_type)
		वापस 0;

	i3cdev = dev_to_i3cdev(dev);
	i3cdrv = drv_to_i3cdrv(drv);
	अगर (i3c_device_match_id(i3cdev, i3cdrv->id_table))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक i3c_device_probe(काष्ठा device *dev)
अणु
	काष्ठा i3c_device *i3cdev = dev_to_i3cdev(dev);
	काष्ठा i3c_driver *driver = drv_to_i3cdrv(dev->driver);

	वापस driver->probe(i3cdev);
पूर्ण

अटल पूर्णांक i3c_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा i3c_device *i3cdev = dev_to_i3cdev(dev);
	काष्ठा i3c_driver *driver = drv_to_i3cdrv(dev->driver);

	अगर (driver->हटाओ)
		driver->हटाओ(i3cdev);

	i3c_device_मुक्त_ibi(i3cdev);

	वापस 0;
पूर्ण

काष्ठा bus_type i3c_bus_type = अणु
	.name = "i3c",
	.match = i3c_device_match,
	.probe = i3c_device_probe,
	.हटाओ = i3c_device_हटाओ,
पूर्ण;

अटल क्रमागत i3c_addr_slot_status
i3c_bus_get_addr_slot_status(काष्ठा i3c_bus *bus, u16 addr)
अणु
	पूर्णांक status, bitpos = addr * 2;

	अगर (addr > I2C_MAX_ADDR)
		वापस I3C_ADDR_SLOT_RSVD;

	status = bus->addrslots[bitpos / BITS_PER_LONG];
	status >>= bitpos % BITS_PER_LONG;

	वापस status & I3C_ADDR_SLOT_STATUS_MASK;
पूर्ण

अटल व्योम i3c_bus_set_addr_slot_status(काष्ठा i3c_bus *bus, u16 addr,
					 क्रमागत i3c_addr_slot_status status)
अणु
	पूर्णांक bitpos = addr * 2;
	अचिन्हित दीर्घ *ptr;

	अगर (addr > I2C_MAX_ADDR)
		वापस;

	ptr = bus->addrslots + (bitpos / BITS_PER_LONG);
	*ptr &= ~((अचिन्हित दीर्घ)I3C_ADDR_SLOT_STATUS_MASK <<
						(bitpos % BITS_PER_LONG));
	*ptr |= (अचिन्हित दीर्घ)status << (bitpos % BITS_PER_LONG);
पूर्ण

अटल bool i3c_bus_dev_addr_is_avail(काष्ठा i3c_bus *bus, u8 addr)
अणु
	क्रमागत i3c_addr_slot_status status;

	status = i3c_bus_get_addr_slot_status(bus, addr);

	वापस status == I3C_ADDR_SLOT_FREE;
पूर्ण

अटल पूर्णांक i3c_bus_get_मुक्त_addr(काष्ठा i3c_bus *bus, u8 start_addr)
अणु
	क्रमागत i3c_addr_slot_status status;
	u8 addr;

	क्रम (addr = start_addr; addr < I3C_MAX_ADDR; addr++) अणु
		status = i3c_bus_get_addr_slot_status(bus, addr);
		अगर (status == I3C_ADDR_SLOT_FREE)
			वापस addr;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल व्योम i3c_bus_init_addrslots(काष्ठा i3c_bus *bus)
अणु
	पूर्णांक i;

	/* Addresses 0 to 7 are reserved. */
	क्रम (i = 0; i < 8; i++)
		i3c_bus_set_addr_slot_status(bus, i, I3C_ADDR_SLOT_RSVD);

	/*
	 * Reserve broadcast address and all addresses that might collide
	 * with the broadcast address when facing a single bit error.
	 */
	i3c_bus_set_addr_slot_status(bus, I3C_BROADCAST_ADDR,
				     I3C_ADDR_SLOT_RSVD);
	क्रम (i = 0; i < 7; i++)
		i3c_bus_set_addr_slot_status(bus, I3C_BROADCAST_ADDR ^ BIT(i),
					     I3C_ADDR_SLOT_RSVD);
पूर्ण

अटल व्योम i3c_bus_cleanup(काष्ठा i3c_bus *i3cbus)
अणु
	mutex_lock(&i3c_core_lock);
	idr_हटाओ(&i3c_bus_idr, i3cbus->id);
	mutex_unlock(&i3c_core_lock);
पूर्ण

अटल पूर्णांक i3c_bus_init(काष्ठा i3c_bus *i3cbus)
अणु
	पूर्णांक ret;

	init_rwsem(&i3cbus->lock);
	INIT_LIST_HEAD(&i3cbus->devs.i2c);
	INIT_LIST_HEAD(&i3cbus->devs.i3c);
	i3c_bus_init_addrslots(i3cbus);
	i3cbus->mode = I3C_BUS_MODE_PURE;

	mutex_lock(&i3c_core_lock);
	ret = idr_alloc(&i3c_bus_idr, i3cbus, 0, 0, GFP_KERNEL);
	mutex_unlock(&i3c_core_lock);

	अगर (ret < 0)
		वापस ret;

	i3cbus->id = ret;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर i3c_bus_mode_strings[] = अणु
	[I3C_BUS_MODE_PURE] = "pure",
	[I3C_BUS_MODE_MIXED_FAST] = "mixed-fast",
	[I3C_BUS_MODE_MIXED_LIMITED] = "mixed-limited",
	[I3C_BUS_MODE_MIXED_SLOW] = "mixed-slow",
पूर्ण;

अटल sमाप_प्रकार mode_show(काष्ठा device *dev,
			 काष्ठा device_attribute *da,
			 अक्षर *buf)
अणु
	काष्ठा i3c_bus *i3cbus = dev_to_i3cbus(dev);
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(i3cbus);
	अगर (i3cbus->mode < 0 ||
	    i3cbus->mode >= ARRAY_SIZE(i3c_bus_mode_strings) ||
	    !i3c_bus_mode_strings[i3cbus->mode])
		ret = प्र_लिखो(buf, "unknown\n");
	अन्यथा
		ret = प्र_लिखो(buf, "%s\n", i3c_bus_mode_strings[i3cbus->mode]);
	i3c_bus_normaluse_unlock(i3cbus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(mode);

अटल sमाप_प्रकार current_master_show(काष्ठा device *dev,
				   काष्ठा device_attribute *da,
				   अक्षर *buf)
अणु
	काष्ठा i3c_bus *i3cbus = dev_to_i3cbus(dev);
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(i3cbus);
	ret = प्र_लिखो(buf, "%d-%llx\n", i3cbus->id,
		      i3cbus->cur_master->info.pid);
	i3c_bus_normaluse_unlock(i3cbus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(current_master);

अटल sमाप_प्रकार i3c_scl_frequency_show(काष्ठा device *dev,
				      काष्ठा device_attribute *da,
				      अक्षर *buf)
अणु
	काष्ठा i3c_bus *i3cbus = dev_to_i3cbus(dev);
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(i3cbus);
	ret = प्र_लिखो(buf, "%ld\n", i3cbus->scl_rate.i3c);
	i3c_bus_normaluse_unlock(i3cbus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(i3c_scl_frequency);

अटल sमाप_प्रकार i2c_scl_frequency_show(काष्ठा device *dev,
				      काष्ठा device_attribute *da,
				      अक्षर *buf)
अणु
	काष्ठा i3c_bus *i3cbus = dev_to_i3cbus(dev);
	sमाप_प्रकार ret;

	i3c_bus_normaluse_lock(i3cbus);
	ret = प्र_लिखो(buf, "%ld\n", i3cbus->scl_rate.i2c);
	i3c_bus_normaluse_unlock(i3cbus);

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RO(i2c_scl_frequency);

अटल काष्ठा attribute *i3c_masterdev_attrs[] = अणु
	&dev_attr_mode.attr,
	&dev_attr_current_master.attr,
	&dev_attr_i3c_scl_frequency.attr,
	&dev_attr_i2c_scl_frequency.attr,
	&dev_attr_bcr.attr,
	&dev_attr_dcr.attr,
	&dev_attr_pid.attr,
	&dev_attr_dynamic_address.attr,
	&dev_attr_hdrcap.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(i3c_masterdev);

अटल व्योम i3c_masterdev_release(काष्ठा device *dev)
अणु
	काष्ठा i3c_master_controller *master = dev_to_i3cmaster(dev);
	काष्ठा i3c_bus *bus = dev_to_i3cbus(dev);

	अगर (master->wq)
		destroy_workqueue(master->wq);

	WARN_ON(!list_empty(&bus->devs.i2c) || !list_empty(&bus->devs.i3c));
	i3c_bus_cleanup(bus);

	of_node_put(dev->of_node);
पूर्ण

अटल स्थिर काष्ठा device_type i3c_masterdev_type = अणु
	.groups	= i3c_masterdev_groups,
पूर्ण;

अटल पूर्णांक i3c_bus_set_mode(काष्ठा i3c_bus *i3cbus, क्रमागत i3c_bus_mode mode,
			    अचिन्हित दीर्घ max_i2c_scl_rate)
अणु
	काष्ठा i3c_master_controller *master = i3c_bus_to_i3c_master(i3cbus);

	i3cbus->mode = mode;

	चयन (i3cbus->mode) अणु
	हाल I3C_BUS_MODE_PURE:
		अगर (!i3cbus->scl_rate.i3c)
			i3cbus->scl_rate.i3c = I3C_BUS_TYP_I3C_SCL_RATE;
		अवरोध;
	हाल I3C_BUS_MODE_MIXED_FAST:
	हाल I3C_BUS_MODE_MIXED_LIMITED:
		अगर (!i3cbus->scl_rate.i3c)
			i3cbus->scl_rate.i3c = I3C_BUS_TYP_I3C_SCL_RATE;
		अगर (!i3cbus->scl_rate.i2c)
			i3cbus->scl_rate.i2c = max_i2c_scl_rate;
		अवरोध;
	हाल I3C_BUS_MODE_MIXED_SLOW:
		अगर (!i3cbus->scl_rate.i2c)
			i3cbus->scl_rate.i2c = max_i2c_scl_rate;
		अगर (!i3cbus->scl_rate.i3c ||
		    i3cbus->scl_rate.i3c > i3cbus->scl_rate.i2c)
			i3cbus->scl_rate.i3c = i3cbus->scl_rate.i2c;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&master->dev, "i2c-scl = %ld Hz i3c-scl = %ld Hz\n",
		i3cbus->scl_rate.i2c, i3cbus->scl_rate.i3c);

	/*
	 * I3C/I2C frequency may have been overridden, check that user-provided
	 * values are not exceeding max possible frequency.
	 */
	अगर (i3cbus->scl_rate.i3c > I3C_BUS_MAX_I3C_SCL_RATE ||
	    i3cbus->scl_rate.i2c > I3C_BUS_I2C_FM_PLUS_SCL_RATE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा i3c_master_controller *
i2c_adapter_to_i3c_master(काष्ठा i2c_adapter *adap)
अणु
	वापस container_of(adap, काष्ठा i3c_master_controller, i2c);
पूर्ण

अटल काष्ठा i2c_adapter *
i3c_master_to_i2c_adapter(काष्ठा i3c_master_controller *master)
अणु
	वापस &master->i2c;
पूर्ण

अटल व्योम i3c_master_मुक्त_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल काष्ठा i2c_dev_desc *
i3c_master_alloc_i2c_dev(काष्ठा i3c_master_controller *master,
			 स्थिर काष्ठा i2c_dev_boardinfo *boardinfo)
अणु
	काष्ठा i2c_dev_desc *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev->common.master = master;
	dev->boardinfo = boardinfo;
	dev->addr = boardinfo->base.addr;
	dev->lvr = boardinfo->lvr;

	वापस dev;
पूर्ण

अटल व्योम *i3c_ccc_cmd_dest_init(काष्ठा i3c_ccc_cmd_dest *dest, u8 addr,
				   u16 payloadlen)
अणु
	dest->addr = addr;
	dest->payload.len = payloadlen;
	अगर (payloadlen)
		dest->payload.data = kzalloc(payloadlen, GFP_KERNEL);
	अन्यथा
		dest->payload.data = शून्य;

	वापस dest->payload.data;
पूर्ण

अटल व्योम i3c_ccc_cmd_dest_cleanup(काष्ठा i3c_ccc_cmd_dest *dest)
अणु
	kमुक्त(dest->payload.data);
पूर्ण

अटल व्योम i3c_ccc_cmd_init(काष्ठा i3c_ccc_cmd *cmd, bool rnw, u8 id,
			     काष्ठा i3c_ccc_cmd_dest *dests,
			     अचिन्हित पूर्णांक ndests)
अणु
	cmd->rnw = rnw ? 1 : 0;
	cmd->id = id;
	cmd->dests = dests;
	cmd->ndests = ndests;
	cmd->err = I3C_ERROR_UNKNOWN;
पूर्ण

अटल पूर्णांक i3c_master_send_ccc_cmd_locked(काष्ठा i3c_master_controller *master,
					  काष्ठा i3c_ccc_cmd *cmd)
अणु
	पूर्णांक ret;

	अगर (!cmd || !master)
		वापस -EINVAL;

	अगर (WARN_ON(master->init_करोne &&
		    !rwsem_is_locked(&master->bus.lock)))
		वापस -EINVAL;

	अगर (!master->ops->send_ccc_cmd)
		वापस -ENOTSUPP;

	अगर ((cmd->id & I3C_CCC_सूचीECT) && (!cmd->dests || !cmd->ndests))
		वापस -EINVAL;

	अगर (master->ops->supports_ccc_cmd &&
	    !master->ops->supports_ccc_cmd(master, cmd))
		वापस -ENOTSUPP;

	ret = master->ops->send_ccc_cmd(master, cmd);
	अगर (ret) अणु
		अगर (cmd->err != I3C_ERROR_UNKNOWN)
			वापस cmd->err;

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा i2c_dev_desc *
i3c_master_find_i2c_dev_by_addr(स्थिर काष्ठा i3c_master_controller *master,
				u16 addr)
अणु
	काष्ठा i2c_dev_desc *dev;

	i3c_bus_क्रम_each_i2cdev(&master->bus, dev) अणु
		अगर (dev->boardinfo->base.addr == addr)
			वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * i3c_master_get_मुक्त_addr() - get a मुक्त address on the bus
 * @master: I3C master object
 * @start_addr: where to start searching
 *
 * This function must be called with the bus lock held in ग_लिखो mode.
 *
 * Return: the first मुक्त address starting at @start_addr (included) or -ENOMEM
 * अगर there's no more address available.
 */
पूर्णांक i3c_master_get_मुक्त_addr(काष्ठा i3c_master_controller *master,
			     u8 start_addr)
अणु
	वापस i3c_bus_get_मुक्त_addr(&master->bus, start_addr);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_get_मुक्त_addr);

अटल व्योम i3c_device_release(काष्ठा device *dev)
अणु
	काष्ठा i3c_device *i3cdev = dev_to_i3cdev(dev);

	WARN_ON(i3cdev->desc);

	of_node_put(i3cdev->dev.of_node);
	kमुक्त(i3cdev);
पूर्ण

अटल व्योम i3c_master_मुक्त_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल काष्ठा i3c_dev_desc *
i3c_master_alloc_i3c_dev(काष्ठा i3c_master_controller *master,
			 स्थिर काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_dev_desc *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस ERR_PTR(-ENOMEM);

	dev->common.master = master;
	dev->info = *info;
	mutex_init(&dev->ibi_lock);

	वापस dev;
पूर्ण

अटल पूर्णांक i3c_master_rstdaa_locked(काष्ठा i3c_master_controller *master,
				    u8 addr)
अणु
	क्रमागत i3c_addr_slot_status addrstat;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	अगर (!master)
		वापस -EINVAL;

	addrstat = i3c_bus_get_addr_slot_status(&master->bus, addr);
	अगर (addr != I3C_BROADCAST_ADDR && addrstat != I3C_ADDR_SLOT_I3C_DEV)
		वापस -EINVAL;

	i3c_ccc_cmd_dest_init(&dest, addr, 0);
	i3c_ccc_cmd_init(&cmd, false,
			 I3C_CCC_RSTDAA(addr == I3C_BROADCAST_ADDR),
			 &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

/**
 * i3c_master_entdaa_locked() - start a DAA (Dynamic Address Assignment)
 *				procedure
 * @master: master used to send frames on the bus
 *
 * Send a ENTDAA CCC command to start a DAA procedure.
 *
 * Note that this function only sends the ENTDAA CCC command, all the logic
 * behind dynamic address assignment has to be handled in the I3C master
 * driver.
 *
 * This function must be called with the bus lock held in ग_लिखो mode.
 *
 * Return: 0 in हाल of success, a positive I3C error code अगर the error is
 * one of the official Mx error codes, and a negative error code otherwise.
 */
पूर्णांक i3c_master_entdaa_locked(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	i3c_ccc_cmd_dest_init(&dest, I3C_BROADCAST_ADDR, 0);
	i3c_ccc_cmd_init(&cmd, false, I3C_CCC_ENTDAA, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_entdaa_locked);

अटल पूर्णांक i3c_master_enec_disec_locked(काष्ठा i3c_master_controller *master,
					u8 addr, bool enable, u8 evts)
अणु
	काष्ठा i3c_ccc_events *events;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	events = i3c_ccc_cmd_dest_init(&dest, addr, माप(*events));
	अगर (!events)
		वापस -ENOMEM;

	events->events = evts;
	i3c_ccc_cmd_init(&cmd, false,
			 enable ?
			 I3C_CCC_ENEC(addr == I3C_BROADCAST_ADDR) :
			 I3C_CCC_DISEC(addr == I3C_BROADCAST_ADDR),
			 &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

/**
 * i3c_master_disec_locked() - send a DISEC CCC command
 * @master: master used to send frames on the bus
 * @addr: a valid I3C slave address or %I3C_BROADCAST_ADDR
 * @evts: events to disable
 *
 * Send a DISEC CCC command to disable some or all events coming from a
 * specअगरic slave, or all devices अगर @addr is %I3C_BROADCAST_ADDR.
 *
 * This function must be called with the bus lock held in ग_लिखो mode.
 *
 * Return: 0 in हाल of success, a positive I3C error code अगर the error is
 * one of the official Mx error codes, and a negative error code otherwise.
 */
पूर्णांक i3c_master_disec_locked(काष्ठा i3c_master_controller *master, u8 addr,
			    u8 evts)
अणु
	वापस i3c_master_enec_disec_locked(master, addr, false, evts);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_disec_locked);

/**
 * i3c_master_enec_locked() - send an ENEC CCC command
 * @master: master used to send frames on the bus
 * @addr: a valid I3C slave address or %I3C_BROADCAST_ADDR
 * @evts: events to disable
 *
 * Sends an ENEC CCC command to enable some or all events coming from a
 * specअगरic slave, or all devices अगर @addr is %I3C_BROADCAST_ADDR.
 *
 * This function must be called with the bus lock held in ग_लिखो mode.
 *
 * Return: 0 in हाल of success, a positive I3C error code अगर the error is
 * one of the official Mx error codes, and a negative error code otherwise.
 */
पूर्णांक i3c_master_enec_locked(काष्ठा i3c_master_controller *master, u8 addr,
			   u8 evts)
अणु
	वापस i3c_master_enec_disec_locked(master, addr, true, evts);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_enec_locked);

/**
 * i3c_master_defslvs_locked() - send a DEFSLVS CCC command
 * @master: master used to send frames on the bus
 *
 * Send a DEFSLVS CCC command containing all the devices known to the @master.
 * This is useful when you have secondary masters on the bus to propagate
 * device inक्रमmation.
 *
 * This should be called after all I3C devices have been discovered (in other
 * words, after the DAA procedure has finished) and instantiated in
 * &i3c_master_controller_ops->bus_init().
 * It should also be called अगर a master ACKed an Hot-Join request and asचिन्हित
 * a dynamic address to the device joining the bus.
 *
 * This function must be called with the bus lock held in ग_लिखो mode.
 *
 * Return: 0 in हाल of success, a positive I3C error code अगर the error is
 * one of the official Mx error codes, and a negative error code otherwise.
 */
पूर्णांक i3c_master_defslvs_locked(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा i3c_ccc_defslvs *defslvs;
	काष्ठा i3c_ccc_dev_desc *desc;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_dev_desc *i3cdev;
	काष्ठा i2c_dev_desc *i2cdev;
	काष्ठा i3c_ccc_cmd cmd;
	काष्ठा i3c_bus *bus;
	bool send = false;
	पूर्णांक ndevs = 0, ret;

	अगर (!master)
		वापस -EINVAL;

	bus = i3c_master_get_bus(master);
	i3c_bus_क्रम_each_i3cdev(bus, i3cdev) अणु
		ndevs++;

		अगर (i3cdev == master->this)
			जारी;

		अगर (I3C_BCR_DEVICE_ROLE(i3cdev->info.bcr) ==
		    I3C_BCR_I3C_MASTER)
			send = true;
	पूर्ण

	/* No other master on the bus, skip DEFSLVS. */
	अगर (!send)
		वापस 0;

	i3c_bus_क्रम_each_i2cdev(bus, i2cdev)
		ndevs++;

	defslvs = i3c_ccc_cmd_dest_init(&dest, I3C_BROADCAST_ADDR,
					काष्ठा_size(defslvs, slaves,
						    ndevs - 1));
	अगर (!defslvs)
		वापस -ENOMEM;

	defslvs->count = ndevs;
	defslvs->master.bcr = master->this->info.bcr;
	defslvs->master.dcr = master->this->info.dcr;
	defslvs->master.dyn_addr = master->this->info.dyn_addr << 1;
	defslvs->master.अटल_addr = I3C_BROADCAST_ADDR << 1;

	desc = defslvs->slaves;
	i3c_bus_क्रम_each_i2cdev(bus, i2cdev) अणु
		desc->lvr = i2cdev->lvr;
		desc->अटल_addr = i2cdev->addr << 1;
		desc++;
	पूर्ण

	i3c_bus_क्रम_each_i3cdev(bus, i3cdev) अणु
		/* Skip the I3C dev representing this master. */
		अगर (i3cdev == master->this)
			जारी;

		desc->bcr = i3cdev->info.bcr;
		desc->dcr = i3cdev->info.dcr;
		desc->dyn_addr = i3cdev->info.dyn_addr << 1;
		desc->अटल_addr = i3cdev->info.अटल_addr << 1;
		desc++;
	पूर्ण

	i3c_ccc_cmd_init(&cmd, false, I3C_CCC_DEFSLVS, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_defslvs_locked);

अटल पूर्णांक i3c_master_setda_locked(काष्ठा i3c_master_controller *master,
				   u8 oldaddr, u8 newaddr, bool setdasa)
अणु
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_setda *setda;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	अगर (!oldaddr || !newaddr)
		वापस -EINVAL;

	setda = i3c_ccc_cmd_dest_init(&dest, oldaddr, माप(*setda));
	अगर (!setda)
		वापस -ENOMEM;

	setda->addr = newaddr << 1;
	i3c_ccc_cmd_init(&cmd, false,
			 setdasa ? I3C_CCC_SETDASA : I3C_CCC_SETNEWDA,
			 &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_setdasa_locked(काष्ठा i3c_master_controller *master,
				     u8 अटल_addr, u8 dyn_addr)
अणु
	वापस i3c_master_setda_locked(master, अटल_addr, dyn_addr, true);
पूर्ण

अटल पूर्णांक i3c_master_setnewda_locked(काष्ठा i3c_master_controller *master,
				      u8 oldaddr, u8 newaddr)
अणु
	वापस i3c_master_setda_locked(master, oldaddr, newaddr, false);
पूर्ण

अटल पूर्णांक i3c_master_geपंचांगrl_locked(काष्ठा i3c_master_controller *master,
				    काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_mrl *mrl;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	mrl = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr, माप(*mrl));
	अगर (!mrl)
		वापस -ENOMEM;

	/*
	 * When the device करोes not have IBI payload GETMRL only वापसs 2
	 * bytes of data.
	 */
	अगर (!(info->bcr & I3C_BCR_IBI_PAYLOAD))
		dest.payload.len -= 1;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETMRL, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	अगर (ret)
		जाओ out;

	चयन (dest.payload.len) अणु
	हाल 3:
		info->max_ibi_len = mrl->ibi_len;
		fallthrough;
	हाल 2:
		info->max_पढ़ो_len = be16_to_cpu(mrl->पढ़ो_len);
		अवरोध;
	शेष:
		ret = -EIO;
		जाओ out;
	पूर्ण

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_geपंचांगwl_locked(काष्ठा i3c_master_controller *master,
				    काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_mwl *mwl;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	mwl = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr, माप(*mwl));
	अगर (!mwl)
		वापस -ENOMEM;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETMWL, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	अगर (ret)
		जाओ out;

	अगर (dest.payload.len != माप(*mwl)) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	info->max_ग_लिखो_len = be16_to_cpu(mwl->len);

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_geपंचांगxds_locked(काष्ठा i3c_master_controller *master,
				     काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_ccc_geपंचांगxds *geपंचांगaxds;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	geपंचांगaxds = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr,
					 माप(*geपंचांगaxds));
	अगर (!geपंचांगaxds)
		वापस -ENOMEM;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETMXDS, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	अगर (ret)
		जाओ out;

	अगर (dest.payload.len != 2 && dest.payload.len != 5) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	info->max_पढ़ो_ds = geपंचांगaxds->maxrd;
	info->max_ग_लिखो_ds = geपंचांगaxds->maxwr;
	अगर (dest.payload.len == 5)
		info->max_पढ़ो_turnaround = geपंचांगaxds->maxrdturn[0] |
					    ((u32)geपंचांगaxds->maxrdturn[1] << 8) |
					    ((u32)geपंचांगaxds->maxrdturn[2] << 16);

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_gethdrcap_locked(काष्ठा i3c_master_controller *master,
				       काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_ccc_gethdrcap *gethdrcap;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	gethdrcap = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr,
					  माप(*gethdrcap));
	अगर (!gethdrcap)
		वापस -ENOMEM;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETHDRCAP, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	अगर (ret)
		जाओ out;

	अगर (dest.payload.len != 1) अणु
		ret = -EIO;
		जाओ out;
	पूर्ण

	info->hdr_cap = gethdrcap->modes;

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_getpid_locked(काष्ठा i3c_master_controller *master,
				    काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_ccc_getpid *getpid;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret, i;

	getpid = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr, माप(*getpid));
	अगर (!getpid)
		वापस -ENOMEM;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETPID, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	अगर (ret)
		जाओ out;

	info->pid = 0;
	क्रम (i = 0; i < माप(getpid->pid); i++) अणु
		पूर्णांक sft = (माप(getpid->pid) - i - 1) * 8;

		info->pid |= (u64)getpid->pid[i] << sft;
	पूर्ण

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_getbcr_locked(काष्ठा i3c_master_controller *master,
				    काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_ccc_getbcr *getbcr;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	getbcr = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr, माप(*getbcr));
	अगर (!getbcr)
		वापस -ENOMEM;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETBCR, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	अगर (ret)
		जाओ out;

	info->bcr = getbcr->bcr;

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_getdcr_locked(काष्ठा i3c_master_controller *master,
				    काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_ccc_getdcr *getdcr;
	काष्ठा i3c_ccc_cmd_dest dest;
	काष्ठा i3c_ccc_cmd cmd;
	पूर्णांक ret;

	getdcr = i3c_ccc_cmd_dest_init(&dest, info->dyn_addr, माप(*getdcr));
	अगर (!getdcr)
		वापस -ENOMEM;

	i3c_ccc_cmd_init(&cmd, true, I3C_CCC_GETDCR, &dest, 1);
	ret = i3c_master_send_ccc_cmd_locked(master, &cmd);
	अगर (ret)
		जाओ out;

	info->dcr = getdcr->dcr;

out:
	i3c_ccc_cmd_dest_cleanup(&dest);

	वापस ret;
पूर्ण

अटल पूर्णांक i3c_master_retrieve_dev_info(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);
	क्रमागत i3c_addr_slot_status slot_status;
	पूर्णांक ret;

	अगर (!dev->info.dyn_addr)
		वापस -EINVAL;

	slot_status = i3c_bus_get_addr_slot_status(&master->bus,
						   dev->info.dyn_addr);
	अगर (slot_status == I3C_ADDR_SLOT_RSVD ||
	    slot_status == I3C_ADDR_SLOT_I2C_DEV)
		वापस -EINVAL;

	ret = i3c_master_getpid_locked(master, &dev->info);
	अगर (ret)
		वापस ret;

	ret = i3c_master_getbcr_locked(master, &dev->info);
	अगर (ret)
		वापस ret;

	ret = i3c_master_getdcr_locked(master, &dev->info);
	अगर (ret)
		वापस ret;

	अगर (dev->info.bcr & I3C_BCR_MAX_DATA_SPEED_LIM) अणु
		ret = i3c_master_geपंचांगxds_locked(master, &dev->info);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev->info.bcr & I3C_BCR_IBI_PAYLOAD)
		dev->info.max_ibi_len = 1;

	i3c_master_geपंचांगrl_locked(master, &dev->info);
	i3c_master_geपंचांगwl_locked(master, &dev->info);

	अगर (dev->info.bcr & I3C_BCR_HDR_CAP) अणु
		ret = i3c_master_gethdrcap_locked(master, &dev->info);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i3c_master_put_i3c_addrs(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);

	अगर (dev->info.अटल_addr)
		i3c_bus_set_addr_slot_status(&master->bus,
					     dev->info.अटल_addr,
					     I3C_ADDR_SLOT_FREE);

	अगर (dev->info.dyn_addr)
		i3c_bus_set_addr_slot_status(&master->bus, dev->info.dyn_addr,
					     I3C_ADDR_SLOT_FREE);

	अगर (dev->boardinfo && dev->boardinfo->init_dyn_addr)
		i3c_bus_set_addr_slot_status(&master->bus, dev->info.dyn_addr,
					     I3C_ADDR_SLOT_FREE);
पूर्ण

अटल पूर्णांक i3c_master_get_i3c_addrs(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);
	क्रमागत i3c_addr_slot_status status;

	अगर (!dev->info.अटल_addr && !dev->info.dyn_addr)
		वापस 0;

	अगर (dev->info.अटल_addr) अणु
		status = i3c_bus_get_addr_slot_status(&master->bus,
						      dev->info.अटल_addr);
		अगर (status != I3C_ADDR_SLOT_FREE)
			वापस -EBUSY;

		i3c_bus_set_addr_slot_status(&master->bus,
					     dev->info.अटल_addr,
					     I3C_ADDR_SLOT_I3C_DEV);
	पूर्ण

	/*
	 * ->init_dyn_addr should have been reserved beक्रमe that, so, अगर we're
	 * trying to apply a pre-reserved dynamic address, we should not try
	 * to reserve the address slot a second समय.
	 */
	अगर (dev->info.dyn_addr &&
	    (!dev->boardinfo ||
	     dev->boardinfo->init_dyn_addr != dev->info.dyn_addr)) अणु
		status = i3c_bus_get_addr_slot_status(&master->bus,
						      dev->info.dyn_addr);
		अगर (status != I3C_ADDR_SLOT_FREE)
			जाओ err_release_अटल_addr;

		i3c_bus_set_addr_slot_status(&master->bus, dev->info.dyn_addr,
					     I3C_ADDR_SLOT_I3C_DEV);
	पूर्ण

	वापस 0;

err_release_अटल_addr:
	अगर (dev->info.अटल_addr)
		i3c_bus_set_addr_slot_status(&master->bus,
					     dev->info.अटल_addr,
					     I3C_ADDR_SLOT_FREE);

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक i3c_master_attach_i3c_dev(काष्ठा i3c_master_controller *master,
				     काष्ठा i3c_dev_desc *dev)
अणु
	पूर्णांक ret;

	/*
	 * We करोn't attach devices to the controller until they are
	 * addressable on the bus.
	 */
	अगर (!dev->info.अटल_addr && !dev->info.dyn_addr)
		वापस 0;

	ret = i3c_master_get_i3c_addrs(dev);
	अगर (ret)
		वापस ret;

	/* Do not attach the master device itself. */
	अगर (master->this != dev && master->ops->attach_i3c_dev) अणु
		ret = master->ops->attach_i3c_dev(dev);
		अगर (ret) अणु
			i3c_master_put_i3c_addrs(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	list_add_tail(&dev->common.node, &master->bus.devs.i3c);

	वापस 0;
पूर्ण

अटल पूर्णांक i3c_master_reattach_i3c_dev(काष्ठा i3c_dev_desc *dev,
				       u8 old_dyn_addr)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);
	क्रमागत i3c_addr_slot_status status;
	पूर्णांक ret;

	अगर (dev->info.dyn_addr != old_dyn_addr &&
	    (!dev->boardinfo ||
	     dev->info.dyn_addr != dev->boardinfo->init_dyn_addr)) अणु
		status = i3c_bus_get_addr_slot_status(&master->bus,
						      dev->info.dyn_addr);
		अगर (status != I3C_ADDR_SLOT_FREE)
			वापस -EBUSY;
		i3c_bus_set_addr_slot_status(&master->bus,
					     dev->info.dyn_addr,
					     I3C_ADDR_SLOT_I3C_DEV);
	पूर्ण

	अगर (master->ops->reattach_i3c_dev) अणु
		ret = master->ops->reattach_i3c_dev(dev, old_dyn_addr);
		अगर (ret) अणु
			i3c_master_put_i3c_addrs(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम i3c_master_detach_i3c_dev(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);

	/* Do not detach the master device itself. */
	अगर (master->this != dev && master->ops->detach_i3c_dev)
		master->ops->detach_i3c_dev(dev);

	i3c_master_put_i3c_addrs(dev);
	list_del(&dev->common.node);
पूर्ण

अटल पूर्णांक i3c_master_attach_i2c_dev(काष्ठा i3c_master_controller *master,
				     काष्ठा i2c_dev_desc *dev)
अणु
	पूर्णांक ret;

	अगर (master->ops->attach_i2c_dev) अणु
		ret = master->ops->attach_i2c_dev(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	list_add_tail(&dev->common.node, &master->bus.devs.i2c);

	वापस 0;
पूर्ण

अटल व्योम i3c_master_detach_i2c_dev(काष्ठा i2c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master = i2c_dev_get_master(dev);

	list_del(&dev->common.node);

	अगर (master->ops->detach_i2c_dev)
		master->ops->detach_i2c_dev(dev);
पूर्ण

अटल पूर्णांक i3c_master_early_i3c_dev_add(काष्ठा i3c_master_controller *master,
					  काष्ठा i3c_dev_boardinfo *boardinfo)
अणु
	काष्ठा i3c_device_info info = अणु
		.अटल_addr = boardinfo->अटल_addr,
	पूर्ण;
	काष्ठा i3c_dev_desc *i3cdev;
	पूर्णांक ret;

	i3cdev = i3c_master_alloc_i3c_dev(master, &info);
	अगर (IS_ERR(i3cdev))
		वापस -ENOMEM;

	i3cdev->boardinfo = boardinfo;

	ret = i3c_master_attach_i3c_dev(master, i3cdev);
	अगर (ret)
		जाओ err_मुक्त_dev;

	ret = i3c_master_setdasa_locked(master, i3cdev->info.अटल_addr,
					i3cdev->boardinfo->init_dyn_addr);
	अगर (ret)
		जाओ err_detach_dev;

	i3cdev->info.dyn_addr = i3cdev->boardinfo->init_dyn_addr;
	ret = i3c_master_reattach_i3c_dev(i3cdev, 0);
	अगर (ret)
		जाओ err_rstdaa;

	ret = i3c_master_retrieve_dev_info(i3cdev);
	अगर (ret)
		जाओ err_rstdaa;

	वापस 0;

err_rstdaa:
	i3c_master_rstdaa_locked(master, i3cdev->boardinfo->init_dyn_addr);
err_detach_dev:
	i3c_master_detach_i3c_dev(i3cdev);
err_मुक्त_dev:
	i3c_master_मुक्त_i3c_dev(i3cdev);

	वापस ret;
पूर्ण

अटल व्योम
i3c_master_रेजिस्टर_new_i3c_devs(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा i3c_dev_desc *desc;
	पूर्णांक ret;

	अगर (!master->init_करोne)
		वापस;

	i3c_bus_क्रम_each_i3cdev(&master->bus, desc) अणु
		अगर (desc->dev || !desc->info.dyn_addr || desc == master->this)
			जारी;

		desc->dev = kzalloc(माप(*desc->dev), GFP_KERNEL);
		अगर (!desc->dev)
			जारी;

		desc->dev->bus = &master->bus;
		desc->dev->desc = desc;
		desc->dev->dev.parent = &master->dev;
		desc->dev->dev.type = &i3c_device_type;
		desc->dev->dev.bus = &i3c_bus_type;
		desc->dev->dev.release = i3c_device_release;
		dev_set_name(&desc->dev->dev, "%d-%llx", master->bus.id,
			     desc->info.pid);

		अगर (desc->boardinfo)
			desc->dev->dev.of_node = desc->boardinfo->of_node;

		ret = device_रेजिस्टर(&desc->dev->dev);
		अगर (ret)
			dev_err(&master->dev,
				"Failed to add I3C device (err = %d)\n", ret);
	पूर्ण
पूर्ण

/**
 * i3c_master_करो_daa() - करो a DAA (Dynamic Address Assignment)
 * @master: master करोing the DAA
 *
 * This function is instantiating an I3C device object and adding it to the
 * I3C device list. All device inक्रमmation are स्वतःmatically retrieved using
 * standard CCC commands.
 *
 * The I3C device object is वापसed in हाल the master wants to attach
 * निजी data to it using i3c_dev_set_master_data().
 *
 * This function must be called with the bus lock held in ग_लिखो mode.
 *
 * Return: a 0 in हाल of success, an negative error code otherwise.
 */
पूर्णांक i3c_master_करो_daa(काष्ठा i3c_master_controller *master)
अणु
	पूर्णांक ret;

	i3c_bus_मुख्यtenance_lock(&master->bus);
	ret = master->ops->करो_daa(master);
	i3c_bus_मुख्यtenance_unlock(&master->bus);

	अगर (ret)
		वापस ret;

	i3c_bus_normaluse_lock(&master->bus);
	i3c_master_रेजिस्टर_new_i3c_devs(master);
	i3c_bus_normaluse_unlock(&master->bus);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_करो_daa);

/**
 * i3c_master_set_info() - set master device inक्रमmation
 * @master: master used to send frames on the bus
 * @info: I3C device inक्रमmation
 *
 * Set master device info. This should be called from
 * &i3c_master_controller_ops->bus_init().
 *
 * Not all &i3c_device_info fields are meaningful क्रम a master device.
 * Here is a list of fields that should be properly filled:
 *
 * - &i3c_device_info->dyn_addr
 * - &i3c_device_info->bcr
 * - &i3c_device_info->dcr
 * - &i3c_device_info->pid
 * - &i3c_device_info->hdr_cap अगर %I3C_BCR_HDR_CAP bit is set in
 *   &i3c_device_info->bcr
 *
 * This function must be called with the bus lock held in मुख्यtenance mode.
 *
 * Return: 0 अगर @info contains valid inक्रमmation (not every piece of
 * inक्रमmation can be checked, but we can at least make sure @info->dyn_addr
 * and @info->bcr are correct), -EINVAL otherwise.
 */
पूर्णांक i3c_master_set_info(काष्ठा i3c_master_controller *master,
			स्थिर काष्ठा i3c_device_info *info)
अणु
	काष्ठा i3c_dev_desc *i3cdev;
	पूर्णांक ret;

	अगर (!i3c_bus_dev_addr_is_avail(&master->bus, info->dyn_addr))
		वापस -EINVAL;

	अगर (I3C_BCR_DEVICE_ROLE(info->bcr) == I3C_BCR_I3C_MASTER &&
	    master->secondary)
		वापस -EINVAL;

	अगर (master->this)
		वापस -EINVAL;

	i3cdev = i3c_master_alloc_i3c_dev(master, info);
	अगर (IS_ERR(i3cdev))
		वापस PTR_ERR(i3cdev);

	master->this = i3cdev;
	master->bus.cur_master = master->this;

	ret = i3c_master_attach_i3c_dev(master, i3cdev);
	अगर (ret)
		जाओ err_मुक्त_dev;

	वापस 0;

err_मुक्त_dev:
	i3c_master_मुक्त_i3c_dev(i3cdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_set_info);

अटल व्योम i3c_master_detach_मुक्त_devs(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा i3c_dev_desc *i3cdev, *i3cपंचांगp;
	काष्ठा i2c_dev_desc *i2cdev, *i2cपंचांगp;

	list_क्रम_each_entry_safe(i3cdev, i3cपंचांगp, &master->bus.devs.i3c,
				 common.node) अणु
		i3c_master_detach_i3c_dev(i3cdev);

		अगर (i3cdev->boardinfo && i3cdev->boardinfo->init_dyn_addr)
			i3c_bus_set_addr_slot_status(&master->bus,
					i3cdev->boardinfo->init_dyn_addr,
					I3C_ADDR_SLOT_FREE);

		i3c_master_मुक्त_i3c_dev(i3cdev);
	पूर्ण

	list_क्रम_each_entry_safe(i2cdev, i2cपंचांगp, &master->bus.devs.i2c,
				 common.node) अणु
		i3c_master_detach_i2c_dev(i2cdev);
		i3c_bus_set_addr_slot_status(&master->bus,
					     i2cdev->addr,
					     I3C_ADDR_SLOT_FREE);
		i3c_master_मुक्त_i2c_dev(i2cdev);
	पूर्ण
पूर्ण

/**
 * i3c_master_bus_init() - initialize an I3C bus
 * @master: मुख्य master initializing the bus
 *
 * This function is following all initialisation steps described in the I3C
 * specअगरication:
 *
 * 1. Attach I2C devs to the master so that the master can fill its पूर्णांकernal
 *    device table appropriately
 *
 * 2. Call &i3c_master_controller_ops->bus_init() method to initialize
 *    the master controller. That's usually where the bus mode is selected
 *    (pure bus or mixed fast/slow bus)
 *
 * 3. Inकाष्ठा all devices on the bus to drop their dynamic address. This is
 *    particularly important when the bus was previously configured by someone
 *    अन्यथा (क्रम example the bootloader)
 *
 * 4. Disable all slave events.
 *
 * 5. Reserve address slots क्रम I3C devices with init_dyn_addr. And अगर devices
 *    also have अटल_addr, try to pre-assign dynamic addresses requested by
 *    the FW with SETDASA and attach corresponding अटलally defined I3C
 *    devices to the master.
 *
 * 6. Do a DAA (Dynamic Address Assignment) to assign dynamic addresses to all
 *    reमुख्यing I3C devices
 *
 * Once this is करोne, all I3C and I2C devices should be usable.
 *
 * Return: a 0 in हाल of success, an negative error code otherwise.
 */
अटल पूर्णांक i3c_master_bus_init(काष्ठा i3c_master_controller *master)
अणु
	क्रमागत i3c_addr_slot_status status;
	काष्ठा i2c_dev_boardinfo *i2cboardinfo;
	काष्ठा i3c_dev_boardinfo *i3cboardinfo;
	काष्ठा i2c_dev_desc *i2cdev;
	पूर्णांक ret;

	/*
	 * First attach all devices with अटल definitions provided by the
	 * FW.
	 */
	list_क्रम_each_entry(i2cboardinfo, &master->boardinfo.i2c, node) अणु
		status = i3c_bus_get_addr_slot_status(&master->bus,
						      i2cboardinfo->base.addr);
		अगर (status != I3C_ADDR_SLOT_FREE) अणु
			ret = -EBUSY;
			जाओ err_detach_devs;
		पूर्ण

		i3c_bus_set_addr_slot_status(&master->bus,
					     i2cboardinfo->base.addr,
					     I3C_ADDR_SLOT_I2C_DEV);

		i2cdev = i3c_master_alloc_i2c_dev(master, i2cboardinfo);
		अगर (IS_ERR(i2cdev)) अणु
			ret = PTR_ERR(i2cdev);
			जाओ err_detach_devs;
		पूर्ण

		ret = i3c_master_attach_i2c_dev(master, i2cdev);
		अगर (ret) अणु
			i3c_master_मुक्त_i2c_dev(i2cdev);
			जाओ err_detach_devs;
		पूर्ण
	पूर्ण

	/*
	 * Now execute the controller specअगरic ->bus_init() routine, which
	 * might configure its पूर्णांकernal logic to match the bus limitations.
	 */
	ret = master->ops->bus_init(master);
	अगर (ret)
		जाओ err_detach_devs;

	/*
	 * The master device should have been instantiated in ->bus_init(),
	 * complain अगर this was not the हाल.
	 */
	अगर (!master->this) अणु
		dev_err(&master->dev,
			"master_set_info() was not called in ->bus_init()\n");
		ret = -EINVAL;
		जाओ err_bus_cleanup;
	पूर्ण

	/*
	 * Reset all dynamic address that may have been asचिन्हित beक्रमe
	 * (asचिन्हित by the bootloader क्रम example).
	 */
	ret = i3c_master_rstdaa_locked(master, I3C_BROADCAST_ADDR);
	अगर (ret && ret != I3C_ERROR_M2)
		जाओ err_bus_cleanup;

	/* Disable all slave events beक्रमe starting DAA. */
	ret = i3c_master_disec_locked(master, I3C_BROADCAST_ADDR,
				      I3C_CCC_EVENT_SIR | I3C_CCC_EVENT_MR |
				      I3C_CCC_EVENT_HJ);
	अगर (ret && ret != I3C_ERROR_M2)
		जाओ err_bus_cleanup;

	/*
	 * Reserve init_dyn_addr first, and then try to pre-assign dynamic
	 * address and retrieve device inक्रमmation अगर needed.
	 * In हाल pre-assign dynamic address fails, setting dynamic address to
	 * the requested init_dyn_addr is retried after DAA is करोne in
	 * i3c_master_add_i3c_dev_locked().
	 */
	list_क्रम_each_entry(i3cboardinfo, &master->boardinfo.i3c, node) अणु

		/*
		 * We करोn't reserve a dynamic address क्रम devices that
		 * करोn't explicitly request one.
		 */
		अगर (!i3cboardinfo->init_dyn_addr)
			जारी;

		ret = i3c_bus_get_addr_slot_status(&master->bus,
						   i3cboardinfo->init_dyn_addr);
		अगर (ret != I3C_ADDR_SLOT_FREE) अणु
			ret = -EBUSY;
			जाओ err_rstdaa;
		पूर्ण

		i3c_bus_set_addr_slot_status(&master->bus,
					     i3cboardinfo->init_dyn_addr,
					     I3C_ADDR_SLOT_I3C_DEV);

		/*
		 * Only try to create/attach devices that have a अटल
		 * address. Other devices will be created/attached when
		 * DAA happens, and the requested dynamic address will
		 * be set using SETNEWDA once those devices become
		 * addressable.
		 */

		अगर (i3cboardinfo->अटल_addr)
			i3c_master_early_i3c_dev_add(master, i3cboardinfo);
	पूर्ण

	ret = i3c_master_करो_daa(master);
	अगर (ret)
		जाओ err_rstdaa;

	वापस 0;

err_rstdaa:
	i3c_master_rstdaa_locked(master, I3C_BROADCAST_ADDR);

err_bus_cleanup:
	अगर (master->ops->bus_cleanup)
		master->ops->bus_cleanup(master);

err_detach_devs:
	i3c_master_detach_मुक्त_devs(master);

	वापस ret;
पूर्ण

अटल व्योम i3c_master_bus_cleanup(काष्ठा i3c_master_controller *master)
अणु
	अगर (master->ops->bus_cleanup)
		master->ops->bus_cleanup(master);

	i3c_master_detach_मुक्त_devs(master);
पूर्ण

अटल व्योम i3c_master_attach_boardinfo(काष्ठा i3c_dev_desc *i3cdev)
अणु
	काष्ठा i3c_master_controller *master = i3cdev->common.master;
	काष्ठा i3c_dev_boardinfo *i3cboardinfo;

	list_क्रम_each_entry(i3cboardinfo, &master->boardinfo.i3c, node) अणु
		अगर (i3cdev->info.pid != i3cboardinfo->pid)
			जारी;

		i3cdev->boardinfo = i3cboardinfo;
		i3cdev->info.अटल_addr = i3cboardinfo->अटल_addr;
		वापस;
	पूर्ण
पूर्ण

अटल काष्ठा i3c_dev_desc *
i3c_master_search_i3c_dev_duplicate(काष्ठा i3c_dev_desc *refdev)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(refdev);
	काष्ठा i3c_dev_desc *i3cdev;

	i3c_bus_क्रम_each_i3cdev(&master->bus, i3cdev) अणु
		अगर (i3cdev != refdev && i3cdev->info.pid == refdev->info.pid)
			वापस i3cdev;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * i3c_master_add_i3c_dev_locked() - add an I3C slave to the bus
 * @master: master used to send frames on the bus
 * @addr: I3C slave dynamic address asचिन्हित to the device
 *
 * This function is instantiating an I3C device object and adding it to the
 * I3C device list. All device inक्रमmation are स्वतःmatically retrieved using
 * standard CCC commands.
 *
 * The I3C device object is वापसed in हाल the master wants to attach
 * निजी data to it using i3c_dev_set_master_data().
 *
 * This function must be called with the bus lock held in ग_लिखो mode.
 *
 * Return: a 0 in हाल of success, an negative error code otherwise.
 */
पूर्णांक i3c_master_add_i3c_dev_locked(काष्ठा i3c_master_controller *master,
				  u8 addr)
अणु
	काष्ठा i3c_device_info info = अणु .dyn_addr = addr पूर्ण;
	काष्ठा i3c_dev_desc *newdev, *olddev;
	u8 old_dyn_addr = addr, expected_dyn_addr;
	काष्ठा i3c_ibi_setup ibireq = अणु पूर्ण;
	bool enable_ibi = false;
	पूर्णांक ret;

	अगर (!master)
		वापस -EINVAL;

	newdev = i3c_master_alloc_i3c_dev(master, &info);
	अगर (IS_ERR(newdev))
		वापस PTR_ERR(newdev);

	ret = i3c_master_attach_i3c_dev(master, newdev);
	अगर (ret)
		जाओ err_मुक्त_dev;

	ret = i3c_master_retrieve_dev_info(newdev);
	अगर (ret)
		जाओ err_detach_dev;

	i3c_master_attach_boardinfo(newdev);

	olddev = i3c_master_search_i3c_dev_duplicate(newdev);
	अगर (olddev) अणु
		newdev->dev = olddev->dev;
		अगर (newdev->dev)
			newdev->dev->desc = newdev;

		/*
		 * We need to restore the IBI state too, so let's save the
		 * IBI inक्रमmation and try to restore them after olddev has
		 * been detached+released and its IBI has been stopped and
		 * the associated resources have been मुक्तd.
		 */
		mutex_lock(&olddev->ibi_lock);
		अगर (olddev->ibi) अणु
			ibireq.handler = olddev->ibi->handler;
			ibireq.max_payload_len = olddev->ibi->max_payload_len;
			ibireq.num_slots = olddev->ibi->num_slots;

			अगर (olddev->ibi->enabled) अणु
				enable_ibi = true;
				i3c_dev_disable_ibi_locked(olddev);
			पूर्ण

			i3c_dev_मुक्त_ibi_locked(olddev);
		पूर्ण
		mutex_unlock(&olddev->ibi_lock);

		old_dyn_addr = olddev->info.dyn_addr;

		i3c_master_detach_i3c_dev(olddev);
		i3c_master_मुक्त_i3c_dev(olddev);
	पूर्ण

	ret = i3c_master_reattach_i3c_dev(newdev, old_dyn_addr);
	अगर (ret)
		जाओ err_detach_dev;

	/*
	 * Depending on our previous state, the expected dynamic address might
	 * dअगरfer:
	 * - अगर the device alपढ़ोy had a dynamic address asचिन्हित, let's try to
	 *   re-apply this one
	 * - अगर the device did not have a dynamic address and the firmware
	 *   requested a specअगरic address, pick this one
	 * - in any other हाल, keep the address स्वतःmatically asचिन्हित by the
	 *   master
	 */
	अगर (old_dyn_addr && old_dyn_addr != newdev->info.dyn_addr)
		expected_dyn_addr = old_dyn_addr;
	अन्यथा अगर (newdev->boardinfo && newdev->boardinfo->init_dyn_addr)
		expected_dyn_addr = newdev->boardinfo->init_dyn_addr;
	अन्यथा
		expected_dyn_addr = newdev->info.dyn_addr;

	अगर (newdev->info.dyn_addr != expected_dyn_addr) अणु
		/*
		 * Try to apply the expected dynamic address. If it fails, keep
		 * the address asचिन्हित by the master.
		 */
		ret = i3c_master_setnewda_locked(master,
						 newdev->info.dyn_addr,
						 expected_dyn_addr);
		अगर (!ret) अणु
			old_dyn_addr = newdev->info.dyn_addr;
			newdev->info.dyn_addr = expected_dyn_addr;
			i3c_master_reattach_i3c_dev(newdev, old_dyn_addr);
		पूर्ण अन्यथा अणु
			dev_err(&master->dev,
				"Failed to assign reserved/old address to device %d%llx",
				master->bus.id, newdev->info.pid);
		पूर्ण
	पूर्ण

	/*
	 * Now is समय to try to restore the IBI setup. If we're lucky,
	 * everything works as beक्रमe, otherwise, all we can करो is complain.
	 * FIXME: maybe we should add callback to inक्रमm the driver that it
	 * should request the IBI again instead of trying to hide that from
	 * him.
	 */
	अगर (ibireq.handler) अणु
		mutex_lock(&newdev->ibi_lock);
		ret = i3c_dev_request_ibi_locked(newdev, &ibireq);
		अगर (ret) अणु
			dev_err(&master->dev,
				"Failed to request IBI on device %d-%llx",
				master->bus.id, newdev->info.pid);
		पूर्ण अन्यथा अगर (enable_ibi) अणु
			ret = i3c_dev_enable_ibi_locked(newdev);
			अगर (ret)
				dev_err(&master->dev,
					"Failed to re-enable IBI on device %d-%llx",
					master->bus.id, newdev->info.pid);
		पूर्ण
		mutex_unlock(&newdev->ibi_lock);
	पूर्ण

	वापस 0;

err_detach_dev:
	अगर (newdev->dev && newdev->dev->desc)
		newdev->dev->desc = शून्य;

	i3c_master_detach_i3c_dev(newdev);

err_मुक्त_dev:
	i3c_master_मुक्त_i3c_dev(newdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_add_i3c_dev_locked);

#घोषणा OF_I3C_REG1_IS_I2C_DEV			BIT(31)

अटल पूर्णांक
of_i3c_master_add_i2c_boardinfo(काष्ठा i3c_master_controller *master,
				काष्ठा device_node *node, u32 *reg)
अणु
	काष्ठा i2c_dev_boardinfo *boardinfo;
	काष्ठा device *dev = &master->dev;
	पूर्णांक ret;

	boardinfo = devm_kzalloc(dev, माप(*boardinfo), GFP_KERNEL);
	अगर (!boardinfo)
		वापस -ENOMEM;

	ret = of_i2c_get_board_info(dev, node, &boardinfo->base);
	अगर (ret)
		वापस ret;

	/*
	 * The I3C Specअगरication करोes not clearly say I2C devices with 10-bit
	 * address are supported. These devices can't be passed properly through
	 * DEFSLVS command.
	 */
	अगर (boardinfo->base.flags & I2C_CLIENT_TEN) अणु
		dev_err(dev, "I2C device with 10 bit address not supported.");
		वापस -ENOTSUPP;
	पूर्ण

	/* LVR is encoded in reg[2]. */
	boardinfo->lvr = reg[2];

	list_add_tail(&boardinfo->node, &master->boardinfo.i2c);
	of_node_get(node);

	वापस 0;
पूर्ण

अटल पूर्णांक
of_i3c_master_add_i3c_boardinfo(काष्ठा i3c_master_controller *master,
				काष्ठा device_node *node, u32 *reg)
अणु
	काष्ठा i3c_dev_boardinfo *boardinfo;
	काष्ठा device *dev = &master->dev;
	क्रमागत i3c_addr_slot_status addrstatus;
	u32 init_dyn_addr = 0;

	boardinfo = devm_kzalloc(dev, माप(*boardinfo), GFP_KERNEL);
	अगर (!boardinfo)
		वापस -ENOMEM;

	अगर (reg[0]) अणु
		अगर (reg[0] > I3C_MAX_ADDR)
			वापस -EINVAL;

		addrstatus = i3c_bus_get_addr_slot_status(&master->bus,
							  reg[0]);
		अगर (addrstatus != I3C_ADDR_SLOT_FREE)
			वापस -EINVAL;
	पूर्ण

	boardinfo->अटल_addr = reg[0];

	अगर (!of_property_पढ़ो_u32(node, "assigned-address", &init_dyn_addr)) अणु
		अगर (init_dyn_addr > I3C_MAX_ADDR)
			वापस -EINVAL;

		addrstatus = i3c_bus_get_addr_slot_status(&master->bus,
							  init_dyn_addr);
		अगर (addrstatus != I3C_ADDR_SLOT_FREE)
			वापस -EINVAL;
	पूर्ण

	boardinfo->pid = ((u64)reg[1] << 32) | reg[2];

	अगर ((boardinfo->pid & GENMASK_ULL(63, 48)) ||
	    I3C_PID_RND_LOWER_32BITS(boardinfo->pid))
		वापस -EINVAL;

	boardinfo->init_dyn_addr = init_dyn_addr;
	boardinfo->of_node = of_node_get(node);
	list_add_tail(&boardinfo->node, &master->boardinfo.i3c);

	वापस 0;
पूर्ण

अटल पूर्णांक of_i3c_master_add_dev(काष्ठा i3c_master_controller *master,
				 काष्ठा device_node *node)
अणु
	u32 reg[3];
	पूर्णांक ret;

	अगर (!master || !node)
		वापस -EINVAL;

	ret = of_property_पढ़ो_u32_array(node, "reg", reg, ARRAY_SIZE(reg));
	अगर (ret)
		वापस ret;

	/*
	 * The manufacturer ID can't be 0. If reg[1] == 0 that means we're
	 * dealing with an I2C device.
	 */
	अगर (!reg[1])
		ret = of_i3c_master_add_i2c_boardinfo(master, node, reg);
	अन्यथा
		ret = of_i3c_master_add_i3c_boardinfo(master, node, reg);

	वापस ret;
पूर्ण

अटल पूर्णांक of_populate_i3c_bus(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा device *dev = &master->dev;
	काष्ठा device_node *i3cbus_np = dev->of_node;
	काष्ठा device_node *node;
	पूर्णांक ret;
	u32 val;

	अगर (!i3cbus_np)
		वापस 0;

	क्रम_each_available_child_of_node(i3cbus_np, node) अणु
		ret = of_i3c_master_add_dev(master, node);
		अगर (ret) अणु
			of_node_put(node);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * The user might want to limit I2C and I3C speed in हाल some devices
	 * on the bus are not supporting typical rates, or अगर the bus topology
	 * prevents it from using max possible rate.
	 */
	अगर (!of_property_पढ़ो_u32(i3cbus_np, "i2c-scl-hz", &val))
		master->bus.scl_rate.i2c = val;

	अगर (!of_property_पढ़ो_u32(i3cbus_np, "i3c-scl-hz", &val))
		master->bus.scl_rate.i3c = val;

	वापस 0;
पूर्ण

अटल पूर्णांक i3c_master_i2c_adapter_xfer(काष्ठा i2c_adapter *adap,
				       काष्ठा i2c_msg *xfers, पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *master = i2c_adapter_to_i3c_master(adap);
	काष्ठा i2c_dev_desc *dev;
	पूर्णांक i, ret;
	u16 addr;

	अगर (!xfers || !master || nxfers <= 0)
		वापस -EINVAL;

	अगर (!master->ops->i2c_xfers)
		वापस -ENOTSUPP;

	/* Doing transfers to dअगरferent devices is not supported. */
	addr = xfers[0].addr;
	क्रम (i = 1; i < nxfers; i++) अणु
		अगर (addr != xfers[i].addr)
			वापस -ENOTSUPP;
	पूर्ण

	i3c_bus_normaluse_lock(&master->bus);
	dev = i3c_master_find_i2c_dev_by_addr(master, addr);
	अगर (!dev)
		ret = -ENOENT;
	अन्यथा
		ret = master->ops->i2c_xfers(dev, xfers, nxfers);
	i3c_bus_normaluse_unlock(&master->bus);

	वापस ret ? ret : nxfers;
पूर्ण

अटल u32 i3c_master_i2c_funcs(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_EMUL | I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm i3c_master_i2c_algo = अणु
	.master_xfer = i3c_master_i2c_adapter_xfer,
	.functionality = i3c_master_i2c_funcs,
पूर्ण;

अटल पूर्णांक i3c_master_i2c_adapter_init(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा i2c_adapter *adap = i3c_master_to_i2c_adapter(master);
	काष्ठा i2c_dev_desc *i2cdev;
	पूर्णांक ret;

	adap->dev.parent = master->dev.parent;
	adap->owner = master->dev.parent->driver->owner;
	adap->algo = &i3c_master_i2c_algo;
	म_नकलन(adap->name, dev_name(master->dev.parent), माप(adap->name));

	/* FIXME: Should we allow i3c masters to override these values? */
	adap->समयout = 1000;
	adap->retries = 3;

	ret = i2c_add_adapter(adap);
	अगर (ret)
		वापस ret;

	/*
	 * We silently ignore failures here. The bus should keep working
	 * correctly even अगर one or more i2c devices are not रेजिस्टरed.
	 */
	i3c_bus_क्रम_each_i2cdev(&master->bus, i2cdev)
		i2cdev->dev = i2c_new_client_device(adap, &i2cdev->boardinfo->base);

	वापस 0;
पूर्ण

अटल व्योम i3c_master_i2c_adapter_cleanup(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा i2c_dev_desc *i2cdev;

	i2c_del_adapter(&master->i2c);

	i3c_bus_क्रम_each_i2cdev(&master->bus, i2cdev)
		i2cdev->dev = शून्य;
पूर्ण

अटल व्योम i3c_master_unरेजिस्टर_i3c_devs(काष्ठा i3c_master_controller *master)
अणु
	काष्ठा i3c_dev_desc *i3cdev;

	i3c_bus_क्रम_each_i3cdev(&master->bus, i3cdev) अणु
		अगर (!i3cdev->dev)
			जारी;

		i3cdev->dev->desc = शून्य;
		अगर (device_is_रेजिस्टरed(&i3cdev->dev->dev))
			device_unरेजिस्टर(&i3cdev->dev->dev);
		अन्यथा
			put_device(&i3cdev->dev->dev);
		i3cdev->dev = शून्य;
	पूर्ण
पूर्ण

/**
 * i3c_master_queue_ibi() - Queue an IBI
 * @dev: the device this IBI is coming from
 * @slot: the IBI slot used to store the payload
 *
 * Queue an IBI to the controller workqueue. The IBI handler attached to
 * the dev will be called from a workqueue context.
 */
व्योम i3c_master_queue_ibi(काष्ठा i3c_dev_desc *dev, काष्ठा i3c_ibi_slot *slot)
अणु
	atomic_inc(&dev->ibi->pending_ibis);
	queue_work(dev->common.master->wq, &slot->work);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_queue_ibi);

अटल व्योम i3c_master_handle_ibi(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा i3c_ibi_slot *slot = container_of(work, काष्ठा i3c_ibi_slot,
						 work);
	काष्ठा i3c_dev_desc *dev = slot->dev;
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);
	काष्ठा i3c_ibi_payload payload;

	payload.data = slot->data;
	payload.len = slot->len;

	अगर (dev->dev)
		dev->ibi->handler(dev->dev, &payload);

	master->ops->recycle_ibi_slot(dev, slot);
	अगर (atomic_dec_and_test(&dev->ibi->pending_ibis))
		complete(&dev->ibi->all_ibis_handled);
पूर्ण

अटल व्योम i3c_master_init_ibi_slot(काष्ठा i3c_dev_desc *dev,
				     काष्ठा i3c_ibi_slot *slot)
अणु
	slot->dev = dev;
	INIT_WORK(&slot->work, i3c_master_handle_ibi);
पूर्ण

काष्ठा i3c_generic_ibi_slot अणु
	काष्ठा list_head node;
	काष्ठा i3c_ibi_slot base;
पूर्ण;

काष्ठा i3c_generic_ibi_pool अणु
	spinlock_t lock;
	अचिन्हित पूर्णांक num_slots;
	काष्ठा i3c_generic_ibi_slot *slots;
	व्योम *payload_buf;
	काष्ठा list_head मुक्त_slots;
	काष्ठा list_head pending;
पूर्ण;

/**
 * i3c_generic_ibi_मुक्त_pool() - Free a generic IBI pool
 * @pool: the IBI pool to मुक्त
 *
 * Free all IBI slots allated by a generic IBI pool.
 */
व्योम i3c_generic_ibi_मुक्त_pool(काष्ठा i3c_generic_ibi_pool *pool)
अणु
	काष्ठा i3c_generic_ibi_slot *slot;
	अचिन्हित पूर्णांक nslots = 0;

	जबतक (!list_empty(&pool->मुक्त_slots)) अणु
		slot = list_first_entry(&pool->मुक्त_slots,
					काष्ठा i3c_generic_ibi_slot, node);
		list_del(&slot->node);
		nslots++;
	पूर्ण

	/*
	 * If the number of मुक्तd slots is not equal to the number of allocated
	 * slots we have a leak somewhere.
	 */
	WARN_ON(nslots != pool->num_slots);

	kमुक्त(pool->payload_buf);
	kमुक्त(pool->slots);
	kमुक्त(pool);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_generic_ibi_मुक्त_pool);

/**
 * i3c_generic_ibi_alloc_pool() - Create a generic IBI pool
 * @dev: the device this pool will be used क्रम
 * @req: IBI setup request describing what the device driver expects
 *
 * Create a generic IBI pool based on the inक्रमmation provided in @req.
 *
 * Return: a valid IBI pool in हाल of success, an ERR_PTR() otherwise.
 */
काष्ठा i3c_generic_ibi_pool *
i3c_generic_ibi_alloc_pool(काष्ठा i3c_dev_desc *dev,
			   स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	काष्ठा i3c_generic_ibi_pool *pool;
	काष्ठा i3c_generic_ibi_slot *slot;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	pool = kzalloc(माप(*pool), GFP_KERNEL);
	अगर (!pool)
		वापस ERR_PTR(-ENOMEM);

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->मुक्त_slots);
	INIT_LIST_HEAD(&pool->pending);

	pool->slots = kसुस्मृति(req->num_slots, माप(*slot), GFP_KERNEL);
	अगर (!pool->slots) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_pool;
	पूर्ण

	अगर (req->max_payload_len) अणु
		pool->payload_buf = kसुस्मृति(req->num_slots,
					    req->max_payload_len, GFP_KERNEL);
		अगर (!pool->payload_buf) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_pool;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < req->num_slots; i++) अणु
		slot = &pool->slots[i];
		i3c_master_init_ibi_slot(dev, &slot->base);

		अगर (req->max_payload_len)
			slot->base.data = pool->payload_buf +
					  (i * req->max_payload_len);

		list_add_tail(&slot->node, &pool->मुक्त_slots);
		pool->num_slots++;
	पूर्ण

	वापस pool;

err_मुक्त_pool:
	i3c_generic_ibi_मुक्त_pool(pool);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_generic_ibi_alloc_pool);

/**
 * i3c_generic_ibi_get_मुक्त_slot() - Get a मुक्त slot from a generic IBI pool
 * @pool: the pool to query an IBI slot on
 *
 * Search क्रम a मुक्त slot in a generic IBI pool.
 * The slot should be वापसed to the pool using i3c_generic_ibi_recycle_slot()
 * when it's no दीर्घer needed.
 *
 * Return: a poपूर्णांकer to a मुक्त slot, or शून्य अगर there's no मुक्त slot available.
 */
काष्ठा i3c_ibi_slot *
i3c_generic_ibi_get_मुक्त_slot(काष्ठा i3c_generic_ibi_pool *pool)
अणु
	काष्ठा i3c_generic_ibi_slot *slot;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pool->lock, flags);
	slot = list_first_entry_or_null(&pool->मुक्त_slots,
					काष्ठा i3c_generic_ibi_slot, node);
	अगर (slot)
		list_del(&slot->node);
	spin_unlock_irqrestore(&pool->lock, flags);

	वापस slot ? &slot->base : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_generic_ibi_get_मुक्त_slot);

/**
 * i3c_generic_ibi_recycle_slot() - Return a slot to a generic IBI pool
 * @pool: the pool to वापस the IBI slot to
 * @s: IBI slot to recycle
 *
 * Add an IBI slot back to its generic IBI pool. Should be called from the
 * master driver काष्ठा_master_controller_ops->recycle_ibi() method.
 */
व्योम i3c_generic_ibi_recycle_slot(काष्ठा i3c_generic_ibi_pool *pool,
				  काष्ठा i3c_ibi_slot *s)
अणु
	काष्ठा i3c_generic_ibi_slot *slot;
	अचिन्हित दीर्घ flags;

	अगर (!s)
		वापस;

	slot = container_of(s, काष्ठा i3c_generic_ibi_slot, base);
	spin_lock_irqsave(&pool->lock, flags);
	list_add_tail(&slot->node, &pool->मुक्त_slots);
	spin_unlock_irqrestore(&pool->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_generic_ibi_recycle_slot);

अटल पूर्णांक i3c_master_check_ops(स्थिर काष्ठा i3c_master_controller_ops *ops)
अणु
	अगर (!ops || !ops->bus_init || !ops->priv_xfers ||
	    !ops->send_ccc_cmd || !ops->करो_daa || !ops->i2c_xfers)
		वापस -EINVAL;

	अगर (ops->request_ibi &&
	    (!ops->enable_ibi || !ops->disable_ibi || !ops->मुक्त_ibi ||
	     !ops->recycle_ibi_slot))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/**
 * i3c_master_रेजिस्टर() - रेजिस्टर an I3C master
 * @master: master used to send frames on the bus
 * @parent: the parent device (the one that provides this I3C master
 *	    controller)
 * @ops: the master controller operations
 * @secondary: true अगर you are रेजिस्टरing a secondary master. Will वापस
 *	       -ENOTSUPP अगर set to true since secondary masters are not yet
 *	       supported
 *
 * This function takes care of everything क्रम you:
 *
 * - creates and initializes the I3C bus
 * - populates the bus with अटल I2C devs अगर @parent->of_node is not
 *   शून्य
 * - रेजिस्टरs all I3C devices added by the controller during bus
 *   initialization
 * - रेजिस्टरs the I2C adapter and all I2C devices
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक i3c_master_रेजिस्टर(काष्ठा i3c_master_controller *master,
			काष्ठा device *parent,
			स्थिर काष्ठा i3c_master_controller_ops *ops,
			bool secondary)
अणु
	अचिन्हित दीर्घ i2c_scl_rate = I3C_BUS_I2C_FM_PLUS_SCL_RATE;
	काष्ठा i3c_bus *i3cbus = i3c_master_get_bus(master);
	क्रमागत i3c_bus_mode mode = I3C_BUS_MODE_PURE;
	काष्ठा i2c_dev_boardinfo *i2cbi;
	पूर्णांक ret;

	/* We करो not support secondary masters yet. */
	अगर (secondary)
		वापस -ENOTSUPP;

	ret = i3c_master_check_ops(ops);
	अगर (ret)
		वापस ret;

	master->dev.parent = parent;
	master->dev.of_node = of_node_get(parent->of_node);
	master->dev.bus = &i3c_bus_type;
	master->dev.type = &i3c_masterdev_type;
	master->dev.release = i3c_masterdev_release;
	master->ops = ops;
	master->secondary = secondary;
	INIT_LIST_HEAD(&master->boardinfo.i2c);
	INIT_LIST_HEAD(&master->boardinfo.i3c);

	ret = i3c_bus_init(i3cbus);
	अगर (ret)
		वापस ret;

	device_initialize(&master->dev);
	dev_set_name(&master->dev, "i3c-%d", i3cbus->id);

	ret = of_populate_i3c_bus(master);
	अगर (ret)
		जाओ err_put_dev;

	list_क्रम_each_entry(i2cbi, &master->boardinfo.i2c, node) अणु
		चयन (i2cbi->lvr & I3C_LVR_I2C_INDEX_MASK) अणु
		हाल I3C_LVR_I2C_INDEX(0):
			अगर (mode < I3C_BUS_MODE_MIXED_FAST)
				mode = I3C_BUS_MODE_MIXED_FAST;
			अवरोध;
		हाल I3C_LVR_I2C_INDEX(1):
			अगर (mode < I3C_BUS_MODE_MIXED_LIMITED)
				mode = I3C_BUS_MODE_MIXED_LIMITED;
			अवरोध;
		हाल I3C_LVR_I2C_INDEX(2):
			अगर (mode < I3C_BUS_MODE_MIXED_SLOW)
				mode = I3C_BUS_MODE_MIXED_SLOW;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ err_put_dev;
		पूर्ण

		अगर (i2cbi->lvr & I3C_LVR_I2C_FM_MODE)
			i2c_scl_rate = I3C_BUS_I2C_FM_SCL_RATE;
	पूर्ण

	ret = i3c_bus_set_mode(i3cbus, mode, i2c_scl_rate);
	अगर (ret)
		जाओ err_put_dev;

	master->wq = alloc_workqueue("%s", 0, 0, dev_name(parent));
	अगर (!master->wq) अणु
		ret = -ENOMEM;
		जाओ err_put_dev;
	पूर्ण

	ret = i3c_master_bus_init(master);
	अगर (ret)
		जाओ err_put_dev;

	ret = device_add(&master->dev);
	अगर (ret)
		जाओ err_cleanup_bus;

	/*
	 * Expose our I3C bus as an I2C adapter so that I2C devices are exposed
	 * through the I2C subप्रणाली.
	 */
	ret = i3c_master_i2c_adapter_init(master);
	अगर (ret)
		जाओ err_del_dev;

	/*
	 * We're करोne initializing the bus and the controller, we can now
	 * रेजिस्टर I3C devices discovered during the initial DAA.
	 */
	master->init_करोne = true;
	i3c_bus_normaluse_lock(&master->bus);
	i3c_master_रेजिस्टर_new_i3c_devs(master);
	i3c_bus_normaluse_unlock(&master->bus);

	वापस 0;

err_del_dev:
	device_del(&master->dev);

err_cleanup_bus:
	i3c_master_bus_cleanup(master);

err_put_dev:
	put_device(&master->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_रेजिस्टर);

/**
 * i3c_master_unरेजिस्टर() - unरेजिस्टर an I3C master
 * @master: master used to send frames on the bus
 *
 * Basically unकरो everything करोne in i3c_master_रेजिस्टर().
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
पूर्णांक i3c_master_unरेजिस्टर(काष्ठा i3c_master_controller *master)
अणु
	i3c_master_i2c_adapter_cleanup(master);
	i3c_master_unरेजिस्टर_i3c_devs(master);
	i3c_master_bus_cleanup(master);
	device_unरेजिस्टर(&master->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_master_unरेजिस्टर);

पूर्णांक i3c_dev_करो_priv_xfers_locked(काष्ठा i3c_dev_desc *dev,
				 काष्ठा i3c_priv_xfer *xfers,
				 पूर्णांक nxfers)
अणु
	काष्ठा i3c_master_controller *master;

	अगर (!dev)
		वापस -ENOENT;

	master = i3c_dev_get_master(dev);
	अगर (!master || !xfers)
		वापस -EINVAL;

	अगर (!master->ops->priv_xfers)
		वापस -ENOTSUPP;

	वापस master->ops->priv_xfers(dev, xfers, nxfers);
पूर्ण

पूर्णांक i3c_dev_disable_ibi_locked(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master;
	पूर्णांक ret;

	अगर (!dev->ibi)
		वापस -EINVAL;

	master = i3c_dev_get_master(dev);
	ret = master->ops->disable_ibi(dev);
	अगर (ret)
		वापस ret;

	reinit_completion(&dev->ibi->all_ibis_handled);
	अगर (atomic_पढ़ो(&dev->ibi->pending_ibis))
		रुको_क्रम_completion(&dev->ibi->all_ibis_handled);

	dev->ibi->enabled = false;

	वापस 0;
पूर्ण

पूर्णांक i3c_dev_enable_ibi_locked(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);
	पूर्णांक ret;

	अगर (!dev->ibi)
		वापस -EINVAL;

	ret = master->ops->enable_ibi(dev);
	अगर (!ret)
		dev->ibi->enabled = true;

	वापस ret;
पूर्ण

पूर्णांक i3c_dev_request_ibi_locked(काष्ठा i3c_dev_desc *dev,
			       स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);
	काष्ठा i3c_device_ibi_info *ibi;
	पूर्णांक ret;

	अगर (!master->ops->request_ibi)
		वापस -ENOTSUPP;

	अगर (dev->ibi)
		वापस -EBUSY;

	ibi = kzalloc(माप(*ibi), GFP_KERNEL);
	अगर (!ibi)
		वापस -ENOMEM;

	atomic_set(&ibi->pending_ibis, 0);
	init_completion(&ibi->all_ibis_handled);
	ibi->handler = req->handler;
	ibi->max_payload_len = req->max_payload_len;
	ibi->num_slots = req->num_slots;

	dev->ibi = ibi;
	ret = master->ops->request_ibi(dev, req);
	अगर (ret) अणु
		kमुक्त(ibi);
		dev->ibi = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

व्योम i3c_dev_मुक्त_ibi_locked(काष्ठा i3c_dev_desc *dev)
अणु
	काष्ठा i3c_master_controller *master = i3c_dev_get_master(dev);

	अगर (!dev->ibi)
		वापस;

	अगर (WARN_ON(dev->ibi->enabled))
		WARN_ON(i3c_dev_disable_ibi_locked(dev));

	master->ops->मुक्त_ibi(dev);
	kमुक्त(dev->ibi);
	dev->ibi = शून्य;
पूर्ण

अटल पूर्णांक __init i3c_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&i3c_bus_type);
पूर्ण
subsys_initcall(i3c_init);

अटल व्योम __निकास i3c_निकास(व्योम)
अणु
	idr_destroy(&i3c_bus_idr);
	bus_unरेजिस्टर(&i3c_bus_type);
पूर्ण
module_निकास(i3c_निकास);

MODULE_AUTHOR("Boris Brezillon <boris.brezillon@bootlin.com>");
MODULE_DESCRIPTION("I3C core");
MODULE_LICENSE("GPL v2");
