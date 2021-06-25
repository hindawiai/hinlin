<शैली गुरु>
/*
 * Copyright तऊ 2016-2019 Intel Corporation
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
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Please use पूर्णांकel_vbt_defs.h क्रम VBT निजी data, to hide and असलtract away
 * the VBT from the rest of the driver. Add the parsed, clean data to काष्ठा
 * पूर्णांकel_vbt_data within काष्ठा drm_i915_निजी.
 */

#अगर_अघोषित _INTEL_BIOS_H_
#घोषणा _INTEL_BIOS_H_

#समावेश <linux/types.h>

काष्ठा drm_i915_निजी;
काष्ठा पूर्णांकel_bios_encoder_data;
काष्ठा पूर्णांकel_crtc_state;
काष्ठा पूर्णांकel_encoder;
क्रमागत port;

क्रमागत पूर्णांकel_backlight_type अणु
	INTEL_BACKLIGHT_PMIC,
	INTEL_BACKLIGHT_LPSS,
	INTEL_BACKLIGHT_DISPLAY_DDI,
	INTEL_BACKLIGHT_DSI_DCS,
	INTEL_BACKLIGHT_PANEL_DRIVER_INTERFACE,
	INTEL_BACKLIGHT_VESA_EDP_AUX_INTERFACE,
पूर्ण;

काष्ठा edp_घातer_seq अणु
	u16 t1_t3;
	u16 t8;
	u16 t9;
	u16 t10;
	u16 t11_t12;
पूर्ण __packed;

/*
 * MIPI Sequence Block definitions
 *
 * Note the VBT spec has AssertReset / Deनिश्चितReset swapped from their
 * usual naming, we use the proper names here to aव्योम confusion when
 * पढ़ोing the code.
 */
क्रमागत mipi_seq अणु
	MIPI_SEQ_END = 0,
	MIPI_SEQ_DEASSERT_RESET,	/* Spec says MipiAssertResetPin */
	MIPI_SEQ_INIT_OTP,
	MIPI_SEQ_DISPLAY_ON,
	MIPI_SEQ_DISPLAY_OFF,
	MIPI_SEQ_ASSERT_RESET,		/* Spec says MipiDeनिश्चितResetPin */
	MIPI_SEQ_BACKLIGHT_ON,		/* sequence block v2+ */
	MIPI_SEQ_BACKLIGHT_OFF,		/* sequence block v2+ */
	MIPI_SEQ_TEAR_ON,		/* sequence block v2+ */
	MIPI_SEQ_TEAR_OFF,		/* sequence block v3+ */
	MIPI_SEQ_POWER_ON,		/* sequence block v3+ */
	MIPI_SEQ_POWER_OFF,		/* sequence block v3+ */
	MIPI_SEQ_MAX
पूर्ण;

क्रमागत mipi_seq_element अणु
	MIPI_SEQ_ELEM_END = 0,
	MIPI_SEQ_ELEM_SEND_PKT,
	MIPI_SEQ_ELEM_DELAY,
	MIPI_SEQ_ELEM_GPIO,
	MIPI_SEQ_ELEM_I2C,		/* sequence block v2+ */
	MIPI_SEQ_ELEM_SPI,		/* sequence block v3+ */
	MIPI_SEQ_ELEM_PMIC,		/* sequence block v3+ */
	MIPI_SEQ_ELEM_MAX
पूर्ण;

#घोषणा MIPI_DSI_UNDEFINED_PANEL_ID	0
#घोषणा MIPI_DSI_GENERIC_PANEL_ID	1

काष्ठा mipi_config अणु
	u16 panel_id;

	/* General Params */
	u32 enable_dithering:1;
	u32 rsvd1:1;
	u32 is_bridge:1;

	u32 panel_arch_type:2;
	u32 is_cmd_mode:1;

#घोषणा NON_BURST_SYNC_PULSE	0x1
#घोषणा NON_BURST_SYNC_EVENTS	0x2
#घोषणा BURST_MODE		0x3
	u32 video_transfer_mode:2;

	u32 cabc_supported:1;
#घोषणा PPS_BLC_PMIC   0
#घोषणा PPS_BLC_SOC    1
	u32 pwm_blc:1;

	/* Bit 13:10 */
#घोषणा PIXEL_FORMAT_RGB565			0x1
#घोषणा PIXEL_FORMAT_RGB666			0x2
#घोषणा PIXEL_FORMAT_RGB666_LOOSELY_PACKED	0x3
#घोषणा PIXEL_FORMAT_RGB888			0x4
	u32 videomode_color_क्रमmat:4;

	/* Bit 15:14 */
#घोषणा ENABLE_ROTATION_0	0x0
#घोषणा ENABLE_ROTATION_90	0x1
#घोषणा ENABLE_ROTATION_180	0x2
#घोषणा ENABLE_ROTATION_270	0x3
	u32 rotation:2;
	u32 bta_enabled:1;
	u32 rsvd2:15;

	/* 2 byte Port Description */
#घोषणा DUAL_LINK_NOT_SUPPORTED	0
#घोषणा DUAL_LINK_FRONT_BACK	1
#घोषणा DUAL_LINK_PIXEL_ALT	2
	u16 dual_link:2;
	u16 lane_cnt:2;
	u16 pixel_overlap:3;
	u16 rgb_flip:1;
#घोषणा DL_DCS_PORT_A			0x00
#घोषणा DL_DCS_PORT_C			0x01
#घोषणा DL_DCS_PORT_A_AND_C		0x02
	u16 dl_dcs_cabc_ports:2;
	u16 dl_dcs_backlight_ports:2;
	u16 rsvd3:4;

	u16 rsvd4;

	u8 rsvd5;
	u32 target_burst_mode_freq;
	u32 dsi_ddr_clk;
	u32 bridge_ref_clk;

#घोषणा  BYTE_CLK_SEL_20MHZ		0
#घोषणा  BYTE_CLK_SEL_10MHZ		1
#घोषणा  BYTE_CLK_SEL_5MHZ		2
	u8 byte_clk_sel:2;

	u8 rsvd6:6;

	/* DPHY Flags */
	u16 dphy_param_valid:1;
	u16 eot_pkt_disabled:1;
	u16 enable_clk_stop:1;
	u16 rsvd7:13;

	u32 hs_tx_समयout;
	u32 lp_rx_समयout;
	u32 turn_around_समयout;
	u32 device_reset_समयr;
	u32 master_init_समयr;
	u32 dbi_bw_समयr;
	u32 lp_byte_clk_val;

	/*  4 byte Dphy Params */
	u32 prepare_cnt:6;
	u32 rsvd8:2;
	u32 clk_zero_cnt:8;
	u32 trail_cnt:5;
	u32 rsvd9:3;
	u32 निकास_zero_cnt:6;
	u32 rsvd10:2;

	u32 clk_lane_चयन_cnt;
	u32 hl_चयन_cnt;

	u32 rsvd11[6];

	/* timings based on dphy spec */
	u8 tclk_miss;
	u8 tclk_post;
	u8 rsvd12;
	u8 tclk_pre;
	u8 tclk_prepare;
	u8 tclk_settle;
	u8 tclk_term_enable;
	u8 tclk_trail;
	u16 tclk_prepare_clkzero;
	u8 rsvd13;
	u8 td_term_enable;
	u8 teot;
	u8 ths_निकास;
	u8 ths_prepare;
	u16 ths_prepare_hszero;
	u8 rsvd14;
	u8 ths_settle;
	u8 ths_skip;
	u8 ths_trail;
	u8 tinit;
	u8 tlpx;
	u8 rsvd15[3];

	/* GPIOs */
	u8 panel_enable;
	u8 bl_enable;
	u8 pwm_enable;
	u8 reset_r_n;
	u8 pwr_करोwn_r;
	u8 stdby_r_n;

पूर्ण __packed;

/* all delays have a unit of 100us */
काष्ठा mipi_pps_data अणु
	u16 panel_on_delay;
	u16 bl_enable_delay;
	u16 bl_disable_delay;
	u16 panel_off_delay;
	u16 panel_घातer_cycle_delay;
पूर्ण __packed;

व्योम पूर्णांकel_bios_init(काष्ठा drm_i915_निजी *dev_priv);
व्योम पूर्णांकel_bios_driver_हटाओ(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_bios_is_valid_vbt(स्थिर व्योम *buf, माप_प्रकार size);
bool पूर्णांकel_bios_is_tv_present(काष्ठा drm_i915_निजी *dev_priv);
bool पूर्णांकel_bios_is_lvds_present(काष्ठा drm_i915_निजी *dev_priv, u8 *i2c_pin);
bool पूर्णांकel_bios_is_port_present(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port);
bool पूर्णांकel_bios_is_port_edp(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port);
bool पूर्णांकel_bios_is_port_dp_dual_mode(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port);
bool पूर्णांकel_bios_is_dsi_present(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port *port);
bool पूर्णांकel_bios_is_port_hpd_inverted(स्थिर काष्ठा drm_i915_निजी *i915,
				     क्रमागत port port);
bool पूर्णांकel_bios_is_lspcon_present(स्थिर काष्ठा drm_i915_निजी *i915,
				  क्रमागत port port);
bool पूर्णांकel_bios_is_lane_reversal_needed(स्थिर काष्ठा drm_i915_निजी *i915,
					क्रमागत port port);
क्रमागत aux_ch पूर्णांकel_bios_port_aux_ch(काष्ठा drm_i915_निजी *dev_priv, क्रमागत port port);
bool पूर्णांकel_bios_get_dsc_params(काष्ठा पूर्णांकel_encoder *encoder,
			       काष्ठा पूर्णांकel_crtc_state *crtc_state,
			       पूर्णांक dsc_max_bpc);
पूर्णांक पूर्णांकel_bios_max_पंचांगds_घड़ी(काष्ठा पूर्णांकel_encoder *encoder);
पूर्णांक पूर्णांकel_bios_hdmi_level_shअगरt(काष्ठा पूर्णांकel_encoder *encoder);
पूर्णांक पूर्णांकel_bios_dp_max_link_rate(काष्ठा पूर्णांकel_encoder *encoder);
पूर्णांक पूर्णांकel_bios_alternate_ddc_pin(काष्ठा पूर्णांकel_encoder *encoder);
bool पूर्णांकel_bios_port_supports_typec_usb(काष्ठा drm_i915_निजी *i915, क्रमागत port port);
bool पूर्णांकel_bios_port_supports_tbt(काष्ठा drm_i915_निजी *i915, क्रमागत port port);

स्थिर काष्ठा पूर्णांकel_bios_encoder_data *
पूर्णांकel_bios_encoder_data_lookup(काष्ठा drm_i915_निजी *i915, क्रमागत port port);

bool पूर्णांकel_bios_encoder_supports_dvi(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata);
bool पूर्णांकel_bios_encoder_supports_hdmi(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata);
bool पूर्णांकel_bios_encoder_supports_dp(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata);
bool पूर्णांकel_bios_encoder_supports_typec_usb(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata);
bool पूर्णांकel_bios_encoder_supports_tbt(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata);
पूर्णांक पूर्णांकel_bios_encoder_dp_boost_level(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata);
पूर्णांक पूर्णांकel_bios_encoder_hdmi_boost_level(स्थिर काष्ठा पूर्णांकel_bios_encoder_data *devdata);

#पूर्ण_अगर /* _INTEL_BIOS_H_ */
