<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Arvo driver क्रम Linux
 *
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Roccat Arvo is a gamer keyboard with 5 macro keys that can be configured in
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
#समावेश "hid-roccat-arvo.h"

अटल काष्ठा class *arvo_class;

अटल sमाप_प्रकार arvo_sysfs_show_mode_key(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	काष्ठा usb_device *usb_dev =
			पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev->parent->parent));
	काष्ठा arvo_mode_key temp_buf;
	पूर्णांक retval;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_receive(usb_dev, ARVO_COMMAND_MODE_KEY,
			&temp_buf, माप(काष्ठा arvo_mode_key));
	mutex_unlock(&arvo->arvo_lock);
	अगर (retval)
		वापस retval;

	वापस sysfs_emit(buf, "%d\n", temp_buf.state);
पूर्ण

अटल sमाप_प्रकार arvo_sysfs_set_mode_key(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर स्थिर *buf, माप_प्रकार size)
अणु
	काष्ठा arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	काष्ठा usb_device *usb_dev =
			पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev->parent->parent));
	काष्ठा arvo_mode_key temp_buf;
	अचिन्हित दीर्घ state;
	पूर्णांक retval;

	retval = kम_से_अदीर्घ(buf, 10, &state);
	अगर (retval)
		वापस retval;

	temp_buf.command = ARVO_COMMAND_MODE_KEY;
	temp_buf.state = state;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_send(usb_dev, ARVO_COMMAND_MODE_KEY,
			&temp_buf, माप(काष्ठा arvo_mode_key));
	mutex_unlock(&arvo->arvo_lock);
	अगर (retval)
		वापस retval;

	वापस size;
पूर्ण
अटल DEVICE_ATTR(mode_key, 0660,
		   arvo_sysfs_show_mode_key, arvo_sysfs_set_mode_key);

अटल sमाप_प्रकार arvo_sysfs_show_key_mask(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	काष्ठा usb_device *usb_dev =
			पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev->parent->parent));
	काष्ठा arvo_key_mask temp_buf;
	पूर्णांक retval;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_receive(usb_dev, ARVO_COMMAND_KEY_MASK,
			&temp_buf, माप(काष्ठा arvo_key_mask));
	mutex_unlock(&arvo->arvo_lock);
	अगर (retval)
		वापस retval;

	वापस sysfs_emit(buf, "%d\n", temp_buf.key_mask);
पूर्ण

अटल sमाप_प्रकार arvo_sysfs_set_key_mask(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर स्थिर *buf, माप_प्रकार size)
अणु
	काष्ठा arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	काष्ठा usb_device *usb_dev =
			पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev->parent->parent));
	काष्ठा arvo_key_mask temp_buf;
	अचिन्हित दीर्घ key_mask;
	पूर्णांक retval;

	retval = kम_से_अदीर्घ(buf, 10, &key_mask);
	अगर (retval)
		वापस retval;

	temp_buf.command = ARVO_COMMAND_KEY_MASK;
	temp_buf.key_mask = key_mask;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_send(usb_dev, ARVO_COMMAND_KEY_MASK,
			&temp_buf, माप(काष्ठा arvo_key_mask));
	mutex_unlock(&arvo->arvo_lock);
	अगर (retval)
		वापस retval;

	वापस size;
पूर्ण
अटल DEVICE_ATTR(key_mask, 0660,
		   arvo_sysfs_show_key_mask, arvo_sysfs_set_key_mask);

/* retval is 1-5 on success, < 0 on error */
अटल पूर्णांक arvo_get_actual_profile(काष्ठा usb_device *usb_dev)
अणु
	काष्ठा arvo_actual_profile temp_buf;
	पूर्णांक retval;

	retval = roccat_common2_receive(usb_dev, ARVO_COMMAND_ACTUAL_PROखाता,
			&temp_buf, माप(काष्ठा arvo_actual_profile));

	अगर (retval)
		वापस retval;

	वापस temp_buf.actual_profile;
पूर्ण

अटल sमाप_प्रकार arvo_sysfs_show_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));

	वापस sysfs_emit(buf, "%d\n", arvo->actual_profile);
पूर्ण

अटल sमाप_प्रकार arvo_sysfs_set_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर स्थिर *buf, माप_प्रकार size)
अणु
	काष्ठा arvo_device *arvo =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	काष्ठा usb_device *usb_dev =
			पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev->parent->parent));
	काष्ठा arvo_actual_profile temp_buf;
	अचिन्हित दीर्घ profile;
	पूर्णांक retval;

	retval = kम_से_अदीर्घ(buf, 10, &profile);
	अगर (retval)
		वापस retval;

	अगर (profile < 1 || profile > 5)
		वापस -EINVAL;

	temp_buf.command = ARVO_COMMAND_ACTUAL_PROखाता;
	temp_buf.actual_profile = profile;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_send(usb_dev, ARVO_COMMAND_ACTUAL_PROखाता,
			&temp_buf, माप(काष्ठा arvo_actual_profile));
	अगर (!retval) अणु
		arvo->actual_profile = profile;
		retval = size;
	पूर्ण
	mutex_unlock(&arvo->arvo_lock);
	वापस retval;
पूर्ण
अटल DEVICE_ATTR(actual_profile, 0660,
		   arvo_sysfs_show_actual_profile,
		   arvo_sysfs_set_actual_profile);

अटल sमाप_प्रकार arvo_sysfs_ग_लिखो(काष्ठा file *fp,
		काष्ठा kobject *kobj, व्योम स्थिर *buf,
		loff_t off, माप_प्रकार count, माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा arvo_device *arvo = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_send(usb_dev, command, buf, real_size);
	mutex_unlock(&arvo->arvo_lock);

	वापस (retval ? retval : real_size);
पूर्ण

अटल sमाप_प्रकार arvo_sysfs_पढ़ो(काष्ठा file *fp,
		काष्ठा kobject *kobj, व्योम *buf, loff_t off,
		माप_प्रकार count, माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा arvo_device *arvo = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off >= real_size)
		वापस 0;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&arvo->arvo_lock);
	retval = roccat_common2_receive(usb_dev, command, buf, real_size);
	mutex_unlock(&arvo->arvo_lock);

	वापस (retval ? retval : real_size);
पूर्ण

अटल sमाप_प्रकार arvo_sysfs_ग_लिखो_button(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	वापस arvo_sysfs_ग_लिखो(fp, kobj, buf, off, count,
			माप(काष्ठा arvo_button), ARVO_COMMAND_BUTTON);
पूर्ण
अटल BIN_ATTR(button, 0220, शून्य, arvo_sysfs_ग_लिखो_button,
		माप(काष्ठा arvo_button));

अटल sमाप_प्रकार arvo_sysfs_पढ़ो_info(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	वापस arvo_sysfs_पढ़ो(fp, kobj, buf, off, count,
			माप(काष्ठा arvo_info), ARVO_COMMAND_INFO);
पूर्ण
अटल BIN_ATTR(info, 0440, arvo_sysfs_पढ़ो_info, शून्य,
		माप(काष्ठा arvo_info));

अटल काष्ठा attribute *arvo_attrs[] = अणु
	&dev_attr_mode_key.attr,
	&dev_attr_key_mask.attr,
	&dev_attr_actual_profile.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *arvo_bin_attributes[] = अणु
	&bin_attr_button,
	&bin_attr_info,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group arvo_group = अणु
	.attrs = arvo_attrs,
	.bin_attrs = arvo_bin_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *arvo_groups[] = अणु
	&arvo_group,
	शून्य,
पूर्ण;

अटल पूर्णांक arvo_init_arvo_device_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा arvo_device *arvo)
अणु
	पूर्णांक retval;

	mutex_init(&arvo->arvo_lock);

	retval = arvo_get_actual_profile(usb_dev);
	अगर (retval < 0)
		वापस retval;
	arvo->actual_profile = retval;

	वापस 0;
पूर्ण

अटल पूर्णांक arvo_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा arvo_device *arvo;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_KEYBOARD) अणु
		hid_set_drvdata(hdev, शून्य);
		वापस 0;
	पूर्ण

	arvo = kzalloc(माप(*arvo), GFP_KERNEL);
	अगर (!arvo) अणु
		hid_err(hdev, "can't alloc device descriptor\n");
		वापस -ENOMEM;
	पूर्ण
	hid_set_drvdata(hdev, arvo);

	retval = arvo_init_arvo_device_काष्ठा(usb_dev, arvo);
	अगर (retval) अणु
		hid_err(hdev, "couldn't init struct arvo_device\n");
		जाओ निकास_मुक्त;
	पूर्ण

	retval = roccat_connect(arvo_class, hdev,
			माप(काष्ठा arvo_roccat_report));
	अगर (retval < 0) अणु
		hid_err(hdev, "couldn't init char dev\n");
	पूर्ण अन्यथा अणु
		arvo->chrdev_minor = retval;
		arvo->roccat_claimed = 1;
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(arvo);
	वापस retval;
पूर्ण

अटल व्योम arvo_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा arvo_device *arvo;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_KEYBOARD)
		वापस;

	arvo = hid_get_drvdata(hdev);
	अगर (arvo->roccat_claimed)
		roccat_disconnect(arvo->chrdev_minor);
	kमुक्त(arvo);
पूर्ण

अटल पूर्णांक arvo_probe(काष्ठा hid_device *hdev,
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

	retval = arvo_init_specials(hdev);
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

अटल व्योम arvo_हटाओ(काष्ठा hid_device *hdev)
अणु
	arvo_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

अटल व्योम arvo_report_to_chrdev(काष्ठा arvo_device स्थिर *arvo,
		u8 स्थिर *data)
अणु
	काष्ठा arvo_special_report स्थिर *special_report;
	काष्ठा arvo_roccat_report roccat_report;

	special_report = (काष्ठा arvo_special_report स्थिर *)data;

	roccat_report.profile = arvo->actual_profile;
	roccat_report.button = special_report->event &
			ARVO_SPECIAL_REPORT_EVENT_MASK_BUTTON;
	अगर ((special_report->event & ARVO_SPECIAL_REPORT_EVENT_MASK_ACTION) ==
			ARVO_SPECIAL_REPORT_EVENT_ACTION_PRESS)
		roccat_report.action = ARVO_ROCCAT_REPORT_ACTION_PRESS;
	अन्यथा
		roccat_report.action = ARVO_ROCCAT_REPORT_ACTION_RELEASE;

	roccat_report_event(arvo->chrdev_minor,
			(uपूर्णांक8_t स्थिर *)&roccat_report);
पूर्ण

अटल पूर्णांक arvo_raw_event(काष्ठा hid_device *hdev,
		काष्ठा hid_report *report, u8 *data, पूर्णांक size)
अणु
	काष्ठा arvo_device *arvo = hid_get_drvdata(hdev);

	अगर (size != 3)
		वापस 0;

	अगर (arvo && arvo->roccat_claimed)
		arvo_report_to_chrdev(arvo, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id arvo_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_ARVO) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, arvo_devices);

अटल काष्ठा hid_driver arvo_driver = अणु
	.name = "arvo",
	.id_table = arvo_devices,
	.probe = arvo_probe,
	.हटाओ = arvo_हटाओ,
	.raw_event = arvo_raw_event
पूर्ण;

अटल पूर्णांक __init arvo_init(व्योम)
अणु
	पूर्णांक retval;

	arvo_class = class_create(THIS_MODULE, "arvo");
	अगर (IS_ERR(arvo_class))
		वापस PTR_ERR(arvo_class);
	arvo_class->dev_groups = arvo_groups;

	retval = hid_रेजिस्टर_driver(&arvo_driver);
	अगर (retval)
		class_destroy(arvo_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास arvo_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&arvo_driver);
	class_destroy(arvo_class);
पूर्ण

module_init(arvo_init);
module_निकास(arvo_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Arvo driver");
MODULE_LICENSE("GPL v2");
