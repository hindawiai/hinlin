<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/usb/core/file.c
 *
 * (C) Copyright Linus Torvalds 1999
 * (C) Copyright Johannes Erdfelt 1999-2001
 * (C) Copyright Andreas Gal 1999
 * (C) Copyright Gregory P. Smith 1999
 * (C) Copyright Deti Fliegl 1999 (new USB architecture)
 * (C) Copyright Randy Dunlap 2000
 * (C) Copyright David Brownell 2000-2001 (kernel hotplug, usb_device_id,
 *	more करोcs, etc)
 * (C) Copyright Yggdrasil Computing, Inc. 2000
 *     (usb_device_id matching changes by Adam J. Richter)
 * (C) Copyright Greg Kroah-Harपंचांगan 2002-2003
 *
 * Released under the GPLv2 only.
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/usb.h>

#समावेश "usb.h"

#घोषणा MAX_USB_MINORS	256
अटल स्थिर काष्ठा file_operations *usb_minors[MAX_USB_MINORS];
अटल DECLARE_RWSEM(minor_rwsem);
अटल DEFINE_MUTEX(init_usb_class_mutex);

अटल पूर्णांक usb_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक err = -ENODEV;
	स्थिर काष्ठा file_operations *new_fops;

	करोwn_पढ़ो(&minor_rwsem);
	new_fops = fops_get(usb_minors[iminor(inode)]);

	अगर (!new_fops)
		जाओ करोne;

	replace_fops(file, new_fops);
	/* Curiouser and curiouser... शून्य ->खोलो() as "no device" ? */
	अगर (file->f_op->खोलो)
		err = file->f_op->खोलो(inode, file);
 करोne:
	up_पढ़ो(&minor_rwsem);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा file_operations usb_fops = अणु
	.owner =	THIS_MODULE,
	.खोलो =		usb_खोलो,
	.llseek =	noop_llseek,
पूर्ण;

अटल काष्ठा usb_class अणु
	काष्ठा kref kref;
	काष्ठा class *class;
पूर्ण *usb_class;

अटल अक्षर *usb_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	काष्ठा usb_class_driver *drv;

	drv = dev_get_drvdata(dev);
	अगर (!drv || !drv->devnode)
		वापस शून्य;
	वापस drv->devnode(dev, mode);
पूर्ण

अटल पूर्णांक init_usb_class(व्योम)
अणु
	पूर्णांक result = 0;

	अगर (usb_class != शून्य) अणु
		kref_get(&usb_class->kref);
		जाओ निकास;
	पूर्ण

	usb_class = kदो_स्मृति(माप(*usb_class), GFP_KERNEL);
	अगर (!usb_class) अणु
		result = -ENOMEM;
		जाओ निकास;
	पूर्ण

	kref_init(&usb_class->kref);
	usb_class->class = class_create(THIS_MODULE, "usbmisc");
	अगर (IS_ERR(usb_class->class)) अणु
		result = PTR_ERR(usb_class->class);
		prपूर्णांकk(KERN_ERR "class_create failed for usb devices\n");
		kमुक्त(usb_class);
		usb_class = शून्य;
		जाओ निकास;
	पूर्ण
	usb_class->class->devnode = usb_devnode;

निकास:
	वापस result;
पूर्ण

अटल व्योम release_usb_class(काष्ठा kref *kref)
अणु
	/* Ok, we cheat as we know we only have one usb_class */
	class_destroy(usb_class->class);
	kमुक्त(usb_class);
	usb_class = शून्य;
पूर्ण

अटल व्योम destroy_usb_class(व्योम)
अणु
	mutex_lock(&init_usb_class_mutex);
	kref_put(&usb_class->kref, release_usb_class);
	mutex_unlock(&init_usb_class_mutex);
पूर्ण

पूर्णांक usb_major_init(व्योम)
अणु
	पूर्णांक error;

	error = रेजिस्टर_chrdev(USB_MAJOR, "usb", &usb_fops);
	अगर (error)
		prपूर्णांकk(KERN_ERR "Unable to get major %d for usb devices\n",
		       USB_MAJOR);

	वापस error;
पूर्ण

व्योम usb_major_cleanup(व्योम)
अणु
	unरेजिस्टर_chrdev(USB_MAJOR, "usb");
पूर्ण

/**
 * usb_रेजिस्टर_dev - रेजिस्टर a USB device, and ask क्रम a minor number
 * @पूर्णांकf: poपूर्णांकer to the usb_पूर्णांकerface that is being रेजिस्टरed
 * @class_driver: poपूर्णांकer to the usb_class_driver क्रम this device
 *
 * This should be called by all USB drivers that use the USB major number.
 * If CONFIG_USB_DYNAMIC_MINORS is enabled, the minor number will be
 * dynamically allocated out of the list of available ones.  If it is not
 * enabled, the minor number will be based on the next available मुक्त minor,
 * starting at the class_driver->minor_base.
 *
 * This function also creates a usb class device in the sysfs tree.
 *
 * usb_deरेजिस्टर_dev() must be called when the driver is करोne with
 * the minor numbers given out by this function.
 *
 * Return: -EINVAL अगर something bad happens with trying to रेजिस्टर a
 * device, and 0 on success.
 */
पूर्णांक usb_रेजिस्टर_dev(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
		     काष्ठा usb_class_driver *class_driver)
अणु
	पूर्णांक retval;
	पूर्णांक minor_base = class_driver->minor_base;
	पूर्णांक minor;
	अक्षर name[20];

#अगर_घोषित CONFIG_USB_DYNAMIC_MINORS
	/*
	 * We करोn't care what the device tries to start at, we want to start
	 * at zero to pack the devices पूर्णांकo the smallest available space with
	 * no holes in the minor range.
	 */
	minor_base = 0;
#पूर्ण_अगर

	अगर (class_driver->fops == शून्य)
		वापस -EINVAL;
	अगर (पूर्णांकf->minor >= 0)
		वापस -EADDRINUSE;

	mutex_lock(&init_usb_class_mutex);
	retval = init_usb_class();
	mutex_unlock(&init_usb_class_mutex);

	अगर (retval)
		वापस retval;

	dev_dbg(&पूर्णांकf->dev, "looking for a minor, starting at %d\n", minor_base);

	करोwn_ग_लिखो(&minor_rwsem);
	क्रम (minor = minor_base; minor < MAX_USB_MINORS; ++minor) अणु
		अगर (usb_minors[minor])
			जारी;

		usb_minors[minor] = class_driver->fops;
		पूर्णांकf->minor = minor;
		अवरोध;
	पूर्ण
	अगर (पूर्णांकf->minor < 0) अणु
		up_ग_लिखो(&minor_rwsem);
		वापस -EXFULL;
	पूर्ण

	/* create a usb class device क्रम this usb पूर्णांकerface */
	snम_लिखो(name, माप(name), class_driver->name, minor - minor_base);
	पूर्णांकf->usb_dev = device_create(usb_class->class, &पूर्णांकf->dev,
				      MKDEV(USB_MAJOR, minor), class_driver,
				      "%s", kbasename(name));
	अगर (IS_ERR(पूर्णांकf->usb_dev)) अणु
		usb_minors[minor] = शून्य;
		पूर्णांकf->minor = -1;
		retval = PTR_ERR(पूर्णांकf->usb_dev);
	पूर्ण
	up_ग_लिखो(&minor_rwsem);
	वापस retval;
पूर्ण
EXPORT_SYMBOL_GPL(usb_रेजिस्टर_dev);

/**
 * usb_deरेजिस्टर_dev - deरेजिस्टर a USB device's dynamic minor.
 * @पूर्णांकf: poपूर्णांकer to the usb_पूर्णांकerface that is being deरेजिस्टरed
 * @class_driver: poपूर्णांकer to the usb_class_driver क्रम this device
 *
 * Used in conjunction with usb_रेजिस्टर_dev().  This function is called
 * when the USB driver is finished with the minor numbers gotten from a
 * call to usb_रेजिस्टर_dev() (usually when the device is disconnected
 * from the प्रणाली.)
 *
 * This function also हटाओs the usb class device from the sysfs tree.
 *
 * This should be called by all drivers that use the USB major number.
 */
व्योम usb_deरेजिस्टर_dev(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			काष्ठा usb_class_driver *class_driver)
अणु
	अगर (पूर्णांकf->minor == -1)
		वापस;

	dev_dbg(&पूर्णांकf->dev, "removing %d minor\n", पूर्णांकf->minor);
	device_destroy(usb_class->class, MKDEV(USB_MAJOR, पूर्णांकf->minor));

	करोwn_ग_लिखो(&minor_rwsem);
	usb_minors[पूर्णांकf->minor] = शून्य;
	up_ग_लिखो(&minor_rwsem);

	पूर्णांकf->usb_dev = शून्य;
	पूर्णांकf->minor = -1;
	destroy_usb_class();
पूर्ण
EXPORT_SYMBOL_GPL(usb_deरेजिस्टर_dev);
