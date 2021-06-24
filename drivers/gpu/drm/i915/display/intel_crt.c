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

#समावेश <linux/dmi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "i915_drv.h"
#समावेश "intel_connector.h"
#समावेश "intel_crt.h"
#समावेश "intel_ddi.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fdi.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_gmbus.h"
#समावेश "intel_hotplug.h"

/* Here's the desired hotplug mode */
#घोषणा ADPA_HOTPLUG_BITS (ADPA_CRT_HOTPLUG_PERIOD_128 |		\
			   ADPA_CRT_HOTPLUG_WARMUP_10MS |		\
			   ADPA_CRT_HOTPLUG_SAMPLE_4S |			\
			   ADPA_CRT_HOTPLUG_VOLTAGE_50 |		\
			   ADPA_CRT_HOTPLUG_VOLREF_325MV |		\
			   ADPA_CRT_HOTPLUG_ENABLE)

काष्ठा पूर्णांकel_crt अणु
	काष्ठा पूर्णांकel_encoder base;
	/* DPMS state is stored in the connector, which we need in the
	 * encoder's enable/disable callbacks */
	काष्ठा पूर्णांकel_connector *connector;
	bool क्रमce_hotplug_required;
	i915_reg_t adpa_reg;
पूर्ण;

अटल काष्ठा पूर्णांकel_crt *पूर्णांकel_encoder_to_crt(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा पूर्णांकel_crt, base);
पूर्ण

अटल काष्ठा पूर्णांकel_crt *पूर्णांकel_attached_crt(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस पूर्णांकel_encoder_to_crt(पूर्णांकel_attached_encoder(connector));
पूर्ण

bool पूर्णांकel_crt_port_enabled(काष्ठा drm_i915_निजी *dev_priv,
			    i915_reg_t adpa_reg, क्रमागत pipe *pipe)
अणु
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, adpa_reg);

	/* निश्चितs want to know the pipe even अगर the port is disabled */
	अगर (HAS_PCH_CPT(dev_priv))
		*pipe = (val & ADPA_PIPE_SEL_MASK_CPT) >> ADPA_PIPE_SEL_SHIFT_CPT;
	अन्यथा
		*pipe = (val & ADPA_PIPE_SEL_MASK) >> ADPA_PIPE_SEL_SHIFT;

	वापस val & ADPA_DAC_ENABLE;
पूर्ण

अटल bool पूर्णांकel_crt_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				   क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_encoder_to_crt(encoder);
	पूर्णांकel_wakeref_t wakeref;
	bool ret;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	ret = पूर्णांकel_crt_port_enabled(dev_priv, crt->adpa_reg, pipe);

	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक पूर्णांकel_crt_get_flags(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_encoder_to_crt(encoder);
	u32 पंचांगp, flags = 0;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, crt->adpa_reg);

	अगर (पंचांगp & ADPA_HSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NHSYNC;

	अगर (पंचांगp & ADPA_VSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NVSYNC;

	वापस flags;
पूर्ण

अटल व्योम पूर्णांकel_crt_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	pipe_config->output_types |= BIT(INTEL_OUTPUT_ANALOG);

	pipe_config->hw.adjusted_mode.flags |= पूर्णांकel_crt_get_flags(encoder);

	pipe_config->hw.adjusted_mode.crtc_घड़ी = pipe_config->port_घड़ी;
पूर्ण

अटल व्योम hsw_crt_get_config(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	hsw_ddi_get_config(encoder, pipe_config);

	pipe_config->hw.adjusted_mode.flags &= ~(DRM_MODE_FLAG_PHSYNC |
					      DRM_MODE_FLAG_NHSYNC |
					      DRM_MODE_FLAG_PVSYNC |
					      DRM_MODE_FLAG_NVSYNC);
	pipe_config->hw.adjusted_mode.flags |= पूर्णांकel_crt_get_flags(encoder);

	pipe_config->hw.adjusted_mode.crtc_घड़ी = lpt_get_iclkip(dev_priv);
पूर्ण

/* Note: The caller is required to filter out dpms modes not supported by the
 * platक्रमm. */
अटल व्योम पूर्णांकel_crt_set_dpms(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       पूर्णांक mode)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_encoder_to_crt(encoder);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &crtc_state->hw.adjusted_mode;
	u32 adpa;

	अगर (DISPLAY_VER(dev_priv) >= 5)
		adpa = ADPA_HOTPLUG_BITS;
	अन्यथा
		adpa = 0;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		adpa |= ADPA_HSYNC_ACTIVE_HIGH;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		adpa |= ADPA_VSYNC_ACTIVE_HIGH;

	/* For CPT allow 3 pipe config, क्रम others just use A or B */
	अगर (HAS_PCH_LPT(dev_priv))
		; /* Those bits करोn't exist here */
	अन्यथा अगर (HAS_PCH_CPT(dev_priv))
		adpa |= ADPA_PIPE_SEL_CPT(crtc->pipe);
	अन्यथा
		adpa |= ADPA_PIPE_SEL(crtc->pipe);

	अगर (!HAS_PCH_SPLIT(dev_priv))
		पूर्णांकel_de_ग_लिखो(dev_priv, BCLRPAT(crtc->pipe), 0);

	चयन (mode) अणु
	हाल DRM_MODE_DPMS_ON:
		adpa |= ADPA_DAC_ENABLE;
		अवरोध;
	हाल DRM_MODE_DPMS_STANDBY:
		adpa |= ADPA_DAC_ENABLE | ADPA_HSYNC_CNTL_DISABLE;
		अवरोध;
	हाल DRM_MODE_DPMS_SUSPEND:
		adpa |= ADPA_DAC_ENABLE | ADPA_VSYNC_CNTL_DISABLE;
		अवरोध;
	हाल DRM_MODE_DPMS_OFF:
		adpa |= ADPA_HSYNC_CNTL_DISABLE | ADPA_VSYNC_CNTL_DISABLE;
		अवरोध;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, crt->adpa_reg, adpa);
पूर्ण

अटल व्योम पूर्णांकel_disable_crt(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_crt_set_dpms(encoder, old_crtc_state, DRM_MODE_DPMS_OFF);
पूर्ण

अटल व्योम pch_disable_crt(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			    स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
पूर्ण

अटल व्योम pch_post_disable_crt(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				 स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_disable_crt(state, encoder, old_crtc_state, old_conn_state);
पूर्ण

अटल व्योम hsw_disable_crt(काष्ठा पूर्णांकel_atomic_state *state,
			    काष्ठा पूर्णांकel_encoder *encoder,
			    स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			    स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	drm_WARN_ON(&dev_priv->drm, !old_crtc_state->has_pch_encoder);

	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);
पूर्ण

अटल व्योम hsw_post_disable_crt(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				 स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	पूर्णांकel_crtc_vblank_off(old_crtc_state);

	पूर्णांकel_disable_pipe(old_crtc_state);

	पूर्णांकel_ddi_disable_transcoder_func(old_crtc_state);

	ilk_pfit_disable(old_crtc_state);

	पूर्णांकel_ddi_disable_pipe_घड़ी(old_crtc_state);

	pch_post_disable_crt(state, encoder, old_crtc_state, old_conn_state);

	lpt_disable_pch_transcoder(dev_priv);
	lpt_disable_iclkip(dev_priv);

	पूर्णांकel_ddi_fdi_post_disable(state, encoder, old_crtc_state, old_conn_state);

	drm_WARN_ON(&dev_priv->drm, !old_crtc_state->has_pch_encoder);

	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
पूर्ण

अटल व्योम hsw_pre_pll_enable_crt(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	drm_WARN_ON(&dev_priv->drm, !crtc_state->has_pch_encoder);

	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, false);
पूर्ण

अटल व्योम hsw_pre_enable_crt(काष्ठा पूर्णांकel_atomic_state *state,
			       काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;

	drm_WARN_ON(&dev_priv->drm, !crtc_state->has_pch_encoder);

	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, false);

	hsw_fdi_link_train(encoder, crtc_state);

	पूर्णांकel_ddi_enable_pipe_घड़ी(encoder, crtc_state);
पूर्ण

अटल व्योम hsw_enable_crt(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;

	drm_WARN_ON(&dev_priv->drm, !crtc_state->has_pch_encoder);

	पूर्णांकel_ddi_enable_transcoder_func(encoder, crtc_state);

	पूर्णांकel_enable_pipe(crtc_state);

	lpt_pch_enable(crtc_state);

	पूर्णांकel_crtc_vblank_on(crtc_state);

	पूर्णांकel_crt_set_dpms(encoder, crtc_state, DRM_MODE_DPMS_ON);

	पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
	पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, true);
	पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, PIPE_A, true);
पूर्ण

अटल व्योम पूर्णांकel_enable_crt(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	पूर्णांकel_crt_set_dpms(encoder, crtc_state, DRM_MODE_DPMS_ON);
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_crt_mode_valid(काष्ठा drm_connector *connector,
		     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	पूर्णांक max_करोtclk = dev_priv->max_करोtclk_freq;
	पूर्णांक max_घड़ी;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	अगर (mode->घड़ी < 25000)
		वापस MODE_CLOCK_LOW;

	अगर (HAS_PCH_LPT(dev_priv))
		max_घड़ी = 180000;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		/*
		 * 270 MHz due to current DPLL limits,
		 * DAC limit supposedly 355 MHz.
		 */
		max_घड़ी = 270000;
	अन्यथा अगर (IS_DISPLAY_RANGE(dev_priv, 3, 4))
		max_घड़ी = 400000;
	अन्यथा
		max_घड़ी = 350000;
	अगर (mode->घड़ी > max_घड़ी)
		वापस MODE_CLOCK_HIGH;

	अगर (mode->घड़ी > max_करोtclk)
		वापस MODE_CLOCK_HIGH;

	/* The FDI receiver on LPT only supports 8bpc and only has 2 lanes. */
	अगर (HAS_PCH_LPT(dev_priv) &&
	    ilk_get_lanes_required(mode->घड़ी, 270000, 24) > 2)
		वापस MODE_CLOCK_HIGH;

	/* HSW/BDW FDI limited to 4k */
	अगर (mode->hdisplay > 4096)
		वापस MODE_H_ILLEGAL;

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक पूर्णांकel_crt_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	वापस 0;
पूर्ण

अटल पूर्णांक pch_crt_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	pipe_config->has_pch_encoder = true;
	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	वापस 0;
पूर्ण

अटल पूर्णांक hsw_crt_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config,
				  काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	/* HSW/BDW FDI limited to 4k */
	अगर (adjusted_mode->crtc_hdisplay > 4096 ||
	    adjusted_mode->crtc_hblank_start > 4096)
		वापस -EINVAL;

	pipe_config->has_pch_encoder = true;
	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	/* LPT FDI RX only supports 8bpc. */
	अगर (HAS_PCH_LPT(dev_priv)) अणु
		अगर (pipe_config->bw_स्थिरrained && pipe_config->pipe_bpp < 24) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "LPT only supports 24bpp\n");
			वापस -EINVAL;
		पूर्ण

		pipe_config->pipe_bpp = 24;
	पूर्ण

	/* FDI must always be 2.7 GHz */
	pipe_config->port_घड़ी = 135000 * 2;

	वापस 0;
पूर्ण

अटल bool ilk_crt_detect_hotplug(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_attached_crt(to_पूर्णांकel_connector(connector));
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 adpa;
	bool ret;

	/* The first समय through, trigger an explicit detection cycle */
	अगर (crt->क्रमce_hotplug_required) अणु
		bool turn_off_dac = HAS_PCH_SPLIT(dev_priv);
		u32 save_adpa;

		crt->क्रमce_hotplug_required = false;

		save_adpa = adpa = पूर्णांकel_de_पढ़ो(dev_priv, crt->adpa_reg);
		drm_dbg_kms(&dev_priv->drm,
			    "trigger hotplug detect cycle: adpa=0x%x\n", adpa);

		adpa |= ADPA_CRT_HOTPLUG_FORCE_TRIGGER;
		अगर (turn_off_dac)
			adpa &= ~ADPA_DAC_ENABLE;

		पूर्णांकel_de_ग_लिखो(dev_priv, crt->adpa_reg, adpa);

		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv,
					    crt->adpa_reg,
					    ADPA_CRT_HOTPLUG_FORCE_TRIGGER,
					    1000))
			drm_dbg_kms(&dev_priv->drm,
				    "timed out waiting for FORCE_TRIGGER");

		अगर (turn_off_dac) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, crt->adpa_reg, save_adpa);
			पूर्णांकel_de_posting_पढ़ो(dev_priv, crt->adpa_reg);
		पूर्ण
	पूर्ण

	/* Check the status to see अगर both blue and green are on now */
	adpa = पूर्णांकel_de_पढ़ो(dev_priv, crt->adpa_reg);
	अगर ((adpa & ADPA_CRT_HOTPLUG_MONITOR_MASK) != 0)
		ret = true;
	अन्यथा
		ret = false;
	drm_dbg_kms(&dev_priv->drm, "ironlake hotplug adpa=0x%x, result %d\n",
		    adpa, ret);

	वापस ret;
पूर्ण

अटल bool valleyview_crt_detect_hotplug(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_attached_crt(to_पूर्णांकel_connector(connector));
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	bool reenable_hpd;
	u32 adpa;
	bool ret;
	u32 save_adpa;

	/*
	 * Doing a क्रमce trigger causes a hpd पूर्णांकerrupt to get sent, which can
	 * get us stuck in a loop अगर we're polling:
	 *  - We enable घातer wells and reset the ADPA
	 *  - output_poll_exec करोes क्रमce probe on VGA, triggering a hpd
	 *  - HPD handler रुकोs क्रम poll to unlock dev->mode_config.mutex
	 *  - output_poll_exec shuts off the ADPA, unlocks
	 *    dev->mode_config.mutex
	 *  - HPD handler runs, resets ADPA and brings us back to the start
	 *
	 * Just disable HPD पूर्णांकerrupts here to prevent this
	 */
	reenable_hpd = पूर्णांकel_hpd_disable(dev_priv, crt->base.hpd_pin);

	save_adpa = adpa = पूर्णांकel_de_पढ़ो(dev_priv, crt->adpa_reg);
	drm_dbg_kms(&dev_priv->drm,
		    "trigger hotplug detect cycle: adpa=0x%x\n", adpa);

	adpa |= ADPA_CRT_HOTPLUG_FORCE_TRIGGER;

	पूर्णांकel_de_ग_लिखो(dev_priv, crt->adpa_reg, adpa);

	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, crt->adpa_reg,
				    ADPA_CRT_HOTPLUG_FORCE_TRIGGER, 1000)) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "timed out waiting for FORCE_TRIGGER");
		पूर्णांकel_de_ग_लिखो(dev_priv, crt->adpa_reg, save_adpa);
	पूर्ण

	/* Check the status to see अगर both blue and green are on now */
	adpa = पूर्णांकel_de_पढ़ो(dev_priv, crt->adpa_reg);
	अगर ((adpa & ADPA_CRT_HOTPLUG_MONITOR_MASK) != 0)
		ret = true;
	अन्यथा
		ret = false;

	drm_dbg_kms(&dev_priv->drm,
		    "valleyview hotplug adpa=0x%x, result %d\n", adpa, ret);

	अगर (reenable_hpd)
		पूर्णांकel_hpd_enable(dev_priv, crt->base.hpd_pin);

	वापस ret;
पूर्ण

अटल bool पूर्णांकel_crt_detect_hotplug(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 stat;
	bool ret = false;
	पूर्णांक i, tries = 0;

	अगर (HAS_PCH_SPLIT(dev_priv))
		वापस ilk_crt_detect_hotplug(connector);

	अगर (IS_VALLEYVIEW(dev_priv))
		वापस valleyview_crt_detect_hotplug(connector);

	/*
	 * On 4 series desktop, CRT detect sequence need to be करोne twice
	 * to get a reliable result.
	 */

	अगर (IS_G45(dev_priv))
		tries = 2;
	अन्यथा
		tries = 1;

	क्रम (i = 0; i < tries ; i++) अणु
		/* turn on the FORCE_DETECT */
		i915_hotplug_पूर्णांकerrupt_update(dev_priv,
					      CRT_HOTPLUG_FORCE_DETECT,
					      CRT_HOTPLUG_FORCE_DETECT);
		/* रुको क्रम FORCE_DETECT to go off */
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, PORT_HOTPLUG_EN,
					    CRT_HOTPLUG_FORCE_DETECT, 1000))
			drm_dbg_kms(&dev_priv->drm,
				    "timed out waiting for FORCE_DETECT to go off");
	पूर्ण

	stat = पूर्णांकel_de_पढ़ो(dev_priv, PORT_HOTPLUG_STAT);
	अगर ((stat & CRT_HOTPLUG_MONITOR_MASK) != CRT_HOTPLUG_MONITOR_NONE)
		ret = true;

	/* clear the पूर्णांकerrupt we just generated, अगर any */
	पूर्णांकel_de_ग_लिखो(dev_priv, PORT_HOTPLUG_STAT, CRT_HOTPLUG_INT_STATUS);

	i915_hotplug_पूर्णांकerrupt_update(dev_priv, CRT_HOTPLUG_FORCE_DETECT, 0);

	वापस ret;
पूर्ण

अटल काष्ठा edid *पूर्णांकel_crt_get_edid(काष्ठा drm_connector *connector,
				काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा edid *edid;

	edid = drm_get_edid(connector, i2c);

	अगर (!edid && !पूर्णांकel_gmbus_is_क्रमced_bit(i2c)) अणु
		drm_dbg_kms(connector->dev,
			    "CRT GMBUS EDID read failed, retry using GPIO bit-banging\n");
		पूर्णांकel_gmbus_क्रमce_bit(i2c, true);
		edid = drm_get_edid(connector, i2c);
		पूर्णांकel_gmbus_क्रमce_bit(i2c, false);
	पूर्ण

	वापस edid;
पूर्ण

/* local version of पूर्णांकel_ddc_get_modes() to use पूर्णांकel_crt_get_edid() */
अटल पूर्णांक पूर्णांकel_crt_ddc_get_modes(काष्ठा drm_connector *connector,
				काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा edid *edid;
	पूर्णांक ret;

	edid = पूर्णांकel_crt_get_edid(connector, adapter);
	अगर (!edid)
		वापस 0;

	ret = पूर्णांकel_connector_update_modes(connector, edid);
	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल bool पूर्णांकel_crt_detect_ddc(काष्ठा drm_connector *connector)
अणु
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_attached_crt(to_पूर्णांकel_connector(connector));
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crt->base.base.dev);
	काष्ठा edid *edid;
	काष्ठा i2c_adapter *i2c;
	bool ret = false;

	BUG_ON(crt->base.type != INTEL_OUTPUT_ANALOG);

	i2c = पूर्णांकel_gmbus_get_adapter(dev_priv, dev_priv->vbt.crt_ddc_pin);
	edid = पूर्णांकel_crt_get_edid(connector, i2c);

	अगर (edid) अणु
		bool is_digital = edid->input & DRM_EDID_INPUT_DIGITAL;

		/*
		 * This may be a DVI-I connector with a shared DDC
		 * link between analog and digital outमाला_दो, so we
		 * have to check the EDID input spec of the attached device.
		 */
		अगर (!is_digital) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "CRT detected via DDC:0x50 [EDID]\n");
			ret = true;
		पूर्ण अन्यथा अणु
			drm_dbg_kms(&dev_priv->drm,
				    "CRT not detected via DDC:0x50 [EDID reports a digital panel]\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		drm_dbg_kms(&dev_priv->drm,
			    "CRT not detected via DDC:0x50 [no valid EDID found]\n");
	पूर्ण

	kमुक्त(edid);

	वापस ret;
पूर्ण

अटल क्रमागत drm_connector_status
पूर्णांकel_crt_load_detect(काष्ठा पूर्णांकel_crt *crt, u32 pipe)
अणु
	काष्ठा drm_device *dev = crt->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_uncore *uncore = &dev_priv->uncore;
	u32 save_bclrpat;
	u32 save_vtotal;
	u32 vtotal, vactive;
	u32 vsample;
	u32 vblank, vblank_start, vblank_end;
	u32 dsl;
	i915_reg_t bclrpat_reg, vtotal_reg,
		vblank_reg, vsync_reg, pipeconf_reg, pipe_dsl_reg;
	u8 st00;
	क्रमागत drm_connector_status status;

	drm_dbg_kms(&dev_priv->drm, "starting load-detect on CRT\n");

	bclrpat_reg = BCLRPAT(pipe);
	vtotal_reg = VTOTAL(pipe);
	vblank_reg = VBLANK(pipe);
	vsync_reg = VSYNC(pipe);
	pipeconf_reg = PIPECONF(pipe);
	pipe_dsl_reg = PIPEDSL(pipe);

	save_bclrpat = पूर्णांकel_uncore_पढ़ो(uncore, bclrpat_reg);
	save_vtotal = पूर्णांकel_uncore_पढ़ो(uncore, vtotal_reg);
	vblank = पूर्णांकel_uncore_पढ़ो(uncore, vblank_reg);

	vtotal = ((save_vtotal >> 16) & 0xfff) + 1;
	vactive = (save_vtotal & 0x7ff) + 1;

	vblank_start = (vblank & 0xfff) + 1;
	vblank_end = ((vblank >> 16) & 0xfff) + 1;

	/* Set the border color to purple. */
	पूर्णांकel_uncore_ग_लिखो(uncore, bclrpat_reg, 0x500050);

	अगर (!IS_DISPLAY_VER(dev_priv, 2)) अणु
		u32 pipeconf = पूर्णांकel_uncore_पढ़ो(uncore, pipeconf_reg);
		पूर्णांकel_uncore_ग_लिखो(uncore,
				   pipeconf_reg,
				   pipeconf | PIPECONF_FORCE_BORDER);
		पूर्णांकel_uncore_posting_पढ़ो(uncore, pipeconf_reg);
		/* Wait क्रम next Vblank to substitue
		 * border color क्रम Color info */
		पूर्णांकel_रुको_क्रम_vblank(dev_priv, pipe);
		st00 = पूर्णांकel_uncore_पढ़ो8(uncore, _VGA_MSR_WRITE);
		status = ((st00 & (1 << 4)) != 0) ?
			connector_status_connected :
			connector_status_disconnected;

		पूर्णांकel_uncore_ग_लिखो(uncore, pipeconf_reg, pipeconf);
	पूर्ण अन्यथा अणु
		bool restore_vblank = false;
		पूर्णांक count, detect;

		/*
		* If there isn't any border, add some.
		* Yes, this will flicker
		*/
		अगर (vblank_start <= vactive && vblank_end >= vtotal) अणु
			u32 vsync = पूर्णांकel_de_पढ़ो(dev_priv, vsync_reg);
			u32 vsync_start = (vsync & 0xffff) + 1;

			vblank_start = vsync_start;
			पूर्णांकel_uncore_ग_लिखो(uncore,
					   vblank_reg,
					   (vblank_start - 1) |
					   ((vblank_end - 1) << 16));
			restore_vblank = true;
		पूर्ण
		/* sample in the vertical border, selecting the larger one */
		अगर (vblank_start - vactive >= vtotal - vblank_end)
			vsample = (vblank_start + vactive) >> 1;
		अन्यथा
			vsample = (vtotal + vblank_end) >> 1;

		/*
		 * Wait क्रम the border to be displayed
		 */
		जबतक (पूर्णांकel_uncore_पढ़ो(uncore, pipe_dsl_reg) >= vactive)
			;
		जबतक ((dsl = पूर्णांकel_uncore_पढ़ो(uncore, pipe_dsl_reg)) <=
		       vsample)
			;
		/*
		 * Watch ST00 क्रम an entire scanline
		 */
		detect = 0;
		count = 0;
		करो अणु
			count++;
			/* Read the ST00 VGA status रेजिस्टर */
			st00 = पूर्णांकel_uncore_पढ़ो8(uncore, _VGA_MSR_WRITE);
			अगर (st00 & (1 << 4))
				detect++;
		पूर्ण जबतक ((पूर्णांकel_uncore_पढ़ो(uncore, pipe_dsl_reg) == dsl));

		/* restore vblank अगर necessary */
		अगर (restore_vblank)
			पूर्णांकel_uncore_ग_लिखो(uncore, vblank_reg, vblank);
		/*
		 * If more than 3/4 of the scanline detected a monitor,
		 * then it is assumed to be present. This works even on i830,
		 * where there isn't any way to क्रमce the border color across
		 * the screen
		 */
		status = detect * 4 > count * 3 ?
			 connector_status_connected :
			 connector_status_disconnected;
	पूर्ण

	/* Restore previous settings */
	पूर्णांकel_uncore_ग_लिखो(uncore, bclrpat_reg, save_bclrpat);

	वापस status;
पूर्ण

अटल पूर्णांक पूर्णांकel_spurious_crt_detect_dmi_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	DRM_DEBUG_DRIVER("Skipping CRT detection for %s\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id पूर्णांकel_spurious_crt_detect[] = अणु
	अणु
		.callback = पूर्णांकel_spurious_crt_detect_dmi_callback,
		.ident = "ACER ZGB",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ACER"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ZGB"),
		पूर्ण,
	पूर्ण,
	अणु
		.callback = पूर्णांकel_spurious_crt_detect_dmi_callback,
		.ident = "Intel DZ77BH-55K",
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "Intel Corporation"),
			DMI_MATCH(DMI_BOARD_NAME, "DZ77BH-55K"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक
पूर्णांकel_crt_detect(काष्ठा drm_connector *connector,
		 काष्ठा drm_modeset_acquire_ctx *ctx,
		 bool क्रमce)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_attached_crt(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = &crt->base;
	पूर्णांकel_wakeref_t wakeref;
	पूर्णांक status, ret;
	काष्ठा पूर्णांकel_load_detect_pipe पंचांगp;

	drm_dbg_kms(&dev_priv->drm, "[CONNECTOR:%d:%s] force=%d\n",
		    connector->base.id, connector->name,
		    क्रमce);

	अगर (!INTEL_DISPLAY_ENABLED(dev_priv))
		वापस connector_status_disconnected;

	अगर (dev_priv->params.load_detect_test) अणु
		wakeref = पूर्णांकel_display_घातer_get(dev_priv,
						  पूर्णांकel_encoder->घातer_करोमुख्य);
		जाओ load_detect;
	पूर्ण

	/* Skip machines without VGA that falsely report hotplug events */
	अगर (dmi_check_प्रणाली(पूर्णांकel_spurious_crt_detect))
		वापस connector_status_disconnected;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv,
					  पूर्णांकel_encoder->घातer_करोमुख्य);

	अगर (I915_HAS_HOTPLUG(dev_priv)) अणु
		/* We can not rely on the HPD pin always being correctly wired
		 * up, क्रम example many KVM करो not pass it through, and so
		 * only trust an निश्चितion that the monitor is connected.
		 */
		अगर (पूर्णांकel_crt_detect_hotplug(connector)) अणु
			drm_dbg_kms(&dev_priv->drm,
				    "CRT detected via hotplug\n");
			status = connector_status_connected;
			जाओ out;
		पूर्ण अन्यथा
			drm_dbg_kms(&dev_priv->drm,
				    "CRT not detected via hotplug\n");
	पूर्ण

	अगर (पूर्णांकel_crt_detect_ddc(connector)) अणु
		status = connector_status_connected;
		जाओ out;
	पूर्ण

	/* Load detection is broken on HPD capable machines. Whoever wants a
	 * broken monitor (without edid) to work behind a broken kvm (that fails
	 * to have the right resistors क्रम HP detection) needs to fix this up.
	 * For now just bail out. */
	अगर (I915_HAS_HOTPLUG(dev_priv)) अणु
		status = connector_status_disconnected;
		जाओ out;
	पूर्ण

load_detect:
	अगर (!क्रमce) अणु
		status = connector->status;
		जाओ out;
	पूर्ण

	/* क्रम pre-945g platक्रमms use load detect */
	ret = पूर्णांकel_get_load_detect_pipe(connector, &पंचांगp, ctx);
	अगर (ret > 0) अणु
		अगर (पूर्णांकel_crt_detect_ddc(connector))
			status = connector_status_connected;
		अन्यथा अगर (DISPLAY_VER(dev_priv) < 4)
			status = पूर्णांकel_crt_load_detect(crt,
				to_पूर्णांकel_crtc(connector->state->crtc)->pipe);
		अन्यथा अगर (dev_priv->params.load_detect_test)
			status = connector_status_disconnected;
		अन्यथा
			status = connector_status_unknown;
		पूर्णांकel_release_load_detect_pipe(connector, &पंचांगp, ctx);
	पूर्ण अन्यथा अगर (ret == 0) अणु
		status = connector_status_unknown;
	पूर्ण अन्यथा अणु
		status = ret;
	पूर्ण

out:
	पूर्णांकel_display_घातer_put(dev_priv, पूर्णांकel_encoder->घातer_करोमुख्य, wakeref);

	/*
	 * Make sure the refs क्रम घातer wells enabled during detect are
	 * dropped to aव्योम a new detect cycle triggered by HPD polling.
	 */
	पूर्णांकel_display_घातer_flush_work(dev_priv);

	वापस status;
पूर्ण

अटल पूर्णांक पूर्णांकel_crt_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_attached_crt(to_पूर्णांकel_connector(connector));
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder = &crt->base;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा i2c_adapter *i2c;
	पूर्णांक ret;

	wakeref = पूर्णांकel_display_घातer_get(dev_priv,
					  पूर्णांकel_encoder->घातer_करोमुख्य);

	i2c = पूर्णांकel_gmbus_get_adapter(dev_priv, dev_priv->vbt.crt_ddc_pin);
	ret = पूर्णांकel_crt_ddc_get_modes(connector, i2c);
	अगर (ret || !IS_G4X(dev_priv))
		जाओ out;

	/* Try to probe digital port क्रम output in DVI-I -> VGA mode. */
	i2c = पूर्णांकel_gmbus_get_adapter(dev_priv, GMBUS_PIN_DPB);
	ret = पूर्णांकel_crt_ddc_get_modes(connector, i2c);

out:
	पूर्णांकel_display_घातer_put(dev_priv, पूर्णांकel_encoder->घातer_करोमुख्य, wakeref);

	वापस ret;
पूर्ण

व्योम पूर्णांकel_crt_reset(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->dev);
	काष्ठा पूर्णांकel_crt *crt = पूर्णांकel_encoder_to_crt(to_पूर्णांकel_encoder(encoder));

	अगर (DISPLAY_VER(dev_priv) >= 5) अणु
		u32 adpa;

		adpa = पूर्णांकel_de_पढ़ो(dev_priv, crt->adpa_reg);
		adpa &= ~ADPA_CRT_HOTPLUG_MASK;
		adpa |= ADPA_HOTPLUG_BITS;
		पूर्णांकel_de_ग_लिखो(dev_priv, crt->adpa_reg, adpa);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, crt->adpa_reg);

		drm_dbg_kms(&dev_priv->drm, "crt adpa set to 0x%x\n", adpa);
		crt->क्रमce_hotplug_required = true;
	पूर्ण

पूर्ण

/*
 * Routines क्रम controlling stuff on the analog port
 */

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_crt_connector_funcs = अणु
	.fill_modes = drm_helper_probe_single_connector_modes,
	.late_रेजिस्टर = पूर्णांकel_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_crt_connector_helper_funcs = अणु
	.detect_ctx = पूर्णांकel_crt_detect,
	.mode_valid = पूर्णांकel_crt_mode_valid,
	.get_modes = पूर्णांकel_crt_get_modes,
पूर्ण;

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_crt_enc_funcs = अणु
	.reset = पूर्णांकel_crt_reset,
	.destroy = पूर्णांकel_encoder_destroy,
पूर्ण;

व्योम पूर्णांकel_crt_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_connector *connector;
	काष्ठा पूर्णांकel_crt *crt;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	i915_reg_t adpa_reg;
	u32 adpa;

	अगर (HAS_PCH_SPLIT(dev_priv))
		adpa_reg = PCH_ADPA;
	अन्यथा अगर (IS_VALLEYVIEW(dev_priv))
		adpa_reg = VLV_ADPA;
	अन्यथा
		adpa_reg = ADPA;

	adpa = पूर्णांकel_de_पढ़ो(dev_priv, adpa_reg);
	अगर ((adpa & ADPA_DAC_ENABLE) == 0) अणु
		/*
		 * On some machines (some IVB at least) CRT can be
		 * fused off, but there's no known fuse bit to
		 * indicate that. On these machine the ADPA रेजिस्टर
		 * works normally, except the DAC enable bit won't
		 * take. So the only way to tell is attempt to enable
		 * it and see what happens.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, adpa_reg,
			       adpa | ADPA_DAC_ENABLE | ADPA_HSYNC_CNTL_DISABLE | ADPA_VSYNC_CNTL_DISABLE);
		अगर ((पूर्णांकel_de_पढ़ो(dev_priv, adpa_reg) & ADPA_DAC_ENABLE) == 0)
			वापस;
		पूर्णांकel_de_ग_लिखो(dev_priv, adpa_reg, adpa);
	पूर्ण

	crt = kzalloc(माप(काष्ठा पूर्णांकel_crt), GFP_KERNEL);
	अगर (!crt)
		वापस;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector) अणु
		kमुक्त(crt);
		वापस;
	पूर्ण

	connector = &पूर्णांकel_connector->base;
	crt->connector = पूर्णांकel_connector;
	drm_connector_init(&dev_priv->drm, &पूर्णांकel_connector->base,
			   &पूर्णांकel_crt_connector_funcs, DRM_MODE_CONNECTOR_VGA);

	drm_encoder_init(&dev_priv->drm, &crt->base.base, &पूर्णांकel_crt_enc_funcs,
			 DRM_MODE_ENCODER_DAC, "CRT");

	पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, &crt->base);

	crt->base.type = INTEL_OUTPUT_ANALOG;
	crt->base.cloneable = (1 << INTEL_OUTPUT_DVO) | (1 << INTEL_OUTPUT_HDMI);
	अगर (IS_I830(dev_priv))
		crt->base.pipe_mask = BIT(PIPE_A);
	अन्यथा
		crt->base.pipe_mask = ~0;

	अगर (IS_DISPLAY_VER(dev_priv, 2))
		connector->पूर्णांकerlace_allowed = 0;
	अन्यथा
		connector->पूर्णांकerlace_allowed = 1;
	connector->द्विगुनscan_allowed = 0;

	crt->adpa_reg = adpa_reg;

	crt->base.घातer_करोमुख्य = POWER_DOMAIN_PORT_CRT;

	अगर (I915_HAS_HOTPLUG(dev_priv) &&
	    !dmi_check_प्रणाली(पूर्णांकel_spurious_crt_detect)) अणु
		crt->base.hpd_pin = HPD_CRT;
		crt->base.hotplug = पूर्णांकel_encoder_hotplug;
		पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_HPD;
	पूर्ण अन्यथा अणु
		पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_CONNECT;
	पूर्ण

	अगर (HAS_DDI(dev_priv)) अणु
		crt->base.port = PORT_E;
		crt->base.get_config = hsw_crt_get_config;
		crt->base.get_hw_state = पूर्णांकel_ddi_get_hw_state;
		crt->base.compute_config = hsw_crt_compute_config;
		crt->base.pre_pll_enable = hsw_pre_pll_enable_crt;
		crt->base.pre_enable = hsw_pre_enable_crt;
		crt->base.enable = hsw_enable_crt;
		crt->base.disable = hsw_disable_crt;
		crt->base.post_disable = hsw_post_disable_crt;
		crt->base.enable_घड़ी = hsw_ddi_enable_घड़ी;
		crt->base.disable_घड़ी = hsw_ddi_disable_घड़ी;
		crt->base.is_घड़ी_enabled = hsw_ddi_is_घड़ी_enabled;
	पूर्ण अन्यथा अणु
		अगर (HAS_PCH_SPLIT(dev_priv)) अणु
			crt->base.compute_config = pch_crt_compute_config;
			crt->base.disable = pch_disable_crt;
			crt->base.post_disable = pch_post_disable_crt;
		पूर्ण अन्यथा अणु
			crt->base.compute_config = पूर्णांकel_crt_compute_config;
			crt->base.disable = पूर्णांकel_disable_crt;
		पूर्ण
		crt->base.port = PORT_NONE;
		crt->base.get_config = पूर्णांकel_crt_get_config;
		crt->base.get_hw_state = पूर्णांकel_crt_get_hw_state;
		crt->base.enable = पूर्णांकel_enable_crt;
	पूर्ण
	पूर्णांकel_connector->get_hw_state = पूर्णांकel_connector_get_hw_state;

	drm_connector_helper_add(connector, &पूर्णांकel_crt_connector_helper_funcs);

	/*
	 * TODO: find a proper way to discover whether we need to set the the
	 * polarity and link reversal bits or not, instead of relying on the
	 * BIOS.
	 */
	अगर (HAS_PCH_LPT(dev_priv)) अणु
		u32 fdi_config = FDI_RX_POLARITY_REVERSED_LPT |
				 FDI_RX_LINK_REVERSAL_OVERRIDE;

		dev_priv->fdi_rx_config = पूर्णांकel_de_पढ़ो(dev_priv,
							FDI_RX_CTL(PIPE_A)) & fdi_config;
	पूर्ण

	पूर्णांकel_crt_reset(&crt->base.base);
पूर्ण
