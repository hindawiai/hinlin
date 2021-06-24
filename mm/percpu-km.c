<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/percpu-km.c - kernel memory based chunk allocation
 *
 * Copyright (C) 2010		SUSE Linux Products GmbH
 * Copyright (C) 2010		Tejun Heo <tj@kernel.org>
 *
 * Chunks are allocated as a contiguous kernel memory using gfp
 * allocation.  This is to be used on nommu architectures.
 *
 * To use percpu-km,
 *
 * - define CONFIG_NEED_PER_CPU_KM from the arch Kconfig.
 *
 * - CONFIG_NEED_PER_CPU_PAGE_FIRST_CHUNK must not be defined.  It's
 *   not compatible with PER_CPU_KM.  EMBED_FIRST_CHUNK should work
 *   fine.
 *
 * - NUMA is not supported.  When setting up the first chunk,
 *   @cpu_distance_fn should be शून्य or report all CPUs to be nearer
 *   than or at LOCAL_DISTANCE.
 *
 * - It's best अगर the chunk size is घातer of two multiple of
 *   PAGE_SIZE.  Because each chunk is allocated as a contiguous
 *   kernel memory block using alloc_pages(), memory will be wasted अगर
 *   chunk size is not aligned.  percpu-km code will whine about it.
 */

#अगर defined(CONFIG_SMP) && defined(CONFIG_NEED_PER_CPU_PAGE_FIRST_CHUNK)
#त्रुटि "contiguous percpu allocation is incompatible with paged first chunk"
#पूर्ण_अगर

#समावेश <linux/log2.h>

अटल पूर्णांक pcpu_populate_chunk(काष्ठा pcpu_chunk *chunk,
			       पूर्णांक page_start, पूर्णांक page_end, gfp_t gfp)
अणु
	वापस 0;
पूर्ण

अटल व्योम pcpu_depopulate_chunk(काष्ठा pcpu_chunk *chunk,
				  पूर्णांक page_start, पूर्णांक page_end)
अणु
	/* nada */
पूर्ण

अटल काष्ठा pcpu_chunk *pcpu_create_chunk(क्रमागत pcpu_chunk_type type,
					    gfp_t gfp)
अणु
	स्थिर पूर्णांक nr_pages = pcpu_group_sizes[0] >> PAGE_SHIFT;
	काष्ठा pcpu_chunk *chunk;
	काष्ठा page *pages;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	chunk = pcpu_alloc_chunk(type, gfp);
	अगर (!chunk)
		वापस शून्य;

	pages = alloc_pages(gfp, order_base_2(nr_pages));
	अगर (!pages) अणु
		pcpu_मुक्त_chunk(chunk);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++)
		pcpu_set_page_chunk(nth_page(pages, i), chunk);

	chunk->data = pages;
	chunk->base_addr = page_address(pages);

	spin_lock_irqsave(&pcpu_lock, flags);
	pcpu_chunk_populated(chunk, 0, nr_pages);
	spin_unlock_irqrestore(&pcpu_lock, flags);

	pcpu_stats_chunk_alloc();
	trace_percpu_create_chunk(chunk->base_addr);

	वापस chunk;
पूर्ण

अटल व्योम pcpu_destroy_chunk(काष्ठा pcpu_chunk *chunk)
अणु
	स्थिर पूर्णांक nr_pages = pcpu_group_sizes[0] >> PAGE_SHIFT;

	अगर (!chunk)
		वापस;

	pcpu_stats_chunk_dealloc();
	trace_percpu_destroy_chunk(chunk->base_addr);

	अगर (chunk->data)
		__मुक्त_pages(chunk->data, order_base_2(nr_pages));
	pcpu_मुक्त_chunk(chunk);
पूर्ण

अटल काष्ठा page *pcpu_addr_to_page(व्योम *addr)
अणु
	वापस virt_to_page(addr);
पूर्ण

अटल पूर्णांक __init pcpu_verअगरy_alloc_info(स्थिर काष्ठा pcpu_alloc_info *ai)
अणु
	माप_प्रकार nr_pages, alloc_pages;

	/* all units must be in a single group */
	अगर (ai->nr_groups != 1) अणु
		pr_crit("can't handle more than one group\n");
		वापस -EINVAL;
	पूर्ण

	nr_pages = (ai->groups[0].nr_units * ai->unit_size) >> PAGE_SHIFT;
	alloc_pages = roundup_घात_of_two(nr_pages);

	अगर (alloc_pages > nr_pages)
		pr_warn("wasting %zu pages per chunk\n",
			alloc_pages - nr_pages);

	वापस 0;
पूर्ण
