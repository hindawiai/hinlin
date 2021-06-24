<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2001-2008 Silicon Graphics, Inc.  All rights reserved.
 *
 * A simple uncached page allocator using the generic allocator. This
 * allocator first utilizes the spare (spill) pages found in the EFI
 * memmap and will then start converting cached pages to uncached ones
 * at a granule at a समय. Node awareness is implemented by having a
 * pool of pages per node.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/efi.h>
#समावेश <linux/nmi.h>
#समावेश <linux/genभाग.स>
#समावेश <linux/gfp.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/pal.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/tlbflush.h>

काष्ठा uncached_pool अणु
	काष्ठा gen_pool *pool;
	काष्ठा mutex add_chunk_mutex;	/* serialize adding a converted chunk */
	पूर्णांक nchunks_added;		/* #of converted chunks added to pool */
	atomic_t status;		/* smp called function's वापस status*/
पूर्ण;

#घोषणा MAX_CONVERTED_CHUNKS_PER_NODE	2

काष्ठा uncached_pool uncached_pools[MAX_NUMNODES];


अटल व्योम uncached_ipi_visibility(व्योम *data)
अणु
	पूर्णांक status;
	काष्ठा uncached_pool *uc_pool = (काष्ठा uncached_pool *)data;

	status = ia64_pal_prefetch_visibility(PAL_VISIBILITY_PHYSICAL);
	अगर ((status != PAL_VISIBILITY_OK) &&
	    (status != PAL_VISIBILITY_OK_REMOTE_NEEDED))
		atomic_inc(&uc_pool->status);
पूर्ण


अटल व्योम uncached_ipi_mc_drain(व्योम *data)
अणु
	पूर्णांक status;
	काष्ठा uncached_pool *uc_pool = (काष्ठा uncached_pool *)data;

	status = ia64_pal_mc_drain();
	अगर (status != PAL_STATUS_SUCCESS)
		atomic_inc(&uc_pool->status);
पूर्ण


/*
 * Add a new chunk of uncached memory pages to the specअगरied pool.
 *
 * @pool: pool to add new chunk of uncached memory to
 * @nid: node id of node to allocate memory from, or -1
 *
 * This is accomplished by first allocating a granule of cached memory pages
 * and then converting them to uncached memory pages.
 */
अटल पूर्णांक uncached_add_chunk(काष्ठा uncached_pool *uc_pool, पूर्णांक nid)
अणु
	काष्ठा page *page;
	पूर्णांक status, i, nchunks_added = uc_pool->nchunks_added;
	अचिन्हित दीर्घ c_addr, uc_addr;

	अगर (mutex_lock_पूर्णांकerruptible(&uc_pool->add_chunk_mutex) != 0)
		वापस -1;	/* पूर्णांकerrupted by a संकेत */

	अगर (uc_pool->nchunks_added > nchunks_added) अणु
		/* someone added a new chunk जबतक we were रुकोing */
		mutex_unlock(&uc_pool->add_chunk_mutex);
		वापस 0;
	पूर्ण

	अगर (uc_pool->nchunks_added >= MAX_CONVERTED_CHUNKS_PER_NODE) अणु
		mutex_unlock(&uc_pool->add_chunk_mutex);
		वापस -1;
	पूर्ण

	/* attempt to allocate a granule's worth of cached memory pages */

	page = __alloc_pages_node(nid,
				GFP_KERNEL | __GFP_ZERO | __GFP_THISNODE,
				IA64_GRANULE_SHIFT-PAGE_SHIFT);
	अगर (!page) अणु
		mutex_unlock(&uc_pool->add_chunk_mutex);
		वापस -1;
	पूर्ण

	/* convert the memory pages from cached to uncached */

	c_addr = (अचिन्हित दीर्घ)page_address(page);
	uc_addr = c_addr - PAGE_OFFSET + __IA64_UNCACHED_OFFSET;

	/*
	 * There's a small race here where it's possible क्रम someone to
	 * access the page through /dev/mem halfway through the conversion
	 * to uncached - not sure it's really worth bothering about
	 */
	क्रम (i = 0; i < (IA64_GRANULE_SIZE / PAGE_SIZE); i++)
		SetPageUncached(&page[i]);

	flush_tlb_kernel_range(uc_addr, uc_addr + IA64_GRANULE_SIZE);

	status = ia64_pal_prefetch_visibility(PAL_VISIBILITY_PHYSICAL);
	अगर (status == PAL_VISIBILITY_OK_REMOTE_NEEDED) अणु
		atomic_set(&uc_pool->status, 0);
		smp_call_function(uncached_ipi_visibility, uc_pool, 1);
		अगर (atomic_पढ़ो(&uc_pool->status))
			जाओ failed;
	पूर्ण अन्यथा अगर (status != PAL_VISIBILITY_OK)
		जाओ failed;

	preempt_disable();

	flush_icache_range(uc_addr, uc_addr + IA64_GRANULE_SIZE);

	/* flush the just पूर्णांकroduced uncached translation from the TLB */
	local_flush_tlb_all();

	preempt_enable();

	status = ia64_pal_mc_drain();
	अगर (status != PAL_STATUS_SUCCESS)
		जाओ failed;
	atomic_set(&uc_pool->status, 0);
	smp_call_function(uncached_ipi_mc_drain, uc_pool, 1);
	अगर (atomic_पढ़ो(&uc_pool->status))
		जाओ failed;

	/*
	 * The chunk of memory pages has been converted to uncached so now we
	 * can add it to the pool.
	 */
	status = gen_pool_add(uc_pool->pool, uc_addr, IA64_GRANULE_SIZE, nid);
	अगर (status)
		जाओ failed;

	uc_pool->nchunks_added++;
	mutex_unlock(&uc_pool->add_chunk_mutex);
	वापस 0;

	/* failed to convert or add the chunk so give it back to the kernel */
failed:
	क्रम (i = 0; i < (IA64_GRANULE_SIZE / PAGE_SIZE); i++)
		ClearPageUncached(&page[i]);

	मुक्त_pages(c_addr, IA64_GRANULE_SHIFT-PAGE_SHIFT);
	mutex_unlock(&uc_pool->add_chunk_mutex);
	वापस -1;
पूर्ण


/*
 * uncached_alloc_page
 *
 * @starting_nid: node id of node to start with, or -1
 * @n_pages: number of contiguous pages to allocate
 *
 * Allocate the specअगरied number of contiguous uncached pages on the
 * the requested node. If not enough contiguous uncached pages are available
 * on the requested node, roundrobin starting with the next higher node.
 */
अचिन्हित दीर्घ uncached_alloc_page(पूर्णांक starting_nid, पूर्णांक n_pages)
अणु
	अचिन्हित दीर्घ uc_addr;
	काष्ठा uncached_pool *uc_pool;
	पूर्णांक nid;

	अगर (unlikely(starting_nid >= MAX_NUMNODES))
		वापस 0;

	अगर (starting_nid < 0)
		starting_nid = numa_node_id();
	nid = starting_nid;

	करो अणु
		अगर (!node_state(nid, N_HIGH_MEMORY))
			जारी;
		uc_pool = &uncached_pools[nid];
		अगर (uc_pool->pool == शून्य)
			जारी;
		करो अणु
			uc_addr = gen_pool_alloc(uc_pool->pool,
						 n_pages * PAGE_SIZE);
			अगर (uc_addr != 0)
				वापस uc_addr;
		पूर्ण जबतक (uncached_add_chunk(uc_pool, nid) == 0);

	पूर्ण जबतक ((nid = (nid + 1) % MAX_NUMNODES) != starting_nid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(uncached_alloc_page);


/*
 * uncached_मुक्त_page
 *
 * @uc_addr: uncached address of first page to मुक्त
 * @n_pages: number of contiguous pages to मुक्त
 *
 * Free the specअगरied number of uncached pages.
 */
व्योम uncached_मुक्त_page(अचिन्हित दीर्घ uc_addr, पूर्णांक n_pages)
अणु
	पूर्णांक nid = paddr_to_nid(uc_addr - __IA64_UNCACHED_OFFSET);
	काष्ठा gen_pool *pool = uncached_pools[nid].pool;

	अगर (unlikely(pool == शून्य))
		वापस;

	अगर ((uc_addr & (0XFUL << 60)) != __IA64_UNCACHED_OFFSET)
		panic("uncached_free_page invalid address %lx\n", uc_addr);

	gen_pool_मुक्त(pool, uc_addr, n_pages * PAGE_SIZE);
पूर्ण
EXPORT_SYMBOL(uncached_मुक्त_page);


/*
 * uncached_build_memmap,
 *
 * @uc_start: uncached starting address of a chunk of uncached memory
 * @uc_end: uncached ending address of a chunk of uncached memory
 * @arg: ignored, (शून्य argument passed in on call to efi_memmap_walk_uc())
 *
 * Called at boot समय to build a map of pages that can be used क्रम
 * memory special operations.
 */
अटल पूर्णांक __init uncached_build_memmap(u64 uc_start, u64 uc_end, व्योम *arg)
अणु
	पूर्णांक nid = paddr_to_nid(uc_start - __IA64_UNCACHED_OFFSET);
	काष्ठा gen_pool *pool = uncached_pools[nid].pool;
	माप_प्रकार size = uc_end - uc_start;

	touch_softlockup_watchकरोg();

	अगर (pool != शून्य) अणु
		स_रखो((अक्षर *)uc_start, 0, size);
		(व्योम) gen_pool_add(pool, uc_start, size, nid);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक __init uncached_init(व्योम)
अणु
	पूर्णांक nid;

	क्रम_each_node_state(nid, N_ONLINE) अणु
		uncached_pools[nid].pool = gen_pool_create(PAGE_SHIFT, nid);
		mutex_init(&uncached_pools[nid].add_chunk_mutex);
	पूर्ण

	efi_memmap_walk_uc(uncached_build_memmap, शून्य);
	वापस 0;
पूर्ण

__initcall(uncached_init);
