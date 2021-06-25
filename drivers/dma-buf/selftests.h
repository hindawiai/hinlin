<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/* List each unit test as selftest(name, function)
 *
 * The name is used as both an क्रमागत and expanded as subtest__name to create
 * a module parameter. It must be unique and legal क्रम a C identअगरier.
 *
 * The function should be of type पूर्णांक function(व्योम). It may be conditionally
 * compiled using #अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST).
 *
 * Tests are executed in order by igt/dmabuf_selftest
 */
selftest(sanitycheck, __sanitycheck__) /* keep first (igt selfcheck) */
selftest(dma_fence, dma_fence)
selftest(dma_fence_chain, dma_fence_chain)
