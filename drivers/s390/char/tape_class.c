<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2004
 *
 * Tape class device support
 *
 * Author: Stefan Bader <shbader@de.ibm.com>
 * Based on simple class device code by Greg K-H
 */

#घोषणा KMSG_COMPONENT "tape"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/slab.h>

#समावेश "tape_class.h"

MODULE_AUTHOR("Stefan Bader <shbader@de.ibm.com>");
MODULE_DESCRIPTION(
	"Copyright IBM Corp. 2004   All Rights Reserved.\n"
	"tape_class.c"
);
MODULE_LICENSE("GPL");

अटल काष्ठा class *tape_class;

/*
 * Register a tape device and वापस a poपूर्णांकer to the cdev काष्ठाure.
 *
 * device
 *	The poपूर्णांकer to the काष्ठा device of the physical (base) device.
 * drivername
 *	The poपूर्णांकer to the drivers name क्रम it's अक्षरacter devices.
 * dev
 *	The पूर्णांकended major/minor number. The major number may be 0 to
 *	get a dynamic major number.
 * fops
 *	The poपूर्णांकer to the drivers file operations क्रम the tape device.
 * devname
 *	The poपूर्णांकer to the name of the अक्षरacter device.
 */
काष्ठा tape_class_device *रेजिस्टर_tape_dev(
	काष्ठा device *		device,
	dev_t			dev,
	स्थिर काष्ठा file_operations *fops,
	अक्षर *			device_name,
	अक्षर *			mode_name)
अणु
	काष्ठा tape_class_device *	tcd;
	पूर्णांक		rc;
	अक्षर *		s;

	tcd = kzalloc(माप(काष्ठा tape_class_device), GFP_KERNEL);
	अगर (!tcd)
		वापस ERR_PTR(-ENOMEM);

	strlcpy(tcd->device_name, device_name, TAPECLASS_NAME_LEN);
	क्रम (s = म_अक्षर(tcd->device_name, '/'); s; s = strchr(s, '/'))
		*s = '!';
	strlcpy(tcd->mode_name, mode_name, TAPECLASS_NAME_LEN);
	क्रम (s = म_अक्षर(tcd->mode_name, '/'); s; s = strchr(s, '/'))
		*s = '!';

	tcd->अक्षर_device = cdev_alloc();
	अगर (!tcd->अक्षर_device) अणु
		rc = -ENOMEM;
		जाओ fail_with_tcd;
	पूर्ण

	tcd->अक्षर_device->owner = fops->owner;
	tcd->अक्षर_device->ops   = fops;

	rc = cdev_add(tcd->अक्षर_device, dev, 1);
	अगर (rc)
		जाओ fail_with_cdev;

	tcd->class_device = device_create(tape_class, device,
					  tcd->अक्षर_device->dev, शून्य,
					  "%s", tcd->device_name);
	rc = PTR_ERR_OR_ZERO(tcd->class_device);
	अगर (rc)
		जाओ fail_with_cdev;
	rc = sysfs_create_link(
		&device->kobj,
		&tcd->class_device->kobj,
		tcd->mode_name
	);
	अगर (rc)
		जाओ fail_with_class_device;

	वापस tcd;

fail_with_class_device:
	device_destroy(tape_class, tcd->अक्षर_device->dev);

fail_with_cdev:
	cdev_del(tcd->अक्षर_device);

fail_with_tcd:
	kमुक्त(tcd);

	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_tape_dev);

व्योम unरेजिस्टर_tape_dev(काष्ठा device *device, काष्ठा tape_class_device *tcd)
अणु
	अगर (tcd != शून्य && !IS_ERR(tcd)) अणु
		sysfs_हटाओ_link(&device->kobj, tcd->mode_name);
		device_destroy(tape_class, tcd->अक्षर_device->dev);
		cdev_del(tcd->अक्षर_device);
		kमुक्त(tcd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_tape_dev);


अटल पूर्णांक __init tape_init(व्योम)
अणु
	tape_class = class_create(THIS_MODULE, "tape390");

	वापस 0;
पूर्ण

अटल व्योम __निकास tape_निकास(व्योम)
अणु
	class_destroy(tape_class);
	tape_class = शून्य;
पूर्ण

postcore_initcall(tape_init);
module_निकास(tape_निकास);
