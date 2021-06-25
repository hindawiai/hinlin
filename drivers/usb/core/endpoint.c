<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/core/endpoपूर्णांक.c
 *
 * (C) Copyright 2002,2004,2006 Greg Kroah-Harपंचांगan
 * (C) Copyright 2002,2004 IBM Corp.
 * (C) Copyright 2006 Novell Inc.
 *
 * Released under the GPLv2 only.
 *
 * Endpoपूर्णांक sysfs stuff
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश "usb.h"

काष्ठा ep_device अणु
	काष्ठा usb_endpoपूर्णांक_descriptor *desc;
	काष्ठा usb_device *udev;
	काष्ठा device dev;
पूर्ण;
#घोषणा to_ep_device(_dev) \
	container_of(_dev, काष्ठा ep_device, dev)

काष्ठा ep_attribute अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा usb_device *,
			काष्ठा usb_endpoपूर्णांक_descriptor *, अक्षर *);
पूर्ण;
#घोषणा to_ep_attribute(_attr) \
	container_of(_attr, काष्ठा ep_attribute, attr)

#घोषणा usb_ep_attr(field, क्रमmat_string)			\
अटल sमाप_प्रकार field##_show(काष्ठा device *dev,			\
			       काष्ठा device_attribute *attr,	\
			       अक्षर *buf)			\
अणु								\
	काष्ठा ep_device *ep = to_ep_device(dev);		\
	वापस प्र_लिखो(buf, क्रमmat_string, ep->desc->field);	\
पूर्ण								\
अटल DEVICE_ATTR_RO(field)

usb_ep_attr(bLength, "%02x\n");
usb_ep_attr(bEndpoपूर्णांकAddress, "%02x\n");
usb_ep_attr(bmAttributes, "%02x\n");
usb_ep_attr(bInterval, "%02x\n");

अटल sमाप_प्रकार wMaxPacketSize_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ep_device *ep = to_ep_device(dev);
	वापस प्र_लिखो(buf, "%04x\n", usb_endpoपूर्णांक_maxp(ep->desc));
पूर्ण
अटल DEVICE_ATTR_RO(wMaxPacketSize);

अटल sमाप_प्रकार type_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा ep_device *ep = to_ep_device(dev);
	अक्षर *type = "unknown";

	चयन (usb_endpoपूर्णांक_type(ep->desc)) अणु
	हाल USB_ENDPOINT_XFER_CONTROL:
		type = "Control";
		अवरोध;
	हाल USB_ENDPOINT_XFER_ISOC:
		type = "Isoc";
		अवरोध;
	हाल USB_ENDPOINT_XFER_BULK:
		type = "Bulk";
		अवरोध;
	हाल USB_ENDPOINT_XFER_INT:
		type = "Interrupt";
		अवरोध;
	पूर्ण
	वापस प्र_लिखो(buf, "%s\n", type);
पूर्ण
अटल DEVICE_ATTR_RO(type);

अटल sमाप_प्रकार पूर्णांकerval_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा ep_device *ep = to_ep_device(dev);
	अचिन्हित पूर्णांक पूर्णांकerval;
	अक्षर unit;

	पूर्णांकerval = usb_decode_पूर्णांकerval(ep->desc, ep->udev->speed);
	अगर (पूर्णांकerval % 1000) अणु
		unit = 'u';
	पूर्ण अन्यथा अणु
		unit = 'm';
		पूर्णांकerval /= 1000;
	पूर्ण

	वापस प्र_लिखो(buf, "%d%cs\n", पूर्णांकerval, unit);
पूर्ण
अटल DEVICE_ATTR_RO(पूर्णांकerval);

अटल sमाप_प्रकार direction_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा ep_device *ep = to_ep_device(dev);
	अक्षर *direction;

	अगर (usb_endpoपूर्णांक_xfer_control(ep->desc))
		direction = "both";
	अन्यथा अगर (usb_endpoपूर्णांक_dir_in(ep->desc))
		direction = "in";
	अन्यथा
		direction = "out";
	वापस प्र_लिखो(buf, "%s\n", direction);
पूर्ण
अटल DEVICE_ATTR_RO(direction);

अटल काष्ठा attribute *ep_dev_attrs[] = अणु
	&dev_attr_bLength.attr,
	&dev_attr_bEndpoपूर्णांकAddress.attr,
	&dev_attr_bmAttributes.attr,
	&dev_attr_bInterval.attr,
	&dev_attr_wMaxPacketSize.attr,
	&dev_attr_पूर्णांकerval.attr,
	&dev_attr_type.attr,
	&dev_attr_direction.attr,
	शून्य,
पूर्ण;
अटल स्थिर काष्ठा attribute_group ep_dev_attr_grp = अणु
	.attrs = ep_dev_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *ep_dev_groups[] = अणु
	&ep_dev_attr_grp,
	शून्य
पूर्ण;

अटल व्योम ep_device_release(काष्ठा device *dev)
अणु
	काष्ठा ep_device *ep_dev = to_ep_device(dev);

	kमुक्त(ep_dev);
पूर्ण

काष्ठा device_type usb_ep_device_type = अणु
	.name =		"usb_endpoint",
	.release = ep_device_release,
पूर्ण;

पूर्णांक usb_create_ep_devs(काष्ठा device *parent,
			काष्ठा usb_host_endpoपूर्णांक *endpoपूर्णांक,
			काष्ठा usb_device *udev)
अणु
	काष्ठा ep_device *ep_dev;
	पूर्णांक retval;

	ep_dev = kzalloc(माप(*ep_dev), GFP_KERNEL);
	अगर (!ep_dev) अणु
		retval = -ENOMEM;
		जाओ निकास;
	पूर्ण

	ep_dev->desc = &endpoपूर्णांक->desc;
	ep_dev->udev = udev;
	ep_dev->dev.groups = ep_dev_groups;
	ep_dev->dev.type = &usb_ep_device_type;
	ep_dev->dev.parent = parent;
	dev_set_name(&ep_dev->dev, "ep_%02x", endpoपूर्णांक->desc.bEndpoपूर्णांकAddress);

	retval = device_रेजिस्टर(&ep_dev->dev);
	अगर (retval)
		जाओ error_रेजिस्टर;

	device_enable_async_suspend(&ep_dev->dev);
	endpoपूर्णांक->ep_dev = ep_dev;
	वापस retval;

error_रेजिस्टर:
	put_device(&ep_dev->dev);
निकास:
	वापस retval;
पूर्ण

व्योम usb_हटाओ_ep_devs(काष्ठा usb_host_endpoपूर्णांक *endpoपूर्णांक)
अणु
	काष्ठा ep_device *ep_dev = endpoपूर्णांक->ep_dev;

	अगर (ep_dev) अणु
		device_unरेजिस्टर(&ep_dev->dev);
		endpoपूर्णांक->ep_dev = शून्य;
	पूर्ण
पूर्ण
