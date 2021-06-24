<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB Role Switch Support
 *
 * Copyright (C) 2018 Intel Corporation
 * Author: Heikki Krogerus <heikki.krogerus@linux.पूर्णांकel.com>
 *         Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/usb/role.h>
#समावेश <linux/property.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

अटल काष्ठा class *role_class;

काष्ठा usb_role_चयन अणु
	काष्ठा device dev;
	काष्ठा mutex lock; /* device lock*/
	क्रमागत usb_role role;

	/* From descriptor */
	काष्ठा device *usb2_port;
	काष्ठा device *usb3_port;
	काष्ठा device *udc;
	usb_role_चयन_set_t set;
	usb_role_चयन_get_t get;
	bool allow_userspace_control;
पूर्ण;

#घोषणा to_role_चयन(d)	container_of(d, काष्ठा usb_role_चयन, dev)

/**
 * usb_role_चयन_set_role - Set USB role क्रम a चयन
 * @sw: USB role चयन
 * @role: USB role to be चयनed to
 *
 * Set USB role @role क्रम @sw.
 */
पूर्णांक usb_role_चयन_set_role(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role)
अणु
	पूर्णांक ret;

	अगर (IS_ERR_OR_शून्य(sw))
		वापस 0;

	mutex_lock(&sw->lock);

	ret = sw->set(sw, role);
	अगर (!ret) अणु
		sw->role = role;
		kobject_uevent(&sw->dev.kobj, KOBJ_CHANGE);
	पूर्ण

	mutex_unlock(&sw->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_set_role);

/**
 * usb_role_चयन_get_role - Get the USB role क्रम a चयन
 * @sw: USB role चयन
 *
 * Depending on the role-चयन-driver this function वापसs either a cached
 * value of the last set role, or पढ़ोs back the actual value from the hardware.
 */
क्रमागत usb_role usb_role_चयन_get_role(काष्ठा usb_role_चयन *sw)
अणु
	क्रमागत usb_role role;

	अगर (IS_ERR_OR_शून्य(sw))
		वापस USB_ROLE_NONE;

	mutex_lock(&sw->lock);

	अगर (sw->get)
		role = sw->get(sw);
	अन्यथा
		role = sw->role;

	mutex_unlock(&sw->lock);

	वापस role;
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_get_role);

अटल व्योम *usb_role_चयन_match(काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *id,
				   व्योम *data)
अणु
	काष्ठा device *dev;

	अगर (id && !fwnode_property_present(fwnode, id))
		वापस शून्य;

	dev = class_find_device_by_fwnode(role_class, fwnode);

	वापस dev ? to_role_चयन(dev) : ERR_PTR(-EPROBE_DEFER);
पूर्ण

अटल काष्ठा usb_role_चयन *
usb_role_चयन_is_parent(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा fwnode_handle *parent = fwnode_get_parent(fwnode);
	काष्ठा device *dev;

	अगर (!parent || !fwnode_property_present(parent, "usb-role-switch"))
		वापस शून्य;

	dev = class_find_device_by_fwnode(role_class, parent);
	वापस dev ? to_role_चयन(dev) : ERR_PTR(-EPROBE_DEFER);
पूर्ण

/**
 * usb_role_चयन_get - Find USB role चयन linked with the caller
 * @dev: The caller device
 *
 * Finds and वापसs role चयन linked with @dev. The reference count क्रम the
 * found चयन is incremented.
 */
काष्ठा usb_role_चयन *usb_role_चयन_get(काष्ठा device *dev)
अणु
	काष्ठा usb_role_चयन *sw;

	sw = usb_role_चयन_is_parent(dev_fwnode(dev));
	अगर (!sw)
		sw = device_connection_find_match(dev, "usb-role-switch", शून्य,
						  usb_role_चयन_match);

	अगर (!IS_ERR_OR_शून्य(sw))
		WARN_ON(!try_module_get(sw->dev.parent->driver->owner));

	वापस sw;
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_get);

/**
 * fwnode_usb_role_चयन_get - Find USB role चयन linked with the caller
 * @fwnode: The caller device node
 *
 * This is similar to the usb_role_चयन_get() function above, but it searches
 * the चयन using fwnode instead of device entry.
 */
काष्ठा usb_role_चयन *fwnode_usb_role_चयन_get(काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा usb_role_चयन *sw;

	sw = usb_role_चयन_is_parent(fwnode);
	अगर (!sw)
		sw = fwnode_connection_find_match(fwnode, "usb-role-switch",
						  शून्य, usb_role_चयन_match);
	अगर (!IS_ERR_OR_शून्य(sw))
		WARN_ON(!try_module_get(sw->dev.parent->driver->owner));

	वापस sw;
पूर्ण
EXPORT_SYMBOL_GPL(fwnode_usb_role_चयन_get);

/**
 * usb_role_चयन_put - Release handle to a चयन
 * @sw: USB Role Switch
 *
 * Decrement reference count क्रम @sw.
 */
व्योम usb_role_चयन_put(काष्ठा usb_role_चयन *sw)
अणु
	अगर (!IS_ERR_OR_शून्य(sw)) अणु
		module_put(sw->dev.parent->driver->owner);
		put_device(&sw->dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_put);

/**
 * usb_role_चयन_find_by_fwnode - Find USB role चयन with its fwnode
 * @fwnode: fwnode of the USB Role Switch
 *
 * Finds and वापसs role चयन with @fwnode. The reference count क्रम the
 * found चयन is incremented.
 */
काष्ठा usb_role_चयन *
usb_role_चयन_find_by_fwnode(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	काष्ठा device *dev;

	अगर (!fwnode)
		वापस शून्य;

	dev = class_find_device_by_fwnode(role_class, fwnode);
	अगर (dev)
		WARN_ON(!try_module_get(dev->parent->driver->owner));

	वापस dev ? to_role_चयन(dev) : शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_find_by_fwnode);

अटल umode_t
usb_role_चयन_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा usb_role_चयन *sw = to_role_चयन(dev);

	अगर (sw->allow_userspace_control)
		वापस attr->mode;

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर usb_roles[] = अणु
	[USB_ROLE_NONE]		= "none",
	[USB_ROLE_HOST]		= "host",
	[USB_ROLE_DEVICE]	= "device",
पूर्ण;

अटल sमाप_प्रकार
role_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_role_चयन *sw = to_role_चयन(dev);
	क्रमागत usb_role role = usb_role_चयन_get_role(sw);

	वापस प्र_लिखो(buf, "%s\n", usb_roles[role]);
पूर्ण

अटल sमाप_प्रकार role_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा usb_role_चयन *sw = to_role_चयन(dev);
	पूर्णांक ret;

	ret = sysfs_match_string(usb_roles, buf);
	अगर (ret < 0) अणु
		bool res;

		/* Extra check अगर the user wants to disable the चयन */
		ret = kstrtobool(buf, &res);
		अगर (ret || res)
			वापस -EINVAL;
	पूर्ण

	ret = usb_role_चयन_set_role(sw, ret);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(role);

अटल काष्ठा attribute *usb_role_चयन_attrs[] = अणु
	&dev_attr_role.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group usb_role_चयन_group = अणु
	.is_visible = usb_role_चयन_is_visible,
	.attrs = usb_role_चयन_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *usb_role_चयन_groups[] = अणु
	&usb_role_चयन_group,
	शून्य,
पूर्ण;

अटल पूर्णांक
usb_role_चयन_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक ret;

	ret = add_uevent_var(env, "USB_ROLE_SWITCH=%s", dev_name(dev));
	अगर (ret)
		dev_err(dev, "failed to add uevent USB_ROLE_SWITCH\n");

	वापस ret;
पूर्ण

अटल व्योम usb_role_चयन_release(काष्ठा device *dev)
अणु
	काष्ठा usb_role_चयन *sw = to_role_चयन(dev);

	kमुक्त(sw);
पूर्ण

अटल स्थिर काष्ठा device_type usb_role_dev_type = अणु
	.name = "usb_role_switch",
	.groups = usb_role_चयन_groups,
	.uevent = usb_role_चयन_uevent,
	.release = usb_role_चयन_release,
पूर्ण;

/**
 * usb_role_चयन_रेजिस्टर - Register USB Role Switch
 * @parent: Parent device क्रम the चयन
 * @desc: Description of the चयन
 *
 * USB Role Switch is a device capable or choosing the role क्रम USB connector.
 * On platक्रमms where the USB controller is dual-role capable, the controller
 * driver will need to रेजिस्टर the चयन. On platक्रमms where the USB host and
 * USB device controllers behind the connector are separate, there will be a
 * mux, and the driver क्रम that mux will need to रेजिस्टर the चयन.
 *
 * Returns handle to a new role चयन or ERR_PTR. The content of @desc is
 * copied.
 */
काष्ठा usb_role_चयन *
usb_role_चयन_रेजिस्टर(काष्ठा device *parent,
			 स्थिर काष्ठा usb_role_चयन_desc *desc)
अणु
	काष्ठा usb_role_चयन *sw;
	पूर्णांक ret;

	अगर (!desc || !desc->set)
		वापस ERR_PTR(-EINVAL);

	sw = kzalloc(माप(*sw), GFP_KERNEL);
	अगर (!sw)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&sw->lock);

	sw->allow_userspace_control = desc->allow_userspace_control;
	sw->usb2_port = desc->usb2_port;
	sw->usb3_port = desc->usb3_port;
	sw->udc = desc->udc;
	sw->set = desc->set;
	sw->get = desc->get;

	sw->dev.parent = parent;
	sw->dev.fwnode = desc->fwnode;
	sw->dev.class = role_class;
	sw->dev.type = &usb_role_dev_type;
	dev_set_drvdata(&sw->dev, desc->driver_data);
	dev_set_name(&sw->dev, "%s-role-switch",
		     desc->name ? desc->name : dev_name(parent));

	ret = device_रेजिस्टर(&sw->dev);
	अगर (ret) अणु
		put_device(&sw->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	/* TODO: Symlinks क्रम the host port and the device controller. */

	वापस sw;
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_रेजिस्टर);

/**
 * usb_role_चयन_unरेजिस्टर - Unregsiter USB Role Switch
 * @sw: USB Role Switch
 *
 * Unरेजिस्टर चयन that was रेजिस्टरed with usb_role_चयन_रेजिस्टर().
 */
व्योम usb_role_चयन_unरेजिस्टर(काष्ठा usb_role_चयन *sw)
अणु
	अगर (!IS_ERR_OR_शून्य(sw))
		device_unरेजिस्टर(&sw->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_unरेजिस्टर);

/**
 * usb_role_चयन_set_drvdata - Assign निजी data poपूर्णांकer to a चयन
 * @sw: USB Role Switch
 * @data: Private data poपूर्णांकer
 */
व्योम usb_role_चयन_set_drvdata(काष्ठा usb_role_चयन *sw, व्योम *data)
अणु
	dev_set_drvdata(&sw->dev, data);
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_set_drvdata);

/**
 * usb_role_चयन_get_drvdata - Get the निजी data poपूर्णांकer of a चयन
 * @sw: USB Role Switch
 */
व्योम *usb_role_चयन_get_drvdata(काष्ठा usb_role_चयन *sw)
अणु
	वापस dev_get_drvdata(&sw->dev);
पूर्ण
EXPORT_SYMBOL_GPL(usb_role_चयन_get_drvdata);

अटल पूर्णांक __init usb_roles_init(व्योम)
अणु
	role_class = class_create(THIS_MODULE, "usb_role");
	वापस PTR_ERR_OR_ZERO(role_class);
पूर्ण
subsys_initcall(usb_roles_init);

अटल व्योम __निकास usb_roles_निकास(व्योम)
अणु
	class_destroy(role_class);
पूर्ण
module_निकास(usb_roles_निकास);

MODULE_AUTHOR("Heikki Krogerus <heikki.krogerus@linux.intel.com>");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("USB Role Class");
