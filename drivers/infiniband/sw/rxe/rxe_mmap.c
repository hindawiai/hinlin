<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "rxe.h"
#समावेश "rxe_loc.h"
#समावेश "rxe_queue.h"

व्योम rxe_mmap_release(काष्ठा kref *ref)
अणु
	काष्ठा rxe_mmap_info *ip = container_of(ref,
					काष्ठा rxe_mmap_info, ref);
	काष्ठा rxe_dev *rxe = to_rdev(ip->context->device);

	spin_lock_bh(&rxe->pending_lock);

	अगर (!list_empty(&ip->pending_mmaps))
		list_del(&ip->pending_mmaps);

	spin_unlock_bh(&rxe->pending_lock);

	vमुक्त(ip->obj);		/* buf */
	kमुक्त(ip);
पूर्ण

/*
 * खोलो and बंद keep track of how many बार the memory region is mapped,
 * to aव्योम releasing it.
 */
अटल व्योम rxe_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rxe_mmap_info *ip = vma->vm_निजी_data;

	kref_get(&ip->ref);
पूर्ण

अटल व्योम rxe_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rxe_mmap_info *ip = vma->vm_निजी_data;

	kref_put(&ip->ref, rxe_mmap_release);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा rxe_vm_ops = अणु
	.खोलो = rxe_vma_खोलो,
	.बंद = rxe_vma_बंद,
पूर्ण;

/**
 * rxe_mmap - create a new mmap region
 * @context: the IB user context of the process making the mmap() call
 * @vma: the VMA to be initialized
 * Return zero अगर the mmap is OK. Otherwise, वापस an त्रुटि_सं.
 */
पूर्णांक rxe_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rxe_dev *rxe = to_rdev(context->device);
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	काष्ठा rxe_mmap_info *ip, *pp;
	पूर्णांक ret;

	/*
	 * Search the device's list of objects रुकोing क्रम a mmap call.
	 * Normally, this list is very लघु since a call to create a
	 * CQ, QP, or SRQ is soon followed by a call to mmap().
	 */
	spin_lock_bh(&rxe->pending_lock);
	list_क्रम_each_entry_safe(ip, pp, &rxe->pending_mmaps, pending_mmaps) अणु
		अगर (context != ip->context || (__u64)offset != ip->info.offset)
			जारी;

		/* Don't allow a mmap larger than the object. */
		अगर (size > ip->info.size) अणु
			pr_err("mmap region is larger than the object!\n");
			spin_unlock_bh(&rxe->pending_lock);
			ret = -EINVAL;
			जाओ करोne;
		पूर्ण

		जाओ found_it;
	पूर्ण
	pr_warn("unable to find pending mmap info\n");
	spin_unlock_bh(&rxe->pending_lock);
	ret = -EINVAL;
	जाओ करोne;

found_it:
	list_del_init(&ip->pending_mmaps);
	spin_unlock_bh(&rxe->pending_lock);

	ret = remap_vदो_स्मृति_range(vma, ip->obj, 0);
	अगर (ret) अणु
		pr_err("err %d from remap_vmalloc_range\n", ret);
		जाओ करोne;
	पूर्ण

	vma->vm_ops = &rxe_vm_ops;
	vma->vm_निजी_data = ip;
	rxe_vma_खोलो(vma);
करोne:
	वापस ret;
पूर्ण

/*
 * Allocate inक्रमmation क्रम rxe_mmap
 */
काष्ठा rxe_mmap_info *rxe_create_mmap_info(काष्ठा rxe_dev *rxe, u32 size,
					   काष्ठा ib_udata *udata, व्योम *obj)
अणु
	काष्ठा rxe_mmap_info *ip;

	अगर (!udata)
		वापस ERR_PTR(-EINVAL);

	ip = kदो_स्मृति(माप(*ip), GFP_KERNEL);
	अगर (!ip)
		वापस ERR_PTR(-ENOMEM);

	size = PAGE_ALIGN(size);

	spin_lock_bh(&rxe->mmap_offset_lock);

	अगर (rxe->mmap_offset == 0)
		rxe->mmap_offset = ALIGN(PAGE_SIZE, SHMLBA);

	ip->info.offset = rxe->mmap_offset;
	rxe->mmap_offset += ALIGN(size, SHMLBA);

	spin_unlock_bh(&rxe->mmap_offset_lock);

	INIT_LIST_HEAD(&ip->pending_mmaps);
	ip->info.size = size;
	ip->context =
		container_of(udata, काष्ठा uverbs_attr_bundle, driver_udata)
			->context;
	ip->obj = obj;
	kref_init(&ip->ref);

	वापस ip;
पूर्ण
