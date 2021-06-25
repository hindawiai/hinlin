<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drivers/acpi/घातer.c - ACPI Power Resources management.
 *
 * Copyright (C) 2001 - 2015 Intel Corp.
 * Author: Andy Grover <andrew.grover@पूर्णांकel.com>
 * Author: Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 */

/*
 * ACPI घातer-managed devices may be controlled in two ways:
 * 1. via "Device Specific (D-State) Control"
 * 2. via "Power Resource Control".
 * The code below deals with ACPI Power Resources control.
 *
 * An ACPI "power resource object" represents a software controllable घातer
 * plane, घड़ी plane, or other resource depended on by a device.
 *
 * A device may rely on multiple घातer resources, and a घातer resource
 * may be shared by multiple devices.
 */

#घोषणा pr_fmt(fmt) "ACPI: PM: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/acpi.h>
#समावेश "sleep.h"
#समावेश "internal.h"

#घोषणा ACPI_POWER_CLASS		"power_resource"
#घोषणा ACPI_POWER_DEVICE_NAME		"Power Resource"
#घोषणा ACPI_POWER_RESOURCE_STATE_OFF	0x00
#घोषणा ACPI_POWER_RESOURCE_STATE_ON	0x01
#घोषणा ACPI_POWER_RESOURCE_STATE_UNKNOWN 0xFF

काष्ठा acpi_घातer_dependent_device अणु
	काष्ठा device *dev;
	काष्ठा list_head node;
पूर्ण;

काष्ठा acpi_घातer_resource अणु
	काष्ठा acpi_device device;
	काष्ठा list_head list_node;
	अक्षर *name;
	u32 प्रणाली_level;
	u32 order;
	अचिन्हित पूर्णांक ref_count;
	अचिन्हित पूर्णांक users;
	bool wakeup_enabled;
	काष्ठा mutex resource_lock;
	काष्ठा list_head dependents;
पूर्ण;

काष्ठा acpi_घातer_resource_entry अणु
	काष्ठा list_head node;
	काष्ठा acpi_घातer_resource *resource;
पूर्ण;

अटल LIST_HEAD(acpi_घातer_resource_list);
अटल DEFINE_MUTEX(घातer_resource_list_lock);

/* --------------------------------------------------------------------------
                             Power Resource Management
   -------------------------------------------------------------------------- */

अटल अंतरभूत
काष्ठा acpi_घातer_resource *to_घातer_resource(काष्ठा acpi_device *device)
अणु
	वापस container_of(device, काष्ठा acpi_घातer_resource, device);
पूर्ण

अटल काष्ठा acpi_घातer_resource *acpi_घातer_get_context(acpi_handle handle)
अणु
	काष्ठा acpi_device *device;

	अगर (acpi_bus_get_device(handle, &device))
		वापस शून्य;

	वापस to_घातer_resource(device);
पूर्ण

अटल पूर्णांक acpi_घातer_resources_list_add(acpi_handle handle,
					 काष्ठा list_head *list)
अणु
	काष्ठा acpi_घातer_resource *resource = acpi_घातer_get_context(handle);
	काष्ठा acpi_घातer_resource_entry *entry;

	अगर (!resource || !list)
		वापस -EINVAL;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->resource = resource;
	अगर (!list_empty(list)) अणु
		काष्ठा acpi_घातer_resource_entry *e;

		list_क्रम_each_entry(e, list, node)
			अगर (e->resource->order > resource->order) अणु
				list_add_tail(&entry->node, &e->node);
				वापस 0;
			पूर्ण
	पूर्ण
	list_add_tail(&entry->node, list);
	वापस 0;
पूर्ण

व्योम acpi_घातer_resources_list_मुक्त(काष्ठा list_head *list)
अणु
	काष्ठा acpi_घातer_resource_entry *entry, *e;

	list_क्रम_each_entry_safe(entry, e, list, node) अणु
		list_del(&entry->node);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल bool acpi_घातer_resource_is_dup(जोड़ acpi_object *package,
				       अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक i)
अणु
	acpi_handle rhandle, dup;
	अचिन्हित पूर्णांक j;

	/* The caller is expected to check the package element types */
	rhandle = package->package.elements[i].reference.handle;
	क्रम (j = start; j < i; j++) अणु
		dup = package->package.elements[j].reference.handle;
		अगर (dup == rhandle)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

पूर्णांक acpi_extract_घातer_resources(जोड़ acpi_object *package, अचिन्हित पूर्णांक start,
				 काष्ठा list_head *list)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = start; i < package->package.count; i++) अणु
		जोड़ acpi_object *element = &package->package.elements[i];
		काष्ठा acpi_device *rdev;
		acpi_handle rhandle;

		अगर (element->type != ACPI_TYPE_LOCAL_REFERENCE) अणु
			err = -ENODATA;
			अवरोध;
		पूर्ण
		rhandle = element->reference.handle;
		अगर (!rhandle) अणु
			err = -ENODEV;
			अवरोध;
		पूर्ण

		/* Some ACPI tables contain duplicate घातer resource references */
		अगर (acpi_घातer_resource_is_dup(package, start, i))
			जारी;

		rdev = acpi_add_घातer_resource(rhandle);
		अगर (!rdev) अणु
			err = -ENODEV;
			अवरोध;
		पूर्ण
		err = acpi_घातer_resources_list_add(rhandle, list);
		अगर (err)
			अवरोध;

		to_घातer_resource(rdev)->users++;
	पूर्ण
	अगर (err)
		acpi_घातer_resources_list_मुक्त(list);

	वापस err;
पूर्ण

अटल पूर्णांक acpi_घातer_get_state(acpi_handle handle, पूर्णांक *state)
अणु
	acpi_status status = AE_OK;
	अचिन्हित दीर्घ दीर्घ sta = 0;

	अगर (!handle || !state)
		वापस -EINVAL;

	status = acpi_evaluate_पूर्णांकeger(handle, "_STA", शून्य, &sta);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	*state = (sta & 0x01)?ACPI_POWER_RESOURCE_STATE_ON:
			      ACPI_POWER_RESOURCE_STATE_OFF;

	acpi_handle_debug(handle, "Power resource is %s\n",
			  *state ? "on" : "off");

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_घातer_get_list_state(काष्ठा list_head *list, पूर्णांक *state)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	पूर्णांक cur_state;

	अगर (!list || !state)
		वापस -EINVAL;

	/* The state of the list is 'on' IFF all resources are 'on'. */
	cur_state = 0;
	list_क्रम_each_entry(entry, list, node) अणु
		काष्ठा acpi_घातer_resource *resource = entry->resource;
		acpi_handle handle = resource->device.handle;
		पूर्णांक result;

		mutex_lock(&resource->resource_lock);
		result = acpi_घातer_get_state(handle, &cur_state);
		mutex_unlock(&resource->resource_lock);
		अगर (result)
			वापस result;

		अगर (cur_state != ACPI_POWER_RESOURCE_STATE_ON)
			अवरोध;
	पूर्ण

	pr_debug("Power resource list is %s\n", cur_state ? "on" : "off");

	*state = cur_state;
	वापस 0;
पूर्ण

अटल पूर्णांक
acpi_घातer_resource_add_dependent(काष्ठा acpi_घातer_resource *resource,
				  काष्ठा device *dev)
अणु
	काष्ठा acpi_घातer_dependent_device *dep;
	पूर्णांक ret = 0;

	mutex_lock(&resource->resource_lock);
	list_क्रम_each_entry(dep, &resource->dependents, node) अणु
		/* Only add it once */
		अगर (dep->dev == dev)
			जाओ unlock;
	पूर्ण

	dep = kzalloc(माप(*dep), GFP_KERNEL);
	अगर (!dep) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	dep->dev = dev;
	list_add_tail(&dep->node, &resource->dependents);
	dev_dbg(dev, "added power dependency to [%s]\n", resource->name);

unlock:
	mutex_unlock(&resource->resource_lock);
	वापस ret;
पूर्ण

अटल व्योम
acpi_घातer_resource_हटाओ_dependent(काष्ठा acpi_घातer_resource *resource,
				     काष्ठा device *dev)
अणु
	काष्ठा acpi_घातer_dependent_device *dep;

	mutex_lock(&resource->resource_lock);
	list_क्रम_each_entry(dep, &resource->dependents, node) अणु
		अगर (dep->dev == dev) अणु
			list_del(&dep->node);
			kमुक्त(dep);
			dev_dbg(dev, "removed power dependency to [%s]\n",
				resource->name);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&resource->resource_lock);
पूर्ण

/**
 * acpi_device_घातer_add_dependent - Add dependent device of this ACPI device
 * @adev: ACPI device poपूर्णांकer
 * @dev: Dependent device
 *
 * If @adev has non-empty _PR0 the @dev is added as dependent device to all
 * घातer resources वापसed by it. This means that whenever these घातer
 * resources are turned _ON the dependent devices get runसमय resumed. This
 * is needed क्रम devices such as PCI to allow its driver to re-initialize
 * it after it went to D0uninitialized.
 *
 * If @adev करोes not have _PR0 this करोes nothing.
 *
 * Returns %0 in हाल of success and negative त्रुटि_सं otherwise.
 */
पूर्णांक acpi_device_घातer_add_dependent(काष्ठा acpi_device *adev,
				    काष्ठा device *dev)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	काष्ठा list_head *resources;
	पूर्णांक ret;

	अगर (!adev->flags.घातer_manageable)
		वापस 0;

	resources = &adev->घातer.states[ACPI_STATE_D0].resources;
	list_क्रम_each_entry(entry, resources, node) अणु
		ret = acpi_घातer_resource_add_dependent(entry->resource, dev);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	list_क्रम_each_entry(entry, resources, node)
		acpi_घातer_resource_हटाओ_dependent(entry->resource, dev);

	वापस ret;
पूर्ण

/**
 * acpi_device_घातer_हटाओ_dependent - Remove dependent device
 * @adev: ACPI device poपूर्णांकer
 * @dev: Dependent device
 *
 * Does the opposite of acpi_device_घातer_add_dependent() and हटाओs the
 * dependent device अगर it is found. Can be called to @adev that करोes not
 * have _PR0 as well.
 */
व्योम acpi_device_घातer_हटाओ_dependent(काष्ठा acpi_device *adev,
					काष्ठा device *dev)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	काष्ठा list_head *resources;

	अगर (!adev->flags.घातer_manageable)
		वापस;

	resources = &adev->घातer.states[ACPI_STATE_D0].resources;
	list_क्रम_each_entry_reverse(entry, resources, node)
		acpi_घातer_resource_हटाओ_dependent(entry->resource, dev);
पूर्ण

अटल पूर्णांक __acpi_घातer_on(काष्ठा acpi_घातer_resource *resource)
अणु
	काष्ठा acpi_घातer_dependent_device *dep;
	acpi_status status = AE_OK;

	status = acpi_evaluate_object(resource->device.handle, "_ON", शून्य, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	pr_debug("Power resource [%s] turned on\n", resource->name);

	/*
	 * If there are other dependents on this घातer resource we need to
	 * resume them now so that their drivers can re-initialize the
	 * hardware properly after it went back to D0.
	 */
	अगर (list_empty(&resource->dependents) ||
	    list_is_singular(&resource->dependents))
		वापस 0;

	list_क्रम_each_entry(dep, &resource->dependents, node) अणु
		dev_dbg(dep->dev, "runtime resuming because [%s] turned on\n",
			resource->name);
		pm_request_resume(dep->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_घातer_on_unlocked(काष्ठा acpi_घातer_resource *resource)
अणु
	पूर्णांक result = 0;

	अगर (resource->ref_count++) अणु
		pr_debug("Power resource [%s] already on\n", resource->name);
	पूर्ण अन्यथा अणु
		result = __acpi_घातer_on(resource);
		अगर (result)
			resource->ref_count--;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक acpi_घातer_on(काष्ठा acpi_घातer_resource *resource)
अणु
	पूर्णांक result;

	mutex_lock(&resource->resource_lock);
	result = acpi_घातer_on_unlocked(resource);
	mutex_unlock(&resource->resource_lock);
	वापस result;
पूर्ण

अटल पूर्णांक __acpi_घातer_off(काष्ठा acpi_घातer_resource *resource)
अणु
	acpi_status status;

	status = acpi_evaluate_object(resource->device.handle, "_OFF",
				      शून्य, शून्य);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	pr_debug("Power resource [%s] turned off\n", resource->name);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_घातer_off_unlocked(काष्ठा acpi_घातer_resource *resource)
अणु
	पूर्णांक result = 0;

	अगर (!resource->ref_count) अणु
		pr_debug("Power resource [%s] already off\n", resource->name);
		वापस 0;
	पूर्ण

	अगर (--resource->ref_count) अणु
		pr_debug("Power resource [%s] still in use\n", resource->name);
	पूर्ण अन्यथा अणु
		result = __acpi_घातer_off(resource);
		अगर (result)
			resource->ref_count++;
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक acpi_घातer_off(काष्ठा acpi_घातer_resource *resource)
अणु
	पूर्णांक result;

	mutex_lock(&resource->resource_lock);
	result = acpi_घातer_off_unlocked(resource);
	mutex_unlock(&resource->resource_lock);
	वापस result;
पूर्ण

अटल पूर्णांक acpi_घातer_off_list(काष्ठा list_head *list)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	पूर्णांक result = 0;

	list_क्रम_each_entry_reverse(entry, list, node) अणु
		result = acpi_घातer_off(entry->resource);
		अगर (result)
			जाओ err;
	पूर्ण
	वापस 0;

 err:
	list_क्रम_each_entry_जारी(entry, list, node)
		acpi_घातer_on(entry->resource);

	वापस result;
पूर्ण

अटल पूर्णांक acpi_घातer_on_list(काष्ठा list_head *list)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	पूर्णांक result = 0;

	list_क्रम_each_entry(entry, list, node) अणु
		result = acpi_घातer_on(entry->resource);
		अगर (result)
			जाओ err;
	पूर्ण
	वापस 0;

 err:
	list_क्रम_each_entry_जारी_reverse(entry, list, node)
		acpi_घातer_off(entry->resource);

	वापस result;
पूर्ण

अटल काष्ठा attribute *attrs[] = अणु
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group attr_groups[] = अणु
	[ACPI_STATE_D0] = अणु
		.name = "power_resources_D0",
		.attrs = attrs,
	पूर्ण,
	[ACPI_STATE_D1] = अणु
		.name = "power_resources_D1",
		.attrs = attrs,
	पूर्ण,
	[ACPI_STATE_D2] = अणु
		.name = "power_resources_D2",
		.attrs = attrs,
	पूर्ण,
	[ACPI_STATE_D3_HOT] = अणु
		.name = "power_resources_D3hot",
		.attrs = attrs,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा attribute_group wakeup_attr_group = अणु
	.name = "power_resources_wakeup",
	.attrs = attrs,
पूर्ण;

अटल व्योम acpi_घातer_hide_list(काष्ठा acpi_device *adev,
				 काष्ठा list_head *resources,
				 स्थिर काष्ठा attribute_group *attr_group)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;

	अगर (list_empty(resources))
		वापस;

	list_क्रम_each_entry_reverse(entry, resources, node) अणु
		काष्ठा acpi_device *res_dev = &entry->resource->device;

		sysfs_हटाओ_link_from_group(&adev->dev.kobj,
					     attr_group->name,
					     dev_name(&res_dev->dev));
	पूर्ण
	sysfs_हटाओ_group(&adev->dev.kobj, attr_group);
पूर्ण

अटल व्योम acpi_घातer_expose_list(काष्ठा acpi_device *adev,
				   काष्ठा list_head *resources,
				   स्थिर काष्ठा attribute_group *attr_group)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	पूर्णांक ret;

	अगर (list_empty(resources))
		वापस;

	ret = sysfs_create_group(&adev->dev.kobj, attr_group);
	अगर (ret)
		वापस;

	list_क्रम_each_entry(entry, resources, node) अणु
		काष्ठा acpi_device *res_dev = &entry->resource->device;

		ret = sysfs_add_link_to_group(&adev->dev.kobj,
					      attr_group->name,
					      &res_dev->dev.kobj,
					      dev_name(&res_dev->dev));
		अगर (ret) अणु
			acpi_घातer_hide_list(adev, resources, attr_group);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम acpi_घातer_expose_hide(काष्ठा acpi_device *adev,
				   काष्ठा list_head *resources,
				   स्थिर काष्ठा attribute_group *attr_group,
				   bool expose)
अणु
	अगर (expose)
		acpi_घातer_expose_list(adev, resources, attr_group);
	अन्यथा
		acpi_घातer_hide_list(adev, resources, attr_group);
पूर्ण

व्योम acpi_घातer_add_हटाओ_device(काष्ठा acpi_device *adev, bool add)
अणु
	पूर्णांक state;

	अगर (adev->wakeup.flags.valid)
		acpi_घातer_expose_hide(adev, &adev->wakeup.resources,
				       &wakeup_attr_group, add);

	अगर (!adev->घातer.flags.घातer_resources)
		वापस;

	क्रम (state = ACPI_STATE_D0; state <= ACPI_STATE_D3_HOT; state++)
		acpi_घातer_expose_hide(adev,
				       &adev->घातer.states[state].resources,
				       &attr_groups[state], add);
पूर्ण

पूर्णांक acpi_घातer_wakeup_list_init(काष्ठा list_head *list, पूर्णांक *प्रणाली_level_p)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	पूर्णांक प्रणाली_level = 5;

	list_क्रम_each_entry(entry, list, node) अणु
		काष्ठा acpi_घातer_resource *resource = entry->resource;
		acpi_handle handle = resource->device.handle;
		पूर्णांक result;
		पूर्णांक state;

		mutex_lock(&resource->resource_lock);

		result = acpi_घातer_get_state(handle, &state);
		अगर (result) अणु
			mutex_unlock(&resource->resource_lock);
			वापस result;
		पूर्ण
		अगर (state == ACPI_POWER_RESOURCE_STATE_ON) अणु
			resource->ref_count++;
			resource->wakeup_enabled = true;
		पूर्ण
		अगर (प्रणाली_level > resource->प्रणाली_level)
			प्रणाली_level = resource->प्रणाली_level;

		mutex_unlock(&resource->resource_lock);
	पूर्ण
	*प्रणाली_level_p = प्रणाली_level;
	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
                             Device Power Management
   -------------------------------------------------------------------------- */

/**
 * acpi_device_sleep_wake - execute _DSW (Device Sleep Wake) or (deprecated in
 *                          ACPI 3.0) _PSW (Power State Wake)
 * @dev: Device to handle.
 * @enable: 0 - disable, 1 - enable the wake capabilities of the device.
 * @sleep_state: Target sleep state of the प्रणाली.
 * @dev_state: Target घातer state of the device.
 *
 * Execute _DSW (Device Sleep Wake) or (deprecated in ACPI 3.0) _PSW (Power
 * State Wake) क्रम the device, अगर present.  On failure reset the device's
 * wakeup.flags.valid flag.
 *
 * RETURN VALUE:
 * 0 अगर either _DSW or _PSW has been successfully executed
 * 0 अगर neither _DSW nor _PSW has been found
 * -ENODEV अगर the execution of either _DSW or _PSW has failed
 */
पूर्णांक acpi_device_sleep_wake(काष्ठा acpi_device *dev,
			   पूर्णांक enable, पूर्णांक sleep_state, पूर्णांक dev_state)
अणु
	जोड़ acpi_object in_arg[3];
	काष्ठा acpi_object_list arg_list = अणु 3, in_arg पूर्ण;
	acpi_status status = AE_OK;

	/*
	 * Try to execute _DSW first.
	 *
	 * Three arguments are needed क्रम the _DSW object:
	 * Argument 0: enable/disable the wake capabilities
	 * Argument 1: target प्रणाली state
	 * Argument 2: target device state
	 * When _DSW object is called to disable the wake capabilities, maybe
	 * the first argument is filled. The values of the other two arguments
	 * are meaningless.
	 */
	in_arg[0].type = ACPI_TYPE_INTEGER;
	in_arg[0].पूर्णांकeger.value = enable;
	in_arg[1].type = ACPI_TYPE_INTEGER;
	in_arg[1].पूर्णांकeger.value = sleep_state;
	in_arg[2].type = ACPI_TYPE_INTEGER;
	in_arg[2].पूर्णांकeger.value = dev_state;
	status = acpi_evaluate_object(dev->handle, "_DSW", &arg_list, शून्य);
	अगर (ACPI_SUCCESS(status)) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (status != AE_NOT_FOUND) अणु
		acpi_handle_info(dev->handle, "_DSW execution failed\n");
		dev->wakeup.flags.valid = 0;
		वापस -ENODEV;
	पूर्ण

	/* Execute _PSW */
	status = acpi_execute_simple_method(dev->handle, "_PSW", enable);
	अगर (ACPI_FAILURE(status) && (status != AE_NOT_FOUND)) अणु
		acpi_handle_info(dev->handle, "_PSW execution failed\n");
		dev->wakeup.flags.valid = 0;
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Prepare a wakeup device, two steps (Ref ACPI 2.0:P229):
 * 1. Power on the घातer resources required क्रम the wakeup device
 * 2. Execute _DSW (Device Sleep Wake) or (deprecated in ACPI 3.0) _PSW (Power
 *    State Wake) क्रम the device, अगर present
 */
पूर्णांक acpi_enable_wakeup_device_घातer(काष्ठा acpi_device *dev, पूर्णांक sleep_state)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	पूर्णांक err = 0;

	अगर (!dev || !dev->wakeup.flags.valid)
		वापस -EINVAL;

	mutex_lock(&acpi_device_lock);

	अगर (dev->wakeup.prepare_count++)
		जाओ out;

	list_क्रम_each_entry(entry, &dev->wakeup.resources, node) अणु
		काष्ठा acpi_घातer_resource *resource = entry->resource;

		mutex_lock(&resource->resource_lock);

		अगर (!resource->wakeup_enabled) अणु
			err = acpi_घातer_on_unlocked(resource);
			अगर (!err)
				resource->wakeup_enabled = true;
		पूर्ण

		mutex_unlock(&resource->resource_lock);

		अगर (err) अणु
			dev_err(&dev->dev,
				"Cannot turn wakeup power resources on\n");
			dev->wakeup.flags.valid = 0;
			जाओ out;
		पूर्ण
	पूर्ण
	/*
	 * Passing 3 as the third argument below means the device may be
	 * put पूर्णांकo arbitrary घातer state afterward.
	 */
	err = acpi_device_sleep_wake(dev, 1, sleep_state, 3);
	अगर (err)
		dev->wakeup.prepare_count = 0;

 out:
	mutex_unlock(&acpi_device_lock);
	वापस err;
पूर्ण

/*
 * Shutकरोwn a wakeup device, counterpart of above method
 * 1. Execute _DSW (Device Sleep Wake) or (deprecated in ACPI 3.0) _PSW (Power
 *    State Wake) क्रम the device, अगर present
 * 2. Shutकरोwn करोwn the घातer resources
 */
पूर्णांक acpi_disable_wakeup_device_घातer(काष्ठा acpi_device *dev)
अणु
	काष्ठा acpi_घातer_resource_entry *entry;
	पूर्णांक err = 0;

	अगर (!dev || !dev->wakeup.flags.valid)
		वापस -EINVAL;

	mutex_lock(&acpi_device_lock);

	अगर (--dev->wakeup.prepare_count > 0)
		जाओ out;

	/*
	 * Executing the code below even अगर prepare_count is alपढ़ोy zero when
	 * the function is called may be useful, क्रम example क्रम initialisation.
	 */
	अगर (dev->wakeup.prepare_count < 0)
		dev->wakeup.prepare_count = 0;

	err = acpi_device_sleep_wake(dev, 0, 0, 0);
	अगर (err)
		जाओ out;

	list_क्रम_each_entry(entry, &dev->wakeup.resources, node) अणु
		काष्ठा acpi_घातer_resource *resource = entry->resource;

		mutex_lock(&resource->resource_lock);

		अगर (resource->wakeup_enabled) अणु
			err = acpi_घातer_off_unlocked(resource);
			अगर (!err)
				resource->wakeup_enabled = false;
		पूर्ण

		mutex_unlock(&resource->resource_lock);

		अगर (err) अणु
			dev_err(&dev->dev,
				"Cannot turn wakeup power resources off\n");
			dev->wakeup.flags.valid = 0;
			अवरोध;
		पूर्ण
	पूर्ण

 out:
	mutex_unlock(&acpi_device_lock);
	वापस err;
पूर्ण

पूर्णांक acpi_घातer_get_inferred_state(काष्ठा acpi_device *device, पूर्णांक *state)
अणु
	पूर्णांक result = 0;
	पूर्णांक list_state = 0;
	पूर्णांक i = 0;

	अगर (!device || !state)
		वापस -EINVAL;

	/*
	 * We know a device's inferred घातer state when all the resources
	 * required क्रम a given D-state are 'on'.
	 */
	क्रम (i = ACPI_STATE_D0; i <= ACPI_STATE_D3_HOT; i++) अणु
		काष्ठा list_head *list = &device->घातer.states[i].resources;

		अगर (list_empty(list))
			जारी;

		result = acpi_घातer_get_list_state(list, &list_state);
		अगर (result)
			वापस result;

		अगर (list_state == ACPI_POWER_RESOURCE_STATE_ON) अणु
			*state = i;
			वापस 0;
		पूर्ण
	पूर्ण

	*state = device->घातer.states[ACPI_STATE_D3_COLD].flags.valid ?
		ACPI_STATE_D3_COLD : ACPI_STATE_D3_HOT;
	वापस 0;
पूर्ण

पूर्णांक acpi_घातer_on_resources(काष्ठा acpi_device *device, पूर्णांक state)
अणु
	अगर (!device || state < ACPI_STATE_D0 || state > ACPI_STATE_D3_HOT)
		वापस -EINVAL;

	वापस acpi_घातer_on_list(&device->घातer.states[state].resources);
पूर्ण

पूर्णांक acpi_घातer_transition(काष्ठा acpi_device *device, पूर्णांक state)
अणु
	पूर्णांक result = 0;

	अगर (!device || (state < ACPI_STATE_D0) || (state > ACPI_STATE_D3_COLD))
		वापस -EINVAL;

	अगर (device->घातer.state == state || !device->flags.घातer_manageable)
		वापस 0;

	अगर ((device->घातer.state < ACPI_STATE_D0)
	    || (device->घातer.state > ACPI_STATE_D3_COLD))
		वापस -ENODEV;

	/*
	 * First we reference all घातer resources required in the target list
	 * (e.g. so the device करोesn't lose घातer जबतक transitioning).  Then,
	 * we dereference all घातer resources used in the current list.
	 */
	अगर (state < ACPI_STATE_D3_COLD)
		result = acpi_घातer_on_list(
			&device->घातer.states[state].resources);

	अगर (!result && device->घातer.state < ACPI_STATE_D3_COLD)
		acpi_घातer_off_list(
			&device->घातer.states[device->घातer.state].resources);

	/* We shouldn't change the state unless the above operations succeed. */
	device->घातer.state = result ? ACPI_STATE_UNKNOWN : state;

	वापस result;
पूर्ण

अटल व्योम acpi_release_घातer_resource(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा acpi_घातer_resource *resource;

	resource = container_of(device, काष्ठा acpi_घातer_resource, device);

	mutex_lock(&घातer_resource_list_lock);
	list_del(&resource->list_node);
	mutex_unlock(&घातer_resource_list_lock);

	acpi_मुक्त_pnp_ids(&device->pnp);
	kमुक्त(resource);
पूर्ण

अटल sमाप_प्रकार resource_in_use_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा acpi_घातer_resource *resource;

	resource = to_घातer_resource(to_acpi_device(dev));
	वापस प्र_लिखो(buf, "%u\n", !!resource->ref_count);
पूर्ण
अटल DEVICE_ATTR_RO(resource_in_use);

अटल व्योम acpi_घातer_sysfs_हटाओ(काष्ठा acpi_device *device)
अणु
	device_हटाओ_file(&device->dev, &dev_attr_resource_in_use);
पूर्ण

अटल व्योम acpi_घातer_add_resource_to_list(काष्ठा acpi_घातer_resource *resource)
अणु
	mutex_lock(&घातer_resource_list_lock);

	अगर (!list_empty(&acpi_घातer_resource_list)) अणु
		काष्ठा acpi_घातer_resource *r;

		list_क्रम_each_entry(r, &acpi_घातer_resource_list, list_node)
			अगर (r->order > resource->order) अणु
				list_add_tail(&resource->list_node, &r->list_node);
				जाओ out;
			पूर्ण
	पूर्ण
	list_add_tail(&resource->list_node, &acpi_घातer_resource_list);

 out:
	mutex_unlock(&घातer_resource_list_lock);
पूर्ण

काष्ठा acpi_device *acpi_add_घातer_resource(acpi_handle handle)
अणु
	काष्ठा acpi_घातer_resource *resource;
	काष्ठा acpi_device *device = शून्य;
	जोड़ acpi_object acpi_object;
	काष्ठा acpi_buffer buffer = अणु माप(acpi_object), &acpi_object पूर्ण;
	acpi_status status;
	पूर्णांक state, result = -ENODEV;

	acpi_bus_get_device(handle, &device);
	अगर (device)
		वापस device;

	resource = kzalloc(माप(*resource), GFP_KERNEL);
	अगर (!resource)
		वापस शून्य;

	device = &resource->device;
	acpi_init_device_object(device, handle, ACPI_BUS_TYPE_POWER);
	mutex_init(&resource->resource_lock);
	INIT_LIST_HEAD(&resource->list_node);
	INIT_LIST_HEAD(&resource->dependents);
	resource->name = device->pnp.bus_id;
	म_नकल(acpi_device_name(device), ACPI_POWER_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_POWER_CLASS);
	device->घातer.state = ACPI_STATE_UNKNOWN;

	/* Evaluate the object to get the प्रणाली level and resource order. */
	status = acpi_evaluate_object(handle, शून्य, शून्य, &buffer);
	अगर (ACPI_FAILURE(status))
		जाओ err;

	resource->प्रणाली_level = acpi_object.घातer_resource.प्रणाली_level;
	resource->order = acpi_object.घातer_resource.resource_order;

	result = acpi_घातer_get_state(handle, &state);
	अगर (result)
		जाओ err;

	pr_info("%s [%s] (%s)\n", acpi_device_name(device),
		acpi_device_bid(device), state ? "on" : "off");

	device->flags.match_driver = true;
	result = acpi_device_add(device, acpi_release_घातer_resource);
	अगर (result)
		जाओ err;

	अगर (!device_create_file(&device->dev, &dev_attr_resource_in_use))
		device->हटाओ = acpi_घातer_sysfs_हटाओ;

	acpi_घातer_add_resource_to_list(resource);
	acpi_device_add_finalize(device);
	वापस device;

 err:
	acpi_release_घातer_resource(&device->dev);
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_ACPI_SLEEP
व्योम acpi_resume_घातer_resources(व्योम)
अणु
	काष्ठा acpi_घातer_resource *resource;

	mutex_lock(&घातer_resource_list_lock);

	list_क्रम_each_entry(resource, &acpi_घातer_resource_list, list_node) अणु
		पूर्णांक result, state;

		mutex_lock(&resource->resource_lock);

		result = acpi_घातer_get_state(resource->device.handle, &state);
		अगर (result) अणु
			mutex_unlock(&resource->resource_lock);
			जारी;
		पूर्ण

		अगर (state == ACPI_POWER_RESOURCE_STATE_OFF
		    && resource->ref_count) अणु
			dev_info(&resource->device.dev, "Turning ON\n");
			__acpi_घातer_on(resource);
		पूर्ण

		mutex_unlock(&resource->resource_lock);
	पूर्ण

	mutex_unlock(&घातer_resource_list_lock);
पूर्ण
#पूर्ण_अगर

अटल व्योम acpi_घातer_turn_off_अगर_unused(काष्ठा acpi_घातer_resource *resource,
				       bool init)
अणु
	अगर (resource->ref_count > 0)
		वापस;

	अगर (init) अणु
		अगर (resource->users > 0)
			वापस;
	पूर्ण अन्यथा अणु
		पूर्णांक result, state;

		result = acpi_घातer_get_state(resource->device.handle, &state);
		अगर (result || state == ACPI_POWER_RESOURCE_STATE_OFF)
			वापस;
	पूर्ण

	dev_info(&resource->device.dev, "Turning OFF\n");
	__acpi_घातer_off(resource);
पूर्ण

/**
 * acpi_turn_off_unused_घातer_resources - Turn off घातer resources not in use.
 * @init: Control चयन.
 *
 * If @ainit is set, unconditionally turn off all of the ACPI घातer resources
 * without any users.
 *
 * Otherwise, turn off all ACPI घातer resources without active references (that
 * is, the ones that should be "off" at the moment) that are "on".
 */
व्योम acpi_turn_off_unused_घातer_resources(bool init)
अणु
	काष्ठा acpi_घातer_resource *resource;

	mutex_lock(&घातer_resource_list_lock);

	list_क्रम_each_entry_reverse(resource, &acpi_घातer_resource_list, list_node) अणु
		mutex_lock(&resource->resource_lock);

		acpi_घातer_turn_off_अगर_unused(resource, init);

		mutex_unlock(&resource->resource_lock);
	पूर्ण

	mutex_unlock(&घातer_resource_list_lock);
पूर्ण
