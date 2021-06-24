<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2008 - 2011 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <ilw@linux.पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर_अघोषित __il_4965_h__
#घोषणा __il_4965_h__

काष्ठा il_rx_queue;
काष्ठा il_rx_buf;
काष्ठा il_rx_pkt;
काष्ठा il_tx_queue;
काष्ठा il_rxon_context;

/* configuration क्रम the _4965 devices */
बाह्य काष्ठा il_cfg il4965_cfg;
बाह्य स्थिर काष्ठा il_ops il4965_ops;

बाह्य काष्ठा il_mod_params il4965_mod_params;

/* tx queue */
व्योम il4965_मुक्त_tfds_in_queue(काष्ठा il_priv *il, पूर्णांक sta_id, पूर्णांक tid,
			       पूर्णांक मुक्तd);

/* RXON */
व्योम il4965_set_rxon_chain(काष्ठा il_priv *il);

/* uCode */
पूर्णांक il4965_verअगरy_ucode(काष्ठा il_priv *il);

/* lib */
व्योम il4965_check_पात_status(काष्ठा il_priv *il, u8 frame_count, u32 status);

व्योम il4965_rx_queue_reset(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq);
पूर्णांक il4965_rx_init(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq);
पूर्णांक il4965_hw_nic_init(काष्ठा il_priv *il);
पूर्णांक il4965_dump_fh(काष्ठा il_priv *il, अक्षर **buf, bool display);

व्योम il4965_nic_config(काष्ठा il_priv *il);

/* rx */
व्योम il4965_rx_queue_restock(काष्ठा il_priv *il);
व्योम il4965_rx_replenish(काष्ठा il_priv *il);
व्योम il4965_rx_replenish_now(काष्ठा il_priv *il);
व्योम il4965_rx_queue_मुक्त(काष्ठा il_priv *il, काष्ठा il_rx_queue *rxq);
पूर्णांक il4965_rxq_stop(काष्ठा il_priv *il);
पूर्णांक il4965_hwrate_to_mac80211_idx(u32 rate_n_flags, क्रमागत nl80211_band band);
व्योम il4965_rx_handle(काष्ठा il_priv *il);

/* tx */
व्योम il4965_hw_txq_मुक्त_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq);
पूर्णांक il4965_hw_txq_attach_buf_to_tfd(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq,
				    dma_addr_t addr, u16 len, u8 reset, u8 pad);
पूर्णांक il4965_hw_tx_queue_init(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq);
व्योम il4965_hwrate_to_tx_control(काष्ठा il_priv *il, u32 rate_n_flags,
				 काष्ठा ieee80211_tx_info *info);
पूर्णांक il4965_tx_skb(काष्ठा il_priv *il,
		  काष्ठा ieee80211_sta *sta,
		  काष्ठा sk_buff *skb);
पूर्णांक il4965_tx_agg_start(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid, u16 * ssn);
पूर्णांक il4965_tx_agg_stop(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta, u16 tid);
पूर्णांक il4965_txq_check_empty(काष्ठा il_priv *il, पूर्णांक sta_id, u8 tid, पूर्णांक txq_id);
पूर्णांक il4965_tx_queue_reclaim(काष्ठा il_priv *il, पूर्णांक txq_id, पूर्णांक idx);
व्योम il4965_hw_txq_ctx_मुक्त(काष्ठा il_priv *il);
पूर्णांक il4965_txq_ctx_alloc(काष्ठा il_priv *il);
व्योम il4965_txq_ctx_reset(काष्ठा il_priv *il);
व्योम il4965_txq_ctx_stop(काष्ठा il_priv *il);
व्योम il4965_txq_set_sched(काष्ठा il_priv *il, u32 mask);

/*
 * Acquire il->lock beक्रमe calling this function !
 */
व्योम il4965_set_wr_ptrs(काष्ठा il_priv *il, पूर्णांक txq_id, u32 idx);
/**
 * il4965_tx_queue_set_status - (optionally) start Tx/Cmd queue
 * @tx_fअगरo_id: Tx DMA/FIFO channel (range 0-7) that the queue will feed
 * @scd_retry: (1) Indicates queue will be used in aggregation mode
 *
 * NOTE:  Acquire il->lock beक्रमe calling this function !
 */
व्योम il4965_tx_queue_set_status(काष्ठा il_priv *il, काष्ठा il_tx_queue *txq,
				पूर्णांक tx_fअगरo_id, पूर्णांक scd_retry);

/* scan */
पूर्णांक il4965_request_scan(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर);

/* station mgmt */
पूर्णांक il4965_manage_ibss_station(काष्ठा il_priv *il, काष्ठा ieee80211_vअगर *vअगर,
			       bool add);

/* hcmd */
पूर्णांक il4965_send_beacon_cmd(काष्ठा il_priv *il);

#अगर_घोषित CONFIG_IWLEGACY_DEBUG
स्थिर अक्षर *il4965_get_tx_fail_reason(u32 status);
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *
il4965_get_tx_fail_reason(u32 status)
अणु
	वापस "";
पूर्ण
#पूर्ण_अगर

/* station management */
पूर्णांक il4965_alloc_bcast_station(काष्ठा il_priv *il);
पूर्णांक il4965_add_bssid_station(काष्ठा il_priv *il, स्थिर u8 *addr, u8 *sta_id_r);
पूर्णांक il4965_हटाओ_शेष_wep_key(काष्ठा il_priv *il,
				  काष्ठा ieee80211_key_conf *key);
पूर्णांक il4965_set_शेष_wep_key(काष्ठा il_priv *il,
			       काष्ठा ieee80211_key_conf *key);
पूर्णांक il4965_restore_शेष_wep_keys(काष्ठा il_priv *il);
पूर्णांक il4965_set_dynamic_key(काष्ठा il_priv *il,
			   काष्ठा ieee80211_key_conf *key, u8 sta_id);
पूर्णांक il4965_हटाओ_dynamic_key(काष्ठा il_priv *il,
			      काष्ठा ieee80211_key_conf *key, u8 sta_id);
व्योम il4965_update_tkip_key(काष्ठा il_priv *il,
			    काष्ठा ieee80211_key_conf *keyconf,
			    काष्ठा ieee80211_sta *sta, u32 iv32,
			    u16 *phase1key);
पूर्णांक il4965_sta_tx_modअगरy_enable_tid(काष्ठा il_priv *il, पूर्णांक sta_id, पूर्णांक tid);
पूर्णांक il4965_sta_rx_agg_start(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta,
			    पूर्णांक tid, u16 ssn);
पूर्णांक il4965_sta_rx_agg_stop(काष्ठा il_priv *il, काष्ठा ieee80211_sta *sta,
			   पूर्णांक tid);
व्योम il4965_sta_modअगरy_sleep_tx_count(काष्ठा il_priv *il, पूर्णांक sta_id, पूर्णांक cnt);
पूर्णांक il4965_update_bcast_stations(काष्ठा il_priv *il);

/* rate */
अटल अंतरभूत u8
il4965_hw_get_rate(__le32 rate_n_flags)
अणु
	वापस le32_to_cpu(rate_n_flags) & 0xFF;
पूर्ण

/* eeprom */
व्योम il4965_eeprom_get_mac(स्थिर काष्ठा il_priv *il, u8 * mac);
पूर्णांक il4965_eeprom_acquire_semaphore(काष्ठा il_priv *il);
व्योम il4965_eeprom_release_semaphore(काष्ठा il_priv *il);
पूर्णांक il4965_eeprom_check_version(काष्ठा il_priv *il);

/* mac80211 handlers (क्रम 4965) */
व्योम il4965_mac_tx(काष्ठा ieee80211_hw *hw,
		   काष्ठा ieee80211_tx_control *control,
		   काष्ठा sk_buff *skb);
पूर्णांक il4965_mac_start(काष्ठा ieee80211_hw *hw);
व्योम il4965_mac_stop(काष्ठा ieee80211_hw *hw);
व्योम il4965_configure_filter(काष्ठा ieee80211_hw *hw,
			     अचिन्हित पूर्णांक changed_flags,
			     अचिन्हित पूर्णांक *total_flags, u64 multicast);
पूर्णांक il4965_mac_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		       काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key);
व्योम il4965_mac_update_tkip_key(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_key_conf *keyconf,
				काष्ठा ieee80211_sta *sta, u32 iv32,
				u16 *phase1key);
पूर्णांक il4965_mac_ampdu_action(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_ampdu_params *params);
पूर्णांक il4965_mac_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);
व्योम
il4965_mac_channel_चयन(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_channel_चयन *ch_चयन);

व्योम il4965_led_enable(काष्ठा il_priv *il);

/* EEPROM */
#घोषणा IL4965_EEPROM_IMG_SIZE			1024

/*
 * uCode queue management definitions ...
 * The first queue used क्रम block-ack aggregation is #7 (4965 only).
 * All block-ack aggregation queues should map to Tx DMA/FIFO channel 7.
 */
#घोषणा IL49_FIRST_AMPDU_QUEUE	7

/* Sizes and addresses क्रम inकाष्ठाion and data memory (SRAM) in
 * 4965's embedded processor.  Driver access is via HBUS_TARG_MEM_* regs. */
#घोषणा IL49_RTC_INST_LOWER_BOUND		(0x000000)
#घोषणा IL49_RTC_INST_UPPER_BOUND		(0x018000)

#घोषणा IL49_RTC_DATA_LOWER_BOUND		(0x800000)
#घोषणा IL49_RTC_DATA_UPPER_BOUND		(0x80A000)

#घोषणा IL49_RTC_INST_SIZE  (IL49_RTC_INST_UPPER_BOUND - \
				IL49_RTC_INST_LOWER_BOUND)
#घोषणा IL49_RTC_DATA_SIZE  (IL49_RTC_DATA_UPPER_BOUND - \
				IL49_RTC_DATA_LOWER_BOUND)

#घोषणा IL49_MAX_INST_SIZE IL49_RTC_INST_SIZE
#घोषणा IL49_MAX_DATA_SIZE IL49_RTC_DATA_SIZE

/* Size of uCode inकाष्ठाion memory in bootstrap state machine */
#घोषणा IL49_MAX_BSM_SIZE BSM_SRAM_SIZE

अटल अंतरभूत पूर्णांक
il4965_hw_valid_rtc_data_addr(u32 addr)
अणु
	वापस (addr >= IL49_RTC_DATA_LOWER_BOUND &&
		addr < IL49_RTC_DATA_UPPER_BOUND);
पूर्ण

/********************* START TEMPERATURE *************************************/

/**
 * 4965 temperature calculation.
 *
 * The driver must calculate the device temperature beक्रमe calculating
 * a txघातer setting (amplअगरier gain is temperature dependent).  The
 * calculation uses 4 measurements, 3 of which (R1, R2, R3) are calibration
 * values used क्रम the lअगरe of the driver, and one of which (R4) is the
 * real-समय temperature indicator.
 *
 * uCode provides all 4 values to the driver via the "initialize alive"
 * notअगरication (see काष्ठा il4965_init_alive_resp).  After the runसमय uCode
 * image loads, uCode updates the R4 value via stats notअगरications
 * (see N_STATS), which occur after each received beacon
 * when associated, or can be requested via C_STATS.
 *
 * NOTE:  uCode provides the R4 value as a 23-bit चिन्हित value.  Driver
 *        must sign-extend to 32 bits beक्रमe applying क्रमmula below.
 *
 * Formula:
 *
 * degrees Kelvin = ((97 * 259 * (R4 - R2) / (R3 - R1)) / 100) + 8
 *
 * NOTE:  The basic क्रमmula is 259 * (R4-R2) / (R3-R1).  The 97/100 is
 * an additional correction, which should be centered around 0 degrees
 * Celsius (273 degrees Kelvin).  The 8 (3 percent of 273) compensates क्रम
 * centering the 97/100 correction around 0 degrees K.
 *
 * Add 273 to Kelvin value to find degrees Celsius, क्रम comparing current
 * temperature with factory-measured temperatures when calculating txघातer
 * settings.
 */
#घोषणा TEMPERATURE_CALIB_KELVIN_OFFSET 8
#घोषणा TEMPERATURE_CALIB_A_VAL 259

/* Limit range of calculated temperature to be between these Kelvin values */
#घोषणा IL_TX_POWER_TEMPERATURE_MIN  (263)
#घोषणा IL_TX_POWER_TEMPERATURE_MAX  (410)

#घोषणा IL_TX_POWER_TEMPERATURE_OUT_OF_RANGE(t) \
	((t) < IL_TX_POWER_TEMPERATURE_MIN || \
	 (t) > IL_TX_POWER_TEMPERATURE_MAX)

व्योम il4965_temperature_calib(काष्ठा il_priv *il);
/********************* END TEMPERATURE ***************************************/

/********************* START TXPOWER *****************************************/

/**
 * 4965 txघातer calculations rely on inक्रमmation from three sources:
 *
 *     1) EEPROM
 *     2) "initialize" alive notअगरication
 *     3) stats notअगरications
 *
 * EEPROM data consists of:
 *
 * 1)  Regulatory inक्रमmation (max txघातer and channel usage flags) is provided
 *     separately क्रम each channel that can possibly supported by 4965.
 *     40 MHz wide (.11n HT40) channels are listed separately from 20 MHz
 *     (legacy) channels.
 *
 *     See काष्ठा il4965_eeprom_channel क्रम क्रमmat, and काष्ठा il4965_eeprom
 *     क्रम locations in EEPROM.
 *
 * 2)  Factory txघातer calibration inक्रमmation is provided separately क्रम
 *     sub-bands of contiguous channels.  2.4GHz has just one sub-band,
 *     but 5 GHz has several sub-bands.
 *
 *     In addition, per-band (2.4 and 5 Ghz) saturation txघातers are provided.
 *
 *     See काष्ठा il4965_eeprom_calib_info (and the tree of काष्ठाures
 *     contained within it) क्रम क्रमmat, and काष्ठा il4965_eeprom क्रम
 *     locations in EEPROM.
 *
 * "Initialization alive" notअगरication (see काष्ठा il4965_init_alive_resp)
 * consists of:
 *
 * 1)  Temperature calculation parameters.
 *
 * 2)  Power supply voltage measurement.
 *
 * 3)  Tx gain compensation to balance 2 transmitters क्रम MIMO use.
 *
 * Statistics notअगरications deliver:
 *
 * 1)  Current values क्रम temperature param R4.
 */

/**
 * To calculate a txघातer setting क्रम a given desired target txघातer, channel,
 * modulation bit rate, and transmitter chain (4965 has 2 transmitters to
 * support MIMO and transmit भागersity), driver must करो the following:
 *
 * 1)  Compare desired txघातer vs. (EEPROM) regulatory limit क्रम this channel.
 *     Do not exceed regulatory limit; reduce target txघातer अगर necessary.
 *
 *     If setting up txघातers क्रम MIMO rates (rate idxes 8-15, 24-31),
 *     2 transmitters will be used simultaneously; driver must reduce the
 *     regulatory limit by 3 dB (half-घातer) क्रम each transmitter, so the
 *     combined total output of the 2 transmitters is within regulatory limits.
 *
 *
 * 2)  Compare target txघातer vs. (EEPROM) saturation txघातer *reduced by
 *     backoff क्रम this bit rate*.  Do not exceed (saturation - backoff[rate]);
 *     reduce target txघातer अगर necessary.
 *
 *     Backoff values below are in 1/2 dB units (equivalent to steps in
 *     txघातer gain tables):
 *
 *     OFDM 6 - 36 MBit:  10 steps (5 dB)
 *     OFDM 48 MBit:      15 steps (7.5 dB)
 *     OFDM 54 MBit:      17 steps (8.5 dB)
 *     OFDM 60 MBit:      20 steps (10 dB)
 *     CCK all rates:     10 steps (5 dB)
 *
 *     Backoff values apply to saturation txघातer on a per-transmitter basis;
 *     when using MIMO (2 transmitters), each transmitter uses the same
 *     saturation level provided in EEPROM, and the same backoff values;
 *     no reduction (such as with regulatory txघातer limits) is required.
 *
 *     Saturation and Backoff values apply equally to 20 Mhz (legacy) channel
 *     widths and 40 Mhz (.11n HT40) channel widths; there is no separate
 *     factory measurement क्रम ht40 channels.
 *
 *     The result of this step is the final target txघातer.  The rest of
 *     the steps figure out the proper settings क्रम the device to achieve
 *     that target txघातer.
 *
 *
 * 3)  Determine (EEPROM) calibration sub band क्रम the target channel, by
 *     comparing against first and last channels in each sub band
 *     (see काष्ठा il4965_eeprom_calib_subband_info).
 *
 *
 * 4)  Linearly पूर्णांकerpolate (EEPROM) factory calibration measurement sets,
 *     referencing the 2 factory-measured (sample) channels within the sub band.
 *
 *     Interpolation is based on dअगरference between target channel's frequency
 *     and the sample channels' frequencies.  Since channel numbers are based
 *     on frequency (5 MHz between each channel number), this is equivalent
 *     to पूर्णांकerpolating based on channel number dअगरferences.
 *
 *     Note that the sample channels may or may not be the channels at the
 *     edges of the sub band.  The target channel may be "outside" of the
 *     span of the sampled channels.
 *
 *     Driver may choose the pair (क्रम 2 Tx chains) of measurements (see
 *     काष्ठा il4965_eeprom_calib_ch_info) क्रम which the actual measured
 *     txघातer comes बंदst to the desired txघातer.  Usually, though,
 *     the middle set of measurements is बंदst to the regulatory limits,
 *     and is thereक्रमe a good choice क्रम all txघातer calculations (this
 *     assumes that high accuracy is needed क्रम maximizing legal txघातer,
 *     जबतक lower txघातer configurations करो not need as much accuracy).
 *
 *     Driver should पूर्णांकerpolate both members of the chosen measurement pair,
 *     i.e. क्रम both Tx chains (radio transmitters), unless the driver knows
 *     that only one of the chains will be used (e.g. only one tx antenna
 *     connected, but this should be unusual).  The rate scaling algorithm
 *     चयनes antennas to find best perक्रमmance, so both Tx chains will
 *     be used (although only one at a समय) even क्रम non-MIMO transmissions.
 *
 *     Driver should पूर्णांकerpolate factory values क्रम temperature, gain table
 *     idx, and actual घातer.  The घातer amplअगरier detector values are
 *     not used by the driver.
 *
 *     Sanity check:  If the target channel happens to be one of the sample
 *     channels, the results should agree with the sample channel's
 *     measurements!
 *
 *
 * 5)  Find dअगरference between desired txघातer and (पूर्णांकerpolated)
 *     factory-measured txघातer.  Using (पूर्णांकerpolated) factory gain table idx
 *     (shown अन्यथाwhere) as a starting poपूर्णांक, adjust this idx lower to
 *     increase txघातer, or higher to decrease txघातer, until the target
 *     txघातer is reached.  Each step in the gain table is 1/2 dB.
 *
 *     For example, अगर factory measured txघातer is 16 dBm, and target txघातer
 *     is 13 dBm, add 6 steps to the factory gain idx to reduce txघातer
 *     by 3 dB.
 *
 *
 * 6)  Find dअगरference between current device temperature and (पूर्णांकerpolated)
 *     factory-measured temperature क्रम sub-band.  Factory values are in
 *     degrees Celsius.  To calculate current temperature, see comments क्रम
 *     "4965 temperature calculation".
 *
 *     If current temperature is higher than factory temperature, driver must
 *     increase gain (lower gain table idx), and vice verse.
 *
 *     Temperature affects gain dअगरferently क्रम dअगरferent channels:
 *
 *     2.4 GHz all channels:  3.5 degrees per half-dB step
 *     5 GHz channels 34-43:  4.5 degrees per half-dB step
 *     5 GHz channels >= 44:  4.0 degrees per half-dB step
 *
 *     NOTE:  Temperature can increase rapidly when transmitting, especially
 *            with heavy traffic at high txघातers.  Driver should update
 *            temperature calculations often under these conditions to
 *            मुख्यtain strong txघातer in the face of rising temperature.
 *
 *
 * 7)  Find dअगरference between current घातer supply voltage indicator
 *     (from "initialize alive") and factory-measured घातer supply voltage
 *     indicator (EEPROM).
 *
 *     If the current voltage is higher (indicator is lower) than factory
 *     voltage, gain should be reduced (gain table idx increased) by:
 *
 *     (eeprom - current) / 7
 *
 *     If the current voltage is lower (indicator is higher) than factory
 *     voltage, gain should be increased (gain table idx decreased) by:
 *
 *     2 * (current - eeprom) / 7
 *
 *     If number of idx steps in either direction turns out to be > 2,
 *     something is wrong ... just use 0.
 *
 *     NOTE:  Voltage compensation is independent of band/channel.
 *
 *     NOTE:  "Initialize" uCode measures current voltage, which is assumed
 *            to be स्थिरant after this initial measurement.  Voltage
 *            compensation क्रम txघातer (number of steps in gain table)
 *            may be calculated once and used until the next uCode bootload.
 *
 *
 * 8)  If setting up txघातers क्रम MIMO rates (rate idxes 8-15, 24-31),
 *     adjust txघातer क्रम each transmitter chain, so txघातer is balanced
 *     between the two chains.  There are 5 pairs of tx_atten[group][chain]
 *     values in "initialize alive", one pair क्रम each of 5 channel ranges:
 *
 *     Group 0:  5 GHz channel 34-43
 *     Group 1:  5 GHz channel 44-70
 *     Group 2:  5 GHz channel 71-124
 *     Group 3:  5 GHz channel 125-200
 *     Group 4:  2.4 GHz all channels
 *
 *     Add the tx_atten[group][chain] value to the idx क्रम the target chain.
 *     The values are चिन्हित, but are in pairs of 0 and a non-negative number,
 *     so as to reduce gain (अगर necessary) of the "hotter" channel.  This
 *     aव्योमs any need to द्विगुन-check क्रम regulatory compliance after
 *     this step.
 *
 *
 * 9)  If setting up क्रम a CCK rate, lower the gain by adding a CCK compensation
 *     value to the idx:
 *
 *     Hardware rev B:  9 steps (4.5 dB)
 *     Hardware rev C:  5 steps (2.5 dB)
 *
 *     Hardware rev क्रम 4965 can be determined by पढ़ोing CSR_HW_REV_WA_REG,
 *     bits [3:2], 1 = B, 2 = C.
 *
 *     NOTE:  This compensation is in addition to any saturation backoff that
 *            might have been applied in an earlier step.
 *
 *
 * 10) Select the gain table, based on band (2.4 vs 5 GHz).
 *
 *     Limit the adjusted idx to stay within the table!
 *
 *
 * 11) Read gain table entries क्रम DSP and radio gain, place पूर्णांकo appropriate
 *     location(s) in command (काष्ठा il4965_txघातertable_cmd).
 */

/**
 * When MIMO is used (2 transmitters operating simultaneously), driver should
 * limit each transmitter to deliver a max of 3 dB below the regulatory limit
 * क्रम the device.  That is, use half घातer क्रम each transmitter, so total
 * txघातer is within regulatory limits.
 *
 * The value "6" represents number of steps in gain table to reduce घातer 3 dB.
 * Each step is 1/2 dB.
 */
#घोषणा IL_TX_POWER_MIMO_REGULATORY_COMPENSATION (6)

/**
 * CCK gain compensation.
 *
 * When calculating txघातers क्रम CCK, after making sure that the target घातer
 * is within regulatory and saturation limits, driver must additionally
 * back off gain by adding these values to the gain table idx.
 *
 * Hardware rev क्रम 4965 can be determined by पढ़ोing CSR_HW_REV_WA_REG,
 * bits [3:2], 1 = B, 2 = C.
 */
#घोषणा IL_TX_POWER_CCK_COMPENSATION_B_STEP (9)
#घोषणा IL_TX_POWER_CCK_COMPENSATION_C_STEP (5)

/*
 * 4965 घातer supply voltage compensation क्रम txघातer
 */
#घोषणा TX_POWER_IL_VOLTAGE_CODES_PER_03V   (7)

/**
 * Gain tables.
 *
 * The following tables contain pair of values क्रम setting txघातer, i.e.
 * gain settings क्रम the output of the device's digital संकेत processor (DSP),
 * and क्रम the analog gain काष्ठाure of the transmitter.
 *
 * Each entry in the gain tables represents a step of 1/2 dB.  Note that these
 * are *relative* steps, not indications of असलolute output घातer.  Output
 * घातer varies with temperature, voltage, and channel frequency, and also
 * requires consideration of average घातer (to satisfy regulatory स्थिरraपूर्णांकs),
 * and peak घातer (to aव्योम distortion of the output संकेत).
 *
 * Each entry contains two values:
 * 1)  DSP gain (or someबार called DSP attenuation).  This is a fine-grained
 *     linear value that multiplies the output of the digital संकेत processor,
 *     beक्रमe being sent to the analog radio.
 * 2)  Radio gain.  This sets the analog gain of the radio Tx path.
 *     It is a coarser setting, and behaves in a logarithmic (dB) fashion.
 *
 * EEPROM contains factory calibration data क्रम txघातer.  This maps actual
 * measured txघातer levels to gain settings in the "well known" tables
 * below ("well-known" means here that both factory calibration *and* the
 * driver work with the same table).
 *
 * There are separate tables क्रम 2.4 GHz and 5 GHz bands.  The 5 GHz table
 * has an extension (पूर्णांकo negative idxes), in हाल the driver needs to
 * boost घातer setting क्रम high device temperatures (higher than would be
 * present during factory calibration).  A 5 Ghz EEPROM idx of "40"
 * corresponds to the 49th entry in the table used by the driver.
 */
#घोषणा MIN_TX_GAIN_IDX		(0)	/* highest gain, lowest idx, 2.4 */
#घोषणा MIN_TX_GAIN_IDX_52GHZ_EXT	(-9)	/* highest gain, lowest idx, 5 */

/**
 * 2.4 GHz gain table
 *
 * Index    Dsp gain   Radio gain
 *   0        110         0x3f      (highest gain)
 *   1        104         0x3f
 *   2         98         0x3f
 *   3        110         0x3e
 *   4        104         0x3e
 *   5         98         0x3e
 *   6        110         0x3d
 *   7        104         0x3d
 *   8         98         0x3d
 *   9        110         0x3c
 *  10        104         0x3c
 *  11         98         0x3c
 *  12        110         0x3b
 *  13        104         0x3b
 *  14         98         0x3b
 *  15        110         0x3a
 *  16        104         0x3a
 *  17         98         0x3a
 *  18        110         0x39
 *  19        104         0x39
 *  20         98         0x39
 *  21        110         0x38
 *  22        104         0x38
 *  23         98         0x38
 *  24        110         0x37
 *  25        104         0x37
 *  26         98         0x37
 *  27        110         0x36
 *  28        104         0x36
 *  29         98         0x36
 *  30        110         0x35
 *  31        104         0x35
 *  32         98         0x35
 *  33        110         0x34
 *  34        104         0x34
 *  35         98         0x34
 *  36        110         0x33
 *  37        104         0x33
 *  38         98         0x33
 *  39        110         0x32
 *  40        104         0x32
 *  41         98         0x32
 *  42        110         0x31
 *  43        104         0x31
 *  44         98         0x31
 *  45        110         0x30
 *  46        104         0x30
 *  47         98         0x30
 *  48        110          0x6
 *  49        104          0x6
 *  50         98          0x6
 *  51        110          0x5
 *  52        104          0x5
 *  53         98          0x5
 *  54        110          0x4
 *  55        104          0x4
 *  56         98          0x4
 *  57        110          0x3
 *  58        104          0x3
 *  59         98          0x3
 *  60        110          0x2
 *  61        104          0x2
 *  62         98          0x2
 *  63        110          0x1
 *  64        104          0x1
 *  65         98          0x1
 *  66        110          0x0
 *  67        104          0x0
 *  68         98          0x0
 *  69         97            0
 *  70         96            0
 *  71         95            0
 *  72         94            0
 *  73         93            0
 *  74         92            0
 *  75         91            0
 *  76         90            0
 *  77         89            0
 *  78         88            0
 *  79         87            0
 *  80         86            0
 *  81         85            0
 *  82         84            0
 *  83         83            0
 *  84         82            0
 *  85         81            0
 *  86         80            0
 *  87         79            0
 *  88         78            0
 *  89         77            0
 *  90         76            0
 *  91         75            0
 *  92         74            0
 *  93         73            0
 *  94         72            0
 *  95         71            0
 *  96         70            0
 *  97         69            0
 *  98         68            0
 */

/**
 * 5 GHz gain table
 *
 * Index    Dsp gain   Radio gain
 *  -9 	      123         0x3F      (highest gain)
 *  -8 	      117         0x3F
 *  -7        110         0x3F
 *  -6        104         0x3F
 *  -5         98         0x3F
 *  -4        110         0x3E
 *  -3        104         0x3E
 *  -2         98         0x3E
 *  -1        110         0x3D
 *   0        104         0x3D
 *   1         98         0x3D
 *   2        110         0x3C
 *   3        104         0x3C
 *   4         98         0x3C
 *   5        110         0x3B
 *   6        104         0x3B
 *   7         98         0x3B
 *   8        110         0x3A
 *   9        104         0x3A
 *  10         98         0x3A
 *  11        110         0x39
 *  12        104         0x39
 *  13         98         0x39
 *  14        110         0x38
 *  15        104         0x38
 *  16         98         0x38
 *  17        110         0x37
 *  18        104         0x37
 *  19         98         0x37
 *  20        110         0x36
 *  21        104         0x36
 *  22         98         0x36
 *  23        110         0x35
 *  24        104         0x35
 *  25         98         0x35
 *  26        110         0x34
 *  27        104         0x34
 *  28         98         0x34
 *  29        110         0x33
 *  30        104         0x33
 *  31         98         0x33
 *  32        110         0x32
 *  33        104         0x32
 *  34         98         0x32
 *  35        110         0x31
 *  36        104         0x31
 *  37         98         0x31
 *  38        110         0x30
 *  39        104         0x30
 *  40         98         0x30
 *  41        110         0x25
 *  42        104         0x25
 *  43         98         0x25
 *  44        110         0x24
 *  45        104         0x24
 *  46         98         0x24
 *  47        110         0x23
 *  48        104         0x23
 *  49         98         0x23
 *  50        110         0x22
 *  51        104         0x18
 *  52         98         0x18
 *  53        110         0x17
 *  54        104         0x17
 *  55         98         0x17
 *  56        110         0x16
 *  57        104         0x16
 *  58         98         0x16
 *  59        110         0x15
 *  60        104         0x15
 *  61         98         0x15
 *  62        110         0x14
 *  63        104         0x14
 *  64         98         0x14
 *  65        110         0x13
 *  66        104         0x13
 *  67         98         0x13
 *  68        110         0x12
 *  69        104         0x08
 *  70         98         0x08
 *  71        110         0x07
 *  72        104         0x07
 *  73         98         0x07
 *  74        110         0x06
 *  75        104         0x06
 *  76         98         0x06
 *  77        110         0x05
 *  78        104         0x05
 *  79         98         0x05
 *  80        110         0x04
 *  81        104         0x04
 *  82         98         0x04
 *  83        110         0x03
 *  84        104         0x03
 *  85         98         0x03
 *  86        110         0x02
 *  87        104         0x02
 *  88         98         0x02
 *  89        110         0x01
 *  90        104         0x01
 *  91         98         0x01
 *  92        110         0x00
 *  93        104         0x00
 *  94         98         0x00
 *  95         93         0x00
 *  96         88         0x00
 *  97         83         0x00
 *  98         78         0x00
 */

/**
 * Sanity checks and शेष values क्रम EEPROM regulatory levels.
 * If EEPROM values fall outside MIN/MAX range, use शेष values.
 *
 * Regulatory limits refer to the maximum average txघातer allowed by
 * regulatory agencies in the geographies in which the device is meant
 * to be operated.  These limits are SKU-specअगरic (i.e. geography-specअगरic),
 * and channel-specअगरic; each channel has an inभागidual regulatory limit
 * listed in the EEPROM.
 *
 * Units are in half-dBm (i.e. "34" means 17 dBm).
 */
#घोषणा IL_TX_POWER_DEFAULT_REGULATORY_24   (34)
#घोषणा IL_TX_POWER_DEFAULT_REGULATORY_52   (34)
#घोषणा IL_TX_POWER_REGULATORY_MIN          (0)
#घोषणा IL_TX_POWER_REGULATORY_MAX          (34)

/**
 * Sanity checks and शेष values क्रम EEPROM saturation levels.
 * If EEPROM values fall outside MIN/MAX range, use शेष values.
 *
 * Saturation is the highest level that the output घातer amplअगरier can produce
 * without signअगरicant clipping distortion.  This is a "peak" घातer level.
 * Dअगरferent types of modulation (i.e. various "rates", and OFDM vs. CCK)
 * require dअगरfering amounts of backoff, relative to their average घातer output,
 * in order to aव्योम clipping distortion.
 *
 * Driver must make sure that it is violating neither the saturation limit,
 * nor the regulatory limit, when calculating Tx घातer settings क्रम various
 * rates.
 *
 * Units are in half-dBm (i.e. "38" means 19 dBm).
 */
#घोषणा IL_TX_POWER_DEFAULT_SATURATION_24   (38)
#घोषणा IL_TX_POWER_DEFAULT_SATURATION_52   (38)
#घोषणा IL_TX_POWER_SATURATION_MIN          (20)
#घोषणा IL_TX_POWER_SATURATION_MAX          (50)

/**
 * Channel groups used क्रम Tx Attenuation calibration (MIMO tx channel balance)
 * and thermal Txघातer calibration.
 *
 * When calculating txघातer, driver must compensate क्रम current device
 * temperature; higher temperature requires higher gain.  Driver must calculate
 * current temperature (see "4965 temperature calculation"), then compare vs.
 * factory calibration temperature in EEPROM; अगर current temperature is higher
 * than factory temperature, driver must *increase* gain by proportions shown
 * in table below.  If current temperature is lower than factory, driver must
 * *decrease* gain.
 *
 * Dअगरferent frequency ranges require dअगरferent compensation, as shown below.
 */
/* Group 0, 5.2 GHz ch 34-43:  4.5 degrees per 1/2 dB. */
#घोषणा CALIB_IL_TX_ATTEN_GR1_FCH 34
#घोषणा CALIB_IL_TX_ATTEN_GR1_LCH 43

/* Group 1, 5.3 GHz ch 44-70:  4.0 degrees per 1/2 dB. */
#घोषणा CALIB_IL_TX_ATTEN_GR2_FCH 44
#घोषणा CALIB_IL_TX_ATTEN_GR2_LCH 70

/* Group 2, 5.5 GHz ch 71-124:  4.0 degrees per 1/2 dB. */
#घोषणा CALIB_IL_TX_ATTEN_GR3_FCH 71
#घोषणा CALIB_IL_TX_ATTEN_GR3_LCH 124

/* Group 3, 5.7 GHz ch 125-200:  4.0 degrees per 1/2 dB. */
#घोषणा CALIB_IL_TX_ATTEN_GR4_FCH 125
#घोषणा CALIB_IL_TX_ATTEN_GR4_LCH 200

/* Group 4, 2.4 GHz all channels:  3.5 degrees per 1/2 dB. */
#घोषणा CALIB_IL_TX_ATTEN_GR5_FCH 1
#घोषणा CALIB_IL_TX_ATTEN_GR5_LCH 20

क्रमागत अणु
	CALIB_CH_GROUP_1 = 0,
	CALIB_CH_GROUP_2 = 1,
	CALIB_CH_GROUP_3 = 2,
	CALIB_CH_GROUP_4 = 3,
	CALIB_CH_GROUP_5 = 4,
	CALIB_CH_GROUP_MAX
पूर्ण;

/********************* END TXPOWER *****************************************/

/**
 * Tx/Rx Queues
 *
 * Most communication between driver and 4965 is via queues of data buffers.
 * For example, all commands that the driver issues to device's embedded
 * controller (uCode) are via the command queue (one of the Tx queues).  All
 * uCode command responses/replies/notअगरications, including Rx frames, are
 * conveyed from uCode to driver via the Rx queue.
 *
 * Most support क्रम these queues, including handshake support, resides in
 * काष्ठाures in host DRAM, shared between the driver and the device.  When
 * allocating this memory, the driver must make sure that data written by
 * the host CPU updates DRAM immediately (and करोes not get "stuck" in CPU's
 * cache memory), so DRAM and cache are consistent, and the device can
 * immediately see changes made by the driver.
 *
 * 4965 supports up to 16 DRAM-based Tx queues, and services these queues via
 * up to 7 DMA channels (FIFOs).  Each Tx queue is supported by a circular array
 * in DRAM containing 256 Transmit Frame Descriptors (TFDs).
 */
#घोषणा IL49_NUM_FIFOS	7
#घोषणा IL49_CMD_FIFO_NUM	4
#घोषणा IL49_NUM_QUEUES	16
#घोषणा IL49_NUM_AMPDU_QUEUES	8

/**
 * काष्ठा il4965_schedq_bc_tbl
 *
 * Byte Count table
 *
 * Each Tx queue uses a byte-count table containing 320 entries:
 * one 16-bit entry क्रम each of 256 TFDs, plus an additional 64 entries that
 * duplicate the first 64 entries (to aव्योम wrap-around within a Tx win;
 * max Tx win is 64 TFDs).
 *
 * When driver sets up a new TFD, it must also enter the total byte count
 * of the frame to be transmitted पूर्णांकo the corresponding entry in the byte
 * count table क्रम the chosen Tx queue.  If the TFD idx is 0-63, the driver
 * must duplicate the byte count entry in corresponding idx 256-319.
 *
 * padding माला_दो each byte count table on a 1024-byte boundary;
 * 4965 assumes tables are separated by 1024 bytes.
 */
काष्ठा il4965_scd_bc_tbl अणु
	__le16 tfd_offset[TFD_QUEUE_BC_SIZE];
	u8 pad[1024 - (TFD_QUEUE_BC_SIZE) * माप(__le16)];
पूर्ण __packed;

#घोषणा IL4965_RTC_INST_LOWER_BOUND		(0x000000)

/* RSSI to dBm */
#घोषणा IL4965_RSSI_OFFSET	44

/* PCI रेजिस्टरs */
#घोषणा PCI_CFG_RETRY_TIMEOUT	0x041

#घोषणा IL4965_DEFAULT_TX_RETRY  15

/* EEPROM */
#घोषणा IL4965_FIRST_AMPDU_QUEUE	10

/* Calibration */
व्योम il4965_chain_noise_calibration(काष्ठा il_priv *il, व्योम *stat_resp);
व्योम il4965_sensitivity_calibration(काष्ठा il_priv *il, व्योम *resp);
व्योम il4965_init_sensitivity(काष्ठा il_priv *il);
व्योम il4965_reset_run_समय_calib(काष्ठा il_priv *il);

/* Debug */
#अगर_घोषित CONFIG_IWLEGACY_DEBUGFS
बाह्य स्थिर काष्ठा il_debugfs_ops il4965_debugfs_ops;
#पूर्ण_अगर

/****************************/
/* Flow Handler Definitions */
/****************************/

/**
 * This I/O area is directly पढ़ो/writable by driver (e.g. Linux uses ग_लिखोl())
 * Addresses are offsets from device's PCI hardware base address.
 */
#घोषणा FH49_MEM_LOWER_BOUND                   (0x1000)
#घोषणा FH49_MEM_UPPER_BOUND                   (0x2000)

/**
 * Keep-Warm (KW) buffer base address.
 *
 * Driver must allocate a 4KByte buffer that is used by 4965 क्रम keeping the
 * host DRAM घातered on (via dummy accesses to DRAM) to मुख्यtain low-latency
 * DRAM access when 4965 is Txing or Rxing.  The dummy accesses prevent host
 * from going पूर्णांकo a घातer-savings mode that would cause higher DRAM latency,
 * and possible data over/under-runs, beक्रमe all Tx/Rx is complete.
 *
 * Driver loads FH49_KW_MEM_ADDR_REG with the physical address (bits 35:4)
 * of the buffer, which must be 4K aligned.  Once this is set up, the 4965
 * स्वतःmatically invokes keep-warm accesses when normal accesses might not
 * be sufficient to मुख्यtain fast DRAM response.
 *
 * Bit fields:
 *  31-0:  Keep-warm buffer physical base address [35:4], must be 4K aligned
 */
#घोषणा FH49_KW_MEM_ADDR_REG		     (FH49_MEM_LOWER_BOUND + 0x97C)

/**
 * TFD Circular Buffers Base (CBBC) addresses
 *
 * 4965 has 16 base poपूर्णांकer रेजिस्टरs, one क्रम each of 16 host-DRAM-resident
 * circular buffers (CBs/queues) containing Transmit Frame Descriptors (TFDs)
 * (see काष्ठा il_tfd_frame).  These 16 poपूर्णांकer रेजिस्टरs are offset by 0x04
 * bytes from one another.  Each TFD circular buffer in DRAM must be 256-byte
 * aligned (address bits 0-7 must be 0).
 *
 * Bit fields in each poपूर्णांकer रेजिस्टर:
 *  27-0: TFD CB physical base address [35:8], must be 256-byte aligned
 */
#घोषणा FH49_MEM_CBBC_LOWER_BOUND          (FH49_MEM_LOWER_BOUND + 0x9D0)
#घोषणा FH49_MEM_CBBC_UPPER_BOUND          (FH49_MEM_LOWER_BOUND + 0xA10)

/* Find TFD CB base poपूर्णांकer क्रम given queue (range 0-15). */
#घोषणा FH49_MEM_CBBC_QUEUE(x)  (FH49_MEM_CBBC_LOWER_BOUND + (x) * 0x4)

/**
 * Rx SRAM Control and Status Registers (RSCSR)
 *
 * These रेजिस्टरs provide handshake between driver and 4965 क्रम the Rx queue
 * (this queue handles *all* command responses, notअगरications, Rx data, etc.
 * sent from 4965 uCode to host driver).  Unlike Tx, there is only one Rx
 * queue, and only one Rx DMA/FIFO channel.  Also unlike Tx, which can
 * concatenate up to 20 DRAM buffers to क्रमm a Tx frame, each Receive Buffer
 * Descriptor (RBD) poपूर्णांकs to only one Rx Buffer (RB); there is a 1:1
 * mapping between RBDs and RBs.
 *
 * Driver must allocate host DRAM memory क्रम the following, and set the
 * physical address of each पूर्णांकo 4965 रेजिस्टरs:
 *
 * 1)  Receive Buffer Descriptor (RBD) circular buffer (CB), typically with 256
 *     entries (although any घातer of 2, up to 4096, is selectable by driver).
 *     Each entry (1 dword) poपूर्णांकs to a receive buffer (RB) of consistent size
 *     (typically 4K, although 8K or 16K are also selectable by driver).
 *     Driver sets up RB size and number of RBDs in the CB via Rx config
 *     रेजिस्टर FH49_MEM_RCSR_CHNL0_CONFIG_REG.
 *
 *     Bit fields within one RBD:
 *     27-0:  Receive Buffer physical address bits [35:8], 256-byte aligned
 *
 *     Driver sets physical address [35:8] of base of RBD circular buffer
 *     पूर्णांकo FH49_RSCSR_CHNL0_RBDCB_BASE_REG [27:0].
 *
 * 2)  Rx status buffer, 8 bytes, in which 4965 indicates which Rx Buffers
 *     (RBs) have been filled, via a "write pointer", actually the idx of
 *     the RB's corresponding RBD within the circular buffer.  Driver sets
 *     physical address [35:4] पूर्णांकo FH49_RSCSR_CHNL0_STTS_WPTR_REG [31:0].
 *
 *     Bit fields in lower dword of Rx status buffer (upper dword not used
 *     by driver; see काष्ठा il4965_shared, val0):
 *     31-12:  Not used by driver
 *     11- 0:  Index of last filled Rx buffer descriptor
 *             (4965 ग_लिखोs, driver पढ़ोs this value)
 *
 * As the driver prepares Receive Buffers (RBs) क्रम 4965 to fill, driver must
 * enter poपूर्णांकers to these RBs पूर्णांकo contiguous RBD circular buffer entries,
 * and update the 4965's "write" idx रेजिस्टर,
 * FH49_RSCSR_CHNL0_RBDCB_WPTR_REG.
 *
 * This "write" idx corresponds to the *next* RBD that the driver will make
 * available, i.e. one RBD past the tail of the पढ़ोy-to-fill RBDs within
 * the circular buffer.  This value should initially be 0 (beक्रमe preparing any
 * RBs), should be 8 after preparing the first 8 RBs (क्रम example), and must
 * wrap back to 0 at the end of the circular buffer (but करोn't wrap beक्रमe
 * "read" idx has advanced past 1!  See below).
 * NOTE:  4965 EXPECTS THE WRITE IDX TO BE INCREMENTED IN MULTIPLES OF 8.
 *
 * As the 4965 fills RBs (referenced from contiguous RBDs within the circular
 * buffer), it updates the Rx status buffer in host DRAM, 2) described above,
 * to tell the driver the idx of the latest filled RBD.  The driver must
 * पढ़ो this "read" idx from DRAM after receiving an Rx पूर्णांकerrupt from 4965.
 *
 * The driver must also पूर्णांकernally keep track of a third idx, which is the
 * next RBD to process.  When receiving an Rx पूर्णांकerrupt, driver should process
 * all filled but unprocessed RBs up to, but not including, the RB
 * corresponding to the "read" idx.  For example, अगर "read" idx becomes "1",
 * driver may process the RB poपूर्णांकed to by RBD 0.  Depending on volume of
 * traffic, there may be many RBs to process.
 *
 * If पढ़ो idx == ग_लिखो idx, 4965 thinks there is no room to put new data.
 * Due to this, the maximum number of filled RBs is 255, instead of 256.  To
 * be safe, make sure that there is a gap of at least 2 RBDs between "write"
 * and "read" idxes; that is, make sure that there are no more than 254
 * buffers रुकोing to be filled.
 */
#घोषणा FH49_MEM_RSCSR_LOWER_BOUND	(FH49_MEM_LOWER_BOUND + 0xBC0)
#घोषणा FH49_MEM_RSCSR_UPPER_BOUND	(FH49_MEM_LOWER_BOUND + 0xC00)
#घोषणा FH49_MEM_RSCSR_CHNL0		(FH49_MEM_RSCSR_LOWER_BOUND)

/**
 * Physical base address of 8-byte Rx Status buffer.
 * Bit fields:
 *  31-0: Rx status buffer physical base address [35:4], must 16-byte aligned.
 */
#घोषणा FH49_RSCSR_CHNL0_STTS_WPTR_REG	(FH49_MEM_RSCSR_CHNL0)

/**
 * Physical base address of Rx Buffer Descriptor Circular Buffer.
 * Bit fields:
 *  27-0:  RBD CD physical base address [35:8], must be 256-byte aligned.
 */
#घोषणा FH49_RSCSR_CHNL0_RBDCB_BASE_REG	(FH49_MEM_RSCSR_CHNL0 + 0x004)

/**
 * Rx ग_लिखो poपूर्णांकer (idx, really!).
 * Bit fields:
 *  11-0:  Index of driver's most recent prepared-to-be-filled RBD, + 1.
 *         NOTE:  For 256-entry circular buffer, use only bits [7:0].
 */
#घोषणा FH49_RSCSR_CHNL0_RBDCB_WPTR_REG	(FH49_MEM_RSCSR_CHNL0 + 0x008)
#घोषणा FH49_RSCSR_CHNL0_WPTR        (FH49_RSCSR_CHNL0_RBDCB_WPTR_REG)

/**
 * Rx Config/Status Registers (RCSR)
 * Rx Config Reg क्रम channel 0 (only channel used)
 *
 * Driver must initialize FH49_MEM_RCSR_CHNL0_CONFIG_REG as follows क्रम
 * normal operation (see bit fields).
 *
 * Clearing FH49_MEM_RCSR_CHNL0_CONFIG_REG to 0 turns off Rx DMA.
 * Driver should poll FH49_MEM_RSSR_RX_STATUS_REG	क्रम
 * FH49_RSSR_CHNL0_RX_STATUS_CHNL_IDLE (bit 24) beक्रमe continuing.
 *
 * Bit fields:
 * 31-30: Rx DMA channel enable: '00' off/pause, '01' छोड़ो at end of frame,
 *        '10' operate normally
 * 29-24: reserved
 * 23-20: # RBDs in circular buffer = 2^value; use "8" क्रम 256 RBDs (normal),
 *        min "5" क्रम 32 RBDs, max "12" क्रम 4096 RBDs.
 * 19-18: reserved
 * 17-16: size of each receive buffer; '00' 4K (normal), '01' 8K,
 *        '10' 12K, '11' 16K.
 * 15-14: reserved
 * 13-12: IRQ destination; '00' none, '01' host driver (normal operation)
 * 11- 4: समयout क्रम closing Rx buffer and पूर्णांकerrupting host (units 32 usec)
 *        typical value 0x10 (about 1/2 msec)
 *  3- 0: reserved
 */
#घोषणा FH49_MEM_RCSR_LOWER_BOUND      (FH49_MEM_LOWER_BOUND + 0xC00)
#घोषणा FH49_MEM_RCSR_UPPER_BOUND      (FH49_MEM_LOWER_BOUND + 0xCC0)
#घोषणा FH49_MEM_RCSR_CHNL0            (FH49_MEM_RCSR_LOWER_BOUND)

#घोषणा FH49_MEM_RCSR_CHNL0_CONFIG_REG	(FH49_MEM_RCSR_CHNL0)

#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_RB_TIMEOUT_MSK (0x00000FF0)	/* bits 4-11 */
#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_MSK   (0x00001000)	/* bits 12 */
#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_SINGLE_FRAME_MSK (0x00008000)	/* bit 15 */
#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_RB_SIZE_MSK   (0x00030000)	/* bits 16-17 */
#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_RBDBC_SIZE_MSK (0x00F00000)	/* bits 20-23 */
#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_DMA_CHNL_EN_MSK (0xC0000000)	/* bits 30-31 */

#घोषणा FH49_RCSR_RX_CONFIG_RBDCB_SIZE_POS	(20)
#घोषणा FH49_RCSR_RX_CONFIG_REG_IRQ_RBTH_POS	(4)
#घोषणा RX_RB_TIMEOUT	(0x10)

#घोषणा FH49_RCSR_RX_CONFIG_CHNL_EN_PAUSE_VAL         (0x00000000)
#घोषणा FH49_RCSR_RX_CONFIG_CHNL_EN_PAUSE_खातापूर्ण_VAL     (0x40000000)
#घोषणा FH49_RCSR_RX_CONFIG_CHNL_EN_ENABLE_VAL        (0x80000000)

#घोषणा FH49_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_4K    (0x00000000)
#घोषणा FH49_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_8K    (0x00010000)
#घोषणा FH49_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_12K   (0x00020000)
#घोषणा FH49_RCSR_RX_CONFIG_REG_VAL_RB_SIZE_16K   (0x00030000)

#घोषणा FH49_RCSR_CHNL0_RX_IGNORE_RXF_EMPTY              (0x00000004)
#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_NO_INT_VAL    (0x00000000)
#घोषणा FH49_RCSR_CHNL0_RX_CONFIG_IRQ_DEST_INT_HOST_VAL  (0x00001000)

/**
 * Rx Shared Status Registers (RSSR)
 *
 * After stopping Rx DMA channel (writing 0 to
 * FH49_MEM_RCSR_CHNL0_CONFIG_REG), driver must poll
 * FH49_MEM_RSSR_RX_STATUS_REG until Rx channel is idle.
 *
 * Bit fields:
 *  24:  1 = Channel 0 is idle
 *
 * FH49_MEM_RSSR_SHARED_CTRL_REG and FH49_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV
 * contain शेष values that should not be altered by the driver.
 */
#घोषणा FH49_MEM_RSSR_LOWER_BOUND           (FH49_MEM_LOWER_BOUND + 0xC40)
#घोषणा FH49_MEM_RSSR_UPPER_BOUND           (FH49_MEM_LOWER_BOUND + 0xD00)

#घोषणा FH49_MEM_RSSR_SHARED_CTRL_REG       (FH49_MEM_RSSR_LOWER_BOUND)
#घोषणा FH49_MEM_RSSR_RX_STATUS_REG	(FH49_MEM_RSSR_LOWER_BOUND + 0x004)
#घोषणा FH49_MEM_RSSR_RX_ENABLE_ERR_IRQ2DRV\
					(FH49_MEM_RSSR_LOWER_BOUND + 0x008)

#घोषणा FH49_RSSR_CHNL0_RX_STATUS_CHNL_IDLE	(0x01000000)

#घोषणा FH49_MEM_TFDIB_REG1_ADDR_BITSHIFT	28

/* TFDB  Area - TFDs buffer table */
#घोषणा FH49_MEM_TFDIB_DRAM_ADDR_LSB_MSK      (0xFFFFFFFF)
#घोषणा FH49_TFDIB_LOWER_BOUND       (FH49_MEM_LOWER_BOUND + 0x900)
#घोषणा FH49_TFDIB_UPPER_BOUND       (FH49_MEM_LOWER_BOUND + 0x958)
#घोषणा FH49_TFDIB_CTRL0_REG(_chnl)  (FH49_TFDIB_LOWER_BOUND + 0x8 * (_chnl))
#घोषणा FH49_TFDIB_CTRL1_REG(_chnl)  (FH49_TFDIB_LOWER_BOUND + 0x8 * (_chnl) + 0x4)

/**
 * Transmit DMA Channel Control/Status Registers (TCSR)
 *
 * 4965 has one configuration रेजिस्टर क्रम each of 8 Tx DMA/FIFO channels
 * supported in hardware (करोn't confuse these with the 16 Tx queues in DRAM,
 * which feed the DMA/FIFO channels); config regs are separated by 0x20 bytes.
 *
 * To use a Tx DMA channel, driver must initialize its
 * FH49_TCSR_CHNL_TX_CONFIG_REG(chnl) with:
 *
 * FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE |
 * FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE_VAL
 *
 * All other bits should be 0.
 *
 * Bit fields:
 * 31-30: Tx DMA channel enable: '00' off/pause, '01' छोड़ो at end of frame,
 *        '10' operate normally
 * 29- 4: Reserved, set to "0"
 *     3: Enable पूर्णांकernal DMA requests (1, normal operation), disable (0)
 *  2- 0: Reserved, set to "0"
 */
#घोषणा FH49_TCSR_LOWER_BOUND  (FH49_MEM_LOWER_BOUND + 0xD00)
#घोषणा FH49_TCSR_UPPER_BOUND  (FH49_MEM_LOWER_BOUND + 0xE60)

/* Find Control/Status reg क्रम given Tx DMA/FIFO channel */
#घोषणा FH49_TCSR_CHNL_NUM                            (7)
#घोषणा FH50_TCSR_CHNL_NUM                            (8)

/* TCSR: tx_config रेजिस्टर values */
#घोषणा FH49_TCSR_CHNL_TX_CONFIG_REG(_chnl)	\
		(FH49_TCSR_LOWER_BOUND + 0x20 * (_chnl))
#घोषणा FH49_TCSR_CHNL_TX_CREDIT_REG(_chnl)	\
		(FH49_TCSR_LOWER_BOUND + 0x20 * (_chnl) + 0x4)
#घोषणा FH49_TCSR_CHNL_TX_BUF_STS_REG(_chnl)	\
		(FH49_TCSR_LOWER_BOUND + 0x20 * (_chnl) + 0x8)

#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_MSG_MODE_TXF		(0x00000000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_MSG_MODE_DRV		(0x00000001)

#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_DISABLE	(0x00000000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CREDIT_ENABLE	(0x00000008)

#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_NOINT	(0x00000000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_ENDTFD	(0x00100000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_CIRQ_HOST_IFTFD	(0x00200000)

#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_NOINT	(0x00000000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_ENDTFD	(0x00400000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_CIRQ_RTC_IFTFD	(0x00800000)

#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_PAUSE	(0x00000000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_PAUSE_खातापूर्ण	(0x40000000)
#घोषणा FH49_TCSR_TX_CONFIG_REG_VAL_DMA_CHNL_ENABLE	(0x80000000)

#घोषणा FH49_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_EMPTY	(0x00000000)
#घोषणा FH49_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_WAIT	(0x00002000)
#घोषणा FH49_TCSR_CHNL_TX_BUF_STS_REG_VAL_TFDB_VALID	(0x00000003)

#घोषणा FH49_TCSR_CHNL_TX_BUF_STS_REG_POS_TB_NUM		(20)
#घोषणा FH49_TCSR_CHNL_TX_BUF_STS_REG_POS_TB_IDX		(12)

/**
 * Tx Shared Status Registers (TSSR)
 *
 * After stopping Tx DMA channel (writing 0 to
 * FH49_TCSR_CHNL_TX_CONFIG_REG(chnl)), driver must poll
 * FH49_TSSR_TX_STATUS_REG until selected Tx channel is idle
 * (channel's buffers empty | no pending requests).
 *
 * Bit fields:
 * 31-24:  1 = Channel buffers empty (channel 7:0)
 * 23-16:  1 = No pending requests (channel 7:0)
 */
#घोषणा FH49_TSSR_LOWER_BOUND		(FH49_MEM_LOWER_BOUND + 0xEA0)
#घोषणा FH49_TSSR_UPPER_BOUND		(FH49_MEM_LOWER_BOUND + 0xEC0)

#घोषणा FH49_TSSR_TX_STATUS_REG		(FH49_TSSR_LOWER_BOUND + 0x010)

/**
 * Bit fields क्रम TSSR(Tx Shared Status & Control) error status रेजिस्टर:
 * 31:  Indicates an address error when accessed to पूर्णांकernal memory
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 * 30:  Indicates that Host did not send the expected number of dwords to FH
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 * 16-9:Each status bit is क्रम one channel. Indicates that an (Error) ActDMA
 *	command was received from the scheduler जबतक the TRB was alपढ़ोy full
 *	with previous command
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 * 7-0: Each status bit indicates a channel's TxCredit error. When an error
 *	bit is set, it indicates that the FH has received a full indication
 *	from the RTC TxFIFO and the current value of the TxCredit counter was
 *	not equal to zero. This mean that the credit mechanism was not
 *	synchronized to the TxFIFO status
 *	uCode/driver must ग_लिखो "1" in order to clear this flag
 */
#घोषणा FH49_TSSR_TX_ERROR_REG		(FH49_TSSR_LOWER_BOUND + 0x018)

#घोषणा FH49_TSSR_TX_STATUS_REG_MSK_CHNL_IDLE(_chnl) ((1 << (_chnl)) << 16)

/* Tx service channels */
#घोषणा FH49_SRVC_CHNL		(9)
#घोषणा FH49_SRVC_LOWER_BOUND	(FH49_MEM_LOWER_BOUND + 0x9C8)
#घोषणा FH49_SRVC_UPPER_BOUND	(FH49_MEM_LOWER_BOUND + 0x9D0)
#घोषणा FH49_SRVC_CHNL_SRAM_ADDR_REG(_chnl) \
		(FH49_SRVC_LOWER_BOUND + ((_chnl) - 9) * 0x4)

#घोषणा FH49_TX_CHICKEN_BITS_REG	(FH49_MEM_LOWER_BOUND + 0xE98)
/* Inकाष्ठा FH to increment the retry count of a packet when
 * it is brought from the memory to TX-FIFO
 */
#घोषणा FH49_TX_CHICKEN_BITS_SCD_AUTO_RETRY_EN	(0x00000002)

/* Keep Warm Size */
#घोषणा IL_KW_SIZE 0x1000	/* 4k */

#पूर्ण_अगर /* __il_4965_h__ */
