<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2021 Intel Corporation
 */

#समावेश <drm/drm_framebuffer.h>

#समावेश "intel_display.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fb.h"

#घोषणा check_array_bounds(i915, a, i) drm_WARN_ON(&(i915)->drm, (i) >= ARRAY_SIZE(a))

bool is_ccs_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane)
अणु
	अगर (!is_ccs_modअगरier(fb->modअगरier))
		वापस false;

	वापस plane >= fb->क्रमmat->num_planes / 2;
पूर्ण

bool is_gen12_ccs_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane)
अणु
	वापस is_gen12_ccs_modअगरier(fb->modअगरier) && is_ccs_plane(fb, plane);
पूर्ण

bool is_gen12_ccs_cc_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane)
अणु
	वापस fb->modअगरier == I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC &&
	       plane == 2;
पूर्ण

bool is_aux_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक plane)
अणु
	अगर (is_ccs_modअगरier(fb->modअगरier))
		वापस is_ccs_plane(fb, plane);

	वापस plane == 1;
पूर्ण

bool is_semiplanar_uv_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane)
अणु
	वापस पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier) &&
		color_plane == 1;
पूर्ण

bool is_surface_linear(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane)
अणु
	वापस fb->modअगरier == DRM_FORMAT_MOD_LINEAR ||
	       is_gen12_ccs_plane(fb, color_plane);
पूर्ण

पूर्णांक मुख्य_to_ccs_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक मुख्य_plane)
अणु
	drm_WARN_ON(fb->dev, !is_ccs_modअगरier(fb->modअगरier) ||
		    (मुख्य_plane && मुख्य_plane >= fb->क्रमmat->num_planes / 2));

	वापस fb->क्रमmat->num_planes / 2 + मुख्य_plane;
पूर्ण

पूर्णांक skl_ccs_to_मुख्य_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक ccs_plane)
अणु
	drm_WARN_ON(fb->dev, !is_ccs_modअगरier(fb->modअगरier) ||
		    ccs_plane < fb->क्रमmat->num_planes / 2);

	अगर (is_gen12_ccs_cc_plane(fb, ccs_plane))
		वापस 0;

	वापस ccs_plane - fb->क्रमmat->num_planes / 2;
पूर्ण

पूर्णांक skl_मुख्य_to_aux_plane(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक मुख्य_plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(fb->dev);

	अगर (is_ccs_modअगरier(fb->modअगरier))
		वापस मुख्य_to_ccs_plane(fb, मुख्य_plane);
	अन्यथा अगर (DISPLAY_VER(i915) < 11 &&
		 पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(fb->क्रमmat, fb->modअगरier))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_tile_size(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	वापस IS_DISPLAY_VER(i915, 2) ? 2048 : 4096;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_tile_height(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane)
अणु
	अगर (is_gen12_ccs_plane(fb, color_plane))
		वापस 1;

	वापस पूर्णांकel_tile_size(to_i915(fb->dev)) /
		पूर्णांकel_tile_width_bytes(fb, color_plane);
पूर्ण

/* Return the tile dimensions in pixel units */
अटल व्योम पूर्णांकel_tile_dims(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane,
			    अचिन्हित पूर्णांक *tile_width,
			    अचिन्हित पूर्णांक *tile_height)
अणु
	अचिन्हित पूर्णांक tile_width_bytes = पूर्णांकel_tile_width_bytes(fb, color_plane);
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[color_plane];

	*tile_width = tile_width_bytes / cpp;
	*tile_height = पूर्णांकel_tile_height(fb, color_plane);
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_tile_row_size(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane)
अणु
	अचिन्हित पूर्णांक tile_width, tile_height;

	पूर्णांकel_tile_dims(fb, color_plane, &tile_width, &tile_height);

	वापस fb->pitches[color_plane] * tile_height;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_cursor_alignment(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	अगर (IS_I830(i915))
		वापस 16 * 1024;
	अन्यथा अगर (IS_I85X(i915))
		वापस 256;
	अन्यथा अगर (IS_I845G(i915) || IS_I865G(i915))
		वापस 32;
	अन्यथा
		वापस 4 * 1024;
पूर्ण

व्योम पूर्णांकel_fb_plane_get_subsampling(पूर्णांक *hsub, पूर्णांक *vsub,
				    स्थिर काष्ठा drm_framebuffer *fb,
				    पूर्णांक color_plane)
अणु
	पूर्णांक मुख्य_plane;

	अगर (color_plane == 0) अणु
		*hsub = 1;
		*vsub = 1;

		वापस;
	पूर्ण

	/*
	 * TODO: Deduct the subsampling from the अक्षर block क्रम all CCS
	 * क्रमmats and planes.
	 */
	अगर (!is_gen12_ccs_plane(fb, color_plane)) अणु
		*hsub = fb->क्रमmat->hsub;
		*vsub = fb->क्रमmat->vsub;

		वापस;
	पूर्ण

	मुख्य_plane = skl_ccs_to_मुख्य_plane(fb, color_plane);
	*hsub = drm_क्रमmat_info_block_width(fb->क्रमmat, color_plane) /
		drm_क्रमmat_info_block_width(fb->क्रमmat, मुख्य_plane);

	/*
	 * The min stride check in the core framebuffer_check() function
	 * assumes that क्रमmat->hsub applies to every plane except क्रम the
	 * first plane. That's incorrect क्रम the CCS AUX plane of the first
	 * plane, but क्रम the above check to pass we must define the block
	 * width with that subsampling applied to it. Adjust the width here
	 * accordingly, so we can calculate the actual subsampling factor.
	 */
	अगर (मुख्य_plane == 0)
		*hsub *= fb->क्रमmat->hsub;

	*vsub = 32;
पूर्ण

अटल व्योम पूर्णांकel_fb_plane_dims(पूर्णांक *w, पूर्णांक *h, काष्ठा drm_framebuffer *fb, पूर्णांक color_plane)
अणु
	पूर्णांक मुख्य_plane = is_ccs_plane(fb, color_plane) ?
			 skl_ccs_to_मुख्य_plane(fb, color_plane) : 0;
	पूर्णांक मुख्य_hsub, मुख्य_vsub;
	पूर्णांक hsub, vsub;

	पूर्णांकel_fb_plane_get_subsampling(&मुख्य_hsub, &मुख्य_vsub, fb, मुख्य_plane);
	पूर्णांकel_fb_plane_get_subsampling(&hsub, &vsub, fb, color_plane);
	*w = fb->width / मुख्य_hsub / hsub;
	*h = fb->height / मुख्य_vsub / vsub;
पूर्ण

अटल u32 पूर्णांकel_adjust_tile_offset(पूर्णांक *x, पूर्णांक *y,
				    अचिन्हित पूर्णांक tile_width,
				    अचिन्हित पूर्णांक tile_height,
				    अचिन्हित पूर्णांक tile_size,
				    अचिन्हित पूर्णांक pitch_tiles,
				    u32 old_offset,
				    u32 new_offset)
अणु
	अचिन्हित पूर्णांक pitch_pixels = pitch_tiles * tile_width;
	अचिन्हित पूर्णांक tiles;

	WARN_ON(old_offset & (tile_size - 1));
	WARN_ON(new_offset & (tile_size - 1));
	WARN_ON(new_offset > old_offset);

	tiles = (old_offset - new_offset) / tile_size;

	*y += tiles / pitch_tiles * tile_height;
	*x += tiles % pitch_tiles * tile_width;

	/* minimize x in हाल it got needlessly big */
	*y += *x / pitch_pixels * tile_height;
	*x %= pitch_pixels;

	वापस new_offset;
पूर्ण

अटल u32 पूर्णांकel_adjust_aligned_offset(पूर्णांक *x, पूर्णांक *y,
				       स्थिर काष्ठा drm_framebuffer *fb,
				       पूर्णांक color_plane,
				       अचिन्हित पूर्णांक rotation,
				       अचिन्हित पूर्णांक pitch,
				       u32 old_offset, u32 new_offset)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(fb->dev);
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[color_plane];

	drm_WARN_ON(&i915->drm, new_offset > old_offset);

	अगर (!is_surface_linear(fb, color_plane)) अणु
		अचिन्हित पूर्णांक tile_size, tile_width, tile_height;
		अचिन्हित पूर्णांक pitch_tiles;

		tile_size = पूर्णांकel_tile_size(i915);
		पूर्णांकel_tile_dims(fb, color_plane, &tile_width, &tile_height);

		अगर (drm_rotation_90_or_270(rotation)) अणु
			pitch_tiles = pitch / tile_height;
			swap(tile_width, tile_height);
		पूर्ण अन्यथा अणु
			pitch_tiles = pitch / (tile_width * cpp);
		पूर्ण

		पूर्णांकel_adjust_tile_offset(x, y, tile_width, tile_height,
					 tile_size, pitch_tiles,
					 old_offset, new_offset);
	पूर्ण अन्यथा अणु
		old_offset += *y * pitch + *x * cpp;

		*y = (old_offset - new_offset) / pitch;
		*x = ((old_offset - new_offset) - *y * pitch) / cpp;
	पूर्ण

	वापस new_offset;
पूर्ण

/*
 * Adjust the tile offset by moving the dअगरference पूर्णांकo
 * the x/y offsets.
 */
u32 पूर्णांकel_plane_adjust_aligned_offset(पूर्णांक *x, पूर्णांक *y,
				      स्थिर काष्ठा पूर्णांकel_plane_state *state,
				      पूर्णांक color_plane,
				      u32 old_offset, u32 new_offset)
अणु
	वापस पूर्णांकel_adjust_aligned_offset(x, y, state->hw.fb, color_plane,
					   state->hw.rotation,
					   state->view.color_plane[color_plane].stride,
					   old_offset, new_offset);
पूर्ण

/*
 * Computes the aligned offset to the base tile and adjusts
 * x, y. bytes per pixel is assumed to be a घातer-of-two.
 *
 * In the 90/270 rotated हाल, x and y are assumed
 * to be alपढ़ोy rotated to match the rotated GTT view, and
 * pitch is the tile_height aligned framebuffer height.
 *
 * This function is used when computing the derived inक्रमmation
 * under पूर्णांकel_framebuffer, so using any of that inक्रमmation
 * here is not allowed. Anything under drm_framebuffer can be
 * used. This is why the user has to pass in the pitch since it
 * is specअगरied in the rotated orientation.
 */
अटल u32 पूर्णांकel_compute_aligned_offset(काष्ठा drm_i915_निजी *i915,
					पूर्णांक *x, पूर्णांक *y,
					स्थिर काष्ठा drm_framebuffer *fb,
					पूर्णांक color_plane,
					अचिन्हित पूर्णांक pitch,
					अचिन्हित पूर्णांक rotation,
					u32 alignment)
अणु
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[color_plane];
	u32 offset, offset_aligned;

	अगर (!is_surface_linear(fb, color_plane)) अणु
		अचिन्हित पूर्णांक tile_size, tile_width, tile_height;
		अचिन्हित पूर्णांक tile_rows, tiles, pitch_tiles;

		tile_size = पूर्णांकel_tile_size(i915);
		पूर्णांकel_tile_dims(fb, color_plane, &tile_width, &tile_height);

		अगर (drm_rotation_90_or_270(rotation)) अणु
			pitch_tiles = pitch / tile_height;
			swap(tile_width, tile_height);
		पूर्ण अन्यथा अणु
			pitch_tiles = pitch / (tile_width * cpp);
		पूर्ण

		tile_rows = *y / tile_height;
		*y %= tile_height;

		tiles = *x / tile_width;
		*x %= tile_width;

		offset = (tile_rows * pitch_tiles + tiles) * tile_size;

		offset_aligned = offset;
		अगर (alignment)
			offset_aligned = roundकरोwn(offset_aligned, alignment);

		पूर्णांकel_adjust_tile_offset(x, y, tile_width, tile_height,
					 tile_size, pitch_tiles,
					 offset, offset_aligned);
	पूर्ण अन्यथा अणु
		offset = *y * pitch + *x * cpp;
		offset_aligned = offset;
		अगर (alignment) अणु
			offset_aligned = roundकरोwn(offset_aligned, alignment);
			*y = (offset % alignment) / pitch;
			*x = ((offset % alignment) - *y * pitch) / cpp;
		पूर्ण अन्यथा अणु
			*y = *x = 0;
		पूर्ण
	पूर्ण

	वापस offset_aligned;
पूर्ण

u32 पूर्णांकel_plane_compute_aligned_offset(पूर्णांक *x, पूर्णांक *y,
				       स्थिर काष्ठा पूर्णांकel_plane_state *state,
				       पूर्णांक color_plane)
अणु
	काष्ठा पूर्णांकel_plane *पूर्णांकel_plane = to_पूर्णांकel_plane(state->uapi.plane);
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = state->hw.fb;
	अचिन्हित पूर्णांक rotation = state->hw.rotation;
	पूर्णांक pitch = state->view.color_plane[color_plane].stride;
	u32 alignment;

	अगर (पूर्णांकel_plane->id == PLANE_CURSOR)
		alignment = पूर्णांकel_cursor_alignment(i915);
	अन्यथा
		alignment = पूर्णांकel_surf_alignment(fb, color_plane);

	वापस पूर्णांकel_compute_aligned_offset(i915, x, y, fb, color_plane,
					    pitch, rotation, alignment);
पूर्ण

/* Convert the fb->offset[] पूर्णांकo x/y offsets */
अटल पूर्णांक पूर्णांकel_fb_offset_to_xy(पूर्णांक *x, पूर्णांक *y,
				 स्थिर काष्ठा drm_framebuffer *fb,
				 पूर्णांक color_plane)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(fb->dev);
	अचिन्हित पूर्णांक height;
	u32 alignment;

	अगर (DISPLAY_VER(i915) >= 12 &&
	    is_semiplanar_uv_plane(fb, color_plane))
		alignment = पूर्णांकel_tile_row_size(fb, color_plane);
	अन्यथा अगर (fb->modअगरier != DRM_FORMAT_MOD_LINEAR)
		alignment = पूर्णांकel_tile_size(i915);
	अन्यथा
		alignment = 0;

	अगर (alignment != 0 && fb->offsets[color_plane] % alignment) अणु
		drm_dbg_kms(&i915->drm,
			    "Misaligned offset 0x%08x for color plane %d\n",
			    fb->offsets[color_plane], color_plane);
		वापस -EINVAL;
	पूर्ण

	height = drm_framebuffer_plane_height(fb->height, fb, color_plane);
	height = ALIGN(height, पूर्णांकel_tile_height(fb, color_plane));

	/* Catch potential overflows early */
	अगर (add_overflows_t(u32, mul_u32_u32(height, fb->pitches[color_plane]),
			    fb->offsets[color_plane])) अणु
		drm_dbg_kms(&i915->drm,
			    "Bad offset 0x%08x or pitch %d for color plane %d\n",
			    fb->offsets[color_plane], fb->pitches[color_plane],
			    color_plane);
		वापस -दुस्फल;
	पूर्ण

	*x = 0;
	*y = 0;

	पूर्णांकel_adjust_aligned_offset(x, y,
				    fb, color_plane, DRM_MODE_ROTATE_0,
				    fb->pitches[color_plane],
				    fb->offsets[color_plane], 0);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_fb_check_ccs_xy(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक ccs_plane, पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(fb->dev);
	स्थिर काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb = to_पूर्णांकel_framebuffer(fb);
	पूर्णांक मुख्य_plane;
	पूर्णांक hsub, vsub;
	पूर्णांक tile_width, tile_height;
	पूर्णांक ccs_x, ccs_y;
	पूर्णांक मुख्य_x, मुख्य_y;

	अगर (!is_ccs_plane(fb, ccs_plane) || is_gen12_ccs_cc_plane(fb, ccs_plane))
		वापस 0;

	पूर्णांकel_tile_dims(fb, ccs_plane, &tile_width, &tile_height);
	पूर्णांकel_fb_plane_get_subsampling(&hsub, &vsub, fb, ccs_plane);

	tile_width *= hsub;
	tile_height *= vsub;

	ccs_x = (x * hsub) % tile_width;
	ccs_y = (y * vsub) % tile_height;

	मुख्य_plane = skl_ccs_to_मुख्य_plane(fb, ccs_plane);
	मुख्य_x = पूर्णांकel_fb->normal_view.color_plane[मुख्य_plane].x % tile_width;
	मुख्य_y = पूर्णांकel_fb->normal_view.color_plane[मुख्य_plane].y % tile_height;

	/*
	 * CCS करोesn't have its own x/y offset रेजिस्टर, so the पूर्णांकra CCS tile
	 * x/y offsets must match between CCS and the मुख्य surface.
	 */
	अगर (मुख्य_x != ccs_x || मुख्य_y != ccs_y) अणु
		drm_dbg_kms(&i915->drm,
			      "Bad CCS x/y (main %d,%d ccs %d,%d) full (main %d,%d ccs %d,%d)\n",
			      मुख्य_x, मुख्य_y,
			      ccs_x, ccs_y,
			      पूर्णांकel_fb->normal_view.color_plane[मुख्य_plane].x,
			      पूर्णांकel_fb->normal_view.color_plane[मुख्य_plane].y,
			      x, y);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool पूर्णांकel_plane_can_remap(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	पूर्णांक i;

	/* We करोn't want to deal with remapping with cursors */
	अगर (plane->id == PLANE_CURSOR)
		वापस false;

	/*
	 * The display engine limits alपढ़ोy match/exceed the
	 * render engine limits, so not much poपूर्णांक in remapping.
	 * Would also need to deal with the fence POT alignment
	 * and gen2 2KiB GTT tile size.
	 */
	अगर (DISPLAY_VER(i915) < 4)
		वापस false;

	/*
	 * The new CCS hash mode isn't compatible with remapping as
	 * the भव address of the pages affects the compressed data.
	 */
	अगर (is_ccs_modअगरier(fb->modअगरier))
		वापस false;

	/* Linear needs a page aligned stride क्रम remapping */
	अगर (fb->modअगरier == DRM_FORMAT_MOD_LINEAR) अणु
		अचिन्हित पूर्णांक alignment = पूर्णांकel_tile_size(i915) - 1;

		क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
			अगर (fb->pitches[i] & alignment)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool पूर्णांकel_fb_needs_pot_stride_remap(स्थिर काष्ठा पूर्णांकel_framebuffer *fb)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_fb_pitch(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane, अचिन्हित पूर्णांक rotation)
अणु
	अगर (drm_rotation_90_or_270(rotation))
		वापस fb->rotated_view.color_plane[color_plane].stride;
	अन्यथा अगर (पूर्णांकel_fb_needs_pot_stride_remap(fb))
		वापस fb->remapped_view.color_plane[color_plane].stride;
	अन्यथा
		वापस fb->normal_view.color_plane[color_plane].stride;
पूर्ण

अटल bool पूर्णांकel_plane_needs_remap(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	स्थिर काष्ठा पूर्णांकel_framebuffer *fb = to_पूर्णांकel_framebuffer(plane_state->hw.fb);
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	u32 stride, max_stride;

	/*
	 * No remapping क्रम invisible planes since we करोn't have
	 * an actual source viewport to remap.
	 */
	अगर (!plane_state->uapi.visible)
		वापस false;

	अगर (!पूर्णांकel_plane_can_remap(plane_state))
		वापस false;

	/*
	 * FIXME: aux plane limits on gen9+ are
	 * unclear in Bspec, क्रम now no checking.
	 */
	stride = पूर्णांकel_fb_pitch(fb, 0, rotation);
	max_stride = plane->max_stride(plane, fb->base.क्रमmat->क्रमmat,
				       fb->base.modअगरier, rotation);

	वापस stride > max_stride;
पूर्ण

अटल पूर्णांक convert_plane_offset_to_xy(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
				      पूर्णांक plane_width, पूर्णांक *x, पूर्णांक *y)
अणु
	काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(&fb->base);
	पूर्णांक ret;

	ret = पूर्णांकel_fb_offset_to_xy(x, y, &fb->base, color_plane);
	अगर (ret) अणु
		drm_dbg_kms(fb->base.dev,
			    "bad fb plane %d offset: 0x%x\n",
			    color_plane, fb->base.offsets[color_plane]);
		वापस ret;
	पूर्ण

	ret = पूर्णांकel_fb_check_ccs_xy(&fb->base, color_plane, *x, *y);
	अगर (ret)
		वापस ret;

	/*
	 * The fence (अगर used) is aligned to the start of the object
	 * so having the framebuffer wrap around across the edge of the
	 * fenced region करोesn't really work. We have no API to configure
	 * the fence start offset within the object (nor could we probably
	 * on gen2/3). So it's just easier अगर we just require that the
	 * fb layout agrees with the fence layout. We alपढ़ोy check that the
	 * fb stride matches the fence stride अन्यथाwhere.
	 */
	अगर (color_plane == 0 && i915_gem_object_is_tiled(obj) &&
	    (*x + plane_width) * fb->base.क्रमmat->cpp[color_plane] > fb->base.pitches[color_plane]) अणु
		drm_dbg_kms(fb->base.dev,
			    "bad fb plane %d offset: 0x%x\n",
			    color_plane, fb->base.offsets[color_plane]);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 calc_plane_aligned_offset(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane, पूर्णांक *x, पूर्णांक *y)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(fb->base.dev);
	अचिन्हित पूर्णांक tile_size = पूर्णांकel_tile_size(i915);
	u32 offset;

	offset = पूर्णांकel_compute_aligned_offset(i915, x, y, &fb->base, color_plane,
					      fb->base.pitches[color_plane],
					      DRM_MODE_ROTATE_0,
					      tile_size);

	वापस offset / tile_size;
पूर्ण

काष्ठा fb_plane_view_dims अणु
	अचिन्हित पूर्णांक width, height;
	अचिन्हित पूर्णांक tile_width, tile_height;
पूर्ण;

अटल व्योम init_plane_view_dims(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
				 अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
				 काष्ठा fb_plane_view_dims *dims)
अणु
	dims->width = width;
	dims->height = height;

	पूर्णांकel_tile_dims(&fb->base, color_plane, &dims->tile_width, &dims->tile_height);
पूर्ण

अटल अचिन्हित पूर्णांक
plane_view_src_stride_tiles(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
			    स्थिर काष्ठा fb_plane_view_dims *dims)
अणु
	वापस DIV_ROUND_UP(fb->base.pitches[color_plane],
			    dims->tile_width * fb->base.क्रमmat->cpp[color_plane]);
पूर्ण

अटल अचिन्हित पूर्णांक
plane_view_dst_stride_tiles(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
			    अचिन्हित पूर्णांक pitch_tiles)
अणु
	अगर (पूर्णांकel_fb_needs_pot_stride_remap(fb))
		वापस roundup_घात_of_two(pitch_tiles);
	अन्यथा
		वापस pitch_tiles;
पूर्ण

अटल अचिन्हित पूर्णांक
plane_view_width_tiles(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
		       स्थिर काष्ठा fb_plane_view_dims *dims,
		       पूर्णांक x)
अणु
	वापस DIV_ROUND_UP(x + dims->width, dims->tile_width);
पूर्ण

अटल अचिन्हित पूर्णांक
plane_view_height_tiles(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
			स्थिर काष्ठा fb_plane_view_dims *dims,
			पूर्णांक y)
अणु
	वापस DIV_ROUND_UP(y + dims->height, dims->tile_height);
पूर्ण

#घोषणा assign_chk_ovf(i915, var, val) (अणु \
	drm_WARN_ON(&(i915)->drm, overflows_type(val, var)); \
	(var) = (val); \
पूर्ण)

अटल u32 calc_plane_remap_info(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
				 स्थिर काष्ठा fb_plane_view_dims *dims,
				 u32 obj_offset, u32 gtt_offset, पूर्णांक x, पूर्णांक y,
				 काष्ठा पूर्णांकel_fb_view *view)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(fb->base.dev);
	काष्ठा पूर्णांकel_remapped_plane_info *remap_info = &view->gtt.remapped.plane[color_plane];
	काष्ठा i915_color_plane_view *color_plane_info = &view->color_plane[color_plane];
	अचिन्हित पूर्णांक tile_width = dims->tile_width;
	अचिन्हित पूर्णांक tile_height = dims->tile_height;
	अचिन्हित पूर्णांक tile_size = पूर्णांकel_tile_size(i915);
	काष्ठा drm_rect r;
	u32 size;

	assign_chk_ovf(i915, remap_info->offset, obj_offset);
	assign_chk_ovf(i915, remap_info->src_stride, plane_view_src_stride_tiles(fb, color_plane, dims));
	assign_chk_ovf(i915, remap_info->width, plane_view_width_tiles(fb, color_plane, dims, x));
	assign_chk_ovf(i915, remap_info->height, plane_view_height_tiles(fb, color_plane, dims, y));

	अगर (view->gtt.type == I915_GGTT_VIEW_ROTATED) अणु
		check_array_bounds(i915, view->gtt.rotated.plane, color_plane);

		assign_chk_ovf(i915, remap_info->dst_stride,
			       plane_view_dst_stride_tiles(fb, color_plane, remap_info->height));

		/* rotate the x/y offsets to match the GTT view */
		drm_rect_init(&r, x, y, dims->width, dims->height);
		drm_rect_rotate(&r,
				remap_info->width * tile_width,
				remap_info->height * tile_height,
				DRM_MODE_ROTATE_270);

		color_plane_info->x = r.x1;
		color_plane_info->y = r.y1;

		color_plane_info->stride = remap_info->dst_stride * tile_height;

		size = remap_info->dst_stride * remap_info->width;

		/* rotate the tile dimensions to match the GTT view */
		swap(tile_width, tile_height);
	पूर्ण अन्यथा अणु
		drm_WARN_ON(&i915->drm, view->gtt.type != I915_GGTT_VIEW_REMAPPED);

		check_array_bounds(i915, view->gtt.remapped.plane, color_plane);

		assign_chk_ovf(i915, remap_info->dst_stride,
			       plane_view_dst_stride_tiles(fb, color_plane, remap_info->width));

		color_plane_info->x = x;
		color_plane_info->y = y;

		color_plane_info->stride = remap_info->dst_stride * tile_width *
					   fb->base.क्रमmat->cpp[color_plane];

		size = remap_info->dst_stride * remap_info->height;
	पूर्ण

	/*
	 * We only keep the x/y offsets, so push all of the gtt offset पूर्णांकo
	 * the x/y offsets.  x,y will hold the first pixel of the framebuffer
	 * plane from the start of the remapped/rotated gtt mapping.
	 */
	पूर्णांकel_adjust_tile_offset(&color_plane_info->x, &color_plane_info->y,
				 tile_width, tile_height,
				 tile_size, remap_info->dst_stride,
				 gtt_offset * tile_size, 0);

	वापस size;
पूर्ण

#अघोषित assign_chk_ovf

/* Return number of tiles @color_plane needs. */
अटल अचिन्हित पूर्णांक
calc_plane_normal_size(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, पूर्णांक color_plane,
		       स्थिर काष्ठा fb_plane_view_dims *dims,
		       पूर्णांक x, पूर्णांक y)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(fb->base.dev);
	अचिन्हित पूर्णांक tiles;

	अगर (is_surface_linear(&fb->base, color_plane)) अणु
		अचिन्हित पूर्णांक size;

		size = (y + dims->height) * fb->base.pitches[color_plane] +
		       x * fb->base.क्रमmat->cpp[color_plane];
		tiles = DIV_ROUND_UP(size, पूर्णांकel_tile_size(i915));
	पूर्ण अन्यथा अणु
		tiles = plane_view_src_stride_tiles(fb, color_plane, dims) *
			plane_view_height_tiles(fb, color_plane, dims, y);
		/*
		 * If the plane isn't horizontally tile aligned,
		 * we need one more tile.
		 */
		अगर (x != 0)
			tiles++;
	पूर्ण

	वापस tiles;
पूर्ण

अटल व्योम पूर्णांकel_fb_view_init(काष्ठा पूर्णांकel_fb_view *view, क्रमागत i915_ggtt_view_type view_type)
अणु
	स_रखो(view, 0, माप(*view));
	view->gtt.type = view_type;
पूर्ण

पूर्णांक पूर्णांकel_fill_fb_info(काष्ठा drm_i915_निजी *i915, काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb = to_पूर्णांकel_framebuffer(fb);
	काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(fb);
	u32 gtt_offset_rotated = 0;
	u32 gtt_offset_remapped = 0;
	अचिन्हित पूर्णांक max_size = 0;
	पूर्णांक i, num_planes = fb->क्रमmat->num_planes;
	अचिन्हित पूर्णांक tile_size = पूर्णांकel_tile_size(i915);

	पूर्णांकel_fb_view_init(&पूर्णांकel_fb->normal_view, I915_GGTT_VIEW_NORMAL);
	पूर्णांकel_fb_view_init(&पूर्णांकel_fb->rotated_view, I915_GGTT_VIEW_ROTATED);
	पूर्णांकel_fb_view_init(&पूर्णांकel_fb->remapped_view, I915_GGTT_VIEW_REMAPPED);

	क्रम (i = 0; i < num_planes; i++) अणु
		काष्ठा fb_plane_view_dims view_dims;
		अचिन्हित पूर्णांक width, height;
		अचिन्हित पूर्णांक cpp, size;
		u32 offset;
		पूर्णांक x, y;
		पूर्णांक ret;

		/*
		 * Plane 2 of Render Compression with Clear Color fb modअगरier
		 * is consumed by the driver and not passed to DE. Skip the
		 * arithmetic related to alignment and offset calculation.
		 */
		अगर (is_gen12_ccs_cc_plane(fb, i)) अणु
			अगर (IS_ALIGNED(fb->offsets[i], PAGE_SIZE))
				जारी;
			अन्यथा
				वापस -EINVAL;
		पूर्ण

		cpp = fb->क्रमmat->cpp[i];
		पूर्णांकel_fb_plane_dims(&width, &height, fb, i);

		ret = convert_plane_offset_to_xy(पूर्णांकel_fb, i, width, &x, &y);
		अगर (ret)
			वापस ret;

		init_plane_view_dims(पूर्णांकel_fb, i, width, height, &view_dims);

		/*
		 * First pixel of the framebuffer from
		 * the start of the normal gtt mapping.
		 */
		पूर्णांकel_fb->normal_view.color_plane[i].x = x;
		पूर्णांकel_fb->normal_view.color_plane[i].y = y;
		पूर्णांकel_fb->normal_view.color_plane[i].stride = पूर्णांकel_fb->base.pitches[i];

		offset = calc_plane_aligned_offset(पूर्णांकel_fb, i, &x, &y);

		/* Y or Yf modअगरiers required क्रम 90/270 rotation */
		अगर (fb->modअगरier == I915_FORMAT_MOD_Y_TILED ||
		    fb->modअगरier == I915_FORMAT_MOD_Yf_TILED)
			gtt_offset_rotated += calc_plane_remap_info(पूर्णांकel_fb, i, &view_dims,
								    offset, gtt_offset_rotated, x, y,
								    &पूर्णांकel_fb->rotated_view);

		अगर (पूर्णांकel_fb_needs_pot_stride_remap(पूर्णांकel_fb))
			gtt_offset_remapped += calc_plane_remap_info(पूर्णांकel_fb, i, &view_dims,
								     offset, gtt_offset_remapped, x, y,
								     &पूर्णांकel_fb->remapped_view);

		size = calc_plane_normal_size(पूर्णांकel_fb, i, &view_dims, x, y);
		/* how many tiles in total needed in the bo */
		max_size = max(max_size, offset + size);
	पूर्ण

	अगर (mul_u32_u32(max_size, tile_size) > obj->base.size) अणु
		drm_dbg_kms(&i915->drm,
			    "fb too big for bo (need %llu bytes, have %zu bytes)\n",
			    mul_u32_u32(max_size, tile_size), obj->base.size);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_plane_remap_gtt(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा drm_i915_निजी *i915 =
		to_i915(plane_state->uapi.plane->dev);
	काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb = to_पूर्णांकel_framebuffer(fb);
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	पूर्णांक i, num_planes = fb->क्रमmat->num_planes;
	अचिन्हित पूर्णांक src_x, src_y;
	अचिन्हित पूर्णांक src_w, src_h;
	u32 gtt_offset = 0;

	पूर्णांकel_fb_view_init(&plane_state->view,
			   drm_rotation_90_or_270(rotation) ? I915_GGTT_VIEW_ROTATED :
							      I915_GGTT_VIEW_REMAPPED);

	src_x = plane_state->uapi.src.x1 >> 16;
	src_y = plane_state->uapi.src.y1 >> 16;
	src_w = drm_rect_width(&plane_state->uapi.src) >> 16;
	src_h = drm_rect_height(&plane_state->uapi.src) >> 16;

	drm_WARN_ON(&i915->drm, is_ccs_modअगरier(fb->modअगरier));

	/* Make src coordinates relative to the viewport */
	drm_rect_translate(&plane_state->uapi.src,
			   -(src_x << 16), -(src_y << 16));

	/* Rotate src coordinates to match rotated GTT view */
	अगर (drm_rotation_90_or_270(rotation))
		drm_rect_rotate(&plane_state->uapi.src,
				src_w << 16, src_h << 16,
				DRM_MODE_ROTATE_270);

	क्रम (i = 0; i < num_planes; i++) अणु
		अचिन्हित पूर्णांक hsub = i ? fb->क्रमmat->hsub : 1;
		अचिन्हित पूर्णांक vsub = i ? fb->क्रमmat->vsub : 1;
		काष्ठा fb_plane_view_dims view_dims;
		अचिन्हित पूर्णांक width, height;
		अचिन्हित पूर्णांक x, y;
		u32 offset;

		x = src_x / hsub;
		y = src_y / vsub;
		width = src_w / hsub;
		height = src_h / vsub;

		init_plane_view_dims(पूर्णांकel_fb, i, width, height, &view_dims);

		/*
		 * First pixel of the src viewport from the
		 * start of the normal gtt mapping.
		 */
		x += पूर्णांकel_fb->normal_view.color_plane[i].x;
		y += पूर्णांकel_fb->normal_view.color_plane[i].y;

		offset = calc_plane_aligned_offset(पूर्णांकel_fb, i, &x, &y);

		gtt_offset += calc_plane_remap_info(पूर्णांकel_fb, i, &view_dims,
						    offset, gtt_offset, x, y,
						    &plane_state->view);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_fb_fill_view(स्थिर काष्ठा पूर्णांकel_framebuffer *fb, अचिन्हित पूर्णांक rotation,
			काष्ठा पूर्णांकel_fb_view *view)
अणु
	अगर (drm_rotation_90_or_270(rotation))
		*view = fb->rotated_view;
	अन्यथा अगर (पूर्णांकel_fb_needs_pot_stride_remap(fb))
		*view = fb->remapped_view;
	अन्यथा
		*view = fb->normal_view;
पूर्ण

अटल पूर्णांक पूर्णांकel_plane_check_stride(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;
	u32 stride, max_stride;

	/*
	 * We ignore stride क्रम all invisible planes that
	 * can be remapped. Otherwise we could end up
	 * with a false positive when the remapping didn't
	 * kick in due the plane being invisible.
	 */
	अगर (पूर्णांकel_plane_can_remap(plane_state) &&
	    !plane_state->uapi.visible)
		वापस 0;

	/* FIXME other color planes? */
	stride = plane_state->view.color_plane[0].stride;
	max_stride = plane->max_stride(plane, fb->क्रमmat->क्रमmat,
				       fb->modअगरier, rotation);

	अगर (stride > max_stride) अणु
		DRM_DEBUG_KMS("[FB:%d] stride (%d) exceeds [PLANE:%d:%s] max stride (%d)\n",
			      fb->base.id, stride,
			      plane->base.base.id, plane->base.name, max_stride);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_plane_compute_gtt(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	स्थिर काष्ठा पूर्णांकel_framebuffer *fb =
		to_पूर्णांकel_framebuffer(plane_state->hw.fb);
	अचिन्हित पूर्णांक rotation = plane_state->hw.rotation;

	अगर (!fb)
		वापस 0;

	अगर (पूर्णांकel_plane_needs_remap(plane_state)) अणु
		पूर्णांकel_plane_remap_gtt(plane_state);

		/*
		 * Someबार even remapping can't overcome
		 * the stride limitations :( Can happen with
		 * big plane sizes and suitably misaligned
		 * offsets.
		 */
		वापस पूर्णांकel_plane_check_stride(plane_state);
	पूर्ण

	पूर्णांकel_fb_fill_view(fb, rotation, &plane_state->view);

	/* Rotate src coordinates to match rotated GTT view */
	अगर (drm_rotation_90_or_270(rotation))
		drm_rect_rotate(&plane_state->uapi.src,
				fb->base.width << 16, fb->base.height << 16,
				DRM_MODE_ROTATE_270);

	वापस पूर्णांकel_plane_check_stride(plane_state);
पूर्ण
