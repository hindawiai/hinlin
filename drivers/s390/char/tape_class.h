<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright IBM Corp. 2004   All Rights Reserved.
 *
 * Tape class device support
 *
 * Author: Stefan Bader <shbader@de.ibm.com>
 * Based on simple class device code by Greg K-H
 */
#अगर_अघोषित __TAPE_CLASS_H__
#घोषणा __TAPE_CLASS_H__

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/major.h>
#समावेश <linux/cdev.h>

#समावेश <linux/device.h>
#समावेश <linux/kdev_t.h>

#घोषणा TAPECLASS_NAME_LEN	32

काष्ठा tape_class_device अणु
	काष्ठा cdev		*अक्षर_device;
	काष्ठा device		*class_device;
	अक्षर			device_name[TAPECLASS_NAME_LEN];
	अक्षर			mode_name[TAPECLASS_NAME_LEN];
पूर्ण;

/*
 * Register a tape device and वापस a poपूर्णांकer to the tape class device
 * created by the call.
 *
 * device
 *	The poपूर्णांकer to the काष्ठा device of the physical (base) device.
 * dev
 *	The पूर्णांकended major/minor number. The major number may be 0 to
 *	get a dynamic major number.
 * fops
 *	The poपूर्णांकer to the drivers file operations क्रम the tape device.
 * device_name
 *	Poपूर्णांकer to the logical device name (will also be used as kobject name
 *	of the cdev). This can also be called the name of the tape class
 *	device.
 * mode_name
 *	Poपूर्णांकs to the name of the tape mode. This creates a link with that
 *	name from the physical device to the logical device (class).
 */
काष्ठा tape_class_device *रेजिस्टर_tape_dev(
	काष्ठा device *		device,
	dev_t			dev,
	स्थिर काष्ठा file_operations *fops,
	अक्षर *			device_name,
	अक्षर *			node_name
);
व्योम unरेजिस्टर_tape_dev(काष्ठा device *device, काष्ठा tape_class_device *tcd);

#पूर्ण_अगर /* __TAPE_CLASS_H__ */
