<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RapidIO driver support
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_ids.h>
#समावेश <linux/rio_drv.h>

#समावेश "rio.h"

/**
 *  rio_match_device - Tell अगर a RIO device has a matching RIO device id काष्ठाure
 *  @id: the RIO device id काष्ठाure to match against
 *  @rdev: the RIO device काष्ठाure to match against
 *
 *  Used from driver probe and bus matching to check whether a RIO device
 *  matches a device id काष्ठाure provided by a RIO driver. Returns the
 *  matching &काष्ठा rio_device_id or %शून्य अगर there is no match.
 */
अटल स्थिर काष्ठा rio_device_id *rio_match_device(स्थिर काष्ठा rio_device_id
						    *id,
						    स्थिर काष्ठा rio_dev *rdev)
अणु
	जबतक (id->vid || id->यंत्र_vid) अणु
		अगर (((id->vid == RIO_ANY_ID) || (id->vid == rdev->vid)) &&
		    ((id->did == RIO_ANY_ID) || (id->did == rdev->did)) &&
		    ((id->यंत्र_vid == RIO_ANY_ID)
		     || (id->यंत्र_vid == rdev->यंत्र_vid))
		    && ((id->यंत्र_did == RIO_ANY_ID)
			|| (id->यंत्र_did == rdev->यंत्र_did)))
			वापस id;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * rio_dev_get - Increments the reference count of the RIO device काष्ठाure
 *
 * @rdev: RIO device being referenced
 *
 * Each live reference to a device should be refcounted.
 *
 * Drivers क्रम RIO devices should normally record such references in
 * their probe() methods, when they bind to a device, and release
 * them by calling rio_dev_put(), in their disconnect() methods.
 */
काष्ठा rio_dev *rio_dev_get(काष्ठा rio_dev *rdev)
अणु
	अगर (rdev)
		get_device(&rdev->dev);

	वापस rdev;
पूर्ण

/**
 * rio_dev_put - Release a use of the RIO device काष्ठाure
 *
 * @rdev: RIO device being disconnected
 *
 * Must be called when a user of a device is finished with it.
 * When the last user of the device calls this function, the
 * memory of the device is मुक्तd.
 */
व्योम rio_dev_put(काष्ठा rio_dev *rdev)
अणु
	अगर (rdev)
		put_device(&rdev->dev);
पूर्ण

/**
 *  rio_device_probe - Tell अगर a RIO device काष्ठाure has a matching RIO device id काष्ठाure
 *  @dev: the RIO device काष्ठाure to match against
 *
 * वापस 0 and set rio_dev->driver when drv claims rio_dev, अन्यथा error
 */
अटल पूर्णांक rio_device_probe(काष्ठा device *dev)
अणु
	काष्ठा rio_driver *rdrv = to_rio_driver(dev->driver);
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	पूर्णांक error = -ENODEV;
	स्थिर काष्ठा rio_device_id *id;

	अगर (!rdev->driver && rdrv->probe) अणु
		अगर (!rdrv->id_table)
			वापस error;
		id = rio_match_device(rdrv->id_table, rdev);
		rio_dev_get(rdev);
		अगर (id)
			error = rdrv->probe(rdev, id);
		अगर (error >= 0) अणु
			rdev->driver = rdrv;
			error = 0;
		पूर्ण अन्यथा
			rio_dev_put(rdev);
	पूर्ण
	वापस error;
पूर्ण

/**
 *  rio_device_हटाओ - Remove a RIO device from the प्रणाली
 *
 *  @dev: the RIO device काष्ठाure to match against
 *
 * Remove a RIO device from the प्रणाली. If it has an associated
 * driver, then run the driver हटाओ() method.  Then update
 * the reference count.
 */
अटल पूर्णांक rio_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	काष्ठा rio_driver *rdrv = rdev->driver;

	अगर (rdrv) अणु
		अगर (rdrv->हटाओ)
			rdrv->हटाओ(rdev);
		rdev->driver = शून्य;
	पूर्ण

	rio_dev_put(rdev);

	वापस 0;
पूर्ण

अटल व्योम rio_device_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	काष्ठा rio_driver *rdrv = rdev->driver;

	dev_dbg(dev, "RIO: %s\n", __func__);

	अगर (rdrv && rdrv->shutकरोwn)
		rdrv->shutकरोwn(rdev);
पूर्ण

/**
 *  rio_रेजिस्टर_driver - रेजिस्टर a new RIO driver
 *  @rdrv: the RIO driver काष्ठाure to रेजिस्टर
 *
 *  Adds a &काष्ठा rio_driver to the list of रेजिस्टरed drivers.
 *  Returns a negative value on error, otherwise 0. If no error
 *  occurred, the driver reमुख्यs रेजिस्टरed even अगर no device
 *  was claimed during registration.
 */
पूर्णांक rio_रेजिस्टर_driver(काष्ठा rio_driver *rdrv)
अणु
	/* initialize common driver fields */
	rdrv->driver.name = rdrv->name;
	rdrv->driver.bus = &rio_bus_type;

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&rdrv->driver);
पूर्ण

/**
 *  rio_unरेजिस्टर_driver - unरेजिस्टर a RIO driver
 *  @rdrv: the RIO driver काष्ठाure to unरेजिस्टर
 *
 *  Deletes the &काष्ठा rio_driver from the list of रेजिस्टरed RIO
 *  drivers, gives it a chance to clean up by calling its हटाओ()
 *  function क्रम each device it was responsible क्रम, and marks those
 *  devices as driverless.
 */
व्योम rio_unरेजिस्टर_driver(काष्ठा rio_driver *rdrv)
अणु
	driver_unरेजिस्टर(&rdrv->driver);
पूर्ण

व्योम rio_attach_device(काष्ठा rio_dev *rdev)
अणु
	rdev->dev.bus = &rio_bus_type;
पूर्ण
EXPORT_SYMBOL_GPL(rio_attach_device);

/**
 *  rio_match_bus - Tell अगर a RIO device काष्ठाure has a matching RIO driver device id काष्ठाure
 *  @dev: the standard device काष्ठाure to match against
 *  @drv: the standard driver काष्ठाure containing the ids to match against
 *
 *  Used by a driver to check whether a RIO device present in the
 *  प्रणाली is in its list of supported devices. Returns 1 अगर
 *  there is a matching &काष्ठा rio_device_id or 0 अगर there is
 *  no match.
 */
अटल पूर्णांक rio_match_bus(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा rio_dev *rdev = to_rio_dev(dev);
	काष्ठा rio_driver *rdrv = to_rio_driver(drv);
	स्थिर काष्ठा rio_device_id *id = rdrv->id_table;
	स्थिर काष्ठा rio_device_id *found_id;

	अगर (!id)
		जाओ out;

	found_id = rio_match_device(id, rdev);

	अगर (found_id)
		वापस 1;

      out:वापस 0;
पूर्ण

अटल पूर्णांक rio_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा rio_dev *rdev;

	अगर (!dev)
		वापस -ENODEV;

	rdev = to_rio_dev(dev);
	अगर (!rdev)
		वापस -ENODEV;

	अगर (add_uevent_var(env, "MODALIAS=rapidio:v%04Xd%04Xav%04Xad%04X",
			   rdev->vid, rdev->did, rdev->यंत्र_vid, rdev->यंत्र_did))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

काष्ठा class rio_mport_class = अणु
	.name		= "rapidio_port",
	.owner		= THIS_MODULE,
	.dev_groups	= rio_mport_groups,
पूर्ण;
EXPORT_SYMBOL_GPL(rio_mport_class);

काष्ठा bus_type rio_bus_type = अणु
	.name = "rapidio",
	.match = rio_match_bus,
	.dev_groups = rio_dev_groups,
	.bus_groups = rio_bus_groups,
	.probe = rio_device_probe,
	.हटाओ = rio_device_हटाओ,
	.shutकरोwn = rio_device_shutकरोwn,
	.uevent	= rio_uevent,
पूर्ण;

/**
 *  rio_bus_init - Register the RapidIO bus with the device model
 *
 *  Registers the RIO mport device class and RIO bus type with the Linux
 *  device model.
 */
अटल पूर्णांक __init rio_bus_init(व्योम)
अणु
	पूर्णांक ret;

	ret = class_रेजिस्टर(&rio_mport_class);
	अगर (!ret) अणु
		ret = bus_रेजिस्टर(&rio_bus_type);
		अगर (ret)
			class_unरेजिस्टर(&rio_mport_class);
	पूर्ण
	वापस ret;
पूर्ण

postcore_initcall(rio_bus_init);

EXPORT_SYMBOL_GPL(rio_रेजिस्टर_driver);
EXPORT_SYMBOL_GPL(rio_unरेजिस्टर_driver);
EXPORT_SYMBOL_GPL(rio_bus_type);
EXPORT_SYMBOL_GPL(rio_dev_get);
EXPORT_SYMBOL_GPL(rio_dev_put);
