<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**************************************************************************
 * Copyright (c) 2011, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#समावेश <linux/backlight.h>

#समावेश <drm/drm.h>

#समावेश "gma_device.h"
#समावेश "intel_bios.h"
#समावेश "psb_device.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_reg.h"
#समावेश "psb_reg.h"

अटल पूर्णांक psb_output_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	psb_पूर्णांकel_lvds_init(dev, &dev_priv->mode_dev);
	psb_पूर्णांकel_sdvo_init(dev, SDVOB);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE

/*
 *	Poulsbo Backlight Interfaces
 */

#घोषणा BLC_PWM_PRECISION_FACTOR 100	/* 10000000 */
#घोषणा BLC_PWM_FREQ_CALC_CONSTANT 32
#घोषणा MHz 1000000

#घोषणा PSB_BLC_PWM_PRECISION_FACTOR    10
#घोषणा PSB_BLC_MAX_PWM_REG_FREQ        0xFFFE
#घोषणा PSB_BLC_MIN_PWM_REG_FREQ        0x2

#घोषणा PSB_BACKLIGHT_PWM_POLARITY_BIT_CLEAR (0xFFFE)
#घोषणा PSB_BACKLIGHT_PWM_CTL_SHIFT	(16)

अटल पूर्णांक psb_brightness;
अटल काष्ठा backlight_device *psb_backlight_device;

अटल पूर्णांक psb_get_brightness(काष्ठा backlight_device *bd)
अणु
	/* वापस locally cached var instead of HW पढ़ो (due to DPST etc.) */
	/* FIXME: ideally वापस actual value in हाल firmware fiddled with
	   it */
	वापस psb_brightness;
पूर्ण


अटल पूर्णांक psb_backlight_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	अचिन्हित दीर्घ core_घड़ी;
	/* u32 bl_max_freq; */
	/* अचिन्हित दीर्घ value; */
	u16 bl_max_freq;
	uपूर्णांक32_t value;
	uपूर्णांक32_t blc_pwm_precision_factor;

	/* get bl_max_freq and pol from dev_priv*/
	अगर (!dev_priv->lvds_bl) अणु
		dev_err(dev->dev, "Has no valid LVDS backlight info\n");
		वापस -ENOENT;
	पूर्ण
	bl_max_freq = dev_priv->lvds_bl->freq;
	blc_pwm_precision_factor = PSB_BLC_PWM_PRECISION_FACTOR;

	core_घड़ी = dev_priv->core_freq;

	value = (core_घड़ी * MHz) / BLC_PWM_FREQ_CALC_CONSTANT;
	value *= blc_pwm_precision_factor;
	value /= bl_max_freq;
	value /= blc_pwm_precision_factor;

	अगर (value > (अचिन्हित दीर्घ दीर्घ)PSB_BLC_MAX_PWM_REG_FREQ ||
		 value < (अचिन्हित दीर्घ दीर्घ)PSB_BLC_MIN_PWM_REG_FREQ)
				वापस -दुस्फल;
	अन्यथा अणु
		value &= PSB_BACKLIGHT_PWM_POLARITY_BIT_CLEAR;
		REG_WRITE(BLC_PWM_CTL,
			(value << PSB_BACKLIGHT_PWM_CTL_SHIFT) | (value));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक psb_set_brightness(काष्ठा backlight_device *bd)
अणु
	काष्ठा drm_device *dev = bl_get_data(psb_backlight_device);
	पूर्णांक level = bd->props.brightness;

	/* Percentage 1-100% being valid */
	अगर (level < 1)
		level = 1;

	psb_पूर्णांकel_lvds_set_brightness(dev, level);
	psb_brightness = level;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops psb_ops = अणु
	.get_brightness = psb_get_brightness,
	.update_status  = psb_set_brightness,
पूर्ण;

अटल पूर्णांक psb_backlight_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक ret;
	काष्ठा backlight_properties props;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.max_brightness = 100;
	props.type = BACKLIGHT_PLATFORM;

	psb_backlight_device = backlight_device_रेजिस्टर("psb-bl",
					शून्य, (व्योम *)dev, &psb_ops, &props);
	अगर (IS_ERR(psb_backlight_device))
		वापस PTR_ERR(psb_backlight_device);

	ret = psb_backlight_setup(dev);
	अगर (ret < 0) अणु
		backlight_device_unरेजिस्टर(psb_backlight_device);
		psb_backlight_device = शून्य;
		वापस ret;
	पूर्ण
	psb_backlight_device->props.brightness = 100;
	psb_backlight_device->props.max_brightness = 100;
	backlight_update_status(psb_backlight_device);
	dev_priv->backlight_device = psb_backlight_device;

	/* This must occur after the backlight is properly initialised */
	psb_lid_समयr_init(dev_priv);

	वापस 0;
पूर्ण

#पूर्ण_अगर

/*
 *	Provide the Poulsbo specअगरic chip logic and low level methods
 *	क्रम घातer management
 */

अटल व्योम psb_init_pm(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	u32 gating = PSB_RSGX32(PSB_CR_CLKGATECTL);
	gating &= ~3;	/* Disable 2D घड़ी gating */
	gating |= 1;
	PSB_WSGX32(gating, PSB_CR_CLKGATECTL);
	PSB_RSGX32(PSB_CR_CLKGATECTL);
पूर्ण

/**
 *	psb_save_display_रेजिस्टरs	-	save रेजिस्टरs lost on suspend
 *	@dev: our DRM device
 *
 *	Save the state we need in order to be able to restore the पूर्णांकerface
 *	upon resume from suspend
 */
अटल पूर्णांक psb_save_display_रेजिस्टरs(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_crtc *crtc;
	काष्ठा gma_connector *connector;
	काष्ठा psb_state *regs = &dev_priv->regs.psb;

	/* Display arbitration control + watermarks */
	regs->saveDSPARB = PSB_RVDC32(DSPARB);
	regs->saveDSPFW1 = PSB_RVDC32(DSPFW1);
	regs->saveDSPFW2 = PSB_RVDC32(DSPFW2);
	regs->saveDSPFW3 = PSB_RVDC32(DSPFW3);
	regs->saveDSPFW4 = PSB_RVDC32(DSPFW4);
	regs->saveDSPFW5 = PSB_RVDC32(DSPFW5);
	regs->saveDSPFW6 = PSB_RVDC32(DSPFW6);
	regs->saveCHICKENBIT = PSB_RVDC32(DSPCHICKENBIT);

	/* Save crtc and output state */
	drm_modeset_lock_all(dev);
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		अगर (drm_helper_crtc_in_use(crtc))
			dev_priv->ops->save_crtc(crtc);
	पूर्ण

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, base.head)
		अगर (connector->save)
			connector->save(&connector->base);

	drm_modeset_unlock_all(dev);
	वापस 0;
पूर्ण

/**
 *	psb_restore_display_रेजिस्टरs	-	restore lost रेजिस्टर state
 *	@dev: our DRM device
 *
 *	Restore रेजिस्टर state that was lost during suspend and resume.
 */
अटल पूर्णांक psb_restore_display_रेजिस्टरs(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_crtc *crtc;
	काष्ठा gma_connector *connector;
	काष्ठा psb_state *regs = &dev_priv->regs.psb;

	/* Display arbitration + watermarks */
	PSB_WVDC32(regs->saveDSPARB, DSPARB);
	PSB_WVDC32(regs->saveDSPFW1, DSPFW1);
	PSB_WVDC32(regs->saveDSPFW2, DSPFW2);
	PSB_WVDC32(regs->saveDSPFW3, DSPFW3);
	PSB_WVDC32(regs->saveDSPFW4, DSPFW4);
	PSB_WVDC32(regs->saveDSPFW5, DSPFW5);
	PSB_WVDC32(regs->saveDSPFW6, DSPFW6);
	PSB_WVDC32(regs->saveCHICKENBIT, DSPCHICKENBIT);

	/*make sure VGA plane is off. it initializes to on after reset!*/
	PSB_WVDC32(0x80000000, VGACNTRL);

	drm_modeset_lock_all(dev);
	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head)
		अगर (drm_helper_crtc_in_use(crtc))
			dev_priv->ops->restore_crtc(crtc);

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list, base.head)
		अगर (connector->restore)
			connector->restore(&connector->base);

	drm_modeset_unlock_all(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक psb_घातer_करोwn(काष्ठा drm_device *dev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक psb_घातer_up(काष्ठा drm_device *dev)
अणु
	वापस 0;
पूर्ण

/* Poulsbo */
अटल स्थिर काष्ठा psb_offset psb_regmap[2] = अणु
	अणु
		.fp0 = FPA0,
		.fp1 = FPA1,
		.cntr = DSPACNTR,
		.conf = PIPEACONF,
		.src = PIPEASRC,
		.dpll = DPLL_A,
		.htotal = HTOTAL_A,
		.hblank = HBLANK_A,
		.hsync = HSYNC_A,
		.vtotal = VTOTAL_A,
		.vblank = VBLANK_A,
		.vsync = VSYNC_A,
		.stride = DSPASTRIDE,
		.size = DSPASIZE,
		.pos = DSPAPOS,
		.base = DSPABASE,
		.surf = DSPASURF,
		.addr = DSPABASE,
		.status = PIPEASTAT,
		.linoff = DSPALINOFF,
		.tileoff = DSPATILखातापूर्णF,
		.palette = PALETTE_A,
	पूर्ण,
	अणु
		.fp0 = FPB0,
		.fp1 = FPB1,
		.cntr = DSPBCNTR,
		.conf = PIPEBCONF,
		.src = PIPEBSRC,
		.dpll = DPLL_B,
		.htotal = HTOTAL_B,
		.hblank = HBLANK_B,
		.hsync = HSYNC_B,
		.vtotal = VTOTAL_B,
		.vblank = VBLANK_B,
		.vsync = VSYNC_B,
		.stride = DSPBSTRIDE,
		.size = DSPBSIZE,
		.pos = DSPBPOS,
		.base = DSPBBASE,
		.surf = DSPBSURF,
		.addr = DSPBBASE,
		.status = PIPEBSTAT,
		.linoff = DSPBLINOFF,
		.tileoff = DSPBTILखातापूर्णF,
		.palette = PALETTE_B,
	पूर्ण
पूर्ण;

अटल पूर्णांक psb_chip_setup(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	dev_priv->regmap = psb_regmap;
	gma_get_core_freq(dev);
	gma_पूर्णांकel_setup_gmbus(dev);
	psb_पूर्णांकel_opregion_init(dev);
	psb_पूर्णांकel_init_bios(dev);
	वापस 0;
पूर्ण

अटल व्योम psb_chip_tearकरोwn(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	psb_lid_समयr_takeकरोwn(dev_priv);
	gma_पूर्णांकel_tearकरोwn_gmbus(dev);
पूर्ण

स्थिर काष्ठा psb_ops psb_chip_ops = अणु
	.name = "Poulsbo",
	.pipes = 2,
	.crtcs = 2,
	.hdmi_mask = (1 << 0),
	.lvds_mask = (1 << 1),
	.sdvo_mask = (1 << 0),
	.cursor_needs_phys = 1,
	.sgx_offset = PSB_SGX_OFFSET,
	.chip_setup = psb_chip_setup,
	.chip_tearकरोwn = psb_chip_tearकरोwn,

	.crtc_helper = &psb_पूर्णांकel_helper_funcs,
	.crtc_funcs = &gma_पूर्णांकel_crtc_funcs,
	.घड़ी_funcs = &psb_घड़ी_funcs,

	.output_init = psb_output_init,

#अगर_घोषित CONFIG_BACKLIGHT_CLASS_DEVICE
	.backlight_init = psb_backlight_init,
#पूर्ण_अगर

	.init_pm = psb_init_pm,
	.save_regs = psb_save_display_रेजिस्टरs,
	.restore_regs = psb_restore_display_रेजिस्टरs,
	.save_crtc = gma_crtc_save,
	.restore_crtc = gma_crtc_restore,
	.घातer_करोwn = psb_घातer_करोwn,
	.घातer_up = psb_घातer_up,
पूर्ण;

