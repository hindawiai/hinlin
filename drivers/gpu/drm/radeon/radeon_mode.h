<शैली गुरु>
/*
 * Copyright 2000 ATI Technologies Inc., Markham, Ontario, and
 *                VA Linux Systems Inc., Fremont, Calअगरornia.
 * Copyright 2008 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Original Authors:
 *   Kevin E. Martin, Rickard E. Faith, Alan Hourihane
 *
 * Kernel port Author: Dave Airlie
 */

#अगर_अघोषित RADEON_MODE_H
#घोषणा RADEON_MODE_H

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_dp_mst_helper.h>
#समावेश <drm/drm_fixed.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>

काष्ठा radeon_bo;
काष्ठा radeon_device;

#घोषणा to_radeon_crtc(x) container_of(x, काष्ठा radeon_crtc, base)
#घोषणा to_radeon_connector(x) container_of(x, काष्ठा radeon_connector, base)
#घोषणा to_radeon_encoder(x) container_of(x, काष्ठा radeon_encoder, base)

#घोषणा RADEON_MAX_HPD_PINS 7
#घोषणा RADEON_MAX_CRTCS 6
#घोषणा RADEON_MAX_AFMT_BLOCKS 7

क्रमागत radeon_rmx_type अणु
	RMX_OFF,
	RMX_FULL,
	RMX_CENTER,
	RMX_ASPECT
पूर्ण;

क्रमागत radeon_tv_std अणु
	TV_STD_NTSC,
	TV_STD_PAL,
	TV_STD_PAL_M,
	TV_STD_PAL_60,
	TV_STD_NTSC_J,
	TV_STD_SCART_PAL,
	TV_STD_SECAM,
	TV_STD_PAL_CN,
	TV_STD_PAL_N,
पूर्ण;

क्रमागत radeon_underscan_type अणु
	UNDERSCAN_OFF,
	UNDERSCAN_ON,
	UNDERSCAN_AUTO,
पूर्ण;

क्रमागत radeon_hpd_id अणु
	RADEON_HPD_1 = 0,
	RADEON_HPD_2,
	RADEON_HPD_3,
	RADEON_HPD_4,
	RADEON_HPD_5,
	RADEON_HPD_6,
	RADEON_HPD_NONE = 0xff,
पूर्ण;

क्रमागत radeon_output_csc अणु
	RADEON_OUTPUT_CSC_BYPASS = 0,
	RADEON_OUTPUT_CSC_TVRGB = 1,
	RADEON_OUTPUT_CSC_YCBCR601 = 2,
	RADEON_OUTPUT_CSC_YCBCR709 = 3,
पूर्ण;

#घोषणा RADEON_MAX_I2C_BUS 16

/* radeon gpio-based i2c
 * 1. "mask" reg and bits
 *    grअसल the gpio pins क्रम software use
 *    0=not held  1=held
 * 2. "a" reg and bits
 *    output pin value
 *    0=low 1=high
 * 3. "en" reg and bits
 *    sets the pin direction
 *    0=input 1=output
 * 4. "y" reg and bits
 *    input pin value
 *    0=low 1=high
 */
काष्ठा radeon_i2c_bus_rec अणु
	bool valid;
	/* id used by atom */
	uपूर्णांक8_t i2c_id;
	/* id used by atom */
	क्रमागत radeon_hpd_id hpd;
	/* can be used with hw i2c engine */
	bool hw_capable;
	/* uses multi-media i2c engine */
	bool mm_i2c;
	/* regs and bits */
	uपूर्णांक32_t mask_clk_reg;
	uपूर्णांक32_t mask_data_reg;
	uपूर्णांक32_t a_clk_reg;
	uपूर्णांक32_t a_data_reg;
	uपूर्णांक32_t en_clk_reg;
	uपूर्णांक32_t en_data_reg;
	uपूर्णांक32_t y_clk_reg;
	uपूर्णांक32_t y_data_reg;
	uपूर्णांक32_t mask_clk_mask;
	uपूर्णांक32_t mask_data_mask;
	uपूर्णांक32_t a_clk_mask;
	uपूर्णांक32_t a_data_mask;
	uपूर्णांक32_t en_clk_mask;
	uपूर्णांक32_t en_data_mask;
	uपूर्णांक32_t y_clk_mask;
	uपूर्णांक32_t y_data_mask;
पूर्ण;

काष्ठा radeon_पंचांगds_pll अणु
    uपूर्णांक32_t freq;
    uपूर्णांक32_t value;
पूर्ण;

#घोषणा RADEON_MAX_BIOS_CONNECTOR 16

/* pll flags */
#घोषणा RADEON_PLL_USE_BIOS_DIVS        (1 << 0)
#घोषणा RADEON_PLL_NO_ODD_POST_DIV      (1 << 1)
#घोषणा RADEON_PLL_USE_REF_DIV          (1 << 2)
#घोषणा RADEON_PLL_LEGACY               (1 << 3)
#घोषणा RADEON_PLL_PREFER_LOW_REF_DIV   (1 << 4)
#घोषणा RADEON_PLL_PREFER_HIGH_REF_DIV  (1 << 5)
#घोषणा RADEON_PLL_PREFER_LOW_FB_DIV    (1 << 6)
#घोषणा RADEON_PLL_PREFER_HIGH_FB_DIV   (1 << 7)
#घोषणा RADEON_PLL_PREFER_LOW_POST_DIV  (1 << 8)
#घोषणा RADEON_PLL_PREFER_HIGH_POST_DIV (1 << 9)
#घोषणा RADEON_PLL_USE_FRAC_FB_DIV      (1 << 10)
#घोषणा RADEON_PLL_PREFER_CLOSEST_LOWER (1 << 11)
#घोषणा RADEON_PLL_USE_POST_DIV         (1 << 12)
#घोषणा RADEON_PLL_IS_LCD               (1 << 13)
#घोषणा RADEON_PLL_PREFER_MINM_OVER_MAXP (1 << 14)

काष्ठा radeon_pll अणु
	/* reference frequency */
	uपूर्णांक32_t reference_freq;

	/* fixed भागiders */
	uपूर्णांक32_t reference_भाग;
	uपूर्णांक32_t post_भाग;

	/* pll in/out limits */
	uपूर्णांक32_t pll_in_min;
	uपूर्णांक32_t pll_in_max;
	uपूर्णांक32_t pll_out_min;
	uपूर्णांक32_t pll_out_max;
	uपूर्णांक32_t lcd_pll_out_min;
	uपूर्णांक32_t lcd_pll_out_max;
	uपूर्णांक32_t best_vco;

	/* भागider limits */
	uपूर्णांक32_t min_ref_भाग;
	uपूर्णांक32_t max_ref_भाग;
	uपूर्णांक32_t min_post_भाग;
	uपूर्णांक32_t max_post_भाग;
	uपूर्णांक32_t min_feedback_भाग;
	uपूर्णांक32_t max_feedback_भाग;
	uपूर्णांक32_t min_frac_feedback_भाग;
	uपूर्णांक32_t max_frac_feedback_भाग;

	/* flags क्रम the current घड़ी */
	uपूर्णांक32_t flags;

	/* pll id */
	uपूर्णांक32_t id;
पूर्ण;

काष्ठा radeon_i2c_chan अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा drm_device *dev;
	काष्ठा i2c_algo_bit_data bit;
	काष्ठा radeon_i2c_bus_rec rec;
	काष्ठा drm_dp_aux aux;
	bool has_aux;
	काष्ठा mutex mutex;
पूर्ण;

/* mostly क्रम macs, but really any प्रणाली without connector tables */
क्रमागत radeon_connector_table अणु
	CT_NONE = 0,
	CT_GENERIC,
	CT_IBOOK,
	CT_POWERBOOK_EXTERNAL,
	CT_POWERBOOK_INTERNAL,
	CT_POWERBOOK_VGA,
	CT_MINI_EXTERNAL,
	CT_MINI_INTERNAL,
	CT_IMAC_G5_ISIGHT,
	CT_EMAC,
	CT_RN50_POWER,
	CT_MAC_X800,
	CT_MAC_G5_9600,
	CT_SAM440EP,
	CT_MAC_G4_SILVER
पूर्ण;

क्रमागत radeon_dvo_chip अणु
	DVO_SIL164,
	DVO_SIL1178,
पूर्ण;

काष्ठा radeon_fbdev;

काष्ठा radeon_afmt अणु
	bool enabled;
	पूर्णांक offset;
	bool last_buffer_filled_status;
	पूर्णांक id;
पूर्ण;

काष्ठा radeon_mode_info अणु
	काष्ठा atom_context *atom_context;
	काष्ठा card_info *atom_card_info;
	क्रमागत radeon_connector_table connector_table;
	bool mode_config_initialized;
	काष्ठा radeon_crtc *crtcs[RADEON_MAX_CRTCS];
	काष्ठा radeon_afmt *afmt[RADEON_MAX_AFMT_BLOCKS];
	/* DVI-I properties */
	काष्ठा drm_property *coherent_mode_property;
	/* DAC enable load detect */
	काष्ठा drm_property *load_detect_property;
	/* TV standard */
	काष्ठा drm_property *tv_std_property;
	/* legacy TMDS PLL detect */
	काष्ठा drm_property *पंचांगds_pll_property;
	/* underscan */
	काष्ठा drm_property *underscan_property;
	काष्ठा drm_property *underscan_hborder_property;
	काष्ठा drm_property *underscan_vborder_property;
	/* audio */
	काष्ठा drm_property *audio_property;
	/* FMT dithering */
	काष्ठा drm_property *dither_property;
	/* Output CSC */
	काष्ठा drm_property *output_csc_property;
	/* hardcoded DFP edid from BIOS */
	काष्ठा edid *bios_hardcoded_edid;
	पूर्णांक bios_hardcoded_edid_size;

	/* poपूर्णांकer to fbdev info काष्ठाure */
	काष्ठा radeon_fbdev *rfbdev;
	/* firmware flags */
	u16 firmware_flags;
	/* poपूर्णांकer to backlight encoder */
	काष्ठा radeon_encoder *bl_encoder;

	/* biपंचांगask क्रम active encoder frontends */
	uपूर्णांक32_t active_encoders;
पूर्ण;

#घोषणा RADEON_MAX_BL_LEVEL 0xFF

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

काष्ठा radeon_backlight_privdata अणु
	काष्ठा radeon_encoder *encoder;
	uपूर्णांक8_t negative;
पूर्ण;

#पूर्ण_अगर

#घोषणा MAX_H_CODE_TIMING_LEN 32
#घोषणा MAX_V_CODE_TIMING_LEN 32

/* need to store these as पढ़ोing
   back code tables is excessive */
काष्ठा radeon_tv_regs अणु
	uपूर्णांक32_t tv_uv_adr;
	uपूर्णांक32_t timing_cntl;
	uपूर्णांक32_t hrestart;
	uपूर्णांक32_t vrestart;
	uपूर्णांक32_t frestart;
	uपूर्णांक16_t h_code_timing[MAX_H_CODE_TIMING_LEN];
	uपूर्णांक16_t v_code_timing[MAX_V_CODE_TIMING_LEN];
पूर्ण;

काष्ठा radeon_atom_ss अणु
	uपूर्णांक16_t percentage;
	uपूर्णांक16_t percentage_भागider;
	uपूर्णांक8_t type;
	uपूर्णांक16_t step;
	uपूर्णांक8_t delay;
	uपूर्णांक8_t range;
	uपूर्णांक8_t refभाग;
	/* asic_ss */
	uपूर्णांक16_t rate;
	uपूर्णांक16_t amount;
पूर्ण;

क्रमागत radeon_flip_status अणु
	RADEON_FLIP_NONE,
	RADEON_FLIP_PENDING,
	RADEON_FLIP_SUBMITTED
पूर्ण;

काष्ठा radeon_crtc अणु
	काष्ठा drm_crtc base;
	पूर्णांक crtc_id;
	bool enabled;
	bool can_tile;
	bool cursor_out_of_bounds;
	uपूर्णांक32_t crtc_offset;
	काष्ठा drm_gem_object *cursor_bo;
	uपूर्णांक64_t cursor_addr;
	पूर्णांक cursor_x;
	पूर्णांक cursor_y;
	पूर्णांक cursor_hot_x;
	पूर्णांक cursor_hot_y;
	पूर्णांक cursor_width;
	पूर्णांक cursor_height;
	पूर्णांक max_cursor_width;
	पूर्णांक max_cursor_height;
	uपूर्णांक32_t legacy_display_base_addr;
	क्रमागत radeon_rmx_type rmx_type;
	u8 h_border;
	u8 v_border;
	fixed20_12 vsc;
	fixed20_12 hsc;
	काष्ठा drm_display_mode native_mode;
	पूर्णांक pll_id;
	/* page flipping */
	काष्ठा workqueue_काष्ठा *flip_queue;
	काष्ठा radeon_flip_work *flip_work;
	क्रमागत radeon_flip_status flip_status;
	/* pll sharing */
	काष्ठा radeon_atom_ss ss;
	bool ss_enabled;
	u32 adjusted_घड़ी;
	पूर्णांक bpc;
	u32 pll_reference_भाग;
	u32 pll_post_भाग;
	u32 pll_flags;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector *connector;
	/* क्रम dpm */
	u32 line_समय;
	u32 wm_low;
	u32 wm_high;
	u32 lb_vblank_lead_lines;
	काष्ठा drm_display_mode hw_mode;
	क्रमागत radeon_output_csc output_csc;
पूर्ण;

काष्ठा radeon_encoder_primary_dac अणु
	/* legacy primary dac */
	uपूर्णांक32_t ps2_pdac_adj;
पूर्ण;

काष्ठा radeon_encoder_lvds अणु
	/* legacy lvds */
	uपूर्णांक16_t panel_vcc_delay;
	uपूर्णांक8_t  panel_pwr_delay;
	uपूर्णांक8_t  panel_digon_delay;
	uपूर्णांक8_t  panel_blon_delay;
	uपूर्णांक16_t panel_ref_भागider;
	uपूर्णांक8_t  panel_post_भागider;
	uपूर्णांक16_t panel_fb_भागider;
	bool     use_bios_भागiders;
	uपूर्णांक32_t lvds_gen_cntl;
	/* panel mode */
	काष्ठा drm_display_mode native_mode;
	काष्ठा backlight_device *bl_dev;
	पूर्णांक      dpms_mode;
	uपूर्णांक8_t  backlight_level;
पूर्ण;

काष्ठा radeon_encoder_tv_dac अणु
	/* legacy tv dac */
	uपूर्णांक32_t ps2_tvdac_adj;
	uपूर्णांक32_t ntsc_tvdac_adj;
	uपूर्णांक32_t pal_tvdac_adj;

	पूर्णांक               h_pos;
	पूर्णांक               v_pos;
	पूर्णांक               h_size;
	पूर्णांक               supported_tv_stds;
	bool              tv_on;
	क्रमागत radeon_tv_std tv_std;
	काष्ठा radeon_tv_regs tv;
पूर्ण;

काष्ठा radeon_encoder_पूर्णांक_पंचांगds अणु
	/* legacy पूर्णांक पंचांगds */
	काष्ठा radeon_पंचांगds_pll पंचांगds_pll[4];
पूर्ण;

काष्ठा radeon_encoder_ext_पंचांगds अणु
	/* पंचांगds over dvo */
	काष्ठा radeon_i2c_chan *i2c_bus;
	uपूर्णांक8_t slave_addr;
	क्रमागत radeon_dvo_chip dvo_chip;
पूर्ण;

/* spपढ़ो spectrum */
काष्ठा radeon_encoder_atom_dig अणु
	bool linkb;
	/* atom dig */
	bool coherent_mode;
	पूर्णांक dig_encoder; /* -1 disabled, 0 DIGA, 1 DIGB, etc. */
	/* atom lvds/edp */
	uपूर्णांक32_t lcd_misc;
	uपूर्णांक16_t panel_pwr_delay;
	uपूर्णांक32_t lcd_ss_id;
	/* panel mode */
	काष्ठा drm_display_mode native_mode;
	काष्ठा backlight_device *bl_dev;
	पूर्णांक dpms_mode;
	uपूर्णांक8_t backlight_level;
	पूर्णांक panel_mode;
	काष्ठा radeon_afmt *afmt;
	काष्ठा r600_audio_pin *pin;
	पूर्णांक active_mst_links;
पूर्ण;

काष्ठा radeon_encoder_atom_dac अणु
	क्रमागत radeon_tv_std tv_std;
पूर्ण;

काष्ठा radeon_encoder_mst अणु
	पूर्णांक crtc;
	काष्ठा radeon_encoder *primary;
	काष्ठा radeon_connector *connector;
	काष्ठा drm_dp_mst_port *port;
	पूर्णांक pbn;
	पूर्णांक fe;
	bool fe_from_be;
	bool enc_active;
पूर्ण;

काष्ठा radeon_encoder अणु
	काष्ठा drm_encoder base;
	uपूर्णांक32_t encoder_क्रमागत;
	uपूर्णांक32_t encoder_id;
	uपूर्णांक32_t devices;
	uपूर्णांक32_t active_device;
	uपूर्णांक32_t flags;
	uपूर्णांक32_t pixel_घड़ी;
	क्रमागत radeon_rmx_type rmx_type;
	क्रमागत radeon_underscan_type underscan_type;
	uपूर्णांक32_t underscan_hborder;
	uपूर्णांक32_t underscan_vborder;
	काष्ठा drm_display_mode native_mode;
	व्योम *enc_priv;
	पूर्णांक audio_polling_active;
	bool is_ext_encoder;
	u16 caps;
	काष्ठा radeon_audio_funcs *audio;
	क्रमागत radeon_output_csc output_csc;
	bool can_mst;
	uपूर्णांक32_t offset;
	bool is_mst_encoder;
	/* front end क्रम this mst encoder */
पूर्ण;

काष्ठा radeon_connector_atom_dig अणु
	uपूर्णांक32_t igp_lane_info;
	/* displayport */
	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	u8 dp_sink_type;
	पूर्णांक dp_घड़ी;
	पूर्णांक dp_lane_count;
	bool edp_on;
	bool is_mst;
पूर्ण;

काष्ठा radeon_gpio_rec अणु
	bool valid;
	u8 id;
	u32 reg;
	u32 mask;
	u32 shअगरt;
पूर्ण;

काष्ठा radeon_hpd अणु
	क्रमागत radeon_hpd_id hpd;
	u8 plugged_state;
	काष्ठा radeon_gpio_rec gpio;
पूर्ण;

काष्ठा radeon_router अणु
	u32 router_id;
	काष्ठा radeon_i2c_bus_rec i2c_info;
	u8 i2c_addr;
	/* i2c mux */
	bool ddc_valid;
	u8 ddc_mux_type;
	u8 ddc_mux_control_pin;
	u8 ddc_mux_state;
	/* घड़ी/data mux */
	bool cd_valid;
	u8 cd_mux_type;
	u8 cd_mux_control_pin;
	u8 cd_mux_state;
पूर्ण;

क्रमागत radeon_connector_audio अणु
	RADEON_AUDIO_DISABLE = 0,
	RADEON_AUDIO_ENABLE = 1,
	RADEON_AUDIO_AUTO = 2
पूर्ण;

क्रमागत radeon_connector_dither अणु
	RADEON_FMT_DITHER_DISABLE = 0,
	RADEON_FMT_DITHER_ENABLE = 1,
पूर्ण;

काष्ठा stream_attribs अणु
	uपूर्णांक16_t fe;
	uपूर्णांक16_t slots;
पूर्ण;

काष्ठा radeon_connector अणु
	काष्ठा drm_connector base;
	uपूर्णांक32_t connector_id;
	uपूर्णांक32_t devices;
	काष्ठा radeon_i2c_chan *ddc_bus;
	/* some प्रणालीs have an hdmi and vga port with a shared ddc line */
	bool shared_ddc;
	bool use_digital;
	/* we need to mind the EDID between detect
	   and get modes due to analog/digital/tvencoder */
	काष्ठा edid *edid;
	व्योम *con_priv;
	bool dac_load_detect;
	bool detected_by_load; /* अगर the connection status was determined by load */
	bool detected_hpd_without_ddc; /* अगर an HPD संकेत was detected on DVI, but ddc probing failed */
	uपूर्णांक16_t connector_object_id;
	काष्ठा radeon_hpd hpd;
	काष्ठा radeon_router router;
	काष्ठा radeon_i2c_chan *router_bus;
	क्रमागत radeon_connector_audio audio;
	क्रमागत radeon_connector_dither dither;
	पूर्णांक pixelघड़ी_क्रम_modeset;
	bool is_mst_connector;
	काष्ठा radeon_connector *mst_port;
	काष्ठा drm_dp_mst_port *port;
	काष्ठा drm_dp_mst_topology_mgr mst_mgr;

	काष्ठा radeon_encoder *mst_encoder;
	काष्ठा stream_attribs cur_stream_attribs[6];
	पूर्णांक enabled_attribs;
पूर्ण;

#घोषणा ENCODER_MODE_IS_DP(em) (((em) == ATOM_ENCODER_MODE_DP) || \
				((em) == ATOM_ENCODER_MODE_DP_MST))

काष्ठा atom_घड़ी_भागiders अणु
	u32 post_भाग;
	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
			u32 reserved : 6;
			u32 whole_fb_भाग : 12;
			u32 frac_fb_भाग : 14;
#अन्यथा
			u32 frac_fb_भाग : 14;
			u32 whole_fb_भाग : 12;
			u32 reserved : 6;
#पूर्ण_अगर
		पूर्ण;
		u32 fb_भाग;
	पूर्ण;
	u32 ref_भाग;
	bool enable_post_भाग;
	bool enable_dithen;
	u32 vco_mode;
	u32 real_घड़ी;
	/* added क्रम CI */
	u32 post_भागider;
	u32 flags;
पूर्ण;

काष्ठा atom_mpll_param अणु
	जोड़ अणु
		काष्ठा अणु
#अगर_घोषित __BIG_ENDIAN
			u32 reserved : 8;
			u32 clkfrac : 12;
			u32 clkf : 12;
#अन्यथा
			u32 clkf : 12;
			u32 clkfrac : 12;
			u32 reserved : 8;
#पूर्ण_अगर
		पूर्ण;
		u32 fb_भाग;
	पूर्ण;
	u32 post_भाग;
	u32 bwcntl;
	u32 dll_speed;
	u32 vco_mode;
	u32 yclk_sel;
	u32 qdr;
	u32 half_rate;
पूर्ण;

#घोषणा MEM_TYPE_GDDR5  0x50
#घोषणा MEM_TYPE_GDDR4  0x40
#घोषणा MEM_TYPE_GDDR3  0x30
#घोषणा MEM_TYPE_DDR2   0x20
#घोषणा MEM_TYPE_GDDR1  0x10
#घोषणा MEM_TYPE_DDR3   0xb0
#घोषणा MEM_TYPE_MASK   0xf0

काष्ठा atom_memory_info अणु
	u8 mem_venकरोr;
	u8 mem_type;
पूर्ण;

#घोषणा MAX_AC_TIMING_ENTRIES 16

काष्ठा atom_memory_घड़ी_range_table
अणु
	u8 num_entries;
	u8 rsv[3];
	u32 mclk[MAX_AC_TIMING_ENTRIES];
पूर्ण;

#घोषणा VBIOS_MC_REGISTER_ARRAY_SIZE 32
#घोषणा VBIOS_MAX_AC_TIMING_ENTRIES 20

काष्ठा atom_mc_reg_entry अणु
	u32 mclk_max;
	u32 mc_data[VBIOS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

काष्ठा atom_mc_रेजिस्टर_address अणु
	u16 s1;
	u8 pre_reg_data;
पूर्ण;

काष्ठा atom_mc_reg_table अणु
	u8 last;
	u8 num_entries;
	काष्ठा atom_mc_reg_entry mc_reg_table_entry[VBIOS_MAX_AC_TIMING_ENTRIES];
	काष्ठा atom_mc_रेजिस्टर_address mc_reg_address[VBIOS_MC_REGISTER_ARRAY_SIZE];
पूर्ण;

#घोषणा MAX_VOLTAGE_ENTRIES 32

काष्ठा atom_voltage_table_entry
अणु
	u16 value;
	u32 smio_low;
पूर्ण;

काष्ठा atom_voltage_table
अणु
	u32 count;
	u32 mask_low;
	u32 phase_delay;
	काष्ठा atom_voltage_table_entry entries[MAX_VOLTAGE_ENTRIES];
पूर्ण;

/* Driver पूर्णांकernal use only flags of radeon_get_crtc_scanoutpos() */
#घोषणा DRM_SCANOUTPOS_VALID        (1 << 0)
#घोषणा DRM_SCANOUTPOS_IN_VBLANK    (1 << 1)
#घोषणा DRM_SCANOUTPOS_ACCURATE     (1 << 2)
#घोषणा USE_REAL_VBLANKSTART 		(1 << 30)
#घोषणा GET_DISTANCE_TO_VBLANKSTART	(1 << 31)

बाह्य व्योम
radeon_add_atom_connector(काष्ठा drm_device *dev,
			  uपूर्णांक32_t connector_id,
			  uपूर्णांक32_t supported_device,
			  पूर्णांक connector_type,
			  काष्ठा radeon_i2c_bus_rec *i2c_bus,
			  uपूर्णांक32_t igp_lane_info,
			  uपूर्णांक16_t connector_object_id,
			  काष्ठा radeon_hpd *hpd,
			  काष्ठा radeon_router *router);
बाह्य व्योम
radeon_add_legacy_connector(काष्ठा drm_device *dev,
			    uपूर्णांक32_t connector_id,
			    uपूर्णांक32_t supported_device,
			    पूर्णांक connector_type,
			    काष्ठा radeon_i2c_bus_rec *i2c_bus,
			    uपूर्णांक16_t connector_object_id,
			    काष्ठा radeon_hpd *hpd);
बाह्य uपूर्णांक32_t
radeon_get_encoder_क्रमागत(काष्ठा drm_device *dev, uपूर्णांक32_t supported_device,
			uपूर्णांक8_t dac);
बाह्य व्योम radeon_link_encoder_connector(काष्ठा drm_device *dev);

बाह्य क्रमागत radeon_tv_std
radeon_combios_get_tv_info(काष्ठा radeon_device *rdev);
बाह्य क्रमागत radeon_tv_std
radeon_atombios_get_tv_info(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_atombios_get_शेष_voltages(काष्ठा radeon_device *rdev,
						 u16 *vddc, u16 *vddci, u16 *mvdd);

बाह्य व्योम
radeon_combios_connected_scratch_regs(काष्ठा drm_connector *connector,
				      काष्ठा drm_encoder *encoder,
				      bool connected);
बाह्य व्योम
radeon_atombios_connected_scratch_regs(काष्ठा drm_connector *connector,
				       काष्ठा drm_encoder *encoder,
				       bool connected);

बाह्य काष्ठा drm_connector *
radeon_get_connector_क्रम_encoder(काष्ठा drm_encoder *encoder);
बाह्य काष्ठा drm_connector *
radeon_get_connector_क्रम_encoder_init(काष्ठा drm_encoder *encoder);
बाह्य bool radeon_dig_monitor_is_duallink(काष्ठा drm_encoder *encoder,
				    u32 pixel_घड़ी);

बाह्य u16 radeon_encoder_get_dp_bridge_encoder_id(काष्ठा drm_encoder *encoder);
बाह्य u16 radeon_connector_encoder_get_dp_bridge_encoder_id(काष्ठा drm_connector *connector);
बाह्य bool radeon_connector_is_dp12_capable(काष्ठा drm_connector *connector);
बाह्य पूर्णांक radeon_get_monitor_bpc(काष्ठा drm_connector *connector);

बाह्य काष्ठा edid *radeon_connector_edid(काष्ठा drm_connector *connector);

बाह्य व्योम radeon_connector_hotplug(काष्ठा drm_connector *connector);
बाह्य पूर्णांक radeon_dp_mode_valid_helper(काष्ठा drm_connector *connector,
				       काष्ठा drm_display_mode *mode);
बाह्य व्योम radeon_dp_set_link_config(काष्ठा drm_connector *connector,
				      स्थिर काष्ठा drm_display_mode *mode);
बाह्य व्योम radeon_dp_link_train(काष्ठा drm_encoder *encoder,
				 काष्ठा drm_connector *connector);
बाह्य bool radeon_dp_needs_link_train(काष्ठा radeon_connector *radeon_connector);
बाह्य u8 radeon_dp_माला_लोinktype(काष्ठा radeon_connector *radeon_connector);
बाह्य bool radeon_dp_getdpcd(काष्ठा radeon_connector *radeon_connector);
बाह्य पूर्णांक radeon_dp_get_panel_mode(काष्ठा drm_encoder *encoder,
				    काष्ठा drm_connector *connector);
बाह्य व्योम radeon_dp_set_rx_घातer_state(काष्ठा drm_connector *connector,
					 u8 घातer_state);
बाह्य व्योम radeon_dp_aux_init(काष्ठा radeon_connector *radeon_connector);
बाह्य sमाप_प्रकार
radeon_dp_aux_transfer_native(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_aux_msg *msg);

बाह्य व्योम atombios_dig_encoder_setup(काष्ठा drm_encoder *encoder, पूर्णांक action, पूर्णांक panel_mode);
बाह्य व्योम atombios_dig_encoder_setup2(काष्ठा drm_encoder *encoder, पूर्णांक action, पूर्णांक panel_mode, पूर्णांक enc_override);
बाह्य व्योम radeon_atom_encoder_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_atom_disp_eng_pll_init(काष्ठा radeon_device *rdev);
बाह्य व्योम atombios_dig_transmitter_setup(काष्ठा drm_encoder *encoder,
					   पूर्णांक action, uपूर्णांक8_t lane_num,
					   uपूर्णांक8_t lane_set);
बाह्य व्योम atombios_dig_transmitter_setup2(काष्ठा drm_encoder *encoder,
					    पूर्णांक action, uपूर्णांक8_t lane_num,
					    uपूर्णांक8_t lane_set, पूर्णांक fe);
बाह्य व्योम atombios_set_mst_encoder_crtc_source(काष्ठा drm_encoder *encoder,
						 पूर्णांक fe);
बाह्य व्योम radeon_atom_ext_encoder_setup_ddc(काष्ठा drm_encoder *encoder);
बाह्य काष्ठा drm_encoder *radeon_get_बाह्यal_encoder(काष्ठा drm_encoder *encoder);
व्योम radeon_atom_copy_swap(u8 *dst, u8 *src, u8 num_bytes, bool to_le);

बाह्य व्योम radeon_i2c_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_i2c_fini(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_combios_i2c_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_atombios_i2c_init(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_i2c_add(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_i2c_bus_rec *rec,
			   स्थिर अक्षर *name);
बाह्य काष्ठा radeon_i2c_chan *radeon_i2c_lookup(काष्ठा radeon_device *rdev,
						 काष्ठा radeon_i2c_bus_rec *i2c_bus);
बाह्य काष्ठा radeon_i2c_chan *radeon_i2c_create(काष्ठा drm_device *dev,
						 काष्ठा radeon_i2c_bus_rec *rec,
						 स्थिर अक्षर *name);
बाह्य व्योम radeon_i2c_destroy(काष्ठा radeon_i2c_chan *i2c);
बाह्य व्योम radeon_i2c_get_byte(काष्ठा radeon_i2c_chan *i2c_bus,
				u8 slave_addr,
				u8 addr,
				u8 *val);
बाह्य व्योम radeon_i2c_put_byte(काष्ठा radeon_i2c_chan *i2c,
				u8 slave_addr,
				u8 addr,
				u8 val);
बाह्य व्योम radeon_router_select_ddc_port(काष्ठा radeon_connector *radeon_connector);
बाह्य व्योम radeon_router_select_cd_port(काष्ठा radeon_connector *radeon_connector);
बाह्य bool radeon_ddc_probe(काष्ठा radeon_connector *radeon_connector, bool use_aux);

बाह्य bool radeon_atombios_get_ppll_ss_info(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_atom_ss *ss,
					     पूर्णांक id);
बाह्य bool radeon_atombios_get_asic_ss_info(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_atom_ss *ss,
					     पूर्णांक id, u32 घड़ी);
बाह्य काष्ठा radeon_gpio_rec radeon_atombios_lookup_gpio(काष्ठा radeon_device *rdev,
							  u8 id);

बाह्य व्योम radeon_compute_pll_legacy(काष्ठा radeon_pll *pll,
				      uपूर्णांक64_t freq,
				      uपूर्णांक32_t *करोt_घड़ी_p,
				      uपूर्णांक32_t *fb_भाग_p,
				      uपूर्णांक32_t *frac_fb_भाग_p,
				      uपूर्णांक32_t *ref_भाग_p,
				      uपूर्णांक32_t *post_भाग_p);

बाह्य व्योम radeon_compute_pll_avivo(काष्ठा radeon_pll *pll,
				     u32 freq,
				     u32 *करोt_घड़ी_p,
				     u32 *fb_भाग_p,
				     u32 *frac_fb_भाग_p,
				     u32 *ref_भाग_p,
				     u32 *post_भाग_p);

बाह्य व्योम radeon_setup_encoder_clones(काष्ठा drm_device *dev);

काष्ठा drm_encoder *radeon_encoder_legacy_lvds_add(काष्ठा drm_device *dev, पूर्णांक bios_index);
काष्ठा drm_encoder *radeon_encoder_legacy_primary_dac_add(काष्ठा drm_device *dev, पूर्णांक bios_index, पूर्णांक with_tv);
काष्ठा drm_encoder *radeon_encoder_legacy_tv_dac_add(काष्ठा drm_device *dev, पूर्णांक bios_index, पूर्णांक with_tv);
काष्ठा drm_encoder *radeon_encoder_legacy_पंचांगds_पूर्णांक_add(काष्ठा drm_device *dev, पूर्णांक bios_index);
काष्ठा drm_encoder *radeon_encoder_legacy_पंचांगds_ext_add(काष्ठा drm_device *dev, पूर्णांक bios_index);
बाह्य व्योम atombios_dvo_setup(काष्ठा drm_encoder *encoder, पूर्णांक action);
बाह्य व्योम atombios_digital_setup(काष्ठा drm_encoder *encoder, पूर्णांक action);
बाह्य पूर्णांक atombios_get_encoder_mode(काष्ठा drm_encoder *encoder);
बाह्य bool atombios_set_edp_panel_घातer(काष्ठा drm_connector *connector, पूर्णांक action);
बाह्य व्योम radeon_encoder_set_active_device(काष्ठा drm_encoder *encoder);
बाह्य bool radeon_encoder_is_digital(काष्ठा drm_encoder *encoder);

बाह्य व्योम radeon_crtc_load_lut(काष्ठा drm_crtc *crtc);
बाह्य पूर्णांक atombios_crtc_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
				   काष्ठा drm_framebuffer *old_fb);
बाह्य पूर्णांक atombios_crtc_set_base_atomic(काष्ठा drm_crtc *crtc,
					 काष्ठा drm_framebuffer *fb,
					 पूर्णांक x, पूर्णांक y,
					 क्रमागत mode_set_atomic state);
बाह्य पूर्णांक atombios_crtc_mode_set(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_display_mode *mode,
				   काष्ठा drm_display_mode *adjusted_mode,
				   पूर्णांक x, पूर्णांक y,
				   काष्ठा drm_framebuffer *old_fb);
बाह्य व्योम atombios_crtc_dpms(काष्ठा drm_crtc *crtc, पूर्णांक mode);

बाह्य पूर्णांक radeon_crtc_set_base(काष्ठा drm_crtc *crtc, पूर्णांक x, पूर्णांक y,
				 काष्ठा drm_framebuffer *old_fb);
बाह्य पूर्णांक radeon_crtc_set_base_atomic(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_framebuffer *fb,
				       पूर्णांक x, पूर्णांक y,
				       क्रमागत mode_set_atomic state);
बाह्य पूर्णांक radeon_crtc_करो_set_base(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_framebuffer *fb,
				   पूर्णांक x, पूर्णांक y, पूर्णांक atomic);
बाह्य पूर्णांक radeon_crtc_cursor_set2(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_file *file_priv,
				   uपूर्णांक32_t handle,
				   uपूर्णांक32_t width,
				   uपूर्णांक32_t height,
				   पूर्णांक32_t hot_x,
				   पूर्णांक32_t hot_y);
बाह्य पूर्णांक radeon_crtc_cursor_move(काष्ठा drm_crtc *crtc,
				   पूर्णांक x, पूर्णांक y);
बाह्य व्योम radeon_cursor_reset(काष्ठा drm_crtc *crtc);

बाह्य पूर्णांक radeon_get_crtc_scanoutpos(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
				      अचिन्हित पूर्णांक flags, पूर्णांक *vpos, पूर्णांक *hpos,
				      kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
				      स्थिर काष्ठा drm_display_mode *mode);

बाह्य bool
radeon_get_crtc_scanout_position(काष्ठा drm_crtc *crtc, bool in_vblank_irq,
				 पूर्णांक *vpos, पूर्णांक *hpos,
				 kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
				 स्थिर काष्ठा drm_display_mode *mode);

बाह्य bool radeon_combios_check_hardcoded_edid(काष्ठा radeon_device *rdev);
बाह्य काष्ठा edid *
radeon_bios_get_hardcoded_edid(काष्ठा radeon_device *rdev);
बाह्य bool radeon_atom_get_घड़ी_info(काष्ठा drm_device *dev);
बाह्य bool radeon_combios_get_घड़ी_info(काष्ठा drm_device *dev);
बाह्य काष्ठा radeon_encoder_atom_dig *
radeon_atombios_get_lvds_info(काष्ठा radeon_encoder *encoder);
बाह्य bool radeon_atombios_get_पंचांगds_info(काष्ठा radeon_encoder *encoder,
					  काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds);
बाह्य bool radeon_legacy_get_पंचांगds_info_from_combios(काष्ठा radeon_encoder *encoder,
						     काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds);
बाह्य bool radeon_legacy_get_पंचांगds_info_from_table(काष्ठा radeon_encoder *encoder,
						   काष्ठा radeon_encoder_पूर्णांक_पंचांगds *पंचांगds);
बाह्य bool radeon_legacy_get_ext_पंचांगds_info_from_combios(काष्ठा radeon_encoder *encoder,
							 काष्ठा radeon_encoder_ext_पंचांगds *पंचांगds);
बाह्य bool radeon_legacy_get_ext_पंचांगds_info_from_table(काष्ठा radeon_encoder *encoder,
						       काष्ठा radeon_encoder_ext_पंचांगds *पंचांगds);
बाह्य काष्ठा radeon_encoder_primary_dac *
radeon_atombios_get_primary_dac_info(काष्ठा radeon_encoder *encoder);
बाह्य काष्ठा radeon_encoder_tv_dac *
radeon_atombios_get_tv_dac_info(काष्ठा radeon_encoder *encoder);
बाह्य काष्ठा radeon_encoder_lvds *
radeon_combios_get_lvds_info(काष्ठा radeon_encoder *encoder);
बाह्य व्योम radeon_combios_get_ext_पंचांगds_info(काष्ठा radeon_encoder *encoder);
बाह्य काष्ठा radeon_encoder_tv_dac *
radeon_combios_get_tv_dac_info(काष्ठा radeon_encoder *encoder);
बाह्य काष्ठा radeon_encoder_primary_dac *
radeon_combios_get_primary_dac_info(काष्ठा radeon_encoder *encoder);
बाह्य bool radeon_combios_बाह्यal_पंचांगds_setup(काष्ठा drm_encoder *encoder);
बाह्य व्योम radeon_बाह्यal_पंचांगds_setup(काष्ठा drm_encoder *encoder);
बाह्य व्योम radeon_combios_output_lock(काष्ठा drm_encoder *encoder, bool lock);
बाह्य व्योम radeon_combios_initialize_bios_scratch_regs(काष्ठा drm_device *dev);
बाह्य व्योम radeon_atom_output_lock(काष्ठा drm_encoder *encoder, bool lock);
बाह्य व्योम radeon_atom_initialize_bios_scratch_regs(काष्ठा drm_device *dev);
बाह्य व्योम radeon_save_bios_scratch_regs(काष्ठा radeon_device *rdev);
बाह्य व्योम radeon_restore_bios_scratch_regs(काष्ठा radeon_device *rdev);
बाह्य व्योम
radeon_atombios_encoder_crtc_scratch_regs(काष्ठा drm_encoder *encoder, पूर्णांक crtc);
बाह्य व्योम
radeon_atombios_encoder_dpms_scratch_regs(काष्ठा drm_encoder *encoder, bool on);
बाह्य व्योम
radeon_combios_encoder_crtc_scratch_regs(काष्ठा drm_encoder *encoder, पूर्णांक crtc);
बाह्य व्योम
radeon_combios_encoder_dpms_scratch_regs(काष्ठा drm_encoder *encoder, bool on);
पूर्णांक radeon_framebuffer_init(काष्ठा drm_device *dev,
			     काष्ठा drm_framebuffer *rfb,
			     स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			     काष्ठा drm_gem_object *obj);

पूर्णांक radeonfb_हटाओ(काष्ठा drm_device *dev, काष्ठा drm_framebuffer *fb);
bool radeon_get_legacy_connector_info_from_bios(काष्ठा drm_device *dev);
bool radeon_get_legacy_connector_info_from_table(काष्ठा drm_device *dev);
व्योम radeon_atombios_init_crtc(काष्ठा drm_device *dev,
			       काष्ठा radeon_crtc *radeon_crtc);
व्योम radeon_legacy_init_crtc(काष्ठा drm_device *dev,
			     काष्ठा radeon_crtc *radeon_crtc);

व्योम radeon_get_घड़ी_info(काष्ठा drm_device *dev);

बाह्य bool radeon_get_atom_connector_info_from_object_table(काष्ठा drm_device *dev);
बाह्य bool radeon_get_atom_connector_info_from_supported_devices_table(काष्ठा drm_device *dev);

व्योम radeon_enc_destroy(काष्ठा drm_encoder *encoder);
व्योम radeon_copy_fb(काष्ठा drm_device *dev, काष्ठा drm_gem_object *dst_obj);
व्योम radeon_combios_asic_init(काष्ठा drm_device *dev);
bool radeon_crtc_scaling_mode_fixup(काष्ठा drm_crtc *crtc,
					स्थिर काष्ठा drm_display_mode *mode,
					काष्ठा drm_display_mode *adjusted_mode);
व्योम radeon_panel_mode_fixup(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *adjusted_mode);
व्योम atom_rv515_क्रमce_tv_scaler(काष्ठा radeon_device *rdev, काष्ठा radeon_crtc *radeon_crtc);

/* legacy tv */
व्योम radeon_legacy_tv_adjust_crtc_reg(काष्ठा drm_encoder *encoder,
				      uपूर्णांक32_t *h_total_disp, uपूर्णांक32_t *h_sync_strt_wid,
				      uपूर्णांक32_t *v_total_disp, uपूर्णांक32_t *v_sync_strt_wid);
व्योम radeon_legacy_tv_adjust_pll1(काष्ठा drm_encoder *encoder,
				  uपूर्णांक32_t *htotal_cntl, uपूर्णांक32_t *ppll_ref_भाग,
				  uपूर्णांक32_t *ppll_भाग_3, uपूर्णांक32_t *pixclks_cntl);
व्योम radeon_legacy_tv_adjust_pll2(काष्ठा drm_encoder *encoder,
				  uपूर्णांक32_t *htotal2_cntl, uपूर्णांक32_t *p2pll_ref_भाग,
				  uपूर्णांक32_t *p2pll_भाग_0, uपूर्णांक32_t *pixclks_cntl);
व्योम radeon_legacy_tv_mode_set(काष्ठा drm_encoder *encoder,
			       काष्ठा drm_display_mode *mode,
			       काष्ठा drm_display_mode *adjusted_mode);

/* fmt blocks */
व्योम avivo_program_fmt(काष्ठा drm_encoder *encoder);
व्योम dce3_program_fmt(काष्ठा drm_encoder *encoder);
व्योम dce4_program_fmt(काष्ठा drm_encoder *encoder);
व्योम dce8_program_fmt(काष्ठा drm_encoder *encoder);

/* fbdev layer */
पूर्णांक radeon_fbdev_init(काष्ठा radeon_device *rdev);
व्योम radeon_fbdev_fini(काष्ठा radeon_device *rdev);
व्योम radeon_fbdev_set_suspend(काष्ठा radeon_device *rdev, पूर्णांक state);
bool radeon_fbdev_robj_is_fb(काष्ठा radeon_device *rdev, काष्ठा radeon_bo *robj);

व्योम radeon_crtc_handle_vblank(काष्ठा radeon_device *rdev, पूर्णांक crtc_id);

व्योम radeon_crtc_handle_flip(काष्ठा radeon_device *rdev, पूर्णांक crtc_id);

पूर्णांक radeon_align_pitch(काष्ठा radeon_device *rdev, पूर्णांक width, पूर्णांक bpp, bool tiled);

/* mst */
पूर्णांक radeon_dp_mst_init(काष्ठा radeon_connector *radeon_connector);
पूर्णांक radeon_dp_mst_probe(काष्ठा radeon_connector *radeon_connector);
पूर्णांक radeon_dp_mst_check_status(काष्ठा radeon_connector *radeon_connector);
व्योम radeon_mst_debugfs_init(काष्ठा radeon_device *rdev);
व्योम radeon_dp_mst_prepare_pll(काष्ठा drm_crtc *crtc, काष्ठा drm_display_mode *mode);

व्योम radeon_setup_mst_connector(काष्ठा drm_device *dev);

पूर्णांक radeon_atom_pick_dig_encoder(काष्ठा drm_encoder *encoder, पूर्णांक fe_idx);
व्योम radeon_atom_release_dig_encoder(काष्ठा radeon_device *rdev, पूर्णांक enc_idx);
#पूर्ण_अगर
