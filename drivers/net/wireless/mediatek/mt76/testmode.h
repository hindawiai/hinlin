<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (C) 2020 Felix Fietkau <nbd@nbd.name>
 */
#अगर_अघोषित __MT76_TESTMODE_H
#घोषणा __MT76_TESTMODE_H

#घोषणा MT76_TM_TIMEOUT	10

/**
 * क्रमागत mt76_tesपंचांगode_attr - tesपंचांगode attributes inside NL80211_ATTR_TESTDATA
 *
 * @MT76_TM_ATTR_UNSPEC: (invalid attribute)
 *
 * @MT76_TM_ATTR_RESET: reset parameters to शेष (flag)
 * @MT76_TM_ATTR_STATE: test state (u32), see &क्रमागत mt76_tesपंचांगode_state
 *
 * @MT76_TM_ATTR_MTD_PART: mtd partition used क्रम eeprom data (string)
 * @MT76_TM_ATTR_MTD_OFFSET: offset of eeprom data within the partition (u32)
 *
 * @MT76_TM_ATTR_TX_COUNT: configured number of frames to send when setting
 *	state to MT76_TM_STATE_TX_FRAMES (u32)
 * @MT76_TM_ATTR_TX_PENDING: pending frames during MT76_TM_STATE_TX_FRAMES (u32)
 * @MT76_TM_ATTR_TX_LENGTH: packet tx mpdu length (u32)
 * @MT76_TM_ATTR_TX_RATE_MODE: packet tx mode (u8, see &क्रमागत mt76_tesपंचांगode_tx_mode)
 * @MT76_TM_ATTR_TX_RATE_NSS: packet tx number of spatial streams (u8)
 * @MT76_TM_ATTR_TX_RATE_IDX: packet tx rate/MCS index (u8)
 * @MT76_TM_ATTR_TX_RATE_SGI: packet tx use लघु guard पूर्णांकerval (u8)
 * @MT76_TM_ATTR_TX_RATE_LDPC: packet tx enable LDPC (u8)
 * @MT76_TM_ATTR_TX_RATE_STBC: packet tx enable STBC (u8)
 * @MT76_TM_ATTR_TX_LTF: packet tx LTF, set 0 to 2 क्रम 1x, 2x, and 4x LTF (u8)
 *
 * @MT76_TM_ATTR_TX_ANTENNA: tx antenna mask (u8)
 * @MT76_TM_ATTR_TX_POWER_CONTROL: enable tx घातer control (u8)
 * @MT76_TM_ATTR_TX_POWER: per-antenna tx घातer array (nested, u8 attrs)
 *
 * @MT76_TM_ATTR_FREQ_OFFSET: RF frequency offset (u32)
 *
 * @MT76_TM_ATTR_STATS: statistics (nested, see &क्रमागत mt76_tesपंचांगode_stats_attr)
 *
 * @MT76_TM_ATTR_TX_SPE_IDX: tx spatial extension index (u8)
 *
 * @MT76_TM_ATTR_TX_DUTY_CYCLE: packet tx duty cycle (u8)
 * @MT76_TM_ATTR_TX_IPG: tx पूर्णांकer-packet gap, in unit of us (u32)
 * @MT76_TM_ATTR_TX_TIME: packet transmission समय, in unit of us (u32)
 *
 */
क्रमागत mt76_tesपंचांगode_attr अणु
	MT76_TM_ATTR_UNSPEC,

	MT76_TM_ATTR_RESET,
	MT76_TM_ATTR_STATE,

	MT76_TM_ATTR_MTD_PART,
	MT76_TM_ATTR_MTD_OFFSET,

	MT76_TM_ATTR_TX_COUNT,
	MT76_TM_ATTR_TX_LENGTH,
	MT76_TM_ATTR_TX_RATE_MODE,
	MT76_TM_ATTR_TX_RATE_NSS,
	MT76_TM_ATTR_TX_RATE_IDX,
	MT76_TM_ATTR_TX_RATE_SGI,
	MT76_TM_ATTR_TX_RATE_LDPC,
	MT76_TM_ATTR_TX_RATE_STBC,
	MT76_TM_ATTR_TX_LTF,

	MT76_TM_ATTR_TX_ANTENNA,
	MT76_TM_ATTR_TX_POWER_CONTROL,
	MT76_TM_ATTR_TX_POWER,

	MT76_TM_ATTR_FREQ_OFFSET,

	MT76_TM_ATTR_STATS,

	MT76_TM_ATTR_TX_SPE_IDX,

	MT76_TM_ATTR_TX_DUTY_CYCLE,
	MT76_TM_ATTR_TX_IPG,
	MT76_TM_ATTR_TX_TIME,

	/* keep last */
	NUM_MT76_TM_ATTRS,
	MT76_TM_ATTR_MAX = NUM_MT76_TM_ATTRS - 1,
पूर्ण;

/**
 * क्रमागत mt76_tesपंचांगode_state - statistics attributes
 *
 * @MT76_TM_STATS_ATTR_TX_PENDING: pending tx frames (u32)
 * @MT76_TM_STATS_ATTR_TX_QUEUED: queued tx frames (u32)
 * @MT76_TM_STATS_ATTR_TX_QUEUED: completed tx frames (u32)
 *
 * @MT76_TM_STATS_ATTR_RX_PACKETS: number of rx packets (u64)
 * @MT76_TM_STATS_ATTR_RX_FCS_ERROR: number of rx packets with FCS error (u64)
 * @MT76_TM_STATS_ATTR_LAST_RX: inक्रमmation about the last received packet
 *	see &क्रमागत mt76_tesपंचांगode_rx_attr
 */
क्रमागत mt76_tesपंचांगode_stats_attr अणु
	MT76_TM_STATS_ATTR_UNSPEC,
	MT76_TM_STATS_ATTR_PAD,

	MT76_TM_STATS_ATTR_TX_PENDING,
	MT76_TM_STATS_ATTR_TX_QUEUED,
	MT76_TM_STATS_ATTR_TX_DONE,

	MT76_TM_STATS_ATTR_RX_PACKETS,
	MT76_TM_STATS_ATTR_RX_FCS_ERROR,
	MT76_TM_STATS_ATTR_LAST_RX,

	/* keep last */
	NUM_MT76_TM_STATS_ATTRS,
	MT76_TM_STATS_ATTR_MAX = NUM_MT76_TM_STATS_ATTRS - 1,
पूर्ण;


/**
 * क्रमागत mt76_tesपंचांगode_rx_attr - packet rx inक्रमmation
 *
 * @MT76_TM_RX_ATTR_FREQ_OFFSET: frequency offset (s32)
 * @MT76_TM_RX_ATTR_RCPI: received channel घातer indicator (array, u8)
 * @MT76_TM_RX_ATTR_IB_RSSI: पूर्णांकernal inband RSSI (array, s8)
 * @MT76_TM_RX_ATTR_WB_RSSI: पूर्णांकernal wideband RSSI (array, s8)
 * @MT76_TM_RX_ATTR_SNR: संकेत-to-noise ratio (u8)
 */
क्रमागत mt76_tesपंचांगode_rx_attr अणु
	MT76_TM_RX_ATTR_UNSPEC,

	MT76_TM_RX_ATTR_FREQ_OFFSET,
	MT76_TM_RX_ATTR_RCPI,
	MT76_TM_RX_ATTR_IB_RSSI,
	MT76_TM_RX_ATTR_WB_RSSI,
	MT76_TM_RX_ATTR_SNR,

	/* keep last */
	NUM_MT76_TM_RX_ATTRS,
	MT76_TM_RX_ATTR_MAX = NUM_MT76_TM_RX_ATTRS - 1,
पूर्ण;

/**
 * क्रमागत mt76_tesपंचांगode_state - phy test state
 *
 * @MT76_TM_STATE_OFF: test mode disabled (normal operation)
 * @MT76_TM_STATE_IDLE: test mode enabled, but idle
 * @MT76_TM_STATE_TX_FRAMES: send a fixed number of test frames
 * @MT76_TM_STATE_RX_FRAMES: receive packets and keep statistics
 * @MT76_TM_STATE_TX_CONT: waveक्रमm tx without समय gap
 */
क्रमागत mt76_tesपंचांगode_state अणु
	MT76_TM_STATE_OFF,
	MT76_TM_STATE_IDLE,
	MT76_TM_STATE_TX_FRAMES,
	MT76_TM_STATE_RX_FRAMES,
	MT76_TM_STATE_TX_CONT,

	/* keep last */
	NUM_MT76_TM_STATES,
	MT76_TM_STATE_MAX = NUM_MT76_TM_STATES - 1,
पूर्ण;

/**
 * क्रमागत mt76_tesपंचांगode_tx_mode - packet tx phy mode
 *
 * @MT76_TM_TX_MODE_CCK: legacy CCK mode
 * @MT76_TM_TX_MODE_OFDM: legacy OFDM mode
 * @MT76_TM_TX_MODE_HT: 802.11n MCS
 * @MT76_TM_TX_MODE_VHT: 802.11ac MCS
 * @MT76_TM_TX_MODE_HE_SU: 802.11ax single-user MIMO
 * @MT76_TM_TX_MODE_HE_EXT_SU: 802.11ax extended-range SU
 * @MT76_TM_TX_MODE_HE_TB: 802.11ax trigger-based
 * @MT76_TM_TX_MODE_HE_MU: 802.11ax multi-user MIMO
 */
क्रमागत mt76_tesपंचांगode_tx_mode अणु
	MT76_TM_TX_MODE_CCK,
	MT76_TM_TX_MODE_OFDM,
	MT76_TM_TX_MODE_HT,
	MT76_TM_TX_MODE_VHT,
	MT76_TM_TX_MODE_HE_SU,
	MT76_TM_TX_MODE_HE_EXT_SU,
	MT76_TM_TX_MODE_HE_TB,
	MT76_TM_TX_MODE_HE_MU,

	/* keep last */
	NUM_MT76_TM_TX_MODES,
	MT76_TM_TX_MODE_MAX = NUM_MT76_TM_TX_MODES - 1,
पूर्ण;

#पूर्ण_अगर
