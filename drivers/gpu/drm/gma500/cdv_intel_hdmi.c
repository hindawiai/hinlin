<शैली गुरु>
/*
 * Copyright तऊ 2006-2011 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	jim liu <jim.liu@पूर्णांकel.com>
 */

#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "cdv_device.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

/* hdmi control bits */
#घोषणा HDMI_शून्य_PACKETS_DURING_VSYNC	(1 << 9)
#घोषणा HDMI_BORDER_ENABLE		(1 << 7)
#घोषणा HDMI_AUDIO_ENABLE		(1 << 6)
#घोषणा HDMI_VSYNC_ACTIVE_HIGH		(1 << 4)
#घोषणा HDMI_HSYNC_ACTIVE_HIGH		(1 << 3)
/* hdmi-b control bits */
#घोषणा	HDMIB_PIPE_B_SELECT		(1 << 30)


काष्ठा mid_पूर्णांकel_hdmi_priv अणु
	u32 hdmi_reg;
	u32 save_HDMIB;
	bool has_hdmi_sink;
	bool has_hdmi_audio;
	/* Should set this when detect hotplug */
	bool hdmi_device_connected;
	काष्ठा i2c_adapter *hdmi_i2c_adapter;	/* क्रम control functions */
	काष्ठा drm_device *dev;
पूर्ण;

अटल व्योम cdv_hdmi_mode_set(काष्ठा drm_encoder *encoder,
			काष्ठा drm_display_mode *mode,
			काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा gma_encoder *gma_encoder = to_gma_encoder(encoder);
	काष्ठा mid_पूर्णांकel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;
	u32 hdmib;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);

	hdmib = (2 << 10);

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		hdmib |= HDMI_VSYNC_ACTIVE_HIGH;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		hdmib |= HDMI_HSYNC_ACTIVE_HIGH;

	अगर (gma_crtc->pipe == 1)
		hdmib |= HDMIB_PIPE_B_SELECT;

	अगर (hdmi_priv->has_hdmi_audio) अणु
		hdmib |= HDMI_AUDIO_ENABLE;
		hdmib |= HDMI_शून्य_PACKETS_DURING_VSYNC;
	पूर्ण

	REG_WRITE(hdmi_priv->hdmi_reg, hdmib);
	REG_READ(hdmi_priv->hdmi_reg);
पूर्ण

अटल व्योम cdv_hdmi_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा gma_encoder *gma_encoder = to_gma_encoder(encoder);
	काष्ठा mid_पूर्णांकel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;
	u32 hdmib;

	hdmib = REG_READ(hdmi_priv->hdmi_reg);

	अगर (mode != DRM_MODE_DPMS_ON)
		REG_WRITE(hdmi_priv->hdmi_reg, hdmib & ~HDMIB_PORT_EN);
	अन्यथा
		REG_WRITE(hdmi_priv->hdmi_reg, hdmib | HDMIB_PORT_EN);
	REG_READ(hdmi_priv->hdmi_reg);
पूर्ण

अटल व्योम cdv_hdmi_save(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा mid_पूर्णांकel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;

	hdmi_priv->save_HDMIB = REG_READ(hdmi_priv->hdmi_reg);
पूर्ण

अटल व्योम cdv_hdmi_restore(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा mid_पूर्णांकel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;

	REG_WRITE(hdmi_priv->hdmi_reg, hdmi_priv->save_HDMIB);
	REG_READ(hdmi_priv->hdmi_reg);
पूर्ण

अटल क्रमागत drm_connector_status cdv_hdmi_detect(
				काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा mid_पूर्णांकel_hdmi_priv *hdmi_priv = gma_encoder->dev_priv;
	काष्ठा edid *edid = शून्य;
	क्रमागत drm_connector_status status = connector_status_disconnected;

	edid = drm_get_edid(connector, &gma_encoder->i2c_bus->adapter);

	hdmi_priv->has_hdmi_sink = false;
	hdmi_priv->has_hdmi_audio = false;
	अगर (edid) अणु
		अगर (edid->input & DRM_EDID_INPUT_DIGITAL) अणु
			status = connector_status_connected;
			hdmi_priv->has_hdmi_sink =
						drm_detect_hdmi_monitor(edid);
			hdmi_priv->has_hdmi_audio =
						drm_detect_monitor_audio(edid);
		पूर्ण
		kमुक्त(edid);
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक cdv_hdmi_set_property(काष्ठा drm_connector *connector,
				       काष्ठा drm_property *property,
				       uपूर्णांक64_t value)
अणु
	काष्ठा drm_encoder *encoder = connector->encoder;

	अगर (!म_भेद(property->name, "scaling mode") && encoder) अणु
		काष्ठा gma_crtc *crtc = to_gma_crtc(encoder->crtc);
		bool centre;
		uपूर्णांक64_t curValue;

		अगर (!crtc)
			वापस -1;

		चयन (value) अणु
		हाल DRM_MODE_SCALE_FULLSCREEN:
			अवरोध;
		हाल DRM_MODE_SCALE_NO_SCALE:
			अवरोध;
		हाल DRM_MODE_SCALE_ASPECT:
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण

		अगर (drm_object_property_get_value(&connector->base,
							property, &curValue))
			वापस -1;

		अगर (curValue == value)
			वापस 0;

		अगर (drm_object_property_set_value(&connector->base,
							property, value))
			वापस -1;

		centre = (curValue == DRM_MODE_SCALE_NO_SCALE) ||
			(value == DRM_MODE_SCALE_NO_SCALE);

		अगर (crtc->saved_mode.hdisplay != 0 &&
		    crtc->saved_mode.vdisplay != 0) अणु
			अगर (centre) अणु
				अगर (!drm_crtc_helper_set_mode(encoder->crtc, &crtc->saved_mode,
					    encoder->crtc->x, encoder->crtc->y, encoder->crtc->primary->fb))
					वापस -1;
			पूर्ण अन्यथा अणु
				स्थिर काष्ठा drm_encoder_helper_funcs *helpers
						    = encoder->helper_निजी;
				helpers->mode_set(encoder, &crtc->saved_mode,
					     &crtc->saved_adjusted_mode);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return the list of HDMI DDC modes अगर available.
 */
अटल पूर्णांक cdv_hdmi_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा edid *edid = शून्य;
	पूर्णांक ret = 0;

	edid = drm_get_edid(connector, &gma_encoder->i2c_bus->adapter);
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		ret = drm_add_edid_modes(connector, edid);
		kमुक्त(edid);
	पूर्ण
	वापस ret;
पूर्ण

अटल क्रमागत drm_mode_status cdv_hdmi_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	अगर (mode->घड़ी > 165000)
		वापस MODE_CLOCK_HIGH;
	अगर (mode->घड़ी < 20000)
		वापस MODE_CLOCK_HIGH;

	/* just in हाल */
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	/* just in हाल */
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	वापस MODE_OK;
पूर्ण

अटल व्योम cdv_hdmi_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);

	psb_पूर्णांकel_i2c_destroy(gma_encoder->i2c_bus);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs cdv_hdmi_helper_funcs = अणु
	.dpms = cdv_hdmi_dpms,
	.prepare = gma_encoder_prepare,
	.mode_set = cdv_hdmi_mode_set,
	.commit = gma_encoder_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs
					cdv_hdmi_connector_helper_funcs = अणु
	.get_modes = cdv_hdmi_get_modes,
	.mode_valid = cdv_hdmi_mode_valid,
	.best_encoder = gma_best_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs cdv_hdmi_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.detect = cdv_hdmi_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = cdv_hdmi_set_property,
	.destroy = cdv_hdmi_destroy,
पूर्ण;

व्योम cdv_hdmi_init(काष्ठा drm_device *dev,
			काष्ठा psb_पूर्णांकel_mode_device *mode_dev, पूर्णांक reg)
अणु
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा gma_connector *gma_connector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा mid_पूर्णांकel_hdmi_priv *hdmi_priv;
	पूर्णांक ddc_bus;

	gma_encoder = kzalloc(माप(काष्ठा gma_encoder), GFP_KERNEL);

	अगर (!gma_encoder)
		वापस;

	gma_connector = kzalloc(माप(काष्ठा gma_connector),
				      GFP_KERNEL);

	अगर (!gma_connector)
		जाओ err_connector;

	hdmi_priv = kzalloc(माप(काष्ठा mid_पूर्णांकel_hdmi_priv), GFP_KERNEL);

	अगर (!hdmi_priv)
		जाओ err_priv;

	connector = &gma_connector->base;
	connector->polled = DRM_CONNECTOR_POLL_HPD;
	gma_connector->save = cdv_hdmi_save;
	gma_connector->restore = cdv_hdmi_restore;

	encoder = &gma_encoder->base;
	drm_connector_init(dev, connector,
			   &cdv_hdmi_connector_funcs,
			   DRM_MODE_CONNECTOR_DVID);

	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_TMDS);

	gma_connector_attach_encoder(gma_connector, gma_encoder);
	gma_encoder->type = INTEL_OUTPUT_HDMI;
	hdmi_priv->hdmi_reg = reg;
	hdmi_priv->has_hdmi_sink = false;
	gma_encoder->dev_priv = hdmi_priv;

	drm_encoder_helper_add(encoder, &cdv_hdmi_helper_funcs);
	drm_connector_helper_add(connector,
				 &cdv_hdmi_connector_helper_funcs);
	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	drm_object_attach_property(&connector->base,
				      dev->mode_config.scaling_mode_property,
				      DRM_MODE_SCALE_FULLSCREEN);

	चयन (reg) अणु
	हाल SDVOB:
		ddc_bus = GPIOE;
		gma_encoder->ddi_select = DDI0_SELECT;
		अवरोध;
	हाल SDVOC:
		ddc_bus = GPIOD;
		gma_encoder->ddi_select = DDI1_SELECT;
		अवरोध;
	शेष:
		DRM_ERROR("unknown reg 0x%x for HDMI\n", reg);
		जाओ failed_ddc;
		अवरोध;
	पूर्ण

	gma_encoder->i2c_bus = psb_पूर्णांकel_i2c_create(dev,
				ddc_bus, (reg == SDVOB) ? "HDMIB" : "HDMIC");

	अगर (!gma_encoder->i2c_bus) अणु
		dev_err(dev->dev, "No ddc adapter available!\n");
		जाओ failed_ddc;
	पूर्ण

	hdmi_priv->hdmi_i2c_adapter = &(gma_encoder->i2c_bus->adapter);
	hdmi_priv->dev = dev;
	drm_connector_रेजिस्टर(connector);
	वापस;

failed_ddc:
	drm_encoder_cleanup(encoder);
	drm_connector_cleanup(connector);
err_priv:
	kमुक्त(gma_connector);
err_connector:
	kमुक्त(gma_encoder);
पूर्ण
