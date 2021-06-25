<शैली गुरु>
/*
 * Copyright(c) 2016 Intel Corporation.
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

#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <rdma/uverbs_ioctl.h>
#समावेश "mmap.h"

/**
 * rvt_mmap_init - init link list and lock क्रम mem map
 * @rdi: rvt dev काष्ठा
 */
व्योम rvt_mmap_init(काष्ठा rvt_dev_info *rdi)
अणु
	INIT_LIST_HEAD(&rdi->pending_mmaps);
	spin_lock_init(&rdi->pending_lock);
	rdi->mmap_offset = PAGE_SIZE;
	spin_lock_init(&rdi->mmap_offset_lock);
पूर्ण

/**
 * rvt_release_mmap_info - मुक्त mmap info काष्ठाure
 * @ref: a poपूर्णांकer to the kref within काष्ठा rvt_mmap_info
 */
व्योम rvt_release_mmap_info(काष्ठा kref *ref)
अणु
	काष्ठा rvt_mmap_info *ip =
		container_of(ref, काष्ठा rvt_mmap_info, ref);
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ip->context->device);

	spin_lock_irq(&rdi->pending_lock);
	list_del(&ip->pending_mmaps);
	spin_unlock_irq(&rdi->pending_lock);

	vमुक्त(ip->obj);
	kमुक्त(ip);
पूर्ण

अटल व्योम rvt_vma_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rvt_mmap_info *ip = vma->vm_निजी_data;

	kref_get(&ip->ref);
पूर्ण

अटल व्योम rvt_vma_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rvt_mmap_info *ip = vma->vm_निजी_data;

	kref_put(&ip->ref, rvt_release_mmap_info);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा rvt_vm_ops = अणु
	.खोलो = rvt_vma_खोलो,
	.बंद = rvt_vma_बंद,
पूर्ण;

/**
 * rvt_mmap - create a new mmap region
 * @context: the IB user context of the process making the mmap() call
 * @vma: the VMA to be initialized
 *
 * Return: zero अगर the mmap is OK. Otherwise, वापस an त्रुटि_सं.
 */
पूर्णांक rvt_mmap(काष्ठा ib_ucontext *context, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(context->device);
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	काष्ठा rvt_mmap_info *ip, *pp;
	पूर्णांक ret = -EINVAL;

	/*
	 * Search the device's list of objects रुकोing क्रम a mmap call.
	 * Normally, this list is very लघु since a call to create a
	 * CQ, QP, or SRQ is soon followed by a call to mmap().
	 */
	spin_lock_irq(&rdi->pending_lock);
	list_क्रम_each_entry_safe(ip, pp, &rdi->pending_mmaps,
				 pending_mmaps) अणु
		/* Only the creator is allowed to mmap the object */
		अगर (context != ip->context || (__u64)offset != ip->offset)
			जारी;
		/* Don't allow a mmap larger than the object. */
		अगर (size > ip->size)
			अवरोध;

		list_del_init(&ip->pending_mmaps);
		spin_unlock_irq(&rdi->pending_lock);

		ret = remap_vदो_स्मृति_range(vma, ip->obj, 0);
		अगर (ret)
			जाओ करोne;
		vma->vm_ops = &rvt_vm_ops;
		vma->vm_निजी_data = ip;
		rvt_vma_खोलो(vma);
		जाओ करोne;
	पूर्ण
	spin_unlock_irq(&rdi->pending_lock);
करोne:
	वापस ret;
पूर्ण

/**
 * rvt_create_mmap_info - allocate inक्रमmation क्रम hfi1_mmap
 * @rdi: rvt dev काष्ठा
 * @size: size in bytes to map
 * @udata: user data (must be valid!)
 * @obj: opaque poपूर्णांकer to a cq, wq etc
 *
 * Return: rvt_mmap काष्ठा on success, ERR_PTR on failure
 */
काष्ठा rvt_mmap_info *rvt_create_mmap_info(काष्ठा rvt_dev_info *rdi, u32 size,
					   काष्ठा ib_udata *udata, व्योम *obj)
अणु
	काष्ठा rvt_mmap_info *ip;

	अगर (!udata)
		वापस ERR_PTR(-EINVAL);

	ip = kदो_स्मृति_node(माप(*ip), GFP_KERNEL, rdi->dparms.node);
	अगर (!ip)
		वापस ERR_PTR(-ENOMEM);

	size = PAGE_ALIGN(size);

	spin_lock_irq(&rdi->mmap_offset_lock);
	अगर (rdi->mmap_offset == 0)
		rdi->mmap_offset = ALIGN(PAGE_SIZE, SHMLBA);
	ip->offset = rdi->mmap_offset;
	rdi->mmap_offset += ALIGN(size, SHMLBA);
	spin_unlock_irq(&rdi->mmap_offset_lock);

	INIT_LIST_HEAD(&ip->pending_mmaps);
	ip->size = size;
	ip->context =
		container_of(udata, काष्ठा uverbs_attr_bundle, driver_udata)
			->context;
	ip->obj = obj;
	kref_init(&ip->ref);

	वापस ip;
पूर्ण

/**
 * rvt_update_mmap_info - update a mem map
 * @rdi: rvt dev काष्ठा
 * @ip: mmap info poपूर्णांकer
 * @size: size to grow by
 * @obj: opaque poपूर्णांकer to cq, wq, etc.
 */
व्योम rvt_update_mmap_info(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_mmap_info *ip,
			  u32 size, व्योम *obj)
अणु
	size = PAGE_ALIGN(size);

	spin_lock_irq(&rdi->mmap_offset_lock);
	अगर (rdi->mmap_offset == 0)
		rdi->mmap_offset = PAGE_SIZE;
	ip->offset = rdi->mmap_offset;
	rdi->mmap_offset += size;
	spin_unlock_irq(&rdi->mmap_offset_lock);

	ip->size = size;
	ip->obj = obj;
पूर्ण
