<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017-2018 Etnaviv Project
 */

#समावेश <linux/dma-mapping.h>

#समावेश <drm/drm_mm.h>

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_mmu.h"
#समावेश "etnaviv_perfmon.h"

#घोषणा SUBALLOC_SIZE		SZ_512K
#घोषणा SUBALLOC_GRANULE	SZ_4K
#घोषणा SUBALLOC_GRANULES	(SUBALLOC_SIZE / SUBALLOC_GRANULE)

काष्ठा etnaviv_cmdbuf_suballoc अणु
	/* suballocated dma buffer properties */
	काष्ठा device *dev;
	व्योम *vaddr;
	dma_addr_t paddr;

	/* allocation management */
	काष्ठा mutex lock;
	DECLARE_BITMAP(granule_map, SUBALLOC_GRANULES);
	पूर्णांक मुक्त_space;
	रुको_queue_head_t मुक्त_event;
पूर्ण;

काष्ठा etnaviv_cmdbuf_suballoc *
etnaviv_cmdbuf_suballoc_new(काष्ठा device *dev)
अणु
	काष्ठा etnaviv_cmdbuf_suballoc *suballoc;
	पूर्णांक ret;

	suballoc = kzalloc(माप(*suballoc), GFP_KERNEL);
	अगर (!suballoc)
		वापस ERR_PTR(-ENOMEM);

	suballoc->dev = dev;
	mutex_init(&suballoc->lock);
	init_रुकोqueue_head(&suballoc->मुक्त_event);

	BUILD_BUG_ON(ETNAVIV_SOFTPIN_START_ADDRESS < SUBALLOC_SIZE);
	suballoc->vaddr = dma_alloc_wc(dev, SUBALLOC_SIZE,
				       &suballoc->paddr, GFP_KERNEL);
	अगर (!suballoc->vaddr) अणु
		ret = -ENOMEM;
		जाओ मुक्त_suballoc;
	पूर्ण

	वापस suballoc;

मुक्त_suballoc:
	kमुक्त(suballoc);

	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक etnaviv_cmdbuf_suballoc_map(काष्ठा etnaviv_cmdbuf_suballoc *suballoc,
				काष्ठा etnaviv_iommu_context *context,
				काष्ठा etnaviv_vram_mapping *mapping,
				u32 memory_base)
अणु
	वापस etnaviv_iommu_get_suballoc_va(context, mapping, memory_base,
					     suballoc->paddr, SUBALLOC_SIZE);
पूर्ण

व्योम etnaviv_cmdbuf_suballoc_unmap(काष्ठा etnaviv_iommu_context *context,
				   काष्ठा etnaviv_vram_mapping *mapping)
अणु
	etnaviv_iommu_put_suballoc_va(context, mapping);
पूर्ण

व्योम etnaviv_cmdbuf_suballoc_destroy(काष्ठा etnaviv_cmdbuf_suballoc *suballoc)
अणु
	dma_मुक्त_wc(suballoc->dev, SUBALLOC_SIZE, suballoc->vaddr,
		    suballoc->paddr);
	kमुक्त(suballoc);
पूर्ण

पूर्णांक etnaviv_cmdbuf_init(काष्ठा etnaviv_cmdbuf_suballoc *suballoc,
			काष्ठा etnaviv_cmdbuf *cmdbuf, u32 size)
अणु
	पूर्णांक granule_offs, order, ret;

	cmdbuf->suballoc = suballoc;
	cmdbuf->size = size;

	order = order_base_2(ALIGN(size, SUBALLOC_GRANULE) / SUBALLOC_GRANULE);
retry:
	mutex_lock(&suballoc->lock);
	granule_offs = biपंचांगap_find_मुक्त_region(suballoc->granule_map,
					SUBALLOC_GRANULES, order);
	अगर (granule_offs < 0) अणु
		suballoc->मुक्त_space = 0;
		mutex_unlock(&suballoc->lock);
		ret = रुको_event_पूर्णांकerruptible_समयout(suballoc->मुक्त_event,
						       suballoc->मुक्त_space,
						       msecs_to_jअगरfies(10 * 1000));
		अगर (!ret) अणु
			dev_err(suballoc->dev,
				"Timeout waiting for cmdbuf space\n");
			वापस -ETIMEDOUT;
		पूर्ण
		जाओ retry;
	पूर्ण
	mutex_unlock(&suballoc->lock);
	cmdbuf->suballoc_offset = granule_offs * SUBALLOC_GRANULE;
	cmdbuf->vaddr = suballoc->vaddr + cmdbuf->suballoc_offset;

	वापस 0;
पूर्ण

व्योम etnaviv_cmdbuf_मुक्त(काष्ठा etnaviv_cmdbuf *cmdbuf)
अणु
	काष्ठा etnaviv_cmdbuf_suballoc *suballoc = cmdbuf->suballoc;
	पूर्णांक order = order_base_2(ALIGN(cmdbuf->size, SUBALLOC_GRANULE) /
				 SUBALLOC_GRANULE);

	mutex_lock(&suballoc->lock);
	biपंचांगap_release_region(suballoc->granule_map,
			      cmdbuf->suballoc_offset / SUBALLOC_GRANULE,
			      order);
	suballoc->मुक्त_space = 1;
	mutex_unlock(&suballoc->lock);
	wake_up_all(&suballoc->मुक्त_event);
पूर्ण

u32 etnaviv_cmdbuf_get_va(काष्ठा etnaviv_cmdbuf *buf,
			  काष्ठा etnaviv_vram_mapping *mapping)
अणु
	वापस mapping->iova + buf->suballoc_offset;
पूर्ण

dma_addr_t etnaviv_cmdbuf_get_pa(काष्ठा etnaviv_cmdbuf *buf)
अणु
	वापस buf->suballoc->paddr + buf->suballoc_offset;
पूर्ण
