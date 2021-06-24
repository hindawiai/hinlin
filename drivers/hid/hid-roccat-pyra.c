<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Pyra driver क्रम Linux
 *
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Roccat Pyra is a mobile gamer mouse which comes in wired and wireless
 * variant. Wireless variant is not tested.
 * Userland tools can be found at http://sourceक्रमge.net/projects/roccat
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid-roccat.h>
#समावेश "hid-ids.h"
#समावेश "hid-roccat-common.h"
#समावेश "hid-roccat-pyra.h"

अटल uपूर्णांक profile_numbers[5] = अणु0, 1, 2, 3, 4पूर्ण;

/* pyra_class is used क्रम creating sysfs attributes via roccat अक्षर device */
अटल काष्ठा class *pyra_class;

अटल व्योम profile_activated(काष्ठा pyra_device *pyra,
		अचिन्हित पूर्णांक new_profile)
अणु
	अगर (new_profile >= ARRAY_SIZE(pyra->profile_settings))
		वापस;
	pyra->actual_profile = new_profile;
	pyra->actual_cpi = pyra->profile_settings[pyra->actual_profile].y_cpi;
पूर्ण

अटल पूर्णांक pyra_send_control(काष्ठा usb_device *usb_dev, पूर्णांक value,
		क्रमागत pyra_control_requests request)
अणु
	काष्ठा roccat_common2_control control;

	अगर ((request == PYRA_CONTROL_REQUEST_PROखाता_SETTINGS ||
			request == PYRA_CONTROL_REQUEST_PROखाता_BUTTONS) &&
			(value < 0 || value > 4))
		वापस -EINVAL;

	control.command = ROCCAT_COMMON_COMMAND_CONTROL;
	control.value = value;
	control.request = request;

	वापस roccat_common2_send(usb_dev, ROCCAT_COMMON_COMMAND_CONTROL,
			&control, माप(काष्ठा roccat_common2_control));
पूर्ण

अटल पूर्णांक pyra_get_profile_settings(काष्ठा usb_device *usb_dev,
		काष्ठा pyra_profile_settings *buf, पूर्णांक number)
अणु
	पूर्णांक retval;
	retval = pyra_send_control(usb_dev, number,
			PYRA_CONTROL_REQUEST_PROखाता_SETTINGS);
	अगर (retval)
		वापस retval;
	वापस roccat_common2_receive(usb_dev, PYRA_COMMAND_PROखाता_SETTINGS,
			buf, PYRA_SIZE_PROखाता_SETTINGS);
पूर्ण

अटल पूर्णांक pyra_get_settings(काष्ठा usb_device *usb_dev,
		काष्ठा pyra_settings *buf)
अणु
	वापस roccat_common2_receive(usb_dev, PYRA_COMMAND_SETTINGS,
			buf, PYRA_SIZE_SETTINGS);
पूर्ण

अटल पूर्णांक pyra_set_settings(काष्ठा usb_device *usb_dev,
		काष्ठा pyra_settings स्थिर *settings)
अणु
	वापस roccat_common2_send_with_status(usb_dev,
			PYRA_COMMAND_SETTINGS, settings,
			PYRA_SIZE_SETTINGS);
पूर्ण

अटल sमाप_प्रकार pyra_sysfs_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
		अक्षर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा pyra_device *pyra = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off >= real_size)
		वापस 0;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&pyra->pyra_lock);
	retval = roccat_common2_receive(usb_dev, command, buf, real_size);
	mutex_unlock(&pyra->pyra_lock);

	अगर (retval)
		वापस retval;

	वापस real_size;
पूर्ण

अटल sमाप_प्रकार pyra_sysfs_ग_लिखो(काष्ठा file *fp, काष्ठा kobject *kobj,
		व्योम स्थिर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा pyra_device *pyra = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&pyra->pyra_lock);
	retval = roccat_common2_send_with_status(usb_dev, command, (व्योम *)buf, real_size);
	mutex_unlock(&pyra->pyra_lock);

	अगर (retval)
		वापस retval;

	वापस real_size;
पूर्ण

#घोषणा PYRA_SYSFS_W(thingy, THINGY) \
अटल sमाप_प्रकार pyra_sysfs_ग_लिखो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस pyra_sysfs_ग_लिखो(fp, kobj, buf, off, count, \
			PYRA_SIZE_ ## THINGY, PYRA_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा PYRA_SYSFS_R(thingy, THINGY) \
अटल sमाप_प्रकार pyra_sysfs_पढ़ो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस pyra_sysfs_पढ़ो(fp, kobj, buf, off, count, \
			PYRA_SIZE_ ## THINGY, PYRA_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा PYRA_SYSFS_RW(thingy, THINGY) \
PYRA_SYSFS_W(thingy, THINGY) \
PYRA_SYSFS_R(thingy, THINGY)

#घोषणा PYRA_BIN_ATTRIBUTE_RW(thingy, THINGY) \
PYRA_SYSFS_RW(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0660 पूर्ण, \
	.size = PYRA_SIZE_ ## THINGY, \
	.पढ़ो = pyra_sysfs_पढ़ो_ ## thingy, \
	.ग_लिखो = pyra_sysfs_ग_लिखो_ ## thingy \
पूर्ण

#घोषणा PYRA_BIN_ATTRIBUTE_R(thingy, THINGY) \
PYRA_SYSFS_R(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0440 पूर्ण, \
	.size = PYRA_SIZE_ ## THINGY, \
	.पढ़ो = pyra_sysfs_पढ़ो_ ## thingy, \
पूर्ण

#घोषणा PYRA_BIN_ATTRIBUTE_W(thingy, THINGY) \
PYRA_SYSFS_W(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0220 पूर्ण, \
	.size = PYRA_SIZE_ ## THINGY, \
	.ग_लिखो = pyra_sysfs_ग_लिखो_ ## thingy \
पूर्ण

PYRA_BIN_ATTRIBUTE_W(control, CONTROL);
PYRA_BIN_ATTRIBUTE_RW(info, INFO);
PYRA_BIN_ATTRIBUTE_RW(profile_settings, PROखाता_SETTINGS);
PYRA_BIN_ATTRIBUTE_RW(profile_buttons, PROखाता_BUTTONS);

अटल sमाप_प्रकार pyra_sysfs_पढ़ो_profilex_settings(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	sमाप_प्रकार retval;

	retval = pyra_send_control(usb_dev, *(uपूर्णांक *)(attr->निजी),
			PYRA_CONTROL_REQUEST_PROखाता_SETTINGS);
	अगर (retval)
		वापस retval;

	वापस pyra_sysfs_पढ़ो(fp, kobj, buf, off, count,
			PYRA_SIZE_PROखाता_SETTINGS,
			PYRA_COMMAND_PROखाता_SETTINGS);
पूर्ण

अटल sमाप_प्रकार pyra_sysfs_पढ़ो_profilex_buttons(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	sमाप_प्रकार retval;

	retval = pyra_send_control(usb_dev, *(uपूर्णांक *)(attr->निजी),
			PYRA_CONTROL_REQUEST_PROखाता_BUTTONS);
	अगर (retval)
		वापस retval;

	वापस pyra_sysfs_पढ़ो(fp, kobj, buf, off, count,
			PYRA_SIZE_PROखाता_BUTTONS,
			PYRA_COMMAND_PROखाता_BUTTONS);
पूर्ण

#घोषणा PROखाता_ATTR(number)						\
अटल काष्ठा bin_attribute bin_attr_profile##number##_settings = अणु	\
	.attr = अणु .name = "profile" #number "_settings", .mode = 0440 पूर्ण,	\
	.size = PYRA_SIZE_PROखाता_SETTINGS,				\
	.पढ़ो = pyra_sysfs_पढ़ो_profilex_settings,			\
	.निजी = &profile_numbers[number-1],				\
पूर्ण;									\
अटल काष्ठा bin_attribute bin_attr_profile##number##_buttons = अणु	\
	.attr = अणु .name = "profile" #number "_buttons", .mode = 0440 पूर्ण,	\
	.size = PYRA_SIZE_PROखाता_BUTTONS,				\
	.पढ़ो = pyra_sysfs_पढ़ो_profilex_buttons,			\
	.निजी = &profile_numbers[number-1],				\
पूर्ण;
PROखाता_ATTR(1);
PROखाता_ATTR(2);
PROखाता_ATTR(3);
PROखाता_ATTR(4);
PROखाता_ATTR(5);

अटल sमाप_प्रकार pyra_sysfs_ग_लिखो_settings(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा pyra_device *pyra = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval = 0;
	काष्ठा pyra_roccat_report roccat_report;
	काष्ठा pyra_settings स्थिर *settings;

	अगर (off != 0 || count != PYRA_SIZE_SETTINGS)
		वापस -EINVAL;

	settings = (काष्ठा pyra_settings स्थिर *)buf;
	अगर (settings->startup_profile >= ARRAY_SIZE(pyra->profile_settings))
		वापस -EINVAL;

	mutex_lock(&pyra->pyra_lock);

	retval = pyra_set_settings(usb_dev, settings);
	अगर (retval) अणु
		mutex_unlock(&pyra->pyra_lock);
		वापस retval;
	पूर्ण

	profile_activated(pyra, settings->startup_profile);

	roccat_report.type = PYRA_MOUSE_EVENT_BUTTON_TYPE_PROखाता_2;
	roccat_report.value = settings->startup_profile + 1;
	roccat_report.key = 0;
	roccat_report_event(pyra->chrdev_minor,
			(uपूर्णांक8_t स्थिर *)&roccat_report);

	mutex_unlock(&pyra->pyra_lock);
	वापस PYRA_SIZE_SETTINGS;
पूर्ण

PYRA_SYSFS_R(settings, SETTINGS);
अटल काष्ठा bin_attribute bin_attr_settings =
	__BIN_ATTR(settings, (S_IWUSR | S_IRUGO),
		   pyra_sysfs_पढ़ो_settings, pyra_sysfs_ग_लिखो_settings,
		   PYRA_SIZE_SETTINGS);

अटल sमाप_प्रकार pyra_sysfs_show_actual_cpi(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pyra_device *pyra =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", pyra->actual_cpi);
पूर्ण
अटल DEVICE_ATTR(actual_cpi, 0440, pyra_sysfs_show_actual_cpi, शून्य);

अटल sमाप_प्रकार pyra_sysfs_show_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pyra_device *pyra =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	काष्ठा pyra_settings settings;

	mutex_lock(&pyra->pyra_lock);
	roccat_common2_receive(usb_dev, PYRA_COMMAND_SETTINGS,
			&settings, PYRA_SIZE_SETTINGS);
	mutex_unlock(&pyra->pyra_lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", settings.startup_profile);
पूर्ण
अटल DEVICE_ATTR(actual_profile, 0440, pyra_sysfs_show_actual_profile, शून्य);
अटल DEVICE_ATTR(startup_profile, 0440, pyra_sysfs_show_actual_profile, शून्य);

अटल sमाप_प्रकार pyra_sysfs_show_firmware_version(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pyra_device *pyra;
	काष्ठा usb_device *usb_dev;
	काष्ठा pyra_info info;

	dev = dev->parent->parent;
	pyra = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));

	mutex_lock(&pyra->pyra_lock);
	roccat_common2_receive(usb_dev, PYRA_COMMAND_INFO,
			&info, PYRA_SIZE_INFO);
	mutex_unlock(&pyra->pyra_lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", info.firmware_version);
पूर्ण
अटल DEVICE_ATTR(firmware_version, 0440, pyra_sysfs_show_firmware_version,
		   शून्य);

अटल काष्ठा attribute *pyra_attrs[] = अणु
	&dev_attr_actual_cpi.attr,
	&dev_attr_actual_profile.attr,
	&dev_attr_firmware_version.attr,
	&dev_attr_startup_profile.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *pyra_bin_attributes[] = अणु
	&bin_attr_control,
	&bin_attr_info,
	&bin_attr_profile_settings,
	&bin_attr_profile_buttons,
	&bin_attr_settings,
	&bin_attr_profile1_settings,
	&bin_attr_profile2_settings,
	&bin_attr_profile3_settings,
	&bin_attr_profile4_settings,
	&bin_attr_profile5_settings,
	&bin_attr_profile1_buttons,
	&bin_attr_profile2_buttons,
	&bin_attr_profile3_buttons,
	&bin_attr_profile4_buttons,
	&bin_attr_profile5_buttons,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pyra_group = अणु
	.attrs = pyra_attrs,
	.bin_attrs = pyra_bin_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *pyra_groups[] = अणु
	&pyra_group,
	शून्य,
पूर्ण;

अटल पूर्णांक pyra_init_pyra_device_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा pyra_device *pyra)
अणु
	काष्ठा pyra_settings settings;
	पूर्णांक retval, i;

	mutex_init(&pyra->pyra_lock);

	retval = pyra_get_settings(usb_dev, &settings);
	अगर (retval)
		वापस retval;

	क्रम (i = 0; i < 5; ++i) अणु
		retval = pyra_get_profile_settings(usb_dev,
				&pyra->profile_settings[i], i);
		अगर (retval)
			वापस retval;
	पूर्ण

	profile_activated(pyra, settings.startup_profile);

	वापस 0;
पूर्ण

अटल पूर्णांक pyra_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा pyra_device *pyra;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_MOUSE) अणु

		pyra = kzalloc(माप(*pyra), GFP_KERNEL);
		अगर (!pyra) अणु
			hid_err(hdev, "can't alloc device descriptor\n");
			वापस -ENOMEM;
		पूर्ण
		hid_set_drvdata(hdev, pyra);

		retval = pyra_init_pyra_device_काष्ठा(usb_dev, pyra);
		अगर (retval) अणु
			hid_err(hdev, "couldn't init struct pyra_device\n");
			जाओ निकास_मुक्त;
		पूर्ण

		retval = roccat_connect(pyra_class, hdev,
				माप(काष्ठा pyra_roccat_report));
		अगर (retval < 0) अणु
			hid_err(hdev, "couldn't init char dev\n");
		पूर्ण अन्यथा अणु
			pyra->chrdev_minor = retval;
			pyra->roccat_claimed = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		hid_set_drvdata(hdev, शून्य);
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(pyra);
	वापस retval;
पूर्ण

अटल व्योम pyra_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा pyra_device *pyra;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_MOUSE) अणु
		pyra = hid_get_drvdata(hdev);
		अगर (pyra->roccat_claimed)
			roccat_disconnect(pyra->chrdev_minor);
		kमुक्त(hid_get_drvdata(hdev));
	पूर्ण
पूर्ण

अटल पूर्णांक pyra_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
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

	retval = pyra_init_specials(hdev);
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

अटल व्योम pyra_हटाओ(काष्ठा hid_device *hdev)
अणु
	pyra_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल व्योम pyra_keep_values_up_to_date(काष्ठा pyra_device *pyra,
		u8 स्थिर *data)
अणु
	काष्ठा pyra_mouse_event_button स्थिर *button_event;

	चयन (data[0]) अणु
	हाल PYRA_MOUSE_REPORT_NUMBER_BUTTON:
		button_event = (काष्ठा pyra_mouse_event_button स्थिर *)data;
		चयन (button_event->type) अणु
		हाल PYRA_MOUSE_EVENT_BUTTON_TYPE_PROखाता_2:
			profile_activated(pyra, button_event->data1 - 1);
			अवरोध;
		हाल PYRA_MOUSE_EVENT_BUTTON_TYPE_CPI:
			pyra->actual_cpi = button_event->data1;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pyra_report_to_chrdev(काष्ठा pyra_device स्थिर *pyra,
		u8 स्थिर *data)
अणु
	काष्ठा pyra_roccat_report roccat_report;
	काष्ठा pyra_mouse_event_button स्थिर *button_event;

	अगर (data[0] != PYRA_MOUSE_REPORT_NUMBER_BUTTON)
		वापस;

	button_event = (काष्ठा pyra_mouse_event_button स्थिर *)data;

	चयन (button_event->type) अणु
	हाल PYRA_MOUSE_EVENT_BUTTON_TYPE_PROखाता_2:
	हाल PYRA_MOUSE_EVENT_BUTTON_TYPE_CPI:
		roccat_report.type = button_event->type;
		roccat_report.value = button_event->data1;
		roccat_report.key = 0;
		roccat_report_event(pyra->chrdev_minor,
				(uपूर्णांक8_t स्थिर *)&roccat_report);
		अवरोध;
	हाल PYRA_MOUSE_EVENT_BUTTON_TYPE_MACRO:
	हाल PYRA_MOUSE_EVENT_BUTTON_TYPE_SHORTCUT:
	हाल PYRA_MOUSE_EVENT_BUTTON_TYPE_QUICKLAUNCH:
		अगर (button_event->data2 == PYRA_MOUSE_EVENT_BUTTON_PRESS) अणु
			roccat_report.type = button_event->type;
			roccat_report.key = button_event->data1;
			/*
			 * pyra reports profile numbers with range 1-5.
			 * Keeping this behaviour.
			 */
			roccat_report.value = pyra->actual_profile + 1;
			roccat_report_event(pyra->chrdev_minor,
					(uपूर्णांक8_t स्थिर *)&roccat_report);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक pyra_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *data, पूर्णांक size)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा pyra_device *pyra = hid_get_drvdata(hdev);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE)
		वापस 0;

	अगर (pyra == शून्य)
		वापस 0;

	pyra_keep_values_up_to_date(pyra, data);

	अगर (pyra->roccat_claimed)
		pyra_report_to_chrdev(pyra, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id pyra_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT,
			USB_DEVICE_ID_ROCCAT_PYRA_WIRED) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT,
			USB_DEVICE_ID_ROCCAT_PYRA_WIRELESS) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, pyra_devices);

अटल काष्ठा hid_driver pyra_driver = अणु
		.name = "pyra",
		.id_table = pyra_devices,
		.probe = pyra_probe,
		.हटाओ = pyra_हटाओ,
		.raw_event = pyra_raw_event
पूर्ण;

अटल पूर्णांक __init pyra_init(व्योम)
अणु
	पूर्णांक retval;

	/* class name has to be same as driver name */
	pyra_class = class_create(THIS_MODULE, "pyra");
	अगर (IS_ERR(pyra_class))
		वापस PTR_ERR(pyra_class);
	pyra_class->dev_groups = pyra_groups;

	retval = hid_रेजिस्टर_driver(&pyra_driver);
	अगर (retval)
		class_destroy(pyra_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास pyra_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&pyra_driver);
	class_destroy(pyra_class);
पूर्ण

module_init(pyra_init);
module_निकास(pyra_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Pyra driver");
MODULE_LICENSE("GPL v2");
