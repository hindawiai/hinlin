<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Character device पूर्णांकerface driver क्रम Remoteproc framework.
 *
 * Copyright (c) 2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/cdev.h>
#समावेश <linux/compat.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/remoteproc_cdev.h>

#समावेश "remoteproc_internal.h"

#घोषणा NUM_RPROC_DEVICES	64
अटल dev_t rproc_major;

अटल sमाप_प्रकार rproc_cdev_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t *pos)
अणु
	काष्ठा rproc *rproc = container_of(filp->f_inode->i_cdev, काष्ठा rproc, cdev);
	पूर्णांक ret = 0;
	अक्षर cmd[10];

	अगर (!len || len > माप(cmd))
		वापस -EINVAL;

	ret = copy_from_user(cmd, buf, len);
	अगर (ret)
		वापस -EFAULT;

	अगर (!म_भेदन(cmd, "start", len)) अणु
		अगर (rproc->state == RPROC_RUNNING ||
		    rproc->state == RPROC_ATTACHED)
			वापस -EBUSY;

		ret = rproc_boot(rproc);
	पूर्ण अन्यथा अगर (!म_भेदन(cmd, "stop", len)) अणु
		अगर (rproc->state != RPROC_RUNNING &&
		    rproc->state != RPROC_ATTACHED)
			वापस -EINVAL;

		rproc_shutकरोwn(rproc);
	पूर्ण अन्यथा अगर (!म_भेदन(cmd, "detach", len)) अणु
		अगर (rproc->state != RPROC_ATTACHED)
			वापस -EINVAL;

		ret = rproc_detach(rproc);
	पूर्ण अन्यथा अणु
		dev_err(&rproc->dev, "Unrecognized option\n");
		ret = -EINVAL;
	पूर्ण

	वापस ret ? ret : len;
पूर्ण

अटल दीर्घ rproc_device_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक ioctl, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rproc *rproc = container_of(filp->f_inode->i_cdev, काष्ठा rproc, cdev);
	व्योम __user *argp = (व्योम __user *)arg;
	s32 param;

	चयन (ioctl) अणु
	हाल RPROC_SET_SHUTDOWN_ON_RELEASE:
		अगर (copy_from_user(&param, argp, माप(s32)))
			वापस -EFAULT;

		rproc->cdev_put_on_release = !!param;
		अवरोध;
	हाल RPROC_GET_SHUTDOWN_ON_RELEASE:
		param = (s32)rproc->cdev_put_on_release;
		अगर (copy_to_user(argp, &param, माप(s32)))
			वापस -EFAULT;

		अवरोध;
	शेष:
		dev_err(&rproc->dev, "Unsupported ioctl\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rproc_cdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rproc *rproc = container_of(inode->i_cdev, काष्ठा rproc, cdev);
	पूर्णांक ret = 0;

	अगर (!rproc->cdev_put_on_release)
		वापस 0;

	अगर (rproc->state == RPROC_RUNNING)
		rproc_shutकरोwn(rproc);
	अन्यथा अगर (rproc->state == RPROC_ATTACHED)
		ret = rproc_detach(rproc);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations rproc_fops = अणु
	.ग_लिखो = rproc_cdev_ग_लिखो,
	.unlocked_ioctl = rproc_device_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.release = rproc_cdev_release,
पूर्ण;

पूर्णांक rproc_अक्षर_device_add(काष्ठा rproc *rproc)
अणु
	पूर्णांक ret;

	cdev_init(&rproc->cdev, &rproc_fops);
	rproc->cdev.owner = THIS_MODULE;

	rproc->dev.devt = MKDEV(MAJOR(rproc_major), rproc->index);
	cdev_set_parent(&rproc->cdev, &rproc->dev.kobj);
	ret = cdev_add(&rproc->cdev, rproc->dev.devt, 1);
	अगर (ret < 0)
		dev_err(&rproc->dev, "Failed to add char dev for %s\n", rproc->name);

	वापस ret;
पूर्ण

व्योम rproc_अक्षर_device_हटाओ(काष्ठा rproc *rproc)
अणु
	__unरेजिस्टर_chrdev(MAJOR(rproc->dev.devt), rproc->index, 1, "remoteproc");
पूर्ण

व्योम __init rproc_init_cdev(व्योम)
अणु
	पूर्णांक ret;

	ret = alloc_chrdev_region(&rproc_major, 0, NUM_RPROC_DEVICES, "remoteproc");
	अगर (ret < 0)
		pr_err("Failed to alloc rproc_cdev region, err %d\n", ret);
पूर्ण
