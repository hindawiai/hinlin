<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "i915_selftest.h"

#समावेश "huge_gem_object.h"
#समावेश "selftests/igt_flush_test.h"
#समावेश "selftests/mock_gem_device.h"

अटल पूर्णांक igt_gem_object(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err;

	/* Basic test to ensure we can create an object */

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		pr_err("i915_gem_object_create failed, err=%d\n", err);
		जाओ out;
	पूर्ण

	err = 0;
	i915_gem_object_put(obj);
out:
	वापस err;
पूर्ण

अटल पूर्णांक igt_gem_huge(व्योम *arg)
अणु
	स्थिर अचिन्हित पूर्णांक nreal = 509; /* just to be awkward */
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित पूर्णांक n;
	पूर्णांक err;

	/* Basic sanitycheck of our huge fake object allocation */

	obj = huge_gem_object(i915,
			      nreal * PAGE_SIZE,
			      i915->ggtt.vm.total + PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस PTR_ERR(obj);

	err = i915_gem_object_pin_pages_unlocked(obj);
	अगर (err) अणु
		pr_err("Failed to allocate %u pages (%lu total), err=%d\n",
		       nreal, obj->base.size / PAGE_SIZE, err);
		जाओ out;
	पूर्ण

	क्रम (n = 0; n < obj->base.size / PAGE_SIZE; n++) अणु
		अगर (i915_gem_object_get_page(obj, n) !=
		    i915_gem_object_get_page(obj, n % nreal)) अणु
			pr_err("Page lookup mismatch at index %u [%u]\n",
			       n, n % nreal);
			err = -EINVAL;
			जाओ out_unpin;
		पूर्ण
	पूर्ण

out_unpin:
	i915_gem_object_unpin_pages(obj);
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

पूर्णांक i915_gem_object_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_gem_object),
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

पूर्णांक i915_gem_object_live_selftests(काष्ठा drm_i915_निजी *i915)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(igt_gem_huge),
	पूर्ण;

	वापस i915_subtests(tests, i915);
पूर्ण
