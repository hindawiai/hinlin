<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header is क्रम implementations of dma_map_ops and related code.
 * It should not be included in drivers just using the DMA API.
 */
#अगर_अघोषित _LINUX_DMA_MAP_OPS_H
#घोषणा _LINUX_DMA_MAP_OPS_H

#समावेश <linux/dma-mapping.h>
#समावेश <linux/pgtable.h>

काष्ठा cma;

काष्ठा dma_map_ops अणु
	व्योम *(*alloc)(काष्ठा device *dev, माप_प्रकार size,
			dma_addr_t *dma_handle, gfp_t gfp,
			अचिन्हित दीर्घ attrs);
	व्योम (*मुक्त)(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
			dma_addr_t dma_handle, अचिन्हित दीर्घ attrs);
	काष्ठा page *(*alloc_pages)(काष्ठा device *dev, माप_प्रकार size,
			dma_addr_t *dma_handle, क्रमागत dma_data_direction dir,
			gfp_t gfp);
	व्योम (*मुक्त_pages)(काष्ठा device *dev, माप_प्रकार size, काष्ठा page *vaddr,
			dma_addr_t dma_handle, क्रमागत dma_data_direction dir);
	काष्ठा sg_table *(*alloc_noncontiguous)(काष्ठा device *dev, माप_प्रकार size,
			क्रमागत dma_data_direction dir, gfp_t gfp,
			अचिन्हित दीर्घ attrs);
	व्योम (*मुक्त_noncontiguous)(काष्ठा device *dev, माप_प्रकार size,
			काष्ठा sg_table *sgt, क्रमागत dma_data_direction dir);
	पूर्णांक (*mmap)(काष्ठा device *, काष्ठा vm_area_काष्ठा *,
			व्योम *, dma_addr_t, माप_प्रकार, अचिन्हित दीर्घ attrs);

	पूर्णांक (*get_sgtable)(काष्ठा device *dev, काष्ठा sg_table *sgt,
			व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
			अचिन्हित दीर्घ attrs);

	dma_addr_t (*map_page)(काष्ठा device *dev, काष्ठा page *page,
			अचिन्हित दीर्घ offset, माप_प्रकार size,
			क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
	व्योम (*unmap_page)(काष्ठा device *dev, dma_addr_t dma_handle,
			माप_प्रकार size, क्रमागत dma_data_direction dir,
			अचिन्हित दीर्घ attrs);
	/*
	 * map_sg वापसs 0 on error and a value > 0 on success.
	 * It should never वापस a value < 0.
	 */
	पूर्णांक (*map_sg)(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
			क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
	व्योम (*unmap_sg)(काष्ठा device *dev, काष्ठा scatterlist *sg, पूर्णांक nents,
			क्रमागत dma_data_direction dir, अचिन्हित दीर्घ attrs);
	dma_addr_t (*map_resource)(काष्ठा device *dev, phys_addr_t phys_addr,
			माप_प्रकार size, क्रमागत dma_data_direction dir,
			अचिन्हित दीर्घ attrs);
	व्योम (*unmap_resource)(काष्ठा device *dev, dma_addr_t dma_handle,
			माप_प्रकार size, क्रमागत dma_data_direction dir,
			अचिन्हित दीर्घ attrs);
	व्योम (*sync_single_क्रम_cpu)(काष्ठा device *dev, dma_addr_t dma_handle,
			माप_प्रकार size, क्रमागत dma_data_direction dir);
	व्योम (*sync_single_क्रम_device)(काष्ठा device *dev,
			dma_addr_t dma_handle, माप_प्रकार size,
			क्रमागत dma_data_direction dir);
	व्योम (*sync_sg_क्रम_cpu)(काष्ठा device *dev, काष्ठा scatterlist *sg,
			पूर्णांक nents, क्रमागत dma_data_direction dir);
	व्योम (*sync_sg_क्रम_device)(काष्ठा device *dev, काष्ठा scatterlist *sg,
			पूर्णांक nents, क्रमागत dma_data_direction dir);
	व्योम (*cache_sync)(काष्ठा device *dev, व्योम *vaddr, माप_प्रकार size,
			क्रमागत dma_data_direction direction);
	पूर्णांक (*dma_supported)(काष्ठा device *dev, u64 mask);
	u64 (*get_required_mask)(काष्ठा device *dev);
	माप_प्रकार (*max_mapping_size)(काष्ठा device *dev);
	अचिन्हित दीर्घ (*get_merge_boundary)(काष्ठा device *dev);
पूर्ण;

#अगर_घोषित CONFIG_DMA_OPS
#समावेश <यंत्र/dma-mapping.h>

अटल अंतरभूत स्थिर काष्ठा dma_map_ops *get_dma_ops(काष्ठा device *dev)
अणु
	अगर (dev->dma_ops)
		वापस dev->dma_ops;
	वापस get_arch_dma_ops(dev->bus);
पूर्ण

अटल अंतरभूत व्योम set_dma_ops(काष्ठा device *dev,
			       स्थिर काष्ठा dma_map_ops *dma_ops)
अणु
	dev->dma_ops = dma_ops;
पूर्ण
#अन्यथा /* CONFIG_DMA_OPS */
अटल अंतरभूत स्थिर काष्ठा dma_map_ops *get_dma_ops(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम set_dma_ops(काष्ठा device *dev,
			       स्थिर काष्ठा dma_map_ops *dma_ops)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_OPS */

#अगर_घोषित CONFIG_DMA_CMA
बाह्य काष्ठा cma *dma_contiguous_शेष_area;

अटल अंतरभूत काष्ठा cma *dev_get_cma_area(काष्ठा device *dev)
अणु
	अगर (dev && dev->cma_area)
		वापस dev->cma_area;
	वापस dma_contiguous_शेष_area;
पूर्ण

व्योम dma_contiguous_reserve(phys_addr_t addr_limit);
पूर्णांक __init dma_contiguous_reserve_area(phys_addr_t size, phys_addr_t base,
		phys_addr_t limit, काष्ठा cma **res_cma, bool fixed);

काष्ठा page *dma_alloc_from_contiguous(काष्ठा device *dev, माप_प्रकार count,
				       अचिन्हित पूर्णांक order, bool no_warn);
bool dma_release_from_contiguous(काष्ठा device *dev, काष्ठा page *pages,
				 पूर्णांक count);
काष्ठा page *dma_alloc_contiguous(काष्ठा device *dev, माप_प्रकार size, gfp_t gfp);
व्योम dma_मुक्त_contiguous(काष्ठा device *dev, काष्ठा page *page, माप_प्रकार size);

व्योम dma_contiguous_early_fixup(phys_addr_t base, अचिन्हित दीर्घ size);
#अन्यथा /* CONFIG_DMA_CMA */
अटल अंतरभूत काष्ठा cma *dev_get_cma_area(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dma_contiguous_reserve(phys_addr_t limit)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक dma_contiguous_reserve_area(phys_addr_t size,
		phys_addr_t base, phys_addr_t limit, काष्ठा cma **res_cma,
		bool fixed)
अणु
	वापस -ENOSYS;
पूर्ण
अटल अंतरभूत काष्ठा page *dma_alloc_from_contiguous(काष्ठा device *dev,
		माप_प्रकार count, अचिन्हित पूर्णांक order, bool no_warn)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत bool dma_release_from_contiguous(काष्ठा device *dev,
		काष्ठा page *pages, पूर्णांक count)
अणु
	वापस false;
पूर्ण
/* Use fallback alloc() and मुक्त() when CONFIG_DMA_CMA=n */
अटल अंतरभूत काष्ठा page *dma_alloc_contiguous(काष्ठा device *dev, माप_प्रकार size,
		gfp_t gfp)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम dma_मुक्त_contiguous(काष्ठा device *dev, काष्ठा page *page,
		माप_प्रकार size)
अणु
	__मुक्त_pages(page, get_order(size));
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_CMA*/

#अगर_घोषित CONFIG_DMA_PERNUMA_CMA
व्योम dma_pernuma_cma_reserve(व्योम);
#अन्यथा
अटल अंतरभूत व्योम dma_pernuma_cma_reserve(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_PERNUMA_CMA */

#अगर_घोषित CONFIG_DMA_DECLARE_COHERENT
पूर्णांक dma_declare_coherent_memory(काष्ठा device *dev, phys_addr_t phys_addr,
		dma_addr_t device_addr, माप_प्रकार size);
पूर्णांक dma_alloc_from_dev_coherent(काष्ठा device *dev, sमाप_प्रकार size,
		dma_addr_t *dma_handle, व्योम **ret);
पूर्णांक dma_release_from_dev_coherent(काष्ठा device *dev, पूर्णांक order, व्योम *vaddr);
पूर्णांक dma_mmap_from_dev_coherent(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, माप_प्रकार size, पूर्णांक *ret);

व्योम *dma_alloc_from_global_coherent(काष्ठा device *dev, sमाप_प्रकार size,
		dma_addr_t *dma_handle);
पूर्णांक dma_release_from_global_coherent(पूर्णांक order, व्योम *vaddr);
पूर्णांक dma_mmap_from_global_coherent(काष्ठा vm_area_काष्ठा *vma, व्योम *cpu_addr,
		माप_प्रकार size, पूर्णांक *ret);

#अन्यथा
अटल अंतरभूत पूर्णांक dma_declare_coherent_memory(काष्ठा device *dev,
		phys_addr_t phys_addr, dma_addr_t device_addr, माप_प्रकार size)
अणु
	वापस -ENOSYS;
पूर्ण
#घोषणा dma_alloc_from_dev_coherent(dev, size, handle, ret) (0)
#घोषणा dma_release_from_dev_coherent(dev, order, vaddr) (0)
#घोषणा dma_mmap_from_dev_coherent(dev, vma, vaddr, order, ret) (0)

अटल अंतरभूत व्योम *dma_alloc_from_global_coherent(काष्ठा device *dev,
		sमाप_प्रकार size, dma_addr_t *dma_handle)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत पूर्णांक dma_release_from_global_coherent(पूर्णांक order, व्योम *vaddr)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक dma_mmap_from_global_coherent(काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, माप_प्रकार size, पूर्णांक *ret)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_DECLARE_COHERENT */

/*
 * This is the actual वापस value from the ->alloc_noncontiguous method.
 * The users of the DMA API should only care about the sg_table, but to make
 * the DMA-API पूर्णांकernal vmaping and मुक्तing easier we stash away the page
 * array as well (except क्रम the fallback हाल).  This can go away any समय,
 * e.g. when a vmap-variant that takes a scatterlist comes aदीर्घ.
 */
काष्ठा dma_sgt_handle अणु
	काष्ठा sg_table sgt;
	काष्ठा page **pages;
पूर्ण;
#घोषणा sgt_handle(sgt) \
	container_of((sgt), काष्ठा dma_sgt_handle, sgt)

पूर्णांक dma_common_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs);
पूर्णांक dma_common_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs);
काष्ठा page *dma_common_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp);
व्योम dma_common_मुक्त_pages(काष्ठा device *dev, माप_प्रकार size, काष्ठा page *vaddr,
		dma_addr_t dma_handle, क्रमागत dma_data_direction dir);

काष्ठा page **dma_common_find_pages(व्योम *cpu_addr);
व्योम *dma_common_contiguous_remap(काष्ठा page *page, माप_प्रकार size, pgprot_t prot,
		स्थिर व्योम *caller);
व्योम *dma_common_pages_remap(काष्ठा page **pages, माप_प्रकार size, pgprot_t prot,
		स्थिर व्योम *caller);
व्योम dma_common_मुक्त_remap(व्योम *cpu_addr, माप_प्रकार size);

काष्ठा page *dma_alloc_from_pool(काष्ठा device *dev, माप_प्रकार size,
		व्योम **cpu_addr, gfp_t flags,
		bool (*phys_addr_ok)(काष्ठा device *, phys_addr_t, माप_प्रकार));
bool dma_मुक्त_from_pool(काष्ठा device *dev, व्योम *start, माप_प्रकार size);

पूर्णांक dma_direct_set_offset(काष्ठा device *dev, phys_addr_t cpu_start,
		dma_addr_t dma_start, u64 size);

#अगर defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_DEVICE) || \
	defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU) || \
	defined(CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL)
बाह्य bool dma_शेष_coherent;
अटल अंतरभूत bool dev_is_dma_coherent(काष्ठा device *dev)
अणु
	वापस dev->dma_coherent;
पूर्ण
#अन्यथा
अटल अंतरभूत bool dev_is_dma_coherent(काष्ठा device *dev)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_DMA_COHERENCE_H */

व्योम *arch_dma_alloc(काष्ठा device *dev, माप_प्रकार size, dma_addr_t *dma_handle,
		gfp_t gfp, अचिन्हित दीर्घ attrs);
व्योम arch_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *cpu_addr,
		dma_addr_t dma_addr, अचिन्हित दीर्घ attrs);

#अगर_घोषित CONFIG_MMU
/*
 * Page protection so that devices that can't snoop CPU caches can use the
 * memory coherently.  We शेष to pgprot_noncached which is usually used
 * क्रम ioremap as a safe bet, but architectures can override this with less
 * strict semantics अगर possible.
 */
#अगर_अघोषित pgprot_dmacoherent
#घोषणा pgprot_dmacoherent(prot)	pgprot_noncached(prot)
#पूर्ण_अगर

pgprot_t dma_pgprot(काष्ठा device *dev, pgprot_t prot, अचिन्हित दीर्घ attrs);
#अन्यथा
अटल अंतरभूत pgprot_t dma_pgprot(काष्ठा device *dev, pgprot_t prot,
		अचिन्हित दीर्घ attrs)
अणु
	वापस prot;	/* no protection bits supported without page tables */
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

#अगर_घोषित CONFIG_ARCH_HAS_SYNC_DMA_FOR_DEVICE
व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir);
#अन्यथा
अटल अंतरभूत व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
पूर्ण
#पूर्ण_अगर /* ARCH_HAS_SYNC_DMA_FOR_DEVICE */

#अगर_घोषित CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU
व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir);
#अन्यथा
अटल अंतरभूत व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
पूर्ण
#पूर्ण_अगर /* ARCH_HAS_SYNC_DMA_FOR_CPU */

#अगर_घोषित CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL
व्योम arch_sync_dma_क्रम_cpu_all(व्योम);
#अन्यथा
अटल अंतरभूत व्योम arch_sync_dma_क्रम_cpu_all(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_SYNC_DMA_FOR_CPU_ALL */

#अगर_घोषित CONFIG_ARCH_HAS_DMA_PREP_COHERENT
व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_DMA_PREP_COHERENT */

#अगर_घोषित CONFIG_ARCH_HAS_DMA_MARK_CLEAN
व्योम arch_dma_mark_clean(phys_addr_t paddr, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत व्योम arch_dma_mark_clean(phys_addr_t paddr, माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर /* ARCH_HAS_DMA_MARK_CLEAN */

व्योम *arch_dma_set_uncached(व्योम *addr, माप_प्रकार size);
व्योम arch_dma_clear_uncached(व्योम *addr, माप_प्रकार size);

#अगर_घोषित CONFIG_ARCH_HAS_DMA_MAP_सूचीECT
bool arch_dma_map_page_direct(काष्ठा device *dev, phys_addr_t addr);
bool arch_dma_unmap_page_direct(काष्ठा device *dev, dma_addr_t dma_handle);
bool arch_dma_map_sg_direct(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents);
bool arch_dma_unmap_sg_direct(काष्ठा device *dev, काष्ठा scatterlist *sg,
		पूर्णांक nents);
#अन्यथा
#घोषणा arch_dma_map_page_direct(d, a)		(false)
#घोषणा arch_dma_unmap_page_direct(d, a)	(false)
#घोषणा arch_dma_map_sg_direct(d, s, n)		(false)
#घोषणा arch_dma_unmap_sg_direct(d, s, n)	(false)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_HAS_SETUP_DMA_OPS
व्योम arch_setup_dma_ops(काष्ठा device *dev, u64 dma_base, u64 size,
		स्थिर काष्ठा iommu_ops *iommu, bool coherent);
#अन्यथा
अटल अंतरभूत व्योम arch_setup_dma_ops(काष्ठा device *dev, u64 dma_base,
		u64 size, स्थिर काष्ठा iommu_ops *iommu, bool coherent)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_SETUP_DMA_OPS */

#अगर_घोषित CONFIG_ARCH_HAS_TEARDOWN_DMA_OPS
व्योम arch_tearकरोwn_dma_ops(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत व्योम arch_tearकरोwn_dma_ops(काष्ठा device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ARCH_HAS_TEARDOWN_DMA_OPS */

#अगर_घोषित CONFIG_DMA_API_DEBUG
व्योम dma_debug_add_bus(काष्ठा bus_type *bus);
व्योम debug_dma_dump_mappings(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत व्योम dma_debug_add_bus(काष्ठा bus_type *bus)
अणु
पूर्ण
अटल अंतरभूत व्योम debug_dma_dump_mappings(काष्ठा device *dev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DMA_API_DEBUG */

बाह्य स्थिर काष्ठा dma_map_ops dma_dummy_ops;

#पूर्ण_अगर /* _LINUX_DMA_MAP_OPS_H */
