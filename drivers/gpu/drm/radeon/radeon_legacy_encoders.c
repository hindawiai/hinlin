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

#समावेश <linux/backlight.h>
#समावेश <linux/pci.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_util.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "radeon_legacy_encoders.h"
#समावेश "atom.h"
#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर

अटल व्योम radeon_legacy_encoder_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	स्थिर काष्ठा drm_encoder_helper_funcs *encoder_funcs;

	encoder_funcs = encoder->helper_निजी;
	encoder_funcs->dpms(encoder, DRM_MODE_DPMS_OFF);
	radeon_encoder->active_device = 0;
पूर्ण

अटल व्योम radeon_legacy_lvds_update(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t lvds_gen_cntl, lvds_pll_cntl, pixclks_cntl, disp_pwr_man;
	पूर्णांक panel_pwr_delay = 2000;
	bool is_mac = false;
	uपूर्णांक8_t backlight_level;
	DRM_DEBUG_KMS("\n");

	lvds_gen_cntl = RREG32(RADEON_LVDS_GEN_CNTL);
	backlight_level = (lvds_gen_cntl >> RADEON_LVDS_BL_MOD_LEVEL_SHIFT) & 0xff;

	अगर (radeon_encoder->enc_priv) अणु
		अगर (rdev->is_atom_bios) अणु
			काष्ठा radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
			panel_pwr_delay = lvds->panel_pwr_delay;
			अगर (lvds->bl_dev)
				backlight_level = lvds->backlight_level;
		पूर्ण अन्यथा अणु
			काष्ठा radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
			panel_pwr_delay = lvds->panel_pwr_delay;
			अगर (lvds->bl_dev)
				backlight_level = lvds->backlight_level;
		पूर्ण
	पूर्ण

	/* macs (and possibly some x86 oem प्रणालीs?) wire up LVDS strangely
	 * Taken from radeonfb.
	 */
	अगर ((rdev->mode_info.connector_table == CT_IBOOK) ||
	    (rdev->mode_info.connector_table == CT_POWERBOOK_EXTERNAL) ||
	    (rdev->mode_info.connector_table == CT_POWERBOOK_INTERNAL) ||
	    (rdev->mode_info.connector_table == CT_POWERBOOK_VGA))
		is_mac = true;

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		disp_pwr_man = RREG32(RADEON_DISP_PWR_MAN);
		disp_pwr_man |= RADEON_AUTO_PWRUP_EN;
		WREG32(RADEON_DISP_PWR_MAN, disp_pwr_man);
		lvds_pll_cntl = RREG32(RADEON_LVDS_PLL_CNTL);
		lvds_pll_cntl |= RADEON_LVDS_PLL_EN;
		WREG32(RADEON_LVDS_PLL_CNTL, lvds_pll_cntl);
		mdelay(1);

		lvds_pll_cntl = RREG32(RADEON_LVDS_PLL_CNTL);
		lvds_pll_cntl &= ~RADEON_LVDS_PLL_RESET;
		WREG32(RADEON_LVDS_PLL_CNTL, lvds_pll_cntl);

		lvds_gen_cntl &= ~(RADEON_LVDS_DISPLAY_DIS |
				   RADEON_LVDS_BL_MOD_LEVEL_MASK);
		lvds_gen_cntl |= (RADEON_LVDS_ON | RADEON_LVDS_EN |
				  RADEON_LVDS_DIGON | RADEON_LVDS_BLON |
				  (backlight_level << RADEON_LVDS_BL_MOD_LEVEL_SHIFT));
		अगर (is_mac)
			lvds_gen_cntl |= RADEON_LVDS_BL_MOD_EN;
		mdelay(panel_pwr_delay);
		WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		pixclks_cntl = RREG32_PLL(RADEON_PIXCLKS_CNTL);
		WREG32_PLL_P(RADEON_PIXCLKS_CNTL, 0, ~RADEON_PIXCLK_LVDS_ALWAYS_ONb);
		lvds_gen_cntl |= RADEON_LVDS_DISPLAY_DIS;
		अगर (is_mac) अणु
			lvds_gen_cntl &= ~RADEON_LVDS_BL_MOD_EN;
			WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
			lvds_gen_cntl &= ~(RADEON_LVDS_ON | RADEON_LVDS_EN);
		पूर्ण अन्यथा अणु
			WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
			lvds_gen_cntl &= ~(RADEON_LVDS_ON | RADEON_LVDS_BLON | RADEON_LVDS_EN | RADEON_LVDS_DIGON);
		पूर्ण
		mdelay(panel_pwr_delay);
		WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
		WREG32_PLL(RADEON_PIXCLKS_CNTL, pixclks_cntl);
		mdelay(panel_pwr_delay);
		अवरोध;
	पूर्ण

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);
	अन्यथा
		radeon_combios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);

पूर्ण

अटल व्योम radeon_legacy_lvds_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	DRM_DEBUG("\n");

	अगर (radeon_encoder->enc_priv) अणु
		अगर (rdev->is_atom_bios) अणु
			काष्ठा radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
			lvds->dpms_mode = mode;
		पूर्ण अन्यथा अणु
			काष्ठा radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
			lvds->dpms_mode = mode;
		पूर्ण
	पूर्ण

	radeon_legacy_lvds_update(encoder, mode);
पूर्ण

अटल व्योम radeon_legacy_lvds_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	अन्यथा
		radeon_combios_output_lock(encoder, true);
	radeon_legacy_lvds_dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम radeon_legacy_lvds_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	radeon_legacy_lvds_dpms(encoder, DRM_MODE_DPMS_ON);
	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, false);
	अन्यथा
		radeon_combios_output_lock(encoder, false);
पूर्ण

अटल व्योम radeon_legacy_lvds_mode_set(काष्ठा drm_encoder *encoder,
					काष्ठा drm_display_mode *mode,
					काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t lvds_pll_cntl, lvds_gen_cntl, lvds_ss_gen_cntl;

	DRM_DEBUG_KMS("\n");

	lvds_pll_cntl = RREG32(RADEON_LVDS_PLL_CNTL);
	lvds_pll_cntl &= ~RADEON_LVDS_PLL_EN;

	lvds_ss_gen_cntl = RREG32(RADEON_LVDS_SS_GEN_CNTL);
	अगर (rdev->is_atom_bios) अणु
		/* LVDS_GEN_CNTL parameters are computed in LVDSEncoderControl
		 * need to call that on resume to set up the reg properly.
		 */
		radeon_encoder->pixel_घड़ी = adjusted_mode->घड़ी;
		atombios_digital_setup(encoder, PANEL_ENCODER_ACTION_ENABLE);
		lvds_gen_cntl = RREG32(RADEON_LVDS_GEN_CNTL);
	पूर्ण अन्यथा अणु
		काष्ठा radeon_encoder_lvds *lvds = (काष्ठा radeon_encoder_lvds *)radeon_encoder->enc_priv;
		अगर (lvds) अणु
			DRM_DEBUG_KMS("bios LVDS_GEN_CNTL: 0x%x\n", lvds->lvds_gen_cntl);
			lvds_gen_cntl = lvds->lvds_gen_cntl;
			lvds_ss_gen_cntl &= ~((0xf << RADEON_LVDS_PWRSEQ_DELAY1_SHIFT) |
					      (0xf << RADEON_LVDS_PWRSEQ_DELAY2_SHIFT));
			lvds_ss_gen_cntl |= ((lvds->panel_digon_delay << RADEON_LVDS_PWRSEQ_DELAY1_SHIFT) |
					     (lvds->panel_blon_delay << RADEON_LVDS_PWRSEQ_DELAY2_SHIFT));
		पूर्ण अन्यथा
			lvds_gen_cntl = RREG32(RADEON_LVDS_GEN_CNTL);
	पूर्ण
	lvds_gen_cntl |= RADEON_LVDS_DISPLAY_DIS;
	lvds_gen_cntl &= ~(RADEON_LVDS_ON |
			   RADEON_LVDS_BLON |
			   RADEON_LVDS_EN |
			   RADEON_LVDS_RST_FM);

	अगर (ASIC_IS_R300(rdev))
		lvds_pll_cntl &= ~(R300_LVDS_SRC_SEL_MASK);

	अगर (radeon_crtc->crtc_id == 0) अणु
		अगर (ASIC_IS_R300(rdev)) अणु
			अगर (radeon_encoder->rmx_type != RMX_OFF)
				lvds_pll_cntl |= R300_LVDS_SRC_SEL_RMX;
		पूर्ण अन्यथा
			lvds_gen_cntl &= ~RADEON_LVDS_SEL_CRTC2;
	पूर्ण अन्यथा अणु
		अगर (ASIC_IS_R300(rdev))
			lvds_pll_cntl |= R300_LVDS_SRC_SEL_CRTC2;
		अन्यथा
			lvds_gen_cntl |= RADEON_LVDS_SEL_CRTC2;
	पूर्ण

	WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
	WREG32(RADEON_LVDS_PLL_CNTL, lvds_pll_cntl);
	WREG32(RADEON_LVDS_SS_GEN_CNTL, lvds_ss_gen_cntl);

	अगर (rdev->family == CHIP_RV410)
		WREG32(RADEON_CLOCK_CNTL_INDEX, 0);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	अन्यथा
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
पूर्ण

अटल bool radeon_legacy_mode_fixup(काष्ठा drm_encoder *encoder,
				     स्थिर काष्ठा drm_display_mode *mode,
				     काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	/* set the active encoder to connector routing */
	radeon_encoder_set_active_device(encoder);
	drm_mode_set_crtcinfo(adjusted_mode, 0);

	/* get the native mode क्रम LVDS */
	अगर (radeon_encoder->active_device & (ATOM_DEVICE_LCD_SUPPORT))
		radeon_panel_mode_fixup(encoder, adjusted_mode);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_legacy_lvds_helper_funcs = अणु
	.dpms = radeon_legacy_lvds_dpms,
	.mode_fixup = radeon_legacy_mode_fixup,
	.prepare = radeon_legacy_lvds_prepare,
	.mode_set = radeon_legacy_lvds_mode_set,
	.commit = radeon_legacy_lvds_commit,
	.disable = radeon_legacy_encoder_disable,
पूर्ण;

u8
radeon_legacy_get_backlight_level(काष्ठा radeon_encoder *radeon_encoder)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	u8 backlight_level;

	backlight_level = (RREG32(RADEON_LVDS_GEN_CNTL) >>
			   RADEON_LVDS_BL_MOD_LEVEL_SHIFT) & 0xff;

	वापस backlight_level;
पूर्ण

व्योम
radeon_legacy_set_backlight_level(काष्ठा radeon_encoder *radeon_encoder, u8 level)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	पूर्णांक dpms_mode = DRM_MODE_DPMS_ON;

	अगर (radeon_encoder->enc_priv) अणु
		अगर (rdev->is_atom_bios) अणु
			काष्ठा radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
			अगर (lvds->backlight_level > 0)
				dpms_mode = lvds->dpms_mode;
			अन्यथा
				dpms_mode = DRM_MODE_DPMS_OFF;
			lvds->backlight_level = level;
		पूर्ण अन्यथा अणु
			काष्ठा radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
			अगर (lvds->backlight_level > 0)
				dpms_mode = lvds->dpms_mode;
			अन्यथा
				dpms_mode = DRM_MODE_DPMS_OFF;
			lvds->backlight_level = level;
		पूर्ण
	पूर्ण

	radeon_legacy_lvds_update(&radeon_encoder->base, dpms_mode);
पूर्ण

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

अटल uपूर्णांक8_t radeon_legacy_lvds_level(काष्ठा backlight_device *bd)
अणु
	काष्ठा radeon_backlight_privdata *pdata = bl_get_data(bd);
	uपूर्णांक8_t level;

	/* Convert brightness to hardware level */
	अगर (bd->props.brightness < 0)
		level = 0;
	अन्यथा अगर (bd->props.brightness > RADEON_MAX_BL_LEVEL)
		level = RADEON_MAX_BL_LEVEL;
	अन्यथा
		level = bd->props.brightness;

	अगर (pdata->negative)
		level = RADEON_MAX_BL_LEVEL - level;

	वापस level;
पूर्ण

अटल पूर्णांक radeon_legacy_backlight_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा radeon_backlight_privdata *pdata = bl_get_data(bd);
	काष्ठा radeon_encoder *radeon_encoder = pdata->encoder;

	radeon_legacy_set_backlight_level(radeon_encoder,
					  radeon_legacy_lvds_level(bd));

	वापस 0;
पूर्ण

अटल पूर्णांक radeon_legacy_backlight_get_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा radeon_backlight_privdata *pdata = bl_get_data(bd);
	काष्ठा radeon_encoder *radeon_encoder = pdata->encoder;
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक8_t backlight_level;

	backlight_level = (RREG32(RADEON_LVDS_GEN_CNTL) >>
			   RADEON_LVDS_BL_MOD_LEVEL_SHIFT) & 0xff;

	वापस pdata->negative ? RADEON_MAX_BL_LEVEL - backlight_level : backlight_level;
पूर्ण

अटल स्थिर काष्ठा backlight_ops radeon_backlight_ops = अणु
	.get_brightness = radeon_legacy_backlight_get_brightness,
	.update_status	= radeon_legacy_backlight_update_status,
पूर्ण;

व्योम radeon_legacy_backlight_init(काष्ठा radeon_encoder *radeon_encoder,
				  काष्ठा drm_connector *drm_connector)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;
	काष्ठा radeon_backlight_privdata *pdata;
	uपूर्णांक8_t backlight_level;
	अक्षर bl_name[16];

	अगर (!radeon_encoder->enc_priv)
		वापस;

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
	अगर (!pmac_has_backlight_type("ati") &&
	    !pmac_has_backlight_type("mnca"))
		वापस;
#पूर्ण_अगर

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
				       pdata, &radeon_backlight_ops, &props);
	अगर (IS_ERR(bd)) अणु
		DRM_ERROR("Backlight registration failed\n");
		जाओ error;
	पूर्ण

	pdata->encoder = radeon_encoder;

	backlight_level = (RREG32(RADEON_LVDS_GEN_CNTL) >>
			   RADEON_LVDS_BL_MOD_LEVEL_SHIFT) & 0xff;

	/* First, try to detect backlight level sense based on the assumption
	 * that firmware set it up at full brightness
	 */
	अगर (backlight_level == 0)
		pdata->negative = true;
	अन्यथा अगर (backlight_level == 0xff)
		pdata->negative = false;
	अन्यथा अणु
		/* XXX hack... maybe some day we can figure out in what direction
		 * backlight should work on a given panel?
		 */
		pdata->negative = (rdev->family != CHIP_RV200 &&
				   rdev->family != CHIP_RV250 &&
				   rdev->family != CHIP_RV280 &&
				   rdev->family != CHIP_RV350);

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
		pdata->negative = (pdata->negative ||
				   of_machine_is_compatible("PowerBook4,3") ||
				   of_machine_is_compatible("PowerBook6,3") ||
				   of_machine_is_compatible("PowerBook6,5"));
#पूर्ण_अगर
	पूर्ण

	अगर (rdev->is_atom_bios) अणु
		काष्ठा radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
		lvds->bl_dev = bd;
	पूर्ण अन्यथा अणु
		काष्ठा radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
		lvds->bl_dev = bd;
	पूर्ण

	bd->props.brightness = radeon_legacy_backlight_get_brightness(bd);
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	DRM_INFO("radeon legacy LVDS backlight initialized\n");
	rdev->mode_info.bl_encoder = radeon_encoder;

	वापस;

error:
	kमुक्त(pdata);
	वापस;
पूर्ण

अटल व्योम radeon_legacy_backlight_निकास(काष्ठा radeon_encoder *radeon_encoder)
अणु
	काष्ठा drm_device *dev = radeon_encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा backlight_device *bd = शून्य;

	अगर (!radeon_encoder->enc_priv)
		वापस;

	अगर (rdev->is_atom_bios) अणु
		काष्ठा radeon_encoder_atom_dig *lvds = radeon_encoder->enc_priv;
		bd = lvds->bl_dev;
		lvds->bl_dev = शून्य;
	पूर्ण अन्यथा अणु
		काष्ठा radeon_encoder_lvds *lvds = radeon_encoder->enc_priv;
		bd = lvds->bl_dev;
		lvds->bl_dev = शून्य;
	पूर्ण

	अगर (bd) अणु
		काष्ठा radeon_backlight_privdata *pdata;

		pdata = bl_get_data(bd);
		backlight_device_unरेजिस्टर(bd);
		kमुक्त(pdata);

		DRM_INFO("radeon legacy LVDS backlight unloaded\n");
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_BACKLIGHT_CLASS_DEVICE */

व्योम radeon_legacy_backlight_init(काष्ठा radeon_encoder *encoder)
अणु
पूर्ण

अटल व्योम radeon_legacy_backlight_निकास(काष्ठा radeon_encoder *encoder)
अणु
पूर्ण

#पूर्ण_अगर


अटल व्योम radeon_lvds_enc_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);

	अगर (radeon_encoder->enc_priv) अणु
		radeon_legacy_backlight_निकास(radeon_encoder);
		kमुक्त(radeon_encoder->enc_priv);
	पूर्ण
	drm_encoder_cleanup(encoder);
	kमुक्त(radeon_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs radeon_legacy_lvds_enc_funcs = अणु
	.destroy = radeon_lvds_enc_destroy,
पूर्ण;

अटल व्योम radeon_legacy_primary_dac_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t crtc_ext_cntl = RREG32(RADEON_CRTC_EXT_CNTL);
	uपूर्णांक32_t dac_cntl = RREG32(RADEON_DAC_CNTL);
	uपूर्णांक32_t dac_macro_cntl = RREG32(RADEON_DAC_MACRO_CNTL);

	DRM_DEBUG_KMS("\n");

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		crtc_ext_cntl |= RADEON_CRTC_CRT_ON;
		dac_cntl &= ~RADEON_DAC_PDWN;
		dac_macro_cntl &= ~(RADEON_DAC_PDWN_R |
				    RADEON_DAC_PDWN_G |
				    RADEON_DAC_PDWN_B);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		crtc_ext_cntl &= ~RADEON_CRTC_CRT_ON;
		dac_cntl |= RADEON_DAC_PDWN;
		dac_macro_cntl |= (RADEON_DAC_PDWN_R |
				   RADEON_DAC_PDWN_G |
				   RADEON_DAC_PDWN_B);
		अवरोध;
	पूर्ण

	/* handled in radeon_crtc_dpms() */
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC))
		WREG32(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl);
	WREG32(RADEON_DAC_CNTL, dac_cntl);
	WREG32(RADEON_DAC_MACRO_CNTL, dac_macro_cntl);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);
	अन्यथा
		radeon_combios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);

पूर्ण

अटल व्योम radeon_legacy_primary_dac_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	अन्यथा
		radeon_combios_output_lock(encoder, true);
	radeon_legacy_primary_dac_dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम radeon_legacy_primary_dac_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	radeon_legacy_primary_dac_dpms(encoder, DRM_MODE_DPMS_ON);

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, false);
	अन्यथा
		radeon_combios_output_lock(encoder, false);
पूर्ण

अटल व्योम radeon_legacy_primary_dac_mode_set(काष्ठा drm_encoder *encoder,
					       काष्ठा drm_display_mode *mode,
					       काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t disp_output_cntl, dac_cntl, dac2_cntl, dac_macro_cntl;

	DRM_DEBUG_KMS("\n");

	अगर (radeon_crtc->crtc_id == 0) अणु
		अगर (rdev->family == CHIP_R200 || ASIC_IS_R300(rdev)) अणु
			disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL) &
				~(RADEON_DISP_DAC_SOURCE_MASK);
			WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
		पूर्ण अन्यथा अणु
			dac2_cntl = RREG32(RADEON_DAC_CNTL2)  & ~(RADEON_DAC2_DAC_CLK_SEL);
			WREG32(RADEON_DAC_CNTL2, dac2_cntl);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rdev->family == CHIP_R200 || ASIC_IS_R300(rdev)) अणु
			disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL) &
				~(RADEON_DISP_DAC_SOURCE_MASK);
			disp_output_cntl |= RADEON_DISP_DAC_SOURCE_CRTC2;
			WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
		पूर्ण अन्यथा अणु
			dac2_cntl = RREG32(RADEON_DAC_CNTL2) | RADEON_DAC2_DAC_CLK_SEL;
			WREG32(RADEON_DAC_CNTL2, dac2_cntl);
		पूर्ण
	पूर्ण

	dac_cntl = (RADEON_DAC_MASK_ALL |
		    RADEON_DAC_VGA_ADR_EN |
		    /* TODO 6-bits */
		    RADEON_DAC_8BIT_EN);

	WREG32_P(RADEON_DAC_CNTL,
		       dac_cntl,
		       RADEON_DAC_RANGE_CNTL |
		       RADEON_DAC_BLANKING);

	अगर (radeon_encoder->enc_priv) अणु
		काष्ठा radeon_encoder_primary_dac *p_dac = (काष्ठा radeon_encoder_primary_dac *)radeon_encoder->enc_priv;
		dac_macro_cntl = p_dac->ps2_pdac_adj;
	पूर्ण अन्यथा
		dac_macro_cntl = RREG32(RADEON_DAC_MACRO_CNTL);
	dac_macro_cntl |= RADEON_DAC_PDWN_R | RADEON_DAC_PDWN_G | RADEON_DAC_PDWN_B;
	WREG32(RADEON_DAC_MACRO_CNTL, dac_macro_cntl);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	अन्यथा
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
पूर्ण

अटल क्रमागत drm_connector_status radeon_legacy_primary_dac_detect(काष्ठा drm_encoder *encoder,
								  काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t vclk_ecp_cntl, crtc_ext_cntl;
	uपूर्णांक32_t dac_ext_cntl, dac_cntl, dac_macro_cntl, पंचांगp;
	क्रमागत drm_connector_status found = connector_status_disconnected;
	bool color = true;

	/* just करोn't bother on RN50 those chip are often connected to remoting
	 * console hw and often we get failure to load detect those. So to make
	 * everyone happy report the encoder as always connected.
	 */
	अगर (ASIC_IS_RN50(rdev)) अणु
		वापस connector_status_connected;
	पूर्ण

	/* save the regs we need */
	vclk_ecp_cntl = RREG32_PLL(RADEON_VCLK_ECP_CNTL);
	crtc_ext_cntl = RREG32(RADEON_CRTC_EXT_CNTL);
	dac_ext_cntl = RREG32(RADEON_DAC_EXT_CNTL);
	dac_cntl = RREG32(RADEON_DAC_CNTL);
	dac_macro_cntl = RREG32(RADEON_DAC_MACRO_CNTL);

	पंचांगp = vclk_ecp_cntl &
		~(RADEON_PIXCLK_ALWAYS_ONb | RADEON_PIXCLK_DAC_ALWAYS_ONb);
	WREG32_PLL(RADEON_VCLK_ECP_CNTL, पंचांगp);

	पंचांगp = crtc_ext_cntl | RADEON_CRTC_CRT_ON;
	WREG32(RADEON_CRTC_EXT_CNTL, पंचांगp);

	पंचांगp = RADEON_DAC_FORCE_BLANK_OFF_EN |
		RADEON_DAC_FORCE_DATA_EN;

	अगर (color)
		पंचांगp |= RADEON_DAC_FORCE_DATA_SEL_RGB;
	अन्यथा
		पंचांगp |= RADEON_DAC_FORCE_DATA_SEL_G;

	अगर (ASIC_IS_R300(rdev))
		पंचांगp |= (0x1b6 << RADEON_DAC_FORCE_DATA_SHIFT);
	अन्यथा अगर (ASIC_IS_RV100(rdev))
		पंचांगp |= (0x1ac << RADEON_DAC_FORCE_DATA_SHIFT);
	अन्यथा
		पंचांगp |= (0x180 << RADEON_DAC_FORCE_DATA_SHIFT);

	WREG32(RADEON_DAC_EXT_CNTL, पंचांगp);

	पंचांगp = dac_cntl & ~(RADEON_DAC_RANGE_CNTL_MASK | RADEON_DAC_PDWN);
	पंचांगp |= RADEON_DAC_RANGE_CNTL_PS2 | RADEON_DAC_CMP_EN;
	WREG32(RADEON_DAC_CNTL, पंचांगp);

	पंचांगp = dac_macro_cntl;
	पंचांगp &= ~(RADEON_DAC_PDWN_R |
		 RADEON_DAC_PDWN_G |
		 RADEON_DAC_PDWN_B);

	WREG32(RADEON_DAC_MACRO_CNTL, पंचांगp);

	mdelay(2);

	अगर (RREG32(RADEON_DAC_CNTL) & RADEON_DAC_CMP_OUTPUT)
		found = connector_status_connected;

	/* restore the regs we used */
	WREG32(RADEON_DAC_CNTL, dac_cntl);
	WREG32(RADEON_DAC_MACRO_CNTL, dac_macro_cntl);
	WREG32(RADEON_DAC_EXT_CNTL, dac_ext_cntl);
	WREG32(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl);
	WREG32_PLL(RADEON_VCLK_ECP_CNTL, vclk_ecp_cntl);

	वापस found;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_legacy_primary_dac_helper_funcs = अणु
	.dpms = radeon_legacy_primary_dac_dpms,
	.mode_fixup = radeon_legacy_mode_fixup,
	.prepare = radeon_legacy_primary_dac_prepare,
	.mode_set = radeon_legacy_primary_dac_mode_set,
	.commit = radeon_legacy_primary_dac_commit,
	.detect = radeon_legacy_primary_dac_detect,
	.disable = radeon_legacy_encoder_disable,
पूर्ण;


अटल स्थिर काष्ठा drm_encoder_funcs radeon_legacy_primary_dac_enc_funcs = अणु
	.destroy = radeon_enc_destroy,
पूर्ण;

अटल व्योम radeon_legacy_पंचांगds_पूर्णांक_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t fp_gen_cntl = RREG32(RADEON_FP_GEN_CNTL);
	DRM_DEBUG_KMS("\n");

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		fp_gen_cntl |= (RADEON_FP_FPON | RADEON_FP_TMDS_EN);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		fp_gen_cntl &= ~(RADEON_FP_FPON | RADEON_FP_TMDS_EN);
		अवरोध;
	पूर्ण

	WREG32(RADEON_FP_GEN_CNTL, fp_gen_cntl);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);
	अन्यथा
		radeon_combios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);

पूर्ण

अटल व्योम radeon_legacy_पंचांगds_पूर्णांक_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	अन्यथा
		radeon_combios_output_lock(encoder, true);
	radeon_legacy_पंचांगds_पूर्णांक_dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम radeon_legacy_पंचांगds_पूर्णांक_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	radeon_legacy_पंचांगds_पूर्णांक_dpms(encoder, DRM_MODE_DPMS_ON);

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	अन्यथा
		radeon_combios_output_lock(encoder, true);
पूर्ण

अटल व्योम radeon_legacy_पंचांगds_पूर्णांक_mode_set(काष्ठा drm_encoder *encoder,
					    काष्ठा drm_display_mode *mode,
					    काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t पंचांगp, पंचांगds_pll_cntl, पंचांगds_transmitter_cntl, fp_gen_cntl;
	पूर्णांक i;

	DRM_DEBUG_KMS("\n");

	पंचांगp = पंचांगds_pll_cntl = RREG32(RADEON_TMDS_PLL_CNTL);
	पंचांगp &= 0xfffff;
	अगर (rdev->family == CHIP_RV280) अणु
		/* bit 22 of TMDS_PLL_CNTL is पढ़ो-back inverted */
		पंचांगp ^= (1 << 22);
		पंचांगds_pll_cntl ^= (1 << 22);
	पूर्ण

	अगर (radeon_encoder->enc_priv) अणु
		काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds = (काष्ठा radeon_encoder_पूर्णांक_पंचांगds *)radeon_encoder->enc_priv;

		क्रम (i = 0; i < 4; i++) अणु
			अगर (पंचांगds->पंचांगds_pll[i].freq == 0)
				अवरोध;
			अगर ((uपूर्णांक32_t)(mode->घड़ी / 10) < पंचांगds->पंचांगds_pll[i].freq) अणु
				पंचांगp = पंचांगds->पंचांगds_pll[i].value ;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (ASIC_IS_R300(rdev) || (rdev->family == CHIP_RV280)) अणु
		अगर (पंचांगp & 0xfff00000)
			पंचांगds_pll_cntl = पंचांगp;
		अन्यथा अणु
			पंचांगds_pll_cntl &= 0xfff00000;
			पंचांगds_pll_cntl |= पंचांगp;
		पूर्ण
	पूर्ण अन्यथा
		पंचांगds_pll_cntl = पंचांगp;

	पंचांगds_transmitter_cntl = RREG32(RADEON_TMDS_TRANSMITTER_CNTL) &
		~(RADEON_TMDS_TRANSMITTER_PLLRST);

	अगर (rdev->family == CHIP_R200 ||
	    rdev->family == CHIP_R100 ||
	    ASIC_IS_R300(rdev))
		पंचांगds_transmitter_cntl &= ~(RADEON_TMDS_TRANSMITTER_PLLEN);
	अन्यथा /* RV chips got this bit reversed */
		पंचांगds_transmitter_cntl |= RADEON_TMDS_TRANSMITTER_PLLEN;

	fp_gen_cntl = (RREG32(RADEON_FP_GEN_CNTL) |
		      (RADEON_FP_CRTC_DONT_SHADOW_VPAR |
		       RADEON_FP_CRTC_DONT_SHADOW_HEND));

	fp_gen_cntl &= ~(RADEON_FP_FPON | RADEON_FP_TMDS_EN);

	fp_gen_cntl &= ~(RADEON_FP_RMX_HVSYNC_CONTROL_EN |
			 RADEON_FP_DFP_SYNC_SEL |
			 RADEON_FP_CRT_SYNC_SEL |
			 RADEON_FP_CRTC_LOCK_8DOT |
			 RADEON_FP_USE_SHADOW_EN |
			 RADEON_FP_CRTC_USE_SHADOW_VEND |
			 RADEON_FP_CRT_SYNC_ALT);

	अगर (1) /*  FIXME rgbBits == 8 */
		fp_gen_cntl |= RADEON_FP_PANEL_FORMAT;  /* 24 bit क्रमmat */
	अन्यथा
		fp_gen_cntl &= ~RADEON_FP_PANEL_FORMAT;/* 18 bit क्रमmat */

	अगर (radeon_crtc->crtc_id == 0) अणु
		अगर (ASIC_IS_R300(rdev) || rdev->family == CHIP_R200) अणु
			fp_gen_cntl &= ~R200_FP_SOURCE_SEL_MASK;
			अगर (radeon_encoder->rmx_type != RMX_OFF)
				fp_gen_cntl |= R200_FP_SOURCE_SEL_RMX;
			अन्यथा
				fp_gen_cntl |= R200_FP_SOURCE_SEL_CRTC1;
		पूर्ण अन्यथा
			fp_gen_cntl &= ~RADEON_FP_SEL_CRTC2;
	पूर्ण अन्यथा अणु
		अगर (ASIC_IS_R300(rdev) || rdev->family == CHIP_R200) अणु
			fp_gen_cntl &= ~R200_FP_SOURCE_SEL_MASK;
			fp_gen_cntl |= R200_FP_SOURCE_SEL_CRTC2;
		पूर्ण अन्यथा
			fp_gen_cntl |= RADEON_FP_SEL_CRTC2;
	पूर्ण

	WREG32(RADEON_TMDS_PLL_CNTL, पंचांगds_pll_cntl);
	WREG32(RADEON_TMDS_TRANSMITTER_CNTL, पंचांगds_transmitter_cntl);
	WREG32(RADEON_FP_GEN_CNTL, fp_gen_cntl);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	अन्यथा
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_legacy_पंचांगds_पूर्णांक_helper_funcs = अणु
	.dpms = radeon_legacy_पंचांगds_पूर्णांक_dpms,
	.mode_fixup = radeon_legacy_mode_fixup,
	.prepare = radeon_legacy_पंचांगds_पूर्णांक_prepare,
	.mode_set = radeon_legacy_पंचांगds_पूर्णांक_mode_set,
	.commit = radeon_legacy_पंचांगds_पूर्णांक_commit,
	.disable = radeon_legacy_encoder_disable,
पूर्ण;


अटल स्थिर काष्ठा drm_encoder_funcs radeon_legacy_पंचांगds_पूर्णांक_enc_funcs = अणु
	.destroy = radeon_enc_destroy,
पूर्ण;

अटल व्योम radeon_legacy_पंचांगds_ext_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);
	DRM_DEBUG_KMS("\n");

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		fp2_gen_cntl &= ~RADEON_FP2_BLANK_EN;
		fp2_gen_cntl |= (RADEON_FP2_ON | RADEON_FP2_DVO_EN);
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		fp2_gen_cntl |= RADEON_FP2_BLANK_EN;
		fp2_gen_cntl &= ~(RADEON_FP2_ON | RADEON_FP2_DVO_EN);
		अवरोध;
	पूर्ण

	WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);
	अन्यथा
		radeon_combios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);

पूर्ण

अटल व्योम radeon_legacy_पंचांगds_ext_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	अन्यथा
		radeon_combios_output_lock(encoder, true);
	radeon_legacy_पंचांगds_ext_dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम radeon_legacy_पंचांगds_ext_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;
	radeon_legacy_पंचांगds_ext_dpms(encoder, DRM_MODE_DPMS_ON);

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, false);
	अन्यथा
		radeon_combios_output_lock(encoder, false);
पूर्ण

अटल व्योम radeon_legacy_पंचांगds_ext_mode_set(काष्ठा drm_encoder *encoder,
					    काष्ठा drm_display_mode *mode,
					    काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t fp2_gen_cntl;

	DRM_DEBUG_KMS("\n");

	अगर (rdev->is_atom_bios) अणु
		radeon_encoder->pixel_घड़ी = adjusted_mode->घड़ी;
		atombios_dvo_setup(encoder, ATOM_ENABLE);
		fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);
	पूर्ण अन्यथा अणु
		fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);

		अगर (1) /*  FIXME rgbBits == 8 */
			fp2_gen_cntl |= RADEON_FP2_PANEL_FORMAT; /* 24 bit क्रमmat, */
		अन्यथा
			fp2_gen_cntl &= ~RADEON_FP2_PANEL_FORMAT;/* 18 bit क्रमmat, */

		fp2_gen_cntl &= ~(RADEON_FP2_ON |
				  RADEON_FP2_DVO_EN |
				  RADEON_FP2_DVO_RATE_SEL_SDR);

		/* XXX: these are oem specअगरic */
		अगर (ASIC_IS_R300(rdev)) अणु
			अगर ((rdev->pdev->device == 0x4850) &&
			    (rdev->pdev->subप्रणाली_venकरोr == 0x1028) &&
			    (rdev->pdev->subप्रणाली_device == 0x2001)) /* Dell Inspiron 8600 */
				fp2_gen_cntl |= R300_FP2_DVO_CLOCK_MODE_SINGLE;
			अन्यथा
				fp2_gen_cntl |= RADEON_FP2_PAD_FLOP_EN | R300_FP2_DVO_CLOCK_MODE_SINGLE;

			/*अगर (mode->घड़ी > 165000)
			  fp2_gen_cntl |= R300_FP2_DVO_DUAL_CHANNEL_EN;*/
		पूर्ण
		अगर (!radeon_combios_बाह्यal_पंचांगds_setup(encoder))
			radeon_बाह्यal_पंचांगds_setup(encoder);
	पूर्ण

	अगर (radeon_crtc->crtc_id == 0) अणु
		अगर ((rdev->family == CHIP_R200) || ASIC_IS_R300(rdev)) अणु
			fp2_gen_cntl &= ~R200_FP2_SOURCE_SEL_MASK;
			अगर (radeon_encoder->rmx_type != RMX_OFF)
				fp2_gen_cntl |= R200_FP2_SOURCE_SEL_RMX;
			अन्यथा
				fp2_gen_cntl |= R200_FP2_SOURCE_SEL_CRTC1;
		पूर्ण अन्यथा
			fp2_gen_cntl &= ~RADEON_FP2_SRC_SEL_CRTC2;
	पूर्ण अन्यथा अणु
		अगर ((rdev->family == CHIP_R200) || ASIC_IS_R300(rdev)) अणु
			fp2_gen_cntl &= ~R200_FP2_SOURCE_SEL_MASK;
			fp2_gen_cntl |= R200_FP2_SOURCE_SEL_CRTC2;
		पूर्ण अन्यथा
			fp2_gen_cntl |= RADEON_FP2_SRC_SEL_CRTC2;
	पूर्ण

	WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	अन्यथा
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
पूर्ण

अटल व्योम radeon_ext_पंचांगds_enc_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	/* करोn't destroy the i2c bus record here, this will be करोne in radeon_i2c_fini */
	kमुक्त(radeon_encoder->enc_priv);
	drm_encoder_cleanup(encoder);
	kमुक्त(radeon_encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_legacy_पंचांगds_ext_helper_funcs = अणु
	.dpms = radeon_legacy_पंचांगds_ext_dpms,
	.mode_fixup = radeon_legacy_mode_fixup,
	.prepare = radeon_legacy_पंचांगds_ext_prepare,
	.mode_set = radeon_legacy_पंचांगds_ext_mode_set,
	.commit = radeon_legacy_पंचांगds_ext_commit,
	.disable = radeon_legacy_encoder_disable,
पूर्ण;


अटल स्थिर काष्ठा drm_encoder_funcs radeon_legacy_पंचांगds_ext_enc_funcs = अणु
	.destroy = radeon_ext_पंचांगds_enc_destroy,
पूर्ण;

अटल व्योम radeon_legacy_tv_dac_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uपूर्णांक32_t fp2_gen_cntl = 0, crtc2_gen_cntl = 0, tv_dac_cntl = 0;
	uपूर्णांक32_t tv_master_cntl = 0;
	bool is_tv;
	DRM_DEBUG_KMS("\n");

	is_tv = radeon_encoder->active_device & ATOM_DEVICE_TV_SUPPORT ? true : false;

	अगर (rdev->family == CHIP_R200)
		fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);
	अन्यथा अणु
		अगर (is_tv)
			tv_master_cntl = RREG32(RADEON_TV_MASTER_CNTL);
		अन्यथा
			crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
		tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
	पूर्ण

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		अगर (rdev->family == CHIP_R200) अणु
			fp2_gen_cntl |= (RADEON_FP2_ON | RADEON_FP2_DVO_EN);
		पूर्ण अन्यथा अणु
			अगर (is_tv)
				tv_master_cntl |= RADEON_TV_ON;
			अन्यथा
				crtc2_gen_cntl |= RADEON_CRTC2_CRT2_ON;

			अगर (rdev->family == CHIP_R420 ||
			    rdev->family == CHIP_R423 ||
			    rdev->family == CHIP_RV410)
				tv_dac_cntl &= ~(R420_TV_DAC_RDACPD |
						 R420_TV_DAC_GDACPD |
						 R420_TV_DAC_BDACPD |
						 RADEON_TV_DAC_BGSLEEP);
			अन्यथा
				tv_dac_cntl &= ~(RADEON_TV_DAC_RDACPD |
						 RADEON_TV_DAC_GDACPD |
						 RADEON_TV_DAC_BDACPD |
						 RADEON_TV_DAC_BGSLEEP);
		पूर्ण
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
	हाल DRM_MODE_DPMS_OFF:
		अगर (rdev->family == CHIP_R200)
			fp2_gen_cntl &= ~(RADEON_FP2_ON | RADEON_FP2_DVO_EN);
		अन्यथा अणु
			अगर (is_tv)
				tv_master_cntl &= ~RADEON_TV_ON;
			अन्यथा
				crtc2_gen_cntl &= ~RADEON_CRTC2_CRT2_ON;

			अगर (rdev->family == CHIP_R420 ||
			    rdev->family == CHIP_R423 ||
			    rdev->family == CHIP_RV410)
				tv_dac_cntl |= (R420_TV_DAC_RDACPD |
						R420_TV_DAC_GDACPD |
						R420_TV_DAC_BDACPD |
						RADEON_TV_DAC_BGSLEEP);
			अन्यथा
				tv_dac_cntl |= (RADEON_TV_DAC_RDACPD |
						RADEON_TV_DAC_GDACPD |
						RADEON_TV_DAC_BDACPD |
						RADEON_TV_DAC_BGSLEEP);
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (rdev->family == CHIP_R200) अणु
		WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);
	पूर्ण अन्यथा अणु
		अगर (is_tv)
			WREG32(RADEON_TV_MASTER_CNTL, tv_master_cntl);
		/* handled in radeon_crtc_dpms() */
		अन्यथा अगर (!(rdev->flags & RADEON_SINGLE_CRTC))
			WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
		WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
	पूर्ण

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);
	अन्यथा
		radeon_combios_encoder_dpms_scratch_regs(encoder, (mode == DRM_MODE_DPMS_ON) ? true : false);

पूर्ण

अटल व्योम radeon_legacy_tv_dac_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	अन्यथा
		radeon_combios_output_lock(encoder, true);
	radeon_legacy_tv_dac_dpms(encoder, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम radeon_legacy_tv_dac_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा radeon_device *rdev = encoder->dev->dev_निजी;

	radeon_legacy_tv_dac_dpms(encoder, DRM_MODE_DPMS_ON);

	अगर (rdev->is_atom_bios)
		radeon_atom_output_lock(encoder, true);
	अन्यथा
		radeon_combios_output_lock(encoder, true);
पूर्ण

अटल व्योम radeon_legacy_tv_dac_mode_set(काष्ठा drm_encoder *encoder,
		काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	uपूर्णांक32_t tv_dac_cntl, gpiopad_a = 0, dac2_cntl, disp_output_cntl = 0;
	uपूर्णांक32_t disp_hw_debug = 0, fp2_gen_cntl = 0, disp_tv_out_cntl = 0;
	bool is_tv = false;

	DRM_DEBUG_KMS("\n");

	is_tv = radeon_encoder->active_device & ATOM_DEVICE_TV_SUPPORT ? true : false;

	अगर (rdev->family != CHIP_R200) अणु
		tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
		अगर (rdev->family == CHIP_R420 ||
		    rdev->family == CHIP_R423 ||
		    rdev->family == CHIP_RV410) अणु
			tv_dac_cntl &= ~(RADEON_TV_DAC_STD_MASK |
					 RADEON_TV_DAC_BGADJ_MASK |
					 R420_TV_DAC_DACADJ_MASK |
					 R420_TV_DAC_RDACPD |
					 R420_TV_DAC_GDACPD |
					 R420_TV_DAC_BDACPD |
					 R420_TV_DAC_TVENABLE);
		पूर्ण अन्यथा अणु
			tv_dac_cntl &= ~(RADEON_TV_DAC_STD_MASK |
					 RADEON_TV_DAC_BGADJ_MASK |
					 RADEON_TV_DAC_DACADJ_MASK |
					 RADEON_TV_DAC_RDACPD |
					 RADEON_TV_DAC_GDACPD |
					 RADEON_TV_DAC_BDACPD);
		पूर्ण

		tv_dac_cntl |= RADEON_TV_DAC_NBLANK | RADEON_TV_DAC_NHOLD;

		अगर (is_tv) अणु
			अगर (tv_dac->tv_std == TV_STD_NTSC ||
			    tv_dac->tv_std == TV_STD_NTSC_J ||
			    tv_dac->tv_std == TV_STD_PAL_M ||
			    tv_dac->tv_std == TV_STD_PAL_60)
				tv_dac_cntl |= tv_dac->ntsc_tvdac_adj;
			अन्यथा
				tv_dac_cntl |= tv_dac->pal_tvdac_adj;

			अगर (tv_dac->tv_std == TV_STD_NTSC ||
			    tv_dac->tv_std == TV_STD_NTSC_J)
				tv_dac_cntl |= RADEON_TV_DAC_STD_NTSC;
			अन्यथा
				tv_dac_cntl |= RADEON_TV_DAC_STD_PAL;
		पूर्ण अन्यथा
			tv_dac_cntl |= (RADEON_TV_DAC_STD_PS2 |
					tv_dac->ps2_tvdac_adj);

		WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
	पूर्ण

	अगर (ASIC_IS_R300(rdev)) अणु
		gpiopad_a = RREG32(RADEON_GPIOPAD_A) | 1;
		disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL);
	पूर्ण अन्यथा अगर (rdev->family != CHIP_R200)
		disp_hw_debug = RREG32(RADEON_DISP_HW_DEBUG);
	अन्यथा अगर (rdev->family == CHIP_R200)
		fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);

	अगर (rdev->family >= CHIP_R200)
		disp_tv_out_cntl = RREG32(RADEON_DISP_TV_OUT_CNTL);

	अगर (is_tv) अणु
		uपूर्णांक32_t dac_cntl;

		dac_cntl = RREG32(RADEON_DAC_CNTL);
		dac_cntl &= ~RADEON_DAC_TVO_EN;
		WREG32(RADEON_DAC_CNTL, dac_cntl);

		अगर (ASIC_IS_R300(rdev))
			gpiopad_a = RREG32(RADEON_GPIOPAD_A) & ~1;

		dac2_cntl = RREG32(RADEON_DAC_CNTL2) & ~RADEON_DAC2_DAC2_CLK_SEL;
		अगर (radeon_crtc->crtc_id == 0) अणु
			अगर (ASIC_IS_R300(rdev)) अणु
				disp_output_cntl &= ~RADEON_DISP_TVDAC_SOURCE_MASK;
				disp_output_cntl |= (RADEON_DISP_TVDAC_SOURCE_CRTC |
						     RADEON_DISP_TV_SOURCE_CRTC);
			पूर्ण
			अगर (rdev->family >= CHIP_R200) अणु
				disp_tv_out_cntl &= ~RADEON_DISP_TV_PATH_SRC_CRTC2;
			पूर्ण अन्यथा अणु
				disp_hw_debug |= RADEON_CRT2_DISP1_SEL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (ASIC_IS_R300(rdev)) अणु
				disp_output_cntl &= ~RADEON_DISP_TVDAC_SOURCE_MASK;
				disp_output_cntl |= RADEON_DISP_TV_SOURCE_CRTC;
			पूर्ण
			अगर (rdev->family >= CHIP_R200) अणु
				disp_tv_out_cntl |= RADEON_DISP_TV_PATH_SRC_CRTC2;
			पूर्ण अन्यथा अणु
				disp_hw_debug &= ~RADEON_CRT2_DISP1_SEL;
			पूर्ण
		पूर्ण
		WREG32(RADEON_DAC_CNTL2, dac2_cntl);
	पूर्ण अन्यथा अणु

		dac2_cntl = RREG32(RADEON_DAC_CNTL2) | RADEON_DAC2_DAC2_CLK_SEL;

		अगर (radeon_crtc->crtc_id == 0) अणु
			अगर (ASIC_IS_R300(rdev)) अणु
				disp_output_cntl &= ~RADEON_DISP_TVDAC_SOURCE_MASK;
				disp_output_cntl |= RADEON_DISP_TVDAC_SOURCE_CRTC;
			पूर्ण अन्यथा अगर (rdev->family == CHIP_R200) अणु
				fp2_gen_cntl &= ~(R200_FP2_SOURCE_SEL_MASK |
						  RADEON_FP2_DVO_RATE_SEL_SDR);
			पूर्ण अन्यथा
				disp_hw_debug |= RADEON_CRT2_DISP1_SEL;
		पूर्ण अन्यथा अणु
			अगर (ASIC_IS_R300(rdev)) अणु
				disp_output_cntl &= ~RADEON_DISP_TVDAC_SOURCE_MASK;
				disp_output_cntl |= RADEON_DISP_TVDAC_SOURCE_CRTC2;
			पूर्ण अन्यथा अगर (rdev->family == CHIP_R200) अणु
				fp2_gen_cntl &= ~(R200_FP2_SOURCE_SEL_MASK |
						  RADEON_FP2_DVO_RATE_SEL_SDR);
				fp2_gen_cntl |= R200_FP2_SOURCE_SEL_CRTC2;
			पूर्ण अन्यथा
				disp_hw_debug &= ~RADEON_CRT2_DISP1_SEL;
		पूर्ण
		WREG32(RADEON_DAC_CNTL2, dac2_cntl);
	पूर्ण

	अगर (ASIC_IS_R300(rdev)) अणु
		WREG32_P(RADEON_GPIOPAD_A, gpiopad_a, ~1);
		WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
	पूर्ण अन्यथा अगर (rdev->family != CHIP_R200)
		WREG32(RADEON_DISP_HW_DEBUG, disp_hw_debug);
	अन्यथा अगर (rdev->family == CHIP_R200)
		WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);

	अगर (rdev->family >= CHIP_R200)
		WREG32(RADEON_DISP_TV_OUT_CNTL, disp_tv_out_cntl);

	अगर (is_tv)
		radeon_legacy_tv_mode_set(encoder, mode, adjusted_mode);

	अगर (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	अन्यथा
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);

पूर्ण

अटल bool r300_legacy_tv_detect(काष्ठा drm_encoder *encoder,
				  काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t crtc2_gen_cntl, tv_dac_cntl, dac_cntl2, dac_ext_cntl;
	uपूर्णांक32_t disp_output_cntl, gpiopad_a, पंचांगp;
	bool found = false;

	/* save regs needed */
	gpiopad_a = RREG32(RADEON_GPIOPAD_A);
	dac_cntl2 = RREG32(RADEON_DAC_CNTL2);
	crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
	dac_ext_cntl = RREG32(RADEON_DAC_EXT_CNTL);
	tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
	disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL);

	WREG32_P(RADEON_GPIOPAD_A, 0, ~1);

	WREG32(RADEON_DAC_CNTL2, RADEON_DAC2_DAC2_CLK_SEL);

	WREG32(RADEON_CRTC2_GEN_CNTL,
	       RADEON_CRTC2_CRT2_ON | RADEON_CRTC2_VSYNC_TRISTAT);

	पंचांगp = disp_output_cntl & ~RADEON_DISP_TVDAC_SOURCE_MASK;
	पंचांगp |= RADEON_DISP_TVDAC_SOURCE_CRTC2;
	WREG32(RADEON_DISP_OUTPUT_CNTL, पंचांगp);

	WREG32(RADEON_DAC_EXT_CNTL,
	       RADEON_DAC2_FORCE_BLANK_OFF_EN |
	       RADEON_DAC2_FORCE_DATA_EN |
	       RADEON_DAC_FORCE_DATA_SEL_RGB |
	       (0xec << RADEON_DAC_FORCE_DATA_SHIFT));

	WREG32(RADEON_TV_DAC_CNTL,
	       RADEON_TV_DAC_STD_NTSC |
	       (8 << RADEON_TV_DAC_BGADJ_SHIFT) |
	       (6 << RADEON_TV_DAC_DACADJ_SHIFT));

	RREG32(RADEON_TV_DAC_CNTL);
	mdelay(4);

	WREG32(RADEON_TV_DAC_CNTL,
	       RADEON_TV_DAC_NBLANK |
	       RADEON_TV_DAC_NHOLD |
	       RADEON_TV_MONITOR_DETECT_EN |
	       RADEON_TV_DAC_STD_NTSC |
	       (8 << RADEON_TV_DAC_BGADJ_SHIFT) |
	       (6 << RADEON_TV_DAC_DACADJ_SHIFT));

	RREG32(RADEON_TV_DAC_CNTL);
	mdelay(6);

	पंचांगp = RREG32(RADEON_TV_DAC_CNTL);
	अगर ((पंचांगp & RADEON_TV_DAC_GDACDET) != 0) अणु
		found = true;
		DRM_DEBUG_KMS("S-video TV connection detected\n");
	पूर्ण अन्यथा अगर ((पंचांगp & RADEON_TV_DAC_BDACDET) != 0) अणु
		found = true;
		DRM_DEBUG_KMS("Composite TV connection detected\n");
	पूर्ण

	WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
	WREG32(RADEON_DAC_EXT_CNTL, dac_ext_cntl);
	WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
	WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
	WREG32(RADEON_DAC_CNTL2, dac_cntl2);
	WREG32_P(RADEON_GPIOPAD_A, gpiopad_a, ~1);
	वापस found;
पूर्ण

अटल bool radeon_legacy_tv_detect(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t tv_dac_cntl, dac_cntl2;
	uपूर्णांक32_t config_cntl, tv_pre_dac_mux_cntl, tv_master_cntl, पंचांगp;
	bool found = false;

	अगर (ASIC_IS_R300(rdev))
		वापस r300_legacy_tv_detect(encoder, connector);

	dac_cntl2 = RREG32(RADEON_DAC_CNTL2);
	tv_master_cntl = RREG32(RADEON_TV_MASTER_CNTL);
	tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
	config_cntl = RREG32(RADEON_CONFIG_CNTL);
	tv_pre_dac_mux_cntl = RREG32(RADEON_TV_PRE_DAC_MUX_CNTL);

	पंचांगp = dac_cntl2 & ~RADEON_DAC2_DAC2_CLK_SEL;
	WREG32(RADEON_DAC_CNTL2, पंचांगp);

	पंचांगp = tv_master_cntl | RADEON_TV_ON;
	पंचांगp &= ~(RADEON_TV_ASYNC_RST |
		 RADEON_RESTART_PHASE_FIX |
		 RADEON_CRT_FIFO_CE_EN |
		 RADEON_TV_FIFO_CE_EN |
		 RADEON_RE_SYNC_NOW_SEL_MASK);
	पंचांगp |= RADEON_TV_FIFO_ASYNC_RST | RADEON_CRT_ASYNC_RST;
	WREG32(RADEON_TV_MASTER_CNTL, पंचांगp);

	पंचांगp = RADEON_TV_DAC_NBLANK | RADEON_TV_DAC_NHOLD |
		RADEON_TV_MONITOR_DETECT_EN | RADEON_TV_DAC_STD_NTSC |
		(8 << RADEON_TV_DAC_BGADJ_SHIFT);

	अगर (config_cntl & RADEON_CFG_ATI_REV_ID_MASK)
		पंचांगp |= (4 << RADEON_TV_DAC_DACADJ_SHIFT);
	अन्यथा
		पंचांगp |= (8 << RADEON_TV_DAC_DACADJ_SHIFT);
	WREG32(RADEON_TV_DAC_CNTL, पंचांगp);

	पंचांगp = RADEON_C_GRN_EN | RADEON_CMP_BLU_EN |
		RADEON_RED_MX_FORCE_DAC_DATA |
		RADEON_GRN_MX_FORCE_DAC_DATA |
		RADEON_BLU_MX_FORCE_DAC_DATA |
		(0x109 << RADEON_TV_FORCE_DAC_DATA_SHIFT);
	WREG32(RADEON_TV_PRE_DAC_MUX_CNTL, पंचांगp);

	mdelay(3);
	पंचांगp = RREG32(RADEON_TV_DAC_CNTL);
	अगर (पंचांगp & RADEON_TV_DAC_GDACDET) अणु
		found = true;
		DRM_DEBUG_KMS("S-video TV connection detected\n");
	पूर्ण अन्यथा अगर ((पंचांगp & RADEON_TV_DAC_BDACDET) != 0) अणु
		found = true;
		DRM_DEBUG_KMS("Composite TV connection detected\n");
	पूर्ण

	WREG32(RADEON_TV_PRE_DAC_MUX_CNTL, tv_pre_dac_mux_cntl);
	WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);
	WREG32(RADEON_TV_MASTER_CNTL, tv_master_cntl);
	WREG32(RADEON_DAC_CNTL2, dac_cntl2);
	वापस found;
पूर्ण

अटल bool radeon_legacy_ext_dac_detect(काष्ठा drm_encoder *encoder,
					 काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t gpio_monid, fp2_gen_cntl, disp_output_cntl, crtc2_gen_cntl;
	uपूर्णांक32_t disp_lin_trans_grph_a, disp_lin_trans_grph_b, disp_lin_trans_grph_c;
	uपूर्णांक32_t disp_lin_trans_grph_d, disp_lin_trans_grph_e, disp_lin_trans_grph_f;
	uपूर्णांक32_t पंचांगp, crtc2_h_total_disp, crtc2_v_total_disp;
	uपूर्णांक32_t crtc2_h_sync_strt_wid, crtc2_v_sync_strt_wid;
	bool found = false;
	पूर्णांक i;

	/* save the regs we need */
	gpio_monid = RREG32(RADEON_GPIO_MONID);
	fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);
	disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL);
	crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
	disp_lin_trans_grph_a = RREG32(RADEON_DISP_LIN_TRANS_GRPH_A);
	disp_lin_trans_grph_b = RREG32(RADEON_DISP_LIN_TRANS_GRPH_B);
	disp_lin_trans_grph_c = RREG32(RADEON_DISP_LIN_TRANS_GRPH_C);
	disp_lin_trans_grph_d = RREG32(RADEON_DISP_LIN_TRANS_GRPH_D);
	disp_lin_trans_grph_e = RREG32(RADEON_DISP_LIN_TRANS_GRPH_E);
	disp_lin_trans_grph_f = RREG32(RADEON_DISP_LIN_TRANS_GRPH_F);
	crtc2_h_total_disp = RREG32(RADEON_CRTC2_H_TOTAL_DISP);
	crtc2_v_total_disp = RREG32(RADEON_CRTC2_V_TOTAL_DISP);
	crtc2_h_sync_strt_wid = RREG32(RADEON_CRTC2_H_SYNC_STRT_WID);
	crtc2_v_sync_strt_wid = RREG32(RADEON_CRTC2_V_SYNC_STRT_WID);

	पंचांगp = RREG32(RADEON_GPIO_MONID);
	पंचांगp &= ~RADEON_GPIO_A_0;
	WREG32(RADEON_GPIO_MONID, पंचांगp);

	WREG32(RADEON_FP2_GEN_CNTL, (RADEON_FP2_ON |
				     RADEON_FP2_PANEL_FORMAT |
				     R200_FP2_SOURCE_SEL_TRANS_UNIT |
				     RADEON_FP2_DVO_EN |
				     R200_FP2_DVO_RATE_SEL_SDR));

	WREG32(RADEON_DISP_OUTPUT_CNTL, (RADEON_DISP_DAC_SOURCE_RMX |
					 RADEON_DISP_TRANS_MATRIX_GRAPHICS));

	WREG32(RADEON_CRTC2_GEN_CNTL, (RADEON_CRTC2_EN |
				       RADEON_CRTC2_DISP_REQ_EN_B));

	WREG32(RADEON_DISP_LIN_TRANS_GRPH_A, 0x00000000);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_B, 0x000003f0);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_C, 0x00000000);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_D, 0x000003f0);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_E, 0x00000000);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_F, 0x000003f0);

	WREG32(RADEON_CRTC2_H_TOTAL_DISP, 0x01000008);
	WREG32(RADEON_CRTC2_H_SYNC_STRT_WID, 0x00000800);
	WREG32(RADEON_CRTC2_V_TOTAL_DISP, 0x00080001);
	WREG32(RADEON_CRTC2_V_SYNC_STRT_WID, 0x00000080);

	क्रम (i = 0; i < 200; i++) अणु
		पंचांगp = RREG32(RADEON_GPIO_MONID);
		अगर (पंचांगp & RADEON_GPIO_Y_0)
			found = true;

		अगर (found)
			अवरोध;

		अगर (!drm_can_sleep())
			mdelay(1);
		अन्यथा
			msleep(1);
	पूर्ण

	/* restore the regs we used */
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_A, disp_lin_trans_grph_a);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_B, disp_lin_trans_grph_b);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_C, disp_lin_trans_grph_c);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_D, disp_lin_trans_grph_d);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_E, disp_lin_trans_grph_e);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_F, disp_lin_trans_grph_f);
	WREG32(RADEON_CRTC2_H_TOTAL_DISP, crtc2_h_total_disp);
	WREG32(RADEON_CRTC2_V_TOTAL_DISP, crtc2_v_total_disp);
	WREG32(RADEON_CRTC2_H_SYNC_STRT_WID, crtc2_h_sync_strt_wid);
	WREG32(RADEON_CRTC2_V_SYNC_STRT_WID, crtc2_v_sync_strt_wid);
	WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
	WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
	WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);
	WREG32(RADEON_GPIO_MONID, gpio_monid);

	वापस found;
पूर्ण

अटल क्रमागत drm_connector_status radeon_legacy_tv_dac_detect(काष्ठा drm_encoder *encoder,
							     काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	uपूर्णांक32_t crtc2_gen_cntl = 0, tv_dac_cntl, dac_cntl2, dac_ext_cntl;
	uपूर्णांक32_t gpiopad_a = 0, pixclks_cntl, पंचांगp;
	uपूर्णांक32_t disp_output_cntl = 0, disp_hw_debug = 0, crtc_ext_cntl = 0;
	क्रमागत drm_connector_status found = connector_status_disconnected;
	काष्ठा radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	काष्ठा radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	bool color = true;
	काष्ठा drm_crtc *crtc;

	/* find out अगर crtc2 is in use or अगर this encoder is using it */
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
		अगर ((radeon_crtc->crtc_id == 1) && crtc->enabled) अणु
			अगर (encoder->crtc != crtc) अणु
				वापस connector_status_disconnected;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (connector->connector_type == DRM_MODE_CONNECTOR_SVIDEO ||
	    connector->connector_type == DRM_MODE_CONNECTOR_Composite ||
	    connector->connector_type == DRM_MODE_CONNECTOR_9PinDIN) अणु
		bool tv_detect;

		अगर (radeon_encoder->active_device && !(radeon_encoder->active_device & ATOM_DEVICE_TV_SUPPORT))
			वापस connector_status_disconnected;

		tv_detect = radeon_legacy_tv_detect(encoder, connector);
		अगर (tv_detect && tv_dac)
			found = connector_status_connected;
		वापस found;
	पूर्ण

	/* करोn't probe अगर the encoder is being used क्रम something अन्यथा not CRT related */
	अगर (radeon_encoder->active_device && !(radeon_encoder->active_device & ATOM_DEVICE_CRT_SUPPORT)) अणु
		DRM_INFO("not detecting due to %08x\n", radeon_encoder->active_device);
		वापस connector_status_disconnected;
	पूर्ण

	/* R200 uses an बाह्यal DAC क्रम secondary DAC */
	अगर (rdev->family == CHIP_R200) अणु
		अगर (radeon_legacy_ext_dac_detect(encoder, connector))
			found = connector_status_connected;
		वापस found;
	पूर्ण

	/* save the regs we need */
	pixclks_cntl = RREG32_PLL(RADEON_PIXCLKS_CNTL);

	अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
		crtc_ext_cntl = RREG32(RADEON_CRTC_EXT_CNTL);
	पूर्ण अन्यथा अणु
		अगर (ASIC_IS_R300(rdev)) अणु
			gpiopad_a = RREG32(RADEON_GPIOPAD_A);
			disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL);
		पूर्ण अन्यथा अणु
			disp_hw_debug = RREG32(RADEON_DISP_HW_DEBUG);
		पूर्ण
		crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
	पूर्ण
	tv_dac_cntl = RREG32(RADEON_TV_DAC_CNTL);
	dac_ext_cntl = RREG32(RADEON_DAC_EXT_CNTL);
	dac_cntl2 = RREG32(RADEON_DAC_CNTL2);

	पंचांगp = pixclks_cntl & ~(RADEON_PIX2CLK_ALWAYS_ONb
			       | RADEON_PIX2CLK_DAC_ALWAYS_ONb);
	WREG32_PLL(RADEON_PIXCLKS_CNTL, पंचांगp);

	अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
		पंचांगp = crtc_ext_cntl | RADEON_CRTC_CRT_ON;
		WREG32(RADEON_CRTC_EXT_CNTL, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = crtc2_gen_cntl & ~RADEON_CRTC2_PIX_WIDTH_MASK;
		पंचांगp |= RADEON_CRTC2_CRT2_ON |
			(2 << RADEON_CRTC2_PIX_WIDTH_SHIFT);
		WREG32(RADEON_CRTC2_GEN_CNTL, पंचांगp);

		अगर (ASIC_IS_R300(rdev)) अणु
			WREG32_P(RADEON_GPIOPAD_A, 1, ~1);
			पंचांगp = disp_output_cntl & ~RADEON_DISP_TVDAC_SOURCE_MASK;
			पंचांगp |= RADEON_DISP_TVDAC_SOURCE_CRTC2;
			WREG32(RADEON_DISP_OUTPUT_CNTL, पंचांगp);
		पूर्ण अन्यथा अणु
			पंचांगp = disp_hw_debug & ~RADEON_CRT2_DISP1_SEL;
			WREG32(RADEON_DISP_HW_DEBUG, पंचांगp);
		पूर्ण
	पूर्ण

	पंचांगp = RADEON_TV_DAC_NBLANK |
		RADEON_TV_DAC_NHOLD |
		RADEON_TV_MONITOR_DETECT_EN |
		RADEON_TV_DAC_STD_PS2;

	WREG32(RADEON_TV_DAC_CNTL, पंचांगp);

	पंचांगp = RADEON_DAC2_FORCE_BLANK_OFF_EN |
		RADEON_DAC2_FORCE_DATA_EN;

	अगर (color)
		पंचांगp |= RADEON_DAC_FORCE_DATA_SEL_RGB;
	अन्यथा
		पंचांगp |= RADEON_DAC_FORCE_DATA_SEL_G;

	अगर (ASIC_IS_R300(rdev))
		पंचांगp |= (0x1b6 << RADEON_DAC_FORCE_DATA_SHIFT);
	अन्यथा
		पंचांगp |= (0x180 << RADEON_DAC_FORCE_DATA_SHIFT);

	WREG32(RADEON_DAC_EXT_CNTL, पंचांगp);

	पंचांगp = dac_cntl2 | RADEON_DAC2_DAC2_CLK_SEL | RADEON_DAC2_CMP_EN;
	WREG32(RADEON_DAC_CNTL2, पंचांगp);

	mdelay(10);

	अगर (ASIC_IS_R300(rdev)) अणु
		अगर (RREG32(RADEON_DAC_CNTL2) & RADEON_DAC2_CMP_OUT_B)
			found = connector_status_connected;
	पूर्ण अन्यथा अणु
		अगर (RREG32(RADEON_DAC_CNTL2) & RADEON_DAC2_CMP_OUTPUT)
			found = connector_status_connected;
	पूर्ण

	/* restore regs we used */
	WREG32(RADEON_DAC_CNTL2, dac_cntl2);
	WREG32(RADEON_DAC_EXT_CNTL, dac_ext_cntl);
	WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);

	अगर (rdev->flags & RADEON_SINGLE_CRTC) अणु
		WREG32(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl);
	पूर्ण अन्यथा अणु
		WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
		अगर (ASIC_IS_R300(rdev)) अणु
			WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
			WREG32_P(RADEON_GPIOPAD_A, gpiopad_a, ~1);
		पूर्ण अन्यथा अणु
			WREG32(RADEON_DISP_HW_DEBUG, disp_hw_debug);
		पूर्ण
	पूर्ण

	WREG32_PLL(RADEON_PIXCLKS_CNTL, pixclks_cntl);

	वापस found;

पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs radeon_legacy_tv_dac_helper_funcs = अणु
	.dpms = radeon_legacy_tv_dac_dpms,
	.mode_fixup = radeon_legacy_mode_fixup,
	.prepare = radeon_legacy_tv_dac_prepare,
	.mode_set = radeon_legacy_tv_dac_mode_set,
	.commit = radeon_legacy_tv_dac_commit,
	.detect = radeon_legacy_tv_dac_detect,
	.disable = radeon_legacy_encoder_disable,
पूर्ण;


अटल स्थिर काष्ठा drm_encoder_funcs radeon_legacy_tv_dac_enc_funcs = अणु
	.destroy = radeon_enc_destroy,
पूर्ण;


अटल काष्ठा radeon_encoder_पूर्णांक_पंचांगds *radeon_legacy_get_पंचांगds_info(काष्ठा radeon_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds = शून्य;
	bool ret;

	पंचांगds = kzalloc(माप(काष्ठा radeon_encoder_पूर्णांक_पंचांगds), GFP_KERNEL);

	अगर (!पंचांगds)
		वापस शून्य;

	अगर (rdev->is_atom_bios)
		ret = radeon_atombios_get_पंचांगds_info(encoder, पंचांगds);
	अन्यथा
		ret = radeon_legacy_get_पंचांगds_info_from_combios(encoder, पंचांगds);

	अगर (!ret)
		radeon_legacy_get_पंचांगds_info_from_table(encoder, पंचांगds);

	वापस पंचांगds;
पूर्ण

अटल काष्ठा radeon_encoder_ext_पंचांगds *radeon_legacy_get_ext_पंचांगds_info(काष्ठा radeon_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_encoder_ext_पंचांगds *पंचांगds = शून्य;
	bool ret;

	अगर (rdev->is_atom_bios)
		वापस शून्य;

	पंचांगds = kzalloc(माप(काष्ठा radeon_encoder_ext_पंचांगds), GFP_KERNEL);

	अगर (!पंचांगds)
		वापस शून्य;

	ret = radeon_legacy_get_ext_पंचांगds_info_from_combios(encoder, पंचांगds);

	अगर (!ret)
		radeon_legacy_get_ext_पंचांगds_info_from_table(encoder, पंचांगds);

	वापस पंचांगds;
पूर्ण

व्योम
radeon_add_legacy_encoder(काष्ठा drm_device *dev, uपूर्णांक32_t encoder_क्रमागत, uपूर्णांक32_t supported_device)
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
	अगर (rdev->flags & RADEON_SINGLE_CRTC)
		encoder->possible_crtcs = 0x1;
	अन्यथा
		encoder->possible_crtcs = 0x3;

	radeon_encoder->enc_priv = शून्य;

	radeon_encoder->encoder_क्रमागत = encoder_क्रमागत;
	radeon_encoder->encoder_id = (encoder_क्रमागत & OBJECT_ID_MASK) >> OBJECT_ID_SHIFT;
	radeon_encoder->devices = supported_device;
	radeon_encoder->rmx_type = RMX_OFF;

	चयन (radeon_encoder->encoder_id) अणु
	हाल ENCODER_OBJECT_ID_INTERNAL_LVDS:
		encoder->possible_crtcs = 0x1;
		drm_encoder_init(dev, encoder, &radeon_legacy_lvds_enc_funcs,
				 DRM_MODE_ENCODER_LVDS, शून्य);
		drm_encoder_helper_add(encoder, &radeon_legacy_lvds_helper_funcs);
		अगर (rdev->is_atom_bios)
			radeon_encoder->enc_priv = radeon_atombios_get_lvds_info(radeon_encoder);
		अन्यथा
			radeon_encoder->enc_priv = radeon_combios_get_lvds_info(radeon_encoder);
		radeon_encoder->rmx_type = RMX_FULL;
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_TMDS1:
		drm_encoder_init(dev, encoder, &radeon_legacy_पंचांगds_पूर्णांक_enc_funcs,
				 DRM_MODE_ENCODER_TMDS, शून्य);
		drm_encoder_helper_add(encoder, &radeon_legacy_पंचांगds_पूर्णांक_helper_funcs);
		radeon_encoder->enc_priv = radeon_legacy_get_पंचांगds_info(radeon_encoder);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC1:
		drm_encoder_init(dev, encoder, &radeon_legacy_primary_dac_enc_funcs,
				 DRM_MODE_ENCODER_DAC, शून्य);
		drm_encoder_helper_add(encoder, &radeon_legacy_primary_dac_helper_funcs);
		अगर (rdev->is_atom_bios)
			radeon_encoder->enc_priv = radeon_atombios_get_primary_dac_info(radeon_encoder);
		अन्यथा
			radeon_encoder->enc_priv = radeon_combios_get_primary_dac_info(radeon_encoder);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DAC2:
		drm_encoder_init(dev, encoder, &radeon_legacy_tv_dac_enc_funcs,
				 DRM_MODE_ENCODER_TVDAC, शून्य);
		drm_encoder_helper_add(encoder, &radeon_legacy_tv_dac_helper_funcs);
		अगर (rdev->is_atom_bios)
			radeon_encoder->enc_priv = radeon_atombios_get_tv_dac_info(radeon_encoder);
		अन्यथा
			radeon_encoder->enc_priv = radeon_combios_get_tv_dac_info(radeon_encoder);
		अवरोध;
	हाल ENCODER_OBJECT_ID_INTERNAL_DVO1:
		drm_encoder_init(dev, encoder, &radeon_legacy_पंचांगds_ext_enc_funcs,
				 DRM_MODE_ENCODER_TMDS, शून्य);
		drm_encoder_helper_add(encoder, &radeon_legacy_पंचांगds_ext_helper_funcs);
		अगर (!rdev->is_atom_bios)
			radeon_encoder->enc_priv = radeon_legacy_get_ext_पंचांगds_info(radeon_encoder);
		अवरोध;
	पूर्ण
पूर्ण
