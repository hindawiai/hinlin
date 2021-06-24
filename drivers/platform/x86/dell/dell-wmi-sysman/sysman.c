<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common methods क्रम use with dell-wmi-sysman
 *
 *  Copyright (c) 2020 Dell Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/fs.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/wmi.h>
#समावेश "dell-wmi-sysman.h"

#घोषणा MAX_TYPES  4
#समावेश <linux/nls.h>

अटल काष्ठा class firmware_attributes_class = अणु
	.name = "firmware-attributes",
पूर्ण;

काष्ठा wmi_sysman_priv wmi_priv = अणु
	.mutex = __MUTEX_INITIALIZER(wmi_priv.mutex),
पूर्ण;

/* reset bios to शेषs */
अटल स्थिर अक्षर * स्थिर reset_types[] = अणु"builtinsafe", "lastknowngood", "factory", "custom"पूर्ण;
अटल पूर्णांक reset_option = -1;


/**
 * populate_string_buffer() - populates a string buffer
 * @buffer: the start of the destination buffer
 * @buffer_len: length of the destination buffer
 * @str: the string to insert पूर्णांकo buffer
 */
sमाप_प्रकार populate_string_buffer(अक्षर *buffer, माप_प्रकार buffer_len, स्थिर अक्षर *str)
अणु
	u16 *length = (u16 *)buffer;
	u16 *target = length + 1;
	पूर्णांक ret;

	ret = utf8s_to_utf16s(str, म_माप(str), UTF16_HOST_ENDIAN,
			      target, buffer_len - माप(u16));
	अगर (ret < 0) अणु
		dev_err(wmi_priv.class_dev, "UTF16 conversion failed\n");
		वापस ret;
	पूर्ण

	अगर ((ret * माप(u16)) > U16_MAX) अणु
		dev_err(wmi_priv.class_dev, "Error string too long\n");
		वापस -दुस्फल;
	पूर्ण

	*length = ret * माप(u16);
	वापस माप(u16) + *length;
पूर्ण

/**
 * calculate_string_buffer() - determines size of string buffer क्रम use with BIOS communication
 * @str: the string to calculate based upon
 *
 */
माप_प्रकार calculate_string_buffer(स्थिर अक्षर *str)
अणु
	/* u16 length field + one UTF16 अक्षर क्रम each input अक्षर */
	वापस माप(u16) + म_माप(str) * माप(u16);
पूर्ण

/**
 * calculate_security_buffer() - determines size of security buffer क्रम authentication scheme
 * @authentication: the authentication content
 *
 * Currently only supported type is Admin password
 */
माप_प्रकार calculate_security_buffer(अक्षर *authentication)
अणु
	अगर (म_माप(authentication) > 0) अणु
		वापस (माप(u32) * 2) + म_माप(authentication) +
			म_माप(authentication) % 2;
	पूर्ण
	वापस माप(u32) * 2;
पूर्ण

/**
 * populate_security_buffer() - builds a security buffer क्रम authentication scheme
 * @buffer: the buffer to populate
 * @authentication: the authentication content
 *
 * Currently only supported type is PLAIN TEXT
 */
व्योम populate_security_buffer(अक्षर *buffer, अक्षर *authentication)
अणु
	अक्षर *auth = buffer + माप(u32) * 2;
	u32 *sectype = (u32 *) buffer;
	u32 *seclen = sectype + 1;

	*sectype = म_माप(authentication) > 0 ? 1 : 0;
	*seclen = म_माप(authentication);

	/* plain text */
	अगर (म_माप(authentication) > 0)
		स_नकल(auth, authentication, *seclen);
पूर्ण

/**
 * map_wmi_error() - map errors from WMI methods to kernel error codes
 * @error_code: पूर्णांकeger error code वापसed from Dell's firmware
 */
पूर्णांक map_wmi_error(पूर्णांक error_code)
अणु
	चयन (error_code) अणु
	हाल 0:
		/* success */
		वापस 0;
	हाल 1:
		/* failed */
		वापस -EIO;
	हाल 2:
		/* invalid parameter */
		वापस -EINVAL;
	हाल 3:
		/* access denied */
		वापस -EACCES;
	हाल 4:
		/* not supported */
		वापस -EOPNOTSUPP;
	हाल 5:
		/* memory error */
		वापस -ENOMEM;
	हाल 6:
		/* protocol error */
		वापस -EPROTO;
	पूर्ण
	/* unspecअगरied error */
	वापस -EIO;
पूर्ण

/**
 * reset_bios_show() - sysfs implementaton क्रम पढ़ो reset_bios
 * @kobj: Kernel object क्रम this attribute
 * @attr: Kernel object attribute
 * @buf: The buffer to display to userspace
 */
अटल sमाप_प्रकार reset_bios_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अक्षर *start = buf;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_TYPES; i++) अणु
		अगर (i == reset_option)
			buf += प्र_लिखो(buf, "[%s] ", reset_types[i]);
		अन्यथा
			buf += प्र_लिखो(buf, "%s ", reset_types[i]);
	पूर्ण
	buf += प्र_लिखो(buf, "\n");
	वापस buf-start;
पूर्ण

/**
 * reset_bios_store() - sysfs implementaton क्रम ग_लिखो reset_bios
 * @kobj: Kernel object क्रम this attribute
 * @attr: Kernel object attribute
 * @buf: The buffer from userspace
 * @count: the size of the buffer from userspace
 */
अटल sमाप_प्रकार reset_bios_store(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक type = sysfs_match_string(reset_types, buf);
	पूर्णांक ret;

	अगर (type < 0)
		वापस type;

	ret = set_bios_शेषs(type);
	pr_debug("reset all attributes request type %d: %d\n", type, ret);
	अगर (!ret) अणु
		reset_option = type;
		ret = count;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * pending_reboot_show() - sysfs implementaton क्रम पढ़ो pending_reboot
 * @kobj: Kernel object क्रम this attribute
 * @attr: Kernel object attribute
 * @buf: The buffer to display to userspace
 *
 * Stores शेष value as 0
 * When current_value is changed this attribute is set to 1 to notअगरy reboot may be required
 */
अटल sमाप_प्रकार pending_reboot_show(काष्ठा kobject *kobj, काष्ठा kobj_attribute *attr,
				   अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d\n", wmi_priv.pending_changes);
पूर्ण

अटल काष्ठा kobj_attribute reset_bios = __ATTR_RW(reset_bios);
अटल काष्ठा kobj_attribute pending_reboot = __ATTR_RO(pending_reboot);


/**
 * create_attributes_level_sysfs_files() - Creates reset_bios and
 * pending_reboot attributes
 */
अटल पूर्णांक create_attributes_level_sysfs_files(व्योम)
अणु
	पूर्णांक ret;

	ret = sysfs_create_file(&wmi_priv.मुख्य_dir_kset->kobj, &reset_bios.attr);
	अगर (ret)
		वापस ret;

	ret = sysfs_create_file(&wmi_priv.मुख्य_dir_kset->kobj, &pending_reboot.attr);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार wmi_sysman_attr_show(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा kobj_attribute *kattr;
	sमाप_प्रकार ret = -EIO;

	kattr = container_of(attr, काष्ठा kobj_attribute, attr);
	अगर (kattr->show)
		ret = kattr->show(kobj, kattr, buf);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार wmi_sysman_attr_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा kobj_attribute *kattr;
	sमाप_प्रकार ret = -EIO;

	kattr = container_of(attr, काष्ठा kobj_attribute, attr);
	अगर (kattr->store)
		ret = kattr->store(kobj, kattr, buf, count);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops wmi_sysman_kobj_sysfs_ops = अणु
	.show	= wmi_sysman_attr_show,
	.store	= wmi_sysman_attr_store,
पूर्ण;

अटल व्योम attr_name_release(काष्ठा kobject *kobj)
अणु
	kमुक्त(kobj);
पूर्ण

अटल काष्ठा kobj_type attr_name_ktype = अणु
	.release	= attr_name_release,
	.sysfs_ops	= &wmi_sysman_kobj_sysfs_ops,
पूर्ण;

/**
 * strlcpy_attr - Copy a length-limited, शून्य-terminated string with bound checks
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
व्योम strlcpy_attr(अक्षर *dest, अक्षर *src)
अणु
	माप_प्रकार len = म_माप(src) + 1;

	अगर (len > 1 && len <= MAX_BUFF)
		strlcpy(dest, src, len);

	/*len can be zero because any property not-applicable to attribute can
	 * be empty so check only क्रम too दीर्घ buffers and log error
	 */
	अगर (len > MAX_BUFF)
		pr_err("Source string returned from BIOS is out of bound!\n");
पूर्ण

/**
 * get_wmiobj_poपूर्णांकer() - Get Content of WMI block क्रम particular instance
 * @instance_id: WMI instance ID
 * @guid_string: WMI GUID (in str क्रमm)
 *
 * Fetches the content क्रम WMI block (instance_id) under GUID (guid_string)
 * Caller must kमुक्त the वापस
 */
जोड़ acpi_object *get_wmiobj_poपूर्णांकer(पूर्णांक instance_id, स्थिर अक्षर *guid_string)
अणु
	काष्ठा acpi_buffer out = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	acpi_status status;

	status = wmi_query_block(guid_string, instance_id, &out);

	वापस ACPI_SUCCESS(status) ? (जोड़ acpi_object *)out.poपूर्णांकer : शून्य;
पूर्ण

/**
 * get_instance_count() - Compute total number of instances under guid_string
 * @guid_string: WMI GUID (in string क्रमm)
 */
पूर्णांक get_instance_count(स्थिर अक्षर *guid_string)
अणु
	जोड़ acpi_object *wmi_obj = शून्य;
	पूर्णांक i = 0;

	करो अणु
		kमुक्त(wmi_obj);
		wmi_obj = get_wmiobj_poपूर्णांकer(i, guid_string);
		i++;
	पूर्ण जबतक (wmi_obj);

	वापस (i-1);
पूर्ण

/**
 * alloc_attributes_data() - Allocate attributes data क्रम a particular type
 * @attr_type: Attribute type to allocate
 */
अटल पूर्णांक alloc_attributes_data(पूर्णांक attr_type)
अणु
	पूर्णांक retval = 0;

	चयन (attr_type) अणु
	हाल ENUM:
		retval = alloc_क्रमागत_data();
		अवरोध;
	हाल INT:
		retval = alloc_पूर्णांक_data();
		अवरोध;
	हाल STR:
		retval = alloc_str_data();
		अवरोध;
	हाल PO:
		retval = alloc_po_data();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

/**
 * destroy_attribute_objs() - Free a kset of kobjects
 * @kset: The kset to destroy
 *
 * Fress kobjects created क्रम each attribute_name under attribute type kset
 */
अटल व्योम destroy_attribute_objs(काष्ठा kset *kset)
अणु
	काष्ठा kobject *pos, *next;

	list_क्रम_each_entry_safe(pos, next, &kset->list, entry) अणु
		kobject_put(pos);
	पूर्ण
पूर्ण

/**
 * release_attributes_data() - Clean-up all sysfs directories and files created
 */
अटल व्योम release_attributes_data(व्योम)
अणु
	mutex_lock(&wmi_priv.mutex);
	निकास_क्रमागत_attributes();
	निकास_पूर्णांक_attributes();
	निकास_str_attributes();
	निकास_po_attributes();
	अगर (wmi_priv.authentication_dir_kset) अणु
		destroy_attribute_objs(wmi_priv.authentication_dir_kset);
		kset_unरेजिस्टर(wmi_priv.authentication_dir_kset);
		wmi_priv.authentication_dir_kset = शून्य;
	पूर्ण
	अगर (wmi_priv.मुख्य_dir_kset) अणु
		sysfs_हटाओ_file(&wmi_priv.मुख्य_dir_kset->kobj, &reset_bios.attr);
		sysfs_हटाओ_file(&wmi_priv.मुख्य_dir_kset->kobj, &pending_reboot.attr);
		destroy_attribute_objs(wmi_priv.मुख्य_dir_kset);
		kset_unरेजिस्टर(wmi_priv.मुख्य_dir_kset);
		wmi_priv.मुख्य_dir_kset = शून्य;
	पूर्ण
	mutex_unlock(&wmi_priv.mutex);
पूर्ण

/**
 * init_bios_attributes() - Initialize all attributes क्रम a type
 * @attr_type: The attribute type to initialize
 * @guid: The WMI GUID associated with this type to initialize
 *
 * Initialiaze all 4 types of attributes क्रमागतeration, पूर्णांकeger, string and password object.
 * Populates each attrbute typ's respective properties under sysfs files
 */
अटल पूर्णांक init_bios_attributes(पूर्णांक attr_type, स्थिर अक्षर *guid)
अणु
	काष्ठा kobject *attr_name_kobj; //inभागidual attribute names
	जोड़ acpi_object *obj = शून्य;
	जोड़ acpi_object *elements;
	काष्ठा kset *पंचांगp_set;
	पूर्णांक min_elements;

	/* instance_id needs to be reset क्रम each type GUID
	 * also, instance IDs are unique within GUID but not across
	 */
	पूर्णांक instance_id = 0;
	पूर्णांक retval = 0;

	retval = alloc_attributes_data(attr_type);
	अगर (retval)
		वापस retval;

	चयन (attr_type) अणु
	हाल ENUM:	min_elements = 8;	अवरोध;
	हाल INT:	min_elements = 9;	अवरोध;
	हाल STR:	min_elements = 8;	अवरोध;
	हाल PO:	min_elements = 4;	अवरोध;
	शेष:
		pr_err("Error: Unknown attr_type: %d\n", attr_type);
		वापस -EINVAL;
	पूर्ण

	/* need to use specअगरic instance_id and guid combination to get right data */
	obj = get_wmiobj_poपूर्णांकer(instance_id, guid);
	अगर (!obj)
		वापस -ENODEV;

	mutex_lock(&wmi_priv.mutex);
	जबतक (obj) अणु
		अगर (obj->type != ACPI_TYPE_PACKAGE) अणु
			pr_err("Error: Expected ACPI-package type, got: %d\n", obj->type);
			retval = -EIO;
			जाओ err_attr_init;
		पूर्ण

		अगर (obj->package.count < min_elements) अणु
			pr_err("Error: ACPI-package does not have enough elements: %d < %d\n",
			       obj->package.count, min_elements);
			जाओ nextobj;
		पूर्ण

		elements = obj->package.elements;

		/* sanity checking */
		अगर (elements[ATTR_NAME].type != ACPI_TYPE_STRING) अणु
			pr_debug("incorrect element type\n");
			जाओ nextobj;
		पूर्ण
		अगर (म_माप(elements[ATTR_NAME].string.poपूर्णांकer) == 0) अणु
			pr_debug("empty attribute found\n");
			जाओ nextobj;
		पूर्ण
		अगर (attr_type == PO)
			पंचांगp_set = wmi_priv.authentication_dir_kset;
		अन्यथा
			पंचांगp_set = wmi_priv.मुख्य_dir_kset;

		अगर (kset_find_obj(पंचांगp_set, elements[ATTR_NAME].string.poपूर्णांकer)) अणु
			pr_debug("duplicate attribute name found - %s\n",
				elements[ATTR_NAME].string.poपूर्णांकer);
			जाओ nextobj;
		पूर्ण

		/* build attribute */
		attr_name_kobj = kzalloc(माप(*attr_name_kobj), GFP_KERNEL);
		अगर (!attr_name_kobj) अणु
			retval = -ENOMEM;
			जाओ err_attr_init;
		पूर्ण

		attr_name_kobj->kset = पंचांगp_set;

		retval = kobject_init_and_add(attr_name_kobj, &attr_name_ktype, शून्य, "%s",
						elements[ATTR_NAME].string.poपूर्णांकer);
		अगर (retval) अणु
			kobject_put(attr_name_kobj);
			जाओ err_attr_init;
		पूर्ण

		/* क्रमागतerate all of this attribute */
		चयन (attr_type) अणु
		हाल ENUM:
			retval = populate_क्रमागत_data(elements, instance_id, attr_name_kobj);
			अवरोध;
		हाल INT:
			retval = populate_पूर्णांक_data(elements, instance_id, attr_name_kobj);
			अवरोध;
		हाल STR:
			retval = populate_str_data(elements, instance_id, attr_name_kobj);
			अवरोध;
		हाल PO:
			retval = populate_po_data(elements, instance_id, attr_name_kobj);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (retval) अणु
			pr_debug("failed to populate %s\n",
				elements[ATTR_NAME].string.poपूर्णांकer);
			जाओ err_attr_init;
		पूर्ण

nextobj:
		kमुक्त(obj);
		instance_id++;
		obj = get_wmiobj_poपूर्णांकer(instance_id, guid);
	पूर्ण

	mutex_unlock(&wmi_priv.mutex);
	वापस 0;

err_attr_init:
	mutex_unlock(&wmi_priv.mutex);
	kमुक्त(obj);
	वापस retval;
पूर्ण

अटल पूर्णांक __init sysman_init(व्योम)
अणु
	पूर्णांक ret = 0;

	अगर (!dmi_find_device(DMI_DEV_TYPE_OEM_STRING, "Dell System", शून्य) &&
	    !dmi_find_device(DMI_DEV_TYPE_OEM_STRING, "www.dell.com", शून्य)) अणु
		pr_err("Unable to run on non-Dell system\n");
		वापस -ENODEV;
	पूर्ण

	ret = init_bios_attr_set_पूर्णांकerface();
	अगर (ret)
		वापस ret;

	ret = init_bios_attr_pass_पूर्णांकerface();
	अगर (ret)
		जाओ err_निकास_bios_attr_set_पूर्णांकerface;

	अगर (!wmi_priv.bios_attr_wdev || !wmi_priv.password_attr_wdev) अणु
		pr_debug("failed to find set or pass interface\n");
		ret = -ENODEV;
		जाओ err_निकास_bios_attr_pass_पूर्णांकerface;
	पूर्ण

	ret = class_रेजिस्टर(&firmware_attributes_class);
	अगर (ret)
		जाओ err_निकास_bios_attr_pass_पूर्णांकerface;

	wmi_priv.class_dev = device_create(&firmware_attributes_class, शून्य, MKDEV(0, 0),
				  शून्य, "%s", DRIVER_NAME);
	अगर (IS_ERR(wmi_priv.class_dev)) अणु
		ret = PTR_ERR(wmi_priv.class_dev);
		जाओ err_unरेजिस्टर_class;
	पूर्ण

	wmi_priv.मुख्य_dir_kset = kset_create_and_add("attributes", शून्य,
						     &wmi_priv.class_dev->kobj);
	अगर (!wmi_priv.मुख्य_dir_kset) अणु
		ret = -ENOMEM;
		जाओ err_destroy_classdev;
	पूर्ण

	wmi_priv.authentication_dir_kset = kset_create_and_add("authentication", शून्य,
								&wmi_priv.class_dev->kobj);
	अगर (!wmi_priv.authentication_dir_kset) अणु
		ret = -ENOMEM;
		जाओ err_release_attributes_data;
	पूर्ण

	ret = create_attributes_level_sysfs_files();
	अगर (ret) अणु
		pr_debug("could not create reset BIOS attribute\n");
		जाओ err_release_attributes_data;
	पूर्ण

	ret = init_bios_attributes(ENUM, DELL_WMI_BIOS_ENUMERATION_ATTRIBUTE_GUID);
	अगर (ret) अणु
		pr_debug("failed to populate enumeration type attributes\n");
		जाओ err_release_attributes_data;
	पूर्ण

	ret = init_bios_attributes(INT, DELL_WMI_BIOS_INTEGER_ATTRIBUTE_GUID);
	अगर (ret) अणु
		pr_debug("failed to populate integer type attributes\n");
		जाओ err_release_attributes_data;
	पूर्ण

	ret = init_bios_attributes(STR, DELL_WMI_BIOS_STRING_ATTRIBUTE_GUID);
	अगर (ret) अणु
		pr_debug("failed to populate string type attributes\n");
		जाओ err_release_attributes_data;
	पूर्ण

	ret = init_bios_attributes(PO, DELL_WMI_BIOS_PASSOBJ_ATTRIBUTE_GUID);
	अगर (ret) अणु
		pr_debug("failed to populate pass object type attributes\n");
		जाओ err_release_attributes_data;
	पूर्ण

	वापस 0;

err_release_attributes_data:
	release_attributes_data();

err_destroy_classdev:
	device_destroy(&firmware_attributes_class, MKDEV(0, 0));

err_unरेजिस्टर_class:
	class_unरेजिस्टर(&firmware_attributes_class);

err_निकास_bios_attr_pass_पूर्णांकerface:
	निकास_bios_attr_pass_पूर्णांकerface();

err_निकास_bios_attr_set_पूर्णांकerface:
	निकास_bios_attr_set_पूर्णांकerface();

	वापस ret;
पूर्ण

अटल व्योम __निकास sysman_निकास(व्योम)
अणु
	release_attributes_data();
	device_destroy(&firmware_attributes_class, MKDEV(0, 0));
	class_unरेजिस्टर(&firmware_attributes_class);
	निकास_bios_attr_set_पूर्णांकerface();
	निकास_bios_attr_pass_पूर्णांकerface();
पूर्ण

module_init(sysman_init);
module_निकास(sysman_निकास);

MODULE_AUTHOR("Mario Limonciello <mario.limonciello@outlook.com>");
MODULE_AUTHOR("Prasanth Ksr <prasanth.ksr@dell.com>");
MODULE_AUTHOR("Divya Bharathi <divya.bharathi@dell.com>");
MODULE_DESCRIPTION("Dell platform setting control interface");
MODULE_LICENSE("GPL");
