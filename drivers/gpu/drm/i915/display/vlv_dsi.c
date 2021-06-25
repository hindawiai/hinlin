<शैली गुरु>
/*
 * Copyright तऊ 2013 Intel Corporation
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
 * Author: Jani Nikula <jani.nikula@पूर्णांकel.com>
 */

#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_mipi_dsi.h>

#समावेश "i915_drv.h"
#समावेश "intel_atomic.h"
#समावेश "intel_connector.h"
#समावेश "intel_display_types.h"
#समावेश "intel_dsi.h"
#समावेश "intel_fifo_underrun.h"
#समावेश "intel_panel.h"
#समावेश "intel_sideband.h"
#समावेश "skl_scaler.h"

/* वापस pixels in terms of txbyteclkhs */
अटल u16 txbyteclkhs(u16 pixels, पूर्णांक bpp, पूर्णांक lane_count,
		       u16 burst_mode_ratio)
अणु
	वापस DIV_ROUND_UP(DIV_ROUND_UP(pixels * bpp * burst_mode_ratio,
					 8 * 100), lane_count);
पूर्ण

/* वापस pixels equvalent to txbyteclkhs */
अटल u16 pixels_from_txbyteclkhs(u16 clk_hs, पूर्णांक bpp, पूर्णांक lane_count,
			u16 burst_mode_ratio)
अणु
	वापस DIV_ROUND_UP((clk_hs * lane_count * 8 * 100),
						(bpp * burst_mode_ratio));
पूर्ण

क्रमागत mipi_dsi_pixel_क्रमmat pixel_क्रमmat_from_रेजिस्टर_bits(u32 fmt)
अणु
	/* It just so happens the VBT matches रेजिस्टर contents. */
	चयन (fmt) अणु
	हाल VID_MODE_FORMAT_RGB888:
		वापस MIPI_DSI_FMT_RGB888;
	हाल VID_MODE_FORMAT_RGB666:
		वापस MIPI_DSI_FMT_RGB666;
	हाल VID_MODE_FORMAT_RGB666_PACKED:
		वापस MIPI_DSI_FMT_RGB666_PACKED;
	हाल VID_MODE_FORMAT_RGB565:
		वापस MIPI_DSI_FMT_RGB565;
	शेष:
		MISSING_CASE(fmt);
		वापस MIPI_DSI_FMT_RGB666;
	पूर्ण
पूर्ण

व्योम vlv_dsi_रुको_क्रम_fअगरo_empty(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, क्रमागत port port)
अणु
	काष्ठा drm_encoder *encoder = &पूर्णांकel_dsi->base.base;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 mask;

	mask = LP_CTRL_FIFO_EMPTY | HS_CTRL_FIFO_EMPTY |
		LP_DATA_FIFO_EMPTY | HS_DATA_FIFO_EMPTY;

	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, MIPI_GEN_FIFO_STAT(port),
				  mask, 100))
		drm_err(&dev_priv->drm, "DPI FIFOs are not empty\n");
पूर्ण

अटल व्योम ग_लिखो_data(काष्ठा drm_i915_निजी *dev_priv,
		       i915_reg_t reg,
		       स्थिर u8 *data, u32 len)
अणु
	u32 i, j;

	क्रम (i = 0; i < len; i += 4) अणु
		u32 val = 0;

		क्रम (j = 0; j < min_t(u32, len - i, 4); j++)
			val |= *data++ << 8 * j;

		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_data(काष्ठा drm_i915_निजी *dev_priv,
		      i915_reg_t reg,
		      u8 *data, u32 len)
अणु
	u32 i, j;

	क्रम (i = 0; i < len; i += 4) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, reg);

		क्रम (j = 0; j < min_t(u32, len - i, 4); j++)
			*data++ = val >> 8 * j;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार पूर्णांकel_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				       स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा पूर्णांकel_dsi_host *पूर्णांकel_dsi_host = to_पूर्णांकel_dsi_host(host);
	काष्ठा drm_device *dev = पूर्णांकel_dsi_host->पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत port port = पूर्णांकel_dsi_host->port;
	काष्ठा mipi_dsi_packet packet;
	sमाप_प्रकार ret;
	स्थिर u8 *header, *data;
	i915_reg_t data_reg, ctrl_reg;
	u32 data_mask, ctrl_mask;

	ret = mipi_dsi_create_packet(&packet, msg);
	अगर (ret < 0)
		वापस ret;

	header = packet.header;
	data = packet.payload;

	अगर (msg->flags & MIPI_DSI_MSG_USE_LPM) अणु
		data_reg = MIPI_LP_GEN_DATA(port);
		data_mask = LP_DATA_FIFO_FULL;
		ctrl_reg = MIPI_LP_GEN_CTRL(port);
		ctrl_mask = LP_CTRL_FIFO_FULL;
	पूर्ण अन्यथा अणु
		data_reg = MIPI_HS_GEN_DATA(port);
		data_mask = HS_DATA_FIFO_FULL;
		ctrl_reg = MIPI_HS_GEN_CTRL(port);
		ctrl_mask = HS_CTRL_FIFO_FULL;
	पूर्ण

	/* note: this is never true क्रम पढ़ोs */
	अगर (packet.payload_length) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, MIPI_GEN_FIFO_STAT(port),
					    data_mask, 50))
			drm_err(&dev_priv->drm,
				"Timeout waiting for HS/LP DATA FIFO !full\n");

		ग_लिखो_data(dev_priv, data_reg, packet.payload,
			   packet.payload_length);
	पूर्ण

	अगर (msg->rx_len) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_INTR_STAT(port),
			       GEN_READ_DATA_AVAIL);
	पूर्ण

	अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, MIPI_GEN_FIFO_STAT(port),
				    ctrl_mask, 50)) अणु
		drm_err(&dev_priv->drm,
			"Timeout waiting for HS/LP CTRL FIFO !full\n");
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, ctrl_reg,
		       header[2] << 16 | header[1] << 8 | header[0]);

	/* ->rx_len is set only क्रम पढ़ोs */
	अगर (msg->rx_len) अणु
		data_mask = GEN_READ_DATA_AVAIL;
		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, MIPI_INTR_STAT(port),
					  data_mask, 50))
			drm_err(&dev_priv->drm,
				"Timeout waiting for read data.\n");

		पढ़ो_data(dev_priv, data_reg, msg->rx_buf, msg->rx_len);
	पूर्ण

	/* XXX: fix क्रम पढ़ोs and ग_लिखोs */
	वापस 4 + packet.payload_length;
पूर्ण

अटल पूर्णांक पूर्णांकel_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				 काष्ठा mipi_dsi_device *dsi)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				 काष्ठा mipi_dsi_device *dsi)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops पूर्णांकel_dsi_host_ops = अणु
	.attach = पूर्णांकel_dsi_host_attach,
	.detach = पूर्णांकel_dsi_host_detach,
	.transfer = पूर्णांकel_dsi_host_transfer,
पूर्ण;

/*
 * send a video mode command
 *
 * XXX: commands with data in MIPI_DPI_DATA?
 */
अटल पूर्णांक dpi_send_cmd(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, u32 cmd, bool hs,
			क्रमागत port port)
अणु
	काष्ठा drm_encoder *encoder = &पूर्णांकel_dsi->base.base;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 mask;

	/* XXX: pipe, hs */
	अगर (hs)
		cmd &= ~DPI_LP_MODE;
	अन्यथा
		cmd |= DPI_LP_MODE;

	/* clear bit */
	पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_INTR_STAT(port), SPL_PKT_SENT_INTERRUPT);

	/* XXX: old code skips ग_लिखो अगर control unchanged */
	अगर (cmd == पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DPI_CONTROL(port)))
		drm_dbg_kms(&dev_priv->drm,
			    "Same special packet %02x twice in a row.\n", cmd);

	पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DPI_CONTROL(port), cmd);

	mask = SPL_PKT_SENT_INTERRUPT;
	अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, MIPI_INTR_STAT(port), mask, 100))
		drm_err(&dev_priv->drm,
			"Video mode command 0x%08x send failed.\n", cmd);

	वापस 0;
पूर्ण

अटल व्योम band_gap_reset(काष्ठा drm_i915_निजी *dev_priv)
अणु
	vlv_flisdsi_get(dev_priv);

	vlv_flisdsi_ग_लिखो(dev_priv, 0x08, 0x0001);
	vlv_flisdsi_ग_लिखो(dev_priv, 0x0F, 0x0005);
	vlv_flisdsi_ग_लिखो(dev_priv, 0x0F, 0x0025);
	udelay(150);
	vlv_flisdsi_ग_लिखो(dev_priv, 0x0F, 0x0000);
	vlv_flisdsi_ग_लिखो(dev_priv, 0x08, 0x0000);

	vlv_flisdsi_put(dev_priv);
पूर्ण

अटल पूर्णांक पूर्णांकel_dsi_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = container_of(encoder, काष्ठा पूर्णांकel_dsi,
						   base);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dsi->attached_connector;
	स्थिर काष्ठा drm_display_mode *fixed_mode = पूर्णांकel_connector->panel.fixed_mode;
	काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	पूर्णांक ret;

	drm_dbg_kms(&dev_priv->drm, "\n");
	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;

	अगर (fixed_mode) अणु
		पूर्णांकel_fixed_panel_mode(fixed_mode, adjusted_mode);

		अगर (HAS_GMCH(dev_priv))
			ret = पूर्णांकel_gmch_panel_fitting(pipe_config, conn_state);
		अन्यथा
			ret = पूर्णांकel_pch_panel_fitting(pipe_config, conn_state);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (adjusted_mode->flags & DRM_MODE_FLAG_DBLSCAN)
		वापस -EINVAL;

	/* DSI uses लघु packets क्रम sync events, so clear mode flags क्रम DSI */
	adjusted_mode->flags = 0;

	अगर (पूर्णांकel_dsi->pixel_क्रमmat == MIPI_DSI_FMT_RGB888)
		pipe_config->pipe_bpp = 24;
	अन्यथा
		pipe_config->pipe_bpp = 18;

	अगर (IS_GEN9_LP(dev_priv)) अणु
		/* Enable Frame समय stamp based scanline reporting */
		pipe_config->mode_flags |=
			I915_MODE_FLAG_GET_SCANLINE_FROM_TIMESTAMP;

		/* Dual link goes to DSI transcoder A. */
		अगर (पूर्णांकel_dsi->ports == BIT(PORT_C))
			pipe_config->cpu_transcoder = TRANSCODER_DSI_C;
		अन्यथा
			pipe_config->cpu_transcoder = TRANSCODER_DSI_A;

		ret = bxt_dsi_pll_compute(encoder, pipe_config);
		अगर (ret)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ret = vlv_dsi_pll_compute(encoder, pipe_config);
		अगर (ret)
			वापस -EINVAL;
	पूर्ण

	pipe_config->घड़ी_set = true;

	वापस 0;
पूर्ण

अटल bool glk_dsi_enable_io(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 पंचांगp;
	bool cold_boot = false;

	/* Set the MIPI mode
	 * If MIPI_Mode is off, then writing to LP_Wake bit is not reflecting.
	 * Power ON MIPI IO first and then ग_लिखो पूर्णांकo IO reset and LP wake bits
	 */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port),
			       पंचांगp | GLK_MIPIIO_ENABLE);
	पूर्ण

	/* Put the IO पूर्णांकo reset */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(PORT_A));
	पंचांगp &= ~GLK_MIPIIO_RESET_RELEASED;
	पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(PORT_A), पंचांगp);

	/* Program LP Wake */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
		अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port)) & DEVICE_READY))
			पंचांगp &= ~GLK_LP_WAKE;
		अन्यथा
			पंचांगp |= GLK_LP_WAKE;
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port), पंचांगp);
	पूर्ण

	/* Wait क्रम Pwr ACK */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, MIPI_CTRL(port),
					  GLK_MIPIIO_PORT_POWERED, 20))
			drm_err(&dev_priv->drm, "MIPIO port is powergated\n");
	पूर्ण

	/* Check क्रम cold boot scenario */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		cold_boot |=
			!(पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port)) & DEVICE_READY);
	पूर्ण

	वापस cold_boot;
पूर्ण

अटल व्योम glk_dsi_device_पढ़ोy(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 val;

	/* Wait क्रम MIPI PHY status bit to set */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, MIPI_CTRL(port),
					  GLK_PHY_STATUS_PORT_READY, 20))
			drm_err(&dev_priv->drm, "PHY is not ON\n");
	पूर्ण

	/* Get IO out of reset */
	val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(PORT_A));
	पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(PORT_A),
		       val | GLK_MIPIIO_RESET_RELEASED);

	/* Get IO out of Low घातer state*/
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port)) & DEVICE_READY)) अणु
			val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port));
			val &= ~ULPS_STATE_MASK;
			val |= DEVICE_READY;
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), val);
			usleep_range(10, 15);
		पूर्ण अन्यथा अणु
			/* Enter ULPS */
			val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port));
			val &= ~ULPS_STATE_MASK;
			val |= (ULPS_STATE_ENTER | DEVICE_READY);
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), val);

			/* Wait क्रम ULPS active */
			अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, MIPI_CTRL(port),
						    GLK_ULPS_NOT_ACTIVE, 20))
				drm_err(&dev_priv->drm, "ULPS not active\n");

			/* Exit ULPS */
			val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port));
			val &= ~ULPS_STATE_MASK;
			val |= (ULPS_STATE_EXIT | DEVICE_READY);
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), val);

			/* Enter Normal Mode */
			val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port));
			val &= ~ULPS_STATE_MASK;
			val |= (ULPS_STATE_NORMAL_OPERATION | DEVICE_READY);
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), val);

			val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
			val &= ~GLK_LP_WAKE;
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port), val);
		पूर्ण
	पूर्ण

	/* Wait क्रम Stop state */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, MIPI_CTRL(port),
					  GLK_DATA_LANE_STOP_STATE, 20))
			drm_err(&dev_priv->drm,
				"Date lane not in STOP state\n");
	पूर्ण

	/* Wait क्रम AFE LATCH */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, BXT_MIPI_PORT_CTRL(port),
					  AFE_LATCHOUT, 20))
			drm_err(&dev_priv->drm,
				"D-PHY not entering LP-11 state\n");
	पूर्ण
पूर्ण

अटल व्योम bxt_dsi_device_पढ़ोy(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "\n");

	/* Enable MIPI PHY transparent latch */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_MIPI_PORT_CTRL(port));
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_MIPI_PORT_CTRL(port),
			       val | LP_OUTPUT_HOLD);
		usleep_range(2000, 2500);
	पूर्ण

	/* Clear ULPS and set device पढ़ोy */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port));
		val &= ~ULPS_STATE_MASK;
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), val);
		usleep_range(2000, 2500);
		val |= DEVICE_READY;
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), val);
	पूर्ण
पूर्ण

अटल व्योम vlv_dsi_device_पढ़ोy(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "\n");

	vlv_flisdsi_get(dev_priv);
	/* program rcomp क्रम compliance, reduce from 50 ohms to 45 ohms
	 * needed everyसमय after घातer gate */
	vlv_flisdsi_ग_लिखो(dev_priv, 0x04, 0x0004);
	vlv_flisdsi_put(dev_priv);

	/* bandgap reset is needed after everyसमय we करो घातer gate */
	band_gap_reset(dev_priv);

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port),
			       ULPS_STATE_ENTER);
		usleep_range(2500, 3000);

		/* Enable MIPI PHY transparent latch
		 * Common bit क्रम both MIPI Port A & MIPI Port C
		 * No similar bit in MIPI Port C reg
		 */
		val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_PORT_CTRL(PORT_A));
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_PORT_CTRL(PORT_A),
			       val | LP_OUTPUT_HOLD);
		usleep_range(1000, 1500);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port),
			       ULPS_STATE_EXIT);
		usleep_range(2500, 3000);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port),
			       DEVICE_READY);
		usleep_range(2500, 3000);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_device_पढ़ोy(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_GEMINILAKE(dev_priv))
		glk_dsi_device_पढ़ोy(encoder);
	अन्यथा अगर (IS_GEN9_LP(dev_priv))
		bxt_dsi_device_पढ़ोy(encoder);
	अन्यथा
		vlv_dsi_device_पढ़ोy(encoder);
पूर्ण

अटल व्योम glk_dsi_enter_low_घातer_mode(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 val;

	/* Enter ULPS */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port));
		val &= ~ULPS_STATE_MASK;
		val |= (ULPS_STATE_ENTER | DEVICE_READY);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), val);
	पूर्ण

	/* Wait क्रम MIPI PHY status bit to unset */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, MIPI_CTRL(port),
					    GLK_PHY_STATUS_PORT_READY, 20))
			drm_err(&dev_priv->drm, "PHY is not turning OFF\n");
	पूर्ण

	/* Wait क्रम Pwr ACK bit to unset */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, MIPI_CTRL(port),
					    GLK_MIPIIO_PORT_POWERED, 20))
			drm_err(&dev_priv->drm,
				"MIPI IO Port is not powergated\n");
	पूर्ण
पूर्ण

अटल व्योम glk_dsi_disable_mipi_io(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 पंचांगp;

	/* Put the IO पूर्णांकo reset */
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(PORT_A));
	पंचांगp &= ~GLK_MIPIIO_RESET_RELEASED;
	पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(PORT_A), पंचांगp);

	/* Wait क्रम MIPI PHY status bit to unset */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, MIPI_CTRL(port),
					    GLK_PHY_STATUS_PORT_READY, 20))
			drm_err(&dev_priv->drm, "PHY is not turning OFF\n");
	पूर्ण

	/* Clear MIPI mode */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
		पंचांगp &= ~GLK_MIPIIO_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port), पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम glk_dsi_clear_device_पढ़ोy(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	glk_dsi_enter_low_घातer_mode(encoder);
	glk_dsi_disable_mipi_io(encoder);
पूर्ण

अटल व्योम vlv_dsi_clear_device_पढ़ोy(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;

	drm_dbg_kms(&dev_priv->drm, "\n");
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		/* Common bit क्रम both MIPI Port A & MIPI Port C on VLV/CHV */
		i915_reg_t port_ctrl = IS_GEN9_LP(dev_priv) ?
			BXT_MIPI_PORT_CTRL(port) : MIPI_PORT_CTRL(PORT_A);
		u32 val;

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port),
			       DEVICE_READY | ULPS_STATE_ENTER);
		usleep_range(2000, 2500);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port),
			       DEVICE_READY | ULPS_STATE_EXIT);
		usleep_range(2000, 2500);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port),
			       DEVICE_READY | ULPS_STATE_ENTER);
		usleep_range(2000, 2500);

		/*
		 * On VLV/CHV, रुको till Clock lanes are in LP-00 state क्रम MIPI
		 * Port A only. MIPI Port C has no similar bit क्रम checking.
		 */
		अगर ((IS_GEN9_LP(dev_priv) || port == PORT_A) &&
		    पूर्णांकel_de_रुको_क्रम_clear(dev_priv, port_ctrl,
					    AFE_LATCHOUT, 30))
			drm_err(&dev_priv->drm, "DSI LP not going Low\n");

		/* Disable MIPI PHY transparent latch */
		val = पूर्णांकel_de_पढ़ो(dev_priv, port_ctrl);
		पूर्णांकel_de_ग_लिखो(dev_priv, port_ctrl, val & ~LP_OUTPUT_HOLD);
		usleep_range(1000, 1500);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), 0x00);
		usleep_range(2000, 2500);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_port_enable(काष्ठा पूर्णांकel_encoder *encoder,
				  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;

	अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK) अणु
		u32 temp;
		अगर (IS_GEN9_LP(dev_priv)) अणु
			क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
				temp = पूर्णांकel_de_पढ़ो(dev_priv,
						     MIPI_CTRL(port));
				temp &= ~BXT_PIXEL_OVERLAP_CNT_MASK |
					पूर्णांकel_dsi->pixel_overlap <<
					BXT_PIXEL_OVERLAP_CNT_SHIFT;
				पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port),
					       temp);
			पूर्ण
		पूर्ण अन्यथा अणु
			temp = पूर्णांकel_de_पढ़ो(dev_priv, VLV_CHICKEN_3);
			temp &= ~PIXEL_OVERLAP_CNT_MASK |
					पूर्णांकel_dsi->pixel_overlap <<
					PIXEL_OVERLAP_CNT_SHIFT;
			पूर्णांकel_de_ग_लिखो(dev_priv, VLV_CHICKEN_3, temp);
		पूर्ण
	पूर्ण

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		i915_reg_t port_ctrl = IS_GEN9_LP(dev_priv) ?
			BXT_MIPI_PORT_CTRL(port) : MIPI_PORT_CTRL(port);
		u32 temp;

		temp = पूर्णांकel_de_पढ़ो(dev_priv, port_ctrl);

		temp &= ~LANE_CONFIGURATION_MASK;
		temp &= ~DUAL_LINK_MODE_MASK;

		अगर (पूर्णांकel_dsi->ports == (BIT(PORT_A) | BIT(PORT_C))) अणु
			temp |= (पूर्णांकel_dsi->dual_link - 1)
						<< DUAL_LINK_MODE_SHIFT;
			अगर (IS_BROXTON(dev_priv))
				temp |= LANE_CONFIGURATION_DUAL_LINK_A;
			अन्यथा
				temp |= crtc->pipe ?
					LANE_CONFIGURATION_DUAL_LINK_B :
					LANE_CONFIGURATION_DUAL_LINK_A;
		पूर्ण

		अगर (पूर्णांकel_dsi->pixel_क्रमmat != MIPI_DSI_FMT_RGB888)
			temp |= DITHERING_ENABLE;

		/* निश्चित ip_tg_enable संकेत */
		पूर्णांकel_de_ग_लिखो(dev_priv, port_ctrl, temp | DPI_ENABLE);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, port_ctrl);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_port_disable(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		i915_reg_t port_ctrl = IS_GEN9_LP(dev_priv) ?
			BXT_MIPI_PORT_CTRL(port) : MIPI_PORT_CTRL(port);
		u32 temp;

		/* de-निश्चित ip_tg_enable संकेत */
		temp = पूर्णांकel_de_पढ़ो(dev_priv, port_ctrl);
		पूर्णांकel_de_ग_लिखो(dev_priv, port_ctrl, temp & ~DPI_ENABLE);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, port_ctrl);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_prepare(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config);
अटल व्योम पूर्णांकel_dsi_unprepare(काष्ठा पूर्णांकel_encoder *encoder);

/*
 * Panel enable/disable sequences from the VBT spec.
 *
 * Note the spec has AssertReset / Deनिश्चितReset swapped from their
 * usual naming. We use the normal names to aव्योम confusion (so below
 * they are swapped compared to the spec).
 *
 * Steps starting with MIPI refer to VBT sequences, note that क्रम v2
 * VBTs several steps which have a VBT in v2 are expected to be handled
 * directly by the driver, by directly driving gpios क्रम example.
 *
 * v2 video mode seq         v3 video mode seq         command mode seq
 * - घातer on                - MIPIPanelPowerOn        - घातer on
 * - रुको t1+t2                                        - रुको t1+t2
 * - MIPIDeनिश्चितResetPin    - MIPIDeनिश्चितResetPin    - MIPIDeनिश्चितResetPin
 * - io lines to lp-11       - io lines to lp-11       - io lines to lp-11
 * - MIPISendInitialDcsCmds  - MIPISendInitialDcsCmds  - MIPISendInitialDcsCmds
 *                                                     - MIPITearOn
 *                                                     - MIPIDisplayOn
 * - turn on DPI             - turn on DPI             - set pipe to dsr mode
 * - MIPIDisplayOn           - MIPIDisplayOn
 * - रुको t5                                           - रुको t5
 * - backlight on            - MIPIBacklightOn         - backlight on
 * ...                       ...                       ... issue mem cmds ...
 * - backlight off           - MIPIBacklightOff        - backlight off
 * - रुको t6                                           - रुको t6
 * - MIPIDisplayOff
 * - turn off DPI            - turn off DPI            - disable pipe dsr mode
 *                                                     - MIPITearOff
 *                           - MIPIDisplayOff          - MIPIDisplayOff
 * - io lines to lp-00       - io lines to lp-00       - io lines to lp-00
 * - MIPIAssertResetPin      - MIPIAssertResetPin      - MIPIAssertResetPin
 * - रुको t3                                           - रुको t3
 * - घातer off               - MIPIPanelPowerOff       - घातer off
 * - रुको t4                                           - रुको t4
 */

/*
 * DSI port enable has to be करोne beक्रमe pipe and plane enable, so we करो it in
 * the pre_enable hook instead of the enable hook.
 */
अटल व्योम पूर्णांकel_dsi_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा drm_crtc *crtc = pipe_config->uapi.crtc;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(crtc);
	क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;
	क्रमागत port port;
	u32 val;
	bool glk_cold_boot = false;

	drm_dbg_kms(&dev_priv->drm, "\n");

	पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, true);

	/*
	 * The BIOS may leave the PLL in a wonky state where it करोesn't
	 * lock. It needs to be fully घातered करोwn to fix it.
	 */
	अगर (IS_GEN9_LP(dev_priv)) अणु
		bxt_dsi_pll_disable(encoder);
		bxt_dsi_pll_enable(encoder, pipe_config);
	पूर्ण अन्यथा अणु
		vlv_dsi_pll_disable(encoder);
		vlv_dsi_pll_enable(encoder, pipe_config);
	पूर्ण

	अगर (IS_BROXTON(dev_priv)) अणु
		/* Add MIPI IO reset programming क्रम modeset */
		val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_P_CR_GT_DISP_PWRON);
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_CR_GT_DISP_PWRON,
			       val | MIPIO_RST_CTRL);

		/* Power up DSI regulator */
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_DSI_REGULATOR_CFG, STAP_SELECT);
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_DSI_REGULATOR_TX_CTRL, 0);
	पूर्ण

	अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
		u32 val;

		/* Disable DPOunit घड़ी gating, can stall pipe */
		val = पूर्णांकel_de_पढ़ो(dev_priv, DSPCLK_GATE_D);
		val |= DPOUNIT_CLOCK_GATE_DISABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, DSPCLK_GATE_D, val);
	पूर्ण

	अगर (!IS_GEMINILAKE(dev_priv))
		पूर्णांकel_dsi_prepare(encoder, pipe_config);

	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_POWER_ON);

	/*
	 * Give the panel समय to घातer-on and then deनिश्चित its reset.
	 * Depending on the VBT MIPI sequences version the deनिश्चित-seq
	 * may contain the necessary delay, पूर्णांकel_dsi_msleep() will skip
	 * the delay in that हाल. If there is no deनिश्चित-seq, then an
	 * unconditional msleep is used to give the panel समय to घातer-on.
	 */
	अगर (dev_priv->vbt.dsi.sequence[MIPI_SEQ_DEASSERT_RESET]) अणु
		पूर्णांकel_dsi_msleep(पूर्णांकel_dsi, पूर्णांकel_dsi->panel_on_delay);
		पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_DEASSERT_RESET);
	पूर्ण अन्यथा अणु
		msleep(पूर्णांकel_dsi->panel_on_delay);
	पूर्ण

	अगर (IS_GEMINILAKE(dev_priv)) अणु
		glk_cold_boot = glk_dsi_enable_io(encoder);

		/* Prepare port in cold boot(s3/s4) scenario */
		अगर (glk_cold_boot)
			पूर्णांकel_dsi_prepare(encoder, pipe_config);
	पूर्ण

	/* Put device in पढ़ोy state (LP-11) */
	पूर्णांकel_dsi_device_पढ़ोy(encoder);

	/* Prepare port in normal boot scenario */
	अगर (IS_GEMINILAKE(dev_priv) && !glk_cold_boot)
		पूर्णांकel_dsi_prepare(encoder, pipe_config);

	/* Send initialization commands in LP mode */
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_INIT_OTP);

	/* Enable port in pre-enable phase itself because as per hw team
	 * recommendation, port should be enabled beक्रम plane & pipe */
	अगर (is_cmd_mode(पूर्णांकel_dsi)) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports)
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       MIPI_MAX_RETURN_PKT_SIZE(port), 8 * 4);
		पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_TEAR_ON);
		पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_DISPLAY_ON);
	पूर्ण अन्यथा अणु
		msleep(20); /* XXX */
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports)
			dpi_send_cmd(पूर्णांकel_dsi, TURN_ON, false, port);
		पूर्णांकel_dsi_msleep(पूर्णांकel_dsi, 100);

		पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_DISPLAY_ON);

		पूर्णांकel_dsi_port_enable(encoder, pipe_config);
	पूर्ण

	पूर्णांकel_panel_enable_backlight(pipe_config, conn_state);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_BACKLIGHT_ON);
पूर्ण

अटल व्योम bxt_dsi_enable(काष्ठा पूर्णांकel_atomic_state *state,
			   काष्ठा पूर्णांकel_encoder *encoder,
			   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			   स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	drm_WARN_ON(state->base.dev, crtc_state->has_pch_encoder);

	पूर्णांकel_crtc_vblank_on(crtc_state);
पूर्ण

/*
 * DSI port disable has to be करोne after pipe and plane disable, so we करो it in
 * the post_disable hook.
 */
अटल व्योम पूर्णांकel_dsi_disable(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;

	drm_dbg_kms(&i915->drm, "\n");

	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_BACKLIGHT_OFF);
	पूर्णांकel_panel_disable_backlight(old_conn_state);

	/*
	 * According to the spec we should send SHUTDOWN beक्रमe
	 * MIPI_SEQ_DISPLAY_OFF only क्रम v3+ VBTs, but field testing
	 * has shown that the v3 sequence works क्रम v2 VBTs too
	 */
	अगर (is_vid_mode(पूर्णांकel_dsi)) अणु
		/* Send Shutकरोwn command to the panel in LP mode */
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports)
			dpi_send_cmd(पूर्णांकel_dsi, SHUTDOWN, false, port);
		msleep(10);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_clear_device_पढ़ोy(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	अगर (IS_GEMINILAKE(dev_priv))
		glk_dsi_clear_device_पढ़ोy(encoder);
	अन्यथा
		vlv_dsi_clear_device_पढ़ोy(encoder);
पूर्ण

अटल व्योम पूर्णांकel_dsi_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				   स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 val;

	drm_dbg_kms(&dev_priv->drm, "\n");

	अगर (IS_GEN9_LP(dev_priv)) अणु
		पूर्णांकel_crtc_vblank_off(old_crtc_state);

		skl_scaler_disable(old_crtc_state);
	पूर्ण

	अगर (is_vid_mode(पूर्णांकel_dsi)) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports)
			vlv_dsi_रुको_क्रम_fअगरo_empty(पूर्णांकel_dsi, port);

		पूर्णांकel_dsi_port_disable(encoder);
		usleep_range(2000, 5000);
	पूर्ण

	पूर्णांकel_dsi_unprepare(encoder);

	/*
	 * अगर disable packets are sent beक्रमe sending shutकरोwn packet then in
	 * some next enable sequence send turn on packet error is observed
	 */
	अगर (is_cmd_mode(पूर्णांकel_dsi))
		पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_TEAR_OFF);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_DISPLAY_OFF);

	/* Transition to LP-00 */
	पूर्णांकel_dsi_clear_device_पढ़ोy(encoder);

	अगर (IS_BROXTON(dev_priv)) अणु
		/* Power करोwn DSI regulator to save घातer */
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_DSI_REGULATOR_CFG, STAP_SELECT);
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_DSI_REGULATOR_TX_CTRL,
			       HS_IO_CTRL_SELECT);

		/* Add MIPI IO reset programming क्रम modeset */
		val = पूर्णांकel_de_पढ़ो(dev_priv, BXT_P_CR_GT_DISP_PWRON);
		पूर्णांकel_de_ग_लिखो(dev_priv, BXT_P_CR_GT_DISP_PWRON,
			       val & ~MIPIO_RST_CTRL);
	पूर्ण

	अगर (IS_GEN9_LP(dev_priv)) अणु
		bxt_dsi_pll_disable(encoder);
	पूर्ण अन्यथा अणु
		u32 val;

		vlv_dsi_pll_disable(encoder);

		val = पूर्णांकel_de_पढ़ो(dev_priv, DSPCLK_GATE_D);
		val &= ~DPOUNIT_CLOCK_GATE_DISABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, DSPCLK_GATE_D, val);
	पूर्ण

	/* Assert reset */
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_ASSERT_RESET);

	पूर्णांकel_dsi_msleep(पूर्णांकel_dsi, पूर्णांकel_dsi->panel_off_delay);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_POWER_OFF);

	/*
	 * FIXME As we करो with eDP, just make a note of the समय here
	 * and perक्रमm the रुको beक्रमe the next panel घातer on.
	 */
	msleep(पूर्णांकel_dsi->panel_pwr_cycle_delay);
पूर्ण

अटल व्योम पूर्णांकel_dsi_shutकरोwn(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);

	msleep(पूर्णांकel_dsi->panel_pwr_cycle_delay);
पूर्ण

अटल bool पूर्णांकel_dsi_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				   क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत port port;
	bool active = false;

	drm_dbg_kms(&dev_priv->drm, "\n");

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	/*
	 * On Broxton the PLL needs to be enabled with a valid भागider
	 * configuration, otherwise accessing DSI रेजिस्टरs will hang the
	 * machine. See BSpec North Display Engine रेजिस्टरs/MIPI[BXT].
	 */
	अगर (IS_GEN9_LP(dev_priv) && !bxt_dsi_pll_is_enabled(dev_priv))
		जाओ out_put_घातer;

	/* XXX: this only works क्रम one DSI output */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		i915_reg_t ctrl_reg = IS_GEN9_LP(dev_priv) ?
			BXT_MIPI_PORT_CTRL(port) : MIPI_PORT_CTRL(port);
		bool enabled = पूर्णांकel_de_पढ़ो(dev_priv, ctrl_reg) & DPI_ENABLE;

		/*
		 * Due to some hardware limitations on VLV/CHV, the DPI enable
		 * bit in port C control रेजिस्टर करोes not get set. As a
		 * workaround, check pipe B conf instead.
		 */
		अगर ((IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) &&
		    port == PORT_C)
			enabled = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(PIPE_B)) & PIPECONF_ENABLE;

		/* Try command mode अगर video mode not enabled */
		अगर (!enabled) अणु
			u32 पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
						MIPI_DSI_FUNC_PRG(port));
			enabled = पंचांगp & CMD_MODE_DATA_WIDTH_MASK;
		पूर्ण

		अगर (!enabled)
			जारी;

		अगर (!(पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DEVICE_READY(port)) & DEVICE_READY))
			जारी;

		अगर (IS_GEN9_LP(dev_priv)) अणु
			u32 पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
			पंचांगp &= BXT_PIPE_SELECT_MASK;
			पंचांगp >>= BXT_PIPE_SELECT_SHIFT;

			अगर (drm_WARN_ON(&dev_priv->drm, पंचांगp > PIPE_C))
				जारी;

			*pipe = पंचांगp;
		पूर्ण अन्यथा अणु
			*pipe = port == PORT_A ? PIPE_A : PIPE_B;
		पूर्ण

		active = true;
		अवरोध;
	पूर्ण

out_put_घातer:
	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);

	वापस active;
पूर्ण

अटल व्योम bxt_dsi_get_pipe_config(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_device *dev = encoder->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_display_mode *adjusted_mode =
					&pipe_config->hw.adjusted_mode;
	काष्ठा drm_display_mode *adjusted_mode_sw;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	अचिन्हित पूर्णांक lane_count = पूर्णांकel_dsi->lane_count;
	अचिन्हित पूर्णांक bpp, fmt;
	क्रमागत port port;
	u16 hactive, hfp, hsync, hbp, vfp, vsync, vbp;
	u16 hfp_sw, hsync_sw, hbp_sw;
	u16 crtc_htotal_sw, crtc_hsync_start_sw, crtc_hsync_end_sw,
				crtc_hblank_start_sw, crtc_hblank_end_sw;

	/* FIXME: hw पढ़ोout should not depend on SW state */
	adjusted_mode_sw = &crtc->config->hw.adjusted_mode;

	/*
	 * Atleast one port is active as encoder->get_config called only अगर
	 * encoder->get_hw_state() वापसs true.
	 */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (पूर्णांकel_de_पढ़ो(dev_priv, BXT_MIPI_PORT_CTRL(port)) & DPI_ENABLE)
			अवरोध;
	पूर्ण

	fmt = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DSI_FUNC_PRG(port)) & VID_MODE_FORMAT_MASK;
	bpp = mipi_dsi_pixel_क्रमmat_to_bpp(
			pixel_क्रमmat_from_रेजिस्टर_bits(fmt));

	pipe_config->pipe_bpp = bdw_get_pipemisc_bpp(crtc);

	/* Enable Frame समय stamo based scanline reporting */
	pipe_config->mode_flags |=
		I915_MODE_FLAG_GET_SCANLINE_FROM_TIMESTAMP;

	/* In terms of pixels */
	adjusted_mode->crtc_hdisplay =
				पूर्णांकel_de_पढ़ो(dev_priv,
				              BXT_MIPI_TRANS_HACTIVE(port));
	adjusted_mode->crtc_vdisplay =
				पूर्णांकel_de_पढ़ो(dev_priv,
				              BXT_MIPI_TRANS_VACTIVE(port));
	adjusted_mode->crtc_vtotal =
				पूर्णांकel_de_पढ़ो(dev_priv,
				              BXT_MIPI_TRANS_VTOTAL(port));

	hactive = adjusted_mode->crtc_hdisplay;
	hfp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_HFP_COUNT(port));

	/*
	 * Meaningful क्रम video mode non-burst sync pulse mode only,
	 * can be zero क्रम non-burst sync events and burst modes
	 */
	hsync = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_HSYNC_PADDING_COUNT(port));
	hbp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_HBP_COUNT(port));

	/* harizontal values are in terms of high speed byte घड़ी */
	hfp = pixels_from_txbyteclkhs(hfp, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);
	hsync = pixels_from_txbyteclkhs(hsync, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);
	hbp = pixels_from_txbyteclkhs(hbp, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);

	अगर (पूर्णांकel_dsi->dual_link) अणु
		hfp *= 2;
		hsync *= 2;
		hbp *= 2;
	पूर्ण

	/* vertical values are in terms of lines */
	vfp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_VFP_COUNT(port));
	vsync = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_VSYNC_PADDING_COUNT(port));
	vbp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_VBP_COUNT(port));

	adjusted_mode->crtc_htotal = hactive + hfp + hsync + hbp;
	adjusted_mode->crtc_hsync_start = hfp + adjusted_mode->crtc_hdisplay;
	adjusted_mode->crtc_hsync_end = hsync + adjusted_mode->crtc_hsync_start;
	adjusted_mode->crtc_hblank_start = adjusted_mode->crtc_hdisplay;
	adjusted_mode->crtc_hblank_end = adjusted_mode->crtc_htotal;

	adjusted_mode->crtc_vsync_start = vfp + adjusted_mode->crtc_vdisplay;
	adjusted_mode->crtc_vsync_end = vsync + adjusted_mode->crtc_vsync_start;
	adjusted_mode->crtc_vblank_start = adjusted_mode->crtc_vdisplay;
	adjusted_mode->crtc_vblank_end = adjusted_mode->crtc_vtotal;

	/*
	 * In BXT DSI there is no regs programmed with few horizontal timings
	 * in Pixels but txbyteclkhs.. So retrieval process adds some
	 * ROUND_UP ERRORS in the process of PIXELS<==>txbyteclkhs.
	 * Actually here क्रम the given adjusted_mode, we are calculating the
	 * value programmed to the port and then back to the horizontal timing
	 * param in pixels. This is the expected value, including roundup errors
	 * And अगर that is same as retrieved value from port, then
	 * (HW state) adjusted_mode's horizontal timings are corrected to
	 * match with SW state to nullअगरy the errors.
	 */
	/* Calculating the value programmed to the Port रेजिस्टर */
	hfp_sw = adjusted_mode_sw->crtc_hsync_start -
					adjusted_mode_sw->crtc_hdisplay;
	hsync_sw = adjusted_mode_sw->crtc_hsync_end -
					adjusted_mode_sw->crtc_hsync_start;
	hbp_sw = adjusted_mode_sw->crtc_htotal -
					adjusted_mode_sw->crtc_hsync_end;

	अगर (पूर्णांकel_dsi->dual_link) अणु
		hfp_sw /= 2;
		hsync_sw /= 2;
		hbp_sw /= 2;
	पूर्ण

	hfp_sw = txbyteclkhs(hfp_sw, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);
	hsync_sw = txbyteclkhs(hsync_sw, bpp, lane_count,
			    पूर्णांकel_dsi->burst_mode_ratio);
	hbp_sw = txbyteclkhs(hbp_sw, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);

	/* Reverse calculating the adjusted mode parameters from port reg vals*/
	hfp_sw = pixels_from_txbyteclkhs(hfp_sw, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);
	hsync_sw = pixels_from_txbyteclkhs(hsync_sw, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);
	hbp_sw = pixels_from_txbyteclkhs(hbp_sw, bpp, lane_count,
						पूर्णांकel_dsi->burst_mode_ratio);

	अगर (पूर्णांकel_dsi->dual_link) अणु
		hfp_sw *= 2;
		hsync_sw *= 2;
		hbp_sw *= 2;
	पूर्ण

	crtc_htotal_sw = adjusted_mode_sw->crtc_hdisplay + hfp_sw +
							hsync_sw + hbp_sw;
	crtc_hsync_start_sw = hfp_sw + adjusted_mode_sw->crtc_hdisplay;
	crtc_hsync_end_sw = hsync_sw + crtc_hsync_start_sw;
	crtc_hblank_start_sw = adjusted_mode_sw->crtc_hdisplay;
	crtc_hblank_end_sw = crtc_htotal_sw;

	अगर (adjusted_mode->crtc_htotal == crtc_htotal_sw)
		adjusted_mode->crtc_htotal = adjusted_mode_sw->crtc_htotal;

	अगर (adjusted_mode->crtc_hsync_start == crtc_hsync_start_sw)
		adjusted_mode->crtc_hsync_start =
					adjusted_mode_sw->crtc_hsync_start;

	अगर (adjusted_mode->crtc_hsync_end == crtc_hsync_end_sw)
		adjusted_mode->crtc_hsync_end =
					adjusted_mode_sw->crtc_hsync_end;

	अगर (adjusted_mode->crtc_hblank_start == crtc_hblank_start_sw)
		adjusted_mode->crtc_hblank_start =
					adjusted_mode_sw->crtc_hblank_start;

	अगर (adjusted_mode->crtc_hblank_end == crtc_hblank_end_sw)
		adjusted_mode->crtc_hblank_end =
					adjusted_mode_sw->crtc_hblank_end;
पूर्ण

अटल व्योम पूर्णांकel_dsi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	u32 pclk;
	drm_dbg_kms(&dev_priv->drm, "\n");

	pipe_config->output_types |= BIT(INTEL_OUTPUT_DSI);

	अगर (IS_GEN9_LP(dev_priv)) अणु
		bxt_dsi_get_pipe_config(encoder, pipe_config);
		pclk = bxt_dsi_get_pclk(encoder, pipe_config);
	पूर्ण अन्यथा अणु
		pclk = vlv_dsi_get_pclk(encoder, pipe_config);
	पूर्ण

	अगर (pclk) अणु
		pipe_config->hw.adjusted_mode.crtc_घड़ी = pclk;
		pipe_config->port_घड़ी = pclk;
	पूर्ण
पूर्ण

/* वापस txclkesc cycles in terms of भागider and duration in us */
अटल u16 txclkesc(u32 भागider, अचिन्हित पूर्णांक us)
अणु
	चयन (भागider) अणु
	हाल ESCAPE_CLOCK_DIVIDER_1:
	शेष:
		वापस 20 * us;
	हाल ESCAPE_CLOCK_DIVIDER_2:
		वापस 10 * us;
	हाल ESCAPE_CLOCK_DIVIDER_4:
		वापस 5 * us;
	पूर्ण
पूर्ण

अटल व्योम set_dsi_timings(काष्ठा drm_encoder *encoder,
			    स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(to_पूर्णांकel_encoder(encoder));
	क्रमागत port port;
	अचिन्हित पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);
	अचिन्हित पूर्णांक lane_count = पूर्णांकel_dsi->lane_count;

	u16 hactive, hfp, hsync, hbp, vfp, vsync, vbp;

	hactive = adjusted_mode->crtc_hdisplay;
	hfp = adjusted_mode->crtc_hsync_start - adjusted_mode->crtc_hdisplay;
	hsync = adjusted_mode->crtc_hsync_end - adjusted_mode->crtc_hsync_start;
	hbp = adjusted_mode->crtc_htotal - adjusted_mode->crtc_hsync_end;

	अगर (पूर्णांकel_dsi->dual_link) अणु
		hactive /= 2;
		अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK)
			hactive += पूर्णांकel_dsi->pixel_overlap;
		hfp /= 2;
		hsync /= 2;
		hbp /= 2;
	पूर्ण

	vfp = adjusted_mode->crtc_vsync_start - adjusted_mode->crtc_vdisplay;
	vsync = adjusted_mode->crtc_vsync_end - adjusted_mode->crtc_vsync_start;
	vbp = adjusted_mode->crtc_vtotal - adjusted_mode->crtc_vsync_end;

	/* horizontal values are in terms of high speed byte घड़ी */
	hactive = txbyteclkhs(hactive, bpp, lane_count,
			      पूर्णांकel_dsi->burst_mode_ratio);
	hfp = txbyteclkhs(hfp, bpp, lane_count, पूर्णांकel_dsi->burst_mode_ratio);
	hsync = txbyteclkhs(hsync, bpp, lane_count,
			    पूर्णांकel_dsi->burst_mode_ratio);
	hbp = txbyteclkhs(hbp, bpp, lane_count, पूर्णांकel_dsi->burst_mode_ratio);

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (IS_GEN9_LP(dev_priv)) अणु
			/*
			 * Program hdisplay and vdisplay on MIPI transcoder.
			 * This is dअगरferent from calculated hactive and
			 * vactive, as they are calculated per channel basis,
			 * whereas these values should be based on resolution.
			 */
			पूर्णांकel_de_ग_लिखो(dev_priv, BXT_MIPI_TRANS_HACTIVE(port),
				       adjusted_mode->crtc_hdisplay);
			पूर्णांकel_de_ग_लिखो(dev_priv, BXT_MIPI_TRANS_VACTIVE(port),
				       adjusted_mode->crtc_vdisplay);
			पूर्णांकel_de_ग_लिखो(dev_priv, BXT_MIPI_TRANS_VTOTAL(port),
				       adjusted_mode->crtc_vtotal);
		पूर्ण

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_HACTIVE_AREA_COUNT(port),
			       hactive);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_HFP_COUNT(port), hfp);

		/* meaningful क्रम video mode non-burst sync pulse mode only,
		 * can be zero क्रम non-burst sync events and burst modes */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_HSYNC_PADDING_COUNT(port),
			       hsync);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_HBP_COUNT(port), hbp);

		/* vertical values are in terms of lines */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_VFP_COUNT(port), vfp);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_VSYNC_PADDING_COUNT(port),
			       vsync);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_VBP_COUNT(port), vbp);
	पूर्ण
पूर्ण

अटल u32 pixel_क्रमmat_to_reg(क्रमागत mipi_dsi_pixel_क्रमmat fmt)
अणु
	चयन (fmt) अणु
	हाल MIPI_DSI_FMT_RGB888:
		वापस VID_MODE_FORMAT_RGB888;
	हाल MIPI_DSI_FMT_RGB666:
		वापस VID_MODE_FORMAT_RGB666;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		वापस VID_MODE_FORMAT_RGB666_PACKED;
	हाल MIPI_DSI_FMT_RGB565:
		वापस VID_MODE_FORMAT_RGB565;
	शेष:
		MISSING_CASE(fmt);
		वापस VID_MODE_FORMAT_RGB666;
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_prepare(काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_encoder *encoder = &पूर्णांकel_encoder->base;
	काष्ठा drm_device *dev = encoder->dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(to_पूर्णांकel_encoder(encoder));
	स्थिर काष्ठा drm_display_mode *adjusted_mode = &pipe_config->hw.adjusted_mode;
	क्रमागत port port;
	अचिन्हित पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);
	u32 val, पंचांगp;
	u16 mode_hdisplay;

	drm_dbg_kms(&dev_priv->drm, "pipe %c\n", pipe_name(पूर्णांकel_crtc->pipe));

	mode_hdisplay = adjusted_mode->crtc_hdisplay;

	अगर (पूर्णांकel_dsi->dual_link) अणु
		mode_hdisplay /= 2;
		अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK)
			mode_hdisplay += पूर्णांकel_dsi->pixel_overlap;
	पूर्ण

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		अगर (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) अणु
			/*
			 * escape घड़ी भागider, 20MHz, shared क्रम A and C.
			 * device पढ़ोy must be off when करोing this! txclkesc?
			 */
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(PORT_A));
			पंचांगp &= ~ESCAPE_CLOCK_DIVIDER_MASK;
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(PORT_A),
				       पंचांगp | ESCAPE_CLOCK_DIVIDER_1);

			/* पढ़ो request priority is per pipe */
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
			पंचांगp &= ~READ_REQUEST_PRIORITY_MASK;
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port),
				       पंचांगp | READ_REQUEST_PRIORITY_HIGH);
		पूर्ण अन्यथा अगर (IS_GEN9_LP(dev_priv)) अणु
			क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;

			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_CTRL(port));
			पंचांगp &= ~BXT_PIPE_SELECT_MASK;

			पंचांगp |= BXT_PIPE_SELECT(pipe);
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CTRL(port), पंचांगp);
		पूर्ण

		/* XXX: why here, why like this? handling in irq handler?! */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_INTR_STAT(port), 0xffffffff);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_INTR_EN(port), 0xffffffff);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DPHY_PARAM(port),
			       पूर्णांकel_dsi->dphy_reg);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DPI_RESOLUTION(port),
			       adjusted_mode->crtc_vdisplay << VERTICAL_ADDRESS_SHIFT | mode_hdisplay << HORIZONTAL_ADDRESS_SHIFT);
	पूर्ण

	set_dsi_timings(encoder, adjusted_mode);

	val = पूर्णांकel_dsi->lane_count << DATA_LANES_PRG_REG_SHIFT;
	अगर (is_cmd_mode(पूर्णांकel_dsi)) अणु
		val |= पूर्णांकel_dsi->channel << CMD_MODE_CHANNEL_NUMBER_SHIFT;
		val |= CMD_MODE_DATA_WIDTH_8_BIT; /* XXX */
	पूर्ण अन्यथा अणु
		val |= पूर्णांकel_dsi->channel << VID_MODE_CHANNEL_NUMBER_SHIFT;
		val |= pixel_क्रमmat_to_reg(पूर्णांकel_dsi->pixel_क्रमmat);
	पूर्ण

	पंचांगp = 0;
	अगर (पूर्णांकel_dsi->eotp_pkt == 0)
		पंचांगp |= EOT_DISABLE;
	अगर (पूर्णांकel_dsi->घड़ी_stop)
		पंचांगp |= CLOCKSTOP;

	अगर (IS_GEN9_LP(dev_priv)) अणु
		पंचांगp |= BXT_DPHY_DEFEATURE_EN;
		अगर (!is_cmd_mode(पूर्णांकel_dsi))
			पंचांगp |= BXT_DEFEATURE_DPI_FIFO_CTR;
	पूर्ण

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DSI_FUNC_PRG(port), val);

		/* समयouts क्रम recovery. one frame IIUC. अगर counter expires,
		 * EOT and stop state. */

		/*
		 * In burst mode, value greater than one DPI line Time in byte
		 * घड़ी (txbyteclkhs) To समयout this समयr 1+ of the above
		 * said value is recommended.
		 *
		 * In non-burst mode, Value greater than one DPI frame समय in
		 * byte घड़ी(txbyteclkhs) To समयout this समयr 1+ of the above
		 * said value is recommended.
		 *
		 * In DBI only mode, value greater than one DBI frame समय in
		 * byte घड़ी(txbyteclkhs) To समयout this समयr 1+ of the above
		 * said value is recommended.
		 */

		अगर (is_vid_mode(पूर्णांकel_dsi) &&
			पूर्णांकel_dsi->video_mode_क्रमmat == VIDEO_MODE_BURST) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_HS_TX_TIMEOUT(port),
				       txbyteclkhs(adjusted_mode->crtc_htotal, bpp, पूर्णांकel_dsi->lane_count, पूर्णांकel_dsi->burst_mode_ratio) + 1);
		पूर्ण अन्यथा अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_HS_TX_TIMEOUT(port),
				       txbyteclkhs(adjusted_mode->crtc_vtotal * adjusted_mode->crtc_htotal, bpp, पूर्णांकel_dsi->lane_count, पूर्णांकel_dsi->burst_mode_ratio) + 1);
		पूर्ण
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_LP_RX_TIMEOUT(port),
			       पूर्णांकel_dsi->lp_rx_समयout);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_TURN_AROUND_TIMEOUT(port),
			       पूर्णांकel_dsi->turn_arnd_val);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_RESET_TIMER(port),
			       पूर्णांकel_dsi->rst_समयr_val);

		/* dphy stuff */

		/* in terms of low घातer घड़ी */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_INIT_COUNT(port),
			       txclkesc(पूर्णांकel_dsi->escape_clk_भाग, 100));

		अगर (IS_GEN9_LP(dev_priv) && (!पूर्णांकel_dsi->dual_link)) अणु
			/*
			 * BXT spec says ग_लिखो MIPI_INIT_COUNT क्रम
			 * both the ports, even अगर only one is
			 * getting used. So ग_लिखो the other port
			 * अगर not in dual link mode.
			 */
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       MIPI_INIT_COUNT(port == PORT_A ? PORT_C : PORT_A),
				       पूर्णांकel_dsi->init_count);
		पूर्ण

		/* recovery disables */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_EOT_DISABLE(port), पंचांगp);

		/* in terms of low घातer घड़ी */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_INIT_COUNT(port),
			       पूर्णांकel_dsi->init_count);

		/* in terms of txbyteclkhs. actual high to low चयन +
		 * MIPI_STOP_STATE_STALL * MIPI_LP_BYTECLK.
		 *
		 * XXX: ग_लिखो MIPI_STOP_STATE_STALL?
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_HIGH_LOW_SWITCH_COUNT(port),
			       पूर्णांकel_dsi->hs_to_lp_count);

		/* XXX: low घातer घड़ी equivalence in terms of byte घड़ी.
		 * the number of byte घड़ीs occupied in one low घातer घड़ी.
		 * based on txbyteclkhs and txclkesc.
		 * txclkesc समय / txbyteclk समय * (105 + MIPI_STOP_STATE_STALL
		 * ) / 105.???
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_LP_BYTECLK(port),
			       पूर्णांकel_dsi->lp_byte_clk);

		अगर (IS_GEMINILAKE(dev_priv)) अणु
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_TLPX_TIME_COUNT(port),
				       पूर्णांकel_dsi->lp_byte_clk);
			/* Shaकरोw of DPHY reg */
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CLK_LANE_TIMING(port),
				       पूर्णांकel_dsi->dphy_reg);
		पूर्ण

		/* the bw essential क्रम transmitting 16 दीर्घ packets containing
		 * 252 bytes meant क्रम dcs ग_लिखो memory command is programmed in
		 * this रेजिस्टर in terms of byte घड़ीs. based on dsi transfer
		 * rate and the number of lanes configured the समय taken to
		 * transmit 16 दीर्घ packets in a dsi stream varies. */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DBI_BW_CTRL(port),
			       पूर्णांकel_dsi->bw_समयr);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_CLK_LANE_SWITCH_TIME_CNT(port),
			       पूर्णांकel_dsi->clk_lp_to_hs_count << LP_HS_SSW_CNT_SHIFT | पूर्णांकel_dsi->clk_hs_to_lp_count << HS_LP_PWR_SW_CNT_SHIFT);

		अगर (is_vid_mode(पूर्णांकel_dsi))
			/* Some panels might have resolution which is not a
			 * multiple of 64 like 1366 x 768. Enable RANDOM
			 * resolution support क्रम such panels by शेष */
			पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_VIDEO_MODE_FORMAT(port),
				       पूर्णांकel_dsi->video_frmt_cfg_bits | पूर्णांकel_dsi->video_mode_क्रमmat | IP_TG_CONFIG | RANDOM_DPI_DISPLAY_RESOLUTION);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_unprepare(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 val;

	अगर (IS_GEMINILAKE(dev_priv))
		वापस;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		/* Panel commands can be sent when घड़ी is in LP11 */
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), 0x0);

		अगर (IS_GEN9_LP(dev_priv))
			bxt_dsi_reset_घड़ीs(encoder, port);
		अन्यथा
			vlv_dsi_reset_घड़ीs(encoder, port);
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_EOT_DISABLE(port), CLOCKSTOP);

		val = पूर्णांकel_de_पढ़ो(dev_priv, MIPI_DSI_FUNC_PRG(port));
		val &= ~VID_MODE_FORMAT_MASK;
		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DSI_FUNC_PRG(port), val);

		पूर्णांकel_de_ग_लिखो(dev_priv, MIPI_DEVICE_READY(port), 0x1);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_dsi_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(to_पूर्णांकel_encoder(encoder));

	पूर्णांकel_dsi_vbt_gpio_cleanup(पूर्णांकel_dsi);
	पूर्णांकel_encoder_destroy(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs पूर्णांकel_dsi_funcs = अणु
	.destroy = पूर्णांकel_dsi_encoder_destroy,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_helper_funcs पूर्णांकel_dsi_connector_helper_funcs = अणु
	.get_modes = पूर्णांकel_dsi_get_modes,
	.mode_valid = पूर्णांकel_dsi_mode_valid,
	.atomic_check = पूर्णांकel_digital_connector_atomic_check,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs पूर्णांकel_dsi_connector_funcs = अणु
	.detect = पूर्णांकel_panel_detect,
	.late_रेजिस्टर = पूर्णांकel_connector_रेजिस्टर,
	.early_unरेजिस्टर = पूर्णांकel_connector_unरेजिस्टर,
	.destroy = पूर्णांकel_connector_destroy,
	.fill_modes = drm_helper_probe_single_connector_modes,
	.atomic_get_property = पूर्णांकel_digital_connector_atomic_get_property,
	.atomic_set_property = पूर्णांकel_digital_connector_atomic_set_property,
	.atomic_destroy_state = drm_atomic_helper_connector_destroy_state,
	.atomic_duplicate_state = पूर्णांकel_digital_connector_duplicate_state,
पूर्ण;

अटल व्योम vlv_dsi_add_properties(काष्ठा पूर्णांकel_connector *connector)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(connector->base.dev);

	अगर (connector->panel.fixed_mode) अणु
		u32 allowed_scalers;

		allowed_scalers = BIT(DRM_MODE_SCALE_ASPECT) | BIT(DRM_MODE_SCALE_FULLSCREEN);
		अगर (!HAS_GMCH(dev_priv))
			allowed_scalers |= BIT(DRM_MODE_SCALE_CENTER);

		drm_connector_attach_scaling_mode_property(&connector->base,
								allowed_scalers);

		connector->base.state->scaling_mode = DRM_MODE_SCALE_ASPECT;

		drm_connector_set_panel_orientation_with_quirk(
				&connector->base,
				पूर्णांकel_dsi_get_panel_orientation(connector),
				connector->panel.fixed_mode->hdisplay,
				connector->panel.fixed_mode->vdisplay);
	पूर्ण
पूर्ण

#घोषणा NS_KHZ_RATIO		1000000

#घोषणा PREPARE_CNT_MAX		0x3F
#घोषणा EXIT_ZERO_CNT_MAX	0x3F
#घोषणा CLK_ZERO_CNT_MAX	0xFF
#घोषणा TRAIL_CNT_MAX		0x1F

अटल व्योम vlv_dphy_param_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा mipi_config *mipi_config = dev_priv->vbt.dsi.config;
	u32 tlpx_ns, extra_byte_count, tlpx_ui;
	u32 ui_num, ui_den;
	u32 prepare_cnt, निकास_zero_cnt, clk_zero_cnt, trail_cnt;
	u32 ths_prepare_ns, tclk_trail_ns;
	u32 tclk_prepare_clkzero, ths_prepare_hszero;
	u32 lp_to_hs_चयन, hs_to_lp_चयन;
	u32 mul;

	tlpx_ns = पूर्णांकel_dsi_tlpx_ns(पूर्णांकel_dsi);

	चयन (पूर्णांकel_dsi->lane_count) अणु
	हाल 1:
	हाल 2:
		extra_byte_count = 2;
		अवरोध;
	हाल 3:
		extra_byte_count = 4;
		अवरोध;
	हाल 4:
	शेष:
		extra_byte_count = 3;
		अवरोध;
	पूर्ण

	/* in Kbps */
	ui_num = NS_KHZ_RATIO;
	ui_den = पूर्णांकel_dsi_bitrate(पूर्णांकel_dsi);

	tclk_prepare_clkzero = mipi_config->tclk_prepare_clkzero;
	ths_prepare_hszero = mipi_config->ths_prepare_hszero;

	/*
	 * B060
	 * LP byte घड़ी = TLPX/ (8UI)
	 */
	पूर्णांकel_dsi->lp_byte_clk = DIV_ROUND_UP(tlpx_ns * ui_den, 8 * ui_num);

	/* DDR घड़ी period = 2 * UI
	 * UI(sec) = 1/(bitrate * 10^3) (bitrate is in KHZ)
	 * UI(nsec) = 10^6 / bitrate
	 * DDR घड़ी period (nsec) = 2 * UI = (2 * 10^6)/ bitrate
	 * DDR घड़ी count  = ns_value / DDR घड़ी period
	 *
	 * For GEMINILAKE dphy_param_reg will be programmed in terms of
	 * HS byte घड़ी count क्रम other platक्रमm in HS ddr घड़ी count
	 */
	mul = IS_GEMINILAKE(dev_priv) ? 8 : 2;
	ths_prepare_ns = max(mipi_config->ths_prepare,
			     mipi_config->tclk_prepare);

	/* prepare count */
	prepare_cnt = DIV_ROUND_UP(ths_prepare_ns * ui_den, ui_num * mul);

	अगर (prepare_cnt > PREPARE_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm, "prepare count too high %u\n",
			    prepare_cnt);
		prepare_cnt = PREPARE_CNT_MAX;
	पूर्ण

	/* निकास zero count */
	निकास_zero_cnt = DIV_ROUND_UP(
				(ths_prepare_hszero - ths_prepare_ns) * ui_den,
				ui_num * mul
				);

	/*
	 * Exit zero is unअगरied val ths_zero and ths_निकास
	 * minimum value क्रम ths_निकास = 110ns
	 * min (निकास_zero_cnt * 2) = 110/UI
	 * निकास_zero_cnt = 55/UI
	 */
	अगर (निकास_zero_cnt < (55 * ui_den / ui_num) && (55 * ui_den) % ui_num)
		निकास_zero_cnt += 1;

	अगर (निकास_zero_cnt > EXIT_ZERO_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm, "exit zero count too high %u\n",
			    निकास_zero_cnt);
		निकास_zero_cnt = EXIT_ZERO_CNT_MAX;
	पूर्ण

	/* clk zero count */
	clk_zero_cnt = DIV_ROUND_UP(
				(tclk_prepare_clkzero -	ths_prepare_ns)
				* ui_den, ui_num * mul);

	अगर (clk_zero_cnt > CLK_ZERO_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm, "clock zero count too high %u\n",
			    clk_zero_cnt);
		clk_zero_cnt = CLK_ZERO_CNT_MAX;
	पूर्ण

	/* trail count */
	tclk_trail_ns = max(mipi_config->tclk_trail, mipi_config->ths_trail);
	trail_cnt = DIV_ROUND_UP(tclk_trail_ns * ui_den, ui_num * mul);

	अगर (trail_cnt > TRAIL_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm, "trail count too high %u\n",
			    trail_cnt);
		trail_cnt = TRAIL_CNT_MAX;
	पूर्ण

	/* B080 */
	पूर्णांकel_dsi->dphy_reg = निकास_zero_cnt << 24 | trail_cnt << 16 |
						clk_zero_cnt << 8 | prepare_cnt;

	/*
	 * LP to HS चयन count = 4TLPX + PREP_COUNT * mul + EXIT_ZERO_COUNT *
	 *					mul + 10UI + Extra Byte Count
	 *
	 * HS to LP चयन count = THS-TRAIL + 2TLPX + Extra Byte Count
	 * Extra Byte Count is calculated according to number of lanes.
	 * High Low Switch Count is the Max of LP to HS and
	 * HS to LP चयन count
	 *
	 */
	tlpx_ui = DIV_ROUND_UP(tlpx_ns * ui_den, ui_num);

	/* B044 */
	/* FIXME:
	 * The comment above करोes not match with the code */
	lp_to_hs_चयन = DIV_ROUND_UP(4 * tlpx_ui + prepare_cnt * mul +
						निकास_zero_cnt * mul + 10, 8);

	hs_to_lp_चयन = DIV_ROUND_UP(mipi_config->ths_trail + 2 * tlpx_ui, 8);

	पूर्णांकel_dsi->hs_to_lp_count = max(lp_to_hs_चयन, hs_to_lp_चयन);
	पूर्णांकel_dsi->hs_to_lp_count += extra_byte_count;

	/* B088 */
	/* LP -> HS क्रम घड़ी lanes
	 * LP clk sync + LP11 + LP01 + tclk_prepare + tclk_zero +
	 *						extra byte count
	 * 2TPLX + 1TLPX + 1 TPLX(in ns) + prepare_cnt * 2 + clk_zero_cnt *
	 *					2(in UI) + extra byte count
	 * In byteclks = (4TLPX + prepare_cnt * 2 + clk_zero_cnt *2 (in UI)) /
	 *					8 + extra byte count
	 */
	पूर्णांकel_dsi->clk_lp_to_hs_count =
		DIV_ROUND_UP(
			4 * tlpx_ui + prepare_cnt * 2 +
			clk_zero_cnt * 2,
			8);

	पूर्णांकel_dsi->clk_lp_to_hs_count += extra_byte_count;

	/* HS->LP क्रम Clock Lanes
	 * Low Power घड़ी synchronisations + 1Tx byteclk + tclk_trail +
	 *						Extra byte count
	 * 2TLPX + 8UI + (trail_count*2)(in UI) + Extra byte count
	 * In byteclks = (2*TLpx(in UI) + trail_count*2 +8)(in UI)/8 +
	 *						Extra byte count
	 */
	पूर्णांकel_dsi->clk_hs_to_lp_count =
		DIV_ROUND_UP(2 * tlpx_ui + trail_cnt * 2 + 8,
			8);
	पूर्णांकel_dsi->clk_hs_to_lp_count += extra_byte_count;

	पूर्णांकel_dsi_log_params(पूर्णांकel_dsi);
पूर्ण

व्योम vlv_dsi_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi;
	काष्ठा पूर्णांकel_encoder *पूर्णांकel_encoder;
	काष्ठा drm_encoder *encoder;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_display_mode *current_mode, *fixed_mode;
	क्रमागत port port;
	क्रमागत pipe pipe;

	drm_dbg_kms(&dev_priv->drm, "\n");

	/* There is no detection method क्रम MIPI so rely on VBT */
	अगर (!पूर्णांकel_bios_is_dsi_present(dev_priv, &port))
		वापस;

	अगर (IS_GEN9_LP(dev_priv))
		dev_priv->mipi_mmio_base = BXT_MIPI_BASE;
	अन्यथा
		dev_priv->mipi_mmio_base = VLV_MIPI_BASE;

	पूर्णांकel_dsi = kzalloc(माप(*पूर्णांकel_dsi), GFP_KERNEL);
	अगर (!पूर्णांकel_dsi)
		वापस;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector) अणु
		kमुक्त(पूर्णांकel_dsi);
		वापस;
	पूर्ण

	पूर्णांकel_encoder = &पूर्णांकel_dsi->base;
	encoder = &पूर्णांकel_encoder->base;
	पूर्णांकel_dsi->attached_connector = पूर्णांकel_connector;

	connector = &पूर्णांकel_connector->base;

	drm_encoder_init(dev, encoder, &पूर्णांकel_dsi_funcs, DRM_MODE_ENCODER_DSI,
			 "DSI %c", port_name(port));

	पूर्णांकel_encoder->compute_config = पूर्णांकel_dsi_compute_config;
	पूर्णांकel_encoder->pre_enable = पूर्णांकel_dsi_pre_enable;
	अगर (IS_GEN9_LP(dev_priv))
		पूर्णांकel_encoder->enable = bxt_dsi_enable;
	पूर्णांकel_encoder->disable = पूर्णांकel_dsi_disable;
	पूर्णांकel_encoder->post_disable = पूर्णांकel_dsi_post_disable;
	पूर्णांकel_encoder->get_hw_state = पूर्णांकel_dsi_get_hw_state;
	पूर्णांकel_encoder->get_config = पूर्णांकel_dsi_get_config;
	पूर्णांकel_encoder->update_pipe = पूर्णांकel_panel_update_backlight;
	पूर्णांकel_encoder->shutकरोwn = पूर्णांकel_dsi_shutकरोwn;

	पूर्णांकel_connector->get_hw_state = पूर्णांकel_connector_get_hw_state;

	पूर्णांकel_encoder->port = port;
	पूर्णांकel_encoder->type = INTEL_OUTPUT_DSI;
	पूर्णांकel_encoder->घातer_करोमुख्य = POWER_DOMAIN_PORT_DSI;
	पूर्णांकel_encoder->cloneable = 0;

	/*
	 * On BYT/CHV, pipe A maps to MIPI DSI port A, pipe B maps to MIPI DSI
	 * port C. BXT isn't limited like this.
	 */
	अगर (IS_GEN9_LP(dev_priv))
		पूर्णांकel_encoder->pipe_mask = ~0;
	अन्यथा अगर (port == PORT_A)
		पूर्णांकel_encoder->pipe_mask = BIT(PIPE_A);
	अन्यथा
		पूर्णांकel_encoder->pipe_mask = BIT(PIPE_B);

	अगर (dev_priv->vbt.dsi.config->dual_link)
		पूर्णांकel_dsi->ports = BIT(PORT_A) | BIT(PORT_C);
	अन्यथा
		पूर्णांकel_dsi->ports = BIT(port);

	पूर्णांकel_dsi->dcs_backlight_ports = dev_priv->vbt.dsi.bl_ports;
	पूर्णांकel_dsi->dcs_cabc_ports = dev_priv->vbt.dsi.cabc_ports;

	/* Create a DSI host (and a device) क्रम each port. */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		काष्ठा पूर्णांकel_dsi_host *host;

		host = पूर्णांकel_dsi_host_init(पूर्णांकel_dsi, &पूर्णांकel_dsi_host_ops,
					   port);
		अगर (!host)
			जाओ err;

		पूर्णांकel_dsi->dsi_hosts[port] = host;
	पूर्ण

	अगर (!पूर्णांकel_dsi_vbt_init(पूर्णांकel_dsi, MIPI_DSI_GENERIC_PANEL_ID)) अणु
		drm_dbg_kms(&dev_priv->drm, "no device found\n");
		जाओ err;
	पूर्ण

	/* Use घड़ी पढ़ो-back from current hw-state क्रम fastboot */
	current_mode = पूर्णांकel_encoder_current_mode(पूर्णांकel_encoder);
	अगर (current_mode) अणु
		drm_dbg_kms(&dev_priv->drm, "Calculated pclk %d GOP %d\n",
			    पूर्णांकel_dsi->pclk, current_mode->घड़ी);
		अगर (पूर्णांकel_fuzzy_घड़ी_check(पूर्णांकel_dsi->pclk,
					    current_mode->घड़ी)) अणु
			drm_dbg_kms(&dev_priv->drm, "Using GOP pclk\n");
			पूर्णांकel_dsi->pclk = current_mode->घड़ी;
		पूर्ण

		kमुक्त(current_mode);
	पूर्ण

	vlv_dphy_param_init(पूर्णांकel_dsi);

	पूर्णांकel_dsi_vbt_gpio_init(पूर्णांकel_dsi,
				पूर्णांकel_dsi_get_hw_state(पूर्णांकel_encoder, &pipe));

	drm_connector_init(dev, connector, &पूर्णांकel_dsi_connector_funcs,
			   DRM_MODE_CONNECTOR_DSI);

	drm_connector_helper_add(connector, &पूर्णांकel_dsi_connector_helper_funcs);

	connector->display_info.subpixel_order = SubPixelHorizontalRGB; /*XXX*/
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;

	पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, पूर्णांकel_encoder);

	mutex_lock(&dev->mode_config.mutex);
	fixed_mode = पूर्णांकel_panel_vbt_fixed_mode(पूर्णांकel_connector);
	mutex_unlock(&dev->mode_config.mutex);

	अगर (!fixed_mode) अणु
		drm_dbg_kms(&dev_priv->drm, "no fixed mode\n");
		जाओ err_cleanup_connector;
	पूर्ण

	पूर्णांकel_panel_init(&पूर्णांकel_connector->panel, fixed_mode, शून्य);
	पूर्णांकel_panel_setup_backlight(connector, INVALID_PIPE);

	vlv_dsi_add_properties(पूर्णांकel_connector);

	वापस;

err_cleanup_connector:
	drm_connector_cleanup(&पूर्णांकel_connector->base);
err:
	drm_encoder_cleanup(&पूर्णांकel_encoder->base);
	kमुक्त(पूर्णांकel_dsi);
	kमुक्त(पूर्णांकel_connector);
पूर्ण
