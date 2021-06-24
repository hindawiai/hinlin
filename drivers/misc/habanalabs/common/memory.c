<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 */

#समावेश <uapi/misc/habanaद_असल.h>
#समावेश "habanalabs.h"
#समावेश "../include/hw_ip/mmu/mmu_general.h"

#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>

#घोषणा HL_MMU_DEBUG	0

/* use small pages क्रम supporting non-घात2 (32M/40M/48M) DRAM phys page sizes */
#घोषणा DRAM_POOL_PAGE_SIZE SZ_8M

/*
 * The va ranges in context object contain a list with the available chunks of
 * device भव memory.
 * There is one range क्रम host allocations and one क्रम DRAM allocations.
 *
 * On initialization each range contains one chunk of all of its available
 * भव range which is a half of the total device भव range.
 *
 * On each mapping of physical pages, a suitable भव range chunk (with a
 * minimum size) is selected from the list. If the chunk size equals the
 * requested size, the chunk is वापसed. Otherwise, the chunk is split पूर्णांकo
 * two chunks - one to वापस as result and a reमुख्यder to stay in the list.
 *
 * On each Unmapping of a भव address, the relevant भव chunk is
 * वापसed to the list. The chunk is added to the list and अगर its edges match
 * the edges of the adjacent chunks (means a contiguous chunk can be created),
 * the chunks are merged.
 *
 * On finish, the list is checked to have only one chunk of all the relevant
 * भव range (which is a half of the device total भव range).
 * If not (means not all mappings were unmapped), a warning is prपूर्णांकed.
 */

/*
 * alloc_device_memory() - allocate device memory.
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @args: host parameters containing the requested size.
 * @ret_handle: result handle.
 *
 * This function करोes the following:
 * - Allocate the requested size rounded up to 'dram_page_size' pages.
 * - Return unique handle क्रम later map/unmap/मुक्त.
 */
अटल पूर्णांक alloc_device_memory(काष्ठा hl_ctx *ctx, काष्ठा hl_mem_in *args,
				u32 *ret_handle)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_vm *vm = &hdev->vm;
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack;
	u64 paddr = 0, total_size, num_pgs, i;
	u32 num_curr_pgs, page_size;
	पूर्णांक handle, rc;
	bool contiguous;

	num_curr_pgs = 0;
	page_size = hdev->asic_prop.dram_page_size;
	num_pgs = DIV_ROUND_UP_ULL(args->alloc.mem_size, page_size);
	total_size = num_pgs * page_size;

	अगर (!total_size) अणु
		dev_err(hdev->dev, "Cannot allocate 0 bytes\n");
		वापस -EINVAL;
	पूर्ण

	contiguous = args->flags & HL_MEM_CONTIGUOUS;

	अगर (contiguous) अणु
		paddr = (u64) gen_pool_alloc(vm->dram_pg_pool, total_size);
		अगर (!paddr) अणु
			dev_err(hdev->dev,
				"failed to allocate %llu contiguous pages with total size of %llu\n",
				num_pgs, total_size);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	phys_pg_pack = kzalloc(माप(*phys_pg_pack), GFP_KERNEL);
	अगर (!phys_pg_pack) अणु
		rc = -ENOMEM;
		जाओ pages_pack_err;
	पूर्ण

	phys_pg_pack->vm_type = VM_TYPE_PHYS_PACK;
	phys_pg_pack->asid = ctx->asid;
	phys_pg_pack->npages = num_pgs;
	phys_pg_pack->page_size = page_size;
	phys_pg_pack->total_size = total_size;
	phys_pg_pack->flags = args->flags;
	phys_pg_pack->contiguous = contiguous;

	phys_pg_pack->pages = kvदो_स्मृति_array(num_pgs, माप(u64), GFP_KERNEL);
	अगर (ZERO_OR_शून्य_PTR(phys_pg_pack->pages)) अणु
		rc = -ENOMEM;
		जाओ pages_arr_err;
	पूर्ण

	अगर (phys_pg_pack->contiguous) अणु
		क्रम (i = 0 ; i < num_pgs ; i++)
			phys_pg_pack->pages[i] = paddr + i * page_size;
	पूर्ण अन्यथा अणु
		क्रम (i = 0 ; i < num_pgs ; i++) अणु
			phys_pg_pack->pages[i] = (u64) gen_pool_alloc(
							vm->dram_pg_pool,
							page_size);
			अगर (!phys_pg_pack->pages[i]) अणु
				dev_err(hdev->dev,
					"Failed to allocate device memory (out of memory)\n");
				rc = -ENOMEM;
				जाओ page_err;
			पूर्ण

			num_curr_pgs++;
		पूर्ण
	पूर्ण

	spin_lock(&vm->idr_lock);
	handle = idr_alloc(&vm->phys_pg_pack_handles, phys_pg_pack, 1, 0,
				GFP_KERNEL);
	spin_unlock(&vm->idr_lock);

	अगर (handle < 0) अणु
		dev_err(hdev->dev, "Failed to get handle for page\n");
		rc = -EFAULT;
		जाओ idr_err;
	पूर्ण

	क्रम (i = 0 ; i < num_pgs ; i++)
		kref_get(&vm->dram_pg_pool_refcount);

	phys_pg_pack->handle = handle;

	atomic64_add(phys_pg_pack->total_size, &ctx->dram_phys_mem);
	atomic64_add(phys_pg_pack->total_size, &hdev->dram_used_mem);

	*ret_handle = handle;

	वापस 0;

idr_err:
page_err:
	अगर (!phys_pg_pack->contiguous)
		क्रम (i = 0 ; i < num_curr_pgs ; i++)
			gen_pool_मुक्त(vm->dram_pg_pool, phys_pg_pack->pages[i],
					page_size);

	kvमुक्त(phys_pg_pack->pages);
pages_arr_err:
	kमुक्त(phys_pg_pack);
pages_pack_err:
	अगर (contiguous)
		gen_pool_मुक्त(vm->dram_pg_pool, paddr, total_size);

	वापस rc;
पूर्ण

/**
 * dma_map_host_va() - DMA mapping of the given host भव address.
 * @hdev: habanaद_असल device काष्ठाure.
 * @addr: the host भव address of the memory area.
 * @size: the size of the memory area.
 * @p_userptr: poपूर्णांकer to result userptr काष्ठाure.
 *
 * This function करोes the following:
 * - Allocate userptr काष्ठाure.
 * - Pin the given host memory using the userptr काष्ठाure.
 * - Perक्रमm DMA mapping to have the DMA addresses of the pages.
 */
अटल पूर्णांक dma_map_host_va(काष्ठा hl_device *hdev, u64 addr, u64 size,
				काष्ठा hl_userptr **p_userptr)
अणु
	काष्ठा hl_userptr *userptr;
	पूर्णांक rc;

	userptr = kzalloc(माप(*userptr), GFP_KERNEL);
	अगर (!userptr) अणु
		rc = -ENOMEM;
		जाओ userptr_err;
	पूर्ण

	rc = hl_pin_host_memory(hdev, addr, size, userptr);
	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to pin host memory\n");
		जाओ pin_err;
	पूर्ण

	rc = hdev->asic_funcs->asic_dma_map_sg(hdev, userptr->sgt->sgl,
					userptr->sgt->nents, DMA_BIसूचीECTIONAL);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to map sgt with DMA region\n");
		जाओ dma_map_err;
	पूर्ण

	userptr->dma_mapped = true;
	userptr->dir = DMA_BIसूचीECTIONAL;
	userptr->vm_type = VM_TYPE_USERPTR;

	*p_userptr = userptr;

	वापस 0;

dma_map_err:
	hl_unpin_host_memory(hdev, userptr);
pin_err:
	kमुक्त(userptr);
userptr_err:

	वापस rc;
पूर्ण

/**
 * dma_unmap_host_va() - DMA unmapping of the given host भव address.
 * @hdev: habanaद_असल device काष्ठाure.
 * @userptr: userptr to मुक्त.
 *
 * This function करोes the following:
 * - Unpins the physical pages.
 * - Frees the userptr काष्ठाure.
 */
अटल व्योम dma_unmap_host_va(काष्ठा hl_device *hdev,
				काष्ठा hl_userptr *userptr)
अणु
	hl_unpin_host_memory(hdev, userptr);
	kमुक्त(userptr);
पूर्ण

/**
 * dram_pg_pool_करो_release() - मुक्त DRAM pages pool
 * @ref: poपूर्णांकer to reference object.
 *
 * This function करोes the following:
 * - Frees the idr काष्ठाure of physical pages handles.
 * - Frees the generic pool of DRAM physical pages.
 */
अटल व्योम dram_pg_pool_करो_release(काष्ठा kref *ref)
अणु
	काष्ठा hl_vm *vm = container_of(ref, काष्ठा hl_vm,
			dram_pg_pool_refcount);

	/*
	 * मुक्त the idr here as only here we know क्रम sure that there are no
	 * allocated physical pages and hence there are no handles in use
	 */
	idr_destroy(&vm->phys_pg_pack_handles);
	gen_pool_destroy(vm->dram_pg_pool);
पूर्ण

/**
 * मुक्त_phys_pg_pack() - मुक्त physical page pack.
 * @hdev: habanaद_असल device काष्ठाure.
 * @phys_pg_pack: physical page pack to मुक्त.
 *
 * This function करोes the following:
 * - For DRAM memory only
 *   - iterate over the pack, scrub and मुक्त each physical block काष्ठाure by
 *     वापसing it to the general pool.
 *     In हाल of error during scrubbing, initiate hard reset.
 *     Once hard reset is triggered, scrubbing is bypassed जबतक मुक्तing the
 *     memory जारीs.
 * - Free the hl_vm_phys_pg_pack काष्ठाure.
 */
अटल पूर्णांक मुक्त_phys_pg_pack(काष्ठा hl_device *hdev,
				काष्ठा hl_vm_phys_pg_pack *phys_pg_pack)
अणु
	काष्ठा hl_vm *vm = &hdev->vm;
	u64 i;
	पूर्णांक rc = 0;

	अगर (phys_pg_pack->created_from_userptr)
		जाओ end;

	अगर (phys_pg_pack->contiguous) अणु
		अगर (hdev->memory_scrub && !hdev->disabled) अणु
			rc = hdev->asic_funcs->scrub_device_mem(hdev,
					phys_pg_pack->pages[0],
					phys_pg_pack->total_size);
			अगर (rc)
				dev_err(hdev->dev,
					"Failed to scrub contiguous device memory\n");
		पूर्ण

		gen_pool_मुक्त(vm->dram_pg_pool, phys_pg_pack->pages[0],
			phys_pg_pack->total_size);

		क्रम (i = 0; i < phys_pg_pack->npages ; i++)
			kref_put(&vm->dram_pg_pool_refcount,
				dram_pg_pool_करो_release);
	पूर्ण अन्यथा अणु
		क्रम (i = 0 ; i < phys_pg_pack->npages ; i++) अणु
			अगर (hdev->memory_scrub && !hdev->disabled && rc == 0) अणु
				rc = hdev->asic_funcs->scrub_device_mem(
						hdev,
						phys_pg_pack->pages[i],
						phys_pg_pack->page_size);
				अगर (rc)
					dev_err(hdev->dev,
						"Failed to scrub device memory\n");
			पूर्ण
			gen_pool_मुक्त(vm->dram_pg_pool,
				phys_pg_pack->pages[i],
				phys_pg_pack->page_size);
			kref_put(&vm->dram_pg_pool_refcount,
				dram_pg_pool_करो_release);
		पूर्ण
	पूर्ण

	अगर (rc && !hdev->disabled)
		hl_device_reset(hdev, HL_RESET_HARD);

end:
	kvमुक्त(phys_pg_pack->pages);
	kमुक्त(phys_pg_pack);

	वापस rc;
पूर्ण

/**
 * मुक्त_device_memory() - मुक्त device memory.
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @args: host parameters containing the requested size.
 *
 * This function करोes the following:
 * - Free the device memory related to the given handle.
 */
अटल पूर्णांक मुक्त_device_memory(काष्ठा hl_ctx *ctx, काष्ठा hl_mem_in *args)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_vm *vm = &hdev->vm;
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack;
	u32 handle = args->मुक्त.handle;

	spin_lock(&vm->idr_lock);
	phys_pg_pack = idr_find(&vm->phys_pg_pack_handles, handle);
	अगर (phys_pg_pack) अणु
		अगर (atomic_पढ़ो(&phys_pg_pack->mapping_cnt) > 0) अणु
			dev_err(hdev->dev, "handle %u is mapped, cannot free\n",
				handle);
			spin_unlock(&vm->idr_lock);
			वापस -EINVAL;
		पूर्ण

		/*
		 * must हटाओ from idr beक्रमe the मुक्तing of the physical
		 * pages as the refcount of the pool is also the trigger of the
		 * idr destroy
		 */
		idr_हटाओ(&vm->phys_pg_pack_handles, handle);
		spin_unlock(&vm->idr_lock);

		atomic64_sub(phys_pg_pack->total_size, &ctx->dram_phys_mem);
		atomic64_sub(phys_pg_pack->total_size, &hdev->dram_used_mem);

		वापस मुक्त_phys_pg_pack(hdev, phys_pg_pack);
	पूर्ण अन्यथा अणु
		spin_unlock(&vm->idr_lock);
		dev_err(hdev->dev,
			"free device memory failed, no match for handle %u\n",
			handle);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * clear_बहु_सूची_locked() - मुक्त भव addresses list.
 * @hdev: habanaद_असल device काष्ठाure.
 * @बहु_सूची: list of भव addresses to मुक्त.
 *
 * This function करोes the following:
 * - Iterate over the list and मुक्त each भव addresses block.
 *
 * This function should be called only when बहु_सूची lock is taken.
 */
अटल व्योम clear_बहु_सूची_locked(काष्ठा hl_device *hdev,
		काष्ठा list_head *बहु_सूची)
अणु
	काष्ठा hl_vm_va_block *va_block, *पंचांगp;

	list_क्रम_each_entry_safe(va_block, पंचांगp, बहु_सूची, node) अणु
		list_del(&va_block->node);
		kमुक्त(va_block);
	पूर्ण
पूर्ण

/**
 * prपूर्णांक_बहु_सूची_locked() - prपूर्णांक भव addresses list.
 * @hdev: habanaद_असल device काष्ठाure.
 * @बहु_सूची: list of भव addresses to prपूर्णांक.
 *
 * This function करोes the following:
 * - Iterate over the list and prपूर्णांक each भव addresses block.
 *
 * This function should be called only when बहु_सूची lock is taken.
 */
अटल व्योम prपूर्णांक_बहु_सूची_locked(काष्ठा hl_device *hdev,
		काष्ठा list_head *बहु_सूची)
अणु
#अगर HL_MMU_DEBUG
	काष्ठा hl_vm_va_block *va_block;

	dev_dbg(hdev->dev, "print va list:\n");

	list_क्रम_each_entry(va_block, बहु_सूची, node)
		dev_dbg(hdev->dev,
			"va block, start: 0x%llx, end: 0x%llx, size: %llu\n",
			va_block->start, va_block->end, va_block->size);
#पूर्ण_अगर
पूर्ण

/**
 * merge_va_blocks_locked() - merge a भव block अगर possible.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @बहु_सूची: poपूर्णांकer to the भव addresses block list.
 * @va_block: भव block to merge with adjacent blocks.
 *
 * This function करोes the following:
 * - Merge the given blocks with the adjacent blocks अगर their भव ranges
 *   create a contiguous भव range.
 *
 * This Function should be called only when बहु_सूची lock is taken.
 */
अटल व्योम merge_va_blocks_locked(काष्ठा hl_device *hdev,
		काष्ठा list_head *बहु_सूची, काष्ठा hl_vm_va_block *va_block)
अणु
	काष्ठा hl_vm_va_block *prev, *next;

	prev = list_prev_entry(va_block, node);
	अगर (&prev->node != बहु_सूची && prev->end + 1 == va_block->start) अणु
		prev->end = va_block->end;
		prev->size = prev->end - prev->start;
		list_del(&va_block->node);
		kमुक्त(va_block);
		va_block = prev;
	पूर्ण

	next = list_next_entry(va_block, node);
	अगर (&next->node != बहु_सूची && va_block->end + 1 == next->start) अणु
		next->start = va_block->start;
		next->size = next->end - next->start;
		list_del(&va_block->node);
		kमुक्त(va_block);
	पूर्ण
पूर्ण

/**
 * add_va_block_locked() - add a भव block to the भव addresses list.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @बहु_सूची: poपूर्णांकer to the भव addresses block list.
 * @start: start भव address.
 * @end: end भव address.
 *
 * This function करोes the following:
 * - Add the given block to the भव blocks list and merge with other blocks
 *   अगर a contiguous भव block can be created.
 *
 * This Function should be called only when बहु_सूची lock is taken.
 */
अटल पूर्णांक add_va_block_locked(काष्ठा hl_device *hdev,
		काष्ठा list_head *बहु_सूची, u64 start, u64 end)
अणु
	काष्ठा hl_vm_va_block *va_block, *res = शून्य;
	u64 size = end - start;

	prपूर्णांक_बहु_सूची_locked(hdev, बहु_सूची);

	list_क्रम_each_entry(va_block, बहु_सूची, node) अणु
		/* TODO: हटाओ upon matureness */
		अगर (hl_mem_area_crosses_range(start, size, va_block->start,
				va_block->end)) अणु
			dev_err(hdev->dev,
				"block crossing ranges at start 0x%llx, end 0x%llx\n",
				va_block->start, va_block->end);
			वापस -EINVAL;
		पूर्ण

		अगर (va_block->end < start)
			res = va_block;
	पूर्ण

	va_block = kदो_स्मृति(माप(*va_block), GFP_KERNEL);
	अगर (!va_block)
		वापस -ENOMEM;

	va_block->start = start;
	va_block->end = end;
	va_block->size = size;

	अगर (!res)
		list_add(&va_block->node, बहु_सूची);
	अन्यथा
		list_add(&va_block->node, &res->node);

	merge_va_blocks_locked(hdev, बहु_सूची, va_block);

	prपूर्णांक_बहु_सूची_locked(hdev, बहु_सूची);

	वापस 0;
पूर्ण

/**
 * add_va_block() - wrapper क्रम add_va_block_locked.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @बहु_सूची: poपूर्णांकer to the भव addresses block list.
 * @start: start भव address.
 * @end: end भव address.
 *
 * This function करोes the following:
 * - Takes the list lock and calls add_va_block_locked.
 */
अटल अंतरभूत पूर्णांक add_va_block(काष्ठा hl_device *hdev,
		काष्ठा hl_va_range *va_range, u64 start, u64 end)
अणु
	पूर्णांक rc;

	mutex_lock(&va_range->lock);
	rc = add_va_block_locked(hdev, &va_range->list, start, end);
	mutex_unlock(&va_range->lock);

	वापस rc;
पूर्ण

/**
 * get_va_block() - get a भव block क्रम the given size and alignment.
 *
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @va_range: poपूर्णांकer to the भव addresses range.
 * @size: requested block size.
 * @hपूर्णांक_addr: hपूर्णांक क्रम requested address by the user.
 * @va_block_align: required alignment of the भव block start address.
 *
 * This function करोes the following:
 * - Iterate on the भव block list to find a suitable भव block क्रम the
 *   given size, hपूर्णांक address and alignment.
 * - Reserve the requested block and update the list.
 * - Return the start address of the भव block.
 */
अटल u64 get_va_block(काष्ठा hl_device *hdev,
				काष्ठा hl_va_range *va_range,
				u64 size, u64 hपूर्णांक_addr, u32 va_block_align)
अणु
	काष्ठा hl_vm_va_block *va_block, *new_va_block = शून्य;
	u64 पंचांगp_hपूर्णांक_addr, valid_start, valid_size, prev_start, prev_end,
		align_mask, reserved_valid_start = 0, reserved_valid_size = 0;
	bool add_prev = false;
	bool is_align_घात_2  = is_घातer_of_2(va_range->page_size);

	अगर (is_align_घात_2)
		align_mask = ~((u64)va_block_align - 1);
	अन्यथा
		/*
		 * with non-घातer-of-2 range we work only with page granularity
		 * and the start address is page aligned,
		 * so no need क्रम alignment checking.
		 */
		size = DIV_ROUND_UP_ULL(size, va_range->page_size) *
							va_range->page_size;

	पंचांगp_hपूर्णांक_addr = hपूर्णांक_addr;

	/* Check अगर we need to ignore hपूर्णांक address */
	अगर ((is_align_घात_2 && (hपूर्णांक_addr & (va_block_align - 1))) ||
			(!is_align_घात_2 &&
				करो_भाग(पंचांगp_hपूर्णांक_addr, va_range->page_size))) अणु
		dev_info(hdev->dev, "Hint address 0x%llx will be ignored\n",
					hपूर्णांक_addr);
		hपूर्णांक_addr = 0;
	पूर्ण

	mutex_lock(&va_range->lock);

	prपूर्णांक_बहु_सूची_locked(hdev, &va_range->list);

	list_क्रम_each_entry(va_block, &va_range->list, node) अणु
		/* Calc the first possible aligned addr */
		valid_start = va_block->start;

		अगर (is_align_घात_2 && (valid_start & (va_block_align - 1))) अणु
			valid_start &= align_mask;
			valid_start += va_block_align;
			अगर (valid_start > va_block->end)
				जारी;
		पूर्ण

		valid_size = va_block->end - valid_start;
		अगर (valid_size < size)
			जारी;

		/* Pick the minimal length block which has the required size */
		अगर (!new_va_block || (valid_size < reserved_valid_size)) अणु
			new_va_block = va_block;
			reserved_valid_start = valid_start;
			reserved_valid_size = valid_size;
		पूर्ण

		अगर (hपूर्णांक_addr && hपूर्णांक_addr >= valid_start &&
					(hपूर्णांक_addr + size) <= va_block->end) अणु
			new_va_block = va_block;
			reserved_valid_start = hपूर्णांक_addr;
			reserved_valid_size = valid_size;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!new_va_block) अणु
		dev_err(hdev->dev, "no available va block for size %llu\n",
								size);
		जाओ out;
	पूर्ण

	/*
	 * Check अगर there is some leftover range due to reserving the new
	 * va block, then वापस it to the मुख्य भव addresses list.
	 */
	अगर (reserved_valid_start > new_va_block->start) अणु
		prev_start = new_va_block->start;
		prev_end = reserved_valid_start - 1;

		new_va_block->start = reserved_valid_start;
		new_va_block->size = reserved_valid_size;

		add_prev = true;
	पूर्ण

	अगर (new_va_block->size > size) अणु
		new_va_block->start += size;
		new_va_block->size = new_va_block->end - new_va_block->start;
	पूर्ण अन्यथा अणु
		list_del(&new_va_block->node);
		kमुक्त(new_va_block);
	पूर्ण

	अगर (add_prev)
		add_va_block_locked(hdev, &va_range->list, prev_start,
				prev_end);

	prपूर्णांक_बहु_सूची_locked(hdev, &va_range->list);
out:
	mutex_unlock(&va_range->lock);

	वापस reserved_valid_start;
पूर्ण

/*
 * hl_reserve_va_block() - reserve a भव block of a given size.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @ctx: current context
 * @type: भव addresses range type.
 * @size: requested block size.
 * @alignment: required alignment in bytes of the भव block start address,
 *             0 means no alignment.
 *
 * This function करोes the following:
 * - Iterate on the भव block list to find a suitable भव block क्रम the
 *   given size and alignment.
 * - Reserve the requested block and update the list.
 * - Return the start address of the भव block.
 */
u64 hl_reserve_va_block(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
		क्रमागत hl_va_range_type type, u32 size, u32 alignment)
अणु
	वापस get_va_block(hdev, ctx->va_range[type], size, 0,
			max(alignment, ctx->va_range[type]->page_size));
पूर्ण

/**
 * hl_get_va_range_type() - get va_range type क्रम the given address and size.
 * @address: the start address of the area we want to validate.
 * @size: the size in bytes of the area we want to validate.
 * @type: वापसed va_range type.
 *
 * Return: true अगर the area is inside a valid range, false otherwise.
 */
अटल पूर्णांक hl_get_va_range_type(काष्ठा hl_ctx *ctx, u64 address, u64 size,
			क्रमागत hl_va_range_type *type)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < HL_VA_RANGE_TYPE_MAX; i++) अणु
		अगर (hl_mem_area_inside_range(address, size,
				ctx->va_range[i]->start_addr,
				ctx->va_range[i]->end_addr)) अणु
			*type = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * hl_unreserve_va_block() - wrapper क्रम add_va_block to unreserve a va block.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @start: start भव address.
 * @end: end भव address.
 *
 * This function करोes the following:
 * - Takes the list lock and calls add_va_block_locked.
 */
पूर्णांक hl_unreserve_va_block(काष्ठा hl_device *hdev, काष्ठा hl_ctx *ctx,
		u64 start_addr, u64 size)
अणु
	क्रमागत hl_va_range_type type;
	पूर्णांक rc;

	rc = hl_get_va_range_type(ctx, start_addr, size, &type);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"cannot find va_range for va %#llx size %llu",
			start_addr, size);
		वापस rc;
	पूर्ण

	rc = add_va_block(hdev, ctx->va_range[type], start_addr,
						start_addr + size - 1);
	अगर (rc)
		dev_warn(hdev->dev,
			"add va block failed for vaddr: 0x%llx\n", start_addr);

	वापस rc;
पूर्ण

/**
 * get_sg_info() - get number of pages and the DMA address from SG list.
 * @sg: the SG list.
 * @dma_addr: poपूर्णांकer to DMA address to वापस.
 *
 * Calculate the number of consecutive pages described by the SG list. Take the
 * offset of the address in the first page, add to it the length and round it up
 * to the number of needed pages.
 */
अटल u32 get_sg_info(काष्ठा scatterlist *sg, dma_addr_t *dma_addr)
अणु
	*dma_addr = sg_dma_address(sg);

	वापस ((((*dma_addr) & (PAGE_SIZE - 1)) + sg_dma_len(sg)) +
			(PAGE_SIZE - 1)) >> PAGE_SHIFT;
पूर्ण

/**
 * init_phys_pg_pack_from_userptr() - initialize physical page pack from host
 *                                    memory
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @userptr: userptr to initialize from.
 * @pphys_pg_pack: result poपूर्णांकer.
 *
 * This function करोes the following:
 * - Pin the physical pages related to the given भव block.
 * - Create a physical page pack from the physical pages related to the given
 *   भव block.
 */
अटल पूर्णांक init_phys_pg_pack_from_userptr(काष्ठा hl_ctx *ctx,
				काष्ठा hl_userptr *userptr,
				काष्ठा hl_vm_phys_pg_pack **pphys_pg_pack)
अणु
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack;
	काष्ठा scatterlist *sg;
	dma_addr_t dma_addr;
	u64 page_mask, total_npages;
	u32 npages, page_size = PAGE_SIZE,
		huge_page_size = ctx->hdev->asic_prop.pmmu_huge.page_size;
	bool first = true, is_huge_page_opt = true;
	पूर्णांक rc, i, j;
	u32 pgs_in_huge_page = huge_page_size >> __ffs(page_size);

	phys_pg_pack = kzalloc(माप(*phys_pg_pack), GFP_KERNEL);
	अगर (!phys_pg_pack)
		वापस -ENOMEM;

	phys_pg_pack->vm_type = userptr->vm_type;
	phys_pg_pack->created_from_userptr = true;
	phys_pg_pack->asid = ctx->asid;
	atomic_set(&phys_pg_pack->mapping_cnt, 1);

	/* Only अगर all dma_addrs are aligned to 2MB and their
	 * sizes is at least 2MB, we can use huge page mapping.
	 * We limit the 2MB optimization to this condition,
	 * since later on we acquire the related VA range as one
	 * consecutive block.
	 */
	total_npages = 0;
	क्रम_each_sg(userptr->sgt->sgl, sg, userptr->sgt->nents, i) अणु
		npages = get_sg_info(sg, &dma_addr);

		total_npages += npages;

		अगर ((npages % pgs_in_huge_page) ||
					(dma_addr & (huge_page_size - 1)))
			is_huge_page_opt = false;
	पूर्ण

	अगर (is_huge_page_opt) अणु
		page_size = huge_page_size;
		करो_भाग(total_npages, pgs_in_huge_page);
	पूर्ण

	page_mask = ~(((u64) page_size) - 1);

	phys_pg_pack->pages = kvदो_स्मृति_array(total_npages, माप(u64),
						GFP_KERNEL);
	अगर (ZERO_OR_शून्य_PTR(phys_pg_pack->pages)) अणु
		rc = -ENOMEM;
		जाओ page_pack_arr_mem_err;
	पूर्ण

	phys_pg_pack->npages = total_npages;
	phys_pg_pack->page_size = page_size;
	phys_pg_pack->total_size = total_npages * page_size;

	j = 0;
	क्रम_each_sg(userptr->sgt->sgl, sg, userptr->sgt->nents, i) अणु
		npages = get_sg_info(sg, &dma_addr);

		/* align करोwn to physical page size and save the offset */
		अगर (first) अणु
			first = false;
			phys_pg_pack->offset = dma_addr & (page_size - 1);
			dma_addr &= page_mask;
		पूर्ण

		जबतक (npages) अणु
			phys_pg_pack->pages[j++] = dma_addr;
			dma_addr += page_size;

			अगर (is_huge_page_opt)
				npages -= pgs_in_huge_page;
			अन्यथा
				npages--;
		पूर्ण
	पूर्ण

	*pphys_pg_pack = phys_pg_pack;

	वापस 0;

page_pack_arr_mem_err:
	kमुक्त(phys_pg_pack);

	वापस rc;
पूर्ण

/**
 * map_phys_pg_pack() - maps the physical page pack..
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @vaddr: start address of the भव area to map from.
 * @phys_pg_pack: the pack of physical pages to map to.
 *
 * This function करोes the following:
 * - Maps each chunk of भव memory to matching physical chunk.
 * - Stores number of successful mappings in the given argument.
 * - Returns 0 on success, error code otherwise.
 */
अटल पूर्णांक map_phys_pg_pack(काष्ठा hl_ctx *ctx, u64 vaddr,
				काष्ठा hl_vm_phys_pg_pack *phys_pg_pack)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	u64 next_vaddr = vaddr, paddr, mapped_pg_cnt = 0, i;
	u32 page_size = phys_pg_pack->page_size;
	पूर्णांक rc = 0;
	bool is_host_addr;

	क्रम (i = 0 ; i < phys_pg_pack->npages ; i++) अणु
		paddr = phys_pg_pack->pages[i];

		rc = hl_mmu_map_page(ctx, next_vaddr, paddr, page_size,
				(i + 1) == phys_pg_pack->npages);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"map failed for handle %u, npages: %llu, mapped: %llu",
				phys_pg_pack->handle, phys_pg_pack->npages,
				mapped_pg_cnt);
			जाओ err;
		पूर्ण

		mapped_pg_cnt++;
		next_vaddr += page_size;
	पूर्ण

	वापस 0;

err:
	is_host_addr = !hl_is_dram_va(hdev, vaddr);

	next_vaddr = vaddr;
	क्रम (i = 0 ; i < mapped_pg_cnt ; i++) अणु
		अगर (hl_mmu_unmap_page(ctx, next_vaddr, page_size,
					(i + 1) == mapped_pg_cnt))
			dev_warn_ratelimited(hdev->dev,
				"failed to unmap handle %u, va: 0x%llx, pa: 0x%llx, page size: %u\n",
					phys_pg_pack->handle, next_vaddr,
					phys_pg_pack->pages[i], page_size);

		next_vaddr += page_size;

		/*
		 * unmapping on Palladium can be really दीर्घ, so aव्योम a CPU
		 * soft lockup bug by sleeping a little between unmapping pages
		 *
		 * In addition, on host num of pages could be huge,
		 * because page size could be 4KB, so when unmapping host
		 * pages sleep every 32K pages to aव्योम soft lockup
		 */
		अगर (hdev->pldm || (is_host_addr && (i & 0x7FFF) == 0))
			usleep_range(50, 200);
	पूर्ण

	वापस rc;
पूर्ण

/**
 * unmap_phys_pg_pack() - unmaps the physical page pack.
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @vaddr: start address of the भव area to unmap.
 * @phys_pg_pack: the pack of physical pages to unmap.
 */
अटल व्योम unmap_phys_pg_pack(काष्ठा hl_ctx *ctx, u64 vaddr,
				काष्ठा hl_vm_phys_pg_pack *phys_pg_pack)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	u64 next_vaddr, i;
	bool is_host_addr;
	u32 page_size;

	is_host_addr = !hl_is_dram_va(hdev, vaddr);
	page_size = phys_pg_pack->page_size;
	next_vaddr = vaddr;

	क्रम (i = 0 ; i < phys_pg_pack->npages ; i++, next_vaddr += page_size) अणु
		अगर (hl_mmu_unmap_page(ctx, next_vaddr, page_size,
				       (i + 1) == phys_pg_pack->npages))
			dev_warn_ratelimited(hdev->dev,
			"unmap failed for vaddr: 0x%llx\n", next_vaddr);

		/*
		 * unmapping on Palladium can be really दीर्घ, so aव्योम a CPU
		 * soft lockup bug by sleeping a little between unmapping pages
		 *
		 * In addition, on host num of pages could be huge,
		 * because page size could be 4KB, so when unmapping host
		 * pages sleep every 32K pages to aव्योम soft lockup
		 */
		अगर (hdev->pldm || (is_host_addr && (i & 0x7FFF) == 0))
			usleep_range(50, 200);
	पूर्ण
पूर्ण

अटल पूर्णांक get_paddr_from_handle(काष्ठा hl_ctx *ctx, काष्ठा hl_mem_in *args,
					u64 *paddr)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_vm *vm = &hdev->vm;
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack;
	u32 handle;

	handle = lower_32_bits(args->map_device.handle);
	spin_lock(&vm->idr_lock);
	phys_pg_pack = idr_find(&vm->phys_pg_pack_handles, handle);
	अगर (!phys_pg_pack) अणु
		spin_unlock(&vm->idr_lock);
		dev_err(hdev->dev, "no match for handle %u\n", handle);
		वापस -EINVAL;
	पूर्ण

	*paddr = phys_pg_pack->pages[0];

	spin_unlock(&vm->idr_lock);

	वापस 0;
पूर्ण

/**
 * map_device_va() - map the given memory.
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @args: host parameters with handle/host भव address.
 * @device_addr: poपूर्णांकer to result device भव address.
 *
 * This function करोes the following:
 * - If given a physical device memory handle, map to a device भव block
 *   and वापस the start address of this block.
 * - If given a host भव address and size, find the related physical pages,
 *   map a device भव block to this pages and वापस the start address of
 *   this block.
 */
अटल पूर्णांक map_device_va(काष्ठा hl_ctx *ctx, काष्ठा hl_mem_in *args,
		u64 *device_addr)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_vm *vm = &hdev->vm;
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack;
	काष्ठा hl_userptr *userptr = शून्य;
	काष्ठा hl_vm_hash_node *hnode;
	काष्ठा hl_va_range *va_range;
	क्रमागत vm_type_t *vm_type;
	u64 ret_vaddr, hपूर्णांक_addr;
	u32 handle = 0, va_block_align;
	पूर्णांक rc;
	bool is_userptr = args->flags & HL_MEM_USERPTR;

	/* Assume failure */
	*device_addr = 0;

	अगर (is_userptr) अणु
		u64 addr = args->map_host.host_virt_addr,
			size = args->map_host.mem_size;
		u32 page_size = hdev->asic_prop.pmmu.page_size,
			huge_page_size = hdev->asic_prop.pmmu_huge.page_size;

		rc = dma_map_host_va(hdev, addr, size, &userptr);
		अगर (rc) अणु
			dev_err(hdev->dev, "failed to get userptr from va\n");
			वापस rc;
		पूर्ण

		rc = init_phys_pg_pack_from_userptr(ctx, userptr,
				&phys_pg_pack);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"unable to init page pack for vaddr 0x%llx\n",
				addr);
			जाओ init_page_pack_err;
		पूर्ण

		vm_type = (क्रमागत vm_type_t *) userptr;
		hपूर्णांक_addr = args->map_host.hपूर्णांक_addr;
		handle = phys_pg_pack->handle;

		/* get required alignment */
		अगर (phys_pg_pack->page_size == page_size) अणु
			va_range = ctx->va_range[HL_VA_RANGE_TYPE_HOST];

			/*
			 * huge page alignment may be needed in हाल of regular
			 * page mapping, depending on the host VA alignment
			 */
			अगर (addr & (huge_page_size - 1))
				va_block_align = page_size;
			अन्यथा
				va_block_align = huge_page_size;
		पूर्ण अन्यथा अणु
			/*
			 * huge page alignment is needed in हाल of huge page
			 * mapping
			 */
			va_range = ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE];
			va_block_align = huge_page_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		handle = lower_32_bits(args->map_device.handle);

		spin_lock(&vm->idr_lock);
		phys_pg_pack = idr_find(&vm->phys_pg_pack_handles, handle);
		अगर (!phys_pg_pack) अणु
			spin_unlock(&vm->idr_lock);
			dev_err(hdev->dev,
				"no match for handle %u\n", handle);
			वापस -EINVAL;
		पूर्ण

		/* increment now to aव्योम मुक्तing device memory जबतक mapping */
		atomic_inc(&phys_pg_pack->mapping_cnt);

		spin_unlock(&vm->idr_lock);

		vm_type = (क्रमागत vm_type_t *) phys_pg_pack;

		hपूर्णांक_addr = args->map_device.hपूर्णांक_addr;

		/* DRAM VA alignment is the same as the MMU page size */
		va_range = ctx->va_range[HL_VA_RANGE_TYPE_DRAM];
		va_block_align = hdev->asic_prop.dmmu.page_size;
	पूर्ण

	/*
	 * relevant क्रम mapping device physical memory only, as host memory is
	 * implicitly shared
	 */
	अगर (!is_userptr && !(phys_pg_pack->flags & HL_MEM_SHARED) &&
			phys_pg_pack->asid != ctx->asid) अणु
		dev_err(hdev->dev,
			"Failed to map memory, handle %u is not shared\n",
			handle);
		rc = -EPERM;
		जाओ shared_err;
	पूर्ण

	hnode = kzalloc(माप(*hnode), GFP_KERNEL);
	अगर (!hnode) अणु
		rc = -ENOMEM;
		जाओ hnode_err;
	पूर्ण

	ret_vaddr = get_va_block(hdev, va_range, phys_pg_pack->total_size,
					hपूर्णांक_addr, va_block_align);
	अगर (!ret_vaddr) अणु
		dev_err(hdev->dev, "no available va block for handle %u\n",
				handle);
		rc = -ENOMEM;
		जाओ va_block_err;
	पूर्ण

	mutex_lock(&ctx->mmu_lock);

	rc = map_phys_pg_pack(ctx, ret_vaddr, phys_pg_pack);
	अगर (rc) अणु
		mutex_unlock(&ctx->mmu_lock);
		dev_err(hdev->dev, "mapping page pack failed for handle %u\n",
				handle);
		जाओ map_err;
	पूर्ण

	rc = hdev->asic_funcs->mmu_invalidate_cache(hdev, false, *vm_type);

	mutex_unlock(&ctx->mmu_lock);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"mapping handle %u failed due to MMU cache invalidation\n",
			handle);
		जाओ map_err;
	पूर्ण

	ret_vaddr += phys_pg_pack->offset;

	hnode->ptr = vm_type;
	hnode->vaddr = ret_vaddr;

	mutex_lock(&ctx->mem_hash_lock);
	hash_add(ctx->mem_hash, &hnode->node, ret_vaddr);
	mutex_unlock(&ctx->mem_hash_lock);

	*device_addr = ret_vaddr;

	अगर (is_userptr)
		rc = मुक्त_phys_pg_pack(hdev, phys_pg_pack);

	वापस rc;

map_err:
	अगर (add_va_block(hdev, va_range, ret_vaddr,
				ret_vaddr + phys_pg_pack->total_size - 1))
		dev_warn(hdev->dev,
			"release va block failed for handle 0x%x, vaddr: 0x%llx\n",
				handle, ret_vaddr);

va_block_err:
	kमुक्त(hnode);
hnode_err:
shared_err:
	atomic_dec(&phys_pg_pack->mapping_cnt);
	अगर (is_userptr)
		मुक्त_phys_pg_pack(hdev, phys_pg_pack);
init_page_pack_err:
	अगर (is_userptr)
		dma_unmap_host_va(hdev, userptr);

	वापस rc;
पूर्ण

/**
 * unmap_device_va() - unmap the given device भव address.
 * @ctx: poपूर्णांकer to the context काष्ठाure.
 * @args: host parameters with device भव address to unmap.
 * @ctx_मुक्त: true अगर in context मुक्त flow, false otherwise.
 *
 * This function करोes the following:
 * - unmap the physical pages related to the given भव address.
 * - वापस the device भव block to the भव block list.
 */
अटल पूर्णांक unmap_device_va(काष्ठा hl_ctx *ctx, काष्ठा hl_mem_in *args,
				bool ctx_मुक्त)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_vm_phys_pg_pack *phys_pg_pack = शून्य;
	काष्ठा hl_vm_hash_node *hnode = शून्य;
	काष्ठा hl_userptr *userptr = शून्य;
	काष्ठा hl_va_range *va_range;
	u64 vaddr = args->unmap.device_virt_addr;
	क्रमागत vm_type_t *vm_type;
	bool is_userptr;
	पूर्णांक rc = 0;

	/* protect from द्विगुन entrance */
	mutex_lock(&ctx->mem_hash_lock);
	hash_क्रम_each_possible(ctx->mem_hash, hnode, node, (अचिन्हित दीर्घ)vaddr)
		अगर (vaddr == hnode->vaddr)
			अवरोध;

	अगर (!hnode) अणु
		mutex_unlock(&ctx->mem_hash_lock);
		dev_err(hdev->dev,
			"unmap failed, no mem hnode for vaddr 0x%llx\n",
			vaddr);
		वापस -EINVAL;
	पूर्ण

	hash_del(&hnode->node);
	mutex_unlock(&ctx->mem_hash_lock);

	vm_type = hnode->ptr;

	अगर (*vm_type == VM_TYPE_USERPTR) अणु
		is_userptr = true;
		userptr = hnode->ptr;
		rc = init_phys_pg_pack_from_userptr(ctx, userptr,
							&phys_pg_pack);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"unable to init page pack for vaddr 0x%llx\n",
				vaddr);
			जाओ vm_type_err;
		पूर्ण

		अगर (phys_pg_pack->page_size ==
					hdev->asic_prop.pmmu.page_size)
			va_range = ctx->va_range[HL_VA_RANGE_TYPE_HOST];
		अन्यथा
			va_range = ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE];
	पूर्ण अन्यथा अगर (*vm_type == VM_TYPE_PHYS_PACK) अणु
		is_userptr = false;
		va_range = ctx->va_range[HL_VA_RANGE_TYPE_DRAM];
		phys_pg_pack = hnode->ptr;
	पूर्ण अन्यथा अणु
		dev_warn(hdev->dev,
			"unmap failed, unknown vm desc for vaddr 0x%llx\n",
				vaddr);
		rc = -EFAULT;
		जाओ vm_type_err;
	पूर्ण

	अगर (atomic_पढ़ो(&phys_pg_pack->mapping_cnt) == 0) अणु
		dev_err(hdev->dev, "vaddr 0x%llx is not mapped\n", vaddr);
		rc = -EINVAL;
		जाओ mapping_cnt_err;
	पूर्ण

	अगर (!is_userptr && !is_घातer_of_2(phys_pg_pack->page_size))
		vaddr = prop->dram_base_address +
			DIV_ROUND_DOWN_ULL(vaddr - prop->dram_base_address,
						phys_pg_pack->page_size) *
							phys_pg_pack->page_size;
	अन्यथा
		vaddr &= ~(((u64) phys_pg_pack->page_size) - 1);

	mutex_lock(&ctx->mmu_lock);

	unmap_phys_pg_pack(ctx, vaddr, phys_pg_pack);

	/*
	 * During context मुक्त this function is called in a loop to clean all
	 * the context mappings. Hence the cache invalidation can be called once
	 * at the loop end rather than क्रम each iteration
	 */
	अगर (!ctx_मुक्त)
		rc = hdev->asic_funcs->mmu_invalidate_cache(hdev, true,
								*vm_type);

	mutex_unlock(&ctx->mmu_lock);

	/*
	 * If the context is closing we करोn't need to check क्रम the MMU cache
	 * invalidation वापस code and update the VA मुक्त list as in this flow
	 * we invalidate the MMU cache outside of this unmap function and the VA
	 * मुक्त list will be मुक्तd anyway.
	 */
	अगर (!ctx_मुक्त) अणु
		पूर्णांक पंचांगp_rc;

		अगर (rc)
			dev_err(hdev->dev,
				"unmapping vaddr 0x%llx failed due to MMU cache invalidation\n",
				vaddr);

		पंचांगp_rc = add_va_block(hdev, va_range, vaddr,
					vaddr + phys_pg_pack->total_size - 1);
		अगर (पंचांगp_rc) अणु
			dev_warn(hdev->dev,
					"add va block failed for vaddr: 0x%llx\n",
					vaddr);
			अगर (!rc)
				rc = पंचांगp_rc;
		पूर्ण
	पूर्ण

	atomic_dec(&phys_pg_pack->mapping_cnt);
	kमुक्त(hnode);

	अगर (is_userptr) अणु
		rc = मुक्त_phys_pg_pack(hdev, phys_pg_pack);
		dma_unmap_host_va(hdev, userptr);
	पूर्ण

	वापस rc;

mapping_cnt_err:
	अगर (is_userptr)
		मुक्त_phys_pg_pack(hdev, phys_pg_pack);
vm_type_err:
	mutex_lock(&ctx->mem_hash_lock);
	hash_add(ctx->mem_hash, &hnode->node, vaddr);
	mutex_unlock(&ctx->mem_hash_lock);

	वापस rc;
पूर्ण

अटल पूर्णांक map_block(काष्ठा hl_device *hdev, u64 address, u64 *handle,
			u32 *size)
अणु
	u32 block_id = 0;
	पूर्णांक rc;

	rc = hdev->asic_funcs->get_hw_block_id(hdev, address, size, &block_id);

	*handle = block_id | HL_MMAP_TYPE_BLOCK;
	*handle <<= PAGE_SHIFT;

	वापस rc;
पूर्ण

अटल व्योम hw_block_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hl_vm_hw_block_list_node *lnode =
		(काष्ठा hl_vm_hw_block_list_node *) vma->vm_निजी_data;
	काष्ठा hl_ctx *ctx = lnode->ctx;

	mutex_lock(&ctx->hw_block_list_lock);
	list_del(&lnode->node);
	mutex_unlock(&ctx->hw_block_list_lock);
	hl_ctx_put(ctx);
	kमुक्त(lnode);
	vma->vm_निजी_data = शून्य;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा hw_block_vm_ops = अणु
	.बंद = hw_block_vm_बंद
पूर्ण;

/**
 * hl_hw_block_mmap() - mmap a hw block to user.
 * @hpriv: poपूर्णांकer to the निजी data of the fd
 * @vma: poपूर्णांकer to vm_area_काष्ठा of the process
 *
 * Driver increments context reference क्रम every HW block mapped in order
 * to prevent user from closing FD without unmapping first
 */
पूर्णांक hl_hw_block_mmap(काष्ठा hl_fpriv *hpriv, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा hl_vm_hw_block_list_node *lnode;
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	u32 block_id, block_size;
	पूर्णांक rc;

	/* We use the page offset to hold the block id and thus we need to clear
	 * it beक्रमe करोing the mmap itself
	 */
	block_id = vma->vm_pgoff;
	vma->vm_pgoff = 0;

	/* Driver only allows mapping of a complete HW block */
	block_size = vma->vm_end - vma->vm_start;

#अगर_घोषित _HAS_TYPE_ARG_IN_ACCESS_OK
	अगर (!access_ok(VERIFY_WRITE,
		(व्योम __user *) (uपूर्णांकptr_t) vma->vm_start, block_size)) अणु
#अन्यथा
	अगर (!access_ok((व्योम __user *) (uपूर्णांकptr_t) vma->vm_start, block_size)) अणु
#पूर्ण_अगर
		dev_err(hdev->dev,
			"user pointer is invalid - 0x%lx\n",
			vma->vm_start);

		वापस -EINVAL;
	पूर्ण

	lnode = kzalloc(माप(*lnode), GFP_KERNEL);
	अगर (!lnode)
		वापस -ENOMEM;

	vma->vm_ops = &hw_block_vm_ops;
	vma->vm_निजी_data = lnode;

	hl_ctx_get(hdev, ctx);

	rc = hdev->asic_funcs->hw_block_mmap(hdev, vma, block_id, block_size);
	अगर (rc) अणु
		hl_ctx_put(ctx);
		kमुक्त(lnode);
		वापस rc;
	पूर्ण

	lnode->ctx = ctx;
	lnode->vaddr = vma->vm_start;
	lnode->size = block_size;
	lnode->id = block_id;

	mutex_lock(&ctx->hw_block_list_lock);
	list_add_tail(&lnode->node, &ctx->hw_block_mem_list);
	mutex_unlock(&ctx->hw_block_list_lock);

	vma->vm_pgoff = block_id;

	वापस 0;
पूर्ण

अटल पूर्णांक mem_ioctl_no_mmu(काष्ठा hl_fpriv *hpriv, जोड़ hl_mem_args *args)
अणु
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	u64 block_handle, device_addr = 0;
	u32 handle = 0, block_size;
	पूर्णांक rc;

	चयन (args->in.op) अणु
	हाल HL_MEM_OP_ALLOC:
		अगर (args->in.alloc.mem_size == 0) अणु
			dev_err(hdev->dev,
				"alloc size must be larger than 0\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		/* Force contiguous as there are no real MMU
		 * translations to overcome physical memory gaps
		 */
		args->in.flags |= HL_MEM_CONTIGUOUS;
		rc = alloc_device_memory(ctx, &args->in, &handle);

		स_रखो(args, 0, माप(*args));
		args->out.handle = (__u64) handle;
		अवरोध;

	हाल HL_MEM_OP_FREE:
		rc = मुक्त_device_memory(ctx, &args->in);
		अवरोध;

	हाल HL_MEM_OP_MAP:
		अगर (args->in.flags & HL_MEM_USERPTR) अणु
			device_addr = args->in.map_host.host_virt_addr;
			rc = 0;
		पूर्ण अन्यथा अणु
			rc = get_paddr_from_handle(ctx, &args->in,
							&device_addr);
		पूर्ण

		स_रखो(args, 0, माप(*args));
		args->out.device_virt_addr = device_addr;
		अवरोध;

	हाल HL_MEM_OP_UNMAP:
		rc = 0;
		अवरोध;

	हाल HL_MEM_OP_MAP_BLOCK:
		rc = map_block(hdev, args->in.map_block.block_addr,
				&block_handle, &block_size);
		args->out.block_handle = block_handle;
		args->out.block_size = block_size;
		अवरोध;

	शेष:
		dev_err(hdev->dev, "Unknown opcode for memory IOCTL\n");
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

out:
	वापस rc;
पूर्ण

पूर्णांक hl_mem_ioctl(काष्ठा hl_fpriv *hpriv, व्योम *data)
अणु
	क्रमागत hl_device_status status;
	जोड़ hl_mem_args *args = data;
	काष्ठा hl_device *hdev = hpriv->hdev;
	काष्ठा hl_ctx *ctx = hpriv->ctx;
	u64 block_handle, device_addr = 0;
	u32 handle = 0, block_size;
	पूर्णांक rc;

	अगर (!hl_device_operational(hdev, &status)) अणु
		dev_warn_ratelimited(hdev->dev,
			"Device is %s. Can't execute MEMORY IOCTL\n",
			hdev->status[status]);
		वापस -EBUSY;
	पूर्ण

	अगर (!hdev->mmu_enable)
		वापस mem_ioctl_no_mmu(hpriv, args);

	चयन (args->in.op) अणु
	हाल HL_MEM_OP_ALLOC:
		अगर (args->in.alloc.mem_size == 0) अणु
			dev_err(hdev->dev,
				"alloc size must be larger than 0\n");
			rc = -EINVAL;
			जाओ out;
		पूर्ण

		/* If DRAM करोes not support भव memory the driver won't
		 * handle the allocation/मुक्तing of that memory. However, क्रम
		 * प्रणाली administration/monitoring purposes, the driver will
		 * keep track of the amount of DRAM memory that is allocated
		 * and मुक्तd by the user. Because this code totally relies on
		 * the user's input, the driver can't ensure the validity
		 * of this accounting.
		 */
		अगर (!hdev->asic_prop.dram_supports_भव_memory) अणु
			atomic64_add(args->in.alloc.mem_size,
					&ctx->dram_phys_mem);
			atomic64_add(args->in.alloc.mem_size,
					&hdev->dram_used_mem);

			dev_dbg(hdev->dev, "DRAM alloc is not supported\n");
			rc = 0;

			स_रखो(args, 0, माप(*args));
			args->out.handle = 0;
			जाओ out;
		पूर्ण

		rc = alloc_device_memory(ctx, &args->in, &handle);

		स_रखो(args, 0, माप(*args));
		args->out.handle = (__u64) handle;
		अवरोध;

	हाल HL_MEM_OP_FREE:
		/* If DRAM करोes not support भव memory the driver won't
		 * handle the allocation/मुक्तing of that memory. However, क्रम
		 * प्रणाली administration/monitoring purposes, the driver will
		 * keep track of the amount of DRAM memory that is allocated
		 * and मुक्तd by the user. Because this code totally relies on
		 * the user's input, the driver can't ensure the validity
		 * of this accounting.
		 */
		अगर (!hdev->asic_prop.dram_supports_भव_memory) अणु
			atomic64_sub(args->in.alloc.mem_size,
					&ctx->dram_phys_mem);
			atomic64_sub(args->in.alloc.mem_size,
					&hdev->dram_used_mem);

			dev_dbg(hdev->dev, "DRAM alloc is not supported\n");
			rc = 0;

			जाओ out;
		पूर्ण

		rc = मुक्त_device_memory(ctx, &args->in);
		अवरोध;

	हाल HL_MEM_OP_MAP:
		rc = map_device_va(ctx, &args->in, &device_addr);

		स_रखो(args, 0, माप(*args));
		args->out.device_virt_addr = device_addr;
		अवरोध;

	हाल HL_MEM_OP_UNMAP:
		rc = unmap_device_va(ctx, &args->in, false);
		अवरोध;

	हाल HL_MEM_OP_MAP_BLOCK:
		rc = map_block(hdev, args->in.map_block.block_addr,
				&block_handle, &block_size);
		args->out.block_handle = block_handle;
		args->out.block_size = block_size;
		अवरोध;

	शेष:
		dev_err(hdev->dev, "Unknown opcode for memory IOCTL\n");
		rc = -ENOTTY;
		अवरोध;
	पूर्ण

out:
	वापस rc;
पूर्ण

अटल पूर्णांक get_user_memory(काष्ठा hl_device *hdev, u64 addr, u64 size,
				u32 npages, u64 start, u32 offset,
				काष्ठा hl_userptr *userptr)
अणु
	पूर्णांक rc;

	अगर (!access_ok((व्योम __user *) (uपूर्णांकptr_t) addr, size)) अणु
		dev_err(hdev->dev, "user pointer is invalid - 0x%llx\n", addr);
		वापस -EFAULT;
	पूर्ण

	userptr->pages = kvदो_स्मृति_array(npages, माप(*userptr->pages),
					GFP_KERNEL);
	अगर (!userptr->pages)
		वापस -ENOMEM;

	rc = pin_user_pages_fast(start, npages,
				 FOLL_FORCE | FOLL_WRITE | FOLL_LONGTERM,
				 userptr->pages);

	अगर (rc != npages) अणु
		dev_err(hdev->dev,
			"Failed to map host memory, user ptr probably wrong\n");
		अगर (rc < 0)
			जाओ destroy_pages;
		npages = rc;
		rc = -EFAULT;
		जाओ put_pages;
	पूर्ण
	userptr->npages = npages;

	rc = sg_alloc_table_from_pages(userptr->sgt,
				       userptr->pages,
				       npages, offset, size, GFP_KERNEL);
	अगर (rc < 0) अणु
		dev_err(hdev->dev, "failed to create SG table from pages\n");
		जाओ put_pages;
	पूर्ण

	वापस 0;

put_pages:
	unpin_user_pages(userptr->pages, npages);
destroy_pages:
	kvमुक्त(userptr->pages);
	वापस rc;
पूर्ण

/**
 * hl_pin_host_memory() - pins a chunk of host memory.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @addr: the host भव address of the memory area.
 * @size: the size of the memory area.
 * @userptr: poपूर्णांकer to hl_userptr काष्ठाure.
 *
 * This function करोes the following:
 * - Pins the physical pages.
 * - Create an SG list from those pages.
 */
पूर्णांक hl_pin_host_memory(काष्ठा hl_device *hdev, u64 addr, u64 size,
					काष्ठा hl_userptr *userptr)
अणु
	u64 start, end;
	u32 npages, offset;
	पूर्णांक rc;

	अगर (!size) अणु
		dev_err(hdev->dev, "size to pin is invalid - %llu\n", size);
		वापस -EINVAL;
	पूर्ण

	/*
	 * If the combination of the address and size requested क्रम this memory
	 * region causes an पूर्णांकeger overflow, वापस error.
	 */
	अगर (((addr + size) < addr) ||
			PAGE_ALIGN(addr + size) < (addr + size)) अणु
		dev_err(hdev->dev,
			"user pointer 0x%llx + %llu causes integer overflow\n",
			addr, size);
		वापस -EINVAL;
	पूर्ण

	userptr->sgt = kzalloc(माप(*userptr->sgt), GFP_KERNEL);
	अगर (!userptr->sgt)
		वापस -ENOMEM;

	start = addr & PAGE_MASK;
	offset = addr & ~PAGE_MASK;
	end = PAGE_ALIGN(addr + size);
	npages = (end - start) >> PAGE_SHIFT;

	userptr->size = size;
	userptr->addr = addr;
	userptr->dma_mapped = false;
	INIT_LIST_HEAD(&userptr->job_node);

	rc = get_user_memory(hdev, addr, size, npages, start, offset,
				userptr);
	अगर (rc) अणु
		dev_err(hdev->dev,
			"failed to get user memory for address 0x%llx\n",
			addr);
		जाओ मुक्त_sgt;
	पूर्ण

	hl_debugfs_add_userptr(hdev, userptr);

	वापस 0;

मुक्त_sgt:
	kमुक्त(userptr->sgt);
	वापस rc;
पूर्ण

/*
 * hl_unpin_host_memory - unpins a chunk of host memory.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure
 * @userptr: poपूर्णांकer to hl_userptr काष्ठाure
 *
 * This function करोes the following:
 * - Unpins the physical pages related to the host memory
 * - Free the SG list
 */
व्योम hl_unpin_host_memory(काष्ठा hl_device *hdev, काष्ठा hl_userptr *userptr)
अणु
	hl_debugfs_हटाओ_userptr(hdev, userptr);

	अगर (userptr->dma_mapped)
		hdev->asic_funcs->hl_dma_unmap_sg(hdev, userptr->sgt->sgl,
							userptr->sgt->nents,
							userptr->dir);

	unpin_user_pages_dirty_lock(userptr->pages, userptr->npages, true);
	kvमुक्त(userptr->pages);

	list_del(&userptr->job_node);

	sg_मुक्त_table(userptr->sgt);
	kमुक्त(userptr->sgt);
पूर्ण

/**
 * hl_userptr_delete_list() - clear userptr list.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @userptr_list: poपूर्णांकer to the list to clear.
 *
 * This function करोes the following:
 * - Iterates over the list and unpins the host memory and मुक्तs the userptr
 *   काष्ठाure.
 */
व्योम hl_userptr_delete_list(काष्ठा hl_device *hdev,
				काष्ठा list_head *userptr_list)
अणु
	काष्ठा hl_userptr *userptr, *पंचांगp;

	list_क्रम_each_entry_safe(userptr, पंचांगp, userptr_list, job_node) अणु
		hl_unpin_host_memory(hdev, userptr);
		kमुक्त(userptr);
	पूर्ण

	INIT_LIST_HEAD(userptr_list);
पूर्ण

/**
 * hl_userptr_is_pinned() - वापसs whether the given userptr is pinned.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @userptr_list: poपूर्णांकer to the list to clear.
 * @userptr: poपूर्णांकer to userptr to check.
 *
 * This function करोes the following:
 * - Iterates over the list and checks अगर the given userptr is in it, means is
 *   pinned. If so, वापसs true, otherwise वापसs false.
 */
bool hl_userptr_is_pinned(काष्ठा hl_device *hdev, u64 addr,
				u32 size, काष्ठा list_head *userptr_list,
				काष्ठा hl_userptr **userptr)
अणु
	list_क्रम_each_entry((*userptr), userptr_list, job_node) अणु
		अगर ((addr == (*userptr)->addr) && (size == (*userptr)->size))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * va_range_init() - initialize भव addresses range.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 * @va_range: poपूर्णांकer to the range to initialize.
 * @start: range start address.
 * @end: range end address.
 *
 * This function करोes the following:
 * - Initializes the भव addresses list of the given range with the given
 *   addresses.
 */
अटल पूर्णांक va_range_init(काष्ठा hl_device *hdev, काष्ठा hl_va_range *va_range,
				u64 start, u64 end, u32 page_size)
अणु
	पूर्णांक rc;

	INIT_LIST_HEAD(&va_range->list);

	/*
	 * PAGE_SIZE alignment
	 * it is the callers responsibility to align the addresses अगर the
	 * page size is not a घातer of 2
	 */

	अगर (is_घातer_of_2(page_size)) अणु
		अगर (start & (PAGE_SIZE - 1)) अणु
			start &= PAGE_MASK;
			start += PAGE_SIZE;
		पूर्ण

		अगर (end & (PAGE_SIZE - 1))
			end &= PAGE_MASK;
	पूर्ण

	अगर (start >= end) अणु
		dev_err(hdev->dev, "too small vm range for va list\n");
		वापस -EFAULT;
	पूर्ण

	rc = add_va_block(hdev, va_range, start, end);

	अगर (rc) अणु
		dev_err(hdev->dev, "Failed to init host va list\n");
		वापस rc;
	पूर्ण

	va_range->start_addr = start;
	va_range->end_addr = end;
	va_range->page_size = page_size;

	वापस 0;
पूर्ण

/**
 * va_range_fini() - clear a भव addresses range.
 * @hdev: poपूर्णांकer to the habanaद_असल काष्ठाure.
 * va_range: poपूर्णांकer to भव addresses rang.e
 *
 * This function करोes the following:
 * - Frees the भव addresses block list and its lock.
 */
अटल व्योम va_range_fini(काष्ठा hl_device *hdev, काष्ठा hl_va_range *va_range)
अणु
	mutex_lock(&va_range->lock);
	clear_बहु_सूची_locked(hdev, &va_range->list);
	mutex_unlock(&va_range->lock);

	mutex_destroy(&va_range->lock);
	kमुक्त(va_range);
पूर्ण

/**
 * vm_ctx_init_with_ranges() - initialize भव memory क्रम context.
 * @ctx: poपूर्णांकer to the habanaद_असल context काष्ठाure.
 * @host_range_start: host भव addresses range start.
 * @host_range_end: host भव addresses range end.
 * @host_huge_range_start: host भव addresses range start क्रम memory
 *                         allocated with huge pages.
 * @host_huge_range_end: host भव addresses range end क्रम memory allocated
 *                        with huge pages.
 * @dram_range_start: dram भव addresses range start.
 * @dram_range_end: dram भव addresses range end.
 *
 * This function initializes the following:
 * - MMU क्रम context.
 * - Virtual address to area descriptor hashtable.
 * - Virtual block list of available भव memory.
 */
अटल पूर्णांक vm_ctx_init_with_ranges(काष्ठा hl_ctx *ctx,
					u64 host_range_start,
					u64 host_range_end,
					u32 host_page_size,
					u64 host_huge_range_start,
					u64 host_huge_range_end,
					u32 host_huge_page_size,
					u64 dram_range_start,
					u64 dram_range_end,
					u32 dram_page_size)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	पूर्णांक i, rc;

	क्रम (i = 0 ; i < HL_VA_RANGE_TYPE_MAX ; i++) अणु
		ctx->va_range[i] =
			kzalloc(माप(काष्ठा hl_va_range), GFP_KERNEL);
		अगर (!ctx->va_range[i]) अणु
			rc = -ENOMEM;
			जाओ मुक्त_va_range;
		पूर्ण
	पूर्ण

	rc = hl_mmu_ctx_init(ctx);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to init context %d\n", ctx->asid);
		जाओ मुक्त_va_range;
	पूर्ण

	mutex_init(&ctx->mem_hash_lock);
	hash_init(ctx->mem_hash);

	mutex_init(&ctx->va_range[HL_VA_RANGE_TYPE_HOST]->lock);

	rc = va_range_init(hdev, ctx->va_range[HL_VA_RANGE_TYPE_HOST],
			host_range_start, host_range_end, host_page_size);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to init host vm range\n");
		जाओ mmu_ctx_fini;
	पूर्ण

	अगर (hdev->pmmu_huge_range) अणु
		mutex_init(&ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE]->lock);

		rc = va_range_init(hdev,
			ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE],
			host_huge_range_start, host_huge_range_end,
			host_huge_page_size);
		अगर (rc) अणु
			dev_err(hdev->dev,
				"failed to init host huge vm range\n");
			जाओ clear_host_va_range;
		पूर्ण
	पूर्ण अन्यथा अणु
		kमुक्त(ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE]);
		ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE] =
				ctx->va_range[HL_VA_RANGE_TYPE_HOST];
	पूर्ण

	mutex_init(&ctx->va_range[HL_VA_RANGE_TYPE_DRAM]->lock);

	rc = va_range_init(hdev, ctx->va_range[HL_VA_RANGE_TYPE_DRAM],
			dram_range_start, dram_range_end, dram_page_size);
	अगर (rc) अणु
		dev_err(hdev->dev, "failed to init dram vm range\n");
		जाओ clear_host_huge_va_range;
	पूर्ण

	hl_debugfs_add_ctx_mem_hash(hdev, ctx);

	वापस 0;

clear_host_huge_va_range:
	mutex_destroy(&ctx->va_range[HL_VA_RANGE_TYPE_DRAM]->lock);

	अगर (hdev->pmmu_huge_range) अणु
		mutex_lock(&ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE]->lock);
		clear_बहु_सूची_locked(hdev,
			&ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE]->list);
		mutex_unlock(&ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE]->lock);
	पूर्ण
clear_host_va_range:
	अगर (hdev->pmmu_huge_range)
		mutex_destroy(&ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE]->lock);
	mutex_lock(&ctx->va_range[HL_VA_RANGE_TYPE_HOST]->lock);
	clear_बहु_सूची_locked(hdev, &ctx->va_range[HL_VA_RANGE_TYPE_HOST]->list);
	mutex_unlock(&ctx->va_range[HL_VA_RANGE_TYPE_HOST]->lock);
mmu_ctx_fini:
	mutex_destroy(&ctx->va_range[HL_VA_RANGE_TYPE_HOST]->lock);
	mutex_destroy(&ctx->mem_hash_lock);
	hl_mmu_ctx_fini(ctx);
मुक्त_va_range:
	क्रम (i = 0 ; i < HL_VA_RANGE_TYPE_MAX ; i++)
		kमुक्त(ctx->va_range[i]);

	वापस rc;
पूर्ण

पूर्णांक hl_vm_ctx_init(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा asic_fixed_properties *prop = &ctx->hdev->asic_prop;
	u64 host_range_start, host_range_end, host_huge_range_start,
		host_huge_range_end, dram_range_start, dram_range_end;
	u32 host_page_size, host_huge_page_size, dram_page_size;

	atomic64_set(&ctx->dram_phys_mem, 0);

	/*
	 * - If MMU is enabled, init the ranges as usual.
	 * - If MMU is disabled, in हाल of host mapping, the वापसed address
	 *   is the given one.
	 *   In हाल of DRAM mapping, the वापसed address is the physical
	 *   address of the memory related to the given handle.
	 */
	अगर (!ctx->hdev->mmu_enable)
		वापस 0;

	dram_range_start = prop->dmmu.start_addr;
	dram_range_end = prop->dmmu.end_addr;
	dram_page_size = prop->dram_page_size ?
				prop->dram_page_size : prop->dmmu.page_size;
	host_range_start = prop->pmmu.start_addr;
	host_range_end = prop->pmmu.end_addr;
	host_page_size = prop->pmmu.page_size;
	host_huge_range_start = prop->pmmu_huge.start_addr;
	host_huge_range_end = prop->pmmu_huge.end_addr;
	host_huge_page_size = prop->pmmu_huge.page_size;

	वापस vm_ctx_init_with_ranges(ctx, host_range_start, host_range_end,
			host_page_size, host_huge_range_start,
			host_huge_range_end, host_huge_page_size,
			dram_range_start, dram_range_end, dram_page_size);
पूर्ण

/**
 * hl_vm_ctx_fini() - भव memory tearकरोwn of context.
 * @ctx: poपूर्णांकer to the habanaद_असल context काष्ठाure.
 *
 * This function perक्रमm tearकरोwn the following:
 * - Virtual block list of available भव memory.
 * - Virtual address to area descriptor hashtable.
 * - MMU क्रम context.
 *
 * In addition this function करोes the following:
 * - Unmaps the existing hashtable nodes अगर the hashtable is not empty. The
 *   hashtable should be empty as no valid mappings should exist at this
 *   poपूर्णांक.
 * - Frees any existing physical page list from the idr which relates to the
 *   current context asid.
 * - This function checks the भव block list क्रम correctness. At this poपूर्णांक
 *   the list should contain one element which describes the whole भव
 *   memory range of the context. Otherwise, a warning is prपूर्णांकed.
 */
व्योम hl_vm_ctx_fini(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_device *hdev = ctx->hdev;
	काष्ठा hl_vm *vm = &hdev->vm;
	काष्ठा hl_vm_phys_pg_pack *phys_pg_list;
	काष्ठा hl_vm_hash_node *hnode;
	काष्ठा hlist_node *पंचांगp_node;
	काष्ठा hl_mem_in args;
	पूर्णांक i;

	अगर (!hdev->mmu_enable)
		वापस;

	hl_debugfs_हटाओ_ctx_mem_hash(hdev, ctx);

	/*
	 * Clearly something went wrong on hard reset so no poपूर्णांक in prपूर्णांकing
	 * another side effect error
	 */
	अगर (!hdev->hard_reset_pending && !hash_empty(ctx->mem_hash))
		dev_notice(hdev->dev,
			"user released device without removing its memory mappings\n");

	hash_क्रम_each_safe(ctx->mem_hash, i, पंचांगp_node, hnode, node) अणु
		dev_dbg(hdev->dev,
			"hl_mem_hash_node of vaddr 0x%llx of asid %d is still alive\n",
			hnode->vaddr, ctx->asid);
		args.unmap.device_virt_addr = hnode->vaddr;
		unmap_device_va(ctx, &args, true);
	पूर्ण

	mutex_lock(&ctx->mmu_lock);

	/* invalidate the cache once after the unmapping loop */
	hdev->asic_funcs->mmu_invalidate_cache(hdev, true, VM_TYPE_USERPTR);
	hdev->asic_funcs->mmu_invalidate_cache(hdev, true, VM_TYPE_PHYS_PACK);

	mutex_unlock(&ctx->mmu_lock);

	spin_lock(&vm->idr_lock);
	idr_क्रम_each_entry(&vm->phys_pg_pack_handles, phys_pg_list, i)
		अगर (phys_pg_list->asid == ctx->asid) अणु
			dev_dbg(hdev->dev,
				"page list 0x%px of asid %d is still alive\n",
				phys_pg_list, ctx->asid);
			atomic64_sub(phys_pg_list->total_size,
					&hdev->dram_used_mem);
			मुक्त_phys_pg_pack(hdev, phys_pg_list);
			idr_हटाओ(&vm->phys_pg_pack_handles, i);
		पूर्ण
	spin_unlock(&vm->idr_lock);

	va_range_fini(hdev, ctx->va_range[HL_VA_RANGE_TYPE_DRAM]);
	va_range_fini(hdev, ctx->va_range[HL_VA_RANGE_TYPE_HOST]);

	अगर (hdev->pmmu_huge_range)
		va_range_fini(hdev, ctx->va_range[HL_VA_RANGE_TYPE_HOST_HUGE]);

	mutex_destroy(&ctx->mem_hash_lock);
	hl_mmu_ctx_fini(ctx);

	/* In this हाल we need to clear the global accounting of DRAM usage
	 * because the user notअगरies us on allocations. If the user is no more,
	 * all DRAM is available
	 */
	अगर (ctx->asid != HL_KERNEL_ASID_ID &&
			!hdev->asic_prop.dram_supports_भव_memory)
		atomic64_set(&hdev->dram_used_mem, 0);
पूर्ण

/**
 * hl_vm_init() - initialize भव memory module.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 *
 * This function initializes the following:
 * - MMU module.
 * - DRAM physical pages pool of 2MB.
 * - Idr क्रम device memory allocation handles.
 */
पूर्णांक hl_vm_init(काष्ठा hl_device *hdev)
अणु
	काष्ठा asic_fixed_properties *prop = &hdev->asic_prop;
	काष्ठा hl_vm *vm = &hdev->vm;
	पूर्णांक rc;

	अगर (is_घातer_of_2(prop->dram_page_size))
		vm->dram_pg_pool =
			gen_pool_create(__ffs(prop->dram_page_size), -1);
	अन्यथा
		vm->dram_pg_pool =
			gen_pool_create(__ffs(DRAM_POOL_PAGE_SIZE), -1);

	अगर (!vm->dram_pg_pool) अणु
		dev_err(hdev->dev, "Failed to create dram page pool\n");
		वापस -ENOMEM;
	पूर्ण

	kref_init(&vm->dram_pg_pool_refcount);

	rc = gen_pool_add(vm->dram_pg_pool, prop->dram_user_base_address,
			prop->dram_end_address - prop->dram_user_base_address,
			-1);

	अगर (rc) अणु
		dev_err(hdev->dev,
			"Failed to add memory to dram page pool %d\n", rc);
		जाओ pool_add_err;
	पूर्ण

	spin_lock_init(&vm->idr_lock);
	idr_init(&vm->phys_pg_pack_handles);

	atomic64_set(&hdev->dram_used_mem, 0);

	vm->init_करोne = true;

	वापस 0;

pool_add_err:
	gen_pool_destroy(vm->dram_pg_pool);

	वापस rc;
पूर्ण

/**
 * hl_vm_fini() - भव memory module tearकरोwn.
 * @hdev: poपूर्णांकer to the habanaद_असल device काष्ठाure.
 *
 * This function perक्रमm tearकरोwn to the following:
 * - Idr क्रम device memory allocation handles.
 * - DRAM physical pages pool of 2MB.
 * - MMU module.
 */
व्योम hl_vm_fini(काष्ठा hl_device *hdev)
अणु
	काष्ठा hl_vm *vm = &hdev->vm;

	अगर (!vm->init_करोne)
		वापस;

	/*
	 * At this poपूर्णांक all the contexts should be मुक्तd and hence no DRAM
	 * memory should be in use. Hence the DRAM pool should be मुक्तd here.
	 */
	अगर (kref_put(&vm->dram_pg_pool_refcount, dram_pg_pool_करो_release) != 1)
		dev_warn(hdev->dev, "dram_pg_pool was not destroyed on %s\n",
				__func__);

	vm->init_करोne = false;
पूर्ण

/**
 * hl_hw_block_mem_init() - HW block memory initialization.
 * @ctx: poपूर्णांकer to the habanaद_असल context काष्ठाure.
 *
 * This function initializes the HW block भव mapped addresses list and
 * it's lock.
 */
व्योम hl_hw_block_mem_init(काष्ठा hl_ctx *ctx)
अणु
	mutex_init(&ctx->hw_block_list_lock);
	INIT_LIST_HEAD(&ctx->hw_block_mem_list);
पूर्ण

/**
 * hl_hw_block_mem_fini() - HW block memory tearकरोwn.
 * @ctx: poपूर्णांकer to the habanaद_असल context काष्ठाure.
 *
 * This function clears the HW block भव mapped addresses list and destroys
 * it's lock.
 */
व्योम hl_hw_block_mem_fini(काष्ठा hl_ctx *ctx)
अणु
	काष्ठा hl_vm_hw_block_list_node *lnode, *पंचांगp;

	अगर (!list_empty(&ctx->hw_block_mem_list))
		dev_crit(ctx->hdev->dev, "HW block mem list isn't empty\n");

	list_क्रम_each_entry_safe(lnode, पंचांगp, &ctx->hw_block_mem_list, node) अणु
		list_del(&lnode->node);
		kमुक्त(lnode);
	पूर्ण

	mutex_destroy(&ctx->hw_block_list_lock);
पूर्ण
