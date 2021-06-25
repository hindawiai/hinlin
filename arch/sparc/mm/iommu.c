<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * iommu.c:  IOMMU specअगरic routines क्रम memory management.
 *
 * Copyright (C) 1995 David S. Miller  (davem@caip.rutgers.edu)
 * Copyright (C) 1995,2002 Pete Zaitcev     (zaitcev@yahoo.com)
 * Copyright (C) 1996 Eddie C. Dost    (ecd@skynet.be)
 * Copyright (C) 1997,1998 Jakub Jelinek    (jj@sunsite.mff.cuni.cz)
 */
 
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/mxcc.h>
#समावेश <यंत्र/mbus.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/bitext.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/dma.h>

#समावेश "mm_32.h"

/*
 * This can be sized dynamically, but we will करो this
 * only when we have a guidance about actual I/O pressures.
 */
#घोषणा IOMMU_RNGE	IOMMU_RNGE_256MB
#घोषणा IOMMU_START	0xF0000000
#घोषणा IOMMU_WINSIZE	(256*1024*1024U)
#घोषणा IOMMU_NPTES	(IOMMU_WINSIZE/PAGE_SIZE)	/* 64K PTEs, 256KB */
#घोषणा IOMMU_ORDER	6				/* 4096 * (1<<6) */

अटल पूर्णांक viking_flush;
/* viking.S */
बाह्य व्योम viking_flush_page(अचिन्हित दीर्घ page);
बाह्य व्योम viking_mxcc_flush_page(अचिन्हित दीर्घ page);

/*
 * Values precomputed according to CPU type.
 */
अटल अचिन्हित पूर्णांक ioperm_noc;		/* Consistent mapping iopte flags */
अटल pgprot_t dvma_prot;		/* Consistent mapping pte flags */

#घोषणा IOPERM        (IOPTE_CACHE | IOPTE_WRITE | IOPTE_VALID)
#घोषणा MKIOPTE(pfn, perm) (((((pfn)<<8) & IOPTE_PAGE) | (perm)) & ~IOPTE_WAZ)

अटल स्थिर काष्ठा dma_map_ops sbus_iommu_dma_gflush_ops;
अटल स्थिर काष्ठा dma_map_ops sbus_iommu_dma_pflush_ops;

अटल व्योम __init sbus_iommu_init(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा iommu_काष्ठा *iommu;
	अचिन्हित पूर्णांक impl, vers;
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित दीर्घ control;
	अचिन्हित दीर्घ base;
	अचिन्हित दीर्घ पंचांगp;

	iommu = kदो_स्मृति(माप(काष्ठा iommu_काष्ठा), GFP_KERNEL);
	अगर (!iommu) अणु
		prom_म_लिखो("Unable to allocate iommu structure\n");
		prom_halt();
	पूर्ण

	iommu->regs = of_ioremap(&op->resource[0], 0, PAGE_SIZE * 3,
				 "iommu_regs");
	अगर (!iommu->regs) अणु
		prom_म_लिखो("Cannot map IOMMU registers\n");
		prom_halt();
	पूर्ण

	control = sbus_पढ़ोl(&iommu->regs->control);
	impl = (control & IOMMU_CTRL_IMPL) >> 28;
	vers = (control & IOMMU_CTRL_VERS) >> 24;
	control &= ~(IOMMU_CTRL_RNGE);
	control |= (IOMMU_RNGE_256MB | IOMMU_CTRL_ENAB);
	sbus_ग_लिखोl(control, &iommu->regs->control);

	iommu_invalidate(iommu->regs);
	iommu->start = IOMMU_START;
	iommu->end = 0xffffffff;

	/* Allocate IOMMU page table */
	/* Stupid alignment स्थिरraपूर्णांकs give me a headache. 
	   We need 256K or 512K or 1M or 2M area aligned to
           its size and current gfp will क्रमtunately give
           it to us. */
        पंचांगp = __get_मुक्त_pages(GFP_KERNEL, IOMMU_ORDER);
	अगर (!पंचांगp) अणु
		prom_म_लिखो("Unable to allocate iommu table [0x%lx]\n",
			    IOMMU_NPTES * माप(iopte_t));
		prom_halt();
	पूर्ण
	iommu->page_table = (iopte_t *)पंचांगp;

	/* Initialize new table. */
	स_रखो(iommu->page_table, 0, IOMMU_NPTES*माप(iopte_t));
	flush_cache_all();
	flush_tlb_all();

	base = __pa((अचिन्हित दीर्घ)iommu->page_table) >> 4;
	sbus_ग_लिखोl(base, &iommu->regs->base);
	iommu_invalidate(iommu->regs);

	biपंचांगap = kदो_स्मृति(IOMMU_NPTES>>3, GFP_KERNEL);
	अगर (!biपंचांगap) अणु
		prom_म_लिखो("Unable to allocate iommu bitmap [%d]\n",
			    (पूर्णांक)(IOMMU_NPTES>>3));
		prom_halt();
	पूर्ण
	bit_map_init(&iommu->usemap, biपंचांगap, IOMMU_NPTES);
	/* To be coherent on HyperSparc, the page color of DVMA
	 * and physical addresses must match.
	 */
	अगर (srmmu_modtype == HyperSparc)
		iommu->usemap.num_colors = vac_cache_size >> PAGE_SHIFT;
	अन्यथा
		iommu->usemap.num_colors = 1;

	prपूर्णांकk(KERN_INFO "IOMMU: impl %d vers %d table 0x%p[%d B] map [%d b]\n",
	       impl, vers, iommu->page_table,
	       (पूर्णांक)(IOMMU_NPTES*माप(iopte_t)), (पूर्णांक)IOMMU_NPTES);

	op->dev.archdata.iommu = iommu;

	अगर (flush_page_क्रम_dma_global)
		op->dev.dma_ops = &sbus_iommu_dma_gflush_ops;
	 अन्यथा
		op->dev.dma_ops = &sbus_iommu_dma_pflush_ops;
पूर्ण

अटल पूर्णांक __init iommu_init(व्योम)
अणु
	काष्ठा device_node *dp;

	क्रम_each_node_by_name(dp, "iommu") अणु
		काष्ठा platक्रमm_device *op = of_find_device_by_node(dp);

		sbus_iommu_init(op);
		of_propagate_archdata(op);
	पूर्ण

	वापस 0;
पूर्ण

subsys_initcall(iommu_init);

/* Flush the iotlb entries to ram. */
/* This could be better अगर we didn't have to flush whole pages. */
अटल व्योम iommu_flush_iotlb(iopte_t *iopte, अचिन्हित पूर्णांक niopte)
अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;

	start = (अचिन्हित दीर्घ)iopte;
	end = PAGE_ALIGN(start + niopte*माप(iopte_t));
	start &= PAGE_MASK;
	अगर (viking_mxcc_present) अणु
		जबतक(start < end) अणु
			viking_mxcc_flush_page(start);
			start += PAGE_SIZE;
		पूर्ण
	पूर्ण अन्यथा अगर (viking_flush) अणु
		जबतक(start < end) अणु
			viking_flush_page(start);
			start += PAGE_SIZE;
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक(start < end) अणु
			__flush_page_to_ram(start);
			start += PAGE_SIZE;
		पूर्ण
	पूर्ण
पूर्ण

अटल dma_addr_t __sbus_iommu_map_page(काष्ठा device *dev, काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार len, bool per_page_flush)
अणु
	काष्ठा iommu_काष्ठा *iommu = dev->archdata.iommu;
	phys_addr_t paddr = page_to_phys(page) + offset;
	अचिन्हित दीर्घ off = paddr & ~PAGE_MASK;
	अचिन्हित दीर्घ npages = (off + len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	अचिन्हित दीर्घ pfn = __phys_to_pfn(paddr);
	अचिन्हित पूर्णांक busa, busa0;
	iopte_t *iopte, *iopte0;
	पूर्णांक ioptex, i;

	/* XXX So what is maxphys क्रम us and how करो drivers know it? */
	अगर (!len || len > 256 * 1024)
		वापस DMA_MAPPING_ERROR;

	/*
	 * We expect unmapped highmem pages to be not in the cache.
	 * XXX Is this a good assumption?
	 * XXX What अगर someone अन्यथा unmaps it here and races us?
	 */
	अगर (per_page_flush && !PageHighMem(page)) अणु
		अचिन्हित दीर्घ vaddr, p;

		vaddr = (अचिन्हित दीर्घ)page_address(page) + offset;
		क्रम (p = vaddr & PAGE_MASK; p < vaddr + len; p += PAGE_SIZE)
			flush_page_क्रम_dma(p);
	पूर्ण

	/* page color = pfn of page */
	ioptex = bit_map_string_get(&iommu->usemap, npages, pfn);
	अगर (ioptex < 0)
		panic("iommu out");
	busa0 = iommu->start + (ioptex << PAGE_SHIFT);
	iopte0 = &iommu->page_table[ioptex];

	busa = busa0;
	iopte = iopte0;
	क्रम (i = 0; i < npages; i++) अणु
		iopte_val(*iopte) = MKIOPTE(pfn, IOPERM);
		iommu_invalidate_page(iommu->regs, busa);
		busa += PAGE_SIZE;
		iopte++;
		pfn++;
	पूर्ण

	iommu_flush_iotlb(iopte0, npages);
	वापस busa0 + off;
पूर्ण

अटल dma_addr_t sbus_iommu_map_page_gflush(काष्ठा device *dev,
		काष्ठा page *page, अचिन्हित दीर्घ offset, माप_प्रकार len,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	flush_page_क्रम_dma(0);
	वापस __sbus_iommu_map_page(dev, page, offset, len, false);
पूर्ण

अटल dma_addr_t sbus_iommu_map_page_pflush(काष्ठा device *dev,
		काष्ठा page *page, अचिन्हित दीर्घ offset, माप_प्रकार len,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस __sbus_iommu_map_page(dev, page, offset, len, true);
पूर्ण

अटल पूर्णांक __sbus_iommu_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs,
		bool per_page_flush)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक j;

	क्रम_each_sg(sgl, sg, nents, j) अणु
		sg->dma_address =__sbus_iommu_map_page(dev, sg_page(sg),
				sg->offset, sg->length, per_page_flush);
		अगर (sg->dma_address == DMA_MAPPING_ERROR)
			वापस 0;
		sg->dma_length = sg->length;
	पूर्ण

	वापस nents;
पूर्ण

अटल पूर्णांक sbus_iommu_map_sg_gflush(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	flush_page_क्रम_dma(0);
	वापस __sbus_iommu_map_sg(dev, sgl, nents, dir, attrs, false);
पूर्ण

अटल पूर्णांक sbus_iommu_map_sg_pflush(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस __sbus_iommu_map_sg(dev, sgl, nents, dir, attrs, true);
पूर्ण

अटल व्योम sbus_iommu_unmap_page(काष्ठा device *dev, dma_addr_t dma_addr,
		माप_प्रकार len, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu_काष्ठा *iommu = dev->archdata.iommu;
	अचिन्हित पूर्णांक busa = dma_addr & PAGE_MASK;
	अचिन्हित दीर्घ off = dma_addr & ~PAGE_MASK;
	अचिन्हित पूर्णांक npages = (off + len + PAGE_SIZE-1) >> PAGE_SHIFT;
	अचिन्हित पूर्णांक ioptex = (busa - iommu->start) >> PAGE_SHIFT;
	अचिन्हित पूर्णांक i;

	BUG_ON(busa < iommu->start);
	क्रम (i = 0; i < npages; i++) अणु
		iopte_val(iommu->page_table[ioptex + i]) = 0;
		iommu_invalidate_page(iommu->regs, busa);
		busa += PAGE_SIZE;
	पूर्ण
	bit_map_clear(&iommu->usemap, ioptex, npages);
पूर्ण

अटल व्योम sbus_iommu_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sg(sgl, sg, nents, i) अणु
		sbus_iommu_unmap_page(dev, sg->dma_address, sg->length, dir,
				attrs);
		sg->dma_address = 0x21212121;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SBUS
अटल व्योम *sbus_iommu_alloc(काष्ठा device *dev, माप_प्रकार len,
		dma_addr_t *dma_handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu_काष्ठा *iommu = dev->archdata.iommu;
	अचिन्हित दीर्घ va, addr, page, end, ret;
	iopte_t *iopte = iommu->page_table;
	iopte_t *first;
	पूर्णांक ioptex;

	/* XXX So what is maxphys क्रम us and how करो drivers know it? */
	अगर (!len || len > 256 * 1024)
		वापस शून्य;

	len = PAGE_ALIGN(len);
	va = __get_मुक्त_pages(gfp | __GFP_ZERO, get_order(len));
	अगर (va == 0)
		वापस शून्य;

	addr = ret = sparc_dma_alloc_resource(dev, len);
	अगर (!addr)
		जाओ out_मुक्त_pages;

	BUG_ON((va & ~PAGE_MASK) != 0);
	BUG_ON((addr & ~PAGE_MASK) != 0);
	BUG_ON((len & ~PAGE_MASK) != 0);

	/* page color = physical address */
	ioptex = bit_map_string_get(&iommu->usemap, len >> PAGE_SHIFT,
		addr >> PAGE_SHIFT);
	अगर (ioptex < 0)
		panic("iommu out");

	iopte += ioptex;
	first = iopte;
	end = addr + len;
	जबतक(addr < end) अणु
		page = va;
		अणु
			pmd_t *pmdp;
			pte_t *ptep;

			अगर (viking_mxcc_present)
				viking_mxcc_flush_page(page);
			अन्यथा अगर (viking_flush)
				viking_flush_page(page);
			अन्यथा
				__flush_page_to_ram(page);

			pmdp = pmd_off_k(addr);
			ptep = pte_offset_map(pmdp, addr);

			set_pte(ptep, mk_pte(virt_to_page(page), dvma_prot));
		पूर्ण
		iopte_val(*iopte++) =
		    MKIOPTE(page_to_pfn(virt_to_page(page)), ioperm_noc);
		addr += PAGE_SIZE;
		va += PAGE_SIZE;
	पूर्ण
	/* P3: why करो we need this?
	 *
	 * DAVEM: Because there are several aspects, none of which
	 *        are handled by a single पूर्णांकerface.  Some cpus are
	 *        completely not I/O DMA coherent, and some have
	 *        भवly indexed caches.  The driver DMA flushing
	 *        methods handle the क्रमmer हाल, but here during
	 *        IOMMU page table modअगरications, and usage of non-cacheable
	 *        cpu mappings of pages potentially in the cpu caches, we have
	 *        to handle the latter हाल as well.
	 */
	flush_cache_all();
	iommu_flush_iotlb(first, len >> PAGE_SHIFT);
	flush_tlb_all();
	iommu_invalidate(iommu->regs);

	*dma_handle = iommu->start + (ioptex << PAGE_SHIFT);
	वापस (व्योम *)ret;

out_मुक्त_pages:
	मुक्त_pages(va, get_order(len));
	वापस शून्य;
पूर्ण

अटल व्योम sbus_iommu_मुक्त(काष्ठा device *dev, माप_प्रकार len, व्योम *cpu_addr,
			       dma_addr_t busa, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu_काष्ठा *iommu = dev->archdata.iommu;
	iopte_t *iopte = iommu->page_table;
	काष्ठा page *page = virt_to_page(cpu_addr);
	पूर्णांक ioptex = (busa - iommu->start) >> PAGE_SHIFT;
	अचिन्हित दीर्घ end;

	अगर (!sparc_dma_मुक्त_resource(cpu_addr, len))
		वापस;

	BUG_ON((busa & ~PAGE_MASK) != 0);
	BUG_ON((len & ~PAGE_MASK) != 0);

	iopte += ioptex;
	end = busa + len;
	जबतक (busa < end) अणु
		iopte_val(*iopte++) = 0;
		busa += PAGE_SIZE;
	पूर्ण
	flush_tlb_all();
	iommu_invalidate(iommu->regs);
	bit_map_clear(&iommu->usemap, ioptex, len >> PAGE_SHIFT);

	__मुक्त_pages(page, get_order(len));
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dma_map_ops sbus_iommu_dma_gflush_ops = अणु
#अगर_घोषित CONFIG_SBUS
	.alloc			= sbus_iommu_alloc,
	.मुक्त			= sbus_iommu_मुक्त,
#पूर्ण_अगर
	.map_page		= sbus_iommu_map_page_gflush,
	.unmap_page		= sbus_iommu_unmap_page,
	.map_sg			= sbus_iommu_map_sg_gflush,
	.unmap_sg		= sbus_iommu_unmap_sg,
पूर्ण;

अटल स्थिर काष्ठा dma_map_ops sbus_iommu_dma_pflush_ops = अणु
#अगर_घोषित CONFIG_SBUS
	.alloc			= sbus_iommu_alloc,
	.मुक्त			= sbus_iommu_मुक्त,
#पूर्ण_अगर
	.map_page		= sbus_iommu_map_page_pflush,
	.unmap_page		= sbus_iommu_unmap_page,
	.map_sg			= sbus_iommu_map_sg_pflush,
	.unmap_sg		= sbus_iommu_unmap_sg,
पूर्ण;

व्योम __init ld_mmu_iommu(व्योम)
अणु
	अगर (viking_mxcc_present || srmmu_modtype == HyperSparc) अणु
		dvma_prot = __pgprot(SRMMU_CACHE | SRMMU_ET_PTE | SRMMU_PRIV);
		ioperm_noc = IOPTE_CACHE | IOPTE_WRITE | IOPTE_VALID;
	पूर्ण अन्यथा अणु
		dvma_prot = __pgprot(SRMMU_ET_PTE | SRMMU_PRIV);
		ioperm_noc = IOPTE_WRITE | IOPTE_VALID;
	पूर्ण
पूर्ण
