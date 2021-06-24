<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/acpi/device_sysfs.c - ACPI device sysfs attributes and modalias.
 *
 * Copyright (C) 2015, Intel Corp.
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/acpi.h>
#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/nls.h>

#समावेश "internal.h"

अटल sमाप_प्रकार acpi_object_path(acpi_handle handle, अक्षर *buf)
अणु
	काष्ठा acpi_buffer path = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	पूर्णांक result;

	result = acpi_get_name(handle, ACPI_FULL_PATHNAME, &path);
	अगर (result)
		वापस result;

	result = प्र_लिखो(buf, "%s\n", (अक्षर *)path.poपूर्णांकer);
	kमुक्त(path.poपूर्णांकer);
	वापस result;
पूर्ण

काष्ठा acpi_data_node_attr अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा acpi_data_node *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा acpi_data_node *, स्थिर अक्षर *, माप_प्रकार count);
पूर्ण;

#घोषणा DATA_NODE_ATTR(_name)			\
	अटल काष्ठा acpi_data_node_attr data_node_##_name =	\
		__ATTR(_name, 0444, data_node_show_##_name, शून्य)

अटल sमाप_प्रकार data_node_show_path(काष्ठा acpi_data_node *dn, अक्षर *buf)
अणु
	वापस dn->handle ? acpi_object_path(dn->handle, buf) : 0;
पूर्ण

DATA_NODE_ATTR(path);

अटल काष्ठा attribute *acpi_data_node_शेष_attrs[] = अणु
	&data_node_path.attr,
	शून्य
पूर्ण;

#घोषणा to_data_node(k) container_of(k, काष्ठा acpi_data_node, kobj)
#घोषणा to_attr(a) container_of(a, काष्ठा acpi_data_node_attr, attr)

अटल sमाप_प्रकार acpi_data_node_attr_show(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_data_node *dn = to_data_node(kobj);
	काष्ठा acpi_data_node_attr *dn_attr = to_attr(attr);

	वापस dn_attr->show ? dn_attr->show(dn, buf) : -ENXIO;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops acpi_data_node_sysfs_ops = अणु
	.show	= acpi_data_node_attr_show,
पूर्ण;

अटल व्योम acpi_data_node_release(काष्ठा kobject *kobj)
अणु
	काष्ठा acpi_data_node *dn = to_data_node(kobj);

	complete(&dn->kobj_करोne);
पूर्ण

अटल काष्ठा kobj_type acpi_data_node_ktype = अणु
	.sysfs_ops = &acpi_data_node_sysfs_ops,
	.शेष_attrs = acpi_data_node_शेष_attrs,
	.release = acpi_data_node_release,
पूर्ण;

अटल व्योम acpi_expose_nondev_subnodes(काष्ठा kobject *kobj,
					काष्ठा acpi_device_data *data)
अणु
	काष्ठा list_head *list = &data->subnodes;
	काष्ठा acpi_data_node *dn;

	अगर (list_empty(list))
		वापस;

	list_क्रम_each_entry(dn, list, sibling) अणु
		पूर्णांक ret;

		init_completion(&dn->kobj_करोne);
		ret = kobject_init_and_add(&dn->kobj, &acpi_data_node_ktype,
					   kobj, "%s", dn->name);
		अगर (!ret)
			acpi_expose_nondev_subnodes(&dn->kobj, &dn->data);
		अन्यथा अगर (dn->handle)
			acpi_handle_err(dn->handle, "Failed to expose (%d)\n", ret);
	पूर्ण
पूर्ण

अटल व्योम acpi_hide_nondev_subnodes(काष्ठा acpi_device_data *data)
अणु
	काष्ठा list_head *list = &data->subnodes;
	काष्ठा acpi_data_node *dn;

	अगर (list_empty(list))
		वापस;

	list_क्रम_each_entry_reverse(dn, list, sibling) अणु
		acpi_hide_nondev_subnodes(&dn->data);
		kobject_put(&dn->kobj);
	पूर्ण
पूर्ण

/**
 * create_pnp_modalias - Create hid/cid(s) string क्रम modalias and uevent
 * @acpi_dev: ACPI device object.
 * @modalias: Buffer to prपूर्णांक पूर्णांकo.
 * @size: Size of the buffer.
 *
 * Creates hid/cid(s) string needed क्रम modalias and uevent
 * e.g. on a device with hid:IBM0001 and cid:ACPI0001 you get:
 * अक्षर *modalias: "acpi:IBM0001:ACPI0001"
 * Return: 0: no _HID and no _CID
 *         -EINVAL: output error
 *         -ENOMEM: output is truncated
 */
अटल पूर्णांक create_pnp_modalias(काष्ठा acpi_device *acpi_dev, अक्षर *modalias,
			       पूर्णांक size)
अणु
	पूर्णांक len;
	पूर्णांक count;
	काष्ठा acpi_hardware_id *id;

	/* Aव्योम unnecessarily loading modules क्रम non present devices. */
	अगर (!acpi_device_is_present(acpi_dev))
		वापस 0;

	/*
	 * Since we skip ACPI_DT_NAMESPACE_HID from the modalias below, 0 should
	 * be वापसed अगर ACPI_DT_NAMESPACE_HID is the only ACPI/PNP ID in the
	 * device's list.
	 */
	count = 0;
	list_क्रम_each_entry(id, &acpi_dev->pnp.ids, list)
		अगर (म_भेद(id->id, ACPI_DT_NAMESPACE_HID))
			count++;

	अगर (!count)
		वापस 0;

	len = snम_लिखो(modalias, size, "acpi:");
	अगर (len <= 0)
		वापस len;

	size -= len;

	list_क्रम_each_entry(id, &acpi_dev->pnp.ids, list) अणु
		अगर (!म_भेद(id->id, ACPI_DT_NAMESPACE_HID))
			जारी;

		count = snम_लिखो(&modalias[len], size, "%s:", id->id);
		अगर (count < 0)
			वापस -EINVAL;

		अगर (count >= size)
			वापस -ENOMEM;

		len += count;
		size -= count;
	पूर्ण
	modalias[len] = '\0';
	वापस len;
पूर्ण

/**
 * create_of_modalias - Creates DT compatible string क्रम modalias and uevent
 * @acpi_dev: ACPI device object.
 * @modalias: Buffer to prपूर्णांक पूर्णांकo.
 * @size: Size of the buffer.
 *
 * Expose DT compatible modalias as of:NnameTCcompatible.  This function should
 * only be called क्रम devices having ACPI_DT_NAMESPACE_HID in their list of
 * ACPI/PNP IDs.
 */
अटल पूर्णांक create_of_modalias(काष्ठा acpi_device *acpi_dev, अक्षर *modalias,
			      पूर्णांक size)
अणु
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER पूर्ण;
	स्थिर जोड़ acpi_object *of_compatible, *obj;
	acpi_status status;
	पूर्णांक len, count;
	पूर्णांक i, nval;
	अक्षर *c;

	status = acpi_get_name(acpi_dev->handle, ACPI_SINGLE_NAME, &buf);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	/* DT strings are all in lower हाल */
	क्रम (c = buf.poपूर्णांकer; *c != '\0'; c++)
		*c = छोटे(*c);

	len = snम_लिखो(modalias, size, "of:N%sT", (अक्षर *)buf.poपूर्णांकer);
	ACPI_FREE(buf.poपूर्णांकer);

	अगर (len <= 0)
		वापस len;

	of_compatible = acpi_dev->data.of_compatible;
	अगर (of_compatible->type == ACPI_TYPE_PACKAGE) अणु
		nval = of_compatible->package.count;
		obj = of_compatible->package.elements;
	पूर्ण अन्यथा अणु /* Must be ACPI_TYPE_STRING. */
		nval = 1;
		obj = of_compatible;
	पूर्ण
	क्रम (i = 0; i < nval; i++, obj++) अणु
		count = snम_लिखो(&modalias[len], size, "C%s",
				 obj->string.poपूर्णांकer);
		अगर (count < 0)
			वापस -EINVAL;

		अगर (count >= size)
			वापस -ENOMEM;

		len += count;
		size -= count;
	पूर्ण
	modalias[len] = '\0';
	वापस len;
पूर्ण

पूर्णांक __acpi_device_uevent_modalias(काष्ठा acpi_device *adev,
				  काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक len;

	अगर (!adev)
		वापस -ENODEV;

	अगर (list_empty(&adev->pnp.ids))
		वापस 0;

	अगर (add_uevent_var(env, "MODALIAS="))
		वापस -ENOMEM;

	अगर (adev->data.of_compatible)
		len = create_of_modalias(adev, &env->buf[env->buflen - 1],
					 माप(env->buf) - env->buflen);
	अन्यथा
		len = create_pnp_modalias(adev, &env->buf[env->buflen - 1],
					  माप(env->buf) - env->buflen);
	अगर (len < 0)
		वापस len;

	env->buflen += len;

	वापस 0;
पूर्ण

/**
 * acpi_device_uevent_modalias - uevent modalias क्रम ACPI-क्रमागतerated devices.
 *
 * Create the uevent modalias field क्रम ACPI-क्रमागतerated devices.
 *
 * Because other buses करो not support ACPI HIDs & CIDs, e.g. क्रम a device with
 * hid:IBM0001 and cid:ACPI0001 you get: "acpi:IBM0001:ACPI0001".
 */
पूर्णांक acpi_device_uevent_modalias(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	वापस __acpi_device_uevent_modalias(acpi_companion_match(dev), env);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_device_uevent_modalias);

अटल पूर्णांक __acpi_device_modalias(काष्ठा acpi_device *adev, अक्षर *buf, पूर्णांक size)
अणु
	पूर्णांक len, count;

	अगर (!adev)
		वापस -ENODEV;

	अगर (list_empty(&adev->pnp.ids))
		वापस 0;

	len = create_pnp_modalias(adev, buf, size - 1);
	अगर (len < 0) अणु
		वापस len;
	पूर्ण अन्यथा अगर (len > 0) अणु
		buf[len++] = '\n';
		size -= len;
	पूर्ण
	अगर (!adev->data.of_compatible)
		वापस len;

	count = create_of_modalias(adev, buf + len, size - 1);
	अगर (count < 0) अणु
		वापस count;
	पूर्ण अन्यथा अगर (count > 0) अणु
		len += count;
		buf[len++] = '\n';
	पूर्ण

	वापस len;
पूर्ण

/**
 * acpi_device_modalias - modalias sysfs attribute क्रम ACPI-क्रमागतerated devices.
 *
 * Create the modalias sysfs attribute क्रम ACPI-क्रमागतerated devices.
 *
 * Because other buses करो not support ACPI HIDs & CIDs, e.g. क्रम a device with
 * hid:IBM0001 and cid:ACPI0001 you get: "acpi:IBM0001:ACPI0001".
 */
पूर्णांक acpi_device_modalias(काष्ठा device *dev, अक्षर *buf, पूर्णांक size)
अणु
	वापस __acpi_device_modalias(acpi_companion_match(dev), buf, size);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_device_modalias);

अटल sमाप_प्रकार
modalias_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस __acpi_device_modalias(to_acpi_device(dev), buf, 1024);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल sमाप_प्रकार real_घातer_state_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_device *adev = to_acpi_device(dev);
	पूर्णांक state;
	पूर्णांक ret;

	ret = acpi_device_get_घातer(adev, &state);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%s\n", acpi_घातer_state_string(state));
पूर्ण

अटल DEVICE_ATTR_RO(real_घातer_state);

अटल sमाप_प्रकार घातer_state_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_device *adev = to_acpi_device(dev);

	वापस प्र_लिखो(buf, "%s\n", acpi_घातer_state_string(adev->घातer.state));
पूर्ण

अटल DEVICE_ATTR_RO(घातer_state);

अटल sमाप_प्रकार
eject_store(काष्ठा device *d, काष्ठा device_attribute *attr,
	    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi_device = to_acpi_device(d);
	acpi_object_type not_used;
	acpi_status status;

	अगर (!count || buf[0] != '1')
		वापस -EINVAL;

	अगर ((!acpi_device->handler || !acpi_device->handler->hotplug.enabled)
	    && !acpi_device->driver)
		वापस -ENODEV;

	status = acpi_get_type(acpi_device->handle, &not_used);
	अगर (ACPI_FAILURE(status) || !acpi_device->flags.ejectable)
		वापस -ENODEV;

	acpi_dev_get(acpi_device);
	status = acpi_hotplug_schedule(acpi_device, ACPI_OST_EC_OSPM_EJECT);
	अगर (ACPI_SUCCESS(status))
		वापस count;

	acpi_dev_put(acpi_device);
	acpi_evaluate_ost(acpi_device->handle, ACPI_OST_EC_OSPM_EJECT,
			  ACPI_OST_SC_NON_SPECIFIC_FAILURE, शून्य);
	वापस status == AE_NO_MEMORY ? -ENOMEM : -EAGAIN;
पूर्ण

अटल DEVICE_ATTR_WO(eject);

अटल sमाप_प्रकार
hid_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);

	वापस प्र_लिखो(buf, "%s\n", acpi_device_hid(acpi_dev));
पूर्ण
अटल DEVICE_ATTR_RO(hid);

अटल sमाप_प्रकार uid_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);

	वापस प्र_लिखो(buf, "%s\n", acpi_dev->pnp.unique_id);
पूर्ण
अटल DEVICE_ATTR_RO(uid);

अटल sमाप_प्रकार adr_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);

	अगर (acpi_dev->pnp.bus_address > U32_MAX)
		वापस प्र_लिखो(buf, "0x%016llx\n", acpi_dev->pnp.bus_address);
	अन्यथा
		वापस प्र_लिखो(buf, "0x%08llx\n", acpi_dev->pnp.bus_address);
पूर्ण
अटल DEVICE_ATTR_RO(adr);

अटल sमाप_प्रकार path_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);

	वापस acpi_object_path(acpi_dev->handle, buf);
पूर्ण
अटल DEVICE_ATTR_RO(path);

/* sysfs file that shows description text from the ACPI _STR method */
अटल sमाप_प्रकार description_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	पूर्णांक result;

	अगर (acpi_dev->pnp.str_obj == शून्य)
		वापस 0;

	/*
	 * The _STR object contains a Unicode identअगरier क्रम a device.
	 * We need to convert to utf-8 so it can be displayed.
	 */
	result = utf16s_to_utf8s(
		(ब_अक्षर_प्रकार *)acpi_dev->pnp.str_obj->buffer.poपूर्णांकer,
		acpi_dev->pnp.str_obj->buffer.length,
		UTF16_LITTLE_ENDIAN, buf,
		PAGE_SIZE);

	buf[result++] = '\n';

	वापस result;
पूर्ण
अटल DEVICE_ATTR_RO(description);

अटल sमाप_प्रकार
sun_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	 अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ sun;

	status = acpi_evaluate_पूर्णांकeger(acpi_dev->handle, "_SUN", शून्य, &sun);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस प्र_लिखो(buf, "%llu\n", sun);
पूर्ण
अटल DEVICE_ATTR_RO(sun);

अटल sमाप_प्रकार
hrv_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	 अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ hrv;

	status = acpi_evaluate_पूर्णांकeger(acpi_dev->handle, "_HRV", शून्य, &hrv);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस प्र_लिखो(buf, "%llu\n", hrv);
पूर्ण
अटल DEVICE_ATTR_RO(hrv);

अटल sमाप_प्रकार status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ sta;

	status = acpi_evaluate_पूर्णांकeger(acpi_dev->handle, "_STA", शून्य, &sta);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस प्र_लिखो(buf, "%llu\n", sta);
पूर्ण
अटल DEVICE_ATTR_RO(status);

/**
 * acpi_device_setup_files - Create sysfs attributes of an ACPI device.
 * @dev: ACPI device object.
 */
पूर्णांक acpi_device_setup_files(काष्ठा acpi_device *dev)
अणु
	काष्ठा acpi_buffer buffer = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	acpi_status status;
	पूर्णांक result = 0;

	/*
	 * Devices gotten from FADT करोn't have a "path" attribute
	 */
	अगर (dev->handle) अणु
		result = device_create_file(&dev->dev, &dev_attr_path);
		अगर (result)
			जाओ end;
	पूर्ण

	अगर (!list_empty(&dev->pnp.ids)) अणु
		result = device_create_file(&dev->dev, &dev_attr_hid);
		अगर (result)
			जाओ end;

		result = device_create_file(&dev->dev, &dev_attr_modalias);
		अगर (result)
			जाओ end;
	पूर्ण

	/*
	 * If device has _STR, 'description' file is created
	 */
	अगर (acpi_has_method(dev->handle, "_STR")) अणु
		status = acpi_evaluate_object(dev->handle, "_STR",
					शून्य, &buffer);
		अगर (ACPI_FAILURE(status))
			buffer.poपूर्णांकer = शून्य;
		dev->pnp.str_obj = buffer.poपूर्णांकer;
		result = device_create_file(&dev->dev, &dev_attr_description);
		अगर (result)
			जाओ end;
	पूर्ण

	अगर (dev->pnp.type.bus_address)
		result = device_create_file(&dev->dev, &dev_attr_adr);
	अगर (dev->pnp.unique_id)
		result = device_create_file(&dev->dev, &dev_attr_uid);

	अगर (acpi_has_method(dev->handle, "_SUN")) अणु
		result = device_create_file(&dev->dev, &dev_attr_sun);
		अगर (result)
			जाओ end;
	पूर्ण

	अगर (acpi_has_method(dev->handle, "_HRV")) अणु
		result = device_create_file(&dev->dev, &dev_attr_hrv);
		अगर (result)
			जाओ end;
	पूर्ण

	अगर (acpi_has_method(dev->handle, "_STA")) अणु
		result = device_create_file(&dev->dev, &dev_attr_status);
		अगर (result)
			जाओ end;
	पूर्ण

	/*
	 * If device has _EJ0, 'eject' file is created that is used to trigger
	 * hot-removal function from userland.
	 */
	अगर (acpi_has_method(dev->handle, "_EJ0")) अणु
		result = device_create_file(&dev->dev, &dev_attr_eject);
		अगर (result)
			वापस result;
	पूर्ण

	अगर (dev->flags.घातer_manageable) अणु
		result = device_create_file(&dev->dev, &dev_attr_घातer_state);
		अगर (result)
			वापस result;

		अगर (dev->घातer.flags.घातer_resources)
			result = device_create_file(&dev->dev,
						    &dev_attr_real_घातer_state);
	पूर्ण

	acpi_expose_nondev_subnodes(&dev->dev.kobj, &dev->data);

end:
	वापस result;
पूर्ण

/**
 * acpi_device_हटाओ_files - Remove sysfs attributes of an ACPI device.
 * @dev: ACPI device object.
 */
व्योम acpi_device_हटाओ_files(काष्ठा acpi_device *dev)
अणु
	acpi_hide_nondev_subnodes(&dev->data);

	अगर (dev->flags.घातer_manageable) अणु
		device_हटाओ_file(&dev->dev, &dev_attr_घातer_state);
		अगर (dev->घातer.flags.घातer_resources)
			device_हटाओ_file(&dev->dev,
					   &dev_attr_real_घातer_state);
	पूर्ण

	/*
	 * If device has _STR, हटाओ 'description' file
	 */
	अगर (acpi_has_method(dev->handle, "_STR")) अणु
		kमुक्त(dev->pnp.str_obj);
		device_हटाओ_file(&dev->dev, &dev_attr_description);
	पूर्ण
	/*
	 * If device has _EJ0, हटाओ 'eject' file.
	 */
	अगर (acpi_has_method(dev->handle, "_EJ0"))
		device_हटाओ_file(&dev->dev, &dev_attr_eject);

	अगर (acpi_has_method(dev->handle, "_SUN"))
		device_हटाओ_file(&dev->dev, &dev_attr_sun);

	अगर (acpi_has_method(dev->handle, "_HRV"))
		device_हटाओ_file(&dev->dev, &dev_attr_hrv);

	अगर (dev->pnp.unique_id)
		device_हटाओ_file(&dev->dev, &dev_attr_uid);
	अगर (dev->pnp.type.bus_address)
		device_हटाओ_file(&dev->dev, &dev_attr_adr);
	device_हटाओ_file(&dev->dev, &dev_attr_modalias);
	device_हटाओ_file(&dev->dev, &dev_attr_hid);
	अगर (acpi_has_method(dev->handle, "_STA"))
		device_हटाओ_file(&dev->dev, &dev_attr_status);
	अगर (dev->handle)
		device_हटाओ_file(&dev->dev, &dev_attr_path);
पूर्ण
