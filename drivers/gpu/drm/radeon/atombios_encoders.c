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

#समावेश <linux/backlight.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/radeon_drm.h>

#समावेश "atom.h"
#समावेश "radeon_atombios.h"
#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_audio.h"

बाह्य पूर्णांक atom_debug;

अटल u8
radeon_atom_get_backlight_level_from_reg(काष्ठा radeon_device *rdev)
अणु
	u8 backlight_level;
	u32 bios_2_scratch;

	अगर (rdev->family >= CHIP_R600)
		bios_2_scratch = RREG32(R600_BIOS_2_SCRATCH);
	अन्यथा
		bios_2_scratch = RREG32(RADEON_BIOS_2_SCRATCH);

	backlight_level = ((bios_2_scratch & ATOM_S2_CURRENT_BL_LEVEL_MASK) >>
			   ATOM_S2_CURRENT_BL_LEVEL_SHIFT);

	वापस backlight_level;
पूर्ण

अटल व्योम
radeon_atom_set_backlight_level_to_reg(काष्ठा radeon_device *rdev,
				       u8 backlight_level)
अणु
	u32 bios_2_scratch;

	अगर (rdev->family >= CHIP_R600)
		bios_2_scratch = RREG32(R600_BIOS_2_SCRATCH);
	अन्यथा
		bios_2_scratch = RREG32(RADEON_BIOS_2_SCRATCH);

	bios_2_scratch &= ~ATOM_S2_CURRENT_BL_LEVEL_MASK;
	bios_2_scratch |= ((backlight_level << ATOM_S2_CURRENT_BL_LEVEL_SHIFT) &
			   ATOM_S2_CURRENT_BL_LEVEL_MASK);

	अगर (rdev->family >= CHIP_R600)
		WREG32(R600_BIOS_2_SCRATCH, bios_2_scratch);
	अन्यथा
		WREG32(RADEON_BIOS_2_SCRATCH, bios_2_scratch);
पूर्ण

u8
atombios_get_backlight_level(काष्ठा radeon_encoder *radeon_encoder)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	अगर (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस 0;

	वापस radeon_atom_get_backlight_level_from_reg(rdev);
पूर्ण

व्योम
atombios_set_backlight_level(काष्ठा radeon_encoder *radeon_encoder, u8 level)
अणु
	काष्ठा drm_encoder *encoder = &radeon_encoder->base;
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder_atom_dig *dig;
	DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION args;
	पूर्णांक index;

	अगर (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस;

	अगर ((radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
	    radeon_encoder->enc_priv) अणु
		dig = radeon_encoder->enc_priv;
		dig->backlight_level = level;
		radeon_atom_set_backlight_level_to_reg(rdev, dig->backlight_level);

		चयन (radeon_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
		हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
			index = GetIndexIntoMasterTable(COMMAND, LCD1OutputControl);
			अगर (dig->backlight_level == 0) अणु
				args.ucAction = ATOM_LCD_BLOFF;
				atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
			पूर्ण अन्यथा अणु
				args.ucAction = ATOM_LCD_BL_BRIGHTNESS_CONTROL;
				atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
				args.ucAction = ATOM_LCD_BLON;
				atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
			पूर्ण
			अवरोध;
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			अगर (dig->backlight_level == 0)
				atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);
			अन्यथा अणु
				atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL, 0, 0);
				atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_LCD_BLON, 0, 0);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

अटल u8 radeon_atom_bl_level(काष्ठा backlight_device *bd)
अणु
	u8 level;

	/* Convert brightness to hardware level */
	अगर (bd->props.brightness < 0)
		level = 0;
	अन्यथा अगर (bd->props.brightness > RADEON_MAX_BL_LEVEL)
		level = RADEON_MAX_BL_LEVEL;
	अन्यथा
		level = bd->props.brightness;

	वापस level;
पूर्ण

अटल पूर्णांक radeon_atom_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा radeon_backlight_privdata *pdata = bl_get_data(bd);
	काष्ठा radeon_encoder *radeon_encoder = pdata->encoder;

	atombios_set_backlight_level(radeon_encoder, radeon_atom_bl_level(bd));

	वापस 0;
पूर्ण

अटल पूर्णांक radeon_atom_backlight_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा radeon_backlight_privdata *pdata = bl_get_data(bd);
	काष्ठा radeon_encoder *radeon_encoder = pdata->encoder;
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	वापस radeon_atom_get_backlight_level_from_reg(rdev);
पूर्ण

अटल स्थिर काष्ठा backlight_ops radeon_atom_backlight_ops = अणु
	.get_brightness = radeon_atom_backlight_get_brightness,
	.update_status	= radeon_atom_backlight_update_status,
पूर्ण;

व्योम radeon_atom_backlight_init(काष्ठा radeon_encoder *radeon_encoder,
				काष्ठा drm_connector *drm_connector)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;
	काष्ठा radeon_backlight_privdata *pdata;
	काष्ठा radeon_encoder_atom_dig *dig;
	अक्षर bl_name[16];

	/* Mac laptops with multiple GPUs use the gmux driver क्रम backlight
	 * so करोn't रेजिस्टर a backlight device
	 */
	अगर ((rdev->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_APPLE) &&
	    (rdev->pdev->device == 0x6741))
		वापस;

	अगर (!radeon_encoder->enc_priv)
		वापस;

	अगर (!rdev->is_atom_bios)
		वापस;

	अगर (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस;

	pdata = kदो_स्मृति(माप(काष्ठा radeon_backlight_privdata), GFP_KERNEL);
	अगर (!pdata) अणु
		DRM_ERROR("Memory allocation failed\n");
		जाओ error;
	पूर्ण

	स_रखो(&props, 0, माप(props));
	props.max_brightness = RADEON_MAX_BL_LEVEL;
	props.type = BACKLIGHT_RAW;
	snम_लिखो(bl_name, माप(bl_name),
		 "radeon_bl%d", dev->primary->index);
	bd = backlight_device_रेजिस्टर(bl_name, drm_connector->kdev,
				       pdata, &radeon_atom_backlight_ops, &props);
	अगर (IS_ERR(bd)) अणु
		DRM_ERROR("Backlight registration failed\n");
		जाओ error;
	पूर्ण

	pdata->encoder = radeon_encoder;

	dig = radeon_encoder->enc_priv;
	dig->bl_dev = bd;

	bd->props.brightness = radeon_atom_backlight_get_brightness(bd);
	/* Set a reasonable शेष here अगर the level is 0 otherwise
	 * fbdev will attempt to turn the backlight on after console
	 * unblanking and it will try and restore 0 which turns the backlight
	 * off again.
	 */
	अगर (bd->props.brightness == 0)
		bd->props.brightness = RADEON_MAX_BL_LEVEL;
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	DRM_INFO("radeon atom DIG backlight initialized\n");
	rdev->mode_info.bl_encoder = radeon_encoder;

	वापस;

error:
	kमुक्त(pdata);
	वापस;
पूर्ण

अटल व्योम radeon_atom_backlight_निकास(काष्ठा radeon_encoder *radeon_encoder)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा backlight_device *bd = शून्य;
	काष्ठा radeon_encoder_atom_dig *dig;

	अगर (!radeon_encoder->enc_priv)
		वापस;

	अगर (!rdev->is_atom_bios)
		वापस;

	अगर (!(rdev->mode_info.firmware_flags & ATOM_BIOS_INFO_BL_CONTROLLED_BY_GPU))
		वापस;

	dig = radeon_encoder->enc_priv;
	bd = dig->bl_dev;
	dig->bl_dev = शून्य;

	अगर (bd) अणु
		काष्ठा radeon_legacy_backlight_privdata *pdata;

		pdata = bl_get_data(bd);
		backlight_device_unरेजिस्टर(bd);
		kमुक्त(pdata);

		DRM_INFO("radeon atom LVDS backlight unloaded\n");
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_BACKLIGHT_CLASS_DEVICE */

व्योम radeon_atom_backlight_init(काष्ठा radeon_encoder *encoder)
अणु
पूर्ण

अटल व्योम radeon_atom_backlight_निकास(काष्ठा radeon_encoder *encoder)
अणु
पूर्ण

#पूर्ण_अगर

अटल bool radeon_atom_mode_fixup(काष्ठा drm_encoder *encoder,
				   स्थिर काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;

	/* set the active encoder to connector routing */
	radeon_encoder_set_active_device(encoder);
	drm_mode_set_crtcinfo(adjusted_mode, 0);

	/* hw bug */
	अगर ((mode->flags & DRM_MODE_FLAG_INTERLACE)
	    && (mode->crtc_vsync_start < (mode->crtc_vdisplay + 2)))
		adjusted_mode->crtc_vsync_start = adjusted_mode->crtc_vdisplay + 2;

	/* vertical FP must be at least 1 */
	अगर (mode->crtc_vsync_start == mode->crtc_vdisplay)
		adjusted_mode->crtc_vsync_start++;

	/* get the native mode क्रम scaling */
	अगर (radeon_encoder->active_device & (ATOM_DEVICE_LCD_SUPPORT)) अणु
		radeon_panel_mode_fixup(encoder, adjusted_mode);
	पूर्ण अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT)) अणु
		काष्ठा radeon_encoder_atom_dac *tv_dac = radeon_encoder->enc_priv;
		अगर (tv_dac) अणु
			अगर (tv_dac->tv_std == TV_STD_NTSC ||
			    tv_dac->tv_std == TV_STD_NTSC_J ||
			    tv_dac->tv_std == TV_STD_PAL_M)
				radeon_atom_get_tv_timings(rdev, 0, adjusted_mode);
			अन्यथा
				radeon_atom_get_tv_timings(rdev, 1, adjusted_mode);
		पूर्ण
	पूर्ण अन्यथा अगर (radeon_encoder->rmx_type != RMX_OFF) अणु
		radeon_panel_mode_fixup(encoder, adjusted_mode);
	पूर्ण

	अगर (ASIC_IS_DCE3(rdev) &&
	    ((radeon_encoder->active_device & (ATOM_DEVICE_DFP_SUPPORT | ATOM_DEVICE_LCD_SUPPORT)) ||
	     (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE))) अणु
		काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
		radeon_dp_set_link_config(connector, adjusted_mode);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम
atombios_dac_setup(काष्ठा drm_encoder *encoder, पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	DAC_ENCODER_CONTROL_PS_ALLOCATION args;
	पूर्णांक index = 0;
	काष्ठा radeon_encoder_atom_dac *dac_info = radeon_encoder->enc_priv;

	स_रखो(&args, 0, माप(args));

	चयन (radeon_encoder->encoder_id) अणु
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

	अगर (radeon_encoder->active_device & (ATOM_DEVICE_CRT_SUPPORT))
		args.ucDacStandard = ATOM_DAC1_PS2;
	अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
		args.ucDacStandard = ATOM_DAC1_CV;
	अन्यथा अणु
		चयन (dac_info->tv_std) अणु
		हाल TV_STD_PAL:
		हाल TV_STD_PAL_M:
		हाल TV_STD_SCART_PAL:
		हाल TV_STD_SECAM:
		हाल TV_STD_PAL_CN:
			args.ucDacStandard = ATOM_DAC1_PAL;
			अवरोध;
		हाल TV_STD_NTSC:
		हाल TV_STD_NTSC_J:
		हाल TV_STD_PAL_60:
		शेष:
			args.ucDacStandard = ATOM_DAC1_NTSC;
			अवरोध;
		पूर्ण
	पूर्ण
	args.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

पूर्ण

अटल व्योम
atombios_tv_setup(काष्ठा drm_encoder *encoder, पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	TV_ENCODER_CONTROL_PS_ALLOCATION args;
	पूर्णांक index = 0;
	काष्ठा radeon_encoder_atom_dac *dac_info = radeon_encoder->enc_priv;

	स_रखो(&args, 0, माप(args));

	index = GetIndexIntoMasterTable(COMMAND, TVEncoderControl);

	args.sTVEncoder.ucAction = action;

	अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
		args.sTVEncoder.ucTvStandard = ATOM_TV_CV;
	अन्यथा अणु
		चयन (dac_info->tv_std) अणु
		हाल TV_STD_NTSC:
			args.sTVEncoder.ucTvStandard = ATOM_TV_NTSC;
			अवरोध;
		हाल TV_STD_PAL:
			args.sTVEncoder.ucTvStandard = ATOM_TV_PAL;
			अवरोध;
		हाल TV_STD_PAL_M:
			args.sTVEncoder.ucTvStandard = ATOM_TV_PALM;
			अवरोध;
		हाल TV_STD_PAL_60:
			args.sTVEncoder.ucTvStandard = ATOM_TV_PAL60;
			अवरोध;
		हाल TV_STD_NTSC_J:
			args.sTVEncoder.ucTvStandard = ATOM_TV_NTSCJ;
			अवरोध;
		हाल TV_STD_SCART_PAL:
			args.sTVEncoder.ucTvStandard = ATOM_TV_PAL; /* ??? */
			अवरोध;
		हाल TV_STD_SECAM:
			args.sTVEncoder.ucTvStandard = ATOM_TV_SECAM;
			अवरोध;
		हाल TV_STD_PAL_CN:
			args.sTVEncoder.ucTvStandard = ATOM_TV_PALCN;
			अवरोध;
		शेष:
			args.sTVEncoder.ucTvStandard = ATOM_TV_NTSC;
			अवरोध;
		पूर्ण
	पूर्ण

	args.sTVEncoder.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

पूर्ण

अटल u8 radeon_atom_get_bpc(काष्ठा drm_encoder *encoder)
अणु
	पूर्णांक bpc = 8;

	अगर (encoder->crtc) अणु
		काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
		bpc = radeon_crtc->bpc;
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

व्योम
atombios_dvo_setup(काष्ठा drm_encoder *encoder, पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	जोड़ dvo_encoder_control args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DVOEncoderControl);
	uपूर्णांक8_t frev, crev;

	स_रखो(&args, 0, माप(args));

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	/* some R4xx chips have the wrong frev */
	अगर (rdev->family <= CHIP_RV410)
		frev = 1;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
			/* R4xx, R5xx */
			args.ext_पंचांगds.sXTmdsEncoder.ucEnable = action;

			अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
				args.ext_पंचांगds.sXTmdsEncoder.ucMisc |= PANEL_ENCODER_MISC_DUAL;

			args.ext_पंचांगds.sXTmdsEncoder.ucMisc |= ATOM_PANEL_MISC_888RGB;
			अवरोध;
		हाल 2:
			/* RS600/690/740 */
			args.dvo.sDVOEncoder.ucAction = action;
			args.dvo.sDVOEncoder.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			/* DFP1, CRT1, TV1 depending on the type of port */
			args.dvo.sDVOEncoder.ucDeviceType = ATOM_DEVICE_DFP1_INDEX;

			अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
				args.dvo.sDVOEncoder.usDevAttr.sDigAttrib.ucAttribute |= PANEL_ENCODER_MISC_DUAL;
			अवरोध;
		हाल 3:
			/* R6xx */
			args.dvo_v3.ucAction = action;
			args.dvo_v3.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			args.dvo_v3.ucDVOConfig = 0; /* XXX */
			अवरोध;
		हाल 4:
			/* DCE8 */
			args.dvo_v4.ucAction = action;
			args.dvo_v4.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			args.dvo_v4.ucDVOConfig = 0; /* XXX */
			args.dvo_v4.ucBitPerColor = radeon_atom_get_bpc(encoder);
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

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

जोड़ lvds_encoder_control अणु
	LVDS_ENCODER_CONTROL_PS_ALLOCATION    v1;
	LVDS_ENCODER_CONTROL_PS_ALLOCATION_V2 v2;
पूर्ण;

व्योम
atombios_digital_setup(काष्ठा drm_encoder *encoder, पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	जोड़ lvds_encoder_control args;
	पूर्णांक index = 0;
	पूर्णांक hdmi_detected = 0;
	uपूर्णांक8_t frev, crev;

	अगर (!dig)
		वापस;

	अगर (atombios_get_encoder_mode(encoder) == ATOM_ENCODER_MODE_HDMI)
		hdmi_detected = 1;

	स_रखो(&args, 0, माप(args));

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
		index = GetIndexIntoMasterTable(COMMAND, LVDSEncoderControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
		index = GetIndexIntoMasterTable(COMMAND, TMDS1EncoderControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, LVDSEncoderControl);
		अन्यथा
			index = GetIndexIntoMasterTable(COMMAND, TMDS2EncoderControl);
		अवरोध;
	पूर्ण

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
	हाल 2:
		चयन (crev) अणु
		हाल 1:
			args.v1.ucMisc = 0;
			args.v1.ucAction = action;
			अगर (hdmi_detected)
				args.v1.ucMisc |= PANEL_ENCODER_MISC_HDMI_TYPE;
			args.v1.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
				अगर (dig->lcd_misc & ATOM_PANEL_MISC_DUAL)
					args.v1.ucMisc |= PANEL_ENCODER_MISC_DUAL;
				अगर (dig->lcd_misc & ATOM_PANEL_MISC_888RGB)
					args.v1.ucMisc |= ATOM_PANEL_MISC_888RGB;
			पूर्ण अन्यथा अणु
				अगर (dig->linkb)
					args.v1.ucMisc |= PANEL_ENCODER_MISC_TMDS_LINKB;
				अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
					args.v1.ucMisc |= PANEL_ENCODER_MISC_DUAL;
				/*अगर (pScrn->rgbBits == 8) */
				args.v1.ucMisc |= ATOM_PANEL_MISC_888RGB;
			पूर्ण
			अवरोध;
		हाल 2:
		हाल 3:
			args.v2.ucMisc = 0;
			args.v2.ucAction = action;
			अगर (crev == 3) अणु
				अगर (dig->coherent_mode)
					args.v2.ucMisc |= PANEL_ENCODER_MISC_COHERENT;
			पूर्ण
			अगर (hdmi_detected)
				args.v2.ucMisc |= PANEL_ENCODER_MISC_HDMI_TYPE;
			args.v2.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			args.v2.ucTruncate = 0;
			args.v2.ucSpatial = 0;
			args.v2.ucTemporal = 0;
			args.v2.ucFRC = 0;
			अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
				अगर (dig->lcd_misc & ATOM_PANEL_MISC_DUAL)
					args.v2.ucMisc |= PANEL_ENCODER_MISC_DUAL;
				अगर (dig->lcd_misc & ATOM_PANEL_MISC_SPATIAL) अणु
					args.v2.ucSpatial = PANEL_ENCODER_SPATIAL_DITHER_EN;
					अगर (dig->lcd_misc & ATOM_PANEL_MISC_888RGB)
						args.v2.ucSpatial |= PANEL_ENCODER_SPATIAL_DITHER_DEPTH;
				पूर्ण
				अगर (dig->lcd_misc & ATOM_PANEL_MISC_TEMPORAL) अणु
					args.v2.ucTemporal = PANEL_ENCODER_TEMPORAL_DITHER_EN;
					अगर (dig->lcd_misc & ATOM_PANEL_MISC_888RGB)
						args.v2.ucTemporal |= PANEL_ENCODER_TEMPORAL_DITHER_DEPTH;
					अगर (((dig->lcd_misc >> ATOM_PANEL_MISC_GREY_LEVEL_SHIFT) & 0x3) == 2)
						args.v2.ucTemporal |= PANEL_ENCODER_TEMPORAL_LEVEL_4;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (dig->linkb)
					args.v2.ucMisc |= PANEL_ENCODER_MISC_TMDS_LINKB;
				अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
					args.v2.ucMisc |= PANEL_ENCODER_MISC_DUAL;
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

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

पूर्णांक
atombios_get_encoder_mode(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_connector *connector;
	काष्ठा radeon_connector *radeon_connector;
	काष्ठा radeon_connector_atom_dig *dig_connector;
	काष्ठा radeon_encoder_atom_dig *dig_enc;

	अगर (radeon_encoder_is_digital(encoder)) अणु
		dig_enc = radeon_encoder->enc_priv;
		अगर (dig_enc->active_mst_links)
			वापस ATOM_ENCODER_MODE_DP_MST;
	पूर्ण
	अगर (radeon_encoder->is_mst_encoder || radeon_encoder->offset)
		वापस ATOM_ENCODER_MODE_DP_MST;
	/* dp bridges are always DP */
	अगर (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE)
		वापस ATOM_ENCODER_MODE_DP;

	/* DVO is always DVO */
	अगर ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DVO1) ||
	    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1))
		वापस ATOM_ENCODER_MODE_DVO;

	connector = radeon_get_connector_क्रम_encoder(encoder);
	/* अगर we करोn't have an active device yet, just use one of
	 * the connectors tied to the encoder.
	 */
	अगर (!connector)
		connector = radeon_get_connector_क्रम_encoder_init(encoder);
	radeon_connector = to_radeon_connector(connector);

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_DVII:
	हाल DRM_MODE_CONNECTOR_HDMIB: /* HDMI-B is basically DL-DVI; analog works fine */
		अगर (radeon_audio != 0) अणु
			अगर (radeon_connector->use_digital &&
			    (radeon_connector->audio == RADEON_AUDIO_ENABLE))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (radeon_connector->use_digital)
				वापस ATOM_ENCODER_MODE_DVI;
			अन्यथा
				वापस ATOM_ENCODER_MODE_CRT;
		पूर्ण अन्यथा अगर (radeon_connector->use_digital) अणु
			वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण अन्यथा अणु
			वापस ATOM_ENCODER_MODE_CRT;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DVID:
	हाल DRM_MODE_CONNECTOR_HDMIA:
	शेष:
		अगर (radeon_audio != 0) अणु
			अगर (radeon_connector->audio == RADEON_AUDIO_ENABLE)
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा
				वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण अन्यथा अणु
			वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_LVDS:
		वापस ATOM_ENCODER_MODE_LVDS;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_DisplayPort:
		dig_connector = radeon_connector->con_priv;
		अगर ((dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_DISPLAYPORT) ||
		    (dig_connector->dp_sink_type == CONNECTOR_OBJECT_ID_eDP)) अणु
			अगर (radeon_audio != 0 &&
			    drm_detect_monitor_audio(radeon_connector_edid(connector)) &&
			    ASIC_IS_DCE4(rdev) && !ASIC_IS_DCE5(rdev))
				वापस ATOM_ENCODER_MODE_DP_AUDIO;
			वापस ATOM_ENCODER_MODE_DP;
		पूर्ण अन्यथा अगर (radeon_audio != 0) अणु
			अगर (radeon_connector->audio == RADEON_AUDIO_ENABLE)
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा अगर (drm_detect_hdmi_monitor(radeon_connector_edid(connector)) &&
				 (radeon_connector->audio == RADEON_AUDIO_AUTO))
				वापस ATOM_ENCODER_MODE_HDMI;
			अन्यथा
				वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण अन्यथा अणु
			वापस ATOM_ENCODER_MODE_DVI;
		पूर्ण
		अवरोध;
	हाल DRM_MODE_CONNECTOR_eDP:
		अगर (radeon_audio != 0 &&
		    drm_detect_monitor_audio(radeon_connector_edid(connector)) &&
		    ASIC_IS_DCE4(rdev) && !ASIC_IS_DCE5(rdev))
			वापस ATOM_ENCODER_MODE_DP_AUDIO;
		वापस ATOM_ENCODER_MODE_DP;
	हाल DRM_MODE_CONNECTOR_DVIA:
	हाल DRM_MODE_CONNECTOR_VGA:
		वापस ATOM_ENCODER_MODE_CRT;
		अवरोध;
	हाल DRM_MODE_CONNECTOR_Composite:
	हाल DRM_MODE_CONNECTOR_SVIDEO:
	हाल DRM_MODE_CONNECTOR_9PinDIN:
		/* fix me */
		वापस ATOM_ENCODER_MODE_TV;
		/*वापस ATOM_ENCODER_MODE_CV;*/
		अवरोध;
	पूर्ण
पूर्ण

/*
 * DIG Encoder/Transmitter Setup
 *
 * DCE 3.0/3.1
 * - 2 DIG transmitter blocks. UNIPHY (links A and B) and LVTMA.
 * Supports up to 3 digital outमाला_दो
 * - 2 DIG encoder blocks.
 * DIG1 can drive UNIPHY link A or link B
 * DIG2 can drive UNIPHY link B or LVTMA
 *
 * DCE 3.2
 * - 3 DIG transmitter blocks. UNIPHY0/1/2 (links A and B).
 * Supports up to 5 digital outमाला_दो
 * - 2 DIG encoder blocks.
 * DIG1/2 can drive UNIPHY0/1/2 link A or link B
 *
 * DCE 4.0/5.0/6.0
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
 * DCE 4.1
 * - 3 DIG transmitter blocks UNIPHY0/1/2 (links A and B).
 * Supports up to 6 digital outमाला_दो
 * - 2 DIG encoder blocks.
 * llano
 * DIG1/2 can drive UNIPHY0/1/2 link A or link B
 * ontario
 * DIG1 drives UNIPHY0/1/2 link A
 * DIG2 drives UNIPHY0/1/2 link B
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
पूर्ण;

व्योम
atombios_dig_encoder_setup2(काष्ठा drm_encoder *encoder, पूर्णांक action, पूर्णांक panel_mode, पूर्णांक enc_override)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	जोड़ dig_encoder_control args;
	पूर्णांक index = 0;
	uपूर्णांक8_t frev, crev;
	पूर्णांक dp_घड़ी = 0;
	पूर्णांक dp_lane_count = 0;
	पूर्णांक hpd_id = RADEON_HPD_NONE;

	अगर (connector) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		काष्ठा radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;

		dp_घड़ी = dig_connector->dp_घड़ी;
		dp_lane_count = dig_connector->dp_lane_count;
		hpd_id = radeon_connector->hpd.hpd;
	पूर्ण

	/* no dig encoder asचिन्हित */
	अगर (dig->dig_encoder == -1)
		वापस;

	स_रखो(&args, 0, माप(args));

	अगर (ASIC_IS_DCE4(rdev))
		index = GetIndexIntoMasterTable(COMMAND, DIGxEncoderControl);
	अन्यथा अणु
		अगर (dig->dig_encoder)
			index = GetIndexIntoMasterTable(COMMAND, DIG2EncoderControl);
		अन्यथा
			index = GetIndexIntoMasterTable(COMMAND, DIG1EncoderControl);
	पूर्ण

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
			args.v1.ucAction = action;
			args.v1.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			अगर (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			अन्यथा
				args.v1.ucEncoderMode = atombios_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode))
				args.v1.ucLaneNum = dp_lane_count;
			अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
				args.v1.ucLaneNum = 8;
			अन्यथा
				args.v1.ucLaneNum = 4;

			चयन (radeon_encoder->encoder_id) अणु
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

			अगर (ENCODER_MODE_IS_DP(args.v1.ucEncoderMode) && (dp_घड़ी == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ;

			अवरोध;
		हाल 2:
		हाल 3:
			args.v3.ucAction = action;
			args.v3.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			अगर (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v3.ucPanelMode = panel_mode;
			अन्यथा
				args.v3.ucEncoderMode = atombios_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode))
				args.v3.ucLaneNum = dp_lane_count;
			अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
				args.v3.ucLaneNum = 8;
			अन्यथा
				args.v3.ucLaneNum = 4;

			अगर (ENCODER_MODE_IS_DP(args.v3.ucEncoderMode) && (dp_घड़ी == 270000))
				args.v1.ucConfig |= ATOM_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ;
			अगर (enc_override != -1)
				args.v3.acConfig.ucDigSel = enc_override;
			अन्यथा
				args.v3.acConfig.ucDigSel = dig->dig_encoder;
			args.v3.ucBitPerColor = radeon_atom_get_bpc(encoder);
			अवरोध;
		हाल 4:
			args.v4.ucAction = action;
			args.v4.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			अगर (action == ATOM_ENCODER_CMD_SETUP_PANEL_MODE)
				args.v4.ucPanelMode = panel_mode;
			अन्यथा
				args.v4.ucEncoderMode = atombios_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v4.ucEncoderMode))
				args.v4.ucLaneNum = dp_lane_count;
			अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
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

			अगर (enc_override != -1)
				args.v4.acConfig.ucDigSel = enc_override;
			अन्यथा
				args.v4.acConfig.ucDigSel = dig->dig_encoder;
			args.v4.ucBitPerColor = radeon_atom_get_bpc(encoder);
			अगर (hpd_id == RADEON_HPD_NONE)
				args.v4.ucHPD_ID = 0;
			अन्यथा
				args.v4.ucHPD_ID = hpd_id + 1;
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

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

पूर्ण

व्योम
atombios_dig_encoder_setup(काष्ठा drm_encoder *encoder, पूर्णांक action, पूर्णांक panel_mode)
अणु
	atombios_dig_encoder_setup2(encoder, action, panel_mode, -1);
पूर्ण

जोड़ dig_transmitter_control अणु
	DIG_TRANSMITTER_CONTROL_PS_ALLOCATION v1;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V2 v2;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V3 v3;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V4 v4;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V1_5 v5;
पूर्ण;

व्योम
atombios_dig_transmitter_setup2(काष्ठा drm_encoder *encoder, पूर्णांक action, uपूर्णांक8_t lane_num, uपूर्णांक8_t lane_set, पूर्णांक fe)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
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
	पूर्णांक hpd_id = RADEON_HPD_NONE;

	अगर (action == ATOM_TRANSMITTER_ACTION_INIT) अणु
		connector = radeon_get_connector_क्रम_encoder_init(encoder);
		/* just needed to aव्योम bailing in the encoder check.  the encoder
		 * isn't used क्रम init
		 */
		dig_encoder = 0;
	पूर्ण अन्यथा
		connector = radeon_get_connector_क्रम_encoder(encoder);

	अगर (connector) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		काष्ठा radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;

		hpd_id = radeon_connector->hpd.hpd;
		dp_घड़ी = dig_connector->dp_घड़ी;
		dp_lane_count = dig_connector->dp_lane_count;
		connector_object_id =
			(radeon_connector->connector_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
		igp_lane_info = dig_connector->igp_lane_info;
	पूर्ण

	अगर (encoder->crtc) अणु
		काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
		pll_id = radeon_crtc->pll_id;
	पूर्ण

	/* no dig encoder asचिन्हित */
	अगर (dig_encoder == -1)
		वापस;

	अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)))
		is_dp = true;

	स_रखो(&args, 0, माप(args));

	चयन (radeon_encoder->encoder_id) अणु
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

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
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
				अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
					args.v1.usPixelClock = cpu_to_le16((radeon_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v1.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			पूर्ण

			args.v1.ucConfig = ATOM_TRANSMITTER_CONFIG_CLKSRC_PPLL;

			अगर (dig_encoder)
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_DIG2_ENCODER;
			अन्यथा
				args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_DIG1_ENCODER;

			अगर ((rdev->flags & RADEON_IS_IGP) &&
			    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_UNIPHY)) अणु
				अगर (is_dp ||
				    !radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी)) अणु
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
			अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v1.ucConfig |= ATOM_TRANSMITTER_CONFIG_COHERENT;
				अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
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
				अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
					args.v2.usPixelClock = cpu_to_le16((radeon_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v2.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			पूर्ण

			args.v2.acConfig.ucEncoderSel = dig_encoder;
			अगर (dig->linkb)
				args.v2.acConfig.ucLinkSel = 1;

			चयन (radeon_encoder->encoder_id) अणु
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
			पूर्ण अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v2.acConfig.fCoherentMode = 1;
				अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
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
				अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
					args.v3.usPixelClock = cpu_to_le16((radeon_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v3.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			पूर्ण

			अगर (is_dp)
				args.v3.ucLaneNum = dp_lane_count;
			अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
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
			अगर (is_dp && rdev->घड़ी.dp_extclk)
				args.v3.acConfig.ucRefClkSource = 2; /* बाह्यal src */
			अन्यथा
				args.v3.acConfig.ucRefClkSource = pll_id;

			चयन (radeon_encoder->encoder_id) अणु
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
			अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v3.acConfig.fCoherentMode = 1;
				अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
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
				अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
					args.v4.usPixelClock = cpu_to_le16((radeon_encoder->pixel_घड़ी / 2) / 10);
				अन्यथा
					args.v4.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			पूर्ण

			अगर (is_dp)
				args.v4.ucLaneNum = dp_lane_count;
			अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
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
				अगर (rdev->घड़ी.dp_extclk)
					args.v4.acConfig.ucRefClkSource = ENCODER_REFCLK_SRC_EXTCLK;
				अन्यथा
					args.v4.acConfig.ucRefClkSource = ENCODER_REFCLK_SRC_DCPLL;
			पूर्ण अन्यथा
				args.v4.acConfig.ucRefClkSource = pll_id;

			चयन (radeon_encoder->encoder_id) अणु
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
			अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v4.acConfig.fCoherentMode = 1;
				अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
					args.v4.acConfig.fDualLinkConnector = 1;
			पूर्ण
			अवरोध;
		हाल 5:
			args.v5.ucAction = action;
			अगर (is_dp)
				args.v5.usSymClock = cpu_to_le16(dp_घड़ी / 10);
			अन्यथा
				args.v5.usSymClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);

			चयन (radeon_encoder->encoder_id) अणु
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
			अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
				args.v5.ucLaneNum = 8;
			अन्यथा
				args.v5.ucLaneNum = 4;
			args.v5.ucConnObjId = connector_object_id;
			args.v5.ucDigMode = atombios_get_encoder_mode(encoder);

			अगर (is_dp && rdev->घड़ी.dp_extclk)
				args.v5.asConfig.ucPhyClkSrcId = ENCODER_REFCLK_SRC_EXTCLK;
			अन्यथा
				args.v5.asConfig.ucPhyClkSrcId = pll_id;

			अगर (is_dp)
				args.v5.asConfig.ucCoherentMode = 1; /* DP requires coherent */
			अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_DFP_SUPPORT)) अणु
				अगर (dig->coherent_mode)
					args.v5.asConfig.ucCoherentMode = 1;
			पूर्ण
			अगर (hpd_id == RADEON_HPD_NONE)
				args.v5.asConfig.ucHPDSel = 0;
			अन्यथा
				args.v5.asConfig.ucHPDSel = hpd_id + 1;
			args.v5.ucDigEncoderSel = (fe != -1) ? (1 << fe) : (1 << dig_encoder);
			args.v5.ucDPLaneSet = lane_set;
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

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

व्योम
atombios_dig_transmitter_setup(काष्ठा drm_encoder *encoder, पूर्णांक action, uपूर्णांक8_t lane_num, uपूर्णांक8_t lane_set)
अणु
	atombios_dig_transmitter_setup2(encoder, action, lane_num, lane_set, -1);
पूर्ण

bool
atombios_set_edp_panel_घातer(काष्ठा drm_connector *connector, पूर्णांक action)
अणु
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा drm_device *dev = radeon_connector->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	जोड़ dig_transmitter_control args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, UNIPHYTransmitterControl);
	uपूर्णांक8_t frev, crev;

	अगर (connector->connector_type != DRM_MODE_CONNECTOR_eDP)
		जाओ करोne;

	अगर (!ASIC_IS_DCE4(rdev))
		जाओ करोne;

	अगर ((action != ATOM_TRANSMITTER_ACTION_POWER_ON) &&
	    (action != ATOM_TRANSMITTER_ACTION_POWER_OFF))
		जाओ करोne;

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		जाओ करोne;

	स_रखो(&args, 0, माप(args));

	args.v1.ucAction = action;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	/* रुको क्रम the panel to घातer up */
	अगर (action == ATOM_TRANSMITTER_ACTION_POWER_ON) अणु
		पूर्णांक i;

		क्रम (i = 0; i < 300; i++) अणु
			अगर (radeon_hpd_sense(rdev, radeon_connector->hpd.hpd))
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
atombios_बाह्यal_encoder_setup(काष्ठा drm_encoder *encoder,
				काष्ठा drm_encoder *ext_encoder,
				पूर्णांक action)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder *ext_radeon_encoder = to_radeon_encoder(ext_encoder);
	जोड़ बाह्यal_encoder_control args;
	काष्ठा drm_connector *connector;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, ExternalEncoderControl);
	u8 frev, crev;
	पूर्णांक dp_घड़ी = 0;
	पूर्णांक dp_lane_count = 0;
	पूर्णांक connector_object_id = 0;
	u32 ext_क्रमागत = (ext_radeon_encoder->encoder_क्रमागत & ENUM_ID_MASK) >> ENUM_ID_SHIFT;

	अगर (action == EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT)
		connector = radeon_get_connector_क्रम_encoder_init(encoder);
	अन्यथा
		connector = radeon_get_connector_क्रम_encoder(encoder);

	अगर (connector) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
		काष्ठा radeon_connector_atom_dig *dig_connector =
			radeon_connector->con_priv;

		dp_घड़ी = dig_connector->dp_घड़ी;
		dp_lane_count = dig_connector->dp_lane_count;
		connector_object_id =
			(radeon_connector->connector_object_id & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	पूर्ण

	स_रखो(&args, 0, माप(args));

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
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
			args.v1.sDigEncoder.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			args.v1.sDigEncoder.ucEncoderMode = atombios_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v1.sDigEncoder.ucEncoderMode)) अणु
				अगर (dp_घड़ी == 270000)
					args.v1.sDigEncoder.ucConfig |= ATOM_ENCODER_CONFIG_DPLINKRATE_2_70GHZ;
				args.v1.sDigEncoder.ucLaneNum = dp_lane_count;
			पूर्ण अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
				args.v1.sDigEncoder.ucLaneNum = 8;
			अन्यथा
				args.v1.sDigEncoder.ucLaneNum = 4;
			अवरोध;
		हाल 3:
			args.v3.sExtEncoder.ucAction = action;
			अगर (action == EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT)
				args.v3.sExtEncoder.usConnectorId = cpu_to_le16(connector_object_id);
			अन्यथा
				args.v3.sExtEncoder.usPixelClock = cpu_to_le16(radeon_encoder->pixel_घड़ी / 10);
			args.v3.sExtEncoder.ucEncoderMode = atombios_get_encoder_mode(encoder);

			अगर (ENCODER_MODE_IS_DP(args.v3.sExtEncoder.ucEncoderMode)) अणु
				अगर (dp_घड़ी == 270000)
					args.v3.sExtEncoder.ucConfig |= EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ;
				अन्यथा अगर (dp_घड़ी == 540000)
					args.v3.sExtEncoder.ucConfig |= EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_5_40GHZ;
				args.v3.sExtEncoder.ucLaneNum = dp_lane_count;
			पूर्ण अन्यथा अगर (radeon_dig_monitor_is_duallink(encoder, radeon_encoder->pixel_घड़ी))
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
			args.v3.sExtEncoder.ucBitPerColor = radeon_atom_get_bpc(encoder);
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
	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम
atombios_yuv_setup(काष्ठा drm_encoder *encoder, bool enable)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	ENABLE_YUV_PS_ALLOCATION args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, EnableYUV);
	uपूर्णांक32_t temp, reg;

	स_रखो(&args, 0, माप(args));

	अगर (rdev->family >= CHIP_R600)
		reg = R600_BIOS_3_SCRATCH;
	अन्यथा
		reg = RADEON_BIOS_3_SCRATCH;

	/* XXX: fix up scratch reg handling */
	temp = RREG32(reg);
	अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
		WREG32(reg, (ATOM_S3_TV1_ACTIVE |
			     (radeon_crtc->crtc_id << 18)));
	अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
		WREG32(reg, (ATOM_S3_CV_ACTIVE | (radeon_crtc->crtc_id << 24)));
	अन्यथा
		WREG32(reg, 0);

	अगर (enable)
		args.ucEnable = ATOM_ENABLE;
	args.ucCRTC = radeon_crtc->crtc_id;

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	WREG32(reg, temp);
पूर्ण

अटल व्योम
radeon_atom_encoder_dpms_avivo(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	DISPLAY_DEVICE_OUTPUT_CONTROL_PS_ALLOCATION args;
	पूर्णांक index = 0;

	स_रखो(&args, 0, माप(args));

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
		index = GetIndexIntoMasterTable(COMMAND, TMDSAOutputControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		index = GetIndexIntoMasterTable(COMMAND, DVOOutputControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
		index = GetIndexIntoMasterTable(COMMAND, LCD1OutputControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, LCD1OutputControl);
		अन्यथा
			index = GetIndexIntoMasterTable(COMMAND, LVTMAOutputControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, TV1OutputControl);
		अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, CV1OutputControl);
		अन्यथा
			index = GetIndexIntoMasterTable(COMMAND, DAC1OutputControl);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, TV1OutputControl);
		अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
			index = GetIndexIntoMasterTable(COMMAND, CV1OutputControl);
		अन्यथा
			index = GetIndexIntoMasterTable(COMMAND, DAC2OutputControl);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		args.ucAction = ATOM_ENABLE;
		/* workaround क्रम DVOOutputControl on some RS690 प्रणालीs */
		अगर (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DDI) अणु
			u32 reg = RREG32(RADEON_BIOS_3_SCRATCH);
			WREG32(RADEON_BIOS_3_SCRATCH, reg & ~ATOM_S3_DFP2I_ACTIVE);
			atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
			WREG32(RADEON_BIOS_3_SCRATCH, reg);
		पूर्ण अन्यथा
			atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
			अगर (rdev->mode_info.bl_encoder) अणु
				काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;

				atombios_set_backlight_level(radeon_encoder, dig->backlight_level);
			पूर्ण अन्यथा अणु
				args.ucAction = ATOM_LCD_BLON;
				atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		args.ucAction = ATOM_DISABLE;
		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
			args.ucAction = ATOM_LCD_BLOFF;
			atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
radeon_atom_encoder_dpms_dig(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_encoder *ext_encoder = radeon_get_बाह्यal_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	काष्ठा radeon_connector *radeon_connector = शून्य;
	काष्ठा radeon_connector_atom_dig *radeon_dig_connector = शून्य;
	bool travis_quirk = false;

	अगर (connector) अणु
		radeon_connector = to_radeon_connector(connector);
		radeon_dig_connector = radeon_connector->con_priv;
		अगर ((radeon_connector_encoder_get_dp_bridge_encoder_id(connector) ==
		     ENCODER_OBJECT_ID_TRAVIS) &&
		    (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
		    !ASIC_IS_DCE5(rdev))
			travis_quirk = true;
	पूर्ण

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		अगर (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE5(rdev)) अणु
			अगर (!connector)
				dig->panel_mode = DP_PANEL_MODE_EXTERNAL_DP_MODE;
			अन्यथा
				dig->panel_mode = radeon_dp_get_panel_mode(encoder, connector);

			/* setup and enable the encoder */
			atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_SETUP, 0);
			atombios_dig_encoder_setup(encoder,
						   ATOM_ENCODER_CMD_SETUP_PANEL_MODE,
						   dig->panel_mode);
			अगर (ext_encoder) अणु
				अगर (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE61(rdev))
					atombios_बाह्यal_encoder_setup(encoder, ext_encoder,
									EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP);
			पूर्ण
		पूर्ण अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
			/* setup and enable the encoder */
			atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_SETUP, 0);
		पूर्ण अन्यथा अणु
			/* setup and enable the encoder and transmitter */
			atombios_dig_encoder_setup(encoder, ATOM_ENABLE, 0);
			atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_SETUP, 0, 0);
		पूर्ण
		अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector) अणु
			अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
				atombios_set_edp_panel_घातer(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_ON);
				radeon_dig_connector->edp_on = true;
			पूर्ण
		पूर्ण
		/* enable the transmitter */
		atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_ENABLE, 0, 0);
		अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector) अणु
			/* DP_SET_POWER_D0 is set in radeon_dp_link_train */
			radeon_dp_link_train(encoder, connector);
			अगर (ASIC_IS_DCE4(rdev))
				atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_DP_VIDEO_ON, 0);
		पूर्ण
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
			अगर (rdev->mode_info.bl_encoder)
				atombios_set_backlight_level(radeon_encoder, dig->backlight_level);
			अन्यथा
				atombios_dig_transmitter_setup(encoder,
							       ATOM_TRANSMITTER_ACTION_LCD_BLON, 0, 0);
		पूर्ण
		अगर (ext_encoder)
			atombios_बाह्यal_encoder_setup(encoder, ext_encoder, ATOM_ENABLE);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:

		/* करोn't घातer off encoders with active MST links */
		अगर (dig->active_mst_links)
			वापस;

		अगर (ASIC_IS_DCE4(rdev)) अणु
			अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector)
				atombios_dig_encoder_setup(encoder, ATOM_ENCODER_CMD_DP_VIDEO_OFF, 0);
		पूर्ण
		अगर (ext_encoder)
			atombios_बाह्यal_encoder_setup(encoder, ext_encoder, ATOM_DISABLE);
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			atombios_dig_transmitter_setup(encoder,
						       ATOM_TRANSMITTER_ACTION_LCD_BLOFF, 0, 0);

		अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) &&
		    connector && !travis_quirk)
			radeon_dp_set_rx_घातer_state(connector, DP_SET_POWER_D3);
		अगर (ASIC_IS_DCE4(rdev)) अणु
			/* disable the transmitter */
			atombios_dig_transmitter_setup(encoder,
						       ATOM_TRANSMITTER_ACTION_DISABLE, 0, 0);
		पूर्ण अन्यथा अणु
			/* disable the encoder and transmitter */
			atombios_dig_transmitter_setup(encoder,
						       ATOM_TRANSMITTER_ACTION_DISABLE, 0, 0);
			atombios_dig_encoder_setup(encoder, ATOM_DISABLE, 0);
		पूर्ण
		अगर (ENCODER_MODE_IS_DP(atombios_get_encoder_mode(encoder)) && connector) अणु
			अगर (travis_quirk)
				radeon_dp_set_rx_घातer_state(connector, DP_SET_POWER_D3);
			अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP) अणु
				atombios_set_edp_panel_घातer(connector,
							     ATOM_TRANSMITTER_ACTION_POWER_OFF);
				radeon_dig_connector->edp_on = false;
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
radeon_atom_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	पूर्णांक encoder_mode = atombios_get_encoder_mode(encoder);

	DRM_DEBUG_KMS("encoder dpms %d to mode %d, devices %08x, active_devices %08x\n",
		  radeon_encoder->encoder_id, mode, radeon_encoder->devices,
		  radeon_encoder->active_device);

	अगर ((radeon_audio != 0) &&
	    ((encoder_mode == ATOM_ENCODER_MODE_HDMI) ||
	     ENCODER_MODE_IS_DP(encoder_mode)))
		radeon_audio_dpms(encoder, mode);

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		radeon_atom_encoder_dpms_avivo(encoder, mode);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		radeon_atom_encoder_dpms_dig(encoder, mode);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		अगर (ASIC_IS_DCE5(rdev)) अणु
			चयन (mode) अणु
			हाल DRM_MODE_DPMS_ON:
				atombios_dvo_setup(encoder, ATOM_ENABLE);
				अवरोध;
			हाल DRM_MODE_DPMS_STANDBY:
			हाल DRM_MODE_DPMS_SUSPEND:
			हाल DRM_MODE_DPMS_OFF:
				atombios_dvo_setup(encoder, ATOM_DISABLE);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ASIC_IS_DCE3(rdev))
			radeon_atom_encoder_dpms_dig(encoder, mode);
		अन्यथा
			radeon_atom_encoder_dpms_avivo(encoder, mode);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
		अगर (ASIC_IS_DCE5(rdev)) अणु
			चयन (mode) अणु
			हाल DRM_MODE_DPMS_ON:
				atombios_dac_setup(encoder, ATOM_ENABLE);
				अवरोध;
			हाल DRM_MODE_DPMS_STANDBY:
			हाल DRM_MODE_DPMS_SUSPEND:
			हाल DRM_MODE_DPMS_OFF:
				atombios_dac_setup(encoder, ATOM_DISABLE);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा
			radeon_atom_encoder_dpms_avivo(encoder, mode);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	radeon_atombios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);

पूर्ण

जोड़ crtc_source_param अणु
	SELECT_CRTC_SOURCE_PS_ALLOCATION v1;
	SELECT_CRTC_SOURCE_PARAMETERS_V2 v2;
पूर्ण;

अटल व्योम
atombios_set_encoder_crtc_source(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	जोड़ crtc_source_param args;
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SelectCRTC_Source);
	uपूर्णांक8_t frev, crev;
	काष्ठा radeon_encoder_atom_dig *dig;

	स_रखो(&args, 0, माप(args));

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	चयन (frev) अणु
	हाल 1:
		चयन (crev) अणु
		हाल 1:
		शेष:
			अगर (ASIC_IS_AVIVO(rdev))
				args.v1.ucCRTC = radeon_crtc->crtc_id;
			अन्यथा अणु
				अगर (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DAC1)
					args.v1.ucCRTC = radeon_crtc->crtc_id;
				अन्यथा
					args.v1.ucCRTC = radeon_crtc->crtc_id << 2;
			पूर्ण
			चयन (radeon_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
				args.v1.ucDevice = ATOM_DEVICE_DFP1_INDEX;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
			हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
				अगर (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT)
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
				अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_TV1_INDEX;
				अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_CV_INDEX;
				अन्यथा
					args.v1.ucDevice = ATOM_DEVICE_CRT1_INDEX;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
				अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_TV1_INDEX;
				अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v1.ucDevice = ATOM_DEVICE_CV_INDEX;
				अन्यथा
					args.v1.ucDevice = ATOM_DEVICE_CRT2_INDEX;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल 2:
			args.v2.ucCRTC = radeon_crtc->crtc_id;
			अगर (radeon_encoder_get_dp_bridge_encoder_id(encoder) != ENCODER_OBJECT_ID_NONE) अणु
				काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);

				अगर (connector->connector_type == DRM_MODE_CONNECTOR_LVDS)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
				अन्यथा अगर (connector->connector_type == DRM_MODE_CONNECTOR_VGA)
					args.v2.ucEncodeMode = ATOM_ENCODER_MODE_CRT;
				अन्यथा
					args.v2.ucEncodeMode = atombios_get_encoder_mode(encoder);
			पूर्ण अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
				args.v2.ucEncodeMode = ATOM_ENCODER_MODE_LVDS;
			पूर्ण अन्यथा अणु
				args.v2.ucEncodeMode = atombios_get_encoder_mode(encoder);
			पूर्ण
			चयन (radeon_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
				dig = radeon_encoder->enc_priv;
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
				अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा
					args.v2.ucEncoderID = ASIC_INT_DAC1_ENCODER_ID;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
				अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT))
					args.v2.ucEncoderID = ASIC_INT_TV_ENCODER_ID;
				अन्यथा
					args.v2.ucEncoderID = ASIC_INT_DAC2_ENCODER_ID;
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		DRM_ERROR("Unknown table version: %d, %d\n", frev, crev);
		वापस;
	पूर्ण

	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

	/* update scratch regs with new routing */
	radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
पूर्ण

व्योम
atombios_set_mst_encoder_crtc_source(काष्ठा drm_encoder *encoder, पूर्णांक fe)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	पूर्णांक index = GetIndexIntoMasterTable(COMMAND, SelectCRTC_Source);
	uपूर्णांक8_t frev, crev;
	जोड़ crtc_source_param args;

	स_रखो(&args, 0, माप(args));

	अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
		वापस;

	अगर (frev != 1 && crev != 2)
		DRM_ERROR("Unknown table for MST %d, %d\n", frev, crev);

	args.v2.ucCRTC = radeon_crtc->crtc_id;
	args.v2.ucEncodeMode = ATOM_ENCODER_MODE_DP_MST;

	चयन (fe) अणु
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
	atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);
पूर्ण

अटल व्योम
atombios_apply_encoder_quirks(काष्ठा drm_encoder *encoder,
			      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);

	/* Funky macbooks */
	अगर ((rdev->pdev->device == 0x71C5) &&
	    (rdev->pdev->subप्रणाली_venकरोr == 0x106b) &&
	    (rdev->pdev->subप्रणाली_device == 0x0080)) अणु
		अगर (radeon_encoder->devices & ATOM_DEVICE_LCD1_SUPPORT) अणु
			uपूर्णांक32_t lvपंचांगa_bit_depth_control = RREG32(AVIVO_LVTMA_BIT_DEPTH_CONTROL);

			lvपंचांगa_bit_depth_control &= ~AVIVO_LVTMA_BIT_DEPTH_CONTROL_TRUNCATE_EN;
			lvपंचांगa_bit_depth_control &= ~AVIVO_LVTMA_BIT_DEPTH_CONTROL_SPATIAL_DITHER_EN;

			WREG32(AVIVO_LVTMA_BIT_DEPTH_CONTROL, lvपंचांगa_bit_depth_control);
		पूर्ण
	पूर्ण

	/* set scaler clears this on some chips */
	अगर (ASIC_IS_AVIVO(rdev) &&
	    (!(radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT)))) अणु
		अगर (ASIC_IS_DCE8(rdev)) अणु
			अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
				WREG32(CIK_LB_DATA_FORMAT + radeon_crtc->crtc_offset,
				       CIK_INTERLEAVE_EN);
			अन्यथा
				WREG32(CIK_LB_DATA_FORMAT + radeon_crtc->crtc_offset, 0);
		पूर्ण अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
			अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
				WREG32(EVERGREEN_DATA_FORMAT + radeon_crtc->crtc_offset,
				       EVERGREEN_INTERLEAVE_EN);
			अन्यथा
				WREG32(EVERGREEN_DATA_FORMAT + radeon_crtc->crtc_offset, 0);
		पूर्ण अन्यथा अणु
			अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
				WREG32(AVIVO_D1MODE_DATA_FORMAT + radeon_crtc->crtc_offset,
				       AVIVO_D1MODE_INTERLEAVE_EN);
			अन्यथा
				WREG32(AVIVO_D1MODE_DATA_FORMAT + radeon_crtc->crtc_offset, 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम radeon_atom_release_dig_encoder(काष्ठा radeon_device *rdev, पूर्णांक enc_idx)
अणु
	अगर (enc_idx < 0)
		वापस;
	rdev->mode_info.active_encoders &= ~(1 << enc_idx);
पूर्ण

पूर्णांक radeon_atom_pick_dig_encoder(काष्ठा drm_encoder *encoder, पूर्णांक fe_idx)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_encoder *test_encoder;
	काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
	uपूर्णांक32_t dig_enc_in_use = 0;
	पूर्णांक enc_idx = -1;

	अगर (fe_idx >= 0) अणु
		enc_idx = fe_idx;
		जाओ asचिन्हित;
	पूर्ण
	अगर (ASIC_IS_DCE6(rdev)) अणु
		/* DCE6 */
		चयन (radeon_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
			अगर (dig->linkb)
				enc_idx = 1;
			अन्यथा
				enc_idx = 0;
			अवरोध;
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
			अगर (dig->linkb)
				enc_idx = 3;
			अन्यथा
				enc_idx = 2;
			अवरोध;
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
			अगर (dig->linkb)
				enc_idx = 5;
			अन्यथा
				enc_idx = 4;
			अवरोध;
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
			enc_idx = 6;
			अवरोध;
		पूर्ण
		जाओ asचिन्हित;
	पूर्ण अन्यथा अगर (ASIC_IS_DCE4(rdev)) अणु
		/* DCE4/5 */
		अगर (ASIC_IS_DCE41(rdev) && !ASIC_IS_DCE61(rdev)) अणु
			/* ontario follows DCE4 */
			अगर (rdev->family == CHIP_PALM) अणु
				अगर (dig->linkb)
					enc_idx = 1;
				अन्यथा
					enc_idx = 0;
			पूर्ण अन्यथा
				/* llano follows DCE3.2 */
				enc_idx = radeon_crtc->crtc_id;
		पूर्ण अन्यथा अणु
			चयन (radeon_encoder->encoder_id) अणु
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
				अगर (dig->linkb)
					enc_idx = 1;
				अन्यथा
					enc_idx = 0;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
				अगर (dig->linkb)
					enc_idx = 3;
				अन्यथा
					enc_idx = 2;
				अवरोध;
			हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
				अगर (dig->linkb)
					enc_idx = 5;
				अन्यथा
					enc_idx = 4;
				अवरोध;
			पूर्ण
		पूर्ण
		जाओ asचिन्हित;
	पूर्ण

	/*
	 * On DCE32 any encoder can drive any block so usually just use crtc id,
	 * but Apple thinks dअगरferent at least on iMac10,1, so there use linkb,
	 * otherwise the पूर्णांकernal eDP panel will stay dark.
	 */
	अगर (ASIC_IS_DCE32(rdev)) अणु
		अगर (dmi_match(DMI_PRODUCT_NAME, "iMac10,1"))
			enc_idx = (dig->linkb) ? 1 : 0;
		अन्यथा
			enc_idx = radeon_crtc->crtc_id;

		जाओ asचिन्हित;
	पूर्ण

	/* on DCE3 - LVTMA can only be driven by DIGB */
	list_क्रम_each_entry(test_encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा radeon_encoder *radeon_test_encoder;

		अगर (encoder == test_encoder)
			जारी;

		अगर (!radeon_encoder_is_digital(test_encoder))
			जारी;

		radeon_test_encoder = to_radeon_encoder(test_encoder);
		dig = radeon_test_encoder->enc_priv;

		अगर (dig->dig_encoder >= 0)
			dig_enc_in_use |= (1 << dig->dig_encoder);
	पूर्ण

	अगर (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA) अणु
		अगर (dig_enc_in_use & 0x2)
			DRM_ERROR("LVDS required digital encoder 2 but it was in use - stealing\n");
		वापस 1;
	पूर्ण
	अगर (!(dig_enc_in_use & 1))
		वापस 0;
	वापस 1;

asचिन्हित:
	अगर (enc_idx == -1) अणु
		DRM_ERROR("Got encoder index incorrect - returning 0\n");
		वापस 0;
	पूर्ण
	अगर (rdev->mode_info.active_encoders & (1 << enc_idx))
		DRM_ERROR("chosen encoder in use %d\n", enc_idx);

	rdev->mode_info.active_encoders |= (1 << enc_idx);
	वापस enc_idx;
पूर्ण

/* This only needs to be called once at startup */
व्योम
radeon_atom_encoder_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा drm_device *dev = rdev->ddev;
	काष्ठा drm_encoder *encoder;

	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
		काष्ठा drm_encoder *ext_encoder = radeon_get_बाह्यal_encoder(encoder);

		चयन (radeon_encoder->encoder_id) अणु
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
		हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
			atombios_dig_transmitter_setup(encoder, ATOM_TRANSMITTER_ACTION_INIT, 0, 0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (ext_encoder && (ASIC_IS_DCE41(rdev) || ASIC_IS_DCE61(rdev)))
			atombios_बाह्यal_encoder_setup(encoder, ext_encoder,
							EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT);
	पूर्ण
पूर्ण

अटल व्योम
radeon_atom_encoder_mode_set(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);
	पूर्णांक encoder_mode;

	radeon_encoder->pixel_घड़ी = adjusted_mode->घड़ी;

	/* need to call this here rather than in prepare() since we need some crtc info */
	radeon_atom_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	अगर (ASIC_IS_AVIVO(rdev) && !ASIC_IS_DCE4(rdev)) अणु
		अगर (radeon_encoder->active_device & (ATOM_DEVICE_CV_SUPPORT | ATOM_DEVICE_TV_SUPPORT))
			atombios_yuv_setup(encoder, true);
		अन्यथा
			atombios_yuv_setup(encoder, false);
	पूर्ण

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		atombios_digital_setup(encoder, PANEL_ENCODER_ACTION_ENABLE);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		/* handled in dpms */
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
	हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		atombios_dvo_setup(encoder, ATOM_ENABLE);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		atombios_dac_setup(encoder, ATOM_ENABLE);
		अगर (radeon_encoder->devices & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT)) अणु
			अगर (radeon_encoder->active_device & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))
				atombios_tv_setup(encoder, ATOM_ENABLE);
			अन्यथा
				atombios_tv_setup(encoder, ATOM_DISABLE);
		पूर्ण
		अवरोध;
	पूर्ण

	atombios_apply_encoder_quirks(encoder, adjusted_mode);

	encoder_mode = atombios_get_encoder_mode(encoder);
	अगर (connector && (radeon_audio != 0) &&
	    ((encoder_mode == ATOM_ENCODER_MODE_HDMI) ||
	     ENCODER_MODE_IS_DP(encoder_mode)))
		radeon_audio_mode_set(encoder, adjusted_mode);
पूर्ण

अटल bool
atombios_dac_load_detect(काष्ठा drm_encoder *encoder, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

	अगर (radeon_encoder->devices & (ATOM_DEVICE_TV_SUPPORT |
				       ATOM_DEVICE_CV_SUPPORT |
				       ATOM_DEVICE_CRT_SUPPORT)) अणु
		DAC_LOAD_DETECTION_PS_ALLOCATION args;
		पूर्णांक index = GetIndexIntoMasterTable(COMMAND, DAC_LoadDetection);
		uपूर्णांक8_t frev, crev;

		स_रखो(&args, 0, माप(args));

		अगर (!atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev))
			वापस false;

		args.sDacload.ucMisc = 0;

		अगर ((radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_DAC1) ||
		    (radeon_encoder->encoder_id == ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1))
			args.sDacload.ucDacType = ATOM_DAC_A;
		अन्यथा
			args.sDacload.ucDacType = ATOM_DAC_B;

		अगर (radeon_connector->devices & ATOM_DEVICE_CRT1_SUPPORT)
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_CRT1_SUPPORT);
		अन्यथा अगर (radeon_connector->devices & ATOM_DEVICE_CRT2_SUPPORT)
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_CRT2_SUPPORT);
		अन्यथा अगर (radeon_connector->devices & ATOM_DEVICE_CV_SUPPORT) अणु
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_CV_SUPPORT);
			अगर (crev >= 3)
				args.sDacload.ucMisc = DAC_LOAD_MISC_YPrPb;
		पूर्ण अन्यथा अगर (radeon_connector->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
			args.sDacload.usDeviceID = cpu_to_le16(ATOM_DEVICE_TV1_SUPPORT);
			अगर (crev >= 3)
				args.sDacload.ucMisc = DAC_LOAD_MISC_YPrPb;
		पूर्ण

		atom_execute_table(rdev->mode_info.atom_context, index, (uपूर्णांक32_t *)&args);

		वापस true;
	पूर्ण अन्यथा
		वापस false;
पूर्ण

अटल क्रमागत drm_connector_status
radeon_atom_dac_detect(काष्ठा drm_encoder *encoder, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	uपूर्णांक32_t bios_0_scratch;

	अगर (!atombios_dac_load_detect(encoder, connector)) अणु
		DRM_DEBUG_KMS("detect returned false \n");
		वापस connector_status_unknown;
	पूर्ण

	अगर (rdev->family >= CHIP_R600)
		bios_0_scratch = RREG32(R600_BIOS_0_SCRATCH);
	अन्यथा
		bios_0_scratch = RREG32(RADEON_BIOS_0_SCRATCH);

	DRM_DEBUG_KMS("Bios 0 scratch %x %08x\n", bios_0_scratch, radeon_encoder->devices);
	अगर (radeon_connector->devices & ATOM_DEVICE_CRT1_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT1_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (radeon_connector->devices & ATOM_DEVICE_CRT2_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT2_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (radeon_connector->devices & ATOM_DEVICE_CV_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_CV_MASK|ATOM_S0_CV_MASK_A))
			वापस connector_status_connected;
	पूर्ण
	अगर (radeon_connector->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_TV1_COMPOSITE | ATOM_S0_TV1_COMPOSITE_A))
			वापस connector_status_connected; /* CTV */
		अन्यथा अगर (bios_0_scratch & (ATOM_S0_TV1_SVIDEO | ATOM_S0_TV1_SVIDEO_A))
			वापस connector_status_connected; /* STV */
	पूर्ण
	वापस connector_status_disconnected;
पूर्ण

अटल क्रमागत drm_connector_status
radeon_atom_dig_detect(काष्ठा drm_encoder *encoder, काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);
	काष्ठा drm_encoder *ext_encoder = radeon_get_बाह्यal_encoder(encoder);
	u32 bios_0_scratch;

	अगर (!ASIC_IS_DCE4(rdev))
		वापस connector_status_unknown;

	अगर (!ext_encoder)
		वापस connector_status_unknown;

	अगर ((radeon_connector->devices & ATOM_DEVICE_CRT_SUPPORT) == 0)
		वापस connector_status_unknown;

	/* load detect on the dp bridge */
	atombios_बाह्यal_encoder_setup(encoder, ext_encoder,
					EXTERNAL_ENCODER_ACTION_V3_DACLOAD_DETECTION);

	bios_0_scratch = RREG32(R600_BIOS_0_SCRATCH);

	DRM_DEBUG_KMS("Bios 0 scratch %x %08x\n", bios_0_scratch, radeon_encoder->devices);
	अगर (radeon_connector->devices & ATOM_DEVICE_CRT1_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT1_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (radeon_connector->devices & ATOM_DEVICE_CRT2_SUPPORT) अणु
		अगर (bios_0_scratch & ATOM_S0_CRT2_MASK)
			वापस connector_status_connected;
	पूर्ण
	अगर (radeon_connector->devices & ATOM_DEVICE_CV_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_CV_MASK|ATOM_S0_CV_MASK_A))
			वापस connector_status_connected;
	पूर्ण
	अगर (radeon_connector->devices & ATOM_DEVICE_TV1_SUPPORT) अणु
		अगर (bios_0_scratch & (ATOM_S0_TV1_COMPOSITE | ATOM_S0_TV1_COMPOSITE_A))
			वापस connector_status_connected; /* CTV */
		अन्यथा अगर (bios_0_scratch & (ATOM_S0_TV1_SVIDEO | ATOM_S0_TV1_SVIDEO_A))
			वापस connector_status_connected; /* STV */
	पूर्ण
	वापस connector_status_disconnected;
पूर्ण

व्योम
radeon_atom_ext_encoder_setup_ddc(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_encoder *ext_encoder = radeon_get_बाह्यal_encoder(encoder);

	अगर (ext_encoder)
		/* ddc_setup on the dp bridge */
		atombios_बाह्यal_encoder_setup(encoder, ext_encoder,
						EXTERNAL_ENCODER_ACTION_V3_DDC_SETUP);

पूर्ण

अटल व्योम radeon_atom_encoder_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा drm_connector *connector = radeon_get_connector_क्रम_encoder(encoder);

	अगर ((radeon_encoder->active_device &
	     (ATOM_DEVICE_DFP_SUPPORT | ATOM_DEVICE_LCD_SUPPORT)) ||
	    (radeon_encoder_get_dp_bridge_encoder_id(encoder) !=
	     ENCODER_OBJECT_ID_NONE)) अणु
		काष्ठा radeon_encoder_atom_dig *dig = radeon_encoder->enc_priv;
		अगर (dig) अणु
			अगर (dig->dig_encoder >= 0)
				radeon_atom_release_dig_encoder(rdev, dig->dig_encoder);
			dig->dig_encoder = radeon_atom_pick_dig_encoder(encoder, -1);
			अगर (radeon_encoder->active_device & ATOM_DEVICE_DFP_SUPPORT) अणु
				अगर (rdev->family >= CHIP_R600)
					dig->afmt = rdev->mode_info.afmt[dig->dig_encoder];
				अन्यथा
					/* RS600/690/740 have only 1 afmt block */
					dig->afmt = rdev->mode_info.afmt[0];
			पूर्ण
		पूर्ण
	पूर्ण

	radeon_atom_output_lock(encoder, true);

	अगर (connector) अणु
		काष्ठा radeon_connector *radeon_connector = to_radeon_connector(connector);

		/* select the घड़ी/data port अगर it uses a router */
		अगर (radeon_connector->router.cd_valid)
			radeon_router_select_cd_port(radeon_connector);

		/* turn eDP panel on क्रम mode set */
		अगर (connector->connector_type == DRM_MODE_CONNECTOR_eDP)
			atombios_set_edp_panel_घातer(connector,
						     ATOM_TRANSMITTER_ACTION_POWER_ON);
	पूर्ण

	/* this is needed क्रम the pll/ss setup to work correctly in some हालs */
	atombios_set_encoder_crtc_source(encoder);
	/* set up the FMT blocks */
	अगर (ASIC_IS_DCE8(rdev))
		dce8_program_fmt(encoder);
	अन्यथा अगर (ASIC_IS_DCE4(rdev))
		dce4_program_fmt(encoder);
	अन्यथा अगर (ASIC_IS_DCE3(rdev))
		dce3_program_fmt(encoder);
	अन्यथा अगर (ASIC_IS_AVIVO(rdev))
		avivo_program_fmt(encoder);
पूर्ण

अटल व्योम radeon_atom_encoder_commit(काष्ठा drm_encoder *encoder)
अणु
	/* need to call this here as we need the crtc set up */
	radeon_atom_encoder_dpms(encoder, DRM_MODE_DPMS_ON);
	radeon_atom_output_lock(encoder, false);
पूर्ण

अटल व्योम radeon_atom_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_atom_dig *dig;

	/* check क्रम pre-DCE3 cards with shared encoders;
	 * can't really use the links individually, so don't disable
	 * the encoder अगर it's in use by another connector
	 */
	अगर (!ASIC_IS_DCE3(rdev)) अणु
		काष्ठा drm_encoder *other_encoder;
		काष्ठा radeon_encoder *other_radeon_encoder;

		list_क्रम_each_entry(other_encoder, &dev->mode_config.encoder_list, head) अणु
			other_radeon_encoder = to_radeon_encoder(other_encoder);
			अगर ((radeon_encoder->encoder_id == other_radeon_encoder->encoder_id) &&
			    drm_helper_encoder_in_use(other_encoder))
				जाओ disable_करोne;
		पूर्ण
	पूर्ण

	radeon_atom_encoder_dpms(encoder, DRM_MODE_DPMS_OFF);

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		atombios_digital_setup(encoder, PANEL_ENCODER_ACTION_DISABLE);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
		/* handled in dpms */
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
	हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
		atombios_dvo_setup(encoder, ATOM_DISABLE);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		atombios_dac_setup(encoder, ATOM_DISABLE);
		अगर (radeon_encoder->devices & (ATOM_DEVICE_TV_SUPPORT | ATOM_DEVICE_CV_SUPPORT))
			atombios_tv_setup(encoder, ATOM_DISABLE);
		अवरोध;
	पूर्ण

disable_करोne:
	अगर (radeon_encoder_is_digital(encoder)) अणु
		अगर (atombios_get_encoder_mode(encoder) == ATOM_ENCODER_MODE_HDMI) अणु
			अगर (rdev->asic->display.hdmi_enable)
				radeon_hdmi_enable(rdev, encoder, false);
		पूर्ण
		अगर (atombios_get_encoder_mode(encoder) != ATOM_ENCODER_MODE_DP_MST) अणु
			dig = radeon_encoder->enc_priv;
			radeon_atom_release_dig_encoder(rdev, dig->dig_encoder);
			dig->dig_encoder = -1;
			radeon_encoder->active_device = 0;
		पूर्ण
	पूर्ण अन्यथा
		radeon_encoder->active_device = 0;
पूर्ण

/* these are handled by the primary encoders */
अटल व्योम radeon_atom_ext_prepare(काष्ठा drm_encoder *encoder)
अणु

पूर्ण

अटल व्योम radeon_atom_ext_commit(काष्ठा drm_encoder *encoder)
अणु

पूर्ण

अटल व्योम
radeon_atom_ext_mode_set(काष्ठा drm_encoder *encoder,
			 काष्ठा drm_display_mode *mode,
			 काष्ठा drm_display_mode *adjusted_mode)
अणु

पूर्ण

अटल व्योम radeon_atom_ext_disable(काष्ठा drm_encoder *encoder)
अणु

पूर्ण

अटल व्योम
radeon_atom_ext_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु

पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_atom_ext_helper_funcs = अणु
	.dpms = radeon_atom_ext_dpms,
	.prepare = radeon_atom_ext_prepare,
	.mode_set = radeon_atom_ext_mode_set,
	.commit = radeon_atom_ext_commit,
	.disable = radeon_atom_ext_disable,
	/* no detect क्रम TMDS/LVDS yet */
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_atom_dig_helper_funcs = अणु
	.dpms = radeon_atom_encoder_dpms,
	.mode_fixup = radeon_atom_mode_fixup,
	.prepare = radeon_atom_encoder_prepare,
	.mode_set = radeon_atom_encoder_mode_set,
	.commit = radeon_atom_encoder_commit,
	.disable = radeon_atom_encoder_disable,
	.detect = radeon_atom_dig_detect,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_atom_dac_helper_funcs = अणु
	.dpms = radeon_atom_encoder_dpms,
	.mode_fixup = radeon_atom_mode_fixup,
	.prepare = radeon_atom_encoder_prepare,
	.mode_set = radeon_atom_encoder_mode_set,
	.commit = radeon_atom_encoder_commit,
	.detect = radeon_atom_dac_detect,
पूर्ण;

व्योम radeon_enc_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
		radeon_atom_backlight_निकास(radeon_encoder);
	kमुक्त(radeon_encoder->enc_priv);
	drm_encoder_cleanup(encoder);
	kमुक्त(radeon_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs radeon_atom_enc_funcs = अणु
	.destroy = radeon_enc_destroy,
पूर्ण;

अटल काष्ठा radeon_encoder_atom_dac *
radeon_atombios_set_dac_info(काष्ठा radeon_encoder *radeon_encoder)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder_atom_dac *dac = kzalloc(माप(काष्ठा radeon_encoder_atom_dac), GFP_KERNEL);

	अगर (!dac)
		वापस शून्य;

	dac->tv_std = radeon_atombios_get_tv_info(rdev);
	वापस dac;
पूर्ण

अटल काष्ठा radeon_encoder_atom_dig *
radeon_atombios_set_dig_info(काष्ठा radeon_encoder *radeon_encoder)
अणु
	पूर्णांक encoder_क्रमागत = (radeon_encoder->encoder_क्रमागत & ENUM_ID_MASK) >> ENUM_ID_SHIFT;
	काष्ठा radeon_encoder_atom_dig *dig = kzalloc(माप(काष्ठा radeon_encoder_atom_dig), GFP_KERNEL);

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

व्योम
radeon_add_atom_encoder(काष्ठा drm_device *dev,
			uपूर्णांक32_t encoder_क्रमागत,
			uपूर्णांक32_t supported_device,
			u16 caps)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_encoder *encoder;
	काष्ठा radeon_encoder *radeon_encoder;

	/* see अगर we alपढ़ोy added it */
	list_क्रम_each_entry(encoder, &dev->mode_config.encoder_list, head) अणु
		radeon_encoder = to_radeon_encoder(encoder);
		अगर (radeon_encoder->encoder_क्रमागत == encoder_क्रमागत) अणु
			radeon_encoder->devices |= supported_device;
			वापस;
		पूर्ण

	पूर्ण

	/* add a new one */
	radeon_encoder = kzalloc(माप(काष्ठा radeon_encoder), GFP_KERNEL);
	अगर (!radeon_encoder)
		वापस;

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

	radeon_encoder->enc_priv = शून्य;

	radeon_encoder->encoder_क्रमागत = encoder_क्रमागत;
	radeon_encoder->encoder_id = (encoder_क्रमागत & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	radeon_encoder->devices = supported_device;
	radeon_encoder->rmx_type = RMX_OFF;
	radeon_encoder->underscan_type = UNDERSCAN_OFF;
	radeon_encoder->is_ext_encoder = false;
	radeon_encoder->caps = caps;

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_TMDS1:
	हाल ENCODER_OBJECT_ID_INTERNAL_LVTM1:
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
			radeon_encoder->rmx_type = RMX_FULL;
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_LVDS, शून्य);
			radeon_encoder->enc_priv = radeon_atombios_get_lvds_info(radeon_encoder);
		पूर्ण अन्यथा अणु
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_TMDS, शून्य);
			radeon_encoder->enc_priv = radeon_atombios_set_dig_info(radeon_encoder);
		पूर्ण
		drm_encoder_helper_add(encoder, &radeon_atom_dig_helper_funcs);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
		drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
				 DRM_MODE_ENCODER_DAC, शून्य);
		radeon_encoder->enc_priv = radeon_atombios_set_dac_info(radeon_encoder);
		drm_encoder_helper_add(encoder, &radeon_atom_dac_helper_funcs);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DAC2:
		drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
				 DRM_MODE_ENCODER_TVDAC, शून्य);
		radeon_encoder->enc_priv = radeon_atombios_set_dac_info(radeon_encoder);
		drm_encoder_helper_add(encoder, &radeon_atom_dac_helper_funcs);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_DVO1:
	हाल ENCODER_OBJECT_ID_INTERNAL_DDI:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY:
	हाल ENCODER_OBJECT_ID_INTERNAL_KLDSCP_LVTMA:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY1:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY2:
	हाल ENCODER_OBJECT_ID_INTERNAL_UNIPHY3:
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT)) अणु
			radeon_encoder->rmx_type = RMX_FULL;
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_LVDS, शून्य);
			radeon_encoder->enc_priv = radeon_atombios_get_lvds_info(radeon_encoder);
		पूर्ण अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_CRT_SUPPORT)) अणु
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_DAC, शून्य);
			radeon_encoder->enc_priv = radeon_atombios_set_dig_info(radeon_encoder);
		पूर्ण अन्यथा अणु
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_TMDS, शून्य);
			radeon_encoder->enc_priv = radeon_atombios_set_dig_info(radeon_encoder);
		पूर्ण
		drm_encoder_helper_add(encoder, &radeon_atom_dig_helper_funcs);
		अवरोध;
	हाल ENCODER_OBJECT_ID_SI170B:
	हाल ENCODER_OBJECT_ID_CH7303:
	हाल ENCODER_OBJECT_ID_EXTERNAL_SDVOA:
	हाल ENCODER_OBJECT_ID_EXTERNAL_SDVOB:
	हाल ENCODER_OBJECT_ID_TITFP513:
	हाल ENCODER_OBJECT_ID_VT1623:
	हाल ENCODER_OBJECT_ID_HDMI_SI1930:
	हाल ENCODER_OBJECT_ID_TRAVIS:
	हाल ENCODER_OBJECT_ID_NUTMEG:
		/* these are handled by the primary encoders */
		radeon_encoder->is_ext_encoder = true;
		अगर (radeon_encoder->devices & (ATOM_DEVICE_LCD_SUPPORT))
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_LVDS, शून्य);
		अन्यथा अगर (radeon_encoder->devices & (ATOM_DEVICE_CRT_SUPPORT))
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_DAC, शून्य);
		अन्यथा
			drm_encoder_init(dev, encoder, &radeon_atom_enc_funcs,
					 DRM_MODE_ENCODER_TMDS, शून्य);
		drm_encoder_helper_add(encoder, &radeon_atom_ext_helper_funcs);
		अवरोध;
	पूर्ण
पूर्ण
