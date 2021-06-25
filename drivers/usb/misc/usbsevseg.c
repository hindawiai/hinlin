<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB 7 Segment Driver
 *
 * Copyright (C) 2008 Harrison Metzger <harrisonmetz@gmail.com>
 * Based on usbled.c by Greg Kroah-Harपंचांगan (greg@kroah.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb.h>


#घोषणा DRIVER_AUTHOR "Harrison Metzger <harrisonmetz@gmail.com>"
#घोषणा DRIVER_DESC "USB 7 Segment Driver"

#घोषणा VENDOR_ID	0x0fc5
#घोषणा PRODUCT_ID	0x1227
#घोषणा MAXLEN		8

/* table of devices that work with this driver */
अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(VENDOR_ID, PRODUCT_ID) पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* the dअगरferent text display modes the device is capable of */
अटल स्थिर अक्षर *display_texपंचांगodes[] = अणु"raw", "hex", "ascii"पूर्ण;

काष्ठा usb_sevsegdev अणु
	काष्ठा usb_device *udev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकf;

	u8 घातered;
	u8 mode_msb;
	u8 mode_lsb;
	u8 decimals[MAXLEN];
	u8 texपंचांगode;
	u8 text[MAXLEN];
	u16 textlength;

	u8 shaकरोw_घातer; /* क्रम PM */
	u8 has_पूर्णांकerface_pm;
पूर्ण;

/* sysfs_streq can't replace this completely
 * If the device was in hex mode, and the user wanted a 0,
 * अगर str commands are used, we would assume the end of string
 * so mem commands are used.
 */
अटल अंतरभूत माप_प्रकार my_memlen(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (count > 0 && buf[count-1] == '\n')
		वापस count - 1;
	अन्यथा
		वापस count;
पूर्ण

अटल व्योम update_display_घातered(काष्ठा usb_sevsegdev *mydev)
अणु
	पूर्णांक rc;

	अगर (mydev->घातered && !mydev->has_पूर्णांकerface_pm) अणु
		rc = usb_स्वतःpm_get_पूर्णांकerface(mydev->पूर्णांकf);
		अगर (rc < 0)
			वापस;
		mydev->has_पूर्णांकerface_pm = 1;
	पूर्ण

	अगर (mydev->shaकरोw_घातer != 1)
		वापस;

	rc = usb_control_msg_send(mydev->udev, 0, 0x12, 0x48,
				  (80 * 0x100) + 10, /*  (घातer mode) */
				  (0x00 * 0x100) + (mydev->घातered ? 1 : 0),
				  शून्य, 0, 2000, GFP_KERNEL);
	अगर (rc < 0)
		dev_dbg(&mydev->udev->dev, "power retval = %d\n", rc);

	अगर (!mydev->घातered && mydev->has_पूर्णांकerface_pm) अणु
		usb_स्वतःpm_put_पूर्णांकerface(mydev->पूर्णांकf);
		mydev->has_पूर्णांकerface_pm = 0;
	पूर्ण
पूर्ण

अटल व्योम update_display_mode(काष्ठा usb_sevsegdev *mydev)
अणु
	पूर्णांक rc;

	अगर(mydev->shaकरोw_घातer != 1)
		वापस;

	rc = usb_control_msg_send(mydev->udev, 0, 0x12, 0x48,
				  (82 * 0x100) + 10, /* (set mode) */
				  (mydev->mode_msb * 0x100) + mydev->mode_lsb,
				  शून्य, 0, 2000, GFP_NOIO);

	अगर (rc < 0)
		dev_dbg(&mydev->udev->dev, "mode retval = %d\n", rc);
पूर्ण

अटल व्योम update_display_visual(काष्ठा usb_sevsegdev *mydev, gfp_t mf)
अणु
	पूर्णांक rc;
	पूर्णांक i;
	अचिन्हित अक्षर buffer[MAXLEN] = अणु0पूर्ण;
	u8 decimals = 0;

	अगर(mydev->shaकरोw_घातer != 1)
		वापस;

	/* The device is right to left, where as you ग_लिखो left to right */
	क्रम (i = 0; i < mydev->textlength; i++)
		buffer[i] = mydev->text[mydev->textlength-1-i];

	rc = usb_control_msg_send(mydev->udev, 0, 0x12, 0x48,
				  (85 * 0x100) + 10, /* (ग_लिखो text) */
				  (0 * 0x100) + mydev->texपंचांगode, /* mode  */
				  &buffer, mydev->textlength, 2000, mf);

	अगर (rc < 0)
		dev_dbg(&mydev->udev->dev, "write retval = %d\n", rc);

	/* The device is right to left, where as you ग_लिखो left to right */
	क्रम (i = 0; i < माप(mydev->decimals); i++)
		decimals |= mydev->decimals[i] << i;

	rc = usb_control_msg_send(mydev->udev, 0, 0x12, 0x48,
				  (86 * 0x100) + 10, /* (set decimal) */
				  (0 * 0x100) + decimals, /* decimals */
				  शून्य, 0, 2000, mf);

	अगर (rc < 0)
		dev_dbg(&mydev->udev->dev, "decimal retval = %d\n", rc);
पूर्ण

#घोषणा MYDEV_ATTR_SIMPLE_UNSIGNED(name, update_fcn)		\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,			\
	काष्ठा device_attribute *attr, अक्षर *buf) 		\
अणु								\
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);	\
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);	\
								\
	वापस प्र_लिखो(buf, "%u\n", mydev->name);		\
पूर्ण								\
								\
अटल sमाप_प्रकार name##_store(काष्ठा device *dev,			\
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count) \
अणु								\
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);	\
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);	\
								\
	mydev->name = simple_म_से_अदीर्घ(buf, शून्य, 10);		\
	update_fcn(mydev); 					\
								\
	वापस count;						\
पूर्ण								\
अटल DEVICE_ATTR_RW(name);

अटल sमाप_प्रकार text_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);

	वापस snम_लिखो(buf, mydev->textlength, "%s\n", mydev->text);
पूर्ण

अटल sमाप_प्रकार text_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	माप_प्रकार end = my_memlen(buf, count);

	अगर (end > माप(mydev->text))
		वापस -EINVAL;

	स_रखो(mydev->text, 0, माप(mydev->text));
	mydev->textlength = end;

	अगर (end > 0)
		स_नकल(mydev->text, buf, end);

	update_display_visual(mydev, GFP_KERNEL);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(text);

अटल sमाप_प्रकार decimals_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक i;
	पूर्णांक pos;

	क्रम (i = 0; i < माप(mydev->decimals); i++) अणु
		pos = माप(mydev->decimals) - 1 - i;
		अगर (mydev->decimals[i] == 0)
			buf[pos] = '0';
		अन्यथा अगर (mydev->decimals[i] == 1)
			buf[pos] = '1';
		अन्यथा
			buf[pos] = 'x';
	पूर्ण

	buf[माप(mydev->decimals)] = '\n';
	वापस माप(mydev->decimals) + 1;
पूर्ण

अटल sमाप_प्रकार decimals_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	माप_प्रकार end = my_memlen(buf, count);
	पूर्णांक i;

	अगर (end > माप(mydev->decimals))
		वापस -EINVAL;

	क्रम (i = 0; i < end; i++)
		अगर (buf[i] != '0' && buf[i] != '1')
			वापस -EINVAL;

	स_रखो(mydev->decimals, 0, माप(mydev->decimals));
	क्रम (i = 0; i < end; i++)
		अगर (buf[i] == '1')
			mydev->decimals[end-1-i] = 1;

	update_display_visual(mydev, GFP_KERNEL);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(decimals);

अटल sमाप_प्रकार texपंचांगode_show(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक i;

	buf[0] = 0;

	क्रम (i = 0; i < ARRAY_SIZE(display_texपंचांगodes); i++) अणु
		अगर (mydev->texपंचांगode == i) अणु
			म_जोड़ो(buf, " [");
			म_जोड़ो(buf, display_texपंचांगodes[i]);
			म_जोड़ो(buf, "] ");
		पूर्ण अन्यथा अणु
			म_जोड़ो(buf, " ");
			म_जोड़ो(buf, display_texपंचांगodes[i]);
			म_जोड़ो(buf, " ");
		पूर्ण
	पूर्ण
	म_जोड़ो(buf, "\n");


	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार texपंचांगode_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_sevsegdev *mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	पूर्णांक i;

	i = sysfs_match_string(display_texपंचांगodes, buf);
	अगर (i < 0)
		वापस i;

	mydev->texपंचांगode = i;
	update_display_visual(mydev, GFP_KERNEL);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(texपंचांगode);


MYDEV_ATTR_SIMPLE_UNSIGNED(घातered, update_display_घातered);
MYDEV_ATTR_SIMPLE_UNSIGNED(mode_msb, update_display_mode);
MYDEV_ATTR_SIMPLE_UNSIGNED(mode_lsb, update_display_mode);

अटल काष्ठा attribute *sevseg_attrs[] = अणु
	&dev_attr_घातered.attr,
	&dev_attr_text.attr,
	&dev_attr_texपंचांगode.attr,
	&dev_attr_decimals.attr,
	&dev_attr_mode_msb.attr,
	&dev_attr_mode_lsb.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(sevseg);

अटल पूर्णांक sevseg_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
	स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_sevsegdev *mydev = शून्य;
	पूर्णांक rc = -ENOMEM;

	mydev = kzalloc(माप(काष्ठा usb_sevsegdev), GFP_KERNEL);
	अगर (!mydev)
		जाओ error_mem;

	mydev->udev = usb_get_dev(udev);
	mydev->पूर्णांकf = पूर्णांकerface;
	usb_set_पूर्णांकfdata(पूर्णांकerface, mydev);

	/* PM */
	mydev->shaकरोw_घातer = 1; /* currently active */
	mydev->has_पूर्णांकerface_pm = 0; /* have not issued स्वतःpm_get */

	/*set शेषs */
	mydev->texपंचांगode = 0x02; /* ascii mode */
	mydev->mode_msb = 0x06; /* 6 अक्षरacters */
	mydev->mode_lsb = 0x3f; /* scanmode क्रम 6 अक्षरs */

	dev_info(&पूर्णांकerface->dev, "USB 7 Segment device now attached\n");
	वापस 0;

error_mem:
	वापस rc;
पूर्ण

अटल व्योम sevseg_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_sevsegdev *mydev;

	mydev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	usb_set_पूर्णांकfdata(पूर्णांकerface, शून्य);
	usb_put_dev(mydev->udev);
	kमुक्त(mydev);
	dev_info(&पूर्णांकerface->dev, "USB 7 Segment now disconnected\n");
पूर्ण

अटल पूर्णांक sevseg_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	काष्ठा usb_sevsegdev *mydev;

	mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	mydev->shaकरोw_घातer = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sevseg_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_sevsegdev *mydev;

	mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	mydev->shaकरोw_घातer = 1;
	update_display_mode(mydev);
	update_display_visual(mydev, GFP_NOIO);

	वापस 0;
पूर्ण

अटल पूर्णांक sevseg_reset_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा usb_sevsegdev *mydev;

	mydev = usb_get_पूर्णांकfdata(पूर्णांकf);
	mydev->shaकरोw_घातer = 1;
	update_display_mode(mydev);
	update_display_visual(mydev, GFP_NOIO);

	वापस 0;
पूर्ण

अटल काष्ठा usb_driver sevseg_driver = अणु
	.name =		"usbsevseg",
	.probe =	sevseg_probe,
	.disconnect =	sevseg_disconnect,
	.suspend =	sevseg_suspend,
	.resume =	sevseg_resume,
	.reset_resume =	sevseg_reset_resume,
	.id_table =	id_table,
	.dev_groups =	sevseg_groups,
	.supports_स्वतःsuspend = 1,
पूर्ण;

module_usb_driver(sevseg_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
