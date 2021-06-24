<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Roccat common functions क्रम device specअगरic drivers
 *
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceक्रमge.net>
 */

/*
 */

#समावेश <linux/hid.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश "hid-roccat-common.h"

अटल अंतरभूत uपूर्णांक16_t roccat_common2_feature_report(uपूर्णांक8_t report_id)
अणु
	वापस 0x300 | report_id;
पूर्ण

पूर्णांक roccat_common2_receive(काष्ठा usb_device *usb_dev, uपूर्णांक report_id,
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
			roccat_common2_feature_report(report_id),
			0, buf, size, USB_CTRL_SET_TIMEOUT);

	स_नकल(data, buf, size);
	kमुक्त(buf);
	वापस ((len < 0) ? len : ((len != size) ? -EIO : 0));
पूर्ण
EXPORT_SYMBOL_GPL(roccat_common2_receive);

पूर्णांक roccat_common2_send(काष्ठा usb_device *usb_dev, uपूर्णांक report_id,
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
			roccat_common2_feature_report(report_id),
			0, buf, size, USB_CTRL_SET_TIMEOUT);

	kमुक्त(buf);
	वापस ((len < 0) ? len : ((len != size) ? -EIO : 0));
पूर्ण
EXPORT_SYMBOL_GPL(roccat_common2_send);

क्रमागत roccat_common2_control_states अणु
	ROCCAT_COMMON_CONTROL_STATUS_CRITICAL = 0,
	ROCCAT_COMMON_CONTROL_STATUS_OK = 1,
	ROCCAT_COMMON_CONTROL_STATUS_INVALID = 2,
	ROCCAT_COMMON_CONTROL_STATUS_BUSY = 3,
	ROCCAT_COMMON_CONTROL_STATUS_CRITICAL_NEW = 4,
पूर्ण;

अटल पूर्णांक roccat_common2_receive_control_status(काष्ठा usb_device *usb_dev)
अणु
	पूर्णांक retval;
	काष्ठा roccat_common2_control control;

	करो अणु
		msleep(50);
		retval = roccat_common2_receive(usb_dev,
				ROCCAT_COMMON_COMMAND_CONTROL,
				&control, माप(काष्ठा roccat_common2_control));

		अगर (retval)
			वापस retval;

		चयन (control.value) अणु
		हाल ROCCAT_COMMON_CONTROL_STATUS_OK:
			वापस 0;
		हाल ROCCAT_COMMON_CONTROL_STATUS_BUSY:
			msleep(500);
			जारी;
		हाल ROCCAT_COMMON_CONTROL_STATUS_INVALID:
		हाल ROCCAT_COMMON_CONTROL_STATUS_CRITICAL:
		हाल ROCCAT_COMMON_CONTROL_STATUS_CRITICAL_NEW:
			वापस -EINVAL;
		शेष:
			dev_err(&usb_dev->dev,
					"roccat_common2_receive_control_status: "
					"unknown response value 0x%x\n",
					control.value);
			वापस -EINVAL;
		पूर्ण

	पूर्ण जबतक (1);
पूर्ण

पूर्णांक roccat_common2_send_with_status(काष्ठा usb_device *usb_dev,
		uपूर्णांक command, व्योम स्थिर *buf, uपूर्णांक size)
अणु
	पूर्णांक retval;

	retval = roccat_common2_send(usb_dev, command, buf, size);
	अगर (retval)
		वापस retval;

	msleep(100);

	वापस roccat_common2_receive_control_status(usb_dev);
पूर्ण
EXPORT_SYMBOL_GPL(roccat_common2_send_with_status);

पूर्णांक roccat_common2_device_init_काष्ठा(काष्ठा usb_device *usb_dev,
		काष्ठा roccat_common2_device *dev)
अणु
	mutex_init(&dev->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(roccat_common2_device_init_काष्ठा);

sमाप_प्रकार roccat_common2_sysfs_पढ़ो(काष्ठा file *fp, काष्ठा kobject *kobj,
		अक्षर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा roccat_common2_device *roccat_dev = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off >= real_size)
		वापस 0;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&roccat_dev->lock);
	retval = roccat_common2_receive(usb_dev, command, buf, real_size);
	mutex_unlock(&roccat_dev->lock);

	वापस retval ? retval : real_size;
पूर्ण
EXPORT_SYMBOL_GPL(roccat_common2_sysfs_पढ़ो);

sमाप_प्रकार roccat_common2_sysfs_ग_लिखो(काष्ठा file *fp, काष्ठा kobject *kobj,
		व्योम स्थिर *buf, loff_t off, माप_प्रकार count,
		माप_प्रकार real_size, uपूर्णांक command)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj)->parent->parent;
	काष्ठा roccat_common2_device *roccat_dev = hid_get_drvdata(dev_get_drvdata(dev));
	काष्ठा usb_device *usb_dev = पूर्णांकerface_to_usbdev(to_usb_पूर्णांकerface(dev));
	पूर्णांक retval;

	अगर (off != 0 || count != real_size)
		वापस -EINVAL;

	mutex_lock(&roccat_dev->lock);
	retval = roccat_common2_send_with_status(usb_dev, command, buf, real_size);
	mutex_unlock(&roccat_dev->lock);

	वापस retval ? retval : real_size;
पूर्ण
EXPORT_SYMBOL_GPL(roccat_common2_sysfs_ग_लिखो);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat common driver");
MODULE_LICENSE("GPL v2");
