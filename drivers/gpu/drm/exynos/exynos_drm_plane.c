<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Authors: Joonyoung Shim <jy0922.shim@samsung.com>
 */


#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_gem.h"
#समावेश "exynos_drm_plane.h"

/*
 * This function is to get X or Y size shown via screen. This needs length and
 * start position of CRTC.
 *
 *      <--- length --->
 * CRTC ----------------
 *      ^ start        ^ end
 *
 * There are six हालs from a to f.
 *
 *             <----- SCREEN ----->
 *             0                 last
 *   ----------|------------------|----------
 * CRTCs
 * a -------
 *        b -------
 *        c --------------------------
 *                 d --------
 *                           e -------
 *                                  f -------
 */
अटल पूर्णांक exynos_plane_get_size(पूर्णांक start, अचिन्हित length, अचिन्हित last)
अणु
	पूर्णांक end = start + length;
	पूर्णांक size = 0;

	अगर (start <= 0) अणु
		अगर (end > 0)
			size = min_t(अचिन्हित, end, last);
	पूर्ण अन्यथा अगर (start <= last) अणु
		size = min_t(अचिन्हित, last - start, length);
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम exynos_plane_mode_set(काष्ठा exynos_drm_plane_state *exynos_state)
अणु
	काष्ठा drm_plane_state *state = &exynos_state->base;
	काष्ठा drm_crtc *crtc = state->crtc;
	काष्ठा drm_crtc_state *crtc_state =
			drm_atomic_get_existing_crtc_state(state->state, crtc);
	काष्ठा drm_display_mode *mode = &crtc_state->adjusted_mode;
	पूर्णांक crtc_x, crtc_y;
	अचिन्हित पूर्णांक crtc_w, crtc_h;
	अचिन्हित पूर्णांक src_x, src_y;
	अचिन्हित पूर्णांक src_w, src_h;
	अचिन्हित पूर्णांक actual_w;
	अचिन्हित पूर्णांक actual_h;

	/*
	 * The original src/dest coordinates are stored in exynos_state->base,
	 * but we want to keep another copy पूर्णांकernal to our driver that we can
	 * clip/modअगरy ourselves.
	 */

	crtc_x = state->crtc_x;
	crtc_y = state->crtc_y;
	crtc_w = state->crtc_w;
	crtc_h = state->crtc_h;

	src_x = state->src_x >> 16;
	src_y = state->src_y >> 16;
	src_w = state->src_w >> 16;
	src_h = state->src_h >> 16;

	/* set ratio */
	exynos_state->h_ratio = (src_w << 16) / crtc_w;
	exynos_state->v_ratio = (src_h << 16) / crtc_h;

	/* clip to visible area */
	actual_w = exynos_plane_get_size(crtc_x, crtc_w, mode->hdisplay);
	actual_h = exynos_plane_get_size(crtc_y, crtc_h, mode->vdisplay);

	अगर (crtc_x < 0) अणु
		अगर (actual_w)
			src_x += ((-crtc_x) * exynos_state->h_ratio) >> 16;
		crtc_x = 0;
	पूर्ण

	अगर (crtc_y < 0) अणु
		अगर (actual_h)
			src_y += ((-crtc_y) * exynos_state->v_ratio) >> 16;
		crtc_y = 0;
	पूर्ण

	/* set drm framebuffer data. */
	exynos_state->src.x = src_x;
	exynos_state->src.y = src_y;
	exynos_state->src.w = (actual_w * exynos_state->h_ratio) >> 16;
	exynos_state->src.h = (actual_h * exynos_state->v_ratio) >> 16;

	/* set plane range to be displayed. */
	exynos_state->crtc.x = crtc_x;
	exynos_state->crtc.y = crtc_y;
	exynos_state->crtc.w = actual_w;
	exynos_state->crtc.h = actual_h;

	DRM_DEV_DEBUG_KMS(crtc->dev->dev,
			  "plane : offset_x/y(%d,%d), width/height(%d,%d)",
			  exynos_state->crtc.x, exynos_state->crtc.y,
			  exynos_state->crtc.w, exynos_state->crtc.h);
पूर्ण

अटल व्योम exynos_drm_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा exynos_drm_plane *exynos_plane = to_exynos_plane(plane);
	काष्ठा exynos_drm_plane_state *exynos_state;

	अगर (plane->state) अणु
		exynos_state = to_exynos_plane_state(plane->state);
		__drm_atomic_helper_plane_destroy_state(plane->state);
		kमुक्त(exynos_state);
		plane->state = शून्य;
	पूर्ण

	exynos_state = kzalloc(माप(*exynos_state), GFP_KERNEL);
	अगर (exynos_state) अणु
		__drm_atomic_helper_plane_reset(plane, &exynos_state->base);
		plane->state->zpos = exynos_plane->config->zpos;
	पूर्ण
पूर्ण

अटल काष्ठा drm_plane_state *
exynos_drm_plane_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा exynos_drm_plane_state *exynos_state;
	काष्ठा exynos_drm_plane_state *copy;

	exynos_state = to_exynos_plane_state(plane->state);
	copy = kzalloc(माप(*exynos_state), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &copy->base);
	वापस &copy->base;
पूर्ण

अटल व्योम exynos_drm_plane_destroy_state(काष्ठा drm_plane *plane,
					   काष्ठा drm_plane_state *old_state)
अणु
	काष्ठा exynos_drm_plane_state *old_exynos_state =
					to_exynos_plane_state(old_state);
	__drm_atomic_helper_plane_destroy_state(old_state);
	kमुक्त(old_exynos_state);
पूर्ण

अटल काष्ठा drm_plane_funcs exynos_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_plane_cleanup,
	.reset		= exynos_drm_plane_reset,
	.atomic_duplicate_state = exynos_drm_plane_duplicate_state,
	.atomic_destroy_state = exynos_drm_plane_destroy_state,
पूर्ण;

अटल पूर्णांक
exynos_drm_plane_check_क्रमmat(स्थिर काष्ठा exynos_drm_plane_config *config,
			      काष्ठा exynos_drm_plane_state *state)
अणु
	काष्ठा drm_framebuffer *fb = state->base.fb;
	काष्ठा drm_device *dev = fb->dev;

	चयन (fb->modअगरier) अणु
	हाल DRM_FORMAT_MOD_SAMSUNG_64_32_TILE:
		अगर (!(config->capabilities & EXYNOS_DRM_PLANE_CAP_TILE))
			वापस -ENOTSUPP;
		अवरोध;

	हाल DRM_FORMAT_MOD_LINEAR:
		अवरोध;

	शेष:
		DRM_DEV_ERROR(dev->dev, "unsupported pixel format modifier");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
exynos_drm_plane_check_size(स्थिर काष्ठा exynos_drm_plane_config *config,
			    काष्ठा exynos_drm_plane_state *state)
अणु
	काष्ठा drm_crtc *crtc = state->base.crtc;
	bool width_ok = false, height_ok = false;

	अगर (config->capabilities & EXYNOS_DRM_PLANE_CAP_SCALE)
		वापस 0;

	अगर (state->src.w == state->crtc.w)
		width_ok = true;

	अगर (state->src.h == state->crtc.h)
		height_ok = true;

	अगर ((config->capabilities & EXYNOS_DRM_PLANE_CAP_DOUBLE) &&
	    state->h_ratio == (1 << 15))
		width_ok = true;

	अगर ((config->capabilities & EXYNOS_DRM_PLANE_CAP_DOUBLE) &&
	    state->v_ratio == (1 << 15))
		height_ok = true;

	अगर (width_ok && height_ok)
		वापस 0;

	DRM_DEV_DEBUG_KMS(crtc->dev->dev, "scaling mode is not supported");
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक exynos_plane_atomic_check(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा exynos_drm_plane *exynos_plane = to_exynos_plane(plane);
	काष्ठा exynos_drm_plane_state *exynos_state =
						to_exynos_plane_state(new_plane_state);
	पूर्णांक ret = 0;

	अगर (!new_plane_state->crtc || !new_plane_state->fb)
		वापस 0;

	/* translate state पूर्णांकo exynos_state */
	exynos_plane_mode_set(exynos_state);

	ret = exynos_drm_plane_check_क्रमmat(exynos_plane->config, exynos_state);
	अगर (ret)
		वापस ret;

	ret = exynos_drm_plane_check_size(exynos_plane->config, exynos_state);
	वापस ret;
पूर्ण

अटल व्योम exynos_plane_atomic_update(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
								           plane);
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(new_state->crtc);
	काष्ठा exynos_drm_plane *exynos_plane = to_exynos_plane(plane);

	अगर (!new_state->crtc)
		वापस;

	अगर (exynos_crtc->ops->update_plane)
		exynos_crtc->ops->update_plane(exynos_crtc, exynos_plane);
पूर्ण

अटल व्योम exynos_plane_atomic_disable(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state, plane);
	काष्ठा exynos_drm_plane *exynos_plane = to_exynos_plane(plane);
	काष्ठा exynos_drm_crtc *exynos_crtc = to_exynos_crtc(old_state->crtc);

	अगर (!old_state->crtc)
		वापस;

	अगर (exynos_crtc->ops->disable_plane)
		exynos_crtc->ops->disable_plane(exynos_crtc, exynos_plane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs plane_helper_funcs = अणु
	.atomic_check = exynos_plane_atomic_check,
	.atomic_update = exynos_plane_atomic_update,
	.atomic_disable = exynos_plane_atomic_disable,
पूर्ण;

अटल व्योम exynos_plane_attach_zpos_property(काष्ठा drm_plane *plane,
					      पूर्णांक zpos, bool immutable)
अणु
	अगर (immutable)
		drm_plane_create_zpos_immutable_property(plane, zpos);
	अन्यथा
		drm_plane_create_zpos_property(plane, zpos, 0, MAX_PLANE - 1);
पूर्ण

पूर्णांक exynos_plane_init(काष्ठा drm_device *dev,
		      काष्ठा exynos_drm_plane *exynos_plane, अचिन्हित पूर्णांक index,
		      स्थिर काष्ठा exynos_drm_plane_config *config)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक supported_modes = BIT(DRM_MODE_BLEND_PIXEL_NONE) |
				       BIT(DRM_MODE_BLEND_PREMULTI) |
				       BIT(DRM_MODE_BLEND_COVERAGE);
	काष्ठा drm_plane *plane = &exynos_plane->base;

	err = drm_universal_plane_init(dev, &exynos_plane->base,
				       1 << dev->mode_config.num_crtc,
				       &exynos_plane_funcs,
				       config->pixel_क्रमmats,
				       config->num_pixel_क्रमmats,
				       शून्य, config->type, शून्य);
	अगर (err) अणु
		DRM_DEV_ERROR(dev->dev, "failed to initialize plane\n");
		वापस err;
	पूर्ण

	drm_plane_helper_add(&exynos_plane->base, &plane_helper_funcs);

	exynos_plane->index = index;
	exynos_plane->config = config;

	exynos_plane_attach_zpos_property(&exynos_plane->base, config->zpos,
			   !(config->capabilities & EXYNOS_DRM_PLANE_CAP_ZPOS));

	अगर (config->capabilities & EXYNOS_DRM_PLANE_CAP_PIX_BLEND)
		drm_plane_create_blend_mode_property(plane, supported_modes);

	अगर (config->capabilities & EXYNOS_DRM_PLANE_CAP_WIN_BLEND)
		drm_plane_create_alpha_property(plane);

	वापस 0;
पूर्ण
