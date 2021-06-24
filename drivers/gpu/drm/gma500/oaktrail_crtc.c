<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2009 Intel Corporation
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_fourcc.h>

#समावेश "framebuffer.h"
#समावेश "gma_display.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

#घोषणा MRST_LIMIT_LVDS_100L	0
#घोषणा MRST_LIMIT_LVDS_83	1
#घोषणा MRST_LIMIT_LVDS_100	2
#घोषणा MRST_LIMIT_SDVO		3

#घोषणा MRST_DOT_MIN		  19750
#घोषणा MRST_DOT_MAX		  120000
#घोषणा MRST_M_MIN_100L		    20
#घोषणा MRST_M_MIN_100		    10
#घोषणा MRST_M_MIN_83		    12
#घोषणा MRST_M_MAX_100L		    34
#घोषणा MRST_M_MAX_100		    17
#घोषणा MRST_M_MAX_83		    20
#घोषणा MRST_P1_MIN		    2
#घोषणा MRST_P1_MAX_0		    7
#घोषणा MRST_P1_MAX_1		    8

अटल bool mrst_lvds_find_best_pll(स्थिर काष्ठा gma_limit_t *limit,
				    काष्ठा drm_crtc *crtc, पूर्णांक target,
				    पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *best_घड़ी);

अटल bool mrst_sdvo_find_best_pll(स्थिर काष्ठा gma_limit_t *limit,
				    काष्ठा drm_crtc *crtc, पूर्णांक target,
				    पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *best_घड़ी);

अटल स्थिर काष्ठा gma_limit_t mrst_limits[] = अणु
	अणु			/* MRST_LIMIT_LVDS_100L */
	 .करोt = अणु.min = MRST_DOT_MIN, .max = MRST_DOT_MAXपूर्ण,
	 .m = अणु.min = MRST_M_MIN_100L, .max = MRST_M_MAX_100Lपूर्ण,
	 .p1 = अणु.min = MRST_P1_MIN, .max = MRST_P1_MAX_1पूर्ण,
	 .find_pll = mrst_lvds_find_best_pll,
	 पूर्ण,
	अणु			/* MRST_LIMIT_LVDS_83L */
	 .करोt = अणु.min = MRST_DOT_MIN, .max = MRST_DOT_MAXपूर्ण,
	 .m = अणु.min = MRST_M_MIN_83, .max = MRST_M_MAX_83पूर्ण,
	 .p1 = अणु.min = MRST_P1_MIN, .max = MRST_P1_MAX_0पूर्ण,
	 .find_pll = mrst_lvds_find_best_pll,
	 पूर्ण,
	अणु			/* MRST_LIMIT_LVDS_100 */
	 .करोt = अणु.min = MRST_DOT_MIN, .max = MRST_DOT_MAXपूर्ण,
	 .m = अणु.min = MRST_M_MIN_100, .max = MRST_M_MAX_100पूर्ण,
	 .p1 = अणु.min = MRST_P1_MIN, .max = MRST_P1_MAX_1पूर्ण,
	 .find_pll = mrst_lvds_find_best_pll,
	 पूर्ण,
	अणु			/* MRST_LIMIT_SDVO */
	 .vco = अणु.min = 1400000, .max = 2800000पूर्ण,
	 .n = अणु.min = 3, .max = 7पूर्ण,
	 .m = अणु.min = 80, .max = 137पूर्ण,
	 .p1 = अणु.min = 1, .max = 2पूर्ण,
	 .p2 = अणु.करोt_limit = 200000, .p2_slow = 10, .p2_fast = 10पूर्ण,
	 .find_pll = mrst_sdvo_find_best_pll,
	 पूर्ण,
पूर्ण;

#घोषणा MRST_M_MIN	    10
अटल स्थिर u32 oaktrail_m_converts[] = अणु
	0x2B, 0x15, 0x2A, 0x35, 0x1A, 0x0D, 0x26, 0x33, 0x19, 0x2C,
	0x36, 0x3B, 0x1D, 0x2E, 0x37, 0x1B, 0x2D, 0x16, 0x0B, 0x25,
	0x12, 0x09, 0x24, 0x32, 0x39, 0x1c,
पूर्ण;

अटल स्थिर काष्ठा gma_limit_t *mrst_limit(काष्ठा drm_crtc *crtc,
					    पूर्णांक refclk)
अणु
	स्थिर काष्ठा gma_limit_t *limit = शून्य;
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;

	अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS)
	    || gma_pipe_has_type(crtc, INTEL_OUTPUT_MIPI)) अणु
		चयन (dev_priv->core_freq) अणु
		हाल 100:
			limit = &mrst_limits[MRST_LIMIT_LVDS_100L];
			अवरोध;
		हाल 166:
			limit = &mrst_limits[MRST_LIMIT_LVDS_83];
			अवरोध;
		हाल 200:
			limit = &mrst_limits[MRST_LIMIT_LVDS_100];
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_SDVO)) अणु
		limit = &mrst_limits[MRST_LIMIT_SDVO];
	पूर्ण अन्यथा अणु
		limit = शून्य;
		dev_err(dev->dev, "mrst_limit Wrong display type.\n");
	पूर्ण

	वापस limit;
पूर्ण

/** Derive the pixel घड़ी क्रम the given refclk and भागisors क्रम 8xx chips. */
अटल व्योम mrst_lvds_घड़ी(पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *घड़ी)
अणु
	घड़ी->करोt = (refclk * घड़ी->m) / (14 * घड़ी->p1);
पूर्ण

अटल व्योम mrst_prपूर्णांक_pll(काष्ठा gma_घड़ी_प्रकार *घड़ी)
अणु
	DRM_DEBUG_DRIVER("dotclock=%d,  m=%d, m1=%d, m2=%d, n=%d, p1=%d, p2=%d\n",
			 घड़ी->करोt, घड़ी->m, घड़ी->m1, घड़ी->m2, घड़ी->n,
			 घड़ी->p1, घड़ी->p2);
पूर्ण

अटल bool mrst_sdvo_find_best_pll(स्थिर काष्ठा gma_limit_t *limit,
				    काष्ठा drm_crtc *crtc, पूर्णांक target,
				    पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *best_घड़ी)
अणु
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	u32 target_vco, actual_freq;
	s32 freq_error, min_error = 100000;

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));
	स_रखो(&घड़ी, 0, माप(घड़ी));

	क्रम (घड़ी.m = limit->m.min; घड़ी.m <= limit->m.max; घड़ी.m++) अणु
		क्रम (घड़ी.n = limit->n.min; घड़ी.n <= limit->n.max;
		     घड़ी.n++) अणु
			क्रम (घड़ी.p1 = limit->p1.min;
			     घड़ी.p1 <= limit->p1.max; घड़ी.p1++) अणु
				/* p2 value always stored in p2_slow on SDVO */
				घड़ी.p = घड़ी.p1 * limit->p2.p2_slow;
				target_vco = target * घड़ी.p;

				/* VCO will increase at this poपूर्णांक so अवरोध */
				अगर (target_vco > limit->vco.max)
					अवरोध;

				अगर (target_vco < limit->vco.min)
					जारी;

				actual_freq = (refclk * घड़ी.m) /
					      (घड़ी.n * घड़ी.p);
				freq_error = 10000 -
					     ((target * 10000) / actual_freq);

				अगर (freq_error < -min_error) अणु
					/* freq_error will start to decrease at
					   this poपूर्णांक so अवरोध */
					अवरोध;
				पूर्ण

				अगर (freq_error < 0)
					freq_error = -freq_error;

				अगर (freq_error < min_error) अणु
					min_error = freq_error;
					*best_घड़ी = घड़ी;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (min_error == 0)
			अवरोध;
	पूर्ण

	वापस min_error == 0;
पूर्ण

/*
 * Returns a set of भागisors क्रम the desired target घड़ी with the given refclk,
 * or FALSE.  Divisor values are the actual भागisors क्रम
 */
अटल bool mrst_lvds_find_best_pll(स्थिर काष्ठा gma_limit_t *limit,
				    काष्ठा drm_crtc *crtc, पूर्णांक target,
				    पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *best_घड़ी)
अणु
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	पूर्णांक err = target;

	स_रखो(best_घड़ी, 0, माप(*best_घड़ी));
	स_रखो(&घड़ी, 0, माप(घड़ी));

	क्रम (घड़ी.m = limit->m.min; घड़ी.m <= limit->m.max; घड़ी.m++) अणु
		क्रम (घड़ी.p1 = limit->p1.min; घड़ी.p1 <= limit->p1.max;
		     घड़ी.p1++) अणु
			पूर्णांक this_err;

			mrst_lvds_घड़ी(refclk, &घड़ी);

			this_err = असल(घड़ी.करोt - target);
			अगर (this_err < err) अणु
				*best_घड़ी = घड़ी;
				err = this_err;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस err != target;
पूर्ण

/*
 * Sets the घातer management mode of the pipe and plane.
 *
 * This code should probably grow support क्रम turning the cursor off and back
 * on appropriately at the same समय as we're turning the pipe off/on.
 */
अटल व्योम oaktrail_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	u32 temp;
	पूर्णांक i;
	पूर्णांक need_aux = gma_pipe_has_type(crtc, INTEL_OUTPUT_SDVO) ? 1 : 0;

	अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_HDMI)) अणु
		oaktrail_crtc_hdmi_dpms(crtc, mode);
		वापस;
	पूर्ण

	अगर (!gma_घातer_begin(dev, true))
		वापस;

	/* XXX: When our outमाला_दो are all unaware of DPMS modes other than off
	 * and on, we should map those modes to DRM_MODE_DPMS_OFF in the CRTC.
	 */
	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
	हाल DRM_MODE_DPMS_STANDBY:
	हाल DRM_MODE_DPMS_SUSPEND:
		क्रम (i = 0; i <= need_aux; i++) अणु
			/* Enable the DPLL */
			temp = REG_READ_WITH_AUX(map->dpll, i);
			अगर ((temp & DPLL_VCO_ENABLE) == 0) अणु
				REG_WRITE_WITH_AUX(map->dpll, temp, i);
				REG_READ_WITH_AUX(map->dpll, i);
				/* Wait क्रम the घड़ीs to stabilize. */
				udelay(150);
				REG_WRITE_WITH_AUX(map->dpll,
						   temp | DPLL_VCO_ENABLE, i);
				REG_READ_WITH_AUX(map->dpll, i);
				/* Wait क्रम the घड़ीs to stabilize. */
				udelay(150);
				REG_WRITE_WITH_AUX(map->dpll,
						   temp | DPLL_VCO_ENABLE, i);
				REG_READ_WITH_AUX(map->dpll, i);
				/* Wait क्रम the घड़ीs to stabilize. */
				udelay(150);
			पूर्ण

			/* Enable the pipe */
			temp = REG_READ_WITH_AUX(map->conf, i);
			अगर ((temp & PIPEACONF_ENABLE) == 0) अणु
				REG_WRITE_WITH_AUX(map->conf,
						   temp | PIPEACONF_ENABLE, i);
			पूर्ण

			/* Enable the plane */
			temp = REG_READ_WITH_AUX(map->cntr, i);
			अगर ((temp & DISPLAY_PLANE_ENABLE) == 0) अणु
				REG_WRITE_WITH_AUX(map->cntr,
						   temp | DISPLAY_PLANE_ENABLE,
						   i);
				/* Flush the plane changes */
				REG_WRITE_WITH_AUX(map->base,
					REG_READ_WITH_AUX(map->base, i), i);
			पूर्ण

		पूर्ण
		gma_crtc_load_lut(crtc);

		/* Give the overlay scaler a chance to enable
		   अगर it's on this pipe */
		/* psb_पूर्णांकel_crtc_dpms_video(crtc, true); TODO */
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		/* Give the overlay scaler a chance to disable
		 * अगर it's on this pipe */
		/* psb_पूर्णांकel_crtc_dpms_video(crtc, FALSE); TODO */

		क्रम (i = 0; i <= need_aux; i++) अणु
			/* Disable the VGA plane that we never use */
			REG_WRITE_WITH_AUX(VGACNTRL, VGA_DISP_DISABLE, i);
			/* Disable display plane */
			temp = REG_READ_WITH_AUX(map->cntr, i);
			अगर ((temp & DISPLAY_PLANE_ENABLE) != 0) अणु
				REG_WRITE_WITH_AUX(map->cntr,
					temp & ~DISPLAY_PLANE_ENABLE, i);
				/* Flush the plane changes */
				REG_WRITE_WITH_AUX(map->base,
						   REG_READ(map->base), i);
				REG_READ_WITH_AUX(map->base, i);
			पूर्ण

			/* Next, disable display pipes */
			temp = REG_READ_WITH_AUX(map->conf, i);
			अगर ((temp & PIPEACONF_ENABLE) != 0) अणु
				REG_WRITE_WITH_AUX(map->conf,
						   temp & ~PIPEACONF_ENABLE, i);
				REG_READ_WITH_AUX(map->conf, i);
			पूर्ण
			/* Wait क्रम क्रम the pipe disable to take effect. */
			gma_रुको_क्रम_vblank(dev);

			temp = REG_READ_WITH_AUX(map->dpll, i);
			अगर ((temp & DPLL_VCO_ENABLE) != 0) अणु
				REG_WRITE_WITH_AUX(map->dpll,
						   temp & ~DPLL_VCO_ENABLE, i);
				REG_READ_WITH_AUX(map->dpll, i);
			पूर्ण

			/* Wait क्रम the घड़ीs to turn off. */
			udelay(150);
		पूर्ण
		अवरोध;
	पूर्ण

	/* Set FIFO Watermarks (values taken from EMGD) */
	REG_WRITE(DSPARB, 0x3f80);
	REG_WRITE(DSPFW1, 0x3f8f0404);
	REG_WRITE(DSPFW2, 0x04040f04);
	REG_WRITE(DSPFW3, 0x0);
	REG_WRITE(DSPFW4, 0x04040404);
	REG_WRITE(DSPFW5, 0x04040404);
	REG_WRITE(DSPFW6, 0x78);
	REG_WRITE(DSPCHICKENBIT, REG_READ(DSPCHICKENBIT) | 0xc040);

	gma_घातer_end(dev);
पूर्ण

/*
 * Return the pipe currently connected to the panel fitter,
 * or -1 अगर the panel fitter is not present or not in use
 */
अटल पूर्णांक oaktrail_panel_fitter_pipe(काष्ठा drm_device *dev)
अणु
	u32 pfit_control;

	pfit_control = REG_READ(PFIT_CONTROL);

	/* See अगर the panel fitter is in use */
	अगर ((pfit_control & PFIT_ENABLE) == 0)
		वापस -1;
	वापस (pfit_control >> 29) & 3;
पूर्ण

अटल पूर्णांक oaktrail_crtc_mode_set(काष्ठा drm_crtc *crtc,
			      काष्ठा drm_display_mode *mode,
			      काष्ठा drm_display_mode *adjusted_mode,
			      पूर्णांक x, पूर्णांक y,
			      काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	पूर्णांक refclk = 0;
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	स्थिर काष्ठा gma_limit_t *limit;
	u32 dpll = 0, fp = 0, dspcntr, pipeconf;
	bool ok, is_sdvo = false;
	bool is_lvds = false;
	bool is_mipi = false;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा gma_encoder *gma_encoder = शून्य;
	uपूर्णांक64_t scalingType = DRM_MODE_SCALE_FULLSCREEN;
	काष्ठा drm_connector *connector;
	पूर्णांक i;
	पूर्णांक need_aux = gma_pipe_has_type(crtc, INTEL_OUTPUT_SDVO) ? 1 : 0;

	अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_HDMI))
		वापस oaktrail_crtc_hdmi_mode_set(crtc, mode, adjusted_mode, x, y, old_fb);

	अगर (!gma_घातer_begin(dev, true))
		वापस 0;

	स_नकल(&gma_crtc->saved_mode,
		mode,
		माप(काष्ठा drm_display_mode));
	स_नकल(&gma_crtc->saved_adjusted_mode,
		adjusted_mode,
		माप(काष्ठा drm_display_mode));

	list_क्रम_each_entry(connector, &mode_config->connector_list, head) अणु
		अगर (!connector->encoder || connector->encoder->crtc != crtc)
			जारी;

		gma_encoder = gma_attached_encoder(connector);

		चयन (gma_encoder->type) अणु
		हाल INTEL_OUTPUT_LVDS:
			is_lvds = true;
			अवरोध;
		हाल INTEL_OUTPUT_SDVO:
			is_sdvo = true;
			अवरोध;
		हाल INTEL_OUTPUT_MIPI:
			is_mipi = true;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Disable the VGA plane that we never use */
	क्रम (i = 0; i <= need_aux; i++)
		REG_WRITE_WITH_AUX(VGACNTRL, VGA_DISP_DISABLE, i);

	/* Disable the panel fitter अगर it was on our pipe */
	अगर (oaktrail_panel_fitter_pipe(dev) == pipe)
		REG_WRITE(PFIT_CONTROL, 0);

	क्रम (i = 0; i <= need_aux; i++) अणु
		REG_WRITE_WITH_AUX(map->src, ((mode->crtc_hdisplay - 1) << 16) |
					     (mode->crtc_vdisplay - 1), i);
	पूर्ण

	अगर (gma_encoder)
		drm_object_property_get_value(&connector->base,
			dev->mode_config.scaling_mode_property, &scalingType);

	अगर (scalingType == DRM_MODE_SCALE_NO_SCALE) अणु
		/* Moorestown करोesn't have रेजिस्टर support क्रम centering so
		 * we need to mess with the h/vblank and h/vsync start and
		 * ends to get centering */
		पूर्णांक offsetX = 0, offsetY = 0;

		offsetX = (adjusted_mode->crtc_hdisplay -
			   mode->crtc_hdisplay) / 2;
		offsetY = (adjusted_mode->crtc_vdisplay -
			   mode->crtc_vdisplay) / 2;

		क्रम (i = 0; i <= need_aux; i++) अणु
			REG_WRITE_WITH_AUX(map->htotal, (mode->crtc_hdisplay - 1) |
				((adjusted_mode->crtc_htotal - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->vtotal, (mode->crtc_vdisplay - 1) |
				((adjusted_mode->crtc_vtotal - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->hblank,
				(adjusted_mode->crtc_hblank_start - offsetX - 1) |
				((adjusted_mode->crtc_hblank_end - offsetX - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->hsync,
				(adjusted_mode->crtc_hsync_start - offsetX - 1) |
				((adjusted_mode->crtc_hsync_end - offsetX - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->vblank,
				(adjusted_mode->crtc_vblank_start - offsetY - 1) |
				((adjusted_mode->crtc_vblank_end - offsetY - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->vsync,
				(adjusted_mode->crtc_vsync_start - offsetY - 1) |
				((adjusted_mode->crtc_vsync_end - offsetY - 1) << 16), i);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i <= need_aux; i++) अणु
			REG_WRITE_WITH_AUX(map->htotal, (adjusted_mode->crtc_hdisplay - 1) |
				((adjusted_mode->crtc_htotal - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->vtotal, (adjusted_mode->crtc_vdisplay - 1) |
				((adjusted_mode->crtc_vtotal - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->hblank, (adjusted_mode->crtc_hblank_start - 1) |
				((adjusted_mode->crtc_hblank_end - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->hsync, (adjusted_mode->crtc_hsync_start - 1) |
				((adjusted_mode->crtc_hsync_end - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->vblank, (adjusted_mode->crtc_vblank_start - 1) |
				((adjusted_mode->crtc_vblank_end - 1) << 16), i);
			REG_WRITE_WITH_AUX(map->vsync, (adjusted_mode->crtc_vsync_start - 1) |
				((adjusted_mode->crtc_vsync_end - 1) << 16), i);
		पूर्ण
	पूर्ण

	/* Flush the plane changes */
	अणु
		स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs =
		    crtc->helper_निजी;
		crtc_funcs->mode_set_base(crtc, x, y, old_fb);
	पूर्ण

	/* setup pipeconf */
	pipeconf = REG_READ(map->conf);

	/* Set up the display plane रेजिस्टर */
	dspcntr = REG_READ(map->cntr);
	dspcntr |= DISPPLANE_GAMMA_ENABLE;

	अगर (pipe == 0)
		dspcntr |= DISPPLANE_SEL_PIPE_A;
	अन्यथा
		dspcntr |= DISPPLANE_SEL_PIPE_B;

	अगर (is_mipi)
		जाओ oaktrail_crtc_mode_set_निकास;


	dpll = 0;		/*BIT16 = 0 क्रम 100MHz reference */

	refclk = is_sdvo ? 96000 : dev_priv->core_freq * 1000;
	limit = mrst_limit(crtc, refclk);
	ok = limit->find_pll(limit, crtc, adjusted_mode->घड़ी,
			     refclk, &घड़ी);

	अगर (is_sdvo) अणु
		/* Convert calculated values to रेजिस्टर values */
		घड़ी.p1 = (1L << (घड़ी.p1 - 1));
		घड़ी.m -= 2;
		घड़ी.n = (1L << (घड़ी.n - 1));
	पूर्ण

	अगर (!ok)
		DRM_ERROR("Failed to find proper PLL settings");

	mrst_prपूर्णांक_pll(&घड़ी);

	अगर (is_sdvo)
		fp = घड़ी.n << 16 | घड़ी.m;
	अन्यथा
		fp = oaktrail_m_converts[(घड़ी.m - MRST_M_MIN)] << 8;

	dpll |= DPLL_VGA_MODE_DIS;


	dpll |= DPLL_VCO_ENABLE;

	अगर (is_lvds)
		dpll |= DPLLA_MODE_LVDS;
	अन्यथा
		dpll |= DPLLB_MODE_DAC_SERIAL;

	अगर (is_sdvo) अणु
		पूर्णांक sdvo_pixel_multiply =
		    adjusted_mode->घड़ी / mode->घड़ी;

		dpll |= DPLL_DVO_HIGH_SPEED;
		dpll |=
		    (sdvo_pixel_multiply -
		     1) << SDVO_MULTIPLIER_SHIFT_HIRES;
	पूर्ण


	/* compute biपंचांगask from p1 value */
	अगर (is_sdvo)
		dpll |= घड़ी.p1 << 16; // dpll |= (1 << (घड़ी.p1 - 1)) << 16;
	अन्यथा
		dpll |= (1 << (घड़ी.p1 - 2)) << 17;

	dpll |= DPLL_VCO_ENABLE;

	अगर (dpll & DPLL_VCO_ENABLE) अणु
		क्रम (i = 0; i <= need_aux; i++) अणु
			REG_WRITE_WITH_AUX(map->fp0, fp, i);
			REG_WRITE_WITH_AUX(map->dpll, dpll & ~DPLL_VCO_ENABLE, i);
			REG_READ_WITH_AUX(map->dpll, i);
			/* Check the DPLLA lock bit PIPEACONF[29] */
			udelay(150);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i <= need_aux; i++) अणु
		REG_WRITE_WITH_AUX(map->fp0, fp, i);
		REG_WRITE_WITH_AUX(map->dpll, dpll, i);
		REG_READ_WITH_AUX(map->dpll, i);
		/* Wait क्रम the घड़ीs to stabilize. */
		udelay(150);

		/* ग_लिखो it again -- the BIOS करोes, after all */
		REG_WRITE_WITH_AUX(map->dpll, dpll, i);
		REG_READ_WITH_AUX(map->dpll, i);
		/* Wait क्रम the घड़ीs to stabilize. */
		udelay(150);

		REG_WRITE_WITH_AUX(map->conf, pipeconf, i);
		REG_READ_WITH_AUX(map->conf, i);
		gma_रुको_क्रम_vblank(dev);

		REG_WRITE_WITH_AUX(map->cntr, dspcntr, i);
		gma_रुको_क्रम_vblank(dev);
	पूर्ण

oaktrail_crtc_mode_set_निकास:
	gma_घातer_end(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक oaktrail_pipe_set_base(काष्ठा drm_crtc *crtc,
			    पूर्णांक x, पूर्णांक y, काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा drm_framebuffer *fb = crtc->primary->fb;
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	अचिन्हित दीर्घ start, offset;

	u32 dspcntr;
	पूर्णांक ret = 0;

	/* no fb bound */
	अगर (!fb) अणु
		dev_dbg(dev->dev, "No FB bound\n");
		वापस 0;
	पूर्ण

	अगर (!gma_घातer_begin(dev, true))
		वापस 0;

	start = to_gtt_range(fb->obj[0])->offset;
	offset = y * fb->pitches[0] + x * fb->क्रमmat->cpp[0];

	REG_WRITE(map->stride, fb->pitches[0]);

	dspcntr = REG_READ(map->cntr);
	dspcntr &= ~DISPPLANE_PIXFORMAT_MASK;

	चयन (fb->क्रमmat->cpp[0] * 8) अणु
	हाल 8:
		dspcntr |= DISPPLANE_8BPP;
		अवरोध;
	हाल 16:
		अगर (fb->क्रमmat->depth == 15)
			dspcntr |= DISPPLANE_15_16BPP;
		अन्यथा
			dspcntr |= DISPPLANE_16BPP;
		अवरोध;
	हाल 24:
	हाल 32:
		dspcntr |= DISPPLANE_32BPP_NO_ALPHA;
		अवरोध;
	शेष:
		dev_err(dev->dev, "Unknown color depth\n");
		ret = -EINVAL;
		जाओ pipe_set_base_निकास;
	पूर्ण
	REG_WRITE(map->cntr, dspcntr);

	REG_WRITE(map->base, offset);
	REG_READ(map->base);
	REG_WRITE(map->surf, start);
	REG_READ(map->surf);

pipe_set_base_निकास:
	gma_घातer_end(dev);
	वापस ret;
पूर्ण

स्थिर काष्ठा drm_crtc_helper_funcs oaktrail_helper_funcs = अणु
	.dpms = oaktrail_crtc_dpms,
	.mode_set = oaktrail_crtc_mode_set,
	.mode_set_base = oaktrail_pipe_set_base,
	.prepare = gma_crtc_prepare,
	.commit = gma_crtc_commit,
पूर्ण;

/* Not used yet */
स्थिर काष्ठा gma_घड़ी_funcs mrst_घड़ी_funcs = अणु
	.घड़ी = mrst_lvds_घड़ी,
	.limit = mrst_limit,
	.pll_is_valid = gma_pll_is_valid,
पूर्ण;
