<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Isku driver क्रम Linux
 *
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Roccat Isku is a gamer keyboard with macro keys that can be configured in
 * 5 profiles.
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid-roccat.h>
#समावेश "hid-ids.h"
#समावेश "hid-roccat-common.h"
#समावेश "hid-roccat-isku.h"

अटल काष्ठा class *isku_class;

अटल व्योम isku_profile_activated(काष्ठा isku_device *isku, uपूर्णांक new_profile)
अणु
	isku->actual_profile = new_profile;
पूर्ण

अटल पूर्णांक isku_receive(काष्ठा usb_device *usb_dev, uपूर्णांक command,
		व्योम *buf, uपूर्णांक size)
अणु
	वापस roccat_common2_receive(usb_dev, command, buf, size);
पूर्ण

अटल पूर्णांक isku_get_actual_profile(काष्ठा usb_device *usb_dev)
अणु
	काष्ठा isku_actual_profile buf;
	पूर्णांक retval;

	retval = isku_receive(usb_dev, ISKU_COMMAND_ACTUAL_PROखाता,
			&buf, माप(काष्ठा isku_actual_profile));
	वापस retval ? retval : buf.actual_profile;
पूर्ण

अटल पूर्णांक isku_set_actual_profile(काष्ठा usb_device *usb_dev, पूर्णांक new_profile)
अणु
	काष्ठा isku_actual_profile buf;

	buf.command = ISKU_COMMAND_ACTUAL_PROखाता;
	buf.size = माप(काष्ठा isku_actual_profile);
	buf.actual_profile = new_profile;
	वापस roccat_common2_send_with_status(usb_dev,
			ISKU_COMMAND_ACTUAL_PROखाता, &buf,
			माप(काष्ठा isku_actual_profile));
पूर्ण

अटल sमाप_प्रकार isku_sysfs_show_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा isku_device *isku =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", isku->actual_profile);
पूर्ण

अटल sमाप_प्रकार isku_sysfs_set_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर स्थिर *buf, माप_प्रकार size)
अणु
	काष्ठा isku_device *isku;
	काष्ठा usb_device *usb_dev;
	अचिन्हित दीर्घ profile;
	पूर्णांक retval;
	काष्ठा isku_roccat_report roccat_report;

	dev = dev->parent->parent;
	isku = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));

	retval = kम_से_अदीर्घ(buf, 10, &profile);
	अगर (retval)
		वापस retval;

	अगर (profile > 4)
		वापस -EINVAL;

	mutex_lock(&isku->isku_lock);

	retval = isku_set_actual_profile(usb_dev, profile);
	अगर (retval) अणु
		mutex_unlock(&isku->isku_lock);
		वापस retval;
	पूर्ण

	isku_profile_activated(isku, profile);

	roccat_report.event = ISKU_REPORT_BUTTON_EVENT_PROखाता;
	roccat_report.data1 = profile + 1;
	roccat_report.data2 = 0;
	roccat_report.profile = profile + 1;
	roccat_report_event(isku->chrdev_minor, (uपूर्णांक8_t स्थिर *)&roccat_report);

	mutex_unlock(&isku->isku_lock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR(actual_profile, 0660, isku_sysfs_show_actual_profile,
		   isku_sysfs_set_actual_profile);

अटल काष्ठा attribute *isku_attrs[] = अणु
	&dev_attr_actual_profile.attr,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार isku_sysfs_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
		अक्षर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा isku_device *isku = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off >= real_size)
		वापस 0;

	अगर (off != 0 || count > real_size)
		वापस -EINVAL;

	mutex_lock(&isku->isku_lock);
	retval = isku_receive(usb_dev, command, buf, count);
	mutex_unlock(&isku->isku_lock);

	वापस retval ? retval : count;
पूर्ण

अटल sमाप_प्रकार isku_sysfs_ग_लिखो(काष्ठा file *fp, काष्ठा kobject *kobj,
		व्योम स्थिर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा isku_device *isku = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off != 0 || count > real_size)
		वापस -EINVAL;

	mutex_lock(&isku->isku_lock);
	retval = roccat_common2_send_with_status(usb_dev, command,
			(व्योम *)buf, count);
	mutex_unlock(&isku->isku_lock);

	वापस retval ? retval : count;
पूर्ण

#घोषणा ISKU_SYSFS_W(thingy, THINGY) \
अटल sमाप_प्रकार isku_sysfs_ग_लिखो_ ## thingy(काष्ठा file *fp, काष्ठा kobject *kobj, \
		काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस isku_sysfs_ग_लिखो(fp, kobj, buf, off, count, \
			ISKU_SIZE_ ## THINGY, ISKU_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा ISKU_SYSFS_R(thingy, THINGY) \
अटल sमाप_प्रकार isku_sysfs_पढ़ो_ ## thingy(काष्ठा file *fp, काष्ठा kobject *kobj, \
		काष्ठा bin_attribute *attr, अक्षर *buf, \
		loff_t off, माप_प्रकार count) \
अणु \
	वापस isku_sysfs_पढ़ो(fp, kobj, buf, off, count, \
			ISKU_SIZE_ ## THINGY, ISKU_COMMAND_ ## THINGY); \
पूर्ण

#घोषणा ISKU_SYSFS_RW(thingy, THINGY) \
ISKU_SYSFS_R(thingy, THINGY) \
ISKU_SYSFS_W(thingy, THINGY)

#घोषणा ISKU_BIN_ATTR_RW(thingy, THINGY) \
ISKU_SYSFS_RW(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0660 पूर्ण, \
	.size = ISKU_SIZE_ ## THINGY, \
	.पढ़ो = isku_sysfs_पढ़ो_ ## thingy, \
	.ग_लिखो = isku_sysfs_ग_लिखो_ ## thingy \
पूर्ण

#घोषणा ISKU_BIN_ATTR_R(thingy, THINGY) \
ISKU_SYSFS_R(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0440 पूर्ण, \
	.size = ISKU_SIZE_ ## THINGY, \
	.पढ़ो = isku_sysfs_पढ़ो_ ## thingy, \
पूर्ण

#घोषणा ISKU_BIN_ATTR_W(thingy, THINGY) \
ISKU_SYSFS_W(thingy, THINGY); \
अटल काष्ठा bin_attribute bin_attr_##thingy = अणु \
	.attr = अणु .name = #thingy, .mode = 0220 पूर्ण, \
	.size = ISKU_SIZE_ ## THINGY, \
	.ग_लिखो = isku_sysfs_ग_लिखो_ ## thingy \
पूर्ण

ISKU_BIN_ATTR_RW(macro, MACRO);
ISKU_BIN_ATTR_RW(keys_function, KEYS_FUNCTION);
ISKU_BIN_ATTR_RW(keys_easyzone, KEYS_EASYZONE);
ISKU_BIN_ATTR_RW(keys_media, KEYS_MEDIA);
ISKU_BIN_ATTR_RW(keys_thumbster, KEYS_THUMBSTER);
ISKU_BIN_ATTR_RW(keys_macro, KEYS_MACRO);
ISKU_BIN_ATTR_RW(keys_capslock, KEYS_CAPSLOCK);
ISKU_BIN_ATTR_RW(light, LIGHT);
ISKU_BIN_ATTR_RW(key_mask, KEY_MASK);
ISKU_BIN_ATTR_RW(last_set, LAST_SET);
ISKU_BIN_ATTR_W(talk, TALK);
ISKU_BIN_ATTR_W(talkfx, TALKFX);
ISKU_BIN_ATTR_W(control, CONTROL);
ISKU_BIN_ATTR_W(reset, RESET);
ISKU_BIN_ATTR_R(info, INFO);

अटल काष्ठा bin_attribute *isku_bin_attributes[] = अणु
	&bin_attr_macro,
	&bin_attr_keys_function,
	&bin_attr_keys_easyzone,
	&bin_attr_keys_media,
	&bin_attr_keys_thumbster,
	&bin_attr_keys_macro,
	&bin_attr_keys_capslock,
	&bin_attr_light,
	&bin_attr_key_mask,
	&bin_attr_last_set,
	&bin_attr_talk,
	&bin_attr_talkfx,
	&bin_attr_control,
	&bin_attr_reset,
	&bin_attr_info,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group isku_group = अणु
	.attrs = isku_attrs,
	.bin_attrs = isku_bin_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *isku_groups[] = अणु
	&isku_group,
	शून्य,
पूर्ण;

अटल पूर्णांक isku_init_isku_device_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा isku_device *isku)
अणु
	पूर्णांक retval;

	mutex_init(&isku->isku_lock);

	retval = isku_get_actual_profile(usb_dev);
	अगर (retval < 0)
		वापस retval;
	isku_profile_activated(isku, retval);

	वापस 0;
पूर्ण

अटल पूर्णांक isku_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा isku_device *isku;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= ISKU_USB_INTERFACE_PROTOCOL) अणु
		hid_set_drvdata(hdev, शून्य);
		वापस 0;
	पूर्ण

	isku = kzalloc(माप(*isku), GFP_KERNEL);
	अगर (!isku) अणु
		hid_err(hdev, "can't alloc device descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	hid_set_drvdata(hdev, isku);

	retval = isku_init_isku_device_काष्ठा(usb_dev, isku);
	अगर (retval) अणु
		hid_err(hdev, "couldn't init struct isku_device\n");
		जाओ निकास_मुक्त;
	पूर्ण

	retval = roccat_connect(isku_class, hdev,
			माप(काष्ठा isku_roccat_report));
	अगर (retval < 0) अणु
		hid_err(hdev, "couldn't init char dev\n");
	पूर्ण अन्यथा अणु
		isku->chrdev_minor = retval;
		isku->roccat_claimed = 1;
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(isku);
	वापस retval;
पूर्ण

अटल व्योम isku_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा isku_device *isku;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= ISKU_USB_INTERFACE_PROTOCOL)
		वापस;

	isku = hid_get_drvdata(hdev);
	अगर (isku->roccat_claimed)
		roccat_disconnect(isku->chrdev_minor);
	kमुक्त(isku);
पूर्ण

अटल पूर्णांक isku_probe(काष्ठा hid_device *hdev,
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

	retval = isku_init_specials(hdev);
	अगर (retval) अणु
		hid_err(hdev, "couldn't install keyboard\n");
		जाओ निकास_stop;
	पूर्ण

	वापस 0;

निकास_stop:
	hid_hw_stop(hdev);
निकास:
	वापस retval;
पूर्ण

अटल व्योम isku_हटाओ(काष्ठा hid_device *hdev)
अणु
	isku_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल व्योम isku_keep_values_up_to_date(काष्ठा isku_device *isku,
		u8 स्थिर *data)
अणु
	काष्ठा isku_report_button स्थिर *button_report;

	चयन (data[0]) अणु
	हाल ISKU_REPORT_NUMBER_BUTTON:
		button_report = (काष्ठा isku_report_button स्थिर *)data;
		चयन (button_report->event) अणु
		हाल ISKU_REPORT_BUTTON_EVENT_PROखाता:
			isku_profile_activated(isku, button_report->data1 - 1);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम isku_report_to_chrdev(काष्ठा isku_device स्थिर *isku,
		u8 स्थिर *data)
अणु
	काष्ठा isku_roccat_report roccat_report;
	काष्ठा isku_report_button स्थिर *button_report;

	अगर (data[0] != ISKU_REPORT_NUMBER_BUTTON)
		वापस;

	button_report = (काष्ठा isku_report_button स्थिर *)data;

	roccat_report.event = button_report->event;
	roccat_report.data1 = button_report->data1;
	roccat_report.data2 = button_report->data2;
	roccat_report.profile = isku->actual_profile + 1;
	roccat_report_event(isku->chrdev_minor,
			(uपूर्णांक8_t स्थिर *)&roccat_report);
पूर्ण

अटल पूर्णांक isku_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा isku_device *isku = hid_get_drvdata(hdev);

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			!= ISKU_USB_INTERFACE_PROTOCOL)
		वापस 0;

	अगर (isku == शून्य)
		वापस 0;

	isku_keep_values_up_to_date(isku, data);

	अगर (isku->roccat_claimed)
		isku_report_to_chrdev(isku, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id isku_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_ISKU) पूर्ण,
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_ISKUFX) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, isku_devices);

अटल काष्ठा hid_driver isku_driver = अणु
		.name = "isku",
		.id_table = isku_devices,
		.probe = isku_probe,
		.हटाओ = isku_हटाओ,
		.raw_event = isku_raw_event
पूर्ण;

अटल पूर्णांक __init isku_init(व्योम)
अणु
	पूर्णांक retval;
	isku_class = class_create(THIS_MODULE, "isku");
	अगर (IS_ERR(isku_class))
		वापस PTR_ERR(isku_class);
	isku_class->dev_groups = isku_groups;

	retval = hid_रेजिस्टर_driver(&isku_driver);
	अगर (retval)
		class_destroy(isku_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास isku_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&isku_driver);
	class_destroy(isku_class);
पूर्ण

module_init(isku_init);
module_निकास(isku_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Isku/FX driver");
MODULE_LICENSE("GPL v2");
