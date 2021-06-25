<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020,2021 Intel Corporation
 */

#अगर_अघोषित __INTEL_STEP_H__
#घोषणा __INTEL_STEP_H__

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;

काष्ठा पूर्णांकel_step_info अणु
	u8 gt_step;
	u8 display_step;
पूर्ण;

/*
 * Symbolic steppings that करो not match the hardware. These are valid both as gt
 * and display steppings as symbolic names.
 */
क्रमागत पूर्णांकel_step अणु
	STEP_NONE = 0,
	STEP_A0,
	STEP_A2,
	STEP_B0,
	STEP_B1,
	STEP_C0,
	STEP_D0,
	STEP_D1,
	STEP_E0,
	STEP_F0,
	STEP_G0,
	STEP_FUTURE,
	STEP_FOREVER,
पूर्ण;

व्योम पूर्णांकel_step_init(काष्ठा drm_i915_निजी *i915);

#पूर्ण_अगर /* __INTEL_STEP_H__ */
