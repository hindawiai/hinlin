<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions corresponding to password object type attributes under BIOS Password Object GUID क्रम
 * use with dell-wmi-sysman
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#समावेश "dell-wmi-sysman.h"

क्रमागत po_properties अणुIS_PASS_SET = 1, MIN_PASS_LEN, MAX_PASS_LENपूर्ण;

get_instance_id(po);

अटल sमाप_प्रकार is_enabled_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
					  अक्षर *buf)
अणु
	पूर्णांक instance_id = get_po_instance_id(kobj);
	जोड़ acpi_object *obj;
	sमाप_प्रकार ret;

	अगर (instance_id < 0)
		वापस instance_id;

	/* need to use specअगरic instance_id and guid combination to get right data */
	obj = get_wmiobj_poपूर्णांकer(instance_id, DELL_WMI_BIOS_PASSOBJ_ATTRIBUTE_GUID);
	अगर (!obj)
		वापस -EIO;
	अगर (obj->package.elements[IS_PASS_SET].type != ACPI_TYPE_INTEGER) अणु
		kमुक्त(obj);
		वापस -EINVAL;
	पूर्ण
	ret = snम_लिखो(buf, PAGE_SIZE, "%lld\n", obj->package.elements[IS_PASS_SET].पूर्णांकeger.value);
	kमुक्त(obj);
	वापस ret;
पूर्ण

अटल काष्ठा kobj_attribute po_is_pass_set = __ATTR_RO(is_enabled);

अटल sमाप_प्रकार current_password_store(काष्ठा kobject *kobj,
				      काष्ठा kobj_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर *target = शून्य;
	पूर्णांक length;

	length = म_माप(buf);
	अगर (buf[length-1] == '\n')
		length--;

	/* firmware करोes verअगरiation of min/max password length,
	 * hence only check क्रम not exceeding MAX_BUFF here.
	 */
	अगर (length >= MAX_BUFF)
		वापस -EINVAL;

	अगर (म_भेद(kobj->name, "Admin") == 0)
		target = wmi_priv.current_admin_password;
	अन्यथा अगर (म_भेद(kobj->name, "System") == 0)
		target = wmi_priv.current_प्रणाली_password;
	अगर (!target)
		वापस -EIO;
	स_नकल(target, buf, length);
	target[length] = '\0';

	वापस count;
पूर्ण

अटल काष्ठा kobj_attribute po_current_password = __ATTR_WO(current_password);

अटल sमाप_प्रकार new_password_store(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर *p, *buf_cp;
	पूर्णांक ret;

	buf_cp = kstrdup(buf, GFP_KERNEL);
	अगर (!buf_cp)
		वापस -ENOMEM;
	p = स_प्रथम(buf_cp, '\n', count);

	अगर (p != शून्य)
		*p = '\0';
	अगर (म_माप(buf_cp) > MAX_BUFF) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = set_new_password(kobj->name, buf_cp);

out:
	kमुक्त(buf_cp);
	वापस ret ? ret : count;
पूर्ण

अटल काष्ठा kobj_attribute po_new_password = __ATTR_WO(new_password);

attribute_n_property_show(min_password_length, po);
अटल काष्ठा kobj_attribute po_min_pass_length = __ATTR_RO(min_password_length);

attribute_n_property_show(max_password_length, po);
अटल काष्ठा kobj_attribute po_max_pass_length = __ATTR_RO(max_password_length);

अटल sमाप_प्रकार mechanism_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "password\n");
पूर्ण

अटल काष्ठा kobj_attribute po_mechanism = __ATTR_RO(mechanism);

अटल sमाप_प्रकार role_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	अगर (म_भेद(kobj->name, "Admin") == 0)
		वापस प्र_लिखो(buf, "bios-admin\n");
	अन्यथा अगर (म_भेद(kobj->name, "System") == 0)
		वापस प्र_लिखो(buf, "power-on\n");
	वापस -EIO;
पूर्ण

अटल काष्ठा kobj_attribute po_role = __ATTR_RO(role);

अटल काष्ठा attribute *po_attrs[] = अणु
	&po_is_pass_set.attr,
	&po_min_pass_length.attr,
	&po_max_pass_length.attr,
	&po_current_password.attr,
	&po_new_password.attr,
	&po_role.attr,
	&po_mechanism.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group po_attr_group = अणु
	.attrs = po_attrs,
पूर्ण;

पूर्णांक alloc_po_data(व्योम)
अणु
	पूर्णांक ret = 0;

	wmi_priv.po_instances_count = get_instance_count(DELL_WMI_BIOS_PASSOBJ_ATTRIBUTE_GUID);
	wmi_priv.po_data = kसुस्मृति(wmi_priv.po_instances_count, माप(काष्ठा po_data), GFP_KERNEL);
	अगर (!wmi_priv.po_data) अणु
		wmi_priv.po_instances_count = 0;
		ret = -ENOMEM;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * populate_po_data() - Populate all properties of an instance under password object attribute
 * @po_obj: ACPI object with password object data
 * @instance_id: The instance to क्रमागतerate
 * @attr_name_kobj: The parent kernel object
 */
पूर्णांक populate_po_data(जोड़ acpi_object *po_obj, पूर्णांक instance_id, काष्ठा kobject *attr_name_kobj)
अणु
	wmi_priv.po_data[instance_id].attr_name_kobj = attr_name_kobj;
	strlcpy_attr(wmi_priv.po_data[instance_id].attribute_name,
		     po_obj[ATTR_NAME].string.poपूर्णांकer);
	wmi_priv.po_data[instance_id].min_password_length =
		(uपूर्णांकptr_t)po_obj[MIN_PASS_LEN].string.poपूर्णांकer;
	wmi_priv.po_data[instance_id].max_password_length =
		(uपूर्णांकptr_t) po_obj[MAX_PASS_LEN].string.poपूर्णांकer;

	वापस sysfs_create_group(attr_name_kobj, &po_attr_group);
पूर्ण

/**
 * निकास_po_attributes() - Clear all attribute data
 *
 * Clears all data allocated क्रम this group of attributes
 */
व्योम निकास_po_attributes(व्योम)
अणु
	पूर्णांक instance_id;

	क्रम (instance_id = 0; instance_id < wmi_priv.po_instances_count; instance_id++) अणु
		अगर (wmi_priv.po_data[instance_id].attr_name_kobj)
			sysfs_हटाओ_group(wmi_priv.po_data[instance_id].attr_name_kobj,
								&po_attr_group);
	पूर्ण
	wmi_priv.po_instances_count = 0;

	kमुक्त(wmi_priv.po_data);
	wmi_priv.po_data = शून्य;
पूर्ण
