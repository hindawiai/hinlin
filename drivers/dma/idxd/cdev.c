<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2019 Intel Corporation. All rights rsvd. */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/पूर्णांकel-svm.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/iommu.h>
#समावेश <uapi/linux/idxd.h>
#समावेश "registers.h"
#समावेश "idxd.h"

काष्ठा idxd_cdev_context अणु
	स्थिर अक्षर *name;
	dev_t devt;
	काष्ठा ida minor_ida;
पूर्ण;

/*
 * ictx is an array based off of accelerator types. क्रमागत idxd_type
 * is used as index
 */
अटल काष्ठा idxd_cdev_context ictx[IDXD_TYPE_MAX] = अणु
	अणु .name = "dsa" पूर्ण,
	अणु .name = "iax" पूर्ण
पूर्ण;

काष्ठा idxd_user_context अणु
	काष्ठा idxd_wq *wq;
	काष्ठा task_काष्ठा *task;
	अचिन्हित पूर्णांक pasid;
	अचिन्हित पूर्णांक flags;
	काष्ठा iommu_sva *sva;
पूर्ण;

अटल व्योम idxd_cdev_dev_release(काष्ठा device *dev)
अणु
	काष्ठा idxd_cdev *idxd_cdev = container_of(dev, काष्ठा idxd_cdev, dev);
	काष्ठा idxd_cdev_context *cdev_ctx;
	काष्ठा idxd_wq *wq = idxd_cdev->wq;

	cdev_ctx = &ictx[wq->idxd->data->type];
	ida_simple_हटाओ(&cdev_ctx->minor_ida, idxd_cdev->minor);
	kमुक्त(idxd_cdev);
पूर्ण

अटल काष्ठा device_type idxd_cdev_device_type = अणु
	.name = "idxd_cdev",
	.release = idxd_cdev_dev_release,
पूर्ण;

अटल अंतरभूत काष्ठा idxd_cdev *inode_idxd_cdev(काष्ठा inode *inode)
अणु
	काष्ठा cdev *cdev = inode->i_cdev;

	वापस container_of(cdev, काष्ठा idxd_cdev, cdev);
पूर्ण

अटल अंतरभूत काष्ठा idxd_wq *inode_wq(काष्ठा inode *inode)
अणु
	काष्ठा idxd_cdev *idxd_cdev = inode_idxd_cdev(inode);

	वापस idxd_cdev->wq;
पूर्ण

अटल पूर्णांक idxd_cdev_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा idxd_user_context *ctx;
	काष्ठा idxd_device *idxd;
	काष्ठा idxd_wq *wq;
	काष्ठा device *dev;
	पूर्णांक rc = 0;
	काष्ठा iommu_sva *sva;
	अचिन्हित पूर्णांक pasid;

	wq = inode_wq(inode);
	idxd = wq->idxd;
	dev = &idxd->pdev->dev;

	dev_dbg(dev, "%s called: %d\n", __func__, idxd_wq_refcount(wq));

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	mutex_lock(&wq->wq_lock);

	अगर (idxd_wq_refcount(wq) > 0 && wq_dedicated(wq)) अणु
		rc = -EBUSY;
		जाओ failed;
	पूर्ण

	ctx->wq = wq;
	filp->निजी_data = ctx;

	अगर (device_pasid_enabled(idxd)) अणु
		sva = iommu_sva_bind_device(dev, current->mm, शून्य);
		अगर (IS_ERR(sva)) अणु
			rc = PTR_ERR(sva);
			dev_err(dev, "pasid allocation failed: %d\n", rc);
			जाओ failed;
		पूर्ण

		pasid = iommu_sva_get_pasid(sva);
		अगर (pasid == IOMMU_PASID_INVALID) अणु
			iommu_sva_unbind_device(sva);
			rc = -EINVAL;
			जाओ failed;
		पूर्ण

		ctx->sva = sva;
		ctx->pasid = pasid;

		अगर (wq_dedicated(wq)) अणु
			rc = idxd_wq_set_pasid(wq, pasid);
			अगर (rc < 0) अणु
				iommu_sva_unbind_device(sva);
				dev_err(dev, "wq set pasid failed: %d\n", rc);
				जाओ failed;
			पूर्ण
		पूर्ण
	पूर्ण

	idxd_wq_get(wq);
	mutex_unlock(&wq->wq_lock);
	वापस 0;

 failed:
	mutex_unlock(&wq->wq_lock);
	kमुक्त(ctx);
	वापस rc;
पूर्ण

अटल पूर्णांक idxd_cdev_release(काष्ठा inode *node, काष्ठा file *filep)
अणु
	काष्ठा idxd_user_context *ctx = filep->निजी_data;
	काष्ठा idxd_wq *wq = ctx->wq;
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा device *dev = &idxd->pdev->dev;
	पूर्णांक rc;

	dev_dbg(dev, "%s called\n", __func__);
	filep->निजी_data = शून्य;

	/* Wait क्रम in-flight operations to complete. */
	अगर (wq_shared(wq)) अणु
		idxd_device_drain_pasid(idxd, ctx->pasid);
	पूर्ण अन्यथा अणु
		अगर (device_pasid_enabled(idxd)) अणु
			/* The wq disable in the disable pasid function will drain the wq */
			rc = idxd_wq_disable_pasid(wq);
			अगर (rc < 0)
				dev_err(dev, "wq disable pasid failed.\n");
		पूर्ण अन्यथा अणु
			idxd_wq_drain(wq);
		पूर्ण
	पूर्ण

	अगर (ctx->sva)
		iommu_sva_unbind_device(ctx->sva);
	kमुक्त(ctx);
	mutex_lock(&wq->wq_lock);
	idxd_wq_put(wq);
	mutex_unlock(&wq->wq_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक check_vma(काष्ठा idxd_wq *wq, काष्ठा vm_area_काष्ठा *vma,
		     स्थिर अक्षर *func)
अणु
	काष्ठा device *dev = &wq->idxd->pdev->dev;

	अगर ((vma->vm_end - vma->vm_start) > PAGE_SIZE) अणु
		dev_info_ratelimited(dev,
				     "%s: %s: mapping too large: %lu\n",
				     current->comm, func,
				     vma->vm_end - vma->vm_start);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idxd_cdev_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा idxd_user_context *ctx = filp->निजी_data;
	काष्ठा idxd_wq *wq = ctx->wq;
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा pci_dev *pdev = idxd->pdev;
	phys_addr_t base = pci_resource_start(pdev, IDXD_WQ_BAR);
	अचिन्हित दीर्घ pfn;
	पूर्णांक rc;

	dev_dbg(&pdev->dev, "%s called\n", __func__);
	rc = check_vma(wq, vma, __func__);
	अगर (rc < 0)
		वापस rc;

	vma->vm_flags |= VM_DONTCOPY;
	pfn = (base + idxd_get_wq_portal_full_offset(wq->id,
				IDXD_PORTAL_LIMITED)) >> PAGE_SHIFT;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	vma->vm_निजी_data = ctx;

	वापस io_remap_pfn_range(vma, vma->vm_start, pfn, PAGE_SIZE,
			vma->vm_page_prot);
पूर्ण

अटल __poll_t idxd_cdev_poll(काष्ठा file *filp,
			       काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा idxd_user_context *ctx = filp->निजी_data;
	काष्ठा idxd_wq *wq = ctx->wq;
	काष्ठा idxd_device *idxd = wq->idxd;
	अचिन्हित दीर्घ flags;
	__poll_t out = 0;

	poll_रुको(filp, &wq->err_queue, रुको);
	spin_lock_irqsave(&idxd->dev_lock, flags);
	अगर (idxd->sw_err.valid)
		out = EPOLLIN | EPOLLRDNORM;
	spin_unlock_irqrestore(&idxd->dev_lock, flags);

	वापस out;
पूर्ण

अटल स्थिर काष्ठा file_operations idxd_cdev_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = idxd_cdev_खोलो,
	.release = idxd_cdev_release,
	.mmap = idxd_cdev_mmap,
	.poll = idxd_cdev_poll,
पूर्ण;

पूर्णांक idxd_cdev_get_major(काष्ठा idxd_device *idxd)
अणु
	वापस MAJOR(ictx[idxd->data->type].devt);
पूर्ण

पूर्णांक idxd_wq_add_cdev(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_device *idxd = wq->idxd;
	काष्ठा idxd_cdev *idxd_cdev;
	काष्ठा cdev *cdev;
	काष्ठा device *dev;
	काष्ठा idxd_cdev_context *cdev_ctx;
	पूर्णांक rc, minor;

	idxd_cdev = kzalloc(माप(*idxd_cdev), GFP_KERNEL);
	अगर (!idxd_cdev)
		वापस -ENOMEM;

	idxd_cdev->wq = wq;
	cdev = &idxd_cdev->cdev;
	dev = &idxd_cdev->dev;
	cdev_ctx = &ictx[wq->idxd->data->type];
	minor = ida_simple_get(&cdev_ctx->minor_ida, 0, MINORMASK, GFP_KERNEL);
	अगर (minor < 0) अणु
		kमुक्त(idxd_cdev);
		वापस minor;
	पूर्ण
	idxd_cdev->minor = minor;

	device_initialize(dev);
	dev->parent = &wq->conf_dev;
	dev->bus = &dsa_bus_type;
	dev->type = &idxd_cdev_device_type;
	dev->devt = MKDEV(MAJOR(cdev_ctx->devt), minor);

	rc = dev_set_name(dev, "%s/wq%u.%u", idxd->data->name_prefix, idxd->id, wq->id);
	अगर (rc < 0)
		जाओ err;

	wq->idxd_cdev = idxd_cdev;
	cdev_init(cdev, &idxd_cdev_fops);
	rc = cdev_device_add(cdev, dev);
	अगर (rc) अणु
		dev_dbg(&wq->idxd->pdev->dev, "cdev_add failed: %d\n", rc);
		जाओ err;
	पूर्ण

	वापस 0;

 err:
	put_device(dev);
	wq->idxd_cdev = शून्य;
	वापस rc;
पूर्ण

व्योम idxd_wq_del_cdev(काष्ठा idxd_wq *wq)
अणु
	काष्ठा idxd_cdev *idxd_cdev;
	काष्ठा idxd_cdev_context *cdev_ctx;

	cdev_ctx = &ictx[wq->idxd->data->type];
	idxd_cdev = wq->idxd_cdev;
	wq->idxd_cdev = शून्य;
	cdev_device_del(&idxd_cdev->cdev, &idxd_cdev->dev);
	put_device(&idxd_cdev->dev);
पूर्ण

पूर्णांक idxd_cdev_रेजिस्टर(व्योम)
अणु
	पूर्णांक rc, i;

	क्रम (i = 0; i < IDXD_TYPE_MAX; i++) अणु
		ida_init(&ictx[i].minor_ida);
		rc = alloc_chrdev_region(&ictx[i].devt, 0, MINORMASK,
					 ictx[i].name);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम idxd_cdev_हटाओ(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IDXD_TYPE_MAX; i++) अणु
		unरेजिस्टर_chrdev_region(ictx[i].devt, MINORMASK);
		ida_destroy(&ictx[i].minor_ida);
	पूर्ण
पूर्ण
