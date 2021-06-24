<शैली गुरु>
/*
 *	TURBOchannel driver services.
 *
 *	Copyright (c) 2005  James Simmons
 *	Copyright (c) 2006  Maciej W. Rozycki
 *
 *	Loosely based on drivers/dio/dio-driver.c and
 *	drivers/pci/pci-driver.c.
 *
 *	This file is subject to the terms and conditions of the GNU
 *	General Public License.  See the file "COPYING" in the मुख्य
 *	directory of this archive क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/tc.h>

/**
 * tc_रेजिस्टर_driver - रेजिस्टर a new TC driver
 * @drv: the driver काष्ठाure to रेजिस्टर
 *
 * Adds the driver काष्ठाure to the list of रेजिस्टरed drivers
 * Returns a negative value on error, otherwise 0.
 * If no error occurred, the driver reमुख्यs रेजिस्टरed even अगर
 * no device was claimed during registration.
 */
पूर्णांक tc_रेजिस्टर_driver(काष्ठा tc_driver *tdrv)
अणु
	वापस driver_रेजिस्टर(&tdrv->driver);
पूर्ण
EXPORT_SYMBOL(tc_रेजिस्टर_driver);

/**
 * tc_unरेजिस्टर_driver - unरेजिस्टर a TC driver
 * @drv: the driver काष्ठाure to unरेजिस्टर
 *
 * Deletes the driver काष्ठाure from the list of रेजिस्टरed TC drivers,
 * gives it a chance to clean up by calling its हटाओ() function क्रम
 * each device it was responsible क्रम, and marks those devices as
 * driverless.
 */
व्योम tc_unरेजिस्टर_driver(काष्ठा tc_driver *tdrv)
अणु
	driver_unरेजिस्टर(&tdrv->driver);
पूर्ण
EXPORT_SYMBOL(tc_unरेजिस्टर_driver);

/**
 * tc_match_device - tell अगर a TC device काष्ठाure has a matching
 *                   TC device ID काष्ठाure
 * @tdrv: the TC driver to earch क्रम matching TC device ID strings
 * @tdev: the TC device काष्ठाure to match against
 *
 * Used by a driver to check whether a TC device present in the
 * प्रणाली is in its list of supported devices.  Returns the matching
 * tc_device_id काष्ठाure or %शून्य अगर there is no match.
 */
अटल स्थिर काष्ठा tc_device_id *tc_match_device(काष्ठा tc_driver *tdrv,
						  काष्ठा tc_dev *tdev)
अणु
	स्थिर काष्ठा tc_device_id *id = tdrv->id_table;

	अगर (id) अणु
		जबतक (id->name[0] || id->venकरोr[0]) अणु
			अगर (म_भेद(tdev->name, id->name) == 0 &&
			    म_भेद(tdev->venकरोr, id->venकरोr) == 0)
				वापस id;
			id++;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * tc_bus_match - Tell अगर a device काष्ठाure has a matching
 *                TC device ID काष्ठाure
 * @dev: the device काष्ठाure to match against
 * @drv: the device driver to search क्रम matching TC device ID strings
 *
 * Used by a driver to check whether a TC device present in the
 * प्रणाली is in its list of supported devices.  Returns 1 अगर there
 * is a match or 0 otherwise.
 */
अटल पूर्णांक tc_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा tc_dev *tdev = to_tc_dev(dev);
	काष्ठा tc_driver *tdrv = to_tc_driver(drv);
	स्थिर काष्ठा tc_device_id *id;

	id = tc_match_device(tdrv, tdev);
	अगर (id)
		वापस 1;

	वापस 0;
पूर्ण

काष्ठा bus_type tc_bus_type = अणु
	.name	= "tc",
	.match	= tc_bus_match,
पूर्ण;
EXPORT_SYMBOL(tc_bus_type);

अटल पूर्णांक __init tc_driver_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&tc_bus_type);
पूर्ण

postcore_initcall(tc_driver_init);
