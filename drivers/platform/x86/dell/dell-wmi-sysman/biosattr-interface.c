<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions corresponding to SET methods under BIOS attributes पूर्णांकerface GUID क्रम use
 * with dell-wmi-sysman
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#समावेश <linux/wmi.h>
#समावेश "dell-wmi-sysman.h"

#घोषणा SETDEFAULTVALUES_METHOD_ID					0x02
#घोषणा SETBIOSDEFAULTS_METHOD_ID					0x03
#घोषणा SETATTRIBUTE_METHOD_ID						0x04

अटल पूर्णांक call_biosattributes_पूर्णांकerface(काष्ठा wmi_device *wdev, अक्षर *in_args, माप_प्रकार size,
					पूर्णांक method_id)
अणु
	काष्ठा acpi_buffer output = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	काष्ठा acpi_buffer input;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक ret = -EIO;

	input.length =  (acpi_size) size;
	input.poपूर्णांकer = in_args;
	status = wmidev_evaluate_method(wdev, 0, method_id, &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;
	obj = (जोड़ acpi_object *)output.poपूर्णांकer;
	अगर (obj->type == ACPI_TYPE_INTEGER)
		ret = obj->पूर्णांकeger.value;

	अगर (wmi_priv.pending_changes == 0) अणु
		wmi_priv.pending_changes = 1;
		/* let userland know it may need to check reboot pending again */
		kobject_uevent(&wmi_priv.class_dev->kobj, KOBJ_CHANGE);
	पूर्ण
	kमुक्त(output.poपूर्णांकer);
	वापस map_wmi_error(ret);
पूर्ण

/**
 * set_attribute() - Update an attribute value
 * @a_name: The attribute name
 * @a_value: The attribute value
 *
 * Sets an attribute to new value
 */
पूर्णांक set_attribute(स्थिर अक्षर *a_name, स्थिर अक्षर *a_value)
अणु
	माप_प्रकार security_area_size, buffer_size;
	माप_प्रकार a_name_size, a_value_size;
	अक्षर *buffer = शून्य, *start;
	पूर्णांक ret;

	mutex_lock(&wmi_priv.mutex);
	अगर (!wmi_priv.bios_attr_wdev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* build/calculate buffer */
	security_area_size = calculate_security_buffer(wmi_priv.current_admin_password);
	a_name_size = calculate_string_buffer(a_name);
	a_value_size = calculate_string_buffer(a_value);
	buffer_size = security_area_size + a_name_size + a_value_size;
	buffer = kzalloc(buffer_size, GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* build security area */
	populate_security_buffer(buffer, wmi_priv.current_admin_password);

	/* build variables to set */
	start = buffer + security_area_size;
	ret = populate_string_buffer(start, a_name_size, a_name);
	अगर (ret < 0)
		जाओ out;
	start += ret;
	ret = populate_string_buffer(start, a_value_size, a_value);
	अगर (ret < 0)
		जाओ out;

	prपूर्णांक_hex_dump_bytes("set attribute data: ", DUMP_PREFIX_NONE, buffer, buffer_size);
	ret = call_biosattributes_पूर्णांकerface(wmi_priv.bios_attr_wdev,
					    buffer, buffer_size,
					    SETATTRIBUTE_METHOD_ID);
	अगर (ret == -EOPNOTSUPP)
		dev_err(&wmi_priv.bios_attr_wdev->dev, "admin password must be configured\n");
	अन्यथा अगर (ret == -EACCES)
		dev_err(&wmi_priv.bios_attr_wdev->dev, "invalid password\n");

out:
	kमुक्त(buffer);
	mutex_unlock(&wmi_priv.mutex);
	वापस ret;
पूर्ण

/**
 * set_bios_शेषs() - Resets BIOS शेषs
 * @deftype: the type of BIOS value reset to issue.
 *
 * Resets BIOS शेषs
 */
पूर्णांक set_bios_शेषs(u8 deftype)
अणु
	माप_प्रकार security_area_size, buffer_size;
	माप_प्रकार पूर्णांकeger_area_size = माप(u8);
	अक्षर *buffer = शून्य;
	u8 *शेषType;
	पूर्णांक ret;

	mutex_lock(&wmi_priv.mutex);
	अगर (!wmi_priv.bios_attr_wdev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	security_area_size = calculate_security_buffer(wmi_priv.current_admin_password);
	buffer_size = security_area_size + पूर्णांकeger_area_size;
	buffer = kzalloc(buffer_size, GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* build security area */
	populate_security_buffer(buffer, wmi_priv.current_admin_password);

	शेषType = buffer + security_area_size;
	*शेषType = deftype;

	ret = call_biosattributes_पूर्णांकerface(wmi_priv.bios_attr_wdev, buffer, buffer_size,
					    SETBIOSDEFAULTS_METHOD_ID);
	अगर (ret)
		dev_err(&wmi_priv.bios_attr_wdev->dev, "reset BIOS defaults failed: %d\n", ret);

	kमुक्त(buffer);
out:
	mutex_unlock(&wmi_priv.mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक bios_attr_set_पूर्णांकerface_probe(काष्ठा wmi_device *wdev, स्थिर व्योम *context)
अणु
	mutex_lock(&wmi_priv.mutex);
	wmi_priv.bios_attr_wdev = wdev;
	mutex_unlock(&wmi_priv.mutex);
	वापस 0;
पूर्ण

अटल व्योम bios_attr_set_पूर्णांकerface_हटाओ(काष्ठा wmi_device *wdev)
अणु
	mutex_lock(&wmi_priv.mutex);
	wmi_priv.bios_attr_wdev = शून्य;
	mutex_unlock(&wmi_priv.mutex);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id bios_attr_set_पूर्णांकerface_id_table[] = अणु
	अणु .guid_string = DELL_WMI_BIOS_ATTRIBUTES_INTERFACE_GUID पूर्ण,
	अणु पूर्ण,
पूर्ण;
अटल काष्ठा wmi_driver bios_attr_set_पूर्णांकerface_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME
	पूर्ण,
	.probe = bios_attr_set_पूर्णांकerface_probe,
	.हटाओ = bios_attr_set_पूर्णांकerface_हटाओ,
	.id_table = bios_attr_set_पूर्णांकerface_id_table,
पूर्ण;

पूर्णांक init_bios_attr_set_पूर्णांकerface(व्योम)
अणु
	वापस wmi_driver_रेजिस्टर(&bios_attr_set_पूर्णांकerface_driver);
पूर्ण

व्योम निकास_bios_attr_set_पूर्णांकerface(व्योम)
अणु
	wmi_driver_unरेजिस्टर(&bios_attr_set_पूर्णांकerface_driver);
पूर्ण

MODULE_DEVICE_TABLE(wmi, bios_attr_set_पूर्णांकerface_id_table);
