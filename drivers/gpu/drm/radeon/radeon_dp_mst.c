<शैली गुरु>
// SPDX-License-Identअगरier: MIT

#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "atom.h"
#समावेश "ni_reg.h"
#समावेश "radeon.h"

अटल काष्ठा radeon_encoder *radeon_dp_create_fake_mst_encoder(काष्ठा radeon_connector *connector);

अटल पूर्णांक radeon_atom_set_enc_offset(पूर्णांक id)
अणु
	अटल स्थिर पूर्णांक offsets[] = अणु EVERGREEN_CRTC0_REGISTER_OFFSET,
				       EVERGREEN_CRTC1_REGISTER_OFFSET,
				       EVERGREEN_CRTC2_REGISTER_OFFSET,
				       EVERGREEN_CRTC3_REGISTER_OFFSET,
				       EVERGREEN_CRTC4_REGISTER_OFFSET,
				       EVERGREEN_CRTC5_REGISTER_OFFSET,
				       0x13830 - 0x7030 पूर्ण;

	वापस offsets[id];
पूर्ण

अटल पूर्णांक radeon_dp_mst_set_be_cntl(काष्ठा radeon_encoder *primary,
				     काष्ठा radeon_encoder_mst *mst_enc,
				     क्रमागत radeon_hpd_id hpd, bool enable)
अणु
	काष्ठा drm_device *dev = primary->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t reg;
	पूर्णांक retries = 0;
	uपूर्णांक32_t temp;

	reg = RREG32(NI_DIG_BE_CNTL + primary->offset);

	/* set MST mode */
	reg &= ~NI_DIG_FE_DIG_MODE(7);
	reg |= NI_DIG_FE_DIG_MODE(NI_DIG_MODE_DP_MST);

	अगर (enable)
		reg |= NI_DIG_FE_SOURCE_SELECT(1 << mst_enc->fe);
	अन्यथा
		reg &= ~NI_DIG_FE_SOURCE_SELECT(1 << mst_enc->fe);

	reg |= NI_DIG_HPD_SELECT(hpd);
	DRM_DEBUG_KMS("writing 0x%08x 0x%08x\n", NI_DIG_BE_CNTL + primary->offset, reg);
	WREG32(NI_DIG_BE_CNTL + primary->offset, reg);

	अगर (enable) अणु
		uपूर्णांक32_t offset = radeon_atom_set_enc_offset(mst_enc->fe);

		करो अणु
			temp = RREG32(NI_DIG_FE_CNTL + offset);
		पूर्ण जबतक ((temp & NI_DIG_SYMCLK_FE_ON) && retries++ < 10000);
		अगर (retries == 10000)
			DRM_ERROR("timed out waiting for FE %d %d\n", primary->offset, mst_enc->fe);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_dp_mst_set_stream_attrib(काष्ठा radeon_encoder *primary,
					   पूर्णांक stream_number,
					   पूर्णांक fe,
					   पूर्णांक slots)
अणु
	काष्ठा drm_device *dev = primary->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	u32 temp, val;
	पूर्णांक retries  = 0;
	पूर्णांक satreg, satidx;

	satreg = stream_number >> 1;
	satidx = stream_number & 1;

	temp = RREG32(NI_DP_MSE_SAT0 + satreg + primary->offset);

	val = NI_DP_MSE_SAT_SLOT_COUNT0(slots) | NI_DP_MSE_SAT_SRC0(fe);

	val <<= (16 * satidx);

	temp &= ~(0xffff << (16 * satidx));

	temp |= val;

	DRM_DEBUG_KMS("writing 0x%08x 0x%08x\n", NI_DP_MSE_SAT0 + satreg + primary->offset, temp);
	WREG32(NI_DP_MSE_SAT0 + satreg + primary->offset, temp);

	WREG32(NI_DP_MSE_SAT_UPDATE + primary->offset, 1);

	करो अणु
		अचिन्हित value1, value2;
		udelay(10);
		temp = RREG32(NI_DP_MSE_SAT_UPDATE + primary->offset);

		value1 = temp & NI_DP_MSE_SAT_UPDATE_MASK;
		value2 = temp & NI_DP_MSE_16_MTP_KEEPOUT;

		अगर (!value1 && !value2)
			अवरोध;
	पूर्ण जबतक (retries++ < 50);

	अगर (retries == 10000)
		DRM_ERROR("timed out waitin for SAT update %d\n", primary->offset);

	/* MTP 16 ? */
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_dp_mst_update_stream_attribs(काष्ठा radeon_connector *mst_conn,
					       काष्ठा radeon_encoder *primary)
अणु
	काष्ठा drm_device *dev = mst_conn->base.dev;
	काष्ठा stream_attribs new_attribs[6];
	पूर्णांक i;
	पूर्णांक idx = 0;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा drm_connector *connector;

	स_रखो(new_attribs, 0, माप(new_attribs));
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_encoder *subenc;
		काष्ठा radeon_encoder_mst *mst_enc;

		radeon_connector = to_radeon_connector(connector);
		अगर (!radeon_connector->is_mst_connector)
			जारी;

		अगर (radeon_connector->mst_port != mst_conn)
			जारी;

		subenc = radeon_connector->mst_encoder;
		mst_enc = subenc->enc_priv;

		अगर (!mst_enc->enc_active)
			जारी;

		new_attribs[idx].fe = mst_enc->fe;
		new_attribs[idx].slots = drm_dp_mst_get_vcpi_slots(&mst_conn->mst_mgr, mst_enc->port);
		idx++;
	पूर्ण

	क्रम (i = 0; i < idx; i++) अणु
		अगर (new_attribs[i].fe != mst_conn->cur_stream_attribs[i].fe ||
		    new_attribs[i].slots != mst_conn->cur_stream_attribs[i].slots) अणु
			radeon_dp_mst_set_stream_attrib(primary, i, new_attribs[i].fe, new_attribs[i].slots);
			mst_conn->cur_stream_attribs[i].fe = new_attribs[i].fe;
			mst_conn->cur_stream_attribs[i].slots = new_attribs[i].slots;
		पूर्ण
	पूर्ण

	क्रम (i = idx; i < mst_conn->enabled_attribs; i++) अणु
		radeon_dp_mst_set_stream_attrib(primary, i, 0, 0);
		mst_conn->cur_stream_attribs[i].fe = 0;
		mst_conn->cur_stream_attribs[i].slots = 0;
	पूर्ण
	mst_conn->enabled_attribs = idx;
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_dp_mst_set_vcp_size(काष्ठा radeon_encoder *mst, s64 avg_समय_slots_per_mtp)
अणु
	काष्ठा drm_device *dev = mst->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder_mst *mst_enc = mst->enc_priv;
	uपूर्णांक32_t val, temp;
	uपूर्णांक32_t offset = radeon_atom_set_enc_offset(mst_enc->fe);
	पूर्णांक retries = 0;
	uपूर्णांक32_t x = drm_fixp2पूर्णांक(avg_समय_slots_per_mtp);
	uपूर्णांक32_t y = drm_fixp2पूर्णांक_उच्चमान((avg_समय_slots_per_mtp - x) << 26);

	val = NI_DP_MSE_RATE_X(x) | NI_DP_MSE_RATE_Y(y);

	WREG32(NI_DP_MSE_RATE_CNTL + offset, val);

	करो अणु
		temp = RREG32(NI_DP_MSE_RATE_UPDATE + offset);
		udelay(10);
	पूर्ण जबतक ((temp & 0x1) && (retries++ < 10000));

	अगर (retries >= 10000)
		DRM_ERROR("timed out wait for rate cntl %d\n", mst_enc->fe);
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_dp_mst_get_ddc_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा radeon_connector *master = radeon_connector->mst_port;
	काष्ठा edid *edid;
	पूर्णांक ret = 0;

	edid = drm_dp_mst_get_edid(connector, &master->mst_mgr, radeon_connector->port);
	radeon_connector->edid = edid;
	DRM_DEBUG_KMS("edid retrieved %p\n", edid);
	अगर (radeon_connector->edid) अणु
		drm_connector_update_edid_property(&radeon_connector->base, radeon_connector->edid);
		ret = drm_add_edid_modes(&radeon_connector->base, radeon_connector->edid);
		वापस ret;
	पूर्ण
	drm_connector_update_edid_property(&radeon_connector->base, शून्य);

	वापस ret;
पूर्ण

अटल पूर्णांक radeon_dp_mst_get_modes(काष्ठा drm_connector *connector)
अणु
	वापस radeon_dp_mst_get_ddc_modes(connector);
पूर्ण

अटल क्रमागत drm_mode_status
radeon_dp_mst_mode_valid(काष्ठा drm_connector *connector,
			काष्ठा drm_display_mode *mode)
अणु
	/* TODO - validate mode against available PBN क्रम link */
	अगर (mode->घड़ी < 10000)
		वापस MODE_CLOCK_LOW;

	अगर (mode->flags & DRM_MODE_FLAG_DBLCLK)
		वापस MODE_H_ILLEGAL;

	वापस MODE_OK;
पूर्ण

अटल काष्ठा
drm_encoder *radeon_mst_best_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	वापस &radeon_connector->mst_encoder->base;
पूर्ण

अटल पूर्णांक
radeon_dp_mst_detect(काष्ठा drm_connector *connector,
		     काष्ठा drm_modeset_acquire_ctx *ctx,
		     bool क्रमce)
अणु
	काष्ठा radeon_connector *radeon_connector =
		to_radeon_connector(connector);
	काष्ठा radeon_connector *master = radeon_connector->mst_port;

	अगर (drm_connector_is_unरेजिस्टरed(connector))
		वापस connector_status_disconnected;

	वापस drm_dp_mst_detect_port(connector, ctx, &master->mst_mgr,
				      radeon_connector->port);
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs radeon_dp_mst_connector_helper_funcs = अणु
	.get_modes = radeon_dp_mst_get_modes,
	.mode_valid = radeon_dp_mst_mode_valid,
	.best_encoder = radeon_mst_best_encoder,
	.detect_ctx = radeon_dp_mst_detect,
पूर्ण;

अटल व्योम
radeon_dp_mst_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा radeon_encoder *radeon_encoder = radeon_connector->mst_encoder;

	drm_encoder_cleanup(&radeon_encoder->base);
	kमुक्त(radeon_encoder);
	drm_connector_cleanup(connector);
	kमुक्त(radeon_connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs radeon_dp_mst_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.destroy = radeon_dp_mst_connector_destroy,
पूर्ण;

अटल काष्ठा drm_connector *radeon_dp_add_mst_connector(काष्ठा drm_dp_mst_topology_mgr *mgr,
							 काष्ठा drm_dp_mst_port *port,
							 स्थिर अक्षर *pathprop)
अणु
	काष्ठा radeon_connector *master = container_of(mgr, काष्ठा radeon_connector, mst_mgr);
	काष्ठा drm_device *dev = master->base.dev;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा drm_connector *connector;

	radeon_connector = kzalloc(माप(*radeon_connector), GFP_KERNEL);
	अगर (!radeon_connector)
		वापस शून्य;

	radeon_connector->is_mst_connector = true;
	connector = &radeon_connector->base;
	radeon_connector->port = port;
	radeon_connector->mst_port = master;
	DRM_DEBUG_KMS("\n");

	drm_connector_init(dev, connector, &radeon_dp_mst_connector_funcs, DRM_MODE_CONNECTOR_DisplayPort);
	drm_connector_helper_add(connector, &radeon_dp_mst_connector_helper_funcs);
	radeon_connector->mst_encoder = radeon_dp_create_fake_mst_encoder(master);

	drm_object_attach_property(&connector->base, dev->mode_config.path_property, 0);
	drm_object_attach_property(&connector->base, dev->mode_config.tile_property, 0);
	drm_connector_set_path_property(connector, pathprop);

	वापस connector;
पूर्ण

अटल स्थिर काष्ठा drm_dp_mst_topology_cbs mst_cbs = अणु
	.add_connector = radeon_dp_add_mst_connector,
पूर्ण;

अटल काष्ठा
radeon_connector *radeon_mst_find_connector(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_connector *connector;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		अगर (!connector->encoder)
			जारी;
		अगर (!radeon_connector->is_mst_connector)
			जारी;

		DRM_DEBUG_KMS("checking %p vs %p\n", connector->encoder, encoder);
		अगर (connector->encoder == encoder)
			वापस radeon_connector;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम radeon_dp_mst_prepare_pll(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode)
अणु
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(radeon_crtc->encoder);
	काष्ठा radeon_encoder_mst *mst_enc = radeon_encoder->enc_priv;
	काष्ठा radeon_connector *radeon_connector = radeon_mst_find_connector(&radeon_encoder->base);
	पूर्णांक dp_घड़ी;
	काष्ठा radeon_connector_atom_dig *dig_connector = mst_enc->connector->con_priv;

	अगर (radeon_connector) अणु
		radeon_connector->pixelघड़ी_क्रम_modeset = mode->घड़ी;
		अगर (radeon_connector->base.display_info.bpc)
			radeon_crtc->bpc = radeon_connector->base.display_info.bpc;
		अन्यथा
			radeon_crtc->bpc = 8;
	पूर्ण

	DRM_DEBUG_KMS("dp_clock %p %d\n", dig_connector, dig_connector->dp_घड़ी);
	dp_घड़ी = dig_connector->dp_घड़ी;
	radeon_crtc->ss_enabled =
		radeon_atombios_get_asic_ss_info(rdev, &radeon_crtc->ss,
						 ASIC_INTERNAL_SS_ON_DP,
						 dp_घड़ी);
पूर्ण

अटल व्योम
radeon_mst_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder, *primary;
	काष्ठा radeon_encoder_mst *mst_enc;
	काष्ठा radeon_encoder_atom_dig *dig_enc;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा drm_crtc *crtc;
	काष्ठा radeon_crtc *radeon_crtc;
	पूर्णांक slots;
	s64 fixed_pbn, fixed_pbn_per_slot, avg_समय_slots_per_mtp;
	अगर (!ASIC_IS_DCE5(rdev)) अणु
		DRM_ERROR("got mst dpms on non-DCE5\n");
		वापस;
	पूर्ण

	radeon_connector = radeon_mst_find_connector(encoder);
	अगर (!radeon_connector)
		वापस;

	radeon_encoder = to_radeon_encoder(encoder);

	mst_enc = radeon_encoder->enc_priv;

	primary = mst_enc->primary;

	dig_enc = primary->enc_priv;

	crtc = encoder->crtc;
	DRM_DEBUG_KMS("got connector %d\n", dig_enc->active_mst_links);

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		dig_enc->active_mst_links++;

		radeon_crtc = to_radeon_crtc(crtc);

		अगर (dig_enc->active_mst_links == 1) अणु
			mst_enc->fe = dig_enc->dig_encoder;
			mst_enc->fe_from_be = true;
			atombios_set_mst_encoder_crtc_source(encoder, mst_enc->fe);

			atombios_dig_encoder_setup(&primary->base, ATOM_ENCODER_CMD_SETUP, 0);
			atombios_dig_transmitter_setup2(&primary->base, ATOM_TRANSMITTER_ACTION_ENABLE,
							0, 0, dig_enc->dig_encoder);

			अगर (radeon_dp_needs_link_train(mst_enc->connector) ||
			    dig_enc->active_mst_links == 1) अणु
				radeon_dp_link_train(&primary->base, &mst_enc->connector->base);
			पूर्ण

		पूर्ण अन्यथा अणु
			mst_enc->fe = radeon_atom_pick_dig_encoder(encoder, radeon_crtc->crtc_id);
			अगर (mst_enc->fe == -1)
				DRM_ERROR("failed to get frontend for dig encoder\n");
			mst_enc->fe_from_be = false;
			atombios_set_mst_encoder_crtc_source(encoder, mst_enc->fe);
		पूर्ण

		DRM_DEBUG_KMS("dig encoder is %d %d %d\n", dig_enc->dig_encoder,
			      dig_enc->linkb, radeon_crtc->crtc_id);

		slots = drm_dp_find_vcpi_slots(&radeon_connector->mst_port->mst_mgr,
					       mst_enc->pbn);
		drm_dp_mst_allocate_vcpi(&radeon_connector->mst_port->mst_mgr,
					 radeon_connector->port,
					 mst_enc->pbn, slots);
		drm_dp_update_payload_part1(&radeon_connector->mst_port->mst_mgr);

		radeon_dp_mst_set_be_cntl(primary, mst_enc,
					  radeon_connector->mst_port->hpd.hpd, true);

		mst_enc->enc_active = true;
		radeon_dp_mst_update_stream_attribs(radeon_connector->mst_port, primary);

		fixed_pbn = drm_पूर्णांक2fixp(mst_enc->pbn);
		fixed_pbn_per_slot = drm_पूर्णांक2fixp(radeon_connector->mst_port->mst_mgr.pbn_भाग);
		avg_समय_slots_per_mtp = drm_fixp_भाग(fixed_pbn, fixed_pbn_per_slot);
		radeon_dp_mst_set_vcp_size(radeon_encoder, avg_समय_slots_per_mtp);

		atombios_dig_encoder_setup2(&primary->base, ATOM_ENCODER_CMD_DP_VIDEO_ON, 0,
					    mst_enc->fe);
		drm_dp_check_act_status(&radeon_connector->mst_port->mst_mgr);

		drm_dp_update_payload_part2(&radeon_connector->mst_port->mst_mgr);

		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		DRM_ERROR("DPMS OFF %d\n", dig_enc->active_mst_links);

		अगर (!mst_enc->enc_active)
			वापस;

		drm_dp_mst_reset_vcpi_slots(&radeon_connector->mst_port->mst_mgr, mst_enc->port);
		drm_dp_update_payload_part1(&radeon_connector->mst_port->mst_mgr);

		drm_dp_check_act_status(&radeon_connector->mst_port->mst_mgr);
		/* and this can also fail */
		drm_dp_update_payload_part2(&radeon_connector->mst_port->mst_mgr);

		drm_dp_mst_deallocate_vcpi(&radeon_connector->mst_port->mst_mgr, mst_enc->port);

		mst_enc->enc_active = false;
		radeon_dp_mst_update_stream_attribs(radeon_connector->mst_port, primary);

		radeon_dp_mst_set_be_cntl(primary, mst_enc,
					  radeon_connector->mst_port->hpd.hpd, false);
		atombios_dig_encoder_setup2(&primary->base, ATOM_ENCODER_CMD_DP_VIDEO_OFF, 0,
					    mst_enc->fe);

		अगर (!mst_enc->fe_from_be)
			radeon_atom_release_dig_encoder(rdev, mst_enc->fe);

		mst_enc->fe_from_be = false;
		dig_enc->active_mst_links--;
		अगर (dig_enc->active_mst_links == 0) अणु
			/* drop link */
		पूर्ण

		अवरोध;
	पूर्ण

पूर्ण

अटल bool radeon_mst_mode_fixup(काष्ठा drm_encoder *encoder,
				   स्थिर काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा radeon_encoder_mst *mst_enc;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_connector_atom_dig *dig_connector;
	पूर्णांक bpp = 24;

	mst_enc = radeon_encoder->enc_priv;

	mst_enc->pbn = drm_dp_calc_pbn_mode(adjusted_mode->घड़ी, bpp, false);

	mst_enc->primary->active_device = mst_enc->primary->devices & mst_enc->connector->devices;
	DRM_DEBUG_KMS("setting active device to %08x from %08x %08x for encoder %d\n",
		      mst_enc->primary->active_device, mst_enc->primary->devices,
		      mst_enc->connector->devices, mst_enc->primary->base.encoder_type);


	drm_mode_set_crtcinfo(adjusted_mode, 0);
	dig_connector = mst_enc->connector->con_priv;
	dig_connector->dp_lane_count = drm_dp_max_lane_count(dig_connector->dpcd);
	dig_connector->dp_घड़ी = drm_dp_max_link_rate(dig_connector->dpcd);
	DRM_DEBUG_KMS("dig clock %p %d %d\n", dig_connector,
		      dig_connector->dp_lane_count, dig_connector->dp_घड़ी);
	वापस true;
पूर्ण

अटल व्योम radeon_mst_encoder_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा radeon_encoder *radeon_encoder, *primary;
	काष्ठा radeon_encoder_mst *mst_enc;
	काष्ठा radeon_encoder_atom_dig *dig_enc;

	radeon_connector = radeon_mst_find_connector(encoder);
	अगर (!radeon_connector) अणु
		DRM_DEBUG_KMS("failed to find connector %p\n", encoder);
		वापस;
	पूर्ण
	radeon_encoder = to_radeon_encoder(encoder);

	radeon_mst_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	mst_enc = radeon_encoder->enc_priv;

	primary = mst_enc->primary;

	dig_enc = primary->enc_priv;

	mst_enc->port = radeon_connector->port;

	अगर (dig_enc->dig_encoder == -1) अणु
		dig_enc->dig_encoder = radeon_atom_pick_dig_encoder(&primary->base, -1);
		primary->offset = radeon_atom_set_enc_offset(dig_enc->dig_encoder);
		atombios_set_mst_encoder_crtc_source(encoder, dig_enc->dig_encoder);


	पूर्ण
	DRM_DEBUG_KMS("%d %d\n", dig_enc->dig_encoder, primary->offset);
पूर्ण

अटल व्योम
radeon_mst_encoder_mode_set(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा drm_display_mode *adjusted_mode)
अणु
	DRM_DEBUG_KMS("\n");
पूर्ण

अटल व्योम radeon_mst_encoder_commit(काष्ठा drm_encoder *encoder)
अणु
	radeon_mst_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
	DRM_DEBUG_KMS("\n");
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_mst_helper_funcs = अणु
	.dpms = radeon_mst_encoder_dpms,
	.mode_fixup = radeon_mst_mode_fixup,
	.prepare = radeon_mst_encoder_prepare,
	.mode_set = radeon_mst_encoder_mode_set,
	.commit = radeon_mst_encoder_commit,
पूर्ण;

अटल व्योम radeon_dp_mst_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	drm_encoder_cleanup(encoder);
	kमुक्त(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs radeon_dp_mst_enc_funcs = अणु
	.destroy = radeon_dp_mst_encoder_destroy,
पूर्ण;

अटल काष्ठा radeon_encoder *
radeon_dp_create_fake_mst_encoder(काष्ठा radeon_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder;
	काष्ठा radeon_encoder_mst *mst_enc;
	काष्ठा drm_encoder *encoder;
	स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs = connector->base.helper_निजी;
	काष्ठा drm_encoder *enc_master = connector_funcs->best_encoder(&connector->base);

	DRM_DEBUG_KMS("enc master is %p\n", enc_master);
	radeon_encoder = kzalloc(माप(*radeon_encoder), GFP_KERNEL);
	अगर (!radeon_encoder)
		वापस शून्य;

	radeon_encoder->enc_priv = kzalloc(माप(*mst_enc), GFP_KERNEL);
	अगर (!radeon_encoder->enc_priv) अणु
		kमुक्त(radeon_encoder);
		वापस शून्य;
	पूर्ण
	encoder = &radeon_encoder->base;
	चयन (rdev->num_crtc) अणु
	हाल 1:
		encoder->possible_crtcs = 0x1;
		अवरोध;
	हाल 2:
	शेष:
		encoder->possible_crtcs = 0x3;
		अवरोध;
	हाल 4:
		encoder->possible_crtcs = 0xf;
		अवरोध;
	हाल 6:
		encoder->possible_crtcs = 0x3f;
		अवरोध;
	पूर्ण

	drm_encoder_init(dev, &radeon_encoder->base, &radeon_dp_mst_enc_funcs,
			 DRM_MODE_ENCODER_DPMST, शून्य);
	drm_encoder_helper_add(encoder, &radeon_mst_helper_funcs);

	mst_enc = radeon_encoder->enc_priv;
	mst_enc->connector = connector;
	mst_enc->primary = to_radeon_encoder(enc_master);
	radeon_encoder->is_mst_encoder = true;
	वापस radeon_encoder;
पूर्ण

पूर्णांक
radeon_dp_mst_init(काष्ठा radeon_connector *radeon_connector)
अणु
	काष्ठा drm_device *dev = radeon_connector->base.dev;

	अगर (!radeon_connector->ddc_bus->has_aux)
		वापस 0;

	radeon_connector->mst_mgr.cbs = &mst_cbs;
	वापस drm_dp_mst_topology_mgr_init(&radeon_connector->mst_mgr, dev,
					    &radeon_connector->ddc_bus->aux, 16, 6,
					    radeon_connector->base.base.id);
पूर्ण

पूर्णांक
radeon_dp_mst_probe(काष्ठा radeon_connector *radeon_connector)
अणु
	काष्ठा radeon_connector_atom_dig *dig_connector = radeon_connector->con_priv;
	काष्ठा drm_device *dev = radeon_connector->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक ret;
	u8 msg[1];

	अगर (!radeon_mst)
		वापस 0;

	अगर (!ASIC_IS_DCE5(rdev))
		वापस 0;

	अगर (dig_connector->dpcd[DP_DPCD_REV] < 0x12)
		वापस 0;

	ret = drm_dp_dpcd_पढ़ो(&radeon_connector->ddc_bus->aux, DP_MSTM_CAP, msg,
			       1);
	अगर (ret) अणु
		अगर (msg[0] & DP_MST_CAP) अणु
			DRM_DEBUG_KMS("Sink is MST capable\n");
			dig_connector->is_mst = true;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("Sink is not MST capable\n");
			dig_connector->is_mst = false;
		पूर्ण

	पूर्ण
	drm_dp_mst_topology_mgr_set_mst(&radeon_connector->mst_mgr,
					dig_connector->is_mst);
	वापस dig_connector->is_mst;
पूर्ण

पूर्णांक
radeon_dp_mst_check_status(काष्ठा radeon_connector *radeon_connector)
अणु
	काष्ठा radeon_connector_atom_dig *dig_connector = radeon_connector->con_priv;
	पूर्णांक retry;

	अगर (dig_connector->is_mst) अणु
		u8 esi[16] = अणु 0 पूर्ण;
		पूर्णांक dret;
		पूर्णांक ret = 0;
		bool handled;

		dret = drm_dp_dpcd_पढ़ो(&radeon_connector->ddc_bus->aux,
				       DP_SINK_COUNT_ESI, esi, 8);
go_again:
		अगर (dret == 8) अणु
			DRM_DEBUG_KMS("got esi %3ph\n", esi);
			ret = drm_dp_mst_hpd_irq(&radeon_connector->mst_mgr, esi, &handled);

			अगर (handled) अणु
				क्रम (retry = 0; retry < 3; retry++) अणु
					पूर्णांक wret;
					wret = drm_dp_dpcd_ग_लिखो(&radeon_connector->ddc_bus->aux,
								 DP_SINK_COUNT_ESI + 1, &esi[1], 3);
					अगर (wret == 3)
						अवरोध;
				पूर्ण

				dret = drm_dp_dpcd_पढ़ो(&radeon_connector->ddc_bus->aux,
							DP_SINK_COUNT_ESI, esi, 8);
				अगर (dret == 8) अणु
					DRM_DEBUG_KMS("got esi2 %3ph\n", esi);
					जाओ go_again;
				पूर्ण
			पूर्ण अन्यथा
				ret = 0;

			वापस ret;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("failed to get ESI - device may have failed %d\n", ret);
			dig_connector->is_mst = false;
			drm_dp_mst_topology_mgr_set_mst(&radeon_connector->mst_mgr,
							dig_connector->is_mst);
			/* send a hotplug event */
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक radeon_debugfs_mst_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा radeon_connector_atom_dig *dig_connector;
	पूर्णांक i;

	drm_modeset_lock_all(dev);
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		अगर (connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		radeon_connector = to_radeon_connector(connector);
		dig_connector = radeon_connector->con_priv;
		अगर (radeon_connector->is_mst_connector)
			जारी;
		अगर (!dig_connector->is_mst)
			जारी;
		drm_dp_mst_dump_topology(m, &radeon_connector->mst_mgr);

		क्रम (i = 0; i < radeon_connector->enabled_attribs; i++)
			seq_म_लिखो(m, "attrib %d: %d %d\n", i,
				   radeon_connector->cur_stream_attribs[i].fe,
				   radeon_connector->cur_stream_attribs[i].slots);
	पूर्ण
	drm_modeset_unlock_all(dev);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(radeon_debugfs_mst_info);
#पूर्ण_अगर

व्योम radeon_mst_debugfs_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("radeon_mst_info", 0444, root, rdev,
			    &radeon_debugfs_mst_info_fops);

#पूर्ण_अगर
पूर्ण
