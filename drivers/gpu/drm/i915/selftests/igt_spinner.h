<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#अगर_अघोषित __I915_SELFTESTS_IGT_SPINNER_H__
#घोषणा __I915_SELFTESTS_IGT_SPINNER_H__

#समावेश "gem/i915_gem_context.h"
#समावेश "gt/intel_engine.h"

#समावेश "i915_drv.h"
#समावेश "i915_request.h"
#समावेश "i915_selftest.h"

काष्ठा पूर्णांकel_gt;

काष्ठा igt_spinner अणु
	काष्ठा पूर्णांकel_gt *gt;
	काष्ठा drm_i915_gem_object *hws;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा पूर्णांकel_context *ce;
	काष्ठा i915_vma *hws_vma, *batch_vma;
	u32 *batch;
	व्योम *seqno;
पूर्ण;

पूर्णांक igt_spinner_init(काष्ठा igt_spinner *spin, काष्ठा पूर्णांकel_gt *gt);
पूर्णांक igt_spinner_pin(काष्ठा igt_spinner *spin,
		    काष्ठा पूर्णांकel_context *ce,
		    काष्ठा i915_gem_ww_ctx *ww);
व्योम igt_spinner_fini(काष्ठा igt_spinner *spin);

काष्ठा i915_request *
igt_spinner_create_request(काष्ठा igt_spinner *spin,
			   काष्ठा पूर्णांकel_context *ce,
			   u32 arbitration_command);
व्योम igt_spinner_end(काष्ठा igt_spinner *spin);

bool igt_रुको_क्रम_spinner(काष्ठा igt_spinner *spin, काष्ठा i915_request *rq);

#पूर्ण_अगर
