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

#अगर_अघोषित AMDGPU_MODE_H
#घोषणा AMDGPU_MODE_H

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_dp_helper.h>
#समावेश <drm/drm_fixed.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/hrसमयr.h>
#समावेश "amdgpu_irq.h"

#समावेश <drm/drm_dp_mst_helper.h>
#समावेश "modules/inc/mod_freesync.h"
#समावेश "amdgpu_dm_irq_params.h"

काष्ठा amdgpu_bo;
काष्ठा amdgpu_device;
काष्ठा amdgpu_encoder;
काष्ठा amdgpu_router;
काष्ठा amdgpu_hpd;

#घोषणा to_amdgpu_crtc(x) container_of(x, काष्ठा amdgpu_crtc, base)
#घोषणा to_amdgpu_connector(x) container_of(x, काष्ठा amdgpu_connector, base)
#घोषणा to_amdgpu_encoder(x) container_of(x, काष्ठा amdgpu_encoder, base)
#घोषणा to_amdgpu_framebuffer(x) container_of(x, काष्ठा amdgpu_framebuffer, base)

#घोषणा to_dm_plane_state(x)	container_of(x, काष्ठा dm_plane_state, base)

#घोषणा AMDGPU_MAX_HPD_PINS 6
#घोषणा AMDGPU_MAX_CRTCS 6
#घोषणा AMDGPU_MAX_PLANES 6
#घोषणा AMDGPU_MAX_AFMT_BLOCKS 9

क्रमागत amdgpu_rmx_type अणु
	RMX_OFF,
	RMX_FULL,
	RMX_CENTER,
	RMX_ASPECT
पूर्ण;

क्रमागत amdgpu_underscan_type अणु
	UNDERSCAN_OFF,
	UNDERSCAN_ON,
	UNDERSCAN_AUTO,
पूर्ण;

#घोषणा AMDGPU_HPD_CONNECT_INT_DELAY_IN_MS 50
#घोषणा AMDGPU_HPD_DISCONNECT_INT_DELAY_IN_MS 10

क्रमागत amdgpu_hpd_id अणु
	AMDGPU_HPD_1 = 0,
	AMDGPU_HPD_2,
	AMDGPU_HPD_3,
	AMDGPU_HPD_4,
	AMDGPU_HPD_5,
	AMDGPU_HPD_6,
	AMDGPU_HPD_NONE = 0xff,
पूर्ण;

क्रमागत amdgpu_crtc_irq अणु
	AMDGPU_CRTC_IRQ_VBLANK1 = 0,
	AMDGPU_CRTC_IRQ_VBLANK2,
	AMDGPU_CRTC_IRQ_VBLANK3,
	AMDGPU_CRTC_IRQ_VBLANK4,
	AMDGPU_CRTC_IRQ_VBLANK5,
	AMDGPU_CRTC_IRQ_VBLANK6,
	AMDGPU_CRTC_IRQ_VLINE1,
	AMDGPU_CRTC_IRQ_VLINE2,
	AMDGPU_CRTC_IRQ_VLINE3,
	AMDGPU_CRTC_IRQ_VLINE4,
	AMDGPU_CRTC_IRQ_VLINE5,
	AMDGPU_CRTC_IRQ_VLINE6,
	AMDGPU_CRTC_IRQ_NONE = 0xff
पूर्ण;

क्रमागत amdgpu_pageflip_irq अणु
	AMDGPU_PAGEFLIP_IRQ_D1 = 0,
	AMDGPU_PAGEFLIP_IRQ_D2,
	AMDGPU_PAGEFLIP_IRQ_D3,
	AMDGPU_PAGEFLIP_IRQ_D4,
	AMDGPU_PAGEFLIP_IRQ_D5,
	AMDGPU_PAGEFLIP_IRQ_D6,
	AMDGPU_PAGEFLIP_IRQ_NONE = 0xff
पूर्ण;

क्रमागत amdgpu_flip_status अणु
	AMDGPU_FLIP_NONE,
	AMDGPU_FLIP_PENDING,
	AMDGPU_FLIP_SUBMITTED
पूर्ण;

#घोषणा AMDGPU_MAX_I2C_BUS 16

/* amdgpu gpio-based i2c
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
काष्ठा amdgpu_i2c_bus_rec अणु
	bool valid;
	/* id used by atom */
	uपूर्णांक8_t i2c_id;
	/* id used by atom */
	क्रमागत amdgpu_hpd_id hpd;
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

#घोषणा AMDGPU_MAX_BIOS_CONNECTOR 16

/* pll flags */
#घोषणा AMDGPU_PLL_USE_BIOS_DIVS        (1 << 0)
#घोषणा AMDGPU_PLL_NO_ODD_POST_DIV      (1 << 1)
#घोषणा AMDGPU_PLL_USE_REF_DIV          (1 << 2)
#घोषणा AMDGPU_PLL_LEGACY               (1 << 3)
#घोषणा AMDGPU_PLL_PREFER_LOW_REF_DIV   (1 << 4)
#घोषणा AMDGPU_PLL_PREFER_HIGH_REF_DIV  (1 << 5)
#घोषणा AMDGPU_PLL_PREFER_LOW_FB_DIV    (1 << 6)
#घोषणा AMDGPU_PLL_PREFER_HIGH_FB_DIV   (1 << 7)
#घोषणा AMDGPU_PLL_PREFER_LOW_POST_DIV  (1 << 8)
#घोषणा AMDGPU_PLL_PREFER_HIGH_POST_DIV (1 << 9)
#घोषणा AMDGPU_PLL_USE_FRAC_FB_DIV      (1 << 10)
#घोषणा AMDGPU_PLL_PREFER_CLOSEST_LOWER (1 << 11)
#घोषणा AMDGPU_PLL_USE_POST_DIV         (1 << 12)
#घोषणा AMDGPU_PLL_IS_LCD               (1 << 13)
#घोषणा AMDGPU_PLL_PREFER_MINM_OVER_MAXP (1 << 14)

काष्ठा amdgpu_pll अणु
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

काष्ठा amdgpu_i2c_chan अणु
	काष्ठा i2c_adapter adapter;
	काष्ठा drm_device *dev;
	काष्ठा i2c_algo_bit_data bit;
	काष्ठा amdgpu_i2c_bus_rec rec;
	काष्ठा drm_dp_aux aux;
	bool has_aux;
	काष्ठा mutex mutex;
पूर्ण;

काष्ठा amdgpu_fbdev;

काष्ठा amdgpu_afmt अणु
	bool enabled;
	पूर्णांक offset;
	bool last_buffer_filled_status;
	पूर्णांक id;
	काष्ठा amdgpu_audio_pin *pin;
पूर्ण;

/*
 * Audio
 */
काष्ठा amdgpu_audio_pin अणु
	पूर्णांक			channels;
	पूर्णांक			rate;
	पूर्णांक			bits_per_sample;
	u8			status_bits;
	u8			category_code;
	u32			offset;
	bool			connected;
	u32			id;
पूर्ण;

काष्ठा amdgpu_audio अणु
	bool enabled;
	काष्ठा amdgpu_audio_pin pin[AMDGPU_MAX_AFMT_BLOCKS];
	पूर्णांक num_pins;
पूर्ण;

काष्ठा amdgpu_display_funcs अणु
	/* display watermarks */
	व्योम (*bandwidth_update)(काष्ठा amdgpu_device *adev);
	/* get frame count */
	u32 (*vblank_get_counter)(काष्ठा amdgpu_device *adev, पूर्णांक crtc);
	/* set backlight level */
	व्योम (*backlight_set_level)(काष्ठा amdgpu_encoder *amdgpu_encoder,
				    u8 level);
	/* get backlight level */
	u8 (*backlight_get_level)(काष्ठा amdgpu_encoder *amdgpu_encoder);
	/* hotplug detect */
	bool (*hpd_sense)(काष्ठा amdgpu_device *adev, क्रमागत amdgpu_hpd_id hpd);
	व्योम (*hpd_set_polarity)(काष्ठा amdgpu_device *adev,
				 क्रमागत amdgpu_hpd_id hpd);
	u32 (*hpd_get_gpio_reg)(काष्ठा amdgpu_device *adev);
	/* pageflipping */
	व्योम (*page_flip)(काष्ठा amdgpu_device *adev,
			  पूर्णांक crtc_id, u64 crtc_base, bool async);
	पूर्णांक (*page_flip_get_scanoutpos)(काष्ठा amdgpu_device *adev, पूर्णांक crtc,
					u32 *vbl, u32 *position);
	/* display topology setup */
	व्योम (*add_encoder)(काष्ठा amdgpu_device *adev,
			    uपूर्णांक32_t encoder_क्रमागत,
			    uपूर्णांक32_t supported_device,
			    u16 caps);
	व्योम (*add_connector)(काष्ठा amdgpu_device *adev,
			      uपूर्णांक32_t connector_id,
			      uपूर्णांक32_t supported_device,
			      पूर्णांक connector_type,
			      काष्ठा amdgpu_i2c_bus_rec *i2c_bus,
			      uपूर्णांक16_t connector_object_id,
			      काष्ठा amdgpu_hpd *hpd,
			      काष्ठा amdgpu_router *router);


पूर्ण;

काष्ठा amdgpu_framebuffer अणु
	काष्ठा drm_framebuffer base;

	uपूर्णांक64_t tiling_flags;
	bool पंचांगz_surface;

	/* caching क्रम later use */
	uपूर्णांक64_t address;
पूर्ण;

काष्ठा amdgpu_fbdev अणु
	काष्ठा drm_fb_helper helper;
	काष्ठा amdgpu_framebuffer rfb;
	काष्ठा list_head fbdev_list;
	काष्ठा amdgpu_device *adev;
पूर्ण;

काष्ठा amdgpu_mode_info अणु
	काष्ठा atom_context *atom_context;
	काष्ठा card_info *atom_card_info;
	bool mode_config_initialized;
	काष्ठा amdgpu_crtc *crtcs[AMDGPU_MAX_CRTCS];
	काष्ठा drm_plane *planes[AMDGPU_MAX_PLANES];
	काष्ठा amdgpu_afmt *afmt[AMDGPU_MAX_AFMT_BLOCKS];
	/* DVI-I properties */
	काष्ठा drm_property *coherent_mode_property;
	/* DAC enable load detect */
	काष्ठा drm_property *load_detect_property;
	/* underscan */
	काष्ठा drm_property *underscan_property;
	काष्ठा drm_property *underscan_hborder_property;
	काष्ठा drm_property *underscan_vborder_property;
	/* audio */
	काष्ठा drm_property *audio_property;
	/* FMT dithering */
	काष्ठा drm_property *dither_property;
	/* Adaptive Backlight Modulation (घातer feature) */
	काष्ठा drm_property *abm_level_property;
	/* hardcoded DFP edid from BIOS */
	काष्ठा edid *bios_hardcoded_edid;
	पूर्णांक bios_hardcoded_edid_size;

	/* poपूर्णांकer to fbdev info काष्ठाure */
	काष्ठा amdgpu_fbdev *rfbdev;
	/* firmware flags */
	u16 firmware_flags;
	/* poपूर्णांकer to backlight encoder */
	काष्ठा amdgpu_encoder *bl_encoder;
	u8 bl_level; /* saved backlight level */
	काष्ठा amdgpu_audio	audio; /* audio stuff */
	पूर्णांक			num_crtc; /* number of crtcs */
	पूर्णांक			num_hpd; /* number of hpd pins */
	पूर्णांक			num_dig; /* number of dig blocks */
	पूर्णांक			disp_priority;
	स्थिर काष्ठा amdgpu_display_funcs *funcs;
	स्थिर क्रमागत drm_plane_type *plane_type;
पूर्ण;

#घोषणा AMDGPU_MAX_BL_LEVEL 0xFF

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)

काष्ठा amdgpu_backlight_privdata अणु
	काष्ठा amdgpu_encoder *encoder;
	uपूर्णांक8_t negative;
पूर्ण;

#पूर्ण_अगर

काष्ठा amdgpu_atom_ss अणु
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

काष्ठा amdgpu_crtc अणु
	काष्ठा drm_crtc base;
	पूर्णांक crtc_id;
	bool enabled;
	bool can_tile;
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
	क्रमागत amdgpu_rmx_type rmx_type;
	u8 h_border;
	u8 v_border;
	fixed20_12 vsc;
	fixed20_12 hsc;
	काष्ठा drm_display_mode native_mode;
	u32 pll_id;
	/* page flipping */
	काष्ठा amdgpu_flip_work *pflip_works;
	क्रमागत amdgpu_flip_status pflip_status;
	पूर्णांक deferred_flip_completion;
	/* parameters access from DM IRQ handler */
	काष्ठा dm_irq_params dm_irq_params;
	/* pll sharing */
	काष्ठा amdgpu_atom_ss ss;
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
	/* क्रम भव dce */
	काष्ठा hrसमयr vblank_समयr;
	क्रमागत amdgpu_पूर्णांकerrupt_state vsync_समयr_enabled;

	पूर्णांक otg_inst;
	काष्ठा drm_pending_vblank_event *event;
पूर्ण;

काष्ठा amdgpu_encoder_atom_dig अणु
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
	काष्ठा amdgpu_afmt *afmt;
पूर्ण;

काष्ठा amdgpu_encoder अणु
	काष्ठा drm_encoder base;
	uपूर्णांक32_t encoder_क्रमागत;
	uपूर्णांक32_t encoder_id;
	uपूर्णांक32_t devices;
	uपूर्णांक32_t active_device;
	uपूर्णांक32_t flags;
	uपूर्णांक32_t pixel_घड़ी;
	क्रमागत amdgpu_rmx_type rmx_type;
	क्रमागत amdgpu_underscan_type underscan_type;
	uपूर्णांक32_t underscan_hborder;
	uपूर्णांक32_t underscan_vborder;
	काष्ठा drm_display_mode native_mode;
	व्योम *enc_priv;
	पूर्णांक audio_polling_active;
	bool is_ext_encoder;
	u16 caps;
पूर्ण;

काष्ठा amdgpu_connector_atom_dig अणु
	/* displayport */
	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	u8 करोwnstream_ports[DP_MAX_DOWNSTREAM_PORTS];
	u8 dp_sink_type;
	पूर्णांक dp_घड़ी;
	पूर्णांक dp_lane_count;
	bool edp_on;
पूर्ण;

काष्ठा amdgpu_gpio_rec अणु
	bool valid;
	u8 id;
	u32 reg;
	u32 mask;
	u32 shअगरt;
पूर्ण;

काष्ठा amdgpu_hpd अणु
	क्रमागत amdgpu_hpd_id hpd;
	u8 plugged_state;
	काष्ठा amdgpu_gpio_rec gpio;
पूर्ण;

काष्ठा amdgpu_router अणु
	u32 router_id;
	काष्ठा amdgpu_i2c_bus_rec i2c_info;
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

क्रमागत amdgpu_connector_audio अणु
	AMDGPU_AUDIO_DISABLE = 0,
	AMDGPU_AUDIO_ENABLE = 1,
	AMDGPU_AUDIO_AUTO = 2
पूर्ण;

क्रमागत amdgpu_connector_dither अणु
	AMDGPU_FMT_DITHER_DISABLE = 0,
	AMDGPU_FMT_DITHER_ENABLE = 1,
पूर्ण;

काष्ठा amdgpu_dm_dp_aux अणु
	काष्ठा drm_dp_aux aux;
	काष्ठा ddc_service *ddc_service;
पूर्ण;

काष्ठा amdgpu_i2c_adapter अणु
	काष्ठा i2c_adapter base;

	काष्ठा ddc_service *ddc_service;
पूर्ण;

#घोषणा TO_DM_AUX(x) container_of((x), काष्ठा amdgpu_dm_dp_aux, aux)

काष्ठा amdgpu_connector अणु
	काष्ठा drm_connector base;
	uपूर्णांक32_t connector_id;
	uपूर्णांक32_t devices;
	काष्ठा amdgpu_i2c_chan *ddc_bus;
	/* some प्रणालीs have an hdmi and vga port with a shared ddc line */
	bool shared_ddc;
	bool use_digital;
	/* we need to mind the EDID between detect
	   and get modes due to analog/digital/tvencoder */
	काष्ठा edid *edid;
	व्योम *con_priv;
	bool dac_load_detect;
	bool detected_by_load; /* अगर the connection status was determined by load */
	uपूर्णांक16_t connector_object_id;
	काष्ठा amdgpu_hpd hpd;
	काष्ठा amdgpu_router router;
	काष्ठा amdgpu_i2c_chan *router_bus;
	क्रमागत amdgpu_connector_audio audio;
	क्रमागत amdgpu_connector_dither dither;
	अचिन्हित pixelघड़ी_क्रम_modeset;
पूर्ण;

/* TODO: start to use this काष्ठा and हटाओ same field from base one */
काष्ठा amdgpu_mst_connector अणु
	काष्ठा amdgpu_connector base;

	काष्ठा drm_dp_mst_topology_mgr mst_mgr;
	काष्ठा amdgpu_dm_dp_aux dm_dp_aux;
	काष्ठा drm_dp_mst_port *port;
	काष्ठा amdgpu_connector *mst_port;
	bool is_mst_connector;
	काष्ठा amdgpu_encoder *mst_encoder;
पूर्ण;

#घोषणा ENCODER_MODE_IS_DP(em) (((em) == ATOM_ENCODER_MODE_DP) || \
				((em) == ATOM_ENCODER_MODE_DP_MST))

/* Driver पूर्णांकernal use only flags of amdgpu_display_get_crtc_scanoutpos() */
#घोषणा DRM_SCANOUTPOS_VALID        (1 << 0)
#घोषणा DRM_SCANOUTPOS_IN_VBLANK    (1 << 1)
#घोषणा DRM_SCANOUTPOS_ACCURATE     (1 << 2)
#घोषणा USE_REAL_VBLANKSTART		(1 << 30)
#घोषणा GET_DISTANCE_TO_VBLANKSTART	(1 << 31)

व्योम amdgpu_link_encoder_connector(काष्ठा drm_device *dev);

काष्ठा drm_connector *
amdgpu_get_connector_क्रम_encoder(काष्ठा drm_encoder *encoder);
काष्ठा drm_connector *
amdgpu_get_connector_क्रम_encoder_init(काष्ठा drm_encoder *encoder);
bool amdgpu_dig_monitor_is_duallink(काष्ठा drm_encoder *encoder,
				    u32 pixel_घड़ी);

u16 amdgpu_encoder_get_dp_bridge_encoder_id(काष्ठा drm_encoder *encoder);
काष्ठा drm_encoder *amdgpu_get_बाह्यal_encoder(काष्ठा drm_encoder *encoder);

bool amdgpu_display_ddc_probe(काष्ठा amdgpu_connector *amdgpu_connector,
			      bool use_aux);

व्योम amdgpu_encoder_set_active_device(काष्ठा drm_encoder *encoder);

पूर्णांक amdgpu_display_get_crtc_scanoutpos(काष्ठा drm_device *dev,
			अचिन्हित पूर्णांक pipe, अचिन्हित पूर्णांक flags, पूर्णांक *vpos,
			पूर्णांक *hpos, kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
			स्थिर काष्ठा drm_display_mode *mode);

पूर्णांक amdgpu_display_gem_fb_init(काष्ठा drm_device *dev,
			       काष्ठा amdgpu_framebuffer *rfb,
			       स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
			       काष्ठा drm_gem_object *obj);
पूर्णांक amdgpu_display_gem_fb_verअगरy_and_init(
	काष्ठा drm_device *dev, काष्ठा amdgpu_framebuffer *rfb,
	काष्ठा drm_file *file_priv, स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
	काष्ठा drm_gem_object *obj);
पूर्णांक amdgpu_display_framebuffer_init(काष्ठा drm_device *dev,
				    काष्ठा amdgpu_framebuffer *rfb,
				    स्थिर काष्ठा drm_mode_fb_cmd2 *mode_cmd,
				    काष्ठा drm_gem_object *obj);

पूर्णांक amdgpufb_हटाओ(काष्ठा drm_device *dev, काष्ठा drm_framebuffer *fb);

व्योम amdgpu_enc_destroy(काष्ठा drm_encoder *encoder);
व्योम amdgpu_copy_fb(काष्ठा drm_device *dev, काष्ठा drm_gem_object *dst_obj);
bool amdgpu_display_crtc_scaling_mode_fixup(काष्ठा drm_crtc *crtc,
				स्थिर काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode);
व्योम amdgpu_panel_mode_fixup(काष्ठा drm_encoder *encoder,
			     काष्ठा drm_display_mode *adjusted_mode);
पूर्णांक amdgpu_display_crtc_idx_to_irq_type(काष्ठा amdgpu_device *adev, पूर्णांक crtc);

bool amdgpu_crtc_get_scanout_position(काष्ठा drm_crtc *crtc,
			bool in_vblank_irq, पूर्णांक *vpos,
			पूर्णांक *hpos, kसमय_प्रकार *sसमय, kसमय_प्रकार *eसमय,
			स्थिर काष्ठा drm_display_mode *mode);

/* fbdev layer */
पूर्णांक amdgpu_fbdev_init(काष्ठा amdgpu_device *adev);
व्योम amdgpu_fbdev_fini(काष्ठा amdgpu_device *adev);
व्योम amdgpu_fbdev_set_suspend(काष्ठा amdgpu_device *adev, पूर्णांक state);
पूर्णांक amdgpu_fbdev_total_size(काष्ठा amdgpu_device *adev);
bool amdgpu_fbdev_robj_is_fb(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_bo *robj);

पूर्णांक amdgpu_align_pitch(काष्ठा amdgpu_device *adev, पूर्णांक width, पूर्णांक bpp, bool tiled);

/* amdgpu_display.c */
व्योम amdgpu_display_prपूर्णांक_display_setup(काष्ठा drm_device *dev);
पूर्णांक amdgpu_display_modeset_create_props(काष्ठा amdgpu_device *adev);
पूर्णांक amdgpu_display_crtc_set_config(काष्ठा drm_mode_set *set,
				   काष्ठा drm_modeset_acquire_ctx *ctx);
पूर्णांक amdgpu_display_crtc_page_flip_target(काष्ठा drm_crtc *crtc,
				काष्ठा drm_framebuffer *fb,
				काष्ठा drm_pending_vblank_event *event,
				uपूर्णांक32_t page_flip_flags, uपूर्णांक32_t target,
				काष्ठा drm_modeset_acquire_ctx *ctx);
बाह्य स्थिर काष्ठा drm_mode_config_funcs amdgpu_mode_funcs;

#पूर्ण_अगर
