<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#अगर_अघोषित __INTEL_LRC_H__
#घोषणा __INTEL_LRC_H__

#समावेश <linux/types.h>

#समावेश "intel_context.h"
#समावेश "intel_lrc_reg.h"

काष्ठा drm_i915_gem_object;
काष्ठा पूर्णांकel_engine_cs;
काष्ठा पूर्णांकel_ring;

/* At the start of the context image is its per-process HWS page */
#घोषणा LRC_PPHWSP_PN	(0)
#घोषणा LRC_PPHWSP_SZ	(1)
/* After the PPHWSP we have the logical state क्रम the context */
#घोषणा LRC_STATE_PN	(LRC_PPHWSP_PN + LRC_PPHWSP_SZ)
#घोषणा LRC_STATE_OFFSET (LRC_STATE_PN * PAGE_SIZE)

/* Space within PPHWSP reserved to be used as scratch */
#घोषणा LRC_PPHWSP_SCRATCH		0x34
#घोषणा LRC_PPHWSP_SCRATCH_ADDR		(LRC_PPHWSP_SCRATCH * माप(u32))

व्योम lrc_init_wa_ctx(काष्ठा पूर्णांकel_engine_cs *engine);
व्योम lrc_fini_wa_ctx(काष्ठा पूर्णांकel_engine_cs *engine);

पूर्णांक lrc_alloc(काष्ठा पूर्णांकel_context *ce,
	      काष्ठा पूर्णांकel_engine_cs *engine);
व्योम lrc_reset(काष्ठा पूर्णांकel_context *ce);
व्योम lrc_fini(काष्ठा पूर्णांकel_context *ce);
व्योम lrc_destroy(काष्ठा kref *kref);

पूर्णांक
lrc_pre_pin(काष्ठा पूर्णांकel_context *ce,
	    काष्ठा पूर्णांकel_engine_cs *engine,
	    काष्ठा i915_gem_ww_ctx *ww,
	    व्योम **vaddr);
पूर्णांक
lrc_pin(काष्ठा पूर्णांकel_context *ce,
	काष्ठा पूर्णांकel_engine_cs *engine,
	व्योम *vaddr);
व्योम lrc_unpin(काष्ठा पूर्णांकel_context *ce);
व्योम lrc_post_unpin(काष्ठा पूर्णांकel_context *ce);

व्योम lrc_init_state(काष्ठा पूर्णांकel_context *ce,
		    काष्ठा पूर्णांकel_engine_cs *engine,
		    व्योम *state);

व्योम lrc_init_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		   स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		   bool clear);
व्योम lrc_reset_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		    स्थिर काष्ठा पूर्णांकel_engine_cs *engine);

u32 lrc_update_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		    स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		    u32 head);
व्योम lrc_update_offsets(काष्ठा पूर्णांकel_context *ce,
			काष्ठा पूर्णांकel_engine_cs *engine);

व्योम lrc_check_regs(स्थिर काष्ठा पूर्णांकel_context *ce,
		    स्थिर काष्ठा पूर्णांकel_engine_cs *engine,
		    स्थिर अक्षर *when);

व्योम lrc_update_runसमय(काष्ठा पूर्णांकel_context *ce);
अटल अंतरभूत u32 lrc_get_runसमय(स्थिर काष्ठा पूर्णांकel_context *ce)
अणु
	/*
	 * We can use either ppHWSP[16] which is recorded beक्रमe the context
	 * चयन (and so excludes the cost of context चयनes) or use the
	 * value from the context image itself, which is saved/restored earlier
	 * and so includes the cost of the save.
	 */
	वापस READ_ONCE(ce->lrc_reg_state[CTX_TIMESTAMP]);
पूर्ण

#पूर्ण_अगर /* __INTEL_LRC_H__ */
