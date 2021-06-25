<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "xen_drm_front.h"
#समावेश "xen_drm_front_conn.h"
#समावेश "xen_drm_front_kms.h"

/*
 * Timeout in ms to रुको क्रम frame करोne event from the backend:
 * must be a bit more than IO समय-out
 */
#घोषणा FRAME_DONE_TO_MS	(XEN_DRM_FRONT_WAIT_BACK_MS + 100)

अटल काष्ठा xen_drm_front_drm_pipeline *
to_xen_drm_pipeline(काष्ठा drm_simple_display_pipe *pipe)
अणु
	वापस container_of(pipe, काष्ठा xen_drm_front_drm_pipeline, pipe);
पूर्ण

अटल व्योम fb_destroy(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = fb->dev->dev_निजी;
	पूर्णांक idx;

	अगर (drm_dev_enter(fb->dev, &idx)) अणु
		xen_drm_front_fb_detach(drm_info->front_info,
					xen_drm_front_fb_to_cookie(fb));
		drm_dev_निकास(idx);
	पूर्ण
	drm_gem_fb_destroy(fb);
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs fb_funcs = अणु
	.destroy = fb_destroy,
पूर्ण;

अटल काष्ठा drm_framebuffer *
fb_create(काष्ठा drm_device *dev, काष्ठा drm_file *filp,
	  स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = dev->dev_निजी;
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_gem_object *gem_obj;
	पूर्णांक ret;

	fb = drm_gem_fb_create_with_funcs(dev, filp, mode_cmd, &fb_funcs);
	अगर (IS_ERR(fb))
		वापस fb;

	gem_obj = fb->obj[0];

	ret = xen_drm_front_fb_attach(drm_info->front_info,
				      xen_drm_front_dbuf_to_cookie(gem_obj),
				      xen_drm_front_fb_to_cookie(fb),
				      fb->width, fb->height,
				      fb->क्रमmat->क्रमmat);
	अगर (ret < 0) अणु
		DRM_ERROR("Back failed to attach FB %p: %d\n", fb, ret);
		जाओ fail;
	पूर्ण

	वापस fb;

fail:
	drm_gem_fb_destroy(fb);
	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs mode_config_funcs = अणु
	.fb_create = fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
पूर्ण;

अटल व्योम send_pending_event(काष्ठा xen_drm_front_drm_pipeline *pipeline)
अणु
	काष्ठा drm_crtc *crtc = &pipeline->pipe.crtc;
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	अगर (pipeline->pending_event)
		drm_crtc_send_vblank_event(crtc, pipeline->pending_event);
	pipeline->pending_event = शून्य;
	spin_unlock_irqrestore(&dev->event_lock, flags);
पूर्ण

अटल व्योम display_enable(काष्ठा drm_simple_display_pipe *pipe,
			   काष्ठा drm_crtc_state *crtc_state,
			   काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(pipe);
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_framebuffer *fb = plane_state->fb;
	पूर्णांक ret, idx;

	अगर (!drm_dev_enter(pipe->crtc.dev, &idx))
		वापस;

	ret = xen_drm_front_mode_set(pipeline, crtc->x, crtc->y,
				     fb->width, fb->height,
				     fb->क्रमmat->cpp[0] * 8,
				     xen_drm_front_fb_to_cookie(fb));

	अगर (ret) अणु
		DRM_ERROR("Failed to enable display: %d\n", ret);
		pipeline->conn_connected = false;
	पूर्ण

	drm_dev_निकास(idx);
पूर्ण

अटल व्योम display_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(pipe);
	पूर्णांक ret = 0, idx;

	अगर (drm_dev_enter(pipe->crtc.dev, &idx)) अणु
		ret = xen_drm_front_mode_set(pipeline, 0, 0, 0, 0, 0,
					     xen_drm_front_fb_to_cookie(शून्य));
		drm_dev_निकास(idx);
	पूर्ण
	अगर (ret)
		DRM_ERROR("Failed to disable display: %d\n", ret);

	/* Make sure we can restart with enabled connector next समय */
	pipeline->conn_connected = true;

	/* release stalled event अगर any */
	send_pending_event(pipeline);
पूर्ण

व्योम xen_drm_front_kms_on_frame_करोne(काष्ठा xen_drm_front_drm_pipeline *pipeline,
				     u64 fb_cookie)
अणु
	/*
	 * This runs in पूर्णांकerrupt context, e.g. under
	 * drm_info->front_info->io_lock, so we cannot call _sync version
	 * to cancel the work
	 */
	cancel_delayed_work(&pipeline->pflip_to_worker);

	send_pending_event(pipeline);
पूर्ण

अटल व्योम pflip_to_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			container_of(delayed_work,
				     काष्ठा xen_drm_front_drm_pipeline,
				     pflip_to_worker);

	DRM_ERROR("Frame done timed-out, releasing");
	send_pending_event(pipeline);
पूर्ण

अटल bool display_send_page_flip(काष्ठा drm_simple_display_pipe *pipe,
				   काष्ठा drm_plane_state *old_plane_state)
अणु
	काष्ठा drm_plane_state *plane_state =
			drm_atomic_get_new_plane_state(old_plane_state->state,
						       &pipe->plane);

	/*
	 * If old_plane_state->fb is शून्य and plane_state->fb is not,
	 * then this is an atomic commit which will enable display.
	 * If old_plane_state->fb is not शून्य and plane_state->fb is,
	 * then this is an atomic commit which will disable display.
	 * Ignore these and करो not send page flip as this framebuffer will be
	 * sent to the backend as a part of display_set_config call.
	 */
	अगर (old_plane_state->fb && plane_state->fb) अणु
		काष्ठा xen_drm_front_drm_pipeline *pipeline =
				to_xen_drm_pipeline(pipe);
		काष्ठा xen_drm_front_drm_info *drm_info = pipeline->drm_info;
		पूर्णांक ret;

		schedule_delayed_work(&pipeline->pflip_to_worker,
				      msecs_to_jअगरfies(FRAME_DONE_TO_MS));

		ret = xen_drm_front_page_flip(drm_info->front_info,
					      pipeline->index,
					      xen_drm_front_fb_to_cookie(plane_state->fb));
		अगर (ret) अणु
			DRM_ERROR("Failed to send page flip request to backend: %d\n", ret);

			pipeline->conn_connected = false;
			/*
			 * Report the flip not handled, so pending event is
			 * sent, unblocking user-space.
			 */
			वापस false;
		पूर्ण
		/*
		 * Signal that page flip was handled, pending event will be sent
		 * on frame करोne event from the backend.
		 */
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक display_check(काष्ठा drm_simple_display_pipe *pipe,
			 काष्ठा drm_plane_state *plane_state,
			 काष्ठा drm_crtc_state *crtc_state)
अणु
	/*
	 * Xen करोesn't initialize vblanking via drm_vblank_init(), so
	 * DRM helpers assume that it करोesn't handle vblanking and start
	 * sending out fake VBLANK events स्वतःmatically.
	 *
	 * As xen contains it's own logic क्रम sending out VBLANK events
	 * in send_pending_event(), disable no_vblank (i.e., the xen
	 * driver has vblanking support).
	 */
	crtc_state->no_vblank = false;

	वापस 0;
पूर्ण

अटल व्योम display_update(काष्ठा drm_simple_display_pipe *pipe,
			   काष्ठा drm_plane_state *old_plane_state)
अणु
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(pipe);
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_pending_vblank_event *event;
	पूर्णांक idx;

	event = crtc->state->event;
	अगर (event) अणु
		काष्ठा drm_device *dev = crtc->dev;
		अचिन्हित दीर्घ flags;

		WARN_ON(pipeline->pending_event);

		spin_lock_irqsave(&dev->event_lock, flags);
		crtc->state->event = शून्य;

		pipeline->pending_event = event;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	पूर्ण

	अगर (!drm_dev_enter(pipe->crtc.dev, &idx)) अणु
		send_pending_event(pipeline);
		वापस;
	पूर्ण

	/*
	 * Send page flip request to the backend *after* we have event cached
	 * above, so on page flip करोne event from the backend we can
	 * deliver it and there is no race condition between this code and
	 * event from the backend.
	 * If this is not a page flip, e.g. no flip करोne event from the backend
	 * is expected, then send now.
	 */
	अगर (!display_send_page_flip(pipe, old_plane_state))
		send_pending_event(pipeline);

	drm_dev_निकास(idx);
पूर्ण

अटल क्रमागत drm_mode_status
display_mode_valid(काष्ठा drm_simple_display_pipe *pipe,
		   स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा xen_drm_front_drm_pipeline *pipeline =
			container_of(pipe, काष्ठा xen_drm_front_drm_pipeline,
				     pipe);

	अगर (mode->hdisplay != pipeline->width)
		वापस MODE_ERROR;

	अगर (mode->vdisplay != pipeline->height)
		वापस MODE_ERROR;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs display_funcs = अणु
	.mode_valid = display_mode_valid,
	.enable = display_enable,
	.disable = display_disable,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
	.check = display_check,
	.update = display_update,
पूर्ण;

अटल पूर्णांक display_pipe_init(काष्ठा xen_drm_front_drm_info *drm_info,
			     पूर्णांक index, काष्ठा xen_drm_front_cfg_connector *cfg,
			     काष्ठा xen_drm_front_drm_pipeline *pipeline)
अणु
	काष्ठा drm_device *dev = drm_info->drm_dev;
	स्थिर u32 *क्रमmats;
	पूर्णांक क्रमmat_count;
	पूर्णांक ret;

	pipeline->drm_info = drm_info;
	pipeline->index = index;
	pipeline->height = cfg->height;
	pipeline->width = cfg->width;

	INIT_DELAYED_WORK(&pipeline->pflip_to_worker, pflip_to_worker);

	ret = xen_drm_front_conn_init(drm_info, &pipeline->conn);
	अगर (ret)
		वापस ret;

	क्रमmats = xen_drm_front_conn_get_क्रमmats(&क्रमmat_count);

	वापस drm_simple_display_pipe_init(dev, &pipeline->pipe,
					    &display_funcs, क्रमmats,
					    क्रमmat_count, शून्य,
					    &pipeline->conn);
पूर्ण

पूर्णांक xen_drm_front_kms_init(काष्ठा xen_drm_front_drm_info *drm_info)
अणु
	काष्ठा drm_device *dev = drm_info->drm_dev;
	पूर्णांक i, ret;

	drm_mode_config_init(dev);

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 4095;
	dev->mode_config.max_height = 2047;
	dev->mode_config.funcs = &mode_config_funcs;

	क्रम (i = 0; i < drm_info->front_info->cfg.num_connectors; i++) अणु
		काष्ठा xen_drm_front_cfg_connector *cfg =
				&drm_info->front_info->cfg.connectors[i];
		काष्ठा xen_drm_front_drm_pipeline *pipeline =
				&drm_info->pipeline[i];

		ret = display_pipe_init(drm_info, i, cfg, pipeline);
		अगर (ret) अणु
			drm_mode_config_cleanup(dev);
			वापस ret;
		पूर्ण
	पूर्ण

	drm_mode_config_reset(dev);
	drm_kms_helper_poll_init(dev);
	वापस 0;
पूर्ण

व्योम xen_drm_front_kms_fini(काष्ठा xen_drm_front_drm_info *drm_info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < drm_info->front_info->cfg.num_connectors; i++) अणु
		काष्ठा xen_drm_front_drm_pipeline *pipeline =
				&drm_info->pipeline[i];

		cancel_delayed_work_sync(&pipeline->pflip_to_worker);

		send_pending_event(pipeline);
	पूर्ण
पूर्ण
