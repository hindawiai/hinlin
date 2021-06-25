<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mm/percpu.c - percpu memory allocator
 *
 * Copyright (C) 2009		SUSE Linux Products GmbH
 * Copyright (C) 2009		Tejun Heo <tj@kernel.org>
 *
 * Copyright (C) 2017		Facebook Inc.
 * Copyright (C) 2017		Dennis Zhou <dennis@kernel.org>
 *
 * The percpu allocator handles both अटल and dynamic areas.  Percpu
 * areas are allocated in chunks which are भागided पूर्णांकo units.  There is
 * a 1-to-1 mapping क्रम units to possible cpus.  These units are grouped
 * based on NUMA properties of the machine.
 *
 *  c0                           c1                         c2
 *  -------------------          -------------------        ------------
 * | u0 | u1 | u2 | u3 |        | u0 | u1 | u2 | u3 |      | u0 | u1 | u
 *  -------------------  ......  -------------------  ....  ------------
 *
 * Allocation is करोne by offsets पूर्णांकo a unit's address space.  Ie., an
 * area of 512 bytes at 6k in c1 occupies 512 bytes at 6k in c1:u0,
 * c1:u1, c1:u2, etc.  On NUMA machines, the mapping may be non-linear
 * and even sparse.  Access is handled by configuring percpu base
 * रेजिस्टरs according to the cpu to unit mappings and offsetting the
 * base address using pcpu_unit_size.
 *
 * There is special consideration क्रम the first chunk which must handle
 * the अटल percpu variables in the kernel image as allocation services
 * are not online yet.  In लघु, the first chunk is काष्ठाured like so:
 *
 *                  <Static | [Reserved] | Dynamic>
 *
 * The अटल data is copied from the original section managed by the
 * linker.  The reserved section, अगर non-zero, primarily manages अटल
 * percpu variables from kernel modules.  Finally, the dynamic section
 * takes care of normal allocations.
 *
 * The allocator organizes chunks पूर्णांकo lists according to मुक्त size and
 * memcg-awareness.  To make a percpu allocation memcg-aware the __GFP_ACCOUNT
 * flag should be passed.  All memcg-aware allocations are sharing one set
 * of chunks and all unaccounted allocations and allocations perक्रमmed
 * by processes beदीर्घing to the root memory cgroup are using the second set.
 *
 * The allocator tries to allocate from the fullest chunk first. Each chunk
 * is managed by a biपंचांगap with metadata blocks.  The allocation map is updated
 * on every allocation and मुक्त to reflect the current state जबतक the boundary
 * map is only updated on allocation.  Each metadata block contains
 * inक्रमmation to help mitigate the need to iterate over large portions
 * of the biपंचांगap.  The reverse mapping from page to chunk is stored in
 * the page's index.  Lastly, units are lazily backed and grow in unison.
 *
 * There is a unique conversion that goes on here between bytes and bits.
 * Each bit represents a fragment of size PCPU_MIN_ALLOC_SIZE.  The chunk
 * tracks the number of pages it is responsible क्रम in nr_pages.  Helper
 * functions are used to convert from between the bytes, bits, and blocks.
 * All hपूर्णांकs are managed in bits unless explicitly stated.
 *
 * To use this allocator, arch code should करो the following:
 *
 * - define __addr_to_pcpu_ptr() and __pcpu_ptr_to_addr() to translate
 *   regular address to percpu poपूर्णांकer and back अगर they need to be
 *   dअगरferent from the शेष
 *
 * - use pcpu_setup_first_chunk() during percpu area initialization to
 *   setup the first chunk containing the kernel अटल percpu area
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/memblock.h>
#समावेश <linux/err.h>
#समावेश <linux/lcm.h>
#समावेश <linux/list.h>
#समावेश <linux/log2.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/percpu.h>
#समावेश <linux/pfn.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/memcontrol.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/पन.स>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/percpu.h>

#समावेश "percpu-internal.h"

/* the slots are sorted by मुक्त bytes left, 1-31 bytes share the same slot */
#घोषणा PCPU_SLOT_BASE_SHIFT		5
/* chunks in slots below this are subject to being sidelined on failed alloc */
#घोषणा PCPU_SLOT_FAIL_THRESHOLD	3

#घोषणा PCPU_EMPTY_POP_PAGES_LOW	2
#घोषणा PCPU_EMPTY_POP_PAGES_HIGH	4

#अगर_घोषित CONFIG_SMP
/* शेष addr <-> pcpu_ptr mapping, override in यंत्र/percpu.h अगर necessary */
#अगर_अघोषित __addr_to_pcpu_ptr
#घोषणा __addr_to_pcpu_ptr(addr)					\
	(व्योम __percpu *)((अचिन्हित दीर्घ)(addr) -			\
			  (अचिन्हित दीर्घ)pcpu_base_addr	+		\
			  (अचिन्हित दीर्घ)__per_cpu_start)
#पूर्ण_अगर
#अगर_अघोषित __pcpu_ptr_to_addr
#घोषणा __pcpu_ptr_to_addr(ptr)						\
	(व्योम __क्रमce *)((अचिन्हित दीर्घ)(ptr) +				\
			 (अचिन्हित दीर्घ)pcpu_base_addr -		\
			 (अचिन्हित दीर्घ)__per_cpu_start)
#पूर्ण_अगर
#अन्यथा	/* CONFIG_SMP */
/* on UP, it's always identity mapped */
#घोषणा __addr_to_pcpu_ptr(addr)	(व्योम __percpu *)(addr)
#घोषणा __pcpu_ptr_to_addr(ptr)		(व्योम __क्रमce *)(ptr)
#पूर्ण_अगर	/* CONFIG_SMP */

अटल पूर्णांक pcpu_unit_pages __ro_after_init;
अटल पूर्णांक pcpu_unit_size __ro_after_init;
अटल पूर्णांक pcpu_nr_units __ro_after_init;
अटल पूर्णांक pcpu_atom_size __ro_after_init;
पूर्णांक pcpu_nr_slots __ro_after_init;
अटल माप_प्रकार pcpu_chunk_काष्ठा_size __ro_after_init;

/* cpus with the lowest and highest unit addresses */
अटल अचिन्हित पूर्णांक pcpu_low_unit_cpu __ro_after_init;
अटल अचिन्हित पूर्णांक pcpu_high_unit_cpu __ro_after_init;

/* the address of the first chunk which starts with the kernel अटल area */
व्योम *pcpu_base_addr __ro_after_init;
EXPORT_SYMBOL_GPL(pcpu_base_addr);

अटल स्थिर पूर्णांक *pcpu_unit_map __ro_after_init;		/* cpu -> unit */
स्थिर अचिन्हित दीर्घ *pcpu_unit_offsets __ro_after_init;	/* cpu -> unit offset */

/* group inक्रमmation, used क्रम vm allocation */
अटल पूर्णांक pcpu_nr_groups __ro_after_init;
अटल स्थिर अचिन्हित दीर्घ *pcpu_group_offsets __ro_after_init;
अटल स्थिर माप_प्रकार *pcpu_group_sizes __ro_after_init;

/*
 * The first chunk which always exists.  Note that unlike other
 * chunks, this one can be allocated and mapped in several dअगरferent
 * ways and thus often करोesn't live in the vदो_स्मृति area.
 */
काष्ठा pcpu_chunk *pcpu_first_chunk __ro_after_init;

/*
 * Optional reserved chunk.  This chunk reserves part of the first
 * chunk and serves it क्रम reserved allocations.  When the reserved
 * region करोesn't exist, the following variable is शून्य.
 */
काष्ठा pcpu_chunk *pcpu_reserved_chunk __ro_after_init;

DEFINE_SPINLOCK(pcpu_lock);	/* all पूर्णांकernal data काष्ठाures */
अटल DEFINE_MUTEX(pcpu_alloc_mutex);	/* chunk create/destroy, [de]pop, map ext */

काष्ठा list_head *pcpu_chunk_lists __ro_after_init; /* chunk list slots */

/* chunks which need their map areas extended, रक्षित by pcpu_lock */
अटल LIST_HEAD(pcpu_map_extend_chunks);

/*
 * The number of empty populated pages by chunk type, रक्षित by pcpu_lock.
 * The reserved chunk करोesn't contribute to the count.
 */
पूर्णांक pcpu_nr_empty_pop_pages[PCPU_NR_CHUNK_TYPES];

/*
 * The number of populated pages in use by the allocator, रक्षित by
 * pcpu_lock.  This number is kept per a unit per chunk (i.e. when a page माला_लो
 * allocated/deallocated, it is allocated/deallocated in all units of a chunk
 * and increments/decrements this count by 1).
 */
अटल अचिन्हित दीर्घ pcpu_nr_populated;

/*
 * Balance work is used to populate or destroy chunks asynchronously.  We
 * try to keep the number of populated मुक्त pages between
 * PCPU_EMPTY_POP_PAGES_LOW and HIGH क्रम atomic allocations and at most one
 * empty chunk.
 */
अटल व्योम pcpu_balance_workfn(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(pcpu_balance_work, pcpu_balance_workfn);
अटल bool pcpu_async_enabled __पढ़ो_mostly;
अटल bool pcpu_atomic_alloc_failed;

अटल व्योम pcpu_schedule_balance_work(व्योम)
अणु
	अगर (pcpu_async_enabled)
		schedule_work(&pcpu_balance_work);
पूर्ण

/**
 * pcpu_addr_in_chunk - check अगर the address is served from this chunk
 * @chunk: chunk of पूर्णांकerest
 * @addr: percpu address
 *
 * RETURNS:
 * True अगर the address is served from this chunk.
 */
अटल bool pcpu_addr_in_chunk(काष्ठा pcpu_chunk *chunk, व्योम *addr)
अणु
	व्योम *start_addr, *end_addr;

	अगर (!chunk)
		वापस false;

	start_addr = chunk->base_addr + chunk->start_offset;
	end_addr = chunk->base_addr + chunk->nr_pages * PAGE_SIZE -
		   chunk->end_offset;

	वापस addr >= start_addr && addr < end_addr;
पूर्ण

अटल पूर्णांक __pcpu_माप_प्रकारo_slot(पूर्णांक size)
अणु
	पूर्णांक highbit = fls(size);	/* size is in bytes */
	वापस max(highbit - PCPU_SLOT_BASE_SHIFT + 2, 1);
पूर्ण

अटल पूर्णांक pcpu_माप_प्रकारo_slot(पूर्णांक size)
अणु
	अगर (size == pcpu_unit_size)
		वापस pcpu_nr_slots - 1;
	वापस __pcpu_माप_प्रकारo_slot(size);
पूर्ण

अटल पूर्णांक pcpu_chunk_slot(स्थिर काष्ठा pcpu_chunk *chunk)
अणु
	स्थिर काष्ठा pcpu_block_md *chunk_md = &chunk->chunk_md;

	अगर (chunk->मुक्त_bytes < PCPU_MIN_ALLOC_SIZE ||
	    chunk_md->contig_hपूर्णांक == 0)
		वापस 0;

	वापस pcpu_माप_प्रकारo_slot(chunk_md->contig_hपूर्णांक * PCPU_MIN_ALLOC_SIZE);
पूर्ण

/* set the poपूर्णांकer to a chunk in a page काष्ठा */
अटल व्योम pcpu_set_page_chunk(काष्ठा page *page, काष्ठा pcpu_chunk *pcpu)
अणु
	page->index = (अचिन्हित दीर्घ)pcpu;
पूर्ण

/* obtain poपूर्णांकer to a chunk from a page काष्ठा */
अटल काष्ठा pcpu_chunk *pcpu_get_page_chunk(काष्ठा page *page)
अणु
	वापस (काष्ठा pcpu_chunk *)page->index;
पूर्ण

अटल पूर्णांक __maybe_unused pcpu_page_idx(अचिन्हित पूर्णांक cpu, पूर्णांक page_idx)
अणु
	वापस pcpu_unit_map[cpu] * pcpu_unit_pages + page_idx;
पूर्ण

अटल अचिन्हित दीर्घ pcpu_unit_page_offset(अचिन्हित पूर्णांक cpu, पूर्णांक page_idx)
अणु
	वापस pcpu_unit_offsets[cpu] + (page_idx << PAGE_SHIFT);
पूर्ण

अटल अचिन्हित दीर्घ pcpu_chunk_addr(काष्ठा pcpu_chunk *chunk,
				     अचिन्हित पूर्णांक cpu, पूर्णांक page_idx)
अणु
	वापस (अचिन्हित दीर्घ)chunk->base_addr +
	       pcpu_unit_page_offset(cpu, page_idx);
पूर्ण

/*
 * The following are helper functions to help access biपंचांगaps and convert
 * between biपंचांगap offsets to address offsets.
 */
अटल अचिन्हित दीर्घ *pcpu_index_alloc_map(काष्ठा pcpu_chunk *chunk, पूर्णांक index)
अणु
	वापस chunk->alloc_map +
	       (index * PCPU_BITMAP_BLOCK_BITS / BITS_PER_LONG);
पूर्ण

अटल अचिन्हित दीर्घ pcpu_off_to_block_index(पूर्णांक off)
अणु
	वापस off / PCPU_BITMAP_BLOCK_BITS;
पूर्ण

अटल अचिन्हित दीर्घ pcpu_off_to_block_off(पूर्णांक off)
अणु
	वापस off & (PCPU_BITMAP_BLOCK_BITS - 1);
पूर्ण

अटल अचिन्हित दीर्घ pcpu_block_off_to_off(पूर्णांक index, पूर्णांक off)
अणु
	वापस index * PCPU_BITMAP_BLOCK_BITS + off;
पूर्ण

/*
 * pcpu_next_hपूर्णांक - determine which hपूर्णांक to use
 * @block: block of पूर्णांकerest
 * @alloc_bits: size of allocation
 *
 * This determines अगर we should scan based on the scan_hपूर्णांक or first_मुक्त.
 * In general, we want to scan from first_मुक्त to fulfill allocations by
 * first fit.  However, अगर we know a scan_hपूर्णांक at position scan_hपूर्णांक_start
 * cannot fulfill an allocation, we can begin scanning from there knowing
 * the contig_hपूर्णांक will be our fallback.
 */
अटल पूर्णांक pcpu_next_hपूर्णांक(काष्ठा pcpu_block_md *block, पूर्णांक alloc_bits)
अणु
	/*
	 * The three conditions below determine अगर we can skip past the
	 * scan_hपूर्णांक.  First, करोes the scan hपूर्णांक exist.  Second, is the
	 * contig_hपूर्णांक after the scan_hपूर्णांक (possibly not true अगरf
	 * contig_hपूर्णांक == scan_hपूर्णांक).  Third, is the allocation request
	 * larger than the scan_hपूर्णांक.
	 */
	अगर (block->scan_hपूर्णांक &&
	    block->contig_hपूर्णांक_start > block->scan_hपूर्णांक_start &&
	    alloc_bits > block->scan_hपूर्णांक)
		वापस block->scan_hपूर्णांक_start + block->scan_hपूर्णांक;

	वापस block->first_मुक्त;
पूर्ण

/**
 * pcpu_next_md_मुक्त_region - finds the next hपूर्णांक मुक्त area
 * @chunk: chunk of पूर्णांकerest
 * @bit_off: chunk offset
 * @bits: size of मुक्त area
 *
 * Helper function क्रम pcpu_क्रम_each_md_मुक्त_region.  It checks
 * block->contig_hपूर्णांक and perक्रमms aggregation across blocks to find the
 * next hपूर्णांक.  It modअगरies bit_off and bits in-place to be consumed in the
 * loop.
 */
अटल व्योम pcpu_next_md_मुक्त_region(काष्ठा pcpu_chunk *chunk, पूर्णांक *bit_off,
				     पूर्णांक *bits)
अणु
	पूर्णांक i = pcpu_off_to_block_index(*bit_off);
	पूर्णांक block_off = pcpu_off_to_block_off(*bit_off);
	काष्ठा pcpu_block_md *block;

	*bits = 0;
	क्रम (block = chunk->md_blocks + i; i < pcpu_chunk_nr_blocks(chunk);
	     block++, i++) अणु
		/* handles contig area across blocks */
		अगर (*bits) अणु
			*bits += block->left_मुक्त;
			अगर (block->left_मुक्त == PCPU_BITMAP_BLOCK_BITS)
				जारी;
			वापस;
		पूर्ण

		/*
		 * This checks three things.  First is there a contig_hपूर्णांक to
		 * check.  Second, have we checked this hपूर्णांक beक्रमe by
		 * comparing the block_off.  Third, is this the same as the
		 * right contig hपूर्णांक.  In the last हाल, it spills over पूर्णांकo
		 * the next block and should be handled by the contig area
		 * across blocks code.
		 */
		*bits = block->contig_hपूर्णांक;
		अगर (*bits && block->contig_hपूर्णांक_start >= block_off &&
		    *bits + block->contig_hपूर्णांक_start < PCPU_BITMAP_BLOCK_BITS) अणु
			*bit_off = pcpu_block_off_to_off(i,
					block->contig_hपूर्णांक_start);
			वापस;
		पूर्ण
		/* reset to satisfy the second predicate above */
		block_off = 0;

		*bits = block->right_मुक्त;
		*bit_off = (i + 1) * PCPU_BITMAP_BLOCK_BITS - block->right_मुक्त;
	पूर्ण
पूर्ण

/**
 * pcpu_next_fit_region - finds fit areas क्रम a given allocation request
 * @chunk: chunk of पूर्णांकerest
 * @alloc_bits: size of allocation
 * @align: alignment of area (max PAGE_SIZE)
 * @bit_off: chunk offset
 * @bits: size of मुक्त area
 *
 * Finds the next मुक्त region that is viable क्रम use with a given size and
 * alignment.  This only वापसs अगर there is a valid area to be used क्रम this
 * allocation.  block->first_मुक्त is वापसed अगर the allocation request fits
 * within the block to see अगर the request can be fulfilled prior to the contig
 * hपूर्णांक.
 */
अटल व्योम pcpu_next_fit_region(काष्ठा pcpu_chunk *chunk, पूर्णांक alloc_bits,
				 पूर्णांक align, पूर्णांक *bit_off, पूर्णांक *bits)
अणु
	पूर्णांक i = pcpu_off_to_block_index(*bit_off);
	पूर्णांक block_off = pcpu_off_to_block_off(*bit_off);
	काष्ठा pcpu_block_md *block;

	*bits = 0;
	क्रम (block = chunk->md_blocks + i; i < pcpu_chunk_nr_blocks(chunk);
	     block++, i++) अणु
		/* handles contig area across blocks */
		अगर (*bits) अणु
			*bits += block->left_मुक्त;
			अगर (*bits >= alloc_bits)
				वापस;
			अगर (block->left_मुक्त == PCPU_BITMAP_BLOCK_BITS)
				जारी;
		पूर्ण

		/* check block->contig_hपूर्णांक */
		*bits = ALIGN(block->contig_hपूर्णांक_start, align) -
			block->contig_hपूर्णांक_start;
		/*
		 * This uses the block offset to determine अगर this has been
		 * checked in the prior iteration.
		 */
		अगर (block->contig_hपूर्णांक &&
		    block->contig_hपूर्णांक_start >= block_off &&
		    block->contig_hपूर्णांक >= *bits + alloc_bits) अणु
			पूर्णांक start = pcpu_next_hपूर्णांक(block, alloc_bits);

			*bits += alloc_bits + block->contig_hपूर्णांक_start -
				 start;
			*bit_off = pcpu_block_off_to_off(i, start);
			वापस;
		पूर्ण
		/* reset to satisfy the second predicate above */
		block_off = 0;

		*bit_off = ALIGN(PCPU_BITMAP_BLOCK_BITS - block->right_मुक्त,
				 align);
		*bits = PCPU_BITMAP_BLOCK_BITS - *bit_off;
		*bit_off = pcpu_block_off_to_off(i, *bit_off);
		अगर (*bits >= alloc_bits)
			वापस;
	पूर्ण

	/* no valid offsets were found - fail condition */
	*bit_off = pcpu_chunk_map_bits(chunk);
पूर्ण

/*
 * Metadata मुक्त area iterators.  These perक्रमm aggregation of मुक्त areas
 * based on the metadata blocks and वापस the offset @bit_off and size in
 * bits of the मुक्त area @bits.  pcpu_क्रम_each_fit_region only वापसs when
 * a fit is found क्रम the allocation request.
 */
#घोषणा pcpu_क्रम_each_md_मुक्त_region(chunk, bit_off, bits)		\
	क्रम (pcpu_next_md_मुक्त_region((chunk), &(bit_off), &(bits));	\
	     (bit_off) < pcpu_chunk_map_bits((chunk));			\
	     (bit_off) += (bits) + 1,					\
	     pcpu_next_md_मुक्त_region((chunk), &(bit_off), &(bits)))

#घोषणा pcpu_क्रम_each_fit_region(chunk, alloc_bits, align, bit_off, bits)     \
	क्रम (pcpu_next_fit_region((chunk), (alloc_bits), (align), &(bit_off), \
				  &(bits));				      \
	     (bit_off) < pcpu_chunk_map_bits((chunk));			      \
	     (bit_off) += (bits),					      \
	     pcpu_next_fit_region((chunk), (alloc_bits), (align), &(bit_off), \
				  &(bits)))

/**
 * pcpu_mem_zalloc - allocate memory
 * @size: bytes to allocate
 * @gfp: allocation flags
 *
 * Allocate @size bytes.  If @size is smaller than PAGE_SIZE,
 * kzalloc() is used; otherwise, the equivalent of vzalloc() is used.
 * This is to facilitate passing through whitelisted flags.  The
 * वापसed memory is always zeroed.
 *
 * RETURNS:
 * Poपूर्णांकer to the allocated area on success, शून्य on failure.
 */
अटल व्योम *pcpu_mem_zalloc(माप_प्रकार size, gfp_t gfp)
अणु
	अगर (WARN_ON_ONCE(!slab_is_available()))
		वापस शून्य;

	अगर (size <= PAGE_SIZE)
		वापस kzalloc(size, gfp);
	अन्यथा
		वापस __vदो_स्मृति(size, gfp | __GFP_ZERO);
पूर्ण

/**
 * pcpu_mem_मुक्त - मुक्त memory
 * @ptr: memory to मुक्त
 *
 * Free @ptr.  @ptr should have been allocated using pcpu_mem_zalloc().
 */
अटल व्योम pcpu_mem_मुक्त(व्योम *ptr)
अणु
	kvमुक्त(ptr);
पूर्ण

अटल व्योम __pcpu_chunk_move(काष्ठा pcpu_chunk *chunk, पूर्णांक slot,
			      bool move_front)
अणु
	अगर (chunk != pcpu_reserved_chunk) अणु
		काष्ठा list_head *pcpu_slot;

		pcpu_slot = pcpu_chunk_list(pcpu_chunk_type(chunk));
		अगर (move_front)
			list_move(&chunk->list, &pcpu_slot[slot]);
		अन्यथा
			list_move_tail(&chunk->list, &pcpu_slot[slot]);
	पूर्ण
पूर्ण

अटल व्योम pcpu_chunk_move(काष्ठा pcpu_chunk *chunk, पूर्णांक slot)
अणु
	__pcpu_chunk_move(chunk, slot, true);
पूर्ण

/**
 * pcpu_chunk_relocate - put chunk in the appropriate chunk slot
 * @chunk: chunk of पूर्णांकerest
 * @oslot: the previous slot it was on
 *
 * This function is called after an allocation or मुक्त changed @chunk.
 * New slot according to the changed state is determined and @chunk is
 * moved to the slot.  Note that the reserved chunk is never put on
 * chunk slots.
 *
 * CONTEXT:
 * pcpu_lock.
 */
अटल व्योम pcpu_chunk_relocate(काष्ठा pcpu_chunk *chunk, पूर्णांक oslot)
अणु
	पूर्णांक nslot = pcpu_chunk_slot(chunk);

	अगर (oslot != nslot)
		__pcpu_chunk_move(chunk, nslot, oslot < nslot);
पूर्ण

/*
 * pcpu_update_empty_pages - update empty page counters
 * @chunk: chunk of पूर्णांकerest
 * @nr: nr of empty pages
 *
 * This is used to keep track of the empty pages now based on the premise
 * a md_block covers a page.  The hपूर्णांक update functions recognize अगर a block
 * is made full or broken to calculate deltas क्रम keeping track of मुक्त pages.
 */
अटल अंतरभूत व्योम pcpu_update_empty_pages(काष्ठा pcpu_chunk *chunk, पूर्णांक nr)
अणु
	chunk->nr_empty_pop_pages += nr;
	अगर (chunk != pcpu_reserved_chunk)
		pcpu_nr_empty_pop_pages[pcpu_chunk_type(chunk)] += nr;
पूर्ण

/*
 * pcpu_region_overlap - determines अगर two regions overlap
 * @a: start of first region, inclusive
 * @b: end of first region, exclusive
 * @x: start of second region, inclusive
 * @y: end of second region, exclusive
 *
 * This is used to determine अगर the hपूर्णांक region [a, b) overlaps with the
 * allocated region [x, y).
 */
अटल अंतरभूत bool pcpu_region_overlap(पूर्णांक a, पूर्णांक b, पूर्णांक x, पूर्णांक y)
अणु
	वापस (a < y) && (x < b);
पूर्ण

/**
 * pcpu_block_update - updates a block given a मुक्त area
 * @block: block of पूर्णांकerest
 * @start: start offset in block
 * @end: end offset in block
 *
 * Updates a block given a known मुक्त area.  The region [start, end) is
 * expected to be the entirety of the मुक्त area within a block.  Chooses
 * the best starting offset अगर the contig hपूर्णांकs are equal.
 */
अटल व्योम pcpu_block_update(काष्ठा pcpu_block_md *block, पूर्णांक start, पूर्णांक end)
अणु
	पूर्णांक contig = end - start;

	block->first_मुक्त = min(block->first_मुक्त, start);
	अगर (start == 0)
		block->left_मुक्त = contig;

	अगर (end == block->nr_bits)
		block->right_मुक्त = contig;

	अगर (contig > block->contig_hपूर्णांक) अणु
		/* promote the old contig_hपूर्णांक to be the new scan_hपूर्णांक */
		अगर (start > block->contig_hपूर्णांक_start) अणु
			अगर (block->contig_hपूर्णांक > block->scan_hपूर्णांक) अणु
				block->scan_hपूर्णांक_start =
					block->contig_hपूर्णांक_start;
				block->scan_hपूर्णांक = block->contig_hपूर्णांक;
			पूर्ण अन्यथा अगर (start < block->scan_hपूर्णांक_start) अणु
				/*
				 * The old contig_hपूर्णांक == scan_hपूर्णांक.  But, the
				 * new contig is larger so hold the invariant
				 * scan_hपूर्णांक_start < contig_hपूर्णांक_start.
				 */
				block->scan_hपूर्णांक = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			block->scan_hपूर्णांक = 0;
		पूर्ण
		block->contig_hपूर्णांक_start = start;
		block->contig_hपूर्णांक = contig;
	पूर्ण अन्यथा अगर (contig == block->contig_hपूर्णांक) अणु
		अगर (block->contig_hपूर्णांक_start &&
		    (!start ||
		     __ffs(start) > __ffs(block->contig_hपूर्णांक_start))) अणु
			/* start has a better alignment so use it */
			block->contig_hपूर्णांक_start = start;
			अगर (start < block->scan_hपूर्णांक_start &&
			    block->contig_hपूर्णांक > block->scan_hपूर्णांक)
				block->scan_hपूर्णांक = 0;
		पूर्ण अन्यथा अगर (start > block->scan_hपूर्णांक_start ||
			   block->contig_hपूर्णांक > block->scan_hपूर्णांक) अणु
			/*
			 * Knowing contig == contig_hपूर्णांक, update the scan_hपूर्णांक
			 * अगर it is farther than or larger than the current
			 * scan_hपूर्णांक.
			 */
			block->scan_hपूर्णांक_start = start;
			block->scan_hपूर्णांक = contig;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The region is smaller than the contig_hपूर्णांक.  So only update
		 * the scan_hपूर्णांक अगर it is larger than or equal and farther than
		 * the current scan_hपूर्णांक.
		 */
		अगर ((start < block->contig_hपूर्णांक_start &&
		     (contig > block->scan_hपूर्णांक ||
		      (contig == block->scan_hपूर्णांक &&
		       start > block->scan_hपूर्णांक_start)))) अणु
			block->scan_hपूर्णांक_start = start;
			block->scan_hपूर्णांक = contig;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * pcpu_block_update_scan - update a block given a मुक्त area from a scan
 * @chunk: chunk of पूर्णांकerest
 * @bit_off: chunk offset
 * @bits: size of मुक्त area
 *
 * Finding the final allocation spot first goes through pcpu_find_block_fit()
 * to find a block that can hold the allocation and then pcpu_alloc_area()
 * where a scan is used.  When allocations require specअगरic alignments,
 * we can inadvertently create holes which will not be seen in the alloc
 * or मुक्त paths.
 *
 * This takes a given मुक्त area hole and updates a block as it may change the
 * scan_hपूर्णांक.  We need to scan backwards to ensure we करोn't miss मुक्त bits
 * from alignment.
 */
अटल व्योम pcpu_block_update_scan(काष्ठा pcpu_chunk *chunk, पूर्णांक bit_off,
				   पूर्णांक bits)
अणु
	पूर्णांक s_off = pcpu_off_to_block_off(bit_off);
	पूर्णांक e_off = s_off + bits;
	पूर्णांक s_index, l_bit;
	काष्ठा pcpu_block_md *block;

	अगर (e_off > PCPU_BITMAP_BLOCK_BITS)
		वापस;

	s_index = pcpu_off_to_block_index(bit_off);
	block = chunk->md_blocks + s_index;

	/* scan backwards in हाल of alignment skipping मुक्त bits */
	l_bit = find_last_bit(pcpu_index_alloc_map(chunk, s_index), s_off);
	s_off = (s_off == l_bit) ? 0 : l_bit + 1;

	pcpu_block_update(block, s_off, e_off);
पूर्ण

/**
 * pcpu_chunk_refresh_hपूर्णांक - updates metadata about a chunk
 * @chunk: chunk of पूर्णांकerest
 * @full_scan: अगर we should scan from the beginning
 *
 * Iterates over the metadata blocks to find the largest contig area.
 * A full scan can be aव्योमed on the allocation path as this is triggered
 * अगर we broke the contig_hपूर्णांक.  In करोing so, the scan_hपूर्णांक will be beक्रमe
 * the contig_hपूर्णांक or after अगर the scan_hपूर्णांक == contig_hपूर्णांक.  This cannot
 * be prevented on मुक्तing as we want to find the largest area possibly
 * spanning blocks.
 */
अटल व्योम pcpu_chunk_refresh_hपूर्णांक(काष्ठा pcpu_chunk *chunk, bool full_scan)
अणु
	काष्ठा pcpu_block_md *chunk_md = &chunk->chunk_md;
	पूर्णांक bit_off, bits;

	/* promote scan_hपूर्णांक to contig_hपूर्णांक */
	अगर (!full_scan && chunk_md->scan_hपूर्णांक) अणु
		bit_off = chunk_md->scan_hपूर्णांक_start + chunk_md->scan_hपूर्णांक;
		chunk_md->contig_hपूर्णांक_start = chunk_md->scan_hपूर्णांक_start;
		chunk_md->contig_hपूर्णांक = chunk_md->scan_hपूर्णांक;
		chunk_md->scan_hपूर्णांक = 0;
	पूर्ण अन्यथा अणु
		bit_off = chunk_md->first_मुक्त;
		chunk_md->contig_hपूर्णांक = 0;
	पूर्ण

	bits = 0;
	pcpu_क्रम_each_md_मुक्त_region(chunk, bit_off, bits)
		pcpu_block_update(chunk_md, bit_off, bit_off + bits);
पूर्ण

/**
 * pcpu_block_refresh_hपूर्णांक
 * @chunk: chunk of पूर्णांकerest
 * @index: index of the metadata block
 *
 * Scans over the block beginning at first_मुक्त and updates the block
 * metadata accordingly.
 */
अटल व्योम pcpu_block_refresh_hपूर्णांक(काष्ठा pcpu_chunk *chunk, पूर्णांक index)
अणु
	काष्ठा pcpu_block_md *block = chunk->md_blocks + index;
	अचिन्हित दीर्घ *alloc_map = pcpu_index_alloc_map(chunk, index);
	अचिन्हित पूर्णांक rs, re, start;	/* region start, region end */

	/* promote scan_hपूर्णांक to contig_hपूर्णांक */
	अगर (block->scan_hपूर्णांक) अणु
		start = block->scan_hपूर्णांक_start + block->scan_hपूर्णांक;
		block->contig_hपूर्णांक_start = block->scan_hपूर्णांक_start;
		block->contig_hपूर्णांक = block->scan_hपूर्णांक;
		block->scan_hपूर्णांक = 0;
	पूर्ण अन्यथा अणु
		start = block->first_मुक्त;
		block->contig_hपूर्णांक = 0;
	पूर्ण

	block->right_मुक्त = 0;

	/* iterate over मुक्त areas and update the contig hपूर्णांकs */
	biपंचांगap_क्रम_each_clear_region(alloc_map, rs, re, start,
				     PCPU_BITMAP_BLOCK_BITS)
		pcpu_block_update(block, rs, re);
पूर्ण

/**
 * pcpu_block_update_hपूर्णांक_alloc - update hपूर्णांक on allocation path
 * @chunk: chunk of पूर्णांकerest
 * @bit_off: chunk offset
 * @bits: size of request
 *
 * Updates metadata क्रम the allocation path.  The metadata only has to be
 * refreshed by a full scan अगरf the chunk's contig hपूर्णांक is broken.  Block level
 * scans are required अगर the block's contig hपूर्णांक is broken.
 */
अटल व्योम pcpu_block_update_hपूर्णांक_alloc(काष्ठा pcpu_chunk *chunk, पूर्णांक bit_off,
					 पूर्णांक bits)
अणु
	काष्ठा pcpu_block_md *chunk_md = &chunk->chunk_md;
	पूर्णांक nr_empty_pages = 0;
	काष्ठा pcpu_block_md *s_block, *e_block, *block;
	पूर्णांक s_index, e_index;	/* block indexes of the मुक्तd allocation */
	पूर्णांक s_off, e_off;	/* block offsets of the मुक्तd allocation */

	/*
	 * Calculate per block offsets.
	 * The calculation uses an inclusive range, but the resulting offsets
	 * are [start, end).  e_index always poपूर्णांकs to the last block in the
	 * range.
	 */
	s_index = pcpu_off_to_block_index(bit_off);
	e_index = pcpu_off_to_block_index(bit_off + bits - 1);
	s_off = pcpu_off_to_block_off(bit_off);
	e_off = pcpu_off_to_block_off(bit_off + bits - 1) + 1;

	s_block = chunk->md_blocks + s_index;
	e_block = chunk->md_blocks + e_index;

	/*
	 * Update s_block.
	 * block->first_मुक्त must be updated अगर the allocation takes its place.
	 * If the allocation अवरोधs the contig_hपूर्णांक, a scan is required to
	 * restore this hपूर्णांक.
	 */
	अगर (s_block->contig_hपूर्णांक == PCPU_BITMAP_BLOCK_BITS)
		nr_empty_pages++;

	अगर (s_off == s_block->first_मुक्त)
		s_block->first_मुक्त = find_next_zero_bit(
					pcpu_index_alloc_map(chunk, s_index),
					PCPU_BITMAP_BLOCK_BITS,
					s_off + bits);

	अगर (pcpu_region_overlap(s_block->scan_hपूर्णांक_start,
				s_block->scan_hपूर्णांक_start + s_block->scan_hपूर्णांक,
				s_off,
				s_off + bits))
		s_block->scan_hपूर्णांक = 0;

	अगर (pcpu_region_overlap(s_block->contig_hपूर्णांक_start,
				s_block->contig_hपूर्णांक_start +
				s_block->contig_hपूर्णांक,
				s_off,
				s_off + bits)) अणु
		/* block contig hपूर्णांक is broken - scan to fix it */
		अगर (!s_off)
			s_block->left_मुक्त = 0;
		pcpu_block_refresh_hपूर्णांक(chunk, s_index);
	पूर्ण अन्यथा अणु
		/* update left and right contig manually */
		s_block->left_मुक्त = min(s_block->left_मुक्त, s_off);
		अगर (s_index == e_index)
			s_block->right_मुक्त = min_t(पूर्णांक, s_block->right_मुक्त,
					PCPU_BITMAP_BLOCK_BITS - e_off);
		अन्यथा
			s_block->right_मुक्त = 0;
	पूर्ण

	/*
	 * Update e_block.
	 */
	अगर (s_index != e_index) अणु
		अगर (e_block->contig_hपूर्णांक == PCPU_BITMAP_BLOCK_BITS)
			nr_empty_pages++;

		/*
		 * When the allocation is across blocks, the end is aदीर्घ
		 * the left part of the e_block.
		 */
		e_block->first_मुक्त = find_next_zero_bit(
				pcpu_index_alloc_map(chunk, e_index),
				PCPU_BITMAP_BLOCK_BITS, e_off);

		अगर (e_off == PCPU_BITMAP_BLOCK_BITS) अणु
			/* reset the block */
			e_block++;
		पूर्ण अन्यथा अणु
			अगर (e_off > e_block->scan_hपूर्णांक_start)
				e_block->scan_hपूर्णांक = 0;

			e_block->left_मुक्त = 0;
			अगर (e_off > e_block->contig_hपूर्णांक_start) अणु
				/* contig hपूर्णांक is broken - scan to fix it */
				pcpu_block_refresh_hपूर्णांक(chunk, e_index);
			पूर्ण अन्यथा अणु
				e_block->right_मुक्त =
					min_t(पूर्णांक, e_block->right_मुक्त,
					      PCPU_BITMAP_BLOCK_BITS - e_off);
			पूर्ण
		पूर्ण

		/* update in-between md_blocks */
		nr_empty_pages += (e_index - s_index - 1);
		क्रम (block = s_block + 1; block < e_block; block++) अणु
			block->scan_hपूर्णांक = 0;
			block->contig_hपूर्णांक = 0;
			block->left_मुक्त = 0;
			block->right_मुक्त = 0;
		पूर्ण
	पूर्ण

	अगर (nr_empty_pages)
		pcpu_update_empty_pages(chunk, -nr_empty_pages);

	अगर (pcpu_region_overlap(chunk_md->scan_hपूर्णांक_start,
				chunk_md->scan_hपूर्णांक_start +
				chunk_md->scan_hपूर्णांक,
				bit_off,
				bit_off + bits))
		chunk_md->scan_hपूर्णांक = 0;

	/*
	 * The only समय a full chunk scan is required is अगर the chunk
	 * contig hपूर्णांक is broken.  Otherwise, it means a smaller space
	 * was used and thereक्रमe the chunk contig hपूर्णांक is still correct.
	 */
	अगर (pcpu_region_overlap(chunk_md->contig_hपूर्णांक_start,
				chunk_md->contig_hपूर्णांक_start +
				chunk_md->contig_hपूर्णांक,
				bit_off,
				bit_off + bits))
		pcpu_chunk_refresh_hपूर्णांक(chunk, false);
पूर्ण

/**
 * pcpu_block_update_hपूर्णांक_मुक्त - updates the block hपूर्णांकs on the मुक्त path
 * @chunk: chunk of पूर्णांकerest
 * @bit_off: chunk offset
 * @bits: size of request
 *
 * Updates metadata क्रम the allocation path.  This aव्योमs a blind block
 * refresh by making use of the block contig hपूर्णांकs.  If this fails, it scans
 * क्रमward and backward to determine the extent of the मुक्त area.  This is
 * capped at the boundary of blocks.
 *
 * A chunk update is triggered अगर a page becomes मुक्त, a block becomes मुक्त,
 * or the मुक्त spans across blocks.  This tradeoff is to minimize iterating
 * over the block metadata to update chunk_md->contig_hपूर्णांक.
 * chunk_md->contig_hपूर्णांक may be off by up to a page, but it will never be more
 * than the available space.  If the contig hपूर्णांक is contained in one block, it
 * will be accurate.
 */
अटल व्योम pcpu_block_update_hपूर्णांक_मुक्त(काष्ठा pcpu_chunk *chunk, पूर्णांक bit_off,
					पूर्णांक bits)
अणु
	पूर्णांक nr_empty_pages = 0;
	काष्ठा pcpu_block_md *s_block, *e_block, *block;
	पूर्णांक s_index, e_index;	/* block indexes of the मुक्तd allocation */
	पूर्णांक s_off, e_off;	/* block offsets of the मुक्तd allocation */
	पूर्णांक start, end;		/* start and end of the whole मुक्त area */

	/*
	 * Calculate per block offsets.
	 * The calculation uses an inclusive range, but the resulting offsets
	 * are [start, end).  e_index always poपूर्णांकs to the last block in the
	 * range.
	 */
	s_index = pcpu_off_to_block_index(bit_off);
	e_index = pcpu_off_to_block_index(bit_off + bits - 1);
	s_off = pcpu_off_to_block_off(bit_off);
	e_off = pcpu_off_to_block_off(bit_off + bits - 1) + 1;

	s_block = chunk->md_blocks + s_index;
	e_block = chunk->md_blocks + e_index;

	/*
	 * Check अगर the मुक्तd area aligns with the block->contig_hपूर्णांक.
	 * If it करोes, then the scan to find the beginning/end of the
	 * larger मुक्त area can be aव्योमed.
	 *
	 * start and end refer to beginning and end of the मुक्त area
	 * within each their respective blocks.  This is not necessarily
	 * the entire मुक्त area as it may span blocks past the beginning
	 * or end of the block.
	 */
	start = s_off;
	अगर (s_off == s_block->contig_hपूर्णांक + s_block->contig_hपूर्णांक_start) अणु
		start = s_block->contig_hपूर्णांक_start;
	पूर्ण अन्यथा अणु
		/*
		 * Scan backwards to find the extent of the मुक्त area.
		 * find_last_bit वापसs the starting bit, so अगर the start bit
		 * is वापसed, that means there was no last bit and the
		 * reमुख्यder of the chunk is मुक्त.
		 */
		पूर्णांक l_bit = find_last_bit(pcpu_index_alloc_map(chunk, s_index),
					  start);
		start = (start == l_bit) ? 0 : l_bit + 1;
	पूर्ण

	end = e_off;
	अगर (e_off == e_block->contig_hपूर्णांक_start)
		end = e_block->contig_hपूर्णांक_start + e_block->contig_hपूर्णांक;
	अन्यथा
		end = find_next_bit(pcpu_index_alloc_map(chunk, e_index),
				    PCPU_BITMAP_BLOCK_BITS, end);

	/* update s_block */
	e_off = (s_index == e_index) ? end : PCPU_BITMAP_BLOCK_BITS;
	अगर (!start && e_off == PCPU_BITMAP_BLOCK_BITS)
		nr_empty_pages++;
	pcpu_block_update(s_block, start, e_off);

	/* मुक्तing in the same block */
	अगर (s_index != e_index) अणु
		/* update e_block */
		अगर (end == PCPU_BITMAP_BLOCK_BITS)
			nr_empty_pages++;
		pcpu_block_update(e_block, 0, end);

		/* reset md_blocks in the middle */
		nr_empty_pages += (e_index - s_index - 1);
		क्रम (block = s_block + 1; block < e_block; block++) अणु
			block->first_मुक्त = 0;
			block->scan_hपूर्णांक = 0;
			block->contig_hपूर्णांक_start = 0;
			block->contig_hपूर्णांक = PCPU_BITMAP_BLOCK_BITS;
			block->left_मुक्त = PCPU_BITMAP_BLOCK_BITS;
			block->right_मुक्त = PCPU_BITMAP_BLOCK_BITS;
		पूर्ण
	पूर्ण

	अगर (nr_empty_pages)
		pcpu_update_empty_pages(chunk, nr_empty_pages);

	/*
	 * Refresh chunk metadata when the मुक्त makes a block मुक्त or spans
	 * across blocks.  The contig_hपूर्णांक may be off by up to a page, but अगर
	 * the contig_hपूर्णांक is contained in a block, it will be accurate with
	 * the अन्यथा condition below.
	 */
	अगर (((end - start) >= PCPU_BITMAP_BLOCK_BITS) || s_index != e_index)
		pcpu_chunk_refresh_hपूर्णांक(chunk, true);
	अन्यथा
		pcpu_block_update(&chunk->chunk_md,
				  pcpu_block_off_to_off(s_index, start),
				  end);
पूर्ण

/**
 * pcpu_is_populated - determines अगर the region is populated
 * @chunk: chunk of पूर्णांकerest
 * @bit_off: chunk offset
 * @bits: size of area
 * @next_off: वापस value क्रम the next offset to start searching
 *
 * For atomic allocations, check अगर the backing pages are populated.
 *
 * RETURNS:
 * Bool अगर the backing pages are populated.
 * next_index is to skip over unpopulated blocks in pcpu_find_block_fit.
 */
अटल bool pcpu_is_populated(काष्ठा pcpu_chunk *chunk, पूर्णांक bit_off, पूर्णांक bits,
			      पूर्णांक *next_off)
अणु
	अचिन्हित पूर्णांक page_start, page_end, rs, re;

	page_start = PFN_DOWN(bit_off * PCPU_MIN_ALLOC_SIZE);
	page_end = PFN_UP((bit_off + bits) * PCPU_MIN_ALLOC_SIZE);

	rs = page_start;
	biपंचांगap_next_clear_region(chunk->populated, &rs, &re, page_end);
	अगर (rs >= page_end)
		वापस true;

	*next_off = re * PAGE_SIZE / PCPU_MIN_ALLOC_SIZE;
	वापस false;
पूर्ण

/**
 * pcpu_find_block_fit - finds the block index to start searching
 * @chunk: chunk of पूर्णांकerest
 * @alloc_bits: size of request in allocation units
 * @align: alignment of area (max PAGE_SIZE bytes)
 * @pop_only: use populated regions only
 *
 * Given a chunk and an allocation spec, find the offset to begin searching
 * क्रम a मुक्त region.  This iterates over the biपंचांगap metadata blocks to
 * find an offset that will be guaranteed to fit the requirements.  It is
 * not quite first fit as अगर the allocation करोes not fit in the contig hपूर्णांक
 * of a block or chunk, it is skipped.  This errs on the side of caution
 * to prevent excess iteration.  Poor alignment can cause the allocator to
 * skip over blocks and chunks that have valid मुक्त areas.
 *
 * RETURNS:
 * The offset in the biपंचांगap to begin searching.
 * -1 अगर no offset is found.
 */
अटल पूर्णांक pcpu_find_block_fit(काष्ठा pcpu_chunk *chunk, पूर्णांक alloc_bits,
			       माप_प्रकार align, bool pop_only)
अणु
	काष्ठा pcpu_block_md *chunk_md = &chunk->chunk_md;
	पूर्णांक bit_off, bits, next_off;

	/*
	 * Check to see अगर the allocation can fit in the chunk's contig hपूर्णांक.
	 * This is an optimization to prevent scanning by assuming अगर it
	 * cannot fit in the global hपूर्णांक, there is memory pressure and creating
	 * a new chunk would happen soon.
	 */
	bit_off = ALIGN(chunk_md->contig_hपूर्णांक_start, align) -
		  chunk_md->contig_hपूर्णांक_start;
	अगर (bit_off + alloc_bits > chunk_md->contig_hपूर्णांक)
		वापस -1;

	bit_off = pcpu_next_hपूर्णांक(chunk_md, alloc_bits);
	bits = 0;
	pcpu_क्रम_each_fit_region(chunk, alloc_bits, align, bit_off, bits) अणु
		अगर (!pop_only || pcpu_is_populated(chunk, bit_off, bits,
						   &next_off))
			अवरोध;

		bit_off = next_off;
		bits = 0;
	पूर्ण

	अगर (bit_off == pcpu_chunk_map_bits(chunk))
		वापस -1;

	वापस bit_off;
पूर्ण

/*
 * pcpu_find_zero_area - modअगरied from biपंचांगap_find_next_zero_area_off()
 * @map: the address to base the search on
 * @size: the biपंचांगap size in bits
 * @start: the bitnumber to start searching at
 * @nr: the number of zeroed bits we're looking क्रम
 * @align_mask: alignment mask क्रम zero area
 * @largest_off: offset of the largest area skipped
 * @largest_bits: size of the largest area skipped
 *
 * The @align_mask should be one less than a घातer of 2.
 *
 * This is a modअगरied version of biपंचांगap_find_next_zero_area_off() to remember
 * the largest area that was skipped.  This is imperfect, but in general is
 * good enough.  The largest remembered region is the largest failed region
 * seen.  This करोes not include anything we possibly skipped due to alignment.
 * pcpu_block_update_scan() करोes scan backwards to try and recover what was
 * lost to alignment.  While this can cause scanning to miss earlier possible
 * मुक्त areas, smaller allocations will eventually fill those holes.
 */
अटल अचिन्हित दीर्घ pcpu_find_zero_area(अचिन्हित दीर्घ *map,
					 अचिन्हित दीर्घ size,
					 अचिन्हित दीर्घ start,
					 अचिन्हित दीर्घ nr,
					 अचिन्हित दीर्घ align_mask,
					 अचिन्हित दीर्घ *largest_off,
					 अचिन्हित दीर्घ *largest_bits)
अणु
	अचिन्हित दीर्घ index, end, i, area_off, area_bits;
again:
	index = find_next_zero_bit(map, size, start);

	/* Align allocation */
	index = __ALIGN_MASK(index, align_mask);
	area_off = index;

	end = index + nr;
	अगर (end > size)
		वापस end;
	i = find_next_bit(map, end, index);
	अगर (i < end) अणु
		area_bits = i - area_off;
		/* remember largest unused area with best alignment */
		अगर (area_bits > *largest_bits ||
		    (area_bits == *largest_bits && *largest_off &&
		     (!area_off || __ffs(area_off) > __ffs(*largest_off)))) अणु
			*largest_off = area_off;
			*largest_bits = area_bits;
		पूर्ण

		start = i + 1;
		जाओ again;
	पूर्ण
	वापस index;
पूर्ण

/**
 * pcpu_alloc_area - allocates an area from a pcpu_chunk
 * @chunk: chunk of पूर्णांकerest
 * @alloc_bits: size of request in allocation units
 * @align: alignment of area (max PAGE_SIZE)
 * @start: bit_off to start searching
 *
 * This function takes in a @start offset to begin searching to fit an
 * allocation of @alloc_bits with alignment @align.  It needs to scan
 * the allocation map because अगर it fits within the block's contig hपूर्णांक,
 * @start will be block->first_मुक्त. This is an attempt to fill the
 * allocation prior to अवरोधing the contig hपूर्णांक.  The allocation and
 * boundary maps are updated accordingly अगर it confirms a valid
 * मुक्त area.
 *
 * RETURNS:
 * Allocated addr offset in @chunk on success.
 * -1 अगर no matching area is found.
 */
अटल पूर्णांक pcpu_alloc_area(काष्ठा pcpu_chunk *chunk, पूर्णांक alloc_bits,
			   माप_प्रकार align, पूर्णांक start)
अणु
	काष्ठा pcpu_block_md *chunk_md = &chunk->chunk_md;
	माप_प्रकार align_mask = (align) ? (align - 1) : 0;
	अचिन्हित दीर्घ area_off = 0, area_bits = 0;
	पूर्णांक bit_off, end, oslot;

	lockdep_निश्चित_held(&pcpu_lock);

	oslot = pcpu_chunk_slot(chunk);

	/*
	 * Search to find a fit.
	 */
	end = min_t(पूर्णांक, start + alloc_bits + PCPU_BITMAP_BLOCK_BITS,
		    pcpu_chunk_map_bits(chunk));
	bit_off = pcpu_find_zero_area(chunk->alloc_map, end, start, alloc_bits,
				      align_mask, &area_off, &area_bits);
	अगर (bit_off >= end)
		वापस -1;

	अगर (area_bits)
		pcpu_block_update_scan(chunk, area_off, area_bits);

	/* update alloc map */
	biपंचांगap_set(chunk->alloc_map, bit_off, alloc_bits);

	/* update boundary map */
	set_bit(bit_off, chunk->bound_map);
	biपंचांगap_clear(chunk->bound_map, bit_off + 1, alloc_bits - 1);
	set_bit(bit_off + alloc_bits, chunk->bound_map);

	chunk->मुक्त_bytes -= alloc_bits * PCPU_MIN_ALLOC_SIZE;

	/* update first मुक्त bit */
	अगर (bit_off == chunk_md->first_मुक्त)
		chunk_md->first_मुक्त = find_next_zero_bit(
					chunk->alloc_map,
					pcpu_chunk_map_bits(chunk),
					bit_off + alloc_bits);

	pcpu_block_update_hपूर्णांक_alloc(chunk, bit_off, alloc_bits);

	pcpu_chunk_relocate(chunk, oslot);

	वापस bit_off * PCPU_MIN_ALLOC_SIZE;
पूर्ण

/**
 * pcpu_मुक्त_area - मुक्तs the corresponding offset
 * @chunk: chunk of पूर्णांकerest
 * @off: addr offset पूर्णांकo chunk
 *
 * This function determines the size of an allocation to मुक्त using
 * the boundary biपंचांगap and clears the allocation map.
 *
 * RETURNS:
 * Number of मुक्तd bytes.
 */
अटल पूर्णांक pcpu_मुक्त_area(काष्ठा pcpu_chunk *chunk, पूर्णांक off)
अणु
	काष्ठा pcpu_block_md *chunk_md = &chunk->chunk_md;
	पूर्णांक bit_off, bits, end, oslot, मुक्तd;

	lockdep_निश्चित_held(&pcpu_lock);
	pcpu_stats_area_dealloc(chunk);

	oslot = pcpu_chunk_slot(chunk);

	bit_off = off / PCPU_MIN_ALLOC_SIZE;

	/* find end index */
	end = find_next_bit(chunk->bound_map, pcpu_chunk_map_bits(chunk),
			    bit_off + 1);
	bits = end - bit_off;
	biपंचांगap_clear(chunk->alloc_map, bit_off, bits);

	मुक्तd = bits * PCPU_MIN_ALLOC_SIZE;

	/* update metadata */
	chunk->मुक्त_bytes += मुक्तd;

	/* update first मुक्त bit */
	chunk_md->first_मुक्त = min(chunk_md->first_मुक्त, bit_off);

	pcpu_block_update_hपूर्णांक_मुक्त(chunk, bit_off, bits);

	pcpu_chunk_relocate(chunk, oslot);

	वापस मुक्तd;
पूर्ण

अटल व्योम pcpu_init_md_block(काष्ठा pcpu_block_md *block, पूर्णांक nr_bits)
अणु
	block->scan_hपूर्णांक = 0;
	block->contig_hपूर्णांक = nr_bits;
	block->left_मुक्त = nr_bits;
	block->right_मुक्त = nr_bits;
	block->first_मुक्त = 0;
	block->nr_bits = nr_bits;
पूर्ण

अटल व्योम pcpu_init_md_blocks(काष्ठा pcpu_chunk *chunk)
अणु
	काष्ठा pcpu_block_md *md_block;

	/* init the chunk's block */
	pcpu_init_md_block(&chunk->chunk_md, pcpu_chunk_map_bits(chunk));

	क्रम (md_block = chunk->md_blocks;
	     md_block != chunk->md_blocks + pcpu_chunk_nr_blocks(chunk);
	     md_block++)
		pcpu_init_md_block(md_block, PCPU_BITMAP_BLOCK_BITS);
पूर्ण

/**
 * pcpu_alloc_first_chunk - creates chunks that serve the first chunk
 * @पंचांगp_addr: the start of the region served
 * @map_size: size of the region served
 *
 * This is responsible क्रम creating the chunks that serve the first chunk.  The
 * base_addr is page aligned करोwn of @पंचांगp_addr जबतक the region end is page
 * aligned up.  Offsets are kept track of to determine the region served. All
 * this is करोne to appease the biपंचांगap allocator in aव्योमing partial blocks.
 *
 * RETURNS:
 * Chunk serving the region at @पंचांगp_addr of @map_size.
 */
अटल काष्ठा pcpu_chunk * __init pcpu_alloc_first_chunk(अचिन्हित दीर्घ पंचांगp_addr,
							 पूर्णांक map_size)
अणु
	काष्ठा pcpu_chunk *chunk;
	अचिन्हित दीर्घ aligned_addr, lcm_align;
	पूर्णांक start_offset, offset_bits, region_size, region_bits;
	माप_प्रकार alloc_size;

	/* region calculations */
	aligned_addr = पंचांगp_addr & PAGE_MASK;

	start_offset = पंचांगp_addr - aligned_addr;

	/*
	 * Align the end of the region with the LCM of PAGE_SIZE and
	 * PCPU_BITMAP_BLOCK_SIZE.  One of these स्थिरants is a multiple of
	 * the other.
	 */
	lcm_align = lcm(PAGE_SIZE, PCPU_BITMAP_BLOCK_SIZE);
	region_size = ALIGN(start_offset + map_size, lcm_align);

	/* allocate chunk */
	alloc_size = काष्ठा_size(chunk, populated,
				 BITS_TO_LONGS(region_size >> PAGE_SHIFT));
	chunk = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!chunk)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

	INIT_LIST_HEAD(&chunk->list);

	chunk->base_addr = (व्योम *)aligned_addr;
	chunk->start_offset = start_offset;
	chunk->end_offset = region_size - chunk->start_offset - map_size;

	chunk->nr_pages = region_size >> PAGE_SHIFT;
	region_bits = pcpu_chunk_map_bits(chunk);

	alloc_size = BITS_TO_LONGS(region_bits) * माप(chunk->alloc_map[0]);
	chunk->alloc_map = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!chunk->alloc_map)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

	alloc_size =
		BITS_TO_LONGS(region_bits + 1) * माप(chunk->bound_map[0]);
	chunk->bound_map = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!chunk->bound_map)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

	alloc_size = pcpu_chunk_nr_blocks(chunk) * माप(chunk->md_blocks[0]);
	chunk->md_blocks = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!chunk->md_blocks)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

#अगर_घोषित CONFIG_MEMCG_KMEM
	/* first chunk isn't memcg-aware */
	chunk->obj_cgroups = शून्य;
#पूर्ण_अगर
	pcpu_init_md_blocks(chunk);

	/* manage populated page biपंचांगap */
	chunk->immutable = true;
	biपंचांगap_fill(chunk->populated, chunk->nr_pages);
	chunk->nr_populated = chunk->nr_pages;
	chunk->nr_empty_pop_pages = chunk->nr_pages;

	chunk->मुक्त_bytes = map_size;

	अगर (chunk->start_offset) अणु
		/* hide the beginning of the biपंचांगap */
		offset_bits = chunk->start_offset / PCPU_MIN_ALLOC_SIZE;
		biपंचांगap_set(chunk->alloc_map, 0, offset_bits);
		set_bit(0, chunk->bound_map);
		set_bit(offset_bits, chunk->bound_map);

		chunk->chunk_md.first_मुक्त = offset_bits;

		pcpu_block_update_hपूर्णांक_alloc(chunk, 0, offset_bits);
	पूर्ण

	अगर (chunk->end_offset) अणु
		/* hide the end of the biपंचांगap */
		offset_bits = chunk->end_offset / PCPU_MIN_ALLOC_SIZE;
		biपंचांगap_set(chunk->alloc_map,
			   pcpu_chunk_map_bits(chunk) - offset_bits,
			   offset_bits);
		set_bit((start_offset + map_size) / PCPU_MIN_ALLOC_SIZE,
			chunk->bound_map);
		set_bit(region_bits, chunk->bound_map);

		pcpu_block_update_hपूर्णांक_alloc(chunk, pcpu_chunk_map_bits(chunk)
					     - offset_bits, offset_bits);
	पूर्ण

	वापस chunk;
पूर्ण

अटल काष्ठा pcpu_chunk *pcpu_alloc_chunk(क्रमागत pcpu_chunk_type type, gfp_t gfp)
अणु
	काष्ठा pcpu_chunk *chunk;
	पूर्णांक region_bits;

	chunk = pcpu_mem_zalloc(pcpu_chunk_काष्ठा_size, gfp);
	अगर (!chunk)
		वापस शून्य;

	INIT_LIST_HEAD(&chunk->list);
	chunk->nr_pages = pcpu_unit_pages;
	region_bits = pcpu_chunk_map_bits(chunk);

	chunk->alloc_map = pcpu_mem_zalloc(BITS_TO_LONGS(region_bits) *
					   माप(chunk->alloc_map[0]), gfp);
	अगर (!chunk->alloc_map)
		जाओ alloc_map_fail;

	chunk->bound_map = pcpu_mem_zalloc(BITS_TO_LONGS(region_bits + 1) *
					   माप(chunk->bound_map[0]), gfp);
	अगर (!chunk->bound_map)
		जाओ bound_map_fail;

	chunk->md_blocks = pcpu_mem_zalloc(pcpu_chunk_nr_blocks(chunk) *
					   माप(chunk->md_blocks[0]), gfp);
	अगर (!chunk->md_blocks)
		जाओ md_blocks_fail;

#अगर_घोषित CONFIG_MEMCG_KMEM
	अगर (pcpu_is_memcg_chunk(type)) अणु
		chunk->obj_cgroups =
			pcpu_mem_zalloc(pcpu_chunk_map_bits(chunk) *
					माप(काष्ठा obj_cgroup *), gfp);
		अगर (!chunk->obj_cgroups)
			जाओ objcg_fail;
	पूर्ण
#पूर्ण_अगर

	pcpu_init_md_blocks(chunk);

	/* init metadata */
	chunk->मुक्त_bytes = chunk->nr_pages * PAGE_SIZE;

	वापस chunk;

#अगर_घोषित CONFIG_MEMCG_KMEM
objcg_fail:
	pcpu_mem_मुक्त(chunk->md_blocks);
#पूर्ण_अगर
md_blocks_fail:
	pcpu_mem_मुक्त(chunk->bound_map);
bound_map_fail:
	pcpu_mem_मुक्त(chunk->alloc_map);
alloc_map_fail:
	pcpu_mem_मुक्त(chunk);

	वापस शून्य;
पूर्ण

अटल व्योम pcpu_मुक्त_chunk(काष्ठा pcpu_chunk *chunk)
अणु
	अगर (!chunk)
		वापस;
#अगर_घोषित CONFIG_MEMCG_KMEM
	pcpu_mem_मुक्त(chunk->obj_cgroups);
#पूर्ण_अगर
	pcpu_mem_मुक्त(chunk->md_blocks);
	pcpu_mem_मुक्त(chunk->bound_map);
	pcpu_mem_मुक्त(chunk->alloc_map);
	pcpu_mem_मुक्त(chunk);
पूर्ण

/**
 * pcpu_chunk_populated - post-population bookkeeping
 * @chunk: pcpu_chunk which got populated
 * @page_start: the start page
 * @page_end: the end page
 *
 * Pages in [@page_start,@page_end) have been populated to @chunk.  Update
 * the bookkeeping inक्रमmation accordingly.  Must be called after each
 * successful population.
 *
 * If this is @क्रम_alloc, करो not increment pcpu_nr_empty_pop_pages because it
 * is to serve an allocation in that area.
 */
अटल व्योम pcpu_chunk_populated(काष्ठा pcpu_chunk *chunk, पूर्णांक page_start,
				 पूर्णांक page_end)
अणु
	पूर्णांक nr = page_end - page_start;

	lockdep_निश्चित_held(&pcpu_lock);

	biपंचांगap_set(chunk->populated, page_start, nr);
	chunk->nr_populated += nr;
	pcpu_nr_populated += nr;

	pcpu_update_empty_pages(chunk, nr);
पूर्ण

/**
 * pcpu_chunk_depopulated - post-depopulation bookkeeping
 * @chunk: pcpu_chunk which got depopulated
 * @page_start: the start page
 * @page_end: the end page
 *
 * Pages in [@page_start,@page_end) have been depopulated from @chunk.
 * Update the bookkeeping inक्रमmation accordingly.  Must be called after
 * each successful depopulation.
 */
अटल व्योम pcpu_chunk_depopulated(काष्ठा pcpu_chunk *chunk,
				   पूर्णांक page_start, पूर्णांक page_end)
अणु
	पूर्णांक nr = page_end - page_start;

	lockdep_निश्चित_held(&pcpu_lock);

	biपंचांगap_clear(chunk->populated, page_start, nr);
	chunk->nr_populated -= nr;
	pcpu_nr_populated -= nr;

	pcpu_update_empty_pages(chunk, -nr);
पूर्ण

/*
 * Chunk management implementation.
 *
 * To allow dअगरferent implementations, chunk alloc/मुक्त and
 * [de]population are implemented in a separate file which is pulled
 * पूर्णांकo this file and compiled together.  The following functions
 * should be implemented.
 *
 * pcpu_populate_chunk		- populate the specअगरied range of a chunk
 * pcpu_depopulate_chunk	- depopulate the specअगरied range of a chunk
 * pcpu_create_chunk		- create a new chunk
 * pcpu_destroy_chunk		- destroy a chunk, always preceded by full depop
 * pcpu_addr_to_page		- translate address to physical address
 * pcpu_verअगरy_alloc_info	- check alloc_info is acceptable during init
 */
अटल पूर्णांक pcpu_populate_chunk(काष्ठा pcpu_chunk *chunk,
			       पूर्णांक page_start, पूर्णांक page_end, gfp_t gfp);
अटल व्योम pcpu_depopulate_chunk(काष्ठा pcpu_chunk *chunk,
				  पूर्णांक page_start, पूर्णांक page_end);
अटल काष्ठा pcpu_chunk *pcpu_create_chunk(क्रमागत pcpu_chunk_type type,
					    gfp_t gfp);
अटल व्योम pcpu_destroy_chunk(काष्ठा pcpu_chunk *chunk);
अटल काष्ठा page *pcpu_addr_to_page(व्योम *addr);
अटल पूर्णांक __init pcpu_verअगरy_alloc_info(स्थिर काष्ठा pcpu_alloc_info *ai);

#अगर_घोषित CONFIG_NEED_PER_CPU_KM
#समावेश "percpu-km.c"
#अन्यथा
#समावेश "percpu-vm.c"
#पूर्ण_अगर

/**
 * pcpu_chunk_addr_search - determine chunk containing specअगरied address
 * @addr: address क्रम which the chunk needs to be determined.
 *
 * This is an पूर्णांकernal function that handles all but अटल allocations.
 * Static percpu address values should never be passed पूर्णांकo the allocator.
 *
 * RETURNS:
 * The address of the found chunk.
 */
अटल काष्ठा pcpu_chunk *pcpu_chunk_addr_search(व्योम *addr)
अणु
	/* is it in the dynamic region (first chunk)? */
	अगर (pcpu_addr_in_chunk(pcpu_first_chunk, addr))
		वापस pcpu_first_chunk;

	/* is it in the reserved region? */
	अगर (pcpu_addr_in_chunk(pcpu_reserved_chunk, addr))
		वापस pcpu_reserved_chunk;

	/*
	 * The address is relative to unit0 which might be unused and
	 * thus unmapped.  Offset the address to the unit space of the
	 * current processor beक्रमe looking it up in the vदो_स्मृति
	 * space.  Note that any possible cpu id can be used here, so
	 * there's no need to worry about preemption or cpu hotplug.
	 */
	addr += pcpu_unit_offsets[raw_smp_processor_id()];
	वापस pcpu_get_page_chunk(pcpu_addr_to_page(addr));
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
अटल क्रमागत pcpu_chunk_type pcpu_memcg_pre_alloc_hook(माप_प्रकार size, gfp_t gfp,
						     काष्ठा obj_cgroup **objcgp)
अणु
	काष्ठा obj_cgroup *objcg;

	अगर (!memcg_kmem_enabled() || !(gfp & __GFP_ACCOUNT))
		वापस PCPU_CHUNK_ROOT;

	objcg = get_obj_cgroup_from_current();
	अगर (!objcg)
		वापस PCPU_CHUNK_ROOT;

	अगर (obj_cgroup_अक्षरge(objcg, gfp, size * num_possible_cpus())) अणु
		obj_cgroup_put(objcg);
		वापस PCPU_FAIL_ALLOC;
	पूर्ण

	*objcgp = objcg;
	वापस PCPU_CHUNK_MEMCG;
पूर्ण

अटल व्योम pcpu_memcg_post_alloc_hook(काष्ठा obj_cgroup *objcg,
				       काष्ठा pcpu_chunk *chunk, पूर्णांक off,
				       माप_प्रकार size)
अणु
	अगर (!objcg)
		वापस;

	अगर (chunk) अणु
		chunk->obj_cgroups[off >> PCPU_MIN_ALLOC_SHIFT] = objcg;

		rcu_पढ़ो_lock();
		mod_memcg_state(obj_cgroup_memcg(objcg), MEMCG_PERCPU_B,
				size * num_possible_cpus());
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		obj_cgroup_unअक्षरge(objcg, size * num_possible_cpus());
		obj_cgroup_put(objcg);
	पूर्ण
पूर्ण

अटल व्योम pcpu_memcg_मुक्त_hook(काष्ठा pcpu_chunk *chunk, पूर्णांक off, माप_प्रकार size)
अणु
	काष्ठा obj_cgroup *objcg;

	अगर (!pcpu_is_memcg_chunk(pcpu_chunk_type(chunk)))
		वापस;

	objcg = chunk->obj_cgroups[off >> PCPU_MIN_ALLOC_SHIFT];
	chunk->obj_cgroups[off >> PCPU_MIN_ALLOC_SHIFT] = शून्य;

	obj_cgroup_unअक्षरge(objcg, size * num_possible_cpus());

	rcu_पढ़ो_lock();
	mod_memcg_state(obj_cgroup_memcg(objcg), MEMCG_PERCPU_B,
			-(size * num_possible_cpus()));
	rcu_पढ़ो_unlock();

	obj_cgroup_put(objcg);
पूर्ण

#अन्यथा /* CONFIG_MEMCG_KMEM */
अटल क्रमागत pcpu_chunk_type
pcpu_memcg_pre_alloc_hook(माप_प्रकार size, gfp_t gfp, काष्ठा obj_cgroup **objcgp)
अणु
	वापस PCPU_CHUNK_ROOT;
पूर्ण

अटल व्योम pcpu_memcg_post_alloc_hook(काष्ठा obj_cgroup *objcg,
				       काष्ठा pcpu_chunk *chunk, पूर्णांक off,
				       माप_प्रकार size)
अणु
पूर्ण

अटल व्योम pcpu_memcg_मुक्त_hook(काष्ठा pcpu_chunk *chunk, पूर्णांक off, माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG_KMEM */

/**
 * pcpu_alloc - the percpu allocator
 * @size: size of area to allocate in bytes
 * @align: alignment of area (max PAGE_SIZE)
 * @reserved: allocate from the reserved chunk अगर available
 * @gfp: allocation flags
 *
 * Allocate percpu area of @size bytes aligned at @align.  If @gfp करोesn't
 * contain %GFP_KERNEL, the allocation is atomic. If @gfp has __GFP_NOWARN
 * then no warning will be triggered on invalid or failed allocation
 * requests.
 *
 * RETURNS:
 * Percpu poपूर्णांकer to the allocated area on success, शून्य on failure.
 */
अटल व्योम __percpu *pcpu_alloc(माप_प्रकार size, माप_प्रकार align, bool reserved,
				 gfp_t gfp)
अणु
	gfp_t pcpu_gfp;
	bool is_atomic;
	bool करो_warn;
	क्रमागत pcpu_chunk_type type;
	काष्ठा list_head *pcpu_slot;
	काष्ठा obj_cgroup *objcg = शून्य;
	अटल पूर्णांक warn_limit = 10;
	काष्ठा pcpu_chunk *chunk, *next;
	स्थिर अक्षर *err;
	पूर्णांक slot, off, cpu, ret;
	अचिन्हित दीर्घ flags;
	व्योम __percpu *ptr;
	माप_प्रकार bits, bit_align;

	gfp = current_gfp_context(gfp);
	/* whitelisted flags that can be passed to the backing allocators */
	pcpu_gfp = gfp & (GFP_KERNEL | __GFP_NORETRY | __GFP_NOWARN);
	is_atomic = (gfp & GFP_KERNEL) != GFP_KERNEL;
	करो_warn = !(gfp & __GFP_NOWARN);

	/*
	 * There is now a minimum allocation size of PCPU_MIN_ALLOC_SIZE,
	 * thereक्रमe alignment must be a minimum of that many bytes.
	 * An allocation may have पूर्णांकernal fragmentation from rounding up
	 * of up to PCPU_MIN_ALLOC_SIZE - 1 bytes.
	 */
	अगर (unlikely(align < PCPU_MIN_ALLOC_SIZE))
		align = PCPU_MIN_ALLOC_SIZE;

	size = ALIGN(size, PCPU_MIN_ALLOC_SIZE);
	bits = size >> PCPU_MIN_ALLOC_SHIFT;
	bit_align = align >> PCPU_MIN_ALLOC_SHIFT;

	अगर (unlikely(!size || size > PCPU_MIN_UNIT_SIZE || align > PAGE_SIZE ||
		     !is_घातer_of_2(align))) अणु
		WARN(करो_warn, "illegal size (%zu) or align (%zu) for percpu allocation\n",
		     size, align);
		वापस शून्य;
	पूर्ण

	type = pcpu_memcg_pre_alloc_hook(size, gfp, &objcg);
	अगर (unlikely(type == PCPU_FAIL_ALLOC))
		वापस शून्य;
	pcpu_slot = pcpu_chunk_list(type);

	अगर (!is_atomic) अणु
		/*
		 * pcpu_balance_workfn() allocates memory under this mutex,
		 * and it may रुको क्रम memory reclaim. Allow current task
		 * to become OOM victim, in हाल of memory pressure.
		 */
		अगर (gfp & __GFP_NOFAIL) अणु
			mutex_lock(&pcpu_alloc_mutex);
		पूर्ण अन्यथा अगर (mutex_lock_समाप्तable(&pcpu_alloc_mutex)) अणु
			pcpu_memcg_post_alloc_hook(objcg, शून्य, 0, size);
			वापस शून्य;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&pcpu_lock, flags);

	/* serve reserved allocations from the reserved chunk अगर available */
	अगर (reserved && pcpu_reserved_chunk) अणु
		chunk = pcpu_reserved_chunk;

		off = pcpu_find_block_fit(chunk, bits, bit_align, is_atomic);
		अगर (off < 0) अणु
			err = "alloc from reserved chunk failed";
			जाओ fail_unlock;
		पूर्ण

		off = pcpu_alloc_area(chunk, bits, bit_align, off);
		अगर (off >= 0)
			जाओ area_found;

		err = "alloc from reserved chunk failed";
		जाओ fail_unlock;
	पूर्ण

restart:
	/* search through normal chunks */
	क्रम (slot = pcpu_माप_प्रकारo_slot(size); slot < pcpu_nr_slots; slot++) अणु
		list_क्रम_each_entry_safe(chunk, next, &pcpu_slot[slot], list) अणु
			off = pcpu_find_block_fit(chunk, bits, bit_align,
						  is_atomic);
			अगर (off < 0) अणु
				अगर (slot < PCPU_SLOT_FAIL_THRESHOLD)
					pcpu_chunk_move(chunk, 0);
				जारी;
			पूर्ण

			off = pcpu_alloc_area(chunk, bits, bit_align, off);
			अगर (off >= 0)
				जाओ area_found;

		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&pcpu_lock, flags);

	/*
	 * No space left.  Create a new chunk.  We करोn't want multiple
	 * tasks to create chunks simultaneously.  Serialize and create अगरf
	 * there's still no empty chunk after grabbing the mutex.
	 */
	अगर (is_atomic) अणु
		err = "atomic alloc failed, no space left";
		जाओ fail;
	पूर्ण

	अगर (list_empty(&pcpu_slot[pcpu_nr_slots - 1])) अणु
		chunk = pcpu_create_chunk(type, pcpu_gfp);
		अगर (!chunk) अणु
			err = "failed to allocate new chunk";
			जाओ fail;
		पूर्ण

		spin_lock_irqsave(&pcpu_lock, flags);
		pcpu_chunk_relocate(chunk, -1);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&pcpu_lock, flags);
	पूर्ण

	जाओ restart;

area_found:
	pcpu_stats_area_alloc(chunk, size);
	spin_unlock_irqrestore(&pcpu_lock, flags);

	/* populate अगर not all pages are alपढ़ोy there */
	अगर (!is_atomic) अणु
		अचिन्हित पूर्णांक page_start, page_end, rs, re;

		page_start = PFN_DOWN(off);
		page_end = PFN_UP(off + size);

		biपंचांगap_क्रम_each_clear_region(chunk->populated, rs, re,
					     page_start, page_end) अणु
			WARN_ON(chunk->immutable);

			ret = pcpu_populate_chunk(chunk, rs, re, pcpu_gfp);

			spin_lock_irqsave(&pcpu_lock, flags);
			अगर (ret) अणु
				pcpu_मुक्त_area(chunk, off);
				err = "failed to populate";
				जाओ fail_unlock;
			पूर्ण
			pcpu_chunk_populated(chunk, rs, re);
			spin_unlock_irqrestore(&pcpu_lock, flags);
		पूर्ण

		mutex_unlock(&pcpu_alloc_mutex);
	पूर्ण

	अगर (pcpu_nr_empty_pop_pages[type] < PCPU_EMPTY_POP_PAGES_LOW)
		pcpu_schedule_balance_work();

	/* clear the areas and वापस address relative to base address */
	क्रम_each_possible_cpu(cpu)
		स_रखो((व्योम *)pcpu_chunk_addr(chunk, cpu, 0) + off, 0, size);

	ptr = __addr_to_pcpu_ptr(chunk->base_addr + off);
	kmemleak_alloc_percpu(ptr, size, gfp);

	trace_percpu_alloc_percpu(reserved, is_atomic, size, align,
			chunk->base_addr, off, ptr);

	pcpu_memcg_post_alloc_hook(objcg, chunk, off, size);

	वापस ptr;

fail_unlock:
	spin_unlock_irqrestore(&pcpu_lock, flags);
fail:
	trace_percpu_alloc_percpu_fail(reserved, is_atomic, size, align);

	अगर (!is_atomic && करो_warn && warn_limit) अणु
		pr_warn("allocation failed, size=%zu align=%zu atomic=%d, %s\n",
			size, align, is_atomic, err);
		dump_stack();
		अगर (!--warn_limit)
			pr_info("limit reached, disable warning\n");
	पूर्ण
	अगर (is_atomic) अणु
		/* see the flag handling in pcpu_balance_workfn() */
		pcpu_atomic_alloc_failed = true;
		pcpu_schedule_balance_work();
	पूर्ण अन्यथा अणु
		mutex_unlock(&pcpu_alloc_mutex);
	पूर्ण

	pcpu_memcg_post_alloc_hook(objcg, शून्य, 0, size);

	वापस शून्य;
पूर्ण

/**
 * __alloc_percpu_gfp - allocate dynamic percpu area
 * @size: size of area to allocate in bytes
 * @align: alignment of area (max PAGE_SIZE)
 * @gfp: allocation flags
 *
 * Allocate zero-filled percpu area of @size bytes aligned at @align.  If
 * @gfp करोesn't contain %GFP_KERNEL, the allocation doesn't block and can
 * be called from any context but is a lot more likely to fail. If @gfp
 * has __GFP_NOWARN then no warning will be triggered on invalid or failed
 * allocation requests.
 *
 * RETURNS:
 * Percpu poपूर्णांकer to the allocated area on success, शून्य on failure.
 */
व्योम __percpu *__alloc_percpu_gfp(माप_प्रकार size, माप_प्रकार align, gfp_t gfp)
अणु
	वापस pcpu_alloc(size, align, false, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(__alloc_percpu_gfp);

/**
 * __alloc_percpu - allocate dynamic percpu area
 * @size: size of area to allocate in bytes
 * @align: alignment of area (max PAGE_SIZE)
 *
 * Equivalent to __alloc_percpu_gfp(size, align, %GFP_KERNEL).
 */
व्योम __percpu *__alloc_percpu(माप_प्रकार size, माप_प्रकार align)
अणु
	वापस pcpu_alloc(size, align, false, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL_GPL(__alloc_percpu);

/**
 * __alloc_reserved_percpu - allocate reserved percpu area
 * @size: size of area to allocate in bytes
 * @align: alignment of area (max PAGE_SIZE)
 *
 * Allocate zero-filled percpu area of @size bytes aligned at @align
 * from reserved percpu area अगर arch has set it up; otherwise,
 * allocation is served from the same dynamic area.  Might sleep.
 * Might trigger ग_लिखोouts.
 *
 * CONTEXT:
 * Does GFP_KERNEL allocation.
 *
 * RETURNS:
 * Percpu poपूर्णांकer to the allocated area on success, शून्य on failure.
 */
व्योम __percpu *__alloc_reserved_percpu(माप_प्रकार size, माप_प्रकार align)
अणु
	वापस pcpu_alloc(size, align, true, GFP_KERNEL);
पूर्ण

/**
 * __pcpu_balance_workfn - manage the amount of मुक्त chunks and populated pages
 * @type: chunk type
 *
 * Reclaim all fully मुक्त chunks except क्रम the first one.  This is also
 * responsible क्रम मुख्यtaining the pool of empty populated pages.  However,
 * it is possible that this is called when physical memory is scarce causing
 * OOM समाप्तer to be triggered.  We should aव्योम करोing so until an actual
 * allocation causes the failure as it is possible that requests can be
 * serviced from alपढ़ोy backed regions.
 */
अटल व्योम __pcpu_balance_workfn(क्रमागत pcpu_chunk_type type)
अणु
	/* gfp flags passed to underlying allocators */
	स्थिर gfp_t gfp = GFP_KERNEL | __GFP_NORETRY | __GFP_NOWARN;
	LIST_HEAD(to_मुक्त);
	काष्ठा list_head *pcpu_slot = pcpu_chunk_list(type);
	काष्ठा list_head *मुक्त_head = &pcpu_slot[pcpu_nr_slots - 1];
	काष्ठा pcpu_chunk *chunk, *next;
	पूर्णांक slot, nr_to_pop, ret;

	/*
	 * There's no reason to keep around multiple unused chunks and VM
	 * areas can be scarce.  Destroy all मुक्त chunks except क्रम one.
	 */
	mutex_lock(&pcpu_alloc_mutex);
	spin_lock_irq(&pcpu_lock);

	list_क्रम_each_entry_safe(chunk, next, मुक्त_head, list) अणु
		WARN_ON(chunk->immutable);

		/* spare the first one */
		अगर (chunk == list_first_entry(मुक्त_head, काष्ठा pcpu_chunk, list))
			जारी;

		list_move(&chunk->list, &to_मुक्त);
	पूर्ण

	spin_unlock_irq(&pcpu_lock);

	list_क्रम_each_entry_safe(chunk, next, &to_मुक्त, list) अणु
		अचिन्हित पूर्णांक rs, re;

		biपंचांगap_क्रम_each_set_region(chunk->populated, rs, re, 0,
					   chunk->nr_pages) अणु
			pcpu_depopulate_chunk(chunk, rs, re);
			spin_lock_irq(&pcpu_lock);
			pcpu_chunk_depopulated(chunk, rs, re);
			spin_unlock_irq(&pcpu_lock);
		पूर्ण
		pcpu_destroy_chunk(chunk);
		cond_resched();
	पूर्ण

	/*
	 * Ensure there are certain number of मुक्त populated pages क्रम
	 * atomic allocs.  Fill up from the most packed so that atomic
	 * allocs करोn't increase fragmentation.  If atomic allocation
	 * failed previously, always populate the maximum amount.  This
	 * should prevent atomic allocs larger than PAGE_SIZE from keeping
	 * failing indefinitely; however, large atomic allocs are not
	 * something we support properly and can be highly unreliable and
	 * inefficient.
	 */
retry_pop:
	अगर (pcpu_atomic_alloc_failed) अणु
		nr_to_pop = PCPU_EMPTY_POP_PAGES_HIGH;
		/* best efक्रमt anyway, करोn't worry about synchronization */
		pcpu_atomic_alloc_failed = false;
	पूर्ण अन्यथा अणु
		nr_to_pop = clamp(PCPU_EMPTY_POP_PAGES_HIGH -
				  pcpu_nr_empty_pop_pages[type],
				  0, PCPU_EMPTY_POP_PAGES_HIGH);
	पूर्ण

	क्रम (slot = pcpu_माप_प्रकारo_slot(PAGE_SIZE); slot < pcpu_nr_slots; slot++) अणु
		अचिन्हित पूर्णांक nr_unpop = 0, rs, re;

		अगर (!nr_to_pop)
			अवरोध;

		spin_lock_irq(&pcpu_lock);
		list_क्रम_each_entry(chunk, &pcpu_slot[slot], list) अणु
			nr_unpop = chunk->nr_pages - chunk->nr_populated;
			अगर (nr_unpop)
				अवरोध;
		पूर्ण
		spin_unlock_irq(&pcpu_lock);

		अगर (!nr_unpop)
			जारी;

		/* @chunk can't go away जबतक pcpu_alloc_mutex is held */
		biपंचांगap_क्रम_each_clear_region(chunk->populated, rs, re, 0,
					     chunk->nr_pages) अणु
			पूर्णांक nr = min_t(पूर्णांक, re - rs, nr_to_pop);

			ret = pcpu_populate_chunk(chunk, rs, rs + nr, gfp);
			अगर (!ret) अणु
				nr_to_pop -= nr;
				spin_lock_irq(&pcpu_lock);
				pcpu_chunk_populated(chunk, rs, rs + nr);
				spin_unlock_irq(&pcpu_lock);
			पूर्ण अन्यथा अणु
				nr_to_pop = 0;
			पूर्ण

			अगर (!nr_to_pop)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (nr_to_pop) अणु
		/* ran out of chunks to populate, create a new one and retry */
		chunk = pcpu_create_chunk(type, gfp);
		अगर (chunk) अणु
			spin_lock_irq(&pcpu_lock);
			pcpu_chunk_relocate(chunk, -1);
			spin_unlock_irq(&pcpu_lock);
			जाओ retry_pop;
		पूर्ण
	पूर्ण

	mutex_unlock(&pcpu_alloc_mutex);
पूर्ण

/**
 * pcpu_balance_workfn - manage the amount of मुक्त chunks and populated pages
 * @work: unused
 *
 * Call __pcpu_balance_workfn() क्रम each chunk type.
 */
अटल व्योम pcpu_balance_workfn(काष्ठा work_काष्ठा *work)
अणु
	क्रमागत pcpu_chunk_type type;

	क्रम (type = 0; type < PCPU_NR_CHUNK_TYPES; type++)
		__pcpu_balance_workfn(type);
पूर्ण

/**
 * मुक्त_percpu - मुक्त percpu area
 * @ptr: poपूर्णांकer to area to मुक्त
 *
 * Free percpu area @ptr.
 *
 * CONTEXT:
 * Can be called from atomic context.
 */
व्योम मुक्त_percpu(व्योम __percpu *ptr)
अणु
	व्योम *addr;
	काष्ठा pcpu_chunk *chunk;
	अचिन्हित दीर्घ flags;
	पूर्णांक size, off;
	bool need_balance = false;
	काष्ठा list_head *pcpu_slot;

	अगर (!ptr)
		वापस;

	kmemleak_मुक्त_percpu(ptr);

	addr = __pcpu_ptr_to_addr(ptr);

	spin_lock_irqsave(&pcpu_lock, flags);

	chunk = pcpu_chunk_addr_search(addr);
	off = addr - chunk->base_addr;

	size = pcpu_मुक्त_area(chunk, off);

	pcpu_slot = pcpu_chunk_list(pcpu_chunk_type(chunk));

	pcpu_memcg_मुक्त_hook(chunk, off, size);

	/* अगर there are more than one fully मुक्त chunks, wake up grim reaper */
	अगर (chunk->मुक्त_bytes == pcpu_unit_size) अणु
		काष्ठा pcpu_chunk *pos;

		list_क्रम_each_entry(pos, &pcpu_slot[pcpu_nr_slots - 1], list)
			अगर (pos != chunk) अणु
				need_balance = true;
				अवरोध;
			पूर्ण
	पूर्ण

	trace_percpu_मुक्त_percpu(chunk->base_addr, off, ptr);

	spin_unlock_irqrestore(&pcpu_lock, flags);

	अगर (need_balance)
		pcpu_schedule_balance_work();
पूर्ण
EXPORT_SYMBOL_GPL(मुक्त_percpu);

bool __is_kernel_percpu_address(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ *can_addr)
अणु
#अगर_घोषित CONFIG_SMP
	स्थिर माप_प्रकार अटल_size = __per_cpu_end - __per_cpu_start;
	व्योम __percpu *base = __addr_to_pcpu_ptr(pcpu_base_addr);
	अचिन्हित पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		व्योम *start = per_cpu_ptr(base, cpu);
		व्योम *va = (व्योम *)addr;

		अगर (va >= start && va < start + अटल_size) अणु
			अगर (can_addr) अणु
				*can_addr = (अचिन्हित दीर्घ) (va - start);
				*can_addr += (अचिन्हित दीर्घ)
					per_cpu_ptr(base, get_boot_cpu_id());
			पूर्ण
			वापस true;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	/* on UP, can't distinguish from other अटल vars, always false */
	वापस false;
पूर्ण

/**
 * is_kernel_percpu_address - test whether address is from अटल percpu area
 * @addr: address to test
 *
 * Test whether @addr beदीर्घs to in-kernel अटल percpu area.  Module
 * अटल percpu areas are not considered.  For those, use
 * is_module_percpu_address().
 *
 * RETURNS:
 * %true अगर @addr is from in-kernel अटल percpu area, %false otherwise.
 */
bool is_kernel_percpu_address(अचिन्हित दीर्घ addr)
अणु
	वापस __is_kernel_percpu_address(addr, शून्य);
पूर्ण

/**
 * per_cpu_ptr_to_phys - convert translated percpu address to physical address
 * @addr: the address to be converted to physical address
 *
 * Given @addr which is dereferenceable address obtained via one of
 * percpu access macros, this function translates it पूर्णांकo its physical
 * address.  The caller is responsible क्रम ensuring @addr stays valid
 * until this function finishes.
 *
 * percpu allocator has special setup क्रम the first chunk, which currently
 * supports either embedding in linear address space or vदो_स्मृति mapping,
 * and, from the second one, the backing allocator (currently either vm or
 * km) provides translation.
 *
 * The addr can be translated simply without checking अगर it falls पूर्णांकo the
 * first chunk. But the current code reflects better how percpu allocator
 * actually works, and the verअगरication can discover both bugs in percpu
 * allocator itself and per_cpu_ptr_to_phys() callers. So we keep current
 * code.
 *
 * RETURNS:
 * The physical address क्रम @addr.
 */
phys_addr_t per_cpu_ptr_to_phys(व्योम *addr)
अणु
	व्योम __percpu *base = __addr_to_pcpu_ptr(pcpu_base_addr);
	bool in_first_chunk = false;
	अचिन्हित दीर्घ first_low, first_high;
	अचिन्हित पूर्णांक cpu;

	/*
	 * The following test on unit_low/high isn't strictly
	 * necessary but will speed up lookups of addresses which
	 * aren't in the first chunk.
	 *
	 * The address check is against full chunk sizes.  pcpu_base_addr
	 * poपूर्णांकs to the beginning of the first chunk including the
	 * अटल region.  Assumes good पूर्णांकent as the first chunk may
	 * not be full (ie. < pcpu_unit_pages in size).
	 */
	first_low = (अचिन्हित दीर्घ)pcpu_base_addr +
		    pcpu_unit_page_offset(pcpu_low_unit_cpu, 0);
	first_high = (अचिन्हित दीर्घ)pcpu_base_addr +
		     pcpu_unit_page_offset(pcpu_high_unit_cpu, pcpu_unit_pages);
	अगर ((अचिन्हित दीर्घ)addr >= first_low &&
	    (अचिन्हित दीर्घ)addr < first_high) अणु
		क्रम_each_possible_cpu(cpu) अणु
			व्योम *start = per_cpu_ptr(base, cpu);

			अगर (addr >= start && addr < start + pcpu_unit_size) अणु
				in_first_chunk = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (in_first_chunk) अणु
		अगर (!is_vदो_स्मृति_addr(addr))
			वापस __pa(addr);
		अन्यथा
			वापस page_to_phys(vदो_स्मृति_to_page(addr)) +
			       offset_in_page(addr);
	पूर्ण अन्यथा
		वापस page_to_phys(pcpu_addr_to_page(addr)) +
		       offset_in_page(addr);
पूर्ण

/**
 * pcpu_alloc_alloc_info - allocate percpu allocation info
 * @nr_groups: the number of groups
 * @nr_units: the number of units
 *
 * Allocate ai which is large enough क्रम @nr_groups groups containing
 * @nr_units units.  The वापसed ai's groups[0].cpu_map poपूर्णांकs to the
 * cpu_map array which is दीर्घ enough क्रम @nr_units and filled with
 * NR_CPUS.  It's the caller's responsibility to initialize cpu_map
 * poपूर्णांकer of other groups.
 *
 * RETURNS:
 * Poपूर्णांकer to the allocated pcpu_alloc_info on success, शून्य on
 * failure.
 */
काष्ठा pcpu_alloc_info * __init pcpu_alloc_alloc_info(पूर्णांक nr_groups,
						      पूर्णांक nr_units)
अणु
	काष्ठा pcpu_alloc_info *ai;
	माप_प्रकार base_size, ai_size;
	व्योम *ptr;
	पूर्णांक unit;

	base_size = ALIGN(काष्ठा_size(ai, groups, nr_groups),
			  __alignof__(ai->groups[0].cpu_map[0]));
	ai_size = base_size + nr_units * माप(ai->groups[0].cpu_map[0]);

	ptr = memblock_alloc(PFN_ALIGN(ai_size), PAGE_SIZE);
	अगर (!ptr)
		वापस शून्य;
	ai = ptr;
	ptr += base_size;

	ai->groups[0].cpu_map = ptr;

	क्रम (unit = 0; unit < nr_units; unit++)
		ai->groups[0].cpu_map[unit] = NR_CPUS;

	ai->nr_groups = nr_groups;
	ai->__ai_size = PFN_ALIGN(ai_size);

	वापस ai;
पूर्ण

/**
 * pcpu_मुक्त_alloc_info - मुक्त percpu allocation info
 * @ai: pcpu_alloc_info to मुक्त
 *
 * Free @ai which was allocated by pcpu_alloc_alloc_info().
 */
व्योम __init pcpu_मुक्त_alloc_info(काष्ठा pcpu_alloc_info *ai)
अणु
	memblock_मुक्त_early(__pa(ai), ai->__ai_size);
पूर्ण

/**
 * pcpu_dump_alloc_info - prपूर्णांक out inक्रमmation about pcpu_alloc_info
 * @lvl: loglevel
 * @ai: allocation info to dump
 *
 * Prपूर्णांक out inक्रमmation about @ai using loglevel @lvl.
 */
अटल व्योम pcpu_dump_alloc_info(स्थिर अक्षर *lvl,
				 स्थिर काष्ठा pcpu_alloc_info *ai)
अणु
	पूर्णांक group_width = 1, cpu_width = 1, width;
	अक्षर empty_str[] = "--------";
	पूर्णांक alloc = 0, alloc_end = 0;
	पूर्णांक group, v;
	पूर्णांक upa, apl;	/* units per alloc, allocs per line */

	v = ai->nr_groups;
	जबतक (v /= 10)
		group_width++;

	v = num_possible_cpus();
	जबतक (v /= 10)
		cpu_width++;
	empty_str[min_t(पूर्णांक, cpu_width, माप(empty_str) - 1)] = '\0';

	upa = ai->alloc_size / ai->unit_size;
	width = upa * (cpu_width + 1) + group_width + 3;
	apl = roundकरोwn_घात_of_two(max(60 / width, 1));

	prपूर्णांकk("%spcpu-alloc: s%zu r%zu d%zu u%zu alloc=%zu*%zu",
	       lvl, ai->अटल_size, ai->reserved_size, ai->dyn_size,
	       ai->unit_size, ai->alloc_size / ai->atom_size, ai->atom_size);

	क्रम (group = 0; group < ai->nr_groups; group++) अणु
		स्थिर काष्ठा pcpu_group_info *gi = &ai->groups[group];
		पूर्णांक unit = 0, unit_end = 0;

		BUG_ON(gi->nr_units % upa);
		क्रम (alloc_end += gi->nr_units / upa;
		     alloc < alloc_end; alloc++) अणु
			अगर (!(alloc % apl)) अणु
				pr_cont("\n");
				prपूर्णांकk("%spcpu-alloc: ", lvl);
			पूर्ण
			pr_cont("[%0*d] ", group_width, group);

			क्रम (unit_end += upa; unit < unit_end; unit++)
				अगर (gi->cpu_map[unit] != NR_CPUS)
					pr_cont("%0*d ",
						cpu_width, gi->cpu_map[unit]);
				अन्यथा
					pr_cont("%s ", empty_str);
		पूर्ण
	पूर्ण
	pr_cont("\n");
पूर्ण

/**
 * pcpu_setup_first_chunk - initialize the first percpu chunk
 * @ai: pcpu_alloc_info describing how to percpu area is shaped
 * @base_addr: mapped address
 *
 * Initialize the first percpu chunk which contains the kernel अटल
 * percpu area.  This function is to be called from arch percpu area
 * setup path.
 *
 * @ai contains all inक्रमmation necessary to initialize the first
 * chunk and prime the dynamic percpu allocator.
 *
 * @ai->अटल_size is the size of अटल percpu area.
 *
 * @ai->reserved_size, अगर non-zero, specअगरies the amount of bytes to
 * reserve after the अटल area in the first chunk.  This reserves
 * the first chunk such that it's available only through reserved
 * percpu allocation.  This is primarily used to serve module percpu
 * अटल areas on architectures where the addressing model has
 * limited offset range क्रम symbol relocations to guarantee module
 * percpu symbols fall inside the relocatable range.
 *
 * @ai->dyn_size determines the number of bytes available क्रम dynamic
 * allocation in the first chunk.  The area between @ai->अटल_size +
 * @ai->reserved_size + @ai->dyn_size and @ai->unit_size is unused.
 *
 * @ai->unit_size specअगरies unit size and must be aligned to PAGE_SIZE
 * and equal to or larger than @ai->अटल_size + @ai->reserved_size +
 * @ai->dyn_size.
 *
 * @ai->atom_size is the allocation atom size and used as alignment
 * क्रम vm areas.
 *
 * @ai->alloc_size is the allocation size and always multiple of
 * @ai->atom_size.  This is larger than @ai->atom_size अगर
 * @ai->unit_size is larger than @ai->atom_size.
 *
 * @ai->nr_groups and @ai->groups describe भव memory layout of
 * percpu areas.  Units which should be colocated are put पूर्णांकo the
 * same group.  Dynamic VM areas will be allocated according to these
 * groupings.  If @ai->nr_groups is zero, a single group containing
 * all units is assumed.
 *
 * The caller should have mapped the first chunk at @base_addr and
 * copied अटल data to each unit.
 *
 * The first chunk will always contain a अटल and a dynamic region.
 * However, the अटल region is not managed by any chunk.  If the first
 * chunk also contains a reserved region, it is served by two chunks -
 * one क्रम the reserved region and one क्रम the dynamic region.  They
 * share the same vm, but use offset regions in the area allocation map.
 * The chunk serving the dynamic region is circulated in the chunk slots
 * and available क्रम dynamic allocation like any other chunk.
 */
व्योम __init pcpu_setup_first_chunk(स्थिर काष्ठा pcpu_alloc_info *ai,
				   व्योम *base_addr)
अणु
	माप_प्रकार size_sum = ai->अटल_size + ai->reserved_size + ai->dyn_size;
	माप_प्रकार अटल_size, dyn_size;
	काष्ठा pcpu_chunk *chunk;
	अचिन्हित दीर्घ *group_offsets;
	माप_प्रकार *group_sizes;
	अचिन्हित दीर्घ *unit_off;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक *unit_map;
	पूर्णांक group, unit, i;
	पूर्णांक map_size;
	अचिन्हित दीर्घ पंचांगp_addr;
	माप_प्रकार alloc_size;
	क्रमागत pcpu_chunk_type type;

#घोषणा PCPU_SETUP_BUG_ON(cond)	करो अणु					\
	अगर (unlikely(cond)) अणु						\
		pr_emerg("failed to initialize, %s\n", #cond);		\
		pr_emerg("cpu_possible_mask=%*pb\n",			\
			 cpumask_pr_args(cpu_possible_mask));		\
		pcpu_dump_alloc_info(KERN_EMERG, ai);			\
		BUG();							\
	पूर्ण								\
पूर्ण जबतक (0)

	/* sanity checks */
	PCPU_SETUP_BUG_ON(ai->nr_groups <= 0);
#अगर_घोषित CONFIG_SMP
	PCPU_SETUP_BUG_ON(!ai->अटल_size);
	PCPU_SETUP_BUG_ON(offset_in_page(__per_cpu_start));
#पूर्ण_अगर
	PCPU_SETUP_BUG_ON(!base_addr);
	PCPU_SETUP_BUG_ON(offset_in_page(base_addr));
	PCPU_SETUP_BUG_ON(ai->unit_size < size_sum);
	PCPU_SETUP_BUG_ON(offset_in_page(ai->unit_size));
	PCPU_SETUP_BUG_ON(ai->unit_size < PCPU_MIN_UNIT_SIZE);
	PCPU_SETUP_BUG_ON(!IS_ALIGNED(ai->unit_size, PCPU_BITMAP_BLOCK_SIZE));
	PCPU_SETUP_BUG_ON(ai->dyn_size < PERCPU_DYNAMIC_EARLY_SIZE);
	PCPU_SETUP_BUG_ON(!ai->dyn_size);
	PCPU_SETUP_BUG_ON(!IS_ALIGNED(ai->reserved_size, PCPU_MIN_ALLOC_SIZE));
	PCPU_SETUP_BUG_ON(!(IS_ALIGNED(PCPU_BITMAP_BLOCK_SIZE, PAGE_SIZE) ||
			    IS_ALIGNED(PAGE_SIZE, PCPU_BITMAP_BLOCK_SIZE)));
	PCPU_SETUP_BUG_ON(pcpu_verअगरy_alloc_info(ai) < 0);

	/* process group inक्रमmation and build config tables accordingly */
	alloc_size = ai->nr_groups * माप(group_offsets[0]);
	group_offsets = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!group_offsets)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

	alloc_size = ai->nr_groups * माप(group_sizes[0]);
	group_sizes = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!group_sizes)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

	alloc_size = nr_cpu_ids * माप(unit_map[0]);
	unit_map = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!unit_map)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

	alloc_size = nr_cpu_ids * माप(unit_off[0]);
	unit_off = memblock_alloc(alloc_size, SMP_CACHE_BYTES);
	अगर (!unit_off)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      alloc_size);

	क्रम (cpu = 0; cpu < nr_cpu_ids; cpu++)
		unit_map[cpu] = अच_पूर्णांक_उच्च;

	pcpu_low_unit_cpu = NR_CPUS;
	pcpu_high_unit_cpu = NR_CPUS;

	क्रम (group = 0, unit = 0; group < ai->nr_groups; group++, unit += i) अणु
		स्थिर काष्ठा pcpu_group_info *gi = &ai->groups[group];

		group_offsets[group] = gi->base_offset;
		group_sizes[group] = gi->nr_units * ai->unit_size;

		क्रम (i = 0; i < gi->nr_units; i++) अणु
			cpu = gi->cpu_map[i];
			अगर (cpu == NR_CPUS)
				जारी;

			PCPU_SETUP_BUG_ON(cpu >= nr_cpu_ids);
			PCPU_SETUP_BUG_ON(!cpu_possible(cpu));
			PCPU_SETUP_BUG_ON(unit_map[cpu] != अच_पूर्णांक_उच्च);

			unit_map[cpu] = unit + i;
			unit_off[cpu] = gi->base_offset + i * ai->unit_size;

			/* determine low/high unit_cpu */
			अगर (pcpu_low_unit_cpu == NR_CPUS ||
			    unit_off[cpu] < unit_off[pcpu_low_unit_cpu])
				pcpu_low_unit_cpu = cpu;
			अगर (pcpu_high_unit_cpu == NR_CPUS ||
			    unit_off[cpu] > unit_off[pcpu_high_unit_cpu])
				pcpu_high_unit_cpu = cpu;
		पूर्ण
	पूर्ण
	pcpu_nr_units = unit;

	क्रम_each_possible_cpu(cpu)
		PCPU_SETUP_BUG_ON(unit_map[cpu] == अच_पूर्णांक_उच्च);

	/* we're करोne parsing the input, undefine BUG macro and dump config */
#अघोषित PCPU_SETUP_BUG_ON
	pcpu_dump_alloc_info(KERN_DEBUG, ai);

	pcpu_nr_groups = ai->nr_groups;
	pcpu_group_offsets = group_offsets;
	pcpu_group_sizes = group_sizes;
	pcpu_unit_map = unit_map;
	pcpu_unit_offsets = unit_off;

	/* determine basic parameters */
	pcpu_unit_pages = ai->unit_size >> PAGE_SHIFT;
	pcpu_unit_size = pcpu_unit_pages << PAGE_SHIFT;
	pcpu_atom_size = ai->atom_size;
	pcpu_chunk_काष्ठा_size = काष्ठा_size(chunk, populated,
					     BITS_TO_LONGS(pcpu_unit_pages));

	pcpu_stats_save_ai(ai);

	/*
	 * Allocate chunk slots.  The additional last slot is क्रम
	 * empty chunks.
	 */
	pcpu_nr_slots = __pcpu_माप_प्रकारo_slot(pcpu_unit_size) + 2;
	pcpu_chunk_lists = memblock_alloc(pcpu_nr_slots *
					  माप(pcpu_chunk_lists[0]) *
					  PCPU_NR_CHUNK_TYPES,
					  SMP_CACHE_BYTES);
	अगर (!pcpu_chunk_lists)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      pcpu_nr_slots * माप(pcpu_chunk_lists[0]) *
		      PCPU_NR_CHUNK_TYPES);

	क्रम (type = 0; type < PCPU_NR_CHUNK_TYPES; type++)
		क्रम (i = 0; i < pcpu_nr_slots; i++)
			INIT_LIST_HEAD(&pcpu_chunk_list(type)[i]);

	/*
	 * The end of the अटल region needs to be aligned with the
	 * minimum allocation size as this offsets the reserved and
	 * dynamic region.  The first chunk ends page aligned by
	 * expanding the dynamic region, thereक्रमe the dynamic region
	 * can be shrunk to compensate जबतक still staying above the
	 * configured sizes.
	 */
	अटल_size = ALIGN(ai->अटल_size, PCPU_MIN_ALLOC_SIZE);
	dyn_size = ai->dyn_size - (अटल_size - ai->अटल_size);

	/*
	 * Initialize first chunk.
	 * If the reserved_size is non-zero, this initializes the reserved
	 * chunk.  If the reserved_size is zero, the reserved chunk is शून्य
	 * and the dynamic region is initialized here.  The first chunk,
	 * pcpu_first_chunk, will always poपूर्णांक to the chunk that serves
	 * the dynamic region.
	 */
	पंचांगp_addr = (अचिन्हित दीर्घ)base_addr + अटल_size;
	map_size = ai->reserved_size ?: dyn_size;
	chunk = pcpu_alloc_first_chunk(पंचांगp_addr, map_size);

	/* init dynamic chunk अगर necessary */
	अगर (ai->reserved_size) अणु
		pcpu_reserved_chunk = chunk;

		पंचांगp_addr = (अचिन्हित दीर्घ)base_addr + अटल_size +
			   ai->reserved_size;
		map_size = dyn_size;
		chunk = pcpu_alloc_first_chunk(पंचांगp_addr, map_size);
	पूर्ण

	/* link the first chunk in */
	pcpu_first_chunk = chunk;
	pcpu_nr_empty_pop_pages[PCPU_CHUNK_ROOT] = pcpu_first_chunk->nr_empty_pop_pages;
	pcpu_chunk_relocate(pcpu_first_chunk, -1);

	/* include all regions of the first chunk */
	pcpu_nr_populated += PFN_DOWN(size_sum);

	pcpu_stats_chunk_alloc();
	trace_percpu_create_chunk(base_addr);

	/* we're करोne */
	pcpu_base_addr = base_addr;
पूर्ण

#अगर_घोषित CONFIG_SMP

स्थिर अक्षर * स्थिर pcpu_fc_names[PCPU_FC_NR] __initस्थिर = अणु
	[PCPU_FC_AUTO]	= "auto",
	[PCPU_FC_EMBED]	= "embed",
	[PCPU_FC_PAGE]	= "page",
पूर्ण;

क्रमागत pcpu_fc pcpu_chosen_fc __initdata = PCPU_FC_AUTO;

अटल पूर्णांक __init percpu_alloc_setup(अक्षर *str)
अणु
	अगर (!str)
		वापस -EINVAL;

	अगर (0)
		/* nada */;
#अगर_घोषित CONFIG_NEED_PER_CPU_EMBED_FIRST_CHUNK
	अन्यथा अगर (!म_भेद(str, "embed"))
		pcpu_chosen_fc = PCPU_FC_EMBED;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NEED_PER_CPU_PAGE_FIRST_CHUNK
	अन्यथा अगर (!म_भेद(str, "page"))
		pcpu_chosen_fc = PCPU_FC_PAGE;
#पूर्ण_अगर
	अन्यथा
		pr_warn("unknown allocator %s specified\n", str);

	वापस 0;
पूर्ण
early_param("percpu_alloc", percpu_alloc_setup);

/*
 * pcpu_embed_first_chunk() is used by the generic percpu setup.
 * Build it अगर needed by the arch config or the generic setup is going
 * to be used.
 */
#अगर defined(CONFIG_NEED_PER_CPU_EMBED_FIRST_CHUNK) || \
	!defined(CONFIG_HAVE_SETUP_PER_CPU_AREA)
#घोषणा BUILD_EMBED_FIRST_CHUNK
#पूर्ण_अगर

/* build pcpu_page_first_chunk() अगरf needed by the arch config */
#अगर defined(CONFIG_NEED_PER_CPU_PAGE_FIRST_CHUNK)
#घोषणा BUILD_PAGE_FIRST_CHUNK
#पूर्ण_अगर

/* pcpu_build_alloc_info() is used by both embed and page first chunk */
#अगर defined(BUILD_EMBED_FIRST_CHUNK) || defined(BUILD_PAGE_FIRST_CHUNK)
/**
 * pcpu_build_alloc_info - build alloc_info considering distances between CPUs
 * @reserved_size: the size of reserved percpu area in bytes
 * @dyn_size: minimum मुक्त size क्रम dynamic allocation in bytes
 * @atom_size: allocation atom size
 * @cpu_distance_fn: callback to determine distance between cpus, optional
 *
 * This function determines grouping of units, their mappings to cpus
 * and other parameters considering needed percpu size, allocation
 * atom size and distances between CPUs.
 *
 * Groups are always multiples of atom size and CPUs which are of
 * LOCAL_DISTANCE both ways are grouped together and share space क्रम
 * units in the same group.  The वापसed configuration is guaranteed
 * to have CPUs on dअगरferent nodes on dअगरferent groups and >=75% usage
 * of allocated भव address space.
 *
 * RETURNS:
 * On success, poपूर्णांकer to the new allocation_info is वापसed.  On
 * failure, ERR_PTR value is वापसed.
 */
अटल काष्ठा pcpu_alloc_info * __init __flatten pcpu_build_alloc_info(
				माप_प्रकार reserved_size, माप_प्रकार dyn_size,
				माप_प्रकार atom_size,
				pcpu_fc_cpu_distance_fn_t cpu_distance_fn)
अणु
	अटल पूर्णांक group_map[NR_CPUS] __initdata;
	अटल पूर्णांक group_cnt[NR_CPUS] __initdata;
	अटल काष्ठा cpumask mask __initdata;
	स्थिर माप_प्रकार अटल_size = __per_cpu_end - __per_cpu_start;
	पूर्णांक nr_groups = 1, nr_units = 0;
	माप_प्रकार size_sum, min_unit_size, alloc_size;
	पूर्णांक upa, max_upa, best_upa;	/* units_per_alloc */
	पूर्णांक last_allocs, group, unit;
	अचिन्हित पूर्णांक cpu, tcpu;
	काष्ठा pcpu_alloc_info *ai;
	अचिन्हित पूर्णांक *cpu_map;

	/* this function may be called multiple बार */
	स_रखो(group_map, 0, माप(group_map));
	स_रखो(group_cnt, 0, माप(group_cnt));
	cpumask_clear(&mask);

	/* calculate size_sum and ensure dyn_size is enough क्रम early alloc */
	size_sum = PFN_ALIGN(अटल_size + reserved_size +
			    max_t(माप_प्रकार, dyn_size, PERCPU_DYNAMIC_EARLY_SIZE));
	dyn_size = size_sum - अटल_size - reserved_size;

	/*
	 * Determine min_unit_size, alloc_size and max_upa such that
	 * alloc_size is multiple of atom_size and is the smallest
	 * which can accommodate 4k aligned segments which are equal to
	 * or larger than min_unit_size.
	 */
	min_unit_size = max_t(माप_प्रकार, size_sum, PCPU_MIN_UNIT_SIZE);

	/* determine the maximum # of units that can fit in an allocation */
	alloc_size = roundup(min_unit_size, atom_size);
	upa = alloc_size / min_unit_size;
	जबतक (alloc_size % upa || (offset_in_page(alloc_size / upa)))
		upa--;
	max_upa = upa;

	cpumask_copy(&mask, cpu_possible_mask);

	/* group cpus according to their proximity */
	क्रम (group = 0; !cpumask_empty(&mask); group++) अणु
		/* pop the group's first cpu */
		cpu = cpumask_first(&mask);
		group_map[cpu] = group;
		group_cnt[group]++;
		cpumask_clear_cpu(cpu, &mask);

		क्रम_each_cpu(tcpu, &mask) अणु
			अगर (!cpu_distance_fn ||
			    (cpu_distance_fn(cpu, tcpu) == LOCAL_DISTANCE &&
			     cpu_distance_fn(tcpu, cpu) == LOCAL_DISTANCE)) अणु
				group_map[tcpu] = group;
				group_cnt[group]++;
				cpumask_clear_cpu(tcpu, &mask);
			पूर्ण
		पूर्ण
	पूर्ण
	nr_groups = group;

	/*
	 * Wasted space is caused by a ratio imbalance of upa to group_cnt.
	 * Expand the unit_size until we use >= 75% of the units allocated.
	 * Related to atom_size, which could be much larger than the unit_size.
	 */
	last_allocs = पूर्णांक_उच्च;
	क्रम (upa = max_upa; upa; upa--) अणु
		पूर्णांक allocs = 0, wasted = 0;

		अगर (alloc_size % upa || (offset_in_page(alloc_size / upa)))
			जारी;

		क्रम (group = 0; group < nr_groups; group++) अणु
			पूर्णांक this_allocs = DIV_ROUND_UP(group_cnt[group], upa);
			allocs += this_allocs;
			wasted += this_allocs * upa - group_cnt[group];
		पूर्ण

		/*
		 * Don't accept अगर wastage is over 1/3.  The
		 * greater-than comparison ensures upa==1 always
		 * passes the following check.
		 */
		अगर (wasted > num_possible_cpus() / 3)
			जारी;

		/* and then करोn't consume more memory */
		अगर (allocs > last_allocs)
			अवरोध;
		last_allocs = allocs;
		best_upa = upa;
	पूर्ण
	upa = best_upa;

	/* allocate and fill alloc_info */
	क्रम (group = 0; group < nr_groups; group++)
		nr_units += roundup(group_cnt[group], upa);

	ai = pcpu_alloc_alloc_info(nr_groups, nr_units);
	अगर (!ai)
		वापस ERR_PTR(-ENOMEM);
	cpu_map = ai->groups[0].cpu_map;

	क्रम (group = 0; group < nr_groups; group++) अणु
		ai->groups[group].cpu_map = cpu_map;
		cpu_map += roundup(group_cnt[group], upa);
	पूर्ण

	ai->अटल_size = अटल_size;
	ai->reserved_size = reserved_size;
	ai->dyn_size = dyn_size;
	ai->unit_size = alloc_size / upa;
	ai->atom_size = atom_size;
	ai->alloc_size = alloc_size;

	क्रम (group = 0, unit = 0; group < nr_groups; group++) अणु
		काष्ठा pcpu_group_info *gi = &ai->groups[group];

		/*
		 * Initialize base_offset as अगर all groups are located
		 * back-to-back.  The caller should update this to
		 * reflect actual allocation.
		 */
		gi->base_offset = unit * ai->unit_size;

		क्रम_each_possible_cpu(cpu)
			अगर (group_map[cpu] == group)
				gi->cpu_map[gi->nr_units++] = cpu;
		gi->nr_units = roundup(gi->nr_units, upa);
		unit += gi->nr_units;
	पूर्ण
	BUG_ON(unit != nr_units);

	वापस ai;
पूर्ण
#पूर्ण_अगर /* BUILD_EMBED_FIRST_CHUNK || BUILD_PAGE_FIRST_CHUNK */

#अगर defined(BUILD_EMBED_FIRST_CHUNK)
/**
 * pcpu_embed_first_chunk - embed the first percpu chunk पूर्णांकo booपंचांगem
 * @reserved_size: the size of reserved percpu area in bytes
 * @dyn_size: minimum मुक्त size क्रम dynamic allocation in bytes
 * @atom_size: allocation atom size
 * @cpu_distance_fn: callback to determine distance between cpus, optional
 * @alloc_fn: function to allocate percpu page
 * @मुक्त_fn: function to मुक्त percpu page
 *
 * This is a helper to ease setting up embedded first percpu chunk and
 * can be called where pcpu_setup_first_chunk() is expected.
 *
 * If this function is used to setup the first chunk, it is allocated
 * by calling @alloc_fn and used as-is without being mapped पूर्णांकo
 * vदो_स्मृति area.  Allocations are always whole multiples of @atom_size
 * aligned to @atom_size.
 *
 * This enables the first chunk to piggy back on the linear physical
 * mapping which often uses larger page size.  Please note that this
 * can result in very sparse cpu->unit mapping on NUMA machines thus
 * requiring large vदो_स्मृति address space.  Don't use this allocator अगर
 * vदो_स्मृति space is not orders of magnitude larger than distances
 * between node memory addresses (ie. 32bit NUMA machines).
 *
 * @dyn_size specअगरies the minimum dynamic area size.
 *
 * If the needed size is smaller than the minimum or specअगरied unit
 * size, the leftover is वापसed using @मुक्त_fn.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init pcpu_embed_first_chunk(माप_प्रकार reserved_size, माप_प्रकार dyn_size,
				  माप_प्रकार atom_size,
				  pcpu_fc_cpu_distance_fn_t cpu_distance_fn,
				  pcpu_fc_alloc_fn_t alloc_fn,
				  pcpu_fc_मुक्त_fn_t मुक्त_fn)
अणु
	व्योम *base = (व्योम *)अच_दीर्घ_उच्च;
	व्योम **areas = शून्य;
	काष्ठा pcpu_alloc_info *ai;
	माप_प्रकार size_sum, areas_size;
	अचिन्हित दीर्घ max_distance;
	पूर्णांक group, i, highest_group, rc = 0;

	ai = pcpu_build_alloc_info(reserved_size, dyn_size, atom_size,
				   cpu_distance_fn);
	अगर (IS_ERR(ai))
		वापस PTR_ERR(ai);

	size_sum = ai->अटल_size + ai->reserved_size + ai->dyn_size;
	areas_size = PFN_ALIGN(ai->nr_groups * माप(व्योम *));

	areas = memblock_alloc(areas_size, SMP_CACHE_BYTES);
	अगर (!areas) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	/* allocate, copy and determine base address & max_distance */
	highest_group = 0;
	क्रम (group = 0; group < ai->nr_groups; group++) अणु
		काष्ठा pcpu_group_info *gi = &ai->groups[group];
		अचिन्हित पूर्णांक cpu = NR_CPUS;
		व्योम *ptr;

		क्रम (i = 0; i < gi->nr_units && cpu == NR_CPUS; i++)
			cpu = gi->cpu_map[i];
		BUG_ON(cpu == NR_CPUS);

		/* allocate space क्रम the whole group */
		ptr = alloc_fn(cpu, gi->nr_units * ai->unit_size, atom_size);
		अगर (!ptr) अणु
			rc = -ENOMEM;
			जाओ out_मुक्त_areas;
		पूर्ण
		/* kmemleak tracks the percpu allocations separately */
		kmemleak_मुक्त(ptr);
		areas[group] = ptr;

		base = min(ptr, base);
		अगर (ptr > areas[highest_group])
			highest_group = group;
	पूर्ण
	max_distance = areas[highest_group] - base;
	max_distance += ai->unit_size * ai->groups[highest_group].nr_units;

	/* warn अगर maximum distance is further than 75% of vदो_स्मृति space */
	अगर (max_distance > VMALLOC_TOTAL * 3 / 4) अणु
		pr_warn("max_distance=0x%lx too large for vmalloc space 0x%lx\n",
				max_distance, VMALLOC_TOTAL);
#अगर_घोषित CONFIG_NEED_PER_CPU_PAGE_FIRST_CHUNK
		/* and fail अगर we have fallback */
		rc = -EINVAL;
		जाओ out_मुक्त_areas;
#पूर्ण_अगर
	पूर्ण

	/*
	 * Copy data and मुक्त unused parts.  This should happen after all
	 * allocations are complete; otherwise, we may end up with
	 * overlapping groups.
	 */
	क्रम (group = 0; group < ai->nr_groups; group++) अणु
		काष्ठा pcpu_group_info *gi = &ai->groups[group];
		व्योम *ptr = areas[group];

		क्रम (i = 0; i < gi->nr_units; i++, ptr += ai->unit_size) अणु
			अगर (gi->cpu_map[i] == NR_CPUS) अणु
				/* unused unit, मुक्त whole */
				मुक्त_fn(ptr, ai->unit_size);
				जारी;
			पूर्ण
			/* copy and वापस the unused part */
			स_नकल(ptr, __per_cpu_load, ai->अटल_size);
			मुक्त_fn(ptr + size_sum, ai->unit_size - size_sum);
		पूर्ण
	पूर्ण

	/* base address is now known, determine group base offsets */
	क्रम (group = 0; group < ai->nr_groups; group++) अणु
		ai->groups[group].base_offset = areas[group] - base;
	पूर्ण

	pr_info("Embedded %zu pages/cpu s%zu r%zu d%zu u%zu\n",
		PFN_DOWN(size_sum), ai->अटल_size, ai->reserved_size,
		ai->dyn_size, ai->unit_size);

	pcpu_setup_first_chunk(ai, base);
	जाओ out_मुक्त;

out_मुक्त_areas:
	क्रम (group = 0; group < ai->nr_groups; group++)
		अगर (areas[group])
			मुक्त_fn(areas[group],
				ai->groups[group].nr_units * ai->unit_size);
out_मुक्त:
	pcpu_मुक्त_alloc_info(ai);
	अगर (areas)
		memblock_मुक्त_early(__pa(areas), areas_size);
	वापस rc;
पूर्ण
#पूर्ण_अगर /* BUILD_EMBED_FIRST_CHUNK */

#अगर_घोषित BUILD_PAGE_FIRST_CHUNK
/**
 * pcpu_page_first_chunk - map the first chunk using PAGE_SIZE pages
 * @reserved_size: the size of reserved percpu area in bytes
 * @alloc_fn: function to allocate percpu page, always called with PAGE_SIZE
 * @मुक्त_fn: function to मुक्त percpu page, always called with PAGE_SIZE
 * @populate_pte_fn: function to populate pte
 *
 * This is a helper to ease setting up page-remapped first percpu
 * chunk and can be called where pcpu_setup_first_chunk() is expected.
 *
 * This is the basic allocator.  Static percpu area is allocated
 * page-by-page पूर्णांकo vदो_स्मृति area.
 *
 * RETURNS:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init pcpu_page_first_chunk(माप_प्रकार reserved_size,
				 pcpu_fc_alloc_fn_t alloc_fn,
				 pcpu_fc_मुक्त_fn_t मुक्त_fn,
				 pcpu_fc_populate_pte_fn_t populate_pte_fn)
अणु
	अटल काष्ठा vm_काष्ठा vm;
	काष्ठा pcpu_alloc_info *ai;
	अक्षर psize_str[16];
	पूर्णांक unit_pages;
	माप_प्रकार pages_size;
	काष्ठा page **pages;
	पूर्णांक unit, i, j, rc = 0;
	पूर्णांक upa;
	पूर्णांक nr_g0_units;

	snम_लिखो(psize_str, माप(psize_str), "%luK", PAGE_SIZE >> 10);

	ai = pcpu_build_alloc_info(reserved_size, 0, PAGE_SIZE, शून्य);
	अगर (IS_ERR(ai))
		वापस PTR_ERR(ai);
	BUG_ON(ai->nr_groups != 1);
	upa = ai->alloc_size/ai->unit_size;
	nr_g0_units = roundup(num_possible_cpus(), upa);
	अगर (WARN_ON(ai->groups[0].nr_units != nr_g0_units)) अणु
		pcpu_मुक्त_alloc_info(ai);
		वापस -EINVAL;
	पूर्ण

	unit_pages = ai->unit_size >> PAGE_SHIFT;

	/* unaligned allocations can't be मुक्तd, round up to page size */
	pages_size = PFN_ALIGN(unit_pages * num_possible_cpus() *
			       माप(pages[0]));
	pages = memblock_alloc(pages_size, SMP_CACHE_BYTES);
	अगर (!pages)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      pages_size);

	/* allocate pages */
	j = 0;
	क्रम (unit = 0; unit < num_possible_cpus(); unit++) अणु
		अचिन्हित पूर्णांक cpu = ai->groups[0].cpu_map[unit];
		क्रम (i = 0; i < unit_pages; i++) अणु
			व्योम *ptr;

			ptr = alloc_fn(cpu, PAGE_SIZE, PAGE_SIZE);
			अगर (!ptr) अणु
				pr_warn("failed to allocate %s page for cpu%u\n",
						psize_str, cpu);
				जाओ enomem;
			पूर्ण
			/* kmemleak tracks the percpu allocations separately */
			kmemleak_मुक्त(ptr);
			pages[j++] = virt_to_page(ptr);
		पूर्ण
	पूर्ण

	/* allocate vm area, map the pages and copy अटल data */
	vm.flags = VM_ALLOC;
	vm.size = num_possible_cpus() * ai->unit_size;
	vm_area_रेजिस्टर_early(&vm, PAGE_SIZE);

	क्रम (unit = 0; unit < num_possible_cpus(); unit++) अणु
		अचिन्हित दीर्घ unit_addr =
			(अचिन्हित दीर्घ)vm.addr + unit * ai->unit_size;

		क्रम (i = 0; i < unit_pages; i++)
			populate_pte_fn(unit_addr + (i << PAGE_SHIFT));

		/* pte alपढ़ोy populated, the following shouldn't fail */
		rc = __pcpu_map_pages(unit_addr, &pages[unit * unit_pages],
				      unit_pages);
		अगर (rc < 0)
			panic("failed to map percpu area, err=%d\n", rc);

		/*
		 * FIXME: Archs with भव cache should flush local
		 * cache क्रम the linear mapping here - something
		 * equivalent to flush_cache_vmap() on the local cpu.
		 * flush_cache_vmap() can't be used as most supporting
		 * data काष्ठाures are not set up yet.
		 */

		/* copy अटल data */
		स_नकल((व्योम *)unit_addr, __per_cpu_load, ai->अटल_size);
	पूर्ण

	/* we're पढ़ोy, commit */
	pr_info("%d %s pages/cpu s%zu r%zu d%zu\n",
		unit_pages, psize_str, ai->अटल_size,
		ai->reserved_size, ai->dyn_size);

	pcpu_setup_first_chunk(ai, vm.addr);
	जाओ out_मुक्त_ar;

enomem:
	जबतक (--j >= 0)
		मुक्त_fn(page_address(pages[j]), PAGE_SIZE);
	rc = -ENOMEM;
out_मुक्त_ar:
	memblock_मुक्त_early(__pa(pages), pages_size);
	pcpu_मुक्त_alloc_info(ai);
	वापस rc;
पूर्ण
#पूर्ण_अगर /* BUILD_PAGE_FIRST_CHUNK */

#अगर_अघोषित	CONFIG_HAVE_SETUP_PER_CPU_AREA
/*
 * Generic SMP percpu area setup.
 *
 * The embedding helper is used because its behavior बंदly resembles
 * the original non-dynamic generic percpu area setup.  This is
 * important because many archs have addressing restrictions and might
 * fail अगर the percpu area is located far away from the previous
 * location.  As an added bonus, in non-NUMA हालs, embedding is
 * generally a good idea TLB-wise because percpu area can piggy back
 * on the physical linear memory mapping which uses large page
 * mappings on applicable archs.
 */
अचिन्हित दीर्घ __per_cpu_offset[NR_CPUS] __पढ़ो_mostly;
EXPORT_SYMBOL(__per_cpu_offset);

अटल व्योम * __init pcpu_dfl_fc_alloc(अचिन्हित पूर्णांक cpu, माप_प्रकार size,
				       माप_प्रकार align)
अणु
	वापस  memblock_alloc_from(size, align, __pa(MAX_DMA_ADDRESS));
पूर्ण

अटल व्योम __init pcpu_dfl_fc_मुक्त(व्योम *ptr, माप_प्रकार size)
अणु
	memblock_मुक्त_early(__pa(ptr), size);
पूर्ण

व्योम __init setup_per_cpu_areas(व्योम)
अणु
	अचिन्हित दीर्घ delta;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक rc;

	/*
	 * Always reserve area क्रम module percpu variables.  That's
	 * what the legacy allocator did.
	 */
	rc = pcpu_embed_first_chunk(PERCPU_MODULE_RESERVE,
				    PERCPU_DYNAMIC_RESERVE, PAGE_SIZE, शून्य,
				    pcpu_dfl_fc_alloc, pcpu_dfl_fc_मुक्त);
	अगर (rc < 0)
		panic("Failed to initialize percpu areas.");

	delta = (अचिन्हित दीर्घ)pcpu_base_addr - (अचिन्हित दीर्घ)__per_cpu_start;
	क्रम_each_possible_cpu(cpu)
		__per_cpu_offset[cpu] = delta + pcpu_unit_offsets[cpu];
पूर्ण
#पूर्ण_अगर	/* CONFIG_HAVE_SETUP_PER_CPU_AREA */

#अन्यथा	/* CONFIG_SMP */

/*
 * UP percpu area setup.
 *
 * UP always uses km-based percpu allocator with identity mapping.
 * Static percpu variables are indistinguishable from the usual अटल
 * variables and करोn't require any special preparation.
 */
व्योम __init setup_per_cpu_areas(व्योम)
अणु
	स्थिर माप_प्रकार unit_size =
		roundup_घात_of_two(max_t(माप_प्रकार, PCPU_MIN_UNIT_SIZE,
					 PERCPU_DYNAMIC_RESERVE));
	काष्ठा pcpu_alloc_info *ai;
	व्योम *fc;

	ai = pcpu_alloc_alloc_info(1, 1);
	fc = memblock_alloc_from(unit_size, PAGE_SIZE, __pa(MAX_DMA_ADDRESS));
	अगर (!ai || !fc)
		panic("Failed to allocate memory for percpu areas.");
	/* kmemleak tracks the percpu allocations separately */
	kmemleak_मुक्त(fc);

	ai->dyn_size = unit_size;
	ai->unit_size = unit_size;
	ai->atom_size = unit_size;
	ai->alloc_size = unit_size;
	ai->groups[0].nr_units = 1;
	ai->groups[0].cpu_map[0] = 0;

	pcpu_setup_first_chunk(ai, fc);
	pcpu_मुक्त_alloc_info(ai);
पूर्ण

#पूर्ण_अगर	/* CONFIG_SMP */

/*
 * pcpu_nr_pages - calculate total number of populated backing pages
 *
 * This reflects the number of pages populated to back chunks.  Metadata is
 * excluded in the number exposed in meminfo as the number of backing pages
 * scales with the number of cpus and can quickly outweigh the memory used क्रम
 * metadata.  It also keeps this calculation nice and simple.
 *
 * RETURNS:
 * Total number of populated backing pages in use by the allocator.
 */
अचिन्हित दीर्घ pcpu_nr_pages(व्योम)
अणु
	वापस pcpu_nr_populated * pcpu_nr_units;
पूर्ण

/*
 * Percpu allocator is initialized early during boot when neither slab or
 * workqueue is available.  Plug async management until everything is up
 * and running.
 */
अटल पूर्णांक __init percpu_enable_async(व्योम)
अणु
	pcpu_async_enabled = true;
	वापस 0;
पूर्ण
subsys_initcall(percpu_enable_async);
