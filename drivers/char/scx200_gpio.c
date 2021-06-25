<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* linux/drivers/अक्षर/scx200_gpio.c

   National Semiconductor SCx200 GPIO driver.  Allows a user space
   process to play with the GPIO pins.

   Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com> */

#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>

#समावेश <linux/types.h>
#समावेश <linux/cdev.h>

#समावेश <linux/scx200_gpपन.स>
#समावेश <linux/nsc_gpपन.स>

#घोषणा DRVNAME "scx200_gpio"

अटल काष्ठा platक्रमm_device *pdev;

MODULE_AUTHOR("Christer Weinigel <wingel@nano-system.com>");
MODULE_DESCRIPTION("NatSemi/AMD SCx200 GPIO Pin Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक major = 0;		/* शेष to dynamic major */
module_param(major, पूर्णांक, 0);
MODULE_PARM_DESC(major, "Major device number");

#घोषणा MAX_PINS 32		/* 64 later, when known ok */

काष्ठा nsc_gpio_ops scx200_gpio_ops = अणु
	.owner		= THIS_MODULE,
	.gpio_config	= scx200_gpio_configure,
	.gpio_dump	= nsc_gpio_dump,
	.gpio_get	= scx200_gpio_get,
	.gpio_set	= scx200_gpio_set,
	.gpio_change	= scx200_gpio_change,
	.gpio_current	= scx200_gpio_current
पूर्ण;
EXPORT_SYMBOL_GPL(scx200_gpio_ops);

अटल पूर्णांक scx200_gpio_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित m = iminor(inode);
	file->निजी_data = &scx200_gpio_ops;

	अगर (m >= MAX_PINS)
		वापस -EINVAL;
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक scx200_gpio_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations scx200_gpio_fileops = अणु
	.owner   = THIS_MODULE,
	.ग_लिखो   = nsc_gpio_ग_लिखो,
	.पढ़ो    = nsc_gpio_पढ़ो,
	.खोलो    = scx200_gpio_खोलो,
	.release = scx200_gpio_release,
	.llseek  = no_llseek,
पूर्ण;

अटल काष्ठा cdev scx200_gpio_cdev;  /* use 1 cdev क्रम all pins */

अटल पूर्णांक __init scx200_gpio_init(व्योम)
अणु
	पूर्णांक rc;
	dev_t devid;

	अगर (!scx200_gpio_present()) अणु
		prपूर्णांकk(KERN_ERR DRVNAME ": no SCx200 gpio present\n");
		वापस -ENODEV;
	पूर्ण

	/* support dev_dbg() with pdev->dev */
	pdev = platक्रमm_device_alloc(DRVNAME, 0);
	अगर (!pdev)
		वापस -ENOMEM;

	rc = platक्रमm_device_add(pdev);
	अगर (rc)
		जाओ unकरो_दो_स्मृति;

	/* nsc_gpio uses dev_dbg(), so needs this */
	scx200_gpio_ops.dev = &pdev->dev;

	अगर (major) अणु
		devid = MKDEV(major, 0);
		rc = रेजिस्टर_chrdev_region(devid, MAX_PINS, "scx200_gpio");
	पूर्ण अन्यथा अणु
		rc = alloc_chrdev_region(&devid, 0, MAX_PINS, "scx200_gpio");
		major = MAJOR(devid);
	पूर्ण
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "SCx200 chrdev_region err: %d\n", rc);
		जाओ unकरो_platक्रमm_device_add;
	पूर्ण

	cdev_init(&scx200_gpio_cdev, &scx200_gpio_fileops);
	cdev_add(&scx200_gpio_cdev, devid, MAX_PINS);

	वापस 0; /* succeed */

unकरो_platक्रमm_device_add:
	platक्रमm_device_del(pdev);
unकरो_दो_स्मृति:
	platक्रमm_device_put(pdev);

	वापस rc;
पूर्ण

अटल व्योम __निकास scx200_gpio_cleanup(व्योम)
अणु
	cdev_del(&scx200_gpio_cdev);
	/* cdev_put(&scx200_gpio_cdev); */

	unरेजिस्टर_chrdev_region(MKDEV(major, 0), MAX_PINS);
	platक्रमm_device_unरेजिस्टर(pdev);
पूर्ण

module_init(scx200_gpio_init);
module_निकास(scx200_gpio_cleanup);
