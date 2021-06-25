<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/sysdev/dart_iommu.c
 *
 * Copyright (C) 2004 Olof Johansson <olof@lixom.net>, IBM Corporation
 * Copyright (C) 2005 Benjamin Herrenschmidt <benh@kernel.crashing.org>,
 *                    IBM Corporation
 *
 * Based on pSeries_iommu.c:
 * Copyright (C) 2001 Mike Corrigan & Dave Engebretsen, IBM Corporation
 * Copyright (C) 2004 Olof Johansson <olof@lixom.net>, IBM Corporation
 *
 * Dynamic DMA mapping support, Apple U3, U4 & IBM CPC925 "DART" iommu.
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/suspend.h>
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kmemleak.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/ppc-pci.h>

#समावेश "dart.h"

/* DART table address and size */
अटल u32 *dart_tablebase;
अटल अचिन्हित दीर्घ dart_tablesize;

/* Mapped base address क्रम the dart */
अटल अचिन्हित पूर्णांक __iomem *dart;

/* Dummy val that entries are set to when unused */
अटल अचिन्हित पूर्णांक dart_emptyval;

अटल काष्ठा iommu_table iommu_table_dart;
अटल पूर्णांक iommu_table_dart_inited;
अटल पूर्णांक dart_dirty;
अटल पूर्णांक dart_is_u4;

#घोषणा DART_U4_BYPASS_BASE	0x8000000000ull

#घोषणा DBG(...)

अटल DEFINE_SPINLOCK(invalidate_lock);

अटल अंतरभूत व्योम dart_tlb_invalidate_all(व्योम)
अणु
	अचिन्हित दीर्घ l = 0;
	अचिन्हित पूर्णांक reg, inv_bit;
	अचिन्हित दीर्घ limit;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&invalidate_lock, flags);

	DBG("dart: flush\n");

	/* To invalidate the DART, set the DARTCNTL_FLUSHTLB bit in the
	 * control रेजिस्टर and रुको क्रम it to clear.
	 *
	 * Gotcha: Someबार, the DART won't detect that the bit माला_लो
	 * set. If so, clear it and set it again.
	 */

	limit = 0;

	inv_bit = dart_is_u4 ? DART_CNTL_U4_FLUSHTLB : DART_CNTL_U3_FLUSHTLB;
retry:
	l = 0;
	reg = DART_IN(DART_CNTL);
	reg |= inv_bit;
	DART_OUT(DART_CNTL, reg);

	जबतक ((DART_IN(DART_CNTL) & inv_bit) && l < (1L << limit))
		l++;
	अगर (l == (1L << limit)) अणु
		अगर (limit < 4) अणु
			limit++;
			reg = DART_IN(DART_CNTL);
			reg &= ~inv_bit;
			DART_OUT(DART_CNTL, reg);
			जाओ retry;
		पूर्ण अन्यथा
			panic("DART: TLB did not flush after waiting a long "
			      "time. Buggy U3 ?");
	पूर्ण

	spin_unlock_irqrestore(&invalidate_lock, flags);
पूर्ण

अटल अंतरभूत व्योम dart_tlb_invalidate_one(अचिन्हित दीर्घ bus_rpn)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक l, limit;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&invalidate_lock, flags);

	reg = DART_CNTL_U4_ENABLE | DART_CNTL_U4_IONE |
		(bus_rpn & DART_CNTL_U4_IONE_MASK);
	DART_OUT(DART_CNTL, reg);

	limit = 0;
रुको_more:
	l = 0;
	जबतक ((DART_IN(DART_CNTL) & DART_CNTL_U4_IONE) && l < (1L << limit)) अणु
		rmb();
		l++;
	पूर्ण

	अगर (l == (1L << limit)) अणु
		अगर (limit < 4) अणु
			limit++;
			जाओ रुको_more;
		पूर्ण अन्यथा
			panic("DART: TLB did not flush after waiting a long "
			      "time. Buggy U4 ?");
	पूर्ण

	spin_unlock_irqrestore(&invalidate_lock, flags);
पूर्ण

अटल व्योम dart_cache_sync(अचिन्हित पूर्णांक *base, अचिन्हित पूर्णांक count)
अणु
	/*
	 * We add 1 to the number of entries to flush, following a
	 * comment in Darwin indicating that the memory controller
	 * can prefetch unmapped memory under some circumstances.
	 */
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)base;
	अचिन्हित दीर्घ end = start + (count + 1) * माप(अचिन्हित पूर्णांक);
	अचिन्हित पूर्णांक पंचांगp;

	/* Perक्रमm a standard cache flush */
	flush_dcache_range(start, end);

	/*
	 * Perक्रमm the sequence described in the CPC925 manual to
	 * ensure all the data माला_लो to a poपूर्णांक the cache incoherent
	 * DART hardware will see.
	 */
	यंत्र अस्थिर(" sync;"
		     " isync;"
		     " dcbf 0,%1;"
		     " sync;"
		     " isync;"
		     " lwz %0,0(%1);"
		     " isync" : "=r" (पंचांगp) : "r" (end) : "memory");
पूर्ण

अटल व्योम dart_flush(काष्ठा iommu_table *tbl)
अणु
	mb();
	अगर (dart_dirty) अणु
		dart_tlb_invalidate_all();
		dart_dirty = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक dart_build(काष्ठा iommu_table *tbl, दीर्घ index,
		       दीर्घ npages, अचिन्हित दीर्घ uaddr,
		       क्रमागत dma_data_direction direction,
		       अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित पूर्णांक *dp, *orig_dp;
	अचिन्हित पूर्णांक rpn;
	दीर्घ l;

	DBG("dart: build at: %lx, %lx, addr: %x\n", index, npages, uaddr);

	orig_dp = dp = ((अचिन्हित पूर्णांक*)tbl->it_base) + index;

	/* On U3, all memory is contiguous, so we can move this
	 * out of the loop.
	 */
	l = npages;
	जबतक (l--) अणु
		rpn = __pa(uaddr) >> DART_PAGE_SHIFT;

		*(dp++) = DARTMAP_VALID | (rpn & DARTMAP_RPNMASK);

		uaddr += DART_PAGE_SIZE;
	पूर्ण
	dart_cache_sync(orig_dp, npages);

	अगर (dart_is_u4) अणु
		rpn = index;
		जबतक (npages--)
			dart_tlb_invalidate_one(rpn++);
	पूर्ण अन्यथा अणु
		dart_dirty = 1;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम dart_मुक्त(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages)
अणु
	अचिन्हित पूर्णांक *dp, *orig_dp;
	दीर्घ orig_npages = npages;

	/* We करोn't worry about flushing the TLB cache. The only drawback of
	 * not करोing it is that we won't catch buggy device drivers करोing
	 * bad DMAs, but then no 32-bit architecture ever करोes either.
	 */

	DBG("dart: free at: %lx, %lx\n", index, npages);

	orig_dp = dp  = ((अचिन्हित पूर्णांक *)tbl->it_base) + index;

	जबतक (npages--)
		*(dp++) = dart_emptyval;

	dart_cache_sync(orig_dp, orig_npages);
पूर्ण

अटल व्योम allocate_dart(व्योम)
अणु
	अचिन्हित दीर्घ पंचांगp;

	/* 512 pages (2MB) is max DART tablesize. */
	dart_tablesize = 1UL << 21;

	/*
	 * 16MB (1 << 24) alignment. We allocate a full 16Mb chuck since we
	 * will blow up an entire large page anyway in the kernel mapping.
	 */
	dart_tablebase = memblock_alloc_try_nid_raw(SZ_16M, SZ_16M,
					MEMBLOCK_LOW_LIMIT, SZ_2G,
					NUMA_NO_NODE);
	अगर (!dart_tablebase)
		panic("Failed to allocate 16MB below 2GB for DART table\n");

	/* There is no poपूर्णांक scanning the DART space क्रम leaks*/
	kmemleak_no_scan((व्योम *)dart_tablebase);

	/* Allocate a spare page to map all invalid DART pages. We need to करो
	 * that to work around what looks like a problem with the HT bridge
	 * prefetching पूर्णांकo invalid pages and corrupting data
	 */
	पंचांगp = memblock_phys_alloc(DART_PAGE_SIZE, DART_PAGE_SIZE);
	अगर (!पंचांगp)
		panic("DART: table allocation failed\n");

	dart_emptyval = DARTMAP_VALID | ((पंचांगp >> DART_PAGE_SHIFT) &
					 DARTMAP_RPNMASK);

	prपूर्णांकk(KERN_INFO "DART table allocated at: %p\n", dart_tablebase);
पूर्ण

अटल पूर्णांक __init dart_init(काष्ठा device_node *dart_node)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ base, size;
	काष्ठा resource r;

	/* IOMMU disabled by the user ? bail out */
	अगर (iommu_is_off)
		वापस -ENODEV;

	/*
	 * Only use the DART अगर the machine has more than 1GB of RAM
	 * or अगर requested with iommu=on on cmdline.
	 *
	 * 1GB of RAM is picked as limit because some शेष devices
	 * (i.e. Airport Extreme) have 30 bit address range limits.
	 */

	अगर (!iommu_क्रमce_on && memblock_end_of_DRAM() <= 0x40000000ull)
		वापस -ENODEV;

	/* Get DART रेजिस्टरs */
	अगर (of_address_to_resource(dart_node, 0, &r))
		panic("DART: can't get register base ! ");

	/* Map in DART रेजिस्टरs */
	dart = ioremap(r.start, resource_size(&r));
	अगर (dart == शून्य)
		panic("DART: Cannot map registers!");

	/* Allocate the DART and dummy page */
	allocate_dart();

	/* Fill initial table */
	क्रम (i = 0; i < dart_tablesize/4; i++)
		dart_tablebase[i] = dart_emptyval;

	/* Push to memory */
	dart_cache_sync(dart_tablebase, dart_tablesize / माप(u32));

	/* Initialize DART with table base and enable it. */
	base = ((अचिन्हित दीर्घ)dart_tablebase) >> DART_PAGE_SHIFT;
	size = dart_tablesize >> DART_PAGE_SHIFT;
	अगर (dart_is_u4) अणु
		size &= DART_SIZE_U4_SIZE_MASK;
		DART_OUT(DART_BASE_U4, base);
		DART_OUT(DART_SIZE_U4, size);
		DART_OUT(DART_CNTL, DART_CNTL_U4_ENABLE);
	पूर्ण अन्यथा अणु
		size &= DART_CNTL_U3_SIZE_MASK;
		DART_OUT(DART_CNTL,
			 DART_CNTL_U3_ENABLE |
			 (base << DART_CNTL_U3_BASE_SHIFT) |
			 (size << DART_CNTL_U3_SIZE_SHIFT));
	पूर्ण

	/* Invalidate DART to get rid of possible stale TLBs */
	dart_tlb_invalidate_all();

	prपूर्णांकk(KERN_INFO "DART IOMMU initialized for %s type chipset\n",
	       dart_is_u4 ? "U4" : "U3");

	वापस 0;
पूर्ण

अटल काष्ठा iommu_table_ops iommu_dart_ops = अणु
	.set = dart_build,
	.clear = dart_मुक्त,
	.flush = dart_flush,
पूर्ण;

अटल व्योम iommu_table_dart_setup(व्योम)
अणु
	iommu_table_dart.it_busno = 0;
	iommu_table_dart.it_offset = 0;
	/* it_size is in number of entries */
	iommu_table_dart.it_size = dart_tablesize / माप(u32);
	iommu_table_dart.it_page_shअगरt = IOMMU_PAGE_SHIFT_4K;

	/* Initialize the common IOMMU code */
	iommu_table_dart.it_base = (अचिन्हित दीर्घ)dart_tablebase;
	iommu_table_dart.it_index = 0;
	iommu_table_dart.it_blocksize = 1;
	iommu_table_dart.it_ops = &iommu_dart_ops;
	अगर (!iommu_init_table(&iommu_table_dart, -1, 0, 0))
		panic("Failed to initialize iommu table");

	/* Reserve the last page of the DART to aव्योम possible prefetch
	 * past the DART mapped area
	 */
	set_bit(iommu_table_dart.it_size - 1, iommu_table_dart.it_map);
पूर्ण

अटल व्योम pci_dma_bus_setup_dart(काष्ठा pci_bus *bus)
अणु
	अगर (!iommu_table_dart_inited) अणु
		iommu_table_dart_inited = 1;
		iommu_table_dart_setup();
	पूर्ण
पूर्ण

अटल bool dart_device_on_pcie(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = of_node_get(dev->of_node);

	जबतक(np) अणु
		अगर (of_device_is_compatible(np, "U4-pcie") ||
		    of_device_is_compatible(np, "u4-pcie")) अणु
			of_node_put(np);
			वापस true;
		पूर्ण
		np = of_get_next_parent(np);
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम pci_dma_dev_setup_dart(काष्ठा pci_dev *dev)
अणु
	अगर (dart_is_u4 && dart_device_on_pcie(&dev->dev))
		dev->dev.archdata.dma_offset = DART_U4_BYPASS_BASE;
	set_iommu_table_base(&dev->dev, &iommu_table_dart);
पूर्ण

अटल bool iommu_bypass_supported_dart(काष्ठा pci_dev *dev, u64 mask)
अणु
	वापस dart_is_u4 &&
		dart_device_on_pcie(&dev->dev) &&
		mask >= DMA_BIT_MASK(40);
पूर्ण

व्योम __init iommu_init_early_dart(काष्ठा pci_controller_ops *controller_ops)
अणु
	काष्ठा device_node *dn;

	/* Find the DART in the device-tree */
	dn = of_find_compatible_node(शून्य, "dart", "u3-dart");
	अगर (dn == शून्य) अणु
		dn = of_find_compatible_node(शून्य, "dart", "u4-dart");
		अगर (dn == शून्य)
			वापस;	/* use शेष direct_dma_ops */
		dart_is_u4 = 1;
	पूर्ण

	/* Initialize the DART HW */
	अगर (dart_init(dn) != 0)
		वापस;

	/*
	 * U4 supports a DART bypass, we use it क्रम 64-bit capable devices to
	 * improve perक्रमmance.  However, that only works क्रम devices connected
	 * to the U4 own PCIe पूर्णांकerface, not bridged through hypertransport.
	 * We need the device to support at least 40 bits of addresses.
	 */
	controller_ops->dma_dev_setup = pci_dma_dev_setup_dart;
	controller_ops->dma_bus_setup = pci_dma_bus_setup_dart;
	controller_ops->iommu_bypass_supported = iommu_bypass_supported_dart;

	/* Setup pci_dma ops */
	set_pci_dma_ops(&dma_iommu_ops);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम iommu_dart_restore(व्योम)
अणु
	dart_cache_sync(dart_tablebase, dart_tablesize / माप(u32));
	dart_tlb_invalidate_all();
पूर्ण

अटल पूर्णांक __init iommu_init_late_dart(व्योम)
अणु
	अगर (!dart_tablebase)
		वापस 0;

	ppc_md.iommu_restore = iommu_dart_restore;

	वापस 0;
पूर्ण

late_initcall(iommu_init_late_dart);
#पूर्ण_अगर /* CONFIG_PM */
