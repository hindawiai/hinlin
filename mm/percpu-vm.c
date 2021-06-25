<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/percpu-vm.c - vदो_स्मृति area based chunk allocation
 *
 * Copyright (C) 2010		SUSE Linux Products GmbH
 * Copyright (C) 2010		Tejun Heo <tj@kernel.org>
 *
 * Chunks are mapped पूर्णांकo vदो_स्मृति areas and populated page by page.
 * This is the शेष chunk allocator.
 */
#समावेश "internal.h"

अटल काष्ठा page *pcpu_chunk_page(काष्ठा pcpu_chunk *chunk,
				    अचिन्हित पूर्णांक cpu, पूर्णांक page_idx)
अणु
	/* must not be used on pre-mapped chunk */
	WARN_ON(chunk->immutable);

	वापस vदो_स्मृति_to_page((व्योम *)pcpu_chunk_addr(chunk, cpu, page_idx));
पूर्ण

/**
 * pcpu_get_pages - get temp pages array
 *
 * Returns poपूर्णांकer to array of poपूर्णांकers to काष्ठा page which can be indexed
 * with pcpu_page_idx().  Note that there is only one array and accesses
 * should be serialized by pcpu_alloc_mutex.
 *
 * RETURNS:
 * Poपूर्णांकer to temp pages array on success.
 */
अटल काष्ठा page **pcpu_get_pages(व्योम)
अणु
	अटल काष्ठा page **pages;
	माप_प्रकार pages_size = pcpu_nr_units * pcpu_unit_pages * माप(pages[0]);

	lockdep_निश्चित_held(&pcpu_alloc_mutex);

	अगर (!pages)
		pages = pcpu_mem_zalloc(pages_size, GFP_KERNEL);
	वापस pages;
पूर्ण

/**
 * pcpu_मुक्त_pages - मुक्त pages which were allocated क्रम @chunk
 * @chunk: chunk pages were allocated क्रम
 * @pages: array of pages to be मुक्तd, indexed by pcpu_page_idx()
 * @page_start: page index of the first page to be मुक्तd
 * @page_end: page index of the last page to be मुक्तd + 1
 *
 * Free pages [@page_start and @page_end) in @pages क्रम all units.
 * The pages were allocated क्रम @chunk.
 */
अटल व्योम pcpu_मुक्त_pages(काष्ठा pcpu_chunk *chunk,
			    काष्ठा page **pages, पूर्णांक page_start, पूर्णांक page_end)
अणु
	अचिन्हित पूर्णांक cpu;
	पूर्णांक i;

	क्रम_each_possible_cpu(cpu) अणु
		क्रम (i = page_start; i < page_end; i++) अणु
			काष्ठा page *page = pages[pcpu_page_idx(cpu, i)];

			अगर (page)
				__मुक्त_page(page);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * pcpu_alloc_pages - allocates pages क्रम @chunk
 * @chunk: target chunk
 * @pages: array to put the allocated pages पूर्णांकo, indexed by pcpu_page_idx()
 * @page_start: page index of the first page to be allocated
 * @page_end: page index of the last page to be allocated + 1
 * @gfp: allocation flags passed to the underlying allocator
 *
 * Allocate pages [@page_start,@page_end) पूर्णांकo @pages क्रम all units.
 * The allocation is क्रम @chunk.  Percpu core करोesn't care about the
 * content of @pages and will pass it verbatim to pcpu_map_pages().
 */
अटल पूर्णांक pcpu_alloc_pages(काष्ठा pcpu_chunk *chunk,
			    काष्ठा page **pages, पूर्णांक page_start, पूर्णांक page_end,
			    gfp_t gfp)
अणु
	अचिन्हित पूर्णांक cpu, tcpu;
	पूर्णांक i;

	gfp |= __GFP_HIGHMEM;

	क्रम_each_possible_cpu(cpu) अणु
		क्रम (i = page_start; i < page_end; i++) अणु
			काष्ठा page **pagep = &pages[pcpu_page_idx(cpu, i)];

			*pagep = alloc_pages_node(cpu_to_node(cpu), gfp, 0);
			अगर (!*pagep)
				जाओ err;
		पूर्ण
	पूर्ण
	वापस 0;

err:
	जबतक (--i >= page_start)
		__मुक्त_page(pages[pcpu_page_idx(cpu, i)]);

	क्रम_each_possible_cpu(tcpu) अणु
		अगर (tcpu == cpu)
			अवरोध;
		क्रम (i = page_start; i < page_end; i++)
			__मुक्त_page(pages[pcpu_page_idx(tcpu, i)]);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

/**
 * pcpu_pre_unmap_flush - flush cache prior to unmapping
 * @chunk: chunk the regions to be flushed beदीर्घs to
 * @page_start: page index of the first page to be flushed
 * @page_end: page index of the last page to be flushed + 1
 *
 * Pages in [@page_start,@page_end) of @chunk are about to be
 * unmapped.  Flush cache.  As each flushing trial can be very
 * expensive, issue flush on the whole region at once rather than
 * करोing it क्रम each cpu.  This could be an overसमाप्त but is more
 * scalable.
 */
अटल व्योम pcpu_pre_unmap_flush(काष्ठा pcpu_chunk *chunk,
				 पूर्णांक page_start, पूर्णांक page_end)
अणु
	flush_cache_vunmap(
		pcpu_chunk_addr(chunk, pcpu_low_unit_cpu, page_start),
		pcpu_chunk_addr(chunk, pcpu_high_unit_cpu, page_end));
पूर्ण

अटल व्योम __pcpu_unmap_pages(अचिन्हित दीर्घ addr, पूर्णांक nr_pages)
अणु
	vunmap_range_noflush(addr, addr + (nr_pages << PAGE_SHIFT));
पूर्ण

/**
 * pcpu_unmap_pages - unmap pages out of a pcpu_chunk
 * @chunk: chunk of पूर्णांकerest
 * @pages: pages array which can be used to pass inक्रमmation to मुक्त
 * @page_start: page index of the first page to unmap
 * @page_end: page index of the last page to unmap + 1
 *
 * For each cpu, unmap pages [@page_start,@page_end) out of @chunk.
 * Corresponding elements in @pages were cleared by the caller and can
 * be used to carry inक्रमmation to pcpu_मुक्त_pages() which will be
 * called after all unmaps are finished.  The caller should call
 * proper pre/post flush functions.
 */
अटल व्योम pcpu_unmap_pages(काष्ठा pcpu_chunk *chunk,
			     काष्ठा page **pages, पूर्णांक page_start, पूर्णांक page_end)
अणु
	अचिन्हित पूर्णांक cpu;
	पूर्णांक i;

	क्रम_each_possible_cpu(cpu) अणु
		क्रम (i = page_start; i < page_end; i++) अणु
			काष्ठा page *page;

			page = pcpu_chunk_page(chunk, cpu, i);
			WARN_ON(!page);
			pages[pcpu_page_idx(cpu, i)] = page;
		पूर्ण
		__pcpu_unmap_pages(pcpu_chunk_addr(chunk, cpu, page_start),
				   page_end - page_start);
	पूर्ण
पूर्ण

/**
 * pcpu_post_unmap_tlb_flush - flush TLB after unmapping
 * @chunk: pcpu_chunk the regions to be flushed beदीर्घ to
 * @page_start: page index of the first page to be flushed
 * @page_end: page index of the last page to be flushed + 1
 *
 * Pages [@page_start,@page_end) of @chunk have been unmapped.  Flush
 * TLB क्रम the regions.  This can be skipped अगर the area is to be
 * वापसed to vदो_स्मृति as vदो_स्मृति will handle TLB flushing lazily.
 *
 * As with pcpu_pre_unmap_flush(), TLB flushing also is करोne at once
 * क्रम the whole region.
 */
अटल व्योम pcpu_post_unmap_tlb_flush(काष्ठा pcpu_chunk *chunk,
				      पूर्णांक page_start, पूर्णांक page_end)
अणु
	flush_tlb_kernel_range(
		pcpu_chunk_addr(chunk, pcpu_low_unit_cpu, page_start),
		pcpu_chunk_addr(chunk, pcpu_high_unit_cpu, page_end));
पूर्ण

अटल पूर्णांक __pcpu_map_pages(अचिन्हित दीर्घ addr, काष्ठा page **pages,
			    पूर्णांक nr_pages)
अणु
	वापस vmap_pages_range_noflush(addr, addr + (nr_pages << PAGE_SHIFT),
					PAGE_KERNEL, pages, PAGE_SHIFT);
पूर्ण

/**
 * pcpu_map_pages - map pages पूर्णांकo a pcpu_chunk
 * @chunk: chunk of पूर्णांकerest
 * @pages: pages array containing pages to be mapped
 * @page_start: page index of the first page to map
 * @page_end: page index of the last page to map + 1
 *
 * For each cpu, map pages [@page_start,@page_end) पूर्णांकo @chunk.  The
 * caller is responsible क्रम calling pcpu_post_map_flush() after all
 * mappings are complete.
 *
 * This function is responsible क्रम setting up whatever is necessary क्रम
 * reverse lookup (addr -> chunk).
 */
अटल पूर्णांक pcpu_map_pages(काष्ठा pcpu_chunk *chunk,
			  काष्ठा page **pages, पूर्णांक page_start, पूर्णांक page_end)
अणु
	अचिन्हित पूर्णांक cpu, tcpu;
	पूर्णांक i, err;

	क्रम_each_possible_cpu(cpu) अणु
		err = __pcpu_map_pages(pcpu_chunk_addr(chunk, cpu, page_start),
				       &pages[pcpu_page_idx(cpu, page_start)],
				       page_end - page_start);
		अगर (err < 0)
			जाओ err;

		क्रम (i = page_start; i < page_end; i++)
			pcpu_set_page_chunk(pages[pcpu_page_idx(cpu, i)],
					    chunk);
	पूर्ण
	वापस 0;
err:
	क्रम_each_possible_cpu(tcpu) अणु
		अगर (tcpu == cpu)
			अवरोध;
		__pcpu_unmap_pages(pcpu_chunk_addr(chunk, tcpu, page_start),
				   page_end - page_start);
	पूर्ण
	pcpu_post_unmap_tlb_flush(chunk, page_start, page_end);
	वापस err;
पूर्ण

/**
 * pcpu_post_map_flush - flush cache after mapping
 * @chunk: pcpu_chunk the regions to be flushed beदीर्घ to
 * @page_start: page index of the first page to be flushed
 * @page_end: page index of the last page to be flushed + 1
 *
 * Pages [@page_start,@page_end) of @chunk have been mapped.  Flush
 * cache.
 *
 * As with pcpu_pre_unmap_flush(), TLB flushing also is करोne at once
 * क्रम the whole region.
 */
अटल व्योम pcpu_post_map_flush(काष्ठा pcpu_chunk *chunk,
				पूर्णांक page_start, पूर्णांक page_end)
अणु
	flush_cache_vmap(
		pcpu_chunk_addr(chunk, pcpu_low_unit_cpu, page_start),
		pcpu_chunk_addr(chunk, pcpu_high_unit_cpu, page_end));
पूर्ण

/**
 * pcpu_populate_chunk - populate and map an area of a pcpu_chunk
 * @chunk: chunk of पूर्णांकerest
 * @page_start: the start page
 * @page_end: the end page
 * @gfp: allocation flags passed to the underlying memory allocator
 *
 * For each cpu, populate and map pages [@page_start,@page_end) पूर्णांकo
 * @chunk.
 *
 * CONTEXT:
 * pcpu_alloc_mutex, करोes GFP_KERNEL allocation.
 */
अटल पूर्णांक pcpu_populate_chunk(काष्ठा pcpu_chunk *chunk,
			       पूर्णांक page_start, पूर्णांक page_end, gfp_t gfp)
अणु
	काष्ठा page **pages;

	pages = pcpu_get_pages();
	अगर (!pages)
		वापस -ENOMEM;

	अगर (pcpu_alloc_pages(chunk, pages, page_start, page_end, gfp))
		वापस -ENOMEM;

	अगर (pcpu_map_pages(chunk, pages, page_start, page_end)) अणु
		pcpu_मुक्त_pages(chunk, pages, page_start, page_end);
		वापस -ENOMEM;
	पूर्ण
	pcpu_post_map_flush(chunk, page_start, page_end);

	वापस 0;
पूर्ण

/**
 * pcpu_depopulate_chunk - depopulate and unmap an area of a pcpu_chunk
 * @chunk: chunk to depopulate
 * @page_start: the start page
 * @page_end: the end page
 *
 * For each cpu, depopulate and unmap pages [@page_start,@page_end)
 * from @chunk.
 *
 * CONTEXT:
 * pcpu_alloc_mutex.
 */
अटल व्योम pcpu_depopulate_chunk(काष्ठा pcpu_chunk *chunk,
				  पूर्णांक page_start, पूर्णांक page_end)
अणु
	काष्ठा page **pages;

	/*
	 * If control reaches here, there must have been at least one
	 * successful population attempt so the temp pages array must
	 * be available now.
	 */
	pages = pcpu_get_pages();
	BUG_ON(!pages);

	/* unmap and मुक्त */
	pcpu_pre_unmap_flush(chunk, page_start, page_end);

	pcpu_unmap_pages(chunk, pages, page_start, page_end);

	/* no need to flush tlb, vदो_स्मृति will handle it lazily */

	pcpu_मुक्त_pages(chunk, pages, page_start, page_end);
पूर्ण

अटल काष्ठा pcpu_chunk *pcpu_create_chunk(क्रमागत pcpu_chunk_type type,
					    gfp_t gfp)
अणु
	काष्ठा pcpu_chunk *chunk;
	काष्ठा vm_काष्ठा **vms;

	chunk = pcpu_alloc_chunk(type, gfp);
	अगर (!chunk)
		वापस शून्य;

	vms = pcpu_get_vm_areas(pcpu_group_offsets, pcpu_group_sizes,
				pcpu_nr_groups, pcpu_atom_size);
	अगर (!vms) अणु
		pcpu_मुक्त_chunk(chunk);
		वापस शून्य;
	पूर्ण

	chunk->data = vms;
	chunk->base_addr = vms[0]->addr - pcpu_group_offsets[0];

	pcpu_stats_chunk_alloc();
	trace_percpu_create_chunk(chunk->base_addr);

	वापस chunk;
पूर्ण

अटल व्योम pcpu_destroy_chunk(काष्ठा pcpu_chunk *chunk)
अणु
	अगर (!chunk)
		वापस;

	pcpu_stats_chunk_dealloc();
	trace_percpu_destroy_chunk(chunk->base_addr);

	अगर (chunk->data)
		pcpu_मुक्त_vm_areas(chunk->data, pcpu_nr_groups);
	pcpu_मुक्त_chunk(chunk);
पूर्ण

अटल काष्ठा page *pcpu_addr_to_page(व्योम *addr)
अणु
	वापस vदो_स्मृति_to_page(addr);
पूर्ण

अटल पूर्णांक __init pcpu_verअगरy_alloc_info(स्थिर काष्ठा pcpu_alloc_info *ai)
अणु
	/* no extra restriction */
	वापस 0;
पूर्ण
