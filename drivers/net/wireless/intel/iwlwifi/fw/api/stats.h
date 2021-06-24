<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018, 2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_stats_h__
#घोषणा __iwl_fw_api_stats_h__
#समावेश "mac.h"

काष्ठा mvm_statistics_dbg अणु
	__le32 burst_check;
	__le32 burst_count;
	__le32 रुको_क्रम_silence_समयout_cnt;
	u8 reserved[12];
पूर्ण __packed; /* STATISTICS_DEBUG_API_S_VER_2 */

काष्ठा mvm_statistics_भाग अणु
	__le32 tx_on_a;
	__le32 tx_on_b;
	__le32 exec_समय;
	__le32 probe_समय;
	__le32 rssi_ant;
	__le32 reserved2;
पूर्ण __packed; /* STATISTICS_SLOW_DIV_API_S_VER_2 */

/**
 * काष्ठा mvm_statistics_rx_non_phy
 * @bogus_cts: CTS received when not expecting CTS
 * @bogus_ack: ACK received when not expecting ACK
 * @non_channel_beacons: beacons with our bss id but not on our serving channel
 * @channel_beacons: beacons with our bss id and in our serving channel
 * @num_missed_bcon: number of missed beacons
 * @adc_rx_saturation_समय: count in 0.8us units the समय the ADC was in
 *	saturation
 * @ina_detection_search_समय: total समय (in 0.8us) searched क्रम INA
 * @beacon_silence_rssi_a: RSSI silence after beacon frame
 * @beacon_silence_rssi_b: RSSI silence after beacon frame
 * @beacon_silence_rssi_c: RSSI silence after beacon frame
 * @पूर्णांकerference_data_flag: flag क्रम पूर्णांकerference data availability. 1 when data
 *	is available.
 * @channel_load: counts RX Enable समय in uSec
 * @beacon_rssi_a: beacon RSSI on antenna A
 * @beacon_rssi_b: beacon RSSI on antenna B
 * @beacon_rssi_c: beacon RSSI on antenna C
 * @beacon_energy_a: beacon energy on antenna A
 * @beacon_energy_b: beacon energy on antenna B
 * @beacon_energy_c: beacon energy on antenna C
 * @num_bt_समाप्तs: number of BT "kills" (frame TX पातs)
 * @mac_id: mac ID
 */
काष्ठा mvm_statistics_rx_non_phy अणु
	__le32 bogus_cts;
	__le32 bogus_ack;
	__le32 non_channel_beacons;
	__le32 channel_beacons;
	__le32 num_missed_bcon;
	__le32 adc_rx_saturation_समय;
	__le32 ina_detection_search_समय;
	__le32 beacon_silence_rssi_a;
	__le32 beacon_silence_rssi_b;
	__le32 beacon_silence_rssi_c;
	__le32 पूर्णांकerference_data_flag;
	__le32 channel_load;
	__le32 beacon_rssi_a;
	__le32 beacon_rssi_b;
	__le32 beacon_rssi_c;
	__le32 beacon_energy_a;
	__le32 beacon_energy_b;
	__le32 beacon_energy_c;
	__le32 num_bt_समाप्तs;
	__le32 mac_id;
पूर्ण __packed; /* STATISTICS_RX_NON_PHY_API_S_VER_4 */

काष्ठा mvm_statistics_rx_non_phy_v3 अणु
	__le32 bogus_cts;	/* CTS received when not expecting CTS */
	__le32 bogus_ack;	/* ACK received when not expecting ACK */
	__le32 non_bssid_frames;	/* number of frames with BSSID that
					 * करोesn't beदीर्घ to the STA BSSID */
	__le32 filtered_frames;	/* count frames that were dumped in the
				 * filtering process */
	__le32 non_channel_beacons;	/* beacons with our bss id but not on
					 * our serving channel */
	__le32 channel_beacons;	/* beacons with our bss id and in our
				 * serving channel */
	__le32 num_missed_bcon;	/* number of missed beacons */
	__le32 adc_rx_saturation_समय;	/* count in 0.8us units the समय the
					 * ADC was in saturation */
	__le32 ina_detection_search_समय;/* total समय (in 0.8us) searched
					  * क्रम INA */
	__le32 beacon_silence_rssi_a;	/* RSSI silence after beacon frame */
	__le32 beacon_silence_rssi_b;	/* RSSI silence after beacon frame */
	__le32 beacon_silence_rssi_c;	/* RSSI silence after beacon frame */
	__le32 पूर्णांकerference_data_flag;	/* flag क्रम पूर्णांकerference data
					 * availability. 1 when data is
					 * available. */
	__le32 channel_load;		/* counts RX Enable समय in uSec */
	__le32 dsp_false_alarms;	/* DSP false alarm (both OFDM
					 * and CCK) counter */
	__le32 beacon_rssi_a;
	__le32 beacon_rssi_b;
	__le32 beacon_rssi_c;
	__le32 beacon_energy_a;
	__le32 beacon_energy_b;
	__le32 beacon_energy_c;
	__le32 num_bt_समाप्तs;
	__le32 mac_id;
	__le32 directed_data_mpdu;
पूर्ण __packed; /* STATISTICS_RX_NON_PHY_API_S_VER_3 */

काष्ठा mvm_statistics_rx_phy अणु
	__le32 unresponded_rts;
	__le32 rxe_frame_lmt_overrun;
	__le32 sent_ba_rsp_cnt;
	__le32 dsp_self_समाप्त;
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_RX_PHY_API_S_VER_3 */

काष्ठा mvm_statistics_rx_phy_v2 अणु
	__le32 ina_cnt;
	__le32 fina_cnt;
	__le32 plcp_err;
	__le32 crc32_err;
	__le32 overrun_err;
	__le32 early_overrun_err;
	__le32 crc32_good;
	__le32 false_alarm_cnt;
	__le32 fina_sync_err_cnt;
	__le32 sfd_समयout;
	__le32 fina_समयout;
	__le32 unresponded_rts;
	__le32 rxe_frame_lmt_overrun;
	__le32 sent_ack_cnt;
	__le32 sent_cts_cnt;
	__le32 sent_ba_rsp_cnt;
	__le32 dsp_self_समाप्त;
	__le32 mh_क्रमmat_err;
	__le32 re_acq_मुख्य_rssi_sum;
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_RX_PHY_API_S_VER_2 */

काष्ठा mvm_statistics_rx_ht_phy_v1 अणु
	__le32 plcp_err;
	__le32 overrun_err;
	__le32 early_overrun_err;
	__le32 crc32_good;
	__le32 crc32_err;
	__le32 mh_क्रमmat_err;
	__le32 agg_crc32_good;
	__le32 agg_mpdu_cnt;
	__le32 agg_cnt;
	__le32 unsupport_mcs;
पूर्ण __packed;  /* STATISTICS_HT_RX_PHY_API_S_VER_1 */

काष्ठा mvm_statistics_rx_ht_phy अणु
	__le32 mh_क्रमmat_err;
	__le32 agg_mpdu_cnt;
	__le32 agg_cnt;
	__le32 unsupport_mcs;
पूर्ण __packed;  /* STATISTICS_HT_RX_PHY_API_S_VER_2 */

काष्ठा mvm_statistics_tx_non_phy_v3 अणु
	__le32 preamble_cnt;
	__le32 rx_detected_cnt;
	__le32 bt_prio_defer_cnt;
	__le32 bt_prio_समाप्त_cnt;
	__le32 few_bytes_cnt;
	__le32 cts_समयout;
	__le32 ack_समयout;
	__le32 expected_ack_cnt;
	__le32 actual_ack_cnt;
	__le32 dump_msdu_cnt;
	__le32 burst_पात_next_frame_mismatch_cnt;
	__le32 burst_पात_missing_next_frame_cnt;
	__le32 cts_समयout_collision;
	__le32 ack_or_ba_समयout_collision;
पूर्ण __packed; /* STATISTICS_TX_NON_PHY_API_S_VER_3 */

काष्ठा mvm_statistics_tx_non_phy अणु
	__le32 bt_prio_defer_cnt;
	__le32 bt_prio_समाप्त_cnt;
	__le32 few_bytes_cnt;
	__le32 cts_समयout;
	__le32 ack_समयout;
	__le32 dump_msdu_cnt;
	__le32 burst_पात_next_frame_mismatch_cnt;
	__le32 burst_पात_missing_next_frame_cnt;
	__le32 cts_समयout_collision;
	__le32 ack_or_ba_समयout_collision;
पूर्ण __packed; /* STATISTICS_TX_NON_PHY_API_S_VER_4 */

#घोषणा MAX_CHAINS 3

काष्ठा mvm_statistics_tx_non_phy_agg अणु
	__le32 ba_समयout;
	__le32 ba_reschedule_frames;
	__le32 scd_query_agg_frame_cnt;
	__le32 scd_query_no_agg;
	__le32 scd_query_agg;
	__le32 scd_query_mismatch;
	__le32 frame_not_पढ़ोy;
	__le32 underrun;
	__le32 bt_prio_समाप्त;
	__le32 rx_ba_rsp_cnt;
	__s8 txघातer[MAX_CHAINS];
	__s8 reserved;
	__le32 reserved2;
पूर्ण __packed; /* STATISTICS_TX_NON_PHY_AGG_API_S_VER_1 */

काष्ठा mvm_statistics_tx_channel_width अणु
	__le32 ext_cca_narrow_ch20[1];
	__le32 ext_cca_narrow_ch40[2];
	__le32 ext_cca_narrow_ch80[3];
	__le32 ext_cca_narrow_ch160[4];
	__le32 last_tx_ch_width_indx;
	__le32 rx_detected_per_ch_width[4];
	__le32 success_per_ch_width[4];
	__le32 fail_per_ch_width[4];
पूर्ण; /* STATISTICS_TX_CHANNEL_WIDTH_API_S_VER_1 */

काष्ठा mvm_statistics_tx_v4 अणु
	काष्ठा mvm_statistics_tx_non_phy_v3 general;
	काष्ठा mvm_statistics_tx_non_phy_agg agg;
	काष्ठा mvm_statistics_tx_channel_width channel_width;
पूर्ण __packed; /* STATISTICS_TX_API_S_VER_4 */

काष्ठा mvm_statistics_tx अणु
	काष्ठा mvm_statistics_tx_non_phy general;
	काष्ठा mvm_statistics_tx_non_phy_agg agg;
	काष्ठा mvm_statistics_tx_channel_width channel_width;
पूर्ण __packed; /* STATISTICS_TX_API_S_VER_5 */


काष्ठा mvm_statistics_bt_activity अणु
	__le32 hi_priority_tx_req_cnt;
	__le32 hi_priority_tx_denied_cnt;
	__le32 lo_priority_tx_req_cnt;
	__le32 lo_priority_tx_denied_cnt;
	__le32 hi_priority_rx_req_cnt;
	__le32 hi_priority_rx_denied_cnt;
	__le32 lo_priority_rx_req_cnt;
	__le32 lo_priority_rx_denied_cnt;
पूर्ण __packed;  /* STATISTICS_BT_ACTIVITY_API_S_VER_1 */

काष्ठा mvm_statistics_general_common_v19 अणु
	__le32 radio_temperature;
	__le32 radio_voltage;
	काष्ठा mvm_statistics_dbg dbg;
	__le32 sleep_समय;
	__le32 slots_out;
	__le32 slots_idle;
	__le32 ttl_बारtamp;
	काष्ठा mvm_statistics_भाग slow_भाग;
	__le32 rx_enable_counter;
	/*
	 * num_of_sos_states:
	 *  count the number of बार we have to re-tune
	 *  in order to get out of bad PHY status
	 */
	__le32 num_of_sos_states;
	__le32 beacon_filtered;
	__le32 missed_beacons;
	u8 beacon_filter_average_energy;
	u8 beacon_filter_reason;
	u8 beacon_filter_current_energy;
	u8 beacon_filter_reserved;
	__le32 beacon_filter_delta_समय;
	काष्ठा mvm_statistics_bt_activity bt_activity;
	__le64 rx_समय;
	__le64 on_समय_rf;
	__le64 on_समय_scan;
	__le64 tx_समय;
पूर्ण __packed;

काष्ठा mvm_statistics_general_common अणु
	__le32 radio_temperature;
	काष्ठा mvm_statistics_dbg dbg;
	__le32 sleep_समय;
	__le32 slots_out;
	__le32 slots_idle;
	__le32 ttl_बारtamp;
	काष्ठा mvm_statistics_भाग slow_भाग;
	__le32 rx_enable_counter;
	/*
	 * num_of_sos_states:
	 *  count the number of बार we have to re-tune
	 *  in order to get out of bad PHY status
	 */
	__le32 num_of_sos_states;
	__le32 beacon_filtered;
	__le32 missed_beacons;
	u8 beacon_filter_average_energy;
	u8 beacon_filter_reason;
	u8 beacon_filter_current_energy;
	u8 beacon_filter_reserved;
	__le32 beacon_filter_delta_समय;
	काष्ठा mvm_statistics_bt_activity bt_activity;
	__le64 rx_समय;
	__le64 on_समय_rf;
	__le64 on_समय_scan;
	__le64 tx_समय;
पूर्ण __packed; /* STATISTICS_GENERAL_API_S_VER_10 */

काष्ठा mvm_statistics_general_v8 अणु
	काष्ठा mvm_statistics_general_common_v19 common;
	__le32 beacon_counter[NUM_MAC_INDEX];
	u8 beacon_average_energy[NUM_MAC_INDEX];
	u8 reserved[4 - (NUM_MAC_INDEX % 4)];
पूर्ण __packed; /* STATISTICS_GENERAL_API_S_VER_8 */

काष्ठा mvm_statistics_general अणु
	काष्ठा mvm_statistics_general_common common;
	__le32 beacon_counter[MAC_INDEX_AUX];
	u8 beacon_average_energy[MAC_INDEX_AUX];
	u8 reserved[8 - MAC_INDEX_AUX];
पूर्ण __packed; /* STATISTICS_GENERAL_API_S_VER_10 */

/**
 * काष्ठा mvm_statistics_load - RX statistics क्रम multi-queue devices
 * @air_समय: accumulated air समय, per mac
 * @byte_count: accumulated byte count, per mac
 * @pkt_count: accumulated packet count, per mac
 * @avg_energy: average RSSI, per station
 */
काष्ठा mvm_statistics_load अणु
	__le32 air_समय[MAC_INDEX_AUX];
	__le32 byte_count[MAC_INDEX_AUX];
	__le32 pkt_count[MAC_INDEX_AUX];
	u8 avg_energy[IWL_MVM_STATION_COUNT_MAX];
पूर्ण __packed; /* STATISTICS_RX_MAC_STATION_S_VER_3 */

काष्ठा mvm_statistics_load_v1 अणु
	__le32 air_समय[NUM_MAC_INDEX];
	__le32 byte_count[NUM_MAC_INDEX];
	__le32 pkt_count[NUM_MAC_INDEX];
	u8 avg_energy[IWL_MVM_STATION_COUNT_MAX];
पूर्ण __packed; /* STATISTICS_RX_MAC_STATION_S_VER_1 */

काष्ठा mvm_statistics_rx अणु
	काष्ठा mvm_statistics_rx_phy ofdm;
	काष्ठा mvm_statistics_rx_phy cck;
	काष्ठा mvm_statistics_rx_non_phy general;
	काष्ठा mvm_statistics_rx_ht_phy ofdm_ht;
पूर्ण __packed; /* STATISTICS_RX_API_S_VER_4 */

काष्ठा mvm_statistics_rx_v3 अणु
	काष्ठा mvm_statistics_rx_phy_v2 ofdm;
	काष्ठा mvm_statistics_rx_phy_v2 cck;
	काष्ठा mvm_statistics_rx_non_phy_v3 general;
	काष्ठा mvm_statistics_rx_ht_phy_v1 ofdm_ht;
पूर्ण __packed; /* STATISTICS_RX_API_S_VER_3 */

/*
 * STATISTICS_NOTIFICATION = 0x9d (notअगरication only, not a command)
 *
 * By शेष, uCode issues this notअगरication after receiving a beacon
 * जबतक associated.  To disable this behavior, set DISABLE_NOTIF flag in the
 * STATISTICS_CMD (0x9c), below.
 */

काष्ठा iwl_notअगर_statistics_v10 अणु
	__le32 flag;
	काष्ठा mvm_statistics_rx_v3 rx;
	काष्ठा mvm_statistics_tx_v4 tx;
	काष्ठा mvm_statistics_general_v8 general;
पूर्ण __packed; /* STATISTICS_NTFY_API_S_VER_10 */

काष्ठा iwl_notअगर_statistics_v11 अणु
	__le32 flag;
	काष्ठा mvm_statistics_rx_v3 rx;
	काष्ठा mvm_statistics_tx_v4 tx;
	काष्ठा mvm_statistics_general_v8 general;
	काष्ठा mvm_statistics_load_v1 load_stats;
पूर्ण __packed; /* STATISTICS_NTFY_API_S_VER_11 */

काष्ठा iwl_notअगर_statistics अणु
	__le32 flag;
	काष्ठा mvm_statistics_rx rx;
	काष्ठा mvm_statistics_tx tx;
	काष्ठा mvm_statistics_general general;
	काष्ठा mvm_statistics_load load_stats;
पूर्ण __packed; /* STATISTICS_NTFY_API_S_VER_13 */

/**
 * क्रमागत iwl_statistics_notअगर_flags - flags used in statistics notअगरication
 * @IWL_STATISTICS_REPLY_FLG_CLEAR: statistics were cleared after this report
 */
क्रमागत iwl_statistics_notअगर_flags अणु
	IWL_STATISTICS_REPLY_FLG_CLEAR		= 0x1,
पूर्ण;

/**
 * क्रमागत iwl_statistics_cmd_flags - flags used in statistics command
 * @IWL_STATISTICS_FLG_CLEAR: request to clear statistics after the report
 *	that's sent after this command
 * @IWL_STATISTICS_FLG_DISABLE_NOTIF: disable unilateral statistics
 *	notअगरications
 */
क्रमागत iwl_statistics_cmd_flags अणु
	IWL_STATISTICS_FLG_CLEAR		= 0x1,
	IWL_STATISTICS_FLG_DISABLE_NOTIF	= 0x2,
पूर्ण;

/**
 * काष्ठा iwl_statistics_cmd - statistics config command
 * @flags: flags from &क्रमागत iwl_statistics_cmd_flags
 */
काष्ठा iwl_statistics_cmd अणु
	__le32 flags;
पूर्ण __packed; /* STATISTICS_CMD_API_S_VER_1 */

#घोषणा MAX_BCAST_FILTER_NUM		8

/**
 * क्रमागत iwl_fw_statistics_type
 *
 * @FW_STATISTICS_OPERATIONAL: operational statistics
 * @FW_STATISTICS_PHY: phy statistics
 * @FW_STATISTICS_MAC: mac statistics
 * @FW_STATISTICS_RX: rx statistics
 * @FW_STATISTICS_TX: tx statistics
 * @FW_STATISTICS_DURATION: duration statistics
 * @FW_STATISTICS_HE: he statistics
 */
क्रमागत iwl_fw_statistics_type अणु
	FW_STATISTICS_OPERATIONAL,
	FW_STATISTICS_PHY,
	FW_STATISTICS_MAC,
	FW_STATISTICS_RX,
	FW_STATISTICS_TX,
	FW_STATISTICS_DURATION,
	FW_STATISTICS_HE,
पूर्ण; /* FW_STATISTICS_TYPE_API_E_VER_1 */

/**
 * काष्ठा iwl_statistics_ntfy_hdr
 *
 * @type: काष्ठा type
 * @version: version of the काष्ठा
 * @size: size in bytes
 */
काष्ठा iwl_statistics_ntfy_hdr अणु
	u8 type;
	u8 version;
	__le16 size;
पूर्ण; /* STATISTICS_NTFY_HDR_API_S_VER_1 */

/**
 * काष्ठा iwl_statistics_operational_ntfy
 *
 * @hdr: general statistics header
 * @flags: biपंचांगap of possible notअगरication काष्ठाures
 * @mac_id: mac on which the beacon was received
 * @beacon_filter_average_energy: Average energy [-dBm] of the 2
 *	 antennas.
 * @beacon_filter_reason: beacon filter reason
 * @radio_temperature: radio temperature
 * @air_समय: air समय
 * @beacon_counter: all beacons (both filtered and not filtered)
 * @beacon_average_energy: all beacons (both filtered and not
 *	 filtered)
 * @beacon_rssi_a: beacon RSSI on antenna A
 * @beacon_rssi_b: beacon RSSI on antenna B
 * @rx_bytes: per MAC RX byte count
 * @rx_समय: rx समय
 * @tx_समय: usec the radio is transmitting.
 * @on_समय_rf: The total समय in usec the RF is awake.
 * @on_समय_scan: usec the radio is awake due to scan.
 * @average_energy: in fact it is minus the energy..
 * @reserved: reserved
 */
काष्ठा iwl_statistics_operational_ntfy अणु
	काष्ठा iwl_statistics_ntfy_hdr hdr;
	__le32 flags;
	__le32 mac_id;
	__le32 beacon_filter_average_energy;
	__le32 beacon_filter_reason;
	__le32 radio_temperature;
	__le32 air_समय[MAC_INDEX_AUX];
	__le32 beacon_counter[MAC_INDEX_AUX];
	__le32 beacon_average_energy[MAC_INDEX_AUX];
	__le32 beacon_rssi_a;
	__le32 beacon_rssi_b;
	__le32 rx_bytes[MAC_INDEX_AUX];
	__le64 rx_समय;
	__le64 tx_समय;
	__le64 on_समय_rf;
	__le64 on_समय_scan;
	__le32 average_energy[IWL_MVM_STATION_COUNT_MAX];
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_OPERATIONAL_NTFY_API_S_VER_14 */

/**
 * काष्ठा iwl_statistics_phy_ntfy
 *
 * @hdr: general statistics header
 * RX PHY related statistics
 * @energy_and_config: ???
 * @rssi_band: @31:24 rssiAllBand_B, 23:16 rssiInBand_B, 15:8
 *	 rssiAllBand_A, 7:0 rssiInBand_A
 * @agc_word: @31:16 agcWord_B, 15:0 agcWord_A
 * @agc_gain: @19:10 agcGain_B, 9:0 agcGain_A
 * @dfe_gain: @19:10 dfeGain_B, 9:0 dfeGain_A
 * @snr_calc_मुख्य: @18:0 snrCalcMain
 * @energy_calc_मुख्य: @18:0 energyCalcMain
 * @snr_calc_aux: @18:0 snrCalcAux
 * @dsp_dc_estim_a: @27:14 dspDcEstimQA, 13:0 dspDcEstimIA
 * @dsp_dc_estim_b: @27:14 dspDcEstimQB, 13:0 dspDcEstimIB
 * @ina_detec_type_and_ofdm_corr_comb: @31:31 inaDetectCckMrc,
 *	 30:27 inaDetectType, 26:0 ofdmCorrComb
 * @cw_corr_comb: @26:0 cwCorrComb
 * @rssi_comb: @25:0 rssiComb
 * @स्वतः_corr_cck: @23:12 स्वतःCck, 11:00 crossCck
 * @ofdm_fine_freq_and_pina_freq_err: @18:7 ofdmFineFreq, 6:0
 *	 ofdmPinaFreqErr
 * @snrm_evm_मुख्य: @31:0 snrmEvmMain
 * @snrm_evm_aux: @31:0 snrmEvmAux
 * @rx_rate: @31:0 rate
 * TX PHY related statistics
 * @per_chain_क्रमागतs_and_dsp_atten_a: @perChainEnumsAndDspAtten
 *	 (per version)
 * @target_घातer_and_घातer_meas_a: @31:16 targetPower_A, 15:0
 *	 घातerMeasuredCalc_A
 * @tx_config_as_i_and_ac_a: @31:16 txConfigAsI_A, 15:0
 *	 txConfigAc_A
 * @predist_dcq_and_dci_a: @31:16 predist_dci_A, 15:0
 *	 predist_dcq_A
 * @per_chain_क्रमागतs_and_dsp_atten_b: @perChainEnumsAndDspAtten
 *	 (per version)
 * @target_घातer_and_घातer_meas_b: @31:16 targetPower_B, 15:0
 *	 घातerMeasuredCalc_B
 * @tx_config_as_i_and_ac_b: @31:16 txConfigAsI_B, 15:0
 *	 txConfigAc_B
 * @predist_dcq_and_dci_b: @31:16 predist_dci_B, 15:0
 *	 predist_dcq_B
 * @tx_rate: @31:0 rate
 * @tlc_backoff: @31:0 tlcBackoff
 * @mpapd_calib_mode_mpapd_calib_type_a: @31:16
 *	 mpapdCalibMode_A, 15:0 mpapdCalibType_A
 * @psat_and_phy_घातer_limit_a: @31:16 psat_A, 15:0
 *	 phyPowerLimit_A
 * @sar_and_regulatory_घातer_limit_a: @31:16 sarPowerLimit_A,
 *	 15:0 regulatoryPowerLimit_A
 * @mpapd_calib_mode_mpapd_calib_type_b: @31:16
 *	 mpapdCalibMode_B, 15:0 mpapdCalibType_B
 * @psat_and_phy_घातer_limit_b: @31:16 psat_B, 15:0
 *	 phyPowerLimit_B
 * @sar_and_regulatory_घातer_limit_b: @31:16 sarPowerLimit_B,
 *	 15:0 regulatoryPowerLimit_B
 * @srd_and_driver_घातer_limits: @31:16 srdPowerLimit, 15:0
 *	 driverPowerLimit
 * @reserved: reserved
 */
काष्ठा iwl_statistics_phy_ntfy अणु
	काष्ठा iwl_statistics_ntfy_hdr hdr;
	__le32 energy_and_config;
	__le32 rssi_band;
	__le32 agc_word;
	__le32 agc_gain;
	__le32 dfe_gain;
	__le32 snr_calc_मुख्य;
	__le32 energy_calc_मुख्य;
	__le32 snr_calc_aux;
	__le32 dsp_dc_estim_a;
	__le32 dsp_dc_estim_b;
	__le32 ina_detec_type_and_ofdm_corr_comb;
	__le32 cw_corr_comb;
	__le32 rssi_comb;
	__le32 स्वतः_corr_cck;
	__le32 ofdm_fine_freq_and_pina_freq_err;
	__le32 snrm_evm_मुख्य;
	__le32 snrm_evm_aux;
	__le32 rx_rate;
	__le32 per_chain_क्रमागतs_and_dsp_atten_a;
	__le32 target_घातer_and_घातer_meas_a;
	__le32 tx_config_as_i_and_ac_a;
	__le32 predist_dcq_and_dci_a;
	__le32 per_chain_क्रमागतs_and_dsp_atten_b;
	__le32 target_घातer_and_घातer_meas_b;
	__le32 tx_config_as_i_and_ac_b;
	__le32 predist_dcq_and_dci_b;
	__le32 tx_rate;
	__le32 tlc_backoff;
	__le32 mpapd_calib_mode_mpapd_calib_type_a;
	__le32 psat_and_phy_घातer_limit_a;
	__le32 sar_and_regulatory_घातer_limit_a;
	__le32 mpapd_calib_mode_mpapd_calib_type_b;
	__le32 psat_and_phy_घातer_limit_b;
	__le32 sar_and_regulatory_घातer_limit_b;
	__le32 srd_and_driver_घातer_limits;
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_PHY_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_statistics_mac_ntfy
 *
 * @hdr: general statistics header
 * @bcast_filter_passed_per_mac: bcast filter passed per mac
 * @bcast_filter_dropped_per_mac: bcast filter dropped per mac
 * @bcast_filter_passed_per_filter: bcast filter passed per filter
 * @bcast_filter_dropped_per_filter: bcast filter dropped per filter
 * @reserved: reserved
 */
काष्ठा iwl_statistics_mac_ntfy अणु
	काष्ठा iwl_statistics_ntfy_hdr hdr;
	__le32 bcast_filter_passed_per_mac[NUM_MAC_INDEX_CDB];
	__le32 bcast_filter_dropped_per_mac[NUM_MAC_INDEX_CDB];
	__le32 bcast_filter_passed_per_filter[MAX_BCAST_FILTER_NUM];
	__le32 bcast_filter_dropped_per_filter[MAX_BCAST_FILTER_NUM];
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_MAC_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_statistics_rx_ntfy
 *
 * @hdr: general statistics header
 * @rx_agg_mpdu_cnt: aggregation frame count (number of
 *	 delimiters)
 * @rx_agg_cnt: number of RX Aggregations
 * @unsupported_mcs: number of PLCP headers that have rate which
 *	 is unsupported by DSP
 * @bogus_cts: CTS received when not expecting CTS
 * @bogus_ack: ACK received when not expecting ACK
 * @rx_byte_count: ???
 * @rx_packet_count: ???
 * @missed_beacons: ???
 * @unresponded_rts: un-responded RTS, due to NAV not zero
 * @rxe_frame_limit_overrun: RXE got frame limit overrun
 * @sent_ba_rsp_cnt: BA response TX count
 * @late_rx_handle: count the number of बार the RX path was
 *	 पातed due to late entry
 * @num_bt_समाप्तs: ???
 * @reserved: reserved
 */
काष्ठा iwl_statistics_rx_ntfy अणु
	काष्ठा iwl_statistics_ntfy_hdr hdr;
	__le32 rx_agg_mpdu_cnt;
	__le32 rx_agg_cnt;
	__le32 unsupported_mcs;
	__le32 bogus_cts;
	__le32 bogus_ack;
	__le32 rx_byte_count[MAC_INDEX_AUX];
	__le32 rx_packet_count[MAC_INDEX_AUX];
	__le32 missed_beacons;
	__le32 unresponded_rts;
	__le32 rxe_frame_limit_overrun;
	__le32 sent_ba_rsp_cnt;
	__le32 late_rx_handle;
	__le32 num_bt_समाप्तs;
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_RX_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_statistics_tx_ntfy
 *
 * @hdr: general statistics header
 * @cts_समयout: समयout when रुकोing क्रम CTS
 * @ack_समयout: समयout when रुकोing क्रम ACK
 * @dump_msdu_cnt: number of MSDUs that were dumped due to any
 *	 reason
 * @burst_पात_missing_next_frame_cnt: number of बार a burst
 *	 was पातed due to missing next frame bytes in txfअगरo
 * number of बार got समयout when रुकोing क्रम CTS/ACK/BA and energy was
 * detected just after sending the RTS/DATA. this statistics may help getting
 * पूर्णांकeresting indicators, like the likelihood of collision (so the benefit of
 * protection may be estimated Vs. its cost). Or how many of the failures are
 * due to collision and how many due to SNR.
 * For Link-quality the CTS collision indication is more reliable then the ACK
 * collision indication as the RTS frame is लघु and has more chance that the
 * frame/s which caused the collision जारी after the RTS was sent.
 * @cts_समयout_collision: ???
 * ACK/BA failed and energy as detected after DATA
 * Note: to get the collision ratio need to:
 * ackOrBaTimeoutCollision / (ack_समयout + ba_समयout)
 * @ack_or_ba_समयout_collision: ???
 * @ba_समयout: समयout when रुकोing क्रम immediate BA response
 * @ba_reschedule_frames: failed to get BA response and
 *	 rescheduled all the non-ACKed frames
 * gives the avarage number of frames inside aggregation
 * @scd_query_agg_frame_cnt: ???
 * @scd_query_no_agg: scheduler query prevented aggregation
 * @scd_query_agg: scheduler query allowed aggregation
 * @scd_query_mismatch: scheduler query inaccurate, either too
 *	 लघु or too दीर्घ
 * @agg_terminated_underrun: aggregation was terminated due to
 *	 underrun
 * @agg_terminated_bt_prio_समाप्त: aggregation was terminated due
 *	 to BT
 * @tx_समाप्त_on_दीर्घ_retry: count the tx frames dropped due to
 *	 दीर्घ retry limit (DATA frame failed)
 * @tx_समाप्त_on_लघु_retry: count the tx frames dropped due to
 *	 लघु retry limit (RTS frame failed)
 * TX deffer on energy. This counter is reset on each successful transmit.
 * When समयr exceed TX deffer limit than will be uCode निश्चित.
 * @tx_deffer_counter: ???
 * @tx_deffer_base_समय: Keep the समय of the last successful
 *	 transmit
 * @tx_underrun: TX समाप्तed due to underrun
 * @bt_defer: TX deferred due to BT priority, so probably TX was
 *	 not started.
 * @tx_समाप्त_on_dsp_समयout: TX समाप्तed on DSP problem detected
 * @tx_समाप्त_on_immediate_quiet: TX समाप्तed due to immediate quiet
 * @समाप्त_ba_cnt: number of बार sending BA failed
 * @समाप्त_ack_cnt: number of बार sending ACK failed
 * @समाप्त_cts_cnt: number of बार sending CTS failed
 * @burst_terminated: Count burst or fragmentation termination
 *	 occurrence
 * @late_tx_vec_wr_cnt: ???
 * TX is not sent because ucode failed to notअगरy the TRM in SIFS-delta from
 * ON_AIR deनिश्चितion.
 * @late_rx2_tx_cnt: ???
 * @scd_query_cnt: count the बार SCD query was करोne to check
 *	 क्रम TX AGG
 * @tx_frames_acked_in_agg: count the number of frames
 *	 transmitted inside AGG and were successful
 * @last_tx_ch_width_indx: ???
 * number of deferred TX per channel width, 0 - 20, 1/2/3 - 40/80/160
 * @rx_detected_per_ch_width: ???
 * @success_per_ch_width: ???
 * @fail_per_ch_width: ???
 * @reserved: reserved
 */
काष्ठा iwl_statistics_tx_ntfy अणु
	काष्ठा iwl_statistics_ntfy_hdr hdr;
	__le32 cts_समयout;
	__le32 ack_समयout;
	__le32 dump_msdu_cnt;
	__le32 burst_पात_missing_next_frame_cnt;
	__le32 cts_समयout_collision;
	__le32 ack_or_ba_समयout_collision;
	__le32 ba_समयout;
	__le32 ba_reschedule_frames;
	__le32 scd_query_agg_frame_cnt;
	__le32 scd_query_no_agg;
	__le32 scd_query_agg;
	__le32 scd_query_mismatch;
	__le32 agg_terminated_underrun;
	__le32 agg_terminated_bt_prio_समाप्त;
	__le32 tx_समाप्त_on_दीर्घ_retry;
	__le32 tx_समाप्त_on_लघु_retry;
	__le32 tx_deffer_counter;
	__le32 tx_deffer_base_समय;
	__le32 tx_underrun;
	__le32 bt_defer;
	__le32 tx_समाप्त_on_dsp_समयout;
	__le32 tx_समाप्त_on_immediate_quiet;
	__le32 समाप्त_ba_cnt;
	__le32 समाप्त_ack_cnt;
	__le32 समाप्त_cts_cnt;
	__le32 burst_terminated;
	__le32 late_tx_vec_wr_cnt;
	__le32 late_rx2_tx_cnt;
	__le32 scd_query_cnt;
	__le32 tx_frames_acked_in_agg;
	__le32 last_tx_ch_width_indx;
	__le32 rx_detected_per_ch_width[4];
	__le32 success_per_ch_width[4];
	__le32 fail_per_ch_width[4];
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_TX_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_statistics_duration_ntfy
 *
 * @hdr: general statistics header
 * @cont_burst_chk_cnt: number of बार continuation or
 *	 fragmentation or bursting was checked
 * @cont_burst_cnt: number of बार continuation or fragmentation
 *	 or bursting was successful
 * @रुको_क्रम_silence_समयout_cnt: ???
 * @reserved: reserved
 */
काष्ठा iwl_statistics_duration_ntfy अणु
	काष्ठा iwl_statistics_ntfy_hdr hdr;
	__le32 cont_burst_chk_cnt;
	__le32 cont_burst_cnt;
	__le32 रुको_क्रम_silence_समयout_cnt;
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_DURATION_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_statistics_he_ntfy
 *
 * @hdr: general statistics header
 * received HE frames
 * @rx_siga_valid_cnt: rx HE SIG-A valid
 * @rx_siga_invalid_cnt: rx HE SIG-A invalid
 * received HE frames w/ valid Sig-A
 * @rx_trig_based_frame_cnt: rx HE-TB (trig-based)
 * @rx_su_frame_cnt: rx HE-SU
 * @rx_sigb_invalid_cnt: rx (suspected) HE-MU w/ bad SIG-B
 * @rx_our_bss_color_cnt: rx valid HE SIG-A w/ our BSS color
 * @rx_other_bss_color_cnt: rx valid HE SIG-A w/ other BSS color
 * @rx_zero_bss_color_cnt: ???
 * received HE-MU frames w/ good Sig-B
 * @rx_mu_क्रम_us_cnt: match AID
 * @rx_mu_not_क्रम_us_cnt: no matched AID
 * received HE-MU frames क्रम us (w/ our AID)
 * @rx_mu_nss_ar: 0 - SISO, 1 - MIMO2
 * @rx_mu_mimo_cnt: full BW RU, compressed SIG-B
 * @rx_mu_ru_bw_ar: MU alloc, MHz: 0 - 2, 1 - 5, 2 - 10, 3 - 20,
 *	 4 - 40, 5 - 80, 6 - 160
 * received trigger frames
 * @rx_trig_क्रम_us_cnt: ???
 * @rx_trig_not_क्रम_us_cnt: ???
 * trigger क्रम us
 * @rx_trig_with_cs_req_cnt: ???
 * @rx_trig_type_ar: ???
 * @rx_trig_in_agg_cnt: ???
 * basic trigger क्रम us allocations
 * @rx_basic_trig_alloc_nss_ar: ???
 * @rx_basic_trig_alloc_mu_mimo_cnt: ???
 * @rx_basic_trig_alloc_ru_bw_ar: ???
 * @rx_basic_trig_total_byte_cnt: ???
 * trig-based TX
 * @tx_trig_based_cs_req_fail_cnt: ???
 * @tx_trig_based_sअगरs_ok_cnt: ???
 * @tx_trig_based_sअगरs_fail_cnt: ???
 * @tx_trig_based_byte_cnt: ???
 * @tx_trig_based_pad_byte_cnt: ???
 * @tx_trig_based_frame_cnt: ???
 * @tx_trig_based_acked_frame_cnt: ???
 * @tx_trig_based_ack_समयout_cnt: ???
 * HE-SU TX
 * @tx_su_frame_cnt: ???
 * EDCA <--> MU-EDCA transitions
 * @tx_edca_to_mu_edca_cnt: ???
 * @tx_mu_edca_to_edca_by_समयout_cnt: ???
 * @tx_mu_edca_to_edca_by_ack_fail_cnt: ???
 * @tx_mu_edca_to_edca_by_small_alloc_cnt: ???
 * @reserved: reserved
 */
काष्ठा iwl_statistics_he_ntfy अणु
	काष्ठा iwl_statistics_ntfy_hdr hdr;
	__le32 rx_siga_valid_cnt;
	__le32 rx_siga_invalid_cnt;
	__le32 rx_trig_based_frame_cnt;
	__le32 rx_su_frame_cnt;
	__le32 rx_sigb_invalid_cnt;
	__le32 rx_our_bss_color_cnt;
	__le32 rx_other_bss_color_cnt;
	__le32 rx_zero_bss_color_cnt;
	__le32 rx_mu_क्रम_us_cnt;
	__le32 rx_mu_not_क्रम_us_cnt;
	__le32 rx_mu_nss_ar[2];
	__le32 rx_mu_mimo_cnt;
	__le32 rx_mu_ru_bw_ar[7];
	__le32 rx_trig_क्रम_us_cnt;
	__le32 rx_trig_not_क्रम_us_cnt;
	__le32 rx_trig_with_cs_req_cnt;
	__le32 rx_trig_type_ar[8 + 1];
	__le32 rx_trig_in_agg_cnt;
	__le32 rx_basic_trig_alloc_nss_ar[2];
	__le32 rx_basic_trig_alloc_mu_mimo_cnt;
	__le32 rx_basic_trig_alloc_ru_bw_ar[7];
	__le32 rx_basic_trig_total_byte_cnt;
	__le32 tx_trig_based_cs_req_fail_cnt;
	__le32 tx_trig_based_sअगरs_ok_cnt;
	__le32 tx_trig_based_sअगरs_fail_cnt;
	__le32 tx_trig_based_byte_cnt;
	__le32 tx_trig_based_pad_byte_cnt;
	__le32 tx_trig_based_frame_cnt;
	__le32 tx_trig_based_acked_frame_cnt;
	__le32 tx_trig_based_ack_समयout_cnt;
	__le32 tx_su_frame_cnt;
	__le32 tx_edca_to_mu_edca_cnt;
	__le32 tx_mu_edca_to_edca_by_समयout_cnt;
	__le32 tx_mu_edca_to_edca_by_ack_fail_cnt;
	__le32 tx_mu_edca_to_edca_by_small_alloc_cnt;
	__le32 reserved;
पूर्ण __packed; /* STATISTICS_HE_NTFY_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_stats_h__ */
