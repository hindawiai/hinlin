<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * rcar_du_vsp.h  --  R-Car Display Unit VSP-Based Compositor
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * Contact: Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश <linux/bitops.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/videodev2.h>

#समावेश <media/vsp1.h>

#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_kms.h"
#समावेश "rcar_du_vsp.h"
#समावेश "rcar_du_writeback.h"

अटल व्योम rcar_du_vsp_complete(व्योम *निजी, अचिन्हित पूर्णांक status, u32 crc)
अणु
	काष्ठा rcar_du_crtc *crtc = निजी;

	अगर (crtc->vblank_enable)
		drm_crtc_handle_vblank(&crtc->crtc);

	अगर (status & VSP1_DU_STATUS_COMPLETE)
		rcar_du_crtc_finish_page_flip(crtc);
	अगर (status & VSP1_DU_STATUS_WRITEBACK)
		rcar_du_ग_लिखोback_complete(crtc);

	drm_crtc_add_crc_entry(&crtc->crtc, false, 0, &crc);
पूर्ण

व्योम rcar_du_vsp_enable(काष्ठा rcar_du_crtc *crtc)
अणु
	स्थिर काष्ठा drm_display_mode *mode = &crtc->crtc.state->adjusted_mode;
	काष्ठा rcar_du_device *rcdu = crtc->dev;
	काष्ठा vsp1_du_lअगर_config cfg = अणु
		.width = mode->hdisplay,
		.height = mode->vdisplay,
		.पूर्णांकerlaced = mode->flags & DRM_MODE_FLAG_INTERLACE,
		.callback = rcar_du_vsp_complete,
		.callback_data = crtc,
	पूर्ण;
	काष्ठा rcar_du_plane_state state = अणु
		.state = अणु
			.alpha = DRM_BLEND_ALPHA_OPAQUE,
			.crtc = &crtc->crtc,
			.dst.x1 = 0,
			.dst.y1 = 0,
			.dst.x2 = mode->hdisplay,
			.dst.y2 = mode->vdisplay,
			.src.x1 = 0,
			.src.y1 = 0,
			.src.x2 = mode->hdisplay << 16,
			.src.y2 = mode->vdisplay << 16,
			.zpos = 0,
		पूर्ण,
		.क्रमmat = rcar_du_क्रमmat_info(DRM_FORMAT_ARGB8888),
		.source = RCAR_DU_PLANE_VSPD1,
		.colorkey = 0,
	पूर्ण;

	अगर (rcdu->info->gen >= 3)
		state.hwindex = (crtc->index % 2) ? 2 : 0;
	अन्यथा
		state.hwindex = crtc->index % 2;

	__rcar_du_plane_setup(crtc->group, &state);

	/*
	 * Ensure that the plane source configuration takes effect by requesting
	 * a restart of the group. See rcar_du_plane_atomic_update() क्रम a more
	 * detailed explanation.
	 *
	 * TODO: Check whether this is still needed on Gen3.
	 */
	crtc->group->need_restart = true;

	vsp1_du_setup_lअगर(crtc->vsp->vsp, crtc->vsp_pipe, &cfg);
पूर्ण

व्योम rcar_du_vsp_disable(काष्ठा rcar_du_crtc *crtc)
अणु
	vsp1_du_setup_lअगर(crtc->vsp->vsp, crtc->vsp_pipe, शून्य);
पूर्ण

व्योम rcar_du_vsp_atomic_begin(काष्ठा rcar_du_crtc *crtc)
अणु
	vsp1_du_atomic_begin(crtc->vsp->vsp, crtc->vsp_pipe);
पूर्ण

व्योम rcar_du_vsp_atomic_flush(काष्ठा rcar_du_crtc *crtc)
अणु
	काष्ठा vsp1_du_atomic_pipe_config cfg = अणु अणु 0, पूर्ण पूर्ण;
	काष्ठा rcar_du_crtc_state *state;

	state = to_rcar_crtc_state(crtc->crtc.state);
	cfg.crc = state->crc;

	rcar_du_ग_लिखोback_setup(crtc, &cfg.ग_लिखोback);

	vsp1_du_atomic_flush(crtc->vsp->vsp, crtc->vsp_pipe, &cfg);
पूर्ण

अटल स्थिर u32 rcar_du_vsp_क्रमmats[] = अणु
	DRM_FORMAT_RGB332,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_BGR888,
	DRM_FORMAT_RGB888,
	DRM_FORMAT_BGRA8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_UYVY,
	DRM_FORMAT_YUYV,
	DRM_FORMAT_YVYU,
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV21,
	DRM_FORMAT_NV16,
	DRM_FORMAT_NV61,
	DRM_FORMAT_YUV420,
	DRM_FORMAT_YVU420,
	DRM_FORMAT_YUV422,
	DRM_FORMAT_YVU422,
	DRM_FORMAT_YUV444,
	DRM_FORMAT_YVU444,
पूर्ण;

अटल व्योम rcar_du_vsp_plane_setup(काष्ठा rcar_du_vsp_plane *plane)
अणु
	काष्ठा rcar_du_vsp_plane_state *state =
		to_rcar_vsp_plane_state(plane->plane.state);
	काष्ठा rcar_du_crtc *crtc = to_rcar_crtc(state->state.crtc);
	काष्ठा drm_framebuffer *fb = plane->plane.state->fb;
	स्थिर काष्ठा rcar_du_क्रमmat_info *क्रमmat;
	काष्ठा vsp1_du_atomic_config cfg = अणु
		.pixelक्रमmat = 0,
		.pitch = fb->pitches[0],
		.alpha = state->state.alpha >> 8,
		.zpos = state->state.zpos,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	cfg.src.left = state->state.src.x1 >> 16;
	cfg.src.top = state->state.src.y1 >> 16;
	cfg.src.width = drm_rect_width(&state->state.src) >> 16;
	cfg.src.height = drm_rect_height(&state->state.src) >> 16;

	cfg.dst.left = state->state.dst.x1;
	cfg.dst.top = state->state.dst.y1;
	cfg.dst.width = drm_rect_width(&state->state.dst);
	cfg.dst.height = drm_rect_height(&state->state.dst);

	क्रम (i = 0; i < state->क्रमmat->planes; ++i)
		cfg.mem[i] = sg_dma_address(state->sg_tables[i].sgl)
			   + fb->offsets[i];

	क्रमmat = rcar_du_क्रमmat_info(state->क्रमmat->fourcc);
	cfg.pixelक्रमmat = क्रमmat->v4l2;

	vsp1_du_atomic_update(plane->vsp->vsp, crtc->vsp_pipe,
			      plane->index, &cfg);
पूर्ण

पूर्णांक rcar_du_vsp_map_fb(काष्ठा rcar_du_vsp *vsp, काष्ठा drm_framebuffer *fb,
		       काष्ठा sg_table sg_tables[3])
अणु
	काष्ठा rcar_du_device *rcdu = vsp->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < fb->क्रमmat->num_planes; ++i) अणु
		काष्ठा drm_gem_cma_object *gem = drm_fb_cma_get_gem_obj(fb, i);
		काष्ठा sg_table *sgt = &sg_tables[i];

		ret = dma_get_sgtable(rcdu->dev, sgt, gem->vaddr, gem->paddr,
				      gem->base.size);
		अगर (ret)
			जाओ fail;

		ret = vsp1_du_map_sg(vsp->vsp, sgt);
		अगर (ret) अणु
			sg_मुक्त_table(sgt);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	जबतक (i--) अणु
		काष्ठा sg_table *sgt = &sg_tables[i];

		vsp1_du_unmap_sg(vsp->vsp, sgt);
		sg_मुक्त_table(sgt);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rcar_du_vsp_plane_prepare_fb(काष्ठा drm_plane *plane,
					काष्ठा drm_plane_state *state)
अणु
	काष्ठा rcar_du_vsp_plane_state *rstate = to_rcar_vsp_plane_state(state);
	काष्ठा rcar_du_vsp *vsp = to_rcar_vsp_plane(plane)->vsp;
	पूर्णांक ret;

	/*
	 * There's no need to prepare (and unprepare) the framebuffer when the
	 * plane is not visible, as it will not be displayed.
	 */
	अगर (!state->visible)
		वापस 0;

	ret = rcar_du_vsp_map_fb(vsp, state->fb, rstate->sg_tables);
	अगर (ret < 0)
		वापस ret;

	वापस drm_gem_plane_helper_prepare_fb(plane, state);
पूर्ण

व्योम rcar_du_vsp_unmap_fb(काष्ठा rcar_du_vsp *vsp, काष्ठा drm_framebuffer *fb,
			  काष्ठा sg_table sg_tables[3])
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < fb->क्रमmat->num_planes; ++i) अणु
		काष्ठा sg_table *sgt = &sg_tables[i];

		vsp1_du_unmap_sg(vsp->vsp, sgt);
		sg_मुक्त_table(sgt);
	पूर्ण
पूर्ण

अटल व्योम rcar_du_vsp_plane_cleanup_fb(काष्ठा drm_plane *plane,
					 काष्ठा drm_plane_state *state)
अणु
	काष्ठा rcar_du_vsp_plane_state *rstate = to_rcar_vsp_plane_state(state);
	काष्ठा rcar_du_vsp *vsp = to_rcar_vsp_plane(plane)->vsp;

	अगर (!state->visible)
		वापस;

	rcar_du_vsp_unmap_fb(vsp, state->fb, rstate->sg_tables);
पूर्ण

अटल पूर्णांक rcar_du_vsp_plane_atomic_check(काष्ठा drm_plane *plane,
					  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा rcar_du_vsp_plane_state *rstate = to_rcar_vsp_plane_state(new_plane_state);

	वापस __rcar_du_plane_atomic_check(plane, new_plane_state,
					    &rstate->क्रमmat);
पूर्ण

अटल व्योम rcar_du_vsp_plane_atomic_update(काष्ठा drm_plane *plane,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_state = drm_atomic_get_old_plane_state(state, plane);
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state, plane);
	काष्ठा rcar_du_vsp_plane *rplane = to_rcar_vsp_plane(plane);
	काष्ठा rcar_du_crtc *crtc = to_rcar_crtc(old_state->crtc);

	अगर (new_state->visible)
		rcar_du_vsp_plane_setup(rplane);
	अन्यथा अगर (old_state->crtc)
		vsp1_du_atomic_update(rplane->vsp->vsp, crtc->vsp_pipe,
				      rplane->index, शून्य);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs rcar_du_vsp_plane_helper_funcs = अणु
	.prepare_fb = rcar_du_vsp_plane_prepare_fb,
	.cleanup_fb = rcar_du_vsp_plane_cleanup_fb,
	.atomic_check = rcar_du_vsp_plane_atomic_check,
	.atomic_update = rcar_du_vsp_plane_atomic_update,
पूर्ण;

अटल काष्ठा drm_plane_state *
rcar_du_vsp_plane_atomic_duplicate_state(काष्ठा drm_plane *plane)
अणु
	काष्ठा rcar_du_vsp_plane_state *copy;

	अगर (WARN_ON(!plane->state))
		वापस शून्य;

	copy = kzalloc(माप(*copy), GFP_KERNEL);
	अगर (copy == शून्य)
		वापस शून्य;

	__drm_atomic_helper_plane_duplicate_state(plane, &copy->state);

	वापस &copy->state;
पूर्ण

अटल व्योम rcar_du_vsp_plane_atomic_destroy_state(काष्ठा drm_plane *plane,
						   काष्ठा drm_plane_state *state)
अणु
	__drm_atomic_helper_plane_destroy_state(state);
	kमुक्त(to_rcar_vsp_plane_state(state));
पूर्ण

अटल व्योम rcar_du_vsp_plane_reset(काष्ठा drm_plane *plane)
अणु
	काष्ठा rcar_du_vsp_plane_state *state;

	अगर (plane->state) अणु
		rcar_du_vsp_plane_atomic_destroy_state(plane, plane->state);
		plane->state = शून्य;
	पूर्ण

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस;

	__drm_atomic_helper_plane_reset(plane, &state->state);
	state->state.zpos = plane->type == DRM_PLANE_TYPE_PRIMARY ? 0 : 1;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs rcar_du_vsp_plane_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.reset = rcar_du_vsp_plane_reset,
	.destroy = drm_plane_cleanup,
	.atomic_duplicate_state = rcar_du_vsp_plane_atomic_duplicate_state,
	.atomic_destroy_state = rcar_du_vsp_plane_atomic_destroy_state,
पूर्ण;

अटल व्योम rcar_du_vsp_cleanup(काष्ठा drm_device *dev, व्योम *res)
अणु
	काष्ठा rcar_du_vsp *vsp = res;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vsp->num_planes; ++i) अणु
		काष्ठा rcar_du_vsp_plane *plane = &vsp->planes[i];

		drm_plane_cleanup(&plane->plane);
	पूर्ण

	kमुक्त(vsp->planes);

	put_device(vsp->vsp);
पूर्ण

पूर्णांक rcar_du_vsp_init(काष्ठा rcar_du_vsp *vsp, काष्ठा device_node *np,
		     अचिन्हित पूर्णांक crtcs)
अणु
	काष्ठा rcar_du_device *rcdu = vsp->dev;
	काष्ठा platक्रमm_device *pdev;
	अचिन्हित पूर्णांक num_crtcs = hweight32(crtcs);
	अचिन्हित पूर्णांक num_planes;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	/* Find the VSP device and initialize it. */
	pdev = of_find_device_by_node(np);
	अगर (!pdev)
		वापस -ENXIO;

	vsp->vsp = &pdev->dev;

	ret = drmm_add_action_or_reset(&rcdu->ddev, rcar_du_vsp_cleanup, vsp);
	अगर (ret < 0)
		वापस ret;

	ret = vsp1_du_init(vsp->vsp);
	अगर (ret < 0)
		वापस ret;

	 /*
	  * The VSP2D (Gen3) has 5 RPFs, but the VSP1D (Gen2) is limited to
	  * 4 RPFs.
	  */
	num_planes = rcdu->info->gen >= 3 ? 5 : 4;

	vsp->planes = kसुस्मृति(num_planes, माप(*vsp->planes), GFP_KERNEL);
	अगर (!vsp->planes)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_planes; ++i) अणु
		क्रमागत drm_plane_type type = i < num_crtcs
					 ? DRM_PLANE_TYPE_PRIMARY
					 : DRM_PLANE_TYPE_OVERLAY;
		काष्ठा rcar_du_vsp_plane *plane = &vsp->planes[i];

		plane->vsp = vsp;
		plane->index = i;

		ret = drm_universal_plane_init(&rcdu->ddev, &plane->plane,
					       crtcs, &rcar_du_vsp_plane_funcs,
					       rcar_du_vsp_क्रमmats,
					       ARRAY_SIZE(rcar_du_vsp_क्रमmats),
					       शून्य, type, शून्य);
		अगर (ret < 0)
			वापस ret;

		drm_plane_helper_add(&plane->plane,
				     &rcar_du_vsp_plane_helper_funcs);

		अगर (type == DRM_PLANE_TYPE_PRIMARY) अणु
			drm_plane_create_zpos_immutable_property(&plane->plane,
								 0);
		पूर्ण अन्यथा अणु
			drm_plane_create_alpha_property(&plane->plane);
			drm_plane_create_zpos_property(&plane->plane, 1, 1,
						       num_planes - 1);
		पूर्ण

		vsp->num_planes++;
	पूर्ण

	वापस 0;
पूर्ण
