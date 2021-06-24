<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 * Definitions क्रम kernel modules using Dell WMI System Management Driver
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#अगर_अघोषित _DELL_WMI_BIOS_ATTR_H_
#घोषणा _DELL_WMI_BIOS_ATTR_H_

#समावेश <linux/wmi.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/capability.h>

#घोषणा DRIVER_NAME					"dell-wmi-sysman"
#घोषणा MAX_BUFF  512

#घोषणा DELL_WMI_BIOS_ENUMERATION_ATTRIBUTE_GUID	"F1DDEE52-063C-4784-A11E-8A06684B9BF5"
#घोषणा DELL_WMI_BIOS_INTEGER_ATTRIBUTE_GUID		"F1DDEE52-063C-4784-A11E-8A06684B9BFA"
#घोषणा DELL_WMI_BIOS_STRING_ATTRIBUTE_GUID		"F1DDEE52-063C-4784-A11E-8A06684B9BF9"
#घोषणा DELL_WMI_BIOS_PASSOBJ_ATTRIBUTE_GUID		"0894B8D6-44A6-4719-97D7-6AD24108BFD4"
#घोषणा DELL_WMI_BIOS_ATTRIBUTES_INTERFACE_GUID		"F1DDEE52-063C-4784-A11E-8A06684B9BF4"
#घोषणा DELL_WMI_BIOS_PASSWORD_INTERFACE_GUID		"70FE8229-D03B-4214-A1C6-1F884B1A892A"

काष्ठा क्रमागतeration_data अणु
	काष्ठा kobject *attr_name_kobj;
	अक्षर display_name_language_code[MAX_BUFF];
	अक्षर dell_value_modअगरier[MAX_BUFF];
	अक्षर possible_values[MAX_BUFF];
	अक्षर attribute_name[MAX_BUFF];
	अक्षर शेष_value[MAX_BUFF];
	अक्षर dell_modअगरier[MAX_BUFF];
	अक्षर display_name[MAX_BUFF];
पूर्ण;

काष्ठा पूर्णांकeger_data अणु
	काष्ठा kobject *attr_name_kobj;
	अक्षर display_name_language_code[MAX_BUFF];
	अक्षर attribute_name[MAX_BUFF];
	अक्षर dell_modअगरier[MAX_BUFF];
	अक्षर display_name[MAX_BUFF];
	पूर्णांक scalar_increment;
	पूर्णांक शेष_value;
	पूर्णांक min_value;
	पूर्णांक max_value;
पूर्ण;

काष्ठा str_data अणु
	काष्ठा kobject *attr_name_kobj;
	अक्षर display_name_language_code[MAX_BUFF];
	अक्षर attribute_name[MAX_BUFF];
	अक्षर display_name[MAX_BUFF];
	अक्षर शेष_value[MAX_BUFF];
	अक्षर dell_modअगरier[MAX_BUFF];
	पूर्णांक min_length;
	पूर्णांक max_length;
पूर्ण;

काष्ठा po_data अणु
	काष्ठा kobject *attr_name_kobj;
	अक्षर attribute_name[MAX_BUFF];
	पूर्णांक min_password_length;
	पूर्णांक max_password_length;
पूर्ण;

काष्ठा wmi_sysman_priv अणु
	अक्षर current_admin_password[MAX_BUFF];
	अक्षर current_प्रणाली_password[MAX_BUFF];
	काष्ठा wmi_device *password_attr_wdev;
	काष्ठा wmi_device *bios_attr_wdev;
	काष्ठा kset *authentication_dir_kset;
	काष्ठा kset *मुख्य_dir_kset;
	काष्ठा device *class_dev;
	काष्ठा क्रमागतeration_data *क्रमागतeration_data;
	पूर्णांक क्रमागतeration_instances_count;
	काष्ठा पूर्णांकeger_data *पूर्णांकeger_data;
	पूर्णांक पूर्णांकeger_instances_count;
	काष्ठा str_data *str_data;
	पूर्णांक str_instances_count;
	काष्ठा po_data *po_data;
	पूर्णांक po_instances_count;
	bool pending_changes;
	काष्ठा mutex mutex;
पूर्ण;

/* global काष्ठाure used by multiple WMI पूर्णांकerfaces */
बाह्य काष्ठा wmi_sysman_priv wmi_priv;

क्रमागत अणु ENUM, INT, STR, PO पूर्ण;

क्रमागत अणु
	ATTR_NAME,
	DISPL_NAME_LANG_CODE,
	DISPLAY_NAME,
	DEFAULT_VAL,
	CURRENT_VAL,
	MODIFIER
पूर्ण;

#घोषणा get_instance_id(type)							\
अटल पूर्णांक get_##type##_instance_id(काष्ठा kobject *kobj)			\
अणु										\
	पूर्णांक i;									\
	क्रम (i = 0; i <= wmi_priv.type##_instances_count; i++) अणु		\
		अगर (!(म_भेद(kobj->name, wmi_priv.type##_data[i].attribute_name)))\
			वापस i;						\
	पूर्ण									\
	वापस -EIO;								\
पूर्ण

#घोषणा attribute_s_property_show(name, type)					\
अटल sमाप_प्रकार name##_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,	\
			   अक्षर *buf)						\
अणु										\
	पूर्णांक i = get_##type##_instance_id(kobj);					\
	अगर (i >= 0)								\
		वापस प्र_लिखो(buf, "%s\n", wmi_priv.type##_data[i].name);	\
	वापस 0;								\
पूर्ण

#घोषणा attribute_n_property_show(name, type)					\
अटल sमाप_प्रकार name##_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,	\
			   अक्षर *buf)						\
अणु										\
	पूर्णांक i = get_##type##_instance_id(kobj);					\
	अगर (i >= 0)								\
		वापस प्र_लिखो(buf, "%d\n", wmi_priv.type##_data[i].name);	\
	वापस 0;								\
पूर्ण

#घोषणा attribute_property_store(curr_val, type)				\
अटल sमाप_प्रकार curr_val##_store(काष्ठा kobject *kobj,				\
				काष्ठा kobj_attribute *attr,			\
				स्थिर अक्षर *buf, माप_प्रकार count)			\
अणु										\
	अक्षर *p, *buf_cp;							\
	पूर्णांक i, ret = -EIO;							\
	buf_cp = kstrdup(buf, GFP_KERNEL);					\
	अगर (!buf_cp)								\
		वापस -ENOMEM;							\
	p = स_प्रथम(buf_cp, '\n', count);					\
										\
	अगर (p != शून्य)								\
		*p = '\0';							\
	i = get_##type##_instance_id(kobj);					\
	अगर (i >= 0)								\
		ret = validate_##type##_input(i, buf_cp);			\
	अगर (!ret)								\
		ret = set_attribute(kobj->name, buf_cp);			\
	kमुक्त(buf_cp);								\
	वापस ret ? ret : count;						\
पूर्ण

जोड़ acpi_object *get_wmiobj_poपूर्णांकer(पूर्णांक instance_id, स्थिर अक्षर *guid_string);
पूर्णांक get_instance_count(स्थिर अक्षर *guid_string);
व्योम strlcpy_attr(अक्षर *dest, अक्षर *src);

पूर्णांक populate_क्रमागत_data(जोड़ acpi_object *क्रमागतeration_obj, पूर्णांक instance_id,
			काष्ठा kobject *attr_name_kobj);
पूर्णांक alloc_क्रमागत_data(व्योम);
व्योम निकास_क्रमागत_attributes(व्योम);

पूर्णांक populate_पूर्णांक_data(जोड़ acpi_object *पूर्णांकeger_obj, पूर्णांक instance_id,
			काष्ठा kobject *attr_name_kobj);
पूर्णांक alloc_पूर्णांक_data(व्योम);
व्योम निकास_पूर्णांक_attributes(व्योम);

पूर्णांक populate_str_data(जोड़ acpi_object *str_obj, पूर्णांक instance_id, काष्ठा kobject *attr_name_kobj);
पूर्णांक alloc_str_data(व्योम);
व्योम निकास_str_attributes(व्योम);

पूर्णांक populate_po_data(जोड़ acpi_object *po_obj, पूर्णांक instance_id, काष्ठा kobject *attr_name_kobj);
पूर्णांक alloc_po_data(व्योम);
व्योम निकास_po_attributes(व्योम);

पूर्णांक set_attribute(स्थिर अक्षर *a_name, स्थिर अक्षर *a_value);
पूर्णांक set_bios_शेषs(u8 defType);

व्योम निकास_bios_attr_set_पूर्णांकerface(व्योम);
पूर्णांक init_bios_attr_set_पूर्णांकerface(व्योम);
पूर्णांक map_wmi_error(पूर्णांक error_code);
माप_प्रकार calculate_string_buffer(स्थिर अक्षर *str);
माप_प्रकार calculate_security_buffer(अक्षर *authentication);
व्योम populate_security_buffer(अक्षर *buffer, अक्षर *authentication);
sमाप_प्रकार populate_string_buffer(अक्षर *buffer, माप_प्रकार buffer_len, स्थिर अक्षर *str);
पूर्णांक set_new_password(स्थिर अक्षर *password_type, स्थिर अक्षर *new);
पूर्णांक init_bios_attr_pass_पूर्णांकerface(व्योम);
व्योम निकास_bios_attr_pass_पूर्णांकerface(व्योम);

#पूर्ण_अगर
