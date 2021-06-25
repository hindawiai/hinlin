<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HP Compaq TC1100 Tablet WMI Extras Driver
 *
 *  Copyright (C) 2007 Carlos Corbacho <carlos@strangeworlds.co.uk>
 *  Copyright (C) 2004 Jamey Hicks <jamey.hicks@hp.com>
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा GUID "C364AC71-36DB-495A-8494-B439D472A505"

#घोषणा TC1100_INSTANCE_WIRELESS		1
#घोषणा TC1100_INSTANCE_JOGDIAL		2

MODULE_AUTHOR("Jamey Hicks, Carlos Corbacho");
MODULE_DESCRIPTION("HP Compaq TC1100 Tablet WMI Extras");
MODULE_LICENSE("GPL");
MODULE_ALIAS("wmi:C364AC71-36DB-495A-8494-B439D472A505");

अटल काष्ठा platक्रमm_device *tc1100_device;

काष्ठा tc1100_data अणु
	u32 wireless;
	u32 jogdial;
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल काष्ठा tc1100_data suspend_data;
#पूर्ण_अगर

/* --------------------------------------------------------------------------
				Device Management
   -------------------------------------------------------------------------- */

अटल पूर्णांक get_state(u32 *out, u8 instance)
अणु
	u32 पंचांगp;
	acpi_status status;
	काष्ठा acpi_buffer result = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *obj;

	अगर (!out)
		वापस -EINVAL;

	अगर (instance > 2)
		वापस -ENODEV;

	status = wmi_query_block(GUID, instance, &result);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	obj = (जोड़ acpi_object *) result.poपूर्णांकer;
	अगर (obj && obj->type == ACPI_TYPE_INTEGER) अणु
		पंचांगp = obj->पूर्णांकeger.value;
	पूर्ण अन्यथा अणु
		पंचांगp = 0;
	पूर्ण

	अगर (result.length > 0)
		kमुक्त(result.poपूर्णांकer);

	चयन (instance) अणु
	हाल TC1100_INSTANCE_WIRELESS:
		*out = (पंचांगp == 3) ? 1 : 0;
		वापस 0;
	हाल TC1100_INSTANCE_JOGDIAL:
		*out = (पंचांगp == 1) ? 0 : 1;
		वापस 0;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक set_state(u32 *in, u8 instance)
अणु
	u32 value;
	acpi_status status;
	काष्ठा acpi_buffer input;

	अगर (!in)
		वापस -EINVAL;

	अगर (instance > 2)
		वापस -ENODEV;

	चयन (instance) अणु
	हाल TC1100_INSTANCE_WIRELESS:
		value = (*in) ? 1 : 2;
		अवरोध;
	हाल TC1100_INSTANCE_JOGDIAL:
		value = (*in) ? 0 : 1;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	input.length = माप(u32);
	input.poपूर्णांकer = &value;

	status = wmi_set_block(GUID, instance, &input);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
				FS Interface (/sys)
   -------------------------------------------------------------------------- */

/*
 * Read/ ग_लिखो bool sysfs macro
 */
#घोषणा show_set_bool(value, instance) \
अटल sमाप_प्रकार \
show_bool_##value(काष्ठा device *dev, काष्ठा device_attribute *attr, \
	अक्षर *buf) \
अणु \
	u32 result; \
	acpi_status status = get_state(&result, instance); \
	अगर (ACPI_SUCCESS(status)) \
		वापस प्र_लिखो(buf, "%d\n", result); \
	वापस प्र_लिखो(buf, "Read error\n"); \
पूर्ण \
\
अटल sमाप_प्रकार \
set_bool_##value(काष्ठा device *dev, काष्ठा device_attribute *attr, \
	स्थिर अक्षर *buf, माप_प्रकार count) \
अणु \
	u32 पंचांगp = simple_म_से_अदीर्घ(buf, शून्य, 10); \
	acpi_status status = set_state(&पंचांगp, instance); \
		अगर (ACPI_FAILURE(status)) \
			वापस -EINVAL; \
	वापस count; \
पूर्ण \
अटल DEVICE_ATTR(value, S_IRUGO | S_IWUSR, \
	show_bool_##value, set_bool_##value);

show_set_bool(wireless, TC1100_INSTANCE_WIRELESS);
show_set_bool(jogdial, TC1100_INSTANCE_JOGDIAL);

अटल काष्ठा attribute *tc1100_attributes[] = अणु
	&dev_attr_wireless.attr,
	&dev_attr_jogdial.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group tc1100_attribute_group = अणु
	.attrs	= tc1100_attributes,
पूर्ण;

/* --------------------------------------------------------------------------
				Driver Model
   -------------------------------------------------------------------------- */

अटल पूर्णांक __init tc1100_probe(काष्ठा platक्रमm_device *device)
अणु
	वापस sysfs_create_group(&device->dev.kobj, &tc1100_attribute_group);
पूर्ण


अटल पूर्णांक tc1100_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	sysfs_हटाओ_group(&device->dev.kobj, &tc1100_attribute_group);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tc1100_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = get_state(&suspend_data.wireless, TC1100_INSTANCE_WIRELESS);
	अगर (ret)
		वापस ret;

	ret = get_state(&suspend_data.jogdial, TC1100_INSTANCE_JOGDIAL);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक tc1100_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = set_state(&suspend_data.wireless, TC1100_INSTANCE_WIRELESS);
	अगर (ret)
		वापस ret;

	ret = set_state(&suspend_data.jogdial, TC1100_INSTANCE_JOGDIAL);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tc1100_pm_ops = अणु
	.suspend	= tc1100_suspend,
	.resume		= tc1100_resume,
	.मुक्तze		= tc1100_suspend,
	.restore	= tc1100_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver tc1100_driver = अणु
	.driver = अणु
		.name = "tc1100-wmi",
#अगर_घोषित CONFIG_PM
		.pm = &tc1100_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.हटाओ = tc1100_हटाओ,
पूर्ण;

अटल पूर्णांक __init tc1100_init(व्योम)
अणु
	पूर्णांक error;

	अगर (!wmi_has_guid(GUID))
		वापस -ENODEV;

	tc1100_device = platक्रमm_device_alloc("tc1100-wmi", -1);
	अगर (!tc1100_device)
		वापस -ENOMEM;

	error = platक्रमm_device_add(tc1100_device);
	अगर (error)
		जाओ err_device_put;

	error = platक्रमm_driver_probe(&tc1100_driver, tc1100_probe);
	अगर (error)
		जाओ err_device_del;

	pr_info("HP Compaq TC1100 Tablet WMI Extras loaded\n");
	वापस 0;

 err_device_del:
	platक्रमm_device_del(tc1100_device);
 err_device_put:
	platक्रमm_device_put(tc1100_device);
	वापस error;
पूर्ण

अटल व्योम __निकास tc1100_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(tc1100_device);
	platक्रमm_driver_unरेजिस्टर(&tc1100_driver);
पूर्ण

module_init(tc1100_init);
module_निकास(tc1100_निकास);
