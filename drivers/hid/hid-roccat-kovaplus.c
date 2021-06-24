<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Kova[+] driver क्रम Linux
 *
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Roccat Kova[+] is a bigger version of the Pyra with two more side buttons.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid-roccat.h>
#समावेश "hid-ids.h"
#समावेश "hid-roccat-common.h"
#समावेश "hid-roccat-kovaplus.h"

अटल uपूर्णांक profile_numbers[5] = अणु0, 1, 2, 3, 4पूर्ण;

अटल काष्ठा class *kovaplus_class;

अटल uपूर्णांक kovaplus_convert_event_cpi(uपूर्णांक value)
अणु
	वापस (value == 7 ? 4 : (value == 4 ? 3 : value));
पूर्ण

अटल व्योम kovaplus_profile_activated(काष्ठा kovaplus_device *kovaplus,
		uपूर्णांक new_profile_index)
अणु
	अगर (new_profile_index >= ARRAY_SIZE(kovaplus->profile_settings))
		वापस;
	kovaplus->actual_profile = new_profile_index;
	kovaplus->actual_cpi = kovaplus->profile_settings[new_profile_index].cpi_startup_level;
	kovaplus->actual_x_sensitivity = kovaplus->profile_settings[new_profile_index].sensitivity_x;
	kovaplus->actual_y_sensitivity = kovaplus->profile_settings[new_profile_index].sensitivity_y;
पूर्ण

अटल पूर्णांक kovaplus_send_control(काष्ठा usb_device *usb_dev, uपूर्णांक value,
		क्रमागत kovaplus_control_requests request)
अणु
	पूर्णांक retval;
	काष्ठा roccat_common2_control control;

	अगर ((request == KOVAPLUS_CONTROL_REQUEST_PROखाता_SETTINGS ||
			request == KOVAPLUS_CONTROL_REQUEST_PROखाता_BUTTONS) &&
			value > 4)
		वापस -EINVAL;

	control.command = ROCCAT_COMMON_COMMAND_CONTROL;
	control.value = value;
	control.request = request;

	retval = roccat_common2_send(usb_dev, ROCCAT_COMMON_COMMAND_CONTROL,
			&control, माप(काष्ठा roccat_common2_control));

	वापस retval;
पूर्ण

अटल पूर्णांक kovaplus_select_profile(काष्ठा usb_device *usb_dev, uपूर्णांक number,
		क्रमागत kovaplus_control_requests request)
अणु
	वापस kovaplus_send_control(usb_dev, number, request);
पूर्ण

अटल पूर्णांक kovaplus_get_profile_settings(काष्ठा usb_device *usb_dev,
		काष्ठा kovaplus_profile_settings *buf, uपूर्णांक number)
अणु
	पूर्णांक retval;

	retval = kovaplus_select_profile(usb_dev, number,
			KOVAPLUS_CONTROL_REQUEST_PROखाता_SETTINGS);
	अगर (retval)
		वापस retval;

	वापस roccat_common2_receive(usb_dev, KOVAPLUS_COMMAND_PROखाता_SETTINGS,
			buf, KOVAPLUS_SIZE_PROखाता_SETTINGS);
पूर्ण

अटल पूर्णांक kovaplus_get_profile_buttons(काष्ठा usb_device *usb_dev,
		काष्ठा kovaplus_profile_buttons *buf, पूर्णांक number)
अणु
	पूर्णांक retval;

	retval = kovaplus_select_profile(usb_dev, number,
			KOVAPLUS_CONTROL_REQUEST_PROखाता_BUTTONS);
	अगर (retval)
		वापस retval;

	वापस roccat_common2_receive(usb_dev, KOVAPLUS_COMMAND_PROखाता_BUTTONS,
			buf, KOVAPLUS_SIZE_PROखाता_BUTTONS);
पूर्ण

/* retval is 0-4 on success, < 0 on error */
अटल पूर्णांक kovaplus_get_actual_profile(काष्ठा usb_device *usb_dev)
अणु
	काष्ठा kovaplus_actual_profile buf;
	पूर्णांक retval;

	retval = roccat_common2_receive(usb_dev, KOVAPLUS_COMMAND_ACTUAL_PROखाता,
			&buf, माप(काष्ठा kovaplus_actual_profile));

	वापस retval ? retval : buf.actual_profile;
पूर्ण

अटल पूर्णांक kovaplus_set_actual_profile(काष्ठा usb_device *usb_dev,
		पूर्णांक new_profile)
अणु
	काष्ठा kovaplus_actual_profile buf;

	buf.command = KOVAPLUS_COMMAND_ACTUAL_PROखाता;
	buf.size = माप(काष्ठा kovaplus_actual_profile);
	buf.actual_profile = new_profile;

	वापस roccat_common2_send_with_status(usb_dev,
			KOVAPLUS_COMMAND_ACTUAL_PROखाता,
			&buf, माप(काष्ठा kovaplus_actual_profile));
पूर्ण

अटल sमाप_प्रकार kovaplus_sysfs_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
		अक्षर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा kovaplus_device *kovaplus = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off >= real_size)
		वापस 0;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&kovaplus->kovaplus_lock);
	retval = roccat_common2_receive(usb_dev, command, buf, real_size);
	mutex_unlock(&kovaplus->kovaplus_lock);

	अगर (retval)
		वापस retval;

	वापस real_size;
पूर्ण

अटल sमाप_प्रकार kovaplus_sysfs_ग_लिखो(काष्ठा file *fp, काष्ठा kobject *kobj,
		व्योम स्थिर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा kovaplus_device *kovaplus = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&kovaplus->kovaplus_lock);
	retval = roccat_common2_send_with_status(usb_dev, command,
			buf, real_size);
	mutex_unlock(&kovaplus->kovaplus_lock);

	अगर (retval)
		वापस retval;

	वापस real_size;
पूर्ण

#घोषणा KOVAPLUS_SYSFS_W(thingy, THINGY) \
अटल sमाप_प्रकार kovaplus_sysfs_ग_लिखो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस kovaplus_sysfs_ग_लिखो(fp, kobj, buf, off, count, \
			KOVAPLUS_SIZE_ ## THINGY, KOVAPLUS_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा KOVAPLUS_SYSFS_R(thingy, THINGY) \
अटल sमाप_प्रकार kovaplus_sysfs_पढ़ो_ ## thingy(काष्ठा file *fp, \
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस kovaplus_sysfs_पढ़ो(fp, kobj, buf, off, count, \
			KOVAPLUS_SIZE_ ## THINGY, KOVAPLUS_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा KOVAPLUS_SYSFS_RW(thingy, THINGY) \
KOVAPLUS_SYSFS_W(thingy, THINGY) \
KOVAPLUS_SYSFS_R(thingy, THINGY)

#घोषणा KOVAPLUS_BIN_ATTRIBUTE_RW(thingy, THINGY) \
KOVAPLUS_SYSFS_RW(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0660 पूर्ण, \
	.size = KOVAPLUS_SIZE_ ## THINGY, \
	.पढ़ो = kovaplus_sysfs_पढ़ो_ ## thingy, \
	.ग_लिखो = kovaplus_sysfs_ग_लिखो_ ## thingy \
पूर्ण

#घोषणा KOVAPLUS_BIN_ATTRIBUTE_W(thingy, THINGY) \
KOVAPLUS_SYSFS_W(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0220 पूर्ण, \
	.size = KOVAPLUS_SIZE_ ## THINGY, \
	.ग_लिखो = kovaplus_sysfs_ग_लिखो_ ## thingy \
पूर्ण
KOVAPLUS_BIN_ATTRIBUTE_W(control, CONTROL);
KOVAPLUS_BIN_ATTRIBUTE_RW(info, INFO);
KOVAPLUS_BIN_ATTRIBUTE_RW(profile_settings, PROखाता_SETTINGS);
KOVAPLUS_BIN_ATTRIBUTE_RW(profile_buttons, PROखाता_BUTTONS);

अटल sमाप_प्रकार kovaplus_sysfs_पढ़ो_profilex_settings(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	sमाप_प्रकार retval;

	retval = kovaplus_select_profile(usb_dev, *(uपूर्णांक *)(attr->निजी),
			KOVAPLUS_CONTROL_REQUEST_PROखाता_SETTINGS);
	अगर (retval)
		वापस retval;

	वापस kovaplus_sysfs_पढ़ो(fp, kobj, buf, off, count,
			KOVAPLUS_SIZE_PROखाता_SETTINGS,
			KOVAPLUS_COMMAND_PROखाता_SETTINGS);
पूर्ण

अटल sमाप_प्रकार kovaplus_sysfs_पढ़ो_profilex_buttons(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	sमाप_प्रकार retval;

	retval = kovaplus_select_profile(usb_dev, *(uपूर्णांक *)(attr->निजी),
			KOVAPLUS_CONTROL_REQUEST_PROखाता_BUTTONS);
	अगर (retval)
		वापस retval;

	वापस kovaplus_sysfs_पढ़ो(fp, kobj, buf, off, count,
			KOVAPLUS_SIZE_PROखाता_BUTTONS,
			KOVAPLUS_COMMAND_PROखाता_BUTTONS);
पूर्ण

#घोषणा PROखाता_ATTR(number)						\
अटल काष्ठा bin_attribute bin_attr_profile##number##_settings = अणु	\
	.attr = अणु .name = "profile" #number "_settings", .mode = 0440 पूर्ण,	\
	.size = KOVAPLUS_SIZE_PROखाता_SETTINGS,				\
	.पढ़ो = kovaplus_sysfs_पढ़ो_profilex_settings,			\
	.निजी = &profile_numbers[number-1],				\
पूर्ण;									\
अटल काष्ठा bin_attribute bin_attr_profile##number##_buttons = अणु	\
	.attr = अणु .name = "profile" #number "_buttons", .mode = 0440 पूर्ण,	\
	.size = KOVAPLUS_SIZE_PROखाता_BUTTONS,				\
	.पढ़ो = kovaplus_sysfs_पढ़ो_profilex_buttons,			\
	.निजी = &profile_numbers[number-1],				\
पूर्ण;
PROखाता_ATTR(1);
PROखाता_ATTR(2);
PROखाता_ATTR(3);
PROखाता_ATTR(4);
PROखाता_ATTR(5);

अटल sमाप_प्रकार kovaplus_sysfs_show_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kovaplus_device *kovaplus =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kovaplus->actual_profile);
पूर्ण

अटल sमाप_प्रकार kovaplus_sysfs_set_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर स्थिर *buf, माप_प्रकार size)
अणु
	काष्ठा kovaplus_device *kovaplus;
	काष्ठा usb_device *usb_dev;
	अचिन्हित दीर्घ profile;
	पूर्णांक retval;
	काष्ठा kovaplus_roccat_report roccat_report;

	dev = dev->parent->parent;
	kovaplus = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));

	retval = kम_से_अदीर्घ(buf, 10, &profile);
	अगर (retval)
		वापस retval;

	अगर (profile >= 5)
		वापस -EINVAL;

	mutex_lock(&kovaplus->kovaplus_lock);
	retval = kovaplus_set_actual_profile(usb_dev, profile);
	अगर (retval) अणु
		mutex_unlock(&kovaplus->kovaplus_lock);
		वापस retval;
	पूर्ण

	kovaplus_profile_activated(kovaplus, profile);

	roccat_report.type = KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROखाता_1;
	roccat_report.profile = profile + 1;
	roccat_report.button = 0;
	roccat_report.data1 = profile + 1;
	roccat_report.data2 = 0;
	roccat_report_event(kovaplus->chrdev_minor,
			(uपूर्णांक8_t स्थिर *)&roccat_report);

	mutex_unlock(&kovaplus->kovaplus_lock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR(actual_profile, 0660,
		   kovaplus_sysfs_show_actual_profile,
		   kovaplus_sysfs_set_actual_profile);

अटल sमाप_प्रकार kovaplus_sysfs_show_actual_cpi(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kovaplus_device *kovaplus =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kovaplus->actual_cpi);
पूर्ण
अटल DEVICE_ATTR(actual_cpi, 0440, kovaplus_sysfs_show_actual_cpi, शून्य);

अटल sमाप_प्रकार kovaplus_sysfs_show_actual_sensitivity_x(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kovaplus_device *kovaplus =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kovaplus->actual_x_sensitivity);
पूर्ण
अटल DEVICE_ATTR(actual_sensitivity_x, 0440,
		   kovaplus_sysfs_show_actual_sensitivity_x, शून्य);

अटल sमाप_प्रकार kovaplus_sysfs_show_actual_sensitivity_y(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kovaplus_device *kovaplus =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kovaplus->actual_y_sensitivity);
पूर्ण
अटल DEVICE_ATTR(actual_sensitivity_y, 0440,
		   kovaplus_sysfs_show_actual_sensitivity_y, शून्य);

अटल sमाप_प्रकार kovaplus_sysfs_show_firmware_version(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kovaplus_device *kovaplus;
	काष्ठा usb_device *usb_dev;
	काष्ठा kovaplus_info info;

	dev = dev->parent->parent;
	kovaplus = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));

	mutex_lock(&kovaplus->kovaplus_lock);
	roccat_common2_receive(usb_dev, KOVAPLUS_COMMAND_INFO,
			&info, KOVAPLUS_SIZE_INFO);
	mutex_unlock(&kovaplus->kovaplus_lock);

	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", info.firmware_version);
पूर्ण
अटल DEVICE_ATTR(firmware_version, 0440,
		   kovaplus_sysfs_show_firmware_version, शून्य);

अटल काष्ठा attribute *kovaplus_attrs[] = अणु
	&dev_attr_actual_cpi.attr,
	&dev_attr_firmware_version.attr,
	&dev_attr_actual_profile.attr,
	&dev_attr_actual_sensitivity_x.attr,
	&dev_attr_actual_sensitivity_y.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *kovaplus_bin_attributes[] = अणु
	&bin_attr_control,
	&bin_attr_info,
	&bin_attr_profile_settings,
	&bin_attr_profile_buttons,
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

अटल स्थिर काष्ठा attribute_group kovaplus_group = अणु
	.attrs = kovaplus_attrs,
	.bin_attrs = kovaplus_bin_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *kovaplus_groups[] = अणु
	&kovaplus_group,
	शून्य,
पूर्ण;

अटल पूर्णांक kovaplus_init_kovaplus_device_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा kovaplus_device *kovaplus)
अणु
	पूर्णांक retval, i;
	अटल uपूर्णांक रुको = 70; /* device will मुक्तze with just 60 */

	mutex_init(&kovaplus->kovaplus_lock);

	क्रम (i = 0; i < 5; ++i) अणु
		msleep(रुको);
		retval = kovaplus_get_profile_settings(usb_dev,
				&kovaplus->profile_settings[i], i);
		अगर (retval)
			वापस retval;

		msleep(रुको);
		retval = kovaplus_get_profile_buttons(usb_dev,
				&kovaplus->profile_buttons[i], i);
		अगर (retval)
			वापस retval;
	पूर्ण

	msleep(रुको);
	retval = kovaplus_get_actual_profile(usb_dev);
	अगर (retval < 0)
		वापस retval;
	kovaplus_profile_activated(kovaplus, retval);

	वापस 0;
पूर्ण

अटल पूर्णांक kovaplus_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा kovaplus_device *kovaplus;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_MOUSE) अणु

		kovaplus = kzalloc(माप(*kovaplus), GFP_KERNEL);
		अगर (!kovaplus) अणु
			hid_err(hdev, "can't alloc device descriptor\n");
			वापस -ENOMEM;
		पूर्ण
		hid_set_drvdata(hdev, kovaplus);

		retval = kovaplus_init_kovaplus_device_काष्ठा(usb_dev, kovaplus);
		अगर (retval) अणु
			hid_err(hdev, "couldn't init struct kovaplus_device\n");
			जाओ निकास_मुक्त;
		पूर्ण

		retval = roccat_connect(kovaplus_class, hdev,
				माप(काष्ठा kovaplus_roccat_report));
		अगर (retval < 0) अणु
			hid_err(hdev, "couldn't init char dev\n");
		पूर्ण अन्यथा अणु
			kovaplus->chrdev_minor = retval;
			kovaplus->roccat_claimed = 1;
		पूर्ण

	पूर्ण अन्यथा अणु
		hid_set_drvdata(hdev, शून्य);
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(kovaplus);
	वापस retval;
पूर्ण

अटल व्योम kovaplus_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा kovaplus_device *kovaplus;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_MOUSE) अणु
		kovaplus = hid_get_drvdata(hdev);
		अगर (kovaplus->roccat_claimed)
			roccat_disconnect(kovaplus->chrdev_minor);
		kमुक्त(kovaplus);
	पूर्ण
पूर्ण

अटल पूर्णांक kovaplus_probe(काष्ठा hid_device *hdev,
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

	retval = kovaplus_init_specials(hdev);
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

अटल व्योम kovaplus_हटाओ(काष्ठा hid_device *hdev)
अणु
	kovaplus_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल व्योम kovaplus_keep_values_up_to_date(काष्ठा kovaplus_device *kovaplus,
		u8 स्थिर *data)
अणु
	काष्ठा kovaplus_mouse_report_button स्थिर *button_report;

	अगर (data[0] != KOVAPLUS_MOUSE_REPORT_NUMBER_BUTTON)
		वापस;

	button_report = (काष्ठा kovaplus_mouse_report_button स्थिर *)data;

	चयन (button_report->type) अणु
	हाल KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROखाता_1:
		kovaplus_profile_activated(kovaplus, button_report->data1 - 1);
		अवरोध;
	हाल KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_CPI:
		kovaplus->actual_cpi = kovaplus_convert_event_cpi(button_report->data1);
		अवरोध;
	हाल KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_SENSITIVITY:
		kovaplus->actual_x_sensitivity = button_report->data1;
		kovaplus->actual_y_sensitivity = button_report->data2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम kovaplus_report_to_chrdev(काष्ठा kovaplus_device स्थिर *kovaplus,
		u8 स्थिर *data)
अणु
	काष्ठा kovaplus_roccat_report roccat_report;
	काष्ठा kovaplus_mouse_report_button स्थिर *button_report;

	अगर (data[0] != KOVAPLUS_MOUSE_REPORT_NUMBER_BUTTON)
		वापस;

	button_report = (काष्ठा kovaplus_mouse_report_button स्थिर *)data;

	अगर (button_report->type == KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_PROखाता_2)
		वापस;

	roccat_report.type = button_report->type;
	roccat_report.profile = kovaplus->actual_profile + 1;

	अगर (roccat_report.type == KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_MACRO ||
			roccat_report.type == KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_SHORTCUT ||
			roccat_report.type == KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_QUICKLAUNCH ||
			roccat_report.type == KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_TIMER)
		roccat_report.button = button_report->data1;
	अन्यथा
		roccat_report.button = 0;

	अगर (roccat_report.type == KOVAPLUS_MOUSE_REPORT_BUTTON_TYPE_CPI)
		roccat_report.data1 = kovaplus_convert_event_cpi(button_report->data1);
	अन्यथा
		roccat_report.data1 = button_report->data1;

	roccat_report.data2 = button_report->data2;

	roccat_report_event(kovaplus->chrdev_minor,
			(uपूर्णांक8_t स्थिर *)&roccat_report);
पूर्ण

अटल पूर्णांक kovaplus_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा kovaplus_device *kovaplus = hid_get_drvdata(hdev);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= USB_INTERFACE_PROTOCOL_MOUSE)
		वापस 0;

	अगर (kovaplus == शून्य)
		वापस 0;

	kovaplus_keep_values_up_to_date(kovaplus, data);

	अगर (kovaplus->roccat_claimed)
		kovaplus_report_to_chrdev(kovaplus, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id kovaplus_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_KOVAPLUS) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, kovaplus_devices);

अटल काष्ठा hid_driver kovaplus_driver = अणु
		.name = "kovaplus",
		.id_table = kovaplus_devices,
		.probe = kovaplus_probe,
		.हटाओ = kovaplus_हटाओ,
		.raw_event = kovaplus_raw_event
पूर्ण;

अटल पूर्णांक __init kovaplus_init(व्योम)
अणु
	पूर्णांक retval;

	kovaplus_class = class_create(THIS_MODULE, "kovaplus");
	अगर (IS_ERR(kovaplus_class))
		वापस PTR_ERR(kovaplus_class);
	kovaplus_class->dev_groups = kovaplus_groups;

	retval = hid_रेजिस्टर_driver(&kovaplus_driver);
	अगर (retval)
		class_destroy(kovaplus_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास kovaplus_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&kovaplus_driver);
	class_destroy(kovaplus_class);
पूर्ण

module_init(kovaplus_init);
module_निकास(kovaplus_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Kova[+] driver");
MODULE_LICENSE("GPL v2");
