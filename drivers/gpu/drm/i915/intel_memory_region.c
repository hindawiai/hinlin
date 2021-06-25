<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "intel_memory_region.h"
#समावेश "i915_drv.h"

अटल स्थिर काष्ठा अणु
	u16 class;
	u16 instance;
पूर्ण पूर्णांकel_region_map[] = अणु
	[INTEL_REGION_SMEM] = अणु
		.class = INTEL_MEMORY_SYSTEM,
		.instance = 0,
	पूर्ण,
	[INTEL_REGION_LMEM] = अणु
		.class = INTEL_MEMORY_LOCAL,
		.instance = 0,
	पूर्ण,
	[INTEL_REGION_STOLEN_SMEM] = अणु
		.class = INTEL_MEMORY_STOLEN_SYSTEM,
		.instance = 0,
	पूर्ण,
पूर्ण;

काष्ठा पूर्णांकel_memory_region *
पूर्णांकel_memory_region_by_type(काष्ठा drm_i915_निजी *i915,
			    क्रमागत पूर्णांकel_memory_type mem_type)
अणु
	काष्ठा पूर्णांकel_memory_region *mr;
	पूर्णांक id;

	क्रम_each_memory_region(mr, i915, id)
		अगर (mr->type == mem_type)
			वापस mr;

	वापस शून्य;
पूर्ण

अटल u64
पूर्णांकel_memory_region_मुक्त_pages(काष्ठा पूर्णांकel_memory_region *mem,
			       काष्ठा list_head *blocks)
अणु
	काष्ठा i915_buddy_block *block, *on;
	u64 size = 0;

	list_क्रम_each_entry_safe(block, on, blocks, link) अणु
		size += i915_buddy_block_size(&mem->mm, block);
		i915_buddy_मुक्त(&mem->mm, block);
	पूर्ण
	INIT_LIST_HEAD(blocks);

	वापस size;
पूर्ण

व्योम
__पूर्णांकel_memory_region_put_pages_buddy(काष्ठा पूर्णांकel_memory_region *mem,
				      काष्ठा list_head *blocks)
अणु
	mutex_lock(&mem->mm_lock);
	mem->avail += पूर्णांकel_memory_region_मुक्त_pages(mem, blocks);
	mutex_unlock(&mem->mm_lock);
पूर्ण

व्योम
__पूर्णांकel_memory_region_put_block_buddy(काष्ठा i915_buddy_block *block)
अणु
	काष्ठा list_head blocks;

	INIT_LIST_HEAD(&blocks);
	list_add(&block->link, &blocks);
	__पूर्णांकel_memory_region_put_pages_buddy(block->निजी, &blocks);
पूर्ण

पूर्णांक
__पूर्णांकel_memory_region_get_pages_buddy(काष्ठा पूर्णांकel_memory_region *mem,
				      resource_माप_प्रकार size,
				      अचिन्हित पूर्णांक flags,
				      काष्ठा list_head *blocks)
अणु
	अचिन्हित पूर्णांक min_order = 0;
	अचिन्हित दीर्घ n_pages;

	GEM_BUG_ON(!IS_ALIGNED(size, mem->mm.chunk_size));
	GEM_BUG_ON(!list_empty(blocks));

	अगर (flags & I915_ALLOC_MIN_PAGE_SIZE) अणु
		min_order = ilog2(mem->min_page_size) -
			    ilog2(mem->mm.chunk_size);
	पूर्ण

	अगर (flags & I915_ALLOC_CONTIGUOUS) अणु
		size = roundup_घात_of_two(size);
		min_order = ilog2(size) - ilog2(mem->mm.chunk_size);
	पूर्ण

	अगर (size > mem->mm.size)
		वापस -E2BIG;

	n_pages = size >> ilog2(mem->mm.chunk_size);

	mutex_lock(&mem->mm_lock);

	करो अणु
		काष्ठा i915_buddy_block *block;
		अचिन्हित पूर्णांक order;

		order = fls(n_pages) - 1;
		GEM_BUG_ON(order > mem->mm.max_order);
		GEM_BUG_ON(order < min_order);

		करो अणु
			block = i915_buddy_alloc(&mem->mm, order);
			अगर (!IS_ERR(block))
				अवरोध;

			अगर (order-- == min_order)
				जाओ err_मुक्त_blocks;
		पूर्ण जबतक (1);

		n_pages -= BIT(order);

		block->निजी = mem;
		list_add_tail(&block->link, blocks);

		अगर (!n_pages)
			अवरोध;
	पूर्ण जबतक (1);

	mem->avail -= size;
	mutex_unlock(&mem->mm_lock);
	वापस 0;

err_मुक्त_blocks:
	पूर्णांकel_memory_region_मुक्त_pages(mem, blocks);
	mutex_unlock(&mem->mm_lock);
	वापस -ENXIO;
पूर्ण

काष्ठा i915_buddy_block *
__पूर्णांकel_memory_region_get_block_buddy(काष्ठा पूर्णांकel_memory_region *mem,
				      resource_माप_प्रकार size,
				      अचिन्हित पूर्णांक flags)
अणु
	काष्ठा i915_buddy_block *block;
	LIST_HEAD(blocks);
	पूर्णांक ret;

	ret = __पूर्णांकel_memory_region_get_pages_buddy(mem, size, flags, &blocks);
	अगर (ret)
		वापस ERR_PTR(ret);

	block = list_first_entry(&blocks, typeof(*block), link);
	list_del_init(&block->link);
	वापस block;
पूर्ण

पूर्णांक पूर्णांकel_memory_region_init_buddy(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	वापस i915_buddy_init(&mem->mm, resource_size(&mem->region),
			       PAGE_SIZE);
पूर्ण

व्योम पूर्णांकel_memory_region_release_buddy(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	i915_buddy_मुक्त_list(&mem->mm, &mem->reserved);
	i915_buddy_fini(&mem->mm);
पूर्ण

पूर्णांक पूर्णांकel_memory_region_reserve(काष्ठा पूर्णांकel_memory_region *mem,
				u64 offset, u64 size)
अणु
	पूर्णांक ret;

	mutex_lock(&mem->mm_lock);
	ret = i915_buddy_alloc_range(&mem->mm, &mem->reserved, offset, size);
	mutex_unlock(&mem->mm_lock);

	वापस ret;
पूर्ण

काष्ठा पूर्णांकel_memory_region *
पूर्णांकel_memory_region_create(काष्ठा drm_i915_निजी *i915,
			   resource_माप_प्रकार start,
			   resource_माप_प्रकार size,
			   resource_माप_प्रकार min_page_size,
			   resource_माप_प्रकार io_start,
			   स्थिर काष्ठा पूर्णांकel_memory_region_ops *ops)
अणु
	काष्ठा पूर्णांकel_memory_region *mem;
	पूर्णांक err;

	mem = kzalloc(माप(*mem), GFP_KERNEL);
	अगर (!mem)
		वापस ERR_PTR(-ENOMEM);

	mem->i915 = i915;
	mem->region = (काष्ठा resource)DEFINE_RES_MEM(start, size);
	mem->io_start = io_start;
	mem->min_page_size = min_page_size;
	mem->ops = ops;
	mem->total = size;
	mem->avail = mem->total;

	mutex_init(&mem->objects.lock);
	INIT_LIST_HEAD(&mem->objects.list);
	INIT_LIST_HEAD(&mem->objects.purgeable);
	INIT_LIST_HEAD(&mem->reserved);

	mutex_init(&mem->mm_lock);

	अगर (ops->init) अणु
		err = ops->init(mem);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण

	kref_init(&mem->kref);
	वापस mem;

err_मुक्त:
	kमुक्त(mem);
	वापस ERR_PTR(err);
पूर्ण

व्योम पूर्णांकel_memory_region_set_name(काष्ठा पूर्णांकel_memory_region *mem,
				  स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	vsnम_लिखो(mem->name, माप(mem->name), fmt, ap);
	बहु_पूर्ण(ap);
पूर्ण

अटल व्योम __पूर्णांकel_memory_region_destroy(काष्ठा kref *kref)
अणु
	काष्ठा पूर्णांकel_memory_region *mem =
		container_of(kref, typeof(*mem), kref);

	अगर (mem->ops->release)
		mem->ops->release(mem);

	mutex_destroy(&mem->mm_lock);
	mutex_destroy(&mem->objects.lock);
	kमुक्त(mem);
पूर्ण

काष्ठा पूर्णांकel_memory_region *
पूर्णांकel_memory_region_get(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	kref_get(&mem->kref);
	वापस mem;
पूर्ण

व्योम पूर्णांकel_memory_region_put(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	kref_put(&mem->kref, __पूर्णांकel_memory_region_destroy);
पूर्ण

/* Global memory region registration -- only slight layer inversions! */

पूर्णांक पूर्णांकel_memory_regions_hw_probe(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < ARRAY_SIZE(i915->mm.regions); i++) अणु
		काष्ठा पूर्णांकel_memory_region *mem = ERR_PTR(-ENODEV);
		u16 type, instance;

		अगर (!HAS_REGION(i915, BIT(i)))
			जारी;

		type = पूर्णांकel_region_map[i].class;
		instance = पूर्णांकel_region_map[i].instance;
		चयन (type) अणु
		हाल INTEL_MEMORY_SYSTEM:
			mem = i915_gem_shmem_setup(i915);
			अवरोध;
		हाल INTEL_MEMORY_STOLEN_SYSTEM:
			mem = i915_gem_stolen_setup(i915);
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अगर (IS_ERR(mem)) अणु
			err = PTR_ERR(mem);
			drm_err(&i915->drm,
				"Failed to setup region(%d) type=%d\n",
				err, type);
			जाओ out_cleanup;
		पूर्ण

		mem->id = i;
		mem->type = type;
		mem->instance = instance;

		i915->mm.regions[i] = mem;
	पूर्ण

	वापस 0;

out_cleanup:
	पूर्णांकel_memory_regions_driver_release(i915);
	वापस err;
पूर्ण

व्योम पूर्णांकel_memory_regions_driver_release(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(i915->mm.regions); i++) अणु
		काष्ठा पूर्णांकel_memory_region *region =
			fetch_and_zero(&i915->mm.regions[i]);

		अगर (region)
			पूर्णांकel_memory_region_put(region);
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/intel_memory_region.c"
#समावेश "selftests/mock_region.c"
#पूर्ण_अगर
