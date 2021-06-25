<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <linux/dma-fence.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_vblank.h>

#समावेश "tidss_crtc.h"
#समावेश "tidss_dispc.h"
#समावेश "tidss_drv.h"
#समावेश "tidss_encoder.h"
#समावेश "tidss_kms.h"
#समावेश "tidss_plane.h"

अटल व्योम tidss_atomic_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *ddev = old_state->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	bool fence_cookie = dma_fence_begin_संकेतling();

	dev_dbg(ddev->dev, "%s\n", __func__);

	tidss_runसमय_get(tidss);

	drm_atomic_helper_commit_modeset_disables(ddev, old_state);
	drm_atomic_helper_commit_planes(ddev, old_state, 0);
	drm_atomic_helper_commit_modeset_enables(ddev, old_state);

	drm_atomic_helper_commit_hw_करोne(old_state);
	dma_fence_end_संकेतling(fence_cookie);
	drm_atomic_helper_रुको_क्रम_flip_करोne(ddev, old_state);

	drm_atomic_helper_cleanup_planes(ddev, old_state);

	tidss_runसमय_put(tidss);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_helper_funcs mode_config_helper_funcs = अणु
	.atomic_commit_tail = tidss_atomic_commit_tail,
पूर्ण;

अटल पूर्णांक tidss_atomic_check(काष्ठा drm_device *ddev,
			      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *opstate;
	काष्ठा drm_plane_state *npstate;
	काष्ठा drm_plane *plane;
	काष्ठा drm_crtc_state *cstate;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret, i;

	ret = drm_atomic_helper_check(ddev, state);
	अगर (ret)
		वापस ret;

	/*
	 * Add all active planes on a CRTC to the atomic state, अगर
	 * x/y/z position or activity of any plane on that CRTC
	 * changes. This is needed क्रम updating the plane positions in
	 * tidss_crtc_position_planes() which is called from
	 * crtc_atomic_enable() and crtc_atomic_flush(). We have an
	 * extra flag to to mark x,y-position changes and together
	 * with zpos_changed the condition recognizes all the above
	 * हालs.
	 */
	क्रम_each_oldnew_plane_in_state(state, plane, opstate, npstate, i) अणु
		अगर (!npstate->crtc || !npstate->visible)
			जारी;

		अगर (!opstate->crtc || opstate->crtc_x != npstate->crtc_x ||
		    opstate->crtc_y != npstate->crtc_y) अणु
			cstate = drm_atomic_get_crtc_state(state,
							   npstate->crtc);
			अगर (IS_ERR(cstate))
				वापस PTR_ERR(cstate);
			to_tidss_crtc_state(cstate)->plane_pos_changed = true;
		पूर्ण
	पूर्ण

	क्रम_each_new_crtc_in_state(state, crtc, cstate, i) अणु
		अगर (to_tidss_crtc_state(cstate)->plane_pos_changed ||
		    cstate->zpos_changed) अणु
			ret = drm_atomic_add_affected_planes(state, crtc);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = tidss_atomic_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल पूर्णांक tidss_dispc_modeset_init(काष्ठा tidss_device *tidss)
अणु
	काष्ठा device *dev = tidss->dev;
	अचिन्हित पूर्णांक fourccs_len;
	स्थिर u32 *fourccs = dispc_plane_क्रमmats(tidss->dispc, &fourccs_len);
	अचिन्हित पूर्णांक i;

	काष्ठा pipe अणु
		u32 hw_videoport;
		काष्ठा drm_bridge *bridge;
		u32 enc_type;
	पूर्ण;

	स्थिर काष्ठा dispc_features *feat = tidss->feat;
	u32 max_vps = feat->num_vps;
	u32 max_planes = feat->num_planes;

	काष्ठा pipe pipes[TIDSS_MAX_PORTS];
	u32 num_pipes = 0;
	u32 crtc_mask;

	/* first find all the connected panels & bridges */

	क्रम (i = 0; i < max_vps; i++) अणु
		काष्ठा drm_panel *panel;
		काष्ठा drm_bridge *bridge;
		u32 enc_type = DRM_MODE_ENCODER_NONE;
		पूर्णांक ret;

		ret = drm_of_find_panel_or_bridge(dev->of_node, i, 0,
						  &panel, &bridge);
		अगर (ret == -ENODEV) अणु
			dev_dbg(dev, "no panel/bridge for port %d\n", i);
			जारी;
		पूर्ण अन्यथा अगर (ret) अणु
			dev_dbg(dev, "port %d probe returned %d\n", i, ret);
			वापस ret;
		पूर्ण

		अगर (panel) अणु
			u32 conn_type;

			dev_dbg(dev, "Setting up panel for port %d\n", i);

			चयन (feat->vp_bus_type[i]) अणु
			हाल DISPC_VP_OLDI:
				enc_type = DRM_MODE_ENCODER_LVDS;
				conn_type = DRM_MODE_CONNECTOR_LVDS;
				अवरोध;
			हाल DISPC_VP_DPI:
				enc_type = DRM_MODE_ENCODER_DPI;
				conn_type = DRM_MODE_CONNECTOR_DPI;
				अवरोध;
			शेष:
				WARN_ON(1);
				वापस -EINVAL;
			पूर्ण

			अगर (panel->connector_type != conn_type) अणु
				dev_err(dev,
					"%s: Panel %s has incompatible connector type for vp%d (%d != %d)\n",
					 __func__, dev_name(panel->dev), i,
					 panel->connector_type, conn_type);
				वापस -EINVAL;
			पूर्ण

			bridge = devm_drm_panel_bridge_add(dev, panel);
			अगर (IS_ERR(bridge)) अणु
				dev_err(dev,
					"failed to set up panel bridge for port %d\n",
					i);
				वापस PTR_ERR(bridge);
			पूर्ण
		पूर्ण

		pipes[num_pipes].hw_videoport = i;
		pipes[num_pipes].bridge = bridge;
		pipes[num_pipes].enc_type = enc_type;
		num_pipes++;
	पूर्ण

	/* all planes can be on any crtc */
	crtc_mask = (1 << num_pipes) - 1;

	/* then create a plane, a crtc and an encoder क्रम each panel/bridge */

	क्रम (i = 0; i < num_pipes; ++i) अणु
		काष्ठा tidss_plane *tplane;
		काष्ठा tidss_crtc *tcrtc;
		काष्ठा drm_encoder *enc;
		u32 hw_plane_id = feat->vid_order[tidss->num_planes];
		पूर्णांक ret;

		tplane = tidss_plane_create(tidss, hw_plane_id,
					    DRM_PLANE_TYPE_PRIMARY, crtc_mask,
					    fourccs, fourccs_len);
		अगर (IS_ERR(tplane)) अणु
			dev_err(tidss->dev, "plane create failed\n");
			वापस PTR_ERR(tplane);
		पूर्ण

		tidss->planes[tidss->num_planes++] = &tplane->plane;

		tcrtc = tidss_crtc_create(tidss, pipes[i].hw_videoport,
					  &tplane->plane);
		अगर (IS_ERR(tcrtc)) अणु
			dev_err(tidss->dev, "crtc create failed\n");
			वापस PTR_ERR(tcrtc);
		पूर्ण

		tidss->crtcs[tidss->num_crtcs++] = &tcrtc->crtc;

		enc = tidss_encoder_create(tidss, pipes[i].enc_type,
					   1 << tcrtc->crtc.index);
		अगर (IS_ERR(enc)) अणु
			dev_err(tidss->dev, "encoder create failed\n");
			वापस PTR_ERR(enc);
		पूर्ण

		ret = drm_bridge_attach(enc, pipes[i].bridge, शून्य, 0);
		अगर (ret) अणु
			dev_err(tidss->dev, "bridge attach failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* create overlay planes of the leftover planes */

	जबतक (tidss->num_planes < max_planes) अणु
		काष्ठा tidss_plane *tplane;
		u32 hw_plane_id = feat->vid_order[tidss->num_planes];

		tplane = tidss_plane_create(tidss, hw_plane_id,
					    DRM_PLANE_TYPE_OVERLAY, crtc_mask,
					    fourccs, fourccs_len);

		अगर (IS_ERR(tplane)) अणु
			dev_err(tidss->dev, "plane create failed\n");
			वापस PTR_ERR(tplane);
		पूर्ण

		tidss->planes[tidss->num_planes++] = &tplane->plane;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक tidss_modeset_init(काष्ठा tidss_device *tidss)
अणु
	काष्ठा drm_device *ddev = &tidss->ddev;
	पूर्णांक ret;

	dev_dbg(tidss->dev, "%s\n", __func__);

	ret = drmm_mode_config_init(ddev);
	अगर (ret)
		वापस ret;

	ddev->mode_config.min_width = 8;
	ddev->mode_config.min_height = 8;
	ddev->mode_config.max_width = 8096;
	ddev->mode_config.max_height = 8096;
	ddev->mode_config.normalize_zpos = true;
	ddev->mode_config.funcs = &mode_config_funcs;
	ddev->mode_config.helper_निजी = &mode_config_helper_funcs;

	ret = tidss_dispc_modeset_init(tidss);
	अगर (ret)
		वापस ret;

	ret = drm_vblank_init(ddev, tidss->num_crtcs);
	अगर (ret)
		वापस ret;

	drm_mode_config_reset(ddev);

	dev_dbg(tidss->dev, "%s done\n", __func__);

	वापस 0;
पूर्ण
