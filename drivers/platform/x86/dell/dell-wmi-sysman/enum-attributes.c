<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions corresponding to क्रमागतeration type attributes under
 * BIOS Enumeration GUID क्रम use with dell-wmi-sysman
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#समावेश "dell-wmi-sysman.h"

get_instance_id(क्रमागतeration);

अटल sमाप_प्रकार current_value_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक instance_id = get_क्रमागतeration_instance_id(kobj);
	जोड़ acpi_object *obj;
	sमाप_प्रकार ret;

	अगर (instance_id < 0)
		वापस instance_id;

	/* need to use specअगरic instance_id and guid combination to get right data */
	obj = get_wmiobj_poपूर्णांकer(instance_id, DELL_WMI_BIOS_ENUMERATION_ATTRIBUTE_GUID);
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
 * validate_क्रमागतeration_input() - Validate input of current_value against possible values
 * @instance_id: The instance on which input is validated
 * @buf: Input value
 */
अटल पूर्णांक validate_क्रमागतeration_input(पूर्णांक instance_id, स्थिर अक्षर *buf)
अणु
	अक्षर *options, *पंचांगp, *p;
	पूर्णांक ret = -EINVAL;

	options = पंचांगp = kstrdup(wmi_priv.क्रमागतeration_data[instance_id].possible_values,
				 GFP_KERNEL);
	अगर (!options)
		वापस -ENOMEM;

	जबतक ((p = strsep(&options, ";")) != शून्य) अणु
		अगर (!*p)
			जारी;
		अगर (!strहालcmp(p, buf)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

attribute_s_property_show(display_name_language_code, क्रमागतeration);
अटल काष्ठा kobj_attribute displ_langcode =
		__ATTR_RO(display_name_language_code);

attribute_s_property_show(display_name, क्रमागतeration);
अटल काष्ठा kobj_attribute displ_name =
		__ATTR_RO(display_name);

attribute_s_property_show(शेष_value, क्रमागतeration);
अटल काष्ठा kobj_attribute शेष_val =
		__ATTR_RO(शेष_value);

attribute_property_store(current_value, क्रमागतeration);
अटल काष्ठा kobj_attribute current_val =
		__ATTR_RW_MODE(current_value, 0600);

attribute_s_property_show(dell_modअगरier, क्रमागतeration);
अटल काष्ठा kobj_attribute modअगरier =
		__ATTR_RO(dell_modअगरier);

attribute_s_property_show(dell_value_modअगरier, क्रमागतeration);
अटल काष्ठा kobj_attribute value_modfr =
		__ATTR_RO(dell_value_modअगरier);

attribute_s_property_show(possible_values, क्रमागतeration);
अटल काष्ठा kobj_attribute poss_val =
		__ATTR_RO(possible_values);

अटल sमाप_प्रकार type_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "enumeration\n");
पूर्ण
अटल काष्ठा kobj_attribute type =
		__ATTR_RO(type);

अटल काष्ठा attribute *क्रमागतeration_attrs[] = अणु
	&displ_langcode.attr,
	&displ_name.attr,
	&शेष_val.attr,
	&current_val.attr,
	&modअगरier.attr,
	&value_modfr.attr,
	&poss_val.attr,
	&type.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group क्रमागतeration_attr_group = अणु
	.attrs = क्रमागतeration_attrs,
पूर्ण;

पूर्णांक alloc_क्रमागत_data(व्योम)
अणु
	पूर्णांक ret = 0;

	wmi_priv.क्रमागतeration_instances_count =
		get_instance_count(DELL_WMI_BIOS_ENUMERATION_ATTRIBUTE_GUID);
	wmi_priv.क्रमागतeration_data = kसुस्मृति(wmi_priv.क्रमागतeration_instances_count,
					माप(काष्ठा क्रमागतeration_data), GFP_KERNEL);
	अगर (!wmi_priv.क्रमागतeration_data) अणु
		wmi_priv.क्रमागतeration_instances_count = 0;
		ret = -ENOMEM;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * populate_क्रमागत_data() - Populate all properties of an instance under क्रमागतeration attribute
 * @क्रमागतeration_obj: ACPI object with क्रमागतeration data
 * @instance_id: The instance to क्रमागतerate
 * @attr_name_kobj: The parent kernel object
 */
पूर्णांक populate_क्रमागत_data(जोड़ acpi_object *क्रमागतeration_obj, पूर्णांक instance_id,
			काष्ठा kobject *attr_name_kobj)
अणु
	पूर्णांक i, next_obj, value_modअगरier_count, possible_values_count;

	wmi_priv.क्रमागतeration_data[instance_id].attr_name_kobj = attr_name_kobj;
	strlcpy_attr(wmi_priv.क्रमागतeration_data[instance_id].attribute_name,
		क्रमागतeration_obj[ATTR_NAME].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.क्रमागतeration_data[instance_id].display_name_language_code,
		क्रमागतeration_obj[DISPL_NAME_LANG_CODE].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.क्रमागतeration_data[instance_id].display_name,
		क्रमागतeration_obj[DISPLAY_NAME].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.क्रमागतeration_data[instance_id].शेष_value,
		क्रमागतeration_obj[DEFAULT_VAL].string.poपूर्णांकer);
	strlcpy_attr(wmi_priv.क्रमागतeration_data[instance_id].dell_modअगरier,
		क्रमागतeration_obj[MODIFIER].string.poपूर्णांकer);

	next_obj = MODIFIER + 1;

	value_modअगरier_count = (uपूर्णांकptr_t)क्रमागतeration_obj[next_obj].string.poपूर्णांकer;

	क्रम (i = 0; i < value_modअगरier_count; i++) अणु
		म_जोड़ो(wmi_priv.क्रमागतeration_data[instance_id].dell_value_modअगरier,
			क्रमागतeration_obj[++next_obj].string.poपूर्णांकer);
		म_जोड़ो(wmi_priv.क्रमागतeration_data[instance_id].dell_value_modअगरier, ";");
	पूर्ण

	possible_values_count = (uपूर्णांकptr_t) क्रमागतeration_obj[++next_obj].string.poपूर्णांकer;

	क्रम (i = 0; i < possible_values_count; i++) अणु
		म_जोड़ो(wmi_priv.क्रमागतeration_data[instance_id].possible_values,
			क्रमागतeration_obj[++next_obj].string.poपूर्णांकer);
		म_जोड़ो(wmi_priv.क्रमागतeration_data[instance_id].possible_values, ";");
	पूर्ण

	वापस sysfs_create_group(attr_name_kobj, &क्रमागतeration_attr_group);
पूर्ण

/**
 * निकास_क्रमागत_attributes() - Clear all attribute data
 *
 * Clears all data allocated क्रम this group of attributes
 */
व्योम निकास_क्रमागत_attributes(व्योम)
अणु
	पूर्णांक instance_id;

	क्रम (instance_id = 0; instance_id < wmi_priv.क्रमागतeration_instances_count; instance_id++) अणु
		अगर (wmi_priv.क्रमागतeration_data[instance_id].attr_name_kobj)
			sysfs_हटाओ_group(wmi_priv.क्रमागतeration_data[instance_id].attr_name_kobj,
								&क्रमागतeration_attr_group);
	पूर्ण
	wmi_priv.क्रमागतeration_instances_count = 0;

	kमुक्त(wmi_priv.क्रमागतeration_data);
	wmi_priv.क्रमागतeration_data = शून्य;
पूर्ण
