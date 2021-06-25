<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rcar_du_ग_लिखोback.c  --  R-Car Display Unit Writeback Support
 *
 * Copyright (C) 2019 Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_ग_लिखोback.h>

#समावेश "rcar_du_crtc.h"
#समावेश "rcar_du_drv.h"
#समावेश "rcar_du_kms.h"
#समावेश "rcar_du_writeback.h"

/**
 * काष्ठा rcar_du_wb_conn_state - Driver-specअगरic ग_लिखोback connector state
 * @state: base DRM connector state
 * @क्रमmat: क्रमmat of the ग_लिखोback framebuffer
 */
काष्ठा rcar_du_wb_conn_state अणु
	काष्ठा drm_connector_state state;
	स्थिर काष्ठा rcar_du_क्रमmat_info *क्रमmat;
पूर्ण;

#घोषणा to_rcar_wb_conn_state(s) \
	container_of(s, काष्ठा rcar_du_wb_conn_state, state)

/**
 * काष्ठा rcar_du_wb_job - Driver-निजी data क्रम ग_लिखोback jobs
 * @sg_tables: scatter-gather tables क्रम the framebuffer memory
 */
काष्ठा rcar_du_wb_job अणु
	काष्ठा sg_table sg_tables[3];
पूर्ण;

अटल पूर्णांक rcar_du_wb_conn_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;

	वापस drm_add_modes_noedid(connector, dev->mode_config.max_width,
				    dev->mode_config.max_height);
पूर्ण

अटल पूर्णांक rcar_du_wb_prepare_job(काष्ठा drm_ग_लिखोback_connector *connector,
				  काष्ठा drm_ग_लिखोback_job *job)
अणु
	काष्ठा rcar_du_crtc *rcrtc = wb_to_rcar_crtc(connector);
	काष्ठा rcar_du_wb_job *rjob;
	पूर्णांक ret;

	अगर (!job->fb)
		वापस 0;

	rjob = kzalloc(माप(*rjob), GFP_KERNEL);
	अगर (!rjob)
		वापस -ENOMEM;

	/* Map the framebuffer to the VSP. */
	ret = rcar_du_vsp_map_fb(rcrtc->vsp, job->fb, rjob->sg_tables);
	अगर (ret < 0) अणु
		kमुक्त(rjob);
		वापस ret;
	पूर्ण

	job->priv = rjob;
	वापस 0;
पूर्ण

अटल व्योम rcar_du_wb_cleanup_job(काष्ठा drm_ग_लिखोback_connector *connector,
				   काष्ठा drm_ग_लिखोback_job *job)
अणु
	काष्ठा rcar_du_crtc *rcrtc = wb_to_rcar_crtc(connector);
	काष्ठा rcar_du_wb_job *rjob = job->priv;

	अगर (!job->fb)
		वापस;

	rcar_du_vsp_unmap_fb(rcrtc->vsp, job->fb, rjob->sg_tables);
	kमुक्त(rjob);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs rcar_du_wb_conn_helper_funcs = अणु
	.get_modes = rcar_du_wb_conn_get_modes,
	.prepare_ग_लिखोback_job = rcar_du_wb_prepare_job,
	.cleanup_ग_लिखोback_job = rcar_du_wb_cleanup_job,
पूर्ण;

अटल काष्ठा drm_connector_state *
rcar_du_wb_conn_duplicate_state(काष्ठा drm_connector *connector)
अणु
	काष्ठा rcar_du_wb_conn_state *copy;

	अगर (WARN_ON(!connector->state))
		वापस शून्य;

	copy = kzalloc(माप(*copy), GFP_KERNEL);
	अगर (!copy)
		वापस शून्य;

	__drm_atomic_helper_connector_duplicate_state(connector, &copy->state);

	वापस &copy->state;
पूर्ण

अटल व्योम rcar_du_wb_conn_destroy_state(काष्ठा drm_connector *connector,
					  काष्ठा drm_connector_state *state)
अणु
	__drm_atomic_helper_connector_destroy_state(state);
	kमुक्त(to_rcar_wb_conn_state(state));
पूर्ण

अटल व्योम rcar_du_wb_conn_reset(काष्ठा drm_connector *connector)
अणु
	काष्ठा rcar_du_wb_conn_state *state;

	अगर (connector->state) अणु
		rcar_du_wb_conn_destroy_state(connector, connector->state);
		connector->state = शून्य;
	पूर्ण

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state == शून्य)
		वापस;

	__drm_atomic_helper_connector_reset(connector, &state->state);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs rcar_du_wb_conn_funcs = अणु
	.reset = rcar_du_wb_conn_reset,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = drm_connector_cleanup,
	.atomic_duplicate_state = rcar_du_wb_conn_duplicate_state,
	.atomic_destroy_state = rcar_du_wb_conn_destroy_state,
पूर्ण;

अटल पूर्णांक rcar_du_wb_enc_atomic_check(काष्ठा drm_encoder *encoder,
				       काष्ठा drm_crtc_state *crtc_state,
				       काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा rcar_du_wb_conn_state *wb_state =
		to_rcar_wb_conn_state(conn_state);
	स्थिर काष्ठा drm_display_mode *mode = &crtc_state->mode;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_framebuffer *fb;

	अगर (!conn_state->ग_लिखोback_job)
		वापस 0;

	fb = conn_state->ग_लिखोback_job->fb;

	/*
	 * Verअगरy that the framebuffer क्रमmat is supported and that its size
	 * matches the current mode.
	 */
	अगर (fb->width != mode->hdisplay || fb->height != mode->vdisplay) अणु
		dev_dbg(dev->dev, "%s: invalid framebuffer size %ux%u\n",
			__func__, fb->width, fb->height);
		वापस -EINVAL;
	पूर्ण

	wb_state->क्रमmat = rcar_du_क्रमmat_info(fb->क्रमmat->क्रमmat);
	अगर (wb_state->क्रमmat == शून्य) अणु
		dev_dbg(dev->dev, "%s: unsupported format %08x\n", __func__,
			fb->क्रमmat->क्रमmat);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs rcar_du_wb_enc_helper_funcs = अणु
	.atomic_check = rcar_du_wb_enc_atomic_check,
पूर्ण;

/*
 * Only RGB क्रमmats are currently supported as the VSP outमाला_दो RGB to the DU
 * and can't convert to YUV separately क्रम ग_लिखोback.
 */
अटल स्थिर u32 ग_लिखोback_क्रमmats[] = अणु
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
पूर्ण;

पूर्णांक rcar_du_ग_लिखोback_init(काष्ठा rcar_du_device *rcdu,
			   काष्ठा rcar_du_crtc *rcrtc)
अणु
	काष्ठा drm_ग_लिखोback_connector *wb_conn = &rcrtc->ग_लिखोback;

	wb_conn->encoder.possible_crtcs = 1 << drm_crtc_index(&rcrtc->crtc);
	drm_connector_helper_add(&wb_conn->base,
				 &rcar_du_wb_conn_helper_funcs);

	वापस drm_ग_लिखोback_connector_init(&rcdu->ddev, wb_conn,
					    &rcar_du_wb_conn_funcs,
					    &rcar_du_wb_enc_helper_funcs,
					    ग_लिखोback_क्रमmats,
					    ARRAY_SIZE(ग_लिखोback_क्रमmats));
पूर्ण

व्योम rcar_du_ग_लिखोback_setup(काष्ठा rcar_du_crtc *rcrtc,
			     काष्ठा vsp1_du_ग_लिखोback_config *cfg)
अणु
	काष्ठा rcar_du_wb_conn_state *wb_state;
	काष्ठा drm_connector_state *state;
	काष्ठा rcar_du_wb_job *rjob;
	काष्ठा drm_framebuffer *fb;
	अचिन्हित पूर्णांक i;

	state = rcrtc->ग_लिखोback.base.state;
	अगर (!state || !state->ग_लिखोback_job)
		वापस;

	fb = state->ग_लिखोback_job->fb;
	rjob = state->ग_लिखोback_job->priv;
	wb_state = to_rcar_wb_conn_state(state);

	cfg->pixelक्रमmat = wb_state->क्रमmat->v4l2;
	cfg->pitch = fb->pitches[0];

	क्रम (i = 0; i < wb_state->क्रमmat->planes; ++i)
		cfg->mem[i] = sg_dma_address(rjob->sg_tables[i].sgl)
			    + fb->offsets[i];

	drm_ग_लिखोback_queue_job(&rcrtc->ग_लिखोback, state);
पूर्ण

व्योम rcar_du_ग_लिखोback_complete(काष्ठा rcar_du_crtc *rcrtc)
अणु
	drm_ग_लिखोback_संकेत_completion(&rcrtc->ग_लिखोback, 0);
पूर्ण
