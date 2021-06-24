<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions corresponding to SET password methods under BIOS attributes पूर्णांकerface GUID
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#समावेश <linux/wmi.h>
#समावेश "dell-wmi-sysman.h"

अटल पूर्णांक call_password_पूर्णांकerface(काष्ठा wmi_device *wdev, अक्षर *in_args, माप_प्रकार size)
अणु
	काष्ठा acpi_buffer output = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;
	काष्ठा acpi_buffer input;
	जोड़ acpi_object *obj;
	acpi_status status;
	पूर्णांक ret = -EIO;

	input.length =  (acpi_size) size;
	input.poपूर्णांकer = in_args;
	status = wmidev_evaluate_method(wdev, 0, 1, &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;
	obj = (जोड़ acpi_object *)output.poपूर्णांकer;
	अगर (obj->type == ACPI_TYPE_INTEGER)
		ret = obj->पूर्णांकeger.value;

	kमुक्त(output.poपूर्णांकer);
	/* let userland know it may need to check is_password_set again */
	kobject_uevent(&wmi_priv.class_dev->kobj, KOBJ_CHANGE);
	वापस map_wmi_error(ret);
पूर्ण

/**
 * set_new_password() - Sets a प्रणाली admin password
 * @password_type: The type of password to set
 * @new: The new password
 *
 * Sets the password using plaपूर्णांकext पूर्णांकerface
 */
पूर्णांक set_new_password(स्थिर अक्षर *password_type, स्थिर अक्षर *new)
अणु
	माप_प्रकार password_type_size, current_password_size, new_size;
	माप_प्रकार security_area_size, buffer_size;
	अक्षर *buffer = शून्य, *start;
	अक्षर *current_password;
	पूर्णांक ret;

	mutex_lock(&wmi_priv.mutex);
	अगर (!wmi_priv.password_attr_wdev) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण
	अगर (म_भेद(password_type, "Admin") == 0) अणु
		current_password = wmi_priv.current_admin_password;
	पूर्ण अन्यथा अगर (म_भेद(password_type, "System") == 0) अणु
		current_password = wmi_priv.current_प्रणाली_password;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		dev_err(&wmi_priv.password_attr_wdev->dev, "unknown password type %s\n",
			password_type);
		जाओ out;
	पूर्ण

	/* build/calculate buffer */
	security_area_size = calculate_security_buffer(wmi_priv.current_admin_password);
	password_type_size = calculate_string_buffer(password_type);
	current_password_size = calculate_string_buffer(current_password);
	new_size = calculate_string_buffer(new);
	buffer_size = security_area_size + password_type_size + current_password_size + new_size;
	buffer = kzalloc(buffer_size, GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/* build security area */
	populate_security_buffer(buffer, wmi_priv.current_admin_password);

	/* build variables to set */
	start = buffer + security_area_size;
	ret = populate_string_buffer(start, password_type_size, password_type);
	अगर (ret < 0)
		जाओ out;

	start += ret;
	ret = populate_string_buffer(start, current_password_size, current_password);
	अगर (ret < 0)
		जाओ out;

	start += ret;
	ret = populate_string_buffer(start, new_size, new);
	अगर (ret < 0)
		जाओ out;

	prपूर्णांक_hex_dump_bytes("set new password data: ", DUMP_PREFIX_NONE, buffer, buffer_size);
	ret = call_password_पूर्णांकerface(wmi_priv.password_attr_wdev, buffer, buffer_size);
	/* clear current_password here and use user input from wmi_priv.current_password */
	अगर (!ret)
		स_रखो(current_password, 0, MAX_BUFF);
	/* explain to user the detailed failure reason */
	अन्यथा अगर (ret == -EOPNOTSUPP)
		dev_err(&wmi_priv.password_attr_wdev->dev, "admin password must be configured\n");
	अन्यथा अगर (ret == -EACCES)
		dev_err(&wmi_priv.password_attr_wdev->dev, "invalid password\n");

out:
	kमुक्त(buffer);
	mutex_unlock(&wmi_priv.mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक bios_attr_pass_पूर्णांकerface_probe(काष्ठा wmi_device *wdev, स्थिर व्योम *context)
अणु
	mutex_lock(&wmi_priv.mutex);
	wmi_priv.password_attr_wdev = wdev;
	mutex_unlock(&wmi_priv.mutex);
	वापस 0;
पूर्ण

अटल व्योम bios_attr_pass_पूर्णांकerface_हटाओ(काष्ठा wmi_device *wdev)
अणु
	mutex_lock(&wmi_priv.mutex);
	wmi_priv.password_attr_wdev = शून्य;
	mutex_unlock(&wmi_priv.mutex);
पूर्ण

अटल स्थिर काष्ठा wmi_device_id bios_attr_pass_पूर्णांकerface_id_table[] = अणु
	अणु .guid_string = DELL_WMI_BIOS_PASSWORD_INTERFACE_GUID पूर्ण,
	अणु पूर्ण,
पूर्ण;
अटल काष्ठा wmi_driver bios_attr_pass_पूर्णांकerface_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME"-password"
	पूर्ण,
	.probe = bios_attr_pass_पूर्णांकerface_probe,
	.हटाओ = bios_attr_pass_पूर्णांकerface_हटाओ,
	.id_table = bios_attr_pass_पूर्णांकerface_id_table,
पूर्ण;

पूर्णांक init_bios_attr_pass_पूर्णांकerface(व्योम)
अणु
	वापस wmi_driver_रेजिस्टर(&bios_attr_pass_पूर्णांकerface_driver);
पूर्ण

व्योम निकास_bios_attr_pass_पूर्णांकerface(व्योम)
अणु
	wmi_driver_unरेजिस्टर(&bios_attr_pass_पूर्णांकerface_driver);
पूर्ण

MODULE_DEVICE_TABLE(wmi, bios_attr_pass_पूर्णांकerface_id_table);
