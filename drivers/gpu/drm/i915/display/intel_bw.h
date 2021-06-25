<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_BW_H__
#घोषणा __INTEL_BW_H__

#समावेश <drm/drm_atomic.h>

#समावेश "intel_display.h"
#समावेश "intel_display_power.h"
#समावेश "intel_global_state.h"

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc_state;

काष्ठा पूर्णांकel_dbuf_bw अणु
	पूर्णांक used_bw[I915_MAX_DBUF_SLICES];
पूर्ण;

काष्ठा पूर्णांकel_bw_state अणु
	काष्ठा पूर्णांकel_global_state base;
	काष्ठा पूर्णांकel_dbuf_bw dbuf_bw[I915_MAX_PIPES];

	/*
	 * Contains a bit mask, used to determine, whether correspondent
	 * pipe allows SAGV or not.
	 */
	u8 pipe_sagv_reject;

	/*
	 * Current QGV poपूर्णांकs mask, which restricts
	 * some particular SAGV states, not to confuse
	 * with pipe_sagv_mask.
	 */
	u8 qgv_poपूर्णांकs_mask;

	अचिन्हित पूर्णांक data_rate[I915_MAX_PIPES];
	u8 num_active_planes[I915_MAX_PIPES];

	/* biपंचांगask of active pipes */
	u8 active_pipes;

	पूर्णांक min_cdclk;
पूर्ण;

#घोषणा to_पूर्णांकel_bw_state(x) container_of((x), काष्ठा पूर्णांकel_bw_state, base)

काष्ठा पूर्णांकel_bw_state *
पूर्णांकel_atomic_get_old_bw_state(काष्ठा पूर्णांकel_atomic_state *state);

काष्ठा पूर्णांकel_bw_state *
पूर्णांकel_atomic_get_new_bw_state(काष्ठा पूर्णांकel_atomic_state *state);

काष्ठा पूर्णांकel_bw_state *
पूर्णांकel_atomic_get_bw_state(काष्ठा पूर्णांकel_atomic_state *state);

व्योम पूर्णांकel_bw_init_hw(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_bw_init(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक पूर्णांकel_bw_atomic_check(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_bw_crtc_update(काष्ठा पूर्णांकel_bw_state *bw_state,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
पूर्णांक icl_pcode_restrict_qgv_poपूर्णांकs(काष्ठा drm_i915_निजी *dev_priv,
				  u32 poपूर्णांकs_mask);
पूर्णांक पूर्णांकel_bw_calc_min_cdclk(काष्ठा पूर्णांकel_atomic_state *state);
पूर्णांक skl_bw_calc_min_cdclk(काष्ठा पूर्णांकel_atomic_state *state);

#पूर्ण_अगर /* __INTEL_BW_H__ */
