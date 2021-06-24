<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Intel Corporation

#समावेश <linux/device.h>

#समावेश "ipu3.h"
#समावेश "ipu3-css-pool.h"
#समावेश "ipu3-dmamap.h"

पूर्णांक imgu_css_dma_buffer_resize(काष्ठा imgu_device *imgu,
			       काष्ठा imgu_css_map *map, माप_प्रकार size)
अणु
	अगर (map->size < size && map->vaddr) अणु
		dev_warn(&imgu->pci_dev->dev, "dma buf resized from %zu to %zu",
			 map->size, size);

		imgu_dmamap_मुक्त(imgu, map);
		अगर (!imgu_dmamap_alloc(imgu, map, size))
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम imgu_css_pool_cleanup(काष्ठा imgu_device *imgu, काष्ठा imgu_css_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IPU3_CSS_POOL_SIZE; i++)
		imgu_dmamap_मुक्त(imgu, &pool->entry[i].param);
पूर्ण

पूर्णांक imgu_css_pool_init(काष्ठा imgu_device *imgu, काष्ठा imgu_css_pool *pool,
		       माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < IPU3_CSS_POOL_SIZE; i++) अणु
		pool->entry[i].valid = false;
		अगर (size == 0) अणु
			pool->entry[i].param.vaddr = शून्य;
			जारी;
		पूर्ण

		अगर (!imgu_dmamap_alloc(imgu, &pool->entry[i].param, size))
			जाओ fail;
	पूर्ण

	pool->last = IPU3_CSS_POOL_SIZE;

	वापस 0;

fail:
	imgu_css_pool_cleanup(imgu, pool);
	वापस -ENOMEM;
पूर्ण

/*
 * Allocate a new parameter via recycling the oldest entry in the pool.
 */
व्योम imgu_css_pool_get(काष्ठा imgu_css_pool *pool)
अणु
	/* Get the oldest entry */
	u32 n = (pool->last + 1) % IPU3_CSS_POOL_SIZE;

	pool->entry[n].valid = true;
	pool->last = n;
पूर्ण

/*
 * Unकरो, क्रम all practical purposes, the effect of pool_get().
 */
व्योम imgu_css_pool_put(काष्ठा imgu_css_pool *pool)
अणु
	pool->entry[pool->last].valid = false;
	pool->last = (pool->last + IPU3_CSS_POOL_SIZE - 1) % IPU3_CSS_POOL_SIZE;
पूर्ण

/**
 * imgu_css_pool_last - Retrieve the nth pool entry from last
 *
 * @pool: a poपूर्णांकer to &काष्ठा imgu_css_pool.
 * @n: the distance to the last index.
 *
 * Returns:
 *  The nth entry from last or null map to indicate no frame stored.
 */
स्थिर काष्ठा imgu_css_map *
imgu_css_pool_last(काष्ठा imgu_css_pool *pool, अचिन्हित पूर्णांक n)
अणु
	अटल स्थिर काष्ठा imgu_css_map null_map = अणु 0 पूर्ण;
	पूर्णांक i = (pool->last + IPU3_CSS_POOL_SIZE - n) % IPU3_CSS_POOL_SIZE;

	WARN_ON(n >= IPU3_CSS_POOL_SIZE);

	अगर (!pool->entry[i].valid)
		वापस &null_map;

	वापस &pool->entry[i].param;
पूर्ण
