<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश <linux/compat.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/poll.h>
#समावेश <linux/slab.h>
#समावेश <linux/uacce.h>

अटल काष्ठा class *uacce_class;
अटल dev_t uacce_devt;
अटल DEFINE_MUTEX(uacce_mutex);
अटल DEFINE_XARRAY_ALLOC(uacce_xa);

अटल पूर्णांक uacce_start_queue(काष्ठा uacce_queue *q)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&uacce_mutex);

	अगर (q->state != UACCE_Q_INIT) अणु
		ret = -EINVAL;
		जाओ out_with_lock;
	पूर्ण

	अगर (q->uacce->ops->start_queue) अणु
		ret = q->uacce->ops->start_queue(q);
		अगर (ret < 0)
			जाओ out_with_lock;
	पूर्ण

	q->state = UACCE_Q_STARTED;

out_with_lock:
	mutex_unlock(&uacce_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक uacce_put_queue(काष्ठा uacce_queue *q)
अणु
	काष्ठा uacce_device *uacce = q->uacce;

	mutex_lock(&uacce_mutex);

	अगर (q->state == UACCE_Q_ZOMBIE)
		जाओ out;

	अगर ((q->state == UACCE_Q_STARTED) && uacce->ops->stop_queue)
		uacce->ops->stop_queue(q);

	अगर ((q->state == UACCE_Q_INIT || q->state == UACCE_Q_STARTED) &&
	     uacce->ops->put_queue)
		uacce->ops->put_queue(q);

	q->state = UACCE_Q_ZOMBIE;
out:
	mutex_unlock(&uacce_mutex);

	वापस 0;
पूर्ण

अटल दीर्घ uacce_fops_unl_ioctl(काष्ठा file *filep,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा uacce_queue *q = filep->निजी_data;
	काष्ठा uacce_device *uacce = q->uacce;

	चयन (cmd) अणु
	हाल UACCE_CMD_START_Q:
		वापस uacce_start_queue(q);

	हाल UACCE_CMD_PUT_Q:
		वापस uacce_put_queue(q);

	शेष:
		अगर (!uacce->ops->ioctl)
			वापस -EINVAL;

		वापस uacce->ops->ioctl(q, cmd, arg);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल दीर्घ uacce_fops_compat_ioctl(काष्ठा file *filep,
				   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	arg = (अचिन्हित दीर्घ)compat_ptr(arg);

	वापस uacce_fops_unl_ioctl(filep, cmd, arg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक uacce_bind_queue(काष्ठा uacce_device *uacce, काष्ठा uacce_queue *q)
अणु
	u32 pasid;
	काष्ठा iommu_sva *handle;

	अगर (!(uacce->flags & UACCE_DEV_SVA))
		वापस 0;

	handle = iommu_sva_bind_device(uacce->parent, current->mm, शून्य);
	अगर (IS_ERR(handle))
		वापस PTR_ERR(handle);

	pasid = iommu_sva_get_pasid(handle);
	अगर (pasid == IOMMU_PASID_INVALID) अणु
		iommu_sva_unbind_device(handle);
		वापस -ENODEV;
	पूर्ण

	q->handle = handle;
	q->pasid = pasid;
	वापस 0;
पूर्ण

अटल व्योम uacce_unbind_queue(काष्ठा uacce_queue *q)
अणु
	अगर (!q->handle)
		वापस;
	iommu_sva_unbind_device(q->handle);
	q->handle = शून्य;
पूर्ण

अटल पूर्णांक uacce_fops_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा uacce_device *uacce;
	काष्ठा uacce_queue *q;
	पूर्णांक ret;

	uacce = xa_load(&uacce_xa, iminor(inode));
	अगर (!uacce)
		वापस -ENODEV;

	q = kzalloc(माप(काष्ठा uacce_queue), GFP_KERNEL);
	अगर (!q)
		वापस -ENOMEM;

	ret = uacce_bind_queue(uacce, q);
	अगर (ret)
		जाओ out_with_mem;

	q->uacce = uacce;

	अगर (uacce->ops->get_queue) अणु
		ret = uacce->ops->get_queue(uacce, q->pasid, q);
		अगर (ret < 0)
			जाओ out_with_bond;
	पूर्ण

	init_रुकोqueue_head(&q->रुको);
	filep->निजी_data = q;
	uacce->inode = inode;
	q->state = UACCE_Q_INIT;

	mutex_lock(&uacce->queues_lock);
	list_add(&q->list, &uacce->queues);
	mutex_unlock(&uacce->queues_lock);

	वापस 0;

out_with_bond:
	uacce_unbind_queue(q);
out_with_mem:
	kमुक्त(q);
	वापस ret;
पूर्ण

अटल पूर्णांक uacce_fops_release(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा uacce_queue *q = filep->निजी_data;

	mutex_lock(&q->uacce->queues_lock);
	list_del(&q->list);
	mutex_unlock(&q->uacce->queues_lock);
	uacce_put_queue(q);
	uacce_unbind_queue(q);
	kमुक्त(q);

	वापस 0;
पूर्ण

अटल व्योम uacce_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा uacce_queue *q = vma->vm_निजी_data;
	काष्ठा uacce_qfile_region *qfr = शून्य;

	अगर (vma->vm_pgoff < UACCE_MAX_REGION)
		qfr = q->qfrs[vma->vm_pgoff];

	kमुक्त(qfr);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा uacce_vm_ops = अणु
	.बंद = uacce_vma_बंद,
पूर्ण;

अटल पूर्णांक uacce_fops_mmap(काष्ठा file *filep, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा uacce_queue *q = filep->निजी_data;
	काष्ठा uacce_device *uacce = q->uacce;
	काष्ठा uacce_qfile_region *qfr;
	क्रमागत uacce_qfrt type = UACCE_MAX_REGION;
	पूर्णांक ret = 0;

	अगर (vma->vm_pgoff < UACCE_MAX_REGION)
		type = vma->vm_pgoff;
	अन्यथा
		वापस -EINVAL;

	qfr = kzalloc(माप(*qfr), GFP_KERNEL);
	अगर (!qfr)
		वापस -ENOMEM;

	vma->vm_flags |= VM_DONTCOPY | VM_DONTEXPAND | VM_WIPEONFORK;
	vma->vm_ops = &uacce_vm_ops;
	vma->vm_निजी_data = q;
	qfr->type = type;

	mutex_lock(&uacce_mutex);

	अगर (q->state != UACCE_Q_INIT && q->state != UACCE_Q_STARTED) अणु
		ret = -EINVAL;
		जाओ out_with_lock;
	पूर्ण

	अगर (q->qfrs[type]) अणु
		ret = -EEXIST;
		जाओ out_with_lock;
	पूर्ण

	चयन (type) अणु
	हाल UACCE_QFRT_MMIO:
	हाल UACCE_QFRT_DUS:
		अगर (!uacce->ops->mmap) अणु
			ret = -EINVAL;
			जाओ out_with_lock;
		पूर्ण

		ret = uacce->ops->mmap(q, vma, qfr);
		अगर (ret)
			जाओ out_with_lock;
		अवरोध;

	शेष:
		ret = -EINVAL;
		जाओ out_with_lock;
	पूर्ण

	q->qfrs[type] = qfr;
	mutex_unlock(&uacce_mutex);

	वापस ret;

out_with_lock:
	mutex_unlock(&uacce_mutex);
	kमुक्त(qfr);
	वापस ret;
पूर्ण

अटल __poll_t uacce_fops_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा uacce_queue *q = file->निजी_data;
	काष्ठा uacce_device *uacce = q->uacce;

	poll_रुको(file, &q->रुको, रुको);
	अगर (uacce->ops->is_q_updated && uacce->ops->is_q_updated(q))
		वापस EPOLLIN | EPOLLRDNORM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations uacce_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= uacce_fops_खोलो,
	.release	= uacce_fops_release,
	.unlocked_ioctl	= uacce_fops_unl_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= uacce_fops_compat_ioctl,
#पूर्ण_अगर
	.mmap		= uacce_fops_mmap,
	.poll		= uacce_fops_poll,
पूर्ण;

#घोषणा to_uacce_device(dev) container_of(dev, काष्ठा uacce_device, dev)

अटल sमाप_प्रकार api_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	वापस प्र_लिखो(buf, "%s\n", uacce->api_ver);
पूर्ण

अटल sमाप_प्रकार flags_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	वापस प्र_लिखो(buf, "%u\n", uacce->flags);
पूर्ण

अटल sमाप_प्रकार available_instances_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	अगर (!uacce->ops->get_available_instances)
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%d\n",
		       uacce->ops->get_available_instances(uacce));
पूर्ण

अटल sमाप_प्रकार algorithms_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	वापस प्र_लिखो(buf, "%s\n", uacce->algs);
पूर्ण

अटल sमाप_प्रकार region_mmio_size_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	वापस प्र_लिखो(buf, "%lu\n",
		       uacce->qf_pg_num[UACCE_QFRT_MMIO] << PAGE_SHIFT);
पूर्ण

अटल sमाप_प्रकार region_dus_size_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	वापस प्र_लिखो(buf, "%lu\n",
		       uacce->qf_pg_num[UACCE_QFRT_DUS] << PAGE_SHIFT);
पूर्ण

अटल DEVICE_ATTR_RO(api);
अटल DEVICE_ATTR_RO(flags);
अटल DEVICE_ATTR_RO(available_instances);
अटल DEVICE_ATTR_RO(algorithms);
अटल DEVICE_ATTR_RO(region_mmio_size);
अटल DEVICE_ATTR_RO(region_dus_size);

अटल काष्ठा attribute *uacce_dev_attrs[] = अणु
	&dev_attr_api.attr,
	&dev_attr_flags.attr,
	&dev_attr_available_instances.attr,
	&dev_attr_algorithms.attr,
	&dev_attr_region_mmio_size.attr,
	&dev_attr_region_dus_size.attr,
	शून्य,
पूर्ण;

अटल umode_t uacce_dev_is_visible(काष्ठा kobject *kobj,
				    काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	अगर (((attr == &dev_attr_region_mmio_size.attr) &&
	    (!uacce->qf_pg_num[UACCE_QFRT_MMIO])) ||
	    ((attr == &dev_attr_region_dus_size.attr) &&
	    (!uacce->qf_pg_num[UACCE_QFRT_DUS])))
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल काष्ठा attribute_group uacce_dev_group = अणु
	.is_visible	= uacce_dev_is_visible,
	.attrs		= uacce_dev_attrs,
पूर्ण;

__ATTRIBUTE_GROUPS(uacce_dev);

अटल व्योम uacce_release(काष्ठा device *dev)
अणु
	काष्ठा uacce_device *uacce = to_uacce_device(dev);

	kमुक्त(uacce);
पूर्ण

अटल अचिन्हित पूर्णांक uacce_enable_sva(काष्ठा device *parent, अचिन्हित पूर्णांक flags)
अणु
	अगर (!(flags & UACCE_DEV_SVA))
		वापस flags;

	flags &= ~UACCE_DEV_SVA;

	अगर (iommu_dev_enable_feature(parent, IOMMU_DEV_FEAT_IOPF))
		वापस flags;

	अगर (iommu_dev_enable_feature(parent, IOMMU_DEV_FEAT_SVA)) अणु
		iommu_dev_disable_feature(parent, IOMMU_DEV_FEAT_IOPF);
		वापस flags;
	पूर्ण

	वापस flags | UACCE_DEV_SVA;
पूर्ण

अटल व्योम uacce_disable_sva(काष्ठा uacce_device *uacce)
अणु
	अगर (!(uacce->flags & UACCE_DEV_SVA))
		वापस;

	iommu_dev_disable_feature(uacce->parent, IOMMU_DEV_FEAT_SVA);
	iommu_dev_disable_feature(uacce->parent, IOMMU_DEV_FEAT_IOPF);
पूर्ण

/**
 * uacce_alloc() - alloc an accelerator
 * @parent: poपूर्णांकer of uacce parent device
 * @पूर्णांकerface: poपूर्णांकer of uacce_पूर्णांकerface क्रम रेजिस्टर
 *
 * Returns uacce poपूर्णांकer अगर success and ERR_PTR अगर not
 * Need check वापसed negotiated uacce->flags
 */
काष्ठा uacce_device *uacce_alloc(काष्ठा device *parent,
				 काष्ठा uacce_पूर्णांकerface *पूर्णांकerface)
अणु
	अचिन्हित पूर्णांक flags = पूर्णांकerface->flags;
	काष्ठा uacce_device *uacce;
	पूर्णांक ret;

	uacce = kzalloc(माप(काष्ठा uacce_device), GFP_KERNEL);
	अगर (!uacce)
		वापस ERR_PTR(-ENOMEM);

	flags = uacce_enable_sva(parent, flags);

	uacce->parent = parent;
	uacce->flags = flags;
	uacce->ops = पूर्णांकerface->ops;

	ret = xa_alloc(&uacce_xa, &uacce->dev_id, uacce, xa_limit_32b,
		       GFP_KERNEL);
	अगर (ret < 0)
		जाओ err_with_uacce;

	INIT_LIST_HEAD(&uacce->queues);
	mutex_init(&uacce->queues_lock);
	device_initialize(&uacce->dev);
	uacce->dev.devt = MKDEV(MAJOR(uacce_devt), uacce->dev_id);
	uacce->dev.class = uacce_class;
	uacce->dev.groups = uacce_dev_groups;
	uacce->dev.parent = uacce->parent;
	uacce->dev.release = uacce_release;
	dev_set_name(&uacce->dev, "%s-%d", पूर्णांकerface->name, uacce->dev_id);

	वापस uacce;

err_with_uacce:
	uacce_disable_sva(uacce);
	kमुक्त(uacce);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(uacce_alloc);

/**
 * uacce_रेजिस्टर() - add the accelerator to cdev and export to user space
 * @uacce: The initialized uacce device
 *
 * Return 0 अगर रेजिस्टर succeeded, or an error.
 */
पूर्णांक uacce_रेजिस्टर(काष्ठा uacce_device *uacce)
अणु
	अगर (!uacce)
		वापस -ENODEV;

	uacce->cdev = cdev_alloc();
	अगर (!uacce->cdev)
		वापस -ENOMEM;

	uacce->cdev->ops = &uacce_fops;
	uacce->cdev->owner = THIS_MODULE;

	वापस cdev_device_add(uacce->cdev, &uacce->dev);
पूर्ण
EXPORT_SYMBOL_GPL(uacce_रेजिस्टर);

/**
 * uacce_हटाओ() - हटाओ the accelerator
 * @uacce: the accelerator to हटाओ
 */
व्योम uacce_हटाओ(काष्ठा uacce_device *uacce)
अणु
	काष्ठा uacce_queue *q, *next_q;

	अगर (!uacce)
		वापस;
	/*
	 * unmap reमुख्यing mapping from user space, preventing user still
	 * access the mmaped area जबतक parent device is alपढ़ोy हटाओd
	 */
	अगर (uacce->inode)
		unmap_mapping_range(uacce->inode->i_mapping, 0, 0, 1);

	/* ensure no खोलो queue reमुख्यs */
	mutex_lock(&uacce->queues_lock);
	list_क्रम_each_entry_safe(q, next_q, &uacce->queues, list) अणु
		uacce_put_queue(q);
		uacce_unbind_queue(q);
	पूर्ण
	mutex_unlock(&uacce->queues_lock);

	/* disable sva now since no खोलोed queues */
	uacce_disable_sva(uacce);

	अगर (uacce->cdev)
		cdev_device_del(uacce->cdev, &uacce->dev);
	xa_erase(&uacce_xa, uacce->dev_id);
	put_device(&uacce->dev);
पूर्ण
EXPORT_SYMBOL_GPL(uacce_हटाओ);

अटल पूर्णांक __init uacce_init(व्योम)
अणु
	पूर्णांक ret;

	uacce_class = class_create(THIS_MODULE, UACCE_NAME);
	अगर (IS_ERR(uacce_class))
		वापस PTR_ERR(uacce_class);

	ret = alloc_chrdev_region(&uacce_devt, 0, MINORMASK, UACCE_NAME);
	अगर (ret)
		class_destroy(uacce_class);

	वापस ret;
पूर्ण

अटल __निकास व्योम uacce_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(uacce_devt, MINORMASK);
	class_destroy(uacce_class);
पूर्ण

subsys_initcall(uacce_init);
module_निकास(uacce_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HiSilicon Tech. Co., Ltd.");
MODULE_DESCRIPTION("Accelerator interface for Userland applications");
