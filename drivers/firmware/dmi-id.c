<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Export SMBIOS/DMI info via sysfs to userspace
 *
 * Copyright 2007, Lennart Poettering
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

काष्ठा dmi_device_attributeअणु
	काष्ठा device_attribute dev_attr;
	पूर्णांक field;
पूर्ण;
#घोषणा to_dmi_dev_attr(_dev_attr) \
	container_of(_dev_attr, काष्ठा dmi_device_attribute, dev_attr)

अटल sमाप_प्रकार sys_dmi_field_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *page)
अणु
	पूर्णांक field = to_dmi_dev_attr(attr)->field;
	sमाप_प्रकार len;
	len = scnम_लिखो(page, PAGE_SIZE, "%s\n", dmi_get_प्रणाली_info(field));
	page[len-1] = '\n';
	वापस len;
पूर्ण

#घोषणा DMI_ATTR(_name, _mode, _show, _field)			\
	अणु .dev_attr = __ATTR(_name, _mode, _show, शून्य),	\
	  .field = _field पूर्ण

#घोषणा DEFINE_DMI_ATTR_WITH_SHOW(_name, _mode, _field)		\
अटल काष्ठा dmi_device_attribute sys_dmi_##_name##_attr =	\
	DMI_ATTR(_name, _mode, sys_dmi_field_show, _field);

DEFINE_DMI_ATTR_WITH_SHOW(bios_venकरोr,		0444, DMI_BIOS_VENDOR);
DEFINE_DMI_ATTR_WITH_SHOW(bios_version,		0444, DMI_BIOS_VERSION);
DEFINE_DMI_ATTR_WITH_SHOW(bios_date,		0444, DMI_BIOS_DATE);
DEFINE_DMI_ATTR_WITH_SHOW(sys_venकरोr,		0444, DMI_SYS_VENDOR);
DEFINE_DMI_ATTR_WITH_SHOW(bios_release,		0444, DMI_BIOS_RELEASE);
DEFINE_DMI_ATTR_WITH_SHOW(ec_firmware_release,	0444, DMI_EC_FIRMWARE_RELEASE);
DEFINE_DMI_ATTR_WITH_SHOW(product_name,		0444, DMI_PRODUCT_NAME);
DEFINE_DMI_ATTR_WITH_SHOW(product_version,	0444, DMI_PRODUCT_VERSION);
DEFINE_DMI_ATTR_WITH_SHOW(product_serial,	0400, DMI_PRODUCT_SERIAL);
DEFINE_DMI_ATTR_WITH_SHOW(product_uuid,		0400, DMI_PRODUCT_UUID);
DEFINE_DMI_ATTR_WITH_SHOW(product_sku,		0444, DMI_PRODUCT_SKU);
DEFINE_DMI_ATTR_WITH_SHOW(product_family,	0444, DMI_PRODUCT_FAMILY);
DEFINE_DMI_ATTR_WITH_SHOW(board_venकरोr,		0444, DMI_BOARD_VENDOR);
DEFINE_DMI_ATTR_WITH_SHOW(board_name,		0444, DMI_BOARD_NAME);
DEFINE_DMI_ATTR_WITH_SHOW(board_version,	0444, DMI_BOARD_VERSION);
DEFINE_DMI_ATTR_WITH_SHOW(board_serial,		0400, DMI_BOARD_SERIAL);
DEFINE_DMI_ATTR_WITH_SHOW(board_asset_tag,	0444, DMI_BOARD_ASSET_TAG);
DEFINE_DMI_ATTR_WITH_SHOW(chassis_venकरोr,	0444, DMI_CHASSIS_VENDOR);
DEFINE_DMI_ATTR_WITH_SHOW(chassis_type,		0444, DMI_CHASSIS_TYPE);
DEFINE_DMI_ATTR_WITH_SHOW(chassis_version,	0444, DMI_CHASSIS_VERSION);
DEFINE_DMI_ATTR_WITH_SHOW(chassis_serial,	0400, DMI_CHASSIS_SERIAL);
DEFINE_DMI_ATTR_WITH_SHOW(chassis_asset_tag,	0444, DMI_CHASSIS_ASSET_TAG);

अटल व्योम ascii_filter(अक्षर *d, स्थिर अक्षर *s)
अणु
	/* Filter out अक्षरacters we करोn't want to see in the modalias string */
	क्रम (; *s; s++)
		अगर (*s > ' ' && *s < 127 && *s != ':')
			*(d++) = *s;

	*d = 0;
पूर्ण

अटल sमाप_प्रकार get_modalias(अक्षर *buffer, माप_प्रकार buffer_size)
अणु
	अटल स्थिर काष्ठा mafield अणु
		स्थिर अक्षर *prefix;
		पूर्णांक field;
	पूर्ण fields[] = अणु
		अणु "bvn", DMI_BIOS_VENDOR पूर्ण,
		अणु "bvr", DMI_BIOS_VERSION पूर्ण,
		अणु "bd",  DMI_BIOS_DATE पूर्ण,
		अणु "br",  DMI_BIOS_RELEASE पूर्ण,
		अणु "efr", DMI_EC_FIRMWARE_RELEASE पूर्ण,
		अणु "svn", DMI_SYS_VENDOR पूर्ण,
		अणु "pn",  DMI_PRODUCT_NAME पूर्ण,
		अणु "pvr", DMI_PRODUCT_VERSION पूर्ण,
		अणु "sku", DMI_PRODUCT_SKU पूर्ण,
		अणु "rvn", DMI_BOARD_VENDOR पूर्ण,
		अणु "rn",  DMI_BOARD_NAME पूर्ण,
		अणु "rvr", DMI_BOARD_VERSION पूर्ण,
		अणु "cvn", DMI_CHASSIS_VENDOR पूर्ण,
		अणु "ct",  DMI_CHASSIS_TYPE पूर्ण,
		अणु "cvr", DMI_CHASSIS_VERSION पूर्ण,
		अणु शून्य,  DMI_NONE पूर्ण
	पूर्ण;

	sमाप_प्रकार l, left;
	अक्षर *p;
	स्थिर काष्ठा mafield *f;

	म_नकल(buffer, "dmi");
	p = buffer + 3; left = buffer_size - 4;

	क्रम (f = fields; f->prefix && left > 0; f++) अणु
		स्थिर अक्षर *c;
		अक्षर *t;

		c = dmi_get_प्रणाली_info(f->field);
		अगर (!c)
			जारी;

		t = kदो_स्मृति(म_माप(c) + 1, GFP_KERNEL);
		अगर (!t)
			अवरोध;
		ascii_filter(t, c);
		l = scnम_लिखो(p, left, ":%s%s", f->prefix, t);
		kमुक्त(t);

		p += l;
		left -= l;
	पूर्ण

	p[0] = ':';
	p[1] = 0;

	वापस p - buffer + 1;
पूर्ण

अटल sमाप_प्रकार sys_dmi_modalias_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *page)
अणु
	sमाप_प्रकार r;
	r = get_modalias(page, PAGE_SIZE-1);
	page[r] = '\n';
	page[r+1] = 0;
	वापस r+1;
पूर्ण

अटल काष्ठा device_attribute sys_dmi_modalias_attr =
	__ATTR(modalias, 0444, sys_dmi_modalias_show, शून्य);

अटल काष्ठा attribute *sys_dmi_attributes[DMI_STRING_MAX+2];

अटल काष्ठा attribute_group sys_dmi_attribute_group = अणु
	.attrs = sys_dmi_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group* sys_dmi_attribute_groups[] = अणु
	&sys_dmi_attribute_group,
	शून्य
पूर्ण;

अटल पूर्णांक dmi_dev_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	sमाप_प्रकार len;

	अगर (add_uevent_var(env, "MODALIAS="))
		वापस -ENOMEM;
	len = get_modalias(&env->buf[env->buflen - 1],
			   माप(env->buf) - env->buflen);
	अगर (len >= (माप(env->buf) - env->buflen))
		वापस -ENOMEM;
	env->buflen += len;
	वापस 0;
पूर्ण

अटल काष्ठा class dmi_class = अणु
	.name = "dmi",
	.dev_release = (व्योम(*)(काष्ठा device *)) kमुक्त,
	.dev_uevent = dmi_dev_uevent,
पूर्ण;

अटल काष्ठा device *dmi_dev;

/* Initialization */

#घोषणा ADD_DMI_ATTR(_name, _field) \
	अगर (dmi_get_प्रणाली_info(_field)) \
		sys_dmi_attributes[i++] = &sys_dmi_##_name##_attr.dev_attr.attr;

/* In a separate function to keep gcc 3.2 happy - करो NOT merge this in
   dmi_id_init! */
अटल व्योम __init dmi_id_init_attr_table(व्योम)
अणु
	पूर्णांक i;

	/* Not necessarily all DMI fields are available on all
	 * प्रणालीs, hence let's built an attribute table of just
	 * what's available */
	i = 0;
	ADD_DMI_ATTR(bios_venकरोr,       DMI_BIOS_VENDOR);
	ADD_DMI_ATTR(bios_version,      DMI_BIOS_VERSION);
	ADD_DMI_ATTR(bios_date,         DMI_BIOS_DATE);
	ADD_DMI_ATTR(bios_release,      DMI_BIOS_RELEASE);
	ADD_DMI_ATTR(ec_firmware_release, DMI_EC_FIRMWARE_RELEASE);
	ADD_DMI_ATTR(sys_venकरोr,        DMI_SYS_VENDOR);
	ADD_DMI_ATTR(product_name,      DMI_PRODUCT_NAME);
	ADD_DMI_ATTR(product_version,   DMI_PRODUCT_VERSION);
	ADD_DMI_ATTR(product_serial,    DMI_PRODUCT_SERIAL);
	ADD_DMI_ATTR(product_uuid,      DMI_PRODUCT_UUID);
	ADD_DMI_ATTR(product_family,    DMI_PRODUCT_FAMILY);
	ADD_DMI_ATTR(product_sku,       DMI_PRODUCT_SKU);
	ADD_DMI_ATTR(board_venकरोr,      DMI_BOARD_VENDOR);
	ADD_DMI_ATTR(board_name,        DMI_BOARD_NAME);
	ADD_DMI_ATTR(board_version,     DMI_BOARD_VERSION);
	ADD_DMI_ATTR(board_serial,      DMI_BOARD_SERIAL);
	ADD_DMI_ATTR(board_asset_tag,   DMI_BOARD_ASSET_TAG);
	ADD_DMI_ATTR(chassis_venकरोr,    DMI_CHASSIS_VENDOR);
	ADD_DMI_ATTR(chassis_type,      DMI_CHASSIS_TYPE);
	ADD_DMI_ATTR(chassis_version,   DMI_CHASSIS_VERSION);
	ADD_DMI_ATTR(chassis_serial,    DMI_CHASSIS_SERIAL);
	ADD_DMI_ATTR(chassis_asset_tag, DMI_CHASSIS_ASSET_TAG);
	sys_dmi_attributes[i++] = &sys_dmi_modalias_attr.attr;
पूर्ण

अटल पूर्णांक __init dmi_id_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!dmi_available)
		वापस -ENODEV;

	dmi_id_init_attr_table();

	ret = class_रेजिस्टर(&dmi_class);
	अगर (ret)
		वापस ret;

	dmi_dev = kzalloc(माप(*dmi_dev), GFP_KERNEL);
	अगर (!dmi_dev) अणु
		ret = -ENOMEM;
		जाओ fail_class_unरेजिस्टर;
	पूर्ण

	dmi_dev->class = &dmi_class;
	dev_set_name(dmi_dev, "id");
	dmi_dev->groups = sys_dmi_attribute_groups;

	ret = device_रेजिस्टर(dmi_dev);
	अगर (ret)
		जाओ fail_put_dmi_dev;

	वापस 0;

fail_put_dmi_dev:
	put_device(dmi_dev);

fail_class_unरेजिस्टर:
	class_unरेजिस्टर(&dmi_class);

	वापस ret;
पूर्ण

arch_initcall(dmi_id_init);
