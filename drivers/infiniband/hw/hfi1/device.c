<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/cdev.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>

#समावेश "hfi.h"
#समावेश "device.h"

अटल काष्ठा class *class;
अटल काष्ठा class *user_class;
अटल dev_t hfi1_dev;

पूर्णांक hfi1_cdev_init(पूर्णांक minor, स्थिर अक्षर *name,
		   स्थिर काष्ठा file_operations *fops,
		   काष्ठा cdev *cdev, काष्ठा device **devp,
		   bool user_accessible,
		   काष्ठा kobject *parent)
अणु
	स्थिर dev_t dev = MKDEV(MAJOR(hfi1_dev), minor);
	काष्ठा device *device = शून्य;
	पूर्णांक ret;

	cdev_init(cdev, fops);
	cdev->owner = THIS_MODULE;
	cdev_set_parent(cdev, parent);
	kobject_set_name(&cdev->kobj, name);

	ret = cdev_add(cdev, dev, 1);
	अगर (ret < 0) अणु
		pr_err("Could not add cdev for minor %d, %s (err %d)\n",
		       minor, name, -ret);
		जाओ करोne;
	पूर्ण

	अगर (user_accessible)
		device = device_create(user_class, शून्य, dev, शून्य, "%s", name);
	अन्यथा
		device = device_create(class, शून्य, dev, शून्य, "%s", name);

	अगर (IS_ERR(device)) अणु
		ret = PTR_ERR(device);
		device = शून्य;
		pr_err("Could not create device for minor %d, %s (err %d)\n",
			minor, name, -ret);
		cdev_del(cdev);
	पूर्ण
करोne:
	*devp = device;
	वापस ret;
पूर्ण

व्योम hfi1_cdev_cleanup(काष्ठा cdev *cdev, काष्ठा device **devp)
अणु
	काष्ठा device *device = *devp;

	अगर (device) अणु
		device_unरेजिस्टर(device);
		*devp = शून्य;

		cdev_del(cdev);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *hfi1_class_name = "hfi1";

स्थिर अक्षर *class_name(व्योम)
अणु
	वापस hfi1_class_name;
पूर्ण

अटल अक्षर *hfi1_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (mode)
		*mode = 0600;
	वापस kaप्र_लिखो(GFP_KERNEL, "%s", dev_name(dev));
पूर्ण

अटल स्थिर अक्षर *hfi1_class_name_user = "hfi1_user";
अटल स्थिर अक्षर *class_name_user(व्योम)
अणु
	वापस hfi1_class_name_user;
पूर्ण

अटल अक्षर *hfi1_user_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (mode)
		*mode = 0666;
	वापस kaप्र_लिखो(GFP_KERNEL, "%s", dev_name(dev));
पूर्ण

पूर्णांक __init dev_init(व्योम)
अणु
	पूर्णांक ret;

	ret = alloc_chrdev_region(&hfi1_dev, 0, HFI1_NMINORS, DRIVER_NAME);
	अगर (ret < 0) अणु
		pr_err("Could not allocate chrdev region (err %d)\n", -ret);
		जाओ करोne;
	पूर्ण

	class = class_create(THIS_MODULE, class_name());
	अगर (IS_ERR(class)) अणु
		ret = PTR_ERR(class);
		pr_err("Could not create device class (err %d)\n", -ret);
		unरेजिस्टर_chrdev_region(hfi1_dev, HFI1_NMINORS);
		जाओ करोne;
	पूर्ण
	class->devnode = hfi1_devnode;

	user_class = class_create(THIS_MODULE, class_name_user());
	अगर (IS_ERR(user_class)) अणु
		ret = PTR_ERR(user_class);
		pr_err("Could not create device class for user accessible files (err %d)\n",
		       -ret);
		class_destroy(class);
		class = शून्य;
		user_class = शून्य;
		unरेजिस्टर_chrdev_region(hfi1_dev, HFI1_NMINORS);
		जाओ करोne;
	पूर्ण
	user_class->devnode = hfi1_user_devnode;

करोne:
	वापस ret;
पूर्ण

व्योम dev_cleanup(व्योम)
अणु
	class_destroy(class);
	class = शून्य;

	class_destroy(user_class);
	user_class = शून्य;

	unरेजिस्टर_chrdev_region(hfi1_dev, HFI1_NMINORS);
पूर्ण
