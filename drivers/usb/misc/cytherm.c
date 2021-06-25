<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* -*- linux-c -*-
 * Cypress USB Thermometer driver 
 * 
 * Copyright (c) 2004 Erik Rigtorp <erkki@linux.nu> <erik@rigtorp.com>
 * 
 * This driver works with Elektor magazine USB Interface as published in 
 * issue #291. It should also work with the original starter kit/demo board
 * from Cypress.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/usb.h>

#घोषणा DRIVER_AUTHOR "Erik Rigtorp"
#घोषणा DRIVER_DESC "Cypress USB Thermometer driver"

#घोषणा USB_SKEL_VENDOR_ID	0x04b4
#घोषणा USB_SKEL_PRODUCT_ID	0x0002

अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु USB_DEVICE(USB_SKEL_VENDOR_ID, USB_SKEL_PRODUCT_ID) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE (usb, id_table);

/* Structure to hold all of our device specअगरic stuff */
काष्ठा usb_cytherm अणु
	काष्ठा usb_device    *udev;	 /* save off the usb device poपूर्णांकer */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface; /* the पूर्णांकerface क्रम this device */
	पूर्णांक brightness;
पूर्ण;


/* Venकरोr requests */
/* They all operate on one byte at a समय */
#घोषणा PING       0x00
#घोषणा READ_ROM   0x01 /* Reads क्रमm ROM, value = address */
#घोषणा READ_RAM   0x02 /* Reads क्रमm RAM, value = address */
#घोषणा WRITE_RAM  0x03 /* Write to RAM, value = address, index = data */
#घोषणा READ_PORT  0x04 /* Reads from port, value = address */
#घोषणा WRITE_PORT 0x05 /* Write to port, value = address, index = data */ 


/* Send a venकरोr command to device */
अटल पूर्णांक venकरोr_command(काष्ठा usb_device *dev, अचिन्हित अक्षर request, 
			  अचिन्हित अक्षर value, अचिन्हित अक्षर index,
			  व्योम *buf, पूर्णांक size)
अणु
	वापस usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			       request, 
			       USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_OTHER,
			       value, 
			       index, buf, size,
			       USB_CTRL_GET_TIMEOUT);
पूर्ण



#घोषणा BRIGHTNESS 0x2c     /* RAM location क्रम brightness value */
#घोषणा BRIGHTNESS_SEM 0x2b /* RAM location क्रम brightness semaphore */

अटल sमाप_प्रकार brightness_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);    
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);     

	वापस प्र_लिखो(buf, "%i", cytherm->brightness);
पूर्ण

अटल sमाप_प्रकार brightness_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);

	अचिन्हित अक्षर *buffer;
	पूर्णांक retval;
   
	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस 0;

	cytherm->brightness = simple_म_से_अदीर्घ(buf, शून्य, 10);
   
	अगर (cytherm->brightness > 0xFF)
		cytherm->brightness = 0xFF;
	अन्यथा अगर (cytherm->brightness < 0)
		cytherm->brightness = 0;
   
	/* Set brightness */
	retval = venकरोr_command(cytherm->udev, WRITE_RAM, BRIGHTNESS, 
				cytherm->brightness, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
	/* Inक्रमm तगC that we have changed the brightness setting */
	retval = venकरोr_command(cytherm->udev, WRITE_RAM, BRIGHTNESS_SEM,
				0x01, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
   
	kमुक्त(buffer);
   
	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(brightness);


#घोषणा TEMP 0x33 /* RAM location क्रम temperature */
#घोषणा SIGN 0x34 /* RAM location क्रम temperature sign */

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);

	पूर्णांक retval;
	अचिन्हित अक्षर *buffer;

	पूर्णांक temp, sign;
   
	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस 0;

	/* पढ़ो temperature */
	retval = venकरोr_command(cytherm->udev, READ_RAM, TEMP, 0, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
	temp = buffer[1];
   
	/* पढ़ो sign */
	retval = venकरोr_command(cytherm->udev, READ_RAM, SIGN, 0, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
	sign = buffer[1];

	kमुक्त(buffer);
   
	वापस प्र_लिखो(buf, "%c%i.%i", sign ? '-' : '+', temp >> 1,
		       5*(temp - ((temp >> 1) << 1)));
पूर्ण
अटल DEVICE_ATTR_RO(temp);


#घोषणा BUTTON 0x7a

अटल sमाप_प्रकार button_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु

	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);

	पूर्णांक retval;
	अचिन्हित अक्षर *buffer;

	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस 0;

	/* check button */
	retval = venकरोr_command(cytherm->udev, READ_RAM, BUTTON, 0, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
   
	retval = buffer[1];

	kमुक्त(buffer);

	अगर (retval)
		वापस प्र_लिखो(buf, "1");
	अन्यथा
		वापस प्र_लिखो(buf, "0");
पूर्ण
अटल DEVICE_ATTR_RO(button);


अटल sमाप_प्रकार port0_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);

	पूर्णांक retval;
	अचिन्हित अक्षर *buffer;

	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस 0;

	retval = venकरोr_command(cytherm->udev, READ_PORT, 0, 0, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);

	retval = buffer[1];

	kमुक्त(buffer);

	वापस प्र_लिखो(buf, "%d", retval);
पूर्ण


अटल sमाप_प्रकार port0_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);

	अचिन्हित अक्षर *buffer;
	पूर्णांक retval;
	पूर्णांक पंचांगp;
   
	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस 0;

	पंचांगp = simple_म_से_अदीर्घ(buf, शून्य, 10);
   
	अगर (पंचांगp > 0xFF)
		पंचांगp = 0xFF;
	अन्यथा अगर (पंचांगp < 0)
		पंचांगp = 0;
   
	retval = venकरोr_command(cytherm->udev, WRITE_PORT, 0,
				पंचांगp, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);

	kमुक्त(buffer);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(port0);

अटल sमाप_प्रकार port1_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);

	पूर्णांक retval;
	अचिन्हित अक्षर *buffer;

	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस 0;

	retval = venकरोr_command(cytherm->udev, READ_PORT, 1, 0, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
   
	retval = buffer[1];

	kमुक्त(buffer);

	वापस प्र_लिखो(buf, "%d", retval);
पूर्ण


अटल sमाप_प्रकार port1_store(काष्ठा device *dev, काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा usb_पूर्णांकerface *पूर्णांकf = to_usb_पूर्णांकerface(dev);
	काष्ठा usb_cytherm *cytherm = usb_get_पूर्णांकfdata(पूर्णांकf);

	अचिन्हित अक्षर *buffer;
	पूर्णांक retval;
	पूर्णांक पंचांगp;
   
	buffer = kदो_स्मृति(8, GFP_KERNEL);
	अगर (!buffer)
		वापस 0;

	पंचांगp = simple_म_से_अदीर्घ(buf, शून्य, 10);
   
	अगर (पंचांगp > 0xFF)
		पंचांगp = 0xFF;
	अन्यथा अगर (पंचांगp < 0)
		पंचांगp = 0;
   
	retval = venकरोr_command(cytherm->udev, WRITE_PORT, 1,
				पंचांगp, buffer, 8);
	अगर (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);

	kमुक्त(buffer);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(port1);

अटल काष्ठा attribute *cytherm_attrs[] = अणु
	&dev_attr_brightness.attr,
	&dev_attr_temp.attr,
	&dev_attr_button.attr,
	&dev_attr_port0.attr,
	&dev_attr_port1.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(cytherm);

अटल पूर्णांक cytherm_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface, 
			 स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_cytherm *dev = शून्य;
	पूर्णांक retval = -ENOMEM;

	dev = kzalloc (माप(काष्ठा usb_cytherm), GFP_KERNEL);
	अगर (!dev)
		जाओ error_mem;

	dev->udev = usb_get_dev(udev);

	usb_set_पूर्णांकfdata (पूर्णांकerface, dev);

	dev->brightness = 0xFF;

	dev_info (&पूर्णांकerface->dev,
		  "Cypress thermometer device now attached\n");
	वापस 0;

error_mem:
	वापस retval;
पूर्ण

अटल व्योम cytherm_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_cytherm *dev;

	dev = usb_get_पूर्णांकfdata (पूर्णांकerface);

	/* first हटाओ the files, then शून्य the poपूर्णांकer */
	usb_set_पूर्णांकfdata (पूर्णांकerface, शून्य);

	usb_put_dev(dev->udev);

	kमुक्त(dev);

	dev_info(&पूर्णांकerface->dev, "Cypress thermometer now disconnected\n");
पूर्ण

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver cytherm_driver = अणु
	.name =		"cytherm",
	.probe =	cytherm_probe,
	.disconnect =	cytherm_disconnect,
	.id_table =	id_table,
	.dev_groups =	cytherm_groups,
पूर्ण;

module_usb_driver(cytherm_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
