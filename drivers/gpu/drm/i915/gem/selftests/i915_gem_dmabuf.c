<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "i915_selftest.h"

#समावेश "mock_dmabuf.h"
#समावेश "selftests/mock_gem_device.h"

अटल पूर्णांक igt_dmabuf_export(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा dma_buf *dmabuf;

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	dmabuf = i915_gem_prime_export(&obj->base, 0);
	i915_gem_object_put(obj);
	अगर (IS_ERR(dmabuf)) अणु
		pr_err("i915_gem_prime_export failed with err=%d\n",
		       (पूर्णांक)PTR_ERR(dmabuf));
		वापस PTR_ERR(dmabuf);
	पूर्ण

	dma_buf_put(dmabuf);
	वापस 0;
पूर्ण

अटल पूर्णांक igt_dmabuf_import_self(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा drm_gem_object *import;
	काष्ठा dma_buf *dmabuf;
	पूर्णांक err;

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	dmabuf = i915_gem_prime_export(&obj->base, 0);
	अगर (IS_ERR(dmabuf)) अणु
		pr_err("i915_gem_prime_export failed with err=%d\n",
		       (पूर्णांक)PTR_ERR(dmabuf));
		err = PTR_ERR(dmabuf);
		जाओ out;
	पूर्ण

	import = i915_gem_prime_import(&i915->drm, dmabuf);
	अगर (IS_ERR(import)) अणु
		pr_err("i915_gem_prime_import failed with err=%d\n",
		       (पूर्णांक)PTR_ERR(import));
		err = PTR_ERR(import);
		जाओ out_dmabuf;
	पूर्ण

	अगर (import != &obj->base) अणु
		pr_err("i915_gem_prime_import created a new object!\n");
		err = -EINVAL;
		जाओ out_import;
	पूर्ण

	err = 0;
out_import:
	i915_gem_object_put(to_पूर्णांकel_bo(import));
out_dmabuf:
	dma_buf_put(dmabuf);
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

अटल पूर्णांक igt_dmabuf_import(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा dma_buf *dmabuf;
	व्योम *obj_map, *dma_map;
	काष्ठा dma_buf_map map;
	u32 pattern[] = अणु 0, 0xaa, 0xcc, 0x55, 0xff पूर्ण;
	पूर्णांक err, i;

	dmabuf = mock_dmabuf(1);
	अगर (IS_ERR(dmabuf))
		वापस PTR_ERR(dmabuf);

	obj = to_पूर्णांकel_bo(i915_gem_prime_import(&i915->drm, dmabuf));
	अगर (IS_ERR(obj)) अणु
		pr_err("i915_gem_prime_import failed with err=%d\n",
		       (पूर्णांक)PTR_ERR(obj));
		err = PTR_ERR(obj);
		जाओ out_dmabuf;
	पूर्ण

	अगर (obj->base.dev != &i915->drm) अणु
		pr_err("i915_gem_prime_import created a non-i915 object!\n");
		err = -EINVAL;
		जाओ out_obj;
	पूर्ण

	अगर (obj->base.size != PAGE_SIZE) अणु
		pr_err("i915_gem_prime_import is wrong size found %lld, expected %ld\n",
		       (दीर्घ दीर्घ)obj->base.size, PAGE_SIZE);
		err = -EINVAL;
		जाओ out_obj;
	पूर्ण

	err = dma_buf_vmap(dmabuf, &map);
	dma_map = err ? शून्य : map.vaddr;
	अगर (!dma_map) अणु
		pr_err("dma_buf_vmap failed\n");
		err = -ENOMEM;
		जाओ out_obj;
	पूर्ण

	अगर (0) अणु /* Can not yet map dmabuf */
		obj_map = i915_gem_object_pin_map(obj, I915_MAP_WB);
		अगर (IS_ERR(obj_map)) अणु
			err = PTR_ERR(obj_map);
			pr_err("i915_gem_object_pin_map failed with err=%d\n", err);
			जाओ out_dma_map;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(pattern); i++) अणु
			स_रखो(dma_map, pattern[i], PAGE_SIZE);
			अगर (स_प्रथम_inv(obj_map, pattern[i], PAGE_SIZE)) अणु
				err = -EINVAL;
				pr_err("imported vmap not all set to %x!\n", pattern[i]);
				i915_gem_object_unpin_map(obj);
				जाओ out_dma_map;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(pattern); i++) अणु
			स_रखो(obj_map, pattern[i], PAGE_SIZE);
			अगर (स_प्रथम_inv(dma_map, pattern[i], PAGE_SIZE)) अणु
				err = -EINVAL;
				pr_err("exported vmap not all set to %x!\n", pattern[i]);
				i915_gem_object_unpin_map(obj);
				जाओ out_dma_map;
			पूर्ण
		पूर्ण

		i915_gem_object_unpin_map(obj);
	पूर्ण

	err = 0;
out_dma_map:
	dma_buf_vunmap(dmabuf, &map);
out_obj:
	i915_gem_object_put(obj);
out_dmabuf:
	dma_buf_put(dmabuf);
	वापस err;
पूर्ण

अटल पूर्णांक igt_dmabuf_import_ownership(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा dma_buf *dmabuf;
	काष्ठा dma_buf_map map;
	व्योम *ptr;
	पूर्णांक err;

	dmabuf = mock_dmabuf(1);
	अगर (IS_ERR(dmabuf))
		वापस PTR_ERR(dmabuf);

	err = dma_buf_vmap(dmabuf, &map);
	ptr = err ? शून्य : map.vaddr;
	अगर (!ptr) अणु
		pr_err("dma_buf_vmap failed\n");
		err = -ENOMEM;
		जाओ err_dmabuf;
	पूर्ण

	स_रखो(ptr, 0xc5, PAGE_SIZE);
	dma_buf_vunmap(dmabuf, &map);

	obj = to_पूर्णांकel_bo(i915_gem_prime_import(&i915->drm, dmabuf));
	अगर (IS_ERR(obj)) अणु
		pr_err("i915_gem_prime_import failed with err=%d\n",
		       (पूर्णांक)PTR_ERR(obj));
		err = PTR_ERR(obj);
		जाओ err_dmabuf;
	पूर्ण

	dma_buf_put(dmabuf);

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err) अणु
		pr_err("i915_gem_object_pin_pages failed with err=%d\n", err);
		जाओ out_obj;
	पूर्ण

	err = 0;
	i915_gem_object_unpin_pages(obj);
out_obj:
	i915_gem_object_put(obj);
	वापस err;

err_dmabuf:
	dma_buf_put(dmabuf);
	वापस err;
पूर्ण

अटल पूर्णांक igt_dmabuf_export_vmap(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा dma_buf *dmabuf;
	काष्ठा dma_buf_map map;
	व्योम *ptr;
	पूर्णांक err;

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	dmabuf = i915_gem_prime_export(&obj->base, 0);
	अगर (IS_ERR(dmabuf)) अणु
		pr_err("i915_gem_prime_export failed with err=%d\n",
		       (पूर्णांक)PTR_ERR(dmabuf));
		err = PTR_ERR(dmabuf);
		जाओ err_obj;
	पूर्ण
	i915_gem_object_put(obj);

	err = dma_buf_vmap(dmabuf, &map);
	ptr = err ? शून्य : map.vaddr;
	अगर (!ptr) अणु
		pr_err("dma_buf_vmap failed\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (स_प्रथम_inv(ptr, 0, dmabuf->size)) अणु
		pr_err("Exported object not initialiased to zero!\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	स_रखो(ptr, 0xc5, dmabuf->size);

	err = 0;
	dma_buf_vunmap(dmabuf, &map);
out:
	dma_buf_put(dmabuf);
	वापस err;

err_obj:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

पूर्णांक i915_gem_dmabuf_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_dmabuf_export),
		SUBTEST(igt_dmabuf_import_self),
		SUBTEST(igt_dmabuf_import),
		SUBTEST(igt_dmabuf_import_ownership),
		SUBTEST(igt_dmabuf_export_vmap),
	पूर्ण;
	काष्ठा drm_i915_निजी *i915;
	पूर्णांक err;

	i915 = mock_gem_device();
	अगर (!i915)
		वापस -ENOMEM;

	err = i915_subtests(tests, i915);

	mock_destroy_device(i915);
	वापस err;
पूर्ण

पूर्णांक i915_gem_dmabuf_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_dmabuf_export),
	पूर्ण;

	वापस i915_subtests(tests, i915);
पूर्ण
