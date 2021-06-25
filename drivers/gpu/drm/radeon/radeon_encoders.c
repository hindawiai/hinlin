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

#समावेश <linux/pci.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_atombios.h"
#समावेश "radeon_legacy_encoders.h"
#समावेश "atom.h"

अटल uपूर्णांक32_t radeon_encoder_clones(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_encoder *clone_encoder;
	uपूर्णांक32_t index_mask = 0;
	पूर्णांक count;

	/* DIG routing माला_लो problematic */
	अगर (rdev->family >= CHIP_R600)
		वापस index_mask;
	/* LVDS/TV are too wacky */
	अगर (radeon_encoder->devices & ATOM_DEVICE_LCD_SUPPORT)
		वापस index_mask;
	/* DVO requires 2x ppll घड़ीs depending on पंचांगds chip */
	अगर (radeon_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT)
		वापस index_mask;

	count = -1;
	list_क्रम_each_entry(clone_encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा radeon_encoder *radeon_clone = to_radeon_encoder(clone_encoder);
		count++;

		अगर (clone_encoder == encoder)
			जारी;
		अगर (radeon_clone->devices & (ATOM_DEVICE_LCD_SUPPORT))
			जारी;
		अगर (radeon_clone->devices & ATOM_DEVICE_DFP2_SUPPORT)
			जारी;
		अन्यथा
			index_mask |= (1 << count);
	पूर्ण
	वापस index_mask;
पूर्ण

व्योम radeon_setup_encoder_clones(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_encoder *encoder;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		encoder->possible_clones = radeon_encoder_clones(encoder);
	पूर्ण
पूर्ण

uपूर्णांक32_t
radeon_get_encoder_क्रमागत(काष्ठा drm_device *dev, uपूर्णांक32_t supported_device, uपूर्णांक8_t dac)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t ret = 0;

	चयन (supported_device) अणु
	हाल ATOM_DEVICE_CRT1_SUPPORT:
	हाल ATOM_DEVICE_TV1_SUPPORT:
	हाल ATOM_DEVICE_TV2_SUPPORT:
	हाल ATOM_DEVICE_CRT2_SUPPORT:
	हाल ATOM_DEVICE_CV_SUPPORT:
		चयन (dac) अणु
		हाल 1: /* dac a */
			अगर ((rdev->family == CHIP_RS300) ||
			    (rdev->family == CHIP_RS400) ||
			    (rdev->family == CHIP_RS480))
				ret = ENCODER_INTERNAL_DAC2_ENUM_ID1;
			अन्यथा अगर (ASIC_IS_AVIVO(rdev))
				ret = ENCODER_INTERNAL_KLDSCP_DAC1_ENUM_ID1;
			अन्यथा
				ret = ENCODER_INTERNAL_DAC1_ENUM_ID1;
			अवरोध;
		हाल 2: /* dac b */
			अगर (ASIC_IS_AVIVO(rdev))
				ret = ENCODER_INTERNAL_KLDSCP_DAC2_ENUM_ID1;
			अन्यथा अणु
				/*अगर (rdev->family == CHIP_R200)
				  ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
				  अन्यथा*/
				ret = ENCODER_INTERNAL_DAC2_ENUM_ID1;
			पूर्ण
			अवरोध;
		हाल 3: /* बाह्यal dac */
			अगर (ASIC_IS_AVIVO(rdev))
				ret = ENCODER_INTERNAL_KLDSCP_DVO1_ENUM_ID1;
			अन्यथा
				ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ATOM_DEVICE_LCD1_SUPPORT:
		अगर (ASIC_IS_AVIVO(rdev))
			ret = ENCODER_INTERNAL_LVTM1_ENUM_ID1;
		अन्यथा
			ret = ENCODER_INTERNAL_LVDS_ENUM_ID1;
		अवरोध;
	हाल ATOM_DEVICE_DFP1_SUPPORT:
		अगर ((rdev->family == CHIP_RS300) ||
		    (rdev->family == CHIP_RS400) ||
		    (rdev->family == CHIP_RS480))
			ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
		अन्यथा अगर (ASIC_IS_AVIVO(rdev))
			ret = ENCODER_INTERNAL_KLDSCP_TMDS1_ENUM_ID1;
		अन्यथा
			ret = ENCODER_INTERNAL_TMDS1_ENUM_ID1;
		अवरोध;
	हाल ATOM_DEVICE_LCD2_SUPPORT:
	हाल ATOM_DEVICE_DFP2_SUPPORT:
		अगर ((rdev->family == CHIP_RS600) ||
		    (rdev->family == CHIP_RS690) ||
		    (rdev->family == CHIP_RS740))
			ret = ENCODER_INTERNAL_DDI_ENUM_ID1;
		अन्यथा अगर (ASIC_IS_AVIVO(rdev))
			ret = ENCODER_INTERNAL_KLDSCP_DVO1_ENUM_ID1;
		अन्यथा
			ret = ENCODER_INTERNAL_DVO1_ENUM_ID1;
		अवरोध;
	हाल ATOM_DEVICE_DFP3_SUPPORT:
		ret = ENCODER_INTERNAL_LVTM1_ENUM_ID1;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम radeon_encoder_add_backlight(काष्ठा radeon_encoder *radeon_encoder,
					 काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	bool use_bl = false;

	अगर (!(radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)))
		वापस;

	अगर (radeon_backlight == 0) अणु
		वापस;
	पूर्ण अन्यथा अगर (radeon_backlight == 1) अणु
		use_bl = true;
	पूर्ण अन्यथा अगर (radeon_backlight == -1) अणु
		/* Quirks */
		/* Amilo Xi 2550 only works with acpi bl */
		अगर ((rdev->pdev->device == 0x9583) &&
		    (rdev->pdev->subप्रणाली_venकरोr == 0x1734) &&
		    (rdev->pdev->subप्रणाली_device == 0x1107))
			use_bl = false;
/* Older PPC macs use on-GPU backlight controller */
#अगर_अघोषित CONFIG_PPC_PMAC
		/* disable native backlight control on older asics */
		अन्यथा अगर (rdev->family < CHIP_R600)
			use_bl = false;
#पूर्ण_अगर
		अन्यथा
			use_bl = true;
	पूर्ण

	अगर (use_bl) अणु
		अगर (rdev->is_atom_bios)
			radeon_atom_backlight_init(radeon_encoder, connector);
		अन्यथा
			radeon_legacy_backlight_init(radeon_encoder, connector);
	पूर्ण
पूर्ण

व्योम
radeon_link_encoder_connector(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;

	/* walk the list and link encoders to connectors */
	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		radeon_connector = to_radeon_connector(connector);
		list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
			radeon_encoder = to_radeon_encoder(encoder);
			अगर (radeon_encoder->devices & radeon_connector->devices) अणु
				drm_connector_attach_encoder(connector, encoder);
				अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
					radeon_encoder_add_backlight(radeon_encoder, connector);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम radeon_encoder_set_active_device(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_connector *connector;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		अगर (connector->encoder == encoder) अणु
			काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
			radeon_encoder->active_device = radeon_encoder->devices & radeon_connector->devices;
			DRM_DEBUG_KMS("setting active device to %08x from %08x %08x for encoder %d\n",
				  radeon_encoder->active_device, radeon_encoder->devices,
				  radeon_connector->devices, encoder->encoder_type);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा drm_connector *
radeon_get_connector_क्रम_encoder(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		radeon_connector = to_radeon_connector(connector);
		अगर (radeon_encoder->is_mst_encoder) अणु
			काष्ठा radeon_encoder_mst *mst_enc;

			अगर (!radeon_connector->is_mst_connector)
				जारी;

			mst_enc = radeon_encoder->enc_priv;
			अगर (mst_enc->connector == radeon_connector->mst_port)
				वापस connector;
		पूर्ण अन्यथा अगर (radeon_encoder->active_device & radeon_connector->devices)
			वापस connector;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा drm_connector *
radeon_get_connector_क्रम_encoder_init(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, head) अणु
		radeon_connector = to_radeon_connector(connector);
		अगर (radeon_encoder->devices & radeon_connector->devices)
			वापस connector;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा drm_encoder *radeon_get_बाह्यal_encoder(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_encoder *other_encoder;
	काष्ठा radeon_encoder *other_radeon_encoder;

	अगर (radeon_encoder->is_ext_encoder)
		वापस शून्य;

	list_क्रम_each_entry(other_encoder, &dev->mode_config.encoder_list, head) अणु
		अगर (other_encoder == encoder)
			जारी;
		other_radeon_encoder = to_radeon_encoder(other_encoder);
		अगर (other_radeon_encoder->is_ext_encoder &&
		    (radeon_encoder->devices & other_radeon_encoder->devices))
			वापस other_encoder;
	पूर्ण
	वापस शून्य;
पूर्ण

u16 radeon_encoder_get_dp_bridge_encoder_id(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_encoder *other_encoder = radeon_get_बाह्यal_encoder(encoder);

	अगर (other_encoder) अणु
		काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(other_encoder);

		चयन (radeon_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_TRAVIS:
		हाल ENCODER_OBJECT_ID_NUTMEG:
			वापस radeon_encoder->encoder_id;
		शेष:
			वापस ENCODER_OBJECT_ID_NONE;
		पूर्ण
	पूर्ण
	वापस ENCODER_OBJECT_ID_NONE;
पूर्ण

व्योम radeon_panel_mode_fixup(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_display_mode *native_mode = &radeon_encoder->native_mode;
	अचिन्हित hblank = native_mode->htotal - native_mode->hdisplay;
	अचिन्हित vblank = native_mode->vtotal - native_mode->vdisplay;
	अचिन्हित hover = native_mode->hsync_start - native_mode->hdisplay;
	अचिन्हित vover = native_mode->vsync_start - native_mode->vdisplay;
	अचिन्हित hsync_width = native_mode->hsync_end - native_mode->hsync_start;
	अचिन्हित vsync_width = native_mode->vsync_end - native_mode->vsync_start;

	adjusted_mode->घड़ी = native_mode->घड़ी;
	adjusted_mode->flags = native_mode->flags;

	अगर (ASIC_IS_AVIVO(rdev)) अणु
		adjusted_mode->hdisplay = native_mode->hdisplay;
		adjusted_mode->vdisplay = native_mode->vdisplay;
	पूर्ण

	adjusted_mode->htotal = native_mode->hdisplay + hblank;
	adjusted_mode->hsync_start = native_mode->hdisplay + hover;
	adjusted_mode->hsync_end = adjusted_mode->hsync_start + hsync_width;

	adjusted_mode->vtotal = native_mode->vdisplay + vblank;
	adjusted_mode->vsync_start = native_mode->vdisplay + vover;
	adjusted_mode->vsync_end = adjusted_mode->vsync_start + vsync_width;

	drm_mode_set_crtcinfo(adjusted_mode, CRTC_INTERLACE_HALVE_V);

	अगर (ASIC_IS_AVIVO(rdev)) अणु
		adjusted_mode->crtc_hdisplay = native_mode->hdisplay;
		adjusted_mode->crtc_vdisplay = native_mode->vdisplay;
	पूर्ण

	adjusted_mode->crtc_htotal = adjusted_mode->crtc_hdisplay + hblank;
	adjusted_mode->crtc_hsync_start = adjusted_mode->crtc_hdisplay + hover;
	adjusted_mode->crtc_hsync_end = adjusted_mode->crtc_hsync_start + hsync_width;

	adjusted_mode->crtc_vtotal = adjusted_mode->crtc_vdisplay + vblank;
	adjusted_mode->crtc_vsync_start = adjusted_mode->crtc_vdisplay + vover;
	adjusted_mode->crtc_vsync_end = adjusted_mode->crtc_vsync_start + vsync_width;

पूर्ण

bool radeon_dig_monitor_is_duallink(काष्ठा drm_encoder *encoder,
				    u32 pixel_घड़ी)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा radeon_connector_atom_dig *dig_connector;

	connector = radeon_get_connector_क्रम_encoder(encoder);
	/* अगर we करोn't have an active device yet, just use one of
	 * the connectors tied to the encoder.
	 */
	अगर (!connector)
		connector = radeon_get_connector_क्रम_encoder_init(encoder);
	radeon_connector = to_radeon_connector(connector);

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_HDMIB:
		अगर (radeon_connector->use_digital) अणु
			/* HDMI 1.3 supports up to 340 Mhz over single link */
			अगर (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
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
		अगर (radeon_connector->is_mst_connector)
			वापस false;

		dig_connector = radeon_connector->con_priv;
		अगर ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP))
			वापस false;
		अन्यथा अणु
			/* HDMI 1.3 supports up to 340 Mhz over single link */
			अगर (ASIC_IS_DCE6(rdev) && drm_detect_hdmi_monitor(radeon_connector_edid(connector))) अणु
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

bool radeon_encoder_is_digital(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
