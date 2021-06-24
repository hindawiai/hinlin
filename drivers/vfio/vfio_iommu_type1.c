<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VFIO: IOMMU DMA mapping support क्रम Type1 IOMMU
 *
 * Copyright (C) 2012 Red Hat, Inc.  All rights reserved.
 *     Author: Alex Williamson <alex.williamson@redhat.com>
 *
 * Derived from original vfio:
 * Copyright 2010 Cisco Systems, Inc.  All rights reserved.
 * Author: Tom Lyon, pugs@cisco.com
 *
 * We arbitrarily define a Type1 IOMMU as one matching the below code.
 * It could be called the x86 IOMMU as it's deचिन्हित क्रम AMD-Vi & Intel
 * VT-d, but that makes it harder to re-use as theoretically anyone
 * implementing a similar IOMMU could make use of this.  We expect the
 * IOMMU to support the IOMMU API and have few to no restrictions around
 * the IOVA range that can be mapped.  The Type1 IOMMU is currently
 * optimized क्रम relatively अटल mappings of a userspace process with
 * userspace pages pinned पूर्णांकo memory.  We also assume devices and IOMMU
 * करोमुख्यs are PCI based as the IOMMU API is still centered around a
 * device/bus पूर्णांकerface rather than a group पूर्णांकerface.
 */

#समावेश <linux/compat.h>
#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/iommu.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vfपन.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/mdev.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/dma-iommu.h>
#समावेश <linux/irqकरोमुख्य.h>

#घोषणा DRIVER_VERSION  "0.2"
#घोषणा DRIVER_AUTHOR   "Alex Williamson <alex.williamson@redhat.com>"
#घोषणा DRIVER_DESC     "Type1 IOMMU driver for VFIO"

अटल bool allow_unsafe_पूर्णांकerrupts;
module_param_named(allow_unsafe_पूर्णांकerrupts,
		   allow_unsafe_पूर्णांकerrupts, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(allow_unsafe_पूर्णांकerrupts,
		 "Enable VFIO IOMMU support for on platforms without interrupt remapping support.");

अटल bool disable_hugepages;
module_param_named(disable_hugepages,
		   disable_hugepages, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(disable_hugepages,
		 "Disable VFIO IOMMU support for IOMMU hugepages.");

अटल अचिन्हित पूर्णांक dma_entry_limit __पढ़ो_mostly = U16_MAX;
module_param_named(dma_entry_limit, dma_entry_limit, uपूर्णांक, 0644);
MODULE_PARM_DESC(dma_entry_limit,
		 "Maximum number of user DMA mappings per container (65535).");

काष्ठा vfio_iommu अणु
	काष्ठा list_head	करोमुख्य_list;
	काष्ठा list_head	ioबहु_सूची;
	काष्ठा vfio_करोमुख्य	*बाह्यal_करोमुख्य; /* करोमुख्य क्रम बाह्यal user */
	काष्ठा mutex		lock;
	काष्ठा rb_root		dma_list;
	काष्ठा blocking_notअगरier_head notअगरier;
	अचिन्हित पूर्णांक		dma_avail;
	अचिन्हित पूर्णांक		vaddr_invalid_count;
	uपूर्णांक64_t		pgsize_biपंचांगap;
	uपूर्णांक64_t		num_non_pinned_groups;
	रुको_queue_head_t	vaddr_रुको;
	bool			v2;
	bool			nesting;
	bool			dirty_page_tracking;
	bool			container_खोलो;
पूर्ण;

काष्ठा vfio_करोमुख्य अणु
	काष्ठा iommu_करोमुख्य	*करोमुख्य;
	काष्ठा list_head	next;
	काष्ठा list_head	group_list;
	पूर्णांक			prot;		/* IOMMU_CACHE */
	bool			fgsp;		/* Fine-grained super pages */
पूर्ण;

काष्ठा vfio_dma अणु
	काष्ठा rb_node		node;
	dma_addr_t		iova;		/* Device address */
	अचिन्हित दीर्घ		vaddr;		/* Process भव addr */
	माप_प्रकार			size;		/* Map size (bytes) */
	पूर्णांक			prot;		/* IOMMU_READ/WRITE */
	bool			iommu_mapped;
	bool			lock_cap;	/* capable(CAP_IPC_LOCK) */
	bool			vaddr_invalid;
	काष्ठा task_काष्ठा	*task;
	काष्ठा rb_root		pfn_list;	/* Ex-user pinned pfn list */
	अचिन्हित दीर्घ		*biपंचांगap;
पूर्ण;

काष्ठा vfio_batch अणु
	काष्ठा page		**pages;	/* क्रम pin_user_pages_remote */
	काष्ठा page		*fallback_page; /* अगर pages alloc fails */
	पूर्णांक			capacity;	/* length of pages array */
	पूर्णांक			size;		/* of batch currently */
	पूर्णांक			offset;		/* of next entry in pages */
पूर्ण;

काष्ठा vfio_group अणु
	काष्ठा iommu_group	*iommu_group;
	काष्ठा list_head	next;
	bool			mdev_group;	/* An mdev group */
	bool			pinned_page_dirty_scope;
पूर्ण;

काष्ठा vfio_iova अणु
	काष्ठा list_head	list;
	dma_addr_t		start;
	dma_addr_t		end;
पूर्ण;

/*
 * Guest RAM pinning working set or DMA target
 */
काष्ठा vfio_pfn अणु
	काष्ठा rb_node		node;
	dma_addr_t		iova;		/* Device address */
	अचिन्हित दीर्घ		pfn;		/* Host pfn */
	अचिन्हित पूर्णांक		ref_count;
पूर्ण;

काष्ठा vfio_regions अणु
	काष्ठा list_head list;
	dma_addr_t iova;
	phys_addr_t phys;
	माप_प्रकार len;
पूर्ण;

#घोषणा IS_IOMMU_CAP_DOMAIN_IN_CONTAINER(iommu)	\
					(!list_empty(&iommu->करोमुख्य_list))

#घोषणा सूचीTY_BITMAP_BYTES(n)	(ALIGN(n, BITS_PER_TYPE(u64)) / BITS_PER_BYTE)

/*
 * Input argument of number of bits to biपंचांगap_set() is अचिन्हित पूर्णांकeger, which
 * further casts to चिन्हित पूर्णांकeger क्रम unaligned multi-bit operation,
 * __biपंचांगap_set().
 * Then maximum biपंचांगap size supported is 2^31 bits भागided by 2^3 bits/byte,
 * that is 2^28 (256 MB) which maps to 2^31 * 2^12 = 2^43 (8TB) on 4K page
 * प्रणाली.
 */
#घोषणा सूचीTY_BITMAP_PAGES_MAX	 ((u64)पूर्णांक_उच्च)
#घोषणा सूचीTY_BITMAP_SIZE_MAX	 सूचीTY_BITMAP_BYTES(सूचीTY_BITMAP_PAGES_MAX)

#घोषणा WAITED 1

अटल पूर्णांक put_pfn(अचिन्हित दीर्घ pfn, पूर्णांक prot);

अटल काष्ठा vfio_group *vfio_iommu_find_iommu_group(काष्ठा vfio_iommu *iommu,
					       काष्ठा iommu_group *iommu_group);

/*
 * This code handles mapping and unmapping of user data buffers
 * पूर्णांकo DMA'ble space using the IOMMU
 */

अटल काष्ठा vfio_dma *vfio_find_dma(काष्ठा vfio_iommu *iommu,
				      dma_addr_t start, माप_प्रकार size)
अणु
	काष्ठा rb_node *node = iommu->dma_list.rb_node;

	जबतक (node) अणु
		काष्ठा vfio_dma *dma = rb_entry(node, काष्ठा vfio_dma, node);

		अगर (start + size <= dma->iova)
			node = node->rb_left;
		अन्यथा अगर (start >= dma->iova + dma->size)
			node = node->rb_right;
		अन्यथा
			वापस dma;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा rb_node *vfio_find_dma_first_node(काष्ठा vfio_iommu *iommu,
						dma_addr_t start, u64 size)
अणु
	काष्ठा rb_node *res = शून्य;
	काष्ठा rb_node *node = iommu->dma_list.rb_node;
	काष्ठा vfio_dma *dma_res = शून्य;

	जबतक (node) अणु
		काष्ठा vfio_dma *dma = rb_entry(node, काष्ठा vfio_dma, node);

		अगर (start < dma->iova + dma->size) अणु
			res = node;
			dma_res = dma;
			अगर (start >= dma->iova)
				अवरोध;
			node = node->rb_left;
		पूर्ण अन्यथा अणु
			node = node->rb_right;
		पूर्ण
	पूर्ण
	अगर (res && size && dma_res->iova >= start + size)
		res = शून्य;
	वापस res;
पूर्ण

अटल व्योम vfio_link_dma(काष्ठा vfio_iommu *iommu, काष्ठा vfio_dma *new)
अणु
	काष्ठा rb_node **link = &iommu->dma_list.rb_node, *parent = शून्य;
	काष्ठा vfio_dma *dma;

	जबतक (*link) अणु
		parent = *link;
		dma = rb_entry(parent, काष्ठा vfio_dma, node);

		अगर (new->iova + new->size <= dma->iova)
			link = &(*link)->rb_left;
		अन्यथा
			link = &(*link)->rb_right;
	पूर्ण

	rb_link_node(&new->node, parent, link);
	rb_insert_color(&new->node, &iommu->dma_list);
पूर्ण

अटल व्योम vfio_unlink_dma(काष्ठा vfio_iommu *iommu, काष्ठा vfio_dma *old)
अणु
	rb_erase(&old->node, &iommu->dma_list);
पूर्ण


अटल पूर्णांक vfio_dma_biपंचांगap_alloc(काष्ठा vfio_dma *dma, माप_प्रकार pgsize)
अणु
	uपूर्णांक64_t npages = dma->size / pgsize;

	अगर (npages > सूचीTY_BITMAP_PAGES_MAX)
		वापस -EINVAL;

	/*
	 * Allocate extra 64 bits that are used to calculate shअगरt required क्रम
	 * biपंचांगap_shअगरt_left() to manipulate and club unaligned number of pages
	 * in adjacent vfio_dma ranges.
	 */
	dma->biपंचांगap = kvzalloc(सूचीTY_BITMAP_BYTES(npages) + माप(u64),
			       GFP_KERNEL);
	अगर (!dma->biपंचांगap)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम vfio_dma_biपंचांगap_मुक्त(काष्ठा vfio_dma *dma)
अणु
	kमुक्त(dma->biपंचांगap);
	dma->biपंचांगap = शून्य;
पूर्ण

अटल व्योम vfio_dma_populate_biपंचांगap(काष्ठा vfio_dma *dma, माप_प्रकार pgsize)
अणु
	काष्ठा rb_node *p;
	अचिन्हित दीर्घ pgshअगरt = __ffs(pgsize);

	क्रम (p = rb_first(&dma->pfn_list); p; p = rb_next(p)) अणु
		काष्ठा vfio_pfn *vpfn = rb_entry(p, काष्ठा vfio_pfn, node);

		biपंचांगap_set(dma->biपंचांगap, (vpfn->iova - dma->iova) >> pgshअगरt, 1);
	पूर्ण
पूर्ण

अटल व्योम vfio_iommu_populate_biपंचांगap_full(काष्ठा vfio_iommu *iommu)
अणु
	काष्ठा rb_node *n;
	अचिन्हित दीर्घ pgshअगरt = __ffs(iommu->pgsize_biपंचांगap);

	क्रम (n = rb_first(&iommu->dma_list); n; n = rb_next(n)) अणु
		काष्ठा vfio_dma *dma = rb_entry(n, काष्ठा vfio_dma, node);

		biपंचांगap_set(dma->biपंचांगap, 0, dma->size >> pgshअगरt);
	पूर्ण
पूर्ण

अटल पूर्णांक vfio_dma_biपंचांगap_alloc_all(काष्ठा vfio_iommu *iommu, माप_प्रकार pgsize)
अणु
	काष्ठा rb_node *n;

	क्रम (n = rb_first(&iommu->dma_list); n; n = rb_next(n)) अणु
		काष्ठा vfio_dma *dma = rb_entry(n, काष्ठा vfio_dma, node);
		पूर्णांक ret;

		ret = vfio_dma_biपंचांगap_alloc(dma, pgsize);
		अगर (ret) अणु
			काष्ठा rb_node *p;

			क्रम (p = rb_prev(n); p; p = rb_prev(p)) अणु
				काष्ठा vfio_dma *dma = rb_entry(n,
							काष्ठा vfio_dma, node);

				vfio_dma_biपंचांगap_मुक्त(dma);
			पूर्ण
			वापस ret;
		पूर्ण
		vfio_dma_populate_biपंचांगap(dma, pgsize);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम vfio_dma_biपंचांगap_मुक्त_all(काष्ठा vfio_iommu *iommu)
अणु
	काष्ठा rb_node *n;

	क्रम (n = rb_first(&iommu->dma_list); n; n = rb_next(n)) अणु
		काष्ठा vfio_dma *dma = rb_entry(n, काष्ठा vfio_dma, node);

		vfio_dma_biपंचांगap_मुक्त(dma);
	पूर्ण
पूर्ण

/*
 * Helper Functions क्रम host iova-pfn list
 */
अटल काष्ठा vfio_pfn *vfio_find_vpfn(काष्ठा vfio_dma *dma, dma_addr_t iova)
अणु
	काष्ठा vfio_pfn *vpfn;
	काष्ठा rb_node *node = dma->pfn_list.rb_node;

	जबतक (node) अणु
		vpfn = rb_entry(node, काष्ठा vfio_pfn, node);

		अगर (iova < vpfn->iova)
			node = node->rb_left;
		अन्यथा अगर (iova > vpfn->iova)
			node = node->rb_right;
		अन्यथा
			वापस vpfn;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम vfio_link_pfn(काष्ठा vfio_dma *dma,
			  काष्ठा vfio_pfn *new)
अणु
	काष्ठा rb_node **link, *parent = शून्य;
	काष्ठा vfio_pfn *vpfn;

	link = &dma->pfn_list.rb_node;
	जबतक (*link) अणु
		parent = *link;
		vpfn = rb_entry(parent, काष्ठा vfio_pfn, node);

		अगर (new->iova < vpfn->iova)
			link = &(*link)->rb_left;
		अन्यथा
			link = &(*link)->rb_right;
	पूर्ण

	rb_link_node(&new->node, parent, link);
	rb_insert_color(&new->node, &dma->pfn_list);
पूर्ण

अटल व्योम vfio_unlink_pfn(काष्ठा vfio_dma *dma, काष्ठा vfio_pfn *old)
अणु
	rb_erase(&old->node, &dma->pfn_list);
पूर्ण

अटल पूर्णांक vfio_add_to_pfn_list(काष्ठा vfio_dma *dma, dma_addr_t iova,
				अचिन्हित दीर्घ pfn)
अणु
	काष्ठा vfio_pfn *vpfn;

	vpfn = kzalloc(माप(*vpfn), GFP_KERNEL);
	अगर (!vpfn)
		वापस -ENOMEM;

	vpfn->iova = iova;
	vpfn->pfn = pfn;
	vpfn->ref_count = 1;
	vfio_link_pfn(dma, vpfn);
	वापस 0;
पूर्ण

अटल व्योम vfio_हटाओ_from_pfn_list(काष्ठा vfio_dma *dma,
				      काष्ठा vfio_pfn *vpfn)
अणु
	vfio_unlink_pfn(dma, vpfn);
	kमुक्त(vpfn);
पूर्ण

अटल काष्ठा vfio_pfn *vfio_iova_get_vfio_pfn(काष्ठा vfio_dma *dma,
					       अचिन्हित दीर्घ iova)
अणु
	काष्ठा vfio_pfn *vpfn = vfio_find_vpfn(dma, iova);

	अगर (vpfn)
		vpfn->ref_count++;
	वापस vpfn;
पूर्ण

अटल पूर्णांक vfio_iova_put_vfio_pfn(काष्ठा vfio_dma *dma, काष्ठा vfio_pfn *vpfn)
अणु
	पूर्णांक ret = 0;

	vpfn->ref_count--;
	अगर (!vpfn->ref_count) अणु
		ret = put_pfn(vpfn->pfn, dma->prot);
		vfio_हटाओ_from_pfn_list(dma, vpfn);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_lock_acct(काष्ठा vfio_dma *dma, दीर्घ npage, bool async)
अणु
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक ret;

	अगर (!npage)
		वापस 0;

	mm = async ? get_task_mm(dma->task) : dma->task->mm;
	अगर (!mm)
		वापस -ESRCH; /* process निकासed */

	ret = mmap_ग_लिखो_lock_समाप्तable(mm);
	अगर (!ret) अणु
		ret = __account_locked_vm(mm, असल(npage), npage > 0, dma->task,
					  dma->lock_cap);
		mmap_ग_लिखो_unlock(mm);
	पूर्ण

	अगर (async)
		mmput(mm);

	वापस ret;
पूर्ण

/*
 * Some mappings aren't backed by a struct page, for example an mmap'd
 * MMIO range क्रम our own or another device.  These use a dअगरferent
 * pfn conversion and shouldn't be tracked as locked pages.
 * For compound pages, any driver that sets the reserved bit in head
 * page needs to set the reserved bit in all subpages to be safe.
 */
अटल bool is_invalid_reserved_pfn(अचिन्हित दीर्घ pfn)
अणु
	अगर (pfn_valid(pfn))
		वापस PageReserved(pfn_to_page(pfn));

	वापस true;
पूर्ण

अटल पूर्णांक put_pfn(अचिन्हित दीर्घ pfn, पूर्णांक prot)
अणु
	अगर (!is_invalid_reserved_pfn(pfn)) अणु
		काष्ठा page *page = pfn_to_page(pfn);

		unpin_user_pages_dirty_lock(&page, 1, prot & IOMMU_WRITE);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा VFIO_BATCH_MAX_CAPACITY (PAGE_SIZE / माप(काष्ठा page *))

अटल व्योम vfio_batch_init(काष्ठा vfio_batch *batch)
अणु
	batch->size = 0;
	batch->offset = 0;

	अगर (unlikely(disable_hugepages))
		जाओ fallback;

	batch->pages = (काष्ठा page **) __get_मुक्त_page(GFP_KERNEL);
	अगर (!batch->pages)
		जाओ fallback;

	batch->capacity = VFIO_BATCH_MAX_CAPACITY;
	वापस;

fallback:
	batch->pages = &batch->fallback_page;
	batch->capacity = 1;
पूर्ण

अटल व्योम vfio_batch_unpin(काष्ठा vfio_batch *batch, काष्ठा vfio_dma *dma)
अणु
	जबतक (batch->size) अणु
		अचिन्हित दीर्घ pfn = page_to_pfn(batch->pages[batch->offset]);

		put_pfn(pfn, dma->prot);
		batch->offset++;
		batch->size--;
	पूर्ण
पूर्ण

अटल व्योम vfio_batch_fini(काष्ठा vfio_batch *batch)
अणु
	अगर (batch->capacity == VFIO_BATCH_MAX_CAPACITY)
		मुक्त_page((अचिन्हित दीर्घ)batch->pages);
पूर्ण

अटल पूर्णांक follow_fault_pfn(काष्ठा vm_area_काष्ठा *vma, काष्ठा mm_काष्ठा *mm,
			    अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ *pfn,
			    bool ग_लिखो_fault)
अणु
	pte_t *ptep;
	spinlock_t *ptl;
	पूर्णांक ret;

	ret = follow_pte(vma->vm_mm, vaddr, &ptep, &ptl);
	अगर (ret) अणु
		bool unlocked = false;

		ret = fixup_user_fault(mm, vaddr,
				       FAULT_FLAG_REMOTE |
				       (ग_लिखो_fault ?  FAULT_FLAG_WRITE : 0),
				       &unlocked);
		अगर (unlocked)
			वापस -EAGAIN;

		अगर (ret)
			वापस ret;

		ret = follow_pte(vma->vm_mm, vaddr, &ptep, &ptl);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (ग_लिखो_fault && !pte_ग_लिखो(*ptep))
		ret = -EFAULT;
	अन्यथा
		*pfn = pte_pfn(*ptep);

	pte_unmap_unlock(ptep, ptl);
	वापस ret;
पूर्ण

/*
 * Returns the positive number of pfns successfully obtained or a negative
 * error code.
 */
अटल पूर्णांक vaddr_get_pfns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ vaddr,
			  दीर्घ npages, पूर्णांक prot, अचिन्हित दीर्घ *pfn,
			  काष्ठा page **pages)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित पूर्णांक flags = 0;
	पूर्णांक ret;

	अगर (prot & IOMMU_WRITE)
		flags |= FOLL_WRITE;

	mmap_पढ़ो_lock(mm);
	ret = pin_user_pages_remote(mm, vaddr, npages, flags | FOLL_LONGTERM,
				    pages, शून्य, शून्य);
	अगर (ret > 0) अणु
		*pfn = page_to_pfn(pages[0]);
		जाओ करोne;
	पूर्ण

	vaddr = untagged_addr(vaddr);

retry:
	vma = find_vma_पूर्णांकersection(mm, vaddr, vaddr + 1);

	अगर (vma && vma->vm_flags & VM_PFNMAP) अणु
		ret = follow_fault_pfn(vma, mm, vaddr, pfn, prot & IOMMU_WRITE);
		अगर (ret == -EAGAIN)
			जाओ retry;

		अगर (!ret) अणु
			अगर (is_invalid_reserved_pfn(*pfn))
				ret = 1;
			अन्यथा
				ret = -EFAULT;
		पूर्ण
	पूर्ण
करोne:
	mmap_पढ़ो_unlock(mm);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_रुको(काष्ठा vfio_iommu *iommu)
अणु
	DEFINE_WAIT(रुको);

	prepare_to_रुको(&iommu->vaddr_रुको, &रुको, TASK_KILLABLE);
	mutex_unlock(&iommu->lock);
	schedule();
	mutex_lock(&iommu->lock);
	finish_रुको(&iommu->vaddr_रुको, &रुको);
	अगर (kthपढ़ो_should_stop() || !iommu->container_खोलो ||
	    fatal_संकेत_pending(current)) अणु
		वापस -EFAULT;
	पूर्ण
	वापस WAITED;
पूर्ण

/*
 * Find dma काष्ठा and रुको क्रम its vaddr to be valid.  iommu lock is dropped
 * अगर the task रुकोs, but is re-locked on वापस.  Return result in *dma_p.
 * Return 0 on success with no रुकोing, WAITED on success अगर रुकोed, and -त्रुटि_सं
 * on error.
 */
अटल पूर्णांक vfio_find_dma_valid(काष्ठा vfio_iommu *iommu, dma_addr_t start,
			       माप_प्रकार size, काष्ठा vfio_dma **dma_p)
अणु
	पूर्णांक ret;

	करो अणु
		*dma_p = vfio_find_dma(iommu, start, size);
		अगर (!*dma_p)
			ret = -EINVAL;
		अन्यथा अगर (!(*dma_p)->vaddr_invalid)
			ret = 0;
		अन्यथा
			ret = vfio_रुको(iommu);
	पूर्ण जबतक (ret > 0);

	वापस ret;
पूर्ण

/*
 * Wait क्रम all vaddr in the dma_list to become valid.  iommu lock is dropped
 * अगर the task रुकोs, but is re-locked on वापस.  Return 0 on success with no
 * रुकोing, WAITED on success अगर रुकोed, and -त्रुटि_सं on error.
 */
अटल पूर्णांक vfio_रुको_all_valid(काष्ठा vfio_iommu *iommu)
अणु
	पूर्णांक ret = 0;

	जबतक (iommu->vaddr_invalid_count && ret >= 0)
		ret = vfio_रुको(iommu);

	वापस ret;
पूर्ण

/*
 * Attempt to pin pages.  We really करोn't want to track all the pfns and
 * the iommu can only map chunks of consecutive pfns anyway, so get the
 * first page and all consecutive pages with the same locking.
 */
अटल दीर्घ vfio_pin_pages_remote(काष्ठा vfio_dma *dma, अचिन्हित दीर्घ vaddr,
				  दीर्घ npage, अचिन्हित दीर्घ *pfn_base,
				  अचिन्हित दीर्घ limit, काष्ठा vfio_batch *batch)
अणु
	अचिन्हित दीर्घ pfn;
	काष्ठा mm_काष्ठा *mm = current->mm;
	दीर्घ ret, pinned = 0, lock_acct = 0;
	bool rsvd;
	dma_addr_t iova = vaddr - dma->vaddr + dma->iova;

	/* This code path is only user initiated */
	अगर (!mm)
		वापस -ENODEV;

	अगर (batch->size) अणु
		/* Leftover pages in batch from an earlier call. */
		*pfn_base = page_to_pfn(batch->pages[batch->offset]);
		pfn = *pfn_base;
		rsvd = is_invalid_reserved_pfn(*pfn_base);
	पूर्ण अन्यथा अणु
		*pfn_base = 0;
	पूर्ण

	जबतक (npage) अणु
		अगर (!batch->size) अणु
			/* Empty batch, so refill it. */
			दीर्घ req_pages = min_t(दीर्घ, npage, batch->capacity);

			ret = vaddr_get_pfns(mm, vaddr, req_pages, dma->prot,
					     &pfn, batch->pages);
			अगर (ret < 0)
				जाओ unpin_out;

			batch->size = ret;
			batch->offset = 0;

			अगर (!*pfn_base) अणु
				*pfn_base = pfn;
				rsvd = is_invalid_reserved_pfn(*pfn_base);
			पूर्ण
		पूर्ण

		/*
		 * pfn is preset क्रम the first iteration of this inner loop and
		 * updated at the end to handle a VM_PFNMAP pfn.  In that हाल,
		 * batch->pages isn't valid (there's no काष्ठा page), so allow
		 * batch->pages to be touched only when there's more than one
		 * pfn to check, which guarantees the pfns are from a
		 * !VM_PFNMAP vma.
		 */
		जबतक (true) अणु
			अगर (pfn != *pfn_base + pinned ||
			    rsvd != is_invalid_reserved_pfn(pfn))
				जाओ out;

			/*
			 * Reserved pages aren't counted against the user,
			 * बाह्यally pinned pages are alपढ़ोy counted against
			 * the user.
			 */
			अगर (!rsvd && !vfio_find_vpfn(dma, iova)) अणु
				अगर (!dma->lock_cap &&
				    mm->locked_vm + lock_acct + 1 > limit) अणु
					pr_warn("%s: RLIMIT_MEMLOCK (%ld) exceeded\n",
						__func__, limit << PAGE_SHIFT);
					ret = -ENOMEM;
					जाओ unpin_out;
				पूर्ण
				lock_acct++;
			पूर्ण

			pinned++;
			npage--;
			vaddr += PAGE_SIZE;
			iova += PAGE_SIZE;
			batch->offset++;
			batch->size--;

			अगर (!batch->size)
				अवरोध;

			pfn = page_to_pfn(batch->pages[batch->offset]);
		पूर्ण

		अगर (unlikely(disable_hugepages))
			अवरोध;
	पूर्ण

out:
	ret = vfio_lock_acct(dma, lock_acct, false);

unpin_out:
	अगर (batch->size == 1 && !batch->offset) अणु
		/* May be a VM_PFNMAP pfn, which the batch can't remember. */
		put_pfn(pfn, dma->prot);
		batch->size = 0;
	पूर्ण

	अगर (ret < 0) अणु
		अगर (pinned && !rsvd) अणु
			क्रम (pfn = *pfn_base ; pinned ; pfn++, pinned--)
				put_pfn(pfn, dma->prot);
		पूर्ण
		vfio_batch_unpin(batch, dma);

		वापस ret;
	पूर्ण

	वापस pinned;
पूर्ण

अटल दीर्घ vfio_unpin_pages_remote(काष्ठा vfio_dma *dma, dma_addr_t iova,
				    अचिन्हित दीर्घ pfn, दीर्घ npage,
				    bool करो_accounting)
अणु
	दीर्घ unlocked = 0, locked = 0;
	दीर्घ i;

	क्रम (i = 0; i < npage; i++, iova += PAGE_SIZE) अणु
		अगर (put_pfn(pfn++, dma->prot)) अणु
			unlocked++;
			अगर (vfio_find_vpfn(dma, iova))
				locked++;
		पूर्ण
	पूर्ण

	अगर (करो_accounting)
		vfio_lock_acct(dma, locked - unlocked, true);

	वापस unlocked;
पूर्ण

अटल पूर्णांक vfio_pin_page_बाह्यal(काष्ठा vfio_dma *dma, अचिन्हित दीर्घ vaddr,
				  अचिन्हित दीर्घ *pfn_base, bool करो_accounting)
अणु
	काष्ठा page *pages[1];
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक ret;

	mm = get_task_mm(dma->task);
	अगर (!mm)
		वापस -ENODEV;

	ret = vaddr_get_pfns(mm, vaddr, 1, dma->prot, pfn_base, pages);
	अगर (ret != 1)
		जाओ out;

	ret = 0;

	अगर (करो_accounting && !is_invalid_reserved_pfn(*pfn_base)) अणु
		ret = vfio_lock_acct(dma, 1, true);
		अगर (ret) अणु
			put_pfn(*pfn_base, dma->prot);
			अगर (ret == -ENOMEM)
				pr_warn("%s: Task %s (%d) RLIMIT_MEMLOCK "
					"(%ld) exceeded\n", __func__,
					dma->task->comm, task_pid_nr(dma->task),
					task_rlimit(dma->task, RLIMIT_MEMLOCK));
		पूर्ण
	पूर्ण

out:
	mmput(mm);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_unpin_page_बाह्यal(काष्ठा vfio_dma *dma, dma_addr_t iova,
				    bool करो_accounting)
अणु
	पूर्णांक unlocked;
	काष्ठा vfio_pfn *vpfn = vfio_find_vpfn(dma, iova);

	अगर (!vpfn)
		वापस 0;

	unlocked = vfio_iova_put_vfio_pfn(dma, vpfn);

	अगर (करो_accounting)
		vfio_lock_acct(dma, -unlocked, true);

	वापस unlocked;
पूर्ण

अटल पूर्णांक vfio_iommu_type1_pin_pages(व्योम *iommu_data,
				      काष्ठा iommu_group *iommu_group,
				      अचिन्हित दीर्घ *user_pfn,
				      पूर्णांक npage, पूर्णांक prot,
				      अचिन्हित दीर्घ *phys_pfn)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;
	काष्ठा vfio_group *group;
	पूर्णांक i, j, ret;
	अचिन्हित दीर्घ remote_vaddr;
	काष्ठा vfio_dma *dma;
	bool करो_accounting;
	dma_addr_t iova;

	अगर (!iommu || !user_pfn || !phys_pfn)
		वापस -EINVAL;

	/* Supported क्रम v2 version only */
	अगर (!iommu->v2)
		वापस -EACCES;

	mutex_lock(&iommu->lock);

	/*
	 * Wait क्रम all necessary vaddr's to be valid so they can be used in
	 * the मुख्य loop without dropping the lock, to aव्योम racing vs unmap.
	 */
again:
	अगर (iommu->vaddr_invalid_count) अणु
		क्रम (i = 0; i < npage; i++) अणु
			iova = user_pfn[i] << PAGE_SHIFT;
			ret = vfio_find_dma_valid(iommu, iova, PAGE_SIZE, &dma);
			अगर (ret < 0)
				जाओ pin_करोne;
			अगर (ret == WAITED)
				जाओ again;
		पूर्ण
	पूर्ण

	/* Fail अगर notअगरier list is empty */
	अगर (!iommu->notअगरier.head) अणु
		ret = -EINVAL;
		जाओ pin_करोne;
	पूर्ण

	/*
	 * If iommu capable करोमुख्य exist in the container then all pages are
	 * alपढ़ोy pinned and accounted. Accounting should be करोne अगर there is no
	 * iommu capable करोमुख्य in the container.
	 */
	करो_accounting = !IS_IOMMU_CAP_DOMAIN_IN_CONTAINER(iommu);

	क्रम (i = 0; i < npage; i++) अणु
		काष्ठा vfio_pfn *vpfn;

		iova = user_pfn[i] << PAGE_SHIFT;
		dma = vfio_find_dma(iommu, iova, PAGE_SIZE);
		अगर (!dma) अणु
			ret = -EINVAL;
			जाओ pin_unwind;
		पूर्ण

		अगर ((dma->prot & prot) != prot) अणु
			ret = -EPERM;
			जाओ pin_unwind;
		पूर्ण

		vpfn = vfio_iova_get_vfio_pfn(dma, iova);
		अगर (vpfn) अणु
			phys_pfn[i] = vpfn->pfn;
			जारी;
		पूर्ण

		remote_vaddr = dma->vaddr + (iova - dma->iova);
		ret = vfio_pin_page_बाह्यal(dma, remote_vaddr, &phys_pfn[i],
					     करो_accounting);
		अगर (ret)
			जाओ pin_unwind;

		ret = vfio_add_to_pfn_list(dma, iova, phys_pfn[i]);
		अगर (ret) अणु
			अगर (put_pfn(phys_pfn[i], dma->prot) && करो_accounting)
				vfio_lock_acct(dma, -1, true);
			जाओ pin_unwind;
		पूर्ण

		अगर (iommu->dirty_page_tracking) अणु
			अचिन्हित दीर्घ pgshअगरt = __ffs(iommu->pgsize_biपंचांगap);

			/*
			 * Biपंचांगap populated with the smallest supported page
			 * size
			 */
			biपंचांगap_set(dma->biपंचांगap,
				   (iova - dma->iova) >> pgshअगरt, 1);
		पूर्ण
	पूर्ण
	ret = i;

	group = vfio_iommu_find_iommu_group(iommu, iommu_group);
	अगर (!group->pinned_page_dirty_scope) अणु
		group->pinned_page_dirty_scope = true;
		iommu->num_non_pinned_groups--;
	पूर्ण

	जाओ pin_करोne;

pin_unwind:
	phys_pfn[i] = 0;
	क्रम (j = 0; j < i; j++) अणु
		dma_addr_t iova;

		iova = user_pfn[j] << PAGE_SHIFT;
		dma = vfio_find_dma(iommu, iova, PAGE_SIZE);
		vfio_unpin_page_बाह्यal(dma, iova, करो_accounting);
		phys_pfn[j] = 0;
	पूर्ण
pin_करोne:
	mutex_unlock(&iommu->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_iommu_type1_unpin_pages(व्योम *iommu_data,
					अचिन्हित दीर्घ *user_pfn,
					पूर्णांक npage)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;
	bool करो_accounting;
	पूर्णांक i;

	अगर (!iommu || !user_pfn || npage <= 0)
		वापस -EINVAL;

	/* Supported क्रम v2 version only */
	अगर (!iommu->v2)
		वापस -EACCES;

	mutex_lock(&iommu->lock);

	करो_accounting = !IS_IOMMU_CAP_DOMAIN_IN_CONTAINER(iommu);
	क्रम (i = 0; i < npage; i++) अणु
		काष्ठा vfio_dma *dma;
		dma_addr_t iova;

		iova = user_pfn[i] << PAGE_SHIFT;
		dma = vfio_find_dma(iommu, iova, PAGE_SIZE);
		अगर (!dma)
			अवरोध;

		vfio_unpin_page_बाह्यal(dma, iova, करो_accounting);
	पूर्ण

	mutex_unlock(&iommu->lock);
	वापस i > 0 ? i : -EINVAL;
पूर्ण

अटल दीर्घ vfio_sync_unpin(काष्ठा vfio_dma *dma, काष्ठा vfio_करोमुख्य *करोमुख्य,
			    काष्ठा list_head *regions,
			    काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	दीर्घ unlocked = 0;
	काष्ठा vfio_regions *entry, *next;

	iommu_iotlb_sync(करोमुख्य->करोमुख्य, iotlb_gather);

	list_क्रम_each_entry_safe(entry, next, regions, list) अणु
		unlocked += vfio_unpin_pages_remote(dma,
						    entry->iova,
						    entry->phys >> PAGE_SHIFT,
						    entry->len >> PAGE_SHIFT,
						    false);
		list_del(&entry->list);
		kमुक्त(entry);
	पूर्ण

	cond_resched();

	वापस unlocked;
पूर्ण

/*
 * Generally, VFIO needs to unpin remote pages after each IOTLB flush.
 * Thereक्रमe, when using IOTLB flush sync पूर्णांकerface, VFIO need to keep track
 * of these regions (currently using a list).
 *
 * This value specअगरies maximum number of regions क्रम each IOTLB flush sync.
 */
#घोषणा VFIO_IOMMU_TLB_SYNC_MAX		512

अटल माप_प्रकार unmap_unpin_fast(काष्ठा vfio_करोमुख्य *करोमुख्य,
			       काष्ठा vfio_dma *dma, dma_addr_t *iova,
			       माप_प्रकार len, phys_addr_t phys, दीर्घ *unlocked,
			       काष्ठा list_head *unmapped_list,
			       पूर्णांक *unmapped_cnt,
			       काष्ठा iommu_iotlb_gather *iotlb_gather)
अणु
	माप_प्रकार unmapped = 0;
	काष्ठा vfio_regions *entry = kzalloc(माप(*entry), GFP_KERNEL);

	अगर (entry) अणु
		unmapped = iommu_unmap_fast(करोमुख्य->करोमुख्य, *iova, len,
					    iotlb_gather);

		अगर (!unmapped) अणु
			kमुक्त(entry);
		पूर्ण अन्यथा अणु
			entry->iova = *iova;
			entry->phys = phys;
			entry->len  = unmapped;
			list_add_tail(&entry->list, unmapped_list);

			*iova += unmapped;
			(*unmapped_cnt)++;
		पूर्ण
	पूर्ण

	/*
	 * Sync अगर the number of fast-unmap regions hits the limit
	 * or in हाल of errors.
	 */
	अगर (*unmapped_cnt >= VFIO_IOMMU_TLB_SYNC_MAX || !unmapped) अणु
		*unlocked += vfio_sync_unpin(dma, करोमुख्य, unmapped_list,
					     iotlb_gather);
		*unmapped_cnt = 0;
	पूर्ण

	वापस unmapped;
पूर्ण

अटल माप_प्रकार unmap_unpin_slow(काष्ठा vfio_करोमुख्य *करोमुख्य,
			       काष्ठा vfio_dma *dma, dma_addr_t *iova,
			       माप_प्रकार len, phys_addr_t phys,
			       दीर्घ *unlocked)
अणु
	माप_प्रकार unmapped = iommu_unmap(करोमुख्य->करोमुख्य, *iova, len);

	अगर (unmapped) अणु
		*unlocked += vfio_unpin_pages_remote(dma, *iova,
						     phys >> PAGE_SHIFT,
						     unmapped >> PAGE_SHIFT,
						     false);
		*iova += unmapped;
		cond_resched();
	पूर्ण
	वापस unmapped;
पूर्ण

अटल दीर्घ vfio_unmap_unpin(काष्ठा vfio_iommu *iommu, काष्ठा vfio_dma *dma,
			     bool करो_accounting)
अणु
	dma_addr_t iova = dma->iova, end = dma->iova + dma->size;
	काष्ठा vfio_करोमुख्य *करोमुख्य, *d;
	LIST_HEAD(unmapped_region_list);
	काष्ठा iommu_iotlb_gather iotlb_gather;
	पूर्णांक unmapped_region_cnt = 0;
	दीर्घ unlocked = 0;

	अगर (!dma->size)
		वापस 0;

	अगर (!IS_IOMMU_CAP_DOMAIN_IN_CONTAINER(iommu))
		वापस 0;

	/*
	 * We use the IOMMU to track the physical addresses, otherwise we'd
	 * need a much more complicated tracking प्रणाली.  Unक्रमtunately that
	 * means we need to use one of the iommu करोमुख्यs to figure out the
	 * pfns to unpin.  The rest need to be unmapped in advance so we have
	 * no iommu translations reमुख्यing when the pages are unpinned.
	 */
	करोमुख्य = d = list_first_entry(&iommu->करोमुख्य_list,
				      काष्ठा vfio_करोमुख्य, next);

	list_क्रम_each_entry_जारी(d, &iommu->करोमुख्य_list, next) अणु
		iommu_unmap(d->करोमुख्य, dma->iova, dma->size);
		cond_resched();
	पूर्ण

	iommu_iotlb_gather_init(&iotlb_gather);
	जबतक (iova < end) अणु
		माप_प्रकार unmapped, len;
		phys_addr_t phys, next;

		phys = iommu_iova_to_phys(करोमुख्य->करोमुख्य, iova);
		अगर (WARN_ON(!phys)) अणु
			iova += PAGE_SIZE;
			जारी;
		पूर्ण

		/*
		 * To optimize क्रम fewer iommu_unmap() calls, each of which
		 * may require hardware cache flushing, try to find the
		 * largest contiguous physical memory chunk to unmap.
		 */
		क्रम (len = PAGE_SIZE;
		     !करोमुख्य->fgsp && iova + len < end; len += PAGE_SIZE) अणु
			next = iommu_iova_to_phys(करोमुख्य->करोमुख्य, iova + len);
			अगर (next != phys + len)
				अवरोध;
		पूर्ण

		/*
		 * First, try to use fast unmap/unpin. In हाल of failure,
		 * चयन to slow unmap/unpin path.
		 */
		unmapped = unmap_unpin_fast(करोमुख्य, dma, &iova, len, phys,
					    &unlocked, &unmapped_region_list,
					    &unmapped_region_cnt,
					    &iotlb_gather);
		अगर (!unmapped) अणु
			unmapped = unmap_unpin_slow(करोमुख्य, dma, &iova, len,
						    phys, &unlocked);
			अगर (WARN_ON(!unmapped))
				अवरोध;
		पूर्ण
	पूर्ण

	dma->iommu_mapped = false;

	अगर (unmapped_region_cnt) अणु
		unlocked += vfio_sync_unpin(dma, करोमुख्य, &unmapped_region_list,
					    &iotlb_gather);
	पूर्ण

	अगर (करो_accounting) अणु
		vfio_lock_acct(dma, -unlocked, true);
		वापस 0;
	पूर्ण
	वापस unlocked;
पूर्ण

अटल व्योम vfio_हटाओ_dma(काष्ठा vfio_iommu *iommu, काष्ठा vfio_dma *dma)
अणु
	WARN_ON(!RB_EMPTY_ROOT(&dma->pfn_list));
	vfio_unmap_unpin(iommu, dma, true);
	vfio_unlink_dma(iommu, dma);
	put_task_काष्ठा(dma->task);
	vfio_dma_biपंचांगap_मुक्त(dma);
	अगर (dma->vaddr_invalid) अणु
		iommu->vaddr_invalid_count--;
		wake_up_all(&iommu->vaddr_रुको);
	पूर्ण
	kमुक्त(dma);
	iommu->dma_avail++;
पूर्ण

अटल व्योम vfio_update_pgsize_biपंचांगap(काष्ठा vfio_iommu *iommu)
अणु
	काष्ठा vfio_करोमुख्य *करोमुख्य;

	iommu->pgsize_biपंचांगap = अच_दीर्घ_उच्च;

	list_क्रम_each_entry(करोमुख्य, &iommu->करोमुख्य_list, next)
		iommu->pgsize_biपंचांगap &= करोमुख्य->करोमुख्य->pgsize_biपंचांगap;

	/*
	 * In हाल the IOMMU supports page sizes smaller than PAGE_SIZE
	 * we pretend PAGE_SIZE is supported and hide sub-PAGE_SIZE sizes.
	 * That way the user will be able to map/unmap buffers whose size/
	 * start address is aligned with PAGE_SIZE. Pinning code uses that
	 * granularity जबतक iommu driver can use the sub-PAGE_SIZE size
	 * to map the buffer.
	 */
	अगर (iommu->pgsize_biपंचांगap & ~PAGE_MASK) अणु
		iommu->pgsize_biपंचांगap &= PAGE_MASK;
		iommu->pgsize_biपंचांगap |= PAGE_SIZE;
	पूर्ण
पूर्ण

अटल पूर्णांक update_user_biपंचांगap(u64 __user *biपंचांगap, काष्ठा vfio_iommu *iommu,
			      काष्ठा vfio_dma *dma, dma_addr_t base_iova,
			      माप_प्रकार pgsize)
अणु
	अचिन्हित दीर्घ pgshअगरt = __ffs(pgsize);
	अचिन्हित दीर्घ nbits = dma->size >> pgshअगरt;
	अचिन्हित दीर्घ bit_offset = (dma->iova - base_iova) >> pgshअगरt;
	अचिन्हित दीर्घ copy_offset = bit_offset / BITS_PER_LONG;
	अचिन्हित दीर्घ shअगरt = bit_offset % BITS_PER_LONG;
	अचिन्हित दीर्घ leftover;

	/*
	 * mark all pages dirty अगर any IOMMU capable device is not able
	 * to report dirty pages and all pages are pinned and mapped.
	 */
	अगर (iommu->num_non_pinned_groups && dma->iommu_mapped)
		biपंचांगap_set(dma->biपंचांगap, 0, nbits);

	अगर (shअगरt) अणु
		biपंचांगap_shअगरt_left(dma->biपंचांगap, dma->biपंचांगap, shअगरt,
				  nbits + shअगरt);

		अगर (copy_from_user(&leftover,
				   (व्योम __user *)(biपंचांगap + copy_offset),
				   माप(leftover)))
			वापस -EFAULT;

		biपंचांगap_or(dma->biपंचांगap, dma->biपंचांगap, &leftover, shअगरt);
	पूर्ण

	अगर (copy_to_user((व्योम __user *)(biपंचांगap + copy_offset), dma->biपंचांगap,
			 सूचीTY_BITMAP_BYTES(nbits + shअगरt)))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_iova_dirty_biपंचांगap(u64 __user *biपंचांगap, काष्ठा vfio_iommu *iommu,
				  dma_addr_t iova, माप_प्रकार size, माप_प्रकार pgsize)
अणु
	काष्ठा vfio_dma *dma;
	काष्ठा rb_node *n;
	अचिन्हित दीर्घ pgshअगरt = __ffs(pgsize);
	पूर्णांक ret;

	/*
	 * GET_BITMAP request must fully cover vfio_dma mappings.  Multiple
	 * vfio_dma mappings may be clubbed by specअगरying large ranges, but
	 * there must not be any previous mappings bisected by the range.
	 * An error will be वापसed अगर these conditions are not met.
	 */
	dma = vfio_find_dma(iommu, iova, 1);
	अगर (dma && dma->iova != iova)
		वापस -EINVAL;

	dma = vfio_find_dma(iommu, iova + size - 1, 0);
	अगर (dma && dma->iova + dma->size != iova + size)
		वापस -EINVAL;

	क्रम (n = rb_first(&iommu->dma_list); n; n = rb_next(n)) अणु
		काष्ठा vfio_dma *dma = rb_entry(n, काष्ठा vfio_dma, node);

		अगर (dma->iova < iova)
			जारी;

		अगर (dma->iova > iova + size - 1)
			अवरोध;

		ret = update_user_biपंचांगap(biपंचांगap, iommu, dma, iova, pgsize);
		अगर (ret)
			वापस ret;

		/*
		 * Re-populate biपंचांगap to include all pinned pages which are
		 * considered as dirty but exclude pages which are unpinned and
		 * pages which are marked dirty by vfio_dma_rw()
		 */
		biपंचांगap_clear(dma->biपंचांगap, 0, dma->size >> pgshअगरt);
		vfio_dma_populate_biपंचांगap(dma, pgsize);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक verअगरy_biपंचांगap_size(uपूर्णांक64_t npages, uपूर्णांक64_t biपंचांगap_size)
अणु
	अगर (!npages || !biपंचांगap_size || (biपंचांगap_size > सूचीTY_BITMAP_SIZE_MAX) ||
	    (biपंचांगap_size < सूचीTY_BITMAP_BYTES(npages)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_dma_करो_unmap(काष्ठा vfio_iommu *iommu,
			     काष्ठा vfio_iommu_type1_dma_unmap *unmap,
			     काष्ठा vfio_biपंचांगap *biपंचांगap)
अणु
	काष्ठा vfio_dma *dma, *dma_last = शून्य;
	माप_प्रकार unmapped = 0, pgsize;
	पूर्णांक ret = -EINVAL, retries = 0;
	अचिन्हित दीर्घ pgshअगरt;
	dma_addr_t iova = unmap->iova;
	u64 size = unmap->size;
	bool unmap_all = unmap->flags & VFIO_DMA_UNMAP_FLAG_ALL;
	bool invalidate_vaddr = unmap->flags & VFIO_DMA_UNMAP_FLAG_VADDR;
	काष्ठा rb_node *n, *first_n;

	mutex_lock(&iommu->lock);

	pgshअगरt = __ffs(iommu->pgsize_biपंचांगap);
	pgsize = (माप_प्रकार)1 << pgshअगरt;

	अगर (iova & (pgsize - 1))
		जाओ unlock;

	अगर (unmap_all) अणु
		अगर (iova || size)
			जाओ unlock;
		size = U64_MAX;
	पूर्ण अन्यथा अगर (!size || size & (pgsize - 1) ||
		   iova + size - 1 < iova || size > SIZE_MAX) अणु
		जाओ unlock;
	पूर्ण

	/* When dirty tracking is enabled, allow only min supported pgsize */
	अगर ((unmap->flags & VFIO_DMA_UNMAP_FLAG_GET_सूचीTY_BITMAP) &&
	    (!iommu->dirty_page_tracking || (biपंचांगap->pgsize != pgsize))) अणु
		जाओ unlock;
	पूर्ण

	WARN_ON((pgsize - 1) & PAGE_MASK);
again:
	/*
	 * vfio-iommu-type1 (v1) - User mappings were coalesced together to
	 * aव्योम tracking inभागidual mappings.  This means that the granularity
	 * of the original mapping was lost and the user was allowed to attempt
	 * to unmap any range.  Depending on the contiguousness of physical
	 * memory and page sizes supported by the IOMMU, arbitrary unmaps may
	 * or may not have worked.  We only guaranteed unmap granularity
	 * matching the original mapping; even though it was untracked here,
	 * the original mappings are reflected in IOMMU mappings.  This
	 * resulted in a couple unusual behaviors.  First, अगर a range is not
	 * able to be unmapped, ex. a set of 4k pages that was mapped as a
	 * 2M hugepage पूर्णांकo the IOMMU, the unmap ioctl वापसs success but with
	 * a zero sized unmap.  Also, अगर an unmap request overlaps the first
	 * address of a hugepage, the IOMMU will unmap the entire hugepage.
	 * This also वापसs success and the वापसed unmap size reflects the
	 * actual size unmapped.
	 *
	 * We attempt to मुख्यtain compatibility with this "v1" पूर्णांकerface, but
	 * we take control out of the hands of the IOMMU.  Thereक्रमe, an unmap
	 * request offset from the beginning of the original mapping will
	 * वापस success with zero sized unmap.  And an unmap request covering
	 * the first iova of mapping will unmap the entire range.
	 *
	 * The v2 version of this पूर्णांकerface पूर्णांकends to be more deterministic.
	 * Unmap requests must fully cover previous mappings.  Multiple
	 * mappings may still be unmaped by specअगरying large ranges, but there
	 * must not be any previous mappings bisected by the range.  An error
	 * will be वापसed अगर these conditions are not met.  The v2 पूर्णांकerface
	 * will only वापस success and a size of zero अगर there were no
	 * mappings within the range.
	 */
	अगर (iommu->v2 && !unmap_all) अणु
		dma = vfio_find_dma(iommu, iova, 1);
		अगर (dma && dma->iova != iova)
			जाओ unlock;

		dma = vfio_find_dma(iommu, iova + size - 1, 0);
		अगर (dma && dma->iova + dma->size != iova + size)
			जाओ unlock;
	पूर्ण

	ret = 0;
	n = first_n = vfio_find_dma_first_node(iommu, iova, size);

	जबतक (n) अणु
		dma = rb_entry(n, काष्ठा vfio_dma, node);
		अगर (dma->iova >= iova + size)
			अवरोध;

		अगर (!iommu->v2 && iova > dma->iova)
			अवरोध;
		/*
		 * Task with same address space who mapped this iova range is
		 * allowed to unmap the iova range.
		 */
		अगर (dma->task->mm != current->mm)
			अवरोध;

		अगर (invalidate_vaddr) अणु
			अगर (dma->vaddr_invalid) अणु
				काष्ठा rb_node *last_n = n;

				क्रम (n = first_n; n != last_n; n = rb_next(n)) अणु
					dma = rb_entry(n,
						       काष्ठा vfio_dma, node);
					dma->vaddr_invalid = false;
					iommu->vaddr_invalid_count--;
				पूर्ण
				ret = -EINVAL;
				unmapped = 0;
				अवरोध;
			पूर्ण
			dma->vaddr_invalid = true;
			iommu->vaddr_invalid_count++;
			unmapped += dma->size;
			n = rb_next(n);
			जारी;
		पूर्ण

		अगर (!RB_EMPTY_ROOT(&dma->pfn_list)) अणु
			काष्ठा vfio_iommu_type1_dma_unmap nb_unmap;

			अगर (dma_last == dma) अणु
				BUG_ON(++retries > 10);
			पूर्ण अन्यथा अणु
				dma_last = dma;
				retries = 0;
			पूर्ण

			nb_unmap.iova = dma->iova;
			nb_unmap.size = dma->size;

			/*
			 * Notअगरy anyone (mdev venकरोr drivers) to invalidate and
			 * unmap iovas within the range we're about to unmap.
			 * Venकरोr drivers MUST unpin pages in response to an
			 * invalidation.
			 */
			mutex_unlock(&iommu->lock);
			blocking_notअगरier_call_chain(&iommu->notअगरier,
						    VFIO_IOMMU_NOTIFY_DMA_UNMAP,
						    &nb_unmap);
			mutex_lock(&iommu->lock);
			जाओ again;
		पूर्ण

		अगर (unmap->flags & VFIO_DMA_UNMAP_FLAG_GET_सूचीTY_BITMAP) अणु
			ret = update_user_biपंचांगap(biपंचांगap->data, iommu, dma,
						 iova, pgsize);
			अगर (ret)
				अवरोध;
		पूर्ण

		unmapped += dma->size;
		n = rb_next(n);
		vfio_हटाओ_dma(iommu, dma);
	पूर्ण

unlock:
	mutex_unlock(&iommu->lock);

	/* Report how much was unmapped */
	unmap->size = unmapped;

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_iommu_map(काष्ठा vfio_iommu *iommu, dma_addr_t iova,
			  अचिन्हित दीर्घ pfn, दीर्घ npage, पूर्णांक prot)
अणु
	काष्ठा vfio_करोमुख्य *d;
	पूर्णांक ret;

	list_क्रम_each_entry(d, &iommu->करोमुख्य_list, next) अणु
		ret = iommu_map(d->करोमुख्य, iova, (phys_addr_t)pfn << PAGE_SHIFT,
				npage << PAGE_SHIFT, prot | d->prot);
		अगर (ret)
			जाओ unwind;

		cond_resched();
	पूर्ण

	वापस 0;

unwind:
	list_क्रम_each_entry_जारी_reverse(d, &iommu->करोमुख्य_list, next) अणु
		iommu_unmap(d->करोमुख्य, iova, npage << PAGE_SHIFT);
		cond_resched();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_pin_map_dma(काष्ठा vfio_iommu *iommu, काष्ठा vfio_dma *dma,
			    माप_प्रकार map_size)
अणु
	dma_addr_t iova = dma->iova;
	अचिन्हित दीर्घ vaddr = dma->vaddr;
	काष्ठा vfio_batch batch;
	माप_प्रकार size = map_size;
	दीर्घ npage;
	अचिन्हित दीर्घ pfn, limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	पूर्णांक ret = 0;

	vfio_batch_init(&batch);

	जबतक (size) अणु
		/* Pin a contiguous chunk of memory */
		npage = vfio_pin_pages_remote(dma, vaddr + dma->size,
					      size >> PAGE_SHIFT, &pfn, limit,
					      &batch);
		अगर (npage <= 0) अणु
			WARN_ON(!npage);
			ret = (पूर्णांक)npage;
			अवरोध;
		पूर्ण

		/* Map it! */
		ret = vfio_iommu_map(iommu, iova + dma->size, pfn, npage,
				     dma->prot);
		अगर (ret) अणु
			vfio_unpin_pages_remote(dma, iova + dma->size, pfn,
						npage, true);
			vfio_batch_unpin(&batch, dma);
			अवरोध;
		पूर्ण

		size -= npage << PAGE_SHIFT;
		dma->size += npage << PAGE_SHIFT;
	पूर्ण

	vfio_batch_fini(&batch);
	dma->iommu_mapped = true;

	अगर (ret)
		vfio_हटाओ_dma(iommu, dma);

	वापस ret;
पूर्ण

/*
 * Check dma map request is within a valid iova range
 */
अटल bool vfio_iommu_iova_dma_valid(काष्ठा vfio_iommu *iommu,
				      dma_addr_t start, dma_addr_t end)
अणु
	काष्ठा list_head *iova = &iommu->ioबहु_सूची;
	काष्ठा vfio_iova *node;

	list_क्रम_each_entry(node, iova, list) अणु
		अगर (start >= node->start && end <= node->end)
			वापस true;
	पूर्ण

	/*
	 * Check क्रम list_empty() as well since a container with
	 * a single mdev device will have an empty list.
	 */
	वापस list_empty(iova);
पूर्ण

अटल पूर्णांक vfio_dma_करो_map(काष्ठा vfio_iommu *iommu,
			   काष्ठा vfio_iommu_type1_dma_map *map)
अणु
	bool set_vaddr = map->flags & VFIO_DMA_MAP_FLAG_VADDR;
	dma_addr_t iova = map->iova;
	अचिन्हित दीर्घ vaddr = map->vaddr;
	माप_प्रकार size = map->size;
	पूर्णांक ret = 0, prot = 0;
	माप_प्रकार pgsize;
	काष्ठा vfio_dma *dma;

	/* Verअगरy that none of our __u64 fields overflow */
	अगर (map->size != size || map->vaddr != vaddr || map->iova != iova)
		वापस -EINVAL;

	/* READ/WRITE from device perspective */
	अगर (map->flags & VFIO_DMA_MAP_FLAG_WRITE)
		prot |= IOMMU_WRITE;
	अगर (map->flags & VFIO_DMA_MAP_FLAG_READ)
		prot |= IOMMU_READ;

	अगर ((prot && set_vaddr) || (!prot && !set_vaddr))
		वापस -EINVAL;

	mutex_lock(&iommu->lock);

	pgsize = (माप_प्रकार)1 << __ffs(iommu->pgsize_biपंचांगap);

	WARN_ON((pgsize - 1) & PAGE_MASK);

	अगर (!size || (size | iova | vaddr) & (pgsize - 1)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	/* Don't allow IOVA or भव address wrap */
	अगर (iova + size - 1 < iova || vaddr + size - 1 < vaddr) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	dma = vfio_find_dma(iommu, iova, size);
	अगर (set_vaddr) अणु
		अगर (!dma) अणु
			ret = -ENOENT;
		पूर्ण अन्यथा अगर (!dma->vaddr_invalid || dma->iova != iova ||
			   dma->size != size) अणु
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			dma->vaddr = vaddr;
			dma->vaddr_invalid = false;
			iommu->vaddr_invalid_count--;
			wake_up_all(&iommu->vaddr_रुको);
		पूर्ण
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (dma) अणु
		ret = -EEXIST;
		जाओ out_unlock;
	पूर्ण

	अगर (!iommu->dma_avail) अणु
		ret = -ENOSPC;
		जाओ out_unlock;
	पूर्ण

	अगर (!vfio_iommu_iova_dma_valid(iommu, iova, iova + size - 1)) अणु
		ret = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	dma = kzalloc(माप(*dma), GFP_KERNEL);
	अगर (!dma) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	iommu->dma_avail--;
	dma->iova = iova;
	dma->vaddr = vaddr;
	dma->prot = prot;

	/*
	 * We need to be able to both add to a task's locked memory and test
	 * against the locked memory limit and we need to be able to करो both
	 * outside of this call path as pinning can be asynchronous via the
	 * बाह्यal पूर्णांकerfaces क्रम mdev devices.  RLIMIT_MEMLOCK requires a
	 * task_काष्ठा and VM locked pages requires an mm_काष्ठा, however
	 * holding an indefinite mm reference is not recommended, thereक्रमe we
	 * only hold a reference to a task.  We could hold a reference to
	 * current, however QEMU uses this call path through vCPU thपढ़ोs,
	 * which can be समाप्तed resulting in a शून्य mm and failure in the unmap
	 * path when called via a dअगरferent thपढ़ो.  Aव्योम this problem by
	 * using the group_leader as thपढ़ोs within the same group require
	 * both CLONE_THREAD and CLONE_VM and will thereक्रमe use the same
	 * mm_काष्ठा.
	 *
	 * Previously we also used the task क्रम testing CAP_IPC_LOCK at the
	 * समय of pinning and accounting, however has_capability() makes use
	 * of real_cred, a copy-on-ग_लिखो field, so we can't guarantee that it
	 * matches group_leader, or in fact that it might not change by the
	 * समय it's evaluated.  If a process were to call MAP_DMA with
	 * CAP_IPC_LOCK but later drop it, it करोesn't make sense that they
	 * possibly see dअगरferent results क्रम an iommu_mapped vfio_dma vs
	 * बाह्यally mapped.  Thereक्रमe track CAP_IPC_LOCK in vfio_dma at the
	 * समय of calling MAP_DMA.
	 */
	get_task_काष्ठा(current->group_leader);
	dma->task = current->group_leader;
	dma->lock_cap = capable(CAP_IPC_LOCK);

	dma->pfn_list = RB_ROOT;

	/* Insert zero-sized and grow as we map chunks of it */
	vfio_link_dma(iommu, dma);

	/* Don't pin and map if container doesn't contain IOMMU capable करोमुख्य*/
	अगर (!IS_IOMMU_CAP_DOMAIN_IN_CONTAINER(iommu))
		dma->size = size;
	अन्यथा
		ret = vfio_pin_map_dma(iommu, dma, size);

	अगर (!ret && iommu->dirty_page_tracking) अणु
		ret = vfio_dma_biपंचांगap_alloc(dma, pgsize);
		अगर (ret)
			vfio_हटाओ_dma(iommu, dma);
	पूर्ण

out_unlock:
	mutex_unlock(&iommu->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_bus_type(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा bus_type **bus = data;

	अगर (*bus && *bus != dev->bus)
		वापस -EINVAL;

	*bus = dev->bus;

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_iommu_replay(काष्ठा vfio_iommu *iommu,
			     काष्ठा vfio_करोमुख्य *करोमुख्य)
अणु
	काष्ठा vfio_batch batch;
	काष्ठा vfio_करोमुख्य *d = शून्य;
	काष्ठा rb_node *n;
	अचिन्हित दीर्घ limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	पूर्णांक ret;

	ret = vfio_रुको_all_valid(iommu);
	अगर (ret < 0)
		वापस ret;

	/* Arbitrarily pick the first करोमुख्य in the list क्रम lookups */
	अगर (!list_empty(&iommu->करोमुख्य_list))
		d = list_first_entry(&iommu->करोमुख्य_list,
				     काष्ठा vfio_करोमुख्य, next);

	vfio_batch_init(&batch);

	n = rb_first(&iommu->dma_list);

	क्रम (; n; n = rb_next(n)) अणु
		काष्ठा vfio_dma *dma;
		dma_addr_t iova;

		dma = rb_entry(n, काष्ठा vfio_dma, node);
		iova = dma->iova;

		जबतक (iova < dma->iova + dma->size) अणु
			phys_addr_t phys;
			माप_प्रकार size;

			अगर (dma->iommu_mapped) अणु
				phys_addr_t p;
				dma_addr_t i;

				अगर (WARN_ON(!d)) अणु /* mapped w/o a करोमुख्य?! */
					ret = -EINVAL;
					जाओ unwind;
				पूर्ण

				phys = iommu_iova_to_phys(d->करोमुख्य, iova);

				अगर (WARN_ON(!phys)) अणु
					iova += PAGE_SIZE;
					जारी;
				पूर्ण

				size = PAGE_SIZE;
				p = phys + size;
				i = iova + size;
				जबतक (i < dma->iova + dma->size &&
				       p == iommu_iova_to_phys(d->करोमुख्य, i)) अणु
					size += PAGE_SIZE;
					p += PAGE_SIZE;
					i += PAGE_SIZE;
				पूर्ण
			पूर्ण अन्यथा अणु
				अचिन्हित दीर्घ pfn;
				अचिन्हित दीर्घ vaddr = dma->vaddr +
						     (iova - dma->iova);
				माप_प्रकार n = dma->iova + dma->size - iova;
				दीर्घ npage;

				npage = vfio_pin_pages_remote(dma, vaddr,
							      n >> PAGE_SHIFT,
							      &pfn, limit,
							      &batch);
				अगर (npage <= 0) अणु
					WARN_ON(!npage);
					ret = (पूर्णांक)npage;
					जाओ unwind;
				पूर्ण

				phys = pfn << PAGE_SHIFT;
				size = npage << PAGE_SHIFT;
			पूर्ण

			ret = iommu_map(करोमुख्य->करोमुख्य, iova, phys,
					size, dma->prot | करोमुख्य->prot);
			अगर (ret) अणु
				अगर (!dma->iommu_mapped) अणु
					vfio_unpin_pages_remote(dma, iova,
							phys >> PAGE_SHIFT,
							size >> PAGE_SHIFT,
							true);
					vfio_batch_unpin(&batch, dma);
				पूर्ण
				जाओ unwind;
			पूर्ण

			iova += size;
		पूर्ण
	पूर्ण

	/* All dmas are now mapped, defer to second tree walk क्रम unwind */
	क्रम (n = rb_first(&iommu->dma_list); n; n = rb_next(n)) अणु
		काष्ठा vfio_dma *dma = rb_entry(n, काष्ठा vfio_dma, node);

		dma->iommu_mapped = true;
	पूर्ण

	vfio_batch_fini(&batch);
	वापस 0;

unwind:
	क्रम (; n; n = rb_prev(n)) अणु
		काष्ठा vfio_dma *dma = rb_entry(n, काष्ठा vfio_dma, node);
		dma_addr_t iova;

		अगर (dma->iommu_mapped) अणु
			iommu_unmap(करोमुख्य->करोमुख्य, dma->iova, dma->size);
			जारी;
		पूर्ण

		iova = dma->iova;
		जबतक (iova < dma->iova + dma->size) अणु
			phys_addr_t phys, p;
			माप_प्रकार size;
			dma_addr_t i;

			phys = iommu_iova_to_phys(करोमुख्य->करोमुख्य, iova);
			अगर (!phys) अणु
				iova += PAGE_SIZE;
				जारी;
			पूर्ण

			size = PAGE_SIZE;
			p = phys + size;
			i = iova + size;
			जबतक (i < dma->iova + dma->size &&
			       p == iommu_iova_to_phys(करोमुख्य->करोमुख्य, i)) अणु
				size += PAGE_SIZE;
				p += PAGE_SIZE;
				i += PAGE_SIZE;
			पूर्ण

			iommu_unmap(करोमुख्य->करोमुख्य, iova, size);
			vfio_unpin_pages_remote(dma, iova, phys >> PAGE_SHIFT,
						size >> PAGE_SHIFT, true);
		पूर्ण
	पूर्ण

	vfio_batch_fini(&batch);
	वापस ret;
पूर्ण

/*
 * We change our unmap behavior slightly depending on whether the IOMMU
 * supports fine-grained superpages.  IOMMUs like AMD-Vi will use a superpage
 * क्रम practically any contiguous घातer-of-two mapping we give it.  This means
 * we करोn't need to look क्रम contiguous chunks ourselves to make unmapping
 * more efficient.  On IOMMUs with coarse-grained super pages, like Intel VT-d
 * with discrete 2M/1G/512G/1T superpages, identअगरying contiguous chunks
 * signअगरicantly boosts non-hugetlbfs mappings and करोesn't seem to hurt when
 * hugetlbfs is in use.
 */
अटल व्योम vfio_test_करोमुख्य_fgsp(काष्ठा vfio_करोमुख्य *करोमुख्य)
अणु
	काष्ठा page *pages;
	पूर्णांक ret, order = get_order(PAGE_SIZE * 2);

	pages = alloc_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!pages)
		वापस;

	ret = iommu_map(करोमुख्य->करोमुख्य, 0, page_to_phys(pages), PAGE_SIZE * 2,
			IOMMU_READ | IOMMU_WRITE | करोमुख्य->prot);
	अगर (!ret) अणु
		माप_प्रकार unmapped = iommu_unmap(करोमुख्य->करोमुख्य, 0, PAGE_SIZE);

		अगर (unmapped == PAGE_SIZE)
			iommu_unmap(करोमुख्य->करोमुख्य, PAGE_SIZE, PAGE_SIZE);
		अन्यथा
			करोमुख्य->fgsp = true;
	पूर्ण

	__मुक्त_pages(pages, order);
पूर्ण

अटल काष्ठा vfio_group *find_iommu_group(काष्ठा vfio_करोमुख्य *करोमुख्य,
					   काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा vfio_group *g;

	list_क्रम_each_entry(g, &करोमुख्य->group_list, next) अणु
		अगर (g->iommu_group == iommu_group)
			वापस g;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा vfio_group *vfio_iommu_find_iommu_group(काष्ठा vfio_iommu *iommu,
					       काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा vfio_करोमुख्य *करोमुख्य;
	काष्ठा vfio_group *group = शून्य;

	list_क्रम_each_entry(करोमुख्य, &iommu->करोमुख्य_list, next) अणु
		group = find_iommu_group(करोमुख्य, iommu_group);
		अगर (group)
			वापस group;
	पूर्ण

	अगर (iommu->बाह्यal_करोमुख्य)
		group = find_iommu_group(iommu->बाह्यal_करोमुख्य, iommu_group);

	वापस group;
पूर्ण

अटल bool vfio_iommu_has_sw_msi(काष्ठा list_head *group_resv_regions,
				  phys_addr_t *base)
अणु
	काष्ठा iommu_resv_region *region;
	bool ret = false;

	list_क्रम_each_entry(region, group_resv_regions, list) अणु
		/*
		 * The presence of any 'real' MSI regions should take
		 * precedence over the software-managed one अगर the
		 * IOMMU driver happens to advertise both types.
		 */
		अगर (region->type == IOMMU_RESV_MSI) अणु
			ret = false;
			अवरोध;
		पूर्ण

		अगर (region->type == IOMMU_RESV_SW_MSI) अणु
			*base = region->start;
			ret = true;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_mdev_attach_करोमुख्य(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(dev);
	काष्ठा iommu_करोमुख्य *करोमुख्य = data;
	काष्ठा device *iommu_device;

	iommu_device = mdev_get_iommu_device(mdev);
	अगर (iommu_device) अणु
		अगर (iommu_dev_feature_enabled(iommu_device, IOMMU_DEV_FEAT_AUX))
			वापस iommu_aux_attach_device(करोमुख्य, iommu_device);
		अन्यथा
			वापस iommu_attach_device(करोमुख्य, iommu_device);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक vfio_mdev_detach_करोमुख्य(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(dev);
	काष्ठा iommu_करोमुख्य *करोमुख्य = data;
	काष्ठा device *iommu_device;

	iommu_device = mdev_get_iommu_device(mdev);
	अगर (iommu_device) अणु
		अगर (iommu_dev_feature_enabled(iommu_device, IOMMU_DEV_FEAT_AUX))
			iommu_aux_detach_device(करोमुख्य, iommu_device);
		अन्यथा
			iommu_detach_device(करोमुख्य, iommu_device);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vfio_iommu_attach_group(काष्ठा vfio_करोमुख्य *करोमुख्य,
				   काष्ठा vfio_group *group)
अणु
	अगर (group->mdev_group)
		वापस iommu_group_क्रम_each_dev(group->iommu_group,
						करोमुख्य->करोमुख्य,
						vfio_mdev_attach_करोमुख्य);
	अन्यथा
		वापस iommu_attach_group(करोमुख्य->करोमुख्य, group->iommu_group);
पूर्ण

अटल व्योम vfio_iommu_detach_group(काष्ठा vfio_करोमुख्य *करोमुख्य,
				    काष्ठा vfio_group *group)
अणु
	अगर (group->mdev_group)
		iommu_group_क्रम_each_dev(group->iommu_group, करोमुख्य->करोमुख्य,
					 vfio_mdev_detach_करोमुख्य);
	अन्यथा
		iommu_detach_group(करोमुख्य->करोमुख्य, group->iommu_group);
पूर्ण

अटल bool vfio_bus_is_mdev(काष्ठा bus_type *bus)
अणु
	काष्ठा bus_type *mdev_bus;
	bool ret = false;

	mdev_bus = symbol_get(mdev_bus_type);
	अगर (mdev_bus) अणु
		ret = (bus == mdev_bus);
		symbol_put(mdev_bus_type);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_mdev_iommu_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा mdev_device *mdev = to_mdev_device(dev);
	काष्ठा device **old = data, *new;

	new = mdev_get_iommu_device(mdev);
	अगर (!new || (*old && *old != new))
		वापस -EINVAL;

	*old = new;

	वापस 0;
पूर्ण

/*
 * This is a helper function to insert an address range to iova list.
 * The list is initially created with a single entry corresponding to
 * the IOMMU करोमुख्य geometry to which the device group is attached.
 * The list aperture माला_लो modअगरied when a new करोमुख्य is added to the
 * container अगर the new aperture करोesn't conflict with the current one
 * or with any existing dma mappings. The list is also modअगरied to
 * exclude any reserved regions associated with the device group.
 */
अटल पूर्णांक vfio_iommu_iova_insert(काष्ठा list_head *head,
				  dma_addr_t start, dma_addr_t end)
अणु
	काष्ठा vfio_iova *region;

	region = kदो_स्मृति(माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&region->list);
	region->start = start;
	region->end = end;

	list_add_tail(&region->list, head);
	वापस 0;
पूर्ण

/*
 * Check the new iommu aperture conflicts with existing aper or with any
 * existing dma mappings.
 */
अटल bool vfio_iommu_aper_conflict(काष्ठा vfio_iommu *iommu,
				     dma_addr_t start, dma_addr_t end)
अणु
	काष्ठा vfio_iova *first, *last;
	काष्ठा list_head *iova = &iommu->ioबहु_सूची;

	अगर (list_empty(iova))
		वापस false;

	/* Disjoपूर्णांक sets, वापस conflict */
	first = list_first_entry(iova, काष्ठा vfio_iova, list);
	last = list_last_entry(iova, काष्ठा vfio_iova, list);
	अगर (start > last->end || end < first->start)
		वापस true;

	/* Check क्रम any existing dma mappings below the new start */
	अगर (start > first->start) अणु
		अगर (vfio_find_dma(iommu, first->start, start - first->start))
			वापस true;
	पूर्ण

	/* Check क्रम any existing dma mappings beyond the new end */
	अगर (end < last->end) अणु
		अगर (vfio_find_dma(iommu, end + 1, last->end - end))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Resize iommu iova aperture winकरोw. This is called only अगर the new
 * aperture has no conflict with existing aperture and dma mappings.
 */
अटल पूर्णांक vfio_iommu_aper_resize(काष्ठा list_head *iova,
				  dma_addr_t start, dma_addr_t end)
अणु
	काष्ठा vfio_iova *node, *next;

	अगर (list_empty(iova))
		वापस vfio_iommu_iova_insert(iova, start, end);

	/* Adjust iova list start */
	list_क्रम_each_entry_safe(node, next, iova, list) अणु
		अगर (start < node->start)
			अवरोध;
		अगर (start >= node->start && start < node->end) अणु
			node->start = start;
			अवरोध;
		पूर्ण
		/* Delete nodes beक्रमe new start */
		list_del(&node->list);
		kमुक्त(node);
	पूर्ण

	/* Adjust iova list end */
	list_क्रम_each_entry_safe(node, next, iova, list) अणु
		अगर (end > node->end)
			जारी;
		अगर (end > node->start && end <= node->end) अणु
			node->end = end;
			जारी;
		पूर्ण
		/* Delete nodes after new end */
		list_del(&node->list);
		kमुक्त(node);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Check reserved region conflicts with existing dma mappings
 */
अटल bool vfio_iommu_resv_conflict(काष्ठा vfio_iommu *iommu,
				     काष्ठा list_head *resv_regions)
अणु
	काष्ठा iommu_resv_region *region;

	/* Check क्रम conflict with existing dma mappings */
	list_क्रम_each_entry(region, resv_regions, list) अणु
		अगर (region->type == IOMMU_RESV_सूचीECT_RELAXABLE)
			जारी;

		अगर (vfio_find_dma(iommu, region->start, region->length))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Check iova region overlap with  reserved regions and
 * exclude them from the iommu iova range
 */
अटल पूर्णांक vfio_iommu_resv_exclude(काष्ठा list_head *iova,
				   काष्ठा list_head *resv_regions)
अणु
	काष्ठा iommu_resv_region *resv;
	काष्ठा vfio_iova *n, *next;

	list_क्रम_each_entry(resv, resv_regions, list) अणु
		phys_addr_t start, end;

		अगर (resv->type == IOMMU_RESV_सूचीECT_RELAXABLE)
			जारी;

		start = resv->start;
		end = resv->start + resv->length - 1;

		list_क्रम_each_entry_safe(n, next, iova, list) अणु
			पूर्णांक ret = 0;

			/* No overlap */
			अगर (start > n->end || end < n->start)
				जारी;
			/*
			 * Insert a new node अगर current node overlaps with the
			 * reserve region to exclude that from valid iova range.
			 * Note that, new node is inserted beक्रमe the current
			 * node and finally the current node is deleted keeping
			 * the list updated and sorted.
			 */
			अगर (start > n->start)
				ret = vfio_iommu_iova_insert(&n->list, n->start,
							     start - 1);
			अगर (!ret && end < n->end)
				ret = vfio_iommu_iova_insert(&n->list, end + 1,
							     n->end);
			अगर (ret)
				वापस ret;

			list_del(&n->list);
			kमुक्त(n);
		पूर्ण
	पूर्ण

	अगर (list_empty(iova))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम vfio_iommu_resv_मुक्त(काष्ठा list_head *resv_regions)
अणु
	काष्ठा iommu_resv_region *n, *next;

	list_क्रम_each_entry_safe(n, next, resv_regions, list) अणु
		list_del(&n->list);
		kमुक्त(n);
	पूर्ण
पूर्ण

अटल व्योम vfio_iommu_iova_मुक्त(काष्ठा list_head *iova)
अणु
	काष्ठा vfio_iova *n, *next;

	list_क्रम_each_entry_safe(n, next, iova, list) अणु
		list_del(&n->list);
		kमुक्त(n);
	पूर्ण
पूर्ण

अटल पूर्णांक vfio_iommu_iova_get_copy(काष्ठा vfio_iommu *iommu,
				    काष्ठा list_head *iova_copy)
अणु
	काष्ठा list_head *iova = &iommu->ioबहु_सूची;
	काष्ठा vfio_iova *n;
	पूर्णांक ret;

	list_क्रम_each_entry(n, iova, list) अणु
		ret = vfio_iommu_iova_insert(iova_copy, n->start, n->end);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	वापस 0;

out_मुक्त:
	vfio_iommu_iova_मुक्त(iova_copy);
	वापस ret;
पूर्ण

अटल व्योम vfio_iommu_iova_insert_copy(काष्ठा vfio_iommu *iommu,
					काष्ठा list_head *iova_copy)
अणु
	काष्ठा list_head *iova = &iommu->ioबहु_सूची;

	vfio_iommu_iova_मुक्त(iova);

	list_splice_tail(iova_copy, iova);
पूर्ण

अटल पूर्णांक vfio_iommu_type1_attach_group(व्योम *iommu_data,
					 काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;
	काष्ठा vfio_group *group;
	काष्ठा vfio_करोमुख्य *करोमुख्य, *d;
	काष्ठा bus_type *bus = शून्य;
	पूर्णांक ret;
	bool resv_msi, msi_remap;
	phys_addr_t resv_msi_base = 0;
	काष्ठा iommu_करोमुख्य_geometry *geo;
	LIST_HEAD(iova_copy);
	LIST_HEAD(group_resv_regions);

	mutex_lock(&iommu->lock);

	/* Check क्रम duplicates */
	अगर (vfio_iommu_find_iommu_group(iommu, iommu_group)) अणु
		mutex_unlock(&iommu->lock);
		वापस -EINVAL;
	पूर्ण

	group = kzalloc(माप(*group), GFP_KERNEL);
	करोमुख्य = kzalloc(माप(*करोमुख्य), GFP_KERNEL);
	अगर (!group || !करोमुख्य) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	group->iommu_group = iommu_group;

	/* Determine bus_type in order to allocate a करोमुख्य */
	ret = iommu_group_क्रम_each_dev(iommu_group, &bus, vfio_bus_type);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (vfio_bus_is_mdev(bus)) अणु
		काष्ठा device *iommu_device = शून्य;

		group->mdev_group = true;

		/* Determine the isolation type */
		ret = iommu_group_क्रम_each_dev(iommu_group, &iommu_device,
					       vfio_mdev_iommu_device);
		अगर (ret || !iommu_device) अणु
			अगर (!iommu->बाह्यal_करोमुख्य) अणु
				INIT_LIST_HEAD(&करोमुख्य->group_list);
				iommu->बाह्यal_करोमुख्य = करोमुख्य;
				vfio_update_pgsize_biपंचांगap(iommu);
			पूर्ण अन्यथा अणु
				kमुक्त(करोमुख्य);
			पूर्ण

			list_add(&group->next,
				 &iommu->बाह्यal_करोमुख्य->group_list);
			/*
			 * Non-iommu backed group cannot dirty memory directly,
			 * it can only use पूर्णांकerfaces that provide dirty
			 * tracking.
			 * The iommu scope can only be promoted with the
			 * addition of a dirty tracking group.
			 */
			group->pinned_page_dirty_scope = true;
			mutex_unlock(&iommu->lock);

			वापस 0;
		पूर्ण

		bus = iommu_device->bus;
	पूर्ण

	करोमुख्य->करोमुख्य = iommu_करोमुख्य_alloc(bus);
	अगर (!करोमुख्य->करोमुख्य) अणु
		ret = -EIO;
		जाओ out_मुक्त;
	पूर्ण

	अगर (iommu->nesting) अणु
		ret = iommu_enable_nesting(करोमुख्य->करोमुख्य);
		अगर (ret)
			जाओ out_करोमुख्य;
	पूर्ण

	ret = vfio_iommu_attach_group(करोमुख्य, group);
	अगर (ret)
		जाओ out_करोमुख्य;

	/* Get aperture info */
	geo = &करोमुख्य->करोमुख्य->geometry;
	अगर (vfio_iommu_aper_conflict(iommu, geo->aperture_start,
				     geo->aperture_end)) अणु
		ret = -EINVAL;
		जाओ out_detach;
	पूर्ण

	ret = iommu_get_group_resv_regions(iommu_group, &group_resv_regions);
	अगर (ret)
		जाओ out_detach;

	अगर (vfio_iommu_resv_conflict(iommu, &group_resv_regions)) अणु
		ret = -EINVAL;
		जाओ out_detach;
	पूर्ण

	/*
	 * We करोn't want to work on the original iova list as the list
	 * माला_लो modअगरied and in हाल of failure we have to retain the
	 * original list. Get a copy here.
	 */
	ret = vfio_iommu_iova_get_copy(iommu, &iova_copy);
	अगर (ret)
		जाओ out_detach;

	ret = vfio_iommu_aper_resize(&iova_copy, geo->aperture_start,
				     geo->aperture_end);
	अगर (ret)
		जाओ out_detach;

	ret = vfio_iommu_resv_exclude(&iova_copy, &group_resv_regions);
	अगर (ret)
		जाओ out_detach;

	resv_msi = vfio_iommu_has_sw_msi(&group_resv_regions, &resv_msi_base);

	INIT_LIST_HEAD(&करोमुख्य->group_list);
	list_add(&group->next, &करोमुख्य->group_list);

	msi_remap = irq_करोमुख्य_check_msi_remap() ||
		    iommu_capable(bus, IOMMU_CAP_INTR_REMAP);

	अगर (!allow_unsafe_पूर्णांकerrupts && !msi_remap) अणु
		pr_warn("%s: No interrupt remapping support.  Use the module param \"allow_unsafe_interrupts\" to enable VFIO IOMMU support on this platform\n",
		       __func__);
		ret = -EPERM;
		जाओ out_detach;
	पूर्ण

	अगर (iommu_capable(bus, IOMMU_CAP_CACHE_COHERENCY))
		करोमुख्य->prot |= IOMMU_CACHE;

	/*
	 * Try to match an existing compatible करोमुख्य.  We करोn't want to
	 * preclude an IOMMU driver supporting multiple bus_types and being
	 * able to include dअगरferent bus_types in the same IOMMU करोमुख्य, so
	 * we test whether the करोमुख्यs use the same iommu_ops rather than
	 * testing अगर they're on the same bus_type.
	 */
	list_क्रम_each_entry(d, &iommu->करोमुख्य_list, next) अणु
		अगर (d->करोमुख्य->ops == करोमुख्य->करोमुख्य->ops &&
		    d->prot == करोमुख्य->prot) अणु
			vfio_iommu_detach_group(करोमुख्य, group);
			अगर (!vfio_iommu_attach_group(d, group)) अणु
				list_add(&group->next, &d->group_list);
				iommu_करोमुख्य_मुक्त(करोमुख्य->करोमुख्य);
				kमुक्त(करोमुख्य);
				जाओ करोne;
			पूर्ण

			ret = vfio_iommu_attach_group(करोमुख्य, group);
			अगर (ret)
				जाओ out_करोमुख्य;
		पूर्ण
	पूर्ण

	vfio_test_करोमुख्य_fgsp(करोमुख्य);

	/* replay mappings on new करोमुख्यs */
	ret = vfio_iommu_replay(iommu, करोमुख्य);
	अगर (ret)
		जाओ out_detach;

	अगर (resv_msi) अणु
		ret = iommu_get_msi_cookie(करोमुख्य->करोमुख्य, resv_msi_base);
		अगर (ret && ret != -ENODEV)
			जाओ out_detach;
	पूर्ण

	list_add(&करोमुख्य->next, &iommu->करोमुख्य_list);
	vfio_update_pgsize_biपंचांगap(iommu);
करोne:
	/* Delete the old one and insert new iova list */
	vfio_iommu_iova_insert_copy(iommu, &iova_copy);

	/*
	 * An iommu backed group can dirty memory directly and thereक्रमe
	 * demotes the iommu scope until it declares itself dirty tracking
	 * capable via the page pinning पूर्णांकerface.
	 */
	iommu->num_non_pinned_groups++;
	mutex_unlock(&iommu->lock);
	vfio_iommu_resv_मुक्त(&group_resv_regions);

	वापस 0;

out_detach:
	vfio_iommu_detach_group(करोमुख्य, group);
out_करोमुख्य:
	iommu_करोमुख्य_मुक्त(करोमुख्य->करोमुख्य);
	vfio_iommu_iova_मुक्त(&iova_copy);
	vfio_iommu_resv_मुक्त(&group_resv_regions);
out_मुक्त:
	kमुक्त(करोमुख्य);
	kमुक्त(group);
	mutex_unlock(&iommu->lock);
	वापस ret;
पूर्ण

अटल व्योम vfio_iommu_unmap_unpin_all(काष्ठा vfio_iommu *iommu)
अणु
	काष्ठा rb_node *node;

	जबतक ((node = rb_first(&iommu->dma_list)))
		vfio_हटाओ_dma(iommu, rb_entry(node, काष्ठा vfio_dma, node));
पूर्ण

अटल व्योम vfio_iommu_unmap_unpin_reaccount(काष्ठा vfio_iommu *iommu)
अणु
	काष्ठा rb_node *n, *p;

	n = rb_first(&iommu->dma_list);
	क्रम (; n; n = rb_next(n)) अणु
		काष्ठा vfio_dma *dma;
		दीर्घ locked = 0, unlocked = 0;

		dma = rb_entry(n, काष्ठा vfio_dma, node);
		unlocked += vfio_unmap_unpin(iommu, dma, false);
		p = rb_first(&dma->pfn_list);
		क्रम (; p; p = rb_next(p)) अणु
			काष्ठा vfio_pfn *vpfn = rb_entry(p, काष्ठा vfio_pfn,
							 node);

			अगर (!is_invalid_reserved_pfn(vpfn->pfn))
				locked++;
		पूर्ण
		vfio_lock_acct(dma, locked - unlocked, true);
	पूर्ण
पूर्ण

/*
 * Called when a करोमुख्य is हटाओd in detach. It is possible that
 * the हटाओd करोमुख्य decided the iova aperture winकरोw. Modअगरy the
 * iova aperture with the smallest winकरोw among existing करोमुख्यs.
 */
अटल व्योम vfio_iommu_aper_expand(काष्ठा vfio_iommu *iommu,
				   काष्ठा list_head *iova_copy)
अणु
	काष्ठा vfio_करोमुख्य *करोमुख्य;
	काष्ठा vfio_iova *node;
	dma_addr_t start = 0;
	dma_addr_t end = (dma_addr_t)~0;

	अगर (list_empty(iova_copy))
		वापस;

	list_क्रम_each_entry(करोमुख्य, &iommu->करोमुख्य_list, next) अणु
		काष्ठा iommu_करोमुख्य_geometry *geo = &करोमुख्य->करोमुख्य->geometry;

		अगर (geo->aperture_start > start)
			start = geo->aperture_start;
		अगर (geo->aperture_end < end)
			end = geo->aperture_end;
	पूर्ण

	/* Modअगरy aperture limits. The new aper is either same or bigger */
	node = list_first_entry(iova_copy, काष्ठा vfio_iova, list);
	node->start = start;
	node = list_last_entry(iova_copy, काष्ठा vfio_iova, list);
	node->end = end;
पूर्ण

/*
 * Called when a group is detached. The reserved regions क्रम that
 * group can be part of valid iova now. But since reserved regions
 * may be duplicated among groups, populate the iova valid regions
 * list again.
 */
अटल पूर्णांक vfio_iommu_resv_refresh(काष्ठा vfio_iommu *iommu,
				   काष्ठा list_head *iova_copy)
अणु
	काष्ठा vfio_करोमुख्य *d;
	काष्ठा vfio_group *g;
	काष्ठा vfio_iova *node;
	dma_addr_t start, end;
	LIST_HEAD(resv_regions);
	पूर्णांक ret;

	अगर (list_empty(iova_copy))
		वापस -EINVAL;

	list_क्रम_each_entry(d, &iommu->करोमुख्य_list, next) अणु
		list_क्रम_each_entry(g, &d->group_list, next) अणु
			ret = iommu_get_group_resv_regions(g->iommu_group,
							   &resv_regions);
			अगर (ret)
				जाओ करोne;
		पूर्ण
	पूर्ण

	node = list_first_entry(iova_copy, काष्ठा vfio_iova, list);
	start = node->start;
	node = list_last_entry(iova_copy, काष्ठा vfio_iova, list);
	end = node->end;

	/* purge the iova list and create new one */
	vfio_iommu_iova_मुक्त(iova_copy);

	ret = vfio_iommu_aper_resize(iova_copy, start, end);
	अगर (ret)
		जाओ करोne;

	/* Exclude current reserved regions from iova ranges */
	ret = vfio_iommu_resv_exclude(iova_copy, &resv_regions);
करोne:
	vfio_iommu_resv_मुक्त(&resv_regions);
	वापस ret;
पूर्ण

अटल व्योम vfio_iommu_type1_detach_group(व्योम *iommu_data,
					  काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;
	काष्ठा vfio_करोमुख्य *करोमुख्य;
	काष्ठा vfio_group *group;
	bool update_dirty_scope = false;
	LIST_HEAD(iova_copy);

	mutex_lock(&iommu->lock);

	अगर (iommu->बाह्यal_करोमुख्य) अणु
		group = find_iommu_group(iommu->बाह्यal_करोमुख्य, iommu_group);
		अगर (group) अणु
			update_dirty_scope = !group->pinned_page_dirty_scope;
			list_del(&group->next);
			kमुक्त(group);

			अगर (list_empty(&iommu->बाह्यal_करोमुख्य->group_list)) अणु
				अगर (!IS_IOMMU_CAP_DOMAIN_IN_CONTAINER(iommu)) अणु
					WARN_ON(iommu->notअगरier.head);
					vfio_iommu_unmap_unpin_all(iommu);
				पूर्ण

				kमुक्त(iommu->बाह्यal_करोमुख्य);
				iommu->बाह्यal_करोमुख्य = शून्य;
			पूर्ण
			जाओ detach_group_करोne;
		पूर्ण
	पूर्ण

	/*
	 * Get a copy of iova list. This will be used to update
	 * and to replace the current one later. Please note that
	 * we will leave the original list as it is अगर update fails.
	 */
	vfio_iommu_iova_get_copy(iommu, &iova_copy);

	list_क्रम_each_entry(करोमुख्य, &iommu->करोमुख्य_list, next) अणु
		group = find_iommu_group(करोमुख्य, iommu_group);
		अगर (!group)
			जारी;

		vfio_iommu_detach_group(करोमुख्य, group);
		update_dirty_scope = !group->pinned_page_dirty_scope;
		list_del(&group->next);
		kमुक्त(group);
		/*
		 * Group ownership provides privilege, अगर the group list is
		 * empty, the करोमुख्य goes away. If it's the last करोमुख्य with
		 * iommu and बाह्यal करोमुख्य करोesn't exist, then all the
		 * mappings go away too. If it's the last करोमुख्य with iommu and
		 * बाह्यal करोमुख्य exist, update accounting
		 */
		अगर (list_empty(&करोमुख्य->group_list)) अणु
			अगर (list_is_singular(&iommu->करोमुख्य_list)) अणु
				अगर (!iommu->बाह्यal_करोमुख्य) अणु
					WARN_ON(iommu->notअगरier.head);
					vfio_iommu_unmap_unpin_all(iommu);
				पूर्ण अन्यथा अणु
					vfio_iommu_unmap_unpin_reaccount(iommu);
				पूर्ण
			पूर्ण
			iommu_करोमुख्य_मुक्त(करोमुख्य->करोमुख्य);
			list_del(&करोमुख्य->next);
			kमुक्त(करोमुख्य);
			vfio_iommu_aper_expand(iommu, &iova_copy);
			vfio_update_pgsize_biपंचांगap(iommu);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!vfio_iommu_resv_refresh(iommu, &iova_copy))
		vfio_iommu_iova_insert_copy(iommu, &iova_copy);
	अन्यथा
		vfio_iommu_iova_मुक्त(&iova_copy);

detach_group_करोne:
	/*
	 * Removal of a group without dirty tracking may allow the iommu scope
	 * to be promoted.
	 */
	अगर (update_dirty_scope) अणु
		iommu->num_non_pinned_groups--;
		अगर (iommu->dirty_page_tracking)
			vfio_iommu_populate_biपंचांगap_full(iommu);
	पूर्ण
	mutex_unlock(&iommu->lock);
पूर्ण

अटल व्योम *vfio_iommu_type1_खोलो(अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu *iommu;

	iommu = kzalloc(माप(*iommu), GFP_KERNEL);
	अगर (!iommu)
		वापस ERR_PTR(-ENOMEM);

	चयन (arg) अणु
	हाल VFIO_TYPE1_IOMMU:
		अवरोध;
	हाल VFIO_TYPE1_NESTING_IOMMU:
		iommu->nesting = true;
		fallthrough;
	हाल VFIO_TYPE1v2_IOMMU:
		iommu->v2 = true;
		अवरोध;
	शेष:
		kमुक्त(iommu);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	INIT_LIST_HEAD(&iommu->करोमुख्य_list);
	INIT_LIST_HEAD(&iommu->ioबहु_सूची);
	iommu->dma_list = RB_ROOT;
	iommu->dma_avail = dma_entry_limit;
	iommu->container_खोलो = true;
	mutex_init(&iommu->lock);
	BLOCKING_INIT_NOTIFIER_HEAD(&iommu->notअगरier);
	init_रुकोqueue_head(&iommu->vaddr_रुको);

	वापस iommu;
पूर्ण

अटल व्योम vfio_release_करोमुख्य(काष्ठा vfio_करोमुख्य *करोमुख्य, bool बाह्यal)
अणु
	काष्ठा vfio_group *group, *group_पंचांगp;

	list_क्रम_each_entry_safe(group, group_पंचांगp,
				 &करोमुख्य->group_list, next) अणु
		अगर (!बाह्यal)
			vfio_iommu_detach_group(करोमुख्य, group);
		list_del(&group->next);
		kमुक्त(group);
	पूर्ण

	अगर (!बाह्यal)
		iommu_करोमुख्य_मुक्त(करोमुख्य->करोमुख्य);
पूर्ण

अटल व्योम vfio_iommu_type1_release(व्योम *iommu_data)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;
	काष्ठा vfio_करोमुख्य *करोमुख्य, *करोमुख्य_पंचांगp;

	अगर (iommu->बाह्यal_करोमुख्य) अणु
		vfio_release_करोमुख्य(iommu->बाह्यal_करोमुख्य, true);
		kमुक्त(iommu->बाह्यal_करोमुख्य);
	पूर्ण

	vfio_iommu_unmap_unpin_all(iommu);

	list_क्रम_each_entry_safe(करोमुख्य, करोमुख्य_पंचांगp,
				 &iommu->करोमुख्य_list, next) अणु
		vfio_release_करोमुख्य(करोमुख्य, false);
		list_del(&करोमुख्य->next);
		kमुक्त(करोमुख्य);
	पूर्ण

	vfio_iommu_iova_मुक्त(&iommu->ioबहु_सूची);

	kमुक्त(iommu);
पूर्ण

अटल पूर्णांक vfio_करोमुख्यs_have_iommu_cache(काष्ठा vfio_iommu *iommu)
अणु
	काष्ठा vfio_करोमुख्य *करोमुख्य;
	पूर्णांक ret = 1;

	mutex_lock(&iommu->lock);
	list_क्रम_each_entry(करोमुख्य, &iommu->करोमुख्य_list, next) अणु
		अगर (!(करोमुख्य->prot & IOMMU_CACHE)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&iommu->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vfio_iommu_type1_check_extension(काष्ठा vfio_iommu *iommu,
					    अचिन्हित दीर्घ arg)
अणु
	चयन (arg) अणु
	हाल VFIO_TYPE1_IOMMU:
	हाल VFIO_TYPE1v2_IOMMU:
	हाल VFIO_TYPE1_NESTING_IOMMU:
	हाल VFIO_UNMAP_ALL:
	हाल VFIO_UPDATE_VADDR:
		वापस 1;
	हाल VFIO_DMA_CC_IOMMU:
		अगर (!iommu)
			वापस 0;
		वापस vfio_करोमुख्यs_have_iommu_cache(iommu);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक vfio_iommu_iova_add_cap(काष्ठा vfio_info_cap *caps,
		 काष्ठा vfio_iommu_type1_info_cap_iova_range *cap_iovas,
		 माप_प्रकार size)
अणु
	काष्ठा vfio_info_cap_header *header;
	काष्ठा vfio_iommu_type1_info_cap_iova_range *iova_cap;

	header = vfio_info_cap_add(caps, size,
				   VFIO_IOMMU_TYPE1_INFO_CAP_IOVA_RANGE, 1);
	अगर (IS_ERR(header))
		वापस PTR_ERR(header);

	iova_cap = container_of(header,
				काष्ठा vfio_iommu_type1_info_cap_iova_range,
				header);
	iova_cap->nr_iovas = cap_iovas->nr_iovas;
	स_नकल(iova_cap->iova_ranges, cap_iovas->iova_ranges,
	       cap_iovas->nr_iovas * माप(*cap_iovas->iova_ranges));
	वापस 0;
पूर्ण

अटल पूर्णांक vfio_iommu_iova_build_caps(काष्ठा vfio_iommu *iommu,
				      काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_iommu_type1_info_cap_iova_range *cap_iovas;
	काष्ठा vfio_iova *iova;
	माप_प्रकार size;
	पूर्णांक iovas = 0, i = 0, ret;

	list_क्रम_each_entry(iova, &iommu->ioबहु_सूची, list)
		iovas++;

	अगर (!iovas) अणु
		/*
		 * Return 0 as a container with a single mdev device
		 * will have an empty list
		 */
		वापस 0;
	पूर्ण

	size = काष्ठा_size(cap_iovas, iova_ranges, iovas);

	cap_iovas = kzalloc(size, GFP_KERNEL);
	अगर (!cap_iovas)
		वापस -ENOMEM;

	cap_iovas->nr_iovas = iovas;

	list_क्रम_each_entry(iova, &iommu->ioबहु_सूची, list) अणु
		cap_iovas->iova_ranges[i].start = iova->start;
		cap_iovas->iova_ranges[i].end = iova->end;
		i++;
	पूर्ण

	ret = vfio_iommu_iova_add_cap(caps, cap_iovas, size);

	kमुक्त(cap_iovas);
	वापस ret;
पूर्ण

अटल पूर्णांक vfio_iommu_migration_build_caps(काष्ठा vfio_iommu *iommu,
					   काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_iommu_type1_info_cap_migration cap_mig;

	cap_mig.header.id = VFIO_IOMMU_TYPE1_INFO_CAP_MIGRATION;
	cap_mig.header.version = 1;

	cap_mig.flags = 0;
	/* support minimum pgsize */
	cap_mig.pgsize_biपंचांगap = (माप_प्रकार)1 << __ffs(iommu->pgsize_biपंचांगap);
	cap_mig.max_dirty_biपंचांगap_size = सूचीTY_BITMAP_SIZE_MAX;

	वापस vfio_info_add_capability(caps, &cap_mig.header, माप(cap_mig));
पूर्ण

अटल पूर्णांक vfio_iommu_dma_avail_build_caps(काष्ठा vfio_iommu *iommu,
					   काष्ठा vfio_info_cap *caps)
अणु
	काष्ठा vfio_iommu_type1_info_dma_avail cap_dma_avail;

	cap_dma_avail.header.id = VFIO_IOMMU_TYPE1_INFO_DMA_AVAIL;
	cap_dma_avail.header.version = 1;

	cap_dma_avail.avail = iommu->dma_avail;

	वापस vfio_info_add_capability(caps, &cap_dma_avail.header,
					माप(cap_dma_avail));
पूर्ण

अटल पूर्णांक vfio_iommu_type1_get_info(काष्ठा vfio_iommu *iommu,
				     अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu_type1_info info;
	अचिन्हित दीर्घ minsz;
	काष्ठा vfio_info_cap caps = अणु .buf = शून्य, .size = 0 पूर्ण;
	अचिन्हित दीर्घ capsz;
	पूर्णांक ret;

	minsz = दुरत्वend(काष्ठा vfio_iommu_type1_info, iova_pgsizes);

	/* For backward compatibility, cannot require this */
	capsz = दुरत्वend(काष्ठा vfio_iommu_type1_info, cap_offset);

	अगर (copy_from_user(&info, (व्योम __user *)arg, minsz))
		वापस -EFAULT;

	अगर (info.argsz < minsz)
		वापस -EINVAL;

	अगर (info.argsz >= capsz) अणु
		minsz = capsz;
		info.cap_offset = 0; /* output, no-recopy necessary */
	पूर्ण

	mutex_lock(&iommu->lock);
	info.flags = VFIO_IOMMU_INFO_PGSIZES;

	info.iova_pgsizes = iommu->pgsize_biपंचांगap;

	ret = vfio_iommu_migration_build_caps(iommu, &caps);

	अगर (!ret)
		ret = vfio_iommu_dma_avail_build_caps(iommu, &caps);

	अगर (!ret)
		ret = vfio_iommu_iova_build_caps(iommu, &caps);

	mutex_unlock(&iommu->lock);

	अगर (ret)
		वापस ret;

	अगर (caps.size) अणु
		info.flags |= VFIO_IOMMU_INFO_CAPS;

		अगर (info.argsz < माप(info) + caps.size) अणु
			info.argsz = माप(info) + caps.size;
		पूर्ण अन्यथा अणु
			vfio_info_cap_shअगरt(&caps, माप(info));
			अगर (copy_to_user((व्योम __user *)arg +
					माप(info), caps.buf,
					caps.size)) अणु
				kमुक्त(caps.buf);
				वापस -EFAULT;
			पूर्ण
			info.cap_offset = माप(info);
		पूर्ण

		kमुक्त(caps.buf);
	पूर्ण

	वापस copy_to_user((व्योम __user *)arg, &info, minsz) ?
			-EFAULT : 0;
पूर्ण

अटल पूर्णांक vfio_iommu_type1_map_dma(काष्ठा vfio_iommu *iommu,
				    अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu_type1_dma_map map;
	अचिन्हित दीर्घ minsz;
	uपूर्णांक32_t mask = VFIO_DMA_MAP_FLAG_READ | VFIO_DMA_MAP_FLAG_WRITE |
			VFIO_DMA_MAP_FLAG_VADDR;

	minsz = दुरत्वend(काष्ठा vfio_iommu_type1_dma_map, size);

	अगर (copy_from_user(&map, (व्योम __user *)arg, minsz))
		वापस -EFAULT;

	अगर (map.argsz < minsz || map.flags & ~mask)
		वापस -EINVAL;

	वापस vfio_dma_करो_map(iommu, &map);
पूर्ण

अटल पूर्णांक vfio_iommu_type1_unmap_dma(काष्ठा vfio_iommu *iommu,
				      अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu_type1_dma_unmap unmap;
	काष्ठा vfio_biपंचांगap biपंचांगap = अणु 0 पूर्ण;
	uपूर्णांक32_t mask = VFIO_DMA_UNMAP_FLAG_GET_सूचीTY_BITMAP |
			VFIO_DMA_UNMAP_FLAG_VADDR |
			VFIO_DMA_UNMAP_FLAG_ALL;
	अचिन्हित दीर्घ minsz;
	पूर्णांक ret;

	minsz = दुरत्वend(काष्ठा vfio_iommu_type1_dma_unmap, size);

	अगर (copy_from_user(&unmap, (व्योम __user *)arg, minsz))
		वापस -EFAULT;

	अगर (unmap.argsz < minsz || unmap.flags & ~mask)
		वापस -EINVAL;

	अगर ((unmap.flags & VFIO_DMA_UNMAP_FLAG_GET_सूचीTY_BITMAP) &&
	    (unmap.flags & (VFIO_DMA_UNMAP_FLAG_ALL |
			    VFIO_DMA_UNMAP_FLAG_VADDR)))
		वापस -EINVAL;

	अगर (unmap.flags & VFIO_DMA_UNMAP_FLAG_GET_सूचीTY_BITMAP) अणु
		अचिन्हित दीर्घ pgshअगरt;

		अगर (unmap.argsz < (minsz + माप(biपंचांगap)))
			वापस -EINVAL;

		अगर (copy_from_user(&biपंचांगap,
				   (व्योम __user *)(arg + minsz),
				   माप(biपंचांगap)))
			वापस -EFAULT;

		अगर (!access_ok((व्योम __user *)biपंचांगap.data, biपंचांगap.size))
			वापस -EINVAL;

		pgshअगरt = __ffs(biपंचांगap.pgsize);
		ret = verअगरy_biपंचांगap_size(unmap.size >> pgshअगरt,
					 biपंचांगap.size);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = vfio_dma_करो_unmap(iommu, &unmap, &biपंचांगap);
	अगर (ret)
		वापस ret;

	वापस copy_to_user((व्योम __user *)arg, &unmap, minsz) ?
			-EFAULT : 0;
पूर्ण

अटल पूर्णांक vfio_iommu_type1_dirty_pages(काष्ठा vfio_iommu *iommu,
					अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu_type1_dirty_biपंचांगap dirty;
	uपूर्णांक32_t mask = VFIO_IOMMU_सूचीTY_PAGES_FLAG_START |
			VFIO_IOMMU_सूचीTY_PAGES_FLAG_STOP |
			VFIO_IOMMU_सूचीTY_PAGES_FLAG_GET_BITMAP;
	अचिन्हित दीर्घ minsz;
	पूर्णांक ret = 0;

	अगर (!iommu->v2)
		वापस -EACCES;

	minsz = दुरत्वend(काष्ठा vfio_iommu_type1_dirty_biपंचांगap, flags);

	अगर (copy_from_user(&dirty, (व्योम __user *)arg, minsz))
		वापस -EFAULT;

	अगर (dirty.argsz < minsz || dirty.flags & ~mask)
		वापस -EINVAL;

	/* only one flag should be set at a समय */
	अगर (__ffs(dirty.flags) != __fls(dirty.flags))
		वापस -EINVAL;

	अगर (dirty.flags & VFIO_IOMMU_सूचीTY_PAGES_FLAG_START) अणु
		माप_प्रकार pgsize;

		mutex_lock(&iommu->lock);
		pgsize = 1 << __ffs(iommu->pgsize_biपंचांगap);
		अगर (!iommu->dirty_page_tracking) अणु
			ret = vfio_dma_biपंचांगap_alloc_all(iommu, pgsize);
			अगर (!ret)
				iommu->dirty_page_tracking = true;
		पूर्ण
		mutex_unlock(&iommu->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (dirty.flags & VFIO_IOMMU_सूचीTY_PAGES_FLAG_STOP) अणु
		mutex_lock(&iommu->lock);
		अगर (iommu->dirty_page_tracking) अणु
			iommu->dirty_page_tracking = false;
			vfio_dma_biपंचांगap_मुक्त_all(iommu);
		पूर्ण
		mutex_unlock(&iommu->lock);
		वापस 0;
	पूर्ण अन्यथा अगर (dirty.flags & VFIO_IOMMU_सूचीTY_PAGES_FLAG_GET_BITMAP) अणु
		काष्ठा vfio_iommu_type1_dirty_biपंचांगap_get range;
		अचिन्हित दीर्घ pgshअगरt;
		माप_प्रकार data_size = dirty.argsz - minsz;
		माप_प्रकार iommu_pgsize;

		अगर (!data_size || data_size < माप(range))
			वापस -EINVAL;

		अगर (copy_from_user(&range, (व्योम __user *)(arg + minsz),
				   माप(range)))
			वापस -EFAULT;

		अगर (range.iova + range.size < range.iova)
			वापस -EINVAL;
		अगर (!access_ok((व्योम __user *)range.biपंचांगap.data,
			       range.biपंचांगap.size))
			वापस -EINVAL;

		pgshअगरt = __ffs(range.biपंचांगap.pgsize);
		ret = verअगरy_biपंचांगap_size(range.size >> pgshअगरt,
					 range.biपंचांगap.size);
		अगर (ret)
			वापस ret;

		mutex_lock(&iommu->lock);

		iommu_pgsize = (माप_प्रकार)1 << __ffs(iommu->pgsize_biपंचांगap);

		/* allow only smallest supported pgsize */
		अगर (range.biपंचांगap.pgsize != iommu_pgsize) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		अगर (range.iova & (iommu_pgsize - 1)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण
		अगर (!range.size || range.size & (iommu_pgsize - 1)) अणु
			ret = -EINVAL;
			जाओ out_unlock;
		पूर्ण

		अगर (iommu->dirty_page_tracking)
			ret = vfio_iova_dirty_biपंचांगap(range.biपंचांगap.data,
						     iommu, range.iova,
						     range.size,
						     range.biपंचांगap.pgsize);
		अन्यथा
			ret = -EINVAL;
out_unlock:
		mutex_unlock(&iommu->lock);

		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल दीर्घ vfio_iommu_type1_ioctl(व्योम *iommu_data,
				   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;

	चयन (cmd) अणु
	हाल VFIO_CHECK_EXTENSION:
		वापस vfio_iommu_type1_check_extension(iommu, arg);
	हाल VFIO_IOMMU_GET_INFO:
		वापस vfio_iommu_type1_get_info(iommu, arg);
	हाल VFIO_IOMMU_MAP_DMA:
		वापस vfio_iommu_type1_map_dma(iommu, arg);
	हाल VFIO_IOMMU_UNMAP_DMA:
		वापस vfio_iommu_type1_unmap_dma(iommu, arg);
	हाल VFIO_IOMMU_सूचीTY_PAGES:
		वापस vfio_iommu_type1_dirty_pages(iommu, arg);
	शेष:
		वापस -ENOTTY;
	पूर्ण
पूर्ण

अटल पूर्णांक vfio_iommu_type1_रेजिस्टर_notअगरier(व्योम *iommu_data,
					      अचिन्हित दीर्घ *events,
					      काष्ठा notअगरier_block *nb)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;

	/* clear known events */
	*events &= ~VFIO_IOMMU_NOTIFY_DMA_UNMAP;

	/* refuse to रेजिस्टर अगर still events reमुख्यing */
	अगर (*events)
		वापस -EINVAL;

	वापस blocking_notअगरier_chain_रेजिस्टर(&iommu->notअगरier, nb);
पूर्ण

अटल पूर्णांक vfio_iommu_type1_unरेजिस्टर_notअगरier(व्योम *iommu_data,
						काष्ठा notअगरier_block *nb)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;

	वापस blocking_notअगरier_chain_unरेजिस्टर(&iommu->notअगरier, nb);
पूर्ण

अटल पूर्णांक vfio_iommu_type1_dma_rw_chunk(काष्ठा vfio_iommu *iommu,
					 dma_addr_t user_iova, व्योम *data,
					 माप_प्रकार count, bool ग_लिखो,
					 माप_प्रकार *copied)
अणु
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ vaddr;
	काष्ठा vfio_dma *dma;
	bool kthपढ़ो = current->mm == शून्य;
	माप_प्रकार offset;
	पूर्णांक ret;

	*copied = 0;

	ret = vfio_find_dma_valid(iommu, user_iova, 1, &dma);
	अगर (ret < 0)
		वापस ret;

	अगर ((ग_लिखो && !(dma->prot & IOMMU_WRITE)) ||
			!(dma->prot & IOMMU_READ))
		वापस -EPERM;

	mm = get_task_mm(dma->task);

	अगर (!mm)
		वापस -EPERM;

	अगर (kthपढ़ो)
		kthपढ़ो_use_mm(mm);
	अन्यथा अगर (current->mm != mm)
		जाओ out;

	offset = user_iova - dma->iova;

	अगर (count > dma->size - offset)
		count = dma->size - offset;

	vaddr = dma->vaddr + offset;

	अगर (ग_लिखो) अणु
		*copied = copy_to_user((व्योम __user *)vaddr, data,
					 count) ? 0 : count;
		अगर (*copied && iommu->dirty_page_tracking) अणु
			अचिन्हित दीर्घ pgshअगरt = __ffs(iommu->pgsize_biपंचांगap);
			/*
			 * Biपंचांगap populated with the smallest supported page
			 * size
			 */
			biपंचांगap_set(dma->biपंचांगap, offset >> pgshअगरt,
				   ((offset + *copied - 1) >> pgshअगरt) -
				   (offset >> pgshअगरt) + 1);
		पूर्ण
	पूर्ण अन्यथा
		*copied = copy_from_user(data, (व्योम __user *)vaddr,
					   count) ? 0 : count;
	अगर (kthपढ़ो)
		kthपढ़ो_unuse_mm(mm);
out:
	mmput(mm);
	वापस *copied ? 0 : -EFAULT;
पूर्ण

अटल पूर्णांक vfio_iommu_type1_dma_rw(व्योम *iommu_data, dma_addr_t user_iova,
				   व्योम *data, माप_प्रकार count, bool ग_लिखो)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;
	पूर्णांक ret = 0;
	माप_प्रकार करोne;

	mutex_lock(&iommu->lock);
	जबतक (count > 0) अणु
		ret = vfio_iommu_type1_dma_rw_chunk(iommu, user_iova, data,
						    count, ग_लिखो, &करोne);
		अगर (ret)
			अवरोध;

		count -= करोne;
		data += करोne;
		user_iova += करोne;
	पूर्ण

	mutex_unlock(&iommu->lock);
	वापस ret;
पूर्ण

अटल काष्ठा iommu_करोमुख्य *
vfio_iommu_type1_group_iommu_करोमुख्य(व्योम *iommu_data,
				    काष्ठा iommu_group *iommu_group)
अणु
	काष्ठा iommu_करोमुख्य *करोमुख्य = ERR_PTR(-ENODEV);
	काष्ठा vfio_iommu *iommu = iommu_data;
	काष्ठा vfio_करोमुख्य *d;

	अगर (!iommu || !iommu_group)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&iommu->lock);
	list_क्रम_each_entry(d, &iommu->करोमुख्य_list, next) अणु
		अगर (find_iommu_group(d, iommu_group)) अणु
			करोमुख्य = d->करोमुख्य;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&iommu->lock);

	वापस करोमुख्य;
पूर्ण

अटल व्योम vfio_iommu_type1_notअगरy(व्योम *iommu_data,
				    क्रमागत vfio_iommu_notअगरy_type event)
अणु
	काष्ठा vfio_iommu *iommu = iommu_data;

	अगर (event != VFIO_IOMMU_CONTAINER_CLOSE)
		वापस;
	mutex_lock(&iommu->lock);
	iommu->container_खोलो = false;
	mutex_unlock(&iommu->lock);
	wake_up_all(&iommu->vaddr_रुको);
पूर्ण

अटल स्थिर काष्ठा vfio_iommu_driver_ops vfio_iommu_driver_ops_type1 = अणु
	.name			= "vfio-iommu-type1",
	.owner			= THIS_MODULE,
	.खोलो			= vfio_iommu_type1_खोलो,
	.release		= vfio_iommu_type1_release,
	.ioctl			= vfio_iommu_type1_ioctl,
	.attach_group		= vfio_iommu_type1_attach_group,
	.detach_group		= vfio_iommu_type1_detach_group,
	.pin_pages		= vfio_iommu_type1_pin_pages,
	.unpin_pages		= vfio_iommu_type1_unpin_pages,
	.रेजिस्टर_notअगरier	= vfio_iommu_type1_रेजिस्टर_notअगरier,
	.unरेजिस्टर_notअगरier	= vfio_iommu_type1_unरेजिस्टर_notअगरier,
	.dma_rw			= vfio_iommu_type1_dma_rw,
	.group_iommu_करोमुख्य	= vfio_iommu_type1_group_iommu_करोमुख्य,
	.notअगरy			= vfio_iommu_type1_notअगरy,
पूर्ण;

अटल पूर्णांक __init vfio_iommu_type1_init(व्योम)
अणु
	वापस vfio_रेजिस्टर_iommu_driver(&vfio_iommu_driver_ops_type1);
पूर्ण

अटल व्योम __निकास vfio_iommu_type1_cleanup(व्योम)
अणु
	vfio_unरेजिस्टर_iommu_driver(&vfio_iommu_driver_ops_type1);
पूर्ण

module_init(vfio_iommu_type1_init);
module_निकास(vfio_iommu_type1_cleanup);

MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
