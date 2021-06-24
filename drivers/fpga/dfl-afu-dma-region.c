<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Accelerated Function Unit (AFU) DMA Region Management
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>

#समावेश "dfl-afu.h"

व्योम afu_dma_region_init(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_afu *afu = dfl_fpga_pdata_get_निजी(pdata);

	afu->dma_regions = RB_ROOT;
पूर्ण

/**
 * afu_dma_pin_pages - pin pages of given dma memory region
 * @pdata: feature device platक्रमm data
 * @region: dma memory region to be pinned
 *
 * Pin all the pages of given dfl_afu_dma_region.
 * Return 0 क्रम success or negative error code.
 */
अटल पूर्णांक afu_dma_pin_pages(काष्ठा dfl_feature_platक्रमm_data *pdata,
			     काष्ठा dfl_afu_dma_region *region)
अणु
	पूर्णांक npages = region->length >> PAGE_SHIFT;
	काष्ठा device *dev = &pdata->dev->dev;
	पूर्णांक ret, pinned;

	ret = account_locked_vm(current->mm, npages, true);
	अगर (ret)
		वापस ret;

	region->pages = kसुस्मृति(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!region->pages) अणु
		ret = -ENOMEM;
		जाओ unlock_vm;
	पूर्ण

	pinned = pin_user_pages_fast(region->user_addr, npages, FOLL_WRITE,
				     region->pages);
	अगर (pinned < 0) अणु
		ret = pinned;
		जाओ मुक्त_pages;
	पूर्ण अन्यथा अगर (pinned != npages) अणु
		ret = -EFAULT;
		जाओ unpin_pages;
	पूर्ण

	dev_dbg(dev, "%d pages pinned\n", pinned);

	वापस 0;

unpin_pages:
	unpin_user_pages(region->pages, pinned);
मुक्त_pages:
	kमुक्त(region->pages);
unlock_vm:
	account_locked_vm(current->mm, npages, false);
	वापस ret;
पूर्ण

/**
 * afu_dma_unpin_pages - unpin pages of given dma memory region
 * @pdata: feature device platक्रमm data
 * @region: dma memory region to be unpinned
 *
 * Unpin all the pages of given dfl_afu_dma_region.
 * Return 0 क्रम success or negative error code.
 */
अटल व्योम afu_dma_unpin_pages(काष्ठा dfl_feature_platक्रमm_data *pdata,
				काष्ठा dfl_afu_dma_region *region)
अणु
	दीर्घ npages = region->length >> PAGE_SHIFT;
	काष्ठा device *dev = &pdata->dev->dev;

	unpin_user_pages(region->pages, npages);
	kमुक्त(region->pages);
	account_locked_vm(current->mm, npages, false);

	dev_dbg(dev, "%ld pages unpinned\n", npages);
पूर्ण

/**
 * afu_dma_check_continuous_pages - check अगर pages are continuous
 * @region: dma memory region
 *
 * Return true अगर pages of given dma memory region have continuous physical
 * address, otherwise वापस false.
 */
अटल bool afu_dma_check_continuous_pages(काष्ठा dfl_afu_dma_region *region)
अणु
	पूर्णांक npages = region->length >> PAGE_SHIFT;
	पूर्णांक i;

	क्रम (i = 0; i < npages - 1; i++)
		अगर (page_to_pfn(region->pages[i]) + 1 !=
				page_to_pfn(region->pages[i + 1]))
			वापस false;

	वापस true;
पूर्ण

/**
 * dma_region_check_iova - check अगर memory area is fully contained in the region
 * @region: dma memory region
 * @iova: address of the dma memory area
 * @size: size of the dma memory area
 *
 * Compare the dma memory area defined by @iova and @size with given dma region.
 * Return true अगर memory area is fully contained in the region, otherwise false.
 */
अटल bool dma_region_check_iova(काष्ठा dfl_afu_dma_region *region,
				  u64 iova, u64 size)
अणु
	अगर (!size && region->iova != iova)
		वापस false;

	वापस (region->iova <= iova) &&
		(region->length + region->iova >= iova + size);
पूर्ण

/**
 * afu_dma_region_add - add given dma region to rbtree
 * @pdata: feature device platक्रमm data
 * @region: dma region to be added
 *
 * Return 0 क्रम success, -EEXIST अगर dma region has alपढ़ोy been added.
 *
 * Needs to be called with pdata->lock heold.
 */
अटल पूर्णांक afu_dma_region_add(काष्ठा dfl_feature_platक्रमm_data *pdata,
			      काष्ठा dfl_afu_dma_region *region)
अणु
	काष्ठा dfl_afu *afu = dfl_fpga_pdata_get_निजी(pdata);
	काष्ठा rb_node **new, *parent = शून्य;

	dev_dbg(&pdata->dev->dev, "add region (iova = %llx)\n",
		(अचिन्हित दीर्घ दीर्घ)region->iova);

	new = &afu->dma_regions.rb_node;

	जबतक (*new) अणु
		काष्ठा dfl_afu_dma_region *this;

		this = container_of(*new, काष्ठा dfl_afu_dma_region, node);

		parent = *new;

		अगर (dma_region_check_iova(this, region->iova, region->length))
			वापस -EEXIST;

		अगर (region->iova < this->iova)
			new = &((*new)->rb_left);
		अन्यथा अगर (region->iova > this->iova)
			new = &((*new)->rb_right);
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	rb_link_node(&region->node, parent, new);
	rb_insert_color(&region->node, &afu->dma_regions);

	वापस 0;
पूर्ण

/**
 * afu_dma_region_हटाओ - हटाओ given dma region from rbtree
 * @pdata: feature device platक्रमm data
 * @region: dma region to be हटाओd
 *
 * Needs to be called with pdata->lock heold.
 */
अटल व्योम afu_dma_region_हटाओ(काष्ठा dfl_feature_platक्रमm_data *pdata,
				  काष्ठा dfl_afu_dma_region *region)
अणु
	काष्ठा dfl_afu *afu;

	dev_dbg(&pdata->dev->dev, "del region (iova = %llx)\n",
		(अचिन्हित दीर्घ दीर्घ)region->iova);

	afu = dfl_fpga_pdata_get_निजी(pdata);
	rb_erase(&region->node, &afu->dma_regions);
पूर्ण

/**
 * afu_dma_region_destroy - destroy all regions in rbtree
 * @pdata: feature device platक्रमm data
 *
 * Needs to be called with pdata->lock heold.
 */
व्योम afu_dma_region_destroy(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_afu *afu = dfl_fpga_pdata_get_निजी(pdata);
	काष्ठा rb_node *node = rb_first(&afu->dma_regions);
	काष्ठा dfl_afu_dma_region *region;

	जबतक (node) अणु
		region = container_of(node, काष्ठा dfl_afu_dma_region, node);

		dev_dbg(&pdata->dev->dev, "del region (iova = %llx)\n",
			(अचिन्हित दीर्घ दीर्घ)region->iova);

		rb_erase(node, &afu->dma_regions);

		अगर (region->iova)
			dma_unmap_page(dfl_fpga_pdata_to_parent(pdata),
				       region->iova, region->length,
				       DMA_BIसूचीECTIONAL);

		अगर (region->pages)
			afu_dma_unpin_pages(pdata, region);

		node = rb_next(node);
		kमुक्त(region);
	पूर्ण
पूर्ण

/**
 * afu_dma_region_find - find the dma region from rbtree based on iova and size
 * @pdata: feature device platक्रमm data
 * @iova: address of the dma memory area
 * @size: size of the dma memory area
 *
 * It finds the dma region from the rbtree based on @iova and @size:
 * - अगर @size == 0, it finds the dma region which starts from @iova
 * - otherwise, it finds the dma region which fully contains
 *   [@iova, @iova+size)
 * If nothing is matched वापसs शून्य.
 *
 * Needs to be called with pdata->lock held.
 */
काष्ठा dfl_afu_dma_region *
afu_dma_region_find(काष्ठा dfl_feature_platक्रमm_data *pdata, u64 iova, u64 size)
अणु
	काष्ठा dfl_afu *afu = dfl_fpga_pdata_get_निजी(pdata);
	काष्ठा rb_node *node = afu->dma_regions.rb_node;
	काष्ठा device *dev = &pdata->dev->dev;

	जबतक (node) अणु
		काष्ठा dfl_afu_dma_region *region;

		region = container_of(node, काष्ठा dfl_afu_dma_region, node);

		अगर (dma_region_check_iova(region, iova, size)) अणु
			dev_dbg(dev, "find region (iova = %llx)\n",
				(अचिन्हित दीर्घ दीर्घ)region->iova);
			वापस region;
		पूर्ण

		अगर (iova < region->iova)
			node = node->rb_left;
		अन्यथा अगर (iova > region->iova)
			node = node->rb_right;
		अन्यथा
			/* the iova region is not fully covered. */
			अवरोध;
	पूर्ण

	dev_dbg(dev, "region with iova %llx and size %llx is not found\n",
		(अचिन्हित दीर्घ दीर्घ)iova, (अचिन्हित दीर्घ दीर्घ)size);

	वापस शून्य;
पूर्ण

/**
 * afu_dma_region_find_iova - find the dma region from rbtree by iova
 * @pdata: feature device platक्रमm data
 * @iova: address of the dma region
 *
 * Needs to be called with pdata->lock held.
 */
अटल काष्ठा dfl_afu_dma_region *
afu_dma_region_find_iova(काष्ठा dfl_feature_platक्रमm_data *pdata, u64 iova)
अणु
	वापस afu_dma_region_find(pdata, iova, 0);
पूर्ण

/**
 * afu_dma_map_region - map memory region क्रम dma
 * @pdata: feature device platक्रमm data
 * @user_addr: address of the memory region
 * @length: size of the memory region
 * @iova: poपूर्णांकer of iova address
 *
 * Map memory region defined by @user_addr and @length, and वापस dma address
 * of the memory region via @iova.
 * Return 0 क्रम success, otherwise error code.
 */
पूर्णांक afu_dma_map_region(काष्ठा dfl_feature_platक्रमm_data *pdata,
		       u64 user_addr, u64 length, u64 *iova)
अणु
	काष्ठा dfl_afu_dma_region *region;
	पूर्णांक ret;

	/*
	 * Check Inमाला_दो, only accept page-aligned user memory region with
	 * valid length.
	 */
	अगर (!PAGE_ALIGNED(user_addr) || !PAGE_ALIGNED(length) || !length)
		वापस -EINVAL;

	/* Check overflow */
	अगर (user_addr + length < user_addr)
		वापस -EINVAL;

	region = kzalloc(माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	region->user_addr = user_addr;
	region->length = length;

	/* Pin the user memory region */
	ret = afu_dma_pin_pages(pdata, region);
	अगर (ret) अणु
		dev_err(&pdata->dev->dev, "failed to pin memory region\n");
		जाओ मुक्त_region;
	पूर्ण

	/* Only accept continuous pages, वापस error अन्यथा */
	अगर (!afu_dma_check_continuous_pages(region)) अणु
		dev_err(&pdata->dev->dev, "pages are not continuous\n");
		ret = -EINVAL;
		जाओ unpin_pages;
	पूर्ण

	/* As pages are continuous then start to करो DMA mapping */
	region->iova = dma_map_page(dfl_fpga_pdata_to_parent(pdata),
				    region->pages[0], 0,
				    region->length,
				    DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(dfl_fpga_pdata_to_parent(pdata), region->iova)) अणु
		dev_err(&pdata->dev->dev, "failed to map for dma\n");
		ret = -EFAULT;
		जाओ unpin_pages;
	पूर्ण

	*iova = region->iova;

	mutex_lock(&pdata->lock);
	ret = afu_dma_region_add(pdata, region);
	mutex_unlock(&pdata->lock);
	अगर (ret) अणु
		dev_err(&pdata->dev->dev, "failed to add dma region\n");
		जाओ unmap_dma;
	पूर्ण

	वापस 0;

unmap_dma:
	dma_unmap_page(dfl_fpga_pdata_to_parent(pdata),
		       region->iova, region->length, DMA_BIसूचीECTIONAL);
unpin_pages:
	afu_dma_unpin_pages(pdata, region);
मुक्त_region:
	kमुक्त(region);
	वापस ret;
पूर्ण

/**
 * afu_dma_unmap_region - unmap dma memory region
 * @pdata: feature device platक्रमm data
 * @iova: dma address of the region
 *
 * Unmap dma memory region based on @iova.
 * Return 0 क्रम success, otherwise error code.
 */
पूर्णांक afu_dma_unmap_region(काष्ठा dfl_feature_platक्रमm_data *pdata, u64 iova)
अणु
	काष्ठा dfl_afu_dma_region *region;

	mutex_lock(&pdata->lock);
	region = afu_dma_region_find_iova(pdata, iova);
	अगर (!region) अणु
		mutex_unlock(&pdata->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (region->in_use) अणु
		mutex_unlock(&pdata->lock);
		वापस -EBUSY;
	पूर्ण

	afu_dma_region_हटाओ(pdata, region);
	mutex_unlock(&pdata->lock);

	dma_unmap_page(dfl_fpga_pdata_to_parent(pdata),
		       region->iova, region->length, DMA_BIसूचीECTIONAL);
	afu_dma_unpin_pages(pdata, region);
	kमुक्त(region);

	वापस 0;
पूर्ण
