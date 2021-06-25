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
selftest(engine_cs, पूर्णांकel_engine_cs_perf_selftests)
selftest(request, i915_request_perf_selftests)
selftest(blt, i915_gem_object_blt_perf_selftests)
selftest(region, पूर्णांकel_memory_region_perf_selftests)
