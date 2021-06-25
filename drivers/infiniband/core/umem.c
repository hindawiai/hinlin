<शैली गुरु>
/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2020 Intel Corporation. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
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
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/count_zeros.h>
#समावेश <rdma/ib_umem_odp.h>

#समावेश "uverbs.h"

अटल व्योम __ib_umem_release(काष्ठा ib_device *dev, काष्ठा ib_umem *umem, पूर्णांक dirty)
अणु
	bool make_dirty = umem->writable && dirty;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	अगर (umem->nmap > 0)
		ib_dma_unmap_sg(dev, umem->sg_head.sgl, umem->sg_nents,
				DMA_BIसूचीECTIONAL);

	क्रम_each_sg(umem->sg_head.sgl, sg, umem->sg_nents, i)
		unpin_user_page_range_dirty_lock(sg_page(sg),
			DIV_ROUND_UP(sg->length, PAGE_SIZE), make_dirty);

	sg_मुक्त_table(&umem->sg_head);
पूर्ण

/**
 * ib_umem_find_best_pgsz - Find best HW page size to use क्रम this MR
 *
 * @umem: umem काष्ठा
 * @pgsz_biपंचांगap: biपंचांगap of HW supported page sizes
 * @virt: IOVA
 *
 * This helper is पूर्णांकended क्रम HW that support multiple page
 * sizes but can करो only a single page size in an MR.
 *
 * Returns 0 अगर the umem requires page sizes not supported by
 * the driver to be mapped. Drivers always supporting PAGE_SIZE
 * or smaller will never see a 0 result.
 */
अचिन्हित दीर्घ ib_umem_find_best_pgsz(काष्ठा ib_umem *umem,
				     अचिन्हित दीर्घ pgsz_biपंचांगap,
				     अचिन्हित दीर्घ virt)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ va, pgoff;
	dma_addr_t mask;
	पूर्णांक i;

	अगर (umem->is_odp) अणु
		अचिन्हित पूर्णांक page_size = BIT(to_ib_umem_odp(umem)->page_shअगरt);

		/* ODP must always be self consistent. */
		अगर (!(pgsz_biपंचांगap & page_size))
			वापस 0;
		वापस page_size;
	पूर्ण

	/* rdma_क्रम_each_block() has a bug अगर the page size is smaller than the
	 * page size used to build the umem. For now prevent smaller page sizes
	 * from being वापसed.
	 */
	pgsz_biपंचांगap &= GENMASK(BITS_PER_LONG - 1, PAGE_SHIFT);

	umem->iova = va = virt;
	/* The best result is the smallest page size that results in the minimum
	 * number of required pages. Compute the largest page size that could
	 * work based on VA address bits that करोn't change.
	 */
	mask = pgsz_biपंचांगap &
	       GENMASK(BITS_PER_LONG - 1,
		       bits_per((umem->length - 1 + virt) ^ virt));
	/* offset पूर्णांकo first SGL */
	pgoff = umem->address & ~PAGE_MASK;

	क्रम_each_sg(umem->sg_head.sgl, sg, umem->nmap, i) अणु
		/* Walk SGL and reduce max page size अगर VA/PA bits dअगरfer
		 * क्रम any address.
		 */
		mask |= (sg_dma_address(sg) + pgoff) ^ va;
		va += sg_dma_len(sg) - pgoff;
		/* Except क्रम the last entry, the ending iova alignment sets
		 * the maximum possible page size as the low bits of the iova
		 * must be zero when starting the next chunk.
		 */
		अगर (i != (umem->nmap - 1))
			mask |= va;
		pgoff = 0;
	पूर्ण

	/* The mask accumulates 1's in each position where the VA and physical
	 * address dअगरfer, thus the length of trailing 0 is the largest page
	 * size that can pass the VA through to the physical.
	 */
	अगर (mask)
		pgsz_biपंचांगap &= GENMASK(count_trailing_zeros(mask), 0);
	वापस pgsz_biपंचांगap ? roundकरोwn_घात_of_two(pgsz_biपंचांगap) : 0;
पूर्ण
EXPORT_SYMBOL(ib_umem_find_best_pgsz);

/**
 * ib_umem_get - Pin and DMA map userspace memory.
 *
 * @device: IB device to connect UMEM
 * @addr: userspace भव address to start at
 * @size: length of region to pin
 * @access: IB_ACCESS_xxx flags क्रम memory being pinned
 */
काष्ठा ib_umem *ib_umem_get(काष्ठा ib_device *device, अचिन्हित दीर्घ addr,
			    माप_प्रकार size, पूर्णांक access)
अणु
	काष्ठा ib_umem *umem;
	काष्ठा page **page_list;
	अचिन्हित दीर्घ lock_limit;
	अचिन्हित दीर्घ new_pinned;
	अचिन्हित दीर्घ cur_base;
	अचिन्हित दीर्घ dma_attr = 0;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ npages;
	पूर्णांक ret;
	काष्ठा scatterlist *sg = शून्य;
	अचिन्हित पूर्णांक gup_flags = FOLL_WRITE;

	/*
	 * If the combination of the addr and size requested क्रम this memory
	 * region causes an पूर्णांकeger overflow, वापस error.
	 */
	अगर (((addr + size) < addr) ||
	    PAGE_ALIGN(addr + size) < (addr + size))
		वापस ERR_PTR(-EINVAL);

	अगर (!can_करो_mlock())
		वापस ERR_PTR(-EPERM);

	अगर (access & IB_ACCESS_ON_DEMAND)
		वापस ERR_PTR(-EOPNOTSUPP);

	umem = kzalloc(माप(*umem), GFP_KERNEL);
	अगर (!umem)
		वापस ERR_PTR(-ENOMEM);
	umem->ibdev      = device;
	umem->length     = size;
	umem->address    = addr;
	/*
	 * Drivers should call ib_umem_find_best_pgsz() to set the iova
	 * correctly.
	 */
	umem->iova = addr;
	umem->writable   = ib_access_writable(access);
	umem->owning_mm = mm = current->mm;
	mmgrab(mm);

	page_list = (काष्ठा page **) __get_मुक्त_page(GFP_KERNEL);
	अगर (!page_list) अणु
		ret = -ENOMEM;
		जाओ umem_kमुक्त;
	पूर्ण

	npages = ib_umem_num_pages(umem);
	अगर (npages == 0 || npages > अच_पूर्णांक_उच्च) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;

	new_pinned = atomic64_add_वापस(npages, &mm->pinned_vm);
	अगर (new_pinned > lock_limit && !capable(CAP_IPC_LOCK)) अणु
		atomic64_sub(npages, &mm->pinned_vm);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	cur_base = addr & PAGE_MASK;

	अगर (!umem->writable)
		gup_flags |= FOLL_FORCE;

	जबतक (npages) अणु
		cond_resched();
		ret = pin_user_pages_fast(cur_base,
					  min_t(अचिन्हित दीर्घ, npages,
						PAGE_SIZE /
						माप(काष्ठा page *)),
					  gup_flags | FOLL_LONGTERM, page_list);
		अगर (ret < 0)
			जाओ umem_release;

		cur_base += ret * PAGE_SIZE;
		npages -= ret;
		sg = __sg_alloc_table_from_pages(&umem->sg_head, page_list, ret,
				0, ret << PAGE_SHIFT,
				ib_dma_max_seg_size(device), sg, npages,
				GFP_KERNEL);
		umem->sg_nents = umem->sg_head.nents;
		अगर (IS_ERR(sg)) अणु
			unpin_user_pages_dirty_lock(page_list, ret, 0);
			ret = PTR_ERR(sg);
			जाओ umem_release;
		पूर्ण
	पूर्ण

	अगर (access & IB_ACCESS_RELAXED_ORDERING)
		dma_attr |= DMA_ATTR_WEAK_ORDERING;

	umem->nmap =
		ib_dma_map_sg_attrs(device, umem->sg_head.sgl, umem->sg_nents,
				    DMA_BIसूचीECTIONAL, dma_attr);

	अगर (!umem->nmap) अणु
		ret = -ENOMEM;
		जाओ umem_release;
	पूर्ण

	ret = 0;
	जाओ out;

umem_release:
	__ib_umem_release(device, umem, 0);
	atomic64_sub(ib_umem_num_pages(umem), &mm->pinned_vm);
out:
	मुक्त_page((अचिन्हित दीर्घ) page_list);
umem_kमुक्त:
	अगर (ret) अणु
		mmdrop(umem->owning_mm);
		kमुक्त(umem);
	पूर्ण
	वापस ret ? ERR_PTR(ret) : umem;
पूर्ण
EXPORT_SYMBOL(ib_umem_get);

/**
 * ib_umem_release - release memory pinned with ib_umem_get
 * @umem: umem काष्ठा to release
 */
व्योम ib_umem_release(काष्ठा ib_umem *umem)
अणु
	अगर (!umem)
		वापस;
	अगर (umem->is_dmabuf)
		वापस ib_umem_dmabuf_release(to_ib_umem_dmabuf(umem));
	अगर (umem->is_odp)
		वापस ib_umem_odp_release(to_ib_umem_odp(umem));

	__ib_umem_release(umem->ibdev, umem, 1);

	atomic64_sub(ib_umem_num_pages(umem), &umem->owning_mm->pinned_vm);
	mmdrop(umem->owning_mm);
	kमुक्त(umem);
पूर्ण
EXPORT_SYMBOL(ib_umem_release);

/*
 * Copy from the given ib_umem's pages to the given buffer.
 *
 * umem - the umem to copy from
 * offset - offset to start copying from
 * dst - destination buffer
 * length - buffer length
 *
 * Returns 0 on success, or an error code.
 */
पूर्णांक ib_umem_copy_from(व्योम *dst, काष्ठा ib_umem *umem, माप_प्रकार offset,
		      माप_प्रकार length)
अणु
	माप_प्रकार end = offset + length;
	पूर्णांक ret;

	अगर (offset > umem->length || length > umem->length - offset) अणु
		pr_err("%s not in range. offset: %zd umem length: %zd end: %zd\n",
		       __func__, offset, umem->length, end);
		वापस -EINVAL;
	पूर्ण

	ret = sg_pcopy_to_buffer(umem->sg_head.sgl, umem->sg_nents, dst, length,
				 offset + ib_umem_offset(umem));

	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != length)
		वापस -EINVAL;
	अन्यथा
		वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_umem_copy_from);
