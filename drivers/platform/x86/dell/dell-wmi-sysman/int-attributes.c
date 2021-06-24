<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions corresponding to पूर्णांकeger type attributes under BIOS Integer GUID क्रम use with
 * dell-wmi-sysman
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#समावेश "dell-wmi-sysman.h"

क्रमागत पूर्णांक_properties अणुMIN_VALUE = 6, MAX_VALUE, SCALAR_INCRपूर्ण;

get_instance_id(पूर्णांकeger);

अटल sमाप_प्रकार current_value_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक instance_id = get_पूर्णांकeger_instance_id(kobj);
	जोड़ acpi_object *obj;
	sमाप_प्रकार ret;

	अगर (instance_id < 0)
		वापस instance_id;

	/* need to use specअगरic instance_id and guid combination to get right data */
	obj = get_wmiobj_poपूर्णांकer(instance_id, DELL_WMI_BIOS_INTEGER_ATTRIBUTE_GUID);
	अगर (!obj)
		वापस -EIO;
	अगर (obj->package.elements[CURRENT_VAL].type != ACPI_TYPE_INTEGER) अणु
		kमुक्त(obj);
		वापस -EINVAL;
	पूर्ण
	ret = snम_लिखो(buf, PAGE_SIZE, "%lld\n", obj->package.elements[CURRENT_VAL].पूर्णांकeger.value);
	kमुक्त(obj);
	वापस ret;
पूर्ण

/**
 * validate_पूर्णांकeger_input() - Validate input of current_value against lower and upper bound
 * @instance_id: The instance on which input is validated
 * @buf: Input value
 */
अटल पूर्णांक validate_पूर्णांकeger_input(पूर्णांक instance_id, अक्षर *buf)
अणु
	पूर्णांक in_val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक(buf, 0, &in_val);
	अगर (ret)
		वापस ret;
	अगर (in_val < wmi_priv.पूर्णांकeger_data[instance_id].min_value ||
			in_val > wmi_priv.पूर्णांकeger_data[instance_id].max_value)
		वापस -EINVAL;

	/* workaround क्रम BIOS error.
	 * validate input to aव्योम setting 0 when पूर्णांकeger input passed with + sign
	 */
	अगर (*buf == '+')
		स_हटाओ(buf, (buf + 1), म_माप(buf + 1) + 1);

	वापस ret;
पूर्ण

attribute_s_property_show(display_name_language_code, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_displ_langcode =
	__ATTR_RO(display_name_language_code);

attribute_s_property_show(display_name, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_displ_name =
	__ATTR_RO(display_name);

attribute_n_property_show(शेष_value, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_शेष_val =
	__ATTR_RO(शेष_value);

attribute_property_store(current_value, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_current_val =
	__ATTR_RW_MODE(current_value, 0600);

attribute_s_property_show(dell_modअगरier, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_modअगरier =
	__ATTR_RO(dell_modअगरier);

attribute_n_property_show(min_value, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_lower_bound =
	__ATTR_RO(min_value);

attribute_n_property_show(max_value, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_upper_bound =
	__ATTR_RO(max_value);

attribute_n_property_show(scalar_increment, पूर्णांकeger);
अटल काष्ठा kobj_attribute पूर्णांकeger_scalar_increment =
	__ATTR_RO(scalar_increment);

अटल sमाप_प्रकार type_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "integer\n");
पूर्ण
अटल काष्ठा kobj_attribute पूर्णांकeger_type =
	__ATTR_RO(type);

अटल काष्ठा attribute *पूर्णांकeger_attrs[] = अणु
	&पूर्णांकeger_displ_langcode.attr,
	&पूर्णांकeger_displ_name.attr,
	&पूर्णांकeger_शेष_val.attr,
	&पूर्णांकeger_current_val.attr,
	&पूर्णांकeger_modअगरier.attr,
	&पूर्णांकeger_lower_bound.attr,
	&पूर्णांकeger_upper_bound.attr,
	&पूर्णांकeger_scalar_increment.attr,
	&पूर्णांकeger_type.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group पूर्णांकeger_attr_group = अणु
	.attrs = पूर्णांकeger_attrs,
पूर्ण;

पूर्णांक alloc_पूर्णांक_data(व्योम)
अणु
	पूर्णांक ret = 0;

	wmi_priv.पूर्णांकeger_instances_count = get_instance_count(DELL_WMI_BIOS_INTEGER_ATTRIBUTE_GUID);
	wmi_priv.पूर्णांकeger_data = kसुस्मृति(wmi_priv.पूर्णांकeger_instances_count,
					माप(काष्ठा पूर्णांकeger_data), GFP_KERNEL);
	अगर (!wmi_priv.पूर्णांकeger_data) अणु
		wmi_priv.पूर्णांकeger_instances_count = 0;
		ret = -ENOMEM;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * populate_पूर्णांक_data() - Populate all properties of an instance under पूर्णांकeger attribute
 * @पूर्णांकeger_obj: ACPI object with पूर्णांकeger data
 * @instance_id: The instance to क्रमागतerate
 * @attr_name_kobj: The parent kernel object
 */
पूर्णांक populate_पूर्णांक_data(जोड़ acpi_object *पूर्णांकeger_obj, पूर्णांक instance_id,
			काष्ठा kobject *attr_name_kobj)
अणु
	wmi_priv.पूर्णांकeger_data[instance_id].attr_name_kobj = attr_name_kobj;
	strlcpy_attr(wmi_priv.पूर्णांकeger_data[instance_id].attribute_name,
		पूर्णांकeger_obj[ATTR_NAME].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.पूर्णांकeger_data[instance_id].display_name_language_code,
		पूर्णांकeger_obj[DISPL_NAME_LANG_CODE].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.पूर्णांकeger_data[instance_id].display_name,
		पूर्णांकeger_obj[DISPLAY_NAME].string.poपूर्णांकer);
	wmi_priv.पूर्णांकeger_data[instance_id].शेष_value =
		(uपूर्णांकptr_t)पूर्णांकeger_obj[DEFAULT_VAL].string.poपूर्णांकer;
	strlcpy_attr(wmi_priv.पूर्णांकeger_data[instance_id].dell_modअगरier,
		पूर्णांकeger_obj[MODIFIER].string.poपूर्णांकer);
	wmi_priv.पूर्णांकeger_data[instance_id].min_value =
		(uपूर्णांकptr_t)पूर्णांकeger_obj[MIN_VALUE].string.poपूर्णांकer;
	wmi_priv.पूर्णांकeger_data[instance_id].max_value =
		(uपूर्णांकptr_t)पूर्णांकeger_obj[MAX_VALUE].string.poपूर्णांकer;
	wmi_priv.पूर्णांकeger_data[instance_id].scalar_increment =
		(uपूर्णांकptr_t)पूर्णांकeger_obj[SCALAR_INCR].string.poपूर्णांकer;

	वापस sysfs_create_group(attr_name_kobj, &पूर्णांकeger_attr_group);
पूर्ण

/**
 * निकास_पूर्णांक_attributes() - Clear all attribute data
 *
 * Clears all data allocated क्रम this group of attributes
 */
व्योम निकास_पूर्णांक_attributes(व्योम)
अणु
	पूर्णांक instance_id;

	क्रम (instance_id = 0; instance_id < wmi_priv.पूर्णांकeger_instances_count; instance_id++) अणु
		अगर (wmi_priv.पूर्णांकeger_data[instance_id].attr_name_kobj)
			sysfs_हटाओ_group(wmi_priv.पूर्णांकeger_data[instance_id].attr_name_kobj,
								&पूर्णांकeger_attr_group);
	पूर्ण
	wmi_priv.पूर्णांकeger_instances_count = 0;

	kमुक्त(wmi_priv.पूर्णांकeger_data);
	wmi_priv.पूर्णांकeger_data = शून्य;
पूर्ण
