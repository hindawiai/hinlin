<शैली गुरु>
/*
 * Copyright 2007-11 Advanced Micro Devices, Inc.
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
#समावेश <drm/amdgpu_drm.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_connectors.h"
#समावेश "amdgpu_display.h"
#समावेश "atom.h"
#समावेश "atombios_encoders.h"
#समावेश "atombios_dp.h"
#समावेश <linux/backlight.h>
#समावेश "bif/bif_4_1_d.h"

u8
amdgpu_atombios_encoder_get_backlight_level_from_reg(काष्ठा amdgpu_device *adev)
अणु
	u8 backlight_level;
	u32 bios_2_scratch;

	bios_2_scratch = RREG32(mmBIOS_SCRATCH_2);

	backlight_level = ((bios_2_scratch & ATOM_S2_CURRENT_BL_LEVEL_MASK) >>
			   ATOM_S2_CURRENT_BL_LEVEL_SHIFT);

	वापस backlight_level;
पूर्ण

व्योम
amdgpu_atombios_encoder_set_backlight_level_to_reg(काष्ठा amdgpu_device *adev,
					    u8 backlight_level)
अणु
	u32 bios_2_scratch;

	bios_2_scratch = RREG32(mmBIOS_SCRATCH_2);

	bios_2_scratch &= ~ATOM_S2_CURRENT_BL_LEVEL_MASK;
	bios_2_scratch |= ((backlight_level << ATOM_S2_CURRENT_BL_LEVEL_SHIFT) &
			   ATOM_S2_CURRENT_BL_LEVEL_MASK);

	WREG32(mmBIOS_SCRATCH_2, bios_2_scratch);
पूर्ण

u8
amdgpu_atombios_encoder_get_backlight_level(काष्ठा amdgpu_encoder *amdgpu_encoder)
अणु
	काष्ठा drm_device *dev = amdgpu_encoder->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	अगर (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस 0;

	वापस amdgpu_atombios_encoder_get_backlight_level_from_reg(adev);
पूर्ण

व्योम
amdgpu_atombios_encoder_set_backlight_level(काष्ठा amdgpu_encoder *amdgpu_encoder,
				     u8 level)
अणु
	काष्ठा drm_encoder *encoder = &amdgpu_encoder->base;
	काष्ठा drm_device *dev = amdgpu_encoder->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder_atom_dig *dig;

	अगर (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस;

	अगर ((amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
	    amdgpu_encoder->enc_priv) अणु
		dig = amdgpu_encoder->enc_priv;
		dig->backlight_level = level;
		amdgpu_atombios_encoder_set_backlight_level_to_reg(adev, dig->backlight_level);

		चयन (amdgpu_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			अगर (dig->backlight_level == 0)
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);
			अन्यथा अणु
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL, 0, 0);
				amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
								       ATOM_TRANSMITTER_ACTION_LCD_BLON, 0, 0);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

अटल u8 amdgpu_atombios_encoder_backlight_level(काष्ठा backlight_device *bd)
अणु
	u8 level;

	/* Convert brightness to hardware level */
	अगर (bd->props.brightness < 0)
		level = 0;
	अन्यथा अगर (bd->props.brightness > AMDGPU_MAX_BL_LEVEL)
		level = AMDGPU_MAX_BL_LEVEL;
	अन्यथा
		level = bd->props.brightness;

	वापस level;
पूर्ण

अटल पूर्णांक amdgpu_atombios_encoder_update_backlight_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा amdgpu_backlight_privdata *pdata = bl_get_data(bd);
	काष्ठा amdgpu_encoder *amdgpu_encoder = pdata->encoder;

	amdgpu_atombios_encoder_set_backlight_level(amdgpu_encoder,
					     amdgpu_atombios_encoder_backlight_level(bd));

	वापस 0;
पूर्ण

अटल पूर्णांक
amdgpu_atombios_encoder_get_backlight_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा amdgpu_backlight_privdata *pdata = bl_get_data(bd);
	काष्ठा amdgpu_encoder *amdgpu_encoder = pdata->encoder;
	काष्ठा drm_device *dev = amdgpu_encoder->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);

	वापस amdgpu_atombios_encoder_get_backlight_level_from_reg(adev);
पूर्ण

अटल स्थिर काष्ठा backlight_ops amdgpu_atombios_encoder_backlight_ops = अणु
	.get_brightness = amdgpu_atombios_encoder_get_backlight_brightness,
	.update_status	= amdgpu_atombios_encoder_update_backlight_status,
पूर्ण;

व्योम amdgpu_atombios_encoder_init_backlight(काष्ठा amdgpu_encoder *amdgpu_encoder,
				     काष्ठा drm_connector *drm_connector)
अणु
	काष्ठा drm_device *dev = amdgpu_encoder->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;
	काष्ठा amdgpu_backlight_privdata *pdata;
	काष्ठा amdgpu_encoder_atom_dig *dig;
	अक्षर bl_name[16];

	/* Mac laptops with multiple GPUs use the gmux driver क्रम backlight
	 * so करोn't रेजिस्टर a backlight device
	 */
	अगर ((adev->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_APPLE) &&
	    (adev->pdev->device == 0x6741))
		वापस;

	अगर (!amdgpu_encoder->enc_priv)
		वापस;

	अगर (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस;

	pdata = kदो_स्मृति(माप(काष्ठा amdgpu_backlight_privdata), GFP_KERNEL);
	अगर (!pdata) अणु
		DRM_ERROR("Memory allocation failed\n");
		जाओ error;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.max_brightness = AMDGPU_MAX_BL_LEVEL;
	props.type = BACKLIGHT_RAW;
	snम_लिखो(bl_name, माप(bl_name),
		 "amdgpu_bl%d", dev->primary->index);
	bd = backlight_device_रेजिस्टर(bl_name, drm_connector->kdev,
				       pdata, &amdgpu_atombios_encoder_backlight_ops, &props);
	अगर (IS_ERR(bd)) अणु
		DRM_ERROR("Backlight registration failed\n");
		जाओ error;
	पूर्ण

	pdata->encoder = amdgpu_encoder;

	dig = amdgpu_encoder->enc_priv;
	dig->bl_dev = bd;

	bd->props.brightness = amdgpu_atombios_encoder_get_backlight_brightness(bd);
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	DRM_INFO("amdgpu atom DIG backlight initialized\n");

	वापस;

error:
	kमुक्त(pdata);
	वापस;
पूर्ण

व्योम
amdgpu_atombios_encoder_fini_backlight(काष्ठा amdgpu_encoder *amdgpu_encoder)
अणु
	काष्ठा drm_device *dev = amdgpu_encoder->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा backlight_device *bd = शून्य;
	काष्ठा amdgpu_encoder_atom_dig *dig;

	अगर (!amdgpu_encoder->enc_priv)
		वापस;

	अगर (!(adev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस;

	dig = amdgpu_encoder->enc_priv;
	bd = dig->bl_dev;
	dig->bl_dev = शून्य;

	अगर (bd) अणु
		काष्ठा amdgpu_legacy_backlight_privdata *pdata;

		pdata = bl_get_data(bd);
		backlight_device_unरेजिस्टर(bd);
		kमुक्त(pdata);

		DRM_INFO("amdgpu atom LVDS backlight unloaded\n");
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_BACKLIGHT_CLASS_DEVICE */

व्योम amdgpu_atombios_encoder_init_backlight(काष्ठा amdgpu_encoder *encoder)
अणु
पूर्ण

व्योम amdgpu_atombios_encoder_fini_backlight(काष्ठा amdgpu_encoder *encoder)
अणु
पूर्ण

#पूर्ण_अगर

bool amdgpu_atombios_encoder_is_digital(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	चयन (amdgpu_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

bool amdgpu_atombios_encoder_mode_fixup(काष्ठा drm_encoder *encoder,
				 स्थिर काष्ठा drm_display_mode *mode,
				 काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);

	/* set the active encoder to connector routing */
	amdgpu_encoder_set_active_device(encoder);
	drm_mode_set_crtcinfo(adjusted_mode, 0);

	/* hw bug */
	अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE)
	    && (mode->crtc_vsync_start < (mode->crtc_vdisplay + 2)))
		adjusted_mode->crtc_vsync_start = adjusted_mode->crtc_vdisplay + 2;

	/* vertical FP must be at least 1 */
	अगर (mode->crtc_vsync_start == mode->crtc_vdisplay)
		adjusted_mode->crtc_vsync_start++;

	/* get the native mode क्रम scaling */
	अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_LCD_SUPPORT))
		amdgpu_panel_mode_fixup(encoder, adjusted_mode);
	अन्यथा अगर (amdgpu_encoder->rmx_type != RMX_OFF)
		amdgpu_panel_mode_fixup(encoder, adjusted_mode);

	अगर ((amdgpu_encoder->active_device & (ATOM_DEVICE_DFP_SUPPORT | ATOM_DEVICE_LCD_SUPPORT)) ||
	    (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)) अणु
		काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);
		amdgpu_atombios_dp_set_link_config(connector, adjusted_mode);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
amdgpu_atombios_encoder_setup_dac(काष्ठा drm_encoder *encoder, पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	DAC_ENCODER_CONTROL_PS_ALLOCATION args;
	पूर्णांक index = 0;

	स_रखो(&args, 0, माप(args));

	चयन (amdgpu_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		index = GetIndexIntoMasterTable(COMMAND, DAC1EncoderControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		index = GetIndexIntoMasterTable(COMMAND, DAC2EncoderControl);
		अवरोध;
	पूर्ण

	args.ucAction = action;
	args.ucDacStandard = ATOM_DAC1_PS2;
	args.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

पूर्ण

अटल u8 amdgpu_atombios_encoder_get_bpc(काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक bpc = 8;

	अगर (encoder->crtc) अणु
		काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
		bpc = amdgpu_crtc->bpc;
	पूर्ण

	चयन (bpc) अणु
	हाल 0:
		वापस PANEL_BPC_UNDEFINE;
	हाल 6:
		वापस PANEL_6BIT_PER_COLOR;
	हाल 8:
	शेष:
		वापस PANEL_8BIT_PER_COLOR;
	हाल 10:
		वापस PANEL_10BIT_PER_COLOR;
	हाल 12:
		वापस PANEL_12BIT_PER_COLOR;
	हाल 16:
		वापस PANEL_16BIT_PER_COLOR;
	पूर्ण
पूर्ण

जोड़ dvo_encoder_control अणु
	ENABLE_EXTERNAL_TMDS_ENCODER_PS_ALLOCATION ext_पंचांगds;
	DVO_ENCODER_CONTROL_PS_ALLOCATION dvo;
	DVO_ENCODER_CONTROL_PS_ALLOCATION_V3 dvo_v3;
	DVO_ENCODER_CONTROL_PS_ALLOCATION_V1_4 dvo_v4;
पूर्ण;

अटल व्योम
amdgpu_atombios_encoder_setup_dvo(काष्ठा drm_encoder *encoder, पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	जोड़ dvo_encoder_control args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DVOEncoderControl);
	uपूर्णांक8_t frev, crev;

	स_रखो(&args, 0, माप(args));

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
			/* R4xx, R5xx */
			args.ext_पंचांगds.sXTmdsEncoder.ucEnable = action;

			अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.ext_पंचांगds.sXTmdsEncoder.ucMisc |= PANEL_ENCODER_MISC_DUAL;

			args.ext_पंचांगds.sXTmdsEncoder.ucMisc |= ATOM_PANEL_MISC_888RGB;
			अवरोध;
		हाल 2:
			/* RS600/690/740 */
			args.dvo.sDVOEncoder.ucAction = action;
			args.dvo.sDVOEncoder.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			/* DFP1, CRT1, TV1 depending on the type of port */
			args.dvo.sDVOEncoder.ucDeviceType = ATOM_DEVICE_DFP1_INDEX;

			अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.dvo.sDVOEncoder.usDevAttr.sDigAttrib.ucAttribute |= PANEL_ENCODER_MISC_DUAL;
			अवरोध;
		हाल 3:
			/* R6xx */
			args.dvo_v3.ucAction = action;
			args.dvo_v3.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			args.dvo_v3.ucDVOConfig = 0; /* XXX */
			अवरोध;
		हाल 4:
			/* DCE8 */
			args.dvo_v4.ucAction = action;
			args.dvo_v4.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			args.dvo_v4.ucDVOConfig = 0; /* XXX */
			args.dvo_v4.ucBitPerColor = amdgpu_atombios_encoder_get_bpc(encoder);
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		अवरोध;
	पूर्ण

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

पूर्णांक amdgpu_atombios_encoder_get_encoder_mode(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_connector *connector;
	काष्ठा amdgpu_connector *amdgpu_connector;
	काष्ठा amdgpu_connector_atom_dig *dig_connector;

	/* dp bridges are always DP */
	अगर (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)
		वापस ATOM_ENCODER_MODE_DP;

	/* DVO is always DVO */
	अगर ((amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DVO1) ||
	    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1))
		वापस ATOM_ENCODER_MODE_DVO;

	connector = amdgpu_get_connector_क्रम_encoder(encoder);
	/* अगर we करोn't have an active device yet, just use one of
	 * the connectors tied to the encoder.
	 */
	अगर (!connector)
		connector = amdgpu_get_connector_क्रम_encoder_init(encoder);
	amdgpu_connector = to_amdgpu_connector(connector);

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_HDMIB: /* HDMI-B is basically DL-DVI; analog works fine */
		अगर (amdgpu_audio != 0) अणु
			अगर (amdgpu_connector->use_digital &&
			    (amdgpu_connector->audio == AMDGPU_AUDIO_ENABLE))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector)) &&
				 (amdgpu_connector->audio == AMDGPU_AUDIO_AUTO))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (amdgpu_connector->use_digital)
				वापस ATOM_ENCODER_MODE_DVI;
			अन्यथा
				वापस ATOM_ENCODER_MODE_CRT;
		पूर्ण अन्यथा अगर (amdgpu_connector->use_digital) अणु
			वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण अन्यथा अणु
			वापस ATOM_ENCODER_MODE_CRT;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVID:
	हाल DRM_MODE_CONNECTOR_HDMIA:
	शेष:
		अगर (amdgpu_audio != 0) अणु
			अगर (amdgpu_connector->audio == AMDGPU_AUDIO_ENABLE)
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector)) &&
				 (amdgpu_connector->audio == AMDGPU_AUDIO_AUTO))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा
				वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण अन्यथा अणु
			वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण
	हाल DRM_MODE_CONNECTOR_LVDS:
		वापस ATOM_ENCODER_MODE_LVDS;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = amdgpu_connector->con_priv;
		अगर ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) अणु
			वापस ATOM_ENCODER_MODE_DP;
		पूर्ण अन्यथा अगर (amdgpu_audio != 0) अणु
			अगर (amdgpu_connector->audio == AMDGPU_AUDIO_ENABLE)
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (drm_detect_hdmi_monitor(amdgpu_connector_edid(connector)) &&
				 (amdgpu_connector->audio == AMDGPU_AUDIO_AUTO))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा
				वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण अन्यथा अणु
			वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण
	हाल DRM_MODE_CONNECTOR_eDP:
		वापस ATOM_ENCODER_MODE_DP;
	हाल DRM_MODE_CONNECTOR_DVIA:
	हाल DRM_MODE_CONNECTOR_VGA:
		वापस ATOM_ENCODER_MODE_CRT;
	हाल DRM_MODE_CONNECTOR_Composite:
	हाल DRM_MODE_CONNECTOR_SVIDEO:
	हाल DRM_MODE_CONNECTOR_9PinDIN:
		/* fix me */
		वापस ATOM_ENCODER_MODE_TV;
	पूर्ण
पूर्ण

/*
 * DIG Encoder/Transmitter Setup
 *
 * DCE 6.0
 * - 3 DIG transmitter blocks UNIPHY0/1/2 (links A and B).
 * Supports up to 6 digital outमाला_दो
 * - 6 DIG encoder blocks.
 * - DIG to PHY mapping is hardcoded
 * DIG1 drives UNIPHY0 link A, A+B
 * DIG2 drives UNIPHY0 link B
 * DIG3 drives UNIPHY1 link A, A+B
 * DIG4 drives UNIPHY1 link B
 * DIG5 drives UNIPHY2 link A, A+B
 * DIG6 drives UNIPHY2 link B
 *
 * Routing
 * crtc -> dig encoder -> UNIPHY/LVTMA (1 or 2 links)
 * Examples:
 * crtc0 -> dig2 -> LVTMA   links A+B -> TMDS/HDMI
 * crtc1 -> dig1 -> UNIPHY0 link  B   -> DP
 * crtc0 -> dig1 -> UNIPHY2 link  A   -> LVDS
 * crtc1 -> dig2 -> UNIPHY1 link  B+A -> TMDS/HDMI
 */

जोड़ dig_encoder_control अणु
	DIG_ENCODER_CONTROL_PS_ALLOCATION v1;
	DIG_ENCODER_CONTROL_PARAMETERS_V2 v2;
	DIG_ENCODER_CONTROL_PARAMETERS_V3 v3;
	DIG_ENCODER_CONTROL_PARAMETERS_V4 v4;
	DIG_ENCODER_CONTROL_PARAMETERS_V5 v5;
पूर्ण;

व्योम
amdgpu_atombios_encoder_setup_dig_encoder(काष्ठा drm_encoder *encoder,
				   पूर्णांक action, पूर्णांक panel_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);
	जोड़ dig_encoder_control args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DIGxEncoderControl);
	uपूर्णांक8_t frev, crev;
	पूर्णांक dp_घड़ी = 0;
	पूर्णांक dp_lane_count = 0;
	पूर्णांक hpd_id = AMDGPU_HPD_NONE;

	अगर (connector) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		काष्ठा amdgpu_connector_atom_dig *dig_connector =
			amdgpu_connector->con_priv;

		dp_घड़ी = dig_connector->dp_घड़ी;
		dp_lane_count = dig_connector->dp_lane_count;
		hpd_id = amdgpu_connector->hpd.hpd;
	पूर्ण

	/* no dig encoder asचिन्हित */
	अगर (dig->dig_encoder == -1)
		वापस;

	स_रखो(&args, 0, माप(args));

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
			args.v1.ucAction = action;
			args.v1.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			अगर (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			अन्यथा
				args.v1.ucEncoderMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode))
				args.v1.ucLaneNum = dp_lane_count;
			अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v1.ucLaneNum = 8;
			अन्यथा
				args.v1.ucLaneNum = 4;

			अगर (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode) && (dp_घड़ी == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ;
			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v1.ucConfig = ATOM_ENCODER_CONFIG_V2_TRANSMITTER1;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
				args.v1.ucConfig = ATOM_ENCODER_CONFIG_V2_TRANSMITTER2;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v1.ucConfig = ATOM_ENCODER_CONFIG_V2_TRANSMITTER3;
				अवरोध;
			पूर्ण
			अगर (dig->linkb)
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_LINKB;
			अन्यथा
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_LINKA;
			अवरोध;
		हाल 2:
		हाल 3:
			args.v3.ucAction = action;
			args.v3.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			अगर (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			अन्यथा
				args.v3.ucEncoderMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode))
				args.v3.ucLaneNum = dp_lane_count;
			अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v3.ucLaneNum = 8;
			अन्यथा
				args.v3.ucLaneNum = 4;

			अगर (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode) && (dp_घड़ी == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ;
			args.v3.acConfig.ucDigSel = dig->dig_encoder;
			args.v3.ucBitPerColor = amdgpu_atombios_encoder_get_bpc(encoder);
			अवरोध;
		हाल 4:
			args.v4.ucAction = action;
			args.v4.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			अगर (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v4.ucPanelMode = panel_mode;
			अन्यथा
				args.v4.ucEncoderMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v4.ucEncoderMode))
				args.v4.ucLaneNum = dp_lane_count;
			अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v4.ucLaneNum = 8;
			अन्यथा
				args.v4.ucLaneNum = 4;

			अगर (ENCODER_MODE_IS_DP(args.v4.ucEncoderMode)) अणु
				अगर (dp_घड़ी == 540000)
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_5_40GHZ;
				अन्यथा अगर (dp_घड़ी == 324000)
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_3_24GHZ;
				अन्यथा अगर (dp_घड़ी == 270000)
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_2_70GHZ;
				अन्यथा
					args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V4_DPLINKRATE_1_62GHZ;
			पूर्ण
			args.v4.acConfig.ucDigSel = dig->dig_encoder;
			args.v4.ucBitPerColor = amdgpu_atombios_encoder_get_bpc(encoder);
			अगर (hpd_id == AMDGPU_HPD_NONE)
				args.v4.ucHPD_ID = 0;
			अन्यथा
				args.v4.ucHPD_ID = hpd_id + 1;
			अवरोध;
		हाल 5:
			चयन (action) अणु
			हाल ATOM_ENCODER_CMD_SETUP_PANEL_MODE:
				args.v5.asDPPanelModeParam.ucAction = action;
				args.v5.asDPPanelModeParam.ucPanelMode = panel_mode;
				args.v5.asDPPanelModeParam.ucDigId = dig->dig_encoder;
				अवरोध;
			हाल ATOM_ENCODER_CMD_STREAM_SETUP:
				args.v5.asStreamParam.ucAction = action;
				args.v5.asStreamParam.ucDigId = dig->dig_encoder;
				args.v5.asStreamParam.ucDigMode =
					amdgpu_atombios_encoder_get_encoder_mode(encoder);
				अगर (ENCODER_MODE_IS_DP(args.v5.asStreamParam.ucDigMode))
					args.v5.asStreamParam.ucLaneNum = dp_lane_count;
				अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder,
									amdgpu_encoder->pixel_घड़ी))
					args.v5.asStreamParam.ucLaneNum = 8;
				अन्यथा
					args.v5.asStreamParam.ucLaneNum = 4;
				args.v5.asStreamParam.ulPixelClock =
					cpu_to_le32(amdgpu_encoder->pixel_घड़ी / 10);
				args.v5.asStreamParam.ucBitPerColor =
					amdgpu_atombios_encoder_get_bpc(encoder);
				args.v5.asStreamParam.ucLinkRateIn270Mhz = dp_घड़ी / 27000;
				अवरोध;
			हाल ATOM_ENCODER_CMD_DP_LINK_TRAINING_START:
			हाल ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1:
			हाल ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2:
			हाल ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3:
			हाल ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN4:
			हाल ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE:
			हाल ATOM_ENCODER_CMD_DP_VIDEO_OFF:
			हाल ATOM_ENCODER_CMD_DP_VIDEO_ON:
				args.v5.asCmdParam.ucAction = action;
				args.v5.asCmdParam.ucDigId = dig->dig_encoder;
				अवरोध;
			शेष:
				DRM_ERROR("Unsupported action 0x%x\n", action);
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		अवरोध;
	पूर्ण

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

पूर्ण

जोड़ dig_transmitter_control अणु
	DIG_TRANSMITTER_CONTROL_PS_ALLOCATION v1;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V2 v2;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V3 v3;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V4 v4;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_5 v5;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_6 v6;
पूर्ण;

व्योम
amdgpu_atombios_encoder_setup_dig_transmitter(काष्ठा drm_encoder *encoder, पूर्णांक action,
					      uपूर्णांक8_t lane_num, uपूर्णांक8_t lane_set)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	काष्ठा drm_connector *connector;
	जोड़ dig_transmitter_control args;
	पूर्णांक index = 0;
	uपूर्णांक8_t frev, crev;
	bool is_dp = false;
	पूर्णांक pll_id = 0;
	पूर्णांक dp_घड़ी = 0;
	पूर्णांक dp_lane_count = 0;
	पूर्णांक connector_object_id = 0;
	पूर्णांक igp_lane_info = 0;
	पूर्णांक dig_encoder = dig->dig_encoder;
	पूर्णांक hpd_id = AMDGPU_HPD_NONE;

	अगर (action == ATOM_TRANSMITTER_ACTION_INIT) अणु
		connector = amdgpu_get_connector_क्रम_encoder_init(encoder);
		/* just needed to aव्योम bailing in the encoder check.  the encoder
		 * isn't used क्रम init
		 */
		dig_encoder = 0;
	पूर्ण अन्यथा
		connector = amdgpu_get_connector_क्रम_encoder(encoder);

	अगर (connector) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		काष्ठा amdgpu_connector_atom_dig *dig_connector =
			amdgpu_connector->con_priv;

		hpd_id = amdgpu_connector->hpd.hpd;
		dp_घड़ी = dig_connector->dp_घड़ी;
		dp_lane_count = dig_connector->dp_lane_count;
		connector_object_id =
			(amdgpu_connector->connector_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	पूर्ण

	अगर (encoder->crtc) अणु
		काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
		pll_id = amdgpu_crtc->pll_id;
	पूर्ण

	/* no dig encoder asचिन्हित */
	अगर (dig_encoder == -1)
		वापस;

	अगर (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)))
		is_dp = true;

	स_रखो(&args, 0, माप(args));

	चयन (amdgpu_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		index = GetIndexIntoMasterTable(COMMAND, DVOOutputControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		index = GetIndexIntoMasterTable(COMMAND, UNIPHYTransmitterControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		index = GetIndexIntoMasterTable(COMMAND, LVTMATransmitterControl);
		अवरोध;
	पूर्ण

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
			args.v1.ucAction = action;
			अगर (action == ATOM_TRANSMITTER_ACTION_INIT) अणु
				args.v1.usInitInfo = cpu_to_le16(connector_object_id);
			पूर्ण अन्यथा अगर (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) अणु
				args.v1.asMode.ucLaneSel = lane_num;
				args.v1.asMode.ucLaneSet = lane_set;
			पूर्ण अन्यथा अणु
				अगर (is_dp)
					args.v1.usPixelClock = cpu_to_le16(dp_घड़ी / 10);
				अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v1.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v1.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			पूर्ण

			args.v1.ucConfig = ATOM_TRANSMITTER_CONFIG_CLKSRC_PPLL;

			अगर (dig_encoder)
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_DIG2_ENCODER;
			अन्यथा
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_DIG1_ENCODER;

			अगर ((adev->flags & AMD_IS_APU) &&
			    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_UNIPHY)) अणु
				अगर (is_dp ||
				    !amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी)) अणु
					अगर (igp_lane_info & 0x1)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_0_3;
					अन्यथा अगर (igp_lane_info & 0x2)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_4_7;
					अन्यथा अगर (igp_lane_info & 0x4)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_8_11;
					अन्यथा अगर (igp_lane_info & 0x8)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_12_15;
				पूर्ण अन्यथा अणु
					अगर (igp_lane_info & 0x3)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_0_7;
					अन्यथा अगर (igp_lane_info & 0xc)
						args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LANE_8_15;
				पूर्ण
			पूर्ण

			अगर (dig->linkb)
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LINKB;
			अन्यथा
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_LINKA;

			अगर (is_dp)
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_COHERENT;
			अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_COHERENT;
				अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_8LANE_LINK;
			पूर्ण
			अवरोध;
		हाल 2:
			args.v2.ucAction = action;
			अगर (action == ATOM_TRANSMITTER_ACTION_INIT) अणु
				args.v2.usInitInfo = cpu_to_le16(connector_object_id);
			पूर्ण अन्यथा अगर (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) अणु
				args.v2.asMode.ucLaneSel = lane_num;
				args.v2.asMode.ucLaneSet = lane_set;
			पूर्ण अन्यथा अणु
				अगर (is_dp)
					args.v2.usPixelClock = cpu_to_le16(dp_घड़ी / 10);
				अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v2.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v2.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			पूर्ण

			args.v2.acConfig.ucEncoderSel = dig_encoder;
			अगर (dig->linkb)
				args.v2.acConfig.ucLinkSel = 1;

			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v2.acConfig.ucTransmitterSel = 0;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				args.v2.acConfig.ucTransmitterSel = 1;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v2.acConfig.ucTransmitterSel = 2;
				अवरोध;
			पूर्ण

			अगर (is_dp) अणु
				args.v2.acConfig.fCoherentMode = 1;
				args.v2.acConfig.fDPConnector = 1;
			पूर्ण अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v2.acConfig.fCoherentMode = 1;
				अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v2.acConfig.fDualLinkConnector = 1;
			पूर्ण
			अवरोध;
		हाल 3:
			args.v3.ucAction = action;
			अगर (action == ATOM_TRANSMITTER_ACTION_INIT) अणु
				args.v3.usInitInfo = cpu_to_le16(connector_object_id);
			पूर्ण अन्यथा अगर (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) अणु
				args.v3.asMode.ucLaneSel = lane_num;
				args.v3.asMode.ucLaneSet = lane_set;
			पूर्ण अन्यथा अणु
				अगर (is_dp)
					args.v3.usPixelClock = cpu_to_le16(dp_घड़ी / 10);
				अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v3.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v3.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			पूर्ण

			अगर (is_dp)
				args.v3.ucLaneNum = dp_lane_count;
			अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v3.ucLaneNum = 8;
			अन्यथा
				args.v3.ucLaneNum = 4;

			अगर (dig->linkb)
				args.v3.acConfig.ucLinkSel = 1;
			अगर (dig_encoder & 1)
				args.v3.acConfig.ucEncoderSel = 1;

			/* Select the PLL क्रम the PHY
			 * DP PHY should be घड़ीed from बाह्यal src अगर there is
			 * one.
			 */
			/* On DCE4, अगर there is an बाह्यal घड़ी, it generates the DP ref घड़ी */
			अगर (is_dp && adev->घड़ी.dp_extclk)
				args.v3.acConfig.ucRefClkSource = 2; /* बाह्यal src */
			अन्यथा
				args.v3.acConfig.ucRefClkSource = pll_id;

			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v3.acConfig.ucTransmitterSel = 0;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				args.v3.acConfig.ucTransmitterSel = 1;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v3.acConfig.ucTransmitterSel = 2;
				अवरोध;
			पूर्ण

			अगर (is_dp)
				args.v3.acConfig.fCoherentMode = 1; /* DP requires coherent */
			अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v3.acConfig.fCoherentMode = 1;
				अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v3.acConfig.fDualLinkConnector = 1;
			पूर्ण
			अवरोध;
		हाल 4:
			args.v4.ucAction = action;
			अगर (action == ATOM_TRANSMITTER_ACTION_INIT) अणु
				args.v4.usInitInfo = cpu_to_le16(connector_object_id);
			पूर्ण अन्यथा अगर (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH) अणु
				args.v4.asMode.ucLaneSel = lane_num;
				args.v4.asMode.ucLaneSet = lane_set;
			पूर्ण अन्यथा अणु
				अगर (is_dp)
					args.v4.usPixelClock = cpu_to_le16(dp_घड़ी / 10);
				अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v4.usPixelClock = cpu_to_le16((amdgpu_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v4.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			पूर्ण

			अगर (is_dp)
				args.v4.ucLaneNum = dp_lane_count;
			अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v4.ucLaneNum = 8;
			अन्यथा
				args.v4.ucLaneNum = 4;

			अगर (dig->linkb)
				args.v4.acConfig.ucLinkSel = 1;
			अगर (dig_encoder & 1)
				args.v4.acConfig.ucEncoderSel = 1;

			/* Select the PLL क्रम the PHY
			 * DP PHY should be घड़ीed from बाह्यal src अगर there is
			 * one.
			 */
			/* On DCE5 DCPLL usually generates the DP ref घड़ी */
			अगर (is_dp) अणु
				अगर (adev->घड़ी.dp_extclk)
					args.v4.acConfig.ucRefClkSource = ENCODER_REFCLK_SRC_EXTCLK;
				अन्यथा
					args.v4.acConfig.ucRefClkSource = ENCODER_REFCLK_SRC_DCPLL;
			पूर्ण अन्यथा
				args.v4.acConfig.ucRefClkSource = pll_id;

			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				args.v4.acConfig.ucTransmitterSel = 0;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				args.v4.acConfig.ucTransmitterSel = 1;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				args.v4.acConfig.ucTransmitterSel = 2;
				अवरोध;
			पूर्ण

			अगर (is_dp)
				args.v4.acConfig.fCoherentMode = 1; /* DP requires coherent */
			अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v4.acConfig.fCoherentMode = 1;
				अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
					args.v4.acConfig.fDualLinkConnector = 1;
			पूर्ण
			अवरोध;
		हाल 5:
			args.v5.ucAction = action;
			अगर (is_dp)
				args.v5.usSymClock = cpu_to_le16(dp_घड़ी / 10);
			अन्यथा
				args.v5.usSymClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);

			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				अगर (dig->linkb)
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYB;
				अन्यथा
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYA;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				अगर (dig->linkb)
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYD;
				अन्यथा
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYC;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				अगर (dig->linkb)
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYF;
				अन्यथा
					args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYE;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
				args.v5.ucPhyId = ATOM_PHY_ID_UNIPHYG;
				अवरोध;
			पूर्ण
			अगर (is_dp)
				args.v5.ucLaneNum = dp_lane_count;
			अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v5.ucLaneNum = 8;
			अन्यथा
				args.v5.ucLaneNum = 4;
			args.v5.ucConnObjId = connector_object_id;
			args.v5.ucDigMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			अगर (is_dp && adev->घड़ी.dp_extclk)
				args.v5.asConfig.ucPhyClkSrcId = ENCODER_REFCLK_SRC_EXTCLK;
			अन्यथा
				args.v5.asConfig.ucPhyClkSrcId = pll_id;

			अगर (is_dp)
				args.v5.asConfig.ucCoherentMode = 1; /* DP requires coherent */
			अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v5.asConfig.ucCoherentMode = 1;
			पूर्ण
			अगर (hpd_id == AMDGPU_HPD_NONE)
				args.v5.asConfig.ucHPDSel = 0;
			अन्यथा
				args.v5.asConfig.ucHPDSel = hpd_id + 1;
			args.v5.ucDigEncoderSel = 1 << dig_encoder;
			args.v5.ucDPLaneSet = lane_set;
			अवरोध;
		हाल 6:
			args.v6.ucAction = action;
			अगर (is_dp)
				args.v6.ulSymClock = cpu_to_le32(dp_घड़ी / 10);
			अन्यथा
				args.v6.ulSymClock = cpu_to_le32(amdgpu_encoder->pixel_घड़ी / 10);

			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				अगर (dig->linkb)
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYB;
				अन्यथा
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYA;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				अगर (dig->linkb)
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYD;
				अन्यथा
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYC;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				अगर (dig->linkb)
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYF;
				अन्यथा
					args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYE;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
				args.v6.ucPhyId = ATOM_PHY_ID_UNIPHYG;
				अवरोध;
			पूर्ण
			अगर (is_dp)
				args.v6.ucLaneNum = dp_lane_count;
			अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v6.ucLaneNum = 8;
			अन्यथा
				args.v6.ucLaneNum = 4;
			args.v6.ucConnObjId = connector_object_id;
			अगर (action == ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH)
				args.v6.ucDPLaneSet = lane_set;
			अन्यथा
				args.v6.ucDigMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);

			अगर (hpd_id == AMDGPU_HPD_NONE)
				args.v6.ucHPDSel = 0;
			अन्यथा
				args.v6.ucHPDSel = hpd_id + 1;
			args.v6.ucDigEncoderSel = 1 << dig_encoder;
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version %d, %d\n", frev, crev);
		अवरोध;
	पूर्ण

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

bool
amdgpu_atombios_encoder_set_edp_panel_घातer(काष्ठा drm_connector *connector,
				     पूर्णांक action)
अणु
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा drm_device *dev = amdgpu_connector->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	जोड़ dig_transmitter_control args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, UNIPHYTransmitterControl);
	uपूर्णांक8_t frev, crev;

	अगर (connector->connector_type != DRM_MODE_CONNECTOR_eDP)
		जाओ करोne;

	अगर ((action != ATOM_TRANSMITTER_ACTION_POWER_ON) &&
	    (action != ATOM_TRANSMITTER_ACTION_POWER_OFF))
		जाओ करोne;

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		जाओ करोne;

	स_रखो(&args, 0, माप(args));

	args.v1.ucAction = action;

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	/* रुको क्रम the panel to घातer up */
	अगर (action == ATOM_TRANSMITTER_ACTION_POWER_ON) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 300; i++) अणु
			अगर (amdgpu_display_hpd_sense(adev, amdgpu_connector->hpd.hpd))
				वापस true;
			mdelay(1);
		पूर्ण
		वापस false;
	पूर्ण
करोne:
	वापस true;
पूर्ण

जोड़ बाह्यal_encoder_control अणु
	EXTERNAL_ENCODER_CONTROL_PS_ALLOCATION v1;
	EXTERNAL_ENCODER_CONTROL_PS_ALLOCATION_V3 v3;
पूर्ण;

अटल व्योम
amdgpu_atombios_encoder_setup_बाह्यal_encoder(काष्ठा drm_encoder *encoder,
					काष्ठा drm_encoder *ext_encoder,
					पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_encoder *ext_amdgpu_encoder = to_amdgpu_encoder(ext_encoder);
	जोड़ बाह्यal_encoder_control args;
	काष्ठा drm_connector *connector;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ExternalEncoderControl);
	u8 frev, crev;
	पूर्णांक dp_घड़ी = 0;
	पूर्णांक dp_lane_count = 0;
	पूर्णांक connector_object_id = 0;
	u32 ext_क्रमागत = (ext_amdgpu_encoder->encoder_क्रमागत & ENUM_ID_MASK) >> ENUM_ID_SHIFT;

	अगर (action == EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT)
		connector = amdgpu_get_connector_क्रम_encoder_init(encoder);
	अन्यथा
		connector = amdgpu_get_connector_क्रम_encoder(encoder);

	अगर (connector) अणु
		काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
		काष्ठा amdgpu_connector_atom_dig *dig_connector =
			amdgpu_connector->con_priv;

		dp_घड़ी = dig_connector->dp_घड़ी;
		dp_lane_count = dig_connector->dp_lane_count;
		connector_object_id =
			(amdgpu_connector->connector_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	पूर्ण

	स_रखो(&args, 0, माप(args));

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		/* no params on frev 1 */
		अवरोध;
	हाल 2:
		चयन (crev) अणु
		हाल 1:
		हाल 2:
			args.v1.sDigEncoder.ucAction = action;
			args.v1.sDigEncoder.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			args.v1.sDigEncoder.ucEncoderMode =
				amdgpu_atombios_encoder_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v1.sDigEncoder.ucEncoderMode)) अणु
				अगर (dp_घड़ी == 270000)
					args.v1.sDigEncoder.ucConfig |= ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ;
				args.v1.sDigEncoder.ucLaneNum = dp_lane_count;
			पूर्ण अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v1.sDigEncoder.ucLaneNum = 8;
			अन्यथा
				args.v1.sDigEncoder.ucLaneNum = 4;
			अवरोध;
		हाल 3:
			args.v3.sExtEncoder.ucAction = action;
			अगर (action == EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT)
				args.v3.sExtEncoder.usConnectorId = cpu_to_le16(connector_object_id);
			अन्यथा
				args.v3.sExtEncoder.usPixelClock = cpu_to_le16(amdgpu_encoder->pixel_घड़ी / 10);
			args.v3.sExtEncoder.ucEncoderMode =
				amdgpu_atombios_encoder_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v3.sExtEncoder.ucEncoderMode)) अणु
				अगर (dp_घड़ी == 270000)
					args.v3.sExtEncoder.ucConfig |= EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ;
				अन्यथा अगर (dp_घड़ी == 540000)
					args.v3.sExtEncoder.ucConfig |= EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_5_40GHZ;
				args.v3.sExtEncoder.ucLaneNum = dp_lane_count;
			पूर्ण अन्यथा अगर (amdgpu_dig_monitor_is_duallink(encoder, amdgpu_encoder->pixel_घड़ी))
				args.v3.sExtEncoder.ucLaneNum = 8;
			अन्यथा
				args.v3.sExtEncoder.ucLaneNum = 4;
			चयन (ext_क्रमागत) अणु
			हाल GRAPH_OBJECT_ENUM_ID1:
				args.v3.sExtEncoder.ucConfig |= EXTERNAL_ENCODER_CONFIG_V3_ENCODER1;
				अवरोध;
			हाल GRAPH_OBJECT_ENUM_ID2:
				args.v3.sExtEncoder.ucConfig |= EXTERNAL_ENCODER_CONFIG_V3_ENCODER2;
				अवरोध;
			हाल GRAPH_OBJECT_ENUM_ID3:
				args.v3.sExtEncoder.ucConfig |= EXTERNAL_ENCODER_CONFIG_V3_ENCODER3;
				अवरोध;
			पूर्ण
			args.v3.sExtEncoder.ucBitPerColor = amdgpu_atombios_encoder_get_bpc(encoder);
			अवरोध;
		शेष:
			DRM_ERROR("Unknown table version: %d, %d\n", frev, crev);
			वापस;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version: %d, %d\n", frev, crev);
		वापस;
	पूर्ण
	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम
amdgpu_atombios_encoder_setup_dig(काष्ठा drm_encoder *encoder, पूर्णांक action)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा drm_encoder *ext_encoder = amdgpu_get_बाह्यal_encoder(encoder);
	काष्ठा amdgpu_encoder_atom_dig *dig = amdgpu_encoder->enc_priv;
	काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);
	काष्ठा amdgpu_connector *amdgpu_connector = शून्य;
	काष्ठा amdgpu_connector_atom_dig *amdgpu_dig_connector = शून्य;

	अगर (connector) अणु
		amdgpu_connector = to_amdgpu_connector(connector);
		amdgpu_dig_connector = amdgpu_connector->con_priv;
	पूर्ण

	अगर (action == ATOM_ENABLE) अणु
		अगर (!connector)
			dig->panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
		अन्यथा
			dig->panel_mode = amdgpu_atombios_dp_get_panel_mode(encoder, connector);

		/* setup and enable the encoder */
		amdgpu_atombios_encoder_setup_dig_encoder(encoder, ATOM_ENCODER_CMD_SETUP, 0);
		amdgpu_atombios_encoder_setup_dig_encoder(encoder,
						   ATOM_ENCODER_CMD_SETUP_PANEL_MODE,
						   dig->panel_mode);
		अगर (ext_encoder)
			amdgpu_atombios_encoder_setup_बाह्यal_encoder(encoder, ext_encoder,
								EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP);
		अगर (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector) अणु
			अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
				amdgpu_atombios_encoder_set_edp_panel_घातer(connector,
								     ATOM_TRANSMITTER_ACTION_POWER_ON);
				amdgpu_dig_connector->edp_on = true;
			पूर्ण
		पूर्ण
		/* enable the transmitter */
		amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
						       ATOM_TRANSMITTER_ACTION_ENABLE,
						       0, 0);
		अगर (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector) अणु
			/* DP_SET_POWER_D0 is set in amdgpu_atombios_dp_link_train */
			amdgpu_atombios_dp_link_train(encoder, connector);
			amdgpu_atombios_encoder_setup_dig_encoder(encoder, ATOM_ENCODER_CMD_DP_VIDEO_ON, 0);
		पूर्ण
		अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			amdgpu_atombios_encoder_set_backlight_level(amdgpu_encoder, dig->backlight_level);
		अगर (ext_encoder)
			amdgpu_atombios_encoder_setup_बाह्यal_encoder(encoder, ext_encoder, ATOM_ENABLE);
	पूर्ण अन्यथा अणु
		अगर (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector)
			amdgpu_atombios_encoder_setup_dig_encoder(encoder,
							   ATOM_ENCODER_CMD_DP_VIDEO_OFF, 0);
		अगर (ext_encoder)
			amdgpu_atombios_encoder_setup_बाह्यal_encoder(encoder, ext_encoder, ATOM_DISABLE);
		अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
							       ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);

		अगर (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector)
			amdgpu_atombios_dp_set_rx_घातer_state(connector, DP_SET_POWER_D3);
		/* disable the transmitter */
		amdgpu_atombios_encoder_setup_dig_transmitter(encoder,
						       ATOM_TRANSMITTER_ACTION_DISABLE, 0, 0);
		अगर (ENCODER_MODE_IS_DP(amdgpu_atombios_encoder_get_encoder_mode(encoder)) &&
		    connector) अणु
			अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
				amdgpu_atombios_encoder_set_edp_panel_घातer(connector,
								     ATOM_TRANSMITTER_ACTION_POWER_OFF);
				amdgpu_dig_connector->edp_on = false;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम
amdgpu_atombios_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);

	DRM_DEBUG_KMS("encoder dpms %d to mode %d, devices %08x, active_devices %08x\n",
		  amdgpu_encoder->encoder_id, mode, amdgpu_encoder->devices,
		  amdgpu_encoder->active_device);
	चयन (amdgpu_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		चयन (mode) अणु
		हाल DRM_MODE_DPMS_ON:
			amdgpu_atombios_encoder_setup_dig(encoder, ATOM_ENABLE);
			अवरोध;
		हाल DRM_MODE_DPMS_STANDBY:
		हाल DRM_MODE_DPMS_SUSPEND:
		हाल DRM_MODE_DPMS_OFF:
			amdgpu_atombios_encoder_setup_dig(encoder, ATOM_DISABLE);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		चयन (mode) अणु
		हाल DRM_MODE_DPMS_ON:
			amdgpu_atombios_encoder_setup_dvo(encoder, ATOM_ENABLE);
			अवरोध;
		हाल DRM_MODE_DPMS_STANDBY:
		हाल DRM_MODE_DPMS_SUSPEND:
		हाल DRM_MODE_DPMS_OFF:
			amdgpu_atombios_encoder_setup_dvo(encoder, ATOM_DISABLE);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		चयन (mode) अणु
		हाल DRM_MODE_DPMS_ON:
			amdgpu_atombios_encoder_setup_dac(encoder, ATOM_ENABLE);
			अवरोध;
		हाल DRM_MODE_DPMS_STANDBY:
		हाल DRM_MODE_DPMS_SUSPEND:
		हाल DRM_MODE_DPMS_OFF:
			amdgpu_atombios_encoder_setup_dac(encoder, ATOM_DISABLE);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस;
	पूर्ण
पूर्ण

जोड़ crtc_source_param अणु
	SELECT_CRTC_SOURCE_PS_ALLOCATION v1;
	SELECT_CRTC_SOURCE_PARAMETERS_V2 v2;
	SELECT_CRTC_SOURCE_PARAMETERS_V3 v3;
पूर्ण;

व्योम
amdgpu_atombios_encoder_set_crtc_source(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_crtc *amdgpu_crtc = to_amdgpu_crtc(encoder->crtc);
	जोड़ crtc_source_param args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SelectCRTC_Source);
	uपूर्णांक8_t frev, crev;
	काष्ठा amdgpu_encoder_atom_dig *dig;

	स_रखो(&args, 0, माप(args));

	अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
		शेष:
			args.v1.ucCRTC = amdgpu_crtc->crtc_id;
			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
				args.v1.ucDevice = ATOM_DEVICE_DFP1_INDEX;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
			हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
				अगर (amdgpu_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT)
					args.v1.ucDevice = ATOM_DEVICE_LCD1_INDEX;
				अन्यथा
					args.v1.ucDevice = ATOM_DEVICE_DFP3_INDEX;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
			हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
				args.v1.ucDevice = ATOM_DEVICE_DFP2_INDEX;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
				अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_TV1_INDEX;
				अन्यथा अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_CV_INDEX;
				अन्यथा
					args.v1.ucDevice = ATOM_DEVICE_CRT1_INDEX;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
				अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_TV1_INDEX;
				अन्यथा अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_CV_INDEX;
				अन्यथा
					args.v1.ucDevice = ATOM_DEVICE_CRT2_INDEX;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 2:
			args.v2.ucCRTC = amdgpu_crtc->crtc_id;
			अगर (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE) अणु
				काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);

				अगर (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
				अन्यथा अगर (connector->connector_type == DRM_MODE_CONNECTOR_VGA)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_CRT;
				अन्यथा
					args.v2.ucEncodeMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);
			पूर्ण अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
				args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
			पूर्ण अन्यथा अणु
				args.v2.ucEncodeMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);
			पूर्ण
			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
				dig = amdgpu_encoder->enc_priv;
				चयन (dig->dig_encoder) अणु
				हाल 0:
					args.v2.ucEncoderID = ASIC_INT_DIG1_ENCODER_ID;
					अवरोध;
				हाल 1:
					args.v2.ucEncoderID = ASIC_INT_DIG2_ENCODER_ID;
					अवरोध;
				हाल 2:
					args.v2.ucEncoderID = ASIC_INT_DIG3_ENCODER_ID;
					अवरोध;
				हाल 3:
					args.v2.ucEncoderID = ASIC_INT_DIG4_ENCODER_ID;
					अवरोध;
				हाल 4:
					args.v2.ucEncoderID = ASIC_INT_DIG5_ENCODER_ID;
					अवरोध;
				हाल 5:
					args.v2.ucEncoderID = ASIC_INT_DIG6_ENCODER_ID;
					अवरोध;
				हाल 6:
					args.v2.ucEncoderID = ASIC_INT_DIG7_ENCODER_ID;
					अवरोध;
				पूर्ण
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
				args.v2.ucEncoderID = ASIC_INT_DVO_ENCODER_ID;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
				अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा
					args.v2.ucEncoderID = ASIC_INT_DAC1_ENCODER_ID;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
				अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा
					args.v2.ucEncoderID = ASIC_INT_DAC2_ENCODER_ID;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 3:
			args.v3.ucCRTC = amdgpu_crtc->crtc_id;
			अगर (amdgpu_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE) अणु
				काष्ठा drm_connector *connector = amdgpu_get_connector_क्रम_encoder(encoder);

				अगर (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
				अन्यथा अगर (connector->connector_type == DRM_MODE_CONNECTOR_VGA)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_CRT;
				अन्यथा
					args.v2.ucEncodeMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);
			पूर्ण अन्यथा अगर (amdgpu_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
				args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
			पूर्ण अन्यथा अणु
				args.v2.ucEncodeMode = amdgpu_atombios_encoder_get_encoder_mode(encoder);
			पूर्ण
			args.v3.ucDstBpc = amdgpu_atombios_encoder_get_bpc(encoder);
			चयन (amdgpu_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
				dig = amdgpu_encoder->enc_priv;
				चयन (dig->dig_encoder) अणु
				हाल 0:
					args.v3.ucEncoderID = ASIC_INT_DIG1_ENCODER_ID;
					अवरोध;
				हाल 1:
					args.v3.ucEncoderID = ASIC_INT_DIG2_ENCODER_ID;
					अवरोध;
				हाल 2:
					args.v3.ucEncoderID = ASIC_INT_DIG3_ENCODER_ID;
					अवरोध;
				हाल 3:
					args.v3.ucEncoderID = ASIC_INT_DIG4_ENCODER_ID;
					अवरोध;
				हाल 4:
					args.v3.ucEncoderID = ASIC_INT_DIG5_ENCODER_ID;
					अवरोध;
				हाल 5:
					args.v3.ucEncoderID = ASIC_INT_DIG6_ENCODER_ID;
					अवरोध;
				हाल 6:
					args.v3.ucEncoderID = ASIC_INT_DIG7_ENCODER_ID;
					अवरोध;
				पूर्ण
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
				args.v3.ucEncoderID = ASIC_INT_DVO_ENCODER_ID;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
				अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v3.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v3.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा
					args.v3.ucEncoderID = ASIC_INT_DAC1_ENCODER_ID;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
				अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v3.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा अगर (amdgpu_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v3.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा
					args.v3.ucEncoderID = ASIC_INT_DAC2_ENCODER_ID;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version: %d, %d\n", frev, crev);
		वापस;
	पूर्ण

	amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

/* This only needs to be called once at startup */
व्योम
amdgpu_atombios_encoder_init_dig(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_encoder *encoder;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
		काष्ठा drm_encoder *ext_encoder = amdgpu_get_बाह्यal_encoder(encoder);

		चयन (amdgpu_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			amdgpu_atombios_encoder_setup_dig_transmitter(encoder, ATOM_TRANSMITTER_ACTION_INIT,
							       0, 0);
			अवरोध;
		पूर्ण

		अगर (ext_encoder)
			amdgpu_atombios_encoder_setup_बाह्यal_encoder(encoder, ext_encoder,
								EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT);
	पूर्ण
पूर्ण

अटल bool
amdgpu_atombios_encoder_dac_load_detect(काष्ठा drm_encoder *encoder,
				 काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);

	अगर (amdgpu_encoder->devices & (ATOM_DEVICE_TV_SUPPORT |
				       ATOM_DEVICE_CV_SUPPORT |
				       ATOM_DEVICE_CRT_SUPPORT)) अणु
		DAC_LOAD_DETECTION_PS_ALLOCATION args;
		पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DAC_LoadDetection);
		uपूर्णांक8_t frev, crev;

		स_रखो(&args, 0, माप(args));

		अगर (!amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context, index, &frev, &crev))
			वापस false;

		args.sDacload.ucMisc = 0;

		अगर ((amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DAC1) ||
		    (amdgpu_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1))
			args.sDacload.ucDacType = ATOM_DAC_A;
		अन्यथा
			args.sDacload.ucDacType = ATOM_DAC_B;

		अगर (amdgpu_connector->devices & ATOM_DEVICE_CRT1_SUPPORT)
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_CRT1_SUPPORT);
		अन्यथा अगर (amdgpu_connector->devices & ATOM_DEVICE_CRT2_SUPPORT)
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_CRT2_SUPPORT);
		अन्यथा अगर (amdgpu_connector->devices & ATOM_DEVICE_CV_SUPPORT) अणु
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_CV_SUPPORT);
			अगर (crev >= 3)
				args.sDacload.ucMisc = DAC_LOAD_MISC_YPrPb;
		पूर्ण अन्यथा अगर (amdgpu_connector->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_TV1_SUPPORT);
			अगर (crev >= 3)
				args.sDacload.ucMisc = DAC_LOAD_MISC_YPrPb;
		पूर्ण

		amdgpu_atom_execute_table(adev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		वापस true;
	पूर्ण अन्यथा
		वापस false;
पूर्ण

क्रमागत drm_connector_status
amdgpu_atombios_encoder_dac_detect(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	uपूर्णांक32_t bios_0_scratch;

	अगर (!amdgpu_atombios_encoder_dac_load_detect(encoder, connector)) अणु
		DRM_DEBUG_KMS("detect returned false \n");
		वापस connector_status_unknown;
	पूर्ण

	bios_0_scratch = RREG32(mmBIOS_SCRATCH_0);

	DRM_DEBUG_KMS("Bios 0 scratch %x %08x\n", bios_0_scratch, amdgpu_encoder->devices);
	अगर (amdgpu_connector->devices & ATOM_DEVICE_CRT1_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT1_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (amdgpu_connector->devices & ATOM_DEVICE_CRT2_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT2_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (amdgpu_connector->devices & ATOM_DEVICE_CV_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_CV_MASK|ATOM_S0_CV_MASK_A))
			वापस connector_status_connected;
	पूर्ण
	अगर (amdgpu_connector->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_TV1_COMPOSITE | ATOM_S0_TV1_COMPOSITE_A))
			वापस connector_status_connected; /* CTV */
		अन्यथा अगर (bios_0_scratch & (ATOM_S0_TV1_SVIDEO | ATOM_S0_TV1_SVIDEO_A))
			वापस connector_status_connected; /* STV */
	पूर्ण
	वापस connector_status_disconnected;
पूर्ण

क्रमागत drm_connector_status
amdgpu_atombios_encoder_dig_detect(काष्ठा drm_encoder *encoder,
			    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	काष्ठा amdgpu_connector *amdgpu_connector = to_amdgpu_connector(connector);
	काष्ठा drm_encoder *ext_encoder = amdgpu_get_बाह्यal_encoder(encoder);
	u32 bios_0_scratch;

	अगर (!ext_encoder)
		वापस connector_status_unknown;

	अगर ((amdgpu_connector->devices & ATOM_DEVICE_CRT_SUPPORT) == 0)
		वापस connector_status_unknown;

	/* load detect on the dp bridge */
	amdgpu_atombios_encoder_setup_बाह्यal_encoder(encoder, ext_encoder,
						EXTERNAL_ENCODER_ACTION_V3_DACLOAD_DETECTION);

	bios_0_scratch = RREG32(mmBIOS_SCRATCH_0);

	DRM_DEBUG_KMS("Bios 0 scratch %x %08x\n", bios_0_scratch, amdgpu_encoder->devices);
	अगर (amdgpu_connector->devices & ATOM_DEVICE_CRT1_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT1_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (amdgpu_connector->devices & ATOM_DEVICE_CRT2_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT2_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (amdgpu_connector->devices & ATOM_DEVICE_CV_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_CV_MASK|ATOM_S0_CV_MASK_A))
			वापस connector_status_connected;
	पूर्ण
	अगर (amdgpu_connector->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_TV1_COMPOSITE | ATOM_S0_TV1_COMPOSITE_A))
			वापस connector_status_connected; /* CTV */
		अन्यथा अगर (bios_0_scratch & (ATOM_S0_TV1_SVIDEO | ATOM_S0_TV1_SVIDEO_A))
			वापस connector_status_connected; /* STV */
	पूर्ण
	वापस connector_status_disconnected;
पूर्ण

व्योम
amdgpu_atombios_encoder_setup_ext_encoder_ddc(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_encoder *ext_encoder = amdgpu_get_बाह्यal_encoder(encoder);

	अगर (ext_encoder)
		/* ddc_setup on the dp bridge */
		amdgpu_atombios_encoder_setup_बाह्यal_encoder(encoder, ext_encoder,
							EXTERNAL_ENCODER_ACTION_V3_DDC_SETUP);

पूर्ण

व्योम
amdgpu_atombios_encoder_set_bios_scratch_regs(काष्ठा drm_connector *connector,
				       काष्ठा drm_encoder *encoder,
				       bool connected)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_connector *amdgpu_connector =
	    to_amdgpu_connector(connector);
	काष्ठा amdgpu_encoder *amdgpu_encoder = to_amdgpu_encoder(encoder);
	uपूर्णांक32_t bios_0_scratch, bios_3_scratch, bios_6_scratch;

	bios_0_scratch = RREG32(mmBIOS_SCRATCH_0);
	bios_3_scratch = RREG32(mmBIOS_SCRATCH_3);
	bios_6_scratch = RREG32(mmBIOS_SCRATCH_6);

	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_LCD1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("LCD1 connected\n");
			bios_0_scratch |= ATOM_S0_LCD1;
			bios_3_scratch |= ATOM_S3_LCD1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_LCD1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("LCD1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_LCD1;
			bios_3_scratch &= ~ATOM_S3_LCD1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_LCD1;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_CRT1_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_CRT1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("CRT1 connected\n");
			bios_0_scratch |= ATOM_S0_CRT1_COLOR;
			bios_3_scratch |= ATOM_S3_CRT1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CRT1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("CRT1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CRT1_MASK;
			bios_3_scratch &= ~ATOM_S3_CRT1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CRT1;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_CRT2_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_CRT2_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("CRT2 connected\n");
			bios_0_scratch |= ATOM_S0_CRT2_COLOR;
			bios_3_scratch |= ATOM_S3_CRT2_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_CRT2;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("CRT2 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_CRT2_MASK;
			bios_3_scratch &= ~ATOM_S3_CRT2_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_CRT2;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_DFP1_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_DFP1_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP1 connected\n");
			bios_0_scratch |= ATOM_S0_DFP1;
			bios_3_scratch |= ATOM_S3_DFP1_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP1;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP1 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP1;
			bios_3_scratch &= ~ATOM_S3_DFP1_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP1;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_DFP2_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_DFP2_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP2 connected\n");
			bios_0_scratch |= ATOM_S0_DFP2;
			bios_3_scratch |= ATOM_S3_DFP2_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP2;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP2 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP2;
			bios_3_scratch &= ~ATOM_S3_DFP2_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP2;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_DFP3_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_DFP3_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP3 connected\n");
			bios_0_scratch |= ATOM_S0_DFP3;
			bios_3_scratch |= ATOM_S3_DFP3_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP3;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP3 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP3;
			bios_3_scratch &= ~ATOM_S3_DFP3_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP3;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_DFP4_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_DFP4_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP4 connected\n");
			bios_0_scratch |= ATOM_S0_DFP4;
			bios_3_scratch |= ATOM_S3_DFP4_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP4;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP4 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP4;
			bios_3_scratch &= ~ATOM_S3_DFP4_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP4;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_DFP5_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_DFP5_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP5 connected\n");
			bios_0_scratch |= ATOM_S0_DFP5;
			bios_3_scratch |= ATOM_S3_DFP5_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP5;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP5 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP5;
			bios_3_scratch &= ~ATOM_S3_DFP5_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP5;
		पूर्ण
	पूर्ण
	अगर ((amdgpu_encoder->devices & ATOM_DEVICE_DFP6_SUPPORT) &&
	    (amdgpu_connector->devices & ATOM_DEVICE_DFP6_SUPPORT)) अणु
		अगर (connected) अणु
			DRM_DEBUG_KMS("DFP6 connected\n");
			bios_0_scratch |= ATOM_S0_DFP6;
			bios_3_scratch |= ATOM_S3_DFP6_ACTIVE;
			bios_6_scratch |= ATOM_S6_ACC_REQ_DFP6;
		पूर्ण अन्यथा अणु
			DRM_DEBUG_KMS("DFP6 disconnected\n");
			bios_0_scratch &= ~ATOM_S0_DFP6;
			bios_3_scratch &= ~ATOM_S3_DFP6_ACTIVE;
			bios_6_scratch &= ~ATOM_S6_ACC_REQ_DFP6;
		पूर्ण
	पूर्ण

	WREG32(mmBIOS_SCRATCH_0, bios_0_scratch);
	WREG32(mmBIOS_SCRATCH_3, bios_3_scratch);
	WREG32(mmBIOS_SCRATCH_6, bios_6_scratch);
पूर्ण

जोड़ lvds_info अणु
	काष्ठा _ATOM_LVDS_INFO info;
	काष्ठा _ATOM_LVDS_INFO_V12 info_12;
पूर्ण;

काष्ठा amdgpu_encoder_atom_dig *
amdgpu_atombios_encoder_get_lcd_info(काष्ठा amdgpu_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_mode_info *mode_info = &adev->mode_info;
	पूर्णांक index = GetIndexIntoMasterTable(DATA, LVDS_Info);
	uपूर्णांक16_t data_offset, misc;
	जोड़ lvds_info *lvds_info;
	uपूर्णांक8_t frev, crev;
	काष्ठा amdgpu_encoder_atom_dig *lvds = शून्य;
	पूर्णांक encoder_क्रमागत = (encoder->encoder_क्रमागत & ENUM_ID_MASK) >> ENUM_ID_SHIFT;

	अगर (amdgpu_atom_parse_data_header(mode_info->atom_context, index, शून्य,
				   &frev, &crev, &data_offset)) अणु
		lvds_info =
			(जोड़ lvds_info *)(mode_info->atom_context->bios + data_offset);
		lvds =
		    kzalloc(माप(काष्ठा amdgpu_encoder_atom_dig), GFP_KERNEL);

		अगर (!lvds)
			वापस शून्य;

		lvds->native_mode.घड़ी =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usPixClk) * 10;
		lvds->native_mode.hdisplay =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usHActive);
		lvds->native_mode.vdisplay =
		    le16_to_cpu(lvds_info->info.sLCDTiming.usVActive);
		lvds->native_mode.htotal = lvds->native_mode.hdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHBlanking_Time);
		lvds->native_mode.hsync_start = lvds->native_mode.hdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHSyncOffset);
		lvds->native_mode.hsync_end = lvds->native_mode.hsync_start +
			le16_to_cpu(lvds_info->info.sLCDTiming.usHSyncWidth);
		lvds->native_mode.vtotal = lvds->native_mode.vdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVBlanking_Time);
		lvds->native_mode.vsync_start = lvds->native_mode.vdisplay +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVSyncOffset);
		lvds->native_mode.vsync_end = lvds->native_mode.vsync_start +
			le16_to_cpu(lvds_info->info.sLCDTiming.usVSyncWidth);
		lvds->panel_pwr_delay =
		    le16_to_cpu(lvds_info->info.usOffDelayInMs);
		lvds->lcd_misc = lvds_info->info.ucLVDS_Misc;

		misc = le16_to_cpu(lvds_info->info.sLCDTiming.susModeMiscInfo.usAccess);
		अगर (misc & ATOM_VSYNC_POLARITY)
			lvds->native_mode.flags |= DRM_MODE_FLAG_NVSYNC;
		अगर (misc & ATOM_HSYNC_POLARITY)
			lvds->native_mode.flags |= DRM_MODE_FLAG_NHSYNC;
		अगर (misc & ATOM_COMPOSITESYNC)
			lvds->native_mode.flags |= DRM_MODE_FLAG_CSYNC;
		अगर (misc & ATOM_INTERLACE)
			lvds->native_mode.flags |= DRM_MODE_FLAG_INTERLACE;
		अगर (misc & ATOM_DOUBLE_CLOCK_MODE)
			lvds->native_mode.flags |= DRM_MODE_FLAG_DBLSCAN;

		lvds->native_mode.width_mm = le16_to_cpu(lvds_info->info.sLCDTiming.usImageHSize);
		lvds->native_mode.height_mm = le16_to_cpu(lvds_info->info.sLCDTiming.usImageVSize);

		/* set crtc values */
		drm_mode_set_crtcinfo(&lvds->native_mode, CRTC_INTERLACE_HALVE_V);

		lvds->lcd_ss_id = lvds_info->info.ucSS_Id;

		encoder->native_mode = lvds->native_mode;

		अगर (encoder_क्रमागत == 2)
			lvds->linkb = true;
		अन्यथा
			lvds->linkb = false;

		/* parse the lcd record table */
		अगर (le16_to_cpu(lvds_info->info.usModePatchTableOffset)) अणु
			ATOM_FAKE_EDID_PATCH_RECORD *fake_edid_record;
			ATOM_PANEL_RESOLUTION_PATCH_RECORD *panel_res_record;
			bool bad_record = false;
			u8 *record;

			अगर ((frev == 1) && (crev < 2))
				/* असलolute */
				record = (u8 *)(mode_info->atom_context->bios +
						le16_to_cpu(lvds_info->info.usModePatchTableOffset));
			अन्यथा
				/* relative */
				record = (u8 *)(mode_info->atom_context->bios +
						data_offset +
						le16_to_cpu(lvds_info->info.usModePatchTableOffset));
			जबतक (*record != ATOM_RECORD_END_TYPE) अणु
				चयन (*record) अणु
				हाल LCD_MODE_PATCH_RECORD_MODE_TYPE:
					record += माप(ATOM_PATCH_RECORD_MODE);
					अवरोध;
				हाल LCD_RTS_RECORD_TYPE:
					record += माप(ATOM_LCD_RTS_RECORD);
					अवरोध;
				हाल LCD_CAP_RECORD_TYPE:
					record += माप(ATOM_LCD_MODE_CONTROL_CAP);
					अवरोध;
				हाल LCD_FAKE_EDID_PATCH_RECORD_TYPE:
					fake_edid_record = (ATOM_FAKE_EDID_PATCH_RECORD *)record;
					अगर (fake_edid_record->ucFakeEDIDLength) अणु
						काष्ठा edid *edid;
						पूर्णांक edid_size =
							max((पूर्णांक)EDID_LENGTH, (पूर्णांक)fake_edid_record->ucFakeEDIDLength);
						edid = kदो_स्मृति(edid_size, GFP_KERNEL);
						अगर (edid) अणु
							स_नकल((u8 *)edid, (u8 *)&fake_edid_record->ucFakeEDIDString[0],
							       fake_edid_record->ucFakeEDIDLength);

							अगर (drm_edid_is_valid(edid)) अणु
								adev->mode_info.bios_hardcoded_edid = edid;
								adev->mode_info.bios_hardcoded_edid_size = edid_size;
							पूर्ण अन्यथा
								kमुक्त(edid);
						पूर्ण
					पूर्ण
					record += fake_edid_record->ucFakeEDIDLength ?
						fake_edid_record->ucFakeEDIDLength + 2 :
						माप(ATOM_FAKE_EDID_PATCH_RECORD);
					अवरोध;
				हाल LCD_PANEL_RESOLUTION_RECORD_TYPE:
					panel_res_record = (ATOM_PANEL_RESOLUTION_PATCH_RECORD *)record;
					lvds->native_mode.width_mm = panel_res_record->usHSize;
					lvds->native_mode.height_mm = panel_res_record->usVSize;
					record += माप(ATOM_PANEL_RESOLUTION_PATCH_RECORD);
					अवरोध;
				शेष:
					DRM_ERROR("Bad LCD record %d\n", *record);
					bad_record = true;
					अवरोध;
				पूर्ण
				अगर (bad_record)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस lvds;
पूर्ण

काष्ठा amdgpu_encoder_atom_dig *
amdgpu_atombios_encoder_get_dig_info(काष्ठा amdgpu_encoder *amdgpu_encoder)
अणु
	पूर्णांक encoder_क्रमागत = (amdgpu_encoder->encoder_क्रमागत & ENUM_ID_MASK) >> ENUM_ID_SHIFT;
	काष्ठा amdgpu_encoder_atom_dig *dig = kzalloc(माप(काष्ठा amdgpu_encoder_atom_dig), GFP_KERNEL);

	अगर (!dig)
		वापस शून्य;

	/* coherent mode by शेष */
	dig->coherent_mode = true;
	dig->dig_encoder = -1;

	अगर (encoder_क्रमागत == 2)
		dig->linkb = true;
	अन्यथा
		dig->linkb = false;

	वापस dig;
पूर्ण

