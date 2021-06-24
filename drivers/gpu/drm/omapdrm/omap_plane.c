<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob.clark@linaro.org>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>

#समावेश "omap_dmm_tiler.h"
#समावेश "omap_drv.h"

/*
 * plane funcs
 */

#घोषणा to_omap_plane(x) container_of(x, काष्ठा omap_plane, base)

काष्ठा omap_plane अणु
	काष्ठा drm_plane base;
	क्रमागत omap_plane_id id;
	स्थिर अक्षर *name;
पूर्ण;

अटल पूर्णांक omap_plane_prepare_fb(काष्ठा drm_plane *plane,
				 काष्ठा drm_plane_state *new_state)
अणु
	अगर (!new_state->fb)
		वापस 0;

	वापस omap_framebuffer_pin(new_state->fb);
पूर्ण

अटल व्योम omap_plane_cleanup_fb(काष्ठा drm_plane *plane,
				  काष्ठा drm_plane_state *old_state)
अणु
	अगर (old_state->fb)
		omap_framebuffer_unpin(old_state->fb);
पूर्ण

अटल व्योम omap_plane_atomic_update(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा omap_drm_निजी *priv = plane->dev->dev_निजी;
	काष्ठा omap_plane *omap_plane = to_omap_plane(plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा omap_overlay_info info;
	पूर्णांक ret;

	DBG("%s, crtc=%p fb=%p", omap_plane->name, new_state->crtc,
	    new_state->fb);

	स_रखो(&info, 0, माप(info));
	info.rotation_type = OMAP_DSS_ROT_NONE;
	info.rotation = DRM_MODE_ROTATE_0;
	info.global_alpha = new_state->alpha >> 8;
	info.zorder = new_state->normalized_zpos;
	अगर (new_state->pixel_blend_mode == DRM_MODE_BLEND_PREMULTI)
		info.pre_mult_alpha = 1;
	अन्यथा
		info.pre_mult_alpha = 0;
	info.color_encoding = new_state->color_encoding;
	info.color_range = new_state->color_range;

	/* update scanout: */
	omap_framebuffer_update_scanout(new_state->fb, new_state, &info);

	DBG("%dx%d -> %dx%d (%d)", info.width, info.height,
			info.out_width, info.out_height,
			info.screen_width);
	DBG("%d,%d %pad %pad", info.pos_x, info.pos_y,
			&info.paddr, &info.p_uv_addr);

	/* and finally, update omapdss: */
	ret = dispc_ovl_setup(priv->dispc, omap_plane->id, &info,
			      omap_crtc_timings(new_state->crtc), false,
			      omap_crtc_channel(new_state->crtc));
	अगर (ret) अणु
		dev_err(plane->dev->dev, "Failed to setup plane %s\n",
			omap_plane->name);
		dispc_ovl_enable(priv->dispc, omap_plane->id, false);
		वापस;
	पूर्ण

	dispc_ovl_enable(priv->dispc, omap_plane->id, true);
पूर्ण

अटल व्योम omap_plane_atomic_disable(काष्ठा drm_plane *plane,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा omap_drm_निजी *priv = plane->dev->dev_निजी;
	काष्ठा omap_plane *omap_plane = to_omap_plane(plane);

	new_state->rotation = DRM_MODE_ROTATE_0;
	new_state->zpos = plane->type == DRM_PLANE_TYPE_PRIMARY ? 0 : omap_plane->id;

	dispc_ovl_enable(priv->dispc, omap_plane->id, false);
पूर्ण

अटल पूर्णांक omap_plane_atomic_check(काष्ठा drm_plane *plane,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_crtc_state *crtc_state;

	अगर (!new_plane_state->fb)
		वापस 0;

	/* crtc should only be शून्य when disabling (i.e., !new_plane_state->fb) */
	अगर (WARN_ON(!new_plane_state->crtc))
		वापस 0;

	crtc_state = drm_atomic_get_existing_crtc_state(state,
							new_plane_state->crtc);
	/* we should have a crtc state अगर the plane is attached to a crtc */
	अगर (WARN_ON(!crtc_state))
		वापस 0;

	अगर (!crtc_state->enable)
		वापस 0;

	अगर (new_plane_state->crtc_x < 0 || new_plane_state->crtc_y < 0)
		वापस -EINVAL;

	अगर (new_plane_state->crtc_x + new_plane_state->crtc_w > crtc_state->adjusted_mode.hdisplay)
		वापस -EINVAL;

	अगर (new_plane_state->crtc_y + new_plane_state->crtc_h > crtc_state->adjusted_mode.vdisplay)
		वापस -EINVAL;

	अगर (new_plane_state->rotation != DRM_MODE_ROTATE_0 &&
	    !omap_framebuffer_supports_rotation(new_plane_state->fb))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs omap_plane_helper_funcs = अणु
	.prepare_fb = omap_plane_prepare_fb,
	.cleanup_fb = omap_plane_cleanup_fb,
	.atomic_check = omap_plane_atomic_check,
	.atomic_update = omap_plane_atomic_update,
	.atomic_disable = omap_plane_atomic_disable,
पूर्ण;

अटल व्योम omap_plane_destroy(काष्ठा drm_plane *plane)
अणु
	काष्ठा omap_plane *omap_plane = to_omap_plane(plane);

	DBG("%s", omap_plane->name);

	drm_plane_cleanup(plane);

	kमुक्त(omap_plane);
पूर्ण

/* helper to install properties which are common to planes and crtcs */
व्योम omap_plane_install_properties(काष्ठा drm_plane *plane,
		काष्ठा drm_mode_object *obj)
अणु
	काष्ठा drm_device *dev = plane->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;

	अगर (priv->has_dmm) अणु
		अगर (!plane->rotation_property)
			drm_plane_create_rotation_property(plane,
							   DRM_MODE_ROTATE_0,
							   DRM_MODE_ROTATE_0 | DRM_MODE_ROTATE_90 |
							   DRM_MODE_ROTATE_180 | DRM_MODE_ROTATE_270 |
							   DRM_MODE_REFLECT_X | DRM_MODE_REFLECT_Y);

		/* Attach the rotation property also to the crtc object */
		अगर (plane->rotation_property && obj != &plane->base)
			drm_object_attach_property(obj, plane->rotation_property,
						   DRM_MODE_ROTATE_0);
	पूर्ण

	drm_object_attach_property(obj, priv->zorder_prop, 0);
पूर्ण

अटल व्योम omap_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा omap_plane *omap_plane = to_omap_plane(plane);

	drm_atomic_helper_plane_reset(plane);
	अगर (!plane->state)
		वापस;

	/*
	 * Set the zpos शेष depending on whether we are a primary or overlay
	 * plane.
	 */
	plane->state->zpos = plane->type == DRM_PLANE_TYPE_PRIMARY
			   ? 0 : omap_plane->id;
	plane->state->color_encoding = DRM_COLOR_YCBCR_BT601;
	plane->state->color_range = DRM_COLOR_YCBCR_FULL_RANGE;
पूर्ण

अटल पूर्णांक omap_plane_atomic_set_property(काष्ठा drm_plane *plane,
					  काष्ठा drm_plane_state *state,
					  काष्ठा drm_property *property,
					  u64 val)
अणु
	काष्ठा omap_drm_निजी *priv = plane->dev->dev_निजी;

	अगर (property == priv->zorder_prop)
		state->zpos = val;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_plane_atomic_get_property(काष्ठा drm_plane *plane,
					  स्थिर काष्ठा drm_plane_state *state,
					  काष्ठा drm_property *property,
					  u64 *val)
अणु
	काष्ठा omap_drm_निजी *priv = plane->dev->dev_निजी;

	अगर (property == priv->zorder_prop)
		*val = state->zpos;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs omap_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.reset = omap_plane_reset,
	.destroy = omap_plane_destroy,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.atomic_set_property = omap_plane_atomic_set_property,
	.atomic_get_property = omap_plane_atomic_get_property,
पूर्ण;

अटल bool omap_plane_supports_yuv(काष्ठा drm_plane *plane)
अणु
	काष्ठा omap_drm_निजी *priv = plane->dev->dev_निजी;
	काष्ठा omap_plane *omap_plane = to_omap_plane(plane);
	स्थिर u32 *क्रमmats = dispc_ovl_get_color_modes(priv->dispc, omap_plane->id);
	u32 i;

	क्रम (i = 0; क्रमmats[i]; i++)
		अगर (क्रमmats[i] == DRM_FORMAT_YUYV ||
		    क्रमmats[i] == DRM_FORMAT_UYVY ||
		    क्रमmats[i] == DRM_FORMAT_NV12)
			वापस true;

	वापस false;
पूर्ण

अटल स्थिर अक्षर *plane_id_to_name[] = अणु
	[OMAP_DSS_GFX] = "gfx",
	[OMAP_DSS_VIDEO1] = "vid1",
	[OMAP_DSS_VIDEO2] = "vid2",
	[OMAP_DSS_VIDEO3] = "vid3",
पूर्ण;

अटल स्थिर क्रमागत omap_plane_id plane_idx_to_id[] = अणु
	OMAP_DSS_GFX,
	OMAP_DSS_VIDEO1,
	OMAP_DSS_VIDEO2,
	OMAP_DSS_VIDEO3,
पूर्ण;

/* initialize plane */
काष्ठा drm_plane *omap_plane_init(काष्ठा drm_device *dev,
		पूर्णांक idx, क्रमागत drm_plane_type type,
		u32 possible_crtcs)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित पूर्णांक num_planes = dispc_get_num_ovls(priv->dispc);
	काष्ठा drm_plane *plane;
	काष्ठा omap_plane *omap_plane;
	क्रमागत omap_plane_id id;
	पूर्णांक ret;
	u32 nक्रमmats;
	स्थिर u32 *क्रमmats;

	अगर (WARN_ON(idx >= ARRAY_SIZE(plane_idx_to_id)))
		वापस ERR_PTR(-EINVAL);

	id = plane_idx_to_id[idx];

	DBG("%s: type=%d", plane_id_to_name[id], type);

	omap_plane = kzalloc(माप(*omap_plane), GFP_KERNEL);
	अगर (!omap_plane)
		वापस ERR_PTR(-ENOMEM);

	क्रमmats = dispc_ovl_get_color_modes(priv->dispc, id);
	क्रम (nक्रमmats = 0; क्रमmats[nक्रमmats]; ++nक्रमmats)
		;
	omap_plane->id = id;
	omap_plane->name = plane_id_to_name[id];

	plane = &omap_plane->base;

	ret = drm_universal_plane_init(dev, plane, possible_crtcs,
				       &omap_plane_funcs, क्रमmats,
				       nक्रमmats, शून्य, type, शून्य);
	अगर (ret < 0)
		जाओ error;

	drm_plane_helper_add(plane, &omap_plane_helper_funcs);

	omap_plane_install_properties(plane, &plane->base);
	drm_plane_create_zpos_property(plane, 0, 0, num_planes - 1);
	drm_plane_create_alpha_property(plane);
	drm_plane_create_blend_mode_property(plane, BIT(DRM_MODE_BLEND_PREMULTI) |
					     BIT(DRM_MODE_BLEND_COVERAGE));

	अगर (omap_plane_supports_yuv(plane))
		drm_plane_create_color_properties(plane,
						  BIT(DRM_COLOR_YCBCR_BT601) |
						  BIT(DRM_COLOR_YCBCR_BT709),
						  BIT(DRM_COLOR_YCBCR_FULL_RANGE) |
						  BIT(DRM_COLOR_YCBCR_LIMITED_RANGE),
						  DRM_COLOR_YCBCR_BT601,
						  DRM_COLOR_YCBCR_FULL_RANGE);

	वापस plane;

error:
	dev_err(dev->dev, "%s(): could not create plane: %s\n",
		__func__, plane_id_to_name[id]);

	kमुक्त(omap_plane);
	वापस शून्य;
पूर्ण
