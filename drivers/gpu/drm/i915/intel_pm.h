<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_PM_H__
#घोषणा __INTEL_PM_H__

#समावेश <linux/types.h>

#समावेश "display/intel_bw.h"
#समावेश "display/intel_display.h"
#समावेश "display/intel_global_state.h"

#समावेश "i915_drv.h"
#समावेश "i915_reg.h"

काष्ठा drm_device;
काष्ठा drm_i915_निजी;
काष्ठा i915_request;
काष्ठा पूर्णांकel_atomic_state;
काष्ठा पूर्णांकel_crtc;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_plane;
काष्ठा skl_ddb_entry;
काष्ठा skl_pipe_wm;
काष्ठा skl_wm_level;

व्योम पूर्णांकel_init_घड़ी_gating(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_suspend_hw(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक ilk_wm_max_level(स्थिर काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_update_watermarks(काष्ठा पूर्णांकel_crtc *crtc);
व्योम पूर्णांकel_init_pm(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_init_घड़ी_gating_hooks(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_pm_setup(काष्ठा drm_i915_निजी *dev_priv);
व्योम g4x_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv);
व्योम vlv_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv);
व्योम ilk_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv);
व्योम skl_wm_get_hw_state(काष्ठा drm_i915_निजी *dev_priv);
u8 पूर्णांकel_enabled_dbuf_slices_mask(काष्ठा drm_i915_निजी *dev_priv);
व्योम skl_pipe_ddb_get_hw_state(काष्ठा पूर्णांकel_crtc *crtc,
			       काष्ठा skl_ddb_entry *ddb_y,
			       काष्ठा skl_ddb_entry *ddb_uv);
व्योम skl_ddb_get_hw_state(काष्ठा drm_i915_निजी *dev_priv);
u32 skl_ddb_dbuf_slice_mask(काष्ठा drm_i915_निजी *dev_priv,
			    स्थिर काष्ठा skl_ddb_entry *entry);
व्योम skl_pipe_wm_get_hw_state(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा skl_pipe_wm *out);
व्योम g4x_wm_sanitize(काष्ठा drm_i915_निजी *dev_priv);
व्योम vlv_wm_sanitize(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_can_enable_sagv(काष्ठा drm_i915_निजी *dev_priv,
			   स्थिर काष्ठा पूर्णांकel_bw_state *bw_state);
व्योम पूर्णांकel_sagv_pre_plane_update(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_sagv_post_plane_update(काष्ठा पूर्णांकel_atomic_state *state);
स्थिर काष्ठा skl_wm_level *skl_plane_wm_level(स्थिर काष्ठा skl_pipe_wm *pipe_wm,
					      क्रमागत plane_id plane_id,
					      पूर्णांक level);
स्थिर काष्ठा skl_wm_level *skl_plane_trans_wm(स्थिर काष्ठा skl_pipe_wm *pipe_wm,
					      क्रमागत plane_id plane_id);
bool skl_wm_level_equals(स्थिर काष्ठा skl_wm_level *l1,
			 स्थिर काष्ठा skl_wm_level *l2);
bool skl_ddb_allocation_overlaps(स्थिर काष्ठा skl_ddb_entry *ddb,
				 स्थिर काष्ठा skl_ddb_entry *entries,
				 पूर्णांक num_entries, पूर्णांक ignore_idx);
व्योम skl_ग_लिखो_plane_wm(काष्ठा पूर्णांकel_plane *plane,
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
व्योम skl_ग_लिखो_cursor_wm(काष्ठा पूर्णांकel_plane *plane,
			 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
bool ilk_disable_lp_wm(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_init_ipc(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_enable_ipc(काष्ठा drm_i915_निजी *dev_priv);

bool पूर्णांकel_set_memory_cxsr(काष्ठा drm_i915_निजी *dev_priv, bool enable);

काष्ठा पूर्णांकel_dbuf_state अणु
	काष्ठा पूर्णांकel_global_state base;

	काष्ठा skl_ddb_entry ddb[I915_MAX_PIPES];
	अचिन्हित पूर्णांक weight[I915_MAX_PIPES];
	u8 slices[I915_MAX_PIPES];

	u8 enabled_slices;
	u8 active_pipes;
पूर्ण;

पूर्णांक पूर्णांकel_dbuf_init(काष्ठा drm_i915_निजी *dev_priv);

काष्ठा पूर्णांकel_dbuf_state *
पूर्णांकel_atomic_get_dbuf_state(काष्ठा पूर्णांकel_atomic_state *state);

#घोषणा to_पूर्णांकel_dbuf_state(x) container_of((x), काष्ठा पूर्णांकel_dbuf_state, base)
#घोषणा पूर्णांकel_atomic_get_old_dbuf_state(state) \
	to_पूर्णांकel_dbuf_state(पूर्णांकel_atomic_get_old_global_obj_state(state, &to_i915(state->base.dev)->dbuf.obj))
#घोषणा पूर्णांकel_atomic_get_new_dbuf_state(state) \
	to_पूर्णांकel_dbuf_state(पूर्णांकel_atomic_get_new_global_obj_state(state, &to_i915(state->base.dev)->dbuf.obj))

पूर्णांक पूर्णांकel_dbuf_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_dbuf_pre_plane_update(काष्ठा पूर्णांकel_atomic_state *state);
व्योम पूर्णांकel_dbuf_post_plane_update(काष्ठा पूर्णांकel_atomic_state *state);

#पूर्ण_अगर /* __INTEL_PM_H__ */
