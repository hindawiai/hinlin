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
selftest(sanitycheck, i915_live_sanitycheck) /* keep first (igt selfcheck) */
selftest(uncore, पूर्णांकel_uncore_live_selftests)
selftest(workarounds, पूर्णांकel_workarounds_live_selftests)
selftest(gt_engines, पूर्णांकel_engine_live_selftests)
selftest(gt_समयlines, पूर्णांकel_समयline_live_selftests)
selftest(gt_contexts, पूर्णांकel_context_live_selftests)
selftest(gt_lrc, पूर्णांकel_lrc_live_selftests)
selftest(gt_mocs, पूर्णांकel_mocs_live_selftests)
selftest(gt_pm, पूर्णांकel_gt_pm_live_selftests)
selftest(gt_heartbeat, पूर्णांकel_heartbeat_live_selftests)
selftest(requests, i915_request_live_selftests)
selftest(active, i915_active_live_selftests)
selftest(objects, i915_gem_object_live_selftests)
selftest(mman, i915_gem_mman_live_selftests)
selftest(dmabuf, i915_gem_dmabuf_live_selftests)
selftest(vma, i915_vma_live_selftests)
selftest(coherency, i915_gem_coherency_live_selftests)
selftest(gtt, i915_gem_gtt_live_selftests)
selftest(gem, i915_gem_live_selftests)
selftest(evict, i915_gem_evict_live_selftests)
selftest(hugepages, i915_gem_huge_page_live_selftests)
selftest(gem_contexts, i915_gem_context_live_selftests)
selftest(gem_execbuf, i915_gem_execbuffer_live_selftests)
selftest(blt, i915_gem_object_blt_live_selftests)
selftest(client, i915_gem_client_blt_live_selftests)
selftest(reset, पूर्णांकel_reset_live_selftests)
selftest(memory_region, पूर्णांकel_memory_region_live_selftests)
selftest(hangcheck, पूर्णांकel_hangcheck_live_selftests)
selftest(execlists, पूर्णांकel_execlists_live_selftests)
selftest(ring_submission, पूर्णांकel_ring_submission_live_selftests)
selftest(perf, i915_perf_live_selftests)
/* Here be dragons: keep last to run last! */
selftest(late_gt_pm, पूर्णांकel_gt_pm_late_selftests)
