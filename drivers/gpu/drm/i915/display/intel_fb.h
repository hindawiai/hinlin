<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2020-2021 Intel Corporation
 */

#अगर_अघोषित __INTEL_FB_H__
#घोषणा __INTEL_FB_H__

#समावेश <linux/types.h>

काष्ठा drm_framebuffer;

काष्ठा drm_i915_निजी;

काष्ठा पूर्णांकel_fb_view;
काष्ठा पूर्णांकel_framebuffer;
काष्ठा पूर्णांकel_plane_state;

bool is_ccs_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane);
bool is_gen12_ccs_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane);
bool is_gen12_ccs_cc_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane);
bool is_aux_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane);
bool is_semiplanar_uv_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane);

bool is_surface_linear(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane);

पूर्णांक मुख्य_to_ccs_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक मुख्य_plane);
पूर्णांक skl_ccs_to_मुख्य_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक ccs_plane);
पूर्णांक skl_मुख्य_to_aux_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक मुख्य_plane);

अचिन्हित पूर्णांक पूर्णांकel_tile_size(स्थिर काष्ठा drm_i915_निजी *i915);
अचिन्हित पूर्णांक पूर्णांकel_tile_height(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane);
अचिन्हित पूर्णांक पूर्णांकel_tile_row_size(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane);

अचिन्हित पूर्णांक पूर्णांकel_cursor_alignment(स्थिर काष्ठा drm_i915_निजी *i915);

व्योम पूर्णांकel_fb_plane_get_subsampling(पूर्णांक *hsub, पूर्णांक *vsub,
				    स्थिर काष्ठा drm_framebuffer *fb,
				    पूर्णांक color_plane);

u32 पूर्णांकel_plane_adjust_aligned_offset(पूर्णांक *x, पूर्णांक *y,
				      स्थिर काष्ठा पूर्णांकel_plane_state *state,
				      पूर्णांक color_plane,
				      u32 old_offset, u32 new_offset);
u32 पूर्णांकel_plane_compute_aligned_offset(पूर्णांक *x, पूर्णांक *y,
				       स्थिर काष्ठा पूर्णांकel_plane_state *state,
				       पूर्णांक color_plane);

पूर्णांक पूर्णांकel_fill_fb_info(काष्ठा drm_i915_निजी *i915, काष्ठा drm_framebuffer *fb);
व्योम पूर्णांकel_fb_fill_view(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, अचिन्हित पूर्णांक rotation,
			काष्ठा पूर्णांकel_fb_view *view);
पूर्णांक पूर्णांकel_plane_compute_gtt(काष्ठा पूर्णांकel_plane_state *plane_state);

#पूर्ण_अगर /* __INTEL_FB_H__ */
