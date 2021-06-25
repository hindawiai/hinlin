<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2011 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Dave Airlie <airlied@linux.ie>
 *	Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */

#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "cdv_device.h"
#समावेश "intel_bios.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

/**
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

काष्ठा cdv_पूर्णांकel_lvds_priv अणु
	/**
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
पूर्ण;

/*
 * Returns the maximum level of the backlight duty cycle field.
 */
अटल u32 cdv_पूर्णांकel_lvds_get_max_backlight(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 retval;

	अगर (gma_घातer_begin(dev, false)) अणु
		retval = ((REG_READ(BLC_PWM_CTL) &
			  BACKLIGHT_MODULATION_FREQ_MASK) >>
			  BACKLIGHT_MODULATION_FREQ_SHIFT) * 2;

		gma_घातer_end(dev);
	पूर्ण अन्यथा
		retval = ((dev_priv->regs.saveBLC_PWM_CTL &
			  BACKLIGHT_MODULATION_FREQ_MASK) >>
			  BACKLIGHT_MODULATION_FREQ_SHIFT) * 2;

	वापस retval;
पूर्ण

/*
 * Sets the backlight level.
 *
 * level backlight level, from 0 to cdv_पूर्णांकel_lvds_get_max_backlight().
 */
अटल व्योम cdv_पूर्णांकel_lvds_set_backlight(काष्ठा drm_device *dev, पूर्णांक level)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 blc_pwm_ctl;

	अगर (gma_घातer_begin(dev, false)) अणु
		blc_pwm_ctl =
			REG_READ(BLC_PWM_CTL) & ~BACKLIGHT_DUTY_CYCLE_MASK;
		REG_WRITE(BLC_PWM_CTL,
				(blc_pwm_ctl |
				(level << BACKLIGHT_DUTY_CYCLE_SHIFT)));
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
अटल व्योम cdv_पूर्णांकel_lvds_set_घातer(काष्ठा drm_device *dev,
				     काष्ठा drm_encoder *encoder, bool on)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 pp_status;

	अगर (!gma_घातer_begin(dev, true))
		वापस;

	अगर (on) अणु
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) |
			  POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक ((pp_status & PP_ON) == 0);

		cdv_पूर्णांकel_lvds_set_backlight(dev,
				dev_priv->mode_dev.backlight_duty_cycle);
	पूर्ण अन्यथा अणु
		cdv_पूर्णांकel_lvds_set_backlight(dev, 0);

		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) &
			  ~POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक (pp_status & PP_ON);
	पूर्ण
	gma_घातer_end(dev);
पूर्ण

अटल व्योम cdv_पूर्णांकel_lvds_encoder_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	अगर (mode == DRM_MODE_DPMS_ON)
		cdv_पूर्णांकel_lvds_set_घातer(dev, encoder, true);
	अन्यथा
		cdv_पूर्णांकel_lvds_set_घातer(dev, encoder, false);
	/* XXX: We never घातer करोwn the LVDS pairs. */
पूर्ण

अटल व्योम cdv_पूर्णांकel_lvds_save(काष्ठा drm_connector *connector)
अणु
पूर्ण

अटल व्योम cdv_पूर्णांकel_lvds_restore(काष्ठा drm_connector *connector)
अणु
पूर्ण

अटल क्रमागत drm_mode_status cdv_पूर्णांकel_lvds_mode_valid(काष्ठा drm_connector *connector,
			      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा drm_display_mode *fixed_mode =
					dev_priv->mode_dev.panel_fixed_mode;

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

अटल bool cdv_पूर्णांकel_lvds_mode_fixup(काष्ठा drm_encoder *encoder,
				  स्थिर काष्ठा drm_display_mode *mode,
				  काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;
	काष्ठा drm_encoder *पंचांगp_encoder;
	काष्ठा drm_display_mode *panel_fixed_mode = mode_dev->panel_fixed_mode;

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

अटल व्योम cdv_पूर्णांकel_lvds_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;

	अगर (!gma_घातer_begin(dev, true))
		वापस;

	mode_dev->saveBLC_PWM_CTL = REG_READ(BLC_PWM_CTL);
	mode_dev->backlight_duty_cycle = (mode_dev->saveBLC_PWM_CTL &
					  BACKLIGHT_DUTY_CYCLE_MASK);

	cdv_पूर्णांकel_lvds_set_घातer(dev, encoder, false);

	gma_घातer_end(dev);
पूर्ण

अटल व्योम cdv_पूर्णांकel_lvds_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;

	अगर (mode_dev->backlight_duty_cycle == 0)
		mode_dev->backlight_duty_cycle =
		    cdv_पूर्णांकel_lvds_get_max_backlight(dev);

	cdv_पूर्णांकel_lvds_set_घातer(dev, encoder, true);
पूर्ण

अटल व्योम cdv_पूर्णांकel_lvds_mode_set(काष्ठा drm_encoder *encoder,
				काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(encoder->crtc);
	u32 pfit_control;

	/*
	 * The LVDS pin pair will alपढ़ोy have been turned on in the
	 * cdv_पूर्णांकel_crtc_mode_set since it has a large impact on the DPLL
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

	pfit_control |= gma_crtc->pipe << PFIT_PIPE_SHIFT;

	अगर (dev_priv->lvds_dither)
		pfit_control |= PANEL_8TO6_DITHER_ENABLE;

	REG_WRITE(PFIT_CONTROL, pfit_control);
पूर्ण

/*
 * Return the list of DDC modes अगर available, or the BIOS fixed mode otherwise.
 */
अटल पूर्णांक cdv_पूर्णांकel_lvds_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;
	पूर्णांक ret;

	ret = psb_पूर्णांकel_ddc_get_modes(connector, &gma_encoder->i2c_bus->adapter);

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
 * cdv_पूर्णांकel_lvds_destroy - unरेजिस्टर and मुक्त LVDS काष्ठाures
 * @connector: connector to मुक्त
 *
 * Unरेजिस्टर the DDC bus क्रम this connector then मुक्त the driver निजी
 * काष्ठाure.
 */
अटल व्योम cdv_पूर्णांकel_lvds_destroy(काष्ठा drm_connector *connector)
अणु
	काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);

	psb_पूर्णांकel_i2c_destroy(gma_encoder->i2c_bus);
	drm_connector_unरेजिस्टर(connector);
	drm_connector_cleanup(connector);
	kमुक्त(connector);
पूर्ण

अटल पूर्णांक cdv_पूर्णांकel_lvds_set_property(काष्ठा drm_connector *connector,
				       काष्ठा drm_property *property,
				       uपूर्णांक64_t value)
अणु
	काष्ठा drm_encoder *encoder = connector->encoder;

	अगर (!म_भेद(property->name, "scaling mode") && encoder) अणु
		काष्ठा gma_crtc *crtc = to_gma_crtc(encoder->crtc);
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
						     property,
						     &curValue))
			वापस -1;

		अगर (curValue == value)
			वापस 0;

		अगर (drm_object_property_set_value(&connector->base,
							property,
							value))
			वापस -1;

		अगर (crtc->saved_mode.hdisplay != 0 &&
		    crtc->saved_mode.vdisplay != 0) अणु
			अगर (!drm_crtc_helper_set_mode(encoder->crtc,
						      &crtc->saved_mode,
						      encoder->crtc->x,
						      encoder->crtc->y,
						      encoder->crtc->primary->fb))
				वापस -1;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेद(property->name, "backlight") && encoder) अणु
		अगर (drm_object_property_set_value(&connector->base,
							property,
							value))
			वापस -1;
		अन्यथा
                        gma_backlight_set(encoder->dev, value);
	पूर्ण अन्यथा अगर (!म_भेद(property->name, "DPMS") && encoder) अणु
		स्थिर काष्ठा drm_encoder_helper_funcs *helpers =
					encoder->helper_निजी;
		helpers->dpms(encoder, value);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs
					cdv_पूर्णांकel_lvds_helper_funcs = अणु
	.dpms = cdv_पूर्णांकel_lvds_encoder_dpms,
	.mode_fixup = cdv_पूर्णांकel_lvds_mode_fixup,
	.prepare = cdv_पूर्णांकel_lvds_prepare,
	.mode_set = cdv_पूर्णांकel_lvds_mode_set,
	.commit = cdv_पूर्णांकel_lvds_commit,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs
				cdv_पूर्णांकel_lvds_connector_helper_funcs = अणु
	.get_modes = cdv_पूर्णांकel_lvds_get_modes,
	.mode_valid = cdv_पूर्णांकel_lvds_mode_valid,
	.best_encoder = gma_best_encoder,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs cdv_पूर्णांकel_lvds_connector_funcs = अणु
	.dpms = drm_helper_connector_dpms,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.set_property = cdv_पूर्णांकel_lvds_set_property,
	.destroy = cdv_पूर्णांकel_lvds_destroy,
पूर्ण;

/*
 * Enumerate the child dev array parsed from VBT to check whether
 * the LVDS is present.
 * If it is present, वापस 1.
 * If it is not present, वापस false.
 * If no child dev is parsed from VBT, it assumes that the LVDS is present.
 */
अटल bool lvds_is_present_in_vbt(काष्ठा drm_device *dev,
				   u8 *i2c_pin)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक i;

	अगर (!dev_priv->child_dev_num)
		वापस true;

	क्रम (i = 0; i < dev_priv->child_dev_num; i++) अणु
		काष्ठा child_device_config *child = dev_priv->child_dev + i;

		/* If the device type is not LFP, जारी.
		 * We have to check both the new identअगरiers as well as the
		 * old क्रम compatibility with some BIOSes.
		 */
		अगर (child->device_type != DEVICE_TYPE_INT_LFP &&
		    child->device_type != DEVICE_TYPE_LFP)
			जारी;

		अगर (child->i2c_pin)
		    *i2c_pin = child->i2c_pin;

		/* However, we cannot trust the BIOS ग_लिखोrs to populate
		 * the VBT correctly.  Since LVDS requires additional
		 * inक्रमmation from AIM blocks, a non-zero addin offset is
		 * a good indicator that the LVDS is actually present.
		 */
		अगर (child->addin_offset)
			वापस true;

		/* But even then some BIOS ग_लिखोrs perक्रमm some black magic
		 * and instantiate the device without reference to any
		 * additional data.  Trust that अगर the VBT was written पूर्णांकo
		 * the OpRegion then they have validated the LVDS's existence.
		 */
		अगर (dev_priv->opregion.vbt)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * cdv_पूर्णांकel_lvds_init - setup LVDS connectors on this device
 * @dev: drm device
 * @mode_dev: PSB mode device
 *
 * Create the connector, रेजिस्टर the LVDS DDC bus, and try to figure out what
 * modes we can display on the LVDS panel (अगर present).
 */
व्योम cdv_पूर्णांकel_lvds_init(काष्ठा drm_device *dev,
		     काष्ठा psb_पूर्णांकel_mode_device *mode_dev)
अणु
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा gma_connector *gma_connector;
	काष्ठा cdv_पूर्णांकel_lvds_priv *lvds_priv;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_display_mode *scan;
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 lvds;
	पूर्णांक pipe;
	u8 pin;

	अगर (!dev_priv->lvds_enabled_in_vbt)
		वापस;

	pin = GMBUS_PORT_PANEL;
	अगर (!lvds_is_present_in_vbt(dev, &pin)) अणु
		DRM_DEBUG_KMS("LVDS is not present in VBT\n");
		वापस;
	पूर्ण

	gma_encoder = kzalloc(माप(काष्ठा gma_encoder),
				    GFP_KERNEL);
	अगर (!gma_encoder)
		वापस;

	gma_connector = kzalloc(माप(काष्ठा gma_connector),
				      GFP_KERNEL);
	अगर (!gma_connector)
		जाओ failed_connector;

	lvds_priv = kzalloc(माप(काष्ठा cdv_पूर्णांकel_lvds_priv), GFP_KERNEL);
	अगर (!lvds_priv)
		जाओ failed_lvds_priv;

	gma_encoder->dev_priv = lvds_priv;

	connector = &gma_connector->base;
	gma_connector->save = cdv_पूर्णांकel_lvds_save;
	gma_connector->restore = cdv_पूर्णांकel_lvds_restore;
	encoder = &gma_encoder->base;


	drm_connector_init(dev, connector,
			   &cdv_पूर्णांकel_lvds_connector_funcs,
			   DRM_MODE_CONNECTOR_LVDS);

	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_LVDS);

	gma_connector_attach_encoder(gma_connector, gma_encoder);
	gma_encoder->type = INTEL_OUTPUT_LVDS;

	drm_encoder_helper_add(encoder, &cdv_पूर्णांकel_lvds_helper_funcs);
	drm_connector_helper_add(connector,
				 &cdv_पूर्णांकel_lvds_connector_helper_funcs);
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

	/**
	 * Set up I2C bus
	 * FIXME: distroy i2c_bus when निकास
	 */
	gma_encoder->i2c_bus = psb_पूर्णांकel_i2c_create(dev,
							 GPIOB,
							 "LVDSBLC_B");
	अगर (!gma_encoder->i2c_bus) अणु
		dev_prपूर्णांकk(KERN_ERR,
			dev->dev, "I2C bus registration failed.\n");
		जाओ failed_blc_i2c;
	पूर्ण
	gma_encoder->i2c_bus->slave_addr = 0x2C;
	dev_priv->lvds_i2c_bus = gma_encoder->i2c_bus;

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
	gma_encoder->ddc_bus = psb_पूर्णांकel_i2c_create(dev,
							 GPIOC,
							 "LVDSDDC_C");
	अगर (!gma_encoder->ddc_bus) अणु
		dev_prपूर्णांकk(KERN_ERR, dev->dev,
			   "DDC bus registration " "failed.\n");
		जाओ failed_ddc;
	पूर्ण

	/*
	 * Attempt to get the fixed panel mode from DDC.  Assume that the
	 * preferred mode is the right one.
	 */
	mutex_lock(&dev->mode_config.mutex);
	psb_पूर्णांकel_ddc_get_modes(connector,
				&gma_encoder->ddc_bus->adapter);
	list_क्रम_each_entry(scan, &connector->probed_modes, head) अणु
		अगर (scan->type & DRM_MODE_TYPE_PREFERRED) अणु
			mode_dev->panel_fixed_mode =
			    drm_mode_duplicate(dev, scan);
			जाओ out;	/* FIXME: check क्रम quirks */
		पूर्ण
	पूर्ण

	/* Failed to get EDID, what about VBT? करो we need this?*/
	अगर (dev_priv->lfp_lvds_vbt_mode) अणु
		mode_dev->panel_fixed_mode =
			drm_mode_duplicate(dev, dev_priv->lfp_lvds_vbt_mode);
		अगर (mode_dev->panel_fixed_mode) अणु
			mode_dev->panel_fixed_mode->type |=
				DRM_MODE_TYPE_PREFERRED;
			जाओ out;	/* FIXME: check क्रम quirks */
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
		    cdv_पूर्णांकel_crtc_mode_get(dev, crtc);
		अगर (mode_dev->panel_fixed_mode) अणु
			mode_dev->panel_fixed_mode->type |=
			    DRM_MODE_TYPE_PREFERRED;
			जाओ out;	/* FIXME: check क्रम quirks */
		पूर्ण
	पूर्ण

	/* If we still करोn't have a mode after all that, give up. */
	अगर (!mode_dev->panel_fixed_mode) अणु
		DRM_DEBUG
			("Found no modes on the lvds, ignoring the LVDS\n");
		जाओ failed_find;
	पूर्ण

	/* setup PWM */
	अणु
		u32 pwm;

		pwm = REG_READ(BLC_PWM_CTL2);
		अगर (pipe == 1)
			pwm |= PWM_PIPE_B;
		अन्यथा
			pwm &= ~PWM_PIPE_B;
		pwm |= PWM_ENABLE;
		REG_WRITE(BLC_PWM_CTL2, pwm);
	पूर्ण

out:
	mutex_unlock(&dev->mode_config.mutex);
	drm_connector_रेजिस्टर(connector);
	वापस;

failed_find:
	mutex_unlock(&dev->mode_config.mutex);
	pr_err("Failed find\n");
	psb_पूर्णांकel_i2c_destroy(gma_encoder->ddc_bus);
failed_ddc:
	pr_err("Failed DDC\n");
	psb_पूर्णांकel_i2c_destroy(gma_encoder->i2c_bus);
failed_blc_i2c:
	pr_err("Failed BLC\n");
	drm_encoder_cleanup(encoder);
	drm_connector_cleanup(connector);
	kमुक्त(lvds_priv);
failed_lvds_priv:
	kमुक्त(gma_connector);
failed_connector:
	kमुक्त(gma_encoder);
पूर्ण
