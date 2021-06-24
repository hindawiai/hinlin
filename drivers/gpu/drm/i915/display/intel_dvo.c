<शैली गुरु>
/*
 * Copyright 2006 Dave Airlie <airlied@linux.ie>
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

#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>

#समावेश "i915_drv.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dvo.h"
#समावेश "intel_dvo_dev.h"
#समावेश "intel_gmbus.h"
#समावेश "intel_panel.h"

#घोषणा INTEL_DVO_CHIP_NONE	0
#घोषणा INTEL_DVO_CHIP_LVDS	1
#घोषणा INTEL_DVO_CHIP_TMDS	2
#घोषणा INTEL_DVO_CHIP_TVOUT	4
#घोषणा INTEL_DVO_CHIP_LVDS_NO_FIXED	5

#घोषणा SIL164_ADDR	0x38
#घोषणा CH7xxx_ADDR	0x76
#घोषणा TFP410_ADDR	0x38
#घोषणा NS2501_ADDR     0x38

अटल स्थिर काष्ठा पूर्णांकel_dvo_device पूर्णांकel_dvo_devices[] = अणु
	अणु
		.type = INTEL_DVO_CHIP_TMDS,
		.name = "sil164",
		.dvo_reg = DVOC,
		.dvo_srcdim_reg = DVOC_SRCDIM,
		.slave_addr = SIL164_ADDR,
		.dev_ops = &sil164_ops,
	पूर्ण,
	अणु
		.type = INTEL_DVO_CHIP_TMDS,
		.name = "ch7xxx",
		.dvo_reg = DVOC,
		.dvo_srcdim_reg = DVOC_SRCDIM,
		.slave_addr = CH7xxx_ADDR,
		.dev_ops = &ch7xxx_ops,
	पूर्ण,
	अणु
		.type = INTEL_DVO_CHIP_TMDS,
		.name = "ch7xxx",
		.dvo_reg = DVOC,
		.dvo_srcdim_reg = DVOC_SRCDIM,
		.slave_addr = 0x75, /* For some ch7010 */
		.dev_ops = &ch7xxx_ops,
	पूर्ण,
	अणु
		.type = INTEL_DVO_CHIP_LVDS,
		.name = "ivch",
		.dvo_reg = DVOA,
		.dvo_srcdim_reg = DVOA_SRCDIM,
		.slave_addr = 0x02, /* Might also be 0x44, 0x84, 0xc4 */
		.dev_ops = &ivch_ops,
	पूर्ण,
	अणु
		.type = INTEL_DVO_CHIP_TMDS,
		.name = "tfp410",
		.dvo_reg = DVOC,
		.dvo_srcdim_reg = DVOC_SRCDIM,
		.slave_addr = TFP410_ADDR,
		.dev_ops = &tfp410_ops,
	पूर्ण,
	अणु
		.type = INTEL_DVO_CHIP_LVDS,
		.name = "ch7017",
		.dvo_reg = DVOC,
		.dvo_srcdim_reg = DVOC_SRCDIM,
		.slave_addr = 0x75,
		.gpio = GMBUS_PIN_DPB,
		.dev_ops = &ch7017_ops,
	पूर्ण,
	अणु
		.type = INTEL_DVO_CHIP_LVDS_NO_FIXED,
		.name = "ns2501",
		.dvo_reg = DVOB,
		.dvo_srcdim_reg = DVOB_SRCDIM,
		.slave_addr = NS2501_ADDR,
		.dev_ops = &ns2501_ops,
	पूर्ण,
पूर्ण;

काष्ठा पूर्णांकel_dvo अणु
	काष्ठा पूर्णांकel_encoder base;

	काष्ठा पूर्णांकel_dvo_device dev;

	काष्ठा पूर्णांकel_connector *attached_connector;

	bool panel_wants_dither;
पूर्ण;

अटल काष्ठा पूर्णांकel_dvo *enc_to_dvo(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा पूर्णांकel_dvo, base);
पूर्ण

अटल काष्ठा पूर्णांकel_dvo *पूर्णांकel_attached_dvo(काष्ठा पूर्णांकel_connector *connector)
अणु
	वापस enc_to_dvo(पूर्णांकel_attached_encoder(connector));
पूर्ण

अटल bool पूर्णांकel_dvo_connector_get_hw_state(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_device *dev = connector->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = पूर्णांकel_attached_dvo(connector);
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dvo->dev.dvo_reg);

	अगर (!(पंचांगp & DVO_ENABLE))
		वापस false;

	वापस पूर्णांकel_dvo->dev.dev_ops->get_hw_state(&पूर्णांकel_dvo->dev);
पूर्ण

अटल bool पूर्णांकel_dvo_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				   क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = enc_to_dvo(encoder);
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dvo->dev.dvo_reg);

	*pipe = (पंचांगp & DVO_PIPE_SEL_MASK) >> DVO_PIPE_SEL_SHIFT;

	वापस पंचांगp & DVO_ENABLE;
पूर्ण

अटल व्योम पूर्णांकel_dvo_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = enc_to_dvo(encoder);
	u32 पंचांगp, flags = 0;

	pipe_config->output_types |= BIT(INTEL_OUTPUT_DVO);

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, पूर्णांकel_dvo->dev.dvo_reg);
	अगर (पंचांगp & DVO_HSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PHSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NHSYNC;
	अगर (पंचांगp & DVO_VSYNC_ACTIVE_HIGH)
		flags |= DRM_MODE_FLAG_PVSYNC;
	अन्यथा
		flags |= DRM_MODE_FLAG_NVSYNC;

	pipe_config->hw.adjusted_mode.flags |= flags;

	pipe_config->hw.adjusted_mode.crtc_घड़ी = pipe_config->port_घड़ी;
पूर्ण

अटल व्योम पूर्णांकel_disable_dvo(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = enc_to_dvo(encoder);
	i915_reg_t dvo_reg = पूर्णांकel_dvo->dev.dvo_reg;
	u32 temp = पूर्णांकel_de_पढ़ो(dev_priv, dvo_reg);

	पूर्णांकel_dvo->dev.dev_ops->dpms(&पूर्णांकel_dvo->dev, false);
	पूर्णांकel_de_ग_लिखो(dev_priv, dvo_reg, temp & ~DVO_ENABLE);
	पूर्णांकel_de_पढ़ो(dev_priv, dvo_reg);
पूर्ण

अटल व्योम पूर्णांकel_enable_dvo(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
			     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = enc_to_dvo(encoder);
	i915_reg_t dvo_reg = पूर्णांकel_dvo->dev.dvo_reg;
	u32 temp = पूर्णांकel_de_पढ़ो(dev_priv, dvo_reg);

	पूर्णांकel_dvo->dev.dev_ops->mode_set(&पूर्णांकel_dvo->dev,
					 &pipe_config->hw.mode,
					 &pipe_config->hw.adjusted_mode);

	पूर्णांकel_de_ग_लिखो(dev_priv, dvo_reg, temp | DVO_ENABLE);
	पूर्णांकel_de_पढ़ो(dev_priv, dvo_reg);

	पूर्णांकel_dvo->dev.dev_ops->dpms(&पूर्णांकel_dvo->dev, true);
पूर्ण

अटल क्रमागत drm_mode_status
पूर्णांकel_dvo_mode_valid(काष्ठा drm_connector *connector,
		     काष्ठा drm_display_mode *mode)
अणु
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = पूर्णांकel_attached_dvo(to_पूर्णांकel_connector(connector));
	स्थिर काष्ठा drm_display_mode *fixed_mode =
		to_पूर्णांकel_connector(connector)->panel.fixed_mode;
	पूर्णांक max_करोtclk = to_i915(connector->dev)->max_करोtclk_freq;
	पूर्णांक target_घड़ी = mode->घड़ी;

	अगर (mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस MODE_NO_DBLESCAN;

	/* XXX: Validate घड़ी range */

	अगर (fixed_mode) अणु
		अगर (mode->hdisplay > fixed_mode->hdisplay)
			वापस MODE_PANEL;
		अगर (mode->vdisplay > fixed_mode->vdisplay)
			वापस MODE_PANEL;

		target_घड़ी = fixed_mode->घड़ी;
	पूर्ण

	अगर (target_घड़ी > max_करोtclk)
		वापस MODE_CLOCK_HIGH;

	वापस पूर्णांकel_dvo->dev.dev_ops->mode_valid(&पूर्णांकel_dvo->dev, mode);
पूर्ण

अटल पूर्णांक पूर्णांकel_dvo_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = enc_to_dvo(encoder);
	स्थिर काष्ठा drm_display_mode *fixed_mode =
		पूर्णांकel_dvo->attached_connector->panel.fixed_mode;
	काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;

	/*
	 * If we have timings from the BIOS क्रम the panel, put them in
	 * to the adjusted mode.  The CRTC will be set up क्रम this mode,
	 * with the panel scaling set up to source from the H/VDisplay
	 * of the original mode.
	 */
	अगर (fixed_mode)
		पूर्णांकel_fixed_panel_mode(fixed_mode, adjusted_mode);

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_dvo_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = enc_to_dvo(encoder);
	क्रमागत pipe pipe = crtc->pipe;
	u32 dvo_val;
	i915_reg_t dvo_reg = पूर्णांकel_dvo->dev.dvo_reg;
	i915_reg_t dvo_srcdim_reg = पूर्णांकel_dvo->dev.dvo_srcdim_reg;

	/* Save the data order, since I करोn't know what it should be set to. */
	dvo_val = पूर्णांकel_de_पढ़ो(dev_priv, dvo_reg) &
		  (DVO_PRESERVE_MASK | DVO_DATA_ORDER_GBRG);
	dvo_val |= DVO_DATA_ORDER_FP | DVO_BORDER_ENABLE |
		   DVO_BLANK_ACTIVE_HIGH;

	dvo_val |= DVO_PIPE_SEL(pipe);
	dvo_val |= DVO_PIPE_STALL;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PHSYNC)
		dvo_val |= DVO_HSYNC_ACTIVE_HIGH;
	अगर (adjusted_mode->flags & DRM_MODE_FLAG_PVSYNC)
		dvo_val |= DVO_VSYNC_ACTIVE_HIGH;

	पूर्णांकel_de_ग_लिखो(dev_priv, dvo_srcdim_reg,
		       (adjusted_mode->crtc_hdisplay << DVO_SRCDIM_HORIZONTAL_SHIFT) | (adjusted_mode->crtc_vdisplay << DVO_SRCDIM_VERTICAL_SHIFT));
	पूर्णांकel_de_ग_लिखो(dev_priv, dvo_reg, dvo_val);
पूर्ण

अटल क्रमागत drm_connector_status
पूर्णांकel_dvo_detect(काष्ठा drm_connector *connector, bool क्रमce)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(connector->dev);
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = पूर्णांकel_attached_dvo(to_पूर्णांकel_connector(connector));

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);

	अगर (!INTEL_DISPLAY_ENABLED(i915))
		वापस connector_status_disconnected;

	वापस पूर्णांकel_dvo->dev.dev_ops->detect(&पूर्णांकel_dvo->dev);
पूर्ण

अटल पूर्णांक पूर्णांकel_dvo_get_modes(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->dev);
	स्थिर काष्ठा drm_display_mode *fixed_mode =
		to_पूर्णांकel_connector(connector)->panel.fixed_mode;
	पूर्णांक num_modes;

	/*
	 * We should probably have an i2c driver get_modes function क्रम those
	 * devices which will have a fixed set of modes determined by the chip
	 * (TV-out, क्रम example), but क्रम now with just TMDS and LVDS,
	 * that's not the हाल.
	 */
	num_modes = पूर्णांकel_ddc_get_modes(connector,
					पूर्णांकel_gmbus_get_adapter(dev_priv, GMBUS_PIN_DPC));
	अगर (num_modes)
		वापस num_modes;

	अगर (fixed_mode) अणु
		काष्ठा drm_display_mode *mode;

		mode = drm_mode_duplicate(connector->dev, fixed_mode);
		अगर (mode) अणु
			drm_mode_probed_add(connector, mode);
			num_modes++;
		पूर्ण
	पूर्ण

	वापस num_modes;
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_dvo_connector_funcs = अणु
	.detect = पूर्णांकel_dvo_detect,
	.late_रेजिस्टर = पूर्णांकel_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = drm_atomic_helper_connector_duplicate_state,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_dvo_connector_helper_funcs = अणु
	.mode_valid = पूर्णांकel_dvo_mode_valid,
	.get_modes = पूर्णांकel_dvo_get_modes,
पूर्ण;

अटल व्योम पूर्णांकel_dvo_enc_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo = enc_to_dvo(to_पूर्णांकel_encoder(encoder));

	अगर (पूर्णांकel_dvo->dev.dev_ops->destroy)
		पूर्णांकel_dvo->dev.dev_ops->destroy(&पूर्णांकel_dvo->dev);

	पूर्णांकel_encoder_destroy(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_dvo_enc_funcs = अणु
	.destroy = पूर्णांकel_dvo_enc_destroy,
पूर्ण;

/*
 * Attempts to get a fixed panel timing क्रम LVDS (currently only the i830).
 *
 * Other chips with DVO LVDS will need to extend this to deal with the LVDS
 * chip being on DVOB/C and having multiple pipes.
 */
अटल काष्ठा drm_display_mode *
पूर्णांकel_dvo_get_current_mode(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_display_mode *mode;

	mode = पूर्णांकel_encoder_current_mode(encoder);
	अगर (mode) अणु
		DRM_DEBUG_KMS("using current (BIOS) mode: ");
		drm_mode_debug_prपूर्णांकmodeline(mode);
		mode->type |= DRM_MODE_TYPE_PREFERRED;
	पूर्ण

	वापस mode;
पूर्ण

अटल क्रमागत port पूर्णांकel_dvo_port(i915_reg_t dvo_reg)
अणु
	अगर (i915_mmio_reg_equal(dvo_reg, DVOA))
		वापस PORT_A;
	अन्यथा अगर (i915_mmio_reg_equal(dvo_reg, DVOB))
		वापस PORT_B;
	अन्यथा
		वापस PORT_C;
पूर्ण

व्योम पूर्णांकel_dvo_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा पूर्णांकel_dvo *पूर्णांकel_dvo;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	पूर्णांक i;
	पूर्णांक encoder_type = DRM_MODE_ENCODER_NONE;

	पूर्णांकel_dvo = kzalloc(माप(*पूर्णांकel_dvo), GFP_KERNEL);
	अगर (!पूर्णांकel_dvo)
		वापस;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector) अणु
		kमुक्त(पूर्णांकel_dvo);
		वापस;
	पूर्ण

	पूर्णांकel_dvo->attached_connector = पूर्णांकel_connector;

	पूर्णांकel_encoder = &पूर्णांकel_dvo->base;

	पूर्णांकel_encoder->disable = पूर्णांकel_disable_dvo;
	पूर्णांकel_encoder->enable = पूर्णांकel_enable_dvo;
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_dvo_get_hw_state;
	पूर्णांकel_encoder->get_config = पूर्णांकel_dvo_get_config;
	पूर्णांकel_encoder->compute_config = पूर्णांकel_dvo_compute_config;
	पूर्णांकel_encoder->pre_enable = पूर्णांकel_dvo_pre_enable;
	पूर्णांकel_connector->get_hw_state = पूर्णांकel_dvo_connector_get_hw_state;

	/* Now, try to find a controller */
	क्रम (i = 0; i < ARRAY_SIZE(पूर्णांकel_dvo_devices); i++) अणु
		काष्ठा drm_connector *connector = &पूर्णांकel_connector->base;
		स्थिर काष्ठा पूर्णांकel_dvo_device *dvo = &पूर्णांकel_dvo_devices[i];
		काष्ठा i2c_adapter *i2c;
		पूर्णांक gpio;
		bool dvoinit;
		क्रमागत pipe pipe;
		u32 dpll[I915_MAX_PIPES];
		क्रमागत port port;

		/*
		 * Allow the I2C driver info to specअगरy the GPIO to be used in
		 * special हालs, but otherwise शेष to what's defined
		 * in the spec.
		 */
		अगर (पूर्णांकel_gmbus_is_valid_pin(dev_priv, dvo->gpio))
			gpio = dvo->gpio;
		अन्यथा अगर (dvo->type == INTEL_DVO_CHIP_LVDS)
			gpio = GMBUS_PIN_SSC;
		अन्यथा
			gpio = GMBUS_PIN_DPB;

		/*
		 * Set up the I2C bus necessary क्रम the chip we're probing.
		 * It appears that everything is on GPIOE except क्रम panels
		 * on i830 laptops, which are on GPIOB (DVOA).
		 */
		i2c = पूर्णांकel_gmbus_get_adapter(dev_priv, gpio);

		पूर्णांकel_dvo->dev = *dvo;

		/*
		 * GMBUS NAK handling seems to be unstable, hence let the
		 * transmitter detection run in bit banging mode क्रम now.
		 */
		पूर्णांकel_gmbus_क्रमce_bit(i2c, true);

		/*
		 * ns2501 requires the DVO 2x घड़ी beक्रमe it will
		 * respond to i2c accesses, so make sure we have
		 * have the घड़ी enabled beक्रमe we attempt to
		 * initialize the device.
		 */
		क्रम_each_pipe(dev_priv, pipe) अणु
			dpll[pipe] = पूर्णांकel_de_पढ़ो(dev_priv, DPLL(pipe));
			पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe),
				       dpll[pipe] | DPLL_DVO_2X_MODE);
		पूर्ण

		dvoinit = dvo->dev_ops->init(&पूर्णांकel_dvo->dev, i2c);

		/* restore the DVO 2x घड़ी state to original */
		क्रम_each_pipe(dev_priv, pipe) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, DPLL(pipe), dpll[pipe]);
		पूर्ण

		पूर्णांकel_gmbus_क्रमce_bit(i2c, false);

		अगर (!dvoinit)
			जारी;

		port = पूर्णांकel_dvo_port(dvo->dvo_reg);
		drm_encoder_init(&dev_priv->drm, &पूर्णांकel_encoder->base,
				 &पूर्णांकel_dvo_enc_funcs, encoder_type,
				 "DVO %c", port_name(port));

		पूर्णांकel_encoder->type = INTEL_OUTPUT_DVO;
		पूर्णांकel_encoder->घातer_करोमुख्य = POWER_DOMAIN_PORT_OTHER;
		पूर्णांकel_encoder->port = port;
		पूर्णांकel_encoder->pipe_mask = ~0;

		अगर (dvo->type != INTEL_DVO_CHIP_LVDS)
			पूर्णांकel_encoder->cloneable = (1 << INTEL_OUTPUT_ANALOG) |
				(1 << INTEL_OUTPUT_DVO);

		चयन (dvo->type) अणु
		हाल INTEL_DVO_CHIP_TMDS:
			पूर्णांकel_connector->polled = DRM_CONNECTOR_POLL_CONNECT |
				DRM_CONNECTOR_POLL_DISCONNECT;
			drm_connector_init(&dev_priv->drm, connector,
					   &पूर्णांकel_dvo_connector_funcs,
					   DRM_MODE_CONNECTOR_DVII);
			encoder_type = DRM_MODE_ENCODER_TMDS;
			अवरोध;
		हाल INTEL_DVO_CHIP_LVDS_NO_FIXED:
		हाल INTEL_DVO_CHIP_LVDS:
			drm_connector_init(&dev_priv->drm, connector,
					   &पूर्णांकel_dvo_connector_funcs,
					   DRM_MODE_CONNECTOR_LVDS);
			encoder_type = DRM_MODE_ENCODER_LVDS;
			अवरोध;
		पूर्ण

		drm_connector_helper_add(connector,
					 &पूर्णांकel_dvo_connector_helper_funcs);
		connector->display_info.subpixel_order = SubPixelHorizontalRGB;
		connector->पूर्णांकerlace_allowed = false;
		connector->द्विगुनscan_allowed = false;

		पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, पूर्णांकel_encoder);
		अगर (dvo->type == INTEL_DVO_CHIP_LVDS) अणु
			/*
			 * For our LVDS chipsets, we should hopefully be able
			 * to dig the fixed panel mode out of the BIOS data.
			 * However, it's in a dअगरferent क्रमmat from the BIOS
			 * data on chipsets with पूर्णांकegrated LVDS (stored in AIM
			 * headers, likely), so क्रम now, just get the current
			 * mode being output through DVO.
			 */
			पूर्णांकel_panel_init(&पूर्णांकel_connector->panel,
					 पूर्णांकel_dvo_get_current_mode(पूर्णांकel_encoder),
					 शून्य);
			पूर्णांकel_dvo->panel_wants_dither = true;
		पूर्ण

		वापस;
	पूर्ण

	kमुक्त(पूर्णांकel_dvo);
	kमुक्त(पूर्णांकel_connector);
पूर्ण
