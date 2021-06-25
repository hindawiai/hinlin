<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017 Intel Corporation
 */

#समावेश <linux/prime_numbers.h>

#समावेश "i915_selftest.h"

#समावेश "gem/i915_gem_region.h"
#समावेश "gem/i915_gem_lmem.h"
#समावेश "gem/i915_gem_pm.h"

#समावेश "gt/intel_gt.h"

#समावेश "igt_gem_utils.h"
#समावेश "mock_context.h"

#समावेश "selftests/mock_drm.h"
#समावेश "selftests/mock_gem_device.h"
#समावेश "selftests/mock_region.h"
#समावेश "selftests/i915_random.h"

अटल स्थिर अचिन्हित पूर्णांक page_sizes[] = अणु
	I915_GTT_PAGE_SIZE_2M,
	I915_GTT_PAGE_SIZE_64K,
	I915_GTT_PAGE_SIZE_4K,
पूर्ण;

अटल अचिन्हित पूर्णांक get_largest_page_size(काष्ठा drm_i915_निजी *i915,
					  u64 rem)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(page_sizes); ++i) अणु
		अचिन्हित पूर्णांक page_size = page_sizes[i];

		अगर (HAS_PAGE_SIZES(i915, page_size) && rem >= page_size)
			वापस page_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम huge_pages_मुक्त_pages(काष्ठा sg_table *st)
अणु
	काष्ठा scatterlist *sg;

	क्रम (sg = st->sgl; sg; sg = __sg_next(sg)) अणु
		अगर (sg_page(sg))
			__मुक्त_pages(sg_page(sg), get_order(sg->length));
	पूर्ण

	sg_मुक्त_table(st);
	kमुक्त(st);
पूर्ण

अटल पूर्णांक get_huge_pages(काष्ठा drm_i915_gem_object *obj)
अणु
#घोषणा GFP (GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY)
	अचिन्हित पूर्णांक page_mask = obj->mm.page_mask;
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक sg_page_sizes;
	u64 rem;

	st = kदो_स्मृति(माप(*st), GFP);
	अगर (!st)
		वापस -ENOMEM;

	अगर (sg_alloc_table(st, obj->base.size >> PAGE_SHIFT, GFP)) अणु
		kमुक्त(st);
		वापस -ENOMEM;
	पूर्ण

	rem = obj->base.size;
	sg = st->sgl;
	st->nents = 0;
	sg_page_sizes = 0;

	/*
	 * Our goal here is simple, we want to greedily fill the object from
	 * largest to smallest page-size, जबतक ensuring that we use *every*
	 * page-size as per the given page-mask.
	 */
	करो अणु
		अचिन्हित पूर्णांक bit = ilog2(page_mask);
		अचिन्हित पूर्णांक page_size = BIT(bit);
		पूर्णांक order = get_order(page_size);

		करो अणु
			काष्ठा page *page;

			GEM_BUG_ON(order >= MAX_ORDER);
			page = alloc_pages(GFP | __GFP_ZERO, order);
			अगर (!page)
				जाओ err;

			sg_set_page(sg, page, page_size, 0);
			sg_page_sizes |= page_size;
			st->nents++;

			rem -= page_size;
			अगर (!rem) अणु
				sg_mark_end(sg);
				अवरोध;
			पूर्ण

			sg = __sg_next(sg);
		पूर्ण जबतक ((rem - ((page_size-1) & page_mask)) >= page_size);

		page_mask &= (page_size-1);
	पूर्ण जबतक (page_mask);

	अगर (i915_gem_gtt_prepare_pages(obj, st))
		जाओ err;

	GEM_BUG_ON(sg_page_sizes != obj->mm.page_mask);
	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	वापस 0;

err:
	sg_set_page(sg, शून्य, 0, 0);
	sg_mark_end(sg);
	huge_pages_मुक्त_pages(st);

	वापस -ENOMEM;
पूर्ण

अटल व्योम put_huge_pages(काष्ठा drm_i915_gem_object *obj,
			   काष्ठा sg_table *pages)
अणु
	i915_gem_gtt_finish_pages(obj, pages);
	huge_pages_मुक्त_pages(pages);

	obj->mm.dirty = false;
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops huge_page_ops = अणु
	.name = "huge-gem",
	.flags = I915_GEM_OBJECT_IS_SHRINKABLE,
	.get_pages = get_huge_pages,
	.put_pages = put_huge_pages,
पूर्ण;

अटल काष्ठा drm_i915_gem_object *
huge_pages_object(काष्ठा drm_i915_निजी *i915,
		  u64 size,
		  अचिन्हित पूर्णांक page_mask)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_gem_object *obj;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, BIT(__ffs(page_mask))));

	अगर (size >> PAGE_SHIFT > पूर्णांक_उच्च)
		वापस ERR_PTR(-E2BIG);

	अगर (overflows_type(size, obj->base.size))
		वापस ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	drm_gem_निजी_object_init(&i915->drm, &obj->base, size);
	i915_gem_object_init(obj, &huge_page_ops, &lock_class,
			     I915_BO_ALLOC_STRUCT_PAGE);

	i915_gem_object_set_अस्थिर(obj);

	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;
	obj->cache_level = I915_CACHE_NONE;

	obj->mm.page_mask = page_mask;

	वापस obj;
पूर्ण

अटल पूर्णांक fake_get_huge_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	स्थिर u64 max_len = roundकरोwn_घात_of_two(अच_पूर्णांक_उच्च);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक sg_page_sizes;
	u64 rem;

	st = kदो_स्मृति(माप(*st), GFP);
	अगर (!st)
		वापस -ENOMEM;

	अगर (sg_alloc_table(st, obj->base.size >> PAGE_SHIFT, GFP)) अणु
		kमुक्त(st);
		वापस -ENOMEM;
	पूर्ण

	/* Use optimal page sized chunks to fill in the sg table */
	rem = obj->base.size;
	sg = st->sgl;
	st->nents = 0;
	sg_page_sizes = 0;
	करो अणु
		अचिन्हित पूर्णांक page_size = get_largest_page_size(i915, rem);
		अचिन्हित पूर्णांक len = min(page_size * भाग_u64(rem, page_size),
				       max_len);

		GEM_BUG_ON(!page_size);

		sg->offset = 0;
		sg->length = len;
		sg_dma_len(sg) = len;
		sg_dma_address(sg) = page_size;

		sg_page_sizes |= len;

		st->nents++;

		rem -= len;
		अगर (!rem) अणु
			sg_mark_end(sg);
			अवरोध;
		पूर्ण

		sg = sg_next(sg);
	पूर्ण जबतक (1);

	i915_sg_trim(st);

	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	वापस 0;
पूर्ण

अटल पूर्णांक fake_get_huge_pages_single(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक page_size;

	st = kदो_स्मृति(माप(*st), GFP);
	अगर (!st)
		वापस -ENOMEM;

	अगर (sg_alloc_table(st, 1, GFP)) अणु
		kमुक्त(st);
		वापस -ENOMEM;
	पूर्ण

	sg = st->sgl;
	st->nents = 1;

	page_size = get_largest_page_size(i915, obj->base.size);
	GEM_BUG_ON(!page_size);

	sg->offset = 0;
	sg->length = obj->base.size;
	sg_dma_len(sg) = obj->base.size;
	sg_dma_address(sg) = page_size;

	__i915_gem_object_set_pages(obj, st, sg->length);

	वापस 0;
#अघोषित GFP
पूर्ण

अटल व्योम fake_मुक्त_huge_pages(काष्ठा drm_i915_gem_object *obj,
				 काष्ठा sg_table *pages)
अणु
	sg_मुक्त_table(pages);
	kमुक्त(pages);
पूर्ण

अटल व्योम fake_put_huge_pages(काष्ठा drm_i915_gem_object *obj,
				काष्ठा sg_table *pages)
अणु
	fake_मुक्त_huge_pages(obj, pages);
	obj->mm.dirty = false;
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops fake_ops = अणु
	.name = "fake-gem",
	.flags = I915_GEM_OBJECT_IS_SHRINKABLE,
	.get_pages = fake_get_huge_pages,
	.put_pages = fake_put_huge_pages,
पूर्ण;

अटल स्थिर काष्ठा drm_i915_gem_object_ops fake_ops_single = अणु
	.name = "fake-gem",
	.flags = I915_GEM_OBJECT_IS_SHRINKABLE,
	.get_pages = fake_get_huge_pages_single,
	.put_pages = fake_put_huge_pages,
पूर्ण;

अटल काष्ठा drm_i915_gem_object *
fake_huge_pages_object(काष्ठा drm_i915_निजी *i915, u64 size, bool single)
अणु
	अटल काष्ठा lock_class_key lock_class;
	काष्ठा drm_i915_gem_object *obj;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));

	अगर (size >> PAGE_SHIFT > अच_पूर्णांक_उच्च)
		वापस ERR_PTR(-E2BIG);

	अगर (overflows_type(size, obj->base.size))
		वापस ERR_PTR(-E2BIG);

	obj = i915_gem_object_alloc();
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	drm_gem_निजी_object_init(&i915->drm, &obj->base, size);

	अगर (single)
		i915_gem_object_init(obj, &fake_ops_single, &lock_class, 0);
	अन्यथा
		i915_gem_object_init(obj, &fake_ops, &lock_class, 0);

	i915_gem_object_set_अस्थिर(obj);

	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;
	obj->cache_level = I915_CACHE_NONE;

	वापस obj;
पूर्ण

अटल पूर्णांक igt_check_page_sizes(काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_i915_निजी *i915 = vma->vm->i915;
	अचिन्हित पूर्णांक supported = INTEL_INFO(i915)->page_sizes;
	काष्ठा drm_i915_gem_object *obj = vma->obj;
	पूर्णांक err;

	/* We have to रुको क्रम the async bind to complete beक्रमe our निश्चितs */
	err = i915_vma_sync(vma);
	अगर (err)
		वापस err;

	अगर (!HAS_PAGE_SIZES(i915, vma->page_sizes.sg)) अणु
		pr_err("unsupported page_sizes.sg=%u, supported=%u\n",
		       vma->page_sizes.sg & ~supported, supported);
		err = -EINVAL;
	पूर्ण

	अगर (!HAS_PAGE_SIZES(i915, vma->page_sizes.gtt)) अणु
		pr_err("unsupported page_sizes.gtt=%u, supported=%u\n",
		       vma->page_sizes.gtt & ~supported, supported);
		err = -EINVAL;
	पूर्ण

	अगर (vma->page_sizes.phys != obj->mm.page_sizes.phys) अणु
		pr_err("vma->page_sizes.phys(%u) != obj->mm.page_sizes.phys(%u)\n",
		       vma->page_sizes.phys, obj->mm.page_sizes.phys);
		err = -EINVAL;
	पूर्ण

	अगर (vma->page_sizes.sg != obj->mm.page_sizes.sg) अणु
		pr_err("vma->page_sizes.sg(%u) != obj->mm.page_sizes.sg(%u)\n",
		       vma->page_sizes.sg, obj->mm.page_sizes.sg);
		err = -EINVAL;
	पूर्ण

	/*
	 * The dma-api is like a box of chocolates when it comes to the
	 * alignment of dma addresses, however क्रम LMEM we have total control
	 * and so can guarantee alignment, likewise when we allocate our blocks
	 * they should appear in descending order, and अगर we know that we align
	 * to the largest page size क्रम the GTT address, we should be able to
	 * निश्चित that अगर we see 2M physical pages then we should also get 2M
	 * GTT pages. If we करोn't then something might be wrong in our
	 * स्थिरruction of the backing pages.
	 *
	 * Maपूर्णांकaining alignment is required to utilise huge pages in the ppGGT.
	 */
	अगर (i915_gem_object_is_lmem(obj) &&
	    IS_ALIGNED(vma->node.start, SZ_2M) &&
	    vma->page_sizes.sg & SZ_2M &&
	    vma->page_sizes.gtt < SZ_2M) अणु
		pr_err("gtt pages mismatch for LMEM, expected 2M GTT pages, sg(%u), gtt(%u)\n",
		       vma->page_sizes.sg, vma->page_sizes.gtt);
		err = -EINVAL;
	पूर्ण

	अगर (obj->mm.page_sizes.gtt) अणु
		pr_err("obj->page_sizes.gtt(%u) should never be set\n",
		       obj->mm.page_sizes.gtt);
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक igt_mock_exhaust_device_supported_pages(व्योम *arg)
अणु
	काष्ठा i915_ppgtt *ppgtt = arg;
	काष्ठा drm_i915_निजी *i915 = ppgtt->vm.i915;
	अचिन्हित पूर्णांक saved_mask = INTEL_INFO(i915)->page_sizes;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक i, j, single;
	पूर्णांक err;

	/*
	 * Sanity check creating objects with every valid page support
	 * combination क्रम our mock device.
	 */

	क्रम (i = 1; i < BIT(ARRAY_SIZE(page_sizes)); i++) अणु
		अचिन्हित पूर्णांक combination = SZ_4K; /* Required क्रम ppGTT */

		क्रम (j = 0; j < ARRAY_SIZE(page_sizes); j++) अणु
			अगर (i & BIT(j))
				combination |= page_sizes[j];
		पूर्ण

		mkग_लिखो_device_info(i915)->page_sizes = combination;

		क्रम (single = 0; single <= 1; ++single) अणु
			obj = fake_huge_pages_object(i915, combination, !!single);
			अगर (IS_ERR(obj)) अणु
				err = PTR_ERR(obj);
				जाओ out_device;
			पूर्ण

			अगर (obj->base.size != combination) अणु
				pr_err("obj->base.size=%zu, expected=%u\n",
				       obj->base.size, combination);
				err = -EINVAL;
				जाओ out_put;
			पूर्ण

			vma = i915_vma_instance(obj, &ppgtt->vm, शून्य);
			अगर (IS_ERR(vma)) अणु
				err = PTR_ERR(vma);
				जाओ out_put;
			पूर्ण

			err = i915_vma_pin(vma, 0, 0, PIN_USER);
			अगर (err)
				जाओ out_put;

			err = igt_check_page_sizes(vma);

			अगर (vma->page_sizes.sg != combination) अणु
				pr_err("page_sizes.sg=%u, expected=%u\n",
				       vma->page_sizes.sg, combination);
				err = -EINVAL;
			पूर्ण

			i915_vma_unpin(vma);
			i915_gem_object_put(obj);

			अगर (err)
				जाओ out_device;
		पूर्ण
	पूर्ण

	जाओ out_device;

out_put:
	i915_gem_object_put(obj);
out_device:
	mkग_लिखो_device_info(i915)->page_sizes = saved_mask;

	वापस err;
पूर्ण

अटल पूर्णांक igt_mock_memory_region_huge_pages(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक flags[] = अणु 0, I915_BO_ALLOC_CONTIGUOUS पूर्ण;
	काष्ठा i915_ppgtt *ppgtt = arg;
	काष्ठा drm_i915_निजी *i915 = ppgtt->vm.i915;
	अचिन्हित दीर्घ supported = INTEL_INFO(i915)->page_sizes;
	काष्ठा पूर्णांकel_memory_region *mem;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	पूर्णांक bit;
	पूर्णांक err = 0;

	mem = mock_region_create(i915, 0, SZ_2G, I915_GTT_PAGE_SIZE_4K, 0);
	अगर (IS_ERR(mem)) अणु
		pr_err("%s failed to create memory region\n", __func__);
		वापस PTR_ERR(mem);
	पूर्ण

	क्रम_each_set_bit(bit, &supported, ilog2(I915_GTT_MAX_PAGE_SIZE) + 1) अणु
		अचिन्हित पूर्णांक page_size = BIT(bit);
		resource_माप_प्रकार phys;
		पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(flags); ++i) अणु
			obj = i915_gem_object_create_region(mem, page_size,
							    flags[i]);
			अगर (IS_ERR(obj)) अणु
				err = PTR_ERR(obj);
				जाओ out_region;
			पूर्ण

			vma = i915_vma_instance(obj, &ppgtt->vm, शून्य);
			अगर (IS_ERR(vma)) अणु
				err = PTR_ERR(vma);
				जाओ out_put;
			पूर्ण

			err = i915_vma_pin(vma, 0, 0, PIN_USER);
			अगर (err)
				जाओ out_put;

			err = igt_check_page_sizes(vma);
			अगर (err)
				जाओ out_unpin;

			phys = i915_gem_object_get_dma_address(obj, 0);
			अगर (!IS_ALIGNED(phys, page_size)) अणु
				pr_err("%s addr misaligned(%pa) page_size=%u\n",
				       __func__, &phys, page_size);
				err = -EINVAL;
				जाओ out_unpin;
			पूर्ण

			अगर (vma->page_sizes.gtt != page_size) अणु
				pr_err("%s page_sizes.gtt=%u, expected=%u\n",
				       __func__, vma->page_sizes.gtt,
				       page_size);
				err = -EINVAL;
				जाओ out_unpin;
			पूर्ण

			i915_vma_unpin(vma);
			__i915_gem_object_put_pages(obj);
			i915_gem_object_put(obj);
		पूर्ण
	पूर्ण

	जाओ out_region;

out_unpin:
	i915_vma_unpin(vma);
out_put:
	i915_gem_object_put(obj);
out_region:
	पूर्णांकel_memory_region_put(mem);
	वापस err;
पूर्ण

अटल पूर्णांक igt_mock_ppgtt_misaligned_dma(व्योम *arg)
अणु
	काष्ठा i915_ppgtt *ppgtt = arg;
	काष्ठा drm_i915_निजी *i915 = ppgtt->vm.i915;
	अचिन्हित दीर्घ supported = INTEL_INFO(i915)->page_sizes;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक bit;
	पूर्णांक err;

	/*
	 * Sanity check dma misalignment क्रम huge pages -- the dma addresses we
	 * insert पूर्णांकo the paging काष्ठाures need to always respect the page
	 * size alignment.
	 */

	bit = ilog2(I915_GTT_PAGE_SIZE_64K);

	क्रम_each_set_bit_from(bit, &supported,
			      ilog2(I915_GTT_MAX_PAGE_SIZE) + 1) अणु
		IGT_TIMEOUT(end_समय);
		अचिन्हित पूर्णांक page_size = BIT(bit);
		अचिन्हित पूर्णांक flags = PIN_USER | PIN_OFFSET_FIXED;
		अचिन्हित पूर्णांक offset;
		अचिन्हित पूर्णांक size =
			round_up(page_size, I915_GTT_PAGE_SIZE_2M) << 1;
		काष्ठा i915_vma *vma;

		obj = fake_huge_pages_object(i915, size, true);
		अगर (IS_ERR(obj))
			वापस PTR_ERR(obj);

		अगर (obj->base.size != size) अणु
			pr_err("obj->base.size=%zu, expected=%u\n",
			       obj->base.size, size);
			err = -EINVAL;
			जाओ out_put;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err)
			जाओ out_put;

		/* Force the page size क्रम this object */
		obj->mm.page_sizes.sg = page_size;

		vma = i915_vma_instance(obj, &ppgtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			जाओ out_unpin;
		पूर्ण

		err = i915_vma_pin(vma, 0, 0, flags);
		अगर (err)
			जाओ out_unpin;


		err = igt_check_page_sizes(vma);

		अगर (vma->page_sizes.gtt != page_size) अणु
			pr_err("page_sizes.gtt=%u, expected %u\n",
			       vma->page_sizes.gtt, page_size);
			err = -EINVAL;
		पूर्ण

		i915_vma_unpin(vma);

		अगर (err)
			जाओ out_unpin;

		/*
		 * Try all the other valid offsets until the next
		 * boundary -- should always fall back to using 4K
		 * pages.
		 */
		क्रम (offset = 4096; offset < page_size; offset += 4096) अणु
			err = i915_vma_unbind(vma);
			अगर (err)
				जाओ out_unpin;

			err = i915_vma_pin(vma, 0, 0, flags | offset);
			अगर (err)
				जाओ out_unpin;

			err = igt_check_page_sizes(vma);

			अगर (vma->page_sizes.gtt != I915_GTT_PAGE_SIZE_4K) अणु
				pr_err("page_sizes.gtt=%u, expected %llu\n",
				       vma->page_sizes.gtt, I915_GTT_PAGE_SIZE_4K);
				err = -EINVAL;
			पूर्ण

			i915_vma_unpin(vma);

			अगर (err)
				जाओ out_unpin;

			अगर (igt_समयout(end_समय,
					"%s timed out at offset %x with page-size %x\n",
					__func__, offset, page_size))
				अवरोध;
		पूर्ण

		i915_gem_object_lock(obj, शून्य);
		i915_gem_object_unpin_pages(obj);
		__i915_gem_object_put_pages(obj);
		i915_gem_object_unlock(obj);
		i915_gem_object_put(obj);
	पूर्ण

	वापस 0;

out_unpin:
	i915_gem_object_lock(obj, शून्य);
	i915_gem_object_unpin_pages(obj);
	i915_gem_object_unlock(obj);
out_put:
	i915_gem_object_put(obj);

	वापस err;
पूर्ण

अटल व्योम बंद_object_list(काष्ठा list_head *objects,
			      काष्ठा i915_ppgtt *ppgtt)
अणु
	काष्ठा drm_i915_gem_object *obj, *on;

	list_क्रम_each_entry_safe(obj, on, objects, st_link) अणु
		list_del(&obj->st_link);
		i915_gem_object_lock(obj, शून्य);
		i915_gem_object_unpin_pages(obj);
		__i915_gem_object_put_pages(obj);
		i915_gem_object_unlock(obj);
		i915_gem_object_put(obj);
	पूर्ण
पूर्ण

अटल पूर्णांक igt_mock_ppgtt_huge_fill(व्योम *arg)
अणु
	काष्ठा i915_ppgtt *ppgtt = arg;
	काष्ठा drm_i915_निजी *i915 = ppgtt->vm.i915;
	अचिन्हित दीर्घ max_pages = ppgtt->vm.total >> PAGE_SHIFT;
	अचिन्हित दीर्घ page_num;
	bool single = false;
	LIST_HEAD(objects);
	IGT_TIMEOUT(end_समय);
	पूर्णांक err = -ENODEV;

	क्रम_each_prime_number_from(page_num, 1, max_pages) अणु
		काष्ठा drm_i915_gem_object *obj;
		u64 size = page_num << PAGE_SHIFT;
		काष्ठा i915_vma *vma;
		अचिन्हित पूर्णांक expected_gtt = 0;
		पूर्णांक i;

		obj = fake_huge_pages_object(i915, size, single);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			अवरोध;
		पूर्ण

		अगर (obj->base.size != size) अणु
			pr_err("obj->base.size=%zd, expected=%llu\n",
			       obj->base.size, size);
			i915_gem_object_put(obj);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err) अणु
			i915_gem_object_put(obj);
			अवरोध;
		पूर्ण

		list_add(&obj->st_link, &objects);

		vma = i915_vma_instance(obj, &ppgtt->vm, शून्य);
		अगर (IS_ERR(vma)) अणु
			err = PTR_ERR(vma);
			अवरोध;
		पूर्ण

		err = i915_vma_pin(vma, 0, 0, PIN_USER);
		अगर (err)
			अवरोध;

		err = igt_check_page_sizes(vma);
		अगर (err) अणु
			i915_vma_unpin(vma);
			अवरोध;
		पूर्ण

		/*
		 * Figure out the expected gtt page size knowing that we go from
		 * largest to smallest page size sg chunks, and that we align to
		 * the largest page size.
		 */
		क्रम (i = 0; i < ARRAY_SIZE(page_sizes); ++i) अणु
			अचिन्हित पूर्णांक page_size = page_sizes[i];

			अगर (HAS_PAGE_SIZES(i915, page_size) &&
			    size >= page_size) अणु
				expected_gtt |= page_size;
				size &= page_size-1;
			पूर्ण
		पूर्ण

		GEM_BUG_ON(!expected_gtt);
		GEM_BUG_ON(size);

		अगर (expected_gtt & I915_GTT_PAGE_SIZE_4K)
			expected_gtt &= ~I915_GTT_PAGE_SIZE_64K;

		i915_vma_unpin(vma);

		अगर (vma->page_sizes.sg & I915_GTT_PAGE_SIZE_64K) अणु
			अगर (!IS_ALIGNED(vma->node.start,
					I915_GTT_PAGE_SIZE_2M)) अणु
				pr_err("node.start(%llx) not aligned to 2M\n",
				       vma->node.start);
				err = -EINVAL;
				अवरोध;
			पूर्ण

			अगर (!IS_ALIGNED(vma->node.size,
					I915_GTT_PAGE_SIZE_2M)) अणु
				pr_err("node.size(%llx) not aligned to 2M\n",
				       vma->node.size);
				err = -EINVAL;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (vma->page_sizes.gtt != expected_gtt) अणु
			pr_err("gtt=%u, expected=%u, size=%zd, single=%s\n",
			       vma->page_sizes.gtt, expected_gtt,
			       obj->base.size, yesno(!!single));
			err = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (igt_समयout(end_समय,
				"%s timed out at size %zd\n",
				__func__, obj->base.size))
			अवरोध;

		single = !single;
	पूर्ण

	बंद_object_list(&objects, ppgtt);

	अगर (err == -ENOMEM || err == -ENOSPC)
		err = 0;

	वापस err;
पूर्ण

अटल पूर्णांक igt_mock_ppgtt_64K(व्योम *arg)
अणु
	काष्ठा i915_ppgtt *ppgtt = arg;
	काष्ठा drm_i915_निजी *i915 = ppgtt->vm.i915;
	काष्ठा drm_i915_gem_object *obj;
	स्थिर काष्ठा object_info अणु
		अचिन्हित पूर्णांक size;
		अचिन्हित पूर्णांक gtt;
		अचिन्हित पूर्णांक offset;
	पूर्ण objects[] = अणु
		/* Cases with क्रमced padding/alignment */
		अणु
			.size = SZ_64K,
			.gtt = I915_GTT_PAGE_SIZE_64K,
			.offset = 0,
		पूर्ण,
		अणु
			.size = SZ_64K + SZ_4K,
			.gtt = I915_GTT_PAGE_SIZE_4K,
			.offset = 0,
		पूर्ण,
		अणु
			.size = SZ_64K - SZ_4K,
			.gtt = I915_GTT_PAGE_SIZE_4K,
			.offset = 0,
		पूर्ण,
		अणु
			.size = SZ_2M,
			.gtt = I915_GTT_PAGE_SIZE_64K,
			.offset = 0,
		पूर्ण,
		अणु
			.size = SZ_2M - SZ_4K,
			.gtt = I915_GTT_PAGE_SIZE_4K,
			.offset = 0,
		पूर्ण,
		अणु
			.size = SZ_2M + SZ_4K,
			.gtt = I915_GTT_PAGE_SIZE_64K | I915_GTT_PAGE_SIZE_4K,
			.offset = 0,
		पूर्ण,
		अणु
			.size = SZ_2M + SZ_64K,
			.gtt = I915_GTT_PAGE_SIZE_64K,
			.offset = 0,
		पूर्ण,
		अणु
			.size = SZ_2M - SZ_64K,
			.gtt = I915_GTT_PAGE_SIZE_64K,
			.offset = 0,
		पूर्ण,
		/* Try without any क्रमced padding/alignment */
		अणु
			.size = SZ_64K,
			.offset = SZ_2M,
			.gtt = I915_GTT_PAGE_SIZE_4K,
		पूर्ण,
		अणु
			.size = SZ_128K,
			.offset = SZ_2M - SZ_64K,
			.gtt = I915_GTT_PAGE_SIZE_4K,
		पूर्ण,
	पूर्ण;
	काष्ठा i915_vma *vma;
	पूर्णांक i, single;
	पूर्णांक err;

	/*
	 * Sanity check some of the trickiness with 64K pages -- either we can
	 * safely mark the whole page-table(2M block) as 64K, or we have to
	 * always fallback to 4K.
	 */

	अगर (!HAS_PAGE_SIZES(i915, I915_GTT_PAGE_SIZE_64K))
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(objects); ++i) अणु
		अचिन्हित पूर्णांक size = objects[i].size;
		अचिन्हित पूर्णांक expected_gtt = objects[i].gtt;
		अचिन्हित पूर्णांक offset = objects[i].offset;
		अचिन्हित पूर्णांक flags = PIN_USER;

		क्रम (single = 0; single <= 1; single++) अणु
			obj = fake_huge_pages_object(i915, size, !!single);
			अगर (IS_ERR(obj))
				वापस PTR_ERR(obj);

			err = i915_gem_object_pin_pages_unlocked(obj);
			अगर (err)
				जाओ out_object_put;

			/*
			 * Disable 2M pages -- We only want to use 64K/4K pages
			 * क्रम this test.
			 */
			obj->mm.page_sizes.sg &= ~I915_GTT_PAGE_SIZE_2M;

			vma = i915_vma_instance(obj, &ppgtt->vm, शून्य);
			अगर (IS_ERR(vma)) अणु
				err = PTR_ERR(vma);
				जाओ out_object_unpin;
			पूर्ण

			अगर (offset)
				flags |= PIN_OFFSET_FIXED | offset;

			err = i915_vma_pin(vma, 0, 0, flags);
			अगर (err)
				जाओ out_object_unpin;

			err = igt_check_page_sizes(vma);
			अगर (err)
				जाओ out_vma_unpin;

			अगर (!offset && vma->page_sizes.sg & I915_GTT_PAGE_SIZE_64K) अणु
				अगर (!IS_ALIGNED(vma->node.start,
						I915_GTT_PAGE_SIZE_2M)) अणु
					pr_err("node.start(%llx) not aligned to 2M\n",
					       vma->node.start);
					err = -EINVAL;
					जाओ out_vma_unpin;
				पूर्ण

				अगर (!IS_ALIGNED(vma->node.size,
						I915_GTT_PAGE_SIZE_2M)) अणु
					pr_err("node.size(%llx) not aligned to 2M\n",
					       vma->node.size);
					err = -EINVAL;
					जाओ out_vma_unpin;
				पूर्ण
			पूर्ण

			अगर (vma->page_sizes.gtt != expected_gtt) अणु
				pr_err("gtt=%u, expected=%u, i=%d, single=%s\n",
				       vma->page_sizes.gtt, expected_gtt, i,
				       yesno(!!single));
				err = -EINVAL;
				जाओ out_vma_unpin;
			पूर्ण

			i915_vma_unpin(vma);
			i915_gem_object_lock(obj, शून्य);
			i915_gem_object_unpin_pages(obj);
			__i915_gem_object_put_pages(obj);
			i915_gem_object_unlock(obj);
			i915_gem_object_put(obj);
		पूर्ण
	पूर्ण

	वापस 0;

out_vma_unpin:
	i915_vma_unpin(vma);
out_object_unpin:
	i915_gem_object_lock(obj, शून्य);
	i915_gem_object_unpin_pages(obj);
	i915_gem_object_unlock(obj);
out_object_put:
	i915_gem_object_put(obj);

	वापस err;
पूर्ण

अटल पूर्णांक gpu_ग_लिखो(काष्ठा पूर्णांकel_context *ce,
		     काष्ठा i915_vma *vma,
		     u32 dw,
		     u32 val)
अणु
	पूर्णांक err;

	i915_gem_object_lock(vma->obj, शून्य);
	err = i915_gem_object_set_to_gtt_करोमुख्य(vma->obj, true);
	i915_gem_object_unlock(vma->obj);
	अगर (err)
		वापस err;

	वापस igt_gpu_fill_dw(ce, vma, dw * माप(u32),
			       vma->size >> PAGE_SHIFT, val);
पूर्ण

अटल पूर्णांक
__cpu_check_shmem(काष्ठा drm_i915_gem_object *obj, u32 dword, u32 val)
अणु
	अचिन्हित पूर्णांक needs_flush;
	अचिन्हित दीर्घ n;
	पूर्णांक err;

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_prepare_पढ़ो(obj, &needs_flush);
	अगर (err)
		जाओ err_unlock;

	क्रम (n = 0; n < obj->base.size >> PAGE_SHIFT; ++n) अणु
		u32 *ptr = kmap_atomic(i915_gem_object_get_page(obj, n));

		अगर (needs_flush & CLFLUSH_BEFORE)
			drm_clflush_virt_range(ptr, PAGE_SIZE);

		अगर (ptr[dword] != val) अणु
			pr_err("n=%lu ptr[%u]=%u, val=%u\n",
			       n, dword, ptr[dword], val);
			kunmap_atomic(ptr);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		kunmap_atomic(ptr);
	पूर्ण

	i915_gem_object_finish_access(obj);
err_unlock:
	i915_gem_object_unlock(obj);

	वापस err;
पूर्ण

अटल पूर्णांक __cpu_check_vmap(काष्ठा drm_i915_gem_object *obj, u32 dword, u32 val)
अणु
	अचिन्हित दीर्घ n = obj->base.size >> PAGE_SHIFT;
	u32 *ptr;
	पूर्णांक err;

	err = i915_gem_object_रुको(obj, 0, MAX_SCHEDULE_TIMEOUT);
	अगर (err)
		वापस err;

	ptr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WC);
	अगर (IS_ERR(ptr))
		वापस PTR_ERR(ptr);

	ptr += dword;
	जबतक (n--) अणु
		अगर (*ptr != val) अणु
			pr_err("base[%u]=%08x, val=%08x\n",
			       dword, *ptr, val);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		ptr += PAGE_SIZE / माप(*ptr);
	पूर्ण

	i915_gem_object_unpin_map(obj);
	वापस err;
पूर्ण

अटल पूर्णांक cpu_check(काष्ठा drm_i915_gem_object *obj, u32 dword, u32 val)
अणु
	अगर (i915_gem_object_has_काष्ठा_page(obj))
		वापस __cpu_check_shmem(obj, dword, val);
	अन्यथा
		वापस __cpu_check_vmap(obj, dword, val);
पूर्ण

अटल पूर्णांक __igt_ग_लिखो_huge(काष्ठा पूर्णांकel_context *ce,
			    काष्ठा drm_i915_gem_object *obj,
			    u64 size, u64 offset,
			    u32 dword, u32 val)
अणु
	अचिन्हित पूर्णांक flags = PIN_USER | PIN_OFFSET_FIXED;
	काष्ठा i915_vma *vma;
	पूर्णांक err;

	vma = i915_vma_instance(obj, ce->vm, शून्य);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	err = i915_vma_unbind(vma);
	अगर (err)
		वापस err;

	err = i915_vma_pin(vma, size, 0, flags | offset);
	अगर (err) अणु
		/*
		 * The ggtt may have some pages reserved so
		 * refrain from erroring out.
		 */
		अगर (err == -ENOSPC && i915_is_ggtt(ce->vm))
			err = 0;

		वापस err;
	पूर्ण

	err = igt_check_page_sizes(vma);
	अगर (err)
		जाओ out_vma_unpin;

	err = gpu_ग_लिखो(ce, vma, dword, val);
	अगर (err) अणु
		pr_err("gpu-write failed at offset=%llx\n", offset);
		जाओ out_vma_unpin;
	पूर्ण

	err = cpu_check(obj, dword, val);
	अगर (err) अणु
		pr_err("cpu-check failed at offset=%llx\n", offset);
		जाओ out_vma_unpin;
	पूर्ण

out_vma_unpin:
	i915_vma_unpin(vma);
	वापस err;
पूर्ण

अटल पूर्णांक igt_ग_लिखो_huge(काष्ठा i915_gem_context *ctx,
			  काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा i915_gem_engines *engines;
	काष्ठा i915_gem_engines_iter it;
	काष्ठा पूर्णांकel_context *ce;
	I915_RND_STATE(prng);
	IGT_TIMEOUT(end_समय);
	अचिन्हित पूर्णांक max_page_size;
	अचिन्हित पूर्णांक count;
	u64 max;
	u64 num;
	u64 size;
	पूर्णांक *order;
	पूर्णांक i, n;
	पूर्णांक err = 0;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));

	size = obj->base.size;
	अगर (obj->mm.page_sizes.sg & I915_GTT_PAGE_SIZE_64K)
		size = round_up(size, I915_GTT_PAGE_SIZE_2M);

	n = 0;
	count = 0;
	max = U64_MAX;
	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it) अणु
		count++;
		अगर (!पूर्णांकel_engine_can_store_dword(ce->engine))
			जारी;

		max = min(max, ce->vm->total);
		n++;
	पूर्ण
	i915_gem_context_unlock_engines(ctx);
	अगर (!n)
		वापस 0;

	/*
	 * To keep things पूर्णांकeresting when alternating between engines in our
	 * अक्रमomized order, lets also make feeding to the same engine a few
	 * बार in succession a possibility by enlarging the permutation array.
	 */
	order = i915_अक्रमom_order(count * count, &prng);
	अगर (!order)
		वापस -ENOMEM;

	max_page_size = roundकरोwn_घात_of_two(obj->mm.page_sizes.sg);
	max = भाग_u64(max - size, max_page_size);

	/*
	 * Try various offsets in an ascending/descending fashion until we
	 * समयout -- we want to aव्योम issues hidden by effectively always using
	 * offset = 0.
	 */
	i = 0;
	engines = i915_gem_context_lock_engines(ctx);
	क्रम_each_prime_number_from(num, 0, max) अणु
		u64 offset_low = num * max_page_size;
		u64 offset_high = (max - num) * max_page_size;
		u32 dword = offset_in_page(num) / 4;
		काष्ठा पूर्णांकel_context *ce;

		ce = engines->engines[order[i] % engines->num_engines];
		i = (i + 1) % (count * count);
		अगर (!ce || !पूर्णांकel_engine_can_store_dword(ce->engine))
			जारी;

		/*
		 * In order to utilize 64K pages we need to both pad the vma
		 * size and ensure the vma offset is at the start of the pt
		 * boundary, however to improve coverage we opt क्रम testing both
		 * aligned and unaligned offsets.
		 */
		अगर (obj->mm.page_sizes.sg & I915_GTT_PAGE_SIZE_64K)
			offset_low = round_करोwn(offset_low,
						I915_GTT_PAGE_SIZE_2M);

		err = __igt_ग_लिखो_huge(ce, obj, size, offset_low,
				       dword, num + 1);
		अगर (err)
			अवरोध;

		err = __igt_ग_लिखो_huge(ce, obj, size, offset_high,
				       dword, num + 1);
		अगर (err)
			अवरोध;

		अगर (igt_समयout(end_समय,
				"%s timed out on %s, offset_low=%llx offset_high=%llx, max_page_size=%x\n",
				__func__, ce->engine->name, offset_low, offset_high,
				max_page_size))
			अवरोध;
	पूर्ण
	i915_gem_context_unlock_engines(ctx);

	kमुक्त(order);

	वापस err;
पूर्ण

प्रकार काष्ठा drm_i915_gem_object *
(*igt_create_fn)(काष्ठा drm_i915_निजी *i915, u32 size, u32 flags);

अटल अंतरभूत bool igt_can_allocate_thp(काष्ठा drm_i915_निजी *i915)
अणु
	वापस i915->mm.gemfs && has_transparent_hugepage();
पूर्ण

अटल काष्ठा drm_i915_gem_object *
igt_create_shmem(काष्ठा drm_i915_निजी *i915, u32 size, u32 flags)
अणु
	अगर (!igt_can_allocate_thp(i915)) अणु
		pr_info("%s missing THP support, skipping\n", __func__);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	वापस i915_gem_object_create_shmem(i915, size);
पूर्ण

अटल काष्ठा drm_i915_gem_object *
igt_create_पूर्णांकernal(काष्ठा drm_i915_निजी *i915, u32 size, u32 flags)
अणु
	वापस i915_gem_object_create_पूर्णांकernal(i915, size);
पूर्ण

अटल काष्ठा drm_i915_gem_object *
igt_create_प्रणाली(काष्ठा drm_i915_निजी *i915, u32 size, u32 flags)
अणु
	वापस huge_pages_object(i915, size, size);
पूर्ण

अटल काष्ठा drm_i915_gem_object *
igt_create_local(काष्ठा drm_i915_निजी *i915, u32 size, u32 flags)
अणु
	वापस i915_gem_object_create_lmem(i915, size, flags);
पूर्ण

अटल u32 igt_अक्रमom_size(काष्ठा rnd_state *prng,
			   u32 min_page_size,
			   u32 max_page_size)
अणु
	u64 mask;
	u32 size;

	GEM_BUG_ON(!is_घातer_of_2(min_page_size));
	GEM_BUG_ON(!is_घातer_of_2(max_page_size));
	GEM_BUG_ON(min_page_size < PAGE_SIZE);
	GEM_BUG_ON(min_page_size > max_page_size);

	mask = ((max_page_size << 1ULL) - 1) & PAGE_MASK;
	size = pअक्रमom_u32_state(prng) & mask;
	अगर (size < min_page_size)
		size |= min_page_size;

	वापस size;
पूर्ण

अटल पूर्णांक igt_ppgtt_smoke_huge(व्योम *arg)
अणु
	काष्ठा i915_gem_context *ctx = arg;
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा drm_i915_gem_object *obj;
	I915_RND_STATE(prng);
	काष्ठा अणु
		igt_create_fn fn;
		u32 min;
		u32 max;
	पूर्ण backends[] = अणु
		अणु igt_create_पूर्णांकernal, SZ_64K, SZ_2M,  पूर्ण,
		अणु igt_create_shmem,    SZ_64K, SZ_32M, पूर्ण,
		अणु igt_create_local,    SZ_64K, SZ_1G,  पूर्ण,
	पूर्ण;
	पूर्णांक err;
	पूर्णांक i;

	/*
	 * Sanity check that the HW uses huge pages correctly through our
	 * various backends -- ensure that our ग_लिखोs land in the right place.
	 */

	क्रम (i = 0; i < ARRAY_SIZE(backends); ++i) अणु
		u32 min = backends[i].min;
		u32 max = backends[i].max;
		u32 size = max;
try_again:
		size = igt_अक्रमom_size(&prng, min, roundकरोwn_घात_of_two(size));

		obj = backends[i].fn(i915, size, 0);
		अगर (IS_ERR(obj)) अणु
			err = PTR_ERR(obj);
			अगर (err == -E2BIG) अणु
				size >>= 1;
				जाओ try_again;
			पूर्ण अन्यथा अगर (err == -ENODEV) अणु
				err = 0;
				जारी;
			पूर्ण

			वापस err;
		पूर्ण

		err = i915_gem_object_pin_pages_unlocked(obj);
		अगर (err) अणु
			अगर (err == -ENXIO || err == -E2BIG) अणु
				i915_gem_object_put(obj);
				size >>= 1;
				जाओ try_again;
			पूर्ण
			जाओ out_put;
		पूर्ण

		अगर (obj->mm.page_sizes.phys < min) अणु
			pr_info("%s unable to allocate huge-page(s) with size=%u, i=%d\n",
				__func__, size, i);
			err = -ENOMEM;
			जाओ out_unpin;
		पूर्ण

		err = igt_ग_लिखो_huge(ctx, obj);
		अगर (err) अणु
			pr_err("%s write-huge failed with size=%u, i=%d\n",
			       __func__, size, i);
		पूर्ण
out_unpin:
		i915_gem_object_lock(obj, शून्य);
		i915_gem_object_unpin_pages(obj);
		__i915_gem_object_put_pages(obj);
		i915_gem_object_unlock(obj);
out_put:
		i915_gem_object_put(obj);

		अगर (err == -ENOMEM || err == -ENXIO)
			err = 0;

		अगर (err)
			अवरोध;

		cond_resched();
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक igt_ppgtt_sanity_check(व्योम *arg)
अणु
	काष्ठा i915_gem_context *ctx = arg;
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	अचिन्हित पूर्णांक supported = INTEL_INFO(i915)->page_sizes;
	काष्ठा अणु
		igt_create_fn fn;
		अचिन्हित पूर्णांक flags;
	पूर्ण backends[] = अणु
		अणु igt_create_प्रणाली, 0,                        पूर्ण,
		अणु igt_create_local,  0,                        पूर्ण,
		अणु igt_create_local,  I915_BO_ALLOC_CONTIGUOUS, पूर्ण,
	पूर्ण;
	काष्ठा अणु
		u32 size;
		u32 pages;
	पूर्ण combos[] = अणु
		अणु SZ_64K,		SZ_64K		पूर्ण,
		अणु SZ_2M,		SZ_2M		पूर्ण,
		अणु SZ_2M,		SZ_64K		पूर्ण,
		अणु SZ_2M - SZ_64K,	SZ_64K		पूर्ण,
		अणु SZ_2M - SZ_4K,	SZ_64K | SZ_4K	पूर्ण,
		अणु SZ_2M + SZ_4K,	SZ_64K | SZ_4K	पूर्ण,
		अणु SZ_2M + SZ_4K,	SZ_2M  | SZ_4K	पूर्ण,
		अणु SZ_2M + SZ_64K,	SZ_2M  | SZ_64K पूर्ण,
	पूर्ण;
	पूर्णांक i, j;
	पूर्णांक err;

	अगर (supported == I915_GTT_PAGE_SIZE_4K)
		वापस 0;

	/*
	 * Sanity check that the HW behaves with a limited set of combinations.
	 * We alपढ़ोy have a bunch of अक्रमomised testing, which should give us
	 * a decent amount of variation between runs, however we should keep
	 * this to limit the chances of पूर्णांकroducing a temporary regression, by
	 * testing the most obvious हालs that might make something blow up.
	 */

	क्रम (i = 0; i < ARRAY_SIZE(backends); ++i) अणु
		क्रम (j = 0; j < ARRAY_SIZE(combos); ++j) अणु
			काष्ठा drm_i915_gem_object *obj;
			u32 size = combos[j].size;
			u32 pages = combos[j].pages;

			obj = backends[i].fn(i915, size, backends[i].flags);
			अगर (IS_ERR(obj)) अणु
				err = PTR_ERR(obj);
				अगर (err == -ENODEV) अणु
					pr_info("Device lacks local memory, skipping\n");
					err = 0;
					अवरोध;
				पूर्ण

				वापस err;
			पूर्ण

			err = i915_gem_object_pin_pages_unlocked(obj);
			अगर (err) अणु
				i915_gem_object_put(obj);
				जाओ out;
			पूर्ण

			GEM_BUG_ON(pages > obj->base.size);
			pages = pages & supported;

			अगर (pages)
				obj->mm.page_sizes.sg = pages;

			err = igt_ग_लिखो_huge(ctx, obj);

			i915_gem_object_lock(obj, शून्य);
			i915_gem_object_unpin_pages(obj);
			__i915_gem_object_put_pages(obj);
			i915_gem_object_unlock(obj);
			i915_gem_object_put(obj);

			अगर (err) अणु
				pr_err("%s write-huge failed with size=%u pages=%u i=%d, j=%d\n",
				       __func__, size, pages, i, j);
				जाओ out;
			पूर्ण
		पूर्ण

		cond_resched();
	पूर्ण

out:
	अगर (err == -ENOMEM)
		err = 0;

	वापस err;
पूर्ण

अटल पूर्णांक igt_पंचांगpfs_fallback(व्योम *arg)
अणु
	काष्ठा i915_gem_context *ctx = arg;
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा vfsmount *gemfs = i915->mm.gemfs;
	काष्ठा i915_address_space *vm = i915_gem_context_get_vm_rcu(ctx);
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 *vaddr;
	पूर्णांक err = 0;

	/*
	 * Make sure that we करोn't burst पूर्णांकo a ball of flames upon falling back
	 * to पंचांगpfs, which we rely on अगर on the off-chance we encouter a failure
	 * when setting up gemfs.
	 */

	i915->mm.gemfs = शून्य;

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ out_restore;
	पूर्ण

	vaddr = i915_gem_object_pin_map_unlocked(obj, I915_MAP_WB);
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ out_put;
	पूर्ण
	*vaddr = 0xdeadbeaf;

	__i915_gem_object_flush_map(obj, 0, 64);
	i915_gem_object_unpin_map(obj);

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ out_put;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, PIN_USER);
	अगर (err)
		जाओ out_put;

	err = igt_check_page_sizes(vma);

	i915_vma_unpin(vma);
out_put:
	i915_gem_object_put(obj);
out_restore:
	i915->mm.gemfs = gemfs;

	i915_vm_put(vm);
	वापस err;
पूर्ण

अटल पूर्णांक igt_shrink_thp(व्योम *arg)
अणु
	काष्ठा i915_gem_context *ctx = arg;
	काष्ठा drm_i915_निजी *i915 = ctx->i915;
	काष्ठा i915_address_space *vm = i915_gem_context_get_vm_rcu(ctx);
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_gem_engines_iter it;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_vma *vma;
	अचिन्हित पूर्णांक flags = PIN_USER;
	अचिन्हित पूर्णांक n;
	पूर्णांक err = 0;

	/*
	 * Sanity check shrinking huge-paged object -- make sure nothing blows
	 * up.
	 */

	अगर (!igt_can_allocate_thp(i915)) अणु
		pr_info("missing THP support, skipping\n");
		जाओ out_vm;
	पूर्ण

	obj = i915_gem_object_create_shmem(i915, SZ_2M);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		जाओ out_vm;
	पूर्ण

	vma = i915_vma_instance(obj, vm, शून्य);
	अगर (IS_ERR(vma)) अणु
		err = PTR_ERR(vma);
		जाओ out_put;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, flags);
	अगर (err)
		जाओ out_put;

	अगर (obj->mm.page_sizes.phys < I915_GTT_PAGE_SIZE_2M) अणु
		pr_info("failed to allocate THP, finishing test early\n");
		जाओ out_unpin;
	पूर्ण

	err = igt_check_page_sizes(vma);
	अगर (err)
		जाओ out_unpin;

	n = 0;

	क्रम_each_gem_engine(ce, i915_gem_context_lock_engines(ctx), it) अणु
		अगर (!पूर्णांकel_engine_can_store_dword(ce->engine))
			जारी;

		err = gpu_ग_लिखो(ce, vma, n++, 0xdeadbeaf);
		अगर (err)
			अवरोध;
	पूर्ण
	i915_gem_context_unlock_engines(ctx);
	i915_vma_unpin(vma);
	अगर (err)
		जाओ out_put;

	/*
	 * Now that the pages are *unpinned* shrink-all should invoke
	 * shmem to truncate our pages.
	 */
	i915_gem_shrink_all(i915);
	अगर (i915_gem_object_has_pages(obj)) अणु
		pr_err("shrink-all didn't truncate the pages\n");
		err = -EINVAL;
		जाओ out_put;
	पूर्ण

	अगर (obj->mm.page_sizes.sg || obj->mm.page_sizes.phys) अणु
		pr_err("residual page-size bits left\n");
		err = -EINVAL;
		जाओ out_put;
	पूर्ण

	err = i915_vma_pin(vma, 0, 0, flags);
	अगर (err)
		जाओ out_put;

	जबतक (n--) अणु
		err = cpu_check(obj, n, 0xdeadbeaf);
		अगर (err)
			अवरोध;
	पूर्ण

out_unpin:
	i915_vma_unpin(vma);
out_put:
	i915_gem_object_put(obj);
out_vm:
	i915_vm_put(vm);

	वापस err;
पूर्ण

पूर्णांक i915_gem_huge_page_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_mock_exhaust_device_supported_pages),
		SUBTEST(igt_mock_memory_region_huge_pages),
		SUBTEST(igt_mock_ppgtt_misaligned_dma),
		SUBTEST(igt_mock_ppgtt_huge_fill),
		SUBTEST(igt_mock_ppgtt_64K),
	पूर्ण;
	काष्ठा drm_i915_निजी *dev_priv;
	काष्ठा i915_ppgtt *ppgtt;
	पूर्णांक err;

	dev_priv = mock_gem_device();
	अगर (!dev_priv)
		वापस -ENOMEM;

	/* Pretend to be a device which supports the 48b PPGTT */
	mkग_लिखो_device_info(dev_priv)->ppgtt_type = INTEL_PPGTT_FULL;
	mkग_लिखो_device_info(dev_priv)->ppgtt_size = 48;

	ppgtt = i915_ppgtt_create(&dev_priv->gt);
	अगर (IS_ERR(ppgtt)) अणु
		err = PTR_ERR(ppgtt);
		जाओ out_unlock;
	पूर्ण

	अगर (!i915_vm_is_4lvl(&ppgtt->vm)) अणु
		pr_err("failed to create 48b PPGTT\n");
		err = -EINVAL;
		जाओ out_put;
	पूर्ण

	/* If we were ever hit this then it's समय to mock the 64K scratch */
	अगर (!i915_vm_has_scratch_64K(&ppgtt->vm)) अणु
		pr_err("PPGTT missing 64K scratch page\n");
		err = -EINVAL;
		जाओ out_put;
	पूर्ण

	err = i915_subtests(tests, ppgtt);

out_put:
	i915_vm_put(&ppgtt->vm);
out_unlock:
	mock_destroy_device(dev_priv);
	वापस err;
पूर्ण

पूर्णांक i915_gem_huge_page_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_shrink_thp),
		SUBTEST(igt_पंचांगpfs_fallback),
		SUBTEST(igt_ppgtt_smoke_huge),
		SUBTEST(igt_ppgtt_sanity_check),
	पूर्ण;
	काष्ठा i915_gem_context *ctx;
	काष्ठा i915_address_space *vm;
	काष्ठा file *file;
	पूर्णांक err;

	अगर (!HAS_PPGTT(i915)) अणु
		pr_info("PPGTT not supported, skipping live-selftests\n");
		वापस 0;
	पूर्ण

	अगर (पूर्णांकel_gt_is_wedged(&i915->gt))
		वापस 0;

	file = mock_file(i915);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ctx = live_context(i915, file);
	अगर (IS_ERR(ctx)) अणु
		err = PTR_ERR(ctx);
		जाओ out_file;
	पूर्ण

	mutex_lock(&ctx->mutex);
	vm = i915_gem_context_vm(ctx);
	अगर (vm)
		WRITE_ONCE(vm->scrub_64K, true);
	mutex_unlock(&ctx->mutex);

	err = i915_subtests(tests, ctx);

out_file:
	fput(file);
	वापस err;
पूर्ण
