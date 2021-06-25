<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#अगर_अघोषित __GEN2_ENGINE_CS_H__
#घोषणा __GEN2_ENGINE_CS_H__

#समावेश <linux/types.h>

काष्ठा i915_request;
काष्ठा पूर्णांकel_engine_cs;

पूर्णांक gen2_emit_flush(काष्ठा i915_request *rq, u32 mode);
पूर्णांक gen4_emit_flush_rcs(काष्ठा i915_request *rq, u32 mode);
पूर्णांक gen4_emit_flush_vcs(काष्ठा i915_request *rq, u32 mode);

u32 *gen3_emit_bपढ़ोcrumb(काष्ठा i915_request *rq, u32 *cs);
u32 *gen5_emit_bपढ़ोcrumb(काष्ठा i915_request *rq, u32 *cs);

पूर्णांक i830_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
		       अचिन्हित पूर्णांक dispatch_flags);
पूर्णांक gen3_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 len,
		       अचिन्हित पूर्णांक dispatch_flags);
पूर्णांक gen4_emit_bb_start(काष्ठा i915_request *rq,
		       u64 offset, u32 length,
		       अचिन्हित पूर्णांक dispatch_flags);

व्योम gen2_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम gen2_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम gen3_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम gen3_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम gen5_irq_enable(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम gen5_irq_disable(काष्ठा पूर्णांकel_engine_cs *engine);

#पूर्ण_अगर /* __GEN2_ENGINE_CS_H__ */
