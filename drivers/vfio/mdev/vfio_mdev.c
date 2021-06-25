<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO based driver क्रम Mediated device
 *
 * Copyright (c) 2016, NVIDIA CORPORATION. All rights reserved.
 *     Author: Neo Jia <cjia@nvidia.com>
 *             Kirti Wankhede <kwankhede@nvidia.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/mdev.h>

#समावेश "mdev_private.h"

#घोषणा DRIVER_VERSION  "0.1"
#घोषणा DRIVER_AUTHOR   "NVIDIA Corporation"
#घोषणा DRIVER_DESC     "VFIO based driver for Mediated device"

अटल पूर्णांक vfio_mdev_खोलो(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(core_vdev->dev);
	काष्ठा mdev_parent *parent = mdev->type->parent;

	पूर्णांक ret;

	अगर (unlikely(!parent->ops->खोलो))
		वापस -EINVAL;

	अगर (!try_module_get(THIS_MODULE))
		वापस -ENODEV;

	ret = parent->ops->खोलो(mdev);
	अगर (ret)
		module_put(THIS_MODULE);

	वापस ret;
पूर्ण

अटल व्योम vfio_mdev_release(काष्ठा vfio_device *core_vdev)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(core_vdev->dev);
	काष्ठा mdev_parent *parent = mdev->type->parent;

	अगर (likely(parent->ops->release))
		parent->ops->release(mdev);

	module_put(THIS_MODULE);
पूर्ण

अटल दीर्घ vfio_mdev_unlocked_ioctl(काष्ठा vfio_device *core_vdev,
				     अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(core_vdev->dev);
	काष्ठा mdev_parent *parent = mdev->type->parent;

	अगर (unlikely(!parent->ops->ioctl))
		वापस -EINVAL;

	वापस parent->ops->ioctl(mdev, cmd, arg);
पूर्ण

अटल sमाप_प्रकार vfio_mdev_पढ़ो(काष्ठा vfio_device *core_vdev, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(core_vdev->dev);
	काष्ठा mdev_parent *parent = mdev->type->parent;

	अगर (unlikely(!parent->ops->पढ़ो))
		वापस -EINVAL;

	वापस parent->ops->पढ़ो(mdev, buf, count, ppos);
पूर्ण

अटल sमाप_प्रकार vfio_mdev_ग_लिखो(काष्ठा vfio_device *core_vdev,
			       स्थिर अक्षर __user *buf, माप_प्रकार count,
			       loff_t *ppos)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(core_vdev->dev);
	काष्ठा mdev_parent *parent = mdev->type->parent;

	अगर (unlikely(!parent->ops->ग_लिखो))
		वापस -EINVAL;

	वापस parent->ops->ग_लिखो(mdev, buf, count, ppos);
पूर्ण

अटल पूर्णांक vfio_mdev_mmap(काष्ठा vfio_device *core_vdev,
			  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(core_vdev->dev);
	काष्ठा mdev_parent *parent = mdev->type->parent;

	अगर (unlikely(!parent->ops->mmap))
		वापस -EINVAL;

	वापस parent->ops->mmap(mdev, vma);
पूर्ण

अटल व्योम vfio_mdev_request(काष्ठा vfio_device *core_vdev, अचिन्हित पूर्णांक count)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(core_vdev->dev);
	काष्ठा mdev_parent *parent = mdev->type->parent;

	अगर (parent->ops->request)
		parent->ops->request(mdev, count);
	अन्यथा अगर (count == 0)
		dev_notice(mdev_dev(mdev),
			   "No mdev vendor driver request callback support, blocked until released by user\n");
पूर्ण

अटल स्थिर काष्ठा vfio_device_ops vfio_mdev_dev_ops = अणु
	.name		= "vfio-mdev",
	.खोलो		= vfio_mdev_खोलो,
	.release	= vfio_mdev_release,
	.ioctl		= vfio_mdev_unlocked_ioctl,
	.पढ़ो		= vfio_mdev_पढ़ो,
	.ग_लिखो		= vfio_mdev_ग_लिखो,
	.mmap		= vfio_mdev_mmap,
	.request	= vfio_mdev_request,
पूर्ण;

अटल पूर्णांक vfio_mdev_probe(काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_device *vdev;
	पूर्णांक ret;

	vdev = kzalloc(माप(*vdev), GFP_KERNEL);
	अगर (!vdev)
		वापस -ENOMEM;

	vfio_init_group_dev(vdev, &mdev->dev, &vfio_mdev_dev_ops);
	ret = vfio_रेजिस्टर_group_dev(vdev);
	अगर (ret) अणु
		kमुक्त(vdev);
		वापस ret;
	पूर्ण
	dev_set_drvdata(&mdev->dev, vdev);
	वापस 0;
पूर्ण

अटल व्योम vfio_mdev_हटाओ(काष्ठा mdev_device *mdev)
अणु
	काष्ठा vfio_device *vdev = dev_get_drvdata(&mdev->dev);

	vfio_unरेजिस्टर_group_dev(vdev);
	kमुक्त(vdev);
पूर्ण

अटल काष्ठा mdev_driver vfio_mdev_driver = अणु
	.driver = अणु
		.name = "vfio_mdev",
		.owner = THIS_MODULE,
		.mod_name = KBUILD_MODNAME,
	पूर्ण,
	.probe	= vfio_mdev_probe,
	.हटाओ	= vfio_mdev_हटाओ,
पूर्ण;

अटल पूर्णांक __init vfio_mdev_init(व्योम)
अणु
	वापस mdev_रेजिस्टर_driver(&vfio_mdev_driver);
पूर्ण

अटल व्योम __निकास vfio_mdev_निकास(व्योम)
अणु
	mdev_unरेजिस्टर_driver(&vfio_mdev_driver);
पूर्ण

module_init(vfio_mdev_init)
module_निकास(vfio_mdev_निकास)

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
