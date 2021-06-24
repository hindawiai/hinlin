<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_gem_atomic_helper.h>

#समावेश "tidss_crtc.h"
#समावेश "tidss_dispc.h"
#समावेश "tidss_drv.h"
#समावेश "tidss_plane.h"

/* drm_plane_helper_funcs */

अटल पूर्णांक tidss_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_device *ddev = plane->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	काष्ठा tidss_plane *tplane = to_tidss_plane(plane);
	स्थिर काष्ठा drm_क्रमmat_info *finfo;
	काष्ठा drm_crtc_state *crtc_state;
	u32 hw_plane = tplane->hw_plane_id;
	u32 hw_videoport;
	पूर्णांक ret;

	dev_dbg(ddev->dev, "%s\n", __func__);

	अगर (!new_plane_state->crtc) अणु
		/*
		 * The visible field is not reset by the DRM core but only
		 * updated by drm_plane_helper_check_state(), set it manually.
		 */
		new_plane_state->visible = false;
		वापस 0;
	पूर्ण

	crtc_state = drm_atomic_get_crtc_state(state,
					       new_plane_state->crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	ret = drm_atomic_helper_check_plane_state(new_plane_state, crtc_state,
						  0,
						  पूर्णांक_उच्च, true, true);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The HW is only able to start drawing at subpixel boundary
	 * (the two first checks bellow). At the end of a row the HW
	 * can only jump पूर्णांकeger number of subpixels क्रमward to the
	 * beginning of the next row. So we can only show picture with
	 * पूर्णांकeger subpixel width (the third check). However, after
	 * reaching the end of the drawn picture the drawing starts
	 * again at the असलolute memory address where top left corner
	 * position of the drawn picture is (so there is no need to
	 * check क्रम odd height).
	 */

	finfo = drm_क्रमmat_info(new_plane_state->fb->क्रमmat->क्रमmat);

	अगर ((new_plane_state->src_x >> 16) % finfo->hsub != 0) अणु
		dev_dbg(ddev->dev,
			"%s: x-position %u not divisible subpixel size %u\n",
			__func__, (new_plane_state->src_x >> 16), finfo->hsub);
		वापस -EINVAL;
	पूर्ण

	अगर ((new_plane_state->src_y >> 16) % finfo->vsub != 0) अणु
		dev_dbg(ddev->dev,
			"%s: y-position %u not divisible subpixel size %u\n",
			__func__, (new_plane_state->src_y >> 16), finfo->vsub);
		वापस -EINVAL;
	पूर्ण

	अगर ((new_plane_state->src_w >> 16) % finfo->hsub != 0) अणु
		dev_dbg(ddev->dev,
			"%s: src width %u not divisible by subpixel size %u\n",
			 __func__, (new_plane_state->src_w >> 16),
			 finfo->hsub);
		वापस -EINVAL;
	पूर्ण

	अगर (!new_plane_state->visible)
		वापस 0;

	hw_videoport = to_tidss_crtc(new_plane_state->crtc)->hw_videoport;

	ret = dispc_plane_check(tidss->dispc, hw_plane, new_plane_state,
				hw_videoport);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम tidss_plane_atomic_update(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *ddev = plane->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	काष्ठा tidss_plane *tplane = to_tidss_plane(plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	u32 hw_videoport;
	पूर्णांक ret;

	dev_dbg(ddev->dev, "%s\n", __func__);

	अगर (!new_state->visible) अणु
		dispc_plane_enable(tidss->dispc, tplane->hw_plane_id, false);
		वापस;
	पूर्ण

	hw_videoport = to_tidss_crtc(new_state->crtc)->hw_videoport;

	ret = dispc_plane_setup(tidss->dispc, tplane->hw_plane_id,
				new_state, hw_videoport);

	अगर (ret) अणु
		dev_err(plane->dev->dev, "%s: Failed to setup plane %d\n",
			__func__, tplane->hw_plane_id);
		dispc_plane_enable(tidss->dispc, tplane->hw_plane_id, false);
		वापस;
	पूर्ण

	dispc_plane_enable(tidss->dispc, tplane->hw_plane_id, true);
पूर्ण

अटल व्योम tidss_plane_atomic_disable(काष्ठा drm_plane *plane,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_device *ddev = plane->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	काष्ठा tidss_plane *tplane = to_tidss_plane(plane);

	dev_dbg(ddev->dev, "%s\n", __func__);

	dispc_plane_enable(tidss->dispc, tplane->hw_plane_id, false);
पूर्ण

अटल व्योम drm_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा tidss_plane *tplane = to_tidss_plane(plane);

	drm_plane_cleanup(plane);
	kमुक्त(tplane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs tidss_plane_helper_funcs = अणु
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
	.atomic_check = tidss_plane_atomic_check,
	.atomic_update = tidss_plane_atomic_update,
	.atomic_disable = tidss_plane_atomic_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs tidss_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.reset = drm_atomic_helper_plane_reset,
	.destroy = drm_plane_destroy,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

काष्ठा tidss_plane *tidss_plane_create(काष्ठा tidss_device *tidss,
				       u32 hw_plane_id, u32 plane_type,
				       u32 crtc_mask, स्थिर u32 *क्रमmats,
				       u32 num_क्रमmats)
अणु
	काष्ठा tidss_plane *tplane;
	क्रमागत drm_plane_type type;
	u32 possible_crtcs;
	u32 num_planes = tidss->feat->num_planes;
	u32 color_encodings = (BIT(DRM_COLOR_YCBCR_BT601) |
			       BIT(DRM_COLOR_YCBCR_BT709));
	u32 color_ranges = (BIT(DRM_COLOR_YCBCR_FULL_RANGE) |
			    BIT(DRM_COLOR_YCBCR_LIMITED_RANGE));
	u32 शेष_encoding = DRM_COLOR_YCBCR_BT601;
	u32 शेष_range = DRM_COLOR_YCBCR_FULL_RANGE;
	u32 blend_modes = (BIT(DRM_MODE_BLEND_PREMULTI) |
			   BIT(DRM_MODE_BLEND_COVERAGE));
	पूर्णांक ret;

	tplane = kzalloc(माप(*tplane), GFP_KERNEL);
	अगर (!tplane)
		वापस ERR_PTR(-ENOMEM);

	tplane->hw_plane_id = hw_plane_id;

	possible_crtcs = crtc_mask;
	type = plane_type;

	ret = drm_universal_plane_init(&tidss->ddev, &tplane->plane,
				       possible_crtcs,
				       &tidss_plane_funcs,
				       क्रमmats, num_क्रमmats,
				       शून्य, type, शून्य);
	अगर (ret < 0)
		जाओ err;

	drm_plane_helper_add(&tplane->plane, &tidss_plane_helper_funcs);

	drm_plane_create_zpos_property(&tplane->plane, hw_plane_id, 0,
				       num_planes - 1);

	ret = drm_plane_create_color_properties(&tplane->plane,
						color_encodings,
						color_ranges,
						शेष_encoding,
						शेष_range);
	अगर (ret)
		जाओ err;

	ret = drm_plane_create_alpha_property(&tplane->plane);
	अगर (ret)
		जाओ err;

	ret = drm_plane_create_blend_mode_property(&tplane->plane, blend_modes);
	अगर (ret)
		जाओ err;

	वापस tplane;

err:
	kमुक्त(tplane);
	वापस ERR_PTR(ret);
पूर्ण
