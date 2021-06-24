<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MM_PERCPU_INTERNAL_H
#घोषणा _MM_PERCPU_INTERNAL_H

#समावेश <linux/types.h>
#समावेश <linux/percpu.h>

/*
 * There are two chunk types: root and memcg-aware.
 * Chunks of each type have separate slots list.
 *
 * Memcg-aware chunks have an attached vector of obj_cgroup poपूर्णांकers, which is
 * used to store memcg membership data of a percpu object.  Obj_cgroups are
 * ref-counted poपूर्णांकers to a memory cgroup with an ability to चयन dynamically
 * to the parent memory cgroup.  This allows to reclaim a deleted memory cgroup
 * without reclaiming of all outstanding objects, which hold a reference at it.
 */
क्रमागत pcpu_chunk_type अणु
	PCPU_CHUNK_ROOT,
#अगर_घोषित CONFIG_MEMCG_KMEM
	PCPU_CHUNK_MEMCG,
#पूर्ण_अगर
	PCPU_NR_CHUNK_TYPES,
	PCPU_FAIL_ALLOC = PCPU_NR_CHUNK_TYPES
पूर्ण;

/*
 * pcpu_block_md is the metadata block काष्ठा.
 * Each chunk's biपंचांगap is split पूर्णांकo a number of full blocks.
 * All units are in terms of bits.
 *
 * The scan hपूर्णांक is the largest known contiguous area beक्रमe the contig hपूर्णांक.
 * It is not necessarily the actual largest contig hपूर्णांक though.  There is an
 * invariant that the scan_hपूर्णांक_start > contig_hपूर्णांक_start अगरf
 * scan_hपूर्णांक == contig_hपूर्णांक.  This is necessary because when scanning क्रमward,
 * we करोn't know अगर a new contig hपूर्णांक would be better than the current one.
 */
काष्ठा pcpu_block_md अणु
	पूर्णांक			scan_hपूर्णांक;	/* scan hपूर्णांक क्रम block */
	पूर्णांक			scan_hपूर्णांक_start; /* block relative starting
						    position of the scan hपूर्णांक */
	पूर्णांक                     contig_hपूर्णांक;    /* contig hपूर्णांक क्रम block */
	पूर्णांक                     contig_hपूर्णांक_start; /* block relative starting
						      position of the contig hपूर्णांक */
	पूर्णांक                     left_मुक्त;      /* size of मुक्त space aदीर्घ
						   the left side of the block */
	पूर्णांक                     right_मुक्त;     /* size of मुक्त space aदीर्घ
						   the right side of the block */
	पूर्णांक                     first_मुक्त;     /* block position of first मुक्त */
	पूर्णांक			nr_bits;	/* total bits responsible क्रम */
पूर्ण;

काष्ठा pcpu_chunk अणु
#अगर_घोषित CONFIG_PERCPU_STATS
	पूर्णांक			nr_alloc;	/* # of allocations */
	माप_प्रकार			max_alloc_size; /* largest allocation size */
#पूर्ण_अगर

	काष्ठा list_head	list;		/* linked to pcpu_slot lists */
	पूर्णांक			मुक्त_bytes;	/* मुक्त bytes in the chunk */
	काष्ठा pcpu_block_md	chunk_md;
	व्योम			*base_addr;	/* base address of this chunk */

	अचिन्हित दीर्घ		*alloc_map;	/* allocation map */
	अचिन्हित दीर्घ		*bound_map;	/* boundary map */
	काष्ठा pcpu_block_md	*md_blocks;	/* metadata blocks */

	व्योम			*data;		/* chunk data */
	bool			immutable;	/* no [de]population allowed */
	पूर्णांक			start_offset;	/* the overlap with the previous
						   region to have a page aligned
						   base_addr */
	पूर्णांक			end_offset;	/* additional area required to
						   have the region end page
						   aligned */
#अगर_घोषित CONFIG_MEMCG_KMEM
	काष्ठा obj_cgroup	**obj_cgroups;	/* vector of object cgroups */
#पूर्ण_अगर

	पूर्णांक			nr_pages;	/* # of pages served by this chunk */
	पूर्णांक			nr_populated;	/* # of populated pages */
	पूर्णांक                     nr_empty_pop_pages; /* # of empty populated pages */
	अचिन्हित दीर्घ		populated[];	/* populated biपंचांगap */
पूर्ण;

बाह्य spinlock_t pcpu_lock;

बाह्य काष्ठा list_head *pcpu_chunk_lists;
बाह्य पूर्णांक pcpu_nr_slots;
बाह्य पूर्णांक pcpu_nr_empty_pop_pages[];

बाह्य काष्ठा pcpu_chunk *pcpu_first_chunk;
बाह्य काष्ठा pcpu_chunk *pcpu_reserved_chunk;

/**
 * pcpu_chunk_nr_blocks - converts nr_pages to # of md_blocks
 * @chunk: chunk of पूर्णांकerest
 *
 * This conversion is from the number of physical pages that the chunk
 * serves to the number of biपंचांगap blocks used.
 */
अटल अंतरभूत पूर्णांक pcpu_chunk_nr_blocks(काष्ठा pcpu_chunk *chunk)
अणु
	वापस chunk->nr_pages * PAGE_SIZE / PCPU_BITMAP_BLOCK_SIZE;
पूर्ण

/**
 * pcpu_nr_pages_to_map_bits - converts the pages to size of biपंचांगap
 * @pages: number of physical pages
 *
 * This conversion is from physical pages to the number of bits
 * required in the biपंचांगap.
 */
अटल अंतरभूत पूर्णांक pcpu_nr_pages_to_map_bits(पूर्णांक pages)
अणु
	वापस pages * PAGE_SIZE / PCPU_MIN_ALLOC_SIZE;
पूर्ण

/**
 * pcpu_chunk_map_bits - helper to convert nr_pages to size of biपंचांगap
 * @chunk: chunk of पूर्णांकerest
 *
 * This conversion is from the number of physical pages that the chunk
 * serves to the number of bits in the biपंचांगap.
 */
अटल अंतरभूत पूर्णांक pcpu_chunk_map_bits(काष्ठा pcpu_chunk *chunk)
अणु
	वापस pcpu_nr_pages_to_map_bits(chunk->nr_pages);
पूर्ण

#अगर_घोषित CONFIG_MEMCG_KMEM
अटल अंतरभूत क्रमागत pcpu_chunk_type pcpu_chunk_type(काष्ठा pcpu_chunk *chunk)
अणु
	अगर (chunk->obj_cgroups)
		वापस PCPU_CHUNK_MEMCG;
	वापस PCPU_CHUNK_ROOT;
पूर्ण

अटल अंतरभूत bool pcpu_is_memcg_chunk(क्रमागत pcpu_chunk_type chunk_type)
अणु
	वापस chunk_type == PCPU_CHUNK_MEMCG;
पूर्ण

#अन्यथा
अटल अंतरभूत क्रमागत pcpu_chunk_type pcpu_chunk_type(काष्ठा pcpu_chunk *chunk)
अणु
	वापस PCPU_CHUNK_ROOT;
पूर्ण

अटल अंतरभूत bool pcpu_is_memcg_chunk(क्रमागत pcpu_chunk_type chunk_type)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा list_head *pcpu_chunk_list(क्रमागत pcpu_chunk_type chunk_type)
अणु
	वापस &pcpu_chunk_lists[pcpu_nr_slots *
				 pcpu_is_memcg_chunk(chunk_type)];
पूर्ण

#अगर_घोषित CONFIG_PERCPU_STATS

#समावेश <linux/spinlock.h>

काष्ठा percpu_stats अणु
	u64 nr_alloc;		/* lअगरeसमय # of allocations */
	u64 nr_dealloc;		/* lअगरeसमय # of deallocations */
	u64 nr_cur_alloc;	/* current # of allocations */
	u64 nr_max_alloc;	/* max # of live allocations */
	u32 nr_chunks;		/* current # of live chunks */
	u32 nr_max_chunks;	/* max # of live chunks */
	माप_प्रकार min_alloc_size;	/* min allocation size */
	माप_प्रकार max_alloc_size;	/* max allocation size */
पूर्ण;

बाह्य काष्ठा percpu_stats pcpu_stats;
बाह्य काष्ठा pcpu_alloc_info pcpu_stats_ai;

/*
 * For debug purposes. We करोn't care about the flexible array.
 */
अटल अंतरभूत व्योम pcpu_stats_save_ai(स्थिर काष्ठा pcpu_alloc_info *ai)
अणु
	स_नकल(&pcpu_stats_ai, ai, माप(काष्ठा pcpu_alloc_info));

	/* initialize min_alloc_size to unit_size */
	pcpu_stats.min_alloc_size = pcpu_stats_ai.unit_size;
पूर्ण

/*
 * pcpu_stats_area_alloc - increment area allocation stats
 * @chunk: the location of the area being allocated
 * @size: size of area to allocate in bytes
 *
 * CONTEXT:
 * pcpu_lock.
 */
अटल अंतरभूत व्योम pcpu_stats_area_alloc(काष्ठा pcpu_chunk *chunk, माप_प्रकार size)
अणु
	lockdep_निश्चित_held(&pcpu_lock);

	pcpu_stats.nr_alloc++;
	pcpu_stats.nr_cur_alloc++;
	pcpu_stats.nr_max_alloc =
		max(pcpu_stats.nr_max_alloc, pcpu_stats.nr_cur_alloc);
	pcpu_stats.min_alloc_size =
		min(pcpu_stats.min_alloc_size, size);
	pcpu_stats.max_alloc_size =
		max(pcpu_stats.max_alloc_size, size);

	chunk->nr_alloc++;
	chunk->max_alloc_size = max(chunk->max_alloc_size, size);
पूर्ण

/*
 * pcpu_stats_area_dealloc - decrement allocation stats
 * @chunk: the location of the area being deallocated
 *
 * CONTEXT:
 * pcpu_lock.
 */
अटल अंतरभूत व्योम pcpu_stats_area_dealloc(काष्ठा pcpu_chunk *chunk)
अणु
	lockdep_निश्चित_held(&pcpu_lock);

	pcpu_stats.nr_dealloc++;
	pcpu_stats.nr_cur_alloc--;

	chunk->nr_alloc--;
पूर्ण

/*
 * pcpu_stats_chunk_alloc - increment chunk stats
 */
अटल अंतरभूत व्योम pcpu_stats_chunk_alloc(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&pcpu_lock, flags);

	pcpu_stats.nr_chunks++;
	pcpu_stats.nr_max_chunks =
		max(pcpu_stats.nr_max_chunks, pcpu_stats.nr_chunks);

	spin_unlock_irqrestore(&pcpu_lock, flags);
पूर्ण

/*
 * pcpu_stats_chunk_dealloc - decrement chunk stats
 */
अटल अंतरभूत व्योम pcpu_stats_chunk_dealloc(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&pcpu_lock, flags);

	pcpu_stats.nr_chunks--;

	spin_unlock_irqrestore(&pcpu_lock, flags);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम pcpu_stats_save_ai(स्थिर काष्ठा pcpu_alloc_info *ai)
अणु
पूर्ण

अटल अंतरभूत व्योम pcpu_stats_area_alloc(काष्ठा pcpu_chunk *chunk, माप_प्रकार size)
अणु
पूर्ण

अटल अंतरभूत व्योम pcpu_stats_area_dealloc(काष्ठा pcpu_chunk *chunk)
अणु
पूर्ण

अटल अंतरभूत व्योम pcpu_stats_chunk_alloc(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम pcpu_stats_chunk_dealloc(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* !CONFIG_PERCPU_STATS */

#पूर्ण_अगर
