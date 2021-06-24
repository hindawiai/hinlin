<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2014 Intel Corporation
 */

#अगर_अघोषित _INTEL_RENDERSTATE_H_
#घोषणा _INTEL_RENDERSTATE_H_

#समावेश <linux/types.h>
#समावेश "i915_gem.h"

काष्ठा i915_request;
काष्ठा पूर्णांकel_context;
काष्ठा i915_vma;

काष्ठा पूर्णांकel_renderstate_rodata अणु
	स्थिर u32 *reloc;
	स्थिर u32 *batch;
	स्थिर u32 batch_items;
पूर्ण;

#घोषणा RO_RENDERSTATE(_g)						\
	स्थिर काष्ठा पूर्णांकel_renderstate_rodata gen ## _g ## _null_state = अणु \
		.reloc = gen ## _g ## _null_state_relocs,		\
		.batch = gen ## _g ## _null_state_batch,		\
		.batch_items = माप(gen ## _g ## _null_state_batch)/4, \
	पूर्ण

बाह्य स्थिर काष्ठा पूर्णांकel_renderstate_rodata gen6_null_state;
बाह्य स्थिर काष्ठा पूर्णांकel_renderstate_rodata gen7_null_state;
बाह्य स्थिर काष्ठा पूर्णांकel_renderstate_rodata gen8_null_state;
बाह्य स्थिर काष्ठा पूर्णांकel_renderstate_rodata gen9_null_state;

काष्ठा पूर्णांकel_renderstate अणु
	काष्ठा i915_gem_ww_ctx ww;
	स्थिर काष्ठा पूर्णांकel_renderstate_rodata *rodata;
	काष्ठा i915_vma *vma;
	u32 batch_offset;
	u32 batch_size;
	u32 aux_offset;
	u32 aux_size;
पूर्ण;

पूर्णांक पूर्णांकel_renderstate_init(काष्ठा पूर्णांकel_renderstate *so,
			   काष्ठा पूर्णांकel_context *ce);
पूर्णांक पूर्णांकel_renderstate_emit(काष्ठा पूर्णांकel_renderstate *so,
			   काष्ठा i915_request *rq);
व्योम पूर्णांकel_renderstate_fini(काष्ठा पूर्णांकel_renderstate *so,
			    काष्ठा पूर्णांकel_context *ce);

#पूर्ण_अगर /* _INTEL_RENDERSTATE_H_ */
