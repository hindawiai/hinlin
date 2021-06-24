<शैली गुरु>
/*
 *  Zorro Driver Services
 *
 *  Copyright (C) 2003 Geert Uytterhoeven
 *
 *  Loosely based on drivers/pci/pci-driver.c
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/zorro.h>

#समावेश "zorro.h"


    /**
     *  zorro_match_device - Tell अगर a Zorro device काष्ठाure has a matching
     *                       Zorro device id काष्ठाure
     *  @ids: array of Zorro device id काष्ठाures to search in
     *  @dev: the Zorro device काष्ठाure to match against
     *
     *  Used by a driver to check whether a Zorro device present in the
     *  प्रणाली is in its list of supported devices. Returns the matching
     *  zorro_device_id काष्ठाure or %शून्य अगर there is no match.
     */

अटल स्थिर काष्ठा zorro_device_id *
zorro_match_device(स्थिर काष्ठा zorro_device_id *ids,
		   स्थिर काष्ठा zorro_dev *z)
अणु
	जबतक (ids->id) अणु
		अगर (ids->id == ZORRO_WILDCARD || ids->id == z->id)
			वापस ids;
		ids++;
	पूर्ण
	वापस शून्य;
पूर्ण


अटल पूर्णांक zorro_device_probe(काष्ठा device *dev)
अणु
	पूर्णांक error = 0;
	काष्ठा zorro_driver *drv = to_zorro_driver(dev->driver);
	काष्ठा zorro_dev *z = to_zorro_dev(dev);

	अगर (!z->driver && drv->probe) अणु
		स्थिर काष्ठा zorro_device_id *id;

		id = zorro_match_device(drv->id_table, z);
		अगर (id)
			error = drv->probe(z, id);
		अगर (error >= 0) अणु
			z->driver = drv;
			error = 0;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण


अटल पूर्णांक zorro_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा zorro_dev *z = to_zorro_dev(dev);
	काष्ठा zorro_driver *drv = to_zorro_driver(dev->driver);

	अगर (drv) अणु
		अगर (drv->हटाओ)
			drv->हटाओ(z);
		z->driver = शून्य;
	पूर्ण
	वापस 0;
पूर्ण


    /**
     *  zorro_रेजिस्टर_driver - रेजिस्टर a new Zorro driver
     *  @drv: the driver काष्ठाure to रेजिस्टर
     *
     *  Adds the driver काष्ठाure to the list of रेजिस्टरed drivers
     *  Returns zero or a negative error value.
     */

पूर्णांक zorro_रेजिस्टर_driver(काष्ठा zorro_driver *drv)
अणु
	/* initialize common driver fields */
	drv->driver.name = drv->name;
	drv->driver.bus = &zorro_bus_type;

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(zorro_रेजिस्टर_driver);


    /**
     *  zorro_unरेजिस्टर_driver - unरेजिस्टर a zorro driver
     *  @drv: the driver काष्ठाure to unरेजिस्टर
     *
     *  Deletes the driver काष्ठाure from the list of रेजिस्टरed Zorro drivers,
     *  gives it a chance to clean up by calling its हटाओ() function क्रम
     *  each device it was responsible क्रम, and marks those devices as
     *  driverless.
     */

व्योम zorro_unरेजिस्टर_driver(काष्ठा zorro_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL(zorro_unरेजिस्टर_driver);


    /**
     *  zorro_bus_match - Tell अगर a Zorro device काष्ठाure has a matching Zorro
     *                    device id काष्ठाure
     *  @ids: array of Zorro device id काष्ठाures to search in
     *  @dev: the Zorro device काष्ठाure to match against
     *
     *  Used by the driver core to check whether a Zorro device present in the
     *  प्रणाली is in a driver's list of supported devices.  Returns 1 अगर
     *  supported, and 0 अगर there is no match.
     */

अटल पूर्णांक zorro_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा zorro_dev *z = to_zorro_dev(dev);
	काष्ठा zorro_driver *zorro_drv = to_zorro_driver(drv);
	स्थिर काष्ठा zorro_device_id *ids = zorro_drv->id_table;

	अगर (!ids)
		वापस 0;

	वापस !!zorro_match_device(ids, z);
पूर्ण

अटल पूर्णांक zorro_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा zorro_dev *z;

	अगर (!dev)
		वापस -ENODEV;

	z = to_zorro_dev(dev);
	अगर (!z)
		वापस -ENODEV;

	अगर (add_uevent_var(env, "ZORRO_ID=%08X", z->id) ||
	    add_uevent_var(env, "ZORRO_SLOT_NAME=%s", dev_name(dev)) ||
	    add_uevent_var(env, "ZORRO_SLOT_ADDR=%04X", z->slotaddr) ||
	    add_uevent_var(env, "MODALIAS=" ZORRO_DEVICE_MODALIAS_FMT, z->id))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा bus_type zorro_bus_type = अणु
	.name		= "zorro",
	.dev_name	= "zorro",
	.dev_groups	= zorro_device_attribute_groups,
	.match		= zorro_bus_match,
	.uevent		= zorro_uevent,
	.probe		= zorro_device_probe,
	.हटाओ		= zorro_device_हटाओ,
पूर्ण;
EXPORT_SYMBOL(zorro_bus_type);


अटल पूर्णांक __init zorro_driver_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&zorro_bus_type);
पूर्ण

postcore_initcall(zorro_driver_init);

