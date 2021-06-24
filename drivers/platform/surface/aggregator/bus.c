<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface System Aggregator Module bus and device पूर्णांकegration.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/device.h>

#समावेश "bus.h"
#समावेश "controller.h"

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ssam_device *sdev = to_ssam_device(dev);

	वापस sysfs_emit(buf, "ssam:d%02Xc%02Xt%02Xi%02Xf%02X\n",
			sdev->uid.करोमुख्य, sdev->uid.category, sdev->uid.target,
			sdev->uid.instance, sdev->uid.function);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *ssam_device_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(ssam_device);

अटल पूर्णांक ssam_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा ssam_device *sdev = to_ssam_device(dev);

	वापस add_uevent_var(env, "MODALIAS=ssam:d%02Xc%02Xt%02Xi%02Xf%02X",
			      sdev->uid.करोमुख्य, sdev->uid.category,
			      sdev->uid.target, sdev->uid.instance,
			      sdev->uid.function);
पूर्ण

अटल व्योम ssam_device_release(काष्ठा device *dev)
अणु
	काष्ठा ssam_device *sdev = to_ssam_device(dev);

	ssam_controller_put(sdev->ctrl);
	kमुक्त(sdev);
पूर्ण

स्थिर काष्ठा device_type ssam_device_type = अणु
	.name    = "surface_aggregator_device",
	.groups  = ssam_device_groups,
	.uevent  = ssam_device_uevent,
	.release = ssam_device_release,
पूर्ण;
EXPORT_SYMBOL_GPL(ssam_device_type);

/**
 * ssam_device_alloc() - Allocate and initialize a SSAM client device.
 * @ctrl: The controller under which the device should be added.
 * @uid:  The UID of the device to be added.
 *
 * Allocates and initializes a new client device. The parent of the device
 * will be set to the controller device and the name will be set based on the
 * UID. Note that the device still has to be added via ssam_device_add().
 * Refer to that function क्रम more details.
 *
 * Return: Returns the newly allocated and initialized SSAM client device, or
 * %शून्य अगर it could not be allocated.
 */
काष्ठा ssam_device *ssam_device_alloc(काष्ठा ssam_controller *ctrl,
				      काष्ठा ssam_device_uid uid)
अणु
	काष्ठा ssam_device *sdev;

	sdev = kzalloc(माप(*sdev), GFP_KERNEL);
	अगर (!sdev)
		वापस शून्य;

	device_initialize(&sdev->dev);
	sdev->dev.bus = &ssam_bus_type;
	sdev->dev.type = &ssam_device_type;
	sdev->dev.parent = ssam_controller_device(ctrl);
	sdev->ctrl = ssam_controller_get(ctrl);
	sdev->uid = uid;

	dev_set_name(&sdev->dev, "%02x:%02x:%02x:%02x:%02x",
		     sdev->uid.करोमुख्य, sdev->uid.category, sdev->uid.target,
		     sdev->uid.instance, sdev->uid.function);

	वापस sdev;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_device_alloc);

/**
 * ssam_device_add() - Add a SSAM client device.
 * @sdev: The SSAM client device to be added.
 *
 * Added client devices must be guaranteed to always have a valid and active
 * controller. Thus, this function will fail with %-ENODEV अगर the controller
 * of the device has not been initialized yet, has been suspended, or has been
 * shut करोwn.
 *
 * The caller of this function should ensure that the corresponding call to
 * ssam_device_हटाओ() is issued beक्रमe the controller is shut करोwn. If the
 * added device is a direct child of the controller device (शेष), it will
 * be स्वतःmatically हटाओd when the controller is shut करोwn.
 *
 * By शेष, the controller device will become the parent of the newly
 * created client device. The parent may be changed beक्रमe ssam_device_add is
 * called, but care must be taken that a) the correct suspend/resume ordering
 * is guaranteed and b) the client device करोes not outlive the controller,
 * i.e. that the device is हटाओd beक्रमe the controller is being shut करोwn.
 * In हाल these guarantees have to be manually enक्रमced, please refer to the
 * ssam_client_link() and ssam_client_bind() functions, which are पूर्णांकended to
 * set up device-links क्रम this purpose.
 *
 * Return: Returns zero on success, a negative error code on failure.
 */
पूर्णांक ssam_device_add(काष्ठा ssam_device *sdev)
अणु
	पूर्णांक status;

	/*
	 * Ensure that we can only add new devices to a controller अगर it has
	 * been started and is not going away soon. This works in combination
	 * with ssam_controller_हटाओ_clients to ensure driver presence क्रम the
	 * controller device, i.e. it ensures that the controller (sdev->ctrl)
	 * is always valid and can be used क्रम requests as दीर्घ as the client
	 * device we add here is रेजिस्टरed as child under it. This essentially
	 * guarantees that the client driver can always expect the preconditions
	 * क्रम functions like ssam_request_sync (controller has to be started
	 * and is not suspended) to hold and thus करोes not have to check क्रम
	 * them.
	 *
	 * Note that क्रम this to work, the controller has to be a parent device.
	 * If it is not a direct parent, care has to be taken that the device is
	 * हटाओd via ssam_device_हटाओ(), as device_unरेजिस्टर करोes not
	 * हटाओ child devices recursively.
	 */
	ssam_controller_statelock(sdev->ctrl);

	अगर (sdev->ctrl->state != SSAM_CONTROLLER_STARTED) अणु
		ssam_controller_stateunlock(sdev->ctrl);
		वापस -ENODEV;
	पूर्ण

	status = device_add(&sdev->dev);

	ssam_controller_stateunlock(sdev->ctrl);
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_device_add);

/**
 * ssam_device_हटाओ() - Remove a SSAM client device.
 * @sdev: The device to हटाओ.
 *
 * Removes and unरेजिस्टरs the provided SSAM client device.
 */
व्योम ssam_device_हटाओ(काष्ठा ssam_device *sdev)
अणु
	device_unरेजिस्टर(&sdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_device_हटाओ);

/**
 * ssam_device_id_compatible() - Check अगर a device ID matches a UID.
 * @id:  The device ID as potential match.
 * @uid: The device UID matching against.
 *
 * Check अगर the given ID is a match क्रम the given UID, i.e. अगर a device with
 * the provided UID is compatible to the given ID following the match rules
 * described in its &ssam_device_id.match_flags member.
 *
 * Return: Returns %true अगर the given UID is compatible to the match rule
 * described by the given ID, %false otherwise.
 */
अटल bool ssam_device_id_compatible(स्थिर काष्ठा ssam_device_id *id,
				      काष्ठा ssam_device_uid uid)
अणु
	अगर (id->करोमुख्य != uid.करोमुख्य || id->category != uid.category)
		वापस false;

	अगर ((id->match_flags & SSAM_MATCH_TARGET) && id->target != uid.target)
		वापस false;

	अगर ((id->match_flags & SSAM_MATCH_INSTANCE) && id->instance != uid.instance)
		वापस false;

	अगर ((id->match_flags & SSAM_MATCH_FUNCTION) && id->function != uid.function)
		वापस false;

	वापस true;
पूर्ण

/**
 * ssam_device_id_is_null() - Check अगर a device ID is null.
 * @id: The device ID to check.
 *
 * Check अगर a given device ID is null, i.e. all zeros. Used to check क्रम the
 * end of ``MODULE_DEVICE_TABLE(ssam, ...)`` or similar lists.
 *
 * Return: Returns %true अगर the given ID represents a null ID, %false
 * otherwise.
 */
अटल bool ssam_device_id_is_null(स्थिर काष्ठा ssam_device_id *id)
अणु
	वापस id->match_flags == 0 &&
		id->करोमुख्य == 0 &&
		id->category == 0 &&
		id->target == 0 &&
		id->instance == 0 &&
		id->function == 0 &&
		id->driver_data == 0;
पूर्ण

/**
 * ssam_device_id_match() - Find the matching ID table entry क्रम the given UID.
 * @table: The table to search in.
 * @uid:   The UID to matched against the inभागidual table entries.
 *
 * Find the first match क्रम the provided device UID in the provided ID table
 * and वापस it. Returns %शून्य अगर no match could be found.
 */
स्थिर काष्ठा ssam_device_id *ssam_device_id_match(स्थिर काष्ठा ssam_device_id *table,
						  स्थिर काष्ठा ssam_device_uid uid)
अणु
	स्थिर काष्ठा ssam_device_id *id;

	क्रम (id = table; !ssam_device_id_is_null(id); ++id)
		अगर (ssam_device_id_compatible(id, uid))
			वापस id;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_device_id_match);

/**
 * ssam_device_get_match() - Find and वापस the ID matching the device in the
 * ID table of the bound driver.
 * @dev: The device क्रम which to get the matching ID table entry.
 *
 * Find the fist match क्रम the UID of the device in the ID table of the
 * currently bound driver and वापस it. Returns %शून्य अगर the device करोes not
 * have a driver bound to it, the driver करोes not have match_table (i.e. it is
 * %शून्य), or there is no match in the driver's match_table.
 *
 * This function essentially calls ssam_device_id_match() with the ID table of
 * the bound device driver and the UID of the device.
 *
 * Return: Returns the first match क्रम the UID of the device in the device
 * driver's match table, or %शून्य अगर no such match could be found.
 */
स्थिर काष्ठा ssam_device_id *ssam_device_get_match(स्थिर काष्ठा ssam_device *dev)
अणु
	स्थिर काष्ठा ssam_device_driver *sdrv;

	sdrv = to_ssam_device_driver(dev->dev.driver);
	अगर (!sdrv)
		वापस शून्य;

	अगर (!sdrv->match_table)
		वापस शून्य;

	वापस ssam_device_id_match(sdrv->match_table, dev->uid);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_device_get_match);

/**
 * ssam_device_get_match_data() - Find the ID matching the device in the
 * ID table of the bound driver and वापस its ``driver_data`` member.
 * @dev: The device क्रम which to get the match data.
 *
 * Find the fist match क्रम the UID of the device in the ID table of the
 * corresponding driver and वापस its driver_data. Returns %शून्य अगर the
 * device करोes not have a driver bound to it, the driver करोes not have
 * match_table (i.e. it is %शून्य), there is no match in the driver's
 * match_table, or the match करोes not have any driver_data.
 *
 * This function essentially calls ssam_device_get_match() and, अगर any match
 * could be found, वापसs its ``काष्ठा ssam_device_id.driver_data`` member.
 *
 * Return: Returns the driver data associated with the first match क्रम the UID
 * of the device in the device driver's match table, or %शून्य अगर no such match
 * could be found.
 */
स्थिर व्योम *ssam_device_get_match_data(स्थिर काष्ठा ssam_device *dev)
अणु
	स्थिर काष्ठा ssam_device_id *id;

	id = ssam_device_get_match(dev);
	अगर (!id)
		वापस शून्य;

	वापस (स्थिर व्योम *)id->driver_data;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_device_get_match_data);

अटल पूर्णांक ssam_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा ssam_device_driver *sdrv = to_ssam_device_driver(drv);
	काष्ठा ssam_device *sdev = to_ssam_device(dev);

	अगर (!is_ssam_device(dev))
		वापस 0;

	वापस !!ssam_device_id_match(sdrv->match_table, sdev->uid);
पूर्ण

अटल पूर्णांक ssam_bus_probe(काष्ठा device *dev)
अणु
	वापस to_ssam_device_driver(dev->driver)
		->probe(to_ssam_device(dev));
पूर्ण

अटल पूर्णांक ssam_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ssam_device_driver *sdrv = to_ssam_device_driver(dev->driver);

	अगर (sdrv->हटाओ)
		sdrv->हटाओ(to_ssam_device(dev));

	वापस 0;
पूर्ण

काष्ठा bus_type ssam_bus_type = अणु
	.name   = "surface_aggregator",
	.match  = ssam_bus_match,
	.probe  = ssam_bus_probe,
	.हटाओ = ssam_bus_हटाओ,
पूर्ण;
EXPORT_SYMBOL_GPL(ssam_bus_type);

/**
 * __ssam_device_driver_रेजिस्टर() - Register a SSAM client device driver.
 * @sdrv:  The driver to रेजिस्टर.
 * @owner: The module owning the provided driver.
 *
 * Please refer to the ssam_device_driver_रेजिस्टर() macro क्रम the normal way
 * to रेजिस्टर a driver from inside its owning module.
 */
पूर्णांक __ssam_device_driver_रेजिस्टर(काष्ठा ssam_device_driver *sdrv,
				  काष्ठा module *owner)
अणु
	sdrv->driver.owner = owner;
	sdrv->driver.bus = &ssam_bus_type;

	/* क्रमce drivers to async probe so I/O is possible in probe */
	sdrv->driver.probe_type = PROBE_PREFER_ASYNCHRONOUS;

	वापस driver_रेजिस्टर(&sdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__ssam_device_driver_रेजिस्टर);

/**
 * ssam_device_driver_unरेजिस्टर - Unरेजिस्टर a SSAM device driver.
 * @sdrv: The driver to unरेजिस्टर.
 */
व्योम ssam_device_driver_unरेजिस्टर(काष्ठा ssam_device_driver *sdrv)
अणु
	driver_unरेजिस्टर(&sdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_device_driver_unरेजिस्टर);

अटल पूर्णांक ssam_हटाओ_device(काष्ठा device *dev, व्योम *_data)
अणु
	काष्ठा ssam_device *sdev = to_ssam_device(dev);

	अगर (is_ssam_device(dev))
		ssam_device_हटाओ(sdev);

	वापस 0;
पूर्ण

/**
 * ssam_controller_हटाओ_clients() - Remove SSAM client devices रेजिस्टरed as
 * direct children under the given controller.
 * @ctrl: The controller to हटाओ all direct clients क्रम.
 *
 * Remove all SSAM client devices रेजिस्टरed as direct children under the
 * given controller. Note that this only accounts क्रम direct children of the
 * controller device. This करोes not take care of any client devices where the
 * parent device has been manually set beक्रमe calling ssam_device_add. Refer
 * to ssam_device_add()/ssam_device_हटाओ() क्रम more details on those हालs.
 *
 * To aव्योम new devices being added in parallel to this call, the मुख्य
 * controller lock (not statelock) must be held during this (and अगर
 * necessary, any subsequent deinitialization) call.
 */
व्योम ssam_controller_हटाओ_clients(काष्ठा ssam_controller *ctrl)
अणु
	काष्ठा device *dev;

	dev = ssam_controller_device(ctrl);
	device_क्रम_each_child_reverse(dev, शून्य, ssam_हटाओ_device);
पूर्ण

/**
 * ssam_bus_रेजिस्टर() - Register and set-up the SSAM client device bus.
 */
पूर्णांक ssam_bus_रेजिस्टर(व्योम)
अणु
	वापस bus_रेजिस्टर(&ssam_bus_type);
पूर्ण

/**
 * ssam_bus_unरेजिस्टर() - Unरेजिस्टर the SSAM client device bus.
 */
व्योम ssam_bus_unरेजिस्टर(व्योम)
अणु
	वापस bus_unरेजिस्टर(&ssam_bus_type);
पूर्ण
