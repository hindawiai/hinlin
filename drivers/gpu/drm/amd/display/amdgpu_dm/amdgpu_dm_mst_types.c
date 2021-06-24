<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश "dm_services.h"
#समावेश "amdgpu.h"
#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_dm_mst_types.h"

#समावेश "dc.h"
#समावेश "dm_helpers.h"

#समावेश "dc_link_ddc.h"

#समावेश "i2caux_interface.h"
#समावेश "dmub_cmd.h"
#अगर defined(CONFIG_DEBUG_FS)
#समावेश "amdgpu_dm_debugfs.h"
#पूर्ण_अगर

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
#समावेश "dc/dcn20/dcn20_resource.h"
#पूर्ण_अगर

अटल sमाप_प्रकार dm_dp_aux_transfer(काष्ठा drm_dp_aux *aux,
				  काष्ठा drm_dp_aux_msg *msg)
अणु
	sमाप_प्रकार result = 0;
	काष्ठा aux_payload payload;
	क्रमागत aux_वापस_code_type operation_result;

	अगर (WARN_ON(msg->size > 16))
		वापस -E2BIG;

	payload.address = msg->address;
	payload.data = msg->buffer;
	payload.length = msg->size;
	payload.reply = &msg->reply;
	payload.i2c_over_aux = (msg->request & DP_AUX_NATIVE_WRITE) == 0;
	payload.ग_लिखो = (msg->request & DP_AUX_I2C_READ) == 0;
	payload.mot = (msg->request & DP_AUX_I2C_MOT) != 0;
	payload.defer_delay = 0;

	result = dc_link_aux_transfer_raw(TO_DM_AUX(aux)->ddc_service, &payload,
				      &operation_result);

	अगर (payload.ग_लिखो && result >= 0)
		result = msg->size;

	अगर (result < 0)
		चयन (operation_result) अणु
		हाल AUX_RET_SUCCESS:
			अवरोध;
		हाल AUX_RET_ERROR_HPD_DISCON:
		हाल AUX_RET_ERROR_UNKNOWN:
		हाल AUX_RET_ERROR_INVALID_OPERATION:
		हाल AUX_RET_ERROR_PROTOCOL_ERROR:
			result = -EIO;
			अवरोध;
		हाल AUX_RET_ERROR_INVALID_REPLY:
		हाल AUX_RET_ERROR_ENGINE_ACQUIRE:
			result = -EBUSY;
			अवरोध;
		हाल AUX_RET_ERROR_TIMEOUT:
			result = -ETIMEDOUT;
			अवरोध;
		पूर्ण

	वापस result;
पूर्ण

अटल व्योम
dm_dp_mst_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *aconnector =
		to_amdgpu_dm_connector(connector);

	अगर (aconnector->dc_sink) अणु
		dc_link_हटाओ_remote_sink(aconnector->dc_link,
					   aconnector->dc_sink);
		dc_sink_release(aconnector->dc_sink);
	पूर्ण

	kमुक्त(aconnector->edid);

	drm_connector_cleanup(connector);
	drm_dp_mst_put_port_दो_स्मृति(aconnector->port);
	kमुक्त(aconnector);
पूर्ण

अटल पूर्णांक
amdgpu_dm_mst_connector_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
		to_amdgpu_dm_connector(connector);
	पूर्णांक r;

	r = drm_dp_mst_connector_late_रेजिस्टर(connector,
					       amdgpu_dm_connector->port);
	अगर (r < 0)
		वापस r;

#अगर defined(CONFIG_DEBUG_FS)
	connector_debugfs_init(amdgpu_dm_connector);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम
amdgpu_dm_mst_connector_early_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *amdgpu_dm_connector =
		to_amdgpu_dm_connector(connector);
	काष्ठा drm_dp_mst_port *port = amdgpu_dm_connector->port;

	drm_dp_mst_connector_early_unरेजिस्टर(connector, port);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs dm_dp_mst_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = dm_dp_mst_connector_destroy,
	.reset = amdgpu_dm_connector_funcs_reset,
	.atomic_duplicate_state = amdgpu_dm_connector_atomic_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_set_property = amdgpu_dm_connector_atomic_set_property,
	.atomic_get_property = amdgpu_dm_connector_atomic_get_property,
	.late_रेजिस्टर = amdgpu_dm_mst_connector_late_रेजिस्टर,
	.early_unरेजिस्टर = amdgpu_dm_mst_connector_early_unरेजिस्टर,
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
अटल bool validate_dsc_caps_on_connector(काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा dc_sink *dc_sink = aconnector->dc_sink;
	काष्ठा drm_dp_mst_port *port = aconnector->port;
	u8 dsc_caps[16] = अणु 0 पूर्ण;

	aconnector->dsc_aux = drm_dp_mst_dsc_aux_क्रम_port(port);
#अगर defined(CONFIG_HP_HOOK_WORKAROUND)
	/*
	 * drm_dp_mst_dsc_aux_क्रम_port() will वापस शून्य क्रम certain configs
	 * because it only check the dsc/fec caps of the "port variable" and not the करोck
	 *
	 * This हाल will वापस शून्य: DSC capabe MST करोck connected to a non fec/dsc capable display
	 *
	 * Workaround: explicitly check the use हाल above and use the mst करोck's aux as dsc_aux
	 *
	 */

	अगर (!aconnector->dsc_aux && !port->parent->port_parent)
		aconnector->dsc_aux = &aconnector->mst_port->dm_dp_aux.aux;
#पूर्ण_अगर
	अगर (!aconnector->dsc_aux)
		वापस false;

	अगर (drm_dp_dpcd_पढ़ो(aconnector->dsc_aux, DP_DSC_SUPPORT, dsc_caps, 16) < 0)
		वापस false;

	अगर (!dc_dsc_parse_dsc_dpcd(aconnector->dc_link->ctx->dc,
				   dsc_caps, शून्य,
				   &dc_sink->dsc_caps.dsc_dec_caps))
		वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dm_dp_mst_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	पूर्णांक ret = 0;

	अगर (!aconnector)
		वापस drm_add_edid_modes(connector, शून्य);

	अगर (!aconnector->edid) अणु
		काष्ठा edid *edid;
		edid = drm_dp_mst_get_edid(connector, &aconnector->mst_port->mst_mgr, aconnector->port);

		अगर (!edid) अणु
			drm_connector_update_edid_property(
				&aconnector->base,
				शून्य);
			वापस ret;
		पूर्ण

		aconnector->edid = edid;
	पूर्ण

	अगर (aconnector->dc_sink && aconnector->dc_sink->sink_संकेत == SIGNAL_TYPE_VIRTUAL) अणु
		dc_sink_release(aconnector->dc_sink);
		aconnector->dc_sink = शून्य;
	पूर्ण

	अगर (!aconnector->dc_sink) अणु
		काष्ठा dc_sink *dc_sink;
		काष्ठा dc_sink_init_data init_params = अणु
				.link = aconnector->dc_link,
				.sink_संकेत = SIGNAL_TYPE_DISPLAY_PORT_MST पूर्ण;
		dc_sink = dc_link_add_remote_sink(
			aconnector->dc_link,
			(uपूर्णांक8_t *)aconnector->edid,
			(aconnector->edid->extensions + 1) * EDID_LENGTH,
			&init_params);

		अगर (!dc_sink) अणु
			DRM_ERROR("Unable to add a remote sink\n");
			वापस 0;
		पूर्ण

		dc_sink->priv = aconnector;
		/* dc_link_add_remote_sink वापसs a new reference */
		aconnector->dc_sink = dc_sink;

		अगर (aconnector->dc_sink) अणु
			amdgpu_dm_update_मुक्तsync_caps(
					connector, aconnector->edid);

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
			अगर (!validate_dsc_caps_on_connector(aconnector))
				स_रखो(&aconnector->dc_sink->dsc_caps,
				       0, माप(aconnector->dc_sink->dsc_caps));
#पूर्ण_अगर
		पूर्ण
	पूर्ण

	drm_connector_update_edid_property(
					&aconnector->base, aconnector->edid);

	ret = drm_add_edid_modes(connector, aconnector->edid);

	वापस ret;
पूर्ण

अटल काष्ठा drm_encoder *
dm_mst_atomic_best_encoder(काष्ठा drm_connector *connector,
			   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *connector_state = drm_atomic_get_new_connector_state(state,
											 connector);
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(connector_state->crtc);

	वापस &adev->dm.mst_encoders[acrtc->crtc_id].base;
पूर्ण

अटल पूर्णांक
dm_dp_mst_detect(काष्ठा drm_connector *connector,
		 काष्ठा drm_modeset_acquire_ctx *ctx, bool क्रमce)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	काष्ठा amdgpu_dm_connector *master = aconnector->mst_port;

	वापस drm_dp_mst_detect_port(connector, ctx, &master->mst_mgr,
				      aconnector->port);
पूर्ण

अटल पूर्णांक dm_dp_mst_atomic_check(काष्ठा drm_connector *connector,
				काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_conn_state =
			drm_atomic_get_new_connector_state(state, connector);
	काष्ठा drm_connector_state *old_conn_state =
			drm_atomic_get_old_connector_state(state, connector);
	काष्ठा amdgpu_dm_connector *aconnector = to_amdgpu_dm_connector(connector);
	काष्ठा drm_crtc_state *new_crtc_state;
	काष्ठा drm_dp_mst_topology_mgr *mst_mgr;
	काष्ठा drm_dp_mst_port *mst_port;

	mst_port = aconnector->port;
	mst_mgr = &aconnector->mst_port->mst_mgr;

	अगर (!old_conn_state->crtc)
		वापस 0;

	अगर (new_conn_state->crtc) अणु
		new_crtc_state = drm_atomic_get_new_crtc_state(state, new_conn_state->crtc);
		अगर (!new_crtc_state ||
		    !drm_atomic_crtc_needs_modeset(new_crtc_state) ||
		    new_crtc_state->enable)
			वापस 0;
		पूर्ण

	वापस drm_dp_atomic_release_vcpi_slots(state,
						mst_mgr,
						mst_port);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs dm_dp_mst_connector_helper_funcs = अणु
	.get_modes = dm_dp_mst_get_modes,
	.mode_valid = amdgpu_dm_connector_mode_valid,
	.atomic_best_encoder = dm_mst_atomic_best_encoder,
	.detect_ctx = dm_dp_mst_detect,
	.atomic_check = dm_dp_mst_atomic_check,
पूर्ण;

अटल व्योम amdgpu_dm_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs amdgpu_dm_encoder_funcs = अणु
	.destroy = amdgpu_dm_encoder_destroy,
पूर्ण;

व्योम
dm_dp_create_fake_mst_encoders(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	पूर्णांक i;

	क्रम (i = 0; i < adev->dm.display_indexes_num; i++) अणु
		काष्ठा amdgpu_encoder *amdgpu_encoder = &adev->dm.mst_encoders[i];
		काष्ठा drm_encoder *encoder = &amdgpu_encoder->base;

		encoder->possible_crtcs = amdgpu_dm_get_encoder_crtc_mask(adev);

		drm_encoder_init(
			dev,
			&amdgpu_encoder->base,
			&amdgpu_dm_encoder_funcs,
			DRM_MODE_ENCODER_DPMST,
			शून्य);

		drm_encoder_helper_add(encoder, &amdgpu_dm_encoder_helper_funcs);
	पूर्ण
पूर्ण

अटल काष्ठा drm_connector *
dm_dp_add_mst_connector(काष्ठा drm_dp_mst_topology_mgr *mgr,
			काष्ठा drm_dp_mst_port *port,
			स्थिर अक्षर *pathprop)
अणु
	काष्ठा amdgpu_dm_connector *master = container_of(mgr, काष्ठा amdgpu_dm_connector, mst_mgr);
	काष्ठा drm_device *dev = master->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_connector *connector;
	पूर्णांक i;

	aconnector = kzalloc(माप(*aconnector), GFP_KERNEL);
	अगर (!aconnector)
		वापस शून्य;

	connector = &aconnector->base;
	aconnector->port = port;
	aconnector->mst_port = master;

	अगर (drm_connector_init(
		dev,
		connector,
		&dm_dp_mst_connector_funcs,
		DRM_MODE_CONNECTOR_DisplayPort)) अणु
		kमुक्त(aconnector);
		वापस शून्य;
	पूर्ण
	drm_connector_helper_add(connector, &dm_dp_mst_connector_helper_funcs);

	amdgpu_dm_connector_init_helper(
		&adev->dm,
		aconnector,
		DRM_MODE_CONNECTOR_DisplayPort,
		master->dc_link,
		master->connector_id);

	क्रम (i = 0; i < adev->dm.display_indexes_num; i++) अणु
		drm_connector_attach_encoder(&aconnector->base,
					     &adev->dm.mst_encoders[i].base);
	पूर्ण

	connector->max_bpc_property = master->base.max_bpc_property;
	अगर (connector->max_bpc_property)
		drm_connector_attach_max_bpc_property(connector, 8, 16);

	connector->vrr_capable_property = master->base.vrr_capable_property;
	अगर (connector->vrr_capable_property)
		drm_connector_attach_vrr_capable_property(connector);

	drm_object_attach_property(
		&connector->base,
		dev->mode_config.path_property,
		0);
	drm_object_attach_property(
		&connector->base,
		dev->mode_config.tile_property,
		0);

	drm_connector_set_path_property(connector, pathprop);

	/*
	 * Initialize connector state beक्रमe adding the connectror to drm and
	 * framebuffer lists
	 */
	amdgpu_dm_connector_funcs_reset(connector);

	drm_dp_mst_get_port_दो_स्मृति(port);

	वापस connector;
पूर्ण

अटल स्थिर काष्ठा drm_dp_mst_topology_cbs dm_mst_cbs = अणु
	.add_connector = dm_dp_add_mst_connector,
पूर्ण;

व्योम amdgpu_dm_initialize_dp_connector(काष्ठा amdgpu_display_manager *dm,
				       काष्ठा amdgpu_dm_connector *aconnector,
				       पूर्णांक link_index)
अणु
	aconnector->dm_dp_aux.aux.name =
		kaप्र_लिखो(GFP_KERNEL, "AMDGPU DM aux hw bus %d",
			  link_index);
	aconnector->dm_dp_aux.aux.transfer = dm_dp_aux_transfer;
	aconnector->dm_dp_aux.ddc_service = aconnector->dc_link->ddc;

	drm_dp_aux_init(&aconnector->dm_dp_aux.aux);
	drm_dp_cec_रेजिस्टर_connector(&aconnector->dm_dp_aux.aux,
				      &aconnector->base);

	अगर (aconnector->base.connector_type == DRM_MODE_CONNECTOR_eDP)
		वापस;

	aconnector->mst_mgr.cbs = &dm_mst_cbs;
	drm_dp_mst_topology_mgr_init(
		&aconnector->mst_mgr,
		adev_to_drm(dm->adev),
		&aconnector->dm_dp_aux.aux,
		16,
		4,
		aconnector->connector_id);

	drm_connector_attach_dp_subconnector_property(&aconnector->base);
पूर्ण

पूर्णांक dm_mst_get_pbn_भागider(काष्ठा dc_link *link)
अणु
	अगर (!link)
		वापस 0;

	वापस dc_link_bandwidth_kbps(link,
			dc_link_get_link_cap(link)) / (8 * 1000 * 54);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_DCN)

काष्ठा dsc_mst_fairness_params अणु
	काष्ठा dc_crtc_timing *timing;
	काष्ठा dc_sink *sink;
	काष्ठा dc_dsc_bw_range bw_range;
	bool compression_possible;
	काष्ठा drm_dp_mst_port *port;
	क्रमागत dsc_घड़ी_क्रमce_state घड़ी_क्रमce_enable;
	uपूर्णांक32_t num_slices_h;
	uपूर्णांक32_t num_slices_v;
	uपूर्णांक32_t bpp_overग_लिखो;
पूर्ण;

काष्ठा dsc_mst_fairness_vars अणु
	पूर्णांक pbn;
	bool dsc_enabled;
	पूर्णांक bpp_x16;
पूर्ण;

अटल पूर्णांक kbps_to_peak_pbn(पूर्णांक kbps)
अणु
	u64 peak_kbps = kbps;

	peak_kbps *= 1006;
	peak_kbps = भाग_u64(peak_kbps, 1000);
	वापस (पूर्णांक) DIV64_U64_ROUND_UP(peak_kbps * 64, (54 * 8 * 1000));
पूर्ण

अटल व्योम set_dsc_configs_from_fairness_vars(काष्ठा dsc_mst_fairness_params *params,
		काष्ठा dsc_mst_fairness_vars *vars,
		पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		स_रखो(&params[i].timing->dsc_cfg, 0, माप(params[i].timing->dsc_cfg));
		अगर (vars[i].dsc_enabled && dc_dsc_compute_config(
					params[i].sink->ctx->dc->res_pool->dscs[0],
					&params[i].sink->dsc_caps.dsc_dec_caps,
					params[i].sink->ctx->dc->debug.dsc_min_slice_height_override,
					0,
					0,
					params[i].timing,
					&params[i].timing->dsc_cfg)) अणु
			params[i].timing->flags.DSC = 1;

			अगर (params[i].bpp_overग_लिखो)
				params[i].timing->dsc_cfg.bits_per_pixel = params[i].bpp_overग_लिखो;
			अन्यथा
				params[i].timing->dsc_cfg.bits_per_pixel = vars[i].bpp_x16;

			अगर (params[i].num_slices_h)
				params[i].timing->dsc_cfg.num_slices_h = params[i].num_slices_h;

			अगर (params[i].num_slices_v)
				params[i].timing->dsc_cfg.num_slices_v = params[i].num_slices_v;
		पूर्ण अन्यथा अणु
			params[i].timing->flags.DSC = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bpp_x16_from_pbn(काष्ठा dsc_mst_fairness_params param, पूर्णांक pbn)
अणु
	काष्ठा dc_dsc_config dsc_config;
	u64 kbps;

	kbps = भाग_u64((u64)pbn * 994 * 8 * 54, 64);
	dc_dsc_compute_config(
			param.sink->ctx->dc->res_pool->dscs[0],
			&param.sink->dsc_caps.dsc_dec_caps,
			param.sink->ctx->dc->debug.dsc_min_slice_height_override,
			0,
			(पूर्णांक) kbps, param.timing, &dsc_config);

	वापस dsc_config.bits_per_pixel;
पूर्ण

अटल व्योम increase_dsc_bpp(काष्ठा drm_atomic_state *state,
			     काष्ठा dc_link *dc_link,
			     काष्ठा dsc_mst_fairness_params *params,
			     काष्ठा dsc_mst_fairness_vars *vars,
			     पूर्णांक count)
अणु
	पूर्णांक i;
	bool bpp_increased[MAX_PIPES];
	पूर्णांक initial_slack[MAX_PIPES];
	पूर्णांक min_initial_slack;
	पूर्णांक next_index;
	पूर्णांक reमुख्यing_to_increase = 0;
	पूर्णांक pbn_per_बारlot;
	पूर्णांक link_बारlots_used;
	पूर्णांक fair_pbn_alloc;

	pbn_per_बारlot = dm_mst_get_pbn_भागider(dc_link);

	क्रम (i = 0; i < count; i++) अणु
		अगर (vars[i].dsc_enabled) अणु
			initial_slack[i] = kbps_to_peak_pbn(params[i].bw_range.max_kbps) - vars[i].pbn;
			bpp_increased[i] = false;
			reमुख्यing_to_increase += 1;
		पूर्ण अन्यथा अणु
			initial_slack[i] = 0;
			bpp_increased[i] = true;
		पूर्ण
	पूर्ण

	जबतक (reमुख्यing_to_increase) अणु
		next_index = -1;
		min_initial_slack = -1;
		क्रम (i = 0; i < count; i++) अणु
			अगर (!bpp_increased[i]) अणु
				अगर (min_initial_slack == -1 || min_initial_slack > initial_slack[i]) अणु
					min_initial_slack = initial_slack[i];
					next_index = i;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (next_index == -1)
			अवरोध;

		link_बारlots_used = 0;

		क्रम (i = 0; i < count; i++)
			link_बारlots_used += DIV_ROUND_UP(vars[i].pbn, pbn_per_बारlot);

		fair_pbn_alloc = (63 - link_बारlots_used) / reमुख्यing_to_increase * pbn_per_बारlot;

		अगर (initial_slack[next_index] > fair_pbn_alloc) अणु
			vars[next_index].pbn += fair_pbn_alloc;
			अगर (drm_dp_atomic_find_vcpi_slots(state,
							  params[next_index].port->mgr,
							  params[next_index].port,
							  vars[next_index].pbn,
							  pbn_per_बारlot) < 0)
				वापस;
			अगर (!drm_dp_mst_atomic_check(state)) अणु
				vars[next_index].bpp_x16 = bpp_x16_from_pbn(params[next_index], vars[next_index].pbn);
			पूर्ण अन्यथा अणु
				vars[next_index].pbn -= fair_pbn_alloc;
				अगर (drm_dp_atomic_find_vcpi_slots(state,
								  params[next_index].port->mgr,
								  params[next_index].port,
								  vars[next_index].pbn,
								  pbn_per_बारlot) < 0)
					वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			vars[next_index].pbn += initial_slack[next_index];
			अगर (drm_dp_atomic_find_vcpi_slots(state,
							  params[next_index].port->mgr,
							  params[next_index].port,
							  vars[next_index].pbn,
							  pbn_per_बारlot) < 0)
				वापस;
			अगर (!drm_dp_mst_atomic_check(state)) अणु
				vars[next_index].bpp_x16 = params[next_index].bw_range.max_target_bpp_x16;
			पूर्ण अन्यथा अणु
				vars[next_index].pbn -= initial_slack[next_index];
				अगर (drm_dp_atomic_find_vcpi_slots(state,
								  params[next_index].port->mgr,
								  params[next_index].port,
								  vars[next_index].pbn,
								  pbn_per_बारlot) < 0)
					वापस;
			पूर्ण
		पूर्ण

		bpp_increased[next_index] = true;
		reमुख्यing_to_increase--;
	पूर्ण
पूर्ण

अटल व्योम try_disable_dsc(काष्ठा drm_atomic_state *state,
			    काष्ठा dc_link *dc_link,
			    काष्ठा dsc_mst_fairness_params *params,
			    काष्ठा dsc_mst_fairness_vars *vars,
			    पूर्णांक count)
अणु
	पूर्णांक i;
	bool tried[MAX_PIPES];
	पूर्णांक kbps_increase[MAX_PIPES];
	पूर्णांक max_kbps_increase;
	पूर्णांक next_index;
	पूर्णांक reमुख्यing_to_try = 0;

	क्रम (i = 0; i < count; i++) अणु
		अगर (vars[i].dsc_enabled
				&& vars[i].bpp_x16 == params[i].bw_range.max_target_bpp_x16
				&& params[i].घड़ी_क्रमce_enable == DSC_CLK_FORCE_DEFAULT) अणु
			kbps_increase[i] = params[i].bw_range.stream_kbps - params[i].bw_range.max_kbps;
			tried[i] = false;
			reमुख्यing_to_try += 1;
		पूर्ण अन्यथा अणु
			kbps_increase[i] = 0;
			tried[i] = true;
		पूर्ण
	पूर्ण

	जबतक (reमुख्यing_to_try) अणु
		next_index = -1;
		max_kbps_increase = -1;
		क्रम (i = 0; i < count; i++) अणु
			अगर (!tried[i]) अणु
				अगर (max_kbps_increase == -1 || max_kbps_increase < kbps_increase[i]) अणु
					max_kbps_increase = kbps_increase[i];
					next_index = i;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (next_index == -1)
			अवरोध;

		vars[next_index].pbn = kbps_to_peak_pbn(params[next_index].bw_range.stream_kbps);
		अगर (drm_dp_atomic_find_vcpi_slots(state,
						  params[next_index].port->mgr,
						  params[next_index].port,
						  vars[next_index].pbn,
						  dm_mst_get_pbn_भागider(dc_link)) < 0)
			वापस;

		अगर (!drm_dp_mst_atomic_check(state)) अणु
			vars[next_index].dsc_enabled = false;
			vars[next_index].bpp_x16 = 0;
		पूर्ण अन्यथा अणु
			vars[next_index].pbn = kbps_to_peak_pbn(params[next_index].bw_range.max_kbps);
			अगर (drm_dp_atomic_find_vcpi_slots(state,
							  params[next_index].port->mgr,
							  params[next_index].port,
							  vars[next_index].pbn,
							  dm_mst_get_pbn_भागider(dc_link)) < 0)
				वापस;
		पूर्ण

		tried[next_index] = true;
		reमुख्यing_to_try--;
	पूर्ण
पूर्ण

अटल bool compute_mst_dsc_configs_क्रम_link(काष्ठा drm_atomic_state *state,
					     काष्ठा dc_state *dc_state,
					     काष्ठा dc_link *dc_link)
अणु
	पूर्णांक i;
	काष्ठा dc_stream_state *stream;
	काष्ठा dsc_mst_fairness_params params[MAX_PIPES];
	काष्ठा dsc_mst_fairness_vars vars[MAX_PIPES];
	काष्ठा amdgpu_dm_connector *aconnector;
	पूर्णांक count = 0;
	bool debugfs_overग_लिखो = false;

	स_रखो(params, 0, माप(params));

	/* Set up params */
	क्रम (i = 0; i < dc_state->stream_count; i++) अणु
		काष्ठा dc_dsc_policy dsc_policy = अणु0पूर्ण;

		stream = dc_state->streams[i];

		अगर (stream->link != dc_link)
			जारी;

		stream->timing.flags.DSC = 0;

		params[count].timing = &stream->timing;
		params[count].sink = stream->sink;
		aconnector = (काष्ठा amdgpu_dm_connector *)stream->dm_stream_context;
		params[count].port = aconnector->port;
		params[count].घड़ी_क्रमce_enable = aconnector->dsc_settings.dsc_क्रमce_enable;
		अगर (params[count].घड़ी_क्रमce_enable == DSC_CLK_FORCE_ENABLE)
			debugfs_overग_लिखो = true;
		params[count].num_slices_h = aconnector->dsc_settings.dsc_num_slices_h;
		params[count].num_slices_v = aconnector->dsc_settings.dsc_num_slices_v;
		params[count].bpp_overग_लिखो = aconnector->dsc_settings.dsc_bits_per_pixel;
		params[count].compression_possible = stream->sink->dsc_caps.dsc_dec_caps.is_dsc_supported;
		dc_dsc_get_policy_क्रम_timing(params[count].timing, 0, &dsc_policy);
		अगर (!dc_dsc_compute_bandwidth_range(
				stream->sink->ctx->dc->res_pool->dscs[0],
				stream->sink->ctx->dc->debug.dsc_min_slice_height_override,
				dsc_policy.min_target_bpp * 16,
				dsc_policy.max_target_bpp * 16,
				&stream->sink->dsc_caps.dsc_dec_caps,
				&stream->timing, &params[count].bw_range))
			params[count].bw_range.stream_kbps = dc_bandwidth_in_kbps_from_timing(&stream->timing);

		count++;
	पूर्ण
	/* Try no compression */
	क्रम (i = 0; i < count; i++) अणु
		vars[i].pbn = kbps_to_peak_pbn(params[i].bw_range.stream_kbps);
		vars[i].dsc_enabled = false;
		vars[i].bpp_x16 = 0;
		अगर (drm_dp_atomic_find_vcpi_slots(state,
						 params[i].port->mgr,
						 params[i].port,
						 vars[i].pbn,
						 dm_mst_get_pbn_भागider(dc_link)) < 0)
			वापस false;
	पूर्ण
	अगर (!drm_dp_mst_atomic_check(state) && !debugfs_overग_लिखो) अणु
		set_dsc_configs_from_fairness_vars(params, vars, count);
		वापस true;
	पूर्ण

	/* Try max compression */
	क्रम (i = 0; i < count; i++) अणु
		अगर (params[i].compression_possible && params[i].घड़ी_क्रमce_enable != DSC_CLK_FORCE_DISABLE) अणु
			vars[i].pbn = kbps_to_peak_pbn(params[i].bw_range.min_kbps);
			vars[i].dsc_enabled = true;
			vars[i].bpp_x16 = params[i].bw_range.min_target_bpp_x16;
			अगर (drm_dp_atomic_find_vcpi_slots(state,
							  params[i].port->mgr,
							  params[i].port,
							  vars[i].pbn,
							  dm_mst_get_pbn_भागider(dc_link)) < 0)
				वापस false;
		पूर्ण अन्यथा अणु
			vars[i].pbn = kbps_to_peak_pbn(params[i].bw_range.stream_kbps);
			vars[i].dsc_enabled = false;
			vars[i].bpp_x16 = 0;
			अगर (drm_dp_atomic_find_vcpi_slots(state,
							  params[i].port->mgr,
							  params[i].port,
							  vars[i].pbn,
							  dm_mst_get_pbn_भागider(dc_link)) < 0)
				वापस false;
		पूर्ण
	पूर्ण
	अगर (drm_dp_mst_atomic_check(state))
		वापस false;

	/* Optimize degree of compression */
	increase_dsc_bpp(state, dc_link, params, vars, count);

	try_disable_dsc(state, dc_link, params, vars, count);

	set_dsc_configs_from_fairness_vars(params, vars, count);

	वापस true;
पूर्ण

bool compute_mst_dsc_configs_क्रम_state(काष्ठा drm_atomic_state *state,
				       काष्ठा dc_state *dc_state)
अणु
	पूर्णांक i, j;
	काष्ठा dc_stream_state *stream;
	bool computed_streams[MAX_PIPES];
	काष्ठा amdgpu_dm_connector *aconnector;

	क्रम (i = 0; i < dc_state->stream_count; i++)
		computed_streams[i] = false;

	क्रम (i = 0; i < dc_state->stream_count; i++) अणु
		stream = dc_state->streams[i];

		अगर (stream->संकेत != SIGNAL_TYPE_DISPLAY_PORT_MST)
			जारी;

		aconnector = (काष्ठा amdgpu_dm_connector *)stream->dm_stream_context;

		अगर (!aconnector || !aconnector->dc_sink)
			जारी;

		अगर (!aconnector->dc_sink->dsc_caps.dsc_dec_caps.is_dsc_supported)
			जारी;

		अगर (computed_streams[i])
			जारी;

		अगर (dcn20_हटाओ_stream_from_ctx(stream->ctx->dc, dc_state, stream) != DC_OK)
			वापस false;

		mutex_lock(&aconnector->mst_mgr.lock);
		अगर (!compute_mst_dsc_configs_क्रम_link(state, dc_state, stream->link)) अणु
			mutex_unlock(&aconnector->mst_mgr.lock);
			वापस false;
		पूर्ण
		mutex_unlock(&aconnector->mst_mgr.lock);

		क्रम (j = 0; j < dc_state->stream_count; j++) अणु
			अगर (dc_state->streams[j]->link == stream->link)
				computed_streams[j] = true;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dc_state->stream_count; i++) अणु
		stream = dc_state->streams[i];

		अगर (stream->timing.flags.DSC == 1)
			अगर (dc_stream_add_dsc_to_resource(stream->ctx->dc, dc_state, stream) != DC_OK)
				वापस false;
	पूर्ण

	वापस true;
पूर्ण

#पूर्ण_अगर
