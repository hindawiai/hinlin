<शैली गुरु>
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2013 Cisco Systems.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/iommu.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/list.h>
#समावेश <linux/pci.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "usnic_log.h"
#समावेश "usnic_uiom.h"
#समावेश "usnic_uiom_interval_tree.h"

#घोषणा USNIC_UIOM_PAGE_CHUNK						\
	((PAGE_SIZE - दुरत्व(काष्ठा usnic_uiom_chunk, page_list))	/\
	((व्योम *) &((काष्ठा usnic_uiom_chunk *) 0)->page_list[1] -	\
	(व्योम *) &((काष्ठा usnic_uiom_chunk *) 0)->page_list[0]))

अटल पूर्णांक usnic_uiom_dma_fault(काष्ठा iommu_करोमुख्य *करोमुख्य,
				काष्ठा device *dev,
				अचिन्हित दीर्घ iova, पूर्णांक flags,
				व्योम *token)
अणु
	usnic_err("Device %s iommu fault domain 0x%pK va 0x%lx flags 0x%x\n",
		dev_name(dev),
		करोमुख्य, iova, flags);
	वापस -ENOSYS;
पूर्ण

अटल व्योम usnic_uiom_put_pages(काष्ठा list_head *chunk_list, पूर्णांक dirty)
अणु
	काष्ठा usnic_uiom_chunk *chunk, *पंचांगp;
	काष्ठा page *page;
	काष्ठा scatterlist *sg;
	पूर्णांक i;
	dma_addr_t pa;

	list_क्रम_each_entry_safe(chunk, पंचांगp, chunk_list, list) अणु
		क्रम_each_sg(chunk->page_list, sg, chunk->nents, i) अणु
			page = sg_page(sg);
			pa = sg_phys(sg);
			unpin_user_pages_dirty_lock(&page, 1, dirty);
			usnic_dbg("pa: %pa\n", &pa);
		पूर्ण
		kमुक्त(chunk);
	पूर्ण
पूर्ण

अटल पूर्णांक usnic_uiom_get_pages(अचिन्हित दीर्घ addr, माप_प्रकार size, पूर्णांक writable,
				पूर्णांक dmasync, काष्ठा usnic_uiom_reg *uiomr)
अणु
	काष्ठा list_head *chunk_list = &uiomr->chunk_list;
	काष्ठा page **page_list;
	काष्ठा scatterlist *sg;
	काष्ठा usnic_uiom_chunk *chunk;
	अचिन्हित दीर्घ locked;
	अचिन्हित दीर्घ lock_limit;
	अचिन्हित दीर्घ cur_base;
	अचिन्हित दीर्घ npages;
	पूर्णांक ret;
	पूर्णांक off;
	पूर्णांक i;
	पूर्णांक flags;
	dma_addr_t pa;
	अचिन्हित पूर्णांक gup_flags;
	काष्ठा mm_काष्ठा *mm;

	/*
	 * If the combination of the addr and size requested क्रम this memory
	 * region causes an पूर्णांकeger overflow, वापस error.
	 */
	अगर (((addr + size) < addr) || PAGE_ALIGN(addr + size) < (addr + size))
		वापस -EINVAL;

	अगर (!size)
		वापस -EINVAL;

	अगर (!can_करो_mlock())
		वापस -EPERM;

	INIT_LIST_HEAD(chunk_list);

	page_list = (काष्ठा page **) __get_मुक्त_page(GFP_KERNEL);
	अगर (!page_list)
		वापस -ENOMEM;

	npages = PAGE_ALIGN(size + (addr & ~PAGE_MASK)) >> PAGE_SHIFT;

	uiomr->owning_mm = mm = current->mm;
	mmap_पढ़ो_lock(mm);

	locked = atomic64_add_वापस(npages, &current->mm->pinned_vm);
	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	अगर ((locked > lock_limit) && !capable(CAP_IPC_LOCK)) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	flags = IOMMU_READ | IOMMU_CACHE;
	flags |= (writable) ? IOMMU_WRITE : 0;
	gup_flags = FOLL_WRITE;
	gup_flags |= (writable) ? 0 : FOLL_FORCE;
	cur_base = addr & PAGE_MASK;
	ret = 0;

	जबतक (npages) अणु
		ret = pin_user_pages(cur_base,
				     min_t(अचिन्हित दीर्घ, npages,
				     PAGE_SIZE / माप(काष्ठा page *)),
				     gup_flags | FOLL_LONGTERM,
				     page_list, शून्य);

		अगर (ret < 0)
			जाओ out;

		npages -= ret;
		off = 0;

		जबतक (ret) अणु
			chunk = kदो_स्मृति(काष्ठा_size(chunk, page_list,
					min_t(पूर्णांक, ret, USNIC_UIOM_PAGE_CHUNK)),
					GFP_KERNEL);
			अगर (!chunk) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण

			chunk->nents = min_t(पूर्णांक, ret, USNIC_UIOM_PAGE_CHUNK);
			sg_init_table(chunk->page_list, chunk->nents);
			क्रम_each_sg(chunk->page_list, sg, chunk->nents, i) अणु
				sg_set_page(sg, page_list[i + off],
						PAGE_SIZE, 0);
				pa = sg_phys(sg);
				usnic_dbg("va: 0x%lx pa: %pa\n",
						cur_base + i*PAGE_SIZE, &pa);
			पूर्ण
			cur_base += chunk->nents * PAGE_SIZE;
			ret -= chunk->nents;
			off += chunk->nents;
			list_add_tail(&chunk->list, chunk_list);
		पूर्ण

		ret = 0;
	पूर्ण

out:
	अगर (ret < 0) अणु
		usnic_uiom_put_pages(chunk_list, 0);
		atomic64_sub(npages, &current->mm->pinned_vm);
	पूर्ण अन्यथा
		mmgrab(uiomr->owning_mm);

	mmap_पढ़ो_unlock(mm);
	मुक्त_page((अचिन्हित दीर्घ) page_list);
	वापस ret;
पूर्ण

अटल व्योम usnic_uiom_unmap_sorted_पूर्णांकervals(काष्ठा list_head *पूर्णांकervals,
						काष्ठा usnic_uiom_pd *pd)
अणु
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval, *पंचांगp;
	दीर्घ अचिन्हित va, size;

	list_क्रम_each_entry_safe(पूर्णांकerval, पंचांगp, पूर्णांकervals, link) अणु
		va = पूर्णांकerval->start << PAGE_SHIFT;
		size = ((पूर्णांकerval->last - पूर्णांकerval->start) + 1) << PAGE_SHIFT;
		जबतक (size > 0) अणु
			/* Workaround क्रम RH 970401 */
			usnic_dbg("va 0x%lx size 0x%lx", va, PAGE_SIZE);
			iommu_unmap(pd->करोमुख्य, va, PAGE_SIZE);
			va += PAGE_SIZE;
			size -= PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __usnic_uiom_reg_release(काष्ठा usnic_uiom_pd *pd,
					काष्ठा usnic_uiom_reg *uiomr,
					पूर्णांक dirty)
अणु
	पूर्णांक npages;
	अचिन्हित दीर्घ vpn_start, vpn_last;
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval, *पंचांगp;
	पूर्णांक writable = 0;
	LIST_HEAD(rm_पूर्णांकervals);

	npages = PAGE_ALIGN(uiomr->length + uiomr->offset) >> PAGE_SHIFT;
	vpn_start = (uiomr->va & PAGE_MASK) >> PAGE_SHIFT;
	vpn_last = vpn_start + npages - 1;

	spin_lock(&pd->lock);
	usnic_uiom_हटाओ_पूर्णांकerval(&pd->root, vpn_start,
					vpn_last, &rm_पूर्णांकervals);
	usnic_uiom_unmap_sorted_पूर्णांकervals(&rm_पूर्णांकervals, pd);

	list_क्रम_each_entry_safe(पूर्णांकerval, पंचांगp, &rm_पूर्णांकervals, link) अणु
		अगर (पूर्णांकerval->flags & IOMMU_WRITE)
			writable = 1;
		list_del(&पूर्णांकerval->link);
		kमुक्त(पूर्णांकerval);
	पूर्ण

	usnic_uiom_put_pages(&uiomr->chunk_list, dirty & writable);
	spin_unlock(&pd->lock);
पूर्ण

अटल पूर्णांक usnic_uiom_map_sorted_पूर्णांकervals(काष्ठा list_head *पूर्णांकervals,
						काष्ठा usnic_uiom_reg *uiomr)
अणु
	पूर्णांक i, err;
	माप_प्रकार size;
	काष्ठा usnic_uiom_chunk *chunk;
	काष्ठा usnic_uiom_पूर्णांकerval_node *पूर्णांकerval_node;
	dma_addr_t pa;
	dma_addr_t pa_start = 0;
	dma_addr_t pa_end = 0;
	दीर्घ पूर्णांक बहु_शुरू = -EINVAL;
	काष्ठा usnic_uiom_pd *pd = uiomr->pd;
	दीर्घ पूर्णांक va = uiomr->va & PAGE_MASK;
	पूर्णांक flags = IOMMU_READ | IOMMU_CACHE;

	flags |= (uiomr->writable) ? IOMMU_WRITE : 0;
	chunk = list_first_entry(&uiomr->chunk_list, काष्ठा usnic_uiom_chunk,
									list);
	list_क्रम_each_entry(पूर्णांकerval_node, पूर्णांकervals, link) अणु
iter_chunk:
		क्रम (i = 0; i < chunk->nents; i++, va += PAGE_SIZE) अणु
			pa = sg_phys(&chunk->page_list[i]);
			अगर ((va >> PAGE_SHIFT) < पूर्णांकerval_node->start)
				जारी;

			अगर ((va >> PAGE_SHIFT) == पूर्णांकerval_node->start) अणु
				/* First page of the पूर्णांकerval */
				बहु_शुरू = va;
				pa_start = pa;
				pa_end = pa;
			पूर्ण

			WARN_ON(बहु_शुरू == -EINVAL);

			अगर ((pa_end + PAGE_SIZE != pa) &&
					(pa != pa_start)) अणु
				/* PAs are not contiguous */
				size = pa_end - pa_start + PAGE_SIZE;
				usnic_dbg("va 0x%lx pa %pa size 0x%zx flags 0x%x",
					बहु_शुरू, &pa_start, size, flags);
				err = iommu_map(pd->करोमुख्य, बहु_शुरू, pa_start,
							size, flags);
				अगर (err) अणु
					usnic_err("Failed to map va 0x%lx pa %pa size 0x%zx with err %d\n",
						बहु_शुरू, &pa_start, size, err);
					जाओ err_out;
				पूर्ण
				बहु_शुरू = va;
				pa_start = pa;
				pa_end = pa;
			पूर्ण

			अगर ((va >> PAGE_SHIFT) == पूर्णांकerval_node->last) अणु
				/* Last page of the पूर्णांकerval */
				size = pa - pa_start + PAGE_SIZE;
				usnic_dbg("va 0x%lx pa %pa size 0x%zx flags 0x%x\n",
					बहु_शुरू, &pa_start, size, flags);
				err = iommu_map(pd->करोमुख्य, बहु_शुरू, pa_start,
						size, flags);
				अगर (err) अणु
					usnic_err("Failed to map va 0x%lx pa %pa size 0x%zx with err %d\n",
						बहु_शुरू, &pa_start, size, err);
					जाओ err_out;
				पूर्ण
				अवरोध;
			पूर्ण

			अगर (pa != pa_start)
				pa_end += PAGE_SIZE;
		पूर्ण

		अगर (i == chunk->nents) अणु
			/*
			 * Hit last entry of the chunk,
			 * hence advance to next chunk
			 */
			chunk = list_first_entry(&chunk->list,
							काष्ठा usnic_uiom_chunk,
							list);
			जाओ iter_chunk;
		पूर्ण
	पूर्ण

	वापस 0;

err_out:
	usnic_uiom_unmap_sorted_पूर्णांकervals(पूर्णांकervals, pd);
	वापस err;
पूर्ण

काष्ठा usnic_uiom_reg *usnic_uiom_reg_get(काष्ठा usnic_uiom_pd *pd,
						अचिन्हित दीर्घ addr, माप_प्रकार size,
						पूर्णांक writable, पूर्णांक dmasync)
अणु
	काष्ठा usnic_uiom_reg *uiomr;
	अचिन्हित दीर्घ va_base, vpn_start, vpn_last;
	अचिन्हित दीर्घ npages;
	पूर्णांक offset, err;
	LIST_HEAD(sorted_dअगरf_पूर्णांकervals);

	/*
	 * Intel IOMMU map throws an error अगर a translation entry is
	 * changed from पढ़ो to ग_लिखो.  This module may not unmap
	 * and then remap the entry after fixing the permission
	 * b/c this खोलो up a small winकरोws where hw DMA may page fault
	 * Hence, make all entries to be writable.
	 */
	writable = 1;

	va_base = addr & PAGE_MASK;
	offset = addr & ~PAGE_MASK;
	npages = PAGE_ALIGN(size + offset) >> PAGE_SHIFT;
	vpn_start = (addr & PAGE_MASK) >> PAGE_SHIFT;
	vpn_last = vpn_start + npages - 1;

	uiomr = kदो_स्मृति(माप(*uiomr), GFP_KERNEL);
	अगर (!uiomr)
		वापस ERR_PTR(-ENOMEM);

	uiomr->va = va_base;
	uiomr->offset = offset;
	uiomr->length = size;
	uiomr->writable = writable;
	uiomr->pd = pd;

	err = usnic_uiom_get_pages(addr, size, writable, dmasync,
				   uiomr);
	अगर (err) अणु
		usnic_err("Failed get_pages vpn [0x%lx,0x%lx] err %d\n",
				vpn_start, vpn_last, err);
		जाओ out_मुक्त_uiomr;
	पूर्ण

	spin_lock(&pd->lock);
	err = usnic_uiom_get_पूर्णांकervals_dअगरf(vpn_start, vpn_last,
						(writable) ? IOMMU_WRITE : 0,
						IOMMU_WRITE,
						&pd->root,
						&sorted_dअगरf_पूर्णांकervals);
	अगर (err) अणु
		usnic_err("Failed disjoint interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		जाओ out_put_pages;
	पूर्ण

	err = usnic_uiom_map_sorted_पूर्णांकervals(&sorted_dअगरf_पूर्णांकervals, uiomr);
	अगर (err) अणु
		usnic_err("Failed map interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		जाओ out_put_पूर्णांकervals;

	पूर्ण

	err = usnic_uiom_insert_पूर्णांकerval(&pd->root, vpn_start, vpn_last,
					(writable) ? IOMMU_WRITE : 0);
	अगर (err) अणु
		usnic_err("Failed insert interval vpn [0x%lx,0x%lx] err %d\n",
						vpn_start, vpn_last, err);
		जाओ out_unmap_पूर्णांकervals;
	पूर्ण

	usnic_uiom_put_पूर्णांकerval_set(&sorted_dअगरf_पूर्णांकervals);
	spin_unlock(&pd->lock);

	वापस uiomr;

out_unmap_पूर्णांकervals:
	usnic_uiom_unmap_sorted_पूर्णांकervals(&sorted_dअगरf_पूर्णांकervals, pd);
out_put_पूर्णांकervals:
	usnic_uiom_put_पूर्णांकerval_set(&sorted_dअगरf_पूर्णांकervals);
out_put_pages:
	usnic_uiom_put_pages(&uiomr->chunk_list, 0);
	spin_unlock(&pd->lock);
	mmdrop(uiomr->owning_mm);
out_मुक्त_uiomr:
	kमुक्त(uiomr);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम __usnic_uiom_release_tail(काष्ठा usnic_uiom_reg *uiomr)
अणु
	mmdrop(uiomr->owning_mm);
	kमुक्त(uiomr);
पूर्ण

अटल अंतरभूत माप_प्रकार usnic_uiom_num_pages(काष्ठा usnic_uiom_reg *uiomr)
अणु
	वापस PAGE_ALIGN(uiomr->length + uiomr->offset) >> PAGE_SHIFT;
पूर्ण

व्योम usnic_uiom_reg_release(काष्ठा usnic_uiom_reg *uiomr)
अणु
	__usnic_uiom_reg_release(uiomr->pd, uiomr, 1);

	atomic64_sub(usnic_uiom_num_pages(uiomr), &uiomr->owning_mm->pinned_vm);
	__usnic_uiom_release_tail(uiomr);
पूर्ण

काष्ठा usnic_uiom_pd *usnic_uiom_alloc_pd(व्योम)
अणु
	काष्ठा usnic_uiom_pd *pd;
	व्योम *करोमुख्य;

	pd = kzalloc(माप(*pd), GFP_KERNEL);
	अगर (!pd)
		वापस ERR_PTR(-ENOMEM);

	pd->करोमुख्य = करोमुख्य = iommu_करोमुख्य_alloc(&pci_bus_type);
	अगर (!करोमुख्य) अणु
		usnic_err("Failed to allocate IOMMU domain");
		kमुक्त(pd);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	iommu_set_fault_handler(pd->करोमुख्य, usnic_uiom_dma_fault, शून्य);

	spin_lock_init(&pd->lock);
	INIT_LIST_HEAD(&pd->devs);

	वापस pd;
पूर्ण

व्योम usnic_uiom_dealloc_pd(काष्ठा usnic_uiom_pd *pd)
अणु
	iommu_करोमुख्य_मुक्त(pd->करोमुख्य);
	kमुक्त(pd);
पूर्ण

पूर्णांक usnic_uiom_attach_dev_to_pd(काष्ठा usnic_uiom_pd *pd, काष्ठा device *dev)
अणु
	काष्ठा usnic_uiom_dev *uiom_dev;
	पूर्णांक err;

	uiom_dev = kzalloc(माप(*uiom_dev), GFP_ATOMIC);
	अगर (!uiom_dev)
		वापस -ENOMEM;
	uiom_dev->dev = dev;

	err = iommu_attach_device(pd->करोमुख्य, dev);
	अगर (err)
		जाओ out_मुक्त_dev;

	अगर (!iommu_capable(dev->bus, IOMMU_CAP_CACHE_COHERENCY)) अणु
		usnic_err("IOMMU of %s does not support cache coherency\n",
				dev_name(dev));
		err = -EINVAL;
		जाओ out_detach_device;
	पूर्ण

	spin_lock(&pd->lock);
	list_add_tail(&uiom_dev->link, &pd->devs);
	pd->dev_cnt++;
	spin_unlock(&pd->lock);

	वापस 0;

out_detach_device:
	iommu_detach_device(pd->करोमुख्य, dev);
out_मुक्त_dev:
	kमुक्त(uiom_dev);
	वापस err;
पूर्ण

व्योम usnic_uiom_detach_dev_from_pd(काष्ठा usnic_uiom_pd *pd, काष्ठा device *dev)
अणु
	काष्ठा usnic_uiom_dev *uiom_dev;
	पूर्णांक found = 0;

	spin_lock(&pd->lock);
	list_क्रम_each_entry(uiom_dev, &pd->devs, link) अणु
		अगर (uiom_dev->dev == dev) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		usnic_err("Unable to free dev %s - not found\n",
				dev_name(dev));
		spin_unlock(&pd->lock);
		वापस;
	पूर्ण

	list_del(&uiom_dev->link);
	pd->dev_cnt--;
	spin_unlock(&pd->lock);

	वापस iommu_detach_device(pd->करोमुख्य, dev);
पूर्ण

काष्ठा device **usnic_uiom_get_dev_list(काष्ठा usnic_uiom_pd *pd)
अणु
	काष्ठा usnic_uiom_dev *uiom_dev;
	काष्ठा device **devs;
	पूर्णांक i = 0;

	spin_lock(&pd->lock);
	devs = kसुस्मृति(pd->dev_cnt + 1, माप(*devs), GFP_ATOMIC);
	अगर (!devs) अणु
		devs = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	list_क्रम_each_entry(uiom_dev, &pd->devs, link) अणु
		devs[i++] = uiom_dev->dev;
	पूर्ण
out:
	spin_unlock(&pd->lock);
	वापस devs;
पूर्ण

व्योम usnic_uiom_मुक्त_dev_list(काष्ठा device **devs)
अणु
	kमुक्त(devs);
पूर्ण

पूर्णांक usnic_uiom_init(अक्षर *drv_name)
अणु
	अगर (!iommu_present(&pci_bus_type)) अणु
		usnic_err("IOMMU required but not present or enabled.  USNIC QPs will not function w/o enabling IOMMU\n");
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण
