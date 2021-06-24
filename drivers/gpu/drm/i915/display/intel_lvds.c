<शैली गुरु>
/*
 * Copyright तऊ 2006-2007 Intel Corporation
 * Copyright (c) 2006 Dave Airlie <airlied@linux.ie>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *	Eric Anholt <eric@anholt.net>
 *      Dave Airlie <airlied@linux.ie>
 *      Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 */

#समावेश <acpi/button.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/vga_चयनeroo.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>

#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_gmbus.h"
#समावेश "intel_lvds.h"
#समावेश "intel_panel.h"

/* Private काष्ठाure क्रम the पूर्णांकegrated LVDS support */
काष्ठा पूर्णांकel_lvds_pps अणु
	/* 100us units */
	पूर्णांक t1_t2;
	पूर्णांक t3;
	पूर्णांक t4;
	पूर्णांक t5;
	पूर्णांक tx;

	पूर्णांक भागider;

	पूर्णांक port;
	bool घातerकरोwn_on_reset;
पूर्ण;

काष्ठा पूर्णांकel_lvds_encoder अणु
	काष्ठा पूर्णांकel_encoder base;

	bool is_dual_link;
	i915_reg_t reg;
	u32 a3_घातer;

	काष्ठा पूर्णांकel_lvds_pps init_pps;
	u32 init_lvds_val;

	काष्ठा पूर्णांकel_connector *attached_connector;
पूर्ण;

अटल काष्ठा पूर्णांकel_lvds_encoder *to_lvds_encoder(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा पूर्णांकel_lvds_encoder, base.base);
पूर्ण

bool पूर्णांकel_lvds_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			     i915_reg_t lvds_reg, क्रमागत pipe *pipe)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, lvds_reg);

	/* निश्चितs want to know the pipe even अगर the port is disabled */
	अगर (HAS_PCH_CPT(dev_priv))
		*pipe = (val & LVDS_PIPE_SEL_MASK_CPT) >> LVDS_PIPE_SEL_SHIFT_CPT;
	अन्यथा
		*pipe = (val & LVDS_PIPE_SEL_MASK) >> LVDS_PIPE_SEL_SHIFT;

	वापस val & LVDS_PORT_EN;
पूर्ण

अटल bool पूर्णांकel_lvds_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				    क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = पूर्णांकel_lvds_port_enabled(dev_priv, lvds_encoder->reg, pipe);

	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_lvds_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	u32 पंचांगp, flags = 0;

	pipe_config->output_types |= BIT(INTEL_OUTPUT_LVDS);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, lvds_encoder->reg);
	अगर (पंचांगp & LVDS_HSYNC_POLARITY)
		flags |= DRM_MODE_FLAG_NHSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_PHSYNC;
	अगर (पंचांगp & LVDS_VSYNC_POLARITY)
		flags |= DRM_MODE_FLAG_NVSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_PVSYNC;

	pipe_config->hw.adjusted_mode.flags |= flags;

	अगर (DISPLAY_VER(dev_priv) < 5)
		pipe_config->gmch_pfit.lvds_border_bits =
			पंचांगp & LVDS_BORDER_ENABLE;

	/* gen2/3 store dither state in pfit control, needs to match */
	अगर (DISPLAY_VER(dev_priv) < 4) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PFIT_CONTROL);

		pipe_config->gmch_pfit.control |= पंचांगp & PANEL_8TO6_DITHER_ENABLE;
	पूर्ण

	pipe_config->hw.adjusted_mode.crtc_घड़ी = pipe_config->port_घड़ी;
पूर्ण

अटल व्योम पूर्णांकel_lvds_pps_get_hw_state(काष्ठा drm_i915_निजी *dev_priv,
					काष्ठा पूर्णांकel_lvds_pps *pps)
अणु
	u32 val;

	pps->घातerकरोwn_on_reset = पूर्णांकel_de_पढ़ो(dev_priv, PP_CONTROL(0)) & PANEL_POWER_RESET;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PP_ON_DELAYS(0));
	pps->port = REG_FIELD_GET(PANEL_PORT_SELECT_MASK, val);
	pps->t1_t2 = REG_FIELD_GET(PANEL_POWER_UP_DELAY_MASK, val);
	pps->t5 = REG_FIELD_GET(PANEL_LIGHT_ON_DELAY_MASK, val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, PP_OFF_DELAYS(0));
	pps->t3 = REG_FIELD_GET(PANEL_POWER_DOWN_DELAY_MASK, val);
	pps->tx = REG_FIELD_GET(PANEL_LIGHT_OFF_DELAY_MASK, val);

	val = पूर्णांकel_de_पढ़ो(dev_priv, PP_DIVISOR(0));
	pps->भागider = REG_FIELD_GET(PP_REFERENCE_DIVIDER_MASK, val);
	val = REG_FIELD_GET(PANEL_POWER_CYCLE_DELAY_MASK, val);
	/*
	 * Remove the BSpec specअगरied +1 (100ms) offset that accounts क्रम a
	 * too लघु घातer-cycle delay due to the asynchronous programming of
	 * the रेजिस्टर.
	 */
	अगर (val)
		val--;
	/* Convert from 100ms to 100us units */
	pps->t4 = val * 1000;

	अगर (DISPLAY_VER(dev_priv) <= 4 &&
	    pps->t1_t2 == 0 && pps->t5 == 0 && pps->t3 == 0 && pps->tx == 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Panel power timings uninitialized, "
			    "setting defaults\n");
		/* Set T2 to 40ms and T5 to 200ms in 100 usec units */
		pps->t1_t2 = 40 * 10;
		pps->t5 = 200 * 10;
		/* Set T3 to 35ms and Tx to 200ms in 100 usec units */
		pps->t3 = 35 * 10;
		pps->tx = 200 * 10;
	पूर्ण

	drm_dbg(&dev_priv->drm, "LVDS PPS:t1+t2 %d t3 %d t4 %d t5 %d tx %d "
		"divider %d port %d powerdown_on_reset %d\n",
		pps->t1_t2, pps->t3, pps->t4, pps->t5, pps->tx,
		pps->भागider, pps->port, pps->घातerकरोwn_on_reset);
पूर्ण

अटल व्योम पूर्णांकel_lvds_pps_init_hw(काष्ठा drm_i915_निजी *dev_priv,
				   काष्ठा पूर्णांकel_lvds_pps *pps)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PP_CONTROL(0));
	drm_WARN_ON(&dev_priv->drm,
		    (val & PANEL_UNLOCK_MASK) != PANEL_UNLOCK_REGS);
	अगर (pps->घातerकरोwn_on_reset)
		val |= PANEL_POWER_RESET;
	पूर्णांकel_de_ग_लिखो(dev_priv, PP_CONTROL(0), val);

	पूर्णांकel_de_ग_लिखो(dev_priv, PP_ON_DELAYS(0),
		       REG_FIELD_PREP(PANEL_PORT_SELECT_MASK, pps->port) | REG_FIELD_PREP(PANEL_POWER_UP_DELAY_MASK, pps->t1_t2) | REG_FIELD_PREP(PANEL_LIGHT_ON_DELAY_MASK, pps->t5));

	पूर्णांकel_de_ग_लिखो(dev_priv, PP_OFF_DELAYS(0),
		       REG_FIELD_PREP(PANEL_POWER_DOWN_DELAY_MASK, pps->t3) | REG_FIELD_PREP(PANEL_LIGHT_OFF_DELAY_MASK, pps->tx));

	पूर्णांकel_de_ग_लिखो(dev_priv, PP_DIVISOR(0),
		       REG_FIELD_PREP(PP_REFERENCE_DIVIDER_MASK, pps->भागider) | REG_FIELD_PREP(PANEL_POWER_CYCLE_DELAY_MASK, DIV_ROUND_UP(pps->t4, 1000) + 1));
पूर्ण

अटल व्योम पूर्णांकel_pre_enable_lvds(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	क्रमागत pipe pipe = crtc->pipe;
	u32 temp;

	अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		निश्चित_fdi_rx_pll_disabled(dev_priv, pipe);
		निश्चित_shared_dpll_disabled(dev_priv,
					    pipe_config->shared_dpll);
	पूर्ण अन्यथा अणु
		निश्चित_pll_disabled(dev_priv, pipe);
	पूर्ण

	पूर्णांकel_lvds_pps_init_hw(dev_priv, &lvds_encoder->init_pps);

	temp = lvds_encoder->init_lvds_val;
	temp |= LVDS_PORT_EN | LVDS_A0A2_CLKA_POWER_UP;

	अगर (HAS_PCH_CPT(dev_priv)) अणु
		temp &= ~LVDS_PIPE_SEL_MASK_CPT;
		temp |= LVDS_PIPE_SEL_CPT(pipe);
	पूर्ण अन्यथा अणु
		temp &= ~LVDS_PIPE_SEL_MASK;
		temp |= LVDS_PIPE_SEL(pipe);
	पूर्ण

	/* set the corresponsding LVDS_BORDER bit */
	temp &= ~LVDS_BORDER_ENABLE;
	temp |= pipe_config->gmch_pfit.lvds_border_bits;

	/*
	 * Set the B0-B3 data pairs corresponding to whether we're going to
	 * set the DPLLs क्रम dual-channel mode or not.
	 */
	अगर (lvds_encoder->is_dual_link)
		temp |= LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP;
	अन्यथा
		temp &= ~(LVDS_B0B3_POWER_UP | LVDS_CLKB_POWER_UP);

	/*
	 * It would be nice to set 24 vs 18-bit mode (LVDS_A3_POWER_UP)
	 * appropriately here, but we need to look more thoroughly पूर्णांकo how
	 * panels behave in the two modes. For now, let's just मुख्यtain the
	 * value we got from the BIOS.
	 */
	temp &= ~LVDS_A3_POWER_MASK;
	temp |= lvds_encoder->a3_घातer;

	/*
	 * Set the dithering flag on LVDS as needed, note that there is no
	 * special lvds dither control bit on pch-split platक्रमms, dithering is
	 * only controlled through the PIPECONF reg.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 4)) अणु
		/*
		 * Bspec wording suggests that LVDS port dithering only exists
		 * क्रम 18bpp panels.
		 */
		अगर (pipe_config->dither && pipe_config->pipe_bpp == 18)
			temp |= LVDS_ENABLE_DITHER;
		अन्यथा
			temp &= ~LVDS_ENABLE_DITHER;
	पूर्ण
	temp &= ~(LVDS_HSYNC_POLARITY | LVDS_VSYNC_POLARITY);
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_NHSYNC)
		temp |= LVDS_HSYNC_POLARITY;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_NVSYNC)
		temp |= LVDS_VSYNC_POLARITY;

	पूर्णांकel_de_ग_लिखो(dev_priv, lvds_encoder->reg, temp);
पूर्ण

/*
 * Sets the घातer state क्रम the panel.
 */
अटल व्योम पूर्णांकel_enable_lvds(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			      स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	पूर्णांकel_de_ग_लिखो(dev_priv, lvds_encoder->reg,
		       पूर्णांकel_de_पढ़ो(dev_priv, lvds_encoder->reg) | LVDS_PORT_EN);

	पूर्णांकel_de_ग_लिखो(dev_priv, PP_CONTROL(0),
		       पूर्णांकel_de_पढ़ो(dev_priv, PP_CONTROL(0)) | PANEL_POWER_ON);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, lvds_encoder->reg);

	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, PP_STATUS(0), PP_ON, 5000))
		drm_err(&dev_priv->drm,
			"timed out waiting for panel to power on\n");

	पूर्णांकel_panel_enable_backlight(pipe_config, conn_state);
पूर्ण

अटल व्योम पूर्णांकel_disable_lvds(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			       स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	पूर्णांकel_de_ग_लिखो(dev_priv, PP_CONTROL(0),
		       पूर्णांकel_de_पढ़ो(dev_priv, PP_CONTROL(0)) & ~PANEL_POWER_ON);
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, PP_STATUS(0), PP_ON, 1000))
		drm_err(&dev_priv->drm,
			"timed out waiting for panel to power off\n");

	पूर्णांकel_de_ग_लिखो(dev_priv, lvds_encoder->reg,
		       पूर्णांकel_de_पढ़ो(dev_priv, lvds_encoder->reg) & ~LVDS_PORT_EN);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, lvds_encoder->reg);
पूर्ण

अटल व्योम gmch_disable_lvds(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			      स्थिर काष्ठा drm_connector_state *old_conn_state)

अणु
	पूर्णांकel_panel_disable_backlight(old_conn_state);

	पूर्णांकel_disable_lvds(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम pch_disable_lvds(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			     स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_panel_disable_backlight(old_conn_state);
पूर्ण

अटल व्योम pch_post_disable_lvds(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				  स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_disable_lvds(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम पूर्णांकel_lvds_shutकरोwn(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, PP_STATUS(0), PP_CYCLE_DELAY_ACTIVE, 5000))
		drm_err(&dev_priv->drm,
			"timed out waiting for panel power cycle delay\n");
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_lvds_mode_valid(काष्ठा drm_connector *connector,
		      काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा drm_display_mode *fixed_mode = पूर्णांकel_connector->panel.fixed_mode;
	पूर्णांक max_pixclk = to_i915(connector->dev)->max_करोtclk_freq;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;
	अगर (mode->hdisplay > fixed_mode->hdisplay)
		वापस MODE_PANEL;
	अगर (mode->vdisplay > fixed_mode->vdisplay)
		वापस MODE_PANEL;
	अगर (fixed_mode->घड़ी > max_pixclk)
		वापस MODE_CLOCK_HIGH;

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक पूर्णांकel_lvds_compute_config(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
				     काष्ठा पूर्णांकel_crtc_state *pipe_config,
				     काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_encoder->base.dev);
	काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder =
		to_lvds_encoder(&पूर्णांकel_encoder->base);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector =
		lvds_encoder->attached_connector;
	काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	अचिन्हित पूर्णांक lvds_bpp;
	पूर्णांक ret;

	/* Should never happen!! */
	अगर (DISPLAY_VER(dev_priv) < 4 && पूर्णांकel_crtc->pipe == 0) अणु
		drm_err(&dev_priv->drm, "Can't support LVDS on pipe A\n");
		वापस -EINVAL;
	पूर्ण

	अगर (lvds_encoder->a3_घातer == LVDS_A3_POWER_UP)
		lvds_bpp = 8*3;
	अन्यथा
		lvds_bpp = 6*3;

	अगर (lvds_bpp != pipe_config->pipe_bpp && !pipe_config->bw_स्थिरrained) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "forcing display bpp (was %d) to LVDS (%d)\n",
			    pipe_config->pipe_bpp, lvds_bpp);
		pipe_config->pipe_bpp = lvds_bpp;
	पूर्ण

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	/*
	 * We have timings from the BIOS क्रम the panel, put them in
	 * to the adjusted mode.  The CRTC will be set up क्रम this mode,
	 * with the panel scaling set up to source from the H/VDisplay
	 * of the original mode.
	 */
	पूर्णांकel_fixed_panel_mode(पूर्णांकel_connector->panel.fixed_mode,
			       adjusted_mode);

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	अगर (HAS_PCH_SPLIT(dev_priv))
		pipe_config->has_pch_encoder = true;

	अगर (HAS_GMCH(dev_priv))
		ret = पूर्णांकel_gmch_panel_fitting(pipe_config, conn_state);
	अन्यथा
		ret = पूर्णांकel_pch_panel_fitting(pipe_config, conn_state);
	अगर (ret)
		वापस ret;

	/*
	 * XXX: It would be nice to support lower refresh rates on the
	 * panels to reduce घातer consumption, and perhaps match the
	 * user's requested refresh rate.
	 */

	वापस 0;
पूर्ण

/*
 * Return the list of DDC modes अगर available, or the BIOS fixed mode otherwise.
 */
अटल पूर्णांक पूर्णांकel_lvds_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_display_mode *mode;

	/* use cached edid अगर we have one */
	अगर (!IS_ERR_OR_शून्य(पूर्णांकel_connector->edid))
		वापस drm_add_edid_modes(connector, पूर्णांकel_connector->edid);

	mode = drm_mode_duplicate(dev, पूर्णांकel_connector->panel.fixed_mode);
	अगर (mode == शून्य)
		वापस 0;

	drm_mode_probed_add(connector, mode);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_lvds_connector_helper_funcs = अणु
	.get_modes = पूर्णांकel_lvds_get_modes,
	.mode_valid = पूर्णांकel_lvds_mode_valid,
	.atomic_check = पूर्णांकel_digital_connector_atomic_check,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_lvds_connector_funcs = अणु
	.detect = पूर्णांकel_panel_detect,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_get_property = पूर्णांकel_digital_connector_atomic_get_property,
	.atomic_set_property = पूर्णांकel_digital_connector_atomic_set_property,
	.late_रेजिस्टर = पूर्णांकel_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = पूर्णांकel_digital_connector_duplicate_state,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_lvds_enc_funcs = अणु
	.destroy = पूर्णांकel_encoder_destroy,
पूर्ण;

अटल पूर्णांक पूर्णांकel_no_lvds_dmi_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	DRM_INFO("Skipping LVDS initialization for %s\n", id->ident);
	वापस 1;
पूर्ण

/* These प्रणालीs claim to have LVDS, but really करोn't */
अटल स्थिर काष्ठा dmi_प्रणाली_id पूर्णांकel_no_lvds[] = अणु
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Apple Mac Mini (Core series)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Macmini1,1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Apple Mac Mini (Core 2 series)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Macmini2,1"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "MSI IM-945GSE-A",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "MSI"),
			DMI_MATCH(DMI_PRODUCT_NAME, "A9830IMS"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Dell Studio Hybrid",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Studio Hybrid 140g"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Dell OptiPlex FX170",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "OptiPlex FX170"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "AOpen Mini PC",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "AOpen"),
			DMI_MATCH(DMI_PRODUCT_NAME, "i965GMx-IF"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "AOpen Mini PC MP915",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AOpen"),
			DMI_MATCH(DMI_BOARD_NAME, "i915GMx-F"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "AOpen i915GMm-HFS",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "AOpen"),
			DMI_MATCH(DMI_BOARD_NAME, "i915GMm-HFS"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
                .ident = "AOpen i45GMx-I",
                .matches = अणु
                        DMI_MATCH(DMI_BOARD_VENDOR, "AOpen"),
                        DMI_MATCH(DMI_BOARD_NAME, "i45GMx-I"),
                पूर्ण,
        पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Aopen i945GTt-VFA",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_VERSION, "AO00001JW"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Clientron U800",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Clientron"),
			DMI_MATCH(DMI_PRODUCT_NAME, "U800"),
		पूर्ण,
	पूर्ण,
	अणु
                .callback = पूर्णांकel_no_lvds_dmi_callback,
                .ident = "Clientron E830",
                .matches = अणु
                        DMI_MATCH(DMI_SYS_VENDOR, "Clientron"),
                        DMI_MATCH(DMI_PRODUCT_NAME, "E830"),
                पूर्ण,
        पूर्ण,
        अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Asus EeeBox PC EB1007",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_PRODUCT_NAME, "EB1007"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Asus AT5NM10T-I",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "AT5NM10T-I"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Hewlett-Packard HP t5740",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, " t5740"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Hewlett-Packard t5745",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "hp t5745"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Hewlett-Packard st5747",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Hewlett-Packard"),
			DMI_MATCH(DMI_PRODUCT_NAME, "hp st5747"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "MSI Wind Box DC500",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "MICRO-STAR INTERNATIONAL CO., LTD"),
			DMI_MATCH(DMI_BOARD_NAME, "MS-7469"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Gigabyte GA-D525TUD",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co., Ltd."),
			DMI_MATCH(DMI_BOARD_NAME, "D525TUD"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Supermicro X7SPA-H",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Supermicro"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X7SPA-H"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Fujitsu Esprimo Q900",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "FUJITSU"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ESPRIMO Q900"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Intel D410PT",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Intel"),
			DMI_MATCH(DMI_BOARD_NAME, "D410PT"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Intel D425KT",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Intel"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "D425KT"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Intel D510MO",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Intel"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "D510MO"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Intel D525MW",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Intel"),
			DMI_EXACT_MATCH(DMI_BOARD_NAME, "D525MW"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_no_lvds_dmi_callback,
		.ident = "Radiant P845",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Radiant Systems Inc"),
			DMI_MATCH(DMI_PRODUCT_NAME, "P845"),
		पूर्ण,
	पूर्ण,

	अणु पूर्ण	/* terminating entry */
पूर्ण;

अटल पूर्णांक पूर्णांकel_dual_link_lvds_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	DRM_INFO("Forcing lvds to dual link mode on %s\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id पूर्णांकel_dual_link_lvds[] = अणु
	अणु
		.callback = पूर्णांकel_dual_link_lvds_callback,
		.ident = "Apple MacBook Pro 15\" (2010)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MacBookPro6,2"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_dual_link_lvds_callback,
		.ident = "Apple MacBook Pro 15\" (2011)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MacBookPro8,2"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_dual_link_lvds_callback,
		.ident = "Apple MacBook Pro 15\" (2012)",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Apple Inc."),
			DMI_MATCH(DMI_PRODUCT_NAME, "MacBookPro9,1"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण	/* terminating entry */
पूर्ण;

काष्ठा पूर्णांकel_encoder *पूर्णांकel_get_lvds_encoder(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		अगर (encoder->type == INTEL_OUTPUT_LVDS)
			वापस encoder;
	पूर्ण

	वापस शून्य;
पूर्ण

bool पूर्णांकel_is_dual_link_lvds(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_get_lvds_encoder(dev_priv);

	वापस encoder && to_lvds_encoder(&encoder->base)->is_dual_link;
पूर्ण

अटल bool compute_is_dual_link_lvds(काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder)
अणु
	काष्ठा drm_device *dev = lvds_encoder->base.base.dev;
	अचिन्हित पूर्णांक val;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	/* use the module option value अगर specअगरied */
	अगर (dev_priv->params.lvds_channel_mode > 0)
		वापस dev_priv->params.lvds_channel_mode == 2;

	/* single channel LVDS is limited to 112 MHz */
	अगर (lvds_encoder->attached_connector->panel.fixed_mode->घड़ी > 112999)
		वापस true;

	अगर (dmi_check_प्रणाली(पूर्णांकel_dual_link_lvds))
		वापस true;

	/*
	 * BIOS should set the proper LVDS रेजिस्टर value at boot, but
	 * in reality, it करोesn't set the value when the lid is बंदd;
	 * we need to check "the value to be set" in VBT when LVDS
	 * रेजिस्टर is uninitialized.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, lvds_encoder->reg);
	अगर (HAS_PCH_CPT(dev_priv))
		val &= ~(LVDS_DETECTED | LVDS_PIPE_SEL_MASK_CPT);
	अन्यथा
		val &= ~(LVDS_DETECTED | LVDS_PIPE_SEL_MASK);
	अगर (val == 0)
		val = dev_priv->vbt.bios_lvds_val;

	वापस (val & LVDS_CLKB_POWER_MASK) == LVDS_CLKB_POWER_UP;
पूर्ण

/**
 * पूर्णांकel_lvds_init - setup LVDS connectors on this device
 * @dev_priv: i915 device
 *
 * Create the connector, रेजिस्टर the LVDS DDC bus, and try to figure out what
 * modes we can display on the LVDS panel (अगर present).
 */
व्योम पूर्णांकel_lvds_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_lvds_encoder *lvds_encoder;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_display_mode *fixed_mode = शून्य;
	काष्ठा drm_display_mode *करोwnघड़ी_mode = शून्य;
	काष्ठा edid *edid;
	i915_reg_t lvds_reg;
	u32 lvds;
	u8 pin;
	u32 allowed_scalers;

	/* Skip init on machines we know falsely report LVDS */
	अगर (dmi_check_प्रणाली(पूर्णांकel_no_lvds)) अणु
		drm_WARN(dev, !dev_priv->vbt.पूर्णांक_lvds_support,
			 "Useless DMI match. Internal LVDS support disabled by VBT\n");
		वापस;
	पूर्ण

	अगर (!dev_priv->vbt.पूर्णांक_lvds_support) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Internal LVDS support disabled by VBT\n");
		वापस;
	पूर्ण

	अगर (HAS_PCH_SPLIT(dev_priv))
		lvds_reg = PCH_LVDS;
	अन्यथा
		lvds_reg = LVDS;

	lvds = पूर्णांकel_de_पढ़ो(dev_priv, lvds_reg);

	अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		अगर ((lvds & LVDS_DETECTED) == 0)
			वापस;
	पूर्ण

	pin = GMBUS_PIN_PANEL;
	अगर (!पूर्णांकel_bios_is_lvds_present(dev_priv, &pin)) अणु
		अगर ((lvds & LVDS_PORT_EN) == 0) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "LVDS is not present in VBT\n");
			वापस;
		पूर्ण
		drm_dbg_kms(&dev_priv->drm,
			    "LVDS is not present in VBT, but enabled anyway\n");
	पूर्ण

	lvds_encoder = kzalloc(माप(*lvds_encoder), GFP_KERNEL);
	अगर (!lvds_encoder)
		वापस;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector) अणु
		kमुक्त(lvds_encoder);
		वापस;
	पूर्ण

	lvds_encoder->attached_connector = पूर्णांकel_connector;

	पूर्णांकel_encoder = &lvds_encoder->base;
	encoder = &पूर्णांकel_encoder->base;
	connector = &पूर्णांकel_connector->base;
	drm_connector_init(dev, &पूर्णांकel_connector->base, &पूर्णांकel_lvds_connector_funcs,
			   DRM_MODE_CONNECTOR_LVDS);

	drm_encoder_init(dev, &पूर्णांकel_encoder->base, &पूर्णांकel_lvds_enc_funcs,
			 DRM_MODE_ENCODER_LVDS, "LVDS");

	पूर्णांकel_encoder->enable = पूर्णांकel_enable_lvds;
	पूर्णांकel_encoder->pre_enable = पूर्णांकel_pre_enable_lvds;
	पूर्णांकel_encoder->compute_config = पूर्णांकel_lvds_compute_config;
	अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		पूर्णांकel_encoder->disable = pch_disable_lvds;
		पूर्णांकel_encoder->post_disable = pch_post_disable_lvds;
	पूर्ण अन्यथा अणु
		पूर्णांकel_encoder->disable = gmch_disable_lvds;
	पूर्ण
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_lvds_get_hw_state;
	पूर्णांकel_encoder->get_config = पूर्णांकel_lvds_get_config;
	पूर्णांकel_encoder->update_pipe = पूर्णांकel_panel_update_backlight;
	पूर्णांकel_encoder->shutकरोwn = पूर्णांकel_lvds_shutकरोwn;
	पूर्णांकel_connector->get_hw_state = पूर्णांकel_connector_get_hw_state;

	पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, पूर्णांकel_encoder);

	पूर्णांकel_encoder->type = INTEL_OUTPUT_LVDS;
	पूर्णांकel_encoder->घातer_करोमुख्य = POWER_DOMAIN_PORT_OTHER;
	पूर्णांकel_encoder->port = PORT_NONE;
	पूर्णांकel_encoder->cloneable = 0;
	अगर (DISPLAY_VER(dev_priv) < 4)
		पूर्णांकel_encoder->pipe_mask = BIT(PIPE_B);
	अन्यथा
		पूर्णांकel_encoder->pipe_mask = ~0;

	drm_connector_helper_add(connector, &पूर्णांकel_lvds_connector_helper_funcs);
	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	lvds_encoder->reg = lvds_reg;

	/* create the scaling mode property */
	allowed_scalers = BIT(DRM_MODE_SCALE_ASPECT);
	allowed_scalers |= BIT(DRM_MODE_SCALE_FULLSCREEN);
	allowed_scalers |= BIT(DRM_MODE_SCALE_CENTER);
	drm_connector_attach_scaling_mode_property(connector, allowed_scalers);
	connector->state->scaling_mode = DRM_MODE_SCALE_ASPECT;

	पूर्णांकel_lvds_pps_get_hw_state(dev_priv, &lvds_encoder->init_pps);
	lvds_encoder->init_lvds_val = lvds;

	/*
	 * LVDS discovery:
	 * 1) check क्रम EDID on DDC
	 * 2) check क्रम VBT data
	 * 3) check to see अगर LVDS is alपढ़ोy on
	 *    अगर none of the above, no panel
	 */

	/*
	 * Attempt to get the fixed panel mode from DDC.  Assume that the
	 * preferred mode is the right one.
	 */
	mutex_lock(&dev->mode_config.mutex);
	अगर (vga_चयनeroo_handler_flags() & VGA_SWITCHEROO_CAN_SWITCH_DDC)
		edid = drm_get_edid_चयनeroo(connector,
				    पूर्णांकel_gmbus_get_adapter(dev_priv, pin));
	अन्यथा
		edid = drm_get_edid(connector,
				    पूर्णांकel_gmbus_get_adapter(dev_priv, pin));
	अगर (edid) अणु
		अगर (drm_add_edid_modes(connector, edid)) अणु
			drm_connector_update_edid_property(connector,
								edid);
		पूर्ण अन्यथा अणु
			kमुक्त(edid);
			edid = ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण अन्यथा अणु
		edid = ERR_PTR(-ENOENT);
	पूर्ण
	पूर्णांकel_connector->edid = edid;

	fixed_mode = पूर्णांकel_panel_edid_fixed_mode(पूर्णांकel_connector);
	अगर (fixed_mode)
		जाओ out;

	/* Failed to get EDID, what about VBT? */
	fixed_mode = पूर्णांकel_panel_vbt_fixed_mode(पूर्णांकel_connector);
	अगर (fixed_mode)
		जाओ out;

	/*
	 * If we didn't get EDID, try checking अगर the panel is alपढ़ोy turned
	 * on.  If so, assume that whatever is currently programmed is the
	 * correct mode.
	 */
	fixed_mode = पूर्णांकel_encoder_current_mode(पूर्णांकel_encoder);
	अगर (fixed_mode) अणु
		drm_dbg_kms(&dev_priv->drm, "using current (BIOS) mode: ");
		drm_mode_debug_prपूर्णांकmodeline(fixed_mode);
		fixed_mode->type |= DRM_MODE_TYPE_PREFERRED;
	पूर्ण

	/* If we still करोn't have a mode after all that, give up. */
	अगर (!fixed_mode)
		जाओ failed;

out:
	mutex_unlock(&dev->mode_config.mutex);

	पूर्णांकel_panel_init(&पूर्णांकel_connector->panel, fixed_mode, करोwnघड़ी_mode);
	पूर्णांकel_panel_setup_backlight(connector, INVALID_PIPE);

	lvds_encoder->is_dual_link = compute_is_dual_link_lvds(lvds_encoder);
	drm_dbg_kms(&dev_priv->drm, "detected %s-link lvds configuration\n",
		    lvds_encoder->is_dual_link ? "dual" : "single");

	lvds_encoder->a3_घातer = lvds & LVDS_A3_POWER_MASK;

	वापस;

failed:
	mutex_unlock(&dev->mode_config.mutex);

	drm_dbg_kms(&dev_priv->drm, "No LVDS modes found, disabling.\n");
	drm_connector_cleanup(connector);
	drm_encoder_cleanup(encoder);
	kमुक्त(lvds_encoder);
	पूर्णांकel_connector_मुक्त(पूर्णांकel_connector);
	वापस;
पूर्ण
