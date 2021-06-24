<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * mac80211 <-> driver पूर्णांकerface
 *
 * Copyright 2002-2005, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (C) 2015 - 2017 Intel Deutschland GmbH
 * Copyright (C) 2018 - 2020 Intel Corporation
 */

#अगर_अघोषित MAC80211_H
#घोषणा MAC80211_H

#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश <net/codel.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <यंत्र/unaligned.h>

/**
 * DOC: Introduction
 *
 * mac80211 is the Linux stack क्रम 802.11 hardware that implements
 * only partial functionality in hard- or firmware. This करोcument
 * defines the पूर्णांकerface between mac80211 and low-level hardware
 * drivers.
 */

/**
 * DOC: Calling mac80211 from पूर्णांकerrupts
 *
 * Only ieee80211_tx_status_irqsafe() and ieee80211_rx_irqsafe() can be
 * called in hardware पूर्णांकerrupt context. The low-level driver must not call any
 * other functions in hardware पूर्णांकerrupt context. If there is a need क्रम such
 * call, the low-level driver should first ACK the पूर्णांकerrupt and perक्रमm the
 * IEEE 802.11 code call after this, e.g. from a scheduled workqueue or even
 * tasklet function.
 *
 * NOTE: If the driver opts to use the _irqsafe() functions, it may not also
 *	 use the non-IRQ-safe functions!
 */

/**
 * DOC: Warning
 *
 * If you're पढ़ोing this करोcument and not the header file itself, it will
 * be incomplete because not all करोcumentation has been converted yet.
 */

/**
 * DOC: Frame क्रमmat
 *
 * As a general rule, when frames are passed between mac80211 and the driver,
 * they start with the IEEE 802.11 header and include the same octets that are
 * sent over the air except क्रम the FCS which should be calculated by the
 * hardware.
 *
 * There are, however, various exceptions to this rule क्रम advanced features:
 *
 * The first exception is क्रम hardware encryption and decryption offload
 * where the IV/ICV may or may not be generated in hardware.
 *
 * Secondly, when the hardware handles fragmentation, the frame handed to
 * the driver from mac80211 is the MSDU, not the MPDU.
 */

/**
 * DOC: mac80211 workqueue
 *
 * mac80211 provides its own workqueue क्रम drivers and पूर्णांकernal mac80211 use.
 * The workqueue is a single thपढ़ोed workqueue and can only be accessed by
 * helpers क्रम sanity checking. Drivers must ensure all work added onto the
 * mac80211 workqueue should be cancelled on the driver stop() callback.
 *
 * mac80211 will flushed the workqueue upon पूर्णांकerface removal and during
 * suspend.
 *
 * All work perक्रमmed on the mac80211 workqueue must not acquire the RTNL lock.
 *
 */

/**
 * DOC: mac80211 software tx queueing
 *
 * mac80211 provides an optional पूर्णांकermediate queueing implementation deचिन्हित
 * to allow the driver to keep hardware queues लघु and provide some fairness
 * between dअगरferent stations/पूर्णांकerfaces.
 * In this model, the driver pulls data frames from the mac80211 queue instead
 * of letting mac80211 push them via drv_tx().
 * Other frames (e.g. control or management) are still pushed using drv_tx().
 *
 * Drivers indicate that they use this model by implementing the .wake_tx_queue
 * driver operation.
 *
 * Intermediate queues (काष्ठा ieee80211_txq) are kept per-sta per-tid, with
 * another per-sta क्रम non-data/non-mgmt and bufferable management frames, and
 * a single per-vअगर queue क्रम multicast data frames.
 *
 * The driver is expected to initialize its निजी per-queue data क्रम stations
 * and पूर्णांकerfaces in the .add_पूर्णांकerface and .sta_add ops.
 *
 * The driver can't access the queue directly. To dequeue a frame from a
 * txq, it calls ieee80211_tx_dequeue(). Whenever mac80211 adds a new frame to a
 * queue, it calls the .wake_tx_queue driver op.
 *
 * Drivers can optionally delegate responsibility क्रम scheduling queues to
 * mac80211, to take advantage of airसमय fairness accounting. In this हाल, to
 * obtain the next queue to pull frames from, the driver calls
 * ieee80211_next_txq(). The driver is then expected to वापस the txq using
 * ieee80211_वापस_txq().
 *
 * For AP घातersave TIM handling, the driver only needs to indicate अगर it has
 * buffered packets in the driver specअगरic data काष्ठाures by calling
 * ieee80211_sta_set_buffered(). For frames buffered in the ieee80211_txq
 * काष्ठा, mac80211 sets the appropriate TIM PVB bits and calls
 * .release_buffered_frames().
 * In that callback the driver is thereक्रमe expected to release its own
 * buffered frames and afterwards also frames from the ieee80211_txq (obtained
 * via the usual ieee80211_tx_dequeue).
 */

काष्ठा device;

/**
 * क्रमागत ieee80211_max_queues - maximum number of queues
 *
 * @IEEE80211_MAX_QUEUES: Maximum number of regular device queues.
 * @IEEE80211_MAX_QUEUE_MAP: biपंचांगap with maximum queues set
 */
क्रमागत ieee80211_max_queues अणु
	IEEE80211_MAX_QUEUES =		16,
	IEEE80211_MAX_QUEUE_MAP =	BIT(IEEE80211_MAX_QUEUES) - 1,
पूर्ण;

#घोषणा IEEE80211_INVAL_HW_QUEUE	0xff

/**
 * क्रमागत ieee80211_ac_numbers - AC numbers as used in mac80211
 * @IEEE80211_AC_VO: voice
 * @IEEE80211_AC_VI: video
 * @IEEE80211_AC_BE: best efक्रमt
 * @IEEE80211_AC_BK: background
 */
क्रमागत ieee80211_ac_numbers अणु
	IEEE80211_AC_VO		= 0,
	IEEE80211_AC_VI		= 1,
	IEEE80211_AC_BE		= 2,
	IEEE80211_AC_BK		= 3,
पूर्ण;

/**
 * काष्ठा ieee80211_tx_queue_params - transmit queue configuration
 *
 * The inक्रमmation provided in this काष्ठाure is required क्रम QoS
 * transmit queue configuration. Cf. IEEE 802.11 7.3.2.29.
 *
 * @aअगरs: arbitration पूर्णांकerframe space [0..255]
 * @cw_min: minimum contention winकरोw [a value of the क्रमm
 *	2^n-1 in the range 1..32767]
 * @cw_max: maximum contention winकरोw [like @cw_min]
 * @txop: maximum burst समय in units of 32 usecs, 0 meaning disabled
 * @acm: is mandatory admission control required क्रम the access category
 * @uapsd: is U-APSD mode enabled क्रम the queue
 * @mu_edca: is the MU EDCA configured
 * @mu_edca_param_rec: MU EDCA Parameter Record क्रम HE
 */
काष्ठा ieee80211_tx_queue_params अणु
	u16 txop;
	u16 cw_min;
	u16 cw_max;
	u8 aअगरs;
	bool acm;
	bool uapsd;
	bool mu_edca;
	काष्ठा ieee80211_he_mu_edca_param_ac_rec mu_edca_param_rec;
पूर्ण;

काष्ठा ieee80211_low_level_stats अणु
	अचिन्हित पूर्णांक करोt11ACKFailureCount;
	अचिन्हित पूर्णांक करोt11RTSFailureCount;
	अचिन्हित पूर्णांक करोt11FCSErrorCount;
	अचिन्हित पूर्णांक करोt11RTSSuccessCount;
पूर्ण;

/**
 * क्रमागत ieee80211_chanctx_change - change flag क्रम channel context
 * @IEEE80211_CHANCTX_CHANGE_WIDTH: The channel width changed
 * @IEEE80211_CHANCTX_CHANGE_RX_CHAINS: The number of RX chains changed
 * @IEEE80211_CHANCTX_CHANGE_RADAR: radar detection flag changed
 * @IEEE80211_CHANCTX_CHANGE_CHANNEL: चयनed to another operating channel,
 *	this is used only with channel चयनing with CSA
 * @IEEE80211_CHANCTX_CHANGE_MIN_WIDTH: The min required channel width changed
 */
क्रमागत ieee80211_chanctx_change अणु
	IEEE80211_CHANCTX_CHANGE_WIDTH		= BIT(0),
	IEEE80211_CHANCTX_CHANGE_RX_CHAINS	= BIT(1),
	IEEE80211_CHANCTX_CHANGE_RADAR		= BIT(2),
	IEEE80211_CHANCTX_CHANGE_CHANNEL	= BIT(3),
	IEEE80211_CHANCTX_CHANGE_MIN_WIDTH	= BIT(4),
पूर्ण;

/**
 * काष्ठा ieee80211_chanctx_conf - channel context that vअगरs may be tuned to
 *
 * This is the driver-visible part. The ieee80211_chanctx
 * that contains it is visible in mac80211 only.
 *
 * @def: the channel definition
 * @min_def: the minimum channel definition currently required.
 * @rx_chains_अटल: The number of RX chains that must always be
 *	active on the channel to receive MIMO transmissions
 * @rx_chains_dynamic: The number of RX chains that must be enabled
 *	after RTS/CTS handshake to receive SMPS MIMO transmissions;
 *	this will always be >= @rx_chains_अटल.
 * @radar_enabled: whether radar detection is enabled on this channel.
 * @drv_priv: data area क्रम driver use, will always be aligned to
 *	माप(व्योम *), size is determined in hw inक्रमmation.
 */
काष्ठा ieee80211_chanctx_conf अणु
	काष्ठा cfg80211_chan_def def;
	काष्ठा cfg80211_chan_def min_def;

	u8 rx_chains_अटल, rx_chains_dynamic;

	bool radar_enabled;

	u8 drv_priv[] __aligned(माप(व्योम *));
पूर्ण;

/**
 * क्रमागत ieee80211_chanctx_चयन_mode - channel context चयन mode
 * @CHANCTX_SWMODE_REASSIGN_VIF: Both old and new contexts alपढ़ोy
 *	exist (and will जारी to exist), but the भव पूर्णांकerface
 *	needs to be चयनed from one to the other.
 * @CHANCTX_SWMODE_SWAP_CONTEXTS: The old context exists but will stop
 *      to exist with this call, the new context करोesn't exist but
 *      will be active after this call, the भव पूर्णांकerface चयनes
 *      from the old to the new (note that the driver may of course
 *      implement this as an on-the-fly chandef चयन of the existing
 *      hardware context, but the mac80211 poपूर्णांकer क्रम the old context
 *      will cease to exist and only the new one will later be used
 *      क्रम changes/removal.)
 */
क्रमागत ieee80211_chanctx_चयन_mode अणु
	CHANCTX_SWMODE_REASSIGN_VIF,
	CHANCTX_SWMODE_SWAP_CONTEXTS,
पूर्ण;

/**
 * काष्ठा ieee80211_vअगर_chanctx_चयन - vअगर chanctx चयन inक्रमmation
 *
 * This is काष्ठाure is used to pass inक्रमmation about a vअगर that
 * needs to चयन from one chanctx to another.  The
 * &ieee80211_chanctx_चयन_mode defines how the चयन should be
 * करोne.
 *
 * @vअगर: the vअगर that should be चयनed from old_ctx to new_ctx
 * @old_ctx: the old context to which the vअगर was asचिन्हित
 * @new_ctx: the new context to which the vअगर must be asचिन्हित
 */
काष्ठा ieee80211_vअगर_chanctx_चयन अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_chanctx_conf *old_ctx;
	काष्ठा ieee80211_chanctx_conf *new_ctx;
पूर्ण;

/**
 * क्रमागत ieee80211_bss_change - BSS change notअगरication flags
 *
 * These flags are used with the bss_info_changed() callback
 * to indicate which BSS parameter changed.
 *
 * @BSS_CHANGED_ASSOC: association status changed (associated/disassociated),
 *	also implies a change in the AID.
 * @BSS_CHANGED_ERP_CTS_PROT: CTS protection changed
 * @BSS_CHANGED_ERP_PREAMBLE: preamble changed
 * @BSS_CHANGED_ERP_SLOT: slot timing changed
 * @BSS_CHANGED_HT: 802.11n parameters changed
 * @BSS_CHANGED_BASIC_RATES: Basic rateset changed
 * @BSS_CHANGED_BEACON_INT: Beacon पूर्णांकerval changed
 * @BSS_CHANGED_BSSID: BSSID changed, क्रम whatever
 *	reason (IBSS and managed mode)
 * @BSS_CHANGED_BEACON: Beacon data changed, retrieve
 *	new beacon (beaconing modes)
 * @BSS_CHANGED_BEACON_ENABLED: Beaconing should be
 *	enabled/disabled (beaconing modes)
 * @BSS_CHANGED_CQM: Connection quality monitor config changed
 * @BSS_CHANGED_IBSS: IBSS join status changed
 * @BSS_CHANGED_ARP_FILTER: Hardware ARP filter address list or state changed.
 * @BSS_CHANGED_QOS: QoS क्रम this association was enabled/disabled. Note
 *	that it is only ever disabled क्रम station mode.
 * @BSS_CHANGED_IDLE: Idle changed क्रम this BSS/पूर्णांकerface.
 * @BSS_CHANGED_SSID: SSID changed क्रम this BSS (AP and IBSS mode)
 * @BSS_CHANGED_AP_PROBE_RESP: Probe Response changed क्रम this BSS (AP mode)
 * @BSS_CHANGED_PS: PS changed क्रम this BSS (STA mode)
 * @BSS_CHANGED_TXPOWER: TX घातer setting changed क्रम this पूर्णांकerface
 * @BSS_CHANGED_P2P_PS: P2P घातersave settings (CTWinकरोw, opportunistic PS)
 *	changed
 * @BSS_CHANGED_BEACON_INFO: Data from the AP's beacon became available:
 *	currently dtim_period only is under consideration.
 * @BSS_CHANGED_BANDWIDTH: The bandwidth used by this पूर्णांकerface changed,
 *	note that this is only called when it changes after the channel
 *	context had been asचिन्हित.
 * @BSS_CHANGED_OCB: OCB join status changed
 * @BSS_CHANGED_MU_GROUPS: VHT MU-MIMO group id or user position changed
 * @BSS_CHANGED_KEEP_ALIVE: keep alive options (idle period or रक्षित
 *	keep alive) changed.
 * @BSS_CHANGED_MCAST_RATE: Multicast Rate setting changed क्रम this पूर्णांकerface
 * @BSS_CHANGED_FTM_RESPONDER: fine timing measurement request responder
 *	functionality changed क्रम this BSS (AP mode).
 * @BSS_CHANGED_TWT: TWT status changed
 * @BSS_CHANGED_HE_OBSS_PD: OBSS Packet Detection status changed.
 * @BSS_CHANGED_HE_BSS_COLOR: BSS Color has changed
 * @BSS_CHANGED_FILS_DISCOVERY: FILS discovery status changed.
 * @BSS_CHANGED_UNSOL_BCAST_PROBE_RESP: Unsolicited broadcast probe response
 *	status changed.
 *
 */
क्रमागत ieee80211_bss_change अणु
	BSS_CHANGED_ASSOC		= 1<<0,
	BSS_CHANGED_ERP_CTS_PROT	= 1<<1,
	BSS_CHANGED_ERP_PREAMBLE	= 1<<2,
	BSS_CHANGED_ERP_SLOT		= 1<<3,
	BSS_CHANGED_HT			= 1<<4,
	BSS_CHANGED_BASIC_RATES		= 1<<5,
	BSS_CHANGED_BEACON_INT		= 1<<6,
	BSS_CHANGED_BSSID		= 1<<7,
	BSS_CHANGED_BEACON		= 1<<8,
	BSS_CHANGED_BEACON_ENABLED	= 1<<9,
	BSS_CHANGED_CQM			= 1<<10,
	BSS_CHANGED_IBSS		= 1<<11,
	BSS_CHANGED_ARP_FILTER		= 1<<12,
	BSS_CHANGED_QOS			= 1<<13,
	BSS_CHANGED_IDLE		= 1<<14,
	BSS_CHANGED_SSID		= 1<<15,
	BSS_CHANGED_AP_PROBE_RESP	= 1<<16,
	BSS_CHANGED_PS			= 1<<17,
	BSS_CHANGED_TXPOWER		= 1<<18,
	BSS_CHANGED_P2P_PS		= 1<<19,
	BSS_CHANGED_BEACON_INFO		= 1<<20,
	BSS_CHANGED_BANDWIDTH		= 1<<21,
	BSS_CHANGED_OCB                 = 1<<22,
	BSS_CHANGED_MU_GROUPS		= 1<<23,
	BSS_CHANGED_KEEP_ALIVE		= 1<<24,
	BSS_CHANGED_MCAST_RATE		= 1<<25,
	BSS_CHANGED_FTM_RESPONDER	= 1<<26,
	BSS_CHANGED_TWT			= 1<<27,
	BSS_CHANGED_HE_OBSS_PD		= 1<<28,
	BSS_CHANGED_HE_BSS_COLOR	= 1<<29,
	BSS_CHANGED_FILS_DISCOVERY      = 1<<30,
	BSS_CHANGED_UNSOL_BCAST_PROBE_RESP = 1<<31,

	/* when adding here, make sure to change ieee80211_reconfig */
पूर्ण;

/*
 * The maximum number of IPv4 addresses listed क्रम ARP filtering. If the number
 * of addresses क्रम an पूर्णांकerface increase beyond this value, hardware ARP
 * filtering will be disabled.
 */
#घोषणा IEEE80211_BSS_ARP_ADDR_LIST_LEN 4

/**
 * क्रमागत ieee80211_event_type - event to be notअगरied to the low level driver
 * @RSSI_EVENT: AP's rssi crossed the a threshold set by the driver.
 * @MLME_EVENT: event related to MLME
 * @BAR_RX_EVENT: a BAR was received
 * @BA_FRAME_TIMEOUT: Frames were released from the reordering buffer because
 *	they समयd out. This won't be called क्रम each frame released, but only
 *	once each समय the समयout triggers.
 */
क्रमागत ieee80211_event_type अणु
	RSSI_EVENT,
	MLME_EVENT,
	BAR_RX_EVENT,
	BA_FRAME_TIMEOUT,
पूर्ण;

/**
 * क्रमागत ieee80211_rssi_event_data - relevant when event type is %RSSI_EVENT
 * @RSSI_EVENT_HIGH: AP's rssi went below the threshold set by the driver.
 * @RSSI_EVENT_LOW: AP's rssi went above the threshold set by the driver.
 */
क्रमागत ieee80211_rssi_event_data अणु
	RSSI_EVENT_HIGH,
	RSSI_EVENT_LOW,
पूर्ण;

/**
 * काष्ठा ieee80211_rssi_event - data attached to an %RSSI_EVENT
 * @data: See &क्रमागत ieee80211_rssi_event_data
 */
काष्ठा ieee80211_rssi_event अणु
	क्रमागत ieee80211_rssi_event_data data;
पूर्ण;

/**
 * क्रमागत ieee80211_mlme_event_data - relevant when event type is %MLME_EVENT
 * @AUTH_EVENT: the MLME operation is authentication
 * @ASSOC_EVENT: the MLME operation is association
 * @DEAUTH_RX_EVENT: deauth received..
 * @DEAUTH_TX_EVENT: deauth sent.
 */
क्रमागत ieee80211_mlme_event_data अणु
	AUTH_EVENT,
	ASSOC_EVENT,
	DEAUTH_RX_EVENT,
	DEAUTH_TX_EVENT,
पूर्ण;

/**
 * क्रमागत ieee80211_mlme_event_status - relevant when event type is %MLME_EVENT
 * @MLME_SUCCESS: the MLME operation completed successfully.
 * @MLME_DENIED: the MLME operation was denied by the peer.
 * @MLME_TIMEOUT: the MLME operation समयd out.
 */
क्रमागत ieee80211_mlme_event_status अणु
	MLME_SUCCESS,
	MLME_DENIED,
	MLME_TIMEOUT,
पूर्ण;

/**
 * काष्ठा ieee80211_mlme_event - data attached to an %MLME_EVENT
 * @data: See &क्रमागत ieee80211_mlme_event_data
 * @status: See &क्रमागत ieee80211_mlme_event_status
 * @reason: the reason code अगर applicable
 */
काष्ठा ieee80211_mlme_event अणु
	क्रमागत ieee80211_mlme_event_data data;
	क्रमागत ieee80211_mlme_event_status status;
	u16 reason;
पूर्ण;

/**
 * काष्ठा ieee80211_ba_event - data attached क्रम BlockAck related events
 * @sta: poपूर्णांकer to the &ieee80211_sta to which this event relates
 * @tid: the tid
 * @ssn: the starting sequence number (क्रम %BAR_RX_EVENT)
 */
काष्ठा ieee80211_ba_event अणु
	काष्ठा ieee80211_sta *sta;
	u16 tid;
	u16 ssn;
पूर्ण;

/**
 * काष्ठा ieee80211_event - event to be sent to the driver
 * @type: The event itself. See &क्रमागत ieee80211_event_type.
 * @rssi: relevant अगर &type is %RSSI_EVENT
 * @mlme: relevant अगर &type is %AUTH_EVENT
 * @ba: relevant अगर &type is %BAR_RX_EVENT or %BA_FRAME_TIMEOUT
 * @u:जोड़ holding the fields above
 */
काष्ठा ieee80211_event अणु
	क्रमागत ieee80211_event_type type;
	जोड़ अणु
		काष्ठा ieee80211_rssi_event rssi;
		काष्ठा ieee80211_mlme_event mlme;
		काष्ठा ieee80211_ba_event ba;
	पूर्ण u;
पूर्ण;

/**
 * काष्ठा ieee80211_mu_group_data - STA's VHT MU-MIMO group data
 *
 * This काष्ठाure describes the group id data of VHT MU-MIMO
 *
 * @membership: 64 bits array - a bit is set अगर station is member of the group
 * @position: 2 bits per group id indicating the position in the group
 */
काष्ठा ieee80211_mu_group_data अणु
	u8 membership[WLAN_MEMBERSHIP_LEN];
	u8 position[WLAN_USER_POSITION_LEN];
पूर्ण;

/**
 * काष्ठा ieee80211_fपंचांग_responder_params - FTM responder parameters
 *
 * @lci: LCI subelement content
 * @civicloc: CIVIC location subelement content
 * @lci_len: LCI data length
 * @civicloc_len: Civic data length
 */
काष्ठा ieee80211_fपंचांग_responder_params अणु
	स्थिर u8 *lci;
	स्थिर u8 *civicloc;
	माप_प्रकार lci_len;
	माप_प्रकार civicloc_len;
पूर्ण;

/**
 * काष्ठा ieee80211_fils_discovery - FILS discovery parameters from
 * IEEE Std 802.11ai-2016, Annex C.3 MIB detail.
 *
 * @min_पूर्णांकerval: Minimum packet पूर्णांकerval in TUs (0 - 10000)
 * @max_पूर्णांकerval: Maximum packet पूर्णांकerval in TUs (0 - 10000)
 */
काष्ठा ieee80211_fils_discovery अणु
	u32 min_पूर्णांकerval;
	u32 max_पूर्णांकerval;
पूर्ण;

/**
 * काष्ठा ieee80211_bss_conf - holds the BSS's changing parameters
 *
 * This काष्ठाure keeps inक्रमmation about a BSS (and an association
 * to that BSS) that can change during the lअगरeसमय of the BSS.
 *
 * @htc_trig_based_pkt_ext: शेष PE in 4us units, अगर BSS supports HE
 * @multi_sta_back_32bit: supports BA biपंचांगap of 32-bits in Multi-STA BACK
 * @uora_exists: is the UORA element advertised by AP
 * @ack_enabled: indicates support to receive a multi-TID that solicits either
 *	ACK, BACK or both
 * @uora_ocw_range: UORA element's OCW Range field
 * @frame_समय_rts_th: HE duration RTS threshold, in units of 32us
 * @he_support: करोes this BSS support HE
 * @twt_requester: करोes this BSS support TWT requester (relevant क्रम managed
 *	mode only, set अगर the AP advertises TWT responder role)
 * @twt_responder: करोes this BSS support TWT requester (relevant क्रम managed
 *	mode only, set अगर the AP advertises TWT responder role)
 * @twt_रक्षित: करोes this BSS support रक्षित TWT frames
 * @assoc: association status
 * @ibss_joined: indicates whether this station is part of an IBSS
 *	or not
 * @ibss_creator: indicates अगर a new IBSS network is being created
 * @aid: association ID number, valid only when @assoc is true
 * @use_cts_prot: use CTS protection
 * @use_लघु_preamble: use 802.11b लघु preamble
 * @use_लघु_slot: use लघु slot समय (only relevant क्रम ERP)
 * @dtim_period: num of beacons beक्रमe the next DTIM, क्रम beaconing,
 *	valid in station mode only अगर after the driver was notअगरied
 *	with the %BSS_CHANGED_BEACON_INFO flag, will be non-zero then.
 * @sync_tsf: last beacon's/probe response's TSF बारtamp (could be old
 *	as it may have been received during scanning दीर्घ ago). If the
 *	HW flag %IEEE80211_HW_TIMING_BEACON_ONLY is set, then this can
 *	only come from a beacon, but might not become valid until after
 *	association when a beacon is received (which is notअगरied with the
 *	%BSS_CHANGED_DTIM flag.). See also sync_dtim_count important notice.
 * @sync_device_ts: the device बारtamp corresponding to the sync_tsf,
 *	the driver/device can use this to calculate synchronisation
 *	(see @sync_tsf). See also sync_dtim_count important notice.
 * @sync_dtim_count: Only valid when %IEEE80211_HW_TIMING_BEACON_ONLY
 *	is requested, see @sync_tsf/@sync_device_ts.
 *	IMPORTANT: These three sync_* parameters would possibly be out of sync
 *	by the समय the driver will use them. The synchronized view is currently
 *	guaranteed only in certain callbacks.
 * @beacon_पूर्णांक: beacon पूर्णांकerval
 * @assoc_capability: capabilities taken from assoc resp
 * @basic_rates: biपंचांगap of basic rates, each bit stands क्रम an
 *	index पूर्णांकo the rate table configured by the driver in
 *	the current band.
 * @beacon_rate: associated AP's beacon TX rate
 * @mcast_rate: per-band multicast rate index + 1 (0: disabled)
 * @bssid: The BSSID क्रम this BSS
 * @enable_beacon: whether beaconing should be enabled or not
 * @chandef: Channel definition क्रम this BSS -- the hardware might be
 *	configured a higher bandwidth than this BSS uses, क्रम example.
 * @mu_group: VHT MU-MIMO group membership data
 * @ht_operation_mode: HT operation mode like in &काष्ठा ieee80211_ht_operation.
 *	This field is only valid when the channel is a wide HT/VHT channel.
 *	Note that with TDLS this can be the हाल (channel is HT, protection must
 *	be used from this field) even when the BSS association isn't using HT.
 * @cqm_rssi_thold: Connection quality monitor RSSI threshold, a zero value
 *	implies disabled. As with the cfg80211 callback, a change here should
 *	cause an event to be sent indicating where the current value is in
 *	relation to the newly configured threshold.
 * @cqm_rssi_low: Connection quality monitor RSSI lower threshold, a zero value
 *	implies disabled.  This is an alternative mechanism to the single
 *	threshold event and can't be enabled simultaneously with it.
 * @cqm_rssi_high: Connection quality monitor RSSI upper threshold.
 * @cqm_rssi_hyst: Connection quality monitor RSSI hysteresis
 * @arp_addr_list: List of IPv4 addresses क्रम hardware ARP filtering. The
 *	may filter ARP queries targeted क्रम other addresses than listed here.
 *	The driver must allow ARP queries targeted क्रम all address listed here
 *	to pass through. An empty list implies no ARP queries need to pass.
 * @arp_addr_cnt: Number of addresses currently on the list. Note that this
 *	may be larger than %IEEE80211_BSS_ARP_ADDR_LIST_LEN (the arp_addr_list
 *	array size), it's up to the driver what to करो in that हाल.
 * @qos: This is a QoS-enabled BSS.
 * @idle: This पूर्णांकerface is idle. There's also a global idle flag in the
 *	hardware config which may be more appropriate depending on what
 *	your driver/device needs to करो.
 * @ps: घातer-save mode (STA only). This flag is NOT affected by
 *	offchannel/dynamic_ps operations.
 * @ssid: The SSID of the current vअगर. Valid in AP and IBSS mode.
 * @ssid_len: Length of SSID given in @ssid.
 * @hidden_ssid: The SSID of the current vअगर is hidden. Only valid in AP-mode.
 * @txघातer: TX घातer in dBm.  पूर्णांक_न्यून means not configured.
 * @txघातer_type: TX घातer adjusपंचांगent used to control per packet Transmit
 *	Power Control (TPC) in lower driver क्रम the current vअगर. In particular
 *	TPC is enabled अगर value passed in %txघातer_type is
 *	NL80211_TX_POWER_LIMITED (allow using less than specअगरied from
 *	userspace), whereas TPC is disabled अगर %txघातer_type is set to
 *	NL80211_TX_POWER_FIXED (use value configured from userspace)
 * @p2p_noa_attr: P2P NoA attribute क्रम P2P घातersave
 * @allow_p2p_go_ps: indication क्रम AP or P2P GO पूर्णांकerface, whether it's allowed
 *	to use P2P PS mechanism or not. AP/P2P GO is not allowed to use P2P PS
 *	अगर it has associated clients without P2P PS support.
 * @max_idle_period: the समय period during which the station can refrain from
 *	transmitting frames to its associated AP without being disassociated.
 *	In units of 1000 TUs. Zero value indicates that the AP did not include
 *	a (valid) BSS Max Idle Period Element.
 * @रक्षित_keep_alive: अगर set, indicates that the station should send an RSN
 *	रक्षित frame to the AP to reset the idle समयr at the AP क्रम the
 *	station.
 * @fपंचांग_responder: whether to enable or disable fine timing measurement FTM
 *	responder functionality.
 * @fपंचांगr_params: configurable lci/civic parameter when enabling FTM responder.
 * @nontransmitted: this BSS is a nontransmitted BSS profile
 * @transmitter_bssid: the address of transmitter AP
 * @bssid_index: index inside the multiple BSSID set
 * @bssid_indicator: 2^bssid_indicator is the maximum number of APs in set
 * @ema_ap: AP supports enhancements of discovery and advertisement of
 *	nontransmitted BSSIDs
 * @profile_periodicity: the least number of beacon frames need to be received
 *	in order to discover all the nontransmitted BSSIDs in the set.
 * @he_oper: HE operation inक्रमmation of the BSS (AP/Mesh) or of the AP we are
 *	connected to (STA)
 * @he_obss_pd: OBSS Packet Detection parameters.
 * @he_bss_color: BSS coloring settings, अगर BSS supports HE
 * @fils_discovery: FILS discovery configuration
 * @unsol_bcast_probe_resp_पूर्णांकerval: Unsolicited broadcast probe response
 *	पूर्णांकerval.
 * @s1g: BSS is S1G BSS (affects Association Request क्रमmat).
 * @beacon_tx_rate: The configured beacon transmit rate that needs to be passed
 *	to driver when rate control is offloaded to firmware.
 */
काष्ठा ieee80211_bss_conf अणु
	स्थिर u8 *bssid;
	u8 htc_trig_based_pkt_ext;
	bool uora_exists;
	u8 uora_ocw_range;
	u16 frame_समय_rts_th;
	bool he_support;
	bool twt_requester;
	bool twt_responder;
	bool twt_रक्षित;
	/* association related data */
	bool assoc, ibss_joined;
	bool ibss_creator;
	u16 aid;
	/* erp related data */
	bool use_cts_prot;
	bool use_लघु_preamble;
	bool use_लघु_slot;
	bool enable_beacon;
	u8 dtim_period;
	u16 beacon_पूर्णांक;
	u16 assoc_capability;
	u64 sync_tsf;
	u32 sync_device_ts;
	u8 sync_dtim_count;
	u32 basic_rates;
	काष्ठा ieee80211_rate *beacon_rate;
	पूर्णांक mcast_rate[NUM_NL80211_BANDS];
	u16 ht_operation_mode;
	s32 cqm_rssi_thold;
	u32 cqm_rssi_hyst;
	s32 cqm_rssi_low;
	s32 cqm_rssi_high;
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा ieee80211_mu_group_data mu_group;
	__be32 arp_addr_list[IEEE80211_BSS_ARP_ADDR_LIST_LEN];
	पूर्णांक arp_addr_cnt;
	bool qos;
	bool idle;
	bool ps;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	माप_प्रकार ssid_len;
	bool hidden_ssid;
	पूर्णांक txघातer;
	क्रमागत nl80211_tx_घातer_setting txघातer_type;
	काष्ठा ieee80211_p2p_noa_attr p2p_noa_attr;
	bool allow_p2p_go_ps;
	u16 max_idle_period;
	bool रक्षित_keep_alive;
	bool fपंचांग_responder;
	काष्ठा ieee80211_fपंचांग_responder_params *fपंचांगr_params;
	/* Multiple BSSID data */
	bool nontransmitted;
	u8 transmitter_bssid[ETH_ALEN];
	u8 bssid_index;
	u8 bssid_indicator;
	bool ema_ap;
	u8 profile_periodicity;
	काष्ठा अणु
		u32 params;
		u16 nss_set;
	पूर्ण he_oper;
	काष्ठा ieee80211_he_obss_pd he_obss_pd;
	काष्ठा cfg80211_he_bss_color he_bss_color;
	काष्ठा ieee80211_fils_discovery fils_discovery;
	u32 unsol_bcast_probe_resp_पूर्णांकerval;
	bool s1g;
	काष्ठा cfg80211_bitrate_mask beacon_tx_rate;
पूर्ण;

/**
 * क्रमागत mac80211_tx_info_flags - flags to describe transmission inक्रमmation/status
 *
 * These flags are used with the @flags member of &ieee80211_tx_info.
 *
 * @IEEE80211_TX_CTL_REQ_TX_STATUS: require TX status callback क्रम this frame.
 * @IEEE80211_TX_CTL_ASSIGN_SEQ: The driver has to assign a sequence
 *	number to this frame, taking care of not overwriting the fragment
 *	number and increasing the sequence number only when the
 *	IEEE80211_TX_CTL_FIRST_FRAGMENT flag is set. mac80211 will properly
 *	assign sequence numbers to QoS-data frames but cannot करो so correctly
 *	क्रम non-QoS-data and management frames because beacons need them from
 *	that counter as well and mac80211 cannot guarantee proper sequencing.
 *	If this flag is set, the driver should inकाष्ठा the hardware to
 *	assign a sequence number to the frame or assign one itself. Cf. IEEE
 *	802.11-2007 7.1.3.4.1 paragraph 3. This flag will always be set क्रम
 *	beacons and always be clear क्रम frames without a sequence number field.
 * @IEEE80211_TX_CTL_NO_ACK: tell the low level not to रुको क्रम an ack
 * @IEEE80211_TX_CTL_CLEAR_PS_FILT: clear घातersave filter क्रम destination
 *	station
 * @IEEE80211_TX_CTL_FIRST_FRAGMENT: this is a first fragment of the frame
 * @IEEE80211_TX_CTL_SEND_AFTER_DTIM: send this frame after DTIM beacon
 * @IEEE80211_TX_CTL_AMPDU: this frame should be sent as part of an A-MPDU
 * @IEEE80211_TX_CTL_INJECTED: Frame was injected, पूर्णांकernal to mac80211.
 * @IEEE80211_TX_STAT_TX_FILTERED: The frame was not transmitted
 *	because the destination STA was in घातersave mode. Note that to
 *	aव्योम race conditions, the filter must be set by the hardware or
 *	firmware upon receiving a frame that indicates that the station
 *	went to sleep (must be करोne on device to filter frames alपढ़ोy on
 *	the queue) and may only be unset after mac80211 gives the OK क्रम
 *	that by setting the IEEE80211_TX_CTL_CLEAR_PS_FILT (see above),
 *	since only then is it guaranteed that no more frames are in the
 *	hardware queue.
 * @IEEE80211_TX_STAT_ACK: Frame was acknowledged
 * @IEEE80211_TX_STAT_AMPDU: The frame was aggregated, so status
 * 	is क्रम the whole aggregation.
 * @IEEE80211_TX_STAT_AMPDU_NO_BACK: no block ack was वापसed,
 * 	so consider using block ack request (BAR).
 * @IEEE80211_TX_CTL_RATE_CTRL_PROBE: पूर्णांकernal to mac80211, can be
 *	set by rate control algorithms to indicate probe rate, will
 *	be cleared क्रम fragmented frames (except on the last fragment)
 * @IEEE80211_TX_INTFL_OFFCHAN_TX_OK: Internal to mac80211. Used to indicate
 *	that a frame can be transmitted जबतक the queues are stopped क्रम
 *	off-channel operation.
 * @IEEE80211_TX_CTL_HW_80211_ENCAP: This frame uses hardware encapsulation
 *	(header conversion)
 * @IEEE80211_TX_INTFL_RETRIED: completely पूर्णांकernal to mac80211,
 *	used to indicate that a frame was alपढ़ोy retried due to PS
 * @IEEE80211_TX_INTFL_DONT_ENCRYPT: completely पूर्णांकernal to mac80211,
 *	used to indicate frame should not be encrypted
 * @IEEE80211_TX_CTL_NO_PS_BUFFER: This frame is a response to a poll
 *	frame (PS-Poll or uAPSD) or a non-bufferable MMPDU and must
 *	be sent although the station is in घातersave mode.
 * @IEEE80211_TX_CTL_MORE_FRAMES: More frames will be passed to the
 *	transmit function after the current frame, this can be used
 *	by drivers to kick the DMA queue only अगर unset or when the
 *	queue माला_लो full.
 * @IEEE80211_TX_INTFL_RETRANSMISSION: This frame is being retransmitted
 *	after TX status because the destination was asleep, it must not
 *	be modअगरied again (no seqno assignment, crypto, etc.)
 * @IEEE80211_TX_INTFL_MLME_CONN_TX: This frame was transmitted by the MLME
 *	code क्रम connection establishment, this indicates that its status
 *	should kick the MLME state machine.
 * @IEEE80211_TX_INTFL_NL80211_FRAME_TX: Frame was requested through nl80211
 *	MLME command (पूर्णांकernal to mac80211 to figure out whether to send TX
 *	status to user space)
 * @IEEE80211_TX_CTL_LDPC: tells the driver to use LDPC क्रम this frame
 * @IEEE80211_TX_CTL_STBC: Enables Space-Time Block Coding (STBC) क्रम this
 *	frame and selects the maximum number of streams that it can use.
 * @IEEE80211_TX_CTL_TX_OFFCHAN: Marks this packet to be transmitted on
 *	the off-channel channel when a reमुख्य-on-channel offload is करोne
 *	in hardware -- normal packets still flow and are expected to be
 *	handled properly by the device.
 * @IEEE80211_TX_INTFL_TKIP_MIC_FAILURE: Marks this packet to be used क्रम TKIP
 *	testing. It will be sent out with incorrect Michael MIC key to allow
 *	TKIP countermeasures to be tested.
 * @IEEE80211_TX_CTL_NO_CCK_RATE: This frame will be sent at non CCK rate.
 *	This flag is actually used क्रम management frame especially क्रम P2P
 *	frames not being sent at CCK rate in 2GHz band.
 * @IEEE80211_TX_STATUS_EOSP: This packet marks the end of service period,
 *	when its status is reported the service period ends. For frames in
 *	an SP that mac80211 transmits, it is alपढ़ोy set; क्रम driver frames
 *	the driver may set this flag. It is also used to करो the same क्रम
 *	PS-Poll responses.
 * @IEEE80211_TX_CTL_USE_MINRATE: This frame will be sent at lowest rate.
 *	This flag is used to send nullfunc frame at minimum rate when
 *	the nullfunc is used क्रम connection monitoring purpose.
 * @IEEE80211_TX_CTL_DONTFRAG: Don't fragment this packet even अगर it
 *	would be fragmented by size (this is optional, only used क्रम
 *	monitor injection).
 * @IEEE80211_TX_STAT_NOACK_TRANSMITTED: A frame that was marked with
 *	IEEE80211_TX_CTL_NO_ACK has been successfully transmitted without
 *	any errors (like issues specअगरic to the driver/HW).
 *	This flag must not be set क्रम frames that करोn't request no-ack
 *	behaviour with IEEE80211_TX_CTL_NO_ACK.
 *
 * Note: If you have to add new flags to the क्रमागतeration, then करोn't
 *	 क्रमget to update %IEEE80211_TX_TEMPORARY_FLAGS when necessary.
 */
क्रमागत mac80211_tx_info_flags अणु
	IEEE80211_TX_CTL_REQ_TX_STATUS		= BIT(0),
	IEEE80211_TX_CTL_ASSIGN_SEQ		= BIT(1),
	IEEE80211_TX_CTL_NO_ACK			= BIT(2),
	IEEE80211_TX_CTL_CLEAR_PS_FILT		= BIT(3),
	IEEE80211_TX_CTL_FIRST_FRAGMENT		= BIT(4),
	IEEE80211_TX_CTL_SEND_AFTER_DTIM	= BIT(5),
	IEEE80211_TX_CTL_AMPDU			= BIT(6),
	IEEE80211_TX_CTL_INJECTED		= BIT(7),
	IEEE80211_TX_STAT_TX_FILTERED		= BIT(8),
	IEEE80211_TX_STAT_ACK			= BIT(9),
	IEEE80211_TX_STAT_AMPDU			= BIT(10),
	IEEE80211_TX_STAT_AMPDU_NO_BACK		= BIT(11),
	IEEE80211_TX_CTL_RATE_CTRL_PROBE	= BIT(12),
	IEEE80211_TX_INTFL_OFFCHAN_TX_OK	= BIT(13),
	IEEE80211_TX_CTL_HW_80211_ENCAP		= BIT(14),
	IEEE80211_TX_INTFL_RETRIED		= BIT(15),
	IEEE80211_TX_INTFL_DONT_ENCRYPT		= BIT(16),
	IEEE80211_TX_CTL_NO_PS_BUFFER		= BIT(17),
	IEEE80211_TX_CTL_MORE_FRAMES		= BIT(18),
	IEEE80211_TX_INTFL_RETRANSMISSION	= BIT(19),
	IEEE80211_TX_INTFL_MLME_CONN_TX		= BIT(20),
	IEEE80211_TX_INTFL_NL80211_FRAME_TX	= BIT(21),
	IEEE80211_TX_CTL_LDPC			= BIT(22),
	IEEE80211_TX_CTL_STBC			= BIT(23) | BIT(24),
	IEEE80211_TX_CTL_TX_OFFCHAN		= BIT(25),
	IEEE80211_TX_INTFL_TKIP_MIC_FAILURE	= BIT(26),
	IEEE80211_TX_CTL_NO_CCK_RATE		= BIT(27),
	IEEE80211_TX_STATUS_EOSP		= BIT(28),
	IEEE80211_TX_CTL_USE_MINRATE		= BIT(29),
	IEEE80211_TX_CTL_DONTFRAG		= BIT(30),
	IEEE80211_TX_STAT_NOACK_TRANSMITTED	= BIT(31),
पूर्ण;

#घोषणा IEEE80211_TX_CTL_STBC_SHIFT		23

#घोषणा IEEE80211_TX_RC_S1G_MCS IEEE80211_TX_RC_VHT_MCS

/**
 * क्रमागत mac80211_tx_control_flags - flags to describe transmit control
 *
 * @IEEE80211_TX_CTRL_PORT_CTRL_PROTO: this frame is a port control
 *	protocol frame (e.g. EAP)
 * @IEEE80211_TX_CTRL_PS_RESPONSE: This frame is a response to a poll
 *	frame (PS-Poll or uAPSD).
 * @IEEE80211_TX_CTRL_RATE_INJECT: This frame is injected with rate inक्रमmation
 * @IEEE80211_TX_CTRL_AMSDU: This frame is an A-MSDU frame
 * @IEEE80211_TX_CTRL_FAST_XMIT: This frame is going through the fast_xmit path
 * @IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP: This frame skips mesh path lookup
 * @IEEE80211_TX_INTCFL_NEED_TXPROCESSING: completely पूर्णांकernal to mac80211,
 *	used to indicate that a pending frame requires TX processing beक्रमe
 *	it can be sent out.
 * @IEEE80211_TX_CTRL_NO_SEQNO: Do not overग_लिखो the sequence number that
 *	has alपढ़ोy been asचिन्हित to this frame.
 * @IEEE80211_TX_CTRL_DONT_REORDER: This frame should not be reordered
 *	relative to other frames that have this flag set, independent
 *	of their QoS TID or other priority field values.
 *
 * These flags are used in tx_info->control.flags.
 */
क्रमागत mac80211_tx_control_flags अणु
	IEEE80211_TX_CTRL_PORT_CTRL_PROTO	= BIT(0),
	IEEE80211_TX_CTRL_PS_RESPONSE		= BIT(1),
	IEEE80211_TX_CTRL_RATE_INJECT		= BIT(2),
	IEEE80211_TX_CTRL_AMSDU			= BIT(3),
	IEEE80211_TX_CTRL_FAST_XMIT		= BIT(4),
	IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP	= BIT(5),
	IEEE80211_TX_INTCFL_NEED_TXPROCESSING	= BIT(6),
	IEEE80211_TX_CTRL_NO_SEQNO		= BIT(7),
	IEEE80211_TX_CTRL_DONT_REORDER		= BIT(8),
पूर्ण;

/*
 * This definition is used as a mask to clear all temporary flags, which are
 * set by the tx handlers क्रम each transmission attempt by the mac80211 stack.
 */
#घोषणा IEEE80211_TX_TEMPORARY_FLAGS (IEEE80211_TX_CTL_NO_ACK |		      \
	IEEE80211_TX_CTL_CLEAR_PS_FILT | IEEE80211_TX_CTL_FIRST_FRAGMENT |    \
	IEEE80211_TX_CTL_SEND_AFTER_DTIM | IEEE80211_TX_CTL_AMPDU |	      \
	IEEE80211_TX_STAT_TX_FILTERED |	IEEE80211_TX_STAT_ACK |		      \
	IEEE80211_TX_STAT_AMPDU | IEEE80211_TX_STAT_AMPDU_NO_BACK |	      \
	IEEE80211_TX_CTL_RATE_CTRL_PROBE | IEEE80211_TX_CTL_NO_PS_BUFFER |    \
	IEEE80211_TX_CTL_MORE_FRAMES | IEEE80211_TX_CTL_LDPC |		      \
	IEEE80211_TX_CTL_STBC | IEEE80211_TX_STATUS_EOSP)

/**
 * क्रमागत mac80211_rate_control_flags - per-rate flags set by the
 *	Rate Control algorithm.
 *
 * These flags are set by the Rate control algorithm क्रम each rate during tx,
 * in the @flags member of काष्ठा ieee80211_tx_rate.
 *
 * @IEEE80211_TX_RC_USE_RTS_CTS: Use RTS/CTS exchange क्रम this rate.
 * @IEEE80211_TX_RC_USE_CTS_PROTECT: CTS-to-self protection is required.
 *	This is set अगर the current BSS requires ERP protection.
 * @IEEE80211_TX_RC_USE_SHORT_PREAMBLE: Use लघु preamble.
 * @IEEE80211_TX_RC_MCS: HT rate.
 * @IEEE80211_TX_RC_VHT_MCS: VHT MCS rate, in this हाल the idx field is split
 *	पूर्णांकo a higher 4 bits (Nss) and lower 4 bits (MCS number)
 * @IEEE80211_TX_RC_GREEN_FIELD: Indicates whether this rate should be used in
 *	Greenfield mode.
 * @IEEE80211_TX_RC_40_MHZ_WIDTH: Indicates अगर the Channel Width should be 40 MHz.
 * @IEEE80211_TX_RC_80_MHZ_WIDTH: Indicates 80 MHz transmission
 * @IEEE80211_TX_RC_160_MHZ_WIDTH: Indicates 160 MHz transmission
 *	(80+80 isn't supported yet)
 * @IEEE80211_TX_RC_DUP_DATA: The frame should be transmitted on both of the
 *	adjacent 20 MHz channels, अगर the current channel type is
 *	NL80211_CHAN_HT40MINUS or NL80211_CHAN_HT40PLUS.
 * @IEEE80211_TX_RC_SHORT_GI: Short Guard पूर्णांकerval should be used क्रम this rate.
 */
क्रमागत mac80211_rate_control_flags अणु
	IEEE80211_TX_RC_USE_RTS_CTS		= BIT(0),
	IEEE80211_TX_RC_USE_CTS_PROTECT		= BIT(1),
	IEEE80211_TX_RC_USE_SHORT_PREAMBLE	= BIT(2),

	/* rate index is an HT/VHT MCS instead of an index */
	IEEE80211_TX_RC_MCS			= BIT(3),
	IEEE80211_TX_RC_GREEN_FIELD		= BIT(4),
	IEEE80211_TX_RC_40_MHZ_WIDTH		= BIT(5),
	IEEE80211_TX_RC_DUP_DATA		= BIT(6),
	IEEE80211_TX_RC_SHORT_GI		= BIT(7),
	IEEE80211_TX_RC_VHT_MCS			= BIT(8),
	IEEE80211_TX_RC_80_MHZ_WIDTH		= BIT(9),
	IEEE80211_TX_RC_160_MHZ_WIDTH		= BIT(10),
पूर्ण;


/* there are 40 bytes अगर you करोn't need the rateset to be kept */
#घोषणा IEEE80211_TX_INFO_DRIVER_DATA_SIZE 40

/* अगर you करो need the rateset, then you have less space */
#घोषणा IEEE80211_TX_INFO_RATE_DRIVER_DATA_SIZE 24

/* maximum number of rate stages */
#घोषणा IEEE80211_TX_MAX_RATES	4

/* maximum number of rate table entries */
#घोषणा IEEE80211_TX_RATE_TABLE_SIZE	4

/**
 * काष्ठा ieee80211_tx_rate - rate selection/status
 *
 * @idx: rate index to attempt to send with
 * @flags: rate control flags (&क्रमागत mac80211_rate_control_flags)
 * @count: number of tries in this rate beक्रमe going to the next rate
 *
 * A value of -1 क्रम @idx indicates an invalid rate and, अगर used
 * in an array of retry rates, that no more rates should be tried.
 *
 * When used क्रम transmit status reporting, the driver should
 * always report the rate aदीर्घ with the flags it used.
 *
 * &काष्ठा ieee80211_tx_info contains an array of these काष्ठाs
 * in the control inक्रमmation, and it will be filled by the rate
 * control algorithm according to what should be sent. For example,
 * अगर this array contains, in the क्रमmat अणु <idx>, <count> पूर्ण the
 * inक्रमmation::
 *
 *    अणु 3, 2 पूर्ण, अणु 2, 2 पूर्ण, अणु 1, 4 पूर्ण, अणु -1, 0 पूर्ण, अणु -1, 0 पूर्ण
 *
 * then this means that the frame should be transmitted
 * up to twice at rate 3, up to twice at rate 2, and up to four
 * बार at rate 1 अगर it करोesn't get acknowledged. Say it माला_लो
 * acknowledged by the peer after the fअगरth attempt, the status
 * inक्रमmation should then contain::
 *
 *   अणु 3, 2 पूर्ण, अणु 2, 2 पूर्ण, अणु 1, 1 पूर्ण, अणु -1, 0 पूर्ण ...
 *
 * since it was transmitted twice at rate 3, twice at rate 2
 * and once at rate 1 after which we received an acknowledgement.
 */
काष्ठा ieee80211_tx_rate अणु
	s8 idx;
	u16 count:5,
	    flags:11;
पूर्ण __packed;

#घोषणा IEEE80211_MAX_TX_RETRY		31

अटल अंतरभूत व्योम ieee80211_rate_set_vht(काष्ठा ieee80211_tx_rate *rate,
					  u8 mcs, u8 nss)
अणु
	WARN_ON(mcs & ~0xF);
	WARN_ON((nss - 1) & ~0x7);
	rate->idx = ((nss - 1) << 4) | mcs;
पूर्ण

अटल अंतरभूत u8
ieee80211_rate_get_vht_mcs(स्थिर काष्ठा ieee80211_tx_rate *rate)
अणु
	वापस rate->idx & 0xF;
पूर्ण

अटल अंतरभूत u8
ieee80211_rate_get_vht_nss(स्थिर काष्ठा ieee80211_tx_rate *rate)
अणु
	वापस (rate->idx >> 4) + 1;
पूर्ण

/**
 * काष्ठा ieee80211_tx_info - skb transmit inक्रमmation
 *
 * This काष्ठाure is placed in skb->cb क्रम three uses:
 *  (1) mac80211 TX control - mac80211 tells the driver what to करो
 *  (2) driver पूर्णांकernal use (अगर applicable)
 *  (3) TX status inक्रमmation - driver tells mac80211 what happened
 *
 * @flags: transmit info flags, defined above
 * @band: the band to transmit on (use क्रम checking क्रम races)
 * @hw_queue: HW queue to put the frame on, skb_get_queue_mapping() gives the AC
 * @ack_frame_id: पूर्णांकernal frame ID क्रम TX status, used पूर्णांकernally
 * @tx_समय_est: TX समय estimate in units of 4us, used पूर्णांकernally
 * @control: जोड़ part क्रम control data
 * @control.rates: TX rates array to try
 * @control.rts_cts_rate_idx: rate क्रम RTS or CTS
 * @control.use_rts: use RTS
 * @control.use_cts_prot: use RTS/CTS
 * @control.लघु_preamble: use लघु preamble (CCK only)
 * @control.skip_table: skip बाह्यally configured rate table
 * @control.jअगरfies: बारtamp क्रम expiry on घातersave clients
 * @control.vअगर: भव पूर्णांकerface (may be शून्य)
 * @control.hw_key: key to encrypt with (may be शून्य)
 * @control.flags: control flags, see &क्रमागत mac80211_tx_control_flags
 * @control.enqueue_समय: enqueue समय (क्रम iTXQs)
 * @driver_rates: alias to @control.rates to reserve space
 * @pad: padding
 * @rate_driver_data: driver use area अगर driver needs @control.rates
 * @status: जोड़ part क्रम status data
 * @status.rates: attempted rates
 * @status.ack_संकेत: ACK संकेत
 * @status.ampdu_ack_len: AMPDU ack length
 * @status.ampdu_len: AMPDU length
 * @status.antenna: (legacy, kept only क्रम iwlegacy)
 * @status.tx_समय: airसमय consumed क्रम transmission; note this is only
 *	used क्रम WMM AC, not क्रम airसमय fairness
 * @status.is_valid_ack_संकेत: ACK संकेत is valid
 * @status.status_driver_data: driver use area
 * @ack: जोड़ part क्रम pure ACK data
 * @ack.cookie: cookie क्रम the ACK
 * @driver_data: array of driver_data poपूर्णांकers
 * @ampdu_ack_len: number of acked aggregated frames.
 * 	relevant only अगर IEEE80211_TX_STAT_AMPDU was set.
 * @ampdu_len: number of aggregated frames.
 * 	relevant only अगर IEEE80211_TX_STAT_AMPDU was set.
 * @ack_संकेत: संकेत strength of the ACK frame
 */
काष्ठा ieee80211_tx_info अणु
	/* common inक्रमmation */
	u32 flags;
	u32 band:3,
	    ack_frame_id:13,
	    hw_queue:4,
	    tx_समय_est:10;
	/* 2 मुक्त bits */

	जोड़ अणु
		काष्ठा अणु
			जोड़ अणु
				/* rate control */
				काष्ठा अणु
					काष्ठा ieee80211_tx_rate rates[
						IEEE80211_TX_MAX_RATES];
					s8 rts_cts_rate_idx;
					u8 use_rts:1;
					u8 use_cts_prot:1;
					u8 लघु_preamble:1;
					u8 skip_table:1;
					/* 2 bytes मुक्त */
				पूर्ण;
				/* only needed beक्रमe rate control */
				अचिन्हित दीर्घ jअगरfies;
			पूर्ण;
			/* NB: vअगर can be शून्य क्रम injected frames */
			काष्ठा ieee80211_vअगर *vअगर;
			काष्ठा ieee80211_key_conf *hw_key;
			u32 flags;
			codel_समय_प्रकार enqueue_समय;
		पूर्ण control;
		काष्ठा अणु
			u64 cookie;
		पूर्ण ack;
		काष्ठा अणु
			काष्ठा ieee80211_tx_rate rates[IEEE80211_TX_MAX_RATES];
			s32 ack_संकेत;
			u8 ampdu_ack_len;
			u8 ampdu_len;
			u8 antenna;
			u16 tx_समय;
			bool is_valid_ack_संकेत;
			व्योम *status_driver_data[19 / माप(व्योम *)];
		पूर्ण status;
		काष्ठा अणु
			काष्ठा ieee80211_tx_rate driver_rates[
				IEEE80211_TX_MAX_RATES];
			u8 pad[4];

			व्योम *rate_driver_data[
				IEEE80211_TX_INFO_RATE_DRIVER_DATA_SIZE / माप(व्योम *)];
		पूर्ण;
		व्योम *driver_data[
			IEEE80211_TX_INFO_DRIVER_DATA_SIZE / माप(व्योम *)];
	पूर्ण;
पूर्ण;

अटल अंतरभूत u16
ieee80211_info_set_tx_समय_est(काष्ठा ieee80211_tx_info *info, u16 tx_समय_est)
अणु
	/* We only have 10 bits in tx_समय_est, so store airसमय
	 * in increments of 4us and clamp the maximum to 2**12-1
	 */
	info->tx_समय_est = min_t(u16, tx_समय_est, 4095) >> 2;
	वापस info->tx_समय_est << 2;
पूर्ण

अटल अंतरभूत u16
ieee80211_info_get_tx_समय_est(काष्ठा ieee80211_tx_info *info)
अणु
	वापस info->tx_समय_est << 2;
पूर्ण

/**
 * काष्ठा ieee80211_tx_status - extended tx status info क्रम rate control
 *
 * @sta: Station that the packet was transmitted क्रम
 * @info: Basic tx status inक्रमmation
 * @skb: Packet skb (can be शून्य अगर not provided by the driver)
 * @rate: The TX rate that was used when sending the packet
 * @मुक्त_list: list where processed skbs are stored to be मुक्त'd by the driver
 */
काष्ठा ieee80211_tx_status अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sk_buff *skb;
	काष्ठा rate_info *rate;
	काष्ठा list_head *मुक्त_list;
पूर्ण;

/**
 * काष्ठा ieee80211_scan_ies - descriptors क्रम dअगरferent blocks of IEs
 *
 * This काष्ठाure is used to poपूर्णांक to dअगरferent blocks of IEs in HW scan
 * and scheduled scan. These blocks contain the IEs passed by userspace
 * and the ones generated by mac80211.
 *
 * @ies: poपूर्णांकers to band specअगरic IEs.
 * @len: lengths of band_specअगरic IEs.
 * @common_ies: IEs क्रम all bands (especially venकरोr specअगरic ones)
 * @common_ie_len: length of the common_ies
 */
काष्ठा ieee80211_scan_ies अणु
	स्थिर u8 *ies[NUM_NL80211_BANDS];
	माप_प्रकार len[NUM_NL80211_BANDS];
	स्थिर u8 *common_ies;
	माप_प्रकार common_ie_len;
पूर्ण;


अटल अंतरभूत काष्ठा ieee80211_tx_info *IEEE80211_SKB_CB(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ieee80211_tx_info *)skb->cb;
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_rx_status *IEEE80211_SKB_RXCB(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा ieee80211_rx_status *)skb->cb;
पूर्ण

/**
 * ieee80211_tx_info_clear_status - clear TX status
 *
 * @info: The &काष्ठा ieee80211_tx_info to be cleared.
 *
 * When the driver passes an skb back to mac80211, it must report
 * a number of things in TX status. This function clears everything
 * in the TX status but the rate control inक्रमmation (it करोes clear
 * the count since you need to fill that in anyway).
 *
 * NOTE: You can only use this function अगर you करो NOT use
 *	 info->driver_data! Use info->rate_driver_data
 *	 instead अगर you need only the less space that allows.
 */
अटल अंतरभूत व्योम
ieee80211_tx_info_clear_status(काष्ठा ieee80211_tx_info *info)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(दुरत्व(काष्ठा ieee80211_tx_info, status.rates) !=
		     दुरत्व(काष्ठा ieee80211_tx_info, control.rates));
	BUILD_BUG_ON(दुरत्व(काष्ठा ieee80211_tx_info, status.rates) !=
		     दुरत्व(काष्ठा ieee80211_tx_info, driver_rates));
	BUILD_BUG_ON(दुरत्व(काष्ठा ieee80211_tx_info, status.rates) != 8);
	/* clear the rate counts */
	क्रम (i = 0; i < IEEE80211_TX_MAX_RATES; i++)
		info->status.rates[i].count = 0;

	BUILD_BUG_ON(
	    दुरत्व(काष्ठा ieee80211_tx_info, status.ack_संकेत) != 20);
	स_रखो(&info->status.ampdu_ack_len, 0,
	       माप(काष्ठा ieee80211_tx_info) -
	       दुरत्व(काष्ठा ieee80211_tx_info, status.ampdu_ack_len));
पूर्ण


/**
 * क्रमागत mac80211_rx_flags - receive flags
 *
 * These flags are used with the @flag member of &काष्ठा ieee80211_rx_status.
 * @RX_FLAG_MMIC_ERROR: Michael MIC error was reported on this frame.
 *	Use together with %RX_FLAG_MMIC_STRIPPED.
 * @RX_FLAG_DECRYPTED: This frame was decrypted in hardware.
 * @RX_FLAG_MMIC_STRIPPED: the Michael MIC is stripped off this frame,
 *	verअगरication has been करोne by the hardware.
 * @RX_FLAG_IV_STRIPPED: The IV and ICV are stripped from this frame.
 *	If this flag is set, the stack cannot करो any replay detection
 *	hence the driver or hardware will have to करो that.
 * @RX_FLAG_PN_VALIDATED: Currently only valid क्रम CCMP/GCMP frames, this
 *	flag indicates that the PN was verअगरied क्रम replay protection.
 *	Note that this flag is also currently only supported when a frame
 *	is also decrypted (ie. @RX_FLAG_DECRYPTED must be set)
 * @RX_FLAG_DUP_VALIDATED: The driver should set this flag अगर it did
 *	de-duplication by itself.
 * @RX_FLAG_FAILED_FCS_CRC: Set this flag अगर the FCS check failed on
 *	the frame.
 * @RX_FLAG_FAILED_PLCP_CRC: Set this flag अगर the PCLP check failed on
 *	the frame.
 * @RX_FLAG_MACTIME_START: The बारtamp passed in the RX status (@maस_समय
 *	field) is valid and contains the समय the first symbol of the MPDU
 *	was received. This is useful in monitor mode and क्रम proper IBSS
 *	merging.
 * @RX_FLAG_MACTIME_END: The बारtamp passed in the RX status (@maस_समय
 *	field) is valid and contains the समय the last symbol of the MPDU
 *	(including FCS) was received.
 * @RX_FLAG_MACTIME_PLCP_START: The बारtamp passed in the RX status (@maस_समय
 *	field) is valid and contains the समय the SYNC preamble was received.
 * @RX_FLAG_NO_SIGNAL_VAL: The संकेत strength value is not present.
 *	Valid only क्रम data frames (मुख्यly A-MPDU)
 * @RX_FLAG_AMPDU_DETAILS: A-MPDU details are known, in particular the reference
 *	number (@ampdu_reference) must be populated and be a distinct number क्रम
 *	each A-MPDU
 * @RX_FLAG_AMPDU_LAST_KNOWN: last subframe is known, should be set on all
 *	subframes of a single A-MPDU
 * @RX_FLAG_AMPDU_IS_LAST: this subframe is the last subframe of the A-MPDU
 * @RX_FLAG_AMPDU_DELIM_CRC_ERROR: A delimiter CRC error has been detected
 *	on this subframe
 * @RX_FLAG_AMPDU_DELIM_CRC_KNOWN: The delimiter CRC field is known (the CRC
 *	is stored in the @ampdu_delimiter_crc field)
 * @RX_FLAG_MIC_STRIPPED: The mic was stripped of this packet. Decryption was
 *	करोne by the hardware
 * @RX_FLAG_ONLY_MONITOR: Report frame only to monitor पूर्णांकerfaces without
 *	processing it in any regular way.
 *	This is useful अगर drivers offload some frames but still want to report
 *	them क्रम snअगरfing purposes.
 * @RX_FLAG_SKIP_MONITOR: Process and report frame to all पूर्णांकerfaces except
 *	monitor पूर्णांकerfaces.
 *	This is useful अगर drivers offload some frames but still want to report
 *	them क्रम snअगरfing purposes.
 * @RX_FLAG_AMSDU_MORE: Some drivers may prefer to report separate A-MSDU
 *	subframes instead of a one huge frame क्रम perक्रमmance reasons.
 *	All, but the last MSDU from an A-MSDU should have this flag set. E.g.
 *	अगर an A-MSDU has 3 frames, the first 2 must have the flag set, जबतक
 *	the 3rd (last) one must not have this flag set. The flag is used to
 *	deal with retransmission/duplication recovery properly since A-MSDU
 *	subframes share the same sequence number. Reported subframes can be
 *	either regular MSDU or singly A-MSDUs. Subframes must not be
 *	पूर्णांकerleaved with other frames.
 * @RX_FLAG_RADIOTAP_VENDOR_DATA: This frame contains venकरोr-specअगरic
 *	radiotap data in the skb->data (beक्रमe the frame) as described by
 *	the &काष्ठा ieee80211_venकरोr_radiotap.
 * @RX_FLAG_ALLOW_SAME_PN: Allow the same PN as same packet beक्रमe.
 *	This is used क्रम AMSDU subframes which can have the same PN as
 *	the first subframe.
 * @RX_FLAG_ICV_STRIPPED: The ICV is stripped from this frame. CRC checking must
 *	be करोne in the hardware.
 * @RX_FLAG_AMPDU_खातापूर्ण_BIT: Value of the खातापूर्ण bit in the A-MPDU delimiter क्रम this
 *	frame
 * @RX_FLAG_AMPDU_खातापूर्ण_BIT_KNOWN: The खातापूर्ण value is known
 * @RX_FLAG_RADIOTAP_HE: HE radiotap data is present
 *	(&काष्ठा ieee80211_radiotap_he, mac80211 will fill in
 *	
 *	 - DATA3_DATA_MCS
 *	 - DATA3_DATA_DCM
 *	 - DATA3_CODING
 *	 - DATA5_GI
 *	 - DATA5_DATA_BW_RU_ALLOC
 *	 - DATA6_NSTS
 *	 - DATA3_STBC
 *	
 *	from the RX info data, so leave those zeroed when building this data)
 * @RX_FLAG_RADIOTAP_HE_MU: HE MU radiotap data is present
 *	(&काष्ठा ieee80211_radiotap_he_mu)
 * @RX_FLAG_RADIOTAP_LSIG: L-SIG radiotap data is present
 * @RX_FLAG_NO_PSDU: use the frame only क्रम radiotap reporting, with
 *	the "0-length PSDU" field included there.  The value क्रम it is
 *	in &काष्ठा ieee80211_rx_status.  Note that अगर this value isn't
 *	known the frame shouldn't be reported.
 * @RX_FLAG_8023: the frame has an 802.3 header (decap offload perक्रमmed by
 *	hardware or driver)
 */
क्रमागत mac80211_rx_flags अणु
	RX_FLAG_MMIC_ERROR		= BIT(0),
	RX_FLAG_DECRYPTED		= BIT(1),
	RX_FLAG_MACTIME_PLCP_START	= BIT(2),
	RX_FLAG_MMIC_STRIPPED		= BIT(3),
	RX_FLAG_IV_STRIPPED		= BIT(4),
	RX_FLAG_FAILED_FCS_CRC		= BIT(5),
	RX_FLAG_FAILED_PLCP_CRC 	= BIT(6),
	RX_FLAG_MACTIME_START		= BIT(7),
	RX_FLAG_NO_SIGNAL_VAL		= BIT(8),
	RX_FLAG_AMPDU_DETAILS		= BIT(9),
	RX_FLAG_PN_VALIDATED		= BIT(10),
	RX_FLAG_DUP_VALIDATED		= BIT(11),
	RX_FLAG_AMPDU_LAST_KNOWN	= BIT(12),
	RX_FLAG_AMPDU_IS_LAST		= BIT(13),
	RX_FLAG_AMPDU_DELIM_CRC_ERROR	= BIT(14),
	RX_FLAG_AMPDU_DELIM_CRC_KNOWN	= BIT(15),
	RX_FLAG_MACTIME_END		= BIT(16),
	RX_FLAG_ONLY_MONITOR		= BIT(17),
	RX_FLAG_SKIP_MONITOR		= BIT(18),
	RX_FLAG_AMSDU_MORE		= BIT(19),
	RX_FLAG_RADIOTAP_VENDOR_DATA	= BIT(20),
	RX_FLAG_MIC_STRIPPED		= BIT(21),
	RX_FLAG_ALLOW_SAME_PN		= BIT(22),
	RX_FLAG_ICV_STRIPPED		= BIT(23),
	RX_FLAG_AMPDU_खातापूर्ण_BIT		= BIT(24),
	RX_FLAG_AMPDU_खातापूर्ण_BIT_KNOWN	= BIT(25),
	RX_FLAG_RADIOTAP_HE		= BIT(26),
	RX_FLAG_RADIOTAP_HE_MU		= BIT(27),
	RX_FLAG_RADIOTAP_LSIG		= BIT(28),
	RX_FLAG_NO_PSDU			= BIT(29),
	RX_FLAG_8023			= BIT(30),
पूर्ण;

/**
 * क्रमागत mac80211_rx_encoding_flags - MCS & bandwidth flags
 *
 * @RX_ENC_FLAG_SHORTPRE: Short preamble was used क्रम this frame
 * @RX_ENC_FLAG_SHORT_GI: Short guard पूर्णांकerval was used
 * @RX_ENC_FLAG_HT_GF: This frame was received in a HT-greenfield transmission,
 *	अगर the driver fills this value it should add
 *	%IEEE80211_RADIOTAP_MCS_HAVE_FMT
 *	to @hw.radiotap_mcs_details to advertise that fact.
 * @RX_ENC_FLAG_LDPC: LDPC was used
 * @RX_ENC_FLAG_STBC_MASK: STBC 2 bit biपंचांगask. 1 - Nss=1, 2 - Nss=2, 3 - Nss=3
 * @RX_ENC_FLAG_BF: packet was beamक्रमmed
 */
क्रमागत mac80211_rx_encoding_flags अणु
	RX_ENC_FLAG_SHORTPRE		= BIT(0),
	RX_ENC_FLAG_SHORT_GI		= BIT(2),
	RX_ENC_FLAG_HT_GF		= BIT(3),
	RX_ENC_FLAG_STBC_MASK		= BIT(4) | BIT(5),
	RX_ENC_FLAG_LDPC		= BIT(6),
	RX_ENC_FLAG_BF			= BIT(7),
पूर्ण;

#घोषणा RX_ENC_FLAG_STBC_SHIFT		4

क्रमागत mac80211_rx_encoding अणु
	RX_ENC_LEGACY = 0,
	RX_ENC_HT,
	RX_ENC_VHT,
	RX_ENC_HE,
पूर्ण;

/**
 * काष्ठा ieee80211_rx_status - receive status
 *
 * The low-level driver should provide this inक्रमmation (the subset
 * supported by hardware) to the 802.11 code with each received
 * frame, in the skb's control buffer (cb).
 *
 * @maस_समय: value in microseconds of the 64-bit Time Synchronization Function
 * 	(TSF) समयr when the first data symbol (MPDU) arrived at the hardware.
 * @bootसमय_ns: CLOCK_BOOTTIME बारtamp the frame was received at, this is
 *	needed only क्रम beacons and probe responses that update the scan cache.
 * @device_बारtamp: arbitrary बारtamp क्रम the device, mac80211 करोesn't use
 *	it but can store it and pass it back to the driver क्रम synchronisation
 * @band: the active band when this frame was received
 * @freq: frequency the radio was tuned to when receiving this frame, in MHz
 *	This field must be set क्रम management frames, but isn't strictly needed
 *	क्रम data (other) frames - क्रम those it only affects radiotap reporting.
 * @freq_offset: @freq has a positive offset of 500Khz.
 * @संकेत: संकेत strength when receiving this frame, either in dBm, in dB or
 *	unspecअगरied depending on the hardware capabilities flags
 *	@IEEE80211_HW_SIGNAL_*
 * @chains: biपंचांगask of receive chains क्रम which separate संकेत strength
 *	values were filled.
 * @chain_संकेत: per-chain संकेत strength, in dBm (unlike @संकेत, करोesn't
 *	support dB or unspecअगरied units)
 * @antenna: antenna used
 * @rate_idx: index of data rate पूर्णांकo band's supported rates or MCS index अगर
 *	HT or VHT is used (%RX_FLAG_HT/%RX_FLAG_VHT)
 * @nss: number of streams (VHT and HE only)
 * @flag: %RX_FLAG_\*
 * @encoding: &क्रमागत mac80211_rx_encoding
 * @bw: &क्रमागत rate_info_bw
 * @enc_flags: uses bits from &क्रमागत mac80211_rx_encoding_flags
 * @he_ru: HE RU, from &क्रमागत nl80211_he_ru_alloc
 * @he_gi: HE GI, from &क्रमागत nl80211_he_gi
 * @he_dcm: HE DCM value
 * @rx_flags: पूर्णांकernal RX flags क्रम mac80211
 * @ampdu_reference: A-MPDU reference number, must be a dअगरferent value क्रम
 *	each A-MPDU but the same क्रम each subframe within one A-MPDU
 * @ampdu_delimiter_crc: A-MPDU delimiter CRC
 * @zero_length_psdu_type: radiotap type of the 0-length PSDU
 */
काष्ठा ieee80211_rx_status अणु
	u64 maस_समय;
	u64 bootसमय_ns;
	u32 device_बारtamp;
	u32 ampdu_reference;
	u32 flag;
	u16 freq: 13, freq_offset: 1;
	u8 enc_flags;
	u8 encoding:2, bw:3, he_ru:3;
	u8 he_gi:2, he_dcm:1;
	u8 rate_idx;
	u8 nss;
	u8 rx_flags;
	u8 band;
	u8 antenna;
	s8 संकेत;
	u8 chains;
	s8 chain_संकेत[IEEE80211_MAX_CHAINS];
	u8 ampdu_delimiter_crc;
	u8 zero_length_psdu_type;
पूर्ण;

अटल अंतरभूत u32
ieee80211_rx_status_to_khz(काष्ठा ieee80211_rx_status *rx_status)
अणु
	वापस MHZ_TO_KHZ(rx_status->freq) +
	       (rx_status->freq_offset ? 500 : 0);
पूर्ण

/**
 * काष्ठा ieee80211_venकरोr_radiotap - venकरोr radiotap data inक्रमmation
 * @present: presence biपंचांगap क्रम this venकरोr namespace
 *	(this could be extended in the future अगर any venकरोr needs more
 *	 bits, the radiotap spec करोes allow क्रम that)
 * @align: radiotap venकरोr namespace alignment. This defines the needed
 *	alignment क्रम the @data field below, not क्रम the venकरोr namespace
 *	description itself (which has a fixed 2-byte alignment)
 *	Must be a घातer of two, and be set to at least 1!
 * @oui: radiotap venकरोr namespace OUI
 * @subns: radiotap venकरोr sub namespace
 * @len: radiotap venकरोr sub namespace skip length, अगर alignment is करोne
 *	then that's added to this, i.e. this is only the length of the
 *	@data field.
 * @pad: number of bytes of padding after the @data, this exists so that
 *	the skb data alignment can be preserved even अगर the data has odd
 *	length
 * @data: the actual venकरोr namespace data
 *
 * This काष्ठा, including the venकरोr data, goes पूर्णांकo the skb->data beक्रमe
 * the 802.11 header. It's split up in mac80211 using the align/oui/subns
 * data.
 */
काष्ठा ieee80211_venकरोr_radiotap अणु
	u32 present;
	u8 align;
	u8 oui[3];
	u8 subns;
	u8 pad;
	u16 len;
	u8 data[];
पूर्ण __packed;

/**
 * क्रमागत ieee80211_conf_flags - configuration flags
 *
 * Flags to define PHY configuration options
 *
 * @IEEE80211_CONF_MONITOR: there's a monitor पूर्णांकerface present -- use this
 *	to determine क्रम example whether to calculate बारtamps क्रम packets
 *	or not, करो not use instead of filter flags!
 * @IEEE80211_CONF_PS: Enable 802.11 घातer save mode (managed mode only).
 *	This is the घातer save mode defined by IEEE 802.11-2007 section 11.2,
 *	meaning that the hardware still wakes up क्रम beacons, is able to
 *	transmit frames and receive the possible acknowledgment frames.
 *	Not to be confused with hardware specअगरic wakeup/sleep states,
 *	driver is responsible क्रम that. See the section "Powersave support"
 *	क्रम more.
 * @IEEE80211_CONF_IDLE: The device is running, but idle; अगर the flag is set
 *	the driver should be prepared to handle configuration requests but
 *	may turn the device off as much as possible. Typically, this flag will
 *	be set when an पूर्णांकerface is set UP but not associated or scanning, but
 *	it can also be unset in that हाल when monitor पूर्णांकerfaces are active.
 * @IEEE80211_CONF_OFFCHANNEL: The device is currently not on its मुख्य
 *	operating channel.
 */
क्रमागत ieee80211_conf_flags अणु
	IEEE80211_CONF_MONITOR		= (1<<0),
	IEEE80211_CONF_PS		= (1<<1),
	IEEE80211_CONF_IDLE		= (1<<2),
	IEEE80211_CONF_OFFCHANNEL	= (1<<3),
पूर्ण;


/**
 * क्रमागत ieee80211_conf_changed - denotes which configuration changed
 *
 * @IEEE80211_CONF_CHANGE_LISTEN_INTERVAL: the listen पूर्णांकerval changed
 * @IEEE80211_CONF_CHANGE_MONITOR: the monitor flag changed
 * @IEEE80211_CONF_CHANGE_PS: the PS flag or dynamic PS समयout changed
 * @IEEE80211_CONF_CHANGE_POWER: the TX घातer changed
 * @IEEE80211_CONF_CHANGE_CHANNEL: the channel/channel_type changed
 * @IEEE80211_CONF_CHANGE_RETRY_LIMITS: retry limits changed
 * @IEEE80211_CONF_CHANGE_IDLE: Idle flag changed
 * @IEEE80211_CONF_CHANGE_SMPS: Spatial multiplexing घातersave mode changed
 *	Note that this is only valid अगर channel contexts are not used,
 *	otherwise each channel context has the number of chains listed.
 */
क्रमागत ieee80211_conf_changed अणु
	IEEE80211_CONF_CHANGE_SMPS		= BIT(1),
	IEEE80211_CONF_CHANGE_LISTEN_INTERVAL	= BIT(2),
	IEEE80211_CONF_CHANGE_MONITOR		= BIT(3),
	IEEE80211_CONF_CHANGE_PS		= BIT(4),
	IEEE80211_CONF_CHANGE_POWER		= BIT(5),
	IEEE80211_CONF_CHANGE_CHANNEL		= BIT(6),
	IEEE80211_CONF_CHANGE_RETRY_LIMITS	= BIT(7),
	IEEE80211_CONF_CHANGE_IDLE		= BIT(8),
पूर्ण;

/**
 * क्रमागत ieee80211_smps_mode - spatial multiplexing घातer save mode
 *
 * @IEEE80211_SMPS_AUTOMATIC: स्वतःmatic
 * @IEEE80211_SMPS_OFF: off
 * @IEEE80211_SMPS_STATIC: अटल
 * @IEEE80211_SMPS_DYNAMIC: dynamic
 * @IEEE80211_SMPS_NUM_MODES: पूर्णांकernal, करोn't use
 */
क्रमागत ieee80211_smps_mode अणु
	IEEE80211_SMPS_AUTOMATIC,
	IEEE80211_SMPS_OFF,
	IEEE80211_SMPS_STATIC,
	IEEE80211_SMPS_DYNAMIC,

	/* keep last */
	IEEE80211_SMPS_NUM_MODES,
पूर्ण;

/**
 * काष्ठा ieee80211_conf - configuration of the device
 *
 * This काष्ठा indicates how the driver shall configure the hardware.
 *
 * @flags: configuration flags defined above
 *
 * @listen_पूर्णांकerval: listen पूर्णांकerval in units of beacon पूर्णांकerval
 * @ps_dtim_period: The DTIM period of the AP we're connected to, क्रम use
 *	in घातer saving. Power saving will not be enabled until a beacon
 *	has been received and the DTIM period is known.
 * @dynamic_ps_समयout: The dynamic घातersave समयout (in ms), see the
 *	घातersave करोcumentation below. This variable is valid only when
 *	the CONF_PS flag is set.
 *
 * @घातer_level: requested transmit घातer (in dBm), backward compatibility
 *	value only that is set to the minimum of all पूर्णांकerfaces
 *
 * @chandef: the channel definition to tune to
 * @radar_enabled: whether radar detection is enabled
 *
 * @दीर्घ_frame_max_tx_count: Maximum number of transmissions क्रम a "long" frame
 *	(a frame not RTS रक्षित), called "dot11LongRetryLimit" in 802.11,
 *	but actually means the number of transmissions not the number of retries
 * @लघु_frame_max_tx_count: Maximum number of transmissions क्रम a "short"
 *	frame, called "dot11ShortRetryLimit" in 802.11, but actually means the
 *	number of transmissions not the number of retries
 *
 * @smps_mode: spatial multiplexing घातersave mode; note that
 *	%IEEE80211_SMPS_STATIC is used when the device is not
 *	configured क्रम an HT channel.
 *	Note that this is only valid अगर channel contexts are not used,
 *	otherwise each channel context has the number of chains listed.
 */
काष्ठा ieee80211_conf अणु
	u32 flags;
	पूर्णांक घातer_level, dynamic_ps_समयout;

	u16 listen_पूर्णांकerval;
	u8 ps_dtim_period;

	u8 दीर्घ_frame_max_tx_count, लघु_frame_max_tx_count;

	काष्ठा cfg80211_chan_def chandef;
	bool radar_enabled;
	क्रमागत ieee80211_smps_mode smps_mode;
पूर्ण;

/**
 * काष्ठा ieee80211_channel_चयन - holds the channel चयन data
 *
 * The inक्रमmation provided in this काष्ठाure is required क्रम channel चयन
 * operation.
 *
 * @बारtamp: value in microseconds of the 64-bit Time Synchronization
 *	Function (TSF) समयr when the frame containing the channel चयन
 *	announcement was received. This is simply the rx.maस_समय parameter
 *	the driver passed पूर्णांकo mac80211.
 * @device_बारtamp: arbitrary बारtamp क्रम the device, this is the
 *	rx.device_बारtamp parameter the driver passed to mac80211.
 * @block_tx: Indicates whether transmission must be blocked beक्रमe the
 *	scheduled channel चयन, as indicated by the AP.
 * @chandef: the new channel to चयन to
 * @count: the number of TBTT's until the channel चयन event
 * @delay: maximum delay between the समय the AP transmitted the last beacon in
  *	current channel and the expected समय of the first beacon in the new
  *	channel, expressed in TU.
 */
काष्ठा ieee80211_channel_चयन अणु
	u64 बारtamp;
	u32 device_बारtamp;
	bool block_tx;
	काष्ठा cfg80211_chan_def chandef;
	u8 count;
	u32 delay;
पूर्ण;

/**
 * क्रमागत ieee80211_vअगर_flags - भव पूर्णांकerface flags
 *
 * @IEEE80211_VIF_BEACON_FILTER: the device perक्रमms beacon filtering
 *	on this भव पूर्णांकerface to aव्योम unnecessary CPU wakeups
 * @IEEE80211_VIF_SUPPORTS_CQM_RSSI: the device can करो connection quality
 *	monitoring on this भव पूर्णांकerface -- i.e. it can monitor
 *	connection quality related parameters, such as the RSSI level and
 *	provide notअगरications अगर configured trigger levels are reached.
 * @IEEE80211_VIF_SUPPORTS_UAPSD: The device can करो U-APSD क्रम this
 *	पूर्णांकerface. This flag should be set during पूर्णांकerface addition,
 *	but may be set/cleared as late as authentication to an AP. It is
 *	only valid क्रम managed/station mode पूर्णांकerfaces.
 * @IEEE80211_VIF_GET_NOA_UPDATE: request to handle NOA attributes
 *	and send P2P_PS notअगरication to the driver अगर NOA changed, even
 *	this is not pure P2P vअगर.
 */
क्रमागत ieee80211_vअगर_flags अणु
	IEEE80211_VIF_BEACON_FILTER		= BIT(0),
	IEEE80211_VIF_SUPPORTS_CQM_RSSI		= BIT(1),
	IEEE80211_VIF_SUPPORTS_UAPSD		= BIT(2),
	IEEE80211_VIF_GET_NOA_UPDATE		= BIT(3),
पूर्ण;


/**
 * क्रमागत ieee80211_offload_flags - भव पूर्णांकerface offload flags
 *
 * @IEEE80211_OFFLOAD_ENCAP_ENABLED: tx encapsulation offload is enabled
 *	The driver supports sending frames passed as 802.3 frames by mac80211.
 *	It must also support sending 802.11 packets क्रम the same पूर्णांकerface.
 * @IEEE80211_OFFLOAD_ENCAP_4ADDR: support 4-address mode encapsulation offload
 * @IEEE80211_OFFLOAD_DECAP_ENABLED: rx encapsulation offload is enabled
 *	The driver supports passing received 802.11 frames as 802.3 frames to
 *	mac80211.
 */

क्रमागत ieee80211_offload_flags अणु
	IEEE80211_OFFLOAD_ENCAP_ENABLED		= BIT(0),
	IEEE80211_OFFLOAD_ENCAP_4ADDR		= BIT(1),
	IEEE80211_OFFLOAD_DECAP_ENABLED		= BIT(2),
पूर्ण;

/**
 * काष्ठा ieee80211_vअगर - per-पूर्णांकerface data
 *
 * Data in this काष्ठाure is continually present क्रम driver
 * use during the lअगरe of a भव पूर्णांकerface.
 *
 * @type: type of this भव पूर्णांकerface
 * @bss_conf: BSS configuration क्रम this पूर्णांकerface, either our own
 *	or the BSS we're associated to
 * @addr: address of this पूर्णांकerface
 * @p2p: indicates whether this AP or STA पूर्णांकerface is a p2p
 *	पूर्णांकerface, i.e. a GO or p2p-sta respectively
 * @csa_active: marks whether a channel चयन is going on. Internally it is
 *	ग_लिखो-रक्षित by sdata_lock and local->mtx so holding either is fine
 *	क्रम पढ़ो access.
 * @mu_mimo_owner: indicates पूर्णांकerface owns MU-MIMO capability
 * @driver_flags: flags/capabilities the driver has क्रम this पूर्णांकerface,
 *	these need to be set (or cleared) when the पूर्णांकerface is added
 *	or, अगर supported by the driver, the पूर्णांकerface type is changed
 *	at runसमय, mac80211 will never touch this field
 * @offloaad_flags: hardware offload capabilities/flags क्रम this पूर्णांकerface.
 *	These are initialized by mac80211 beक्रमe calling .add_पूर्णांकerface,
 *	.change_पूर्णांकerface or .update_vअगर_offload and updated by the driver
 *	within these ops, based on supported features or runसमय change
 *	restrictions.
 * @hw_queue: hardware queue क्रम each AC
 * @cab_queue: content-after-beacon (DTIM beacon really) queue, AP mode only
 * @chanctx_conf: The channel context this पूर्णांकerface is asचिन्हित to, or %शून्य
 *	when it is not asचिन्हित. This poपूर्णांकer is RCU-रक्षित due to the TX
 *	path needing to access it; even though the netdev carrier will always
 *	be off when it is %शून्य there can still be races and packets could be
 *	processed after it चयनes back to %शून्य.
 * @debugfs_dir: debugfs dentry, can be used by drivers to create own per
 *	पूर्णांकerface debug files. Note that it will be शून्य क्रम the भव
 *	monitor पूर्णांकerface (अगर that is requested.)
 * @probe_req_reg: probe requests should be reported to mac80211 क्रम this
 *	पूर्णांकerface.
 * @rx_mcast_action_reg: multicast Action frames should be reported to mac80211
 *	क्रम this पूर्णांकerface.
 * @drv_priv: data area क्रम driver use, will always be aligned to
 *	माप(व्योम \*).
 * @txq: the multicast data TX queue (अगर driver uses the TXQ असलtraction)
 * @txqs_stopped: per AC flag to indicate that पूर्णांकermediate TXQs are stopped,
 *	रक्षित by fq->lock.
 * @offload_flags: 802.3 -> 802.11 enapsulation offload flags, see
 *	&क्रमागत ieee80211_offload_flags.
 */
काष्ठा ieee80211_vअगर अणु
	क्रमागत nl80211_अगरtype type;
	काष्ठा ieee80211_bss_conf bss_conf;
	u8 addr[ETH_ALEN] __aligned(2);
	bool p2p;
	bool csa_active;
	bool mu_mimo_owner;

	u8 cab_queue;
	u8 hw_queue[IEEE80211_NUM_ACS];

	काष्ठा ieee80211_txq *txq;

	काष्ठा ieee80211_chanctx_conf __rcu *chanctx_conf;

	u32 driver_flags;
	u32 offload_flags;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	काष्ठा dentry *debugfs_dir;
#पूर्ण_अगर

	bool probe_req_reg;
	bool rx_mcast_action_reg;

	bool txqs_stopped[IEEE80211_NUM_ACS];

	/* must be last */
	u8 drv_priv[] __aligned(माप(व्योम *));
पूर्ण;

अटल अंतरभूत bool ieee80211_vअगर_is_mesh(काष्ठा ieee80211_vअगर *vअगर)
अणु
#अगर_घोषित CONFIG_MAC80211_MESH
	वापस vअगर->type == NL80211_IFTYPE_MESH_POINT;
#पूर्ण_अगर
	वापस false;
पूर्ण

/**
 * wdev_to_ieee80211_vअगर - वापस a vअगर काष्ठा from a wdev
 * @wdev: the wdev to get the vअगर क्रम
 *
 * This can be used by mac80211 drivers with direct cfg80211 APIs
 * (like the venकरोr commands) that get a wdev.
 *
 * Note that this function may वापस %शून्य अगर the given wdev isn't
 * associated with a vअगर that the driver knows about (e.g. monitor
 * or AP_VLAN पूर्णांकerfaces.)
 */
काष्ठा ieee80211_vअगर *wdev_to_ieee80211_vअगर(काष्ठा wireless_dev *wdev);

/**
 * ieee80211_vअगर_to_wdev - वापस a wdev काष्ठा from a vअगर
 * @vअगर: the vअगर to get the wdev क्रम
 *
 * This can be used by mac80211 drivers with direct cfg80211 APIs
 * (like the venकरोr commands) that needs to get the wdev क्रम a vअगर.
 * This can also be useful to get the netdev associated to a vअगर.
 */
काष्ठा wireless_dev *ieee80211_vअगर_to_wdev(काष्ठा ieee80211_vअगर *vअगर);

/**
 * क्रमागत ieee80211_key_flags - key flags
 *
 * These flags are used क्रम communication about keys between the driver
 * and mac80211, with the @flags parameter of &काष्ठा ieee80211_key_conf.
 *
 * @IEEE80211_KEY_FLAG_GENERATE_IV: This flag should be set by the
 *	driver to indicate that it requires IV generation क्रम this
 *	particular key. Setting this flag करोes not necessarily mean that SKBs
 *	will have sufficient tailroom क्रम ICV or MIC.
 * @IEEE80211_KEY_FLAG_GENERATE_MMIC: This flag should be set by
 *	the driver क्रम a TKIP key अगर it requires Michael MIC
 *	generation in software.
 * @IEEE80211_KEY_FLAG_PAIRWISE: Set by mac80211, this flag indicates
 *	that the key is pairwise rather then a shared key.
 * @IEEE80211_KEY_FLAG_SW_MGMT_TX: This flag should be set by the driver क्रम a
 *	CCMP/GCMP key अगर it requires CCMP/GCMP encryption of management frames
 *	(MFP) to be करोne in software.
 * @IEEE80211_KEY_FLAG_PUT_IV_SPACE: This flag should be set by the driver
 *	अगर space should be prepared क्रम the IV, but the IV
 *	itself should not be generated. Do not set together with
 *	@IEEE80211_KEY_FLAG_GENERATE_IV on the same key. Setting this flag करोes
 *	not necessarily mean that SKBs will have sufficient tailroom क्रम ICV or
 *	MIC.
 * @IEEE80211_KEY_FLAG_RX_MGMT: This key will be used to decrypt received
 *	management frames. The flag can help drivers that have a hardware
 *	crypto implementation that करोesn't deal with management frames
 *	properly by allowing them to not upload the keys to hardware and
 *	fall back to software crypto. Note that this flag deals only with
 *	RX, अगर your crypto engine can't deal with TX you can also set the
 *	%IEEE80211_KEY_FLAG_SW_MGMT_TX flag to encrypt such frames in SW.
 * @IEEE80211_KEY_FLAG_GENERATE_IV_MGMT: This flag should be set by the
 *	driver क्रम a CCMP/GCMP key to indicate that is requires IV generation
 *	only क्रम management frames (MFP).
 * @IEEE80211_KEY_FLAG_RESERVE_TAILROOM: This flag should be set by the
 *	driver क्रम a key to indicate that sufficient tailroom must always
 *	be reserved क्रम ICV or MIC, even when HW encryption is enabled.
 * @IEEE80211_KEY_FLAG_PUT_MIC_SPACE: This flag should be set by the driver क्रम
 *	a TKIP key अगर it only requires MIC space. Do not set together with
 *	@IEEE80211_KEY_FLAG_GENERATE_MMIC on the same key.
 * @IEEE80211_KEY_FLAG_NO_AUTO_TX: Key needs explicit Tx activation.
 * @IEEE80211_KEY_FLAG_GENERATE_MMIE: This flag should be set by the driver
 *	क्रम a AES_CMAC key to indicate that it requires sequence number
 *	generation only
 */
क्रमागत ieee80211_key_flags अणु
	IEEE80211_KEY_FLAG_GENERATE_IV_MGMT	= BIT(0),
	IEEE80211_KEY_FLAG_GENERATE_IV		= BIT(1),
	IEEE80211_KEY_FLAG_GENERATE_MMIC	= BIT(2),
	IEEE80211_KEY_FLAG_PAIRWISE		= BIT(3),
	IEEE80211_KEY_FLAG_SW_MGMT_TX		= BIT(4),
	IEEE80211_KEY_FLAG_PUT_IV_SPACE		= BIT(5),
	IEEE80211_KEY_FLAG_RX_MGMT		= BIT(6),
	IEEE80211_KEY_FLAG_RESERVE_TAILROOM	= BIT(7),
	IEEE80211_KEY_FLAG_PUT_MIC_SPACE	= BIT(8),
	IEEE80211_KEY_FLAG_NO_AUTO_TX		= BIT(9),
	IEEE80211_KEY_FLAG_GENERATE_MMIE	= BIT(10),
पूर्ण;

/**
 * काष्ठा ieee80211_key_conf - key inक्रमmation
 *
 * This key inक्रमmation is given by mac80211 to the driver by
 * the set_key() callback in &काष्ठा ieee80211_ops.
 *
 * @hw_key_idx: To be set by the driver, this is the key index the driver
 *	wants to be given when a frame is transmitted and needs to be
 *	encrypted in hardware.
 * @cipher: The key's cipher suite selector.
 * @tx_pn: PN used क्रम TX keys, may be used by the driver as well अगर it
 *	needs to करो software PN assignment by itself (e.g. due to TSO)
 * @flags: key flags, see &क्रमागत ieee80211_key_flags.
 * @keyidx: the key index (0-3)
 * @keylen: key material length
 * @key: key material. For ALG_TKIP the key is encoded as a 256-bit (32 byte)
 * 	data block:
 * 	- Temporal Encryption Key (128 bits)
 * 	- Temporal Authenticator Tx MIC Key (64 bits)
 * 	- Temporal Authenticator Rx MIC Key (64 bits)
 * @icv_len: The ICV length क्रम this key type
 * @iv_len: The IV length क्रम this key type
 */
काष्ठा ieee80211_key_conf अणु
	atomic64_t tx_pn;
	u32 cipher;
	u8 icv_len;
	u8 iv_len;
	u8 hw_key_idx;
	s8 keyidx;
	u16 flags;
	u8 keylen;
	u8 key[];
पूर्ण;

#घोषणा IEEE80211_MAX_PN_LEN	16

#घोषणा TKIP_PN_TO_IV16(pn) ((u16)(pn & 0xffff))
#घोषणा TKIP_PN_TO_IV32(pn) ((u32)((pn >> 16) & 0xffffffff))

/**
 * काष्ठा ieee80211_key_seq - key sequence counter
 *
 * @tkip: TKIP data, containing IV32 and IV16 in host byte order
 * @ccmp: PN data, most signअगरicant byte first (big endian,
 *	reverse order than in packet)
 * @aes_cmac: PN data, most signअगरicant byte first (big endian,
 *	reverse order than in packet)
 * @aes_gmac: PN data, most signअगरicant byte first (big endian,
 *	reverse order than in packet)
 * @gcmp: PN data, most signअगरicant byte first (big endian,
 *	reverse order than in packet)
 * @hw: data क्रम HW-only (e.g. cipher scheme) keys
 */
काष्ठा ieee80211_key_seq अणु
	जोड़ अणु
		काष्ठा अणु
			u32 iv32;
			u16 iv16;
		पूर्ण tkip;
		काष्ठा अणु
			u8 pn[6];
		पूर्ण ccmp;
		काष्ठा अणु
			u8 pn[6];
		पूर्ण aes_cmac;
		काष्ठा अणु
			u8 pn[6];
		पूर्ण aes_gmac;
		काष्ठा अणु
			u8 pn[6];
		पूर्ण gcmp;
		काष्ठा अणु
			u8 seq[IEEE80211_MAX_PN_LEN];
			u8 seq_len;
		पूर्ण hw;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा ieee80211_cipher_scheme - cipher scheme
 *
 * This काष्ठाure contains a cipher scheme inक्रमmation defining
 * the secure packet crypto handling.
 *
 * @cipher: a cipher suite selector
 * @अगरtype: a cipher अगरtype bit mask indicating an allowed cipher usage
 * @hdr_len: a length of a security header used the cipher
 * @pn_len: a length of a packet number in the security header
 * @pn_off: an offset of pn from the beginning of the security header
 * @key_idx_off: an offset of key index byte in the security header
 * @key_idx_mask: a bit mask of key_idx bits
 * @key_idx_shअगरt: a bit shअगरt needed to get key_idx
 *     key_idx value calculation:
 *      (sec_header_base[key_idx_off] & key_idx_mask) >> key_idx_shअगरt
 * @mic_len: a mic length in bytes
 */
काष्ठा ieee80211_cipher_scheme अणु
	u32 cipher;
	u16 अगरtype;
	u8 hdr_len;
	u8 pn_len;
	u8 pn_off;
	u8 key_idx_off;
	u8 key_idx_mask;
	u8 key_idx_shअगरt;
	u8 mic_len;
पूर्ण;

/**
 * क्रमागत set_key_cmd - key command
 *
 * Used with the set_key() callback in &काष्ठा ieee80211_ops, this
 * indicates whether a key is being हटाओd or added.
 *
 * @SET_KEY: a key is set
 * @DISABLE_KEY: a key must be disabled
 */
क्रमागत set_key_cmd अणु
	SET_KEY, DISABLE_KEY,
पूर्ण;

/**
 * क्रमागत ieee80211_sta_state - station state
 *
 * @IEEE80211_STA_NOTEXIST: station करोesn't exist at all,
 *	this is a special state क्रम add/हटाओ transitions
 * @IEEE80211_STA_NONE: station exists without special state
 * @IEEE80211_STA_AUTH: station is authenticated
 * @IEEE80211_STA_ASSOC: station is associated
 * @IEEE80211_STA_AUTHORIZED: station is authorized (802.1X)
 */
क्रमागत ieee80211_sta_state अणु
	/* NOTE: These need to be ordered correctly! */
	IEEE80211_STA_NOTEXIST,
	IEEE80211_STA_NONE,
	IEEE80211_STA_AUTH,
	IEEE80211_STA_ASSOC,
	IEEE80211_STA_AUTHORIZED,
पूर्ण;

/**
 * क्रमागत ieee80211_sta_rx_bandwidth - station RX bandwidth
 * @IEEE80211_STA_RX_BW_20: station can only receive 20 MHz
 * @IEEE80211_STA_RX_BW_40: station can receive up to 40 MHz
 * @IEEE80211_STA_RX_BW_80: station can receive up to 80 MHz
 * @IEEE80211_STA_RX_BW_160: station can receive up to 160 MHz
 *	(including 80+80 MHz)
 *
 * Implementation note: 20 must be zero to be initialized
 *	correctly, the values must be sorted.
 */
क्रमागत ieee80211_sta_rx_bandwidth अणु
	IEEE80211_STA_RX_BW_20 = 0,
	IEEE80211_STA_RX_BW_40,
	IEEE80211_STA_RX_BW_80,
	IEEE80211_STA_RX_BW_160,
पूर्ण;

/**
 * काष्ठा ieee80211_sta_rates - station rate selection table
 *
 * @rcu_head: RCU head used क्रम मुक्तing the table on update
 * @rate: transmit rates/flags to be used by शेष.
 *	Overriding entries per-packet is possible by using cb tx control.
 */
काष्ठा ieee80211_sta_rates अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा अणु
		s8 idx;
		u8 count;
		u8 count_cts;
		u8 count_rts;
		u16 flags;
	पूर्ण rate[IEEE80211_TX_RATE_TABLE_SIZE];
पूर्ण;

/**
 * काष्ठा ieee80211_sta_txpwr - station txघातer configuration
 *
 * Used to configure txघातer क्रम station.
 *
 * @घातer: indicates the tx घातer, in dBm, to be used when sending data frames
 *	to the STA.
 * @type: In particular अगर TPC %type is NL80211_TX_POWER_LIMITED then tx घातer
 *	will be less than or equal to specअगरied from userspace, whereas अगर TPC
 *	%type is NL80211_TX_POWER_AUTOMATIC then it indicates शेष tx घातer.
 *	NL80211_TX_POWER_FIXED is not a valid configuration option क्रम
 *	per peer TPC.
 */
काष्ठा ieee80211_sta_txpwr अणु
	s16 घातer;
	क्रमागत nl80211_tx_घातer_setting type;
पूर्ण;

/**
 * काष्ठा ieee80211_sta - station table entry
 *
 * A station table entry represents a station we are possibly
 * communicating with. Since stations are RCU-managed in
 * mac80211, any ieee80211_sta poपूर्णांकer you get access to must
 * either be रक्षित by rcu_पढ़ो_lock() explicitly or implicitly,
 * or you must take good care to not use such a poपूर्णांकer after a
 * call to your sta_हटाओ callback that हटाओd it.
 *
 * @addr: MAC address
 * @aid: AID we asचिन्हित to the station अगर we're an AP
 * @supp_rates: Biपंचांगap of supported rates (per band)
 * @ht_cap: HT capabilities of this STA; restricted to our own capabilities
 * @vht_cap: VHT capabilities of this STA; restricted to our own capabilities
 * @he_cap: HE capabilities of this STA
 * @he_6ghz_capa: on 6 GHz, holds the HE 6 GHz band capabilities
 * @max_rx_aggregation_subframes: maximal amount of frames in a single AMPDU
 *	that this station is allowed to transmit to us.
 *	Can be modअगरied by driver.
 * @wme: indicates whether the STA supports QoS/WME (अगर local devices करोes,
 *	otherwise always false)
 * @drv_priv: data area क्रम driver use, will always be aligned to
 *	माप(व्योम \*), size is determined in hw inक्रमmation.
 * @uapsd_queues: biपंचांगap of queues configured क्रम uapsd. Only valid
 *	अगर wme is supported. The bits order is like in
 *	IEEE80211_WMM_IE_STA_QOSINFO_AC_*.
 * @max_sp: max Service Period. Only valid अगर wme is supported.
 * @bandwidth: current bandwidth the station can receive with
 * @rx_nss: in HT/VHT, the maximum number of spatial streams the
 *	station can receive at the moment, changed by operating mode
 *	notअगरications and capabilities. The value is only valid after
 *	the station moves to associated state.
 * @smps_mode: current SMPS mode (off, अटल or dynamic)
 * @rates: rate control selection table
 * @tdls: indicates whether the STA is a TDLS peer
 * @tdls_initiator: indicates the STA is an initiator of the TDLS link. Only
 *	valid अगर the STA is a TDLS peer in the first place.
 * @mfp: indicates whether the STA uses management frame protection or not.
 * @max_amsdu_subframes: indicates the maximal number of MSDUs in a single
 *	A-MSDU. Taken from the Extended Capabilities element. 0 means
 *	unlimited.
 * @support_p2p_ps: indicates whether the STA supports P2P PS mechanism or not.
 * @max_rc_amsdu_len: Maximum A-MSDU size in bytes recommended by rate control.
 * @max_tid_amsdu_len: Maximum A-MSDU size in bytes क्रम this TID
 * @txpwr: the station tx घातer configuration
 * @txq: per-TID data TX queues (अगर driver uses the TXQ असलtraction); note that
 *	the last entry (%IEEE80211_NUM_TIDS) is used क्रम non-data frames
 */
काष्ठा ieee80211_sta अणु
	u32 supp_rates[NUM_NL80211_BANDS];
	u8 addr[ETH_ALEN];
	u16 aid;
	काष्ठा ieee80211_sta_ht_cap ht_cap;
	काष्ठा ieee80211_sta_vht_cap vht_cap;
	काष्ठा ieee80211_sta_he_cap he_cap;
	काष्ठा ieee80211_he_6ghz_capa he_6ghz_capa;
	u16 max_rx_aggregation_subframes;
	bool wme;
	u8 uapsd_queues;
	u8 max_sp;
	u8 rx_nss;
	क्रमागत ieee80211_sta_rx_bandwidth bandwidth;
	क्रमागत ieee80211_smps_mode smps_mode;
	काष्ठा ieee80211_sta_rates __rcu *rates;
	bool tdls;
	bool tdls_initiator;
	bool mfp;
	u8 max_amsdu_subframes;

	/**
	 * @max_amsdu_len:
	 * indicates the maximal length of an A-MSDU in bytes.
	 * This field is always valid क्रम packets with a VHT preamble.
	 * For packets with a HT preamble, additional limits apply:
	 *
	 * * If the skb is transmitted as part of a BA agreement, the
	 *   A-MSDU maximal size is min(max_amsdu_len, 4065) bytes.
	 * * If the skb is not part of a BA agreement, the A-MSDU maximal
	 *   size is min(max_amsdu_len, 7935) bytes.
	 *
	 * Both additional HT limits must be enक्रमced by the low level
	 * driver. This is defined by the spec (IEEE 802.11-2012 section
	 * 8.3.2.2 NOTE 2).
	 */
	u16 max_amsdu_len;
	bool support_p2p_ps;
	u16 max_rc_amsdu_len;
	u16 max_tid_amsdu_len[IEEE80211_NUM_TIDS];
	काष्ठा ieee80211_sta_txpwr txpwr;

	काष्ठा ieee80211_txq *txq[IEEE80211_NUM_TIDS + 1];

	/* must be last */
	u8 drv_priv[] __aligned(माप(व्योम *));
पूर्ण;

/**
 * क्रमागत sta_notअगरy_cmd - sta notअगरy command
 *
 * Used with the sta_notअगरy() callback in &काष्ठा ieee80211_ops, this
 * indicates अगर an associated station made a घातer state transition.
 *
 * @STA_NOTIFY_SLEEP: a station is now sleeping
 * @STA_NOTIFY_AWAKE: a sleeping station woke up
 */
क्रमागत sta_notअगरy_cmd अणु
	STA_NOTIFY_SLEEP, STA_NOTIFY_AWAKE,
पूर्ण;

/**
 * काष्ठा ieee80211_tx_control - TX control data
 *
 * @sta: station table entry, this sta poपूर्णांकer may be शून्य and
 * 	it is not allowed to copy the poपूर्णांकer, due to RCU.
 */
काष्ठा ieee80211_tx_control अणु
	काष्ठा ieee80211_sta *sta;
पूर्ण;

/**
 * काष्ठा ieee80211_txq - Software पूर्णांकermediate tx queue
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @sta: station table entry, %शून्य क्रम per-vअगर queue
 * @tid: the TID क्रम this queue (unused क्रम per-vअगर queue),
 *	%IEEE80211_NUM_TIDS क्रम non-data (अगर enabled)
 * @ac: the AC क्रम this queue
 * @drv_priv: driver निजी area, sized by hw->txq_data_size
 *
 * The driver can obtain packets from this queue by calling
 * ieee80211_tx_dequeue().
 */
काष्ठा ieee80211_txq अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_sta *sta;
	u8 tid;
	u8 ac;

	/* must be last */
	u8 drv_priv[] __aligned(माप(व्योम *));
पूर्ण;

/**
 * क्रमागत ieee80211_hw_flags - hardware flags
 *
 * These flags are used to indicate hardware capabilities to
 * the stack. Generally, flags here should have their meaning
 * करोne in a way that the simplest hardware करोesn't need setting
 * any particular flags. There are some exceptions to this rule,
 * however, so you are advised to review these flags carefully.
 *
 * @IEEE80211_HW_HAS_RATE_CONTROL:
 *	The hardware or firmware includes rate control, and cannot be
 *	controlled by the stack. As such, no rate control algorithm
 *	should be instantiated, and the TX rate reported to userspace
 *	will be taken from the TX status instead of the rate control
 *	algorithm.
 *	Note that this requires that the driver implement a number of
 *	callbacks so it has the correct inक्रमmation, it needs to have
 *	the @set_rts_threshold callback and must look at the BSS config
 *	@use_cts_prot क्रम G/N protection, @use_लघु_slot क्रम slot
 *	timing in 2.4 GHz and @use_लघु_preamble क्रम preambles क्रम
 *	CCK frames.
 *
 * @IEEE80211_HW_RX_INCLUDES_FCS:
 *	Indicates that received frames passed to the stack include
 *	the FCS at the end.
 *
 * @IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING:
 *	Some wireless LAN chipsets buffer broadcast/multicast frames
 *	क्रम घातer saving stations in the hardware/firmware and others
 *	rely on the host प्रणाली क्रम such buffering. This option is used
 *	to configure the IEEE 802.11 upper layer to buffer broadcast and
 *	multicast frames when there are घातer saving stations so that
 *	the driver can fetch them with ieee80211_get_buffered_bc().
 *
 * @IEEE80211_HW_SIGNAL_UNSPEC:
 *	Hardware can provide संकेत values but we करोn't know its units. We
 *	expect values between 0 and @max_संकेत.
 *	If possible please provide dB or dBm instead.
 *
 * @IEEE80211_HW_SIGNAL_DBM:
 *	Hardware gives संकेत values in dBm, decibel dअगरference from
 *	one milliwatt. This is the preferred method since it is standardized
 *	between dअगरferent devices. @max_संकेत करोes not need to be set.
 *
 * @IEEE80211_HW_SPECTRUM_MGMT:
 * 	Hardware supports spectrum management defined in 802.11h
 * 	Measurement, Channel Switch, Quieting, TPC
 *
 * @IEEE80211_HW_AMPDU_AGGREGATION:
 *	Hardware supports 11n A-MPDU aggregation.
 *
 * @IEEE80211_HW_SUPPORTS_PS:
 *	Hardware has घातer save support (i.e. can go to sleep).
 *
 * @IEEE80211_HW_PS_शून्यFUNC_STACK:
 *	Hardware requires nullfunc frame handling in stack, implies
 *	stack support क्रम dynamic PS.
 *
 * @IEEE80211_HW_SUPPORTS_DYNAMIC_PS:
 *	Hardware has support क्रम dynamic PS.
 *
 * @IEEE80211_HW_MFP_CAPABLE:
 *	Hardware supports management frame protection (MFP, IEEE 802.11w).
 *
 * @IEEE80211_HW_REPORTS_TX_ACK_STATUS:
 *	Hardware can provide ack status reports of Tx frames to
 *	the stack.
 *
 * @IEEE80211_HW_CONNECTION_MONITOR:
 *	The hardware perक्रमms its own connection monitoring, including
 *	periodic keep-alives to the AP and probing the AP on beacon loss.
 *
 * @IEEE80211_HW_NEED_DTIM_BEFORE_ASSOC:
 *	This device needs to get data from beacon beक्रमe association (i.e.
 *	dtim_period).
 *
 * @IEEE80211_HW_SUPPORTS_PER_STA_GTK: The device's crypto engine supports
 *	per-station GTKs as used by IBSS RSN or during fast transition. If
 *	the device करोesn't support per-station GTKs, but can be asked not
 *	to decrypt group addressed frames, then IBSS RSN support is still
 *	possible but software crypto will be used. Advertise the wiphy flag
 *	only in that हाल.
 *
 * @IEEE80211_HW_AP_LINK_PS: When operating in AP mode the device
 *	स्वतःnomously manages the PS status of connected stations. When
 *	this flag is set mac80211 will not trigger PS mode क्रम connected
 *	stations based on the PM bit of incoming frames.
 *	Use ieee80211_start_ps()/ieee8021_end_ps() to manually configure
 *	the PS mode of connected stations.
 *
 * @IEEE80211_HW_TX_AMPDU_SETUP_IN_HW: The device handles TX A-MPDU session
 *	setup strictly in HW. mac80211 should not attempt to करो this in
 *	software.
 *
 * @IEEE80211_HW_WANT_MONITOR_VIF: The driver would like to be inक्रमmed of
 *	a भव monitor पूर्णांकerface when monitor पूर्णांकerfaces are the only
 *	active पूर्णांकerfaces.
 *
 * @IEEE80211_HW_NO_AUTO_VIF: The driver would like क्रम no wlanX to
 *	be created.  It is expected user-space will create vअगरs as
 *	desired (and thus have them named as desired).
 *
 * @IEEE80211_HW_SW_CRYPTO_CONTROL: The driver wants to control which of the
 *	crypto algorithms can be करोne in software - so करोn't स्वतःmatically
 *	try to fall back to it अगर hardware crypto fails, but करो so only अगर
 *	the driver वापसs 1. This also क्रमces the driver to advertise its
 *	supported cipher suites.
 *
 * @IEEE80211_HW_SUPPORT_FAST_XMIT: The driver/hardware supports fast-xmit,
 *	this currently requires only the ability to calculate the duration
 *	क्रम frames.
 *
 * @IEEE80211_HW_QUEUE_CONTROL: The driver wants to control per-पूर्णांकerface
 *	queue mapping in order to use dअगरferent queues (not just one per AC)
 *	क्रम dअगरferent भव पूर्णांकerfaces. See the करोc section on HW queue
 *	control क्रम more details.
 *
 * @IEEE80211_HW_SUPPORTS_RC_TABLE: The driver supports using a rate
 *	selection table provided by the rate control algorithm.
 *
 * @IEEE80211_HW_P2P_DEV_ADDR_FOR_INTF: Use the P2P Device address क्रम any
 *	P2P Interface. This will be honoured even अगर more than one पूर्णांकerface
 *	is supported.
 *
 * @IEEE80211_HW_TIMING_BEACON_ONLY: Use sync timing from beacon frames
 *	only, to allow getting TBTT of a DTIM beacon.
 *
 * @IEEE80211_HW_SUPPORTS_HT_CCK_RATES: Hardware supports mixing HT/CCK rates
 *	and can cope with CCK rates in an aggregation session (e.g. by not
 *	using aggregation क्रम such frames.)
 *
 * @IEEE80211_HW_CHANCTX_STA_CSA: Support 802.11h based channel-चयन (CSA)
 *	क्रम a single active channel जबतक using channel contexts. When support
 *	is not enabled the शेष action is to disconnect when getting the
 *	CSA frame.
 *
 * @IEEE80211_HW_SUPPORTS_CLONED_SKBS: The driver will never modअगरy the payload
 *	or tailroom of TX skbs without copying them first.
 *
 * @IEEE80211_HW_SINGLE_SCAN_ON_ALL_BANDS: The HW supports scanning on all bands
 *	in one command, mac80211 करोesn't have to run separate scans per band.
 *
 * @IEEE80211_HW_TDLS_WIDER_BW: The device/driver supports wider bandwidth
 *	than then BSS bandwidth क्रम a TDLS link on the base channel.
 *
 * @IEEE80211_HW_SUPPORTS_AMSDU_IN_AMPDU: The driver supports receiving A-MSDUs
 *	within A-MPDU.
 *
 * @IEEE80211_HW_BEACON_TX_STATUS: The device/driver provides TX status
 *	क्रम sent beacons.
 *
 * @IEEE80211_HW_NEEDS_UNIQUE_STA_ADDR: Hardware (or driver) requires that each
 *	station has a unique address, i.e. each station entry can be identअगरied
 *	by just its MAC address; this prevents, क्रम example, the same station
 *	from connecting to two भव AP पूर्णांकerfaces at the same समय.
 *
 * @IEEE80211_HW_SUPPORTS_REORDERING_BUFFER: Hardware (or driver) manages the
 *	reordering buffer पूर्णांकernally, guaranteeing mac80211 receives frames in
 *	order and करोes not need to manage its own reorder buffer or BA session
 *	समयout.
 *
 * @IEEE80211_HW_USES_RSS: The device uses RSS and thus requires parallel RX,
 *	which implies using per-CPU station statistics.
 *
 * @IEEE80211_HW_TX_AMSDU: Hardware (or driver) supports software aggregated
 *	A-MSDU frames. Requires software tx queueing and fast-xmit support.
 *	When not using minstrel/minstrel_ht rate control, the driver must
 *	limit the maximum A-MSDU size based on the current tx rate by setting
 *	max_rc_amsdu_len in काष्ठा ieee80211_sta.
 *
 * @IEEE80211_HW_TX_FRAG_LIST: Hardware (or driver) supports sending frag_list
 *	skbs, needed क्रम zero-copy software A-MSDU.
 *
 * @IEEE80211_HW_REPORTS_LOW_ACK: The driver (or firmware) reports low ack event
 *	by ieee80211_report_low_ack() based on its own algorithm. For such
 *	drivers, mac80211 packet loss mechanism will not be triggered and driver
 *	is completely depending on firmware event क्रम station kickout.
 *
 * @IEEE80211_HW_SUPPORTS_TX_FRAG: Hardware करोes fragmentation by itself.
 *	The stack will not करो fragmentation.
 *	The callback क्रम @set_frag_threshold should be set as well.
 *
 * @IEEE80211_HW_SUPPORTS_TDLS_BUFFER_STA: Hardware supports buffer STA on
 *	TDLS links.
 *
 * @IEEE80211_HW_DEAUTH_NEED_MGD_TX_PREP: The driver requires the
 *	mgd_prepare_tx() callback to be called beक्रमe transmission of a
 *	deauthentication frame in हाल the association was completed but no
 *	beacon was heard. This is required in multi-channel scenarios, where the
 *	भव पूर्णांकerface might not be given air समय क्रम the transmission of
 *	the frame, as it is not synced with the AP/P2P GO yet, and thus the
 *	deauthentication frame might not be transmitted.
 *
 * @IEEE80211_HW_DOESNT_SUPPORT_QOS_NDP: The driver (or firmware) करोesn't
 *	support QoS NDP क्रम AP probing - that's most likely a driver bug.
 *
 * @IEEE80211_HW_BUFF_MMPDU_TXQ: use the TXQ क्रम bufferable MMPDUs, this of
 *	course requires the driver to use TXQs to start with.
 *
 * @IEEE80211_HW_SUPPORTS_VHT_EXT_NSS_BW: (Hardware) rate control supports VHT
 *	extended NSS BW (करोt11VHTExtendedNSSBWCapable). This flag will be set अगर
 *	the selected rate control algorithm sets %RATE_CTRL_CAPA_VHT_EXT_NSS_BW
 *	but अगर the rate control is built-in then it must be set by the driver.
 *	See also the करोcumentation क्रम that flag.
 *
 * @IEEE80211_HW_STA_MMPDU_TXQ: use the extra non-TID per-station TXQ क्रम all
 *	MMPDUs on station पूर्णांकerfaces. This of course requires the driver to use
 *	TXQs to start with.
 *
 * @IEEE80211_HW_TX_STATUS_NO_AMPDU_LEN: Driver करोes not report accurate A-MPDU
 *	length in tx status inक्रमmation
 *
 * @IEEE80211_HW_SUPPORTS_MULTI_BSSID: Hardware supports multi BSSID
 *
 * @IEEE80211_HW_SUPPORTS_ONLY_HE_MULTI_BSSID: Hardware supports multi BSSID
 *	only क्रम HE APs. Applies अगर @IEEE80211_HW_SUPPORTS_MULTI_BSSID is set.
 *
 * @IEEE80211_HW_AMPDU_KEYBORDER_SUPPORT: The card and driver is only
 *	aggregating MPDUs with the same keyid, allowing mac80211 to keep Tx
 *	A-MPDU sessions active जबतक rekeying with Extended Key ID.
 *
 * @IEEE80211_HW_SUPPORTS_TX_ENCAP_OFFLOAD: Hardware supports tx encapsulation
 *	offload
 *
 * @IEEE80211_HW_SUPPORTS_RX_DECAP_OFFLOAD: Hardware supports rx decapsulation
 *	offload
 *
 * @IEEE80211_HW_SUPPORTS_CONC_MON_RX_DECAP: Hardware supports concurrent rx
 *	decapsulation offload and passing raw 802.11 frames क्रम monitor अगरace.
 *	If this is supported, the driver must pass both 802.3 frames क्रम real
 *	usage and 802.11 frames with %RX_FLAG_ONLY_MONITOR set क्रम monitor to
 *	the stack.
 *
 * @NUM_IEEE80211_HW_FLAGS: number of hardware flags, used क्रम sizing arrays
 */
क्रमागत ieee80211_hw_flags अणु
	IEEE80211_HW_HAS_RATE_CONTROL,
	IEEE80211_HW_RX_INCLUDES_FCS,
	IEEE80211_HW_HOST_BROADCAST_PS_BUFFERING,
	IEEE80211_HW_SIGNAL_UNSPEC,
	IEEE80211_HW_SIGNAL_DBM,
	IEEE80211_HW_NEED_DTIM_BEFORE_ASSOC,
	IEEE80211_HW_SPECTRUM_MGMT,
	IEEE80211_HW_AMPDU_AGGREGATION,
	IEEE80211_HW_SUPPORTS_PS,
	IEEE80211_HW_PS_शून्यFUNC_STACK,
	IEEE80211_HW_SUPPORTS_DYNAMIC_PS,
	IEEE80211_HW_MFP_CAPABLE,
	IEEE80211_HW_WANT_MONITOR_VIF,
	IEEE80211_HW_NO_AUTO_VIF,
	IEEE80211_HW_SW_CRYPTO_CONTROL,
	IEEE80211_HW_SUPPORT_FAST_XMIT,
	IEEE80211_HW_REPORTS_TX_ACK_STATUS,
	IEEE80211_HW_CONNECTION_MONITOR,
	IEEE80211_HW_QUEUE_CONTROL,
	IEEE80211_HW_SUPPORTS_PER_STA_GTK,
	IEEE80211_HW_AP_LINK_PS,
	IEEE80211_HW_TX_AMPDU_SETUP_IN_HW,
	IEEE80211_HW_SUPPORTS_RC_TABLE,
	IEEE80211_HW_P2P_DEV_ADDR_FOR_INTF,
	IEEE80211_HW_TIMING_BEACON_ONLY,
	IEEE80211_HW_SUPPORTS_HT_CCK_RATES,
	IEEE80211_HW_CHANCTX_STA_CSA,
	IEEE80211_HW_SUPPORTS_CLONED_SKBS,
	IEEE80211_HW_SINGLE_SCAN_ON_ALL_BANDS,
	IEEE80211_HW_TDLS_WIDER_BW,
	IEEE80211_HW_SUPPORTS_AMSDU_IN_AMPDU,
	IEEE80211_HW_BEACON_TX_STATUS,
	IEEE80211_HW_NEEDS_UNIQUE_STA_ADDR,
	IEEE80211_HW_SUPPORTS_REORDERING_BUFFER,
	IEEE80211_HW_USES_RSS,
	IEEE80211_HW_TX_AMSDU,
	IEEE80211_HW_TX_FRAG_LIST,
	IEEE80211_HW_REPORTS_LOW_ACK,
	IEEE80211_HW_SUPPORTS_TX_FRAG,
	IEEE80211_HW_SUPPORTS_TDLS_BUFFER_STA,
	IEEE80211_HW_DEAUTH_NEED_MGD_TX_PREP,
	IEEE80211_HW_DOESNT_SUPPORT_QOS_NDP,
	IEEE80211_HW_BUFF_MMPDU_TXQ,
	IEEE80211_HW_SUPPORTS_VHT_EXT_NSS_BW,
	IEEE80211_HW_STA_MMPDU_TXQ,
	IEEE80211_HW_TX_STATUS_NO_AMPDU_LEN,
	IEEE80211_HW_SUPPORTS_MULTI_BSSID,
	IEEE80211_HW_SUPPORTS_ONLY_HE_MULTI_BSSID,
	IEEE80211_HW_AMPDU_KEYBORDER_SUPPORT,
	IEEE80211_HW_SUPPORTS_TX_ENCAP_OFFLOAD,
	IEEE80211_HW_SUPPORTS_RX_DECAP_OFFLOAD,
	IEEE80211_HW_SUPPORTS_CONC_MON_RX_DECAP,

	/* keep last, obviously */
	NUM_IEEE80211_HW_FLAGS
पूर्ण;

/**
 * काष्ठा ieee80211_hw - hardware inक्रमmation and state
 *
 * This काष्ठाure contains the configuration and hardware
 * inक्रमmation क्रम an 802.11 PHY.
 *
 * @wiphy: This poपूर्णांकs to the &काष्ठा wiphy allocated क्रम this
 *	802.11 PHY. You must fill in the @perm_addr and @dev
 *	members of this काष्ठाure using SET_IEEE80211_DEV()
 *	and SET_IEEE80211_PERM_ADDR(). Additionally, all supported
 *	bands (with channels, bitrates) are रेजिस्टरed here.
 *
 * @conf: &काष्ठा ieee80211_conf, device configuration, करोn't use.
 *
 * @priv: poपूर्णांकer to निजी area that was allocated क्रम driver use
 *	aदीर्घ with this काष्ठाure.
 *
 * @flags: hardware flags, see &क्रमागत ieee80211_hw_flags.
 *
 * @extra_tx_headroom: headroom to reserve in each transmit skb
 *	क्रम use by the driver (e.g. क्रम transmit headers.)
 *
 * @extra_beacon_tailroom: tailroom to reserve in each beacon tx skb.
 *	Can be used by drivers to add extra IEs.
 *
 * @max_संकेत: Maximum value क्रम संकेत (rssi) in RX inक्रमmation, used
 *	only when @IEEE80211_HW_SIGNAL_UNSPEC or @IEEE80211_HW_SIGNAL_DB
 *
 * @max_listen_पूर्णांकerval: max listen पूर्णांकerval in units of beacon पूर्णांकerval
 *	that HW supports
 *
 * @queues: number of available hardware transmit queues क्रम
 *	data packets. WMM/QoS requires at least four, these
 *	queues need to have configurable access parameters.
 *
 * @rate_control_algorithm: rate control algorithm क्रम this hardware.
 *	If unset (शून्य), the शेष algorithm will be used. Must be
 *	set beक्रमe calling ieee80211_रेजिस्टर_hw().
 *
 * @vअगर_data_size: size (in bytes) of the drv_priv data area
 *	within &काष्ठा ieee80211_vअगर.
 * @sta_data_size: size (in bytes) of the drv_priv data area
 *	within &काष्ठा ieee80211_sta.
 * @chanctx_data_size: size (in bytes) of the drv_priv data area
 *	within &काष्ठा ieee80211_chanctx_conf.
 * @txq_data_size: size (in bytes) of the drv_priv data area
 *	within @काष्ठा ieee80211_txq.
 *
 * @max_rates: maximum number of alternate rate retry stages the hw
 *	can handle.
 * @max_report_rates: maximum number of alternate rate retry stages
 *	the hw can report back.
 * @max_rate_tries: maximum number of tries क्रम each stage
 *
 * @max_rx_aggregation_subframes: maximum buffer size (number of
 *	sub-frames) to be used क्रम A-MPDU block ack receiver
 *	aggregation.
 *	This is only relevant अगर the device has restrictions on the
 *	number of subframes, अगर it relies on mac80211 to करो reordering
 *	it shouldn't be set.
 *
 * @max_tx_aggregation_subframes: maximum number of subframes in an
 *	aggregate an HT/HE device will transmit. In HT AddBA we'll
 *	advertise a स्थिरant value of 64 as some older APs crash अगर
 *	the winकरोw size is smaller (an example is LinkSys WRT120N
 *	with FW v1.0.07 build 002 Jun 18 2012).
 *	For AddBA to HE capable peers this value will be used.
 *
 * @max_tx_fragments: maximum number of tx buffers per (A)-MSDU, sum
 *	of 1 + skb_shinfo(skb)->nr_frags क्रम each skb in the frag_list.
 *
 * @offchannel_tx_hw_queue: HW queue ID to use क्रम offchannel TX
 *	(अगर %IEEE80211_HW_QUEUE_CONTROL is set)
 *
 * @radiotap_mcs_details: lists which MCS inक्रमmation can the HW
 *	reports, by शेष it is set to _MCS, _GI and _BW but करोesn't
 *	include _FMT. Use %IEEE80211_RADIOTAP_MCS_HAVE_\* values, only
 *	adding _BW is supported today.
 *
 * @radiotap_vht_details: lists which VHT MCS inक्रमmation the HW reports,
 *	the शेष is _GI | _BANDWIDTH.
 *	Use the %IEEE80211_RADIOTAP_VHT_KNOWN_\* values.
 *
 * @radiotap_he: HE radiotap validity flags
 *
 * @radiotap_बारtamp: Inक्रमmation क्रम the radiotap बारtamp field; अगर the
 *	@units_pos member is set to a non-negative value then the बारtamp
 *	field will be added and populated from the &काष्ठा ieee80211_rx_status
 *	device_बारtamp.
 * @radiotap_बारtamp.units_pos: Must be set to a combination of a
 *	IEEE80211_RADIOTAP_TIMESTAMP_UNIT_* and a
 *	IEEE80211_RADIOTAP_TIMESTAMP_SPOS_* value.
 * @radiotap_बारtamp.accuracy: If non-negative, fills the accuracy in the
 *	radiotap field and the accuracy known flag will be set.
 *
 * @netdev_features: netdev features to be set in each netdev created
 *	from this HW. Note that not all features are usable with mac80211,
 *	other features will be rejected during HW registration.
 *
 * @uapsd_queues: This biपंचांगap is included in (re)association frame to indicate
 *	क्रम each access category अगर it is uAPSD trigger-enabled and delivery-
 *	enabled. Use IEEE80211_WMM_IE_STA_QOSINFO_AC_* to set this biपंचांगap.
 *	Each bit corresponds to dअगरferent AC. Value '1' in specअगरic bit means
 *	that corresponding AC is both trigger- and delivery-enabled. '0' means
 *	neither enabled.
 *
 * @uapsd_max_sp_len: maximum number of total buffered frames the WMM AP may
 *	deliver to a WMM STA during any Service Period triggered by the WMM STA.
 *	Use IEEE80211_WMM_IE_STA_QOSINFO_SP_* क्रम correct values.
 *
 * @n_cipher_schemes: a size of an array of cipher schemes definitions.
 * @cipher_schemes: a poपूर्णांकer to an array of cipher scheme definitions
 *	supported by HW.
 * @max_nan_de_entries: maximum number of न_अंक DE functions supported by the
 *	device.
 *
 * @tx_sk_pacing_shअगरt: Pacing shअगरt to set on TCP sockets when frames from
 *	them are encountered. The शेष should typically not be changed,
 *	unless the driver has good reasons क्रम needing more buffers.
 *
 * @weight_multiplier: Driver specअगरic airसमय weight multiplier used जबतक
 *	refilling deficit of each TXQ.
 *
 * @max_mtu: the max mtu could be set.
 */
काष्ठा ieee80211_hw अणु
	काष्ठा ieee80211_conf conf;
	काष्ठा wiphy *wiphy;
	स्थिर अक्षर *rate_control_algorithm;
	व्योम *priv;
	अचिन्हित दीर्घ flags[BITS_TO_LONGS(NUM_IEEE80211_HW_FLAGS)];
	अचिन्हित पूर्णांक extra_tx_headroom;
	अचिन्हित पूर्णांक extra_beacon_tailroom;
	पूर्णांक vअगर_data_size;
	पूर्णांक sta_data_size;
	पूर्णांक chanctx_data_size;
	पूर्णांक txq_data_size;
	u16 queues;
	u16 max_listen_पूर्णांकerval;
	s8 max_संकेत;
	u8 max_rates;
	u8 max_report_rates;
	u8 max_rate_tries;
	u16 max_rx_aggregation_subframes;
	u16 max_tx_aggregation_subframes;
	u8 max_tx_fragments;
	u8 offchannel_tx_hw_queue;
	u8 radiotap_mcs_details;
	u16 radiotap_vht_details;
	काष्ठा अणु
		पूर्णांक units_pos;
		s16 accuracy;
	पूर्ण radiotap_बारtamp;
	netdev_features_t netdev_features;
	u8 uapsd_queues;
	u8 uapsd_max_sp_len;
	u8 n_cipher_schemes;
	स्थिर काष्ठा ieee80211_cipher_scheme *cipher_schemes;
	u8 max_nan_de_entries;
	u8 tx_sk_pacing_shअगरt;
	u8 weight_multiplier;
	u32 max_mtu;
पूर्ण;

अटल अंतरभूत bool _ieee80211_hw_check(काष्ठा ieee80211_hw *hw,
				       क्रमागत ieee80211_hw_flags flg)
अणु
	वापस test_bit(flg, hw->flags);
पूर्ण
#घोषणा ieee80211_hw_check(hw, flg)	_ieee80211_hw_check(hw, IEEE80211_HW_##flg)

अटल अंतरभूत व्योम _ieee80211_hw_set(काष्ठा ieee80211_hw *hw,
				     क्रमागत ieee80211_hw_flags flg)
अणु
	वापस __set_bit(flg, hw->flags);
पूर्ण
#घोषणा ieee80211_hw_set(hw, flg)	_ieee80211_hw_set(hw, IEEE80211_HW_##flg)

/**
 * काष्ठा ieee80211_scan_request - hw scan request
 *
 * @ies: poपूर्णांकers dअगरferent parts of IEs (in req.ie)
 * @req: cfg80211 request.
 */
काष्ठा ieee80211_scan_request अणु
	काष्ठा ieee80211_scan_ies ies;

	/* Keep last */
	काष्ठा cfg80211_scan_request req;
पूर्ण;

/**
 * काष्ठा ieee80211_tdls_ch_sw_params - TDLS channel चयन parameters
 *
 * @sta: peer this TDLS channel-चयन request/response came from
 * @chandef: channel referenced in a TDLS channel-चयन request
 * @action_code: see &क्रमागत ieee80211_tdls_actioncode
 * @status: channel-चयन response status
 * @बारtamp: समय at which the frame was received
 * @चयन_समय: चयन-timing parameter received in the frame
 * @चयन_समयout: चयन-timing parameter received in the frame
 * @पंचांगpl_skb: TDLS चयन-channel response ढाँचा
 * @ch_sw_पंचांग_ie: offset of the channel-चयन timing IE inside @पंचांगpl_skb
 */
काष्ठा ieee80211_tdls_ch_sw_params अणु
	काष्ठा ieee80211_sta *sta;
	काष्ठा cfg80211_chan_def *chandef;
	u8 action_code;
	u32 status;
	u32 बारtamp;
	u16 चयन_समय;
	u16 चयन_समयout;
	काष्ठा sk_buff *पंचांगpl_skb;
	u32 ch_sw_पंचांग_ie;
पूर्ण;

/**
 * wiphy_to_ieee80211_hw - वापस a mac80211 driver hw काष्ठा from a wiphy
 *
 * @wiphy: the &काष्ठा wiphy which we want to query
 *
 * mac80211 drivers can use this to get to their respective
 * &काष्ठा ieee80211_hw. Drivers wishing to get to their own निजी
 * काष्ठाure can then access it via hw->priv. Note that mac802111 drivers should
 * not use wiphy_priv() to try to get their निजी driver काष्ठाure as this
 * is alपढ़ोy used पूर्णांकernally by mac80211.
 *
 * Return: The mac80211 driver hw काष्ठा of @wiphy.
 */
काष्ठा ieee80211_hw *wiphy_to_ieee80211_hw(काष्ठा wiphy *wiphy);

/**
 * SET_IEEE80211_DEV - set device क्रम 802.11 hardware
 *
 * @hw: the &काष्ठा ieee80211_hw to set the device क्रम
 * @dev: the &काष्ठा device of this 802.11 device
 */
अटल अंतरभूत व्योम SET_IEEE80211_DEV(काष्ठा ieee80211_hw *hw, काष्ठा device *dev)
अणु
	set_wiphy_dev(hw->wiphy, dev);
पूर्ण

/**
 * SET_IEEE80211_PERM_ADDR - set the permanent MAC address क्रम 802.11 hardware
 *
 * @hw: the &काष्ठा ieee80211_hw to set the MAC address क्रम
 * @addr: the address to set
 */
अटल अंतरभूत व्योम SET_IEEE80211_PERM_ADDR(काष्ठा ieee80211_hw *hw, स्थिर u8 *addr)
अणु
	स_नकल(hw->wiphy->perm_addr, addr, ETH_ALEN);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_rate *
ieee80211_get_tx_rate(स्थिर काष्ठा ieee80211_hw *hw,
		      स्थिर काष्ठा ieee80211_tx_info *c)
अणु
	अगर (WARN_ON_ONCE(c->control.rates[0].idx < 0))
		वापस शून्य;
	वापस &hw->wiphy->bands[c->band]->bitrates[c->control.rates[0].idx];
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_rate *
ieee80211_get_rts_cts_rate(स्थिर काष्ठा ieee80211_hw *hw,
			   स्थिर काष्ठा ieee80211_tx_info *c)
अणु
	अगर (c->control.rts_cts_rate_idx < 0)
		वापस शून्य;
	वापस &hw->wiphy->bands[c->band]->bitrates[c->control.rts_cts_rate_idx];
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_rate *
ieee80211_get_alt_retry_rate(स्थिर काष्ठा ieee80211_hw *hw,
			     स्थिर काष्ठा ieee80211_tx_info *c, पूर्णांक idx)
अणु
	अगर (c->control.rates[idx + 1].idx < 0)
		वापस शून्य;
	वापस &hw->wiphy->bands[c->band]->bitrates[c->control.rates[idx + 1].idx];
पूर्ण

/**
 * ieee80211_मुक्त_txskb - मुक्त TX skb
 * @hw: the hardware
 * @skb: the skb
 *
 * Free a transmit skb. Use this function when some failure
 * to transmit happened and thus status cannot be reported.
 */
व्योम ieee80211_मुक्त_txskb(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);

/**
 * DOC: Hardware crypto acceleration
 *
 * mac80211 is capable of taking advantage of many hardware
 * acceleration designs क्रम encryption and decryption operations.
 *
 * The set_key() callback in the &काष्ठा ieee80211_ops क्रम a given
 * device is called to enable hardware acceleration of encryption and
 * decryption. The callback takes a @sta parameter that will be शून्य
 * क्रम शेष keys or keys used क्रम transmission only, or poपूर्णांक to
 * the station inक्रमmation क्रम the peer क्रम inभागidual keys.
 * Multiple transmission keys with the same key index may be used when
 * VLANs are configured क्रम an access poपूर्णांक.
 *
 * When transmitting, the TX control data will use the @hw_key_idx
 * selected by the driver by modअगरying the &काष्ठा ieee80211_key_conf
 * poपूर्णांकed to by the @key parameter to the set_key() function.
 *
 * The set_key() call क्रम the %SET_KEY command should वापस 0 अगर
 * the key is now in use, -%EOPNOTSUPP or -%ENOSPC अगर it couldn't be
 * added; अगर you वापस 0 then hw_key_idx must be asचिन्हित to the
 * hardware key index, you are मुक्त to use the full u8 range.
 *
 * Note that in the हाल that the @IEEE80211_HW_SW_CRYPTO_CONTROL flag is
 * set, mac80211 will not स्वतःmatically fall back to software crypto अगर
 * enabling hardware crypto failed. The set_key() call may also वापस the
 * value 1 to permit this specअगरic key/algorithm to be करोne in software.
 *
 * When the cmd is %DISABLE_KEY then it must succeed.
 *
 * Note that it is permissible to not decrypt a frame even अगर a key
 * क्रम it has been uploaded to hardware, the stack will not make any
 * decision based on whether a key has been uploaded or not but rather
 * based on the receive flags.
 *
 * The &काष्ठा ieee80211_key_conf काष्ठाure poपूर्णांकed to by the @key
 * parameter is guaranteed to be valid until another call to set_key()
 * हटाओs it, but it can only be used as a cookie to dअगरferentiate
 * keys.
 *
 * In TKIP some HW need to be provided a phase 1 key, क्रम RX decryption
 * acceleration (i.e. iwlwअगरi). Those drivers should provide update_tkip_key
 * handler.
 * The update_tkip_key() call updates the driver with the new phase 1 key.
 * This happens every समय the iv16 wraps around (every 65536 packets). The
 * set_key() call will happen only once क्रम each key (unless the AP did
 * rekeying), it will not include a valid phase 1 key. The valid phase 1 key is
 * provided by update_tkip_key only. The trigger that makes mac80211 call this
 * handler is software decryption with wrap around of iv16.
 *
 * The set_शेष_unicast_key() call updates the शेष WEP key index
 * configured to the hardware क्रम WEP encryption type. This is required
 * क्रम devices that support offload of data packets (e.g. ARP responses).
 *
 * Mac80211 drivers should set the @NL80211_EXT_FEATURE_CAN_REPLACE_PTK0 flag
 * when they are able to replace in-use PTK keys according to the following
 * requirements:
 * 1) They करो not hand over frames decrypted with the old key to
      mac80211 once the call to set_key() with command %DISABLE_KEY has been
      completed when also setting @IEEE80211_KEY_FLAG_GENERATE_IV क्रम any key,
   2) either drop or जारी to use the old key क्रम any outgoing frames queued
      at the समय of the key deletion (including re-transmits),
   3) never send out a frame queued prior to the set_key() %SET_KEY command
      encrypted with the new key and
   4) never send out a frame unencrypted when it should be encrypted.
   Mac80211 will not queue any new frames क्रम a deleted key to the driver.
 */

/**
 * DOC: Powersave support
 *
 * mac80211 has support क्रम various घातersave implementations.
 *
 * First, it can support hardware that handles all घातersaving by itself,
 * such hardware should simply set the %IEEE80211_HW_SUPPORTS_PS hardware
 * flag. In that हाल, it will be told about the desired घातersave mode
 * with the %IEEE80211_CONF_PS flag depending on the association status.
 * The hardware must take care of sending nullfunc frames when necessary,
 * i.e. when entering and leaving घातersave mode. The hardware is required
 * to look at the AID in beacons and संकेत to the AP that it woke up when
 * it finds traffic directed to it.
 *
 * %IEEE80211_CONF_PS flag enabled means that the घातersave mode defined in
 * IEEE 802.11-2007 section 11.2 is enabled. This is not to be confused
 * with hardware wakeup and sleep states. Driver is responsible क्रम waking
 * up the hardware beक्रमe issuing commands to the hardware and putting it
 * back to sleep at appropriate बार.
 *
 * When PS is enabled, hardware needs to wakeup क्रम beacons and receive the
 * buffered multicast/broadcast frames after the beacon. Also it must be
 * possible to send frames and receive the acknowledment frame.
 *
 * Other hardware designs cannot send nullfunc frames by themselves and also
 * need software support क्रम parsing the TIM biपंचांगap. This is also supported
 * by mac80211 by combining the %IEEE80211_HW_SUPPORTS_PS and
 * %IEEE80211_HW_PS_शून्यFUNC_STACK flags. The hardware is of course still
 * required to pass up beacons. The hardware is still required to handle
 * waking up क्रम multicast traffic; अगर it cannot the driver must handle that
 * as best as it can, mac80211 is too slow to करो that.
 *
 * Dynamic घातersave is an extension to normal घातersave in which the
 * hardware stays awake क्रम a user-specअगरied period of समय after sending a
 * frame so that reply frames need not be buffered and thereक्रमe delayed to
 * the next wakeup. It's compromise of getting good enough latency when
 * there's data traffic and still saving signअगरicantly घातer in idle
 * periods.
 *
 * Dynamic घातersave is simply supported by mac80211 enabling and disabling
 * PS based on traffic. Driver needs to only set %IEEE80211_HW_SUPPORTS_PS
 * flag and mac80211 will handle everything स्वतःmatically. Additionally,
 * hardware having support क्रम the dynamic PS feature may set the
 * %IEEE80211_HW_SUPPORTS_DYNAMIC_PS flag to indicate that it can support
 * dynamic PS mode itself. The driver needs to look at the
 * @dynamic_ps_समयout hardware configuration value and use it that value
 * whenever %IEEE80211_CONF_PS is set. In this हाल mac80211 will disable
 * dynamic PS feature in stack and will just keep %IEEE80211_CONF_PS
 * enabled whenever user has enabled घातersave.
 *
 * Driver inक्रमms U-APSD client support by enabling
 * %IEEE80211_VIF_SUPPORTS_UAPSD flag. The mode is configured through the
 * uapsd parameter in conf_tx() operation. Hardware needs to send the QoS
 * Nullfunc frames and stay awake until the service period has ended. To
 * utilize U-APSD, dynamic घातersave is disabled क्रम voip AC and all frames
 * from that AC are transmitted with घातersave enabled.
 *
 * Note: U-APSD client mode is not yet supported with
 * %IEEE80211_HW_PS_शून्यFUNC_STACK.
 */

/**
 * DOC: Beacon filter support
 *
 * Some hardware have beacon filter support to reduce host cpu wakeups
 * which will reduce प्रणाली घातer consumption. It usually works so that
 * the firmware creates a checksum of the beacon but omits all स्थिरantly
 * changing elements (TSF, TIM etc). Whenever the checksum changes the
 * beacon is क्रमwarded to the host, otherwise it will be just dropped. That
 * way the host will only receive beacons where some relevant inक्रमmation
 * (क्रम example ERP protection or WMM settings) have changed.
 *
 * Beacon filter support is advertised with the %IEEE80211_VIF_BEACON_FILTER
 * पूर्णांकerface capability. The driver needs to enable beacon filter support
 * whenever घातer save is enabled, that is %IEEE80211_CONF_PS is set. When
 * घातer save is enabled, the stack will not check क्रम beacon loss and the
 * driver needs to notअगरy about loss of beacons with ieee80211_beacon_loss().
 *
 * The समय (or number of beacons missed) until the firmware notअगरies the
 * driver of a beacon loss event (which in turn causes the driver to call
 * ieee80211_beacon_loss()) should be configurable and will be controlled
 * by mac80211 and the roaming algorithm in the future.
 *
 * Since there may be स्थिरantly changing inक्रमmation elements that nothing
 * in the software stack cares about, we will, in the future, have mac80211
 * tell the driver which inक्रमmation elements are पूर्णांकeresting in the sense
 * that we want to see changes in them. This will include
 *
 *  - a list of inक्रमmation element IDs
 *  - a list of OUIs क्रम the venकरोr inक्रमmation element
 *
 * Ideally, the hardware would filter out any beacons without changes in the
 * requested elements, but अगर it cannot support that it may, at the expense
 * of some efficiency, filter out only a subset. For example, अगर the device
 * करोesn't support checking क्रम OUIs it should pass up all changes in all
 * venकरोr inक्रमmation elements.
 *
 * Note that change, क्रम the sake of simplअगरication, also includes inक्रमmation
 * elements appearing or disappearing from the beacon.
 *
 * Some hardware supports an "ignore list" instead, just make sure nothing
 * that was requested is on the ignore list, and include commonly changing
 * inक्रमmation element IDs in the ignore list, क्रम example 11 (BSS load) and
 * the various venकरोr-asचिन्हित IEs with unknown contents (128, 129, 133-136,
 * 149, 150, 155, 156, 173, 176, 178, 179, 219); क्रम क्रमward compatibility
 * it could also include some currently unused IDs.
 *
 *
 * In addition to these capabilities, hardware should support notअगरying the
 * host of changes in the beacon RSSI. This is relevant to implement roaming
 * when no traffic is flowing (when traffic is flowing we see the RSSI of
 * the received data packets). This can consist in notअगरying the host when
 * the RSSI changes signअगरicantly or when it drops below or rises above
 * configurable thresholds. In the future these thresholds will also be
 * configured by mac80211 (which माला_लो them from userspace) to implement
 * them as the roaming algorithm requires.
 *
 * If the hardware cannot implement this, the driver should ask it to
 * periodically pass beacon frames to the host so that software can करो the
 * संकेत strength threshold checking.
 */

/**
 * DOC: Spatial multiplexing घातer save
 *
 * SMPS (Spatial multiplexing घातer save) is a mechanism to conserve
 * घातer in an 802.11n implementation. For details on the mechanism
 * and rationale, please refer to 802.11 (as amended by 802.11n-2009)
 * "11.2.3 SM power save".
 *
 * The mac80211 implementation is capable of sending action frames
 * to update the AP about the station's SMPS mode, and will inकाष्ठा
 * the driver to enter the specअगरic mode. It will also announce the
 * requested SMPS mode during the association handshake. Hardware
 * support क्रम this feature is required, and can be indicated by
 * hardware flags.
 *
 * The शेष mode will be "automatic", which nl80211/cfg80211
 * defines to be dynamic SMPS in (regular) घातersave, and SMPS
 * turned off otherwise.
 *
 * To support this feature, the driver must set the appropriate
 * hardware support flags, and handle the SMPS flag to the config()
 * operation. It will then with this mechanism be inकाष्ठाed to
 * enter the requested SMPS mode जबतक associated to an HT AP.
 */

/**
 * DOC: Frame filtering
 *
 * mac80211 requires to see many management frames क्रम proper
 * operation, and users may want to see many more frames when
 * in monitor mode. However, क्रम best CPU usage and घातer consumption,
 * having as few frames as possible percolate through the stack is
 * desirable. Hence, the hardware should filter as much as possible.
 *
 * To achieve this, mac80211 uses filter flags (see below) to tell
 * the driver's configure_filter() function which frames should be
 * passed to mac80211 and which should be filtered out.
 *
 * Beक्रमe configure_filter() is invoked, the prepare_multicast()
 * callback is invoked with the parameters @mc_count and @mc_list
 * क्रम the combined multicast address list of all भव पूर्णांकerfaces.
 * It's use is optional, and it वापसs a u64 that is passed to
 * configure_filter(). Additionally, configure_filter() has the
 * arguments @changed_flags telling which flags were changed and
 * @total_flags with the new flag states.
 *
 * If your device has no multicast address filters your driver will
 * need to check both the %FIF_ALLMULTI flag and the @mc_count
 * parameter to see whether multicast frames should be accepted
 * or dropped.
 *
 * All unsupported flags in @total_flags must be cleared.
 * Hardware करोes not support a flag अगर it is incapable of _passing_
 * the frame to the stack. Otherwise the driver must ignore
 * the flag, but not clear it.
 * You must _only_ clear the flag (announce no support क्रम the
 * flag to mac80211) अगर you are not able to pass the packet type
 * to the stack (so the hardware always filters it).
 * So क्रम example, you should clear @FIF_CONTROL, अगर your hardware
 * always filters control frames. If your hardware always passes
 * control frames to the kernel and is incapable of filtering them,
 * you करो _not_ clear the @FIF_CONTROL flag.
 * This rule applies to all other FIF flags as well.
 */

/**
 * DOC: AP support क्रम घातersaving clients
 *
 * In order to implement AP and P2P GO modes, mac80211 has support क्रम
 * client घातersaving, both "legacy" PS (PS-Poll/null data) and uAPSD.
 * There currently is no support क्रम sAPSD.
 *
 * There is one assumption that mac80211 makes, namely that a client
 * will not poll with PS-Poll and trigger with uAPSD at the same समय.
 * Both are supported, and both can be used by the same client, but
 * they can't be used concurrently by the same client. This simplअगरies
 * the driver code.
 *
 * The first thing to keep in mind is that there is a flag क्रम complete
 * driver implementation: %IEEE80211_HW_AP_LINK_PS. If this flag is set,
 * mac80211 expects the driver to handle most of the state machine क्रम
 * घातersaving clients and will ignore the PM bit in incoming frames.
 * Drivers then use ieee80211_sta_ps_transition() to inक्रमm mac80211 of
 * stations' powersave transitions. In this mode, mac80211 also doesn't
 * handle PS-Poll/uAPSD.
 *
 * In the mode without %IEEE80211_HW_AP_LINK_PS, mac80211 will check the
 * PM bit in incoming frames क्रम client घातersave transitions. When a
 * station goes to sleep, we will stop transmitting to it. There is,
 * however, a race condition: a station might go to sleep जबतक there is
 * data buffered on hardware queues. If the device has support क्रम this
 * it will reject frames, and the driver should give the frames back to
 * mac80211 with the %IEEE80211_TX_STAT_TX_FILTERED flag set which will
 * cause mac80211 to retry the frame when the station wakes up. The
 * driver is also notअगरied of घातersave transitions by calling its
 * @sta_notअगरy callback.
 *
 * When the station is asleep, it has three choices: it can wake up,
 * it can PS-Poll, or it can possibly start a uAPSD service period.
 * Waking up is implemented by simply transmitting all buffered (and
 * filtered) frames to the station. This is the easiest हाल. When
 * the station sends a PS-Poll or a uAPSD trigger frame, mac80211
 * will inक्रमm the driver of this with the @allow_buffered_frames
 * callback; this callback is optional. mac80211 will then transmit
 * the frames as usual and set the %IEEE80211_TX_CTL_NO_PS_BUFFER
 * on each frame. The last frame in the service period (or the only
 * response to a PS-Poll) also has %IEEE80211_TX_STATUS_EOSP set to
 * indicate that it ends the service period; as this frame must have
 * TX status report it also sets %IEEE80211_TX_CTL_REQ_TX_STATUS.
 * When TX status is reported क्रम this frame, the service period is
 * marked has having ended and a new one can be started by the peer.
 *
 * Additionally, non-bufferable MMPDUs can also be transmitted by
 * mac80211 with the %IEEE80211_TX_CTL_NO_PS_BUFFER set in them.
 *
 * Another race condition can happen on some devices like iwlwअगरi
 * when there are frames queued क्रम the station and it wakes up
 * or polls; the frames that are alपढ़ोy queued could end up being
 * transmitted first instead, causing reordering and/or wrong
 * processing of the EOSP. The cause is that allowing frames to be
 * transmitted to a certain station is out-of-band communication to
 * the device. To allow this problem to be solved, the driver can
 * call ieee80211_sta_block_awake() अगर frames are buffered when it
 * is notअगरied that the station went to sleep. When all these frames
 * have been filtered (see above), it must call the function again
 * to indicate that the station is no दीर्घer blocked.
 *
 * If the driver buffers frames in the driver क्रम aggregation in any
 * way, it must use the ieee80211_sta_set_buffered() call when it is
 * notअगरied of the station going to sleep to inक्रमm mac80211 of any
 * TIDs that have frames buffered. Note that when a station wakes up
 * this inक्रमmation is reset (hence the requirement to call it when
 * inक्रमmed of the station going to sleep). Then, when a service
 * period starts क्रम any reason, @release_buffered_frames is called
 * with the number of frames to be released and which TIDs they are
 * to come from. In this हाल, the driver is responsible क्रम setting
 * the EOSP (क्रम uAPSD) and MORE_DATA bits in the released frames,
 * to help the @more_data parameter is passed to tell the driver अगर
 * there is more data on other TIDs -- the TIDs to release frames
 * from are ignored since mac80211 करोesn't know how many frames the
 * buffers क्रम those TIDs contain.
 *
 * If the driver also implement GO mode, where असलence periods may
 * लघुen service periods (or पात PS-Poll responses), it must
 * filter those response frames except in the हाल of frames that
 * are buffered in the driver -- those must reमुख्य buffered to aव्योम
 * reordering. Because it is possible that no frames are released
 * in this हाल, the driver must call ieee80211_sta_eosp()
 * to indicate to mac80211 that the service period ended anyway.
 *
 * Finally, अगर frames from multiple TIDs are released from mac80211
 * but the driver might reorder them, it must clear & set the flags
 * appropriately (only the last frame may have %IEEE80211_TX_STATUS_EOSP)
 * and also take care of the EOSP and MORE_DATA bits in the frame.
 * The driver may also use ieee80211_sta_eosp() in this हाल.
 *
 * Note that अगर the driver ever buffers frames other than QoS-data
 * frames, it must take care to never send a non-QoS-data frame as
 * the last frame in a service period, adding a QoS-nulldata frame
 * after a non-QoS-data frame अगर needed.
 */

/**
 * DOC: HW queue control
 *
 * Beक्रमe HW queue control was पूर्णांकroduced, mac80211 only had a single अटल
 * assignment of per-पूर्णांकerface AC software queues to hardware queues. This
 * was problematic क्रम a few reasons:
 * 1) off-channel transmissions might get stuck behind other frames
 * 2) multiple भव पूर्णांकerfaces couldn't be handled correctly
 * 3) after-DTIM frames could get stuck behind other frames
 *
 * To solve this, hardware typically uses multiple dअगरferent queues क्रम all
 * the dअगरferent usages, and this needs to be propagated पूर्णांकo mac80211 so it
 * won't have the same problem with the software queues.
 *
 * Thereक्रमe, mac80211 now offers the %IEEE80211_HW_QUEUE_CONTROL capability
 * flag that tells it that the driver implements its own queue control. To करो
 * so, the driver will set up the various queues in each &काष्ठा ieee80211_vअगर
 * and the offchannel queue in &काष्ठा ieee80211_hw. In response, mac80211 will
 * use those queue IDs in the hw_queue field of &काष्ठा ieee80211_tx_info and
 * अगर necessary will queue the frame on the right software queue that mirrors
 * the hardware queue.
 * Additionally, the driver has to then use these HW queue IDs क्रम the queue
 * management functions (ieee80211_stop_queue() et al.)
 *
 * The driver is मुक्त to set up the queue mappings as needed, multiple भव
 * पूर्णांकerfaces may map to the same hardware queues अगर needed. The setup has to
 * happen during add_पूर्णांकerface or change_पूर्णांकerface callbacks. For example, a
 * driver supporting station+station and station+AP modes might decide to have
 * 10 hardware queues to handle dअगरferent scenarios:
 *
 * 4 AC HW queues क्रम 1st vअगर: 0, 1, 2, 3
 * 4 AC HW queues क्रम 2nd vअगर: 4, 5, 6, 7
 * after-DTIM queue क्रम AP:   8
 * off-channel queue:         9
 *
 * It would then set up the hardware like this:
 *   hw.offchannel_tx_hw_queue = 9
 *
 * and the first भव पूर्णांकerface that is added as follows:
 *   vअगर.hw_queue[IEEE80211_AC_VO] = 0
 *   vअगर.hw_queue[IEEE80211_AC_VI] = 1
 *   vअगर.hw_queue[IEEE80211_AC_BE] = 2
 *   vअगर.hw_queue[IEEE80211_AC_BK] = 3
 *   vअगर.cab_queue = 8 // अगर AP mode, otherwise %IEEE80211_INVAL_HW_QUEUE
 * and the second भव पूर्णांकerface with 4-7.
 *
 * If queue 6 माला_लो full, क्रम example, mac80211 would only stop the second
 * भव पूर्णांकerface's BE queue since भव पूर्णांकerface queues are per AC.
 *
 * Note that the vअगर.cab_queue value should be set to %IEEE80211_INVAL_HW_QUEUE
 * whenever the queue is not used (i.e. the पूर्णांकerface is not in AP mode) अगर the
 * queue could potentially be shared since mac80211 will look at cab_queue when
 * a queue is stopped/woken even अगर the पूर्णांकerface is not in AP mode.
 */

/**
 * क्रमागत ieee80211_filter_flags - hardware filter flags
 *
 * These flags determine what the filter in hardware should be
 * programmed to let through and what should not be passed to the
 * stack. It is always safe to pass more frames than requested,
 * but this has negative impact on घातer consumption.
 *
 * @FIF_ALLMULTI: pass all multicast frames, this is used अगर requested
 *	by the user or अगर the hardware is not capable of filtering by
 *	multicast address.
 *
 * @FIF_FCSFAIL: pass frames with failed FCS (but you need to set the
 *	%RX_FLAG_FAILED_FCS_CRC क्रम them)
 *
 * @FIF_PLCPFAIL: pass frames with failed PLCP CRC (but you need to set
 *	the %RX_FLAG_FAILED_PLCP_CRC क्रम them
 *
 * @FIF_BCN_PRBRESP_PROMISC: This flag is set during scanning to indicate
 *	to the hardware that it should not filter beacons or probe responses
 *	by BSSID. Filtering them can greatly reduce the amount of processing
 *	mac80211 needs to करो and the amount of CPU wakeups, so you should
 *	honour this flag अगर possible.
 *
 * @FIF_CONTROL: pass control frames (except क्रम PS Poll) addressed to this
 *	station
 *
 * @FIF_OTHER_BSS: pass frames destined to other BSSes
 *
 * @FIF_PSPOLL: pass PS Poll frames
 *
 * @FIF_PROBE_REQ: pass probe request frames
 *
 * @FIF_MCAST_ACTION: pass multicast Action frames
 */
क्रमागत ieee80211_filter_flags अणु
	FIF_ALLMULTI		= 1<<1,
	FIF_FCSFAIL		= 1<<2,
	FIF_PLCPFAIL		= 1<<3,
	FIF_BCN_PRBRESP_PROMISC	= 1<<4,
	FIF_CONTROL		= 1<<5,
	FIF_OTHER_BSS		= 1<<6,
	FIF_PSPOLL		= 1<<7,
	FIF_PROBE_REQ		= 1<<8,
	FIF_MCAST_ACTION	= 1<<9,
पूर्ण;

/**
 * क्रमागत ieee80211_ampdu_mlme_action - A-MPDU actions
 *
 * These flags are used with the ampdu_action() callback in
 * &काष्ठा ieee80211_ops to indicate which action is needed.
 *
 * Note that drivers MUST be able to deal with a TX aggregation
 * session being stopped even beक्रमe they OK'ed starting it by
 * calling ieee80211_start_tx_ba_cb_irqsafe, because the peer
 * might receive the addBA frame and send a delBA right away!
 *
 * @IEEE80211_AMPDU_RX_START: start RX aggregation
 * @IEEE80211_AMPDU_RX_STOP: stop RX aggregation
 * @IEEE80211_AMPDU_TX_START: start TX aggregation, the driver must either
 *	call ieee80211_start_tx_ba_cb_irqsafe() or
 *	call ieee80211_start_tx_ba_cb_irqsafe() with status
 *	%IEEE80211_AMPDU_TX_START_DELAY_ADDBA to delay addba after
 *	ieee80211_start_tx_ba_cb_irqsafe is called, or just वापस the special
 *	status %IEEE80211_AMPDU_TX_START_IMMEDIATE.
 * @IEEE80211_AMPDU_TX_OPERATIONAL: TX aggregation has become operational
 * @IEEE80211_AMPDU_TX_STOP_CONT: stop TX aggregation but जारी transmitting
 *	queued packets, now unaggregated. After all packets are transmitted the
 *	driver has to call ieee80211_stop_tx_ba_cb_irqsafe().
 * @IEEE80211_AMPDU_TX_STOP_FLUSH: stop TX aggregation and flush all packets,
 *	called when the station is हटाओd. There's no need or reason to call
 *	ieee80211_stop_tx_ba_cb_irqsafe() in this हाल as mac80211 assumes the
 *	session is gone and हटाओs the station.
 * @IEEE80211_AMPDU_TX_STOP_FLUSH_CONT: called when TX aggregation is stopped
 *	but the driver hasn't called ieee80211_stop_tx_ba_cb_irqsafe() yet and
 *	now the connection is dropped and the station will be हटाओd. Drivers
 *	should clean up and drop reमुख्यing packets when this is called.
 */
क्रमागत ieee80211_ampdu_mlme_action अणु
	IEEE80211_AMPDU_RX_START,
	IEEE80211_AMPDU_RX_STOP,
	IEEE80211_AMPDU_TX_START,
	IEEE80211_AMPDU_TX_STOP_CONT,
	IEEE80211_AMPDU_TX_STOP_FLUSH,
	IEEE80211_AMPDU_TX_STOP_FLUSH_CONT,
	IEEE80211_AMPDU_TX_OPERATIONAL,
पूर्ण;

#घोषणा IEEE80211_AMPDU_TX_START_IMMEDIATE 1
#घोषणा IEEE80211_AMPDU_TX_START_DELAY_ADDBA 2

/**
 * काष्ठा ieee80211_ampdu_params - AMPDU action parameters
 *
 * @action: the ampdu action, value from %ieee80211_ampdu_mlme_action.
 * @sta: peer of this AMPDU session
 * @tid: tid of the BA session
 * @ssn: start sequence number of the session. TX/RX_STOP can pass 0. When
 *	action is set to %IEEE80211_AMPDU_RX_START the driver passes back the
 *	actual ssn value used to start the session and ग_लिखोs the value here.
 * @buf_size: reorder buffer size  (number of subframes). Valid only when the
 *	action is set to %IEEE80211_AMPDU_RX_START or
 *	%IEEE80211_AMPDU_TX_OPERATIONAL
 * @amsdu: indicates the peer's ability to receive A-MSDU within A-MPDU.
 *	valid when the action is set to %IEEE80211_AMPDU_TX_OPERATIONAL
 * @समयout: BA session समयout. Valid only when the action is set to
 *	%IEEE80211_AMPDU_RX_START
 */
काष्ठा ieee80211_ampdu_params अणु
	क्रमागत ieee80211_ampdu_mlme_action action;
	काष्ठा ieee80211_sta *sta;
	u16 tid;
	u16 ssn;
	u16 buf_size;
	bool amsdu;
	u16 समयout;
पूर्ण;

/**
 * क्रमागत ieee80211_frame_release_type - frame release reason
 * @IEEE80211_FRAME_RELEASE_PSPOLL: frame released क्रम PS-Poll
 * @IEEE80211_FRAME_RELEASE_UAPSD: frame(s) released due to
 *	frame received on trigger-enabled AC
 */
क्रमागत ieee80211_frame_release_type अणु
	IEEE80211_FRAME_RELEASE_PSPOLL,
	IEEE80211_FRAME_RELEASE_UAPSD,
पूर्ण;

/**
 * क्रमागत ieee80211_rate_control_changed - flags to indicate what changed
 *
 * @IEEE80211_RC_BW_CHANGED: The bandwidth that can be used to transmit
 *	to this station changed. The actual bandwidth is in the station
 *	inक्रमmation -- क्रम HT20/40 the IEEE80211_HT_CAP_SUP_WIDTH_20_40
 *	flag changes, क्रम HT and VHT the bandwidth field changes.
 * @IEEE80211_RC_SMPS_CHANGED: The SMPS state of the station changed.
 * @IEEE80211_RC_SUPP_RATES_CHANGED: The supported rate set of this peer
 *	changed (in IBSS mode) due to discovering more inक्रमmation about
 *	the peer.
 * @IEEE80211_RC_NSS_CHANGED: N_SS (number of spatial streams) was changed
 *	by the peer
 */
क्रमागत ieee80211_rate_control_changed अणु
	IEEE80211_RC_BW_CHANGED		= BIT(0),
	IEEE80211_RC_SMPS_CHANGED	= BIT(1),
	IEEE80211_RC_SUPP_RATES_CHANGED	= BIT(2),
	IEEE80211_RC_NSS_CHANGED	= BIT(3),
पूर्ण;

/**
 * क्रमागत ieee80211_roc_type - reमुख्य on channel type
 *
 * With the support क्रम multi channel contexts and multi channel operations,
 * reमुख्य on channel operations might be limited/deferred/पातed by other
 * flows/operations which have higher priority (and vice versa).
 * Specअगरying the ROC type can be used by devices to prioritize the ROC
 * operations compared to other operations/flows.
 *
 * @IEEE80211_ROC_TYPE_NORMAL: There are no special requirements क्रम this ROC.
 * @IEEE80211_ROC_TYPE_MGMT_TX: The reमुख्य on channel request is required
 *	क्रम sending management frames offchannel.
 */
क्रमागत ieee80211_roc_type अणु
	IEEE80211_ROC_TYPE_NORMAL = 0,
	IEEE80211_ROC_TYPE_MGMT_TX,
पूर्ण;

/**
 * क्रमागत ieee80211_reconfig_type - reconfig type
 *
 * This क्रमागत is used by the reconfig_complete() callback to indicate what
 * reconfiguration type was completed.
 *
 * @IEEE80211_RECONFIG_TYPE_RESTART: hw restart type
 *	(also due to resume() callback वापसing 1)
 * @IEEE80211_RECONFIG_TYPE_SUSPEND: suspend type (regardless
 *	of wowlan configuration)
 */
क्रमागत ieee80211_reconfig_type अणु
	IEEE80211_RECONFIG_TYPE_RESTART,
	IEEE80211_RECONFIG_TYPE_SUSPEND,
पूर्ण;

/**
 * काष्ठा ieee80211_ops - callbacks from mac80211 to the driver
 *
 * This काष्ठाure contains various callbacks that the driver may
 * handle or, in some हालs, must handle, क्रम example to configure
 * the hardware to a new channel or to transmit a frame.
 *
 * @tx: Handler that 802.11 module calls क्रम each transmitted frame.
 *	skb contains the buffer starting from the IEEE 802.11 header.
 *	The low-level driver should send the frame out based on
 *	configuration in the TX control data. This handler should,
 *	preferably, never fail and stop queues appropriately.
 *	Must be atomic.
 *
 * @start: Called beक्रमe the first netdevice attached to the hardware
 *	is enabled. This should turn on the hardware and must turn on
 *	frame reception (क्रम possibly enabled monitor पूर्णांकerfaces.)
 *	Returns negative error codes, these may be seen in userspace,
 *	or zero.
 *	When the device is started it should not have a MAC address
 *	to aव्योम acknowledging frames beक्रमe a non-monitor device
 *	is added.
 *	Must be implemented and can sleep.
 *
 * @stop: Called after last netdevice attached to the hardware
 *	is disabled. This should turn off the hardware (at least
 *	it must turn off frame reception.)
 *	May be called right after add_पूर्णांकerface अगर that rejects
 *	an पूर्णांकerface. If you added any work onto the mac80211 workqueue
 *	you should ensure to cancel it on this callback.
 *	Must be implemented and can sleep.
 *
 * @suspend: Suspend the device; mac80211 itself will quiesce beक्रमe and
 *	stop transmitting and करोing any other configuration, and then
 *	ask the device to suspend. This is only invoked when WoWLAN is
 *	configured, otherwise the device is deconfigured completely and
 *	reconfigured at resume समय.
 *	The driver may also impose special conditions under which it
 *	wants to use the "normal" suspend (deconfigure), say अगर it only
 *	supports WoWLAN when the device is associated. In this हाल, it
 *	must वापस 1 from this function.
 *
 * @resume: If WoWLAN was configured, this indicates that mac80211 is
 *	now resuming its operation, after this the device must be fully
 *	functional again. If this वापसs an error, the only way out is
 *	to also unरेजिस्टर the device. If it वापसs 1, then mac80211
 *	will also go through the regular complete restart on resume.
 *
 * @set_wakeup: Enable or disable wakeup when WoWLAN configuration is
 *	modअगरied. The reason is that device_set_wakeup_enable() is
 *	supposed to be called when the configuration changes, not only
 *	in suspend().
 *
 * @add_पूर्णांकerface: Called when a netdevice attached to the hardware is
 *	enabled. Because it is not called क्रम monitor mode devices, @start
 *	and @stop must be implemented.
 *	The driver should perक्रमm any initialization it needs beक्रमe
 *	the device can be enabled. The initial configuration क्रम the
 *	पूर्णांकerface is given in the conf parameter.
 *	The callback may refuse to add an पूर्णांकerface by वापसing a
 *	negative error code (which will be seen in userspace.)
 *	Must be implemented and can sleep.
 *
 * @change_पूर्णांकerface: Called when a netdevice changes type. This callback
 *	is optional, but only अगर it is supported can पूर्णांकerface types be
 *	चयनed जबतक the पूर्णांकerface is UP. The callback may sleep.
 *	Note that जबतक an पूर्णांकerface is being चयनed, it will not be
 *	found by the पूर्णांकerface iteration callbacks.
 *
 * @हटाओ_पूर्णांकerface: Notअगरies a driver that an पूर्णांकerface is going करोwn.
 *	The @stop callback is called after this अगर it is the last पूर्णांकerface
 *	and no monitor पूर्णांकerfaces are present.
 *	When all पूर्णांकerfaces are हटाओd, the MAC address in the hardware
 *	must be cleared so the device no दीर्घer acknowledges packets,
 *	the mac_addr member of the conf काष्ठाure is, however, set to the
 *	MAC address of the device going away.
 *	Hence, this callback must be implemented. It can sleep.
 *
 * @config: Handler क्रम configuration requests. IEEE 802.11 code calls this
 *	function to change hardware configuration, e.g., channel.
 *	This function should never fail but वापसs a negative error code
 *	अगर it करोes. The callback can sleep.
 *
 * @bss_info_changed: Handler क्रम configuration requests related to BSS
 *	parameters that may vary during BSS's lअगरespan, and may affect low
 *	level driver (e.g. assoc/disassoc status, erp parameters).
 *	This function should not be used अगर no BSS has been set, unless
 *	क्रम association indication. The @changed parameter indicates which
 *	of the bss parameters has changed when a call is made. The callback
 *	can sleep.
 *
 * @prepare_multicast: Prepare क्रम multicast filter configuration.
 *	This callback is optional, and its वापस value is passed
 *	to configure_filter(). This callback must be atomic.
 *
 * @configure_filter: Configure the device's RX filter.
 *	See the section "Frame filtering" क्रम more inक्रमmation.
 *	This callback must be implemented and can sleep.
 *
 * @config_अगरace_filter: Configure the पूर्णांकerface's RX filter.
 *	This callback is optional and is used to configure which frames
 *	should be passed to mac80211. The filter_flags is the combination
 *	of FIF_* flags. The changed_flags is a bit mask that indicates
 *	which flags are changed.
 *	This callback can sleep.
 *
 * @set_tim: Set TIM bit. mac80211 calls this function when a TIM bit
 * 	must be set or cleared क्रम a given STA. Must be atomic.
 *
 * @set_key: See the section "Hardware crypto acceleration"
 *	This callback is only called between add_पूर्णांकerface and
 *	हटाओ_पूर्णांकerface calls, i.e. जबतक the given भव पूर्णांकerface
 *	is enabled.
 *	Returns a negative error code अगर the key can't be added.
 *	The callback can sleep.
 *
 * @update_tkip_key: See the section "Hardware crypto acceleration"
 * 	This callback will be called in the context of Rx. Called क्रम drivers
 * 	which set IEEE80211_KEY_FLAG_TKIP_REQ_RX_P1_KEY.
 *	The callback must be atomic.
 *
 * @set_rekey_data: If the device supports GTK rekeying, क्रम example जबतक the
 *	host is suspended, it can assign this callback to retrieve the data
 *	necessary to करो GTK rekeying, this is the KEK, KCK and replay counter.
 *	After rekeying was करोne it should (क्रम example during resume) notअगरy
 *	userspace of the new replay counter using ieee80211_gtk_rekey_notअगरy().
 *
 * @set_शेष_unicast_key: Set the शेष (unicast) key index, useful क्रम
 *	WEP when the device sends data packets स्वतःnomously, e.g. क्रम ARP
 *	offloading. The index can be 0-3, or -1 क्रम unsetting it.
 *
 * @hw_scan: Ask the hardware to service the scan request, no need to start
 *	the scan state machine in stack. The scan must honour the channel
 *	configuration करोne by the regulatory agent in the wiphy's
 *	रेजिस्टरed bands. The hardware (or the driver) needs to make sure
 *	that घातer save is disabled.
 *	The @req ie/ie_len members are rewritten by mac80211 to contain the
 *	entire IEs after the SSID, so that drivers need not look at these
 *	at all but just send them after the SSID -- mac80211 includes the
 *	(extended) supported rates and HT inक्रमmation (where applicable).
 *	When the scan finishes, ieee80211_scan_completed() must be called;
 *	note that it also must be called when the scan cannot finish due to
 *	any error unless this callback वापसed a negative error code.
 *	This callback is also allowed to वापस the special वापस value 1,
 *	this indicates that hardware scan isn't desirable right now and a
 *	software scan should be करोne instead. A driver wishing to use this
 *	capability must ensure its (hardware) scan capabilities aren't
 *	advertised as more capable than mac80211's software scan is.
 *	The callback can sleep.
 *
 * @cancel_hw_scan: Ask the low-level tp cancel the active hw scan.
 *	The driver should ask the hardware to cancel the scan (अगर possible),
 *	but the scan will be completed only after the driver will call
 *	ieee80211_scan_completed().
 *	This callback is needed क्रम wowlan, to prevent enqueueing a new
 *	scan_work after the low-level driver was alपढ़ोy suspended.
 *	The callback can sleep.
 *
 * @sched_scan_start: Ask the hardware to start scanning repeatedly at
 *	specअगरic पूर्णांकervals.  The driver must call the
 *	ieee80211_sched_scan_results() function whenever it finds results.
 *	This process will जारी until sched_scan_stop is called.
 *
 * @sched_scan_stop: Tell the hardware to stop an ongoing scheduled scan.
 *	In this हाल, ieee80211_sched_scan_stopped() must not be called.
 *
 * @sw_scan_start: Notअगरier function that is called just beक्रमe a software scan
 *	is started. Can be शून्य, अगर the driver करोesn't need this notअगरication.
 *	The mac_addr parameter allows supporting NL80211_SCAN_FLAG_RANDOM_ADDR,
 *	the driver may set the NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR flag अगर it
 *	can use this parameter. The callback can sleep.
 *
 * @sw_scan_complete: Notअगरier function that is called just after a
 *	software scan finished. Can be शून्य, अगर the driver करोesn't need
 *	this notअगरication.
 *	The callback can sleep.
 *
 * @get_stats: Return low-level statistics.
 * 	Returns zero अगर statistics are available.
 *	The callback can sleep.
 *
 * @get_key_seq: If your device implements encryption in hardware and करोes
 *	IV/PN assignment then this callback should be provided to पढ़ो the
 *	IV/PN क्रम the given key from hardware.
 *	The callback must be atomic.
 *
 * @set_frag_threshold: Configuration of fragmentation threshold. Assign this
 *	अगर the device करोes fragmentation by itself. Note that to prevent the
 *	stack from करोing fragmentation IEEE80211_HW_SUPPORTS_TX_FRAG
 *	should be set as well.
 *	The callback can sleep.
 *
 * @set_rts_threshold: Configuration of RTS threshold (अगर device needs it)
 *	The callback can sleep.
 *
 * @sta_add: Notअगरies low level driver about addition of an associated station,
 *	AP, IBSS/WDS/mesh peer etc. This callback can sleep.
 *
 * @sta_हटाओ: Notअगरies low level driver about removal of an associated
 *	station, AP, IBSS/WDS/mesh peer etc. Note that after the callback
 *	वापसs it isn't safe to use the poपूर्णांकer, not even RCU रक्षित;
 *	no RCU grace period is guaranteed between वापसing here and मुक्तing
 *	the station. See @sta_pre_rcu_हटाओ अगर needed.
 *	This callback can sleep.
 *
 * @sta_add_debugfs: Drivers can use this callback to add debugfs files
 *	when a station is added to mac80211's station list. This callback
 *	should be within a CONFIG_MAC80211_DEBUGFS conditional. This
 *	callback can sleep.
 *
 * @sta_notअगरy: Notअगरies low level driver about घातer state transition of an
 *	associated station, AP,  IBSS/WDS/mesh peer etc. For a VIF operating
 *	in AP mode, this callback will not be called when the flag
 *	%IEEE80211_HW_AP_LINK_PS is set. Must be atomic.
 *
 * @sta_set_txpwr: Configure the station tx घातer. This callback set the tx
 *	घातer क्रम the station.
 *	This callback can sleep.
 *
 * @sta_state: Notअगरies low level driver about state transition of a
 *	station (which can be the AP, a client, IBSS/WDS/mesh peer etc.)
 *	This callback is mutually exclusive with @sta_add/@sta_हटाओ.
 *	It must not fail क्रम करोwn transitions but may fail क्रम transitions
 *	up the list of states. Also note that after the callback वापसs it
 *	isn't safe to use the poपूर्णांकer, not even RCU रक्षित - no RCU grace
 *	period is guaranteed between वापसing here and मुक्तing the station.
 *	See @sta_pre_rcu_हटाओ अगर needed.
 *	The callback can sleep.
 *
 * @sta_pre_rcu_हटाओ: Notअगरy driver about station removal beक्रमe RCU
 *	synchronisation. This is useful अगर a driver needs to have station
 *	poपूर्णांकers रक्षित using RCU, it can then use this call to clear
 *	the poपूर्णांकers instead of रुकोing क्रम an RCU grace period to elapse
 *	in @sta_state.
 *	The callback can sleep.
 *
 * @sta_rc_update: Notअगरies the driver of changes to the bitrates that can be
 *	used to transmit to the station. The changes are advertised with bits
 *	from &क्रमागत ieee80211_rate_control_changed and the values are reflected
 *	in the station data. This callback should only be used when the driver
 *	uses hardware rate control (%IEEE80211_HW_HAS_RATE_CONTROL) since
 *	otherwise the rate control algorithm is notअगरied directly.
 *	Must be atomic.
 * @sta_rate_tbl_update: Notअगरies the driver that the rate table changed. This
 *	is only used अगर the configured rate control algorithm actually uses
 *	the new rate table API, and is thereक्रमe optional. Must be atomic.
 *
 * @sta_statistics: Get statistics क्रम this station. For example with beacon
 *	filtering, the statistics kept by mac80211 might not be accurate, so
 *	let the driver pre-fill the statistics. The driver can fill most of
 *	the values (indicating which by setting the filled biपंचांगap), but not
 *	all of them make sense - see the source क्रम which ones are possible.
 *	Statistics that the driver करोesn't fill will be filled by mac80211.
 *	The callback can sleep.
 *
 * @conf_tx: Configure TX queue parameters (EDCF (aअगरs, cw_min, cw_max),
 *	bursting) क्रम a hardware TX queue.
 *	Returns a negative error code on failure.
 *	The callback can sleep.
 *
 * @get_tsf: Get the current TSF समयr value from firmware/hardware. Currently,
 *	this is only used क्रम IBSS mode BSSID merging and debugging. Is not a
 *	required function.
 *	The callback can sleep.
 *
 * @set_tsf: Set the TSF समयr to the specअगरied value in the firmware/hardware.
 *	Currently, this is only used क्रम IBSS mode debugging. Is not a
 *	required function.
 *	The callback can sleep.
 *
 * @offset_tsf: Offset the TSF समयr by the specअगरied value in the
 *	firmware/hardware.  Preferred to set_tsf as it aव्योमs delay between
 *	calling set_tsf() and hardware getting programmed, which will show up
 *	as TSF delay. Is not a required function.
 *	The callback can sleep.
 *
 * @reset_tsf: Reset the TSF समयr and allow firmware/hardware to synchronize
 *	with other STAs in the IBSS. This is only used in IBSS mode. This
 *	function is optional अगर the firmware/hardware takes full care of
 *	TSF synchronization.
 *	The callback can sleep.
 *
 * @tx_last_beacon: Determine whether the last IBSS beacon was sent by us.
 *	This is needed only क्रम IBSS mode and the result of this function is
 *	used to determine whether to reply to Probe Requests.
 *	Returns non-zero अगर this device sent the last beacon.
 *	The callback can sleep.
 *
 * @get_survey: Return per-channel survey inक्रमmation
 *
 * @rfसमाप्त_poll: Poll rfसमाप्त hardware state. If you need this, you also
 *	need to set wiphy->rfसमाप्त_poll to %true beक्रमe registration,
 *	and need to call wiphy_rfसमाप्त_set_hw_state() in the callback.
 *	The callback can sleep.
 *
 * @set_coverage_class: Set slot समय क्रम given coverage class as specअगरied
 *	in IEEE 802.11-2007 section 17.3.8.6 and modअगरy ACK समयout
 *	accordingly; coverage class equals to -1 to enable ACK समयout
 *	estimation algorithm (dynack). To disable dynack set valid value क्रम
 *	coverage class. This callback is not required and may sleep.
 *
 * @tesपंचांगode_cmd: Implement a cfg80211 test mode command. The passed @vअगर may
 *	be %शून्य. The callback can sleep.
 * @tesपंचांगode_dump: Implement a cfg80211 test mode dump. The callback can sleep.
 *
 * @flush: Flush all pending frames from the hardware queue, making sure
 *	that the hardware queues are empty. The @queues parameter is a biपंचांगap
 *	of queues to flush, which is useful अगर dअगरferent भव पूर्णांकerfaces
 *	use dअगरferent hardware queues; it may also indicate all queues.
 *	If the parameter @drop is set to %true, pending frames may be dropped.
 *	Note that vअगर can be शून्य.
 *	The callback can sleep.
 *
 * @channel_चयन: Drivers that need (or want) to offload the channel
 *	चयन operation क्रम CSAs received from the AP may implement this
 *	callback. They must then call ieee80211_chचयन_करोne() to indicate
 *	completion of the channel चयन.
 *
 * @set_antenna: Set antenna configuration (tx_ant, rx_ant) on the device.
 *	Parameters are biपंचांगaps of allowed antennas to use क्रम TX/RX. Drivers may
 *	reject TX/RX mask combinations they cannot support by वापसing -EINVAL
 *	(also see nl80211.h @NL80211_ATTR_WIPHY_ANTENNA_TX).
 *
 * @get_antenna: Get current antenna configuration from device (tx_ant, rx_ant).
 *
 * @reमुख्य_on_channel: Starts an off-channel period on the given channel, must
 *	call back to ieee80211_पढ़ोy_on_channel() when on that channel. Note
 *	that normal channel traffic is not stopped as this is पूर्णांकended क्रम hw
 *	offload. Frames to transmit on the off-channel channel are transmitted
 *	normally except क्रम the %IEEE80211_TX_CTL_TX_OFFCHAN flag. When the
 *	duration (which will always be non-zero) expires, the driver must call
 *	ieee80211_reमुख्य_on_channel_expired().
 *	Note that this callback may be called जबतक the device is in IDLE and
 *	must be accepted in this हाल.
 *	This callback may sleep.
 * @cancel_reमुख्य_on_channel: Requests that an ongoing off-channel period is
 *	पातed beक्रमe it expires. This callback may sleep.
 *
 * @set_ringparam: Set tx and rx ring sizes.
 *
 * @get_ringparam: Get tx and rx ring current and maximum sizes.
 *
 * @tx_frames_pending: Check अगर there is any pending frame in the hardware
 *	queues beक्रमe entering घातer save.
 *
 * @set_bitrate_mask: Set a mask of rates to be used क्रम rate control selection
 *	when transmitting a frame. Currently only legacy rates are handled.
 *	The callback can sleep.
 * @event_callback: Notअगरy driver about any event in mac80211. See
 *	&क्रमागत ieee80211_event_type क्रम the dअगरferent types.
 *	The callback must be atomic.
 *
 * @release_buffered_frames: Release buffered frames according to the given
 *	parameters. In the हाल where the driver buffers some frames क्रम
 *	sleeping stations mac80211 will use this callback to tell the driver
 *	to release some frames, either क्रम PS-poll or uAPSD.
 *	Note that अगर the @more_data parameter is %false the driver must check
 *	अगर there are more frames on the given TIDs, and अगर there are more than
 *	the frames being released then it must still set the more-data bit in
 *	the frame. If the @more_data parameter is %true, then of course the
 *	more-data bit must always be set.
 *	The @tids parameter tells the driver which TIDs to release frames
 *	from, क्रम PS-poll it will always have only a single bit set.
 *	In the हाल this is used क्रम a PS-poll initiated release, the
 *	@num_frames parameter will always be 1 so code can be shared. In
 *	this हाल the driver must also set %IEEE80211_TX_STATUS_EOSP flag
 *	on the TX status (and must report TX status) so that the PS-poll
 *	period is properly ended. This is used to aव्योम sending multiple
 *	responses क्रम a retried PS-poll frame.
 *	In the हाल this is used क्रम uAPSD, the @num_frames parameter may be
 *	bigger than one, but the driver may send fewer frames (it must send
 *	at least one, however). In this हाल it is also responsible क्रम
 *	setting the EOSP flag in the QoS header of the frames. Also, when the
 *	service period ends, the driver must set %IEEE80211_TX_STATUS_EOSP
 *	on the last frame in the SP. Alternatively, it may call the function
 *	ieee80211_sta_eosp() to inक्रमm mac80211 of the end of the SP.
 *	This callback must be atomic.
 * @allow_buffered_frames: Prepare device to allow the given number of frames
 *	to go out to the given station. The frames will be sent by mac80211
 *	via the usual TX path after this call. The TX inक्रमmation क्रम frames
 *	released will also have the %IEEE80211_TX_CTL_NO_PS_BUFFER flag set
 *	and the last one will also have %IEEE80211_TX_STATUS_EOSP set. In हाल
 *	frames from multiple TIDs are released and the driver might reorder
 *	them between the TIDs, it must set the %IEEE80211_TX_STATUS_EOSP flag
 *	on the last frame and clear it on all others and also handle the EOSP
 *	bit in the QoS header correctly. Alternatively, it can also call the
 *	ieee80211_sta_eosp() function.
 *	The @tids parameter is a biपंचांगap and tells the driver which TIDs the
 *	frames will be on; it will at most have two bits set.
 *	This callback must be atomic.
 *
 * @get_et_sset_count:  Ethtool API to get string-set count.
 *
 * @get_et_stats:  Ethtool API to get a set of u64 stats.
 *
 * @get_et_strings:  Ethtool API to get a set of strings to describe stats
 *	and perhaps other supported types of ethtool data-sets.
 *
 * @mgd_prepare_tx: Prepare क्रम transmitting a management frame क्रम association
 *	beक्रमe associated. In multi-channel scenarios, a भव पूर्णांकerface is
 *	bound to a channel beक्रमe it is associated, but as it isn't associated
 *	yet it need not necessarily be given airसमय, in particular since any
 *	transmission to a P2P GO needs to be synchronized against the GO's
 *	घातersave state. mac80211 will call this function beक्रमe transmitting a
 *	management frame prior to having successfully associated to allow the
 *	driver to give it channel समय क्रम the transmission, to get a response
 *	and to be able to synchronize with the GO.
 *	For drivers that set %IEEE80211_HW_DEAUTH_NEED_MGD_TX_PREP, mac80211
 *	would also call this function beक्रमe transmitting a deauthentication
 *	frame in हाल that no beacon was heard from the AP/P2P GO.
 *	The callback will be called beक्रमe each transmission and upon वापस
 *	mac80211 will transmit the frame right away.
 *      If duration is greater than zero, mac80211 hपूर्णांकs to the driver the
 *      duration क्रम which the operation is requested.
 *	The callback is optional and can (should!) sleep.
 *
 * @mgd_protect_tdls_discover: Protect a TDLS discovery session. After sending
 *	a TDLS discovery-request, we expect a reply to arrive on the AP's
 *	channel. We must stay on the channel (no PSM, scan, etc.), since a TDLS
 *	setup-response is a direct packet not buffered by the AP.
 *	mac80211 will call this function just beक्रमe the transmission of a TDLS
 *	discovery-request. The recommended period of protection is at least
 *	2 * (DTIM period).
 *	The callback is optional and can sleep.
 *
 * @add_chanctx: Notअगरies device driver about new channel context creation.
 *	This callback may sleep.
 * @हटाओ_chanctx: Notअगरies device driver about channel context deकाष्ठाion.
 *	This callback may sleep.
 * @change_chanctx: Notअगरies device driver about channel context changes that
 *	may happen when combining dअगरferent भव पूर्णांकerfaces on the same
 *	channel context with dअगरferent settings
 *	This callback may sleep.
 * @assign_vअगर_chanctx: Notअगरies device driver about channel context being bound
 *	to vअगर. Possible use is क्रम hw queue remapping.
 *	This callback may sleep.
 * @unassign_vअगर_chanctx: Notअगरies device driver about channel context being
 *	unbound from vअगर.
 *	This callback may sleep.
 * @चयन_vअगर_chanctx: चयन a number of vअगरs from one chanctx to
 *	another, as specअगरied in the list of
 *	@ieee80211_vअगर_chanctx_चयन passed to the driver, according
 *	to the mode defined in &ieee80211_chanctx_चयन_mode.
 *	This callback may sleep.
 *
 * @start_ap: Start operation on the AP पूर्णांकerface, this is called after all the
 *	inक्रमmation in bss_conf is set and beacon can be retrieved. A channel
 *	context is bound beक्रमe this is called. Note that अगर the driver uses
 *	software scan or ROC, this (and @stop_ap) isn't called when the AP is
 *	just "paused" क्रम scanning/ROC, which is indicated by the beacon being
 *	disabled/enabled via @bss_info_changed.
 * @stop_ap: Stop operation on the AP पूर्णांकerface.
 *
 * @reconfig_complete: Called after a call to ieee80211_restart_hw() and
 *	during resume, when the reconfiguration has completed.
 *	This can help the driver implement the reconfiguration step (and
 *	indicate mac80211 is पढ़ोy to receive frames).
 *	This callback may sleep.
 *
 * @ipv6_addr_change: IPv6 address assignment on the given पूर्णांकerface changed.
 *	Currently, this is only called क्रम managed or P2P client पूर्णांकerfaces.
 *	This callback is optional; it must not sleep.
 *
 * @channel_चयन_beacon: Starts a channel चयन to a new channel.
 *	Beacons are modअगरied to include CSA or ECSA IEs beक्रमe calling this
 *	function. The corresponding count fields in these IEs must be
 *	decremented, and when they reach 1 the driver must call
 *	ieee80211_csa_finish(). Drivers which use ieee80211_beacon_get()
 *	get the csa counter decremented by mac80211, but must check अगर it is
 *	1 using ieee80211_beacon_counter_is_complete() after the beacon has been
 *	transmitted and then call ieee80211_csa_finish().
 *	If the CSA count starts as zero or 1, this function will not be called,
 *	since there won't be any समय to beacon beक्रमe the चयन anyway.
 * @pre_channel_चयन: This is an optional callback that is called
 *	beक्रमe a channel चयन procedure is started (ie. when a STA
 *	माला_लो a CSA or a userspace initiated channel-चयन), allowing
 *	the driver to prepare क्रम the channel चयन.
 * @post_channel_चयन: This is an optional callback that is called
 *	after a channel चयन procedure is completed, allowing the
 *	driver to go back to a normal configuration.
 * @पात_channel_चयन: This is an optional callback that is called
 *	when channel चयन procedure was completed, allowing the
 *	driver to go back to a normal configuration.
 * @channel_चयन_rx_beacon: This is an optional callback that is called
 *	when channel चयन procedure is in progress and additional beacon with
 *	CSA IE was received, allowing driver to track changes in count.
 * @join_ibss: Join an IBSS (on an IBSS पूर्णांकerface); this is called after all
 *	inक्रमmation in bss_conf is set up and the beacon can be retrieved. A
 *	channel context is bound beक्रमe this is called.
 * @leave_ibss: Leave the IBSS again.
 *
 * @get_expected_throughput: extract the expected throughput towards the
 *	specअगरied station. The वापसed value is expressed in Kbps. It वापसs 0
 *	अगर the RC algorithm करोes not have proper data to provide.
 *
 * @get_txघातer: get current maximum tx घातer (in dBm) based on configuration
 *	and hardware limits.
 *
 * @tdls_channel_चयन: Start channel-चयनing with a TDLS peer. The driver
 *	is responsible क्रम continually initiating channel-चयनing operations
 *	and वापसing to the base channel क्रम communication with the AP. The
 *	driver receives a channel-चयन request ढाँचा and the location of
 *	the चयन-timing IE within the ढाँचा as part of the invocation.
 *	The ढाँचा is valid only within the call, and the driver can
 *	optionally copy the skb क्रम further re-use.
 * @tdls_cancel_channel_चयन: Stop channel-चयनing with a TDLS peer. Both
 *	peers must be on the base channel when the call completes.
 * @tdls_recv_channel_चयन: a TDLS channel-चयन related frame (request or
 *	response) has been received from a remote peer. The driver माला_लो
 *	parameters parsed from the incoming frame and may use them to जारी
 *	an ongoing channel-चयन operation. In addition, a channel-चयन
 *	response ढाँचा is provided, together with the location of the
 *	चयन-timing IE within the ढाँचा. The skb can only be used within
 *	the function call.
 *
 * @wake_tx_queue: Called when new packets have been added to the queue.
 * @sync_rx_queues: Process all pending frames in RSS queues. This is a
 *	synchronization which is needed in हाल driver has in its RSS queues
 *	pending frames that were received prior to the control path action
 *	currently taken (e.g. disassociation) but are not processed yet.
 *
 * @start_nan: join an existing न_अंक cluster, or create a new one.
 * @stop_nan: leave the न_अंक cluster.
 * @nan_change_conf: change न_अंक configuration. The data in cfg80211_nan_conf
 *	contains full new configuration and changes specअगरy which parameters
 *	are changed with respect to the last न_अंक config.
 *	The driver माला_लो both full configuration and the changed parameters since
 *	some devices may need the full configuration जबतक others need only the
 *	changed parameters.
 * @add_nan_func: Add a न_अंक function. Returns 0 on success. The data in
 *	cfg80211_nan_func must not be referenced outside the scope of
 *	this call.
 * @del_nan_func: Remove a न_अंक function. The driver must call
 *	ieee80211_nan_func_terminated() with
 *	NL80211_न_अंक_FUNC_TERM_REASON_USER_REQUEST reason code upon removal.
 * @can_aggregate_in_amsdu: Called in order to determine अगर HW supports
 *	aggregating two specअगरic frames in the same A-MSDU. The relation
 *	between the skbs should be symmetric and transitive. Note that जबतक
 *	skb is always a real frame, head may or may not be an A-MSDU.
 * @get_fपंचांग_responder_stats: Retrieve FTM responder statistics, अगर available.
 *	Statistics should be cumulative, currently no way to reset is provided.
 *
 * @start_pmsr: start peer measurement (e.g. FTM) (this call can sleep)
 * @पात_pmsr: पात peer measurement (this call can sleep)
 * @set_tid_config: Apply TID specअगरic configurations. This callback may sleep.
 * @reset_tid_config: Reset TID specअगरic configuration क्रम the peer.
 *	This callback may sleep.
 * @update_vअगर_offload: Update भव पूर्णांकerface offload flags
 *	This callback may sleep.
 * @sta_set_4addr: Called to notअगरy the driver when a station starts/stops using
 *	4-address mode
 * @set_sar_specs: Update the SAR (TX घातer) settings.
 * @sta_set_decap_offload: Called to notअगरy the driver when a station is allowed
 *	to use rx decapsulation offload
 */
काष्ठा ieee80211_ops अणु
	व्योम (*tx)(काष्ठा ieee80211_hw *hw,
		   काष्ठा ieee80211_tx_control *control,
		   काष्ठा sk_buff *skb);
	पूर्णांक (*start)(काष्ठा ieee80211_hw *hw);
	व्योम (*stop)(काष्ठा ieee80211_hw *hw);
#अगर_घोषित CONFIG_PM
	पूर्णांक (*suspend)(काष्ठा ieee80211_hw *hw, काष्ठा cfg80211_wowlan *wowlan);
	पूर्णांक (*resume)(काष्ठा ieee80211_hw *hw);
	व्योम (*set_wakeup)(काष्ठा ieee80211_hw *hw, bool enabled);
#पूर्ण_अगर
	पूर्णांक (*add_पूर्णांकerface)(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर);
	पूर्णांक (*change_पूर्णांकerface)(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				क्रमागत nl80211_अगरtype new_type, bool p2p);
	व्योम (*हटाओ_पूर्णांकerface)(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर);
	पूर्णांक (*config)(काष्ठा ieee80211_hw *hw, u32 changed);
	व्योम (*bss_info_changed)(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_bss_conf *info,
				 u32 changed);

	पूर्णांक (*start_ap)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*stop_ap)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);

	u64 (*prepare_multicast)(काष्ठा ieee80211_hw *hw,
				 काष्ठा netdev_hw_addr_list *mc_list);
	व्योम (*configure_filter)(काष्ठा ieee80211_hw *hw,
				 अचिन्हित पूर्णांक changed_flags,
				 अचिन्हित पूर्णांक *total_flags,
				 u64 multicast);
	व्योम (*config_अगरace_filter)(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    अचिन्हित पूर्णांक filter_flags,
				    अचिन्हित पूर्णांक changed_flags);
	पूर्णांक (*set_tim)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		       bool set);
	पूर्णांक (*set_key)(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
		       काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key);
	व्योम (*update_tkip_key)(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_key_conf *conf,
				काष्ठा ieee80211_sta *sta,
				u32 iv32, u16 *phase1key);
	व्योम (*set_rekey_data)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा cfg80211_gtk_rekey_data *data);
	व्योम (*set_शेष_unicast_key)(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर, पूर्णांक idx);
	पूर्णांक (*hw_scan)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_scan_request *req);
	व्योम (*cancel_hw_scan)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर);
	पूर्णांक (*sched_scan_start)(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा cfg80211_sched_scan_request *req,
				काष्ठा ieee80211_scan_ies *ies);
	पूर्णांक (*sched_scan_stop)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*sw_scan_start)(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      स्थिर u8 *mac_addr);
	व्योम (*sw_scan_complete)(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर);
	पूर्णांक (*get_stats)(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_low_level_stats *stats);
	व्योम (*get_key_seq)(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_key_conf *key,
			    काष्ठा ieee80211_key_seq *seq);
	पूर्णांक (*set_frag_threshold)(काष्ठा ieee80211_hw *hw, u32 value);
	पूर्णांक (*set_rts_threshold)(काष्ठा ieee80211_hw *hw, u32 value);
	पूर्णांक (*sta_add)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		       काष्ठा ieee80211_sta *sta);
	पूर्णांक (*sta_हटाओ)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_sta *sta);
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	व्योम (*sta_add_debugfs)(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta,
				काष्ठा dentry *dir);
#पूर्ण_अगर
	व्योम (*sta_notअगरy)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			क्रमागत sta_notअगरy_cmd, काष्ठा ieee80211_sta *sta);
	पूर्णांक (*sta_set_txpwr)(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta);
	पूर्णांक (*sta_state)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta,
			 क्रमागत ieee80211_sta_state old_state,
			 क्रमागत ieee80211_sta_state new_state);
	व्योम (*sta_pre_rcu_हटाओ)(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta);
	व्योम (*sta_rc_update)(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta,
			      u32 changed);
	व्योम (*sta_rate_tbl_update)(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_sta *sta);
	व्योम (*sta_statistics)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा station_info *sinfo);
	पूर्णांक (*conf_tx)(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_vअगर *vअगर, u16 ac,
		       स्थिर काष्ठा ieee80211_tx_queue_params *params);
	u64 (*get_tsf)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*set_tsf)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			u64 tsf);
	व्योम (*offset_tsf)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   s64 offset);
	व्योम (*reset_tsf)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
	पूर्णांक (*tx_last_beacon)(काष्ठा ieee80211_hw *hw);

	/**
	 * @ampdu_action:
	 * Perक्रमm a certain A-MPDU action.
	 * The RA/TID combination determines the destination and TID we want
	 * the ampdu action to be perक्रमmed क्रम. The action is defined through
	 * ieee80211_ampdu_mlme_action.
	 * When the action is set to %IEEE80211_AMPDU_TX_OPERATIONAL the driver
	 * may neither send aggregates containing more subframes than @buf_size
	 * nor send aggregates in a way that lost frames would exceed the
	 * buffer size. If just limiting the aggregate size, this would be
	 * possible with a buf_size of 8:
	 *
	 * - ``TX: 1.....7``
	 * - ``RX:  2....7`` (lost frame #1)
	 * - ``TX:        8..1...``
	 *
	 * which is invalid since #1 was now re-transmitted well past the
	 * buffer size of 8. Correct ways to retransmit #1 would be:
	 *
	 * - ``TX:        1   or``
	 * - ``TX:        18  or``
	 * - ``TX:        81``
	 *
	 * Even ``189`` would be wrong since 1 could be lost again.
	 *
	 * Returns a negative error code on failure. The driver may वापस
	 * %IEEE80211_AMPDU_TX_START_IMMEDIATE क्रम %IEEE80211_AMPDU_TX_START
	 * अगर the session can start immediately.
	 *
	 * The callback can sleep.
	 */
	पूर्णांक (*ampdu_action)(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_ampdu_params *params);
	पूर्णांक (*get_survey)(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
		काष्ठा survey_info *survey);
	व्योम (*rfसमाप्त_poll)(काष्ठा ieee80211_hw *hw);
	व्योम (*set_coverage_class)(काष्ठा ieee80211_hw *hw, s16 coverage_class);
#अगर_घोषित CONFIG_NL80211_TESTMODE
	पूर्णांक (*tesपंचांगode_cmd)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			    व्योम *data, पूर्णांक len);
	पूर्णांक (*tesपंचांगode_dump)(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb,
			     व्योम *data, पूर्णांक len);
#पूर्ण_अगर
	व्योम (*flush)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		      u32 queues, bool drop);
	व्योम (*channel_चयन)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_channel_चयन *ch_चयन);
	पूर्णांक (*set_antenna)(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant);
	पूर्णांक (*get_antenna)(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant);

	पूर्णांक (*reमुख्य_on_channel)(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_channel *chan,
				 पूर्णांक duration,
				 क्रमागत ieee80211_roc_type type);
	पूर्णांक (*cancel_reमुख्य_on_channel)(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर);
	पूर्णांक (*set_ringparam)(काष्ठा ieee80211_hw *hw, u32 tx, u32 rx);
	व्योम (*get_ringparam)(काष्ठा ieee80211_hw *hw,
			      u32 *tx, u32 *tx_max, u32 *rx, u32 *rx_max);
	bool (*tx_frames_pending)(काष्ठा ieee80211_hw *hw);
	पूर्णांक (*set_bitrate_mask)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
				स्थिर काष्ठा cfg80211_bitrate_mask *mask);
	व्योम (*event_callback)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       स्थिर काष्ठा ieee80211_event *event);

	व्योम (*allow_buffered_frames)(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_sta *sta,
				      u16 tids, पूर्णांक num_frames,
				      क्रमागत ieee80211_frame_release_type reason,
				      bool more_data);
	व्योम (*release_buffered_frames)(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_sta *sta,
					u16 tids, पूर्णांक num_frames,
					क्रमागत ieee80211_frame_release_type reason,
					bool more_data);

	पूर्णांक	(*get_et_sset_count)(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset);
	व्योम	(*get_et_stats)(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ethtool_stats *stats, u64 *data);
	व्योम	(*get_et_strings)(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  u32 sset, u8 *data);

	व्योम	(*mgd_prepare_tx)(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  u16 duration);

	व्योम	(*mgd_protect_tdls_discover)(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_vअगर *vअगर);

	पूर्णांक (*add_chanctx)(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_chanctx_conf *ctx);
	व्योम (*हटाओ_chanctx)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_chanctx_conf *ctx);
	व्योम (*change_chanctx)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_chanctx_conf *ctx,
			       u32 changed);
	पूर्णांक (*assign_vअगर_chanctx)(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_chanctx_conf *ctx);
	व्योम (*unassign_vअगर_chanctx)(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_chanctx_conf *ctx);
	पूर्णांक (*चयन_vअगर_chanctx)(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
				  पूर्णांक n_vअगरs,
				  क्रमागत ieee80211_chanctx_चयन_mode mode);

	व्योम (*reconfig_complete)(काष्ठा ieee80211_hw *hw,
				  क्रमागत ieee80211_reconfig_type reconfig_type);

#अगर IS_ENABLED(CONFIG_IPV6)
	व्योम (*ipv6_addr_change)(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा inet6_dev *idev);
#पूर्ण_अगर
	व्योम (*channel_चयन_beacon)(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा cfg80211_chan_def *chandef);
	पूर्णांक (*pre_channel_चयन)(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  काष्ठा ieee80211_channel_चयन *ch_चयन);

	पूर्णांक (*post_channel_चयन)(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*पात_channel_चयन)(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*channel_चयन_rx_beacon)(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा ieee80211_channel_चयन *ch_चयन);

	पूर्णांक (*join_ibss)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*leave_ibss)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);
	u32 (*get_expected_throughput)(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_sta *sta);
	पूर्णांक (*get_txघातer)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   पूर्णांक *dbm);

	पूर्णांक (*tdls_channel_चयन)(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_sta *sta, u8 oper_class,
				   काष्ठा cfg80211_chan_def *chandef,
				   काष्ठा sk_buff *पंचांगpl_skb, u32 ch_sw_पंचांग_ie);
	व्योम (*tdls_cancel_channel_चयन)(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर,
					   काष्ठा ieee80211_sta *sta);
	व्योम (*tdls_recv_channel_चयन)(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा ieee80211_tdls_ch_sw_params *params);

	व्योम (*wake_tx_queue)(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_txq *txq);
	व्योम (*sync_rx_queues)(काष्ठा ieee80211_hw *hw);

	पूर्णांक (*start_nan)(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा cfg80211_nan_conf *conf);
	पूर्णांक (*stop_nan)(काष्ठा ieee80211_hw *hw,
			काष्ठा ieee80211_vअगर *vअगर);
	पूर्णांक (*nan_change_conf)(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा cfg80211_nan_conf *conf, u32 changes);
	पूर्णांक (*add_nan_func)(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    स्थिर काष्ठा cfg80211_nan_func *nan_func);
	व्योम (*del_nan_func)(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    u8 instance_id);
	bool (*can_aggregate_in_amsdu)(काष्ठा ieee80211_hw *hw,
				       काष्ठा sk_buff *head,
				       काष्ठा sk_buff *skb);
	पूर्णांक (*get_fपंचांग_responder_stats)(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा cfg80211_fपंचांग_responder_stats *fपंचांग_stats);
	पूर्णांक (*start_pmsr)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा cfg80211_pmsr_request *request);
	व्योम (*पात_pmsr)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा cfg80211_pmsr_request *request);
	पूर्णांक (*set_tid_config)(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta,
			      काष्ठा cfg80211_tid_config *tid_conf);
	पूर्णांक (*reset_tid_config)(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta, u8 tids);
	व्योम (*update_vअगर_offload)(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर);
	व्योम (*sta_set_4addr)(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta, bool enabled);
	पूर्णांक (*set_sar_specs)(काष्ठा ieee80211_hw *hw,
			     स्थिर काष्ठा cfg80211_sar_specs *sar);
	व्योम (*sta_set_decap_offload)(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta, bool enabled);
पूर्ण;

/**
 * ieee80211_alloc_hw_nm - Allocate a new hardware device
 *
 * This must be called once क्रम each hardware device. The वापसed poपूर्णांकer
 * must be used to refer to this device when calling other functions.
 * mac80211 allocates a निजी data area क्रम the driver poपूर्णांकed to by
 * @priv in &काष्ठा ieee80211_hw, the size of this area is given as
 * @priv_data_len.
 *
 * @priv_data_len: length of निजी data
 * @ops: callbacks क्रम this device
 * @requested_name: Requested name क्रम this device.
 *	शून्य is valid value, and means use the शेष naming (phy%d)
 *
 * Return: A poपूर्णांकer to the new hardware device, or %शून्य on error.
 */
काष्ठा ieee80211_hw *ieee80211_alloc_hw_nm(माप_प्रकार priv_data_len,
					   स्थिर काष्ठा ieee80211_ops *ops,
					   स्थिर अक्षर *requested_name);

/**
 * ieee80211_alloc_hw - Allocate a new hardware device
 *
 * This must be called once क्रम each hardware device. The वापसed poपूर्णांकer
 * must be used to refer to this device when calling other functions.
 * mac80211 allocates a निजी data area क्रम the driver poपूर्णांकed to by
 * @priv in &काष्ठा ieee80211_hw, the size of this area is given as
 * @priv_data_len.
 *
 * @priv_data_len: length of निजी data
 * @ops: callbacks क्रम this device
 *
 * Return: A poपूर्णांकer to the new hardware device, or %शून्य on error.
 */
अटल अंतरभूत
काष्ठा ieee80211_hw *ieee80211_alloc_hw(माप_प्रकार priv_data_len,
					स्थिर काष्ठा ieee80211_ops *ops)
अणु
	वापस ieee80211_alloc_hw_nm(priv_data_len, ops, शून्य);
पूर्ण

/**
 * ieee80211_रेजिस्टर_hw - Register hardware device
 *
 * You must call this function beक्रमe any other functions in
 * mac80211. Note that beक्रमe a hardware can be रेजिस्टरed, you
 * need to fill the contained wiphy's inक्रमmation.
 *
 * @hw: the device to रेजिस्टर as वापसed by ieee80211_alloc_hw()
 *
 * Return: 0 on success. An error code otherwise.
 */
पूर्णांक ieee80211_रेजिस्टर_hw(काष्ठा ieee80211_hw *hw);

/**
 * काष्ठा ieee80211_tpt_blink - throughput blink description
 * @throughput: throughput in Kbit/sec
 * @blink_समय: blink समय in milliseconds
 *	(full cycle, ie. one off + one on period)
 */
काष्ठा ieee80211_tpt_blink अणु
	पूर्णांक throughput;
	पूर्णांक blink_समय;
पूर्ण;

/**
 * क्रमागत ieee80211_tpt_led_trigger_flags - throughput trigger flags
 * @IEEE80211_TPT_LEDTRIG_FL_RADIO: enable blinking with radio
 * @IEEE80211_TPT_LEDTRIG_FL_WORK: enable blinking when working
 * @IEEE80211_TPT_LEDTRIG_FL_CONNECTED: enable blinking when at least one
 *	पूर्णांकerface is connected in some way, including being an AP
 */
क्रमागत ieee80211_tpt_led_trigger_flags अणु
	IEEE80211_TPT_LEDTRIG_FL_RADIO		= BIT(0),
	IEEE80211_TPT_LEDTRIG_FL_WORK		= BIT(1),
	IEEE80211_TPT_LEDTRIG_FL_CONNECTED	= BIT(2),
पूर्ण;

#अगर_घोषित CONFIG_MAC80211_LEDS
स्थिर अक्षर *__ieee80211_get_tx_led_name(काष्ठा ieee80211_hw *hw);
स्थिर अक्षर *__ieee80211_get_rx_led_name(काष्ठा ieee80211_hw *hw);
स्थिर अक्षर *__ieee80211_get_assoc_led_name(काष्ठा ieee80211_hw *hw);
स्थिर अक्षर *__ieee80211_get_radio_led_name(काष्ठा ieee80211_hw *hw);
स्थिर अक्षर *
__ieee80211_create_tpt_led_trigger(काष्ठा ieee80211_hw *hw,
				   अचिन्हित पूर्णांक flags,
				   स्थिर काष्ठा ieee80211_tpt_blink *blink_table,
				   अचिन्हित पूर्णांक blink_table_len);
#पूर्ण_अगर
/**
 * ieee80211_get_tx_led_name - get name of TX LED
 *
 * mac80211 creates a transmit LED trigger क्रम each wireless hardware
 * that can be used to drive LEDs अगर your driver रेजिस्टरs a LED device.
 * This function वापसs the name (or %शून्य अगर not configured क्रम LEDs)
 * of the trigger so you can स्वतःmatically link the LED device.
 *
 * @hw: the hardware to get the LED trigger name क्रम
 *
 * Return: The name of the LED trigger. %शून्य अगर not configured क्रम LEDs.
 */
अटल अंतरभूत स्थिर अक्षर *ieee80211_get_tx_led_name(काष्ठा ieee80211_hw *hw)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	वापस __ieee80211_get_tx_led_name(hw);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/**
 * ieee80211_get_rx_led_name - get name of RX LED
 *
 * mac80211 creates a receive LED trigger क्रम each wireless hardware
 * that can be used to drive LEDs अगर your driver रेजिस्टरs a LED device.
 * This function वापसs the name (or %शून्य अगर not configured क्रम LEDs)
 * of the trigger so you can स्वतःmatically link the LED device.
 *
 * @hw: the hardware to get the LED trigger name क्रम
 *
 * Return: The name of the LED trigger. %शून्य अगर not configured क्रम LEDs.
 */
अटल अंतरभूत स्थिर अक्षर *ieee80211_get_rx_led_name(काष्ठा ieee80211_hw *hw)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	वापस __ieee80211_get_rx_led_name(hw);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/**
 * ieee80211_get_assoc_led_name - get name of association LED
 *
 * mac80211 creates a association LED trigger क्रम each wireless hardware
 * that can be used to drive LEDs अगर your driver रेजिस्टरs a LED device.
 * This function वापसs the name (or %शून्य अगर not configured क्रम LEDs)
 * of the trigger so you can स्वतःmatically link the LED device.
 *
 * @hw: the hardware to get the LED trigger name क्रम
 *
 * Return: The name of the LED trigger. %शून्य अगर not configured क्रम LEDs.
 */
अटल अंतरभूत स्थिर अक्षर *ieee80211_get_assoc_led_name(काष्ठा ieee80211_hw *hw)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	वापस __ieee80211_get_assoc_led_name(hw);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/**
 * ieee80211_get_radio_led_name - get name of radio LED
 *
 * mac80211 creates a radio change LED trigger क्रम each wireless hardware
 * that can be used to drive LEDs अगर your driver रेजिस्टरs a LED device.
 * This function वापसs the name (or %शून्य अगर not configured क्रम LEDs)
 * of the trigger so you can स्वतःmatically link the LED device.
 *
 * @hw: the hardware to get the LED trigger name क्रम
 *
 * Return: The name of the LED trigger. %शून्य अगर not configured क्रम LEDs.
 */
अटल अंतरभूत स्थिर अक्षर *ieee80211_get_radio_led_name(काष्ठा ieee80211_hw *hw)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	वापस __ieee80211_get_radio_led_name(hw);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/**
 * ieee80211_create_tpt_led_trigger - create throughput LED trigger
 * @hw: the hardware to create the trigger क्रम
 * @flags: trigger flags, see &क्रमागत ieee80211_tpt_led_trigger_flags
 * @blink_table: the blink table -- needs to be ordered by throughput
 * @blink_table_len: size of the blink table
 *
 * Return: %शून्य (in हाल of error, or अगर no LED triggers are
 * configured) or the name of the new trigger.
 *
 * Note: This function must be called beक्रमe ieee80211_रेजिस्टर_hw().
 */
अटल अंतरभूत स्थिर अक्षर *
ieee80211_create_tpt_led_trigger(काष्ठा ieee80211_hw *hw, अचिन्हित पूर्णांक flags,
				 स्थिर काष्ठा ieee80211_tpt_blink *blink_table,
				 अचिन्हित पूर्णांक blink_table_len)
अणु
#अगर_घोषित CONFIG_MAC80211_LEDS
	वापस __ieee80211_create_tpt_led_trigger(hw, flags, blink_table,
						  blink_table_len);
#अन्यथा
	वापस शून्य;
#पूर्ण_अगर
पूर्ण

/**
 * ieee80211_unरेजिस्टर_hw - Unरेजिस्टर a hardware device
 *
 * This function inकाष्ठाs mac80211 to मुक्त allocated resources
 * and unरेजिस्टर netdevices from the networking subप्रणाली.
 *
 * @hw: the hardware to unरेजिस्टर
 */
व्योम ieee80211_unरेजिस्टर_hw(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_मुक्त_hw - मुक्त hardware descriptor
 *
 * This function मुक्तs everything that was allocated, including the
 * निजी data क्रम the driver. You must call ieee80211_unरेजिस्टर_hw()
 * beक्रमe calling this function.
 *
 * @hw: the hardware to मुक्त
 */
व्योम ieee80211_मुक्त_hw(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_restart_hw - restart hardware completely
 *
 * Call this function when the hardware was restarted क्रम some reason
 * (hardware error, ...) and the driver is unable to restore its state
 * by itself. mac80211 assumes that at this poपूर्णांक the driver/hardware
 * is completely uninitialised and stopped, it starts the process by
 * calling the ->start() operation. The driver will need to reset all
 * पूर्णांकernal state that it has prior to calling this function.
 *
 * @hw: the hardware to restart
 */
व्योम ieee80211_restart_hw(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_rx_list - receive frame and store processed skbs in a list
 *
 * Use this function to hand received frames to mac80211. The receive
 * buffer in @skb must start with an IEEE 802.11 header. In हाल of a
 * paged @skb is used, the driver is recommended to put the ieee80211
 * header of the frame on the linear part of the @skb to aव्योम memory
 * allocation and/or स_नकल by the stack.
 *
 * This function may not be called in IRQ context. Calls to this function
 * क्रम a single hardware must be synchronized against each other. Calls to
 * this function, ieee80211_rx_ni() and ieee80211_rx_irqsafe() may not be
 * mixed क्रम a single hardware. Must not run concurrently with
 * ieee80211_tx_status() or ieee80211_tx_status_ni().
 *
 * This function must be called with BHs disabled and RCU पढ़ो lock
 *
 * @hw: the hardware this frame came in on
 * @sta: the station the frame was received from, or %शून्य
 * @skb: the buffer to receive, owned by mac80211 after this call
 * @list: the destination list
 */
व्योम ieee80211_rx_list(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		       काष्ठा sk_buff *skb, काष्ठा list_head *list);

/**
 * ieee80211_rx_napi - receive frame from NAPI context
 *
 * Use this function to hand received frames to mac80211. The receive
 * buffer in @skb must start with an IEEE 802.11 header. In हाल of a
 * paged @skb is used, the driver is recommended to put the ieee80211
 * header of the frame on the linear part of the @skb to aव्योम memory
 * allocation and/or स_नकल by the stack.
 *
 * This function may not be called in IRQ context. Calls to this function
 * क्रम a single hardware must be synchronized against each other. Calls to
 * this function, ieee80211_rx_ni() and ieee80211_rx_irqsafe() may not be
 * mixed क्रम a single hardware. Must not run concurrently with
 * ieee80211_tx_status() or ieee80211_tx_status_ni().
 *
 * This function must be called with BHs disabled.
 *
 * @hw: the hardware this frame came in on
 * @sta: the station the frame was received from, or %शून्य
 * @skb: the buffer to receive, owned by mac80211 after this call
 * @napi: the NAPI context
 */
व्योम ieee80211_rx_napi(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_sta *sta,
		       काष्ठा sk_buff *skb, काष्ठा napi_काष्ठा *napi);

/**
 * ieee80211_rx - receive frame
 *
 * Use this function to hand received frames to mac80211. The receive
 * buffer in @skb must start with an IEEE 802.11 header. In हाल of a
 * paged @skb is used, the driver is recommended to put the ieee80211
 * header of the frame on the linear part of the @skb to aव्योम memory
 * allocation and/or स_नकल by the stack.
 *
 * This function may not be called in IRQ context. Calls to this function
 * क्रम a single hardware must be synchronized against each other. Calls to
 * this function, ieee80211_rx_ni() and ieee80211_rx_irqsafe() may not be
 * mixed क्रम a single hardware. Must not run concurrently with
 * ieee80211_tx_status() or ieee80211_tx_status_ni().
 *
 * In process context use instead ieee80211_rx_ni().
 *
 * @hw: the hardware this frame came in on
 * @skb: the buffer to receive, owned by mac80211 after this call
 */
अटल अंतरभूत व्योम ieee80211_rx(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	ieee80211_rx_napi(hw, शून्य, skb, शून्य);
पूर्ण

/**
 * ieee80211_rx_irqsafe - receive frame
 *
 * Like ieee80211_rx() but can be called in IRQ context
 * (पूर्णांकernally defers to a tasklet.)
 *
 * Calls to this function, ieee80211_rx() or ieee80211_rx_ni() may not
 * be mixed क्रम a single hardware.Must not run concurrently with
 * ieee80211_tx_status() or ieee80211_tx_status_ni().
 *
 * @hw: the hardware this frame came in on
 * @skb: the buffer to receive, owned by mac80211 after this call
 */
व्योम ieee80211_rx_irqsafe(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);

/**
 * ieee80211_rx_ni - receive frame (in process context)
 *
 * Like ieee80211_rx() but can be called in process context
 * (पूर्णांकernally disables bottom halves).
 *
 * Calls to this function, ieee80211_rx() and ieee80211_rx_irqsafe() may
 * not be mixed क्रम a single hardware. Must not run concurrently with
 * ieee80211_tx_status() or ieee80211_tx_status_ni().
 *
 * @hw: the hardware this frame came in on
 * @skb: the buffer to receive, owned by mac80211 after this call
 */
अटल अंतरभूत व्योम ieee80211_rx_ni(काष्ठा ieee80211_hw *hw,
				   काष्ठा sk_buff *skb)
अणु
	local_bh_disable();
	ieee80211_rx(hw, skb);
	local_bh_enable();
पूर्ण

/**
 * ieee80211_sta_ps_transition - PS transition क्रम connected sta
 *
 * When operating in AP mode with the %IEEE80211_HW_AP_LINK_PS
 * flag set, use this function to inक्रमm mac80211 about a connected station
 * entering/leaving PS mode.
 *
 * This function may not be called in IRQ context or with softirqs enabled.
 *
 * Calls to this function क्रम a single hardware must be synchronized against
 * each other.
 *
 * @sta: currently connected sta
 * @start: start or stop PS
 *
 * Return: 0 on success. -EINVAL when the requested PS mode is alपढ़ोy set.
 */
पूर्णांक ieee80211_sta_ps_transition(काष्ठा ieee80211_sta *sta, bool start);

/**
 * ieee80211_sta_ps_transition_ni - PS transition क्रम connected sta
 *                                  (in process context)
 *
 * Like ieee80211_sta_ps_transition() but can be called in process context
 * (पूर्णांकernally disables bottom halves). Concurrent call restriction still
 * applies.
 *
 * @sta: currently connected sta
 * @start: start or stop PS
 *
 * Return: Like ieee80211_sta_ps_transition().
 */
अटल अंतरभूत पूर्णांक ieee80211_sta_ps_transition_ni(काष्ठा ieee80211_sta *sta,
						  bool start)
अणु
	पूर्णांक ret;

	local_bh_disable();
	ret = ieee80211_sta_ps_transition(sta, start);
	local_bh_enable();

	वापस ret;
पूर्ण

/**
 * ieee80211_sta_pspoll - PS-Poll frame received
 * @sta: currently connected station
 *
 * When operating in AP mode with the %IEEE80211_HW_AP_LINK_PS flag set,
 * use this function to inक्रमm mac80211 that a PS-Poll frame from a
 * connected station was received.
 * This must be used in conjunction with ieee80211_sta_ps_transition()
 * and possibly ieee80211_sta_uapsd_trigger(); calls to all three must
 * be serialized.
 */
व्योम ieee80211_sta_pspoll(काष्ठा ieee80211_sta *sta);

/**
 * ieee80211_sta_uapsd_trigger - (potential) U-APSD trigger frame received
 * @sta: currently connected station
 * @tid: TID of the received (potential) trigger frame
 *
 * When operating in AP mode with the %IEEE80211_HW_AP_LINK_PS flag set,
 * use this function to inक्रमm mac80211 that a (potential) trigger frame
 * from a connected station was received.
 * This must be used in conjunction with ieee80211_sta_ps_transition()
 * and possibly ieee80211_sta_pspoll(); calls to all three must be
 * serialized.
 * %IEEE80211_NUM_TIDS can be passed as the tid अगर the tid is unknown.
 * In this हाल, mac80211 will not check that this tid maps to an AC
 * that is trigger enabled and assume that the caller did the proper
 * checks.
 */
व्योम ieee80211_sta_uapsd_trigger(काष्ठा ieee80211_sta *sta, u8 tid);

/*
 * The TX headroom reserved by mac80211 क्रम its own tx_status functions.
 * This is enough क्रम the radiotap header.
 */
#घोषणा IEEE80211_TX_STATUS_HEADROOM	ALIGN(14, 4)

/**
 * ieee80211_sta_set_buffered - inक्रमm mac80211 about driver-buffered frames
 * @sta: &काष्ठा ieee80211_sta poपूर्णांकer क्रम the sleeping station
 * @tid: the TID that has buffered frames
 * @buffered: indicates whether or not frames are buffered क्रम this TID
 *
 * If a driver buffers frames क्रम a घातersave station instead of passing
 * them back to mac80211 क्रम retransmission, the station may still need
 * to be told that there are buffered frames via the TIM bit.
 *
 * This function inक्रमms mac80211 whether or not there are frames that are
 * buffered in the driver क्रम a given TID; mac80211 can then use this data
 * to set the TIM bit (NOTE: This may call back पूर्णांकo the driver's set_tim
 * call! Beware of the locking!)
 *
 * If all frames are released to the station (due to PS-poll or uAPSD)
 * then the driver needs to inक्रमm mac80211 that there no दीर्घer are
 * frames buffered. However, when the station wakes up mac80211 assumes
 * that all buffered frames will be transmitted and clears this data,
 * drivers need to make sure they inक्रमm mac80211 about all buffered
 * frames on the sleep transition (sta_notअगरy() with %STA_NOTIFY_SLEEP).
 *
 * Note that technically mac80211 only needs to know this per AC, not per
 * TID, but since driver buffering will inevitably happen per TID (since
 * it is related to aggregation) it is easier to make mac80211 map the
 * TID to the AC as required instead of keeping track in all drivers that
 * use this API.
 */
व्योम ieee80211_sta_set_buffered(काष्ठा ieee80211_sta *sta,
				u8 tid, bool buffered);

/**
 * ieee80211_get_tx_rates - get the selected transmit rates क्रम a packet
 *
 * Call this function in a driver with per-packet rate selection support
 * to combine the rate info in the packet tx info with the most recent
 * rate selection table क्रम the station entry.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @sta: the receiver station to which this packet is sent.
 * @skb: the frame to be transmitted.
 * @dest: buffer क्रम extracted rate/retry inक्रमmation
 * @max_rates: maximum number of rates to fetch
 */
व्योम ieee80211_get_tx_rates(काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta,
			    काष्ठा sk_buff *skb,
			    काष्ठा ieee80211_tx_rate *dest,
			    पूर्णांक max_rates);

/**
 * ieee80211_sta_set_expected_throughput - set the expected tpt क्रम a station
 *
 * Call this function to notअगरy mac80211 about a change in expected throughput
 * to a station. A driver क्रम a device that करोes rate control in firmware can
 * call this function when the expected throughput estimate towards a station
 * changes. The inक्रमmation is used to tune the CoDel AQM applied to traffic
 * going towards that station (which can otherwise be too aggressive and cause
 * slow stations to starve).
 *
 * @pubsta: the station to set throughput क्रम.
 * @thr: the current expected throughput in kbps.
 */
व्योम ieee80211_sta_set_expected_throughput(काष्ठा ieee80211_sta *pubsta,
					   u32 thr);

/**
 * ieee80211_tx_rate_update - transmit rate update callback
 *
 * Drivers should call this functions with a non-शून्य pub sta
 * This function can be used in drivers that करोes not have provision
 * in updating the tx rate in data path.
 *
 * @hw: the hardware the frame was transmitted by
 * @pubsta: the station to update the tx rate क्रम.
 * @info: tx status inक्रमmation
 */
व्योम ieee80211_tx_rate_update(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_sta *pubsta,
			      काष्ठा ieee80211_tx_info *info);

/**
 * ieee80211_tx_status - transmit status callback
 *
 * Call this function क्रम all transmitted frames after they have been
 * transmitted. It is permissible to not call this function क्रम
 * multicast frames but this can affect statistics.
 *
 * This function may not be called in IRQ context. Calls to this function
 * क्रम a single hardware must be synchronized against each other. Calls
 * to this function, ieee80211_tx_status_ni() and ieee80211_tx_status_irqsafe()
 * may not be mixed क्रम a single hardware. Must not run concurrently with
 * ieee80211_rx() or ieee80211_rx_ni().
 *
 * @hw: the hardware the frame was transmitted by
 * @skb: the frame that was transmitted, owned by mac80211 after this call
 */
व्योम ieee80211_tx_status(काष्ठा ieee80211_hw *hw,
			 काष्ठा sk_buff *skb);

/**
 * ieee80211_tx_status_ext - extended transmit status callback
 *
 * This function can be used as a replacement क्रम ieee80211_tx_status
 * in drivers that may want to provide extra inक्रमmation that करोes not
 * fit पूर्णांकo &काष्ठा ieee80211_tx_info.
 *
 * Calls to this function क्रम a single hardware must be synchronized
 * against each other. Calls to this function, ieee80211_tx_status_ni()
 * and ieee80211_tx_status_irqsafe() may not be mixed क्रम a single hardware.
 *
 * @hw: the hardware the frame was transmitted by
 * @status: tx status inक्रमmation
 */
व्योम ieee80211_tx_status_ext(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_tx_status *status);

/**
 * ieee80211_tx_status_noskb - transmit status callback without skb
 *
 * This function can be used as a replacement क्रम ieee80211_tx_status
 * in drivers that cannot reliably map tx status inक्रमmation back to
 * specअगरic skbs.
 *
 * Calls to this function क्रम a single hardware must be synchronized
 * against each other. Calls to this function, ieee80211_tx_status_ni()
 * and ieee80211_tx_status_irqsafe() may not be mixed क्रम a single hardware.
 *
 * @hw: the hardware the frame was transmitted by
 * @sta: the receiver station to which this packet is sent
 *	(शून्य क्रम multicast packets)
 * @info: tx status inक्रमmation
 */
अटल अंतरभूत व्योम ieee80211_tx_status_noskb(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_sta *sta,
					     काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा ieee80211_tx_status status = अणु
		.sta = sta,
		.info = info,
	पूर्ण;

	ieee80211_tx_status_ext(hw, &status);
पूर्ण

/**
 * ieee80211_tx_status_ni - transmit status callback (in process context)
 *
 * Like ieee80211_tx_status() but can be called in process context.
 *
 * Calls to this function, ieee80211_tx_status() and
 * ieee80211_tx_status_irqsafe() may not be mixed
 * क्रम a single hardware.
 *
 * @hw: the hardware the frame was transmitted by
 * @skb: the frame that was transmitted, owned by mac80211 after this call
 */
अटल अंतरभूत व्योम ieee80211_tx_status_ni(काष्ठा ieee80211_hw *hw,
					  काष्ठा sk_buff *skb)
अणु
	local_bh_disable();
	ieee80211_tx_status(hw, skb);
	local_bh_enable();
पूर्ण

/**
 * ieee80211_tx_status_irqsafe - IRQ-safe transmit status callback
 *
 * Like ieee80211_tx_status() but can be called in IRQ context
 * (पूर्णांकernally defers to a tasklet.)
 *
 * Calls to this function, ieee80211_tx_status() and
 * ieee80211_tx_status_ni() may not be mixed क्रम a single hardware.
 *
 * @hw: the hardware the frame was transmitted by
 * @skb: the frame that was transmitted, owned by mac80211 after this call
 */
व्योम ieee80211_tx_status_irqsafe(काष्ठा ieee80211_hw *hw,
				 काष्ठा sk_buff *skb);

/**
 * ieee80211_tx_status_8023 - transmit status callback क्रम 802.3 frame क्रमmat
 *
 * Call this function क्रम all transmitted data frames after their transmit
 * completion. This callback should only be called क्रम data frames which
 * are using driver's (or hardware's) offload capability of encap/decap
 * 802.11 frames.
 *
 * This function may not be called in IRQ context. Calls to this function
 * क्रम a single hardware must be synchronized against each other and all
 * calls in the same tx status family.
 *
 * @hw: the hardware the frame was transmitted by
 * @vअगर: the पूर्णांकerface क्रम which the frame was transmitted
 * @skb: the frame that was transmitted, owned by mac80211 after this call
 */
व्योम ieee80211_tx_status_8023(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा sk_buff *skb);

/**
 * ieee80211_report_low_ack - report non-responding station
 *
 * When operating in AP-mode, call this function to report a non-responding
 * connected STA.
 *
 * @sta: the non-responding connected sta
 * @num_packets: number of packets sent to @sta without a response
 */
व्योम ieee80211_report_low_ack(काष्ठा ieee80211_sta *sta, u32 num_packets);

#घोषणा IEEE80211_MAX_CNTDWN_COUNTERS_NUM 2

/**
 * काष्ठा ieee80211_mutable_offsets - mutable beacon offsets
 * @tim_offset: position of TIM element
 * @tim_length: size of TIM element
 * @cntdwn_counter_offs: array of IEEE80211_MAX_CNTDWN_COUNTERS_NUM offsets
 *	to countकरोwn counters.  This array can contain zero values which
 *	should be ignored.
 */
काष्ठा ieee80211_mutable_offsets अणु
	u16 tim_offset;
	u16 tim_length;

	u16 cntdwn_counter_offs[IEEE80211_MAX_CNTDWN_COUNTERS_NUM];
पूर्ण;

/**
 * ieee80211_beacon_get_ढाँचा - beacon ढाँचा generation function
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @offs: &काष्ठा ieee80211_mutable_offsets poपूर्णांकer to काष्ठा that will
 *	receive the offsets that may be updated by the driver.
 *
 * If the driver implements beaconing modes, it must use this function to
 * obtain the beacon ढाँचा.
 *
 * This function should be used अगर the beacon frames are generated by the
 * device, and then the driver must use the वापसed beacon as the ढाँचा
 * The driver or the device are responsible to update the DTIM and, when
 * applicable, the CSA count.
 *
 * The driver is responsible क्रम मुक्तing the वापसed skb.
 *
 * Return: The beacon ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *
ieee80211_beacon_get_ढाँचा(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_mutable_offsets *offs);

/**
 * ieee80211_beacon_get_tim - beacon generation function
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @tim_offset: poपूर्णांकer to variable that will receive the TIM IE offset.
 *	Set to 0 अगर invalid (in non-AP modes).
 * @tim_length: poपूर्णांकer to variable that will receive the TIM IE length,
 *	(including the ID and length bytes!).
 *	Set to 0 अगर invalid (in non-AP modes).
 *
 * If the driver implements beaconing modes, it must use this function to
 * obtain the beacon frame.
 *
 * If the beacon frames are generated by the host प्रणाली (i.e., not in
 * hardware/firmware), the driver uses this function to get each beacon
 * frame from mac80211 -- it is responsible क्रम calling this function exactly
 * once beक्रमe the beacon is needed (e.g. based on hardware पूर्णांकerrupt).
 *
 * The driver is responsible क्रम मुक्तing the वापसed skb.
 *
 * Return: The beacon ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *ieee80211_beacon_get_tim(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_vअगर *vअगर,
					 u16 *tim_offset, u16 *tim_length);

/**
 * ieee80211_beacon_get - beacon generation function
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * See ieee80211_beacon_get_tim().
 *
 * Return: See ieee80211_beacon_get_tim().
 */
अटल अंतरभूत काष्ठा sk_buff *ieee80211_beacon_get(काष्ठा ieee80211_hw *hw,
						   काष्ठा ieee80211_vअगर *vअगर)
अणु
	वापस ieee80211_beacon_get_tim(hw, vअगर, शून्य, शून्य);
पूर्ण

/**
 * ieee80211_beacon_update_cntdwn - request mac80211 to decrement the beacon countकरोwn
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * The beacon counter should be updated after each beacon transmission.
 * This function is called implicitly when
 * ieee80211_beacon_get/ieee80211_beacon_get_tim are called, however अगर the
 * beacon frames are generated by the device, the driver should call this
 * function after each beacon transmission to sync mac80211's beacon countकरोwn.
 *
 * Return: new countकरोwn value
 */
u8 ieee80211_beacon_update_cntdwn(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_beacon_set_cntdwn - request mac80211 to set beacon countकरोwn
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @counter: the new value क्रम the counter
 *
 * The beacon countकरोwn can be changed by the device, this API should be
 * used by the device driver to update csa counter in mac80211.
 *
 * It should never be used together with ieee80211_beacon_update_cntdwn(),
 * as it will cause a race condition around the counter value.
 */
व्योम ieee80211_beacon_set_cntdwn(काष्ठा ieee80211_vअगर *vअगर, u8 counter);

/**
 * ieee80211_csa_finish - notअगरy mac80211 about channel चयन
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * After a channel चयन announcement was scheduled and the counter in this
 * announcement hits 1, this function must be called by the driver to
 * notअगरy mac80211 that the channel can be changed.
 */
व्योम ieee80211_csa_finish(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_beacon_cntdwn_is_complete - find out अगर countकरोwn reached 1
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * This function वापसs whether the countकरोwn reached zero.
 */
bool ieee80211_beacon_cntdwn_is_complete(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_proberesp_get - retrieve a Probe Response ढाँचा
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * Creates a Probe Response ढाँचा which can, क्रम example, be uploaded to
 * hardware. The destination address should be set by the caller.
 *
 * Can only be called in AP mode.
 *
 * Return: The Probe Response ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *ieee80211_proberesp_get(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_pspoll_get - retrieve a PS Poll ढाँचा
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * Creates a PS Poll a ढाँचा which can, क्रम example, uploaded to
 * hardware. The ढाँचा must be updated after association so that correct
 * AID, BSSID and MAC address is used.
 *
 * Note: Caller (or hardware) is responsible क्रम setting the
 * &IEEE80211_FCTL_PM bit.
 *
 * Return: The PS Poll ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *ieee80211_pspoll_get(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_nullfunc_get - retrieve a nullfunc ढाँचा
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @qos_ok: QoS NDP is acceptable to the caller, this should be set
 *	अगर at all possible
 *
 * Creates a Nullfunc ढाँचा which can, क्रम example, uploaded to
 * hardware. The ढाँचा must be updated after association so that correct
 * BSSID and address is used.
 *
 * If @qos_ndp is set and the association is to an AP with QoS/WMM, the
 * वापसed packet will be QoS NDP.
 *
 * Note: Caller (or hardware) is responsible क्रम setting the
 * &IEEE80211_FCTL_PM bit as well as Duration and Sequence Control fields.
 *
 * Return: The nullfunc ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *ieee80211_nullfunc_get(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       bool qos_ok);

/**
 * ieee80211_probereq_get - retrieve a Probe Request ढाँचा
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @src_addr: source MAC address
 * @ssid: SSID buffer
 * @ssid_len: length of SSID
 * @tailroom: tailroom to reserve at end of SKB क्रम IEs
 *
 * Creates a Probe Request ढाँचा which can, क्रम example, be uploaded to
 * hardware.
 *
 * Return: The Probe Request ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *ieee80211_probereq_get(काष्ठा ieee80211_hw *hw,
				       स्थिर u8 *src_addr,
				       स्थिर u8 *ssid, माप_प्रकार ssid_len,
				       माप_प्रकार tailroom);

/**
 * ieee80211_rts_get - RTS frame generation function
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @frame: poपूर्णांकer to the frame that is going to be रक्षित by the RTS.
 * @frame_len: the frame length (in octets).
 * @frame_txctl: &काष्ठा ieee80211_tx_info of the frame.
 * @rts: The buffer where to store the RTS frame.
 *
 * If the RTS frames are generated by the host प्रणाली (i.e., not in
 * hardware/firmware), the low-level driver uses this function to receive
 * the next RTS frame from the 802.11 code. The low-level is responsible
 * क्रम calling this function beक्रमe and RTS frame is needed.
 */
व्योम ieee80211_rts_get(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		       स्थिर व्योम *frame, माप_प्रकार frame_len,
		       स्थिर काष्ठा ieee80211_tx_info *frame_txctl,
		       काष्ठा ieee80211_rts *rts);

/**
 * ieee80211_rts_duration - Get the duration field क्रम an RTS frame
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @frame_len: the length of the frame that is going to be रक्षित by the RTS.
 * @frame_txctl: &काष्ठा ieee80211_tx_info of the frame.
 *
 * If the RTS is generated in firmware, but the host प्रणाली must provide
 * the duration field, the low-level driver uses this function to receive
 * the duration field value in little-endian byteorder.
 *
 * Return: The duration.
 */
__le16 ieee80211_rts_duration(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, माप_प्रकार frame_len,
			      स्थिर काष्ठा ieee80211_tx_info *frame_txctl);

/**
 * ieee80211_ctstoself_get - CTS-to-self frame generation function
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @frame: poपूर्णांकer to the frame that is going to be रक्षित by the CTS-to-self.
 * @frame_len: the frame length (in octets).
 * @frame_txctl: &काष्ठा ieee80211_tx_info of the frame.
 * @cts: The buffer where to store the CTS-to-self frame.
 *
 * If the CTS-to-self frames are generated by the host प्रणाली (i.e., not in
 * hardware/firmware), the low-level driver uses this function to receive
 * the next CTS-to-self frame from the 802.11 code. The low-level is responsible
 * क्रम calling this function beक्रमe and CTS-to-self frame is needed.
 */
व्योम ieee80211_ctstoself_get(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     स्थिर व्योम *frame, माप_प्रकार frame_len,
			     स्थिर काष्ठा ieee80211_tx_info *frame_txctl,
			     काष्ठा ieee80211_cts *cts);

/**
 * ieee80211_ctstoself_duration - Get the duration field क्रम a CTS-to-self frame
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @frame_len: the length of the frame that is going to be रक्षित by the CTS-to-self.
 * @frame_txctl: &काष्ठा ieee80211_tx_info of the frame.
 *
 * If the CTS-to-self is generated in firmware, but the host प्रणाली must provide
 * the duration field, the low-level driver uses this function to receive
 * the duration field value in little-endian byteorder.
 *
 * Return: The duration.
 */
__le16 ieee80211_ctstoself_duration(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    माप_प्रकार frame_len,
				    स्थिर काष्ठा ieee80211_tx_info *frame_txctl);

/**
 * ieee80211_generic_frame_duration - Calculate the duration field क्रम a frame
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @band: the band to calculate the frame duration on
 * @frame_len: the length of the frame.
 * @rate: the rate at which the frame is going to be transmitted.
 *
 * Calculate the duration field of some generic frame, given its
 * length and transmission rate (in 100kbps).
 *
 * Return: The duration.
 */
__le16 ieee80211_generic_frame_duration(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					क्रमागत nl80211_band band,
					माप_प्रकार frame_len,
					काष्ठा ieee80211_rate *rate);

/**
 * ieee80211_get_buffered_bc - accessing buffered broadcast and multicast frames
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * Function क्रम accessing buffered broadcast and multicast frames. If
 * hardware/firmware करोes not implement buffering of broadcast/multicast
 * frames when घातer saving is used, 802.11 code buffers them in the host
 * memory. The low-level driver uses this function to fetch next buffered
 * frame. In most हालs, this is used when generating beacon frame.
 *
 * Return: A poपूर्णांकer to the next buffered skb or शून्य अगर no more buffered
 * frames are available.
 *
 * Note: buffered frames are वापसed only after DTIM beacon frame was
 * generated with ieee80211_beacon_get() and the low-level driver must thus
 * call ieee80211_beacon_get() first. ieee80211_get_buffered_bc() वापसs
 * शून्य अगर the previous generated beacon was not DTIM, so the low-level driver
 * करोes not need to check क्रम DTIM beacons separately and should be able to
 * use common code क्रम all beacons.
 */
काष्ठा sk_buff *
ieee80211_get_buffered_bc(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_get_tkip_p1k_iv - get a TKIP phase 1 key क्रम IV32
 *
 * This function वापसs the TKIP phase 1 key क्रम the given IV32.
 *
 * @keyconf: the parameter passed with the set key
 * @iv32: IV32 to get the P1K क्रम
 * @p1k: a buffer to which the key will be written, as 5 u16 values
 */
व्योम ieee80211_get_tkip_p1k_iv(काष्ठा ieee80211_key_conf *keyconf,
			       u32 iv32, u16 *p1k);

/**
 * ieee80211_get_tkip_p1k - get a TKIP phase 1 key
 *
 * This function वापसs the TKIP phase 1 key क्रम the IV32 taken
 * from the given packet.
 *
 * @keyconf: the parameter passed with the set key
 * @skb: the packet to take the IV32 value from that will be encrypted
 *	with this P1K
 * @p1k: a buffer to which the key will be written, as 5 u16 values
 */
अटल अंतरभूत व्योम ieee80211_get_tkip_p1k(काष्ठा ieee80211_key_conf *keyconf,
					  काष्ठा sk_buff *skb, u16 *p1k)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	स्थिर u8 *data = (u8 *)hdr + ieee80211_hdrlen(hdr->frame_control);
	u32 iv32 = get_unaligned_le32(&data[4]);

	ieee80211_get_tkip_p1k_iv(keyconf, iv32, p1k);
पूर्ण

/**
 * ieee80211_get_tkip_rx_p1k - get a TKIP phase 1 key क्रम RX
 *
 * This function वापसs the TKIP phase 1 key क्रम the given IV32
 * and transmitter address.
 *
 * @keyconf: the parameter passed with the set key
 * @ta: TA that will be used with the key
 * @iv32: IV32 to get the P1K क्रम
 * @p1k: a buffer to which the key will be written, as 5 u16 values
 */
व्योम ieee80211_get_tkip_rx_p1k(काष्ठा ieee80211_key_conf *keyconf,
			       स्थिर u8 *ta, u32 iv32, u16 *p1k);

/**
 * ieee80211_get_tkip_p2k - get a TKIP phase 2 key
 *
 * This function computes the TKIP RC4 key क्रम the IV values
 * in the packet.
 *
 * @keyconf: the parameter passed with the set key
 * @skb: the packet to take the IV32/IV16 values from that will be
 *	encrypted with this key
 * @p2k: a buffer to which the key will be written, 16 bytes
 */
व्योम ieee80211_get_tkip_p2k(काष्ठा ieee80211_key_conf *keyconf,
			    काष्ठा sk_buff *skb, u8 *p2k);

/**
 * ieee80211_tkip_add_iv - ग_लिखो TKIP IV and Ext. IV to pos
 *
 * @pos: start of crypto header
 * @keyconf: the parameter passed with the set key
 * @pn: PN to add
 *
 * Returns: poपूर्णांकer to the octet following IVs (i.e. beginning of
 * the packet payload)
 *
 * This function ग_लिखोs the tkip IV value to pos (which should
 * poपूर्णांक to the crypto header)
 */
u8 *ieee80211_tkip_add_iv(u8 *pos, काष्ठा ieee80211_key_conf *keyconf, u64 pn);

/**
 * ieee80211_get_key_rx_seq - get key RX sequence counter
 *
 * @keyconf: the parameter passed with the set key
 * @tid: The TID, or -1 क्रम the management frame value (CCMP/GCMP only);
 *	the value on TID 0 is also used क्रम non-QoS frames. For
 *	CMAC, only TID 0 is valid.
 * @seq: buffer to receive the sequence data
 *
 * This function allows a driver to retrieve the current RX IV/PNs
 * क्रम the given key. It must not be called अगर IV checking is करोne
 * by the device and not by mac80211.
 *
 * Note that this function may only be called when no RX processing
 * can be करोne concurrently.
 */
व्योम ieee80211_get_key_rx_seq(काष्ठा ieee80211_key_conf *keyconf,
			      पूर्णांक tid, काष्ठा ieee80211_key_seq *seq);

/**
 * ieee80211_set_key_rx_seq - set key RX sequence counter
 *
 * @keyconf: the parameter passed with the set key
 * @tid: The TID, or -1 क्रम the management frame value (CCMP/GCMP only);
 *	the value on TID 0 is also used क्रम non-QoS frames. For
 *	CMAC, only TID 0 is valid.
 * @seq: new sequence data
 *
 * This function allows a driver to set the current RX IV/PNs क्रम the
 * given key. This is useful when resuming from WoWLAN sleep and GTK
 * rekey may have been करोne जबतक suspended. It should not be called
 * अगर IV checking is करोne by the device and not by mac80211.
 *
 * Note that this function may only be called when no RX processing
 * can be करोne concurrently.
 */
व्योम ieee80211_set_key_rx_seq(काष्ठा ieee80211_key_conf *keyconf,
			      पूर्णांक tid, काष्ठा ieee80211_key_seq *seq);

/**
 * ieee80211_हटाओ_key - हटाओ the given key
 * @keyconf: the parameter passed with the set key
 *
 * Remove the given key. If the key was uploaded to the hardware at the
 * समय this function is called, it is not deleted in the hardware but
 * instead assumed to have been हटाओd alपढ़ोy.
 *
 * Note that due to locking considerations this function can (currently)
 * only be called during key iteration (ieee80211_iter_keys().)
 */
व्योम ieee80211_हटाओ_key(काष्ठा ieee80211_key_conf *keyconf);

/**
 * ieee80211_gtk_rekey_add - add a GTK key from rekeying during WoWLAN
 * @vअगर: the भव पूर्णांकerface to add the key on
 * @keyconf: new key data
 *
 * When GTK rekeying was करोne जबतक the प्रणाली was suspended, (a) new
 * key(s) will be available. These will be needed by mac80211 क्रम proper
 * RX processing, so this function allows setting them.
 *
 * The function वापसs the newly allocated key काष्ठाure, which will
 * have similar contents to the passed key configuration but poपूर्णांक to
 * mac80211-owned memory. In हाल of errors, the function वापसs an
 * ERR_PTR(), use IS_ERR() etc.
 *
 * Note that this function assumes the key isn't added to hardware
 * acceleration, so no TX will be करोne with the key. Since it's a GTK
 * on managed (station) networks, this is true anyway. If the driver
 * calls this function from the resume callback and subsequently uses
 * the वापस code 1 to reconfigure the device, this key will be part
 * of the reconfiguration.
 *
 * Note that the driver should also call ieee80211_set_key_rx_seq()
 * क्रम the new key क्रम each TID to set up sequence counters properly.
 *
 * IMPORTANT: If this replaces a key that is present in the hardware,
 * then it will attempt to हटाओ it during this call. In many हालs
 * this isn't what you want, so call ieee80211_हटाओ_key() first क्रम
 * the key that's being replaced.
 */
काष्ठा ieee80211_key_conf *
ieee80211_gtk_rekey_add(काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_key_conf *keyconf);

/**
 * ieee80211_gtk_rekey_notअगरy - notअगरy userspace supplicant of rekeying
 * @vअगर: भव पूर्णांकerface the rekeying was करोne on
 * @bssid: The BSSID of the AP, क्रम checking association
 * @replay_ctr: the new replay counter after GTK rekeying
 * @gfp: allocation flags
 */
व्योम ieee80211_gtk_rekey_notअगरy(काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *bssid,
				स्थिर u8 *replay_ctr, gfp_t gfp);

/**
 * ieee80211_key_mic_failure - increment MIC failure counter क्रम the key
 *
 * Note: this is really only safe अगर no other RX function is called
 * at the same समय.
 *
 * @keyconf: the key in question
 */
व्योम ieee80211_key_mic_failure(काष्ठा ieee80211_key_conf *keyconf);

/**
 * ieee80211_key_replay - increment replay counter क्रम the key
 *
 * Note: this is really only safe अगर no other RX function is called
 * at the same समय.
 *
 * @keyconf: the key in question
 */
व्योम ieee80211_key_replay(काष्ठा ieee80211_key_conf *keyconf);

/**
 * ieee80211_wake_queue - wake specअगरic queue
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw().
 * @queue: queue number (counted from zero).
 *
 * Drivers should use this function instead of netअगर_wake_queue.
 */
व्योम ieee80211_wake_queue(काष्ठा ieee80211_hw *hw, पूर्णांक queue);

/**
 * ieee80211_stop_queue - stop specअगरic queue
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw().
 * @queue: queue number (counted from zero).
 *
 * Drivers should use this function instead of netअगर_stop_queue.
 */
व्योम ieee80211_stop_queue(काष्ठा ieee80211_hw *hw, पूर्णांक queue);

/**
 * ieee80211_queue_stopped - test status of the queue
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw().
 * @queue: queue number (counted from zero).
 *
 * Drivers should use this function instead of netअगर_stop_queue.
 *
 * Return: %true अगर the queue is stopped. %false otherwise.
 */

पूर्णांक ieee80211_queue_stopped(काष्ठा ieee80211_hw *hw, पूर्णांक queue);

/**
 * ieee80211_stop_queues - stop all queues
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw().
 *
 * Drivers should use this function instead of netअगर_stop_queue.
 */
व्योम ieee80211_stop_queues(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_wake_queues - wake all queues
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw().
 *
 * Drivers should use this function instead of netअगर_wake_queue.
 */
व्योम ieee80211_wake_queues(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_scan_completed - completed hardware scan
 *
 * When hardware scan offload is used (i.e. the hw_scan() callback is
 * asचिन्हित) this function needs to be called by the driver to notअगरy
 * mac80211 that the scan finished. This function can be called from
 * any context, including hardirq context.
 *
 * @hw: the hardware that finished the scan
 * @info: inक्रमmation about the completed scan
 */
व्योम ieee80211_scan_completed(काष्ठा ieee80211_hw *hw,
			      काष्ठा cfg80211_scan_info *info);

/**
 * ieee80211_sched_scan_results - got results from scheduled scan
 *
 * When a scheduled scan is running, this function needs to be called by the
 * driver whenever there are new scan results available.
 *
 * @hw: the hardware that is perक्रमming scheduled scans
 */
व्योम ieee80211_sched_scan_results(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_sched_scan_stopped - inक्रमm that the scheduled scan has stopped
 *
 * When a scheduled scan is running, this function can be called by
 * the driver अगर it needs to stop the scan to perक्रमm another task.
 * Usual scenarios are drivers that cannot जारी the scheduled scan
 * जबतक associating, क्रम instance.
 *
 * @hw: the hardware that is perक्रमming scheduled scans
 */
व्योम ieee80211_sched_scan_stopped(काष्ठा ieee80211_hw *hw);

/**
 * क्रमागत ieee80211_पूर्णांकerface_iteration_flags - पूर्णांकerface iteration flags
 * @IEEE80211_IFACE_ITER_NORMAL: Iterate over all पूर्णांकerfaces that have
 *	been added to the driver; However, note that during hardware
 *	reconfiguration (after restart_hw) it will iterate over a new
 *	पूर्णांकerface and over all the existing पूर्णांकerfaces even अगर they
 *	haven't been re-added to the driver yet.
 * @IEEE80211_IFACE_ITER_RESUME_ALL: During resume, iterate over all
 *	पूर्णांकerfaces, even अगर they haven't been re-added to the driver yet.
 * @IEEE80211_IFACE_ITER_ACTIVE: Iterate only active पूर्णांकerfaces (netdev is up).
 * @IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DRIVER: Skip any पूर्णांकerfaces where SDATA
 *	is not in the driver.  This may fix crashes during firmware recovery
 *	क्रम instance.
 */
क्रमागत ieee80211_पूर्णांकerface_iteration_flags अणु
	IEEE80211_IFACE_ITER_NORMAL	= 0,
	IEEE80211_IFACE_ITER_RESUME_ALL	= BIT(0),
	IEEE80211_IFACE_ITER_ACTIVE	= BIT(1),
	IEEE80211_IFACE_SKIP_SDATA_NOT_IN_DRIVER	= BIT(2),
पूर्ण;

/**
 * ieee80211_iterate_पूर्णांकerfaces - iterate पूर्णांकerfaces
 *
 * This function iterates over the पूर्णांकerfaces associated with a given
 * hardware and calls the callback क्रम them. This includes active as well as
 * inactive पूर्णांकerfaces. This function allows the iterator function to sleep.
 * Will iterate over a new पूर्णांकerface during add_पूर्णांकerface().
 *
 * @hw: the hardware काष्ठा of which the पूर्णांकerfaces should be iterated over
 * @iter_flags: iteration flags, see &क्रमागत ieee80211_पूर्णांकerface_iteration_flags
 * @iterator: the iterator function to call
 * @data: first argument of the iterator function
 */
व्योम ieee80211_iterate_पूर्णांकerfaces(काष्ठा ieee80211_hw *hw, u32 iter_flags,
				  व्योम (*iterator)(व्योम *data, u8 *mac,
						   काष्ठा ieee80211_vअगर *vअगर),
				  व्योम *data);

/**
 * ieee80211_iterate_active_पूर्णांकerfaces - iterate active पूर्णांकerfaces
 *
 * This function iterates over the पूर्णांकerfaces associated with a given
 * hardware that are currently active and calls the callback क्रम them.
 * This function allows the iterator function to sleep, when the iterator
 * function is atomic @ieee80211_iterate_active_पूर्णांकerfaces_atomic can
 * be used.
 * Does not iterate over a new पूर्णांकerface during add_पूर्णांकerface().
 *
 * @hw: the hardware काष्ठा of which the पूर्णांकerfaces should be iterated over
 * @iter_flags: iteration flags, see &क्रमागत ieee80211_पूर्णांकerface_iteration_flags
 * @iterator: the iterator function to call
 * @data: first argument of the iterator function
 */
अटल अंतरभूत व्योम
ieee80211_iterate_active_पूर्णांकerfaces(काष्ठा ieee80211_hw *hw, u32 iter_flags,
				    व्योम (*iterator)(व्योम *data, u8 *mac,
						     काष्ठा ieee80211_vअगर *vअगर),
				    व्योम *data)
अणु
	ieee80211_iterate_पूर्णांकerfaces(hw,
				     iter_flags | IEEE80211_IFACE_ITER_ACTIVE,
				     iterator, data);
पूर्ण

/**
 * ieee80211_iterate_active_पूर्णांकerfaces_atomic - iterate active पूर्णांकerfaces
 *
 * This function iterates over the पूर्णांकerfaces associated with a given
 * hardware that are currently active and calls the callback क्रम them.
 * This function requires the iterator callback function to be atomic,
 * अगर that is not desired, use @ieee80211_iterate_active_पूर्णांकerfaces instead.
 * Does not iterate over a new पूर्णांकerface during add_पूर्णांकerface().
 *
 * @hw: the hardware काष्ठा of which the पूर्णांकerfaces should be iterated over
 * @iter_flags: iteration flags, see &क्रमागत ieee80211_पूर्णांकerface_iteration_flags
 * @iterator: the iterator function to call, cannot sleep
 * @data: first argument of the iterator function
 */
व्योम ieee80211_iterate_active_पूर्णांकerfaces_atomic(काष्ठा ieee80211_hw *hw,
						u32 iter_flags,
						व्योम (*iterator)(व्योम *data,
						    u8 *mac,
						    काष्ठा ieee80211_vअगर *vअगर),
						व्योम *data);

/**
 * ieee80211_iterate_active_पूर्णांकerfaces_mtx - iterate active पूर्णांकerfaces
 *
 * This function iterates over the पूर्णांकerfaces associated with a given
 * hardware that are currently active and calls the callback क्रम them.
 * This version can only be used जबतक holding the wiphy mutex.
 *
 * @hw: the hardware काष्ठा of which the पूर्णांकerfaces should be iterated over
 * @iter_flags: iteration flags, see &क्रमागत ieee80211_पूर्णांकerface_iteration_flags
 * @iterator: the iterator function to call, cannot sleep
 * @data: first argument of the iterator function
 */
व्योम ieee80211_iterate_active_पूर्णांकerfaces_mtx(काष्ठा ieee80211_hw *hw,
					     u32 iter_flags,
					     व्योम (*iterator)(व्योम *data,
						u8 *mac,
						काष्ठा ieee80211_vअगर *vअगर),
					     व्योम *data);

/**
 * ieee80211_iterate_stations_atomic - iterate stations
 *
 * This function iterates over all stations associated with a given
 * hardware that are currently uploaded to the driver and calls the callback
 * function क्रम them.
 * This function requires the iterator callback function to be atomic,
 *
 * @hw: the hardware काष्ठा of which the पूर्णांकerfaces should be iterated over
 * @iterator: the iterator function to call, cannot sleep
 * @data: first argument of the iterator function
 */
व्योम ieee80211_iterate_stations_atomic(काष्ठा ieee80211_hw *hw,
				       व्योम (*iterator)(व्योम *data,
						काष्ठा ieee80211_sta *sta),
				       व्योम *data);
/**
 * ieee80211_queue_work - add work onto the mac80211 workqueue
 *
 * Drivers and mac80211 use this to add work onto the mac80211 workqueue.
 * This helper ensures drivers are not queueing work when they should not be.
 *
 * @hw: the hardware काष्ठा क्रम the पूर्णांकerface we are adding work क्रम
 * @work: the work we want to add onto the mac80211 workqueue
 */
व्योम ieee80211_queue_work(काष्ठा ieee80211_hw *hw, काष्ठा work_काष्ठा *work);

/**
 * ieee80211_queue_delayed_work - add work onto the mac80211 workqueue
 *
 * Drivers and mac80211 use this to queue delayed work onto the mac80211
 * workqueue.
 *
 * @hw: the hardware काष्ठा क्रम the पूर्णांकerface we are adding work क्रम
 * @dwork: delayable work to queue onto the mac80211 workqueue
 * @delay: number of jअगरfies to रुको beक्रमe queueing
 */
व्योम ieee80211_queue_delayed_work(काष्ठा ieee80211_hw *hw,
				  काष्ठा delayed_work *dwork,
				  अचिन्हित दीर्घ delay);

/**
 * ieee80211_start_tx_ba_session - Start a tx Block Ack session.
 * @sta: the station क्रम which to start a BA session
 * @tid: the TID to BA on.
 * @समयout: session समयout value (in TUs)
 *
 * Return: success अगर addBA request was sent, failure otherwise
 *
 * Although mac80211/low level driver/user space application can estimate
 * the need to start aggregation on a certain RA/TID, the session level
 * will be managed by the mac80211.
 */
पूर्णांक ieee80211_start_tx_ba_session(काष्ठा ieee80211_sta *sta, u16 tid,
				  u16 समयout);

/**
 * ieee80211_start_tx_ba_cb_irqsafe - low level driver पढ़ोy to aggregate.
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback
 * @ra: receiver address of the BA session recipient.
 * @tid: the TID to BA on.
 *
 * This function must be called by low level driver once it has
 * finished with preparations क्रम the BA session. It can be called
 * from any context.
 */
व्योम ieee80211_start_tx_ba_cb_irqsafe(काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *ra,
				      u16 tid);

/**
 * ieee80211_stop_tx_ba_session - Stop a Block Ack session.
 * @sta: the station whose BA session to stop
 * @tid: the TID to stop BA.
 *
 * Return: negative error अगर the TID is invalid, or no aggregation active
 *
 * Although mac80211/low level driver/user space application can estimate
 * the need to stop aggregation on a certain RA/TID, the session level
 * will be managed by the mac80211.
 */
पूर्णांक ieee80211_stop_tx_ba_session(काष्ठा ieee80211_sta *sta, u16 tid);

/**
 * ieee80211_stop_tx_ba_cb_irqsafe - low level driver पढ़ोy to stop aggregate.
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback
 * @ra: receiver address of the BA session recipient.
 * @tid: the desired TID to BA on.
 *
 * This function must be called by low level driver once it has
 * finished with preparations क्रम the BA session tear करोwn. It
 * can be called from any context.
 */
व्योम ieee80211_stop_tx_ba_cb_irqsafe(काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *ra,
				     u16 tid);

/**
 * ieee80211_find_sta - find a station
 *
 * @vअगर: भव पूर्णांकerface to look क्रम station on
 * @addr: station's address
 *
 * Return: The station, अगर found. %शून्य otherwise.
 *
 * Note: This function must be called under RCU lock and the
 * resulting poपूर्णांकer is only valid under RCU lock as well.
 */
काष्ठा ieee80211_sta *ieee80211_find_sta(काष्ठा ieee80211_vअगर *vअगर,
					 स्थिर u8 *addr);

/**
 * ieee80211_find_sta_by_अगरaddr - find a station on hardware
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @addr: remote station's address
 * @localaddr: local address (vअगर->sdata->vअगर.addr). Use शून्य क्रम 'any'.
 *
 * Return: The station, अगर found. %शून्य otherwise.
 *
 * Note: This function must be called under RCU lock and the
 * resulting poपूर्णांकer is only valid under RCU lock as well.
 *
 * NOTE: You may pass शून्य क्रम localaddr, but then you will just get
 *      the first STA that matches the remote address 'addr'.
 *      We can have multiple STA associated with multiple
 *      logical stations (e.g. consider a station connecting to another
 *      BSSID on the same AP hardware without disconnecting first).
 *      In this हाल, the result of this method with localaddr शून्य
 *      is not reliable.
 *
 * DO NOT USE THIS FUNCTION with localaddr शून्य अगर at all possible.
 */
काष्ठा ieee80211_sta *ieee80211_find_sta_by_अगरaddr(काष्ठा ieee80211_hw *hw,
					       स्थिर u8 *addr,
					       स्थिर u8 *localaddr);

/**
 * ieee80211_sta_block_awake - block station from waking up
 * @hw: the hardware
 * @pubsta: the station
 * @block: whether to block or unblock
 *
 * Some devices require that all frames that are on the queues
 * क्रम a specअगरic station that went to sleep are flushed beक्रमe
 * a poll response or frames after the station woke up can be
 * delivered to that it. Note that such frames must be rejected
 * by the driver as filtered, with the appropriate status flag.
 *
 * This function allows implementing this mode in a race-मुक्त
 * manner.
 *
 * To करो this, a driver must keep track of the number of frames
 * still enqueued क्रम a specअगरic station. If this number is not
 * zero when the station goes to sleep, the driver must call
 * this function to क्रमce mac80211 to consider the station to
 * be asleep regardless of the station's actual state. Once the
 * number of outstanding frames reaches zero, the driver must
 * call this function again to unblock the station. That will
 * cause mac80211 to be able to send ps-poll responses, and अगर
 * the station queried in the meanसमय then frames will also
 * be sent out as a result of this. Additionally, the driver
 * will be notअगरied that the station woke up some समय after
 * it is unblocked, regardless of whether the station actually
 * woke up जबतक blocked or not.
 */
व्योम ieee80211_sta_block_awake(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_sta *pubsta, bool block);

/**
 * ieee80211_sta_eosp - notअगरy mac80211 about end of SP
 * @pubsta: the station
 *
 * When a device transmits frames in a way that it can't tell
 * mac80211 in the TX status about the EOSP, it must clear the
 * %IEEE80211_TX_STATUS_EOSP bit and call this function instead.
 * This applies क्रम PS-Poll as well as uAPSD.
 *
 * Note that just like with _tx_status() and _rx() drivers must
 * not mix calls to irqsafe/non-irqsafe versions, this function
 * must not be mixed with those either. Use the all irqsafe, or
 * all non-irqsafe, करोn't mix!
 *
 * NB: the _irqsafe version of this function करोesn't exist, no
 *     driver needs it right now. Don't call this function अगर
 *     you'd need the _irqsafe version, look at the git history
 *     and restore the _irqsafe version!
 */
व्योम ieee80211_sta_eosp(काष्ठा ieee80211_sta *pubsta);

/**
 * ieee80211_send_eosp_nullfunc - ask mac80211 to send NDP with EOSP
 * @pubsta: the station
 * @tid: the tid of the NDP
 *
 * Someबार the device understands that it needs to बंद
 * the Service Period unexpectedly. This can happen when
 * sending frames that are filling holes in the BA winकरोw.
 * In this हाल, the device can ask mac80211 to send a
 * Nullfunc frame with EOSP set. When that happens, the
 * driver must have called ieee80211_sta_set_buffered() to
 * let mac80211 know that there are no buffered frames any
 * more, otherwise mac80211 will get the more_data bit wrong.
 * The low level driver must have made sure that the frame
 * will be sent despite the station being in घातer-save.
 * Mac80211 won't call allow_buffered_frames().
 * Note that calling this function, करोesn't exempt the driver
 * from closing the EOSP properly, it will still have to call
 * ieee80211_sta_eosp when the NDP is sent.
 */
व्योम ieee80211_send_eosp_nullfunc(काष्ठा ieee80211_sta *pubsta, पूर्णांक tid);

/**
 * ieee80211_sta_रेजिस्टर_airसमय - रेजिस्टर airसमय usage क्रम a sta/tid
 *
 * Register airसमय usage क्रम a given sta on a given tid. The driver must call
 * this function to notअगरy mac80211 that a station used a certain amount of
 * airसमय. This inक्रमmation will be used by the TXQ scheduler to schedule
 * stations in a way that ensures airसमय fairness.
 *
 * The reported airसमय should as a minimum include all समय that is spent
 * transmitting to the remote station, including overhead and padding, but not
 * including समय spent रुकोing क्रम a TXOP. If the समय is not reported by the
 * hardware it can in some हालs be calculated from the rate and known frame
 * composition. When possible, the समय should include any failed transmission
 * attempts.
 *
 * The driver can either call this function synchronously क्रम every packet or
 * aggregate, or asynchronously as airसमय usage inक्रमmation becomes available.
 * TX and RX airसमय can be reported together, or separately by setting one of
 * them to 0.
 *
 * @pubsta: the station
 * @tid: the TID to रेजिस्टर airसमय क्रम
 * @tx_airसमय: airसमय used during TX (in usec)
 * @rx_airसमय: airसमय used during RX (in usec)
 */
व्योम ieee80211_sta_रेजिस्टर_airसमय(काष्ठा ieee80211_sta *pubsta, u8 tid,
				    u32 tx_airसमय, u32 rx_airसमय);

/**
 * ieee80211_txq_airसमय_check - check अगर a txq can send frame to device
 *
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw()
 * @txq: poपूर्णांकer obtained from station or भव पूर्णांकerface
 *
 * Return true अगर the AQL's airसमय limit has not been reached and the txq can
 * जारी to send more packets to the device. Otherwise वापस false.
 */
bool
ieee80211_txq_airसमय_check(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *txq);

/**
 * ieee80211_iter_keys - iterate keys programmed पूर्णांकo the device
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw()
 * @vअगर: भव पूर्णांकerface to iterate, may be %शून्य क्रम all
 * @iter: iterator function that will be called क्रम each key
 * @iter_data: custom data to pass to the iterator function
 *
 * This function can be used to iterate all the keys known to
 * mac80211, even those that weren't previously programmed पूर्णांकo
 * the device. This is पूर्णांकended क्रम use in WoWLAN अगर the device
 * needs reprogramming of the keys during suspend. Note that due
 * to locking reasons, it is also only safe to call this at few
 * spots since it must hold the RTNL and be able to sleep.
 *
 * The order in which the keys are iterated matches the order
 * in which they were originally installed and handed to the
 * set_key callback.
 */
व्योम ieee80211_iter_keys(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 व्योम (*iter)(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा ieee80211_key_conf *key,
				      व्योम *data),
			 व्योम *iter_data);

/**
 * ieee80211_iter_keys_rcu - iterate keys programmed पूर्णांकo the device
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw()
 * @vअगर: भव पूर्णांकerface to iterate, may be %शून्य क्रम all
 * @iter: iterator function that will be called क्रम each key
 * @iter_data: custom data to pass to the iterator function
 *
 * This function can be used to iterate all the keys known to
 * mac80211, even those that weren't previously programmed पूर्णांकo
 * the device. Note that due to locking reasons, keys of station
 * in removal process will be skipped.
 *
 * This function requires being called in an RCU critical section,
 * and thus iter must be atomic.
 */
व्योम ieee80211_iter_keys_rcu(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     व्योम (*iter)(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा ieee80211_sta *sta,
					  काष्ठा ieee80211_key_conf *key,
					  व्योम *data),
			     व्योम *iter_data);

/**
 * ieee80211_iter_chan_contexts_atomic - iterate channel contexts
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @iter: iterator function
 * @iter_data: data passed to iterator function
 *
 * Iterate all active channel contexts. This function is atomic and
 * करोesn't acquire any locks पूर्णांकernally that might be held in other
 * places जबतक calling पूर्णांकo the driver.
 *
 * The iterator will not find a context that's being added (during
 * the driver callback to add it) but will find it जबतक it's being
 * हटाओd.
 *
 * Note that during hardware restart, all contexts that existed
 * beक्रमe the restart are considered alपढ़ोy present so will be
 * found जबतक iterating, whether they've been re-added alपढ़ोy
 * or not.
 */
व्योम ieee80211_iter_chan_contexts_atomic(
	काष्ठा ieee80211_hw *hw,
	व्योम (*iter)(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_chanctx_conf *chanctx_conf,
		     व्योम *data),
	व्योम *iter_data);

/**
 * ieee80211_ap_probereq_get - retrieve a Probe Request ढाँचा
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * Creates a Probe Request ढाँचा which can, क्रम example, be uploaded to
 * hardware. The ढाँचा is filled with bssid, ssid and supported rate
 * inक्रमmation. This function must only be called from within the
 * .bss_info_changed callback function and only in managed mode. The function
 * is only useful when the पूर्णांकerface is associated, otherwise it will वापस
 * %शून्य.
 *
 * Return: The Probe Request ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *ieee80211_ap_probereq_get(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_beacon_loss - inक्रमm hardware करोes not receive beacons
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * When beacon filtering is enabled with %IEEE80211_VIF_BEACON_FILTER and
 * %IEEE80211_CONF_PS is set, the driver needs to inक्रमm whenever the
 * hardware is not receiving beacons with this function.
 */
व्योम ieee80211_beacon_loss(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_connection_loss - inक्रमm hardware has lost connection to the AP
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * When beacon filtering is enabled with %IEEE80211_VIF_BEACON_FILTER, and
 * %IEEE80211_CONF_PS and %IEEE80211_HW_CONNECTION_MONITOR are set, the driver
 * needs to inक्रमm अगर the connection to the AP has been lost.
 * The function may also be called अगर the connection needs to be terminated
 * क्रम some other reason, even अगर %IEEE80211_HW_CONNECTION_MONITOR isn't set.
 *
 * This function will cause immediate change to disassociated state,
 * without connection recovery attempts.
 */
व्योम ieee80211_connection_loss(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_disconnect - request disconnection
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @reconnect: immediate reconnect is desired
 *
 * Request disconnection from the current network and, अगर enabled, send a
 * hपूर्णांक to the higher layers that immediate reconnect is desired.
 */
व्योम ieee80211_disconnect(काष्ठा ieee80211_vअगर *vअगर, bool reconnect);

/**
 * ieee80211_resume_disconnect - disconnect from AP after resume
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * Inकाष्ठाs mac80211 to disconnect from the AP after resume.
 * Drivers can use this after WoWLAN अगर they know that the
 * connection cannot be kept up, क्रम example because keys were
 * used जबतक the device was asleep but the replay counters or
 * similar cannot be retrieved from the device during resume.
 *
 * Note that due to implementation issues, अगर the driver uses
 * the reconfiguration functionality during resume the पूर्णांकerface
 * will still be added as associated first during resume and then
 * disconnect normally later.
 *
 * This function can only be called from the resume callback and
 * the driver must not be holding any of its own locks जबतक it
 * calls this function, or at least not any locks it needs in the
 * key configuration paths (अगर it supports HW crypto).
 */
व्योम ieee80211_resume_disconnect(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_cqm_rssi_notअगरy - inक्रमm a configured connection quality monitoring
 *	rssi threshold triggered
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @rssi_event: the RSSI trigger event type
 * @rssi_level: new RSSI level value or 0 अगर not available
 * @gfp: context flags
 *
 * When the %IEEE80211_VIF_SUPPORTS_CQM_RSSI is set, and a connection quality
 * monitoring is configured with an rssi threshold, the driver will inक्रमm
 * whenever the rssi level reaches the threshold.
 */
व्योम ieee80211_cqm_rssi_notअगरy(काष्ठा ieee80211_vअगर *vअगर,
			       क्रमागत nl80211_cqm_rssi_threshold_event rssi_event,
			       s32 rssi_level,
			       gfp_t gfp);

/**
 * ieee80211_cqm_beacon_loss_notअगरy - inक्रमm CQM of beacon loss
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @gfp: context flags
 */
व्योम ieee80211_cqm_beacon_loss_notअगरy(काष्ठा ieee80211_vअगर *vअगर, gfp_t gfp);

/**
 * ieee80211_radar_detected - inक्रमm that a radar was detected
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 */
व्योम ieee80211_radar_detected(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_chचयन_करोne - Complete channel चयन process
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @success: make the channel चयन successful or not
 *
 * Complete the channel चयन post-process: set the new operational channel
 * and wake up the suspended queues.
 */
व्योम ieee80211_chचयन_करोne(काष्ठा ieee80211_vअगर *vअगर, bool success);

/**
 * ieee80211_request_smps - request SM PS transition
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @smps_mode: new SM PS mode
 *
 * This allows the driver to request an SM PS transition in managed
 * mode. This is useful when the driver has more inक्रमmation than
 * the stack about possible पूर्णांकerference, क्रम example by bluetooth.
 */
व्योम ieee80211_request_smps(काष्ठा ieee80211_vअगर *vअगर,
			    क्रमागत ieee80211_smps_mode smps_mode);

/**
 * ieee80211_पढ़ोy_on_channel - notअगरication of reमुख्य-on-channel start
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 */
व्योम ieee80211_पढ़ोy_on_channel(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_reमुख्य_on_channel_expired - reमुख्य_on_channel duration expired
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 */
व्योम ieee80211_reमुख्य_on_channel_expired(काष्ठा ieee80211_hw *hw);

/**
 * ieee80211_stop_rx_ba_session - callback to stop existing BA sessions
 *
 * in order not to harm the प्रणाली perक्रमmance and user experience, the device
 * may request not to allow any rx ba session and tear करोwn existing rx ba
 * sessions based on प्रणाली स्थिरraपूर्णांकs such as periodic BT activity that needs
 * to limit wlan activity (eg.sco or a2dp)."
 * in such हालs, the पूर्णांकention is to limit the duration of the rx ppdu and
 * thereक्रमe prevent the peer device to use a-mpdu aggregation.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @ba_rx_biपंचांगap: Bit map of खोलो rx ba per tid
 * @addr: & to bssid mac address
 */
व्योम ieee80211_stop_rx_ba_session(काष्ठा ieee80211_vअगर *vअगर, u16 ba_rx_biपंचांगap,
				  स्थिर u8 *addr);

/**
 * ieee80211_mark_rx_ba_filtered_frames - move RX BA winकरोw and mark filtered
 * @pubsta: station काष्ठा
 * @tid: the session's TID
 * @ssn: starting sequence number of the biपंचांगap, all frames beक्रमe this are
 *	assumed to be out of the winकरोw after the call
 * @filtered: biपंचांगap of filtered frames, BIT(0) is the @ssn entry etc.
 * @received_mpdus: number of received mpdus in firmware
 *
 * This function moves the BA winकरोw and releases all frames beक्रमe @ssn, and
 * marks frames marked in the biपंचांगap as having been filtered. Afterwards, it
 * checks अगर any frames in the winकरोw starting from @ssn can now be released
 * (in हाल they were only रुकोing क्रम frames that were filtered.)
 */
व्योम ieee80211_mark_rx_ba_filtered_frames(काष्ठा ieee80211_sta *pubsta, u8 tid,
					  u16 ssn, u64 filtered,
					  u16 received_mpdus);

/**
 * ieee80211_send_bar - send a BlockAckReq frame
 *
 * can be used to flush pending frames from the peer's aggregation reorder
 * buffer.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @ra: the peer's destination address
 * @tid: the TID of the aggregation session
 * @ssn: the new starting sequence number क्रम the receiver
 */
व्योम ieee80211_send_bar(काष्ठा ieee80211_vअगर *vअगर, u8 *ra, u16 tid, u16 ssn);

/**
 * ieee80211_manage_rx_ba_offl - helper to queue an RX BA work
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback
 * @addr: station mac address
 * @tid: the rx tid
 */
व्योम ieee80211_manage_rx_ba_offl(काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *addr,
				 अचिन्हित पूर्णांक tid);

/**
 * ieee80211_start_rx_ba_session_offl - start a Rx BA session
 *
 * Some device drivers may offload part of the Rx aggregation flow including
 * AddBa/DelBa negotiation but may otherwise be incapable of full Rx
 * reordering.
 *
 * Create काष्ठाures responsible क्रम reordering so device drivers may call here
 * when they complete AddBa negotiation.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback
 * @addr: station mac address
 * @tid: the rx tid
 */
अटल अंतरभूत व्योम ieee80211_start_rx_ba_session_offl(काष्ठा ieee80211_vअगर *vअगर,
						      स्थिर u8 *addr, u16 tid)
अणु
	अगर (WARN_ON(tid >= IEEE80211_NUM_TIDS))
		वापस;
	ieee80211_manage_rx_ba_offl(vअगर, addr, tid);
पूर्ण

/**
 * ieee80211_stop_rx_ba_session_offl - stop a Rx BA session
 *
 * Some device drivers may offload part of the Rx aggregation flow including
 * AddBa/DelBa negotiation but may otherwise be incapable of full Rx
 * reordering.
 *
 * Destroy काष्ठाures responsible क्रम reordering so device drivers may call here
 * when they complete DelBa negotiation.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback
 * @addr: station mac address
 * @tid: the rx tid
 */
अटल अंतरभूत व्योम ieee80211_stop_rx_ba_session_offl(काष्ठा ieee80211_vअगर *vअगर,
						     स्थिर u8 *addr, u16 tid)
अणु
	अगर (WARN_ON(tid >= IEEE80211_NUM_TIDS))
		वापस;
	ieee80211_manage_rx_ba_offl(vअगर, addr, tid + IEEE80211_NUM_TIDS);
पूर्ण

/**
 * ieee80211_rx_ba_समयr_expired - stop a Rx BA session due to समयout
 *
 * Some device drivers करो not offload AddBa/DelBa negotiation, but handle rx
 * buffer reording पूर्णांकernally, and thereक्रमe also handle the session समयr.
 *
 * Trigger the समयout flow, which sends a DelBa.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback
 * @addr: station mac address
 * @tid: the rx tid
 */
व्योम ieee80211_rx_ba_समयr_expired(काष्ठा ieee80211_vअगर *vअगर,
				   स्थिर u8 *addr, अचिन्हित पूर्णांक tid);

/* Rate control API */

/**
 * काष्ठा ieee80211_tx_rate_control - rate control inक्रमmation क्रम/from RC algo
 *
 * @hw: The hardware the algorithm is invoked क्रम.
 * @sband: The band this frame is being transmitted on.
 * @bss_conf: the current BSS configuration
 * @skb: the skb that will be transmitted, the control inक्रमmation in it needs
 *	to be filled in
 * @reported_rate: The rate control algorithm can fill this in to indicate
 *	which rate should be reported to userspace as the current rate and
 *	used क्रम rate calculations in the mesh network.
 * @rts: whether RTS will be used क्रम this frame because it is दीर्घer than the
 *	RTS threshold
 * @लघु_preamble: whether mac80211 will request लघु-preamble transmission
 *	अगर the selected rate supports it
 * @rate_idx_mask: user-requested (legacy) rate mask
 * @rate_idx_mcs_mask: user-requested MCS rate mask (शून्य अगर not in use)
 * @bss: whether this frame is sent out in AP or IBSS mode
 */
काष्ठा ieee80211_tx_rate_control अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_bss_conf *bss_conf;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_rate reported_rate;
	bool rts, लघु_preamble;
	u32 rate_idx_mask;
	u8 *rate_idx_mcs_mask;
	bool bss;
पूर्ण;

/**
 * क्रमागत rate_control_capabilities - rate control capabilities
 */
क्रमागत rate_control_capabilities अणु
	/**
	 * @RATE_CTRL_CAPA_VHT_EXT_NSS_BW:
	 * Support क्रम extended NSS BW support (करोt11VHTExtendedNSSCapable)
	 * Note that this is only looked at अगर the minimum number of chains
	 * that the AP uses is < the number of TX chains the hardware has,
	 * otherwise the NSS dअगरference करोesn't bother us.
	 */
	RATE_CTRL_CAPA_VHT_EXT_NSS_BW = BIT(0),
पूर्ण;

काष्ठा rate_control_ops अणु
	अचिन्हित दीर्घ capa;
	स्थिर अक्षर *name;
	व्योम *(*alloc)(काष्ठा ieee80211_hw *hw);
	व्योम (*add_debugfs)(काष्ठा ieee80211_hw *hw, व्योम *priv,
			    काष्ठा dentry *debugfsdir);
	व्योम (*मुक्त)(व्योम *priv);

	व्योम *(*alloc_sta)(व्योम *priv, काष्ठा ieee80211_sta *sta, gfp_t gfp);
	व्योम (*rate_init)(व्योम *priv, काष्ठा ieee80211_supported_band *sband,
			  काष्ठा cfg80211_chan_def *chandef,
			  काष्ठा ieee80211_sta *sta, व्योम *priv_sta);
	व्योम (*rate_update)(व्योम *priv, काष्ठा ieee80211_supported_band *sband,
			    काष्ठा cfg80211_chan_def *chandef,
			    काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
			    u32 changed);
	व्योम (*मुक्त_sta)(व्योम *priv, काष्ठा ieee80211_sta *sta,
			 व्योम *priv_sta);

	व्योम (*tx_status_ext)(व्योम *priv,
			      काष्ठा ieee80211_supported_band *sband,
			      व्योम *priv_sta, काष्ठा ieee80211_tx_status *st);
	व्योम (*tx_status)(व्योम *priv, काष्ठा ieee80211_supported_band *sband,
			  काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
			  काष्ठा sk_buff *skb);
	व्योम (*get_rate)(व्योम *priv, काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
			 काष्ठा ieee80211_tx_rate_control *txrc);

	व्योम (*add_sta_debugfs)(व्योम *priv, व्योम *priv_sta,
				काष्ठा dentry *dir);

	u32 (*get_expected_throughput)(व्योम *priv_sta);
पूर्ण;

अटल अंतरभूत पूर्णांक rate_supported(काष्ठा ieee80211_sta *sta,
				 क्रमागत nl80211_band band,
				 पूर्णांक index)
अणु
	वापस (sta == शून्य || sta->supp_rates[band] & BIT(index));
पूर्ण

अटल अंतरभूत s8
rate_lowest_index(काष्ठा ieee80211_supported_band *sband,
		  काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sband->n_bitrates; i++)
		अगर (rate_supported(sta, sband->band, i))
			वापस i;

	/* warn when we cannot find a rate. */
	WARN_ON_ONCE(1);

	/* and वापस 0 (the lowest index) */
	वापस 0;
पूर्ण

अटल अंतरभूत
bool rate_usable_index_exists(काष्ठा ieee80211_supported_band *sband,
			      काष्ठा ieee80211_sta *sta)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < sband->n_bitrates; i++)
		अगर (rate_supported(sta, sband->band, i))
			वापस true;
	वापस false;
पूर्ण

/**
 * rate_control_set_rates - pass the sta rate selection to mac80211/driver
 *
 * When not करोing a rate control probe to test rates, rate control should pass
 * its rate selection to mac80211. If the driver supports receiving a station
 * rate table, it will use it to ensure that frames are always sent based on
 * the most recent rate control module decision.
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @pubsta: &काष्ठा ieee80211_sta poपूर्णांकer to the target destination.
 * @rates: new tx rate set to be used क्रम this station.
 */
पूर्णांक rate_control_set_rates(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_sta *pubsta,
			   काष्ठा ieee80211_sta_rates *rates);

पूर्णांक ieee80211_rate_control_रेजिस्टर(स्थिर काष्ठा rate_control_ops *ops);
व्योम ieee80211_rate_control_unरेजिस्टर(स्थिर काष्ठा rate_control_ops *ops);

अटल अंतरभूत bool
conf_is_ht20(काष्ठा ieee80211_conf *conf)
अणु
	वापस conf->chandef.width == NL80211_CHAN_WIDTH_20;
पूर्ण

अटल अंतरभूत bool
conf_is_ht40_minus(काष्ठा ieee80211_conf *conf)
अणु
	वापस conf->chandef.width == NL80211_CHAN_WIDTH_40 &&
	       conf->chandef.center_freq1 < conf->chandef.chan->center_freq;
पूर्ण

अटल अंतरभूत bool
conf_is_ht40_plus(काष्ठा ieee80211_conf *conf)
अणु
	वापस conf->chandef.width == NL80211_CHAN_WIDTH_40 &&
	       conf->chandef.center_freq1 > conf->chandef.chan->center_freq;
पूर्ण

अटल अंतरभूत bool
conf_is_ht40(काष्ठा ieee80211_conf *conf)
अणु
	वापस conf->chandef.width == NL80211_CHAN_WIDTH_40;
पूर्ण

अटल अंतरभूत bool
conf_is_ht(काष्ठा ieee80211_conf *conf)
अणु
	वापस (conf->chandef.width != NL80211_CHAN_WIDTH_5) &&
		(conf->chandef.width != NL80211_CHAN_WIDTH_10) &&
		(conf->chandef.width != NL80211_CHAN_WIDTH_20_NOHT);
पूर्ण

अटल अंतरभूत क्रमागत nl80211_अगरtype
ieee80211_अगरtype_p2p(क्रमागत nl80211_अगरtype type, bool p2p)
अणु
	अगर (p2p) अणु
		चयन (type) अणु
		हाल NL80211_IFTYPE_STATION:
			वापस NL80211_IFTYPE_P2P_CLIENT;
		हाल NL80211_IFTYPE_AP:
			वापस NL80211_IFTYPE_P2P_GO;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस type;
पूर्ण

अटल अंतरभूत क्रमागत nl80211_अगरtype
ieee80211_vअगर_type_p2p(काष्ठा ieee80211_vअगर *vअगर)
अणु
	वापस ieee80211_अगरtype_p2p(vअगर->type, vअगर->p2p);
पूर्ण

/**
 * ieee80211_update_mu_groups - set the VHT MU-MIMO groud data
 *
 * @vअगर: the specअगरied भव पूर्णांकerface
 * @membership: 64 bits array - a bit is set अगर station is member of the group
 * @position: 2 bits per group id indicating the position in the group
 *
 * Note: This function assumes that the given vअगर is valid and the position and
 * membership data is of the correct size and are in the same byte order as the
 * matching GroupId management frame.
 * Calls to this function need to be serialized with RX path.
 */
व्योम ieee80211_update_mu_groups(काष्ठा ieee80211_vअगर *vअगर,
				स्थिर u8 *membership, स्थिर u8 *position);

व्योम ieee80211_enable_rssi_reports(काष्ठा ieee80211_vअगर *vअगर,
				   पूर्णांक rssi_min_thold,
				   पूर्णांक rssi_max_thold);

व्योम ieee80211_disable_rssi_reports(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_ave_rssi - report the average RSSI क्रम the specअगरied पूर्णांकerface
 *
 * @vअगर: the specअगरied भव पूर्णांकerface
 *
 * Note: This function assumes that the given vअगर is valid.
 *
 * Return: The average RSSI value क्रम the requested पूर्णांकerface, or 0 अगर not
 * applicable.
 */
पूर्णांक ieee80211_ave_rssi(काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_report_wowlan_wakeup - report WoWLAN wakeup
 * @vअगर: भव पूर्णांकerface
 * @wakeup: wakeup reason(s)
 * @gfp: allocation flags
 *
 * See cfg80211_report_wowlan_wakeup().
 */
व्योम ieee80211_report_wowlan_wakeup(काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा cfg80211_wowlan_wakeup *wakeup,
				    gfp_t gfp);

/**
 * ieee80211_tx_prepare_skb - prepare an 802.11 skb क्रम transmission
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @vअगर: भव पूर्णांकerface
 * @skb: frame to be sent from within the driver
 * @band: the band to transmit on
 * @sta: optional poपूर्णांकer to get the station to send the frame to
 *
 * Note: must be called under RCU lock
 */
bool ieee80211_tx_prepare_skb(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर, काष्ठा sk_buff *skb,
			      पूर्णांक band, काष्ठा ieee80211_sta **sta);

/**
 * ieee80211_parse_tx_radiotap - Sanity-check and parse the radiotap header
 *				 of injected frames.
 *
 * To accurately parse and take पूर्णांकo account rate and retransmission fields,
 * you must initialize the chandef field in the ieee80211_tx_info काष्ठाure
 * of the skb beक्रमe calling this function.
 *
 * @skb: packet injected by userspace
 * @dev: the &काष्ठा device of this 802.11 device
 */
bool ieee80211_parse_tx_radiotap(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev);

/**
 * काष्ठा ieee80211_noa_data - holds temporary data क्रम tracking P2P NoA state
 *
 * @next_tsf: TSF बारtamp of the next असलent state change
 * @has_next_tsf: next असलent state change event pending
 *
 * @असलent: descriptor biपंचांगask, set अगर GO is currently असलent
 *
 * निजी:
 *
 * @count: count fields from the NoA descriptors
 * @desc: adjusted data from the NoA
 */
काष्ठा ieee80211_noa_data अणु
	u32 next_tsf;
	bool has_next_tsf;

	u8 असलent;

	u8 count[IEEE80211_P2P_NOA_DESC_MAX];
	काष्ठा अणु
		u32 start;
		u32 duration;
		u32 पूर्णांकerval;
	पूर्ण desc[IEEE80211_P2P_NOA_DESC_MAX];
पूर्ण;

/**
 * ieee80211_parse_p2p_noa - initialize NoA tracking data from P2P IE
 *
 * @attr: P2P NoA IE
 * @data: NoA tracking data
 * @tsf: current TSF बारtamp
 *
 * Return: number of successfully parsed descriptors
 */
पूर्णांक ieee80211_parse_p2p_noa(स्थिर काष्ठा ieee80211_p2p_noa_attr *attr,
			    काष्ठा ieee80211_noa_data *data, u32 tsf);

/**
 * ieee80211_update_p2p_noa - get next pending P2P GO असलent state change
 *
 * @data: NoA tracking data
 * @tsf: current TSF बारtamp
 */
व्योम ieee80211_update_p2p_noa(काष्ठा ieee80211_noa_data *data, u32 tsf);

/**
 * ieee80211_tdls_oper_request - request userspace to perक्रमm a TDLS operation
 * @vअगर: भव पूर्णांकerface
 * @peer: the peer's destination address
 * @oper: the requested TDLS operation
 * @reason_code: reason code क्रम the operation, valid क्रम TDLS tearकरोwn
 * @gfp: allocation flags
 *
 * See cfg80211_tdls_oper_request().
 */
व्योम ieee80211_tdls_oper_request(काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *peer,
				 क्रमागत nl80211_tdls_operation oper,
				 u16 reason_code, gfp_t gfp);

/**
 * ieee80211_reserve_tid - request to reserve a specअगरic TID
 *
 * There is someबार a need (such as in TDLS) क्रम blocking the driver from
 * using a specअगरic TID so that the FW can use it क्रम certain operations such
 * as sending PTI requests. To make sure that the driver करोesn't use that TID,
 * this function must be called as it flushes out packets on this TID and marks
 * it as blocked, so that any transmit क्रम the station on this TID will be
 * redirected to the alternative TID in the same AC.
 *
 * Note that this function blocks and may call back पूर्णांकo the driver, so it
 * should be called without driver locks held. Also note this function should
 * only be called from the driver's @sta_state callback.
 *
 * @sta: the station to reserve the TID क्रम
 * @tid: the TID to reserve
 *
 * Returns: 0 on success, अन्यथा on failure
 */
पूर्णांक ieee80211_reserve_tid(काष्ठा ieee80211_sta *sta, u8 tid);

/**
 * ieee80211_unreserve_tid - request to unreserve a specअगरic TID
 *
 * Once there is no दीर्घer any need क्रम reserving a certain TID, this function
 * should be called, and no दीर्घer will packets have their TID modअगरied क्रम
 * preventing use of this TID in the driver.
 *
 * Note that this function blocks and acquires a lock, so it should be called
 * without driver locks held. Also note this function should only be called
 * from the driver's @sta_state callback.
 *
 * @sta: the station
 * @tid: the TID to unreserve
 */
व्योम ieee80211_unreserve_tid(काष्ठा ieee80211_sta *sta, u8 tid);

/**
 * ieee80211_tx_dequeue - dequeue a packet from a software tx queue
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @txq: poपूर्णांकer obtained from station or भव पूर्णांकerface, or from
 *	ieee80211_next_txq()
 *
 * Returns the skb अगर successful, %शून्य अगर no frame was available.
 *
 * Note that this must be called in an rcu_पढ़ो_lock() critical section,
 * which can only be released after the SKB was handled. Some poपूर्णांकers in
 * skb->cb, e.g. the key poपूर्णांकer, are रक्षित by RCU and thus the
 * critical section must persist not just क्रम the duration of this call
 * but क्रम the duration of the frame handling.
 * However, also note that जबतक in the wake_tx_queue() method,
 * rcu_पढ़ो_lock() is alपढ़ोy held.
 *
 * softirqs must also be disabled when this function is called.
 * In process context, use ieee80211_tx_dequeue_ni() instead.
 */
काष्ठा sk_buff *ieee80211_tx_dequeue(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_txq *txq);

/**
 * ieee80211_tx_dequeue_ni - dequeue a packet from a software tx queue
 * (in process context)
 *
 * Like ieee80211_tx_dequeue() but can be called in process context
 * (पूर्णांकernally disables bottom halves).
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @txq: poपूर्णांकer obtained from station or भव पूर्णांकerface, or from
 *	ieee80211_next_txq()
 */
अटल अंतरभूत काष्ठा sk_buff *ieee80211_tx_dequeue_ni(काष्ठा ieee80211_hw *hw,
						      काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा sk_buff *skb;

	local_bh_disable();
	skb = ieee80211_tx_dequeue(hw, txq);
	local_bh_enable();

	वापस skb;
पूर्ण

/**
 * ieee80211_next_txq - get next tx queue to pull packets from
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @ac: AC number to वापस packets from.
 *
 * Returns the next txq अगर successful, %शून्य अगर no queue is eligible. If a txq
 * is वापसed, it should be वापसed with ieee80211_वापस_txq() after the
 * driver has finished scheduling it.
 */
काष्ठा ieee80211_txq *ieee80211_next_txq(काष्ठा ieee80211_hw *hw, u8 ac);

/**
 * ieee80211_txq_schedule_start - start new scheduling round क्रम TXQs
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @ac: AC number to acquire locks क्रम
 *
 * Should be called beक्रमe ieee80211_next_txq() or ieee80211_वापस_txq().
 * The driver must not call multiple TXQ scheduling rounds concurrently.
 */
व्योम ieee80211_txq_schedule_start(काष्ठा ieee80211_hw *hw, u8 ac);

/* (deprecated) */
अटल अंतरभूत व्योम ieee80211_txq_schedule_end(काष्ठा ieee80211_hw *hw, u8 ac)
अणु
पूर्ण

व्योम __ieee80211_schedule_txq(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_txq *txq, bool क्रमce);

/**
 * ieee80211_schedule_txq - schedule a TXQ क्रम transmission
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @txq: poपूर्णांकer obtained from station or भव पूर्णांकerface
 *
 * Schedules a TXQ क्रम transmission अगर it is not alपढ़ोy scheduled,
 * even अगर mac80211 करोes not have any packets buffered.
 *
 * The driver may call this function अगर it has buffered packets क्रम
 * this TXQ पूर्णांकernally.
 */
अटल अंतरभूत व्योम
ieee80211_schedule_txq(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *txq)
अणु
	__ieee80211_schedule_txq(hw, txq, true);
पूर्ण

/**
 * ieee80211_वापस_txq - वापस a TXQ previously acquired by ieee80211_next_txq()
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @txq: poपूर्णांकer obtained from station or भव पूर्णांकerface
 * @क्रमce: schedule txq even अगर mac80211 करोes not have any buffered packets.
 *
 * The driver may set क्रमce=true अगर it has buffered packets क्रम this TXQ
 * पूर्णांकernally.
 */
अटल अंतरभूत व्योम
ieee80211_वापस_txq(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *txq,
		     bool क्रमce)
अणु
	__ieee80211_schedule_txq(hw, txq, क्रमce);
पूर्ण

/**
 * ieee80211_txq_may_transmit - check whether TXQ is allowed to transmit
 *
 * This function is used to check whether given txq is allowed to transmit by
 * the airसमय scheduler, and can be used by drivers to access the airसमय
 * fairness accounting without going using the scheduling order enक्रमed by
 * next_txq().
 *
 * Returns %true अगर the airसमय scheduler thinks the TXQ should be allowed to
 * transmit, and %false अगर it should be throttled. This function can also have
 * the side effect of rotating the TXQ in the scheduler rotation, which will
 * eventually bring the deficit to positive and allow the station to transmit
 * again.
 *
 * The API ieee80211_txq_may_transmit() also ensures that TXQ list will be
 * aligned against driver's own round-robin scheduler list. i.e it rotates
 * the TXQ list till it makes the requested node becomes the first entry
 * in TXQ list. Thus both the TXQ list and driver's list are in sync. If this
 * function वापसs %true, the driver is expected to schedule packets
 * क्रम transmission, and then वापस the TXQ through ieee80211_वापस_txq().
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @txq: poपूर्णांकer obtained from station or भव पूर्णांकerface
 */
bool ieee80211_txq_may_transmit(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_txq *txq);

/**
 * ieee80211_txq_get_depth - get pending frame/byte count of given txq
 *
 * The values are not guaranteed to be coherent with regard to each other, i.e.
 * txq state can change half-way of this function and the caller may end up
 * with "new" frame_cnt and "old" byte_cnt or vice-versa.
 *
 * @txq: poपूर्णांकer obtained from station or भव पूर्णांकerface
 * @frame_cnt: poपूर्णांकer to store frame count
 * @byte_cnt: poपूर्णांकer to store byte count
 */
व्योम ieee80211_txq_get_depth(काष्ठा ieee80211_txq *txq,
			     अचिन्हित दीर्घ *frame_cnt,
			     अचिन्हित दीर्घ *byte_cnt);

/**
 * ieee80211_nan_func_terminated - notअगरy about न_अंक function termination.
 *
 * This function is used to notअगरy mac80211 about न_अंक function termination.
 * Note that this function can't be called from hard irq.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @inst_id: the local instance id
 * @reason: termination reason (one of the NL80211_न_अंक_FUNC_TERM_REASON_*)
 * @gfp: allocation flags
 */
व्योम ieee80211_nan_func_terminated(काष्ठा ieee80211_vअगर *vअगर,
				   u8 inst_id,
				   क्रमागत nl80211_nan_func_term_reason reason,
				   gfp_t gfp);

/**
 * ieee80211_nan_func_match - notअगरy about न_अंक function match event.
 *
 * This function is used to notअगरy mac80211 about न_अंक function match. The
 * cookie inside the match काष्ठा will be asचिन्हित by mac80211.
 * Note that this function can't be called from hard irq.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @match: match event inक्रमmation
 * @gfp: allocation flags
 */
व्योम ieee80211_nan_func_match(काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा cfg80211_nan_match_params *match,
			      gfp_t gfp);

/**
 * ieee80211_calc_rx_airसमय - calculate estimated transmission airसमय क्रम RX.
 *
 * This function calculates the estimated airसमय usage of a frame based on the
 * rate inक्रमmation in the RX status काष्ठा and the frame length.
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @status: &काष्ठा ieee80211_rx_status containing the transmission rate
 *          inक्रमmation.
 * @len: frame length in bytes
 */
u32 ieee80211_calc_rx_airसमय(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_rx_status *status,
			      पूर्णांक len);

/**
 * ieee80211_calc_tx_airसमय - calculate estimated transmission airसमय क्रम TX.
 *
 * This function calculates the estimated airसमय usage of a frame based on the
 * rate inक्रमmation in the TX info काष्ठा and the frame length.
 *
 * @hw: poपूर्णांकer as obtained from ieee80211_alloc_hw()
 * @info: &काष्ठा ieee80211_tx_info of the frame.
 * @len: frame length in bytes
 */
u32 ieee80211_calc_tx_airसमय(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_tx_info *info,
			      पूर्णांक len);
/**
 * ieee80211_set_hw_80211_encap - enable hardware encapsulation offloading.
 *
 * This function is used to notअगरy mac80211 that a vअगर can be passed raw 802.3
 * frames. The driver needs to then handle the 802.11 encapsulation inside the
 * hardware or firmware.
 *
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 * @enable: indicate अगर the feature should be turned on or off
 */
bool ieee80211_set_hw_80211_encap(काष्ठा ieee80211_vअगर *vअगर, bool enable);

/**
 * ieee80211_get_fils_discovery_पंचांगpl - Get FILS discovery ढाँचा.
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * The driver is responsible क्रम मुक्तing the वापसed skb.
 *
 * Return: FILS discovery ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *ieee80211_get_fils_discovery_पंचांगpl(काष्ठा ieee80211_hw *hw,
						  काष्ठा ieee80211_vअगर *vअगर);

/**
 * ieee80211_get_unsol_bcast_probe_resp_पंचांगpl - Get unsolicited broadcast
 *	probe response ढाँचा.
 * @hw: poपूर्णांकer obtained from ieee80211_alloc_hw().
 * @vअगर: &काष्ठा ieee80211_vअगर poपूर्णांकer from the add_पूर्णांकerface callback.
 *
 * The driver is responsible क्रम मुक्तing the वापसed skb.
 *
 * Return: Unsolicited broadcast probe response ढाँचा. %शून्य on error.
 */
काष्ठा sk_buff *
ieee80211_get_unsol_bcast_probe_resp_पंचांगpl(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर);
#पूर्ण_अगर /* MAC80211_H */
