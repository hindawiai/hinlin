<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  PS3 address space management.
 *
 *  Copyright (C) 2006 Sony Computer Entertainment Inc.
 *  Copyright 2006 Sony Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/cell-regs.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/setup.h>

#समावेश "platform.h"

#अगर defined(DEBUG)
#घोषणा DBG udbg_म_लिखो
#अन्यथा
#घोषणा DBG pr_devel
#पूर्ण_अगर

क्रमागत अणु
#अगर defined(CONFIG_PS3_DYNAMIC_DMA)
	USE_DYNAMIC_DMA = 1,
#अन्यथा
	USE_DYNAMIC_DMA = 0,
#पूर्ण_अगर
पूर्ण;

क्रमागत अणु
	PAGE_SHIFT_4K = 12U,
	PAGE_SHIFT_64K = 16U,
	PAGE_SHIFT_16M = 24U,
पूर्ण;

अटल अचिन्हित दीर्घ make_page_sizes(अचिन्हित दीर्घ a, अचिन्हित दीर्घ b)
अणु
	वापस (a << 56) | (b << 48);
पूर्ण

क्रमागत अणु
	ALLOCATE_MEMORY_TRY_ALT_UNIT = 0X04,
	ALLOCATE_MEMORY_ADDR_ZERO = 0X08,
पूर्ण;

/* valid htab sizes are अणु18,19,20पूर्ण = 256K, 512K, 1M */

क्रमागत अणु
	HTAB_SIZE_MAX = 20U, /* HV limit of 1MB */
	HTAB_SIZE_MIN = 18U, /* CPU limit of 256KB */
पूर्ण;

/*============================================================================*/
/* भव address space routines                                             */
/*============================================================================*/

/**
 * काष्ठा mem_region - memory region काष्ठाure
 * @base: base address
 * @size: size in bytes
 * @offset: dअगरference between base and rm.size
 * @destroy: flag अगर region should be destroyed upon shutकरोwn
 */

काष्ठा mem_region अणु
	u64 base;
	u64 size;
	अचिन्हित दीर्घ offset;
	पूर्णांक destroy;
पूर्ण;

/**
 * काष्ठा map - address space state variables holder
 * @total: total memory available as reported by HV
 * @vas_id - HV भव address space id
 * @htab_size: htab size in bytes
 *
 * The HV भव address space (vas) allows क्रम hotplug memory regions.
 * Memory regions can be created and destroyed in the vas at runसमय.
 * @rm: real mode (booपंचांगem) region
 * @r1: highmem region(s)
 *
 * ps3 addresses
 * virt_addr: a cpu 'translated' effective address
 * phys_addr: an address in what Linux thinks is the physical address space
 * lpar_addr: an address in the HV भव address space
 * bus_addr: an io controller 'translated' address on a device bus
 */

काष्ठा map अणु
	u64 total;
	u64 vas_id;
	u64 htab_size;
	काष्ठा mem_region rm;
	काष्ठा mem_region r1;
पूर्ण;

#घोषणा debug_dump_map(x) _debug_dump_map(x, __func__, __LINE__)
अटल व्योम __maybe_unused _debug_dump_map(स्थिर काष्ठा map *m,
	स्थिर अक्षर *func, पूर्णांक line)
अणु
	DBG("%s:%d: map.total     = %llxh\n", func, line, m->total);
	DBG("%s:%d: map.rm.size   = %llxh\n", func, line, m->rm.size);
	DBG("%s:%d: map.vas_id    = %llu\n", func, line, m->vas_id);
	DBG("%s:%d: map.htab_size = %llxh\n", func, line, m->htab_size);
	DBG("%s:%d: map.r1.base   = %llxh\n", func, line, m->r1.base);
	DBG("%s:%d: map.r1.offset = %lxh\n", func, line, m->r1.offset);
	DBG("%s:%d: map.r1.size   = %llxh\n", func, line, m->r1.size);
पूर्ण

अटल काष्ठा map map;

/**
 * ps3_mm_phys_to_lpar - translate a linux physical address to lpar address
 * @phys_addr: linux physical address
 */

अचिन्हित दीर्घ ps3_mm_phys_to_lpar(अचिन्हित दीर्घ phys_addr)
अणु
	BUG_ON(is_kernel_addr(phys_addr));
	वापस (phys_addr < map.rm.size || phys_addr >= map.total)
		? phys_addr : phys_addr + map.r1.offset;
पूर्ण

EXPORT_SYMBOL(ps3_mm_phys_to_lpar);

/**
 * ps3_mm_vas_create - create the भव address space
 */

व्योम __init ps3_mm_vas_create(अचिन्हित दीर्घ* htab_size)
अणु
	पूर्णांक result;
	u64 start_address;
	u64 size;
	u64 access_right;
	u64 max_page_size;
	u64 flags;

	result = lv1_query_logical_partition_address_region_info(0,
		&start_address, &size, &access_right, &max_page_size,
		&flags);

	अगर (result) अणु
		DBG("%s:%d: lv1_query_logical_partition_address_region_info "
			"failed: %s\n", __func__, __LINE__,
			ps3_result(result));
		जाओ fail;
	पूर्ण

	अगर (max_page_size < PAGE_SHIFT_16M) अणु
		DBG("%s:%d: bad max_page_size %llxh\n", __func__, __LINE__,
			max_page_size);
		जाओ fail;
	पूर्ण

	BUILD_BUG_ON(CONFIG_PS3_HTAB_SIZE > HTAB_SIZE_MAX);
	BUILD_BUG_ON(CONFIG_PS3_HTAB_SIZE < HTAB_SIZE_MIN);

	result = lv1_स्थिरruct_भव_address_space(CONFIG_PS3_HTAB_SIZE,
			2, make_page_sizes(PAGE_SHIFT_16M, PAGE_SHIFT_64K),
			&map.vas_id, &map.htab_size);

	अगर (result) अणु
		DBG("%s:%d: lv1_construct_virtual_address_space failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		जाओ fail;
	पूर्ण

	result = lv1_select_भव_address_space(map.vas_id);

	अगर (result) अणु
		DBG("%s:%d: lv1_select_virtual_address_space failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		जाओ fail;
	पूर्ण

	*htab_size = map.htab_size;

	debug_dump_map(&map);

	वापस;

fail:
	panic("ps3_mm_vas_create failed");
पूर्ण

/**
 * ps3_mm_vas_destroy -
 */

व्योम ps3_mm_vas_destroy(व्योम)
अणु
	पूर्णांक result;

	अगर (map.vas_id) अणु
		result = lv1_select_भव_address_space(0);
		result += lv1_deकाष्ठा_भव_address_space(map.vas_id);

		अगर (result) अणु
			lv1_panic(0);
		पूर्ण

		map.vas_id = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ps3_mm_get_repository_highmem(काष्ठा mem_region *r)
अणु
	पूर्णांक result;

	/* Assume a single highmem region. */

	result = ps3_repository_पढ़ो_highmem_info(0, &r->base, &r->size);

	अगर (result)
		जाओ zero_region;

	अगर (!r->base || !r->size) अणु
		result = -1;
		जाओ zero_region;
	पूर्ण

	r->offset = r->base - map.rm.size;

	DBG("%s:%d: Found high region in repository: %llxh %llxh\n",
	    __func__, __LINE__, r->base, r->size);

	वापस 0;

zero_region:
	DBG("%s:%d: No high region in repository.\n", __func__, __LINE__);

	r->size = r->base = r->offset = 0;
	वापस result;
पूर्ण

अटल पूर्णांक ps3_mm_set_repository_highmem(स्थिर काष्ठा mem_region *r)
अणु
	/* Assume a single highmem region. */

	वापस r ? ps3_repository_ग_लिखो_highmem_info(0, r->base, r->size) :
		ps3_repository_ग_लिखो_highmem_info(0, 0, 0);
पूर्ण

/**
 * ps3_mm_region_create - create a memory region in the vas
 * @r: poपूर्णांकer to a काष्ठा mem_region to accept initialized values
 * @size: requested region size
 *
 * This implementation creates the region with the vas large page size.
 * @size is rounded करोwn to a multiple of the vas large page size.
 */

अटल पूर्णांक ps3_mm_region_create(काष्ठा mem_region *r, अचिन्हित दीर्घ size)
अणु
	पूर्णांक result;
	u64 muid;

	r->size = ALIGN_DOWN(size, 1 << PAGE_SHIFT_16M);

	DBG("%s:%d requested  %lxh\n", __func__, __LINE__, size);
	DBG("%s:%d actual     %llxh\n", __func__, __LINE__, r->size);
	DBG("%s:%d difference %llxh (%lluMB)\n", __func__, __LINE__,
		size - r->size, (size - r->size) / 1024 / 1024);

	अगर (r->size == 0) अणु
		DBG("%s:%d: size == 0\n", __func__, __LINE__);
		result = -1;
		जाओ zero_region;
	पूर्ण

	result = lv1_allocate_memory(r->size, PAGE_SHIFT_16M, 0,
		ALLOCATE_MEMORY_TRY_ALT_UNIT, &r->base, &muid);

	अगर (result || r->base < map.rm.size) अणु
		DBG("%s:%d: lv1_allocate_memory failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		जाओ zero_region;
	पूर्ण

	r->destroy = 1;
	r->offset = r->base - map.rm.size;
	वापस result;

zero_region:
	r->size = r->base = r->offset = 0;
	वापस result;
पूर्ण

/**
 * ps3_mm_region_destroy - destroy a memory region
 * @r: poपूर्णांकer to काष्ठा mem_region
 */

अटल व्योम ps3_mm_region_destroy(काष्ठा mem_region *r)
अणु
	पूर्णांक result;

	अगर (!r->destroy) अणु
		वापस;
	पूर्ण

	अगर (r->base) अणु
		result = lv1_release_memory(r->base);

		अगर (result) अणु
			lv1_panic(0);
		पूर्ण

		r->size = r->base = r->offset = 0;
		map.total = map.rm.size;
	पूर्ण

	ps3_mm_set_repository_highmem(शून्य);
पूर्ण

/*============================================================================*/
/* dma routines                                                               */
/*============================================================================*/

/**
 * dma_sb_lpar_to_bus - Translate an lpar address to ioc mapped bus address.
 * @r: poपूर्णांकer to dma region काष्ठाure
 * @lpar_addr: HV lpar address
 */

अटल अचिन्हित दीर्घ dma_sb_lpar_to_bus(काष्ठा ps3_dma_region *r,
	अचिन्हित दीर्घ lpar_addr)
अणु
	अगर (lpar_addr >= map.rm.size)
		lpar_addr -= map.r1.offset;
	BUG_ON(lpar_addr < r->offset);
	BUG_ON(lpar_addr >= r->offset + r->len);
	वापस r->bus_addr + lpar_addr - r->offset;
पूर्ण

#घोषणा dma_dump_region(_a) _dma_dump_region(_a, __func__, __LINE__)
अटल व्योम  __maybe_unused _dma_dump_region(स्थिर काष्ठा ps3_dma_region *r,
	स्थिर अक्षर *func, पूर्णांक line)
अणु
	DBG("%s:%d: dev        %llu:%llu\n", func, line, r->dev->bus_id,
		r->dev->dev_id);
	DBG("%s:%d: page_size  %u\n", func, line, r->page_size);
	DBG("%s:%d: bus_addr   %lxh\n", func, line, r->bus_addr);
	DBG("%s:%d: len        %lxh\n", func, line, r->len);
	DBG("%s:%d: offset     %lxh\n", func, line, r->offset);
पूर्ण

  /**
 * dma_chunk - A chunk of dma pages mapped by the io controller.
 * @region - The dma region that owns this chunk.
 * @lpar_addr: Starting lpar address of the area to map.
 * @bus_addr: Starting ioc bus address of the area to map.
 * @len: Length in bytes of the area to map.
 * @link: A काष्ठा list_head used with काष्ठा ps3_dma_region.chunk_list, the
 * list of all chuncks owned by the region.
 *
 * This implementation uses a very simple dma page manager
 * based on the dma_chunk काष्ठाure.  This scheme assumes
 * that all drivers use very well behaved dma ops.
 */

काष्ठा dma_chunk अणु
	काष्ठा ps3_dma_region *region;
	अचिन्हित दीर्घ lpar_addr;
	अचिन्हित दीर्घ bus_addr;
	अचिन्हित दीर्घ len;
	काष्ठा list_head link;
	अचिन्हित पूर्णांक usage_count;
पूर्ण;

#घोषणा dma_dump_chunk(_a) _dma_dump_chunk(_a, __func__, __LINE__)
अटल व्योम _dma_dump_chunk (स्थिर काष्ठा dma_chunk* c, स्थिर अक्षर* func,
	पूर्णांक line)
अणु
	DBG("%s:%d: r.dev        %llu:%llu\n", func, line,
		c->region->dev->bus_id, c->region->dev->dev_id);
	DBG("%s:%d: r.bus_addr   %lxh\n", func, line, c->region->bus_addr);
	DBG("%s:%d: r.page_size  %u\n", func, line, c->region->page_size);
	DBG("%s:%d: r.len        %lxh\n", func, line, c->region->len);
	DBG("%s:%d: r.offset     %lxh\n", func, line, c->region->offset);
	DBG("%s:%d: c.lpar_addr  %lxh\n", func, line, c->lpar_addr);
	DBG("%s:%d: c.bus_addr   %lxh\n", func, line, c->bus_addr);
	DBG("%s:%d: c.len        %lxh\n", func, line, c->len);
पूर्ण

अटल काष्ठा dma_chunk * dma_find_chunk(काष्ठा ps3_dma_region *r,
	अचिन्हित दीर्घ bus_addr, अचिन्हित दीर्घ len)
अणु
	काष्ठा dma_chunk *c;
	अचिन्हित दीर्घ aligned_bus = ALIGN_DOWN(bus_addr, 1 << r->page_size);
	अचिन्हित दीर्घ aligned_len = ALIGN(len+bus_addr-aligned_bus,
					      1 << r->page_size);

	list_क्रम_each_entry(c, &r->chunk_list.head, link) अणु
		/* पूर्णांकersection */
		अगर (aligned_bus >= c->bus_addr &&
		    aligned_bus + aligned_len <= c->bus_addr + c->len)
			वापस c;

		/* below */
		अगर (aligned_bus + aligned_len <= c->bus_addr)
			जारी;

		/* above */
		अगर (aligned_bus >= c->bus_addr + c->len)
			जारी;

		/* we करोn't handle the multi-chunk हाल क्रम now */
		dma_dump_chunk(c);
		BUG();
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_chunk *dma_find_chunk_lpar(काष्ठा ps3_dma_region *r,
	अचिन्हित दीर्घ lpar_addr, अचिन्हित दीर्घ len)
अणु
	काष्ठा dma_chunk *c;
	अचिन्हित दीर्घ aligned_lpar = ALIGN_DOWN(lpar_addr, 1 << r->page_size);
	अचिन्हित दीर्घ aligned_len = ALIGN(len + lpar_addr - aligned_lpar,
					      1 << r->page_size);

	list_क्रम_each_entry(c, &r->chunk_list.head, link) अणु
		/* पूर्णांकersection */
		अगर (c->lpar_addr <= aligned_lpar &&
		    aligned_lpar < c->lpar_addr + c->len) अणु
			अगर (aligned_lpar + aligned_len <= c->lpar_addr + c->len)
				वापस c;
			अन्यथा अणु
				dma_dump_chunk(c);
				BUG();
			पूर्ण
		पूर्ण
		/* below */
		अगर (aligned_lpar + aligned_len <= c->lpar_addr) अणु
			जारी;
		पूर्ण
		/* above */
		अगर (c->lpar_addr + c->len <= aligned_lpar) अणु
			जारी;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक dma_sb_मुक्त_chunk(काष्ठा dma_chunk *c)
अणु
	पूर्णांक result = 0;

	अगर (c->bus_addr) अणु
		result = lv1_unmap_device_dma_region(c->region->dev->bus_id,
			c->region->dev->dev_id, c->bus_addr, c->len);
		BUG_ON(result);
	पूर्ण

	kमुक्त(c);
	वापस result;
पूर्ण

अटल पूर्णांक dma_ioc0_मुक्त_chunk(काष्ठा dma_chunk *c)
अणु
	पूर्णांक result = 0;
	पूर्णांक iopage;
	अचिन्हित दीर्घ offset;
	काष्ठा ps3_dma_region *r = c->region;

	DBG("%s:start\n", __func__);
	क्रम (iopage = 0; iopage < (c->len >> r->page_size); iopage++) अणु
		offset = (1 << r->page_size) * iopage;
		/* put INVALID entry */
		result = lv1_put_iopte(0,
				       c->bus_addr + offset,
				       c->lpar_addr + offset,
				       r->ioid,
				       0);
		DBG("%s: bus=%#lx, lpar=%#lx, ioid=%d\n", __func__,
		    c->bus_addr + offset,
		    c->lpar_addr + offset,
		    r->ioid);

		अगर (result) अणु
			DBG("%s:%d: lv1_put_iopte failed: %s\n", __func__,
			    __LINE__, ps3_result(result));
		पूर्ण
	पूर्ण
	kमुक्त(c);
	DBG("%s:end\n", __func__);
	वापस result;
पूर्ण

/**
 * dma_sb_map_pages - Maps dma pages पूर्णांकo the io controller bus address space.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 * @phys_addr: Starting physical address of the area to map.
 * @len: Length in bytes of the area to map.
 * c_out: A poपूर्णांकer to receive an allocated काष्ठा dma_chunk क्रम this area.
 *
 * This is the lowest level dma mapping routine, and is the one that will
 * make the HV call to add the pages पूर्णांकo the io controller address space.
 */

अटल पूर्णांक dma_sb_map_pages(काष्ठा ps3_dma_region *r, अचिन्हित दीर्घ phys_addr,
	    अचिन्हित दीर्घ len, काष्ठा dma_chunk **c_out, u64 iopte_flag)
अणु
	पूर्णांक result;
	काष्ठा dma_chunk *c;

	c = kzalloc(माप(*c), GFP_ATOMIC);
	अगर (!c) अणु
		result = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	c->region = r;
	c->lpar_addr = ps3_mm_phys_to_lpar(phys_addr);
	c->bus_addr = dma_sb_lpar_to_bus(r, c->lpar_addr);
	c->len = len;

	BUG_ON(iopte_flag != 0xf800000000000000UL);
	result = lv1_map_device_dma_region(c->region->dev->bus_id,
					   c->region->dev->dev_id, c->lpar_addr,
					   c->bus_addr, c->len, iopte_flag);
	अगर (result) अणु
		DBG("%s:%d: lv1_map_device_dma_region failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		जाओ fail_map;
	पूर्ण

	list_add(&c->link, &r->chunk_list.head);

	*c_out = c;
	वापस 0;

fail_map:
	kमुक्त(c);
fail_alloc:
	*c_out = शून्य;
	DBG(" <- %s:%d\n", __func__, __LINE__);
	वापस result;
पूर्ण

अटल पूर्णांक dma_ioc0_map_pages(काष्ठा ps3_dma_region *r, अचिन्हित दीर्घ phys_addr,
			      अचिन्हित दीर्घ len, काष्ठा dma_chunk **c_out,
			      u64 iopte_flag)
अणु
	पूर्णांक result;
	काष्ठा dma_chunk *c, *last;
	पूर्णांक iopage, pages;
	अचिन्हित दीर्घ offset;

	DBG(KERN_ERR "%s: phy=%#lx, lpar%#lx, len=%#lx\n", __func__,
	    phys_addr, ps3_mm_phys_to_lpar(phys_addr), len);
	c = kzalloc(माप(*c), GFP_ATOMIC);
	अगर (!c) अणु
		result = -ENOMEM;
		जाओ fail_alloc;
	पूर्ण

	c->region = r;
	c->len = len;
	c->lpar_addr = ps3_mm_phys_to_lpar(phys_addr);
	/* allocate IO address */
	अगर (list_empty(&r->chunk_list.head)) अणु
		/* first one */
		c->bus_addr = r->bus_addr;
	पूर्ण अन्यथा अणु
		/* derive from last bus addr*/
		last  = list_entry(r->chunk_list.head.next,
				   काष्ठा dma_chunk, link);
		c->bus_addr = last->bus_addr + last->len;
		DBG("%s: last bus=%#lx, len=%#lx\n", __func__,
		    last->bus_addr, last->len);
	पूर्ण

	/* FIXME: check whether length exceeds region size */

	/* build ioptes क्रम the area */
	pages = len >> r->page_size;
	DBG("%s: pgsize=%#x len=%#lx pages=%#x iopteflag=%#llx\n", __func__,
	    r->page_size, r->len, pages, iopte_flag);
	क्रम (iopage = 0; iopage < pages; iopage++) अणु
		offset = (1 << r->page_size) * iopage;
		result = lv1_put_iopte(0,
				       c->bus_addr + offset,
				       c->lpar_addr + offset,
				       r->ioid,
				       iopte_flag);
		अगर (result) अणु
			pr_warn("%s:%d: lv1_put_iopte failed: %s\n",
				__func__, __LINE__, ps3_result(result));
			जाओ fail_map;
		पूर्ण
		DBG("%s: pg=%d bus=%#lx, lpar=%#lx, ioid=%#x\n", __func__,
		    iopage, c->bus_addr + offset, c->lpar_addr + offset,
		    r->ioid);
	पूर्ण

	/* be sure that last allocated one is inserted at head */
	list_add(&c->link, &r->chunk_list.head);

	*c_out = c;
	DBG("%s: end\n", __func__);
	वापस 0;

fail_map:
	क्रम (iopage--; 0 <= iopage; iopage--) अणु
		lv1_put_iopte(0,
			      c->bus_addr + offset,
			      c->lpar_addr + offset,
			      r->ioid,
			      0);
	पूर्ण
	kमुक्त(c);
fail_alloc:
	*c_out = शून्य;
	वापस result;
पूर्ण

/**
 * dma_sb_region_create - Create a device dma region.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 *
 * This is the lowest level dma region create routine, and is the one that
 * will make the HV call to create the region.
 */

अटल पूर्णांक dma_sb_region_create(काष्ठा ps3_dma_region *r)
अणु
	पूर्णांक result;
	u64 bus_addr;

	DBG(" -> %s:%d:\n", __func__, __LINE__);

	BUG_ON(!r);

	अगर (!r->dev->bus_id) अणु
		pr_info("%s:%d: %llu:%llu no dma\n", __func__, __LINE__,
			r->dev->bus_id, r->dev->dev_id);
		वापस 0;
	पूर्ण

	DBG("%s:%u: len = 0x%lx, page_size = %u, offset = 0x%lx\n", __func__,
	    __LINE__, r->len, r->page_size, r->offset);

	BUG_ON(!r->len);
	BUG_ON(!r->page_size);
	BUG_ON(!r->region_ops);

	INIT_LIST_HEAD(&r->chunk_list.head);
	spin_lock_init(&r->chunk_list.lock);

	result = lv1_allocate_device_dma_region(r->dev->bus_id, r->dev->dev_id,
		roundup_घात_of_two(r->len), r->page_size, r->region_type,
		&bus_addr);
	r->bus_addr = bus_addr;

	अगर (result) अणु
		DBG("%s:%d: lv1_allocate_device_dma_region failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		r->len = r->bus_addr = 0;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक dma_ioc0_region_create(काष्ठा ps3_dma_region *r)
अणु
	पूर्णांक result;
	u64 bus_addr;

	INIT_LIST_HEAD(&r->chunk_list.head);
	spin_lock_init(&r->chunk_list.lock);

	result = lv1_allocate_io_segment(0,
					 r->len,
					 r->page_size,
					 &bus_addr);
	r->bus_addr = bus_addr;
	अगर (result) अणु
		DBG("%s:%d: lv1_allocate_io_segment failed: %s\n",
			__func__, __LINE__, ps3_result(result));
		r->len = r->bus_addr = 0;
	पूर्ण
	DBG("%s: len=%#lx, pg=%d, bus=%#lx\n", __func__,
	    r->len, r->page_size, r->bus_addr);
	वापस result;
पूर्ण

/**
 * dma_region_मुक्त - Free a device dma region.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 *
 * This is the lowest level dma region मुक्त routine, and is the one that
 * will make the HV call to मुक्त the region.
 */

अटल पूर्णांक dma_sb_region_मुक्त(काष्ठा ps3_dma_region *r)
अणु
	पूर्णांक result;
	काष्ठा dma_chunk *c;
	काष्ठा dma_chunk *पंचांगp;

	BUG_ON(!r);

	अगर (!r->dev->bus_id) अणु
		pr_info("%s:%d: %llu:%llu no dma\n", __func__, __LINE__,
			r->dev->bus_id, r->dev->dev_id);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry_safe(c, पंचांगp, &r->chunk_list.head, link) अणु
		list_del(&c->link);
		dma_sb_मुक्त_chunk(c);
	पूर्ण

	result = lv1_मुक्त_device_dma_region(r->dev->bus_id, r->dev->dev_id,
		r->bus_addr);

	अगर (result)
		DBG("%s:%d: lv1_free_device_dma_region failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	r->bus_addr = 0;

	वापस result;
पूर्ण

अटल पूर्णांक dma_ioc0_region_मुक्त(काष्ठा ps3_dma_region *r)
अणु
	पूर्णांक result;
	काष्ठा dma_chunk *c, *n;

	DBG("%s: start\n", __func__);
	list_क्रम_each_entry_safe(c, n, &r->chunk_list.head, link) अणु
		list_del(&c->link);
		dma_ioc0_मुक्त_chunk(c);
	पूर्ण

	result = lv1_release_io_segment(0, r->bus_addr);

	अगर (result)
		DBG("%s:%d: lv1_free_device_dma_region failed: %s\n",
			__func__, __LINE__, ps3_result(result));

	r->bus_addr = 0;
	DBG("%s: end\n", __func__);

	वापस result;
पूर्ण

/**
 * dma_sb_map_area - Map an area of memory पूर्णांकo a device dma region.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 * @virt_addr: Starting भव address of the area to map.
 * @len: Length in bytes of the area to map.
 * @bus_addr: A poपूर्णांकer to वापस the starting ioc bus address of the area to
 * map.
 *
 * This is the common dma mapping routine.
 */

अटल पूर्णांक dma_sb_map_area(काष्ठा ps3_dma_region *r, अचिन्हित दीर्घ virt_addr,
	   अचिन्हित दीर्घ len, dma_addr_t *bus_addr,
	   u64 iopte_flag)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ flags;
	काष्ठा dma_chunk *c;
	अचिन्हित दीर्घ phys_addr = is_kernel_addr(virt_addr) ? __pa(virt_addr)
		: virt_addr;
	अचिन्हित दीर्घ aligned_phys = ALIGN_DOWN(phys_addr, 1 << r->page_size);
	अचिन्हित दीर्घ aligned_len = ALIGN(len + phys_addr - aligned_phys,
					      1 << r->page_size);
	*bus_addr = dma_sb_lpar_to_bus(r, ps3_mm_phys_to_lpar(phys_addr));

	अगर (!USE_DYNAMIC_DMA) अणु
		अचिन्हित दीर्घ lpar_addr = ps3_mm_phys_to_lpar(phys_addr);
		DBG(" -> %s:%d\n", __func__, __LINE__);
		DBG("%s:%d virt_addr %lxh\n", __func__, __LINE__,
			virt_addr);
		DBG("%s:%d phys_addr %lxh\n", __func__, __LINE__,
			phys_addr);
		DBG("%s:%d lpar_addr %lxh\n", __func__, __LINE__,
			lpar_addr);
		DBG("%s:%d len       %lxh\n", __func__, __LINE__, len);
		DBG("%s:%d bus_addr  %llxh (%lxh)\n", __func__, __LINE__,
		*bus_addr, len);
	पूर्ण

	spin_lock_irqsave(&r->chunk_list.lock, flags);
	c = dma_find_chunk(r, *bus_addr, len);

	अगर (c) अणु
		DBG("%s:%d: reusing mapped chunk", __func__, __LINE__);
		dma_dump_chunk(c);
		c->usage_count++;
		spin_unlock_irqrestore(&r->chunk_list.lock, flags);
		वापस 0;
	पूर्ण

	result = dma_sb_map_pages(r, aligned_phys, aligned_len, &c, iopte_flag);

	अगर (result) अणु
		*bus_addr = 0;
		DBG("%s:%d: dma_sb_map_pages failed (%d)\n",
			__func__, __LINE__, result);
		spin_unlock_irqrestore(&r->chunk_list.lock, flags);
		वापस result;
	पूर्ण

	c->usage_count = 1;

	spin_unlock_irqrestore(&r->chunk_list.lock, flags);
	वापस result;
पूर्ण

अटल पूर्णांक dma_ioc0_map_area(काष्ठा ps3_dma_region *r, अचिन्हित दीर्घ virt_addr,
	     अचिन्हित दीर्घ len, dma_addr_t *bus_addr,
	     u64 iopte_flag)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ flags;
	काष्ठा dma_chunk *c;
	अचिन्हित दीर्घ phys_addr = is_kernel_addr(virt_addr) ? __pa(virt_addr)
		: virt_addr;
	अचिन्हित दीर्घ aligned_phys = ALIGN_DOWN(phys_addr, 1 << r->page_size);
	अचिन्हित दीर्घ aligned_len = ALIGN(len + phys_addr - aligned_phys,
					      1 << r->page_size);

	DBG(KERN_ERR "%s: vaddr=%#lx, len=%#lx\n", __func__,
	    virt_addr, len);
	DBG(KERN_ERR "%s: ph=%#lx a_ph=%#lx a_l=%#lx\n", __func__,
	    phys_addr, aligned_phys, aligned_len);

	spin_lock_irqsave(&r->chunk_list.lock, flags);
	c = dma_find_chunk_lpar(r, ps3_mm_phys_to_lpar(phys_addr), len);

	अगर (c) अणु
		/* FIXME */
		BUG();
		*bus_addr = c->bus_addr + phys_addr - aligned_phys;
		c->usage_count++;
		spin_unlock_irqrestore(&r->chunk_list.lock, flags);
		वापस 0;
	पूर्ण

	result = dma_ioc0_map_pages(r, aligned_phys, aligned_len, &c,
				    iopte_flag);

	अगर (result) अणु
		*bus_addr = 0;
		DBG("%s:%d: dma_ioc0_map_pages failed (%d)\n",
			__func__, __LINE__, result);
		spin_unlock_irqrestore(&r->chunk_list.lock, flags);
		वापस result;
	पूर्ण
	*bus_addr = c->bus_addr + phys_addr - aligned_phys;
	DBG("%s: va=%#lx pa=%#lx a_pa=%#lx bus=%#llx\n", __func__,
	    virt_addr, phys_addr, aligned_phys, *bus_addr);
	c->usage_count = 1;

	spin_unlock_irqrestore(&r->chunk_list.lock, flags);
	वापस result;
पूर्ण

/**
 * dma_sb_unmap_area - Unmap an area of memory from a device dma region.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 * @bus_addr: The starting ioc bus address of the area to unmap.
 * @len: Length in bytes of the area to unmap.
 *
 * This is the common dma unmap routine.
 */

अटल पूर्णांक dma_sb_unmap_area(काष्ठा ps3_dma_region *r, dma_addr_t bus_addr,
	अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_chunk *c;

	spin_lock_irqsave(&r->chunk_list.lock, flags);
	c = dma_find_chunk(r, bus_addr, len);

	अगर (!c) अणु
		अचिन्हित दीर्घ aligned_bus = ALIGN_DOWN(bus_addr,
			1 << r->page_size);
		अचिन्हित दीर्घ aligned_len = ALIGN(len + bus_addr
			- aligned_bus, 1 << r->page_size);
		DBG("%s:%d: not found: bus_addr %llxh\n",
			__func__, __LINE__, bus_addr);
		DBG("%s:%d: not found: len %lxh\n",
			__func__, __LINE__, len);
		DBG("%s:%d: not found: aligned_bus %lxh\n",
			__func__, __LINE__, aligned_bus);
		DBG("%s:%d: not found: aligned_len %lxh\n",
			__func__, __LINE__, aligned_len);
		BUG();
	पूर्ण

	c->usage_count--;

	अगर (!c->usage_count) अणु
		list_del(&c->link);
		dma_sb_मुक्त_chunk(c);
	पूर्ण

	spin_unlock_irqrestore(&r->chunk_list.lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक dma_ioc0_unmap_area(काष्ठा ps3_dma_region *r,
			dma_addr_t bus_addr, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dma_chunk *c;

	DBG("%s: start a=%#llx l=%#lx\n", __func__, bus_addr, len);
	spin_lock_irqsave(&r->chunk_list.lock, flags);
	c = dma_find_chunk(r, bus_addr, len);

	अगर (!c) अणु
		अचिन्हित दीर्घ aligned_bus = ALIGN_DOWN(bus_addr,
							1 << r->page_size);
		अचिन्हित दीर्घ aligned_len = ALIGN(len + bus_addr
						      - aligned_bus,
						      1 << r->page_size);
		DBG("%s:%d: not found: bus_addr %llxh\n",
		    __func__, __LINE__, bus_addr);
		DBG("%s:%d: not found: len %lxh\n",
		    __func__, __LINE__, len);
		DBG("%s:%d: not found: aligned_bus %lxh\n",
		    __func__, __LINE__, aligned_bus);
		DBG("%s:%d: not found: aligned_len %lxh\n",
		    __func__, __LINE__, aligned_len);
		BUG();
	पूर्ण

	c->usage_count--;

	अगर (!c->usage_count) अणु
		list_del(&c->link);
		dma_ioc0_मुक्त_chunk(c);
	पूर्ण

	spin_unlock_irqrestore(&r->chunk_list.lock, flags);
	DBG("%s: end\n", __func__);
	वापस 0;
पूर्ण

/**
 * dma_sb_region_create_linear - Setup a linear dma mapping क्रम a device.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 *
 * This routine creates an HV dma region क्रम the device and maps all available
 * ram पूर्णांकo the io controller bus address space.
 */

अटल पूर्णांक dma_sb_region_create_linear(काष्ठा ps3_dma_region *r)
अणु
	पूर्णांक result;
	अचिन्हित दीर्घ virt_addr, len;
	dma_addr_t पंचांगp;

	अगर (r->len > 16*1024*1024) अणु	/* FIXME: need proper fix */
		/* क्रमce 16M dma pages क्रम linear mapping */
		अगर (r->page_size != PS3_DMA_16M) अणु
			pr_info("%s:%d: forcing 16M pages for linear map\n",
				__func__, __LINE__);
			r->page_size = PS3_DMA_16M;
			r->len = ALIGN(r->len, 1 << r->page_size);
		पूर्ण
	पूर्ण

	result = dma_sb_region_create(r);
	BUG_ON(result);

	अगर (r->offset < map.rm.size) अणु
		/* Map (part of) 1st RAM chunk */
		virt_addr = map.rm.base + r->offset;
		len = map.rm.size - r->offset;
		अगर (len > r->len)
			len = r->len;
		result = dma_sb_map_area(r, virt_addr, len, &पंचांगp,
			CBE_IOPTE_PP_W | CBE_IOPTE_PP_R | CBE_IOPTE_SO_RW |
			CBE_IOPTE_M);
		BUG_ON(result);
	पूर्ण

	अगर (r->offset + r->len > map.rm.size) अणु
		/* Map (part of) 2nd RAM chunk */
		virt_addr = map.rm.size;
		len = r->len;
		अगर (r->offset >= map.rm.size)
			virt_addr += r->offset - map.rm.size;
		अन्यथा
			len -= map.rm.size - r->offset;
		result = dma_sb_map_area(r, virt_addr, len, &पंचांगp,
			CBE_IOPTE_PP_W | CBE_IOPTE_PP_R | CBE_IOPTE_SO_RW |
			CBE_IOPTE_M);
		BUG_ON(result);
	पूर्ण

	वापस result;
पूर्ण

/**
 * dma_sb_region_मुक्त_linear - Free a linear dma mapping क्रम a device.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 *
 * This routine will unmap all mapped areas and मुक्त the HV dma region.
 */

अटल पूर्णांक dma_sb_region_मुक्त_linear(काष्ठा ps3_dma_region *r)
अणु
	पूर्णांक result;
	dma_addr_t bus_addr;
	अचिन्हित दीर्घ len, lpar_addr;

	अगर (r->offset < map.rm.size) अणु
		/* Unmap (part of) 1st RAM chunk */
		lpar_addr = map.rm.base + r->offset;
		len = map.rm.size - r->offset;
		अगर (len > r->len)
			len = r->len;
		bus_addr = dma_sb_lpar_to_bus(r, lpar_addr);
		result = dma_sb_unmap_area(r, bus_addr, len);
		BUG_ON(result);
	पूर्ण

	अगर (r->offset + r->len > map.rm.size) अणु
		/* Unmap (part of) 2nd RAM chunk */
		lpar_addr = map.r1.base;
		len = r->len;
		अगर (r->offset >= map.rm.size)
			lpar_addr += r->offset - map.rm.size;
		अन्यथा
			len -= map.rm.size - r->offset;
		bus_addr = dma_sb_lpar_to_bus(r, lpar_addr);
		result = dma_sb_unmap_area(r, bus_addr, len);
		BUG_ON(result);
	पूर्ण

	result = dma_sb_region_मुक्त(r);
	BUG_ON(result);

	वापस result;
पूर्ण

/**
 * dma_sb_map_area_linear - Map an area of memory पूर्णांकo a device dma region.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 * @virt_addr: Starting भव address of the area to map.
 * @len: Length in bytes of the area to map.
 * @bus_addr: A poपूर्णांकer to वापस the starting ioc bus address of the area to
 * map.
 *
 * This routine just वापसs the corresponding bus address.  Actual mapping
 * occurs in dma_region_create_linear().
 */

अटल पूर्णांक dma_sb_map_area_linear(काष्ठा ps3_dma_region *r,
	अचिन्हित दीर्घ virt_addr, अचिन्हित दीर्घ len, dma_addr_t *bus_addr,
	u64 iopte_flag)
अणु
	अचिन्हित दीर्घ phys_addr = is_kernel_addr(virt_addr) ? __pa(virt_addr)
		: virt_addr;
	*bus_addr = dma_sb_lpar_to_bus(r, ps3_mm_phys_to_lpar(phys_addr));
	वापस 0;
पूर्ण

/**
 * dma_unmap_area_linear - Unmap an area of memory from a device dma region.
 * @r: Poपूर्णांकer to a काष्ठा ps3_dma_region.
 * @bus_addr: The starting ioc bus address of the area to unmap.
 * @len: Length in bytes of the area to unmap.
 *
 * This routine करोes nothing.  Unmapping occurs in dma_sb_region_मुक्त_linear().
 */

अटल पूर्णांक dma_sb_unmap_area_linear(काष्ठा ps3_dma_region *r,
	dma_addr_t bus_addr, अचिन्हित दीर्घ len)
अणु
	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा ps3_dma_region_ops ps3_dma_sb_region_ops =  अणु
	.create = dma_sb_region_create,
	.मुक्त = dma_sb_region_मुक्त,
	.map = dma_sb_map_area,
	.unmap = dma_sb_unmap_area
पूर्ण;

अटल स्थिर काष्ठा ps3_dma_region_ops ps3_dma_sb_region_linear_ops = अणु
	.create = dma_sb_region_create_linear,
	.मुक्त = dma_sb_region_मुक्त_linear,
	.map = dma_sb_map_area_linear,
	.unmap = dma_sb_unmap_area_linear
पूर्ण;

अटल स्थिर काष्ठा ps3_dma_region_ops ps3_dma_ioc0_region_ops = अणु
	.create = dma_ioc0_region_create,
	.मुक्त = dma_ioc0_region_मुक्त,
	.map = dma_ioc0_map_area,
	.unmap = dma_ioc0_unmap_area
पूर्ण;

पूर्णांक ps3_dma_region_init(काष्ठा ps3_प्रणाली_bus_device *dev,
	काष्ठा ps3_dma_region *r, क्रमागत ps3_dma_page_size page_size,
	क्रमागत ps3_dma_region_type region_type, व्योम *addr, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ lpar_addr;

	lpar_addr = addr ? ps3_mm_phys_to_lpar(__pa(addr)) : 0;

	r->dev = dev;
	r->page_size = page_size;
	r->region_type = region_type;
	r->offset = lpar_addr;
	अगर (r->offset >= map.rm.size)
		r->offset -= map.r1.offset;
	r->len = len ? len : ALIGN(map.total, 1 << r->page_size);

	चयन (dev->dev_type) अणु
	हाल PS3_DEVICE_TYPE_SB:
		r->region_ops =  (USE_DYNAMIC_DMA)
			? &ps3_dma_sb_region_ops
			: &ps3_dma_sb_region_linear_ops;
		अवरोध;
	हाल PS3_DEVICE_TYPE_IOC0:
		r->region_ops = &ps3_dma_ioc0_region_ops;
		अवरोध;
	शेष:
		BUG();
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ps3_dma_region_init);

पूर्णांक ps3_dma_region_create(काष्ठा ps3_dma_region *r)
अणु
	BUG_ON(!r);
	BUG_ON(!r->region_ops);
	BUG_ON(!r->region_ops->create);
	वापस r->region_ops->create(r);
पूर्ण
EXPORT_SYMBOL(ps3_dma_region_create);

पूर्णांक ps3_dma_region_मुक्त(काष्ठा ps3_dma_region *r)
अणु
	BUG_ON(!r);
	BUG_ON(!r->region_ops);
	BUG_ON(!r->region_ops->मुक्त);
	वापस r->region_ops->मुक्त(r);
पूर्ण
EXPORT_SYMBOL(ps3_dma_region_मुक्त);

पूर्णांक ps3_dma_map(काष्ठा ps3_dma_region *r, अचिन्हित दीर्घ virt_addr,
	अचिन्हित दीर्घ len, dma_addr_t *bus_addr,
	u64 iopte_flag)
अणु
	वापस r->region_ops->map(r, virt_addr, len, bus_addr, iopte_flag);
पूर्ण

पूर्णांक ps3_dma_unmap(काष्ठा ps3_dma_region *r, dma_addr_t bus_addr,
	अचिन्हित दीर्घ len)
अणु
	वापस r->region_ops->unmap(r, bus_addr, len);
पूर्ण

/*============================================================================*/
/* प्रणाली startup routines                                                    */
/*============================================================================*/

/**
 * ps3_mm_init - initialize the address space state variables
 */

व्योम __init ps3_mm_init(व्योम)
अणु
	पूर्णांक result;

	DBG(" -> %s:%d\n", __func__, __LINE__);

	result = ps3_repository_पढ़ो_mm_info(&map.rm.base, &map.rm.size,
		&map.total);

	अगर (result)
		panic("ps3_repository_read_mm_info() failed");

	map.rm.offset = map.rm.base;
	map.vas_id = map.htab_size = 0;

	/* this implementation assumes map.rm.base is zero */

	BUG_ON(map.rm.base);
	BUG_ON(!map.rm.size);

	/* Check अगर we got the highmem region from an earlier boot step */

	अगर (ps3_mm_get_repository_highmem(&map.r1)) अणु
		result = ps3_mm_region_create(&map.r1, map.total - map.rm.size);

		अगर (!result)
			ps3_mm_set_repository_highmem(&map.r1);
	पूर्ण

	/* correct map.total क्रम the real total amount of memory we use */
	map.total = map.rm.size + map.r1.size;

	अगर (!map.r1.size) अणु
		DBG("%s:%d: No highmem region found\n", __func__, __LINE__);
	पूर्ण अन्यथा अणु
		DBG("%s:%d: Adding highmem region: %llxh %llxh\n",
			__func__, __LINE__, map.rm.size,
			map.total - map.rm.size);
		memblock_add(map.rm.size, map.total - map.rm.size);
	पूर्ण

	DBG(" <- %s:%d\n", __func__, __LINE__);
पूर्ण

/**
 * ps3_mm_shutकरोwn - final cleanup of address space
 */

व्योम ps3_mm_shutकरोwn(व्योम)
अणु
	ps3_mm_region_destroy(&map.r1);
पूर्ण
