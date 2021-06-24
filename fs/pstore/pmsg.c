<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014  Google, Inc.
 */

#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश "internal.h"

अटल DEFINE_MUTEX(pmsg_lock);

अटल sमाप_प्रकार ग_लिखो_pmsg(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा pstore_record record;
	पूर्णांक ret;

	अगर (!count)
		वापस 0;

	pstore_record_init(&record, psinfo);
	record.type = PSTORE_TYPE_PMSG;
	record.size = count;

	/* check outside lock, page in any data. ग_लिखो_user also checks */
	अगर (!access_ok(buf, count))
		वापस -EFAULT;

	mutex_lock(&pmsg_lock);
	ret = psinfo->ग_लिखो_user(&record, buf);
	mutex_unlock(&pmsg_lock);
	वापस ret ? ret : count;
पूर्ण

अटल स्थिर काष्ठा file_operations pmsg_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= noop_llseek,
	.ग_लिखो		= ग_लिखो_pmsg,
पूर्ण;

अटल काष्ठा class *pmsg_class;
अटल पूर्णांक pmsg_major;
#घोषणा PMSG_NAME "pmsg"
#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) PMSG_NAME ": " fmt

अटल अक्षर *pmsg_devnode(काष्ठा device *dev, umode_t *mode)
अणु
	अगर (mode)
		*mode = 0220;
	वापस शून्य;
पूर्ण

व्योम pstore_रेजिस्टर_pmsg(व्योम)
अणु
	काष्ठा device *pmsg_device;

	pmsg_major = रेजिस्टर_chrdev(0, PMSG_NAME, &pmsg_fops);
	अगर (pmsg_major < 0) अणु
		pr_err("register_chrdev failed\n");
		जाओ err;
	पूर्ण

	pmsg_class = class_create(THIS_MODULE, PMSG_NAME);
	अगर (IS_ERR(pmsg_class)) अणु
		pr_err("device class file already in use\n");
		जाओ err_class;
	पूर्ण
	pmsg_class->devnode = pmsg_devnode;

	pmsg_device = device_create(pmsg_class, शून्य, MKDEV(pmsg_major, 0),
					शून्य, "%s%d", PMSG_NAME, 0);
	अगर (IS_ERR(pmsg_device)) अणु
		pr_err("failed to create device\n");
		जाओ err_device;
	पूर्ण
	वापस;

err_device:
	class_destroy(pmsg_class);
err_class:
	unरेजिस्टर_chrdev(pmsg_major, PMSG_NAME);
err:
	वापस;
पूर्ण

व्योम pstore_unरेजिस्टर_pmsg(व्योम)
अणु
	device_destroy(pmsg_class, MKDEV(pmsg_major, 0));
	class_destroy(pmsg_class);
	unरेजिस्टर_chrdev(pmsg_major, PMSG_NAME);
पूर्ण
