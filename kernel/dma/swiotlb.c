<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dynamic DMA mapping support.
 *
 * This implementation is a fallback क्रम platक्रमms that करो not support
 * I/O TLBs (aka DMA address translation hardware).
 * Copyright (C) 2000 Asit Mallick <Asit.K.Mallick@पूर्णांकel.com>
 * Copyright (C) 2000 Goutham Rao <goutham.rao@पूर्णांकel.com>
 * Copyright (C) 2000, 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * 03/05/07 davidm	Switch from PCI-DMA to generic device DMA API.
 * 00/12/13 davidm	Rename to swiotlb.c and add mark_clean() to aव्योम
 *			unnecessary i-cache flushing.
 * 04/07/.. ak		Better overflow handling. Assorted fixes.
 * 05/09/10 linville	Add support क्रम syncing ranges, support syncing क्रम
 *			DMA_BIसूचीECTIONAL mappings, miscellaneous cleanup.
 * 08/12/11 beckyb	Add highmem support
 */

#घोषणा pr_fmt(fmt) "software IO TLB: " fmt

#समावेश <linux/cache.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/mm.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/swiotlb.h>
#समावेश <linux/pfn.h>
#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/set_memory.h>
#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
#पूर्ण_अगर

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>

#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/iommu-helper.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/swiotlb.h>

#घोषणा SLABS_PER_PAGE (1 << (PAGE_SHIFT - IO_TLB_SHIFT))

/*
 * Minimum IO TLB size to bother booting with.  Systems with मुख्यly
 * 64bit capable cards will only lightly use the swiotlb.  If we can't
 * allocate a contiguous 1MB, we're probably in trouble anyway.
 */
#घोषणा IO_TLB_MIN_SLABS ((1<<20) >> IO_TLB_SHIFT)

#घोषणा INVALID_PHYS_ADDR (~(phys_addr_t)0)

क्रमागत swiotlb_क्रमce swiotlb_क्रमce;

काष्ठा io_tlb_mem *io_tlb_शेष_mem;

/*
 * Max segment that we can provide which (अगर pages are contingous) will
 * not be bounced (unless SWIOTLB_FORCE is set).
 */
अटल अचिन्हित पूर्णांक max_segment;

अटल अचिन्हित दीर्घ शेष_nsद_असल = IO_TLB_DEFAULT_SIZE >> IO_TLB_SHIFT;

अटल पूर्णांक __init
setup_io_tlb_npages(अक्षर *str)
अणु
	अगर (है_अंक(*str)) अणु
		/* aव्योम tail segment of size < IO_TLB_SEGSIZE */
		शेष_nsद_असल =
			ALIGN(simple_म_से_अदीर्घ(str, &str, 0), IO_TLB_SEGSIZE);
	पूर्ण
	अगर (*str == ',')
		++str;
	अगर (!म_भेद(str, "force"))
		swiotlb_क्रमce = SWIOTLB_FORCE;
	अन्यथा अगर (!म_भेद(str, "noforce"))
		swiotlb_क्रमce = SWIOTLB_NO_FORCE;

	वापस 0;
पूर्ण
early_param("swiotlb", setup_io_tlb_npages);

अचिन्हित पूर्णांक swiotlb_max_segment(व्योम)
अणु
	वापस io_tlb_शेष_mem ? max_segment : 0;
पूर्ण
EXPORT_SYMBOL_GPL(swiotlb_max_segment);

व्योम swiotlb_set_max_segment(अचिन्हित पूर्णांक val)
अणु
	अगर (swiotlb_क्रमce == SWIOTLB_FORCE)
		max_segment = 1;
	अन्यथा
		max_segment = roundकरोwn(val, PAGE_SIZE);
पूर्ण

अचिन्हित दीर्घ swiotlb_size_or_शेष(व्योम)
अणु
	वापस शेष_nsद_असल << IO_TLB_SHIFT;
पूर्ण

व्योम __init swiotlb_adjust_size(अचिन्हित दीर्घ size)
अणु
	/*
	 * If swiotlb parameter has not been specअगरied, give a chance to
	 * architectures such as those supporting memory encryption to
	 * adjust/expand SWIOTLB size क्रम their use.
	 */
	अगर (शेष_nsद_असल != IO_TLB_DEFAULT_SIZE >> IO_TLB_SHIFT)
		वापस;
	size = ALIGN(size, IO_TLB_SIZE);
	शेष_nsद_असल = ALIGN(size >> IO_TLB_SHIFT, IO_TLB_SEGSIZE);
	pr_info("SWIOTLB bounce buffer size adjusted to %luMB", size >> 20);
पूर्ण

व्योम swiotlb_prपूर्णांक_info(व्योम)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;

	अगर (!mem) अणु
		pr_warn("No low mem\n");
		वापस;
	पूर्ण

	pr_info("mapped [mem %pa-%pa] (%luMB)\n", &mem->start, &mem->end,
	       (mem->nsद_असल << IO_TLB_SHIFT) >> 20);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ io_tlb_offset(अचिन्हित दीर्घ val)
अणु
	वापस val & (IO_TLB_SEGSIZE - 1);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ nr_slots(u64 val)
अणु
	वापस DIV_ROUND_UP(val, IO_TLB_SIZE);
पूर्ण

/*
 * Early SWIOTLB allocation may be too early to allow an architecture to
 * perक्रमm the desired operations.  This function allows the architecture to
 * call SWIOTLB when the operations are possible.  It needs to be called
 * beक्रमe the SWIOTLB memory is used.
 */
व्योम __init swiotlb_update_mem_attributes(व्योम)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;
	व्योम *vaddr;
	अचिन्हित दीर्घ bytes;

	अगर (!mem || mem->late_alloc)
		वापस;
	vaddr = phys_to_virt(mem->start);
	bytes = PAGE_ALIGN(mem->nsद_असल << IO_TLB_SHIFT);
	set_memory_decrypted((अचिन्हित दीर्घ)vaddr, bytes >> PAGE_SHIFT);
	स_रखो(vaddr, 0, bytes);
पूर्ण

पूर्णांक __init swiotlb_init_with_tbl(अक्षर *tlb, अचिन्हित दीर्घ nsद_असल, पूर्णांक verbose)
अणु
	अचिन्हित दीर्घ bytes = nsद_असल << IO_TLB_SHIFT, i;
	काष्ठा io_tlb_mem *mem;
	माप_प्रकार alloc_size;

	अगर (swiotlb_क्रमce == SWIOTLB_NO_FORCE)
		वापस 0;

	/* protect against द्विगुन initialization */
	अगर (WARN_ON_ONCE(io_tlb_शेष_mem))
		वापस -ENOMEM;

	alloc_size = PAGE_ALIGN(काष्ठा_size(mem, slots, nsद_असल));
	mem = memblock_alloc(alloc_size, PAGE_SIZE);
	अगर (!mem)
		panic("%s: Failed to allocate %zu bytes align=0x%lx\n",
		      __func__, alloc_size, PAGE_SIZE);
	mem->nsद_असल = nsद_असल;
	mem->start = __pa(tlb);
	mem->end = mem->start + bytes;
	mem->index = 0;
	spin_lock_init(&mem->lock);
	क्रम (i = 0; i < mem->nsद_असल; i++) अणु
		mem->slots[i].list = IO_TLB_SEGSIZE - io_tlb_offset(i);
		mem->slots[i].orig_addr = INVALID_PHYS_ADDR;
		mem->slots[i].alloc_size = 0;
	पूर्ण

	io_tlb_शेष_mem = mem;
	अगर (verbose)
		swiotlb_prपूर्णांक_info();
	swiotlb_set_max_segment(mem->nsद_असल << IO_TLB_SHIFT);
	वापस 0;
पूर्ण

/*
 * Statically reserve bounce buffer space and initialize bounce buffer data
 * काष्ठाures क्रम the software IO TLB used to implement the DMA API.
 */
व्योम  __init
swiotlb_init(पूर्णांक verbose)
अणु
	माप_प्रकार bytes = PAGE_ALIGN(शेष_nsद_असल << IO_TLB_SHIFT);
	व्योम *tlb;

	अगर (swiotlb_क्रमce == SWIOTLB_NO_FORCE)
		वापस;

	/* Get IO TLB memory from the low pages */
	tlb = memblock_alloc_low(bytes, PAGE_SIZE);
	अगर (!tlb)
		जाओ fail;
	अगर (swiotlb_init_with_tbl(tlb, शेष_nsद_असल, verbose))
		जाओ fail_मुक्त_mem;
	वापस;

fail_मुक्त_mem:
	memblock_मुक्त_early(__pa(tlb), bytes);
fail:
	pr_warn("Cannot allocate buffer");
पूर्ण

/*
 * Systems with larger DMA zones (those that करोn't support ISA) can
 * initialize the swiotlb later using the slab allocator अगर needed.
 * This should be just like above, but with some error catching.
 */
पूर्णांक
swiotlb_late_init_with_शेष_size(माप_प्रकार शेष_size)
अणु
	अचिन्हित दीर्घ nsद_असल =
		ALIGN(शेष_size >> IO_TLB_SHIFT, IO_TLB_SEGSIZE);
	अचिन्हित दीर्घ bytes;
	अचिन्हित अक्षर *vstart = शून्य;
	अचिन्हित पूर्णांक order;
	पूर्णांक rc = 0;

	अगर (swiotlb_क्रमce == SWIOTLB_NO_FORCE)
		वापस 0;

	/*
	 * Get IO TLB memory from the low pages
	 */
	order = get_order(nsद_असल << IO_TLB_SHIFT);
	nsद_असल = SLABS_PER_PAGE << order;
	bytes = nsद_असल << IO_TLB_SHIFT;

	जबतक ((SLABS_PER_PAGE << order) > IO_TLB_MIN_SLABS) अणु
		vstart = (व्योम *)__get_मुक्त_pages(GFP_DMA | __GFP_NOWARN,
						  order);
		अगर (vstart)
			अवरोध;
		order--;
	पूर्ण

	अगर (!vstart)
		वापस -ENOMEM;

	अगर (order != get_order(bytes)) अणु
		pr_warn("only able to allocate %ld MB\n",
			(PAGE_SIZE << order) >> 20);
		nsद_असल = SLABS_PER_PAGE << order;
	पूर्ण
	rc = swiotlb_late_init_with_tbl(vstart, nsद_असल);
	अगर (rc)
		मुक्त_pages((अचिन्हित दीर्घ)vstart, order);

	वापस rc;
पूर्ण

पूर्णांक
swiotlb_late_init_with_tbl(अक्षर *tlb, अचिन्हित दीर्घ nsद_असल)
अणु
	अचिन्हित दीर्घ bytes = nsद_असल << IO_TLB_SHIFT, i;
	काष्ठा io_tlb_mem *mem;

	अगर (swiotlb_क्रमce == SWIOTLB_NO_FORCE)
		वापस 0;

	/* protect against द्विगुन initialization */
	अगर (WARN_ON_ONCE(io_tlb_शेष_mem))
		वापस -ENOMEM;

	mem = (व्योम *)__get_मुक्त_pages(GFP_KERNEL,
		get_order(काष्ठा_size(mem, slots, nsद_असल)));
	अगर (!mem)
		वापस -ENOMEM;

	mem->nsद_असल = nsद_असल;
	mem->start = virt_to_phys(tlb);
	mem->end = mem->start + bytes;
	mem->index = 0;
	mem->late_alloc = 1;
	spin_lock_init(&mem->lock);
	क्रम (i = 0; i < mem->nsद_असल; i++) अणु
		mem->slots[i].list = IO_TLB_SEGSIZE - io_tlb_offset(i);
		mem->slots[i].orig_addr = INVALID_PHYS_ADDR;
		mem->slots[i].alloc_size = 0;
	पूर्ण

	set_memory_decrypted((अचिन्हित दीर्घ)tlb, bytes >> PAGE_SHIFT);
	स_रखो(tlb, 0, bytes);

	io_tlb_शेष_mem = mem;
	swiotlb_prपूर्णांक_info();
	swiotlb_set_max_segment(mem->nsद_असल << IO_TLB_SHIFT);
	वापस 0;
पूर्ण

व्योम __init swiotlb_निकास(व्योम)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;
	माप_प्रकार size;

	अगर (!mem)
		वापस;

	size = काष्ठा_size(mem, slots, mem->nsद_असल);
	अगर (mem->late_alloc)
		मुक्त_pages((अचिन्हित दीर्घ)mem, get_order(size));
	अन्यथा
		memblock_मुक्त_late(__pa(mem), PAGE_ALIGN(size));
	io_tlb_शेष_mem = शून्य;
पूर्ण

/*
 * Return the offset पूर्णांकo a iotlb slot required to keep the device happy.
 */
अटल अचिन्हित पूर्णांक swiotlb_align_offset(काष्ठा device *dev, u64 addr)
अणु
	वापस addr & dma_get_min_align_mask(dev) & (IO_TLB_SIZE - 1);
पूर्ण

/*
 * Bounce: copy the swiotlb buffer from or back to the original dma location
 */
अटल व्योम swiotlb_bounce(काष्ठा device *dev, phys_addr_t tlb_addr, माप_प्रकार size,
			   क्रमागत dma_data_direction dir)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;
	पूर्णांक index = (tlb_addr - mem->start) >> IO_TLB_SHIFT;
	phys_addr_t orig_addr = mem->slots[index].orig_addr;
	माप_प्रकार alloc_size = mem->slots[index].alloc_size;
	अचिन्हित दीर्घ pfn = PFN_DOWN(orig_addr);
	अचिन्हित अक्षर *vaddr = phys_to_virt(tlb_addr);
	अचिन्हित पूर्णांक tlb_offset;

	अगर (orig_addr == INVALID_PHYS_ADDR)
		वापस;

	tlb_offset = (tlb_addr & (IO_TLB_SIZE - 1)) -
		     swiotlb_align_offset(dev, orig_addr);

	orig_addr += tlb_offset;
	alloc_size -= tlb_offset;

	अगर (size > alloc_size) अणु
		dev_WARN_ONCE(dev, 1,
			"Buffer overflow detected. Allocation size: %zu. Mapping size: %zu.\n",
			alloc_size, size);
		size = alloc_size;
	पूर्ण

	अगर (PageHighMem(pfn_to_page(pfn))) अणु
		/* The buffer करोes not have a mapping.  Map it in and copy */
		अचिन्हित पूर्णांक offset = orig_addr & ~PAGE_MASK;
		अक्षर *buffer;
		अचिन्हित पूर्णांक sz = 0;
		अचिन्हित दीर्घ flags;

		जबतक (size) अणु
			sz = min_t(माप_प्रकार, PAGE_SIZE - offset, size);

			local_irq_save(flags);
			buffer = kmap_atomic(pfn_to_page(pfn));
			अगर (dir == DMA_TO_DEVICE)
				स_नकल(vaddr, buffer + offset, sz);
			अन्यथा
				स_नकल(buffer + offset, vaddr, sz);
			kunmap_atomic(buffer);
			local_irq_restore(flags);

			size -= sz;
			pfn++;
			vaddr += sz;
			offset = 0;
		पूर्ण
	पूर्ण अन्यथा अगर (dir == DMA_TO_DEVICE) अणु
		स_नकल(vaddr, phys_to_virt(orig_addr), size);
	पूर्ण अन्यथा अणु
		स_नकल(phys_to_virt(orig_addr), vaddr, size);
	पूर्ण
पूर्ण

#घोषणा slot_addr(start, idx)	((start) + ((idx) << IO_TLB_SHIFT))

/*
 * Carefully handle पूर्णांकeger overflow which can occur when boundary_mask == ~0UL.
 */
अटल अंतरभूत अचिन्हित दीर्घ get_max_slots(अचिन्हित दीर्घ boundary_mask)
अणु
	अगर (boundary_mask == ~0UL)
		वापस 1UL << (BITS_PER_LONG - IO_TLB_SHIFT);
	वापस nr_slots(boundary_mask + 1);
पूर्ण

अटल अचिन्हित पूर्णांक wrap_index(काष्ठा io_tlb_mem *mem, अचिन्हित पूर्णांक index)
अणु
	अगर (index >= mem->nsद_असल)
		वापस 0;
	वापस index;
पूर्ण

/*
 * Find a suitable number of IO TLB entries size that will fit this request and
 * allocate a buffer from that IO TLB pool.
 */
अटल पूर्णांक find_slots(काष्ठा device *dev, phys_addr_t orig_addr,
		माप_प्रकार alloc_size)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;
	अचिन्हित दीर्घ boundary_mask = dma_get_seg_boundary(dev);
	dma_addr_t tbl_dma_addr =
		phys_to_dma_unencrypted(dev, mem->start) & boundary_mask;
	अचिन्हित दीर्घ max_slots = get_max_slots(boundary_mask);
	अचिन्हित पूर्णांक iotlb_align_mask =
		dma_get_min_align_mask(dev) & ~(IO_TLB_SIZE - 1);
	अचिन्हित पूर्णांक nslots = nr_slots(alloc_size), stride;
	अचिन्हित पूर्णांक index, wrap, count = 0, i;
	अचिन्हित दीर्घ flags;

	BUG_ON(!nslots);

	/*
	 * For mappings with an alignment requirement करोn't bother looping to
	 * unaligned slots once we found an aligned one.  For allocations of
	 * PAGE_SIZE or larger only look क्रम page aligned allocations.
	 */
	stride = (iotlb_align_mask >> IO_TLB_SHIFT) + 1;
	अगर (alloc_size >= PAGE_SIZE)
		stride = max(stride, stride << (PAGE_SHIFT - IO_TLB_SHIFT));

	spin_lock_irqsave(&mem->lock, flags);
	अगर (unlikely(nslots > mem->nsद_असल - mem->used))
		जाओ not_found;

	index = wrap = wrap_index(mem, ALIGN(mem->index, stride));
	करो अणु
		अगर ((slot_addr(tbl_dma_addr, index) & iotlb_align_mask) !=
		    (orig_addr & iotlb_align_mask)) अणु
			index = wrap_index(mem, index + 1);
			जारी;
		पूर्ण

		/*
		 * If we find a slot that indicates we have 'nslots' number of
		 * contiguous buffers, we allocate the buffers from that slot
		 * and mark the entries as '0' indicating unavailable.
		 */
		अगर (!iommu_is_span_boundary(index, nslots,
					    nr_slots(tbl_dma_addr),
					    max_slots)) अणु
			अगर (mem->slots[index].list >= nslots)
				जाओ found;
		पूर्ण
		index = wrap_index(mem, index + stride);
	पूर्ण जबतक (index != wrap);

not_found:
	spin_unlock_irqrestore(&mem->lock, flags);
	वापस -1;

found:
	क्रम (i = index; i < index + nslots; i++)
		mem->slots[i].list = 0;
	क्रम (i = index - 1;
	     io_tlb_offset(i) != IO_TLB_SEGSIZE - 1 &&
	     mem->slots[i].list; i--)
		mem->slots[i].list = ++count;

	/*
	 * Update the indices to aव्योम searching in the next round.
	 */
	अगर (index + nslots < mem->nsद_असल)
		mem->index = index + nslots;
	अन्यथा
		mem->index = 0;
	mem->used += nslots;

	spin_unlock_irqrestore(&mem->lock, flags);
	वापस index;
पूर्ण

phys_addr_t swiotlb_tbl_map_single(काष्ठा device *dev, phys_addr_t orig_addr,
		माप_प्रकार mapping_size, माप_प्रकार alloc_size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;
	अचिन्हित पूर्णांक offset = swiotlb_align_offset(dev, orig_addr);
	अचिन्हित पूर्णांक i;
	पूर्णांक index;
	phys_addr_t tlb_addr;

	अगर (!mem)
		panic("Can not allocate SWIOTLB buffer earlier and can't now provide you with the DMA bounce buffer");

	अगर (mem_encrypt_active())
		pr_warn_once("Memory encryption is active and system is using DMA bounce buffers\n");

	अगर (mapping_size > alloc_size) अणु
		dev_warn_once(dev, "Invalid sizes (mapping: %zd bytes, alloc: %zd bytes)",
			      mapping_size, alloc_size);
		वापस (phys_addr_t)DMA_MAPPING_ERROR;
	पूर्ण

	index = find_slots(dev, orig_addr, alloc_size + offset);
	अगर (index == -1) अणु
		अगर (!(attrs & DMA_ATTR_NO_WARN))
			dev_warn_ratelimited(dev,
	"swiotlb buffer is full (sz: %zd bytes), total %lu (slots), used %lu (slots)\n",
				 alloc_size, mem->nsद_असल, mem->used);
		वापस (phys_addr_t)DMA_MAPPING_ERROR;
	पूर्ण

	/*
	 * Save away the mapping from the original address to the DMA address.
	 * This is needed when we sync the memory.  Then we sync the buffer अगर
	 * needed.
	 */
	क्रम (i = 0; i < nr_slots(alloc_size + offset); i++) अणु
		mem->slots[index + i].orig_addr = slot_addr(orig_addr, i);
		mem->slots[index + i].alloc_size =
			alloc_size - (i << IO_TLB_SHIFT);
	पूर्ण
	tlb_addr = slot_addr(mem->start, index) + offset;
	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC) &&
	    (dir == DMA_TO_DEVICE || dir == DMA_BIसूचीECTIONAL))
		swiotlb_bounce(dev, tlb_addr, mapping_size, DMA_TO_DEVICE);
	वापस tlb_addr;
पूर्ण

/*
 * tlb_addr is the physical address of the bounce buffer to unmap.
 */
व्योम swiotlb_tbl_unmap_single(काष्ठा device *hwdev, phys_addr_t tlb_addr,
			      माप_प्रकार mapping_size, क्रमागत dma_data_direction dir,
			      अचिन्हित दीर्घ attrs)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक offset = swiotlb_align_offset(hwdev, tlb_addr);
	पूर्णांक index = (tlb_addr - offset - mem->start) >> IO_TLB_SHIFT;
	पूर्णांक nslots = nr_slots(mem->slots[index].alloc_size + offset);
	पूर्णांक count, i;

	/*
	 * First, sync the memory beक्रमe unmapping the entry
	 */
	अगर (!(attrs & DMA_ATTR_SKIP_CPU_SYNC) &&
	    (dir == DMA_FROM_DEVICE || dir == DMA_BIसूचीECTIONAL))
		swiotlb_bounce(hwdev, tlb_addr, mapping_size, DMA_FROM_DEVICE);

	/*
	 * Return the buffer to the मुक्त list by setting the corresponding
	 * entries to indicate the number of contiguous entries available.
	 * While वापसing the entries to the मुक्त list, we merge the entries
	 * with slots below and above the pool being वापसed.
	 */
	spin_lock_irqsave(&mem->lock, flags);
	अगर (index + nslots < ALIGN(index + 1, IO_TLB_SEGSIZE))
		count = mem->slots[index + nslots].list;
	अन्यथा
		count = 0;

	/*
	 * Step 1: वापस the slots to the मुक्त list, merging the slots with
	 * superceeding slots
	 */
	क्रम (i = index + nslots - 1; i >= index; i--) अणु
		mem->slots[i].list = ++count;
		mem->slots[i].orig_addr = INVALID_PHYS_ADDR;
		mem->slots[i].alloc_size = 0;
	पूर्ण

	/*
	 * Step 2: merge the वापसed slots with the preceding slots, अगर
	 * available (non zero)
	 */
	क्रम (i = index - 1;
	     io_tlb_offset(i) != IO_TLB_SEGSIZE - 1 && mem->slots[i].list;
	     i--)
		mem->slots[i].list = ++count;
	mem->used -= nslots;
	spin_unlock_irqrestore(&mem->lock, flags);
पूर्ण

व्योम swiotlb_sync_single_क्रम_device(काष्ठा device *dev, phys_addr_t tlb_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अगर (dir == DMA_TO_DEVICE || dir == DMA_BIसूचीECTIONAL)
		swiotlb_bounce(dev, tlb_addr, size, DMA_TO_DEVICE);
	अन्यथा
		BUG_ON(dir != DMA_FROM_DEVICE);
पूर्ण

व्योम swiotlb_sync_single_क्रम_cpu(काष्ठा device *dev, phys_addr_t tlb_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	अगर (dir == DMA_FROM_DEVICE || dir == DMA_BIसूचीECTIONAL)
		swiotlb_bounce(dev, tlb_addr, size, DMA_FROM_DEVICE);
	अन्यथा
		BUG_ON(dir != DMA_TO_DEVICE);
पूर्ण

/*
 * Create a swiotlb mapping क्रम the buffer at @paddr, and in हाल of DMAing
 * to the device copy the data पूर्णांकo it as well.
 */
dma_addr_t swiotlb_map(काष्ठा device *dev, phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	phys_addr_t swiotlb_addr;
	dma_addr_t dma_addr;

	trace_swiotlb_bounced(dev, phys_to_dma(dev, paddr), size,
			      swiotlb_क्रमce);

	swiotlb_addr = swiotlb_tbl_map_single(dev, paddr, size, size, dir,
			attrs);
	अगर (swiotlb_addr == (phys_addr_t)DMA_MAPPING_ERROR)
		वापस DMA_MAPPING_ERROR;

	/* Ensure that the address वापसed is DMA'ble */
	dma_addr = phys_to_dma_unencrypted(dev, swiotlb_addr);
	अगर (unlikely(!dma_capable(dev, dma_addr, size, true))) अणु
		swiotlb_tbl_unmap_single(dev, swiotlb_addr, size, dir,
			attrs | DMA_ATTR_SKIP_CPU_SYNC);
		dev_WARN_ONCE(dev, 1,
			"swiotlb addr %pad+%zu overflow (mask %llx, bus limit %llx).\n",
			&dma_addr, size, *dev->dma_mask, dev->bus_dma_limit);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	अगर (!dev_is_dma_coherent(dev) && !(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		arch_sync_dma_क्रम_device(swiotlb_addr, size, dir);
	वापस dma_addr;
पूर्ण

माप_प्रकार swiotlb_max_mapping_size(काष्ठा device *dev)
अणु
	वापस ((माप_प्रकार)IO_TLB_SIZE) * IO_TLB_SEGSIZE;
पूर्ण

bool is_swiotlb_active(व्योम)
अणु
	वापस io_tlb_शेष_mem != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(is_swiotlb_active);

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक __init swiotlb_create_debugfs(व्योम)
अणु
	काष्ठा io_tlb_mem *mem = io_tlb_शेष_mem;

	अगर (!mem)
		वापस 0;
	mem->debugfs = debugfs_create_dir("swiotlb", शून्य);
	debugfs_create_uदीर्घ("io_tlb_nslabs", 0400, mem->debugfs, &mem->nsद_असल);
	debugfs_create_uदीर्घ("io_tlb_used", 0400, mem->debugfs, &mem->used);
	वापस 0;
पूर्ण

late_initcall(swiotlb_create_debugfs);

#पूर्ण_अगर
