<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat Kone driver क्रम Linux
 *
 * Copyright (c) 2010 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

/*
 * Roccat Kone is a gamer mouse which consists of a mouse part and a keyboard
 * part. The keyboard part enables the mouse to execute stored macros with mixed
 * key- and button-events.
 *
 * TODO implement on-the-fly polling-rate change
 *      The winकरोws driver has the ability to change the polling rate of the
 *      device on the press of a mousebutton.
 *      Is it possible to हटाओ and reinstall the urb in raw-event- or any
 *      other handler, or to defer this action to be executed somewhere अन्यथा?
 *
 * TODO is it possible to overग_लिखो group क्रम sysfs attributes via udev?
 */

#समावेश <linux/device.h>
#समावेश <linux/input.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid-roccat.h>
#समावेश "hid-ids.h"
#समावेश "hid-roccat-common.h"
#समावेश "hid-roccat-kone.h"

अटल uपूर्णांक profile_numbers[5] = अणु0, 1, 2, 3, 4पूर्ण;

अटल व्योम kone_profile_activated(काष्ठा kone_device *kone, uपूर्णांक new_profile)
अणु
	kone->actual_profile = new_profile;
	kone->actual_dpi = kone->profiles[new_profile - 1].startup_dpi;
पूर्ण

अटल व्योम kone_profile_report(काष्ठा kone_device *kone, uपूर्णांक new_profile)
अणु
	काष्ठा kone_roccat_report roccat_report;

	roccat_report.event = kone_mouse_event_चयन_profile;
	roccat_report.value = new_profile;
	roccat_report.key = 0;
	roccat_report_event(kone->chrdev_minor, (uपूर्णांक8_t *)&roccat_report);
पूर्ण

अटल पूर्णांक kone_receive(काष्ठा usb_device *usb_dev, uपूर्णांक usb_command,
		व्योम *data, uपूर्णांक size)
अणु
	अक्षर *buf;
	पूर्णांक len;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	len = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			HID_REQ_GET_REPORT,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
			usb_command, 0, buf, size, USB_CTRL_SET_TIMEOUT);

	स_नकल(data, buf, size);
	kमुक्त(buf);
	वापस ((len < 0) ? len : ((len != size) ? -EIO : 0));
पूर्ण

अटल पूर्णांक kone_send(काष्ठा usb_device *usb_dev, uपूर्णांक usb_command,
		व्योम स्थिर *data, uपूर्णांक size)
अणु
	अक्षर *buf;
	पूर्णांक len;

	buf = kmemdup(data, size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;

	len = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			HID_REQ_SET_REPORT,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
			usb_command, 0, buf, size, USB_CTRL_SET_TIMEOUT);

	kमुक्त(buf);
	वापस ((len < 0) ? len : ((len != size) ? -EIO : 0));
पूर्ण

/* kone_class is used क्रम creating sysfs attributes via roccat अक्षर device */
अटल काष्ठा class *kone_class;

अटल व्योम kone_set_settings_checksum(काष्ठा kone_settings *settings)
अणु
	uपूर्णांक16_t checksum = 0;
	अचिन्हित अक्षर *address = (अचिन्हित अक्षर *)settings;
	पूर्णांक i;

	क्रम (i = 0; i < माप(काष्ठा kone_settings) - 2; ++i, ++address)
		checksum += *address;
	settings->checksum = cpu_to_le16(checksum);
पूर्ण

/*
 * Checks success after writing data to mouse
 * On success वापसs 0
 * On failure वापसs त्रुटि_सं
 */
अटल पूर्णांक kone_check_ग_लिखो(काष्ठा usb_device *usb_dev)
अणु
	पूर्णांक retval;
	uपूर्णांक8_t data;

	करो अणु
		/*
		 * Mouse needs 50 msecs until it says ok, but there are
		 * 30 more msecs needed क्रम next ग_लिखो to work.
		 */
		msleep(80);

		retval = kone_receive(usb_dev,
				kone_command_confirm_ग_लिखो, &data, 1);
		अगर (retval)
			वापस retval;

		/*
		 * value of 3 seems to mean something like
		 * "not finished yet, but it looks good"
		 * So check again after a moment.
		 */
	पूर्ण जबतक (data == 3);

	अगर (data == 1) /* everything alright */
		वापस 0;

	/* unknown answer */
	dev_err(&usb_dev->dev, "got retval %d when checking write\n", data);
	वापस -EIO;
पूर्ण

/*
 * Reads settings from mouse and stores it in @buf
 * On success वापसs 0
 * On failure वापसs त्रुटि_सं
 */
अटल पूर्णांक kone_get_settings(काष्ठा usb_device *usb_dev,
		काष्ठा kone_settings *buf)
अणु
	वापस kone_receive(usb_dev, kone_command_settings, buf,
			माप(काष्ठा kone_settings));
पूर्ण

/*
 * Writes settings from @buf to mouse
 * On success वापसs 0
 * On failure वापसs त्रुटि_सं
 */
अटल पूर्णांक kone_set_settings(काष्ठा usb_device *usb_dev,
		काष्ठा kone_settings स्थिर *settings)
अणु
	पूर्णांक retval;

	retval = kone_send(usb_dev, kone_command_settings,
			settings, माप(काष्ठा kone_settings));
	अगर (retval)
		वापस retval;
	वापस kone_check_ग_लिखो(usb_dev);
पूर्ण

/*
 * Reads profile data from mouse and stores it in @buf
 * @number: profile number to पढ़ो
 * On success वापसs 0
 * On failure वापसs त्रुटि_सं
 */
अटल पूर्णांक kone_get_profile(काष्ठा usb_device *usb_dev,
		काष्ठा kone_profile *buf, पूर्णांक number)
अणु
	पूर्णांक len;

	अगर (number < 1 || number > 5)
		वापस -EINVAL;

	len = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
			USB_REQ_CLEAR_FEATURE,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_IN,
			kone_command_profile, number, buf,
			माप(काष्ठा kone_profile), USB_CTRL_SET_TIMEOUT);

	अगर (len != माप(काष्ठा kone_profile))
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Writes profile data to mouse.
 * @number: profile number to ग_लिखो
 * On success वापसs 0
 * On failure वापसs त्रुटि_सं
 */
अटल पूर्णांक kone_set_profile(काष्ठा usb_device *usb_dev,
		काष्ठा kone_profile स्थिर *profile, पूर्णांक number)
अणु
	पूर्णांक len;

	अगर (number < 1 || number > 5)
		वापस -EINVAL;

	len = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			USB_REQ_SET_CONFIGURATION,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_सूची_OUT,
			kone_command_profile, number, (व्योम *)profile,
			माप(काष्ठा kone_profile),
			USB_CTRL_SET_TIMEOUT);

	अगर (len != माप(काष्ठा kone_profile))
		वापस len;

	अगर (kone_check_ग_लिखो(usb_dev))
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Reads value of "fast-clip-weight" and stores it in @result
 * On success वापसs 0
 * On failure वापसs त्रुटि_सं
 */
अटल पूर्णांक kone_get_weight(काष्ठा usb_device *usb_dev, पूर्णांक *result)
अणु
	पूर्णांक retval;
	uपूर्णांक8_t data;

	retval = kone_receive(usb_dev, kone_command_weight, &data, 1);

	अगर (retval)
		वापस retval;

	*result = (पूर्णांक)data;
	वापस 0;
पूर्ण

/*
 * Reads firmware_version of mouse and stores it in @result
 * On success वापसs 0
 * On failure वापसs त्रुटि_सं
 */
अटल पूर्णांक kone_get_firmware_version(काष्ठा usb_device *usb_dev, पूर्णांक *result)
अणु
	पूर्णांक retval;
	uपूर्णांक16_t data;

	retval = kone_receive(usb_dev, kone_command_firmware_version,
			&data, 2);
	अगर (retval)
		वापस retval;

	*result = le16_to_cpu(data);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार kone_sysfs_पढ़ो_settings(काष्ठा file *fp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count) अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा kone_device *kone = hid_get_drvdata(dev_get_drvdata(dev));

	अगर (off >= माप(काष्ठा kone_settings))
		वापस 0;

	अगर (off + count > माप(काष्ठा kone_settings))
		count = माप(काष्ठा kone_settings) - off;

	mutex_lock(&kone->kone_lock);
	स_नकल(buf, ((अक्षर स्थिर *)&kone->settings) + off, count);
	mutex_unlock(&kone->kone_lock);

	वापस count;
पूर्ण

/*
 * Writing settings स्वतःmatically activates startup_profile.
 * This function keeps values in kone_device up to date and assumes that in
 * हाल of error the old data is still valid
 */
अटल sमाप_प्रकार kone_sysfs_ग_लिखो_settings(काष्ठा file *fp, काष्ठा kobject *kobj,
		काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count) अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा kone_device *kone = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval = 0, dअगरference, old_profile;
	काष्ठा kone_settings *settings = (काष्ठा kone_settings *)buf;

	/* I need to get my data in one piece */
	अगर (off != 0 || count != माप(काष्ठा kone_settings))
		वापस -EINVAL;

	mutex_lock(&kone->kone_lock);
	dअगरference = स_भेद(settings, &kone->settings,
			    माप(काष्ठा kone_settings));
	अगर (dअगरference) अणु
		अगर (settings->startup_profile < 1 ||
		    settings->startup_profile > 5) अणु
			retval = -EINVAL;
			जाओ unlock;
		पूर्ण

		retval = kone_set_settings(usb_dev, settings);
		अगर (retval)
			जाओ unlock;

		old_profile = kone->settings.startup_profile;
		स_नकल(&kone->settings, settings, माप(काष्ठा kone_settings));

		kone_profile_activated(kone, kone->settings.startup_profile);

		अगर (kone->settings.startup_profile != old_profile)
			kone_profile_report(kone, kone->settings.startup_profile);
	पूर्ण
unlock:
	mutex_unlock(&kone->kone_lock);

	अगर (retval)
		वापस retval;

	वापस माप(काष्ठा kone_settings);
पूर्ण
अटल BIN_ATTR(settings, 0660, kone_sysfs_पढ़ो_settings,
		kone_sysfs_ग_लिखो_settings, माप(काष्ठा kone_settings));

अटल sमाप_प्रकार kone_sysfs_पढ़ो_profilex(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t off, माप_प्रकार count) अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा kone_device *kone = hid_get_drvdata(dev_get_drvdata(dev));

	अगर (off >= माप(काष्ठा kone_profile))
		वापस 0;

	अगर (off + count > माप(काष्ठा kone_profile))
		count = माप(काष्ठा kone_profile) - off;

	mutex_lock(&kone->kone_lock);
	स_नकल(buf, ((अक्षर स्थिर *)&kone->profiles[*(uपूर्णांक *)(attr->निजी)]) + off, count);
	mutex_unlock(&kone->kone_lock);

	वापस count;
पूर्ण

/* Writes data only अगर dअगरferent to stored data */
अटल sमाप_प्रकार kone_sysfs_ग_लिखो_profilex(काष्ठा file *fp,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t off, माप_प्रकार count) अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा kone_device *kone = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	काष्ठा kone_profile *profile;
	पूर्णांक retval = 0, dअगरference;

	/* I need to get my data in one piece */
	अगर (off != 0 || count != माप(काष्ठा kone_profile))
		वापस -EINVAL;

	profile = &kone->profiles[*(uपूर्णांक *)(attr->निजी)];

	mutex_lock(&kone->kone_lock);
	dअगरference = स_भेद(buf, profile, माप(काष्ठा kone_profile));
	अगर (dअगरference) अणु
		retval = kone_set_profile(usb_dev,
				(काष्ठा kone_profile स्थिर *)buf,
				*(uपूर्णांक *)(attr->निजी) + 1);
		अगर (!retval)
			स_नकल(profile, buf, माप(काष्ठा kone_profile));
	पूर्ण
	mutex_unlock(&kone->kone_lock);

	अगर (retval)
		वापस retval;

	वापस माप(काष्ठा kone_profile);
पूर्ण
#घोषणा PROखाता_ATTR(number)					\
अटल काष्ठा bin_attribute bin_attr_profile##number = अणु	\
	.attr = अणु .name = "profile" #number, .mode = 0660 पूर्ण,	\
	.size = माप(काष्ठा kone_profile),			\
	.पढ़ो = kone_sysfs_पढ़ो_profilex,			\
	.ग_लिखो = kone_sysfs_ग_लिखो_profilex,			\
	.निजी = &profile_numbers[number-1],			\
पूर्ण
PROखाता_ATTR(1);
PROखाता_ATTR(2);
PROखाता_ATTR(3);
PROखाता_ATTR(4);
PROखाता_ATTR(5);

अटल sमाप_प्रकार kone_sysfs_show_actual_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kone_device *kone =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kone->actual_profile);
पूर्ण
अटल DEVICE_ATTR(actual_profile, 0440, kone_sysfs_show_actual_profile, शून्य);

अटल sमाप_प्रकार kone_sysfs_show_actual_dpi(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kone_device *kone =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kone->actual_dpi);
पूर्ण
अटल DEVICE_ATTR(actual_dpi, 0440, kone_sysfs_show_actual_dpi, शून्य);

/* weight is पढ़ो each समय, since we करोn't get informed when it's changed */
अटल sमाप_प्रकार kone_sysfs_show_weight(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kone_device *kone;
	काष्ठा usb_device *usb_dev;
	पूर्णांक weight = 0;
	पूर्णांक retval;

	dev = dev->parent->parent;
	kone = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));

	mutex_lock(&kone->kone_lock);
	retval = kone_get_weight(usb_dev, &weight);
	mutex_unlock(&kone->kone_lock);

	अगर (retval)
		वापस retval;
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", weight);
पूर्ण
अटल DEVICE_ATTR(weight, 0440, kone_sysfs_show_weight, शून्य);

अटल sमाप_प्रकार kone_sysfs_show_firmware_version(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kone_device *kone =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kone->firmware_version);
पूर्ण
अटल DEVICE_ATTR(firmware_version, 0440, kone_sysfs_show_firmware_version,
		   शून्य);

अटल sमाप_प्रकार kone_sysfs_show_tcu(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kone_device *kone =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kone->settings.tcu);
पूर्ण

अटल पूर्णांक kone_tcu_command(काष्ठा usb_device *usb_dev, पूर्णांक number)
अणु
	अचिन्हित अक्षर value;

	value = number;
	वापस kone_send(usb_dev, kone_command_calibrate, &value, 1);
पूर्ण

/*
 * Calibrating the tcu is the only action that changes settings data inside the
 * mouse, so this data needs to be reपढ़ो
 */
अटल sमाप_प्रकार kone_sysfs_set_tcu(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर स्थिर *buf, माप_प्रकार size)
अणु
	काष्ठा kone_device *kone;
	काष्ठा usb_device *usb_dev;
	पूर्णांक retval;
	अचिन्हित दीर्घ state;

	dev = dev->parent->parent;
	kone = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));

	retval = kम_से_अदीर्घ(buf, 10, &state);
	अगर (retval)
		वापस retval;

	अगर (state != 0 && state != 1)
		वापस -EINVAL;

	mutex_lock(&kone->kone_lock);

	अगर (state == 1) अणु /* state activate */
		retval = kone_tcu_command(usb_dev, 1);
		अगर (retval)
			जाओ निकास_unlock;
		retval = kone_tcu_command(usb_dev, 2);
		अगर (retval)
			जाओ निकास_unlock;
		ssleep(5); /* tcu needs this समय क्रम calibration */
		retval = kone_tcu_command(usb_dev, 3);
		अगर (retval)
			जाओ निकास_unlock;
		retval = kone_tcu_command(usb_dev, 0);
		अगर (retval)
			जाओ निकास_unlock;
		retval = kone_tcu_command(usb_dev, 4);
		अगर (retval)
			जाओ निकास_unlock;
		/*
		 * Kone needs this समय to settle things.
		 * Reading settings too early will result in invalid data.
		 * Roccat's driver रुकोs 1 sec, maybe this समय could be
		 * लघुened.
		 */
		ssleep(1);
	पूर्ण

	/* calibration changes values in settings, so reपढ़ो */
	retval = kone_get_settings(usb_dev, &kone->settings);
	अगर (retval)
		जाओ निकास_no_settings;

	/* only ग_लिखो settings back अगर activation state is dअगरferent */
	अगर (kone->settings.tcu != state) अणु
		kone->settings.tcu = state;
		kone_set_settings_checksum(&kone->settings);

		retval = kone_set_settings(usb_dev, &kone->settings);
		अगर (retval) अणु
			dev_err(&usb_dev->dev, "couldn't set tcu state\n");
			/*
			 * try to reपढ़ो valid settings पूर्णांकo buffer overwriting
			 * first error code
			 */
			retval = kone_get_settings(usb_dev, &kone->settings);
			अगर (retval)
				जाओ निकास_no_settings;
			जाओ निकास_unlock;
		पूर्ण
		/* calibration resets profile */
		kone_profile_activated(kone, kone->settings.startup_profile);
	पूर्ण

	retval = size;
निकास_no_settings:
	dev_err(&usb_dev->dev, "couldn't read settings\n");
निकास_unlock:
	mutex_unlock(&kone->kone_lock);
	वापस retval;
पूर्ण
अटल DEVICE_ATTR(tcu, 0660, kone_sysfs_show_tcu, kone_sysfs_set_tcu);

अटल sमाप_प्रकार kone_sysfs_show_startup_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा kone_device *kone =
			hid_get_drvdata(dev_get_drvdata(dev->parent->parent));
	वापस snम_लिखो(buf, PAGE_SIZE, "%d\n", kone->settings.startup_profile);
पूर्ण

अटल sमाप_प्रकार kone_sysfs_set_startup_profile(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर स्थिर *buf, माप_प्रकार size)
अणु
	काष्ठा kone_device *kone;
	काष्ठा usb_device *usb_dev;
	पूर्णांक retval;
	अचिन्हित दीर्घ new_startup_profile;

	dev = dev->parent->parent;
	kone = hid_get_drvdata(dev_get_drvdata(dev));
	usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));

	retval = kम_से_अदीर्घ(buf, 10, &new_startup_profile);
	अगर (retval)
		वापस retval;

	अगर (new_startup_profile  < 1 || new_startup_profile > 5)
		वापस -EINVAL;

	mutex_lock(&kone->kone_lock);

	kone->settings.startup_profile = new_startup_profile;
	kone_set_settings_checksum(&kone->settings);

	retval = kone_set_settings(usb_dev, &kone->settings);
	अगर (retval) अणु
		mutex_unlock(&kone->kone_lock);
		वापस retval;
	पूर्ण

	/* changing the startup profile immediately activates this profile */
	kone_profile_activated(kone, new_startup_profile);
	kone_profile_report(kone, new_startup_profile);

	mutex_unlock(&kone->kone_lock);
	वापस size;
पूर्ण
अटल DEVICE_ATTR(startup_profile, 0660, kone_sysfs_show_startup_profile,
		   kone_sysfs_set_startup_profile);

अटल काष्ठा attribute *kone_attrs[] = अणु
	/*
	 * Read actual dpi settings.
	 * Returns raw value क्रम further processing. Refer to क्रमागत
	 * kone_polling_rates to get real value.
	 */
	&dev_attr_actual_dpi.attr,
	&dev_attr_actual_profile.attr,

	/*
	 * The mouse can be equipped with one of four supplied weights from 5
	 * to 20 grams which are recognized and its value can be पढ़ो out.
	 * This वापसs the raw value reported by the mouse क्रम easy evaluation
	 * by software. Refer to क्रमागत kone_weights to get corresponding real
	 * weight.
	 */
	&dev_attr_weight.attr,

	/*
	 * Prपूर्णांकs firmware version stored in mouse as पूर्णांकeger.
	 * The raw value reported by the mouse is वापसed क्रम easy evaluation,
	 * to get the real version number the decimal poपूर्णांक has to be shअगरted 2
	 * positions to the left. E.g. a value of 138 means 1.38.
	 */
	&dev_attr_firmware_version.attr,

	/*
	 * Prपूर्णांकs state of Tracking Control Unit as number where 0 = off and
	 * 1 = on. Writing 0 deactivates tcu and writing 1 calibrates and
	 * activates the tcu
	 */
	&dev_attr_tcu.attr,

	/* Prपूर्णांकs and takes the number of the profile the mouse starts with */
	&dev_attr_startup_profile.attr,
	शून्य,
पूर्ण;

अटल काष्ठा bin_attribute *kone_bin_attributes[] = अणु
	&bin_attr_settings,
	&bin_attr_profile1,
	&bin_attr_profile2,
	&bin_attr_profile3,
	&bin_attr_profile4,
	&bin_attr_profile5,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group kone_group = अणु
	.attrs = kone_attrs,
	.bin_attrs = kone_bin_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *kone_groups[] = अणु
	&kone_group,
	शून्य,
पूर्ण;

अटल पूर्णांक kone_init_kone_device_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा kone_device *kone)
अणु
	uपूर्णांक i;
	पूर्णांक retval;

	mutex_init(&kone->kone_lock);

	क्रम (i = 0; i < 5; ++i) अणु
		retval = kone_get_profile(usb_dev, &kone->profiles[i], i + 1);
		अगर (retval)
			वापस retval;
	पूर्ण

	retval = kone_get_settings(usb_dev, &kone->settings);
	अगर (retval)
		वापस retval;

	retval = kone_get_firmware_version(usb_dev, &kone->firmware_version);
	अगर (retval)
		वापस retval;

	kone_profile_activated(kone, kone->settings.startup_profile);

	वापस 0;
पूर्ण

/*
 * Since IGNORE_MOUSE quirk moved to hid-apple, there is no way to bind only to
 * mousepart अगर usb_hid is compiled पूर्णांकo the kernel and kone is compiled as
 * module.
 * Secial behaviour is bound only to mousepart since only mouseevents contain
 * additional notअगरications.
 */
अटल पूर्णांक kone_init_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(पूर्णांकf);
	काष्ठा kone_device *kone;
	पूर्णांक retval;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_MOUSE) अणु

		kone = kzalloc(माप(*kone), GFP_KERNEL);
		अगर (!kone)
			वापस -ENOMEM;
		hid_set_drvdata(hdev, kone);

		retval = kone_init_kone_device_काष्ठा(usb_dev, kone);
		अगर (retval) अणु
			hid_err(hdev, "couldn't init struct kone_device\n");
			जाओ निकास_मुक्त;
		पूर्ण

		retval = roccat_connect(kone_class, hdev,
				माप(काष्ठा kone_roccat_report));
		अगर (retval < 0) अणु
			hid_err(hdev, "couldn't init char dev\n");
			/* be tolerant about not getting chrdev */
		पूर्ण अन्यथा अणु
			kone->roccat_claimed = 1;
			kone->chrdev_minor = retval;
		पूर्ण
	पूर्ण अन्यथा अणु
		hid_set_drvdata(hdev, शून्य);
	पूर्ण

	वापस 0;
निकास_मुक्त:
	kमुक्त(kone);
	वापस retval;
पूर्ण

अटल व्योम kone_हटाओ_specials(काष्ठा hid_device *hdev)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(hdev->dev.parent);
	काष्ठा kone_device *kone;

	अगर (पूर्णांकf->cur_altsetting->desc.bInterfaceProtocol
			== USB_INTERFACE_PROTOCOL_MOUSE) अणु
		kone = hid_get_drvdata(hdev);
		अगर (kone->roccat_claimed)
			roccat_disconnect(kone->chrdev_minor);
		kमुक्त(hid_get_drvdata(hdev));
	पूर्ण
पूर्ण

अटल पूर्णांक kone_probe(काष्ठा hid_device *hdev, स्थिर काष्ठा hid_device_id *id)
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

	retval = kone_init_specials(hdev);
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

अटल व्योम kone_हटाओ(काष्ठा hid_device *hdev)
अणु
	kone_हटाओ_specials(hdev);
	hid_hw_stop(hdev);
पूर्ण

/* handle special events and keep actual profile and dpi values up to date */
अटल व्योम kone_keep_values_up_to_date(काष्ठा kone_device *kone,
		काष्ठा kone_mouse_event स्थिर *event)
अणु
	चयन (event->event) अणु
	हाल kone_mouse_event_चयन_profile:
		kone->actual_dpi = kone->profiles[event->value - 1].
				startup_dpi;
		fallthrough;
	हाल kone_mouse_event_osd_profile:
		kone->actual_profile = event->value;
		अवरोध;
	हाल kone_mouse_event_चयन_dpi:
	हाल kone_mouse_event_osd_dpi:
		kone->actual_dpi = event->value;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम kone_report_to_chrdev(काष्ठा kone_device स्थिर *kone,
		काष्ठा kone_mouse_event स्थिर *event)
अणु
	काष्ठा kone_roccat_report roccat_report;

	चयन (event->event) अणु
	हाल kone_mouse_event_चयन_profile:
	हाल kone_mouse_event_चयन_dpi:
	हाल kone_mouse_event_osd_profile:
	हाल kone_mouse_event_osd_dpi:
		roccat_report.event = event->event;
		roccat_report.value = event->value;
		roccat_report.key = 0;
		roccat_report_event(kone->chrdev_minor,
				(uपूर्णांक8_t *)&roccat_report);
		अवरोध;
	हाल kone_mouse_event_call_overदीर्घ_macro:
	हाल kone_mouse_event_mulसमयdia:
		अगर (event->value == kone_keystroke_action_press) अणु
			roccat_report.event = event->event;
			roccat_report.value = kone->actual_profile;
			roccat_report.key = event->macro_key;
			roccat_report_event(kone->chrdev_minor,
					(uपूर्णांक8_t *)&roccat_report);
		पूर्ण
		अवरोध;
	पूर्ण

पूर्ण

/*
 * Is called क्रम keyboard- and mousepart.
 * Only mousepart माला_लो inक्रमmations about special events in its extended event
 * काष्ठाure.
 */
अटल पूर्णांक kone_raw_event(काष्ठा hid_device *hdev, काष्ठा hid_report *report,
		u8 *data, पूर्णांक size)
अणु
	काष्ठा kone_device *kone = hid_get_drvdata(hdev);
	काष्ठा kone_mouse_event *event = (काष्ठा kone_mouse_event *)data;

	/* keyboard events are always processed by शेष handler */
	अगर (size != माप(काष्ठा kone_mouse_event))
		वापस 0;

	अगर (kone == शून्य)
		वापस 0;

	/*
	 * Firmware 1.38 पूर्णांकroduced new behaviour क्रम tilt and special buttons.
	 * Pressed button is reported in each movement event.
	 * Workaround sends only one event per press.
	 */
	अगर (स_भेद(&kone->last_mouse_event.tilt, &event->tilt, 5))
		स_नकल(&kone->last_mouse_event, event,
				माप(काष्ठा kone_mouse_event));
	अन्यथा
		स_रखो(&event->tilt, 0, 5);

	kone_keep_values_up_to_date(kone, event);

	अगर (kone->roccat_claimed)
		kone_report_to_chrdev(kone, event);

	वापस 0; /* always करो further processing */
पूर्ण

अटल स्थिर काष्ठा hid_device_id kone_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_ROCCAT, USB_DEVICE_ID_ROCCAT_KONE) पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(hid, kone_devices);

अटल काष्ठा hid_driver kone_driver = अणु
		.name = "kone",
		.id_table = kone_devices,
		.probe = kone_probe,
		.हटाओ = kone_हटाओ,
		.raw_event = kone_raw_event
पूर्ण;

अटल पूर्णांक __init kone_init(व्योम)
अणु
	पूर्णांक retval;

	/* class name has to be same as driver name */
	kone_class = class_create(THIS_MODULE, "kone");
	अगर (IS_ERR(kone_class))
		वापस PTR_ERR(kone_class);
	kone_class->dev_groups = kone_groups;

	retval = hid_रेजिस्टर_driver(&kone_driver);
	अगर (retval)
		class_destroy(kone_class);
	वापस retval;
पूर्ण

अटल व्योम __निकास kone_निकास(व्योम)
अणु
	hid_unरेजिस्टर_driver(&kone_driver);
	class_destroy(kone_class);
पूर्ण

module_init(kone_init);
module_निकास(kone_निकास);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat Kone driver");
MODULE_LICENSE("GPL v2");
