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
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "atom.h"
#समावेश "atombios_encoders.h"
#समावेश "atombios_dp.h"
#समावेश "amdgpu_connectors.h"
#समावेश "amdgpu_i2c.h"
#समावेश "amdgpu_display.h"

#समावेश <linux/pm_runसमय.स>

व्योम amdgpu_connector_hotplug(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	/* bail अगर the connector करोes not have hpd pin, e.g.,
	 * VGA, TV, etc.
	 */
	अगर (amdgpu_connector->hpd.hpd == AMDGPU_HPD_NONE)
		वापस;

	amdgpu_display_hpd_set_polarity(adev, amdgpu_connector->hpd.hpd);

	/* अगर the connector is alपढ़ोy off, करोn't turn it back on */
	अगर (connector->dpms != DRM_MODE_DPMS_ON)
		वापस;

	/* just deal with DP (not eDP) here. */
	अगर (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) अणु
		काष्ठा amdgpu_connector_atom_dig *dig_connector =
			amdgpu_connector->con_priv;

		/* अगर existing sink type was not DP no need to retrain */
		अगर (dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_DISPLAYPORT)
			वापस;

		/* first get sink type as it may be reset after (un)plug */
		dig_connector->dp_sink_type = amdgpu_atombios_dp_get_sinktype(amdgpu_connector);
		/* करोn't करो anything अगर sink is not display port, i.e.,
		 * passive dp->(dvi|hdmi) adaptor
		 */
		अगर (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT &&
		    amdgpu_display_hpd_sense(adev, amdgpu_connector->hpd.hpd) &&
		    amdgpu_atombios_dp_needs_link_train(amdgpu_connector)) अणु
			/* Don't start link training beक्रमe we have the DPCD */
			अगर (amdgpu_atombios_dp_get_dpcd(amdgpu_connector))
				वापस;

			/* Turn the connector off and back on immediately, which
			 * will trigger link training
			 */
			drm_helper_connector_dpms(connector, DRM_MODE_DPMS_OFF);
			drm_helper_connector_dpms(connector, DRM_MODE_DPMS_ON);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम amdgpu_connector_property_change_mode(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_crtc *crtc = encoder->crtc;

	अगर (crtc && crtc->enabled) अणु
		drm_crtc_helper_set_mode(crtc, &crtc->mode,
					 crtc->x, crtc->y, crtc->primary->fb);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_connector_get_monitor_bpc(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा amdgpu_connector_atom_dig *dig_connector;
	पूर्णांक bpc = 8;
	अचिन्हित mode_घड़ी, max_पंचांगds_घड़ी;

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_HDMIB:
		अगर (amdgpu_connector->use_digital) अणु
			अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
				अगर (connector->display_info.bpc)
					bpc = connector->display_info.bpc;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVID:
	हाल DRM_MODE_CONNECTOR_HDMIA:
		अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
			अगर (connector->display_info.bpc)
				bpc = connector->display_info.bpc;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = amdgpu_connector->con_priv;
		अगर ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP) ||
		    drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
			अगर (connector->display_info.bpc)
				bpc = connector->display_info.bpc;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_eDP:
	हाल DRM_MODE_CONNECTOR_LVDS:
		अगर (connector->display_info.bpc)
			bpc = connector->display_info.bpc;
		अन्यथा अणु
			स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs =
				connector->helper_निजी;
			काष्ठा drm_encoder *encoder = connector_funcs->best_encoder(connector);
			काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
			काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;

			अगर (dig->lcd_misc & ATOM_PANEL_MISC_V13_6BIT_PER_COLOR)
				bpc = 6;
			अन्यथा अगर (dig->lcd_misc & ATOM_PANEL_MISC_V13_8BIT_PER_COLOR)
				bpc = 8;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
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
			mode_घड़ी = amdgpu_connector->pixelघड़ी_क्रम_modeset;

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
		पूर्ण अन्यथा अगर (bpc > 8) अणु
			/* max_पंचांगds_घड़ी missing, but hdmi spec mandates it क्रम deep color. */
			DRM_DEBUG("%s: Required max tmds clock for HDMI deep color missing. Using 8 bpc.\n",
				  connector->name);
			bpc = 8;
		पूर्ण
	पूर्ण

	अगर ((amdgpu_deep_color == 0) && (bpc > 8)) अणु
		DRM_DEBUG("%s: Deep color disabled. Set amdgpu module param deep_color=1 to enable.\n",
			  connector->name);
		bpc = 8;
	पूर्ण

	DRM_DEBUG("%s: Display bpc=%d, returned bpc=%d\n",
		  connector->name, connector->display_info.bpc, bpc);

	वापस bpc;
पूर्ण

अटल व्योम
amdgpu_connector_update_scratch_regs(काष्ठा drm_connector *connector,
				      क्रमागत drm_connector_status status)
अणु
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

		amdgpu_atombios_encoder_set_bios_scratch_regs(connector, encoder, connected);
	पूर्ण
पूर्ण

अटल काष्ठा drm_encoder *
amdgpu_connector_find_encoder(काष्ठा drm_connector *connector,
			       पूर्णांक encoder_type)
अणु
	काष्ठा drm_encoder *encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		अगर (encoder->encoder_type == encoder_type)
			वापस encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा edid *amdgpu_connector_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा drm_property_blob *edid_blob = connector->edid_blob_ptr;

	अगर (amdgpu_connector->edid) अणु
		वापस amdgpu_connector->edid;
	पूर्ण अन्यथा अगर (edid_blob) अणु
		काष्ठा edid *edid = kmemdup(edid_blob->data, edid_blob->length, GFP_KERNEL);
		अगर (edid)
			amdgpu_connector->edid = edid;
	पूर्ण
	वापस amdgpu_connector->edid;
पूर्ण

अटल काष्ठा edid *
amdgpu_connector_get_hardcoded_edid(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा edid *edid;

	अगर (adev->mode_info.bios_hardcoded_edid) अणु
		edid = kदो_स्मृति(adev->mode_info.bios_hardcoded_edid_size, GFP_KERNEL);
		अगर (edid) अणु
			स_नकल((अचिन्हित अक्षर *)edid,
			       (अचिन्हित अक्षर *)adev->mode_info.bios_hardcoded_edid,
			       adev->mode_info.bios_hardcoded_edid_size);
			वापस edid;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम amdgpu_connector_get_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	अगर (amdgpu_connector->edid)
		वापस;

	/* on hw with routers, select right port */
	अगर (amdgpu_connector->router.ddc_valid)
		amdgpu_i2c_router_select_ddc_port(amdgpu_connector);

	अगर ((amdgpu_connector_encoder_get_dp_bridge_encoder_id(connector) !=
	     ENCODER_OBJECT_ID_NONE) &&
	    amdgpu_connector->ddc_bus->has_aux) अणु
		amdgpu_connector->edid = drm_get_edid(connector,
						      &amdgpu_connector->ddc_bus->aux.ddc);
	पूर्ण अन्यथा अगर ((connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort) ||
		   (connector->connector_type == DRM_MODE_CONNECTOR_eDP)) अणु
		काष्ठा amdgpu_connector_atom_dig *dig = amdgpu_connector->con_priv;

		अगर ((dig->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT ||
		     dig->dp_sink_type == CONNECTOR_OBJECT_ID_eDP) &&
		    amdgpu_connector->ddc_bus->has_aux)
			amdgpu_connector->edid = drm_get_edid(connector,
							      &amdgpu_connector->ddc_bus->aux.ddc);
		अन्यथा अगर (amdgpu_connector->ddc_bus)
			amdgpu_connector->edid = drm_get_edid(connector,
							      &amdgpu_connector->ddc_bus->adapter);
	पूर्ण अन्यथा अगर (amdgpu_connector->ddc_bus) अणु
		amdgpu_connector->edid = drm_get_edid(connector,
						      &amdgpu_connector->ddc_bus->adapter);
	पूर्ण

	अगर (!amdgpu_connector->edid) अणु
		/* some laptops provide a hardcoded edid in rom क्रम LCDs */
		अगर (((connector->connector_type == DRM_MODE_CONNECTOR_LVDS) ||
		     (connector->connector_type == DRM_MODE_CONNECTOR_eDP)))
			amdgpu_connector->edid = amdgpu_connector_get_hardcoded_edid(adev);
	पूर्ण
पूर्ण

अटल व्योम amdgpu_connector_मुक्त_edid(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	kमुक्त(amdgpu_connector->edid);
	amdgpu_connector->edid = शून्य;
पूर्ण

अटल पूर्णांक amdgpu_connector_ddc_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	पूर्णांक ret;

	अगर (amdgpu_connector->edid) अणु
		drm_connector_update_edid_property(connector, amdgpu_connector->edid);
		ret = drm_add_edid_modes(connector, amdgpu_connector->edid);
		वापस ret;
	पूर्ण
	drm_connector_update_edid_property(connector, शून्य);
	वापस 0;
पूर्ण

अटल काष्ठा drm_encoder *
amdgpu_connector_best_single_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;

	/* pick the first one */
	drm_connector_क्रम_each_possible_encoder(connector, encoder)
		वापस encoder;

	वापस शून्य;
पूर्ण

अटल व्योम amdgpu_get_native_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder = amdgpu_connector_best_single_encoder(connector);
	काष्ठा amdgpu_encoder *amdgpu_encoder;

	अगर (encoder == शून्य)
		वापस;

	amdgpu_encoder = to_amdgpu_encoder(encoder);

	अगर (!list_empty(&connector->probed_modes)) अणु
		काष्ठा drm_display_mode *preferred_mode =
			list_first_entry(&connector->probed_modes,
					 काष्ठा drm_display_mode, head);

		amdgpu_encoder->native_mode = *preferred_mode;
	पूर्ण अन्यथा अणु
		amdgpu_encoder->native_mode.घड़ी = 0;
	पूर्ण
पूर्ण

अटल काष्ठा drm_display_mode *
amdgpu_connector_lcd_native_mode(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

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

अटल व्योम amdgpu_connector_add_common_modes(काष्ठा drm_encoder *encoder,
					       काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;
	पूर्णांक i;
	अटल स्थिर काष्ठा mode_size अणु
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
		अगर (amdgpu_encoder->devices & (ATOM_DEVICE_TV_SUPPORT)) अणु
			अगर (common_modes[i].w > 1024 ||
			    common_modes[i].h > 768)
				जारी;
		पूर्ण
		अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
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

अटल पूर्णांक amdgpu_connector_set_property(काष्ठा drm_connector *connector,
					  काष्ठा drm_property *property,
					  uपूर्णांक64_t val)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;

	अगर (property == adev->mode_info.coherent_mode_property) अणु
		काष्ठा amdgpu_encoder_atom_dig *dig;
		bool new_coherent_mode;

		/* need to find digital encoder on connector */
		encoder = amdgpu_connector_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		amdgpu_encoder = to_amdgpu_encoder(encoder);

		अगर (!amdgpu_encoder->enc_priv)
			वापस 0;

		dig = amdgpu_encoder->enc_priv;
		new_coherent_mode = val ? true : false;
		अगर (dig->coherent_mode != new_coherent_mode) अणु
			dig->coherent_mode = new_coherent_mode;
			amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == adev->mode_info.audio_property) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		/* need to find digital encoder on connector */
		encoder = amdgpu_connector_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		amdgpu_encoder = to_amdgpu_encoder(encoder);

		अगर (amdgpu_connector->audio != val) अणु
			amdgpu_connector->audio = val;
			amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == adev->mode_info.dither_property) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		/* need to find digital encoder on connector */
		encoder = amdgpu_connector_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		amdgpu_encoder = to_amdgpu_encoder(encoder);

		अगर (amdgpu_connector->dither != val) अणु
			amdgpu_connector->dither = val;
			amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == adev->mode_info.underscan_property) अणु
		/* need to find digital encoder on connector */
		encoder = amdgpu_connector_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		amdgpu_encoder = to_amdgpu_encoder(encoder);

		अगर (amdgpu_encoder->underscan_type != val) अणु
			amdgpu_encoder->underscan_type = val;
			amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == adev->mode_info.underscan_hborder_property) अणु
		/* need to find digital encoder on connector */
		encoder = amdgpu_connector_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		amdgpu_encoder = to_amdgpu_encoder(encoder);

		अगर (amdgpu_encoder->underscan_hborder != val) अणु
			amdgpu_encoder->underscan_hborder = val;
			amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == adev->mode_info.underscan_vborder_property) अणु
		/* need to find digital encoder on connector */
		encoder = amdgpu_connector_find_encoder(connector, DRM_MODE_ENCODER_TMDS);
		अगर (!encoder)
			वापस 0;

		amdgpu_encoder = to_amdgpu_encoder(encoder);

		अगर (amdgpu_encoder->underscan_vborder != val) अणु
			amdgpu_encoder->underscan_vborder = val;
			amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
		पूर्ण
	पूर्ण

	अगर (property == adev->mode_info.load_detect_property) अणु
		काष्ठा amdgpu_connector *amdgpu_connector =
			to_amdgpu_connector(connector);

		अगर (val == 0)
			amdgpu_connector->dac_load_detect = false;
		अन्यथा
			amdgpu_connector->dac_load_detect = true;
	पूर्ण

	अगर (property == dev->mode_config.scaling_mode_property) अणु
		क्रमागत amdgpu_rmx_type rmx_type;

		अगर (connector->encoder) अणु
			amdgpu_encoder = to_amdgpu_encoder(connector->encoder);
		पूर्ण अन्यथा अणु
			स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs = connector->helper_निजी;
			amdgpu_encoder = to_amdgpu_encoder(connector_funcs->best_encoder(connector));
		पूर्ण

		चयन (val) अणु
		शेष:
		हाल DRM_MODE_SCALE_NONE: rmx_type = RMX_OFF; अवरोध;
		हाल DRM_MODE_SCALE_CENTER: rmx_type = RMX_CENTER; अवरोध;
		हाल DRM_MODE_SCALE_ASPECT: rmx_type = RMX_ASPECT; अवरोध;
		हाल DRM_MODE_SCALE_FULLSCREEN: rmx_type = RMX_FULL; अवरोध;
		पूर्ण
		अगर (amdgpu_encoder->rmx_type == rmx_type)
			वापस 0;

		अगर ((rmx_type != DRM_MODE_SCALE_NONE) &&
		    (amdgpu_encoder->native_mode.घड़ी == 0))
			वापस 0;

		amdgpu_encoder->rmx_type = rmx_type;

		amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
amdgpu_connector_fixup_lcd_native_mode(काष्ठा drm_encoder *encoder,
					काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder =	to_amdgpu_encoder(encoder);
	काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;
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
		amdgpu_encoder->rmx_type = RMX_OFF;
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_connector_lvds_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;
	पूर्णांक ret = 0;
	काष्ठा drm_display_mode *mode;

	amdgpu_connector_get_edid(connector);
	ret = amdgpu_connector_ddc_get_modes(connector);
	अगर (ret > 0) अणु
		encoder = amdgpu_connector_best_single_encoder(connector);
		अगर (encoder) अणु
			amdgpu_connector_fixup_lcd_native_mode(encoder, connector);
			/* add scaled modes */
			amdgpu_connector_add_common_modes(encoder, connector);
		पूर्ण
		वापस ret;
	पूर्ण

	encoder = amdgpu_connector_best_single_encoder(connector);
	अगर (!encoder)
		वापस 0;

	/* we have no EDID modes */
	mode = amdgpu_connector_lcd_native_mode(encoder);
	अगर (mode) अणु
		ret = 1;
		drm_mode_probed_add(connector, mode);
		/* add the width/height from vbios tables अगर available */
		connector->display_info.width_mm = mode->width_mm;
		connector->display_info.height_mm = mode->height_mm;
		/* add scaled modes */
		amdgpu_connector_add_common_modes(encoder, connector);
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status amdgpu_connector_lvds_mode_valid(काष्ठा drm_connector *connector,
					     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_encoder *encoder = amdgpu_connector_best_single_encoder(connector);

	अगर ((mode->hdisplay < 320) || (mode->vdisplay < 240))
		वापस MODE_PANEL;

	अगर (encoder) अणु
		काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
		काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

		/* AVIVO hardware supports करोwnscaling modes larger than the panel
		 * to the panel size, but I'm not sure this is desirable.
		 */
		अगर ((mode->hdisplay > native_mode->hdisplay) ||
		    (mode->vdisplay > native_mode->vdisplay))
			वापस MODE_PANEL;

		/* अगर scaling is disabled, block non-native modes */
		अगर (amdgpu_encoder->rmx_type == RMX_OFF) अणु
			अगर ((mode->hdisplay != native_mode->hdisplay) ||
			    (mode->vdisplay != native_mode->vdisplay))
				वापस MODE_PANEL;
		पूर्ण
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_connector_status
amdgpu_connector_lvds_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा drm_encoder *encoder = amdgpu_connector_best_single_encoder(connector);
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
		काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
		काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

		/* check अगर panel is valid */
		अगर (native_mode->hdisplay >= 320 && native_mode->vdisplay >= 240)
			ret = connector_status_connected;

	पूर्ण

	/* check क्रम edid as well */
	amdgpu_connector_get_edid(connector);
	अगर (amdgpu_connector->edid)
		ret = connector_status_connected;
	/* check acpi lid status ??? */

	amdgpu_connector_update_scratch_regs(connector, ret);

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम amdgpu_connector_unरेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	अगर (amdgpu_connector->ddc_bus && amdgpu_connector->ddc_bus->has_aux) अणु
		drm_dp_aux_unरेजिस्टर(&amdgpu_connector->ddc_bus->aux);
		amdgpu_connector->ddc_bus->has_aux = false;
	पूर्ण
पूर्ण

अटल व्योम amdgpu_connector_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	amdgpu_connector_मुक्त_edid(connector);
	kमुक्त(amdgpu_connector->con_priv);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल पूर्णांक amdgpu_connector_set_lcd_property(काष्ठा drm_connector *connector,
					      काष्ठा drm_property *property,
					      uपूर्णांक64_t value)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder;
	क्रमागत amdgpu_rmx_type rmx_type;

	DRM_DEBUG_KMS("\n");
	अगर (property != dev->mode_config.scaling_mode_property)
		वापस 0;

	अगर (connector->encoder)
		amdgpu_encoder = to_amdgpu_encoder(connector->encoder);
	अन्यथा अणु
		स्थिर काष्ठा drm_connector_helper_funcs *connector_funcs = connector->helper_निजी;
		amdgpu_encoder = to_amdgpu_encoder(connector_funcs->best_encoder(connector));
	पूर्ण

	चयन (value) अणु
	हाल DRM_MODE_SCALE_NONE: rmx_type = RMX_OFF; अवरोध;
	हाल DRM_MODE_SCALE_CENTER: rmx_type = RMX_CENTER; अवरोध;
	हाल DRM_MODE_SCALE_ASPECT: rmx_type = RMX_ASPECT; अवरोध;
	शेष:
	हाल DRM_MODE_SCALE_FULLSCREEN: rmx_type = RMX_FULL; अवरोध;
	पूर्ण
	अगर (amdgpu_encoder->rmx_type == rmx_type)
		वापस 0;

	amdgpu_encoder->rmx_type = rmx_type;

	amdgpu_connector_property_change_mode(&amdgpu_encoder->base);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा drm_connector_helper_funcs amdgpu_connector_lvds_helper_funcs = अणु
	.get_modes = amdgpu_connector_lvds_get_modes,
	.mode_valid = amdgpu_connector_lvds_mode_valid,
	.best_encoder = amdgpu_connector_best_single_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs amdgpu_connector_lvds_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = amdgpu_connector_lvds_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.early_unरेजिस्टर = amdgpu_connector_unरेजिस्टर,
	.destroy = amdgpu_connector_destroy,
	.set_property = amdgpu_connector_set_lcd_property,
पूर्ण;

अटल पूर्णांक amdgpu_connector_vga_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक ret;

	amdgpu_connector_get_edid(connector);
	ret = amdgpu_connector_ddc_get_modes(connector);

	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status amdgpu_connector_vga_mode_valid(काष्ठा drm_connector *connector,
					    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	/* XXX check mode bandwidth */

	अगर ((mode->घड़ी / 10) > adev->घड़ी.max_pixel_घड़ी)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल क्रमागत drm_connector_status
amdgpu_connector_vga_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
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

	encoder = amdgpu_connector_best_single_encoder(connector);
	अगर (!encoder)
		ret = connector_status_disconnected;

	अगर (amdgpu_connector->ddc_bus)
		dret = amdgpu_display_ddc_probe(amdgpu_connector, false);
	अगर (dret) अणु
		amdgpu_connector->detected_by_load = false;
		amdgpu_connector_मुक्त_edid(connector);
		amdgpu_connector_get_edid(connector);

		अगर (!amdgpu_connector->edid) अणु
			DRM_ERROR("%s: probed a monitor but no|invalid EDID\n",
					connector->name);
			ret = connector_status_connected;
		पूर्ण अन्यथा अणु
			amdgpu_connector->use_digital =
				!!(amdgpu_connector->edid->input & DRM_EDID_INPUT_DIGITAL);

			/* some oems have boards with separate digital and analog connectors
			 * with a shared ddc line (often vga + hdmi)
			 */
			अगर (amdgpu_connector->use_digital && amdgpu_connector->shared_ddc) अणु
				amdgpu_connector_मुक्त_edid(connector);
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
			अगर (amdgpu_connector->detected_by_load)
				ret = connector->status;
			जाओ out;
		पूर्ण

		अगर (amdgpu_connector->dac_load_detect && encoder) अणु
			encoder_funcs = encoder->helper_निजी;
			ret = encoder_funcs->detect(encoder, connector);
			अगर (ret != connector_status_disconnected)
				amdgpu_connector->detected_by_load = true;
		पूर्ण
	पूर्ण

	amdgpu_connector_update_scratch_regs(connector, ret);

out:
	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs amdgpu_connector_vga_helper_funcs = अणु
	.get_modes = amdgpu_connector_vga_get_modes,
	.mode_valid = amdgpu_connector_vga_mode_valid,
	.best_encoder = amdgpu_connector_best_single_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs amdgpu_connector_vga_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = amdgpu_connector_vga_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.early_unरेजिस्टर = amdgpu_connector_unरेजिस्टर,
	.destroy = amdgpu_connector_destroy,
	.set_property = amdgpu_connector_set_property,
पूर्ण;

अटल bool
amdgpu_connector_check_hpd_status_unchanged(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	क्रमागत drm_connector_status status;

	अगर (amdgpu_connector->hpd.hpd != AMDGPU_HPD_NONE) अणु
		अगर (amdgpu_display_hpd_sense(adev, amdgpu_connector->hpd.hpd))
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
amdgpu_connector_dvi_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
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

	अगर (!क्रमce && amdgpu_connector_check_hpd_status_unchanged(connector)) अणु
		ret = connector->status;
		जाओ निकास;
	पूर्ण

	अगर (amdgpu_connector->ddc_bus)
		dret = amdgpu_display_ddc_probe(amdgpu_connector, false);
	अगर (dret) अणु
		amdgpu_connector->detected_by_load = false;
		amdgpu_connector_मुक्त_edid(connector);
		amdgpu_connector_get_edid(connector);

		अगर (!amdgpu_connector->edid) अणु
			DRM_ERROR("%s: probed a monitor but no|invalid EDID\n",
					connector->name);
			ret = connector_status_connected;
			broken_edid = true; /* defer use_digital to later */
		पूर्ण अन्यथा अणु
			amdgpu_connector->use_digital =
				!!(amdgpu_connector->edid->input & DRM_EDID_INPUT_DIGITAL);

			/* some oems have boards with separate digital and analog connectors
			 * with a shared ddc line (often vga + hdmi)
			 */
			अगर ((!amdgpu_connector->use_digital) && amdgpu_connector->shared_ddc) अणु
				amdgpu_connector_मुक्त_edid(connector);
				ret = connector_status_disconnected;
			पूर्ण अन्यथा अणु
				ret = connector_status_connected;
			पूर्ण

			/* This माला_लो complicated.  We have boards with VGA + HDMI with a
			 * shared DDC line and we have boards with DVI-D + HDMI with a shared
			 * DDC line.  The latter is more complex because with DVI<->HDMI adapters
			 * you करोn't really know what's connected to which port as both are digital.
			 */
			अगर (amdgpu_connector->shared_ddc && (ret == connector_status_connected)) अणु
				काष्ठा drm_connector *list_connector;
				काष्ठा drm_connector_list_iter iter;
				काष्ठा amdgpu_connector *list_amdgpu_connector;

				drm_connector_list_iter_begin(dev, &iter);
				drm_क्रम_each_connector_iter(list_connector,
							    &iter) अणु
					अगर (connector == list_connector)
						जारी;
					list_amdgpu_connector = to_amdgpu_connector(list_connector);
					अगर (list_amdgpu_connector->shared_ddc &&
					    (list_amdgpu_connector->ddc_bus->rec.i2c_id ==
					     amdgpu_connector->ddc_bus->rec.i2c_id)) अणु
						/* हालs where both connectors are digital */
						अगर (list_connector->connector_type != DRM_MODE_CONNECTOR_VGA) अणु
							/* hpd is our only option in this हाल */
							अगर (!amdgpu_display_hpd_sense(adev, amdgpu_connector->hpd.hpd)) अणु
								amdgpu_connector_मुक्त_edid(connector);
								ret = connector_status_disconnected;
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
				drm_connector_list_iter_end(&iter);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((ret == connector_status_connected) && (amdgpu_connector->use_digital == true))
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
		अगर (amdgpu_connector->detected_by_load)
			ret = connector->status;
		जाओ out;
	पूर्ण

	/* find analog encoder */
	अगर (amdgpu_connector->dac_load_detect) अणु
		काष्ठा drm_encoder *encoder;

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
							amdgpu_connector->use_digital = false;
						पूर्ण
						अगर (ret != connector_status_disconnected)
							amdgpu_connector->detected_by_load = true;
					पूर्ण
				पूर्ण अन्यथा अणु
					क्रमागत drm_connector_status lret;
					/* assume digital unless load detected otherwise */
					amdgpu_connector->use_digital = true;
					lret = encoder_funcs->detect(encoder, connector);
					DRM_DEBUG_KMS("load_detect %x returned: %x\n",encoder->encoder_type,lret);
					अगर (lret == connector_status_connected)
						amdgpu_connector->use_digital = false;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	/* updated in get modes as well since we need to know अगर it's analog or digital */
	amdgpu_connector_update_scratch_regs(connector, ret);

निकास:
	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	वापस ret;
पूर्ण

/* okay need to be smart in here about which encoder to pick */
अटल काष्ठा drm_encoder *
amdgpu_connector_dvi_encoder(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा drm_encoder *encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		अगर (amdgpu_connector->use_digital == true) अणु
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

अटल व्योम amdgpu_connector_dvi_क्रमce(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	अगर (connector->क्रमce == DRM_FORCE_ON)
		amdgpu_connector->use_digital = false;
	अगर (connector->क्रमce == DRM_FORCE_ON_DIGITAL)
		amdgpu_connector->use_digital = true;
पूर्ण

अटल क्रमागत drm_mode_status amdgpu_connector_dvi_mode_valid(काष्ठा drm_connector *connector,
					    काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	/* XXX check mode bandwidth */

	अगर (amdgpu_connector->use_digital && (mode->घड़ी > 165000)) अणु
		अगर ((amdgpu_connector->connector_object_id == CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_I) ||
		    (amdgpu_connector->connector_object_id == CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D) ||
		    (amdgpu_connector->connector_object_id == CONNECTOR_OBJECT_ID_HDMI_TYPE_B)) अणु
			वापस MODE_OK;
		पूर्ण अन्यथा अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
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
	अगर ((mode->घड़ी / 10) > adev->घड़ी.max_pixel_घड़ी)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs amdgpu_connector_dvi_helper_funcs = अणु
	.get_modes = amdgpu_connector_vga_get_modes,
	.mode_valid = amdgpu_connector_dvi_mode_valid,
	.best_encoder = amdgpu_connector_dvi_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs amdgpu_connector_dvi_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = amdgpu_connector_dvi_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = amdgpu_connector_set_property,
	.early_unरेजिस्टर = amdgpu_connector_unरेजिस्टर,
	.destroy = amdgpu_connector_destroy,
	.क्रमce = amdgpu_connector_dvi_क्रमce,
पूर्ण;

अटल पूर्णांक amdgpu_connector_dp_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा amdgpu_connector_atom_dig *amdgpu_dig_connector = amdgpu_connector->con_priv;
	काष्ठा drm_encoder *encoder = amdgpu_connector_best_single_encoder(connector);
	पूर्णांक ret;

	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) अणु
		काष्ठा drm_display_mode *mode;

		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
			अगर (!amdgpu_dig_connector->edp_on)
				amdgpu_atombios_encoder_set_edp_panel_घातer(connector,
								     ATOM_TRANSMITTER_ACTION_POWER_ON);
			amdgpu_connector_get_edid(connector);
			ret = amdgpu_connector_ddc_get_modes(connector);
			अगर (!amdgpu_dig_connector->edp_on)
				amdgpu_atombios_encoder_set_edp_panel_घातer(connector,
								     ATOM_TRANSMITTER_ACTION_POWER_OFF);
		पूर्ण अन्यथा अणु
			/* need to setup ddc on the bridge */
			अगर (amdgpu_connector_encoder_get_dp_bridge_encoder_id(connector) !=
			    ENCODER_OBJECT_ID_NONE) अणु
				अगर (encoder)
					amdgpu_atombios_encoder_setup_ext_encoder_ddc(encoder);
			पूर्ण
			amdgpu_connector_get_edid(connector);
			ret = amdgpu_connector_ddc_get_modes(connector);
		पूर्ण

		अगर (ret > 0) अणु
			अगर (encoder) अणु
				amdgpu_connector_fixup_lcd_native_mode(encoder, connector);
				/* add scaled modes */
				amdgpu_connector_add_common_modes(encoder, connector);
			पूर्ण
			वापस ret;
		पूर्ण

		अगर (!encoder)
			वापस 0;

		/* we have no EDID modes */
		mode = amdgpu_connector_lcd_native_mode(encoder);
		अगर (mode) अणु
			ret = 1;
			drm_mode_probed_add(connector, mode);
			/* add the width/height from vbios tables अगर available */
			connector->display_info.width_mm = mode->width_mm;
			connector->display_info.height_mm = mode->height_mm;
			/* add scaled modes */
			amdgpu_connector_add_common_modes(encoder, connector);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* need to setup ddc on the bridge */
		अगर (amdgpu_connector_encoder_get_dp_bridge_encoder_id(connector) !=
			ENCODER_OBJECT_ID_NONE) अणु
			अगर (encoder)
				amdgpu_atombios_encoder_setup_ext_encoder_ddc(encoder);
		पूर्ण
		amdgpu_connector_get_edid(connector);
		ret = amdgpu_connector_ddc_get_modes(connector);

		amdgpu_get_native_mode(connector);
	पूर्ण

	वापस ret;
पूर्ण

u16 amdgpu_connector_encoder_get_dp_bridge_encoder_id(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		amdgpu_encoder = to_amdgpu_encoder(encoder);

		चयन (amdgpu_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_TRAVIS:
		हाल ENCODER_OBJECT_ID_NUTMEG:
			वापस amdgpu_encoder->encoder_id;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ENCODER_OBJECT_ID_NONE;
पूर्ण

अटल bool amdgpu_connector_encoder_is_hbr2(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;
	bool found = false;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		amdgpu_encoder = to_amdgpu_encoder(encoder);
		अगर (amdgpu_encoder->caps & ATOM_ENCODER_CAP_RECORD_HBR2)
			found = true;
	पूर्ण

	वापस found;
पूर्ण

bool amdgpu_connector_is_dp12_capable(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	अगर ((adev->घड़ी.शेष_dispclk >= 53900) &&
	    amdgpu_connector_encoder_is_hbr2(connector)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल क्रमागत drm_connector_status
amdgpu_connector_dp_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	क्रमागत drm_connector_status ret = connector_status_disconnected;
	काष्ठा amdgpu_connector_atom_dig *amdgpu_dig_connector = amdgpu_connector->con_priv;
	काष्ठा drm_encoder *encoder = amdgpu_connector_best_single_encoder(connector);
	पूर्णांक r;

	अगर (!drm_kms_helper_is_poll_worker()) अणु
		r = pm_runसमय_get_sync(connector->dev->dev);
		अगर (r < 0) अणु
			pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
			वापस connector_status_disconnected;
		पूर्ण
	पूर्ण

	अगर (!क्रमce && amdgpu_connector_check_hpd_status_unchanged(connector)) अणु
		ret = connector->status;
		जाओ out;
	पूर्ण

	amdgpu_connector_मुक्त_edid(connector);

	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) अणु
		अगर (encoder) अणु
			काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
			काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

			/* check अगर panel is valid */
			अगर (native_mode->hdisplay >= 320 && native_mode->vdisplay >= 240)
				ret = connector_status_connected;
		पूर्ण
		/* eDP is always DP */
		amdgpu_dig_connector->dp_sink_type = CONNECTOR_OBJECT_ID_DISPLAYPORT;
		अगर (!amdgpu_dig_connector->edp_on)
			amdgpu_atombios_encoder_set_edp_panel_घातer(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_ON);
		अगर (!amdgpu_atombios_dp_get_dpcd(amdgpu_connector))
			ret = connector_status_connected;
		अगर (!amdgpu_dig_connector->edp_on)
			amdgpu_atombios_encoder_set_edp_panel_घातer(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_OFF);
	पूर्ण अन्यथा अगर (amdgpu_connector_encoder_get_dp_bridge_encoder_id(connector) !=
		   ENCODER_OBJECT_ID_NONE) अणु
		/* DP bridges are always DP */
		amdgpu_dig_connector->dp_sink_type = CONNECTOR_OBJECT_ID_DISPLAYPORT;
		/* get the DPCD from the bridge */
		amdgpu_atombios_dp_get_dpcd(amdgpu_connector);

		अगर (encoder) अणु
			/* setup ddc on the bridge */
			amdgpu_atombios_encoder_setup_ext_encoder_ddc(encoder);
			/* bridge chips are always aux */
			/* try DDC */
			अगर (amdgpu_display_ddc_probe(amdgpu_connector, true))
				ret = connector_status_connected;
			अन्यथा अगर (amdgpu_connector->dac_load_detect) अणु /* try load detection */
				स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs = encoder->helper_निजी;
				ret = encoder_funcs->detect(encoder, connector);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		amdgpu_dig_connector->dp_sink_type =
			amdgpu_atombios_dp_get_sinktype(amdgpu_connector);
		अगर (amdgpu_display_hpd_sense(adev, amdgpu_connector->hpd.hpd)) अणु
			ret = connector_status_connected;
			अगर (amdgpu_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT)
				amdgpu_atombios_dp_get_dpcd(amdgpu_connector);
		पूर्ण अन्यथा अणु
			अगर (amdgpu_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) अणु
				अगर (!amdgpu_atombios_dp_get_dpcd(amdgpu_connector))
					ret = connector_status_connected;
			पूर्ण अन्यथा अणु
				/* try non-aux ddc (DP to DVI/HDMI/etc. adapter) */
				अगर (amdgpu_display_ddc_probe(amdgpu_connector,
							     false))
					ret = connector_status_connected;
			पूर्ण
		पूर्ण
	पूर्ण

	amdgpu_connector_update_scratch_regs(connector, ret);
out:
	अगर (!drm_kms_helper_is_poll_worker()) अणु
		pm_runसमय_mark_last_busy(connector->dev->dev);
		pm_runसमय_put_स्वतःsuspend(connector->dev->dev);
	पूर्ण

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector->connector_type == DRM_MODE_CONNECTOR_eDP)
		drm_dp_set_subconnector_property(&amdgpu_connector->base,
						 ret,
						 amdgpu_dig_connector->dpcd,
						 amdgpu_dig_connector->करोwnstream_ports);
	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status amdgpu_connector_dp_mode_valid(काष्ठा drm_connector *connector,
					   काष्ठा drm_display_mode *mode)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा amdgpu_connector_atom_dig *amdgpu_dig_connector = amdgpu_connector->con_priv;

	/* XXX check mode bandwidth */

	अगर ((connector->connector_type == DRM_MODE_CONNECTOR_eDP) ||
	    (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)) अणु
		काष्ठा drm_encoder *encoder = amdgpu_connector_best_single_encoder(connector);

		अगर ((mode->hdisplay < 320) || (mode->vdisplay < 240))
			वापस MODE_PANEL;

		अगर (encoder) अणु
			काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
			काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;

			/* AVIVO hardware supports करोwnscaling modes larger than the panel
			 * to the panel size, but I'm not sure this is desirable.
			 */
			अगर ((mode->hdisplay > native_mode->hdisplay) ||
			    (mode->vdisplay > native_mode->vdisplay))
				वापस MODE_PANEL;

			/* अगर scaling is disabled, block non-native modes */
			अगर (amdgpu_encoder->rmx_type == RMX_OFF) अणु
				अगर ((mode->hdisplay != native_mode->hdisplay) ||
				    (mode->vdisplay != native_mode->vdisplay))
					वापस MODE_PANEL;
			पूर्ण
		पूर्ण
		वापस MODE_OK;
	पूर्ण अन्यथा अणु
		अगर ((amdgpu_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (amdgpu_dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) अणु
			वापस amdgpu_atombios_dp_mode_valid_helper(connector, mode);
		पूर्ण अन्यथा अणु
			अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
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

अटल पूर्णांक
amdgpu_connector_late_रेजिस्टर(काष्ठा drm_connector *connector)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	पूर्णांक r = 0;

	अगर (amdgpu_connector->ddc_bus->has_aux) अणु
		amdgpu_connector->ddc_bus->aux.dev = amdgpu_connector->base.kdev;
		r = drm_dp_aux_रेजिस्टर(&amdgpu_connector->ddc_bus->aux);
	पूर्ण

	वापस r;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs amdgpu_connector_dp_helper_funcs = अणु
	.get_modes = amdgpu_connector_dp_get_modes,
	.mode_valid = amdgpu_connector_dp_mode_valid,
	.best_encoder = amdgpu_connector_dvi_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs amdgpu_connector_dp_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = amdgpu_connector_dp_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = amdgpu_connector_set_property,
	.early_unरेजिस्टर = amdgpu_connector_unरेजिस्टर,
	.destroy = amdgpu_connector_destroy,
	.क्रमce = amdgpu_connector_dvi_क्रमce,
	.late_रेजिस्टर = amdgpu_connector_late_रेजिस्टर,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs amdgpu_connector_edp_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = amdgpu_connector_dp_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = amdgpu_connector_set_lcd_property,
	.early_unरेजिस्टर = amdgpu_connector_unरेजिस्टर,
	.destroy = amdgpu_connector_destroy,
	.क्रमce = amdgpu_connector_dvi_क्रमce,
	.late_रेजिस्टर = amdgpu_connector_late_रेजिस्टर,
पूर्ण;

व्योम
amdgpu_connector_add(काष्ठा amdgpu_device *adev,
		      uपूर्णांक32_t connector_id,
		      uपूर्णांक32_t supported_device,
		      पूर्णांक connector_type,
		      काष्ठा amdgpu_i2c_bus_rec *i2c_bus,
		      uपूर्णांक16_t connector_object_id,
		      काष्ठा amdgpu_hpd *hpd,
		      काष्ठा amdgpu_router *router)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_connector *amdgpu_connector;
	काष्ठा amdgpu_connector_atom_dig *amdgpu_dig_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;
	काष्ठा i2c_adapter *ddc = शून्य;
	uपूर्णांक32_t subpixel_order = SubPixelNone;
	bool shared_ddc = false;
	bool is_dp_bridge = false;
	bool has_aux = false;

	अगर (connector_type == DRM_MODE_CONNECTOR_Unknown)
		वापस;

	/* see अगर we alपढ़ोy added it */
	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		amdgpu_connector = to_amdgpu_connector(connector);
		अगर (amdgpu_connector->connector_id == connector_id) अणु
			amdgpu_connector->devices |= supported_device;
			drm_connector_list_iter_end(&iter);
			वापस;
		पूर्ण
		अगर (amdgpu_connector->ddc_bus && i2c_bus->valid) अणु
			अगर (amdgpu_connector->ddc_bus->rec.i2c_id == i2c_bus->i2c_id) अणु
				amdgpu_connector->shared_ddc = true;
				shared_ddc = true;
			पूर्ण
			अगर (amdgpu_connector->router_bus && router->ddc_valid &&
			    (amdgpu_connector->router.router_id == router->router_id)) अणु
				amdgpu_connector->shared_ddc = false;
				shared_ddc = false;
			पूर्ण
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);

	/* check अगर it's a dp bridge */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		amdgpu_encoder = to_amdgpu_encoder(encoder);
		अगर (amdgpu_encoder->devices & supported_device) अणु
			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_TRAVIS:
			हाल ENCODER_OBJECT_ID_NUTMEG:
				is_dp_bridge = true;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	amdgpu_connector = kzalloc(माप(काष्ठा amdgpu_connector), GFP_KERNEL);
	अगर (!amdgpu_connector)
		वापस;

	connector = &amdgpu_connector->base;

	amdgpu_connector->connector_id = connector_id;
	amdgpu_connector->devices = supported_device;
	amdgpu_connector->shared_ddc = shared_ddc;
	amdgpu_connector->connector_object_id = connector_object_id;
	amdgpu_connector->hpd = *hpd;

	amdgpu_connector->router = *router;
	अगर (router->ddc_valid || router->cd_valid) अणु
		amdgpu_connector->router_bus = amdgpu_i2c_lookup(adev, &router->i2c_info);
		अगर (!amdgpu_connector->router_bus)
			DRM_ERROR("Failed to assign router i2c bus! Check dmesg for i2c errors.\n");
	पूर्ण

	अगर (is_dp_bridge) अणु
		amdgpu_dig_connector = kzalloc(माप(काष्ठा amdgpu_connector_atom_dig), GFP_KERNEL);
		अगर (!amdgpu_dig_connector)
			जाओ failed;
		amdgpu_connector->con_priv = amdgpu_dig_connector;
		अगर (i2c_bus->valid) अणु
			amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
			अगर (amdgpu_connector->ddc_bus) अणु
				has_aux = true;
				ddc = &amdgpu_connector->ddc_bus->adapter;
			पूर्ण अन्यथा अणु
				DRM_ERROR("DP: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
			पूर्ण
		पूर्ण
		चयन (connector_type) अणु
		हाल DRM_MODE_CONNECTOR_VGA:
		हाल DRM_MODE_CONNECTOR_DVIA:
		शेष:
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_dp_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base,
						 &amdgpu_connector_dp_helper_funcs);
			connector->पूर्णांकerlace_allowed = true;
			connector->द्विगुनscan_allowed = true;
			amdgpu_connector->dac_load_detect = true;
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.load_detect_property,
						      1);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DVII:
		हाल DRM_MODE_CONNECTOR_DVID:
		हाल DRM_MODE_CONNECTOR_HDMIA:
		हाल DRM_MODE_CONNECTOR_HDMIB:
		हाल DRM_MODE_CONNECTOR_DisplayPort:
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_dp_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base,
						 &amdgpu_connector_dp_helper_funcs);
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.underscan_property,
						      UNDERSCAN_OFF);
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.underscan_hborder_property,
						      0);
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.underscan_vborder_property,
						      0);

			drm_object_attach_property(&amdgpu_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);

			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.dither_property,
						   AMDGPU_FMT_DITHER_DISABLE);

			अगर (amdgpu_audio != 0)
				drm_object_attach_property(&amdgpu_connector->base.base,
							   adev->mode_info.audio_property,
							   AMDGPU_AUDIO_AUTO);

			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = true;
			अगर (connector_type == DRM_MODE_CONNECTOR_HDMIB)
				connector->द्विगुनscan_allowed = true;
			अन्यथा
				connector->द्विगुनscan_allowed = false;
			अगर (connector_type == DRM_MODE_CONNECTOR_DVII) अणु
				amdgpu_connector->dac_load_detect = true;
				drm_object_attach_property(&amdgpu_connector->base.base,
							      adev->mode_info.load_detect_property,
							      1);
			पूर्ण
			अवरोध;
		हाल DRM_MODE_CONNECTOR_LVDS:
		हाल DRM_MODE_CONNECTOR_eDP:
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_edp_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base,
						 &amdgpu_connector_dp_helper_funcs);
			drm_object_attach_property(&amdgpu_connector->base.base,
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
				amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
				अगर (!amdgpu_connector->ddc_bus)
					DRM_ERROR("VGA: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &amdgpu_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_vga_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base, &amdgpu_connector_vga_helper_funcs);
			amdgpu_connector->dac_load_detect = true;
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.load_detect_property,
						      1);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);
			/* no HPD on analog connectors */
			amdgpu_connector->hpd.hpd = AMDGPU_HPD_NONE;
			connector->पूर्णांकerlace_allowed = true;
			connector->द्विगुनscan_allowed = true;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DVIA:
			अगर (i2c_bus->valid) अणु
				amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
				अगर (!amdgpu_connector->ddc_bus)
					DRM_ERROR("DVIA: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &amdgpu_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_vga_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base, &amdgpu_connector_vga_helper_funcs);
			amdgpu_connector->dac_load_detect = true;
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.load_detect_property,
						      1);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);
			/* no HPD on analog connectors */
			amdgpu_connector->hpd.hpd = AMDGPU_HPD_NONE;
			connector->पूर्णांकerlace_allowed = true;
			connector->द्विगुनscan_allowed = true;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DVII:
		हाल DRM_MODE_CONNECTOR_DVID:
			amdgpu_dig_connector = kzalloc(माप(काष्ठा amdgpu_connector_atom_dig), GFP_KERNEL);
			अगर (!amdgpu_dig_connector)
				जाओ failed;
			amdgpu_connector->con_priv = amdgpu_dig_connector;
			अगर (i2c_bus->valid) अणु
				amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
				अगर (!amdgpu_connector->ddc_bus)
					DRM_ERROR("DVI: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &amdgpu_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_dvi_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base, &amdgpu_connector_dvi_helper_funcs);
			subpixel_order = SubPixelHorizontalRGB;
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.coherent_mode_property,
						      1);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_property,
						   UNDERSCAN_OFF);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_hborder_property,
						   0);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_vborder_property,
						   0);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);

			अगर (amdgpu_audio != 0) अणु
				drm_object_attach_property(&amdgpu_connector->base.base,
							   adev->mode_info.audio_property,
							   AMDGPU_AUDIO_AUTO);
			पूर्ण
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.dither_property,
						   AMDGPU_FMT_DITHER_DISABLE);
			अगर (connector_type == DRM_MODE_CONNECTOR_DVII) अणु
				amdgpu_connector->dac_load_detect = true;
				drm_object_attach_property(&amdgpu_connector->base.base,
							   adev->mode_info.load_detect_property,
							   1);
			पूर्ण
			connector->पूर्णांकerlace_allowed = true;
			अगर (connector_type == DRM_MODE_CONNECTOR_DVII)
				connector->द्विगुनscan_allowed = true;
			अन्यथा
				connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_HDMIA:
		हाल DRM_MODE_CONNECTOR_HDMIB:
			amdgpu_dig_connector = kzalloc(माप(काष्ठा amdgpu_connector_atom_dig), GFP_KERNEL);
			अगर (!amdgpu_dig_connector)
				जाओ failed;
			amdgpu_connector->con_priv = amdgpu_dig_connector;
			अगर (i2c_bus->valid) अणु
				amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
				अगर (!amdgpu_connector->ddc_bus)
					DRM_ERROR("HDMI: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &amdgpu_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_dvi_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base, &amdgpu_connector_dvi_helper_funcs);
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.coherent_mode_property,
						      1);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_property,
						   UNDERSCAN_OFF);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_hborder_property,
						   0);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_vborder_property,
						   0);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);
			अगर (amdgpu_audio != 0) अणु
				drm_object_attach_property(&amdgpu_connector->base.base,
							   adev->mode_info.audio_property,
							   AMDGPU_AUDIO_AUTO);
			पूर्ण
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.dither_property,
						   AMDGPU_FMT_DITHER_DISABLE);
			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = true;
			अगर (connector_type == DRM_MODE_CONNECTOR_HDMIB)
				connector->द्विगुनscan_allowed = true;
			अन्यथा
				connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_DisplayPort:
			amdgpu_dig_connector = kzalloc(माप(काष्ठा amdgpu_connector_atom_dig), GFP_KERNEL);
			अगर (!amdgpu_dig_connector)
				जाओ failed;
			amdgpu_connector->con_priv = amdgpu_dig_connector;
			अगर (i2c_bus->valid) अणु
				amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
				अगर (amdgpu_connector->ddc_bus) अणु
					has_aux = true;
					ddc = &amdgpu_connector->ddc_bus->adapter;
				पूर्ण अन्यथा अणु
					DRM_ERROR("DP: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				पूर्ण
			पूर्ण
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_dp_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base, &amdgpu_connector_dp_helper_funcs);
			subpixel_order = SubPixelHorizontalRGB;
			drm_object_attach_property(&amdgpu_connector->base.base,
						      adev->mode_info.coherent_mode_property,
						      1);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_property,
						   UNDERSCAN_OFF);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_hborder_property,
						   0);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.underscan_vborder_property,
						   0);
			drm_object_attach_property(&amdgpu_connector->base.base,
						   dev->mode_config.scaling_mode_property,
						   DRM_MODE_SCALE_NONE);
			अगर (amdgpu_audio != 0) अणु
				drm_object_attach_property(&amdgpu_connector->base.base,
							   adev->mode_info.audio_property,
							   AMDGPU_AUDIO_AUTO);
			पूर्ण
			drm_object_attach_property(&amdgpu_connector->base.base,
						   adev->mode_info.dither_property,
						   AMDGPU_FMT_DITHER_DISABLE);
			connector->पूर्णांकerlace_allowed = true;
			/* in theory with a DP to VGA converter... */
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_eDP:
			amdgpu_dig_connector = kzalloc(माप(काष्ठा amdgpu_connector_atom_dig), GFP_KERNEL);
			अगर (!amdgpu_dig_connector)
				जाओ failed;
			amdgpu_connector->con_priv = amdgpu_dig_connector;
			अगर (i2c_bus->valid) अणु
				amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
				अगर (amdgpu_connector->ddc_bus) अणु
					has_aux = true;
					ddc = &amdgpu_connector->ddc_bus->adapter;
				पूर्ण अन्यथा अणु
					DRM_ERROR("DP: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				पूर्ण
			पूर्ण
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_edp_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base, &amdgpu_connector_dp_helper_funcs);
			drm_object_attach_property(&amdgpu_connector->base.base,
						      dev->mode_config.scaling_mode_property,
						      DRM_MODE_SCALE_FULLSCREEN);
			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = false;
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		हाल DRM_MODE_CONNECTOR_LVDS:
			amdgpu_dig_connector = kzalloc(माप(काष्ठा amdgpu_connector_atom_dig), GFP_KERNEL);
			अगर (!amdgpu_dig_connector)
				जाओ failed;
			amdgpu_connector->con_priv = amdgpu_dig_connector;
			अगर (i2c_bus->valid) अणु
				amdgpu_connector->ddc_bus = amdgpu_i2c_lookup(adev, i2c_bus);
				अगर (!amdgpu_connector->ddc_bus)
					DRM_ERROR("LVDS: Failed to assign ddc bus! Check dmesg for i2c errors.\n");
				अन्यथा
					ddc = &amdgpu_connector->ddc_bus->adapter;
			पूर्ण
			drm_connector_init_with_ddc(dev, &amdgpu_connector->base,
						    &amdgpu_connector_lvds_funcs,
						    connector_type,
						    ddc);
			drm_connector_helper_add(&amdgpu_connector->base, &amdgpu_connector_lvds_helper_funcs);
			drm_object_attach_property(&amdgpu_connector->base.base,
						      dev->mode_config.scaling_mode_property,
						      DRM_MODE_SCALE_FULLSCREEN);
			subpixel_order = SubPixelHorizontalRGB;
			connector->पूर्णांकerlace_allowed = false;
			connector->द्विगुनscan_allowed = false;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (amdgpu_connector->hpd.hpd == AMDGPU_HPD_NONE) अणु
		अगर (i2c_bus->valid) अणु
			connector->polled = DRM_CONNECTOR_POLL_CONNECT |
			                    DRM_CONNECTOR_POLL_DISCONNECT;
		पूर्ण
	पूर्ण अन्यथा
		connector->polled = DRM_CONNECTOR_POLL_HPD;

	connector->display_info.subpixel_order = subpixel_order;

	अगर (has_aux)
		amdgpu_atombios_dp_aux_init(amdgpu_connector);

	अगर (connector_type == DRM_MODE_CONNECTOR_DisplayPort ||
	    connector_type == DRM_MODE_CONNECTOR_eDP) अणु
		drm_connector_attach_dp_subconnector_property(&amdgpu_connector->base);
	पूर्ण

	वापस;

failed:
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण
