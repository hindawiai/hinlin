<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित selftest
#घोषणा selftest(x, y)
#पूर्ण_अगर

/*
 * List each unit test as selftest(name, function)
 *
 * The name is used as both an क्रमागत and expanded as subtest__name to create
 * a module parameter. It must be unique and legal क्रम a C identअगरier.
 *
 * The function should be of type पूर्णांक function(व्योम). It may be conditionally
 * compiled using #अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST).
 *
 * Tests are executed in order by igt/i915_selftest
 */
selftest(sanitycheck, i915_mock_sanitycheck) /* keep first (igt selfcheck) */
selftest(shmem, shmem_utils_mock_selftests)
selftest(fence, i915_sw_fence_mock_selftests)
selftest(scatterlist, scatterlist_mock_selftests)
selftest(syncmap, i915_syncmap_mock_selftests)
selftest(uncore, पूर्णांकel_uncore_mock_selftests)
selftest(ring, पूर्णांकel_ring_mock_selftests)
selftest(engine, पूर्णांकel_engine_cs_mock_selftests)
selftest(समयlines, पूर्णांकel_समयline_mock_selftests)
selftest(requests, i915_request_mock_selftests)
selftest(objects, i915_gem_object_mock_selftests)
selftest(phys, i915_gem_phys_mock_selftests)
selftest(dmabuf, i915_gem_dmabuf_mock_selftests)
selftest(vma, i915_vma_mock_selftests)
selftest(evict, i915_gem_evict_mock_selftests)
selftest(gtt, i915_gem_gtt_mock_selftests)
selftest(hugepages, i915_gem_huge_page_mock_selftests)
selftest(contexts, i915_gem_context_mock_selftests)
selftest(buddy, i915_buddy_mock_selftests)
selftest(memory_region, पूर्णांकel_memory_region_mock_selftests)
