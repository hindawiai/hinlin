<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/kernel/घातer/snapshot.c
 *
 * This file provides प्रणाली snapshot/restore functionality क्रम swsusp.
 *
 * Copyright (C) 1998-2005 Pavel Machek <pavel@ucw.cz>
 * Copyright (C) 2006 Rafael J. Wysocki <rjw@sisk.pl>
 */

#घोषणा pr_fmt(fmt) "PM: hibernation: " fmt

#समावेश <linux/version.h>
#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/nmi.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/console.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/compiler.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/set_memory.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/पन.स>

#समावेश "power.h"

#अगर defined(CONFIG_STRICT_KERNEL_RWX) && defined(CONFIG_ARCH_HAS_SET_MEMORY)
अटल bool hibernate_restore_protection;
अटल bool hibernate_restore_protection_active;

व्योम enable_restore_image_protection(व्योम)
अणु
	hibernate_restore_protection = true;
पूर्ण

अटल अंतरभूत व्योम hibernate_restore_protection_begin(व्योम)
अणु
	hibernate_restore_protection_active = hibernate_restore_protection;
पूर्ण

अटल अंतरभूत व्योम hibernate_restore_protection_end(व्योम)
अणु
	hibernate_restore_protection_active = false;
पूर्ण

अटल अंतरभूत व्योम hibernate_restore_protect_page(व्योम *page_address)
अणु
	अगर (hibernate_restore_protection_active)
		set_memory_ro((अचिन्हित दीर्घ)page_address, 1);
पूर्ण

अटल अंतरभूत व्योम hibernate_restore_unprotect_page(व्योम *page_address)
अणु
	अगर (hibernate_restore_protection_active)
		set_memory_rw((अचिन्हित दीर्घ)page_address, 1);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम hibernate_restore_protection_begin(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम hibernate_restore_protection_end(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम hibernate_restore_protect_page(व्योम *page_address) अणुपूर्ण
अटल अंतरभूत व्योम hibernate_restore_unprotect_page(व्योम *page_address) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_STRICT_KERNEL_RWX  && CONFIG_ARCH_HAS_SET_MEMORY */


/*
 * The calls to set_direct_map_*() should not fail because remapping a page
 * here means that we only update protection bits in an existing PTE.
 * It is still worth to have a warning here अगर something changes and this
 * will no दीर्घer be the हाल.
 */
अटल अंतरभूत व्योम hibernate_map_page(काष्ठा page *page)
अणु
	अगर (IS_ENABLED(CONFIG_ARCH_HAS_SET_सूचीECT_MAP)) अणु
		पूर्णांक ret = set_direct_map_शेष_noflush(page);

		अगर (ret)
			pr_warn_once("Failed to remap page\n");
	पूर्ण अन्यथा अणु
		debug_pagealloc_map_pages(page, 1);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hibernate_unmap_page(काष्ठा page *page)
अणु
	अगर (IS_ENABLED(CONFIG_ARCH_HAS_SET_सूचीECT_MAP)) अणु
		अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)page_address(page);
		पूर्णांक ret  = set_direct_map_invalid_noflush(page);

		अगर (ret)
			pr_warn_once("Failed to remap page\n");

		flush_tlb_kernel_range(addr, addr + PAGE_SIZE);
	पूर्ण अन्यथा अणु
		debug_pagealloc_unmap_pages(page, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक swsusp_page_is_मुक्त(काष्ठा page *);
अटल व्योम swsusp_set_page_क्रमbidden(काष्ठा page *);
अटल व्योम swsusp_unset_page_क्रमbidden(काष्ठा page *);

/*
 * Number of bytes to reserve क्रम memory allocations made by device drivers
 * from their ->मुक्तze() and ->मुक्तze_noirq() callbacks so that they करोn't
 * cause image creation to fail (tunable via /sys/घातer/reserved_size).
 */
अचिन्हित दीर्घ reserved_size;

व्योम __init hibernate_reserved_size_init(व्योम)
अणु
	reserved_size = SPARE_PAGES * PAGE_SIZE;
पूर्ण

/*
 * Preferred image size in bytes (tunable via /sys/घातer/image_size).
 * When it is set to N, swsusp will करो its best to ensure the image
 * size will not exceed N bytes, but अगर that is impossible, it will
 * try to create the smallest image possible.
 */
अचिन्हित दीर्घ image_size;

व्योम __init hibernate_image_size_init(व्योम)
अणु
	image_size = ((totalram_pages() * 2) / 5) * PAGE_SIZE;
पूर्ण

/*
 * List of PBEs needed क्रम restoring the pages that were allocated beक्रमe
 * the suspend and included in the suspend image, but have also been
 * allocated by the "resume" kernel, so their contents cannot be written
 * directly to their "original" page frames.
 */
काष्ठा pbe *restore_pblist;

/* काष्ठा linked_page is used to build chains of pages */

#घोषणा LINKED_PAGE_DATA_SIZE	(PAGE_SIZE - माप(व्योम *))

काष्ठा linked_page अणु
	काष्ठा linked_page *next;
	अक्षर data[LINKED_PAGE_DATA_SIZE];
पूर्ण __packed;

/*
 * List of "safe" pages (ie. pages that were not used by the image kernel
 * beक्रमe hibernation) that may be used as temporary storage क्रम image kernel
 * memory contents.
 */
अटल काष्ठा linked_page *safe_pages_list;

/* Poपूर्णांकer to an auxiliary buffer (1 page) */
अटल व्योम *buffer;

#घोषणा PG_ANY		0
#घोषणा PG_SAFE		1
#घोषणा PG_UNSAFE_CLEAR	1
#घोषणा PG_UNSAFE_KEEP	0

अटल अचिन्हित पूर्णांक allocated_unsafe_pages;

/**
 * get_image_page - Allocate a page क्रम a hibernation image.
 * @gfp_mask: GFP mask क्रम the allocation.
 * @safe_needed: Get pages that were not used beक्रमe hibernation (restore only)
 *
 * During image restoration, क्रम storing the PBE list and the image data, we can
 * only use memory pages that करो not conflict with the pages used beक्रमe
 * hibernation.  The "unsafe" pages have PageNosaveFree set and we count them
 * using allocated_unsafe_pages.
 *
 * Each allocated image page is marked as PageNosave and PageNosaveFree so that
 * swsusp_मुक्त() can release it.
 */
अटल व्योम *get_image_page(gfp_t gfp_mask, पूर्णांक safe_needed)
अणु
	व्योम *res;

	res = (व्योम *)get_zeroed_page(gfp_mask);
	अगर (safe_needed)
		जबतक (res && swsusp_page_is_मुक्त(virt_to_page(res))) अणु
			/* The page is unsafe, mark it क्रम swsusp_मुक्त() */
			swsusp_set_page_क्रमbidden(virt_to_page(res));
			allocated_unsafe_pages++;
			res = (व्योम *)get_zeroed_page(gfp_mask);
		पूर्ण
	अगर (res) अणु
		swsusp_set_page_क्रमbidden(virt_to_page(res));
		swsusp_set_page_मुक्त(virt_to_page(res));
	पूर्ण
	वापस res;
पूर्ण

अटल व्योम *__get_safe_page(gfp_t gfp_mask)
अणु
	अगर (safe_pages_list) अणु
		व्योम *ret = safe_pages_list;

		safe_pages_list = safe_pages_list->next;
		स_रखो(ret, 0, PAGE_SIZE);
		वापस ret;
	पूर्ण
	वापस get_image_page(gfp_mask, PG_SAFE);
पूर्ण

अचिन्हित दीर्घ get_safe_page(gfp_t gfp_mask)
अणु
	वापस (अचिन्हित दीर्घ)__get_safe_page(gfp_mask);
पूर्ण

अटल काष्ठा page *alloc_image_page(gfp_t gfp_mask)
अणु
	काष्ठा page *page;

	page = alloc_page(gfp_mask);
	अगर (page) अणु
		swsusp_set_page_क्रमbidden(page);
		swsusp_set_page_मुक्त(page);
	पूर्ण
	वापस page;
पूर्ण

अटल व्योम recycle_safe_page(व्योम *page_address)
अणु
	काष्ठा linked_page *lp = page_address;

	lp->next = safe_pages_list;
	safe_pages_list = lp;
पूर्ण

/**
 * मुक्त_image_page - Free a page allocated क्रम hibernation image.
 * @addr: Address of the page to मुक्त.
 * @clear_nosave_मुक्त: If set, clear the PageNosaveFree bit क्रम the page.
 *
 * The page to मुक्त should have been allocated by get_image_page() (page flags
 * set by it are affected).
 */
अटल अंतरभूत व्योम मुक्त_image_page(व्योम *addr, पूर्णांक clear_nosave_मुक्त)
अणु
	काष्ठा page *page;

	BUG_ON(!virt_addr_valid(addr));

	page = virt_to_page(addr);

	swsusp_unset_page_क्रमbidden(page);
	अगर (clear_nosave_मुक्त)
		swsusp_unset_page_मुक्त(page);

	__मुक्त_page(page);
पूर्ण

अटल अंतरभूत व्योम मुक्त_list_of_pages(काष्ठा linked_page *list,
				      पूर्णांक clear_page_nosave)
अणु
	जबतक (list) अणु
		काष्ठा linked_page *lp = list->next;

		मुक्त_image_page(list, clear_page_nosave);
		list = lp;
	पूर्ण
पूर्ण

/*
 * काष्ठा chain_allocator is used क्रम allocating small objects out of
 * a linked list of pages called 'the chain'.
 *
 * The chain grows each समय when there is no room क्रम a new object in
 * the current page.  The allocated objects cannot be मुक्तd inभागidually.
 * It is only possible to मुक्त them all at once, by मुक्तing the entire
 * chain.
 *
 * NOTE: The chain allocator may be inefficient अगर the allocated objects
 * are not much smaller than PAGE_SIZE.
 */
काष्ठा chain_allocator अणु
	काष्ठा linked_page *chain;	/* the chain */
	अचिन्हित पूर्णांक used_space;	/* total size of objects allocated out
					   of the current page */
	gfp_t gfp_mask;		/* mask क्रम allocating pages */
	पूर्णांक safe_needed;	/* अगर set, only "safe" pages are allocated */
पूर्ण;

अटल व्योम chain_init(काष्ठा chain_allocator *ca, gfp_t gfp_mask,
		       पूर्णांक safe_needed)
अणु
	ca->chain = शून्य;
	ca->used_space = LINKED_PAGE_DATA_SIZE;
	ca->gfp_mask = gfp_mask;
	ca->safe_needed = safe_needed;
पूर्ण

अटल व्योम *chain_alloc(काष्ठा chain_allocator *ca, अचिन्हित पूर्णांक size)
अणु
	व्योम *ret;

	अगर (LINKED_PAGE_DATA_SIZE - ca->used_space < size) अणु
		काष्ठा linked_page *lp;

		lp = ca->safe_needed ? __get_safe_page(ca->gfp_mask) :
					get_image_page(ca->gfp_mask, PG_ANY);
		अगर (!lp)
			वापस शून्य;

		lp->next = ca->chain;
		ca->chain = lp;
		ca->used_space = 0;
	पूर्ण
	ret = ca->chain->data + ca->used_space;
	ca->used_space += size;
	वापस ret;
पूर्ण

/**
 * Data types related to memory biपंचांगaps.
 *
 * Memory biपंचांगap is a काष्ठाure consisting of many linked lists of
 * objects.  The मुख्य list's elements are of type काष्ठा zone_biपंचांगap
 * and each of them corresonds to one zone.  For each zone biपंचांगap
 * object there is a list of objects of type काष्ठा bm_block that
 * represent each blocks of biपंचांगap in which inक्रमmation is stored.
 *
 * काष्ठा memory_biपंचांगap contains a poपूर्णांकer to the मुख्य list of zone
 * biपंचांगap objects, a काष्ठा bm_position used क्रम browsing the biपंचांगap,
 * and a poपूर्णांकer to the list of pages used क्रम allocating all of the
 * zone biपंचांगap objects and biपंचांगap block objects.
 *
 * NOTE: It has to be possible to lay out the biपंचांगap in memory
 * using only allocations of order 0.  Additionally, the biपंचांगap is
 * deचिन्हित to work with arbitrary number of zones (this is over the
 * top क्रम now, but let's aव्योम making unnecessary assumptions ;-).
 *
 * काष्ठा zone_biपंचांगap contains a poपूर्णांकer to a list of biपंचांगap block
 * objects and a poपूर्णांकer to the biपंचांगap block object that has been
 * most recently used क्रम setting bits.  Additionally, it contains the
 * PFNs that correspond to the start and end of the represented zone.
 *
 * काष्ठा bm_block contains a poपूर्णांकer to the memory page in which
 * inक्रमmation is stored (in the क्रमm of a block of biपंचांगap)
 * It also contains the pfns that correspond to the start and end of
 * the represented memory area.
 *
 * The memory biपंचांगap is organized as a radix tree to guarantee fast अक्रमom
 * access to the bits. There is one radix tree क्रम each zone (as वापसed
 * from create_mem_extents).
 *
 * One radix tree is represented by one काष्ठा mem_zone_bm_rtree. There are
 * two linked lists क्रम the nodes of the tree, one क्रम the inner nodes and
 * one क्रम the leave nodes. The linked leave nodes are used क्रम fast linear
 * access of the memory biपंचांगap.
 *
 * The काष्ठा rtree_node represents one node of the radix tree.
 */

#घोषणा BM_END_OF_MAP	(~0UL)

#घोषणा BM_BITS_PER_BLOCK	(PAGE_SIZE * BITS_PER_BYTE)
#घोषणा BM_BLOCK_SHIFT		(PAGE_SHIFT + 3)
#घोषणा BM_BLOCK_MASK		((1UL << BM_BLOCK_SHIFT) - 1)

/*
 * काष्ठा rtree_node is a wrapper काष्ठा to link the nodes
 * of the rtree together क्रम easy linear iteration over
 * bits and easy मुक्तing
 */
काष्ठा rtree_node अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ *data;
पूर्ण;

/*
 * काष्ठा mem_zone_bm_rtree represents a biपंचांगap used क्रम one
 * populated memory zone.
 */
काष्ठा mem_zone_bm_rtree अणु
	काष्ठा list_head list;		/* Link Zones together         */
	काष्ठा list_head nodes;		/* Radix Tree inner nodes      */
	काष्ठा list_head leaves;	/* Radix Tree leaves           */
	अचिन्हित दीर्घ start_pfn;	/* Zone start page frame       */
	अचिन्हित दीर्घ end_pfn;		/* Zone end page frame + 1     */
	काष्ठा rtree_node *rtree;	/* Radix Tree Root             */
	पूर्णांक levels;			/* Number of Radix Tree Levels */
	अचिन्हित पूर्णांक blocks;		/* Number of Biपंचांगap Blocks     */
पूर्ण;

/* strcut bm_position is used क्रम browsing memory biपंचांगaps */

काष्ठा bm_position अणु
	काष्ठा mem_zone_bm_rtree *zone;
	काष्ठा rtree_node *node;
	अचिन्हित दीर्घ node_pfn;
	पूर्णांक node_bit;
पूर्ण;

काष्ठा memory_biपंचांगap अणु
	काष्ठा list_head zones;
	काष्ठा linked_page *p_list;	/* list of pages used to store zone
					   biपंचांगap objects and biपंचांगap block
					   objects */
	काष्ठा bm_position cur;	/* most recently used bit position */
पूर्ण;

/* Functions that operate on memory biपंचांगaps */

#घोषणा BM_ENTRIES_PER_LEVEL	(PAGE_SIZE / माप(अचिन्हित दीर्घ))
#अगर BITS_PER_LONG == 32
#घोषणा BM_RTREE_LEVEL_SHIFT	(PAGE_SHIFT - 2)
#अन्यथा
#घोषणा BM_RTREE_LEVEL_SHIFT	(PAGE_SHIFT - 3)
#पूर्ण_अगर
#घोषणा BM_RTREE_LEVEL_MASK	((1UL << BM_RTREE_LEVEL_SHIFT) - 1)

/**
 * alloc_rtree_node - Allocate a new node and add it to the radix tree.
 *
 * This function is used to allocate inner nodes as well as the
 * leave nodes of the radix tree. It also adds the node to the
 * corresponding linked list passed in by the *list parameter.
 */
अटल काष्ठा rtree_node *alloc_rtree_node(gfp_t gfp_mask, पूर्णांक safe_needed,
					   काष्ठा chain_allocator *ca,
					   काष्ठा list_head *list)
अणु
	काष्ठा rtree_node *node;

	node = chain_alloc(ca, माप(काष्ठा rtree_node));
	अगर (!node)
		वापस शून्य;

	node->data = get_image_page(gfp_mask, safe_needed);
	अगर (!node->data)
		वापस शून्य;

	list_add_tail(&node->list, list);

	वापस node;
पूर्ण

/**
 * add_rtree_block - Add a new leave node to the radix tree.
 *
 * The leave nodes need to be allocated in order to keep the leaves
 * linked list in order. This is guaranteed by the zone->blocks
 * counter.
 */
अटल पूर्णांक add_rtree_block(काष्ठा mem_zone_bm_rtree *zone, gfp_t gfp_mask,
			   पूर्णांक safe_needed, काष्ठा chain_allocator *ca)
अणु
	काष्ठा rtree_node *node, *block, **dst;
	अचिन्हित पूर्णांक levels_needed, block_nr;
	पूर्णांक i;

	block_nr = zone->blocks;
	levels_needed = 0;

	/* How many levels करो we need क्रम this block nr? */
	जबतक (block_nr) अणु
		levels_needed += 1;
		block_nr >>= BM_RTREE_LEVEL_SHIFT;
	पूर्ण

	/* Make sure the rtree has enough levels */
	क्रम (i = zone->levels; i < levels_needed; i++) अणु
		node = alloc_rtree_node(gfp_mask, safe_needed, ca,
					&zone->nodes);
		अगर (!node)
			वापस -ENOMEM;

		node->data[0] = (अचिन्हित दीर्घ)zone->rtree;
		zone->rtree = node;
		zone->levels += 1;
	पूर्ण

	/* Allocate new block */
	block = alloc_rtree_node(gfp_mask, safe_needed, ca, &zone->leaves);
	अगर (!block)
		वापस -ENOMEM;

	/* Now walk the rtree to insert the block */
	node = zone->rtree;
	dst = &zone->rtree;
	block_nr = zone->blocks;
	क्रम (i = zone->levels; i > 0; i--) अणु
		पूर्णांक index;

		अगर (!node) अणु
			node = alloc_rtree_node(gfp_mask, safe_needed, ca,
						&zone->nodes);
			अगर (!node)
				वापस -ENOMEM;
			*dst = node;
		पूर्ण

		index = block_nr >> ((i - 1) * BM_RTREE_LEVEL_SHIFT);
		index &= BM_RTREE_LEVEL_MASK;
		dst = (काष्ठा rtree_node **)&((*dst)->data[index]);
		node = *dst;
	पूर्ण

	zone->blocks += 1;
	*dst = block;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_zone_bm_rtree(काष्ठा mem_zone_bm_rtree *zone,
			       पूर्णांक clear_nosave_मुक्त);

/**
 * create_zone_bm_rtree - Create a radix tree क्रम one zone.
 *
 * Allocated the mem_zone_bm_rtree काष्ठाure and initializes it.
 * This function also allocated and builds the radix tree क्रम the
 * zone.
 */
अटल काष्ठा mem_zone_bm_rtree *create_zone_bm_rtree(gfp_t gfp_mask,
						      पूर्णांक safe_needed,
						      काष्ठा chain_allocator *ca,
						      अचिन्हित दीर्घ start,
						      अचिन्हित दीर्घ end)
अणु
	काष्ठा mem_zone_bm_rtree *zone;
	अचिन्हित पूर्णांक i, nr_blocks;
	अचिन्हित दीर्घ pages;

	pages = end - start;
	zone  = chain_alloc(ca, माप(काष्ठा mem_zone_bm_rtree));
	अगर (!zone)
		वापस शून्य;

	INIT_LIST_HEAD(&zone->nodes);
	INIT_LIST_HEAD(&zone->leaves);
	zone->start_pfn = start;
	zone->end_pfn = end;
	nr_blocks = DIV_ROUND_UP(pages, BM_BITS_PER_BLOCK);

	क्रम (i = 0; i < nr_blocks; i++) अणु
		अगर (add_rtree_block(zone, gfp_mask, safe_needed, ca)) अणु
			मुक्त_zone_bm_rtree(zone, PG_UNSAFE_CLEAR);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस zone;
पूर्ण

/**
 * मुक्त_zone_bm_rtree - Free the memory of the radix tree.
 *
 * Free all node pages of the radix tree. The mem_zone_bm_rtree
 * काष्ठाure itself is not मुक्तd here nor are the rtree_node
 * काष्ठाs.
 */
अटल व्योम मुक्त_zone_bm_rtree(काष्ठा mem_zone_bm_rtree *zone,
			       पूर्णांक clear_nosave_मुक्त)
अणु
	काष्ठा rtree_node *node;

	list_क्रम_each_entry(node, &zone->nodes, list)
		मुक्त_image_page(node->data, clear_nosave_मुक्त);

	list_क्रम_each_entry(node, &zone->leaves, list)
		मुक्त_image_page(node->data, clear_nosave_मुक्त);
पूर्ण

अटल व्योम memory_bm_position_reset(काष्ठा memory_biपंचांगap *bm)
अणु
	bm->cur.zone = list_entry(bm->zones.next, काष्ठा mem_zone_bm_rtree,
				  list);
	bm->cur.node = list_entry(bm->cur.zone->leaves.next,
				  काष्ठा rtree_node, list);
	bm->cur.node_pfn = 0;
	bm->cur.node_bit = 0;
पूर्ण

अटल व्योम memory_bm_मुक्त(काष्ठा memory_biपंचांगap *bm, पूर्णांक clear_nosave_मुक्त);

काष्ठा mem_extent अणु
	काष्ठा list_head hook;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

/**
 * मुक्त_mem_extents - Free a list of memory extents.
 * @list: List of extents to मुक्त.
 */
अटल व्योम मुक्त_mem_extents(काष्ठा list_head *list)
अणु
	काष्ठा mem_extent *ext, *aux;

	list_क्रम_each_entry_safe(ext, aux, list, hook) अणु
		list_del(&ext->hook);
		kमुक्त(ext);
	पूर्ण
पूर्ण

/**
 * create_mem_extents - Create a list of memory extents.
 * @list: List to put the extents पूर्णांकo.
 * @gfp_mask: Mask to use क्रम memory allocations.
 *
 * The extents represent contiguous ranges of PFNs.
 */
अटल पूर्णांक create_mem_extents(काष्ठा list_head *list, gfp_t gfp_mask)
अणु
	काष्ठा zone *zone;

	INIT_LIST_HEAD(list);

	क्रम_each_populated_zone(zone) अणु
		अचिन्हित दीर्घ zone_start, zone_end;
		काष्ठा mem_extent *ext, *cur, *aux;

		zone_start = zone->zone_start_pfn;
		zone_end = zone_end_pfn(zone);

		list_क्रम_each_entry(ext, list, hook)
			अगर (zone_start <= ext->end)
				अवरोध;

		अगर (&ext->hook == list || zone_end < ext->start) अणु
			/* New extent is necessary */
			काष्ठा mem_extent *new_ext;

			new_ext = kzalloc(माप(काष्ठा mem_extent), gfp_mask);
			अगर (!new_ext) अणु
				मुक्त_mem_extents(list);
				वापस -ENOMEM;
			पूर्ण
			new_ext->start = zone_start;
			new_ext->end = zone_end;
			list_add_tail(&new_ext->hook, &ext->hook);
			जारी;
		पूर्ण

		/* Merge this zone's range of PFNs with the existing one */
		अगर (zone_start < ext->start)
			ext->start = zone_start;
		अगर (zone_end > ext->end)
			ext->end = zone_end;

		/* More merging may be possible */
		cur = ext;
		list_क्रम_each_entry_safe_जारी(cur, aux, list, hook) अणु
			अगर (zone_end < cur->start)
				अवरोध;
			अगर (zone_end < cur->end)
				ext->end = cur->end;
			list_del(&cur->hook);
			kमुक्त(cur);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * memory_bm_create - Allocate memory क्रम a memory biपंचांगap.
 */
अटल पूर्णांक memory_bm_create(काष्ठा memory_biपंचांगap *bm, gfp_t gfp_mask,
			    पूर्णांक safe_needed)
अणु
	काष्ठा chain_allocator ca;
	काष्ठा list_head mem_extents;
	काष्ठा mem_extent *ext;
	पूर्णांक error;

	chain_init(&ca, gfp_mask, safe_needed);
	INIT_LIST_HEAD(&bm->zones);

	error = create_mem_extents(&mem_extents, gfp_mask);
	अगर (error)
		वापस error;

	list_क्रम_each_entry(ext, &mem_extents, hook) अणु
		काष्ठा mem_zone_bm_rtree *zone;

		zone = create_zone_bm_rtree(gfp_mask, safe_needed, &ca,
					    ext->start, ext->end);
		अगर (!zone) अणु
			error = -ENOMEM;
			जाओ Error;
		पूर्ण
		list_add_tail(&zone->list, &bm->zones);
	पूर्ण

	bm->p_list = ca.chain;
	memory_bm_position_reset(bm);
 Exit:
	मुक्त_mem_extents(&mem_extents);
	वापस error;

 Error:
	bm->p_list = ca.chain;
	memory_bm_मुक्त(bm, PG_UNSAFE_CLEAR);
	जाओ Exit;
पूर्ण

/**
 * memory_bm_मुक्त - Free memory occupied by the memory biपंचांगap.
 * @bm: Memory biपंचांगap.
 */
अटल व्योम memory_bm_मुक्त(काष्ठा memory_biपंचांगap *bm, पूर्णांक clear_nosave_मुक्त)
अणु
	काष्ठा mem_zone_bm_rtree *zone;

	list_क्रम_each_entry(zone, &bm->zones, list)
		मुक्त_zone_bm_rtree(zone, clear_nosave_मुक्त);

	मुक्त_list_of_pages(bm->p_list, clear_nosave_मुक्त);

	INIT_LIST_HEAD(&bm->zones);
पूर्ण

/**
 * memory_bm_find_bit - Find the bit क्रम a given PFN in a memory biपंचांगap.
 *
 * Find the bit in memory biपंचांगap @bm that corresponds to the given PFN.
 * The cur.zone, cur.block and cur.node_pfn members of @bm are updated.
 *
 * Walk the radix tree to find the page containing the bit that represents @pfn
 * and वापस the position of the bit in @addr and @bit_nr.
 */
अटल पूर्णांक memory_bm_find_bit(काष्ठा memory_biपंचांगap *bm, अचिन्हित दीर्घ pfn,
			      व्योम **addr, अचिन्हित पूर्णांक *bit_nr)
अणु
	काष्ठा mem_zone_bm_rtree *curr, *zone;
	काष्ठा rtree_node *node;
	पूर्णांक i, block_nr;

	zone = bm->cur.zone;

	अगर (pfn >= zone->start_pfn && pfn < zone->end_pfn)
		जाओ zone_found;

	zone = शून्य;

	/* Find the right zone */
	list_क्रम_each_entry(curr, &bm->zones, list) अणु
		अगर (pfn >= curr->start_pfn && pfn < curr->end_pfn) अणु
			zone = curr;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!zone)
		वापस -EFAULT;

zone_found:
	/*
	 * We have found the zone. Now walk the radix tree to find the leaf node
	 * क्रम our PFN.
	 */

	/*
	 * If the zone we wish to scan is the current zone and the
	 * pfn falls पूर्णांकo the current node then we करो not need to walk
	 * the tree.
	 */
	node = bm->cur.node;
	अगर (zone == bm->cur.zone &&
	    ((pfn - zone->start_pfn) & ~BM_BLOCK_MASK) == bm->cur.node_pfn)
		जाओ node_found;

	node      = zone->rtree;
	block_nr  = (pfn - zone->start_pfn) >> BM_BLOCK_SHIFT;

	क्रम (i = zone->levels; i > 0; i--) अणु
		पूर्णांक index;

		index = block_nr >> ((i - 1) * BM_RTREE_LEVEL_SHIFT);
		index &= BM_RTREE_LEVEL_MASK;
		BUG_ON(node->data[index] == 0);
		node = (काष्ठा rtree_node *)node->data[index];
	पूर्ण

node_found:
	/* Update last position */
	bm->cur.zone = zone;
	bm->cur.node = node;
	bm->cur.node_pfn = (pfn - zone->start_pfn) & ~BM_BLOCK_MASK;

	/* Set वापस values */
	*addr = node->data;
	*bit_nr = (pfn - zone->start_pfn) & BM_BLOCK_MASK;

	वापस 0;
पूर्ण

अटल व्योम memory_bm_set_bit(काष्ठा memory_biपंचांगap *bm, अचिन्हित दीर्घ pfn)
अणु
	व्योम *addr;
	अचिन्हित पूर्णांक bit;
	पूर्णांक error;

	error = memory_bm_find_bit(bm, pfn, &addr, &bit);
	BUG_ON(error);
	set_bit(bit, addr);
पूर्ण

अटल पूर्णांक mem_bm_set_bit_check(काष्ठा memory_biपंचांगap *bm, अचिन्हित दीर्घ pfn)
अणु
	व्योम *addr;
	अचिन्हित पूर्णांक bit;
	पूर्णांक error;

	error = memory_bm_find_bit(bm, pfn, &addr, &bit);
	अगर (!error)
		set_bit(bit, addr);

	वापस error;
पूर्ण

अटल व्योम memory_bm_clear_bit(काष्ठा memory_biपंचांगap *bm, अचिन्हित दीर्घ pfn)
अणु
	व्योम *addr;
	अचिन्हित पूर्णांक bit;
	पूर्णांक error;

	error = memory_bm_find_bit(bm, pfn, &addr, &bit);
	BUG_ON(error);
	clear_bit(bit, addr);
पूर्ण

अटल व्योम memory_bm_clear_current(काष्ठा memory_biपंचांगap *bm)
अणु
	पूर्णांक bit;

	bit = max(bm->cur.node_bit - 1, 0);
	clear_bit(bit, bm->cur.node->data);
पूर्ण

अटल पूर्णांक memory_bm_test_bit(काष्ठा memory_biपंचांगap *bm, अचिन्हित दीर्घ pfn)
अणु
	व्योम *addr;
	अचिन्हित पूर्णांक bit;
	पूर्णांक error;

	error = memory_bm_find_bit(bm, pfn, &addr, &bit);
	BUG_ON(error);
	वापस test_bit(bit, addr);
पूर्ण

अटल bool memory_bm_pfn_present(काष्ठा memory_biपंचांगap *bm, अचिन्हित दीर्घ pfn)
अणु
	व्योम *addr;
	अचिन्हित पूर्णांक bit;

	वापस !memory_bm_find_bit(bm, pfn, &addr, &bit);
पूर्ण

/*
 * rtree_next_node - Jump to the next leaf node.
 *
 * Set the position to the beginning of the next node in the
 * memory biपंचांगap. This is either the next node in the current
 * zone's radix tree or the first node in the radix tree of the
 * next zone.
 *
 * Return true अगर there is a next node, false otherwise.
 */
अटल bool rtree_next_node(काष्ठा memory_biपंचांगap *bm)
अणु
	अगर (!list_is_last(&bm->cur.node->list, &bm->cur.zone->leaves)) अणु
		bm->cur.node = list_entry(bm->cur.node->list.next,
					  काष्ठा rtree_node, list);
		bm->cur.node_pfn += BM_BITS_PER_BLOCK;
		bm->cur.node_bit  = 0;
		touch_softlockup_watchकरोg();
		वापस true;
	पूर्ण

	/* No more nodes, जाओ next zone */
	अगर (!list_is_last(&bm->cur.zone->list, &bm->zones)) अणु
		bm->cur.zone = list_entry(bm->cur.zone->list.next,
				  काष्ठा mem_zone_bm_rtree, list);
		bm->cur.node = list_entry(bm->cur.zone->leaves.next,
					  काष्ठा rtree_node, list);
		bm->cur.node_pfn = 0;
		bm->cur.node_bit = 0;
		वापस true;
	पूर्ण

	/* No more zones */
	वापस false;
पूर्ण

/**
 * memory_bm_rtree_next_pfn - Find the next set bit in a memory biपंचांगap.
 * @bm: Memory biपंचांगap.
 *
 * Starting from the last वापसed position this function searches क्रम the next
 * set bit in @bm and वापसs the PFN represented by it.  If no more bits are
 * set, BM_END_OF_MAP is वापसed.
 *
 * It is required to run memory_bm_position_reset() beक्रमe the first call to
 * this function क्रम the given memory biपंचांगap.
 */
अटल अचिन्हित दीर्घ memory_bm_next_pfn(काष्ठा memory_biपंचांगap *bm)
अणु
	अचिन्हित दीर्घ bits, pfn, pages;
	पूर्णांक bit;

	करो अणु
		pages	  = bm->cur.zone->end_pfn - bm->cur.zone->start_pfn;
		bits      = min(pages - bm->cur.node_pfn, BM_BITS_PER_BLOCK);
		bit	  = find_next_bit(bm->cur.node->data, bits,
					  bm->cur.node_bit);
		अगर (bit < bits) अणु
			pfn = bm->cur.zone->start_pfn + bm->cur.node_pfn + bit;
			bm->cur.node_bit = bit + 1;
			वापस pfn;
		पूर्ण
	पूर्ण जबतक (rtree_next_node(bm));

	वापस BM_END_OF_MAP;
पूर्ण

/*
 * This काष्ठाure represents a range of page frames the contents of which
 * should not be saved during hibernation.
 */
काष्ठा nosave_region अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start_pfn;
	अचिन्हित दीर्घ end_pfn;
पूर्ण;

अटल LIST_HEAD(nosave_regions);

अटल व्योम recycle_zone_bm_rtree(काष्ठा mem_zone_bm_rtree *zone)
अणु
	काष्ठा rtree_node *node;

	list_क्रम_each_entry(node, &zone->nodes, list)
		recycle_safe_page(node->data);

	list_क्रम_each_entry(node, &zone->leaves, list)
		recycle_safe_page(node->data);
पूर्ण

अटल व्योम memory_bm_recycle(काष्ठा memory_biपंचांगap *bm)
अणु
	काष्ठा mem_zone_bm_rtree *zone;
	काष्ठा linked_page *p_list;

	list_क्रम_each_entry(zone, &bm->zones, list)
		recycle_zone_bm_rtree(zone);

	p_list = bm->p_list;
	जबतक (p_list) अणु
		काष्ठा linked_page *lp = p_list;

		p_list = lp->next;
		recycle_safe_page(lp);
	पूर्ण
पूर्ण

/**
 * रेजिस्टर_nosave_region - Register a region of unsaveable memory.
 *
 * Register a range of page frames the contents of which should not be saved
 * during hibernation (to be used in the early initialization code).
 */
व्योम __init __रेजिस्टर_nosave_region(अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ end_pfn, पूर्णांक use_kदो_स्मृति)
अणु
	काष्ठा nosave_region *region;

	अगर (start_pfn >= end_pfn)
		वापस;

	अगर (!list_empty(&nosave_regions)) अणु
		/* Try to extend the previous region (they should be sorted) */
		region = list_entry(nosave_regions.prev,
					काष्ठा nosave_region, list);
		अगर (region->end_pfn == start_pfn) अणु
			region->end_pfn = end_pfn;
			जाओ Report;
		पूर्ण
	पूर्ण
	अगर (use_kदो_स्मृति) अणु
		/* During init, this shouldn't fail */
		region = kदो_स्मृति(माप(काष्ठा nosave_region), GFP_KERNEL);
		BUG_ON(!region);
	पूर्ण अन्यथा अणु
		/* This allocation cannot fail */
		region = memblock_alloc(माप(काष्ठा nosave_region),
					SMP_CACHE_BYTES);
		अगर (!region)
			panic("%s: Failed to allocate %zu bytes\n", __func__,
			      माप(काष्ठा nosave_region));
	पूर्ण
	region->start_pfn = start_pfn;
	region->end_pfn = end_pfn;
	list_add_tail(&region->list, &nosave_regions);
 Report:
	pr_info("Registered nosave memory: [mem %#010llx-%#010llx]\n",
		(अचिन्हित दीर्घ दीर्घ) start_pfn << PAGE_SHIFT,
		((अचिन्हित दीर्घ दीर्घ) end_pfn << PAGE_SHIFT) - 1);
पूर्ण

/*
 * Set bits in this map correspond to the page frames the contents of which
 * should not be saved during the suspend.
 */
अटल काष्ठा memory_biपंचांगap *क्रमbidden_pages_map;

/* Set bits in this map correspond to मुक्त page frames. */
अटल काष्ठा memory_biपंचांगap *मुक्त_pages_map;

/*
 * Each page frame allocated क्रम creating the image is marked by setting the
 * corresponding bits in क्रमbidden_pages_map and मुक्त_pages_map simultaneously
 */

व्योम swsusp_set_page_मुक्त(काष्ठा page *page)
अणु
	अगर (मुक्त_pages_map)
		memory_bm_set_bit(मुक्त_pages_map, page_to_pfn(page));
पूर्ण

अटल पूर्णांक swsusp_page_is_मुक्त(काष्ठा page *page)
अणु
	वापस मुक्त_pages_map ?
		memory_bm_test_bit(मुक्त_pages_map, page_to_pfn(page)) : 0;
पूर्ण

व्योम swsusp_unset_page_मुक्त(काष्ठा page *page)
अणु
	अगर (मुक्त_pages_map)
		memory_bm_clear_bit(मुक्त_pages_map, page_to_pfn(page));
पूर्ण

अटल व्योम swsusp_set_page_क्रमbidden(काष्ठा page *page)
अणु
	अगर (क्रमbidden_pages_map)
		memory_bm_set_bit(क्रमbidden_pages_map, page_to_pfn(page));
पूर्ण

पूर्णांक swsusp_page_is_क्रमbidden(काष्ठा page *page)
अणु
	वापस क्रमbidden_pages_map ?
		memory_bm_test_bit(क्रमbidden_pages_map, page_to_pfn(page)) : 0;
पूर्ण

अटल व्योम swsusp_unset_page_क्रमbidden(काष्ठा page *page)
अणु
	अगर (क्रमbidden_pages_map)
		memory_bm_clear_bit(क्रमbidden_pages_map, page_to_pfn(page));
पूर्ण

/**
 * mark_nosave_pages - Mark pages that should not be saved.
 * @bm: Memory biपंचांगap.
 *
 * Set the bits in @bm that correspond to the page frames the contents of which
 * should not be saved.
 */
अटल व्योम mark_nosave_pages(काष्ठा memory_biपंचांगap *bm)
अणु
	काष्ठा nosave_region *region;

	अगर (list_empty(&nosave_regions))
		वापस;

	list_क्रम_each_entry(region, &nosave_regions, list) अणु
		अचिन्हित दीर्घ pfn;

		pr_debug("Marking nosave pages: [mem %#010llx-%#010llx]\n",
			 (अचिन्हित दीर्घ दीर्घ) region->start_pfn << PAGE_SHIFT,
			 ((अचिन्हित दीर्घ दीर्घ) region->end_pfn << PAGE_SHIFT)
				- 1);

		क्रम (pfn = region->start_pfn; pfn < region->end_pfn; pfn++)
			अगर (pfn_valid(pfn)) अणु
				/*
				 * It is safe to ignore the result of
				 * mem_bm_set_bit_check() here, since we won't
				 * touch the PFNs क्रम which the error is
				 * वापसed anyway.
				 */
				mem_bm_set_bit_check(bm, pfn);
			पूर्ण
	पूर्ण
पूर्ण

/**
 * create_basic_memory_biपंचांगaps - Create biपंचांगaps to hold basic page inक्रमmation.
 *
 * Create biपंचांगaps needed क्रम marking page frames that should not be saved and
 * मुक्त page frames.  The क्रमbidden_pages_map and मुक्त_pages_map poपूर्णांकers are
 * only modअगरied अगर everything goes well, because we करोn't want the bits to be
 * touched beक्रमe both biपंचांगaps are set up.
 */
पूर्णांक create_basic_memory_biपंचांगaps(व्योम)
अणु
	काष्ठा memory_biपंचांगap *bm1, *bm2;
	पूर्णांक error = 0;

	अगर (क्रमbidden_pages_map && मुक्त_pages_map)
		वापस 0;
	अन्यथा
		BUG_ON(क्रमbidden_pages_map || मुक्त_pages_map);

	bm1 = kzalloc(माप(काष्ठा memory_biपंचांगap), GFP_KERNEL);
	अगर (!bm1)
		वापस -ENOMEM;

	error = memory_bm_create(bm1, GFP_KERNEL, PG_ANY);
	अगर (error)
		जाओ Free_first_object;

	bm2 = kzalloc(माप(काष्ठा memory_biपंचांगap), GFP_KERNEL);
	अगर (!bm2)
		जाओ Free_first_biपंचांगap;

	error = memory_bm_create(bm2, GFP_KERNEL, PG_ANY);
	अगर (error)
		जाओ Free_second_object;

	क्रमbidden_pages_map = bm1;
	मुक्त_pages_map = bm2;
	mark_nosave_pages(क्रमbidden_pages_map);

	pr_debug("Basic memory bitmaps created\n");

	वापस 0;

 Free_second_object:
	kमुक्त(bm2);
 Free_first_biपंचांगap:
 	memory_bm_मुक्त(bm1, PG_UNSAFE_CLEAR);
 Free_first_object:
	kमुक्त(bm1);
	वापस -ENOMEM;
पूर्ण

/**
 * मुक्त_basic_memory_biपंचांगaps - Free memory biपंचांगaps holding basic inक्रमmation.
 *
 * Free memory biपंचांगaps allocated by create_basic_memory_biपंचांगaps().  The
 * auxiliary poपूर्णांकers are necessary so that the biपंचांगaps themselves are not
 * referred to जबतक they are being मुक्तd.
 */
व्योम मुक्त_basic_memory_biपंचांगaps(व्योम)
अणु
	काष्ठा memory_biपंचांगap *bm1, *bm2;

	अगर (WARN_ON(!(क्रमbidden_pages_map && मुक्त_pages_map)))
		वापस;

	bm1 = क्रमbidden_pages_map;
	bm2 = मुक्त_pages_map;
	क्रमbidden_pages_map = शून्य;
	मुक्त_pages_map = शून्य;
	memory_bm_मुक्त(bm1, PG_UNSAFE_CLEAR);
	kमुक्त(bm1);
	memory_bm_मुक्त(bm2, PG_UNSAFE_CLEAR);
	kमुक्त(bm2);

	pr_debug("Basic memory bitmaps freed\n");
पूर्ण

अटल व्योम clear_or_poison_मुक्त_page(काष्ठा page *page)
अणु
	अगर (page_poisoning_enabled_अटल())
		__kernel_poison_pages(page, 1);
	अन्यथा अगर (want_init_on_मुक्त())
		clear_highpage(page);
पूर्ण

व्योम clear_or_poison_मुक्त_pages(व्योम)
अणु
	काष्ठा memory_biपंचांगap *bm = मुक्त_pages_map;
	अचिन्हित दीर्घ pfn;

	अगर (WARN_ON(!(मुक्त_pages_map)))
		वापस;

	अगर (page_poisoning_enabled() || want_init_on_मुक्त()) अणु
		memory_bm_position_reset(bm);
		pfn = memory_bm_next_pfn(bm);
		जबतक (pfn != BM_END_OF_MAP) अणु
			अगर (pfn_valid(pfn))
				clear_or_poison_मुक्त_page(pfn_to_page(pfn));

			pfn = memory_bm_next_pfn(bm);
		पूर्ण
		memory_bm_position_reset(bm);
		pr_info("free pages cleared after restore\n");
	पूर्ण
पूर्ण

/**
 * snapshot_additional_pages - Estimate the number of extra pages needed.
 * @zone: Memory zone to carry out the computation क्रम.
 *
 * Estimate the number of additional pages needed क्रम setting up a hibernation
 * image data काष्ठाures क्रम @zone (usually, the वापसed value is greater than
 * the exact number).
 */
अचिन्हित पूर्णांक snapshot_additional_pages(काष्ठा zone *zone)
अणु
	अचिन्हित पूर्णांक rtree, nodes;

	rtree = nodes = DIV_ROUND_UP(zone->spanned_pages, BM_BITS_PER_BLOCK);
	rtree += DIV_ROUND_UP(rtree * माप(काष्ठा rtree_node),
			      LINKED_PAGE_DATA_SIZE);
	जबतक (nodes > 1) अणु
		nodes = DIV_ROUND_UP(nodes, BM_ENTRIES_PER_LEVEL);
		rtree += nodes;
	पूर्ण

	वापस 2 * rtree;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
/**
 * count_मुक्त_highmem_pages - Compute the total number of मुक्त highmem pages.
 *
 * The वापसed number is प्रणाली-wide.
 */
अटल अचिन्हित पूर्णांक count_मुक्त_highmem_pages(व्योम)
अणु
	काष्ठा zone *zone;
	अचिन्हित पूर्णांक cnt = 0;

	क्रम_each_populated_zone(zone)
		अगर (is_highmem(zone))
			cnt += zone_page_state(zone, NR_FREE_PAGES);

	वापस cnt;
पूर्ण

/**
 * saveable_highmem_page - Check अगर a highmem page is saveable.
 *
 * Determine whether a highmem page should be included in a hibernation image.
 *
 * We should save the page अगर it isn't Nosave or NosaveFree, or Reserved,
 * and it isn't part of a मुक्त chunk of pages.
 */
अटल काष्ठा page *saveable_highmem_page(काष्ठा zone *zone, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा page *page;

	अगर (!pfn_valid(pfn))
		वापस शून्य;

	page = pfn_to_online_page(pfn);
	अगर (!page || page_zone(page) != zone)
		वापस शून्य;

	BUG_ON(!PageHighMem(page));

	अगर (swsusp_page_is_क्रमbidden(page) ||  swsusp_page_is_मुक्त(page))
		वापस शून्य;

	अगर (PageReserved(page) || PageOffline(page))
		वापस शून्य;

	अगर (page_is_guard(page))
		वापस शून्य;

	वापस page;
पूर्ण

/**
 * count_highmem_pages - Compute the total number of saveable highmem pages.
 */
अटल अचिन्हित पूर्णांक count_highmem_pages(व्योम)
अणु
	काष्ठा zone *zone;
	अचिन्हित पूर्णांक n = 0;

	क्रम_each_populated_zone(zone) अणु
		अचिन्हित दीर्घ pfn, max_zone_pfn;

		अगर (!is_highmem(zone))
			जारी;

		mark_मुक्त_pages(zone);
		max_zone_pfn = zone_end_pfn(zone);
		क्रम (pfn = zone->zone_start_pfn; pfn < max_zone_pfn; pfn++)
			अगर (saveable_highmem_page(zone, pfn))
				n++;
	पूर्ण
	वापस n;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम *saveable_highmem_page(काष्ठा zone *z, अचिन्हित दीर्घ p)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

/**
 * saveable_page - Check अगर the given page is saveable.
 *
 * Determine whether a non-highmem page should be included in a hibernation
 * image.
 *
 * We should save the page अगर it isn't Nosave, and is not in the range
 * of pages अटलally defined as 'unsaveable', and it isn't part of
 * a मुक्त chunk of pages.
 */
अटल काष्ठा page *saveable_page(काष्ठा zone *zone, अचिन्हित दीर्घ pfn)
अणु
	काष्ठा page *page;

	अगर (!pfn_valid(pfn))
		वापस शून्य;

	page = pfn_to_online_page(pfn);
	अगर (!page || page_zone(page) != zone)
		वापस शून्य;

	BUG_ON(PageHighMem(page));

	अगर (swsusp_page_is_क्रमbidden(page) || swsusp_page_is_मुक्त(page))
		वापस शून्य;

	अगर (PageOffline(page))
		वापस शून्य;

	अगर (PageReserved(page)
	    && (!kernel_page_present(page) || pfn_is_nosave(pfn)))
		वापस शून्य;

	अगर (page_is_guard(page))
		वापस शून्य;

	वापस page;
पूर्ण

/**
 * count_data_pages - Compute the total number of saveable non-highmem pages.
 */
अटल अचिन्हित पूर्णांक count_data_pages(व्योम)
अणु
	काष्ठा zone *zone;
	अचिन्हित दीर्घ pfn, max_zone_pfn;
	अचिन्हित पूर्णांक n = 0;

	क्रम_each_populated_zone(zone) अणु
		अगर (is_highmem(zone))
			जारी;

		mark_मुक्त_pages(zone);
		max_zone_pfn = zone_end_pfn(zone);
		क्रम (pfn = zone->zone_start_pfn; pfn < max_zone_pfn; pfn++)
			अगर (saveable_page(zone, pfn))
				n++;
	पूर्ण
	वापस n;
पूर्ण

/*
 * This is needed, because copy_page and स_नकल are not usable क्रम copying
 * task काष्ठाs.
 */
अटल अंतरभूत व्योम करो_copy_page(दीर्घ *dst, दीर्घ *src)
अणु
	पूर्णांक n;

	क्रम (n = PAGE_SIZE / माप(दीर्घ); n; n--)
		*dst++ = *src++;
पूर्ण

/**
 * safe_copy_page - Copy a page in a safe way.
 *
 * Check अगर the page we are going to copy is marked as present in the kernel
 * page tables. This always is the हाल अगर CONFIG_DEBUG_PAGEALLOC or
 * CONFIG_ARCH_HAS_SET_सूचीECT_MAP is not set. In that हाल kernel_page_present()
 * always वापसs 'true'.
 */
अटल व्योम safe_copy_page(व्योम *dst, काष्ठा page *s_page)
अणु
	अगर (kernel_page_present(s_page)) अणु
		करो_copy_page(dst, page_address(s_page));
	पूर्ण अन्यथा अणु
		hibernate_map_page(s_page);
		करो_copy_page(dst, page_address(s_page));
		hibernate_unmap_page(s_page);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
अटल अंतरभूत काष्ठा page *page_is_saveable(काष्ठा zone *zone, अचिन्हित दीर्घ pfn)
अणु
	वापस is_highmem(zone) ?
		saveable_highmem_page(zone, pfn) : saveable_page(zone, pfn);
पूर्ण

अटल व्योम copy_data_page(अचिन्हित दीर्घ dst_pfn, अचिन्हित दीर्घ src_pfn)
अणु
	काष्ठा page *s_page, *d_page;
	व्योम *src, *dst;

	s_page = pfn_to_page(src_pfn);
	d_page = pfn_to_page(dst_pfn);
	अगर (PageHighMem(s_page)) अणु
		src = kmap_atomic(s_page);
		dst = kmap_atomic(d_page);
		करो_copy_page(dst, src);
		kunmap_atomic(dst);
		kunmap_atomic(src);
	पूर्ण अन्यथा अणु
		अगर (PageHighMem(d_page)) अणु
			/*
			 * The page poपूर्णांकed to by src may contain some kernel
			 * data modअगरied by kmap_atomic()
			 */
			safe_copy_page(buffer, s_page);
			dst = kmap_atomic(d_page);
			copy_page(dst, buffer);
			kunmap_atomic(dst);
		पूर्ण अन्यथा अणु
			safe_copy_page(page_address(d_page), s_page);
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा page_is_saveable(zone, pfn)	saveable_page(zone, pfn)

अटल अंतरभूत व्योम copy_data_page(अचिन्हित दीर्घ dst_pfn, अचिन्हित दीर्घ src_pfn)
अणु
	safe_copy_page(page_address(pfn_to_page(dst_pfn)),
				pfn_to_page(src_pfn));
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

अटल व्योम copy_data_pages(काष्ठा memory_biपंचांगap *copy_bm,
			    काष्ठा memory_biपंचांगap *orig_bm)
अणु
	काष्ठा zone *zone;
	अचिन्हित दीर्घ pfn;

	क्रम_each_populated_zone(zone) अणु
		अचिन्हित दीर्घ max_zone_pfn;

		mark_मुक्त_pages(zone);
		max_zone_pfn = zone_end_pfn(zone);
		क्रम (pfn = zone->zone_start_pfn; pfn < max_zone_pfn; pfn++)
			अगर (page_is_saveable(zone, pfn))
				memory_bm_set_bit(orig_bm, pfn);
	पूर्ण
	memory_bm_position_reset(orig_bm);
	memory_bm_position_reset(copy_bm);
	क्रम(;;) अणु
		pfn = memory_bm_next_pfn(orig_bm);
		अगर (unlikely(pfn == BM_END_OF_MAP))
			अवरोध;
		copy_data_page(memory_bm_next_pfn(copy_bm), pfn);
	पूर्ण
पूर्ण

/* Total number of image pages */
अटल अचिन्हित पूर्णांक nr_copy_pages;
/* Number of pages needed क्रम saving the original pfns of the image pages */
अटल अचिन्हित पूर्णांक nr_meta_pages;
/*
 * Numbers of normal and highmem page frames allocated क्रम hibernation image
 * beक्रमe suspending devices.
 */
अटल अचिन्हित पूर्णांक alloc_normal, alloc_highmem;
/*
 * Memory biपंचांगap used क्रम marking saveable pages (during hibernation) or
 * hibernation image pages (during restore)
 */
अटल काष्ठा memory_biपंचांगap orig_bm;
/*
 * Memory biपंचांगap used during hibernation क्रम marking allocated page frames that
 * will contain copies of saveable pages.  During restore it is initially used
 * क्रम marking hibernation image pages, but then the set bits from it are
 * duplicated in @orig_bm and it is released.  On highmem प्रणालीs it is next
 * used क्रम marking "safe" highmem pages, but it has to be reinitialized क्रम
 * this purpose.
 */
अटल काष्ठा memory_biपंचांगap copy_bm;

/**
 * swsusp_मुक्त - Free pages allocated क्रम hibernation image.
 *
 * Image pages are alocated beक्रमe snapshot creation, so they need to be
 * released after resume.
 */
व्योम swsusp_मुक्त(व्योम)
अणु
	अचिन्हित दीर्घ fb_pfn, fr_pfn;

	अगर (!क्रमbidden_pages_map || !मुक्त_pages_map)
		जाओ out;

	memory_bm_position_reset(क्रमbidden_pages_map);
	memory_bm_position_reset(मुक्त_pages_map);

loop:
	fr_pfn = memory_bm_next_pfn(मुक्त_pages_map);
	fb_pfn = memory_bm_next_pfn(क्रमbidden_pages_map);

	/*
	 * Find the next bit set in both biपंचांगaps. This is guaranteed to
	 * terminate when fb_pfn == fr_pfn == BM_END_OF_MAP.
	 */
	करो अणु
		अगर (fb_pfn < fr_pfn)
			fb_pfn = memory_bm_next_pfn(क्रमbidden_pages_map);
		अगर (fr_pfn < fb_pfn)
			fr_pfn = memory_bm_next_pfn(मुक्त_pages_map);
	पूर्ण जबतक (fb_pfn != fr_pfn);

	अगर (fr_pfn != BM_END_OF_MAP && pfn_valid(fr_pfn)) अणु
		काष्ठा page *page = pfn_to_page(fr_pfn);

		memory_bm_clear_current(क्रमbidden_pages_map);
		memory_bm_clear_current(मुक्त_pages_map);
		hibernate_restore_unprotect_page(page_address(page));
		__मुक्त_page(page);
		जाओ loop;
	पूर्ण

out:
	nr_copy_pages = 0;
	nr_meta_pages = 0;
	restore_pblist = शून्य;
	buffer = शून्य;
	alloc_normal = 0;
	alloc_highmem = 0;
	hibernate_restore_protection_end();
पूर्ण

/* Helper functions used क्रम the shrinking of memory. */

#घोषणा GFP_IMAGE	(GFP_KERNEL | __GFP_NOWARN)

/**
 * pपुनः_स्मृतिate_image_pages - Allocate a number of pages क्रम hibernation image.
 * @nr_pages: Number of page frames to allocate.
 * @mask: GFP flags to use क्रम the allocation.
 *
 * Return value: Number of page frames actually allocated
 */
अटल अचिन्हित दीर्घ pपुनः_स्मृतिate_image_pages(अचिन्हित दीर्घ nr_pages, gfp_t mask)
अणु
	अचिन्हित दीर्घ nr_alloc = 0;

	जबतक (nr_pages > 0) अणु
		काष्ठा page *page;

		page = alloc_image_page(mask);
		अगर (!page)
			अवरोध;
		memory_bm_set_bit(&copy_bm, page_to_pfn(page));
		अगर (PageHighMem(page))
			alloc_highmem++;
		अन्यथा
			alloc_normal++;
		nr_pages--;
		nr_alloc++;
	पूर्ण

	वापस nr_alloc;
पूर्ण

अटल अचिन्हित दीर्घ pपुनः_स्मृतिate_image_memory(अचिन्हित दीर्घ nr_pages,
					      अचिन्हित दीर्घ avail_normal)
अणु
	अचिन्हित दीर्घ alloc;

	अगर (avail_normal <= alloc_normal)
		वापस 0;

	alloc = avail_normal - alloc_normal;
	अगर (nr_pages < alloc)
		alloc = nr_pages;

	वापस pपुनः_स्मृतिate_image_pages(alloc, GFP_IMAGE);
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
अटल अचिन्हित दीर्घ pपुनः_स्मृतिate_image_highmem(अचिन्हित दीर्घ nr_pages)
अणु
	वापस pपुनः_स्मृतिate_image_pages(nr_pages, GFP_IMAGE | __GFP_HIGHMEM);
पूर्ण

/**
 *  __fraction - Compute (an approximation of) x * (multiplier / base).
 */
अटल अचिन्हित दीर्घ __fraction(u64 x, u64 multiplier, u64 base)
अणु
	वापस भाग64_u64(x * multiplier, base);
पूर्ण

अटल अचिन्हित दीर्घ pपुनः_स्मृतिate_highmem_fraction(अचिन्हित दीर्घ nr_pages,
						  अचिन्हित दीर्घ highmem,
						  अचिन्हित दीर्घ total)
अणु
	अचिन्हित दीर्घ alloc = __fraction(nr_pages, highmem, total);

	वापस pपुनः_स्मृतिate_image_pages(alloc, GFP_IMAGE | __GFP_HIGHMEM);
पूर्ण
#अन्यथा /* CONFIG_HIGHMEM */
अटल अंतरभूत अचिन्हित दीर्घ pपुनः_स्मृतिate_image_highmem(अचिन्हित दीर्घ nr_pages)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pपुनः_स्मृतिate_highmem_fraction(अचिन्हित दीर्घ nr_pages,
							 अचिन्हित दीर्घ highmem,
							 अचिन्हित दीर्घ total)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

/**
 * मुक्त_unnecessary_pages - Release pपुनः_स्मृतिated pages not needed क्रम the image.
 */
अटल अचिन्हित दीर्घ मुक्त_unnecessary_pages(व्योम)
अणु
	अचिन्हित दीर्घ save, to_मुक्त_normal, to_मुक्त_highmem, मुक्त;

	save = count_data_pages();
	अगर (alloc_normal >= save) अणु
		to_मुक्त_normal = alloc_normal - save;
		save = 0;
	पूर्ण अन्यथा अणु
		to_मुक्त_normal = 0;
		save -= alloc_normal;
	पूर्ण
	save += count_highmem_pages();
	अगर (alloc_highmem >= save) अणु
		to_मुक्त_highmem = alloc_highmem - save;
	पूर्ण अन्यथा अणु
		to_मुक्त_highmem = 0;
		save -= alloc_highmem;
		अगर (to_मुक्त_normal > save)
			to_मुक्त_normal -= save;
		अन्यथा
			to_मुक्त_normal = 0;
	पूर्ण
	मुक्त = to_मुक्त_normal + to_मुक्त_highmem;

	memory_bm_position_reset(&copy_bm);

	जबतक (to_मुक्त_normal > 0 || to_मुक्त_highmem > 0) अणु
		अचिन्हित दीर्घ pfn = memory_bm_next_pfn(&copy_bm);
		काष्ठा page *page = pfn_to_page(pfn);

		अगर (PageHighMem(page)) अणु
			अगर (!to_मुक्त_highmem)
				जारी;
			to_मुक्त_highmem--;
			alloc_highmem--;
		पूर्ण अन्यथा अणु
			अगर (!to_मुक्त_normal)
				जारी;
			to_मुक्त_normal--;
			alloc_normal--;
		पूर्ण
		memory_bm_clear_bit(&copy_bm, pfn);
		swsusp_unset_page_क्रमbidden(page);
		swsusp_unset_page_मुक्त(page);
		__मुक्त_page(page);
	पूर्ण

	वापस मुक्त;
पूर्ण

/**
 * minimum_image_size - Estimate the minimum acceptable size of an image.
 * @saveable: Number of saveable pages in the प्रणाली.
 *
 * We want to aव्योम attempting to मुक्त too much memory too hard, so estimate the
 * minimum acceptable size of a hibernation image to use as the lower limit क्रम
 * pपुनः_स्मृतिating memory.
 *
 * We assume that the minimum image size should be proportional to
 *
 * [number of saveable pages] - [number of pages that can be मुक्तd in theory]
 *
 * where the second term is the sum of (1) reclaimable slab pages, (2) active
 * and (3) inactive anonymous pages, (4) active and (5) inactive file pages.
 */
अटल अचिन्हित दीर्घ minimum_image_size(अचिन्हित दीर्घ saveable)
अणु
	अचिन्हित दीर्घ size;

	size = global_node_page_state_pages(NR_SLAB_RECLAIMABLE_B)
		+ global_node_page_state(NR_ACTIVE_ANON)
		+ global_node_page_state(NR_INACTIVE_ANON)
		+ global_node_page_state(NR_ACTIVE_खाता)
		+ global_node_page_state(NR_INACTIVE_खाता);

	वापस saveable <= size ? 0 : saveable - size;
पूर्ण

/**
 * hibernate_pपुनः_स्मृतिate_memory - Pपुनः_स्मृतिate memory क्रम hibernation image.
 *
 * To create a hibernation image it is necessary to make a copy of every page
 * frame in use.  We also need a number of page frames to be मुक्त during
 * hibernation क्रम allocations made जबतक saving the image and क्रम device
 * drivers, in हाल they need to allocate memory from their hibernation
 * callbacks (these two numbers are given by PAGES_FOR_IO (which is a rough
 * estimate) and reserved_size भागided by PAGE_SIZE (which is tunable through
 * /sys/घातer/reserved_size, respectively).  To make this happen, we compute the
 * total number of available page frames and allocate at least
 *
 * ([page frames total] + PAGES_FOR_IO + [metadata pages]) / 2
 *  + 2 * DIV_ROUND_UP(reserved_size, PAGE_SIZE)
 *
 * of them, which corresponds to the maximum size of a hibernation image.
 *
 * If image_size is set below the number following from the above क्रमmula,
 * the pपुनः_स्मृतिation of memory is जारीd until the total number of saveable
 * pages in the प्रणाली is below the requested image size or the minimum
 * acceptable image size वापसed by minimum_image_size(), whichever is greater.
 */
पूर्णांक hibernate_pपुनः_स्मृतिate_memory(व्योम)
अणु
	काष्ठा zone *zone;
	अचिन्हित दीर्घ saveable, size, max_size, count, highmem, pages = 0;
	अचिन्हित दीर्घ alloc, save_highmem, pages_highmem, avail_normal;
	kसमय_प्रकार start, stop;
	पूर्णांक error;

	pr_info("Preallocating image memory\n");
	start = kसमय_get();

	error = memory_bm_create(&orig_bm, GFP_IMAGE, PG_ANY);
	अगर (error) अणु
		pr_err("Cannot allocate original bitmap\n");
		जाओ err_out;
	पूर्ण

	error = memory_bm_create(&copy_bm, GFP_IMAGE, PG_ANY);
	अगर (error) अणु
		pr_err("Cannot allocate copy bitmap\n");
		जाओ err_out;
	पूर्ण

	alloc_normal = 0;
	alloc_highmem = 0;

	/* Count the number of saveable data pages. */
	save_highmem = count_highmem_pages();
	saveable = count_data_pages();

	/*
	 * Compute the total number of page frames we can use (count) and the
	 * number of pages needed क्रम image metadata (size).
	 */
	count = saveable;
	saveable += save_highmem;
	highmem = save_highmem;
	size = 0;
	क्रम_each_populated_zone(zone) अणु
		size += snapshot_additional_pages(zone);
		अगर (is_highmem(zone))
			highmem += zone_page_state(zone, NR_FREE_PAGES);
		अन्यथा
			count += zone_page_state(zone, NR_FREE_PAGES);
	पूर्ण
	avail_normal = count;
	count += highmem;
	count -= totalreserve_pages;

	/* Compute the maximum number of saveable pages to leave in memory. */
	max_size = (count - (size + PAGES_FOR_IO)) / 2
			- 2 * DIV_ROUND_UP(reserved_size, PAGE_SIZE);
	/* Compute the desired number of image pages specअगरied by image_size. */
	size = DIV_ROUND_UP(image_size, PAGE_SIZE);
	अगर (size > max_size)
		size = max_size;
	/*
	 * If the desired number of image pages is at least as large as the
	 * current number of saveable pages in memory, allocate page frames क्रम
	 * the image and we're करोne.
	 */
	अगर (size >= saveable) अणु
		pages = pपुनः_स्मृतिate_image_highmem(save_highmem);
		pages += pपुनः_स्मृतिate_image_memory(saveable - pages, avail_normal);
		जाओ out;
	पूर्ण

	/* Estimate the minimum size of the image. */
	pages = minimum_image_size(saveable);
	/*
	 * To aव्योम excessive pressure on the normal zone, leave room in it to
	 * accommodate an image of the minimum size (unless it's alपढ़ोy too
	 * small, in which हाल करोn't pपुनः_स्मृतिate pages from it at all).
	 */
	अगर (avail_normal > pages)
		avail_normal -= pages;
	अन्यथा
		avail_normal = 0;
	अगर (size < pages)
		size = min_t(अचिन्हित दीर्घ, pages, max_size);

	/*
	 * Let the memory management subप्रणाली know that we're going to need a
	 * large number of page frames to allocate and make it मुक्त some memory.
	 * NOTE: If this is not करोne, perक्रमmance will be hurt badly in some
	 * test हालs.
	 */
	shrink_all_memory(saveable - size);

	/*
	 * The number of saveable pages in memory was too high, so apply some
	 * pressure to decrease it.  First, make room क्रम the largest possible
	 * image and fail अगर that करोesn't work.  Next, try to decrease the size
	 * of the image as much as indicated by 'size' using allocations from
	 * highmem and non-highmem zones separately.
	 */
	pages_highmem = pपुनः_स्मृतिate_image_highmem(highmem / 2);
	alloc = count - max_size;
	अगर (alloc > pages_highmem)
		alloc -= pages_highmem;
	अन्यथा
		alloc = 0;
	pages = pपुनः_स्मृतिate_image_memory(alloc, avail_normal);
	अगर (pages < alloc) अणु
		/* We have exhausted non-highmem pages, try highmem. */
		alloc -= pages;
		pages += pages_highmem;
		pages_highmem = pपुनः_स्मृतिate_image_highmem(alloc);
		अगर (pages_highmem < alloc) अणु
			pr_err("Image allocation is %lu pages short\n",
				alloc - pages_highmem);
			जाओ err_out;
		पूर्ण
		pages += pages_highmem;
		/*
		 * size is the desired number of saveable pages to leave in
		 * memory, so try to pपुनः_स्मृतिate (all memory - size) pages.
		 */
		alloc = (count - pages) - size;
		pages += pपुनः_स्मृतिate_image_highmem(alloc);
	पूर्ण अन्यथा अणु
		/*
		 * There are approximately max_size saveable pages at this poपूर्णांक
		 * and we want to reduce this number करोwn to size.
		 */
		alloc = max_size - size;
		size = pपुनः_स्मृतिate_highmem_fraction(alloc, highmem, count);
		pages_highmem += size;
		alloc -= size;
		size = pपुनः_स्मृतिate_image_memory(alloc, avail_normal);
		pages_highmem += pपुनः_स्मृतिate_image_highmem(alloc - size);
		pages += pages_highmem + size;
	पूर्ण

	/*
	 * We only need as many page frames क्रम the image as there are saveable
	 * pages in memory, but we have allocated more.  Release the excessive
	 * ones now.
	 */
	pages -= मुक्त_unnecessary_pages();

 out:
	stop = kसमय_get();
	pr_info("Allocated %lu pages for snapshot\n", pages);
	swsusp_show_speed(start, stop, pages, "Allocated");

	वापस 0;

 err_out:
	swsusp_मुक्त();
	वापस -ENOMEM;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
/**
 * count_pages_क्रम_highmem - Count non-highmem pages needed क्रम copying highmem.
 *
 * Compute the number of non-highmem pages that will be necessary क्रम creating
 * copies of highmem pages.
 */
अटल अचिन्हित पूर्णांक count_pages_क्रम_highmem(अचिन्हित पूर्णांक nr_highmem)
अणु
	अचिन्हित पूर्णांक मुक्त_highmem = count_मुक्त_highmem_pages() + alloc_highmem;

	अगर (मुक्त_highmem >= nr_highmem)
		nr_highmem = 0;
	अन्यथा
		nr_highmem -= मुक्त_highmem;

	वापस nr_highmem;
पूर्ण
#अन्यथा
अटल अचिन्हित पूर्णांक count_pages_क्रम_highmem(अचिन्हित पूर्णांक nr_highmem) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

/**
 * enough_मुक्त_mem - Check अगर there is enough मुक्त memory क्रम the image.
 */
अटल पूर्णांक enough_मुक्त_mem(अचिन्हित पूर्णांक nr_pages, अचिन्हित पूर्णांक nr_highmem)
अणु
	काष्ठा zone *zone;
	अचिन्हित पूर्णांक मुक्त = alloc_normal;

	क्रम_each_populated_zone(zone)
		अगर (!is_highmem(zone))
			मुक्त += zone_page_state(zone, NR_FREE_PAGES);

	nr_pages += count_pages_क्रम_highmem(nr_highmem);
	pr_debug("Normal pages needed: %u + %u, available pages: %u\n",
		 nr_pages, PAGES_FOR_IO, मुक्त);

	वापस मुक्त > nr_pages + PAGES_FOR_IO;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
/**
 * get_highmem_buffer - Allocate a buffer क्रम highmem pages.
 *
 * If there are some highmem pages in the hibernation image, we may need a
 * buffer to copy them and/or load their data.
 */
अटल अंतरभूत पूर्णांक get_highmem_buffer(पूर्णांक safe_needed)
अणु
	buffer = get_image_page(GFP_ATOMIC, safe_needed);
	वापस buffer ? 0 : -ENOMEM;
पूर्ण

/**
 * alloc_highmem_image_pages - Allocate some highmem pages क्रम the image.
 *
 * Try to allocate as many pages as needed, but अगर the number of मुक्त highmem
 * pages is less than that, allocate them all.
 */
अटल अंतरभूत अचिन्हित पूर्णांक alloc_highmem_pages(काष्ठा memory_biपंचांगap *bm,
					       अचिन्हित पूर्णांक nr_highmem)
अणु
	अचिन्हित पूर्णांक to_alloc = count_मुक्त_highmem_pages();

	अगर (to_alloc > nr_highmem)
		to_alloc = nr_highmem;

	nr_highmem -= to_alloc;
	जबतक (to_alloc-- > 0) अणु
		काष्ठा page *page;

		page = alloc_image_page(__GFP_HIGHMEM|__GFP_KSWAPD_RECLAIM);
		memory_bm_set_bit(bm, page_to_pfn(page));
	पूर्ण
	वापस nr_highmem;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक get_highmem_buffer(पूर्णांक safe_needed) अणु वापस 0; पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक alloc_highmem_pages(काष्ठा memory_biपंचांगap *bm,
					       अचिन्हित पूर्णांक n) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

/**
 * swsusp_alloc - Allocate memory क्रम hibernation image.
 *
 * We first try to allocate as many highmem pages as there are
 * saveable highmem pages in the प्रणाली.  If that fails, we allocate
 * non-highmem pages क्रम the copies of the reमुख्यing highmem ones.
 *
 * In this approach it is likely that the copies of highmem pages will
 * also be located in the high memory, because of the way in which
 * copy_data_pages() works.
 */
अटल पूर्णांक swsusp_alloc(काष्ठा memory_biपंचांगap *copy_bm,
			अचिन्हित पूर्णांक nr_pages, अचिन्हित पूर्णांक nr_highmem)
अणु
	अगर (nr_highmem > 0) अणु
		अगर (get_highmem_buffer(PG_ANY))
			जाओ err_out;
		अगर (nr_highmem > alloc_highmem) अणु
			nr_highmem -= alloc_highmem;
			nr_pages += alloc_highmem_pages(copy_bm, nr_highmem);
		पूर्ण
	पूर्ण
	अगर (nr_pages > alloc_normal) अणु
		nr_pages -= alloc_normal;
		जबतक (nr_pages-- > 0) अणु
			काष्ठा page *page;

			page = alloc_image_page(GFP_ATOMIC);
			अगर (!page)
				जाओ err_out;
			memory_bm_set_bit(copy_bm, page_to_pfn(page));
		पूर्ण
	पूर्ण

	वापस 0;

 err_out:
	swsusp_मुक्त();
	वापस -ENOMEM;
पूर्ण

यंत्रlinkage __visible पूर्णांक swsusp_save(व्योम)
अणु
	अचिन्हित पूर्णांक nr_pages, nr_highmem;

	pr_info("Creating image:\n");

	drain_local_pages(शून्य);
	nr_pages = count_data_pages();
	nr_highmem = count_highmem_pages();
	pr_info("Need to copy %u pages\n", nr_pages + nr_highmem);

	अगर (!enough_मुक्त_mem(nr_pages, nr_highmem)) अणु
		pr_err("Not enough free memory\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (swsusp_alloc(&copy_bm, nr_pages, nr_highmem)) अणु
		pr_err("Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * During allocating of suspend pagedir, new cold pages may appear.
	 * Kill them.
	 */
	drain_local_pages(शून्य);
	copy_data_pages(&copy_bm, &orig_bm);

	/*
	 * End of critical section. From now on, we can ग_लिखो to memory,
	 * but we should not touch disk. This specially means we must _not_
	 * touch swap space! Except we must ग_लिखो out our image of course.
	 */

	nr_pages += nr_highmem;
	nr_copy_pages = nr_pages;
	nr_meta_pages = DIV_ROUND_UP(nr_pages * माप(दीर्घ), PAGE_SIZE);

	pr_info("Image created (%d pages copied)\n", nr_pages);

	वापस 0;
पूर्ण

#अगर_अघोषित CONFIG_ARCH_HIBERNATION_HEADER
अटल पूर्णांक init_header_complete(काष्ठा swsusp_info *info)
अणु
	स_नकल(&info->uts, init_utsname(), माप(काष्ठा new_utsname));
	info->version_code = LINUX_VERSION_CODE;
	वापस 0;
पूर्ण

अटल स्थिर अक्षर *check_image_kernel(काष्ठा swsusp_info *info)
अणु
	अगर (info->version_code != LINUX_VERSION_CODE)
		वापस "kernel version";
	अगर (म_भेद(info->uts.sysname,init_utsname()->sysname))
		वापस "system type";
	अगर (म_भेद(info->uts.release,init_utsname()->release))
		वापस "kernel release";
	अगर (म_भेद(info->uts.version,init_utsname()->version))
		वापस "version";
	अगर (म_भेद(info->uts.machine,init_utsname()->machine))
		वापस "machine";
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HIBERNATION_HEADER */

अचिन्हित दीर्घ snapshot_get_image_size(व्योम)
अणु
	वापस nr_copy_pages + nr_meta_pages + 1;
पूर्ण

अटल पूर्णांक init_header(काष्ठा swsusp_info *info)
अणु
	स_रखो(info, 0, माप(काष्ठा swsusp_info));
	info->num_physpages = get_num_physpages();
	info->image_pages = nr_copy_pages;
	info->pages = snapshot_get_image_size();
	info->size = info->pages;
	info->size <<= PAGE_SHIFT;
	वापस init_header_complete(info);
पूर्ण

/**
 * pack_pfns - Prepare PFNs क्रम saving.
 * @bm: Memory biपंचांगap.
 * @buf: Memory buffer to store the PFNs in.
 *
 * PFNs corresponding to set bits in @bm are stored in the area of memory
 * poपूर्णांकed to by @buf (1 page at a समय).
 */
अटल अंतरभूत व्योम pack_pfns(अचिन्हित दीर्घ *buf, काष्ठा memory_biपंचांगap *bm)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < PAGE_SIZE / माप(दीर्घ); j++) अणु
		buf[j] = memory_bm_next_pfn(bm);
		अगर (unlikely(buf[j] == BM_END_OF_MAP))
			अवरोध;
	पूर्ण
पूर्ण

/**
 * snapshot_पढ़ो_next - Get the address to पढ़ो the next image page from.
 * @handle: Snapshot handle to be used क्रम the पढ़ोing.
 *
 * On the first call, @handle should poपूर्णांक to a zeroed snapshot_handle
 * काष्ठाure.  The काष्ठाure माला_लो populated then and a poपूर्णांकer to it should be
 * passed to this function every next समय.
 *
 * On success, the function वापसs a positive number.  Then, the caller
 * is allowed to पढ़ो up to the वापसed number of bytes from the memory
 * location computed by the data_of() macro.
 *
 * The function वापसs 0 to indicate the end of the data stream condition,
 * and negative numbers are वापसed on errors.  If that happens, the काष्ठाure
 * poपूर्णांकed to by @handle is not updated and should not be used any more.
 */
पूर्णांक snapshot_पढ़ो_next(काष्ठा snapshot_handle *handle)
अणु
	अगर (handle->cur > nr_meta_pages + nr_copy_pages)
		वापस 0;

	अगर (!buffer) अणु
		/* This makes the buffer be मुक्तd by swsusp_मुक्त() */
		buffer = get_image_page(GFP_ATOMIC, PG_ANY);
		अगर (!buffer)
			वापस -ENOMEM;
	पूर्ण
	अगर (!handle->cur) अणु
		पूर्णांक error;

		error = init_header((काष्ठा swsusp_info *)buffer);
		अगर (error)
			वापस error;
		handle->buffer = buffer;
		memory_bm_position_reset(&orig_bm);
		memory_bm_position_reset(&copy_bm);
	पूर्ण अन्यथा अगर (handle->cur <= nr_meta_pages) अणु
		clear_page(buffer);
		pack_pfns(buffer, &orig_bm);
	पूर्ण अन्यथा अणु
		काष्ठा page *page;

		page = pfn_to_page(memory_bm_next_pfn(&copy_bm));
		अगर (PageHighMem(page)) अणु
			/*
			 * Highmem pages are copied to the buffer,
			 * because we can't वापस with a kmapped
			 * highmem page (we may not be called again).
			 */
			व्योम *kaddr;

			kaddr = kmap_atomic(page);
			copy_page(buffer, kaddr);
			kunmap_atomic(kaddr);
			handle->buffer = buffer;
		पूर्ण अन्यथा अणु
			handle->buffer = page_address(page);
		पूर्ण
	पूर्ण
	handle->cur++;
	वापस PAGE_SIZE;
पूर्ण

अटल व्योम duplicate_memory_biपंचांगap(काष्ठा memory_biपंचांगap *dst,
				    काष्ठा memory_biपंचांगap *src)
अणु
	अचिन्हित दीर्घ pfn;

	memory_bm_position_reset(src);
	pfn = memory_bm_next_pfn(src);
	जबतक (pfn != BM_END_OF_MAP) अणु
		memory_bm_set_bit(dst, pfn);
		pfn = memory_bm_next_pfn(src);
	पूर्ण
पूर्ण

/**
 * mark_unsafe_pages - Mark pages that were used beक्रमe hibernation.
 *
 * Mark the pages that cannot be used क्रम storing the image during restoration,
 * because they conflict with the pages that had been used beक्रमe hibernation.
 */
अटल व्योम mark_unsafe_pages(काष्ठा memory_biपंचांगap *bm)
अणु
	अचिन्हित दीर्घ pfn;

	/* Clear the "free"/"unsafe" bit क्रम all PFNs */
	memory_bm_position_reset(मुक्त_pages_map);
	pfn = memory_bm_next_pfn(मुक्त_pages_map);
	जबतक (pfn != BM_END_OF_MAP) अणु
		memory_bm_clear_current(मुक्त_pages_map);
		pfn = memory_bm_next_pfn(मुक्त_pages_map);
	पूर्ण

	/* Mark pages that correspond to the "original" PFNs as "unsafe" */
	duplicate_memory_biपंचांगap(मुक्त_pages_map, bm);

	allocated_unsafe_pages = 0;
पूर्ण

अटल पूर्णांक check_header(काष्ठा swsusp_info *info)
अणु
	स्थिर अक्षर *reason;

	reason = check_image_kernel(info);
	अगर (!reason && info->num_physpages != get_num_physpages())
		reason = "memory size";
	अगर (reason) अणु
		pr_err("Image mismatch: %s\n", reason);
		वापस -EPERM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * load header - Check the image header and copy the data from it.
 */
अटल पूर्णांक load_header(काष्ठा swsusp_info *info)
अणु
	पूर्णांक error;

	restore_pblist = शून्य;
	error = check_header(info);
	अगर (!error) अणु
		nr_copy_pages = info->image_pages;
		nr_meta_pages = info->pages - info->image_pages - 1;
	पूर्ण
	वापस error;
पूर्ण

/**
 * unpack_orig_pfns - Set bits corresponding to given PFNs in a memory biपंचांगap.
 * @bm: Memory biपंचांगap.
 * @buf: Area of memory containing the PFNs.
 *
 * For each element of the array poपूर्णांकed to by @buf (1 page at a समय), set the
 * corresponding bit in @bm.
 */
अटल पूर्णांक unpack_orig_pfns(अचिन्हित दीर्घ *buf, काष्ठा memory_biपंचांगap *bm)
अणु
	पूर्णांक j;

	क्रम (j = 0; j < PAGE_SIZE / माप(दीर्घ); j++) अणु
		अगर (unlikely(buf[j] == BM_END_OF_MAP))
			अवरोध;

		अगर (pfn_valid(buf[j]) && memory_bm_pfn_present(bm, buf[j]))
			memory_bm_set_bit(bm, buf[j]);
		अन्यथा
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
/*
 * काष्ठा highmem_pbe is used क्रम creating the list of highmem pages that
 * should be restored atomically during the resume from disk, because the page
 * frames they have occupied beक्रमe the suspend are in use.
 */
काष्ठा highmem_pbe अणु
	काष्ठा page *copy_page;	/* data is here now */
	काष्ठा page *orig_page;	/* data was here beक्रमe the suspend */
	काष्ठा highmem_pbe *next;
पूर्ण;

/*
 * List of highmem PBEs needed क्रम restoring the highmem pages that were
 * allocated beक्रमe the suspend and included in the suspend image, but have
 * also been allocated by the "resume" kernel, so their contents cannot be
 * written directly to their "original" page frames.
 */
अटल काष्ठा highmem_pbe *highmem_pblist;

/**
 * count_highmem_image_pages - Compute the number of highmem pages in the image.
 * @bm: Memory biपंचांगap.
 *
 * The bits in @bm that correspond to image pages are assumed to be set.
 */
अटल अचिन्हित पूर्णांक count_highmem_image_pages(काष्ठा memory_biपंचांगap *bm)
अणु
	अचिन्हित दीर्घ pfn;
	अचिन्हित पूर्णांक cnt = 0;

	memory_bm_position_reset(bm);
	pfn = memory_bm_next_pfn(bm);
	जबतक (pfn != BM_END_OF_MAP) अणु
		अगर (PageHighMem(pfn_to_page(pfn)))
			cnt++;

		pfn = memory_bm_next_pfn(bm);
	पूर्ण
	वापस cnt;
पूर्ण

अटल अचिन्हित पूर्णांक safe_highmem_pages;

अटल काष्ठा memory_biपंचांगap *safe_highmem_bm;

/**
 * prepare_highmem_image - Allocate memory क्रम loading highmem data from image.
 * @bm: Poपूर्णांकer to an uninitialized memory biपंचांगap काष्ठाure.
 * @nr_highmem_p: Poपूर्णांकer to the number of highmem image pages.
 *
 * Try to allocate as many highmem pages as there are highmem image pages
 * (@nr_highmem_p poपूर्णांकs to the variable containing the number of highmem image
 * pages).  The pages that are "safe" (ie. will not be overwritten when the
 * hibernation image is restored entirely) have the corresponding bits set in
 * @bm (it must be unitialized).
 *
 * NOTE: This function should not be called अगर there are no highmem image pages.
 */
अटल पूर्णांक prepare_highmem_image(काष्ठा memory_biपंचांगap *bm,
				 अचिन्हित पूर्णांक *nr_highmem_p)
अणु
	अचिन्हित पूर्णांक to_alloc;

	अगर (memory_bm_create(bm, GFP_ATOMIC, PG_SAFE))
		वापस -ENOMEM;

	अगर (get_highmem_buffer(PG_SAFE))
		वापस -ENOMEM;

	to_alloc = count_मुक्त_highmem_pages();
	अगर (to_alloc > *nr_highmem_p)
		to_alloc = *nr_highmem_p;
	अन्यथा
		*nr_highmem_p = to_alloc;

	safe_highmem_pages = 0;
	जबतक (to_alloc-- > 0) अणु
		काष्ठा page *page;

		page = alloc_page(__GFP_HIGHMEM);
		अगर (!swsusp_page_is_मुक्त(page)) अणु
			/* The page is "safe", set its bit the biपंचांगap */
			memory_bm_set_bit(bm, page_to_pfn(page));
			safe_highmem_pages++;
		पूर्ण
		/* Mark the page as allocated */
		swsusp_set_page_क्रमbidden(page);
		swsusp_set_page_मुक्त(page);
	पूर्ण
	memory_bm_position_reset(bm);
	safe_highmem_bm = bm;
	वापस 0;
पूर्ण

अटल काष्ठा page *last_highmem_page;

/**
 * get_highmem_page_buffer - Prepare a buffer to store a highmem image page.
 *
 * For a given highmem image page get a buffer that suspend_ग_लिखो_next() should
 * वापस to its caller to ग_लिखो to.
 *
 * If the page is to be saved to its "original" page frame or a copy of
 * the page is to be made in the highmem, @buffer is वापसed.  Otherwise,
 * the copy of the page is to be made in normal memory, so the address of
 * the copy is वापसed.
 *
 * If @buffer is वापसed, the caller of suspend_ग_लिखो_next() will ग_लिखो
 * the page's contents to @buffer, so they will have to be copied to the
 * right location on the next call to suspend_ग_लिखो_next() and it is करोne
 * with the help of copy_last_highmem_page().  For this purpose, अगर
 * @buffer is वापसed, @last_highmem_page is set to the page to which
 * the data will have to be copied from @buffer.
 */
अटल व्योम *get_highmem_page_buffer(काष्ठा page *page,
				     काष्ठा chain_allocator *ca)
अणु
	काष्ठा highmem_pbe *pbe;
	व्योम *kaddr;

	अगर (swsusp_page_is_क्रमbidden(page) && swsusp_page_is_मुक्त(page)) अणु
		/*
		 * We have allocated the "original" page frame and we can
		 * use it directly to store the loaded page.
		 */
		last_highmem_page = page;
		वापस buffer;
	पूर्ण
	/*
	 * The "original" page frame has not been allocated and we have to
	 * use a "safe" page frame to store the loaded page.
	 */
	pbe = chain_alloc(ca, माप(काष्ठा highmem_pbe));
	अगर (!pbe) अणु
		swsusp_मुक्त();
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	pbe->orig_page = page;
	अगर (safe_highmem_pages > 0) अणु
		काष्ठा page *पंचांगp;

		/* Copy of the page will be stored in high memory */
		kaddr = buffer;
		पंचांगp = pfn_to_page(memory_bm_next_pfn(safe_highmem_bm));
		safe_highmem_pages--;
		last_highmem_page = पंचांगp;
		pbe->copy_page = पंचांगp;
	पूर्ण अन्यथा अणु
		/* Copy of the page will be stored in normal memory */
		kaddr = safe_pages_list;
		safe_pages_list = safe_pages_list->next;
		pbe->copy_page = virt_to_page(kaddr);
	पूर्ण
	pbe->next = highmem_pblist;
	highmem_pblist = pbe;
	वापस kaddr;
पूर्ण

/**
 * copy_last_highmem_page - Copy most the most recent highmem image page.
 *
 * Copy the contents of a highmem image from @buffer, where the caller of
 * snapshot_ग_लिखो_next() has stored them, to the right location represented by
 * @last_highmem_page .
 */
अटल व्योम copy_last_highmem_page(व्योम)
अणु
	अगर (last_highmem_page) अणु
		व्योम *dst;

		dst = kmap_atomic(last_highmem_page);
		copy_page(dst, buffer);
		kunmap_atomic(dst);
		last_highmem_page = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक last_highmem_page_copied(व्योम)
अणु
	वापस !last_highmem_page;
पूर्ण

अटल अंतरभूत व्योम मुक्त_highmem_data(व्योम)
अणु
	अगर (safe_highmem_bm)
		memory_bm_मुक्त(safe_highmem_bm, PG_UNSAFE_CLEAR);

	अगर (buffer)
		मुक्त_image_page(buffer, PG_UNSAFE_CLEAR);
पूर्ण
#अन्यथा
अटल अचिन्हित पूर्णांक count_highmem_image_pages(काष्ठा memory_biपंचांगap *bm) अणु वापस 0; पूर्ण

अटल अंतरभूत पूर्णांक prepare_highmem_image(काष्ठा memory_biपंचांगap *bm,
					अचिन्हित पूर्णांक *nr_highmem_p) अणु वापस 0; पूर्ण

अटल अंतरभूत व्योम *get_highmem_page_buffer(काष्ठा page *page,
					    काष्ठा chain_allocator *ca)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत व्योम copy_last_highmem_page(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक last_highmem_page_copied(व्योम) अणु वापस 1; पूर्ण
अटल अंतरभूत व्योम मुक्त_highmem_data(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */

#घोषणा PBES_PER_LINKED_PAGE	(LINKED_PAGE_DATA_SIZE / माप(काष्ठा pbe))

/**
 * prepare_image - Make room क्रम loading hibernation image.
 * @new_bm: Unitialized memory biपंचांगap काष्ठाure.
 * @bm: Memory biपंचांगap with unsafe pages marked.
 *
 * Use @bm to mark the pages that will be overwritten in the process of
 * restoring the प्रणाली memory state from the suspend image ("unsafe" pages)
 * and allocate memory क्रम the image.
 *
 * The idea is to allocate a new memory biपंचांगap first and then allocate
 * as many pages as needed क्रम image data, but without specअगरying what those
 * pages will be used क्रम just yet.  Instead, we mark them all as allocated and
 * create a lists of "safe" pages to be used later.  On प्रणालीs with high
 * memory a list of "safe" highmem pages is created too.
 */
अटल पूर्णांक prepare_image(काष्ठा memory_biपंचांगap *new_bm, काष्ठा memory_biपंचांगap *bm)
अणु
	अचिन्हित पूर्णांक nr_pages, nr_highmem;
	काष्ठा linked_page *lp;
	पूर्णांक error;

	/* If there is no highmem, the buffer will not be necessary */
	मुक्त_image_page(buffer, PG_UNSAFE_CLEAR);
	buffer = शून्य;

	nr_highmem = count_highmem_image_pages(bm);
	mark_unsafe_pages(bm);

	error = memory_bm_create(new_bm, GFP_ATOMIC, PG_SAFE);
	अगर (error)
		जाओ Free;

	duplicate_memory_biपंचांगap(new_bm, bm);
	memory_bm_मुक्त(bm, PG_UNSAFE_KEEP);
	अगर (nr_highmem > 0) अणु
		error = prepare_highmem_image(bm, &nr_highmem);
		अगर (error)
			जाओ Free;
	पूर्ण
	/*
	 * Reserve some safe pages क्रम potential later use.
	 *
	 * NOTE: This way we make sure there will be enough safe pages क्रम the
	 * chain_alloc() in get_buffer().  It is a bit wasteful, but
	 * nr_copy_pages cannot be greater than 50% of the memory anyway.
	 *
	 * nr_copy_pages cannot be less than allocated_unsafe_pages too.
	 */
	nr_pages = nr_copy_pages - nr_highmem - allocated_unsafe_pages;
	nr_pages = DIV_ROUND_UP(nr_pages, PBES_PER_LINKED_PAGE);
	जबतक (nr_pages > 0) अणु
		lp = get_image_page(GFP_ATOMIC, PG_SAFE);
		अगर (!lp) अणु
			error = -ENOMEM;
			जाओ Free;
		पूर्ण
		lp->next = safe_pages_list;
		safe_pages_list = lp;
		nr_pages--;
	पूर्ण
	/* Pपुनः_स्मृतिate memory क्रम the image */
	nr_pages = nr_copy_pages - nr_highmem - allocated_unsafe_pages;
	जबतक (nr_pages > 0) अणु
		lp = (काष्ठा linked_page *)get_zeroed_page(GFP_ATOMIC);
		अगर (!lp) अणु
			error = -ENOMEM;
			जाओ Free;
		पूर्ण
		अगर (!swsusp_page_is_मुक्त(virt_to_page(lp))) अणु
			/* The page is "safe", add it to the list */
			lp->next = safe_pages_list;
			safe_pages_list = lp;
		पूर्ण
		/* Mark the page as allocated */
		swsusp_set_page_क्रमbidden(virt_to_page(lp));
		swsusp_set_page_मुक्त(virt_to_page(lp));
		nr_pages--;
	पूर्ण
	वापस 0;

 Free:
	swsusp_मुक्त();
	वापस error;
पूर्ण

/**
 * get_buffer - Get the address to store the next image data page.
 *
 * Get the address that snapshot_ग_लिखो_next() should वापस to its caller to
 * ग_लिखो to.
 */
अटल व्योम *get_buffer(काष्ठा memory_biपंचांगap *bm, काष्ठा chain_allocator *ca)
अणु
	काष्ठा pbe *pbe;
	काष्ठा page *page;
	अचिन्हित दीर्घ pfn = memory_bm_next_pfn(bm);

	अगर (pfn == BM_END_OF_MAP)
		वापस ERR_PTR(-EFAULT);

	page = pfn_to_page(pfn);
	अगर (PageHighMem(page))
		वापस get_highmem_page_buffer(page, ca);

	अगर (swsusp_page_is_क्रमbidden(page) && swsusp_page_is_मुक्त(page))
		/*
		 * We have allocated the "original" page frame and we can
		 * use it directly to store the loaded page.
		 */
		वापस page_address(page);

	/*
	 * The "original" page frame has not been allocated and we have to
	 * use a "safe" page frame to store the loaded page.
	 */
	pbe = chain_alloc(ca, माप(काष्ठा pbe));
	अगर (!pbe) अणु
		swsusp_मुक्त();
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	pbe->orig_address = page_address(page);
	pbe->address = safe_pages_list;
	safe_pages_list = safe_pages_list->next;
	pbe->next = restore_pblist;
	restore_pblist = pbe;
	वापस pbe->address;
पूर्ण

/**
 * snapshot_ग_लिखो_next - Get the address to store the next image page.
 * @handle: Snapshot handle काष्ठाure to guide the writing.
 *
 * On the first call, @handle should poपूर्णांक to a zeroed snapshot_handle
 * काष्ठाure.  The काष्ठाure माला_लो populated then and a poपूर्णांकer to it should be
 * passed to this function every next समय.
 *
 * On success, the function वापसs a positive number.  Then, the caller
 * is allowed to ग_लिखो up to the वापसed number of bytes to the memory
 * location computed by the data_of() macro.
 *
 * The function वापसs 0 to indicate the "end of file" condition.  Negative
 * numbers are वापसed on errors, in which हालs the काष्ठाure poपूर्णांकed to by
 * @handle is not updated and should not be used any more.
 */
पूर्णांक snapshot_ग_लिखो_next(काष्ठा snapshot_handle *handle)
अणु
	अटल काष्ठा chain_allocator ca;
	पूर्णांक error = 0;

	/* Check अगर we have alपढ़ोy loaded the entire image */
	अगर (handle->cur > 1 && handle->cur > nr_meta_pages + nr_copy_pages)
		वापस 0;

	handle->sync_पढ़ो = 1;

	अगर (!handle->cur) अणु
		अगर (!buffer)
			/* This makes the buffer be मुक्तd by swsusp_मुक्त() */
			buffer = get_image_page(GFP_ATOMIC, PG_ANY);

		अगर (!buffer)
			वापस -ENOMEM;

		handle->buffer = buffer;
	पूर्ण अन्यथा अगर (handle->cur == 1) अणु
		error = load_header(buffer);
		अगर (error)
			वापस error;

		safe_pages_list = शून्य;

		error = memory_bm_create(&copy_bm, GFP_ATOMIC, PG_ANY);
		अगर (error)
			वापस error;

		hibernate_restore_protection_begin();
	पूर्ण अन्यथा अगर (handle->cur <= nr_meta_pages + 1) अणु
		error = unpack_orig_pfns(buffer, &copy_bm);
		अगर (error)
			वापस error;

		अगर (handle->cur == nr_meta_pages + 1) अणु
			error = prepare_image(&orig_bm, &copy_bm);
			अगर (error)
				वापस error;

			chain_init(&ca, GFP_ATOMIC, PG_SAFE);
			memory_bm_position_reset(&orig_bm);
			restore_pblist = शून्य;
			handle->buffer = get_buffer(&orig_bm, &ca);
			handle->sync_पढ़ो = 0;
			अगर (IS_ERR(handle->buffer))
				वापस PTR_ERR(handle->buffer);
		पूर्ण
	पूर्ण अन्यथा अणु
		copy_last_highmem_page();
		hibernate_restore_protect_page(handle->buffer);
		handle->buffer = get_buffer(&orig_bm, &ca);
		अगर (IS_ERR(handle->buffer))
			वापस PTR_ERR(handle->buffer);
		अगर (handle->buffer != buffer)
			handle->sync_पढ़ो = 0;
	पूर्ण
	handle->cur++;
	वापस PAGE_SIZE;
पूर्ण

/**
 * snapshot_ग_लिखो_finalize - Complete the loading of a hibernation image.
 *
 * Must be called after the last call to snapshot_ग_लिखो_next() in हाल the last
 * page in the image happens to be a highmem page and its contents should be
 * stored in highmem.  Additionally, it recycles biपंचांगap memory that's not
 * necessary any more.
 */
व्योम snapshot_ग_लिखो_finalize(काष्ठा snapshot_handle *handle)
अणु
	copy_last_highmem_page();
	hibernate_restore_protect_page(handle->buffer);
	/* Do that only अगर we have loaded the image entirely */
	अगर (handle->cur > 1 && handle->cur > nr_meta_pages + nr_copy_pages) अणु
		memory_bm_recycle(&orig_bm);
		मुक्त_highmem_data();
	पूर्ण
पूर्ण

पूर्णांक snapshot_image_loaded(काष्ठा snapshot_handle *handle)
अणु
	वापस !(!nr_copy_pages || !last_highmem_page_copied() ||
			handle->cur <= nr_meta_pages + nr_copy_pages);
पूर्ण

#अगर_घोषित CONFIG_HIGHMEM
/* Assumes that @buf is पढ़ोy and poपूर्णांकs to a "safe" page */
अटल अंतरभूत व्योम swap_two_pages_data(काष्ठा page *p1, काष्ठा page *p2,
				       व्योम *buf)
अणु
	व्योम *kaddr1, *kaddr2;

	kaddr1 = kmap_atomic(p1);
	kaddr2 = kmap_atomic(p2);
	copy_page(buf, kaddr1);
	copy_page(kaddr1, kaddr2);
	copy_page(kaddr2, buf);
	kunmap_atomic(kaddr2);
	kunmap_atomic(kaddr1);
पूर्ण

/**
 * restore_highmem - Put highmem image pages पूर्णांकo their original locations.
 *
 * For each highmem page that was in use beक्रमe hibernation and is included in
 * the image, and also has been allocated by the "restore" kernel, swap its
 * current contents with the previous (ie. "before hibernation") ones.
 *
 * If the restore eventually fails, we can call this function once again and
 * restore the highmem state as seen by the restore kernel.
 */
पूर्णांक restore_highmem(व्योम)
अणु
	काष्ठा highmem_pbe *pbe = highmem_pblist;
	व्योम *buf;

	अगर (!pbe)
		वापस 0;

	buf = get_image_page(GFP_ATOMIC, PG_SAFE);
	अगर (!buf)
		वापस -ENOMEM;

	जबतक (pbe) अणु
		swap_two_pages_data(pbe->copy_page, pbe->orig_page, buf);
		pbe = pbe->next;
	पूर्ण
	मुक्त_image_page(buf, PG_UNSAFE_CLEAR);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_HIGHMEM */
