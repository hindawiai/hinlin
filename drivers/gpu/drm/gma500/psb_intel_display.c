<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright थतऊ 2006-2011 Intel Corporation
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>

#समावेश <drm/drm_plane_helper.h>

#समावेश "framebuffer.h"
#समावेश "gma_display.h"
#समावेश "power.h"
#समावेश "psb_drv.h"
#समावेश "psb_intel_drv.h"
#समावेश "psb_intel_reg.h"

#घोषणा INTEL_LIMIT_I9XX_SDVO_DAC   0
#घोषणा INTEL_LIMIT_I9XX_LVDS	    1

अटल स्थिर काष्ठा gma_limit_t psb_पूर्णांकel_limits[] = अणु
	अणु			/* INTEL_LIMIT_I9XX_SDVO_DAC */
	 .करोt = अणु.min = 20000, .max = 400000पूर्ण,
	 .vco = अणु.min = 1400000, .max = 2800000पूर्ण,
	 .n = अणु.min = 1, .max = 6पूर्ण,
	 .m = अणु.min = 70, .max = 120पूर्ण,
	 .m1 = अणु.min = 8, .max = 18पूर्ण,
	 .m2 = अणु.min = 3, .max = 7पूर्ण,
	 .p = अणु.min = 5, .max = 80पूर्ण,
	 .p1 = अणु.min = 1, .max = 8पूर्ण,
	 .p2 = अणु.करोt_limit = 200000, .p2_slow = 10, .p2_fast = 5पूर्ण,
	 .find_pll = gma_find_best_pll,
	 पूर्ण,
	अणु			/* INTEL_LIMIT_I9XX_LVDS */
	 .करोt = अणु.min = 20000, .max = 400000पूर्ण,
	 .vco = अणु.min = 1400000, .max = 2800000पूर्ण,
	 .n = अणु.min = 1, .max = 6पूर्ण,
	 .m = अणु.min = 70, .max = 120पूर्ण,
	 .m1 = अणु.min = 8, .max = 18पूर्ण,
	 .m2 = अणु.min = 3, .max = 7पूर्ण,
	 .p = अणु.min = 7, .max = 98पूर्ण,
	 .p1 = अणु.min = 1, .max = 8पूर्ण,
	 /* The single-channel range is 25-112Mhz, and dual-channel
	  * is 80-224Mhz.  Prefer single channel as much as possible.
	  */
	 .p2 = अणु.करोt_limit = 112000, .p2_slow = 14, .p2_fast = 7पूर्ण,
	 .find_pll = gma_find_best_pll,
	 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा gma_limit_t *psb_पूर्णांकel_limit(काष्ठा drm_crtc *crtc,
						 पूर्णांक refclk)
अणु
	स्थिर काष्ठा gma_limit_t *limit;

	अगर (gma_pipe_has_type(crtc, INTEL_OUTPUT_LVDS))
		limit = &psb_पूर्णांकel_limits[INTEL_LIMIT_I9XX_LVDS];
	अन्यथा
		limit = &psb_पूर्णांकel_limits[INTEL_LIMIT_I9XX_SDVO_DAC];
	वापस limit;
पूर्ण

अटल व्योम psb_पूर्णांकel_घड़ी(पूर्णांक refclk, काष्ठा gma_घड़ी_प्रकार *घड़ी)
अणु
	घड़ी->m = 5 * (घड़ी->m1 + 2) + (घड़ी->m2 + 2);
	घड़ी->p = घड़ी->p1 * घड़ी->p2;
	घड़ी->vco = refclk * घड़ी->m / (घड़ी->n + 2);
	घड़ी->करोt = घड़ी->vco / घड़ी->p;
पूर्ण

/*
 * Return the pipe currently connected to the panel fitter,
 * or -1 अगर the panel fitter is not present or not in use
 */
अटल पूर्णांक psb_पूर्णांकel_panel_fitter_pipe(काष्ठा drm_device *dev)
अणु
	u32 pfit_control;

	pfit_control = REG_READ(PFIT_CONTROL);

	/* See अगर the panel fitter is in use */
	अगर ((pfit_control & PFIT_ENABLE) == 0)
		वापस -1;
	/* Must be on PIPE 1 क्रम PSB */
	वापस 1;
पूर्ण

अटल पूर्णांक psb_पूर्णांकel_crtc_mode_set(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode,
			       पूर्णांक x, पूर्णांक y,
			       काष्ठा drm_framebuffer *old_fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	स्थिर काष्ठा drm_crtc_helper_funcs *crtc_funcs = crtc->helper_निजी;
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	पूर्णांक refclk;
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	u32 dpll = 0, fp = 0, dspcntr, pipeconf;
	bool ok, is_sdvo = false;
	bool is_lvds = false, is_tv = false;
	काष्ठा drm_mode_config *mode_config = &dev->mode_config;
	काष्ठा drm_connector *connector;
	स्थिर काष्ठा gma_limit_t *limit;

	/* No scan out no play */
	अगर (crtc->primary->fb == शून्य) अणु
		crtc_funcs->mode_set_base(crtc, x, y, old_fb);
		वापस 0;
	पूर्ण

	list_क्रम_each_entry(connector, &mode_config->connector_list, head) अणु
		काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);

		अगर (!connector->encoder
		    || connector->encoder->crtc != crtc)
			जारी;

		चयन (gma_encoder->type) अणु
		हाल INTEL_OUTPUT_LVDS:
			is_lvds = true;
			अवरोध;
		हाल INTEL_OUTPUT_SDVO:
			is_sdvo = true;
			अवरोध;
		हाल INTEL_OUTPUT_TVOUT:
			is_tv = true;
			अवरोध;
		पूर्ण
	पूर्ण

	refclk = 96000;

	limit = gma_crtc->घड़ी_funcs->limit(crtc, refclk);

	ok = limit->find_pll(limit, crtc, adjusted_mode->घड़ी, refclk,
				 &घड़ी);
	अगर (!ok) अणु
		DRM_ERROR("Couldn't find PLL settings for mode! target: %d, actual: %d",
			  adjusted_mode->घड़ी, घड़ी.करोt);
		वापस 0;
	पूर्ण

	fp = घड़ी.n << 16 | घड़ी.m1 << 8 | घड़ी.m2;

	dpll = DPLL_VGA_MODE_DIS;
	अगर (is_lvds) अणु
		dpll |= DPLLB_MODE_LVDS;
		dpll |= DPLL_DVO_HIGH_SPEED;
	पूर्ण अन्यथा
		dpll |= DPLLB_MODE_DAC_SERIAL;
	अगर (is_sdvo) अणु
		पूर्णांक sdvo_pixel_multiply =
			    adjusted_mode->घड़ी / mode->घड़ी;
		dpll |= DPLL_DVO_HIGH_SPEED;
		dpll |=
		    (sdvo_pixel_multiply - 1) << SDVO_MULTIPLIER_SHIFT_HIRES;
	पूर्ण

	/* compute biपंचांगask from p1 value */
	dpll |= (1 << (घड़ी.p1 - 1)) << 16;
	चयन (घड़ी.p2) अणु
	हाल 5:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_5;
		अवरोध;
	हाल 7:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_7;
		अवरोध;
	हाल 10:
		dpll |= DPLL_DAC_SERIAL_P2_CLOCK_DIV_10;
		अवरोध;
	हाल 14:
		dpll |= DPLLB_LVDS_P2_CLOCK_DIV_14;
		अवरोध;
	पूर्ण

	अगर (is_tv) अणु
		/* XXX: just matching BIOS क्रम now */
/*	dpll |= PLL_REF_INPUT_TVCLKINBC; */
		dpll |= 3;
	पूर्ण
	dpll |= PLL_REF_INPUT_DREFCLK;

	/* setup pipeconf */
	pipeconf = REG_READ(map->conf);

	/* Set up the display plane रेजिस्टर */
	dspcntr = DISPPLANE_GAMMA_ENABLE;

	अगर (pipe == 0)
		dspcntr |= DISPPLANE_SEL_PIPE_A;
	अन्यथा
		dspcntr |= DISPPLANE_SEL_PIPE_B;

	dspcntr |= DISPLAY_PLANE_ENABLE;
	pipeconf |= PIPEACONF_ENABLE;
	dpll |= DPLL_VCO_ENABLE;


	/* Disable the panel fitter अगर it was on our pipe */
	अगर (psb_पूर्णांकel_panel_fitter_pipe(dev) == pipe)
		REG_WRITE(PFIT_CONTROL, 0);

	drm_mode_debug_prपूर्णांकmodeline(mode);

	अगर (dpll & DPLL_VCO_ENABLE) अणु
		REG_WRITE(map->fp0, fp);
		REG_WRITE(map->dpll, dpll & ~DPLL_VCO_ENABLE);
		REG_READ(map->dpll);
		udelay(150);
	पूर्ण

	/* The LVDS pin pair needs to be on beक्रमe the DPLLs are enabled.
	 * This is an exception to the general rule that mode_set करोesn't turn
	 * things on.
	 */
	अगर (is_lvds) अणु
		u32 lvds = REG_READ(LVDS);

		lvds &= ~LVDS_PIPEB_SELECT;
		अगर (pipe == 1)
			lvds |= LVDS_PIPEB_SELECT;

		lvds |= LVDS_PORT_EN | LVDS_A0A2_CLKA_POWER_UP;
		/* Set the B0-B3 data pairs corresponding to
		 * whether we're going to
		 * set the DPLLs क्रम dual-channel mode or not.
		 */
		lvds &= ~(LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP);
		अगर (घड़ी.p2 == 7)
			lvds |= LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP;

		/* It would be nice to set 24 vs 18-bit mode (LVDS_A3_POWER_UP)
		 * appropriately here, but we need to look more
		 * thoroughly पूर्णांकo how panels behave in the two modes.
		 */

		REG_WRITE(LVDS, lvds);
		REG_READ(LVDS);
	पूर्ण

	REG_WRITE(map->fp0, fp);
	REG_WRITE(map->dpll, dpll);
	REG_READ(map->dpll);
	/* Wait क्रम the घड़ीs to stabilize. */
	udelay(150);

	/* ग_लिखो it again -- the BIOS करोes, after all */
	REG_WRITE(map->dpll, dpll);

	REG_READ(map->dpll);
	/* Wait क्रम the घड़ीs to stabilize. */
	udelay(150);

	REG_WRITE(map->htotal, (adjusted_mode->crtc_hdisplay - 1) |
		  ((adjusted_mode->crtc_htotal - 1) << 16));
	REG_WRITE(map->hblank, (adjusted_mode->crtc_hblank_start - 1) |
		  ((adjusted_mode->crtc_hblank_end - 1) << 16));
	REG_WRITE(map->hsync, (adjusted_mode->crtc_hsync_start - 1) |
		  ((adjusted_mode->crtc_hsync_end - 1) << 16));
	REG_WRITE(map->vtotal, (adjusted_mode->crtc_vdisplay - 1) |
		  ((adjusted_mode->crtc_vtotal - 1) << 16));
	REG_WRITE(map->vblank, (adjusted_mode->crtc_vblank_start - 1) |
		  ((adjusted_mode->crtc_vblank_end - 1) << 16));
	REG_WRITE(map->vsync, (adjusted_mode->crtc_vsync_start - 1) |
		  ((adjusted_mode->crtc_vsync_end - 1) << 16));
	/* pipesrc and dspsize control the size that is scaled from,
	 * which should always be the user's requested size.
	 */
	REG_WRITE(map->size,
		  ((mode->vdisplay - 1) << 16) | (mode->hdisplay - 1));
	REG_WRITE(map->pos, 0);
	REG_WRITE(map->src,
		  ((mode->hdisplay - 1) << 16) | (mode->vdisplay - 1));
	REG_WRITE(map->conf, pipeconf);
	REG_READ(map->conf);

	gma_रुको_क्रम_vblank(dev);

	REG_WRITE(map->cntr, dspcntr);

	/* Flush the plane changes */
	crtc_funcs->mode_set_base(crtc, x, y, old_fb);

	gma_रुको_क्रम_vblank(dev);

	वापस 0;
पूर्ण

/* Returns the घड़ी of the currently programmed mode of the given pipe. */
अटल पूर्णांक psb_पूर्णांकel_crtc_घड़ी_get(काष्ठा drm_device *dev,
				काष्ठा drm_crtc *crtc)
अणु
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	पूर्णांक pipe = gma_crtc->pipe;
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];
	u32 dpll;
	u32 fp;
	काष्ठा gma_घड़ी_प्रकार घड़ी;
	bool is_lvds;
	काष्ठा psb_pipe *p = &dev_priv->regs.pipe[pipe];

	अगर (gma_घातer_begin(dev, false)) अणु
		dpll = REG_READ(map->dpll);
		अगर ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
			fp = REG_READ(map->fp0);
		अन्यथा
			fp = REG_READ(map->fp1);
		is_lvds = (pipe == 1) && (REG_READ(LVDS) & LVDS_PORT_EN);
		gma_घातer_end(dev);
	पूर्ण अन्यथा अणु
		dpll = p->dpll;

		अगर ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
			fp = p->fp0;
		अन्यथा
		        fp = p->fp1;

		is_lvds = (pipe == 1) && (dev_priv->regs.psb.saveLVDS &
								LVDS_PORT_EN);
	पूर्ण

	घड़ी.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	घड़ी.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	घड़ी.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;

	अगर (is_lvds) अणु
		घड़ी.p1 =
		    ffs((dpll &
			 DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS) >>
			DPLL_FPA01_P1_POST_DIV_SHIFT);
		घड़ी.p2 = 14;

		अगर ((dpll & PLL_REF_INPUT_MASK) ==
		    PLLB_REF_INPUT_SPREADSPECTRUMIN) अणु
			/* XXX: might not be 66MHz */
			psb_पूर्णांकel_घड़ी(66000, &घड़ी);
		पूर्ण अन्यथा
			psb_पूर्णांकel_घड़ी(48000, &घड़ी);
	पूर्ण अन्यथा अणु
		अगर (dpll & PLL_P1_DIVIDE_BY_TWO)
			घड़ी.p1 = 2;
		अन्यथा अणु
			घड़ी.p1 =
			    ((dpll &
			      DPLL_FPA01_P1_POST_DIV_MASK_I830) >>
			     DPLL_FPA01_P1_POST_DIV_SHIFT) + 2;
		पूर्ण
		अगर (dpll & PLL_P2_DIVIDE_BY_4)
			घड़ी.p2 = 4;
		अन्यथा
			घड़ी.p2 = 2;

		psb_पूर्णांकel_घड़ी(48000, &घड़ी);
	पूर्ण

	/* XXX: It would be nice to validate the घड़ीs, but we can't reuse
	 * i830PllIsValid() because it relies on the xf86_config connector
	 * configuration being accurate, which it isn't necessarily.
	 */

	वापस घड़ी.करोt;
पूर्ण

/** Returns the currently programmed mode of the given pipe. */
काष्ठा drm_display_mode *psb_पूर्णांकel_crtc_mode_get(काष्ठा drm_device *dev,
					     काष्ठा drm_crtc *crtc)
अणु
	काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
	पूर्णांक pipe = gma_crtc->pipe;
	काष्ठा drm_display_mode *mode;
	पूर्णांक htot;
	पूर्णांक hsync;
	पूर्णांक vtot;
	पूर्णांक vsync;
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा psb_pipe *p = &dev_priv->regs.pipe[pipe];
	स्थिर काष्ठा psb_offset *map = &dev_priv->regmap[pipe];

	अगर (gma_घातer_begin(dev, false)) अणु
		htot = REG_READ(map->htotal);
		hsync = REG_READ(map->hsync);
		vtot = REG_READ(map->vtotal);
		vsync = REG_READ(map->vsync);
		gma_घातer_end(dev);
	पूर्ण अन्यथा अणु
		htot = p->htotal;
		hsync = p->hsync;
		vtot = p->vtotal;
		vsync = p->vsync;
	पूर्ण

	mode = kzalloc(माप(*mode), GFP_KERNEL);
	अगर (!mode)
		वापस शून्य;

	mode->घड़ी = psb_पूर्णांकel_crtc_घड़ी_get(dev, crtc);
	mode->hdisplay = (htot & 0xffff) + 1;
	mode->htotal = ((htot & 0xffff0000) >> 16) + 1;
	mode->hsync_start = (hsync & 0xffff) + 1;
	mode->hsync_end = ((hsync & 0xffff0000) >> 16) + 1;
	mode->vdisplay = (vtot & 0xffff) + 1;
	mode->vtotal = ((vtot & 0xffff0000) >> 16) + 1;
	mode->vsync_start = (vsync & 0xffff) + 1;
	mode->vsync_end = ((vsync & 0xffff0000) >> 16) + 1;

	drm_mode_set_name(mode);
	drm_mode_set_crtcinfo(mode, 0);

	वापस mode;
पूर्ण

स्थिर काष्ठा drm_crtc_helper_funcs psb_पूर्णांकel_helper_funcs = अणु
	.dpms = gma_crtc_dpms,
	.mode_set = psb_पूर्णांकel_crtc_mode_set,
	.mode_set_base = gma_pipe_set_base,
	.prepare = gma_crtc_prepare,
	.commit = gma_crtc_commit,
	.disable = gma_crtc_disable,
पूर्ण;

स्थिर काष्ठा drm_crtc_funcs gma_पूर्णांकel_crtc_funcs = अणु
	.cursor_set = gma_crtc_cursor_set,
	.cursor_move = gma_crtc_cursor_move,
	.gamma_set = gma_crtc_gamma_set,
	.set_config = gma_crtc_set_config,
	.destroy = gma_crtc_destroy,
	.page_flip = gma_crtc_page_flip,
	.enable_vblank = psb_enable_vblank,
	.disable_vblank = psb_disable_vblank,
	.get_vblank_counter = psb_get_vblank_counter,
पूर्ण;

स्थिर काष्ठा gma_घड़ी_funcs psb_घड़ी_funcs = अणु
	.घड़ी = psb_पूर्णांकel_घड़ी,
	.limit = psb_पूर्णांकel_limit,
	.pll_is_valid = gma_pll_is_valid,
पूर्ण;

/*
 * Set the शेष value of cursor control and base रेजिस्टर
 * to zero. This is a workaround क्रम h/w defect on Oaktrail
 */
अटल व्योम psb_पूर्णांकel_cursor_init(काष्ठा drm_device *dev,
				  काष्ठा gma_crtc *gma_crtc)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	u32 control[3] = अणु CURACNTR, CURBCNTR, CURCCNTR पूर्ण;
	u32 base[3] = अणु CURABASE, CURBBASE, CURCBASE पूर्ण;
	काष्ठा gtt_range *cursor_gt;

	अगर (dev_priv->ops->cursor_needs_phys) अणु
		/* Allocate 4 pages of stolen mem क्रम a hardware cursor. That
		 * is enough क्रम the 64 x 64 ARGB cursors we support.
		 */
		cursor_gt = psb_gtt_alloc_range(dev, 4 * PAGE_SIZE, "cursor", 1,
						PAGE_SIZE);
		अगर (!cursor_gt) अणु
			gma_crtc->cursor_gt = शून्य;
			जाओ out;
		पूर्ण
		gma_crtc->cursor_gt = cursor_gt;
		gma_crtc->cursor_addr = dev_priv->stolen_base +
							cursor_gt->offset;
	पूर्ण अन्यथा अणु
		gma_crtc->cursor_gt = शून्य;
	पूर्ण

out:
	REG_WRITE(control[gma_crtc->pipe], 0);
	REG_WRITE(base[gma_crtc->pipe], 0);
पूर्ण

व्योम psb_पूर्णांकel_crtc_init(काष्ठा drm_device *dev, पूर्णांक pipe,
		     काष्ठा psb_पूर्णांकel_mode_device *mode_dev)
अणु
	काष्ठा drm_psb_निजी *dev_priv = dev->dev_निजी;
	काष्ठा gma_crtc *gma_crtc;
	पूर्णांक i;

	/* We allocate a extra array of drm_connector poपूर्णांकers
	 * क्रम fbdev after the crtc */
	gma_crtc = kzalloc(माप(काष्ठा gma_crtc) +
			(INTELFB_CONN_LIMIT * माप(काष्ठा drm_connector *)),
			GFP_KERNEL);
	अगर (gma_crtc == शून्य)
		वापस;

	gma_crtc->crtc_state =
		kzalloc(माप(काष्ठा psb_पूर्णांकel_crtc_state), GFP_KERNEL);
	अगर (!gma_crtc->crtc_state) अणु
		dev_err(dev->dev, "Crtc state error: No memory\n");
		kमुक्त(gma_crtc);
		वापस;
	पूर्ण

	/* Set the CRTC operations from the chip specअगरic data */
	drm_crtc_init(dev, &gma_crtc->base, dev_priv->ops->crtc_funcs);

	/* Set the CRTC घड़ी functions from chip specअगरic data */
	gma_crtc->घड़ी_funcs = dev_priv->ops->घड़ी_funcs;

	drm_mode_crtc_set_gamma_size(&gma_crtc->base, 256);
	gma_crtc->pipe = pipe;
	gma_crtc->plane = pipe;

	क्रम (i = 0; i < 256; i++)
		gma_crtc->lut_adj[i] = 0;

	gma_crtc->mode_dev = mode_dev;
	gma_crtc->cursor_addr = 0;

	drm_crtc_helper_add(&gma_crtc->base,
						dev_priv->ops->crtc_helper);

	/* Setup the array of drm_connector poपूर्णांकer array */
	gma_crtc->mode_set.crtc = &gma_crtc->base;
	BUG_ON(pipe >= ARRAY_SIZE(dev_priv->plane_to_crtc_mapping) ||
	       dev_priv->plane_to_crtc_mapping[gma_crtc->plane] != शून्य);
	dev_priv->plane_to_crtc_mapping[gma_crtc->plane] = &gma_crtc->base;
	dev_priv->pipe_to_crtc_mapping[gma_crtc->pipe] = &gma_crtc->base;
	gma_crtc->mode_set.connectors = (काष्ठा drm_connector **)(gma_crtc + 1);
	gma_crtc->mode_set.num_connectors = 0;
	psb_पूर्णांकel_cursor_init(dev, gma_crtc);

	/* Set to true so that the pipe is क्रमced off on initial config. */
	gma_crtc->active = true;
पूर्ण

काष्ठा drm_crtc *psb_पूर्णांकel_get_crtc_from_pipe(काष्ठा drm_device *dev, पूर्णांक pipe)
अणु
	काष्ठा drm_crtc *crtc = शून्य;

	list_क्रम_each_entry(crtc, &dev->mode_config.crtc_list, head) अणु
		काष्ठा gma_crtc *gma_crtc = to_gma_crtc(crtc);
		अगर (gma_crtc->pipe == pipe)
			अवरोध;
	पूर्ण
	वापस crtc;
पूर्ण

पूर्णांक gma_connector_clones(काष्ठा drm_device *dev, पूर्णांक type_mask)
अणु
	पूर्णांक index_mask = 0;
	काष्ठा drm_connector *connector;
	पूर्णांक entry = 0;

	list_क्रम_each_entry(connector, &dev->mode_config.connector_list,
			    head) अणु
		काष्ठा gma_encoder *gma_encoder = gma_attached_encoder(connector);
		अगर (type_mask & (1 << gma_encoder->type))
			index_mask |= (1 << entry);
		entry++;
	पूर्ण
	वापस index_mask;
पूर्ण
