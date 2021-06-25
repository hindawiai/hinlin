<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2006 Benjamin Herrenschmidt, IBM Corporation
 *
 * Provide शेष implementations of the DMA mapping callbacks क्रम
 * busses using the iommu infraकाष्ठाure
 */

#समावेश <linux/dma-direct.h>
#समावेश <linux/pci.h>
#समावेश <यंत्र/iommu.h>

#अगर_घोषित CONFIG_ARCH_HAS_DMA_MAP_सूचीECT
#घोषणा can_map_direct(dev, addr) \
	((dev)->bus_dma_limit >= phys_to_dma((dev), (addr)))

bool arch_dma_map_page_direct(काष्ठा device *dev, phys_addr_t addr)
अणु
	अगर (likely(!dev->bus_dma_limit))
		वापस false;

	वापस can_map_direct(dev, addr);
पूर्ण

#घोषणा is_direct_handle(dev, h) ((h) >= (dev)->archdata.dma_offset)

bool arch_dma_unmap_page_direct(काष्ठा device *dev, dma_addr_t dma_handle)
अणु
	अगर (likely(!dev->bus_dma_limit))
		वापस false;

	वापस is_direct_handle(dev, dma_handle);
पूर्ण

bool arch_dma_map_sg_direct(काष्ठा device *dev, काष्ठा scatterlist *sg,
			    पूर्णांक nents)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	अगर (likely(!dev->bus_dma_limit))
		वापस false;

	क्रम_each_sg(sg, s, nents, i) अणु
		अगर (!can_map_direct(dev, sg_phys(s) + s->offset + s->length))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool arch_dma_unmap_sg_direct(काष्ठा device *dev, काष्ठा scatterlist *sg,
			      पूर्णांक nents)
अणु
	काष्ठा scatterlist *s;
	पूर्णांक i;

	अगर (likely(!dev->bus_dma_limit))
		वापस false;

	क्रम_each_sg(sg, s, nents, i) अणु
		अगर (!is_direct_handle(dev, s->dma_address + s->length))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_DMA_MAP_सूचीECT */

/*
 * Generic iommu implementation
 */

/* Allocates a contiguous real buffer and creates mappings over it.
 * Returns the भव address of the buffer and sets dma_handle
 * to the dma address (mapping) of the first page.
 */
अटल व्योम *dma_iommu_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
				      dma_addr_t *dma_handle, gfp_t flag,
				      अचिन्हित दीर्घ attrs)
अणु
	वापस iommu_alloc_coherent(dev, get_iommu_table_base(dev), size,
				    dma_handle, dev->coherent_dma_mask, flag,
				    dev_to_node(dev));
पूर्ण

अटल व्योम dma_iommu_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
				    व्योम *vaddr, dma_addr_t dma_handle,
				    अचिन्हित दीर्घ attrs)
अणु
	iommu_मुक्त_coherent(get_iommu_table_base(dev), size, vaddr, dma_handle);
पूर्ण

/* Creates TCEs क्रम a user provided buffer.  The user buffer must be
 * contiguous real kernel storage (not vदो_स्मृति).  The address passed here
 * comprises a page address and offset पूर्णांकo that page. The dma_addr_t
 * वापसed will poपूर्णांक to the same byte within the page as was passed in.
 */
अटल dma_addr_t dma_iommu_map_page(काष्ठा device *dev, काष्ठा page *page,
				     अचिन्हित दीर्घ offset, माप_प्रकार size,
				     क्रमागत dma_data_direction direction,
				     अचिन्हित दीर्घ attrs)
अणु
	वापस iommu_map_page(dev, get_iommu_table_base(dev), page, offset,
			      size, dma_get_mask(dev), direction, attrs);
पूर्ण


अटल व्योम dma_iommu_unmap_page(काष्ठा device *dev, dma_addr_t dma_handle,
				 माप_प्रकार size, क्रमागत dma_data_direction direction,
				 अचिन्हित दीर्घ attrs)
अणु
	iommu_unmap_page(get_iommu_table_base(dev), dma_handle, size, direction,
			 attrs);
पूर्ण


अटल पूर्णांक dma_iommu_map_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
			    पूर्णांक nelems, क्रमागत dma_data_direction direction,
			    अचिन्हित दीर्घ attrs)
अणु
	वापस ppc_iommu_map_sg(dev, get_iommu_table_base(dev), sglist, nelems,
				dma_get_mask(dev), direction, attrs);
पूर्ण

अटल व्योम dma_iommu_unmap_sg(काष्ठा device *dev, काष्ठा scatterlist *sglist,
		पूर्णांक nelems, क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	ppc_iommu_unmap_sg(get_iommu_table_base(dev), sglist, nelems,
			   direction, attrs);
पूर्ण

अटल bool dma_iommu_bypass_supported(काष्ठा device *dev, u64 mask)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा pci_controller *phb = pci_bus_to_host(pdev->bus);

	अगर (iommu_fixed_is_weak || !phb->controller_ops.iommu_bypass_supported)
		वापस false;
	वापस phb->controller_ops.iommu_bypass_supported(pdev, mask);
पूर्ण

/* We support DMA to/from any memory page via the iommu */
पूर्णांक dma_iommu_dma_supported(काष्ठा device *dev, u64 mask)
अणु
	काष्ठा iommu_table *tbl = get_iommu_table_base(dev);

	अगर (dev_is_pci(dev) && dma_iommu_bypass_supported(dev, mask)) अणु
		/*
		 * dma_iommu_bypass_supported() sets dma_max when there is
		 * 1:1 mapping but it is somehow limited.
		 * ibm,pmemory is one example.
		 */
		dev->dma_ops_bypass = dev->bus_dma_limit == 0;
		अगर (!dev->dma_ops_bypass)
			dev_warn(dev,
				 "iommu: 64-bit OK but direct DMA is limited by %llx\n",
				 dev->bus_dma_limit);
		अन्यथा
			dev_dbg(dev, "iommu: 64-bit OK, using fixed ops\n");
		वापस 1;
	पूर्ण

	अगर (!tbl) अणु
		dev_err(dev, "Warning: IOMMU dma not supported: mask 0x%08llx, table unavailable\n", mask);
		वापस 0;
	पूर्ण

	अगर (tbl->it_offset > (mask >> tbl->it_page_shअगरt)) अणु
		dev_info(dev, "Warning: IOMMU offset too big for device mask\n");
		dev_info(dev, "mask: 0x%08llx, table offset: 0x%08lx\n",
				mask, tbl->it_offset << tbl->it_page_shअगरt);
		वापस 0;
	पूर्ण

	dev_dbg(dev, "iommu: not 64-bit, using default ops\n");
	dev->dma_ops_bypass = false;
	वापस 1;
पूर्ण

u64 dma_iommu_get_required_mask(काष्ठा device *dev)
अणु
	काष्ठा iommu_table *tbl = get_iommu_table_base(dev);
	u64 mask;

	अगर (!tbl)
		वापस 0;

	mask = 1ULL << (fls_दीर्घ(tbl->it_offset + tbl->it_size) +
			tbl->it_page_shअगरt - 1);
	mask += mask - 1;

	वापस mask;
पूर्ण

स्थिर काष्ठा dma_map_ops dma_iommu_ops = अणु
	.alloc			= dma_iommu_alloc_coherent,
	.मुक्त			= dma_iommu_मुक्त_coherent,
	.map_sg			= dma_iommu_map_sg,
	.unmap_sg		= dma_iommu_unmap_sg,
	.dma_supported		= dma_iommu_dma_supported,
	.map_page		= dma_iommu_map_page,
	.unmap_page		= dma_iommu_unmap_page,
	.get_required_mask	= dma_iommu_get_required_mask,
	.mmap			= dma_common_mmap,
	.get_sgtable		= dma_common_get_sgtable,
	.alloc_pages		= dma_common_alloc_pages,
	.मुक्त_pages		= dma_common_मुक्त_pages,
पूर्ण;
