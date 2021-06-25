<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __GEN6_ENGINE_CS_H__
#घोषणा __GEN6_ENGINE_CS_H__

#समावेश <linux/types.h>

#समावेश "intel_gpu_commands.h"

काष्ठा i915_request;
काष्ठा पूर्णांकel_engine_cs;

पूर्णांक gen6_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode);
पूर्णांक gen6_emit_flush_vcs(काष्ठा i915_request *rq, u32 mode);
पूर्णांक gen6_emit_flush_xcs(काष्ठा i915_request *rq, u32 mode);
u32 *gen6_emit_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs);
u32 *gen6_emit_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs);

पूर्णांक gen7_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode);
u32 *gen7_emit_bपढ़ोcrumb_rcs(काष्ठा i915_request *rq, u32 *cs);
u32 *gen7_emit_bपढ़ोcrumb_xcs(काष्ठा i915_request *rq, u32 *cs);

पूर्णांक gen6_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
		       अचिन्हित पूर्णांक dispatch_flags);
पूर्णांक hsw_emit_bb_start(काष्ठा i915_request *rq,
		      u64 offset, u32 len,
		      अचिन्हित पूर्णांक dispatch_flags);

व्योम gen6_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम gen6_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine);

व्योम hsw_irq_enable_vecs(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम hsw_irq_disable_vecs(काष्ठा पूर्णांकel_engine_cs *engine);

#पूर्ण_अगर /* __GEN6_ENGINE_CS_H__ */
