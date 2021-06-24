<शैली गुरु>
/*
 * Copyright तऊ 2006-2007 Intel Corporation
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
 */

#समावेश <acpi/video.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकel-iommu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-resv.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_atomic_uapi.h>
#समावेश <drm/drm_damage_helper.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_rect.h>

#समावेश "display/intel_audio.h"
#समावेश "display/intel_crt.h"
#समावेश "display/intel_ddi.h"
#समावेश "display/intel_display_debugfs.h"
#समावेश "display/intel_dp.h"
#समावेश "display/intel_dp_mst.h"
#समावेश "display/intel_dpll.h"
#समावेश "display/intel_dpll_mgr.h"
#समावेश "display/intel_dsi.h"
#समावेश "display/intel_dvo.h"
#समावेश "display/intel_fb.h"
#समावेश "display/intel_gmbus.h"
#समावेश "display/intel_hdmi.h"
#समावेश "display/intel_lvds.h"
#समावेश "display/intel_sdvo.h"
#समावेश "display/intel_tv.h"
#समावेश "display/intel_vdsc.h"
#समावेश "display/intel_vrr.h"

#समावेश "gem/i915_gem_object.h"

#समावेश "gt/intel_rps.h"

#समावेश "g4x_dp.h"
#समावेश "g4x_hdmi.h"
#समावेश "i915_drv.h"
#समावेश "intel_acpi.h"
#समावेश "intel_atomic.h"
#समावेश "intel_atomic_plane.h"
#समावेश "intel_bw.h"
#समावेश "intel_cdclk.h"
#समावेश "intel_color.h"
#समावेश "intel_crtc.h"
#समावेश "intel_csr.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dp_link_training.h"
#समावेश "intel_fbc.h"
#समावेश "intel_fdi.h"
#समावेश "intel_fbdev.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_frontbuffer.h"
#समावेश "intel_hdcp.h"
#समावेश "intel_hotplug.h"
#समावेश "intel_overlay.h"
#समावेश "intel_pipe_crc.h"
#समावेश "intel_pm.h"
#समावेश "intel_pps.h"
#समावेश "intel_psr.h"
#समावेश "intel_quirks.h"
#समावेश "intel_sideband.h"
#समावेश "intel_sprite.h"
#समावेश "intel_tc.h"
#समावेश "intel_vga.h"
#समावेश "i9xx_plane.h"
#समावेश "skl_scaler.h"
#समावेश "skl_universal_plane.h"

अटल व्योम i9xx_crtc_घड़ी_get(काष्ठा पूर्णांकel_crtc *crtc,
				काष्ठा पूर्णांकel_crtc_state *pipe_config);
अटल व्योम ilk_pch_घड़ी_get(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_crtc_state *pipe_config);

अटल पूर्णांक पूर्णांकel_framebuffer_init(काष्ठा पूर्णांकel_framebuffer *अगरb,
				  काष्ठा drm_i915_gem_object *obj,
				  काष्ठा drm_mode_fb_cmd2 *mode_cmd);
अटल व्योम पूर्णांकel_set_transcoder_timings(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
अटल व्योम पूर्णांकel_set_pipe_src_size(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
अटल व्योम पूर्णांकel_cpu_transcoder_set_m_n(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 स्थिर काष्ठा पूर्णांकel_link_m_n *m_n,
					 स्थिर काष्ठा पूर्णांकel_link_m_n *m2_n2);
अटल व्योम i9xx_set_pipeconf(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
अटल व्योम ilk_set_pipeconf(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
अटल व्योम hsw_set_pipeconf(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
अटल व्योम bdw_set_pipemisc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
अटल व्योम ilk_pfit_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state);
अटल व्योम पूर्णांकel_modeset_setup_hw_state(काष्ठा drm_device *dev,
					 काष्ठा drm_modeset_acquire_ctx *ctx);

/* वापसs HPLL frequency in kHz */
पूर्णांक vlv_get_hpll_vco(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक hpll_freq, vco_freq[] = अणु 800, 1600, 2000, 2400 पूर्ण;

	/* Obtain SKU inक्रमmation */
	hpll_freq = vlv_cck_पढ़ो(dev_priv, CCK_FUSE_REG) &
		CCK_FUSE_HPLL_FREQ_MASK;

	वापस vco_freq[hpll_freq] * 1000;
पूर्ण

पूर्णांक vlv_get_cck_घड़ी(काष्ठा drm_i915_निजी *dev_priv,
		      स्थिर अक्षर *name, u32 reg, पूर्णांक ref_freq)
अणु
	u32 val;
	पूर्णांक भागider;

	val = vlv_cck_पढ़ो(dev_priv, reg);
	भागider = val & CCK_FREQUENCY_VALUES;

	drm_WARN(&dev_priv->drm, (val & CCK_FREQUENCY_STATUS) !=
		 (भागider << CCK_FREQUENCY_STATUS_SHIFT),
		 "%s change in progress\n", name);

	वापस DIV_ROUND_CLOSEST(ref_freq << 1, भागider + 1);
पूर्ण

पूर्णांक vlv_get_cck_घड़ी_hpll(काष्ठा drm_i915_निजी *dev_priv,
			   स्थिर अक्षर *name, u32 reg)
अणु
	पूर्णांक hpll;

	vlv_cck_get(dev_priv);

	अगर (dev_priv->hpll_freq == 0)
		dev_priv->hpll_freq = vlv_get_hpll_vco(dev_priv);

	hpll = vlv_get_cck_घड़ी(dev_priv, name, reg, dev_priv->hpll_freq);

	vlv_cck_put(dev_priv);

	वापस hpll;
पूर्ण

अटल व्योम पूर्णांकel_update_czclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!(IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)))
		वापस;

	dev_priv->czclk_freq = vlv_get_cck_घड़ी_hpll(dev_priv, "czclk",
						      CCK_CZ_CLOCK_CONTROL);

	drm_dbg(&dev_priv->drm, "CZ clock rate: %d kHz\n",
		dev_priv->czclk_freq);
पूर्ण

/* WA Display #0827: Gen9:all */
अटल व्योम
skl_wa_827(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe, bool enable)
अणु
	अगर (enable)
		पूर्णांकel_de_ग_लिखो(dev_priv, CLKGATE_DIS_PSL(pipe),
		               पूर्णांकel_de_पढ़ो(dev_priv, CLKGATE_DIS_PSL(pipe)) | DUPS1_GATING_DIS | DUPS2_GATING_DIS);
	अन्यथा
		पूर्णांकel_de_ग_लिखो(dev_priv, CLKGATE_DIS_PSL(pipe),
		               पूर्णांकel_de_पढ़ो(dev_priv, CLKGATE_DIS_PSL(pipe)) & ~(DUPS1_GATING_DIS | DUPS2_GATING_DIS));
पूर्ण

/* Wa_2006604312:icl,ehl */
अटल व्योम
icl_wa_scalerclkgating(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe,
		       bool enable)
अणु
	अगर (enable)
		पूर्णांकel_de_ग_लिखो(dev_priv, CLKGATE_DIS_PSL(pipe),
		               पूर्णांकel_de_पढ़ो(dev_priv, CLKGATE_DIS_PSL(pipe)) | DPFR_GATING_DIS);
	अन्यथा
		पूर्णांकel_de_ग_लिखो(dev_priv, CLKGATE_DIS_PSL(pipe),
		               पूर्णांकel_de_पढ़ो(dev_priv, CLKGATE_DIS_PSL(pipe)) & ~DPFR_GATING_DIS);
पूर्ण

अटल bool
is_trans_port_sync_slave(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस crtc_state->master_transcoder != INVALID_TRANSCODER;
पूर्ण

अटल bool
is_trans_port_sync_master(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस crtc_state->sync_mode_slaves_mask != 0;
पूर्ण

bool
is_trans_port_sync_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस is_trans_port_sync_master(crtc_state) ||
		is_trans_port_sync_slave(crtc_state);
पूर्ण

अटल bool pipe_scanline_is_moving(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत pipe pipe)
अणु
	i915_reg_t reg = PIPEDSL(pipe);
	u32 line1, line2;
	u32 line_mask;

	अगर (IS_DISPLAY_VER(dev_priv, 2))
		line_mask = DSL_LINEMASK_GEN2;
	अन्यथा
		line_mask = DSL_LINEMASK_GEN3;

	line1 = पूर्णांकel_de_पढ़ो(dev_priv, reg) & line_mask;
	msleep(5);
	line2 = पूर्णांकel_de_पढ़ो(dev_priv, reg) & line_mask;

	वापस line1 != line2;
पूर्ण

अटल व्योम रुको_क्रम_pipe_scanline_moving(काष्ठा पूर्णांकel_crtc *crtc, bool state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/* Wait क्रम the display line to settle/start moving */
	अगर (रुको_क्रम(pipe_scanline_is_moving(dev_priv, pipe) == state, 100))
		drm_err(&dev_priv->drm,
			"pipe %c scanline %s wait timed out\n",
			pipe_name(pipe), onoff(state));
पूर्ण

अटल व्योम पूर्णांकel_रुको_क्रम_pipe_scanline_stopped(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	रुको_क्रम_pipe_scanline_moving(crtc, false);
पूर्ण

अटल व्योम पूर्णांकel_रुको_क्रम_pipe_scanline_moving(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	रुको_क्रम_pipe_scanline_moving(crtc, true);
पूर्ण

अटल व्योम
पूर्णांकel_रुको_क्रम_pipe_off(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		क्रमागत transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;
		i915_reg_t reg = PIPECONF(cpu_transcoder);

		/* Wait क्रम the Pipe State to go off */
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, reg,
					    I965_PIPECONF_ACTIVE, 100))
			drm_WARN(&dev_priv->drm, 1,
				 "pipe_off wait timed out\n");
	पूर्ण अन्यथा अणु
		पूर्णांकel_रुको_क्रम_pipe_scanline_stopped(crtc);
	पूर्ण
पूर्ण

/* Only क्रम pre-ILK configs */
व्योम निश्चित_pll(काष्ठा drm_i915_निजी *dev_priv,
		क्रमागत pipe pipe, bool state)
अणु
	u32 val;
	bool cur_state;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DPLL(pipe));
	cur_state = !!(val & DPLL_VCO_ENABLE);
	I915_STATE_WARN(cur_state != state,
	     "PLL state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
पूर्ण

/* XXX: the dsi pll is shared between MIPI DSI ports */
व्योम निश्चित_dsi_pll(काष्ठा drm_i915_निजी *dev_priv, bool state)
अणु
	u32 val;
	bool cur_state;

	vlv_cck_get(dev_priv);
	val = vlv_cck_पढ़ो(dev_priv, CCK_REG_DSI_PLL_CONTROL);
	vlv_cck_put(dev_priv);

	cur_state = val & DSI_PLL_VCO_EN;
	I915_STATE_WARN(cur_state != state,
	     "DSI PLL state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
पूर्ण

अटल व्योम निश्चित_fdi_tx(काष्ठा drm_i915_निजी *dev_priv,
			  क्रमागत pipe pipe, bool state)
अणु
	bool cur_state;

	अगर (HAS_DDI(dev_priv)) अणु
		/*
		 * DDI करोes not have a specअगरic FDI_TX रेजिस्टर.
		 *
		 * FDI is never fed from EDP transcoder
		 * so pipe->transcoder cast is fine here.
		 */
		क्रमागत transcoder cpu_transcoder = (क्रमागत transcoder)pipe;
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv,
					TRANS_DDI_FUNC_CTL(cpu_transcoder));
		cur_state = !!(val & TRANS_DDI_FUNC_ENABLE);
	पूर्ण अन्यथा अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_TX_CTL(pipe));
		cur_state = !!(val & FDI_TX_ENABLE);
	पूर्ण
	I915_STATE_WARN(cur_state != state,
	     "FDI TX state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
पूर्ण
#घोषणा निश्चित_fdi_tx_enabled(d, p) निश्चित_fdi_tx(d, p, true)
#घोषणा निश्चित_fdi_tx_disabled(d, p) निश्चित_fdi_tx(d, p, false)

अटल व्योम निश्चित_fdi_rx(काष्ठा drm_i915_निजी *dev_priv,
			  क्रमागत pipe pipe, bool state)
अणु
	u32 val;
	bool cur_state;

	val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(pipe));
	cur_state = !!(val & FDI_RX_ENABLE);
	I915_STATE_WARN(cur_state != state,
	     "FDI RX state assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
पूर्ण
#घोषणा निश्चित_fdi_rx_enabled(d, p) निश्चित_fdi_rx(d, p, true)
#घोषणा निश्चित_fdi_rx_disabled(d, p) निश्चित_fdi_rx(d, p, false)

अटल व्योम निश्चित_fdi_tx_pll_enabled(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत pipe pipe)
अणु
	u32 val;

	/* ILK FDI PLL is always enabled */
	अगर (IS_IRONLAKE(dev_priv))
		वापस;

	/* On Haswell, DDI ports are responsible क्रम the FDI PLL setup */
	अगर (HAS_DDI(dev_priv))
		वापस;

	val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_TX_CTL(pipe));
	I915_STATE_WARN(!(val & FDI_TX_PLL_ENABLE), "FDI TX PLL assertion failure, should be active but is disabled\n");
पूर्ण

व्योम निश्चित_fdi_rx_pll(काष्ठा drm_i915_निजी *dev_priv,
		       क्रमागत pipe pipe, bool state)
अणु
	u32 val;
	bool cur_state;

	val = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(pipe));
	cur_state = !!(val & FDI_RX_PLL_ENABLE);
	I915_STATE_WARN(cur_state != state,
	     "FDI RX PLL assertion failure (expected %s, current %s)\n",
			onoff(state), onoff(cur_state));
पूर्ण

व्योम निश्चित_panel_unlocked(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	i915_reg_t pp_reg;
	u32 val;
	क्रमागत pipe panel_pipe = INVALID_PIPE;
	bool locked = true;

	अगर (drm_WARN_ON(&dev_priv->drm, HAS_DDI(dev_priv)))
		वापस;

	अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		u32 port_sel;

		pp_reg = PP_CONTROL(0);
		port_sel = पूर्णांकel_de_पढ़ो(dev_priv, PP_ON_DELAYS(0)) & PANEL_PORT_SELECT_MASK;

		चयन (port_sel) अणु
		हाल PANEL_PORT_SELECT_LVDS:
			पूर्णांकel_lvds_port_enabled(dev_priv, PCH_LVDS, &panel_pipe);
			अवरोध;
		हाल PANEL_PORT_SELECT_DPA:
			g4x_dp_port_enabled(dev_priv, DP_A, PORT_A, &panel_pipe);
			अवरोध;
		हाल PANEL_PORT_SELECT_DPC:
			g4x_dp_port_enabled(dev_priv, PCH_DP_C, PORT_C, &panel_pipe);
			अवरोध;
		हाल PANEL_PORT_SELECT_DPD:
			g4x_dp_port_enabled(dev_priv, PCH_DP_D, PORT_D, &panel_pipe);
			अवरोध;
		शेष:
			MISSING_CASE(port_sel);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		/* presumably ग_लिखो lock depends on pipe, not port select */
		pp_reg = PP_CONTROL(pipe);
		panel_pipe = pipe;
	पूर्ण अन्यथा अणु
		u32 port_sel;

		pp_reg = PP_CONTROL(0);
		port_sel = पूर्णांकel_de_पढ़ो(dev_priv, PP_ON_DELAYS(0)) & PANEL_PORT_SELECT_MASK;

		drm_WARN_ON(&dev_priv->drm,
			    port_sel != PANEL_PORT_SELECT_LVDS);
		पूर्णांकel_lvds_port_enabled(dev_priv, LVDS, &panel_pipe);
	पूर्ण

	val = पूर्णांकel_de_पढ़ो(dev_priv, pp_reg);
	अगर (!(val & PANEL_POWER_ON) ||
	    ((val & PANEL_UNLOCK_MASK) == PANEL_UNLOCK_REGS))
		locked = false;

	I915_STATE_WARN(panel_pipe == pipe && locked,
	     "panel assertion failure, pipe %c regs locked\n",
	     pipe_name(pipe));
पूर्ण

व्योम निश्चित_pipe(काष्ठा drm_i915_निजी *dev_priv,
		 क्रमागत transcoder cpu_transcoder, bool state)
अणु
	bool cur_state;
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;

	/* we keep both pipes enabled on 830 */
	अगर (IS_I830(dev_priv))
		state = true;

	घातer_करोमुख्य = POWER_DOMAIN_TRANSCODER(cpu_transcoder);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (wakeref) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(cpu_transcoder));
		cur_state = !!(val & PIPECONF_ENABLE);

		पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);
	पूर्ण अन्यथा अणु
		cur_state = false;
	पूर्ण

	I915_STATE_WARN(cur_state != state,
			"transcoder %s assertion failure (expected %s, current %s)\n",
			transcoder_name(cpu_transcoder),
			onoff(state), onoff(cur_state));
पूर्ण

अटल व्योम निश्चित_plane(काष्ठा पूर्णांकel_plane *plane, bool state)
अणु
	क्रमागत pipe pipe;
	bool cur_state;

	cur_state = plane->get_hw_state(plane, &pipe);

	I915_STATE_WARN(cur_state != state,
			"%s assertion failure (expected %s, current %s)\n",
			plane->base.name, onoff(state), onoff(cur_state));
पूर्ण

#घोषणा निश्चित_plane_enabled(p) निश्चित_plane(p, true)
#घोषणा निश्चित_plane_disabled(p) निश्चित_plane(p, false)

अटल व्योम निश्चित_planes_disabled(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_plane *plane;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane)
		निश्चित_plane_disabled(plane);
पूर्ण

व्योम निश्चित_pch_transcoder_disabled(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत pipe pipe)
अणु
	u32 val;
	bool enabled;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PCH_TRANSCONF(pipe));
	enabled = !!(val & TRANS_ENABLE);
	I915_STATE_WARN(enabled,
	     "transcoder assertion failed, should be off on pipe %c but is still active\n",
	     pipe_name(pipe));
पूर्ण

अटल व्योम निश्चित_pch_dp_disabled(काष्ठा drm_i915_निजी *dev_priv,
				   क्रमागत pipe pipe, क्रमागत port port,
				   i915_reg_t dp_reg)
अणु
	क्रमागत pipe port_pipe;
	bool state;

	state = g4x_dp_port_enabled(dev_priv, dp_reg, port, &port_pipe);

	I915_STATE_WARN(state && port_pipe == pipe,
			"PCH DP %c enabled on transcoder %c, should be disabled\n",
			port_name(port), pipe_name(pipe));

	I915_STATE_WARN(HAS_PCH_IBX(dev_priv) && !state && port_pipe == PIPE_B,
			"IBX PCH DP %c still using transcoder B\n",
			port_name(port));
पूर्ण

अटल व्योम निश्चित_pch_hdmi_disabled(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत pipe pipe, क्रमागत port port,
				     i915_reg_t hdmi_reg)
अणु
	क्रमागत pipe port_pipe;
	bool state;

	state = पूर्णांकel_sdvo_port_enabled(dev_priv, hdmi_reg, &port_pipe);

	I915_STATE_WARN(state && port_pipe == pipe,
			"PCH HDMI %c enabled on transcoder %c, should be disabled\n",
			port_name(port), pipe_name(pipe));

	I915_STATE_WARN(HAS_PCH_IBX(dev_priv) && !state && port_pipe == PIPE_B,
			"IBX PCH HDMI %c still using transcoder B\n",
			port_name(port));
पूर्ण

अटल व्योम निश्चित_pch_ports_disabled(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत pipe pipe)
अणु
	क्रमागत pipe port_pipe;

	निश्चित_pch_dp_disabled(dev_priv, pipe, PORT_B, PCH_DP_B);
	निश्चित_pch_dp_disabled(dev_priv, pipe, PORT_C, PCH_DP_C);
	निश्चित_pch_dp_disabled(dev_priv, pipe, PORT_D, PCH_DP_D);

	I915_STATE_WARN(पूर्णांकel_crt_port_enabled(dev_priv, PCH_ADPA, &port_pipe) &&
			port_pipe == pipe,
			"PCH VGA enabled on transcoder %c, should be disabled\n",
			pipe_name(pipe));

	I915_STATE_WARN(पूर्णांकel_lvds_port_enabled(dev_priv, PCH_LVDS, &port_pipe) &&
			port_pipe == pipe,
			"PCH LVDS enabled on transcoder %c, should be disabled\n",
			pipe_name(pipe));

	/* PCH SDVOB multiplex with HDMIB */
	निश्चित_pch_hdmi_disabled(dev_priv, pipe, PORT_B, PCH_HDMIB);
	निश्चित_pch_hdmi_disabled(dev_priv, pipe, PORT_C, PCH_HDMIC);
	निश्चित_pch_hdmi_disabled(dev_priv, pipe, PORT_D, PCH_HDMID);
पूर्ण

व्योम vlv_रुको_port_पढ़ोy(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा पूर्णांकel_digital_port *dig_port,
			 अचिन्हित पूर्णांक expected_mask)
अणु
	u32 port_mask;
	i915_reg_t dpll_reg;

	चयन (dig_port->base.port) अणु
	हाल PORT_B:
		port_mask = DPLL_PORTB_READY_MASK;
		dpll_reg = DPLL(0);
		अवरोध;
	हाल PORT_C:
		port_mask = DPLL_PORTC_READY_MASK;
		dpll_reg = DPLL(0);
		expected_mask <<= 4;
		अवरोध;
	हाल PORT_D:
		port_mask = DPLL_PORTD_READY_MASK;
		dpll_reg = DPIO_PHY_STATUS;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (पूर्णांकel_de_रुको_क्रम_रेजिस्टर(dev_priv, dpll_reg,
				       port_mask, expected_mask, 1000))
		drm_WARN(&dev_priv->drm, 1,
			 "timed out waiting for [ENCODER:%d:%s] port ready: got 0x%x, expected 0x%x\n",
			 dig_port->base.base.base.id, dig_port->base.base.name,
			 पूर्णांकel_de_पढ़ो(dev_priv, dpll_reg) & port_mask,
			 expected_mask);
पूर्ण

अटल व्योम ilk_enable_pch_transcoder(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 val, pipeconf_val;

	/* Make sure PCH DPLL is enabled */
	निश्चित_shared_dpll_enabled(dev_priv, crtc_state->shared_dpll);

	/* FDI must be feeding us bits क्रम PCH ports */
	निश्चित_fdi_tx_enabled(dev_priv, pipe);
	निश्चित_fdi_rx_enabled(dev_priv, pipe);

	अगर (HAS_PCH_CPT(dev_priv)) अणु
		reg = TRANS_CHICKEN2(pipe);
		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		/*
		 * Workaround: Set the timing override bit
		 * beक्रमe enabling the pch transcoder.
		 */
		val |= TRANS_CHICKEN2_TIMING_OVERRIDE;
		/* Configure frame start delay to match the CPU */
		val &= ~TRANS_CHICKEN2_FRAME_START_DELAY_MASK;
		val |= TRANS_CHICKEN2_FRAME_START_DELAY(dev_priv->framestart_delay - 1);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण

	reg = PCH_TRANSCONF(pipe);
	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	pipeconf_val = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe));

	अगर (HAS_PCH_IBX(dev_priv)) अणु
		/* Configure frame start delay to match the CPU */
		val &= ~TRANS_FRAME_START_DELAY_MASK;
		val |= TRANS_FRAME_START_DELAY(dev_priv->framestart_delay - 1);

		/*
		 * Make the BPC in transcoder be consistent with
		 * that in pipeconf reg. For HDMI we must use 8bpc
		 * here क्रम both 8bpc and 12bpc.
		 */
		val &= ~PIPECONF_BPC_MASK;
		अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
			val |= PIPECONF_8BPC;
		अन्यथा
			val |= pipeconf_val & PIPECONF_BPC_MASK;
	पूर्ण

	val &= ~TRANS_INTERLACE_MASK;
	अगर ((pipeconf_val & PIPECONF_INTERLACE_MASK) == PIPECONF_INTERLACED_ILK) अणु
		अगर (HAS_PCH_IBX(dev_priv) &&
		    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO))
			val |= TRANS_LEGACY_INTERLACED_ILK;
		अन्यथा
			val |= TRANS_INTERLACED;
	पूर्ण अन्यथा अणु
		val |= TRANS_PROGRESSIVE;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val | TRANS_ENABLE);
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, reg, TRANS_STATE_ENABLE, 100))
		drm_err(&dev_priv->drm, "failed to enable transcoder %c\n",
			pipe_name(pipe));
पूर्ण

अटल व्योम lpt_enable_pch_transcoder(काष्ठा drm_i915_निजी *dev_priv,
				      क्रमागत transcoder cpu_transcoder)
अणु
	u32 val, pipeconf_val;

	/* FDI must be feeding us bits क्रम PCH ports */
	निश्चित_fdi_tx_enabled(dev_priv, (क्रमागत pipe) cpu_transcoder);
	निश्चित_fdi_rx_enabled(dev_priv, PIPE_A);

	val = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_CHICKEN2(PIPE_A));
	/* Workaround: set timing override bit. */
	val |= TRANS_CHICKEN2_TIMING_OVERRIDE;
	/* Configure frame start delay to match the CPU */
	val &= ~TRANS_CHICKEN2_FRAME_START_DELAY_MASK;
	val |= TRANS_CHICKEN2_FRAME_START_DELAY(dev_priv->framestart_delay - 1);
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_CHICKEN2(PIPE_A), val);

	val = TRANS_ENABLE;
	pipeconf_val = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(cpu_transcoder));

	अगर ((pipeconf_val & PIPECONF_INTERLACE_MASK_HSW) ==
	    PIPECONF_INTERLACED_ILK)
		val |= TRANS_INTERLACED;
	अन्यथा
		val |= TRANS_PROGRESSIVE;

	पूर्णांकel_de_ग_लिखो(dev_priv, LPT_TRANSCONF, val);
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, LPT_TRANSCONF,
				  TRANS_STATE_ENABLE, 100))
		drm_err(&dev_priv->drm, "Failed to enable PCH transcoder\n");
पूर्ण

अटल व्योम ilk_disable_pch_transcoder(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत pipe pipe)
अणु
	i915_reg_t reg;
	u32 val;

	/* FDI relies on the transcoder */
	निश्चित_fdi_tx_disabled(dev_priv, pipe);
	निश्चित_fdi_rx_disabled(dev_priv, pipe);

	/* Ports must be off as well */
	निश्चित_pch_ports_disabled(dev_priv, pipe);

	reg = PCH_TRANSCONF(pipe);
	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	val &= ~TRANS_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	/* रुको क्रम PCH transcoder off, transcoder state */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, reg, TRANS_STATE_ENABLE, 50))
		drm_err(&dev_priv->drm, "failed to disable transcoder %c\n",
			pipe_name(pipe));

	अगर (HAS_PCH_CPT(dev_priv)) अणु
		/* Workaround: Clear the timing override chicken bit again. */
		reg = TRANS_CHICKEN2(pipe);
		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		val &= ~TRANS_CHICKEN2_TIMING_OVERRIDE;
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण
पूर्ण

व्योम lpt_disable_pch_transcoder(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, LPT_TRANSCONF);
	val &= ~TRANS_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, LPT_TRANSCONF, val);
	/* रुको क्रम PCH transcoder off, transcoder state */
	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, LPT_TRANSCONF,
				    TRANS_STATE_ENABLE, 50))
		drm_err(&dev_priv->drm, "Failed to disable PCH transcoder\n");

	/* Workaround: clear timing override bit. */
	val = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_CHICKEN2(PIPE_A));
	val &= ~TRANS_CHICKEN2_TIMING_OVERRIDE;
	पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_CHICKEN2(PIPE_A), val);
पूर्ण

क्रमागत pipe पूर्णांकel_crtc_pch_transcoder(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (HAS_PCH_LPT(dev_priv))
		वापस PIPE_A;
	अन्यथा
		वापस crtc->pipe;
पूर्ण

व्योम पूर्णांकel_enable_pipe(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = new_crtc_state->cpu_transcoder;
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "enabling pipe %c\n", pipe_name(pipe));

	निश्चित_planes_disabled(crtc);

	/*
	 * A pipe without a PLL won't actually be able to drive bits from
	 * a plane.  On ILK+ the pipe PLLs are पूर्णांकegrated, so we करोn't
	 * need the check.
	 */
	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (पूर्णांकel_crtc_has_type(new_crtc_state, INTEL_OUTPUT_DSI))
			निश्चित_dsi_pll_enabled(dev_priv);
		अन्यथा
			निश्चित_pll_enabled(dev_priv, pipe);
	पूर्ण अन्यथा अणु
		अगर (new_crtc_state->has_pch_encoder) अणु
			/* अगर driving the PCH, we need FDI enabled */
			निश्चित_fdi_rx_pll_enabled(dev_priv,
						  पूर्णांकel_crtc_pch_transcoder(crtc));
			निश्चित_fdi_tx_pll_enabled(dev_priv,
						  (क्रमागत pipe) cpu_transcoder);
		पूर्ण
		/* FIXME: निश्चित CPU port conditions क्रम SNB+ */
	पूर्ण

	reg = PIPECONF(cpu_transcoder);
	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर (val & PIPECONF_ENABLE) अणु
		/* we keep both pipes enabled on 830 */
		drm_WARN_ON(&dev_priv->drm, !IS_I830(dev_priv));
		वापस;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val | PIPECONF_ENABLE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	/*
	 * Until the pipe starts PIPEDSL पढ़ोs will वापस a stale value,
	 * which causes an apparent vblank बारtamp jump when PIPEDSL
	 * resets to its proper value. That also messes up the frame count
	 * when it's derived from the timestamps. So let's रुको क्रम the
	 * pipe to start properly beक्रमe we call drm_crtc_vblank_on()
	 */
	अगर (पूर्णांकel_crtc_max_vblank_count(new_crtc_state) == 0)
		पूर्णांकel_रुको_क्रम_pipe_scanline_moving(crtc);
पूर्ण

व्योम पूर्णांकel_disable_pipe(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = old_crtc_state->cpu_transcoder;
	क्रमागत pipe pipe = crtc->pipe;
	i915_reg_t reg;
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "disabling pipe %c\n", pipe_name(pipe));

	/*
	 * Make sure planes won't keep trying to pump pixels to us,
	 * or we might hang the display.
	 */
	निश्चित_planes_disabled(crtc);

	reg = PIPECONF(cpu_transcoder);
	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	अगर ((val & PIPECONF_ENABLE) == 0)
		वापस;

	/*
	 * Double wide has implications क्रम planes
	 * so best keep it disabled when not needed.
	 */
	अगर (old_crtc_state->द्विगुन_wide)
		val &= ~PIPECONF_DOUBLE_WIDE;

	/* Don't disable pipe or pipe PLLs अगर needed */
	अगर (!IS_I830(dev_priv))
		val &= ~PIPECONF_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	अगर ((val & PIPECONF_ENABLE) == 0)
		पूर्णांकel_रुको_क्रम_pipe_off(old_crtc_state);
पूर्ण

bool
पूर्णांकel_क्रमmat_info_is_yuv_semiplanar(स्थिर काष्ठा drm_क्रमmat_info *info,
				    u64 modअगरier)
अणु
	वापस info->is_yuv &&
	       info->num_planes == (is_ccs_modअगरier(modअगरier) ? 4 : 2);
पूर्ण

अचिन्हित पूर्णांक
पूर्णांकel_tile_width_bytes(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(fb->dev);
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[color_plane];

	चयन (fb->modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
		वापस पूर्णांकel_tile_size(dev_priv);
	हाल I915_FORMAT_MOD_X_TILED:
		अगर (IS_DISPLAY_VER(dev_priv, 2))
			वापस 128;
		अन्यथा
			वापस 512;
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
		अगर (is_ccs_plane(fb, color_plane))
			वापस 128;
		fallthrough;
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS:
		अगर (is_ccs_plane(fb, color_plane))
			वापस 64;
		fallthrough;
	हाल I915_FORMAT_MOD_Y_TILED:
		अगर (IS_DISPLAY_VER(dev_priv, 2) || HAS_128_BYTE_Y_TILING(dev_priv))
			वापस 128;
		अन्यथा
			वापस 512;
	हाल I915_FORMAT_MOD_Yf_TILED_CCS:
		अगर (is_ccs_plane(fb, color_plane))
			वापस 128;
		fallthrough;
	हाल I915_FORMAT_MOD_Yf_TILED:
		चयन (cpp) अणु
		हाल 1:
			वापस 64;
		हाल 2:
		हाल 4:
			वापस 128;
		हाल 8:
		हाल 16:
			वापस 256;
		शेष:
			MISSING_CASE(cpp);
			वापस cpp;
		पूर्ण
		अवरोध;
	शेष:
		MISSING_CASE(fb->modअगरier);
		वापस cpp;
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक
पूर्णांकel_fb_align_height(स्थिर काष्ठा drm_framebuffer *fb,
		      पूर्णांक color_plane, अचिन्हित पूर्णांक height)
अणु
	अचिन्हित पूर्णांक tile_height = पूर्णांकel_tile_height(fb, color_plane);

	वापस ALIGN(height, tile_height);
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_rotation_info_size(स्थिर काष्ठा पूर्णांकel_rotation_info *rot_info)
अणु
	अचिन्हित पूर्णांक size = 0;
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(rot_info->plane); i++)
		size += rot_info->plane[i].dst_stride * rot_info->plane[i].width;

	वापस size;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_remapped_info_size(स्थिर काष्ठा पूर्णांकel_remapped_info *rem_info)
अणु
	अचिन्हित पूर्णांक size = 0;
	पूर्णांक i;

	क्रम (i = 0 ; i < ARRAY_SIZE(rem_info->plane); i++)
		size += rem_info->plane[i].dst_stride * rem_info->plane[i].height;

	वापस size;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_linear_alignment(स्थिर काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 9)
		वापस 256 * 1024;
	अन्यथा अगर (IS_I965G(dev_priv) || IS_I965GM(dev_priv) ||
		 IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		वापस 128 * 1024;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4)
		वापस 4 * 1024;
	अन्यथा
		वापस 0;
पूर्ण

अटल bool has_async_flips(काष्ठा drm_i915_निजी *i915)
अणु
	वापस DISPLAY_VER(i915) >= 5;
पूर्ण

अचिन्हित पूर्णांक पूर्णांकel_surf_alignment(स्थिर काष्ठा drm_framebuffer *fb,
				  पूर्णांक color_plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(fb->dev);

	/* AUX_DIST needs only 4K alignment */
	अगर ((DISPLAY_VER(dev_priv) < 12 && is_aux_plane(fb, color_plane)) ||
	    is_ccs_plane(fb, color_plane))
		वापस 4096;

	चयन (fb->modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
		वापस पूर्णांकel_linear_alignment(dev_priv);
	हाल I915_FORMAT_MOD_X_TILED:
		अगर (has_async_flips(dev_priv))
			वापस 256 * 1024;
		वापस 0;
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS:
		अगर (is_semiplanar_uv_plane(fb, color_plane))
			वापस पूर्णांकel_tile_row_size(fb, color_plane);
		fallthrough;
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC:
		वापस 16 * 1024;
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
	हाल I915_FORMAT_MOD_Yf_TILED_CCS:
	हाल I915_FORMAT_MOD_Y_TILED:
		अगर (DISPLAY_VER(dev_priv) >= 12 &&
		    is_semiplanar_uv_plane(fb, color_plane))
			वापस पूर्णांकel_tile_row_size(fb, color_plane);
		fallthrough;
	हाल I915_FORMAT_MOD_Yf_TILED:
		वापस 1 * 1024 * 1024;
	शेष:
		MISSING_CASE(fb->modअगरier);
		वापस 0;
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_plane_uses_fence(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);

	वापस DISPLAY_VER(dev_priv) < 4 ||
		(plane->has_fbc &&
		 plane_state->view.gtt.type == I915_GGTT_VIEW_NORMAL);
पूर्ण

काष्ठा i915_vma *
पूर्णांकel_pin_and_fence_fb_obj(काष्ठा drm_framebuffer *fb,
			   bool phys_cursor,
			   स्थिर काष्ठा i915_ggtt_view *view,
			   bool uses_fence,
			   अचिन्हित दीर्घ *out_flags)
अणु
	काष्ठा drm_device *dev = fb->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(fb);
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा i915_gem_ww_ctx ww;
	काष्ठा i915_vma *vma;
	अचिन्हित पूर्णांक pinctl;
	u32 alignment;
	पूर्णांक ret;

	अगर (drm_WARN_ON(dev, !i915_gem_object_is_framebuffer(obj)))
		वापस ERR_PTR(-EINVAL);

	अगर (phys_cursor)
		alignment = पूर्णांकel_cursor_alignment(dev_priv);
	अन्यथा
		alignment = पूर्णांकel_surf_alignment(fb, 0);
	अगर (drm_WARN_ON(dev, alignment && !is_घातer_of_2(alignment)))
		वापस ERR_PTR(-EINVAL);

	/* Note that the w/a also requires 64 PTE of padding following the
	 * bo. We currently fill all unused PTE with the shaकरोw page and so
	 * we should always have valid PTE following the scanout preventing
	 * the VT-d warning.
	 */
	अगर (पूर्णांकel_scanout_needs_vtd_wa(dev_priv) && alignment < 256 * 1024)
		alignment = 256 * 1024;

	/*
	 * Global gtt pte रेजिस्टरs are special रेजिस्टरs which actually क्रमward
	 * ग_लिखोs to a chunk of प्रणाली memory. Which means that there is no risk
	 * that the रेजिस्टर values disappear as soon as we call
	 * पूर्णांकel_runसमय_pm_put(), so it is correct to wrap only the
	 * pin/unpin/fence and not more.
	 */
	wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	atomic_inc(&dev_priv->gpu_error.pending_fb_pin);

	/*
	 * Valleyview is definitely limited to scanning out the first
	 * 512MiB. Lets presume this behaviour was inherited from the
	 * g4x display engine and that all earlier gen are similarly
	 * limited. Testing suggests that it is a little more
	 * complicated than this. For example, Cherryview appears quite
	 * happy to scanout from anywhere within its global aperture.
	 */
	pinctl = 0;
	अगर (HAS_GMCH(dev_priv))
		pinctl |= PIN_MAPPABLE;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	ret = i915_gem_object_lock(obj, &ww);
	अगर (!ret && phys_cursor)
		ret = i915_gem_object_attach_phys(obj, alignment);
	अगर (!ret)
		ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		जाओ err;

	अगर (!ret) अणु
		vma = i915_gem_object_pin_to_display_plane(obj, &ww, alignment,
							   view, pinctl);
		अगर (IS_ERR(vma)) अणु
			ret = PTR_ERR(vma);
			जाओ err_unpin;
		पूर्ण
	पूर्ण

	अगर (uses_fence && i915_vma_is_map_and_fenceable(vma)) अणु
		/*
		 * Install a fence क्रम tiled scan-out. Pre-i965 always needs a
		 * fence, whereas 965+ only requires a fence अगर using
		 * framebuffer compression.  For simplicity, we always, when
		 * possible, install a fence as the cost is not that onerous.
		 *
		 * If we fail to fence the tiled scanout, then either the
		 * modeset will reject the change (which is highly unlikely as
		 * the affected प्रणालीs, all but one, करो not have unmappable
		 * space) or we will not be able to enable full घातersaving
		 * techniques (also likely not to apply due to various limits
		 * FBC and the like impose on the size of the buffer, which
		 * presumably we violated anyway with this unmappable buffer).
		 * Anyway, it is presumably better to stumble onwards with
		 * something and try to run the प्रणाली in a "less than optimal"
		 * mode that matches the user configuration.
		 */
		ret = i915_vma_pin_fence(vma);
		अगर (ret != 0 && DISPLAY_VER(dev_priv) < 4) अणु
			i915_vma_unpin(vma);
			जाओ err_unpin;
		पूर्ण
		ret = 0;

		अगर (vma->fence)
			*out_flags |= PLANE_HAS_FENCE;
	पूर्ण

	i915_vma_get(vma);

err_unpin:
	i915_gem_object_unpin_pages(obj);
err:
	अगर (ret == -EDEADLK) अणु
		ret = i915_gem_ww_ctx_backoff(&ww);
		अगर (!ret)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	अगर (ret)
		vma = ERR_PTR(ret);

	atomic_dec(&dev_priv->gpu_error.pending_fb_pin);
	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, wakeref);
	वापस vma;
पूर्ण

व्योम पूर्णांकel_unpin_fb_vma(काष्ठा i915_vma *vma, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & PLANE_HAS_FENCE)
		i915_vma_unpin_fence(vma);
	i915_vma_unpin(vma);
	i915_vma_put(vma);
पूर्ण

/*
 * Convert the x/y offsets पूर्णांकo a linear offset.
 * Only valid with 0/180 degree rotation, which is fine since linear
 * offset is only used with linear buffers on pre-hsw and tiled buffers
 * with gen2/3, and 90/270 degree rotations isn't supported on any of them.
 */
u32 पूर्णांकel_fb_xy_to_linear(पूर्णांक x, पूर्णांक y,
			  स्थिर काष्ठा पूर्णांकel_plane_state *state,
			  पूर्णांक color_plane)
अणु
	स्थिर काष्ठा drm_framebuffer *fb = state->hw.fb;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[color_plane];
	अचिन्हित पूर्णांक pitch = state->view.color_plane[color_plane].stride;

	वापस y * pitch + x * cpp;
पूर्ण

/*
 * Add the x/y offsets derived from fb->offsets[] to the user
 * specअगरied plane src x/y offsets. The resulting x/y offsets
 * specअगरy the start of scanout from the beginning of the gtt mapping.
 */
व्योम पूर्णांकel_add_fb_offsets(पूर्णांक *x, पूर्णांक *y,
			  स्थिर काष्ठा पूर्णांकel_plane_state *state,
			  पूर्णांक color_plane)

अणु
	*x += state->view.color_plane[color_plane].x;
	*y += state->view.color_plane[color_plane].y;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_fb_modअगरier_to_tiling(u64 fb_modअगरier)
अणु
	चयन (fb_modअगरier) अणु
	हाल I915_FORMAT_MOD_X_TILED:
		वापस I915_TILING_X;
	हाल I915_FORMAT_MOD_Y_TILED:
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS:
		वापस I915_TILING_Y;
	शेष:
		वापस I915_TILING_NONE;
	पूर्ण
पूर्ण

/*
 * From the Sky Lake PRM:
 * "The Color Control Surface (CCS) contains the compression status of
 *  the cache-line pairs. The compression state of the cache-line pair
 *  is specअगरied by 2 bits in the CCS. Each CCS cache-line represents
 *  an area on the मुख्य surface of 16 x16 sets of 128 byte Y-tiled
 *  cache-line-pairs. CCS is always Y tiled."
 *
 * Since cache line pairs refers to horizontally adjacent cache lines,
 * each cache line in the CCS corresponds to an area of 32x16 cache
 * lines on the मुख्य surface. Since each pixel is 4 bytes, this gives
 * us a ratio of one byte in the CCS क्रम each 8x16 pixels in the
 * मुख्य surface.
 */
अटल स्थिर काष्ठा drm_क्रमmat_info skl_ccs_क्रमmats[] = अणु
	अणु .क्रमmat = DRM_FORMAT_XRGB8888, .depth = 24, .num_planes = 2,
	  .cpp = अणु 4, 1, पूर्ण, .hsub = 8, .vsub = 16, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_XBGR8888, .depth = 24, .num_planes = 2,
	  .cpp = अणु 4, 1, पूर्ण, .hsub = 8, .vsub = 16, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ARGB8888, .depth = 32, .num_planes = 2,
	  .cpp = अणु 4, 1, पूर्ण, .hsub = 8, .vsub = 16, .has_alpha = true, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ABGR8888, .depth = 32, .num_planes = 2,
	  .cpp = अणु 4, 1, पूर्ण, .hsub = 8, .vsub = 16, .has_alpha = true, पूर्ण,
पूर्ण;

/*
 * Gen-12 compression uses 4 bits of CCS data क्रम each cache line pair in the
 * मुख्य surface. And each 64B CCS cache line represents an area of 4x1 Y-tiles
 * in the मुख्य surface. With 4 byte pixels and each Y-tile having dimensions of
 * 32x32 pixels, the ratio turns out to 1B in the CCS क्रम every 2x32 pixels in
 * the मुख्य surface.
 */
अटल स्थिर काष्ठा drm_क्रमmat_info gen12_ccs_क्रमmats[] = अणु
	अणु .क्रमmat = DRM_FORMAT_XRGB8888, .depth = 24, .num_planes = 2,
	  .अक्षर_per_block = अणु 4, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_XBGR8888, .depth = 24, .num_planes = 2,
	  .अक्षर_per_block = अणु 4, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ARGB8888, .depth = 32, .num_planes = 2,
	  .अक्षर_per_block = अणु 4, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ABGR8888, .depth = 32, .num_planes = 2,
	  .अक्षर_per_block = अणु 4, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_YUYV, .num_planes = 2,
	  .अक्षर_per_block = अणु 2, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_YVYU, .num_planes = 2,
	  .अक्षर_per_block = अणु 2, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_UYVY, .num_planes = 2,
	  .अक्षर_per_block = अणु 2, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_VYUY, .num_planes = 2,
	  .अक्षर_per_block = अणु 2, 1 पूर्ण, .block_w = अणु 1, 2 पूर्ण, .block_h = अणु 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 1, .is_yuv = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_NV12, .num_planes = 4,
	  .अक्षर_per_block = अणु 1, 2, 1, 1 पूर्ण, .block_w = अणु 1, 1, 4, 4 पूर्ण, .block_h = अणु 1, 1, 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_P010, .num_planes = 4,
	  .अक्षर_per_block = अणु 2, 4, 1, 1 पूर्ण, .block_w = अणु 1, 1, 2, 2 पूर्ण, .block_h = अणु 1, 1, 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_P012, .num_planes = 4,
	  .अक्षर_per_block = अणु 2, 4, 1, 1 पूर्ण, .block_w = अणु 1, 1, 2, 2 पूर्ण, .block_h = अणु 1, 1, 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_P016, .num_planes = 4,
	  .अक्षर_per_block = अणु 2, 4, 1, 1 पूर्ण, .block_w = अणु 1, 1, 2, 2 पूर्ण, .block_h = अणु 1, 1, 1, 1 पूर्ण,
	  .hsub = 2, .vsub = 2, .is_yuv = true पूर्ण,
पूर्ण;

/*
 * Same as gen12_ccs_क्रमmats[] above, but with additional surface used
 * to pass Clear Color inक्रमmation in plane 2 with 64 bits of data.
 */
अटल स्थिर काष्ठा drm_क्रमmat_info gen12_ccs_cc_क्रमmats[] = अणु
	अणु .क्रमmat = DRM_FORMAT_XRGB8888, .depth = 24, .num_planes = 3,
	  .अक्षर_per_block = अणु 4, 1, 0 पूर्ण, .block_w = अणु 1, 2, 2 पूर्ण, .block_h = अणु 1, 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_XBGR8888, .depth = 24, .num_planes = 3,
	  .अक्षर_per_block = अणु 4, 1, 0 पूर्ण, .block_w = अणु 1, 2, 2 पूर्ण, .block_h = अणु 1, 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ARGB8888, .depth = 32, .num_planes = 3,
	  .अक्षर_per_block = अणु 4, 1, 0 पूर्ण, .block_w = अणु 1, 2, 2 पूर्ण, .block_h = अणु 1, 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
	अणु .क्रमmat = DRM_FORMAT_ABGR8888, .depth = 32, .num_planes = 3,
	  .अक्षर_per_block = अणु 4, 1, 0 पूर्ण, .block_w = अणु 1, 2, 2 पूर्ण, .block_h = अणु 1, 1, 1 पूर्ण,
	  .hsub = 1, .vsub = 1, .has_alpha = true पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा drm_क्रमmat_info *
lookup_क्रमmat_info(स्थिर काष्ठा drm_क्रमmat_info क्रमmats[],
		   पूर्णांक num_क्रमmats, u32 क्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_क्रमmats; i++) अणु
		अगर (क्रमmats[i].क्रमmat == क्रमmat)
			वापस &क्रमmats[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा drm_क्रमmat_info *
पूर्णांकel_get_क्रमmat_info(स्थिर काष्ठा drm_mode_fb_cmd2 *cmd)
अणु
	चयन (cmd->modअगरier[0]) अणु
	हाल I915_FORMAT_MOD_Y_TILED_CCS:
	हाल I915_FORMAT_MOD_Yf_TILED_CCS:
		वापस lookup_क्रमmat_info(skl_ccs_क्रमmats,
					  ARRAY_SIZE(skl_ccs_क्रमmats),
					  cmd->pixel_क्रमmat);
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS:
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_MC_CCS:
		वापस lookup_क्रमmat_info(gen12_ccs_क्रमmats,
					  ARRAY_SIZE(gen12_ccs_क्रमmats),
					  cmd->pixel_क्रमmat);
	हाल I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC:
		वापस lookup_क्रमmat_info(gen12_ccs_cc_क्रमmats,
					  ARRAY_SIZE(gen12_ccs_cc_क्रमmats),
					  cmd->pixel_क्रमmat);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक gen12_ccs_aux_stride(काष्ठा drm_framebuffer *fb, पूर्णांक ccs_plane)
अणु
	वापस DIV_ROUND_UP(fb->pitches[skl_ccs_to_मुख्य_plane(fb, ccs_plane)],
			    512) * 64;
पूर्ण

u32 पूर्णांकel_plane_fb_max_stride(काष्ठा drm_i915_निजी *dev_priv,
			      u32 pixel_क्रमmat, u64 modअगरier)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_plane *plane;

	/*
	 * We assume the primary plane क्रम pipe A has
	 * the highest stride limits of them all,
	 * अगर in हाल pipe A is disabled, use the first pipe from pipe_mask.
	 */
	crtc = पूर्णांकel_get_first_crtc(dev_priv);
	अगर (!crtc)
		वापस 0;

	plane = to_पूर्णांकel_plane(crtc->base.primary);

	वापस plane->max_stride(plane, pixel_क्रमmat, modअगरier,
				 DRM_MODE_ROTATE_0);
पूर्ण

अटल
u32 पूर्णांकel_fb_max_stride(काष्ठा drm_i915_निजी *dev_priv,
			u32 pixel_क्रमmat, u64 modअगरier)
अणु
	/*
	 * Arbitrary limit क्रम gen4+ chosen to match the
	 * render engine max stride.
	 *
	 * The new CCS hash mode makes remapping impossible
	 */
	अगर (!is_ccs_modअगरier(modअगरier)) अणु
		अगर (DISPLAY_VER(dev_priv) >= 7)
			वापस 256*1024;
		अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4)
			वापस 128*1024;
	पूर्ण

	वापस पूर्णांकel_plane_fb_max_stride(dev_priv, pixel_क्रमmat, modअगरier);
पूर्ण

अटल u32
पूर्णांकel_fb_stride_alignment(स्थिर काष्ठा drm_framebuffer *fb, पूर्णांक color_plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(fb->dev);
	u32 tile_width;

	अगर (is_surface_linear(fb, color_plane)) अणु
		u32 max_stride = पूर्णांकel_plane_fb_max_stride(dev_priv,
							   fb->क्रमmat->क्रमmat,
							   fb->modअगरier);

		/*
		 * To make remapping with linear generally feasible
		 * we need the stride to be page aligned.
		 */
		अगर (fb->pitches[color_plane] > max_stride &&
		    !is_ccs_modअगरier(fb->modअगरier))
			वापस पूर्णांकel_tile_size(dev_priv);
		अन्यथा
			वापस 64;
	पूर्ण

	tile_width = पूर्णांकel_tile_width_bytes(fb, color_plane);
	अगर (is_ccs_modअगरier(fb->modअगरier)) अणु
		/*
		 * Display WA #0531: skl,bxt,kbl,glk
		 *
		 * Render decompression and plane width > 3840
		 * combined with horizontal panning requires the
		 * plane stride to be a multiple of 4. We'll just
		 * require the entire fb to accommodate that to aव्योम
		 * potential runसमय errors at plane configuration समय.
		 */
		अगर ((IS_DISPLAY_VER(dev_priv, 9) || IS_GEMINILAKE(dev_priv)) &&
		    color_plane == 0 && fb->width > 3840)
			tile_width *= 4;
		/*
		 * The मुख्य surface pitch must be padded to a multiple of four
		 * tile widths.
		 */
		अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12)
			tile_width *= 4;
	पूर्ण
	वापस tile_width;
पूर्ण

अटल काष्ठा i915_vma *
initial_plane_vma(काष्ठा drm_i915_निजी *i915,
		  काष्ठा पूर्णांकel_initial_plane_config *plane_config)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 base, size;

	अगर (plane_config->size == 0)
		वापस शून्य;

	base = round_करोwn(plane_config->base,
			  I915_GTT_MIN_ALIGNMENT);
	size = round_up(plane_config->base + plane_config->size,
			I915_GTT_MIN_ALIGNMENT);
	size -= base;

	/*
	 * If the FB is too big, just करोn't use it since fbdev is not very
	 * important and we should probably use that space with FBC or other
	 * features.
	 */
	अगर (size * 2 > i915->stolen_usable_size)
		वापस शून्य;

	obj = i915_gem_object_create_stolen_क्रम_pपुनः_स्मृतिated(i915, base, size);
	अगर (IS_ERR(obj))
		वापस शून्य;

	/*
	 * Mark it WT ahead of समय to aव्योम changing the
	 * cache_level during fbdev initialization. The
	 * unbind there would get stuck रुकोing क्रम rcu.
	 */
	i915_gem_object_set_cache_coherency(obj, HAS_WT(i915) ?
					    I915_CACHE_WT : I915_CACHE_NONE);

	चयन (plane_config->tiling) अणु
	हाल I915_TILING_NONE:
		अवरोध;
	हाल I915_TILING_X:
	हाल I915_TILING_Y:
		obj->tiling_and_stride =
			plane_config->fb->base.pitches[0] |
			plane_config->tiling;
		अवरोध;
	शेष:
		MISSING_CASE(plane_config->tiling);
		जाओ err_obj;
	पूर्ण

	vma = i915_vma_instance(obj, &i915->ggtt.vm, शून्य);
	अगर (IS_ERR(vma))
		जाओ err_obj;

	अगर (i915_ggtt_pin(vma, शून्य, 0, PIN_MAPPABLE | PIN_OFFSET_FIXED | base))
		जाओ err_obj;

	अगर (i915_gem_object_is_tiled(obj) &&
	    !i915_vma_is_map_and_fenceable(vma))
		जाओ err_obj;

	वापस vma;

err_obj:
	i915_gem_object_put(obj);
	वापस शून्य;
पूर्ण

अटल bool
पूर्णांकel_alloc_initial_plane_obj(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_initial_plane_config *plane_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_mode_fb_cmd2 mode_cmd = अणु 0 पूर्ण;
	काष्ठा drm_framebuffer *fb = &plane_config->fb->base;
	काष्ठा i915_vma *vma;

	चयन (fb->modअगरier) अणु
	हाल DRM_FORMAT_MOD_LINEAR:
	हाल I915_FORMAT_MOD_X_TILED:
	हाल I915_FORMAT_MOD_Y_TILED:
		अवरोध;
	शेष:
		drm_dbg(&dev_priv->drm,
			"Unsupported modifier for initial FB: 0x%llx\n",
			fb->modअगरier);
		वापस false;
	पूर्ण

	vma = initial_plane_vma(dev_priv, plane_config);
	अगर (!vma)
		वापस false;

	mode_cmd.pixel_क्रमmat = fb->क्रमmat->क्रमmat;
	mode_cmd.width = fb->width;
	mode_cmd.height = fb->height;
	mode_cmd.pitches[0] = fb->pitches[0];
	mode_cmd.modअगरier[0] = fb->modअगरier;
	mode_cmd.flags = DRM_MODE_FB_MODIFIERS;

	अगर (पूर्णांकel_framebuffer_init(to_पूर्णांकel_framebuffer(fb),
				   vma->obj, &mode_cmd)) अणु
		drm_dbg_kms(&dev_priv->drm, "intel fb init failed\n");
		जाओ err_vma;
	पूर्ण

	plane_config->vma = vma;
	वापस true;

err_vma:
	i915_vma_put(vma);
	वापस false;
पूर्ण

अटल व्योम
पूर्णांकel_set_plane_visible(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			काष्ठा पूर्णांकel_plane_state *plane_state,
			bool visible)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);

	plane_state->uapi.visible = visible;

	अगर (visible)
		crtc_state->uapi.plane_mask |= drm_plane_mask(&plane->base);
	अन्यथा
		crtc_state->uapi.plane_mask &= ~drm_plane_mask(&plane->base);
पूर्ण

अटल व्योम fixup_plane_biपंचांगasks(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा drm_plane *plane;

	/*
	 * Active_planes aliases अगर multiple "primary" or cursor planes
	 * have been used on the same (or wrong) pipe. plane_mask uses
	 * unique ids, hence we can use that to reस्थिरruct active_planes.
	 */
	crtc_state->enabled_planes = 0;
	crtc_state->active_planes = 0;

	drm_क्रम_each_plane_mask(plane, &dev_priv->drm,
				crtc_state->uapi.plane_mask) अणु
		crtc_state->enabled_planes |= BIT(to_पूर्णांकel_plane(plane)->id);
		crtc_state->active_planes |= BIT(to_पूर्णांकel_plane(plane)->id);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_plane_disable_noatomic(काष्ठा पूर्णांकel_crtc *crtc,
					 काष्ठा पूर्णांकel_plane *plane)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		to_पूर्णांकel_crtc_state(crtc->base.state);
	काष्ठा पूर्णांकel_plane_state *plane_state =
		to_पूर्णांकel_plane_state(plane->base.state);

	drm_dbg_kms(&dev_priv->drm,
		    "Disabling [PLANE:%d:%s] on [CRTC:%d:%s]\n",
		    plane->base.base.id, plane->base.name,
		    crtc->base.base.id, crtc->base.name);

	पूर्णांकel_set_plane_visible(crtc_state, plane_state, false);
	fixup_plane_biपंचांगasks(crtc_state);
	crtc_state->data_rate[plane->id] = 0;
	crtc_state->min_cdclk[plane->id] = 0;

	अगर (plane->id == PLANE_PRIMARY)
		hsw_disable_ips(crtc_state);

	/*
	 * Vblank समय updates from the shaकरोw to live plane control रेजिस्टर
	 * are blocked अगर the memory self-refresh mode is active at that
	 * moment. So to make sure the plane माला_लो truly disabled, disable
	 * first the self-refresh mode. The self-refresh enable bit in turn
	 * will be checked/applied by the HW only at the next frame start
	 * event which is after the vblank start event, so we need to have a
	 * रुको-क्रम-vblank between disabling the plane and the pipe.
	 */
	अगर (HAS_GMCH(dev_priv) &&
	    पूर्णांकel_set_memory_cxsr(dev_priv, false))
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, crtc->pipe);

	/*
	 * Gen2 reports pipe underruns whenever all planes are disabled.
	 * So disable underrun reporting beक्रमe all the planes get disabled.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 2) && !crtc_state->active_planes)
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, crtc->pipe, false);

	पूर्णांकel_disable_plane(plane, crtc_state);
	पूर्णांकel_रुको_क्रम_vblank(dev_priv, crtc->pipe);
पूर्ण

अटल व्योम
पूर्णांकel_find_initial_plane_obj(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc,
			     काष्ठा पूर्णांकel_initial_plane_config *plane_config)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_crtc *c;
	काष्ठा drm_plane *primary = पूर्णांकel_crtc->base.primary;
	काष्ठा drm_plane_state *plane_state = primary->state;
	काष्ठा पूर्णांकel_plane *पूर्णांकel_plane = to_पूर्णांकel_plane(primary);
	काष्ठा पूर्णांकel_plane_state *पूर्णांकel_state =
		to_पूर्णांकel_plane_state(plane_state);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		to_पूर्णांकel_crtc_state(पूर्णांकel_crtc->base.state);
	काष्ठा drm_framebuffer *fb;
	काष्ठा i915_vma *vma;

	/*
	 * TODO:
	 *   Disable planes अगर get_initial_plane_config() failed.
	 *   Make sure things work अगर the surface base is not page aligned.
	 */
	अगर (!plane_config->fb)
		वापस;

	अगर (पूर्णांकel_alloc_initial_plane_obj(पूर्णांकel_crtc, plane_config)) अणु
		fb = &plane_config->fb->base;
		vma = plane_config->vma;
		जाओ valid_fb;
	पूर्ण

	/*
	 * Failed to alloc the obj, check to see अगर we should share
	 * an fb with another CRTC instead
	 */
	क्रम_each_crtc(dev, c) अणु
		काष्ठा पूर्णांकel_plane_state *state;

		अगर (c == &पूर्णांकel_crtc->base)
			जारी;

		अगर (!to_पूर्णांकel_crtc_state(c->state)->uapi.active)
			जारी;

		state = to_पूर्णांकel_plane_state(c->primary->state);
		अगर (!state->vma)
			जारी;

		अगर (पूर्णांकel_plane_ggtt_offset(state) == plane_config->base) अणु
			fb = state->hw.fb;
			vma = state->vma;
			जाओ valid_fb;
		पूर्ण
	पूर्ण

	/*
	 * We've failed to reस्थिरruct the BIOS FB.  Current display state
	 * indicates that the primary plane is visible, but has a शून्य FB,
	 * which will lead to problems later अगर we करोn't fix it up.  The
	 * simplest solution is to just disable the primary plane now and
	 * pretend the BIOS never had it enabled.
	 */
	पूर्णांकel_plane_disable_noatomic(पूर्णांकel_crtc, पूर्णांकel_plane);
	अगर (crtc_state->bigjoiner) अणु
		काष्ठा पूर्णांकel_crtc *slave =
			crtc_state->bigjoiner_linked_crtc;
		पूर्णांकel_plane_disable_noatomic(slave, to_पूर्णांकel_plane(slave->base.primary));
	पूर्ण

	वापस;

valid_fb:
	plane_state->rotation = plane_config->rotation;
	पूर्णांकel_fb_fill_view(to_पूर्णांकel_framebuffer(fb), plane_state->rotation,
			   &पूर्णांकel_state->view);

	__i915_vma_pin(vma);
	पूर्णांकel_state->vma = i915_vma_get(vma);
	अगर (पूर्णांकel_plane_uses_fence(पूर्णांकel_state) && i915_vma_pin_fence(vma) == 0)
		अगर (vma->fence)
			पूर्णांकel_state->flags |= PLANE_HAS_FENCE;

	plane_state->src_x = 0;
	plane_state->src_y = 0;
	plane_state->src_w = fb->width << 16;
	plane_state->src_h = fb->height << 16;

	plane_state->crtc_x = 0;
	plane_state->crtc_y = 0;
	plane_state->crtc_w = fb->width;
	plane_state->crtc_h = fb->height;

	अगर (plane_config->tiling)
		dev_priv->preserve_bios_swizzle = true;

	plane_state->fb = fb;
	drm_framebuffer_get(fb);

	plane_state->crtc = &पूर्णांकel_crtc->base;
	पूर्णांकel_plane_copy_uapi_to_hw_state(पूर्णांकel_state, पूर्णांकel_state,
					  पूर्णांकel_crtc);

	पूर्णांकel_frontbuffer_flush(to_पूर्णांकel_frontbuffer(fb), ORIGIN_सूचीTYFB);

	atomic_or(to_पूर्णांकel_plane(primary)->frontbuffer_bit,
		  &to_पूर्णांकel_frontbuffer(fb)->bits);
पूर्ण

अचिन्हित पूर्णांक
पूर्णांकel_plane_fence_y_offset(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	पूर्णांक x = 0, y = 0;

	पूर्णांकel_plane_adjust_aligned_offset(&x, &y, plane_state, 0,
					  plane_state->view.color_plane[0].offset, 0);

	वापस y;
पूर्ण

अटल पूर्णांक
__पूर्णांकel_display_resume(काष्ठा drm_device *dev,
		       काष्ठा drm_atomic_state *state,
		       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_crtc *crtc;
	पूर्णांक i, ret;

	पूर्णांकel_modeset_setup_hw_state(dev, ctx);
	पूर्णांकel_vga_redisable(to_i915(dev));

	अगर (!state)
		वापस 0;

	/*
	 * We've duplicated the state, poपूर्णांकers to the old state are invalid.
	 *
	 * Don't attempt to use the old state until we commit the duplicated state.
	 */
	क्रम_each_new_crtc_in_state(state, crtc, crtc_state, i) अणु
		/*
		 * Force recalculation even अगर we restore
		 * current state. With fast modeset this may not result
		 * in a modeset when the state is compatible.
		 */
		crtc_state->mode_changed = true;
	पूर्ण

	/* ignore any reset values/BIOS leftovers in the WM रेजिस्टरs */
	अगर (!HAS_GMCH(to_i915(dev)))
		to_पूर्णांकel_atomic_state(state)->skip_पूर्णांकermediate_wm = true;

	ret = drm_atomic_helper_commit_duplicated_state(state, ctx);

	drm_WARN_ON(dev, ret == -EDEADLK);
	वापस ret;
पूर्ण

अटल bool gpu_reset_clobbers_display(काष्ठा drm_i915_निजी *dev_priv)
अणु
	वापस (INTEL_INFO(dev_priv)->gpu_reset_clobbers_display &&
		पूर्णांकel_has_gpu_reset(&dev_priv->gt));
पूर्ण

व्योम पूर्णांकel_display_prepare_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_modeset_acquire_ctx *ctx = &dev_priv->reset_ctx;
	काष्ठा drm_atomic_state *state;
	पूर्णांक ret;

	अगर (!HAS_DISPLAY(dev_priv))
		वापस;

	/* reset करोesn't touch the display */
	अगर (!dev_priv->params.क्रमce_reset_modeset_test &&
	    !gpu_reset_clobbers_display(dev_priv))
		वापस;

	/* We have a modeset vs reset deadlock, defensively unअवरोध it. */
	set_bit(I915_RESET_MODESET, &dev_priv->gt.reset.flags);
	smp_mb__after_atomic();
	wake_up_bit(&dev_priv->gt.reset.flags, I915_RESET_MODESET);

	अगर (atomic_पढ़ो(&dev_priv->gpu_error.pending_fb_pin)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Modeset potentially stuck, unbreaking through wedging\n");
		पूर्णांकel_gt_set_wedged(&dev_priv->gt);
	पूर्ण

	/*
	 * Need mode_config.mutex so that we करोn't
	 * trample ongoing ->detect() and whatnot.
	 */
	mutex_lock(&dev->mode_config.mutex);
	drm_modeset_acquire_init(ctx, 0);
	जबतक (1) अणु
		ret = drm_modeset_lock_all_ctx(dev, ctx);
		अगर (ret != -EDEADLK)
			अवरोध;

		drm_modeset_backoff(ctx);
	पूर्ण
	/*
	 * Disabling the crtcs gracefully seems nicer. Also the
	 * g33 करोcs say we should at least disable all the planes.
	 */
	state = drm_atomic_helper_duplicate_state(dev, ctx);
	अगर (IS_ERR(state)) अणु
		ret = PTR_ERR(state);
		drm_err(&dev_priv->drm, "Duplicating state failed with %i\n",
			ret);
		वापस;
	पूर्ण

	ret = drm_atomic_helper_disable_all(dev, ctx);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "Suspending crtc's failed with %i\n",
			ret);
		drm_atomic_state_put(state);
		वापस;
	पूर्ण

	dev_priv->modeset_restore_state = state;
	state->acquire_ctx = ctx;
पूर्ण

व्योम पूर्णांकel_display_finish_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा drm_modeset_acquire_ctx *ctx = &dev_priv->reset_ctx;
	काष्ठा drm_atomic_state *state;
	पूर्णांक ret;

	अगर (!HAS_DISPLAY(dev_priv))
		वापस;

	/* reset करोesn't touch the display */
	अगर (!test_bit(I915_RESET_MODESET, &dev_priv->gt.reset.flags))
		वापस;

	state = fetch_and_zero(&dev_priv->modeset_restore_state);
	अगर (!state)
		जाओ unlock;

	/* reset करोesn't touch the display */
	अगर (!gpu_reset_clobbers_display(dev_priv)) अणु
		/* क्रम testing only restore the display */
		ret = __पूर्णांकel_display_resume(dev, state, ctx);
		अगर (ret)
			drm_err(&dev_priv->drm,
				"Restoring old state failed with %i\n", ret);
	पूर्ण अन्यथा अणु
		/*
		 * The display has been reset as well,
		 * so need a full re-initialization.
		 */
		पूर्णांकel_pps_unlock_regs_wa(dev_priv);
		पूर्णांकel_modeset_init_hw(dev_priv);
		पूर्णांकel_init_घड़ी_gating(dev_priv);
		पूर्णांकel_hpd_init(dev_priv);

		ret = __पूर्णांकel_display_resume(dev, state, ctx);
		अगर (ret)
			drm_err(&dev_priv->drm,
				"Restoring old state failed with %i\n", ret);

		पूर्णांकel_hpd_poll_disable(dev_priv);
	पूर्ण

	drm_atomic_state_put(state);
unlock:
	drm_modeset_drop_locks(ctx);
	drm_modeset_acquire_fini(ctx);
	mutex_unlock(&dev->mode_config.mutex);

	clear_bit_unlock(I915_RESET_MODESET, &dev_priv->gt.reset.flags);
पूर्ण

अटल व्योम icl_set_pipe_chicken(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPE_CHICKEN(pipe));

	/*
	 * Display WA #1153: icl
	 * enable hardware to bypass the alpha math
	 * and rounding क्रम per-pixel values 00 and 0xff
	 */
	पंचांगp |= PER_PIXEL_ALPHA_BYPASS_EN;
	/*
	 * Display WA # 1605353570: icl
	 * Set the pixel rounding bit to 1 क्रम allowing
	 * passthrough of Frame buffer pixels unmodअगरied
	 * across pipe
	 */
	पंचांगp |= PIXEL_ROUNDING_TRUNC_FB_PASSTHRU;
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CHICKEN(pipe), पंचांगp);
पूर्ण

bool पूर्णांकel_has_pending_fb_unpin(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_crtc *crtc;
	bool cleanup_करोne;

	drm_क्रम_each_crtc(crtc, &dev_priv->drm) अणु
		काष्ठा drm_crtc_commit *commit;
		spin_lock(&crtc->commit_lock);
		commit = list_first_entry_or_null(&crtc->commit_list,
						  काष्ठा drm_crtc_commit, commit_entry);
		cleanup_करोne = commit ?
			try_रुको_क्रम_completion(&commit->cleanup_करोne) : true;
		spin_unlock(&crtc->commit_lock);

		अगर (cleanup_करोne)
			जारी;

		drm_crtc_रुको_one_vblank(crtc);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम lpt_disable_iclkip(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 temp;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIXCLK_GATE, PIXCLK_GATE_GATE);

	mutex_lock(&dev_priv->sb_lock);

	temp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCCTL6, SBI_ICLK);
	temp |= SBI_SSCCTL_DISABLE;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCCTL6, temp, SBI_ICLK);

	mutex_unlock(&dev_priv->sb_lock);
पूर्ण

/* Program iCLKIP घड़ी to the desired frequency */
अटल व्योम lpt_program_iclkip(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक घड़ी = crtc_state->hw.adjusted_mode.crtc_घड़ी;
	u32 भागsel, phaseinc, auxभाग, phasedir = 0;
	u32 temp;

	lpt_disable_iclkip(dev_priv);

	/* The iCLK भव घड़ी root frequency is in MHz,
	 * but the adjusted_mode->crtc_घड़ी in in KHz. To get the
	 * भागisors, it is necessary to भागide one by another, so we
	 * convert the भव घड़ी precision to KHz here क्रम higher
	 * precision.
	 */
	क्रम (auxभाग = 0; auxभाग < 2; auxभाग++) अणु
		u32 iclk_भव_root_freq = 172800 * 1000;
		u32 iclk_pi_range = 64;
		u32 desired_भागisor;

		desired_भागisor = DIV_ROUND_CLOSEST(iclk_भव_root_freq,
						    घड़ी << auxभाग);
		भागsel = (desired_भागisor / iclk_pi_range) - 2;
		phaseinc = desired_भागisor % iclk_pi_range;

		/*
		 * Near 20MHz is a corner हाल which is
		 * out of range क्रम the 7-bit भागisor
		 */
		अगर (भागsel <= 0x7f)
			अवरोध;
	पूर्ण

	/* This should not happen with any sane values */
	drm_WARN_ON(&dev_priv->drm, SBI_SSCDIVINTPHASE_DIVSEL(भागsel) &
		    ~SBI_SSCDIVINTPHASE_DIVSEL_MASK);
	drm_WARN_ON(&dev_priv->drm, SBI_SSCDIVINTPHASE_सूची(phasedir) &
		    ~SBI_SSCDIVINTPHASE_INCVAL_MASK);

	drm_dbg_kms(&dev_priv->drm,
		    "iCLKIP clock: found settings for %dKHz refresh rate: auxdiv=%x, divsel=%x, phasedir=%x, phaseinc=%x\n",
		    घड़ी, auxभाग, भागsel, phasedir, phaseinc);

	mutex_lock(&dev_priv->sb_lock);

	/* Program SSCDIVINTPHASE6 */
	temp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCDIVINTPHASE6, SBI_ICLK);
	temp &= ~SBI_SSCDIVINTPHASE_DIVSEL_MASK;
	temp |= SBI_SSCDIVINTPHASE_DIVSEL(भागsel);
	temp &= ~SBI_SSCDIVINTPHASE_INCVAL_MASK;
	temp |= SBI_SSCDIVINTPHASE_INCVAL(phaseinc);
	temp |= SBI_SSCDIVINTPHASE_सूची(phasedir);
	temp |= SBI_SSCDIVINTPHASE_PROPAGATE;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCDIVINTPHASE6, temp, SBI_ICLK);

	/* Program SSCAUXDIV */
	temp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCAUXDIV6, SBI_ICLK);
	temp &= ~SBI_SSCAUXDIV_FINALDIV2SEL(1);
	temp |= SBI_SSCAUXDIV_FINALDIV2SEL(auxभाग);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCAUXDIV6, temp, SBI_ICLK);

	/* Enable modulator and associated भागider */
	temp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCCTL6, SBI_ICLK);
	temp &= ~SBI_SSCCTL_DISABLE;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCCTL6, temp, SBI_ICLK);

	mutex_unlock(&dev_priv->sb_lock);

	/* Wait क्रम initialization समय */
	udelay(24);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIXCLK_GATE, PIXCLK_GATE_UNGATE);
पूर्ण

पूर्णांक lpt_get_iclkip(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 भागsel, phaseinc, auxभाग;
	u32 iclk_भव_root_freq = 172800 * 1000;
	u32 iclk_pi_range = 64;
	u32 desired_भागisor;
	u32 temp;

	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, PIXCLK_GATE) & PIXCLK_GATE_UNGATE) == 0)
		वापस 0;

	mutex_lock(&dev_priv->sb_lock);

	temp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCCTL6, SBI_ICLK);
	अगर (temp & SBI_SSCCTL_DISABLE) अणु
		mutex_unlock(&dev_priv->sb_lock);
		वापस 0;
	पूर्ण

	temp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCDIVINTPHASE6, SBI_ICLK);
	भागsel = (temp & SBI_SSCDIVINTPHASE_DIVSEL_MASK) >>
		SBI_SSCDIVINTPHASE_DIVSEL_SHIFT;
	phaseinc = (temp & SBI_SSCDIVINTPHASE_INCVAL_MASK) >>
		SBI_SSCDIVINTPHASE_INCVAL_SHIFT;

	temp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCAUXDIV6, SBI_ICLK);
	auxभाग = (temp & SBI_SSCAUXDIV_FINALDIV2SEL_MASK) >>
		SBI_SSCAUXDIV_FINALDIV2SEL_SHIFT;

	mutex_unlock(&dev_priv->sb_lock);

	desired_भागisor = (भागsel + 2) * iclk_pi_range + phaseinc;

	वापस DIV_ROUND_CLOSEST(iclk_भव_root_freq,
				 desired_भागisor << auxभाग);
पूर्ण

अटल व्योम ilk_pch_transcoder_set_timings(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					   क्रमागत pipe pch_transcoder)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_HTOTAL(pch_transcoder),
		       पूर्णांकel_de_पढ़ो(dev_priv, HTOTAL(cpu_transcoder)));
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_HBLANK(pch_transcoder),
		       पूर्णांकel_de_पढ़ो(dev_priv, HBLANK(cpu_transcoder)));
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_HSYNC(pch_transcoder),
		       पूर्णांकel_de_पढ़ो(dev_priv, HSYNC(cpu_transcoder)));

	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_VTOTAL(pch_transcoder),
		       पूर्णांकel_de_पढ़ो(dev_priv, VTOTAL(cpu_transcoder)));
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_VBLANK(pch_transcoder),
		       पूर्णांकel_de_पढ़ो(dev_priv, VBLANK(cpu_transcoder)));
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_VSYNC(pch_transcoder),
		       पूर्णांकel_de_पढ़ो(dev_priv, VSYNC(cpu_transcoder)));
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_VSYNCSHIFT(pch_transcoder),
		       पूर्णांकel_de_पढ़ो(dev_priv, VSYNCSHIFT(cpu_transcoder)));
पूर्ण

अटल व्योम cpt_set_fdi_bc_bअगरurcation(काष्ठा drm_i915_निजी *dev_priv, bool enable)
अणु
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN1);
	अगर (!!(temp & FDI_BC_BIFURCATION_SELECT) == enable)
		वापस;

	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_B)) &
		    FDI_RX_ENABLE);
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_C)) &
		    FDI_RX_ENABLE);

	temp &= ~FDI_BC_BIFURCATION_SELECT;
	अगर (enable)
		temp |= FDI_BC_BIFURCATION_SELECT;

	drm_dbg_kms(&dev_priv->drm, "%sabling fdi C rx\n",
		    enable ? "en" : "dis");
	पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_CHICKEN1, temp);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, SOUTH_CHICKEN1);
पूर्ण

अटल व्योम ivb_update_fdi_bc_bअगरurcation(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	चयन (crtc->pipe) अणु
	हाल PIPE_A:
		अवरोध;
	हाल PIPE_B:
		अगर (crtc_state->fdi_lanes > 2)
			cpt_set_fdi_bc_bअगरurcation(dev_priv, false);
		अन्यथा
			cpt_set_fdi_bc_bअगरurcation(dev_priv, true);

		अवरोध;
	हाल PIPE_C:
		cpt_set_fdi_bc_bअगरurcation(dev_priv, true);

		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

/*
 * Finds the encoder associated with the given CRTC. This can only be
 * used when we know that the CRTC isn't feeding multiple encoders!
 */
काष्ठा पूर्णांकel_encoder *
पूर्णांकel_get_crtc_new_encoder(स्थिर काष्ठा पूर्णांकel_atomic_state *state,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_connector_state *connector_state;
	स्थिर काष्ठा drm_connector *connector;
	काष्ठा पूर्णांकel_encoder *encoder = शून्य;
	पूर्णांक num_encoders = 0;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, connector, connector_state, i) अणु
		अगर (connector_state->crtc != &crtc->base)
			जारी;

		encoder = to_पूर्णांकel_encoder(connector_state->best_encoder);
		num_encoders++;
	पूर्ण

	drm_WARN(encoder->base.dev, num_encoders != 1,
		 "%d encoders for pipe %c\n",
		 num_encoders, pipe_name(crtc->pipe));

	वापस encoder;
पूर्ण

/*
 * Enable PCH resources required क्रम PCH ports:
 *   - PCH PLLs
 *   - FDI training & RX/TX
 *   - update transcoder timings
 *   - DP transcoding bits
 *   - transcoder
 */
अटल व्योम ilk_pch_enable(स्थिर काष्ठा पूर्णांकel_atomic_state *state,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 temp;

	निश्चित_pch_transcoder_disabled(dev_priv, pipe);

	अगर (IS_IVYBRIDGE(dev_priv))
		ivb_update_fdi_bc_bअगरurcation(crtc_state);

	/* Write the TU size bits beक्रमe fdi link training, so that error
	 * detection works. */
	पूर्णांकel_de_ग_लिखो(dev_priv, FDI_RX_TUSIZE1(pipe),
		       पूर्णांकel_de_पढ़ो(dev_priv, PIPE_DATA_M1(pipe)) & TU_SIZE_MASK);

	/* For PCH output, training FDI link */
	dev_priv->display.fdi_link_train(crtc, crtc_state);

	/* We need to program the right घड़ी selection beक्रमe writing the pixel
	 * mutliplier पूर्णांकo the DPLL. */
	अगर (HAS_PCH_CPT(dev_priv)) अणु
		u32 sel;

		temp = पूर्णांकel_de_पढ़ो(dev_priv, PCH_DPLL_SEL);
		temp |= TRANS_DPLL_ENABLE(pipe);
		sel = TRANS_DPLLB_SEL(pipe);
		अगर (crtc_state->shared_dpll ==
		    पूर्णांकel_get_shared_dpll_by_id(dev_priv, DPLL_ID_PCH_PLL_B))
			temp |= sel;
		अन्यथा
			temp &= ~sel;
		पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DPLL_SEL, temp);
	पूर्ण

	/* XXX: pch pll's can be enabled any समय beक्रमe we enable the PCH
	 * transcoder, and we actually should करो this to not upset any PCH
	 * transcoder that alपढ़ोy use the घड़ी when we share it.
	 *
	 * Note that enable_shared_dpll tries to करो the right thing, but
	 * get_shared_dpll unconditionally resets the pll - we need that to have
	 * the right LVDS enable sequence. */
	पूर्णांकel_enable_shared_dpll(crtc_state);

	/* set transcoder timing, panel must allow it */
	निश्चित_panel_unlocked(dev_priv, pipe);
	ilk_pch_transcoder_set_timings(crtc_state, pipe);

	पूर्णांकel_fdi_normal_train(crtc);

	/* For PCH DP, enable TRANS_DP_CTL */
	अगर (HAS_PCH_CPT(dev_priv) &&
	    पूर्णांकel_crtc_has_dp_encoder(crtc_state)) अणु
		स्थिर काष्ठा drm_display_mode *adjusted_mode =
			&crtc_state->hw.adjusted_mode;
		u32 bpc = (पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe)) & PIPECONF_BPC_MASK) >> 5;
		i915_reg_t reg = TRANS_DP_CTL(pipe);
		क्रमागत port port;

		temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		temp &= ~(TRANS_DP_PORT_SEL_MASK |
			  TRANS_DP_SYNC_MASK |
			  TRANS_DP_BPC_MASK);
		temp |= TRANS_DP_OUTPUT_ENABLE;
		temp |= bpc << 9; /* same क्रमmat but at 11:9 */

		अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
			temp |= TRANS_DP_HSYNC_ACTIVE_HIGH;
		अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
			temp |= TRANS_DP_VSYNC_ACTIVE_HIGH;

		port = पूर्णांकel_get_crtc_new_encoder(state, crtc_state)->port;
		drm_WARN_ON(dev, port < PORT_B || port > PORT_D);
		temp |= TRANS_DP_PORT_SEL(port);

		पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);
	पूर्ण

	ilk_enable_pch_transcoder(crtc_state);
पूर्ण

व्योम lpt_pch_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	निश्चित_pch_transcoder_disabled(dev_priv, PIPE_A);

	lpt_program_iclkip(crtc_state);

	/* Set transcoder timing. */
	ilk_pch_transcoder_set_timings(crtc_state, PIPE_A);

	lpt_enable_pch_transcoder(dev_priv, cpu_transcoder);
पूर्ण

अटल व्योम cpt_verअगरy_modeset(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत pipe pipe)
अणु
	i915_reg_t dslreg = PIPEDSL(pipe);
	u32 temp;

	temp = पूर्णांकel_de_पढ़ो(dev_priv, dslreg);
	udelay(500);
	अगर (रुको_क्रम(पूर्णांकel_de_पढ़ो(dev_priv, dslreg) != temp, 5)) अणु
		अगर (रुको_क्रम(पूर्णांकel_de_पढ़ो(dev_priv, dslreg) != temp, 5))
			drm_err(&dev_priv->drm,
				"mode set failed: pipe %c stuck\n",
				pipe_name(pipe));
	पूर्ण
पूर्ण

अटल व्योम ilk_pfit_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_rect *dst = &crtc_state->pch_pfit.dst;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक width = drm_rect_width(dst);
	पूर्णांक height = drm_rect_height(dst);
	पूर्णांक x = dst->x1;
	पूर्णांक y = dst->y1;

	अगर (!crtc_state->pch_pfit.enabled)
		वापस;

	/* Force use of hard-coded filter coefficients
	 * as some pre-programmed values are broken,
	 * e.g. x201.
	 */
	अगर (IS_IVYBRIDGE(dev_priv) || IS_HASWELL(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, PF_CTL(pipe), PF_ENABLE |
			       PF_FILTER_MED_3x3 | PF_PIPE_SEL_IVB(pipe));
	अन्यथा
		पूर्णांकel_de_ग_लिखो(dev_priv, PF_CTL(pipe), PF_ENABLE |
			       PF_FILTER_MED_3x3);
	पूर्णांकel_de_ग_लिखो(dev_priv, PF_WIN_POS(pipe), x << 16 | y);
	पूर्णांकel_de_ग_लिखो(dev_priv, PF_WIN_SZ(pipe), width << 16 | height);
पूर्ण

व्योम hsw_enable_ips(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	अगर (!crtc_state->ips_enabled)
		वापस;

	/*
	 * We can only enable IPS after we enable a plane and रुको क्रम a vblank
	 * This function is called from post_plane_update, which is run after
	 * a vblank रुको.
	 */
	drm_WARN_ON(dev, !(crtc_state->active_planes & ~BIT(PLANE_CURSOR)));

	अगर (IS_BROADWELL(dev_priv)) अणु
		drm_WARN_ON(dev, sandybridge_pcode_ग_लिखो(dev_priv, DISPLAY_IPS_CONTROL,
							 IPS_ENABLE | IPS_PCODE_CONTROL));
		/* Quoting Art Runyan: "its not safe to expect any particular
		 * value in IPS_CTL bit 31 after enabling IPS through the
		 * mailbox." Moreover, the mailbox may वापस a bogus state,
		 * so we need to just enable it and जारी on.
		 */
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, IPS_CTL, IPS_ENABLE);
		/* The bit only becomes 1 in the next vblank, so this रुको here
		 * is essentially पूर्णांकel_रुको_क्रम_vblank. If we करोn't have this
		 * and करोn't रुको क्रम vblanks until the end of crtc_enable, then
		 * the HW state पढ़ोout code will complain that the expected
		 * IPS_CTL value is not the one we पढ़ो. */
		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, IPS_CTL, IPS_ENABLE, 50))
			drm_err(&dev_priv->drm,
				"Timed out waiting for IPS enable\n");
	पूर्ण
पूर्ण

व्योम hsw_disable_ips(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	अगर (!crtc_state->ips_enabled)
		वापस;

	अगर (IS_BROADWELL(dev_priv)) अणु
		drm_WARN_ON(dev,
			    sandybridge_pcode_ग_लिखो(dev_priv, DISPLAY_IPS_CONTROL, 0));
		/*
		 * Wait क्रम PCODE to finish disabling IPS. The BSpec specअगरied
		 * 42ms समयout value leads to occasional समयouts so use 100ms
		 * instead.
		 */
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, IPS_CTL, IPS_ENABLE, 100))
			drm_err(&dev_priv->drm,
				"Timed out waiting for IPS disable\n");
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, IPS_CTL, 0);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, IPS_CTL);
	पूर्ण

	/* We need to रुको क्रम a vblank beक्रमe we can disable the plane. */
	पूर्णांकel_रुको_क्रम_vblank(dev_priv, crtc->pipe);
पूर्ण

अटल व्योम पूर्णांकel_crtc_dpms_overlay_disable(काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc)
अणु
	अगर (पूर्णांकel_crtc->overlay)
		(व्योम) पूर्णांकel_overlay_चयन_off(पूर्णांकel_crtc->overlay);

	/* Let userspace चयन the overlay on again. In most हालs userspace
	 * has to recompute where to put it anyway.
	 */
पूर्ण

अटल bool hsw_pre_update_disable_ips(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				       स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (!old_crtc_state->ips_enabled)
		वापस false;

	अगर (पूर्णांकel_crtc_needs_modeset(new_crtc_state))
		वापस true;

	/*
	 * Workaround : Do not पढ़ो or ग_लिखो the pipe palette/gamma data जबतक
	 * GAMMA_MODE is configured क्रम split gamma and IPS_CTL has IPS enabled.
	 *
	 * Disable IPS beक्रमe we program the LUT.
	 */
	अगर (IS_HASWELL(dev_priv) &&
	    (new_crtc_state->uapi.color_mgmt_changed ||
	     new_crtc_state->update_pipe) &&
	    new_crtc_state->gamma_mode == GAMMA_MODE_MODE_SPLIT)
		वापस true;

	वापस !new_crtc_state->ips_enabled;
पूर्ण

अटल bool hsw_post_update_enable_ips(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				       स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (!new_crtc_state->ips_enabled)
		वापस false;

	अगर (पूर्णांकel_crtc_needs_modeset(new_crtc_state))
		वापस true;

	/*
	 * Workaround : Do not पढ़ो or ग_लिखो the pipe palette/gamma data जबतक
	 * GAMMA_MODE is configured क्रम split gamma and IPS_CTL has IPS enabled.
	 *
	 * Re-enable IPS after the LUT has been programmed.
	 */
	अगर (IS_HASWELL(dev_priv) &&
	    (new_crtc_state->uapi.color_mgmt_changed ||
	     new_crtc_state->update_pipe) &&
	    new_crtc_state->gamma_mode == GAMMA_MODE_MODE_SPLIT)
		वापस true;

	/*
	 * We can't पढ़ो out IPS on broadwell, assume the worst and
	 * क्रमcibly enable IPS on the first fastset.
	 */
	अगर (new_crtc_state->update_pipe && old_crtc_state->inherited)
		वापस true;

	वापस !old_crtc_state->ips_enabled;
पूर्ण

अटल bool needs_nv12_wa(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	अगर (!crtc_state->nv12_planes)
		वापस false;

	/* WA Display #0827: Gen9:all */
	अगर (IS_DISPLAY_VER(dev_priv, 9))
		वापस true;

	वापस false;
पूर्ण

अटल bool needs_scalerclk_wa(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	/* Wa_2006604312:icl,ehl */
	अगर (crtc_state->scaler_state.scaler_users > 0 && IS_DISPLAY_VER(dev_priv, 11))
		वापस true;

	वापस false;
पूर्ण

अटल bool planes_enabling(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	वापस (!old_crtc_state->active_planes || पूर्णांकel_crtc_needs_modeset(new_crtc_state)) &&
		new_crtc_state->active_planes;
पूर्ण

अटल bool planes_disabling(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	वापस old_crtc_state->active_planes &&
		(!new_crtc_state->active_planes || पूर्णांकel_crtc_needs_modeset(new_crtc_state));
पूर्ण

अटल व्योम पूर्णांकel_post_plane_update(काष्ठा पूर्णांकel_atomic_state *state,
				    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	क्रमागत pipe pipe = crtc->pipe;

	पूर्णांकel_frontbuffer_flip(dev_priv, new_crtc_state->fb_bits);

	अगर (new_crtc_state->update_wm_post && new_crtc_state->hw.active)
		पूर्णांकel_update_watermarks(crtc);

	अगर (hsw_post_update_enable_ips(old_crtc_state, new_crtc_state))
		hsw_enable_ips(new_crtc_state);

	पूर्णांकel_fbc_post_update(state, crtc);

	अगर (needs_nv12_wa(old_crtc_state) &&
	    !needs_nv12_wa(new_crtc_state))
		skl_wa_827(dev_priv, pipe, false);

	अगर (needs_scalerclk_wa(old_crtc_state) &&
	    !needs_scalerclk_wa(new_crtc_state))
		icl_wa_scalerclkgating(dev_priv, pipe, false);
पूर्ण

अटल व्योम पूर्णांकel_crtc_enable_flip_करोne(काष्ठा पूर्णांकel_atomic_state *state,
					काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	u8 update_planes = crtc_state->update_planes;
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane->enable_flip_करोne &&
		    plane->pipe == crtc->pipe &&
		    update_planes & BIT(plane->id))
			plane->enable_flip_करोne(plane);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_crtc_disable_flip_करोne(काष्ठा पूर्णांकel_atomic_state *state,
					 काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	u8 update_planes = crtc_state->update_planes;
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane->disable_flip_करोne &&
		    plane->pipe == crtc->pipe &&
		    update_planes & BIT(plane->id))
			plane->disable_flip_करोne(plane);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_crtc_async_flip_disable_wa(काष्ठा पूर्णांकel_atomic_state *state,
					     काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	u8 update_planes = new_crtc_state->update_planes;
	स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	bool need_vbl_रुको = false;
	पूर्णांक i;

	क्रम_each_old_पूर्णांकel_plane_in_state(state, plane, old_plane_state, i) अणु
		अगर (plane->need_async_flip_disable_wa &&
		    plane->pipe == crtc->pipe &&
		    update_planes & BIT(plane->id)) अणु
			/*
			 * Apart from the async flip bit we want to
			 * preserve the old state क्रम the plane.
			 */
			plane->async_flip(plane, old_crtc_state,
					  old_plane_state, false);
			need_vbl_रुको = true;
		पूर्ण
	पूर्ण

	अगर (need_vbl_रुको)
		पूर्णांकel_रुको_क्रम_vblank(i915, crtc->pipe);
पूर्ण

अटल व्योम पूर्णांकel_pre_plane_update(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	क्रमागत pipe pipe = crtc->pipe;

	अगर (hsw_pre_update_disable_ips(old_crtc_state, new_crtc_state))
		hsw_disable_ips(old_crtc_state);

	अगर (पूर्णांकel_fbc_pre_update(state, crtc))
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);

	/* Display WA 827 */
	अगर (!needs_nv12_wa(old_crtc_state) &&
	    needs_nv12_wa(new_crtc_state))
		skl_wa_827(dev_priv, pipe, true);

	/* Wa_2006604312:icl,ehl */
	अगर (!needs_scalerclk_wa(old_crtc_state) &&
	    needs_scalerclk_wa(new_crtc_state))
		icl_wa_scalerclkgating(dev_priv, pipe, true);

	/*
	 * Vblank समय updates from the shaकरोw to live plane control रेजिस्टर
	 * are blocked अगर the memory self-refresh mode is active at that
	 * moment. So to make sure the plane माला_लो truly disabled, disable
	 * first the self-refresh mode. The self-refresh enable bit in turn
	 * will be checked/applied by the HW only at the next frame start
	 * event which is after the vblank start event, so we need to have a
	 * रुको-क्रम-vblank between disabling the plane and the pipe.
	 */
	अगर (HAS_GMCH(dev_priv) && old_crtc_state->hw.active &&
	    new_crtc_state->disable_cxsr && पूर्णांकel_set_memory_cxsr(dev_priv, false))
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);

	/*
	 * IVB workaround: must disable low घातer watermarks क्रम at least
	 * one frame beक्रमe enabling scaling.  LP watermarks can be re-enabled
	 * when scaling is disabled.
	 *
	 * WaCxSRDisabledForSpriteScaling:ivb
	 */
	अगर (old_crtc_state->hw.active &&
	    new_crtc_state->disable_lp_wm && ilk_disable_lp_wm(dev_priv))
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);

	/*
	 * If we're doing a modeset we don't need to करो any
	 * pre-vblank watermark programming here.
	 */
	अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state)) अणु
		/*
		 * For platक्रमms that support atomic watermarks, program the
		 * 'intermediate' watermarks immediately.  On pre-gen9 platक्रमms, these
		 * will be the पूर्णांकermediate values that are safe क्रम both pre- and
		 * post- vblank; when vblank happens, the 'active' values will be set
		 * to the final 'target' values and we'll करो this again to get the
		 * optimal watermarks.  For gen9+ platक्रमms, the values we program here
		 * will be the final target values which will get स्वतःmatically latched
		 * at vblank समय; no further programming will be necessary.
		 *
		 * If a platक्रमm hasn't been transitioned to atomic watermarks yet,
		 * we'll जारी to update watermarks the old way, अगर flags tell
		 * us to.
		 */
		अगर (dev_priv->display.initial_watermarks)
			dev_priv->display.initial_watermarks(state, crtc);
		अन्यथा अगर (new_crtc_state->update_wm_pre)
			पूर्णांकel_update_watermarks(crtc);
	पूर्ण

	/*
	 * Gen2 reports pipe underruns whenever all planes are disabled.
	 * So disable underrun reporting beक्रमe all the planes get disabled.
	 *
	 * We करो this after .initial_watermarks() so that we have a
	 * chance of catching underruns with the पूर्णांकermediate watermarks
	 * vs. the old plane configuration.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 2) && planes_disabling(old_crtc_state, new_crtc_state))
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, false);

	/*
	 * WA क्रम platक्रमms where async address update enable bit
	 * is द्विगुन buffered and only latched at start of vblank.
	 */
	अगर (old_crtc_state->uapi.async_flip && !new_crtc_state->uapi.async_flip)
		पूर्णांकel_crtc_async_flip_disable_wa(state, crtc);
पूर्ण

अटल व्योम पूर्णांकel_crtc_disable_planes(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	अचिन्हित पूर्णांक update_mask = new_crtc_state->update_planes;
	स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	अचिन्हित fb_bits = 0;
	पूर्णांक i;

	पूर्णांकel_crtc_dpms_overlay_disable(crtc);

	क्रम_each_old_पूर्णांकel_plane_in_state(state, plane, old_plane_state, i) अणु
		अगर (crtc->pipe != plane->pipe ||
		    !(update_mask & BIT(plane->id)))
			जारी;

		पूर्णांकel_disable_plane(plane, new_crtc_state);

		अगर (old_plane_state->uapi.visible)
			fb_bits |= plane->frontbuffer_bit;
	पूर्ण

	पूर्णांकel_frontbuffer_flip(dev_priv, fb_bits);
पूर्ण

/*
 * पूर्णांकel_connector_primary_encoder - get the primary encoder क्रम a connector
 * @connector: connector क्रम which to वापस the encoder
 *
 * Returns the primary encoder क्रम a connector. There is a 1:1 mapping from
 * all connectors to their encoder, except क्रम DP-MST connectors which have
 * both a भव and a primary encoder. These DP-MST primary encoders can be
 * poपूर्णांकed to by as many DP-MST connectors as there are pipes.
 */
अटल काष्ठा पूर्णांकel_encoder *
पूर्णांकel_connector_primary_encoder(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	अगर (connector->mst_port)
		वापस &dp_to_dig_port(connector->mst_port)->base;

	encoder = पूर्णांकel_attached_encoder(connector);
	drm_WARN_ON(connector->base.dev, !encoder);

	वापस encoder;
पूर्ण

अटल व्योम पूर्णांकel_encoders_update_prepare(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_conn_state;
	काष्ठा drm_connector *connector;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, connector, new_conn_state,
					i) अणु
		काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
		काष्ठा पूर्णांकel_encoder *encoder;
		काष्ठा पूर्णांकel_crtc *crtc;

		अगर (!पूर्णांकel_connector_needs_modeset(state, connector))
			जारी;

		पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
		encoder = पूर्णांकel_connector_primary_encoder(पूर्णांकel_connector);
		अगर (!encoder->update_prepare)
			जारी;

		crtc = new_conn_state->crtc ?
			to_पूर्णांकel_crtc(new_conn_state->crtc) : शून्य;
		encoder->update_prepare(state, encoder, crtc);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_update_complete(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_connector_state *new_conn_state;
	काष्ठा drm_connector *connector;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, connector, new_conn_state,
					i) अणु
		काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
		काष्ठा पूर्णांकel_encoder *encoder;
		काष्ठा पूर्णांकel_crtc *crtc;

		अगर (!पूर्णांकel_connector_needs_modeset(state, connector))
			जारी;

		पूर्णांकel_connector = to_पूर्णांकel_connector(connector);
		encoder = पूर्णांकel_connector_primary_encoder(पूर्णांकel_connector);
		अगर (!encoder->update_complete)
			जारी;

		crtc = new_conn_state->crtc ?
			to_पूर्णांकel_crtc(new_conn_state->crtc) : शून्य;
		encoder->update_complete(state, encoder, crtc);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_pre_pll_enable(काष्ठा पूर्णांकel_atomic_state *state,
					  काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, conn, conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(conn_state->best_encoder);

		अगर (conn_state->crtc != &crtc->base)
			जारी;

		अगर (encoder->pre_pll_enable)
			encoder->pre_pll_enable(state, encoder,
						crtc_state, conn_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, conn, conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(conn_state->best_encoder);

		अगर (conn_state->crtc != &crtc->base)
			जारी;

		अगर (encoder->pre_enable)
			encoder->pre_enable(state, encoder,
					    crtc_state, conn_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_enable(काष्ठा पूर्णांकel_atomic_state *state,
				  काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, conn, conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(conn_state->best_encoder);

		अगर (conn_state->crtc != &crtc->base)
			जारी;

		अगर (encoder->enable)
			encoder->enable(state, encoder,
					crtc_state, conn_state);
		पूर्णांकel_opregion_notअगरy_encoder(encoder, true);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_disable(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा drm_connector_state *old_conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	क्रम_each_old_connector_in_state(&state->base, conn, old_conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(old_conn_state->best_encoder);

		अगर (old_conn_state->crtc != &crtc->base)
			जारी;

		पूर्णांकel_opregion_notअगरy_encoder(encoder, false);
		अगर (encoder->disable)
			encoder->disable(state, encoder,
					 old_crtc_state, old_conn_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
					काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा drm_connector_state *old_conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	क्रम_each_old_connector_in_state(&state->base, conn, old_conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(old_conn_state->best_encoder);

		अगर (old_conn_state->crtc != &crtc->base)
			जारी;

		अगर (encoder->post_disable)
			encoder->post_disable(state, encoder,
					      old_crtc_state, old_conn_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_post_pll_disable(काष्ठा पूर्णांकel_atomic_state *state,
					    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा drm_connector_state *old_conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	क्रम_each_old_connector_in_state(&state->base, conn, old_conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(old_conn_state->best_encoder);

		अगर (old_conn_state->crtc != &crtc->base)
			जारी;

		अगर (encoder->post_pll_disable)
			encoder->post_pll_disable(state, encoder,
						  old_crtc_state, old_conn_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_encoders_update_pipe(काष्ठा पूर्णांकel_atomic_state *state,
				       काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, conn, conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(conn_state->best_encoder);

		अगर (conn_state->crtc != &crtc->base)
			जारी;

		अगर (encoder->update_pipe)
			encoder->update_pipe(state, encoder,
					     crtc_state, conn_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_disable_primary_plane(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);

	plane->disable_plane(plane, crtc_state);
पूर्ण

अटल व्योम ilk_crtc_enable(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	अगर (drm_WARN_ON(&dev_priv->drm, crtc->active))
		वापस;

	/*
	 * Someबार spurious CPU pipe underruns happen during FDI
	 * training, at least with VGA+HDMI cloning. Suppress them.
	 *
	 * On ILK we get an occasional spurious CPU pipe underruns
	 * between eDP port A enable and vdd enable. Also PCH port
	 * enable seems to result in the occasional CPU pipe underrun.
	 *
	 * Spurious PCH underruns also occur during PCH enabling.
	 */
	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, false);
	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, pipe, false);

	अगर (new_crtc_state->has_pch_encoder)
		पूर्णांकel_prepare_shared_dpll(new_crtc_state);

	अगर (पूर्णांकel_crtc_has_dp_encoder(new_crtc_state))
		पूर्णांकel_dp_set_m_n(new_crtc_state, M1_N1);

	पूर्णांकel_set_transcoder_timings(new_crtc_state);
	पूर्णांकel_set_pipe_src_size(new_crtc_state);

	अगर (new_crtc_state->has_pch_encoder)
		पूर्णांकel_cpu_transcoder_set_m_n(new_crtc_state,
					     &new_crtc_state->fdi_m_n, शून्य);

	ilk_set_pipeconf(new_crtc_state);

	crtc->active = true;

	पूर्णांकel_encoders_pre_enable(state, crtc);

	अगर (new_crtc_state->has_pch_encoder) अणु
		/* Note: FDI PLL enabling _must_ be करोne beक्रमe we enable the
		 * cpu pipes, hence this is separate from all the other fdi/pch
		 * enabling. */
		ilk_fdi_pll_enable(new_crtc_state);
	पूर्ण अन्यथा अणु
		निश्चित_fdi_tx_disabled(dev_priv, pipe);
		निश्चित_fdi_rx_disabled(dev_priv, pipe);
	पूर्ण

	ilk_pfit_enable(new_crtc_state);

	/*
	 * On ILK+ LUT must be loaded beक्रमe the pipe is running but with
	 * घड़ीs enabled
	 */
	पूर्णांकel_color_load_luts(new_crtc_state);
	पूर्णांकel_color_commit(new_crtc_state);
	/* update DSPCNTR to configure gamma क्रम pipe bottom color */
	पूर्णांकel_disable_primary_plane(new_crtc_state);

	अगर (dev_priv->display.initial_watermarks)
		dev_priv->display.initial_watermarks(state, crtc);
	पूर्णांकel_enable_pipe(new_crtc_state);

	अगर (new_crtc_state->has_pch_encoder)
		ilk_pch_enable(state, new_crtc_state);

	पूर्णांकel_crtc_vblank_on(new_crtc_state);

	पूर्णांकel_encoders_enable(state, crtc);

	अगर (HAS_PCH_CPT(dev_priv))
		cpt_verअगरy_modeset(dev_priv, pipe);

	/*
	 * Must रुको क्रम vblank to aव्योम spurious PCH FIFO underruns.
	 * And a second vblank रुको is needed at least on ILK with
	 * some पूर्णांकerlaced HDMI modes. Let's करो the द्विगुन रुको always
	 * in हाल there are more corner हालs we करोn't know about.
	 */
	अगर (new_crtc_state->has_pch_encoder) अणु
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
	पूर्ण
	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, true);
	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, pipe, true);
पूर्ण

/* IPS only exists on ULT machines and is tied to pipe A. */
अटल bool hsw_crtc_supports_ips(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	वापस HAS_IPS(to_i915(crtc->base.dev)) && crtc->pipe == PIPE_A;
पूर्ण

अटल व्योम glk_pipe_scaler_घड़ी_gating_wa(काष्ठा drm_i915_निजी *dev_priv,
					    क्रमागत pipe pipe, bool apply)
अणु
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, CLKGATE_DIS_PSL(pipe));
	u32 mask = DPF_GATING_DIS | DPF_RAM_GATING_DIS | DPFR_GATING_DIS;

	अगर (apply)
		val |= mask;
	अन्यथा
		val &= ~mask;

	पूर्णांकel_de_ग_लिखो(dev_priv, CLKGATE_DIS_PSL(pipe), val);
पूर्ण

अटल व्योम icl_pipe_mbus_enable(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val;

	val = MBUS_DBOX_A_CREDIT(2);

	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		val |= MBUS_DBOX_BW_CREDIT(2);
		val |= MBUS_DBOX_B_CREDIT(12);
	पूर्ण अन्यथा अणु
		val |= MBUS_DBOX_BW_CREDIT(1);
		val |= MBUS_DBOX_B_CREDIT(8);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_MBUS_DBOX_CTL(pipe), val);
पूर्ण

अटल व्योम hsw_set_lineसमय_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	पूर्णांकel_de_ग_लिखो(dev_priv, WM_LINETIME(crtc->pipe),
		       HSW_LINETIME(crtc_state->lineसमय) |
		       HSW_IPS_LINETIME(crtc_state->ips_lineसमय));
पूर्ण

अटल व्योम hsw_set_frame_start_delay(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	i915_reg_t reg = CHICKEN_TRANS(crtc_state->cpu_transcoder);
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
	val &= ~HSW_FRAME_START_DELAY_MASK;
	val |= HSW_FRAME_START_DELAY(dev_priv->framestart_delay - 1);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
पूर्ण

अटल व्योम icl_ddi_bigjoiner_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
					 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *master = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_crtc_state *master_crtc_state;
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *conn;
	काष्ठा पूर्णांकel_encoder *encoder = शून्य;
	पूर्णांक i;

	अगर (crtc_state->bigjoiner_slave)
		master = crtc_state->bigjoiner_linked_crtc;

	master_crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, master);

	क्रम_each_new_connector_in_state(&state->base, conn, conn_state, i) अणु
		अगर (conn_state->crtc != &master->base)
			जारी;

		encoder = to_पूर्णांकel_encoder(conn_state->best_encoder);
		अवरोध;
	पूर्ण

	अगर (!crtc_state->bigjoiner_slave) अणु
		/* need to enable VDSC, which we skipped in pre-enable */
		पूर्णांकel_dsc_enable(encoder, crtc_state);
	पूर्ण अन्यथा अणु
		/*
		 * Enable sequence steps 1-7 on bigjoiner master
		 */
		पूर्णांकel_encoders_pre_pll_enable(state, master);
		पूर्णांकel_enable_shared_dpll(master_crtc_state);
		पूर्णांकel_encoders_pre_enable(state, master);

		/* and DSC on slave */
		पूर्णांकel_dsc_enable(शून्य, crtc_state);
	पूर्ण
पूर्ण

अटल व्योम hsw_crtc_enable(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe, hsw_workaround_pipe;
	क्रमागत transcoder cpu_transcoder = new_crtc_state->cpu_transcoder;
	bool psl_clkgate_wa;

	अगर (drm_WARN_ON(&dev_priv->drm, crtc->active))
		वापस;

	अगर (!new_crtc_state->bigjoiner) अणु
		पूर्णांकel_encoders_pre_pll_enable(state, crtc);

		अगर (new_crtc_state->shared_dpll)
			पूर्णांकel_enable_shared_dpll(new_crtc_state);

		पूर्णांकel_encoders_pre_enable(state, crtc);
	पूर्ण अन्यथा अणु
		icl_ddi_bigjoiner_pre_enable(state, new_crtc_state);
	पूर्ण

	पूर्णांकel_set_pipe_src_size(new_crtc_state);
	अगर (DISPLAY_VER(dev_priv) >= 9 || IS_BROADWELL(dev_priv))
		bdw_set_pipemisc(new_crtc_state);

	अगर (!new_crtc_state->bigjoiner_slave && !transcoder_is_dsi(cpu_transcoder)) अणु
		पूर्णांकel_set_transcoder_timings(new_crtc_state);

		अगर (cpu_transcoder != TRANSCODER_EDP)
			पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_MULT(cpu_transcoder),
				       new_crtc_state->pixel_multiplier - 1);

		अगर (new_crtc_state->has_pch_encoder)
			पूर्णांकel_cpu_transcoder_set_m_n(new_crtc_state,
						     &new_crtc_state->fdi_m_n, शून्य);

		hsw_set_frame_start_delay(new_crtc_state);
	पूर्ण

	अगर (!transcoder_is_dsi(cpu_transcoder))
		hsw_set_pipeconf(new_crtc_state);

	crtc->active = true;

	/* Display WA #1180: WaDisableScalarClockGating: glk, cnl */
	psl_clkgate_wa = IS_DISPLAY_VER(dev_priv, 10) &&
		new_crtc_state->pch_pfit.enabled;
	अगर (psl_clkgate_wa)
		glk_pipe_scaler_घड़ी_gating_wa(dev_priv, pipe, true);

	अगर (DISPLAY_VER(dev_priv) >= 9)
		skl_pfit_enable(new_crtc_state);
	अन्यथा
		ilk_pfit_enable(new_crtc_state);

	/*
	 * On ILK+ LUT must be loaded beक्रमe the pipe is running but with
	 * घड़ीs enabled
	 */
	पूर्णांकel_color_load_luts(new_crtc_state);
	पूर्णांकel_color_commit(new_crtc_state);
	/* update DSPCNTR to configure gamma/csc क्रम pipe bottom color */
	अगर (DISPLAY_VER(dev_priv) < 9)
		पूर्णांकel_disable_primary_plane(new_crtc_state);

	hsw_set_lineसमय_wm(new_crtc_state);

	अगर (DISPLAY_VER(dev_priv) >= 11)
		icl_set_pipe_chicken(crtc);

	अगर (dev_priv->display.initial_watermarks)
		dev_priv->display.initial_watermarks(state, crtc);

	अगर (DISPLAY_VER(dev_priv) >= 11)
		icl_pipe_mbus_enable(crtc);

	अगर (new_crtc_state->bigjoiner_slave)
		पूर्णांकel_crtc_vblank_on(new_crtc_state);

	पूर्णांकel_encoders_enable(state, crtc);

	अगर (psl_clkgate_wa) अणु
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
		glk_pipe_scaler_घड़ी_gating_wa(dev_priv, pipe, false);
	पूर्ण

	/* If we change the relative order between pipe/planes enabling, we need
	 * to change the workaround. */
	hsw_workaround_pipe = new_crtc_state->hsw_workaround_pipe;
	अगर (IS_HASWELL(dev_priv) && hsw_workaround_pipe != INVALID_PIPE) अणु
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, hsw_workaround_pipe);
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, hsw_workaround_pipe);
	पूर्ण
पूर्ण

व्योम ilk_pfit_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/* To aव्योम upsetting the घातer well on haswell only disable the pfit अगर
	 * it's in use. The hw state code will make sure we get this right. */
	अगर (!old_crtc_state->pch_pfit.enabled)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, PF_CTL(pipe), 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, PF_WIN_POS(pipe), 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, PF_WIN_SZ(pipe), 0);
पूर्ण

अटल व्योम ilk_crtc_disable(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/*
	 * Someबार spurious CPU pipe underruns happen when the
	 * pipe is alपढ़ोy disabled, but FDI RX/TX is still enabled.
	 * Happens at least with VGA+HDMI cloning. Suppress them.
	 */
	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, false);
	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, pipe, false);

	पूर्णांकel_encoders_disable(state, crtc);

	पूर्णांकel_crtc_vblank_off(old_crtc_state);

	पूर्णांकel_disable_pipe(old_crtc_state);

	ilk_pfit_disable(old_crtc_state);

	अगर (old_crtc_state->has_pch_encoder)
		ilk_fdi_disable(crtc);

	पूर्णांकel_encoders_post_disable(state, crtc);

	अगर (old_crtc_state->has_pch_encoder) अणु
		ilk_disable_pch_transcoder(dev_priv, pipe);

		अगर (HAS_PCH_CPT(dev_priv)) अणु
			i915_reg_t reg;
			u32 temp;

			/* disable TRANS_DP_CTL */
			reg = TRANS_DP_CTL(pipe);
			temp = पूर्णांकel_de_पढ़ो(dev_priv, reg);
			temp &= ~(TRANS_DP_OUTPUT_ENABLE |
				  TRANS_DP_PORT_SEL_MASK);
			temp |= TRANS_DP_PORT_SEL_NONE;
			पूर्णांकel_de_ग_लिखो(dev_priv, reg, temp);

			/* disable DPLL_SEL */
			temp = पूर्णांकel_de_पढ़ो(dev_priv, PCH_DPLL_SEL);
			temp &= ~(TRANS_DPLL_ENABLE(pipe) | TRANS_DPLLB_SEL(pipe));
			पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DPLL_SEL, temp);
		पूर्ण

		ilk_fdi_pll_disable(crtc);
	पूर्ण

	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, true);
	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, pipe, true);
पूर्ण

अटल व्योम hsw_crtc_disable(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_crtc *crtc)
अणु
	/*
	 * FIXME collapse everything to one hook.
	 * Need care with mst->ddi पूर्णांकeractions.
	 */
	पूर्णांकel_encoders_disable(state, crtc);
	पूर्णांकel_encoders_post_disable(state, crtc);
पूर्ण

अटल व्योम i9xx_pfit_enable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (!crtc_state->gmch_pfit.control)
		वापस;

	/*
	 * The panel fitter should only be adjusted whilst the pipe is disabled,
	 * according to रेजिस्टर description and PRM.
	 */
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, PFIT_CONTROL) & PFIT_ENABLE);
	निश्चित_pipe_disabled(dev_priv, crtc_state->cpu_transcoder);

	पूर्णांकel_de_ग_लिखो(dev_priv, PFIT_PGM_RATIOS,
		       crtc_state->gmch_pfit.pgm_ratios);
	पूर्णांकel_de_ग_लिखो(dev_priv, PFIT_CONTROL, crtc_state->gmch_pfit.control);

	/* Border color in हाल we करोn't scale up to the full screen. Black by
	 * शेष, change to something अन्यथा क्रम debugging. */
	पूर्णांकel_de_ग_लिखो(dev_priv, BCLRPAT(crtc->pipe), 0);
पूर्ण

bool पूर्णांकel_phy_is_combo(काष्ठा drm_i915_निजी *dev_priv, क्रमागत phy phy)
अणु
	अगर (phy == PHY_NONE)
		वापस false;
	अन्यथा अगर (IS_ALDERLAKE_S(dev_priv))
		वापस phy <= PHY_E;
	अन्यथा अगर (IS_DG1(dev_priv) || IS_ROCKETLAKE(dev_priv))
		वापस phy <= PHY_D;
	अन्यथा अगर (IS_JSL_EHL(dev_priv))
		वापस phy <= PHY_C;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 11)
		वापस phy <= PHY_B;
	अन्यथा
		वापस false;
पूर्ण

bool पूर्णांकel_phy_is_tc(काष्ठा drm_i915_निजी *dev_priv, क्रमागत phy phy)
अणु
	अगर (IS_TIGERLAKE(dev_priv))
		वापस phy >= PHY_D && phy <= PHY_I;
	अन्यथा अगर (IS_ICELAKE(dev_priv))
		वापस phy >= PHY_C && phy <= PHY_F;
	अन्यथा
		वापस false;
पूर्ण

क्रमागत phy पूर्णांकel_port_to_phy(काष्ठा drm_i915_निजी *i915, क्रमागत port port)
अणु
	अगर (IS_ALDERLAKE_S(i915) && port >= PORT_TC1)
		वापस PHY_B + port - PORT_TC1;
	अन्यथा अगर ((IS_DG1(i915) || IS_ROCKETLAKE(i915)) && port >= PORT_TC1)
		वापस PHY_C + port - PORT_TC1;
	अन्यथा अगर (IS_JSL_EHL(i915) && port == PORT_D)
		वापस PHY_A;

	वापस PHY_A + port - PORT_A;
पूर्ण

क्रमागत tc_port पूर्णांकel_port_to_tc(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port)
अणु
	अगर (!पूर्णांकel_phy_is_tc(dev_priv, पूर्णांकel_port_to_phy(dev_priv, port)))
		वापस TC_PORT_NONE;

	अगर (DISPLAY_VER(dev_priv) >= 12)
		वापस TC_PORT_1 + port - PORT_TC1;
	अन्यथा
		वापस TC_PORT_1 + port - PORT_C;
पूर्ण

क्रमागत पूर्णांकel_display_घातer_करोमुख्य पूर्णांकel_port_to_घातer_करोमुख्य(क्रमागत port port)
अणु
	चयन (port) अणु
	हाल PORT_A:
		वापस POWER_DOMAIN_PORT_DDI_A_LANES;
	हाल PORT_B:
		वापस POWER_DOMAIN_PORT_DDI_B_LANES;
	हाल PORT_C:
		वापस POWER_DOMAIN_PORT_DDI_C_LANES;
	हाल PORT_D:
		वापस POWER_DOMAIN_PORT_DDI_D_LANES;
	हाल PORT_E:
		वापस POWER_DOMAIN_PORT_DDI_E_LANES;
	हाल PORT_F:
		वापस POWER_DOMAIN_PORT_DDI_F_LANES;
	हाल PORT_G:
		वापस POWER_DOMAIN_PORT_DDI_G_LANES;
	हाल PORT_H:
		वापस POWER_DOMAIN_PORT_DDI_H_LANES;
	हाल PORT_I:
		वापस POWER_DOMAIN_PORT_DDI_I_LANES;
	शेष:
		MISSING_CASE(port);
		वापस POWER_DOMAIN_PORT_OTHER;
	पूर्ण
पूर्ण

क्रमागत पूर्णांकel_display_घातer_करोमुख्य
पूर्णांकel_aux_घातer_करोमुख्य(काष्ठा पूर्णांकel_digital_port *dig_port)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dig_port->base.base.dev);
	क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, dig_port->base.port);

	अगर (पूर्णांकel_phy_is_tc(dev_priv, phy) &&
	    dig_port->tc_mode == TC_PORT_TBT_ALT) अणु
		चयन (dig_port->aux_ch) अणु
		हाल AUX_CH_C:
			वापस POWER_DOMAIN_AUX_C_TBT;
		हाल AUX_CH_D:
			वापस POWER_DOMAIN_AUX_D_TBT;
		हाल AUX_CH_E:
			वापस POWER_DOMAIN_AUX_E_TBT;
		हाल AUX_CH_F:
			वापस POWER_DOMAIN_AUX_F_TBT;
		हाल AUX_CH_G:
			वापस POWER_DOMAIN_AUX_G_TBT;
		हाल AUX_CH_H:
			वापस POWER_DOMAIN_AUX_H_TBT;
		हाल AUX_CH_I:
			वापस POWER_DOMAIN_AUX_I_TBT;
		शेष:
			MISSING_CASE(dig_port->aux_ch);
			वापस POWER_DOMAIN_AUX_C_TBT;
		पूर्ण
	पूर्ण

	वापस पूर्णांकel_legacy_aux_to_घातer_करोमुख्य(dig_port->aux_ch);
पूर्ण

/*
 * Converts aux_ch to घातer_करोमुख्य without caring about TBT ports क्रम that use
 * पूर्णांकel_aux_घातer_करोमुख्य()
 */
क्रमागत पूर्णांकel_display_घातer_करोमुख्य
पूर्णांकel_legacy_aux_to_घातer_करोमुख्य(क्रमागत aux_ch aux_ch)
अणु
	चयन (aux_ch) अणु
	हाल AUX_CH_A:
		वापस POWER_DOMAIN_AUX_A;
	हाल AUX_CH_B:
		वापस POWER_DOMAIN_AUX_B;
	हाल AUX_CH_C:
		वापस POWER_DOMAIN_AUX_C;
	हाल AUX_CH_D:
		वापस POWER_DOMAIN_AUX_D;
	हाल AUX_CH_E:
		वापस POWER_DOMAIN_AUX_E;
	हाल AUX_CH_F:
		वापस POWER_DOMAIN_AUX_F;
	हाल AUX_CH_G:
		वापस POWER_DOMAIN_AUX_G;
	हाल AUX_CH_H:
		वापस POWER_DOMAIN_AUX_H;
	हाल AUX_CH_I:
		वापस POWER_DOMAIN_AUX_I;
	शेष:
		MISSING_CASE(aux_ch);
		वापस POWER_DOMAIN_AUX_A;
	पूर्ण
पूर्ण

अटल u64 get_crtc_घातer_करोमुख्यs(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा drm_encoder *encoder;
	क्रमागत pipe pipe = crtc->pipe;
	u64 mask;
	क्रमागत transcoder transcoder = crtc_state->cpu_transcoder;

	अगर (!crtc_state->hw.active)
		वापस 0;

	mask = BIT_ULL(POWER_DOMAIN_PIPE(pipe));
	mask |= BIT_ULL(POWER_DOMAIN_TRANSCODER(transcoder));
	अगर (crtc_state->pch_pfit.enabled ||
	    crtc_state->pch_pfit.क्रमce_thru)
		mask |= BIT_ULL(POWER_DOMAIN_PIPE_PANEL_FITTER(pipe));

	drm_क्रम_each_encoder_mask(encoder, &dev_priv->drm,
				  crtc_state->uapi.encoder_mask) अणु
		काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = to_पूर्णांकel_encoder(encoder);

		mask |= BIT_ULL(पूर्णांकel_encoder->घातer_करोमुख्य);
	पूर्ण

	अगर (HAS_DDI(dev_priv) && crtc_state->has_audio)
		mask |= BIT_ULL(POWER_DOMAIN_AUDIO);

	अगर (crtc_state->shared_dpll)
		mask |= BIT_ULL(POWER_DOMAIN_DISPLAY_CORE);

	अगर (crtc_state->dsc.compression_enable)
		mask |= BIT_ULL(पूर्णांकel_dsc_घातer_करोमुख्य(crtc_state));

	वापस mask;
पूर्ण

अटल u64
modeset_get_crtc_घातer_करोमुख्यs(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य करोमुख्य;
	u64 करोमुख्यs, new_करोमुख्यs, old_करोमुख्यs;

	करोमुख्यs = get_crtc_घातer_करोमुख्यs(crtc_state);

	new_करोमुख्यs = करोमुख्यs & ~crtc->enabled_घातer_करोमुख्यs.mask;
	old_करोमुख्यs = crtc->enabled_घातer_करोमुख्यs.mask & ~करोमुख्यs;

	क्रम_each_घातer_करोमुख्य(करोमुख्य, new_करोमुख्यs)
		पूर्णांकel_display_घातer_get_in_set(dev_priv,
					       &crtc->enabled_घातer_करोमुख्यs,
					       करोमुख्य);

	वापस old_करोमुख्यs;
पूर्ण

अटल व्योम modeset_put_crtc_घातer_करोमुख्यs(काष्ठा पूर्णांकel_crtc *crtc,
					   u64 करोमुख्यs)
अणु
	पूर्णांकel_display_घातer_put_mask_in_set(to_i915(crtc->base.dev),
					    &crtc->enabled_घातer_करोमुख्यs,
					    करोमुख्यs);
पूर्ण

अटल व्योम valleyview_crtc_enable(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	अगर (drm_WARN_ON(&dev_priv->drm, crtc->active))
		वापस;

	अगर (पूर्णांकel_crtc_has_dp_encoder(new_crtc_state))
		पूर्णांकel_dp_set_m_n(new_crtc_state, M1_N1);

	पूर्णांकel_set_transcoder_timings(new_crtc_state);
	पूर्णांकel_set_pipe_src_size(new_crtc_state);

	अगर (IS_CHERRYVIEW(dev_priv) && pipe == PIPE_B) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, CHV_BLEND(pipe), CHV_BLEND_LEGACY);
		पूर्णांकel_de_ग_लिखो(dev_priv, CHV_CANVAS(pipe), 0);
	पूर्ण

	i9xx_set_pipeconf(new_crtc_state);

	crtc->active = true;

	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, true);

	पूर्णांकel_encoders_pre_pll_enable(state, crtc);

	अगर (IS_CHERRYVIEW(dev_priv)) अणु
		chv_prepare_pll(crtc, new_crtc_state);
		chv_enable_pll(crtc, new_crtc_state);
	पूर्ण अन्यथा अणु
		vlv_prepare_pll(crtc, new_crtc_state);
		vlv_enable_pll(crtc, new_crtc_state);
	पूर्ण

	पूर्णांकel_encoders_pre_enable(state, crtc);

	i9xx_pfit_enable(new_crtc_state);

	पूर्णांकel_color_load_luts(new_crtc_state);
	पूर्णांकel_color_commit(new_crtc_state);
	/* update DSPCNTR to configure gamma क्रम pipe bottom color */
	पूर्णांकel_disable_primary_plane(new_crtc_state);

	dev_priv->display.initial_watermarks(state, crtc);
	पूर्णांकel_enable_pipe(new_crtc_state);

	पूर्णांकel_crtc_vblank_on(new_crtc_state);

	पूर्णांकel_encoders_enable(state, crtc);
पूर्ण

अटल व्योम i9xx_set_pll_भागiders(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	पूर्णांकel_de_ग_लिखो(dev_priv, FP0(crtc->pipe),
		       crtc_state->dpll_hw_state.fp0);
	पूर्णांकel_de_ग_लिखो(dev_priv, FP1(crtc->pipe),
		       crtc_state->dpll_hw_state.fp1);
पूर्ण

अटल व्योम i9xx_crtc_enable(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	अगर (drm_WARN_ON(&dev_priv->drm, crtc->active))
		वापस;

	i9xx_set_pll_भागiders(new_crtc_state);

	अगर (पूर्णांकel_crtc_has_dp_encoder(new_crtc_state))
		पूर्णांकel_dp_set_m_n(new_crtc_state, M1_N1);

	पूर्णांकel_set_transcoder_timings(new_crtc_state);
	पूर्णांकel_set_pipe_src_size(new_crtc_state);

	i9xx_set_pipeconf(new_crtc_state);

	crtc->active = true;

	अगर (!IS_DISPLAY_VER(dev_priv, 2))
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, true);

	पूर्णांकel_encoders_pre_enable(state, crtc);

	i9xx_enable_pll(crtc, new_crtc_state);

	i9xx_pfit_enable(new_crtc_state);

	पूर्णांकel_color_load_luts(new_crtc_state);
	पूर्णांकel_color_commit(new_crtc_state);
	/* update DSPCNTR to configure gamma क्रम pipe bottom color */
	पूर्णांकel_disable_primary_plane(new_crtc_state);

	अगर (dev_priv->display.initial_watermarks)
		dev_priv->display.initial_watermarks(state, crtc);
	अन्यथा
		पूर्णांकel_update_watermarks(crtc);
	पूर्णांकel_enable_pipe(new_crtc_state);

	पूर्णांकel_crtc_vblank_on(new_crtc_state);

	पूर्णांकel_encoders_enable(state, crtc);

	/* prevents spurious underruns */
	अगर (IS_DISPLAY_VER(dev_priv, 2))
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
पूर्ण

अटल व्योम i9xx_pfit_disable(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(old_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (!old_crtc_state->gmch_pfit.control)
		वापस;

	निश्चित_pipe_disabled(dev_priv, old_crtc_state->cpu_transcoder);

	drm_dbg_kms(&dev_priv->drm, "disabling pfit, current: 0x%08x\n",
		    पूर्णांकel_de_पढ़ो(dev_priv, PFIT_CONTROL));
	पूर्णांकel_de_ग_लिखो(dev_priv, PFIT_CONTROL, 0);
पूर्ण

अटल व्योम i9xx_crtc_disable(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/*
	 * On gen2 planes are द्विगुन buffered but the pipe isn't, so we must
	 * रुको क्रम planes to fully turn off beक्रमe disabling the pipe.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 2))
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);

	पूर्णांकel_encoders_disable(state, crtc);

	पूर्णांकel_crtc_vblank_off(old_crtc_state);

	पूर्णांकel_disable_pipe(old_crtc_state);

	i9xx_pfit_disable(old_crtc_state);

	पूर्णांकel_encoders_post_disable(state, crtc);

	अगर (!पूर्णांकel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_DSI)) अणु
		अगर (IS_CHERRYVIEW(dev_priv))
			chv_disable_pll(dev_priv, pipe);
		अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
			vlv_disable_pll(dev_priv, pipe);
		अन्यथा
			i9xx_disable_pll(old_crtc_state);
	पूर्ण

	पूर्णांकel_encoders_post_pll_disable(state, crtc);

	अगर (!IS_DISPLAY_VER(dev_priv, 2))
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, false);

	अगर (!dev_priv->display.initial_watermarks)
		पूर्णांकel_update_watermarks(crtc);

	/* घड़ी the pipe करोwn to 640x480@60 to potentially save घातer */
	अगर (IS_I830(dev_priv))
		i830_enable_pipe(dev_priv, pipe);
पूर्ण

अटल व्योम पूर्णांकel_crtc_disable_noatomic(काष्ठा पूर्णांकel_crtc *crtc,
					काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_bw_state *bw_state =
		to_पूर्णांकel_bw_state(dev_priv->bw_obj.state);
	काष्ठा पूर्णांकel_cdclk_state *cdclk_state =
		to_पूर्णांकel_cdclk_state(dev_priv->cdclk.obj.state);
	काष्ठा पूर्णांकel_dbuf_state *dbuf_state =
		to_पूर्णांकel_dbuf_state(dev_priv->dbuf.obj.state);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		to_पूर्णांकel_crtc_state(crtc->base.state);
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा drm_atomic_state *state;
	काष्ठा पूर्णांकel_crtc_state *temp_crtc_state;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक ret;

	अगर (!crtc_state->hw.active)
		वापस;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
		स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
			to_पूर्णांकel_plane_state(plane->base.state);

		अगर (plane_state->uapi.visible)
			पूर्णांकel_plane_disable_noatomic(crtc, plane);
	पूर्ण

	state = drm_atomic_state_alloc(&dev_priv->drm);
	अगर (!state) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "failed to disable [CRTC:%d:%s], out of memory",
			    crtc->base.base.id, crtc->base.name);
		वापस;
	पूर्ण

	state->acquire_ctx = ctx;

	/* Everything's already locked, -EDEADLK can't happen. */
	temp_crtc_state = पूर्णांकel_atomic_get_crtc_state(state, crtc);
	ret = drm_atomic_add_affected_connectors(state, &crtc->base);

	drm_WARN_ON(&dev_priv->drm, IS_ERR(temp_crtc_state) || ret);

	dev_priv->display.crtc_disable(to_पूर्णांकel_atomic_state(state), crtc);

	drm_atomic_state_put(state);

	drm_dbg_kms(&dev_priv->drm,
		    "[CRTC:%d:%s] hw state adjusted, was enabled, now disabled\n",
		    crtc->base.base.id, crtc->base.name);

	crtc->active = false;
	crtc->base.enabled = false;

	drm_WARN_ON(&dev_priv->drm,
		    drm_atomic_set_mode_क्रम_crtc(&crtc_state->uapi, शून्य) < 0);
	crtc_state->uapi.active = false;
	crtc_state->uapi.connector_mask = 0;
	crtc_state->uapi.encoder_mask = 0;
	पूर्णांकel_crtc_मुक्त_hw_state(crtc_state);
	स_रखो(&crtc_state->hw, 0, माप(crtc_state->hw));

	क्रम_each_encoder_on_crtc(&dev_priv->drm, &crtc->base, encoder)
		encoder->base.crtc = शून्य;

	पूर्णांकel_fbc_disable(crtc);
	पूर्णांकel_update_watermarks(crtc);
	पूर्णांकel_disable_shared_dpll(crtc_state);

	पूर्णांकel_display_घातer_put_all_in_set(dev_priv, &crtc->enabled_घातer_करोमुख्यs);

	dev_priv->active_pipes &= ~BIT(pipe);
	cdclk_state->min_cdclk[pipe] = 0;
	cdclk_state->min_voltage_level[pipe] = 0;
	cdclk_state->active_pipes &= ~BIT(pipe);

	dbuf_state->active_pipes &= ~BIT(pipe);

	bw_state->data_rate[pipe] = 0;
	bw_state->num_active_planes[pipe] = 0;
पूर्ण

/*
 * turn all crtc's off, but करो not adjust state
 * This has to be paired with a call to पूर्णांकel_modeset_setup_hw_state.
 */
पूर्णांक पूर्णांकel_display_suspend(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_atomic_state *state;
	पूर्णांक ret;

	state = drm_atomic_helper_suspend(dev);
	ret = PTR_ERR_OR_ZERO(state);
	अगर (ret)
		drm_err(&dev_priv->drm, "Suspending crtc's failed with %i\n",
			ret);
	अन्यथा
		dev_priv->modeset_restore_state = state;
	वापस ret;
पूर्ण

व्योम पूर्णांकel_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = to_पूर्णांकel_encoder(encoder);

	drm_encoder_cleanup(encoder);
	kमुक्त(पूर्णांकel_encoder);
पूर्ण

/* Cross check the actual hw state with our own modeset state tracking (and it's
 * पूर्णांकernal consistency). */
अटल व्योम पूर्णांकel_connector_verअगरy_state(काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_connector *connector = to_पूर्णांकel_connector(conn_state->connector);
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->base.dev);

	drm_dbg_kms(&i915->drm, "[CONNECTOR:%d:%s]\n",
		    connector->base.base.id, connector->base.name);

	अगर (connector->get_hw_state(connector)) अणु
		काष्ठा पूर्णांकel_encoder *encoder = पूर्णांकel_attached_encoder(connector);

		I915_STATE_WARN(!crtc_state,
			 "connector enabled without attached crtc\n");

		अगर (!crtc_state)
			वापस;

		I915_STATE_WARN(!crtc_state->hw.active,
				"connector is active, but attached crtc isn't\n");

		अगर (!encoder || encoder->type == INTEL_OUTPUT_DP_MST)
			वापस;

		I915_STATE_WARN(conn_state->best_encoder != &encoder->base,
			"atomic encoder doesn't match attached encoder\n");

		I915_STATE_WARN(conn_state->crtc != encoder->base.crtc,
			"attached encoder crtc differs from connector crtc\n");
	पूर्ण अन्यथा अणु
		I915_STATE_WARN(crtc_state && crtc_state->hw.active,
				"attached crtc is active, but connector isn't\n");
		I915_STATE_WARN(!crtc_state && conn_state->best_encoder,
			"best encoder set without crtc!\n");
	पूर्ण
पूर्ण

bool hsw_crtc_state_ips_capable(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	/* IPS only exists on ULT machines and is tied to pipe A. */
	अगर (!hsw_crtc_supports_ips(crtc))
		वापस false;

	अगर (!dev_priv->params.enable_ips)
		वापस false;

	अगर (crtc_state->pipe_bpp > 24)
		वापस false;

	/*
	 * We compare against max which means we must take
	 * the increased cdclk requirement पूर्णांकo account when
	 * calculating the new cdclk.
	 *
	 * Should measure whether using a lower cdclk w/o IPS
	 */
	अगर (IS_BROADWELL(dev_priv) &&
	    crtc_state->pixel_rate > dev_priv->max_cdclk_freq * 95 / 100)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hsw_compute_ips_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		to_i915(crtc_state->uapi.crtc->dev);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(crtc_state->uapi.state);

	crtc_state->ips_enabled = false;

	अगर (!hsw_crtc_state_ips_capable(crtc_state))
		वापस 0;

	/*
	 * When IPS माला_लो enabled, the pipe CRC changes. Since IPS माला_लो
	 * enabled and disabled dynamically based on package C states,
	 * user space can't make reliable use of the CRCs, so let's just
	 * completely disable it.
	 */
	अगर (crtc_state->crc_enabled)
		वापस 0;

	/* IPS should be fine as दीर्घ as at least one plane is enabled. */
	अगर (!(crtc_state->active_planes & ~BIT(PLANE_CURSOR)))
		वापस 0;

	अगर (IS_BROADWELL(dev_priv)) अणु
		स्थिर काष्ठा पूर्णांकel_cdclk_state *cdclk_state;

		cdclk_state = पूर्णांकel_atomic_get_cdclk_state(state);
		अगर (IS_ERR(cdclk_state))
			वापस PTR_ERR(cdclk_state);

		/* pixel rate mustn't exceed 95% of cdclk with IPS on BDW */
		अगर (crtc_state->pixel_rate > cdclk_state->logical.cdclk * 95 / 100)
			वापस 0;
	पूर्ण

	crtc_state->ips_enabled = true;

	वापस 0;
पूर्ण

अटल bool पूर्णांकel_crtc_supports_द्विगुन_wide(स्थिर काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	/* GDG द्विगुन wide on either pipe, otherwise pipe A only */
	वापस DISPLAY_VER(dev_priv) < 4 &&
		(crtc->pipe == PIPE_A || IS_I915G(dev_priv));
पूर्ण

अटल u32 ilk_pipe_pixel_rate(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 pixel_rate = crtc_state->hw.pipe_mode.crtc_घड़ी;
	अचिन्हित पूर्णांक pipe_w, pipe_h, pfit_w, pfit_h;

	/*
	 * We only use IF-ID पूर्णांकerlacing. If we ever use
	 * PF-ID we'll need to adjust the pixel_rate here.
	 */

	अगर (!crtc_state->pch_pfit.enabled)
		वापस pixel_rate;

	pipe_w = crtc_state->pipe_src_w;
	pipe_h = crtc_state->pipe_src_h;

	pfit_w = drm_rect_width(&crtc_state->pch_pfit.dst);
	pfit_h = drm_rect_height(&crtc_state->pch_pfit.dst);

	अगर (pipe_w < pfit_w)
		pipe_w = pfit_w;
	अगर (pipe_h < pfit_h)
		pipe_h = pfit_h;

	अगर (drm_WARN_ON(crtc_state->uapi.crtc->dev,
			!pfit_w || !pfit_h))
		वापस pixel_rate;

	वापस भाग_u64(mul_u32_u32(pixel_rate, pipe_w * pipe_h),
		       pfit_w * pfit_h);
पूर्ण

अटल व्योम पूर्णांकel_mode_from_crtc_timings(काष्ठा drm_display_mode *mode,
					 स्थिर काष्ठा drm_display_mode *timings)
अणु
	mode->hdisplay = timings->crtc_hdisplay;
	mode->htotal = timings->crtc_htotal;
	mode->hsync_start = timings->crtc_hsync_start;
	mode->hsync_end = timings->crtc_hsync_end;

	mode->vdisplay = timings->crtc_vdisplay;
	mode->vtotal = timings->crtc_vtotal;
	mode->vsync_start = timings->crtc_vsync_start;
	mode->vsync_end = timings->crtc_vsync_end;

	mode->flags = timings->flags;
	mode->type = DRM_MODE_TYPE_DRIVER;

	mode->घड़ी = timings->crtc_घड़ी;

	drm_mode_set_name(mode);
पूर्ण

अटल व्योम पूर्णांकel_crtc_compute_pixel_rate(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	अगर (HAS_GMCH(dev_priv))
		/* FIXME calculate proper pipe pixel rate क्रम GMCH pfit */
		crtc_state->pixel_rate =
			crtc_state->hw.pipe_mode.crtc_घड़ी;
	अन्यथा
		crtc_state->pixel_rate =
			ilk_pipe_pixel_rate(crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_crtc_पढ़ोout_derived_state(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_display_mode *mode = &crtc_state->hw.mode;
	काष्ठा drm_display_mode *pipe_mode = &crtc_state->hw.pipe_mode;
	काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;

	drm_mode_copy(pipe_mode, adjusted_mode);

	अगर (crtc_state->bigjoiner) अणु
		/*
		 * transcoder is programmed to the full mode,
		 * but pipe timings are half of the transcoder mode
		 */
		pipe_mode->crtc_hdisplay /= 2;
		pipe_mode->crtc_hblank_start /= 2;
		pipe_mode->crtc_hblank_end /= 2;
		pipe_mode->crtc_hsync_start /= 2;
		pipe_mode->crtc_hsync_end /= 2;
		pipe_mode->crtc_htotal /= 2;
		pipe_mode->crtc_घड़ी /= 2;
	पूर्ण

	अगर (crtc_state->splitter.enable) अणु
		पूर्णांक n = crtc_state->splitter.link_count;
		पूर्णांक overlap = crtc_state->splitter.pixel_overlap;

		/*
		 * eDP MSO uses segment timings from EDID क्रम transcoder
		 * timings, but full mode क्रम everything अन्यथा.
		 *
		 * h_full = (h_segment - pixel_overlap) * link_count
		 */
		pipe_mode->crtc_hdisplay = (pipe_mode->crtc_hdisplay - overlap) * n;
		pipe_mode->crtc_hblank_start = (pipe_mode->crtc_hblank_start - overlap) * n;
		pipe_mode->crtc_hblank_end = (pipe_mode->crtc_hblank_end - overlap) * n;
		pipe_mode->crtc_hsync_start = (pipe_mode->crtc_hsync_start - overlap) * n;
		pipe_mode->crtc_hsync_end = (pipe_mode->crtc_hsync_end - overlap) * n;
		pipe_mode->crtc_htotal = (pipe_mode->crtc_htotal - overlap) * n;
		pipe_mode->crtc_घड़ी *= n;

		पूर्णांकel_mode_from_crtc_timings(pipe_mode, pipe_mode);
		पूर्णांकel_mode_from_crtc_timings(adjusted_mode, pipe_mode);
	पूर्ण अन्यथा अणु
		पूर्णांकel_mode_from_crtc_timings(pipe_mode, pipe_mode);
		पूर्णांकel_mode_from_crtc_timings(adjusted_mode, adjusted_mode);
	पूर्ण

	पूर्णांकel_crtc_compute_pixel_rate(crtc_state);

	drm_mode_copy(mode, adjusted_mode);
	mode->hdisplay = crtc_state->pipe_src_w << crtc_state->bigjoiner;
	mode->vdisplay = crtc_state->pipe_src_h;
पूर्ण

अटल व्योम पूर्णांकel_encoder_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				     काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	encoder->get_config(encoder, crtc_state);

	पूर्णांकel_crtc_पढ़ोout_derived_state(crtc_state);
पूर्ण

अटल पूर्णांक पूर्णांकel_crtc_compute_config(काष्ठा पूर्णांकel_crtc *crtc,
				     काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा drm_display_mode *pipe_mode = &pipe_config->hw.pipe_mode;
	पूर्णांक घड़ी_limit = dev_priv->max_करोtclk_freq;

	drm_mode_copy(pipe_mode, &pipe_config->hw.adjusted_mode);

	/* Adjust pipe_mode क्रम bigjoiner, with half the horizontal mode */
	अगर (pipe_config->bigjoiner) अणु
		pipe_mode->crtc_घड़ी /= 2;
		pipe_mode->crtc_hdisplay /= 2;
		pipe_mode->crtc_hblank_start /= 2;
		pipe_mode->crtc_hblank_end /= 2;
		pipe_mode->crtc_hsync_start /= 2;
		pipe_mode->crtc_hsync_end /= 2;
		pipe_mode->crtc_htotal /= 2;
		pipe_config->pipe_src_w /= 2;
	पूर्ण

	अगर (pipe_config->splitter.enable) अणु
		पूर्णांक n = pipe_config->splitter.link_count;
		पूर्णांक overlap = pipe_config->splitter.pixel_overlap;

		pipe_mode->crtc_hdisplay = (pipe_mode->crtc_hdisplay - overlap) * n;
		pipe_mode->crtc_hblank_start = (pipe_mode->crtc_hblank_start - overlap) * n;
		pipe_mode->crtc_hblank_end = (pipe_mode->crtc_hblank_end - overlap) * n;
		pipe_mode->crtc_hsync_start = (pipe_mode->crtc_hsync_start - overlap) * n;
		pipe_mode->crtc_hsync_end = (pipe_mode->crtc_hsync_end - overlap) * n;
		pipe_mode->crtc_htotal = (pipe_mode->crtc_htotal - overlap) * n;
		pipe_mode->crtc_घड़ी *= n;
	पूर्ण

	पूर्णांकel_mode_from_crtc_timings(pipe_mode, pipe_mode);

	अगर (DISPLAY_VER(dev_priv) < 4) अणु
		घड़ी_limit = dev_priv->max_cdclk_freq * 9 / 10;

		/*
		 * Enable द्विगुन wide mode when the करोt घड़ी
		 * is > 90% of the (display) core speed.
		 */
		अगर (पूर्णांकel_crtc_supports_द्विगुन_wide(crtc) &&
		    pipe_mode->crtc_घड़ी > घड़ी_limit) अणु
			घड़ी_limit = dev_priv->max_करोtclk_freq;
			pipe_config->द्विगुन_wide = true;
		पूर्ण
	पूर्ण

	अगर (pipe_mode->crtc_घड़ी > घड़ी_limit) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "requested pixel clock (%d kHz) too high (max: %d kHz, double wide: %s)\n",
			    pipe_mode->crtc_घड़ी, घड़ी_limit,
			    yesno(pipe_config->द्विगुन_wide));
		वापस -EINVAL;
	पूर्ण

	/*
	 * Pipe horizontal size must be even in:
	 * - DVO ganged mode
	 * - LVDS dual channel mode
	 * - Double wide pipe
	 */
	अगर (pipe_config->pipe_src_w & 1) अणु
		अगर (pipe_config->द्विगुन_wide) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Odd pipe source width not supported with double wide pipe\n");
			वापस -EINVAL;
		पूर्ण

		अगर (पूर्णांकel_crtc_has_type(pipe_config, INTEL_OUTPUT_LVDS) &&
		    पूर्णांकel_is_dual_link_lvds(dev_priv)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Odd pipe source width not supported with dual link LVDS\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Cantiga+ cannot handle modes with a hsync front porch of 0.
	 * WaPruneModeWithIncorrectHsyncOffset:ctg,elk,ilk,snb,ivb,vlv,hsw.
	 */
	अगर ((DISPLAY_VER(dev_priv) > 4 || IS_G4X(dev_priv)) &&
	    pipe_mode->crtc_hsync_start == pipe_mode->crtc_hdisplay)
		वापस -EINVAL;

	पूर्णांकel_crtc_compute_pixel_rate(pipe_config);

	अगर (pipe_config->has_pch_encoder)
		वापस ilk_fdi_compute_config(crtc, pipe_config);

	वापस 0;
पूर्ण

अटल व्योम
पूर्णांकel_reduce_m_n_ratio(u32 *num, u32 *den)
अणु
	जबतक (*num > DATA_LINK_M_N_MASK ||
	       *den > DATA_LINK_M_N_MASK) अणु
		*num >>= 1;
		*den >>= 1;
	पूर्ण
पूर्ण

अटल व्योम compute_m_n(अचिन्हित पूर्णांक m, अचिन्हित पूर्णांक n,
			u32 *ret_m, u32 *ret_n,
			bool स्थिरant_n)
अणु
	/*
	 * Several DP करोngles in particular seem to be fussy about
	 * too large link M/N values. Give N value as 0x8000 that
	 * should be acceptable by specअगरic devices. 0x8000 is the
	 * specअगरied fixed N value क्रम asynchronous घड़ी mode,
	 * which the devices expect also in synchronous घड़ी mode.
	 */
	अगर (स्थिरant_n)
		*ret_n = DP_LINK_CONSTANT_N_VALUE;
	अन्यथा
		*ret_n = min_t(अचिन्हित पूर्णांक, roundup_घात_of_two(n), DATA_LINK_N_MAX);

	*ret_m = भाग_u64(mul_u32_u32(m, *ret_n), n);
	पूर्णांकel_reduce_m_n_ratio(ret_m, ret_n);
पूर्ण

व्योम
पूर्णांकel_link_compute_m_n(u16 bits_per_pixel, पूर्णांक nlanes,
		       पूर्णांक pixel_घड़ी, पूर्णांक link_घड़ी,
		       काष्ठा पूर्णांकel_link_m_n *m_n,
		       bool स्थिरant_n, bool fec_enable)
अणु
	u32 data_घड़ी = bits_per_pixel * pixel_घड़ी;

	अगर (fec_enable)
		data_घड़ी = पूर्णांकel_dp_mode_to_fec_घड़ी(data_घड़ी);

	m_n->tu = 64;
	compute_m_n(data_घड़ी,
		    link_घड़ी * nlanes * 8,
		    &m_n->gmch_m, &m_n->gmch_n,
		    स्थिरant_n);

	compute_m_n(pixel_घड़ी, link_घड़ी,
		    &m_n->link_m, &m_n->link_n,
		    स्थिरant_n);
पूर्ण

अटल व्योम पूर्णांकel_panel_sanitize_ssc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * There may be no VBT; and अगर the BIOS enabled SSC we can
	 * just keep using it to aव्योम unnecessary flicker.  Whereas अगर the
	 * BIOS isn't using it, don't assume it will work even अगर the VBT
	 * indicates as much.
	 */
	अगर (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv)) अणु
		bool bios_lvds_use_ssc = पूर्णांकel_de_पढ़ो(dev_priv,
						       PCH_DREF_CONTROL) &
			DREF_SSC1_ENABLE;

		अगर (dev_priv->vbt.lvds_use_ssc != bios_lvds_use_ssc) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "SSC %s by BIOS, overriding VBT which says %s\n",
				    enableddisabled(bios_lvds_use_ssc),
				    enableddisabled(dev_priv->vbt.lvds_use_ssc));
			dev_priv->vbt.lvds_use_ssc = bios_lvds_use_ssc;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pch_transcoder_set_m_n(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 स्थिर काष्ठा पूर्णांकel_link_m_n *m_n)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_DATA_M1(pipe),
		       TU_SIZE(m_n->tu) | m_n->gmch_m);
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_DATA_N1(pipe), m_n->gmch_n);
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_LINK_M1(pipe), m_n->link_m);
	पूर्णांकel_de_ग_लिखो(dev_priv, PCH_TRANS_LINK_N1(pipe), m_n->link_n);
पूर्ण

अटल bool transcoder_has_m2_n2(काष्ठा drm_i915_निजी *dev_priv,
				 क्रमागत transcoder transcoder)
अणु
	अगर (IS_HASWELL(dev_priv))
		वापस transcoder == TRANSCODER_EDP;

	/*
	 * Strictly speaking some रेजिस्टरs are available beक्रमe
	 * gen7, but we only support DRRS on gen7+
	 */
	वापस IS_DISPLAY_VER(dev_priv, 7) || IS_CHERRYVIEW(dev_priv);
पूर्ण

अटल व्योम पूर्णांकel_cpu_transcoder_set_m_n(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
					 स्थिर काष्ठा पूर्णांकel_link_m_n *m_n,
					 स्थिर काष्ठा पूर्णांकel_link_m_n *m2_n2)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत transcoder transcoder = crtc_state->cpu_transcoder;

	अगर (DISPLAY_VER(dev_priv) >= 5) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_DATA_M1(transcoder),
			       TU_SIZE(m_n->tu) | m_n->gmch_m);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_DATA_N1(transcoder),
			       m_n->gmch_n);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_LINK_M1(transcoder),
			       m_n->link_m);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_LINK_N1(transcoder),
			       m_n->link_n);
		/*
		 *  M2_N2 रेजिस्टरs are set only अगर DRRS is supported
		 * (to make sure the रेजिस्टरs are not unnecessarily accessed).
		 */
		अगर (m2_n2 && crtc_state->has_drrs &&
		    transcoder_has_m2_n2(dev_priv, transcoder)) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_DATA_M2(transcoder),
				       TU_SIZE(m2_n2->tu) | m2_n2->gmch_m);
			पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_DATA_N2(transcoder),
				       m2_n2->gmch_n);
			पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_LINK_M2(transcoder),
				       m2_n2->link_m);
			पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_LINK_N2(transcoder),
				       m2_n2->link_n);
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_DATA_M_G4X(pipe),
			       TU_SIZE(m_n->tu) | m_n->gmch_m);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_DATA_N_G4X(pipe), m_n->gmch_n);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_LINK_M_G4X(pipe), m_n->link_m);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_LINK_N_G4X(pipe), m_n->link_n);
	पूर्ण
पूर्ण

व्योम पूर्णांकel_dp_set_m_n(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state, क्रमागत link_m_n_set m_n)
अणु
	स्थिर काष्ठा पूर्णांकel_link_m_n *dp_m_n, *dp_m2_n2 = शून्य;
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc_state->uapi.crtc->dev);

	अगर (m_n == M1_N1) अणु
		dp_m_n = &crtc_state->dp_m_n;
		dp_m2_n2 = &crtc_state->dp_m2_n2;
	पूर्ण अन्यथा अगर (m_n == M2_N2) अणु

		/*
		 * M2_N2 रेजिस्टरs are not supported. Hence m2_n2 भागider value
		 * needs to be programmed पूर्णांकo M1_N1.
		 */
		dp_m_n = &crtc_state->dp_m2_n2;
	पूर्ण अन्यथा अणु
		drm_err(&i915->drm, "Unsupported divider value\n");
		वापस;
	पूर्ण

	अगर (crtc_state->has_pch_encoder)
		पूर्णांकel_pch_transcoder_set_m_n(crtc_state, &crtc_state->dp_m_n);
	अन्यथा
		पूर्णांकel_cpu_transcoder_set_m_n(crtc_state, dp_m_n, dp_m2_n2);
पूर्ण

अटल व्योम पूर्णांकel_set_transcoder_timings(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;
	u32 crtc_vtotal, crtc_vblank_end;
	पूर्णांक vsyncshअगरt = 0;

	/* We need to be careful not to changed the adjusted mode, क्रम otherwise
	 * the hw state checker will get angry at the mismatch. */
	crtc_vtotal = adjusted_mode->crtc_vtotal;
	crtc_vblank_end = adjusted_mode->crtc_vblank_end;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) अणु
		/* the chip adds 2 halflines स्वतःmatically */
		crtc_vtotal -= 1;
		crtc_vblank_end -= 1;

		अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO))
			vsyncshअगरt = (adjusted_mode->crtc_htotal - 1) / 2;
		अन्यथा
			vsyncshअगरt = adjusted_mode->crtc_hsync_start -
				adjusted_mode->crtc_htotal / 2;
		अगर (vsyncshअगरt < 0)
			vsyncshअगरt += adjusted_mode->crtc_htotal;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) > 3)
		पूर्णांकel_de_ग_लिखो(dev_priv, VSYNCSHIFT(cpu_transcoder),
		               vsyncshअगरt);

	पूर्णांकel_de_ग_लिखो(dev_priv, HTOTAL(cpu_transcoder),
		       (adjusted_mode->crtc_hdisplay - 1) | ((adjusted_mode->crtc_htotal - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, HBLANK(cpu_transcoder),
		       (adjusted_mode->crtc_hblank_start - 1) | ((adjusted_mode->crtc_hblank_end - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, HSYNC(cpu_transcoder),
		       (adjusted_mode->crtc_hsync_start - 1) | ((adjusted_mode->crtc_hsync_end - 1) << 16));

	पूर्णांकel_de_ग_लिखो(dev_priv, VTOTAL(cpu_transcoder),
		       (adjusted_mode->crtc_vdisplay - 1) | ((crtc_vtotal - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, VBLANK(cpu_transcoder),
		       (adjusted_mode->crtc_vblank_start - 1) | ((crtc_vblank_end - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, VSYNC(cpu_transcoder),
		       (adjusted_mode->crtc_vsync_start - 1) | ((adjusted_mode->crtc_vsync_end - 1) << 16));

	/* Workaround: when the EDP input selection is B, the VTOTAL_B must be
	 * programmed with the VTOTAL_EDP value. Same क्रम VTOTAL_C. This is
	 * करोcumented on the DDI_FUNC_CTL रेजिस्टर description, EDP Input Select
	 * bits. */
	अगर (IS_HASWELL(dev_priv) && cpu_transcoder == TRANSCODER_EDP &&
	    (pipe == PIPE_B || pipe == PIPE_C))
		पूर्णांकel_de_ग_लिखो(dev_priv, VTOTAL(pipe),
		               पूर्णांकel_de_पढ़ो(dev_priv, VTOTAL(cpu_transcoder)));

पूर्ण

अटल व्योम पूर्णांकel_set_pipe_src_size(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/* pipesrc controls the size that is scaled from, which should
	 * always be the user's requested size.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPESRC(pipe),
		       ((crtc_state->pipe_src_w - 1) << 16) | (crtc_state->pipe_src_h - 1));
पूर्ण

अटल bool पूर्णांकel_pipe_is_पूर्णांकerlaced(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	अगर (IS_DISPLAY_VER(dev_priv, 2))
		वापस false;

	अगर (DISPLAY_VER(dev_priv) >= 9 ||
	    IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		वापस पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(cpu_transcoder)) & PIPECONF_INTERLACE_MASK_HSW;
	अन्यथा
		वापस पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(cpu_transcoder)) & PIPECONF_INTERLACE_MASK;
पूर्ण

अटल व्योम पूर्णांकel_get_transcoder_timings(काष्ठा पूर्णांकel_crtc *crtc,
					 काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत transcoder cpu_transcoder = pipe_config->cpu_transcoder;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HTOTAL(cpu_transcoder));
	pipe_config->hw.adjusted_mode.crtc_hdisplay = (पंचांगp & 0xffff) + 1;
	pipe_config->hw.adjusted_mode.crtc_htotal = ((पंचांगp >> 16) & 0xffff) + 1;

	अगर (!transcoder_is_dsi(cpu_transcoder)) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HBLANK(cpu_transcoder));
		pipe_config->hw.adjusted_mode.crtc_hblank_start =
							(पंचांगp & 0xffff) + 1;
		pipe_config->hw.adjusted_mode.crtc_hblank_end =
						((पंचांगp >> 16) & 0xffff) + 1;
	पूर्ण
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, HSYNC(cpu_transcoder));
	pipe_config->hw.adjusted_mode.crtc_hsync_start = (पंचांगp & 0xffff) + 1;
	pipe_config->hw.adjusted_mode.crtc_hsync_end = ((पंचांगp >> 16) & 0xffff) + 1;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, VTOTAL(cpu_transcoder));
	pipe_config->hw.adjusted_mode.crtc_vdisplay = (पंचांगp & 0xffff) + 1;
	pipe_config->hw.adjusted_mode.crtc_vtotal = ((पंचांगp >> 16) & 0xffff) + 1;

	अगर (!transcoder_is_dsi(cpu_transcoder)) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, VBLANK(cpu_transcoder));
		pipe_config->hw.adjusted_mode.crtc_vblank_start =
							(पंचांगp & 0xffff) + 1;
		pipe_config->hw.adjusted_mode.crtc_vblank_end =
						((पंचांगp >> 16) & 0xffff) + 1;
	पूर्ण
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, VSYNC(cpu_transcoder));
	pipe_config->hw.adjusted_mode.crtc_vsync_start = (पंचांगp & 0xffff) + 1;
	pipe_config->hw.adjusted_mode.crtc_vsync_end = ((पंचांगp >> 16) & 0xffff) + 1;

	अगर (पूर्णांकel_pipe_is_पूर्णांकerlaced(pipe_config)) अणु
		pipe_config->hw.adjusted_mode.flags |= DRM_MODE_FLAG_INTERLACE;
		pipe_config->hw.adjusted_mode.crtc_vtotal += 1;
		pipe_config->hw.adjusted_mode.crtc_vblank_end += 1;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_get_pipe_src_size(काष्ठा पूर्णांकel_crtc *crtc,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPESRC(crtc->pipe));
	pipe_config->pipe_src_h = (पंचांगp & 0xffff) + 1;
	pipe_config->pipe_src_w = ((पंचांगp >> 16) & 0xffff) + 1;
पूर्ण

अटल व्योम i9xx_set_pipeconf(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 pipeconf;

	pipeconf = 0;

	/* we keep both pipes enabled on 830 */
	अगर (IS_I830(dev_priv))
		pipeconf |= पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(crtc->pipe)) & PIPECONF_ENABLE;

	अगर (crtc_state->द्विगुन_wide)
		pipeconf |= PIPECONF_DOUBLE_WIDE;

	/* only g4x and later have fancy bpc/dither controls */
	अगर (IS_G4X(dev_priv) || IS_VALLEYVIEW(dev_priv) ||
	    IS_CHERRYVIEW(dev_priv)) अणु
		/* Bspec claims that we can't use dithering क्रम 30bpp pipes. */
		अगर (crtc_state->dither && crtc_state->pipe_bpp != 30)
			pipeconf |= PIPECONF_DITHER_EN |
				    PIPECONF_DITHER_TYPE_SP;

		चयन (crtc_state->pipe_bpp) अणु
		हाल 18:
			pipeconf |= PIPECONF_6BPC;
			अवरोध;
		हाल 24:
			pipeconf |= PIPECONF_8BPC;
			अवरोध;
		हाल 30:
			pipeconf |= PIPECONF_10BPC;
			अवरोध;
		शेष:
			/* Case prevented by पूर्णांकel_choose_pipe_bpp_dither. */
			BUG();
		पूर्ण
	पूर्ण

	अगर (crtc_state->hw.adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE) अणु
		अगर (DISPLAY_VER(dev_priv) < 4 ||
		    पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO))
			pipeconf |= PIPECONF_INTERLACE_W_FIELD_INDICATION;
		अन्यथा
			pipeconf |= PIPECONF_INTERLACE_W_SYNC_SHIFT;
	पूर्ण अन्यथा अणु
		pipeconf |= PIPECONF_PROGRESSIVE;
	पूर्ण

	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	     crtc_state->limited_color_range)
		pipeconf |= PIPECONF_COLOR_RANGE_SELECT;

	pipeconf |= PIPECONF_GAMMA_MODE(crtc_state->gamma_mode);

	pipeconf |= PIPECONF_FRAME_START_DELAY(dev_priv->framestart_delay - 1);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(crtc->pipe), pipeconf);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPECONF(crtc->pipe));
पूर्ण

अटल bool i9xx_has_pfit(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_I830(dev_priv))
		वापस false;

	वापस DISPLAY_VER(dev_priv) >= 4 ||
		IS_PINEVIEW(dev_priv) || IS_MOBILE(dev_priv);
पूर्ण

अटल व्योम i9xx_get_pfit_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 पंचांगp;

	अगर (!i9xx_has_pfit(dev_priv))
		वापस;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PFIT_CONTROL);
	अगर (!(पंचांगp & PFIT_ENABLE))
		वापस;

	/* Check whether the pfit is attached to our pipe. */
	अगर (DISPLAY_VER(dev_priv) < 4) अणु
		अगर (crtc->pipe != PIPE_B)
			वापस;
	पूर्ण अन्यथा अणु
		अगर ((पंचांगp & PFIT_PIPE_MASK) != (crtc->pipe << PFIT_PIPE_SHIFT))
			वापस;
	पूर्ण

	crtc_state->gmch_pfit.control = पंचांगp;
	crtc_state->gmch_pfit.pgm_ratios =
		पूर्णांकel_de_पढ़ो(dev_priv, PFIT_PGM_RATIOS);
पूर्ण

अटल व्योम vlv_crtc_घड़ी_get(काष्ठा पूर्णांकel_crtc *crtc,
			       काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा dpll घड़ी;
	u32 mभाग;
	पूर्णांक refclk = 100000;

	/* In हाल of DSI, DPLL will not be used */
	अगर ((pipe_config->dpll_hw_state.dpll & DPLL_VCO_ENABLE) == 0)
		वापस;

	vlv_dpio_get(dev_priv);
	mभाग = vlv_dpio_पढ़ो(dev_priv, pipe, VLV_PLL_DW3(pipe));
	vlv_dpio_put(dev_priv);

	घड़ी.m1 = (mभाग >> DPIO_M1DIV_SHIFT) & 7;
	घड़ी.m2 = mभाग & DPIO_M2DIV_MASK;
	घड़ी.n = (mभाग >> DPIO_N_SHIFT) & 0xf;
	घड़ी.p1 = (mभाग >> DPIO_P1_SHIFT) & 7;
	घड़ी.p2 = (mभाग >> DPIO_P2_SHIFT) & 0x1f;

	pipe_config->port_घड़ी = vlv_calc_dpll_params(refclk, &घड़ी);
पूर्ण

अटल व्योम chv_crtc_घड़ी_get(काष्ठा पूर्णांकel_crtc *crtc,
			       काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	क्रमागत dpio_channel port = vlv_pipe_to_channel(pipe);
	काष्ठा dpll घड़ी;
	u32 cmn_dw13, pll_dw0, pll_dw1, pll_dw2, pll_dw3;
	पूर्णांक refclk = 100000;

	/* In हाल of DSI, DPLL will not be used */
	अगर ((pipe_config->dpll_hw_state.dpll & DPLL_VCO_ENABLE) == 0)
		वापस;

	vlv_dpio_get(dev_priv);
	cmn_dw13 = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_CMN_DW13(port));
	pll_dw0 = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_PLL_DW0(port));
	pll_dw1 = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_PLL_DW1(port));
	pll_dw2 = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_PLL_DW2(port));
	pll_dw3 = vlv_dpio_पढ़ो(dev_priv, pipe, CHV_PLL_DW3(port));
	vlv_dpio_put(dev_priv);

	घड़ी.m1 = (pll_dw1 & 0x7) == DPIO_CHV_M1_DIV_BY_2 ? 2 : 0;
	घड़ी.m2 = (pll_dw0 & 0xff) << 22;
	अगर (pll_dw3 & DPIO_CHV_FRAC_DIV_EN)
		घड़ी.m2 |= pll_dw2 & 0x3fffff;
	घड़ी.n = (pll_dw1 >> DPIO_CHV_N_DIV_SHIFT) & 0xf;
	घड़ी.p1 = (cmn_dw13 >> DPIO_CHV_P1_DIV_SHIFT) & 0x7;
	घड़ी.p2 = (cmn_dw13 >> DPIO_CHV_P2_DIV_SHIFT) & 0x1f;

	pipe_config->port_घड़ी = chv_calc_dpll_params(refclk, &घड़ी);
पूर्ण

अटल क्रमागत पूर्णांकel_output_क्रमmat
bdw_get_pipemisc_output_क्रमmat(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPEMISC(crtc->pipe));

	अगर (पंचांगp & PIPEMISC_YUV420_ENABLE) अणु
		/* We support 4:2:0 in full blend mode only */
		drm_WARN_ON(&dev_priv->drm,
			    (पंचांगp & PIPEMISC_YUV420_MODE_FULL_BLEND) == 0);

		वापस INTEL_OUTPUT_FORMAT_YCBCR420;
	पूर्ण अन्यथा अगर (पंचांगp & PIPEMISC_OUTPUT_COLORSPACE_YUV) अणु
		वापस INTEL_OUTPUT_FORMAT_YCBCR444;
	पूर्ण अन्यथा अणु
		वापस INTEL_OUTPUT_FORMAT_RGB;
	पूर्ण
पूर्ण

अटल व्योम i9xx_get_pipe_color_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(crtc->base.primary);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत i9xx_plane_id i9xx_plane = plane->i9xx_plane;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSPCNTR(i9xx_plane));

	अगर (पंचांगp & DISPPLANE_GAMMA_ENABLE)
		crtc_state->gamma_enable = true;

	अगर (!HAS_GMCH(dev_priv) &&
	    पंचांगp & DISPPLANE_PIPE_CSC_ENABLE)
		crtc_state->csc_enable = true;
पूर्ण

अटल bool i9xx_get_pipe_config(काष्ठा पूर्णांकel_crtc *crtc,
				 काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;
	u32 पंचांगp;
	bool ret;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(crtc->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;
	pipe_config->cpu_transcoder = (क्रमागत transcoder) crtc->pipe;
	pipe_config->shared_dpll = शून्य;

	ret = false;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(crtc->pipe));
	अगर (!(पंचांगp & PIPECONF_ENABLE))
		जाओ out;

	अगर (IS_G4X(dev_priv) || IS_VALLEYVIEW(dev_priv) ||
	    IS_CHERRYVIEW(dev_priv)) अणु
		चयन (पंचांगp & PIPECONF_BPC_MASK) अणु
		हाल PIPECONF_6BPC:
			pipe_config->pipe_bpp = 18;
			अवरोध;
		हाल PIPECONF_8BPC:
			pipe_config->pipe_bpp = 24;
			अवरोध;
		हाल PIPECONF_10BPC:
			pipe_config->pipe_bpp = 30;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
	    (पंचांगp & PIPECONF_COLOR_RANGE_SELECT))
		pipe_config->limited_color_range = true;

	pipe_config->gamma_mode = (पंचांगp & PIPECONF_GAMMA_MODE_MASK_I9XX) >>
		PIPECONF_GAMMA_MODE_SHIFT;

	अगर (IS_CHERRYVIEW(dev_priv))
		pipe_config->cgm_mode = पूर्णांकel_de_पढ़ो(dev_priv,
						      CGM_PIPE_MODE(crtc->pipe));

	i9xx_get_pipe_color_config(pipe_config);
	पूर्णांकel_color_get_config(pipe_config);

	अगर (DISPLAY_VER(dev_priv) < 4)
		pipe_config->द्विगुन_wide = पंचांगp & PIPECONF_DOUBLE_WIDE;

	पूर्णांकel_get_transcoder_timings(crtc, pipe_config);
	पूर्णांकel_get_pipe_src_size(crtc, pipe_config);

	i9xx_get_pfit_config(pipe_config);

	अगर (DISPLAY_VER(dev_priv) >= 4) अणु
		/* No way to पढ़ो it out on pipes B and C */
		अगर (IS_CHERRYVIEW(dev_priv) && crtc->pipe != PIPE_A)
			पंचांगp = dev_priv->chv_dpll_md[crtc->pipe];
		अन्यथा
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DPLL_MD(crtc->pipe));
		pipe_config->pixel_multiplier =
			((पंचांगp & DPLL_MD_UDI_MULTIPLIER_MASK)
			 >> DPLL_MD_UDI_MULTIPLIER_SHIFT) + 1;
		pipe_config->dpll_hw_state.dpll_md = पंचांगp;
	पूर्ण अन्यथा अगर (IS_I945G(dev_priv) || IS_I945GM(dev_priv) ||
		   IS_G33(dev_priv) || IS_PINEVIEW(dev_priv)) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DPLL(crtc->pipe));
		pipe_config->pixel_multiplier =
			((पंचांगp & SDVO_MULTIPLIER_MASK)
			 >> SDVO_MULTIPLIER_SHIFT_HIRES) + 1;
	पूर्ण अन्यथा अणु
		/* Note that on i915G/GM the pixel multiplier is in the sdvo
		 * port and will be fixed up in the encoder->get_config
		 * function. */
		pipe_config->pixel_multiplier = 1;
	पूर्ण
	pipe_config->dpll_hw_state.dpll = पूर्णांकel_de_पढ़ो(dev_priv,
							DPLL(crtc->pipe));
	अगर (!IS_VALLEYVIEW(dev_priv) && !IS_CHERRYVIEW(dev_priv)) अणु
		pipe_config->dpll_hw_state.fp0 = पूर्णांकel_de_पढ़ो(dev_priv,
							       FP0(crtc->pipe));
		pipe_config->dpll_hw_state.fp1 = पूर्णांकel_de_पढ़ो(dev_priv,
							       FP1(crtc->pipe));
	पूर्ण अन्यथा अणु
		/* Mask out पढ़ो-only status bits. */
		pipe_config->dpll_hw_state.dpll &= ~(DPLL_LOCK_VLV |
						     DPLL_PORTC_READY_MASK |
						     DPLL_PORTB_READY_MASK);
	पूर्ण

	अगर (IS_CHERRYVIEW(dev_priv))
		chv_crtc_घड़ी_get(crtc, pipe_config);
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		vlv_crtc_घड़ी_get(crtc, pipe_config);
	अन्यथा
		i9xx_crtc_घड़ी_get(crtc, pipe_config);

	/*
	 * Normally the करोtघड़ी is filled in by the encoder .get_config()
	 * but in हाल the pipe is enabled w/o any ports we need a sane
	 * शेष.
	 */
	pipe_config->hw.adjusted_mode.crtc_घड़ी =
		pipe_config->port_घड़ी / pipe_config->pixel_multiplier;

	ret = true;

out:
	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल व्योम ilk_init_pch_refclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	पूर्णांक i;
	u32 val, final;
	bool has_lvds = false;
	bool has_cpu_edp = false;
	bool has_panel = false;
	bool has_ck505 = false;
	bool can_ssc = false;
	bool using_ssc_source = false;

	/* We need to take the global config पूर्णांकo account */
	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		चयन (encoder->type) अणु
		हाल INTEL_OUTPUT_LVDS:
			has_panel = true;
			has_lvds = true;
			अवरोध;
		हाल INTEL_OUTPUT_EDP:
			has_panel = true;
			अगर (encoder->port == PORT_A)
				has_cpu_edp = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (HAS_PCH_IBX(dev_priv)) अणु
		has_ck505 = dev_priv->vbt.display_घड़ी_mode;
		can_ssc = has_ck505;
	पूर्ण अन्यथा अणु
		has_ck505 = false;
		can_ssc = true;
	पूर्ण

	/* Check अगर any DPLLs are using the SSC source */
	क्रम (i = 0; i < dev_priv->dpll.num_shared_dpll; i++) अणु
		u32 temp = पूर्णांकel_de_पढ़ो(dev_priv, PCH_DPLL(i));

		अगर (!(temp & DPLL_VCO_ENABLE))
			जारी;

		अगर ((temp & PLL_REF_INPUT_MASK) ==
		    PLLB_REF_INPUT_SPREADSPECTRUMIN) अणु
			using_ssc_source = true;
			अवरोध;
		पूर्ण
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "has_panel %d has_lvds %d has_ck505 %d using_ssc_source %d\n",
		    has_panel, has_lvds, has_ck505, using_ssc_source);

	/* Ironlake: try to setup display ref घड़ी beक्रमe DPLL
	 * enabling. This is only under driver's control after
	 * PCH B stepping, previous chipset stepping should be
	 * ignoring this setting.
	 */
	val = पूर्णांकel_de_पढ़ो(dev_priv, PCH_DREF_CONTROL);

	/* As we must carefully and slowly disable/enable each source in turn,
	 * compute the final state we want first and check अगर we need to
	 * make any changes at all.
	 */
	final = val;
	final &= ~DREF_NONSPREAD_SOURCE_MASK;
	अगर (has_ck505)
		final |= DREF_NONSPREAD_CK505_ENABLE;
	अन्यथा
		final |= DREF_NONSPREAD_SOURCE_ENABLE;

	final &= ~DREF_SSC_SOURCE_MASK;
	final &= ~DREF_CPU_SOURCE_OUTPUT_MASK;
	final &= ~DREF_SSC1_ENABLE;

	अगर (has_panel) अणु
		final |= DREF_SSC_SOURCE_ENABLE;

		अगर (पूर्णांकel_panel_use_ssc(dev_priv) && can_ssc)
			final |= DREF_SSC1_ENABLE;

		अगर (has_cpu_edp) अणु
			अगर (पूर्णांकel_panel_use_ssc(dev_priv) && can_ssc)
				final |= DREF_CPU_SOURCE_OUTPUT_DOWNSPREAD;
			अन्यथा
				final |= DREF_CPU_SOURCE_OUTPUT_NONSPREAD;
		पूर्ण अन्यथा
			final |= DREF_CPU_SOURCE_OUTPUT_DISABLE;
	पूर्ण अन्यथा अगर (using_ssc_source) अणु
		final |= DREF_SSC_SOURCE_ENABLE;
		final |= DREF_SSC1_ENABLE;
	पूर्ण

	अगर (final == val)
		वापस;

	/* Always enable nonspपढ़ो source */
	val &= ~DREF_NONSPREAD_SOURCE_MASK;

	अगर (has_ck505)
		val |= DREF_NONSPREAD_CK505_ENABLE;
	अन्यथा
		val |= DREF_NONSPREAD_SOURCE_ENABLE;

	अगर (has_panel) अणु
		val &= ~DREF_SSC_SOURCE_MASK;
		val |= DREF_SSC_SOURCE_ENABLE;

		/* SSC must be turned on beक्रमe enabling the CPU output  */
		अगर (पूर्णांकel_panel_use_ssc(dev_priv) && can_ssc) अणु
			drm_dbg_kms(&dev_priv->drm, "Using SSC on panel\n");
			val |= DREF_SSC1_ENABLE;
		पूर्ण अन्यथा
			val &= ~DREF_SSC1_ENABLE;

		/* Get SSC going beक्रमe enabling the outमाला_दो */
		पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DREF_CONTROL, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, PCH_DREF_CONTROL);
		udelay(200);

		val &= ~DREF_CPU_SOURCE_OUTPUT_MASK;

		/* Enable CPU source on CPU attached eDP */
		अगर (has_cpu_edp) अणु
			अगर (पूर्णांकel_panel_use_ssc(dev_priv) && can_ssc) अणु
				drm_dbg_kms(&dev_priv->drm,
					    "Using SSC on eDP\n");
				val |= DREF_CPU_SOURCE_OUTPUT_DOWNSPREAD;
			पूर्ण अन्यथा
				val |= DREF_CPU_SOURCE_OUTPUT_NONSPREAD;
		पूर्ण अन्यथा
			val |= DREF_CPU_SOURCE_OUTPUT_DISABLE;

		पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DREF_CONTROL, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, PCH_DREF_CONTROL);
		udelay(200);
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm, "Disabling CPU source output\n");

		val &= ~DREF_CPU_SOURCE_OUTPUT_MASK;

		/* Turn off CPU output */
		val |= DREF_CPU_SOURCE_OUTPUT_DISABLE;

		पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DREF_CONTROL, val);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, PCH_DREF_CONTROL);
		udelay(200);

		अगर (!using_ssc_source) अणु
			drm_dbg_kms(&dev_priv->drm, "Disabling SSC source\n");

			/* Turn off the SSC source */
			val &= ~DREF_SSC_SOURCE_MASK;
			val |= DREF_SSC_SOURCE_DISABLE;

			/* Turn off SSC1 */
			val &= ~DREF_SSC1_ENABLE;

			पूर्णांकel_de_ग_लिखो(dev_priv, PCH_DREF_CONTROL, val);
			पूर्णांकel_de_posting_पढ़ो(dev_priv, PCH_DREF_CONTROL);
			udelay(200);
		पूर्ण
	पूर्ण

	BUG_ON(val != final);
पूर्ण

अटल व्योम lpt_reset_fdi_mphy(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN2);
	पंचांगp |= FDI_MPHY_IOSFSB_RESET_CTL;
	पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_CHICKEN2, पंचांगp);

	अगर (रुको_क्रम_us(पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN2) &
			FDI_MPHY_IOSFSB_RESET_STATUS, 100))
		drm_err(&dev_priv->drm, "FDI mPHY reset assert timeout\n");

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN2);
	पंचांगp &= ~FDI_MPHY_IOSFSB_RESET_CTL;
	पूर्णांकel_de_ग_लिखो(dev_priv, SOUTH_CHICKEN2, पंचांगp);

	अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, SOUTH_CHICKEN2) &
			 FDI_MPHY_IOSFSB_RESET_STATUS) == 0, 100))
		drm_err(&dev_priv->drm, "FDI mPHY reset de-assert timeout\n");
पूर्ण

/* WaMPhyProgramming:hsw */
अटल व्योम lpt_program_fdi_mphy(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x8008, SBI_MPHY);
	पंचांगp &= ~(0xFF << 24);
	पंचांगp |= (0x12 << 24);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x8008, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x2008, SBI_MPHY);
	पंचांगp |= (1 << 11);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x2008, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x2108, SBI_MPHY);
	पंचांगp |= (1 << 11);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x2108, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x206C, SBI_MPHY);
	पंचांगp |= (1 << 24) | (1 << 21) | (1 << 18);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x206C, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x216C, SBI_MPHY);
	पंचांगp |= (1 << 24) | (1 << 21) | (1 << 18);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x216C, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x2080, SBI_MPHY);
	पंचांगp &= ~(7 << 13);
	पंचांगp |= (5 << 13);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x2080, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x2180, SBI_MPHY);
	पंचांगp &= ~(7 << 13);
	पंचांगp |= (5 << 13);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x2180, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x208C, SBI_MPHY);
	पंचांगp &= ~0xFF;
	पंचांगp |= 0x1C;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x208C, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x218C, SBI_MPHY);
	पंचांगp &= ~0xFF;
	पंचांगp |= 0x1C;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x218C, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x2098, SBI_MPHY);
	पंचांगp &= ~(0xFF << 16);
	पंचांगp |= (0x1C << 16);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x2098, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x2198, SBI_MPHY);
	पंचांगp &= ~(0xFF << 16);
	पंचांगp |= (0x1C << 16);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x2198, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x20C4, SBI_MPHY);
	पंचांगp |= (1 << 27);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x20C4, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x21C4, SBI_MPHY);
	पंचांगp |= (1 << 27);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x21C4, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x20EC, SBI_MPHY);
	पंचांगp &= ~(0xF << 28);
	पंचांगp |= (4 << 28);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x20EC, पंचांगp, SBI_MPHY);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, 0x21EC, SBI_MPHY);
	पंचांगp &= ~(0xF << 28);
	पंचांगp |= (4 << 28);
	पूर्णांकel_sbi_ग_लिखो(dev_priv, 0x21EC, पंचांगp, SBI_MPHY);
पूर्ण

/* Implements 3 dअगरferent sequences from BSpec chapter "Display iCLK
 * Programming" based on the parameters passed:
 * - Sequence to enable CLKOUT_DP
 * - Sequence to enable CLKOUT_DP without spपढ़ो
 * - Sequence to enable CLKOUT_DP क्रम FDI usage and configure PCH FDI I/O
 */
अटल व्योम lpt_enable_clkout_dp(काष्ठा drm_i915_निजी *dev_priv,
				 bool with_spपढ़ो, bool with_fdi)
अणु
	u32 reg, पंचांगp;

	अगर (drm_WARN(&dev_priv->drm, with_fdi && !with_spपढ़ो,
		     "FDI requires downspread\n"))
		with_spपढ़ो = true;
	अगर (drm_WARN(&dev_priv->drm, HAS_PCH_LPT_LP(dev_priv) &&
		     with_fdi, "LP PCH doesn't have FDI\n"))
		with_fdi = false;

	mutex_lock(&dev_priv->sb_lock);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCCTL, SBI_ICLK);
	पंचांगp &= ~SBI_SSCCTL_DISABLE;
	पंचांगp |= SBI_SSCCTL_PATHALT;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCCTL, पंचांगp, SBI_ICLK);

	udelay(24);

	अगर (with_spपढ़ो) अणु
		पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCCTL, SBI_ICLK);
		पंचांगp &= ~SBI_SSCCTL_PATHALT;
		पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCCTL, पंचांगp, SBI_ICLK);

		अगर (with_fdi) अणु
			lpt_reset_fdi_mphy(dev_priv);
			lpt_program_fdi_mphy(dev_priv);
		पूर्ण
	पूर्ण

	reg = HAS_PCH_LPT_LP(dev_priv) ? SBI_GEN0 : SBI_DBUFF0;
	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, reg, SBI_ICLK);
	पंचांगp |= SBI_GEN0_CFG_BUFFENABLE_DISABLE;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, reg, पंचांगp, SBI_ICLK);

	mutex_unlock(&dev_priv->sb_lock);
पूर्ण

/* Sequence to disable CLKOUT_DP */
व्योम lpt_disable_clkout_dp(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 reg, पंचांगp;

	mutex_lock(&dev_priv->sb_lock);

	reg = HAS_PCH_LPT_LP(dev_priv) ? SBI_GEN0 : SBI_DBUFF0;
	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, reg, SBI_ICLK);
	पंचांगp &= ~SBI_GEN0_CFG_BUFFENABLE_DISABLE;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, reg, पंचांगp, SBI_ICLK);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCCTL, SBI_ICLK);
	अगर (!(पंचांगp & SBI_SSCCTL_DISABLE)) अणु
		अगर (!(पंचांगp & SBI_SSCCTL_PATHALT)) अणु
			पंचांगp |= SBI_SSCCTL_PATHALT;
			पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCCTL, पंचांगp, SBI_ICLK);
			udelay(32);
		पूर्ण
		पंचांगp |= SBI_SSCCTL_DISABLE;
		पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCCTL, पंचांगp, SBI_ICLK);
	पूर्ण

	mutex_unlock(&dev_priv->sb_lock);
पूर्ण

#घोषणा BEND_IDX(steps) ((50 + (steps)) / 5)

अटल स्थिर u16 sscभागपूर्णांकphase[] = अणु
	[BEND_IDX( 50)] = 0x3B23,
	[BEND_IDX( 45)] = 0x3B23,
	[BEND_IDX( 40)] = 0x3C23,
	[BEND_IDX( 35)] = 0x3C23,
	[BEND_IDX( 30)] = 0x3D23,
	[BEND_IDX( 25)] = 0x3D23,
	[BEND_IDX( 20)] = 0x3E23,
	[BEND_IDX( 15)] = 0x3E23,
	[BEND_IDX( 10)] = 0x3F23,
	[BEND_IDX(  5)] = 0x3F23,
	[BEND_IDX(  0)] = 0x0025,
	[BEND_IDX( -5)] = 0x0025,
	[BEND_IDX(-10)] = 0x0125,
	[BEND_IDX(-15)] = 0x0125,
	[BEND_IDX(-20)] = 0x0225,
	[BEND_IDX(-25)] = 0x0225,
	[BEND_IDX(-30)] = 0x0325,
	[BEND_IDX(-35)] = 0x0325,
	[BEND_IDX(-40)] = 0x0425,
	[BEND_IDX(-45)] = 0x0425,
	[BEND_IDX(-50)] = 0x0525,
पूर्ण;

/*
 * Bend CLKOUT_DP
 * steps -50 to 50 inclusive, in steps of 5
 * < 0 slow करोwn the घड़ी, > 0 speed up the घड़ी, 0 == no bend (135MHz)
 * change in घड़ी period = -(steps / 10) * 5.787 ps
 */
अटल व्योम lpt_bend_clkout_dp(काष्ठा drm_i915_निजी *dev_priv, पूर्णांक steps)
अणु
	u32 पंचांगp;
	पूर्णांक idx = BEND_IDX(steps);

	अगर (drm_WARN_ON(&dev_priv->drm, steps % 5 != 0))
		वापस;

	अगर (drm_WARN_ON(&dev_priv->drm, idx >= ARRAY_SIZE(sscभागपूर्णांकphase)))
		वापस;

	mutex_lock(&dev_priv->sb_lock);

	अगर (steps % 10 != 0)
		पंचांगp = 0xAAAAAAAB;
	अन्यथा
		पंचांगp = 0x00000000;
	पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCDITHPHASE, पंचांगp, SBI_ICLK);

	पंचांगp = पूर्णांकel_sbi_पढ़ो(dev_priv, SBI_SSCDIVINTPHASE, SBI_ICLK);
	पंचांगp &= 0xffff0000;
	पंचांगp |= sscभागपूर्णांकphase[idx];
	पूर्णांकel_sbi_ग_लिखो(dev_priv, SBI_SSCDIVINTPHASE, पंचांगp, SBI_ICLK);

	mutex_unlock(&dev_priv->sb_lock);
पूर्ण

#अघोषित BEND_IDX

अटल bool spll_uses_pch_ssc(काष्ठा drm_i915_निजी *dev_priv)
अणु
	u32 fuse_strap = पूर्णांकel_de_पढ़ो(dev_priv, FUSE_STRAP);
	u32 ctl = पूर्णांकel_de_पढ़ो(dev_priv, SPLL_CTL);

	अगर ((ctl & SPLL_PLL_ENABLE) == 0)
		वापस false;

	अगर ((ctl & SPLL_REF_MASK) == SPLL_REF_MUXED_SSC &&
	    (fuse_strap & HSW_CPU_SSC_ENABLE) == 0)
		वापस true;

	अगर (IS_BROADWELL(dev_priv) &&
	    (ctl & SPLL_REF_MASK) == SPLL_REF_PCH_SSC_BDW)
		वापस true;

	वापस false;
पूर्ण

अटल bool wrpll_uses_pch_ssc(काष्ठा drm_i915_निजी *dev_priv,
			       क्रमागत पूर्णांकel_dpll_id id)
अणु
	u32 fuse_strap = पूर्णांकel_de_पढ़ो(dev_priv, FUSE_STRAP);
	u32 ctl = पूर्णांकel_de_पढ़ो(dev_priv, WRPLL_CTL(id));

	अगर ((ctl & WRPLL_PLL_ENABLE) == 0)
		वापस false;

	अगर ((ctl & WRPLL_REF_MASK) == WRPLL_REF_PCH_SSC)
		वापस true;

	अगर ((IS_BROADWELL(dev_priv) || IS_HSW_ULT(dev_priv)) &&
	    (ctl & WRPLL_REF_MASK) == WRPLL_REF_MUXED_SSC_BDW &&
	    (fuse_strap & HSW_CPU_SSC_ENABLE) == 0)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम lpt_init_pch_refclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	bool has_fdi = false;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		चयन (encoder->type) अणु
		हाल INTEL_OUTPUT_ANALOG:
			has_fdi = true;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * The BIOS may have decided to use the PCH SSC
	 * reference so we must not disable it until the
	 * relevant PLLs have stopped relying on it. We'll
	 * just leave the PCH SSC reference enabled in हाल
	 * any active PLL is using it. It will get disabled
	 * after runसमय suspend अगर we करोn't have FDI.
	 *
	 * TODO: Move the whole reference घड़ी handling
	 * to the modeset sequence proper so that we can
	 * actually enable/disable/reconfigure these things
	 * safely. To करो that we need to पूर्णांकroduce a real
	 * घड़ी hierarchy. That would also allow us to करो
	 * घड़ी bending finally.
	 */
	dev_priv->pch_ssc_use = 0;

	अगर (spll_uses_pch_ssc(dev_priv)) अणु
		drm_dbg_kms(&dev_priv->drm, "SPLL using PCH SSC\n");
		dev_priv->pch_ssc_use |= BIT(DPLL_ID_SPLL);
	पूर्ण

	अगर (wrpll_uses_pch_ssc(dev_priv, DPLL_ID_WRPLL1)) अणु
		drm_dbg_kms(&dev_priv->drm, "WRPLL1 using PCH SSC\n");
		dev_priv->pch_ssc_use |= BIT(DPLL_ID_WRPLL1);
	पूर्ण

	अगर (wrpll_uses_pch_ssc(dev_priv, DPLL_ID_WRPLL2)) अणु
		drm_dbg_kms(&dev_priv->drm, "WRPLL2 using PCH SSC\n");
		dev_priv->pch_ssc_use |= BIT(DPLL_ID_WRPLL2);
	पूर्ण

	अगर (dev_priv->pch_ssc_use)
		वापस;

	अगर (has_fdi) अणु
		lpt_bend_clkout_dp(dev_priv, 0);
		lpt_enable_clkout_dp(dev_priv, true, true);
	पूर्ण अन्यथा अणु
		lpt_disable_clkout_dp(dev_priv);
	पूर्ण
पूर्ण

/*
 * Initialize reference घड़ीs when the driver loads
 */
व्योम पूर्णांकel_init_pch_refclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv))
		ilk_init_pch_refclk(dev_priv);
	अन्यथा अगर (HAS_PCH_LPT(dev_priv))
		lpt_init_pch_refclk(dev_priv);
पूर्ण

अटल व्योम ilk_set_pipeconf(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val;

	val = 0;

	चयन (crtc_state->pipe_bpp) अणु
	हाल 18:
		val |= PIPECONF_6BPC;
		अवरोध;
	हाल 24:
		val |= PIPECONF_8BPC;
		अवरोध;
	हाल 30:
		val |= PIPECONF_10BPC;
		अवरोध;
	हाल 36:
		val |= PIPECONF_12BPC;
		अवरोध;
	शेष:
		/* Case prevented by पूर्णांकel_choose_pipe_bpp_dither. */
		BUG();
	पूर्ण

	अगर (crtc_state->dither)
		val |= (PIPECONF_DITHER_EN | PIPECONF_DITHER_TYPE_SP);

	अगर (crtc_state->hw.adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE)
		val |= PIPECONF_INTERLACED_ILK;
	अन्यथा
		val |= PIPECONF_PROGRESSIVE;

	/*
	 * This would end up with an odd purple hue over
	 * the entire display. Make sure we करोn't करो it.
	 */
	drm_WARN_ON(&dev_priv->drm, crtc_state->limited_color_range &&
		    crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB);

	अगर (crtc_state->limited_color_range &&
	    !पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_SDVO))
		val |= PIPECONF_COLOR_RANGE_SELECT;

	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB)
		val |= PIPECONF_OUTPUT_COLORSPACE_YUV709;

	val |= PIPECONF_GAMMA_MODE(crtc_state->gamma_mode);

	val |= PIPECONF_FRAME_START_DELAY(dev_priv->framestart_delay - 1);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(pipe), val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPECONF(pipe));
पूर्ण

अटल व्योम hsw_set_pipeconf(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;
	u32 val = 0;

	अगर (IS_HASWELL(dev_priv) && crtc_state->dither)
		val |= (PIPECONF_DITHER_EN | PIPECONF_DITHER_TYPE_SP);

	अगर (crtc_state->hw.adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE)
		val |= PIPECONF_INTERLACED_ILK;
	अन्यथा
		val |= PIPECONF_PROGRESSIVE;

	अगर (IS_HASWELL(dev_priv) &&
	    crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB)
		val |= PIPECONF_OUTPUT_COLORSPACE_YUV_HSW;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(cpu_transcoder), val);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPECONF(cpu_transcoder));
पूर्ण

अटल व्योम bdw_set_pipemisc(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 val = 0;

	चयन (crtc_state->pipe_bpp) अणु
	हाल 18:
		val |= PIPEMISC_DITHER_6_BPC;
		अवरोध;
	हाल 24:
		val |= PIPEMISC_DITHER_8_BPC;
		अवरोध;
	हाल 30:
		val |= PIPEMISC_DITHER_10_BPC;
		अवरोध;
	हाल 36:
		val |= PIPEMISC_DITHER_12_BPC;
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->pipe_bpp);
		अवरोध;
	पूर्ण

	अगर (crtc_state->dither)
		val |= PIPEMISC_DITHER_ENABLE | PIPEMISC_DITHER_TYPE_SP;

	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420 ||
	    crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR444)
		val |= PIPEMISC_OUTPUT_COLORSPACE_YUV;

	अगर (crtc_state->output_क्रमmat == INTEL_OUTPUT_FORMAT_YCBCR420)
		val |= PIPEMISC_YUV420_ENABLE |
			PIPEMISC_YUV420_MODE_FULL_BLEND;

	अगर (DISPLAY_VER(dev_priv) >= 11 &&
	    (crtc_state->active_planes & ~(icl_hdr_plane_mask() |
					   BIT(PLANE_CURSOR))) == 0)
		val |= PIPEMISC_HDR_MODE_PRECISION;

	अगर (DISPLAY_VER(dev_priv) >= 12)
		val |= PIPEMISC_PIXEL_ROUNDING_TRUNC;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPEMISC(crtc->pipe), val);
पूर्ण

पूर्णांक bdw_get_pipemisc_bpp(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPEMISC(crtc->pipe));

	चयन (पंचांगp & PIPEMISC_DITHER_BPC_MASK) अणु
	हाल PIPEMISC_DITHER_6_BPC:
		वापस 18;
	हाल PIPEMISC_DITHER_8_BPC:
		वापस 24;
	हाल PIPEMISC_DITHER_10_BPC:
		वापस 30;
	हाल PIPEMISC_DITHER_12_BPC:
		वापस 36;
	शेष:
		MISSING_CASE(पंचांगp);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक ilk_get_lanes_required(पूर्णांक target_घड़ी, पूर्णांक link_bw, पूर्णांक bpp)
अणु
	/*
	 * Account क्रम spपढ़ो spectrum to aव्योम
	 * oversubscribing the link. Max center spपढ़ो
	 * is 2.5%; use 5% क्रम safety's sake.
	 */
	u32 bps = target_घड़ी * bpp * 21 / 20;
	वापस DIV_ROUND_UP(bps, link_bw * 8);
पूर्ण

अटल व्योम पूर्णांकel_pch_transcoder_get_m_n(काष्ठा पूर्णांकel_crtc *crtc,
					 काष्ठा पूर्णांकel_link_m_n *m_n)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;

	m_n->link_m = पूर्णांकel_de_पढ़ो(dev_priv, PCH_TRANS_LINK_M1(pipe));
	m_n->link_n = पूर्णांकel_de_पढ़ो(dev_priv, PCH_TRANS_LINK_N1(pipe));
	m_n->gmch_m = पूर्णांकel_de_पढ़ो(dev_priv, PCH_TRANS_DATA_M1(pipe))
		& ~TU_SIZE_MASK;
	m_n->gmch_n = पूर्णांकel_de_पढ़ो(dev_priv, PCH_TRANS_DATA_N1(pipe));
	m_n->tu = ((पूर्णांकel_de_पढ़ो(dev_priv, PCH_TRANS_DATA_M1(pipe))
		    & TU_SIZE_MASK) >> TU_SIZE_SHIFT) + 1;
पूर्ण

अटल व्योम पूर्णांकel_cpu_transcoder_get_m_n(काष्ठा पूर्णांकel_crtc *crtc,
					 क्रमागत transcoder transcoder,
					 काष्ठा पूर्णांकel_link_m_n *m_n,
					 काष्ठा पूर्णांकel_link_m_n *m2_n2)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	अगर (DISPLAY_VER(dev_priv) >= 5) अणु
		m_n->link_m = पूर्णांकel_de_पढ़ो(dev_priv,
					    PIPE_LINK_M1(transcoder));
		m_n->link_n = पूर्णांकel_de_पढ़ो(dev_priv,
					    PIPE_LINK_N1(transcoder));
		m_n->gmch_m = पूर्णांकel_de_पढ़ो(dev_priv,
					    PIPE_DATA_M1(transcoder))
			& ~TU_SIZE_MASK;
		m_n->gmch_n = पूर्णांकel_de_पढ़ो(dev_priv,
					    PIPE_DATA_N1(transcoder));
		m_n->tu = ((पूर्णांकel_de_पढ़ो(dev_priv, PIPE_DATA_M1(transcoder))
			    & TU_SIZE_MASK) >> TU_SIZE_SHIFT) + 1;

		अगर (m2_n2 && transcoder_has_m2_n2(dev_priv, transcoder)) अणु
			m2_n2->link_m = पूर्णांकel_de_पढ़ो(dev_priv,
						      PIPE_LINK_M2(transcoder));
			m2_n2->link_n =	पूर्णांकel_de_पढ़ो(dev_priv,
							     PIPE_LINK_N2(transcoder));
			m2_n2->gmch_m =	पूर्णांकel_de_पढ़ो(dev_priv,
							     PIPE_DATA_M2(transcoder))
					& ~TU_SIZE_MASK;
			m2_n2->gmch_n =	पूर्णांकel_de_पढ़ो(dev_priv,
							     PIPE_DATA_N2(transcoder));
			m2_n2->tu = ((पूर्णांकel_de_पढ़ो(dev_priv, PIPE_DATA_M2(transcoder))
					& TU_SIZE_MASK) >> TU_SIZE_SHIFT) + 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		m_n->link_m = पूर्णांकel_de_पढ़ो(dev_priv, PIPE_LINK_M_G4X(pipe));
		m_n->link_n = पूर्णांकel_de_पढ़ो(dev_priv, PIPE_LINK_N_G4X(pipe));
		m_n->gmch_m = पूर्णांकel_de_पढ़ो(dev_priv, PIPE_DATA_M_G4X(pipe))
			& ~TU_SIZE_MASK;
		m_n->gmch_n = पूर्णांकel_de_पढ़ो(dev_priv, PIPE_DATA_N_G4X(pipe));
		m_n->tu = ((पूर्णांकel_de_पढ़ो(dev_priv, PIPE_DATA_M_G4X(pipe))
			    & TU_SIZE_MASK) >> TU_SIZE_SHIFT) + 1;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_dp_get_m_n(काष्ठा पूर्णांकel_crtc *crtc,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	अगर (pipe_config->has_pch_encoder)
		पूर्णांकel_pch_transcoder_get_m_n(crtc, &pipe_config->dp_m_n);
	अन्यथा
		पूर्णांकel_cpu_transcoder_get_m_n(crtc, pipe_config->cpu_transcoder,
					     &pipe_config->dp_m_n,
					     &pipe_config->dp_m2_n2);
पूर्ण

अटल व्योम ilk_get_fdi_m_n_config(काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	पूर्णांकel_cpu_transcoder_get_m_n(crtc, pipe_config->cpu_transcoder,
				     &pipe_config->fdi_m_n, शून्य);
पूर्ण

अटल व्योम ilk_get_pfit_pos_size(काष्ठा पूर्णांकel_crtc_state *crtc_state,
				  u32 pos, u32 size)
अणु
	drm_rect_init(&crtc_state->pch_pfit.dst,
		      pos >> 16, pos & 0xffff,
		      size >> 16, size & 0xffff);
पूर्ण

अटल व्योम skl_get_pfit_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_scaler_state *scaler_state = &crtc_state->scaler_state;
	पूर्णांक id = -1;
	पूर्णांक i;

	/* find scaler attached to this pipe */
	क्रम (i = 0; i < crtc->num_scalers; i++) अणु
		u32 ctl, pos, size;

		ctl = पूर्णांकel_de_पढ़ो(dev_priv, SKL_PS_CTRL(crtc->pipe, i));
		अगर ((ctl & (PS_SCALER_EN | PS_PLANE_SEL_MASK)) != PS_SCALER_EN)
			जारी;

		id = i;
		crtc_state->pch_pfit.enabled = true;

		pos = पूर्णांकel_de_पढ़ो(dev_priv, SKL_PS_WIN_POS(crtc->pipe, i));
		size = पूर्णांकel_de_पढ़ो(dev_priv, SKL_PS_WIN_SZ(crtc->pipe, i));

		ilk_get_pfit_pos_size(crtc_state, pos, size);

		scaler_state->scalers[i].in_use = true;
		अवरोध;
	पूर्ण

	scaler_state->scaler_id = id;
	अगर (id >= 0)
		scaler_state->scaler_users |= (1 << SKL_CRTC_INDEX);
	अन्यथा
		scaler_state->scaler_users &= ~(1 << SKL_CRTC_INDEX);
पूर्ण

अटल व्योम ilk_get_pfit_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 ctl, pos, size;

	ctl = पूर्णांकel_de_पढ़ो(dev_priv, PF_CTL(crtc->pipe));
	अगर ((ctl & PF_ENABLE) == 0)
		वापस;

	crtc_state->pch_pfit.enabled = true;

	pos = पूर्णांकel_de_पढ़ो(dev_priv, PF_WIN_POS(crtc->pipe));
	size = पूर्णांकel_de_पढ़ो(dev_priv, PF_WIN_SZ(crtc->pipe));

	ilk_get_pfit_pos_size(crtc_state, pos, size);

	/*
	 * We currently करो not मुक्त assignements of panel fitters on
	 * ivb/hsw (since we करोn't use the higher upscaling modes which
	 * dअगरferentiates them) so just WARN about this हाल क्रम now.
	 */
	drm_WARN_ON(&dev_priv->drm, IS_DISPLAY_VER(dev_priv, 7) &&
		    (ctl & PF_PIPE_SEL_MASK_IVB) != PF_PIPE_SEL_IVB(crtc->pipe));
पूर्ण

अटल bool ilk_get_pipe_config(काष्ठा पूर्णांकel_crtc *crtc,
				काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत पूर्णांकel_display_घातer_करोमुख्य घातer_करोमुख्य;
	पूर्णांकel_wakeref_t wakeref;
	u32 पंचांगp;
	bool ret;

	घातer_करोमुख्य = POWER_DOMAIN_PIPE(crtc->pipe);
	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv, घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	pipe_config->cpu_transcoder = (क्रमागत transcoder) crtc->pipe;
	pipe_config->shared_dpll = शून्य;

	ret = false;
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(crtc->pipe));
	अगर (!(पंचांगp & PIPECONF_ENABLE))
		जाओ out;

	चयन (पंचांगp & PIPECONF_BPC_MASK) अणु
	हाल PIPECONF_6BPC:
		pipe_config->pipe_bpp = 18;
		अवरोध;
	हाल PIPECONF_8BPC:
		pipe_config->pipe_bpp = 24;
		अवरोध;
	हाल PIPECONF_10BPC:
		pipe_config->pipe_bpp = 30;
		अवरोध;
	हाल PIPECONF_12BPC:
		pipe_config->pipe_bpp = 36;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (पंचांगp & PIPECONF_COLOR_RANGE_SELECT)
		pipe_config->limited_color_range = true;

	चयन (पंचांगp & PIPECONF_OUTPUT_COLORSPACE_MASK) अणु
	हाल PIPECONF_OUTPUT_COLORSPACE_YUV601:
	हाल PIPECONF_OUTPUT_COLORSPACE_YUV709:
		pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_YCBCR444;
		अवरोध;
	शेष:
		pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;
		अवरोध;
	पूर्ण

	pipe_config->gamma_mode = (पंचांगp & PIPECONF_GAMMA_MODE_MASK_ILK) >>
		PIPECONF_GAMMA_MODE_SHIFT;

	pipe_config->csc_mode = पूर्णांकel_de_पढ़ो(dev_priv,
					      PIPE_CSC_MODE(crtc->pipe));

	i9xx_get_pipe_color_config(pipe_config);
	पूर्णांकel_color_get_config(pipe_config);

	अगर (पूर्णांकel_de_पढ़ो(dev_priv, PCH_TRANSCONF(crtc->pipe)) & TRANS_ENABLE) अणु
		काष्ठा पूर्णांकel_shared_dpll *pll;
		क्रमागत पूर्णांकel_dpll_id pll_id;
		bool pll_active;

		pipe_config->has_pch_encoder = true;

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(crtc->pipe));
		pipe_config->fdi_lanes = ((FDI_DP_PORT_WIDTH_MASK & पंचांगp) >>
					  FDI_DP_PORT_WIDTH_SHIFT) + 1;

		ilk_get_fdi_m_n_config(crtc, pipe_config);

		अगर (HAS_PCH_IBX(dev_priv)) अणु
			/*
			 * The pipe->pch transcoder and pch transcoder->pll
			 * mapping is fixed.
			 */
			pll_id = (क्रमागत पूर्णांकel_dpll_id) crtc->pipe;
		पूर्ण अन्यथा अणु
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PCH_DPLL_SEL);
			अगर (पंचांगp & TRANS_DPLLB_SEL(crtc->pipe))
				pll_id = DPLL_ID_PCH_PLL_B;
			अन्यथा
				pll_id= DPLL_ID_PCH_PLL_A;
		पूर्ण

		pipe_config->shared_dpll =
			पूर्णांकel_get_shared_dpll_by_id(dev_priv, pll_id);
		pll = pipe_config->shared_dpll;

		pll_active = पूर्णांकel_dpll_get_hw_state(dev_priv, pll,
						     &pipe_config->dpll_hw_state);
		drm_WARN_ON(dev, !pll_active);

		पंचांगp = pipe_config->dpll_hw_state.dpll;
		pipe_config->pixel_multiplier =
			((पंचांगp & PLL_REF_SDVO_HDMI_MULTIPLIER_MASK)
			 >> PLL_REF_SDVO_HDMI_MULTIPLIER_SHIFT) + 1;

		ilk_pch_घड़ी_get(crtc, pipe_config);
	पूर्ण अन्यथा अणु
		pipe_config->pixel_multiplier = 1;
	पूर्ण

	पूर्णांकel_get_transcoder_timings(crtc, pipe_config);
	पूर्णांकel_get_pipe_src_size(crtc, pipe_config);

	ilk_get_pfit_config(pipe_config);

	ret = true;

out:
	पूर्णांकel_display_घातer_put(dev_priv, घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल bool hsw_get_transcoder_state(काष्ठा पूर्णांकel_crtc *crtc,
				     काष्ठा पूर्णांकel_crtc_state *pipe_config,
				     काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	अचिन्हित दीर्घ panel_transcoder_mask = BIT(TRANSCODER_EDP);
	अचिन्हित दीर्घ enabled_panel_transcoders = 0;
	क्रमागत transcoder panel_transcoder;
	u32 पंचांगp;

	अगर (DISPLAY_VER(dev_priv) >= 11)
		panel_transcoder_mask |=
			BIT(TRANSCODER_DSI_0) | BIT(TRANSCODER_DSI_1);

	/*
	 * The pipe->transcoder mapping is fixed with the exception of the eDP
	 * and DSI transcoders handled below.
	 */
	pipe_config->cpu_transcoder = (क्रमागत transcoder) crtc->pipe;

	/*
	 * XXX: Do पूर्णांकel_display_घातer_get_अगर_enabled beक्रमe पढ़ोing this (क्रम
	 * consistency and less surprising code; it's in always on घातer).
	 */
	क्रम_each_cpu_transcoder_masked(dev_priv, panel_transcoder,
				       panel_transcoder_mask) अणु
		bool क्रमce_thru = false;
		क्रमागत pipe trans_pipe;

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
				    TRANS_DDI_FUNC_CTL(panel_transcoder));
		अगर (!(पंचांगp & TRANS_DDI_FUNC_ENABLE))
			जारी;

		/*
		 * Log all enabled ones, only use the first one.
		 *
		 * FIXME: This won't work क्रम two separate DSI displays.
		 */
		enabled_panel_transcoders |= BIT(panel_transcoder);
		अगर (enabled_panel_transcoders != BIT(panel_transcoder))
			जारी;

		चयन (पंचांगp & TRANS_DDI_EDP_INPUT_MASK) अणु
		शेष:
			drm_WARN(dev, 1,
				 "unknown pipe linked to transcoder %s\n",
				 transcoder_name(panel_transcoder));
			fallthrough;
		हाल TRANS_DDI_EDP_INPUT_A_ONOFF:
			क्रमce_thru = true;
			fallthrough;
		हाल TRANS_DDI_EDP_INPUT_A_ON:
			trans_pipe = PIPE_A;
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_B_ONOFF:
			trans_pipe = PIPE_B;
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_C_ONOFF:
			trans_pipe = PIPE_C;
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_D_ONOFF:
			trans_pipe = PIPE_D;
			अवरोध;
		पूर्ण

		अगर (trans_pipe == crtc->pipe) अणु
			pipe_config->cpu_transcoder = panel_transcoder;
			pipe_config->pch_pfit.क्रमce_thru = क्रमce_thru;
		पूर्ण
	पूर्ण

	/*
	 * Valid combos: none, eDP, DSI0, DSI1, DSI0+DSI1
	 */
	drm_WARN_ON(dev, (enabled_panel_transcoders & BIT(TRANSCODER_EDP)) &&
		    enabled_panel_transcoders != BIT(TRANSCODER_EDP));

	अगर (!पूर्णांकel_display_घातer_get_in_set_अगर_enabled(dev_priv, घातer_करोमुख्य_set,
						       POWER_DOMAIN_TRANSCODER(pipe_config->cpu_transcoder)))
		वापस false;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe_config->cpu_transcoder));

	वापस पंचांगp & PIPECONF_ENABLE;
पूर्ण

अटल bool bxt_get_dsi_transcoder_state(काष्ठा पूर्णांकel_crtc *crtc,
					 काष्ठा पूर्णांकel_crtc_state *pipe_config,
					 काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set *घातer_करोमुख्य_set)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत transcoder cpu_transcoder;
	क्रमागत port port;
	u32 पंचांगp;

	क्रम_each_port_masked(port, BIT(PORT_A) | BIT(PORT_C)) अणु
		अगर (port == PORT_A)
			cpu_transcoder = TRANSCODER_DSI_A;
		अन्यथा
			cpu_transcoder = TRANSCODER_DSI_C;

		अगर (!पूर्णांकel_display_घातer_get_in_set_अगर_enabled(dev_priv, घातer_करोमुख्य_set,
							       POWER_DOMAIN_TRANSCODER(cpu_transcoder)))
			जारी;

		/*
		 * The PLL needs to be enabled with a valid भागider
		 * configuration, otherwise accessing DSI रेजिस्टरs will hang
		 * the machine. See BSpec North Display Engine
		 * रेजिस्टरs/MIPI[BXT]. We can अवरोध out here early, since we
		 * need the same DSI PLL to be enabled क्रम both DSI ports.
		 */
		अगर (!bxt_dsi_pll_is_enabled(dev_priv))
			अवरोध;

		/* XXX: this works क्रम video mode only */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, BXT_MIPI_PORT_CTRL(port));
		अगर (!(पंचांगp & DPI_ENABLE))
			जारी;

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
		अगर ((पंचांगp & BXT_PIPE_SELECT_MASK) != BXT_PIPE_SELECT(crtc->pipe))
			जारी;

		pipe_config->cpu_transcoder = cpu_transcoder;
		अवरोध;
	पूर्ण

	वापस transcoder_is_dsi(pipe_config->cpu_transcoder);
पूर्ण

अटल व्योम hsw_get_ddi_port_state(काष्ठा पूर्णांकel_crtc *crtc,
				   काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = pipe_config->cpu_transcoder;
	क्रमागत port port;
	u32 पंचांगp;

	अगर (transcoder_is_dsi(cpu_transcoder)) अणु
		port = (cpu_transcoder == TRANSCODER_DSI_A) ?
						PORT_A : PORT_B;
	पूर्ण अन्यथा अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
				    TRANS_DDI_FUNC_CTL(cpu_transcoder));
		अगर (!(पंचांगp & TRANS_DDI_FUNC_ENABLE))
			वापस;
		अगर (DISPLAY_VER(dev_priv) >= 12)
			port = TGL_TRANS_DDI_FUNC_CTL_VAL_TO_PORT(पंचांगp);
		अन्यथा
			port = TRANS_DDI_FUNC_CTL_VAL_TO_PORT(पंचांगp);
	पूर्ण

	/*
	 * Haswell has only FDI/PCH transcoder A. It is which is connected to
	 * DDI E. So just check whether this pipe is wired to DDI E and whether
	 * the PCH transcoder is on.
	 */
	अगर (DISPLAY_VER(dev_priv) < 9 &&
	    (port == PORT_E) && पूर्णांकel_de_पढ़ो(dev_priv, LPT_TRANSCONF) & TRANS_ENABLE) अणु
		pipe_config->has_pch_encoder = true;

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, FDI_RX_CTL(PIPE_A));
		pipe_config->fdi_lanes = ((FDI_DP_PORT_WIDTH_MASK & पंचांगp) >>
					  FDI_DP_PORT_WIDTH_SHIFT) + 1;

		ilk_get_fdi_m_n_config(crtc, pipe_config);
	पूर्ण
पूर्ण

अटल bool hsw_get_pipe_config(काष्ठा पूर्णांकel_crtc *crtc,
				काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_display_घातer_करोमुख्य_set घातer_करोमुख्य_set = अणु पूर्ण;
	bool active;
	u32 पंचांगp;

	अगर (!पूर्णांकel_display_घातer_get_in_set_अगर_enabled(dev_priv, &घातer_करोमुख्य_set,
						       POWER_DOMAIN_PIPE(crtc->pipe)))
		वापस false;

	pipe_config->shared_dpll = शून्य;

	active = hsw_get_transcoder_state(crtc, pipe_config, &घातer_करोमुख्य_set);

	अगर (IS_GEN9_LP(dev_priv) &&
	    bxt_get_dsi_transcoder_state(crtc, pipe_config, &घातer_करोमुख्य_set)) अणु
		drm_WARN_ON(&dev_priv->drm, active);
		active = true;
	पूर्ण

	पूर्णांकel_dsc_get_config(pipe_config);

	अगर (!active) अणु
		/* bigjoiner slave करोesn't enable transcoder */
		अगर (!pipe_config->bigjoiner_slave)
			जाओ out;

		active = true;
		pipe_config->pixel_multiplier = 1;

		/* we cannot पढ़ो out most state, so करोn't bother.. */
		pipe_config->quirks |= PIPE_CONFIG_QUIRK_BIGJOINER_SLAVE;
	पूर्ण अन्यथा अगर (!transcoder_is_dsi(pipe_config->cpu_transcoder) ||
	    DISPLAY_VER(dev_priv) >= 11) अणु
		hsw_get_ddi_port_state(crtc, pipe_config);
		पूर्णांकel_get_transcoder_timings(crtc, pipe_config);
	पूर्ण

	अगर (HAS_VRR(dev_priv) && !transcoder_is_dsi(pipe_config->cpu_transcoder))
		पूर्णांकel_vrr_get_config(crtc, pipe_config);

	पूर्णांकel_get_pipe_src_size(crtc, pipe_config);

	अगर (IS_HASWELL(dev_priv)) अणु
		u32 पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
					PIPECONF(pipe_config->cpu_transcoder));

		अगर (पंचांगp & PIPECONF_OUTPUT_COLORSPACE_YUV_HSW)
			pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_YCBCR444;
		अन्यथा
			pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;
	पूर्ण अन्यथा अणु
		pipe_config->output_क्रमmat =
			bdw_get_pipemisc_output_क्रमmat(crtc);
	पूर्ण

	pipe_config->gamma_mode = पूर्णांकel_de_पढ़ो(dev_priv,
						GAMMA_MODE(crtc->pipe));

	pipe_config->csc_mode = पूर्णांकel_de_पढ़ो(dev_priv,
					      PIPE_CSC_MODE(crtc->pipe));

	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, SKL_BOTTOM_COLOR(crtc->pipe));

		अगर (पंचांगp & SKL_BOTTOM_COLOR_GAMMA_ENABLE)
			pipe_config->gamma_enable = true;

		अगर (पंचांगp & SKL_BOTTOM_COLOR_CSC_ENABLE)
			pipe_config->csc_enable = true;
	पूर्ण अन्यथा अणु
		i9xx_get_pipe_color_config(pipe_config);
	पूर्ण

	पूर्णांकel_color_get_config(pipe_config);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, WM_LINETIME(crtc->pipe));
	pipe_config->lineसमय = REG_FIELD_GET(HSW_LINETIME_MASK, पंचांगp);
	अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		pipe_config->ips_lineसमय =
			REG_FIELD_GET(HSW_IPS_LINETIME_MASK, पंचांगp);

	अगर (पूर्णांकel_display_घातer_get_in_set_अगर_enabled(dev_priv, &घातer_करोमुख्य_set,
						      POWER_DOMAIN_PIPE_PANEL_FITTER(crtc->pipe))) अणु
		अगर (DISPLAY_VER(dev_priv) >= 9)
			skl_get_pfit_config(pipe_config);
		अन्यथा
			ilk_get_pfit_config(pipe_config);
	पूर्ण

	अगर (hsw_crtc_supports_ips(crtc)) अणु
		अगर (IS_HASWELL(dev_priv))
			pipe_config->ips_enabled = पूर्णांकel_de_पढ़ो(dev_priv,
								 IPS_CTL) & IPS_ENABLE;
		अन्यथा अणु
			/*
			 * We cannot पढ़ोout IPS state on broadwell, set to
			 * true so we can set it to a defined state on first
			 * commit.
			 */
			pipe_config->ips_enabled = true;
		पूर्ण
	पूर्ण

	अगर (pipe_config->bigjoiner_slave) अणु
		/* Cannot be पढ़ो out as a slave, set to 0. */
		pipe_config->pixel_multiplier = 0;
	पूर्ण अन्यथा अगर (pipe_config->cpu_transcoder != TRANSCODER_EDP &&
	    !transcoder_is_dsi(pipe_config->cpu_transcoder)) अणु
		pipe_config->pixel_multiplier =
			पूर्णांकel_de_पढ़ो(dev_priv,
				      PIPE_MULT(pipe_config->cpu_transcoder)) + 1;
	पूर्ण अन्यथा अणु
		pipe_config->pixel_multiplier = 1;
	पूर्ण

out:
	पूर्णांकel_display_घातer_put_all_in_set(dev_priv, &घातer_करोमुख्य_set);

	वापस active;
पूर्ण

अटल bool पूर्णांकel_crtc_get_pipe_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);

	अगर (!i915->display.get_pipe_config(crtc, crtc_state))
		वापस false;

	crtc_state->hw.active = true;

	पूर्णांकel_crtc_पढ़ोout_derived_state(crtc_state);

	वापस true;
पूर्ण

/* VESA 640x480x72Hz mode to set on the pipe */
अटल स्थिर काष्ठा drm_display_mode load_detect_mode = अणु
	DRM_MODE("640x480", DRM_MODE_TYPE_DEFAULT, 31500, 640, 664,
		 704, 832, 0, 480, 489, 491, 520, 0, DRM_MODE_FLAG_NHSYNC | DRM_MODE_FLAG_NVSYNC),
पूर्ण;

काष्ठा drm_framebuffer *
पूर्णांकel_framebuffer_create(काष्ठा drm_i915_gem_object *obj,
			 काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb;
	पूर्णांक ret;

	पूर्णांकel_fb = kzalloc(माप(*पूर्णांकel_fb), GFP_KERNEL);
	अगर (!पूर्णांकel_fb)
		वापस ERR_PTR(-ENOMEM);

	ret = पूर्णांकel_framebuffer_init(पूर्णांकel_fb, obj, mode_cmd);
	अगर (ret)
		जाओ err;

	वापस &पूर्णांकel_fb->base;

err:
	kमुक्त(पूर्णांकel_fb);
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक पूर्णांकel_modeset_disable_planes(काष्ठा drm_atomic_state *state,
					काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा drm_plane_state *plane_state;
	पूर्णांक ret, i;

	ret = drm_atomic_add_affected_planes(state, crtc);
	अगर (ret)
		वापस ret;

	क्रम_each_new_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane_state->crtc != crtc)
			जारी;

		ret = drm_atomic_set_crtc_क्रम_plane(plane_state, शून्य);
		अगर (ret)
			वापस ret;

		drm_atomic_set_fb_क्रम_plane(plane_state, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_get_load_detect_pipe(काष्ठा drm_connector *connector,
			       काष्ठा पूर्णांकel_load_detect_pipe *old,
			       काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder =
		पूर्णांकel_attached_encoder(to_पूर्णांकel_connector(connector));
	काष्ठा drm_crtc *possible_crtc;
	काष्ठा drm_encoder *encoder = &पूर्णांकel_encoder->base;
	काष्ठा drm_crtc *crtc = शून्य;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_mode_config *config = &dev->mode_config;
	काष्ठा drm_atomic_state *state = शून्य, *restore_state = शून्य;
	काष्ठा drm_connector_state *connector_state;
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	पूर्णांक ret, i = -1;

	drm_dbg_kms(&dev_priv->drm, "[CONNECTOR:%d:%s], [ENCODER:%d:%s]\n",
		    connector->base.id, connector->name,
		    encoder->base.id, encoder->name);

	old->restore_state = शून्य;

	drm_WARN_ON(dev, !drm_modeset_is_locked(&config->connection_mutex));

	/*
	 * Algorithm माला_लो a little messy:
	 *
	 *   - अगर the connector alपढ़ोy has an asचिन्हित crtc, use it (but make
	 *     sure it's on first)
	 *
	 *   - try to find the first unused crtc that can drive this connector,
	 *     and use that अगर we find one
	 */

	/* See अगर we alपढ़ोy have a CRTC क्रम this connector */
	अगर (connector->state->crtc) अणु
		crtc = connector->state->crtc;

		ret = drm_modeset_lock(&crtc->mutex, ctx);
		अगर (ret)
			जाओ fail;

		/* Make sure the crtc and connector are running */
		जाओ found;
	पूर्ण

	/* Find an unused one (अगर possible) */
	क्रम_each_crtc(dev, possible_crtc) अणु
		i++;
		अगर (!(encoder->possible_crtcs & (1 << i)))
			जारी;

		ret = drm_modeset_lock(&possible_crtc->mutex, ctx);
		अगर (ret)
			जाओ fail;

		अगर (possible_crtc->state->enable) अणु
			drm_modeset_unlock(&possible_crtc->mutex);
			जारी;
		पूर्ण

		crtc = possible_crtc;
		अवरोध;
	पूर्ण

	/*
	 * If we didn't find an unused CRTC, don't use any.
	 */
	अगर (!crtc) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "no pipe available for load-detect\n");
		ret = -ENODEV;
		जाओ fail;
	पूर्ण

found:
	पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);

	state = drm_atomic_state_alloc(dev);
	restore_state = drm_atomic_state_alloc(dev);
	अगर (!state || !restore_state) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	state->acquire_ctx = ctx;
	restore_state->acquire_ctx = ctx;

	connector_state = drm_atomic_get_connector_state(state, connector);
	अगर (IS_ERR(connector_state)) अणु
		ret = PTR_ERR(connector_state);
		जाओ fail;
	पूर्ण

	ret = drm_atomic_set_crtc_क्रम_connector(connector_state, crtc);
	अगर (ret)
		जाओ fail;

	crtc_state = पूर्णांकel_atomic_get_crtc_state(state, पूर्णांकel_crtc);
	अगर (IS_ERR(crtc_state)) अणु
		ret = PTR_ERR(crtc_state);
		जाओ fail;
	पूर्ण

	crtc_state->uapi.active = true;

	ret = drm_atomic_set_mode_क्रम_crtc(&crtc_state->uapi,
					   &load_detect_mode);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकel_modeset_disable_planes(state, crtc);
	अगर (ret)
		जाओ fail;

	ret = PTR_ERR_OR_ZERO(drm_atomic_get_connector_state(restore_state, connector));
	अगर (!ret)
		ret = PTR_ERR_OR_ZERO(drm_atomic_get_crtc_state(restore_state, crtc));
	अगर (!ret)
		ret = drm_atomic_add_affected_planes(restore_state, crtc);
	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "Failed to create a copy of old state to restore: %i\n",
			    ret);
		जाओ fail;
	पूर्ण

	ret = drm_atomic_commit(state);
	अगर (ret) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "failed to set mode on load-detect pipe\n");
		जाओ fail;
	पूर्ण

	old->restore_state = restore_state;
	drm_atomic_state_put(state);

	/* let the connector get through one full cycle beक्रमe testing */
	पूर्णांकel_रुको_क्रम_vblank(dev_priv, पूर्णांकel_crtc->pipe);
	वापस true;

fail:
	अगर (state) अणु
		drm_atomic_state_put(state);
		state = शून्य;
	पूर्ण
	अगर (restore_state) अणु
		drm_atomic_state_put(restore_state);
		restore_state = शून्य;
	पूर्ण

	अगर (ret == -EDEADLK)
		वापस ret;

	वापस false;
पूर्ण

व्योम पूर्णांकel_release_load_detect_pipe(काष्ठा drm_connector *connector,
				    काष्ठा पूर्णांकel_load_detect_pipe *old,
				    काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder =
		पूर्णांकel_attached_encoder(to_पूर्णांकel_connector(connector));
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_encoder->base.dev);
	काष्ठा drm_encoder *encoder = &पूर्णांकel_encoder->base;
	काष्ठा drm_atomic_state *state = old->restore_state;
	पूर्णांक ret;

	drm_dbg_kms(&i915->drm, "[CONNECTOR:%d:%s], [ENCODER:%d:%s]\n",
		    connector->base.id, connector->name,
		    encoder->base.id, encoder->name);

	अगर (!state)
		वापस;

	ret = drm_atomic_helper_commit_duplicated_state(state, ctx);
	अगर (ret)
		drm_dbg_kms(&i915->drm,
			    "Couldn't release load detect pipe: %i\n", ret);
	drm_atomic_state_put(state);
पूर्ण

अटल पूर्णांक i9xx_pll_refclk(काष्ठा drm_device *dev,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 dpll = pipe_config->dpll_hw_state.dpll;

	अगर ((dpll & PLL_REF_INPUT_MASK) == PLLB_REF_INPUT_SPREADSPECTRUMIN)
		वापस dev_priv->vbt.lvds_ssc_freq;
	अन्यथा अगर (HAS_PCH_SPLIT(dev_priv))
		वापस 120000;
	अन्यथा अगर (!IS_DISPLAY_VER(dev_priv, 2))
		वापस 96000;
	अन्यथा
		वापस 48000;
पूर्ण

/* Returns the घड़ी of the currently programmed mode of the given pipe. */
अटल व्योम i9xx_crtc_घड़ी_get(काष्ठा पूर्णांकel_crtc *crtc,
				काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 dpll = pipe_config->dpll_hw_state.dpll;
	u32 fp;
	काष्ठा dpll घड़ी;
	पूर्णांक port_घड़ी;
	पूर्णांक refclk = i9xx_pll_refclk(dev, pipe_config);

	अगर ((dpll & DISPLAY_RATE_SELECT_FPA1) == 0)
		fp = pipe_config->dpll_hw_state.fp0;
	अन्यथा
		fp = pipe_config->dpll_hw_state.fp1;

	घड़ी.m1 = (fp & FP_M1_DIV_MASK) >> FP_M1_DIV_SHIFT;
	अगर (IS_PINEVIEW(dev_priv)) अणु
		घड़ी.n = ffs((fp & FP_N_PINEVIEW_DIV_MASK) >> FP_N_DIV_SHIFT) - 1;
		घड़ी.m2 = (fp & FP_M2_PINEVIEW_DIV_MASK) >> FP_M2_DIV_SHIFT;
	पूर्ण अन्यथा अणु
		घड़ी.n = (fp & FP_N_DIV_MASK) >> FP_N_DIV_SHIFT;
		घड़ी.m2 = (fp & FP_M2_DIV_MASK) >> FP_M2_DIV_SHIFT;
	पूर्ण

	अगर (!IS_DISPLAY_VER(dev_priv, 2)) अणु
		अगर (IS_PINEVIEW(dev_priv))
			घड़ी.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK_PINEVIEW) >>
				DPLL_FPA01_P1_POST_DIV_SHIFT_PINEVIEW);
		अन्यथा
			घड़ी.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK) >>
			       DPLL_FPA01_P1_POST_DIV_SHIFT);

		चयन (dpll & DPLL_MODE_MASK) अणु
		हाल DPLLB_MODE_DAC_SERIAL:
			घड़ी.p2 = dpll & DPLL_DAC_SERIAL_P2_CLOCK_DIV_5 ?
				5 : 10;
			अवरोध;
		हाल DPLLB_MODE_LVDS:
			घड़ी.p2 = dpll & DPLLB_LVDS_P2_CLOCK_DIV_7 ?
				7 : 14;
			अवरोध;
		शेष:
			drm_dbg_kms(&dev_priv->drm,
				    "Unknown DPLL mode %08x in programmed "
				    "mode\n", (पूर्णांक)(dpll & DPLL_MODE_MASK));
			वापस;
		पूर्ण

		अगर (IS_PINEVIEW(dev_priv))
			port_घड़ी = pnv_calc_dpll_params(refclk, &घड़ी);
		अन्यथा
			port_घड़ी = i9xx_calc_dpll_params(refclk, &घड़ी);
	पूर्ण अन्यथा अणु
		u32 lvds = IS_I830(dev_priv) ? 0 : पूर्णांकel_de_पढ़ो(dev_priv,
								 LVDS);
		bool is_lvds = (pipe == 1) && (lvds & LVDS_PORT_EN);

		अगर (is_lvds) अणु
			घड़ी.p1 = ffs((dpll & DPLL_FPA01_P1_POST_DIV_MASK_I830_LVDS) >>
				       DPLL_FPA01_P1_POST_DIV_SHIFT);

			अगर (lvds & LVDS_CLKB_POWER_UP)
				घड़ी.p2 = 7;
			अन्यथा
				घड़ी.p2 = 14;
		पूर्ण अन्यथा अणु
			अगर (dpll & PLL_P1_DIVIDE_BY_TWO)
				घड़ी.p1 = 2;
			अन्यथा अणु
				घड़ी.p1 = ((dpll & DPLL_FPA01_P1_POST_DIV_MASK_I830) >>
					    DPLL_FPA01_P1_POST_DIV_SHIFT) + 2;
			पूर्ण
			अगर (dpll & PLL_P2_DIVIDE_BY_4)
				घड़ी.p2 = 4;
			अन्यथा
				घड़ी.p2 = 2;
		पूर्ण

		port_घड़ी = i9xx_calc_dpll_params(refclk, &घड़ी);
	पूर्ण

	/*
	 * This value includes pixel_multiplier. We will use
	 * port_घड़ी to compute adjusted_mode.crtc_घड़ी in the
	 * encoder's get_config() function.
	 */
	pipe_config->port_घड़ी = port_घड़ी;
पूर्ण

पूर्णांक पूर्णांकel_करोtघड़ी_calculate(पूर्णांक link_freq,
			     स्थिर काष्ठा पूर्णांकel_link_m_n *m_n)
अणु
	/*
	 * The calculation क्रम the data घड़ी is:
	 * pixel_घड़ी = ((m/n)*(link_घड़ी * nr_lanes))/bpp
	 * But we want to aव्योम losing precison अगर possible, so:
	 * pixel_घड़ी = ((m * link_घड़ी * nr_lanes)/(n*bpp))
	 *
	 * and the link घड़ी is simpler:
	 * link_घड़ी = (m * link_घड़ी) / n
	 */

	अगर (!m_n->link_n)
		वापस 0;

	वापस भाग_u64(mul_u32_u32(m_n->link_m, link_freq), m_n->link_n);
पूर्ण

अटल व्योम ilk_pch_घड़ी_get(काष्ठा पूर्णांकel_crtc *crtc,
			      काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	/* पढ़ो out port_घड़ी from the DPLL */
	i9xx_crtc_घड़ी_get(crtc, pipe_config);

	/*
	 * In हाल there is an active pipe without active ports,
	 * we may need some idea क्रम the करोtघड़ी anyway.
	 * Calculate one based on the FDI configuration.
	 */
	pipe_config->hw.adjusted_mode.crtc_घड़ी =
		पूर्णांकel_करोtघड़ी_calculate(पूर्णांकel_fdi_link_freq(dev_priv, pipe_config),
					 &pipe_config->fdi_m_n);
पूर्ण

/* Returns the currently programmed mode of the given encoder. */
काष्ठा drm_display_mode *
पूर्णांकel_encoder_current_mode(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा drm_display_mode *mode;
	काष्ठा पूर्णांकel_crtc *crtc;
	क्रमागत pipe pipe;

	अगर (!encoder->get_hw_state(encoder, &pipe))
		वापस शून्य;

	crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

	mode = kzalloc(माप(*mode), GFP_KERNEL);
	अगर (!mode)
		वापस शून्य;

	crtc_state = पूर्णांकel_crtc_state_alloc(crtc);
	अगर (!crtc_state) अणु
		kमुक्त(mode);
		वापस शून्य;
	पूर्ण

	अगर (!पूर्णांकel_crtc_get_pipe_config(crtc_state)) अणु
		kमुक्त(crtc_state);
		kमुक्त(mode);
		वापस शून्य;
	पूर्ण

	पूर्णांकel_encoder_get_config(encoder, crtc_state);

	पूर्णांकel_mode_from_crtc_timings(mode, &crtc_state->hw.adjusted_mode);

	kमुक्त(crtc_state);

	वापस mode;
पूर्ण

/**
 * पूर्णांकel_wm_need_update - Check whether watermarks need updating
 * @cur: current plane state
 * @new: new plane state
 *
 * Check current plane state versus the new one to determine whether
 * watermarks need to be recalculated.
 *
 * Returns true or false.
 */
अटल bool पूर्णांकel_wm_need_update(स्थिर काष्ठा पूर्णांकel_plane_state *cur,
				 काष्ठा पूर्णांकel_plane_state *new)
अणु
	/* Update watermarks on tiling or size changes. */
	अगर (new->uapi.visible != cur->uapi.visible)
		वापस true;

	अगर (!cur->hw.fb || !new->hw.fb)
		वापस false;

	अगर (cur->hw.fb->modअगरier != new->hw.fb->modअगरier ||
	    cur->hw.rotation != new->hw.rotation ||
	    drm_rect_width(&new->uapi.src) != drm_rect_width(&cur->uapi.src) ||
	    drm_rect_height(&new->uapi.src) != drm_rect_height(&cur->uapi.src) ||
	    drm_rect_width(&new->uapi.dst) != drm_rect_width(&cur->uapi.dst) ||
	    drm_rect_height(&new->uapi.dst) != drm_rect_height(&cur->uapi.dst))
		वापस true;

	वापस false;
पूर्ण

अटल bool needs_scaling(स्थिर काष्ठा पूर्णांकel_plane_state *state)
अणु
	पूर्णांक src_w = drm_rect_width(&state->uapi.src) >> 16;
	पूर्णांक src_h = drm_rect_height(&state->uapi.src) >> 16;
	पूर्णांक dst_w = drm_rect_width(&state->uapi.dst);
	पूर्णांक dst_h = drm_rect_height(&state->uapi.dst);

	वापस (src_w != dst_w || src_h != dst_h);
पूर्ण

पूर्णांक पूर्णांकel_plane_atomic_calc_changes(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    काष्ठा पूर्णांकel_crtc_state *crtc_state,
				    स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state,
				    काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	bool mode_changed = पूर्णांकel_crtc_needs_modeset(crtc_state);
	bool was_crtc_enabled = old_crtc_state->hw.active;
	bool is_crtc_enabled = crtc_state->hw.active;
	bool turn_off, turn_on, visible, was_visible;
	पूर्णांक ret;

	अगर (DISPLAY_VER(dev_priv) >= 9 && plane->id != PLANE_CURSOR) अणु
		ret = skl_update_scaler_plane(crtc_state, plane_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	was_visible = old_plane_state->uapi.visible;
	visible = plane_state->uapi.visible;

	अगर (!was_crtc_enabled && drm_WARN_ON(&dev_priv->drm, was_visible))
		was_visible = false;

	/*
	 * Visibility is calculated as अगर the crtc was on, but
	 * after scaler setup everything depends on it being off
	 * when the crtc isn't active.
	 *
	 * FIXME this is wrong क्रम watermarks. Watermarks should also
	 * be computed as अगर the pipe would be active. Perhaps move
	 * per-plane wm computation to the .check_plane() hook, and
	 * only combine the results from all planes in the current place?
	 */
	अगर (!is_crtc_enabled) अणु
		पूर्णांकel_plane_set_invisible(crtc_state, plane_state);
		visible = false;
	पूर्ण

	अगर (!was_visible && !visible)
		वापस 0;

	turn_off = was_visible && (!visible || mode_changed);
	turn_on = visible && (!was_visible || mode_changed);

	drm_dbg_atomic(&dev_priv->drm,
		       "[CRTC:%d:%s] with [PLANE:%d:%s] visible %i -> %i, off %i, on %i, ms %i\n",
		       crtc->base.base.id, crtc->base.name,
		       plane->base.base.id, plane->base.name,
		       was_visible, visible,
		       turn_off, turn_on, mode_changed);

	अगर (turn_on) अणु
		अगर (DISPLAY_VER(dev_priv) < 5 && !IS_G4X(dev_priv))
			crtc_state->update_wm_pre = true;

		/* must disable cxsr around plane enable/disable */
		अगर (plane->id != PLANE_CURSOR)
			crtc_state->disable_cxsr = true;
	पूर्ण अन्यथा अगर (turn_off) अणु
		अगर (DISPLAY_VER(dev_priv) < 5 && !IS_G4X(dev_priv))
			crtc_state->update_wm_post = true;

		/* must disable cxsr around plane enable/disable */
		अगर (plane->id != PLANE_CURSOR)
			crtc_state->disable_cxsr = true;
	पूर्ण अन्यथा अगर (पूर्णांकel_wm_need_update(old_plane_state, plane_state)) अणु
		अगर (DISPLAY_VER(dev_priv) < 5 && !IS_G4X(dev_priv)) अणु
			/* FIXME bollocks */
			crtc_state->update_wm_pre = true;
			crtc_state->update_wm_post = true;
		पूर्ण
	पूर्ण

	अगर (visible || was_visible)
		crtc_state->fb_bits |= plane->frontbuffer_bit;

	/*
	 * ILK/SNB DVSACNTR/Sprite Enable
	 * IVB SPR_CTL/Sprite Enable
	 * "When in Self Refresh Big FIFO mode, a ग_लिखो to enable the
	 *  plane will be पूर्णांकernally buffered and delayed जबतक Big FIFO
	 *  mode is निकासing."
	 *
	 * Which means that enabling the sprite can take an extra frame
	 * when we start in big FIFO mode (LP1+). Thus we need to drop
	 * करोwn to LP0 and रुको क्रम vblank in order to make sure the
	 * sprite माला_लो enabled on the next vblank after the रेजिस्टर ग_लिखो.
	 * Doing otherwise would risk enabling the sprite one frame after
	 * we've alपढ़ोy संकेतled flip completion. We can resume LP1+
	 * once the sprite has been enabled.
	 *
	 *
	 * WaCxSRDisabledForSpriteScaling:ivb
	 * IVB SPR_SCALE/Scaling Enable
	 * "Low Power watermarks must be disabled क्रम at least one
	 *  frame beक्रमe enabling sprite scaling, and kept disabled
	 *  until sprite scaling is disabled."
	 *
	 * ILK/SNB DVSASCALE/Scaling Enable
	 * "When in Self Refresh Big FIFO mode, scaling enable will be
	 *  masked off जबतक Big FIFO mode is निकासing."
	 *
	 * Despite the w/a only being listed क्रम IVB we assume that
	 * the ILK/SNB note has similar ramअगरications, hence we apply
	 * the w/a on all three platक्रमms.
	 *
	 * With experimental results seems this is needed also क्रम primary
	 * plane, not only sprite plane.
	 */
	अगर (plane->id != PLANE_CURSOR &&
	    (IS_IRONLAKE(dev_priv) || IS_SANDYBRIDGE(dev_priv) ||
	     IS_IVYBRIDGE(dev_priv)) &&
	    (turn_on || (!needs_scaling(old_plane_state) &&
			 needs_scaling(plane_state))))
		crtc_state->disable_lp_wm = true;

	वापस 0;
पूर्ण

अटल bool encoders_cloneable(स्थिर काष्ठा पूर्णांकel_encoder *a,
			       स्थिर काष्ठा पूर्णांकel_encoder *b)
अणु
	/* masks could be asymmetric, so check both ways */
	वापस a == b || (a->cloneable & (1 << b->type) &&
			  b->cloneable & (1 << a->type));
पूर्ण

अटल bool check_single_encoder_cloning(काष्ठा पूर्णांकel_atomic_state *state,
					 काष्ठा पूर्णांकel_crtc *crtc,
					 काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_encoder *source_encoder;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *connector_state;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, connector, connector_state, i) अणु
		अगर (connector_state->crtc != &crtc->base)
			जारी;

		source_encoder =
			to_पूर्णांकel_encoder(connector_state->best_encoder);
		अगर (!encoders_cloneable(encoder, source_encoder))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक icl_add_linked_planes(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_plane *plane, *linked;
	काष्ठा पूर्णांकel_plane_state *plane_state, *linked_plane_state;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		linked = plane_state->planar_linked_plane;

		अगर (!linked)
			जारी;

		linked_plane_state = पूर्णांकel_atomic_get_plane_state(state, linked);
		अगर (IS_ERR(linked_plane_state))
			वापस PTR_ERR(linked_plane_state);

		drm_WARN_ON(state->base.dev,
			    linked_plane_state->planar_linked_plane != plane);
		drm_WARN_ON(state->base.dev,
			    linked_plane_state->planar_slave == plane_state->planar_slave);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक icl_check_nv12_planes(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(crtc_state->uapi.state);
	काष्ठा पूर्णांकel_plane *plane, *linked;
	काष्ठा पूर्णांकel_plane_state *plane_state;
	पूर्णांक i;

	अगर (DISPLAY_VER(dev_priv) < 11)
		वापस 0;

	/*
	 * Destroy all old plane links and make the slave plane invisible
	 * in the crtc_state->active_planes mask.
	 */
	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane->pipe != crtc->pipe || !plane_state->planar_linked_plane)
			जारी;

		plane_state->planar_linked_plane = शून्य;
		अगर (plane_state->planar_slave && !plane_state->uapi.visible) अणु
			crtc_state->enabled_planes &= ~BIT(plane->id);
			crtc_state->active_planes &= ~BIT(plane->id);
			crtc_state->update_planes |= BIT(plane->id);
		पूर्ण

		plane_state->planar_slave = false;
	पूर्ण

	अगर (!crtc_state->nv12_planes)
		वापस 0;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		काष्ठा पूर्णांकel_plane_state *linked_state = शून्य;

		अगर (plane->pipe != crtc->pipe ||
		    !(crtc_state->nv12_planes & BIT(plane->id)))
			जारी;

		क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, linked) अणु
			अगर (!icl_is_nv12_y_plane(dev_priv, linked->id))
				जारी;

			अगर (crtc_state->active_planes & BIT(linked->id))
				जारी;

			linked_state = पूर्णांकel_atomic_get_plane_state(state, linked);
			अगर (IS_ERR(linked_state))
				वापस PTR_ERR(linked_state);

			अवरोध;
		पूर्ण

		अगर (!linked_state) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Need %d free Y planes for planar YUV\n",
				    hweight8(crtc_state->nv12_planes));

			वापस -EINVAL;
		पूर्ण

		plane_state->planar_linked_plane = linked;

		linked_state->planar_slave = true;
		linked_state->planar_linked_plane = plane;
		crtc_state->enabled_planes |= BIT(linked->id);
		crtc_state->active_planes |= BIT(linked->id);
		crtc_state->update_planes |= BIT(linked->id);
		drm_dbg_kms(&dev_priv->drm, "Using %s as Y plane for %s\n",
			    linked->base.name, plane->base.name);

		/* Copy parameters to slave plane */
		linked_state->ctl = plane_state->ctl | PLANE_CTL_YUV420_Y_PLANE;
		linked_state->color_ctl = plane_state->color_ctl;
		linked_state->view = plane_state->view;

		पूर्णांकel_plane_copy_hw_state(linked_state, plane_state);
		linked_state->uapi.src = plane_state->uapi.src;
		linked_state->uapi.dst = plane_state->uapi.dst;

		अगर (icl_is_hdr_plane(dev_priv, plane->id)) अणु
			अगर (linked->id == PLANE_SPRITE5)
				plane_state->cus_ctl |= PLANE_CUS_PLANE_7;
			अन्यथा अगर (linked->id == PLANE_SPRITE4)
				plane_state->cus_ctl |= PLANE_CUS_PLANE_6;
			अन्यथा अगर (linked->id == PLANE_SPRITE3)
				plane_state->cus_ctl |= PLANE_CUS_PLANE_5_RKL;
			अन्यथा अगर (linked->id == PLANE_SPRITE2)
				plane_state->cus_ctl |= PLANE_CUS_PLANE_4_RKL;
			अन्यथा
				MISSING_CASE(linked->id);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool c8_planes_changed(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);

	वापस !old_crtc_state->c8_planes != !new_crtc_state->c8_planes;
पूर्ण

अटल u16 hsw_lineसमय_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा drm_display_mode *pipe_mode =
		&crtc_state->hw.pipe_mode;
	पूर्णांक lineसमय_wm;

	अगर (!crtc_state->hw.enable)
		वापस 0;

	lineसमय_wm = DIV_ROUND_CLOSEST(pipe_mode->crtc_htotal * 1000 * 8,
					pipe_mode->crtc_घड़ी);

	वापस min(lineसमय_wm, 0x1ff);
पूर्ण

अटल u16 hsw_ips_lineसमय_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा पूर्णांकel_cdclk_state *cdclk_state)
अणु
	स्थिर काष्ठा drm_display_mode *pipe_mode =
		&crtc_state->hw.pipe_mode;
	पूर्णांक lineसमय_wm;

	अगर (!crtc_state->hw.enable)
		वापस 0;

	lineसमय_wm = DIV_ROUND_CLOSEST(pipe_mode->crtc_htotal * 1000 * 8,
					cdclk_state->logical.cdclk);

	वापस min(lineसमय_wm, 0x1ff);
पूर्ण

अटल u16 skl_lineसमय_wm(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_display_mode *pipe_mode =
		&crtc_state->hw.pipe_mode;
	पूर्णांक lineसमय_wm;

	अगर (!crtc_state->hw.enable)
		वापस 0;

	lineसमय_wm = DIV_ROUND_UP(pipe_mode->crtc_htotal * 1000 * 8,
				   crtc_state->pixel_rate);

	/* Display WA #1135: BXT:ALL GLK:ALL */
	अगर (IS_GEN9_LP(dev_priv) && dev_priv->ipc_enabled)
		lineसमय_wm /= 2;

	वापस min(lineसमय_wm, 0x1ff);
पूर्ण

अटल पूर्णांक hsw_compute_lineसमय_wm(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *cdclk_state;

	अगर (DISPLAY_VER(dev_priv) >= 9)
		crtc_state->lineसमय = skl_lineसमय_wm(crtc_state);
	अन्यथा
		crtc_state->lineसमय = hsw_lineसमय_wm(crtc_state);

	अगर (!hsw_crtc_supports_ips(crtc))
		वापस 0;

	cdclk_state = पूर्णांकel_atomic_get_cdclk_state(state);
	अगर (IS_ERR(cdclk_state))
		वापस PTR_ERR(cdclk_state);

	crtc_state->ips_lineसमय = hsw_ips_lineसमय_wm(crtc_state,
						       cdclk_state);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_crtc_atomic_check(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	bool mode_changed = पूर्णांकel_crtc_needs_modeset(crtc_state);
	पूर्णांक ret;

	अगर (DISPLAY_VER(dev_priv) < 5 && !IS_G4X(dev_priv) &&
	    mode_changed && !crtc_state->hw.active)
		crtc_state->update_wm_post = true;

	अगर (mode_changed && crtc_state->hw.enable &&
	    dev_priv->display.crtc_compute_घड़ी &&
	    !crtc_state->bigjoiner_slave &&
	    !drm_WARN_ON(&dev_priv->drm, crtc_state->shared_dpll)) अणु
		ret = dev_priv->display.crtc_compute_घड़ी(crtc, crtc_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * May need to update pipe gamma enable bits
	 * when C8 planes are getting enabled/disabled.
	 */
	अगर (c8_planes_changed(crtc_state))
		crtc_state->uapi.color_mgmt_changed = true;

	अगर (mode_changed || crtc_state->update_pipe ||
	    crtc_state->uapi.color_mgmt_changed) अणु
		ret = पूर्णांकel_color_check(crtc_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev_priv->display.compute_pipe_wm) अणु
		ret = dev_priv->display.compute_pipe_wm(crtc_state);
		अगर (ret) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "Target pipe watermarks are invalid\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (dev_priv->display.compute_पूर्णांकermediate_wm) अणु
		अगर (drm_WARN_ON(&dev_priv->drm,
				!dev_priv->display.compute_pipe_wm))
			वापस 0;

		/*
		 * Calculate 'intermediate' watermarks that satisfy both the
		 * old state and the new state.  We can program these
		 * immediately.
		 */
		ret = dev_priv->display.compute_पूर्णांकermediate_wm(crtc_state);
		अगर (ret) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "No valid intermediate pipe watermarks are possible\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		अगर (mode_changed || crtc_state->update_pipe) अणु
			ret = skl_update_scaler_crtc(crtc_state);
			अगर (ret)
				वापस ret;
		पूर्ण

		ret = पूर्णांकel_atomic_setup_scalers(dev_priv, crtc, crtc_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (HAS_IPS(dev_priv)) अणु
		ret = hsw_compute_ips_config(crtc_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (DISPLAY_VER(dev_priv) >= 9 ||
	    IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv)) अणु
		ret = hsw_compute_lineसमय_wm(state, crtc);
		अगर (ret)
			वापस ret;

	पूर्ण

	अगर (!mode_changed) अणु
		ret = पूर्णांकel_psr2_sel_fetch_update(state, crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_modeset_update_connector_atomic_state(काष्ठा drm_device *dev)
अणु
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	drm_connector_list_iter_begin(dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_connector_state *conn_state = connector->base.state;
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(connector->base.encoder);

		अगर (conn_state->crtc)
			drm_connector_put(&connector->base);

		अगर (encoder) अणु
			काष्ठा पूर्णांकel_crtc *crtc =
				to_पूर्णांकel_crtc(encoder->base.crtc);
			स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
				to_पूर्णांकel_crtc_state(crtc->base.state);

			conn_state->best_encoder = &encoder->base;
			conn_state->crtc = &crtc->base;
			conn_state->max_bpc = (crtc_state->pipe_bpp ?: 24) / 3;

			drm_connector_get(&connector->base);
		पूर्ण अन्यथा अणु
			conn_state->best_encoder = शून्य;
			conn_state->crtc = शून्य;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
पूर्ण

अटल पूर्णांक
compute_sink_pipe_bpp(स्थिर काष्ठा drm_connector_state *conn_state,
		      काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_connector *connector = conn_state->connector;
	काष्ठा drm_i915_निजी *i915 = to_i915(pipe_config->uapi.crtc->dev);
	स्थिर काष्ठा drm_display_info *info = &connector->display_info;
	पूर्णांक bpp;

	चयन (conn_state->max_bpc) अणु
	हाल 6 ... 7:
		bpp = 6 * 3;
		अवरोध;
	हाल 8 ... 9:
		bpp = 8 * 3;
		अवरोध;
	हाल 10 ... 11:
		bpp = 10 * 3;
		अवरोध;
	हाल 12 ... 16:
		bpp = 12 * 3;
		अवरोध;
	शेष:
		MISSING_CASE(conn_state->max_bpc);
		वापस -EINVAL;
	पूर्ण

	अगर (bpp < pipe_config->pipe_bpp) अणु
		drm_dbg_kms(&i915->drm,
			    "[CONNECTOR:%d:%s] Limiting display bpp to %d instead of "
			    "EDID bpp %d, requested bpp %d, max platform bpp %d\n",
			    connector->base.id, connector->name,
			    bpp, 3 * info->bpc,
			    3 * conn_state->max_requested_bpc,
			    pipe_config->pipe_bpp);

		pipe_config->pipe_bpp = bpp;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
compute_baseline_pipe_bpp(काष्ठा पूर्णांकel_crtc *crtc,
			  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा drm_atomic_state *state = pipe_config->uapi.state;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *connector_state;
	पूर्णांक bpp, i;

	अगर ((IS_G4X(dev_priv) || IS_VALLEYVIEW(dev_priv) ||
	    IS_CHERRYVIEW(dev_priv)))
		bpp = 10*3;
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 5)
		bpp = 12*3;
	अन्यथा
		bpp = 8*3;

	pipe_config->pipe_bpp = bpp;

	/* Clamp display bpp to connector max bpp */
	क्रम_each_new_connector_in_state(state, connector, connector_state, i) अणु
		पूर्णांक ret;

		अगर (connector_state->crtc != &crtc->base)
			जारी;

		ret = compute_sink_pipe_bpp(connector_state, pipe_config);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_dump_crtc_timings(काष्ठा drm_i915_निजी *i915,
				    स्थिर काष्ठा drm_display_mode *mode)
अणु
	drm_dbg_kms(&i915->drm, "crtc timings: %d %d %d %d %d %d %d %d %d, "
		    "type: 0x%x flags: 0x%x\n",
		    mode->crtc_घड़ी,
		    mode->crtc_hdisplay, mode->crtc_hsync_start,
		    mode->crtc_hsync_end, mode->crtc_htotal,
		    mode->crtc_vdisplay, mode->crtc_vsync_start,
		    mode->crtc_vsync_end, mode->crtc_vtotal,
		    mode->type, mode->flags);
पूर्ण

अटल व्योम
पूर्णांकel_dump_m_n_config(स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
		      स्थिर अक्षर *id, अचिन्हित पूर्णांक lane_count,
		      स्थिर काष्ठा पूर्णांकel_link_m_n *m_n)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(pipe_config->uapi.crtc->dev);

	drm_dbg_kms(&i915->drm,
		    "%s: lanes: %i; gmch_m: %u, gmch_n: %u, link_m: %u, link_n: %u, tu: %u\n",
		    id, lane_count,
		    m_n->gmch_m, m_n->gmch_n,
		    m_n->link_m, m_n->link_n, m_n->tu);
पूर्ण

अटल व्योम
पूर्णांकel_dump_infoframe(काष्ठा drm_i915_निजी *dev_priv,
		     स्थिर जोड़ hdmi_infoframe *frame)
अणु
	अगर (!drm_debug_enabled(DRM_UT_KMS))
		वापस;

	hdmi_infoframe_log(KERN_DEBUG, dev_priv->drm.dev, frame);
पूर्ण

अटल व्योम
पूर्णांकel_dump_dp_vsc_sdp(काष्ठा drm_i915_निजी *dev_priv,
		      स्थिर काष्ठा drm_dp_vsc_sdp *vsc)
अणु
	अगर (!drm_debug_enabled(DRM_UT_KMS))
		वापस;

	drm_dp_vsc_sdp_log(KERN_DEBUG, dev_priv->drm.dev, vsc);
पूर्ण

#घोषणा OUTPUT_TYPE(x) [INTEL_OUTPUT_ ## x] = #x

अटल स्थिर अक्षर * स्थिर output_type_str[] = अणु
	OUTPUT_TYPE(UNUSED),
	OUTPUT_TYPE(ANALOG),
	OUTPUT_TYPE(DVO),
	OUTPUT_TYPE(SDVO),
	OUTPUT_TYPE(LVDS),
	OUTPUT_TYPE(TVOUT),
	OUTPUT_TYPE(HDMI),
	OUTPUT_TYPE(DP),
	OUTPUT_TYPE(EDP),
	OUTPUT_TYPE(DSI),
	OUTPUT_TYPE(DDI),
	OUTPUT_TYPE(DP_MST),
पूर्ण;

#अघोषित OUTPUT_TYPE

अटल व्योम snम_लिखो_output_types(अक्षर *buf, माप_प्रकार len,
				  अचिन्हित पूर्णांक output_types)
अणु
	अक्षर *str = buf;
	पूर्णांक i;

	str[0] = '\0';

	क्रम (i = 0; i < ARRAY_SIZE(output_type_str); i++) अणु
		पूर्णांक r;

		अगर ((output_types & BIT(i)) == 0)
			जारी;

		r = snम_लिखो(str, len, "%s%s",
			     str != buf ? "," : "", output_type_str[i]);
		अगर (r >= len)
			अवरोध;
		str += r;
		len -= r;

		output_types &= ~BIT(i);
	पूर्ण

	WARN_ON_ONCE(output_types != 0);
पूर्ण

अटल स्थिर अक्षर * स्थिर output_क्रमmat_str[] = अणु
	[INTEL_OUTPUT_FORMAT_RGB] = "RGB",
	[INTEL_OUTPUT_FORMAT_YCBCR420] = "YCBCR4:2:0",
	[INTEL_OUTPUT_FORMAT_YCBCR444] = "YCBCR4:4:4",
पूर्ण;

अटल स्थिर अक्षर *output_क्रमmats(क्रमागत पूर्णांकel_output_क्रमmat क्रमmat)
अणु
	अगर (क्रमmat >= ARRAY_SIZE(output_क्रमmat_str))
		वापस "invalid";
	वापस output_क्रमmat_str[क्रमmat];
पूर्ण

अटल व्योम पूर्णांकel_dump_plane_state(स्थिर काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *i915 = to_i915(plane->base.dev);
	स्थिर काष्ठा drm_framebuffer *fb = plane_state->hw.fb;

	अगर (!fb) अणु
		drm_dbg_kms(&i915->drm,
			    "[PLANE:%d:%s] fb: [NOFB], visible: %s\n",
			    plane->base.base.id, plane->base.name,
			    yesno(plane_state->uapi.visible));
		वापस;
	पूर्ण

	drm_dbg_kms(&i915->drm,
		    "[PLANE:%d:%s] fb: [FB:%d] %ux%u format = %p4cc modifier = 0x%llx, visible: %s\n",
		    plane->base.base.id, plane->base.name,
		    fb->base.id, fb->width, fb->height, &fb->क्रमmat->क्रमmat,
		    fb->modअगरier, yesno(plane_state->uapi.visible));
	drm_dbg_kms(&i915->drm, "\trotation: 0x%x, scaler: %d\n",
		    plane_state->hw.rotation, plane_state->scaler_id);
	अगर (plane_state->uapi.visible)
		drm_dbg_kms(&i915->drm,
			    "\tsrc: " DRM_RECT_FP_FMT " dst: " DRM_RECT_FMT "\n",
			    DRM_RECT_FP_ARG(&plane_state->uapi.src),
			    DRM_RECT_ARG(&plane_state->uapi.dst));
पूर्ण

अटल व्योम पूर्णांकel_dump_pipe_config(स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				   काष्ठा पूर्णांकel_atomic_state *state,
				   स्थिर अक्षर *context)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	अक्षर buf[64];
	पूर्णांक i;

	drm_dbg_kms(&dev_priv->drm, "[CRTC:%d:%s] enable: %s %s\n",
		    crtc->base.base.id, crtc->base.name,
		    yesno(pipe_config->hw.enable), context);

	अगर (!pipe_config->hw.enable)
		जाओ dump_planes;

	snम_लिखो_output_types(buf, माप(buf), pipe_config->output_types);
	drm_dbg_kms(&dev_priv->drm,
		    "active: %s, output_types: %s (0x%x), output format: %s\n",
		    yesno(pipe_config->hw.active),
		    buf, pipe_config->output_types,
		    output_क्रमmats(pipe_config->output_क्रमmat));

	drm_dbg_kms(&dev_priv->drm,
		    "cpu_transcoder: %s, pipe bpp: %i, dithering: %i\n",
		    transcoder_name(pipe_config->cpu_transcoder),
		    pipe_config->pipe_bpp, pipe_config->dither);

	drm_dbg_kms(&dev_priv->drm, "MST master transcoder: %s\n",
		    transcoder_name(pipe_config->mst_master_transcoder));

	drm_dbg_kms(&dev_priv->drm,
		    "port sync: master transcoder: %s, slave transcoder bitmask = 0x%x\n",
		    transcoder_name(pipe_config->master_transcoder),
		    pipe_config->sync_mode_slaves_mask);

	drm_dbg_kms(&dev_priv->drm, "bigjoiner: %s\n",
		    pipe_config->bigjoiner_slave ? "slave" :
		    pipe_config->bigjoiner ? "master" : "no");

	drm_dbg_kms(&dev_priv->drm, "splitter: %s, link count %d, overlap %d\n",
		    enableddisabled(pipe_config->splitter.enable),
		    pipe_config->splitter.link_count,
		    pipe_config->splitter.pixel_overlap);

	अगर (pipe_config->has_pch_encoder)
		पूर्णांकel_dump_m_n_config(pipe_config, "fdi",
				      pipe_config->fdi_lanes,
				      &pipe_config->fdi_m_n);

	अगर (पूर्णांकel_crtc_has_dp_encoder(pipe_config)) अणु
		पूर्णांकel_dump_m_n_config(pipe_config, "dp m_n",
				pipe_config->lane_count, &pipe_config->dp_m_n);
		अगर (pipe_config->has_drrs)
			पूर्णांकel_dump_m_n_config(pipe_config, "dp m2_n2",
					      pipe_config->lane_count,
					      &pipe_config->dp_m2_n2);
	पूर्ण

	drm_dbg_kms(&dev_priv->drm,
		    "audio: %i, infoframes: %i, infoframes enabled: 0x%x\n",
		    pipe_config->has_audio, pipe_config->has_infoframe,
		    pipe_config->infoframes.enable);

	अगर (pipe_config->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(HDMI_PACKET_TYPE_GENERAL_CONTROL))
		drm_dbg_kms(&dev_priv->drm, "GCP: 0x%x\n",
			    pipe_config->infoframes.gcp);
	अगर (pipe_config->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_AVI))
		पूर्णांकel_dump_infoframe(dev_priv, &pipe_config->infoframes.avi);
	अगर (pipe_config->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_SPD))
		पूर्णांकel_dump_infoframe(dev_priv, &pipe_config->infoframes.spd);
	अगर (pipe_config->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_VENDOR))
		पूर्णांकel_dump_infoframe(dev_priv, &pipe_config->infoframes.hdmi);
	अगर (pipe_config->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(HDMI_INFOFRAME_TYPE_DRM))
		पूर्णांकel_dump_infoframe(dev_priv, &pipe_config->infoframes.drm);
	अगर (pipe_config->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(HDMI_PACKET_TYPE_GAMUT_METADATA))
		पूर्णांकel_dump_infoframe(dev_priv, &pipe_config->infoframes.drm);
	अगर (pipe_config->infoframes.enable &
	    पूर्णांकel_hdmi_infoframe_enable(DP_SDP_VSC))
		पूर्णांकel_dump_dp_vsc_sdp(dev_priv, &pipe_config->infoframes.vsc);

	drm_dbg_kms(&dev_priv->drm, "vrr: %s, vmin: %d, vmax: %d, pipeline full: %d, flipline: %d, vmin vblank: %d, vmax vblank: %d\n",
		    yesno(pipe_config->vrr.enable),
		    pipe_config->vrr.vmin, pipe_config->vrr.vmax,
		    pipe_config->vrr.pipeline_full, pipe_config->vrr.flipline,
		    पूर्णांकel_vrr_vmin_vblank_start(pipe_config),
		    पूर्णांकel_vrr_vmax_vblank_start(pipe_config));

	drm_dbg_kms(&dev_priv->drm, "requested mode:\n");
	drm_mode_debug_prपूर्णांकmodeline(&pipe_config->hw.mode);
	drm_dbg_kms(&dev_priv->drm, "adjusted mode:\n");
	drm_mode_debug_prपूर्णांकmodeline(&pipe_config->hw.adjusted_mode);
	पूर्णांकel_dump_crtc_timings(dev_priv, &pipe_config->hw.adjusted_mode);
	drm_dbg_kms(&dev_priv->drm, "pipe mode:\n");
	drm_mode_debug_prपूर्णांकmodeline(&pipe_config->hw.pipe_mode);
	पूर्णांकel_dump_crtc_timings(dev_priv, &pipe_config->hw.pipe_mode);
	drm_dbg_kms(&dev_priv->drm,
		    "port clock: %d, pipe src size: %dx%d, pixel rate %d\n",
		    pipe_config->port_घड़ी,
		    pipe_config->pipe_src_w, pipe_config->pipe_src_h,
		    pipe_config->pixel_rate);

	drm_dbg_kms(&dev_priv->drm, "linetime: %d, ips linetime: %d\n",
		    pipe_config->lineसमय, pipe_config->ips_lineसमय);

	अगर (DISPLAY_VER(dev_priv) >= 9)
		drm_dbg_kms(&dev_priv->drm,
			    "num_scalers: %d, scaler_users: 0x%x, scaler_id: %d\n",
			    crtc->num_scalers,
			    pipe_config->scaler_state.scaler_users,
			    pipe_config->scaler_state.scaler_id);

	अगर (HAS_GMCH(dev_priv))
		drm_dbg_kms(&dev_priv->drm,
			    "gmch pfit: control: 0x%08x, ratios: 0x%08x, lvds border: 0x%08x\n",
			    pipe_config->gmch_pfit.control,
			    pipe_config->gmch_pfit.pgm_ratios,
			    pipe_config->gmch_pfit.lvds_border_bits);
	अन्यथा
		drm_dbg_kms(&dev_priv->drm,
			    "pch pfit: " DRM_RECT_FMT ", %s, force thru: %s\n",
			    DRM_RECT_ARG(&pipe_config->pch_pfit.dst),
			    enableddisabled(pipe_config->pch_pfit.enabled),
			    yesno(pipe_config->pch_pfit.क्रमce_thru));

	drm_dbg_kms(&dev_priv->drm, "ips: %i, double wide: %i\n",
		    pipe_config->ips_enabled, pipe_config->द्विगुन_wide);

	पूर्णांकel_dpll_dump_hw_state(dev_priv, &pipe_config->dpll_hw_state);

	अगर (IS_CHERRYVIEW(dev_priv))
		drm_dbg_kms(&dev_priv->drm,
			    "cgm_mode: 0x%x gamma_mode: 0x%x gamma_enable: %d csc_enable: %d\n",
			    pipe_config->cgm_mode, pipe_config->gamma_mode,
			    pipe_config->gamma_enable, pipe_config->csc_enable);
	अन्यथा
		drm_dbg_kms(&dev_priv->drm,
			    "csc_mode: 0x%x gamma_mode: 0x%x gamma_enable: %d csc_enable: %d\n",
			    pipe_config->csc_mode, pipe_config->gamma_mode,
			    pipe_config->gamma_enable, pipe_config->csc_enable);

	drm_dbg_kms(&dev_priv->drm, "degamma lut: %d entries, gamma lut: %d entries\n",
		    pipe_config->hw.degamma_lut ?
		    drm_color_lut_size(pipe_config->hw.degamma_lut) : 0,
		    pipe_config->hw.gamma_lut ?
		    drm_color_lut_size(pipe_config->hw.gamma_lut) : 0);

dump_planes:
	अगर (!state)
		वापस;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane->pipe == crtc->pipe)
			पूर्णांकel_dump_plane_state(plane_state);
	पूर्ण
पूर्ण

अटल bool check_digital_port_conflicts(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->base.dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	अचिन्हित पूर्णांक used_ports = 0;
	अचिन्हित पूर्णांक used_mst_ports = 0;
	bool ret = true;

	/*
	 * We're going to peek पूर्णांकo connector->state,
	 * hence connection_mutex must be held.
	 */
	drm_modeset_lock_निश्चित_held(&dev->mode_config.connection_mutex);

	/*
	 * Walk the connector list instead of the encoder
	 * list to detect the problem on ddi platक्रमms
	 * where there's just one encoder per digital port.
	 */
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_connector_state *connector_state;
		काष्ठा पूर्णांकel_encoder *encoder;

		connector_state =
			drm_atomic_get_new_connector_state(&state->base,
							   connector);
		अगर (!connector_state)
			connector_state = connector->state;

		अगर (!connector_state->best_encoder)
			जारी;

		encoder = to_पूर्णांकel_encoder(connector_state->best_encoder);

		drm_WARN_ON(dev, !connector_state->crtc);

		चयन (encoder->type) अणु
		हाल INTEL_OUTPUT_DDI:
			अगर (drm_WARN_ON(dev, !HAS_DDI(to_i915(dev))))
				अवरोध;
			fallthrough;
		हाल INTEL_OUTPUT_DP:
		हाल INTEL_OUTPUT_HDMI:
		हाल INTEL_OUTPUT_EDP:
			/* the same port mustn't appear more than once */
			अगर (used_ports & BIT(encoder->port))
				ret = false;

			used_ports |= BIT(encoder->port);
			अवरोध;
		हाल INTEL_OUTPUT_DP_MST:
			used_mst_ports |=
				1 << encoder->port;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	/* can't mix MST and SST/HDMI on the same port */
	अगर (used_ports & used_mst_ports)
		वापस false;

	वापस ret;
पूर्ण

अटल व्योम
पूर्णांकel_crtc_copy_uapi_to_hw_state_nomodeset(काष्ठा पूर्णांकel_atomic_state *state,
					   काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *from_crtc_state = crtc_state;

	अगर (crtc_state->bigjoiner_slave) अणु
		from_crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state,
								  crtc_state->bigjoiner_linked_crtc);

		/* No need to copy state अगर the master state is unchanged */
		अगर (!from_crtc_state)
			वापस;
	पूर्ण

	पूर्णांकel_crtc_copy_color_blobs(crtc_state, from_crtc_state);
पूर्ण

अटल व्योम
पूर्णांकel_crtc_copy_uapi_to_hw_state(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	crtc_state->hw.enable = crtc_state->uapi.enable;
	crtc_state->hw.active = crtc_state->uapi.active;
	crtc_state->hw.mode = crtc_state->uapi.mode;
	crtc_state->hw.adjusted_mode = crtc_state->uapi.adjusted_mode;
	crtc_state->hw.scaling_filter = crtc_state->uapi.scaling_filter;

	पूर्णांकel_crtc_copy_uapi_to_hw_state_nomodeset(state, crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_crtc_copy_hw_to_uapi_state(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (crtc_state->bigjoiner_slave)
		वापस;

	crtc_state->uapi.enable = crtc_state->hw.enable;
	crtc_state->uapi.active = crtc_state->hw.active;
	drm_WARN_ON(crtc_state->uapi.crtc->dev,
		    drm_atomic_set_mode_क्रम_crtc(&crtc_state->uapi, &crtc_state->hw.mode) < 0);

	crtc_state->uapi.adjusted_mode = crtc_state->hw.adjusted_mode;
	crtc_state->uapi.scaling_filter = crtc_state->hw.scaling_filter;

	/* copy color blobs to uapi */
	drm_property_replace_blob(&crtc_state->uapi.degamma_lut,
				  crtc_state->hw.degamma_lut);
	drm_property_replace_blob(&crtc_state->uapi.gamma_lut,
				  crtc_state->hw.gamma_lut);
	drm_property_replace_blob(&crtc_state->uapi.cपंचांग,
				  crtc_state->hw.cपंचांग);
पूर्ण

अटल पूर्णांक
copy_bigjoiner_crtc_state(काष्ठा पूर्णांकel_crtc_state *crtc_state,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *from_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc_state *saved_state;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	saved_state = kmemdup(from_crtc_state, माप(*saved_state), GFP_KERNEL);
	अगर (!saved_state)
		वापस -ENOMEM;

	saved_state->uapi = crtc_state->uapi;
	saved_state->scaler_state = crtc_state->scaler_state;
	saved_state->shared_dpll = crtc_state->shared_dpll;
	saved_state->dpll_hw_state = crtc_state->dpll_hw_state;
	saved_state->crc_enabled = crtc_state->crc_enabled;

	पूर्णांकel_crtc_मुक्त_hw_state(crtc_state);
	स_नकल(crtc_state, saved_state, माप(*crtc_state));
	kमुक्त(saved_state);

	/* Re-init hw state */
	स_रखो(&crtc_state->hw, 0, माप(saved_state->hw));
	crtc_state->hw.enable = from_crtc_state->hw.enable;
	crtc_state->hw.active = from_crtc_state->hw.active;
	crtc_state->hw.pipe_mode = from_crtc_state->hw.pipe_mode;
	crtc_state->hw.adjusted_mode = from_crtc_state->hw.adjusted_mode;

	/* Some fixups */
	crtc_state->uapi.mode_changed = from_crtc_state->uapi.mode_changed;
	crtc_state->uapi.connectors_changed = from_crtc_state->uapi.connectors_changed;
	crtc_state->uapi.active_changed = from_crtc_state->uapi.active_changed;
	crtc_state->nv12_planes = crtc_state->c8_planes = crtc_state->update_planes = 0;
	crtc_state->bigjoiner_linked_crtc = to_पूर्णांकel_crtc(from_crtc_state->uapi.crtc);
	crtc_state->bigjoiner_slave = true;
	crtc_state->cpu_transcoder = (क्रमागत transcoder)crtc->pipe;
	crtc_state->has_audio = false;

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_crtc_prepare_cleared_state(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_crtc_state *saved_state;

	saved_state = पूर्णांकel_crtc_state_alloc(crtc);
	अगर (!saved_state)
		वापस -ENOMEM;

	/* मुक्त the old crtc_state->hw members */
	पूर्णांकel_crtc_मुक्त_hw_state(crtc_state);

	/* FIXME: beक्रमe the चयन to atomic started, a new pipe_config was
	 * kzalloc'd. Code that depends on any field being zero should be
	 * fixed, so that the crtc_state can be safely duplicated. For now,
	 * only fields that are know to not cause problems are preserved. */

	saved_state->uapi = crtc_state->uapi;
	saved_state->scaler_state = crtc_state->scaler_state;
	saved_state->shared_dpll = crtc_state->shared_dpll;
	saved_state->dpll_hw_state = crtc_state->dpll_hw_state;
	स_नकल(saved_state->icl_port_dplls, crtc_state->icl_port_dplls,
	       माप(saved_state->icl_port_dplls));
	saved_state->crc_enabled = crtc_state->crc_enabled;
	अगर (IS_G4X(dev_priv) ||
	    IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		saved_state->wm = crtc_state->wm;

	स_नकल(crtc_state, saved_state, माप(*crtc_state));
	kमुक्त(saved_state);

	पूर्णांकel_crtc_copy_uapi_to_hw_state(state, crtc_state);

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_modeset_pipe_config(काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_crtc *crtc = pipe_config->uapi.crtc;
	काष्ठा drm_i915_निजी *i915 = to_i915(pipe_config->uapi.crtc->dev);
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *connector_state;
	पूर्णांक base_bpp, ret, i;
	bool retry = true;

	pipe_config->cpu_transcoder =
		(क्रमागत transcoder) to_पूर्णांकel_crtc(crtc)->pipe;

	/*
	 * Sanitize sync polarity flags based on requested ones. If neither
	 * positive or negative polarity is requested, treat this as meaning
	 * negative polarity.
	 */
	अगर (!(pipe_config->hw.adjusted_mode.flags &
	      (DRM_MODE_FLAG_PHSYNC | DRM_MODE_FLAG_NHSYNC)))
		pipe_config->hw.adjusted_mode.flags |= DRM_MODE_FLAG_NHSYNC;

	अगर (!(pipe_config->hw.adjusted_mode.flags &
	      (DRM_MODE_FLAG_PVSYNC | DRM_MODE_FLAG_NVSYNC)))
		pipe_config->hw.adjusted_mode.flags |= DRM_MODE_FLAG_NVSYNC;

	ret = compute_baseline_pipe_bpp(to_पूर्णांकel_crtc(crtc),
					pipe_config);
	अगर (ret)
		वापस ret;

	base_bpp = pipe_config->pipe_bpp;

	/*
	 * Determine the real pipe dimensions. Note that stereo modes can
	 * increase the actual pipe size due to the frame करोubling and
	 * insertion of additional space क्रम blanks between the frame. This
	 * is stored in the crtc timings. We use the requested mode to करो this
	 * computation to clearly distinguish it from the adjusted mode, which
	 * can be changed by the connectors in the below retry loop.
	 */
	drm_mode_get_hv_timing(&pipe_config->hw.mode,
			       &pipe_config->pipe_src_w,
			       &pipe_config->pipe_src_h);

	क्रम_each_new_connector_in_state(&state->base, connector, connector_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(connector_state->best_encoder);

		अगर (connector_state->crtc != crtc)
			जारी;

		अगर (!check_single_encoder_cloning(state, to_पूर्णांकel_crtc(crtc), encoder)) अणु
			drm_dbg_kms(&i915->drm,
				    "rejecting invalid cloning configuration\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * Determine output_types beक्रमe calling the .compute_config()
		 * hooks so that the hooks can use this inक्रमmation safely.
		 */
		अगर (encoder->compute_output_type)
			pipe_config->output_types |=
				BIT(encoder->compute_output_type(encoder, pipe_config,
								 connector_state));
		अन्यथा
			pipe_config->output_types |= BIT(encoder->type);
	पूर्ण

encoder_retry:
	/* Ensure the port घड़ी शेषs are reset when retrying. */
	pipe_config->port_घड़ी = 0;
	pipe_config->pixel_multiplier = 1;

	/* Fill in शेष crtc timings, allow encoders to overग_लिखो them. */
	drm_mode_set_crtcinfo(&pipe_config->hw.adjusted_mode,
			      CRTC_STEREO_DOUBLE);

	/* Pass our mode to the connectors and the CRTC to give them a chance to
	 * adjust it according to limitations or connector properties, and also
	 * a chance to reject the mode entirely.
	 */
	क्रम_each_new_connector_in_state(&state->base, connector, connector_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(connector_state->best_encoder);

		अगर (connector_state->crtc != crtc)
			जारी;

		ret = encoder->compute_config(encoder, pipe_config,
					      connector_state);
		अगर (ret < 0) अणु
			अगर (ret != -EDEADLK)
				drm_dbg_kms(&i915->drm,
					    "Encoder config failure: %d\n",
					    ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Set शेष port घड़ी अगर not overwritten by the encoder. Needs to be
	 * करोne afterwards in हाल the encoder adjusts the mode. */
	अगर (!pipe_config->port_घड़ी)
		pipe_config->port_घड़ी = pipe_config->hw.adjusted_mode.crtc_घड़ी
			* pipe_config->pixel_multiplier;

	ret = पूर्णांकel_crtc_compute_config(to_पूर्णांकel_crtc(crtc), pipe_config);
	अगर (ret == -EDEADLK)
		वापस ret;
	अगर (ret < 0) अणु
		drm_dbg_kms(&i915->drm, "CRTC fixup failed\n");
		वापस ret;
	पूर्ण

	अगर (ret == I915_DISPLAY_CONFIG_RETRY) अणु
		अगर (drm_WARN(&i915->drm, !retry,
			     "loop in pipe configuration computation\n"))
			वापस -EINVAL;

		drm_dbg_kms(&i915->drm, "CRTC bw constrained, retrying\n");
		retry = false;
		जाओ encoder_retry;
	पूर्ण

	/* Dithering seems to not pass-through bits correctly when it should, so
	 * only enable it on 6bpc panels and when its not a compliance
	 * test requesting 6bpc video pattern.
	 */
	pipe_config->dither = (pipe_config->pipe_bpp == 6*3) &&
		!pipe_config->dither_क्रमce_disable;
	drm_dbg_kms(&i915->drm,
		    "hw max bpp: %i, pipe bpp: %i, dithering: %i\n",
		    base_bpp, pipe_config->pipe_bpp, pipe_config->dither);

	वापस 0;
पूर्ण

अटल पूर्णांक
पूर्णांकel_modeset_pipe_config_late(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(crtc_state->uapi.state);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_connector_state *conn_state;
	काष्ठा drm_connector *connector;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, connector,
					conn_state, i) अणु
		काष्ठा पूर्णांकel_encoder *encoder =
			to_पूर्णांकel_encoder(conn_state->best_encoder);
		पूर्णांक ret;

		अगर (conn_state->crtc != &crtc->base ||
		    !encoder->compute_config_late)
			जारी;

		ret = encoder->compute_config_late(encoder, crtc_state,
						   conn_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

bool पूर्णांकel_fuzzy_घड़ी_check(पूर्णांक घड़ी1, पूर्णांक घड़ी2)
अणु
	पूर्णांक dअगरf;

	अगर (घड़ी1 == घड़ी2)
		वापस true;

	अगर (!घड़ी1 || !घड़ी2)
		वापस false;

	dअगरf = असल(घड़ी1 - घड़ी2);

	अगर (((((dअगरf + घड़ी1 + घड़ी2) * 100)) / (घड़ी1 + घड़ी2)) < 105)
		वापस true;

	वापस false;
पूर्ण

अटल bool
पूर्णांकel_compare_m_n(अचिन्हित पूर्णांक m, अचिन्हित पूर्णांक n,
		  अचिन्हित पूर्णांक m2, अचिन्हित पूर्णांक n2,
		  bool exact)
अणु
	अगर (m == m2 && n == n2)
		वापस true;

	अगर (exact || !m || !n || !m2 || !n2)
		वापस false;

	BUILD_BUG_ON(DATA_LINK_M_N_MASK > पूर्णांक_उच्च);

	अगर (n > n2) अणु
		जबतक (n > n2) अणु
			m2 <<= 1;
			n2 <<= 1;
		पूर्ण
	पूर्ण अन्यथा अगर (n < n2) अणु
		जबतक (n < n2) अणु
			m <<= 1;
			n <<= 1;
		पूर्ण
	पूर्ण

	अगर (n != n2)
		वापस false;

	वापस पूर्णांकel_fuzzy_घड़ी_check(m, m2);
पूर्ण

अटल bool
पूर्णांकel_compare_link_m_n(स्थिर काष्ठा पूर्णांकel_link_m_n *m_n,
		       स्थिर काष्ठा पूर्णांकel_link_m_n *m2_n2,
		       bool exact)
अणु
	वापस m_n->tu == m2_n2->tu &&
		पूर्णांकel_compare_m_n(m_n->gmch_m, m_n->gmch_n,
				  m2_n2->gmch_m, m2_n2->gmch_n, exact) &&
		पूर्णांकel_compare_m_n(m_n->link_m, m_n->link_n,
				  m2_n2->link_m, m2_n2->link_n, exact);
पूर्ण

अटल bool
पूर्णांकel_compare_infoframe(स्थिर जोड़ hdmi_infoframe *a,
			स्थिर जोड़ hdmi_infoframe *b)
अणु
	वापस स_भेद(a, b, माप(*a)) == 0;
पूर्ण

अटल bool
पूर्णांकel_compare_dp_vsc_sdp(स्थिर काष्ठा drm_dp_vsc_sdp *a,
			 स्थिर काष्ठा drm_dp_vsc_sdp *b)
अणु
	वापस स_भेद(a, b, माप(*a)) == 0;
पूर्ण

अटल व्योम
pipe_config_infoframe_mismatch(काष्ठा drm_i915_निजी *dev_priv,
			       bool fastset, स्थिर अक्षर *name,
			       स्थिर जोड़ hdmi_infoframe *a,
			       स्थिर जोड़ hdmi_infoframe *b)
अणु
	अगर (fastset) अणु
		अगर (!drm_debug_enabled(DRM_UT_KMS))
			वापस;

		drm_dbg_kms(&dev_priv->drm,
			    "fastset mismatch in %s infoframe\n", name);
		drm_dbg_kms(&dev_priv->drm, "expected:\n");
		hdmi_infoframe_log(KERN_DEBUG, dev_priv->drm.dev, a);
		drm_dbg_kms(&dev_priv->drm, "found:\n");
		hdmi_infoframe_log(KERN_DEBUG, dev_priv->drm.dev, b);
	पूर्ण अन्यथा अणु
		drm_err(&dev_priv->drm, "mismatch in %s infoframe\n", name);
		drm_err(&dev_priv->drm, "expected:\n");
		hdmi_infoframe_log(KERN_ERR, dev_priv->drm.dev, a);
		drm_err(&dev_priv->drm, "found:\n");
		hdmi_infoframe_log(KERN_ERR, dev_priv->drm.dev, b);
	पूर्ण
पूर्ण

अटल व्योम
pipe_config_dp_vsc_sdp_mismatch(काष्ठा drm_i915_निजी *dev_priv,
				bool fastset, स्थिर अक्षर *name,
				स्थिर काष्ठा drm_dp_vsc_sdp *a,
				स्थिर काष्ठा drm_dp_vsc_sdp *b)
अणु
	अगर (fastset) अणु
		अगर (!drm_debug_enabled(DRM_UT_KMS))
			वापस;

		drm_dbg_kms(&dev_priv->drm,
			    "fastset mismatch in %s dp sdp\n", name);
		drm_dbg_kms(&dev_priv->drm, "expected:\n");
		drm_dp_vsc_sdp_log(KERN_DEBUG, dev_priv->drm.dev, a);
		drm_dbg_kms(&dev_priv->drm, "found:\n");
		drm_dp_vsc_sdp_log(KERN_DEBUG, dev_priv->drm.dev, b);
	पूर्ण अन्यथा अणु
		drm_err(&dev_priv->drm, "mismatch in %s dp sdp\n", name);
		drm_err(&dev_priv->drm, "expected:\n");
		drm_dp_vsc_sdp_log(KERN_ERR, dev_priv->drm.dev, a);
		drm_err(&dev_priv->drm, "found:\n");
		drm_dp_vsc_sdp_log(KERN_ERR, dev_priv->drm.dev, b);
	पूर्ण
पूर्ण

अटल व्योम __म_लिखो(4, 5)
pipe_config_mismatch(bool fastset, स्थिर काष्ठा पूर्णांकel_crtc *crtc,
		     स्थिर अक्षर *name, स्थिर अक्षर *क्रमmat, ...)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);
	vaf.fmt = क्रमmat;
	vaf.va = &args;

	अगर (fastset)
		drm_dbg_kms(&i915->drm,
			    "[CRTC:%d:%s] fastset mismatch in %s %pV\n",
			    crtc->base.base.id, crtc->base.name, name, &vaf);
	अन्यथा
		drm_err(&i915->drm, "[CRTC:%d:%s] mismatch in %s %pV\n",
			crtc->base.base.id, crtc->base.name, name, &vaf);

	बहु_पूर्ण(args);
पूर्ण

अटल bool fastboot_enabled(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (dev_priv->params.fastboot != -1)
		वापस dev_priv->params.fastboot;

	/* Enable fastboot by शेष on Skylake and newer */
	अगर (DISPLAY_VER(dev_priv) >= 9)
		वापस true;

	/* Enable fastboot by शेष on VLV and CHV */
	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		वापस true;

	/* Disabled by शेष on all others */
	वापस false;
पूर्ण

अटल bool
पूर्णांकel_pipe_config_compare(स्थिर काष्ठा पूर्णांकel_crtc_state *current_config,
			  स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			  bool fastset)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(current_config->uapi.crtc->dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	bool ret = true;
	u32 bp_gamma = 0;
	bool fixup_inherited = fastset &&
		current_config->inherited && !pipe_config->inherited;

	अगर (fixup_inherited && !fastboot_enabled(dev_priv)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "initial modeset and fastboot not set\n");
		ret = false;
	पूर्ण

#घोषणा PIPE_CONF_CHECK_X(name) करो अणु \
	अगर (current_config->name != pipe_config->name) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "(expected 0x%08x, found 0x%08x)", \
				     current_config->name, \
				     pipe_config->name); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_I(name) करो अणु \
	अगर (current_config->name != pipe_config->name) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "(expected %i, found %i)", \
				     current_config->name, \
				     pipe_config->name); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_BOOL(name) करो अणु \
	अगर (current_config->name != pipe_config->name) अणु \
		pipe_config_mismatch(fastset, crtc,  __stringअगरy(name), \
				     "(expected %s, found %s)", \
				     yesno(current_config->name), \
				     yesno(pipe_config->name)); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

/*
 * Checks state where we only पढ़ो out the enabling, but not the entire
 * state itself (like full infoframes or ELD क्रम audio). These states
 * require a full modeset on bootup to fix up.
 */
#घोषणा PIPE_CONF_CHECK_BOOL_INCOMPLETE(name) करो अणु \
	अगर (!fixup_inherited || (!current_config->name && !pipe_config->name)) अणु \
		PIPE_CONF_CHECK_BOOL(name); \
	पूर्ण अन्यथा अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "unable to verify whether state matches exactly, forcing modeset (expected %s, found %s)", \
				     yesno(current_config->name), \
				     yesno(pipe_config->name)); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_P(name) करो अणु \
	अगर (current_config->name != pipe_config->name) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "(expected %p, found %p)", \
				     current_config->name, \
				     pipe_config->name); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_M_N(name) करो अणु \
	अगर (!पूर्णांकel_compare_link_m_n(&current_config->name, \
				    &pipe_config->name,\
				    !fastset)) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "(expected tu %i gmch %i/%i link %i/%i, " \
				     "found tu %i, gmch %i/%i link %i/%i)", \
				     current_config->name.tu, \
				     current_config->name.gmch_m, \
				     current_config->name.gmch_n, \
				     current_config->name.link_m, \
				     current_config->name.link_n, \
				     pipe_config->name.tu, \
				     pipe_config->name.gmch_m, \
				     pipe_config->name.gmch_n, \
				     pipe_config->name.link_m, \
				     pipe_config->name.link_n); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

/* This is required क्रम BDW+ where there is only one set of रेजिस्टरs क्रम
 * चयनing between high and low RR.
 * This macro can be used whenever a comparison has to be made between one
 * hw state and multiple sw state variables.
 */
#घोषणा PIPE_CONF_CHECK_M_N_ALT(name, alt_name) करो अणु \
	अगर (!पूर्णांकel_compare_link_m_n(&current_config->name, \
				    &pipe_config->name, !fastset) && \
	    !पूर्णांकel_compare_link_m_n(&current_config->alt_name, \
				    &pipe_config->name, !fastset)) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "(expected tu %i gmch %i/%i link %i/%i, " \
				     "or tu %i gmch %i/%i link %i/%i, " \
				     "found tu %i, gmch %i/%i link %i/%i)", \
				     current_config->name.tu, \
				     current_config->name.gmch_m, \
				     current_config->name.gmch_n, \
				     current_config->name.link_m, \
				     current_config->name.link_n, \
				     current_config->alt_name.tu, \
				     current_config->alt_name.gmch_m, \
				     current_config->alt_name.gmch_n, \
				     current_config->alt_name.link_m, \
				     current_config->alt_name.link_n, \
				     pipe_config->name.tu, \
				     pipe_config->name.gmch_m, \
				     pipe_config->name.gmch_n, \
				     pipe_config->name.link_m, \
				     pipe_config->name.link_n); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_FLAGS(name, mask) करो अणु \
	अगर ((current_config->name ^ pipe_config->name) & (mask)) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "(%x) (expected %i, found %i)", \
				     (mask), \
				     current_config->name & (mask), \
				     pipe_config->name & (mask)); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_CLOCK_FUZZY(name) करो अणु \
	अगर (!पूर्णांकel_fuzzy_घड़ी_check(current_config->name, pipe_config->name)) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name), \
				     "(expected %i, found %i)", \
				     current_config->name, \
				     pipe_config->name); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_INFOFRAME(name) करो अणु \
	अगर (!पूर्णांकel_compare_infoframe(&current_config->infoframes.name, \
				     &pipe_config->infoframes.name)) अणु \
		pipe_config_infoframe_mismatch(dev_priv, fastset, __stringअगरy(name), \
					       &current_config->infoframes.name, \
					       &pipe_config->infoframes.name); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_DP_VSC_SDP(name) करो अणु \
	अगर (!current_config->has_psr && !pipe_config->has_psr && \
	    !पूर्णांकel_compare_dp_vsc_sdp(&current_config->infoframes.name, \
				      &pipe_config->infoframes.name)) अणु \
		pipe_config_dp_vsc_sdp_mismatch(dev_priv, fastset, __stringअगरy(name), \
						&current_config->infoframes.name, \
						&pipe_config->infoframes.name); \
		ret = false; \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_CHECK_COLOR_LUT(name1, name2, bit_precision) करो अणु \
	अगर (current_config->name1 != pipe_config->name1) अणु \
		pipe_config_mismatch(fastset, crtc, __stringअगरy(name1), \
				"(expected %i, found %i, won't compare lut values)", \
				current_config->name1, \
				pipe_config->name1); \
		ret = false;\
	पूर्ण अन्यथा अणु \
		अगर (!पूर्णांकel_color_lut_equal(current_config->name2, \
					pipe_config->name2, pipe_config->name1, \
					bit_precision)) अणु \
			pipe_config_mismatch(fastset, crtc, __stringअगरy(name2), \
					"hw_state doesn't match sw_state"); \
			ret = false; \
		पूर्ण \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा PIPE_CONF_QUIRK(quirk) \
	((current_config->quirks | pipe_config->quirks) & (quirk))

	PIPE_CONF_CHECK_I(cpu_transcoder);

	PIPE_CONF_CHECK_BOOL(has_pch_encoder);
	PIPE_CONF_CHECK_I(fdi_lanes);
	PIPE_CONF_CHECK_M_N(fdi_m_n);

	PIPE_CONF_CHECK_I(lane_count);
	PIPE_CONF_CHECK_X(lane_lat_optim_mask);

	अगर (DISPLAY_VER(dev_priv) < 8) अणु
		PIPE_CONF_CHECK_M_N(dp_m_n);

		अगर (current_config->has_drrs)
			PIPE_CONF_CHECK_M_N(dp_m2_n2);
	पूर्ण अन्यथा
		PIPE_CONF_CHECK_M_N_ALT(dp_m_n, dp_m2_n2);

	PIPE_CONF_CHECK_X(output_types);

	/* FIXME करो the पढ़ोout properly and get rid of this quirk */
	अगर (!PIPE_CONF_QUIRK(PIPE_CONFIG_QUIRK_BIGJOINER_SLAVE)) अणु
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_hdisplay);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_htotal);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_hblank_start);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_hblank_end);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_hsync_start);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_hsync_end);

		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_vdisplay);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_vtotal);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_vblank_start);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_vblank_end);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_vsync_start);
		PIPE_CONF_CHECK_I(hw.pipe_mode.crtc_vsync_end);

		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_hdisplay);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_htotal);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_hblank_start);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_hblank_end);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_hsync_start);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_hsync_end);

		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_vdisplay);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_vtotal);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_vblank_start);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_vblank_end);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_vsync_start);
		PIPE_CONF_CHECK_I(hw.adjusted_mode.crtc_vsync_end);

		PIPE_CONF_CHECK_I(pixel_multiplier);

		PIPE_CONF_CHECK_FLAGS(hw.adjusted_mode.flags,
				      DRM_MODE_FLAG_INTERLACE);

		अगर (!PIPE_CONF_QUIRK(PIPE_CONFIG_QUIRK_MODE_SYNC_FLAGS)) अणु
			PIPE_CONF_CHECK_FLAGS(hw.adjusted_mode.flags,
					      DRM_MODE_FLAG_PHSYNC);
			PIPE_CONF_CHECK_FLAGS(hw.adjusted_mode.flags,
					      DRM_MODE_FLAG_NHSYNC);
			PIPE_CONF_CHECK_FLAGS(hw.adjusted_mode.flags,
					      DRM_MODE_FLAG_PVSYNC);
			PIPE_CONF_CHECK_FLAGS(hw.adjusted_mode.flags,
					      DRM_MODE_FLAG_NVSYNC);
		पूर्ण
	पूर्ण

	PIPE_CONF_CHECK_I(output_क्रमmat);
	PIPE_CONF_CHECK_BOOL(has_hdmi_sink);
	अगर ((DISPLAY_VER(dev_priv) < 8 && !IS_HASWELL(dev_priv)) ||
	    IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		PIPE_CONF_CHECK_BOOL(limited_color_range);

	PIPE_CONF_CHECK_BOOL(hdmi_scrambling);
	PIPE_CONF_CHECK_BOOL(hdmi_high_पंचांगds_घड़ी_ratio);
	PIPE_CONF_CHECK_BOOL(has_infoframe);
	/* FIXME करो the पढ़ोout properly and get rid of this quirk */
	अगर (!PIPE_CONF_QUIRK(PIPE_CONFIG_QUIRK_BIGJOINER_SLAVE))
		PIPE_CONF_CHECK_BOOL(fec_enable);

	PIPE_CONF_CHECK_BOOL_INCOMPLETE(has_audio);

	PIPE_CONF_CHECK_X(gmch_pfit.control);
	/* pfit ratios are स्वतःcomputed by the hw on gen4+ */
	अगर (DISPLAY_VER(dev_priv) < 4)
		PIPE_CONF_CHECK_X(gmch_pfit.pgm_ratios);
	PIPE_CONF_CHECK_X(gmch_pfit.lvds_border_bits);

	/*
	 * Changing the EDP transcoder input mux
	 * (A_ONOFF vs. A_ON) requires a full modeset.
	 */
	PIPE_CONF_CHECK_BOOL(pch_pfit.क्रमce_thru);

	अगर (!fastset) अणु
		PIPE_CONF_CHECK_I(pipe_src_w);
		PIPE_CONF_CHECK_I(pipe_src_h);

		PIPE_CONF_CHECK_BOOL(pch_pfit.enabled);
		अगर (current_config->pch_pfit.enabled) अणु
			PIPE_CONF_CHECK_I(pch_pfit.dst.x1);
			PIPE_CONF_CHECK_I(pch_pfit.dst.y1);
			PIPE_CONF_CHECK_I(pch_pfit.dst.x2);
			PIPE_CONF_CHECK_I(pch_pfit.dst.y2);
		पूर्ण

		PIPE_CONF_CHECK_I(scaler_state.scaler_id);
		/* FIXME करो the पढ़ोout properly and get rid of this quirk */
		अगर (!PIPE_CONF_QUIRK(PIPE_CONFIG_QUIRK_BIGJOINER_SLAVE))
			PIPE_CONF_CHECK_CLOCK_FUZZY(pixel_rate);

		PIPE_CONF_CHECK_X(gamma_mode);
		अगर (IS_CHERRYVIEW(dev_priv))
			PIPE_CONF_CHECK_X(cgm_mode);
		अन्यथा
			PIPE_CONF_CHECK_X(csc_mode);
		PIPE_CONF_CHECK_BOOL(gamma_enable);
		PIPE_CONF_CHECK_BOOL(csc_enable);

		PIPE_CONF_CHECK_I(lineसमय);
		PIPE_CONF_CHECK_I(ips_lineसमय);

		bp_gamma = पूर्णांकel_color_get_gamma_bit_precision(pipe_config);
		अगर (bp_gamma)
			PIPE_CONF_CHECK_COLOR_LUT(gamma_mode, hw.gamma_lut, bp_gamma);
	पूर्ण

	PIPE_CONF_CHECK_BOOL(द्विगुन_wide);

	PIPE_CONF_CHECK_P(shared_dpll);

	/* FIXME करो the पढ़ोout properly and get rid of this quirk */
	अगर (!PIPE_CONF_QUIRK(PIPE_CONFIG_QUIRK_BIGJOINER_SLAVE)) अणु
		PIPE_CONF_CHECK_X(dpll_hw_state.dpll);
		PIPE_CONF_CHECK_X(dpll_hw_state.dpll_md);
		PIPE_CONF_CHECK_X(dpll_hw_state.fp0);
		PIPE_CONF_CHECK_X(dpll_hw_state.fp1);
		PIPE_CONF_CHECK_X(dpll_hw_state.wrpll);
		PIPE_CONF_CHECK_X(dpll_hw_state.spll);
		PIPE_CONF_CHECK_X(dpll_hw_state.ctrl1);
		PIPE_CONF_CHECK_X(dpll_hw_state.cfgcr1);
		PIPE_CONF_CHECK_X(dpll_hw_state.cfgcr2);
		PIPE_CONF_CHECK_X(dpll_hw_state.cfgcr0);
		PIPE_CONF_CHECK_X(dpll_hw_state.ebb0);
		PIPE_CONF_CHECK_X(dpll_hw_state.ebb4);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll0);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll1);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll2);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll3);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll6);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll8);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll9);
		PIPE_CONF_CHECK_X(dpll_hw_state.pll10);
		PIPE_CONF_CHECK_X(dpll_hw_state.pcsdw12);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_refclkin_ctl);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_clktop2_coreclkctl1);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_clktop2_hsclkctl);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_pll_भाग0);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_pll_भाग1);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_pll_lf);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_pll_frac_lock);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_pll_ssc);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_pll_bias);
		PIPE_CONF_CHECK_X(dpll_hw_state.mg_pll_tdc_coldst_bias);

		PIPE_CONF_CHECK_X(dsi_pll.ctrl);
		PIPE_CONF_CHECK_X(dsi_pll.भाग);

		अगर (IS_G4X(dev_priv) || DISPLAY_VER(dev_priv) >= 5)
			PIPE_CONF_CHECK_I(pipe_bpp);

		PIPE_CONF_CHECK_CLOCK_FUZZY(hw.pipe_mode.crtc_घड़ी);
		PIPE_CONF_CHECK_CLOCK_FUZZY(hw.adjusted_mode.crtc_घड़ी);
		PIPE_CONF_CHECK_CLOCK_FUZZY(port_घड़ी);

		PIPE_CONF_CHECK_I(min_voltage_level);
	पूर्ण

	PIPE_CONF_CHECK_X(infoframes.enable);
	PIPE_CONF_CHECK_X(infoframes.gcp);
	PIPE_CONF_CHECK_INFOFRAME(avi);
	PIPE_CONF_CHECK_INFOFRAME(spd);
	PIPE_CONF_CHECK_INFOFRAME(hdmi);
	PIPE_CONF_CHECK_INFOFRAME(drm);
	PIPE_CONF_CHECK_DP_VSC_SDP(vsc);

	PIPE_CONF_CHECK_X(sync_mode_slaves_mask);
	PIPE_CONF_CHECK_I(master_transcoder);
	PIPE_CONF_CHECK_BOOL(bigjoiner);
	PIPE_CONF_CHECK_BOOL(bigjoiner_slave);
	PIPE_CONF_CHECK_P(bigjoiner_linked_crtc);

	PIPE_CONF_CHECK_I(dsc.compression_enable);
	PIPE_CONF_CHECK_I(dsc.dsc_split);
	PIPE_CONF_CHECK_I(dsc.compressed_bpp);

	PIPE_CONF_CHECK_BOOL(splitter.enable);
	PIPE_CONF_CHECK_I(splitter.link_count);
	PIPE_CONF_CHECK_I(splitter.pixel_overlap);

	PIPE_CONF_CHECK_I(mst_master_transcoder);

	PIPE_CONF_CHECK_BOOL(vrr.enable);
	PIPE_CONF_CHECK_I(vrr.vmin);
	PIPE_CONF_CHECK_I(vrr.vmax);
	PIPE_CONF_CHECK_I(vrr.flipline);
	PIPE_CONF_CHECK_I(vrr.pipeline_full);

#अघोषित PIPE_CONF_CHECK_X
#अघोषित PIPE_CONF_CHECK_I
#अघोषित PIPE_CONF_CHECK_BOOL
#अघोषित PIPE_CONF_CHECK_BOOL_INCOMPLETE
#अघोषित PIPE_CONF_CHECK_P
#अघोषित PIPE_CONF_CHECK_FLAGS
#अघोषित PIPE_CONF_CHECK_CLOCK_FUZZY
#अघोषित PIPE_CONF_CHECK_COLOR_LUT
#अघोषित PIPE_CONF_QUIRK

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_pipe_config_sanity_check(काष्ठा drm_i915_निजी *dev_priv,
					   स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	अगर (pipe_config->has_pch_encoder) अणु
		पूर्णांक fdi_करोtघड़ी = पूर्णांकel_करोtघड़ी_calculate(पूर्णांकel_fdi_link_freq(dev_priv, pipe_config),
							    &pipe_config->fdi_m_n);
		पूर्णांक करोtघड़ी = pipe_config->hw.adjusted_mode.crtc_घड़ी;

		/*
		 * FDI alपढ़ोy provided one idea क्रम the करोtघड़ी.
		 * Yell अगर the encoder disagrees.
		 */
		drm_WARN(&dev_priv->drm,
			 !पूर्णांकel_fuzzy_घड़ी_check(fdi_करोtघड़ी, करोtघड़ी),
			 "FDI dotclock and encoder dotclock mismatch, fdi: %i, encoder: %i\n",
			 fdi_करोtघड़ी, करोtघड़ी);
	पूर्ण
पूर्ण

अटल व्योम verअगरy_wm_state(काष्ठा पूर्णांकel_crtc *crtc,
			    काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा skl_hw_state अणु
		काष्ठा skl_ddb_entry ddb_y[I915_MAX_PLANES];
		काष्ठा skl_ddb_entry ddb_uv[I915_MAX_PLANES];
		काष्ठा skl_pipe_wm wm;
	पूर्ण *hw;
	स्थिर काष्ठा skl_pipe_wm *sw_wm = &new_crtc_state->wm.skl.optimal;
	पूर्णांक level, max_level = ilk_wm_max_level(dev_priv);
	काष्ठा पूर्णांकel_plane *plane;
	u8 hw_enabled_slices;

	अगर (DISPLAY_VER(dev_priv) < 9 || !new_crtc_state->hw.active)
		वापस;

	hw = kzalloc(माप(*hw), GFP_KERNEL);
	अगर (!hw)
		वापस;

	skl_pipe_wm_get_hw_state(crtc, &hw->wm);

	skl_pipe_ddb_get_hw_state(crtc, hw->ddb_y, hw->ddb_uv);

	hw_enabled_slices = पूर्णांकel_enabled_dbuf_slices_mask(dev_priv);

	अगर (DISPLAY_VER(dev_priv) >= 11 &&
	    hw_enabled_slices != dev_priv->dbuf.enabled_slices)
		drm_err(&dev_priv->drm,
			"mismatch in DBUF Slices (expected 0x%x, got 0x%x)\n",
			dev_priv->dbuf.enabled_slices,
			hw_enabled_slices);

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
		स्थिर काष्ठा skl_ddb_entry *hw_ddb_entry, *sw_ddb_entry;
		स्थिर काष्ठा skl_wm_level *hw_wm_level, *sw_wm_level;

		/* Watermarks */
		क्रम (level = 0; level <= max_level; level++) अणु
			hw_wm_level = &hw->wm.planes[plane->id].wm[level];
			sw_wm_level = skl_plane_wm_level(sw_wm, plane->id, level);

			अगर (skl_wm_level_equals(hw_wm_level, sw_wm_level))
				जारी;

			drm_err(&dev_priv->drm,
				"[PLANE:%d:%s] mismatch in WM%d (expected e=%d b=%u l=%u, got e=%d b=%u l=%u)\n",
				plane->base.base.id, plane->base.name, level,
				sw_wm_level->enable,
				sw_wm_level->blocks,
				sw_wm_level->lines,
				hw_wm_level->enable,
				hw_wm_level->blocks,
				hw_wm_level->lines);
		पूर्ण

		hw_wm_level = &hw->wm.planes[plane->id].trans_wm;
		sw_wm_level = skl_plane_trans_wm(sw_wm, plane->id);

		अगर (!skl_wm_level_equals(hw_wm_level, sw_wm_level)) अणु
			drm_err(&dev_priv->drm,
				"[PLANE:%d:%s] mismatch in trans WM (expected e=%d b=%u l=%u, got e=%d b=%u l=%u)\n",
				plane->base.base.id, plane->base.name,
				sw_wm_level->enable,
				sw_wm_level->blocks,
				sw_wm_level->lines,
				hw_wm_level->enable,
				hw_wm_level->blocks,
				hw_wm_level->lines);
		पूर्ण

		/* DDB */
		hw_ddb_entry = &hw->ddb_y[plane->id];
		sw_ddb_entry = &new_crtc_state->wm.skl.plane_ddb_y[plane->id];

		अगर (!skl_ddb_entry_equal(hw_ddb_entry, sw_ddb_entry)) अणु
			drm_err(&dev_priv->drm,
				"[PLANE:%d:%s] mismatch in DDB (expected (%u,%u), found (%u,%u))\n",
				plane->base.base.id, plane->base.name,
				sw_ddb_entry->start, sw_ddb_entry->end,
				hw_ddb_entry->start, hw_ddb_entry->end);
		पूर्ण
	पूर्ण

	kमुक्त(hw);
पूर्ण

अटल व्योम
verअगरy_connector_state(काष्ठा पूर्णांकel_atomic_state *state,
		       काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *new_conn_state;
	पूर्णांक i;

	क्रम_each_new_connector_in_state(&state->base, connector, new_conn_state, i) अणु
		काष्ठा drm_encoder *encoder = connector->encoder;
		काष्ठा पूर्णांकel_crtc_state *crtc_state = शून्य;

		अगर (new_conn_state->crtc != &crtc->base)
			जारी;

		अगर (crtc)
			crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

		पूर्णांकel_connector_verअगरy_state(crtc_state, new_conn_state);

		I915_STATE_WARN(new_conn_state->best_encoder != encoder,
		     "connector's atomic encoder doesn't match legacy encoder\n");
	पूर्ण
पूर्ण

अटल व्योम
verअगरy_encoder_state(काष्ठा drm_i915_निजी *dev_priv, काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा drm_connector *connector;
	काष्ठा drm_connector_state *old_conn_state, *new_conn_state;
	पूर्णांक i;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		bool enabled = false, found = false;
		क्रमागत pipe pipe;

		drm_dbg_kms(&dev_priv->drm, "[ENCODER:%d:%s]\n",
			    encoder->base.base.id,
			    encoder->base.name);

		क्रम_each_oldnew_connector_in_state(&state->base, connector, old_conn_state,
						   new_conn_state, i) अणु
			अगर (old_conn_state->best_encoder == &encoder->base)
				found = true;

			अगर (new_conn_state->best_encoder != &encoder->base)
				जारी;
			found = enabled = true;

			I915_STATE_WARN(new_conn_state->crtc !=
					encoder->base.crtc,
			     "connector's crtc doesn't match encoder crtc\n");
		पूर्ण

		अगर (!found)
			जारी;

		I915_STATE_WARN(!!encoder->base.crtc != enabled,
		     "encoder's enabled state mismatch "
		     "(expected %i, found %i)\n",
		     !!encoder->base.crtc, enabled);

		अगर (!encoder->base.crtc) अणु
			bool active;

			active = encoder->get_hw_state(encoder, &pipe);
			I915_STATE_WARN(active,
			     "encoder detached but still enabled on pipe %c.\n",
			     pipe_name(pipe));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
verअगरy_crtc_state(काष्ठा पूर्णांकel_crtc *crtc,
		  काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
		  काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा पूर्णांकel_crtc_state *pipe_config = old_crtc_state;
	काष्ठा drm_atomic_state *state = old_crtc_state->uapi.state;
	काष्ठा पूर्णांकel_crtc *master = crtc;

	__drm_atomic_helper_crtc_destroy_state(&old_crtc_state->uapi);
	पूर्णांकel_crtc_मुक्त_hw_state(old_crtc_state);
	पूर्णांकel_crtc_state_reset(old_crtc_state, crtc);
	old_crtc_state->uapi.state = state;

	drm_dbg_kms(&dev_priv->drm, "[CRTC:%d:%s]\n", crtc->base.base.id,
		    crtc->base.name);

	pipe_config->hw.enable = new_crtc_state->hw.enable;

	पूर्णांकel_crtc_get_pipe_config(pipe_config);

	/* we keep both pipes enabled on 830 */
	अगर (IS_I830(dev_priv) && pipe_config->hw.active)
		pipe_config->hw.active = new_crtc_state->hw.active;

	I915_STATE_WARN(new_crtc_state->hw.active != pipe_config->hw.active,
			"crtc active state doesn't match with hw state "
			"(expected %i, found %i)\n",
			new_crtc_state->hw.active, pipe_config->hw.active);

	I915_STATE_WARN(crtc->active != new_crtc_state->hw.active,
			"transitional active state does not match atomic hw state "
			"(expected %i, found %i)\n",
			new_crtc_state->hw.active, crtc->active);

	अगर (new_crtc_state->bigjoiner_slave)
		master = new_crtc_state->bigjoiner_linked_crtc;

	क्रम_each_encoder_on_crtc(dev, &master->base, encoder) अणु
		क्रमागत pipe pipe;
		bool active;

		active = encoder->get_hw_state(encoder, &pipe);
		I915_STATE_WARN(active != new_crtc_state->hw.active,
				"[ENCODER:%i] active %i with crtc active %i\n",
				encoder->base.base.id, active,
				new_crtc_state->hw.active);

		I915_STATE_WARN(active && master->pipe != pipe,
				"Encoder connected to wrong pipe %c\n",
				pipe_name(pipe));

		अगर (active)
			पूर्णांकel_encoder_get_config(encoder, pipe_config);
	पूर्ण

	अगर (!new_crtc_state->hw.active)
		वापस;

	पूर्णांकel_pipe_config_sanity_check(dev_priv, pipe_config);

	अगर (!पूर्णांकel_pipe_config_compare(new_crtc_state,
				       pipe_config, false)) अणु
		I915_STATE_WARN(1, "pipe state doesn't match!\n");
		पूर्णांकel_dump_pipe_config(pipe_config, शून्य, "[hw state]");
		पूर्णांकel_dump_pipe_config(new_crtc_state, शून्य, "[sw state]");
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_verअगरy_planes(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_plane *plane;
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane,
					  plane_state, i)
		निश्चित_plane(plane, plane_state->planar_slave ||
			     plane_state->uapi.visible);
पूर्ण

अटल व्योम
verअगरy_single_dpll_state(काष्ठा drm_i915_निजी *dev_priv,
			 काष्ठा पूर्णांकel_shared_dpll *pll,
			 काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_dpll_hw_state dpll_hw_state;
	u8 pipe_mask;
	bool active;

	स_रखो(&dpll_hw_state, 0, माप(dpll_hw_state));

	drm_dbg_kms(&dev_priv->drm, "%s\n", pll->info->name);

	active = पूर्णांकel_dpll_get_hw_state(dev_priv, pll, &dpll_hw_state);

	अगर (!(pll->info->flags & INTEL_DPLL_ALWAYS_ON)) अणु
		I915_STATE_WARN(!pll->on && pll->active_mask,
		     "pll in active use but not on in sw tracking\n");
		I915_STATE_WARN(pll->on && !pll->active_mask,
		     "pll is on but not used by any active pipe\n");
		I915_STATE_WARN(pll->on != active,
		     "pll on state mismatch (expected %i, found %i)\n",
		     pll->on, active);
	पूर्ण

	अगर (!crtc) अणु
		I915_STATE_WARN(pll->active_mask & ~pll->state.pipe_mask,
				"more active pll users than references: 0x%x vs 0x%x\n",
				pll->active_mask, pll->state.pipe_mask);

		वापस;
	पूर्ण

	pipe_mask = BIT(crtc->pipe);

	अगर (new_crtc_state->hw.active)
		I915_STATE_WARN(!(pll->active_mask & pipe_mask),
				"pll active mismatch (expected pipe %c in active mask 0x%x)\n",
				pipe_name(crtc->pipe), pll->active_mask);
	अन्यथा
		I915_STATE_WARN(pll->active_mask & pipe_mask,
				"pll active mismatch (didn't expect pipe %c in active mask 0x%x)\n",
				pipe_name(crtc->pipe), pll->active_mask);

	I915_STATE_WARN(!(pll->state.pipe_mask & pipe_mask),
			"pll enabled crtcs mismatch (expected 0x%x in 0x%x)\n",
			pipe_mask, pll->state.pipe_mask);

	I915_STATE_WARN(pll->on && स_भेद(&pll->state.hw_state,
					  &dpll_hw_state,
					  माप(dpll_hw_state)),
			"pll hw state mismatch\n");
पूर्ण

अटल व्योम
verअगरy_shared_dpll_state(काष्ठा पूर्णांकel_crtc *crtc,
			 काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			 काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (new_crtc_state->shared_dpll)
		verअगरy_single_dpll_state(dev_priv, new_crtc_state->shared_dpll, crtc, new_crtc_state);

	अगर (old_crtc_state->shared_dpll &&
	    old_crtc_state->shared_dpll != new_crtc_state->shared_dpll) अणु
		u8 pipe_mask = BIT(crtc->pipe);
		काष्ठा पूर्णांकel_shared_dpll *pll = old_crtc_state->shared_dpll;

		I915_STATE_WARN(pll->active_mask & pipe_mask,
				"pll active mismatch (didn't expect pipe %c in active mask (0x%x))\n",
				pipe_name(crtc->pipe), pll->active_mask);
		I915_STATE_WARN(pll->state.pipe_mask & pipe_mask,
				"pll enabled crtcs mismatch (found %x in enabled mask (0x%x))\n",
				pipe_name(crtc->pipe), pll->state.pipe_mask);
	पूर्ण
पूर्ण

अटल व्योम
पूर्णांकel_modeset_verअगरy_crtc(काष्ठा पूर्णांकel_crtc *crtc,
			  काष्ठा पूर्णांकel_atomic_state *state,
			  काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			  काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state) && !new_crtc_state->update_pipe)
		वापस;

	verअगरy_wm_state(crtc, new_crtc_state);
	verअगरy_connector_state(state, crtc);
	verअगरy_crtc_state(crtc, old_crtc_state, new_crtc_state);
	verअगरy_shared_dpll_state(crtc, old_crtc_state, new_crtc_state);
पूर्ण

अटल व्योम
verअगरy_disabled_dpll_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dev_priv->dpll.num_shared_dpll; i++)
		verअगरy_single_dpll_state(dev_priv,
					 &dev_priv->dpll.shared_dplls[i],
					 शून्य, शून्य);
पूर्ण

अटल व्योम
पूर्णांकel_modeset_verअगरy_disabled(काष्ठा drm_i915_निजी *dev_priv,
			      काष्ठा पूर्णांकel_atomic_state *state)
अणु
	verअगरy_encoder_state(dev_priv, state);
	verअगरy_connector_state(state, शून्य);
	verअगरy_disabled_dpll_state(dev_priv);
पूर्ण

अटल व्योम
पूर्णांकel_crtc_update_active_timings(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा drm_display_mode adjusted_mode =
		crtc_state->hw.adjusted_mode;

	अगर (crtc_state->vrr.enable) अणु
		adjusted_mode.crtc_vtotal = crtc_state->vrr.vmax;
		adjusted_mode.crtc_vblank_end = crtc_state->vrr.vmax;
		adjusted_mode.crtc_vblank_start = पूर्णांकel_vrr_vmin_vblank_start(crtc_state);
		crtc->vmax_vblank_start = पूर्णांकel_vrr_vmax_vblank_start(crtc_state);
	पूर्ण

	drm_calc_बारtamping_स्थिरants(&crtc->base, &adjusted_mode);

	crtc->mode_flags = crtc_state->mode_flags;

	/*
	 * The scanline counter increments at the leading edge of hsync.
	 *
	 * On most platक्रमms it starts counting from vtotal-1 on the
	 * first active line. That means the scanline counter value is
	 * always one less than what we would expect. Ie. just after
	 * start of vblank, which also occurs at start of hsync (on the
	 * last active line), the scanline counter will पढ़ो vblank_start-1.
	 *
	 * On gen2 the scanline counter starts counting from 1 instead
	 * of vtotal-1, so we have to subtract one (or rather add vtotal-1
	 * to keep the value positive), instead of adding one.
	 *
	 * On HSW+ the behaviour of the scanline counter depends on the output
	 * type. For DP ports it behaves like most other platक्रमms, but on HDMI
	 * there's an extra 1 line dअगरference. So we need to add two instead of
	 * one to the value.
	 *
	 * On VLV/CHV DSI the scanline counter would appear to increment
	 * approx. 1/3 of a scanline beक्रमe start of vblank. Unक्रमtunately
	 * that means we can't tell whether we're in vblank or not जबतक
	 * we're on that particular line. We must still set scanline_offset
	 * to 1 so that the vblank बारtamps come out correct when we query
	 * the scanline counter from within the vblank पूर्णांकerrupt handler.
	 * However अगर queried just beक्रमe the start of vblank we'll get an
	 * answer that's slightly in the future.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 2)) अणु
		पूर्णांक vtotal;

		vtotal = adjusted_mode.crtc_vtotal;
		अगर (adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE)
			vtotal /= 2;

		crtc->scanline_offset = vtotal - 1;
	पूर्ण अन्यथा अगर (HAS_DDI(dev_priv) &&
		   पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI)) अणु
		crtc->scanline_offset = 2;
	पूर्ण अन्यथा अणु
		crtc->scanline_offset = 1;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_modeset_clear_plls(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	अगर (!dev_priv->display.crtc_compute_घड़ी)
		वापस;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state))
			जारी;

		पूर्णांकel_release_shared_dplls(state, crtc);
	पूर्ण
पूर्ण

/*
 * This implements the workaround described in the "notes" section of the mode
 * set sequence करोcumentation. When going from no pipes or single pipe to
 * multiple pipes, and planes are enabled after the pipe, we need to रुको at
 * least 2 vblanks on the first pipe beक्रमe enabling planes on the second pipe.
 */
अटल पूर्णांक hsw_mode_set_planes_workaround(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *first_crtc_state = शून्य;
	काष्ठा पूर्णांकel_crtc_state *other_crtc_state = शून्य;
	क्रमागत pipe first_pipe = INVALID_PIPE, enabled_pipe = INVALID_PIPE;
	पूर्णांक i;

	/* look at all crtc's that are going to be enabled in during modeset */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		अगर (!crtc_state->hw.active ||
		    !पूर्णांकel_crtc_needs_modeset(crtc_state))
			जारी;

		अगर (first_crtc_state) अणु
			other_crtc_state = crtc_state;
			अवरोध;
		पूर्ण अन्यथा अणु
			first_crtc_state = crtc_state;
			first_pipe = crtc->pipe;
		पूर्ण
	पूर्ण

	/* No workaround needed? */
	अगर (!first_crtc_state)
		वापस 0;

	/* w/a possibly needed, check how many crtc's are alपढ़ोy enabled. */
	क्रम_each_पूर्णांकel_crtc(state->base.dev, crtc) अणु
		crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		crtc_state->hsw_workaround_pipe = INVALID_PIPE;

		अगर (!crtc_state->hw.active ||
		    पूर्णांकel_crtc_needs_modeset(crtc_state))
			जारी;

		/* 2 or more enabled crtcs means no need क्रम w/a */
		अगर (enabled_pipe != INVALID_PIPE)
			वापस 0;

		enabled_pipe = crtc->pipe;
	पूर्ण

	अगर (enabled_pipe != INVALID_PIPE)
		first_crtc_state->hsw_workaround_pipe = enabled_pipe;
	अन्यथा अगर (other_crtc_state)
		other_crtc_state->hsw_workaround_pipe = first_pipe;

	वापस 0;
पूर्ण

u8 पूर्णांकel_calc_active_pipes(काष्ठा पूर्णांकel_atomic_state *state,
			   u8 active_pipes)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		अगर (crtc_state->hw.active)
			active_pipes |= BIT(crtc->pipe);
		अन्यथा
			active_pipes &= ~BIT(crtc->pipe);
	पूर्ण

	वापस active_pipes;
पूर्ण

अटल पूर्णांक पूर्णांकel_modeset_checks(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);

	state->modeset = true;

	अगर (IS_HASWELL(dev_priv))
		वापस hsw_mode_set_planes_workaround(state);

	वापस 0;
पूर्ण

/*
 * Handle calculation of various watermark data at the end of the atomic check
 * phase.  The code here should be run after the per-crtc and per-plane 'check'
 * handlers to ensure that all derived state has been updated.
 */
अटल पूर्णांक calc_watermark_data(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	/* Is there platक्रमm-specअगरic watermark inक्रमmation to calculate? */
	अगर (dev_priv->display.compute_global_watermarks)
		वापस dev_priv->display.compute_global_watermarks(state);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_crtc_check_fastset(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				     काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	अगर (!पूर्णांकel_pipe_config_compare(old_crtc_state, new_crtc_state, true))
		वापस;

	new_crtc_state->uapi.mode_changed = false;
	new_crtc_state->update_pipe = true;
पूर्ण

अटल व्योम पूर्णांकel_crtc_copy_fastset(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				    काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	/*
	 * If we're not करोing the full modeset we want to
	 * keep the current M/N values as they may be
	 * sufficiently dअगरferent to the computed values
	 * to cause problems.
	 *
	 * FIXME: should really copy more fuzzy state here
	 */
	new_crtc_state->fdi_m_n = old_crtc_state->fdi_m_n;
	new_crtc_state->dp_m_n = old_crtc_state->dp_m_n;
	new_crtc_state->dp_m2_n2 = old_crtc_state->dp_m2_n2;
	new_crtc_state->has_drrs = old_crtc_state->has_drrs;
पूर्ण

अटल पूर्णांक पूर्णांकel_crtc_add_planes_to_state(काष्ठा पूर्णांकel_atomic_state *state,
					  काष्ठा पूर्णांकel_crtc *crtc,
					  u8 plane_ids_mask)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_plane *plane;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
		काष्ठा पूर्णांकel_plane_state *plane_state;

		अगर ((plane_ids_mask & BIT(plane->id)) == 0)
			जारी;

		plane_state = पूर्णांकel_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state))
			वापस PTR_ERR(plane_state);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_atomic_add_affected_planes(काष्ठा पूर्णांकel_atomic_state *state,
				     काष्ठा पूर्णांकel_crtc *crtc)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	वापस पूर्णांकel_crtc_add_planes_to_state(state, crtc,
					      old_crtc_state->enabled_planes |
					      new_crtc_state->enabled_planes);
पूर्ण

अटल bool active_planes_affects_min_cdclk(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/* See अणुhsw,vlv,ivbपूर्ण_plane_ratio() */
	वापस IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv) ||
		IS_CHERRYVIEW(dev_priv) || IS_VALLEYVIEW(dev_priv) ||
		IS_IVYBRIDGE(dev_priv);
पूर्ण

अटल पूर्णांक पूर्णांकel_crtc_add_bigjoiner_planes(काष्ठा पूर्णांकel_atomic_state *state,
					   काष्ठा पूर्णांकel_crtc *crtc,
					   काष्ठा पूर्णांकel_crtc *other)
अणु
	स्थिर काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	u8 plane_ids = 0;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		अगर (plane->pipe == crtc->pipe)
			plane_ids |= BIT(plane->id);
	पूर्ण

	वापस पूर्णांकel_crtc_add_planes_to_state(state, other, plane_ids);
पूर्ण

अटल पूर्णांक पूर्णांकel_bigjoiner_add_affected_planes(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		पूर्णांक ret;

		अगर (!crtc_state->bigjoiner)
			जारी;

		ret = पूर्णांकel_crtc_add_bigjoiner_planes(state, crtc,
						      crtc_state->bigjoiner_linked_crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_atomic_check_planes(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i, ret;

	ret = icl_add_linked_planes(state);
	अगर (ret)
		वापस ret;

	ret = पूर्णांकel_bigjoiner_add_affected_planes(state);
	अगर (ret)
		वापस ret;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		ret = पूर्णांकel_plane_atomic_check(state, plane);
		अगर (ret) अणु
			drm_dbg_atomic(&dev_priv->drm,
				       "[PLANE:%d:%s] atomic driver check failed\n",
				       plane->base.base.id, plane->base.name);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		u8 old_active_planes, new_active_planes;

		ret = icl_check_nv12_planes(new_crtc_state);
		अगर (ret)
			वापस ret;

		/*
		 * On some platक्रमms the number of active planes affects
		 * the planes' minimum cdclk calculation. Add such planes
		 * to the state beक्रमe we compute the minimum cdclk.
		 */
		अगर (!active_planes_affects_min_cdclk(dev_priv))
			जारी;

		old_active_planes = old_crtc_state->active_planes & ~BIT(PLANE_CURSOR);
		new_active_planes = new_crtc_state->active_planes & ~BIT(PLANE_CURSOR);

		अगर (hweight8(old_active_planes) == hweight8(new_active_planes))
			जारी;

		ret = पूर्णांकel_crtc_add_planes_to_state(state, crtc, new_active_planes);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_atomic_check_cdclk(काष्ठा पूर्णांकel_atomic_state *state,
				    bool *need_cdclk_calc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_cdclk_state *old_cdclk_state;
	स्थिर काष्ठा पूर्णांकel_cdclk_state *new_cdclk_state;
	काष्ठा पूर्णांकel_plane_state *plane_state;
	काष्ठा पूर्णांकel_bw_state *new_bw_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक min_cdclk = 0;
	क्रमागत pipe pipe;
	पूर्णांक ret;
	पूर्णांक i;
	/*
	 * active_planes biपंचांगask has been updated, and potentially
	 * affected planes are part of the state. We can now
	 * compute the minimum cdclk क्रम each plane.
	 */
	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		ret = पूर्णांकel_plane_calc_min_cdclk(state, plane, need_cdclk_calc);
		अगर (ret)
			वापस ret;
	पूर्ण

	old_cdclk_state = पूर्णांकel_atomic_get_old_cdclk_state(state);
	new_cdclk_state = पूर्णांकel_atomic_get_new_cdclk_state(state);

	अगर (new_cdclk_state &&
	    old_cdclk_state->क्रमce_min_cdclk != new_cdclk_state->क्रमce_min_cdclk)
		*need_cdclk_calc = true;

	ret = dev_priv->display.bw_calc_min_cdclk(state);
	अगर (ret)
		वापस ret;

	new_bw_state = पूर्णांकel_atomic_get_new_bw_state(state);

	अगर (!new_cdclk_state || !new_bw_state)
		वापस 0;

	क्रम_each_pipe(dev_priv, pipe) अणु
		min_cdclk = max(new_cdclk_state->min_cdclk[pipe], min_cdclk);

		/*
		 * Currently करो this change only अगर we need to increase
		 */
		अगर (new_bw_state->min_cdclk > min_cdclk)
			*need_cdclk_calc = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_atomic_check_crtcs(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
		पूर्णांक ret;

		ret = पूर्णांकel_crtc_atomic_check(state, crtc);
		अगर (ret) अणु
			drm_dbg_atomic(&i915->drm,
				       "[CRTC:%d:%s] atomic driver check failed\n",
				       crtc->base.base.id, crtc->base.name);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool पूर्णांकel_cpu_transcoders_need_modeset(काष्ठा पूर्णांकel_atomic_state *state,
					       u8 transcoders)
अणु
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (new_crtc_state->hw.enable &&
		    transcoders & BIT(new_crtc_state->cpu_transcoder) &&
		    पूर्णांकel_crtc_needs_modeset(new_crtc_state))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक पूर्णांकel_atomic_check_bigjoiner(काष्ठा पूर्णांकel_atomic_state *state,
					काष्ठा पूर्णांकel_crtc *crtc,
					काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
					काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc_state *slave_crtc_state, *master_crtc_state;
	काष्ठा पूर्णांकel_crtc *slave, *master;

	/* slave being enabled, is master is still claiming this crtc? */
	अगर (old_crtc_state->bigjoiner_slave) अणु
		slave = crtc;
		master = old_crtc_state->bigjoiner_linked_crtc;
		master_crtc_state = पूर्णांकel_atomic_get_new_crtc_state(state, master);
		अगर (!master_crtc_state || !पूर्णांकel_crtc_needs_modeset(master_crtc_state))
			जाओ claimed;
	पूर्ण

	अगर (!new_crtc_state->bigjoiner)
		वापस 0;

	अगर (1 + crtc->pipe >= INTEL_NUM_PIPES(dev_priv)) अणु
		DRM_DEBUG_KMS("[CRTC:%d:%s] Big joiner configuration requires "
			      "CRTC + 1 to be used, doesn't exist\n",
			      crtc->base.base.id, crtc->base.name);
		वापस -EINVAL;
	पूर्ण

	slave = new_crtc_state->bigjoiner_linked_crtc =
		पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, crtc->pipe + 1);
	slave_crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, slave);
	master = crtc;
	अगर (IS_ERR(slave_crtc_state))
		वापस PTR_ERR(slave_crtc_state);

	/* master being enabled, slave was alपढ़ोy configured? */
	अगर (slave_crtc_state->uapi.enable)
		जाओ claimed;

	DRM_DEBUG_KMS("[CRTC:%d:%s] Used as slave for big joiner\n",
		      slave->base.base.id, slave->base.name);

	वापस copy_bigjoiner_crtc_state(slave_crtc_state, new_crtc_state);

claimed:
	DRM_DEBUG_KMS("[CRTC:%d:%s] Slave is enabled as normal CRTC, but "
		      "[CRTC:%d:%s] claiming this CRTC for bigjoiner.\n",
		      slave->base.base.id, slave->base.name,
		      master->base.base.id, master->base.name);
	वापस -EINVAL;
पूर्ण

अटल व्योम समाप्त_bigjoiner_slave(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_crtc_state *master_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc_state *slave_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, master_crtc_state->bigjoiner_linked_crtc);

	slave_crtc_state->bigjoiner = master_crtc_state->bigjoiner = false;
	slave_crtc_state->bigjoiner_slave = master_crtc_state->bigjoiner_slave = false;
	slave_crtc_state->bigjoiner_linked_crtc = master_crtc_state->bigjoiner_linked_crtc = शून्य;
	पूर्णांकel_crtc_copy_uapi_to_hw_state(state, slave_crtc_state);
पूर्ण

/**
 * DOC: asynchronous flip implementation
 *
 * Asynchronous page flip is the implementation क्रम the DRM_MODE_PAGE_FLIP_ASYNC
 * flag. Currently async flip is only supported via the drmModePageFlip IOCTL.
 * Correspondingly, support is currently added क्रम primary plane only.
 *
 * Async flip can only change the plane surface address, so anything अन्यथा
 * changing is rejected from the पूर्णांकel_atomic_check_async() function.
 * Once this check is cleared, flip करोne पूर्णांकerrupt is enabled using
 * the पूर्णांकel_crtc_enable_flip_करोne() function.
 *
 * As soon as the surface address रेजिस्टर is written, flip करोne पूर्णांकerrupt is
 * generated and the requested events are sent to the usersapce in the पूर्णांकerrupt
 * handler itself. The बारtamp and sequence sent during the flip करोne event
 * correspond to the last vblank and have no relation to the actual समय when
 * the flip करोne event was sent.
 */
अटल पूर्णांक पूर्णांकel_atomic_check_async(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state, *new_crtc_state;
	स्थिर काष्ठा पूर्णांकel_plane_state *new_plane_state, *old_plane_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक i;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (पूर्णांकel_crtc_needs_modeset(new_crtc_state)) अणु
			drm_dbg_kms(&i915->drm, "Modeset Required. Async flip not supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!new_crtc_state->hw.active) अणु
			drm_dbg_kms(&i915->drm, "CRTC inactive\n");
			वापस -EINVAL;
		पूर्ण
		अगर (old_crtc_state->active_planes != new_crtc_state->active_planes) अणु
			drm_dbg_kms(&i915->drm,
				    "Active planes cannot be changed during async flip\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_पूर्णांकel_plane_in_state(state, plane, old_plane_state,
					     new_plane_state, i) अणु
		/*
		 * TODO: Async flip is only supported through the page flip IOCTL
		 * as of now. So support currently added क्रम primary plane only.
		 * Support क्रम other planes on platक्रमms on which supports
		 * this(vlv/chv and icl+) should be added when async flip is
		 * enabled in the atomic IOCTL path.
		 */
		अगर (!plane->async_flip)
			वापस -EINVAL;

		/*
		 * FIXME: This check is kept generic क्रम all platक्रमms.
		 * Need to verअगरy this क्रम all gen9 and gen10 platक्रमms to enable
		 * this selectively अगर required.
		 */
		चयन (new_plane_state->hw.fb->modअगरier) अणु
		हाल I915_FORMAT_MOD_X_TILED:
		हाल I915_FORMAT_MOD_Y_TILED:
		हाल I915_FORMAT_MOD_Yf_TILED:
			अवरोध;
		शेष:
			drm_dbg_kms(&i915->drm,
				    "Linear memory/CCS does not support async flips\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->view.color_plane[0].stride !=
		    new_plane_state->view.color_plane[0].stride) अणु
			drm_dbg_kms(&i915->drm, "Stride cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->hw.fb->modअगरier !=
		    new_plane_state->hw.fb->modअगरier) अणु
			drm_dbg_kms(&i915->drm,
				    "Framebuffer modifiers cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->hw.fb->क्रमmat !=
		    new_plane_state->hw.fb->क्रमmat) अणु
			drm_dbg_kms(&i915->drm,
				    "Framebuffer format cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->hw.rotation !=
		    new_plane_state->hw.rotation) अणु
			drm_dbg_kms(&i915->drm, "Rotation cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!drm_rect_equals(&old_plane_state->uapi.src, &new_plane_state->uapi.src) ||
		    !drm_rect_equals(&old_plane_state->uapi.dst, &new_plane_state->uapi.dst)) अणु
			drm_dbg_kms(&i915->drm,
				    "Plane size/co-ordinates cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->hw.alpha != new_plane_state->hw.alpha) अणु
			drm_dbg_kms(&i915->drm, "Alpha value cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->hw.pixel_blend_mode !=
		    new_plane_state->hw.pixel_blend_mode) अणु
			drm_dbg_kms(&i915->drm,
				    "Pixel blend mode cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->hw.color_encoding != new_plane_state->hw.color_encoding) अणु
			drm_dbg_kms(&i915->drm,
				    "Color encoding cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण

		अगर (old_plane_state->hw.color_range != new_plane_state->hw.color_range) अणु
			drm_dbg_kms(&i915->drm, "Color range cannot be changed in async flip\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_bigjoiner_add_affected_crtcs(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		काष्ठा पूर्णांकel_crtc_state *linked_crtc_state;
		काष्ठा पूर्णांकel_crtc *linked_crtc;
		पूर्णांक ret;

		अगर (!crtc_state->bigjoiner)
			जारी;

		linked_crtc = crtc_state->bigjoiner_linked_crtc;
		linked_crtc_state = पूर्णांकel_atomic_get_crtc_state(&state->base, linked_crtc);
		अगर (IS_ERR(linked_crtc_state))
			वापस PTR_ERR(linked_crtc_state);

		अगर (!पूर्णांकel_crtc_needs_modeset(crtc_state))
			जारी;

		linked_crtc_state->uapi.mode_changed = true;

		ret = drm_atomic_add_affected_connectors(&state->base,
							 &linked_crtc->base);
		अगर (ret)
			वापस ret;

		ret = पूर्णांकel_atomic_add_affected_planes(state, linked_crtc);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		/* Kill old bigjoiner link, we may re-establish afterwards */
		अगर (पूर्णांकel_crtc_needs_modeset(crtc_state) &&
		    crtc_state->bigjoiner && !crtc_state->bigjoiner_slave)
			समाप्त_bigjoiner_slave(state, crtc_state);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_atomic_check - validate state object
 * @dev: drm device
 * @_state: state to validate
 */
अटल पूर्णांक पूर्णांकel_atomic_check(काष्ठा drm_device *dev,
			      काष्ठा drm_atomic_state *_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(_state);
	काष्ठा पूर्णांकel_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक ret, i;
	bool any_ms = false;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (new_crtc_state->inherited != old_crtc_state->inherited)
			new_crtc_state->uapi.mode_changed = true;
	पूर्ण

	पूर्णांकel_vrr_check_modeset(state);

	ret = drm_atomic_helper_check_modeset(dev, &state->base);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकel_bigjoiner_add_affected_crtcs(state);
	अगर (ret)
		जाओ fail;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state)) अणु
			/* Light copy */
			पूर्णांकel_crtc_copy_uapi_to_hw_state_nomodeset(state, new_crtc_state);

			जारी;
		पूर्ण

		अगर (!new_crtc_state->uapi.enable) अणु
			अगर (!new_crtc_state->bigjoiner_slave) अणु
				पूर्णांकel_crtc_copy_uapi_to_hw_state(state, new_crtc_state);
				any_ms = true;
			पूर्ण
			जारी;
		पूर्ण

		ret = पूर्णांकel_crtc_prepare_cleared_state(state, new_crtc_state);
		अगर (ret)
			जाओ fail;

		ret = पूर्णांकel_modeset_pipe_config(state, new_crtc_state);
		अगर (ret)
			जाओ fail;

		ret = पूर्णांकel_atomic_check_bigjoiner(state, crtc, old_crtc_state,
						   new_crtc_state);
		अगर (ret)
			जाओ fail;
	पूर्ण

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state))
			जारी;

		ret = पूर्णांकel_modeset_pipe_config_late(new_crtc_state);
		अगर (ret)
			जाओ fail;

		पूर्णांकel_crtc_check_fastset(old_crtc_state, new_crtc_state);
	पूर्ण

	/**
	 * Check अगर fastset is allowed by बाह्यal dependencies like other
	 * pipes and transcoders.
	 *
	 * Right now it only क्रमces a fullmodeset when the MST master
	 * transcoder did not changed but the pipe of the master transcoder
	 * needs a fullmodeset so all slaves also needs to करो a fullmodeset or
	 * in हाल of port synced crtcs, अगर one of the synced crtcs
	 * needs a full modeset, all other synced crtcs should be
	 * क्रमced a full modeset.
	 */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (!new_crtc_state->hw.enable || पूर्णांकel_crtc_needs_modeset(new_crtc_state))
			जारी;

		अगर (पूर्णांकel_dp_mst_is_slave_trans(new_crtc_state)) अणु
			क्रमागत transcoder master = new_crtc_state->mst_master_transcoder;

			अगर (पूर्णांकel_cpu_transcoders_need_modeset(state, BIT(master))) अणु
				new_crtc_state->uapi.mode_changed = true;
				new_crtc_state->update_pipe = false;
			पूर्ण
		पूर्ण

		अगर (is_trans_port_sync_mode(new_crtc_state)) अणु
			u8 trans = new_crtc_state->sync_mode_slaves_mask;

			अगर (new_crtc_state->master_transcoder != INVALID_TRANSCODER)
				trans |= BIT(new_crtc_state->master_transcoder);

			अगर (पूर्णांकel_cpu_transcoders_need_modeset(state, trans)) अणु
				new_crtc_state->uapi.mode_changed = true;
				new_crtc_state->update_pipe = false;
			पूर्ण
		पूर्ण

		अगर (new_crtc_state->bigjoiner) अणु
			काष्ठा पूर्णांकel_crtc_state *linked_crtc_state =
				पूर्णांकel_atomic_get_new_crtc_state(state, new_crtc_state->bigjoiner_linked_crtc);

			अगर (पूर्णांकel_crtc_needs_modeset(linked_crtc_state)) अणु
				new_crtc_state->uapi.mode_changed = true;
				new_crtc_state->update_pipe = false;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (पूर्णांकel_crtc_needs_modeset(new_crtc_state)) अणु
			any_ms = true;
			जारी;
		पूर्ण

		अगर (!new_crtc_state->update_pipe)
			जारी;

		पूर्णांकel_crtc_copy_fastset(old_crtc_state, new_crtc_state);
	पूर्ण

	अगर (any_ms && !check_digital_port_conflicts(state)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "rejecting conflicting digital port configuration\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	ret = drm_dp_mst_atomic_check(&state->base);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकel_atomic_check_planes(state);
	अगर (ret)
		जाओ fail;

	पूर्णांकel_fbc_choose_crtc(dev_priv, state);
	ret = calc_watermark_data(state);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकel_bw_atomic_check(state);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकel_atomic_check_cdclk(state, &any_ms);
	अगर (ret)
		जाओ fail;

	अगर (any_ms) अणु
		ret = पूर्णांकel_modeset_checks(state);
		अगर (ret)
			जाओ fail;

		ret = पूर्णांकel_modeset_calc_cdclk(state);
		अगर (ret)
			वापस ret;

		पूर्णांकel_modeset_clear_plls(state);
	पूर्ण

	ret = पूर्णांकel_atomic_check_crtcs(state);
	अगर (ret)
		जाओ fail;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (new_crtc_state->uapi.async_flip) अणु
			ret = पूर्णांकel_atomic_check_async(state);
			अगर (ret)
				जाओ fail;
		पूर्ण

		अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state) &&
		    !new_crtc_state->update_pipe)
			जारी;

		पूर्णांकel_dump_pipe_config(new_crtc_state, state,
				       पूर्णांकel_crtc_needs_modeset(new_crtc_state) ?
				       "[modeset]" : "[fastset]");
	पूर्ण

	वापस 0;

 fail:
	अगर (ret == -EDEADLK)
		वापस ret;

	/*
	 * FIXME would probably be nice to know which crtc specअगरically
	 * caused the failure, in हालs where we can pinpoपूर्णांक it.
	 */
	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i)
		पूर्णांकel_dump_pipe_config(new_crtc_state, state, "[failed]");

	वापस ret;
पूर्ण

अटल पूर्णांक पूर्णांकel_atomic_prepare_commit(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i, ret;

	ret = drm_atomic_helper_prepare_planes(state->base.dev, &state->base);
	अगर (ret < 0)
		वापस ret;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, crtc_state, i) अणु
		bool mode_changed = पूर्णांकel_crtc_needs_modeset(crtc_state);

		अगर (mode_changed || crtc_state->update_pipe ||
		    crtc_state->uapi.color_mgmt_changed) अणु
			पूर्णांकel_dsb_prepare(crtc_state);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम पूर्णांकel_crtc_arm_fअगरo_underrun(काष्ठा पूर्णांकel_crtc *crtc,
				  काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (!IS_DISPLAY_VER(dev_priv, 2) || crtc_state->active_planes)
		पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, crtc->pipe, true);

	अगर (crtc_state->has_pch_encoder) अणु
		क्रमागत pipe pch_transcoder =
			पूर्णांकel_crtc_pch_transcoder(crtc);

		पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, pch_transcoder, true);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pipe_fastset(स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	/*
	 * Update pipe size and adjust fitter अगर needed: the reason क्रम this is
	 * that in compute_mode_changes we check the native mode (not the pfit
	 * mode) to see अगर we can flip rather than करो a full mode set. In the
	 * fastboot हाल, we'll flip, but if we don't update the pipesrc and
	 * pfit state, we'll end up with a big fb scanned out पूर्णांकo the wrong
	 * sized surface.
	 */
	पूर्णांकel_set_pipe_src_size(new_crtc_state);

	/* on skylake this is करोne by detaching scalers */
	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		skl_detach_scalers(new_crtc_state);

		अगर (new_crtc_state->pch_pfit.enabled)
			skl_pfit_enable(new_crtc_state);
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		अगर (new_crtc_state->pch_pfit.enabled)
			ilk_pfit_enable(new_crtc_state);
		अन्यथा अगर (old_crtc_state->pch_pfit.enabled)
			ilk_pfit_disable(old_crtc_state);
	पूर्ण

	/*
	 * The रेजिस्टर is supposedly single buffered so perhaps
	 * not 100% correct to करो this here. But SKL+ calculate
	 * this based on the adjust pixel rate so pfit changes करो
	 * affect it and so it must be updated क्रम fastsets.
	 * HSW/BDW only really need this here क्रम fastboot, after
	 * that the value should not change without a full modeset.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 9 ||
	    IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
		hsw_set_lineसमय_wm(new_crtc_state);

	अगर (DISPLAY_VER(dev_priv) >= 11)
		icl_set_pipe_chicken(crtc);
पूर्ण

अटल व्योम commit_pipe_config(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	bool modeset = पूर्णांकel_crtc_needs_modeset(new_crtc_state);

	/*
	 * During modesets pipe configuration was programmed as the
	 * CRTC was enabled.
	 */
	अगर (!modeset) अणु
		अगर (new_crtc_state->uapi.color_mgmt_changed ||
		    new_crtc_state->update_pipe)
			पूर्णांकel_color_commit(new_crtc_state);

		अगर (DISPLAY_VER(dev_priv) >= 9)
			skl_detach_scalers(new_crtc_state);

		अगर (DISPLAY_VER(dev_priv) >= 9 || IS_BROADWELL(dev_priv))
			bdw_set_pipemisc(new_crtc_state);

		अगर (new_crtc_state->update_pipe)
			पूर्णांकel_pipe_fastset(old_crtc_state, new_crtc_state);

		पूर्णांकel_psr2_program_trans_man_trk_ctl(new_crtc_state);
	पूर्ण

	अगर (dev_priv->display.atomic_update_watermarks)
		dev_priv->display.atomic_update_watermarks(state, crtc);
पूर्ण

अटल व्योम पूर्णांकel_enable_crtc(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);

	अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state))
		वापस;

	पूर्णांकel_crtc_update_active_timings(new_crtc_state);

	dev_priv->display.crtc_enable(state, crtc);

	अगर (new_crtc_state->bigjoiner_slave)
		वापस;

	/* vblanks work again, re-enable pipe CRC. */
	पूर्णांकel_crtc_enable_pipe_crc(crtc);
पूर्ण

अटल व्योम पूर्णांकel_update_crtc(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state =
		पूर्णांकel_atomic_get_new_crtc_state(state, crtc);
	bool modeset = पूर्णांकel_crtc_needs_modeset(new_crtc_state);

	अगर (!modeset) अणु
		अगर (new_crtc_state->preload_luts &&
		    (new_crtc_state->uapi.color_mgmt_changed ||
		     new_crtc_state->update_pipe))
			पूर्णांकel_color_load_luts(new_crtc_state);

		पूर्णांकel_pre_plane_update(state, crtc);

		अगर (new_crtc_state->update_pipe)
			पूर्णांकel_encoders_update_pipe(state, crtc);
	पूर्ण

	अगर (new_crtc_state->update_pipe && !new_crtc_state->enable_fbc)
		पूर्णांकel_fbc_disable(crtc);
	अन्यथा
		पूर्णांकel_fbc_enable(state, crtc);

	/* Perक्रमm vblank evasion around commit operation */
	पूर्णांकel_pipe_update_start(new_crtc_state);

	commit_pipe_config(state, crtc);

	अगर (DISPLAY_VER(dev_priv) >= 9)
		skl_update_planes_on_crtc(state, crtc);
	अन्यथा
		i9xx_update_planes_on_crtc(state, crtc);

	पूर्णांकel_pipe_update_end(new_crtc_state);

	/*
	 * We usually enable FIFO underrun पूर्णांकerrupts as part of the
	 * CRTC enable sequence during modesets.  But when we inherit a
	 * valid pipe configuration from the BIOS we need to take care
	 * of enabling them on the CRTC's first fastset.
	 */
	अगर (new_crtc_state->update_pipe && !modeset &&
	    old_crtc_state->inherited)
		पूर्णांकel_crtc_arm_fअगरo_underrun(crtc, new_crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_old_crtc_state_disables(काष्ठा पूर्णांकel_atomic_state *state,
					  काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
					  काष्ठा पूर्णांकel_crtc_state *new_crtc_state,
					  काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);

	drm_WARN_ON(&dev_priv->drm, old_crtc_state->bigjoiner_slave);

	पूर्णांकel_crtc_disable_planes(state, crtc);

	/*
	 * We still need special handling क्रम disabling bigjoiner master
	 * and slaves since क्रम slave we करो not have encoder or plls
	 * so we करोnt need to disable those.
	 */
	अगर (old_crtc_state->bigjoiner) अणु
		पूर्णांकel_crtc_disable_planes(state,
					  old_crtc_state->bigjoiner_linked_crtc);
		old_crtc_state->bigjoiner_linked_crtc->active = false;
	पूर्ण

	/*
	 * We need to disable pipe CRC beक्रमe disabling the pipe,
	 * or we race against vblank off.
	 */
	पूर्णांकel_crtc_disable_pipe_crc(crtc);

	dev_priv->display.crtc_disable(state, crtc);
	crtc->active = false;
	पूर्णांकel_fbc_disable(crtc);
	पूर्णांकel_disable_shared_dpll(old_crtc_state);

	/* FIXME unअगरy this क्रम all platक्रमms */
	अगर (!new_crtc_state->hw.active &&
	    !HAS_GMCH(dev_priv) &&
	    dev_priv->display.initial_watermarks)
		dev_priv->display.initial_watermarks(state, crtc);
पूर्ण

अटल व्योम पूर्णांकel_commit_modeset_disables(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state, *old_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	u32 handled = 0;
	पूर्णांक i;

	/* Only disable port sync and MST slaves */
	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state) || old_crtc_state->bigjoiner)
			जारी;

		अगर (!old_crtc_state->hw.active)
			जारी;

		/* In हाल of Transcoder port Sync master slave CRTCs can be
		 * asचिन्हित in any order and we need to make sure that
		 * slave CRTCs are disabled first and then master CRTC since
		 * Slave vblanks are masked till Master Vblanks.
		 */
		अगर (!is_trans_port_sync_slave(old_crtc_state) &&
		    !पूर्णांकel_dp_mst_is_slave_trans(old_crtc_state))
			जारी;

		पूर्णांकel_pre_plane_update(state, crtc);
		पूर्णांकel_old_crtc_state_disables(state, old_crtc_state,
					      new_crtc_state, crtc);
		handled |= BIT(crtc->pipe);
	पूर्ण

	/* Disable everything अन्यथा left on */
	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state) ||
		    (handled & BIT(crtc->pipe)) ||
		    old_crtc_state->bigjoiner_slave)
			जारी;

		पूर्णांकel_pre_plane_update(state, crtc);
		अगर (old_crtc_state->bigjoiner) अणु
			काष्ठा पूर्णांकel_crtc *slave =
				old_crtc_state->bigjoiner_linked_crtc;

			पूर्णांकel_pre_plane_update(state, slave);
		पूर्ण

		अगर (old_crtc_state->hw.active)
			पूर्णांकel_old_crtc_state_disables(state, old_crtc_state,
						      new_crtc_state, crtc);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_commit_modeset_enables(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (!new_crtc_state->hw.active)
			जारी;

		पूर्णांकel_enable_crtc(state, crtc);
		पूर्णांकel_update_crtc(state, crtc);
	पूर्ण
पूर्ण

अटल व्योम skl_commit_modeset_enables(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा skl_ddb_entry entries[I915_MAX_PIPES] = अणुपूर्ण;
	u8 update_pipes = 0, modeset_pipes = 0;
	पूर्णांक i;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		क्रमागत pipe pipe = crtc->pipe;

		अगर (!new_crtc_state->hw.active)
			जारी;

		/* ignore allocations क्रम crtc's that have been turned off. */
		अगर (!पूर्णांकel_crtc_needs_modeset(new_crtc_state)) अणु
			entries[pipe] = old_crtc_state->wm.skl.ddb;
			update_pipes |= BIT(pipe);
		पूर्ण अन्यथा अणु
			modeset_pipes |= BIT(pipe);
		पूर्ण
	पूर्ण

	/*
	 * Whenever the number of active pipes changes, we need to make sure we
	 * update the pipes in the right order so that their ddb allocations
	 * never overlap with each other between CRTC updates. Otherwise we'll
	 * cause pipe underruns and other bad stuff.
	 *
	 * So first lets enable all pipes that करो not need a fullmodeset as
	 * those करोn't have any बाह्यal dependency.
	 */
	जबतक (update_pipes) अणु
		क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
						    new_crtc_state, i) अणु
			क्रमागत pipe pipe = crtc->pipe;

			अगर ((update_pipes & BIT(pipe)) == 0)
				जारी;

			अगर (skl_ddb_allocation_overlaps(&new_crtc_state->wm.skl.ddb,
							entries, I915_MAX_PIPES, pipe))
				जारी;

			entries[pipe] = new_crtc_state->wm.skl.ddb;
			update_pipes &= ~BIT(pipe);

			पूर्णांकel_update_crtc(state, crtc);

			/*
			 * If this is an alपढ़ोy active pipe, it's DDB changed,
			 * and this isn't the last pipe that needs updating
			 * then we need to रुको क्रम a vblank to pass क्रम the
			 * new ddb allocation to take effect.
			 */
			अगर (!skl_ddb_entry_equal(&new_crtc_state->wm.skl.ddb,
						 &old_crtc_state->wm.skl.ddb) &&
			    (update_pipes | modeset_pipes))
				पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
		पूर्ण
	पूर्ण

	update_pipes = modeset_pipes;

	/*
	 * Enable all pipes that needs a modeset and करो not depends on other
	 * pipes
	 */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		क्रमागत pipe pipe = crtc->pipe;

		अगर ((modeset_pipes & BIT(pipe)) == 0)
			जारी;

		अगर (पूर्णांकel_dp_mst_is_slave_trans(new_crtc_state) ||
		    is_trans_port_sync_master(new_crtc_state) ||
		    (new_crtc_state->bigjoiner && !new_crtc_state->bigjoiner_slave))
			जारी;

		modeset_pipes &= ~BIT(pipe);

		पूर्णांकel_enable_crtc(state, crtc);
	पूर्ण

	/*
	 * Then we enable all reमुख्यing pipes that depend on other
	 * pipes: MST slaves and port sync masters, big joiner master
	 */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		क्रमागत pipe pipe = crtc->pipe;

		अगर ((modeset_pipes & BIT(pipe)) == 0)
			जारी;

		modeset_pipes &= ~BIT(pipe);

		पूर्णांकel_enable_crtc(state, crtc);
	पूर्ण

	/*
	 * Finally we करो the plane updates/etc. क्रम all pipes that got enabled.
	 */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		क्रमागत pipe pipe = crtc->pipe;

		अगर ((update_pipes & BIT(pipe)) == 0)
			जारी;

		drm_WARN_ON(&dev_priv->drm, skl_ddb_allocation_overlaps(&new_crtc_state->wm.skl.ddb,
									entries, I915_MAX_PIPES, pipe));

		entries[pipe] = new_crtc_state->wm.skl.ddb;
		update_pipes &= ~BIT(pipe);

		पूर्णांकel_update_crtc(state, crtc);
	पूर्ण

	drm_WARN_ON(&dev_priv->drm, modeset_pipes);
	drm_WARN_ON(&dev_priv->drm, update_pipes);
पूर्ण

अटल व्योम पूर्णांकel_atomic_helper_मुक्त_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_atomic_state *state, *next;
	काष्ठा llist_node *मुक्तd;

	मुक्तd = llist_del_all(&dev_priv->atomic_helper.मुक्त_list);
	llist_क्रम_each_entry_safe(state, next, मुक्तd, मुक्तd)
		drm_atomic_state_put(&state->base);
पूर्ण

अटल व्योम पूर्णांकel_atomic_helper_मुक्त_state_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा drm_i915_निजी *dev_priv =
		container_of(work, typeof(*dev_priv), atomic_helper.मुक्त_work);

	पूर्णांकel_atomic_helper_मुक्त_state(dev_priv);
पूर्ण

अटल व्योम पूर्णांकel_atomic_commit_fence_रुको(काष्ठा पूर्णांकel_atomic_state *पूर्णांकel_state)
अणु
	काष्ठा रुको_queue_entry रुको_fence, रुको_reset;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_state->base.dev);

	init_रुको_entry(&रुको_fence, 0);
	init_रुको_entry(&रुको_reset, 0);
	क्रम (;;) अणु
		prepare_to_रुको(&पूर्णांकel_state->commit_पढ़ोy.रुको,
				&रुको_fence, TASK_UNINTERRUPTIBLE);
		prepare_to_रुको(bit_रुकोqueue(&dev_priv->gt.reset.flags,
					      I915_RESET_MODESET),
				&रुको_reset, TASK_UNINTERRUPTIBLE);


		अगर (i915_sw_fence_करोne(&पूर्णांकel_state->commit_पढ़ोy) ||
		    test_bit(I915_RESET_MODESET, &dev_priv->gt.reset.flags))
			अवरोध;

		schedule();
	पूर्ण
	finish_रुको(&पूर्णांकel_state->commit_पढ़ोy.रुको, &रुको_fence);
	finish_रुको(bit_रुकोqueue(&dev_priv->gt.reset.flags,
				  I915_RESET_MODESET),
		    &रुको_reset);
पूर्ण

अटल व्योम पूर्णांकel_cleanup_dsbs(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_crtc_state *old_crtc_state, *new_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक i;

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i)
		पूर्णांकel_dsb_cleanup(old_crtc_state);
पूर्ण

अटल व्योम पूर्णांकel_atomic_cleanup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_atomic_state *state =
		container_of(work, काष्ठा पूर्णांकel_atomic_state, base.commit_work);
	काष्ठा drm_i915_निजी *i915 = to_i915(state->base.dev);

	पूर्णांकel_cleanup_dsbs(state);
	drm_atomic_helper_cleanup_planes(&i915->drm, &state->base);
	drm_atomic_helper_commit_cleanup_करोne(&state->base);
	drm_atomic_state_put(&state->base);

	पूर्णांकel_atomic_helper_मुक्त_state(i915);
पूर्ण

अटल व्योम पूर्णांकel_atomic_prepare_plane_clear_colors(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(state->base.dev);
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा पूर्णांकel_plane_state *plane_state;
	पूर्णांक i;

	क्रम_each_new_पूर्णांकel_plane_in_state(state, plane, plane_state, i) अणु
		काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
		पूर्णांक ret;

		अगर (!fb ||
		    fb->modअगरier != I915_FORMAT_MOD_Y_TILED_GEN12_RC_CCS_CC)
			जारी;

		/*
		 * The layout of the fast clear color value expected by HW
		 * (the DRM ABI requiring this value to be located in fb at offset 0 of plane#2):
		 * - 4 x 4 bytes per-channel value
		 *   (in surface type specअगरic भग्न/पूर्णांक क्रमmat provided by the fb user)
		 * - 8 bytes native color value used by the display
		 *   (converted/written by GPU during a fast clear operation using the
		 *    above per-channel values)
		 *
		 * The commit's FB prepare hook alपढ़ोy ensured that FB obj is pinned and the
		 * caller made sure that the object is synced wrt. the related color clear value
		 * GPU ग_लिखो on it.
		 */
		ret = i915_gem_object_पढ़ो_from_page(पूर्णांकel_fb_obj(fb),
						     fb->offsets[2] + 16,
						     &plane_state->ccval,
						     माप(plane_state->ccval));
		/* The above could only fail अगर the FB obj has an unexpected backing store type. */
		drm_WARN_ON(&i915->drm, ret);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_atomic_commit_tail(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा drm_device *dev = state->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc_state *new_crtc_state, *old_crtc_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	u64 put_करोमुख्यs[I915_MAX_PIPES] = अणुपूर्ण;
	पूर्णांकel_wakeref_t wakeref = 0;
	पूर्णांक i;

	पूर्णांकel_atomic_commit_fence_रुको(state);

	drm_atomic_helper_रुको_क्रम_dependencies(&state->base);

	अगर (state->modeset)
		wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_MODESET);

	पूर्णांकel_atomic_prepare_plane_clear_colors(state);

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		अगर (पूर्णांकel_crtc_needs_modeset(new_crtc_state) ||
		    new_crtc_state->update_pipe) अणु

			put_करोमुख्यs[crtc->pipe] =
				modeset_get_crtc_घातer_करोमुख्यs(new_crtc_state);
		पूर्ण
	पूर्ण

	पूर्णांकel_commit_modeset_disables(state);

	/* FIXME: Eventually get rid of our crtc->config poपूर्णांकer */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i)
		crtc->config = new_crtc_state;

	अगर (state->modeset) अणु
		drm_atomic_helper_update_legacy_modeset_state(dev, &state->base);

		पूर्णांकel_set_cdclk_pre_plane_update(state);

		पूर्णांकel_modeset_verअगरy_disabled(dev_priv, state);
	पूर्ण

	पूर्णांकel_sagv_pre_plane_update(state);

	/* Complete the events क्रम pipes that have now been disabled */
	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		bool modeset = पूर्णांकel_crtc_needs_modeset(new_crtc_state);

		/* Complete events क्रम now disable pipes here. */
		अगर (modeset && !new_crtc_state->hw.active && new_crtc_state->uapi.event) अणु
			spin_lock_irq(&dev->event_lock);
			drm_crtc_send_vblank_event(&crtc->base,
						   new_crtc_state->uapi.event);
			spin_unlock_irq(&dev->event_lock);

			new_crtc_state->uapi.event = शून्य;
		पूर्ण
	पूर्ण

	अगर (state->modeset)
		पूर्णांकel_encoders_update_prepare(state);

	पूर्णांकel_dbuf_pre_plane_update(state);

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (new_crtc_state->uapi.async_flip)
			पूर्णांकel_crtc_enable_flip_करोne(state, crtc);
	पूर्ण

	/* Now enable the घड़ीs, plane, pipe, and connectors that we set up. */
	dev_priv->display.commit_modeset_enables(state);

	अगर (state->modeset) अणु
		पूर्णांकel_encoders_update_complete(state);

		पूर्णांकel_set_cdclk_post_plane_update(state);
	पूर्ण

	/* FIXME: We should call drm_atomic_helper_commit_hw_करोne() here
	 * alपढ़ोy, but still need the state क्रम the delayed optimization. To
	 * fix this:
	 * - wrap the optimization/post_plane_update stuff पूर्णांकo a per-crtc work.
	 * - schedule that vblank worker _beक्रमe_ calling hw_करोne
	 * - at the start of commit_tail, cancel it _synchrously
	 * - चयन over to the vblank रुको helper in the core after that since
	 *   we करोn't need out special handling any more.
	 */
	drm_atomic_helper_रुको_क्रम_flip_करोne(dev, &state->base);

	क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i) अणु
		अगर (new_crtc_state->uapi.async_flip)
			पूर्णांकel_crtc_disable_flip_करोne(state, crtc);

		अगर (new_crtc_state->hw.active &&
		    !पूर्णांकel_crtc_needs_modeset(new_crtc_state) &&
		    !new_crtc_state->preload_luts &&
		    (new_crtc_state->uapi.color_mgmt_changed ||
		     new_crtc_state->update_pipe))
			पूर्णांकel_color_load_luts(new_crtc_state);
	पूर्ण

	/*
	 * Now that the vblank has passed, we can go ahead and program the
	 * optimal watermarks on platक्रमms that need two-step watermark
	 * programming.
	 *
	 * TODO: Move this (and other cleanup) to an async worker eventually.
	 */
	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state,
					    new_crtc_state, i) अणु
		/*
		 * Gen2 reports pipe underruns whenever all planes are disabled.
		 * So re-enable underrun reporting after some planes get enabled.
		 *
		 * We करो this beक्रमe .optimize_watermarks() so that we have a
		 * chance of catching underruns with the पूर्णांकermediate watermarks
		 * vs. the new plane configuration.
		 */
		अगर (IS_DISPLAY_VER(dev_priv, 2) && planes_enabling(old_crtc_state, new_crtc_state))
			पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, crtc->pipe, true);

		अगर (dev_priv->display.optimize_watermarks)
			dev_priv->display.optimize_watermarks(state, crtc);
	पूर्ण

	पूर्णांकel_dbuf_post_plane_update(state);

	क्रम_each_oldnew_पूर्णांकel_crtc_in_state(state, crtc, old_crtc_state, new_crtc_state, i) अणु
		पूर्णांकel_post_plane_update(state, crtc);

		modeset_put_crtc_घातer_करोमुख्यs(crtc, put_करोमुख्यs[crtc->pipe]);

		पूर्णांकel_modeset_verअगरy_crtc(crtc, state, old_crtc_state, new_crtc_state);

		/*
		 * DSB cleanup is करोne in cleanup_work aligning with framebuffer
		 * cleanup. So copy and reset the dsb काष्ठाure to sync with
		 * commit_करोne and later करो dsb cleanup in cleanup_work.
		 */
		old_crtc_state->dsb = fetch_and_zero(&new_crtc_state->dsb);
	पूर्ण

	/* Underruns करोn't always उठाओ पूर्णांकerrupts, so check manually */
	पूर्णांकel_check_cpu_fअगरo_underruns(dev_priv);
	पूर्णांकel_check_pch_fअगरo_underruns(dev_priv);

	अगर (state->modeset)
		पूर्णांकel_verअगरy_planes(state);

	पूर्णांकel_sagv_post_plane_update(state);

	drm_atomic_helper_commit_hw_करोne(&state->base);

	अगर (state->modeset) अणु
		/* As one of the primary mmio accessors, KMS has a high
		 * likelihood of triggering bugs in unclaimed access. After we
		 * finish modesetting, see अगर an error has been flagged, and अगर
		 * so enable debugging क्रम the next modeset - and hope we catch
		 * the culprit.
		 */
		पूर्णांकel_uncore_arm_unclaimed_mmio_detection(&dev_priv->uncore);
		पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_MODESET, wakeref);
	पूर्ण
	पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, state->wakeref);

	/*
	 * Defer the cleanup of the old state to a separate worker to not
	 * impede the current task (userspace क्रम blocking modesets) that
	 * are executed अंतरभूत. For out-of-line asynchronous modesets/flips,
	 * deferring to a new worker seems overसमाप्त, but we would place a
	 * schedule poपूर्णांक (cond_resched()) here anyway to keep latencies
	 * करोwn.
	 */
	INIT_WORK(&state->base.commit_work, पूर्णांकel_atomic_cleanup_work);
	queue_work(प्रणाली_highpri_wq, &state->base.commit_work);
पूर्ण

अटल व्योम पूर्णांकel_atomic_commit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांकel_atomic_state *state =
		container_of(work, काष्ठा पूर्णांकel_atomic_state, base.commit_work);

	पूर्णांकel_atomic_commit_tail(state);
पूर्ण

अटल पूर्णांक __i915_sw_fence_call
पूर्णांकel_atomic_commit_पढ़ोy(काष्ठा i915_sw_fence *fence,
			  क्रमागत i915_sw_fence_notअगरy notअगरy)
अणु
	काष्ठा पूर्णांकel_atomic_state *state =
		container_of(fence, काष्ठा पूर्णांकel_atomic_state, commit_पढ़ोy);

	चयन (notअगरy) अणु
	हाल FENCE_COMPLETE:
		/* we करो blocking रुकोs in the worker, nothing to करो here */
		अवरोध;
	हाल FENCE_FREE:
		अणु
			काष्ठा पूर्णांकel_atomic_helper *helper =
				&to_i915(state->base.dev)->atomic_helper;

			अगर (llist_add(&state->मुक्तd, &helper->मुक्त_list))
				schedule_work(&helper->मुक्त_work);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम पूर्णांकel_atomic_track_fbs(काष्ठा पूर्णांकel_atomic_state *state)
अणु
	काष्ठा पूर्णांकel_plane_state *old_plane_state, *new_plane_state;
	काष्ठा पूर्णांकel_plane *plane;
	पूर्णांक i;

	क्रम_each_oldnew_पूर्णांकel_plane_in_state(state, plane, old_plane_state,
					     new_plane_state, i)
		पूर्णांकel_frontbuffer_track(to_पूर्णांकel_frontbuffer(old_plane_state->hw.fb),
					to_पूर्णांकel_frontbuffer(new_plane_state->hw.fb),
					plane->frontbuffer_bit);
पूर्ण

अटल पूर्णांक पूर्णांकel_atomic_commit(काष्ठा drm_device *dev,
			       काष्ठा drm_atomic_state *_state,
			       bool nonblock)
अणु
	काष्ठा पूर्णांकel_atomic_state *state = to_पूर्णांकel_atomic_state(_state);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	पूर्णांक ret = 0;

	state->wakeref = पूर्णांकel_runसमय_pm_get(&dev_priv->runसमय_pm);

	drm_atomic_state_get(&state->base);
	i915_sw_fence_init(&state->commit_पढ़ोy,
			   पूर्णांकel_atomic_commit_पढ़ोy);

	/*
	 * The पूर्णांकel_legacy_cursor_update() fast path takes care
	 * of aव्योमing the vblank रुकोs क्रम simple cursor
	 * movement and flips. For cursor on/off and size changes,
	 * we want to perक्रमm the vblank रुकोs so that watermark
	 * updates happen during the correct frames. Gen9+ have
	 * द्विगुन buffered watermarks and so shouldn't need this.
	 *
	 * Unset state->legacy_cursor_update beक्रमe the call to
	 * drm_atomic_helper_setup_commit() because otherwise
	 * drm_atomic_helper_रुको_क्रम_flip_करोne() is a noop and
	 * we get FIFO underruns because we didn't रुको
	 * क्रम vblank.
	 *
	 * FIXME करोing watermarks and fb cleanup from a vblank worker
	 * (assuming we had any) would solve these problems.
	 */
	अगर (DISPLAY_VER(dev_priv) < 9 && state->base.legacy_cursor_update) अणु
		काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc;
		पूर्णांक i;

		क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i)
			अगर (new_crtc_state->wm.need_postvbl_update ||
			    new_crtc_state->update_wm_post)
				state->base.legacy_cursor_update = false;
	पूर्ण

	ret = पूर्णांकel_atomic_prepare_commit(state);
	अगर (ret) अणु
		drm_dbg_atomic(&dev_priv->drm,
			       "Preparing state failed with %i\n", ret);
		i915_sw_fence_commit(&state->commit_पढ़ोy);
		पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, state->wakeref);
		वापस ret;
	पूर्ण

	ret = drm_atomic_helper_setup_commit(&state->base, nonblock);
	अगर (!ret)
		ret = drm_atomic_helper_swap_state(&state->base, true);
	अगर (!ret)
		पूर्णांकel_atomic_swap_global_state(state);

	अगर (ret) अणु
		काष्ठा पूर्णांकel_crtc_state *new_crtc_state;
		काष्ठा पूर्णांकel_crtc *crtc;
		पूर्णांक i;

		i915_sw_fence_commit(&state->commit_पढ़ोy);

		क्रम_each_new_पूर्णांकel_crtc_in_state(state, crtc, new_crtc_state, i)
			पूर्णांकel_dsb_cleanup(new_crtc_state);

		drm_atomic_helper_cleanup_planes(dev, &state->base);
		पूर्णांकel_runसमय_pm_put(&dev_priv->runसमय_pm, state->wakeref);
		वापस ret;
	पूर्ण
	पूर्णांकel_shared_dpll_swap_state(state);
	पूर्णांकel_atomic_track_fbs(state);

	drm_atomic_state_get(&state->base);
	INIT_WORK(&state->base.commit_work, पूर्णांकel_atomic_commit_work);

	i915_sw_fence_commit(&state->commit_पढ़ोy);
	अगर (nonblock && state->modeset) अणु
		queue_work(dev_priv->modeset_wq, &state->base.commit_work);
	पूर्ण अन्यथा अगर (nonblock) अणु
		queue_work(dev_priv->flip_wq, &state->base.commit_work);
	पूर्ण अन्यथा अणु
		अगर (state->modeset)
			flush_workqueue(dev_priv->modeset_wq);
		पूर्णांकel_atomic_commit_tail(state);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा रुको_rps_boost अणु
	काष्ठा रुको_queue_entry रुको;

	काष्ठा drm_crtc *crtc;
	काष्ठा i915_request *request;
पूर्ण;

अटल पूर्णांक करो_rps_boost(काष्ठा रुको_queue_entry *_रुको,
			अचिन्हित mode, पूर्णांक sync, व्योम *key)
अणु
	काष्ठा रुको_rps_boost *रुको = container_of(_रुको, typeof(*रुको), रुको);
	काष्ठा i915_request *rq = रुको->request;

	/*
	 * If we missed the vblank, but the request is alपढ़ोy running it
	 * is reasonable to assume that it will complete beक्रमe the next
	 * vblank without our पूर्णांकervention, so leave RPS alone.
	 */
	अगर (!i915_request_started(rq))
		पूर्णांकel_rps_boost(rq);
	i915_request_put(rq);

	drm_crtc_vblank_put(रुको->crtc);

	list_del(&रुको->रुको.entry);
	kमुक्त(रुको);
	वापस 1;
पूर्ण

अटल व्योम add_rps_boost_after_vblank(काष्ठा drm_crtc *crtc,
				       काष्ठा dma_fence *fence)
अणु
	काष्ठा रुको_rps_boost *रुको;

	अगर (!dma_fence_is_i915(fence))
		वापस;

	अगर (DISPLAY_VER(to_i915(crtc->dev)) < 6)
		वापस;

	अगर (drm_crtc_vblank_get(crtc))
		वापस;

	रुको = kदो_स्मृति(माप(*रुको), GFP_KERNEL);
	अगर (!रुको) अणु
		drm_crtc_vblank_put(crtc);
		वापस;
	पूर्ण

	रुको->request = to_request(dma_fence_get(fence));
	रुको->crtc = crtc;

	रुको->रुको.func = करो_rps_boost;
	रुको->रुको.flags = 0;

	add_रुको_queue(drm_crtc_vblank_रुकोqueue(crtc), &रुको->रुको);
पूर्ण

पूर्णांक पूर्णांकel_plane_pin_fb(काष्ठा पूर्णांकel_plane_state *plane_state)
अणु
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(plane_state->uapi.plane);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	काष्ठा drm_framebuffer *fb = plane_state->hw.fb;
	काष्ठा i915_vma *vma;
	bool phys_cursor =
		plane->id == PLANE_CURSOR &&
		INTEL_INFO(dev_priv)->display.cursor_needs_physical;

	vma = पूर्णांकel_pin_and_fence_fb_obj(fb, phys_cursor,
					 &plane_state->view.gtt,
					 पूर्णांकel_plane_uses_fence(plane_state),
					 &plane_state->flags);
	अगर (IS_ERR(vma))
		वापस PTR_ERR(vma);

	plane_state->vma = vma;

	वापस 0;
पूर्ण

व्योम पूर्णांकel_plane_unpin_fb(काष्ठा पूर्णांकel_plane_state *old_plane_state)
अणु
	काष्ठा i915_vma *vma;

	vma = fetch_and_zero(&old_plane_state->vma);
	अगर (vma)
		पूर्णांकel_unpin_fb_vma(vma, old_plane_state->flags);
पूर्ण

/**
 * पूर्णांकel_prepare_plane_fb - Prepare fb क्रम usage on plane
 * @_plane: drm plane to prepare क्रम
 * @_new_plane_state: the plane state being prepared
 *
 * Prepares a framebuffer क्रम usage on a display plane.  Generally this
 * involves pinning the underlying object and updating the frontbuffer tracking
 * bits.  Some older platक्रमms need special physical address handling क्रम
 * cursor planes.
 *
 * Returns 0 on success, negative error code on failure.
 */
पूर्णांक
पूर्णांकel_prepare_plane_fb(काष्ठा drm_plane *_plane,
		       काष्ठा drm_plane_state *_new_plane_state)
अणु
	काष्ठा i915_sched_attr attr = अणु .priority = I915_PRIORITY_DISPLAY पूर्ण;
	काष्ठा पूर्णांकel_plane *plane = to_पूर्णांकel_plane(_plane);
	काष्ठा पूर्णांकel_plane_state *new_plane_state =
		to_पूर्णांकel_plane_state(_new_plane_state);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(new_plane_state->uapi.state);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);
	स्थिर काष्ठा पूर्णांकel_plane_state *old_plane_state =
		पूर्णांकel_atomic_get_old_plane_state(state, plane);
	काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(new_plane_state->hw.fb);
	काष्ठा drm_i915_gem_object *old_obj = पूर्णांकel_fb_obj(old_plane_state->hw.fb);
	पूर्णांक ret;

	अगर (old_obj) अणु
		स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state =
			पूर्णांकel_atomic_get_new_crtc_state(state,
							to_पूर्णांकel_crtc(old_plane_state->hw.crtc));

		/* Big Hammer, we also need to ensure that any pending
		 * MI_WAIT_FOR_EVENT inside a user batch buffer on the
		 * current scanout is retired beक्रमe unpinning the old
		 * framebuffer. Note that we rely on userspace rendering
		 * पूर्णांकo the buffer attached to the pipe they are रुकोing
		 * on. If not, userspace generates a GPU hang with IPEHR
		 * poपूर्णांक to the MI_WAIT_FOR_EVENT.
		 *
		 * This should only fail upon a hung GPU, in which हाल we
		 * can safely जारी.
		 */
		अगर (पूर्णांकel_crtc_needs_modeset(crtc_state)) अणु
			ret = i915_sw_fence_aरुको_reservation(&state->commit_पढ़ोy,
							      old_obj->base.resv, शून्य,
							      false, 0,
							      GFP_KERNEL);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
	पूर्ण

	अगर (new_plane_state->uapi.fence) अणु /* explicit fencing */
		i915_gem_fence_रुको_priority(new_plane_state->uapi.fence,
					     &attr);
		ret = i915_sw_fence_aरुको_dma_fence(&state->commit_पढ़ोy,
						    new_plane_state->uapi.fence,
						    i915_fence_समयout(dev_priv),
						    GFP_KERNEL);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (!obj)
		वापस 0;


	ret = पूर्णांकel_plane_pin_fb(new_plane_state);
	अगर (ret)
		वापस ret;

	i915_gem_object_रुको_priority(obj, 0, &attr);
	i915_gem_object_flush_frontbuffer(obj, ORIGIN_सूचीTYFB);

	अगर (!new_plane_state->uapi.fence) अणु /* implicit fencing */
		काष्ठा dma_fence *fence;

		ret = i915_sw_fence_aरुको_reservation(&state->commit_पढ़ोy,
						      obj->base.resv, शून्य,
						      false,
						      i915_fence_समयout(dev_priv),
						      GFP_KERNEL);
		अगर (ret < 0)
			जाओ unpin_fb;

		fence = dma_resv_get_excl_rcu(obj->base.resv);
		अगर (fence) अणु
			add_rps_boost_after_vblank(new_plane_state->hw.crtc,
						   fence);
			dma_fence_put(fence);
		पूर्ण
	पूर्ण अन्यथा अणु
		add_rps_boost_after_vblank(new_plane_state->hw.crtc,
					   new_plane_state->uapi.fence);
	पूर्ण

	/*
	 * We declare pageflips to be पूर्णांकeractive and so merit a small bias
	 * towards upघड़ीing to deliver the frame on समय. By only changing
	 * the RPS thresholds to sample more regularly and aim क्रम higher
	 * घड़ीs we can hopefully deliver low घातer workloads (like kodi)
	 * that are not quite steady state without resorting to क्रमcing
	 * maximum घड़ीs following a vblank miss (see करो_rps_boost()).
	 */
	अगर (!state->rps_पूर्णांकeractive) अणु
		पूर्णांकel_rps_mark_पूर्णांकeractive(&dev_priv->gt.rps, true);
		state->rps_पूर्णांकeractive = true;
	पूर्ण

	वापस 0;

unpin_fb:
	पूर्णांकel_plane_unpin_fb(new_plane_state);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_cleanup_plane_fb - Cleans up an fb after plane use
 * @plane: drm plane to clean up क्रम
 * @_old_plane_state: the state from the previous modeset
 *
 * Cleans up a framebuffer that has just been हटाओd from a plane.
 */
व्योम
पूर्णांकel_cleanup_plane_fb(काष्ठा drm_plane *plane,
		       काष्ठा drm_plane_state *_old_plane_state)
अणु
	काष्ठा पूर्णांकel_plane_state *old_plane_state =
		to_पूर्णांकel_plane_state(_old_plane_state);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(old_plane_state->uapi.state);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->dev);
	काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(old_plane_state->hw.fb);

	अगर (!obj)
		वापस;

	अगर (state->rps_पूर्णांकeractive) अणु
		पूर्णांकel_rps_mark_पूर्णांकeractive(&dev_priv->gt.rps, false);
		state->rps_पूर्णांकeractive = false;
	पूर्ण

	/* Should only be called after a successful पूर्णांकel_prepare_plane_fb()! */
	पूर्णांकel_plane_unpin_fb(old_plane_state);
पूर्ण

/**
 * पूर्णांकel_plane_destroy - destroy a plane
 * @plane: plane to destroy
 *
 * Common deकाष्ठाion function क्रम all types of planes (primary, cursor,
 * sprite).
 */
व्योम पूर्णांकel_plane_destroy(काष्ठा drm_plane *plane)
अणु
	drm_plane_cleanup(plane);
	kमुक्त(to_पूर्णांकel_plane(plane));
पूर्ण

अटल व्योम पूर्णांकel_plane_possible_crtcs_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_plane *plane;

	क्रम_each_पूर्णांकel_plane(&dev_priv->drm, plane) अणु
		काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv,
								  plane->pipe);

		plane->base.possible_crtcs = drm_crtc_mask(&crtc->base);
	पूर्ण
पूर्ण


पूर्णांक पूर्णांकel_get_pipe_from_crtc_id_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_get_pipe_from_crtc_id *pipe_from_crtc_id = data;
	काष्ठा drm_crtc *drmmode_crtc;
	काष्ठा पूर्णांकel_crtc *crtc;

	drmmode_crtc = drm_crtc_find(dev, file, pipe_from_crtc_id->crtc_id);
	अगर (!drmmode_crtc)
		वापस -ENOENT;

	crtc = to_पूर्णांकel_crtc(drmmode_crtc);
	pipe_from_crtc_id->pipe = crtc->pipe;

	वापस 0;
पूर्ण

अटल u32 पूर्णांकel_encoder_possible_clones(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा पूर्णांकel_encoder *source_encoder;
	u32 possible_clones = 0;

	क्रम_each_पूर्णांकel_encoder(dev, source_encoder) अणु
		अगर (encoders_cloneable(encoder, source_encoder))
			possible_clones |= drm_encoder_mask(&source_encoder->base);
	पूर्ण

	वापस possible_clones;
पूर्ण

अटल u32 पूर्णांकel_encoder_possible_crtcs(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा पूर्णांकel_crtc *crtc;
	u32 possible_crtcs = 0;

	क्रम_each_पूर्णांकel_crtc(dev, crtc) अणु
		अगर (encoder->pipe_mask & BIT(crtc->pipe))
			possible_crtcs |= drm_crtc_mask(&crtc->base);
	पूर्ण

	वापस possible_crtcs;
पूर्ण

अटल bool ilk_has_edp_a(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (!IS_MOBILE(dev_priv))
		वापस false;

	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, DP_A) & DP_DETECTED) == 0)
		वापस false;

	अगर (IS_IRONLAKE(dev_priv) && (पूर्णांकel_de_पढ़ो(dev_priv, FUSE_STRAP) & ILK_eDP_A_DISABLE))
		वापस false;

	वापस true;
पूर्ण

अटल bool पूर्णांकel_ddi_crt_present(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (DISPLAY_VER(dev_priv) >= 9)
		वापस false;

	अगर (IS_HSW_ULT(dev_priv) || IS_BDW_ULT(dev_priv))
		वापस false;

	अगर (HAS_PCH_LPT_H(dev_priv) &&
	    पूर्णांकel_de_पढ़ो(dev_priv, SFUSE_STRAP) & SFUSE_STRAP_CRT_DISABLED)
		वापस false;

	/* DDI E can't be used अगर DDI A requires 4 lanes */
	अगर (पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(PORT_A)) & DDI_A_4_LANES)
		वापस false;

	अगर (!dev_priv->vbt.पूर्णांक_crt_support)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम पूर्णांकel_setup_outमाला_दो(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;
	bool dpd_is_edp = false;

	पूर्णांकel_pps_unlock_regs_wa(dev_priv);

	अगर (!HAS_DISPLAY(dev_priv))
		वापस;

	अगर (IS_ALDERLAKE_S(dev_priv)) अणु
		पूर्णांकel_ddi_init(dev_priv, PORT_A);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC1);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC2);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC3);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC4);
	पूर्ण अन्यथा अगर (IS_DG1(dev_priv) || IS_ROCKETLAKE(dev_priv)) अणु
		पूर्णांकel_ddi_init(dev_priv, PORT_A);
		पूर्णांकel_ddi_init(dev_priv, PORT_B);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC1);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC2);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		पूर्णांकel_ddi_init(dev_priv, PORT_A);
		पूर्णांकel_ddi_init(dev_priv, PORT_B);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC1);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC2);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC3);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC4);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC5);
		पूर्णांकel_ddi_init(dev_priv, PORT_TC6);
		icl_dsi_init(dev_priv);
	पूर्ण अन्यथा अगर (IS_JSL_EHL(dev_priv)) अणु
		पूर्णांकel_ddi_init(dev_priv, PORT_A);
		पूर्णांकel_ddi_init(dev_priv, PORT_B);
		पूर्णांकel_ddi_init(dev_priv, PORT_C);
		पूर्णांकel_ddi_init(dev_priv, PORT_D);
		icl_dsi_init(dev_priv);
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 11)) अणु
		पूर्णांकel_ddi_init(dev_priv, PORT_A);
		पूर्णांकel_ddi_init(dev_priv, PORT_B);
		पूर्णांकel_ddi_init(dev_priv, PORT_C);
		पूर्णांकel_ddi_init(dev_priv, PORT_D);
		पूर्णांकel_ddi_init(dev_priv, PORT_E);
		/*
		 * On some ICL SKUs port F is not present. No strap bits क्रम
		 * this, so rely on VBT.
		 * Work around broken VBTs on SKUs known to have no port F.
		 */
		अगर (IS_ICL_WITH_PORT_F(dev_priv) &&
		    पूर्णांकel_bios_is_port_present(dev_priv, PORT_F))
			पूर्णांकel_ddi_init(dev_priv, PORT_F);

		icl_dsi_init(dev_priv);
	पूर्ण अन्यथा अगर (IS_GEN9_LP(dev_priv)) अणु
		/*
		 * FIXME: Broxton करोesn't support port detection via the
		 * DDI_BUF_CTL_A or SFUSE_STRAP रेजिस्टरs, find another way to
		 * detect the ports.
		 */
		पूर्णांकel_ddi_init(dev_priv, PORT_A);
		पूर्णांकel_ddi_init(dev_priv, PORT_B);
		पूर्णांकel_ddi_init(dev_priv, PORT_C);

		vlv_dsi_init(dev_priv);
	पूर्ण अन्यथा अगर (HAS_DDI(dev_priv)) अणु
		पूर्णांक found;

		अगर (पूर्णांकel_ddi_crt_present(dev_priv))
			पूर्णांकel_crt_init(dev_priv);

		/*
		 * Haswell uses DDI functions to detect digital outमाला_दो.
		 * On SKL pre-D0 the strap isn't connected. Later SKUs may or
		 * may not have it - it was supposed to be fixed by the same
		 * समय we stopped using straps. Assume it's there.
		 */
		found = पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(PORT_A)) & DDI_INIT_DISPLAY_DETECTED;
		/* WaIgnoreDDIAStrap: skl */
		अगर (found || IS_GEN9_BC(dev_priv))
			पूर्णांकel_ddi_init(dev_priv, PORT_A);

		/* DDI B, C, D, and F detection is indicated by the SFUSE_STRAP
		 * रेजिस्टर */
		अगर (HAS_PCH_TGP(dev_priv)) अणु
			/* W/A due to lack of STRAP config on TGP PCH*/
			found = (SFUSE_STRAP_DDIB_DETECTED |
				 SFUSE_STRAP_DDIC_DETECTED |
				 SFUSE_STRAP_DDID_DETECTED);
		पूर्ण अन्यथा अणु
			found = पूर्णांकel_de_पढ़ो(dev_priv, SFUSE_STRAP);
		पूर्ण

		अगर (found & SFUSE_STRAP_DDIB_DETECTED)
			पूर्णांकel_ddi_init(dev_priv, PORT_B);
		अगर (found & SFUSE_STRAP_DDIC_DETECTED)
			पूर्णांकel_ddi_init(dev_priv, PORT_C);
		अगर (found & SFUSE_STRAP_DDID_DETECTED)
			पूर्णांकel_ddi_init(dev_priv, PORT_D);
		अगर (found & SFUSE_STRAP_DDIF_DETECTED)
			पूर्णांकel_ddi_init(dev_priv, PORT_F);
		/*
		 * On SKL we करोn't have a way to detect DDI-E so we rely on VBT.
		 */
		अगर (IS_GEN9_BC(dev_priv) &&
		    पूर्णांकel_bios_is_port_present(dev_priv, PORT_E))
			पूर्णांकel_ddi_init(dev_priv, PORT_E);

	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		पूर्णांक found;

		/*
		 * पूर्णांकel_edp_init_connector() depends on this completing first,
		 * to prevent the registration of both eDP and LVDS and the
		 * incorrect sharing of the PPS.
		 */
		पूर्णांकel_lvds_init(dev_priv);
		पूर्णांकel_crt_init(dev_priv);

		dpd_is_edp = पूर्णांकel_dp_is_port_edp(dev_priv, PORT_D);

		अगर (ilk_has_edp_a(dev_priv))
			g4x_dp_init(dev_priv, DP_A, PORT_A);

		अगर (पूर्णांकel_de_पढ़ो(dev_priv, PCH_HDMIB) & SDVO_DETECTED) अणु
			/* PCH SDVOB multiplex with HDMIB */
			found = पूर्णांकel_sdvo_init(dev_priv, PCH_SDVOB, PORT_B);
			अगर (!found)
				g4x_hdmi_init(dev_priv, PCH_HDMIB, PORT_B);
			अगर (!found && (पूर्णांकel_de_पढ़ो(dev_priv, PCH_DP_B) & DP_DETECTED))
				g4x_dp_init(dev_priv, PCH_DP_B, PORT_B);
		पूर्ण

		अगर (पूर्णांकel_de_पढ़ो(dev_priv, PCH_HDMIC) & SDVO_DETECTED)
			g4x_hdmi_init(dev_priv, PCH_HDMIC, PORT_C);

		अगर (!dpd_is_edp && पूर्णांकel_de_पढ़ो(dev_priv, PCH_HDMID) & SDVO_DETECTED)
			g4x_hdmi_init(dev_priv, PCH_HDMID, PORT_D);

		अगर (पूर्णांकel_de_पढ़ो(dev_priv, PCH_DP_C) & DP_DETECTED)
			g4x_dp_init(dev_priv, PCH_DP_C, PORT_C);

		अगर (पूर्णांकel_de_पढ़ो(dev_priv, PCH_DP_D) & DP_DETECTED)
			g4x_dp_init(dev_priv, PCH_DP_D, PORT_D);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		bool has_edp, has_port;

		अगर (IS_VALLEYVIEW(dev_priv) && dev_priv->vbt.पूर्णांक_crt_support)
			पूर्णांकel_crt_init(dev_priv);

		/*
		 * The DP_DETECTED bit is the latched state of the DDC
		 * SDA pin at boot. However since eDP करोesn't require DDC
		 * (no way to plug in a DP->HDMI करोngle) the DDC pins क्रम
		 * eDP ports may have been muxed to an alternate function.
		 * Thus we can't rely on the DP_DETECTED bit alone to detect
		 * eDP ports. Consult the VBT as well as DP_DETECTED to
		 * detect eDP ports.
		 *
		 * Sadly the straps seem to be missing someबार even क्रम HDMI
		 * ports (eg. on Voyo V3 - CHT x7-Z8700), so check both strap
		 * and VBT क्रम the presence of the port. Additionally we can't
		 * trust the port type the VBT declares as we've seen at least
		 * HDMI ports that the VBT claim are DP or eDP.
		 */
		has_edp = पूर्णांकel_dp_is_port_edp(dev_priv, PORT_B);
		has_port = पूर्णांकel_bios_is_port_present(dev_priv, PORT_B);
		अगर (पूर्णांकel_de_पढ़ो(dev_priv, VLV_DP_B) & DP_DETECTED || has_port)
			has_edp &= g4x_dp_init(dev_priv, VLV_DP_B, PORT_B);
		अगर ((पूर्णांकel_de_पढ़ो(dev_priv, VLV_HDMIB) & SDVO_DETECTED || has_port) && !has_edp)
			g4x_hdmi_init(dev_priv, VLV_HDMIB, PORT_B);

		has_edp = पूर्णांकel_dp_is_port_edp(dev_priv, PORT_C);
		has_port = पूर्णांकel_bios_is_port_present(dev_priv, PORT_C);
		अगर (पूर्णांकel_de_पढ़ो(dev_priv, VLV_DP_C) & DP_DETECTED || has_port)
			has_edp &= g4x_dp_init(dev_priv, VLV_DP_C, PORT_C);
		अगर ((पूर्णांकel_de_पढ़ो(dev_priv, VLV_HDMIC) & SDVO_DETECTED || has_port) && !has_edp)
			g4x_hdmi_init(dev_priv, VLV_HDMIC, PORT_C);

		अगर (IS_CHERRYVIEW(dev_priv)) अणु
			/*
			 * eDP not supported on port D,
			 * so no need to worry about it
			 */
			has_port = पूर्णांकel_bios_is_port_present(dev_priv, PORT_D);
			अगर (पूर्णांकel_de_पढ़ो(dev_priv, CHV_DP_D) & DP_DETECTED || has_port)
				g4x_dp_init(dev_priv, CHV_DP_D, PORT_D);
			अगर (पूर्णांकel_de_पढ़ो(dev_priv, CHV_HDMID) & SDVO_DETECTED || has_port)
				g4x_hdmi_init(dev_priv, CHV_HDMID, PORT_D);
		पूर्ण

		vlv_dsi_init(dev_priv);
	पूर्ण अन्यथा अगर (IS_PINEVIEW(dev_priv)) अणु
		पूर्णांकel_lvds_init(dev_priv);
		पूर्णांकel_crt_init(dev_priv);
	पूर्ण अन्यथा अगर (IS_DISPLAY_RANGE(dev_priv, 3, 4)) अणु
		bool found = false;

		अगर (IS_MOBILE(dev_priv))
			पूर्णांकel_lvds_init(dev_priv);

		पूर्णांकel_crt_init(dev_priv);

		अगर (पूर्णांकel_de_पढ़ो(dev_priv, GEN3_SDVOB) & SDVO_DETECTED) अणु
			drm_dbg_kms(&dev_priv->drm, "probing SDVOB\n");
			found = पूर्णांकel_sdvo_init(dev_priv, GEN3_SDVOB, PORT_B);
			अगर (!found && IS_G4X(dev_priv)) अणु
				drm_dbg_kms(&dev_priv->drm,
					    "probing HDMI on SDVOB\n");
				g4x_hdmi_init(dev_priv, GEN4_HDMIB, PORT_B);
			पूर्ण

			अगर (!found && IS_G4X(dev_priv))
				g4x_dp_init(dev_priv, DP_B, PORT_B);
		पूर्ण

		/* Beक्रमe G4X SDVOC करोesn't have its own detect रेजिस्टर */

		अगर (पूर्णांकel_de_पढ़ो(dev_priv, GEN3_SDVOB) & SDVO_DETECTED) अणु
			drm_dbg_kms(&dev_priv->drm, "probing SDVOC\n");
			found = पूर्णांकel_sdvo_init(dev_priv, GEN3_SDVOC, PORT_C);
		पूर्ण

		अगर (!found && (पूर्णांकel_de_पढ़ो(dev_priv, GEN3_SDVOC) & SDVO_DETECTED)) अणु

			अगर (IS_G4X(dev_priv)) अणु
				drm_dbg_kms(&dev_priv->drm,
					    "probing HDMI on SDVOC\n");
				g4x_hdmi_init(dev_priv, GEN4_HDMIC, PORT_C);
			पूर्ण
			अगर (IS_G4X(dev_priv))
				g4x_dp_init(dev_priv, DP_C, PORT_C);
		पूर्ण

		अगर (IS_G4X(dev_priv) && (पूर्णांकel_de_पढ़ो(dev_priv, DP_D) & DP_DETECTED))
			g4x_dp_init(dev_priv, DP_D, PORT_D);

		अगर (SUPPORTS_TV(dev_priv))
			पूर्णांकel_tv_init(dev_priv);
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 2)) अणु
		अगर (IS_I85X(dev_priv))
			पूर्णांकel_lvds_init(dev_priv);

		पूर्णांकel_crt_init(dev_priv);
		पूर्णांकel_dvo_init(dev_priv);
	पूर्ण

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		encoder->base.possible_crtcs =
			पूर्णांकel_encoder_possible_crtcs(encoder);
		encoder->base.possible_clones =
			पूर्णांकel_encoder_possible_clones(encoder);
	पूर्ण

	पूर्णांकel_init_pch_refclk(dev_priv);

	drm_helper_move_panel_connectors_to_head(&dev_priv->drm);
पूर्ण

अटल व्योम पूर्णांकel_user_framebuffer_destroy(काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb = to_पूर्णांकel_framebuffer(fb);

	drm_framebuffer_cleanup(fb);
	पूर्णांकel_frontbuffer_put(पूर्णांकel_fb->frontbuffer);

	kमुक्त(पूर्णांकel_fb);
पूर्ण

अटल पूर्णांक पूर्णांकel_user_framebuffer_create_handle(काष्ठा drm_framebuffer *fb,
						काष्ठा drm_file *file,
						अचिन्हित पूर्णांक *handle)
अणु
	काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(fb);
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);

	अगर (i915_gem_object_is_userptr(obj)) अणु
		drm_dbg(&i915->drm,
			"attempting to use a userptr for a framebuffer, denied\n");
		वापस -EINVAL;
	पूर्ण

	वापस drm_gem_handle_create(file, &obj->base, handle);
पूर्ण

अटल पूर्णांक पूर्णांकel_user_framebuffer_dirty(काष्ठा drm_framebuffer *fb,
					काष्ठा drm_file *file,
					अचिन्हित flags, अचिन्हित color,
					काष्ठा drm_clip_rect *clips,
					अचिन्हित num_clips)
अणु
	काष्ठा drm_i915_gem_object *obj = पूर्णांकel_fb_obj(fb);

	i915_gem_object_flush_अगर_display(obj);
	पूर्णांकel_frontbuffer_flush(to_पूर्णांकel_frontbuffer(fb), ORIGIN_सूचीTYFB);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_framebuffer_funcs पूर्णांकel_fb_funcs = अणु
	.destroy = पूर्णांकel_user_framebuffer_destroy,
	.create_handle = पूर्णांकel_user_framebuffer_create_handle,
	.dirty = पूर्णांकel_user_framebuffer_dirty,
पूर्ण;

अटल पूर्णांक पूर्णांकel_framebuffer_init(काष्ठा पूर्णांकel_framebuffer *पूर्णांकel_fb,
				  काष्ठा drm_i915_gem_object *obj,
				  काष्ठा drm_mode_fb_cmd2 *mode_cmd)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(obj->base.dev);
	काष्ठा drm_framebuffer *fb = &पूर्णांकel_fb->base;
	u32 max_stride;
	अचिन्हित पूर्णांक tiling, stride;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i;

	पूर्णांकel_fb->frontbuffer = पूर्णांकel_frontbuffer_get(obj);
	अगर (!पूर्णांकel_fb->frontbuffer)
		वापस -ENOMEM;

	i915_gem_object_lock(obj, शून्य);
	tiling = i915_gem_object_get_tiling(obj);
	stride = i915_gem_object_get_stride(obj);
	i915_gem_object_unlock(obj);

	अगर (mode_cmd->flags & DRM_MODE_FB_MODIFIERS) अणु
		/*
		 * If there's a fence, enक्रमce that
		 * the fb modअगरier and tiling mode match.
		 */
		अगर (tiling != I915_TILING_NONE &&
		    tiling != पूर्णांकel_fb_modअगरier_to_tiling(mode_cmd->modअगरier[0])) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "tiling_mode doesn't match fb modifier\n");
			जाओ err;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (tiling == I915_TILING_X) अणु
			mode_cmd->modअगरier[0] = I915_FORMAT_MOD_X_TILED;
		पूर्ण अन्यथा अगर (tiling == I915_TILING_Y) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "No Y tiling for legacy addfb\n");
			जाओ err;
		पूर्ण
	पूर्ण

	अगर (!drm_any_plane_has_क्रमmat(&dev_priv->drm,
				      mode_cmd->pixel_क्रमmat,
				      mode_cmd->modअगरier[0])) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "unsupported pixel format %p4cc / modifier 0x%llx\n",
			    &mode_cmd->pixel_क्रमmat, mode_cmd->modअगरier[0]);
		जाओ err;
	पूर्ण

	/*
	 * gen2/3 display engine uses the fence अगर present,
	 * so the tiling mode must match the fb modअगरier exactly.
	 */
	अगर (DISPLAY_VER(dev_priv) < 4 &&
	    tiling != पूर्णांकel_fb_modअगरier_to_tiling(mode_cmd->modअगरier[0])) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "tiling_mode must match fb modifier exactly on gen2/3\n");
		जाओ err;
	पूर्ण

	max_stride = पूर्णांकel_fb_max_stride(dev_priv, mode_cmd->pixel_क्रमmat,
					 mode_cmd->modअगरier[0]);
	अगर (mode_cmd->pitches[0] > max_stride) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "%s pitch (%u) must be at most %d\n",
			    mode_cmd->modअगरier[0] != DRM_FORMAT_MOD_LINEAR ?
			    "tiled" : "linear",
			    mode_cmd->pitches[0], max_stride);
		जाओ err;
	पूर्ण

	/*
	 * If there's a fence, enक्रमce that
	 * the fb pitch and fence stride match.
	 */
	अगर (tiling != I915_TILING_NONE && mode_cmd->pitches[0] != stride) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "pitch (%d) must match tiling stride (%d)\n",
			    mode_cmd->pitches[0], stride);
		जाओ err;
	पूर्ण

	/* FIXME need to adjust LINOFF/TILखातापूर्णF accordingly. */
	अगर (mode_cmd->offsets[0] != 0) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "plane 0 offset (0x%08x) must be 0\n",
			    mode_cmd->offsets[0]);
		जाओ err;
	पूर्ण

	drm_helper_mode_fill_fb_काष्ठा(&dev_priv->drm, fb, mode_cmd);

	क्रम (i = 0; i < fb->क्रमmat->num_planes; i++) अणु
		u32 stride_alignment;

		अगर (mode_cmd->handles[i] != mode_cmd->handles[0]) अणु
			drm_dbg_kms(&dev_priv->drm, "bad plane %d handle\n",
				    i);
			जाओ err;
		पूर्ण

		stride_alignment = पूर्णांकel_fb_stride_alignment(fb, i);
		अगर (fb->pitches[i] & (stride_alignment - 1)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "plane %d pitch (%d) must be at least %u byte aligned\n",
				    i, fb->pitches[i], stride_alignment);
			जाओ err;
		पूर्ण

		अगर (is_gen12_ccs_plane(fb, i) && !is_gen12_ccs_cc_plane(fb, i)) अणु
			पूर्णांक ccs_aux_stride = gen12_ccs_aux_stride(fb, i);

			अगर (fb->pitches[i] != ccs_aux_stride) अणु
				drm_dbg_kms(&dev_priv->drm,
					    "ccs aux plane %d pitch (%d) must be %d\n",
					    i,
					    fb->pitches[i], ccs_aux_stride);
				जाओ err;
			पूर्ण
		पूर्ण

		fb->obj[i] = &obj->base;
	पूर्ण

	ret = पूर्णांकel_fill_fb_info(dev_priv, fb);
	अगर (ret)
		जाओ err;

	ret = drm_framebuffer_init(&dev_priv->drm, fb, &पूर्णांकel_fb_funcs);
	अगर (ret) अणु
		drm_err(&dev_priv->drm, "framebuffer init failed %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	पूर्णांकel_frontbuffer_put(पूर्णांकel_fb->frontbuffer);
	वापस ret;
पूर्ण

अटल काष्ठा drm_framebuffer *
पूर्णांकel_user_framebuffer_create(काष्ठा drm_device *dev,
			      काष्ठा drm_file *filp,
			      स्थिर काष्ठा drm_mode_fb_cmd2 *user_mode_cmd)
अणु
	काष्ठा drm_framebuffer *fb;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा drm_mode_fb_cmd2 mode_cmd = *user_mode_cmd;

	obj = i915_gem_object_lookup(filp, mode_cmd.handles[0]);
	अगर (!obj)
		वापस ERR_PTR(-ENOENT);

	fb = पूर्णांकel_framebuffer_create(obj, &mode_cmd);
	i915_gem_object_put(obj);

	वापस fb;
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_mode_valid(काष्ठा drm_device *dev,
		 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	पूर्णांक hdisplay_max, htotal_max;
	पूर्णांक vdisplay_max, vtotal_max;

	/*
	 * Can't reject DBLSCAN here because Xorg ddxen can add piles
	 * of DBLSCAN modes to the output's mode list when they detect
	 * the scaling mode property on the connector. And they करोn't
	 * ask the kernel to validate those modes in any way until
	 * modeset समय at which poपूर्णांक the client माला_लो a protocol error.
	 * So in order to not upset those clients we silently ignore the
	 * DBLSCAN flag on such connectors. For other connectors we will
	 * reject modes with the DBLSCAN flag in encoder->compute_config().
	 * And we always reject DBLSCAN modes in connector->mode_valid()
	 * as we never want such modes on the connector's mode list.
	 */

	अगर (mode->vscan > 1)
		वापस MODE_NO_VSCAN;

	अगर (mode->flags & DRM_MODE_FLAG_HSKEW)
		वापस MODE_H_ILLEGAL;

	अगर (mode->flags & (DRM_MODE_FLAG_CSYNC |
			   DRM_MODE_FLAG_NCSYNC |
			   DRM_MODE_FLAG_PCSYNC))
		वापस MODE_HSYNC;

	अगर (mode->flags & (DRM_MODE_FLAG_BCAST |
			   DRM_MODE_FLAG_PIXMUX |
			   DRM_MODE_FLAG_CLKDIV2))
		वापस MODE_BAD;

	/* Transcoder timing limits */
	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		hdisplay_max = 16384;
		vdisplay_max = 8192;
		htotal_max = 16384;
		vtotal_max = 8192;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 9 ||
		   IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv)) अणु
		hdisplay_max = 8192; /* FDI max 4096 handled अन्यथाwhere */
		vdisplay_max = 4096;
		htotal_max = 8192;
		vtotal_max = 8192;
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 3) अणु
		hdisplay_max = 4096;
		vdisplay_max = 4096;
		htotal_max = 8192;
		vtotal_max = 8192;
	पूर्ण अन्यथा अणु
		hdisplay_max = 2048;
		vdisplay_max = 2048;
		htotal_max = 4096;
		vtotal_max = 4096;
	पूर्ण

	अगर (mode->hdisplay > hdisplay_max ||
	    mode->hsync_start > htotal_max ||
	    mode->hsync_end > htotal_max ||
	    mode->htotal > htotal_max)
		वापस MODE_H_ILLEGAL;

	अगर (mode->vdisplay > vdisplay_max ||
	    mode->vsync_start > vtotal_max ||
	    mode->vsync_end > vtotal_max ||
	    mode->vtotal > vtotal_max)
		वापस MODE_V_ILLEGAL;

	अगर (DISPLAY_VER(dev_priv) >= 5) अणु
		अगर (mode->hdisplay < 64 ||
		    mode->htotal - mode->hdisplay < 32)
			वापस MODE_H_ILLEGAL;

		अगर (mode->vtotal - mode->vdisplay < 5)
			वापस MODE_V_ILLEGAL;
	पूर्ण अन्यथा अणु
		अगर (mode->htotal - mode->hdisplay < 32)
			वापस MODE_H_ILLEGAL;

		अगर (mode->vtotal - mode->vdisplay < 3)
			वापस MODE_V_ILLEGAL;
	पूर्ण

	वापस MODE_OK;
पूर्ण

क्रमागत drm_mode_status
पूर्णांकel_mode_valid_max_plane_size(काष्ठा drm_i915_निजी *dev_priv,
				स्थिर काष्ठा drm_display_mode *mode,
				bool bigjoiner)
अणु
	पूर्णांक plane_width_max, plane_height_max;

	/*
	 * पूर्णांकel_mode_valid() should be
	 * sufficient on older platक्रमms.
	 */
	अगर (DISPLAY_VER(dev_priv) < 9)
		वापस MODE_OK;

	/*
	 * Most people will probably want a fullscreen
	 * plane so let's not advertize modes that are
	 * too big क्रम that.
	 */
	अगर (DISPLAY_VER(dev_priv) >= 11) अणु
		plane_width_max = 5120 << bigjoiner;
		plane_height_max = 4320;
	पूर्ण अन्यथा अणु
		plane_width_max = 5120;
		plane_height_max = 4096;
	पूर्ण

	अगर (mode->hdisplay > plane_width_max)
		वापस MODE_H_ILLEGAL;

	अगर (mode->vdisplay > plane_height_max)
		वापस MODE_V_ILLEGAL;

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs पूर्णांकel_mode_funcs = अणु
	.fb_create = पूर्णांकel_user_framebuffer_create,
	.get_क्रमmat_info = पूर्णांकel_get_क्रमmat_info,
	.output_poll_changed = पूर्णांकel_fbdev_output_poll_changed,
	.mode_valid = पूर्णांकel_mode_valid,
	.atomic_check = पूर्णांकel_atomic_check,
	.atomic_commit = पूर्णांकel_atomic_commit,
	.atomic_state_alloc = पूर्णांकel_atomic_state_alloc,
	.atomic_state_clear = पूर्णांकel_atomic_state_clear,
	.atomic_state_मुक्त = पूर्णांकel_atomic_state_मुक्त,
पूर्ण;

/**
 * पूर्णांकel_init_display_hooks - initialize the display modesetting hooks
 * @dev_priv: device निजी
 */
व्योम पूर्णांकel_init_display_hooks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_init_cdclk_hooks(dev_priv);
	पूर्णांकel_init_audio_hooks(dev_priv);

	पूर्णांकel_dpll_init_घड़ी_hook(dev_priv);

	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		dev_priv->display.get_pipe_config = hsw_get_pipe_config;
		dev_priv->display.crtc_enable = hsw_crtc_enable;
		dev_priv->display.crtc_disable = hsw_crtc_disable;
	पूर्ण अन्यथा अगर (HAS_DDI(dev_priv)) अणु
		dev_priv->display.get_pipe_config = hsw_get_pipe_config;
		dev_priv->display.crtc_enable = hsw_crtc_enable;
		dev_priv->display.crtc_disable = hsw_crtc_disable;
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		dev_priv->display.get_pipe_config = ilk_get_pipe_config;
		dev_priv->display.crtc_enable = ilk_crtc_enable;
		dev_priv->display.crtc_disable = ilk_crtc_disable;
	पूर्ण अन्यथा अगर (IS_CHERRYVIEW(dev_priv) ||
		   IS_VALLEYVIEW(dev_priv)) अणु
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.crtc_enable = valleyview_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	पूर्ण अन्यथा अणु
		dev_priv->display.get_pipe_config = i9xx_get_pipe_config;
		dev_priv->display.crtc_enable = i9xx_crtc_enable;
		dev_priv->display.crtc_disable = i9xx_crtc_disable;
	पूर्ण

	पूर्णांकel_fdi_init_hook(dev_priv);

	अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		dev_priv->display.commit_modeset_enables = skl_commit_modeset_enables;
		dev_priv->display.get_initial_plane_config = skl_get_initial_plane_config;
	पूर्ण अन्यथा अणु
		dev_priv->display.commit_modeset_enables = पूर्णांकel_commit_modeset_enables;
		dev_priv->display.get_initial_plane_config = i9xx_get_initial_plane_config;
	पूर्ण

पूर्ण

व्योम पूर्णांकel_modeset_init_hw(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_cdclk_state *cdclk_state =
		to_पूर्णांकel_cdclk_state(i915->cdclk.obj.state);

	पूर्णांकel_update_cdclk(i915);
	पूर्णांकel_dump_cdclk_config(&i915->cdclk.hw, "Current CDCLK");
	cdclk_state->logical = cdclk_state->actual = i915->cdclk.hw;
पूर्ण

अटल पूर्णांक sanitize_watermarks_add_affected(काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane *plane;
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_crtc(state->dev, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state;

		crtc_state = पूर्णांकel_atomic_get_crtc_state(state, crtc);
		अगर (IS_ERR(crtc_state))
			वापस PTR_ERR(crtc_state);

		अगर (crtc_state->hw.active) अणु
			/*
			 * Preserve the inherited flag to aव्योम
			 * taking the full modeset path.
			 */
			crtc_state->inherited = true;
		पूर्ण
	पूर्ण

	drm_क्रम_each_plane(plane, state->dev) अणु
		काष्ठा drm_plane_state *plane_state;

		plane_state = drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state))
			वापस PTR_ERR(plane_state);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Calculate what we think the watermarks should be क्रम the state we've पढ़ो
 * out of the hardware and then immediately program those watermarks so that
 * we ensure the hardware settings match our पूर्णांकernal state.
 *
 * We can calculate what we think WM's should be by creating a duplicate of the
 * current state (which was स्थिरructed during hardware पढ़ोout) and running it
 * through the atomic check code to calculate new watermark values in the
 * state object.
 */
अटल व्योम sanitize_watermarks(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_atomic_state *state;
	काष्ठा पूर्णांकel_atomic_state *पूर्णांकel_state;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_crtc_state *crtc_state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;
	पूर्णांक i;

	/* Only supported on platक्रमms that use atomic watermark design */
	अगर (!dev_priv->display.optimize_watermarks)
		वापस;

	state = drm_atomic_state_alloc(&dev_priv->drm);
	अगर (drm_WARN_ON(&dev_priv->drm, !state))
		वापस;

	पूर्णांकel_state = to_पूर्णांकel_atomic_state(state);

	drm_modeset_acquire_init(&ctx, 0);

retry:
	state->acquire_ctx = &ctx;

	/*
	 * Hardware पढ़ोout is the only समय we करोn't want to calculate
	 * पूर्णांकermediate watermarks (since we करोn't trust the current
	 * watermarks).
	 */
	अगर (!HAS_GMCH(dev_priv))
		पूर्णांकel_state->skip_पूर्णांकermediate_wm = true;

	ret = sanitize_watermarks_add_affected(state);
	अगर (ret)
		जाओ fail;

	ret = पूर्णांकel_atomic_check(&dev_priv->drm, state);
	अगर (ret)
		जाओ fail;

	/* Write calculated watermark values back */
	क्रम_each_new_पूर्णांकel_crtc_in_state(पूर्णांकel_state, crtc, crtc_state, i) अणु
		crtc_state->wm.need_postvbl_update = true;
		dev_priv->display.optimize_watermarks(पूर्णांकel_state, crtc);

		to_पूर्णांकel_crtc_state(crtc->base.state)->wm = crtc_state->wm;
	पूर्ण

fail:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	/*
	 * If we fail here, it means that the hardware appears to be
	 * programmed in a way that shouldn't be possible, given our
	 * understanding of watermark requirements.  This might mean a
	 * mistake in the hardware पढ़ोout code or a mistake in the
	 * watermark calculations क्रम a given platक्रमm.  Raise a WARN
	 * so that this is noticeable.
	 *
	 * If this actually happens, we'll have to just leave the
	 * BIOS-programmed watermarks untouched and hope क्रम the best.
	 */
	drm_WARN(&dev_priv->drm, ret,
		 "Could not determine valid watermarks for inherited state\n");

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);
पूर्ण

अटल व्योम पूर्णांकel_update_fdi_pll_freq(काष्ठा drm_i915_निजी *dev_priv)
अणु
	अगर (IS_IRONLAKE(dev_priv)) अणु
		u32 fdi_pll_clk =
			पूर्णांकel_de_पढ़ो(dev_priv, FDI_PLL_BIOS_0) & FDI_PLL_FB_CLOCK_MASK;

		dev_priv->fdi_pll_freq = (fdi_pll_clk + 2) * 10000;
	पूर्ण अन्यथा अगर (IS_SANDYBRIDGE(dev_priv) || IS_IVYBRIDGE(dev_priv)) अणु
		dev_priv->fdi_pll_freq = 270000;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	drm_dbg(&dev_priv->drm, "FDI PLL freq=%d\n", dev_priv->fdi_pll_freq);
पूर्ण

अटल पूर्णांक पूर्णांकel_initial_commit(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_atomic_state *state = शून्य;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक ret = 0;

	state = drm_atomic_state_alloc(dev);
	अगर (!state)
		वापस -ENOMEM;

	drm_modeset_acquire_init(&ctx, 0);

retry:
	state->acquire_ctx = &ctx;

	क्रम_each_पूर्णांकel_crtc(dev, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			पूर्णांकel_atomic_get_crtc_state(state, crtc);

		अगर (IS_ERR(crtc_state)) अणु
			ret = PTR_ERR(crtc_state);
			जाओ out;
		पूर्ण

		अगर (crtc_state->hw.active) अणु
			काष्ठा पूर्णांकel_encoder *encoder;

			/*
			 * We've not yet detected sink capabilities
			 * (audio,infoframes,etc.) and thus we करोn't want to
			 * क्रमce a full state recomputation yet. We want that to
			 * happen only क्रम the first real commit from userspace.
			 * So preserve the inherited flag क्रम the समय being.
			 */
			crtc_state->inherited = true;

			ret = drm_atomic_add_affected_planes(state, &crtc->base);
			अगर (ret)
				जाओ out;

			/*
			 * FIXME hack to क्रमce a LUT update to aव्योम the
			 * plane update क्रमcing the pipe gamma on without
			 * having a proper LUT loaded. Remove once we
			 * have पढ़ोout क्रम pipe gamma enable.
			 */
			crtc_state->uapi.color_mgmt_changed = true;

			क्रम_each_पूर्णांकel_encoder_mask(dev, encoder,
						    crtc_state->uapi.encoder_mask) अणु
				अगर (encoder->initial_fastset_check &&
				    !encoder->initial_fastset_check(encoder, crtc_state)) अणु
					ret = drm_atomic_add_affected_connectors(state,
										 &crtc->base);
					अगर (ret)
						जाओ out;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	ret = drm_atomic_commit(state);

out:
	अगर (ret == -EDEADLK) अणु
		drm_atomic_state_clear(state);
		drm_modeset_backoff(&ctx);
		जाओ retry;
	पूर्ण

	drm_atomic_state_put(state);

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;
पूर्ण

अटल व्योम पूर्णांकel_mode_config_init(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_mode_config *mode_config = &i915->drm.mode_config;

	drm_mode_config_init(&i915->drm);
	INIT_LIST_HEAD(&i915->global_obj_list);

	mode_config->min_width = 0;
	mode_config->min_height = 0;

	mode_config->preferred_depth = 24;
	mode_config->prefer_shaकरोw = 1;

	mode_config->allow_fb_modअगरiers = true;

	mode_config->funcs = &पूर्णांकel_mode_funcs;

	mode_config->async_page_flip = has_async_flips(i915);

	/*
	 * Maximum framebuffer dimensions, chosen to match
	 * the maximum render engine surface size on gen4+.
	 */
	अगर (DISPLAY_VER(i915) >= 7) अणु
		mode_config->max_width = 16384;
		mode_config->max_height = 16384;
	पूर्ण अन्यथा अगर (DISPLAY_VER(i915) >= 4) अणु
		mode_config->max_width = 8192;
		mode_config->max_height = 8192;
	पूर्ण अन्यथा अगर (IS_DISPLAY_VER(i915, 3)) अणु
		mode_config->max_width = 4096;
		mode_config->max_height = 4096;
	पूर्ण अन्यथा अणु
		mode_config->max_width = 2048;
		mode_config->max_height = 2048;
	पूर्ण

	अगर (IS_I845G(i915) || IS_I865G(i915)) अणु
		mode_config->cursor_width = IS_I845G(i915) ? 64 : 512;
		mode_config->cursor_height = 1023;
	पूर्ण अन्यथा अगर (IS_I830(i915) || IS_I85X(i915) ||
		   IS_I915G(i915) || IS_I915GM(i915)) अणु
		mode_config->cursor_width = 64;
		mode_config->cursor_height = 64;
	पूर्ण अन्यथा अणु
		mode_config->cursor_width = 256;
		mode_config->cursor_height = 256;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_mode_config_cleanup(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_atomic_global_obj_cleanup(i915);
	drm_mode_config_cleanup(&i915->drm);
पूर्ण

अटल व्योम plane_config_fini(काष्ठा पूर्णांकel_initial_plane_config *plane_config)
अणु
	अगर (plane_config->fb) अणु
		काष्ठा drm_framebuffer *fb = &plane_config->fb->base;

		/* We may only have the stub and not a full framebuffer */
		अगर (drm_framebuffer_पढ़ो_refcount(fb))
			drm_framebuffer_put(fb);
		अन्यथा
			kमुक्त(fb);
	पूर्ण

	अगर (plane_config->vma)
		i915_vma_put(plane_config->vma);
पूर्ण

/* part #1: call beक्रमe irq install */
पूर्णांक पूर्णांकel_modeset_init_noirq(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret;

	अगर (i915_inject_probe_failure(i915))
		वापस -ENODEV;

	अगर (HAS_DISPLAY(i915)) अणु
		ret = drm_vblank_init(&i915->drm,
				      INTEL_NUM_PIPES(i915));
		अगर (ret)
			वापस ret;
	पूर्ण

	पूर्णांकel_bios_init(i915);

	ret = पूर्णांकel_vga_रेजिस्टर(i915);
	अगर (ret)
		जाओ cleanup_bios;

	/* FIXME: completely on the wrong असलtraction layer */
	पूर्णांकel_घातer_करोमुख्यs_init_hw(i915, false);

	पूर्णांकel_csr_ucode_init(i915);

	i915->modeset_wq = alloc_ordered_workqueue("i915_modeset", 0);
	i915->flip_wq = alloc_workqueue("i915_flip", WQ_HIGHPRI |
					WQ_UNBOUND, WQ_UNBOUND_MAX_ACTIVE);

	i915->framestart_delay = 1; /* 1-4 */

	पूर्णांकel_mode_config_init(i915);

	ret = पूर्णांकel_cdclk_init(i915);
	अगर (ret)
		जाओ cleanup_vga_client_pw_करोमुख्य_csr;

	ret = पूर्णांकel_dbuf_init(i915);
	अगर (ret)
		जाओ cleanup_vga_client_pw_करोमुख्य_csr;

	ret = पूर्णांकel_bw_init(i915);
	अगर (ret)
		जाओ cleanup_vga_client_pw_करोमुख्य_csr;

	init_llist_head(&i915->atomic_helper.मुक्त_list);
	INIT_WORK(&i915->atomic_helper.मुक्त_work,
		  पूर्णांकel_atomic_helper_मुक्त_state_worker);

	पूर्णांकel_init_quirks(i915);

	पूर्णांकel_fbc_init(i915);

	वापस 0;

cleanup_vga_client_pw_करोमुख्य_csr:
	पूर्णांकel_csr_ucode_fini(i915);
	पूर्णांकel_घातer_करोमुख्यs_driver_हटाओ(i915);
	पूर्णांकel_vga_unरेजिस्टर(i915);
cleanup_bios:
	पूर्णांकel_bios_driver_हटाओ(i915);

	वापस ret;
पूर्ण

/* part #2: call after irq install, but beक्रमe gem init */
पूर्णांक पूर्णांकel_modeset_init_nogem(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_device *dev = &i915->drm;
	क्रमागत pipe pipe;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांक ret;

	पूर्णांकel_init_pm(i915);

	पूर्णांकel_panel_sanitize_ssc(i915);

	पूर्णांकel_pps_setup(i915);

	पूर्णांकel_gmbus_setup(i915);

	drm_dbg_kms(&i915->drm, "%d display pipe%s available.\n",
		    INTEL_NUM_PIPES(i915),
		    INTEL_NUM_PIPES(i915) > 1 ? "s" : "");

	अगर (HAS_DISPLAY(i915)) अणु
		क्रम_each_pipe(i915, pipe) अणु
			ret = पूर्णांकel_crtc_init(i915, pipe);
			अगर (ret) अणु
				पूर्णांकel_mode_config_cleanup(i915);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	पूर्णांकel_plane_possible_crtcs_init(i915);
	पूर्णांकel_shared_dpll_init(dev);
	पूर्णांकel_update_fdi_pll_freq(i915);

	पूर्णांकel_update_czclk(i915);
	पूर्णांकel_modeset_init_hw(i915);
	पूर्णांकel_dpll_update_ref_clks(i915);

	पूर्णांकel_hdcp_component_init(i915);

	अगर (i915->max_cdclk_freq == 0)
		पूर्णांकel_update_max_cdclk(i915);

	/*
	 * If the platक्रमm has HTI, we need to find out whether it has reserved
	 * any display resources beक्रमe we create our display outमाला_दो.
	 */
	अगर (INTEL_INFO(i915)->display.has_hti)
		i915->hti_state = पूर्णांकel_de_पढ़ो(i915, HDPORT_STATE);

	/* Just disable it once at startup */
	पूर्णांकel_vga_disable(i915);
	पूर्णांकel_setup_outमाला_दो(i915);

	drm_modeset_lock_all(dev);
	पूर्णांकel_modeset_setup_hw_state(dev, dev->mode_config.acquire_ctx);
	drm_modeset_unlock_all(dev);

	क्रम_each_पूर्णांकel_crtc(dev, crtc) अणु
		काष्ठा पूर्णांकel_initial_plane_config plane_config = अणुपूर्ण;

		अगर (!to_पूर्णांकel_crtc_state(crtc->base.state)->uapi.active)
			जारी;

		/*
		 * Note that reserving the BIOS fb up front prevents us
		 * from stuffing other stolen allocations like the ring
		 * on top.  This prevents some ugliness at boot समय, and
		 * can even allow क्रम smooth boot transitions अगर the BIOS
		 * fb is large enough क्रम the active pipe configuration.
		 */
		i915->display.get_initial_plane_config(crtc, &plane_config);

		/*
		 * If the fb is shared between multiple heads, we'll
		 * just get the first one.
		 */
		पूर्णांकel_find_initial_plane_obj(crtc, &plane_config);

		plane_config_fini(&plane_config);
	पूर्ण

	/*
	 * Make sure hardware watermarks really match the state we पढ़ो out.
	 * Note that we need to करो this after reस्थिरructing the BIOS fb's
	 * since the watermark calculation करोne here will use pstate->fb.
	 */
	अगर (!HAS_GMCH(i915))
		sanitize_watermarks(i915);

	वापस 0;
पूर्ण

/* part #3: call after gem init */
पूर्णांक पूर्णांकel_modeset_init(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret;

	अगर (!HAS_DISPLAY(i915))
		वापस 0;

	/*
	 * Force all active planes to recompute their states. So that on
	 * mode_setcrtc after probe, all the पूर्णांकel_plane_state variables
	 * are alपढ़ोy calculated and there is no निश्चित_plane warnings
	 * during bootup.
	 */
	ret = पूर्णांकel_initial_commit(&i915->drm);
	अगर (ret)
		drm_dbg_kms(&i915->drm, "Initial modeset failed, %d\n", ret);

	पूर्णांकel_overlay_setup(i915);

	ret = पूर्णांकel_fbdev_init(&i915->drm);
	अगर (ret)
		वापस ret;

	/* Only enable hotplug handling once the fbdev is fully set up. */
	पूर्णांकel_hpd_init(i915);
	पूर्णांकel_hpd_poll_disable(i915);

	पूर्णांकel_init_ipc(i915);

	वापस 0;
पूर्ण

व्योम i830_enable_pipe(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
	/* 640x480@60Hz, ~25175 kHz */
	काष्ठा dpll घड़ी = अणु
		.m1 = 18,
		.m2 = 7,
		.p1 = 13,
		.p2 = 4,
		.n = 2,
	पूर्ण;
	u32 dpll, fp;
	पूर्णांक i;

	drm_WARN_ON(&dev_priv->drm,
		    i9xx_calc_dpll_params(48000, &घड़ी) != 25154);

	drm_dbg_kms(&dev_priv->drm,
		    "enabling pipe %c due to force quirk (vco=%d dot=%d)\n",
		    pipe_name(pipe), घड़ी.vco, घड़ी.करोt);

	fp = i9xx_dpll_compute_fp(&घड़ी);
	dpll = DPLL_DVO_2X_MODE |
		DPLL_VGA_MODE_DIS |
		((घड़ी.p1 - 2) << DPLL_FPA01_P1_POST_DIV_SHIFT) |
		PLL_P2_DIVIDE_BY_4 |
		PLL_REF_INPUT_DREFCLK |
		DPLL_VCO_ENABLE;

	पूर्णांकel_de_ग_लिखो(dev_priv, FP0(pipe), fp);
	पूर्णांकel_de_ग_लिखो(dev_priv, FP1(pipe), fp);

	पूर्णांकel_de_ग_लिखो(dev_priv, HTOTAL(pipe), (640 - 1) | ((800 - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, HBLANK(pipe), (640 - 1) | ((800 - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, HSYNC(pipe), (656 - 1) | ((752 - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, VTOTAL(pipe), (480 - 1) | ((525 - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, VBLANK(pipe), (480 - 1) | ((525 - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, VSYNC(pipe), (490 - 1) | ((492 - 1) << 16));
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPESRC(pipe), ((640 - 1) << 16) | (480 - 1));

	/*
	 * Apparently we need to have VGA mode enabled prior to changing
	 * the P1/P2 भागiders. Otherwise the DPLL will keep using the old
	 * भागiders, even though the रेजिस्टर value करोes change.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), dpll & ~DPLL_VGA_MODE_DIS);
	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), dpll);

	/* Wait क्रम the घड़ीs to stabilize. */
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL(pipe));
	udelay(150);

	/* The pixel multiplier can only be updated once the
	 * DPLL is enabled and the घड़ीs are stable.
	 *
	 * So ग_लिखो it again.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), dpll);

	/* We करो this three बार क्रम luck */
	क्रम (i = 0; i < 3 ; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), dpll);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL(pipe));
		udelay(150); /* रुको क्रम warmup */
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(pipe),
		       PIPECONF_ENABLE | PIPECONF_PROGRESSIVE);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPECONF(pipe));

	पूर्णांकel_रुको_क्रम_pipe_scanline_moving(crtc);
पूर्ण

व्योम i830_disable_pipe(काष्ठा drm_i915_निजी *dev_priv, क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

	drm_dbg_kms(&dev_priv->drm, "disabling pipe %c due to force quirk\n",
		    pipe_name(pipe));

	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, DSPCNTR(PLANE_A)) &
		    DISPLAY_PLANE_ENABLE);
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, DSPCNTR(PLANE_B)) &
		    DISPLAY_PLANE_ENABLE);
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, DSPCNTR(PLANE_C)) &
		    DISPLAY_PLANE_ENABLE);
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, CURCNTR(PIPE_A)) & MCURSOR_MODE);
	drm_WARN_ON(&dev_priv->drm,
		    पूर्णांकel_de_पढ़ो(dev_priv, CURCNTR(PIPE_B)) & MCURSOR_MODE);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(pipe), 0);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, PIPECONF(pipe));

	पूर्णांकel_रुको_क्रम_pipe_scanline_stopped(crtc);

	पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), DPLL_VGA_MODE_DIS);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, DPLL(pipe));
पूर्ण

अटल व्योम
पूर्णांकel_sanitize_plane_mapping(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;

	अगर (DISPLAY_VER(dev_priv) >= 4)
		वापस;

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_plane *plane =
			to_पूर्णांकel_plane(crtc->base.primary);
		काष्ठा पूर्णांकel_crtc *plane_crtc;
		क्रमागत pipe pipe;

		अगर (!plane->get_hw_state(plane, &pipe))
			जारी;

		अगर (pipe == crtc->pipe)
			जारी;

		drm_dbg_kms(&dev_priv->drm,
			    "[PLANE:%d:%s] attached to the wrong pipe, disabling plane\n",
			    plane->base.base.id, plane->base.name);

		plane_crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
		पूर्णांकel_plane_disable_noatomic(plane_crtc, plane);
	पूर्ण
पूर्ण

अटल bool पूर्णांकel_crtc_has_encoders(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा पूर्णांकel_encoder *encoder;

	क्रम_each_encoder_on_crtc(dev, &crtc->base, encoder)
		वापस true;

	वापस false;
पूर्ण

अटल काष्ठा पूर्णांकel_connector *पूर्णांकel_encoder_find_connector(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा पूर्णांकel_connector *connector;

	क्रम_each_connector_on_encoder(dev, &encoder->base, connector)
		वापस connector;

	वापस शून्य;
पूर्ण

अटल bool has_pch_trancoder(काष्ठा drm_i915_निजी *dev_priv,
			      क्रमागत pipe pch_transcoder)
अणु
	वापस HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv) ||
		(HAS_PCH_LPT_H(dev_priv) && pch_transcoder == PIPE_A);
पूर्ण

अटल व्योम पूर्णांकel_sanitize_frame_start_delay(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत transcoder cpu_transcoder = crtc_state->cpu_transcoder;

	अगर (DISPLAY_VER(dev_priv) >= 9 ||
	    IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv)) अणु
		i915_reg_t reg = CHICKEN_TRANS(cpu_transcoder);
		u32 val;

		अगर (transcoder_is_dsi(cpu_transcoder))
			वापस;

		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		val &= ~HSW_FRAME_START_DELAY_MASK;
		val |= HSW_FRAME_START_DELAY(dev_priv->framestart_delay - 1);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण अन्यथा अणु
		i915_reg_t reg = PIPECONF(cpu_transcoder);
		u32 val;

		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		val &= ~PIPECONF_FRAME_START_DELAY_MASK;
		val |= PIPECONF_FRAME_START_DELAY(dev_priv->framestart_delay - 1);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण

	अगर (!crtc_state->has_pch_encoder)
		वापस;

	अगर (HAS_PCH_IBX(dev_priv)) अणु
		i915_reg_t reg = PCH_TRANSCONF(crtc->pipe);
		u32 val;

		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		val &= ~TRANS_FRAME_START_DELAY_MASK;
		val |= TRANS_FRAME_START_DELAY(dev_priv->framestart_delay - 1);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण अन्यथा अणु
		क्रमागत pipe pch_transcoder = पूर्णांकel_crtc_pch_transcoder(crtc);
		i915_reg_t reg = TRANS_CHICKEN2(pch_transcoder);
		u32 val;

		val = पूर्णांकel_de_पढ़ो(dev_priv, reg);
		val &= ~TRANS_CHICKEN2_FRAME_START_DELAY_MASK;
		val |= TRANS_CHICKEN2_FRAME_START_DELAY(dev_priv->framestart_delay - 1);
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_sanitize_crtc(काष्ठा पूर्णांकel_crtc *crtc,
				काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc_state *crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);

	अगर (crtc_state->hw.active) अणु
		काष्ठा पूर्णांकel_plane *plane;

		/* Clear any frame start delays used क्रम debugging left by the BIOS */
		पूर्णांकel_sanitize_frame_start_delay(crtc_state);

		/* Disable everything but the primary plane */
		क्रम_each_पूर्णांकel_plane_on_crtc(dev, crtc, plane) अणु
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
				to_पूर्णांकel_plane_state(plane->base.state);

			अगर (plane_state->uapi.visible &&
			    plane->base.type != DRM_PLANE_TYPE_PRIMARY)
				पूर्णांकel_plane_disable_noatomic(crtc, plane);
		पूर्ण

		/*
		 * Disable any background color set by the BIOS, but enable the
		 * gamma and CSC to match how we program our planes.
		 */
		अगर (DISPLAY_VER(dev_priv) >= 9)
			पूर्णांकel_de_ग_लिखो(dev_priv, SKL_BOTTOM_COLOR(crtc->pipe),
				       SKL_BOTTOM_COLOR_GAMMA_ENABLE | SKL_BOTTOM_COLOR_CSC_ENABLE);
	पूर्ण

	/* Adjust the state of the output pipe according to whether we
	 * have active connectors/encoders. */
	अगर (crtc_state->hw.active && !पूर्णांकel_crtc_has_encoders(crtc) &&
	    !crtc_state->bigjoiner_slave)
		पूर्णांकel_crtc_disable_noatomic(crtc, ctx);

	अगर (crtc_state->hw.active || HAS_GMCH(dev_priv)) अणु
		/*
		 * We start out with underrun reporting disabled to aव्योम races.
		 * For correct bookkeeping mark this on active crtcs.
		 *
		 * Also on gmch platक्रमms we करोnt have any hardware bits to
		 * disable the underrun reporting. Which means we need to start
		 * out with underrun reporting disabled also on inactive pipes,
		 * since otherwise we'll complain about the garbage we पढ़ो when
		 * e.g. coming up after runसमय pm.
		 *
		 * No protection against concurrent access is required - at
		 * worst a fअगरo underrun happens which also sets this to false.
		 */
		crtc->cpu_fअगरo_underrun_disabled = true;
		/*
		 * We track the PCH trancoder underrun reporting state
		 * within the crtc. With crtc क्रम pipe A housing the underrun
		 * reporting state क्रम PCH transcoder A, crtc क्रम pipe B housing
		 * it क्रम PCH transcoder B, etc. LPT-H has only PCH transcoder A,
		 * and marking underrun reporting as disabled क्रम the non-existing
		 * PCH transcoders B and C would prevent enabling the south
		 * error पूर्णांकerrupt (see cpt_can_enable_serr_पूर्णांक()).
		 */
		अगर (has_pch_trancoder(dev_priv, crtc->pipe))
			crtc->pch_fअगरo_underrun_disabled = true;
	पूर्ण
पूर्ण

अटल bool has_bogus_dpll_config(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	/*
	 * Some SNB BIOSen (eg. ASUS K53SV) are known to misprogram
	 * the hardware when a high res displays plugged in. DPLL P
	 * भागider is zero, and the pipe timings are bonkers. We'll
	 * try to disable everything in that हाल.
	 *
	 * FIXME would be nice to be able to sanitize this state
	 * without several WARNs, but क्रम now let's take the easy
	 * road.
	 */
	वापस IS_SANDYBRIDGE(dev_priv) &&
		crtc_state->hw.active &&
		crtc_state->shared_dpll &&
		crtc_state->port_घड़ी == 0;
पूर्ण

अटल व्योम पूर्णांकel_sanitize_encoder(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(encoder->base.crtc);
	काष्ठा पूर्णांकel_crtc_state *crtc_state = crtc ?
		to_पूर्णांकel_crtc_state(crtc->base.state) : शून्य;

	/* We need to check both क्रम a crtc link (meaning that the
	 * encoder is active and trying to पढ़ो from a pipe) and the
	 * pipe itself being active. */
	bool has_active_crtc = crtc_state &&
		crtc_state->hw.active;

	अगर (crtc_state && has_bogus_dpll_config(crtc_state)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "BIOS has misprogrammed the hardware. Disabling pipe %c\n",
			    pipe_name(crtc->pipe));
		has_active_crtc = false;
	पूर्ण

	connector = पूर्णांकel_encoder_find_connector(encoder);
	अगर (connector && !has_active_crtc) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "[ENCODER:%d:%s] has active connectors but no active pipe!\n",
			    encoder->base.base.id,
			    encoder->base.name);

		/* Connector is active, but has no active pipe. This is
		 * fallout from our resume रेजिस्टर restoring. Disable
		 * the encoder manually again. */
		अगर (crtc_state) अणु
			काष्ठा drm_encoder *best_encoder;

			drm_dbg_kms(&dev_priv->drm,
				    "[ENCODER:%d:%s] manually disabled\n",
				    encoder->base.base.id,
				    encoder->base.name);

			/* aव्योम oopsing in हाल the hooks consult best_encoder */
			best_encoder = connector->base.state->best_encoder;
			connector->base.state->best_encoder = &encoder->base;

			/* FIXME शून्य atomic state passed! */
			अगर (encoder->disable)
				encoder->disable(शून्य, encoder, crtc_state,
						 connector->base.state);
			अगर (encoder->post_disable)
				encoder->post_disable(शून्य, encoder, crtc_state,
						      connector->base.state);

			connector->base.state->best_encoder = best_encoder;
		पूर्ण
		encoder->base.crtc = शून्य;

		/* Inconsistent output/port/pipe state happens presumably due to
		 * a bug in one of the get_hw_state functions. Or someplace अन्यथा
		 * in our code, like the रेजिस्टर restore mess on resume. Clamp
		 * things to off as a safer शेष. */

		connector->base.dpms = DRM_MODE_DPMS_OFF;
		connector->base.encoder = शून्य;
	पूर्ण

	/* notअगरy opregion of the sanitized encoder state */
	पूर्णांकel_opregion_notअगरy_encoder(encoder, connector && has_active_crtc);

	अगर (HAS_DDI(dev_priv))
		पूर्णांकel_ddi_sanitize_encoder_pll_mapping(encoder);
पूर्ण

/* FIXME पढ़ो out full plane state क्रम all planes */
अटल व्योम पढ़ोout_plane_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_plane *plane;
	काष्ठा पूर्णांकel_crtc *crtc;

	क्रम_each_पूर्णांकel_plane(&dev_priv->drm, plane) अणु
		काष्ठा पूर्णांकel_plane_state *plane_state =
			to_पूर्णांकel_plane_state(plane->base.state);
		काष्ठा पूर्णांकel_crtc_state *crtc_state;
		क्रमागत pipe pipe = PIPE_A;
		bool visible;

		visible = plane->get_hw_state(plane, &pipe);

		crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
		crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);

		पूर्णांकel_set_plane_visible(crtc_state, plane_state, visible);

		drm_dbg_kms(&dev_priv->drm,
			    "[PLANE:%d:%s] hw state readout: %s, pipe %c\n",
			    plane->base.base.id, plane->base.name,
			    enableddisabled(visible), pipe_name(pipe));
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		fixup_plane_biपंचांगasks(crtc_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_modeset_पढ़ोout_hw_state(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_cdclk_state *cdclk_state =
		to_पूर्णांकel_cdclk_state(dev_priv->cdclk.obj.state);
	काष्ठा पूर्णांकel_dbuf_state *dbuf_state =
		to_पूर्णांकel_dbuf_state(dev_priv->dbuf.obj.state);
	क्रमागत pipe pipe;
	काष्ठा पूर्णांकel_crtc *crtc;
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;
	u8 active_pipes = 0;

	क्रम_each_पूर्णांकel_crtc(dev, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		__drm_atomic_helper_crtc_destroy_state(&crtc_state->uapi);
		पूर्णांकel_crtc_मुक्त_hw_state(crtc_state);
		पूर्णांकel_crtc_state_reset(crtc_state, crtc);

		पूर्णांकel_crtc_get_pipe_config(crtc_state);

		crtc_state->hw.enable = crtc_state->hw.active;

		crtc->base.enabled = crtc_state->hw.enable;
		crtc->active = crtc_state->hw.active;

		अगर (crtc_state->hw.active)
			active_pipes |= BIT(crtc->pipe);

		drm_dbg_kms(&dev_priv->drm,
			    "[CRTC:%d:%s] hw state readout: %s\n",
			    crtc->base.base.id, crtc->base.name,
			    enableddisabled(crtc_state->hw.active));
	पूर्ण

	dev_priv->active_pipes = cdclk_state->active_pipes =
		dbuf_state->active_pipes = active_pipes;

	पढ़ोout_plane_state(dev_priv);

	क्रम_each_पूर्णांकel_encoder(dev, encoder) अणु
		pipe = 0;

		अगर (encoder->get_hw_state(encoder, &pipe)) अणु
			काष्ठा पूर्णांकel_crtc_state *crtc_state;

			crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
			crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);

			encoder->base.crtc = &crtc->base;
			पूर्णांकel_encoder_get_config(encoder, crtc_state);
			अगर (encoder->sync_state)
				encoder->sync_state(encoder, crtc_state);

			/* पढ़ो out to slave crtc as well क्रम bigjoiner */
			अगर (crtc_state->bigjoiner) अणु
				/* encoder should पढ़ो be linked to bigjoiner master */
				WARN_ON(crtc_state->bigjoiner_slave);

				crtc = crtc_state->bigjoiner_linked_crtc;
				crtc_state = to_पूर्णांकel_crtc_state(crtc->base.state);
				पूर्णांकel_encoder_get_config(encoder, crtc_state);
			पूर्ण
		पूर्ण अन्यथा अणु
			encoder->base.crtc = शून्य;
		पूर्ण

		drm_dbg_kms(&dev_priv->drm,
			    "[ENCODER:%d:%s] hw state readout: %s, pipe %c\n",
			    encoder->base.base.id, encoder->base.name,
			    enableddisabled(encoder->base.crtc),
			    pipe_name(pipe));
	पूर्ण

	पूर्णांकel_dpll_पढ़ोout_hw_state(dev_priv);

	drm_connector_list_iter_begin(dev, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		अगर (connector->get_hw_state(connector)) अणु
			काष्ठा पूर्णांकel_crtc_state *crtc_state;
			काष्ठा पूर्णांकel_crtc *crtc;

			connector->base.dpms = DRM_MODE_DPMS_ON;

			encoder = पूर्णांकel_attached_encoder(connector);
			connector->base.encoder = &encoder->base;

			crtc = to_पूर्णांकel_crtc(encoder->base.crtc);
			crtc_state = crtc ? to_पूर्णांकel_crtc_state(crtc->base.state) : शून्य;

			अगर (crtc_state && crtc_state->hw.active) अणु
				/*
				 * This has to be करोne during hardware पढ़ोout
				 * because anything calling .crtc_disable may
				 * rely on the connector_mask being accurate.
				 */
				crtc_state->uapi.connector_mask |=
					drm_connector_mask(&connector->base);
				crtc_state->uapi.encoder_mask |=
					drm_encoder_mask(&encoder->base);
			पूर्ण
		पूर्ण अन्यथा अणु
			connector->base.dpms = DRM_MODE_DPMS_OFF;
			connector->base.encoder = शून्य;
		पूर्ण
		drm_dbg_kms(&dev_priv->drm,
			    "[CONNECTOR:%d:%s] hw state readout: %s\n",
			    connector->base.base.id, connector->base.name,
			    enableddisabled(connector->base.encoder));
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	क्रम_each_पूर्णांकel_crtc(dev, crtc) अणु
		काष्ठा पूर्णांकel_bw_state *bw_state =
			to_पूर्णांकel_bw_state(dev_priv->bw_obj.state);
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		काष्ठा पूर्णांकel_plane *plane;
		पूर्णांक min_cdclk = 0;

		अगर (crtc_state->bigjoiner_slave)
			जारी;

		अगर (crtc_state->hw.active) अणु
			/*
			 * The initial mode needs to be set in order to keep
			 * the atomic core happy. It wants a valid mode अगर the
			 * crtc's enabled, so we करो the above call.
			 *
			 * But we करोn't set all the derived state fully, hence
			 * set a flag to indicate that a full recalculation is
			 * needed on the next commit.
			 */
			crtc_state->inherited = true;

			पूर्णांकel_crtc_update_active_timings(crtc_state);

			पूर्णांकel_crtc_copy_hw_to_uapi_state(crtc_state);
		पूर्ण

		क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
			स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
				to_पूर्णांकel_plane_state(plane->base.state);

			/*
			 * FIXME करोn't have the fb yet, so can't
			 * use पूर्णांकel_plane_data_rate() :(
			 */
			अगर (plane_state->uapi.visible)
				crtc_state->data_rate[plane->id] =
					4 * crtc_state->pixel_rate;
			/*
			 * FIXME करोn't have the fb yet, so can't
			 * use plane->min_cdclk() :(
			 */
			अगर (plane_state->uapi.visible && plane->min_cdclk) अणु
				अगर (crtc_state->द्विगुन_wide || DISPLAY_VER(dev_priv) >= 10)
					crtc_state->min_cdclk[plane->id] =
						DIV_ROUND_UP(crtc_state->pixel_rate, 2);
				अन्यथा
					crtc_state->min_cdclk[plane->id] =
						crtc_state->pixel_rate;
			पूर्ण
			drm_dbg_kms(&dev_priv->drm,
				    "[PLANE:%d:%s] min_cdclk %d kHz\n",
				    plane->base.base.id, plane->base.name,
				    crtc_state->min_cdclk[plane->id]);
		पूर्ण

		अगर (crtc_state->hw.active) अणु
			min_cdclk = पूर्णांकel_crtc_compute_min_cdclk(crtc_state);
			अगर (drm_WARN_ON(dev, min_cdclk < 0))
				min_cdclk = 0;
		पूर्ण

		cdclk_state->min_cdclk[crtc->pipe] = min_cdclk;
		cdclk_state->min_voltage_level[crtc->pipe] =
			crtc_state->min_voltage_level;

		पूर्णांकel_bw_crtc_update(bw_state, crtc_state);

		पूर्णांकel_pipe_config_sanity_check(dev_priv, crtc_state);

		/* discard our incomplete slave state, copy it from master */
		अगर (crtc_state->bigjoiner && crtc_state->hw.active) अणु
			काष्ठा पूर्णांकel_crtc *slave = crtc_state->bigjoiner_linked_crtc;
			काष्ठा पूर्णांकel_crtc_state *slave_crtc_state =
				to_पूर्णांकel_crtc_state(slave->base.state);

			copy_bigjoiner_crtc_state(slave_crtc_state, crtc_state);
			slave->base.mode = crtc->base.mode;

			cdclk_state->min_cdclk[slave->pipe] = min_cdclk;
			cdclk_state->min_voltage_level[slave->pipe] =
				crtc_state->min_voltage_level;

			क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, slave, plane) अणु
				स्थिर काष्ठा पूर्णांकel_plane_state *plane_state =
					to_पूर्णांकel_plane_state(plane->base.state);

				/*
				 * FIXME करोn't have the fb yet, so can't
				 * use पूर्णांकel_plane_data_rate() :(
				 */
				अगर (plane_state->uapi.visible)
					crtc_state->data_rate[plane->id] =
						4 * crtc_state->pixel_rate;
				अन्यथा
					crtc_state->data_rate[plane->id] = 0;
			पूर्ण

			पूर्णांकel_bw_crtc_update(bw_state, slave_crtc_state);
			drm_calc_बारtamping_स्थिरants(&slave->base,
							&slave_crtc_state->hw.adjusted_mode);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
get_encoder_घातer_करोमुख्यs(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *encoder;

	क्रम_each_पूर्णांकel_encoder(&dev_priv->drm, encoder) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state;

		अगर (!encoder->get_घातer_करोमुख्यs)
			जारी;

		/*
		 * MST-primary and inactive encoders करोn't have a crtc state
		 * and neither of these require any घातer करोमुख्य references.
		 */
		अगर (!encoder->base.crtc)
			जारी;

		crtc_state = to_पूर्णांकel_crtc_state(encoder->base.crtc->state);
		encoder->get_घातer_करोमुख्यs(encoder, crtc_state);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_early_display_was(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * Display WA #1185 WaDisableDARBFClkGating:cnl,glk,icl,ehl,tgl
	 * Also known as Wa_14010480278.
	 */
	अगर (IS_DISPLAY_RANGE(dev_priv, 10, 12))
		पूर्णांकel_de_ग_लिखो(dev_priv, GEN9_CLKGATE_DIS_0,
			       पूर्णांकel_de_पढ़ो(dev_priv, GEN9_CLKGATE_DIS_0) | DARBF_GATING_DIS);

	अगर (IS_HASWELL(dev_priv)) अणु
		/*
		 * WaRsPkgCStateDisplayPMReq:hsw
		 * System hang अगर this isn't करोne beक्रमe disabling all planes!
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, CHICKEN_PAR1_1,
			       पूर्णांकel_de_पढ़ो(dev_priv, CHICKEN_PAR1_1) | FORCE_ARB_IDLE_PLANES);
	पूर्ण

	अगर (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv) || IS_COMETLAKE(dev_priv)) अणु
		/* Display WA #1142:kbl,cfl,cml */
		पूर्णांकel_de_rmw(dev_priv, CHICKEN_PAR1_1,
			     KBL_ARB_FILL_SPARE_22, KBL_ARB_FILL_SPARE_22);
		पूर्णांकel_de_rmw(dev_priv, CHICKEN_MISC_2,
			     KBL_ARB_FILL_SPARE_13 | KBL_ARB_FILL_SPARE_14,
			     KBL_ARB_FILL_SPARE_14);
	पूर्ण
पूर्ण

अटल व्योम ibx_sanitize_pch_hdmi_port(काष्ठा drm_i915_निजी *dev_priv,
				       क्रमागत port port, i915_reg_t hdmi_reg)
अणु
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, hdmi_reg);

	अगर (val & SDVO_ENABLE ||
	    (val & SDVO_PIPE_SEL_MASK) == SDVO_PIPE_SEL(PIPE_A))
		वापस;

	drm_dbg_kms(&dev_priv->drm,
		    "Sanitizing transcoder select for HDMI %c\n",
		    port_name(port));

	val &= ~SDVO_PIPE_SEL_MASK;
	val |= SDVO_PIPE_SEL(PIPE_A);

	पूर्णांकel_de_ग_लिखो(dev_priv, hdmi_reg, val);
पूर्ण

अटल व्योम ibx_sanitize_pch_dp_port(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत port port, i915_reg_t dp_reg)
अणु
	u32 val = पूर्णांकel_de_पढ़ो(dev_priv, dp_reg);

	अगर (val & DP_PORT_EN ||
	    (val & DP_PIPE_SEL_MASK) == DP_PIPE_SEL(PIPE_A))
		वापस;

	drm_dbg_kms(&dev_priv->drm,
		    "Sanitizing transcoder select for DP %c\n",
		    port_name(port));

	val &= ~DP_PIPE_SEL_MASK;
	val |= DP_PIPE_SEL(PIPE_A);

	पूर्णांकel_de_ग_लिखो(dev_priv, dp_reg, val);
पूर्ण

अटल व्योम ibx_sanitize_pch_ports(काष्ठा drm_i915_निजी *dev_priv)
अणु
	/*
	 * The BIOS may select transcoder B on some of the PCH
	 * ports even it करोesn't enable the port. This would trip
	 * निश्चित_pch_dp_disabled() and निश्चित_pch_hdmi_disabled().
	 * Sanitize the transcoder select bits to prevent that. We
	 * assume that the BIOS never actually enabled the port,
	 * because अगर it did we'd actually have to toggle the port
	 * on and back off to make the transcoder A select stick
	 * (see. पूर्णांकel_dp_link_करोwn(), पूर्णांकel_disable_hdmi(),
	 * पूर्णांकel_disable_sdvo()).
	 */
	ibx_sanitize_pch_dp_port(dev_priv, PORT_B, PCH_DP_B);
	ibx_sanitize_pch_dp_port(dev_priv, PORT_C, PCH_DP_C);
	ibx_sanitize_pch_dp_port(dev_priv, PORT_D, PCH_DP_D);

	/* PCH SDVOB multiplex with HDMIB */
	ibx_sanitize_pch_hdmi_port(dev_priv, PORT_B, PCH_HDMIB);
	ibx_sanitize_pch_hdmi_port(dev_priv, PORT_C, PCH_HDMIC);
	ibx_sanitize_pch_hdmi_port(dev_priv, PORT_D, PCH_HDMID);
पूर्ण

/* Scan out the current hw modeset state,
 * and sanitizes it to the current state
 */
अटल व्योम
पूर्णांकel_modeset_setup_hw_state(काष्ठा drm_device *dev,
			     काष्ठा drm_modeset_acquire_ctx *ctx)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा पूर्णांकel_crtc *crtc;
	पूर्णांकel_wakeref_t wakeref;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv, POWER_DOMAIN_INIT);

	पूर्णांकel_early_display_was(dev_priv);
	पूर्णांकel_modeset_पढ़ोout_hw_state(dev);

	/* HW state is पढ़ो out, now we need to sanitize this mess. */

	/* Sanitize the TypeC port mode upfront, encoders depend on this */
	क्रम_each_पूर्णांकel_encoder(dev, encoder) अणु
		क्रमागत phy phy = पूर्णांकel_port_to_phy(dev_priv, encoder->port);

		/* We need to sanitize only the MST primary port. */
		अगर (encoder->type != INTEL_OUTPUT_DP_MST &&
		    पूर्णांकel_phy_is_tc(dev_priv, phy))
			पूर्णांकel_tc_port_sanitize(enc_to_dig_port(encoder));
	पूर्ण

	get_encoder_घातer_करोमुख्यs(dev_priv);

	अगर (HAS_PCH_IBX(dev_priv))
		ibx_sanitize_pch_ports(dev_priv);

	/*
	 * पूर्णांकel_sanitize_plane_mapping() may need to करो vblank
	 * रुकोs, so we need vblank पूर्णांकerrupts restored beक्रमehand.
	 */
	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		drm_crtc_vblank_reset(&crtc->base);

		अगर (crtc_state->hw.active)
			पूर्णांकel_crtc_vblank_on(crtc_state);
	पूर्ण

	पूर्णांकel_sanitize_plane_mapping(dev_priv);

	क्रम_each_पूर्णांकel_encoder(dev, encoder)
		पूर्णांकel_sanitize_encoder(encoder);

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);

		पूर्णांकel_sanitize_crtc(crtc, ctx);
		पूर्णांकel_dump_pipe_config(crtc_state, शून्य, "[setup_hw_state]");
	पूर्ण

	पूर्णांकel_modeset_update_connector_atomic_state(dev);

	पूर्णांकel_dpll_sanitize_state(dev_priv);

	अगर (IS_G4X(dev_priv)) अणु
		g4x_wm_get_hw_state(dev_priv);
		g4x_wm_sanitize(dev_priv);
	पूर्ण अन्यथा अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		vlv_wm_get_hw_state(dev_priv);
		vlv_wm_sanitize(dev_priv);
	पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 9) अणु
		skl_wm_get_hw_state(dev_priv);
	पूर्ण अन्यथा अगर (HAS_PCH_SPLIT(dev_priv)) अणु
		ilk_wm_get_hw_state(dev_priv);
	पूर्ण

	क्रम_each_पूर्णांकel_crtc(dev, crtc) अणु
		काष्ठा पूर्णांकel_crtc_state *crtc_state =
			to_पूर्णांकel_crtc_state(crtc->base.state);
		u64 put_करोमुख्यs;

		put_करोमुख्यs = modeset_get_crtc_घातer_करोमुख्यs(crtc_state);
		अगर (drm_WARN_ON(dev, put_करोमुख्यs))
			modeset_put_crtc_घातer_करोमुख्यs(crtc, put_करोमुख्यs);
	पूर्ण

	पूर्णांकel_display_घातer_put(dev_priv, POWER_DOMAIN_INIT, wakeref);
पूर्ण

व्योम पूर्णांकel_display_resume(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_atomic_state *state = dev_priv->modeset_restore_state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक ret;

	dev_priv->modeset_restore_state = शून्य;
	अगर (state)
		state->acquire_ctx = &ctx;

	drm_modeset_acquire_init(&ctx, 0);

	जबतक (1) अणु
		ret = drm_modeset_lock_all_ctx(dev, &ctx);
		अगर (ret != -EDEADLK)
			अवरोध;

		drm_modeset_backoff(&ctx);
	पूर्ण

	अगर (!ret)
		ret = __पूर्णांकel_display_resume(dev, state, &ctx);

	पूर्णांकel_enable_ipc(dev_priv);
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	अगर (ret)
		drm_err(&dev_priv->drm,
			"Restoring old state failed with %i\n", ret);
	अगर (state)
		drm_atomic_state_put(state);
पूर्ण

अटल व्योम पूर्णांकel_hpd_poll_fini(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा पूर्णांकel_connector *connector;
	काष्ठा drm_connector_list_iter conn_iter;

	/* Kill all the work that may have been queued by hpd. */
	drm_connector_list_iter_begin(&i915->drm, &conn_iter);
	क्रम_each_पूर्णांकel_connector_iter(connector, &conn_iter) अणु
		अगर (connector->modeset_retry_work.func)
			cancel_work_sync(&connector->modeset_retry_work);
		अगर (connector->hdcp.shim) अणु
			cancel_delayed_work_sync(&connector->hdcp.check_work);
			cancel_work_sync(&connector->hdcp.prop_work);
		पूर्ण
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
पूर्ण

/* part #1: call beक्रमe irq uninstall */
व्योम पूर्णांकel_modeset_driver_हटाओ(काष्ठा drm_i915_निजी *i915)
अणु
	flush_workqueue(i915->flip_wq);
	flush_workqueue(i915->modeset_wq);

	flush_work(&i915->atomic_helper.मुक्त_work);
	drm_WARN_ON(&i915->drm, !llist_empty(&i915->atomic_helper.मुक्त_list));
पूर्ण

/* part #2: call after irq uninstall */
व्योम पूर्णांकel_modeset_driver_हटाओ_noirq(काष्ठा drm_i915_निजी *i915)
अणु
	/*
	 * Due to the hpd irq storm handling the hotplug work can re-arm the
	 * poll handlers. Hence disable polling after hpd handling is shut करोwn.
	 */
	पूर्णांकel_hpd_poll_fini(i915);

	/*
	 * MST topology needs to be suspended so we करोn't have any calls to
	 * fbdev after it's finalized. MST will be destroyed later as part of
	 * drm_mode_config_cleanup()
	 */
	पूर्णांकel_dp_mst_suspend(i915);

	/* poll work can call पूर्णांकo fbdev, hence clean that up afterwards */
	पूर्णांकel_fbdev_fini(i915);

	पूर्णांकel_unरेजिस्टर_dsm_handler();

	पूर्णांकel_fbc_global_disable(i915);

	/* flush any delayed tasks or pending work */
	flush_scheduled_work();

	पूर्णांकel_hdcp_component_fini(i915);

	पूर्णांकel_mode_config_cleanup(i915);

	पूर्णांकel_overlay_cleanup(i915);

	पूर्णांकel_gmbus_tearकरोwn(i915);

	destroy_workqueue(i915->flip_wq);
	destroy_workqueue(i915->modeset_wq);

	पूर्णांकel_fbc_cleanup_cfb(i915);
पूर्ण

/* part #3: call after gem init */
व्योम पूर्णांकel_modeset_driver_हटाओ_nogem(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_csr_ucode_fini(i915);

	पूर्णांकel_घातer_करोमुख्यs_driver_हटाओ(i915);

	पूर्णांकel_vga_unरेजिस्टर(i915);

	पूर्णांकel_bios_driver_हटाओ(i915);
पूर्ण

व्योम पूर्णांकel_display_driver_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (!HAS_DISPLAY(i915))
		वापस;

	पूर्णांकel_display_debugfs_रेजिस्टर(i915);

	/* Must be करोne after probing outमाला_दो */
	पूर्णांकel_opregion_रेजिस्टर(i915);
	acpi_video_रेजिस्टर();

	पूर्णांकel_audio_init(i915);

	/*
	 * Some ports require correctly set-up hpd रेजिस्टरs क्रम
	 * detection to work properly (leading to ghost connected
	 * connector status), e.g. VGA on gm45.  Hence we can only set
	 * up the initial fbdev config after hpd irqs are fully
	 * enabled. We करो it last so that the async config cannot run
	 * beक्रमe the connectors are रेजिस्टरed.
	 */
	पूर्णांकel_fbdev_initial_config_async(&i915->drm);

	/*
	 * We need to coordinate the hotplugs with the asynchronous
	 * fbdev configuration, क्रम which we use the
	 * fbdev->async_cookie.
	 */
	drm_kms_helper_poll_init(&i915->drm);
पूर्ण

व्योम पूर्णांकel_display_driver_unरेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (!HAS_DISPLAY(i915))
		वापस;

	पूर्णांकel_fbdev_unरेजिस्टर(i915);
	पूर्णांकel_audio_deinit(i915);

	/*
	 * After flushing the fbdev (incl. a late async config which
	 * will have delayed queuing of a hotplug event), then flush
	 * the hotplug events.
	 */
	drm_kms_helper_poll_fini(&i915->drm);
	drm_atomic_helper_shutकरोwn(&i915->drm);

	acpi_video_unरेजिस्टर();
	पूर्णांकel_opregion_unरेजिस्टर(i915);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_CAPTURE_ERROR)

काष्ठा पूर्णांकel_display_error_state अणु

	u32 घातer_well_driver;

	काष्ठा पूर्णांकel_cursor_error_state अणु
		u32 control;
		u32 position;
		u32 base;
		u32 size;
	पूर्ण cursor[I915_MAX_PIPES];

	काष्ठा पूर्णांकel_pipe_error_state अणु
		bool घातer_करोमुख्य_on;
		u32 source;
		u32 stat;
	पूर्ण pipe[I915_MAX_PIPES];

	काष्ठा पूर्णांकel_plane_error_state अणु
		u32 control;
		u32 stride;
		u32 size;
		u32 pos;
		u32 addr;
		u32 surface;
		u32 tile_offset;
	पूर्ण plane[I915_MAX_PIPES];

	काष्ठा पूर्णांकel_transcoder_error_state अणु
		bool available;
		bool घातer_करोमुख्य_on;
		क्रमागत transcoder cpu_transcoder;

		u32 conf;

		u32 htotal;
		u32 hblank;
		u32 hsync;
		u32 vtotal;
		u32 vblank;
		u32 vsync;
	पूर्ण transcoder[5];
पूर्ण;

काष्ठा पूर्णांकel_display_error_state *
पूर्णांकel_display_capture_error_state(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_display_error_state *error;
	पूर्णांक transcoders[] = अणु
		TRANSCODER_A,
		TRANSCODER_B,
		TRANSCODER_C,
		TRANSCODER_D,
		TRANSCODER_EDP,
	पूर्ण;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(transcoders) != ARRAY_SIZE(error->transcoder));

	अगर (!HAS_DISPLAY(dev_priv))
		वापस शून्य;

	error = kzalloc(माप(*error), GFP_ATOMIC);
	अगर (error == शून्य)
		वापस शून्य;

	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		error->घातer_well_driver = पूर्णांकel_de_पढ़ो(dev_priv,
							 HSW_PWR_WELL_CTL2);

	क्रम_each_pipe(dev_priv, i) अणु
		error->pipe[i].घातer_करोमुख्य_on =
			__पूर्णांकel_display_घातer_is_enabled(dev_priv,
							 POWER_DOMAIN_PIPE(i));
		अगर (!error->pipe[i].घातer_करोमुख्य_on)
			जारी;

		error->cursor[i].control = पूर्णांकel_de_पढ़ो(dev_priv, CURCNTR(i));
		error->cursor[i].position = पूर्णांकel_de_पढ़ो(dev_priv, CURPOS(i));
		error->cursor[i].base = पूर्णांकel_de_पढ़ो(dev_priv, CURBASE(i));

		error->plane[i].control = पूर्णांकel_de_पढ़ो(dev_priv, DSPCNTR(i));
		error->plane[i].stride = पूर्णांकel_de_पढ़ो(dev_priv, DSPSTRIDE(i));
		अगर (DISPLAY_VER(dev_priv) <= 3) अणु
			error->plane[i].size = पूर्णांकel_de_पढ़ो(dev_priv,
							     DSPSIZE(i));
			error->plane[i].pos = पूर्णांकel_de_पढ़ो(dev_priv,
							    DSPPOS(i));
		पूर्ण
		अगर (DISPLAY_VER(dev_priv) <= 7 && !IS_HASWELL(dev_priv))
			error->plane[i].addr = पूर्णांकel_de_पढ़ो(dev_priv,
							     DSPADDR(i));
		अगर (DISPLAY_VER(dev_priv) >= 4) अणु
			error->plane[i].surface = पूर्णांकel_de_पढ़ो(dev_priv,
								DSPSURF(i));
			error->plane[i].tile_offset = पूर्णांकel_de_पढ़ो(dev_priv,
								    DSPTILखातापूर्णF(i));
		पूर्ण

		error->pipe[i].source = पूर्णांकel_de_पढ़ो(dev_priv, PIPESRC(i));

		अगर (HAS_GMCH(dev_priv))
			error->pipe[i].stat = पूर्णांकel_de_पढ़ो(dev_priv,
							    PIPESTAT(i));
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(error->transcoder); i++) अणु
		क्रमागत transcoder cpu_transcoder = transcoders[i];

		अगर (!HAS_TRANSCODER(dev_priv, cpu_transcoder))
			जारी;

		error->transcoder[i].available = true;
		error->transcoder[i].घातer_करोमुख्य_on =
			__पूर्णांकel_display_घातer_is_enabled(dev_priv,
				POWER_DOMAIN_TRANSCODER(cpu_transcoder));
		अगर (!error->transcoder[i].घातer_करोमुख्य_on)
			जारी;

		error->transcoder[i].cpu_transcoder = cpu_transcoder;

		error->transcoder[i].conf = पूर्णांकel_de_पढ़ो(dev_priv,
							  PIPECONF(cpu_transcoder));
		error->transcoder[i].htotal = पूर्णांकel_de_पढ़ो(dev_priv,
							    HTOTAL(cpu_transcoder));
		error->transcoder[i].hblank = पूर्णांकel_de_पढ़ो(dev_priv,
							    HBLANK(cpu_transcoder));
		error->transcoder[i].hsync = पूर्णांकel_de_पढ़ो(dev_priv,
							   HSYNC(cpu_transcoder));
		error->transcoder[i].vtotal = पूर्णांकel_de_पढ़ो(dev_priv,
							    VTOTAL(cpu_transcoder));
		error->transcoder[i].vblank = पूर्णांकel_de_पढ़ो(dev_priv,
							    VBLANK(cpu_transcoder));
		error->transcoder[i].vsync = पूर्णांकel_de_पढ़ो(dev_priv,
							   VSYNC(cpu_transcoder));
	पूर्ण

	वापस error;
पूर्ण

#घोषणा err_म_लिखो(e, ...) i915_error_म_लिखो(e, __VA_ARGS__)

व्योम
पूर्णांकel_display_prपूर्णांक_error_state(काष्ठा drm_i915_error_state_buf *m,
				काष्ठा पूर्णांकel_display_error_state *error)
अणु
	काष्ठा drm_i915_निजी *dev_priv = m->i915;
	पूर्णांक i;

	अगर (!error)
		वापस;

	err_म_लिखो(m, "Num Pipes: %d\n", INTEL_NUM_PIPES(dev_priv));
	अगर (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv))
		err_म_लिखो(m, "PWR_WELL_CTL2: %08x\n",
			   error->घातer_well_driver);
	क्रम_each_pipe(dev_priv, i) अणु
		err_म_लिखो(m, "Pipe [%d]:\n", i);
		err_म_लिखो(m, "  Power: %s\n",
			   onoff(error->pipe[i].घातer_करोमुख्य_on));
		err_म_लिखो(m, "  SRC: %08x\n", error->pipe[i].source);
		err_म_लिखो(m, "  STAT: %08x\n", error->pipe[i].stat);

		err_म_लिखो(m, "Plane [%d]:\n", i);
		err_म_लिखो(m, "  CNTR: %08x\n", error->plane[i].control);
		err_म_लिखो(m, "  STRIDE: %08x\n", error->plane[i].stride);
		अगर (DISPLAY_VER(dev_priv) <= 3) अणु
			err_म_लिखो(m, "  SIZE: %08x\n", error->plane[i].size);
			err_म_लिखो(m, "  POS: %08x\n", error->plane[i].pos);
		पूर्ण
		अगर (DISPLAY_VER(dev_priv) <= 7 && !IS_HASWELL(dev_priv))
			err_म_लिखो(m, "  ADDR: %08x\n", error->plane[i].addr);
		अगर (DISPLAY_VER(dev_priv) >= 4) अणु
			err_म_लिखो(m, "  SURF: %08x\n", error->plane[i].surface);
			err_म_लिखो(m, "  TILEOFF: %08x\n", error->plane[i].tile_offset);
		पूर्ण

		err_म_लिखो(m, "Cursor [%d]:\n", i);
		err_म_लिखो(m, "  CNTR: %08x\n", error->cursor[i].control);
		err_म_लिखो(m, "  POS: %08x\n", error->cursor[i].position);
		err_म_लिखो(m, "  BASE: %08x\n", error->cursor[i].base);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(error->transcoder); i++) अणु
		अगर (!error->transcoder[i].available)
			जारी;

		err_म_लिखो(m, "CPU transcoder: %s\n",
			   transcoder_name(error->transcoder[i].cpu_transcoder));
		err_म_लिखो(m, "  Power: %s\n",
			   onoff(error->transcoder[i].घातer_करोमुख्य_on));
		err_म_लिखो(m, "  CONF: %08x\n", error->transcoder[i].conf);
		err_म_लिखो(m, "  HTOTAL: %08x\n", error->transcoder[i].htotal);
		err_म_लिखो(m, "  HBLANK: %08x\n", error->transcoder[i].hblank);
		err_म_लिखो(m, "  HSYNC: %08x\n", error->transcoder[i].hsync);
		err_म_लिखो(m, "  VTOTAL: %08x\n", error->transcoder[i].vtotal);
		err_म_लिखो(m, "  VBLANK: %08x\n", error->transcoder[i].vblank);
		err_म_लिखो(m, "  VSYNC: %08x\n", error->transcoder[i].vsync);
	पूर्ण
पूर्ण

#पूर्ण_अगर
