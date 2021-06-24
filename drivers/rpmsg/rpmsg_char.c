<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016, Linaro Ltd.
 * Copyright (c) 2012, Michal Simek <monstr@monstr.eu>
 * Copyright (c) 2012, PetaLogix
 * Copyright (c) 2011, Texas Instruments, Inc.
 * Copyright (c) 2011, Google, Inc.
 *
 * Based on rpmsg perक्रमmance statistics driver by Michal Simek, which in turn
 * was based on TI & Google OMX rpmsg driver.
 */
#समावेश <linux/cdev.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/rpmsg.h>

#समावेश "rpmsg_internal.h"

#घोषणा RPMSG_DEV_MAX	(MINORMASK + 1)

अटल dev_t rpmsg_major;
अटल काष्ठा class *rpmsg_class;

अटल DEFINE_IDA(rpmsg_ctrl_ida);
अटल DEFINE_IDA(rpmsg_ept_ida);
अटल DEFINE_IDA(rpmsg_minor_ida);

#घोषणा dev_to_eptdev(dev) container_of(dev, काष्ठा rpmsg_eptdev, dev)
#घोषणा cdev_to_eptdev(i_cdev) container_of(i_cdev, काष्ठा rpmsg_eptdev, cdev)

#घोषणा dev_to_ctrldev(dev) container_of(dev, काष्ठा rpmsg_ctrldev, dev)
#घोषणा cdev_to_ctrldev(i_cdev) container_of(i_cdev, काष्ठा rpmsg_ctrldev, cdev)

/**
 * काष्ठा rpmsg_ctrldev - control device क्रम instantiating endpoपूर्णांक devices
 * @rpdev:	underlaying rpmsg device
 * @cdev:	cdev क्रम the ctrl device
 * @dev:	device क्रम the ctrl device
 */
काष्ठा rpmsg_ctrldev अणु
	काष्ठा rpmsg_device *rpdev;
	काष्ठा cdev cdev;
	काष्ठा device dev;
पूर्ण;

/**
 * काष्ठा rpmsg_eptdev - endpoपूर्णांक device context
 * @dev:	endpoपूर्णांक device
 * @cdev:	cdev क्रम the endpoपूर्णांक device
 * @rpdev:	underlaying rpmsg device
 * @chinfo:	info used to खोलो the endpoपूर्णांक
 * @ept_lock:	synchronization of @ept modअगरications
 * @ept:	rpmsg endpoपूर्णांक reference, when खोलो
 * @queue_lock:	synchronization of @queue operations
 * @queue:	incoming message queue
 * @पढ़ोq:	रुको object क्रम incoming queue
 */
काष्ठा rpmsg_eptdev अणु
	काष्ठा device dev;
	काष्ठा cdev cdev;

	काष्ठा rpmsg_device *rpdev;
	काष्ठा rpmsg_channel_info chinfo;

	काष्ठा mutex ept_lock;
	काष्ठा rpmsg_endpoपूर्णांक *ept;

	spinlock_t queue_lock;
	काष्ठा sk_buff_head queue;
	रुको_queue_head_t पढ़ोq;
पूर्ण;

अटल पूर्णांक rpmsg_eptdev_destroy(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा rpmsg_eptdev *eptdev = dev_to_eptdev(dev);

	mutex_lock(&eptdev->ept_lock);
	अगर (eptdev->ept) अणु
		rpmsg_destroy_ept(eptdev->ept);
		eptdev->ept = शून्य;
	पूर्ण
	mutex_unlock(&eptdev->ept_lock);

	/* wake up any blocked पढ़ोers */
	wake_up_पूर्णांकerruptible(&eptdev->पढ़ोq);

	device_del(&eptdev->dev);
	put_device(&eptdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rpmsg_ept_cb(काष्ठा rpmsg_device *rpdev, व्योम *buf, पूर्णांक len,
			व्योम *priv, u32 addr)
अणु
	काष्ठा rpmsg_eptdev *eptdev = priv;
	काष्ठा sk_buff *skb;

	skb = alloc_skb(len, GFP_ATOMIC);
	अगर (!skb)
		वापस -ENOMEM;

	skb_put_data(skb, buf, len);

	spin_lock(&eptdev->queue_lock);
	skb_queue_tail(&eptdev->queue, skb);
	spin_unlock(&eptdev->queue_lock);

	/* wake up any blocking processes, रुकोing क्रम new data */
	wake_up_पूर्णांकerruptible(&eptdev->पढ़ोq);

	वापस 0;
पूर्ण

अटल पूर्णांक rpmsg_eptdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rpmsg_eptdev *eptdev = cdev_to_eptdev(inode->i_cdev);
	काष्ठा rpmsg_endpoपूर्णांक *ept;
	काष्ठा rpmsg_device *rpdev = eptdev->rpdev;
	काष्ठा device *dev = &eptdev->dev;

	अगर (eptdev->ept)
		वापस -EBUSY;

	get_device(dev);

	ept = rpmsg_create_ept(rpdev, rpmsg_ept_cb, eptdev, eptdev->chinfo);
	अगर (!ept) अणु
		dev_err(dev, "failed to open %s\n", eptdev->chinfo.name);
		put_device(dev);
		वापस -EINVAL;
	पूर्ण

	eptdev->ept = ept;
	filp->निजी_data = eptdev;

	वापस 0;
पूर्ण

अटल पूर्णांक rpmsg_eptdev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rpmsg_eptdev *eptdev = cdev_to_eptdev(inode->i_cdev);
	काष्ठा device *dev = &eptdev->dev;

	/* Close the endpoपूर्णांक, अगर it's not alपढ़ोy destroyed by the parent */
	mutex_lock(&eptdev->ept_lock);
	अगर (eptdev->ept) अणु
		rpmsg_destroy_ept(eptdev->ept);
		eptdev->ept = शून्य;
	पूर्ण
	mutex_unlock(&eptdev->ept_lock);

	/* Discard all SKBs */
	skb_queue_purge(&eptdev->queue);

	put_device(dev);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rpmsg_eptdev_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा rpmsg_eptdev *eptdev = filp->निजी_data;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	पूर्णांक use;

	अगर (!eptdev->ept)
		वापस -EPIPE;

	spin_lock_irqsave(&eptdev->queue_lock, flags);

	/* Wait क्रम data in the queue */
	अगर (skb_queue_empty(&eptdev->queue)) अणु
		spin_unlock_irqrestore(&eptdev->queue_lock, flags);

		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		/* Wait until we get data or the endpoपूर्णांक goes away */
		अगर (रुको_event_पूर्णांकerruptible(eptdev->पढ़ोq,
					     !skb_queue_empty(&eptdev->queue) ||
					     !eptdev->ept))
			वापस -ERESTARTSYS;

		/* We lost the endpoपूर्णांक जबतक रुकोing */
		अगर (!eptdev->ept)
			वापस -EPIPE;

		spin_lock_irqsave(&eptdev->queue_lock, flags);
	पूर्ण

	skb = skb_dequeue(&eptdev->queue);
	spin_unlock_irqrestore(&eptdev->queue_lock, flags);
	अगर (!skb)
		वापस -EFAULT;

	use = min_t(माप_प्रकार, iov_iter_count(to), skb->len);
	अगर (copy_to_iter(skb->data, use, to) != use)
		use = -EFAULT;

	kमुक्त_skb(skb);

	वापस use;
पूर्ण

अटल sमाप_प्रकार rpmsg_eptdev_ग_लिखो_iter(काष्ठा kiocb *iocb,
				       काष्ठा iov_iter *from)
अणु
	काष्ठा file *filp = iocb->ki_filp;
	काष्ठा rpmsg_eptdev *eptdev = filp->निजी_data;
	माप_प्रकार len = iov_iter_count(from);
	व्योम *kbuf;
	पूर्णांक ret;

	kbuf = kzalloc(len, GFP_KERNEL);
	अगर (!kbuf)
		वापस -ENOMEM;

	अगर (!copy_from_iter_full(kbuf, len, from)) अणु
		ret = -EFAULT;
		जाओ मुक्त_kbuf;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&eptdev->ept_lock)) अणु
		ret = -ERESTARTSYS;
		जाओ मुक्त_kbuf;
	पूर्ण

	अगर (!eptdev->ept) अणु
		ret = -EPIPE;
		जाओ unlock_eptdev;
	पूर्ण

	अगर (filp->f_flags & O_NONBLOCK)
		ret = rpmsg_trysendto(eptdev->ept, kbuf, len, eptdev->chinfo.dst);
	अन्यथा
		ret = rpmsg_sendto(eptdev->ept, kbuf, len, eptdev->chinfo.dst);

unlock_eptdev:
	mutex_unlock(&eptdev->ept_lock);

मुक्त_kbuf:
	kमुक्त(kbuf);
	वापस ret < 0 ? ret : len;
पूर्ण

अटल __poll_t rpmsg_eptdev_poll(काष्ठा file *filp, poll_table *रुको)
अणु
	काष्ठा rpmsg_eptdev *eptdev = filp->निजी_data;
	__poll_t mask = 0;

	अगर (!eptdev->ept)
		वापस EPOLLERR;

	poll_रुको(filp, &eptdev->पढ़ोq, रुको);

	अगर (!skb_queue_empty(&eptdev->queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	mask |= rpmsg_poll(eptdev->ept, filp, रुको);

	वापस mask;
पूर्ण

अटल दीर्घ rpmsg_eptdev_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा rpmsg_eptdev *eptdev = fp->निजी_data;

	अगर (cmd != RPMSG_DESTROY_EPT_IOCTL)
		वापस -EINVAL;

	वापस rpmsg_eptdev_destroy(&eptdev->dev, शून्य);
पूर्ण

अटल स्थिर काष्ठा file_operations rpmsg_eptdev_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = rpmsg_eptdev_खोलो,
	.release = rpmsg_eptdev_release,
	.पढ़ो_iter = rpmsg_eptdev_पढ़ो_iter,
	.ग_लिखो_iter = rpmsg_eptdev_ग_लिखो_iter,
	.poll = rpmsg_eptdev_poll,
	.unlocked_ioctl = rpmsg_eptdev_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rpmsg_eptdev *eptdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", eptdev->chinfo.name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार src_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rpmsg_eptdev *eptdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", eptdev->chinfo.src);
पूर्ण
अटल DEVICE_ATTR_RO(src);

अटल sमाप_प्रकार dst_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा rpmsg_eptdev *eptdev = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", eptdev->chinfo.dst);
पूर्ण
अटल DEVICE_ATTR_RO(dst);

अटल काष्ठा attribute *rpmsg_eptdev_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_src.attr,
	&dev_attr_dst.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(rpmsg_eptdev);

अटल व्योम rpmsg_eptdev_release_device(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_eptdev *eptdev = dev_to_eptdev(dev);

	ida_simple_हटाओ(&rpmsg_ept_ida, dev->id);
	ida_simple_हटाओ(&rpmsg_minor_ida, MINOR(eptdev->dev.devt));
	cdev_del(&eptdev->cdev);
	kमुक्त(eptdev);
पूर्ण

अटल पूर्णांक rpmsg_eptdev_create(काष्ठा rpmsg_ctrldev *ctrldev,
			       काष्ठा rpmsg_channel_info chinfo)
अणु
	काष्ठा rpmsg_device *rpdev = ctrldev->rpdev;
	काष्ठा rpmsg_eptdev *eptdev;
	काष्ठा device *dev;
	पूर्णांक ret;

	eptdev = kzalloc(माप(*eptdev), GFP_KERNEL);
	अगर (!eptdev)
		वापस -ENOMEM;

	dev = &eptdev->dev;
	eptdev->rpdev = rpdev;
	eptdev->chinfo = chinfo;

	mutex_init(&eptdev->ept_lock);
	spin_lock_init(&eptdev->queue_lock);
	skb_queue_head_init(&eptdev->queue);
	init_रुकोqueue_head(&eptdev->पढ़ोq);

	device_initialize(dev);
	dev->class = rpmsg_class;
	dev->parent = &ctrldev->dev;
	dev->groups = rpmsg_eptdev_groups;
	dev_set_drvdata(dev, eptdev);

	cdev_init(&eptdev->cdev, &rpmsg_eptdev_fops);
	eptdev->cdev.owner = THIS_MODULE;

	ret = ida_simple_get(&rpmsg_minor_ida, 0, RPMSG_DEV_MAX, GFP_KERNEL);
	अगर (ret < 0)
		जाओ मुक्त_eptdev;
	dev->devt = MKDEV(MAJOR(rpmsg_major), ret);

	ret = ida_simple_get(&rpmsg_ept_ida, 0, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ मुक्त_minor_ida;
	dev->id = ret;
	dev_set_name(dev, "rpmsg%d", ret);

	ret = cdev_add(&eptdev->cdev, dev->devt, 1);
	अगर (ret)
		जाओ मुक्त_ept_ida;

	/* We can now rely on the release function क्रम cleanup */
	dev->release = rpmsg_eptdev_release_device;

	ret = device_add(dev);
	अगर (ret) अणु
		dev_err(dev, "device_add failed: %d\n", ret);
		put_device(dev);
	पूर्ण

	वापस ret;

मुक्त_ept_ida:
	ida_simple_हटाओ(&rpmsg_ept_ida, dev->id);
मुक्त_minor_ida:
	ida_simple_हटाओ(&rpmsg_minor_ida, MINOR(dev->devt));
मुक्त_eptdev:
	put_device(dev);
	kमुक्त(eptdev);

	वापस ret;
पूर्ण

अटल पूर्णांक rpmsg_ctrldev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rpmsg_ctrldev *ctrldev = cdev_to_ctrldev(inode->i_cdev);

	get_device(&ctrldev->dev);
	filp->निजी_data = ctrldev;

	वापस 0;
पूर्ण

अटल पूर्णांक rpmsg_ctrldev_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा rpmsg_ctrldev *ctrldev = cdev_to_ctrldev(inode->i_cdev);

	put_device(&ctrldev->dev);

	वापस 0;
पूर्ण

अटल दीर्घ rpmsg_ctrldev_ioctl(काष्ठा file *fp, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु
	काष्ठा rpmsg_ctrldev *ctrldev = fp->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा rpmsg_endpoपूर्णांक_info eptinfo;
	काष्ठा rpmsg_channel_info chinfo;

	अगर (cmd != RPMSG_CREATE_EPT_IOCTL)
		वापस -EINVAL;

	अगर (copy_from_user(&eptinfo, argp, माप(eptinfo)))
		वापस -EFAULT;

	स_नकल(chinfo.name, eptinfo.name, RPMSG_NAME_SIZE);
	chinfo.name[RPMSG_NAME_SIZE-1] = '\0';
	chinfo.src = eptinfo.src;
	chinfo.dst = eptinfo.dst;

	वापस rpmsg_eptdev_create(ctrldev, chinfo);
पूर्ण;

अटल स्थिर काष्ठा file_operations rpmsg_ctrldev_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = rpmsg_ctrldev_खोलो,
	.release = rpmsg_ctrldev_release,
	.unlocked_ioctl = rpmsg_ctrldev_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
पूर्ण;

अटल व्योम rpmsg_ctrldev_release_device(काष्ठा device *dev)
अणु
	काष्ठा rpmsg_ctrldev *ctrldev = dev_to_ctrldev(dev);

	ida_simple_हटाओ(&rpmsg_ctrl_ida, dev->id);
	ida_simple_हटाओ(&rpmsg_minor_ida, MINOR(dev->devt));
	cdev_del(&ctrldev->cdev);
	kमुक्त(ctrldev);
पूर्ण

अटल पूर्णांक rpmsg_chrdev_probe(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा rpmsg_ctrldev *ctrldev;
	काष्ठा device *dev;
	पूर्णांक ret;

	ctrldev = kzalloc(माप(*ctrldev), GFP_KERNEL);
	अगर (!ctrldev)
		वापस -ENOMEM;

	ctrldev->rpdev = rpdev;

	dev = &ctrldev->dev;
	device_initialize(dev);
	dev->parent = &rpdev->dev;
	dev->class = rpmsg_class;

	cdev_init(&ctrldev->cdev, &rpmsg_ctrldev_fops);
	ctrldev->cdev.owner = THIS_MODULE;

	ret = ida_simple_get(&rpmsg_minor_ida, 0, RPMSG_DEV_MAX, GFP_KERNEL);
	अगर (ret < 0)
		जाओ मुक्त_ctrldev;
	dev->devt = MKDEV(MAJOR(rpmsg_major), ret);

	ret = ida_simple_get(&rpmsg_ctrl_ida, 0, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ मुक्त_minor_ida;
	dev->id = ret;
	dev_set_name(&ctrldev->dev, "rpmsg_ctrl%d", ret);

	ret = cdev_add(&ctrldev->cdev, dev->devt, 1);
	अगर (ret)
		जाओ मुक्त_ctrl_ida;

	/* We can now rely on the release function क्रम cleanup */
	dev->release = rpmsg_ctrldev_release_device;

	ret = device_add(dev);
	अगर (ret) अणु
		dev_err(&rpdev->dev, "device_add failed: %d\n", ret);
		put_device(dev);
	पूर्ण

	dev_set_drvdata(&rpdev->dev, ctrldev);

	वापस ret;

मुक्त_ctrl_ida:
	ida_simple_हटाओ(&rpmsg_ctrl_ida, dev->id);
मुक्त_minor_ida:
	ida_simple_हटाओ(&rpmsg_minor_ida, MINOR(dev->devt));
मुक्त_ctrldev:
	put_device(dev);
	kमुक्त(ctrldev);

	वापस ret;
पूर्ण

अटल व्योम rpmsg_chrdev_हटाओ(काष्ठा rpmsg_device *rpdev)
अणु
	काष्ठा rpmsg_ctrldev *ctrldev = dev_get_drvdata(&rpdev->dev);
	पूर्णांक ret;

	/* Destroy all endpoपूर्णांकs */
	ret = device_क्रम_each_child(&ctrldev->dev, शून्य, rpmsg_eptdev_destroy);
	अगर (ret)
		dev_warn(&rpdev->dev, "failed to nuke endpoints: %d\n", ret);

	device_del(&ctrldev->dev);
	put_device(&ctrldev->dev);
पूर्ण

अटल काष्ठा rpmsg_driver rpmsg_chrdev_driver = अणु
	.probe = rpmsg_chrdev_probe,
	.हटाओ = rpmsg_chrdev_हटाओ,
	.drv = अणु
		.name = "rpmsg_chrdev",
	पूर्ण,
पूर्ण;

अटल पूर्णांक rpmsg_chrdev_init(व्योम)
अणु
	पूर्णांक ret;

	ret = alloc_chrdev_region(&rpmsg_major, 0, RPMSG_DEV_MAX, "rpmsg");
	अगर (ret < 0) अणु
		pr_err("rpmsg: failed to allocate char dev region\n");
		वापस ret;
	पूर्ण

	rpmsg_class = class_create(THIS_MODULE, "rpmsg");
	अगर (IS_ERR(rpmsg_class)) अणु
		pr_err("failed to create rpmsg class\n");
		unरेजिस्टर_chrdev_region(rpmsg_major, RPMSG_DEV_MAX);
		वापस PTR_ERR(rpmsg_class);
	पूर्ण

	ret = रेजिस्टर_rpmsg_driver(&rpmsg_chrdev_driver);
	अगर (ret < 0) अणु
		pr_err("rpmsgchr: failed to register rpmsg driver\n");
		class_destroy(rpmsg_class);
		unरेजिस्टर_chrdev_region(rpmsg_major, RPMSG_DEV_MAX);
	पूर्ण

	वापस ret;
पूर्ण
postcore_initcall(rpmsg_chrdev_init);

अटल व्योम rpmsg_chrdev_निकास(व्योम)
अणु
	unरेजिस्टर_rpmsg_driver(&rpmsg_chrdev_driver);
	class_destroy(rpmsg_class);
	unरेजिस्टर_chrdev_region(rpmsg_major, RPMSG_DEV_MAX);
पूर्ण
module_निकास(rpmsg_chrdev_निकास);

MODULE_ALIAS("rpmsg:rpmsg_chrdev");
MODULE_LICENSE("GPL v2");
