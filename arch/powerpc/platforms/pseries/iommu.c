<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2001 Mike Corrigan & Dave Engebretsen, IBM Corporation
 *
 * Reग_लिखो, cleanup:
 *
 * Copyright (C) 2004 Olof Johansson <olof@lixom.net>, IBM Corporation
 * Copyright (C) 2006 Olof Johansson <olof@lixom.net>
 *
 * Dynamic DMA mapping support, pSeries-specअगरic parts, both SMP and LPAR.
 */

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/crash_dump.h>
#समावेश <linux/memory.h>
#समावेश <linux/of.h>
#समावेश <linux/iommu.h>
#समावेश <linux/rculist.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/pci-bridge.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/ppc-pci.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/plpar_wrappers.h>

#समावेश "pseries.h"

क्रमागत अणु
	DDW_QUERY_PE_DMA_WIN  = 0,
	DDW_CREATE_PE_DMA_WIN = 1,
	DDW_REMOVE_PE_DMA_WIN = 2,

	DDW_APPLICABLE_SIZE
पूर्ण;

क्रमागत अणु
	DDW_EXT_SIZE = 0,
	DDW_EXT_RESET_DMA_WIN = 1,
	DDW_EXT_QUERY_OUT_SIZE = 2
पूर्ण;

अटल काष्ठा iommu_table_group *iommu_pseries_alloc_group(पूर्णांक node)
अणु
	काष्ठा iommu_table_group *table_group;
	काष्ठा iommu_table *tbl;

	table_group = kzalloc_node(माप(काष्ठा iommu_table_group), GFP_KERNEL,
			   node);
	अगर (!table_group)
		वापस शून्य;

	tbl = kzalloc_node(माप(काष्ठा iommu_table), GFP_KERNEL, node);
	अगर (!tbl)
		जाओ मुक्त_group;

	INIT_LIST_HEAD_RCU(&tbl->it_group_list);
	kref_init(&tbl->it_kref);

	table_group->tables[0] = tbl;

	वापस table_group;

मुक्त_group:
	kमुक्त(table_group);
	वापस शून्य;
पूर्ण

अटल व्योम iommu_pseries_मुक्त_group(काष्ठा iommu_table_group *table_group,
		स्थिर अक्षर *node_name)
अणु
	काष्ठा iommu_table *tbl;

	अगर (!table_group)
		वापस;

	tbl = table_group->tables[0];
#अगर_घोषित CONFIG_IOMMU_API
	अगर (table_group->group) अणु
		iommu_group_put(table_group->group);
		BUG_ON(table_group->group);
	पूर्ण
#पूर्ण_अगर
	iommu_tce_table_put(tbl);

	kमुक्त(table_group);
पूर्ण

अटल पूर्णांक tce_build_pSeries(काष्ठा iommu_table *tbl, दीर्घ index,
			      दीर्घ npages, अचिन्हित दीर्घ uaddr,
			      क्रमागत dma_data_direction direction,
			      अचिन्हित दीर्घ attrs)
अणु
	u64 proto_tce;
	__be64 *tcep;
	u64 rpn;

	proto_tce = TCE_PCI_READ; // Read allowed

	अगर (direction != DMA_TO_DEVICE)
		proto_tce |= TCE_PCI_WRITE;

	tcep = ((__be64 *)tbl->it_base) + index;

	जबतक (npages--) अणु
		/* can't move this out since we might cross MEMBLOCK boundary */
		rpn = __pa(uaddr) >> TCE_SHIFT;
		*tcep = cpu_to_be64(proto_tce | (rpn & TCE_RPN_MASK) << TCE_RPN_SHIFT);

		uaddr += TCE_PAGE_SIZE;
		tcep++;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम tce_मुक्त_pSeries(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages)
अणु
	__be64 *tcep;

	tcep = ((__be64 *)tbl->it_base) + index;

	जबतक (npages--)
		*(tcep++) = 0;
पूर्ण

अटल अचिन्हित दीर्घ tce_get_pseries(काष्ठा iommu_table *tbl, दीर्घ index)
अणु
	__be64 *tcep;

	tcep = ((__be64 *)tbl->it_base) + index;

	वापस be64_to_cpu(*tcep);
पूर्ण

अटल व्योम tce_मुक्त_pSeriesLP(अचिन्हित दीर्घ liobn, दीर्घ, दीर्घ);
अटल व्योम tce_मुक्तmulti_pSeriesLP(काष्ठा iommu_table*, दीर्घ, दीर्घ);

अटल पूर्णांक tce_build_pSeriesLP(अचिन्हित दीर्घ liobn, दीर्घ tcक्रमागत, दीर्घ tceshअगरt,
				दीर्घ npages, अचिन्हित दीर्घ uaddr,
				क्रमागत dma_data_direction direction,
				अचिन्हित दीर्घ attrs)
अणु
	u64 rc = 0;
	u64 proto_tce, tce;
	u64 rpn;
	पूर्णांक ret = 0;
	दीर्घ tcक्रमागत_start = tcक्रमागत, npages_start = npages;

	rpn = __pa(uaddr) >> tceshअगरt;
	proto_tce = TCE_PCI_READ;
	अगर (direction != DMA_TO_DEVICE)
		proto_tce |= TCE_PCI_WRITE;

	जबतक (npages--) अणु
		tce = proto_tce | (rpn & TCE_RPN_MASK) << tceshअगरt;
		rc = plpar_tce_put((u64)liobn, (u64)tcक्रमागत << tceshअगरt, tce);

		अगर (unlikely(rc == H_NOT_ENOUGH_RESOURCES)) अणु
			ret = (पूर्णांक)rc;
			tce_मुक्त_pSeriesLP(liobn, tcक्रमागत_start,
			                   (npages_start - (npages + 1)));
			अवरोध;
		पूर्ण

		अगर (rc && prपूर्णांकk_ratelimit()) अणु
			prपूर्णांकk("tce_build_pSeriesLP: plpar_tce_put failed. rc=%lld\n", rc);
			prपूर्णांकk("\tindex   = 0x%llx\n", (u64)liobn);
			prपूर्णांकk("\ttcenum  = 0x%llx\n", (u64)tcक्रमागत);
			prपूर्णांकk("\ttce val = 0x%llx\n", tce );
			dump_stack();
		पूर्ण

		tcक्रमागत++;
		rpn++;
	पूर्ण
	वापस ret;
पूर्ण

अटल DEFINE_PER_CPU(__be64 *, tce_page);

अटल पूर्णांक tce_buildmulti_pSeriesLP(काष्ठा iommu_table *tbl, दीर्घ tcक्रमागत,
				     दीर्घ npages, अचिन्हित दीर्घ uaddr,
				     क्रमागत dma_data_direction direction,
				     अचिन्हित दीर्घ attrs)
अणु
	u64 rc = 0;
	u64 proto_tce;
	__be64 *tcep;
	u64 rpn;
	दीर्घ l, limit;
	दीर्घ tcक्रमागत_start = tcक्रमागत, npages_start = npages;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	अगर ((npages == 1) || !firmware_has_feature(FW_FEATURE_PUT_TCE_IND)) अणु
		वापस tce_build_pSeriesLP(tbl->it_index, tcक्रमागत,
					   tbl->it_page_shअगरt, npages, uaddr,
		                           direction, attrs);
	पूर्ण

	local_irq_save(flags);	/* to protect tcep and the page behind it */

	tcep = __this_cpu_पढ़ो(tce_page);

	/* This is safe to करो since पूर्णांकerrupts are off when we're called
	 * from iommu_allocअणु,_sgपूर्ण()
	 */
	अगर (!tcep) अणु
		tcep = (__be64 *)__get_मुक्त_page(GFP_ATOMIC);
		/* If allocation fails, fall back to the loop implementation */
		अगर (!tcep) अणु
			local_irq_restore(flags);
			वापस tce_build_pSeriesLP(tbl->it_index, tcक्रमागत,
					tbl->it_page_shअगरt,
					npages, uaddr, direction, attrs);
		पूर्ण
		__this_cpu_ग_लिखो(tce_page, tcep);
	पूर्ण

	rpn = __pa(uaddr) >> TCE_SHIFT;
	proto_tce = TCE_PCI_READ;
	अगर (direction != DMA_TO_DEVICE)
		proto_tce |= TCE_PCI_WRITE;

	/* We can map max one pageful of TCEs at a समय */
	करो अणु
		/*
		 * Set up the page with TCE data, looping through and setting
		 * the values.
		 */
		limit = min_t(दीर्घ, npages, 4096/TCE_ENTRY_SIZE);

		क्रम (l = 0; l < limit; l++) अणु
			tcep[l] = cpu_to_be64(proto_tce | (rpn & TCE_RPN_MASK) << TCE_RPN_SHIFT);
			rpn++;
		पूर्ण

		rc = plpar_tce_put_indirect((u64)tbl->it_index,
					    (u64)tcक्रमागत << 12,
					    (u64)__pa(tcep),
					    limit);

		npages -= limit;
		tcक्रमागत += limit;
	पूर्ण जबतक (npages > 0 && !rc);

	local_irq_restore(flags);

	अगर (unlikely(rc == H_NOT_ENOUGH_RESOURCES)) अणु
		ret = (पूर्णांक)rc;
		tce_मुक्तmulti_pSeriesLP(tbl, tcक्रमागत_start,
		                        (npages_start - (npages + limit)));
		वापस ret;
	पूर्ण

	अगर (rc && prपूर्णांकk_ratelimit()) अणु
		prपूर्णांकk("tce_buildmulti_pSeriesLP: plpar_tce_put failed. rc=%lld\n", rc);
		prपूर्णांकk("\tindex   = 0x%llx\n", (u64)tbl->it_index);
		prपूर्णांकk("\tnpages  = 0x%llx\n", (u64)npages);
		prपूर्णांकk("\ttce[0] val = 0x%llx\n", tcep[0]);
		dump_stack();
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम tce_मुक्त_pSeriesLP(अचिन्हित दीर्घ liobn, दीर्घ tcक्रमागत, दीर्घ npages)
अणु
	u64 rc;

	जबतक (npages--) अणु
		rc = plpar_tce_put((u64)liobn, (u64)tcक्रमागत << 12, 0);

		अगर (rc && prपूर्णांकk_ratelimit()) अणु
			prपूर्णांकk("tce_free_pSeriesLP: plpar_tce_put failed. rc=%lld\n", rc);
			prपूर्णांकk("\tindex   = 0x%llx\n", (u64)liobn);
			prपूर्णांकk("\ttcenum  = 0x%llx\n", (u64)tcक्रमागत);
			dump_stack();
		पूर्ण

		tcक्रमागत++;
	पूर्ण
पूर्ण


अटल व्योम tce_मुक्तmulti_pSeriesLP(काष्ठा iommu_table *tbl, दीर्घ tcक्रमागत, दीर्घ npages)
अणु
	u64 rc;

	अगर (!firmware_has_feature(FW_FEATURE_STUFF_TCE))
		वापस tce_मुक्त_pSeriesLP(tbl->it_index, tcक्रमागत, npages);

	rc = plpar_tce_stuff((u64)tbl->it_index, (u64)tcक्रमागत << 12, 0, npages);

	अगर (rc && prपूर्णांकk_ratelimit()) अणु
		prपूर्णांकk("tce_freemulti_pSeriesLP: plpar_tce_stuff failed\n");
		prपूर्णांकk("\trc      = %lld\n", rc);
		prपूर्णांकk("\tindex   = 0x%llx\n", (u64)tbl->it_index);
		prपूर्णांकk("\tnpages  = 0x%llx\n", (u64)npages);
		dump_stack();
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ tce_get_pSeriesLP(काष्ठा iommu_table *tbl, दीर्घ tcक्रमागत)
अणु
	u64 rc;
	अचिन्हित दीर्घ tce_ret;

	rc = plpar_tce_get((u64)tbl->it_index, (u64)tcक्रमागत << 12, &tce_ret);

	अगर (rc && prपूर्णांकk_ratelimit()) अणु
		prपूर्णांकk("tce_get_pSeriesLP: plpar_tce_get failed. rc=%lld\n", rc);
		prपूर्णांकk("\tindex   = 0x%llx\n", (u64)tbl->it_index);
		prपूर्णांकk("\ttcenum  = 0x%llx\n", (u64)tcक्रमागत);
		dump_stack();
	पूर्ण

	वापस tce_ret;
पूर्ण

/* this is compatible with cells क्रम the device tree property */
काष्ठा dynamic_dma_winकरोw_prop अणु
	__be32	liobn;		/* tce table number */
	__be64	dma_base;	/* address hi,lo */
	__be32	tce_shअगरt;	/* ilog2(tce_page_size) */
	__be32	winकरोw_shअगरt;	/* ilog2(tce_winकरोw_size) */
पूर्ण;

काष्ठा direct_winकरोw अणु
	काष्ठा device_node *device;
	स्थिर काष्ठा dynamic_dma_winकरोw_prop *prop;
	काष्ठा list_head list;
पूर्ण;

/* Dynamic DMA Winकरोw support */
काष्ठा ddw_query_response अणु
	u32 winकरोws_available;
	u64 largest_available_block;
	u32 page_size;
	u32 migration_capable;
पूर्ण;

काष्ठा ddw_create_response अणु
	u32 liobn;
	u32 addr_hi;
	u32 addr_lo;
पूर्ण;

अटल LIST_HEAD(direct_winकरोw_list);
/* prevents races between memory on/offline and winकरोw creation */
अटल DEFINE_SPINLOCK(direct_winकरोw_list_lock);
/* protects initializing winकरोw twice क्रम same device */
अटल DEFINE_MUTEX(direct_winकरोw_init_mutex);
#घोषणा सूचीECT64_PROPNAME "linux,direct64-ddr-window-info"

अटल पूर्णांक tce_clearrange_multi_pSeriesLP(अचिन्हित दीर्घ start_pfn,
					अचिन्हित दीर्घ num_pfn, स्थिर व्योम *arg)
अणु
	स्थिर काष्ठा dynamic_dma_winकरोw_prop *maprange = arg;
	पूर्णांक rc;
	u64 tce_size, num_tce, dma_offset, next;
	u32 tce_shअगरt;
	दीर्घ limit;

	tce_shअगरt = be32_to_cpu(maprange->tce_shअगरt);
	tce_size = 1ULL << tce_shअगरt;
	next = start_pfn << PAGE_SHIFT;
	num_tce = num_pfn << PAGE_SHIFT;

	/* round back to the beginning of the tce page size */
	num_tce += next & (tce_size - 1);
	next &= ~(tce_size - 1);

	/* covert to number of tces */
	num_tce |= tce_size - 1;
	num_tce >>= tce_shअगरt;

	करो अणु
		/*
		 * Set up the page with TCE data, looping through and setting
		 * the values.
		 */
		limit = min_t(दीर्घ, num_tce, 512);
		dma_offset = next + be64_to_cpu(maprange->dma_base);

		rc = plpar_tce_stuff((u64)be32_to_cpu(maprange->liobn),
					     dma_offset,
					     0, limit);
		next += limit * tce_size;
		num_tce -= limit;
	पूर्ण जबतक (num_tce > 0 && !rc);

	वापस rc;
पूर्ण

अटल पूर्णांक tce_setrange_multi_pSeriesLP(अचिन्हित दीर्घ start_pfn,
					अचिन्हित दीर्घ num_pfn, स्थिर व्योम *arg)
अणु
	स्थिर काष्ठा dynamic_dma_winकरोw_prop *maprange = arg;
	u64 tce_size, num_tce, dma_offset, next, proto_tce, liobn;
	__be64 *tcep;
	u32 tce_shअगरt;
	u64 rc = 0;
	दीर्घ l, limit;

	अगर (!firmware_has_feature(FW_FEATURE_PUT_TCE_IND)) अणु
		अचिन्हित दीर्घ tceshअगरt = be32_to_cpu(maprange->tce_shअगरt);
		अचिन्हित दीर्घ dmastart = (start_pfn << PAGE_SHIFT) +
				be64_to_cpu(maprange->dma_base);
		अचिन्हित दीर्घ tcक्रमागत = dmastart >> tceshअगरt;
		अचिन्हित दीर्घ npages = num_pfn << PAGE_SHIFT >> tceshअगरt;
		व्योम *uaddr = __va(start_pfn << PAGE_SHIFT);

		वापस tce_build_pSeriesLP(be32_to_cpu(maprange->liobn),
				tcक्रमागत, tceshअगरt, npages, (अचिन्हित दीर्घ) uaddr,
				DMA_BIसूचीECTIONAL, 0);
	पूर्ण

	local_irq_disable();	/* to protect tcep and the page behind it */
	tcep = __this_cpu_पढ़ो(tce_page);

	अगर (!tcep) अणु
		tcep = (__be64 *)__get_मुक्त_page(GFP_ATOMIC);
		अगर (!tcep) अणु
			local_irq_enable();
			वापस -ENOMEM;
		पूर्ण
		__this_cpu_ग_लिखो(tce_page, tcep);
	पूर्ण

	proto_tce = TCE_PCI_READ | TCE_PCI_WRITE;

	liobn = (u64)be32_to_cpu(maprange->liobn);
	tce_shअगरt = be32_to_cpu(maprange->tce_shअगरt);
	tce_size = 1ULL << tce_shअगरt;
	next = start_pfn << PAGE_SHIFT;
	num_tce = num_pfn << PAGE_SHIFT;

	/* round back to the beginning of the tce page size */
	num_tce += next & (tce_size - 1);
	next &= ~(tce_size - 1);

	/* covert to number of tces */
	num_tce |= tce_size - 1;
	num_tce >>= tce_shअगरt;

	/* We can map max one pageful of TCEs at a समय */
	करो अणु
		/*
		 * Set up the page with TCE data, looping through and setting
		 * the values.
		 */
		limit = min_t(दीर्घ, num_tce, 4096/TCE_ENTRY_SIZE);
		dma_offset = next + be64_to_cpu(maprange->dma_base);

		क्रम (l = 0; l < limit; l++) अणु
			tcep[l] = cpu_to_be64(proto_tce | next);
			next += tce_size;
		पूर्ण

		rc = plpar_tce_put_indirect(liobn,
					    dma_offset,
					    (u64)__pa(tcep),
					    limit);

		num_tce -= limit;
	पूर्ण जबतक (num_tce > 0 && !rc);

	/* error cleanup: caller will clear whole range */

	local_irq_enable();
	वापस rc;
पूर्ण

अटल पूर्णांक tce_setrange_multi_pSeriesLP_walk(अचिन्हित दीर्घ start_pfn,
		अचिन्हित दीर्घ num_pfn, व्योम *arg)
अणु
	वापस tce_setrange_multi_pSeriesLP(start_pfn, num_pfn, arg);
पूर्ण

अटल व्योम iommu_table_setparms(काष्ठा pci_controller *phb,
				 काष्ठा device_node *dn,
				 काष्ठा iommu_table *tbl)
अणु
	काष्ठा device_node *node;
	स्थिर अचिन्हित दीर्घ *basep;
	स्थिर u32 *sizep;

	node = phb->dn;

	basep = of_get_property(node, "linux,tce-base", शून्य);
	sizep = of_get_property(node, "linux,tce-size", शून्य);
	अगर (basep == शून्य || sizep == शून्य) अणु
		prपूर्णांकk(KERN_ERR "PCI_DMA: iommu_table_setparms: %pOF has "
				"missing tce entries !\n", dn);
		वापस;
	पूर्ण

	tbl->it_base = (अचिन्हित दीर्घ)__va(*basep);

	अगर (!is_kdump_kernel())
		स_रखो((व्योम *)tbl->it_base, 0, *sizep);

	tbl->it_busno = phb->bus->number;
	tbl->it_page_shअगरt = IOMMU_PAGE_SHIFT_4K;

	/* Units of tce entries */
	tbl->it_offset = phb->dma_winकरोw_base_cur >> tbl->it_page_shअगरt;

	/* Test अगर we are going over 2GB of DMA space */
	अगर (phb->dma_winकरोw_base_cur + phb->dma_winकरोw_size > 0x80000000ul) अणु
		udbg_म_लिखो("PCI_DMA: Unexpected number of IOAs under this PHB.\n");
		panic("PCI_DMA: Unexpected number of IOAs under this PHB.\n");
	पूर्ण

	phb->dma_winकरोw_base_cur += phb->dma_winकरोw_size;

	/* Set the tce table size - measured in entries */
	tbl->it_size = phb->dma_winकरोw_size >> tbl->it_page_shअगरt;

	tbl->it_index = 0;
	tbl->it_blocksize = 16;
	tbl->it_type = TCE_PCI;
पूर्ण

/*
 * iommu_table_setparms_lpar
 *
 * Function: On pSeries LPAR प्रणालीs, वापस TCE table info, given a pci bus.
 */
अटल व्योम iommu_table_setparms_lpar(काष्ठा pci_controller *phb,
				      काष्ठा device_node *dn,
				      काष्ठा iommu_table *tbl,
				      काष्ठा iommu_table_group *table_group,
				      स्थिर __be32 *dma_winकरोw)
अणु
	अचिन्हित दीर्घ offset, size;

	of_parse_dma_winकरोw(dn, dma_winकरोw, &tbl->it_index, &offset, &size);

	tbl->it_busno = phb->bus->number;
	tbl->it_page_shअगरt = IOMMU_PAGE_SHIFT_4K;
	tbl->it_base   = 0;
	tbl->it_blocksize  = 16;
	tbl->it_type = TCE_PCI;
	tbl->it_offset = offset >> tbl->it_page_shअगरt;
	tbl->it_size = size >> tbl->it_page_shअगरt;

	table_group->tce32_start = offset;
	table_group->tce32_size = size;
पूर्ण

काष्ठा iommu_table_ops iommu_table_pseries_ops = अणु
	.set = tce_build_pSeries,
	.clear = tce_मुक्त_pSeries,
	.get = tce_get_pseries
पूर्ण;

अटल व्योम pci_dma_bus_setup_pSeries(काष्ठा pci_bus *bus)
अणु
	काष्ठा device_node *dn;
	काष्ठा iommu_table *tbl;
	काष्ठा device_node *isa_dn, *isa_dn_orig;
	काष्ठा device_node *पंचांगp;
	काष्ठा pci_dn *pci;
	पूर्णांक children;

	dn = pci_bus_to_OF_node(bus);

	pr_debug("pci_dma_bus_setup_pSeries: setting up bus %pOF\n", dn);

	अगर (bus->self) अणु
		/* This is not a root bus, any setup will be करोne क्रम the
		 * device-side of the bridge in iommu_dev_setup_pSeries().
		 */
		वापस;
	पूर्ण
	pci = PCI_DN(dn);

	/* Check अगर the ISA bus on the प्रणाली is under
	 * this PHB.
	 */
	isa_dn = isa_dn_orig = of_find_node_by_type(शून्य, "isa");

	जबतक (isa_dn && isa_dn != dn)
		isa_dn = isa_dn->parent;

	of_node_put(isa_dn_orig);

	/* Count number of direct PCI children of the PHB. */
	क्रम (children = 0, पंचांगp = dn->child; पंचांगp; पंचांगp = पंचांगp->sibling)
		children++;

	pr_debug("Children: %d\n", children);

	/* Calculate amount of DMA winकरोw per slot. Each winकरोw must be
	 * a घातer of two (due to pci_alloc_consistent requirements).
	 *
	 * Keep 256MB aside क्रम PHBs with ISA.
	 */

	अगर (!isa_dn) अणु
		/* No ISA/IDE - just set winकरोw size and वापस */
		pci->phb->dma_winकरोw_size = 0x80000000ul; /* To be भागided */

		जबतक (pci->phb->dma_winकरोw_size * children > 0x80000000ul)
			pci->phb->dma_winकरोw_size >>= 1;
		pr_debug("No ISA/IDE, window size is 0x%llx\n",
			 pci->phb->dma_winकरोw_size);
		pci->phb->dma_winकरोw_base_cur = 0;

		वापस;
	पूर्ण

	/* If we have ISA, then we probably have an IDE
	 * controller too. Allocate a 128MB table but
	 * skip the first 128MB to aव्योम stepping on ISA
	 * space.
	 */
	pci->phb->dma_winकरोw_size = 0x8000000ul;
	pci->phb->dma_winकरोw_base_cur = 0x8000000ul;

	pci->table_group = iommu_pseries_alloc_group(pci->phb->node);
	tbl = pci->table_group->tables[0];

	iommu_table_setparms(pci->phb, dn, tbl);
	tbl->it_ops = &iommu_table_pseries_ops;
	अगर (!iommu_init_table(tbl, pci->phb->node, 0, 0))
		panic("Failed to initialize iommu table");

	/* Divide the rest (1.75GB) among the children */
	pci->phb->dma_winकरोw_size = 0x80000000ul;
	जबतक (pci->phb->dma_winकरोw_size * children > 0x70000000ul)
		pci->phb->dma_winकरोw_size >>= 1;

	pr_debug("ISA/IDE, window size is 0x%llx\n", pci->phb->dma_winकरोw_size);
पूर्ण

#अगर_घोषित CONFIG_IOMMU_API
अटल पूर्णांक tce_exchange_pseries(काष्ठा iommu_table *tbl, दीर्घ index, अचिन्हित
				दीर्घ *tce, क्रमागत dma_data_direction *direction,
				bool realmode)
अणु
	दीर्घ rc;
	अचिन्हित दीर्घ ioba = (अचिन्हित दीर्घ) index << tbl->it_page_shअगरt;
	अचिन्हित दीर्घ flags, oldtce = 0;
	u64 proto_tce = iommu_direction_to_tce_perm(*direction);
	अचिन्हित दीर्घ newtce = *tce | proto_tce;

	spin_lock_irqsave(&tbl->large_pool.lock, flags);

	rc = plpar_tce_get((u64)tbl->it_index, ioba, &oldtce);
	अगर (!rc)
		rc = plpar_tce_put((u64)tbl->it_index, ioba, newtce);

	अगर (!rc) अणु
		*direction = iommu_tce_direction(oldtce);
		*tce = oldtce & ~(TCE_PCI_READ | TCE_PCI_WRITE);
	पूर्ण

	spin_unlock_irqrestore(&tbl->large_pool.lock, flags);

	वापस rc;
पूर्ण
#पूर्ण_अगर

काष्ठा iommu_table_ops iommu_table_lpar_multi_ops = अणु
	.set = tce_buildmulti_pSeriesLP,
#अगर_घोषित CONFIG_IOMMU_API
	.xchg_no_समाप्त = tce_exchange_pseries,
#पूर्ण_अगर
	.clear = tce_मुक्तmulti_pSeriesLP,
	.get = tce_get_pSeriesLP
पूर्ण;

अटल व्योम pci_dma_bus_setup_pSeriesLP(काष्ठा pci_bus *bus)
अणु
	काष्ठा iommu_table *tbl;
	काष्ठा device_node *dn, *pdn;
	काष्ठा pci_dn *ppci;
	स्थिर __be32 *dma_winकरोw = शून्य;

	dn = pci_bus_to_OF_node(bus);

	pr_debug("pci_dma_bus_setup_pSeriesLP: setting up bus %pOF\n",
		 dn);

	/* Find nearest ibm,dma-winकरोw, walking up the device tree */
	क्रम (pdn = dn; pdn != शून्य; pdn = pdn->parent) अणु
		dma_winकरोw = of_get_property(pdn, "ibm,dma-window", शून्य);
		अगर (dma_winकरोw != शून्य)
			अवरोध;
	पूर्ण

	अगर (dma_winकरोw == शून्य) अणु
		pr_debug("  no ibm,dma-window property !\n");
		वापस;
	पूर्ण

	ppci = PCI_DN(pdn);

	pr_debug("  parent is %pOF, iommu_table: 0x%p\n",
		 pdn, ppci->table_group);

	अगर (!ppci->table_group) अणु
		ppci->table_group = iommu_pseries_alloc_group(ppci->phb->node);
		tbl = ppci->table_group->tables[0];
		iommu_table_setparms_lpar(ppci->phb, pdn, tbl,
				ppci->table_group, dma_winकरोw);
		tbl->it_ops = &iommu_table_lpar_multi_ops;
		अगर (!iommu_init_table(tbl, ppci->phb->node, 0, 0))
			panic("Failed to initialize iommu table");
		iommu_रेजिस्टर_group(ppci->table_group,
				pci_करोमुख्य_nr(bus), 0);
		pr_debug("  created table: %p\n", ppci->table_group);
	पूर्ण
पूर्ण


अटल व्योम pci_dma_dev_setup_pSeries(काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node *dn;
	काष्ठा iommu_table *tbl;

	pr_debug("pci_dma_dev_setup_pSeries: %s\n", pci_name(dev));

	dn = dev->dev.of_node;

	/* If we're the direct child of a root bus, then we need to allocate
	 * an iommu table ourselves. The bus setup code should have setup
	 * the winकरोw sizes alपढ़ोy.
	 */
	अगर (!dev->bus->self) अणु
		काष्ठा pci_controller *phb = PCI_DN(dn)->phb;

		pr_debug(" --> first child, no bridge. Allocating iommu table.\n");
		PCI_DN(dn)->table_group = iommu_pseries_alloc_group(phb->node);
		tbl = PCI_DN(dn)->table_group->tables[0];
		iommu_table_setparms(phb, dn, tbl);
		tbl->it_ops = &iommu_table_pseries_ops;
		अगर (!iommu_init_table(tbl, phb->node, 0, 0))
			panic("Failed to initialize iommu table");

		set_iommu_table_base(&dev->dev, tbl);
		वापस;
	पूर्ण

	/* If this device is further करोwn the bus tree, search upwards until
	 * an alपढ़ोy allocated iommu table is found and use that.
	 */

	जबतक (dn && PCI_DN(dn) && PCI_DN(dn)->table_group == शून्य)
		dn = dn->parent;

	अगर (dn && PCI_DN(dn))
		set_iommu_table_base(&dev->dev,
				PCI_DN(dn)->table_group->tables[0]);
	अन्यथा
		prपूर्णांकk(KERN_WARNING "iommu: Device %s has no iommu table\n",
		       pci_name(dev));
पूर्ण

अटल पूर्णांक __पढ़ो_mostly disable_ddw;

अटल पूर्णांक __init disable_ddw_setup(अक्षर *str)
अणु
	disable_ddw = 1;
	prपूर्णांकk(KERN_INFO "ppc iommu: disabling ddw.\n");

	वापस 0;
पूर्ण

early_param("disable_ddw", disable_ddw_setup);

अटल व्योम हटाओ_dma_winकरोw(काष्ठा device_node *np, u32 *ddw_avail,
			      काष्ठा property *win)
अणु
	काष्ठा dynamic_dma_winकरोw_prop *dwp;
	u64 liobn;
	पूर्णांक ret;

	dwp = win->value;
	liobn = (u64)be32_to_cpu(dwp->liobn);

	/* clear the whole winकरोw, note the arg is in kernel pages */
	ret = tce_clearrange_multi_pSeriesLP(0,
		1ULL << (be32_to_cpu(dwp->winकरोw_shअगरt) - PAGE_SHIFT), dwp);
	अगर (ret)
		pr_warn("%pOF failed to clear tces in window.\n",
			np);
	अन्यथा
		pr_debug("%pOF successfully cleared tces in window.\n",
			 np);

	ret = rtas_call(ddw_avail[DDW_REMOVE_PE_DMA_WIN], 1, 1, शून्य, liobn);
	अगर (ret)
		pr_warn("%pOF: failed to remove direct window: rtas returned "
			"%d to ibm,remove-pe-dma-window(%x) %llx\n",
			np, ret, ddw_avail[DDW_REMOVE_PE_DMA_WIN], liobn);
	अन्यथा
		pr_debug("%pOF: successfully removed direct window: rtas returned "
			"%d to ibm,remove-pe-dma-window(%x) %llx\n",
			np, ret, ddw_avail[DDW_REMOVE_PE_DMA_WIN], liobn);
पूर्ण

अटल व्योम हटाओ_ddw(काष्ठा device_node *np, bool हटाओ_prop)
अणु
	काष्ठा property *win;
	u32 ddw_avail[DDW_APPLICABLE_SIZE];
	पूर्णांक ret = 0;

	ret = of_property_पढ़ो_u32_array(np, "ibm,ddw-applicable",
					 &ddw_avail[0], DDW_APPLICABLE_SIZE);
	अगर (ret)
		वापस;

	win = of_find_property(np, सूचीECT64_PROPNAME, शून्य);
	अगर (!win)
		वापस;

	अगर (win->length >= माप(काष्ठा dynamic_dma_winकरोw_prop))
		हटाओ_dma_winकरोw(np, ddw_avail, win);

	अगर (!हटाओ_prop)
		वापस;

	ret = of_हटाओ_property(np, win);
	अगर (ret)
		pr_warn("%pOF: failed to remove direct window property: %d\n",
			np, ret);
पूर्ण

अटल u64 find_existing_ddw(काष्ठा device_node *pdn, पूर्णांक *winकरोw_shअगरt)
अणु
	काष्ठा direct_winकरोw *winकरोw;
	स्थिर काष्ठा dynamic_dma_winकरोw_prop *direct64;
	u64 dma_addr = 0;

	spin_lock(&direct_winकरोw_list_lock);
	/* check अगर we alपढ़ोy created a winकरोw and dupe that config अगर so */
	list_क्रम_each_entry(winकरोw, &direct_winकरोw_list, list) अणु
		अगर (winकरोw->device == pdn) अणु
			direct64 = winकरोw->prop;
			dma_addr = be64_to_cpu(direct64->dma_base);
			*winकरोw_shअगरt = be32_to_cpu(direct64->winकरोw_shअगरt);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&direct_winकरोw_list_lock);

	वापस dma_addr;
पूर्ण

अटल पूर्णांक find_existing_ddw_winकरोws(व्योम)
अणु
	पूर्णांक len;
	काष्ठा device_node *pdn;
	काष्ठा direct_winकरोw *winकरोw;
	स्थिर काष्ठा dynamic_dma_winकरोw_prop *direct64;

	अगर (!firmware_has_feature(FW_FEATURE_LPAR))
		वापस 0;

	क्रम_each_node_with_property(pdn, सूचीECT64_PROPNAME) अणु
		direct64 = of_get_property(pdn, सूचीECT64_PROPNAME, &len);
		अगर (!direct64)
			जारी;

		winकरोw = kzalloc(माप(*winकरोw), GFP_KERNEL);
		अगर (!winकरोw || len < माप(काष्ठा dynamic_dma_winकरोw_prop)) अणु
			kमुक्त(winकरोw);
			हटाओ_ddw(pdn, true);
			जारी;
		पूर्ण

		winकरोw->device = pdn;
		winकरोw->prop = direct64;
		spin_lock(&direct_winकरोw_list_lock);
		list_add(&winकरोw->list, &direct_winकरोw_list);
		spin_unlock(&direct_winकरोw_list_lock);
	पूर्ण

	वापस 0;
पूर्ण
machine_arch_initcall(pseries, find_existing_ddw_winकरोws);

/**
 * ddw_पढ़ो_ext - Get the value of an DDW extension
 * @np:		device node from which the extension value is to be पढ़ो.
 * @extnum:	index number of the extension.
 * @value:	poपूर्णांकer to वापस value, modअगरied when extension is available.
 *
 * Checks अगर "ibm,ddw-extensions" exists क्रम this node, and get the value
 * on index 'extnum'.
 * It can be used only to check अगर a property exists, passing value == शून्य.
 *
 * Returns:
 *	0 अगर extension successfully पढ़ो
 *	-EINVAL अगर the "ibm,ddw-extensions" करोes not exist,
 *	-ENODATA अगर "ibm,ddw-extensions" करोes not have a value, and
 *	-EOVERFLOW अगर "ibm,ddw-extensions" करोes not contain this extension.
 */
अटल अंतरभूत पूर्णांक ddw_पढ़ो_ext(स्थिर काष्ठा device_node *np, पूर्णांक extnum,
			       u32 *value)
अणु
	अटल स्थिर अक्षर propname[] = "ibm,ddw-extensions";
	u32 count;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32_index(np, propname, DDW_EXT_SIZE, &count);
	अगर (ret)
		वापस ret;

	अगर (count < extnum)
		वापस -EOVERFLOW;

	अगर (!value)
		value = &count;

	वापस of_property_पढ़ो_u32_index(np, propname, extnum, value);
पूर्ण

अटल पूर्णांक query_ddw(काष्ठा pci_dev *dev, स्थिर u32 *ddw_avail,
		     काष्ठा ddw_query_response *query,
		     काष्ठा device_node *parent)
अणु
	काष्ठा device_node *dn;
	काष्ठा pci_dn *pdn;
	u32 cfg_addr, ext_query, query_out[5];
	u64 buid;
	पूर्णांक ret, out_sz;

	/*
	 * From LoPAR level 2.8, "ibm,ddw-extensions" index 3 can rule how many
	 * output parameters ibm,query-pe-dma-winकरोws will have, ranging from
	 * 5 to 6.
	 */
	ret = ddw_पढ़ो_ext(parent, DDW_EXT_QUERY_OUT_SIZE, &ext_query);
	अगर (!ret && ext_query == 1)
		out_sz = 6;
	अन्यथा
		out_sz = 5;

	/*
	 * Get the config address and phb buid of the PE winकरोw.
	 * Rely on eeh to retrieve this क्रम us.
	 * Retrieve them from the pci device, not the node with the
	 * dma-winकरोw property
	 */
	dn = pci_device_to_OF_node(dev);
	pdn = PCI_DN(dn);
	buid = pdn->phb->buid;
	cfg_addr = ((pdn->busno << 16) | (pdn->devfn << 8));

	ret = rtas_call(ddw_avail[DDW_QUERY_PE_DMA_WIN], 3, out_sz, query_out,
			cfg_addr, BUID_HI(buid), BUID_LO(buid));
	dev_info(&dev->dev, "ibm,query-pe-dma-windows(%x) %x %x %x returned %d\n",
		 ddw_avail[DDW_QUERY_PE_DMA_WIN], cfg_addr, BUID_HI(buid),
		 BUID_LO(buid), ret);

	चयन (out_sz) अणु
	हाल 5:
		query->winकरोws_available = query_out[0];
		query->largest_available_block = query_out[1];
		query->page_size = query_out[2];
		query->migration_capable = query_out[3];
		अवरोध;
	हाल 6:
		query->winकरोws_available = query_out[0];
		query->largest_available_block = ((u64)query_out[1] << 32) |
						 query_out[2];
		query->page_size = query_out[3];
		query->migration_capable = query_out[4];
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक create_ddw(काष्ठा pci_dev *dev, स्थिर u32 *ddw_avail,
			काष्ठा ddw_create_response *create, पूर्णांक page_shअगरt,
			पूर्णांक winकरोw_shअगरt)
अणु
	काष्ठा device_node *dn;
	काष्ठा pci_dn *pdn;
	u32 cfg_addr;
	u64 buid;
	पूर्णांक ret;

	/*
	 * Get the config address and phb buid of the PE winकरोw.
	 * Rely on eeh to retrieve this क्रम us.
	 * Retrieve them from the pci device, not the node with the
	 * dma-winकरोw property
	 */
	dn = pci_device_to_OF_node(dev);
	pdn = PCI_DN(dn);
	buid = pdn->phb->buid;
	cfg_addr = ((pdn->busno << 16) | (pdn->devfn << 8));

	करो अणु
		/* extra outमाला_दो are LIOBN and dma-addr (hi, lo) */
		ret = rtas_call(ddw_avail[DDW_CREATE_PE_DMA_WIN], 5, 4,
				(u32 *)create, cfg_addr, BUID_HI(buid),
				BUID_LO(buid), page_shअगरt, winकरोw_shअगरt);
	पूर्ण जबतक (rtas_busy_delay(ret));
	dev_info(&dev->dev,
		"ibm,create-pe-dma-window(%x) %x %x %x %x %x returned %d "
		"(liobn = 0x%x starting addr = %x %x)\n",
		 ddw_avail[DDW_CREATE_PE_DMA_WIN], cfg_addr, BUID_HI(buid),
		 BUID_LO(buid), page_shअगरt, winकरोw_shअगरt, ret, create->liobn,
		 create->addr_hi, create->addr_lo);

	वापस ret;
पूर्ण

काष्ठा failed_ddw_pdn अणु
	काष्ठा device_node *pdn;
	काष्ठा list_head list;
पूर्ण;

अटल LIST_HEAD(failed_ddw_pdn_list);

अटल phys_addr_t ddw_memory_hotplug_max(व्योम)
अणु
	phys_addr_t max_addr = memory_hotplug_max();
	काष्ठा device_node *memory;

	/*
	 * The "ibm,pmemory" can appear anywhere in the address space.
	 * Assuming it is still backed by page काष्ठाs, set the upper limit
	 * क्रम the huge DMA winकरोw as MAX_PHYSMEM_BITS.
	 */
	अगर (of_find_node_by_type(शून्य, "ibm,pmemory"))
		वापस (माप(phys_addr_t) * 8 <= MAX_PHYSMEM_BITS) ?
			(phys_addr_t) -1 : (1ULL << MAX_PHYSMEM_BITS);

	क्रम_each_node_by_type(memory, "memory") अणु
		अचिन्हित दीर्घ start, size;
		पूर्णांक n_mem_addr_cells, n_mem_size_cells, len;
		स्थिर __be32 *memcell_buf;

		memcell_buf = of_get_property(memory, "reg", &len);
		अगर (!memcell_buf || len <= 0)
			जारी;

		n_mem_addr_cells = of_n_addr_cells(memory);
		n_mem_size_cells = of_n_size_cells(memory);

		start = of_पढ़ो_number(memcell_buf, n_mem_addr_cells);
		memcell_buf += n_mem_addr_cells;
		size = of_पढ़ो_number(memcell_buf, n_mem_size_cells);
		memcell_buf += n_mem_size_cells;

		max_addr = max_t(phys_addr_t, max_addr, start + size);
	पूर्ण

	वापस max_addr;
पूर्ण

/*
 * Platक्रमms supporting the DDW option starting with LoPAR level 2.7 implement
 * ibm,ddw-extensions, which carries the rtas token क्रम
 * ibm,reset-pe-dma-winकरोws.
 * That rtas-call can be used to restore the शेष DMA winकरोw क्रम the device.
 */
अटल व्योम reset_dma_winकरोw(काष्ठा pci_dev *dev, काष्ठा device_node *par_dn)
अणु
	पूर्णांक ret;
	u32 cfg_addr, reset_dma_win;
	u64 buid;
	काष्ठा device_node *dn;
	काष्ठा pci_dn *pdn;

	ret = ddw_पढ़ो_ext(par_dn, DDW_EXT_RESET_DMA_WIN, &reset_dma_win);
	अगर (ret)
		वापस;

	dn = pci_device_to_OF_node(dev);
	pdn = PCI_DN(dn);
	buid = pdn->phb->buid;
	cfg_addr = (pdn->busno << 16) | (pdn->devfn << 8);

	ret = rtas_call(reset_dma_win, 3, 1, शून्य, cfg_addr, BUID_HI(buid),
			BUID_LO(buid));
	अगर (ret)
		dev_info(&dev->dev,
			 "ibm,reset-pe-dma-windows(%x) %x %x %x returned %d ",
			 reset_dma_win, cfg_addr, BUID_HI(buid), BUID_LO(buid),
			 ret);
पूर्ण

/* Return largest page shअगरt based on "IO Page Sizes" output of ibm,query-pe-dma-winकरोw. */
अटल पूर्णांक iommu_get_page_shअगरt(u32 query_page_size)
अणु
	/* Supported IO page-sizes according to LoPAR */
	स्थिर पूर्णांक shअगरt[] = अणु
		__builtin_ctzll(SZ_4K),   __builtin_ctzll(SZ_64K), __builtin_ctzll(SZ_16M),
		__builtin_ctzll(SZ_32M),  __builtin_ctzll(SZ_64M), __builtin_ctzll(SZ_128M),
		__builtin_ctzll(SZ_256M), __builtin_ctzll(SZ_16G)
	पूर्ण;

	पूर्णांक i = ARRAY_SIZE(shअगरt) - 1;

	/*
	 * On LoPAR, ibm,query-pe-dma-winकरोw outमाला_दो "IO Page Sizes" using a bit field:
	 * - bit 31 means 4k pages are supported,
	 * - bit 30 means 64k pages are supported, and so on.
	 * Larger pagesizes map more memory with the same amount of TCEs, so start probing them.
	 */
	क्रम (; i >= 0 ; i--) अणु
		अगर (query_page_size & (1 << i))
			वापस shअगरt[i];
	पूर्ण

	/* No valid page size found. */
	वापस 0;
पूर्ण

/*
 * If the PE supports dynamic dma winकरोws, and there is space क्रम a table
 * that can map all pages in a linear offset, then setup such a table,
 * and record the dma-offset in the काष्ठा device.
 *
 * dev: the pci device we are checking
 * pdn: the parent pe node with the ibm,dma_winकरोw property
 * Future: also check अगर we can remap the base winकरोw क्रम our base page size
 *
 * वापसs the dma offset क्रम use by the direct mapped DMA code.
 */
अटल u64 enable_ddw(काष्ठा pci_dev *dev, काष्ठा device_node *pdn)
अणु
	पूर्णांक len = 0, ret;
	पूर्णांक max_ram_len = order_base_2(ddw_memory_hotplug_max());
	काष्ठा ddw_query_response query;
	काष्ठा ddw_create_response create;
	पूर्णांक page_shअगरt;
	u64 dma_addr;
	काष्ठा device_node *dn;
	u32 ddw_avail[DDW_APPLICABLE_SIZE];
	काष्ठा direct_winकरोw *winकरोw;
	काष्ठा property *win64;
	काष्ठा dynamic_dma_winकरोw_prop *ddwprop;
	काष्ठा failed_ddw_pdn *fpdn;
	bool शेष_win_हटाओd = false;
	bool pmem_present;

	dn = of_find_node_by_type(शून्य, "ibm,pmemory");
	pmem_present = dn != शून्य;
	of_node_put(dn);

	mutex_lock(&direct_winकरोw_init_mutex);

	dma_addr = find_existing_ddw(pdn, &len);
	अगर (dma_addr != 0)
		जाओ out_unlock;

	/*
	 * If we alपढ़ोy went through this क्रम a previous function of
	 * the same device and failed, we करोn't want to muck with the
	 * DMA winकरोw again, as it will race with in-flight operations
	 * and can lead to EEHs. The above mutex protects access to the
	 * list.
	 */
	list_क्रम_each_entry(fpdn, &failed_ddw_pdn_list, list) अणु
		अगर (fpdn->pdn == pdn)
			जाओ out_unlock;
	पूर्ण

	/*
	 * the ibm,ddw-applicable property holds the tokens क्रम:
	 * ibm,query-pe-dma-winकरोw
	 * ibm,create-pe-dma-winकरोw
	 * ibm,हटाओ-pe-dma-winकरोw
	 * क्रम the given node in that order.
	 * the property is actually in the parent, not the PE
	 */
	ret = of_property_पढ़ो_u32_array(pdn, "ibm,ddw-applicable",
					 &ddw_avail[0], DDW_APPLICABLE_SIZE);
	अगर (ret)
		जाओ out_failed;

       /*
	 * Query अगर there is a second winकरोw of size to map the
	 * whole partition.  Query वापसs number of winकरोws, largest
	 * block asचिन्हित to PE (partition endpoपूर्णांक), and two biपंचांगasks
	 * of page sizes: supported and supported क्रम migrate-dma.
	 */
	dn = pci_device_to_OF_node(dev);
	ret = query_ddw(dev, ddw_avail, &query, pdn);
	अगर (ret != 0)
		जाओ out_failed;

	/*
	 * If there is no winकरोw available, हटाओ the शेष DMA winकरोw,
	 * अगर it's present. This will make all the resources available to the
	 * new DDW winकरोw.
	 * If anything fails after this, we need to restore it, so also check
	 * क्रम extensions presence.
	 */
	अगर (query.winकरोws_available == 0) अणु
		काष्ठा property *शेष_win;
		पूर्णांक reset_win_ext;

		शेष_win = of_find_property(pdn, "ibm,dma-window", शून्य);
		अगर (!शेष_win)
			जाओ out_failed;

		reset_win_ext = ddw_पढ़ो_ext(pdn, DDW_EXT_RESET_DMA_WIN, शून्य);
		अगर (reset_win_ext)
			जाओ out_failed;

		हटाओ_dma_winकरोw(pdn, ddw_avail, शेष_win);
		शेष_win_हटाओd = true;

		/* Query again, to check अगर the winकरोw is available */
		ret = query_ddw(dev, ddw_avail, &query, pdn);
		अगर (ret != 0)
			जाओ out_failed;

		अगर (query.winकरोws_available == 0) अणु
			/* no winकरोws are available क्रम this device. */
			dev_dbg(&dev->dev, "no free dynamic windows");
			जाओ out_failed;
		पूर्ण
	पूर्ण

	page_shअगरt = iommu_get_page_shअगरt(query.page_size);
	अगर (!page_shअगरt) अणु
		dev_dbg(&dev->dev, "no supported direct page size in mask %x",
			  query.page_size);
		जाओ out_failed;
	पूर्ण
	/* verअगरy the winकरोw * number of ptes will map the partition */
	/* check largest block * page size > max memory hotplug addr */
	/*
	 * The "ibm,pmemory" can appear anywhere in the address space.
	 * Assuming it is still backed by page काष्ठाs, try MAX_PHYSMEM_BITS
	 * क्रम the upper limit and fallback to max RAM otherwise but this
	 * disables device::dma_ops_bypass.
	 */
	len = max_ram_len;
	अगर (pmem_present) अणु
		अगर (query.largest_available_block >=
		    (1ULL << (MAX_PHYSMEM_BITS - page_shअगरt)))
			len = MAX_PHYSMEM_BITS;
		अन्यथा
			dev_info(&dev->dev, "Skipping ibm,pmemory");
	पूर्ण

	अगर (query.largest_available_block < (1ULL << (len - page_shअगरt))) अणु
		dev_dbg(&dev->dev,
			"can't map partition max 0x%llx with %llu %llu-sized pages\n",
			1ULL << len,
			query.largest_available_block,
			1ULL << page_shअगरt);
		जाओ out_failed;
	पूर्ण
	win64 = kzalloc(माप(काष्ठा property), GFP_KERNEL);
	अगर (!win64) अणु
		dev_info(&dev->dev,
			"couldn't allocate property for 64bit dma window\n");
		जाओ out_failed;
	पूर्ण
	win64->name = kstrdup(सूचीECT64_PROPNAME, GFP_KERNEL);
	win64->value = ddwprop = kदो_स्मृति(माप(*ddwprop), GFP_KERNEL);
	win64->length = माप(*ddwprop);
	अगर (!win64->name || !win64->value) अणु
		dev_info(&dev->dev,
			"couldn't allocate property name and value\n");
		जाओ out_मुक्त_prop;
	पूर्ण

	ret = create_ddw(dev, ddw_avail, &create, page_shअगरt, len);
	अगर (ret != 0)
		जाओ out_मुक्त_prop;

	ddwprop->liobn = cpu_to_be32(create.liobn);
	ddwprop->dma_base = cpu_to_be64(((u64)create.addr_hi << 32) |
			create.addr_lo);
	ddwprop->tce_shअगरt = cpu_to_be32(page_shअगरt);
	ddwprop->winकरोw_shअगरt = cpu_to_be32(len);

	dev_dbg(&dev->dev, "created tce table LIOBN 0x%x for %pOF\n",
		  create.liobn, dn);

	winकरोw = kzalloc(माप(*winकरोw), GFP_KERNEL);
	अगर (!winकरोw)
		जाओ out_clear_winकरोw;

	ret = walk_प्रणाली_ram_range(0, memblock_end_of_DRAM() >> PAGE_SHIFT,
			win64->value, tce_setrange_multi_pSeriesLP_walk);
	अगर (ret) अणु
		dev_info(&dev->dev, "failed to map direct window for %pOF: %d\n",
			 dn, ret);
		जाओ out_मुक्त_winकरोw;
	पूर्ण

	ret = of_add_property(pdn, win64);
	अगर (ret) अणु
		dev_err(&dev->dev, "unable to add dma window property for %pOF: %d",
			 pdn, ret);
		जाओ out_मुक्त_winकरोw;
	पूर्ण

	winकरोw->device = pdn;
	winकरोw->prop = ddwprop;
	spin_lock(&direct_winकरोw_list_lock);
	list_add(&winकरोw->list, &direct_winकरोw_list);
	spin_unlock(&direct_winकरोw_list_lock);

	dma_addr = be64_to_cpu(ddwprop->dma_base);
	जाओ out_unlock;

out_मुक्त_winकरोw:
	kमुक्त(winकरोw);

out_clear_winकरोw:
	हटाओ_ddw(pdn, true);

out_मुक्त_prop:
	kमुक्त(win64->name);
	kमुक्त(win64->value);
	kमुक्त(win64);

out_failed:
	अगर (शेष_win_हटाओd)
		reset_dma_winकरोw(dev, pdn);

	fpdn = kzalloc(माप(*fpdn), GFP_KERNEL);
	अगर (!fpdn)
		जाओ out_unlock;
	fpdn->pdn = pdn;
	list_add(&fpdn->list, &failed_ddw_pdn_list);

out_unlock:
	mutex_unlock(&direct_winकरोw_init_mutex);

	/*
	 * If we have persistent memory and the winकरोw size is only as big
	 * as RAM, then we failed to create a winकरोw to cover persistent
	 * memory and need to set the DMA limit.
	 */
	अगर (pmem_present && dma_addr && (len == max_ram_len))
		dev->dev.bus_dma_limit = dma_addr + (1ULL << len);

	वापस dma_addr;
पूर्ण

अटल व्योम pci_dma_dev_setup_pSeriesLP(काष्ठा pci_dev *dev)
अणु
	काष्ठा device_node *pdn, *dn;
	काष्ठा iommu_table *tbl;
	स्थिर __be32 *dma_winकरोw = शून्य;
	काष्ठा pci_dn *pci;

	pr_debug("pci_dma_dev_setup_pSeriesLP: %s\n", pci_name(dev));

	/* dev setup क्रम LPAR is a little tricky, since the device tree might
	 * contain the dma-winकरोw properties per-device and not necessarily
	 * क्रम the bus. So we need to search upwards in the tree until we
	 * either hit a dma-winकरोw property, OR find a parent with a table
	 * alपढ़ोy allocated.
	 */
	dn = pci_device_to_OF_node(dev);
	pr_debug("  node is %pOF\n", dn);

	क्रम (pdn = dn; pdn && PCI_DN(pdn) && !PCI_DN(pdn)->table_group;
	     pdn = pdn->parent) अणु
		dma_winकरोw = of_get_property(pdn, "ibm,dma-window", शून्य);
		अगर (dma_winकरोw)
			अवरोध;
	पूर्ण

	अगर (!pdn || !PCI_DN(pdn)) अणु
		prपूर्णांकk(KERN_WARNING "pci_dma_dev_setup_pSeriesLP: "
		       "no DMA window found for pci dev=%s dn=%pOF\n",
				 pci_name(dev), dn);
		वापस;
	पूर्ण
	pr_debug("  parent is %pOF\n", pdn);

	pci = PCI_DN(pdn);
	अगर (!pci->table_group) अणु
		pci->table_group = iommu_pseries_alloc_group(pci->phb->node);
		tbl = pci->table_group->tables[0];
		iommu_table_setparms_lpar(pci->phb, pdn, tbl,
				pci->table_group, dma_winकरोw);
		tbl->it_ops = &iommu_table_lpar_multi_ops;
		iommu_init_table(tbl, pci->phb->node, 0, 0);
		iommu_रेजिस्टर_group(pci->table_group,
				pci_करोमुख्य_nr(pci->phb->bus), 0);
		pr_debug("  created table: %p\n", pci->table_group);
	पूर्ण अन्यथा अणु
		pr_debug("  found DMA window, table: %p\n", pci->table_group);
	पूर्ण

	set_iommu_table_base(&dev->dev, pci->table_group->tables[0]);
	iommu_add_device(pci->table_group, &dev->dev);
पूर्ण

अटल bool iommu_bypass_supported_pSeriesLP(काष्ठा pci_dev *pdev, u64 dma_mask)
अणु
	काष्ठा device_node *dn = pci_device_to_OF_node(pdev), *pdn;
	स्थिर __be32 *dma_winकरोw = शून्य;

	/* only attempt to use a new winकरोw अगर 64-bit DMA is requested */
	अगर (dma_mask < DMA_BIT_MASK(64))
		वापस false;

	dev_dbg(&pdev->dev, "node is %pOF\n", dn);

	/*
	 * the device tree might contain the dma-winकरोw properties
	 * per-device and not necessarily क्रम the bus. So we need to
	 * search upwards in the tree until we either hit a dma-winकरोw
	 * property, OR find a parent with a table alपढ़ोy allocated.
	 */
	क्रम (pdn = dn; pdn && PCI_DN(pdn) && !PCI_DN(pdn)->table_group;
			pdn = pdn->parent) अणु
		dma_winकरोw = of_get_property(pdn, "ibm,dma-window", शून्य);
		अगर (dma_winकरोw)
			अवरोध;
	पूर्ण

	अगर (pdn && PCI_DN(pdn)) अणु
		pdev->dev.archdata.dma_offset = enable_ddw(pdev, pdn);
		अगर (pdev->dev.archdata.dma_offset)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक iommu_mem_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action,
		व्योम *data)
अणु
	काष्ठा direct_winकरोw *winकरोw;
	काष्ठा memory_notअगरy *arg = data;
	पूर्णांक ret = 0;

	चयन (action) अणु
	हाल MEM_GOING_ONLINE:
		spin_lock(&direct_winकरोw_list_lock);
		list_क्रम_each_entry(winकरोw, &direct_winकरोw_list, list) अणु
			ret |= tce_setrange_multi_pSeriesLP(arg->start_pfn,
					arg->nr_pages, winकरोw->prop);
			/* XXX log error */
		पूर्ण
		spin_unlock(&direct_winकरोw_list_lock);
		अवरोध;
	हाल MEM_CANCEL_ONLINE:
	हाल MEM_OFFLINE:
		spin_lock(&direct_winकरोw_list_lock);
		list_क्रम_each_entry(winकरोw, &direct_winकरोw_list, list) अणु
			ret |= tce_clearrange_multi_pSeriesLP(arg->start_pfn,
					arg->nr_pages, winकरोw->prop);
			/* XXX log error */
		पूर्ण
		spin_unlock(&direct_winकरोw_list_lock);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (ret && action != MEM_CANCEL_ONLINE)
		वापस NOTIFY_BAD;

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block iommu_mem_nb = अणु
	.notअगरier_call = iommu_mem_notअगरier,
पूर्ण;

अटल पूर्णांक iommu_reconfig_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action, व्योम *data)
अणु
	पूर्णांक err = NOTIFY_OK;
	काष्ठा of_reconfig_data *rd = data;
	काष्ठा device_node *np = rd->dn;
	काष्ठा pci_dn *pci = PCI_DN(np);
	काष्ठा direct_winकरोw *winकरोw;

	चयन (action) अणु
	हाल OF_RECONFIG_DETACH_NODE:
		/*
		 * Removing the property will invoke the reconfig
		 * notअगरier again, which causes dead-lock on the
		 * पढ़ो-ग_लिखो semaphore of the notअगरier chain. So
		 * we have to हटाओ the property when releasing
		 * the device node.
		 */
		हटाओ_ddw(np, false);
		अगर (pci && pci->table_group)
			iommu_pseries_मुक्त_group(pci->table_group,
					np->full_name);

		spin_lock(&direct_winकरोw_list_lock);
		list_क्रम_each_entry(winकरोw, &direct_winकरोw_list, list) अणु
			अगर (winकरोw->device == np) अणु
				list_del(&winकरोw->list);
				kमुक्त(winकरोw);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&direct_winकरोw_list_lock);
		अवरोध;
	शेष:
		err = NOTIFY_DONE;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा notअगरier_block iommu_reconfig_nb = अणु
	.notअगरier_call = iommu_reconfig_notअगरier,
पूर्ण;

/* These are called very early. */
व्योम iommu_init_early_pSeries(व्योम)
अणु
	अगर (of_chosen && of_get_property(of_chosen, "linux,iommu-off", शून्य))
		वापस;

	अगर (firmware_has_feature(FW_FEATURE_LPAR)) अणु
		pseries_pci_controller_ops.dma_bus_setup = pci_dma_bus_setup_pSeriesLP;
		pseries_pci_controller_ops.dma_dev_setup = pci_dma_dev_setup_pSeriesLP;
		अगर (!disable_ddw)
			pseries_pci_controller_ops.iommu_bypass_supported =
				iommu_bypass_supported_pSeriesLP;
	पूर्ण अन्यथा अणु
		pseries_pci_controller_ops.dma_bus_setup = pci_dma_bus_setup_pSeries;
		pseries_pci_controller_ops.dma_dev_setup = pci_dma_dev_setup_pSeries;
	पूर्ण


	of_reconfig_notअगरier_रेजिस्टर(&iommu_reconfig_nb);
	रेजिस्टर_memory_notअगरier(&iommu_mem_nb);

	set_pci_dma_ops(&dma_iommu_ops);
पूर्ण

अटल पूर्णांक __init disable_multitce(अक्षर *str)
अणु
	अगर (म_भेद(str, "off") == 0 &&
	    firmware_has_feature(FW_FEATURE_LPAR) &&
	    (firmware_has_feature(FW_FEATURE_PUT_TCE_IND) ||
	     firmware_has_feature(FW_FEATURE_STUFF_TCE))) अणु
		prपूर्णांकk(KERN_INFO "Disabling MULTITCE firmware feature\n");
		घातerpc_firmware_features &=
			~(FW_FEATURE_PUT_TCE_IND | FW_FEATURE_STUFF_TCE);
	पूर्ण
	वापस 1;
पूर्ण

__setup("multitce=", disable_multitce);

अटल पूर्णांक tce_iommu_bus_notअगरier(काष्ठा notअगरier_block *nb,
		अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा device *dev = data;

	चयन (action) अणु
	हाल BUS_NOTIFY_DEL_DEVICE:
		iommu_del_device(dev);
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block tce_iommu_bus_nb = अणु
	.notअगरier_call = tce_iommu_bus_notअगरier,
पूर्ण;

अटल पूर्णांक __init tce_iommu_bus_notअगरier_init(व्योम)
अणु
	bus_रेजिस्टर_notअगरier(&pci_bus_type, &tce_iommu_bus_nb);
	वापस 0;
पूर्ण
machine_subsys_initcall_sync(pseries, tce_iommu_bus_notअगरier_init);
