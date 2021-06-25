<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश "komeda_dev.h"
#समावेश "komeda_kms.h"

अटल पूर्णांक
komeda_wb_init_data_flow(काष्ठा komeda_layer *wb_layer,
			 काष्ठा drm_connector_state *conn_st,
			 काष्ठा komeda_crtc_state *kcrtc_st,
			 काष्ठा komeda_data_flow_cfg *dflow)
अणु
	काष्ठा drm_framebuffer *fb = conn_st->ग_लिखोback_job->fb;

	स_रखो(dflow, 0, माप(*dflow));

	dflow->out_w = fb->width;
	dflow->out_h = fb->height;

	/* the ग_लिखो back data comes from the compiz */
	pipeline_composition_size(kcrtc_st, &dflow->in_w, &dflow->in_h);
	dflow->input.component = &wb_layer->base.pipeline->compiz->base;
	/* compiz करोesn't output alpha */
	dflow->pixel_blend_mode = DRM_MODE_BLEND_PIXEL_NONE;
	dflow->rot = DRM_MODE_ROTATE_0;

	komeda_complete_data_flow_cfg(wb_layer, dflow, fb);

	वापस 0;
पूर्ण

अटल पूर्णांक
komeda_wb_encoder_atomic_check(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_crtc_state *crtc_st,
			       काष्ठा drm_connector_state *conn_st)
अणु
	काष्ठा komeda_crtc_state *kcrtc_st = to_kcrtc_st(crtc_st);
	काष्ठा drm_ग_लिखोback_job *ग_लिखोback_job = conn_st->ग_लिखोback_job;
	काष्ठा komeda_layer *wb_layer;
	काष्ठा komeda_data_flow_cfg dflow;
	पूर्णांक err;

	अगर (!ग_लिखोback_job)
		वापस 0;

	अगर (!crtc_st->active) अणु
		DRM_DEBUG_ATOMIC("Cannot write the composition result out on a inactive CRTC.\n");
		वापस -EINVAL;
	पूर्ण

	wb_layer = to_kconn(to_wb_conn(conn_st->connector))->wb_layer;

	/*
	 * No need क्रम a full modested when the only connector changed is the
	 * ग_लिखोback connector.
	 */
	अगर (crtc_st->connectors_changed &&
	    is_only_changed_connector(crtc_st, conn_st->connector))
		crtc_st->connectors_changed = false;

	err = komeda_wb_init_data_flow(wb_layer, conn_st, kcrtc_st, &dflow);
	अगर (err)
		वापस err;

	अगर (dflow.en_split)
		err = komeda_build_wb_split_data_flow(wb_layer,
				conn_st, kcrtc_st, &dflow);
	अन्यथा
		err = komeda_build_wb_data_flow(wb_layer,
				conn_st, kcrtc_st, &dflow);

	वापस err;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs komeda_wb_encoder_helper_funcs = अणु
	.atomic_check = komeda_wb_encoder_atomic_check,
पूर्ण;

अटल पूर्णांक
komeda_wb_connector_get_modes(काष्ठा drm_connector *connector)
अणु
	वापस 0;
पूर्ण

अटल क्रमागत drm_mode_status
komeda_wb_connector_mode_valid(काष्ठा drm_connector *connector,
			       काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	पूर्णांक w = mode->hdisplay, h = mode->vdisplay;

	अगर ((w < mode_config->min_width) || (w > mode_config->max_width))
		वापस MODE_BAD_HVALUE;

	अगर ((h < mode_config->min_height) || (h > mode_config->max_height))
		वापस MODE_BAD_VVALUE;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs komeda_wb_conn_helper_funcs = अणु
	.get_modes	= komeda_wb_connector_get_modes,
	.mode_valid	= komeda_wb_connector_mode_valid,
पूर्ण;

अटल क्रमागत drm_connector_status
komeda_wb_connector_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	वापस connector_status_connected;
पूर्ण

अटल पूर्णांक
komeda_wb_connector_fill_modes(काष्ठा drm_connector *connector,
			       uपूर्णांक32_t maxX, uपूर्णांक32_t maxY)
अणु
	वापस 0;
पूर्ण

अटल व्योम komeda_wb_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
	kमुक्त(to_kconn(to_wb_conn(connector)));
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs komeda_wb_connector_funcs = अणु
	.reset			= drm_atomic_helper_connector_reset,
	.detect			= komeda_wb_connector_detect,
	.fill_modes		= komeda_wb_connector_fill_modes,
	.destroy		= komeda_wb_connector_destroy,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल पूर्णांक komeda_wb_connector_add(काष्ठा komeda_kms_dev *kms,
				   काष्ठा komeda_crtc *kcrtc)
अणु
	काष्ठा komeda_dev *mdev = kms->base.dev_निजी;
	काष्ठा komeda_wb_connector *kwb_conn;
	काष्ठा drm_ग_लिखोback_connector *wb_conn;
	काष्ठा drm_display_info *info;
	u32 *क्रमmats, n_क्रमmats = 0;
	पूर्णांक err;

	अगर (!kcrtc->master->wb_layer)
		वापस 0;

	kwb_conn = kzalloc(माप(*kwb_conn), GFP_KERNEL);
	अगर (!kwb_conn)
		वापस -ENOMEM;

	kwb_conn->wb_layer = kcrtc->master->wb_layer;

	wb_conn = &kwb_conn->base;
	wb_conn->encoder.possible_crtcs = BIT(drm_crtc_index(&kcrtc->base));

	क्रमmats = komeda_get_layer_fourcc_list(&mdev->fmt_tbl,
					       kwb_conn->wb_layer->layer_type,
					       &n_क्रमmats);

	err = drm_ग_लिखोback_connector_init(&kms->base, wb_conn,
					   &komeda_wb_connector_funcs,
					   &komeda_wb_encoder_helper_funcs,
					   क्रमmats, n_क्रमmats);
	komeda_put_fourcc_list(क्रमmats);
	अगर (err) अणु
		kमुक्त(kwb_conn);
		वापस err;
	पूर्ण

	drm_connector_helper_add(&wb_conn->base, &komeda_wb_conn_helper_funcs);

	info = &kwb_conn->base.base.display_info;
	info->bpc = __fls(kcrtc->master->improc->supported_color_depths);
	info->color_क्रमmats = kcrtc->master->improc->supported_color_क्रमmats;

	kcrtc->wb_conn = kwb_conn;

	वापस 0;
पूर्ण

पूर्णांक komeda_kms_add_wb_connectors(काष्ठा komeda_kms_dev *kms,
				 काष्ठा komeda_dev *mdev)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < kms->n_crtcs; i++) अणु
		err = komeda_wb_connector_add(kms, &kms->crtcs[i]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
