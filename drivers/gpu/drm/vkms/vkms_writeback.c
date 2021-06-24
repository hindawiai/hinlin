<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+

#समावेश <linux/dma-buf-map.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_ग_लिखोback.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_gem_shmem_helper.h>

#समावेश "vkms_drv.h"

अटल स्थिर u32 vkms_wb_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs vkms_wb_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.reset = drm_atomic_helper_connector_reset,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक vkms_wb_encoder_atomic_check(काष्ठा drm_encoder *encoder,
					काष्ठा drm_crtc_state *crtc_state,
					काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_framebuffer *fb;
	स्थिर काष्ठा drm_display_mode *mode = &crtc_state->mode;

	अगर (!conn_state->ग_लिखोback_job || !conn_state->ग_लिखोback_job->fb)
		वापस 0;

	fb = conn_state->ग_लिखोback_job->fb;
	अगर (fb->width != mode->hdisplay || fb->height != mode->vdisplay) अणु
		DRM_DEBUG_KMS("Invalid framebuffer size %ux%u\n",
			      fb->width, fb->height);
		वापस -EINVAL;
	पूर्ण

	अगर (fb->क्रमmat->क्रमmat != vkms_wb_क्रमmats[0]) अणु
		DRM_DEBUG_KMS("Invalid pixel format %p4cc\n",
			      &fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs vkms_wb_encoder_helper_funcs = अणु
	.atomic_check = vkms_wb_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक vkms_wb_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	वापस drm_add_modes_noedid(connector, dev->mode_config.max_width,
				    dev->mode_config.max_height);
पूर्ण

अटल पूर्णांक vkms_wb_prepare_job(काष्ठा drm_ग_लिखोback_connector *wb_connector,
			       काष्ठा drm_ग_लिखोback_job *job)
अणु
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	अगर (!job->fb)
		वापस 0;

	gem_obj = drm_gem_fb_get_obj(job->fb, 0);
	ret = drm_gem_shmem_vmap(gem_obj, &map);
	अगर (ret) अणु
		DRM_ERROR("vmap failed: %d\n", ret);
		वापस ret;
	पूर्ण

	job->priv = map.vaddr;

	वापस 0;
पूर्ण

अटल व्योम vkms_wb_cleanup_job(काष्ठा drm_ग_लिखोback_connector *connector,
				काष्ठा drm_ग_लिखोback_job *job)
अणु
	काष्ठा drm_gem_object *gem_obj;
	काष्ठा vkms_device *vkmsdev;
	काष्ठा dma_buf_map map;

	अगर (!job->fb)
		वापस;

	gem_obj = drm_gem_fb_get_obj(job->fb, 0);
	dma_buf_map_set_vaddr(&map, job->priv);
	drm_gem_shmem_vunmap(gem_obj, &map);

	vkmsdev = drm_device_to_vkms_device(gem_obj->dev);
	vkms_set_composer(&vkmsdev->output, false);
पूर्ण

अटल व्योम vkms_wb_atomic_commit(काष्ठा drm_connector *conn,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *connector_state = drm_atomic_get_new_connector_state(state,
											 conn);
	काष्ठा vkms_device *vkmsdev = drm_device_to_vkms_device(conn->dev);
	काष्ठा vkms_output *output = &vkmsdev->output;
	काष्ठा drm_ग_लिखोback_connector *wb_conn = &output->wb_connector;
	काष्ठा drm_connector_state *conn_state = wb_conn->base.state;
	काष्ठा vkms_crtc_state *crtc_state = output->composer_state;

	अगर (!conn_state)
		वापस;

	vkms_set_composer(&vkmsdev->output, true);

	spin_lock_irq(&output->composer_lock);
	crtc_state->active_ग_लिखोback = conn_state->ग_लिखोback_job->priv;
	crtc_state->wb_pending = true;
	spin_unlock_irq(&output->composer_lock);
	drm_ग_लिखोback_queue_job(wb_conn, connector_state);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs vkms_wb_conn_helper_funcs = अणु
	.get_modes = vkms_wb_connector_get_modes,
	.prepare_ग_लिखोback_job = vkms_wb_prepare_job,
	.cleanup_ग_लिखोback_job = vkms_wb_cleanup_job,
	.atomic_commit = vkms_wb_atomic_commit,
पूर्ण;

पूर्णांक vkms_enable_ग_लिखोback_connector(काष्ठा vkms_device *vkmsdev)
अणु
	काष्ठा drm_ग_लिखोback_connector *wb = &vkmsdev->output.wb_connector;

	vkmsdev->output.wb_connector.encoder.possible_crtcs = 1;
	drm_connector_helper_add(&wb->base, &vkms_wb_conn_helper_funcs);

	वापस drm_ग_लिखोback_connector_init(&vkmsdev->drm, wb,
					    &vkms_wb_connector_funcs,
					    &vkms_wb_encoder_helper_funcs,
					    vkms_wb_क्रमmats,
					    ARRAY_SIZE(vkms_wb_क्रमmats));
पूर्ण
