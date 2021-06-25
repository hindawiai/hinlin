<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	linux/arch/alpha/kernel/pci_iommu.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pci.h>
#समावेश <linux/gfp.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/log2.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/iommu-helper.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hwrpb.h>

#समावेश "proto.h"
#समावेश "pci_impl.h"


#घोषणा DEBUG_ALLOC 0
#अगर DEBUG_ALLOC > 0
# define DBGA(args...)		prपूर्णांकk(KERN_DEBUG args)
#अन्यथा
# define DBGA(args...)
#पूर्ण_अगर
#अगर DEBUG_ALLOC > 1
# define DBGA2(args...)		prपूर्णांकk(KERN_DEBUG args)
#अन्यथा
# define DBGA2(args...)
#पूर्ण_अगर

#घोषणा DEBUG_NOसूचीECT 0

#घोषणा ISA_DMA_MASK		0x00ffffff

अटल अंतरभूत अचिन्हित दीर्घ
mk_iommu_pte(अचिन्हित दीर्घ paddr)
अणु
	वापस (paddr >> (PAGE_SHIFT-1)) | 1;
पूर्ण

/* Return the minimum of MAX or the first घातer of two larger
   than मुख्य memory.  */

अचिन्हित दीर्घ
size_क्रम_memory(अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ mem = max_low_pfn << PAGE_SHIFT;
	अगर (mem < max)
		max = roundup_घात_of_two(mem);
	वापस max;
पूर्ण

काष्ठा pci_iommu_arena * __init
iommu_arena_new_node(पूर्णांक nid, काष्ठा pci_controller *hose, dma_addr_t base,
		     अचिन्हित दीर्घ winकरोw_size, अचिन्हित दीर्घ align)
अणु
	अचिन्हित दीर्घ mem_size;
	काष्ठा pci_iommu_arena *arena;

	mem_size = winकरोw_size / (PAGE_SIZE / माप(अचिन्हित दीर्घ));

	/* Note that the TLB lookup logic uses bitwise concatenation,
	   not addition, so the required arena alignment is based on
	   the size of the winकरोw.  Retain the align parameter so that
	   particular प्रणालीs can over-align the arena.  */
	अगर (align < mem_size)
		align = mem_size;


#अगर_घोषित CONFIG_DISCONTIGMEM

	arena = memblock_alloc_node(माप(*arena), align, nid);
	अगर (!NODE_DATA(nid) || !arena) अणु
		prपूर्णांकk("%s: couldn't allocate arena from node %d\n"
		       "    falling back to system-wide allocation\n",
		       __func__, nid);
		arena = memblock_alloc(माप(*arena), SMP_CACHE_BYTES);
		अगर (!arena)
			panic("%s: Failed to allocate %zu bytes\n", __func__,
			      माप(*arena));
	पूर्ण

	arena->ptes = memblock_alloc_node(माप(*arena), align, nid);
	अगर (!NODE_DATA(nid) || !arena->ptes) अणु
		prपूर्णांकk("%s: couldn't allocate arena ptes from node %d\n"
		       "    falling back to system-wide allocation\n",
		       __func__, nid);
		arena->ptes = memblock_alloc(mem_size, align);
		अगर (!arena->ptes)
			panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
			      __func__, mem_size, align);
	पूर्ण

#अन्यथा /* CONFIG_DISCONTIGMEM */

	arena = memblock_alloc(माप(*arena), SMP_CACHE_BYTES);
	अगर (!arena)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(*arena));
	arena->ptes = memblock_alloc(mem_size, align);
	अगर (!arena->ptes)
		panic("%s: Failed to allocate %lu bytes align=0x%lx\n",
		      __func__, mem_size, align);

#पूर्ण_अगर /* CONFIG_DISCONTIGMEM */

	spin_lock_init(&arena->lock);
	arena->hose = hose;
	arena->dma_base = base;
	arena->size = winकरोw_size;
	arena->next_entry = 0;

	/* Align allocations to a multiple of a page size.  Not needed
	   unless there are chip bugs.  */
	arena->align_entry = 1;

	वापस arena;
पूर्ण

काष्ठा pci_iommu_arena * __init
iommu_arena_new(काष्ठा pci_controller *hose, dma_addr_t base,
		अचिन्हित दीर्घ winकरोw_size, अचिन्हित दीर्घ align)
अणु
	वापस iommu_arena_new_node(0, hose, base, winकरोw_size, align);
पूर्ण

/* Must be called with the arena lock held */
अटल दीर्घ
iommu_arena_find_pages(काष्ठा device *dev, काष्ठा pci_iommu_arena *arena,
		       दीर्घ n, दीर्घ mask)
अणु
	अचिन्हित दीर्घ *ptes;
	दीर्घ i, p, nent;
	पूर्णांक pass = 0;
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ boundary_size;

	base = arena->dma_base >> PAGE_SHIFT;
	boundary_size = dma_get_seg_boundary_nr_pages(dev, PAGE_SHIFT);

	/* Search क्रमward क्रम the first mask-aligned sequence of N मुक्त ptes */
	ptes = arena->ptes;
	nent = arena->size >> PAGE_SHIFT;
	p = ALIGN(arena->next_entry, mask + 1);
	i = 0;

again:
	जबतक (i < n && p+i < nent) अणु
		अगर (!i && iommu_is_span_boundary(p, n, base, boundary_size)) अणु
			p = ALIGN(p + 1, mask + 1);
			जाओ again;
		पूर्ण

		अगर (ptes[p+i])
			p = ALIGN(p + i + 1, mask + 1), i = 0;
		अन्यथा
			i = i + 1;
	पूर्ण

	अगर (i < n) अणु
		अगर (pass < 1) अणु
			/*
			 * Reached the end.  Flush the TLB and restart
			 * the search from the beginning.
			*/
			alpha_mv.mv_pci_tbi(arena->hose, 0, -1);

			pass++;
			p = 0;
			i = 0;
			जाओ again;
		पूर्ण अन्यथा
			वापस -1;
	पूर्ण

	/* Success. It's the responsibility of the caller to mark them
	   in use beक्रमe releasing the lock */
	वापस p;
पूर्ण

अटल दीर्घ
iommu_arena_alloc(काष्ठा device *dev, काष्ठा pci_iommu_arena *arena, दीर्घ n,
		  अचिन्हित पूर्णांक align)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *ptes;
	दीर्घ i, p, mask;

	spin_lock_irqsave(&arena->lock, flags);

	/* Search क्रम N empty ptes */
	ptes = arena->ptes;
	mask = max(align, arena->align_entry) - 1;
	p = iommu_arena_find_pages(dev, arena, n, mask);
	अगर (p < 0) अणु
		spin_unlock_irqrestore(&arena->lock, flags);
		वापस -1;
	पूर्ण

	/* Success.  Mark them all in use, ie not zero and invalid
	   क्रम the iommu tlb that could load them from under us.
	   The chip specअगरic bits will fill this in with something
	   kosher when we वापस.  */
	क्रम (i = 0; i < n; ++i)
		ptes[p+i] = IOMMU_INVALID_PTE;

	arena->next_entry = p + n;
	spin_unlock_irqrestore(&arena->lock, flags);

	वापस p;
पूर्ण

अटल व्योम
iommu_arena_मुक्त(काष्ठा pci_iommu_arena *arena, दीर्घ ofs, दीर्घ n)
अणु
	अचिन्हित दीर्घ *p;
	दीर्घ i;

	p = arena->ptes + ofs;
	क्रम (i = 0; i < n; ++i)
		p[i] = 0;
पूर्ण

/*
 * True अगर the machine supports DAC addressing, and DEV can
 * make use of it given MASK.
 */
अटल पूर्णांक pci_dac_dma_supported(काष्ठा pci_dev *dev, u64 mask)
अणु
	dma_addr_t dac_offset = alpha_mv.pci_dac_offset;
	पूर्णांक ok = 1;

	/* If this is not set, the machine करोesn't support DAC at all.  */
	अगर (dac_offset == 0)
		ok = 0;

	/* The device has to be able to address our DAC bit.  */
	अगर ((dac_offset & dev->dma_mask) != dac_offset)
		ok = 0;

	/* If both conditions above are met, we are fine. */
	DBGA("pci_dac_dma_supported %s from %ps\n",
	     ok ? "yes" : "no", __builtin_वापस_address(0));

	वापस ok;
पूर्ण

/* Map a single buffer of the indicated size क्रम PCI DMA in streaming
   mode.  The 32-bit PCI bus mastering address to use is वापसed.
   Once the device is given the dma address, the device owns this memory
   until either pci_unmap_single or pci_dma_sync_single is perक्रमmed.  */

अटल dma_addr_t
pci_map_single_1(काष्ठा pci_dev *pdev, व्योम *cpu_addr, माप_प्रकार size,
		 पूर्णांक dac_allowed)
अणु
	काष्ठा pci_controller *hose = pdev ? pdev->sysdata : pci_isa_hose;
	dma_addr_t max_dma = pdev ? pdev->dma_mask : ISA_DMA_MASK;
	काष्ठा pci_iommu_arena *arena;
	दीर्घ npages, dma_ofs, i;
	अचिन्हित दीर्घ paddr;
	dma_addr_t ret;
	अचिन्हित पूर्णांक align = 0;
	काष्ठा device *dev = pdev ? &pdev->dev : शून्य;

	paddr = __pa(cpu_addr);

#अगर !DEBUG_NOसूचीECT
	/* First check to see अगर we can use the direct map winकरोw.  */
	अगर (paddr + size + __direct_map_base - 1 <= max_dma
	    && paddr + size <= __direct_map_size) अणु
		ret = paddr + __direct_map_base;

		DBGA2("pci_map_single: [%p,%zx] -> direct %llx from %ps\n",
		      cpu_addr, size, ret, __builtin_वापस_address(0));

		वापस ret;
	पूर्ण
#पूर्ण_अगर

	/* Next, use DAC अगर selected earlier.  */
	अगर (dac_allowed) अणु
		ret = paddr + alpha_mv.pci_dac_offset;

		DBGA2("pci_map_single: [%p,%zx] -> DAC %llx from %ps\n",
		      cpu_addr, size, ret, __builtin_वापस_address(0));

		वापस ret;
	पूर्ण

	/* If the machine करोesn't define a pci_tbi routine, we have to
	   assume it करोesn't support sg mapping, and, since we tried to
	   use direct_map above, it now must be considered an error. */
	अगर (! alpha_mv.mv_pci_tbi) अणु
		prपूर्णांकk_once(KERN_WARNING "pci_map_single: no HW sg\n");
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	arena = hose->sg_pci;
	अगर (!arena || arena->dma_base + arena->size - 1 > max_dma)
		arena = hose->sg_isa;

	npages = iommu_num_pages(paddr, size, PAGE_SIZE);

	/* Force allocation to 64KB boundary क्रम ISA bridges. */
	अगर (pdev && pdev == isa_bridge)
		align = 8;
	dma_ofs = iommu_arena_alloc(dev, arena, npages, align);
	अगर (dma_ofs < 0) अणु
		prपूर्णांकk(KERN_WARNING "pci_map_single failed: "
		       "could not allocate dma page tables\n");
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	paddr &= PAGE_MASK;
	क्रम (i = 0; i < npages; ++i, paddr += PAGE_SIZE)
		arena->ptes[i + dma_ofs] = mk_iommu_pte(paddr);

	ret = arena->dma_base + dma_ofs * PAGE_SIZE;
	ret += (अचिन्हित दीर्घ)cpu_addr & ~PAGE_MASK;

	DBGA2("pci_map_single: [%p,%zx] np %ld -> sg %llx from %ps\n",
	      cpu_addr, size, npages, ret, __builtin_वापस_address(0));

	वापस ret;
पूर्ण

/* Helper क्रम generic DMA-mapping functions. */
अटल काष्ठा pci_dev *alpha_gendev_to_pci(काष्ठा device *dev)
अणु
	अगर (dev && dev_is_pci(dev))
		वापस to_pci_dev(dev);

	/* Assume that non-PCI devices asking क्रम DMA are either ISA or EISA,
	   BUG() otherwise. */
	BUG_ON(!isa_bridge);

	/* Assume non-busmaster ISA DMA when dma_mask is not set (the ISA
	   bridge is bus master then). */
	अगर (!dev || !dev->dma_mask || !*dev->dma_mask)
		वापस isa_bridge;

	/* For EISA bus masters, वापस isa_bridge (it might have smaller
	   dma_mask due to wiring limitations). */
	अगर (*dev->dma_mask >= isa_bridge->dma_mask)
		वापस isa_bridge;

	/* This assumes ISA bus master with dma_mask 0xffffff. */
	वापस शून्य;
पूर्ण

अटल dma_addr_t alpha_pci_map_page(काष्ठा device *dev, काष्ठा page *page,
				     अचिन्हित दीर्घ offset, माप_प्रकार size,
				     क्रमागत dma_data_direction dir,
				     अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_dev *pdev = alpha_gendev_to_pci(dev);
	पूर्णांक dac_allowed;

	BUG_ON(dir == PCI_DMA_NONE);

	dac_allowed = pdev ? pci_dac_dma_supported(pdev, pdev->dma_mask) : 0; 
	वापस pci_map_single_1(pdev, (अक्षर *)page_address(page) + offset, 
				size, dac_allowed);
पूर्ण

/* Unmap a single streaming mode DMA translation.  The DMA_ADDR and
   SIZE must match what was provided क्रम in a previous pci_map_single
   call.  All other usages are undefined.  After this call, पढ़ोs by
   the cpu to the buffer are guaranteed to see whatever the device
   wrote there.  */

अटल व्योम alpha_pci_unmap_page(काष्ठा device *dev, dma_addr_t dma_addr,
				 माप_प्रकार size, क्रमागत dma_data_direction dir,
				 अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा pci_dev *pdev = alpha_gendev_to_pci(dev);
	काष्ठा pci_controller *hose = pdev ? pdev->sysdata : pci_isa_hose;
	काष्ठा pci_iommu_arena *arena;
	दीर्घ dma_ofs, npages;

	BUG_ON(dir == PCI_DMA_NONE);

	अगर (dma_addr >= __direct_map_base
	    && dma_addr < __direct_map_base + __direct_map_size) अणु
		/* Nothing to करो.  */

		DBGA2("pci_unmap_single: direct [%llx,%zx] from %ps\n",
		      dma_addr, size, __builtin_वापस_address(0));

		वापस;
	पूर्ण

	अगर (dma_addr > 0xffffffff) अणु
		DBGA2("pci64_unmap_single: DAC [%llx,%zx] from %ps\n",
		      dma_addr, size, __builtin_वापस_address(0));
		वापस;
	पूर्ण

	arena = hose->sg_pci;
	अगर (!arena || dma_addr < arena->dma_base)
		arena = hose->sg_isa;

	dma_ofs = (dma_addr - arena->dma_base) >> PAGE_SHIFT;
	अगर (dma_ofs * PAGE_SIZE >= arena->size) अणु
		prपूर्णांकk(KERN_ERR "Bogus pci_unmap_single: dma_addr %llx "
		       " base %llx size %x\n",
		       dma_addr, arena->dma_base, arena->size);
		वापस;
		BUG();
	पूर्ण

	npages = iommu_num_pages(dma_addr, size, PAGE_SIZE);

	spin_lock_irqsave(&arena->lock, flags);

	iommu_arena_मुक्त(arena, dma_ofs, npages);

        /* If we're freeing ptes above the `next_entry' poपूर्णांकer (they
           may have snuck back पूर्णांकo the TLB since the last wrap flush),
           we need to flush the TLB beक्रमe पुनः_स्मृतिating the latter.  */
	अगर (dma_ofs >= arena->next_entry)
		alpha_mv.mv_pci_tbi(hose, dma_addr, dma_addr + size - 1);

	spin_unlock_irqrestore(&arena->lock, flags);

	DBGA2("pci_unmap_single: sg [%llx,%zx] np %ld from %ps\n",
	      dma_addr, size, npages, __builtin_वापस_address(0));
पूर्ण

/* Allocate and map kernel buffer using consistent mode DMA क्रम PCI
   device.  Returns non-शून्य cpu-view poपूर्णांकer to the buffer अगर
   successful and sets *DMA_ADDRP to the pci side dma address as well,
   अन्यथा DMA_ADDRP is undefined.  */

अटल व्योम *alpha_pci_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				      dma_addr_t *dma_addrp, gfp_t gfp,
				      अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_dev *pdev = alpha_gendev_to_pci(dev);
	व्योम *cpu_addr;
	दीर्घ order = get_order(size);

	gfp &= ~GFP_DMA;

try_again:
	cpu_addr = (व्योम *)__get_मुक्त_pages(gfp | __GFP_ZERO, order);
	अगर (! cpu_addr) अणु
		prपूर्णांकk(KERN_INFO "pci_alloc_consistent: "
		       "get_free_pages failed from %ps\n",
			__builtin_वापस_address(0));
		/* ??? Really atomic allocation?  Otherwise we could play
		   with vदो_स्मृति and sg अगर we can't find contiguous memory.  */
		वापस शून्य;
	पूर्ण
	स_रखो(cpu_addr, 0, size);

	*dma_addrp = pci_map_single_1(pdev, cpu_addr, size, 0);
	अगर (*dma_addrp == DMA_MAPPING_ERROR) अणु
		मुक्त_pages((अचिन्हित दीर्घ)cpu_addr, order);
		अगर (alpha_mv.mv_pci_tbi || (gfp & GFP_DMA))
			वापस शून्य;
		/* The address करोesn't fit required mask and we
		   करो not have iommu. Try again with GFP_DMA. */
		gfp |= GFP_DMA;
		जाओ try_again;
	पूर्ण

	DBGA2("pci_alloc_consistent: %zx -> [%p,%llx] from %ps\n",
	      size, cpu_addr, *dma_addrp, __builtin_वापस_address(0));

	वापस cpu_addr;
पूर्ण

/* Free and unmap a consistent DMA buffer.  CPU_ADDR and DMA_ADDR must
   be values that were वापसed from pci_alloc_consistent.  SIZE must
   be the same as what as passed पूर्णांकo pci_alloc_consistent.
   References to the memory and mappings associated with CPU_ADDR or
   DMA_ADDR past this call are illegal.  */

अटल व्योम alpha_pci_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
				    व्योम *cpu_addr, dma_addr_t dma_addr,
				    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_dev *pdev = alpha_gendev_to_pci(dev);
	pci_unmap_single(pdev, dma_addr, size, PCI_DMA_BIसूचीECTIONAL);
	मुक्त_pages((अचिन्हित दीर्घ)cpu_addr, get_order(size));

	DBGA2("pci_free_consistent: [%llx,%zx] from %ps\n",
	      dma_addr, size, __builtin_वापस_address(0));
पूर्ण

/* Classअगरy the elements of the scatterlist.  Write dma_address
   of each element with:
	0   : Followers all physically adjacent.
	1   : Followers all भवly adjacent.
	-1  : Not leader, physically adjacent to previous.
	-2  : Not leader, भवly adjacent to previous.
   Write dma_length of each leader with the combined lengths of
   the mergable followers.  */

#घोषणा SG_ENT_VIRT_ADDRESS(SG) (sg_virt((SG)))
#घोषणा SG_ENT_PHYS_ADDRESS(SG) __pa(SG_ENT_VIRT_ADDRESS(SG))

अटल व्योम
sg_classअगरy(काष्ठा device *dev, काष्ठा scatterlist *sg, काष्ठा scatterlist *end,
	    पूर्णांक virt_ok)
अणु
	अचिन्हित दीर्घ next_paddr;
	काष्ठा scatterlist *leader;
	दीर्घ leader_flag, leader_length;
	अचिन्हित पूर्णांक max_seg_size;

	leader = sg;
	leader_flag = 0;
	leader_length = leader->length;
	next_paddr = SG_ENT_PHYS_ADDRESS(leader) + leader_length;

	/* we will not marge sg without device. */
	max_seg_size = dev ? dma_get_max_seg_size(dev) : 0;
	क्रम (++sg; sg < end; ++sg) अणु
		अचिन्हित दीर्घ addr, len;
		addr = SG_ENT_PHYS_ADDRESS(sg);
		len = sg->length;

		अगर (leader_length + len > max_seg_size)
			जाओ new_segment;

		अगर (next_paddr == addr) अणु
			sg->dma_address = -1;
			leader_length += len;
		पूर्ण अन्यथा अगर (((next_paddr | addr) & ~PAGE_MASK) == 0 && virt_ok) अणु
			sg->dma_address = -2;
			leader_flag = 1;
			leader_length += len;
		पूर्ण अन्यथा अणु
new_segment:
			leader->dma_address = leader_flag;
			leader->dma_length = leader_length;
			leader = sg;
			leader_flag = 0;
			leader_length = len;
		पूर्ण

		next_paddr = addr + len;
	पूर्ण

	leader->dma_address = leader_flag;
	leader->dma_length = leader_length;
पूर्ण

/* Given a scatterlist leader, choose an allocation method and fill
   in the blanks.  */

अटल पूर्णांक
sg_fill(काष्ठा device *dev, काष्ठा scatterlist *leader, काष्ठा scatterlist *end,
	काष्ठा scatterlist *out, काष्ठा pci_iommu_arena *arena,
	dma_addr_t max_dma, पूर्णांक dac_allowed)
अणु
	अचिन्हित दीर्घ paddr = SG_ENT_PHYS_ADDRESS(leader);
	दीर्घ size = leader->dma_length;
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ *ptes;
	दीर्घ npages, dma_ofs, i;

#अगर !DEBUG_NOसूचीECT
	/* If everything is physically contiguous, and the addresses
	   fall पूर्णांकo the direct-map winकरोw, use it.  */
	अगर (leader->dma_address == 0
	    && paddr + size + __direct_map_base - 1 <= max_dma
	    && paddr + size <= __direct_map_size) अणु
		out->dma_address = paddr + __direct_map_base;
		out->dma_length = size;

		DBGA("    sg_fill: [%p,%lx] -> direct %llx\n",
		     __va(paddr), size, out->dma_address);

		वापस 0;
	पूर्ण
#पूर्ण_अगर

	/* If physically contiguous and DAC is available, use it.  */
	अगर (leader->dma_address == 0 && dac_allowed) अणु
		out->dma_address = paddr + alpha_mv.pci_dac_offset;
		out->dma_length = size;

		DBGA("    sg_fill: [%p,%lx] -> DAC %llx\n",
		     __va(paddr), size, out->dma_address);

		वापस 0;
	पूर्ण

	/* Otherwise, we'll use the iommu to make the pages भवly
	   contiguous.  */

	paddr &= ~PAGE_MASK;
	npages = iommu_num_pages(paddr, size, PAGE_SIZE);
	dma_ofs = iommu_arena_alloc(dev, arena, npages, 0);
	अगर (dma_ofs < 0) अणु
		/* If we attempted a direct map above but failed, die.  */
		अगर (leader->dma_address == 0)
			वापस -1;

		/* Otherwise, अवरोध up the reमुख्यing भवly contiguous
		   hunks पूर्णांकo inभागidual direct maps and retry.  */
		sg_classअगरy(dev, leader, end, 0);
		वापस sg_fill(dev, leader, end, out, arena, max_dma, dac_allowed);
	पूर्ण

	out->dma_address = arena->dma_base + dma_ofs*PAGE_SIZE + paddr;
	out->dma_length = size;

	DBGA("    sg_fill: [%p,%lx] -> sg %llx np %ld\n",
	     __va(paddr), size, out->dma_address, npages);

	/* All भवly contiguous.  We need to find the length of each
	   physically contiguous subsegment to fill in the ptes.  */
	ptes = &arena->ptes[dma_ofs];
	sg = leader;
	करो अणु
#अगर DEBUG_ALLOC > 0
		काष्ठा scatterlist *last_sg = sg;
#पूर्ण_अगर

		size = sg->length;
		paddr = SG_ENT_PHYS_ADDRESS(sg);

		जबतक (sg+1 < end && (पूर्णांक) sg[1].dma_address == -1) अणु
			size += sg[1].length;
			sg = sg_next(sg);
		पूर्ण

		npages = iommu_num_pages(paddr, size, PAGE_SIZE);

		paddr &= PAGE_MASK;
		क्रम (i = 0; i < npages; ++i, paddr += PAGE_SIZE)
			*ptes++ = mk_iommu_pte(paddr);

#अगर DEBUG_ALLOC > 0
		DBGA("    (%ld) [%p,%x] np %ld\n",
		     last_sg - leader, SG_ENT_VIRT_ADDRESS(last_sg),
		     last_sg->length, npages);
		जबतक (++last_sg <= sg) अणु
			DBGA("        (%ld) [%p,%x] cont\n",
			     last_sg - leader, SG_ENT_VIRT_ADDRESS(last_sg),
			     last_sg->length);
		पूर्ण
#पूर्ण_अगर
	पूर्ण जबतक (++sg < end && (पूर्णांक) sg->dma_address < 0);

	वापस 1;
पूर्ण

अटल पूर्णांक alpha_pci_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
			    पूर्णांक nents, क्रमागत dma_data_direction dir,
			    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_dev *pdev = alpha_gendev_to_pci(dev);
	काष्ठा scatterlist *start, *end, *out;
	काष्ठा pci_controller *hose;
	काष्ठा pci_iommu_arena *arena;
	dma_addr_t max_dma;
	पूर्णांक dac_allowed;

	BUG_ON(dir == PCI_DMA_NONE);

	dac_allowed = dev ? pci_dac_dma_supported(pdev, pdev->dma_mask) : 0;

	/* Fast path single entry scatterlists.  */
	अगर (nents == 1) अणु
		sg->dma_length = sg->length;
		sg->dma_address
		  = pci_map_single_1(pdev, SG_ENT_VIRT_ADDRESS(sg),
				     sg->length, dac_allowed);
		वापस sg->dma_address != DMA_MAPPING_ERROR;
	पूर्ण

	start = sg;
	end = sg + nents;

	/* First, prepare inक्रमmation about the entries.  */
	sg_classअगरy(dev, sg, end, alpha_mv.mv_pci_tbi != 0);

	/* Second, figure out where we're going to map things.  */
	अगर (alpha_mv.mv_pci_tbi) अणु
		hose = pdev ? pdev->sysdata : pci_isa_hose;
		max_dma = pdev ? pdev->dma_mask : ISA_DMA_MASK;
		arena = hose->sg_pci;
		अगर (!arena || arena->dma_base + arena->size - 1 > max_dma)
			arena = hose->sg_isa;
	पूर्ण अन्यथा अणु
		max_dma = -1;
		arena = शून्य;
		hose = शून्य;
	पूर्ण

	/* Third, iterate over the scatterlist leaders and allocate
	   dma space as needed.  */
	क्रम (out = sg; sg < end; ++sg) अणु
		अगर ((पूर्णांक) sg->dma_address < 0)
			जारी;
		अगर (sg_fill(dev, sg, end, out, arena, max_dma, dac_allowed) < 0)
			जाओ error;
		out++;
	पूर्ण

	/* Mark the end of the list क्रम pci_unmap_sg.  */
	अगर (out < end)
		out->dma_length = 0;

	अगर (out - start == 0)
		prपूर्णांकk(KERN_WARNING "pci_map_sg failed: no entries?\n");
	DBGA("pci_map_sg: %ld entries\n", out - start);

	वापस out - start;

 error:
	prपूर्णांकk(KERN_WARNING "pci_map_sg failed: "
	       "could not allocate dma page tables\n");

	/* Some allocation failed जबतक mapping the scatterlist
	   entries.  Unmap them now.  */
	अगर (out > start)
		pci_unmap_sg(pdev, start, out - start, dir);
	वापस 0;
पूर्ण

/* Unmap a set of streaming mode DMA translations.  Again, cpu पढ़ो
   rules concerning calls here are the same as क्रम pci_unmap_single()
   above.  */

अटल व्योम alpha_pci_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sg,
			       पूर्णांक nents, क्रमागत dma_data_direction dir,
			       अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_dev *pdev = alpha_gendev_to_pci(dev);
	अचिन्हित दीर्घ flags;
	काष्ठा pci_controller *hose;
	काष्ठा pci_iommu_arena *arena;
	काष्ठा scatterlist *end;
	dma_addr_t max_dma;
	dma_addr_t fbeg, fend;

	BUG_ON(dir == PCI_DMA_NONE);

	अगर (! alpha_mv.mv_pci_tbi)
		वापस;

	hose = pdev ? pdev->sysdata : pci_isa_hose;
	max_dma = pdev ? pdev->dma_mask : ISA_DMA_MASK;
	arena = hose->sg_pci;
	अगर (!arena || arena->dma_base + arena->size - 1 > max_dma)
		arena = hose->sg_isa;

	fbeg = -1, fend = 0;

	spin_lock_irqsave(&arena->lock, flags);

	क्रम (end = sg + nents; sg < end; ++sg) अणु
		dma_addr_t addr;
		माप_प्रकार size;
		दीर्घ npages, ofs;
		dma_addr_t tend;

		addr = sg->dma_address;
		size = sg->dma_length;
		अगर (!size)
			अवरोध;

		अगर (addr > 0xffffffff) अणु
			/* It's a DAC address -- nothing to करो.  */
			DBGA("    (%ld) DAC [%llx,%zx]\n",
			      sg - end + nents, addr, size);
			जारी;
		पूर्ण

		अगर (addr >= __direct_map_base
		    && addr < __direct_map_base + __direct_map_size) अणु
			/* Nothing to करो.  */
			DBGA("    (%ld) direct [%llx,%zx]\n",
			      sg - end + nents, addr, size);
			जारी;
		पूर्ण

		DBGA("    (%ld) sg [%llx,%zx]\n",
		     sg - end + nents, addr, size);

		npages = iommu_num_pages(addr, size, PAGE_SIZE);
		ofs = (addr - arena->dma_base) >> PAGE_SHIFT;
		iommu_arena_मुक्त(arena, ofs, npages);

		tend = addr + size - 1;
		अगर (fbeg > addr) fbeg = addr;
		अगर (fend < tend) fend = tend;
	पूर्ण

        /* If we're freeing ptes above the `next_entry' poपूर्णांकer (they
           may have snuck back पूर्णांकo the TLB since the last wrap flush),
           we need to flush the TLB beक्रमe पुनः_स्मृतिating the latter.  */
	अगर ((fend - arena->dma_base) >> PAGE_SHIFT >= arena->next_entry)
		alpha_mv.mv_pci_tbi(hose, fbeg, fend);

	spin_unlock_irqrestore(&arena->lock, flags);

	DBGA("pci_unmap_sg: %ld entries\n", nents - (end - sg));
पूर्ण

/* Return whether the given PCI device DMA address mask can be
   supported properly.  */

अटल पूर्णांक alpha_pci_supported(काष्ठा device *dev, u64 mask)
अणु
	काष्ठा pci_dev *pdev = alpha_gendev_to_pci(dev);
	काष्ठा pci_controller *hose;
	काष्ठा pci_iommu_arena *arena;

	/* If there exists a direct map, and the mask fits either
	   the entire direct mapped space or the total प्रणाली memory as
	   shअगरted by the map base */
	अगर (__direct_map_size != 0
	    && (__direct_map_base + __direct_map_size - 1 <= mask ||
		__direct_map_base + (max_low_pfn << PAGE_SHIFT) - 1 <= mask))
		वापस 1;

	/* Check that we have a scatter-gather arena that fits.  */
	hose = pdev ? pdev->sysdata : pci_isa_hose;
	arena = hose->sg_isa;
	अगर (arena && arena->dma_base + arena->size - 1 <= mask)
		वापस 1;
	arena = hose->sg_pci;
	अगर (arena && arena->dma_base + arena->size - 1 <= mask)
		वापस 1;

	/* As last resort try ZONE_DMA.  */
	अगर (!__direct_map_base && MAX_DMA_ADDRESS - IDENT_ADDR - 1 <= mask)
		वापस 1;

	वापस 0;
पूर्ण


/*
 * AGP GART extensions to the IOMMU
 */
पूर्णांक
iommu_reserve(काष्ठा pci_iommu_arena *arena, दीर्घ pg_count, दीर्घ align_mask) 
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *ptes;
	दीर्घ i, p;

	अगर (!arena) वापस -EINVAL;

	spin_lock_irqsave(&arena->lock, flags);

	/* Search क्रम N empty ptes.  */
	ptes = arena->ptes;
	p = iommu_arena_find_pages(शून्य, arena, pg_count, align_mask);
	अगर (p < 0) अणु
		spin_unlock_irqrestore(&arena->lock, flags);
		वापस -1;
	पूर्ण

	/* Success.  Mark them all reserved (ie not zero and invalid)
	   क्रम the iommu tlb that could load them from under us.
	   They will be filled in with valid bits by _bind() */
	क्रम (i = 0; i < pg_count; ++i)
		ptes[p+i] = IOMMU_RESERVED_PTE;

	arena->next_entry = p + pg_count;
	spin_unlock_irqrestore(&arena->lock, flags);

	वापस p;
पूर्ण

पूर्णांक 
iommu_release(काष्ठा pci_iommu_arena *arena, दीर्घ pg_start, दीर्घ pg_count)
अणु
	अचिन्हित दीर्घ *ptes;
	दीर्घ i;

	अगर (!arena) वापस -EINVAL;

	ptes = arena->ptes;

	/* Make sure they're all reserved first... */
	क्रम(i = pg_start; i < pg_start + pg_count; i++)
		अगर (ptes[i] != IOMMU_RESERVED_PTE)
			वापस -EBUSY;

	iommu_arena_मुक्त(arena, pg_start, pg_count);
	वापस 0;
पूर्ण

पूर्णांक
iommu_bind(काष्ठा pci_iommu_arena *arena, दीर्घ pg_start, दीर्घ pg_count, 
	   काष्ठा page **pages)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *ptes;
	दीर्घ i, j;

	अगर (!arena) वापस -EINVAL;
	
	spin_lock_irqsave(&arena->lock, flags);

	ptes = arena->ptes;

	क्रम(j = pg_start; j < pg_start + pg_count; j++) अणु
		अगर (ptes[j] != IOMMU_RESERVED_PTE) अणु
			spin_unlock_irqrestore(&arena->lock, flags);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
		
	क्रम(i = 0, j = pg_start; i < pg_count; i++, j++)
		ptes[j] = mk_iommu_pte(page_to_phys(pages[i]));

	spin_unlock_irqrestore(&arena->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक
iommu_unbind(काष्ठा pci_iommu_arena *arena, दीर्घ pg_start, दीर्घ pg_count)
अणु
	अचिन्हित दीर्घ *p;
	दीर्घ i;

	अगर (!arena) वापस -EINVAL;

	p = arena->ptes + pg_start;
	क्रम(i = 0; i < pg_count; i++)
		p[i] = IOMMU_RESERVED_PTE;

	वापस 0;
पूर्ण

स्थिर काष्ठा dma_map_ops alpha_pci_ops = अणु
	.alloc			= alpha_pci_alloc_coherent,
	.मुक्त			= alpha_pci_मुक्त_coherent,
	.map_page		= alpha_pci_map_page,
	.unmap_page		= alpha_pci_unmap_page,
	.map_sg			= alpha_pci_map_sg,
	.unmap_sg		= alpha_pci_unmap_sg,
	.dma_supported		= alpha_pci_supported,
	.mmap			= dma_common_mmap,
	.get_sgtable		= dma_common_get_sgtable,
	.alloc_pages		= dma_common_alloc_pages,
	.मुक्त_pages		= dma_common_मुक्त_pages,
पूर्ण;
EXPORT_SYMBOL(alpha_pci_ops);
