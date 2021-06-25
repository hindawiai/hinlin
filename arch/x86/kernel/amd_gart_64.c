<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dynamic DMA mapping support क्रम AMD Hammer.
 *
 * Use the पूर्णांकegrated AGP GART in the Hammer northbridge as an IOMMU क्रम PCI.
 * This allows to use PCI devices that only support 32bit addresses on प्रणालीs
 * with more than 4GB.
 *
 * See Documentation/core-api/dma-api-howto.rst क्रम the पूर्णांकerface specअगरication.
 *
 * Copyright 2002 Andi Kleen, SuSE Lअसल.
 */

#समावेश <linux/types.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/agp_backend.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/pci.h>
#समावेश <linux/topology.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/पन.स>
#समावेश <linux/gfp.h>
#समावेश <linux/atomic.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/gart.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/swiotlb.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/x86_init.h>
#समावेश <यंत्र/iommu_table.h>

अटल अचिन्हित दीर्घ iommu_bus_base;	/* GART remapping area (physical) */
अटल अचिन्हित दीर्घ iommu_size;	/* size of remapping area bytes */
अटल अचिन्हित दीर्घ iommu_pages;	/* .. and in pages */

अटल u32 *iommu_gatt_base;		/* Remapping table */

/*
 * If this is disabled the IOMMU will use an optimized flushing strategy
 * of only flushing when an mapping is reused. With it true the GART is
 * flushed क्रम every mapping. Problem is that करोing the lazy flush seems
 * to trigger bugs with some popular PCI cards, in particular 3ware (but
 * has been also also seen with Qlogic at least).
 */
अटल पूर्णांक iommu_fullflush = 1;

/* Allocation biपंचांगap क्रम the remapping area: */
अटल DEFINE_SPINLOCK(iommu_biपंचांगap_lock);
/* Guarded by iommu_biपंचांगap_lock: */
अटल अचिन्हित दीर्घ *iommu_gart_biपंचांगap;

अटल u32 gart_unmapped_entry;

#घोषणा GPTE_VALID    1
#घोषणा GPTE_COHERENT 2
#घोषणा GPTE_ENCODE(x) \
	(((x) & 0xfffff000) | (((x) >> 32) << 4) | GPTE_VALID | GPTE_COHERENT)
#घोषणा GPTE_DECODE(x) (((x) & 0xfffff000) | (((u64)(x) & 0xff0) << 28))

#अगर_घोषित CONFIG_AGP
#घोषणा AGPEXTERN बाह्य
#अन्यथा
#घोषणा AGPEXTERN
#पूर्ण_अगर

/* GART can only remap to physical addresses < 1TB */
#घोषणा GART_MAX_PHYS_ADDR	(1ULL << 40)

/* backकरोor पूर्णांकerface to AGP driver */
AGPEXTERN पूर्णांक agp_memory_reserved;
AGPEXTERN __u32 *agp_gatt_table;

अटल अचिन्हित दीर्घ next_bit;  /* रक्षित by iommu_biपंचांगap_lock */
अटल bool need_flush;		/* global flush state. set क्रम each gart wrap */

अटल अचिन्हित दीर्घ alloc_iommu(काष्ठा device *dev, पूर्णांक size,
				 अचिन्हित दीर्घ align_mask)
अणु
	अचिन्हित दीर्घ offset, flags;
	अचिन्हित दीर्घ boundary_size;
	अचिन्हित दीर्घ base_index;

	base_index = ALIGN(iommu_bus_base & dma_get_seg_boundary(dev),
			   PAGE_SIZE) >> PAGE_SHIFT;
	boundary_size = dma_get_seg_boundary_nr_pages(dev, PAGE_SHIFT);

	spin_lock_irqsave(&iommu_biपंचांगap_lock, flags);
	offset = iommu_area_alloc(iommu_gart_biपंचांगap, iommu_pages, next_bit,
				  size, base_index, boundary_size, align_mask);
	अगर (offset == -1) अणु
		need_flush = true;
		offset = iommu_area_alloc(iommu_gart_biपंचांगap, iommu_pages, 0,
					  size, base_index, boundary_size,
					  align_mask);
	पूर्ण
	अगर (offset != -1) अणु
		next_bit = offset+size;
		अगर (next_bit >= iommu_pages) अणु
			next_bit = 0;
			need_flush = true;
		पूर्ण
	पूर्ण
	अगर (iommu_fullflush)
		need_flush = true;
	spin_unlock_irqrestore(&iommu_biपंचांगap_lock, flags);

	वापस offset;
पूर्ण

अटल व्योम मुक्त_iommu(अचिन्हित दीर्घ offset, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iommu_biपंचांगap_lock, flags);
	biपंचांगap_clear(iommu_gart_biपंचांगap, offset, size);
	अगर (offset >= next_bit)
		next_bit = offset + size;
	spin_unlock_irqrestore(&iommu_biपंचांगap_lock, flags);
पूर्ण

/*
 * Use global flush state to aव्योम races with multiple flushers.
 */
अटल व्योम flush_gart(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&iommu_biपंचांगap_lock, flags);
	अगर (need_flush) अणु
		amd_flush_garts();
		need_flush = false;
	पूर्ण
	spin_unlock_irqrestore(&iommu_biपंचांगap_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_IOMMU_LEAK
/* Debugging aid क्रम drivers that करोn't मुक्त their IOMMU tables */
अटल व्योम dump_leak(व्योम)
अणु
	अटल पूर्णांक dump;

	अगर (dump)
		वापस;
	dump = 1;

	show_stack(शून्य, शून्य, KERN_ERR);
	debug_dma_dump_mappings(शून्य);
पूर्ण
#पूर्ण_अगर

अटल व्योम iommu_full(काष्ठा device *dev, माप_प्रकार size, पूर्णांक dir)
अणु
	/*
	 * Ran out of IOMMU space क्रम this operation. This is very bad.
	 * Unक्रमtunately the drivers cannot handle this operation properly.
	 * Return some non mapped prereserved space in the aperture and
	 * let the Northbridge deal with it. This will result in garbage
	 * in the IO operation. When the size exceeds the prereserved space
	 * memory corruption will occur or अक्रमom memory will be DMAed
	 * out. Hopefully no network devices use single mappings that big.
	 */

	dev_err(dev, "PCI-DMA: Out of IOMMU space for %lu bytes\n", size);
#अगर_घोषित CONFIG_IOMMU_LEAK
	dump_leak();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक
need_iommu(काष्ठा device *dev, अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	वापस क्रमce_iommu || !dma_capable(dev, addr, size, true);
पूर्ण

अटल अंतरभूत पूर्णांक
nonक्रमced_iommu(काष्ठा device *dev, अचिन्हित दीर्घ addr, माप_प्रकार size)
अणु
	वापस !dma_capable(dev, addr, size, true);
पूर्ण

/* Map a single continuous physical area पूर्णांकo the IOMMU.
 * Caller needs to check अगर the iommu is needed and flush.
 */
अटल dma_addr_t dma_map_area(काष्ठा device *dev, dma_addr_t phys_mem,
				माप_प्रकार size, पूर्णांक dir, अचिन्हित दीर्घ align_mask)
अणु
	अचिन्हित दीर्घ npages = iommu_num_pages(phys_mem, size, PAGE_SIZE);
	अचिन्हित दीर्घ iommu_page;
	पूर्णांक i;

	अगर (unlikely(phys_mem + size > GART_MAX_PHYS_ADDR))
		वापस DMA_MAPPING_ERROR;

	iommu_page = alloc_iommu(dev, npages, align_mask);
	अगर (iommu_page == -1) अणु
		अगर (!nonक्रमced_iommu(dev, phys_mem, size))
			वापस phys_mem;
		अगर (panic_on_overflow)
			panic("dma_map_area overflow %lu bytes\n", size);
		iommu_full(dev, size, dir);
		वापस DMA_MAPPING_ERROR;
	पूर्ण

	क्रम (i = 0; i < npages; i++) अणु
		iommu_gatt_base[iommu_page + i] = GPTE_ENCODE(phys_mem);
		phys_mem += PAGE_SIZE;
	पूर्ण
	वापस iommu_bus_base + iommu_page*PAGE_SIZE + (phys_mem & ~PAGE_MASK);
पूर्ण

/* Map a single area पूर्णांकo the IOMMU */
अटल dma_addr_t gart_map_page(काष्ठा device *dev, काष्ठा page *page,
				अचिन्हित दीर्घ offset, माप_प्रकार size,
				क्रमागत dma_data_direction dir,
				अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ bus;
	phys_addr_t paddr = page_to_phys(page) + offset;

	अगर (!need_iommu(dev, paddr, size))
		वापस paddr;

	bus = dma_map_area(dev, paddr, size, dir, 0);
	flush_gart();

	वापस bus;
पूर्ण

/*
 * Free a DMA mapping.
 */
अटल व्योम gart_unmap_page(काष्ठा device *dev, dma_addr_t dma_addr,
			    माप_प्रकार size, क्रमागत dma_data_direction dir,
			    अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ iommu_page;
	पूर्णांक npages;
	पूर्णांक i;

	अगर (WARN_ON_ONCE(dma_addr == DMA_MAPPING_ERROR))
		वापस;

	/*
	 * This driver will not always use a GART mapping, but might have
	 * created a direct mapping instead.  If that is the हाल there is
	 * nothing to unmap here.
	 */
	अगर (dma_addr < iommu_bus_base ||
	    dma_addr >= iommu_bus_base + iommu_size)
		वापस;

	iommu_page = (dma_addr - iommu_bus_base)>>PAGE_SHIFT;
	npages = iommu_num_pages(dma_addr, size, PAGE_SIZE);
	क्रम (i = 0; i < npages; i++) अणु
		iommu_gatt_base[iommu_page + i] = gart_unmapped_entry;
	पूर्ण
	मुक्त_iommu(iommu_page, npages);
पूर्ण

/*
 * Wrapper क्रम pci_unmap_single working with scatterlists.
 */
अटल व्योम gart_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
			  क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	क्रम_each_sg(sg, s, nents, i) अणु
		अगर (!s->dma_length || !s->length)
			अवरोध;
		gart_unmap_page(dev, s->dma_address, s->dma_length, dir, 0);
	पूर्ण
पूर्ण

/* Fallback क्रम dma_map_sg in हाल of overflow */
अटल पूर्णांक dma_map_sg_nonक्रमce(काष्ठा device *dev, काष्ठा scatterlist *sg,
			       पूर्णांक nents, पूर्णांक dir)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

#अगर_घोषित CONFIG_IOMMU_DEBUG
	pr_debug("dma_map_sg overflow\n");
#पूर्ण_अगर

	क्रम_each_sg(sg, s, nents, i) अणु
		अचिन्हित दीर्घ addr = sg_phys(s);

		अगर (nonक्रमced_iommu(dev, addr, s->length)) अणु
			addr = dma_map_area(dev, addr, s->length, dir, 0);
			अगर (addr == DMA_MAPPING_ERROR) अणु
				अगर (i > 0)
					gart_unmap_sg(dev, sg, i, dir, 0);
				nents = 0;
				sg[0].dma_length = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		s->dma_address = addr;
		s->dma_length = s->length;
	पूर्ण
	flush_gart();

	वापस nents;
पूर्ण

/* Map multiple scatterlist entries continuous पूर्णांकo the first. */
अटल पूर्णांक __dma_map_cont(काष्ठा device *dev, काष्ठा scatterlist *start,
			  पूर्णांक nelems, काष्ठा scatterlist *sout,
			  अचिन्हित दीर्घ pages)
अणु
	अचिन्हित दीर्घ iommu_start = alloc_iommu(dev, pages, 0);
	अचिन्हित दीर्घ iommu_page = iommu_start;
	काष्ठा scatterlist *s;
	पूर्णांक i;

	अगर (iommu_start == -1)
		वापस -1;

	क्रम_each_sg(start, s, nelems, i) अणु
		अचिन्हित दीर्घ pages, addr;
		अचिन्हित दीर्घ phys_addr = s->dma_address;

		BUG_ON(s != start && s->offset);
		अगर (s == start) अणु
			sout->dma_address = iommu_bus_base;
			sout->dma_address += iommu_page*PAGE_SIZE + s->offset;
			sout->dma_length = s->length;
		पूर्ण अन्यथा अणु
			sout->dma_length += s->length;
		पूर्ण

		addr = phys_addr;
		pages = iommu_num_pages(s->offset, s->length, PAGE_SIZE);
		जबतक (pages--) अणु
			iommu_gatt_base[iommu_page] = GPTE_ENCODE(addr);
			addr += PAGE_SIZE;
			iommu_page++;
		पूर्ण
	पूर्ण
	BUG_ON(iommu_page - iommu_start != pages);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
dma_map_cont(काष्ठा device *dev, काष्ठा scatterlist *start, पूर्णांक nelems,
	     काष्ठा scatterlist *sout, अचिन्हित दीर्घ pages, पूर्णांक need)
अणु
	अगर (!need) अणु
		BUG_ON(nelems != 1);
		sout->dma_address = start->dma_address;
		sout->dma_length = start->length;
		वापस 0;
	पूर्ण
	वापस __dma_map_cont(dev, start, nelems, sout, pages);
पूर्ण

/*
 * DMA map all entries in a scatterlist.
 * Merge chunks that have page aligned sizes पूर्णांकo a continuous mapping.
 */
अटल पूर्णांक gart_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		       क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s, *ps, *start_sg, *sgmap;
	पूर्णांक need = 0, nextneed, i, out, start;
	अचिन्हित दीर्घ pages = 0;
	अचिन्हित पूर्णांक seg_size;
	अचिन्हित पूर्णांक max_seg_size;

	अगर (nents == 0)
		वापस 0;

	out		= 0;
	start		= 0;
	start_sg	= sg;
	sgmap		= sg;
	seg_size	= 0;
	max_seg_size	= dma_get_max_seg_size(dev);
	ps		= शून्य; /* shut up gcc */

	क्रम_each_sg(sg, s, nents, i) अणु
		dma_addr_t addr = sg_phys(s);

		s->dma_address = addr;
		BUG_ON(s->length == 0);

		nextneed = need_iommu(dev, addr, s->length);

		/* Handle the previous not yet processed entries */
		अगर (i > start) अणु
			/*
			 * Can only merge when the last chunk ends on a
			 * page boundary and the new one करोesn't have an
			 * offset.
			 */
			अगर (!iommu_merge || !nextneed || !need || s->offset ||
			    (s->length + seg_size > max_seg_size) ||
			    (ps->offset + ps->length) % PAGE_SIZE) अणु
				अगर (dma_map_cont(dev, start_sg, i - start,
						 sgmap, pages, need) < 0)
					जाओ error;
				out++;

				seg_size	= 0;
				sgmap		= sg_next(sgmap);
				pages		= 0;
				start		= i;
				start_sg	= s;
			पूर्ण
		पूर्ण

		seg_size += s->length;
		need = nextneed;
		pages += iommu_num_pages(s->offset, s->length, PAGE_SIZE);
		ps = s;
	पूर्ण
	अगर (dma_map_cont(dev, start_sg, i - start, sgmap, pages, need) < 0)
		जाओ error;
	out++;
	flush_gart();
	अगर (out < nents) अणु
		sgmap = sg_next(sgmap);
		sgmap->dma_length = 0;
	पूर्ण
	वापस out;

error:
	flush_gart();
	gart_unmap_sg(dev, sg, out, dir, 0);

	/* When it was क्रमced or merged try again in a dumb way */
	अगर (क्रमce_iommu || iommu_merge) अणु
		out = dma_map_sg_nonक्रमce(dev, sg, nents, dir);
		अगर (out > 0)
			वापस out;
	पूर्ण
	अगर (panic_on_overflow)
		panic("dma_map_sg: overflow on %lu pages\n", pages);

	iommu_full(dev, pages << PAGE_SHIFT, dir);
	क्रम_each_sg(sg, s, nents, i)
		s->dma_address = DMA_MAPPING_ERROR;
	वापस 0;
पूर्ण

/* allocate and map a coherent mapping */
अटल व्योम *
gart_alloc_coherent(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_addr,
		    gfp_t flag, अचिन्हित दीर्घ attrs)
अणु
	व्योम *vaddr;

	vaddr = dma_direct_alloc(dev, size, dma_addr, flag, attrs);
	अगर (!vaddr ||
	    !क्रमce_iommu || dev->coherent_dma_mask <= DMA_BIT_MASK(24))
		वापस vaddr;

	*dma_addr = dma_map_area(dev, virt_to_phys(vaddr), size,
			DMA_BIसूचीECTIONAL, (1UL << get_order(size)) - 1);
	flush_gart();
	अगर (unlikely(*dma_addr == DMA_MAPPING_ERROR))
		जाओ out_मुक्त;
	वापस vaddr;
out_मुक्त:
	dma_direct_मुक्त(dev, size, vaddr, *dma_addr, attrs);
	वापस शून्य;
पूर्ण

/* मुक्त a coherent mapping */
अटल व्योम
gart_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
		   dma_addr_t dma_addr, अचिन्हित दीर्घ attrs)
अणु
	gart_unmap_page(dev, dma_addr, size, DMA_BIसूचीECTIONAL, 0);
	dma_direct_मुक्त(dev, size, vaddr, dma_addr, attrs);
पूर्ण

अटल पूर्णांक no_agp;

अटल __init अचिन्हित दीर्घ check_iommu_size(अचिन्हित दीर्घ aper, u64 aper_size)
अणु
	अचिन्हित दीर्घ a;

	अगर (!iommu_size) अणु
		iommu_size = aper_size;
		अगर (!no_agp)
			iommu_size /= 2;
	पूर्ण

	a = aper + iommu_size;
	iommu_size -= round_up(a, PMD_PAGE_SIZE) - a;

	अगर (iommu_size < 64*1024*1024) अणु
		pr_warn("PCI-DMA: Warning: Small IOMMU %luMB."
			" Consider increasing the AGP aperture in BIOS\n",
			iommu_size >> 20);
	पूर्ण

	वापस iommu_size;
पूर्ण

अटल __init अचिन्हित पढ़ो_aperture(काष्ठा pci_dev *dev, u32 *size)
अणु
	अचिन्हित aper_size = 0, aper_base_32, aper_order;
	u64 aper_base;

	pci_पढ़ो_config_dword(dev, AMD64_GARTAPERTUREBASE, &aper_base_32);
	pci_पढ़ो_config_dword(dev, AMD64_GARTAPERTURECTL, &aper_order);
	aper_order = (aper_order >> 1) & 7;

	aper_base = aper_base_32 & 0x7fff;
	aper_base <<= 25;

	aper_size = (32 * 1024 * 1024) << aper_order;
	अगर (aper_base + aper_size > 0x100000000UL || !aper_size)
		aper_base = 0;

	*size = aper_size;
	वापस aper_base;
पूर्ण

अटल व्योम enable_gart_translations(व्योम)
अणु
	पूर्णांक i;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस;

	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		काष्ठा pci_dev *dev = node_to_amd_nb(i)->misc;

		enable_gart_translation(dev, __pa(agp_gatt_table));
	पूर्ण

	/* Flush the GART-TLB to हटाओ stale entries */
	amd_flush_garts();
पूर्ण

/*
 * If fix_up_north_bridges is set, the north bridges have to be fixed up on
 * resume in the same way as they are handled in gart_iommu_hole_init().
 */
अटल bool fix_up_north_bridges;
अटल u32 aperture_order;
अटल u32 aperture_alloc;

व्योम set_up_gart_resume(u32 aper_order, u32 aper_alloc)
अणु
	fix_up_north_bridges = true;
	aperture_order = aper_order;
	aperture_alloc = aper_alloc;
पूर्ण

अटल व्योम gart_fixup_northbridges(व्योम)
अणु
	पूर्णांक i;

	अगर (!fix_up_north_bridges)
		वापस;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस;

	pr_info("PCI-DMA: Restoring GART aperture settings\n");

	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		काष्ठा pci_dev *dev = node_to_amd_nb(i)->misc;

		/*
		 * Don't enable translations just yet.  That is the next
		 * step.  Restore the pre-suspend aperture settings.
		 */
		gart_set_size_and_enable(dev, aperture_order);
		pci_ग_लिखो_config_dword(dev, AMD64_GARTAPERTUREBASE, aperture_alloc >> 25);
	पूर्ण
पूर्ण

अटल व्योम gart_resume(व्योम)
अणु
	pr_info("PCI-DMA: Resuming GART IOMMU\n");

	gart_fixup_northbridges();

	enable_gart_translations();
पूर्ण

अटल काष्ठा syscore_ops gart_syscore_ops = अणु
	.resume		= gart_resume,

पूर्ण;

/*
 * Private Northbridge GATT initialization in हाल we cannot use the
 * AGP driver क्रम some reason.
 */
अटल __init पूर्णांक init_amd_gatt(काष्ठा agp_kern_info *info)
अणु
	अचिन्हित aper_size, gatt_size, new_aper_size;
	अचिन्हित aper_base, new_aper_base;
	काष्ठा pci_dev *dev;
	व्योम *gatt;
	पूर्णांक i;

	pr_info("PCI-DMA: Disabling AGP.\n");

	aper_size = aper_base = info->aper_size = 0;
	dev = शून्य;
	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		dev = node_to_amd_nb(i)->misc;
		new_aper_base = पढ़ो_aperture(dev, &new_aper_size);
		अगर (!new_aper_base)
			जाओ nommu;

		अगर (!aper_base) अणु
			aper_size = new_aper_size;
			aper_base = new_aper_base;
		पूर्ण
		अगर (aper_size != new_aper_size || aper_base != new_aper_base)
			जाओ nommu;
	पूर्ण
	अगर (!aper_base)
		जाओ nommu;

	info->aper_base = aper_base;
	info->aper_size = aper_size >> 20;

	gatt_size = (aper_size >> PAGE_SHIFT) * माप(u32);
	gatt = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
					get_order(gatt_size));
	अगर (!gatt)
		panic("Cannot allocate GATT table");
	अगर (set_memory_uc((अचिन्हित दीर्घ)gatt, gatt_size >> PAGE_SHIFT))
		panic("Could not set GART PTEs to uncacheable pages");

	agp_gatt_table = gatt;

	रेजिस्टर_syscore_ops(&gart_syscore_ops);

	flush_gart();

	pr_info("PCI-DMA: aperture base @ %x size %u KB\n",
	       aper_base, aper_size>>10);

	वापस 0;

 nommu:
	/* Should not happen anymore */
	pr_warn("PCI-DMA: More than 4GB of RAM and no IOMMU - falling back to iommu=soft.\n");
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा dma_map_ops gart_dma_ops = अणु
	.map_sg				= gart_map_sg,
	.unmap_sg			= gart_unmap_sg,
	.map_page			= gart_map_page,
	.unmap_page			= gart_unmap_page,
	.alloc				= gart_alloc_coherent,
	.मुक्त				= gart_मुक्त_coherent,
	.mmap				= dma_common_mmap,
	.get_sgtable			= dma_common_get_sgtable,
	.dma_supported			= dma_direct_supported,
	.get_required_mask		= dma_direct_get_required_mask,
	.alloc_pages			= dma_direct_alloc_pages,
	.मुक्त_pages			= dma_direct_मुक्त_pages,
पूर्ण;

अटल व्योम gart_iommu_shutकरोwn(व्योम)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक i;

	/* करोn't shutकरोwn it अगर there is AGP installed */
	अगर (!no_agp)
		वापस;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस;

	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		u32 ctl;

		dev = node_to_amd_nb(i)->misc;
		pci_पढ़ो_config_dword(dev, AMD64_GARTAPERTURECTL, &ctl);

		ctl &= ~GARTEN;

		pci_ग_लिखो_config_dword(dev, AMD64_GARTAPERTURECTL, ctl);
	पूर्ण
पूर्ण

पूर्णांक __init gart_iommu_init(व्योम)
अणु
	काष्ठा agp_kern_info info;
	अचिन्हित दीर्घ iommu_start;
	अचिन्हित दीर्घ aper_base, aper_size;
	अचिन्हित दीर्घ start_pfn, end_pfn;
	अचिन्हित दीर्घ scratch;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस 0;

#अगर_अघोषित CONFIG_AGP_AMD64
	no_agp = 1;
#अन्यथा
	/* Makefile माला_दो PCI initialization via subsys_initcall first. */
	/* Add other AMD AGP bridge drivers here */
	no_agp = no_agp ||
		(agp_amd64_init() < 0) ||
		(agp_copy_info(agp_bridge, &info) < 0);
#पूर्ण_अगर

	अगर (no_iommu ||
	    (!क्रमce_iommu && max_pfn <= MAX_DMA32_PFN) ||
	    !gart_iommu_aperture ||
	    (no_agp && init_amd_gatt(&info) < 0)) अणु
		अगर (max_pfn > MAX_DMA32_PFN) अणु
			pr_warn("More than 4GB of memory but GART IOMMU not available.\n");
			pr_warn("falling back to iommu=soft.\n");
		पूर्ण
		वापस 0;
	पूर्ण

	/* need to map that range */
	aper_size	= info.aper_size << 20;
	aper_base	= info.aper_base;
	end_pfn		= (aper_base>>PAGE_SHIFT) + (aper_size>>PAGE_SHIFT);

	start_pfn = PFN_DOWN(aper_base);
	अगर (!pfn_range_is_mapped(start_pfn, end_pfn))
		init_memory_mapping(start_pfn<<PAGE_SHIFT, end_pfn<<PAGE_SHIFT,
				    PAGE_KERNEL);

	pr_info("PCI-DMA: using GART IOMMU.\n");
	iommu_size = check_iommu_size(info.aper_base, aper_size);
	iommu_pages = iommu_size >> PAGE_SHIFT;

	iommu_gart_biपंचांगap = (व्योम *) __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO,
						      get_order(iommu_pages/8));
	अगर (!iommu_gart_biपंचांगap)
		panic("Cannot allocate iommu bitmap\n");

	pr_info("PCI-DMA: Reserving %luMB of IOMMU area in the AGP aperture\n",
	       iommu_size >> 20);

	agp_memory_reserved	= iommu_size;
	iommu_start		= aper_size - iommu_size;
	iommu_bus_base		= info.aper_base + iommu_start;
	iommu_gatt_base		= agp_gatt_table + (iommu_start>>PAGE_SHIFT);

	/*
	 * Unmap the IOMMU part of the GART. The alias of the page is
	 * always mapped with cache enabled and there is no full cache
	 * coherency across the GART remapping. The unmapping aव्योमs
	 * स्वतःmatic prefetches from the CPU allocating cache lines in
	 * there. All CPU accesses are करोne via the direct mapping to
	 * the backing memory. The GART address is only used by PCI
	 * devices.
	 */
	set_memory_np((अचिन्हित दीर्घ)__va(iommu_bus_base),
				iommu_size >> PAGE_SHIFT);
	/*
	 * Tricky. The GART table remaps the physical memory range,
	 * so the CPU wont notice potential aliases and अगर the memory
	 * is remapped to UC later on, we might surprise the PCI devices
	 * with a stray ग_लिखोout of a cacheline. So play it sure and
	 * करो an explicit, full-scale wbinvd() _after_ having marked all
	 * the pages as Not-Present:
	 */
	wbinvd();

	/*
	 * Now all caches are flushed and we can safely enable
	 * GART hardware.  Doing it early leaves the possibility
	 * of stale cache entries that can lead to GART PTE
	 * errors.
	 */
	enable_gart_translations();

	/*
	 * Try to workaround a bug (thanks to BenH):
	 * Set unmapped entries to a scratch page instead of 0.
	 * Any prefetches that hit unmapped entries won't get an bus पात
	 * then. (P2P bridge may be prefetching on DMA पढ़ोs).
	 */
	scratch = get_zeroed_page(GFP_KERNEL);
	अगर (!scratch)
		panic("Cannot allocate iommu scratch page");
	gart_unmapped_entry = GPTE_ENCODE(__pa(scratch));

	flush_gart();
	dma_ops = &gart_dma_ops;
	x86_platक्रमm.iommu_shutकरोwn = gart_iommu_shutकरोwn;
	swiotlb = 0;

	वापस 0;
पूर्ण

व्योम __init gart_parse_options(अक्षर *p)
अणु
	पूर्णांक arg;

	अगर (है_अंक(*p) && get_option(&p, &arg))
		iommu_size = arg;
	अगर (!म_भेदन(p, "fullflush", 9))
		iommu_fullflush = 1;
	अगर (!म_भेदन(p, "nofullflush", 11))
		iommu_fullflush = 0;
	अगर (!म_भेदन(p, "noagp", 5))
		no_agp = 1;
	अगर (!म_भेदन(p, "noaperture", 10))
		fix_aperture = 0;
	/* duplicated from pci-dma.c */
	अगर (!म_भेदन(p, "force", 5))
		gart_iommu_aperture_allowed = 1;
	अगर (!म_भेदन(p, "allowed", 7))
		gart_iommu_aperture_allowed = 1;
	अगर (!म_भेदन(p, "memaper", 7)) अणु
		fallback_aper_क्रमce = 1;
		p += 7;
		अगर (*p == '=') अणु
			++p;
			अगर (get_option(&p, &arg))
				fallback_aper_order = arg;
		पूर्ण
	पूर्ण
पूर्ण
IOMMU_INIT_POST(gart_iommu_hole_init);
