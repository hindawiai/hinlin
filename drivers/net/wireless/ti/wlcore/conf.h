<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __CONF_H__
#घोषणा __CONF_H__

क्रमागत अणु
	CONF_HW_BIT_RATE_1MBPS   = BIT(0),
	CONF_HW_BIT_RATE_2MBPS   = BIT(1),
	CONF_HW_BIT_RATE_5_5MBPS = BIT(2),
	CONF_HW_BIT_RATE_6MBPS   = BIT(3),
	CONF_HW_BIT_RATE_9MBPS   = BIT(4),
	CONF_HW_BIT_RATE_11MBPS  = BIT(5),
	CONF_HW_BIT_RATE_12MBPS  = BIT(6),
	CONF_HW_BIT_RATE_18MBPS  = BIT(7),
	CONF_HW_BIT_RATE_22MBPS  = BIT(8),
	CONF_HW_BIT_RATE_24MBPS  = BIT(9),
	CONF_HW_BIT_RATE_36MBPS  = BIT(10),
	CONF_HW_BIT_RATE_48MBPS  = BIT(11),
	CONF_HW_BIT_RATE_54MBPS  = BIT(12),
	CONF_HW_BIT_RATE_MCS_0   = BIT(13),
	CONF_HW_BIT_RATE_MCS_1   = BIT(14),
	CONF_HW_BIT_RATE_MCS_2   = BIT(15),
	CONF_HW_BIT_RATE_MCS_3   = BIT(16),
	CONF_HW_BIT_RATE_MCS_4   = BIT(17),
	CONF_HW_BIT_RATE_MCS_5   = BIT(18),
	CONF_HW_BIT_RATE_MCS_6   = BIT(19),
	CONF_HW_BIT_RATE_MCS_7   = BIT(20),
	CONF_HW_BIT_RATE_MCS_8   = BIT(21),
	CONF_HW_BIT_RATE_MCS_9   = BIT(22),
	CONF_HW_BIT_RATE_MCS_10  = BIT(23),
	CONF_HW_BIT_RATE_MCS_11  = BIT(24),
	CONF_HW_BIT_RATE_MCS_12  = BIT(25),
	CONF_HW_BIT_RATE_MCS_13  = BIT(26),
	CONF_HW_BIT_RATE_MCS_14  = BIT(27),
	CONF_HW_BIT_RATE_MCS_15  = BIT(28),
पूर्ण;

क्रमागत अणु
	CONF_HW_RATE_INDEX_1MBPS      = 0,
	CONF_HW_RATE_INDEX_2MBPS      = 1,
	CONF_HW_RATE_INDEX_5_5MBPS    = 2,
	CONF_HW_RATE_INDEX_11MBPS     = 3,
	CONF_HW_RATE_INDEX_6MBPS      = 4,
	CONF_HW_RATE_INDEX_9MBPS      = 5,
	CONF_HW_RATE_INDEX_12MBPS     = 6,
	CONF_HW_RATE_INDEX_18MBPS     = 7,
	CONF_HW_RATE_INDEX_24MBPS     = 8,
	CONF_HW_RATE_INDEX_36MBPS     = 9,
	CONF_HW_RATE_INDEX_48MBPS     = 10,
	CONF_HW_RATE_INDEX_54MBPS     = 11,
	CONF_HW_RATE_INDEX_MCS0       = 12,
	CONF_HW_RATE_INDEX_MCS1       = 13,
	CONF_HW_RATE_INDEX_MCS2       = 14,
	CONF_HW_RATE_INDEX_MCS3       = 15,
	CONF_HW_RATE_INDEX_MCS4       = 16,
	CONF_HW_RATE_INDEX_MCS5       = 17,
	CONF_HW_RATE_INDEX_MCS6       = 18,
	CONF_HW_RATE_INDEX_MCS7       = 19,
	CONF_HW_RATE_INDEX_MCS7_SGI   = 20,
	CONF_HW_RATE_INDEX_MCS0_40MHZ = 21,
	CONF_HW_RATE_INDEX_MCS1_40MHZ = 22,
	CONF_HW_RATE_INDEX_MCS2_40MHZ = 23,
	CONF_HW_RATE_INDEX_MCS3_40MHZ = 24,
	CONF_HW_RATE_INDEX_MCS4_40MHZ = 25,
	CONF_HW_RATE_INDEX_MCS5_40MHZ = 26,
	CONF_HW_RATE_INDEX_MCS6_40MHZ = 27,
	CONF_HW_RATE_INDEX_MCS7_40MHZ = 28,
	CONF_HW_RATE_INDEX_MCS7_40MHZ_SGI = 29,

	/* MCS8+ rates overlap with 40Mhz rates */
	CONF_HW_RATE_INDEX_MCS8       = 21,
	CONF_HW_RATE_INDEX_MCS9       = 22,
	CONF_HW_RATE_INDEX_MCS10      = 23,
	CONF_HW_RATE_INDEX_MCS11      = 24,
	CONF_HW_RATE_INDEX_MCS12      = 25,
	CONF_HW_RATE_INDEX_MCS13      = 26,
	CONF_HW_RATE_INDEX_MCS14      = 27,
	CONF_HW_RATE_INDEX_MCS15      = 28,
	CONF_HW_RATE_INDEX_MCS15_SGI  = 29,

	CONF_HW_RATE_INDEX_MAX        = CONF_HW_RATE_INDEX_MCS7_40MHZ_SGI,
पूर्ण;

#घोषणा CONF_HW_RXTX_RATE_UNSUPPORTED 0xff

क्रमागत अणु
	CONF_SG_DISABLE = 0,
	CONF_SG_PROTECTIVE,
	CONF_SG_OPPORTUNISTIC
पूर्ण;

#घोषणा WLCORE_CONF_SG_PARAMS_MAX 67
#घोषणा WLCORE_CONF_SG_PARAMS_ALL 0xff

काष्ठा conf_sg_settings अणु
	u32 params[WLCORE_CONF_SG_PARAMS_MAX];
	u8 state;
पूर्ण __packed;

क्रमागत conf_rx_queue_type अणु
	CONF_RX_QUEUE_TYPE_LOW_PRIORITY,  /* All except the high priority */
	CONF_RX_QUEUE_TYPE_HIGH_PRIORITY, /* Management and voice packets */
पूर्ण;

काष्ठा conf_rx_settings अणु
	/*
	 * The maximum amount of समय, in TU, beक्रमe the
	 * firmware discards the MSDU.
	 *
	 * Range: 0 - 0xFFFFFFFF
	 */
	u32 rx_msdu_lअगरe_समय;

	/*
	 * Packet detection threshold in the PHY.
	 *
	 * FIXME: details unknown.
	 */
	u32 packet_detection_threshold;

	/*
	 * The दीर्घest समय the STA will रुको to receive traffic from the AP
	 * after a PS-poll has been transmitted.
	 *
	 * Range: 0 - 200000
	 */
	u16 ps_poll_समयout;
	/*
	 * The दीर्घest समय the STA will रुको to receive traffic from the AP
	 * after a frame has been sent from an UPSD enabled queue.
	 *
	 * Range: 0 - 200000
	 */
	u16 upsd_समयout;

	/*
	 * The number of octets in an MPDU, below which an RTS/CTS
	 * handshake is not perक्रमmed.
	 *
	 * Range: 0 - 4096
	 */
	u16 rts_threshold;

	/*
	 * The RX Clear Channel Assessment threshold in the PHY
	 * (the energy threshold).
	 *
	 * Range: ENABLE_ENERGY_D  == 0x140A
	 *        DISABLE_ENERGY_D == 0xFFEF
	 */
	u16 rx_cca_threshold;

	/*
	 * Occupied Rx mem-blocks number which requires पूर्णांकerrupting the host
	 * (0 = no buffering, 0xffff = disabled).
	 *
	 * Range: u16
	 */
	u16 irq_blk_threshold;

	/*
	 * Rx packets number which requires पूर्णांकerrupting the host
	 * (0 = no buffering).
	 *
	 * Range: u16
	 */
	u16 irq_pkt_threshold;

	/*
	 * Max समय in msec the FW may delay RX-Complete पूर्णांकerrupt.
	 *
	 * Range: 1 - 100
	 */
	u16 irq_समयout;

	/*
	 * The RX queue type.
	 *
	 * Range: RX_QUEUE_TYPE_RX_LOW_PRIORITY, RX_QUEUE_TYPE_RX_HIGH_PRIORITY,
	 */
	u8 queue_type;
पूर्ण __packed;

#घोषणा CONF_TX_MAX_RATE_CLASSES       10

#घोषणा CONF_TX_RATE_MASK_UNSPECIFIED  0
#घोषणा CONF_TX_RATE_MASK_BASIC        (CONF_HW_BIT_RATE_1MBPS | \
					CONF_HW_BIT_RATE_2MBPS)
#घोषणा CONF_TX_RATE_RETRY_LIMIT       10

/* basic rates क्रम p2p operations (probe req/resp, etc.) */
#घोषणा CONF_TX_RATE_MASK_BASIC_P2P    CONF_HW_BIT_RATE_6MBPS

/*
 * Rates supported क्रम data packets when operating as STA/AP. Note the असलence
 * of the 22Mbps rate. There is a FW limitation on 12 rates so we must drop
 * one. The rate dropped is not mandatory under any operating mode.
 */
#घोषणा CONF_TX_ENABLED_RATES       (CONF_HW_BIT_RATE_1MBPS |    \
	CONF_HW_BIT_RATE_2MBPS | CONF_HW_BIT_RATE_5_5MBPS |      \
	CONF_HW_BIT_RATE_6MBPS | CONF_HW_BIT_RATE_9MBPS |        \
	CONF_HW_BIT_RATE_11MBPS | CONF_HW_BIT_RATE_12MBPS |      \
	CONF_HW_BIT_RATE_18MBPS | CONF_HW_BIT_RATE_24MBPS |      \
	CONF_HW_BIT_RATE_36MBPS | CONF_HW_BIT_RATE_48MBPS |      \
	CONF_HW_BIT_RATE_54MBPS)

#घोषणा CONF_TX_CCK_RATES  (CONF_HW_BIT_RATE_1MBPS |		\
	CONF_HW_BIT_RATE_2MBPS | CONF_HW_BIT_RATE_5_5MBPS |	\
	CONF_HW_BIT_RATE_11MBPS)

#घोषणा CONF_TX_OFDM_RATES (CONF_HW_BIT_RATE_6MBPS |             \
	CONF_HW_BIT_RATE_12MBPS | CONF_HW_BIT_RATE_24MBPS |      \
	CONF_HW_BIT_RATE_36MBPS | CONF_HW_BIT_RATE_48MBPS |      \
	CONF_HW_BIT_RATE_54MBPS)

#घोषणा CONF_TX_MCS_RATES (CONF_HW_BIT_RATE_MCS_0 |              \
	CONF_HW_BIT_RATE_MCS_1 | CONF_HW_BIT_RATE_MCS_2 |        \
	CONF_HW_BIT_RATE_MCS_3 | CONF_HW_BIT_RATE_MCS_4 |        \
	CONF_HW_BIT_RATE_MCS_5 | CONF_HW_BIT_RATE_MCS_6 |        \
	CONF_HW_BIT_RATE_MCS_7)

#घोषणा CONF_TX_MIMO_RATES (CONF_HW_BIT_RATE_MCS_8 |             \
	CONF_HW_BIT_RATE_MCS_9 | CONF_HW_BIT_RATE_MCS_10 |       \
	CONF_HW_BIT_RATE_MCS_11 | CONF_HW_BIT_RATE_MCS_12 |      \
	CONF_HW_BIT_RATE_MCS_13 | CONF_HW_BIT_RATE_MCS_14 |      \
	CONF_HW_BIT_RATE_MCS_15)

/*
 * Default rates क्रम management traffic when operating in AP mode. This
 * should be configured according to the basic rate set of the AP
 */
#घोषणा CONF_TX_AP_DEFAULT_MGMT_RATES  (CONF_HW_BIT_RATE_1MBPS | \
	CONF_HW_BIT_RATE_2MBPS | CONF_HW_BIT_RATE_5_5MBPS)

/* शेष rates क्रम working as IBSS (11b and OFDM) */
#घोषणा CONF_TX_IBSS_DEFAULT_RATES  (CONF_HW_BIT_RATE_1MBPS |       \
		CONF_HW_BIT_RATE_2MBPS | CONF_HW_BIT_RATE_5_5MBPS | \
		CONF_HW_BIT_RATE_11MBPS | CONF_TX_OFDM_RATES);

काष्ठा conf_tx_rate_class अणु

	/*
	 * The rates enabled क्रम this rate class.
	 *
	 * Range: CONF_HW_BIT_RATE_* bit mask
	 */
	u32 enabled_rates;

	/*
	 * The करोt11 लघु retry limit used क्रम TX retries.
	 *
	 * Range: u8
	 */
	u8 लघु_retry_limit;

	/*
	 * The करोt11 दीर्घ retry limit used क्रम TX retries.
	 *
	 * Range: u8
	 */
	u8 दीर्घ_retry_limit;

	/*
	 * Flags controlling the attributes of TX transmission.
	 *
	 * Range: bit 0: Truncate - when set, FW attempts to send a frame stop
	 *               when the total valid per-rate attempts have
	 *               been exhausted; otherwise transmissions
	 *               will जारी at the lowest available rate
	 *               until the appropriate one of the
	 *               लघु_retry_limit, दीर्घ_retry_limit,
	 *               करोt11_max_transmit_msdu_lअगरe_समय, or
	 *               max_tx_lअगरe_समय, is exhausted.
	 *            1: Preamble Override - indicates अगर the preamble type
	 *               should be used in TX.
	 *            2: Preamble Type - the type of the preamble to be used by
	 *               the policy (0 - दीर्घ preamble, 1 - लघु preamble.
	 */
	u8 aflags;
पूर्ण __packed;

#घोषणा CONF_TX_MAX_AC_COUNT 4

/* Slot number setting to start transmission at PIFS पूर्णांकerval */
#घोषणा CONF_TX_AIFS_PIFS 1
/* Slot number setting to start transmission at DIFS पूर्णांकerval normal
 * DCF access */
#घोषणा CONF_TX_AIFS_DIFS 2


क्रमागत conf_tx_ac अणु
	CONF_TX_AC_BE = 0,         /* best efक्रमt / legacy */
	CONF_TX_AC_BK = 1,         /* background */
	CONF_TX_AC_VI = 2,         /* video */
	CONF_TX_AC_VO = 3,         /* voice */
	CONF_TX_AC_CTS2SELF = 4,   /* fictitious AC, follows AC_VO */
	CONF_TX_AC_ANY_TID = 0xff
पूर्ण;

काष्ठा conf_tx_ac_category अणु
	/*
	 * The AC class identअगरier.
	 *
	 * Range: क्रमागत conf_tx_ac
	 */
	u8 ac;

	/*
	 * The contention winकरोw minimum size (in slots) क्रम the access
	 * class.
	 *
	 * Range: u8
	 */
	u8 cw_min;

	/*
	 * The contention winकरोw maximum size (in slots) क्रम the access
	 * class.
	 *
	 * Range: u8
	 */
	u16 cw_max;

	/*
	 * The AIF value (in slots) क्रम the access class.
	 *
	 * Range: u8
	 */
	u8 aअगरsn;

	/*
	 * The TX Op Limit (in microseconds) क्रम the access class.
	 *
	 * Range: u16
	 */
	u16 tx_op_limit;
पूर्ण __packed;

#घोषणा CONF_TX_MAX_TID_COUNT 8

/* Allow TX BA on all TIDs but 6,7. These are currently reserved in the FW */
#घोषणा CONF_TX_BA_ENABLED_TID_BITMAP 0x3F

क्रमागत अणु
	CONF_CHANNEL_TYPE_DCF = 0,   /* DC/LEGACY*/
	CONF_CHANNEL_TYPE_EDCF = 1,  /* EDCA*/
	CONF_CHANNEL_TYPE_HCCA = 2,  /* HCCA*/
पूर्ण;

क्रमागत अणु
	CONF_PS_SCHEME_LEGACY = 0,
	CONF_PS_SCHEME_UPSD_TRIGGER = 1,
	CONF_PS_SCHEME_LEGACY_PSPOLL = 2,
	CONF_PS_SCHEME_SAPSD = 3,
पूर्ण;

क्रमागत अणु
	CONF_ACK_POLICY_LEGACY = 0,
	CONF_ACK_POLICY_NO_ACK = 1,
	CONF_ACK_POLICY_BLOCK = 2,
पूर्ण;


काष्ठा conf_tx_tid अणु
	u8 queue_id;
	u8 channel_type;
	u8 tsid;
	u8 ps_scheme;
	u8 ack_policy;
	u32 apsd_conf[2];
पूर्ण __packed;

काष्ठा conf_tx_settings अणु
	/*
	 * The TX ED value क्रम TELEC Enable/Disable.
	 *
	 * Range: 0, 1
	 */
	u8 tx_energy_detection;

	/*
	 * Configuration क्रम rate classes क्रम TX (currently only one
	 * rate class supported). Used in non-AP mode.
	 */
	काष्ठा conf_tx_rate_class sta_rc_conf;

	/*
	 * Configuration क्रम access categories क्रम TX rate control.
	 */
	u8 ac_conf_count;
	काष्ठा conf_tx_ac_category ac_conf[CONF_TX_MAX_AC_COUNT];

	/*
	 * AP-mode - allow this number of TX retries to a station beक्रमe an
	 * event is triggered from FW.
	 * In AP-mode the hlids of unreachable stations are given in the
	 * "sta_tx_retry_exceeded" member in the event mailbox.
	 */
	u8 max_tx_retries;

	/*
	 * AP-mode - after this number of seconds a connected station is
	 * considered inactive.
	 */
	u16 ap_aging_period;

	/*
	 * Configuration क्रम TID parameters.
	 */
	u8 tid_conf_count;
	काष्ठा conf_tx_tid tid_conf[CONF_TX_MAX_TID_COUNT];

	/*
	 * The TX fragmentation threshold.
	 *
	 * Range: u16
	 */
	u16 frag_threshold;

	/*
	 * Max समय in msec the FW may delay frame TX-Complete पूर्णांकerrupt.
	 *
	 * Range: u16
	 */
	u16 tx_compl_समयout;

	/*
	 * Completed TX packet count which requires to issue the TX-Complete
	 * पूर्णांकerrupt.
	 *
	 * Range: u16
	 */
	u16 tx_compl_threshold;

	/*
	 * The rate used क्रम control messages and scanning on the 2.4GHz band
	 *
	 * Range: CONF_HW_BIT_RATE_* bit mask
	 */
	u32 basic_rate;

	/*
	 * The rate used क्रम control messages and scanning on the 5GHz band
	 *
	 * Range: CONF_HW_BIT_RATE_* bit mask
	 */
	u32 basic_rate_5;

	/*
	 * TX retry limits क्रम ढाँचाs
	 */
	u8 पंचांगpl_लघु_retry_limit;
	u8 पंचांगpl_दीर्घ_retry_limit;

	/* Time in ms क्रम Tx watchकरोg समयr to expire */
	u32 tx_watchकरोg_समयout;

	/*
	 * when a slow link has this much packets pending, it becomes a low
	 * priority link, scheduling-wise
	 */
	u8 slow_link_thold;

	/*
	 * when a fast link has this much packets pending, it becomes a low
	 * priority link, scheduling-wise
	 */
	u8 fast_link_thold;
पूर्ण __packed;

क्रमागत अणु
	CONF_WAKE_UP_EVENT_BEACON    = 0x01, /* Wake on every Beacon*/
	CONF_WAKE_UP_EVENT_DTIM      = 0x02, /* Wake on every DTIM*/
	CONF_WAKE_UP_EVENT_N_DTIM    = 0x04, /* Wake every Nth DTIM */
	CONF_WAKE_UP_EVENT_N_BEACONS = 0x08, /* Wake every Nth beacon */
	CONF_WAKE_UP_EVENT_BITS_MASK = 0x0F
पूर्ण;

#घोषणा CONF_MAX_BCN_FILT_IE_COUNT 32

#घोषणा CONF_BCN_RULE_PASS_ON_CHANGE         BIT(0)
#घोषणा CONF_BCN_RULE_PASS_ON_APPEARANCE     BIT(1)

#घोषणा CONF_BCN_IE_OUI_LEN    3
#घोषणा CONF_BCN_IE_VER_LEN    2

काष्ठा conf_bcn_filt_rule अणु
	/*
	 * IE number to which to associate a rule.
	 *
	 * Range: u8
	 */
	u8 ie;

	/*
	 * Rule to associate with the specअगरic ie.
	 *
	 * Range: CONF_BCN_RULE_PASS_ON_*
	 */
	u8 rule;

	/*
	 * OUI क्रम the venकरोr specअगरie IE (221)
	 */
	u8 oui[CONF_BCN_IE_OUI_LEN];

	/*
	 * Type क्रम the venकरोr specअगरie IE (221)
	 */
	u8 type;

	/*
	 * Version क्रम the venकरोr specअगरie IE (221)
	 */
	u8 version[CONF_BCN_IE_VER_LEN];
पूर्ण __packed;

#घोषणा CONF_MAX_RSSI_SNR_TRIGGERS 8

क्रमागत अणु
	CONF_TRIG_METRIC_RSSI_BEACON = 0,
	CONF_TRIG_METRIC_RSSI_DATA,
	CONF_TRIG_METRIC_SNR_BEACON,
	CONF_TRIG_METRIC_SNR_DATA
पूर्ण;

क्रमागत अणु
	CONF_TRIG_EVENT_TYPE_LEVEL = 0,
	CONF_TRIG_EVENT_TYPE_EDGE
पूर्ण;

क्रमागत अणु
	CONF_TRIG_EVENT_सूची_LOW = 0,
	CONF_TRIG_EVENT_सूची_HIGH,
	CONF_TRIG_EVENT_सूची_BIसूची
पूर्ण;

काष्ठा conf_sig_weights अणु

	/*
	 * RSSI from beacons average weight.
	 *
	 * Range: u8
	 */
	u8 rssi_bcn_avg_weight;

	/*
	 * RSSI from data average weight.
	 *
	 * Range: u8
	 */
	u8 rssi_pkt_avg_weight;

	/*
	 * SNR from beacons average weight.
	 *
	 * Range: u8
	 */
	u8 snr_bcn_avg_weight;

	/*
	 * SNR from data average weight.
	 *
	 * Range: u8
	 */
	u8 snr_pkt_avg_weight;
पूर्ण __packed;

क्रमागत conf_bcn_filt_mode अणु
	CONF_BCN_FILT_MODE_DISABLED = 0,
	CONF_BCN_FILT_MODE_ENABLED = 1
पूर्ण;

क्रमागत conf_bet_mode अणु
	CONF_BET_MODE_DISABLE = 0,
	CONF_BET_MODE_ENABLE = 1,
पूर्ण;

काष्ठा conf_conn_settings अणु
	/*
	 * Firmware wakeup conditions configuration. The host may set only
	 * one bit.
	 *
	 * Range: CONF_WAKE_UP_EVENT_*
	 */
	u8 wake_up_event;

	/*
	 * Listen पूर्णांकerval क्रम beacons or Dtims.
	 *
	 * Range: 0 क्रम beacon and Dtim wakeup
	 *        1-10 क्रम x Dtims
	 *        1-255 क्रम x beacons
	 */
	u8 listen_पूर्णांकerval;

	/*
	 * Firmware wakeup conditions during suspend
	 * Range: CONF_WAKE_UP_EVENT_*
	 */
	u8 suspend_wake_up_event;

	/*
	 * Listen पूर्णांकerval during suspend.
	 * Currently will be in DTIMs (1-10)
	 *
	 */
	u8 suspend_listen_पूर्णांकerval;

	/*
	 * Enable or disable the beacon filtering.
	 *
	 * Range: CONF_BCN_FILT_MODE_*
	 */
	u8 bcn_filt_mode;

	/*
	 * Configure Beacon filter pass-thru rules.
	 */
	u8 bcn_filt_ie_count;
	काष्ठा conf_bcn_filt_rule bcn_filt_ie[CONF_MAX_BCN_FILT_IE_COUNT];

	/*
	 * The number of consecutive beacons to lose, beक्रमe the firmware
	 * becomes out of synch.
	 *
	 * Range: u32
	 */
	u32 synch_fail_thold;

	/*
	 * After out-of-synch, the number of TU's to रुको without a further
	 * received beacon (or probe response) beक्रमe issuing the BSS_EVENT_LOSE
	 * event.
	 *
	 * Range: u32
	 */
	u32 bss_lose_समयout;

	/*
	 * Beacon receive समयout.
	 *
	 * Range: u32
	 */
	u32 beacon_rx_समयout;

	/*
	 * Broadcast receive समयout.
	 *
	 * Range: u32
	 */
	u32 broadcast_समयout;

	/*
	 * Enable/disable reception of broadcast packets in घातer save mode
	 *
	 * Range: 1 - enable, 0 - disable
	 */
	u8 rx_broadcast_in_ps;

	/*
	 * Consecutive PS Poll failures beक्रमe sending event to driver
	 *
	 * Range: u8
	 */
	u8 ps_poll_threshold;

	/*
	 * Configuration of संकेत average weights.
	 */
	काष्ठा conf_sig_weights sig_weights;

	/*
	 * Specअगरies अगर beacon early termination procedure is enabled or
	 * disabled.
	 *
	 * Range: CONF_BET_MODE_*
	 */
	u8 bet_enable;

	/*
	 * Specअगरies the maximum number of consecutive beacons that may be
	 * early terminated. After this number is reached at least one full
	 * beacon must be correctly received in FW beक्रमe beacon ET
	 * resumes.
	 *
	 * Range 0 - 255
	 */
	u8 bet_max_consecutive;

	/*
	 * Specअगरies the maximum number of बार to try PSM entry अगर it fails
	 * (अगर sending the appropriate null-func message fails.)
	 *
	 * Range 0 - 255
	 */
	u8 psm_entry_retries;

	/*
	 * Specअगरies the maximum number of बार to try PSM निकास अगर it fails
	 * (अगर sending the appropriate null-func message fails.)
	 *
	 * Range 0 - 255
	 */
	u8 psm_निकास_retries;

	/*
	 * Specअगरies the maximum number of बार to try transmit the PSM entry
	 * null-func frame क्रम each PSM entry attempt
	 *
	 * Range 0 - 255
	 */
	u8 psm_entry_nullfunc_retries;

	/*
	 * Specअगरies the dynamic PS समयout in ms that will be used
	 * by the FW when in AUTO_PS mode
	 */
	u16 dynamic_ps_समयout;

	/*
	 * Specअगरies whether dynamic PS should be disabled and PSM क्रमced.
	 * This is required क्रम certain WiFi certअगरication tests.
	 */
	u8 क्रमced_ps;

	/*
	 *
	 * Specअगरies the पूर्णांकerval of the connection keep-alive null-func
	 * frame in ms.
	 *
	 * Range: 1000 - 3600000
	 */
	u32 keep_alive_पूर्णांकerval;

	/*
	 * Maximum listen पूर्णांकerval supported by the driver in units of beacons.
	 *
	 * Range: u16
	 */
	u8 max_listen_पूर्णांकerval;

	/*
	 * Default sleep authorization क्रम a new STA पूर्णांकerface. This determines
	 * whether we can go to ELP.
	 */
	u8 sta_sleep_auth;

	/*
	 * Default RX BA Activity filter configuration
	 */
	u8 suspend_rx_ba_activity;
पूर्ण __packed;

क्रमागत अणु
	CONF_REF_CLK_19_2_E,
	CONF_REF_CLK_26_E,
	CONF_REF_CLK_38_4_E,
	CONF_REF_CLK_52_E,
	CONF_REF_CLK_38_4_M_XTAL,
	CONF_REF_CLK_26_M_XTAL,
पूर्ण;

क्रमागत single_dual_band_क्रमागत अणु
	CONF_SINGLE_BAND,
	CONF_DUAL_BAND
पूर्ण;

#घोषणा CONF_RSSI_AND_PROCESS_COMPENSATION_SIZE 15
#घोषणा CONF_NUMBER_OF_SUB_BANDS_5  7
#घोषणा CONF_NUMBER_OF_RATE_GROUPS  6
#घोषणा CONF_NUMBER_OF_CHANNELS_2_4 14
#घोषणा CONF_NUMBER_OF_CHANNELS_5   35

काष्ठा conf_itrim_settings अणु
	/* enable dco itrim */
	u8 enable;

	/* moderation समयout in microsecs from the last TX */
	u32 समयout;
पूर्ण __packed;

क्रमागत conf_fast_wakeup अणु
	CONF_FAST_WAKEUP_ENABLE,
	CONF_FAST_WAKEUP_DISABLE,
पूर्ण;

काष्ठा conf_pm_config_settings अणु
	/*
	 * Host घड़ी settling समय
	 *
	 * Range: 0 - 30000 us
	 */
	u32 host_clk_settling_समय;

	/*
	 * Host fast wakeup support
	 *
	 * Range: क्रमागत conf_fast_wakeup
	 */
	u8 host_fast_wakeup_support;
पूर्ण __packed;

काष्ठा conf_roam_trigger_settings अणु
	/*
	 * The minimum पूर्णांकerval between two trigger events.
	 *
	 * Range: 0 - 60000 ms
	 */
	u16 trigger_pacing;

	/*
	 * The weight क्रम rssi/beacon average calculation
	 *
	 * Range: 0 - 255
	 */
	u8 avg_weight_rssi_beacon;

	/*
	 * The weight क्रम rssi/data frame average calculation
	 *
	 * Range: 0 - 255
	 */
	u8 avg_weight_rssi_data;

	/*
	 * The weight क्रम snr/beacon average calculation
	 *
	 * Range: 0 - 255
	 */
	u8 avg_weight_snr_beacon;

	/*
	 * The weight क्रम snr/data frame average calculation
	 *
	 * Range: 0 - 255
	 */
	u8 avg_weight_snr_data;
पूर्ण __packed;

काष्ठा conf_scan_settings अणु
	/*
	 * The minimum समय to रुको on each channel क्रम active scans
	 * This value will be used whenever there's a connected पूर्णांकerface.
	 *
	 * Range: u32 tu/1000
	 */
	u32 min_dwell_समय_active;

	/*
	 * The maximum समय to रुको on each channel क्रम active scans
	 * This value will be currently used whenever there's a
	 * connected पूर्णांकerface. It shouldn't exceed 30000 (~30ms) to aव्योम
	 * possible पूर्णांकerference of voip traffic going on जबतक scanning.
	 *
	 * Range: u32 tu/1000
	 */
	u32 max_dwell_समय_active;

	/* The minimum समय to रुको on each channel क्रम active scans
	 * when it's possible to have दीर्घer scan dwell बार.
	 * Currently this is used whenever we're idle on all पूर्णांकerfaces.
	 * Longer dwell बार improve detection of networks within a
	 * single scan.
	 *
	 * Range: u32 tu/1000
	 */
	u32 min_dwell_समय_active_दीर्घ;

	/* The maximum समय to रुको on each channel क्रम active scans
	 * when it's possible to have दीर्घer scan dwell बार.
	 * See min_dwell_समय_active_दीर्घ
	 *
	 * Range: u32 tu/1000
	 */
	u32 max_dwell_समय_active_दीर्घ;

	/* समय to रुको on the channel क्रम passive scans (in TU/1000) */
	u32 dwell_समय_passive;

	/* समय to रुको on the channel क्रम DFS scans (in TU/1000) */
	u32 dwell_समय_dfs;

	/*
	 * Number of probe requests to transmit on each active scan channel
	 *
	 * Range: u8
	 */
	u16 num_probe_reqs;

	/*
	 * Scan trigger (split scan) समयout. The FW will split the scan
	 * operation पूर्णांकo slices of the given समय and allow the FW to schedule
	 * other tasks in between.
	 *
	 * Range: u32 Microsecs
	 */
	u32 split_scan_समयout;
पूर्ण __packed;

काष्ठा conf_sched_scan_settings अणु
	/*
	 * The base समय to रुको on the channel क्रम active scans (in TU/1000).
	 * The minimum dwell समय is calculated according to this:
	 * min_dwell_समय = base + num_of_probes_to_be_sent * delta_per_probe
	 * The maximum dwell समय is calculated according to this:
	 * max_dwell_समय = min_dwell_समय + max_dwell_समय_delta
	 */
	u32 base_dwell_समय;

	/* The delta between the min dwell समय and max dwell समय क्रम
	 * active scans (in TU/1000s). The max dwell समय is used by the FW once
	 * traffic is detected on the channel.
	 */
	u32 max_dwell_समय_delta;

	/* Delta added to min dwell समय per each probe in 2.4 GHz (TU/1000) */
	u32 dwell_समय_delta_per_probe;

	/* Delta added to min dwell समय per each probe in 5 GHz (TU/1000) */
	u32 dwell_समय_delta_per_probe_5;

	/* समय to रुको on the channel क्रम passive scans (in TU/1000) */
	u32 dwell_समय_passive;

	/* समय to रुको on the channel क्रम DFS scans (in TU/1000) */
	u32 dwell_समय_dfs;

	/* number of probe requests to send on each channel in active scans */
	u8 num_probe_reqs;

	/* RSSI threshold to be used क्रम filtering */
	s8 rssi_threshold;

	/* SNR threshold to be used क्रम filtering */
	s8 snr_threshold;

	/*
	 * number of लघु पूर्णांकervals scheduled scan cycles beक्रमe
	 * चयनing to दीर्घ पूर्णांकervals
	 */
	u8 num_लघु_पूर्णांकervals;

	/* पूर्णांकerval between each दीर्घ scheduled scan cycle (in ms) */
	u16 दीर्घ_पूर्णांकerval;
पूर्ण __packed;

काष्ठा conf_ht_setting अणु
	u8 rx_ba_win_size;
	u8 tx_ba_win_size;
	u16 inactivity_समयout;

	/* biपंचांगap of enabled TIDs क्रम TX BA sessions */
	u8 tx_ba_tid_biपंचांगap;
पूर्ण __packed;

काष्ठा conf_memory_settings अणु
	/* Number of stations supported in IBSS mode */
	u8 num_stations;

	/* Number of ssid profiles used in IBSS mode */
	u8 ssid_profiles;

	/* Number of memory buffers allocated to rx pool */
	u8 rx_block_num;

	/* Minimum number of blocks allocated to tx pool */
	u8 tx_min_block_num;

	/* Disable/Enable dynamic memory */
	u8 dynamic_memory;

	/*
	 * Minimum required मुक्त tx memory blocks in order to assure optimum
	 * perक्रमmance
	 *
	 * Range: 0-120
	 */
	u8 min_req_tx_blocks;

	/*
	 * Minimum required मुक्त rx memory blocks in order to assure optimum
	 * perक्रमmance
	 *
	 * Range: 0-120
	 */
	u8 min_req_rx_blocks;

	/*
	 * Minimum number of mem blocks (मुक्त+used) guaranteed क्रम TX
	 *
	 * Range: 0-120
	 */
	u8 tx_min;
पूर्ण __packed;

काष्ठा conf_fm_coex अणु
	u8 enable;
	u8 swallow_period;
	u8 n_भागider_fref_set_1;
	u8 n_भागider_fref_set_2;
	u16 m_भागider_fref_set_1;
	u16 m_भागider_fref_set_2;
	u32 coex_pll_stabilization_समय;
	u16 lकरो_stabilization_समय;
	u8 fm_disturbed_band_margin;
	u8 swallow_clk_dअगरf;
पूर्ण __packed;

काष्ठा conf_rx_streaming_settings अणु
	/*
	 * RX Streaming duration (in msec) from last tx/rx
	 *
	 * Range: u32
	 */
	u32 duration;

	/*
	 * Biपंचांगap of tids to be polled during RX streaming.
	 * (Note: it करोesn't look like it really matters)
	 *
	 * Range: 0x1-0xff
	 */
	u8 queues;

	/*
	 * RX Streaming पूर्णांकerval.
	 * (Note:this value is also used as the rx streaming समयout)
	 * Range: 0 (disabled), 10 - 100
	 */
	u8 पूर्णांकerval;

	/*
	 * enable rx streaming also when there is no coex activity
	 */
	u8 always;
पूर्ण __packed;

#घोषणा CONF_FWLOG_MIN_MEM_BLOCKS	2
#घोषणा CONF_FWLOG_MAX_MEM_BLOCKS	16

काष्ठा conf_fwlog अणु
	/* Continuous or on-demand */
	u8 mode;

	/*
	 * Number of memory blocks dedicated क्रम the FW logger
	 *
	 * Range: 2-16, or 0 to disable the FW logger
	 */
	u8 mem_blocks;

	/* Minimum log level threshold */
	u8 severity;

	/* Include/exclude बारtamps from the log messages */
	u8 बारtamp;

	/* See क्रमागत wl1271_fwlogger_output */
	u8 output;

	/* Regulates the frequency of log messages */
	u8 threshold;
पूर्ण __packed;

#घोषणा ACX_RATE_MGMT_NUM_OF_RATES 13
काष्ठा conf_rate_policy_settings अणु
	u16 rate_retry_score;
	u16 per_add;
	u16 per_th1;
	u16 per_th2;
	u16 max_per;
	u8 inverse_curiosity_factor;
	u8 tx_fail_low_th;
	u8 tx_fail_high_th;
	u8 per_alpha_shअगरt;
	u8 per_add_shअगरt;
	u8 per_beta1_shअगरt;
	u8 per_beta2_shअगरt;
	u8 rate_check_up;
	u8 rate_check_करोwn;
	u8 rate_retry_policy[ACX_RATE_MGMT_NUM_OF_RATES];
पूर्ण __packed;

काष्ठा conf_hangover_settings अणु
	u32 recover_समय;
	u8 hangover_period;
	u8 dynamic_mode;
	u8 early_termination_mode;
	u8 max_period;
	u8 min_period;
	u8 increase_delta;
	u8 decrease_delta;
	u8 quiet_समय;
	u8 increase_समय;
	u8 winकरोw_size;
पूर्ण __packed;

काष्ठा conf_recovery_settings अणु
	/* BUG() on fw recovery */
	u8 bug_on_recovery;

	/* Prevent HW recovery. FW will reमुख्य stuck. */
	u8 no_recovery;
पूर्ण __packed;

/*
 * The conf version consists of 4 bytes.  The two MSB are the wlcore
 * version, the two LSB are the lower driver's निजी conf
 * version.
 */
#घोषणा WLCORE_CONF_VERSION	(0x0007 << 16)
#घोषणा WLCORE_CONF_MASK	0xffff0000
#घोषणा WLCORE_CONF_SIZE	(माप(काष्ठा wlcore_conf_header) +	\
				 माप(काष्ठा wlcore_conf))

काष्ठा wlcore_conf_header अणु
	__le32 magic;
	__le32 version;
	__le32 checksum;
पूर्ण __packed;

काष्ठा wlcore_conf अणु
	काष्ठा conf_sg_settings sg;
	काष्ठा conf_rx_settings rx;
	काष्ठा conf_tx_settings tx;
	काष्ठा conf_conn_settings conn;
	काष्ठा conf_itrim_settings itrim;
	काष्ठा conf_pm_config_settings pm_config;
	काष्ठा conf_roam_trigger_settings roam_trigger;
	काष्ठा conf_scan_settings scan;
	काष्ठा conf_sched_scan_settings sched_scan;
	काष्ठा conf_ht_setting ht;
	काष्ठा conf_memory_settings mem;
	काष्ठा conf_fm_coex fm_coex;
	काष्ठा conf_rx_streaming_settings rx_streaming;
	काष्ठा conf_fwlog fwlog;
	काष्ठा conf_rate_policy_settings rate;
	काष्ठा conf_hangover_settings hangover;
	काष्ठा conf_recovery_settings recovery;
पूर्ण __packed;

काष्ठा wlcore_conf_file अणु
	काष्ठा wlcore_conf_header header;
	काष्ठा wlcore_conf core;
	u8 priv[];
पूर्ण __packed;

#पूर्ण_अगर
