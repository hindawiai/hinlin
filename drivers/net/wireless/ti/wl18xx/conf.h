<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments Inc.
 */

#अगर_अघोषित __WL18XX_CONF_H__
#घोषणा __WL18XX_CONF_H__

#घोषणा WL18XX_CONF_MAGIC	0x10e100ca
#घोषणा WL18XX_CONF_VERSION	(WLCORE_CONF_VERSION | 0x0007)
#घोषणा WL18XX_CONF_MASK	0x0000ffff
#घोषणा WL18XX_CONF_SIZE	(WLCORE_CONF_SIZE + \
				 माप(काष्ठा wl18xx_priv_conf))

#घोषणा NUM_OF_CHANNELS_11_ABG 150
#घोषणा NUM_OF_CHANNELS_11_P 7
#घोषणा SRF_TABLE_LEN 16
#घोषणा PIN_MUXING_SIZE 2
#घोषणा WL18XX_TRACE_LOSS_GAPS_TX 10
#घोषणा WL18XX_TRACE_LOSS_GAPS_RX 18

काष्ठा wl18xx_mac_and_phy_params अणु
	u8 phy_standalone;
	u8 spare0;
	u8 enable_clpc;
	u8 enable_tx_low_pwr_on_siso_rdl;
	u8 स्वतः_detect;
	u8 dedicated_fem;

	u8 low_band_component;

	/* Bit 0: One Hot, Bit 1: Control Enable, Bit 2: 1.8V, Bit 3: 3V */
	u8 low_band_component_type;

	u8 high_band_component;

	/* Bit 0: One Hot, Bit 1: Control Enable, Bit 2: 1.8V, Bit 3: 3V */
	u8 high_band_component_type;
	u8 number_of_assembled_ant2_4;
	u8 number_of_assembled_ant5;
	u8 pin_muxing_platक्रमm_options[PIN_MUXING_SIZE];
	u8 बाह्यal_pa_dc2dc;
	u8 tcxo_lकरो_voltage;
	u8 xtal_itrim_val;
	u8 srf_state;
	u8 srf1[SRF_TABLE_LEN];
	u8 srf2[SRF_TABLE_LEN];
	u8 srf3[SRF_TABLE_LEN];
	u8 io_configuration;
	u8 sdio_configuration;
	u8 settings;
	u8 rx_profile;
	u8 per_chan_pwr_limit_arr_11abg[NUM_OF_CHANNELS_11_ABG];
	u8 pwr_limit_reference_11_abg;
	u8 per_chan_pwr_limit_arr_11p[NUM_OF_CHANNELS_11_P];
	u8 pwr_limit_reference_11p;
	u8 spare1;
	u8 per_chan_bo_mode_11_abg[13];
	u8 per_chan_bo_mode_11_p[4];
	u8 primary_घड़ी_setting_समय;
	u8 घड़ी_valid_on_wake_up;
	u8 secondary_घड़ी_setting_समय;
	u8 board_type;
	/* enable poपूर्णांक saturation */
	u8 psat;
	/* low/medium/high Tx घातer in dBm क्रम STA-HP BG */
	s8 low_घातer_val;
	s8 med_घातer_val;
	s8 high_घातer_val;
	s8 per_sub_band_tx_trace_loss[WL18XX_TRACE_LOSS_GAPS_TX];
	s8 per_sub_band_rx_trace_loss[WL18XX_TRACE_LOSS_GAPS_RX];
	u8 tx_rf_margin;
	/* low/medium/high Tx घातer in dBm क्रम other role */
	s8 low_घातer_val_2nd;
	s8 med_घातer_val_2nd;
	s8 high_घातer_val_2nd;

	u8 padding[1];
पूर्ण __packed;

क्रमागत wl18xx_ht_mode अणु
	/* Default - use MIMO, fallback to SISO20 */
	HT_MODE_DEFAULT = 0,

	/* Wide - use SISO40 */
	HT_MODE_WIDE = 1,

	/* Use SISO20 */
	HT_MODE_SISO20 = 2,
पूर्ण;

काष्ठा wl18xx_ht_settings अणु
	/* DEFAULT / WIDE / SISO20 */
	u8 mode;
पूर्ण __packed;

काष्ठा conf_ap_sleep_settings अणु
	/* Duty Cycle (20-80% of staying Awake) क्रम IDLE AP
	 * (0: disable)
	 */
	u8 idle_duty_cycle;
	/* Duty Cycle (20-80% of staying Awake) क्रम Connected AP
	 * (0: disable)
	 */
	u8 connected_duty_cycle;
	/* Maximum stations that are allowed to be connected to AP
	 *  (255: no limit)
	 */
	u8 max_stations_thresh;
	/* Timeout till enabling the Sleep Mechanism after data stops
	 * [unit: 100 msec]
	 */
	u8 idle_conn_thresh;
पूर्ण __packed;

काष्ठा wl18xx_priv_conf अणु
	/* Module params काष्ठाures */
	काष्ठा wl18xx_ht_settings ht;

	/* this काष्ठाure is copied wholesale to FW */
	काष्ठा wl18xx_mac_and_phy_params phy;

	काष्ठा conf_ap_sleep_settings ap_sleep;
पूर्ण __packed;

क्रमागत wl18xx_sg_params अणु
	WL18XX_CONF_SG_PARAM_0 = 0,

	/* Configuration Parameters */
	WL18XX_CONF_SG_ANTENNA_CONFIGURATION,
	WL18XX_CONF_SG_ZIGBEE_COEX,
	WL18XX_CONF_SG_TIME_SYNC,

	WL18XX_CONF_SG_PARAM_4,
	WL18XX_CONF_SG_PARAM_5,
	WL18XX_CONF_SG_PARAM_6,
	WL18XX_CONF_SG_PARAM_7,
	WL18XX_CONF_SG_PARAM_8,
	WL18XX_CONF_SG_PARAM_9,
	WL18XX_CONF_SG_PARAM_10,
	WL18XX_CONF_SG_PARAM_11,
	WL18XX_CONF_SG_PARAM_12,
	WL18XX_CONF_SG_PARAM_13,
	WL18XX_CONF_SG_PARAM_14,
	WL18XX_CONF_SG_PARAM_15,
	WL18XX_CONF_SG_PARAM_16,
	WL18XX_CONF_SG_PARAM_17,
	WL18XX_CONF_SG_PARAM_18,
	WL18XX_CONF_SG_PARAM_19,
	WL18XX_CONF_SG_PARAM_20,
	WL18XX_CONF_SG_PARAM_21,
	WL18XX_CONF_SG_PARAM_22,
	WL18XX_CONF_SG_PARAM_23,
	WL18XX_CONF_SG_PARAM_24,
	WL18XX_CONF_SG_PARAM_25,

	/* Active Scan Parameters */
	WL18XX_CONF_SG_AUTO_SCAN_PROBE_REQ,
	WL18XX_CONF_SG_ACTIVE_SCAN_DURATION_FACTOR_HV3,

	WL18XX_CONF_SG_PARAM_28,

	/* Passive Scan Parameters */
	WL18XX_CONF_SG_PARAM_29,
	WL18XX_CONF_SG_PARAM_30,
	WL18XX_CONF_SG_PASSIVE_SCAN_DURATION_FACTOR_HV3,

	/* Passive Scan in Dual Antenna Parameters */
	WL18XX_CONF_SG_CONSECUTIVE_HV3_IN_PASSIVE_SCAN,
	WL18XX_CONF_SG_BEACON_HV3_COLL_TH_IN_PASSIVE_SCAN,
	WL18XX_CONF_SG_TX_RX_PROTECT_BW_IN_PASSIVE_SCAN,

	/* General Parameters */
	WL18XX_CONF_SG_STA_FORCE_PS_IN_BT_SCO,
	WL18XX_CONF_SG_PARAM_36,
	WL18XX_CONF_SG_BEACON_MISS_PERCENT,
	WL18XX_CONF_SG_PARAM_38,
	WL18XX_CONF_SG_RXT,
	WL18XX_CONF_SG_UNUSED,
	WL18XX_CONF_SG_ADAPTIVE_RXT_TXT,
	WL18XX_CONF_SG_GENERAL_USAGE_BIT_MAP,
	WL18XX_CONF_SG_HV3_MAX_SERVED,
	WL18XX_CONF_SG_PARAM_44,
	WL18XX_CONF_SG_PARAM_45,
	WL18XX_CONF_SG_CONSECUTIVE_CTS_THRESHOLD,
	WL18XX_CONF_SG_GEMINI_PARAM_47,
	WL18XX_CONF_SG_STA_CONNECTION_PROTECTION_TIME,

	/* AP Parameters */
	WL18XX_CONF_SG_AP_BEACON_MISS_TX,
	WL18XX_CONF_SG_PARAM_50,
	WL18XX_CONF_SG_AP_BEACON_WINDOW_INTERVAL,
	WL18XX_CONF_SG_AP_CONNECTION_PROTECTION_TIME,
	WL18XX_CONF_SG_PARAM_53,
	WL18XX_CONF_SG_PARAM_54,

	/* CTS Diluting Parameters */
	WL18XX_CONF_SG_CTS_DILUTED_BAD_RX_PACKETS_TH,
	WL18XX_CONF_SG_CTS_CHOP_IN_DUAL_ANT_SCO_MASTER,

	WL18XX_CONF_SG_TEMP_PARAM_1,
	WL18XX_CONF_SG_TEMP_PARAM_2,
	WL18XX_CONF_SG_TEMP_PARAM_3,
	WL18XX_CONF_SG_TEMP_PARAM_4,
	WL18XX_CONF_SG_TEMP_PARAM_5,
	WL18XX_CONF_SG_TEMP_PARAM_6,
	WL18XX_CONF_SG_TEMP_PARAM_7,
	WL18XX_CONF_SG_TEMP_PARAM_8,
	WL18XX_CONF_SG_TEMP_PARAM_9,
	WL18XX_CONF_SG_TEMP_PARAM_10,

	WL18XX_CONF_SG_PARAMS_MAX,
	WL18XX_CONF_SG_PARAMS_ALL = 0xff
पूर्ण;

#पूर्ण_अगर /* __WL18XX_CONF_H__ */
