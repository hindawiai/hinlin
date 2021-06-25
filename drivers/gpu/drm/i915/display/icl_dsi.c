<शैली गुरु>
/*
 * Copyright तऊ 2018 Intel Corporation
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
 *   Madhav Chauhan <madhav.chauhan@पूर्णांकel.com>
 *   Jani Nikula <jani.nikula@पूर्णांकel.com>
 */

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_mipi_dsi.h>

#समावेश "intel_atomic.h"
#समावेश "intel_combo_phy.h"
#समावेश "intel_connector.h"
#समावेश "intel_ddi.h"
#समावेश "intel_dsi.h"
#समावेश "intel_panel.h"
#समावेश "intel_vdsc.h"
#समावेश "skl_scaler.h"
#समावेश "skl_universal_plane.h"

अटल पूर्णांक header_credits_available(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत transcoder dsi_trans)
अणु
	वापस (पूर्णांकel_de_पढ़ो(dev_priv, DSI_CMD_TXCTL(dsi_trans)) & FREE_HEADER_CREDIT_MASK)
		>> FREE_HEADER_CREDIT_SHIFT;
पूर्ण

अटल पूर्णांक payload_credits_available(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत transcoder dsi_trans)
अणु
	वापस (पूर्णांकel_de_पढ़ो(dev_priv, DSI_CMD_TXCTL(dsi_trans)) & FREE_PLOAD_CREDIT_MASK)
		>> FREE_PLOAD_CREDIT_SHIFT;
पूर्ण

अटल व्योम रुको_क्रम_header_credits(काष्ठा drm_i915_निजी *dev_priv,
				    क्रमागत transcoder dsi_trans)
अणु
	अगर (रुको_क्रम_us(header_credits_available(dev_priv, dsi_trans) >=
			MAX_HEADER_CREDIT, 100))
		drm_err(&dev_priv->drm, "DSI header credits not released\n");
पूर्ण

अटल व्योम रुको_क्रम_payload_credits(काष्ठा drm_i915_निजी *dev_priv,
				     क्रमागत transcoder dsi_trans)
अणु
	अगर (रुको_क्रम_us(payload_credits_available(dev_priv, dsi_trans) >=
			MAX_PLOAD_CREDIT, 100))
		drm_err(&dev_priv->drm, "DSI payload credits not released\n");
पूर्ण

अटल क्रमागत transcoder dsi_port_to_transcoder(क्रमागत port port)
अणु
	अगर (port == PORT_A)
		वापस TRANSCODER_DSI_0;
	अन्यथा
		वापस TRANSCODER_DSI_1;
पूर्ण

अटल व्योम रुको_क्रम_cmds_dispatched_to_panel(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा mipi_dsi_device *dsi;
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;
	पूर्णांक ret;

	/* रुको क्रम header/payload credits to be released */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		रुको_क्रम_header_credits(dev_priv, dsi_trans);
		रुको_क्रम_payload_credits(dev_priv, dsi_trans);
	पूर्ण

	/* send nop DCS command */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi = पूर्णांकel_dsi->dsi_hosts[port]->device;
		dsi->mode_flags |= MIPI_DSI_MODE_LPM;
		dsi->channel = 0;
		ret = mipi_dsi_dcs_nop(dsi);
		अगर (ret < 0)
			drm_err(&dev_priv->drm,
				"error sending DCS NOP command\n");
	पूर्ण

	/* रुको क्रम header credits to be released */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		रुको_क्रम_header_credits(dev_priv, dsi_trans);
	पूर्ण

	/* रुको क्रम LP TX in progress bit to be cleared */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		अगर (रुको_क्रम_us(!(पूर्णांकel_de_पढ़ो(dev_priv, DSI_LP_MSG(dsi_trans)) &
				  LPTX_IN_PROGRESS), 20))
			drm_err(&dev_priv->drm, "LPTX bit not cleared\n");
	पूर्ण
पूर्ण

अटल bool add_payld_to_queue(काष्ठा पूर्णांकel_dsi_host *host, स्थिर u8 *data,
			       u32 len)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = host->पूर्णांकel_dsi;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_dsi->base.base.dev);
	क्रमागत transcoder dsi_trans = dsi_port_to_transcoder(host->port);
	पूर्णांक मुक्त_credits;
	पूर्णांक i, j;

	क्रम (i = 0; i < len; i += 4) अणु
		u32 पंचांगp = 0;

		मुक्त_credits = payload_credits_available(dev_priv, dsi_trans);
		अगर (मुक्त_credits < 1) अणु
			drm_err(&dev_priv->drm,
				"Payload credit not available\n");
			वापस false;
		पूर्ण

		क्रम (j = 0; j < min_t(u32, len - i, 4); j++)
			पंचांगp |= *data++ << 8 * j;

		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_CMD_TXPYLD(dsi_trans), पंचांगp);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक dsi_send_pkt_hdr(काष्ठा पूर्णांकel_dsi_host *host,
			    काष्ठा mipi_dsi_packet pkt, bool enable_lpdt)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = host->पूर्णांकel_dsi;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(पूर्णांकel_dsi->base.base.dev);
	क्रमागत transcoder dsi_trans = dsi_port_to_transcoder(host->port);
	u32 पंचांगp;
	पूर्णांक मुक्त_credits;

	/* check अगर header credit available */
	मुक्त_credits = header_credits_available(dev_priv, dsi_trans);
	अगर (मुक्त_credits < 1) अणु
		drm_err(&dev_priv->drm,
			"send pkt header failed, not enough hdr credits\n");
		वापस -1;
	पूर्ण

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_CMD_TXHDR(dsi_trans));

	अगर (pkt.payload)
		पंचांगp |= PAYLOAD_PRESENT;
	अन्यथा
		पंचांगp &= ~PAYLOAD_PRESENT;

	पंचांगp &= ~VBLANK_FENCE;

	अगर (enable_lpdt)
		पंचांगp |= LP_DATA_TRANSFER;

	पंचांगp &= ~(PARAM_WC_MASK | VC_MASK | DT_MASK);
	पंचांगp |= ((pkt.header[0] & VC_MASK) << VC_SHIFT);
	पंचांगp |= ((pkt.header[0] & DT_MASK) << DT_SHIFT);
	पंचांगp |= (pkt.header[1] << PARAM_WC_LOWER_SHIFT);
	पंचांगp |= (pkt.header[2] << PARAM_WC_UPPER_SHIFT);
	पूर्णांकel_de_ग_लिखो(dev_priv, DSI_CMD_TXHDR(dsi_trans), पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_send_pkt_payld(काष्ठा पूर्णांकel_dsi_host *host,
			      काष्ठा mipi_dsi_packet pkt)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = host->पूर्णांकel_dsi;
	काष्ठा drm_i915_निजी *i915 = to_i915(पूर्णांकel_dsi->base.base.dev);

	/* payload queue can accept *256 bytes*, check limit */
	अगर (pkt.payload_length > MAX_PLOAD_CREDIT * 4) अणु
		drm_err(&i915->drm, "payload size exceeds max queue limit\n");
		वापस -1;
	पूर्ण

	/* load data पूर्णांकo command payload queue */
	अगर (!add_payld_to_queue(host, pkt.payload,
				pkt.payload_length)) अणु
		drm_err(&i915->drm, "adding payload to queue failed\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम icl_dsi_frame_update(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 पंचांगp, mode_flags;
	क्रमागत port port;

	mode_flags = crtc_state->mode_flags;

	/*
	 * हाल 1 also covers dual link
	 * In हाल of dual link, frame update should be set on
	 * DSI_0
	 */
	अगर (mode_flags & I915_MODE_FLAG_DSI_USE_TE0)
		port = PORT_A;
	अन्यथा अगर (mode_flags & I915_MODE_FLAG_DSI_USE_TE1)
		port = PORT_B;
	अन्यथा
		वापस;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_CMD_FRMCTL(port));
	पंचांगp |= DSI_FRAME_UPDATE_REQUEST;
	पूर्णांकel_de_ग_लिखो(dev_priv, DSI_CMD_FRMCTL(port), पंचांगp);
पूर्ण

अटल व्योम dsi_program_swing_and_deemphasis(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत phy phy;
	u32 पंचांगp;
	पूर्णांक lane;

	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		/*
		 * Program voltage swing and pre-emphasis level values as per
		 * table in BSPEC under DDI buffer programing
		 */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_LN0(phy));
		पंचांगp &= ~(SCALING_MODE_SEL_MASK | RTERM_SELECT_MASK);
		पंचांगp |= SCALING_MODE_SEL(0x2);
		पंचांगp |= TAP2_DISABLE | TAP3_DISABLE;
		पंचांगp |= RTERM_SELECT(0x6);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_GRP(phy), पंचांगp);

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_AUX(phy));
		पंचांगp &= ~(SCALING_MODE_SEL_MASK | RTERM_SELECT_MASK);
		पंचांगp |= SCALING_MODE_SEL(0x2);
		पंचांगp |= TAP2_DISABLE | TAP3_DISABLE;
		पंचांगp |= RTERM_SELECT(0x6);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_AUX(phy), पंचांगp);

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW2_LN0(phy));
		पंचांगp &= ~(SWING_SEL_LOWER_MASK | SWING_SEL_UPPER_MASK |
			 RCOMP_SCALAR_MASK);
		पंचांगp |= SWING_SEL_UPPER(0x2);
		पंचांगp |= SWING_SEL_LOWER(0x2);
		पंचांगp |= RCOMP_SCALAR(0x98);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW2_GRP(phy), पंचांगp);

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW2_AUX(phy));
		पंचांगp &= ~(SWING_SEL_LOWER_MASK | SWING_SEL_UPPER_MASK |
			 RCOMP_SCALAR_MASK);
		पंचांगp |= SWING_SEL_UPPER(0x2);
		पंचांगp |= SWING_SEL_LOWER(0x2);
		पंचांगp |= RCOMP_SCALAR(0x98);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW2_AUX(phy), पंचांगp);

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW4_AUX(phy));
		पंचांगp &= ~(POST_CURSOR_1_MASK | POST_CURSOR_2_MASK |
			 CURSOR_COEFF_MASK);
		पंचांगp |= POST_CURSOR_1(0x0);
		पंचांगp |= POST_CURSOR_2(0x0);
		पंचांगp |= CURSOR_COEFF(0x3f);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW4_AUX(phy), पंचांगp);

		क्रम (lane = 0; lane <= 3; lane++) अणु
			/* Bspec: must not use GRP रेजिस्टर क्रम ग_लिखो */
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
					    ICL_PORT_TX_DW4_LN(lane, phy));
			पंचांगp &= ~(POST_CURSOR_1_MASK | POST_CURSOR_2_MASK |
				 CURSOR_COEFF_MASK);
			पंचांगp |= POST_CURSOR_1(0x0);
			पंचांगp |= POST_CURSOR_2(0x0);
			पंचांगp |= CURSOR_COEFF(0x3f);
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_PORT_TX_DW4_LN(lane, phy), पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम configure_dual_link_mode(काष्ठा पूर्णांकel_encoder *encoder,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 dss_ctl1;

	dss_ctl1 = पूर्णांकel_de_पढ़ो(dev_priv, DSS_CTL1);
	dss_ctl1 |= SPLITTER_ENABLE;
	dss_ctl1 &= ~OVERLAP_PIXELS_MASK;
	dss_ctl1 |= OVERLAP_PIXELS(पूर्णांकel_dsi->pixel_overlap);

	अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK) अणु
		स्थिर काष्ठा drm_display_mode *adjusted_mode =
					&pipe_config->hw.adjusted_mode;
		u32 dss_ctl2;
		u16 hactive = adjusted_mode->crtc_hdisplay;
		u16 dl_buffer_depth;

		dss_ctl1 &= ~DUAL_LINK_MODE_INTERLEAVE;
		dl_buffer_depth = hactive / 2 + पूर्णांकel_dsi->pixel_overlap;

		अगर (dl_buffer_depth > MAX_DL_BUFFER_TARGET_DEPTH)
			drm_err(&dev_priv->drm,
				"DL buffer depth exceed max value\n");

		dss_ctl1 &= ~LEFT_DL_BUF_TARGET_DEPTH_MASK;
		dss_ctl1 |= LEFT_DL_BUF_TARGET_DEPTH(dl_buffer_depth);
		dss_ctl2 = पूर्णांकel_de_पढ़ो(dev_priv, DSS_CTL2);
		dss_ctl2 &= ~RIGHT_DL_BUF_TARGET_DEPTH_MASK;
		dss_ctl2 |= RIGHT_DL_BUF_TARGET_DEPTH(dl_buffer_depth);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSS_CTL2, dss_ctl2);
	पूर्ण अन्यथा अणु
		/* Interleave */
		dss_ctl1 |= DUAL_LINK_MODE_INTERLEAVE;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, DSS_CTL1, dss_ctl1);
पूर्ण

/* aka DSI 8X घड़ी */
अटल पूर्णांक afe_clk(काष्ठा पूर्णांकel_encoder *encoder,
		   स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	पूर्णांक bpp;

	अगर (crtc_state->dsc.compression_enable)
		bpp = crtc_state->dsc.compressed_bpp;
	अन्यथा
		bpp = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);

	वापस DIV_ROUND_CLOSEST(पूर्णांकel_dsi->pclk * bpp, पूर्णांकel_dsi->lane_count);
पूर्ण

अटल व्योम gen11_dsi_program_esc_clk_भाग(काष्ठा पूर्णांकel_encoder *encoder,
					  स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	पूर्णांक afe_clk_khz;
	u32 esc_clk_भाग_m;

	afe_clk_khz = afe_clk(encoder, crtc_state);
	esc_clk_भाग_m = DIV_ROUND_UP(afe_clk_khz, DSI_MAX_ESC_CLK);

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSI_ESC_CLK_DIV(port),
			       esc_clk_भाग_m & ICL_ESC_CLK_DIV_MASK);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, ICL_DSI_ESC_CLK_DIV(port));
	पूर्ण

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DPHY_ESC_CLK_DIV(port),
			       esc_clk_भाग_m & ICL_ESC_CLK_DIV_MASK);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, ICL_DPHY_ESC_CLK_DIV(port));
	पूर्ण
पूर्ण

अटल व्योम get_dsi_io_घातer_करोमुख्यs(काष्ठा drm_i915_निजी *dev_priv,
				     काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	क्रमागत port port;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		drm_WARN_ON(&dev_priv->drm, पूर्णांकel_dsi->io_wakeref[port]);
		पूर्णांकel_dsi->io_wakeref[port] =
			पूर्णांकel_display_घातer_get(dev_priv,
						port == PORT_A ?
						POWER_DOMAIN_PORT_DDI_A_IO :
						POWER_DOMAIN_PORT_DDI_B_IO);
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_enable_io_घातer(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 पंचांगp;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DSI_IO_MODECTL(port));
		पंचांगp |= COMBO_PHY_MODE_DSI;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSI_IO_MODECTL(port), पंचांगp);
	पूर्ण

	get_dsi_io_घातer_करोमुख्यs(dev_priv, पूर्णांकel_dsi);
पूर्ण

अटल व्योम gen11_dsi_घातer_up_lanes(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत phy phy;

	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys)
		पूर्णांकel_combo_phy_घातer_up_lanes(dev_priv, phy, true,
					       पूर्णांकel_dsi->lane_count, false);
पूर्ण

अटल व्योम gen11_dsi_config_phy_lanes_sequence(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत phy phy;
	u32 पंचांगp;
	पूर्णांक lane;

	/* Step 4b(i) set loadgen select क्रम transmit and aux lanes */
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW4_AUX(phy));
		पंचांगp &= ~LOADGEN_SELECT;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW4_AUX(phy), पंचांगp);
		क्रम (lane = 0; lane <= 3; lane++) अणु
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
					    ICL_PORT_TX_DW4_LN(lane, phy));
			पंचांगp &= ~LOADGEN_SELECT;
			अगर (lane != 2)
				पंचांगp |= LOADGEN_SELECT;
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       ICL_PORT_TX_DW4_LN(lane, phy), पंचांगp);
		पूर्ण
	पूर्ण

	/* Step 4b(ii) set latency optimization क्रम transmit and aux lanes */
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW2_AUX(phy));
		पंचांगp &= ~FRC_LATENCY_OPTIM_MASK;
		पंचांगp |= FRC_LATENCY_OPTIM_VAL(0x5);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW2_AUX(phy), पंचांगp);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW2_LN0(phy));
		पंचांगp &= ~FRC_LATENCY_OPTIM_MASK;
		पंचांगp |= FRC_LATENCY_OPTIM_VAL(0x5);
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW2_GRP(phy), पंचांगp);

		/* For EHL, TGL, set latency optimization क्रम PCS_DW1 lanes */
		अगर (IS_JSL_EHL(dev_priv) || (DISPLAY_VER(dev_priv) >= 12)) अणु
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
					    ICL_PORT_PCS_DW1_AUX(phy));
			पंचांगp &= ~LATENCY_OPTIM_MASK;
			पंचांगp |= LATENCY_OPTIM_VAL(0);
			पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_PCS_DW1_AUX(phy),
				       पंचांगp);

			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
					    ICL_PORT_PCS_DW1_LN0(phy));
			पंचांगp &= ~LATENCY_OPTIM_MASK;
			पंचांगp |= LATENCY_OPTIM_VAL(0x1);
			पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_PCS_DW1_GRP(phy),
				       पंचांगp);
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम gen11_dsi_voltage_swing_program_seq(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 पंचांगp;
	क्रमागत phy phy;

	/* clear common keeper enable bit */
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_PCS_DW1_LN0(phy));
		पंचांगp &= ~COMMON_KEEPER_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_PCS_DW1_GRP(phy), पंचांगp);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_PCS_DW1_AUX(phy));
		पंचांगp &= ~COMMON_KEEPER_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_PCS_DW1_AUX(phy), पंचांगp);
	पूर्ण

	/*
	 * Set SUS Clock Config bitfield to 11b
	 * Note: loadgen select program is करोne
	 * as part of lane phy sequence configuration
	 */
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_CL_DW5(phy));
		पंचांगp |= SUS_CLOCK_CONFIG;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_CL_DW5(phy), पंचांगp);
	पूर्ण

	/* Clear training enable to change swing values */
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_LN0(phy));
		पंचांगp &= ~TX_TRAINING_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_GRP(phy), पंचांगp);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_AUX(phy));
		पंचांगp &= ~TX_TRAINING_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_AUX(phy), पंचांगp);
	पूर्ण

	/* Program swing and de-emphasis */
	dsi_program_swing_and_deemphasis(encoder);

	/* Set training enable to trigger update */
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_LN0(phy));
		पंचांगp |= TX_TRAINING_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_GRP(phy), पंचांगp);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_PORT_TX_DW5_AUX(phy));
		पंचांगp |= TX_TRAINING_EN;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_PORT_TX_DW5_AUX(phy), पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_enable_ddi_buffer(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 पंचांगp;
	क्रमागत port port;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port));
		पंचांगp |= DDI_BUF_CTL_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(port), पंचांगp);

		अगर (रुको_क्रम_us(!(पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port)) &
				  DDI_BUF_IS_IDLE),
				  500))
			drm_err(&dev_priv->drm, "DDI port:%c buffer idle\n",
				port_name(port));
	पूर्ण
पूर्ण

अटल व्योम
gen11_dsi_setup_dphy_timings(काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 पंचांगp;
	क्रमागत port port;
	क्रमागत phy phy;

	/* Program T-INIT master रेजिस्टरs */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DSI_T_INIT_MASTER(port));
		पंचांगp &= ~MASTER_INIT_TIMER_MASK;
		पंचांगp |= पूर्णांकel_dsi->init_count;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSI_T_INIT_MASTER(port), पंचांगp);
	पूर्ण

	/* Program DPHY घड़ी lanes timings */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DPHY_CLK_TIMING_PARAM(port),
			       पूर्णांकel_dsi->dphy_reg);

		/* shaकरोw रेजिस्टर inside display core */
		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_CLK_TIMING_PARAM(port),
			       पूर्णांकel_dsi->dphy_reg);
	पूर्ण

	/* Program DPHY data lanes timings */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, DPHY_DATA_TIMING_PARAM(port),
			       पूर्णांकel_dsi->dphy_data_lane_reg);

		/* shaकरोw रेजिस्टर inside display core */
		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_DATA_TIMING_PARAM(port),
			       पूर्णांकel_dsi->dphy_data_lane_reg);
	पूर्ण

	/*
	 * If DSI link operating at or below an 800 MHz,
	 * TA_SURE should be override and programmed to
	 * a value '0' inside TA_PARAM_REGISTERS otherwise
	 * leave all fields at HW शेष values.
	 */
	अगर (IS_DISPLAY_VER(dev_priv, 11)) अणु
		अगर (afe_clk(encoder, crtc_state) <= 800000) अणु
			क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
				पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
						    DPHY_TA_TIMING_PARAM(port));
				पंचांगp &= ~TA_SURE_MASK;
				पंचांगp |= TA_SURE_OVERRIDE | TA_SURE(0);
				पूर्णांकel_de_ग_लिखो(dev_priv,
					       DPHY_TA_TIMING_PARAM(port),
					       पंचांगp);

				/* shaकरोw रेजिस्टर inside display core */
				पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
						    DSI_TA_TIMING_PARAM(port));
				पंचांगp &= ~TA_SURE_MASK;
				पंचांगp |= TA_SURE_OVERRIDE | TA_SURE(0);
				पूर्णांकel_de_ग_लिखो(dev_priv,
					       DSI_TA_TIMING_PARAM(port), पंचांगp);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (IS_JSL_EHL(dev_priv)) अणु
		क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DPHY_CHKN(phy));
			पंचांगp |= ICL_DPHY_CHKN_AFE_OVER_PPI_STRAP;
			पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DPHY_CHKN(phy), पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_gate_घड़ीs(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 पंचांगp;
	क्रमागत phy phy;

	mutex_lock(&dev_priv->dpll.lock);
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DPCLKA_CFGCR0);
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys)
		पंचांगp |= ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy);

	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DPCLKA_CFGCR0, पंचांगp);
	mutex_unlock(&dev_priv->dpll.lock);
पूर्ण

अटल व्योम gen11_dsi_ungate_घड़ीs(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 पंचांगp;
	क्रमागत phy phy;

	mutex_lock(&dev_priv->dpll.lock);
	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DPCLKA_CFGCR0);
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys)
		पंचांगp &= ~ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy);

	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DPCLKA_CFGCR0, पंचांगp);
	mutex_unlock(&dev_priv->dpll.lock);
पूर्ण

अटल bool gen11_dsi_is_घड़ी_enabled(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	bool घड़ी_enabled = false;
	क्रमागत phy phy;
	u32 पंचांगp;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DPCLKA_CFGCR0);

	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		अगर (!(पंचांगp & ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy)))
			घड़ी_enabled = true;
	पूर्ण

	वापस घड़ी_enabled;
पूर्ण

अटल व्योम gen11_dsi_map_pll(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा पूर्णांकel_shared_dpll *pll = crtc_state->shared_dpll;
	क्रमागत phy phy;
	u32 val;

	mutex_lock(&dev_priv->dpll.lock);

	val = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DPCLKA_CFGCR0);
	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		val &= ~ICL_DPCLKA_CFGCR0_DDI_CLK_SEL_MASK(phy);
		val |= ICL_DPCLKA_CFGCR0_DDI_CLK_SEL(pll->info->id, phy);
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DPCLKA_CFGCR0, val);

	क्रम_each_dsi_phy(phy, पूर्णांकel_dsi->phys) अणु
		अगर (DISPLAY_VER(dev_priv) >= 12)
			val |= ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy);
		अन्यथा
			val &= ~ICL_DPCLKA_CFGCR0_DDI_CLK_OFF(phy);
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DPCLKA_CFGCR0, val);

	पूर्णांकel_de_posting_पढ़ो(dev_priv, ICL_DPCLKA_CFGCR0);

	mutex_unlock(&dev_priv->dpll.lock);
पूर्ण

अटल व्योम
gen11_dsi_configure_transcoder(काष्ठा पूर्णांकel_encoder *encoder,
			       स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा पूर्णांकel_crtc *पूर्णांकel_crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	क्रमागत pipe pipe = पूर्णांकel_crtc->pipe;
	u32 पंचांगp;
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_TRANS_FUNC_CONF(dsi_trans));

		अगर (पूर्णांकel_dsi->eotp_pkt)
			पंचांगp &= ~EOTP_DISABLED;
		अन्यथा
			पंचांगp |= EOTP_DISABLED;

		/* enable link calibration अगर freq > 1.5Gbps */
		अगर (afe_clk(encoder, pipe_config) >= 1500 * 1000) अणु
			पंचांगp &= ~LINK_CALIBRATION_MASK;
			पंचांगp |= CALIBRATION_ENABLED_INITIAL_ONLY;
		पूर्ण

		/* configure continuous घड़ी */
		पंचांगp &= ~CONTINUOUS_CLK_MASK;
		अगर (पूर्णांकel_dsi->घड़ी_stop)
			पंचांगp |= CLK_ENTER_LP_AFTER_DATA;
		अन्यथा
			पंचांगp |= CLK_HS_CONTINUOUS;

		/* configure buffer threshold limit to minimum */
		पंचांगp &= ~PIX_BUF_THRESHOLD_MASK;
		पंचांगp |= PIX_BUF_THRESHOLD_1_4;

		/* set भव channel to '0' */
		पंचांगp &= ~PIX_VIRT_CHAN_MASK;
		पंचांगp |= PIX_VIRT_CHAN(0);

		/* program BGR transmission */
		अगर (पूर्णांकel_dsi->bgr_enabled)
			पंचांगp |= BGR_TRANSMISSION;

		/* select pixel क्रमmat */
		पंचांगp &= ~PIX_FMT_MASK;
		अगर (pipe_config->dsc.compression_enable) अणु
			पंचांगp |= PIX_FMT_COMPRESSED;
		पूर्ण अन्यथा अणु
			चयन (पूर्णांकel_dsi->pixel_क्रमmat) अणु
			शेष:
				MISSING_CASE(पूर्णांकel_dsi->pixel_क्रमmat);
				fallthrough;
			हाल MIPI_DSI_FMT_RGB565:
				पंचांगp |= PIX_FMT_RGB565;
				अवरोध;
			हाल MIPI_DSI_FMT_RGB666_PACKED:
				पंचांगp |= PIX_FMT_RGB666_PACKED;
				अवरोध;
			हाल MIPI_DSI_FMT_RGB666:
				पंचांगp |= PIX_FMT_RGB666_LOOSE;
				अवरोध;
			हाल MIPI_DSI_FMT_RGB888:
				पंचांगp |= PIX_FMT_RGB888;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (DISPLAY_VER(dev_priv) >= 12) अणु
			अगर (is_vid_mode(पूर्णांकel_dsi))
				पंचांगp |= BLANKING_PACKET_ENABLE;
		पूर्ण

		/* program DSI operation mode */
		अगर (is_vid_mode(पूर्णांकel_dsi)) अणु
			पंचांगp &= ~OP_MODE_MASK;
			चयन (पूर्णांकel_dsi->video_mode_क्रमmat) अणु
			शेष:
				MISSING_CASE(पूर्णांकel_dsi->video_mode_क्रमmat);
				fallthrough;
			हाल VIDEO_MODE_NON_BURST_WITH_SYNC_EVENTS:
				पंचांगp |= VIDEO_MODE_SYNC_EVENT;
				अवरोध;
			हाल VIDEO_MODE_NON_BURST_WITH_SYNC_PULSE:
				पंचांगp |= VIDEO_MODE_SYNC_PULSE;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * FIXME: Retrieve this info from VBT.
			 * As per the spec when dsi transcoder is operating
			 * in TE GATE mode, TE comes from GPIO
			 * which is UTIL PIN क्रम DSI 0.
			 * Also this GPIO would not be used क्रम other
			 * purposes is an assumption.
			 */
			पंचांगp &= ~OP_MODE_MASK;
			पंचांगp |= CMD_MODE_TE_GATE;
			पंचांगp |= TE_SOURCE_GPIO;
		पूर्ण

		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_TRANS_FUNC_CONF(dsi_trans), पंचांगp);
	पूर्ण

	/* enable port sync mode अगर dual link */
	अगर (पूर्णांकel_dsi->dual_link) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
			dsi_trans = dsi_port_to_transcoder(port);
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
					    TRANS_DDI_FUNC_CTL2(dsi_trans));
			पंचांगp |= PORT_SYNC_MODE_ENABLE;
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       TRANS_DDI_FUNC_CTL2(dsi_trans), पंचांगp);
		पूर्ण

		/* configure stream splitting */
		configure_dual_link_mode(encoder, pipe_config);
	पूर्ण

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);

		/* select data lane width */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(dsi_trans));
		पंचांगp &= ~DDI_PORT_WIDTH_MASK;
		पंचांगp |= DDI_PORT_WIDTH(पूर्णांकel_dsi->lane_count);

		/* select input pipe */
		पंचांगp &= ~TRANS_DDI_EDP_INPUT_MASK;
		चयन (pipe) अणु
		शेष:
			MISSING_CASE(pipe);
			fallthrough;
		हाल PIPE_A:
			पंचांगp |= TRANS_DDI_EDP_INPUT_A_ON;
			अवरोध;
		हाल PIPE_B:
			पंचांगp |= TRANS_DDI_EDP_INPUT_B_ONOFF;
			अवरोध;
		हाल PIPE_C:
			पंचांगp |= TRANS_DDI_EDP_INPUT_C_ONOFF;
			अवरोध;
		हाल PIPE_D:
			पंचांगp |= TRANS_DDI_EDP_INPUT_D_ONOFF;
			अवरोध;
		पूर्ण

		/* enable DDI buffer */
		पंचांगp |= TRANS_DDI_FUNC_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(dsi_trans), पंचांगp);
	पूर्ण

	/* रुको क्रम link पढ़ोy */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, DSI_TRANS_FUNC_CONF(dsi_trans)) &
				 LINK_READY), 2500))
			drm_err(&dev_priv->drm, "DSI link not ready\n");
	पूर्ण
पूर्ण

अटल व्योम
gen11_dsi_set_transcoder_timings(काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	स्थिर काष्ठा drm_display_mode *adjusted_mode =
		&crtc_state->hw.adjusted_mode;
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;
	/* horizontal timings */
	u16 htotal, hactive, hsync_start, hsync_end, hsync_size;
	u16 hback_porch;
	/* vertical timings */
	u16 vtotal, vactive, vsync_start, vsync_end, vsync_shअगरt;
	पूर्णांक mul = 1, भाग = 1;

	/*
	 * Adjust horizontal timings (htotal, hsync_start, hsync_end) to account
	 * क्रम slower link speed अगर DSC is enabled.
	 *
	 * The compression frequency ratio is the ratio between compressed and
	 * non-compressed link speeds, and simplअगरies करोwn to the ratio between
	 * compressed and non-compressed bpp.
	 */
	अगर (crtc_state->dsc.compression_enable) अणु
		mul = crtc_state->dsc.compressed_bpp;
		भाग = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);
	पूर्ण

	hactive = adjusted_mode->crtc_hdisplay;

	अगर (is_vid_mode(पूर्णांकel_dsi))
		htotal = DIV_ROUND_UP(adjusted_mode->crtc_htotal * mul, भाग);
	अन्यथा
		htotal = DIV_ROUND_UP((hactive + 160) * mul, भाग);

	hsync_start = DIV_ROUND_UP(adjusted_mode->crtc_hsync_start * mul, भाग);
	hsync_end = DIV_ROUND_UP(adjusted_mode->crtc_hsync_end * mul, भाग);
	hsync_size  = hsync_end - hsync_start;
	hback_porch = (adjusted_mode->crtc_htotal -
		       adjusted_mode->crtc_hsync_end);
	vactive = adjusted_mode->crtc_vdisplay;

	अगर (is_vid_mode(पूर्णांकel_dsi)) अणु
		vtotal = adjusted_mode->crtc_vtotal;
	पूर्ण अन्यथा अणु
		पूर्णांक bpp, line_समय_us, byte_clk_period_ns;

		अगर (crtc_state->dsc.compression_enable)
			bpp = crtc_state->dsc.compressed_bpp;
		अन्यथा
			bpp = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);

		byte_clk_period_ns = 1000000 / afe_clk(encoder, crtc_state);
		line_समय_us = (htotal * (bpp / 8) * byte_clk_period_ns) / (1000 * पूर्णांकel_dsi->lane_count);
		vtotal = vactive + DIV_ROUND_UP(400, line_समय_us);
	पूर्ण
	vsync_start = adjusted_mode->crtc_vsync_start;
	vsync_end = adjusted_mode->crtc_vsync_end;
	vsync_shअगरt = hsync_start - htotal / 2;

	अगर (पूर्णांकel_dsi->dual_link) अणु
		hactive /= 2;
		अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK)
			hactive += पूर्णांकel_dsi->pixel_overlap;
		htotal /= 2;
	पूर्ण

	/* minimum hactive as per bspec: 256 pixels */
	अगर (adjusted_mode->crtc_hdisplay < 256)
		drm_err(&dev_priv->drm, "hactive is less then 256 pixels\n");

	/* अगर RGB666 क्रमmat, then hactive must be multiple of 4 pixels */
	अगर (पूर्णांकel_dsi->pixel_क्रमmat == MIPI_DSI_FMT_RGB666 && hactive % 4 != 0)
		drm_err(&dev_priv->drm,
			"hactive pixels are not multiple of 4\n");

	/* program TRANS_HTOTAL रेजिस्टर */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		पूर्णांकel_de_ग_लिखो(dev_priv, HTOTAL(dsi_trans),
			       (hactive - 1) | ((htotal - 1) << 16));
	पूर्ण

	/* TRANS_HSYNC रेजिस्टर to be programmed only क्रम video mode */
	अगर (is_vid_mode(पूर्णांकel_dsi)) अणु
		अगर (पूर्णांकel_dsi->video_mode_क्रमmat ==
		    VIDEO_MODE_NON_BURST_WITH_SYNC_PULSE) अणु
			/* BSPEC: hsync size should be atleast 16 pixels */
			अगर (hsync_size < 16)
				drm_err(&dev_priv->drm,
					"hsync size < 16 pixels\n");
		पूर्ण

		अगर (hback_porch < 16)
			drm_err(&dev_priv->drm, "hback porch < 16 pixels\n");

		अगर (पूर्णांकel_dsi->dual_link) अणु
			hsync_start /= 2;
			hsync_end /= 2;
		पूर्ण

		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
			dsi_trans = dsi_port_to_transcoder(port);
			पूर्णांकel_de_ग_लिखो(dev_priv, HSYNC(dsi_trans),
				       (hsync_start - 1) | ((hsync_end - 1) << 16));
		पूर्ण
	पूर्ण

	/* program TRANS_VTOTAL रेजिस्टर */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		/*
		 * FIXME: Programing this by assuming progressive mode, since
		 * non-पूर्णांकerlaced info from VBT is not saved inside
		 * काष्ठा drm_display_mode.
		 * For पूर्णांकerlace mode: program required pixel minus 2
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, VTOTAL(dsi_trans),
			       (vactive - 1) | ((vtotal - 1) << 16));
	पूर्ण

	अगर (vsync_end < vsync_start || vsync_end > vtotal)
		drm_err(&dev_priv->drm, "Invalid vsync_end value\n");

	अगर (vsync_start < vactive)
		drm_err(&dev_priv->drm, "vsync_start less than vactive\n");

	/* program TRANS_VSYNC रेजिस्टर क्रम video mode only */
	अगर (is_vid_mode(पूर्णांकel_dsi)) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
			dsi_trans = dsi_port_to_transcoder(port);
			पूर्णांकel_de_ग_लिखो(dev_priv, VSYNC(dsi_trans),
				       (vsync_start - 1) | ((vsync_end - 1) << 16));
		पूर्ण
	पूर्ण

	/*
	 * FIXME: It has to be programmed only क्रम video modes and पूर्णांकerlaced
	 * modes. Put the check condition here once पूर्णांकerlaced
	 * info available as described above.
	 * program TRANS_VSYNCSHIFT रेजिस्टर
	 */
	अगर (is_vid_mode(पूर्णांकel_dsi)) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
			dsi_trans = dsi_port_to_transcoder(port);
			पूर्णांकel_de_ग_लिखो(dev_priv, VSYNCSHIFT(dsi_trans),
				       vsync_shअगरt);
		पूर्ण
	पूर्ण

	/* program TRANS_VBLANK रेजिस्टर, should be same as vtotal programmed */
	अगर (DISPLAY_VER(dev_priv) >= 12) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
			dsi_trans = dsi_port_to_transcoder(port);
			पूर्णांकel_de_ग_लिखो(dev_priv, VBLANK(dsi_trans),
				       (vactive - 1) | ((vtotal - 1) << 16));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_enable_transcoder(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;
	u32 पंचांगp;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(dsi_trans));
		पंचांगp |= PIPECONF_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(dsi_trans), पंचांगp);

		/* रुको क्रम transcoder to be enabled */
		अगर (पूर्णांकel_de_रुको_क्रम_set(dev_priv, PIPECONF(dsi_trans),
					  I965_PIPECONF_ACTIVE, 10))
			drm_err(&dev_priv->drm,
				"DSI transcoder not enabled\n");
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_setup_समयouts(काष्ठा पूर्णांकel_encoder *encoder,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;
	u32 पंचांगp, hs_tx_समयout, lp_rx_समयout, ta_समयout, भागisor, mul;

	/*
	 * escape घड़ी count calculation:
	 * BYTE_CLK_COUNT = TIME_NS/(8 * UI)
	 * UI (nsec) = (10^6)/Bitrate
	 * TIME_NS = (BYTE_CLK_COUNT * 8 * 10^6)/ Bitrate
	 * ESCAPE_CLK_COUNT  = TIME_NS/ESC_CLK_NS
	 */
	भागisor = पूर्णांकel_dsi_tlpx_ns(पूर्णांकel_dsi) * afe_clk(encoder, crtc_state) * 1000;
	mul = 8 * 1000000;
	hs_tx_समयout = DIV_ROUND_UP(पूर्णांकel_dsi->hs_tx_समयout * mul,
				     भागisor);
	lp_rx_समयout = DIV_ROUND_UP(पूर्णांकel_dsi->lp_rx_समयout * mul, भागisor);
	ta_समयout = DIV_ROUND_UP(पूर्णांकel_dsi->turn_arnd_val * mul, भागisor);

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);

		/* program hst_tx_समयout */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_HSTX_TO(dsi_trans));
		पंचांगp &= ~HSTX_TIMEOUT_VALUE_MASK;
		पंचांगp |= HSTX_TIMEOUT_VALUE(hs_tx_समयout);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_HSTX_TO(dsi_trans), पंचांगp);

		/* FIXME: DSI_CALIB_TO */

		/* program lp_rx_host समयout */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_LPRX_HOST_TO(dsi_trans));
		पंचांगp &= ~LPRX_TIMEOUT_VALUE_MASK;
		पंचांगp |= LPRX_TIMEOUT_VALUE(lp_rx_समयout);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_LPRX_HOST_TO(dsi_trans), पंचांगp);

		/* FIXME: DSI_PWAIT_TO */

		/* program turn around समयout */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_TA_TO(dsi_trans));
		पंचांगp &= ~TA_TIMEOUT_VALUE_MASK;
		पंचांगp |= TA_TIMEOUT_VALUE(ta_समयout);
		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_TA_TO(dsi_trans), पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_config_util_pin(काष्ठा पूर्णांकel_encoder *encoder,
				      bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 पंचांगp;

	/*
	 * used as TE i/p क्रम DSI0,
	 * क्रम dual link/DSI1 TE is from slave DSI1
	 * through GPIO.
	 */
	अगर (is_vid_mode(पूर्णांकel_dsi) || (पूर्णांकel_dsi->ports & BIT(PORT_B)))
		वापस;

	पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, UTIL_PIN_CTL);

	अगर (enable) अणु
		पंचांगp |= UTIL_PIN_सूचीECTION_INPUT;
		पंचांगp |= UTIL_PIN_ENABLE;
	पूर्ण अन्यथा अणु
		पंचांगp &= ~UTIL_PIN_ENABLE;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, UTIL_PIN_CTL, पंचांगp);
पूर्ण

अटल व्योम
gen11_dsi_enable_port_and_phy(काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);

	/* step 4a: घातer up all lanes of the DDI used by DSI */
	gen11_dsi_घातer_up_lanes(encoder);

	/* step 4b: configure lane sequencing of the Combo-PHY transmitters */
	gen11_dsi_config_phy_lanes_sequence(encoder);

	/* step 4c: configure voltage swing and skew */
	gen11_dsi_voltage_swing_program_seq(encoder);

	/* enable DDI buffer */
	gen11_dsi_enable_ddi_buffer(encoder);

	/* setup D-PHY timings */
	gen11_dsi_setup_dphy_timings(encoder, crtc_state);

	/* Since transcoder is configured to take events from GPIO */
	gen11_dsi_config_util_pin(encoder, true);

	/* step 4h: setup DSI protocol समयouts */
	gen11_dsi_setup_समयouts(encoder, crtc_state);

	/* Step (4h, 4i, 4j, 4k): Configure transcoder */
	gen11_dsi_configure_transcoder(encoder, crtc_state);

	/* Step 4l: Gate DDI घड़ीs */
	अगर (IS_DISPLAY_VER(dev_priv, 11))
		gen11_dsi_gate_घड़ीs(encoder);
पूर्ण

अटल व्योम gen11_dsi_घातerup_panel(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा mipi_dsi_device *dsi;
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;
	u32 पंचांगp;
	पूर्णांक ret;

	/* set maximum वापस packet size */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);

		/*
		 * FIXME: This uses the number of DW's currently in the payload
		 * receive queue. This is probably not what we want here.
		 */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_CMD_RXCTL(dsi_trans));
		पंचांगp &= NUMBER_RX_PLOAD_DW_MASK;
		/* multiply "Number Rx Payload DW" by 4 to get max value */
		पंचांगp = पंचांगp * 4;
		dsi = पूर्णांकel_dsi->dsi_hosts[port]->device;
		ret = mipi_dsi_set_maximum_वापस_packet_size(dsi, पंचांगp);
		अगर (ret < 0)
			drm_err(&dev_priv->drm,
				"error setting max return pkt size%d\n", पंचांगp);
	पूर्ण

	/* panel घातer on related mipi dsi vbt sequences */
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_POWER_ON);
	पूर्णांकel_dsi_msleep(पूर्णांकel_dsi, पूर्णांकel_dsi->panel_on_delay);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_DEASSERT_RESET);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_INIT_OTP);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_DISPLAY_ON);

	/* ensure all panel commands dispatched beक्रमe enabling transcoder */
	रुको_क्रम_cmds_dispatched_to_panel(encoder);
पूर्ण

अटल व्योम gen11_dsi_pre_pll_enable(काष्ठा पूर्णांकel_atomic_state *state,
				     काष्ठा पूर्णांकel_encoder *encoder,
				     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	/* step2: enable IO घातer */
	gen11_dsi_enable_io_घातer(encoder);

	/* step3: enable DSI PLL */
	gen11_dsi_program_esc_clk_भाग(encoder, crtc_state);
पूर्ण

अटल व्योम gen11_dsi_pre_enable(काष्ठा पूर्णांकel_atomic_state *state,
				 काष्ठा पूर्णांकel_encoder *encoder,
				 स्थिर काष्ठा पूर्णांकel_crtc_state *pipe_config,
				 स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	/* step3b */
	gen11_dsi_map_pll(encoder, pipe_config);

	/* step4: enable DSI port and DPHY */
	gen11_dsi_enable_port_and_phy(encoder, pipe_config);

	/* step5: program and घातerup panel */
	gen11_dsi_घातerup_panel(encoder);

	पूर्णांकel_dsc_enable(encoder, pipe_config);

	/* step6c: configure transcoder timings */
	gen11_dsi_set_transcoder_timings(encoder, pipe_config);
पूर्ण

अटल व्योम gen11_dsi_enable(काष्ठा पूर्णांकel_atomic_state *state,
			     काष्ठा पूर्णांकel_encoder *encoder,
			     स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			     स्थिर काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);

	drm_WARN_ON(state->base.dev, crtc_state->has_pch_encoder);

	/* step6d: enable dsi transcoder */
	gen11_dsi_enable_transcoder(encoder);

	/* step7: enable backlight */
	पूर्णांकel_panel_enable_backlight(crtc_state, conn_state);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_BACKLIGHT_ON);

	पूर्णांकel_crtc_vblank_on(crtc_state);
पूर्ण

अटल व्योम gen11_dsi_disable_transcoder(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;
	u32 पंचांगp;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);

		/* disable transcoder */
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(dsi_trans));
		पंचांगp &= ~PIPECONF_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(dsi_trans), पंचांगp);

		/* रुको क्रम transcoder to be disabled */
		अगर (पूर्णांकel_de_रुको_क्रम_clear(dev_priv, PIPECONF(dsi_trans),
					    I965_PIPECONF_ACTIVE, 50))
			drm_err(&dev_priv->drm,
				"DSI trancoder not disabled\n");
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_घातerकरोwn_panel(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);

	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_DISPLAY_OFF);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_ASSERT_RESET);
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_POWER_OFF);

	/* ensure cmds dispatched to panel */
	रुको_क्रम_cmds_dispatched_to_panel(encoder);
पूर्ण

अटल व्योम gen11_dsi_deconfigure_trancoder(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	क्रमागत transcoder dsi_trans;
	u32 पंचांगp;

	/* disable periodic update mode */
	अगर (is_cmd_mode(पूर्णांकel_dsi)) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_CMD_FRMCTL(port));
			पंचांगp &= ~DSI_PERIODIC_FRAME_UPDATE_ENABLE;
			पूर्णांकel_de_ग_लिखो(dev_priv, DSI_CMD_FRMCTL(port), पंचांगp);
		पूर्ण
	पूर्ण

	/* put dsi link in ULPS */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DSI_LP_MSG(dsi_trans));
		पंचांगp |= LINK_ENTER_ULPS;
		पंचांगp &= ~LINK_ULPS_TYPE_LP11;
		पूर्णांकel_de_ग_लिखो(dev_priv, DSI_LP_MSG(dsi_trans), पंचांगp);

		अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, DSI_LP_MSG(dsi_trans)) &
				 LINK_IN_ULPS),
				10))
			drm_err(&dev_priv->drm, "DSI link not in ULPS\n");
	पूर्ण

	/* disable ddi function */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(dsi_trans));
		पंचांगp &= ~TRANS_DDI_FUNC_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, TRANS_DDI_FUNC_CTL(dsi_trans), पंचांगp);
	पूर्ण

	/* disable port sync mode अगर dual link */
	अगर (पूर्णांकel_dsi->dual_link) अणु
		क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
			dsi_trans = dsi_port_to_transcoder(port);
			पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv,
					    TRANS_DDI_FUNC_CTL2(dsi_trans));
			पंचांगp &= ~PORT_SYNC_MODE_ENABLE;
			पूर्णांकel_de_ग_लिखो(dev_priv,
				       TRANS_DDI_FUNC_CTL2(dsi_trans), पंचांगp);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_disable_port(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	u32 पंचांगp;
	क्रमागत port port;

	gen11_dsi_ungate_घड़ीs(encoder);
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port));
		पंचांगp &= ~DDI_BUF_CTL_ENABLE;
		पूर्णांकel_de_ग_लिखो(dev_priv, DDI_BUF_CTL(port), पंचांगp);

		अगर (रुको_क्रम_us((पूर्णांकel_de_पढ़ो(dev_priv, DDI_BUF_CTL(port)) &
				 DDI_BUF_IS_IDLE),
				 8))
			drm_err(&dev_priv->drm,
				"DDI port:%c buffer not idle\n",
				port_name(port));
	पूर्ण
	gen11_dsi_gate_घड़ीs(encoder);
पूर्ण

अटल व्योम gen11_dsi_disable_io_घातer(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत port port;
	u32 पंचांगp;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पूर्णांकel_wakeref_t wakeref;

		wakeref = fetch_and_zero(&पूर्णांकel_dsi->io_wakeref[port]);
		पूर्णांकel_display_घातer_put(dev_priv,
					port == PORT_A ?
					POWER_DOMAIN_PORT_DDI_A_IO :
					POWER_DOMAIN_PORT_DDI_B_IO,
					wakeref);
	पूर्ण

	/* set mode to DDI */
	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, ICL_DSI_IO_MODECTL(port));
		पंचांगp &= ~COMBO_PHY_MODE_DSI;
		पूर्णांकel_de_ग_लिखो(dev_priv, ICL_DSI_IO_MODECTL(port), पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम gen11_dsi_disable(काष्ठा पूर्णांकel_atomic_state *state,
			      काष्ठा पूर्णांकel_encoder *encoder,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
			      स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);

	/* step1: turn off backlight */
	पूर्णांकel_dsi_vbt_exec_sequence(पूर्णांकel_dsi, MIPI_SEQ_BACKLIGHT_OFF);
	पूर्णांकel_panel_disable_backlight(old_conn_state);

	/* step2d,e: disable transcoder and रुको */
	gen11_dsi_disable_transcoder(encoder);

	/* step2f,g: घातerकरोwn panel */
	gen11_dsi_घातerकरोwn_panel(encoder);

	/* step2h,i,j: deconfig trancoder */
	gen11_dsi_deconfigure_trancoder(encoder);

	/* step3: disable port */
	gen11_dsi_disable_port(encoder);

	gen11_dsi_config_util_pin(encoder, false);

	/* step4: disable IO घातer */
	gen11_dsi_disable_io_घातer(encoder);
पूर्ण

अटल व्योम gen11_dsi_post_disable(काष्ठा पूर्णांकel_atomic_state *state,
				   काष्ठा पूर्णांकel_encoder *encoder,
				   स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state,
				   स्थिर काष्ठा drm_connector_state *old_conn_state)
अणु
	पूर्णांकel_crtc_vblank_off(old_crtc_state);

	पूर्णांकel_dsc_disable(old_crtc_state);

	skl_scaler_disable(old_crtc_state);
पूर्ण

अटल क्रमागत drm_mode_status gen11_dsi_mode_valid(काष्ठा drm_connector *connector,
						 काष्ठा drm_display_mode *mode)
अणु
	/* FIXME: DSC? */
	वापस पूर्णांकel_dsi_mode_valid(connector, mode);
पूर्ण

अटल व्योम gen11_dsi_get_timings(काष्ठा पूर्णांकel_encoder *encoder,
				  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	काष्ठा drm_display_mode *adjusted_mode =
					&pipe_config->hw.adjusted_mode;

	अगर (pipe_config->dsc.compressed_bpp) अणु
		पूर्णांक भाग = pipe_config->dsc.compressed_bpp;
		पूर्णांक mul = mipi_dsi_pixel_क्रमmat_to_bpp(पूर्णांकel_dsi->pixel_क्रमmat);

		adjusted_mode->crtc_htotal =
			DIV_ROUND_UP(adjusted_mode->crtc_htotal * mul, भाग);
		adjusted_mode->crtc_hsync_start =
			DIV_ROUND_UP(adjusted_mode->crtc_hsync_start * mul, भाग);
		adjusted_mode->crtc_hsync_end =
			DIV_ROUND_UP(adjusted_mode->crtc_hsync_end * mul, भाग);
	पूर्ण

	अगर (पूर्णांकel_dsi->dual_link) अणु
		adjusted_mode->crtc_hdisplay *= 2;
		अगर (पूर्णांकel_dsi->dual_link == DSI_DUAL_LINK_FRONT_BACK)
			adjusted_mode->crtc_hdisplay -=
						पूर्णांकel_dsi->pixel_overlap;
		adjusted_mode->crtc_htotal *= 2;
	पूर्ण
	adjusted_mode->crtc_hblank_start = adjusted_mode->crtc_hdisplay;
	adjusted_mode->crtc_hblank_end = adjusted_mode->crtc_htotal;

	अगर (पूर्णांकel_dsi->operation_mode == INTEL_DSI_VIDEO_MODE) अणु
		अगर (पूर्णांकel_dsi->dual_link) अणु
			adjusted_mode->crtc_hsync_start *= 2;
			adjusted_mode->crtc_hsync_end *= 2;
		पूर्ण
	पूर्ण
	adjusted_mode->crtc_vblank_start = adjusted_mode->crtc_vdisplay;
	adjusted_mode->crtc_vblank_end = adjusted_mode->crtc_vtotal;
पूर्ण

अटल bool gen11_dsi_is_periodic_cmd_mode(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत transcoder dsi_trans;
	u32 val;

	अगर (पूर्णांकel_dsi->ports == BIT(PORT_B))
		dsi_trans = TRANSCODER_DSI_1;
	अन्यथा
		dsi_trans = TRANSCODER_DSI_0;

	val = पूर्णांकel_de_पढ़ो(dev_priv, DSI_TRANS_FUNC_CONF(dsi_trans));
	वापस (val & DSI_PERIODIC_FRAME_UPDATE_ENABLE);
पूर्ण

अटल व्योम gen11_dsi_get_cmd_mode_config(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
					  काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	अगर (पूर्णांकel_dsi->ports == (BIT(PORT_B) | BIT(PORT_A)))
		pipe_config->mode_flags |= I915_MODE_FLAG_DSI_USE_TE1 |
					    I915_MODE_FLAG_DSI_USE_TE0;
	अन्यथा अगर (पूर्णांकel_dsi->ports == BIT(PORT_B))
		pipe_config->mode_flags |= I915_MODE_FLAG_DSI_USE_TE1;
	अन्यथा
		pipe_config->mode_flags |= I915_MODE_FLAG_DSI_USE_TE0;
पूर्ण

अटल व्योम gen11_dsi_get_config(काष्ठा पूर्णांकel_encoder *encoder,
				 काष्ठा पूर्णांकel_crtc_state *pipe_config)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(pipe_config->uapi.crtc);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);

	पूर्णांकel_ddi_get_घड़ी(encoder, pipe_config, icl_ddi_combo_get_pll(encoder));

	pipe_config->hw.adjusted_mode.crtc_घड़ी = पूर्णांकel_dsi->pclk;
	अगर (पूर्णांकel_dsi->dual_link)
		pipe_config->hw.adjusted_mode.crtc_घड़ी *= 2;

	gen11_dsi_get_timings(encoder, pipe_config);
	pipe_config->output_types |= BIT(INTEL_OUTPUT_DSI);
	pipe_config->pipe_bpp = bdw_get_pipemisc_bpp(crtc);

	/* Get the details on which TE should be enabled */
	अगर (is_cmd_mode(पूर्णांकel_dsi))
		gen11_dsi_get_cmd_mode_config(पूर्णांकel_dsi, pipe_config);

	अगर (gen11_dsi_is_periodic_cmd_mode(पूर्णांकel_dsi))
		pipe_config->mode_flags |= I915_MODE_FLAG_DSI_PERIODIC_CMD_MODE;
पूर्ण

अटल पूर्णांक gen11_dsi_dsc_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
					काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा drm_dsc_config *vdsc_cfg = &crtc_state->dsc.config;
	पूर्णांक dsc_max_bpc = DISPLAY_VER(dev_priv) >= 12 ? 12 : 10;
	bool use_dsc;
	पूर्णांक ret;

	use_dsc = पूर्णांकel_bios_get_dsc_params(encoder, crtc_state, dsc_max_bpc);
	अगर (!use_dsc)
		वापस 0;

	अगर (crtc_state->pipe_bpp < 8 * 3)
		वापस -EINVAL;

	/* FIXME: split only when necessary */
	अगर (crtc_state->dsc.slice_count > 1)
		crtc_state->dsc.dsc_split = true;

	vdsc_cfg->convert_rgb = true;

	/* FIXME: initialize from VBT */
	vdsc_cfg->rc_model_size = DSC_RC_MODEL_SIZE_CONST;

	ret = पूर्णांकel_dsc_compute_params(encoder, crtc_state);
	अगर (ret)
		वापस ret;

	/* DSI specअगरic sanity checks on the common code */
	drm_WARN_ON(&dev_priv->drm, vdsc_cfg->vbr_enable);
	drm_WARN_ON(&dev_priv->drm, vdsc_cfg->simple_422);
	drm_WARN_ON(&dev_priv->drm,
		    vdsc_cfg->pic_width % vdsc_cfg->slice_width);
	drm_WARN_ON(&dev_priv->drm, vdsc_cfg->slice_height < 8);
	drm_WARN_ON(&dev_priv->drm,
		    vdsc_cfg->pic_height % vdsc_cfg->slice_height);

	ret = drm_dsc_compute_rc_parameters(vdsc_cfg);
	अगर (ret)
		वापस ret;

	crtc_state->dsc.compression_enable = true;

	वापस 0;
पूर्ण

अटल पूर्णांक gen11_dsi_compute_config(काष्ठा पूर्णांकel_encoder *encoder,
				    काष्ठा पूर्णांकel_crtc_state *pipe_config,
				    काष्ठा drm_connector_state *conn_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = container_of(encoder, काष्ठा पूर्णांकel_dsi,
						   base);
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector = पूर्णांकel_dsi->attached_connector;
	स्थिर काष्ठा drm_display_mode *fixed_mode =
		पूर्णांकel_connector->panel.fixed_mode;
	काष्ठा drm_display_mode *adjusted_mode =
		&pipe_config->hw.adjusted_mode;
	पूर्णांक ret;

	pipe_config->output_क्रमmat = INTEL_OUTPUT_FORMAT_RGB;
	पूर्णांकel_fixed_panel_mode(fixed_mode, adjusted_mode);

	ret = पूर्णांकel_pch_panel_fitting(pipe_config, conn_state);
	अगर (ret)
		वापस ret;

	adjusted_mode->flags = 0;

	/* Dual link goes to trancoder DSI'0' */
	अगर (पूर्णांकel_dsi->ports == BIT(PORT_B))
		pipe_config->cpu_transcoder = TRANSCODER_DSI_1;
	अन्यथा
		pipe_config->cpu_transcoder = TRANSCODER_DSI_0;

	अगर (पूर्णांकel_dsi->pixel_क्रमmat == MIPI_DSI_FMT_RGB888)
		pipe_config->pipe_bpp = 24;
	अन्यथा
		pipe_config->pipe_bpp = 18;

	pipe_config->घड़ी_set = true;

	अगर (gen11_dsi_dsc_compute_config(encoder, pipe_config))
		drm_dbg_kms(&i915->drm, "Attempting to use DSC failed\n");

	pipe_config->port_घड़ी = afe_clk(encoder, pipe_config) / 5;

	/*
	 * In हाल of TE GATE cmd mode, we
	 * receive TE from the slave अगर
	 * dual link is enabled
	 */
	अगर (is_cmd_mode(पूर्णांकel_dsi))
		gen11_dsi_get_cmd_mode_config(पूर्णांकel_dsi, pipe_config);

	वापस 0;
पूर्ण

अटल व्योम gen11_dsi_get_घातer_करोमुख्यs(काष्ठा पूर्णांकel_encoder *encoder,
					काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(encoder->base.dev);

	get_dsi_io_घातer_करोमुख्यs(i915,
				 enc_to_पूर्णांकel_dsi(encoder));
पूर्ण

अटल bool gen11_dsi_get_hw_state(काष्ठा पूर्णांकel_encoder *encoder,
				   क्रमागत pipe *pipe)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(encoder->base.dev);
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi = enc_to_पूर्णांकel_dsi(encoder);
	क्रमागत transcoder dsi_trans;
	पूर्णांकel_wakeref_t wakeref;
	क्रमागत port port;
	bool ret = false;
	u32 पंचांगp;

	wakeref = पूर्णांकel_display_घातer_get_अगर_enabled(dev_priv,
						     encoder->घातer_करोमुख्य);
	अगर (!wakeref)
		वापस false;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		dsi_trans = dsi_port_to_transcoder(port);
		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, TRANS_DDI_FUNC_CTL(dsi_trans));
		चयन (पंचांगp & TRANS_DDI_EDP_INPUT_MASK) अणु
		हाल TRANS_DDI_EDP_INPUT_A_ON:
			*pipe = PIPE_A;
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_B_ONOFF:
			*pipe = PIPE_B;
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_C_ONOFF:
			*pipe = PIPE_C;
			अवरोध;
		हाल TRANS_DDI_EDP_INPUT_D_ONOFF:
			*pipe = PIPE_D;
			अवरोध;
		शेष:
			drm_err(&dev_priv->drm, "Invalid PIPE input\n");
			जाओ out;
		पूर्ण

		पंचांगp = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(dsi_trans));
		ret = पंचांगp & PIPECONF_ENABLE;
	पूर्ण
out:
	पूर्णांकel_display_घातer_put(dev_priv, encoder->घातer_करोमुख्य, wakeref);
	वापस ret;
पूर्ण

अटल bool gen11_dsi_initial_fastset_check(काष्ठा पूर्णांकel_encoder *encoder,
					    काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (crtc_state->dsc.compression_enable) अणु
		drm_dbg_kms(encoder->base.dev, "Forcing full modeset due to DSC being enabled\n");
		crtc_state->uapi.mode_changed = true;

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम gen11_dsi_encoder_destroy(काष्ठा drm_encoder *encoder)
अणु
	पूर्णांकel_encoder_destroy(encoder);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_funcs gen11_dsi_encoder_funcs = अणु
	.destroy = gen11_dsi_encoder_destroy,
पूर्ण;

अटल स्थिर काष्ठा drm_connector_funcs gen11_dsi_connector_funcs = अणु
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

अटल स्थिर काष्ठा drm_connector_helper_funcs gen11_dsi_connector_helper_funcs = अणु
	.get_modes = पूर्णांकel_dsi_get_modes,
	.mode_valid = gen11_dsi_mode_valid,
	.atomic_check = पूर्णांकel_digital_connector_atomic_check,
पूर्ण;

अटल पूर्णांक gen11_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				 काष्ठा mipi_dsi_device *dsi)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक gen11_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				 काष्ठा mipi_dsi_device *dsi)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार gen11_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				       स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा पूर्णांकel_dsi_host *पूर्णांकel_dsi_host = to_पूर्णांकel_dsi_host(host);
	काष्ठा mipi_dsi_packet dsi_pkt;
	sमाप_प्रकार ret;
	bool enable_lpdt = false;

	ret = mipi_dsi_create_packet(&dsi_pkt, msg);
	अगर (ret < 0)
		वापस ret;

	अगर (msg->flags & MIPI_DSI_MSG_USE_LPM)
		enable_lpdt = true;

	/* send packet header */
	ret  = dsi_send_pkt_hdr(पूर्णांकel_dsi_host, dsi_pkt, enable_lpdt);
	अगर (ret < 0)
		वापस ret;

	/* only दीर्घ packet contains payload */
	अगर (mipi_dsi_packet_क्रमmat_is_दीर्घ(msg->type)) अणु
		ret = dsi_send_pkt_payld(पूर्णांकel_dsi_host, dsi_pkt);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	//TODO: add payload receive code अगर needed

	ret = माप(dsi_pkt.header) + dsi_pkt.payload_length;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops gen11_dsi_host_ops = अणु
	.attach = gen11_dsi_host_attach,
	.detach = gen11_dsi_host_detach,
	.transfer = gen11_dsi_host_transfer,
पूर्ण;

#घोषणा ICL_PREPARE_CNT_MAX	0x7
#घोषणा ICL_CLK_ZERO_CNT_MAX	0xf
#घोषणा ICL_TRAIL_CNT_MAX	0x7
#घोषणा ICL_TCLK_PRE_CNT_MAX	0x3
#घोषणा ICL_TCLK_POST_CNT_MAX	0x7
#घोषणा ICL_HS_ZERO_CNT_MAX	0xf
#घोषणा ICL_EXIT_ZERO_CNT_MAX	0x7

अटल व्योम icl_dphy_param_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	काष्ठा drm_device *dev = पूर्णांकel_dsi->base.base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा mipi_config *mipi_config = dev_priv->vbt.dsi.config;
	u32 tlpx_ns;
	u32 prepare_cnt, निकास_zero_cnt, clk_zero_cnt, trail_cnt;
	u32 ths_prepare_ns, tclk_trail_ns;
	u32 hs_zero_cnt;
	u32 tclk_pre_cnt, tclk_post_cnt;

	tlpx_ns = पूर्णांकel_dsi_tlpx_ns(पूर्णांकel_dsi);

	tclk_trail_ns = max(mipi_config->tclk_trail, mipi_config->ths_trail);
	ths_prepare_ns = max(mipi_config->ths_prepare,
			     mipi_config->tclk_prepare);

	/*
	 * prepare cnt in escape घड़ीs
	 * this field represents a hexadecimal value with a precision
	 * of 1.2 ै  i.e. the most signअगरicant bit is the पूर्णांकeger
	 * and the least signअगरicant 2 bits are fraction bits.
	 * so, the field can represent a range of 0.25 to 1.75
	 */
	prepare_cnt = DIV_ROUND_UP(ths_prepare_ns * 4, tlpx_ns);
	अगर (prepare_cnt > ICL_PREPARE_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm, "prepare_cnt out of range (%d)\n",
			    prepare_cnt);
		prepare_cnt = ICL_PREPARE_CNT_MAX;
	पूर्ण

	/* clk zero count in escape घड़ीs */
	clk_zero_cnt = DIV_ROUND_UP(mipi_config->tclk_prepare_clkzero -
				    ths_prepare_ns, tlpx_ns);
	अगर (clk_zero_cnt > ICL_CLK_ZERO_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "clk_zero_cnt out of range (%d)\n", clk_zero_cnt);
		clk_zero_cnt = ICL_CLK_ZERO_CNT_MAX;
	पूर्ण

	/* trail cnt in escape घड़ीs*/
	trail_cnt = DIV_ROUND_UP(tclk_trail_ns, tlpx_ns);
	अगर (trail_cnt > ICL_TRAIL_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm, "trail_cnt out of range (%d)\n",
			    trail_cnt);
		trail_cnt = ICL_TRAIL_CNT_MAX;
	पूर्ण

	/* tclk pre count in escape घड़ीs */
	tclk_pre_cnt = DIV_ROUND_UP(mipi_config->tclk_pre, tlpx_ns);
	अगर (tclk_pre_cnt > ICL_TCLK_PRE_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "tclk_pre_cnt out of range (%d)\n", tclk_pre_cnt);
		tclk_pre_cnt = ICL_TCLK_PRE_CNT_MAX;
	पूर्ण

	/* tclk post count in escape घड़ीs */
	tclk_post_cnt = DIV_ROUND_UP(mipi_config->tclk_post, tlpx_ns);
	अगर (tclk_post_cnt > ICL_TCLK_POST_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "tclk_post_cnt out of range (%d)\n",
			    tclk_post_cnt);
		tclk_post_cnt = ICL_TCLK_POST_CNT_MAX;
	पूर्ण

	/* hs zero cnt in escape घड़ीs */
	hs_zero_cnt = DIV_ROUND_UP(mipi_config->ths_prepare_hszero -
				   ths_prepare_ns, tlpx_ns);
	अगर (hs_zero_cnt > ICL_HS_ZERO_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm, "hs_zero_cnt out of range (%d)\n",
			    hs_zero_cnt);
		hs_zero_cnt = ICL_HS_ZERO_CNT_MAX;
	पूर्ण

	/* hs निकास zero cnt in escape घड़ीs */
	निकास_zero_cnt = DIV_ROUND_UP(mipi_config->ths_निकास, tlpx_ns);
	अगर (निकास_zero_cnt > ICL_EXIT_ZERO_CNT_MAX) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "exit_zero_cnt out of range (%d)\n",
			    निकास_zero_cnt);
		निकास_zero_cnt = ICL_EXIT_ZERO_CNT_MAX;
	पूर्ण

	/* घड़ी lane dphy timings */
	पूर्णांकel_dsi->dphy_reg = (CLK_PREPARE_OVERRIDE |
			       CLK_PREPARE(prepare_cnt) |
			       CLK_ZERO_OVERRIDE |
			       CLK_ZERO(clk_zero_cnt) |
			       CLK_PRE_OVERRIDE |
			       CLK_PRE(tclk_pre_cnt) |
			       CLK_POST_OVERRIDE |
			       CLK_POST(tclk_post_cnt) |
			       CLK_TRAIL_OVERRIDE |
			       CLK_TRAIL(trail_cnt));

	/* data lanes dphy timings */
	पूर्णांकel_dsi->dphy_data_lane_reg = (HS_PREPARE_OVERRIDE |
					 HS_PREPARE(prepare_cnt) |
					 HS_ZERO_OVERRIDE |
					 HS_ZERO(hs_zero_cnt) |
					 HS_TRAIL_OVERRIDE |
					 HS_TRAIL(trail_cnt) |
					 HS_EXIT_OVERRIDE |
					 HS_EXIT(निकास_zero_cnt));

	पूर्णांकel_dsi_log_params(पूर्णांकel_dsi);
पूर्ण

अटल व्योम icl_dsi_add_properties(काष्ठा पूर्णांकel_connector *connector)
अणु
	u32 allowed_scalers;

	allowed_scalers = BIT(DRM_MODE_SCALE_ASPECT) |
			   BIT(DRM_MODE_SCALE_FULLSCREEN) |
			   BIT(DRM_MODE_SCALE_CENTER);

	drm_connector_attach_scaling_mode_property(&connector->base,
						   allowed_scalers);

	connector->base.state->scaling_mode = DRM_MODE_SCALE_ASPECT;

	drm_connector_set_panel_orientation_with_quirk(&connector->base,
				पूर्णांकel_dsi_get_panel_orientation(connector),
				connector->panel.fixed_mode->hdisplay,
				connector->panel.fixed_mode->vdisplay);
पूर्ण

व्योम icl_dsi_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा drm_device *dev = &dev_priv->drm;
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi;
	काष्ठा पूर्णांकel_encoder *encoder;
	काष्ठा पूर्णांकel_connector *पूर्णांकel_connector;
	काष्ठा drm_connector *connector;
	काष्ठा drm_display_mode *fixed_mode;
	क्रमागत port port;

	अगर (!पूर्णांकel_bios_is_dsi_present(dev_priv, &port))
		वापस;

	पूर्णांकel_dsi = kzalloc(माप(*पूर्णांकel_dsi), GFP_KERNEL);
	अगर (!पूर्णांकel_dsi)
		वापस;

	पूर्णांकel_connector = पूर्णांकel_connector_alloc();
	अगर (!पूर्णांकel_connector) अणु
		kमुक्त(पूर्णांकel_dsi);
		वापस;
	पूर्ण

	encoder = &पूर्णांकel_dsi->base;
	पूर्णांकel_dsi->attached_connector = पूर्णांकel_connector;
	connector = &पूर्णांकel_connector->base;

	/* रेजिस्टर DSI encoder with DRM subप्रणाली */
	drm_encoder_init(dev, &encoder->base, &gen11_dsi_encoder_funcs,
			 DRM_MODE_ENCODER_DSI, "DSI %c", port_name(port));

	encoder->pre_pll_enable = gen11_dsi_pre_pll_enable;
	encoder->pre_enable = gen11_dsi_pre_enable;
	encoder->enable = gen11_dsi_enable;
	encoder->disable = gen11_dsi_disable;
	encoder->post_disable = gen11_dsi_post_disable;
	encoder->port = port;
	encoder->get_config = gen11_dsi_get_config;
	encoder->update_pipe = पूर्णांकel_panel_update_backlight;
	encoder->compute_config = gen11_dsi_compute_config;
	encoder->get_hw_state = gen11_dsi_get_hw_state;
	encoder->initial_fastset_check = gen11_dsi_initial_fastset_check;
	encoder->type = INTEL_OUTPUT_DSI;
	encoder->cloneable = 0;
	encoder->pipe_mask = ~0;
	encoder->घातer_करोमुख्य = POWER_DOMAIN_PORT_DSI;
	encoder->get_घातer_करोमुख्यs = gen11_dsi_get_घातer_करोमुख्यs;
	encoder->disable_घड़ी = gen11_dsi_gate_घड़ीs;
	encoder->is_घड़ी_enabled = gen11_dsi_is_घड़ी_enabled;

	/* रेजिस्टर DSI connector with DRM subप्रणाली */
	drm_connector_init(dev, connector, &gen11_dsi_connector_funcs,
			   DRM_MODE_CONNECTOR_DSI);
	drm_connector_helper_add(connector, &gen11_dsi_connector_helper_funcs);
	connector->display_info.subpixel_order = SubPixelHorizontalRGB;
	connector->पूर्णांकerlace_allowed = false;
	connector->द्विगुनscan_allowed = false;
	पूर्णांकel_connector->get_hw_state = पूर्णांकel_connector_get_hw_state;

	/* attach connector to encoder */
	पूर्णांकel_connector_attach_encoder(पूर्णांकel_connector, encoder);

	mutex_lock(&dev->mode_config.mutex);
	fixed_mode = पूर्णांकel_panel_vbt_fixed_mode(पूर्णांकel_connector);
	mutex_unlock(&dev->mode_config.mutex);

	अगर (!fixed_mode) अणु
		drm_err(&dev_priv->drm, "DSI fixed mode info missing\n");
		जाओ err;
	पूर्ण

	पूर्णांकel_panel_init(&पूर्णांकel_connector->panel, fixed_mode, शून्य);
	पूर्णांकel_panel_setup_backlight(connector, INVALID_PIPE);

	अगर (dev_priv->vbt.dsi.config->dual_link)
		पूर्णांकel_dsi->ports = BIT(PORT_A) | BIT(PORT_B);
	अन्यथा
		पूर्णांकel_dsi->ports = BIT(port);

	पूर्णांकel_dsi->dcs_backlight_ports = dev_priv->vbt.dsi.bl_ports;
	पूर्णांकel_dsi->dcs_cabc_ports = dev_priv->vbt.dsi.cabc_ports;

	क्रम_each_dsi_port(port, पूर्णांकel_dsi->ports) अणु
		काष्ठा पूर्णांकel_dsi_host *host;

		host = पूर्णांकel_dsi_host_init(पूर्णांकel_dsi, &gen11_dsi_host_ops, port);
		अगर (!host)
			जाओ err;

		पूर्णांकel_dsi->dsi_hosts[port] = host;
	पूर्ण

	अगर (!पूर्णांकel_dsi_vbt_init(पूर्णांकel_dsi, MIPI_DSI_GENERIC_PANEL_ID)) अणु
		drm_dbg_kms(&dev_priv->drm, "no device found\n");
		जाओ err;
	पूर्ण

	icl_dphy_param_init(पूर्णांकel_dsi);

	icl_dsi_add_properties(पूर्णांकel_connector);
	वापस;

err:
	drm_connector_cleanup(connector);
	drm_encoder_cleanup(&encoder->base);
	kमुक्त(पूर्णांकel_dsi);
	kमुक्त(पूर्णांकel_connector);
पूर्ण
