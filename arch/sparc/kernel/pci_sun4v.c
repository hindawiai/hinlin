<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* pci_sun4v.c: SUN4V specअगरic PCI controller support.
 *
 * Copyright (C) 2006, 2007, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/irq.h>
#समावेश <linux/msi.h>
#समावेश <linux/export.h>
#समावेश <linux/log2.h>
#समावेश <linux/of_device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <यंत्र/iommu-common.h>

#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/prom.h>

#समावेश "pci_impl.h"
#समावेश "iommu_common.h"
#समावेश "kernel.h"

#समावेश "pci_sun4v.h"

#घोषणा DRIVER_NAME	"pci_sun4v"
#घोषणा PFX		DRIVER_NAME ": "

अटल अचिन्हित दीर्घ vpci_major;
अटल अचिन्हित दीर्घ vpci_minor;

काष्ठा vpci_version अणु
	अचिन्हित दीर्घ major;
	अचिन्हित दीर्घ minor;
पूर्ण;

/* Ordered from largest major to lowest */
अटल काष्ठा vpci_version vpci_versions[] = अणु
	अणु .major = 2, .minor = 0 पूर्ण,
	अणु .major = 1, .minor = 1 पूर्ण,
पूर्ण;

अटल अचिन्हित दीर्घ vatu_major = 1;
अटल अचिन्हित दीर्घ vatu_minor = 1;

#घोषणा PGLIST_NENTS	(PAGE_SIZE / माप(u64))

काष्ठा iommu_batch अणु
	काष्ठा device	*dev;		/* Device mapping is क्रम.	*/
	अचिन्हित दीर्घ	prot;		/* IOMMU page protections	*/
	अचिन्हित दीर्घ	entry;		/* Index पूर्णांकo IOTSB.		*/
	u64		*pglist;	/* List of physical pages	*/
	अचिन्हित दीर्घ	npages;		/* Number of pages in list.	*/
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा iommu_batch, iommu_batch);
अटल पूर्णांक iommu_batch_initialized;

/* Interrupts must be disabled.  */
अटल अंतरभूत व्योम iommu_batch_start(काष्ठा device *dev, अचिन्हित दीर्घ prot, अचिन्हित दीर्घ entry)
अणु
	काष्ठा iommu_batch *p = this_cpu_ptr(&iommu_batch);

	p->dev		= dev;
	p->prot		= prot;
	p->entry	= entry;
	p->npages	= 0;
पूर्ण

अटल अंतरभूत bool iommu_use_atu(काष्ठा iommu *iommu, u64 mask)
अणु
	वापस iommu->atu && mask > DMA_BIT_MASK(32);
पूर्ण

/* Interrupts must be disabled.  */
अटल दीर्घ iommu_batch_flush(काष्ठा iommu_batch *p, u64 mask)
अणु
	काष्ठा pci_pbm_info *pbm = p->dev->archdata.host_controller;
	u64 *pglist = p->pglist;
	u64 index_count;
	अचिन्हित दीर्घ devhandle = pbm->devhandle;
	अचिन्हित दीर्घ prot = p->prot;
	अचिन्हित दीर्घ entry = p->entry;
	अचिन्हित दीर्घ npages = p->npages;
	अचिन्हित दीर्घ iotsb_num;
	अचिन्हित दीर्घ ret;
	दीर्घ num;

	/* VPCI maj=1, min=[0,1] only supports पढ़ो and ग_लिखो */
	अगर (vpci_major < 2)
		prot &= (HV_PCI_MAP_ATTR_READ | HV_PCI_MAP_ATTR_WRITE);

	जबतक (npages != 0) अणु
		अगर (!iommu_use_atu(pbm->iommu, mask)) अणु
			num = pci_sun4v_iommu_map(devhandle,
						  HV_PCI_TSBID(0, entry),
						  npages,
						  prot,
						  __pa(pglist));
			अगर (unlikely(num < 0)) अणु
				pr_err_ratelimited("%s: IOMMU map of [%08lx:%08llx:%lx:%lx:%lx] failed with status %ld\n",
						   __func__,
						   devhandle,
						   HV_PCI_TSBID(0, entry),
						   npages, prot, __pa(pglist),
						   num);
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			index_count = HV_PCI_IOTSB_INDEX_COUNT(npages, entry),
			iotsb_num = pbm->iommu->atu->iotsb->iotsb_num;
			ret = pci_sun4v_iotsb_map(devhandle,
						  iotsb_num,
						  index_count,
						  prot,
						  __pa(pglist),
						  &num);
			अगर (unlikely(ret != HV_EOK)) अणु
				pr_err_ratelimited("%s: ATU map of [%08lx:%lx:%llx:%lx:%lx] failed with status %ld\n",
						   __func__,
						   devhandle, iotsb_num,
						   index_count, prot,
						   __pa(pglist), ret);
				वापस -1;
			पूर्ण
		पूर्ण
		entry += num;
		npages -= num;
		pglist += num;
	पूर्ण

	p->entry = entry;
	p->npages = 0;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम iommu_batch_new_entry(अचिन्हित दीर्घ entry, u64 mask)
अणु
	काष्ठा iommu_batch *p = this_cpu_ptr(&iommu_batch);

	अगर (p->entry + p->npages == entry)
		वापस;
	अगर (p->entry != ~0UL)
		iommu_batch_flush(p, mask);
	p->entry = entry;
पूर्ण

/* Interrupts must be disabled.  */
अटल अंतरभूत दीर्घ iommu_batch_add(u64 phys_page, u64 mask)
अणु
	काष्ठा iommu_batch *p = this_cpu_ptr(&iommu_batch);

	BUG_ON(p->npages >= PGLIST_NENTS);

	p->pglist[p->npages++] = phys_page;
	अगर (p->npages == PGLIST_NENTS)
		वापस iommu_batch_flush(p, mask);

	वापस 0;
पूर्ण

/* Interrupts must be disabled.  */
अटल अंतरभूत दीर्घ iommu_batch_end(u64 mask)
अणु
	काष्ठा iommu_batch *p = this_cpu_ptr(&iommu_batch);

	BUG_ON(p->npages >= PGLIST_NENTS);

	वापस iommu_batch_flush(p, mask);
पूर्ण

अटल व्योम *dma_4v_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				   dma_addr_t *dma_addrp, gfp_t gfp,
				   अचिन्हित दीर्घ attrs)
अणु
	u64 mask;
	अचिन्हित दीर्घ flags, order, first_page, npages, n;
	अचिन्हित दीर्घ prot = 0;
	काष्ठा iommu *iommu;
	काष्ठा iommu_map_table *tbl;
	काष्ठा page *page;
	व्योम *ret;
	दीर्घ entry;
	पूर्णांक nid;

	size = IO_PAGE_ALIGN(size);
	order = get_order(size);
	अगर (unlikely(order >= MAX_ORDER))
		वापस शून्य;

	npages = size >> IO_PAGE_SHIFT;

	अगर (attrs & DMA_ATTR_WEAK_ORDERING)
		prot = HV_PCI_MAP_ATTR_RELAXED_ORDER;

	nid = dev->archdata.numa_node;
	page = alloc_pages_node(nid, gfp, order);
	अगर (unlikely(!page))
		वापस शून्य;

	first_page = (अचिन्हित दीर्घ) page_address(page);
	स_रखो((अक्षर *)first_page, 0, PAGE_SIZE << order);

	iommu = dev->archdata.iommu;
	mask = dev->coherent_dma_mask;
	अगर (!iommu_use_atu(iommu, mask))
		tbl = &iommu->tbl;
	अन्यथा
		tbl = &iommu->atu->tbl;

	entry = iommu_tbl_range_alloc(dev, tbl, npages, शून्य,
				      (अचिन्हित दीर्घ)(-1), 0);

	अगर (unlikely(entry == IOMMU_ERROR_CODE))
		जाओ range_alloc_fail;

	*dma_addrp = (tbl->table_map_base + (entry << IO_PAGE_SHIFT));
	ret = (व्योम *) first_page;
	first_page = __pa(first_page);

	local_irq_save(flags);

	iommu_batch_start(dev,
			  (HV_PCI_MAP_ATTR_READ | prot |
			   HV_PCI_MAP_ATTR_WRITE),
			  entry);

	क्रम (n = 0; n < npages; n++) अणु
		दीर्घ err = iommu_batch_add(first_page + (n * PAGE_SIZE), mask);
		अगर (unlikely(err < 0L))
			जाओ iommu_map_fail;
	पूर्ण

	अगर (unlikely(iommu_batch_end(mask) < 0L))
		जाओ iommu_map_fail;

	local_irq_restore(flags);

	वापस ret;

iommu_map_fail:
	local_irq_restore(flags);
	iommu_tbl_range_मुक्त(tbl, *dma_addrp, npages, IOMMU_ERROR_CODE);

range_alloc_fail:
	मुक्त_pages(first_page, order);
	वापस शून्य;
पूर्ण

अचिन्हित दीर्घ dma_4v_iotsb_bind(अचिन्हित दीर्घ devhandle,
				अचिन्हित दीर्घ iotsb_num,
				काष्ठा pci_bus *bus_dev)
अणु
	काष्ठा pci_dev *pdev;
	अचिन्हित दीर्घ err;
	अचिन्हित पूर्णांक bus;
	अचिन्हित पूर्णांक device;
	अचिन्हित पूर्णांक fun;

	list_क्रम_each_entry(pdev, &bus_dev->devices, bus_list) अणु
		अगर (pdev->subordinate) अणु
			/* No need to bind pci bridge */
			dma_4v_iotsb_bind(devhandle, iotsb_num,
					  pdev->subordinate);
		पूर्ण अन्यथा अणु
			bus = bus_dev->number;
			device = PCI_SLOT(pdev->devfn);
			fun = PCI_FUNC(pdev->devfn);
			err = pci_sun4v_iotsb_bind(devhandle, iotsb_num,
						   HV_PCI_DEVICE_BUILD(bus,
								       device,
								       fun));

			/* If bind fails क्रम one device it is going to fail
			 * क्रम rest of the devices because we are sharing
			 * IOTSB. So in हाल of failure simply वापस with
			 * error.
			 */
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dma_4v_iommu_demap(काष्ठा device *dev, अचिन्हित दीर्घ devhandle,
			       dma_addr_t dvma, अचिन्हित दीर्घ iotsb_num,
			       अचिन्हित दीर्घ entry, अचिन्हित दीर्घ npages)
अणु
	अचिन्हित दीर्घ num, flags;
	अचिन्हित दीर्घ ret;

	local_irq_save(flags);
	करो अणु
		अगर (dvma <= DMA_BIT_MASK(32)) अणु
			num = pci_sun4v_iommu_demap(devhandle,
						    HV_PCI_TSBID(0, entry),
						    npages);
		पूर्ण अन्यथा अणु
			ret = pci_sun4v_iotsb_demap(devhandle, iotsb_num,
						    entry, npages, &num);
			अगर (unlikely(ret != HV_EOK)) अणु
				pr_err_ratelimited("pci_iotsb_demap() failed with error: %ld\n",
						   ret);
			पूर्ण
		पूर्ण
		entry += num;
		npages -= num;
	पूर्ण जबतक (npages != 0);
	local_irq_restore(flags);
पूर्ण

अटल व्योम dma_4v_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu,
				 dma_addr_t dvma, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_pbm_info *pbm;
	काष्ठा iommu *iommu;
	काष्ठा atu *atu;
	काष्ठा iommu_map_table *tbl;
	अचिन्हित दीर्घ order, npages, entry;
	अचिन्हित दीर्घ iotsb_num;
	u32 devhandle;

	npages = IO_PAGE_ALIGN(size) >> IO_PAGE_SHIFT;
	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	atu = iommu->atu;
	devhandle = pbm->devhandle;

	अगर (!iommu_use_atu(iommu, dvma)) अणु
		tbl = &iommu->tbl;
		iotsb_num = 0; /* we करोn't care क्रम legacy iommu */
	पूर्ण अन्यथा अणु
		tbl = &atu->tbl;
		iotsb_num = atu->iotsb->iotsb_num;
	पूर्ण
	entry = ((dvma - tbl->table_map_base) >> IO_PAGE_SHIFT);
	dma_4v_iommu_demap(dev, devhandle, dvma, iotsb_num, entry, npages);
	iommu_tbl_range_मुक्त(tbl, dvma, npages, IOMMU_ERROR_CODE);
	order = get_order(size);
	अगर (order < 10)
		मुक्त_pages((अचिन्हित दीर्घ)cpu, order);
पूर्ण

अटल dma_addr_t dma_4v_map_page(काष्ठा device *dev, काष्ठा page *page,
				  अचिन्हित दीर्घ offset, माप_प्रकार sz,
				  क्रमागत dma_data_direction direction,
				  अचिन्हित दीर्घ attrs)
अणु
	काष्ठा iommu *iommu;
	काष्ठा atu *atu;
	काष्ठा iommu_map_table *tbl;
	u64 mask;
	अचिन्हित दीर्घ flags, npages, oaddr;
	अचिन्हित दीर्घ i, base_paddr;
	अचिन्हित दीर्घ prot;
	dma_addr_t bus_addr, ret;
	दीर्घ entry;

	iommu = dev->archdata.iommu;
	atu = iommu->atu;

	अगर (unlikely(direction == DMA_NONE))
		जाओ bad;

	oaddr = (अचिन्हित दीर्घ)(page_address(page) + offset);
	npages = IO_PAGE_ALIGN(oaddr + sz) - (oaddr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;

	mask = *dev->dma_mask;
	अगर (!iommu_use_atu(iommu, mask))
		tbl = &iommu->tbl;
	अन्यथा
		tbl = &atu->tbl;

	entry = iommu_tbl_range_alloc(dev, tbl, npages, शून्य,
				      (अचिन्हित दीर्घ)(-1), 0);

	अगर (unlikely(entry == IOMMU_ERROR_CODE))
		जाओ bad;

	bus_addr = (tbl->table_map_base + (entry << IO_PAGE_SHIFT));
	ret = bus_addr | (oaddr & ~IO_PAGE_MASK);
	base_paddr = __pa(oaddr & IO_PAGE_MASK);
	prot = HV_PCI_MAP_ATTR_READ;
	अगर (direction != DMA_TO_DEVICE)
		prot |= HV_PCI_MAP_ATTR_WRITE;

	अगर (attrs & DMA_ATTR_WEAK_ORDERING)
		prot |= HV_PCI_MAP_ATTR_RELAXED_ORDER;

	local_irq_save(flags);

	iommu_batch_start(dev, prot, entry);

	क्रम (i = 0; i < npages; i++, base_paddr += IO_PAGE_SIZE) अणु
		दीर्घ err = iommu_batch_add(base_paddr, mask);
		अगर (unlikely(err < 0L))
			जाओ iommu_map_fail;
	पूर्ण
	अगर (unlikely(iommu_batch_end(mask) < 0L))
		जाओ iommu_map_fail;

	local_irq_restore(flags);

	वापस ret;

bad:
	अगर (prपूर्णांकk_ratelimit())
		WARN_ON(1);
	वापस DMA_MAPPING_ERROR;

iommu_map_fail:
	local_irq_restore(flags);
	iommu_tbl_range_मुक्त(tbl, bus_addr, npages, IOMMU_ERROR_CODE);
	वापस DMA_MAPPING_ERROR;
पूर्ण

अटल व्योम dma_4v_unmap_page(काष्ठा device *dev, dma_addr_t bus_addr,
			      माप_प्रकार sz, क्रमागत dma_data_direction direction,
			      अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_pbm_info *pbm;
	काष्ठा iommu *iommu;
	काष्ठा atu *atu;
	काष्ठा iommu_map_table *tbl;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ iotsb_num;
	दीर्घ entry;
	u32 devhandle;

	अगर (unlikely(direction == DMA_NONE)) अणु
		अगर (prपूर्णांकk_ratelimit())
			WARN_ON(1);
		वापस;
	पूर्ण

	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	atu = iommu->atu;
	devhandle = pbm->devhandle;

	npages = IO_PAGE_ALIGN(bus_addr + sz) - (bus_addr & IO_PAGE_MASK);
	npages >>= IO_PAGE_SHIFT;
	bus_addr &= IO_PAGE_MASK;

	अगर (bus_addr <= DMA_BIT_MASK(32)) अणु
		iotsb_num = 0; /* we करोn't care क्रम legacy iommu */
		tbl = &iommu->tbl;
	पूर्ण अन्यथा अणु
		iotsb_num = atu->iotsb->iotsb_num;
		tbl = &atu->tbl;
	पूर्ण
	entry = (bus_addr - tbl->table_map_base) >> IO_PAGE_SHIFT;
	dma_4v_iommu_demap(dev, devhandle, bus_addr, iotsb_num, entry, npages);
	iommu_tbl_range_मुक्त(tbl, bus_addr, npages, IOMMU_ERROR_CODE);
पूर्ण

अटल पूर्णांक dma_4v_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			 पूर्णांक nelems, क्रमागत dma_data_direction direction,
			 अचिन्हित दीर्घ attrs)
अणु
	काष्ठा scatterlist *s, *outs, *segstart;
	अचिन्हित दीर्घ flags, handle, prot;
	dma_addr_t dma_next = 0, dma_addr;
	अचिन्हित पूर्णांक max_seg_size;
	अचिन्हित दीर्घ seg_boundary_size;
	पूर्णांक outcount, incount, i;
	काष्ठा iommu *iommu;
	काष्ठा atu *atu;
	काष्ठा iommu_map_table *tbl;
	u64 mask;
	अचिन्हित दीर्घ base_shअगरt;
	दीर्घ err;

	BUG_ON(direction == DMA_NONE);

	iommu = dev->archdata.iommu;
	अगर (nelems == 0 || !iommu)
		वापस 0;
	atu = iommu->atu;

	prot = HV_PCI_MAP_ATTR_READ;
	अगर (direction != DMA_TO_DEVICE)
		prot |= HV_PCI_MAP_ATTR_WRITE;

	अगर (attrs & DMA_ATTR_WEAK_ORDERING)
		prot |= HV_PCI_MAP_ATTR_RELAXED_ORDER;

	outs = s = segstart = &sglist[0];
	outcount = 1;
	incount = nelems;
	handle = 0;

	/* Init first segment length क्रम backout at failure */
	outs->dma_length = 0;

	local_irq_save(flags);

	iommu_batch_start(dev, prot, ~0UL);

	max_seg_size = dma_get_max_seg_size(dev);
	seg_boundary_size = dma_get_seg_boundary_nr_pages(dev, IO_PAGE_SHIFT);

	mask = *dev->dma_mask;
	अगर (!iommu_use_atu(iommu, mask))
		tbl = &iommu->tbl;
	अन्यथा
		tbl = &atu->tbl;

	base_shअगरt = tbl->table_map_base >> IO_PAGE_SHIFT;

	क्रम_each_sg(sglist, s, nelems, i) अणु
		अचिन्हित दीर्घ paddr, npages, entry, out_entry = 0, slen;

		slen = s->length;
		/* Sanity check */
		अगर (slen == 0) अणु
			dma_next = 0;
			जारी;
		पूर्ण
		/* Allocate iommu entries क्रम that segment */
		paddr = (अचिन्हित दीर्घ) SG_ENT_PHYS_ADDRESS(s);
		npages = iommu_num_pages(paddr, slen, IO_PAGE_SIZE);
		entry = iommu_tbl_range_alloc(dev, tbl, npages,
					      &handle, (अचिन्हित दीर्घ)(-1), 0);

		/* Handle failure */
		अगर (unlikely(entry == IOMMU_ERROR_CODE)) अणु
			pr_err_ratelimited("iommu_alloc failed, iommu %p paddr %lx npages %lx\n",
					   tbl, paddr, npages);
			जाओ iommu_map_failed;
		पूर्ण

		iommu_batch_new_entry(entry, mask);

		/* Convert entry to a dma_addr_t */
		dma_addr = tbl->table_map_base + (entry << IO_PAGE_SHIFT);
		dma_addr |= (s->offset & ~IO_PAGE_MASK);

		/* Insert पूर्णांकo HW table */
		paddr &= IO_PAGE_MASK;
		जबतक (npages--) अणु
			err = iommu_batch_add(paddr, mask);
			अगर (unlikely(err < 0L))
				जाओ iommu_map_failed;
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

	err = iommu_batch_end(mask);

	अगर (unlikely(err < 0L))
		जाओ iommu_map_failed;

	local_irq_restore(flags);

	अगर (outcount < incount) अणु
		outs = sg_next(outs);
		outs->dma_address = DMA_MAPPING_ERROR;
		outs->dma_length = 0;
	पूर्ण

	वापस outcount;

iommu_map_failed:
	क्रम_each_sg(sglist, s, nelems, i) अणु
		अगर (s->dma_length != 0) अणु
			अचिन्हित दीर्घ vaddr, npages;

			vaddr = s->dma_address & IO_PAGE_MASK;
			npages = iommu_num_pages(s->dma_address, s->dma_length,
						 IO_PAGE_SIZE);
			iommu_tbl_range_मुक्त(tbl, vaddr, npages,
					     IOMMU_ERROR_CODE);
			/* XXX demap? XXX */
			s->dma_address = DMA_MAPPING_ERROR;
			s->dma_length = 0;
		पूर्ण
		अगर (s == outs)
			अवरोध;
	पूर्ण
	local_irq_restore(flags);

	वापस 0;
पूर्ण

अटल व्योम dma_4v_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			    पूर्णांक nelems, क्रमागत dma_data_direction direction,
			    अचिन्हित दीर्घ attrs)
अणु
	काष्ठा pci_pbm_info *pbm;
	काष्ठा scatterlist *sg;
	काष्ठा iommu *iommu;
	काष्ठा atu *atu;
	अचिन्हित दीर्घ flags, entry;
	अचिन्हित दीर्घ iotsb_num;
	u32 devhandle;

	BUG_ON(direction == DMA_NONE);

	iommu = dev->archdata.iommu;
	pbm = dev->archdata.host_controller;
	atu = iommu->atu;
	devhandle = pbm->devhandle;
	
	local_irq_save(flags);

	sg = sglist;
	जबतक (nelems--) अणु
		dma_addr_t dma_handle = sg->dma_address;
		अचिन्हित पूर्णांक len = sg->dma_length;
		अचिन्हित दीर्घ npages;
		काष्ठा iommu_map_table *tbl;
		अचिन्हित दीर्घ shअगरt = IO_PAGE_SHIFT;

		अगर (!len)
			अवरोध;
		npages = iommu_num_pages(dma_handle, len, IO_PAGE_SIZE);

		अगर (dma_handle <= DMA_BIT_MASK(32)) अणु
			iotsb_num = 0; /* we करोn't care क्रम legacy iommu */
			tbl = &iommu->tbl;
		पूर्ण अन्यथा अणु
			iotsb_num = atu->iotsb->iotsb_num;
			tbl = &atu->tbl;
		पूर्ण
		entry = ((dma_handle - tbl->table_map_base) >> shअगरt);
		dma_4v_iommu_demap(dev, devhandle, dma_handle, iotsb_num,
				   entry, npages);
		iommu_tbl_range_मुक्त(tbl, dma_handle, npages,
				     IOMMU_ERROR_CODE);
		sg = sg_next(sg);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक dma_4v_supported(काष्ठा device *dev, u64 device_mask)
अणु
	काष्ठा iommu *iommu = dev->archdata.iommu;

	अगर (ali_sound_dma_hack(dev, device_mask))
		वापस 1;
	अगर (device_mask < iommu->dma_addr_mask)
		वापस 0;
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dma_map_ops sun4v_dma_ops = अणु
	.alloc				= dma_4v_alloc_coherent,
	.मुक्त				= dma_4v_मुक्त_coherent,
	.map_page			= dma_4v_map_page,
	.unmap_page			= dma_4v_unmap_page,
	.map_sg				= dma_4v_map_sg,
	.unmap_sg			= dma_4v_unmap_sg,
	.dma_supported			= dma_4v_supported,
पूर्ण;

अटल व्योम pci_sun4v_scan_bus(काष्ठा pci_pbm_info *pbm, काष्ठा device *parent)
अणु
	काष्ठा property *prop;
	काष्ठा device_node *dp;

	dp = pbm->op->dev.of_node;
	prop = of_find_property(dp, "66mhz-capable", शून्य);
	pbm->is_66mhz_capable = (prop != शून्य);
	pbm->pci_bus = pci_scan_one_pbm(pbm, parent);

	/* XXX रेजिस्टर error पूर्णांकerrupt handlers XXX */
पूर्ण

अटल अचिन्हित दीर्घ probe_existing_entries(काष्ठा pci_pbm_info *pbm,
					    काष्ठा iommu_map_table *iommu)
अणु
	काष्ठा iommu_pool *pool;
	अचिन्हित दीर्घ i, pool_nr, cnt = 0;
	u32 devhandle;

	devhandle = pbm->devhandle;
	क्रम (pool_nr = 0; pool_nr < iommu->nr_pools; pool_nr++) अणु
		pool = &(iommu->pools[pool_nr]);
		क्रम (i = pool->start; i <= pool->end; i++) अणु
			अचिन्हित दीर्घ ret, io_attrs, ra;

			ret = pci_sun4v_iommu_geपंचांगap(devhandle,
						     HV_PCI_TSBID(0, i),
						     &io_attrs, &ra);
			अगर (ret == HV_EOK) अणु
				अगर (page_in_phys_avail(ra)) अणु
					pci_sun4v_iommu_demap(devhandle,
							      HV_PCI_TSBID(0,
							      i), 1);
				पूर्ण अन्यथा अणु
					cnt++;
					__set_bit(i, iommu->map);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस cnt;
पूर्ण

अटल पूर्णांक pci_sun4v_atu_alloc_iotsb(काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा atu *atu = pbm->iommu->atu;
	काष्ठा atu_iotsb *iotsb;
	व्योम *table;
	u64 table_size;
	u64 iotsb_num;
	अचिन्हित दीर्घ order;
	अचिन्हित दीर्घ err;

	iotsb = kzalloc(माप(*iotsb), GFP_KERNEL);
	अगर (!iotsb) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण
	atu->iotsb = iotsb;

	/* calculate size of IOTSB */
	table_size = (atu->size / IO_PAGE_SIZE) * 8;
	order = get_order(table_size);
	table = (व्योम *)__get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!table) अणु
		err = -ENOMEM;
		जाओ table_failed;
	पूर्ण
	iotsb->table = table;
	iotsb->ra = __pa(table);
	iotsb->dvma_size = atu->size;
	iotsb->dvma_base = atu->base;
	iotsb->table_size = table_size;
	iotsb->page_size = IO_PAGE_SIZE;

	/* configure and रेजिस्टर IOTSB with HV */
	err = pci_sun4v_iotsb_conf(pbm->devhandle,
				   iotsb->ra,
				   iotsb->table_size,
				   iotsb->page_size,
				   iotsb->dvma_base,
				   &iotsb_num);
	अगर (err) अणु
		pr_err(PFX "pci_iotsb_conf failed error: %ld\n", err);
		जाओ iotsb_conf_failed;
	पूर्ण
	iotsb->iotsb_num = iotsb_num;

	err = dma_4v_iotsb_bind(pbm->devhandle, iotsb_num, pbm->pci_bus);
	अगर (err) अणु
		pr_err(PFX "pci_iotsb_bind failed error: %ld\n", err);
		जाओ iotsb_conf_failed;
	पूर्ण

	वापस 0;

iotsb_conf_failed:
	मुक्त_pages((अचिन्हित दीर्घ)table, order);
table_failed:
	kमुक्त(iotsb);
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक pci_sun4v_atu_init(काष्ठा pci_pbm_info *pbm)
अणु
	काष्ठा atu *atu = pbm->iommu->atu;
	अचिन्हित दीर्घ err;
	स्थिर u64 *ranges;
	u64 map_size, num_iotte;
	u64 dma_mask;
	स्थिर u32 *page_size;
	पूर्णांक len;

	ranges = of_get_property(pbm->op->dev.of_node, "iommu-address-ranges",
				 &len);
	अगर (!ranges) अणु
		pr_err(PFX "No iommu-address-ranges\n");
		वापस -EINVAL;
	पूर्ण

	page_size = of_get_property(pbm->op->dev.of_node, "iommu-pagesizes",
				    शून्य);
	अगर (!page_size) अणु
		pr_err(PFX "No iommu-pagesizes\n");
		वापस -EINVAL;
	पूर्ण

	/* There are 4 iommu-address-ranges supported. Each range is pair of
	 * अणुbase, sizeपूर्ण. The ranges[0] and ranges[1] are 32bit address space
	 * जबतक ranges[2] and ranges[3] are 64bit space.  We want to use 64bit
	 * address ranges to support 64bit addressing. Because 'size' क्रम
	 * address ranges[2] and ranges[3] are same we can select either of
	 * ranges[2] or ranges[3] क्रम mapping. However due to 'size' is too
	 * large क्रम OS to allocate IOTSB we are using fix size 32G
	 * (ATU_64_SPACE_SIZE) which is more than enough क्रम all PCIe devices
	 * to share.
	 */
	atu->ranges = (काष्ठा atu_ranges *)ranges;
	atu->base = atu->ranges[3].base;
	atu->size = ATU_64_SPACE_SIZE;

	/* Create IOTSB */
	err = pci_sun4v_atu_alloc_iotsb(pbm);
	अगर (err) अणु
		pr_err(PFX "Error creating ATU IOTSB\n");
		वापस err;
	पूर्ण

	/* Create ATU iommu map.
	 * One bit represents one iotte in IOTSB table.
	 */
	dma_mask = (roundup_घात_of_two(atu->size) - 1UL);
	num_iotte = atu->size / IO_PAGE_SIZE;
	map_size = num_iotte / 8;
	atu->tbl.table_map_base = atu->base;
	atu->dma_addr_mask = dma_mask;
	atu->tbl.map = kzalloc(map_size, GFP_KERNEL);
	अगर (!atu->tbl.map)
		वापस -ENOMEM;

	iommu_tbl_pool_init(&atu->tbl, num_iotte, IO_PAGE_SHIFT,
			    शून्य, false /* no large_pool */,
			    0 /* शेष npools */,
			    false /* want span boundary checking */);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_sun4v_iommu_init(काष्ठा pci_pbm_info *pbm)
अणु
	अटल स्थिर u32 vdma_शेष[] = अणु 0x80000000, 0x80000000 पूर्ण;
	काष्ठा iommu *iommu = pbm->iommu;
	अचिन्हित दीर्घ num_tsb_entries, sz;
	u32 dma_mask, dma_offset;
	स्थिर u32 *vdma;

	vdma = of_get_property(pbm->op->dev.of_node, "virtual-dma", शून्य);
	अगर (!vdma)
		vdma = vdma_शेष;

	अगर ((vdma[0] | vdma[1]) & ~IO_PAGE_MASK) अणु
		prपूर्णांकk(KERN_ERR PFX "Strange virtual-dma[%08x:%08x].\n",
		       vdma[0], vdma[1]);
		वापस -EINVAL;
	पूर्ण

	dma_mask = (roundup_घात_of_two(vdma[1]) - 1UL);
	num_tsb_entries = vdma[1] / IO_PAGE_SIZE;

	dma_offset = vdma[0];

	/* Setup initial software IOMMU state. */
	spin_lock_init(&iommu->lock);
	iommu->ctx_lowest_मुक्त = 1;
	iommu->tbl.table_map_base = dma_offset;
	iommu->dma_addr_mask = dma_mask;

	/* Allocate and initialize the मुक्त area map.  */
	sz = (num_tsb_entries + 7) / 8;
	sz = (sz + 7UL) & ~7UL;
	iommu->tbl.map = kzalloc(sz, GFP_KERNEL);
	अगर (!iommu->tbl.map) अणु
		prपूर्णांकk(KERN_ERR PFX "Error, kmalloc(arena.map) failed.\n");
		वापस -ENOMEM;
	पूर्ण
	iommu_tbl_pool_init(&iommu->tbl, num_tsb_entries, IO_PAGE_SHIFT,
			    शून्य, false /* no large_pool */,
			    0 /* शेष npools */,
			    false /* want span boundary checking */);
	sz = probe_existing_entries(pbm, &iommu->tbl);
	अगर (sz)
		prपूर्णांकk("%s: Imported %lu TSB entries from OBP\n",
		       pbm->name, sz);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
काष्ठा pci_sun4v_msiq_entry अणु
	u64		version_type;
#घोषणा MSIQ_VERSION_MASK		0xffffffff00000000UL
#घोषणा MSIQ_VERSION_SHIFT		32
#घोषणा MSIQ_TYPE_MASK			0x00000000000000ffUL
#घोषणा MSIQ_TYPE_SHIFT			0
#घोषणा MSIQ_TYPE_NONE			0x00
#घोषणा MSIQ_TYPE_MSG			0x01
#घोषणा MSIQ_TYPE_MSI32			0x02
#घोषणा MSIQ_TYPE_MSI64			0x03
#घोषणा MSIQ_TYPE_INTX			0x08
#घोषणा MSIQ_TYPE_NONE2			0xff

	u64		पूर्णांकx_sysino;
	u64		reserved1;
	u64		stick;
	u64		req_id;  /* bus/device/func */
#घोषणा MSIQ_REQID_BUS_MASK		0xff00UL
#घोषणा MSIQ_REQID_BUS_SHIFT		8
#घोषणा MSIQ_REQID_DEVICE_MASK		0x00f8UL
#घोषणा MSIQ_REQID_DEVICE_SHIFT		3
#घोषणा MSIQ_REQID_FUNC_MASK		0x0007UL
#घोषणा MSIQ_REQID_FUNC_SHIFT		0

	u64		msi_address;

	/* The क्रमmat of this value is message type dependent.
	 * For MSI bits 15:0 are the data from the MSI packet.
	 * For MSI-X bits 31:0 are the data from the MSI packet.
	 * For MSG, the message code and message routing code where:
	 * 	bits 39:32 is the bus/device/fn of the msg target-id
	 *	bits 18:16 is the message routing code
	 *	bits 7:0 is the message code
	 * For INTx the low order 2-bits are:
	 *	00 - INTA
	 *	01 - INTB
	 *	10 - INTC
	 *	11 - INTD
	 */
	u64		msi_data;

	u64		reserved2;
पूर्ण;

अटल पूर्णांक pci_sun4v_get_head(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			      अचिन्हित दीर्घ *head)
अणु
	अचिन्हित दीर्घ err, limit;

	err = pci_sun4v_msiq_gethead(pbm->devhandle, msiqid, head);
	अगर (unlikely(err))
		वापस -ENXIO;

	limit = pbm->msiq_ent_count * माप(काष्ठा pci_sun4v_msiq_entry);
	अगर (unlikely(*head >= limit))
		वापस -EFBIG;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_sun4v_dequeue_msi(काष्ठा pci_pbm_info *pbm,
				 अचिन्हित दीर्घ msiqid, अचिन्हित दीर्घ *head,
				 अचिन्हित दीर्घ *msi)
अणु
	काष्ठा pci_sun4v_msiq_entry *ep;
	अचिन्हित दीर्घ err, type;

	/* Note: व्योम poपूर्णांकer arithmetic, 'head' is a byte offset  */
	ep = (pbm->msi_queues + ((msiqid - pbm->msiq_first) *
				 (pbm->msiq_ent_count *
				  माप(काष्ठा pci_sun4v_msiq_entry))) +
	      *head);

	अगर ((ep->version_type & MSIQ_TYPE_MASK) == 0)
		वापस 0;

	type = (ep->version_type & MSIQ_TYPE_MASK) >> MSIQ_TYPE_SHIFT;
	अगर (unlikely(type != MSIQ_TYPE_MSI32 &&
		     type != MSIQ_TYPE_MSI64))
		वापस -EINVAL;

	*msi = ep->msi_data;

	err = pci_sun4v_msi_setstate(pbm->devhandle,
				     ep->msi_data /* msi_num */,
				     HV_MSISTATE_IDLE);
	अगर (unlikely(err))
		वापस -ENXIO;

	/* Clear the entry.  */
	ep->version_type &= ~MSIQ_TYPE_MASK;

	(*head) += माप(काष्ठा pci_sun4v_msiq_entry);
	अगर (*head >=
	    (pbm->msiq_ent_count * माप(काष्ठा pci_sun4v_msiq_entry)))
		*head = 0;

	वापस 1;
पूर्ण

अटल पूर्णांक pci_sun4v_set_head(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			      अचिन्हित दीर्घ head)
अणु
	अचिन्हित दीर्घ err;

	err = pci_sun4v_msiq_sethead(pbm->devhandle, msiqid, head);
	अगर (unlikely(err))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_sun4v_msi_setup(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msiqid,
			       अचिन्हित दीर्घ msi, पूर्णांक is_msi64)
अणु
	अगर (pci_sun4v_msi_seपंचांगsiq(pbm->devhandle, msi, msiqid,
				  (is_msi64 ?
				   HV_MSITYPE_MSI64 : HV_MSITYPE_MSI32)))
		वापस -ENXIO;
	अगर (pci_sun4v_msi_setstate(pbm->devhandle, msi, HV_MSISTATE_IDLE))
		वापस -ENXIO;
	अगर (pci_sun4v_msi_setvalid(pbm->devhandle, msi, HV_MSIVALID_VALID))
		वापस -ENXIO;
	वापस 0;
पूर्ण

अटल पूर्णांक pci_sun4v_msi_tearकरोwn(काष्ठा pci_pbm_info *pbm, अचिन्हित दीर्घ msi)
अणु
	अचिन्हित दीर्घ err, msiqid;

	err = pci_sun4v_msi_geपंचांगsiq(pbm->devhandle, msi, &msiqid);
	अगर (err)
		वापस -ENXIO;

	pci_sun4v_msi_setvalid(pbm->devhandle, msi, HV_MSIVALID_INVALID);

	वापस 0;
पूर्ण

अटल पूर्णांक pci_sun4v_msiq_alloc(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ q_size, alloc_size, pages, order;
	पूर्णांक i;

	q_size = pbm->msiq_ent_count * माप(काष्ठा pci_sun4v_msiq_entry);
	alloc_size = (pbm->msiq_num * q_size);
	order = get_order(alloc_size);
	pages = __get_मुक्त_pages(GFP_KERNEL | __GFP_COMP, order);
	अगर (pages == 0UL) अणु
		prपूर्णांकk(KERN_ERR "MSI: Cannot allocate MSI queues (o=%lu).\n",
		       order);
		वापस -ENOMEM;
	पूर्ण
	स_रखो((अक्षर *)pages, 0, PAGE_SIZE << order);
	pbm->msi_queues = (व्योम *) pages;

	क्रम (i = 0; i < pbm->msiq_num; i++) अणु
		अचिन्हित दीर्घ err, base = __pa(pages + (i * q_size));
		अचिन्हित दीर्घ ret1, ret2;

		err = pci_sun4v_msiq_conf(pbm->devhandle,
					  pbm->msiq_first + i,
					  base, pbm->msiq_ent_count);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "MSI: msiq register fails (err=%lu)\n",
			       err);
			जाओ h_error;
		पूर्ण

		err = pci_sun4v_msiq_info(pbm->devhandle,
					  pbm->msiq_first + i,
					  &ret1, &ret2);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "MSI: Cannot read msiq (err=%lu)\n",
			       err);
			जाओ h_error;
		पूर्ण
		अगर (ret1 != base || ret2 != pbm->msiq_ent_count) अणु
			prपूर्णांकk(KERN_ERR "MSI: Bogus qconf "
			       "expected[%lx:%x] got[%lx:%lx]\n",
			       base, pbm->msiq_ent_count,
			       ret1, ret2);
			जाओ h_error;
		पूर्ण
	पूर्ण

	वापस 0;

h_error:
	मुक्त_pages(pages, order);
	वापस -EINVAL;
पूर्ण

अटल व्योम pci_sun4v_msiq_मुक्त(काष्ठा pci_pbm_info *pbm)
अणु
	अचिन्हित दीर्घ q_size, alloc_size, pages, order;
	पूर्णांक i;

	क्रम (i = 0; i < pbm->msiq_num; i++) अणु
		अचिन्हित दीर्घ msiqid = pbm->msiq_first + i;

		(व्योम) pci_sun4v_msiq_conf(pbm->devhandle, msiqid, 0UL, 0);
	पूर्ण

	q_size = pbm->msiq_ent_count * माप(काष्ठा pci_sun4v_msiq_entry);
	alloc_size = (pbm->msiq_num * q_size);
	order = get_order(alloc_size);

	pages = (अचिन्हित दीर्घ) pbm->msi_queues;

	मुक्त_pages(pages, order);

	pbm->msi_queues = शून्य;
पूर्ण

अटल पूर्णांक pci_sun4v_msiq_build_irq(काष्ठा pci_pbm_info *pbm,
				    अचिन्हित दीर्घ msiqid,
				    अचिन्हित दीर्घ devino)
अणु
	अचिन्हित पूर्णांक irq = sun4v_build_irq(pbm->devhandle, devino);

	अगर (!irq)
		वापस -ENOMEM;

	अगर (pci_sun4v_msiq_setvalid(pbm->devhandle, msiqid, HV_MSIQ_VALID))
		वापस -EINVAL;
	अगर (pci_sun4v_msiq_setstate(pbm->devhandle, msiqid, HV_MSIQSTATE_IDLE))
		वापस -EINVAL;

	वापस irq;
पूर्ण

अटल स्थिर काष्ठा sparc64_msiq_ops pci_sun4v_msiq_ops = अणु
	.get_head	=	pci_sun4v_get_head,
	.dequeue_msi	=	pci_sun4v_dequeue_msi,
	.set_head	=	pci_sun4v_set_head,
	.msi_setup	=	pci_sun4v_msi_setup,
	.msi_tearकरोwn	=	pci_sun4v_msi_tearकरोwn,
	.msiq_alloc	=	pci_sun4v_msiq_alloc,
	.msiq_मुक्त	=	pci_sun4v_msiq_मुक्त,
	.msiq_build_irq	=	pci_sun4v_msiq_build_irq,
पूर्ण;

अटल व्योम pci_sun4v_msi_init(काष्ठा pci_pbm_info *pbm)
अणु
	sparc64_pbm_msi_init(pbm, &pci_sun4v_msiq_ops);
पूर्ण
#अन्यथा /* CONFIG_PCI_MSI */
अटल व्योम pci_sun4v_msi_init(काष्ठा pci_pbm_info *pbm)
अणु
पूर्ण
#पूर्ण_अगर /* !(CONFIG_PCI_MSI) */

अटल पूर्णांक pci_sun4v_pbm_init(काष्ठा pci_pbm_info *pbm,
			      काष्ठा platक्रमm_device *op, u32 devhandle)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	पूर्णांक err;

	pbm->numa_node = of_node_to_nid(dp);

	pbm->pci_ops = &sun4v_pci_ops;
	pbm->config_space_reg_bits = 12;

	pbm->index = pci_num_pbms++;

	pbm->op = op;

	pbm->devhandle = devhandle;

	pbm->name = dp->full_name;

	prपूर्णांकk("%s: SUN4V PCI Bus Module\n", pbm->name);
	prपूर्णांकk("%s: On NUMA node %d\n", pbm->name, pbm->numa_node);

	pci_determine_mem_io_space(pbm);

	pci_get_pbm_props(pbm);

	err = pci_sun4v_iommu_init(pbm);
	अगर (err)
		वापस err;

	pci_sun4v_msi_init(pbm);

	pci_sun4v_scan_bus(pbm, &op->dev);

	/* अगर atu_init fails its not complete failure.
	 * we can still जारी using legacy iommu.
	 */
	अगर (pbm->iommu->atu) अणु
		err = pci_sun4v_atu_init(pbm);
		अगर (err) अणु
			kमुक्त(pbm->iommu->atu);
			pbm->iommu->atu = शून्य;
			pr_err(PFX "ATU init failed, err=%d\n", err);
		पूर्ण
	पूर्ण

	pbm->next = pci_pbm_root;
	pci_pbm_root = pbm;

	वापस 0;
पूर्ण

अटल पूर्णांक pci_sun4v_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *regs;
	अटल पूर्णांक hvapi_negotiated = 0;
	काष्ठा pci_pbm_info *pbm;
	काष्ठा device_node *dp;
	काष्ठा iommu *iommu;
	काष्ठा atu *atu;
	u32 devhandle;
	पूर्णांक i, err = -ENODEV;
	अटल bool hv_atu = true;

	dp = op->dev.of_node;

	अगर (!hvapi_negotiated++) अणु
		क्रम (i = 0; i < ARRAY_SIZE(vpci_versions); i++) अणु
			vpci_major = vpci_versions[i].major;
			vpci_minor = vpci_versions[i].minor;

			err = sun4v_hvapi_रेजिस्टर(HV_GRP_PCI, vpci_major,
						   &vpci_minor);
			अगर (!err)
				अवरोध;
		पूर्ण

		अगर (err) अणु
			pr_err(PFX "Could not register hvapi, err=%d\n", err);
			वापस err;
		पूर्ण
		pr_info(PFX "Registered hvapi major[%lu] minor[%lu]\n",
			vpci_major, vpci_minor);

		err = sun4v_hvapi_रेजिस्टर(HV_GRP_ATU, vatu_major, &vatu_minor);
		अगर (err) अणु
			/* करोn't वापस an error अगर we fail to रेजिस्टर the
			 * ATU group, but ATU hcalls won't be available.
			 */
			hv_atu = false;
		पूर्ण अन्यथा अणु
			pr_info(PFX "Registered hvapi ATU major[%lu] minor[%lu]\n",
				vatu_major, vatu_minor);
		पूर्ण

		dma_ops = &sun4v_dma_ops;
	पूर्ण

	regs = of_get_property(dp, "reg", शून्य);
	err = -ENODEV;
	अगर (!regs) अणु
		prपूर्णांकk(KERN_ERR PFX "Could not find config registers\n");
		जाओ out_err;
	पूर्ण
	devhandle = (regs->phys_addr >> 32UL) & 0x0fffffff;

	err = -ENOMEM;
	अगर (!iommu_batch_initialized) अणु
		क्रम_each_possible_cpu(i) अणु
			अचिन्हित दीर्घ page = get_zeroed_page(GFP_KERNEL);

			अगर (!page)
				जाओ out_err;

			per_cpu(iommu_batch, i).pglist = (u64 *) page;
		पूर्ण
		iommu_batch_initialized = 1;
	पूर्ण

	pbm = kzalloc(माप(*pbm), GFP_KERNEL);
	अगर (!pbm) अणु
		prपूर्णांकk(KERN_ERR PFX "Could not allocate pci_pbm_info\n");
		जाओ out_err;
	पूर्ण

	iommu = kzalloc(माप(काष्ठा iommu), GFP_KERNEL);
	अगर (!iommu) अणु
		prपूर्णांकk(KERN_ERR PFX "Could not allocate pbm iommu\n");
		जाओ out_मुक्त_controller;
	पूर्ण

	pbm->iommu = iommu;
	iommu->atu = शून्य;
	अगर (hv_atu) अणु
		atu = kzalloc(माप(*atu), GFP_KERNEL);
		अगर (!atu)
			pr_err(PFX "Could not allocate atu\n");
		अन्यथा
			iommu->atu = atu;
	पूर्ण

	err = pci_sun4v_pbm_init(pbm, op, devhandle);
	अगर (err)
		जाओ out_मुक्त_iommu;

	dev_set_drvdata(&op->dev, pbm);

	वापस 0;

out_मुक्त_iommu:
	kमुक्त(iommu->atu);
	kमुक्त(pbm->iommu);

out_मुक्त_controller:
	kमुक्त(pbm);

out_err:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा of_device_id pci_sun4v_match[] = अणु
	अणु
		.name = "pci",
		.compatible = "SUNW,sun4v-pci",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver pci_sun4v_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = pci_sun4v_match,
	पूर्ण,
	.probe		= pci_sun4v_probe,
पूर्ण;

अटल पूर्णांक __init pci_sun4v_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&pci_sun4v_driver);
पूर्ण

subsys_initcall(pci_sun4v_init);
