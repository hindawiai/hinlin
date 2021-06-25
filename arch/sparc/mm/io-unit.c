<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * io-unit.c:  IO-UNIT specअगरic routines क्रम memory management.
 *
 * Copyright (C) 1997,1998 Jakub Jelinek    (jj@sunsite.mff.cuni.cz)
 */
 
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/io-unit.h>
#समावेश <यंत्र/mxcc.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/oplib.h>

#समावेश "mm_32.h"

/* #घोषणा IOUNIT_DEBUG */
#अगर_घोषित IOUNIT_DEBUG
#घोषणा IOD(x) prपूर्णांकk(x)
#अन्यथा
#घोषणा IOD(x) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा IOPERM        (IOUPTE_CACHE | IOUPTE_WRITE | IOUPTE_VALID)
#घोषणा MKIOPTE(phys) __iopte((((phys)>>4) & IOUPTE_PAGE) | IOPERM)

अटल स्थिर काष्ठा dma_map_ops iounit_dma_ops;

अटल व्योम __init iounit_iommu_init(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा iounit_काष्ठा *iounit;
	iopte_t __iomem *xpt;
	iopte_t __iomem *xptend;

	iounit = kzalloc(माप(काष्ठा iounit_काष्ठा), GFP_ATOMIC);
	अगर (!iounit) अणु
		prom_म_लिखो("SUN4D: Cannot alloc iounit, halting.\n");
		prom_halt();
	पूर्ण

	iounit->limit[0] = IOUNIT_BMAP1_START;
	iounit->limit[1] = IOUNIT_BMAP2_START;
	iounit->limit[2] = IOUNIT_BMAPM_START;
	iounit->limit[3] = IOUNIT_BMAPM_END;
	iounit->rotor[1] = IOUNIT_BMAP2_START;
	iounit->rotor[2] = IOUNIT_BMAPM_START;

	xpt = of_ioremap(&op->resource[2], 0, PAGE_SIZE * 16, "XPT");
	अगर (!xpt) अणु
		prom_म_लिखो("SUN4D: Cannot map External Page Table.");
		prom_halt();
	पूर्ण
	
	op->dev.archdata.iommu = iounit;
	iounit->page_table = xpt;
	spin_lock_init(&iounit->lock);

	xptend = iounit->page_table + (16 * PAGE_SIZE) / माप(iopte_t);
	क्रम (; xpt < xptend; xpt++)
		sbus_ग_लिखोl(0, xpt);

	op->dev.dma_ops = &iounit_dma_ops;
पूर्ण

अटल पूर्णांक __init iounit_init(व्योम)
अणु
	बाह्य व्योम sun4d_init_sbi_irq(व्योम);
	काष्ठा device_node *dp;

	क्रम_each_node_by_name(dp, "sbi") अणु
		काष्ठा platक्रमm_device *op = of_find_device_by_node(dp);

		iounit_iommu_init(op);
		of_propagate_archdata(op);
	पूर्ण

	sun4d_init_sbi_irq();

	वापस 0;
पूर्ण

subsys_initcall(iounit_init);

/* One has to hold iounit->lock to call this */
अटल अचिन्हित दीर्घ iounit_get_area(काष्ठा iounit_काष्ठा *iounit, अचिन्हित दीर्घ vaddr, पूर्णांक size)
अणु
	पूर्णांक i, j, k, npages;
	अचिन्हित दीर्घ rotor, scan, limit;
	iopte_t iopte;

        npages = ((vaddr & ~PAGE_MASK) + size + (PAGE_SIZE-1)) >> PAGE_SHIFT;

	/* A tiny bit of magic ingredience :) */
	चयन (npages) अणु
	हाल 1: i = 0x0231; अवरोध;
	हाल 2: i = 0x0132; अवरोध;
	शेष: i = 0x0213; अवरोध;
	पूर्ण
	
	IOD(("iounit_get_area(%08lx,%d[%d])=", vaddr, size, npages));
	
next:	j = (i & 15);
	rotor = iounit->rotor[j - 1];
	limit = iounit->limit[j];
	scan = rotor;
nexti:	scan = find_next_zero_bit(iounit->bmap, limit, scan);
	अगर (scan + npages > limit) अणु
		अगर (limit != rotor) अणु
			limit = rotor;
			scan = iounit->limit[j - 1];
			जाओ nexti;
		पूर्ण
		i >>= 4;
		अगर (!(i & 15))
			panic("iounit_get_area: Couldn't find free iopte slots for (%08lx,%d)\n", vaddr, size);
		जाओ next;
	पूर्ण
	क्रम (k = 1, scan++; k < npages; k++)
		अगर (test_bit(scan++, iounit->bmap))
			जाओ nexti;
	iounit->rotor[j - 1] = (scan < limit) ? scan : iounit->limit[j - 1];
	scan -= npages;
	iopte = MKIOPTE(__pa(vaddr & PAGE_MASK));
	vaddr = IOUNIT_DMA_BASE + (scan << PAGE_SHIFT) + (vaddr & ~PAGE_MASK);
	क्रम (k = 0; k < npages; k++, iopte = __iopte(iopte_val(iopte) + 0x100), scan++) अणु
		set_bit(scan, iounit->bmap);
		sbus_ग_लिखोl(iopte_val(iopte), &iounit->page_table[scan]);
	पूर्ण
	IOD(("%08lx\n", vaddr));
	वापस vaddr;
पूर्ण

अटल dma_addr_t iounit_map_page(काष्ठा device *dev, काष्ठा page *page,
		अचिन्हित दीर्घ offset, माप_प्रकार len, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	व्योम *vaddr = page_address(page) + offset;
	काष्ठा iounit_काष्ठा *iounit = dev->archdata.iommu;
	अचिन्हित दीर्घ ret, flags;
	
	/* XXX So what is maxphys क्रम us and how करो drivers know it? */
	अगर (!len || len > 256 * 1024)
		वापस DMA_MAPPING_ERROR;

	spin_lock_irqsave(&iounit->lock, flags);
	ret = iounit_get_area(iounit, (अचिन्हित दीर्घ)vaddr, len);
	spin_unlock_irqrestore(&iounit->lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक iounit_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl, पूर्णांक nents,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iounit_काष्ठा *iounit = dev->archdata.iommu;
	काष्ठा scatterlist *sg;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* FIXME: Cache some resolved pages - often several sg entries are to the same page */
	spin_lock_irqsave(&iounit->lock, flags);
	क्रम_each_sg(sgl, sg, nents, i) अणु
		sg->dma_address = iounit_get_area(iounit, (अचिन्हित दीर्घ) sg_virt(sg), sg->length);
		sg->dma_length = sg->length;
	पूर्ण
	spin_unlock_irqrestore(&iounit->lock, flags);
	वापस nents;
पूर्ण

अटल व्योम iounit_unmap_page(काष्ठा device *dev, dma_addr_t vaddr, माप_प्रकार len,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iounit_काष्ठा *iounit = dev->archdata.iommu;
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&iounit->lock, flags);
	len = ((vaddr & ~PAGE_MASK) + len + (PAGE_SIZE-1)) >> PAGE_SHIFT;
	vaddr = (vaddr - IOUNIT_DMA_BASE) >> PAGE_SHIFT;
	IOD(("iounit_release %08lx-%08lx\n", (दीर्घ)vaddr, (दीर्घ)len+vaddr));
	क्रम (len += vaddr; vaddr < len; vaddr++)
		clear_bit(vaddr, iounit->bmap);
	spin_unlock_irqrestore(&iounit->lock, flags);
पूर्ण

अटल व्योम iounit_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sgl,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iounit_काष्ठा *iounit = dev->archdata.iommu;
	अचिन्हित दीर्घ flags, vaddr, len;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	spin_lock_irqsave(&iounit->lock, flags);
	क्रम_each_sg(sgl, sg, nents, i) अणु
		len = ((sg->dma_address & ~PAGE_MASK) + sg->length + (PAGE_SIZE-1)) >> PAGE_SHIFT;
		vaddr = (sg->dma_address - IOUNIT_DMA_BASE) >> PAGE_SHIFT;
		IOD(("iounit_release %08lx-%08lx\n", (दीर्घ)vaddr, (दीर्घ)len+vaddr));
		क्रम (len += vaddr; vaddr < len; vaddr++)
			clear_bit(vaddr, iounit->bmap);
	पूर्ण
	spin_unlock_irqrestore(&iounit->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_SBUS
अटल व्योम *iounit_alloc(काष्ठा device *dev, माप_प्रकार len,
		dma_addr_t *dma_handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iounit_काष्ठा *iounit = dev->archdata.iommu;
	अचिन्हित दीर्घ va, addr, page, end, ret;
	pgprot_t dvma_prot;
	iopte_t __iomem *iopte;

	/* XXX So what is maxphys क्रम us and how करो drivers know it? */
	अगर (!len || len > 256 * 1024)
		वापस शून्य;

	len = PAGE_ALIGN(len);
	va = __get_मुक्त_pages(gfp | __GFP_ZERO, get_order(len));
	अगर (!va)
		वापस शून्य;

	addr = ret = sparc_dma_alloc_resource(dev, len);
	अगर (!addr)
		जाओ out_मुक्त_pages;
	*dma_handle = addr;

	dvma_prot = __pgprot(SRMMU_CACHE | SRMMU_ET_PTE | SRMMU_PRIV);
	end = PAGE_ALIGN((addr + len));
	जबतक(addr < end) अणु
		page = va;
		अणु
			pmd_t *pmdp;
			pte_t *ptep;
			दीर्घ i;

			pmdp = pmd_off_k(addr);
			ptep = pte_offset_map(pmdp, addr);

			set_pte(ptep, mk_pte(virt_to_page(page), dvma_prot));

			i = ((addr - IOUNIT_DMA_BASE) >> PAGE_SHIFT);

			iopte = iounit->page_table + i;
			sbus_ग_लिखोl(iopte_val(MKIOPTE(__pa(page))), iopte);
		पूर्ण
		addr += PAGE_SIZE;
		va += PAGE_SIZE;
	पूर्ण
	flush_cache_all();
	flush_tlb_all();

	वापस (व्योम *)ret;

out_मुक्त_pages:
	मुक्त_pages(va, get_order(len));
	वापस शून्य;
पूर्ण

अटल व्योम iounit_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_addr, अचिन्हित दीर्घ attrs)
अणु
	/* XXX Somebody please fill this in */
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dma_map_ops iounit_dma_ops = अणु
#अगर_घोषित CONFIG_SBUS
	.alloc			= iounit_alloc,
	.मुक्त			= iounit_मुक्त,
#पूर्ण_अगर
	.map_page		= iounit_map_page,
	.unmap_page		= iounit_unmap_page,
	.map_sg			= iounit_map_sg,
	.unmap_sg		= iounit_unmap_sg,
पूर्ण;
