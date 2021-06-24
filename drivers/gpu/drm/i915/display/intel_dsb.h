<शैली गुरु>
/* SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_DSB_H
#घोषणा _INTEL_DSB_H

#समावेश <linux/types.h>

#समावेश "i915_reg.h"

काष्ठा पूर्णांकel_crtc_state;
काष्ठा i915_vma;

क्रमागत dsb_id अणु
	INVALID_DSB = -1,
	DSB1,
	DSB2,
	DSB3,
	MAX_DSB_PER_PIPE
पूर्ण;

काष्ठा पूर्णांकel_dsb अणु
	क्रमागत dsb_id id;
	u32 *cmd_buf;
	काष्ठा i915_vma *vma;

	/*
	 * मुक्त_pos will poपूर्णांक the first मुक्त entry position
	 * and help in calculating tail of command buffer.
	 */
	पूर्णांक मुक्त_pos;

	/*
	 * ins_start_offset will help to store start address of the dsb
	 * instuction and help in identअगरying the batch of स्वतः-increment
	 * रेजिस्टर.
	 */
	u32 ins_start_offset;
पूर्ण;

व्योम पूर्णांकel_dsb_prepare(काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dsb_cleanup(काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_dsb_reg_ग_लिखो(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 i915_reg_t reg, u32 val);
व्योम पूर्णांकel_dsb_indexed_reg_ग_लिखो(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 i915_reg_t reg, u32 val);
व्योम पूर्णांकel_dsb_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);

#पूर्ण_अगर
