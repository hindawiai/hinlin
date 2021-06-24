<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _LINUX_MEMBLOCK_H
#घोषणा _LINUX_MEMBLOCK_H
#अगर_घोषित __KERNEL__

/*
 * Logical memory blocks.
 *
 * Copyright (C) 2001 Peter Bergner, IBM Corp.
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <यंत्र/dma.h>

बाह्य अचिन्हित दीर्घ max_low_pfn;
बाह्य अचिन्हित दीर्घ min_low_pfn;

/*
 * highest page
 */
बाह्य अचिन्हित दीर्घ max_pfn;
/*
 * highest possible page
 */
बाह्य अचिन्हित दीर्घ दीर्घ max_possible_pfn;

/**
 * क्रमागत memblock_flags - definition of memory region attributes
 * @MEMBLOCK_NONE: no special request
 * @MEMBLOCK_HOTPLUG: hotpluggable region
 * @MEMBLOCK_MIRROR: mirrored region
 * @MEMBLOCK_NOMAP: करोn't add to kernel direct mapping
 */
क्रमागत memblock_flags अणु
	MEMBLOCK_NONE		= 0x0,	/* No special request */
	MEMBLOCK_HOTPLUG	= 0x1,	/* hotpluggable region */
	MEMBLOCK_MIRROR		= 0x2,	/* mirrored region */
	MEMBLOCK_NOMAP		= 0x4,	/* करोn't add to kernel direct mapping */
पूर्ण;

/**
 * काष्ठा memblock_region - represents a memory region
 * @base: base address of the region
 * @size: size of the region
 * @flags: memory region attributes
 * @nid: NUMA node id
 */
काष्ठा memblock_region अणु
	phys_addr_t base;
	phys_addr_t size;
	क्रमागत memblock_flags flags;
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	पूर्णांक nid;
#पूर्ण_अगर
पूर्ण;

/**
 * काष्ठा memblock_type - collection of memory regions of certain type
 * @cnt: number of regions
 * @max: size of the allocated array
 * @total_size: size of all regions
 * @regions: array of regions
 * @name: the memory type symbolic name
 */
काष्ठा memblock_type अणु
	अचिन्हित दीर्घ cnt;
	अचिन्हित दीर्घ max;
	phys_addr_t total_size;
	काष्ठा memblock_region *regions;
	अक्षर *name;
पूर्ण;

/**
 * काष्ठा memblock - memblock allocator metadata
 * @bottom_up: is bottom up direction?
 * @current_limit: physical address of the current allocation limit
 * @memory: usable memory regions
 * @reserved: reserved memory regions
 */
काष्ठा memblock अणु
	bool bottom_up;  /* is bottom up direction? */
	phys_addr_t current_limit;
	काष्ठा memblock_type memory;
	काष्ठा memblock_type reserved;
पूर्ण;

बाह्य काष्ठा memblock memblock;

#अगर_अघोषित CONFIG_ARCH_KEEP_MEMBLOCK
#घोषणा __init_memblock __meminit
#घोषणा __initdata_memblock __meminitdata
व्योम memblock_discard(व्योम);
#अन्यथा
#घोषणा __init_memblock
#घोषणा __initdata_memblock
अटल अंतरभूत व्योम memblock_discard(व्योम) अणुपूर्ण
#पूर्ण_अगर

phys_addr_t memblock_find_in_range(phys_addr_t start, phys_addr_t end,
				   phys_addr_t size, phys_addr_t align);
व्योम memblock_allow_resize(व्योम);
पूर्णांक memblock_add_node(phys_addr_t base, phys_addr_t size, पूर्णांक nid);
पूर्णांक memblock_add(phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_हटाओ(phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_मुक्त(phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_reserve(phys_addr_t base, phys_addr_t size);
#अगर_घोषित CONFIG_HAVE_MEMBLOCK_PHYS_MAP
पूर्णांक memblock_physmem_add(phys_addr_t base, phys_addr_t size);
#पूर्ण_अगर
व्योम memblock_trim_memory(phys_addr_t align);
bool memblock_overlaps_region(काष्ठा memblock_type *type,
			      phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_mark_hotplug(phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_clear_hotplug(phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_mark_mirror(phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_mark_nomap(phys_addr_t base, phys_addr_t size);
पूर्णांक memblock_clear_nomap(phys_addr_t base, phys_addr_t size);

व्योम memblock_मुक्त_all(व्योम);
व्योम reset_node_managed_pages(pg_data_t *pgdat);
व्योम reset_all_zones_managed_pages(व्योम);

/* Low level functions */
व्योम __next_mem_range(u64 *idx, पूर्णांक nid, क्रमागत memblock_flags flags,
		      काष्ठा memblock_type *type_a,
		      काष्ठा memblock_type *type_b, phys_addr_t *out_start,
		      phys_addr_t *out_end, पूर्णांक *out_nid);

व्योम __next_mem_range_rev(u64 *idx, पूर्णांक nid, क्रमागत memblock_flags flags,
			  काष्ठा memblock_type *type_a,
			  काष्ठा memblock_type *type_b, phys_addr_t *out_start,
			  phys_addr_t *out_end, पूर्णांक *out_nid);

व्योम __memblock_मुक्त_late(phys_addr_t base, phys_addr_t size);

#अगर_घोषित CONFIG_HAVE_MEMBLOCK_PHYS_MAP
अटल अंतरभूत व्योम __next_physmem_range(u64 *idx, काष्ठा memblock_type *type,
					phys_addr_t *out_start,
					phys_addr_t *out_end)
अणु
	बाह्य काष्ठा memblock_type physmem;

	__next_mem_range(idx, NUMA_NO_NODE, MEMBLOCK_NONE, &physmem, type,
			 out_start, out_end, शून्य);
पूर्ण

/**
 * क्रम_each_physmem_range - iterate through physmem areas not included in type.
 * @i: u64 used as loop variable
 * @type: ptr to memblock_type which excludes from the iteration, can be %शून्य
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 */
#घोषणा क्रम_each_physmem_range(i, type, p_start, p_end)			\
	क्रम (i = 0, __next_physmem_range(&i, type, p_start, p_end);	\
	     i != (u64)ULदीर्घ_उच्च;					\
	     __next_physmem_range(&i, type, p_start, p_end))
#पूर्ण_अगर /* CONFIG_HAVE_MEMBLOCK_PHYS_MAP */

/**
 * __क्रम_each_mem_range - iterate through memblock areas from type_a and not
 * included in type_b. Or just type_a अगर type_b is शून्य.
 * @i: u64 used as loop variable
 * @type_a: ptr to memblock_type to iterate
 * @type_b: ptr to memblock_type which excludes from the iteration
 * @nid: node selector, %NUMA_NO_NODE क्रम all nodes
 * @flags: pick from blocks based on memory attributes
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 * @p_nid: ptr to पूर्णांक क्रम nid of the range, can be %शून्य
 */
#घोषणा __क्रम_each_mem_range(i, type_a, type_b, nid, flags,		\
			   p_start, p_end, p_nid)			\
	क्रम (i = 0, __next_mem_range(&i, nid, flags, type_a, type_b,	\
				     p_start, p_end, p_nid);		\
	     i != (u64)ULदीर्घ_उच्च;					\
	     __next_mem_range(&i, nid, flags, type_a, type_b,		\
			      p_start, p_end, p_nid))

/**
 * __क्रम_each_mem_range_rev - reverse iterate through memblock areas from
 * type_a and not included in type_b. Or just type_a अगर type_b is शून्य.
 * @i: u64 used as loop variable
 * @type_a: ptr to memblock_type to iterate
 * @type_b: ptr to memblock_type which excludes from the iteration
 * @nid: node selector, %NUMA_NO_NODE क्रम all nodes
 * @flags: pick from blocks based on memory attributes
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 * @p_nid: ptr to पूर्णांक क्रम nid of the range, can be %शून्य
 */
#घोषणा __क्रम_each_mem_range_rev(i, type_a, type_b, nid, flags,		\
				 p_start, p_end, p_nid)			\
	क्रम (i = (u64)ULदीर्घ_उच्च,					\
		     __next_mem_range_rev(&i, nid, flags, type_a, type_b, \
					  p_start, p_end, p_nid);	\
	     i != (u64)ULदीर्घ_उच्च;					\
	     __next_mem_range_rev(&i, nid, flags, type_a, type_b,	\
				  p_start, p_end, p_nid))

/**
 * क्रम_each_mem_range - iterate through memory areas.
 * @i: u64 used as loop variable
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 */
#घोषणा क्रम_each_mem_range(i, p_start, p_end) \
	__क्रम_each_mem_range(i, &memblock.memory, शून्य, NUMA_NO_NODE,	\
			     MEMBLOCK_NONE, p_start, p_end, शून्य)

/**
 * क्रम_each_mem_range_rev - reverse iterate through memblock areas from
 * type_a and not included in type_b. Or just type_a अगर type_b is शून्य.
 * @i: u64 used as loop variable
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 */
#घोषणा क्रम_each_mem_range_rev(i, p_start, p_end)			\
	__क्रम_each_mem_range_rev(i, &memblock.memory, शून्य, NUMA_NO_NODE, \
				 MEMBLOCK_NONE, p_start, p_end, शून्य)

/**
 * क्रम_each_reserved_mem_range - iterate over all reserved memblock areas
 * @i: u64 used as loop variable
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 *
 * Walks over reserved areas of memblock. Available as soon as memblock
 * is initialized.
 */
#घोषणा क्रम_each_reserved_mem_range(i, p_start, p_end)			\
	__क्रम_each_mem_range(i, &memblock.reserved, शून्य, NUMA_NO_NODE,	\
			     MEMBLOCK_NONE, p_start, p_end, शून्य)

अटल अंतरभूत bool memblock_is_hotpluggable(काष्ठा memblock_region *m)
अणु
	वापस m->flags & MEMBLOCK_HOTPLUG;
पूर्ण

अटल अंतरभूत bool memblock_is_mirror(काष्ठा memblock_region *m)
अणु
	वापस m->flags & MEMBLOCK_MIRROR;
पूर्ण

अटल अंतरभूत bool memblock_is_nomap(काष्ठा memblock_region *m)
अणु
	वापस m->flags & MEMBLOCK_NOMAP;
पूर्ण

पूर्णांक memblock_search_pfn_nid(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ *start_pfn,
			    अचिन्हित दीर्घ  *end_pfn);
व्योम __next_mem_pfn_range(पूर्णांक *idx, पूर्णांक nid, अचिन्हित दीर्घ *out_start_pfn,
			  अचिन्हित दीर्घ *out_end_pfn, पूर्णांक *out_nid);

/**
 * क्रम_each_mem_pfn_range - early memory pfn range iterator
 * @i: an पूर्णांकeger used as loop variable
 * @nid: node selector, %MAX_NUMNODES क्रम all nodes
 * @p_start: ptr to uदीर्घ क्रम start pfn of the range, can be %शून्य
 * @p_end: ptr to uदीर्घ क्रम end pfn of the range, can be %शून्य
 * @p_nid: ptr to पूर्णांक क्रम nid of the range, can be %शून्य
 *
 * Walks over configured memory ranges.
 */
#घोषणा क्रम_each_mem_pfn_range(i, nid, p_start, p_end, p_nid)		\
	क्रम (i = -1, __next_mem_pfn_range(&i, nid, p_start, p_end, p_nid); \
	     i >= 0; __next_mem_pfn_range(&i, nid, p_start, p_end, p_nid))

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
व्योम __next_mem_pfn_range_in_zone(u64 *idx, काष्ठा zone *zone,
				  अचिन्हित दीर्घ *out_spfn,
				  अचिन्हित दीर्घ *out_epfn);
/**
 * क्रम_each_मुक्त_mem_pfn_range_in_zone - iterate through zone specअगरic मुक्त
 * memblock areas
 * @i: u64 used as loop variable
 * @zone: zone in which all of the memory blocks reside
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 *
 * Walks over मुक्त (memory && !reserved) areas of memblock in a specअगरic
 * zone. Available once memblock and an empty zone is initialized. The मुख्य
 * assumption is that the zone start, end, and pgdat have been associated.
 * This way we can use the zone to determine NUMA node, and अगर a given part
 * of the memblock is valid क्रम the zone.
 */
#घोषणा क्रम_each_मुक्त_mem_pfn_range_in_zone(i, zone, p_start, p_end)	\
	क्रम (i = 0,							\
	     __next_mem_pfn_range_in_zone(&i, zone, p_start, p_end);	\
	     i != U64_MAX;					\
	     __next_mem_pfn_range_in_zone(&i, zone, p_start, p_end))

/**
 * क्रम_each_मुक्त_mem_pfn_range_in_zone_from - iterate through zone specअगरic
 * मुक्त memblock areas from a given poपूर्णांक
 * @i: u64 used as loop variable
 * @zone: zone in which all of the memory blocks reside
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 *
 * Walks over मुक्त (memory && !reserved) areas of memblock in a specअगरic
 * zone, continuing from current position. Available as soon as memblock is
 * initialized.
 */
#घोषणा क्रम_each_मुक्त_mem_pfn_range_in_zone_from(i, zone, p_start, p_end) \
	क्रम (; i != U64_MAX;					  \
	     __next_mem_pfn_range_in_zone(&i, zone, p_start, p_end))

पूर्णांक __init deferred_page_init_max_thपढ़ोs(स्थिर काष्ठा cpumask *node_cpumask);

#पूर्ण_अगर /* CONFIG_DEFERRED_STRUCT_PAGE_INIT */

/**
 * क्रम_each_मुक्त_mem_range - iterate through मुक्त memblock areas
 * @i: u64 used as loop variable
 * @nid: node selector, %NUMA_NO_NODE क्रम all nodes
 * @flags: pick from blocks based on memory attributes
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 * @p_nid: ptr to पूर्णांक क्रम nid of the range, can be %शून्य
 *
 * Walks over मुक्त (memory && !reserved) areas of memblock.  Available as
 * soon as memblock is initialized.
 */
#घोषणा क्रम_each_मुक्त_mem_range(i, nid, flags, p_start, p_end, p_nid)	\
	__क्रम_each_mem_range(i, &memblock.memory, &memblock.reserved,	\
			     nid, flags, p_start, p_end, p_nid)

/**
 * क्रम_each_मुक्त_mem_range_reverse - rev-iterate through मुक्त memblock areas
 * @i: u64 used as loop variable
 * @nid: node selector, %NUMA_NO_NODE क्रम all nodes
 * @flags: pick from blocks based on memory attributes
 * @p_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @p_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 * @p_nid: ptr to पूर्णांक क्रम nid of the range, can be %शून्य
 *
 * Walks over मुक्त (memory && !reserved) areas of memblock in reverse
 * order.  Available as soon as memblock is initialized.
 */
#घोषणा क्रम_each_मुक्त_mem_range_reverse(i, nid, flags, p_start, p_end,	\
					p_nid)				\
	__क्रम_each_mem_range_rev(i, &memblock.memory, &memblock.reserved, \
				 nid, flags, p_start, p_end, p_nid)

पूर्णांक memblock_set_node(phys_addr_t base, phys_addr_t size,
		      काष्ठा memblock_type *type, पूर्णांक nid);

#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
अटल अंतरभूत व्योम memblock_set_region_node(काष्ठा memblock_region *r, पूर्णांक nid)
अणु
	r->nid = nid;
पूर्ण

अटल अंतरभूत पूर्णांक memblock_get_region_node(स्थिर काष्ठा memblock_region *r)
अणु
	वापस r->nid;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम memblock_set_region_node(काष्ठा memblock_region *r, पूर्णांक nid)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक memblock_get_region_node(स्थिर काष्ठा memblock_region *r)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NEED_MULTIPLE_NODES */

/* Flags क्रम memblock allocation APIs */
#घोषणा MEMBLOCK_ALLOC_ANYWHERE	(~(phys_addr_t)0)
#घोषणा MEMBLOCK_ALLOC_ACCESSIBLE	0
#घोषणा MEMBLOCK_ALLOC_KASAN		1

/* We are using top करोwn, so it is safe to use 0 here */
#घोषणा MEMBLOCK_LOW_LIMIT 0

#अगर_अघोषित ARCH_LOW_ADDRESS_LIMIT
#घोषणा ARCH_LOW_ADDRESS_LIMIT  0xffffffffUL
#पूर्ण_अगर

phys_addr_t memblock_phys_alloc_range(phys_addr_t size, phys_addr_t align,
				      phys_addr_t start, phys_addr_t end);
phys_addr_t memblock_alloc_range_nid(phys_addr_t size,
				      phys_addr_t align, phys_addr_t start,
				      phys_addr_t end, पूर्णांक nid, bool exact_nid);
phys_addr_t memblock_phys_alloc_try_nid(phys_addr_t size, phys_addr_t align, पूर्णांक nid);

अटल अंतरभूत phys_addr_t memblock_phys_alloc(phys_addr_t size,
					      phys_addr_t align)
अणु
	वापस memblock_phys_alloc_range(size, align, 0,
					 MEMBLOCK_ALLOC_ACCESSIBLE);
पूर्ण

व्योम *memblock_alloc_exact_nid_raw(phys_addr_t size, phys_addr_t align,
				 phys_addr_t min_addr, phys_addr_t max_addr,
				 पूर्णांक nid);
व्योम *memblock_alloc_try_nid_raw(phys_addr_t size, phys_addr_t align,
				 phys_addr_t min_addr, phys_addr_t max_addr,
				 पूर्णांक nid);
व्योम *memblock_alloc_try_nid(phys_addr_t size, phys_addr_t align,
			     phys_addr_t min_addr, phys_addr_t max_addr,
			     पूर्णांक nid);

अटल __always_अंतरभूत व्योम *memblock_alloc(phys_addr_t size, phys_addr_t align)
अणु
	वापस memblock_alloc_try_nid(size, align, MEMBLOCK_LOW_LIMIT,
				      MEMBLOCK_ALLOC_ACCESSIBLE, NUMA_NO_NODE);
पूर्ण

अटल अंतरभूत व्योम *memblock_alloc_raw(phys_addr_t size,
					       phys_addr_t align)
अणु
	वापस memblock_alloc_try_nid_raw(size, align, MEMBLOCK_LOW_LIMIT,
					  MEMBLOCK_ALLOC_ACCESSIBLE,
					  NUMA_NO_NODE);
पूर्ण

अटल अंतरभूत व्योम *memblock_alloc_from(phys_addr_t size,
						phys_addr_t align,
						phys_addr_t min_addr)
अणु
	वापस memblock_alloc_try_nid(size, align, min_addr,
				      MEMBLOCK_ALLOC_ACCESSIBLE, NUMA_NO_NODE);
पूर्ण

अटल अंतरभूत व्योम *memblock_alloc_low(phys_addr_t size,
					       phys_addr_t align)
अणु
	वापस memblock_alloc_try_nid(size, align, MEMBLOCK_LOW_LIMIT,
				      ARCH_LOW_ADDRESS_LIMIT, NUMA_NO_NODE);
पूर्ण

अटल अंतरभूत व्योम *memblock_alloc_node(phys_addr_t size,
						phys_addr_t align, पूर्णांक nid)
अणु
	वापस memblock_alloc_try_nid(size, align, MEMBLOCK_LOW_LIMIT,
				      MEMBLOCK_ALLOC_ACCESSIBLE, nid);
पूर्ण

अटल अंतरभूत व्योम memblock_मुक्त_early(phys_addr_t base,
					      phys_addr_t size)
अणु
	memblock_मुक्त(base, size);
पूर्ण

अटल अंतरभूत व्योम memblock_मुक्त_early_nid(phys_addr_t base,
						  phys_addr_t size, पूर्णांक nid)
अणु
	memblock_मुक्त(base, size);
पूर्ण

अटल अंतरभूत व्योम memblock_मुक्त_late(phys_addr_t base, phys_addr_t size)
अणु
	__memblock_मुक्त_late(base, size);
पूर्ण

/*
 * Set the allocation direction to bottom-up or top-करोwn.
 */
अटल अंतरभूत __init_memblock व्योम memblock_set_bottom_up(bool enable)
अणु
	memblock.bottom_up = enable;
पूर्ण

/*
 * Check अगर the allocation direction is bottom-up or not.
 * अगर this is true, that said, memblock will allocate memory
 * in bottom-up direction.
 */
अटल अंतरभूत __init_memblock bool memblock_bottom_up(व्योम)
अणु
	वापस memblock.bottom_up;
पूर्ण

phys_addr_t memblock_phys_mem_size(व्योम);
phys_addr_t memblock_reserved_size(व्योम);
phys_addr_t memblock_start_of_DRAM(व्योम);
phys_addr_t memblock_end_of_DRAM(व्योम);
व्योम memblock_enक्रमce_memory_limit(phys_addr_t memory_limit);
व्योम memblock_cap_memory_range(phys_addr_t base, phys_addr_t size);
व्योम memblock_mem_limit_हटाओ_map(phys_addr_t limit);
bool memblock_is_memory(phys_addr_t addr);
bool memblock_is_map_memory(phys_addr_t addr);
bool memblock_is_region_memory(phys_addr_t base, phys_addr_t size);
bool memblock_is_reserved(phys_addr_t addr);
bool memblock_is_region_reserved(phys_addr_t base, phys_addr_t size);

व्योम memblock_dump_all(व्योम);

/**
 * memblock_set_current_limit - Set the current allocation limit to allow
 *                         limiting allocations to what is currently
 *                         accessible during boot
 * @limit: New limit value (physical address)
 */
व्योम memblock_set_current_limit(phys_addr_t limit);


phys_addr_t memblock_get_current_limit(व्योम);

/*
 * pfn conversion functions
 *
 * While the memory MEMBLOCKs should always be page aligned, the reserved
 * MEMBLOCKs may not be. This accessor attempt to provide a very clear
 * idea of what they वापस क्रम such non aligned MEMBLOCKs.
 */

/**
 * memblock_region_memory_base_pfn - get the lowest pfn of the memory region
 * @reg: memblock_region काष्ठाure
 *
 * Return: the lowest pfn पूर्णांकersecting with the memory region
 */
अटल अंतरभूत अचिन्हित दीर्घ memblock_region_memory_base_pfn(स्थिर काष्ठा memblock_region *reg)
अणु
	वापस PFN_UP(reg->base);
पूर्ण

/**
 * memblock_region_memory_end_pfn - get the end pfn of the memory region
 * @reg: memblock_region काष्ठाure
 *
 * Return: the end_pfn of the reserved region
 */
अटल अंतरभूत अचिन्हित दीर्घ memblock_region_memory_end_pfn(स्थिर काष्ठा memblock_region *reg)
अणु
	वापस PFN_DOWN(reg->base + reg->size);
पूर्ण

/**
 * memblock_region_reserved_base_pfn - get the lowest pfn of the reserved region
 * @reg: memblock_region काष्ठाure
 *
 * Return: the lowest pfn पूर्णांकersecting with the reserved region
 */
अटल अंतरभूत अचिन्हित दीर्घ memblock_region_reserved_base_pfn(स्थिर काष्ठा memblock_region *reg)
अणु
	वापस PFN_DOWN(reg->base);
पूर्ण

/**
 * memblock_region_reserved_end_pfn - get the end pfn of the reserved region
 * @reg: memblock_region काष्ठाure
 *
 * Return: the end_pfn of the reserved region
 */
अटल अंतरभूत अचिन्हित दीर्घ memblock_region_reserved_end_pfn(स्थिर काष्ठा memblock_region *reg)
अणु
	वापस PFN_UP(reg->base + reg->size);
पूर्ण

/**
 * क्रम_each_mem_region - itereate over memory regions
 * @region: loop variable
 */
#घोषणा क्रम_each_mem_region(region)					\
	क्रम (region = memblock.memory.regions;				\
	     region < (memblock.memory.regions + memblock.memory.cnt);	\
	     region++)

/**
 * क्रम_each_reserved_mem_region - itereate over reserved memory regions
 * @region: loop variable
 */
#घोषणा क्रम_each_reserved_mem_region(region)				\
	क्रम (region = memblock.reserved.regions;			\
	     region < (memblock.reserved.regions + memblock.reserved.cnt); \
	     region++)

बाह्य व्योम *alloc_large_प्रणाली_hash(स्थिर अक्षर *tablename,
				     अचिन्हित दीर्घ bucketsize,
				     अचिन्हित दीर्घ numentries,
				     पूर्णांक scale,
				     पूर्णांक flags,
				     अचिन्हित पूर्णांक *_hash_shअगरt,
				     अचिन्हित पूर्णांक *_hash_mask,
				     अचिन्हित दीर्घ low_limit,
				     अचिन्हित दीर्घ high_limit);

#घोषणा HASH_EARLY	0x00000001	/* Allocating during early boot? */
#घोषणा HASH_SMALL	0x00000002	/* sub-page allocation allowed, min
					 * shअगरt passed via *_hash_shअगरt */
#घोषणा HASH_ZERO	0x00000004	/* Zero allocated hash table */

/* Only NUMA needs hash distribution. 64bit NUMA architectures have
 * sufficient vदो_स्मृति space.
 */
#अगर_घोषित CONFIG_NUMA
#घोषणा HASHDIST_DEFAULT IS_ENABLED(CONFIG_64BIT)
बाह्य पूर्णांक hashdist;		/* Distribute hashes across NUMA nodes? */
#अन्यथा
#घोषणा hashdist (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMTEST
बाह्य व्योम early_memtest(phys_addr_t start, phys_addr_t end);
#अन्यथा
अटल अंतरभूत व्योम early_memtest(phys_addr_t start, phys_addr_t end)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _LINUX_MEMBLOCK_H */
