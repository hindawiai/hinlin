<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Texas Instruments
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_fourcc.h>

#समावेश "tilcdc_drv.h"

अटल स्थिर काष्ठा drm_plane_funcs tilcdc_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy	= drm_plane_cleanup,
	.reset		= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल पूर्णांक tilcdc_plane_atomic_check(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state,
									   plane);
	अचिन्हित पूर्णांक pitch;

	अगर (!new_state->crtc)
		वापस 0;

	अगर (WARN_ON(!new_state->fb))
		वापस -EINVAL;

	अगर (new_state->crtc_x || new_state->crtc_y) अणु
		dev_err(plane->dev->dev, "%s: crtc position must be zero.",
			__func__);
		वापस -EINVAL;
	पूर्ण

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							new_state->crtc);
	/* we should have a crtc state अगर the plane is attached to a crtc */
	अगर (WARN_ON(!crtc_state))
		वापस 0;

	अगर (crtc_state->mode.hdisplay != new_state->crtc_w ||
	    crtc_state->mode.vdisplay != new_state->crtc_h) अणु
		dev_err(plane->dev->dev,
			"%s: Size must match mode (%dx%d == %dx%d)", __func__,
			crtc_state->mode.hdisplay, crtc_state->mode.vdisplay,
			new_state->crtc_w, new_state->crtc_h);
		वापस -EINVAL;
	पूर्ण

	pitch = crtc_state->mode.hdisplay *
		new_state->fb->क्रमmat->cpp[0];
	अगर (new_state->fb->pitches[0] != pitch) अणु
		dev_err(plane->dev->dev,
			"Invalid pitch: fb and crtc widths must be the same");
		वापस -EINVAL;
	पूर्ण

	अगर (old_state->fb && new_state->fb->क्रमmat != old_state->fb->क्रमmat) अणु
		dev_dbg(plane->dev->dev,
			"%s(): pixel format change requires mode_change\n",
			__func__);
		crtc_state->mode_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tilcdc_plane_atomic_update(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);

	अगर (!new_state->crtc)
		वापस;

	अगर (WARN_ON(!new_state->fb || !new_state->crtc->state))
		वापस;

	अगर (tilcdc_crtc_update_fb(new_state->crtc,
				  new_state->fb,
				  new_state->crtc->state->event) == 0) अणु
		new_state->crtc->state->event = शून्य;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs plane_helper_funcs = अणु
	.atomic_check = tilcdc_plane_atomic_check,
	.atomic_update = tilcdc_plane_atomic_update,
पूर्ण;

पूर्णांक tilcdc_plane_init(काष्ठा drm_device *dev,
		      काष्ठा drm_plane *plane)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	पूर्णांक ret;

	ret = drm_plane_init(dev, plane, 1,
			     &tilcdc_plane_funcs,
			     priv->pixelक्रमmats,
			     priv->num_pixelक्रमmats,
			     true);
	अगर (ret) अणु
		dev_err(dev->dev, "Failed to initialize plane: %d\n", ret);
		वापस ret;
	पूर्ण

	drm_plane_helper_add(plane, &plane_helper_funcs);

	वापस 0;
पूर्ण
