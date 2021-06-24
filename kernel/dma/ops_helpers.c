<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Helpers क्रम DMA ops implementations.  These generally rely on the fact that
 * the allocated memory contains normal pages in the direct kernel mapping.
 */
#समावेश <linux/dma-map-ops.h>

/*
 * Create scatter-list क्रम the alपढ़ोy allocated DMA buffer.
 */
पूर्णांक dma_common_get_sgtable(काष्ठा device *dev, काष्ठा sg_table *sgt,
		 व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		 अचिन्हित दीर्घ attrs)
अणु
	काष्ठा page *page = virt_to_page(cpu_addr);
	पूर्णांक ret;

	ret = sg_alloc_table(sgt, 1, GFP_KERNEL);
	अगर (!ret)
		sg_set_page(sgt->sgl, page, PAGE_ALIGN(size), 0);
	वापस ret;
पूर्ण

/*
 * Create userspace mapping क्रम the DMA-coherent memory.
 */
पूर्णांक dma_common_mmap(काष्ठा device *dev, काष्ठा vm_area_काष्ठा *vma,
		व्योम *cpu_addr, dma_addr_t dma_addr, माप_प्रकार size,
		अचिन्हित दीर्घ attrs)
अणु
#अगर_घोषित CONFIG_MMU
	अचिन्हित दीर्घ user_count = vma_pages(vma);
	अचिन्हित दीर्घ count = PAGE_ALIGN(size) >> PAGE_SHIFT;
	अचिन्हित दीर्घ off = vma->vm_pgoff;
	पूर्णांक ret = -ENXIO;

	vma->vm_page_prot = dma_pgprot(dev, vma->vm_page_prot, attrs);

	अगर (dma_mmap_from_dev_coherent(dev, vma, cpu_addr, size, &ret))
		वापस ret;

	अगर (off >= count || user_count > count - off)
		वापस -ENXIO;

	वापस remap_pfn_range(vma, vma->vm_start,
			page_to_pfn(virt_to_page(cpu_addr)) + vma->vm_pgoff,
			user_count << PAGE_SHIFT, vma->vm_page_prot);
#अन्यथा
	वापस -ENXIO;
#पूर्ण_अगर /* CONFIG_MMU */
पूर्ण

काष्ठा page *dma_common_alloc_pages(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, क्रमागत dma_data_direction dir, gfp_t gfp)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);
	काष्ठा page *page;

	page = dma_alloc_contiguous(dev, size, gfp);
	अगर (!page)
		page = alloc_pages_node(dev_to_node(dev), gfp, get_order(size));
	अगर (!page)
		वापस शून्य;

	*dma_handle = ops->map_page(dev, page, 0, size, dir,
				    DMA_ATTR_SKIP_CPU_SYNC);
	अगर (*dma_handle == DMA_MAPPING_ERROR) अणु
		dma_मुक्त_contiguous(dev, page, size);
		वापस शून्य;
	पूर्ण

	स_रखो(page_address(page), 0, size);
	वापस page;
पूर्ण

व्योम dma_common_मुक्त_pages(काष्ठा device *dev, माप_प्रकार size, काष्ठा page *page,
		dma_addr_t dma_handle, क्रमागत dma_data_direction dir)
अणु
	स्थिर काष्ठा dma_map_ops *ops = get_dma_ops(dev);

	अगर (ops->unmap_page)
		ops->unmap_page(dev, dma_handle, size, dir,
				DMA_ATTR_SKIP_CPU_SYNC);
	dma_मुक्त_contiguous(dev, page, size);
पूर्ण
