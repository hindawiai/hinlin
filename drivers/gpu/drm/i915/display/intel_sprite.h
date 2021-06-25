<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#अगर_अघोषित __INTEL_SPRITE_H__
#घोषणा __INTEL_SPRITE_H__

#समावेश <linux/types.h>

#समावेश "intel_display.h"

काष्ठा drm_device;
काष्ठा drm_display_mode;
काष्ठा drm_file;
काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_plane_state;

/*
 * FIXME: We should instead only take spinlocks once क्रम the entire update
 * instead of once per mmio.
 */
#अगर IS_ENABLED(CONFIG_PROVE_LOCKING)
#घोषणा VBLANK_EVASION_TIME_US 250
#अन्यथा
#घोषणा VBLANK_EVASION_TIME_US 100
#पूर्ण_अगर

पूर्णांक पूर्णांकel_usecs_to_scanlines(स्थिर काष्ठा drm_display_mode *adjusted_mode,
			     पूर्णांक usecs);
काष्ठा पूर्णांकel_plane *पूर्णांकel_sprite_plane_create(काष्ठा drm_i915_निजी *dev_priv,
					      क्रमागत pipe pipe, पूर्णांक plane);
पूर्णांक पूर्णांकel_sprite_set_colorkey_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
व्योम पूर्णांकel_pipe_update_start(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state);
व्योम पूर्णांकel_pipe_update_end(काष्ठा पूर्णांकel_crtc_state *new_crtc_state);
पूर्णांक पूर्णांकel_plane_check_src_coordinates(काष्ठा पूर्णांकel_plane_state *plane_state);
पूर्णांक chv_plane_check_rotation(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);

अटल अंतरभूत u8 icl_hdr_plane_mask(व्योम)
अणु
	वापस BIT(PLANE_PRIMARY) |
		BIT(PLANE_SPRITE0) | BIT(PLANE_SPRITE1);
पूर्ण

पूर्णांक ivb_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);
पूर्णांक hsw_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);
पूर्णांक vlv_plane_min_cdclk(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state);

#पूर्ण_अगर /* __INTEL_SPRITE_H__ */
