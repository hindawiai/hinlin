<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2007 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Dave Airlie <airlied@linux.ie>
 *	Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "intel_bios.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

/*
 * LVDS I2C backlight control macros
 */
#घोषणा BRIGHTNESS_MAX_LEVEL 100
#घोषणा BRIGHTNESS_MASK 0xFF
#घोषणा BLC_I2C_TYPE	0x01
#घोषणा BLC_PWM_TYPT	0x02

#घोषणा BLC_POLARITY_NORMAL 0
#घोषणा BLC_POLARITY_INVERSE 1

#घोषणा PSB_BLC_MAX_PWM_REG_FREQ       (0xFFFE)
#घोषणा PSB_BLC_MIN_PWM_REG_FREQ	(0x2)
#घोषणा PSB_BLC_PWM_PRECISION_FACTOR	(10)
#घोषणा PSB_BACKLIGHT_PWM_CTL_SHIFT	(16)
#घोषणा PSB_BACKLIGHT_PWM_POLARITY_BIT_CLEAR (0xFFFE)

काष्ठा psb_पूर्णांकel_lvds_priv अणु
	/*
	 * Saved LVDO output states
	 */
	uपूर्णांक32_t savePP_ON;
	uपूर्णांक32_t savePP_OFF;
	uपूर्णांक32_t saveLVDS;
	uपूर्णांक32_t savePP_CONTROL;
	uपूर्णांक32_t savePP_CYCLE;
	uपूर्णांक32_t savePFIT_CONTROL;
	uपूर्णांक32_t savePFIT_PGM_RATIOS;
	uपूर्णांक32_t saveBLC_PWM_CTL;

	काष्ठा psb_पूर्णांकel_i2c_chan *i2c_bus;
	काष्ठा psb_पूर्णांकel_i2c_chan *ddc_bus;
पूर्ण;


/*
 * Returns the maximum level of the backlight duty cycle field.
 */
अटल u32 psb_पूर्णांकel_lvds_get_max_backlight(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 ret;

	अगर (gma_घातer_begin(dev, false)) अणु
		ret = REG_READ(BLC_PWM_CTL);
		gma_घातer_end(dev);
	पूर्ण अन्यथा /* Powered off, use the saved value */
		ret = dev_priv->regs.saveBLC_PWM_CTL;

	/* Top 15bits hold the frequency mask */
	ret = (ret &  BACKLIGHT_MODULATION_FREQ_MASK) >>
					BACKLIGHT_MODULATION_FREQ_SHIFT;

        ret *= 2;	/* Return a 16bit range as needed क्रम setting */
        अगर (ret == 0)
                dev_err(dev->dev, "BL bug: Reg %08x save %08X\n",
                        REG_READ(BLC_PWM_CTL), dev_priv->regs.saveBLC_PWM_CTL);
	वापस ret;
पूर्ण

/*
 * Set LVDS backlight level by I2C command
 *
 * FIXME: at some poपूर्णांक we need to both track this क्रम PM and also
 * disable runसमय pm on MRST अगर the brightness is nil (ie blanked)
 */
अटल पूर्णांक psb_lvds_i2c_set_brightness(काष्ठा drm_device *dev,
					अचिन्हित पूर्णांक level)
अणु
	काष्ठा drm_psb_निजी *dev_priv =
		(काष्ठा drm_psb_निजी *)dev->dev_निजी;

	काष्ठा psb_पूर्णांकel_i2c_chan *lvds_i2c_bus = dev_priv->lvds_i2c_bus;
	u8 out_buf[2];
	अचिन्हित पूर्णांक blc_i2c_brightness;

	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr = lvds_i2c_bus->slave_addr,
			.flags = 0,
			.len = 2,
			.buf = out_buf,
		पूर्ण
	पूर्ण;

	blc_i2c_brightness = BRIGHTNESS_MASK & ((अचिन्हित पूर्णांक)level *
			     BRIGHTNESS_MASK /
			     BRIGHTNESS_MAX_LEVEL);

	अगर (dev_priv->lvds_bl->pol == BLC_POLARITY_INVERSE)
		blc_i2c_brightness = BRIGHTNESS_MASK - blc_i2c_brightness;

	out_buf[0] = dev_priv->lvds_bl->brightnesscmd;
	out_buf[1] = (u8)blc_i2c_brightness;

	अगर (i2c_transfer(&lvds_i2c_bus->adapter, msgs, 1) == 1) अणु
		dev_dbg(dev->dev, "I2C set brightness.(command, value) (%d, %d)\n",
			dev_priv->lvds_bl->brightnesscmd,
			blc_i2c_brightness);
		वापस 0;
	पूर्ण

	dev_err(dev->dev, "I2C transfer error\n");
	वापस -1;
पूर्ण


अटल पूर्णांक psb_lvds_pwm_set_brightness(काष्ठा drm_device *dev, पूर्णांक level)
अणु
	काष्ठा drm_psb_निजी *dev_priv =
			(काष्ठा drm_psb_निजी *)dev->dev_निजी;

	u32 max_pwm_blc;
	u32 blc_pwm_duty_cycle;

	max_pwm_blc = psb_पूर्णांकel_lvds_get_max_backlight(dev);

	/*BLC_PWM_CTL Should be initiated जबतक backlight device init*/
	BUG_ON(max_pwm_blc == 0);

	blc_pwm_duty_cycle = level * max_pwm_blc / BRIGHTNESS_MAX_LEVEL;

	अगर (dev_priv->lvds_bl->pol == BLC_POLARITY_INVERSE)
		blc_pwm_duty_cycle = max_pwm_blc - blc_pwm_duty_cycle;

	blc_pwm_duty_cycle &= PSB_BACKLIGHT_PWM_POLARITY_BIT_CLEAR;
	REG_WRITE(BLC_PWM_CTL,
		  (max_pwm_blc << PSB_BACKLIGHT_PWM_CTL_SHIFT) |
		  (blc_pwm_duty_cycle));

        dev_info(dev->dev, "Backlight lvds set brightness %08x\n",
		  (max_pwm_blc << PSB_BACKLIGHT_PWM_CTL_SHIFT) |
		  (blc_pwm_duty_cycle));

	वापस 0;
पूर्ण

/*
 * Set LVDS backlight level either by I2C or PWM
 */
व्योम psb_पूर्णांकel_lvds_set_brightness(काष्ठा drm_device *dev, पूर्णांक level)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	dev_dbg(dev->dev, "backlight level is %d\n", level);

	अगर (!dev_priv->lvds_bl) अणु
		dev_err(dev->dev, "NO LVDS backlight info\n");
		वापस;
	पूर्ण

	अगर (dev_priv->lvds_bl->type == BLC_I2C_TYPE)
		psb_lvds_i2c_set_brightness(dev, level);
	अन्यथा
		psb_lvds_pwm_set_brightness(dev, level);
पूर्ण

/*
 * Sets the backlight level.
 *
 * level: backlight level, from 0 to psb_पूर्णांकel_lvds_get_max_backlight().
 */
अटल व्योम psb_पूर्णांकel_lvds_set_backlight(काष्ठा drm_device *dev, पूर्णांक level)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 blc_pwm_ctl;

	अगर (gma_घातer_begin(dev, false)) अणु
		blc_pwm_ctl = REG_READ(BLC_PWM_CTL);
		blc_pwm_ctl &= ~BACKLIGHT_DUTY_CYCLE_MASK;
		REG_WRITE(BLC_PWM_CTL,
				(blc_pwm_ctl |
				(level << BACKLIGHT_DUTY_CYCLE_SHIFT)));
		dev_priv->regs.saveBLC_PWM_CTL = (blc_pwm_ctl |
					(level << BACKLIGHT_DUTY_CYCLE_SHIFT));
		gma_घातer_end(dev);
	पूर्ण अन्यथा अणु
		blc_pwm_ctl = dev_priv->regs.saveBLC_PWM_CTL &
				~BACKLIGHT_DUTY_CYCLE_MASK;
		dev_priv->regs.saveBLC_PWM_CTL = (blc_pwm_ctl |
					(level << BACKLIGHT_DUTY_CYCLE_SHIFT));
	पूर्ण
पूर्ण

/*
 * Sets the घातer state क्रम the panel.
 */
अटल व्योम psb_पूर्णांकel_lvds_set_घातer(काष्ठा drm_device *dev, bool on)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;
	u32 pp_status;

	अगर (!gma_घातer_begin(dev, true)) अणु
	        dev_err(dev->dev, "set power, chip off!\n");
		वापस;
        पूर्ण

	अगर (on) अणु
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) |
			  POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक ((pp_status & PP_ON) == 0);

		psb_पूर्णांकel_lvds_set_backlight(dev,
					     mode_dev->backlight_duty_cycle);
	पूर्ण अन्यथा अणु
		psb_पूर्णांकel_lvds_set_backlight(dev, 0);

		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) &
			  ~POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक (pp_status & PP_ON);
	पूर्ण

	gma_घातer_end(dev);
पूर्ण

अटल व्योम psb_पूर्णांकel_lvds_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;

	अगर (mode == DRM_MODE_DPMS_ON)
		psb_पूर्णांकel_lvds_set_घातer(dev, true);
	अन्यथा
		psb_पूर्णांकel_lvds_set_घातer(dev, false);

	/* XXX: We never घातer करोwn the LVDS pairs. */
पूर्ण

अटल व्योम psb_पूर्णांकel_lvds_save(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_psb_निजी *dev_priv =
		(काष्ठा drm_psb_निजी *)dev->dev_निजी;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा psb_पूर्णांकel_lvds_priv *lvds_priv =
		(काष्ठा psb_पूर्णांकel_lvds_priv *)gma_encoder->dev_priv;

	lvds_priv->savePP_ON = REG_READ(LVDSPP_ON);
	lvds_priv->savePP_OFF = REG_READ(LVDSPP_OFF);
	lvds_priv->saveLVDS = REG_READ(LVDS);
	lvds_priv->savePP_CONTROL = REG_READ(PP_CONTROL);
	lvds_priv->savePP_CYCLE = REG_READ(PP_CYCLE);
	/*lvds_priv->savePP_DIVISOR = REG_READ(PP_DIVISOR);*/
	lvds_priv->saveBLC_PWM_CTL = REG_READ(BLC_PWM_CTL);
	lvds_priv->savePFIT_CONTROL = REG_READ(PFIT_CONTROL);
	lvds_priv->savePFIT_PGM_RATIOS = REG_READ(PFIT_PGM_RATIOS);

	/*TODO: move backlight_duty_cycle to psb_पूर्णांकel_lvds_priv*/
	dev_priv->backlight_duty_cycle = (dev_priv->regs.saveBLC_PWM_CTL &
						BACKLIGHT_DUTY_CYCLE_MASK);

	/*
	 * If the light is off at server startup,
	 * just make it full brightness
	 */
	अगर (dev_priv->backlight_duty_cycle == 0)
		dev_priv->backlight_duty_cycle =
		psb_पूर्णांकel_lvds_get_max_backlight(dev);

	dev_dbg(dev->dev, "(0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x)\n",
			lvds_priv->savePP_ON,
			lvds_priv->savePP_OFF,
			lvds_priv->saveLVDS,
			lvds_priv->savePP_CONTROL,
			lvds_priv->savePP_CYCLE,
			lvds_priv->saveBLC_PWM_CTL);
पूर्ण

अटल व्योम psb_पूर्णांकel_lvds_restore(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	u32 pp_status;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा psb_पूर्णांकel_lvds_priv *lvds_priv =
		(काष्ठा psb_पूर्णांकel_lvds_priv *)gma_encoder->dev_priv;

	dev_dbg(dev->dev, "(0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x)\n",
			lvds_priv->savePP_ON,
			lvds_priv->savePP_OFF,
			lvds_priv->saveLVDS,
			lvds_priv->savePP_CONTROL,
			lvds_priv->savePP_CYCLE,
			lvds_priv->saveBLC_PWM_CTL);

	REG_WRITE(BLC_PWM_CTL, lvds_priv->saveBLC_PWM_CTL);
	REG_WRITE(PFIT_CONTROL, lvds_priv->savePFIT_CONTROL);
	REG_WRITE(PFIT_PGM_RATIOS, lvds_priv->savePFIT_PGM_RATIOS);
	REG_WRITE(LVDSPP_ON, lvds_priv->savePP_ON);
	REG_WRITE(LVDSPP_OFF, lvds_priv->savePP_OFF);
	/*REG_WRITE(PP_DIVISOR, lvds_priv->savePP_DIVISOR);*/
	REG_WRITE(PP_CYCLE, lvds_priv->savePP_CYCLE);
	REG_WRITE(PP_CONTROL, lvds_priv->savePP_CONTROL);
	REG_WRITE(LVDS, lvds_priv->saveLVDS);

	अगर (lvds_priv->savePP_CONTROL & POWER_TARGET_ON) अणु
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) |
			POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक ((pp_status & PP_ON) == 0);
	पूर्ण अन्यथा अणु
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) &
			~POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक (pp_status & PP_ON);
	पूर्ण
पूर्ण

क्रमागत drm_mode_status psb_पूर्णांकel_lvds_mode_valid(काष्ठा drm_connector *connector,
				 काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_psb_निजी *dev_priv = connector->dev->dev_निजी;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा drm_display_mode *fixed_mode =
					dev_priv->mode_dev.panel_fixed_mode;

	अगर (gma_encoder->type == INTEL_OUTPUT_MIPI2)
		fixed_mode = dev_priv->mode_dev.panel_fixed_mode2;

	/* just in हाल */
	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	/* just in हाल */
	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		वापस MODE_NO_INTERLACE;

	अगर (fixed_mode) अणु
		अगर (mode->hdisplay > fixed_mode->hdisplay)
			वापस MODE_PANEL;
		अगर (mode->vdisplay > fixed_mode->vdisplay)
			वापस MODE_PANEL;
	पूर्ण
	वापस MODE_OK;
पूर्ण

bool psb_पूर्णांकel_lvds_mode_fixup(काष्ठा drm_encoder *encoder,
				  स्थिर काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(encoder->crtc);
	काष्ठा drm_encoder *पंचांगp_encoder;
	काष्ठा drm_display_mode *panel_fixed_mode = mode_dev->panel_fixed_mode;
	काष्ठा gma_encoder *gma_encoder = to_gma_encoder(encoder);

	अगर (gma_encoder->type == INTEL_OUTPUT_MIPI2)
		panel_fixed_mode = mode_dev->panel_fixed_mode2;

	/* PSB requires the LVDS is on pipe B, MRST has only one pipe anyway */
	अगर (!IS_MRST(dev) && gma_crtc->pipe == 0) अणु
		pr_err("Can't support LVDS on pipe A\n");
		वापस false;
	पूर्ण
	अगर (IS_MRST(dev) && gma_crtc->pipe != 0) अणु
		pr_err("Must use PIPE A\n");
		वापस false;
	पूर्ण
	/* Should never happen!! */
	list_क्रम_each_entry(पंचांगp_encoder, &dev->mode_config.encoder_list,
			    head) अणु
		अगर (पंचांगp_encoder != encoder
		    && पंचांगp_encoder->crtc == encoder->crtc) अणु
			pr_err("Can't enable LVDS and another encoder on the same pipe\n");
			वापस false;
		पूर्ण
	पूर्ण

	/*
	 * If we have timings from the BIOS क्रम the panel, put them in
	 * to the adjusted mode.  The CRTC will be set up क्रम this mode,
	 * with the panel scaling set up to source from the H/VDisplay
	 * of the original mode.
	 */
	अगर (panel_fixed_mode != शून्य) अणु
		adjusted_mode->hdisplay = panel_fixed_mode->hdisplay;
		adjusted_mode->hsync_start = panel_fixed_mode->hsync_start;
		adjusted_mode->hsync_end = panel_fixed_mode->hsync_end;
		adjusted_mode->htotal = panel_fixed_mode->htotal;
		adjusted_mode->vdisplay = panel_fixed_mode->vdisplay;
		adjusted_mode->vsync_start = panel_fixed_mode->vsync_start;
		adjusted_mode->vsync_end = panel_fixed_mode->vsync_end;
		adjusted_mode->vtotal = panel_fixed_mode->vtotal;
		adjusted_mode->घड़ी = panel_fixed_mode->घड़ी;
		drm_mode_set_crtcinfo(adjusted_mode,
				      CRTC_INTERLACE_HALVE_V);
	पूर्ण

	/*
	 * XXX: It would be nice to support lower refresh rates on the
	 * panels to reduce घातer consumption, and perhaps match the
	 * user's requested refresh rate.
	 */

	वापस true;
पूर्ण

अटल व्योम psb_पूर्णांकel_lvds_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;

	अगर (!gma_घातer_begin(dev, true))
		वापस;

	mode_dev->saveBLC_PWM_CTL = REG_READ(BLC_PWM_CTL);
	mode_dev->backlight_duty_cycle = (mode_dev->saveBLC_PWM_CTL &
					  BACKLIGHT_DUTY_CYCLE_MASK);

	psb_पूर्णांकel_lvds_set_घातer(dev, false);

	gma_घातer_end(dev);
पूर्ण

अटल व्योम psb_पूर्णांकel_lvds_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;

	अगर (mode_dev->backlight_duty_cycle == 0)
		mode_dev->backlight_duty_cycle =
		    psb_पूर्णांकel_lvds_get_max_backlight(dev);

	psb_पूर्णांकel_lvds_set_घातer(dev, true);
पूर्ण

अटल व्योम psb_पूर्णांकel_lvds_mode_set(काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 pfit_control;

	/*
	 * The LVDS pin pair will alपढ़ोy have been turned on in the
	 * psb_पूर्णांकel_crtc_mode_set since it has a large impact on the DPLL
	 * settings.
	 */

	/*
	 * Enable स्वतःmatic panel scaling so that non-native modes fill the
	 * screen.  Should be enabled beक्रमe the pipe is enabled, according to
	 * रेजिस्टर description and PRM.
	 */
	अगर (mode->hdisplay != adjusted_mode->hdisplay ||
	    mode->vdisplay != adjusted_mode->vdisplay)
		pfit_control = (PFIT_ENABLE | VERT_AUTO_SCALE |
				HORIZ_AUTO_SCALE | VERT_INTERP_BILINEAR |
				HORIZ_INTERP_BILINEAR);
	अन्यथा
		pfit_control = 0;

	अगर (dev_priv->lvds_dither)
		pfit_control |= PANEL_8TO6_DITHER_ENABLE;

	REG_WRITE(PFIT_CONTROL, pfit_control);
पूर्ण

/*
 * Return the list of DDC modes अगर available, or the BIOS fixed mode otherwise.
 */
अटल पूर्णांक psb_पूर्णांकel_lvds_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा psb_पूर्णांकel_lvds_priv *lvds_priv = gma_encoder->dev_priv;
	पूर्णांक ret = 0;

	अगर (!IS_MRST(dev))
		ret = psb_पूर्णांकel_ddc_get_modes(connector, &lvds_priv->i2c_bus->adapter);

	अगर (ret)
		वापस ret;

	अगर (mode_dev->panel_fixed_mode != शून्य) अणु
		काष्ठा drm_display_mode *mode =
		    drm_mode_duplicate(dev, mode_dev->panel_fixed_mode);
		drm_mode_probed_add(connector, mode);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * psb_पूर्णांकel_lvds_destroy - unरेजिस्टर and मुक्त LVDS काष्ठाures
 * @connector: connector to मुक्त
 *
 * Unरेजिस्टर the DDC bus क्रम this connector then मुक्त the driver निजी
 * काष्ठाure.
 */
व्योम psb_पूर्णांकel_lvds_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा psb_पूर्णांकel_lvds_priv *lvds_priv = gma_encoder->dev_priv;

	psb_पूर्णांकel_i2c_destroy(lvds_priv->ddc_bus);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

पूर्णांक psb_पूर्णांकel_lvds_set_property(काष्ठा drm_connector *connector,
				       काष्ठा drm_property *property,
				       uपूर्णांक64_t value)
अणु
	काष्ठा drm_encoder *encoder = connector->encoder;

	अगर (!encoder)
		वापस -1;

	अगर (!म_भेद(property->name, "scaling mode")) अणु
		काष्ठा gma_crtc *crtc = to_gma_crtc(encoder->crtc);
		uपूर्णांक64_t curval;

		अगर (!crtc)
			जाओ set_prop_error;

		चयन (value) अणु
		हाल DRM_MODE_SCALE_FULLSCREEN:
			अवरोध;
		हाल DRM_MODE_SCALE_NO_SCALE:
			अवरोध;
		हाल DRM_MODE_SCALE_ASPECT:
			अवरोध;
		शेष:
			जाओ set_prop_error;
		पूर्ण

		अगर (drm_object_property_get_value(&connector->base,
						     property,
						     &curval))
			जाओ set_prop_error;

		अगर (curval == value)
			जाओ set_prop_करोne;

		अगर (drm_object_property_set_value(&connector->base,
							property,
							value))
			जाओ set_prop_error;

		अगर (crtc->saved_mode.hdisplay != 0 &&
		    crtc->saved_mode.vdisplay != 0) अणु
			अगर (!drm_crtc_helper_set_mode(encoder->crtc,
						      &crtc->saved_mode,
						      encoder->crtc->x,
						      encoder->crtc->y,
						      encoder->crtc->primary->fb))
				जाओ set_prop_error;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(property->name, "backlight")) अणु
		अगर (drm_object_property_set_value(&connector->base,
							property,
							value))
			जाओ set_prop_error;
		अन्यथा
                        gma_backlight_set(encoder->dev, value);
	पूर्ण अन्यथा अगर (!म_भेद(property->name, "DPMS")) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *hfuncs
						= encoder->helper_निजी;
		hfuncs->dpms(encoder, value);
	पूर्ण

set_prop_करोne:
	वापस 0;
set_prop_error:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs psb_पूर्णांकel_lvds_helper_funcs = अणु
	.dpms = psb_पूर्णांकel_lvds_encoder_dpms,
	.mode_fixup = psb_पूर्णांकel_lvds_mode_fixup,
	.prepare = psb_पूर्णांकel_lvds_prepare,
	.mode_set = psb_पूर्णांकel_lvds_mode_set,
	.commit = psb_पूर्णांकel_lvds_commit,
पूर्ण;

स्थिर काष्ठा drm_connector_helper_funcs
				psb_पूर्णांकel_lvds_connector_helper_funcs = अणु
	.get_modes = psb_पूर्णांकel_lvds_get_modes,
	.mode_valid = psb_पूर्णांकel_lvds_mode_valid,
	.best_encoder = gma_best_encoder,
पूर्ण;

स्थिर काष्ठा drm_connector_funcs psb_पूर्णांकel_lvds_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = psb_पूर्णांकel_lvds_set_property,
	.destroy = psb_पूर्णांकel_lvds_destroy,
पूर्ण;

/**
 * psb_पूर्णांकel_lvds_init - setup LVDS connectors on this device
 * @dev: drm device
 * @mode_dev: mode device
 *
 * Create the connector, रेजिस्टर the LVDS DDC bus, and try to figure out what
 * modes we can display on the LVDS panel (अगर present).
 */
व्योम psb_पूर्णांकel_lvds_init(काष्ठा drm_device *dev,
			 काष्ठा psb_पूर्णांकel_mode_device *mode_dev)
अणु
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा gma_connector *gma_connector;
	काष्ठा psb_पूर्णांकel_lvds_priv *lvds_priv;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_display_mode *scan;	/* *modes, *bios_mode; */
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 lvds;
	पूर्णांक pipe;

	gma_encoder = kzalloc(माप(काष्ठा gma_encoder), GFP_KERNEL);
	अगर (!gma_encoder) अणु
		dev_err(dev->dev, "gma_encoder allocation error\n");
		वापस;
	पूर्ण

	gma_connector = kzalloc(माप(काष्ठा gma_connector), GFP_KERNEL);
	अगर (!gma_connector) अणु
		dev_err(dev->dev, "gma_connector allocation error\n");
		जाओ failed_encoder;
	पूर्ण

	lvds_priv = kzalloc(माप(काष्ठा psb_पूर्णांकel_lvds_priv), GFP_KERNEL);
	अगर (!lvds_priv) अणु
		dev_err(dev->dev, "LVDS private allocation error\n");
		जाओ failed_connector;
	पूर्ण

	gma_encoder->dev_priv = lvds_priv;

	connector = &gma_connector->base;
	gma_connector->save = psb_पूर्णांकel_lvds_save;
	gma_connector->restore = psb_पूर्णांकel_lvds_restore;

	encoder = &gma_encoder->base;
	drm_connector_init(dev, connector,
			   &psb_पूर्णांकel_lvds_connector_funcs,
			   DRM_MODE_CONNECTOR_LVDS);

	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_LVDS);

	gma_connector_attach_encoder(gma_connector, gma_encoder);
	gma_encoder->type = INTEL_OUTPUT_LVDS;

	drm_encoder_helper_add(encoder, &psb_पूर्णांकel_lvds_helper_funcs);
	drm_connector_helper_add(connector,
				 &psb_पूर्णांकel_lvds_connector_helper_funcs);
	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	/*Attach connector properties*/
	drm_object_attach_property(&connector->base,
				      dev->mode_config.scaling_mode_property,
				      DRM_MODE_SCALE_FULLSCREEN);
	drm_object_attach_property(&connector->base,
				      dev_priv->backlight_property,
				      BRIGHTNESS_MAX_LEVEL);

	/*
	 * Set up I2C bus
	 * FIXME: distroy i2c_bus when निकास
	 */
	lvds_priv->i2c_bus = psb_पूर्णांकel_i2c_create(dev, GPIOB, "LVDSBLC_B");
	अगर (!lvds_priv->i2c_bus) अणु
		dev_prपूर्णांकk(KERN_ERR,
			dev->dev, "I2C bus registration failed.\n");
		जाओ failed_blc_i2c;
	पूर्ण
	lvds_priv->i2c_bus->slave_addr = 0x2C;
	dev_priv->lvds_i2c_bus =  lvds_priv->i2c_bus;

	/*
	 * LVDS discovery:
	 * 1) check क्रम EDID on DDC
	 * 2) check क्रम VBT data
	 * 3) check to see अगर LVDS is alपढ़ोy on
	 *    अगर none of the above, no panel
	 * 4) make sure lid is खोलो
	 *    अगर बंदd, act like it's not there क्रम now
	 */

	/* Set up the DDC bus. */
	lvds_priv->ddc_bus = psb_पूर्णांकel_i2c_create(dev, GPIOC, "LVDSDDC_C");
	अगर (!lvds_priv->ddc_bus) अणु
		dev_prपूर्णांकk(KERN_ERR, dev->dev,
			   "DDC bus registration " "failed.\n");
		जाओ failed_ddc;
	पूर्ण

	/*
	 * Attempt to get the fixed panel mode from DDC.  Assume that the
	 * preferred mode is the right one.
	 */
	mutex_lock(&dev->mode_config.mutex);
	psb_पूर्णांकel_ddc_get_modes(connector, &lvds_priv->ddc_bus->adapter);
	list_क्रम_each_entry(scan, &connector->probed_modes, head) अणु
		अगर (scan->type & DRM_MODE_TYPE_PREFERRED) अणु
			mode_dev->panel_fixed_mode =
			    drm_mode_duplicate(dev, scan);
			DRM_DEBUG_KMS("Using mode from DDC\n");
			जाओ out;	/* FIXME: check क्रम quirks */
		पूर्ण
	पूर्ण

	/* Failed to get EDID, what about VBT? करो we need this? */
	अगर (dev_priv->lfp_lvds_vbt_mode) अणु
		mode_dev->panel_fixed_mode =
			drm_mode_duplicate(dev, dev_priv->lfp_lvds_vbt_mode);

		अगर (mode_dev->panel_fixed_mode) अणु
			mode_dev->panel_fixed_mode->type |=
				DRM_MODE_TYPE_PREFERRED;
			DRM_DEBUG_KMS("Using mode from VBT\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * If we didn't get EDID, try checking अगर the panel is alपढ़ोy turned
	 * on.	If so, assume that whatever is currently programmed is the
	 * correct mode.
	 */
	lvds = REG_READ(LVDS);
	pipe = (lvds & LVDS_PIPEB_SELECT) ? 1 : 0;
	crtc = psb_पूर्णांकel_get_crtc_from_pipe(dev, pipe);

	अगर (crtc && (lvds & LVDS_PORT_EN)) अणु
		mode_dev->panel_fixed_mode =
		    psb_पूर्णांकel_crtc_mode_get(dev, crtc);
		अगर (mode_dev->panel_fixed_mode) अणु
			mode_dev->panel_fixed_mode->type |=
			    DRM_MODE_TYPE_PREFERRED;
			DRM_DEBUG_KMS("Using pre-programmed mode\n");
			जाओ out;	/* FIXME: check क्रम quirks */
		पूर्ण
	पूर्ण

	/* If we still करोn't have a mode after all that, give up. */
	अगर (!mode_dev->panel_fixed_mode) अणु
		dev_err(dev->dev, "Found no modes on the lvds, ignoring the LVDS\n");
		जाओ failed_find;
	पूर्ण

	/*
	 * Blacklist machines with BIOSes that list an LVDS panel without
	 * actually having one.
	 */
out:
	mutex_unlock(&dev->mode_config.mutex);
	drm_connector_रेजिस्टर(connector);
	वापस;

failed_find:
	mutex_unlock(&dev->mode_config.mutex);
	psb_पूर्णांकel_i2c_destroy(lvds_priv->ddc_bus);
failed_ddc:
	psb_पूर्णांकel_i2c_destroy(lvds_priv->i2c_bus);
failed_blc_i2c:
	drm_encoder_cleanup(encoder);
	drm_connector_cleanup(connector);
failed_connector:
	kमुक्त(gma_connector);
failed_encoder:
	kमुक्त(gma_encoder);
पूर्ण

