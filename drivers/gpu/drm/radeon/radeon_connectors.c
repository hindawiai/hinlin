<शैली गुरु>
/*
 * Copyright 2007-8 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alex Deucher
 */

#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/radeon_drm.h>
#समावेश "radeon.h"
#समावेश "radeon_audio.h"
#समावेश "atom.h"

#समावेश <linux/pm_runसमय.स>
#समावेश <linux/vga_चयनeroo.h>

अटल पूर्णांक radeon_dp_handle_hpd(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	पूर्णांक ret;

	ret = radeon_dp_mst_check_status(radeon_connector);
	अगर (ret == -EINVAL)
		वापस 1;
	वापस 0;
पूर्ण
व्योम radeon_connector_hotplug(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) अणु
		काष्ठा radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;

		अगर (radeon_connector->is_mst_connector)
			वापस;
		अगर (dig_connector->is_mst) अणु
			radeon_dp_handle_hpd(connector);
			वापस;
		पूर्ण
	पूर्ण
	/* bail अगर the connector करोes not have hpd pin, e.g.,
	 * VGA, TV, etc.
	 */
	अगर (radeon_connector->hpd.hpd == RADEON_HPD_NONE)
		वापस;

	radeon_hpd_set_polarity(rdev, radeon_connector->hpd.hpd);

	/* अगर the connector is alपढ़ोy off, करोn't turn it back on */
	/* FIXME: This access isn't रक्षित by any locks. */
	अगर (connector->dpms != DRM_MODE_DPMS_ON)
		वापस;

	/* just deal with DP (not eDP) here. */
	अगर (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) अणु
		काष्ठा radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;

		/* अगर existing sink type was not DP no need to retrain */
		अगर (dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_DISPLAYPORT)
			वापस;

		/* first get sink type as it may be reset after (un)plug */
		dig_connector->dp_sink_type = radeon_dp_माला_लोinktype(radeon_connector);
		/* करोn't करो anything अगर sink is not display port, i.e.,
		 * passive dp->(dvi|hdmi) adaptor
		 */
		अगर (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT &&
		    radeon_hpd_sense(rdev, radeon_connector->hpd.hpd) &&
		    radeon_dp_needs_link_train(radeon_connector)) अणु
			/* Don't start link training beक्रमe we have the DPCD */
			अगर (!radeon_dp_getdpcd(radeon_connector))
				वापस;

			/* Turn the connector off and back on immediately, which
			 * will trigger link training
			 */
			drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
			drm_helper_connector_dpms(connector, DRM_MODE_DPMS_ON);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम radeon_property_change_mode(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_crtc *crtc = encoder->crtc;

	अगर (crtc && crtc->enabled) अणु
		drm_crtc_helper_set_mode(crtc, &crtc->mode,
					 crtc->x, crtc->y, crtc->primary->fb);
	पूर्ण
पूर्ण

पूर्णांक radeon_get_monitor_bpc(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा radeon_connector_atom_dig *dig_connector;
	पूर्णांक bpc = 8;
	पूर्णांक mode_घड़ी, max_पंचांगds_घड़ी;

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_HDMIB:
		अगर (radeon_connector->use_digital) अणु
			अगर (drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
				अगर (connector->display_info.bpc)
					bpc = connector->display_info.bpc;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVID:
	हाल DRM_MODE_CONNECTOR_HDMIA:
		अगर (drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
			अगर (connector->display_info.bpc)
				bpc = connector->display_info.bpc;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = radeon_connector->con_priv;
		अगर ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP) ||
		    drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
			अगर (connector->display_info.bpc)
				bpc = connector->display_info.bpc;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_eDP:
	हाल DRM_MODE_CONNECTOR_LVDS:
		अगर (connector->display_info.bpc)
			bpc = connector->display_info.bpc;
		अन्यथा अगर (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE5(rdev)) अणु
			स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs =
				connector->helper_निजी;
			काष्ठा drm_encoder *encoder = connector_funcs->best_encoder(connector);
			काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
			काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

			अगर (dig->lcd_misc & ATOM_PANEL_MISC_V13_6BIT_PER_COLOR)
				bpc = 6;
			अन्यथा अगर (dig->lcd_misc & ATOM_PANEL_MISC_V13_8BIT_PER_COLOR)
				bpc = 8;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
		/* hdmi deep color only implemented on DCE4+ */
		अगर ((bpc > 8) && !ASIC_IS_DCE4(rdev)) अणु
			DRM_DEBUG("%s: HDMI deep color %d bpc unsupported. Using 8 bpc.\n",
					  connector->name, bpc);
			bpc = 8;
		पूर्ण

		/*
		 * Pre DCE-8 hw can't handle > 12 bpc, and more than 12 bpc doesn't make
		 * much sense without support क्रम > 12 bpc framebuffers. RGB 4:4:4 at
		 * 12 bpc is always supported on hdmi deep color sinks, as this is
		 * required by the HDMI-1.3 spec. Clamp to a safe 12 bpc maximum.
		 */
		अगर (bpc > 12) अणु
			DRM_DEBUG("%s: HDMI deep color %d bpc unsupported. Using 12 bpc.\n",
					  connector->name, bpc);
			bpc = 12;
		पूर्ण

		/* Any defined maximum पंचांगds घड़ी limit we must not exceed? */
		अगर (connector->display_info.max_पंचांगds_घड़ी > 0) अणु
			/* mode_घड़ी is घड़ी in kHz क्रम mode to be modeset on this connector */
			mode_घड़ी = radeon_connector->pixelघड़ी_क्रम_modeset;

			/* Maximum allowable input घड़ी in kHz */
			max_पंचांगds_घड़ी = connector->display_info.max_पंचांगds_घड़ी;

			DRM_DEBUG("%s: hdmi mode dotclock %d kHz, max tmds input clock %d kHz.\n",
					  connector->name, mode_घड़ी, max_पंचांगds_घड़ी);

			/* Check अगर bpc is within घड़ी limit. Try to degrade gracefully otherwise */
			अगर ((bpc == 12) && (mode_घड़ी * 3/2 > max_पंचांगds_घड़ी)) अणु
				अगर ((connector->display_info.edid_hdmi_dc_modes & DRM_EDID_HDMI_DC_30) &&
					(mode_घड़ी * 5/4 <= max_पंचांगds_घड़ी))
					bpc = 10;
				अन्यथा
					bpc = 8;

				DRM_DEBUG("%s: HDMI deep color 12 bpc exceeds max tmds clock. Using %d bpc.\n",
						  connector->name, bpc);
			पूर्ण

			अगर ((bpc == 10) && (mode_घड़ी * 5/4 > max_पंचांगds_घड़ी)) अणु
				bpc = 8;
				DRM_DEBUG("%s: HDMI deep color 10 bpc exceeds max tmds clock. Using %d bpc.\n",
						  connector->name, bpc);
			पूर्ण
		पूर्ण
		अन्यथा अगर (bpc > 8) अणु
			/* max_पंचांगds_घड़ी missing, but hdmi spec mandates it क्रम deep color. */
			DRM_DEBUG("%s: Required max tmds clock for HDMI deep color missing. Using 8 bpc.\n",
					  connector->name);
			bpc = 8;
		पूर्ण
	पूर्ण

	अगर ((radeon_deep_color == 0) && (bpc > 8)) अणु
		DRM_DEBUG("%s: Deep color disabled. Set radeon module param deep_color=1 to enable.\n",
				  connector->name);
		bpc = 8;
	पूर्ण

	DRM_DEBUG("%s: Display bpc=%d, returned bpc=%d\n",
			  connector->name, connector->display_info.bpc, bpc);

	वापस bpc;
पूर्ण

अटल व्योम
radeon_connector_update_scratch_regs(काष्ठा drm_connector *connector, क्रमागत drm_connector_status status)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_encoder *best_encoder;
	काष्ठा drm_encoder *encoder;
	स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs = connector->helper_निजी;
	bool connected;

	best_encoder = connector_funcs->best_encoder(connector);

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		अगर ((encoder == best_encoder) && (status == connector_status_connected))
			connected = true;
		अन्यथा
			connected = false;

		अगर (rdev->is_atom_bios)
			radeon_atombios_connected_scratch_regs(connector, encoder, connected);
		अन्यथा
			radeon_combios_connected_scratch_regs(connector, encoder, connected);
	पूर्ण
पूर्ण

अटल काष्ठा drm_encoder *radeon_find_encoder(काष्ठा drm_connector *connector, पूर्णांक encoder_type)
अणु
	काष्ठा drm_encoder *encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		अगर (encoder->encoder_type == encoder_type)
			वापस encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा edid *radeon_connector_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा drm_property_blob *edid_blob = connector->edid_blob_ptr;

	अगर (radeon_connector->edid) अणु
		वापस radeon_connector->edid;
	पूर्ण अन्यथा अगर (edid_blob) अणु
		काष्ठा edid *edid = kmemdup(edid_blob->data, edid_blob->length, GFP_KERNEL);
		अगर (edid)
			radeon_connector->edid = edid;
	पूर्ण
	वापस radeon_connector->edid;
पूर्ण

अटल व्योम radeon_connector_get_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	अगर (radeon_connector->edid)
		वापस;

	/* on hw with routers, select right port */
	अगर (radeon_connector->router.ddc_valid)
		radeon_router_select_ddc_port(radeon_connector);

	अगर ((radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
	     ENCODER_OBJECT_ID_NONE) &&
	    radeon_connector->ddc_bus->has_aux) अणु
		radeon_connector->edid = drm_get_edid(connector,
						      &radeon_connector->ddc_bus->aux.ddc);
	पूर्ण अन्यथा अगर ((connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) ||
		   (connector->connector_type == DRM_MODE_CONNECTOR_eDP)) अणु
		काष्ठा radeon_connector_atom_dig *dig = radeon_connector->con_priv;

		अगर ((dig->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT ||
		     dig->dp_sink_type == CONNECTOR_OBJECT_ID_eDP) &&
		    radeon_connector->ddc_bus->has_aux)
			radeon_connector->edid = drm_get_edid(&radeon_connector->base,
							      &radeon_connector->ddc_bus->aux.ddc);
		अन्यथा अगर (radeon_connector->ddc_bus)
			radeon_connector->edid = drm_get_edid(&radeon_connector->base,
							      &radeon_connector->ddc_bus->adapter);
	पूर्ण अन्यथा अगर (vga_चयनeroo_handler_flags() & VGA_SWITCHEROO_CAN_SWITCH_DDC &&
		   connector->connector_type == DRM_MODE_CONNECTOR_LVDS &&
		   radeon_connector->ddc_bus) अणु
		radeon_connector->edid = drm_get_edid_चयनeroo(&radeon_connector->base,
								 &radeon_connector->ddc_bus->adapter);
	पूर्ण अन्यथा अगर (radeon_connector->ddc_bus) अणु
		radeon_connector->edid = drm_get_edid(&radeon_connector->base,
						      &radeon_connector->ddc_bus->adapter);
	पूर्ण

	अगर (!radeon_connector->edid) अणु
		/* करोn't fetch the edid from the vbios अगर ddc fails and runpm is
		 * enabled so we report disconnected.
		 */
		अगर ((rdev->flags & RADEON_IS_PX) && (radeon_runसमय_pm != 0))
			वापस;

		अगर (rdev->is_atom_bios) अणु
			/* some laptops provide a hardcoded edid in rom क्रम LCDs */
			अगर (((connector->connector_type == DRM_MODE_CONNECTOR_LVDS) ||
			     (connector->connector_type == DRM_MODE_CONNECTOR_eDP)))
				radeon_connector->edid = radeon_bios_get_hardcoded_edid(rdev);
		पूर्ण अन्यथा अणु
			/* some servers provide a hardcoded edid in rom क्रम KVMs */
			radeon_connector->edid = radeon_bios_get_hardcoded_edid(rdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम radeon_connector_मुक्त_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	अगर (radeon_connector->edid) अणु
		kमुक्त(radeon_connector->edid);
		radeon_connector->edid = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_ddc_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	पूर्णांक ret;

	अगर (radeon_connector->edid) अणु
		drm_connector_update_edid_property(connector, radeon_connector->edid);
		ret = drm_add_edid_modes(connector, radeon_connector->edid);
		वापस ret;
	पूर्ण
	drm_connector_update_edid_property(connector, शून्य);
	वापस 0;
पूर्ण

अटल काष्ठा drm_encoder *radeon_best_single_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;

	/* pick the first one */
	drm_connector_क्रम_each_possible_encoder(connector, encoder)
		वापस encoder;

	वापस शून्य;
पूर्ण

अटल व्योम radeon_get_native_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder = radeon_best_single_encoder(connector);
	काष्ठा radeon_encoder *radeon_encoder;

	अगर (encoder == शून्य)
		वापस;

	radeon_encoder = to_radeon_encoder(encoder);

	अगर (!list_empty(&connector->probed_modes)) अणु
		काष्ठा drm_display_mode *preferred_mode =
			list_first_entry(&connector->probed_modes,
					 काष्ठा drm_display_mode, head);

		radeon_encoder->native_mode = *preferred_mode;
	पूर्ण अन्यथा अणु
		radeon_encoder->native_mode.घड़ी = 0;
	पूर्ण
पूर्ण

/*
 * radeon_connector_analog_encoder_conflict_solve
 * - search क्रम other connectors sharing this encoder
 *   अगर priority is true, then set them disconnected अगर this is connected
 *   अगर priority is false, set us disconnected अगर they are connected
 */
अटल क्रमागत drm_connector_status
radeon_connector_analog_encoder_conflict_solve(काष्ठा drm_connector *connector,
					       काष्ठा drm_encoder *encoder,
					       क्रमागत drm_connector_status current_status,
					       bool priority)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_connector *conflict;
	काष्ठा radeon_connector *radeon_conflict;

	list_क्रम_each_entry(conflict, &dev->mode_config.connector_list, head) अणु
		काष्ठा drm_encoder *enc;

		अगर (conflict == connector)
			जारी;

		radeon_conflict = to_radeon_connector(conflict);

		drm_connector_क्रम_each_possible_encoder(conflict, enc) अणु
			/* अगर the IDs match */
			अगर (enc == encoder) अणु
				अगर (conflict->status != connector_status_connected)
					जारी;

				अगर (radeon_conflict->use_digital)
					जारी;

				अगर (priority) अणु
					DRM_DEBUG_KMS("1: conflicting encoders switching off %s\n",
						      conflict->name);
					DRM_DEBUG_KMS("in favor of %s\n",
						      connector->name);
					conflict->status = connector_status_disconnected;
					radeon_connector_update_scratch_regs(conflict, connector_status_disconnected);
				पूर्ण अन्यथा अणु
					DRM_DEBUG_KMS("2: conflicting encoders switching off %s\n",
						      connector->name);
					DRM_DEBUG_KMS("in favor of %s\n",
						      conflict->name);
					current_status = connector_status_disconnected;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस current_status;

पूर्ण

अटल काष्ठा drm_display_mode *radeon_fp_native_mode(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;

	अगर (native_mode->hdisplay != 0 &&
	    native_mode->vdisplay != 0 &&
	    native_mode->घड़ी != 0) अणु
		mode = drm_mode_duplicate(dev, native_mode);
		mode->type = DRM_MODE_TYPE_PREFERRED | DRM_MODE_TYPE_DRIVER;
		drm_mode_set_name(mode);

		DRM_DEBUG_KMS("Adding native panel mode %s\n", mode->name);
	पूर्ण अन्यथा अगर (native_mode->hdisplay != 0 &&
		   native_mode->vdisplay != 0) अणु
		/* mac laptops without an edid */
		/* Note that this is not necessarily the exact panel mode,
		 * but an approximation based on the cvt क्रमmula.  For these
		 * प्रणालीs we should ideally पढ़ो the mode info out of the
		 * रेजिस्टरs or add a mode table, but this works and is much
		 * simpler.
		 */
		mode = drm_cvt_mode(dev, native_mode->hdisplay, native_mode->vdisplay, 60, true, false, false);
		mode->type = DRM_MODE_TYPE_PREFERRED | DRM_MODE_TYPE_DRIVER;
		DRM_DEBUG_KMS("Adding cvt approximation of native panel mode %s\n", mode->name);
	पूर्ण
	वापस mode;
पूर्ण

अटल व्योम radeon_add_common_modes(काष्ठा drm_encoder *encoder, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;
	पूर्णांक i;
	काष्ठा mode_size अणु
		पूर्णांक w;
		पूर्णांक h;
	पूर्ण common_modes[17] = अणु
		अणु 640,  480पूर्ण,
		अणु 720,  480पूर्ण,
		अणु 800,  600पूर्ण,
		अणु 848,  480पूर्ण,
		अणु1024,  768पूर्ण,
		अणु1152,  768पूर्ण,
		अणु1280,  720पूर्ण,
		अणु1280,  800पूर्ण,
		अणु1280,  854पूर्ण,
		अणु1280,  960पूर्ण,
		अणु1280, 1024पूर्ण,
		अणु1440,  900पूर्ण,
		अणु1400, 1050पूर्ण,
		अणु1680, 1050पूर्ण,
		अणु1600, 1200पूर्ण,
		अणु1920, 1080पूर्ण,
		अणु1920, 1200पूर्ण
	पूर्ण;

	क्रम (i = 0; i < 17; i++) अणु
		अगर (radeon_encoder->devices & (ATOM_DEVICE_TV_SUPPORT)) अणु
			अगर (common_modes[i].w > 1024 ||
			    common_modes[i].h > 768)
				जारी;
		पूर्ण
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
			अगर (common_modes[i].w > native_mode->hdisplay ||
			    common_modes[i].h > native_mode->vdisplay ||
			    (common_modes[i].w == native_mode->hdisplay &&
			     common_modes[i].h == native_mode->vdisplay))
				जारी;
		पूर्ण
		अगर (common_modes[i].w < 320 || common_modes[i].h < 200)
			जारी;

		mode = drm_cvt_mode(dev, common_modes[i].w, common_modes[i].h, 60, false, false, false);
		drm_mode_probed_add(connector, mode);
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_connector_set_property(काष्ठा drm_connector *connector, काष्ठा drm_property *property,
				  uपूर्णांक64_t val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;

	अगर (property == rdev->mode_info.coherent_mode_property) अणु
		काष्ठा radeon_encoder_atom_dig *dig;
		bool new_coherent_mode;

		/* need to find digital encoder on connector */
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);

		अगर (!radeon_encoder->enc_priv)
			वापस 0;

		dig = radeon_encoder->enc_priv;
		new_coherent_mode = val ? true : false;
		अगर (dig->coherent_mode != new_coherent_mode) अणु
			dig->coherent_mode = new_coherent_mode;
			radeon_property_change_mode(&radeon_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == rdev->mode_info.audio_property) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		/* need to find digital encoder on connector */
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);

		अगर (radeon_connector->audio != val) अणु
			radeon_connector->audio = val;
			radeon_property_change_mode(&radeon_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == rdev->mode_info.dither_property) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		/* need to find digital encoder on connector */
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);

		अगर (radeon_connector->dither != val) अणु
			radeon_connector->dither = val;
			radeon_property_change_mode(&radeon_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == rdev->mode_info.underscan_property) अणु
		/* need to find digital encoder on connector */
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);

		अगर (radeon_encoder->underscan_type != val) अणु
			radeon_encoder->underscan_type = val;
			radeon_property_change_mode(&radeon_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == rdev->mode_info.underscan_hborder_property) अणु
		/* need to find digital encoder on connector */
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);

		अगर (radeon_encoder->underscan_hborder != val) अणु
			radeon_encoder->underscan_hborder = val;
			radeon_property_change_mode(&radeon_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == rdev->mode_info.underscan_vborder_property) अणु
		/* need to find digital encoder on connector */
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);

		अगर (radeon_encoder->underscan_vborder != val) अणु
			radeon_encoder->underscan_vborder = val;
			radeon_property_change_mode(&radeon_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == rdev->mode_info.tv_std_property) अणु
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TVDAC);
		अगर (!encoder) अणु
			encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_DAC);
		पूर्ण

		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);
		अगर (!radeon_encoder->enc_priv)
			वापस 0;
		अगर (ASIC_IS_AVIVO(rdev) || radeon_r4xx_atom) अणु
			काष्ठा radeon_encoder_atom_dac *dac_पूर्णांक;
			dac_पूर्णांक = radeon_encoder->enc_priv;
			dac_पूर्णांक->tv_std = val;
		पूर्ण अन्यथा अणु
			काष्ठा radeon_encoder_tv_dac *dac_पूर्णांक;
			dac_पूर्णांक = radeon_encoder->enc_priv;
			dac_पूर्णांक->tv_std = val;
		पूर्ण
		radeon_property_change_mode(&radeon_encoder->base);
	पूर्ण

	अगर (property == rdev->mode_info.load_detect_property) अणु
		काष्ठा radeon_connector *radeon_connector =
			to_radeon_connector(connector);

		अगर (val == 0)
			radeon_connector->dac_load_detect = false;
		अन्यथा
			radeon_connector->dac_load_detect = true;
	पूर्ण

	अगर (property == rdev->mode_info.पंचांगds_pll_property) अणु
		काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds = शून्य;
		bool ret = false;
		/* need to find digital encoder on connector */
		encoder = radeon_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		radeon_encoder = to_radeon_encoder(encoder);

		पंचांगds = radeon_encoder->enc_priv;
		अगर (!पंचांगds)
			वापस 0;

		अगर (val == 0) अणु
			अगर (rdev->is_atom_bios)
				ret = radeon_atombios_get_पंचांगds_info(radeon_encoder, पंचांगds);
			अन्यथा
				ret = radeon_legacy_get_पंचांगds_info_from_combios(radeon_encoder, पंचांगds);
		पूर्ण
		अगर (val == 1 || !ret)
			radeon_legacy_get_पंचांगds_info_from_table(radeon_encoder, पंचांगds);

		radeon_property_change_mode(&radeon_encoder->base);
	पूर्ण

	अगर (property == dev->mode_config.scaling_mode_property) अणु
		क्रमागत radeon_rmx_type rmx_type;

		अगर (connector->encoder)
			radeon_encoder = to_radeon_encoder(connector->encoder);
		अन्यथा अणु
			स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs = connector->helper_निजी;
			radeon_encoder = to_radeon_encoder(connector_funcs->best_encoder(connector));
		पूर्ण

		चयन (val) अणु
		शेष:
		हाल DRM_MODE_SCALE_NONE: rmx_type = RMX_OFF; अवरोध;
		हाल DRM_MODE_SCALE_CENTER: rmx_type = RMX_CENTER; अवरोध;
		हाल DRM_MODE_SCALE_ASPECT: rmx_type = RMX_ASPECT; अवरोध;
		हाल DRM_MODE_SCALE_FULLSCREEN: rmx_type = RMX_FULL; अवरोध;
		पूर्ण
		अगर (radeon_encoder->rmx_type == rmx_type)
			वापस 0;

		अगर ((rmx_type != DRM_MODE_SCALE_NONE) &&
		    (radeon_encoder->native_mode.घड़ी == 0))
			वापस 0;

		radeon_encoder->rmx_type = rmx_type;

		radeon_property_change_mode(&radeon_encoder->base);
	पूर्ण

	अगर (property == rdev->mode_info.output_csc_property) अणु
		अगर (connector->encoder)
			radeon_encoder = to_radeon_encoder(connector->encoder);
		अन्यथा अणु
			स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs = connector->helper_निजी;
			radeon_encoder = to_radeon_encoder(connector_funcs->best_encoder(connector));
		पूर्ण

		अगर (radeon_encoder->output_csc == val)
			वापस 0;

		radeon_encoder->output_csc = val;

		अगर (connector->encoder && connector->encoder->crtc) अणु
			काष्ठा drm_crtc *crtc  = connector->encoder->crtc;
			काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);

			radeon_crtc->output_csc = radeon_encoder->output_csc;

			/*
			 * Our .gamma_set assumes the .gamma_store has been
			 * prefilled and करोn't care about its arguments.
			 */
			crtc->funcs->gamma_set(crtc, शून्य, शून्य, शून्य, 0, शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम radeon_fixup_lvds_native_mode(काष्ठा drm_encoder *encoder,
					  काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_encoder *radeon_encoder =	to_radeon_encoder(encoder);
	काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;
	काष्ठा drm_display_mode *t, *mode;

	/* If the EDID preferred mode करोesn't match the native mode, use it */
	list_क्रम_each_entry_safe(mode, t, &connector->probed_modes, head) अणु
		अगर (mode->type & DRM_MODE_TYPE_PREFERRED) अणु
			अगर (mode->hdisplay != native_mode->hdisplay ||
			    mode->vdisplay != native_mode->vdisplay)
				स_नकल(native_mode, mode, माप(*mode));
		पूर्ण
	पूर्ण

	/* Try to get native mode details from EDID अगर necessary */
	अगर (!native_mode->घड़ी) अणु
		list_क्रम_each_entry_safe(mode, t, &connector->probed_modes, head) अणु
			अगर (mode->hdisplay == native_mode->hdisplay &&
			    mode->vdisplay == native_mode->vdisplay) अणु
				*native_mode = *mode;
				drm_mode_set_crtcinfo(native_mode, CRTC_INTERLACE_HALVE_V);
				DRM_DEBUG_KMS("Determined LVDS native mode details from EDID\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!native_mode->घड़ी) अणु
		DRM_DEBUG_KMS("No LVDS native mode details, disabling RMX\n");
		radeon_encoder->rmx_type = RMX_OFF;
	पूर्ण
पूर्ण

अटल पूर्णांक radeon_lvds_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret = 0;
	काष्ठा drm_display_mode *mode;

	radeon_connector_get_edid(connector);
	ret = radeon_ddc_get_modes(connector);
	अगर (ret > 0) अणु
		encoder = radeon_best_single_encoder(connector);
		अगर (encoder) अणु
			radeon_fixup_lvds_native_mode(encoder, connector);
			/* add scaled modes */
			radeon_add_common_modes(encoder, connector);
		पूर्ण
		वापस ret;
	पूर्ण

	encoder = radeon_best_single_encoder(connector);
	अगर (!encoder)
		वापस 0;

	/* we have no EDID modes */
	mode = radeon_fp_native_mode(encoder);
	अगर (mode) अणु
		ret = 1;
		drm_mode_probed_add(connector, mode);
		/* add the width/height from vbios tables अगर available */
		connector->display_info.width_mm = mode->width_mm;
		connector->display_info.height_mm = mode->height_mm;
		/* add scaled modes */
		radeon_add_common_modes(encoder, connector);
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status radeon_lvds_mode_valid(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_encoder *encoder = radeon_best_single_encoder(connector);

	अगर ((mode->hdisplay < 320) || (mode->vdisplay < 240))
		वापस MODE_PANEL;

	अगर (encoder) अणु
		काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
		काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;

		/* AVIVO hardware supports करोwnscaling modes larger than the panel
		 * to the panel size, but I'm not sure this is desirable.
		 */
		अगर ((mode->hdisplay > native_mode->hdisplay) ||
		    (mode->vdisplay > native_mode->vdisplay))
			वापस MODE_PANEL;

		/* अगर scaling is disabled, block non-native modes */
		अगर (radeon_encoder->rmx_type == RMX_OFF) अणु
			अगर ((mode->hdisplay != native_mode->hdisplay) ||
			    (mode->vdisplay != native_mode->vdisplay))
				वापस MODE_PANEL;
		पूर्ण
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_connector_status
radeon_lvds_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा drm_encoder *encoder = radeon_best_single_encoder(connector);
	क्रमागत drm_connector_status ret = connector_status_disconnected;
	पूर्णांक r;

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		r = pm_runसमय_get_sync(connector->dev->dev);
		अगर (r < 0) अणु
			pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
			वापस connector_status_disconnected;
		पूर्ण
	पूर्ण

	अगर (encoder) अणु
		काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
		काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;

		/* check अगर panel is valid */
		अगर (native_mode->hdisplay >= 320 && native_mode->vdisplay >= 240)
			ret = connector_status_connected;
		/* करोn't fetch the edid from the vbios अगर ddc fails and runpm is
		 * enabled so we report disconnected.
		 */
		अगर ((rdev->flags & RADEON_IS_PX) && (radeon_runसमय_pm != 0))
			ret = connector_status_disconnected;
	पूर्ण

	/* check क्रम edid as well */
	radeon_connector_get_edid(connector);
	अगर (radeon_connector->edid)
		ret = connector_status_connected;
	/* check acpi lid status ??? */

	radeon_connector_update_scratch_regs(connector, ret);

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम radeon_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	अगर (radeon_connector->ddc_bus && radeon_connector->ddc_bus->has_aux) अणु
		drm_dp_aux_unरेजिस्टर(&radeon_connector->ddc_bus->aux);
		radeon_connector->ddc_bus->has_aux = false;
	पूर्ण
पूर्ण

अटल व्योम radeon_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	radeon_connector_मुक्त_edid(connector);
	kमुक्त(radeon_connector->con_priv);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल पूर्णांक radeon_lvds_set_property(काष्ठा drm_connector *connector,
				    काष्ठा drm_property *property,
				    uपूर्णांक64_t value)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_encoder *radeon_encoder;
	क्रमागत radeon_rmx_type rmx_type;

	DRM_DEBUG_KMS("\n");
	अगर (property != dev->mode_config.scaling_mode_property)
		वापस 0;

	अगर (connector->encoder)
		radeon_encoder = to_radeon_encoder(connector->encoder);
	अन्यथा अणु
		स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs = connector->helper_निजी;
		radeon_encoder = to_radeon_encoder(connector_funcs->best_encoder(connector));
	पूर्ण

	चयन (value) अणु
	हाल DRM_MODE_SCALE_NONE: rmx_type = RMX_OFF; अवरोध;
	हाल DRM_MODE_SCALE_CENTER: rmx_type = RMX_CENTER; अवरोध;
	हाल DRM_MODE_SCALE_ASPECT: rmx_type = RMX_ASPECT; अवरोध;
	शेष:
	हाल DRM_MODE_SCALE_FULLSCREEN: rmx_type = RMX_FULL; अवरोध;
	पूर्ण
	अगर (radeon_encoder->rmx_type == rmx_type)
		वापस 0;

	radeon_encoder->rmx_type = rmx_type;

	radeon_property_change_mode(&radeon_encoder->base);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा drm_connector_helper_funcs radeon_lvds_connector_helper_funcs = अणु
	.get_modes = radeon_lvds_get_modes,
	.mode_valid = radeon_lvds_mode_valid,
	.best_encoder = radeon_best_single_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs radeon_lvds_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = radeon_lvds_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.early_unरेजिस्टर = radeon_connector_unरेजिस्टर,
	.destroy = radeon_connector_destroy,
	.set_property = radeon_lvds_set_property,
पूर्ण;

अटल पूर्णांक radeon_vga_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक ret;

	radeon_connector_get_edid(connector);
	ret = radeon_ddc_get_modes(connector);

	radeon_get_native_mode(connector);

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status radeon_vga_mode_valid(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	/* XXX check mode bandwidth */

	अगर ((mode->घड़ी / 10) > rdev->घड़ी.max_pixel_घड़ी)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_connector_status
radeon_vga_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा drm_encoder *encoder;
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;
	bool dret = false;
	क्रमागत drm_connector_status ret = connector_status_disconnected;
	पूर्णांक r;

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		r = pm_runसमय_get_sync(connector->dev->dev);
		अगर (r < 0) अणु
			pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
			वापस connector_status_disconnected;
		पूर्ण
	पूर्ण

	encoder = radeon_best_single_encoder(connector);
	अगर (!encoder)
		ret = connector_status_disconnected;

	अगर (radeon_connector->ddc_bus)
		dret = radeon_ddc_probe(radeon_connector, false);
	अगर (dret) अणु
		radeon_connector->detected_by_load = false;
		radeon_connector_मुक्त_edid(connector);
		radeon_connector_get_edid(connector);

		अगर (!radeon_connector->edid) अणु
			DRM_ERROR("%s: probed a monitor but no|invalid EDID\n",
					connector->name);
			ret = connector_status_connected;
		पूर्ण अन्यथा अणु
			radeon_connector->use_digital =
				!!(radeon_connector->edid->input & DRM_EDID_INPUT_DIGITAL);

			/* some oems have boards with separate digital and analog connectors
			 * with a shared ddc line (often vga + hdmi)
			 */
			अगर (radeon_connector->use_digital && radeon_connector->shared_ddc) अणु
				radeon_connector_मुक्त_edid(connector);
				ret = connector_status_disconnected;
			पूर्ण अन्यथा अणु
				ret = connector_status_connected;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु

		/* अगर we aren't forcing don't करो deकाष्ठाive polling */
		अगर (!क्रमce) अणु
			/* only वापस the previous status अगर we last
			 * detected a monitor via load.
			 */
			अगर (radeon_connector->detected_by_load)
				ret = connector->status;
			जाओ out;
		पूर्ण

		अगर (radeon_connector->dac_load_detect && encoder) अणु
			encoder_funcs = encoder->helper_निजी;
			ret = encoder_funcs->detect(encoder, connector);
			अगर (ret != connector_status_disconnected)
				radeon_connector->detected_by_load = true;
		पूर्ण
	पूर्ण

	अगर (ret == connector_status_connected)
		ret = radeon_connector_analog_encoder_conflict_solve(connector, encoder, ret, true);

	/* RN50 and some RV100 asics in servers often have a hardcoded EDID in the
	 * vbios to deal with KVMs. If we have one and are not able to detect a monitor
	 * by other means, assume the CRT is connected and use that EDID.
	 */
	अगर ((!rdev->is_atom_bios) &&
	    (ret == connector_status_disconnected) &&
	    rdev->mode_info.bios_hardcoded_edid_size) अणु
		ret = connector_status_connected;
	पूर्ण

	radeon_connector_update_scratch_regs(connector, ret);

out:
	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs radeon_vga_connector_helper_funcs = अणु
	.get_modes = radeon_vga_get_modes,
	.mode_valid = radeon_vga_mode_valid,
	.best_encoder = radeon_best_single_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs radeon_vga_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = radeon_vga_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.early_unरेजिस्टर = radeon_connector_unरेजिस्टर,
	.destroy = radeon_connector_destroy,
	.set_property = radeon_connector_set_property,
पूर्ण;

अटल पूर्णांक radeon_tv_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_display_mode *tv_mode;
	काष्ठा drm_encoder *encoder;

	encoder = radeon_best_single_encoder(connector);
	अगर (!encoder)
		वापस 0;

	/* avivo chips can scale any mode */
	अगर (rdev->family >= CHIP_RS600)
		/* add scaled modes */
		radeon_add_common_modes(encoder, connector);
	अन्यथा अणु
		/* only 800x600 is supported right now on pre-avivo chips */
		tv_mode = drm_cvt_mode(dev, 800, 600, 60, false, false, false);
		tv_mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
		drm_mode_probed_add(connector, tv_mode);
	पूर्ण
	वापस 1;
पूर्ण

अटल क्रमागत drm_mode_status radeon_tv_mode_valid(काष्ठा drm_connector *connector,
				काष्ठा drm_display_mode *mode)
अणु
	अगर ((mode->hdisplay > 1024) || (mode->vdisplay > 768))
		वापस MODE_CLOCK_RANGE;
	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_connector_status
radeon_tv_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_encoder *encoder;
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	क्रमागत drm_connector_status ret = connector_status_disconnected;
	पूर्णांक r;

	अगर (!radeon_connector->dac_load_detect)
		वापस ret;

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		r = pm_runसमय_get_sync(connector->dev->dev);
		अगर (r < 0) अणु
			pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
			वापस connector_status_disconnected;
		पूर्ण
	पूर्ण

	encoder = radeon_best_single_encoder(connector);
	अगर (!encoder)
		ret = connector_status_disconnected;
	अन्यथा अणु
		encoder_funcs = encoder->helper_निजी;
		ret = encoder_funcs->detect(encoder, connector);
	पूर्ण
	अगर (ret == connector_status_connected)
		ret = radeon_connector_analog_encoder_conflict_solve(connector, encoder, ret, false);
	radeon_connector_update_scratch_regs(connector, ret);

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs radeon_tv_connector_helper_funcs = अणु
	.get_modes = radeon_tv_get_modes,
	.mode_valid = radeon_tv_mode_valid,
	.best_encoder = radeon_best_single_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs radeon_tv_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = radeon_tv_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.early_unरेजिस्टर = radeon_connector_unरेजिस्टर,
	.destroy = radeon_connector_destroy,
	.set_property = radeon_connector_set_property,
पूर्ण;

अटल bool radeon_check_hpd_status_unchanged(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	क्रमागत drm_connector_status status;

	/* We only trust HPD on R600 and newer ASICS. */
	अगर (rdev->family >= CHIP_R600
	  && radeon_connector->hpd.hpd != RADEON_HPD_NONE) अणु
		अगर (radeon_hpd_sense(rdev, radeon_connector->hpd.hpd))
			status = connector_status_connected;
		अन्यथा
			status = connector_status_disconnected;
		अगर (connector->status == status)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * DVI is complicated
 * Do a DDC probe, अगर DDC probe passes, get the full EDID so
 * we can करो analog/digital monitor detection at this poपूर्णांक.
 * If the monitor is an analog monitor or we got no DDC,
 * we need to find the DAC encoder object क्रम this connector.
 * If we got no DDC, we करो load detection on the DAC encoder object.
 * If we got analog DDC or load detection passes on the DAC encoder
 * we have to check अगर this analog encoder is shared with anyone अन्यथा (TV)
 * अगर its shared we have to set the other connector to disconnected.
 */
अटल क्रमागत drm_connector_status
radeon_dvi_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा drm_encoder *encoder = शून्य;
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;
	पूर्णांक r;
	क्रमागत drm_connector_status ret = connector_status_disconnected;
	bool dret = false, broken_edid = false;

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		r = pm_runसमय_get_sync(connector->dev->dev);
		अगर (r < 0) अणु
			pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
			वापस connector_status_disconnected;
		पूर्ण
	पूर्ण

	अगर (radeon_connector->detected_hpd_without_ddc) अणु
		क्रमce = true;
		radeon_connector->detected_hpd_without_ddc = false;
	पूर्ण

	अगर (!क्रमce && radeon_check_hpd_status_unchanged(connector)) अणु
		ret = connector->status;
		जाओ निकास;
	पूर्ण

	अगर (radeon_connector->ddc_bus) अणु
		dret = radeon_ddc_probe(radeon_connector, false);

		/* Someबार the pins required क्रम the DDC probe on DVI
		 * connectors करोn't make contact at the same समय that the ones
		 * क्रम HPD करो. If the DDC probe fails even though we had an HPD
		 * संकेत, try again later */
		अगर (!dret && !क्रमce &&
		    connector->status != connector_status_connected) अणु
			DRM_DEBUG_KMS("hpd detected without ddc, retrying in 1 second\n");
			radeon_connector->detected_hpd_without_ddc = true;
			schedule_delayed_work(&rdev->hotplug_work,
					      msecs_to_jअगरfies(1000));
			जाओ निकास;
		पूर्ण
	पूर्ण
	अगर (dret) अणु
		radeon_connector->detected_by_load = false;
		radeon_connector_मुक्त_edid(connector);
		radeon_connector_get_edid(connector);

		अगर (!radeon_connector->edid) अणु
			DRM_ERROR("%s: probed a monitor but no|invalid EDID\n",
					connector->name);
			/* rs690 seems to have a problem with connectors not existing and always
			 * वापस a block of 0's. If we see this just stop polling on this output */
			अगर ((rdev->family == CHIP_RS690 || rdev->family == CHIP_RS740) &&
			    radeon_connector->base.null_edid_counter) अणु
				ret = connector_status_disconnected;
				DRM_ERROR("%s: detected RS690 floating bus bug, stopping ddc detect\n",
					  connector->name);
				radeon_connector->ddc_bus = शून्य;
			पूर्ण अन्यथा अणु
				ret = connector_status_connected;
				broken_edid = true; /* defer use_digital to later */
			पूर्ण
		पूर्ण अन्यथा अणु
			radeon_connector->use_digital =
				!!(radeon_connector->edid->input & DRM_EDID_INPUT_DIGITAL);

			/* some oems have boards with separate digital and analog connectors
			 * with a shared ddc line (often vga + hdmi)
			 */
			अगर ((!radeon_connector->use_digital) && radeon_connector->shared_ddc) अणु
				radeon_connector_मुक्त_edid(connector);
				ret = connector_status_disconnected;
			पूर्ण अन्यथा अणु
				ret = connector_status_connected;
			पूर्ण
			/* This माला_लो complicated.  We have boards with VGA + HDMI with a
			 * shared DDC line and we have boards with DVI-D + HDMI with a shared
			 * DDC line.  The latter is more complex because with DVI<->HDMI adapters
			 * you करोn't really know what's connected to which port as both are digital.
			 */
			अगर (radeon_connector->shared_ddc && (ret == connector_status_connected)) अणु
				काष्ठा drm_connector *list_connector;
				काष्ठा radeon_connector *list_radeon_connector;
				list_क्रम_each_entry(list_connector, &dev->mode_config.connector_list, head) अणु
					अगर (connector == list_connector)
						जारी;
					list_radeon_connector = to_radeon_connector(list_connector);
					अगर (list_radeon_connector->shared_ddc &&
					    (list_radeon_connector->ddc_bus->rec.i2c_id ==
					     radeon_connector->ddc_bus->rec.i2c_id)) अणु
						/* हालs where both connectors are digital */
						अगर (list_connector->connector_type != DRM_MODE_CONNECTOR_VGA) अणु
							/* hpd is our only option in this हाल */
							अगर (!radeon_hpd_sense(rdev, radeon_connector->hpd.hpd)) अणु
								radeon_connector_मुक्त_edid(connector);
								ret = connector_status_disconnected;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((ret == connector_status_connected) && (radeon_connector->use_digital == true))
		जाओ out;

	/* DVI-D and HDMI-A are digital only */
	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_DVID) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_HDMIA))
		जाओ out;

	/* अगर we aren't forcing don't करो deकाष्ठाive polling */
	अगर (!क्रमce) अणु
		/* only वापस the previous status अगर we last
		 * detected a monitor via load.
		 */
		अगर (radeon_connector->detected_by_load)
			ret = connector->status;
		जाओ out;
	पूर्ण

	/* find analog encoder */
	अगर (radeon_connector->dac_load_detect) अणु
		drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
			अगर (encoder->encoder_type != DRM_MODE_ENCODER_DAC &&
			    encoder->encoder_type != DRM_MODE_ENCODER_TVDAC)
				जारी;

			encoder_funcs = encoder->helper_निजी;
			अगर (encoder_funcs->detect) अणु
				अगर (!broken_edid) अणु
					अगर (ret != connector_status_connected) अणु
						/* deal with analog monitors without DDC */
						ret = encoder_funcs->detect(encoder, connector);
						अगर (ret == connector_status_connected) अणु
							radeon_connector->use_digital = false;
						पूर्ण
						अगर (ret != connector_status_disconnected)
							radeon_connector->detected_by_load = true;
					पूर्ण
				पूर्ण अन्यथा अणु
					क्रमागत drm_connector_status lret;
					/* assume digital unless load detected otherwise */
					radeon_connector->use_digital = true;
					lret = encoder_funcs->detect(encoder, connector);
					DRM_DEBUG_KMS("load_detect %x returned: %x\n",encoder->encoder_type,lret);
					अगर (lret == connector_status_connected)
						radeon_connector->use_digital = false;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((ret == connector_status_connected) && (radeon_connector->use_digital == false) &&
	    encoder) अणु
		ret = radeon_connector_analog_encoder_conflict_solve(connector, encoder, ret, true);
	पूर्ण

	/* RN50 and some RV100 asics in servers often have a hardcoded EDID in the
	 * vbios to deal with KVMs. If we have one and are not able to detect a monitor
	 * by other means, assume the DFP is connected and use that EDID.  In most
	 * हालs the DVI port is actually a भव KVM port connected to the service
	 * processor.
	 */
out:
	अगर ((!rdev->is_atom_bios) &&
	    (ret == connector_status_disconnected) &&
	    rdev->mode_info.bios_hardcoded_edid_size) अणु
		radeon_connector->use_digital = true;
		ret = connector_status_connected;
	पूर्ण

	/* updated in get modes as well since we need to know अगर it's analog or digital */
	radeon_connector_update_scratch_regs(connector, ret);

	अगर ((radeon_audio != 0) && radeon_connector->use_digital) अणु
		स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs =
			connector->helper_निजी;

		encoder = connector_funcs->best_encoder(connector);
		अगर (encoder && (encoder->encoder_type == DRM_MODE_ENCODER_TMDS)) अणु
			radeon_connector_get_edid(connector);
			radeon_audio_detect(connector, encoder, ret);
		पूर्ण
	पूर्ण

निकास:
	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

/* okay need to be smart in here about which encoder to pick */
अटल काष्ठा drm_encoder *radeon_dvi_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा drm_encoder *encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		अगर (radeon_connector->use_digital == true) अणु
			अगर (encoder->encoder_type == DRM_MODE_ENCODER_TMDS)
				वापस encoder;
		पूर्ण अन्यथा अणु
			अगर (encoder->encoder_type == DRM_MODE_ENCODER_DAC ||
			    encoder->encoder_type == DRM_MODE_ENCODER_TVDAC)
				वापस encoder;
		पूर्ण
	पूर्ण

	/* see अगर we have a शेष encoder  TODO */

	/* then check use digitial */
	/* pick the first one */
	drm_connector_क्रम_each_possible_encoder(connector, encoder)
		वापस encoder;

	वापस शून्य;
पूर्ण

अटल व्योम radeon_dvi_क्रमce(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	अगर (connector->क्रमce == DRM_FORCE_ON)
		radeon_connector->use_digital = false;
	अगर (connector->क्रमce == DRM_FORCE_ON_DIGITAL)
		radeon_connector->use_digital = true;
पूर्ण

अटल क्रमागत drm_mode_status radeon_dvi_mode_valid(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	/* XXX check mode bandwidth */

	/* घड़ीs over 135 MHz have heat issues with DVI on RV100 */
	अगर (radeon_connector->use_digital &&
	    (rdev->family == CHIP_RV100) &&
	    (mode->घड़ी > 135000))
		वापस MODE_CLOCK_HIGH;

	अगर (radeon_connector->use_digital && (mode->घड़ी > 165000)) अणु
		अगर ((radeon_connector->connector_object_id == CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I) ||
		    (radeon_connector->connector_object_id == CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D) ||
		    (radeon_connector->connector_object_id == CONNECTOR_OBJECT_ID_HDMI_TYPE_B))
			वापस MODE_OK;
		अन्यथा अगर (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
			/* HDMI 1.3+ supports max घड़ी of 340 Mhz */
			अगर (mode->घड़ी > 340000)
				वापस MODE_CLOCK_HIGH;
			अन्यथा
				वापस MODE_OK;
		पूर्ण अन्यथा अणु
			वापस MODE_CLOCK_HIGH;
		पूर्ण
	पूर्ण

	/* check against the max pixel घड़ी */
	अगर ((mode->घड़ी / 10) > rdev->घड़ी.max_pixel_घड़ी)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs radeon_dvi_connector_helper_funcs = अणु
	.get_modes = radeon_vga_get_modes,
	.mode_valid = radeon_dvi_mode_valid,
	.best_encoder = radeon_dvi_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs radeon_dvi_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = radeon_dvi_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = radeon_connector_set_property,
	.early_unरेजिस्टर = radeon_connector_unरेजिस्टर,
	.destroy = radeon_connector_destroy,
	.क्रमce = radeon_dvi_क्रमce,
पूर्ण;

अटल पूर्णांक radeon_dp_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा radeon_connector_atom_dig *radeon_dig_connector = radeon_connector->con_priv;
	काष्ठा drm_encoder *encoder = radeon_best_single_encoder(connector);
	पूर्णांक ret;

	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) अणु
		काष्ठा drm_display_mode *mode;

		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
			अगर (!radeon_dig_connector->edp_on)
				atombios_set_edp_panel_घातer(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_ON);
			radeon_connector_get_edid(connector);
			ret = radeon_ddc_get_modes(connector);
			अगर (!radeon_dig_connector->edp_on)
				atombios_set_edp_panel_घातer(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_OFF);
		पूर्ण अन्यथा अणु
			/* need to setup ddc on the bridge */
			अगर (radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
			    ENCODER_OBJECT_ID_NONE) अणु
				अगर (encoder)
					radeon_atom_ext_encoder_setup_ddc(encoder);
			पूर्ण
			radeon_connector_get_edid(connector);
			ret = radeon_ddc_get_modes(connector);
		पूर्ण

		अगर (ret > 0) अणु
			अगर (encoder) अणु
				radeon_fixup_lvds_native_mode(encoder, connector);
				/* add scaled modes */
				radeon_add_common_modes(encoder, connector);
			पूर्ण
			वापस ret;
		पूर्ण

		अगर (!encoder)
			वापस 0;

		/* we have no EDID modes */
		mode = radeon_fp_native_mode(encoder);
		अगर (mode) अणु
			ret = 1;
			drm_mode_probed_add(connector, mode);
			/* add the width/height from vbios tables अगर available */
			connector->display_info.width_mm = mode->width_mm;
			connector->display_info.height_mm = mode->height_mm;
			/* add scaled modes */
			radeon_add_common_modes(encoder, connector);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* need to setup ddc on the bridge */
		अगर (radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
			ENCODER_OBJECT_ID_NONE) अणु
			अगर (encoder)
				radeon_atom_ext_encoder_setup_ddc(encoder);
		पूर्ण
		radeon_connector_get_edid(connector);
		ret = radeon_ddc_get_modes(connector);

		radeon_get_native_mode(connector);
	पूर्ण

	वापस ret;
पूर्ण

u16 radeon_connector_encoder_get_dp_bridge_encoder_id(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		radeon_encoder = to_radeon_encoder(encoder);

		चयन (radeon_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_TRAVIS:
		हाल ENCODER_OBJECT_ID_NUTMEG:
			वापस radeon_encoder->encoder_id;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ENCODER_OBJECT_ID_NONE;
पूर्ण

अटल bool radeon_connector_encoder_is_hbr2(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;
	bool found = false;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		radeon_encoder = to_radeon_encoder(encoder);
		अगर (radeon_encoder->caps & ATOM_ENCODER_CAP_RECORD_HBR2)
			found = true;
	पूर्ण

	वापस found;
पूर्ण

bool radeon_connector_is_dp12_capable(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (ASIC_IS_DCE5(rdev) &&
	    (rdev->घड़ी.शेष_dispclk >= 53900) &&
	    radeon_connector_encoder_is_hbr2(connector)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status
radeon_dp_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	क्रमागत drm_connector_status ret = connector_status_disconnected;
	काष्ठा radeon_connector_atom_dig *radeon_dig_connector = radeon_connector->con_priv;
	काष्ठा drm_encoder *encoder = radeon_best_single_encoder(connector);
	पूर्णांक r;

	अगर (radeon_dig_connector->is_mst)
		वापस connector_status_disconnected;

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		r = pm_runसमय_get_sync(connector->dev->dev);
		अगर (r < 0) अणु
			pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
			वापस connector_status_disconnected;
		पूर्ण
	पूर्ण

	अगर (!क्रमce && radeon_check_hpd_status_unchanged(connector)) अणु
		ret = connector->status;
		जाओ out;
	पूर्ण

	radeon_connector_मुक्त_edid(connector);

	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) अणु
		अगर (encoder) अणु
			काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
			काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;

			/* check अगर panel is valid */
			अगर (native_mode->hdisplay >= 320 && native_mode->vdisplay >= 240)
				ret = connector_status_connected;
			/* करोn't fetch the edid from the vbios अगर ddc fails and runpm is
			 * enabled so we report disconnected.
			 */
			अगर ((rdev->flags & RADEON_IS_PX) && (radeon_runसमय_pm != 0))
				ret = connector_status_disconnected;
		पूर्ण
		/* eDP is always DP */
		radeon_dig_connector->dp_sink_type = CONNECTOR_OBJECT_ID_DISPLAYPORT;
		अगर (!radeon_dig_connector->edp_on)
			atombios_set_edp_panel_घातer(connector,
						     ATOM_TRANSMITTER_ACTION_POWER_ON);
		अगर (radeon_dp_getdpcd(radeon_connector))
			ret = connector_status_connected;
		अगर (!radeon_dig_connector->edp_on)
			atombios_set_edp_panel_घातer(connector,
						     ATOM_TRANSMITTER_ACTION_POWER_OFF);
	पूर्ण अन्यथा अगर (radeon_connector_encoder_get_dp_bridge_encoder_id(connector) !=
		   ENCODER_OBJECT_ID_NONE) अणु
		/* DP bridges are always DP */
		radeon_dig_connector->dp_sink_type = CONNECTOR_OBJECT_ID_DISPLAYPORT;
		/* get the DPCD from the bridge */
		radeon_dp_getdpcd(radeon_connector);

		अगर (encoder) अणु
			/* setup ddc on the bridge */
			radeon_atom_ext_encoder_setup_ddc(encoder);
			/* bridge chips are always aux */
			अगर (radeon_ddc_probe(radeon_connector, true)) /* try DDC */
				ret = connector_status_connected;
			अन्यथा अगर (radeon_connector->dac_load_detect) अणु /* try load detection */
				स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs = encoder->helper_निजी;
				ret = encoder_funcs->detect(encoder, connector);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		radeon_dig_connector->dp_sink_type = radeon_dp_माला_लोinktype(radeon_connector);
		अगर (radeon_hpd_sense(rdev, radeon_connector->hpd.hpd)) अणु
			ret = connector_status_connected;
			अगर (radeon_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) अणु
				radeon_dp_getdpcd(radeon_connector);
				r = radeon_dp_mst_probe(radeon_connector);
				अगर (r == 1)
					ret = connector_status_disconnected;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (radeon_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) अणु
				अगर (radeon_dp_getdpcd(radeon_connector)) अणु
					r = radeon_dp_mst_probe(radeon_connector);
					अगर (r == 1)
						ret = connector_status_disconnected;
					अन्यथा
						ret = connector_status_connected;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* try non-aux ddc (DP to DVI/HDMI/etc. adapter) */
				अगर (radeon_ddc_probe(radeon_connector, false))
					ret = connector_status_connected;
			पूर्ण
		पूर्ण
	पूर्ण

	radeon_connector_update_scratch_regs(connector, ret);

	अगर ((radeon_audio != 0) && encoder) अणु
		radeon_connector_get_edid(connector);
		radeon_audio_detect(connector, encoder, ret);
	पूर्ण

out:
	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status radeon_dp_mode_valid(काष्ठा drm_connector *connector,
				  काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा radeon_connector_atom_dig *radeon_dig_connector = radeon_connector->con_priv;

	/* XXX check mode bandwidth */

	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) अणु
		काष्ठा drm_encoder *encoder = radeon_best_single_encoder(connector);

		अगर ((mode->hdisplay < 320) || (mode->vdisplay < 240))
			वापस MODE_PANEL;

		अगर (encoder) अणु
			काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
			काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;

			/* AVIVO hardware supports करोwnscaling modes larger than the panel
			 * to the panel size, but I'm not sure this is desirable.
			 */
			अगर ((mode->hdisplay > native_mode->hdisplay) ||
			    (mode->vdisplay > native_mode->vdisplay))
				वापस MODE_PANEL;

			/* अगर scaling is disabled, block non-native modes */
			अगर (radeon_encoder->rmx_type == RMX_OFF) अणु
				अगर ((mode->hdisplay != native_mode->hdisplay) ||
				    (mode->vdisplay != native_mode->vdisplay))
					वापस MODE_PANEL;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((radeon_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (radeon_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) अणु
			वापस radeon_dp_mode_valid_helper(connector, mode);
		पूर्ण अन्यथा अणु
			अगर (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
				/* HDMI 1.3+ supports max घड़ी of 340 Mhz */
				अगर (mode->घड़ी > 340000)
					वापस MODE_CLOCK_HIGH;
			पूर्ण अन्यथा अणु
				अगर (mode->घड़ी > 165000)
					वापस MODE_CLOCK_HIGH;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs radeon_dp_connector_helper_funcs = अणु
	.get_modes = radeon_dp_get_modes,
	.mode_valid = radeon_dp_mode_valid,
	.best_encoder = radeon_dvi_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs radeon_dp_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = radeon_dp_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = radeon_connector_set_property,
	.early_unरेजिस्टर = radeon_connector_unरेजिस्टर,
	.destroy = radeon_connector_destroy,
	.क्रमce = radeon_dvi_क्रमce,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs radeon_edp_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = radeon_dp_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = radeon_lvds_set_property,
	.early_unरेजिस्टर = radeon_connector_unरेजिस्टर,
	.destroy = radeon_connector_destroy,
	.क्रमce = radeon_dvi_क्रमce,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs radeon_lvds_bridge_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = radeon_dp_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = radeon_lvds_set_property,
	.early_unरेजिस्टर = radeon_connector_unरेजिस्टर,
	.destroy = radeon_connector_destroy,
	.क्रमce = radeon_dvi_क्रमce,
पूर्ण;

व्योम
radeon_add_atom_connector(काष्ठा drm_device *dev,
			  uपूर्णांक32_t connector_id,
			  uपूर्णांक32_t supported_device,
			  पूर्णांक connector_type,
			  काष्ठा radeon_i2c_bus_rec *i2c_bus,
			  uपूर्णांक32_t igp_lane_info,
			  uपूर्णांक16_t connector_object_id,
			  काष्ठा radeon_hpd *hpd,
			  काष्ठा radeon_router *router)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा radeon_connector_atom_dig *radeon_dig_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;
	काष्ठा i2c_adapter *ddc = शून्य;
	uपूर्णांक32_t subpixel_order = SubPixelNone;
	bool shared_ddc = false;
	bool is_dp_bridge = false;
	bool has_aux = false;

	अगर (connector_type == DRM_MODE_CONNECTOR_Unknown)
		वापस;

	/* अगर the user selected tv=0 करोn't try and add the connector */
	अगर (((connector_type == DRM_MODE_CONNECTOR_SVIDEO) ||
	     (connector_type == DRM_MODE_CONNECTOR_Composite) ||
	     (connector_type == DRM_MODE_CONNECTOR_9PinDIN)) &&
	    (radeon_tv == 0))
		वापस;

	/* see अगर we alपढ़ोy added it */
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		radeon_connector = to_radeon_connector(connector);
		अगर (radeon_connector->connector_id == connector_id) अणु
			radeon_connector->devices |= supported_device;
			वापस;
		पूर्ण
		अगर (radeon_connector->ddc_bus && i2c_bus->valid) अणु
			अगर (radeon_connector->ddc_bus->rec.i2c_id == i2c_bus->i2c_id) अणु
				radeon_connector->shared_ddc = true;
				shared_ddc = true;
			पूर्ण
			अगर (radeon_connector->router_bus && router->ddc_valid &&
			    (radeon_connector->router.router_id == router->router_id)) अणु
				radeon_connector->shared_ddc = false;
				shared_ddc = false;
			पूर्ण
		पूर्ण
	पूर्ण

	/* check अगर it's a dp bridge */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		radeon_encoder = to_radeon_encoder(encoder);
		अगर (radeon_encoder->devices & supported_device) अणु
			चयन (radeon_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_TRAVIS:
			हाल ENCODER_OBJECT_ID_NUTMEG:
				is_dp_bridge = true;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	radeon_connector = kzalloc(माप(काष्ठा radeon_connector), GFP_KERNEL);
	अगर (!radeon_connector)
		वापस;

	connector = &radeon_connector->base;

	radeon_connector->connector_id = connector_id;
	radeon_connector->devices = supported_device;
	radeon_connector->shared_ddc = shared_ddc;
	radeon_connector->connector_object_id = connector_object_id;
	radeon_connector->hpd = *hpd;

	radeon_connector->router = *router;
	अगर (router->ddc_valid || router->cd_valid) अणु
		radeon_connector->router_bus = radeon_i2c_lookup(rdev, &router->i2c_info);
		अगर (!radeon_connector->router_bus)
			DRM_ERROR("Failed to assign router i2c bus! Check dmesg for i2c errors.\n");
	पूर्ण

	अगर (is_dp_bridge) अणु
		radeon_dig_connector = kzalloc(माप(काष्ठा radeon_connector_atom_dig), GFP_KERNEL);
		अगर (!radeon_dig_connector)
			जाओ failed;
		radeon_dig_connector->igp_lane_info = igp_lane_info;
		radeon_connector->con_priv = radeon_dig_connector;
		अगर (i2c_bus->valid) अणु
			radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
			अगर (radeon_connector->ddc_bus) अणु
				has_aux = true;
				ddc = &radeon_connector->ddc_bus->adapter;
			पूर्ण अन्यथा अणु
				DRM_ERROR("DP: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
			पूर्ण
		पूर्ण
		चयन (connector_type) अणु
		हाल DRM_MODE_CONNECTOR_VGA:
		हाल DRM_MODE_CONNECTOR_DVIA:
		शेष:
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_dp_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base,
						 &radeon_dp_connector_helper_funcs);
			connector->पूर्णांकerlace_allowed = true;
			connector->द्विगुनscan_allowed = true;
			radeon_connector->dac_load_detect = true;
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.load_detect_property,
						      1);
			drm_object_attach_property(&radeon_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);
			अगर (ASIC_IS_DCE5(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.output_csc_property,
							   RADEON_OUTPUT_CSC_BYPASS);
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DVII:
		हाल DRM_MODE_CONNECTOR_DVID:
		हाल DRM_MODE_CONNECTOR_HDMIA:
		हाल DRM_MODE_CONNECTOR_HDMIB:
		हाल DRM_MODE_CONNECTOR_DisplayPort:
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_dp_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base,
						 &radeon_dp_connector_helper_funcs);
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.underscan_property,
						      UNDERSCAN_OFF);
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.underscan_hborder_property,
						      0);
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.underscan_vborder_property,
						      0);

			drm_object_attach_property(&radeon_connector->base.base,
						      dev->mode_config.scaling_mode_property,
						      DRM_MODE_SCALE_NONE);

			drm_object_attach_property(&radeon_connector->base.base,
						   rdev->mode_info.dither_property,
						   RADEON_FMT_DITHER_DISABLE);

			अगर (radeon_audio != 0) अणु
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.audio_property,
							   RADEON_AUDIO_AUTO);
				radeon_connector->audio = RADEON_AUDIO_AUTO;
			पूर्ण
			अगर (ASIC_IS_DCE5(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.output_csc_property,
							   RADEON_OUTPUT_CSC_BYPASS);

			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = true;
			अगर (connector_type == DRM_MODE_CONNECTOR_HDMIB)
				connector->द्विगुनscan_allowed = true;
			अन्यथा
				connector->द्विगुनscan_allowed = false;
			अगर (connector_type == DRM_MODE_CONNECTOR_DVII) अणु
				radeon_connector->dac_load_detect = true;
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.load_detect_property,
							      1);
			पूर्ण
			अवरोध;
		हाल DRM_MODE_CONNECTOR_LVDS:
		हाल DRM_MODE_CONNECTOR_eDP:
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_lvds_bridge_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base,
						 &radeon_dp_connector_helper_funcs);
			drm_object_attach_property(&radeon_connector->base.base,
						      dev->mode_config.scaling_mode_property,
						      DRM_MODE_SCALE_FULLSCREEN);
			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = false;
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (connector_type) अणु
		हाल DRM_MODE_CONNECTOR_VGA:
			अगर (i2c_bus->valid) अणु
				radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
				अगर (!radeon_connector->ddc_bus)
					DRM_ERROR("VGA: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &radeon_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_vga_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_vga_connector_helper_funcs);
			radeon_connector->dac_load_detect = true;
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.load_detect_property,
						      1);
			अगर (ASIC_IS_AVIVO(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   dev->mode_config.scaling_mode_property,
							   DRM_MODE_SCALE_NONE);
			अगर (ASIC_IS_DCE5(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.output_csc_property,
							   RADEON_OUTPUT_CSC_BYPASS);
			/* no HPD on analog connectors */
			radeon_connector->hpd.hpd = RADEON_HPD_NONE;
			connector->पूर्णांकerlace_allowed = true;
			connector->द्विगुनscan_allowed = true;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DVIA:
			अगर (i2c_bus->valid) अणु
				radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
				अगर (!radeon_connector->ddc_bus)
					DRM_ERROR("DVIA: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &radeon_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_vga_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_vga_connector_helper_funcs);
			radeon_connector->dac_load_detect = true;
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.load_detect_property,
						      1);
			अगर (ASIC_IS_AVIVO(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   dev->mode_config.scaling_mode_property,
							   DRM_MODE_SCALE_NONE);
			अगर (ASIC_IS_DCE5(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.output_csc_property,
							   RADEON_OUTPUT_CSC_BYPASS);
			/* no HPD on analog connectors */
			radeon_connector->hpd.hpd = RADEON_HPD_NONE;
			connector->पूर्णांकerlace_allowed = true;
			connector->द्विगुनscan_allowed = true;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DVII:
		हाल DRM_MODE_CONNECTOR_DVID:
			radeon_dig_connector = kzalloc(माप(काष्ठा radeon_connector_atom_dig), GFP_KERNEL);
			अगर (!radeon_dig_connector)
				जाओ failed;
			radeon_dig_connector->igp_lane_info = igp_lane_info;
			radeon_connector->con_priv = radeon_dig_connector;
			अगर (i2c_bus->valid) अणु
				radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
				अगर (!radeon_connector->ddc_bus)
					DRM_ERROR("DVI: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &radeon_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_dvi_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_dvi_connector_helper_funcs);
			subpixel_order = SubPixelHorizontalRGB;
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.coherent_mode_property,
						      1);
			अगर (ASIC_IS_AVIVO(rdev)) अणु
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_property,
							      UNDERSCAN_OFF);
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_hborder_property,
							      0);
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_vborder_property,
							      0);
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.dither_property,
							   RADEON_FMT_DITHER_DISABLE);
				drm_object_attach_property(&radeon_connector->base.base,
							   dev->mode_config.scaling_mode_property,
							   DRM_MODE_SCALE_NONE);
			पूर्ण
			अगर (ASIC_IS_DCE2(rdev) && (radeon_audio != 0)) अणु
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.audio_property,
							   RADEON_AUDIO_AUTO);
				radeon_connector->audio = RADEON_AUDIO_AUTO;
			पूर्ण
			अगर (connector_type == DRM_MODE_CONNECTOR_DVII) अणु
				radeon_connector->dac_load_detect = true;
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.load_detect_property,
							      1);
			पूर्ण
			अगर (ASIC_IS_DCE5(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.output_csc_property,
							   RADEON_OUTPUT_CSC_BYPASS);
			connector->पूर्णांकerlace_allowed = true;
			अगर (connector_type == DRM_MODE_CONNECTOR_DVII)
				connector->द्विगुनscan_allowed = true;
			अन्यथा
				connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_HDMIA:
		हाल DRM_MODE_CONNECTOR_HDMIB:
			radeon_dig_connector = kzalloc(माप(काष्ठा radeon_connector_atom_dig), GFP_KERNEL);
			अगर (!radeon_dig_connector)
				जाओ failed;
			radeon_dig_connector->igp_lane_info = igp_lane_info;
			radeon_connector->con_priv = radeon_dig_connector;
			अगर (i2c_bus->valid) अणु
				radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
				अगर (!radeon_connector->ddc_bus)
					DRM_ERROR("HDMI: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &radeon_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_dvi_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_dvi_connector_helper_funcs);
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.coherent_mode_property,
						      1);
			अगर (ASIC_IS_AVIVO(rdev)) अणु
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_property,
							      UNDERSCAN_OFF);
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_hborder_property,
							      0);
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_vborder_property,
							      0);
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.dither_property,
							   RADEON_FMT_DITHER_DISABLE);
				drm_object_attach_property(&radeon_connector->base.base,
							   dev->mode_config.scaling_mode_property,
							   DRM_MODE_SCALE_NONE);
			पूर्ण
			अगर (ASIC_IS_DCE2(rdev) && (radeon_audio != 0)) अणु
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.audio_property,
							   RADEON_AUDIO_AUTO);
				radeon_connector->audio = RADEON_AUDIO_AUTO;
			पूर्ण
			अगर (ASIC_IS_DCE5(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.output_csc_property,
							   RADEON_OUTPUT_CSC_BYPASS);
			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = true;
			अगर (connector_type == DRM_MODE_CONNECTOR_HDMIB)
				connector->द्विगुनscan_allowed = true;
			अन्यथा
				connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DisplayPort:
			radeon_dig_connector = kzalloc(माप(काष्ठा radeon_connector_atom_dig), GFP_KERNEL);
			अगर (!radeon_dig_connector)
				जाओ failed;
			radeon_dig_connector->igp_lane_info = igp_lane_info;
			radeon_connector->con_priv = radeon_dig_connector;
			अगर (i2c_bus->valid) अणु
				radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
				अगर (radeon_connector->ddc_bus) अणु
					has_aux = true;
					ddc = &radeon_connector->ddc_bus->adapter;
				पूर्ण अन्यथा अणु
					DRM_ERROR("DP: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				पूर्ण
			पूर्ण
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_dp_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_dp_connector_helper_funcs);
			subpixel_order = SubPixelHorizontalRGB;
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.coherent_mode_property,
						      1);
			अगर (ASIC_IS_AVIVO(rdev)) अणु
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_property,
							      UNDERSCAN_OFF);
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_hborder_property,
							      0);
				drm_object_attach_property(&radeon_connector->base.base,
							      rdev->mode_info.underscan_vborder_property,
							      0);
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.dither_property,
							   RADEON_FMT_DITHER_DISABLE);
				drm_object_attach_property(&radeon_connector->base.base,
							   dev->mode_config.scaling_mode_property,
							   DRM_MODE_SCALE_NONE);
			पूर्ण
			अगर (ASIC_IS_DCE2(rdev) && (radeon_audio != 0)) अणु
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.audio_property,
							   RADEON_AUDIO_AUTO);
				radeon_connector->audio = RADEON_AUDIO_AUTO;
			पूर्ण
			अगर (ASIC_IS_DCE5(rdev))
				drm_object_attach_property(&radeon_connector->base.base,
							   rdev->mode_info.output_csc_property,
							   RADEON_OUTPUT_CSC_BYPASS);
			connector->पूर्णांकerlace_allowed = true;
			/* in theory with a DP to VGA converter... */
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_eDP:
			radeon_dig_connector = kzalloc(माप(काष्ठा radeon_connector_atom_dig), GFP_KERNEL);
			अगर (!radeon_dig_connector)
				जाओ failed;
			radeon_dig_connector->igp_lane_info = igp_lane_info;
			radeon_connector->con_priv = radeon_dig_connector;
			अगर (i2c_bus->valid) अणु
				radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
				अगर (radeon_connector->ddc_bus) अणु
					has_aux = true;
					ddc = &radeon_connector->ddc_bus->adapter;
				पूर्ण अन्यथा अणु
					DRM_ERROR("DP: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				पूर्ण
			पूर्ण
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_edp_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_dp_connector_helper_funcs);
			drm_object_attach_property(&radeon_connector->base.base,
						      dev->mode_config.scaling_mode_property,
						      DRM_MODE_SCALE_FULLSCREEN);
			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = false;
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_SVIDEO:
		हाल DRM_MODE_CONNECTOR_Composite:
		हाल DRM_MODE_CONNECTOR_9PinDIN:
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_tv_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_tv_connector_helper_funcs);
			radeon_connector->dac_load_detect = true;
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.load_detect_property,
						      1);
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.tv_std_property,
						      radeon_atombios_get_tv_info(rdev));
			/* no HPD on analog connectors */
			radeon_connector->hpd.hpd = RADEON_HPD_NONE;
			connector->पूर्णांकerlace_allowed = false;
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_LVDS:
			radeon_dig_connector = kzalloc(माप(काष्ठा radeon_connector_atom_dig), GFP_KERNEL);
			अगर (!radeon_dig_connector)
				जाओ failed;
			radeon_dig_connector->igp_lane_info = igp_lane_info;
			radeon_connector->con_priv = radeon_dig_connector;
			अगर (i2c_bus->valid) अणु
				radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
				अगर (!radeon_connector->ddc_bus)
					DRM_ERROR("LVDS: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &radeon_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &radeon_connector->base,
						    &radeon_lvds_connector_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&radeon_connector->base, &radeon_lvds_connector_helper_funcs);
			drm_object_attach_property(&radeon_connector->base.base,
						      dev->mode_config.scaling_mode_property,
						      DRM_MODE_SCALE_FULLSCREEN);
			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = false;
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (radeon_connector->hpd.hpd == RADEON_HPD_NONE) अणु
		अगर (i2c_bus->valid) अणु
			connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			                    DRM_CONNECTOR_POLL_DISCONNECT;
		पूर्ण
	पूर्ण अन्यथा
		connector->polled = DRM_CONNECTOR_POLL_HPD;

	connector->display_info.subpixel_order = subpixel_order;
	drm_connector_रेजिस्टर(connector);

	अगर (has_aux)
		radeon_dp_aux_init(radeon_connector);

	वापस;

failed:
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

व्योम
radeon_add_legacy_connector(काष्ठा drm_device *dev,
			    uपूर्णांक32_t connector_id,
			    uपूर्णांक32_t supported_device,
			    पूर्णांक connector_type,
			    काष्ठा radeon_i2c_bus_rec *i2c_bus,
			    uपूर्णांक16_t connector_object_id,
			    काष्ठा radeon_hpd *hpd)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा i2c_adapter *ddc = शून्य;
	uपूर्णांक32_t subpixel_order = SubPixelNone;

	अगर (connector_type == DRM_MODE_CONNECTOR_Unknown)
		वापस;

	/* अगर the user selected tv=0 करोn't try and add the connector */
	अगर (((connector_type == DRM_MODE_CONNECTOR_SVIDEO) ||
	     (connector_type == DRM_MODE_CONNECTOR_Composite) ||
	     (connector_type == DRM_MODE_CONNECTOR_9PinDIN)) &&
	    (radeon_tv == 0))
		वापस;

	/* see अगर we alपढ़ोy added it */
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		radeon_connector = to_radeon_connector(connector);
		अगर (radeon_connector->connector_id == connector_id) अणु
			radeon_connector->devices |= supported_device;
			वापस;
		पूर्ण
	पूर्ण

	radeon_connector = kzalloc(माप(काष्ठा radeon_connector), GFP_KERNEL);
	अगर (!radeon_connector)
		वापस;

	connector = &radeon_connector->base;

	radeon_connector->connector_id = connector_id;
	radeon_connector->devices = supported_device;
	radeon_connector->connector_object_id = connector_object_id;
	radeon_connector->hpd = *hpd;

	चयन (connector_type) अणु
	हाल DRM_MODE_CONNECTOR_VGA:
		अगर (i2c_bus->valid) अणु
			radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
			अगर (!radeon_connector->ddc_bus)
				DRM_ERROR("VGA: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
			अन्यथा
				ddc = &radeon_connector->ddc_bus->adapter;
		पूर्ण
		drm_connector_init_with_ddc(dev, &radeon_connector->base,
					    &radeon_vga_connector_funcs,
					    connector_type,
					    ddc);
		drm_connector_helper_add(&radeon_connector->base, &radeon_vga_connector_helper_funcs);
		radeon_connector->dac_load_detect = true;
		drm_object_attach_property(&radeon_connector->base.base,
					      rdev->mode_info.load_detect_property,
					      1);
		/* no HPD on analog connectors */
		radeon_connector->hpd.hpd = RADEON_HPD_NONE;
		connector->पूर्णांकerlace_allowed = true;
		connector->द्विगुनscan_allowed = true;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVIA:
		अगर (i2c_bus->valid) अणु
			radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
			अगर (!radeon_connector->ddc_bus)
				DRM_ERROR("DVIA: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
			अन्यथा
				ddc = &radeon_connector->ddc_bus->adapter;
		पूर्ण
		drm_connector_init_with_ddc(dev, &radeon_connector->base,
					    &radeon_vga_connector_funcs,
					    connector_type,
					    ddc);
		drm_connector_helper_add(&radeon_connector->base, &radeon_vga_connector_helper_funcs);
		radeon_connector->dac_load_detect = true;
		drm_object_attach_property(&radeon_connector->base.base,
					      rdev->mode_info.load_detect_property,
					      1);
		/* no HPD on analog connectors */
		radeon_connector->hpd.hpd = RADEON_HPD_NONE;
		connector->पूर्णांकerlace_allowed = true;
		connector->द्विगुनscan_allowed = true;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_DVID:
		अगर (i2c_bus->valid) अणु
			radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
			अगर (!radeon_connector->ddc_bus)
				DRM_ERROR("DVI: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
			अन्यथा
				ddc = &radeon_connector->ddc_bus->adapter;
		पूर्ण
		drm_connector_init_with_ddc(dev, &radeon_connector->base,
					    &radeon_dvi_connector_funcs,
					    connector_type,
					    ddc);
		drm_connector_helper_add(&radeon_connector->base, &radeon_dvi_connector_helper_funcs);
		अगर (connector_type == DRM_MODE_CONNECTOR_DVII) अणु
			radeon_connector->dac_load_detect = true;
			drm_object_attach_property(&radeon_connector->base.base,
						      rdev->mode_info.load_detect_property,
						      1);
		पूर्ण
		subpixel_order = SubPixelHorizontalRGB;
		connector->पूर्णांकerlace_allowed = true;
		अगर (connector_type == DRM_MODE_CONNECTOR_DVII)
			connector->द्विगुनscan_allowed = true;
		अन्यथा
			connector->द्विगुनscan_allowed = false;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_SVIDEO:
	हाल DRM_MODE_CONNECTOR_Composite:
	हाल DRM_MODE_CONNECTOR_9PinDIN:
		drm_connector_init_with_ddc(dev, &radeon_connector->base,
					    &radeon_tv_connector_funcs,
					    connector_type,
					    ddc);
		drm_connector_helper_add(&radeon_connector->base, &radeon_tv_connector_helper_funcs);
		radeon_connector->dac_load_detect = true;
		/* RS400,RC410,RS480 chipset seems to report a lot
		 * of false positive on load detect, we haven't yet
		 * found a way to make load detect reliable on those
		 * chipset, thus just disable it क्रम TV.
		 */
		अगर (rdev->family == CHIP_RS400 || rdev->family == CHIP_RS480)
			radeon_connector->dac_load_detect = false;
		drm_object_attach_property(&radeon_connector->base.base,
					      rdev->mode_info.load_detect_property,
					      radeon_connector->dac_load_detect);
		drm_object_attach_property(&radeon_connector->base.base,
					      rdev->mode_info.tv_std_property,
					      radeon_combios_get_tv_info(rdev));
		/* no HPD on analog connectors */
		radeon_connector->hpd.hpd = RADEON_HPD_NONE;
		connector->पूर्णांकerlace_allowed = false;
		connector->द्विगुनscan_allowed = false;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_LVDS:
		अगर (i2c_bus->valid) अणु
			radeon_connector->ddc_bus = radeon_i2c_lookup(rdev, i2c_bus);
			अगर (!radeon_connector->ddc_bus)
				DRM_ERROR("LVDS: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
			अन्यथा
				ddc = &radeon_connector->ddc_bus->adapter;
		पूर्ण
		drm_connector_init_with_ddc(dev, &radeon_connector->base,
					    &radeon_lvds_connector_funcs,
					    connector_type,
					    ddc);
		drm_connector_helper_add(&radeon_connector->base, &radeon_lvds_connector_helper_funcs);
		drm_object_attach_property(&radeon_connector->base.base,
					      dev->mode_config.scaling_mode_property,
					      DRM_MODE_SCALE_FULLSCREEN);
		subpixel_order = SubPixelHorizontalRGB;
		connector->पूर्णांकerlace_allowed = false;
		connector->द्विगुनscan_allowed = false;
		अवरोध;
	पूर्ण

	अगर (radeon_connector->hpd.hpd == RADEON_HPD_NONE) अणु
		अगर (i2c_bus->valid) अणु
			connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			                    DRM_CONNECTOR_POLL_DISCONNECT;
		पूर्ण
	पूर्ण अन्यथा
		connector->polled = DRM_CONNECTOR_POLL_HPD;

	connector->display_info.subpixel_order = subpixel_order;
	drm_connector_रेजिस्टर(connector);
पूर्ण

व्योम radeon_setup_mst_connector(काष्ठा drm_device *dev)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;

	अगर (!ASIC_IS_DCE5(rdev))
		वापस;

	अगर (radeon_mst == 0)
		वापस;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		radeon_connector = to_radeon_connector(connector);

		अगर (connector->connector_type != DRM_MODE_CONNECTOR_DisplayPort)
			जारी;

		radeon_dp_mst_init(radeon_connector);
	पूर्ण
पूर्ण
