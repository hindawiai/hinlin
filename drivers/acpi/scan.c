<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * scan.c - support क्रम transक्रमming the ACPI namespace पूर्णांकo inभागidual objects
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/acpi_iort.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/dmi.h>
#समावेश <linux/nls.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>
#समावेश <linux/pgtable.h>

#समावेश "internal.h"

बाह्य काष्ठा acpi_device *acpi_root;

#घोषणा ACPI_BUS_CLASS			"system_bus"
#घोषणा ACPI_BUS_HID			"LNXSYBUS"
#घोषणा ACPI_BUS_DEVICE_NAME		"System Bus"

#घोषणा ACPI_IS_ROOT_DEVICE(device)    (!(device)->parent)

#घोषणा INVALID_ACPI_HANDLE	((acpi_handle)empty_zero_page)

अटल स्थिर अक्षर *dummy_hid = "device";

अटल LIST_HEAD(acpi_dep_list);
अटल DEFINE_MUTEX(acpi_dep_list_lock);
LIST_HEAD(acpi_bus_id_list);
अटल DEFINE_MUTEX(acpi_scan_lock);
अटल LIST_HEAD(acpi_scan_handlers_list);
DEFINE_MUTEX(acpi_device_lock);
LIST_HEAD(acpi_wakeup_device_list);
अटल DEFINE_MUTEX(acpi_hp_context_lock);

/*
 * The UART device described by the SPCR table is the only object which needs
 * special-casing. Everything अन्यथा is covered by ACPI namespace paths in STAO
 * table.
 */
अटल u64 spcr_uart_addr;

काष्ठा acpi_dep_data अणु
	काष्ठा list_head node;
	acpi_handle supplier;
	acpi_handle consumer;
पूर्ण;

व्योम acpi_scan_lock_acquire(व्योम)
अणु
	mutex_lock(&acpi_scan_lock);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_scan_lock_acquire);

व्योम acpi_scan_lock_release(व्योम)
अणु
	mutex_unlock(&acpi_scan_lock);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_scan_lock_release);

व्योम acpi_lock_hp_context(व्योम)
अणु
	mutex_lock(&acpi_hp_context_lock);
पूर्ण

व्योम acpi_unlock_hp_context(व्योम)
अणु
	mutex_unlock(&acpi_hp_context_lock);
पूर्ण

व्योम acpi_initialize_hp_context(काष्ठा acpi_device *adev,
				काष्ठा acpi_hotplug_context *hp,
				पूर्णांक (*notअगरy)(काष्ठा acpi_device *, u32),
				व्योम (*uevent)(काष्ठा acpi_device *, u32))
अणु
	acpi_lock_hp_context();
	hp->notअगरy = notअगरy;
	hp->uevent = uevent;
	acpi_set_hp_context(adev, hp);
	acpi_unlock_hp_context();
पूर्ण
EXPORT_SYMBOL_GPL(acpi_initialize_hp_context);

पूर्णांक acpi_scan_add_handler(काष्ठा acpi_scan_handler *handler)
अणु
	अगर (!handler)
		वापस -EINVAL;

	list_add_tail(&handler->list_node, &acpi_scan_handlers_list);
	वापस 0;
पूर्ण

पूर्णांक acpi_scan_add_handler_with_hotplug(काष्ठा acpi_scan_handler *handler,
				       स्थिर अक्षर *hotplug_profile_name)
अणु
	पूर्णांक error;

	error = acpi_scan_add_handler(handler);
	अगर (error)
		वापस error;

	acpi_sysfs_add_hotplug_profile(&handler->hotplug, hotplug_profile_name);
	वापस 0;
पूर्ण

bool acpi_scan_is_offline(काष्ठा acpi_device *adev, bool uevent)
अणु
	काष्ठा acpi_device_physical_node *pn;
	bool offline = true;
	अक्षर *envp[] = अणु "EVENT=offline", शून्य पूर्ण;

	/*
	 * acpi_container_offline() calls this क्रम all of the container's
	 * children under the container's physical_node_lock lock.
	 */
	mutex_lock_nested(&adev->physical_node_lock, SINGLE_DEPTH_NESTING);

	list_क्रम_each_entry(pn, &adev->physical_node_list, node)
		अगर (device_supports_offline(pn->dev) && !pn->dev->offline) अणु
			अगर (uevent)
				kobject_uevent_env(&pn->dev->kobj, KOBJ_CHANGE, envp);

			offline = false;
			अवरोध;
		पूर्ण

	mutex_unlock(&adev->physical_node_lock);
	वापस offline;
पूर्ण

अटल acpi_status acpi_bus_offline(acpi_handle handle, u32 lvl, व्योम *data,
				    व्योम **ret_p)
अणु
	काष्ठा acpi_device *device = शून्य;
	काष्ठा acpi_device_physical_node *pn;
	bool second_pass = (bool)data;
	acpi_status status = AE_OK;

	अगर (acpi_bus_get_device(handle, &device))
		वापस AE_OK;

	अगर (device->handler && !device->handler->hotplug.enabled) अणु
		*ret_p = &device->dev;
		वापस AE_SUPPORT;
	पूर्ण

	mutex_lock(&device->physical_node_lock);

	list_क्रम_each_entry(pn, &device->physical_node_list, node) अणु
		पूर्णांक ret;

		अगर (second_pass) अणु
			/* Skip devices offlined by the first pass. */
			अगर (pn->put_online)
				जारी;
		पूर्ण अन्यथा अणु
			pn->put_online = false;
		पूर्ण
		ret = device_offline(pn->dev);
		अगर (ret >= 0) अणु
			pn->put_online = !ret;
		पूर्ण अन्यथा अणु
			*ret_p = pn->dev;
			अगर (second_pass) अणु
				status = AE_ERROR;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&device->physical_node_lock);

	वापस status;
पूर्ण

अटल acpi_status acpi_bus_online(acpi_handle handle, u32 lvl, व्योम *data,
				   व्योम **ret_p)
अणु
	काष्ठा acpi_device *device = शून्य;
	काष्ठा acpi_device_physical_node *pn;

	अगर (acpi_bus_get_device(handle, &device))
		वापस AE_OK;

	mutex_lock(&device->physical_node_lock);

	list_क्रम_each_entry(pn, &device->physical_node_list, node)
		अगर (pn->put_online) अणु
			device_online(pn->dev);
			pn->put_online = false;
		पूर्ण

	mutex_unlock(&device->physical_node_lock);

	वापस AE_OK;
पूर्ण

अटल पूर्णांक acpi_scan_try_to_offline(काष्ठा acpi_device *device)
अणु
	acpi_handle handle = device->handle;
	काष्ठा device *errdev = शून्य;
	acpi_status status;

	/*
	 * Carry out two passes here and ignore errors in the first pass,
	 * because अगर the devices in question are memory blocks and
	 * CONFIG_MEMCG is set, one of the blocks may hold data काष्ठाures
	 * that the other blocks depend on, but it is not known in advance which
	 * block holds them.
	 *
	 * If the first pass is successful, the second one isn't needed, though.
	 */
	status = acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				     शून्य, acpi_bus_offline, (व्योम *)false,
				     (व्योम **)&errdev);
	अगर (status == AE_SUPPORT) अणु
		dev_warn(errdev, "Offline disabled.\n");
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    acpi_bus_online, शून्य, शून्य, शून्य);
		वापस -EPERM;
	पूर्ण
	acpi_bus_offline(handle, 0, (व्योम *)false, (व्योम **)&errdev);
	अगर (errdev) अणु
		errdev = शून्य;
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    शून्य, acpi_bus_offline, (व्योम *)true,
				    (व्योम **)&errdev);
		अगर (!errdev)
			acpi_bus_offline(handle, 0, (व्योम *)true,
					 (व्योम **)&errdev);

		अगर (errdev) अणु
			dev_warn(errdev, "Offline failed.\n");
			acpi_bus_online(handle, 0, शून्य, शून्य);
			acpi_walk_namespace(ACPI_TYPE_ANY, handle,
					    ACPI_UINT32_MAX, acpi_bus_online,
					    शून्य, शून्य, शून्य);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_scan_hot_हटाओ(काष्ठा acpi_device *device)
अणु
	acpi_handle handle = device->handle;
	अचिन्हित दीर्घ दीर्घ sta;
	acpi_status status;

	अगर (device->handler && device->handler->hotplug.demand_offline) अणु
		अगर (!acpi_scan_is_offline(device, true))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु
		पूर्णांक error = acpi_scan_try_to_offline(device);
		अगर (error)
			वापस error;
	पूर्ण

	acpi_handle_debug(handle, "Ejecting\n");

	acpi_bus_trim(device);

	acpi_evaluate_lck(handle, 0);
	/*
	 * TBD: _EJD support.
	 */
	status = acpi_evaluate_ej0(handle);
	अगर (status == AE_NOT_FOUND)
		वापस -ENODEV;
	अन्यथा अगर (ACPI_FAILURE(status))
		वापस -EIO;

	/*
	 * Verअगरy अगर eject was indeed successful.  If not, log an error
	 * message.  No need to call _OST since _EJ0 call was made OK.
	 */
	status = acpi_evaluate_पूर्णांकeger(handle, "_STA", शून्य, &sta);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_warn(handle,
			"Status check after eject failed (0x%x)\n", status);
	पूर्ण अन्यथा अगर (sta & ACPI_STA_DEVICE_ENABLED) अणु
		acpi_handle_warn(handle,
			"Eject incomplete - status 0x%llx\n", sta);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_scan_device_not_present(काष्ठा acpi_device *adev)
अणु
	अगर (!acpi_device_क्रमागतerated(adev)) अणु
		dev_warn(&adev->dev, "Still not present\n");
		वापस -EALREADY;
	पूर्ण
	acpi_bus_trim(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_scan_device_check(काष्ठा acpi_device *adev)
अणु
	पूर्णांक error;

	acpi_bus_get_status(adev);
	अगर (adev->status.present || adev->status.functional) अणु
		/*
		 * This function is only called क्रम device objects क्रम which
		 * matching scan handlers exist.  The only situation in which
		 * the scan handler is not attached to this device object yet
		 * is when the device has just appeared (either it wasn't
		 * present at all beक्रमe or it was हटाओd and then added
		 * again).
		 */
		अगर (adev->handler) अणु
			dev_warn(&adev->dev, "Already enumerated\n");
			वापस -EALREADY;
		पूर्ण
		error = acpi_bus_scan(adev->handle);
		अगर (error) अणु
			dev_warn(&adev->dev, "Namespace scan failure\n");
			वापस error;
		पूर्ण
		अगर (!adev->handler) अणु
			dev_warn(&adev->dev, "Enumeration failure\n");
			error = -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		error = acpi_scan_device_not_present(adev);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक acpi_scan_bus_check(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_scan_handler *handler = adev->handler;
	काष्ठा acpi_device *child;
	पूर्णांक error;

	acpi_bus_get_status(adev);
	अगर (!(adev->status.present || adev->status.functional)) अणु
		acpi_scan_device_not_present(adev);
		वापस 0;
	पूर्ण
	अगर (handler && handler->hotplug.scan_dependent)
		वापस handler->hotplug.scan_dependent(adev);

	error = acpi_bus_scan(adev->handle);
	अगर (error) अणु
		dev_warn(&adev->dev, "Namespace scan failure\n");
		वापस error;
	पूर्ण
	list_क्रम_each_entry(child, &adev->children, node) अणु
		error = acpi_scan_bus_check(child);
		अगर (error)
			वापस error;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_generic_hotplug_event(काष्ठा acpi_device *adev, u32 type)
अणु
	चयन (type) अणु
	हाल ACPI_NOTIFY_BUS_CHECK:
		वापस acpi_scan_bus_check(adev);
	हाल ACPI_NOTIFY_DEVICE_CHECK:
		वापस acpi_scan_device_check(adev);
	हाल ACPI_NOTIFY_EJECT_REQUEST:
	हाल ACPI_OST_EC_OSPM_EJECT:
		अगर (adev->handler && !adev->handler->hotplug.enabled) अणु
			dev_info(&adev->dev, "Eject disabled\n");
			वापस -EPERM;
		पूर्ण
		acpi_evaluate_ost(adev->handle, ACPI_NOTIFY_EJECT_REQUEST,
				  ACPI_OST_SC_EJECT_IN_PROGRESS, शून्य);
		वापस acpi_scan_hot_हटाओ(adev);
	पूर्ण
	वापस -EINVAL;
पूर्ण

व्योम acpi_device_hotplug(काष्ठा acpi_device *adev, u32 src)
अणु
	u32 ost_code = ACPI_OST_SC_NON_SPECIFIC_FAILURE;
	पूर्णांक error = -ENODEV;

	lock_device_hotplug();
	mutex_lock(&acpi_scan_lock);

	/*
	 * The device object's ACPI handle cannot become invalid as दीर्घ as we
	 * are holding acpi_scan_lock, but it might have become invalid beक्रमe
	 * that lock was acquired.
	 */
	अगर (adev->handle == INVALID_ACPI_HANDLE)
		जाओ err_out;

	अगर (adev->flags.is_करोck_station) अणु
		error = करोck_notअगरy(adev, src);
	पूर्ण अन्यथा अगर (adev->flags.hotplug_notअगरy) अणु
		error = acpi_generic_hotplug_event(adev, src);
	पूर्ण अन्यथा अणु
		पूर्णांक (*notअगरy)(काष्ठा acpi_device *, u32);

		acpi_lock_hp_context();
		notअगरy = adev->hp ? adev->hp->notअगरy : शून्य;
		acpi_unlock_hp_context();
		/*
		 * There may be additional notअगरy handlers क्रम device objects
		 * without the .event() callback, so ignore them here.
		 */
		अगर (notअगरy)
			error = notअगरy(adev, src);
		अन्यथा
			जाओ out;
	पूर्ण
	चयन (error) अणु
	हाल 0:
		ost_code = ACPI_OST_SC_SUCCESS;
		अवरोध;
	हाल -EPERM:
		ost_code = ACPI_OST_SC_EJECT_NOT_SUPPORTED;
		अवरोध;
	हाल -EBUSY:
		ost_code = ACPI_OST_SC_DEVICE_BUSY;
		अवरोध;
	शेष:
		ost_code = ACPI_OST_SC_NON_SPECIFIC_FAILURE;
		अवरोध;
	पूर्ण

 err_out:
	acpi_evaluate_ost(adev->handle, src, ost_code, शून्य);

 out:
	acpi_bus_put_acpi_device(adev);
	mutex_unlock(&acpi_scan_lock);
	unlock_device_hotplug();
पूर्ण

अटल व्योम acpi_मुक्त_घातer_resources_lists(काष्ठा acpi_device *device)
अणु
	पूर्णांक i;

	अगर (device->wakeup.flags.valid)
		acpi_घातer_resources_list_मुक्त(&device->wakeup.resources);

	अगर (!device->घातer.flags.घातer_resources)
		वापस;

	क्रम (i = ACPI_STATE_D0; i <= ACPI_STATE_D3_HOT; i++) अणु
		काष्ठा acpi_device_घातer_state *ps = &device->घातer.states[i];
		acpi_घातer_resources_list_मुक्त(&ps->resources);
	पूर्ण
पूर्ण

अटल व्योम acpi_device_release(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);

	acpi_मुक्त_properties(acpi_dev);
	acpi_मुक्त_pnp_ids(&acpi_dev->pnp);
	acpi_मुक्त_घातer_resources_lists(acpi_dev);
	kमुक्त(acpi_dev);
पूर्ण

अटल व्योम acpi_device_del(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_device_bus_id *acpi_device_bus_id;

	mutex_lock(&acpi_device_lock);
	अगर (device->parent)
		list_del(&device->node);

	list_क्रम_each_entry(acpi_device_bus_id, &acpi_bus_id_list, node)
		अगर (!म_भेद(acpi_device_bus_id->bus_id,
			    acpi_device_hid(device))) अणु
			ida_simple_हटाओ(&acpi_device_bus_id->instance_ida, device->pnp.instance_no);
			अगर (ida_is_empty(&acpi_device_bus_id->instance_ida)) अणु
				list_del(&acpi_device_bus_id->node);
				kमुक्त_स्थिर(acpi_device_bus_id->bus_id);
				kमुक्त(acpi_device_bus_id);
			पूर्ण
			अवरोध;
		पूर्ण

	list_del(&device->wakeup_list);
	mutex_unlock(&acpi_device_lock);

	acpi_घातer_add_हटाओ_device(device, false);
	acpi_device_हटाओ_files(device);
	अगर (device->हटाओ)
		device->हटाओ(device);

	device_del(&device->dev);
पूर्ण

अटल BLOCKING_NOTIFIER_HEAD(acpi_reconfig_chain);

अटल LIST_HEAD(acpi_device_del_list);
अटल DEFINE_MUTEX(acpi_device_del_lock);

अटल व्योम acpi_device_del_work_fn(काष्ठा work_काष्ठा *work_not_used)
अणु
	क्रम (;;) अणु
		काष्ठा acpi_device *adev;

		mutex_lock(&acpi_device_del_lock);

		अगर (list_empty(&acpi_device_del_list)) अणु
			mutex_unlock(&acpi_device_del_lock);
			अवरोध;
		पूर्ण
		adev = list_first_entry(&acpi_device_del_list,
					काष्ठा acpi_device, del_list);
		list_del(&adev->del_list);

		mutex_unlock(&acpi_device_del_lock);

		blocking_notअगरier_call_chain(&acpi_reconfig_chain,
					     ACPI_RECONFIG_DEVICE_REMOVE, adev);

		acpi_device_del(adev);
		/*
		 * Drop references to all घातer resources that might have been
		 * used by the device.
		 */
		acpi_घातer_transition(adev, ACPI_STATE_D3_COLD);
		acpi_dev_put(adev);
	पूर्ण
पूर्ण

/**
 * acpi_scan_drop_device - Drop an ACPI device object.
 * @handle: Handle of an ACPI namespace node, not used.
 * @context: Address of the ACPI device object to drop.
 *
 * This is invoked by acpi_ns_delete_node() during the removal of the ACPI
 * namespace node the device object poपूर्णांकed to by @context is attached to.
 *
 * The unregistration is carried out asynchronously to aव्योम running
 * acpi_device_del() under the ACPICA's namespace mutex and the list is used to
 * ensure the correct ordering (the device objects must be unरेजिस्टरed in the
 * same order in which the corresponding namespace nodes are deleted).
 */
अटल व्योम acpi_scan_drop_device(acpi_handle handle, व्योम *context)
अणु
	अटल DECLARE_WORK(work, acpi_device_del_work_fn);
	काष्ठा acpi_device *adev = context;

	mutex_lock(&acpi_device_del_lock);

	/*
	 * Use the ACPI hotplug workqueue which is ordered, so this work item
	 * won't run after any hotplug work items submitted subsequently.  That
	 * prevents attempts to रेजिस्टर device objects identical to those being
	 * deleted from happening concurrently (such attempts result from
	 * hotplug events handled via the ACPI hotplug workqueue).  It also will
	 * run after all of the work items submitted previously, which helps
	 * those work items to ensure that they are not accessing stale device
	 * objects.
	 */
	अगर (list_empty(&acpi_device_del_list))
		acpi_queue_hotplug_work(&work);

	list_add_tail(&adev->del_list, &acpi_device_del_list);
	/* Make acpi_ns_validate_handle() वापस शून्य क्रम this handle. */
	adev->handle = INVALID_ACPI_HANDLE;

	mutex_unlock(&acpi_device_del_lock);
पूर्ण

अटल काष्ठा acpi_device *handle_to_device(acpi_handle handle,
					    व्योम (*callback)(व्योम *))
अणु
	काष्ठा acpi_device *adev = शून्य;
	acpi_status status;

	status = acpi_get_data_full(handle, acpi_scan_drop_device,
				    (व्योम **)&adev, callback);
	अगर (ACPI_FAILURE(status) || !adev) अणु
		acpi_handle_debug(handle, "No context!\n");
		वापस शून्य;
	पूर्ण
	वापस adev;
पूर्ण

पूर्णांक acpi_bus_get_device(acpi_handle handle, काष्ठा acpi_device **device)
अणु
	अगर (!device)
		वापस -EINVAL;

	*device = handle_to_device(handle, शून्य);
	अगर (!*device)
		वापस -ENODEV;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_bus_get_device);

अटल व्योम get_acpi_device(व्योम *dev)
अणु
	acpi_dev_get(dev);
पूर्ण

काष्ठा acpi_device *acpi_bus_get_acpi_device(acpi_handle handle)
अणु
	वापस handle_to_device(handle, get_acpi_device);
पूर्ण

व्योम acpi_bus_put_acpi_device(काष्ठा acpi_device *adev)
अणु
	acpi_dev_put(adev);
पूर्ण

अटल काष्ठा acpi_device_bus_id *acpi_device_bus_id_match(स्थिर अक्षर *dev_id)
अणु
	काष्ठा acpi_device_bus_id *acpi_device_bus_id;

	/* Find suitable bus_id and instance number in acpi_bus_id_list. */
	list_क्रम_each_entry(acpi_device_bus_id, &acpi_bus_id_list, node) अणु
		अगर (!म_भेद(acpi_device_bus_id->bus_id, dev_id))
			वापस acpi_device_bus_id;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक acpi_device_set_name(काष्ठा acpi_device *device,
				काष्ठा acpi_device_bus_id *acpi_device_bus_id)
अणु
	काष्ठा ida *instance_ida = &acpi_device_bus_id->instance_ida;
	पूर्णांक result;

	result = ida_simple_get(instance_ida, 0, ACPI_MAX_DEVICE_INSTANCES, GFP_KERNEL);
	अगर (result < 0)
		वापस result;

	device->pnp.instance_no = result;
	dev_set_name(&device->dev, "%s:%02x", acpi_device_bus_id->bus_id, result);
	वापस 0;
पूर्ण

पूर्णांक acpi_device_add(काष्ठा acpi_device *device,
		    व्योम (*release)(काष्ठा device *))
अणु
	काष्ठा acpi_device_bus_id *acpi_device_bus_id;
	पूर्णांक result;

	अगर (device->handle) अणु
		acpi_status status;

		status = acpi_attach_data(device->handle, acpi_scan_drop_device,
					  device);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_err(device->handle,
					"Unable to attach device data\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	 * Linkage
	 * -------
	 * Link this device to its parent and siblings.
	 */
	INIT_LIST_HEAD(&device->children);
	INIT_LIST_HEAD(&device->node);
	INIT_LIST_HEAD(&device->wakeup_list);
	INIT_LIST_HEAD(&device->physical_node_list);
	INIT_LIST_HEAD(&device->del_list);
	mutex_init(&device->physical_node_lock);

	mutex_lock(&acpi_device_lock);

	acpi_device_bus_id = acpi_device_bus_id_match(acpi_device_hid(device));
	अगर (acpi_device_bus_id) अणु
		result = acpi_device_set_name(device, acpi_device_bus_id);
		अगर (result)
			जाओ err_unlock;
	पूर्ण अन्यथा अणु
		acpi_device_bus_id = kzalloc(माप(*acpi_device_bus_id),
					     GFP_KERNEL);
		अगर (!acpi_device_bus_id) अणु
			result = -ENOMEM;
			जाओ err_unlock;
		पूर्ण
		acpi_device_bus_id->bus_id =
			kstrdup_स्थिर(acpi_device_hid(device), GFP_KERNEL);
		अगर (!acpi_device_bus_id->bus_id) अणु
			kमुक्त(acpi_device_bus_id);
			result = -ENOMEM;
			जाओ err_unlock;
		पूर्ण

		ida_init(&acpi_device_bus_id->instance_ida);

		result = acpi_device_set_name(device, acpi_device_bus_id);
		अगर (result) अणु
			kमुक्त_स्थिर(acpi_device_bus_id->bus_id);
			kमुक्त(acpi_device_bus_id);
			जाओ err_unlock;
		पूर्ण

		list_add_tail(&acpi_device_bus_id->node, &acpi_bus_id_list);
	पूर्ण

	अगर (device->parent)
		list_add_tail(&device->node, &device->parent->children);

	अगर (device->wakeup.flags.valid)
		list_add_tail(&device->wakeup_list, &acpi_wakeup_device_list);

	mutex_unlock(&acpi_device_lock);

	अगर (device->parent)
		device->dev.parent = &device->parent->dev;

	device->dev.bus = &acpi_bus_type;
	device->dev.release = release;
	result = device_add(&device->dev);
	अगर (result) अणु
		dev_err(&device->dev, "Error registering device\n");
		जाओ err;
	पूर्ण

	result = acpi_device_setup_files(device);
	अगर (result)
		prपूर्णांकk(KERN_ERR PREFIX "Error creating sysfs interface for device %s\n",
		       dev_name(&device->dev));

	वापस 0;

err:
	mutex_lock(&acpi_device_lock);

	अगर (device->parent)
		list_del(&device->node);

	list_del(&device->wakeup_list);

err_unlock:
	mutex_unlock(&acpi_device_lock);

	acpi_detach_data(device->handle, acpi_scan_drop_device);

	वापस result;
पूर्ण

/* --------------------------------------------------------------------------
                                 Device Enumeration
   -------------------------------------------------------------------------- */
अटल bool acpi_info_matches_ids(काष्ठा acpi_device_info *info,
				  स्थिर अक्षर * स्थिर ids[])
अणु
	काष्ठा acpi_pnp_device_id_list *cid_list = शून्य;
	पूर्णांक i, index;

	अगर (!(info->valid & ACPI_VALID_HID))
		वापस false;

	index = match_string(ids, -1, info->hardware_id.string);
	अगर (index >= 0)
		वापस true;

	अगर (info->valid & ACPI_VALID_CID)
		cid_list = &info->compatible_id_list;

	अगर (!cid_list)
		वापस false;

	क्रम (i = 0; i < cid_list->count; i++) अणु
		index = match_string(ids, -1, cid_list->ids[i].string);
		अगर (index >= 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* List of HIDs क्रम which we ignore matching ACPI devices, when checking _DEP lists. */
अटल स्थिर अक्षर * स्थिर acpi_ignore_dep_ids[] = अणु
	"PNP0D80", /* Winकरोws-compatible System Power Management Controller */
	"INT33BD", /* Intel Baytrail Mailbox Device */
	शून्य
पूर्ण;

अटल काष्ठा acpi_device *acpi_bus_get_parent(acpi_handle handle)
अणु
	काष्ठा acpi_device *device = शून्य;
	acpi_status status;

	/*
	 * Fixed hardware devices करो not appear in the namespace and करो not
	 * have handles, but we fabricate acpi_devices क्रम them, so we have
	 * to deal with them specially.
	 */
	अगर (!handle)
		वापस acpi_root;

	करो अणु
		status = acpi_get_parent(handle, &handle);
		अगर (ACPI_FAILURE(status))
			वापस status == AE_शून्य_ENTRY ? शून्य : acpi_root;
	पूर्ण जबतक (acpi_bus_get_device(handle, &device));
	वापस device;
पूर्ण

acpi_status
acpi_bus_get_ejd(acpi_handle handle, acpi_handle *ejd)
अणु
	acpi_status status;
	acpi_handle पंचांगp;
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	जोड़ acpi_object *obj;

	status = acpi_get_handle(handle, "_EJD", &पंचांगp);
	अगर (ACPI_FAILURE(status))
		वापस status;

	status = acpi_evaluate_object(handle, "_EJD", शून्य, &buffer);
	अगर (ACPI_SUCCESS(status)) अणु
		obj = buffer.poपूर्णांकer;
		status = acpi_get_handle(ACPI_ROOT_OBJECT, obj->string.poपूर्णांकer,
					 ejd);
		kमुक्त(buffer.poपूर्णांकer);
	पूर्ण
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_get_ejd);

अटल पूर्णांक acpi_bus_extract_wakeup_device_घातer_package(काष्ठा acpi_device *dev)
अणु
	acpi_handle handle = dev->handle;
	काष्ठा acpi_device_wakeup *wakeup = &dev->wakeup;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *package = शून्य;
	जोड़ acpi_object *element = शून्य;
	acpi_status status;
	पूर्णांक err = -ENODATA;

	INIT_LIST_HEAD(&wakeup->resources);

	/* _PRW */
	status = acpi_evaluate_object(handle, "_PRW", शून्य, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_info(handle, "_PRW evaluation failed: %s\n",
				 acpi_क्रमmat_exception(status));
		वापस err;
	पूर्ण

	package = (जोड़ acpi_object *)buffer.poपूर्णांकer;

	अगर (!package || package->package.count < 2)
		जाओ out;

	element = &(package->package.elements[0]);
	अगर (!element)
		जाओ out;

	अगर (element->type == ACPI_TYPE_PACKAGE) अणु
		अगर ((element->package.count < 2) ||
		    (element->package.elements[0].type !=
		     ACPI_TYPE_LOCAL_REFERENCE)
		    || (element->package.elements[1].type != ACPI_TYPE_INTEGER))
			जाओ out;

		wakeup->gpe_device =
		    element->package.elements[0].reference.handle;
		wakeup->gpe_number =
		    (u32) element->package.elements[1].पूर्णांकeger.value;
	पूर्ण अन्यथा अगर (element->type == ACPI_TYPE_INTEGER) अणु
		wakeup->gpe_device = शून्य;
		wakeup->gpe_number = element->पूर्णांकeger.value;
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	element = &(package->package.elements[1]);
	अगर (element->type != ACPI_TYPE_INTEGER)
		जाओ out;

	wakeup->sleep_state = element->पूर्णांकeger.value;

	err = acpi_extract_घातer_resources(package, 2, &wakeup->resources);
	अगर (err)
		जाओ out;

	अगर (!list_empty(&wakeup->resources)) अणु
		पूर्णांक sleep_state;

		err = acpi_घातer_wakeup_list_init(&wakeup->resources,
						  &sleep_state);
		अगर (err) अणु
			acpi_handle_warn(handle, "Retrieving current states "
					 "of wakeup power resources failed\n");
			acpi_घातer_resources_list_मुक्त(&wakeup->resources);
			जाओ out;
		पूर्ण
		अगर (sleep_state < wakeup->sleep_state) अणु
			acpi_handle_warn(handle, "Overriding _PRW sleep state "
					 "(S%d) by S%d from power resources\n",
					 (पूर्णांक)wakeup->sleep_state, sleep_state);
			wakeup->sleep_state = sleep_state;
		पूर्ण
	पूर्ण

 out:
	kमुक्त(buffer.poपूर्णांकer);
	वापस err;
पूर्ण

अटल bool acpi_wakeup_gpe_init(काष्ठा acpi_device *device)
अणु
	अटल स्थिर काष्ठा acpi_device_id button_device_ids[] = अणु
		अणु"PNP0C0C", 0पूर्ण,		/* Power button */
		अणु"PNP0C0D", 0पूर्ण,		/* Lid */
		अणु"PNP0C0E", 0पूर्ण,		/* Sleep button */
		अणु"", 0पूर्ण,
	पूर्ण;
	काष्ठा acpi_device_wakeup *wakeup = &device->wakeup;
	acpi_status status;

	wakeup->flags.notअगरier_present = 0;

	/* Power button, Lid चयन always enable wakeup */
	अगर (!acpi_match_device_ids(device, button_device_ids)) अणु
		अगर (!acpi_match_device_ids(device, &button_device_ids[1])) अणु
			/* Do not use Lid/sleep button क्रम S5 wakeup */
			अगर (wakeup->sleep_state == ACPI_STATE_S5)
				wakeup->sleep_state = ACPI_STATE_S4;
		पूर्ण
		acpi_mark_gpe_क्रम_wake(wakeup->gpe_device, wakeup->gpe_number);
		device_set_wakeup_capable(&device->dev, true);
		वापस true;
	पूर्ण

	status = acpi_setup_gpe_क्रम_wake(device->handle, wakeup->gpe_device,
					 wakeup->gpe_number);
	वापस ACPI_SUCCESS(status);
पूर्ण

अटल व्योम acpi_bus_get_wakeup_device_flags(काष्ठा acpi_device *device)
अणु
	पूर्णांक err;

	/* Presence of _PRW indicates wake capable */
	अगर (!acpi_has_method(device->handle, "_PRW"))
		वापस;

	err = acpi_bus_extract_wakeup_device_घातer_package(device);
	अगर (err) अणु
		dev_err(&device->dev, "Unable to extract wakeup power resources");
		वापस;
	पूर्ण

	device->wakeup.flags.valid = acpi_wakeup_gpe_init(device);
	device->wakeup.prepare_count = 0;
	/*
	 * Call _PSW/_DSW object to disable its ability to wake the sleeping
	 * प्रणाली क्रम the ACPI device with the _PRW object.
	 * The _PSW object is deprecated in ACPI 3.0 and is replaced by _DSW.
	 * So it is necessary to call _DSW object first. Only when it is not
	 * present will the _PSW object used.
	 */
	err = acpi_device_sleep_wake(device, 0, 0, 0);
	अगर (err)
		pr_debug("error in _DSW or _PSW evaluation\n");
पूर्ण

अटल व्योम acpi_bus_init_घातer_state(काष्ठा acpi_device *device, पूर्णांक state)
अणु
	काष्ठा acpi_device_घातer_state *ps = &device->घातer.states[state];
	अक्षर pathname[5] = अणु '_', 'P', 'R', '0' + state, '\0' पूर्ण;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	acpi_status status;

	INIT_LIST_HEAD(&ps->resources);

	/* Evaluate "_PRx" to get referenced घातer resources */
	status = acpi_evaluate_object(device->handle, pathname, शून्य, &buffer);
	अगर (ACPI_SUCCESS(status)) अणु
		जोड़ acpi_object *package = buffer.poपूर्णांकer;

		अगर (buffer.length && package
		    && package->type == ACPI_TYPE_PACKAGE
		    && package->package.count)
			acpi_extract_घातer_resources(package, 0, &ps->resources);

		ACPI_FREE(buffer.poपूर्णांकer);
	पूर्ण

	/* Evaluate "_PSx" to see अगर we can करो explicit sets */
	pathname[2] = 'S';
	अगर (acpi_has_method(device->handle, pathname))
		ps->flags.explicit_set = 1;

	/* State is valid अगर there are means to put the device पूर्णांकo it. */
	अगर (!list_empty(&ps->resources) || ps->flags.explicit_set)
		ps->flags.valid = 1;

	ps->घातer = -1;		/* Unknown - driver asचिन्हित */
	ps->latency = -1;	/* Unknown - driver asचिन्हित */
पूर्ण

अटल व्योम acpi_bus_get_घातer_flags(काष्ठा acpi_device *device)
अणु
	u32 i;

	/* Presence of _PS0|_PR0 indicates 'power manageable' */
	अगर (!acpi_has_method(device->handle, "_PS0") &&
	    !acpi_has_method(device->handle, "_PR0"))
		वापस;

	device->flags.घातer_manageable = 1;

	/*
	 * Power Management Flags
	 */
	अगर (acpi_has_method(device->handle, "_PSC"))
		device->घातer.flags.explicit_get = 1;

	अगर (acpi_has_method(device->handle, "_IRC"))
		device->घातer.flags.inrush_current = 1;

	अगर (acpi_has_method(device->handle, "_DSW"))
		device->घातer.flags.dsw_present = 1;

	/*
	 * Enumerate supported घातer management states
	 */
	क्रम (i = ACPI_STATE_D0; i <= ACPI_STATE_D3_HOT; i++)
		acpi_bus_init_घातer_state(device, i);

	INIT_LIST_HEAD(&device->घातer.states[ACPI_STATE_D3_COLD].resources);

	/* Set the शेषs क्रम D0 and D3hot (always supported). */
	device->घातer.states[ACPI_STATE_D0].flags.valid = 1;
	device->घातer.states[ACPI_STATE_D0].घातer = 100;
	device->घातer.states[ACPI_STATE_D3_HOT].flags.valid = 1;

	/*
	 * Use घातer resources only अगर the D0 list of them is populated, because
	 * some platक्रमms may provide _PR3 only to indicate D3cold support and
	 * in those हालs the घातer resources list वापसed by it may be bogus.
	 */
	अगर (!list_empty(&device->घातer.states[ACPI_STATE_D0].resources)) अणु
		device->घातer.flags.घातer_resources = 1;
		/*
		 * D3cold is supported अगर the D3hot list of घातer resources is
		 * not empty.
		 */
		अगर (!list_empty(&device->घातer.states[ACPI_STATE_D3_HOT].resources))
			device->घातer.states[ACPI_STATE_D3_COLD].flags.valid = 1;
	पूर्ण

	अगर (acpi_bus_init_घातer(device))
		device->flags.घातer_manageable = 0;
पूर्ण

अटल व्योम acpi_bus_get_flags(काष्ठा acpi_device *device)
अणु
	/* Presence of _STA indicates 'dynamic_status' */
	अगर (acpi_has_method(device->handle, "_STA"))
		device->flags.dynamic_status = 1;

	/* Presence of _RMV indicates 'removable' */
	अगर (acpi_has_method(device->handle, "_RMV"))
		device->flags.removable = 1;

	/* Presence of _EJD|_EJ0 indicates 'ejectable' */
	अगर (acpi_has_method(device->handle, "_EJD") ||
	    acpi_has_method(device->handle, "_EJ0"))
		device->flags.ejectable = 1;
पूर्ण

अटल व्योम acpi_device_get_busid(काष्ठा acpi_device *device)
अणु
	अक्षर bus_id[5] = अणु '?', 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणु माप(bus_id), bus_id पूर्ण;
	पूर्णांक i = 0;

	/*
	 * Bus ID
	 * ------
	 * The device's Bus ID is simply the object name.
	 * TBD: Shouldn't this value be unique (within the ACPI namespace)?
	 */
	अगर (ACPI_IS_ROOT_DEVICE(device)) अणु
		म_नकल(device->pnp.bus_id, "ACPI");
		वापस;
	पूर्ण

	चयन (device->device_type) अणु
	हाल ACPI_BUS_TYPE_POWER_BUTTON:
		म_नकल(device->pnp.bus_id, "PWRF");
		अवरोध;
	हाल ACPI_BUS_TYPE_SLEEP_BUTTON:
		म_नकल(device->pnp.bus_id, "SLPF");
		अवरोध;
	हाल ACPI_BUS_TYPE_ECDT_EC:
		म_नकल(device->pnp.bus_id, "ECDT");
		अवरोध;
	शेष:
		acpi_get_name(device->handle, ACPI_SINGLE_NAME, &buffer);
		/* Clean up trailing underscores (अगर any) */
		क्रम (i = 3; i > 1; i--) अणु
			अगर (bus_id[i] == '_')
				bus_id[i] = '\0';
			अन्यथा
				अवरोध;
		पूर्ण
		म_नकल(device->pnp.bus_id, bus_id);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * acpi_ata_match - see अगर an acpi object is an ATA device
 *
 * If an acpi object has one of the ACPI ATA methods defined,
 * then we can safely call it an ATA device.
 */
bool acpi_ata_match(acpi_handle handle)
अणु
	वापस acpi_has_method(handle, "_GTF") ||
	       acpi_has_method(handle, "_GTM") ||
	       acpi_has_method(handle, "_STM") ||
	       acpi_has_method(handle, "_SDD");
पूर्ण

/*
 * acpi_bay_match - see अगर an acpi object is an ejectable driver bay
 *
 * If an acpi object is ejectable and has one of the ACPI ATA methods defined,
 * then we can safely call it an ejectable drive bay
 */
bool acpi_bay_match(acpi_handle handle)
अणु
	acpi_handle phandle;

	अगर (!acpi_has_method(handle, "_EJ0"))
		वापस false;
	अगर (acpi_ata_match(handle))
		वापस true;
	अगर (ACPI_FAILURE(acpi_get_parent(handle, &phandle)))
		वापस false;

	वापस acpi_ata_match(phandle);
पूर्ण

bool acpi_device_is_battery(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_hardware_id *hwid;

	list_क्रम_each_entry(hwid, &adev->pnp.ids, list)
		अगर (!म_भेद("PNP0C0A", hwid->id))
			वापस true;

	वापस false;
पूर्ण

अटल bool is_ejectable_bay(काष्ठा acpi_device *adev)
अणु
	acpi_handle handle = adev->handle;

	अगर (acpi_has_method(handle, "_EJ0") && acpi_device_is_battery(adev))
		वापस true;

	वापस acpi_bay_match(handle);
पूर्ण

/*
 * acpi_करोck_match - see अगर an acpi object has a _DCK method
 */
bool acpi_करोck_match(acpi_handle handle)
अणु
	वापस acpi_has_method(handle, "_DCK");
पूर्ण

अटल acpi_status
acpi_backlight_cap_match(acpi_handle handle, u32 level, व्योम *context,
			  व्योम **वापस_value)
अणु
	दीर्घ *cap = context;

	अगर (acpi_has_method(handle, "_BCM") &&
	    acpi_has_method(handle, "_BCL")) अणु
		acpi_handle_debug(handle, "Found generic backlight support\n");
		*cap |= ACPI_VIDEO_BACKLIGHT;
		/* We have backlight support, no need to scan further */
		वापस AE_CTRL_TERMINATE;
	पूर्ण
	वापस 0;
पूर्ण

/* Returns true अगर the ACPI object is a video device which can be
 * handled by video.ko.
 * The device will get a Linux specअगरic CID added in scan.c to
 * identअगरy the device as an ACPI graphics device
 * Be aware that the graphics device may not be physically present
 * Use acpi_video_get_capabilities() to detect general ACPI video
 * capabilities of present cards
 */
दीर्घ acpi_is_video_device(acpi_handle handle)
अणु
	दीर्घ video_caps = 0;

	/* Is this device able to support video चयनing ? */
	अगर (acpi_has_method(handle, "_DOD") || acpi_has_method(handle, "_DOS"))
		video_caps |= ACPI_VIDEO_OUTPUT_SWITCHING;

	/* Is this device able to retrieve a video ROM ? */
	अगर (acpi_has_method(handle, "_ROM"))
		video_caps |= ACPI_VIDEO_ROM_AVAILABLE;

	/* Is this device able to configure which video head to be POSTed ? */
	अगर (acpi_has_method(handle, "_VPO") &&
	    acpi_has_method(handle, "_GPD") &&
	    acpi_has_method(handle, "_SPD"))
		video_caps |= ACPI_VIDEO_DEVICE_POSTING;

	/* Only check क्रम backlight functionality अगर one of the above hit. */
	अगर (video_caps)
		acpi_walk_namespace(ACPI_TYPE_DEVICE, handle,
				    ACPI_UINT32_MAX, acpi_backlight_cap_match, शून्य,
				    &video_caps, शून्य);

	वापस video_caps;
पूर्ण
EXPORT_SYMBOL(acpi_is_video_device);

स्थिर अक्षर *acpi_device_hid(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_hardware_id *hid;

	अगर (list_empty(&device->pnp.ids))
		वापस dummy_hid;

	hid = list_first_entry(&device->pnp.ids, काष्ठा acpi_hardware_id, list);
	वापस hid->id;
पूर्ण
EXPORT_SYMBOL(acpi_device_hid);

अटल व्योम acpi_add_id(काष्ठा acpi_device_pnp *pnp, स्थिर अक्षर *dev_id)
अणु
	काष्ठा acpi_hardware_id *id;

	id = kदो_स्मृति(माप(*id), GFP_KERNEL);
	अगर (!id)
		वापस;

	id->id = kstrdup_स्थिर(dev_id, GFP_KERNEL);
	अगर (!id->id) अणु
		kमुक्त(id);
		वापस;
	पूर्ण

	list_add_tail(&id->list, &pnp->ids);
	pnp->type.hardware_id = 1;
पूर्ण

/*
 * Old IBM workstations have a DSDT bug wherein the SMBus object
 * lacks the SMBUS01 HID and the methods करो not have the necessary "_"
 * prefix.  Work around this.
 */
अटल bool acpi_ibm_smbus_match(acpi_handle handle)
अणु
	अक्षर node_name[ACPI_PATH_SEGMENT_LENGTH];
	काष्ठा acpi_buffer path = अणु माप(node_name), node_name पूर्ण;

	अगर (!dmi_name_in_venकरोrs("IBM"))
		वापस false;

	/* Look क्रम SMBS object */
	अगर (ACPI_FAILURE(acpi_get_name(handle, ACPI_SINGLE_NAME, &path)) ||
	    म_भेद("SMBS", path.poपूर्णांकer))
		वापस false;

	/* Does it have the necessary (but misnamed) methods? */
	अगर (acpi_has_method(handle, "SBI") &&
	    acpi_has_method(handle, "SBR") &&
	    acpi_has_method(handle, "SBW"))
		वापस true;

	वापस false;
पूर्ण

अटल bool acpi_object_is_प्रणाली_bus(acpi_handle handle)
अणु
	acpi_handle पंचांगp;

	अगर (ACPI_SUCCESS(acpi_get_handle(शून्य, "\\_SB", &पंचांगp)) &&
	    पंचांगp == handle)
		वापस true;
	अगर (ACPI_SUCCESS(acpi_get_handle(शून्य, "\\_TZ", &पंचांगp)) &&
	    पंचांगp == handle)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम acpi_set_pnp_ids(acpi_handle handle, काष्ठा acpi_device_pnp *pnp,
			     पूर्णांक device_type)
अणु
	काष्ठा acpi_device_info *info = शून्य;
	काष्ठा acpi_pnp_device_id_list *cid_list;
	पूर्णांक i;

	चयन (device_type) अणु
	हाल ACPI_BUS_TYPE_DEVICE:
		अगर (handle == ACPI_ROOT_OBJECT) अणु
			acpi_add_id(pnp, ACPI_SYSTEM_HID);
			अवरोध;
		पूर्ण

		acpi_get_object_info(handle, &info);
		अगर (!info) अणु
			pr_err(PREFIX "%s: Error reading device info\n",
					__func__);
			वापस;
		पूर्ण

		अगर (info->valid & ACPI_VALID_HID) अणु
			acpi_add_id(pnp, info->hardware_id.string);
			pnp->type.platक्रमm_id = 1;
		पूर्ण
		अगर (info->valid & ACPI_VALID_CID) अणु
			cid_list = &info->compatible_id_list;
			क्रम (i = 0; i < cid_list->count; i++)
				acpi_add_id(pnp, cid_list->ids[i].string);
		पूर्ण
		अगर (info->valid & ACPI_VALID_ADR) अणु
			pnp->bus_address = info->address;
			pnp->type.bus_address = 1;
		पूर्ण
		अगर (info->valid & ACPI_VALID_UID)
			pnp->unique_id = kstrdup(info->unique_id.string,
							GFP_KERNEL);
		अगर (info->valid & ACPI_VALID_CLS)
			acpi_add_id(pnp, info->class_code.string);

		kमुक्त(info);

		/*
		 * Some devices करोn't reliably have _HIDs & _CIDs, so add
		 * synthetic HIDs to make sure drivers can find them.
		 */
		अगर (acpi_is_video_device(handle))
			acpi_add_id(pnp, ACPI_VIDEO_HID);
		अन्यथा अगर (acpi_bay_match(handle))
			acpi_add_id(pnp, ACPI_BAY_HID);
		अन्यथा अगर (acpi_करोck_match(handle))
			acpi_add_id(pnp, ACPI_DOCK_HID);
		अन्यथा अगर (acpi_ibm_smbus_match(handle))
			acpi_add_id(pnp, ACPI_SMBUS_IBM_HID);
		अन्यथा अगर (list_empty(&pnp->ids) &&
			 acpi_object_is_प्रणाली_bus(handle)) अणु
			/* \_SB, \_TZ, LNXSYBUS */
			acpi_add_id(pnp, ACPI_BUS_HID);
			म_नकल(pnp->device_name, ACPI_BUS_DEVICE_NAME);
			म_नकल(pnp->device_class, ACPI_BUS_CLASS);
		पूर्ण

		अवरोध;
	हाल ACPI_BUS_TYPE_POWER:
		acpi_add_id(pnp, ACPI_POWER_HID);
		अवरोध;
	हाल ACPI_BUS_TYPE_PROCESSOR:
		acpi_add_id(pnp, ACPI_PROCESSOR_OBJECT_HID);
		अवरोध;
	हाल ACPI_BUS_TYPE_THERMAL:
		acpi_add_id(pnp, ACPI_THERMAL_HID);
		अवरोध;
	हाल ACPI_BUS_TYPE_POWER_BUTTON:
		acpi_add_id(pnp, ACPI_BUTTON_HID_POWERF);
		अवरोध;
	हाल ACPI_BUS_TYPE_SLEEP_BUTTON:
		acpi_add_id(pnp, ACPI_BUTTON_HID_SLEEPF);
		अवरोध;
	हाल ACPI_BUS_TYPE_ECDT_EC:
		acpi_add_id(pnp, ACPI_ECDT_HID);
		अवरोध;
	पूर्ण
पूर्ण

व्योम acpi_मुक्त_pnp_ids(काष्ठा acpi_device_pnp *pnp)
अणु
	काष्ठा acpi_hardware_id *id, *पंचांगp;

	list_क्रम_each_entry_safe(id, पंचांगp, &pnp->ids, list) अणु
		kमुक्त_स्थिर(id->id);
		kमुक्त(id);
	पूर्ण
	kमुक्त(pnp->unique_id);
पूर्ण

/**
 * acpi_dma_supported - Check DMA support क्रम the specअगरied device.
 * @adev: The poपूर्णांकer to acpi device
 *
 * Return false अगर DMA is not supported. Otherwise, वापस true
 */
bool acpi_dma_supported(काष्ठा acpi_device *adev)
अणु
	अगर (!adev)
		वापस false;

	अगर (adev->flags.cca_seen)
		वापस true;

	/*
	* Per ACPI 6.0 sec 6.2.17, assume devices can करो cache-coherent
	* DMA on "Intel platforms".  Presumably that includes all x86 and
	* ia64, and other arches will set CONFIG_ACPI_CCA_REQUIRED=y.
	*/
	अगर (!IS_ENABLED(CONFIG_ACPI_CCA_REQUIRED))
		वापस true;

	वापस false;
पूर्ण

/**
 * acpi_get_dma_attr - Check the supported DMA attr क्रम the specअगरied device.
 * @adev: The poपूर्णांकer to acpi device
 *
 * Return क्रमागत dev_dma_attr.
 */
क्रमागत dev_dma_attr acpi_get_dma_attr(काष्ठा acpi_device *adev)
अणु
	अगर (!acpi_dma_supported(adev))
		वापस DEV_DMA_NOT_SUPPORTED;

	अगर (adev->flags.coherent_dma)
		वापस DEV_DMA_COHERENT;
	अन्यथा
		वापस DEV_DMA_NON_COHERENT;
पूर्ण

/**
 * acpi_dma_get_range() - Get device DMA parameters.
 *
 * @dev: device to configure
 * @dma_addr: poपूर्णांकer device DMA address result
 * @offset: poपूर्णांकer to the DMA offset result
 * @size: poपूर्णांकer to DMA range size result
 *
 * Evaluate DMA regions and वापस respectively DMA region start, offset
 * and size in dma_addr, offset and size on parsing success; it करोes not
 * update the passed in values on failure.
 *
 * Return 0 on success, < 0 on failure.
 */
पूर्णांक acpi_dma_get_range(काष्ठा device *dev, u64 *dma_addr, u64 *offset,
		       u64 *size)
अणु
	काष्ठा acpi_device *adev;
	LIST_HEAD(list);
	काष्ठा resource_entry *rentry;
	पूर्णांक ret;
	काष्ठा device *dma_dev = dev;
	u64 len, dma_start = U64_MAX, dma_end = 0, dma_offset = 0;

	/*
	 * Walk the device tree chasing an ACPI companion with a _DMA
	 * object जबतक we go. Stop अगर we find a device with an ACPI
	 * companion containing a _DMA method.
	 */
	करो अणु
		adev = ACPI_COMPANION(dma_dev);
		अगर (adev && acpi_has_method(adev->handle, METHOD_NAME__DMA))
			अवरोध;

		dma_dev = dma_dev->parent;
	पूर्ण जबतक (dma_dev);

	अगर (!dma_dev)
		वापस -ENODEV;

	अगर (!acpi_has_method(adev->handle, METHOD_NAME__CRS)) अणु
		acpi_handle_warn(adev->handle, "_DMA is valid only if _CRS is present\n");
		वापस -EINVAL;
	पूर्ण

	ret = acpi_dev_get_dma_resources(adev, &list);
	अगर (ret > 0) अणु
		list_क्रम_each_entry(rentry, &list, node) अणु
			अगर (dma_offset && rentry->offset != dma_offset) अणु
				ret = -EINVAL;
				dev_warn(dma_dev, "Can't handle multiple windows with different offsets\n");
				जाओ out;
			पूर्ण
			dma_offset = rentry->offset;

			/* Take lower and upper limits */
			अगर (rentry->res->start < dma_start)
				dma_start = rentry->res->start;
			अगर (rentry->res->end > dma_end)
				dma_end = rentry->res->end;
		पूर्ण

		अगर (dma_start >= dma_end) अणु
			ret = -EINVAL;
			dev_dbg(dma_dev, "Invalid DMA regions configuration\n");
			जाओ out;
		पूर्ण

		*dma_addr = dma_start - dma_offset;
		len = dma_end - dma_start;
		*size = max(len, len + 1);
		*offset = dma_offset;
	पूर्ण
 out:
	acpi_dev_मुक्त_resource_list(&list);

	वापस ret >= 0 ? 0 : ret;
पूर्ण

/**
 * acpi_dma_configure_id - Set-up DMA configuration क्रम the device.
 * @dev: The poपूर्णांकer to the device
 * @attr: device dma attributes
 * @input_id: input device id स्थिर value poपूर्णांकer
 */
पूर्णांक acpi_dma_configure_id(काष्ठा device *dev, क्रमागत dev_dma_attr attr,
			  स्थिर u32 *input_id)
अणु
	स्थिर काष्ठा iommu_ops *iommu;
	u64 dma_addr = 0, size = 0;

	अगर (attr == DEV_DMA_NOT_SUPPORTED) अणु
		set_dma_ops(dev, &dma_dummy_ops);
		वापस 0;
	पूर्ण

	iort_dma_setup(dev, &dma_addr, &size);

	iommu = iort_iommu_configure_id(dev, input_id);
	अगर (PTR_ERR(iommu) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	arch_setup_dma_ops(dev, dma_addr, size,
				iommu, attr == DEV_DMA_COHERENT);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dma_configure_id);

अटल व्योम acpi_init_coherency(काष्ठा acpi_device *adev)
अणु
	अचिन्हित दीर्घ दीर्घ cca = 0;
	acpi_status status;
	काष्ठा acpi_device *parent = adev->parent;

	अगर (parent && parent->flags.cca_seen) अणु
		/*
		 * From ACPI spec, OSPM will ignore _CCA अगर an ancestor
		 * alपढ़ोy saw one.
		 */
		adev->flags.cca_seen = 1;
		cca = parent->flags.coherent_dma;
	पूर्ण अन्यथा अणु
		status = acpi_evaluate_पूर्णांकeger(adev->handle, "_CCA",
					       शून्य, &cca);
		अगर (ACPI_SUCCESS(status))
			adev->flags.cca_seen = 1;
		अन्यथा अगर (!IS_ENABLED(CONFIG_ACPI_CCA_REQUIRED))
			/*
			 * If architecture करोes not specअगरy that _CCA is
			 * required क्रम DMA-able devices (e.g. x86),
			 * we शेष to _CCA=1.
			 */
			cca = 1;
		अन्यथा
			acpi_handle_debug(adev->handle,
					  "ACPI device is missing _CCA.\n");
	पूर्ण

	adev->flags.coherent_dma = cca;
पूर्ण

अटल पूर्णांक acpi_check_serial_bus_slave(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	bool *is_serial_bus_slave_p = data;

	अगर (ares->type != ACPI_RESOURCE_TYPE_SERIAL_BUS)
		वापस 1;

	*is_serial_bus_slave_p = true;

	 /* no need to करो more checking */
	वापस -1;
पूर्ण

अटल bool acpi_is_indirect_io_slave(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_device *parent = device->parent;
	अटल स्थिर काष्ठा acpi_device_id indirect_io_hosts[] = अणु
		अणु"HISI0191", 0पूर्ण,
		अणुपूर्ण
	पूर्ण;

	वापस parent && !acpi_match_device_ids(parent, indirect_io_hosts);
पूर्ण

अटल bool acpi_device_क्रमागतeration_by_parent(काष्ठा acpi_device *device)
अणु
	काष्ठा list_head resource_list;
	bool is_serial_bus_slave = false;
	/*
	 * These devices have multiple I2cSerialBus resources and an i2c-client
	 * must be instantiated क्रम each, each with its own i2c_device_id.
	 * Normally we only instantiate an i2c-client क्रम the first resource,
	 * using the ACPI HID as id. These special हालs are handled by the
	 * drivers/platक्रमm/x86/i2c-multi-instantiate.c driver, which knows
	 * which i2c_device_id to use क्रम each resource.
	 */
	अटल स्थिर काष्ठा acpi_device_id i2c_multi_instantiate_ids[] = अणु
		अणु"BSG1160", पूर्ण,
		अणु"BSG2150", पूर्ण,
		अणु"INT33FE", पूर्ण,
		अणु"INT3515", पूर्ण,
		अणुपूर्ण
	पूर्ण;

	अगर (acpi_is_indirect_io_slave(device))
		वापस true;

	/* Macs use device properties in lieu of _CRS resources */
	अगर (x86_apple_machine &&
	    (fwnode_property_present(&device->fwnode, "spiSclkPeriod") ||
	     fwnode_property_present(&device->fwnode, "i2cAddress") ||
	     fwnode_property_present(&device->fwnode, "baud")))
		वापस true;

	/* Instantiate a pdev क्रम the i2c-multi-instantiate drv to bind to */
	अगर (!acpi_match_device_ids(device, i2c_multi_instantiate_ids))
		वापस false;

	INIT_LIST_HEAD(&resource_list);
	acpi_dev_get_resources(device, &resource_list,
			       acpi_check_serial_bus_slave,
			       &is_serial_bus_slave);
	acpi_dev_मुक्त_resource_list(&resource_list);

	वापस is_serial_bus_slave;
पूर्ण

व्योम acpi_init_device_object(काष्ठा acpi_device *device, acpi_handle handle,
			     पूर्णांक type)
अणु
	INIT_LIST_HEAD(&device->pnp.ids);
	device->device_type = type;
	device->handle = handle;
	device->parent = acpi_bus_get_parent(handle);
	fwnode_init(&device->fwnode, &acpi_device_fwnode_ops);
	acpi_set_device_status(device, ACPI_STA_DEFAULT);
	acpi_device_get_busid(device);
	acpi_set_pnp_ids(handle, &device->pnp, type);
	acpi_init_properties(device);
	acpi_bus_get_flags(device);
	device->flags.match_driver = false;
	device->flags.initialized = true;
	device->flags.क्रमागतeration_by_parent =
		acpi_device_क्रमागतeration_by_parent(device);
	acpi_device_clear_क्रमागतerated(device);
	device_initialize(&device->dev);
	dev_set_uevent_suppress(&device->dev, true);
	acpi_init_coherency(device);
	/* Assume there are unmet deps to start with. */
	device->dep_unmet = 1;
पूर्ण

व्योम acpi_device_add_finalize(काष्ठा acpi_device *device)
अणु
	dev_set_uevent_suppress(&device->dev, false);
	kobject_uevent(&device->dev.kobj, KOBJ_ADD);
पूर्ण

अटल व्योम acpi_scan_init_status(काष्ठा acpi_device *adev)
अणु
	अगर (acpi_bus_get_status(adev))
		acpi_set_device_status(adev, 0);
पूर्ण

अटल पूर्णांक acpi_add_single_object(काष्ठा acpi_device **child,
				  acpi_handle handle, पूर्णांक type)
अणु
	काष्ठा acpi_device *device;
	पूर्णांक result;

	device = kzalloc(माप(काष्ठा acpi_device), GFP_KERNEL);
	अगर (!device)
		वापस -ENOMEM;

	acpi_init_device_object(device, handle, type);
	/*
	 * Getting the status is delayed till here so that we can call
	 * acpi_bus_get_status() and use its quirk handling.  Note that
	 * this must be करोne beक्रमe the get घातer-/wakeup_dev-flags calls.
	 */
	अगर (type == ACPI_BUS_TYPE_DEVICE || type == ACPI_BUS_TYPE_PROCESSOR)
		acpi_scan_init_status(device);

	acpi_bus_get_घातer_flags(device);
	acpi_bus_get_wakeup_device_flags(device);

	result = acpi_device_add(device, acpi_device_release);
	अगर (result) अणु
		acpi_device_release(&device->dev);
		वापस result;
	पूर्ण

	acpi_घातer_add_हटाओ_device(device, true);
	acpi_device_add_finalize(device);

	acpi_handle_debug(handle, "Added as %s, parent %s\n",
			  dev_name(&device->dev), device->parent ?
				dev_name(&device->parent->dev) : "(null)");

	*child = device;
	वापस 0;
पूर्ण

अटल acpi_status acpi_get_resource_memory(काष्ठा acpi_resource *ares,
					    व्योम *context)
अणु
	काष्ठा resource *res = context;

	अगर (acpi_dev_resource_memory(ares, res))
		वापस AE_CTRL_TERMINATE;

	वापस AE_OK;
पूर्ण

अटल bool acpi_device_should_be_hidden(acpi_handle handle)
अणु
	acpi_status status;
	काष्ठा resource res;

	/* Check अगर it should ignore the UART device */
	अगर (!(spcr_uart_addr && acpi_has_method(handle, METHOD_NAME__CRS)))
		वापस false;

	/*
	 * The UART device described in SPCR table is assumed to have only one
	 * memory resource present. So we only look क्रम the first one here.
	 */
	status = acpi_walk_resources(handle, METHOD_NAME__CRS,
				     acpi_get_resource_memory, &res);
	अगर (ACPI_FAILURE(status) || res.start != spcr_uart_addr)
		वापस false;

	acpi_handle_info(handle, "The UART device @%pa in SPCR table will be hidden\n",
			 &res.start);

	वापस true;
पूर्ण

bool acpi_device_is_present(स्थिर काष्ठा acpi_device *adev)
अणु
	वापस adev->status.present || adev->status.functional;
पूर्ण

अटल bool acpi_scan_handler_matching(काष्ठा acpi_scan_handler *handler,
				       स्थिर अक्षर *idstr,
				       स्थिर काष्ठा acpi_device_id **matchid)
अणु
	स्थिर काष्ठा acpi_device_id *devid;

	अगर (handler->match)
		वापस handler->match(idstr, matchid);

	क्रम (devid = handler->ids; devid->id[0]; devid++)
		अगर (!म_भेद((अक्षर *)devid->id, idstr)) अणु
			अगर (matchid)
				*matchid = devid;

			वापस true;
		पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा acpi_scan_handler *acpi_scan_match_handler(स्थिर अक्षर *idstr,
					स्थिर काष्ठा acpi_device_id **matchid)
अणु
	काष्ठा acpi_scan_handler *handler;

	list_क्रम_each_entry(handler, &acpi_scan_handlers_list, list_node)
		अगर (acpi_scan_handler_matching(handler, idstr, matchid))
			वापस handler;

	वापस शून्य;
पूर्ण

व्योम acpi_scan_hotplug_enabled(काष्ठा acpi_hotplug_profile *hotplug, bool val)
अणु
	अगर (!!hotplug->enabled == !!val)
		वापस;

	mutex_lock(&acpi_scan_lock);

	hotplug->enabled = val;

	mutex_unlock(&acpi_scan_lock);
पूर्ण

अटल व्योम acpi_scan_init_hotplug(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_hardware_id *hwid;

	अगर (acpi_करोck_match(adev->handle) || is_ejectable_bay(adev)) अणु
		acpi_करोck_add(adev);
		वापस;
	पूर्ण
	list_क्रम_each_entry(hwid, &adev->pnp.ids, list) अणु
		काष्ठा acpi_scan_handler *handler;

		handler = acpi_scan_match_handler(hwid->id, शून्य);
		अगर (handler) अणु
			adev->flags.hotplug_notअगरy = true;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल u32 acpi_scan_check_dep(acpi_handle handle, bool check_dep)
अणु
	काष्ठा acpi_handle_list dep_devices;
	acpi_status status;
	u32 count;
	पूर्णांक i;

	/*
	 * Check क्रम _HID here to aव्योम deferring the क्रमागतeration of:
	 * 1. PCI devices.
	 * 2. ACPI nodes describing USB ports.
	 * Still, checking क्रम _HID catches more then just these हालs ...
	 */
	अगर (!check_dep || !acpi_has_method(handle, "_DEP") ||
	    !acpi_has_method(handle, "_HID"))
		वापस 0;

	status = acpi_evaluate_reference(handle, "_DEP", शून्य, &dep_devices);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_debug(handle, "Failed to evaluate _DEP.\n");
		वापस 0;
	पूर्ण

	क्रम (count = 0, i = 0; i < dep_devices.count; i++) अणु
		काष्ठा acpi_device_info *info;
		काष्ठा acpi_dep_data *dep;
		bool skip;

		status = acpi_get_object_info(dep_devices.handles[i], &info);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_debug(handle, "Error reading _DEP device info\n");
			जारी;
		पूर्ण

		skip = acpi_info_matches_ids(info, acpi_ignore_dep_ids);
		kमुक्त(info);

		अगर (skip)
			जारी;

		dep = kzalloc(माप(*dep), GFP_KERNEL);
		अगर (!dep)
			जारी;

		count++;

		dep->supplier = dep_devices.handles[i];
		dep->consumer = handle;

		mutex_lock(&acpi_dep_list_lock);
		list_add_tail(&dep->node , &acpi_dep_list);
		mutex_unlock(&acpi_dep_list_lock);
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम acpi_scan_dep_init(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_dep_data *dep;

	adev->dep_unmet = 0;

	mutex_lock(&acpi_dep_list_lock);

	list_क्रम_each_entry(dep, &acpi_dep_list, node) अणु
		अगर (dep->consumer == adev->handle)
			adev->dep_unmet++;
	पूर्ण

	mutex_unlock(&acpi_dep_list_lock);
पूर्ण

अटल bool acpi_bus_scan_second_pass;

अटल acpi_status acpi_bus_check_add(acpi_handle handle, bool check_dep,
				      काष्ठा acpi_device **adev_p)
अणु
	काष्ठा acpi_device *device = शून्य;
	acpi_object_type acpi_type;
	पूर्णांक type;

	acpi_bus_get_device(handle, &device);
	अगर (device)
		जाओ out;

	अगर (ACPI_FAILURE(acpi_get_type(handle, &acpi_type)))
		वापस AE_OK;

	चयन (acpi_type) अणु
	हाल ACPI_TYPE_DEVICE:
		अगर (acpi_device_should_be_hidden(handle))
			वापस AE_OK;

		/* Bail out अगर there are dependencies. */
		अगर (acpi_scan_check_dep(handle, check_dep) > 0) अणु
			acpi_bus_scan_second_pass = true;
			वापस AE_CTRL_DEPTH;
		पूर्ण

		fallthrough;
	हाल ACPI_TYPE_ANY:	/* क्रम ACPI_ROOT_OBJECT */
		type = ACPI_BUS_TYPE_DEVICE;
		अवरोध;

	हाल ACPI_TYPE_PROCESSOR:
		type = ACPI_BUS_TYPE_PROCESSOR;
		अवरोध;

	हाल ACPI_TYPE_THERMAL:
		type = ACPI_BUS_TYPE_THERMAL;
		अवरोध;

	हाल ACPI_TYPE_POWER:
		acpi_add_घातer_resource(handle);
		fallthrough;
	शेष:
		वापस AE_OK;
	पूर्ण

	acpi_add_single_object(&device, handle, type);
	अगर (!device)
		वापस AE_CTRL_DEPTH;

	acpi_scan_init_hotplug(device);
	/*
	 * If check_dep is true at this poपूर्णांक, the device has no dependencies,
	 * or the creation of the device object would have been postponed above.
	 */
	अगर (check_dep)
		device->dep_unmet = 0;
	अन्यथा
		acpi_scan_dep_init(device);

out:
	अगर (!*adev_p)
		*adev_p = device;

	वापस AE_OK;
पूर्ण

अटल acpi_status acpi_bus_check_add_1(acpi_handle handle, u32 lvl_not_used,
					व्योम *not_used, व्योम **ret_p)
अणु
	वापस acpi_bus_check_add(handle, true, (काष्ठा acpi_device **)ret_p);
पूर्ण

अटल acpi_status acpi_bus_check_add_2(acpi_handle handle, u32 lvl_not_used,
					व्योम *not_used, व्योम **ret_p)
अणु
	वापस acpi_bus_check_add(handle, false, (काष्ठा acpi_device **)ret_p);
पूर्ण

अटल व्योम acpi_शेष_क्रमागतeration(काष्ठा acpi_device *device)
अणु
	/*
	 * Do not क्रमागतerate devices with क्रमागतeration_by_parent flag set as
	 * they will be क्रमागतerated by their respective parents.
	 */
	अगर (!device->flags.क्रमागतeration_by_parent) अणु
		acpi_create_platक्रमm_device(device, शून्य);
		acpi_device_set_क्रमागतerated(device);
	पूर्ण अन्यथा अणु
		blocking_notअगरier_call_chain(&acpi_reconfig_chain,
					     ACPI_RECONFIG_DEVICE_ADD, device);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा acpi_device_id generic_device_ids[] = अणु
	अणुACPI_DT_NAMESPACE_HID, पूर्ण,
	अणु"", पूर्ण,
पूर्ण;

अटल पूर्णांक acpi_generic_device_attach(काष्ठा acpi_device *adev,
				      स्थिर काष्ठा acpi_device_id *not_used)
अणु
	/*
	 * Since ACPI_DT_NAMESPACE_HID is the only ID handled here, the test
	 * below can be unconditional.
	 */
	अगर (adev->data.of_compatible)
		acpi_शेष_क्रमागतeration(adev);

	वापस 1;
पूर्ण

अटल काष्ठा acpi_scan_handler generic_device_handler = अणु
	.ids = generic_device_ids,
	.attach = acpi_generic_device_attach,
पूर्ण;

अटल पूर्णांक acpi_scan_attach_handler(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_hardware_id *hwid;
	पूर्णांक ret = 0;

	list_क्रम_each_entry(hwid, &device->pnp.ids, list) अणु
		स्थिर काष्ठा acpi_device_id *devid;
		काष्ठा acpi_scan_handler *handler;

		handler = acpi_scan_match_handler(hwid->id, &devid);
		अगर (handler) अणु
			अगर (!handler->attach) अणु
				device->pnp.type.platक्रमm_id = 0;
				जारी;
			पूर्ण
			device->handler = handler;
			ret = handler->attach(device, devid);
			अगर (ret > 0)
				अवरोध;

			device->handler = शून्य;
			अगर (ret < 0)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम acpi_bus_attach(काष्ठा acpi_device *device, bool first_pass)
अणु
	काष्ठा acpi_device *child;
	bool skip = !first_pass && device->flags.visited;
	acpi_handle ejd;
	पूर्णांक ret;

	अगर (skip)
		जाओ ok;

	अगर (ACPI_SUCCESS(acpi_bus_get_ejd(device->handle, &ejd)))
		रेजिस्टर_करोck_dependent_device(device, ejd);

	acpi_bus_get_status(device);
	/* Skip devices that are not present. */
	अगर (!acpi_device_is_present(device)) अणु
		device->flags.initialized = false;
		acpi_device_clear_क्रमागतerated(device);
		device->flags.घातer_manageable = 0;
		वापस;
	पूर्ण
	अगर (device->handler)
		जाओ ok;

	अगर (!device->flags.initialized) अणु
		device->flags.घातer_manageable =
			device->घातer.states[ACPI_STATE_D0].flags.valid;
		अगर (acpi_bus_init_घातer(device))
			device->flags.घातer_manageable = 0;

		device->flags.initialized = true;
	पूर्ण अन्यथा अगर (device->flags.visited) अणु
		जाओ ok;
	पूर्ण

	ret = acpi_scan_attach_handler(device);
	अगर (ret < 0)
		वापस;

	device->flags.match_driver = true;
	अगर (ret > 0 && !device->flags.क्रमागतeration_by_parent) अणु
		acpi_device_set_क्रमागतerated(device);
		जाओ ok;
	पूर्ण

	ret = device_attach(&device->dev);
	अगर (ret < 0)
		वापस;

	अगर (device->pnp.type.platक्रमm_id || device->flags.क्रमागतeration_by_parent)
		acpi_शेष_क्रमागतeration(device);
	अन्यथा
		acpi_device_set_क्रमागतerated(device);

 ok:
	list_क्रम_each_entry(child, &device->children, node)
		acpi_bus_attach(child, first_pass);

	अगर (!skip && device->handler && device->handler->hotplug.notअगरy_online)
		device->handler->hotplug.notअगरy_online(device);
पूर्ण

व्योम acpi_walk_dep_device_list(acpi_handle handle)
अणु
	काष्ठा acpi_dep_data *dep, *पंचांगp;
	काष्ठा acpi_device *adev;

	mutex_lock(&acpi_dep_list_lock);
	list_क्रम_each_entry_safe(dep, पंचांगp, &acpi_dep_list, node) अणु
		अगर (dep->supplier == handle) अणु
			acpi_bus_get_device(dep->consumer, &adev);

			अगर (adev) अणु
				adev->dep_unmet--;
				अगर (!adev->dep_unmet)
					acpi_bus_attach(adev, true);
			पूर्ण

			list_del(&dep->node);
			kमुक्त(dep);
		पूर्ण
	पूर्ण
	mutex_unlock(&acpi_dep_list_lock);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_walk_dep_device_list);

/**
 * acpi_bus_scan - Add ACPI device node objects in a given namespace scope.
 * @handle: Root of the namespace scope to scan.
 *
 * Scan a given ACPI tree (probably recently hot-plugged) and create and add
 * found devices.
 *
 * If no devices were found, -ENODEV is वापसed, but it करोes not mean that
 * there has been a real error.  There just have been no suitable ACPI objects
 * in the table trunk from which the kernel could create a device and add an
 * appropriate driver.
 *
 * Must be called under acpi_scan_lock.
 */
पूर्णांक acpi_bus_scan(acpi_handle handle)
अणु
	काष्ठा acpi_device *device = शून्य;

	acpi_bus_scan_second_pass = false;

	/* Pass 1: Aव्योम क्रमागतerating devices with missing dependencies. */

	अगर (ACPI_SUCCESS(acpi_bus_check_add(handle, true, &device)))
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    acpi_bus_check_add_1, शून्य, शून्य,
				    (व्योम **)&device);

	अगर (!device)
		वापस -ENODEV;

	acpi_bus_attach(device, true);

	अगर (!acpi_bus_scan_second_pass)
		वापस 0;

	/* Pass 2: Enumerate all of the reमुख्यing devices. */

	device = शून्य;

	अगर (ACPI_SUCCESS(acpi_bus_check_add(handle, false, &device)))
		acpi_walk_namespace(ACPI_TYPE_ANY, handle, ACPI_UINT32_MAX,
				    acpi_bus_check_add_2, शून्य, शून्य,
				    (व्योम **)&device);

	acpi_bus_attach(device, false);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_bus_scan);

/**
 * acpi_bus_trim - Detach scan handlers and drivers from ACPI device objects.
 * @adev: Root of the ACPI namespace scope to walk.
 *
 * Must be called under acpi_scan_lock.
 */
व्योम acpi_bus_trim(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_scan_handler *handler = adev->handler;
	काष्ठा acpi_device *child;

	list_क्रम_each_entry_reverse(child, &adev->children, node)
		acpi_bus_trim(child);

	adev->flags.match_driver = false;
	अगर (handler) अणु
		अगर (handler->detach)
			handler->detach(adev);

		adev->handler = शून्य;
	पूर्ण अन्यथा अणु
		device_release_driver(&adev->dev);
	पूर्ण
	/*
	 * Most likely, the device is going away, so put it पूर्णांकo D3cold beक्रमe
	 * that.
	 */
	acpi_device_set_घातer(adev, ACPI_STATE_D3_COLD);
	adev->flags.initialized = false;
	acpi_device_clear_क्रमागतerated(adev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_trim);

पूर्णांक acpi_bus_रेजिस्टर_early_device(पूर्णांक type)
अणु
	काष्ठा acpi_device *device = शून्य;
	पूर्णांक result;

	result = acpi_add_single_object(&device, शून्य, type);
	अगर (result)
		वापस result;

	device->flags.match_driver = true;
	वापस device_attach(&device->dev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_रेजिस्टर_early_device);

अटल पूर्णांक acpi_bus_scan_fixed(व्योम)
अणु
	पूर्णांक result = 0;

	/*
	 * Enumerate all fixed-feature devices.
	 */
	अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_POWER_BUTTON)) अणु
		काष्ठा acpi_device *device = शून्य;

		result = acpi_add_single_object(&device, शून्य,
						ACPI_BUS_TYPE_POWER_BUTTON);
		अगर (result)
			वापस result;

		device->flags.match_driver = true;
		result = device_attach(&device->dev);
		अगर (result < 0)
			वापस result;

		device_init_wakeup(&device->dev, true);
	पूर्ण

	अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_SLEEP_BUTTON)) अणु
		काष्ठा acpi_device *device = शून्य;

		result = acpi_add_single_object(&device, शून्य,
						ACPI_BUS_TYPE_SLEEP_BUTTON);
		अगर (result)
			वापस result;

		device->flags.match_driver = true;
		result = device_attach(&device->dev);
	पूर्ण

	वापस result < 0 ? result : 0;
पूर्ण

अटल व्योम __init acpi_get_spcr_uart_addr(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_table_spcr *spcr_ptr;

	status = acpi_get_table(ACPI_SIG_SPCR, 0,
				(काष्ठा acpi_table_header **)&spcr_ptr);
	अगर (ACPI_FAILURE(status)) अणु
		pr_warn(PREFIX "STAO table present, but SPCR is missing\n");
		वापस;
	पूर्ण

	spcr_uart_addr = spcr_ptr->serial_port.address;
	acpi_put_table((काष्ठा acpi_table_header *)spcr_ptr);
पूर्ण

अटल bool acpi_scan_initialized;

पूर्णांक __init acpi_scan_init(व्योम)
अणु
	पूर्णांक result;
	acpi_status status;
	काष्ठा acpi_table_stao *stao_ptr;

	acpi_pci_root_init();
	acpi_pci_link_init();
	acpi_processor_init();
	acpi_platक्रमm_init();
	acpi_lpss_init();
	acpi_apd_init();
	acpi_cmos_rtc_init();
	acpi_container_init();
	acpi_memory_hotplug_init();
	acpi_watchकरोg_init();
	acpi_pnp_init();
	acpi_पूर्णांक340x_thermal_init();
	acpi_amba_init();
	acpi_init_lpit();

	acpi_scan_add_handler(&generic_device_handler);

	/*
	 * If there is STAO table, check whether it needs to ignore the UART
	 * device in SPCR table.
	 */
	status = acpi_get_table(ACPI_SIG_STAO, 0,
				(काष्ठा acpi_table_header **)&stao_ptr);
	अगर (ACPI_SUCCESS(status)) अणु
		अगर (stao_ptr->header.length > माप(काष्ठा acpi_table_stao))
			pr_info(PREFIX "STAO Name List not yet supported.\n");

		अगर (stao_ptr->ignore_uart)
			acpi_get_spcr_uart_addr();

		acpi_put_table((काष्ठा acpi_table_header *)stao_ptr);
	पूर्ण

	acpi_gpe_apply_masked_gpes();
	acpi_update_all_gpes();

	/*
	 * Although we call __add_memory() that is करोcumented to require the
	 * device_hotplug_lock, it is not necessary here because this is an
	 * early code when userspace or any other code path cannot trigger
	 * hotplug/hotunplug operations.
	 */
	mutex_lock(&acpi_scan_lock);
	/*
	 * Enumerate devices in the ACPI namespace.
	 */
	result = acpi_bus_scan(ACPI_ROOT_OBJECT);
	अगर (result)
		जाओ out;

	result = acpi_bus_get_device(ACPI_ROOT_OBJECT, &acpi_root);
	अगर (result)
		जाओ out;

	/* Fixed feature devices करो not exist on HW-reduced platक्रमm */
	अगर (!acpi_gbl_reduced_hardware) अणु
		result = acpi_bus_scan_fixed();
		अगर (result) अणु
			acpi_detach_data(acpi_root->handle,
					 acpi_scan_drop_device);
			acpi_device_del(acpi_root);
			acpi_bus_put_acpi_device(acpi_root);
			जाओ out;
		पूर्ण
	पूर्ण

	acpi_turn_off_unused_घातer_resources(true);

	acpi_scan_initialized = true;

 out:
	mutex_unlock(&acpi_scan_lock);
	वापस result;
पूर्ण

अटल काष्ठा acpi_probe_entry *ape;
अटल पूर्णांक acpi_probe_count;
अटल DEFINE_MUTEX(acpi_probe_mutex);

अटल पूर्णांक __init acpi_match_madt(जोड़ acpi_subtable_headers *header,
				  स्थिर अचिन्हित दीर्घ end)
अणु
	अगर (!ape->subtable_valid || ape->subtable_valid(&header->common, ape))
		अगर (!ape->probe_subtbl(header, end))
			acpi_probe_count++;

	वापस 0;
पूर्ण

पूर्णांक __init __acpi_probe_device_table(काष्ठा acpi_probe_entry *ap_head, पूर्णांक nr)
अणु
	पूर्णांक count = 0;

	अगर (acpi_disabled)
		वापस 0;

	mutex_lock(&acpi_probe_mutex);
	क्रम (ape = ap_head; nr; ape++, nr--) अणु
		अगर (ACPI_COMPARE_NAMESEG(ACPI_SIG_MADT, ape->id)) अणु
			acpi_probe_count = 0;
			acpi_table_parse_madt(ape->type, acpi_match_madt, 0);
			count += acpi_probe_count;
		पूर्ण अन्यथा अणु
			पूर्णांक res;
			res = acpi_table_parse(ape->id, ape->probe_table);
			अगर (!res)
				count++;
		पूर्ण
	पूर्ण
	mutex_unlock(&acpi_probe_mutex);

	वापस count;
पूर्ण

काष्ठा acpi_table_events_work अणु
	काष्ठा work_काष्ठा work;
	व्योम *table;
	u32 event;
पूर्ण;

अटल व्योम acpi_table_events_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_table_events_work *tew;

	tew = container_of(work, काष्ठा acpi_table_events_work, work);

	अगर (tew->event == ACPI_TABLE_EVENT_LOAD) अणु
		acpi_scan_lock_acquire();
		acpi_bus_scan(ACPI_ROOT_OBJECT);
		acpi_scan_lock_release();
	पूर्ण

	kमुक्त(tew);
पूर्ण

व्योम acpi_scan_table_handler(u32 event, व्योम *table, व्योम *context)
अणु
	काष्ठा acpi_table_events_work *tew;

	अगर (!acpi_scan_initialized)
		वापस;

	अगर (event != ACPI_TABLE_EVENT_LOAD)
		वापस;

	tew = kदो_स्मृति(माप(*tew), GFP_KERNEL);
	अगर (!tew)
		वापस;

	INIT_WORK(&tew->work, acpi_table_events_fn);
	tew->table = table;
	tew->event = event;

	schedule_work(&tew->work);
पूर्ण

पूर्णांक acpi_reconfig_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&acpi_reconfig_chain, nb);
पूर्ण
EXPORT_SYMBOL(acpi_reconfig_notअगरier_रेजिस्टर);

पूर्णांक acpi_reconfig_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&acpi_reconfig_chain, nb);
पूर्ण
EXPORT_SYMBOL(acpi_reconfig_notअगरier_unरेजिस्टर);
