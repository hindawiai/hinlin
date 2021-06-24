<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch-independent dma-mapping routines
 *
 * Copyright (c) 2006  SUSE Linux Products GmbH
 * Copyright (c) 2006  Tejun Heo <teheo@suse.de>
 */
#समावेश <linux/memblock.h> /* क्रम max_pfn */
#समावेश <linux/acpi.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/export.h>
#समावेश <linux/gfp.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "debug.h"
#समावेश "direct.h"

bool dma_शेष_coherent;

/*
 * Managed DMA API
 */
काष्ठा dma_devres अणु
	माप_प्रकार		size;
	व्योम		*vaddr;
	dma_addr_t	dma_handle;
	अचिन्हित दीर्घ	attrs;
पूर्ण;

अटल व्योम dmam_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा dma_devres *this = res;

	dma_मुक्त_attrs(dev, this->size, this->vaddr, this->dma_handle,
			this->attrs);
पूर्ण

अटल पूर्णांक dmam_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	काष्ठा dma_devres *this = res, *match = match_data;

	अगर (this->vaddr == match->vaddr) अणु
		WARN_ON(this->size != match->size ||
			this->dma_handle != match->dma_handle);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dmam_मुक्त_coherent - Managed dma_मुक्त_coherent()
 * @dev: Device to मुक्त coherent memory क्रम
 * @size: Size of allocation
 * @vaddr: Virtual address of the memory to मुक्त
 * @dma_handle: DMA handle of the memory to मुक्त
 *
 * Managed dma_मुक्त_coherent().
 */
व्योम dmam_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
			dma_addr_t dma_handle)
अणु
	काष्ठा dma_devres match_data = अणु size, vaddr, dma_handle पूर्ण;

	dma_मुक्त_coherent(dev, size, vaddr, dma_handle);
	WARN_ON(devres_destroy(dev, dmam_release, dmam_match, &match_data));
पूर्ण
EXPORT_SYMBOL(dmam_मुक्त_coherent);

/**
 * dmam_alloc_attrs - Managed dma_alloc_attrs()
 * @dev: Device to allocate non_coherent memory क्रम
 * @size: Size of allocation
 * @dma_handle: Out argument क्रम allocated DMA handle
 * @gfp: Allocation flags
 * @attrs: Flags in the DMA_ATTR_* namespace.
 *
 * Managed dma_alloc_attrs().  Memory allocated using this function will be
 * स्वतःmatically released on driver detach.
 *
 * RETURNS:
 * Poपूर्णांकer to allocated memory on success, शून्य on failure.
 */
व्योम *dmam_alloc_attrs(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	काष्ठा dma_devres *dr;
	व्योम *vaddr;

	dr = devres_alloc(dmam_release, माप(*dr), gfp);
	अगर (!dr)
		वापस शून्य;

	vaddr = dma_alloc_attrs(dev, size, dma_handle, gfp, attrs);
	अगर (!vaddr) अणु
		devres_मुक्त(dr);
		वापस शून्य;
	पूर्ण

	dr->vaddr = vaddr;
	dr->dma_handle = *dma_handle;
	dr->size = size;
	dr->attrs = attrs;

	devres_add(dev, dr);

	वापस vaddr;
पूर्ण
EXPORT_SYMBOL(dmam_alloc_attrs);

अटल bool dma_go_direct(काष्ठा device *dev, dma_addr_t mask,
		स्थिर काष्ठा dma_map_ops *ops)
अणु
	अगर (likely(!ops))
		वापस true;
#अगर_घोषित CONFIG_DMA_OPS_BYPASS
	अगर (dev->dma_ops_bypass)
		वापस min_not_zero(mask, dev->bus_dma_limit) >=
			    dma_direct_get_required_mask(dev);
#पूर्ण_अगर
	वापस false;
पूर्ण


/*
 * Check अगर the devices uses a direct mapping क्रम streaming DMA operations.
 * This allows IOMMU drivers to set a bypass mode अगर the DMA mask is large
 * enough.
 */
अटल अंतरभूत bool dma_alloc_direct(काष्ठा device *dev,
		स्थिर काष्ठा dma_map_ops *ops)
अणु
	वापस dma_go_direct(dev, dev->coherent_dma_mask, ops);
पूर्ण

अटल अंतरभूत bool dma_map_direct(काष्ठा device *dev,
		स्थिर काष्ठा dma_map_ops *ops)
अणु
	वापस dma_go_direct(dev, *dev->dma_mask, ops);
पूर्ण

dma_addr_t dma_map_page_attrs(काष्ठा device *dev, काष्ठा page *page,
		माप_प्रकार offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	dma_addr_t addr;

	BUG_ON(!valid_dma_direction(dir));

	अगर (WARN_ON_ONCE(!dev->dma_mask))
		वापस DMA_MAPPING_ERROR;

	अगर (dma_map_direct(dev, ops) ||
	    arch_dma_map_page_direct(dev, page_to_phys(page) + offset + size))
		addr = dma_direct_map_page(dev, page, offset, size, dir, attrs);
	अन्यथा
		addr = ops->map_page(dev, page, offset, size, dir, attrs);
	debug_dma_map_page(dev, page, offset, size, dir, addr);

	वापस addr;
पूर्ण
EXPORT_SYMBOL(dma_map_page_attrs);

व्योम dma_unmap_page_attrs(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!valid_dma_direction(dir));
	अगर (dma_map_direct(dev, ops) ||
	    arch_dma_unmap_page_direct(dev, addr + size))
		dma_direct_unmap_page(dev, addr, size, dir, attrs);
	अन्यथा अगर (ops->unmap_page)
		ops->unmap_page(dev, addr, size, dir, attrs);
	debug_dma_unmap_page(dev, addr, size, dir);
पूर्ण
EXPORT_SYMBOL(dma_unmap_page_attrs);

/*
 * dma_maps_sg_attrs वापसs 0 on error and > 0 on success.
 * It should never वापस a value < 0.
 */
पूर्णांक dma_map_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	पूर्णांक ents;

	BUG_ON(!valid_dma_direction(dir));

	अगर (WARN_ON_ONCE(!dev->dma_mask))
		वापस 0;

	अगर (dma_map_direct(dev, ops) ||
	    arch_dma_map_sg_direct(dev, sg, nents))
		ents = dma_direct_map_sg(dev, sg, nents, dir, attrs);
	अन्यथा
		ents = ops->map_sg(dev, sg, nents, dir, attrs);
	BUG_ON(ents < 0);
	debug_dma_map_sg(dev, sg, nents, ents, dir);

	वापस ents;
पूर्ण
EXPORT_SYMBOL(dma_map_sg_attrs);

व्योम dma_unmap_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg,
				      पूर्णांक nents, क्रमागत dma_data_direction dir,
				      अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!valid_dma_direction(dir));
	debug_dma_unmap_sg(dev, sg, nents, dir);
	अगर (dma_map_direct(dev, ops) ||
	    arch_dma_unmap_sg_direct(dev, sg, nents))
		dma_direct_unmap_sg(dev, sg, nents, dir, attrs);
	अन्यथा अगर (ops->unmap_sg)
		ops->unmap_sg(dev, sg, nents, dir, attrs);
पूर्ण
EXPORT_SYMBOL(dma_unmap_sg_attrs);

dma_addr_t dma_map_resource(काष्ठा device *dev, phys_addr_t phys_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	dma_addr_t addr = DMA_MAPPING_ERROR;

	BUG_ON(!valid_dma_direction(dir));

	अगर (WARN_ON_ONCE(!dev->dma_mask))
		वापस DMA_MAPPING_ERROR;

	/* Don't allow RAM to be mapped */
	अगर (WARN_ON_ONCE(pfn_valid(PHYS_PFN(phys_addr))))
		वापस DMA_MAPPING_ERROR;

	अगर (dma_map_direct(dev, ops))
		addr = dma_direct_map_resource(dev, phys_addr, size, dir, attrs);
	अन्यथा अगर (ops->map_resource)
		addr = ops->map_resource(dev, phys_addr, size, dir, attrs);

	debug_dma_map_resource(dev, phys_addr, size, dir, addr);
	वापस addr;
पूर्ण
EXPORT_SYMBOL(dma_map_resource);

व्योम dma_unmap_resource(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!valid_dma_direction(dir));
	अगर (!dma_map_direct(dev, ops) && ops->unmap_resource)
		ops->unmap_resource(dev, addr, size, dir, attrs);
	debug_dma_unmap_resource(dev, addr, size, dir);
पूर्ण
EXPORT_SYMBOL(dma_unmap_resource);

व्योम dma_sync_single_क्रम_cpu(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!valid_dma_direction(dir));
	अगर (dma_map_direct(dev, ops))
		dma_direct_sync_single_क्रम_cpu(dev, addr, size, dir);
	अन्यथा अगर (ops->sync_single_क्रम_cpu)
		ops->sync_single_क्रम_cpu(dev, addr, size, dir);
	debug_dma_sync_single_क्रम_cpu(dev, addr, size, dir);
पूर्ण
EXPORT_SYMBOL(dma_sync_single_क्रम_cpu);

व्योम dma_sync_single_क्रम_device(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!valid_dma_direction(dir));
	अगर (dma_map_direct(dev, ops))
		dma_direct_sync_single_क्रम_device(dev, addr, size, dir);
	अन्यथा अगर (ops->sync_single_क्रम_device)
		ops->sync_single_क्रम_device(dev, addr, size, dir);
	debug_dma_sync_single_क्रम_device(dev, addr, size, dir);
पूर्ण
EXPORT_SYMBOL(dma_sync_single_क्रम_device);

व्योम dma_sync_sg_क्रम_cpu(काष्ठा device *dev, काष्ठा scatterlist *sg,
		    पूर्णांक nelems, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!valid_dma_direction(dir));
	अगर (dma_map_direct(dev, ops))
		dma_direct_sync_sg_क्रम_cpu(dev, sg, nelems, dir);
	अन्यथा अगर (ops->sync_sg_क्रम_cpu)
		ops->sync_sg_क्रम_cpu(dev, sg, nelems, dir);
	debug_dma_sync_sg_क्रम_cpu(dev, sg, nelems, dir);
पूर्ण
EXPORT_SYMBOL(dma_sync_sg_क्रम_cpu);

व्योम dma_sync_sg_क्रम_device(काष्ठा device *dev, काष्ठा scatterlist *sg,
		       पूर्णांक nelems, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	BUG_ON(!valid_dma_direction(dir));
	अगर (dma_map_direct(dev, ops))
		dma_direct_sync_sg_क्रम_device(dev, sg, nelems, dir);
	अन्यथा अगर (ops->sync_sg_क्रम_device)
		ops->sync_sg_क्रम_device(dev, sg, nelems, dir);
	debug_dma_sync_sg_क्रम_device(dev, sg, nelems, dir);
पूर्ण
EXPORT_SYMBOL(dma_sync_sg_क्रम_device);

/*
 * The whole dma_get_sgtable() idea is fundamentally unsafe - it seems
 * that the पूर्णांकention is to allow exporting memory allocated via the
 * coherent DMA APIs through the dma_buf API, which only accepts a
 * scattertable.  This presents a couple of problems:
 * 1. Not all memory allocated via the coherent DMA APIs is backed by
 *    a काष्ठा page
 * 2. Passing coherent DMA memory पूर्णांकo the streaming APIs is not allowed
 *    as we will try to flush the memory through a dअगरferent alias to that
 *    actually being used (and the flushes are redundant.)
 */
पूर्णांक dma_get_sgtable_attrs(काष्ठा device *dev, काष्ठा sg_table *sgt,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (dma_alloc_direct(dev, ops))
		वापस dma_direct_get_sgtable(dev, sgt, cpu_addr, dma_addr,
				size, attrs);
	अगर (!ops->get_sgtable)
		वापस -ENXIO;
	वापस ops->get_sgtable(dev, sgt, cpu_addr, dma_addr, size, attrs);
पूर्ण
EXPORT_SYMBOL(dma_get_sgtable_attrs);

#अगर_घोषित CONFIG_MMU
/*
 * Return the page attributes used क्रम mapping dma_alloc_* memory, either in
 * kernel space अगर remapping is needed, or to userspace through dma_mmap_*.
 */
pgprot_t dma_pgprot(काष्ठा device *dev, pgprot_t prot, अचिन्हित दीर्घ attrs)
अणु
	अगर (क्रमce_dma_unencrypted(dev))
		prot = pgprot_decrypted(prot);
	अगर (dev_is_dma_coherent(dev))
		वापस prot;
#अगर_घोषित CONFIG_ARCH_HAS_DMA_WRITE_COMBINE
	अगर (attrs & DMA_ATTR_WRITE_COMBINE)
		वापस pgprot_ग_लिखोcombine(prot);
#पूर्ण_अगर
	वापस pgprot_dmacoherent(prot);
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

/**
 * dma_can_mmap - check अगर a given device supports dma_mmap_*
 * @dev: device to check
 *
 * Returns %true अगर @dev supports dma_mmap_coherent() and dma_mmap_attrs() to
 * map DMA allocations to userspace.
 */
bool dma_can_mmap(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (dma_alloc_direct(dev, ops))
		वापस dma_direct_can_mmap(dev);
	वापस ops->mmap != शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(dma_can_mmap);

/**
 * dma_mmap_attrs - map a coherent DMA allocation पूर्णांकo user space
 * @dev: valid काष्ठा device poपूर्णांकer, or शून्य क्रम ISA and EISA-like devices
 * @vma: vm_area_काष्ठा describing requested user mapping
 * @cpu_addr: kernel CPU-view address वापसed from dma_alloc_attrs
 * @dma_addr: device-view address वापसed from dma_alloc_attrs
 * @size: size of memory originally requested in dma_alloc_attrs
 * @attrs: attributes of mapping properties requested in dma_alloc_attrs
 *
 * Map a coherent DMA buffer previously allocated by dma_alloc_attrs पूर्णांकo user
 * space.  The coherent DMA buffer must not be मुक्तd by the driver until the
 * user space mapping has been released.
 */
पूर्णांक dma_mmap_attrs(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (dma_alloc_direct(dev, ops))
		वापस dma_direct_mmap(dev, vma, cpu_addr, dma_addr, size,
				attrs);
	अगर (!ops->mmap)
		वापस -ENXIO;
	वापस ops->mmap(dev, vma, cpu_addr, dma_addr, size, attrs);
पूर्ण
EXPORT_SYMBOL(dma_mmap_attrs);

u64 dma_get_required_mask(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (dma_alloc_direct(dev, ops))
		वापस dma_direct_get_required_mask(dev);
	अगर (ops->get_required_mask)
		वापस ops->get_required_mask(dev);

	/*
	 * We require every DMA ops implementation to at least support a 32-bit
	 * DMA mask (and use bounce buffering अगर that isn't supported in
	 * hardware).  As the direct mapping code has its own routine to
	 * actually report an optimal mask we शेष to 32-bit here as that
	 * is the right thing क्रम most IOMMUs, and at least not actively
	 * harmful in general.
	 */
	वापस DMA_BIT_MASK(32);
पूर्ण
EXPORT_SYMBOL_GPL(dma_get_required_mask);

व्योम *dma_alloc_attrs(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t flag, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	व्योम *cpu_addr;

	WARN_ON_ONCE(!dev->coherent_dma_mask);

	अगर (dma_alloc_from_dev_coherent(dev, size, dma_handle, &cpu_addr))
		वापस cpu_addr;

	/* let the implementation decide on the zone to allocate from: */
	flag &= ~(__GFP_DMA | __GFP_DMA32 | __GFP_HIGHMEM);

	अगर (dma_alloc_direct(dev, ops))
		cpu_addr = dma_direct_alloc(dev, size, dma_handle, flag, attrs);
	अन्यथा अगर (ops->alloc)
		cpu_addr = ops->alloc(dev, size, dma_handle, flag, attrs);
	अन्यथा
		वापस शून्य;

	debug_dma_alloc_coherent(dev, size, *dma_handle, cpu_addr);
	वापस cpu_addr;
पूर्ण
EXPORT_SYMBOL(dma_alloc_attrs);

व्योम dma_मुक्त_attrs(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (dma_release_from_dev_coherent(dev, get_order(size), cpu_addr))
		वापस;
	/*
	 * On non-coherent platक्रमms which implement DMA-coherent buffers via
	 * non-cacheable remaps, ops->मुक्त() may call vunmap(). Thus getting
	 * this far in IRQ context is a) at risk of a BUG_ON() or trying to
	 * sleep on some machines, and b) an indication that the driver is
	 * probably misusing the coherent API anyway.
	 */
	WARN_ON(irqs_disabled());

	अगर (!cpu_addr)
		वापस;

	debug_dma_मुक्त_coherent(dev, size, cpu_addr, dma_handle);
	अगर (dma_alloc_direct(dev, ops))
		dma_direct_मुक्त(dev, size, cpu_addr, dma_handle, attrs);
	अन्यथा अगर (ops->मुक्त)
		ops->मुक्त(dev, size, cpu_addr, dma_handle, attrs);
पूर्ण
EXPORT_SYMBOL(dma_मुक्त_attrs);

अटल काष्ठा page *__dma_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (WARN_ON_ONCE(!dev->coherent_dma_mask))
		वापस शून्य;
	अगर (WARN_ON_ONCE(gfp & (__GFP_DMA | __GFP_DMA32 | __GFP_HIGHMEM)))
		वापस शून्य;

	size = PAGE_ALIGN(size);
	अगर (dma_alloc_direct(dev, ops))
		वापस dma_direct_alloc_pages(dev, size, dma_handle, dir, gfp);
	अगर (!ops->alloc_pages)
		वापस शून्य;
	वापस ops->alloc_pages(dev, size, dma_handle, dir, gfp);
पूर्ण

काष्ठा page *dma_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp)
अणु
	काष्ठा page *page = __dma_alloc_pages(dev, size, dma_handle, dir, gfp);

	अगर (page)
		debug_dma_map_page(dev, page, 0, size, dir, *dma_handle);
	वापस page;
पूर्ण
EXPORT_SYMBOL_GPL(dma_alloc_pages);

अटल व्योम __dma_मुक्त_pages(काष्ठा device *dev, माप_प्रकार size, काष्ठा page *page,
		dma_addr_t dma_handle, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	size = PAGE_ALIGN(size);
	अगर (dma_alloc_direct(dev, ops))
		dma_direct_मुक्त_pages(dev, size, page, dma_handle, dir);
	अन्यथा अगर (ops->मुक्त_pages)
		ops->मुक्त_pages(dev, size, page, dma_handle, dir);
पूर्ण

व्योम dma_मुक्त_pages(काष्ठा device *dev, माप_प्रकार size, काष्ठा page *page,
		dma_addr_t dma_handle, क्रमागत dma_data_direction dir)
अणु
	debug_dma_unmap_page(dev, dma_handle, size, dir);
	__dma_मुक्त_pages(dev, size, page, dma_handle, dir);
पूर्ण
EXPORT_SYMBOL_GPL(dma_मुक्त_pages);

पूर्णांक dma_mmap_pages(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		माप_प्रकार size, काष्ठा page *page)
अणु
	अचिन्हित दीर्घ count = PAGE_ALIGN(size) >> PAGE_SHIFT;

	अगर (vma->vm_pgoff >= count || vma_pages(vma) > count - vma->vm_pgoff)
		वापस -ENXIO;
	वापस remap_pfn_range(vma, vma->vm_start,
			       page_to_pfn(page) + vma->vm_pgoff,
			       vma_pages(vma) << PAGE_SHIFT, vma->vm_page_prot);
पूर्ण
EXPORT_SYMBOL_GPL(dma_mmap_pages);

अटल काष्ठा sg_table *alloc_single_sgt(काष्ठा device *dev, माप_प्रकार size,
		क्रमागत dma_data_direction dir, gfp_t gfp)
अणु
	काष्ठा sg_table *sgt;
	काष्ठा page *page;

	sgt = kदो_स्मृति(माप(*sgt), gfp);
	अगर (!sgt)
		वापस शून्य;
	अगर (sg_alloc_table(sgt, 1, gfp))
		जाओ out_मुक्त_sgt;
	page = __dma_alloc_pages(dev, size, &sgt->sgl->dma_address, dir, gfp);
	अगर (!page)
		जाओ out_मुक्त_table;
	sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	sg_dma_len(sgt->sgl) = sgt->sgl->length;
	वापस sgt;
out_मुक्त_table:
	sg_मुक्त_table(sgt);
out_मुक्त_sgt:
	kमुक्त(sgt);
	वापस शून्य;
पूर्ण

काष्ठा sg_table *dma_alloc_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		क्रमागत dma_data_direction dir, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	काष्ठा sg_table *sgt;

	अगर (WARN_ON_ONCE(attrs & ~DMA_ATTR_ALLOC_SINGLE_PAGES))
		वापस शून्य;

	अगर (ops && ops->alloc_noncontiguous)
		sgt = ops->alloc_noncontiguous(dev, size, dir, gfp, attrs);
	अन्यथा
		sgt = alloc_single_sgt(dev, size, dir, gfp);

	अगर (sgt) अणु
		sgt->nents = 1;
		debug_dma_map_sg(dev, sgt->sgl, sgt->orig_nents, 1, dir);
	पूर्ण
	वापस sgt;
पूर्ण
EXPORT_SYMBOL_GPL(dma_alloc_noncontiguous);

अटल व्योम मुक्त_single_sgt(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
	__dma_मुक्त_pages(dev, size, sg_page(sgt->sgl), sgt->sgl->dma_address,
			 dir);
	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
पूर्ण

व्योम dma_मुक्त_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	debug_dma_unmap_sg(dev, sgt->sgl, sgt->orig_nents, dir);
	अगर (ops && ops->मुक्त_noncontiguous)
		ops->मुक्त_noncontiguous(dev, size, sgt, dir);
	अन्यथा
		मुक्त_single_sgt(dev, size, sgt, dir);
पूर्ण
EXPORT_SYMBOL_GPL(dma_मुक्त_noncontiguous);

व्योम *dma_vmap_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	अचिन्हित दीर्घ count = PAGE_ALIGN(size) >> PAGE_SHIFT;

	अगर (ops && ops->alloc_noncontiguous)
		वापस vmap(sgt_handle(sgt)->pages, count, VM_MAP, PAGE_KERNEL);
	वापस page_address(sg_page(sgt->sgl));
पूर्ण
EXPORT_SYMBOL_GPL(dma_vmap_noncontiguous);

व्योम dma_vunmap_noncontiguous(काष्ठा device *dev, व्योम *vaddr)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (ops && ops->alloc_noncontiguous)
		vunmap(vaddr);
पूर्ण
EXPORT_SYMBOL_GPL(dma_vunmap_noncontiguous);

पूर्णांक dma_mmap_noncontiguous(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		माप_प्रकार size, काष्ठा sg_table *sgt)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (ops && ops->alloc_noncontiguous) अणु
		अचिन्हित दीर्घ count = PAGE_ALIGN(size) >> PAGE_SHIFT;

		अगर (vma->vm_pgoff >= count ||
		    vma_pages(vma) > count - vma->vm_pgoff)
			वापस -ENXIO;
		वापस vm_map_pages(vma, sgt_handle(sgt)->pages, count);
	पूर्ण
	वापस dma_mmap_pages(dev, vma, size, sg_page(sgt->sgl));
पूर्ण
EXPORT_SYMBOL_GPL(dma_mmap_noncontiguous);

पूर्णांक dma_supported(काष्ठा device *dev, u64 mask)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	/*
	 * ->dma_supported sets the bypass flag, so we must always call
	 * पूर्णांकo the method here unless the device is truly direct mapped.
	 */
	अगर (!ops)
		वापस dma_direct_supported(dev, mask);
	अगर (!ops->dma_supported)
		वापस 1;
	वापस ops->dma_supported(dev, mask);
पूर्ण
EXPORT_SYMBOL(dma_supported);

#अगर_घोषित CONFIG_ARCH_HAS_DMA_SET_MASK
व्योम arch_dma_set_mask(काष्ठा device *dev, u64 mask);
#अन्यथा
#घोषणा arch_dma_set_mask(dev, mask)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

पूर्णांक dma_set_mask(काष्ठा device *dev, u64 mask)
अणु
	/*
	 * Truncate the mask to the actually supported dma_addr_t width to
	 * aव्योम generating unsupportable addresses.
	 */
	mask = (dma_addr_t)mask;

	अगर (!dev->dma_mask || !dma_supported(dev, mask))
		वापस -EIO;

	arch_dma_set_mask(dev, mask);
	*dev->dma_mask = mask;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dma_set_mask);

#अगर_अघोषित CONFIG_ARCH_HAS_DMA_SET_COHERENT_MASK
पूर्णांक dma_set_coherent_mask(काष्ठा device *dev, u64 mask)
अणु
	/*
	 * Truncate the mask to the actually supported dma_addr_t width to
	 * aव्योम generating unsupportable addresses.
	 */
	mask = (dma_addr_t)mask;

	अगर (!dma_supported(dev, mask))
		वापस -EIO;

	dev->coherent_dma_mask = mask;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dma_set_coherent_mask);
#पूर्ण_अगर

माप_प्रकार dma_max_mapping_size(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	माप_प्रकार size = SIZE_MAX;

	अगर (dma_map_direct(dev, ops))
		size = dma_direct_max_mapping_size(dev);
	अन्यथा अगर (ops && ops->max_mapping_size)
		size = ops->max_mapping_size(dev);

	वापस size;
पूर्ण
EXPORT_SYMBOL_GPL(dma_max_mapping_size);

bool dma_need_sync(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (dma_map_direct(dev, ops))
		वापस dma_direct_need_sync(dev, dma_addr);
	वापस ops->sync_single_क्रम_cpu || ops->sync_single_क्रम_device;
पूर्ण
EXPORT_SYMBOL_GPL(dma_need_sync);

अचिन्हित दीर्घ dma_get_merge_boundary(काष्ठा device *dev)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (!ops || !ops->get_merge_boundary)
		वापस 0;	/* can't merge */

	वापस ops->get_merge_boundary(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dma_get_merge_boundary);
