<शैली गुरु>
/*
 *  DIO Driver Services
 *
 *  Copyright (C) 2004 Jochen Friedrich
 *
 *  Loosely based on drivers/pci/pci-driver.c and drivers/zorro/zorro-driver.c
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/dपन.स>


/**
 *  dio_match_device - Tell अगर a DIO device काष्ठाure has a matching DIO device id काष्ठाure
 *  @ids: array of DIO device id काष्ठाures to search in
 *  @d: the DIO device काष्ठाure to match against
 *
 *  Used by a driver to check whether a DIO device present in the
 *  प्रणाली is in its list of supported devices. Returns the matching
 *  dio_device_id काष्ठाure or %शून्य अगर there is no match.
 */

अटल स्थिर काष्ठा dio_device_id *
dio_match_device(स्थिर काष्ठा dio_device_id *ids,
		   स्थिर काष्ठा dio_dev *d)
अणु
	जबतक (ids->id) अणु
		अगर (ids->id == DIO_WILDCARD)
			वापस ids;
		अगर (DIO_NEEDSSECID(ids->id & 0xff)) अणु
			अगर (ids->id == d->id)
				वापस ids;
		पूर्ण अन्यथा अणु
			अगर ((ids->id & 0xff) == (d->id & 0xff))
				वापस ids;
		पूर्ण
		ids++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक dio_device_probe(काष्ठा device *dev)
अणु
	पूर्णांक error = 0;
	काष्ठा dio_driver *drv = to_dio_driver(dev->driver);
	काष्ठा dio_dev *d = to_dio_dev(dev);

	अगर (!d->driver && drv->probe) अणु
		स्थिर काष्ठा dio_device_id *id;

		id = dio_match_device(drv->id_table, d);
		अगर (id)
			error = drv->probe(d, id);
		अगर (error >= 0) अणु
			d->driver = drv;
			error = 0;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण


/**
 *  dio_रेजिस्टर_driver - रेजिस्टर a new DIO driver
 *  @drv: the driver काष्ठाure to रेजिस्टर
 *
 *  Adds the driver काष्ठाure to the list of रेजिस्टरed drivers
 *  Returns zero or a negative error value.
 */

पूर्णांक dio_रेजिस्टर_driver(काष्ठा dio_driver *drv)
अणु
	/* initialize common driver fields */
	drv->driver.name = drv->name;
	drv->driver.bus = &dio_bus_type;

	/* रेजिस्टर with core */
	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण


/**
 *  dio_unरेजिस्टर_driver - unरेजिस्टर a DIO driver
 *  @drv: the driver काष्ठाure to unरेजिस्टर
 *
 *  Deletes the driver काष्ठाure from the list of रेजिस्टरed DIO drivers,
 *  gives it a chance to clean up by calling its हटाओ() function क्रम
 *  each device it was responsible क्रम, and marks those devices as
 *  driverless.
 */

व्योम dio_unरेजिस्टर_driver(काष्ठा dio_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण


/**
 *  dio_bus_match - Tell अगर a DIO device काष्ठाure has a matching DIO device id काष्ठाure
 *  @dev: the DIO device काष्ठाure to match against
 *  @drv: the &device_driver that poपूर्णांकs to the array of DIO device id काष्ठाures to search
 *
 *  Used by the driver core to check whether a DIO device present in the
 *  प्रणाली is in a driver's list of supported devices. Returns 1 अगर supported,
 *  and 0 अगर there is no match.
 */

अटल पूर्णांक dio_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा dio_dev *d = to_dio_dev(dev);
	काष्ठा dio_driver *dio_drv = to_dio_driver(drv);
	स्थिर काष्ठा dio_device_id *ids = dio_drv->id_table;

	अगर (!ids)
		वापस 0;

	वापस dio_match_device(ids, d) ? 1 : 0;
पूर्ण


काष्ठा bus_type dio_bus_type = अणु
	.name	= "dio",
	.match	= dio_bus_match,
	.probe	= dio_device_probe,
पूर्ण;


अटल पूर्णांक __init dio_driver_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&dio_bus_type);
पूर्ण

postcore_initcall(dio_driver_init);

EXPORT_SYMBOL(dio_रेजिस्टर_driver);
EXPORT_SYMBOL(dio_unरेजिस्टर_driver);
EXPORT_SYMBOL(dio_bus_type);
