<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Procedures क्रम मुख्यtaining inक्रमmation about logical memory blocks.
 *
 * Peter Bergner, IBM Corp.	June 2001.
 * Copyright (C) 2001 Peter Bergner.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/poison.h>
#समावेश <linux/pfn.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/sections.h>
#समावेश <linux/पन.स>

#समावेश "internal.h"

#घोषणा INIT_MEMBLOCK_REGIONS			128
#घोषणा INIT_PHYSMEM_REGIONS			4

#अगर_अघोषित INIT_MEMBLOCK_RESERVED_REGIONS
# define INIT_MEMBLOCK_RESERVED_REGIONS		INIT_MEMBLOCK_REGIONS
#पूर्ण_अगर

/**
 * DOC: memblock overview
 *
 * Memblock is a method of managing memory regions during the early
 * boot period when the usual kernel memory allocators are not up and
 * running.
 *
 * Memblock views the प्रणाली memory as collections of contiguous
 * regions. There are several types of these collections:
 *
 * * ``memory`` - describes the physical memory available to the
 *   kernel; this may dअगरfer from the actual physical memory installed
 *   in the प्रणाली, क्रम instance when the memory is restricted with
 *   ``mem=`` command line parameter
 * * ``reserved`` - describes the regions that were allocated
 * * ``physmem`` - describes the actual physical memory available during
 *   boot regardless of the possible restrictions and memory hot(un)plug;
 *   the ``physmem`` type is only available on some architectures.
 *
 * Each region is represented by काष्ठा memblock_region that
 * defines the region extents, its attributes and NUMA node id on NUMA
 * प्रणालीs. Every memory type is described by the काष्ठा memblock_type
 * which contains an array of memory regions aदीर्घ with
 * the allocator metadata. The "memory" and "reserved" types are nicely
 * wrapped with काष्ठा memblock. This काष्ठाure is अटलally
 * initialized at build समय. The region arrays are initially sized to
 * %INIT_MEMBLOCK_REGIONS क्रम "memory" and %INIT_MEMBLOCK_RESERVED_REGIONS
 * क्रम "reserved". The region array क्रम "physmem" is initially sized to
 * %INIT_PHYSMEM_REGIONS.
 * The memblock_allow_resize() enables स्वतःmatic resizing of the region
 * arrays during addition of new regions. This feature should be used
 * with care so that memory allocated क्रम the region array will not
 * overlap with areas that should be reserved, क्रम example initrd.
 *
 * The early architecture setup should tell memblock what the physical
 * memory layout is by using memblock_add() or memblock_add_node()
 * functions. The first function करोes not assign the region to a NUMA
 * node and it is appropriate क्रम UMA प्रणालीs. Yet, it is possible to
 * use it on NUMA प्रणालीs as well and assign the region to a NUMA node
 * later in the setup process using memblock_set_node(). The
 * memblock_add_node() perक्रमms such an assignment directly.
 *
 * Once memblock is setup the memory can be allocated using one of the
 * API variants:
 *
 * * memblock_phys_alloc*() - these functions वापस the **physical**
 *   address of the allocated memory
 * * memblock_alloc*() - these functions वापस the **भव** address
 *   of the allocated memory.
 *
 * Note, that both API variants use implicit assumptions about allowed
 * memory ranges and the fallback methods. Consult the करोcumentation
 * of memblock_alloc_पूर्णांकernal() and memblock_alloc_range_nid()
 * functions क्रम more elaborate description.
 *
 * As the प्रणाली boot progresses, the architecture specअगरic mem_init()
 * function मुक्तs all the memory to the buddy page allocator.
 *
 * Unless an architecture enables %CONFIG_ARCH_KEEP_MEMBLOCK, the
 * memblock data काष्ठाures (except "physmem") will be discarded after the
 * प्रणाली initialization completes.
 */

#अगर_अघोषित CONFIG_NEED_MULTIPLE_NODES
काष्ठा pglist_data __refdata contig_page_data;
EXPORT_SYMBOL(contig_page_data);
#पूर्ण_अगर

अचिन्हित दीर्घ max_low_pfn;
अचिन्हित दीर्घ min_low_pfn;
अचिन्हित दीर्घ max_pfn;
अचिन्हित दीर्घ दीर्घ max_possible_pfn;

अटल काष्ठा memblock_region memblock_memory_init_regions[INIT_MEMBLOCK_REGIONS] __initdata_memblock;
अटल काष्ठा memblock_region memblock_reserved_init_regions[INIT_MEMBLOCK_RESERVED_REGIONS] __initdata_memblock;
#अगर_घोषित CONFIG_HAVE_MEMBLOCK_PHYS_MAP
अटल काष्ठा memblock_region memblock_physmem_init_regions[INIT_PHYSMEM_REGIONS];
#पूर्ण_अगर

काष्ठा memblock memblock __initdata_memblock = अणु
	.memory.regions		= memblock_memory_init_regions,
	.memory.cnt		= 1,	/* empty dummy entry */
	.memory.max		= INIT_MEMBLOCK_REGIONS,
	.memory.name		= "memory",

	.reserved.regions	= memblock_reserved_init_regions,
	.reserved.cnt		= 1,	/* empty dummy entry */
	.reserved.max		= INIT_MEMBLOCK_RESERVED_REGIONS,
	.reserved.name		= "reserved",

	.bottom_up		= false,
	.current_limit		= MEMBLOCK_ALLOC_ANYWHERE,
पूर्ण;

#अगर_घोषित CONFIG_HAVE_MEMBLOCK_PHYS_MAP
काष्ठा memblock_type physmem = अणु
	.regions		= memblock_physmem_init_regions,
	.cnt			= 1,	/* empty dummy entry */
	.max			= INIT_PHYSMEM_REGIONS,
	.name			= "physmem",
पूर्ण;
#पूर्ण_अगर

/*
 * keep a poपूर्णांकer to &memblock.memory in the text section to use it in
 * __next_mem_range() and its helpers.
 *  For architectures that करो not keep memblock data after init, this
 * poपूर्णांकer will be reset to शून्य at memblock_discard()
 */
अटल __refdata काष्ठा memblock_type *memblock_memory = &memblock.memory;

#घोषणा क्रम_each_memblock_type(i, memblock_type, rgn)			\
	क्रम (i = 0, rgn = &memblock_type->regions[0];			\
	     i < memblock_type->cnt;					\
	     i++, rgn = &memblock_type->regions[i])

#घोषणा memblock_dbg(fmt, ...)						\
	करो अणु								\
		अगर (memblock_debug)					\
			pr_info(fmt, ##__VA_ARGS__);			\
	पूर्ण जबतक (0)

अटल पूर्णांक memblock_debug __initdata_memblock;
अटल bool प्रणाली_has_some_mirror __initdata_memblock = false;
अटल पूर्णांक memblock_can_resize __initdata_memblock;
अटल पूर्णांक memblock_memory_in_slab __initdata_memblock = 0;
अटल पूर्णांक memblock_reserved_in_slab __initdata_memblock = 0;

अटल क्रमागत memblock_flags __init_memblock choose_memblock_flags(व्योम)
अणु
	वापस प्रणाली_has_some_mirror ? MEMBLOCK_MIRROR : MEMBLOCK_NONE;
पूर्ण

/* adjust *@size so that (@base + *@size) करोesn't overflow, वापस new size */
अटल अंतरभूत phys_addr_t memblock_cap_size(phys_addr_t base, phys_addr_t *size)
अणु
	वापस *size = min(*size, PHYS_ADDR_MAX - base);
पूर्ण

/*
 * Address comparison utilities
 */
अटल अचिन्हित दीर्घ __init_memblock memblock_addrs_overlap(phys_addr_t base1, phys_addr_t size1,
				       phys_addr_t base2, phys_addr_t size2)
अणु
	वापस ((base1 < (base2 + size2)) && (base2 < (base1 + size1)));
पूर्ण

bool __init_memblock memblock_overlaps_region(काष्ठा memblock_type *type,
					phys_addr_t base, phys_addr_t size)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < type->cnt; i++)
		अगर (memblock_addrs_overlap(base, size, type->regions[i].base,
					   type->regions[i].size))
			अवरोध;
	वापस i < type->cnt;
पूर्ण

/**
 * __memblock_find_range_bottom_up - find मुक्त area utility in bottom-up
 * @start: start of candidate range
 * @end: end of candidate range, can be %MEMBLOCK_ALLOC_ANYWHERE or
 *       %MEMBLOCK_ALLOC_ACCESSIBLE
 * @size: size of मुक्त area to find
 * @align: alignment of मुक्त area to find
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 * @flags: pick from blocks based on memory attributes
 *
 * Utility called from memblock_find_in_range_node(), find मुक्त area bottom-up.
 *
 * Return:
 * Found address on success, 0 on failure.
 */
अटल phys_addr_t __init_memblock
__memblock_find_range_bottom_up(phys_addr_t start, phys_addr_t end,
				phys_addr_t size, phys_addr_t align, पूर्णांक nid,
				क्रमागत memblock_flags flags)
अणु
	phys_addr_t this_start, this_end, cand;
	u64 i;

	क्रम_each_मुक्त_mem_range(i, nid, flags, &this_start, &this_end, शून्य) अणु
		this_start = clamp(this_start, start, end);
		this_end = clamp(this_end, start, end);

		cand = round_up(this_start, align);
		अगर (cand < this_end && this_end - cand >= size)
			वापस cand;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __memblock_find_range_top_करोwn - find मुक्त area utility, in top-करोwn
 * @start: start of candidate range
 * @end: end of candidate range, can be %MEMBLOCK_ALLOC_ANYWHERE or
 *       %MEMBLOCK_ALLOC_ACCESSIBLE
 * @size: size of मुक्त area to find
 * @align: alignment of मुक्त area to find
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 * @flags: pick from blocks based on memory attributes
 *
 * Utility called from memblock_find_in_range_node(), find मुक्त area top-करोwn.
 *
 * Return:
 * Found address on success, 0 on failure.
 */
अटल phys_addr_t __init_memblock
__memblock_find_range_top_करोwn(phys_addr_t start, phys_addr_t end,
			       phys_addr_t size, phys_addr_t align, पूर्णांक nid,
			       क्रमागत memblock_flags flags)
अणु
	phys_addr_t this_start, this_end, cand;
	u64 i;

	क्रम_each_मुक्त_mem_range_reverse(i, nid, flags, &this_start, &this_end,
					शून्य) अणु
		this_start = clamp(this_start, start, end);
		this_end = clamp(this_end, start, end);

		अगर (this_end < size)
			जारी;

		cand = round_करोwn(this_end - size, align);
		अगर (cand >= this_start)
			वापस cand;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * memblock_find_in_range_node - find मुक्त area in given range and node
 * @size: size of मुक्त area to find
 * @align: alignment of मुक्त area to find
 * @start: start of candidate range
 * @end: end of candidate range, can be %MEMBLOCK_ALLOC_ANYWHERE or
 *       %MEMBLOCK_ALLOC_ACCESSIBLE
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 * @flags: pick from blocks based on memory attributes
 *
 * Find @size मुक्त area aligned to @align in the specअगरied range and node.
 *
 * Return:
 * Found address on success, 0 on failure.
 */
अटल phys_addr_t __init_memblock memblock_find_in_range_node(phys_addr_t size,
					phys_addr_t align, phys_addr_t start,
					phys_addr_t end, पूर्णांक nid,
					क्रमागत memblock_flags flags)
अणु
	/* pump up @end */
	अगर (end == MEMBLOCK_ALLOC_ACCESSIBLE ||
	    end == MEMBLOCK_ALLOC_KASAN)
		end = memblock.current_limit;

	/* aव्योम allocating the first page */
	start = max_t(phys_addr_t, start, PAGE_SIZE);
	end = max(start, end);

	अगर (memblock_bottom_up())
		वापस __memblock_find_range_bottom_up(start, end, size, align,
						       nid, flags);
	अन्यथा
		वापस __memblock_find_range_top_करोwn(start, end, size, align,
						      nid, flags);
पूर्ण

/**
 * memblock_find_in_range - find मुक्त area in given range
 * @start: start of candidate range
 * @end: end of candidate range, can be %MEMBLOCK_ALLOC_ANYWHERE or
 *       %MEMBLOCK_ALLOC_ACCESSIBLE
 * @size: size of मुक्त area to find
 * @align: alignment of मुक्त area to find
 *
 * Find @size मुक्त area aligned to @align in the specअगरied range.
 *
 * Return:
 * Found address on success, 0 on failure.
 */
phys_addr_t __init_memblock memblock_find_in_range(phys_addr_t start,
					phys_addr_t end, phys_addr_t size,
					phys_addr_t align)
अणु
	phys_addr_t ret;
	क्रमागत memblock_flags flags = choose_memblock_flags();

again:
	ret = memblock_find_in_range_node(size, align, start, end,
					    NUMA_NO_NODE, flags);

	अगर (!ret && (flags & MEMBLOCK_MIRROR)) अणु
		pr_warn("Could not allocate %pap bytes of mirrored memory\n",
			&size);
		flags &= ~MEMBLOCK_MIRROR;
		जाओ again;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __init_memblock memblock_हटाओ_region(काष्ठा memblock_type *type, अचिन्हित दीर्घ r)
अणु
	type->total_size -= type->regions[r].size;
	स_हटाओ(&type->regions[r], &type->regions[r + 1],
		(type->cnt - (r + 1)) * माप(type->regions[r]));
	type->cnt--;

	/* Special हाल क्रम empty arrays */
	अगर (type->cnt == 0) अणु
		WARN_ON(type->total_size != 0);
		type->cnt = 1;
		type->regions[0].base = 0;
		type->regions[0].size = 0;
		type->regions[0].flags = 0;
		memblock_set_region_node(&type->regions[0], MAX_NUMNODES);
	पूर्ण
पूर्ण

#अगर_अघोषित CONFIG_ARCH_KEEP_MEMBLOCK
/**
 * memblock_discard - discard memory and reserved arrays अगर they were allocated
 */
व्योम __init memblock_discard(व्योम)
अणु
	phys_addr_t addr, size;

	अगर (memblock.reserved.regions != memblock_reserved_init_regions) अणु
		addr = __pa(memblock.reserved.regions);
		size = PAGE_ALIGN(माप(काष्ठा memblock_region) *
				  memblock.reserved.max);
		__memblock_मुक्त_late(addr, size);
	पूर्ण

	अगर (memblock.memory.regions != memblock_memory_init_regions) अणु
		addr = __pa(memblock.memory.regions);
		size = PAGE_ALIGN(माप(काष्ठा memblock_region) *
				  memblock.memory.max);
		__memblock_मुक्त_late(addr, size);
	पूर्ण

	memblock_memory = शून्य;
पूर्ण
#पूर्ण_अगर

/**
 * memblock_द्विगुन_array - द्विगुन the size of the memblock regions array
 * @type: memblock type of the regions array being द्विगुनd
 * @new_area_start: starting address of memory range to aव्योम overlap with
 * @new_area_size: size of memory range to aव्योम overlap with
 *
 * Double the size of the @type regions array. If memblock is being used to
 * allocate memory क्रम a new reserved regions array and there is a previously
 * allocated memory range [@new_area_start, @new_area_start + @new_area_size]
 * रुकोing to be reserved, ensure the memory used by the new array करोes
 * not overlap.
 *
 * Return:
 * 0 on success, -1 on failure.
 */
अटल पूर्णांक __init_memblock memblock_द्विगुन_array(काष्ठा memblock_type *type,
						phys_addr_t new_area_start,
						phys_addr_t new_area_size)
अणु
	काष्ठा memblock_region *new_array, *old_array;
	phys_addr_t old_alloc_size, new_alloc_size;
	phys_addr_t old_size, new_size, addr, new_end;
	पूर्णांक use_slab = slab_is_available();
	पूर्णांक *in_slab;

	/* We करोn't allow resizing until we know about the reserved regions
	 * of memory that aren't suitable क्रम allocation
	 */
	अगर (!memblock_can_resize)
		वापस -1;

	/* Calculate new द्विगुनd size */
	old_size = type->max * माप(काष्ठा memblock_region);
	new_size = old_size << 1;
	/*
	 * We need to allocated new one align to PAGE_SIZE,
	 *   so we can मुक्त them completely later.
	 */
	old_alloc_size = PAGE_ALIGN(old_size);
	new_alloc_size = PAGE_ALIGN(new_size);

	/* Retrieve the slab flag */
	अगर (type == &memblock.memory)
		in_slab = &memblock_memory_in_slab;
	अन्यथा
		in_slab = &memblock_reserved_in_slab;

	/* Try to find some space क्रम it */
	अगर (use_slab) अणु
		new_array = kदो_स्मृति(new_size, GFP_KERNEL);
		addr = new_array ? __pa(new_array) : 0;
	पूर्ण अन्यथा अणु
		/* only exclude range when trying to द्विगुन reserved.regions */
		अगर (type != &memblock.reserved)
			new_area_start = new_area_size = 0;

		addr = memblock_find_in_range(new_area_start + new_area_size,
						memblock.current_limit,
						new_alloc_size, PAGE_SIZE);
		अगर (!addr && new_area_size)
			addr = memblock_find_in_range(0,
				min(new_area_start, memblock.current_limit),
				new_alloc_size, PAGE_SIZE);

		new_array = addr ? __va(addr) : शून्य;
	पूर्ण
	अगर (!addr) अणु
		pr_err("memblock: Failed to double %s array from %ld to %ld entries !\n",
		       type->name, type->max, type->max * 2);
		वापस -1;
	पूर्ण

	new_end = addr + new_size - 1;
	memblock_dbg("memblock: %s is doubled to %ld at [%pa-%pa]",
			type->name, type->max * 2, &addr, &new_end);

	/*
	 * Found space, we now need to move the array over beक्रमe we add the
	 * reserved region since it may be our reserved array itself that is
	 * full.
	 */
	स_नकल(new_array, type->regions, old_size);
	स_रखो(new_array + type->max, 0, old_size);
	old_array = type->regions;
	type->regions = new_array;
	type->max <<= 1;

	/* Free old array. We needn't मुक्त it अगर the array is the अटल one */
	अगर (*in_slab)
		kमुक्त(old_array);
	अन्यथा अगर (old_array != memblock_memory_init_regions &&
		 old_array != memblock_reserved_init_regions)
		memblock_मुक्त(__pa(old_array), old_alloc_size);

	/*
	 * Reserve the new array अगर that comes from the memblock.  Otherwise, we
	 * needn't करो it
	 */
	अगर (!use_slab)
		BUG_ON(memblock_reserve(addr, new_alloc_size));

	/* Update slab flag */
	*in_slab = use_slab;

	वापस 0;
पूर्ण

/**
 * memblock_merge_regions - merge neighboring compatible regions
 * @type: memblock type to scan
 *
 * Scan @type and merge neighboring compatible regions.
 */
अटल व्योम __init_memblock memblock_merge_regions(काष्ठा memblock_type *type)
अणु
	पूर्णांक i = 0;

	/* cnt never goes below 1 */
	जबतक (i < type->cnt - 1) अणु
		काष्ठा memblock_region *this = &type->regions[i];
		काष्ठा memblock_region *next = &type->regions[i + 1];

		अगर (this->base + this->size != next->base ||
		    memblock_get_region_node(this) !=
		    memblock_get_region_node(next) ||
		    this->flags != next->flags) अणु
			BUG_ON(this->base + this->size > next->base);
			i++;
			जारी;
		पूर्ण

		this->size += next->size;
		/* move क्रमward from next + 1, index of which is i + 2 */
		स_हटाओ(next, next + 1, (type->cnt - (i + 2)) * माप(*next));
		type->cnt--;
	पूर्ण
पूर्ण

/**
 * memblock_insert_region - insert new memblock region
 * @type:	memblock type to insert पूर्णांकo
 * @idx:	index क्रम the insertion poपूर्णांक
 * @base:	base address of the new region
 * @size:	size of the new region
 * @nid:	node id of the new region
 * @flags:	flags of the new region
 *
 * Insert new memblock region [@base, @base + @size) पूर्णांकo @type at @idx.
 * @type must alपढ़ोy have extra room to accommodate the new region.
 */
अटल व्योम __init_memblock memblock_insert_region(काष्ठा memblock_type *type,
						   पूर्णांक idx, phys_addr_t base,
						   phys_addr_t size,
						   पूर्णांक nid,
						   क्रमागत memblock_flags flags)
अणु
	काष्ठा memblock_region *rgn = &type->regions[idx];

	BUG_ON(type->cnt >= type->max);
	स_हटाओ(rgn + 1, rgn, (type->cnt - idx) * माप(*rgn));
	rgn->base = base;
	rgn->size = size;
	rgn->flags = flags;
	memblock_set_region_node(rgn, nid);
	type->cnt++;
	type->total_size += size;
पूर्ण

/**
 * memblock_add_range - add new memblock region
 * @type: memblock type to add new region पूर्णांकo
 * @base: base address of the new region
 * @size: size of the new region
 * @nid: nid of the new region
 * @flags: flags of the new region
 *
 * Add new memblock region [@base, @base + @size) पूर्णांकo @type.  The new region
 * is allowed to overlap with existing ones - overlaps करोn't affect alपढ़ोy
 * existing regions.  @type is guaranteed to be minimal (all neighbouring
 * compatible regions are merged) after the addition.
 *
 * Return:
 * 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक __init_memblock memblock_add_range(काष्ठा memblock_type *type,
				phys_addr_t base, phys_addr_t size,
				पूर्णांक nid, क्रमागत memblock_flags flags)
अणु
	bool insert = false;
	phys_addr_t obase = base;
	phys_addr_t end = base + memblock_cap_size(base, &size);
	पूर्णांक idx, nr_new;
	काष्ठा memblock_region *rgn;

	अगर (!size)
		वापस 0;

	/* special हाल क्रम empty array */
	अगर (type->regions[0].size == 0) अणु
		WARN_ON(type->cnt != 1 || type->total_size);
		type->regions[0].base = base;
		type->regions[0].size = size;
		type->regions[0].flags = flags;
		memblock_set_region_node(&type->regions[0], nid);
		type->total_size = size;
		वापस 0;
	पूर्ण
repeat:
	/*
	 * The following is executed twice.  Once with %false @insert and
	 * then with %true.  The first counts the number of regions needed
	 * to accommodate the new area.  The second actually inserts them.
	 */
	base = obase;
	nr_new = 0;

	क्रम_each_memblock_type(idx, type, rgn) अणु
		phys_addr_t rbase = rgn->base;
		phys_addr_t rend = rbase + rgn->size;

		अगर (rbase >= end)
			अवरोध;
		अगर (rend <= base)
			जारी;
		/*
		 * @rgn overlaps.  If it separates the lower part of new
		 * area, insert that portion.
		 */
		अगर (rbase > base) अणु
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
			WARN_ON(nid != memblock_get_region_node(rgn));
#पूर्ण_अगर
			WARN_ON(flags != rgn->flags);
			nr_new++;
			अगर (insert)
				memblock_insert_region(type, idx++, base,
						       rbase - base, nid,
						       flags);
		पूर्ण
		/* area below @rend is dealt with, क्रमget about it */
		base = min(rend, end);
	पूर्ण

	/* insert the reमुख्यing portion */
	अगर (base < end) अणु
		nr_new++;
		अगर (insert)
			memblock_insert_region(type, idx, base, end - base,
					       nid, flags);
	पूर्ण

	अगर (!nr_new)
		वापस 0;

	/*
	 * If this was the first round, resize array and repeat क्रम actual
	 * insertions; otherwise, merge and वापस.
	 */
	अगर (!insert) अणु
		जबतक (type->cnt + nr_new > type->max)
			अगर (memblock_द्विगुन_array(type, obase, size) < 0)
				वापस -ENOMEM;
		insert = true;
		जाओ repeat;
	पूर्ण अन्यथा अणु
		memblock_merge_regions(type);
		वापस 0;
	पूर्ण
पूर्ण

/**
 * memblock_add_node - add new memblock region within a NUMA node
 * @base: base address of the new region
 * @size: size of the new region
 * @nid: nid of the new region
 *
 * Add new memblock region [@base, @base + @size) to the "memory"
 * type. See memblock_add_range() description क्रम mode details
 *
 * Return:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_add_node(phys_addr_t base, phys_addr_t size,
				       पूर्णांक nid)
अणु
	वापस memblock_add_range(&memblock.memory, base, size, nid, 0);
पूर्ण

/**
 * memblock_add - add new memblock region
 * @base: base address of the new region
 * @size: size of the new region
 *
 * Add new memblock region [@base, @base + @size) to the "memory"
 * type. See memblock_add_range() description क्रम mode details
 *
 * Return:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_add(phys_addr_t base, phys_addr_t size)
अणु
	phys_addr_t end = base + size - 1;

	memblock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (व्योम *)_RET_IP_);

	वापस memblock_add_range(&memblock.memory, base, size, MAX_NUMNODES, 0);
पूर्ण

/**
 * memblock_isolate_range - isolate given range पूर्णांकo disjoपूर्णांक memblocks
 * @type: memblock type to isolate range क्रम
 * @base: base of range to isolate
 * @size: size of range to isolate
 * @start_rgn: out parameter क्रम the start of isolated region
 * @end_rgn: out parameter क्रम the end of isolated region
 *
 * Walk @type and ensure that regions करोn't cross the boundaries defined by
 * [@base, @base + @size).  Crossing regions are split at the boundaries,
 * which may create at most two more regions.  The index of the first
 * region inside the range is वापसed in *@start_rgn and end in *@end_rgn.
 *
 * Return:
 * 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक __init_memblock memblock_isolate_range(काष्ठा memblock_type *type,
					phys_addr_t base, phys_addr_t size,
					पूर्णांक *start_rgn, पूर्णांक *end_rgn)
अणु
	phys_addr_t end = base + memblock_cap_size(base, &size);
	पूर्णांक idx;
	काष्ठा memblock_region *rgn;

	*start_rgn = *end_rgn = 0;

	अगर (!size)
		वापस 0;

	/* we'll create at most two more regions */
	जबतक (type->cnt + 2 > type->max)
		अगर (memblock_द्विगुन_array(type, base, size) < 0)
			वापस -ENOMEM;

	क्रम_each_memblock_type(idx, type, rgn) अणु
		phys_addr_t rbase = rgn->base;
		phys_addr_t rend = rbase + rgn->size;

		अगर (rbase >= end)
			अवरोध;
		अगर (rend <= base)
			जारी;

		अगर (rbase < base) अणु
			/*
			 * @rgn पूर्णांकersects from below.  Split and जारी
			 * to process the next region - the new top half.
			 */
			rgn->base = base;
			rgn->size -= base - rbase;
			type->total_size -= base - rbase;
			memblock_insert_region(type, idx, rbase, base - rbase,
					       memblock_get_region_node(rgn),
					       rgn->flags);
		पूर्ण अन्यथा अगर (rend > end) अणु
			/*
			 * @rgn पूर्णांकersects from above.  Split and reकरो the
			 * current region - the new bottom half.
			 */
			rgn->base = end;
			rgn->size -= end - rbase;
			type->total_size -= end - rbase;
			memblock_insert_region(type, idx--, rbase, end - rbase,
					       memblock_get_region_node(rgn),
					       rgn->flags);
		पूर्ण अन्यथा अणु
			/* @rgn is fully contained, record it */
			अगर (!*end_rgn)
				*start_rgn = idx;
			*end_rgn = idx + 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init_memblock memblock_हटाओ_range(काष्ठा memblock_type *type,
					  phys_addr_t base, phys_addr_t size)
अणु
	पूर्णांक start_rgn, end_rgn;
	पूर्णांक i, ret;

	ret = memblock_isolate_range(type, base, size, &start_rgn, &end_rgn);
	अगर (ret)
		वापस ret;

	क्रम (i = end_rgn - 1; i >= start_rgn; i--)
		memblock_हटाओ_region(type, i);
	वापस 0;
पूर्ण

पूर्णांक __init_memblock memblock_हटाओ(phys_addr_t base, phys_addr_t size)
अणु
	phys_addr_t end = base + size - 1;

	memblock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (व्योम *)_RET_IP_);

	वापस memblock_हटाओ_range(&memblock.memory, base, size);
पूर्ण

/**
 * memblock_मुक्त - मुक्त boot memory block
 * @base: phys starting address of the  boot memory block
 * @size: size of the boot memory block in bytes
 *
 * Free boot memory block previously allocated by memblock_alloc_xx() API.
 * The मुक्तing memory will not be released to the buddy allocator.
 */
पूर्णांक __init_memblock memblock_मुक्त(phys_addr_t base, phys_addr_t size)
अणु
	phys_addr_t end = base + size - 1;

	memblock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (व्योम *)_RET_IP_);

	kmemleak_मुक्त_part_phys(base, size);
	वापस memblock_हटाओ_range(&memblock.reserved, base, size);
पूर्ण

पूर्णांक __init_memblock memblock_reserve(phys_addr_t base, phys_addr_t size)
अणु
	phys_addr_t end = base + size - 1;

	memblock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (व्योम *)_RET_IP_);

	वापस memblock_add_range(&memblock.reserved, base, size, MAX_NUMNODES, 0);
पूर्ण

#अगर_घोषित CONFIG_HAVE_MEMBLOCK_PHYS_MAP
पूर्णांक __init_memblock memblock_physmem_add(phys_addr_t base, phys_addr_t size)
अणु
	phys_addr_t end = base + size - 1;

	memblock_dbg("%s: [%pa-%pa] %pS\n", __func__,
		     &base, &end, (व्योम *)_RET_IP_);

	वापस memblock_add_range(&physmem, base, size, MAX_NUMNODES, 0);
पूर्ण
#पूर्ण_अगर

/**
 * memblock_setclr_flag - set or clear flag क्रम a memory region
 * @base: base address of the region
 * @size: size of the region
 * @set: set or clear the flag
 * @flag: the flag to update
 *
 * This function isolates region [@base, @base + @size), and sets/clears flag
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक __init_memblock memblock_setclr_flag(phys_addr_t base,
				phys_addr_t size, पूर्णांक set, पूर्णांक flag)
अणु
	काष्ठा memblock_type *type = &memblock.memory;
	पूर्णांक i, ret, start_rgn, end_rgn;

	ret = memblock_isolate_range(type, base, size, &start_rgn, &end_rgn);
	अगर (ret)
		वापस ret;

	क्रम (i = start_rgn; i < end_rgn; i++) अणु
		काष्ठा memblock_region *r = &type->regions[i];

		अगर (set)
			r->flags |= flag;
		अन्यथा
			r->flags &= ~flag;
	पूर्ण

	memblock_merge_regions(type);
	वापस 0;
पूर्ण

/**
 * memblock_mark_hotplug - Mark hotpluggable memory with flag MEMBLOCK_HOTPLUG.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_mark_hotplug(phys_addr_t base, phys_addr_t size)
अणु
	वापस memblock_setclr_flag(base, size, 1, MEMBLOCK_HOTPLUG);
पूर्ण

/**
 * memblock_clear_hotplug - Clear flag MEMBLOCK_HOTPLUG क्रम a specअगरied region.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_clear_hotplug(phys_addr_t base, phys_addr_t size)
अणु
	वापस memblock_setclr_flag(base, size, 0, MEMBLOCK_HOTPLUG);
पूर्ण

/**
 * memblock_mark_mirror - Mark mirrored memory with flag MEMBLOCK_MIRROR.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_mark_mirror(phys_addr_t base, phys_addr_t size)
अणु
	प्रणाली_has_some_mirror = true;

	वापस memblock_setclr_flag(base, size, 1, MEMBLOCK_MIRROR);
पूर्ण

/**
 * memblock_mark_nomap - Mark a memory region with flag MEMBLOCK_NOMAP.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_mark_nomap(phys_addr_t base, phys_addr_t size)
अणु
	वापस memblock_setclr_flag(base, size, 1, MEMBLOCK_NOMAP);
पूर्ण

/**
 * memblock_clear_nomap - Clear flag MEMBLOCK_NOMAP क्रम a specअगरied region.
 * @base: the base phys addr of the region
 * @size: the size of the region
 *
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_clear_nomap(phys_addr_t base, phys_addr_t size)
अणु
	वापस memblock_setclr_flag(base, size, 0, MEMBLOCK_NOMAP);
पूर्ण

अटल bool should_skip_region(काष्ठा memblock_type *type,
			       काष्ठा memblock_region *m,
			       पूर्णांक nid, पूर्णांक flags)
अणु
	पूर्णांक m_nid = memblock_get_region_node(m);

	/* we never skip regions when iterating memblock.reserved or physmem */
	अगर (type != memblock_memory)
		वापस false;

	/* only memory regions are associated with nodes, check it */
	अगर (nid != NUMA_NO_NODE && nid != m_nid)
		वापस true;

	/* skip hotpluggable memory regions अगर needed */
	अगर (movable_node_is_enabled() && memblock_is_hotpluggable(m))
		वापस true;

	/* अगर we want mirror memory skip non-mirror memory regions */
	अगर ((flags & MEMBLOCK_MIRROR) && !memblock_is_mirror(m))
		वापस true;

	/* skip nomap memory unless we were asked क्रम it explicitly */
	अगर (!(flags & MEMBLOCK_NOMAP) && memblock_is_nomap(m))
		वापस true;

	वापस false;
पूर्ण

/**
 * __next_mem_range - next function क्रम क्रम_each_मुक्त_mem_range() etc.
 * @idx: poपूर्णांकer to u64 loop variable
 * @nid: node selector, %NUMA_NO_NODE क्रम all nodes
 * @flags: pick from blocks based on memory attributes
 * @type_a: poपूर्णांकer to memblock_type from where the range is taken
 * @type_b: poपूर्णांकer to memblock_type which excludes memory from being taken
 * @out_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @out_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 * @out_nid: ptr to पूर्णांक क्रम nid of the range, can be %शून्य
 *
 * Find the first area from *@idx which matches @nid, fill the out
 * parameters, and update *@idx क्रम the next iteration.  The lower 32bit of
 * *@idx contains index पूर्णांकo type_a and the upper 32bit indexes the
 * areas beक्रमe each region in type_b.	For example, अगर type_b regions
 * look like the following,
 *
 *	0:[0-16), 1:[32-48), 2:[128-130)
 *
 * The upper 32bit indexes the following regions.
 *
 *	0:[0-0), 1:[16-32), 2:[48-128), 3:[130-MAX)
 *
 * As both region arrays are sorted, the function advances the two indices
 * in lockstep and वापसs each पूर्णांकersection.
 */
व्योम __next_mem_range(u64 *idx, पूर्णांक nid, क्रमागत memblock_flags flags,
		      काष्ठा memblock_type *type_a,
		      काष्ठा memblock_type *type_b, phys_addr_t *out_start,
		      phys_addr_t *out_end, पूर्णांक *out_nid)
अणु
	पूर्णांक idx_a = *idx & 0xffffffff;
	पूर्णांक idx_b = *idx >> 32;

	अगर (WARN_ONCE(nid == MAX_NUMNODES,
	"Usage of MAX_NUMNODES is deprecated. Use NUMA_NO_NODE instead\n"))
		nid = NUMA_NO_NODE;

	क्रम (; idx_a < type_a->cnt; idx_a++) अणु
		काष्ठा memblock_region *m = &type_a->regions[idx_a];

		phys_addr_t m_start = m->base;
		phys_addr_t m_end = m->base + m->size;
		पूर्णांक	    m_nid = memblock_get_region_node(m);

		अगर (should_skip_region(type_a, m, nid, flags))
			जारी;

		अगर (!type_b) अणु
			अगर (out_start)
				*out_start = m_start;
			अगर (out_end)
				*out_end = m_end;
			अगर (out_nid)
				*out_nid = m_nid;
			idx_a++;
			*idx = (u32)idx_a | (u64)idx_b << 32;
			वापस;
		पूर्ण

		/* scan areas beक्रमe each reservation */
		क्रम (; idx_b < type_b->cnt + 1; idx_b++) अणु
			काष्ठा memblock_region *r;
			phys_addr_t r_start;
			phys_addr_t r_end;

			r = &type_b->regions[idx_b];
			r_start = idx_b ? r[-1].base + r[-1].size : 0;
			r_end = idx_b < type_b->cnt ?
				r->base : PHYS_ADDR_MAX;

			/*
			 * अगर idx_b advanced past idx_a,
			 * अवरोध out to advance idx_a
			 */
			अगर (r_start >= m_end)
				अवरोध;
			/* अगर the two regions पूर्णांकersect, we're करोne */
			अगर (m_start < r_end) अणु
				अगर (out_start)
					*out_start =
						max(m_start, r_start);
				अगर (out_end)
					*out_end = min(m_end, r_end);
				अगर (out_nid)
					*out_nid = m_nid;
				/*
				 * The region which ends first is
				 * advanced क्रम the next iteration.
				 */
				अगर (m_end <= r_end)
					idx_a++;
				अन्यथा
					idx_b++;
				*idx = (u32)idx_a | (u64)idx_b << 32;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* संकेत end of iteration */
	*idx = ULदीर्घ_उच्च;
पूर्ण

/**
 * __next_mem_range_rev - generic next function क्रम क्रम_each_*_range_rev()
 *
 * @idx: poपूर्णांकer to u64 loop variable
 * @nid: node selector, %NUMA_NO_NODE क्रम all nodes
 * @flags: pick from blocks based on memory attributes
 * @type_a: poपूर्णांकer to memblock_type from where the range is taken
 * @type_b: poपूर्णांकer to memblock_type which excludes memory from being taken
 * @out_start: ptr to phys_addr_t क्रम start address of the range, can be %शून्य
 * @out_end: ptr to phys_addr_t क्रम end address of the range, can be %शून्य
 * @out_nid: ptr to पूर्णांक क्रम nid of the range, can be %शून्य
 *
 * Finds the next range from type_a which is not marked as unsuitable
 * in type_b.
 *
 * Reverse of __next_mem_range().
 */
व्योम __init_memblock __next_mem_range_rev(u64 *idx, पूर्णांक nid,
					  क्रमागत memblock_flags flags,
					  काष्ठा memblock_type *type_a,
					  काष्ठा memblock_type *type_b,
					  phys_addr_t *out_start,
					  phys_addr_t *out_end, पूर्णांक *out_nid)
अणु
	पूर्णांक idx_a = *idx & 0xffffffff;
	पूर्णांक idx_b = *idx >> 32;

	अगर (WARN_ONCE(nid == MAX_NUMNODES, "Usage of MAX_NUMNODES is deprecated. Use NUMA_NO_NODE instead\n"))
		nid = NUMA_NO_NODE;

	अगर (*idx == (u64)ULदीर्घ_उच्च) अणु
		idx_a = type_a->cnt - 1;
		अगर (type_b != शून्य)
			idx_b = type_b->cnt;
		अन्यथा
			idx_b = 0;
	पूर्ण

	क्रम (; idx_a >= 0; idx_a--) अणु
		काष्ठा memblock_region *m = &type_a->regions[idx_a];

		phys_addr_t m_start = m->base;
		phys_addr_t m_end = m->base + m->size;
		पूर्णांक m_nid = memblock_get_region_node(m);

		अगर (should_skip_region(type_a, m, nid, flags))
			जारी;

		अगर (!type_b) अणु
			अगर (out_start)
				*out_start = m_start;
			अगर (out_end)
				*out_end = m_end;
			अगर (out_nid)
				*out_nid = m_nid;
			idx_a--;
			*idx = (u32)idx_a | (u64)idx_b << 32;
			वापस;
		पूर्ण

		/* scan areas beक्रमe each reservation */
		क्रम (; idx_b >= 0; idx_b--) अणु
			काष्ठा memblock_region *r;
			phys_addr_t r_start;
			phys_addr_t r_end;

			r = &type_b->regions[idx_b];
			r_start = idx_b ? r[-1].base + r[-1].size : 0;
			r_end = idx_b < type_b->cnt ?
				r->base : PHYS_ADDR_MAX;
			/*
			 * अगर idx_b advanced past idx_a,
			 * अवरोध out to advance idx_a
			 */

			अगर (r_end <= m_start)
				अवरोध;
			/* अगर the two regions पूर्णांकersect, we're करोne */
			अगर (m_end > r_start) अणु
				अगर (out_start)
					*out_start = max(m_start, r_start);
				अगर (out_end)
					*out_end = min(m_end, r_end);
				अगर (out_nid)
					*out_nid = m_nid;
				अगर (m_start >= r_start)
					idx_a--;
				अन्यथा
					idx_b--;
				*idx = (u32)idx_a | (u64)idx_b << 32;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	/* संकेत end of iteration */
	*idx = ULदीर्घ_उच्च;
पूर्ण

/*
 * Common iterator पूर्णांकerface used to define क्रम_each_mem_pfn_range().
 */
व्योम __init_memblock __next_mem_pfn_range(पूर्णांक *idx, पूर्णांक nid,
				अचिन्हित दीर्घ *out_start_pfn,
				अचिन्हित दीर्घ *out_end_pfn, पूर्णांक *out_nid)
अणु
	काष्ठा memblock_type *type = &memblock.memory;
	काष्ठा memblock_region *r;
	पूर्णांक r_nid;

	जबतक (++*idx < type->cnt) अणु
		r = &type->regions[*idx];
		r_nid = memblock_get_region_node(r);

		अगर (PFN_UP(r->base) >= PFN_DOWN(r->base + r->size))
			जारी;
		अगर (nid == MAX_NUMNODES || nid == r_nid)
			अवरोध;
	पूर्ण
	अगर (*idx >= type->cnt) अणु
		*idx = -1;
		वापस;
	पूर्ण

	अगर (out_start_pfn)
		*out_start_pfn = PFN_UP(r->base);
	अगर (out_end_pfn)
		*out_end_pfn = PFN_DOWN(r->base + r->size);
	अगर (out_nid)
		*out_nid = r_nid;
पूर्ण

/**
 * memblock_set_node - set node ID on memblock regions
 * @base: base of area to set node ID क्रम
 * @size: size of area to set node ID क्रम
 * @type: memblock type to set node ID क्रम
 * @nid: node ID to set
 *
 * Set the nid of memblock @type regions in [@base, @base + @size) to @nid.
 * Regions which cross the area boundaries are split as necessary.
 *
 * Return:
 * 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक __init_memblock memblock_set_node(phys_addr_t base, phys_addr_t size,
				      काष्ठा memblock_type *type, पूर्णांक nid)
अणु
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
	पूर्णांक start_rgn, end_rgn;
	पूर्णांक i, ret;

	ret = memblock_isolate_range(type, base, size, &start_rgn, &end_rgn);
	अगर (ret)
		वापस ret;

	क्रम (i = start_rgn; i < end_rgn; i++)
		memblock_set_region_node(&type->regions[i], nid);

	memblock_merge_regions(type);
#पूर्ण_अगर
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
/**
 * __next_mem_pfn_range_in_zone - iterator क्रम क्रम_each_*_range_in_zone()
 *
 * @idx: poपूर्णांकer to u64 loop variable
 * @zone: zone in which all of the memory blocks reside
 * @out_spfn: ptr to uदीर्घ क्रम start pfn of the range, can be %शून्य
 * @out_epfn: ptr to uदीर्घ क्रम end pfn of the range, can be %शून्य
 *
 * This function is meant to be a zone/pfn specअगरic wrapper क्रम the
 * क्रम_each_mem_range type iterators. Specअगरically they are used in the
 * deferred memory init routines and as such we were duplicating much of
 * this logic throughout the code. So instead of having it in multiple
 * locations it seemed like it would make more sense to centralize this to
 * one new iterator that करोes everything they need.
 */
व्योम __init_memblock
__next_mem_pfn_range_in_zone(u64 *idx, काष्ठा zone *zone,
			     अचिन्हित दीर्घ *out_spfn, अचिन्हित दीर्घ *out_epfn)
अणु
	पूर्णांक zone_nid = zone_to_nid(zone);
	phys_addr_t spa, epa;
	पूर्णांक nid;

	__next_mem_range(idx, zone_nid, MEMBLOCK_NONE,
			 &memblock.memory, &memblock.reserved,
			 &spa, &epa, &nid);

	जबतक (*idx != U64_MAX) अणु
		अचिन्हित दीर्घ epfn = PFN_DOWN(epa);
		अचिन्हित दीर्घ spfn = PFN_UP(spa);

		/*
		 * Verअगरy the end is at least past the start of the zone and
		 * that we have at least one PFN to initialize.
		 */
		अगर (zone->zone_start_pfn < epfn && spfn < epfn) अणु
			/* अगर we went too far just stop searching */
			अगर (zone_end_pfn(zone) <= spfn) अणु
				*idx = U64_MAX;
				अवरोध;
			पूर्ण

			अगर (out_spfn)
				*out_spfn = max(zone->zone_start_pfn, spfn);
			अगर (out_epfn)
				*out_epfn = min(zone_end_pfn(zone), epfn);

			वापस;
		पूर्ण

		__next_mem_range(idx, zone_nid, MEMBLOCK_NONE,
				 &memblock.memory, &memblock.reserved,
				 &spa, &epa, &nid);
	पूर्ण

	/* संकेत end of iteration */
	अगर (out_spfn)
		*out_spfn = अच_दीर्घ_उच्च;
	अगर (out_epfn)
		*out_epfn = 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_DEFERRED_STRUCT_PAGE_INIT */

/**
 * memblock_alloc_range_nid - allocate boot memory block
 * @size: size of memory block to be allocated in bytes
 * @align: alignment of the region and block's size
 * @start: the lower bound of the memory region to allocate (phys address)
 * @end: the upper bound of the memory region to allocate (phys address)
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 * @exact_nid: control the allocation fall back to other nodes
 *
 * The allocation is perक्रमmed from memory region limited by
 * memblock.current_limit अगर @end == %MEMBLOCK_ALLOC_ACCESSIBLE.
 *
 * If the specअगरied node can not hold the requested memory and @exact_nid
 * is false, the allocation falls back to any node in the प्रणाली.
 *
 * For प्रणालीs with memory mirroring, the allocation is attempted first
 * from the regions with mirroring enabled and then retried from any
 * memory region.
 *
 * In addition, function sets the min_count to 0 using kmemleak_alloc_phys क्रम
 * allocated boot memory block, so that it is never reported as leaks.
 *
 * Return:
 * Physical address of allocated memory block on success, %0 on failure.
 */
phys_addr_t __init memblock_alloc_range_nid(phys_addr_t size,
					phys_addr_t align, phys_addr_t start,
					phys_addr_t end, पूर्णांक nid,
					bool exact_nid)
अणु
	क्रमागत memblock_flags flags = choose_memblock_flags();
	phys_addr_t found;

	अगर (WARN_ONCE(nid == MAX_NUMNODES, "Usage of MAX_NUMNODES is deprecated. Use NUMA_NO_NODE instead\n"))
		nid = NUMA_NO_NODE;

	अगर (!align) अणु
		/* Can't use WARNs this early in boot on घातerpc */
		dump_stack();
		align = SMP_CACHE_BYTES;
	पूर्ण

again:
	found = memblock_find_in_range_node(size, align, start, end, nid,
					    flags);
	अगर (found && !memblock_reserve(found, size))
		जाओ करोne;

	अगर (nid != NUMA_NO_NODE && !exact_nid) अणु
		found = memblock_find_in_range_node(size, align, start,
						    end, NUMA_NO_NODE,
						    flags);
		अगर (found && !memblock_reserve(found, size))
			जाओ करोne;
	पूर्ण

	अगर (flags & MEMBLOCK_MIRROR) अणु
		flags &= ~MEMBLOCK_MIRROR;
		pr_warn("Could not allocate %pap bytes of mirrored memory\n",
			&size);
		जाओ again;
	पूर्ण

	वापस 0;

करोne:
	/* Skip kmemleak क्रम kasan_init() due to high volume. */
	अगर (end != MEMBLOCK_ALLOC_KASAN)
		/*
		 * The min_count is set to 0 so that memblock allocated
		 * blocks are never reported as leaks. This is because many
		 * of these blocks are only referred via the physical
		 * address which is not looked up by kmemleak.
		 */
		kmemleak_alloc_phys(found, size, 0, 0);

	वापस found;
पूर्ण

/**
 * memblock_phys_alloc_range - allocate a memory block inside specअगरied range
 * @size: size of memory block to be allocated in bytes
 * @align: alignment of the region and block's size
 * @start: the lower bound of the memory region to allocate (physical address)
 * @end: the upper bound of the memory region to allocate (physical address)
 *
 * Allocate @size bytes in the between @start and @end.
 *
 * Return: physical address of the allocated memory block on success,
 * %0 on failure.
 */
phys_addr_t __init memblock_phys_alloc_range(phys_addr_t size,
					     phys_addr_t align,
					     phys_addr_t start,
					     phys_addr_t end)
अणु
	memblock_dbg("%s: %llu bytes align=0x%llx from=%pa max_addr=%pa %pS\n",
		     __func__, (u64)size, (u64)align, &start, &end,
		     (व्योम *)_RET_IP_);
	वापस memblock_alloc_range_nid(size, align, start, end, NUMA_NO_NODE,
					false);
पूर्ण

/**
 * memblock_phys_alloc_try_nid - allocate a memory block from specअगरied NUMA node
 * @size: size of memory block to be allocated in bytes
 * @align: alignment of the region and block's size
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 *
 * Allocates memory block from the specअगरied NUMA node. If the node
 * has no available memory, attempts to allocated from any node in the
 * प्रणाली.
 *
 * Return: physical address of the allocated memory block on success,
 * %0 on failure.
 */
phys_addr_t __init memblock_phys_alloc_try_nid(phys_addr_t size, phys_addr_t align, पूर्णांक nid)
अणु
	वापस memblock_alloc_range_nid(size, align, 0,
					MEMBLOCK_ALLOC_ACCESSIBLE, nid, false);
पूर्ण

/**
 * memblock_alloc_पूर्णांकernal - allocate boot memory block
 * @size: size of memory block to be allocated in bytes
 * @align: alignment of the region and block's size
 * @min_addr: the lower bound of the memory region to allocate (phys address)
 * @max_addr: the upper bound of the memory region to allocate (phys address)
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 * @exact_nid: control the allocation fall back to other nodes
 *
 * Allocates memory block using memblock_alloc_range_nid() and
 * converts the वापसed physical address to भव.
 *
 * The @min_addr limit is dropped अगर it can not be satisfied and the allocation
 * will fall back to memory below @min_addr. Other स्थिरraपूर्णांकs, such
 * as node and mirrored memory will be handled again in
 * memblock_alloc_range_nid().
 *
 * Return:
 * Virtual address of allocated memory block on success, शून्य on failure.
 */
अटल व्योम * __init memblock_alloc_पूर्णांकernal(
				phys_addr_t size, phys_addr_t align,
				phys_addr_t min_addr, phys_addr_t max_addr,
				पूर्णांक nid, bool exact_nid)
अणु
	phys_addr_t alloc;

	/*
	 * Detect any accidental use of these APIs after slab is पढ़ोy, as at
	 * this moment memblock may be deinitialized alपढ़ोy and its
	 * पूर्णांकernal data may be destroyed (after execution of memblock_मुक्त_all)
	 */
	अगर (WARN_ON_ONCE(slab_is_available()))
		वापस kzalloc_node(size, GFP_NOWAIT, nid);

	अगर (max_addr > memblock.current_limit)
		max_addr = memblock.current_limit;

	alloc = memblock_alloc_range_nid(size, align, min_addr, max_addr, nid,
					exact_nid);

	/* retry allocation without lower limit */
	अगर (!alloc && min_addr)
		alloc = memblock_alloc_range_nid(size, align, 0, max_addr, nid,
						exact_nid);

	अगर (!alloc)
		वापस शून्य;

	वापस phys_to_virt(alloc);
पूर्ण

/**
 * memblock_alloc_exact_nid_raw - allocate boot memory block on the exact node
 * without zeroing memory
 * @size: size of memory block to be allocated in bytes
 * @align: alignment of the region and block's size
 * @min_addr: the lower bound of the memory region from where the allocation
 *	  is preferred (phys address)
 * @max_addr: the upper bound of the memory region from where the allocation
 *	      is preferred (phys address), or %MEMBLOCK_ALLOC_ACCESSIBLE to
 *	      allocate only from memory limited by memblock.current_limit value
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 *
 * Public function, provides additional debug inक्रमmation (including caller
 * info), अगर enabled. Does not zero allocated memory.
 *
 * Return:
 * Virtual address of allocated memory block on success, शून्य on failure.
 */
व्योम * __init memblock_alloc_exact_nid_raw(
			phys_addr_t size, phys_addr_t align,
			phys_addr_t min_addr, phys_addr_t max_addr,
			पूर्णांक nid)
अणु
	व्योम *ptr;

	memblock_dbg("%s: %llu bytes align=0x%llx nid=%d from=%pa max_addr=%pa %pS\n",
		     __func__, (u64)size, (u64)align, nid, &min_addr,
		     &max_addr, (व्योम *)_RET_IP_);

	ptr = memblock_alloc_पूर्णांकernal(size, align,
					   min_addr, max_addr, nid, true);
	अगर (ptr && size > 0)
		page_init_poison(ptr, size);

	वापस ptr;
पूर्ण

/**
 * memblock_alloc_try_nid_raw - allocate boot memory block without zeroing
 * memory and without panicking
 * @size: size of memory block to be allocated in bytes
 * @align: alignment of the region and block's size
 * @min_addr: the lower bound of the memory region from where the allocation
 *	  is preferred (phys address)
 * @max_addr: the upper bound of the memory region from where the allocation
 *	      is preferred (phys address), or %MEMBLOCK_ALLOC_ACCESSIBLE to
 *	      allocate only from memory limited by memblock.current_limit value
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 *
 * Public function, provides additional debug inक्रमmation (including caller
 * info), अगर enabled. Does not zero allocated memory, करोes not panic अगर request
 * cannot be satisfied.
 *
 * Return:
 * Virtual address of allocated memory block on success, शून्य on failure.
 */
व्योम * __init memblock_alloc_try_nid_raw(
			phys_addr_t size, phys_addr_t align,
			phys_addr_t min_addr, phys_addr_t max_addr,
			पूर्णांक nid)
अणु
	व्योम *ptr;

	memblock_dbg("%s: %llu bytes align=0x%llx nid=%d from=%pa max_addr=%pa %pS\n",
		     __func__, (u64)size, (u64)align, nid, &min_addr,
		     &max_addr, (व्योम *)_RET_IP_);

	ptr = memblock_alloc_पूर्णांकernal(size, align,
					   min_addr, max_addr, nid, false);
	अगर (ptr && size > 0)
		page_init_poison(ptr, size);

	वापस ptr;
पूर्ण

/**
 * memblock_alloc_try_nid - allocate boot memory block
 * @size: size of memory block to be allocated in bytes
 * @align: alignment of the region and block's size
 * @min_addr: the lower bound of the memory region from where the allocation
 *	  is preferred (phys address)
 * @max_addr: the upper bound of the memory region from where the allocation
 *	      is preferred (phys address), or %MEMBLOCK_ALLOC_ACCESSIBLE to
 *	      allocate only from memory limited by memblock.current_limit value
 * @nid: nid of the मुक्त area to find, %NUMA_NO_NODE क्रम any node
 *
 * Public function, provides additional debug inक्रमmation (including caller
 * info), अगर enabled. This function zeroes the allocated memory.
 *
 * Return:
 * Virtual address of allocated memory block on success, शून्य on failure.
 */
व्योम * __init memblock_alloc_try_nid(
			phys_addr_t size, phys_addr_t align,
			phys_addr_t min_addr, phys_addr_t max_addr,
			पूर्णांक nid)
अणु
	व्योम *ptr;

	memblock_dbg("%s: %llu bytes align=0x%llx nid=%d from=%pa max_addr=%pa %pS\n",
		     __func__, (u64)size, (u64)align, nid, &min_addr,
		     &max_addr, (व्योम *)_RET_IP_);
	ptr = memblock_alloc_पूर्णांकernal(size, align,
					   min_addr, max_addr, nid, false);
	अगर (ptr)
		स_रखो(ptr, 0, size);

	वापस ptr;
पूर्ण

/**
 * __memblock_मुक्त_late - मुक्त pages directly to buddy allocator
 * @base: phys starting address of the  boot memory block
 * @size: size of the boot memory block in bytes
 *
 * This is only useful when the memblock allocator has alपढ़ोy been torn
 * करोwn, but we are still initializing the प्रणाली.  Pages are released directly
 * to the buddy allocator.
 */
व्योम __init __memblock_मुक्त_late(phys_addr_t base, phys_addr_t size)
अणु
	phys_addr_t cursor, end;

	end = base + size - 1;
	memblock_dbg("%s: [%pa-%pa] %pS\n",
		     __func__, &base, &end, (व्योम *)_RET_IP_);
	kmemleak_मुक्त_part_phys(base, size);
	cursor = PFN_UP(base);
	end = PFN_DOWN(base + size);

	क्रम (; cursor < end; cursor++) अणु
		memblock_मुक्त_pages(pfn_to_page(cursor), cursor, 0);
		totalram_pages_inc();
	पूर्ण
पूर्ण

/*
 * Reमुख्यing API functions
 */

phys_addr_t __init_memblock memblock_phys_mem_size(व्योम)
अणु
	वापस memblock.memory.total_size;
पूर्ण

phys_addr_t __init_memblock memblock_reserved_size(व्योम)
अणु
	वापस memblock.reserved.total_size;
पूर्ण

/* lowest address */
phys_addr_t __init_memblock memblock_start_of_DRAM(व्योम)
अणु
	वापस memblock.memory.regions[0].base;
पूर्ण

phys_addr_t __init_memblock memblock_end_of_DRAM(व्योम)
अणु
	पूर्णांक idx = memblock.memory.cnt - 1;

	वापस (memblock.memory.regions[idx].base + memblock.memory.regions[idx].size);
पूर्ण

अटल phys_addr_t __init_memblock __find_max_addr(phys_addr_t limit)
अणु
	phys_addr_t max_addr = PHYS_ADDR_MAX;
	काष्ठा memblock_region *r;

	/*
	 * translate the memory @limit size पूर्णांकo the max address within one of
	 * the memory memblock regions, अगर the @limit exceeds the total size
	 * of those regions, max_addr will keep original value PHYS_ADDR_MAX
	 */
	क्रम_each_mem_region(r) अणु
		अगर (limit <= r->size) अणु
			max_addr = r->base + limit;
			अवरोध;
		पूर्ण
		limit -= r->size;
	पूर्ण

	वापस max_addr;
पूर्ण

व्योम __init memblock_enक्रमce_memory_limit(phys_addr_t limit)
अणु
	phys_addr_t max_addr;

	अगर (!limit)
		वापस;

	max_addr = __find_max_addr(limit);

	/* @limit exceeds the total size of the memory, करो nothing */
	अगर (max_addr == PHYS_ADDR_MAX)
		वापस;

	/* truncate both memory and reserved regions */
	memblock_हटाओ_range(&memblock.memory, max_addr,
			      PHYS_ADDR_MAX);
	memblock_हटाओ_range(&memblock.reserved, max_addr,
			      PHYS_ADDR_MAX);
पूर्ण

व्योम __init memblock_cap_memory_range(phys_addr_t base, phys_addr_t size)
अणु
	पूर्णांक start_rgn, end_rgn;
	पूर्णांक i, ret;

	अगर (!size)
		वापस;

	ret = memblock_isolate_range(&memblock.memory, base, size,
						&start_rgn, &end_rgn);
	अगर (ret)
		वापस;

	/* हटाओ all the MAP regions */
	क्रम (i = memblock.memory.cnt - 1; i >= end_rgn; i--)
		अगर (!memblock_is_nomap(&memblock.memory.regions[i]))
			memblock_हटाओ_region(&memblock.memory, i);

	क्रम (i = start_rgn - 1; i >= 0; i--)
		अगर (!memblock_is_nomap(&memblock.memory.regions[i]))
			memblock_हटाओ_region(&memblock.memory, i);

	/* truncate the reserved regions */
	memblock_हटाओ_range(&memblock.reserved, 0, base);
	memblock_हटाओ_range(&memblock.reserved,
			base + size, PHYS_ADDR_MAX);
पूर्ण

व्योम __init memblock_mem_limit_हटाओ_map(phys_addr_t limit)
अणु
	phys_addr_t max_addr;

	अगर (!limit)
		वापस;

	max_addr = __find_max_addr(limit);

	/* @limit exceeds the total size of the memory, करो nothing */
	अगर (max_addr == PHYS_ADDR_MAX)
		वापस;

	memblock_cap_memory_range(0, max_addr);
पूर्ण

अटल पूर्णांक __init_memblock memblock_search(काष्ठा memblock_type *type, phys_addr_t addr)
अणु
	अचिन्हित पूर्णांक left = 0, right = type->cnt;

	करो अणु
		अचिन्हित पूर्णांक mid = (right + left) / 2;

		अगर (addr < type->regions[mid].base)
			right = mid;
		अन्यथा अगर (addr >= (type->regions[mid].base +
				  type->regions[mid].size))
			left = mid + 1;
		अन्यथा
			वापस mid;
	पूर्ण जबतक (left < right);
	वापस -1;
पूर्ण

bool __init_memblock memblock_is_reserved(phys_addr_t addr)
अणु
	वापस memblock_search(&memblock.reserved, addr) != -1;
पूर्ण

bool __init_memblock memblock_is_memory(phys_addr_t addr)
अणु
	वापस memblock_search(&memblock.memory, addr) != -1;
पूर्ण

bool __init_memblock memblock_is_map_memory(phys_addr_t addr)
अणु
	पूर्णांक i = memblock_search(&memblock.memory, addr);

	अगर (i == -1)
		वापस false;
	वापस !memblock_is_nomap(&memblock.memory.regions[i]);
पूर्ण

पूर्णांक __init_memblock memblock_search_pfn_nid(अचिन्हित दीर्घ pfn,
			 अचिन्हित दीर्घ *start_pfn, अचिन्हित दीर्घ *end_pfn)
अणु
	काष्ठा memblock_type *type = &memblock.memory;
	पूर्णांक mid = memblock_search(type, PFN_PHYS(pfn));

	अगर (mid == -1)
		वापस -1;

	*start_pfn = PFN_DOWN(type->regions[mid].base);
	*end_pfn = PFN_DOWN(type->regions[mid].base + type->regions[mid].size);

	वापस memblock_get_region_node(&type->regions[mid]);
पूर्ण

/**
 * memblock_is_region_memory - check अगर a region is a subset of memory
 * @base: base of region to check
 * @size: size of region to check
 *
 * Check अगर the region [@base, @base + @size) is a subset of a memory block.
 *
 * Return:
 * 0 अगर false, non-zero अगर true
 */
bool __init_memblock memblock_is_region_memory(phys_addr_t base, phys_addr_t size)
अणु
	पूर्णांक idx = memblock_search(&memblock.memory, base);
	phys_addr_t end = base + memblock_cap_size(base, &size);

	अगर (idx == -1)
		वापस false;
	वापस (memblock.memory.regions[idx].base +
		 memblock.memory.regions[idx].size) >= end;
पूर्ण

/**
 * memblock_is_region_reserved - check अगर a region पूर्णांकersects reserved memory
 * @base: base of region to check
 * @size: size of region to check
 *
 * Check अगर the region [@base, @base + @size) पूर्णांकersects a reserved
 * memory block.
 *
 * Return:
 * True अगर they पूर्णांकersect, false अगर not.
 */
bool __init_memblock memblock_is_region_reserved(phys_addr_t base, phys_addr_t size)
अणु
	memblock_cap_size(base, &size);
	वापस memblock_overlaps_region(&memblock.reserved, base, size);
पूर्ण

व्योम __init_memblock memblock_trim_memory(phys_addr_t align)
अणु
	phys_addr_t start, end, orig_start, orig_end;
	काष्ठा memblock_region *r;

	क्रम_each_mem_region(r) अणु
		orig_start = r->base;
		orig_end = r->base + r->size;
		start = round_up(orig_start, align);
		end = round_करोwn(orig_end, align);

		अगर (start == orig_start && end == orig_end)
			जारी;

		अगर (start < end) अणु
			r->base = start;
			r->size = end - start;
		पूर्ण अन्यथा अणु
			memblock_हटाओ_region(&memblock.memory,
					       r - memblock.memory.regions);
			r--;
		पूर्ण
	पूर्ण
पूर्ण

व्योम __init_memblock memblock_set_current_limit(phys_addr_t limit)
अणु
	memblock.current_limit = limit;
पूर्ण

phys_addr_t __init_memblock memblock_get_current_limit(व्योम)
अणु
	वापस memblock.current_limit;
पूर्ण

अटल व्योम __init_memblock memblock_dump(काष्ठा memblock_type *type)
अणु
	phys_addr_t base, end, size;
	क्रमागत memblock_flags flags;
	पूर्णांक idx;
	काष्ठा memblock_region *rgn;

	pr_info(" %s.cnt  = 0x%lx\n", type->name, type->cnt);

	क्रम_each_memblock_type(idx, type, rgn) अणु
		अक्षर nid_buf[32] = "";

		base = rgn->base;
		size = rgn->size;
		end = base + size - 1;
		flags = rgn->flags;
#अगर_घोषित CONFIG_NEED_MULTIPLE_NODES
		अगर (memblock_get_region_node(rgn) != MAX_NUMNODES)
			snम_लिखो(nid_buf, माप(nid_buf), " on node %d",
				 memblock_get_region_node(rgn));
#पूर्ण_अगर
		pr_info(" %s[%#x]\t[%pa-%pa], %pa bytes%s flags: %#x\n",
			type->name, idx, &base, &end, &size, nid_buf, flags);
	पूर्ण
पूर्ण

अटल व्योम __init_memblock __memblock_dump_all(व्योम)
अणु
	pr_info("MEMBLOCK configuration:\n");
	pr_info(" memory size = %pa reserved size = %pa\n",
		&memblock.memory.total_size,
		&memblock.reserved.total_size);

	memblock_dump(&memblock.memory);
	memblock_dump(&memblock.reserved);
#अगर_घोषित CONFIG_HAVE_MEMBLOCK_PHYS_MAP
	memblock_dump(&physmem);
#पूर्ण_अगर
पूर्ण

व्योम __init_memblock memblock_dump_all(व्योम)
अणु
	अगर (memblock_debug)
		__memblock_dump_all();
पूर्ण

व्योम __init memblock_allow_resize(व्योम)
अणु
	memblock_can_resize = 1;
पूर्ण

अटल पूर्णांक __init early_memblock(अक्षर *p)
अणु
	अगर (p && म_माला(p, "debug"))
		memblock_debug = 1;
	वापस 0;
पूर्ण
early_param("memblock", early_memblock);

अटल व्योम __init मुक्त_memmap(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn)
अणु
	काष्ठा page *start_pg, *end_pg;
	phys_addr_t pg, pgend;

	/*
	 * Convert start_pfn/end_pfn to a काष्ठा page poपूर्णांकer.
	 */
	start_pg = pfn_to_page(start_pfn - 1) + 1;
	end_pg = pfn_to_page(end_pfn - 1) + 1;

	/*
	 * Convert to physical addresses, and round start upwards and end
	 * करोwnwards.
	 */
	pg = PAGE_ALIGN(__pa(start_pg));
	pgend = __pa(end_pg) & PAGE_MASK;

	/*
	 * If there are मुक्त pages between these, मुक्त the section of the
	 * memmap array.
	 */
	अगर (pg < pgend)
		memblock_मुक्त(pg, pgend - pg);
पूर्ण

/*
 * The mem_map array can get very big.  Free the unused area of the memory map.
 */
अटल व्योम __init मुक्त_unused_memmap(व्योम)
अणु
	अचिन्हित दीर्घ start, end, prev_end = 0;
	पूर्णांक i;

	अगर (!IS_ENABLED(CONFIG_HAVE_ARCH_PFN_VALID) ||
	    IS_ENABLED(CONFIG_SPARSEMEM_VMEMMAP))
		वापस;

	/*
	 * This relies on each bank being in address order.
	 * The banks are sorted previously in booपंचांगem_init().
	 */
	क्रम_each_mem_pfn_range(i, MAX_NUMNODES, &start, &end, शून्य) अणु
#अगर_घोषित CONFIG_SPARSEMEM
		/*
		 * Take care not to मुक्त memmap entries that करोn't exist
		 * due to SPARSEMEM sections which aren't present.
		 */
		start = min(start, ALIGN(prev_end, PAGES_PER_SECTION));
#अन्यथा
		/*
		 * Align करोwn here since the VM subप्रणाली insists that the
		 * memmap entries are valid from the bank start aligned to
		 * MAX_ORDER_NR_PAGES.
		 */
		start = round_करोwn(start, MAX_ORDER_NR_PAGES);
#पूर्ण_अगर

		/*
		 * If we had a previous bank, and there is a space
		 * between the current bank and the previous, मुक्त it.
		 */
		अगर (prev_end && prev_end < start)
			मुक्त_memmap(prev_end, start);

		/*
		 * Align up here since the VM subप्रणाली insists that the
		 * memmap entries are valid from the bank end aligned to
		 * MAX_ORDER_NR_PAGES.
		 */
		prev_end = ALIGN(end, MAX_ORDER_NR_PAGES);
	पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM
	अगर (!IS_ALIGNED(prev_end, PAGES_PER_SECTION))
		मुक्त_memmap(prev_end, ALIGN(prev_end, PAGES_PER_SECTION));
#पूर्ण_अगर
पूर्ण

अटल व्योम __init __मुक्त_pages_memory(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक order;

	जबतक (start < end) अणु
		order = min(MAX_ORDER - 1UL, __ffs(start));

		जबतक (start + (1UL << order) > end)
			order--;

		memblock_मुक्त_pages(pfn_to_page(start), start, order);

		start += (1UL << order);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ __init __मुक्त_memory_core(phys_addr_t start,
				 phys_addr_t end)
अणु
	अचिन्हित दीर्घ start_pfn = PFN_UP(start);
	अचिन्हित दीर्घ end_pfn = min_t(अचिन्हित दीर्घ,
				      PFN_DOWN(end), max_low_pfn);

	अगर (start_pfn >= end_pfn)
		वापस 0;

	__मुक्त_pages_memory(start_pfn, end_pfn);

	वापस end_pfn - start_pfn;
पूर्ण

अटल अचिन्हित दीर्घ __init मुक्त_low_memory_core_early(व्योम)
अणु
	अचिन्हित दीर्घ count = 0;
	phys_addr_t start, end;
	u64 i;

	memblock_clear_hotplug(0, -1);

	क्रम_each_reserved_mem_range(i, &start, &end)
		reserve_booपंचांगem_region(start, end);

	/*
	 * We need to use NUMA_NO_NODE instead of NODE_DATA(0)->node_id
	 *  because in some हाल like Node0 करोesn't have RAM installed
	 *  low ram will be on Node1
	 */
	क्रम_each_मुक्त_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE, &start, &end,
				शून्य)
		count += __मुक्त_memory_core(start, end);

	वापस count;
पूर्ण

अटल पूर्णांक reset_managed_pages_करोne __initdata;

व्योम reset_node_managed_pages(pg_data_t *pgdat)
अणु
	काष्ठा zone *z;

	क्रम (z = pgdat->node_zones; z < pgdat->node_zones + MAX_NR_ZONES; z++)
		atomic_दीर्घ_set(&z->managed_pages, 0);
पूर्ण

व्योम __init reset_all_zones_managed_pages(व्योम)
अणु
	काष्ठा pglist_data *pgdat;

	अगर (reset_managed_pages_करोne)
		वापस;

	क्रम_each_online_pgdat(pgdat)
		reset_node_managed_pages(pgdat);

	reset_managed_pages_करोne = 1;
पूर्ण

/**
 * memblock_मुक्त_all - release मुक्त pages to the buddy allocator
 */
व्योम __init memblock_मुक्त_all(व्योम)
अणु
	अचिन्हित दीर्घ pages;

	मुक्त_unused_memmap();
	reset_all_zones_managed_pages();

	pages = मुक्त_low_memory_core_early();
	totalram_pages_add(pages);
पूर्ण

#अगर defined(CONFIG_DEBUG_FS) && defined(CONFIG_ARCH_KEEP_MEMBLOCK)

अटल पूर्णांक memblock_debug_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	काष्ठा memblock_type *type = m->निजी;
	काष्ठा memblock_region *reg;
	पूर्णांक i;
	phys_addr_t end;

	क्रम (i = 0; i < type->cnt; i++) अणु
		reg = &type->regions[i];
		end = reg->base + reg->size - 1;

		seq_म_लिखो(m, "%4d: ", i);
		seq_म_लिखो(m, "%pa..%pa\n", &reg->base, &end);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(memblock_debug);

अटल पूर्णांक __init memblock_init_debugfs(व्योम)
अणु
	काष्ठा dentry *root = debugfs_create_dir("memblock", शून्य);

	debugfs_create_file("memory", 0444, root,
			    &memblock.memory, &memblock_debug_fops);
	debugfs_create_file("reserved", 0444, root,
			    &memblock.reserved, &memblock_debug_fops);
#अगर_घोषित CONFIG_HAVE_MEMBLOCK_PHYS_MAP
	debugfs_create_file("physmem", 0444, root, &physmem,
			    &memblock_debug_fops);
#पूर्ण_अगर

	वापस 0;
पूर्ण
__initcall(memblock_init_debugfs);

#पूर्ण_अगर /* CONFIG_DEBUG_FS */
