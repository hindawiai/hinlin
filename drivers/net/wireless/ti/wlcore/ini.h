<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __INI_H__
#घोषणा __INI_H__

#घोषणा GENERAL_SETTINGS_DRPW_LPD 0xc0
#घोषणा SCRATCH_ENABLE_LPD        BIT(25)

#घोषणा WL1271_INI_MAX_SMART_REFLEX_PARAM 16

काष्ठा wl1271_ini_general_params अणु
	u8 ref_घड़ी;
	u8 settling_समय;
	u8 clk_valid_on_wakeup;
	u8 dc2dc_mode;
	u8 dual_mode_select;
	u8 tx_bip_fem_स्वतः_detect;
	u8 tx_bip_fem_manufacturer;
	u8 general_settings;
	u8 sr_state;
	u8 srf1[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 srf2[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 srf3[WL1271_INI_MAX_SMART_REFLEX_PARAM];
पूर्ण __packed;

#घोषणा WL128X_INI_MAX_SETTINGS_PARAM 4

काष्ठा wl128x_ini_general_params अणु
	u8 ref_घड़ी;
	u8 settling_समय;
	u8 clk_valid_on_wakeup;
	u8 tcxo_ref_घड़ी;
	u8 tcxo_settling_समय;
	u8 tcxo_valid_on_wakeup;
	u8 tcxo_lकरो_voltage;
	u8 xtal_itrim_val;
	u8 platक्रमm_conf;
	u8 dual_mode_select;
	u8 tx_bip_fem_स्वतः_detect;
	u8 tx_bip_fem_manufacturer;
	u8 general_settings[WL128X_INI_MAX_SETTINGS_PARAM];
	u8 sr_state;
	u8 srf1[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 srf2[WL1271_INI_MAX_SMART_REFLEX_PARAM];
	u8 srf3[WL1271_INI_MAX_SMART_REFLEX_PARAM];
पूर्ण __packed;

#घोषणा WL1271_INI_RSSI_PROCESS_COMPENS_SIZE 15

काष्ठा wl1271_ini_band_params_2 अणु
	u8 rx_trace_insertion_loss;
	u8 tx_trace_loss;
	u8 rx_rssi_process_compens[WL1271_INI_RSSI_PROCESS_COMPENS_SIZE];
पूर्ण __packed;

#घोषणा WL1271_INI_CHANNEL_COUNT_2 14

काष्ठा wl128x_ini_band_params_2 अणु
	u8 rx_trace_insertion_loss;
	u8 tx_trace_loss[WL1271_INI_CHANNEL_COUNT_2];
	u8 rx_rssi_process_compens[WL1271_INI_RSSI_PROCESS_COMPENS_SIZE];
पूर्ण __packed;

#घोषणा WL1271_INI_RATE_GROUP_COUNT 6

काष्ठा wl1271_ini_fem_params_2 अणु
	__le16 tx_bip_ref_pd_voltage;
	u8 tx_bip_ref_घातer;
	u8 tx_bip_ref_offset;
	u8 tx_per_rate_pwr_limits_normal[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_degraded[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_extreme[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_per_chan_pwr_limits_11b[WL1271_INI_CHANNEL_COUNT_2];
	u8 tx_per_chan_pwr_limits_ofdm[WL1271_INI_CHANNEL_COUNT_2];
	u8 tx_pd_vs_rate_offsets[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_ibias[WL1271_INI_RATE_GROUP_COUNT];
	u8 rx_fem_insertion_loss;
	u8 degraded_low_to_normal_thr;
	u8 normal_to_degraded_high_thr;
पूर्ण __packed;

#घोषणा WL128X_INI_RATE_GROUP_COUNT 7
/* low and high temperatures */
#घोषणा WL128X_INI_PD_VS_TEMPERATURE_RANGES 2

काष्ठा wl128x_ini_fem_params_2 अणु
	__le16 tx_bip_ref_pd_voltage;
	u8 tx_bip_ref_घातer;
	u8 tx_bip_ref_offset;
	u8 tx_per_rate_pwr_limits_normal[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_degraded[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_extreme[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_per_chan_pwr_limits_11b[WL1271_INI_CHANNEL_COUNT_2];
	u8 tx_per_chan_pwr_limits_ofdm[WL1271_INI_CHANNEL_COUNT_2];
	u8 tx_pd_vs_rate_offsets[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_ibias[WL128X_INI_RATE_GROUP_COUNT + 1];
	u8 tx_pd_vs_chan_offsets[WL1271_INI_CHANNEL_COUNT_2];
	u8 tx_pd_vs_temperature[WL128X_INI_PD_VS_TEMPERATURE_RANGES];
	u8 rx_fem_insertion_loss;
	u8 degraded_low_to_normal_thr;
	u8 normal_to_degraded_high_thr;
पूर्ण __packed;

#घोषणा WL1271_INI_CHANNEL_COUNT_5 35
#घोषणा WL1271_INI_SUB_BAND_COUNT_5 7

काष्ठा wl1271_ini_band_params_5 अणु
	u8 rx_trace_insertion_loss[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_trace_loss[WL1271_INI_SUB_BAND_COUNT_5];
	u8 rx_rssi_process_compens[WL1271_INI_RSSI_PROCESS_COMPENS_SIZE];
पूर्ण __packed;

काष्ठा wl128x_ini_band_params_5 अणु
	u8 rx_trace_insertion_loss[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_trace_loss[WL1271_INI_CHANNEL_COUNT_5];
	u8 rx_rssi_process_compens[WL1271_INI_RSSI_PROCESS_COMPENS_SIZE];
पूर्ण __packed;

काष्ठा wl1271_ini_fem_params_5 अणु
	__le16 tx_bip_ref_pd_voltage[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_bip_ref_घातer[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_bip_ref_offset[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_per_rate_pwr_limits_normal[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_degraded[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_extreme[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_per_chan_pwr_limits_ofdm[WL1271_INI_CHANNEL_COUNT_5];
	u8 tx_pd_vs_rate_offsets[WL1271_INI_RATE_GROUP_COUNT];
	u8 tx_ibias[WL1271_INI_RATE_GROUP_COUNT];
	u8 rx_fem_insertion_loss[WL1271_INI_SUB_BAND_COUNT_5];
	u8 degraded_low_to_normal_thr;
	u8 normal_to_degraded_high_thr;
पूर्ण __packed;

काष्ठा wl128x_ini_fem_params_5 अणु
	__le16 tx_bip_ref_pd_voltage[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_bip_ref_घातer[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_bip_ref_offset[WL1271_INI_SUB_BAND_COUNT_5];
	u8 tx_per_rate_pwr_limits_normal[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_degraded[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_per_rate_pwr_limits_extreme[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_per_chan_pwr_limits_ofdm[WL1271_INI_CHANNEL_COUNT_5];
	u8 tx_pd_vs_rate_offsets[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_ibias[WL128X_INI_RATE_GROUP_COUNT];
	u8 tx_pd_vs_chan_offsets[WL1271_INI_CHANNEL_COUNT_5];
	u8 tx_pd_vs_temperature[WL1271_INI_SUB_BAND_COUNT_5 *
		WL128X_INI_PD_VS_TEMPERATURE_RANGES];
	u8 rx_fem_insertion_loss[WL1271_INI_SUB_BAND_COUNT_5];
	u8 degraded_low_to_normal_thr;
	u8 normal_to_degraded_high_thr;
पूर्ण __packed;

/* NVS data काष्ठाure */
#घोषणा WL1271_INI_NVS_SECTION_SIZE		     468

/* We have four FEM module types: 0-RFMD, 1-TQS, 2-SKW, 3-TQS_HP */
#घोषणा WL1271_INI_FEM_MODULE_COUNT                  4

/*
 * In NVS we only store two FEM module entries -
 *	  FEM modules 0,2,3 are stored in entry 0
 *	  FEM module 1 is stored in entry 1
 */
#घोषणा WL12XX_NVS_FEM_MODULE_COUNT                  2

#घोषणा WL12XX_FEM_TO_NVS_ENTRY(ini_fem_module)      \
	((ini_fem_module) == 1 ? 1 : 0)

#घोषणा WL1271_INI_LEGACY_NVS_खाता_SIZE              800

काष्ठा wl1271_nvs_file अणु
	/* NVS section - must be first! */
	u8 nvs[WL1271_INI_NVS_SECTION_SIZE];

	/* INI section */
	काष्ठा wl1271_ini_general_params general_params;
	u8 padding1;
	काष्ठा wl1271_ini_band_params_2 stat_radio_params_2;
	u8 padding2;
	काष्ठा अणु
		काष्ठा wl1271_ini_fem_params_2 params;
		u8 padding;
	पूर्ण dyn_radio_params_2[WL12XX_NVS_FEM_MODULE_COUNT];
	काष्ठा wl1271_ini_band_params_5 stat_radio_params_5;
	u8 padding3;
	काष्ठा अणु
		काष्ठा wl1271_ini_fem_params_5 params;
		u8 padding;
	पूर्ण dyn_radio_params_5[WL12XX_NVS_FEM_MODULE_COUNT];
पूर्ण __packed;

काष्ठा wl128x_nvs_file अणु
	/* NVS section - must be first! */
	u8 nvs[WL1271_INI_NVS_SECTION_SIZE];

	/* INI section */
	काष्ठा wl128x_ini_general_params general_params;
	u8 fem_venकरोr_and_options;
	काष्ठा wl128x_ini_band_params_2 stat_radio_params_2;
	u8 padding2;
	काष्ठा अणु
		काष्ठा wl128x_ini_fem_params_2 params;
		u8 padding;
	पूर्ण dyn_radio_params_2[WL12XX_NVS_FEM_MODULE_COUNT];
	काष्ठा wl128x_ini_band_params_5 stat_radio_params_5;
	u8 padding3;
	काष्ठा अणु
		काष्ठा wl128x_ini_fem_params_5 params;
		u8 padding;
	पूर्ण dyn_radio_params_5[WL12XX_NVS_FEM_MODULE_COUNT];
पूर्ण __packed;
#पूर्ण_अगर
