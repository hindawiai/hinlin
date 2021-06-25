<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#अगर_अघोषित __IGT_GEM_UTILS_H__
#घोषणा __IGT_GEM_UTILS_H__

#समावेश <linux/types.h>

काष्ठा i915_request;
काष्ठा i915_gem_context;
काष्ठा i915_vma;

काष्ठा पूर्णांकel_context;
काष्ठा पूर्णांकel_engine_cs;

काष्ठा i915_request *
igt_request_alloc(काष्ठा i915_gem_context *ctx, काष्ठा पूर्णांकel_engine_cs *engine);

काष्ठा i915_vma *
igt_emit_store_dw(काष्ठा i915_vma *vma,
		  u64 offset,
		  अचिन्हित दीर्घ count,
		  u32 val);

पूर्णांक igt_gpu_fill_dw(काष्ठा पूर्णांकel_context *ce,
		    काष्ठा i915_vma *vma, u64 offset,
		    अचिन्हित दीर्घ count, u32 val);

#पूर्ण_अगर /* __IGT_GEM_UTILS_H__ */
