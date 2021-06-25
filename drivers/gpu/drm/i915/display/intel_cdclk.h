<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_CDCLK_H__
#घोषणा __INTEL_CDCLK_H__

#समावेश <linux/types.h>

#समावेश "i915_drv.h"
#समावेश "intel_display.h"
#समावेश "intel_global_state.h"

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc_state;

काष्ठा पूर्णांकel_cdclk_vals अणु
	u32 cdclk;
	u16 refclk;
	u8 भागider;	/* CD2X भागider * 2 */
	u8 ratio;
पूर्ण;

काष्ठा पूर्णांकel_cdclk_state अणु
	काष्ठा पूर्णांकel_global_state base;

	/*
	 * Logical configuration of cdclk (used क्रम all scaling,
	 * watermark, etc. calculations and checks). This is
	 * computed as अगर all enabled crtcs were active.
	 */
	काष्ठा पूर्णांकel_cdclk_config logical;

	/*
	 * Actual configuration of cdclk, can be dअगरferent from the
	 * logical configuration only when all crtc's are DPMS off.
	 */
	काष्ठा पूर्णांकel_cdclk_config actual;

	/* minimum acceptable cdclk क्रम each pipe */
	पूर्णांक min_cdclk[I915_MAX_PIPES];
	/* minimum acceptable voltage level क्रम each pipe */
	u8 min_voltage_level[I915_MAX_PIPES];

	/* pipe to which cd2x update is synchronized */
	क्रमागत pipe pipe;

	/* क्रमced minimum cdclk क्रम glk+ audio w/a */
	पूर्णांक क्रमce_min_cdclk;

	/* biपंचांगask of active pipes */
	u8 active_pipes;
पूर्ण;

पूर्णांक पूर्णांकel_crtc_compute_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम पूर्णांकel_cdclk_init_hw(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_cdclk_uninit_hw(काष्ठा drm_i915_निजी *i915);
व्योम पूर्णांकel_init_cdclk_hooks(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_update_max_cdclk(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_update_cdclk(काष्ठा drm_i915_निजी *dev_priv);
u32 पूर्णांकel_पढ़ो_rawclk(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_cdclk_needs_modeset(स्थिर काष्ठा पूर्णांकel_cdclk_config *a,
			       स्थिर काष्ठा पूर्णांकel_cdclk_config *b);
व्योम पूर्णांकel_set_cdclk_pre_plane_update(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_set_cdclk_post_plane_update(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_dump_cdclk_config(स्थिर काष्ठा पूर्णांकel_cdclk_config *cdclk_config,
			     स्थिर अक्षर *context);
पूर्णांक पूर्णांकel_modeset_calc_cdclk(काष्ठा पूर्णांकel_atomic_state *state);

काष्ठा पूर्णांकel_cdclk_state *
पूर्णांकel_atomic_get_cdclk_state(काष्ठा पूर्णांकel_atomic_state *state);

#घोषणा to_पूर्णांकel_cdclk_state(x) container_of((x), काष्ठा पूर्णांकel_cdclk_state, base)
#घोषणा पूर्णांकel_atomic_get_old_cdclk_state(state) \
	to_पूर्णांकel_cdclk_state(पूर्णांकel_atomic_get_old_global_obj_state(state, &to_i915(state->base.dev)->cdclk.obj))
#घोषणा पूर्णांकel_atomic_get_new_cdclk_state(state) \
	to_पूर्णांकel_cdclk_state(पूर्णांकel_atomic_get_new_global_obj_state(state, &to_i915(state->base.dev)->cdclk.obj))

पूर्णांक पूर्णांकel_cdclk_init(काष्ठा drm_i915_निजी *dev_priv);

#पूर्ण_अगर /* __INTEL_CDCLK_H__ */
