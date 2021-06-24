<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_DMA_MAPPING_H
#घोषणा _LINUX_DMA_MAPPING_H

#समावेश <linux/sizes.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/bug.h>
#समावेश <linux/mem_encrypt.h>

/**
 * List of possible attributes associated with a DMA mapping. The semantics
 * of each attribute should be defined in Documentation/core-api/dma-attributes.rst.
 */

/*
 * DMA_ATTR_WEAK_ORDERING: Specअगरies that पढ़ोs and ग_लिखोs to the mapping
 * may be weakly ordered, that is that पढ़ोs and ग_लिखोs may pass each other.
 */
#घोषणा DMA_ATTR_WEAK_ORDERING		(1UL << 1)
/*
 * DMA_ATTR_WRITE_COMBINE: Specअगरies that ग_लिखोs to the mapping may be
 * buffered to improve perक्रमmance.
 */
#घोषणा DMA_ATTR_WRITE_COMBINE		(1UL << 2)
/*
 * DMA_ATTR_NO_KERNEL_MAPPING: Lets the platक्रमm to aव्योम creating a kernel
 * भव mapping क्रम the allocated buffer.
 */
#घोषणा DMA_ATTR_NO_KERNEL_MAPPING	(1UL << 4)
/*
 * DMA_ATTR_SKIP_CPU_SYNC: Allows platक्रमm code to skip synchronization of
 * the CPU cache क्रम the given buffer assuming that it has been alपढ़ोy
 * transferred to 'device' करोमुख्य.
 */
#घोषणा DMA_ATTR_SKIP_CPU_SYNC		(1UL << 5)
/*
 * DMA_ATTR_FORCE_CONTIGUOUS: Forces contiguous allocation of the buffer
 * in physical memory.
 */
#घोषणा DMA_ATTR_FORCE_CONTIGUOUS	(1UL << 6)
/*
 * DMA_ATTR_ALLOC_SINGLE_PAGES: This is a hपूर्णांक to the DMA-mapping subप्रणाली
 * that it's probably not worth the समय to try to allocate memory to in a way
 * that gives better TLB efficiency.
 */
#घोषणा DMA_ATTR_ALLOC_SINGLE_PAGES	(1UL << 7)
/*
 * DMA_ATTR_NO_WARN: This tells the DMA-mapping subप्रणाली to suppress
 * allocation failure reports (similarly to __GFP_NOWARN).
 */
#घोषणा DMA_ATTR_NO_WARN	(1UL << 8)

/*
 * DMA_ATTR_PRIVILEGED: used to indicate that the buffer is fully
 * accessible at an elevated privilege level (and ideally inaccessible or
 * at least पढ़ो-only at lesser-privileged levels).
 */
#घोषणा DMA_ATTR_PRIVILEGED		(1UL << 9)

/*
 * A dma_addr_t can hold any valid DMA or bus address क्रम the platक्रमm.  It can
 * be given to a device to use as a DMA source or target.  It is specअगरic to a
 * given device and there may be a translation between the CPU physical address
 * space and the bus address space.
 *
 * DMA_MAPPING_ERROR is the magic error code अगर a mapping failed.  It should not
 * be used directly in drivers, but checked क्रम using dma_mapping_error()
 * instead.
 */
#घोषणा DMA_MAPPING_ERROR		(~(dma_addr_t)0)

#घोषणा DMA_BIT_MASK(n)	(((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))

#अगर_घोषित CONFIG_DMA_API_DEBUG
व्योम debug_dma_mapping_error(काष्ठा device *dev, dma_addr_t dma_addr);
व्योम debug_dma_map_single(काष्ठा device *dev, स्थिर व्योम *addr,
		अचिन्हित दीर्घ len);
#अन्यथा
अटल अंतरभूत व्योम debug_dma_mapping_error(काष्ठा device *dev,
		dma_addr_t dma_addr)
अणु
पूर्ण
अटल अंतरभूत व्योम debug_dma_map_single(काष्ठा device *dev, स्थिर व्योम *addr,
		अचिन्हित दीर्घ len)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_API_DEBUG */

#अगर_घोषित CONFIG_HAS_DMA
अटल अंतरभूत पूर्णांक dma_mapping_error(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	debug_dma_mapping_error(dev, dma_addr);

	अगर (unlikely(dma_addr == DMA_MAPPING_ERROR))
		वापस -ENOMEM;
	वापस 0;
पूर्ण

dma_addr_t dma_map_page_attrs(काष्ठा device *dev, काष्ठा page *page,
		माप_प्रकार offset, माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs);
व्योम dma_unmap_page_attrs(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
पूर्णांक dma_map_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
व्योम dma_unmap_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg,
				      पूर्णांक nents, क्रमागत dma_data_direction dir,
				      अचिन्हित दीर्घ attrs);
dma_addr_t dma_map_resource(काष्ठा device *dev, phys_addr_t phys_addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
व्योम dma_unmap_resource(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
व्योम dma_sync_single_क्रम_cpu(काष्ठा device *dev, dma_addr_t addr, माप_प्रकार size,
		क्रमागत dma_data_direction dir);
व्योम dma_sync_single_क्रम_device(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir);
व्योम dma_sync_sg_क्रम_cpu(काष्ठा device *dev, काष्ठा scatterlist *sg,
		    पूर्णांक nelems, क्रमागत dma_data_direction dir);
व्योम dma_sync_sg_क्रम_device(काष्ठा device *dev, काष्ठा scatterlist *sg,
		       पूर्णांक nelems, क्रमागत dma_data_direction dir);
व्योम *dma_alloc_attrs(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t flag, अचिन्हित दीर्घ attrs);
व्योम dma_मुक्त_attrs(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs);
व्योम *dmam_alloc_attrs(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs);
व्योम dmam_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
		dma_addr_t dma_handle);
पूर्णांक dma_get_sgtable_attrs(काष्ठा device *dev, काष्ठा sg_table *sgt,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs);
पूर्णांक dma_mmap_attrs(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs);
bool dma_can_mmap(काष्ठा device *dev);
पूर्णांक dma_supported(काष्ठा device *dev, u64 mask);
पूर्णांक dma_set_mask(काष्ठा device *dev, u64 mask);
पूर्णांक dma_set_coherent_mask(काष्ठा device *dev, u64 mask);
u64 dma_get_required_mask(काष्ठा device *dev);
माप_प्रकार dma_max_mapping_size(काष्ठा device *dev);
bool dma_need_sync(काष्ठा device *dev, dma_addr_t dma_addr);
अचिन्हित दीर्घ dma_get_merge_boundary(काष्ठा device *dev);
काष्ठा sg_table *dma_alloc_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		क्रमागत dma_data_direction dir, gfp_t gfp, अचिन्हित दीर्घ attrs);
व्योम dma_मुक्त_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir);
व्योम *dma_vmap_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt);
व्योम dma_vunmap_noncontiguous(काष्ठा device *dev, व्योम *vaddr);
पूर्णांक dma_mmap_noncontiguous(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		माप_प्रकार size, काष्ठा sg_table *sgt);
#अन्यथा /* CONFIG_HAS_DMA */
अटल अंतरभूत dma_addr_t dma_map_page_attrs(काष्ठा device *dev,
		काष्ठा page *page, माप_प्रकार offset, माप_प्रकार size,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस DMA_MAPPING_ERROR;
पूर्ण
अटल अंतरभूत व्योम dma_unmap_page_attrs(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक dma_map_sg_attrs(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम dma_unmap_sg_attrs(काष्ठा device *dev,
		काष्ठा scatterlist *sg, पूर्णांक nents, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
पूर्ण
अटल अंतरभूत dma_addr_t dma_map_resource(काष्ठा device *dev,
		phys_addr_t phys_addr, माप_प्रकार size, क्रमागत dma_data_direction dir,
		अचिन्हित दीर्घ attrs)
अणु
	वापस DMA_MAPPING_ERROR;
पूर्ण
अटल अंतरभूत व्योम dma_unmap_resource(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
पूर्ण
अटल अंतरभूत व्योम dma_sync_single_क्रम_cpu(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
पूर्ण
अटल अंतरभूत व्योम dma_sync_single_क्रम_device(काष्ठा device *dev,
		dma_addr_t addr, माप_प्रकार size, क्रमागत dma_data_direction dir)
अणु
पूर्ण
अटल अंतरभूत व्योम dma_sync_sg_क्रम_cpu(काष्ठा device *dev,
		काष्ठा scatterlist *sg, पूर्णांक nelems, क्रमागत dma_data_direction dir)
अणु
पूर्ण
अटल अंतरभूत व्योम dma_sync_sg_क्रम_device(काष्ठा device *dev,
		काष्ठा scatterlist *sg, पूर्णांक nelems, क्रमागत dma_data_direction dir)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक dma_mapping_error(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	वापस -ENOMEM;
पूर्ण
अटल अंतरभूत व्योम *dma_alloc_attrs(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t flag, अचिन्हित दीर्घ attrs)
अणु
	वापस शून्य;
पूर्ण
अटल व्योम dma_मुक्त_attrs(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
पूर्ण
अटल अंतरभूत व्योम *dmam_alloc_attrs(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dmam_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
		व्योम *vaddr, dma_addr_t dma_handle)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक dma_get_sgtable_attrs(काष्ठा device *dev,
		काष्ठा sg_table *sgt, व्योम *cpu_addr, dma_addr_t dma_addr,
		माप_प्रकार size, अचिन्हित दीर्घ attrs)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत पूर्णांक dma_mmap_attrs(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
	वापस -ENXIO;
पूर्ण
अटल अंतरभूत bool dma_can_mmap(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक dma_supported(काष्ठा device *dev, u64 mask)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक dma_set_mask(काष्ठा device *dev, u64 mask)
अणु
	वापस -EIO;
पूर्ण
अटल अंतरभूत पूर्णांक dma_set_coherent_mask(काष्ठा device *dev, u64 mask)
अणु
	वापस -EIO;
पूर्ण
अटल अंतरभूत u64 dma_get_required_mask(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत माप_प्रकार dma_max_mapping_size(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool dma_need_sync(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ dma_get_merge_boundary(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा sg_table *dma_alloc_noncontiguous(काष्ठा device *dev,
		माप_प्रकार size, क्रमागत dma_data_direction dir, gfp_t gfp,
		अचिन्हित दीर्घ attrs)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dma_मुक्त_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
पूर्ण
अटल अंतरभूत व्योम *dma_vmap_noncontiguous(काष्ठा device *dev, माप_प्रकार size,
		काष्ठा sg_table *sgt)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dma_vunmap_noncontiguous(काष्ठा device *dev, व्योम *vaddr)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक dma_mmap_noncontiguous(काष्ठा device *dev,
		काष्ठा vm_area_काष्ठा *vma, माप_प्रकार size, काष्ठा sg_table *sgt)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_HAS_DMA */

काष्ठा page *dma_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp);
व्योम dma_मुक्त_pages(काष्ठा device *dev, माप_प्रकार size, काष्ठा page *page,
		dma_addr_t dma_handle, क्रमागत dma_data_direction dir);
पूर्णांक dma_mmap_pages(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		माप_प्रकार size, काष्ठा page *page);

अटल अंतरभूत व्योम *dma_alloc_noncoherent(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp)
अणु
	काष्ठा page *page = dma_alloc_pages(dev, size, dma_handle, dir, gfp);
	वापस page ? page_address(page) : शून्य;
पूर्ण

अटल अंतरभूत व्योम dma_मुक्त_noncoherent(काष्ठा device *dev, माप_प्रकार size,
		व्योम *vaddr, dma_addr_t dma_handle, क्रमागत dma_data_direction dir)
अणु
	dma_मुक्त_pages(dev, size, virt_to_page(vaddr), dma_handle, dir);
पूर्ण

अटल अंतरभूत dma_addr_t dma_map_single_attrs(काष्ठा device *dev, व्योम *ptr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	/* DMA must never operate on areas that might be remapped. */
	अगर (dev_WARN_ONCE(dev, is_vदो_स्मृति_addr(ptr),
			  "rejecting DMA map of vmalloc memory\n"))
		वापस DMA_MAPPING_ERROR;
	debug_dma_map_single(dev, ptr, size);
	वापस dma_map_page_attrs(dev, virt_to_page(ptr), offset_in_page(ptr),
			size, dir, attrs);
पूर्ण

अटल अंतरभूत व्योम dma_unmap_single_attrs(काष्ठा device *dev, dma_addr_t addr,
		माप_प्रकार size, क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	वापस dma_unmap_page_attrs(dev, addr, size, dir, attrs);
पूर्ण

अटल अंतरभूत व्योम dma_sync_single_range_क्रम_cpu(काष्ठा device *dev,
		dma_addr_t addr, अचिन्हित दीर्घ offset, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	वापस dma_sync_single_क्रम_cpu(dev, addr + offset, size, dir);
पूर्ण

अटल अंतरभूत व्योम dma_sync_single_range_क्रम_device(काष्ठा device *dev,
		dma_addr_t addr, अचिन्हित दीर्घ offset, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	वापस dma_sync_single_क्रम_device(dev, addr + offset, size, dir);
पूर्ण

/**
 * dma_map_sgtable - Map the given buffer क्रम DMA
 * @dev:	The device क्रम which to perक्रमm the DMA operation
 * @sgt:	The sg_table object describing the buffer
 * @dir:	DMA direction
 * @attrs:	Optional DMA attributes क्रम the map operation
 *
 * Maps a buffer described by a scatterlist stored in the given sg_table
 * object क्रम the @dir DMA operation by the @dev device. After success the
 * ownership क्रम the buffer is transferred to the DMA करोमुख्य.  One has to
 * call dma_sync_sgtable_क्रम_cpu() or dma_unmap_sgtable() to move the
 * ownership of the buffer back to the CPU करोमुख्य beक्रमe touching the
 * buffer by the CPU.
 *
 * Returns 0 on success or -EINVAL on error during mapping the buffer.
 */
अटल अंतरभूत पूर्णांक dma_map_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक nents;

	nents = dma_map_sg_attrs(dev, sgt->sgl, sgt->orig_nents, dir, attrs);
	अगर (nents <= 0)
		वापस -EINVAL;
	sgt->nents = nents;
	वापस 0;
पूर्ण

/**
 * dma_unmap_sgtable - Unmap the given buffer क्रम DMA
 * @dev:	The device क्रम which to perक्रमm the DMA operation
 * @sgt:	The sg_table object describing the buffer
 * @dir:	DMA direction
 * @attrs:	Optional DMA attributes क्रम the unmap operation
 *
 * Unmaps a buffer described by a scatterlist stored in the given sg_table
 * object क्रम the @dir DMA operation by the @dev device. After this function
 * the ownership of the buffer is transferred back to the CPU करोमुख्य.
 */
अटल अंतरभूत व्योम dma_unmap_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs)
अणु
	dma_unmap_sg_attrs(dev, sgt->sgl, sgt->orig_nents, dir, attrs);
पूर्ण

/**
 * dma_sync_sgtable_क्रम_cpu - Synchronize the given buffer क्रम CPU access
 * @dev:	The device क्रम which to perक्रमm the DMA operation
 * @sgt:	The sg_table object describing the buffer
 * @dir:	DMA direction
 *
 * Perक्रमms the needed cache synchronization and moves the ownership of the
 * buffer back to the CPU करोमुख्य, so it is safe to perक्रमm any access to it
 * by the CPU. Beक्रमe करोing any further DMA operations, one has to transfer
 * the ownership of the buffer back to the DMA करोमुख्य by calling the
 * dma_sync_sgtable_क्रम_device().
 */
अटल अंतरभूत व्योम dma_sync_sgtable_क्रम_cpu(काष्ठा device *dev,
		काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
	dma_sync_sg_क्रम_cpu(dev, sgt->sgl, sgt->orig_nents, dir);
पूर्ण

/**
 * dma_sync_sgtable_क्रम_device - Synchronize the given buffer क्रम DMA
 * @dev:	The device क्रम which to perक्रमm the DMA operation
 * @sgt:	The sg_table object describing the buffer
 * @dir:	DMA direction
 *
 * Perक्रमms the needed cache synchronization and moves the ownership of the
 * buffer back to the DMA करोमुख्य, so it is safe to perक्रमm the DMA operation.
 * Once finished, one has to call dma_sync_sgtable_क्रम_cpu() or
 * dma_unmap_sgtable().
 */
अटल अंतरभूत व्योम dma_sync_sgtable_क्रम_device(काष्ठा device *dev,
		काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir)
अणु
	dma_sync_sg_क्रम_device(dev, sgt->sgl, sgt->orig_nents, dir);
पूर्ण

#घोषणा dma_map_single(d, a, s, r) dma_map_single_attrs(d, a, s, r, 0)
#घोषणा dma_unmap_single(d, a, s, r) dma_unmap_single_attrs(d, a, s, r, 0)
#घोषणा dma_map_sg(d, s, n, r) dma_map_sg_attrs(d, s, n, r, 0)
#घोषणा dma_unmap_sg(d, s, n, r) dma_unmap_sg_attrs(d, s, n, r, 0)
#घोषणा dma_map_page(d, p, o, s, r) dma_map_page_attrs(d, p, o, s, r, 0)
#घोषणा dma_unmap_page(d, a, s, r) dma_unmap_page_attrs(d, a, s, r, 0)
#घोषणा dma_get_sgtable(d, t, v, h, s) dma_get_sgtable_attrs(d, t, v, h, s, 0)
#घोषणा dma_mmap_coherent(d, v, c, h, s) dma_mmap_attrs(d, v, c, h, s, 0)

अटल अंतरभूत व्योम *dma_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp)
अणु
	वापस dma_alloc_attrs(dev, size, dma_handle, gfp,
			(gfp & __GFP_NOWARN) ? DMA_ATTR_NO_WARN : 0);
पूर्ण

अटल अंतरभूत व्योम dma_मुक्त_coherent(काष्ठा device *dev, माप_प्रकार size,
		व्योम *cpu_addr, dma_addr_t dma_handle)
अणु
	वापस dma_मुक्त_attrs(dev, size, cpu_addr, dma_handle, 0);
पूर्ण


अटल अंतरभूत u64 dma_get_mask(काष्ठा device *dev)
अणु
	अगर (dev->dma_mask && *dev->dma_mask)
		वापस *dev->dma_mask;
	वापस DMA_BIT_MASK(32);
पूर्ण

/*
 * Set both the DMA mask and the coherent DMA mask to the same thing.
 * Note that we करोn't check the वापस value from dma_set_coherent_mask()
 * as the DMA API guarantees that the coherent DMA mask can be set to
 * the same or smaller than the streaming DMA mask.
 */
अटल अंतरभूत पूर्णांक dma_set_mask_and_coherent(काष्ठा device *dev, u64 mask)
अणु
	पूर्णांक rc = dma_set_mask(dev, mask);
	अगर (rc == 0)
		dma_set_coherent_mask(dev, mask);
	वापस rc;
पूर्ण

/*
 * Similar to the above, except it deals with the हाल where the device
 * करोes not have dev->dma_mask appropriately setup.
 */
अटल अंतरभूत पूर्णांक dma_coerce_mask_and_coherent(काष्ठा device *dev, u64 mask)
अणु
	dev->dma_mask = &dev->coherent_dma_mask;
	वापस dma_set_mask_and_coherent(dev, mask);
पूर्ण

/**
 * dma_addressing_limited - वापस अगर the device is addressing limited
 * @dev:	device to check
 *
 * Return %true अगर the devices DMA mask is too small to address all memory in
 * the प्रणाली, अन्यथा %false.  Lack of addressing bits is the prime reason क्रम
 * bounce buffering, but might not be the only one.
 */
अटल अंतरभूत bool dma_addressing_limited(काष्ठा device *dev)
अणु
	वापस min_not_zero(dma_get_mask(dev), dev->bus_dma_limit) <
			    dma_get_required_mask(dev);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dma_get_max_seg_size(काष्ठा device *dev)
अणु
	अगर (dev->dma_parms && dev->dma_parms->max_segment_size)
		वापस dev->dma_parms->max_segment_size;
	वापस SZ_64K;
पूर्ण

अटल अंतरभूत पूर्णांक dma_set_max_seg_size(काष्ठा device *dev, अचिन्हित पूर्णांक size)
अणु
	अगर (dev->dma_parms) अणु
		dev->dma_parms->max_segment_size = size;
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ dma_get_seg_boundary(काष्ठा device *dev)
अणु
	अगर (dev->dma_parms && dev->dma_parms->segment_boundary_mask)
		वापस dev->dma_parms->segment_boundary_mask;
	वापस अच_दीर्घ_उच्च;
पूर्ण

/**
 * dma_get_seg_boundary_nr_pages - वापस the segment boundary in "page" units
 * @dev: device to guery the boundary क्रम
 * @page_shअगरt: ilog() of the IOMMU page size
 *
 * Return the segment boundary in IOMMU page units (which may be dअगरferent from
 * the CPU page size) क्रम the passed in device.
 *
 * If @dev is शून्य a boundary of U32_MAX is assumed, this हाल is just क्रम
 * non-DMA API callers.
 */
अटल अंतरभूत अचिन्हित दीर्घ dma_get_seg_boundary_nr_pages(काष्ठा device *dev,
		अचिन्हित पूर्णांक page_shअगरt)
अणु
	अगर (!dev)
		वापस (U32_MAX >> page_shअगरt) + 1;
	वापस (dma_get_seg_boundary(dev) >> page_shअगरt) + 1;
पूर्ण

अटल अंतरभूत पूर्णांक dma_set_seg_boundary(काष्ठा device *dev, अचिन्हित दीर्घ mask)
अणु
	अगर (dev->dma_parms) अणु
		dev->dma_parms->segment_boundary_mask = mask;
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक dma_get_min_align_mask(काष्ठा device *dev)
अणु
	अगर (dev->dma_parms)
		वापस dev->dma_parms->min_align_mask;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dma_set_min_align_mask(काष्ठा device *dev,
		अचिन्हित पूर्णांक min_align_mask)
अणु
	अगर (WARN_ON_ONCE(!dev->dma_parms))
		वापस -EIO;
	dev->dma_parms->min_align_mask = min_align_mask;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक dma_get_cache_alignment(व्योम)
अणु
#अगर_घोषित ARCH_DMA_MINALIGN
	वापस ARCH_DMA_MINALIGN;
#पूर्ण_अगर
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम *dmam_alloc_coherent(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp)
अणु
	वापस dmam_alloc_attrs(dev, size, dma_handle, gfp,
			(gfp & __GFP_NOWARN) ? DMA_ATTR_NO_WARN : 0);
पूर्ण

अटल अंतरभूत व्योम *dma_alloc_wc(काष्ठा device *dev, माप_प्रकार size,
				 dma_addr_t *dma_addr, gfp_t gfp)
अणु
	अचिन्हित दीर्घ attrs = DMA_ATTR_WRITE_COMBINE;

	अगर (gfp & __GFP_NOWARN)
		attrs |= DMA_ATTR_NO_WARN;

	वापस dma_alloc_attrs(dev, size, dma_addr, gfp, attrs);
पूर्ण

अटल अंतरभूत व्योम dma_मुक्त_wc(काष्ठा device *dev, माप_प्रकार size,
			       व्योम *cpu_addr, dma_addr_t dma_addr)
अणु
	वापस dma_मुक्त_attrs(dev, size, cpu_addr, dma_addr,
			      DMA_ATTR_WRITE_COMBINE);
पूर्ण

अटल अंतरभूत पूर्णांक dma_mmap_wc(काष्ठा device *dev,
			      काष्ठा vm_area_काष्ठा *vma,
			      व्योम *cpu_addr, dma_addr_t dma_addr,
			      माप_प्रकार size)
अणु
	वापस dma_mmap_attrs(dev, vma, cpu_addr, dma_addr, size,
			      DMA_ATTR_WRITE_COMBINE);
पूर्ण

#अगर_घोषित CONFIG_NEED_DMA_MAP_STATE
#घोषणा DEFINE_DMA_UNMAP_ADDR(ADDR_NAME)        dma_addr_t ADDR_NAME
#घोषणा DEFINE_DMA_UNMAP_LEN(LEN_NAME)          __u32 LEN_NAME
#घोषणा dma_unmap_addr(PTR, ADDR_NAME)           ((PTR)->ADDR_NAME)
#घोषणा dma_unmap_addr_set(PTR, ADDR_NAME, VAL)  (((PTR)->ADDR_NAME) = (VAL))
#घोषणा dma_unmap_len(PTR, LEN_NAME)             ((PTR)->LEN_NAME)
#घोषणा dma_unmap_len_set(PTR, LEN_NAME, VAL)    (((PTR)->LEN_NAME) = (VAL))
#अन्यथा
#घोषणा DEFINE_DMA_UNMAP_ADDR(ADDR_NAME)
#घोषणा DEFINE_DMA_UNMAP_LEN(LEN_NAME)
#घोषणा dma_unmap_addr(PTR, ADDR_NAME)           (0)
#घोषणा dma_unmap_addr_set(PTR, ADDR_NAME, VAL)  करो अणु पूर्ण जबतक (0)
#घोषणा dma_unmap_len(PTR, LEN_NAME)             (0)
#घोषणा dma_unmap_len_set(PTR, LEN_NAME, VAL)    करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_DMA_MAPPING_H */
