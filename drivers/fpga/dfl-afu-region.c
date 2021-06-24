<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम FPGA Accelerated Function Unit (AFU) MMIO Region Management
 *
 * Copyright (C) 2017-2018 Intel Corporation, Inc.
 *
 * Authors:
 *   Wu Hao <hao.wu@पूर्णांकel.com>
 *   Xiao Guangrong <guangrong.xiao@linux.पूर्णांकel.com>
 */
#समावेश "dfl-afu.h"

/**
 * afu_mmio_region_init - init function क्रम afu mmio region support
 * @pdata: afu platक्रमm device's pdata.
 */
व्योम afu_mmio_region_init(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_afu *afu = dfl_fpga_pdata_get_निजी(pdata);

	INIT_LIST_HEAD(&afu->regions);
पूर्ण

#घोषणा क्रम_each_region(region, afu)	\
	list_क्रम_each_entry((region), &(afu)->regions, node)

अटल काष्ठा dfl_afu_mmio_region *get_region_by_index(काष्ठा dfl_afu *afu,
						       u32 region_index)
अणु
	काष्ठा dfl_afu_mmio_region *region;

	क्रम_each_region(region, afu)
		अगर (region->index == region_index)
			वापस region;

	वापस शून्य;
पूर्ण

/**
 * afu_mmio_region_add - add a mmio region to given feature dev.
 *
 * @region_index: region index.
 * @region_size: region size.
 * @phys: region's physical address of this region.
 * @flags: region flags (access permission).
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक afu_mmio_region_add(काष्ठा dfl_feature_platक्रमm_data *pdata,
			u32 region_index, u64 region_size, u64 phys, u32 flags)
अणु
	काष्ठा dfl_afu_mmio_region *region;
	काष्ठा dfl_afu *afu;
	पूर्णांक ret = 0;

	region = devm_kzalloc(&pdata->dev->dev, माप(*region), GFP_KERNEL);
	अगर (!region)
		वापस -ENOMEM;

	region->index = region_index;
	region->size = region_size;
	region->phys = phys;
	region->flags = flags;

	mutex_lock(&pdata->lock);

	afu = dfl_fpga_pdata_get_निजी(pdata);

	/* check अगर @index alपढ़ोy exists */
	अगर (get_region_by_index(afu, region_index)) अणु
		mutex_unlock(&pdata->lock);
		ret = -EEXIST;
		जाओ निकास;
	पूर्ण

	region_size = PAGE_ALIGN(region_size);
	region->offset = afu->region_cur_offset;
	list_add(&region->node, &afu->regions);

	afu->region_cur_offset += region_size;
	afu->num_regions++;
	mutex_unlock(&pdata->lock);

	वापस 0;

निकास:
	devm_kमुक्त(&pdata->dev->dev, region);
	वापस ret;
पूर्ण

/**
 * afu_mmio_region_destroy - destroy all mmio regions under given feature dev.
 * @pdata: afu platक्रमm device's pdata.
 */
व्योम afu_mmio_region_destroy(काष्ठा dfl_feature_platक्रमm_data *pdata)
अणु
	काष्ठा dfl_afu *afu = dfl_fpga_pdata_get_निजी(pdata);
	काष्ठा dfl_afu_mmio_region *पंचांगp, *region;

	list_क्रम_each_entry_safe(region, पंचांगp, &afu->regions, node)
		devm_kमुक्त(&pdata->dev->dev, region);
पूर्ण

/**
 * afu_mmio_region_get_by_index - find an afu region by index.
 * @pdata: afu platक्रमm device's pdata.
 * @region_index: region index.
 * @pregion: ptr to region क्रम result.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक afu_mmio_region_get_by_index(काष्ठा dfl_feature_platक्रमm_data *pdata,
				 u32 region_index,
				 काष्ठा dfl_afu_mmio_region *pregion)
अणु
	काष्ठा dfl_afu_mmio_region *region;
	काष्ठा dfl_afu *afu;
	पूर्णांक ret = 0;

	mutex_lock(&pdata->lock);
	afu = dfl_fpga_pdata_get_निजी(pdata);
	region = get_region_by_index(afu, region_index);
	अगर (!region) अणु
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण
	*pregion = *region;
निकास:
	mutex_unlock(&pdata->lock);
	वापस ret;
पूर्ण

/**
 * afu_mmio_region_get_by_offset - find an afu mmio region by offset and size
 *
 * @pdata: afu platक्रमm device's pdata.
 * @offset: region offset from start of the device fd.
 * @size: region size.
 * @pregion: ptr to region क्रम result.
 *
 * Find the region which fully contains the region described by input
 * parameters (offset and size) from the feature dev's region linked list.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक afu_mmio_region_get_by_offset(काष्ठा dfl_feature_platक्रमm_data *pdata,
				  u64 offset, u64 size,
				  काष्ठा dfl_afu_mmio_region *pregion)
अणु
	काष्ठा dfl_afu_mmio_region *region;
	काष्ठा dfl_afu *afu;
	पूर्णांक ret = 0;

	mutex_lock(&pdata->lock);
	afu = dfl_fpga_pdata_get_निजी(pdata);
	क्रम_each_region(region, afu)
		अगर (region->offset <= offset &&
		    region->offset + region->size >= offset + size) अणु
			*pregion = *region;
			जाओ निकास;
		पूर्ण
	ret = -EINVAL;
निकास:
	mutex_unlock(&pdata->lock);
	वापस ret;
पूर्ण
