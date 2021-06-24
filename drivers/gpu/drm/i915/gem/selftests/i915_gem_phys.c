<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2016 Intel Corporation
 */

#समावेश "i915_selftest.h"

#समावेश "selftests/mock_gem_device.h"

अटल पूर्णांक mock_phys_object(व्योम *arg)
अणु
	काष्ठा drm_i915_निजी *i915 = arg;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err;

	/* Create an object and bind it to a contiguous set of physical pages,
	 * i.e. exercise the i915_gem_object_phys API.
	 */

	obj = i915_gem_object_create_shmem(i915, PAGE_SIZE);
	अगर (IS_ERR(obj)) अणु
		err = PTR_ERR(obj);
		pr_err("i915_gem_object_create failed, err=%d\n", err);
		जाओ out;
	पूर्ण

	अगर (!i915_gem_object_has_काष्ठा_page(obj)) अणु
		err = -EINVAL;
		pr_err("shmem has no struct page\n");
		जाओ out_obj;
	पूर्ण

	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_attach_phys(obj, PAGE_SIZE);
	i915_gem_object_unlock(obj);
	अगर (err) अणु
		pr_err("i915_gem_object_attach_phys failed, err=%d\n", err);
		जाओ out_obj;
	पूर्ण

	अगर (i915_gem_object_has_काष्ठा_page(obj)) अणु
		pr_err("i915_gem_object_attach_phys did not create a phys object\n");
		err = -EINVAL;
		जाओ out_obj;
	पूर्ण

	अगर (!atomic_पढ़ो(&obj->mm.pages_pin_count)) अणु
		pr_err("i915_gem_object_attach_phys did not pin its phys pages\n");
		err = -EINVAL;
		जाओ out_obj;
	पूर्ण

	/* Make the object dirty so that put_pages must करो copy back the data */
	i915_gem_object_lock(obj, शून्य);
	err = i915_gem_object_set_to_gtt_करोमुख्य(obj, true);
	i915_gem_object_unlock(obj);
	अगर (err) अणु
		pr_err("i915_gem_object_set_to_gtt_domain failed with err=%d\n",
		       err);
		जाओ out_obj;
	पूर्ण

out_obj:
	i915_gem_object_put(obj);
out:
	वापस err;
पूर्ण

पूर्णांक i915_gem_phys_mock_selftests(व्योम)
अणु
	अटल स्थिर काष्ठा i915_subtest tests[] = अणु
		SUBTEST(mock_phys_object),
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
