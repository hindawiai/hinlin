<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  dell-smo8800.c - Dell Latitude ACPI SMO88XX मुक्तfall sensor driver
 *
 *  Copyright (C) 2012 Sonal Santan <sonal.santan@gmail.com>
 *  Copyright (C) 2014 Pali Rohथँr <pali@kernel.org>
 *
 *  This is loosely based on lis3lv02d driver.
 */

#घोषणा DRIVER_NAME "smo8800"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>

काष्ठा smo8800_device अणु
	u32 irq;                     /* acpi device irq */
	atomic_t counter;            /* count after last पढ़ो */
	काष्ठा miscdevice miscdev;   /* क्रम /dev/मुक्तfall */
	अचिन्हित दीर्घ misc_खोलोed;   /* whether the device is खोलो */
	रुको_queue_head_t misc_रुको; /* Wait queue क्रम the misc dev */
	काष्ठा device *dev;          /* acpi device */
पूर्ण;

अटल irqवापस_t smo8800_पूर्णांकerrupt_quick(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा smo8800_device *smo8800 = data;

	atomic_inc(&smo8800->counter);
	wake_up_पूर्णांकerruptible(&smo8800->misc_रुको);
	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t smo8800_पूर्णांकerrupt_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा smo8800_device *smo8800 = data;

	dev_info(smo8800->dev, "detected free fall\n");
	वापस IRQ_HANDLED;
पूर्ण

अटल acpi_status smo8800_get_resource(काष्ठा acpi_resource *resource,
					व्योम *context)
अणु
	काष्ठा acpi_resource_extended_irq *irq;

	अगर (resource->type != ACPI_RESOURCE_TYPE_EXTENDED_IRQ)
		वापस AE_OK;

	irq = &resource->data.extended_irq;
	अगर (!irq || !irq->पूर्णांकerrupt_count)
		वापस AE_OK;

	*((u32 *)context) = irq->पूर्णांकerrupts[0];
	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल u32 smo8800_get_irq(काष्ठा acpi_device *device)
अणु
	u32 irq = 0;
	acpi_status status;

	status = acpi_walk_resources(device->handle, METHOD_NAME__CRS,
				     smo8800_get_resource, &irq);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&device->dev, "acpi_walk_resources failed\n");
		वापस 0;
	पूर्ण

	वापस irq;
पूर्ण

अटल sमाप_प्रकार smo8800_misc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा smo8800_device *smo8800 = container_of(file->निजी_data,
					 काष्ठा smo8800_device, miscdev);

	u32 data = 0;
	अचिन्हित अक्षर byte_data;
	sमाप_प्रकार retval = 1;

	अगर (count < 1)
		वापस -EINVAL;

	atomic_set(&smo8800->counter, 0);
	retval = रुको_event_पूर्णांकerruptible(smo8800->misc_रुको,
				(data = atomic_xchg(&smo8800->counter, 0)));

	अगर (retval)
		वापस retval;

	retval = 1;

	अगर (data < 255)
		byte_data = data;
	अन्यथा
		byte_data = 255;

	अगर (put_user(byte_data, buf))
		retval = -EFAULT;

	वापस retval;
पूर्ण

अटल पूर्णांक smo8800_misc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा smo8800_device *smo8800 = container_of(file->निजी_data,
					 काष्ठा smo8800_device, miscdev);

	अगर (test_and_set_bit(0, &smo8800->misc_खोलोed))
		वापस -EBUSY; /* alपढ़ोy खोलो */

	atomic_set(&smo8800->counter, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक smo8800_misc_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा smo8800_device *smo8800 = container_of(file->निजी_data,
					 काष्ठा smo8800_device, miscdev);

	clear_bit(0, &smo8800->misc_खोलोed); /* release the device */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations smo8800_misc_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = smo8800_misc_पढ़ो,
	.खोलो = smo8800_misc_खोलो,
	.release = smo8800_misc_release,
पूर्ण;

अटल पूर्णांक smo8800_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक err;
	काष्ठा smo8800_device *smo8800;

	smo8800 = devm_kzalloc(&device->dev, माप(*smo8800), GFP_KERNEL);
	अगर (!smo8800) अणु
		dev_err(&device->dev, "failed to allocate device data\n");
		वापस -ENOMEM;
	पूर्ण

	smo8800->dev = &device->dev;
	smo8800->miscdev.minor = MISC_DYNAMIC_MINOR;
	smo8800->miscdev.name = "freefall";
	smo8800->miscdev.fops = &smo8800_misc_fops;

	init_रुकोqueue_head(&smo8800->misc_रुको);

	err = misc_रेजिस्टर(&smo8800->miscdev);
	अगर (err) अणु
		dev_err(&device->dev, "failed to register misc dev: %d\n", err);
		वापस err;
	पूर्ण

	device->driver_data = smo8800;

	smo8800->irq = smo8800_get_irq(device);
	अगर (!smo8800->irq) अणु
		dev_err(&device->dev, "failed to obtain IRQ\n");
		err = -EINVAL;
		जाओ error;
	पूर्ण

	err = request_thपढ़ोed_irq(smo8800->irq, smo8800_पूर्णांकerrupt_quick,
				   smo8800_पूर्णांकerrupt_thपढ़ो,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				   DRIVER_NAME, smo8800);
	अगर (err) अणु
		dev_err(&device->dev,
			"failed to request thread for IRQ %d: %d\n",
			smo8800->irq, err);
		जाओ error;
	पूर्ण

	dev_dbg(&device->dev, "device /dev/freefall registered with IRQ %d\n",
		 smo8800->irq);
	वापस 0;

error:
	misc_deरेजिस्टर(&smo8800->miscdev);
	वापस err;
पूर्ण

अटल पूर्णांक smo8800_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा smo8800_device *smo8800 = device->driver_data;

	मुक्त_irq(smo8800->irq, smo8800);
	misc_deरेजिस्टर(&smo8800->miscdev);
	dev_dbg(&device->dev, "device /dev/freefall unregistered\n");
	वापस 0;
पूर्ण

/* NOTE: Keep this list in sync with drivers/i2c/busses/i2c-i801.c */
अटल स्थिर काष्ठा acpi_device_id smo8800_ids[] = अणु
	अणु "SMO8800", 0 पूर्ण,
	अणु "SMO8801", 0 पूर्ण,
	अणु "SMO8810", 0 पूर्ण,
	अणु "SMO8811", 0 पूर्ण,
	अणु "SMO8820", 0 पूर्ण,
	अणु "SMO8821", 0 पूर्ण,
	अणु "SMO8830", 0 पूर्ण,
	अणु "SMO8831", 0 पूर्ण,
	अणु "", 0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, smo8800_ids);

अटल काष्ठा acpi_driver smo8800_driver = अणु
	.name = DRIVER_NAME,
	.class = "Latitude",
	.ids = smo8800_ids,
	.ops = अणु
		.add = smo8800_add,
		.हटाओ = smo8800_हटाओ,
	पूर्ण,
	.owner = THIS_MODULE,
पूर्ण;

module_acpi_driver(smo8800_driver);

MODULE_DESCRIPTION("Dell Latitude freefall driver (ACPI SMO88XX)");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sonal Santan, Pali Rohथँr");
