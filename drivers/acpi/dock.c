<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  करोck.c - ACPI करोck station driver
 *
 *  Copyright (C) 2006, 2014, Intel Corp.
 *  Author: Kristen Carlson Accardi <kristen.c.accardi@पूर्णांकel.com>
 *          Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/acpi.h>

#समावेश "internal.h"

अटल bool immediate_unकरोck = 1;
module_param(immediate_unकरोck, bool, 0644);
MODULE_PARM_DESC(immediate_unकरोck, "1 (default) will cause the driver to "
	"undock immediately when the undock button is pressed, 0 will cause"
	" the driver to wait for userspace to write the undock sysfs file "
	" before undocking");

काष्ठा करोck_station अणु
	acpi_handle handle;
	अचिन्हित दीर्घ last_करोck_समय;
	u32 flags;
	काष्ठा list_head dependent_devices;

	काष्ठा list_head sibling;
	काष्ठा platक्रमm_device *करोck_device;
पूर्ण;
अटल LIST_HEAD(करोck_stations);
अटल पूर्णांक करोck_station_count;

काष्ठा करोck_dependent_device अणु
	काष्ठा list_head list;
	काष्ठा acpi_device *adev;
पूर्ण;

#घोषणा DOCK_DOCKING	0x00000001
#घोषणा DOCK_UNDOCKING  0x00000002
#घोषणा DOCK_IS_DOCK	0x00000010
#घोषणा DOCK_IS_ATA	0x00000020
#घोषणा DOCK_IS_BAT	0x00000040
#घोषणा DOCK_EVENT	3
#घोषणा UNDOCK_EVENT	2

क्रमागत करोck_callback_type अणु
	DOCK_CALL_HANDLER,
	DOCK_CALL_FIXUP,
	DOCK_CALL_UEVENT,
पूर्ण;

/*****************************************************************************
 *                         Dock Dependent device functions                   *
 *****************************************************************************/
/**
 * add_करोck_dependent_device - associate a device with the करोck station
 * @ds: Dock station.
 * @adev: Dependent ACPI device object.
 *
 * Add the dependent device to the करोck's dependent device list.
 */
अटल पूर्णांक add_करोck_dependent_device(काष्ठा करोck_station *ds,
				     काष्ठा acpi_device *adev)
अणु
	काष्ठा करोck_dependent_device *dd;

	dd = kzalloc(माप(*dd), GFP_KERNEL);
	अगर (!dd)
		वापस -ENOMEM;

	dd->adev = adev;
	INIT_LIST_HEAD(&dd->list);
	list_add_tail(&dd->list, &ds->dependent_devices);

	वापस 0;
पूर्ण

अटल व्योम करोck_hotplug_event(काष्ठा करोck_dependent_device *dd, u32 event,
			       क्रमागत करोck_callback_type cb_type)
अणु
	काष्ठा acpi_device *adev = dd->adev;

	acpi_lock_hp_context();

	अगर (!adev->hp)
		जाओ out;

	अगर (cb_type == DOCK_CALL_FIXUP) अणु
		व्योम (*fixup)(काष्ठा acpi_device *);

		fixup = adev->hp->fixup;
		अगर (fixup) अणु
			acpi_unlock_hp_context();
			fixup(adev);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (cb_type == DOCK_CALL_UEVENT) अणु
		व्योम (*uevent)(काष्ठा acpi_device *, u32);

		uevent = adev->hp->uevent;
		अगर (uevent) अणु
			acpi_unlock_hp_context();
			uevent(adev, event);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक (*notअगरy)(काष्ठा acpi_device *, u32);

		notअगरy = adev->hp->notअगरy;
		अगर (notअगरy) अणु
			acpi_unlock_hp_context();
			notअगरy(adev, event);
			वापस;
		पूर्ण
	पूर्ण

 out:
	acpi_unlock_hp_context();
पूर्ण

अटल काष्ठा करोck_station *find_करोck_station(acpi_handle handle)
अणु
	काष्ठा करोck_station *ds;

	list_क्रम_each_entry(ds, &करोck_stations, sibling)
		अगर (ds->handle == handle)
			वापस ds;

	वापस शून्य;
पूर्ण

/**
 * find_करोck_dependent_device - get a device dependent on this करोck
 * @ds: the करोck station
 * @adev: ACPI device object to find.
 *
 * iterate over the dependent device list क्रम this करोck.  If the
 * dependent device matches the handle, वापस.
 */
अटल काष्ठा करोck_dependent_device *
find_करोck_dependent_device(काष्ठा करोck_station *ds, काष्ठा acpi_device *adev)
अणु
	काष्ठा करोck_dependent_device *dd;

	list_क्रम_each_entry(dd, &ds->dependent_devices, list)
		अगर (adev == dd->adev)
			वापस dd;

	वापस शून्य;
पूर्ण

व्योम रेजिस्टर_करोck_dependent_device(काष्ठा acpi_device *adev,
				    acpi_handle dshandle)
अणु
	काष्ठा करोck_station *ds = find_करोck_station(dshandle);

	अगर (ds && !find_करोck_dependent_device(ds, adev))
		add_करोck_dependent_device(ds, adev);
पूर्ण

/*****************************************************************************
 *                         Dock functions                                    *
 *****************************************************************************/

/**
 * is_करोck_device - see अगर a device is on a करोck station
 * @adev: ACPI device object to check.
 *
 * If this device is either the करोck station itself,
 * or is a device dependent on the करोck station, then it
 * is a करोck device
 */
पूर्णांक is_करोck_device(काष्ठा acpi_device *adev)
अणु
	काष्ठा करोck_station *करोck_station;

	अगर (!करोck_station_count)
		वापस 0;

	अगर (acpi_करोck_match(adev->handle))
		वापस 1;

	list_क्रम_each_entry(करोck_station, &करोck_stations, sibling)
		अगर (find_करोck_dependent_device(करोck_station, adev))
			वापस 1;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(is_करोck_device);

/**
 * करोck_present - see अगर the करोck station is present.
 * @ds: the करोck station
 *
 * execute the _STA method.  note that present करोes not
 * imply that we are करोcked.
 */
अटल पूर्णांक करोck_present(काष्ठा करोck_station *ds)
अणु
	अचिन्हित दीर्घ दीर्घ sta;
	acpi_status status;

	अगर (ds) अणु
		status = acpi_evaluate_पूर्णांकeger(ds->handle, "_STA", शून्य, &sta);
		अगर (ACPI_SUCCESS(status) && sta)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * hot_हटाओ_करोck_devices - Remove करोck station devices.
 * @ds: Dock station.
 */
अटल व्योम hot_हटाओ_करोck_devices(काष्ठा करोck_station *ds)
अणु
	काष्ठा करोck_dependent_device *dd;

	/*
	 * Walk the list in reverse order so that devices that have been added
	 * last are हटाओd first (in हाल there are some indirect dependencies
	 * between them).
	 */
	list_क्रम_each_entry_reverse(dd, &ds->dependent_devices, list)
		करोck_hotplug_event(dd, ACPI_NOTIFY_EJECT_REQUEST,
				   DOCK_CALL_HANDLER);

	list_क्रम_each_entry_reverse(dd, &ds->dependent_devices, list)
		acpi_bus_trim(dd->adev);
पूर्ण

/**
 * hotplug_करोck_devices - Insert devices on a करोck station.
 * @ds: the करोck station
 * @event: either bus check or device check request
 *
 * Some devices on the करोck station need to have drivers called
 * to perक्रमm hotplug operations after a करोck event has occurred.
 * Traverse the list of करोck devices that have रेजिस्टरed a
 * hotplug handler, and call the handler.
 */
अटल व्योम hotplug_करोck_devices(काष्ठा करोck_station *ds, u32 event)
अणु
	काष्ठा करोck_dependent_device *dd;

	/* Call driver specअगरic post-करोck fixups. */
	list_क्रम_each_entry(dd, &ds->dependent_devices, list)
		करोck_hotplug_event(dd, event, DOCK_CALL_FIXUP);

	/* Call driver specअगरic hotplug functions. */
	list_क्रम_each_entry(dd, &ds->dependent_devices, list)
		करोck_hotplug_event(dd, event, DOCK_CALL_HANDLER);

	/*
	 * Check अगर all devices have been क्रमागतerated alपढ़ोy.  If not, run
	 * acpi_bus_scan() क्रम them and that will cause scan handlers to be
	 * attached to device objects or acpi_drivers to be stopped/started अगर
	 * they are present.
	 */
	list_क्रम_each_entry(dd, &ds->dependent_devices, list) अणु
		काष्ठा acpi_device *adev = dd->adev;

		अगर (!acpi_device_क्रमागतerated(adev)) अणु
			पूर्णांक ret = acpi_bus_scan(adev->handle);

			अगर (ret)
				dev_dbg(&adev->dev, "scan error %d\n", -ret);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम करोck_event(काष्ठा करोck_station *ds, u32 event, पूर्णांक num)
अणु
	काष्ठा device *dev = &ds->करोck_device->dev;
	अक्षर event_string[13];
	अक्षर *envp[] = अणु event_string, शून्य पूर्ण;
	काष्ठा करोck_dependent_device *dd;

	अगर (num == UNDOCK_EVENT)
		प्र_लिखो(event_string, "EVENT=undock");
	अन्यथा
		प्र_लिखो(event_string, "EVENT=dock");

	/*
	 * Indicate that the status of the करोck station has
	 * changed.
	 */
	अगर (num == DOCK_EVENT)
		kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);

	list_क्रम_each_entry(dd, &ds->dependent_devices, list)
		करोck_hotplug_event(dd, event, DOCK_CALL_UEVENT);

	अगर (num != DOCK_EVENT)
		kobject_uevent_env(&dev->kobj, KOBJ_CHANGE, envp);
पूर्ण

/**
 * handle_करोck - handle a करोck event
 * @ds: the करोck station
 * @करोck: to करोck, or unकरोck - that is the question
 *
 * Execute the _DCK method in response to an acpi event
 */
अटल व्योम handle_करोck(काष्ठा करोck_station *ds, पूर्णांक करोck)
अणु
	acpi_status status;
	काष्ठा acpi_object_list arg_list;
	जोड़ acpi_object arg;
	अचिन्हित दीर्घ दीर्घ value;

	acpi_handle_info(ds->handle, "%s\n", करोck ? "docking" : "undocking");

	/* _DCK method has one argument */
	arg_list.count = 1;
	arg_list.poपूर्णांकer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.पूर्णांकeger.value = करोck;
	status = acpi_evaluate_पूर्णांकeger(ds->handle, "_DCK", &arg_list, &value);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND)
		acpi_handle_err(ds->handle, "Failed to execute _DCK (0x%x)\n",
				status);
पूर्ण

अटल अंतरभूत व्योम करोck(काष्ठा करोck_station *ds)
अणु
	handle_करोck(ds, 1);
पूर्ण

अटल अंतरभूत व्योम unकरोck(काष्ठा करोck_station *ds)
अणु
	handle_करोck(ds, 0);
पूर्ण

अटल अंतरभूत व्योम begin_करोck(काष्ठा करोck_station *ds)
अणु
	ds->flags |= DOCK_DOCKING;
पूर्ण

अटल अंतरभूत व्योम complete_करोck(काष्ठा करोck_station *ds)
अणु
	ds->flags &= ~(DOCK_DOCKING);
	ds->last_करोck_समय = jअगरfies;
पूर्ण

अटल अंतरभूत व्योम begin_unकरोck(काष्ठा करोck_station *ds)
अणु
	ds->flags |= DOCK_UNDOCKING;
पूर्ण

अटल अंतरभूत व्योम complete_unकरोck(काष्ठा करोck_station *ds)
अणु
	ds->flags &= ~(DOCK_UNDOCKING);
पूर्ण

/**
 * करोck_in_progress - see अगर we are in the middle of handling a करोck event
 * @ds: the करोck station
 *
 * Someबार जबतक करोcking, false करोck events can be sent to the driver
 * because good connections aren't made or some other reason.  Ignore these
 * अगर we are in the middle of करोing something.
 */
अटल पूर्णांक करोck_in_progress(काष्ठा करोck_station *ds)
अणु
	अगर ((ds->flags & DOCK_DOCKING) ||
	    समय_beक्रमe(jअगरfies, (ds->last_करोck_समय + HZ)))
		वापस 1;
	वापस 0;
पूर्ण

/**
 * handle_eject_request - handle an unकरोck request checking क्रम error conditions
 *
 * Check to make sure the करोck device is still present, then unकरोck and
 * hotहटाओ all the devices that may need removing.
 */
अटल पूर्णांक handle_eject_request(काष्ठा करोck_station *ds, u32 event)
अणु
	अगर (करोck_in_progress(ds))
		वापस -EBUSY;

	/*
	 * here we need to generate the unकरोck
	 * event prior to actually करोing the unकरोck
	 * so that the device काष्ठा still exists.
	 * Also, even send the करोck event अगर the
	 * device is not present anymore
	 */
	करोck_event(ds, event, UNDOCK_EVENT);

	hot_हटाओ_करोck_devices(ds);
	unकरोck(ds);
	acpi_evaluate_lck(ds->handle, 0);
	acpi_evaluate_ej0(ds->handle);
	अगर (करोck_present(ds)) अणु
		acpi_handle_err(ds->handle, "Unable to undock!\n");
		वापस -EBUSY;
	पूर्ण
	complete_unकरोck(ds);
	वापस 0;
पूर्ण

/**
 * करोck_notअगरy - Handle ACPI करोck notअगरication.
 * @adev: Dock station's ACPI device object.
 * @event: Event code.
 *
 * If we are notअगरied to करोck, then check to see अगर the करोck is
 * present and then करोck.  Notअगरy all drivers of the करोck event,
 * and then hotplug and devices that may need hotplugging.
 */
पूर्णांक करोck_notअगरy(काष्ठा acpi_device *adev, u32 event)
अणु
	acpi_handle handle = adev->handle;
	काष्ठा करोck_station *ds = find_करोck_station(handle);
	पूर्णांक surprise_removal = 0;

	अगर (!ds)
		वापस -ENODEV;

	/*
	 * According to acpi spec 3.0a, अगर a DEVICE_CHECK notअगरication
	 * is sent and _DCK is present, it is assumed to mean an unकरोck
	 * request.
	 */
	अगर ((ds->flags & DOCK_IS_DOCK) && event == ACPI_NOTIFY_DEVICE_CHECK)
		event = ACPI_NOTIFY_EJECT_REQUEST;

	/*
	 * करोck station: BUS_CHECK - करोcked or surprise removal
	 *		 DEVICE_CHECK - unकरोcked
	 * other device: BUS_CHECK/DEVICE_CHECK - added or surprise removal
	 *
	 * To simplअगरy event handling, करोck dependent device handler always
	 * get ACPI_NOTIFY_BUS_CHECK/ACPI_NOTIFY_DEVICE_CHECK क्रम add and
	 * ACPI_NOTIFY_EJECT_REQUEST क्रम removal
	 */
	चयन (event) अणु
	हाल ACPI_NOTIFY_BUS_CHECK:
	हाल ACPI_NOTIFY_DEVICE_CHECK:
		अगर (!करोck_in_progress(ds) && !acpi_device_क्रमागतerated(adev)) अणु
			begin_करोck(ds);
			करोck(ds);
			अगर (!करोck_present(ds)) अणु
				acpi_handle_err(handle, "Unable to dock!\n");
				complete_करोck(ds);
				अवरोध;
			पूर्ण
			hotplug_करोck_devices(ds, event);
			complete_करोck(ds);
			करोck_event(ds, event, DOCK_EVENT);
			acpi_evaluate_lck(ds->handle, 1);
			acpi_update_all_gpes();
			अवरोध;
		पूर्ण
		अगर (करोck_present(ds) || करोck_in_progress(ds))
			अवरोध;
		/* This is a surprise removal */
		surprise_removal = 1;
		event = ACPI_NOTIFY_EJECT_REQUEST;
		/* Fall back */
		fallthrough;
	हाल ACPI_NOTIFY_EJECT_REQUEST:
		begin_unकरोck(ds);
		अगर ((immediate_unकरोck && !(ds->flags & DOCK_IS_ATA))
		   || surprise_removal)
			handle_eject_request(ds, event);
		अन्यथा
			करोck_event(ds, event, UNDOCK_EVENT);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * show_करोcked - पढ़ो method क्रम "docked" file in sysfs
 */
अटल sमाप_प्रकार करोcked_show(काष्ठा device *dev,
			   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा करोck_station *करोck_station = dev->platक्रमm_data;
	काष्ठा acpi_device *adev = शून्य;

	acpi_bus_get_device(करोck_station->handle, &adev);
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n", acpi_device_क्रमागतerated(adev));
पूर्ण
अटल DEVICE_ATTR_RO(करोcked);

/*
 * show_flags - पढ़ो method क्रम flags file in sysfs
 */
अटल sमाप_प्रकार flags_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा करोck_station *करोck_station = dev->platक्रमm_data;

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", करोck_station->flags);

पूर्ण
अटल DEVICE_ATTR_RO(flags);

/*
 * ग_लिखो_unकरोck - ग_लिखो method क्रम "undock" file in sysfs
 */
अटल sमाप_प्रकार unकरोck_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा करोck_station *करोck_station = dev->platक्रमm_data;

	अगर (!count)
		वापस -EINVAL;

	acpi_scan_lock_acquire();
	begin_unकरोck(करोck_station);
	ret = handle_eject_request(करोck_station, ACPI_NOTIFY_EJECT_REQUEST);
	acpi_scan_lock_release();
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_WO(unकरोck);

/*
 * show_करोck_uid - पढ़ो method क्रम "uid" file in sysfs
 */
अटल sमाप_प्रकार uid_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ दीर्घ lbuf;
	काष्ठा करोck_station *करोck_station = dev->platक्रमm_data;

	acpi_status status = acpi_evaluate_पूर्णांकeger(करोck_station->handle,
					"_UID", शून्य, &lbuf);
	अगर (ACPI_FAILURE(status))
		वापस 0;

	वापस snम_लिखो(buf, PAGE_SIZE, "%llx\n", lbuf);
पूर्ण
अटल DEVICE_ATTR_RO(uid);

अटल sमाप_प्रकार type_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा करोck_station *करोck_station = dev->platक्रमm_data;
	अक्षर *type;

	अगर (करोck_station->flags & DOCK_IS_DOCK)
		type = "dock_station";
	अन्यथा अगर (करोck_station->flags & DOCK_IS_ATA)
		type = "ata_bay";
	अन्यथा अगर (करोck_station->flags & DOCK_IS_BAT)
		type = "battery_bay";
	अन्यथा
		type = "unknown";

	वापस snम_लिखो(buf, PAGE_SIZE, "%s\n", type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल काष्ठा attribute *करोck_attributes[] = अणु
	&dev_attr_करोcked.attr,
	&dev_attr_flags.attr,
	&dev_attr_unकरोck.attr,
	&dev_attr_uid.attr,
	&dev_attr_type.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group करोck_attribute_group = अणु
	.attrs = करोck_attributes
पूर्ण;

/**
 * acpi_करोck_add - Add a new करोck station
 * @adev: Dock station ACPI device object.
 *
 * allocated and initialize a new करोck station device.
 */
व्योम acpi_करोck_add(काष्ठा acpi_device *adev)
अणु
	काष्ठा करोck_station *करोck_station, ds = अणु शून्य, पूर्ण;
	काष्ठा platक्रमm_device_info pdevinfo;
	acpi_handle handle = adev->handle;
	काष्ठा platक्रमm_device *dd;
	पूर्णांक ret;

	स_रखो(&pdevinfo, 0, माप(pdevinfo));
	pdevinfo.name = "dock";
	pdevinfo.id = करोck_station_count;
	pdevinfo.fwnode = acpi_fwnode_handle(adev);
	pdevinfo.data = &ds;
	pdevinfo.size_data = माप(ds);
	dd = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	अगर (IS_ERR(dd))
		वापस;

	करोck_station = dd->dev.platक्रमm_data;

	करोck_station->handle = handle;
	करोck_station->करोck_device = dd;
	करोck_station->last_करोck_समय = jअगरfies - HZ;

	INIT_LIST_HEAD(&करोck_station->sibling);
	INIT_LIST_HEAD(&करोck_station->dependent_devices);

	/* we want the करोck device to send uevents */
	dev_set_uevent_suppress(&dd->dev, 0);

	अगर (acpi_करोck_match(handle))
		करोck_station->flags |= DOCK_IS_DOCK;
	अगर (acpi_ata_match(handle))
		करोck_station->flags |= DOCK_IS_ATA;
	अगर (acpi_device_is_battery(adev))
		करोck_station->flags |= DOCK_IS_BAT;

	ret = sysfs_create_group(&dd->dev.kobj, &करोck_attribute_group);
	अगर (ret)
		जाओ err_unरेजिस्टर;

	/* add the करोck station as a device dependent on itself */
	ret = add_करोck_dependent_device(करोck_station, adev);
	अगर (ret)
		जाओ err_rmgroup;

	करोck_station_count++;
	list_add(&करोck_station->sibling, &करोck_stations);
	adev->flags.is_करोck_station = true;
	dev_info(&adev->dev, "ACPI dock station (docks/bays count: %d)\n",
		 करोck_station_count);
	वापस;

err_rmgroup:
	sysfs_हटाओ_group(&dd->dev.kobj, &करोck_attribute_group);

err_unरेजिस्टर:
	platक्रमm_device_unरेजिस्टर(dd);
	acpi_handle_err(handle, "%s encountered error %d\n", __func__, ret);
पूर्ण
