<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_GRPH_OBJECT_CTRL_DEFS_H__
#घोषणा __DAL_GRPH_OBJECT_CTRL_DEFS_H__

#समावेश "grph_object_defs.h"

/*
 * #####################################################
 * #####################################################
 *
 * These defines shared between asic_control/bios_parser and other
 * DAL components
 *
 * #####################################################
 * #####################################################
 */

क्रमागत display_output_bit_depth अणु
	PANEL_UNDEFINE = 0,
	PANEL_6BIT_COLOR = 1,
	PANEL_8BIT_COLOR = 2,
	PANEL_10BIT_COLOR = 3,
	PANEL_12BIT_COLOR = 4,
	PANEL_16BIT_COLOR = 5,
पूर्ण;


/* Device type as असलtracted by ATOM BIOS */
क्रमागत dal_device_type अणु
	DEVICE_TYPE_UNKNOWN = 0,
	DEVICE_TYPE_LCD,
	DEVICE_TYPE_CRT,
	DEVICE_TYPE_DFP,
	DEVICE_TYPE_CV,
	DEVICE_TYPE_TV,
	DEVICE_TYPE_CF,
	DEVICE_TYPE_WIRELESS
पूर्ण;

/* Device ID as असलtracted by ATOM BIOS */
काष्ठा device_id अणु
	क्रमागत dal_device_type device_type:16;
	uपूर्णांक32_t क्रमागत_id:16;	/* 1 based क्रमागत */
	uपूर्णांक16_t raw_device_tag;
पूर्ण;

काष्ठा graphics_object_i2c_info अणु
	काष्ठा gpio_info अणु
		uपूर्णांक32_t clk_mask_रेजिस्टर_index;
		uपूर्णांक32_t clk_en_रेजिस्टर_index;
		uपूर्णांक32_t clk_y_रेजिस्टर_index;
		uपूर्णांक32_t clk_a_रेजिस्टर_index;
		uपूर्णांक32_t data_mask_रेजिस्टर_index;
		uपूर्णांक32_t data_en_रेजिस्टर_index;
		uपूर्णांक32_t data_y_रेजिस्टर_index;
		uपूर्णांक32_t data_a_रेजिस्टर_index;

		uपूर्णांक32_t clk_mask_shअगरt;
		uपूर्णांक32_t clk_en_shअगरt;
		uपूर्णांक32_t clk_y_shअगरt;
		uपूर्णांक32_t clk_a_shअगरt;
		uपूर्णांक32_t data_mask_shअगरt;
		uपूर्णांक32_t data_en_shअगरt;
		uपूर्णांक32_t data_y_shअगरt;
		uपूर्णांक32_t data_a_shअगरt;
	पूर्ण gpio_info;

	bool i2c_hw_assist;
	uपूर्णांक32_t i2c_line;
	uपूर्णांक32_t i2c_engine_id;
	uपूर्णांक32_t i2c_slave_address;
पूर्ण;

काष्ठा graphics_object_hpd_info अणु
	uपूर्णांक8_t hpd_पूर्णांक_gpio_uid;
	uपूर्णांक8_t hpd_active;
पूर्ण;

काष्ठा connector_device_tag_info अणु
	uपूर्णांक32_t acpi_device;
	काष्ठा device_id dev_id;
पूर्ण;

काष्ठा device_timing अणु
	काष्ठा misc_info अणु
		uपूर्णांक32_t HORIZONTAL_CUT_OFF:1;
		/* 0=Active High, 1=Active Low */
		uपूर्णांक32_t H_SYNC_POLARITY:1;
		/* 0=Active High, 1=Active Low */
		uपूर्णांक32_t V_SYNC_POLARITY:1;
		uपूर्णांक32_t VERTICAL_CUT_OFF:1;
		uपूर्णांक32_t H_REPLICATION_BY2:1;
		uपूर्णांक32_t V_REPLICATION_BY2:1;
		uपूर्णांक32_t COMPOSITE_SYNC:1;
		uपूर्णांक32_t INTERLACE:1;
		uपूर्णांक32_t DOUBLE_CLOCK:1;
		uपूर्णांक32_t RGB888:1;
		uपूर्णांक32_t GREY_LEVEL:2;
		uपूर्णांक32_t SPATIAL:1;
		uपूर्णांक32_t TEMPORAL:1;
		uपूर्णांक32_t API_ENABLED:1;
	पूर्ण misc_info;

	uपूर्णांक32_t pixel_clk; /* in KHz */
	uपूर्णांक32_t horizontal_addressable;
	uपूर्णांक32_t horizontal_blanking_समय;
	uपूर्णांक32_t vertical_addressable;
	uपूर्णांक32_t vertical_blanking_समय;
	uपूर्णांक32_t horizontal_sync_offset;
	uपूर्णांक32_t horizontal_sync_width;
	uपूर्णांक32_t vertical_sync_offset;
	uपूर्णांक32_t vertical_sync_width;
	uपूर्णांक32_t horizontal_border;
	uपूर्णांक32_t vertical_border;
पूर्ण;

काष्ठा supported_refresh_rate अणु
	uपूर्णांक32_t REFRESH_RATE_30HZ:1;
	uपूर्णांक32_t REFRESH_RATE_40HZ:1;
	uपूर्णांक32_t REFRESH_RATE_48HZ:1;
	uपूर्णांक32_t REFRESH_RATE_50HZ:1;
	uपूर्णांक32_t REFRESH_RATE_60HZ:1;
पूर्ण;

काष्ठा embedded_panel_info अणु
	काष्ठा device_timing lcd_timing;
	uपूर्णांक32_t ss_id;
	काष्ठा supported_refresh_rate supported_rr;
	uपूर्णांक32_t drr_enabled;
	uपूर्णांक32_t min_drr_refresh_rate;
	bool realtek_eDPToLVDS;
पूर्ण;

काष्ठा dc_firmware_info अणु
	काष्ठा pll_info अणु
		uपूर्णांक32_t crystal_frequency; /* in KHz */
		uपूर्णांक32_t min_input_pxl_clk_pll_frequency; /* in KHz */
		uपूर्णांक32_t max_input_pxl_clk_pll_frequency; /* in KHz */
		uपूर्णांक32_t min_output_pxl_clk_pll_frequency; /* in KHz */
		uपूर्णांक32_t max_output_pxl_clk_pll_frequency; /* in KHz */
	पूर्ण pll_info;

	काष्ठा firmware_feature अणु
		uपूर्णांक32_t memory_clk_ss_percentage;
		uपूर्णांक32_t engine_clk_ss_percentage;
	पूर्ण feature;

	uपूर्णांक32_t शेष_display_engine_pll_frequency; /* in KHz */
	uपूर्णांक32_t बाह्यal_घड़ी_source_frequency_क्रम_dp; /* in KHz */
	uपूर्णांक32_t smu_gpu_pll_output_freq; /* in KHz */
	uपूर्णांक8_t min_allowed_bl_level;
	uपूर्णांक8_t remote_display_config;
	uपूर्णांक32_t शेष_memory_clk; /* in KHz */
	uपूर्णांक32_t शेष_engine_clk; /* in KHz */
	uपूर्णांक32_t dp_phy_ref_clk; /* in KHz - DCE12 only */
	uपूर्णांक32_t i2c_engine_ref_clk; /* in KHz - DCE12 only */
	bool oem_i2c_present;
	uपूर्णांक8_t oem_i2c_obj_id;

पूर्ण;

काष्ठा dc_vram_info अणु
	अचिन्हित पूर्णांक num_chans;
	अचिन्हित पूर्णांक dram_channel_width_bytes;
पूर्ण;

काष्ठा step_and_delay_info अणु
	uपूर्णांक32_t step;
	uपूर्णांक32_t delay;
	uपूर्णांक32_t recommended_ref_भाग;
पूर्ण;

काष्ठा spपढ़ो_spectrum_info अणु
	काष्ठा spपढ़ो_spectrum_type अणु
		bool CENTER_MODE:1;
		bool EXTERNAL:1;
		bool STEP_AND_DELAY_INFO:1;
	पूर्ण type;

	/* in unit of 0.01% (spपढ़ोPercentageDivider = 100),
	otherwise in 0.001% units (spपढ़ोPercentageDivider = 1000); */
	uपूर्णांक32_t spपढ़ो_spectrum_percentage;
	uपूर्णांक32_t spपढ़ो_percentage_भागider; /* 100 or 1000 */
	uपूर्णांक32_t spपढ़ो_spectrum_range; /* modulation freq (HZ)*/

	जोड़ अणु
		काष्ठा step_and_delay_info step_and_delay_info;
		/* For mem/engine/uvd, Clock Out frequence (VCO ),
		in unit of kHz. For TMDS/HDMI/LVDS, it is pixel घड़ी,
		क्रम DP, it is link घड़ी ( 270000 or 162000 ) */
		uपूर्णांक32_t target_घड़ी_range; /* in KHz */
	पूर्ण;

पूर्ण;

काष्ठा graphics_object_encoder_cap_info अणु
	uपूर्णांक32_t dp_hbr2_cap:1;
	uपूर्णांक32_t dp_hbr2_validated:1;
	/*
	 * TODO: added MST and HDMI 6G capable flags
	 */
	uपूर्णांक32_t reserved:15;
पूर्ण;

काष्ठा din_connector_info अणु
	uपूर्णांक32_t gpio_id;
	bool gpio_tv_active_state;
पूर्ण;

/* Invalid channel mapping */
क्रमागत अणु INVALID_DDI_CHANNEL_MAPPING = 0x0 पूर्ण;

/**
 * DDI PHY channel mapping reflecting XBAR setting
 */
जोड़ ddi_channel_mapping अणु
	काष्ठा mapping अणु
		uपूर्णांक8_t lane0:2;	/* Mapping क्रम lane 0 */
		uपूर्णांक8_t lane1:2;	/* Mapping क्रम lane 1 */
		uपूर्णांक8_t lane2:2;	/* Mapping क्रम lane 2 */
		uपूर्णांक8_t lane3:2;	/* Mapping क्रम lane 3 */
	पूर्ण mapping;
	uपूर्णांक8_t raw;
पूर्ण;

/**
* Transmitter output configuration description
*/
काष्ठा transmitter_configuration_info अणु
	/* DDI PHY ID क्रम the transmitter */
	क्रमागत transmitter transmitter_phy_id;
	/* DDI PHY channel mapping reflecting crossbar setting */
	जोड़ ddi_channel_mapping output_channel_mapping;
पूर्ण;

काष्ठा transmitter_configuration अणु
	/* Configuration क्रम the primary transmitter */
	काष्ठा transmitter_configuration_info primary_transmitter_config;
	/* Secondary transmitter configuration क्रम Dual-link DVI */
	काष्ठा transmitter_configuration_info secondary_transmitter_config;
पूर्ण;

/* These size should be sufficient to store info coming from BIOS */
#घोषणा NUMBER_OF_UCHAR_FOR_GUID 16
#घोषणा MAX_NUMBER_OF_EXT_DISPLAY_PATH 7
#घोषणा NUMBER_OF_CSR_M3_ARB 10
#घोषणा NUMBER_OF_DISP_CLK_VOLTAGE 4
#घोषणा NUMBER_OF_AVAILABLE_SCLK 5

काष्ठा i2c_reg_info अणु
	अचिन्हित अक्षर       i2c_reg_index;
	अचिन्हित अक्षर       i2c_reg_val;
पूर्ण;

काष्ठा ext_hdmi_settings अणु
	अचिन्हित अक्षर   slv_addr;
	अचिन्हित अक्षर   reg_num;
	काष्ठा i2c_reg_info      reg_settings[9];
	अचिन्हित अक्षर   reg_num_6g;
	काष्ठा i2c_reg_info      reg_settings_6g[3];
पूर्ण;

काष्ठा edp_info अणु
	uपूर्णांक16_t edp_backlight_pwm_hz;
	uपूर्णांक16_t edp_ss_percentage;
	uपूर्णांक16_t edp_ss_rate_10hz;
	uपूर्णांक8_t  edp_pwr_on_off_delay;
	uपूर्णांक8_t  edp_pwr_on_vary_bl_to_blon;
	uपूर्णांक8_t  edp_pwr_करोwn_bloff_to_vary_bloff;
	uपूर्णांक8_t  edp_panel_bpc;
	uपूर्णांक8_t  edp_bootup_bl_level;
पूर्ण;

/* V6 */
काष्ठा पूर्णांकegrated_info अणु
	काष्ठा घड़ी_voltage_caps अणु
		/* The Voltage Index indicated by FUSE, same voltage index
		shared with SCLK DPM fuse table */
		uपूर्णांक32_t voltage_index;
		/* Maximum घड़ी supported with specअगरied voltage index */
		uपूर्णांक32_t max_supported_clk; /* in KHz */
	पूर्ण disp_clk_voltage[NUMBER_OF_DISP_CLK_VOLTAGE];

	काष्ठा display_connection_info अणु
		काष्ठा बाह्यal_display_path अणु
			/* A bit vector to show what devices are supported */
			uपूर्णांक32_t device_tag;
			/* 16bit device ACPI id. */
			uपूर्णांक32_t device_acpi_क्रमागत;
			/* A physical connector क्रम displays to plug in,
			using object connector definitions */
			काष्ठा graphics_object_id device_connector_id;
			/* An index पूर्णांकo बाह्यal AUX/DDC channel LUT */
			uपूर्णांक8_t ext_aux_ddc_lut_index;
			/* An index पूर्णांकo बाह्यal HPD pin LUT */
			uपूर्णांक8_t ext_hpd_pin_lut_index;
			/* बाह्यal encoder object id */
			काष्ठा graphics_object_id ext_encoder_obj_id;
			/* XBAR mapping of the PHY channels */
			जोड़ ddi_channel_mapping channel_mapping;

			अचिन्हित लघु caps;
		पूर्ण path[MAX_NUMBER_OF_EXT_DISPLAY_PATH];

		uपूर्णांक8_t gu_id[NUMBER_OF_UCHAR_FOR_GUID];
		uपूर्णांक8_t checksum;
	पूर्ण ext_disp_conn_info; /* निकासing दीर्घ दीर्घ समय */

	काष्ठा available_s_clk_list अणु
		/* Maximum घड़ी supported with specअगरied voltage index */
		uपूर्णांक32_t supported_s_clk; /* in KHz */
		/* The Voltage Index indicated by FUSE क्रम specअगरied SCLK */
		uपूर्णांक32_t voltage_index;
		/* The Voltage ID indicated by FUSE क्रम specअगरied SCLK */
		uपूर्णांक32_t voltage_id;
	पूर्ण avail_s_clk[NUMBER_OF_AVAILABLE_SCLK];

	uपूर्णांक8_t memory_type;
	uपूर्णांक8_t ma_channel_number;
	uपूर्णांक32_t boot_up_engine_घड़ी; /* in KHz */
	uपूर्णांक32_t dentist_vco_freq; /* in KHz */
	uपूर्णांक32_t boot_up_uma_घड़ी; /* in KHz */
	uपूर्णांक32_t boot_up_req_display_vector;
	uपूर्णांक32_t other_display_misc;
	uपूर्णांक32_t gpu_cap_info;
	uपूर्णांक32_t sb_mmio_base_addr;
	uपूर्णांक32_t प्रणाली_config;
	uपूर्णांक32_t cpu_cap_info;
	uपूर्णांक32_t max_nb_voltage;
	uपूर्णांक32_t min_nb_voltage;
	uपूर्णांक32_t boot_up_nb_voltage;
	uपूर्णांक32_t ext_disp_conn_info_offset;
	uपूर्णांक32_t csr_m3_arb_cntl_शेष[NUMBER_OF_CSR_M3_ARB];
	uपूर्णांक32_t csr_m3_arb_cntl_uvd[NUMBER_OF_CSR_M3_ARB];
	uपूर्णांक32_t csr_m3_arb_cntl_fs3d[NUMBER_OF_CSR_M3_ARB];
	uपूर्णांक32_t gmc_restore_reset_समय;
	uपूर्णांक32_t minimum_n_clk;
	uपूर्णांक32_t idle_n_clk;
	uपूर्णांक32_t ddr_dll_घातer_up_समय;
	uपूर्णांक32_t ddr_pll_घातer_up_समय;
	/* start क्रम V6 */
	uपूर्णांक32_t pcie_clk_ss_type;
	uपूर्णांक32_t lvds_ss_percentage;
	uपूर्णांक32_t lvds_sspपढ़ो_rate_in_10hz;
	uपूर्णांक32_t hdmi_ss_percentage;
	uपूर्णांक32_t hdmi_sspपढ़ो_rate_in_10hz;
	uपूर्णांक32_t dvi_ss_percentage;
	uपूर्णांक32_t dvi_sspपढ़ो_rate_in_10_hz;
	uपूर्णांक32_t sclk_dpm_boost_margin;
	uपूर्णांक32_t sclk_dpm_throttle_margin;
	uपूर्णांक32_t sclk_dpm_tdp_limit_pg;
	uपूर्णांक32_t sclk_dpm_tdp_limit_boost;
	uपूर्णांक32_t boost_engine_घड़ी;
	uपूर्णांक32_t boost_vid_2bit;
	uपूर्णांक32_t enable_boost;
	uपूर्णांक32_t gnb_tdp_limit;
	/* Start from V7 */
	uपूर्णांक32_t max_lvds_pclk_freq_in_single_link;
	uपूर्णांक32_t lvds_misc;
	uपूर्णांक32_t lvds_pwr_on_seq_dig_on_to_de_in_4ms;
	uपूर्णांक32_t lvds_pwr_on_seq_de_to_vary_bl_in_4ms;
	uपूर्णांक32_t lvds_pwr_off_seq_vary_bl_to_de_in4ms;
	uपूर्णांक32_t lvds_pwr_off_seq_de_to_dig_on_in4ms;
	uपूर्णांक32_t lvds_off_to_on_delay_in_4ms;
	uपूर्णांक32_t lvds_pwr_on_seq_vary_bl_to_blon_in_4ms;
	uपूर्णांक32_t lvds_pwr_off_seq_blon_to_vary_bl_in_4ms;
	uपूर्णांक32_t lvds_reserved1;
	uपूर्णांक32_t lvds_bit_depth_control_val;
	//Start from V9
	अचिन्हित अक्षर dp0_ext_hdmi_slv_addr;
	अचिन्हित अक्षर dp0_ext_hdmi_reg_num;
	काष्ठा i2c_reg_info dp0_ext_hdmi_reg_settings[9];
	अचिन्हित अक्षर dp0_ext_hdmi_6g_reg_num;
	काष्ठा i2c_reg_info dp0_ext_hdmi_6g_reg_settings[3];
	अचिन्हित अक्षर dp1_ext_hdmi_slv_addr;
	अचिन्हित अक्षर dp1_ext_hdmi_reg_num;
	काष्ठा i2c_reg_info dp1_ext_hdmi_reg_settings[9];
	अचिन्हित अक्षर dp1_ext_hdmi_6g_reg_num;
	काष्ठा i2c_reg_info dp1_ext_hdmi_6g_reg_settings[3];
	अचिन्हित अक्षर dp2_ext_hdmi_slv_addr;
	अचिन्हित अक्षर dp2_ext_hdmi_reg_num;
	काष्ठा i2c_reg_info dp2_ext_hdmi_reg_settings[9];
	अचिन्हित अक्षर dp2_ext_hdmi_6g_reg_num;
	काष्ठा i2c_reg_info dp2_ext_hdmi_6g_reg_settings[3];
	अचिन्हित अक्षर dp3_ext_hdmi_slv_addr;
	अचिन्हित अक्षर dp3_ext_hdmi_reg_num;
	काष्ठा i2c_reg_info dp3_ext_hdmi_reg_settings[9];
	अचिन्हित अक्षर dp3_ext_hdmi_6g_reg_num;
	काष्ठा i2c_reg_info dp3_ext_hdmi_6g_reg_settings[3];
	/* V11 */
	uपूर्णांक32_t dp_ss_control;
	/* V2.1 */
	काष्ठा edp_info edp1_info;
	काष्ठा edp_info edp2_info;
पूर्ण;

/**
* Power source ids.
*/
क्रमागत घातer_source अणु
	POWER_SOURCE_AC = 0,
	POWER_SOURCE_DC,
	POWER_SOURCE_LIMITED_POWER,
	POWER_SOURCE_LIMITED_POWER_2,
	POWER_SOURCE_MAX
पूर्ण;

काष्ठा bios_event_info अणु
	uपूर्णांक32_t thermal_state;
	uपूर्णांक32_t backlight_level;
	क्रमागत घातer_source घातerSource;
	bool has_thermal_state_changed;
	bool has_घातer_source_changed;
	bool has_क्रमced_mode_changed;
	bool क्रमced_mode;
	bool backlight_changed;
पूर्ण;

/*
 * DFS-bypass flag
 */
/* Copy of SYS_INFO_GPUCAPS__ENABEL_DFS_BYPASS from atomमूलप्रण.स */
क्रमागत अणु
	DFS_BYPASS_ENABLE = 0x10
पूर्ण;

क्रमागत अणु
	INVALID_BACKLIGHT = -1
पूर्ण;

काष्ठा panel_backlight_boundaries अणु
	uपूर्णांक32_t min_संकेत_level;
	uपूर्णांक32_t max_संकेत_level;
पूर्ण;


#पूर्ण_अगर
