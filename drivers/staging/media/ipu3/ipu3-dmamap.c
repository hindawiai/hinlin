<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Intel Corporation
 * Copyright 2018 Google LLC.
 *
 * Author: Tomasz Figa <tfiga@chromium.org>
 * Author: Yong Zhi <yong.zhi@पूर्णांकel.com>
 */

#समावेश <linux/vदो_स्मृति.h>

#समावेश "ipu3.h"
#समावेश "ipu3-css-pool.h"
#समावेश "ipu3-mmu.h"
#समावेश "ipu3-dmamap.h"

/*
 * Free a buffer allocated by imgu_dmamap_alloc_buffer()
 */
अटल व्योम imgu_dmamap_मुक्त_buffer(काष्ठा page **pages,
				    माप_प्रकार size)
अणु
	पूर्णांक count = size >> PAGE_SHIFT;

	जबतक (count--)
		__मुक्त_page(pages[count]);
	kvमुक्त(pages);
पूर्ण

/*
 * Based on the implementation of __iommu_dma_alloc_pages()
 * defined in drivers/iommu/dma-iommu.c
 */
अटल काष्ठा page **imgu_dmamap_alloc_buffer(माप_प्रकार size, gfp_t gfp)
अणु
	काष्ठा page **pages;
	अचिन्हित पूर्णांक i = 0, count = size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक order_mask = 1;
	स्थिर gfp_t high_order_gfp = __GFP_NOWARN | __GFP_NORETRY;

	/* Allocate mem क्रम array of page ptrs */
	pages = kvदो_स्मृति_array(count, माप(*pages), GFP_KERNEL);

	अगर (!pages)
		वापस शून्य;

	gfp |= __GFP_HIGHMEM | __GFP_ZERO;

	जबतक (count) अणु
		काष्ठा page *page = शून्य;
		अचिन्हित पूर्णांक order_size;

		क्रम (order_mask &= (2U << __fls(count)) - 1;
		     order_mask; order_mask &= ~order_size) अणु
			अचिन्हित पूर्णांक order = __fls(order_mask);

			order_size = 1U << order;
			page = alloc_pages((order_mask - order_size) ?
					   gfp | high_order_gfp : gfp, order);
			अगर (!page)
				जारी;
			अगर (!order)
				अवरोध;
			अगर (!PageCompound(page)) अणु
				split_page(page, order);
				अवरोध;
			पूर्ण

			__मुक्त_pages(page, order);
		पूर्ण
		अगर (!page) अणु
			imgu_dmamap_मुक्त_buffer(pages, i << PAGE_SHIFT);
			वापस शून्य;
		पूर्ण
		count -= order_size;
		जबतक (order_size--)
			pages[i++] = page++;
	पूर्ण

	वापस pages;
पूर्ण

/**
 * imgu_dmamap_alloc - allocate and map a buffer पूर्णांकo KVA
 * @imgu: काष्ठा device poपूर्णांकer
 * @map: काष्ठा to store mapping variables
 * @len: size required
 *
 * Returns:
 *  KVA on success
 *  %शून्य on failure
 */
व्योम *imgu_dmamap_alloc(काष्ठा imgu_device *imgu, काष्ठा imgu_css_map *map,
			माप_प्रकार len)
अणु
	अचिन्हित दीर्घ shअगरt = iova_shअगरt(&imgu->iova_करोमुख्य);
	काष्ठा device *dev = &imgu->pci_dev->dev;
	माप_प्रकार size = PAGE_ALIGN(len);
	पूर्णांक count = size >> PAGE_SHIFT;
	काष्ठा page **pages;
	dma_addr_t iovaddr;
	काष्ठा iova *iova;
	पूर्णांक i, rval;

	dev_dbg(dev, "%s: allocating %zu\n", __func__, size);

	iova = alloc_iova(&imgu->iova_करोमुख्य, size >> shअगरt,
			  imgu->mmu->aperture_end >> shअगरt, 0);
	अगर (!iova)
		वापस शून्य;

	pages = imgu_dmamap_alloc_buffer(size, GFP_KERNEL);
	अगर (!pages)
		जाओ out_मुक्त_iova;

	/* Call IOMMU driver to setup pgt */
	iovaddr = iova_dma_addr(&imgu->iova_करोमुख्य, iova);
	क्रम (i = 0; i < count; ++i) अणु
		rval = imgu_mmu_map(imgu->mmu, iovaddr,
				    page_to_phys(pages[i]), PAGE_SIZE);
		अगर (rval)
			जाओ out_unmap;

		iovaddr += PAGE_SIZE;
	पूर्ण

	map->vaddr = vmap(pages, count, VM_USERMAP, PAGE_KERNEL);
	अगर (!map->vaddr)
		जाओ out_unmap;

	map->pages = pages;
	map->size = size;
	map->daddr = iova_dma_addr(&imgu->iova_करोमुख्य, iova);

	dev_dbg(dev, "%s: allocated %zu @ IOVA %pad @ VA %p\n", __func__,
		size, &map->daddr, map->vaddr);

	वापस map->vaddr;

out_unmap:
	imgu_dmamap_मुक्त_buffer(pages, size);
	imgu_mmu_unmap(imgu->mmu, iova_dma_addr(&imgu->iova_करोमुख्य, iova),
		       i * PAGE_SIZE);

out_मुक्त_iova:
	__मुक्त_iova(&imgu->iova_करोमुख्य, iova);

	वापस शून्य;
पूर्ण

व्योम imgu_dmamap_unmap(काष्ठा imgu_device *imgu, काष्ठा imgu_css_map *map)
अणु
	काष्ठा iova *iova;

	iova = find_iova(&imgu->iova_करोमुख्य,
			 iova_pfn(&imgu->iova_करोमुख्य, map->daddr));
	अगर (WARN_ON(!iova))
		वापस;

	imgu_mmu_unmap(imgu->mmu, iova_dma_addr(&imgu->iova_करोमुख्य, iova),
		       iova_size(iova) << iova_shअगरt(&imgu->iova_करोमुख्य));

	__मुक्त_iova(&imgu->iova_करोमुख्य, iova);
पूर्ण

/*
 * Counterpart of imgu_dmamap_alloc
 */
व्योम imgu_dmamap_मुक्त(काष्ठा imgu_device *imgu, काष्ठा imgu_css_map *map)
अणु
	dev_dbg(&imgu->pci_dev->dev, "%s: freeing %zu @ IOVA %pad @ VA %p\n",
		__func__, map->size, &map->daddr, map->vaddr);

	अगर (!map->vaddr)
		वापस;

	imgu_dmamap_unmap(imgu, map);

	vunmap(map->vaddr);
	imgu_dmamap_मुक्त_buffer(map->pages, map->size);
	map->vaddr = शून्य;
पूर्ण

पूर्णांक imgu_dmamap_map_sg(काष्ठा imgu_device *imgu, काष्ठा scatterlist *sglist,
		       पूर्णांक nents, काष्ठा imgu_css_map *map)
अणु
	अचिन्हित दीर्घ shअगरt = iova_shअगरt(&imgu->iova_करोमुख्य);
	काष्ठा scatterlist *sg;
	काष्ठा iova *iova;
	माप_प्रकार size = 0;
	पूर्णांक i;

	क्रम_each_sg(sglist, sg, nents, i) अणु
		अगर (sg->offset)
			वापस -EINVAL;

		अगर (i != nents - 1 && !PAGE_ALIGNED(sg->length))
			वापस -EINVAL;

		size += sg->length;
	पूर्ण

	size = iova_align(&imgu->iova_करोमुख्य, size);
	dev_dbg(&imgu->pci_dev->dev, "dmamap: mapping sg %d entries, %zu pages\n",
		nents, size >> shअगरt);

	iova = alloc_iova(&imgu->iova_करोमुख्य, size >> shअगरt,
			  imgu->mmu->aperture_end >> shअगरt, 0);
	अगर (!iova)
		वापस -ENOMEM;

	dev_dbg(&imgu->pci_dev->dev, "dmamap: iova low pfn %lu, high pfn %lu\n",
		iova->pfn_lo, iova->pfn_hi);

	अगर (imgu_mmu_map_sg(imgu->mmu, iova_dma_addr(&imgu->iova_करोमुख्य, iova),
			    sglist, nents) < size)
		जाओ out_fail;

	स_रखो(map, 0, माप(*map));
	map->daddr = iova_dma_addr(&imgu->iova_करोमुख्य, iova);
	map->size = size;

	वापस 0;

out_fail:
	__मुक्त_iova(&imgu->iova_करोमुख्य, iova);

	वापस -EFAULT;
पूर्ण

पूर्णांक imgu_dmamap_init(काष्ठा imgu_device *imgu)
अणु
	अचिन्हित दीर्घ order, base_pfn;
	पूर्णांक ret = iova_cache_get();

	अगर (ret)
		वापस ret;

	order = __ffs(IPU3_PAGE_SIZE);
	base_pfn = max_t(अचिन्हित दीर्घ, 1, imgu->mmu->aperture_start >> order);
	init_iova_करोमुख्य(&imgu->iova_करोमुख्य, 1UL << order, base_pfn);

	वापस 0;
पूर्ण

व्योम imgu_dmamap_निकास(काष्ठा imgu_device *imgu)
अणु
	put_iova_करोमुख्य(&imgu->iova_करोमुख्य);
	iova_cache_put();
पूर्ण
