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
 */

#अगर_अघोषित _INTEL_DSI_H
#घोषणा _INTEL_DSI_H

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_mipi_dsi.h>

#समावेश "intel_display_types.h"

#घोषणा INTEL_DSI_VIDEO_MODE	0
#घोषणा INTEL_DSI_COMMAND_MODE	1

/* Dual Link support */
#घोषणा DSI_DUAL_LINK_NONE		0
#घोषणा DSI_DUAL_LINK_FRONT_BACK	1
#घोषणा DSI_DUAL_LINK_PIXEL_ALT		2

काष्ठा पूर्णांकel_dsi_host;

काष्ठा पूर्णांकel_dsi अणु
	काष्ठा पूर्णांकel_encoder base;

	काष्ठा पूर्णांकel_dsi_host *dsi_hosts[I915_MAX_PORTS];
	पूर्णांकel_wakeref_t io_wakeref[I915_MAX_PORTS];

	/* GPIO Desc क्रम panel and backlight control */
	काष्ठा gpio_desc *gpio_panel;
	काष्ठा gpio_desc *gpio_backlight;

	काष्ठा पूर्णांकel_connector *attached_connector;

	/* bit mask of ports (vlv dsi) or phys (icl dsi) being driven */
	जोड़ अणु
		u16 ports;	/* VLV DSI */
		u16 phys;	/* ICL DSI */
	पूर्ण;

	/* अगर true, use HS mode, otherwise LP */
	bool hs;

	/* भव channel */
	पूर्णांक channel;

	/* Video mode or command mode */
	u16 operation_mode;

	/* number of DSI lanes */
	अचिन्हित पूर्णांक lane_count;

	/* i2c bus associated with the slave device */
	पूर्णांक i2c_bus_num;

	/*
	 * video mode pixel क्रमmat
	 *
	 * XXX: consolidate on .क्रमmat in काष्ठा mipi_dsi_device.
	 */
	क्रमागत mipi_dsi_pixel_क्रमmat pixel_क्रमmat;

	/* video mode क्रमmat क्रम MIPI_VIDEO_MODE_FORMAT रेजिस्टर */
	u32 video_mode_क्रमmat;

	/* eot क्रम MIPI_EOT_DISABLE रेजिस्टर */
	u8 eotp_pkt;
	u8 घड़ी_stop;

	u8 escape_clk_भाग;
	u8 dual_link;

	u16 dcs_backlight_ports;
	u16 dcs_cabc_ports;

	/* RGB or BGR */
	bool bgr_enabled;

	u8 pixel_overlap;
	u32 port_bits;
	u32 bw_समयr;
	u32 dphy_reg;

	/* data lanes dphy timing */
	u32 dphy_data_lane_reg;
	u32 video_frmt_cfg_bits;
	u16 lp_byte_clk;

	/* समयouts in byte घड़ीs */
	u16 hs_tx_समयout;
	u16 lp_rx_समयout;
	u16 turn_arnd_val;
	u16 rst_समयr_val;
	u16 hs_to_lp_count;
	u16 clk_lp_to_hs_count;
	u16 clk_hs_to_lp_count;

	u16 init_count;
	u32 pclk;
	u16 burst_mode_ratio;

	/* all delays in ms */
	u16 backlight_off_delay;
	u16 backlight_on_delay;
	u16 panel_on_delay;
	u16 panel_off_delay;
	u16 panel_pwr_cycle_delay;
पूर्ण;

काष्ठा पूर्णांकel_dsi_host अणु
	काष्ठा mipi_dsi_host base;
	काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi;
	क्रमागत port port;

	/* our little hack */
	काष्ठा mipi_dsi_device *device;
पूर्ण;

अटल अंतरभूत काष्ठा पूर्णांकel_dsi_host *to_पूर्णांकel_dsi_host(काष्ठा mipi_dsi_host *h)
अणु
	वापस container_of(h, काष्ठा पूर्णांकel_dsi_host, base);
पूर्ण

#घोषणा क्रम_each_dsi_port(__port, __ports_mask) \
	क्रम_each_port_masked(__port, __ports_mask)
#घोषणा क्रम_each_dsi_phy(__phy, __phys_mask) \
	क्रम_each_phy_masked(__phy, __phys_mask)

अटल अंतरभूत काष्ठा पूर्णांकel_dsi *enc_to_पूर्णांकel_dsi(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस container_of(&encoder->base, काष्ठा पूर्णांकel_dsi, base.base);
पूर्ण

अटल अंतरभूत bool is_vid_mode(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	वापस पूर्णांकel_dsi->operation_mode == INTEL_DSI_VIDEO_MODE;
पूर्ण

अटल अंतरभूत bool is_cmd_mode(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi)
अणु
	वापस पूर्णांकel_dsi->operation_mode == INTEL_DSI_COMMAND_MODE;
पूर्ण

अटल अंतरभूत u16 पूर्णांकel_dsi_encoder_ports(काष्ठा पूर्णांकel_encoder *encoder)
अणु
	वापस enc_to_पूर्णांकel_dsi(encoder)->ports;
पूर्ण

/* icl_dsi.c */
व्योम icl_dsi_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम icl_dsi_frame_update(काष्ठा पूर्णांकel_crtc_state *crtc_state);

/* पूर्णांकel_dsi.c */
पूर्णांक पूर्णांकel_dsi_bitrate(स्थिर काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi);
पूर्णांक पूर्णांकel_dsi_tlpx_ns(स्थिर काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi);
क्रमागत drm_panel_orientation
पूर्णांकel_dsi_get_panel_orientation(काष्ठा पूर्णांकel_connector *connector);

/* vlv_dsi.c */
व्योम vlv_dsi_रुको_क्रम_fअगरo_empty(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, क्रमागत port port);
क्रमागत mipi_dsi_pixel_क्रमmat pixel_क्रमmat_from_रेजिस्टर_bits(u32 fmt);
पूर्णांक पूर्णांकel_dsi_get_modes(काष्ठा drm_connector *connector);
क्रमागत drm_mode_status पूर्णांकel_dsi_mode_valid(काष्ठा drm_connector *connector,
					  काष्ठा drm_display_mode *mode);
काष्ठा पूर्णांकel_dsi_host *पूर्णांकel_dsi_host_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
					   स्थिर काष्ठा mipi_dsi_host_ops *funcs,
					   क्रमागत port port);
व्योम vlv_dsi_init(काष्ठा drm_i915_निजी *dev_priv);

/* vlv_dsi_pll.c */
पूर्णांक vlv_dsi_pll_compute(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *config);
व्योम vlv_dsi_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *config);
व्योम vlv_dsi_pll_disable(काष्ठा पूर्णांकel_encoder *encoder);
u32 vlv_dsi_get_pclk(काष्ठा पूर्णांकel_encoder *encoder,
		     काष्ठा पूर्णांकel_crtc_state *config);
व्योम vlv_dsi_reset_घड़ीs(काष्ठा पूर्णांकel_encoder *encoder, क्रमागत port port);

bool bxt_dsi_pll_is_enabled(काष्ठा drm_i915_निजी *dev_priv);
पूर्णांक bxt_dsi_pll_compute(काष्ठा पूर्णांकel_encoder *encoder,
			काष्ठा पूर्णांकel_crtc_state *config);
व्योम bxt_dsi_pll_enable(काष्ठा पूर्णांकel_encoder *encoder,
			स्थिर काष्ठा पूर्णांकel_crtc_state *config);
व्योम bxt_dsi_pll_disable(काष्ठा पूर्णांकel_encoder *encoder);
u32 bxt_dsi_get_pclk(काष्ठा पूर्णांकel_encoder *encoder,
		     काष्ठा पूर्णांकel_crtc_state *config);
व्योम bxt_dsi_reset_घड़ीs(काष्ठा पूर्णांकel_encoder *encoder, क्रमागत port port);

/* पूर्णांकel_dsi_vbt.c */
bool पूर्णांकel_dsi_vbt_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, u16 panel_id);
व्योम पूर्णांकel_dsi_vbt_gpio_init(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, bool panel_is_on);
व्योम पूर्णांकel_dsi_vbt_gpio_cleanup(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi);
व्योम पूर्णांकel_dsi_vbt_exec_sequence(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi,
				 क्रमागत mipi_seq seq_id);
व्योम पूर्णांकel_dsi_msleep(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi, पूर्णांक msec);
व्योम पूर्णांकel_dsi_log_params(काष्ठा पूर्णांकel_dsi *पूर्णांकel_dsi);

#पूर्ण_अगर /* _INTEL_DSI_H */
