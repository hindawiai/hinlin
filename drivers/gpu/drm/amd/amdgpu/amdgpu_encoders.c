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

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_connectors.h"
#समावेश "amdgpu_display.h"
#समावेश "atom.h"
#समावेश "atombios_encoders.h"

व्योम
amdgpu_link_encoder_connector(काष्ठा drm_device *dev)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_connector *amdgpu_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा amdgpu_encoder *amdgpu_encoder;

	drm_connector_list_iter_begin(dev, &iter);
	/* walk the list and link encoders to connectors */
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		amdgpu_connector = to_amdgpu_connector(connector);
		list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
			amdgpu_encoder = to_amdgpu_encoder(encoder);
			अगर (amdgpu_encoder->devices & amdgpu_connector->devices) अणु
				drm_connector_attach_encoder(connector, encoder);
				अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
					amdgpu_atombios_encoder_init_backlight(amdgpu_encoder, connector);
					adev->mode_info.bl_encoder = amdgpu_encoder;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);
पूर्ण

व्योम amdgpu_encoder_set_active_device(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter iter;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		अगर (connector->encoder == encoder) अणु
			काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
			amdgpu_encoder->active_device = amdgpu_encoder->devices & amdgpu_connector->devices;
			DRM_DEBUG_KMS("setting active device to %08x from %08x %08x for encoder %d\n",
				  amdgpu_encoder->active_device, amdgpu_encoder->devices,
				  amdgpu_connector->devices, encoder->encoder_type);
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);
पूर्ण

काष्ठा drm_connector *
amdgpu_get_connector_क्रम_encoder(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_connector *connector, *found = शून्य;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_connector *amdgpu_connector;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		amdgpu_connector = to_amdgpu_connector(connector);
		अगर (amdgpu_encoder->active_device & amdgpu_connector->devices) अणु
			found = connector;
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);
	वापस found;
पूर्ण

काष्ठा drm_connector *
amdgpu_get_connector_क्रम_encoder_init(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_connector *connector, *found = शून्य;
	काष्ठा drm_connector_list_iter iter;
	काष्ठा amdgpu_connector *amdgpu_connector;

	drm_connector_list_iter_begin(dev, &iter);
	drm_क्रम_each_connector_iter(connector, &iter) अणु
		amdgpu_connector = to_amdgpu_connector(connector);
		अगर (amdgpu_encoder->devices & amdgpu_connector->devices) अणु
			found = connector;
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&iter);
	वापस found;
पूर्ण

काष्ठा drm_encoder *amdgpu_get_बाह्यal_encoder(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_encoder *other_encoder;
	काष्ठा amdgpu_encoder *other_amdgpu_encoder;

	अगर (amdgpu_encoder->is_ext_encoder)
		वापस शून्य;

	list_क्रम_each_entry(other_encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (other_encoder == encoder)
			जारी;
		other_amdgpu_encoder = to_amdgpu_encoder(other_encoder);
		अगर (other_amdgpu_encoder->is_ext_encoder &&
		    (amdgpu_encoder->devices & other_amdgpu_encoder->devices))
			वापस other_encoder;
	पूर्ण
	वापस शून्य;
पूर्ण

u16 amdgpu_encoder_get_dp_bridge_encoder_id(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_encoder *other_encoder = amdgpu_get_बाह्यal_encoder(encoder);

	अगर (other_encoder) अणु
		काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(other_encoder);

		चयन (amdgpu_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_TRAVIS:
		हाल ENCODER_OBJECT_ID_NUTMEG:
			वापस amdgpu_encoder->encoder_id;
		शेष:
			वापस ENCODER_OBJECT_ID_NONE;
		पूर्ण
	पूर्ण
	वापस ENCODER_OBJECT_ID_NONE;
पूर्ण

व्योम amdgpu_panel_mode_fixup(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_display_mode *native_mode = &amdgpu_encoder->native_mode;
	अचिन्हित hblank = native_mode->htotal - native_mode->hdisplay;
	अचिन्हित vblank = native_mode->vtotal - native_mode->vdisplay;
	अचिन्हित hover = native_mode->hsync_start - native_mode->hdisplay;
	अचिन्हित vover = native_mode->vsync_start - native_mode->vdisplay;
	अचिन्हित hsync_width = native_mode->hsync_end - native_mode->hsync_start;
	अचिन्हित vsync_width = native_mode->vsync_end - native_mode->vsync_start;

	adjusted_mode->घड़ी = native_mode->घड़ी;
	adjusted_mode->flags = native_mode->flags;

	adjusted_mode->hdisplay = native_mode->hdisplay;
	adjusted_mode->vdisplay = native_mode->vdisplay;

	adjusted_mode->htotal = native_mode->hdisplay + hblank;
	adjusted_mode->hsync_start = native_mode->hdisplay + hover;
	adjusted_mode->hsync_end = adjusted_mode->hsync_start + hsync_width;

	adjusted_mode->vtotal = native_mode->vdisplay + vblank;
	adjusted_mode->vsync_start = native_mode->vdisplay + vover;
	adjusted_mode->vsync_end = adjusted_mode->vsync_start + vsync_width;

	drm_mode_set_crtcinfo(adjusted_mode, CRTC_INTERLACE_HALVE_V);

	adjusted_mode->crtc_hdisplay = native_mode->hdisplay;
	adjusted_mode->crtc_vdisplay = native_mode->vdisplay;

	adjusted_mode->crtc_htotal = adjusted_mode->crtc_hdisplay + hblank;
	adjusted_mode->crtc_hsync_start = adjusted_mode->crtc_hdisplay + hover;
	adjusted_mode->crtc_hsync_end = adjusted_mode->crtc_hsync_start + hsync_width;

	adjusted_mode->crtc_vtotal = adjusted_mode->crtc_vdisplay + vblank;
	adjusted_mode->crtc_vsync_start = adjusted_mode->crtc_vdisplay + vover;
	adjusted_mode->crtc_vsync_end = adjusted_mode->crtc_vsync_start + vsync_width;

पूर्ण

bool amdgpu_dig_monitor_is_duallink(काष्ठा drm_encoder *encoder,
				    u32 pixel_घड़ी)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा amdgpu_connector *amdgpu_connector;
	काष्ठा amdgpu_connector_atom_dig *dig_connector;

	connector = amdgpu_get_connector_क्रम_encoder(encoder);
	/* अगर we करोn't have an active device yet, just use one of
	 * the connectors tied to the encoder.
	 */
	अगर (!connector)
		connector = amdgpu_get_connector_क्रम_encoder_init(encoder);
	amdgpu_connector = to_amdgpu_connector(connector);

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_HDMIB:
		अगर (amdgpu_connector->use_digital) अणु
			/* HDMI 1.3 supports up to 340 Mhz over single link */
			अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
				अगर (pixel_घड़ी > 340000)
					वापस true;
				अन्यथा
					वापस false;
			पूर्ण अन्यथा अणु
				अगर (pixel_घड़ी > 165000)
					वापस true;
				अन्यथा
					वापस false;
			पूर्ण
		पूर्ण अन्यथा
			वापस false;
	हाल DRM_MODE_CONNECTOR_DVID:
	हाल DRM_MODE_CONNECTOR_HDMIA:
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = amdgpu_connector->con_priv;
		अगर ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP))
			वापस false;
		अन्यथा अणु
			/* HDMI 1.3 supports up to 340 Mhz over single link */
			अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector))) अणु
				अगर (pixel_घड़ी > 340000)
					वापस true;
				अन्यथा
					वापस false;
			पूर्ण अन्यथा अणु
				अगर (pixel_घड़ी > 165000)
					वापस true;
				अन्यथा
					वापस false;
			पूर्ण
		पूर्ण
	शेष:
		वापस false;
	पूर्ण
पूर्ण
