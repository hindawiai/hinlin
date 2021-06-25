<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Lua driver क्रम Linux
 *
 * Copyright (c) 2012 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Roccat Lua is a gamer mouse which cpi, button and light settings can be
 * configured.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid-roccat.h>
#समावेश "hid-ids.h"
#समावेश "hid-roccat-common.h"
#समावेश "hid-roccat-lua.h"

अटल sमाप_प्रकार lua_sysfs_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
		अक्षर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा lua_device *lua = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off >= real_size)
		वापस 0;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&lua->lua_lock);
	retval = roccat_common2_receive(usb_dev, command, buf, real_size);
	mutex_unlock(&lua->lua_lock);

	वापस retval ? retval : real_size;
पूर्ण

अटल sमाप_प्रकार lua_sysfs_ग_लिखो(काष्ठा file *fp, काष्ठा kobject *kobj,
		व्योम स्थिर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा lua_device *lua = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&lua->lua_lock);
	retval = roccat_common2_send(usb_dev, command, buf, real_size);
	mutex_unlock(&lua->lua_lock);

	वापस retval ? retval : real_size;
पूर्ण

#घोषणा LUA_SYSFS_W(thingy, THINGY) \
अटल sमाप_प्रकार lua_sysfs_ग_लिखो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, \
		अक्षर *buf, loff_t off, माप_प्रकार count) \
अणु \
	वापस lua_sysfs_ग_लिखो(fp, kobj, buf, off, count, \
			LUA_SIZE_ ## THINGY, LUA_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा LUA_SYSFS_R(thingy, THINGY) \
अटल sमाप_प्रकार lua_sysfs_पढ़ो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, \
		अक्षर *buf, loff_t off, माप_प्रकार count) \
अणु \
	वापस lua_sysfs_पढ़ो(fp, kobj, buf, off, count, \
			LUA_SIZE_ ## THINGY, LUA_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा LUA_BIN_ATTRIBUTE_RW(thingy, THINGY) \
LUA_SYSFS_W(thingy, THINGY) \
LUA_SYSFS_R(thingy, THINGY) \
अटल काष्ठा bin_attribute lua_ ## thingy ## _attr = अणु \
	.attr = अणु .name = #thingy, .mode = 0660 पूर्ण, \
	.size = LUA_SIZE_ ## THINGY, \
	.पढ़ो = lua_sysfs_पढ़ो_ ## thingy, \
	.ग_लिखो = lua_sysfs_ग_लिखो_ ## thingy \
पूर्ण;

LUA_BIN_ATTRIBUTE_RW(control, CONTROL)

अटल पूर्णांक lua_create_sysfs_attributes(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस sysfs_create_bin_file(&पूर्णांकf->dev.kobj, &lua_control_attr);
पूर्ण

अटल व्योम lua_हटाओ_sysfs_attributes(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	sysfs_हटाओ_bin_file(&पूर्णांकf->dev.kobj, &lua_control_attr);
पूर्ण

अटल पूर्णांक lua_init_lua_device_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा lua_device *lua)
अणु
	mutex_init(&lua->lua_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lua_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा lua_device *lua;
	पूर्णांक retval;

	lua = kzalloc(माप(*lua), GFP_KERNEL);
	अगर (!lua) अणु
		hid_err(hdev, "can't alloc device descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	hid_set_drvdata(hdev, lua);

	retval = lua_init_lua_device_काष्ठा(usb_dev, lua);
	अगर (retval) अणु
		hid_err(hdev, "couldn't init struct lua_device\n");
		जाओ निकास;
	पूर्ण

	retval = lua_create_sysfs_attributes(पूर्णांकf);
	अगर (retval) अणु
		hid_err(hdev, "cannot create sysfs files\n");
		जाओ निकास;
	पूर्ण

	वापस 0;
निकास:
	kमुक्त(lua);
	वापस retval;
पूर्ण

अटल व्योम lua_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा lua_device *lua;

	lua_हटाओ_sysfs_attributes(पूर्णांकf);

	lua = hid_get_drvdata(hdev);
	kमुक्त(lua);
पूर्ण

अटल पूर्णांक lua_probe(काष्ठा hid_device *hdev,
		स्थिर काष्ठा hid_device_id *id)
अणु
	पूर्णांक retval;

	retval = hid_parse(hdev);
	अगर (retval) अणु
		hid_err(hdev, "parse failed\n");
		जाओ निकास;
	पूर्ण

	retval = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (retval) अणु
		hid_err(hdev, "hw start failed\n");
		जाओ निकास;
	पूर्ण

	retval = lua_init_specials(hdev);
	अगर (retval) अणु
		hid_err(hdev, "couldn't install mouse\n");
		जाओ निकास_stop;
	पूर्ण

	वापस 0;

निकास_stop:
	hid_hw_stop(hdev);
निकास:
	वापस retval;
पूर्ण

अटल व्योम lua_हटाओ(काष्ठा hid_device *hdev)
अणु
	lua_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल स्थिर काष्ठा hid_device_id lua_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_LUA) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, lua_devices);

अटल काष्ठा hid_driver lua_driver = अणु
		.name = "lua",
		.id_table = lua_devices,
		.probe = lua_probe,
		.हटाओ = lua_हटाओ
पूर्ण;
module_hid_driver(lua_driver);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Lua driver");
MODULE_LICENSE("GPL v2");
