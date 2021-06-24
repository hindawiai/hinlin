<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश "internals.h"

/**
 * i3c_device_करो_priv_xfers() - करो I3C SDR निजी transfers directed to a
 *				specअगरic device
 *
 * @dev: device with which the transfers should be करोne
 * @xfers: array of transfers
 * @nxfers: number of transfers
 *
 * Initiate one or several निजी SDR transfers with @dev.
 *
 * This function can sleep and thus cannot be called in atomic context.
 *
 * Return: 0 in हाल of success, a negative error core otherwise.
 */
पूर्णांक i3c_device_करो_priv_xfers(काष्ठा i3c_device *dev,
			     काष्ठा i3c_priv_xfer *xfers,
			     पूर्णांक nxfers)
अणु
	पूर्णांक ret, i;

	अगर (nxfers < 1)
		वापस 0;

	क्रम (i = 0; i < nxfers; i++) अणु
		अगर (!xfers[i].len || !xfers[i].data.in)
			वापस -EINVAL;
	पूर्ण

	i3c_bus_normaluse_lock(dev->bus);
	ret = i3c_dev_करो_priv_xfers_locked(dev->desc, xfers, nxfers);
	i3c_bus_normaluse_unlock(dev->bus);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_device_करो_priv_xfers);

/**
 * i3c_device_get_info() - get I3C device inक्रमmation
 *
 * @dev: device we want inक्रमmation on
 * @info: the inक्रमmation object to fill in
 *
 * Retrieve I3C dev info.
 */
व्योम i3c_device_get_info(काष्ठा i3c_device *dev,
			 काष्ठा i3c_device_info *info)
अणु
	अगर (!info)
		वापस;

	i3c_bus_normaluse_lock(dev->bus);
	अगर (dev->desc)
		*info = dev->desc->info;
	i3c_bus_normaluse_unlock(dev->bus);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_device_get_info);

/**
 * i3c_device_disable_ibi() - Disable IBIs coming from a specअगरic device
 * @dev: device on which IBIs should be disabled
 *
 * This function disable IBIs coming from a specअगरic device and रुको क्रम
 * all pending IBIs to be processed.
 *
 * Return: 0 in हाल of success, a negative error core otherwise.
 */
पूर्णांक i3c_device_disable_ibi(काष्ठा i3c_device *dev)
अणु
	पूर्णांक ret = -ENOENT;

	i3c_bus_normaluse_lock(dev->bus);
	अगर (dev->desc) अणु
		mutex_lock(&dev->desc->ibi_lock);
		ret = i3c_dev_disable_ibi_locked(dev->desc);
		mutex_unlock(&dev->desc->ibi_lock);
	पूर्ण
	i3c_bus_normaluse_unlock(dev->bus);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_device_disable_ibi);

/**
 * i3c_device_enable_ibi() - Enable IBIs coming from a specअगरic device
 * @dev: device on which IBIs should be enabled
 *
 * This function enable IBIs coming from a specअगरic device and रुको क्रम
 * all pending IBIs to be processed. This should be called on a device
 * where i3c_device_request_ibi() has succeeded.
 *
 * Note that IBIs from this device might be received beक्रमe this function
 * वापसs to its caller.
 *
 * Return: 0 in हाल of success, a negative error core otherwise.
 */
पूर्णांक i3c_device_enable_ibi(काष्ठा i3c_device *dev)
अणु
	पूर्णांक ret = -ENOENT;

	i3c_bus_normaluse_lock(dev->bus);
	अगर (dev->desc) अणु
		mutex_lock(&dev->desc->ibi_lock);
		ret = i3c_dev_enable_ibi_locked(dev->desc);
		mutex_unlock(&dev->desc->ibi_lock);
	पूर्ण
	i3c_bus_normaluse_unlock(dev->bus);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_device_enable_ibi);

/**
 * i3c_device_request_ibi() - Request an IBI
 * @dev: device क्रम which we should enable IBIs
 * @req: setup requested क्रम this IBI
 *
 * This function is responsible क्रम pre-allocating all resources needed to
 * process IBIs coming from @dev. When this function वापसs, the IBI is not
 * enabled until i3c_device_enable_ibi() is called.
 *
 * Return: 0 in हाल of success, a negative error core otherwise.
 */
पूर्णांक i3c_device_request_ibi(काष्ठा i3c_device *dev,
			   स्थिर काष्ठा i3c_ibi_setup *req)
अणु
	पूर्णांक ret = -ENOENT;

	अगर (!req->handler || !req->num_slots)
		वापस -EINVAL;

	i3c_bus_normaluse_lock(dev->bus);
	अगर (dev->desc) अणु
		mutex_lock(&dev->desc->ibi_lock);
		ret = i3c_dev_request_ibi_locked(dev->desc, req);
		mutex_unlock(&dev->desc->ibi_lock);
	पूर्ण
	i3c_bus_normaluse_unlock(dev->bus);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_device_request_ibi);

/**
 * i3c_device_मुक्त_ibi() - Free all resources needed क्रम IBI handling
 * @dev: device on which you want to release IBI resources
 *
 * This function is responsible क्रम de-allocating resources previously
 * allocated by i3c_device_request_ibi(). It should be called after disabling
 * IBIs with i3c_device_disable_ibi().
 */
व्योम i3c_device_मुक्त_ibi(काष्ठा i3c_device *dev)
अणु
	i3c_bus_normaluse_lock(dev->bus);
	अगर (dev->desc) अणु
		mutex_lock(&dev->desc->ibi_lock);
		i3c_dev_मुक्त_ibi_locked(dev->desc);
		mutex_unlock(&dev->desc->ibi_lock);
	पूर्ण
	i3c_bus_normaluse_unlock(dev->bus);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_device_मुक्त_ibi);

/**
 * i3cdev_to_dev() - Returns the device embedded in @i3cdev
 * @i3cdev: I3C device
 *
 * Return: a poपूर्णांकer to a device object.
 */
काष्ठा device *i3cdev_to_dev(काष्ठा i3c_device *i3cdev)
अणु
	वापस &i3cdev->dev;
पूर्ण
EXPORT_SYMBOL_GPL(i3cdev_to_dev);

/**
 * dev_to_i3cdev() - Returns the I3C device containing @dev
 * @dev: device object
 *
 * Return: a poपूर्णांकer to an I3C device object.
 */
काष्ठा i3c_device *dev_to_i3cdev(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा i3c_device, dev);
पूर्ण
EXPORT_SYMBOL_GPL(dev_to_i3cdev);

/**
 * i3c_device_match_id() - Returns the i3c_device_id entry matching @i3cdev
 * @i3cdev: I3C device
 * @id_table: I3C device match table
 *
 * Return: a poपूर्णांकer to an i3c_device_id object or शून्य अगर there's no match.
 */
स्थिर काष्ठा i3c_device_id *
i3c_device_match_id(काष्ठा i3c_device *i3cdev,
		    स्थिर काष्ठा i3c_device_id *id_table)
अणु
	काष्ठा i3c_device_info devinfo;
	स्थिर काष्ठा i3c_device_id *id;
	u16 manuf, part, ext_info;
	bool rndpid;

	i3c_device_get_info(i3cdev, &devinfo);

	manuf = I3C_PID_MANUF_ID(devinfo.pid);
	part = I3C_PID_PART_ID(devinfo.pid);
	ext_info = I3C_PID_EXTRA_INFO(devinfo.pid);
	rndpid = I3C_PID_RND_LOWER_32BITS(devinfo.pid);

	क्रम (id = id_table; id->match_flags != 0; id++) अणु
		अगर ((id->match_flags & I3C_MATCH_DCR) &&
		    id->dcr != devinfo.dcr)
			जारी;

		अगर ((id->match_flags & I3C_MATCH_MANUF) &&
		    id->manuf_id != manuf)
			जारी;

		अगर ((id->match_flags & I3C_MATCH_PART) &&
		    (rndpid || id->part_id != part))
			जारी;

		अगर ((id->match_flags & I3C_MATCH_EXTRA_INFO) &&
		    (rndpid || id->extra_info != ext_info))
			जारी;

		वापस id;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(i3c_device_match_id);

/**
 * i3c_driver_रेजिस्टर_with_owner() - रेजिस्टर an I3C device driver
 *
 * @drv: driver to रेजिस्टर
 * @owner: module that owns this driver
 *
 * Register @drv to the core.
 *
 * Return: 0 in हाल of success, a negative error core otherwise.
 */
पूर्णांक i3c_driver_रेजिस्टर_with_owner(काष्ठा i3c_driver *drv, काष्ठा module *owner)
अणु
	drv->driver.owner = owner;
	drv->driver.bus = &i3c_bus_type;

	अगर (!drv->probe) अणु
		pr_err("Trying to register an i3c driver without probe callback\n");
		वापस -EINVAL;
	पूर्ण

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_driver_रेजिस्टर_with_owner);

/**
 * i3c_driver_unरेजिस्टर() - unरेजिस्टर an I3C device driver
 *
 * @drv: driver to unरेजिस्टर
 *
 * Unरेजिस्टर @drv.
 */
व्योम i3c_driver_unरेजिस्टर(काष्ठा i3c_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(i3c_driver_unरेजिस्टर);
