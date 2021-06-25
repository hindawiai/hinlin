<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions corresponding to string type attributes under BIOS String GUID क्रम use with
 * dell-wmi-sysman
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#समावेश "dell-wmi-sysman.h"

क्रमागत string_properties अणुMIN_LEN = 6, MAX_LENपूर्ण;

get_instance_id(str);

अटल sमाप_प्रकार current_value_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक instance_id = get_str_instance_id(kobj);
	जोड़ acpi_object *obj;
	sमाप_प्रकार ret;

	अगर (instance_id < 0)
		वापस -EIO;

	/* need to use specअगरic instance_id and guid combination to get right data */
	obj = get_wmiobj_poपूर्णांकer(instance_id, DELL_WMI_BIOS_STRING_ATTRIBUTE_GUID);
	अगर (!obj)
		वापस -EIO;
	अगर (obj->package.elements[CURRENT_VAL].type != ACPI_TYPE_STRING) अणु
		kमुक्त(obj);
		वापस -EINVAL;
	पूर्ण
	ret = snम_लिखो(buf, PAGE_SIZE, "%s\n", obj->package.elements[CURRENT_VAL].string.poपूर्णांकer);
	kमुक्त(obj);
	वापस ret;
पूर्ण

/**
 * validate_str_input() - Validate input of current_value against min and max lengths
 * @instance_id: The instance on which input is validated
 * @buf: Input value
 */
अटल पूर्णांक validate_str_input(पूर्णांक instance_id, स्थिर अक्षर *buf)
अणु
	पूर्णांक in_len = म_माप(buf);

	अगर ((in_len < wmi_priv.str_data[instance_id].min_length) ||
			(in_len > wmi_priv.str_data[instance_id].max_length))
		वापस -EINVAL;

	वापस 0;
पूर्ण

attribute_s_property_show(display_name_language_code, str);
अटल काष्ठा kobj_attribute str_displ_langcode =
		__ATTR_RO(display_name_language_code);

attribute_s_property_show(display_name, str);
अटल काष्ठा kobj_attribute str_displ_name =
		__ATTR_RO(display_name);

attribute_s_property_show(शेष_value, str);
अटल काष्ठा kobj_attribute str_शेष_val =
		__ATTR_RO(शेष_value);

attribute_property_store(current_value, str);
अटल काष्ठा kobj_attribute str_current_val =
		__ATTR_RW_MODE(current_value, 0600);

attribute_s_property_show(dell_modअगरier, str);
अटल काष्ठा kobj_attribute str_modअगरier =
		__ATTR_RO(dell_modअगरier);

attribute_n_property_show(min_length, str);
अटल काष्ठा kobj_attribute str_min_length =
		__ATTR_RO(min_length);

attribute_n_property_show(max_length, str);
अटल काष्ठा kobj_attribute str_max_length =
		__ATTR_RO(max_length);

अटल sमाप_प्रकार type_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "string\n");
पूर्ण
अटल काष्ठा kobj_attribute str_type =
	__ATTR_RO(type);

अटल काष्ठा attribute *str_attrs[] = अणु
	&str_displ_langcode.attr,
	&str_displ_name.attr,
	&str_शेष_val.attr,
	&str_current_val.attr,
	&str_modअगरier.attr,
	&str_min_length.attr,
	&str_max_length.attr,
	&str_type.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group str_attr_group = अणु
	.attrs = str_attrs,
पूर्ण;

पूर्णांक alloc_str_data(व्योम)
अणु
	पूर्णांक ret = 0;

	wmi_priv.str_instances_count = get_instance_count(DELL_WMI_BIOS_STRING_ATTRIBUTE_GUID);
	wmi_priv.str_data = kसुस्मृति(wmi_priv.str_instances_count,
					माप(काष्ठा str_data), GFP_KERNEL);
	अगर (!wmi_priv.str_data) अणु
		wmi_priv.str_instances_count = 0;
		ret = -ENOMEM;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * populate_str_data() - Populate all properties of an instance under string attribute
 * @str_obj: ACPI object with पूर्णांकeger data
 * @instance_id: The instance to क्रमागतerate
 * @attr_name_kobj: The parent kernel object
 */
पूर्णांक populate_str_data(जोड़ acpi_object *str_obj, पूर्णांक instance_id, काष्ठा kobject *attr_name_kobj)
अणु
	wmi_priv.str_data[instance_id].attr_name_kobj = attr_name_kobj;
	strlcpy_attr(wmi_priv.str_data[instance_id].attribute_name,
		     str_obj[ATTR_NAME].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.str_data[instance_id].display_name_language_code,
		     str_obj[DISPL_NAME_LANG_CODE].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.str_data[instance_id].display_name,
		     str_obj[DISPLAY_NAME].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.str_data[instance_id].शेष_value,
		     str_obj[DEFAULT_VAL].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.str_data[instance_id].dell_modअगरier,
		     str_obj[MODIFIER].string.poपूर्णांकer);
	wmi_priv.str_data[instance_id].min_length = (uपूर्णांकptr_t)str_obj[MIN_LEN].string.poपूर्णांकer;
	wmi_priv.str_data[instance_id].max_length = (uपूर्णांकptr_t) str_obj[MAX_LEN].string.poपूर्णांकer;

	वापस sysfs_create_group(attr_name_kobj, &str_attr_group);
पूर्ण

/**
 * निकास_str_attributes() - Clear all attribute data
 *
 * Clears all data allocated क्रम this group of attributes
 */
व्योम निकास_str_attributes(व्योम)
अणु
	पूर्णांक instance_id;

	क्रम (instance_id = 0; instance_id < wmi_priv.str_instances_count; instance_id++) अणु
		अगर (wmi_priv.str_data[instance_id].attr_name_kobj)
			sysfs_हटाओ_group(wmi_priv.str_data[instance_id].attr_name_kobj,
								&str_attr_group);
	पूर्ण
	wmi_priv.str_instances_count = 0;

	kमुक्त(wmi_priv.str_data);
	wmi_priv.str_data = शून्य;
पूर्ण
