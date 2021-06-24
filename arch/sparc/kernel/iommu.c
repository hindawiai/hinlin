<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* iommu.c: Generic sparc64 IOMMU support.
 *
 * Copyright (C) 1999, 2007, 2008 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1999, 2000 Jakub Jelinek (jakub@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/iommu-helper.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <यंत्र/iommu-common.h>

#अगर_घोषित CONFIG_PCI
#समावेश <linux/pci.h>
#पूर्ण_अगर

#समावेश <यंत्र/iommu.h>

#समावेश "iommu_common.h"
#समावेश "kernel.h"

#घोषणा STC_CTXMATCH_ADDR(STC, CTX)	\
	((STC)->strbuf_ctxmatch_base + ((CTX) << 3))
#घोषणा STC_FLUSHFLAG_INIT(STC) \
	(*((STC)->strbuf_flushflag) = 0UL)
#घोषणा STC_FLUSHFLAG_SET(STC) \
	(*((STC)->strbuf_flushflag) != 0UL)

#घोषणा iommu_पढ़ो(__reg) \
(अणु	u64 __ret; \
	__यंत्र__ __अस्थिर__("ldxa [%1] %2, %0" \
			     : "=r" (__ret) \
			     : "r" (__reg), "i" (ASI_PHYS_BYPASS_EC_E) \
			     : "memory"); \
	__ret; \
पूर्ण)
#घोषणा iommu_ग_लिखो(__reg, __val) \
	__यंत्र__ __अस्थिर__("stxa %0, [%1] %2" \
			     : /* no outमाला_दो */ \
			     : "r" (__val), "r" (__reg), \
			       "i" (ASI_PHYS_BYPASS_EC_E))

/* Must be invoked under the IOMMU lock. */
अटल व्योम iommu_flushall(काष्ठा iommu_map_table *iommu_map_table)
अणु
	काष्ठा iommu *iommu = container_of(iommu_map_table, काष्ठा iommu, tbl);
	अगर (iommu->iommu_flushinv) अणु
		iommu_ग_लिखो(iommu->iommu_flushinv, ~(u64)0);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ tag;
		पूर्णांक entry;

		tag = iommu->iommu_tags;
		क्रम (entry = 0; entry < 16; entry++) अणु
			iommu_ग_लिखो(tag, 0);
			tag += 8;
		पूर्ण

		/* Ensure completion of previous PIO ग_लिखोs. */
		(व्योम) iommu_पढ़ो(iommu->ग_लिखो_complete_reg);
	पूर्ण
पूर्ण

#घोषणा IOPTE_CONSISTENT(CTX) \
	(IOPTE_VALID | IOPTE_CACHE | \
	 (((CTX) << 47) & IOPTE_CONTEXT))

#घोषणा IOPTE_STREAMING(CTX) \
	(IOPTE_CONSISTENT(CTX) | IOPTE_STBUF)

/* Existing mappings are never marked invalid, instead they
 * are poपूर्णांकed to a dummy page.
 */
#घोषणा IOPTE_IS_DUMMY(iommu, iopte)	\
	((iopte_val(*iopte) & IOPTE_PAGE) == (iommu)->dummy_page_pa)

अटल अंतरभूत व्योम iopte_make_dummy(काष्ठा iommu *iommu, iopte_t *iopte)
अणु
	अचिन्हित दीर्घ val = iopte_val(*iopte);

	val &= ~IOPTE_PAGE;
	val |= iommu->dummy_page_pa;

	iopte_val(*iopte) = val;
पूर्ण

पूर्णांक iommu_table_init(काष्ठा iommu *iommu, पूर्णांक tsbsize,
		     u32 dma_offset, u32 dma_addr_mask,
		     पूर्णांक numa_node)
अणु
	अचिन्हित दीर्घ i, order, sz, num_tsb_entries;
	काष्ठा page *page;

	num_tsb_entries = tsbsize / माप(iopte_t);

	/* Setup initial software IOMMU state. */
	spin_lock_init(&iommu->lock);
	iommu->ctx_lowest_मुक्त = 1;
	iommu->tbl.table_map_base = dma_offset;
	iommu->dma_addr_mask = dma_addr_mask;

	/* Allocate and initialize the मुक्त area map.  */
	sz = num_tsb_entries / 8;
	sz = (sz + 7UL) & ~7UL;
	iommu->tbl.map = kzalloc_node(sz, GFP_KERNEL, numa_node);
	अगर (!iommu->tbl.map)
		वापस -ENOMEM;

	iommu_tbl_pool_init(&iommu->tbl, num_tsb_entries, IO_PAGE_SHIFT,
			    (tlb_type != hypervisor ? iommu_flushall : शून्य),
			    false, 1, false);

	/* Allocate and initialize the dummy page which we
	 * set inactive IO PTEs to poपूर्णांक to.
	 */
	page = alloc_pages_node(numa_node, GFP_KERNEL, 0);
	अगर (!page) अणु
		prपूर्णांकk(KERN_ERR "IOMMU: Error, gfp(dummy_page) failed.\n");
		जाओ out_मुक्त_map;
	पूर्ण
	iommu->dummy_page = (अचिन्हित दीर्घ) page_address(page);
	स_रखो((व्योम *)iommu->dummy_page, 0, PAGE_SIZE);
	iommu->dummy_page_pa = (अचिन्हित दीर्घ) __pa(iommu->dummy_page);

	/* Now allocate and setup the IOMMU page table itself.  */
	order = get_order(tsbsize);
	page = alloc_pages_node(numa_node, GFP_KERNEL, order);
	अगर (!page) अणु
		prपूर्णांकk(KERN_ERR "IOMMU: Error, gfp(tsb) failed.\n");
		जाओ out_मुक्त_dummy_page;
	पूर्ण
	iommu->page_table = (iopte_t *)page_address(page);

	क्रम (i = 0; i < num_tsb_entries; i++)
		iopte_make_dummy(iommu, &iommu->page_table[i]);

	वापस 0;

out_मुक्त_dummy_page:
	मुक्त_page(iommu->dummy_page);
	iommu->dummy_page = 0UL;

out_मुक्त_map:
	kमुक्त(iommu->tbl.map);
	iommu->tbl.map = शून्य;

	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत iopte_t *alloc_npages(काष्ठा device *dev,
				    काष्ठा iommu *iommu,
				    अचिन्हित दीर्घ npages)
अणु
	अचिन्हित दीर्घ entry;

	entry = iommu_tbl_range_alloc(dev, &iommu->tbl, npages, शून्य,
				      (अचिन्हित दीर्घ)(-1), 0);
	अगर (unlikely(entry == IOMMU_ERROR_CODE))
		वापस शून्य;

	वापस iommu->page_table + entry;
पूर्ण

अटल पूर्णांक iommu_alloc_ctx(काष्ठा iommu *iommu)
अणु
	पूर्णांक lowest = iommu->ctx_lowest_मुक्त;
	पूर्णांक n = find_next_zero_bit(iommu->ctx_biपंचांगap, IOMMU_NUM_CTXS, lowest);

	अगर (unlikely(n == IOMMU_NUM_CTXS)) अणु
		n = find_next_zero_bit(iommu->ctx_biपंचांगap, lowest, 1);
		अगर (unlikely(n == lowest)) अणु
			prपूर्णांकk(KERN_WARNING "IOMMU: Ran out of contexts.\n");
			n = 0;
		पूर्ण
	पूर्ण
	अगर (n)
		__set_bit(n, iommu->ctx_biपंचांगap);

	वापस n;
पूर्ण

अटल अंतरभूत व्योम iommu_मुक्त_ctx(काष्ठा iommu *iommu, पूर्णांक ctx)
अणु
	अगर (likely(ctx)) अणु
		__clear_bit(ctx, iommu->ctx_biपंचांगap);
		अगर (ctx < iommu->ctx_lowest_मुक्त)
			iommu->ctx_lowest_मुक्त = ctx;
	पूर्ण
पूर्ण

अटल व्योम *dma_4u_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				   dma_addr_t *dma_addrp, gfp_t gfp,
				   अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ order, first_page;
	काष्ठा iommu *iommu;
	काष्ठा page *page;
	पूर्णांक npages, nid;
	iopte_t *iopte;
	व्योम *ret;

	size = IO_PAGE_ALIGN(size);
	order = get_order(size);
	अगर (order >= 10)
		वापस शून्य;

	nid = dev->archdata.numa_node;
	page = alloc_pages_node(nid, gfp, order);
	अगर (unlikely(!page))
		वापस शून्य;

	first_page = (अचिन्हित दीर्घ) page_address(page);
	स_रखो((अक्षर *)first_page, 0, PAGE_SIZE << order);

	iommu = dev->archdata.iommu;

	iopte = alloc_npages(dev, iommu, size >> IO_PAGE_SHIFT);

	अगर (unlikely(iopte == शून्य)) अणु
		मुक्त_pages(first_page, order);
		वापस शून्य;
	पूर्ण

	*dma_addrp = (iommu->tbl.table_map_base +
		      ((iopte - iommu->page_table) << IO_PAGE_SHIFT));
	ret = (व्योम *) first_page;
	npages = size >> IO_PAGE_SHIFT;
	first_page = __pa(first_page);
	जबतक (npages--) अणु
		iopte_val(*iopte) = (IOPTE_CONSISTENT(0UL) |
				     IOPTE_WRITE |
				     (first_page & IOPTE_PAGE));
		iopte++;
		first_page += IO_PAGE_SIZE;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dma_4u_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
				 व्योम *cpu, dma_addr_t dvma,
				 अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu *iommu;
	अचिन्हित दीर्घ order, npages;

	npages = IO_PAGE_ALIGN(size) >> IO_PAGE_SHIFT;
	iommu = dev->archdata.iommu;

	iommu_tbl_range_मुक्त(&iommu->tbl, dvma, npages, IOMMU_ERROR_CODE);

	order = get_order(size);
	अगर (order < 10)
		मुक्त_pages((अचिन्हित दीर्घ)cpu, order);
पूर्ण

अटल dma_addr_t dma_4u_map_page(काष्ठा device *dev, काष्ठा page *page,
				  अचिन्हित दीर्घ offset, माप_प्रकार sz,
				  क्रमागत dma_data_direction direction,
				  अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu *iommu;
	काष्ठा strbuf *strbuf;
	iopte_t *base;
	अचिन्हित दीर्घ flags, npages, oaddr;
	अचिन्हित दीर्घ i, base_paddr, ctx;
	u32 bus_addr, ret;
	अचिन्हित दीर्घ iopte_protection;

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	अगर (unlikely(direction == DMA_NONE))
		जाओ bad_no_ctx;

	oaddr = (अचिन्हित दीर्घ)(page_address(page) + offset);
	npages = IO_PAGE_ALIGN(oaddr + sz) - (oaddr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;

	base = alloc_npages(dev, iommu, npages);
	spin_lock_irqsave(&iommu->lock, flags);
	ctx = 0;
	अगर (iommu->iommu_ctxflush)
		ctx = iommu_alloc_ctx(iommu);
	spin_unlock_irqrestore(&iommu->lock, flags);

	अगर (unlikely(!base))
		जाओ bad;

	bus_addr = (iommu->tbl.table_map_base +
		    ((base - iommu->page_table) << IO_PAGE_SHIFT));
	ret = bus_addr | (oaddr & ~IO_PAGE_MASK);
	base_paddr = __pa(oaddr & IO_PAGE_MASK);
	अगर (strbuf->strbuf_enabled)
		iopte_protection = IOPTE_STREAMING(ctx);
	अन्यथा
		iopte_protection = IOPTE_CONSISTENT(ctx);
	अगर (direction != DMA_TO_DEVICE)
		iopte_protection |= IOPTE_WRITE;

	क्रम (i = 0; i < npages; i++, base++, base_paddr += IO_PAGE_SIZE)
		iopte_val(*base) = iopte_protection | base_paddr;

	वापस ret;

bad:
	iommu_मुक्त_ctx(iommu, ctx);
bad_no_ctx:
	अगर (prपूर्णांकk_ratelimit())
		WARN_ON(1);
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल व्योम strbuf_flush(काष्ठा strbuf *strbuf, काष्ठा iommu *iommu,
			 u32 vaddr, अचिन्हित दीर्घ ctx, अचिन्हित दीर्घ npages,
			 क्रमागत dma_data_direction direction)
अणु
	पूर्णांक limit;

	अगर (strbuf->strbuf_ctxflush &&
	    iommu->iommu_ctxflush) अणु
		अचिन्हित दीर्घ matchreg, flushreg;
		u64 val;

		flushreg = strbuf->strbuf_ctxflush;
		matchreg = STC_CTXMATCH_ADDR(strbuf, ctx);

		iommu_ग_लिखो(flushreg, ctx);
		val = iommu_पढ़ो(matchreg);
		val &= 0xffff;
		अगर (!val)
			जाओ करो_flush_sync;

		जबतक (val) अणु
			अगर (val & 0x1)
				iommu_ग_लिखो(flushreg, ctx);
			val >>= 1;
		पूर्ण
		val = iommu_पढ़ो(matchreg);
		अगर (unlikely(val)) अणु
			prपूर्णांकk(KERN_WARNING "strbuf_flush: ctx flush "
			       "timeout matchreg[%llx] ctx[%lx]\n",
			       val, ctx);
			जाओ करो_page_flush;
		पूर्ण
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ i;

	करो_page_flush:
		क्रम (i = 0; i < npages; i++, vaddr += IO_PAGE_SIZE)
			iommu_ग_लिखो(strbuf->strbuf_pflush, vaddr);
	पूर्ण

करो_flush_sync:
	/* If the device could not have possibly put dirty data पूर्णांकo
	 * the streaming cache, no flush-flag synchronization needs
	 * to be perक्रमmed.
	 */
	अगर (direction == DMA_TO_DEVICE)
		वापस;

	STC_FLUSHFLAG_INIT(strbuf);
	iommu_ग_लिखो(strbuf->strbuf_fsync, strbuf->strbuf_flushflag_pa);
	(व्योम) iommu_पढ़ो(iommu->ग_लिखो_complete_reg);

	limit = 100000;
	जबतक (!STC_FLUSHFLAG_SET(strbuf)) अणु
		limit--;
		अगर (!limit)
			अवरोध;
		udelay(1);
		rmb();
	पूर्ण
	अगर (!limit)
		prपूर्णांकk(KERN_WARNING "strbuf_flush: flushflag timeout "
		       "vaddr[%08x] ctx[%lx] npages[%ld]\n",
		       vaddr, ctx, npages);
पूर्ण

अटल व्योम dma_4u_unmap_page(काष्ठा device *dev, dma_addr_t bus_addr,
			      माप_प्रकार sz, क्रमागत dma_data_direction direction,
			      अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu *iommu;
	काष्ठा strbuf *strbuf;
	iopte_t *base;
	अचिन्हित दीर्घ flags, npages, ctx, i;

	अगर (unlikely(direction == DMA_NONE)) अणु
		अगर (prपूर्णांकk_ratelimit())
			WARN_ON(1);
		वापस;
	पूर्ण

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	npages = IO_PAGE_ALIGN(bus_addr + sz) - (bus_addr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;
	base = iommu->page_table +
		((bus_addr - iommu->tbl.table_map_base) >> IO_PAGE_SHIFT);
	bus_addr &= IO_PAGE_MASK;

	spin_lock_irqsave(&iommu->lock, flags);

	/* Record the context, अगर any. */
	ctx = 0;
	अगर (iommu->iommu_ctxflush)
		ctx = (iopte_val(*base) & IOPTE_CONTEXT) >> 47UL;

	/* Step 1: Kick data out of streaming buffers अगर necessary. */
	अगर (strbuf->strbuf_enabled && !(attrs & DMA_ATTR_SKIP_CPU_SYNC))
		strbuf_flush(strbuf, iommu, bus_addr, ctx,
			     npages, direction);

	/* Step 2: Clear out TSB entries. */
	क्रम (i = 0; i < npages; i++)
		iopte_make_dummy(iommu, base + i);

	iommu_मुक्त_ctx(iommu, ctx);
	spin_unlock_irqrestore(&iommu->lock, flags);

	iommu_tbl_range_मुक्त(&iommu->tbl, bus_addr, npages, IOMMU_ERROR_CODE);
पूर्ण

अटल पूर्णांक dma_4u_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			 पूर्णांक nelems, क्रमागत dma_data_direction direction,
			 अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s, *outs, *segstart;
	अचिन्हित दीर्घ flags, handle, prot, ctx;
	dma_addr_t dma_next = 0, dma_addr;
	अचिन्हित पूर्णांक max_seg_size;
	अचिन्हित दीर्घ seg_boundary_size;
	पूर्णांक outcount, incount, i;
	काष्ठा strbuf *strbuf;
	काष्ठा iommu *iommu;
	अचिन्हित दीर्घ base_shअगरt;

	BUG_ON(direction == DMA_NONE);

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;
	अगर (nelems == 0 || !iommu)
		वापस 0;

	spin_lock_irqsave(&iommu->lock, flags);

	ctx = 0;
	अगर (iommu->iommu_ctxflush)
		ctx = iommu_alloc_ctx(iommu);

	अगर (strbuf->strbuf_enabled)
		prot = IOPTE_STREAMING(ctx);
	अन्यथा
		prot = IOPTE_CONSISTENT(ctx);
	अगर (direction != DMA_TO_DEVICE)
		prot |= IOPTE_WRITE;

	outs = s = segstart = &sglist[0];
	outcount = 1;
	incount = nelems;
	handle = 0;

	/* Init first segment length क्रम backout at failure */
	outs->dma_length = 0;

	max_seg_size = dma_get_max_seg_size(dev);
	seg_boundary_size = dma_get_seg_boundary_nr_pages(dev, IO_PAGE_SHIFT);
	base_shअगरt = iommu->tbl.table_map_base >> IO_PAGE_SHIFT;
	क्रम_each_sg(sglist, s, nelems, i) अणु
		अचिन्हित दीर्घ paddr, npages, entry, out_entry = 0, slen;
		iopte_t *base;

		slen = s->length;
		/* Sanity check */
		अगर (slen == 0) अणु
			dma_next = 0;
			जारी;
		पूर्ण
		/* Allocate iommu entries क्रम that segment */
		paddr = (अचिन्हित दीर्घ) SG_ENT_PHYS_ADDRESS(s);
		npages = iommu_num_pages(paddr, slen, IO_PAGE_SIZE);
		entry = iommu_tbl_range_alloc(dev, &iommu->tbl, npages,
					      &handle, (अचिन्हित दीर्घ)(-1), 0);

		/* Handle failure */
		अगर (unlikely(entry == IOMMU_ERROR_CODE)) अणु
			अगर (prपूर्णांकk_ratelimit())
				prपूर्णांकk(KERN_INFO "iommu_alloc failed, iommu %p paddr %lx"
				       " npages %lx\n", iommu, paddr, npages);
			जाओ iommu_map_failed;
		पूर्ण

		base = iommu->page_table + entry;

		/* Convert entry to a dma_addr_t */
		dma_addr = iommu->tbl.table_map_base +
			(entry << IO_PAGE_SHIFT);
		dma_addr |= (s->offset & ~IO_PAGE_MASK);

		/* Insert पूर्णांकo HW table */
		paddr &= IO_PAGE_MASK;
		जबतक (npages--) अणु
			iopte_val(*base) = prot | paddr;
			base++;
			paddr += IO_PAGE_SIZE;
		पूर्ण

		/* If we are in an खोलो segment, try merging */
		अगर (segstart != s) अणु
			/* We cannot merge अगर:
			 * - allocated dma_addr isn't contiguous to previous allocation
			 */
			अगर ((dma_addr != dma_next) ||
			    (outs->dma_length + s->length > max_seg_size) ||
			    (is_span_boundary(out_entry, base_shअगरt,
					      seg_boundary_size, outs, s))) अणु
				/* Can't merge: create a new segment */
				segstart = s;
				outcount++;
				outs = sg_next(outs);
			पूर्ण अन्यथा अणु
				outs->dma_length += s->length;
			पूर्ण
		पूर्ण

		अगर (segstart == s) अणु
			/* This is a new segment, fill entries */
			outs->dma_address = dma_addr;
			outs->dma_length = slen;
			out_entry = entry;
		पूर्ण

		/* Calculate next page poपूर्णांकer क्रम contiguous check */
		dma_next = dma_addr + slen;
	पूर्ण

	spin_unlock_irqrestore(&iommu->lock, flags);

	अगर (outcount < incount) अणु
		outs = sg_next(outs);
		outs->dma_address = DMA_MAPPING_ERROR;
		outs->dma_length = 0;
	पूर्ण

	वापस outcount;

iommu_map_failed:
	क्रम_each_sg(sglist, s, nelems, i) अणु
		अगर (s->dma_length != 0) अणु
			अचिन्हित दीर्घ vaddr, npages, entry, j;
			iopte_t *base;

			vaddr = s->dma_address & IO_PAGE_MASK;
			npages = iommu_num_pages(s->dma_address, s->dma_length,
						 IO_PAGE_SIZE);

			entry = (vaddr - iommu->tbl.table_map_base)
				>> IO_PAGE_SHIFT;
			base = iommu->page_table + entry;

			क्रम (j = 0; j < npages; j++)
				iopte_make_dummy(iommu, base + j);

			iommu_tbl_range_मुक्त(&iommu->tbl, vaddr, npages,
					     IOMMU_ERROR_CODE);

			s->dma_address = DMA_MAPPING_ERROR;
			s->dma_length = 0;
		पूर्ण
		अगर (s == outs)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&iommu->lock, flags);

	वापस 0;
पूर्ण

/* If contexts are being used, they are the same in all of the mappings
 * we make क्रम a particular SG.
 */
अटल अचिन्हित दीर्घ fetch_sg_ctx(काष्ठा iommu *iommu, काष्ठा scatterlist *sg)
अणु
	अचिन्हित दीर्घ ctx = 0;

	अगर (iommu->iommu_ctxflush) अणु
		iopte_t *base;
		u32 bus_addr;
		काष्ठा iommu_map_table *tbl = &iommu->tbl;

		bus_addr = sg->dma_address & IO_PAGE_MASK;
		base = iommu->page_table +
			((bus_addr - tbl->table_map_base) >> IO_PAGE_SHIFT);

		ctx = (iopte_val(*base) & IOPTE_CONTEXT) >> 47UL;
	पूर्ण
	वापस ctx;
पूर्ण

अटल व्योम dma_4u_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			    पूर्णांक nelems, क्रमागत dma_data_direction direction,
			    अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ flags, ctx;
	काष्ठा scatterlist *sg;
	काष्ठा strbuf *strbuf;
	काष्ठा iommu *iommu;

	BUG_ON(direction == DMA_NONE);

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	ctx = fetch_sg_ctx(iommu, sglist);

	spin_lock_irqsave(&iommu->lock, flags);

	sg = sglist;
	जबतक (nelems--) अणु
		dma_addr_t dma_handle = sg->dma_address;
		अचिन्हित पूर्णांक len = sg->dma_length;
		अचिन्हित दीर्घ npages, entry;
		iopte_t *base;
		पूर्णांक i;

		अगर (!len)
			अवरोध;
		npages = iommu_num_pages(dma_handle, len, IO_PAGE_SIZE);

		entry = ((dma_handle - iommu->tbl.table_map_base)
			 >> IO_PAGE_SHIFT);
		base = iommu->page_table + entry;

		dma_handle &= IO_PAGE_MASK;
		अगर (strbuf->strbuf_enabled && !(attrs & DMA_ATTR_SKIP_CPU_SYNC))
			strbuf_flush(strbuf, iommu, dma_handle, ctx,
				     npages, direction);

		क्रम (i = 0; i < npages; i++)
			iopte_make_dummy(iommu, base + i);

		iommu_tbl_range_मुक्त(&iommu->tbl, dma_handle, npages,
				     IOMMU_ERROR_CODE);
		sg = sg_next(sg);
	पूर्ण

	iommu_मुक्त_ctx(iommu, ctx);

	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण

अटल व्योम dma_4u_sync_single_क्रम_cpu(काष्ठा device *dev,
				       dma_addr_t bus_addr, माप_प्रकार sz,
				       क्रमागत dma_data_direction direction)
अणु
	काष्ठा iommu *iommu;
	काष्ठा strbuf *strbuf;
	अचिन्हित दीर्घ flags, ctx, npages;

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	अगर (!strbuf->strbuf_enabled)
		वापस;

	spin_lock_irqsave(&iommu->lock, flags);

	npages = IO_PAGE_ALIGN(bus_addr + sz) - (bus_addr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;
	bus_addr &= IO_PAGE_MASK;

	/* Step 1: Record the context, अगर any. */
	ctx = 0;
	अगर (iommu->iommu_ctxflush &&
	    strbuf->strbuf_ctxflush) अणु
		iopte_t *iopte;
		काष्ठा iommu_map_table *tbl = &iommu->tbl;

		iopte = iommu->page_table +
			((bus_addr - tbl->table_map_base)>>IO_PAGE_SHIFT);
		ctx = (iopte_val(*iopte) & IOPTE_CONTEXT) >> 47UL;
	पूर्ण

	/* Step 2: Kick data out of streaming buffers. */
	strbuf_flush(strbuf, iommu, bus_addr, ctx, npages, direction);

	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण

अटल व्योम dma_4u_sync_sg_क्रम_cpu(काष्ठा device *dev,
				   काष्ठा scatterlist *sglist, पूर्णांक nelems,
				   क्रमागत dma_data_direction direction)
अणु
	काष्ठा iommu *iommu;
	काष्ठा strbuf *strbuf;
	अचिन्हित दीर्घ flags, ctx, npages, i;
	काष्ठा scatterlist *sg, *sgprv;
	u32 bus_addr;

	iommu = dev->archdata.iommu;
	strbuf = dev->archdata.stc;

	अगर (!strbuf->strbuf_enabled)
		वापस;

	spin_lock_irqsave(&iommu->lock, flags);

	/* Step 1: Record the context, अगर any. */
	ctx = 0;
	अगर (iommu->iommu_ctxflush &&
	    strbuf->strbuf_ctxflush) अणु
		iopte_t *iopte;
		काष्ठा iommu_map_table *tbl = &iommu->tbl;

		iopte = iommu->page_table + ((sglist[0].dma_address -
			tbl->table_map_base) >> IO_PAGE_SHIFT);
		ctx = (iopte_val(*iopte) & IOPTE_CONTEXT) >> 47UL;
	पूर्ण

	/* Step 2: Kick data out of streaming buffers. */
	bus_addr = sglist[0].dma_address & IO_PAGE_MASK;
	sgprv = शून्य;
	क्रम_each_sg(sglist, sg, nelems, i) अणु
		अगर (sg->dma_length == 0)
			अवरोध;
		sgprv = sg;
	पूर्ण

	npages = (IO_PAGE_ALIGN(sgprv->dma_address + sgprv->dma_length)
		  - bus_addr) >> IO_PAGE_SHIFT;
	strbuf_flush(strbuf, iommu, bus_addr, ctx, npages, direction);

	spin_unlock_irqrestore(&iommu->lock, flags);
पूर्ण

अटल पूर्णांक dma_4u_supported(काष्ठा device *dev, u64 device_mask)
अणु
	काष्ठा iommu *iommu = dev->archdata.iommu;

	अगर (ali_sound_dma_hack(dev, device_mask))
		वापस 1;

	अगर (device_mask < iommu->dma_addr_mask)
		वापस 0;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dma_map_ops sun4u_dma_ops = अणु
	.alloc			= dma_4u_alloc_coherent,
	.मुक्त			= dma_4u_मुक्त_coherent,
	.map_page		= dma_4u_map_page,
	.unmap_page		= dma_4u_unmap_page,
	.map_sg			= dma_4u_map_sg,
	.unmap_sg		= dma_4u_unmap_sg,
	.sync_single_क्रम_cpu	= dma_4u_sync_single_क्रम_cpu,
	.sync_sg_क्रम_cpu	= dma_4u_sync_sg_क्रम_cpu,
	.dma_supported		= dma_4u_supported,
पूर्ण;

स्थिर काष्ठा dma_map_ops *dma_ops = &sun4u_dma_ops;
EXPORT_SYMBOL(dma_ops);
