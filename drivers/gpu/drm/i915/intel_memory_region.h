<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_MEMORY_REGION_H__
#घोषणा __INTEL_MEMORY_REGION_H__

#समावेश <linux/kref.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mutex.h>
#समावेश <linux/io-mapping.h>
#समावेश <drm/drm_mm.h>

#समावेश "i915_buddy.h"

काष्ठा drm_i915_निजी;
काष्ठा drm_i915_gem_object;
काष्ठा पूर्णांकel_memory_region;
काष्ठा sg_table;

/**
 *  Base memory type
 */
क्रमागत पूर्णांकel_memory_type अणु
	INTEL_MEMORY_SYSTEM = 0,
	INTEL_MEMORY_LOCAL,
	INTEL_MEMORY_STOLEN_SYSTEM,
पूर्ण;

क्रमागत पूर्णांकel_region_id अणु
	INTEL_REGION_SMEM = 0,
	INTEL_REGION_LMEM,
	INTEL_REGION_STOLEN_SMEM,
	INTEL_REGION_UNKNOWN, /* Should be last */
पूर्ण;

#घोषणा REGION_SMEM     BIT(INTEL_REGION_SMEM)
#घोषणा REGION_LMEM     BIT(INTEL_REGION_LMEM)
#घोषणा REGION_STOLEN_SMEM   BIT(INTEL_REGION_STOLEN_SMEM)

#घोषणा I915_ALLOC_MIN_PAGE_SIZE  BIT(0)
#घोषणा I915_ALLOC_CONTIGUOUS     BIT(1)

#घोषणा क्रम_each_memory_region(mr, i915, id) \
	क्रम (id = 0; id < ARRAY_SIZE((i915)->mm.regions); id++) \
		क्रम_each_अगर((mr) = (i915)->mm.regions[id])

काष्ठा पूर्णांकel_memory_region_ops अणु
	अचिन्हित पूर्णांक flags;

	पूर्णांक (*init)(काष्ठा पूर्णांकel_memory_region *mem);
	व्योम (*release)(काष्ठा पूर्णांकel_memory_region *mem);

	पूर्णांक (*init_object)(काष्ठा पूर्णांकel_memory_region *mem,
			   काष्ठा drm_i915_gem_object *obj,
			   resource_माप_प्रकार size,
			   अचिन्हित पूर्णांक flags);
पूर्ण;

काष्ठा पूर्णांकel_memory_region अणु
	काष्ठा drm_i915_निजी *i915;

	स्थिर काष्ठा पूर्णांकel_memory_region_ops *ops;

	काष्ठा io_mapping iomap;
	काष्ठा resource region;

	/* For fake LMEM */
	काष्ठा drm_mm_node fake_mappable;

	काष्ठा i915_buddy_mm mm;
	काष्ठा mutex mm_lock;

	काष्ठा kref kref;

	resource_माप_प्रकार io_start;
	resource_माप_प्रकार min_page_size;
	resource_माप_प्रकार total;
	resource_माप_प्रकार avail;

	u16 type;
	u16 instance;
	क्रमागत पूर्णांकel_region_id id;
	अक्षर name[8];

	काष्ठा list_head reserved;

	dma_addr_t remap_addr;

	काष्ठा अणु
		काष्ठा mutex lock; /* Protects access to objects */
		काष्ठा list_head list;
		काष्ठा list_head purgeable;
	पूर्ण objects;
पूर्ण;

पूर्णांक पूर्णांकel_memory_region_init_buddy(काष्ठा पूर्णांकel_memory_region *mem);
व्योम पूर्णांकel_memory_region_release_buddy(काष्ठा पूर्णांकel_memory_region *mem);

पूर्णांक __पूर्णांकel_memory_region_get_pages_buddy(काष्ठा पूर्णांकel_memory_region *mem,
					  resource_माप_प्रकार size,
					  अचिन्हित पूर्णांक flags,
					  काष्ठा list_head *blocks);
काष्ठा i915_buddy_block *
__पूर्णांकel_memory_region_get_block_buddy(काष्ठा पूर्णांकel_memory_region *mem,
				      resource_माप_प्रकार size,
				      अचिन्हित पूर्णांक flags);
व्योम __पूर्णांकel_memory_region_put_pages_buddy(काष्ठा पूर्णांकel_memory_region *mem,
					   काष्ठा list_head *blocks);
व्योम __पूर्णांकel_memory_region_put_block_buddy(काष्ठा i915_buddy_block *block);

पूर्णांक पूर्णांकel_memory_region_reserve(काष्ठा पूर्णांकel_memory_region *mem,
				u64 offset, u64 size);

काष्ठा पूर्णांकel_memory_region *
पूर्णांकel_memory_region_create(काष्ठा drm_i915_निजी *i915,
			   resource_माप_प्रकार start,
			   resource_माप_प्रकार size,
			   resource_माप_प्रकार min_page_size,
			   resource_माप_प्रकार io_start,
			   स्थिर काष्ठा पूर्णांकel_memory_region_ops *ops);

काष्ठा पूर्णांकel_memory_region *
पूर्णांकel_memory_region_get(काष्ठा पूर्णांकel_memory_region *mem);
व्योम पूर्णांकel_memory_region_put(काष्ठा पूर्णांकel_memory_region *mem);

पूर्णांक पूर्णांकel_memory_regions_hw_probe(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_memory_regions_driver_release(काष्ठा drm_i915_निजी *i915);
काष्ठा पूर्णांकel_memory_region *
पूर्णांकel_memory_region_by_type(काष्ठा drm_i915_निजी *i915,
			    क्रमागत पूर्णांकel_memory_type mem_type);

__म_लिखो(2, 3) व्योम
पूर्णांकel_memory_region_set_name(काष्ठा पूर्णांकel_memory_region *mem,
			     स्थिर अक्षर *fmt, ...);

#पूर्ण_अगर
