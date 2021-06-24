<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2006-2009 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *	Dave Airlie <airlied@linux.ie>
 *	Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <यंत्र/पूर्णांकel-mid.h>

#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "intel_bios.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

/* The max/min PWM frequency in BPCR[31:17] - */
/* The smallest number is 1 (not 0) that can fit in the
 * 15-bit field of the and then*/
/* shअगरts to the left by one bit to get the actual 16-bit
 * value that the 15-bits correspond to.*/
#घोषणा MRST_BLC_MAX_PWM_REG_FREQ	    0xFFFF
#घोषणा BRIGHTNESS_MAX_LEVEL 100

/*
 * Sets the घातer state क्रम the panel.
 */
अटल व्योम oaktrail_lvds_set_घातer(काष्ठा drm_device *dev,
				काष्ठा gma_encoder *gma_encoder,
				bool on)
अणु
	u32 pp_status;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	अगर (!gma_घातer_begin(dev, true))
		वापस;

	अगर (on) अणु
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) |
			  POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक ((pp_status & (PP_ON | PP_READY)) == PP_READY);
		dev_priv->is_lvds_on = true;
		अगर (dev_priv->ops->lvds_bl_घातer)
			dev_priv->ops->lvds_bl_घातer(dev, true);
	पूर्ण अन्यथा अणु
		अगर (dev_priv->ops->lvds_bl_घातer)
			dev_priv->ops->lvds_bl_घातer(dev, false);
		REG_WRITE(PP_CONTROL, REG_READ(PP_CONTROL) &
			  ~POWER_TARGET_ON);
		करो अणु
			pp_status = REG_READ(PP_STATUS);
		पूर्ण जबतक (pp_status & PP_ON);
		dev_priv->is_lvds_on = false;
		pm_request_idle(dev->dev);
	पूर्ण
	gma_घातer_end(dev);
पूर्ण

अटल व्योम oaktrail_lvds_dpms(काष्ठा drm_encoder *encoder, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा gma_encoder *gma_encoder = to_gma_encoder(encoder);

	अगर (mode == DRM_MODE_DPMS_ON)
		oaktrail_lvds_set_घातer(dev, gma_encoder, true);
	अन्यथा
		oaktrail_lvds_set_घातer(dev, gma_encoder, false);

	/* XXX: We never घातer करोwn the LVDS pairs. */
पूर्ण

अटल व्योम oaktrail_lvds_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_connector *connector = शून्य;
	काष्ठा drm_crtc *crtc = encoder->crtc;
	u32 lvds_port;
	uपूर्णांक64_t v = DRM_MODE_SCALE_FULLSCREEN;

	अगर (!gma_घातer_begin(dev, true))
		वापस;

	/*
	 * The LVDS pin pair will alपढ़ोy have been turned on in the
	 * psb_पूर्णांकel_crtc_mode_set since it has a large impact on the DPLL
	 * settings.
	 */
	lvds_port = (REG_READ(LVDS) &
		    (~LVDS_PIPEB_SELECT)) |
		    LVDS_PORT_EN |
		    LVDS_BORDER_EN;

	/* If the firmware says dither on Moorestown, or the BIOS करोes
	   on Oaktrail then enable dithering */
	अगर (mode_dev->panel_wants_dither || dev_priv->lvds_dither)
		lvds_port |= MRST_PANEL_8TO6_DITHER_ENABLE;

	REG_WRITE(LVDS, lvds_port);

	/* Find the connector we're trying to set up */
	list_क्रम_each_entry(connector, &mode_config->connector_list, head) अणु
		अगर (!connector->encoder || connector->encoder->crtc != crtc)
			जारी;
	पूर्ण

	अगर (!connector) अणु
		DRM_ERROR("Couldn't find connector when setting mode");
		gma_घातer_end(dev);
		वापस;
	पूर्ण

	drm_object_property_get_value(
		&connector->base,
		dev->mode_config.scaling_mode_property,
		&v);

	अगर (v == DRM_MODE_SCALE_NO_SCALE)
		REG_WRITE(PFIT_CONTROL, 0);
	अन्यथा अगर (v == DRM_MODE_SCALE_ASPECT) अणु
		अगर ((mode->vdisplay != adjusted_mode->crtc_vdisplay) ||
		    (mode->hdisplay != adjusted_mode->crtc_hdisplay)) अणु
			अगर ((adjusted_mode->crtc_hdisplay * mode->vdisplay) ==
			    (mode->hdisplay * adjusted_mode->crtc_vdisplay))
				REG_WRITE(PFIT_CONTROL, PFIT_ENABLE);
			अन्यथा अगर ((adjusted_mode->crtc_hdisplay *
				mode->vdisplay) > (mode->hdisplay *
				adjusted_mode->crtc_vdisplay))
				REG_WRITE(PFIT_CONTROL, PFIT_ENABLE |
					  PFIT_SCALING_MODE_PILLARBOX);
			अन्यथा
				REG_WRITE(PFIT_CONTROL, PFIT_ENABLE |
					  PFIT_SCALING_MODE_LETTERBOX);
		पूर्ण अन्यथा
			REG_WRITE(PFIT_CONTROL, PFIT_ENABLE);
	पूर्ण अन्यथा /*(v == DRM_MODE_SCALE_FULLSCREEN)*/
		REG_WRITE(PFIT_CONTROL, PFIT_ENABLE);

	gma_घातer_end(dev);
पूर्ण

अटल व्योम oaktrail_lvds_prepare(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_encoder *gma_encoder = to_gma_encoder(encoder);
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;

	अगर (!gma_घातer_begin(dev, true))
		वापस;

	mode_dev->saveBLC_PWM_CTL = REG_READ(BLC_PWM_CTL);
	mode_dev->backlight_duty_cycle = (mode_dev->saveBLC_PWM_CTL &
					  BACKLIGHT_DUTY_CYCLE_MASK);
	oaktrail_lvds_set_घातer(dev, gma_encoder, false);
	gma_घातer_end(dev);
पूर्ण

अटल u32 oaktrail_lvds_get_max_backlight(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 ret;

	अगर (gma_घातer_begin(dev, false)) अणु
		ret = ((REG_READ(BLC_PWM_CTL) &
			  BACKLIGHT_MODULATION_FREQ_MASK) >>
			  BACKLIGHT_MODULATION_FREQ_SHIFT) * 2;

		gma_घातer_end(dev);
	पूर्ण अन्यथा
		ret = ((dev_priv->regs.saveBLC_PWM_CTL &
			  BACKLIGHT_MODULATION_FREQ_MASK) >>
			  BACKLIGHT_MODULATION_FREQ_SHIFT) * 2;

	वापस ret;
पूर्ण

अटल व्योम oaktrail_lvds_commit(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_encoder *gma_encoder = to_gma_encoder(encoder);
	काष्ठा psb_पूर्णांकel_mode_device *mode_dev = &dev_priv->mode_dev;

	अगर (mode_dev->backlight_duty_cycle == 0)
		mode_dev->backlight_duty_cycle =
					oaktrail_lvds_get_max_backlight(dev);
	oaktrail_lvds_set_घातer(dev, gma_encoder, true);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs oaktrail_lvds_helper_funcs = अणु
	.dpms = oaktrail_lvds_dpms,
	.mode_fixup = psb_पूर्णांकel_lvds_mode_fixup,
	.prepare = oaktrail_lvds_prepare,
	.mode_set = oaktrail_lvds_mode_set,
	.commit = oaktrail_lvds_commit,
पूर्ण;

/* Returns the panel fixed mode from configuration. */

अटल व्योम oaktrail_lvds_get_configuration_mode(काष्ठा drm_device *dev,
					काष्ठा psb_पूर्णांकel_mode_device *mode_dev)
अणु
	काष्ठा drm_display_mode *mode = शून्य;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा oaktrail_timing_info *ti = &dev_priv->gct_data.DTD;

	mode_dev->panel_fixed_mode = शून्य;

	/* Use the firmware provided data on Moorestown */
	अगर (dev_priv->has_gct) अणु
		mode = kzalloc(माप(*mode), GFP_KERNEL);
		अगर (!mode)
			वापस;

		mode->hdisplay = (ti->hactive_hi << 8) | ti->hactive_lo;
		mode->vdisplay = (ti->vactive_hi << 8) | ti->vactive_lo;
		mode->hsync_start = mode->hdisplay + \
				((ti->hsync_offset_hi << 8) | \
				ti->hsync_offset_lo);
		mode->hsync_end = mode->hsync_start + \
				((ti->hsync_pulse_width_hi << 8) | \
				ti->hsync_pulse_width_lo);
		mode->htotal = mode->hdisplay + ((ti->hblank_hi << 8) | \
							ti->hblank_lo);
		mode->vsync_start = \
			mode->vdisplay + ((ti->vsync_offset_hi << 4) | \
						ti->vsync_offset_lo);
		mode->vsync_end = \
			mode->vsync_start + ((ti->vsync_pulse_width_hi << 4) | \
						ti->vsync_pulse_width_lo);
		mode->vtotal = mode->vdisplay + \
				((ti->vblank_hi << 8) | ti->vblank_lo);
		mode->घड़ी = ti->pixel_घड़ी * 10;
#अगर 0
		pr_info("hdisplay is %d\n", mode->hdisplay);
		pr_info("vdisplay is %d\n", mode->vdisplay);
		pr_info("HSS is %d\n", mode->hsync_start);
		pr_info("HSE is %d\n", mode->hsync_end);
		pr_info("htotal is %d\n", mode->htotal);
		pr_info("VSS is %d\n", mode->vsync_start);
		pr_info("VSE is %d\n", mode->vsync_end);
		pr_info("vtotal is %d\n", mode->vtotal);
		pr_info("clock is %d\n", mode->घड़ी);
#पूर्ण_अगर
		mode_dev->panel_fixed_mode = mode;
	पूर्ण

	/* Use the BIOS VBT mode अगर available */
	अगर (mode_dev->panel_fixed_mode == शून्य && mode_dev->vbt_mode)
		mode_dev->panel_fixed_mode = drm_mode_duplicate(dev,
						mode_dev->vbt_mode);

	/* Then try the LVDS VBT mode */
	अगर (mode_dev->panel_fixed_mode == शून्य)
		अगर (dev_priv->lfp_lvds_vbt_mode)
			mode_dev->panel_fixed_mode =
				drm_mode_duplicate(dev,
					dev_priv->lfp_lvds_vbt_mode);

	/* If we still got no mode then bail */
	अगर (mode_dev->panel_fixed_mode == शून्य)
		वापस;

	drm_mode_set_name(mode_dev->panel_fixed_mode);
	drm_mode_set_crtcinfo(mode_dev->panel_fixed_mode, 0);
पूर्ण

/**
 * oaktrail_lvds_init - setup LVDS connectors on this device
 * @dev: drm device
 * @mode_dev: PSB mode device
 *
 * Create the connector, रेजिस्टर the LVDS DDC bus, and try to figure out what
 * modes we can display on the LVDS panel (अगर present).
 */
व्योम oaktrail_lvds_init(काष्ठा drm_device *dev,
		    काष्ठा psb_पूर्णांकel_mode_device *mode_dev)
अणु
	काष्ठा gma_encoder *gma_encoder;
	काष्ठा gma_connector *gma_connector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा edid *edid;
	काष्ठा i2c_adapter *i2c_adap;
	काष्ठा drm_display_mode *scan;	/* *modes, *bios_mode; */

	gma_encoder = kzalloc(माप(काष्ठा gma_encoder), GFP_KERNEL);
	अगर (!gma_encoder)
		वापस;

	gma_connector = kzalloc(माप(काष्ठा gma_connector), GFP_KERNEL);
	अगर (!gma_connector)
		जाओ failed_connector;

	connector = &gma_connector->base;
	encoder = &gma_encoder->base;
	dev_priv->is_lvds_on = true;
	drm_connector_init(dev, connector,
			   &psb_पूर्णांकel_lvds_connector_funcs,
			   DRM_MODE_CONNECTOR_LVDS);

	drm_simple_encoder_init(dev, encoder, DRM_MODE_ENCODER_LVDS);

	gma_connector_attach_encoder(gma_connector, gma_encoder);
	gma_encoder->type = INTEL_OUTPUT_LVDS;

	drm_encoder_helper_add(encoder, &oaktrail_lvds_helper_funcs);
	drm_connector_helper_add(connector,
				 &psb_पूर्णांकel_lvds_connector_helper_funcs);
	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	drm_object_attach_property(&connector->base,
					dev->mode_config.scaling_mode_property,
					DRM_MODE_SCALE_FULLSCREEN);
	drm_object_attach_property(&connector->base,
					dev_priv->backlight_property,
					BRIGHTNESS_MAX_LEVEL);

	mode_dev->panel_wants_dither = false;
	अगर (dev_priv->has_gct)
		mode_dev->panel_wants_dither = (dev_priv->gct_data.
			Panel_Port_Control & MRST_PANEL_8TO6_DITHER_ENABLE);
        अगर (dev_priv->lvds_dither)
                mode_dev->panel_wants_dither = 1;

	/*
	 * LVDS discovery:
	 * 1) check क्रम EDID on DDC
	 * 2) check क्रम VBT data
	 * 3) check to see अगर LVDS is alपढ़ोy on
	 *    अगर none of the above, no panel
	 * 4) make sure lid is खोलो
	 *    अगर बंदd, act like it's not there क्रम now
	 */

	edid = शून्य;
	mutex_lock(&dev->mode_config.mutex);
	i2c_adap = i2c_get_adapter(dev_priv->ops->i2c_bus);
	अगर (i2c_adap)
		edid = drm_get_edid(connector, i2c_adap);
	अगर (edid == शून्य && dev_priv->lpc_gpio_base) अणु
		oaktrail_lvds_i2c_init(encoder);
		अगर (gma_encoder->ddc_bus != शून्य) अणु
			i2c_adap = &gma_encoder->ddc_bus->adapter;
			edid = drm_get_edid(connector, i2c_adap);
		पूर्ण
	पूर्ण
	/*
	 * Attempt to get the fixed panel mode from DDC.  Assume that the
	 * preferred mode is the right one.
	 */
	अगर (edid) अणु
		drm_connector_update_edid_property(connector, edid);
		drm_add_edid_modes(connector, edid);
		kमुक्त(edid);

		list_क्रम_each_entry(scan, &connector->probed_modes, head) अणु
			अगर (scan->type & DRM_MODE_TYPE_PREFERRED) अणु
				mode_dev->panel_fixed_mode =
				    drm_mode_duplicate(dev, scan);
				जाओ out;	/* FIXME: check क्रम quirks */
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		dev_err(dev->dev, "No ddc adapter available!\n");
	/*
	 * If we didn't get EDID, try geting panel timing
	 * from configuration data
	 */
	oaktrail_lvds_get_configuration_mode(dev, mode_dev);

	अगर (mode_dev->panel_fixed_mode) अणु
		mode_dev->panel_fixed_mode->type |= DRM_MODE_TYPE_PREFERRED;
		जाओ out;	/* FIXME: check क्रम quirks */
	पूर्ण

	/* If we still करोn't have a mode after all that, give up. */
	अगर (!mode_dev->panel_fixed_mode) अणु
		dev_err(dev->dev, "Found no modes on the lvds, ignoring the LVDS\n");
		जाओ failed_find;
	पूर्ण

out:
	mutex_unlock(&dev->mode_config.mutex);

	drm_connector_रेजिस्टर(connector);
	वापस;

failed_find:
	mutex_unlock(&dev->mode_config.mutex);

	dev_dbg(dev->dev, "No LVDS modes found, disabling.\n");
	अगर (gma_encoder->ddc_bus) अणु
		psb_पूर्णांकel_i2c_destroy(gma_encoder->ddc_bus);
		gma_encoder->ddc_bus = शून्य;
	पूर्ण

/* failed_ddc: */

	drm_encoder_cleanup(encoder);
	drm_connector_cleanup(connector);
	kमुक्त(gma_connector);
failed_connector:
	kमुक्त(gma_encoder);
पूर्ण

