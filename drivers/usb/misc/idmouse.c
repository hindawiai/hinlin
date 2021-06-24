<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Siemens ID Mouse driver v0.6

  Copyright (C) 2004-5 by Florian 'Floe' Echtler  <echtler@fs.tum.de>
                      and Andreas  'ad'  Deresch <aderesch@fs.tum.de>

  Derived from the USB Skeleton driver 1.1,
  Copyright (C) 2003 Greg Kroah-Harपंचांगan (greg@kroah.com)

  Additional inक्रमmation provided by Martin Reising
  <Martin.Reising@natural-computing.de>

*/

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/usb.h>

/* image स्थिरants */
#घोषणा WIDTH 225
#घोषणा HEIGHT 289
#घोषणा HEADER "P5 225 289 255 "
#घोषणा IMGSIZE ((WIDTH * HEIGHT) + माप(HEADER)-1)

#घोषणा DRIVER_SHORT   "idmouse"
#घोषणा DRIVER_AUTHOR  "Florian 'Floe' Echtler <echtler@fs.tum.de>"
#घोषणा DRIVER_DESC    "Siemens ID Mouse FingerTIP Sensor Driver"

/* minor number क्रम misc USB devices */
#घोषणा USB_IDMOUSE_MINOR_BASE 132

/* venकरोr and device IDs */
#घोषणा ID_SIEMENS 0x0681
#घोषणा ID_IDMOUSE 0x0005
#घोषणा ID_CHERRY  0x0010

/* device ID table */
अटल स्थिर काष्ठा usb_device_id idmouse_table[] = अणु
	अणुUSB_DEVICE(ID_SIEMENS, ID_IDMOUSE)पूर्ण, /* Siemens ID Mouse (Professional) */
	अणुUSB_DEVICE(ID_SIEMENS, ID_CHERRY )पूर्ण, /* Cherry FingerTIP ID Board       */
	अणुपूर्ण                                    /* terminating null entry          */
पूर्ण;

/* sensor commands */
#घोषणा FTIP_RESET   0x20
#घोषणा FTIP_ACQUIRE 0x21
#घोषणा FTIP_RELEASE 0x22
#घोषणा FTIP_BLINK   0x23  /* LSB of value = blink pulse width */
#घोषणा FTIP_SCROLL  0x24

#घोषणा ftip_command(dev, command, value, index) \
	usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0), command, \
	USB_TYPE_VENDOR | USB_RECIP_ENDPOINT | USB_सूची_OUT, value, index, शून्य, 0, 1000)

MODULE_DEVICE_TABLE(usb, idmouse_table);

/* काष्ठाure to hold all of our device specअगरic stuff */
काष्ठा usb_idmouse अणु

	काष्ठा usb_device *udev; /* save off the usb device poपूर्णांकer */
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface; /* the पूर्णांकerface क्रम this device */

	अचिन्हित अक्षर *bulk_in_buffer; /* the buffer to receive data */
	माप_प्रकार bulk_in_size; /* the maximum bulk packet size */
	माप_प्रकार orig_bi_size; /* same as above, but reported by the device */
	__u8 bulk_in_endpoपूर्णांकAddr; /* the address of the bulk in endpoपूर्णांक */

	पूर्णांक खोलो; /* अगर the port is खोलो or not */
	पूर्णांक present; /* अगर the device is not disconnected */
	काष्ठा mutex lock; /* locks this काष्ठाure */

पूर्ण;

/* local function prototypes */
अटल sमाप_प्रकार idmouse_पढ़ो(काष्ठा file *file, अक्षर __user *buffer,
				माप_प्रकार count, loff_t * ppos);

अटल पूर्णांक idmouse_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल पूर्णांक idmouse_release(काष्ठा inode *inode, काष्ठा file *file);

अटल पूर्णांक idmouse_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				स्थिर काष्ठा usb_device_id *id);

अटल व्योम idmouse_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक idmouse_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message);
अटल पूर्णांक idmouse_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf);

/* file operation poपूर्णांकers */
अटल स्थिर काष्ठा file_operations idmouse_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = idmouse_पढ़ो,
	.खोलो = idmouse_खोलो,
	.release = idmouse_release,
	.llseek = शेष_llseek,
पूर्ण;

/* class driver inक्रमmation */
अटल काष्ठा usb_class_driver idmouse_class = अणु
	.name = "idmouse%d",
	.fops = &idmouse_fops,
	.minor_base = USB_IDMOUSE_MINOR_BASE,
पूर्ण;

/* usb specअगरic object needed to रेजिस्टर this driver with the usb subप्रणाली */
अटल काष्ठा usb_driver idmouse_driver = अणु
	.name = DRIVER_SHORT,
	.probe = idmouse_probe,
	.disconnect = idmouse_disconnect,
	.suspend = idmouse_suspend,
	.resume = idmouse_resume,
	.reset_resume = idmouse_resume,
	.id_table = idmouse_table,
	.supports_स्वतःsuspend = 1,
पूर्ण;

अटल पूर्णांक idmouse_create_image(काष्ठा usb_idmouse *dev)
अणु
	पूर्णांक bytes_पढ़ो;
	पूर्णांक bulk_पढ़ो;
	पूर्णांक result;

	स_नकल(dev->bulk_in_buffer, HEADER, माप(HEADER)-1);
	bytes_पढ़ो = माप(HEADER)-1;

	/* reset the device and set a fast blink rate */
	result = ftip_command(dev, FTIP_RELEASE, 0, 0);
	अगर (result < 0)
		जाओ reset;
	result = ftip_command(dev, FTIP_BLINK,   1, 0);
	अगर (result < 0)
		जाओ reset;

	/* initialize the sensor - sending this command twice */
	/* signअगरicantly reduces the rate of failed पढ़ोs     */
	result = ftip_command(dev, FTIP_ACQUIRE, 0, 0);
	अगर (result < 0)
		जाओ reset;
	result = ftip_command(dev, FTIP_ACQUIRE, 0, 0);
	अगर (result < 0)
		जाओ reset;

	/* start the पढ़ोout - sending this command twice */
	/* presumably enables the high dynamic range mode */
	result = ftip_command(dev, FTIP_RESET,   0, 0);
	अगर (result < 0)
		जाओ reset;
	result = ftip_command(dev, FTIP_RESET,   0, 0);
	अगर (result < 0)
		जाओ reset;

	/* loop over a blocking bulk पढ़ो to get data from the device */
	जबतक (bytes_पढ़ो < IMGSIZE) अणु
		result = usb_bulk_msg(dev->udev,
				usb_rcvbulkpipe(dev->udev, dev->bulk_in_endpoपूर्णांकAddr),
				dev->bulk_in_buffer + bytes_पढ़ो,
				dev->bulk_in_size, &bulk_पढ़ो, 5000);
		अगर (result < 0) अणु
			/* Maybe this error was caused by the increased packet size? */
			/* Reset to the original value and tell userspace to retry.  */
			अगर (dev->bulk_in_size != dev->orig_bi_size) अणु
				dev->bulk_in_size = dev->orig_bi_size;
				result = -EAGAIN;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (संकेत_pending(current)) अणु
			result = -EINTR;
			अवरोध;
		पूर्ण
		bytes_पढ़ो += bulk_पढ़ो;
	पूर्ण

	/* reset the device */
reset:
	ftip_command(dev, FTIP_RELEASE, 0, 0);

	/* check क्रम valid image */
	/* right border should be black (0x00) */
	क्रम (bytes_पढ़ो = माप(HEADER)-1 + WIDTH-1; bytes_पढ़ो < IMGSIZE; bytes_पढ़ो += WIDTH)
		अगर (dev->bulk_in_buffer[bytes_पढ़ो] != 0x00)
			वापस -EAGAIN;

	/* lower border should be white (0xFF) */
	क्रम (bytes_पढ़ो = IMGSIZE-WIDTH; bytes_पढ़ो < IMGSIZE-1; bytes_पढ़ो++)
		अगर (dev->bulk_in_buffer[bytes_पढ़ो] != 0xFF)
			वापस -EAGAIN;

	/* should be IMGSIZE == 65040 */
	dev_dbg(&dev->पूर्णांकerface->dev, "read %d bytes fingerprint data\n",
		bytes_पढ़ो);
	वापस result;
पूर्ण

/* PM operations are nops as this driver करोes IO only during खोलो() */
अटल पूर्णांक idmouse_suspend(काष्ठा usb_पूर्णांकerface *पूर्णांकf, pm_message_t message)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक idmouse_resume(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम idmouse_delete(काष्ठा usb_idmouse *dev)
अणु
	kमुक्त(dev->bulk_in_buffer);
	kमुक्त(dev);
पूर्ण

अटल पूर्णांक idmouse_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_idmouse *dev;
	काष्ठा usb_पूर्णांकerface *पूर्णांकerface;
	पूर्णांक result;

	/* get the पूर्णांकerface from minor number and driver inक्रमmation */
	पूर्णांकerface = usb_find_पूर्णांकerface(&idmouse_driver, iminor(inode));
	अगर (!पूर्णांकerface)
		वापस -ENODEV;

	/* get the device inक्रमmation block from the पूर्णांकerface */
	dev = usb_get_पूर्णांकfdata(पूर्णांकerface);
	अगर (!dev)
		वापस -ENODEV;

	/* lock this device */
	mutex_lock(&dev->lock);

	/* check अगर alपढ़ोy खोलो */
	अगर (dev->खोलो) अणु

		/* alपढ़ोy खोलो, so fail */
		result = -EBUSY;

	पूर्ण अन्यथा अणु

		/* create a new image and check क्रम success */
		result = usb_स्वतःpm_get_पूर्णांकerface(पूर्णांकerface);
		अगर (result)
			जाओ error;
		result = idmouse_create_image(dev);
		usb_स्वतःpm_put_पूर्णांकerface(पूर्णांकerface);
		अगर (result)
			जाओ error;

		/* increment our usage count क्रम the driver */
		++dev->खोलो;

		/* save our object in the file's निजी काष्ठाure */
		file->निजी_data = dev;

	पूर्ण 

error:

	/* unlock this device */
	mutex_unlock(&dev->lock);
	वापस result;
पूर्ण

अटल पूर्णांक idmouse_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा usb_idmouse *dev;

	dev = file->निजी_data;

	अगर (dev == शून्य)
		वापस -ENODEV;

	/* lock our device */
	mutex_lock(&dev->lock);

	--dev->खोलो;

	अगर (!dev->present) अणु
		/* the device was unplugged beक्रमe the file was released */
		mutex_unlock(&dev->lock);
		idmouse_delete(dev);
	पूर्ण अन्यथा अणु
		mutex_unlock(&dev->lock);
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार idmouse_पढ़ो(काष्ठा file *file, अक्षर __user *buffer, माप_प्रकार count,
				loff_t * ppos)
अणु
	काष्ठा usb_idmouse *dev = file->निजी_data;
	पूर्णांक result;

	/* lock this object */
	mutex_lock(&dev->lock);

	/* verअगरy that the device wasn't unplugged */
	अगर (!dev->present) अणु
		mutex_unlock(&dev->lock);
		वापस -ENODEV;
	पूर्ण

	result = simple_पढ़ो_from_buffer(buffer, count, ppos,
					dev->bulk_in_buffer, IMGSIZE);
	/* unlock the device */
	mutex_unlock(&dev->lock);
	वापस result;
पूर्ण

अटल पूर्णांक idmouse_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकerface,
				स्थिर काष्ठा usb_device_id *id)
अणु
	काष्ठा usb_device *udev = पूर्णांकerface_to_usbdev(पूर्णांकerface);
	काष्ठा usb_idmouse *dev;
	काष्ठा usb_host_पूर्णांकerface *अगरace_desc;
	काष्ठा usb_endpoपूर्णांक_descriptor *endpoपूर्णांक;
	पूर्णांक result;

	/* check अगर we have gotten the data or the hid पूर्णांकerface */
	अगरace_desc = पूर्णांकerface->cur_altsetting;
	अगर (अगरace_desc->desc.bInterfaceClass != 0x0A)
		वापस -ENODEV;

	अगर (अगरace_desc->desc.bNumEndpoपूर्णांकs < 1)
		वापस -ENODEV;

	/* allocate memory क्रम our device state and initialize it */
	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (dev == शून्य)
		वापस -ENOMEM;

	mutex_init(&dev->lock);
	dev->udev = udev;
	dev->पूर्णांकerface = पूर्णांकerface;

	/* set up the endpoपूर्णांक inक्रमmation - use only the first bulk-in endpoपूर्णांक */
	result = usb_find_bulk_in_endpoपूर्णांक(अगरace_desc, &endpoपूर्णांक);
	अगर (result) अणु
		dev_err(&पूर्णांकerface->dev, "Unable to find bulk-in endpoint.\n");
		idmouse_delete(dev);
		वापस result;
	पूर्ण

	dev->orig_bi_size = usb_endpoपूर्णांक_maxp(endpoपूर्णांक);
	dev->bulk_in_size = 0x200; /* works _much_ faster */
	dev->bulk_in_endpoपूर्णांकAddr = endpoपूर्णांक->bEndpoपूर्णांकAddress;
	dev->bulk_in_buffer = kदो_स्मृति(IMGSIZE + dev->bulk_in_size, GFP_KERNEL);
	अगर (!dev->bulk_in_buffer) अणु
		idmouse_delete(dev);
		वापस -ENOMEM;
	पूर्ण

	/* allow device पढ़ो, ग_लिखो and ioctl */
	dev->present = 1;

	/* we can रेजिस्टर the device now, as it is पढ़ोy */
	usb_set_पूर्णांकfdata(पूर्णांकerface, dev);
	result = usb_रेजिस्टर_dev(पूर्णांकerface, &idmouse_class);
	अगर (result) अणु
		/* something prevented us from रेजिस्टरing this device */
		dev_err(&पूर्णांकerface->dev, "Unable to allocate minor number.\n");
		idmouse_delete(dev);
		वापस result;
	पूर्ण

	/* be noisy */
	dev_info(&पूर्णांकerface->dev,"%s now attached\n",DRIVER_DESC);

	वापस 0;
पूर्ण

अटल व्योम idmouse_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा usb_idmouse *dev = usb_get_पूर्णांकfdata(पूर्णांकerface);

	/* give back our minor */
	usb_deरेजिस्टर_dev(पूर्णांकerface, &idmouse_class);

	/* lock the device */
	mutex_lock(&dev->lock);

	/* prevent device पढ़ो, ग_लिखो and ioctl */
	dev->present = 0;

	/* अगर the device is खोलोed, idmouse_release will clean this up */
	अगर (!dev->खोलो) अणु
		mutex_unlock(&dev->lock);
		idmouse_delete(dev);
	पूर्ण अन्यथा अणु
		/* unlock */
		mutex_unlock(&dev->lock);
	पूर्ण

	dev_info(&पूर्णांकerface->dev, "disconnected\n");
पूर्ण

module_usb_driver(idmouse_driver);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");

