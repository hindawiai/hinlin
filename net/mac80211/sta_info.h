<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2002-2005, Devicescape Software, Inc.
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright(c) 2015-2017 Intel Deutschland GmbH
 * Copyright(c) 2020-2021 Intel Corporation
 */

#अगर_अघोषित STA_INFO_H
#घोषणा STA_INFO_H

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/average.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/u64_stats_sync.h>
#समावेश "key.h"

/**
 * क्रमागत ieee80211_sta_info_flags - Stations flags
 *
 * These flags are used with &काष्ठा sta_info's @flags member, but
 * only indirectly with set_sta_flag() and मित्रs.
 *
 * @WLAN_STA_AUTH: Station is authenticated.
 * @WLAN_STA_ASSOC: Station is associated.
 * @WLAN_STA_PS_STA: Station is in घातer-save mode
 * @WLAN_STA_AUTHORIZED: Station is authorized to send/receive traffic.
 *	This bit is always checked so needs to be enabled क्रम all stations
 *	when भव port control is not in use.
 * @WLAN_STA_SHORT_PREAMBLE: Station is capable of receiving लघु-preamble
 *	frames.
 * @WLAN_STA_WDS: Station is one of our WDS peers.
 * @WLAN_STA_CLEAR_PS_FILT: Clear PS filter in hardware (using the
 *	IEEE80211_TX_CTL_CLEAR_PS_FILT control flag) when the next
 *	frame to this station is transmitted.
 * @WLAN_STA_MFP: Management frame protection is used with this STA.
 * @WLAN_STA_BLOCK_BA: Used to deny ADDBA requests (both TX and RX)
 *	during suspend/resume and station removal.
 * @WLAN_STA_PS_DRIVER: driver requires keeping this station in
 *	घातer-save mode logically to flush frames that might still
 *	be in the queues
 * @WLAN_STA_PSPOLL: Station sent PS-poll जबतक driver was keeping
 *	station in घातer-save mode, reply when the driver unblocks.
 * @WLAN_STA_TDLS_PEER: Station is a TDLS peer.
 * @WLAN_STA_TDLS_PEER_AUTH: This TDLS peer is authorized to send direct
 *	packets. This means the link is enabled.
 * @WLAN_STA_TDLS_INITIATOR: We are the initiator of the TDLS link with this
 *	station.
 * @WLAN_STA_TDLS_CHAN_SWITCH: This TDLS peer supports TDLS channel-चयनing
 * @WLAN_STA_TDLS_OFF_CHANNEL: The local STA is currently off-channel with this
 *	TDLS peer
 * @WLAN_STA_TDLS_WIDER_BW: This TDLS peer supports working on a wider bw on
 *	the BSS base channel.
 * @WLAN_STA_UAPSD: Station requested unscheduled SP जबतक driver was
 *	keeping station in घातer-save mode, reply when the driver
 *	unblocks the station.
 * @WLAN_STA_SP: Station is in a service period, so करोn't try to
 *	reply to other uAPSD trigger frames or PS-Poll.
 * @WLAN_STA_4ADDR_EVENT: 4-addr event was alपढ़ोy sent क्रम this frame.
 * @WLAN_STA_INSERTED: This station is inserted पूर्णांकo the hash table.
 * @WLAN_STA_RATE_CONTROL: rate control was initialized क्रम this station.
 * @WLAN_STA_TOFFSET_KNOWN: toffset calculated क्रम this station is valid.
 * @WLAN_STA_MPSP_OWNER: local STA is owner of a mesh Peer Service Period.
 * @WLAN_STA_MPSP_RECIPIENT: local STA is recipient of a MPSP.
 * @WLAN_STA_PS_DELIVER: station woke up, but we're still blocking TX
 *	until pending frames are delivered
 * @WLAN_STA_USES_ENCRYPTION: This station was configured क्रम encryption,
 *	so drop all packets without a key later.
 * @WLAN_STA_DECAP_OFFLOAD: This station uses rx decap offload
 *
 * @NUM_WLAN_STA_FLAGS: number of defined flags
 */
क्रमागत ieee80211_sta_info_flags अणु
	WLAN_STA_AUTH,
	WLAN_STA_ASSOC,
	WLAN_STA_PS_STA,
	WLAN_STA_AUTHORIZED,
	WLAN_STA_SHORT_PREAMBLE,
	WLAN_STA_WDS,
	WLAN_STA_CLEAR_PS_FILT,
	WLAN_STA_MFP,
	WLAN_STA_BLOCK_BA,
	WLAN_STA_PS_DRIVER,
	WLAN_STA_PSPOLL,
	WLAN_STA_TDLS_PEER,
	WLAN_STA_TDLS_PEER_AUTH,
	WLAN_STA_TDLS_INITIATOR,
	WLAN_STA_TDLS_CHAN_SWITCH,
	WLAN_STA_TDLS_OFF_CHANNEL,
	WLAN_STA_TDLS_WIDER_BW,
	WLAN_STA_UAPSD,
	WLAN_STA_SP,
	WLAN_STA_4ADDR_EVENT,
	WLAN_STA_INSERTED,
	WLAN_STA_RATE_CONTROL,
	WLAN_STA_TOFFSET_KNOWN,
	WLAN_STA_MPSP_OWNER,
	WLAN_STA_MPSP_RECIPIENT,
	WLAN_STA_PS_DELIVER,
	WLAN_STA_USES_ENCRYPTION,
	WLAN_STA_DECAP_OFFLOAD,

	NUM_WLAN_STA_FLAGS,
पूर्ण;

#घोषणा ADDBA_RESP_INTERVAL HZ
#घोषणा HT_AGG_MAX_RETRIES		15
#घोषणा HT_AGG_BURST_RETRIES		3
#घोषणा HT_AGG_RETRIES_PERIOD		(15 * HZ)

#घोषणा HT_AGG_STATE_DRV_READY		0
#घोषणा HT_AGG_STATE_RESPONSE_RECEIVED	1
#घोषणा HT_AGG_STATE_OPERATIONAL	2
#घोषणा HT_AGG_STATE_STOPPING		3
#घोषणा HT_AGG_STATE_WANT_START		4
#घोषणा HT_AGG_STATE_WANT_STOP		5
#घोषणा HT_AGG_STATE_START_CB		6
#घोषणा HT_AGG_STATE_STOP_CB		7
#घोषणा HT_AGG_STATE_SENT_ADDBA		8

DECLARE_EWMA(avg_संकेत, 10, 8)
क्रमागत ieee80211_agg_stop_reason अणु
	AGG_STOP_DECLINED,
	AGG_STOP_LOCAL_REQUEST,
	AGG_STOP_PEER_REQUEST,
	AGG_STOP_DESTROY_STA,
पूर्ण;

/* Debugfs flags to enable/disable use of RX/TX airसमय in scheduler */
#घोषणा AIRTIME_USE_TX		BIT(0)
#घोषणा AIRTIME_USE_RX		BIT(1)

काष्ठा airसमय_info अणु
	u64 rx_airसमय;
	u64 tx_airसमय;
	s64 deficit;
	atomic_t aql_tx_pending; /* Estimated airसमय क्रम frames pending */
	u32 aql_limit_low;
	u32 aql_limit_high;
पूर्ण;

व्योम ieee80211_sta_update_pending_airसमय(काष्ठा ieee80211_local *local,
					  काष्ठा sta_info *sta, u8 ac,
					  u16 tx_airसमय, bool tx_completed);

काष्ठा sta_info;

/**
 * काष्ठा tid_ampdu_tx - TID aggregation inक्रमmation (Tx).
 *
 * @rcu_head: rcu head क्रम मुक्तing काष्ठाure
 * @session_समयr: check अगर we keep Tx-ing on the TID (by समयout value)
 * @addba_resp_समयr: समयr क्रम peer's response to addba request
 * @pending: pending frames queue -- use sta's spinlock to protect
 * @sta: station we are attached to
 * @dialog_token: dialog token क्रम aggregation session
 * @समयout: session समयout value to be filled in ADDBA requests
 * @tid: TID number
 * @state: session state (see above)
 * @last_tx: jअगरfies of last tx activity
 * @stop_initiator: initiator of a session stop
 * @tx_stop: TX DelBA frame when stopping
 * @buf_size: reorder buffer size at receiver
 * @failed_bar_ssn: ssn of the last failed BAR tx attempt
 * @bar_pending: BAR needs to be re-sent
 * @amsdu: support A-MSDU withing A-MDPU
 *
 * This काष्ठाure's lअगरeसमय is managed by RCU, assignments to
 * the array holding it must hold the aggregation mutex.
 *
 * The TX path can access it under RCU lock-मुक्त अगर, and
 * only अगर, the state has the flag %HT_AGG_STATE_OPERATIONAL
 * set. Otherwise, the TX path must also acquire the spinlock
 * and re-check the state, see comments in the tx code
 * touching it.
 */
काष्ठा tid_ampdu_tx अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा समयr_list session_समयr;
	काष्ठा समयr_list addba_resp_समयr;
	काष्ठा sk_buff_head pending;
	काष्ठा sta_info *sta;
	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ last_tx;
	u16 समयout;
	u8 dialog_token;
	u8 stop_initiator;
	bool tx_stop;
	u16 buf_size;

	u16 failed_bar_ssn;
	bool bar_pending;
	bool amsdu;
	u8 tid;
पूर्ण;

/**
 * काष्ठा tid_ampdu_rx - TID aggregation inक्रमmation (Rx).
 *
 * @reorder_buf: buffer to reorder incoming aggregated MPDUs. An MPDU may be an
 *	A-MSDU with inभागidually reported subframes.
 * @reorder_buf_filtered: biपंचांगap indicating where there are filtered frames in
 *	the reorder buffer that should be ignored when releasing frames
 * @reorder_समय: jअगरfies when skb was added
 * @session_समयr: check अगर peer keeps Tx-ing on the TID (by समयout value)
 * @reorder_समयr: releases expired frames from the reorder buffer.
 * @sta: station we are attached to
 * @last_rx: jअगरfies of last rx activity
 * @head_seq_num: head sequence number in reordering buffer.
 * @stored_mpdu_num: number of MPDUs in reordering buffer
 * @ssn: Starting Sequence Number expected to be aggregated.
 * @buf_size: buffer size क्रम incoming A-MPDUs
 * @समयout: reset समयr value (in TUs).
 * @tid: TID number
 * @rcu_head: RCU head used क्रम मुक्तing this काष्ठा
 * @reorder_lock: serializes access to reorder buffer, see below.
 * @स्वतः_seq: used क्रम offloaded BA sessions to स्वतःmatically pick head_seq_and
 *	and ssn.
 * @हटाओd: this session is हटाओd (but might have been found due to RCU)
 * @started: this session has started (head ssn or higher was received)
 *
 * This काष्ठाure's lअगरeसमय is managed by RCU, assignments to
 * the array holding it must hold the aggregation mutex.
 *
 * The @reorder_lock is used to protect the members of this
 * काष्ठा, except क्रम @समयout, @buf_size and @dialog_token,
 * which are स्थिरant across the lअगरeसमय of the काष्ठा (the
 * dialog token being used only क्रम debugging).
 */
काष्ठा tid_ampdu_rx अणु
	काष्ठा rcu_head rcu_head;
	spinlock_t reorder_lock;
	u64 reorder_buf_filtered;
	काष्ठा sk_buff_head *reorder_buf;
	अचिन्हित दीर्घ *reorder_समय;
	काष्ठा sta_info *sta;
	काष्ठा समयr_list session_समयr;
	काष्ठा समयr_list reorder_समयr;
	अचिन्हित दीर्घ last_rx;
	u16 head_seq_num;
	u16 stored_mpdu_num;
	u16 ssn;
	u16 buf_size;
	u16 समयout;
	u8 tid;
	u8 स्वतः_seq:1,
	   हटाओd:1,
	   started:1;
पूर्ण;

/**
 * काष्ठा sta_ampdu_mlme - STA aggregation inक्रमmation.
 *
 * @mtx: mutex to protect all TX data (except non-शून्य assignments
 *	to tid_tx[idx], which are रक्षित by the sta spinlock)
 *	tid_start_tx is also रक्षित by sta->lock.
 * @tid_rx: aggregation info क्रम Rx per TID -- RCU रक्षित
 * @tid_rx_token: dialog tokens क्रम valid aggregation sessions
 * @tid_rx_समयr_expired: biपंचांगap indicating on which TIDs the
 *	RX समयr expired until the work क्रम it runs
 * @tid_rx_stop_requested:  biपंचांगap indicating which BA sessions per TID the
 *	driver requested to बंद until the work क्रम it runs
 * @tid_rx_manage_offl: biपंचांगap indicating which BA sessions were requested
 *	to be treated as started/stopped due to offloading
 * @agg_session_valid: biपंचांगap indicating which TID has a rx BA session खोलो on
 * @unexpected_agg: biपंचांगap indicating which TID alपढ़ोy sent a delBA due to
 *	unexpected aggregation related frames outside a session
 * @work: work काष्ठा क्रम starting/stopping aggregation
 * @tid_tx: aggregation info क्रम Tx per TID
 * @tid_start_tx: sessions where start was requested
 * @last_addba_req_समय: बारtamp of the last addBA request.
 * @addba_req_num: number of बार addBA request has been sent.
 * @dialog_token_allocator: dialog token क्रमागतerator क्रम each new session;
 */
काष्ठा sta_ampdu_mlme अणु
	काष्ठा mutex mtx;
	/* rx */
	काष्ठा tid_ampdu_rx __rcu *tid_rx[IEEE80211_NUM_TIDS];
	u8 tid_rx_token[IEEE80211_NUM_TIDS];
	अचिन्हित दीर्घ tid_rx_समयr_expired[BITS_TO_LONGS(IEEE80211_NUM_TIDS)];
	अचिन्हित दीर्घ tid_rx_stop_requested[BITS_TO_LONGS(IEEE80211_NUM_TIDS)];
	अचिन्हित दीर्घ tid_rx_manage_offl[BITS_TO_LONGS(2 * IEEE80211_NUM_TIDS)];
	अचिन्हित दीर्घ agg_session_valid[BITS_TO_LONGS(IEEE80211_NUM_TIDS)];
	अचिन्हित दीर्घ unexpected_agg[BITS_TO_LONGS(IEEE80211_NUM_TIDS)];
	/* tx */
	काष्ठा work_काष्ठा work;
	काष्ठा tid_ampdu_tx __rcu *tid_tx[IEEE80211_NUM_TIDS];
	काष्ठा tid_ampdu_tx *tid_start_tx[IEEE80211_NUM_TIDS];
	अचिन्हित दीर्घ last_addba_req_समय[IEEE80211_NUM_TIDS];
	u8 addba_req_num[IEEE80211_NUM_TIDS];
	u8 dialog_token_allocator;
पूर्ण;


/* Value to indicate no TID reservation */
#घोषणा IEEE80211_TID_UNRESERVED	0xff

#घोषणा IEEE80211_FAST_XMIT_MAX_IV	18

/**
 * काष्ठा ieee80211_fast_tx - TX fastpath inक्रमmation
 * @key: key to use क्रम hw crypto
 * @hdr: the 802.11 header to put with the frame
 * @hdr_len: actual 802.11 header length
 * @sa_offs: offset of the SA
 * @da_offs: offset of the DA
 * @pn_offs: offset where to put PN क्रम crypto (or 0 अगर not needed)
 * @band: band this will be transmitted on, क्रम tx_info
 * @rcu_head: RCU head to मुक्त this काष्ठा
 *
 * This काष्ठा is small enough so that the common हाल (maximum crypto
 * header length of 8 like क्रम CCMP/GCMP) fits पूर्णांकo a single 64-byte
 * cache line.
 */
काष्ठा ieee80211_fast_tx अणु
	काष्ठा ieee80211_key *key;
	u8 hdr_len;
	u8 sa_offs, da_offs, pn_offs;
	u8 band;
	u8 hdr[30 + 2 + IEEE80211_FAST_XMIT_MAX_IV +
	       माप(rfc1042_header)] __aligned(2);

	काष्ठा rcu_head rcu_head;
पूर्ण;

/**
 * काष्ठा ieee80211_fast_rx - RX fastpath inक्रमmation
 * @dev: netdevice क्रम reporting the SKB
 * @vअगर_type: (P2P-less) पूर्णांकerface type of the original sdata (sdata->vअगर.type)
 * @vअगर_addr: पूर्णांकerface address
 * @rfc1042_hdr: copy of the RFC 1042 SNAP header (to have in cache)
 * @control_port_protocol: control port protocol copied from sdata
 * @expected_ds_bits: from/to DS bits expected
 * @icv_len: length of the MIC अगर present
 * @key: bool indicating encryption is expected (key is set)
 * @पूर्णांकernal_क्रमward: क्रमward froms पूर्णांकernally on AP/VLAN type पूर्णांकerfaces
 * @uses_rss: copy of USES_RSS hw flag
 * @da_offs: offset of the DA in the header (क्रम header conversion)
 * @sa_offs: offset of the SA in the header (क्रम header conversion)
 * @rcu_head: RCU head क्रम मुक्तing this काष्ठाure
 */
काष्ठा ieee80211_fast_rx अणु
	काष्ठा net_device *dev;
	क्रमागत nl80211_अगरtype vअगर_type;
	u8 vअगर_addr[ETH_ALEN] __aligned(2);
	u8 rfc1042_hdr[6] __aligned(2);
	__be16 control_port_protocol;
	__le16 expected_ds_bits;
	u8 icv_len;
	u8 key:1,
	   पूर्णांकernal_क्रमward:1,
	   uses_rss:1;
	u8 da_offs, sa_offs;

	काष्ठा rcu_head rcu_head;
पूर्ण;

/* we use only values in the range 0-100, so pick a large precision */
DECLARE_EWMA(mesh_fail_avg, 20, 8)
DECLARE_EWMA(mesh_tx_rate_avg, 8, 16)

/**
 * काष्ठा mesh_sta - mesh STA inक्रमmation
 * @plink_lock: serialize access to plink fields
 * @llid: Local link ID
 * @plid: Peer link ID
 * @aid: local aid supplied by peer
 * @reason: Cancel reason on PLINK_HOLDING state
 * @plink_retries: Retries in establishment
 * @plink_state: peer link state
 * @plink_समयout: समयout of peer link
 * @plink_समयr: peer link watch समयr
 * @plink_sta: peer link watch समयr's sta_info
 * @t_offset: timing offset relative to this host
 * @t_offset_setpoपूर्णांक: reference timing offset of this sta to be used when
 * 	calculating घड़ीdrअगरt
 * @local_pm: local link-specअगरic घातer save mode
 * @peer_pm: peer-specअगरic घातer save mode towards local STA
 * @nonpeer_pm: STA घातer save mode towards non-peer neighbors
 * @processed_beacon: set to true after peer rates and capabilities are
 *	processed
 * @connected_to_gate: true अगर mesh STA has a path to a mesh gate
 * @connected_to_as: true अगर mesh STA has a path to a authentication server
 * @fail_avg: moving percentage of failed MSDUs
 * @tx_rate_avg: moving average of tx bitrate
 */
काष्ठा mesh_sta अणु
	काष्ठा समयr_list plink_समयr;
	काष्ठा sta_info *plink_sta;

	s64 t_offset;
	s64 t_offset_setpoपूर्णांक;

	spinlock_t plink_lock;
	u16 llid;
	u16 plid;
	u16 aid;
	u16 reason;
	u8 plink_retries;

	bool processed_beacon;
	bool connected_to_gate;
	bool connected_to_as;

	क्रमागत nl80211_plink_state plink_state;
	u32 plink_समयout;

	/* mesh घातer save */
	क्रमागत nl80211_mesh_घातer_mode local_pm;
	क्रमागत nl80211_mesh_घातer_mode peer_pm;
	क्रमागत nl80211_mesh_घातer_mode nonpeer_pm;

	/* moving percentage of failed MSDUs */
	काष्ठा ewma_mesh_fail_avg fail_avg;
	/* moving average of tx bitrate */
	काष्ठा ewma_mesh_tx_rate_avg tx_rate_avg;
पूर्ण;

DECLARE_EWMA(संकेत, 10, 8)

काष्ठा ieee80211_sta_rx_stats अणु
	अचिन्हित दीर्घ packets;
	अचिन्हित दीर्घ last_rx;
	अचिन्हित दीर्घ num_duplicates;
	अचिन्हित दीर्घ fragments;
	अचिन्हित दीर्घ dropped;
	पूर्णांक last_संकेत;
	u8 chains;
	s8 chain_संकेत_last[IEEE80211_MAX_CHAINS];
	u32 last_rate;
	काष्ठा u64_stats_sync syncp;
	u64 bytes;
	u64 msdu[IEEE80211_NUM_TIDS + 1];
पूर्ण;

/*
 * IEEE 802.11-2016 (10.6 "Defragmentation") recommends support क्रम "concurrent
 * reception of at least one MSDU per access category per associated STA"
 * on APs, or "at least one MSDU per access category" on other पूर्णांकerface types.
 *
 * This limit can be increased by changing this define, at the cost of slower
 * frame reassembly and increased memory use जबतक fragments are pending.
 */
#घोषणा IEEE80211_FRAGMENT_MAX 4

काष्ठा ieee80211_fragment_entry अणु
	काष्ठा sk_buff_head skb_list;
	अचिन्हित दीर्घ first_frag_समय;
	u16 seq;
	u16 extra_len;
	u16 last_frag;
	u8 rx_queue;
	u8 check_sequential_pn:1, /* needed क्रम CCMP/GCMP */
	   is_रक्षित:1;
	u8 last_pn[6]; /* PN of the last fragment अगर CCMP was used */
	अचिन्हित पूर्णांक key_color;
पूर्ण;

काष्ठा ieee80211_fragment_cache अणु
	काष्ठा ieee80211_fragment_entry	entries[IEEE80211_FRAGMENT_MAX];
	अचिन्हित पूर्णांक next;
पूर्ण;

/*
 * The bandwidth threshold below which the per-station CoDel parameters will be
 * scaled to be more lenient (to prevent starvation of slow stations). This
 * value will be scaled by the number of active stations when it is being
 * applied.
 */
#घोषणा STA_SLOW_THRESHOLD 6000 /* 6 Mbps */

/**
 * काष्ठा sta_info - STA inक्रमmation
 *
 * This काष्ठाure collects inक्रमmation about a station that
 * mac80211 is communicating with.
 *
 * @list: global linked list entry
 * @मुक्त_list: list entry क्रम keeping track of stations to मुक्त
 * @hash_node: hash node क्रम rhashtable
 * @addr: station's MAC address - duplicated from खुला part to
 *	let the hash table work with just a single cacheline
 * @local: poपूर्णांकer to the global inक्रमmation
 * @sdata: भव पूर्णांकerface this station beदीर्घs to
 * @ptk: peer keys negotiated with this station, अगर any
 * @ptk_idx: last installed peer key index
 * @gtk: group keys negotiated with this station, अगर any
 * @rate_ctrl: rate control algorithm reference
 * @rate_ctrl_lock: spinlock used to protect rate control data
 *	(data inside the algorithm, so serializes calls there)
 * @rate_ctrl_priv: rate control निजी per-STA poपूर्णांकer
 * @lock: used क्रम locking all fields that require locking, see comments
 *	in the header file.
 * @drv_deliver_wk: used क्रम delivering frames after driver PS unblocking
 * @listen_पूर्णांकerval: listen पूर्णांकerval of this station, when we're acting as AP
 * @_flags: STA flags, see &क्रमागत ieee80211_sta_info_flags, करो not use directly
 * @ps_lock: used क्रम घातersave (when mac80211 is the AP) related locking
 * @ps_tx_buf: buffers (per AC) of frames to transmit to this station
 *	when it leaves घातer saving state or polls
 * @tx_filtered: buffers (per AC) of frames we alपढ़ोy tried to
 *	transmit but were filtered by hardware due to STA having
 *	entered घातer saving state, these are also delivered to
 *	the station when it leaves घातersave or polls क्रम frames
 * @driver_buffered_tids: biपंचांगap of TIDs the driver has data buffered on
 * @txq_buffered_tids: biपंचांगap of TIDs that mac80211 has txq data buffered on
 * @assoc_at: घड़ी bootसमय (in ns) of last association
 * @last_connected: समय (in seconds) when a station got connected
 * @last_seq_ctrl: last received seq/frag number from this STA (per TID
 *	plus one क्रम non-QoS frames)
 * @tid_seq: per-TID sequence numbers क्रम sending to this STA
 * @airसमय: per-AC काष्ठा airसमय_info describing airसमय statistics क्रम this
 *	station
 * @airसमय_weight: station weight क्रम airसमय fairness calculation purposes
 * @ampdu_mlme: A-MPDU state machine state
 * @mesh: mesh STA inक्रमmation
 * @debugfs_dir: debug fileप्रणाली directory dentry
 * @dead: set to true when sta is unlinked
 * @हटाओd: set to true when sta is being हटाओd from sta_list
 * @uploaded: set to true when sta is uploaded to the driver
 * @sta: station inक्रमmation we share with the driver
 * @sta_state: duplicates inक्रमmation about station state (क्रम debug)
 * @rcu_head: RCU head used क्रम मुक्तing this station काष्ठा
 * @cur_max_bandwidth: maximum bandwidth to use क्रम TX to the station,
 *	taken from HT/VHT capabilities or VHT operating mode notअगरication
 * @known_smps_mode: the smps_mode the client thinks we are in. Relevant क्रम
 *	AP only.
 * @cipher_scheme: optional cipher scheme क्रम this station
 * @cparams: CoDel parameters क्रम this station.
 * @reserved_tid: reserved TID (अगर any, otherwise IEEE80211_TID_UNRESERVED)
 * @fast_tx: TX fastpath inक्रमmation
 * @fast_rx: RX fastpath inक्रमmation
 * @tdls_chandef: a TDLS peer can have a wider chandef that is compatible to
 *	the BSS one.
 * @tx_stats: TX statistics
 * @tx_stats.packets: # of packets transmitted
 * @tx_stats.bytes: # of bytes in all packets transmitted
 * @tx_stats.last_rate: last TX rate
 * @tx_stats.msdu: # of transmitted MSDUs per TID
 * @rx_stats: RX statistics
 * @rx_stats_avg: averaged RX statistics
 * @rx_stats_avg.संकेत: averaged संकेत
 * @rx_stats_avg.chain_संकेत: averaged per-chain संकेत
 * @pcpu_rx_stats: per-CPU RX statistics, asचिन्हित only अगर the driver needs
 *	this (by advertising the USES_RSS hw flag)
 * @status_stats: TX status statistics
 * @status_stats.filtered: # of filtered frames
 * @status_stats.retry_failed: # of frames that failed after retry
 * @status_stats.retry_count: # of retries attempted
 * @status_stats.lost_packets: # of lost packets
 * @status_stats.last_pkt_समय: बारtamp of last ACKed packet
 * @status_stats.msdu_retries: # of MSDU retries
 * @status_stats.msdu_failed: # of failed MSDUs
 * @status_stats.last_ack: last ack बारtamp (jअगरfies)
 * @status_stats.last_ack_संकेत: last ACK संकेत
 * @status_stats.ack_संकेत_filled: last ACK संकेत validity
 * @status_stats.avg_ack_संकेत: average ACK संकेत
 * @frags: fragment cache
 */
काष्ठा sta_info अणु
	/* General inक्रमmation, mostly अटल */
	काष्ठा list_head list, मुक्त_list;
	काष्ठा rcu_head rcu_head;
	काष्ठा rhlist_head hash_node;
	u8 addr[ETH_ALEN];
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_key __rcu *gtk[NUM_DEFAULT_KEYS +
					NUM_DEFAULT_MGMT_KEYS +
					NUM_DEFAULT_BEACON_KEYS];
	काष्ठा ieee80211_key __rcu *ptk[NUM_DEFAULT_KEYS];
	u8 ptk_idx;
	काष्ठा rate_control_ref *rate_ctrl;
	व्योम *rate_ctrl_priv;
	spinlock_t rate_ctrl_lock;
	spinlock_t lock;

	काष्ठा ieee80211_fast_tx __rcu *fast_tx;
	काष्ठा ieee80211_fast_rx __rcu *fast_rx;
	काष्ठा ieee80211_sta_rx_stats __percpu *pcpu_rx_stats;

#अगर_घोषित CONFIG_MAC80211_MESH
	काष्ठा mesh_sta *mesh;
#पूर्ण_अगर

	काष्ठा work_काष्ठा drv_deliver_wk;

	u16 listen_पूर्णांकerval;

	bool dead;
	bool हटाओd;

	bool uploaded;

	क्रमागत ieee80211_sta_state sta_state;

	/* use the accessors defined below */
	अचिन्हित दीर्घ _flags;

	/* STA घातersave lock and frame queues */
	spinlock_t ps_lock;
	काष्ठा sk_buff_head ps_tx_buf[IEEE80211_NUM_ACS];
	काष्ठा sk_buff_head tx_filtered[IEEE80211_NUM_ACS];
	अचिन्हित दीर्घ driver_buffered_tids;
	अचिन्हित दीर्घ txq_buffered_tids;

	u64 assoc_at;
	दीर्घ last_connected;

	/* Updated from RX path only, no locking requirements */
	काष्ठा ieee80211_sta_rx_stats rx_stats;
	काष्ठा अणु
		काष्ठा ewma_संकेत संकेत;
		काष्ठा ewma_संकेत chain_संकेत[IEEE80211_MAX_CHAINS];
	पूर्ण rx_stats_avg;

	/* Plus 1 क्रम non-QoS frames */
	__le16 last_seq_ctrl[IEEE80211_NUM_TIDS + 1];

	/* Updated from TX status path only, no locking requirements */
	काष्ठा अणु
		अचिन्हित दीर्घ filtered;
		अचिन्हित दीर्घ retry_failed, retry_count;
		अचिन्हित पूर्णांक lost_packets;
		अचिन्हित दीर्घ last_pkt_समय;
		u64 msdu_retries[IEEE80211_NUM_TIDS + 1];
		u64 msdu_failed[IEEE80211_NUM_TIDS + 1];
		अचिन्हित दीर्घ last_ack;
		s8 last_ack_संकेत;
		bool ack_संकेत_filled;
		काष्ठा ewma_avg_संकेत avg_ack_संकेत;
	पूर्ण status_stats;

	/* Updated from TX path only, no locking requirements */
	काष्ठा अणु
		u64 packets[IEEE80211_NUM_ACS];
		u64 bytes[IEEE80211_NUM_ACS];
		काष्ठा ieee80211_tx_rate last_rate;
		काष्ठा rate_info last_rate_info;
		u64 msdu[IEEE80211_NUM_TIDS + 1];
	पूर्ण tx_stats;
	u16 tid_seq[IEEE80211_QOS_CTL_TID_MASK + 1];

	काष्ठा airसमय_info airसमय[IEEE80211_NUM_ACS];
	u16 airसमय_weight;

	/*
	 * Aggregation inक्रमmation, locked with lock.
	 */
	काष्ठा sta_ampdu_mlme ampdu_mlme;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	काष्ठा dentry *debugfs_dir;
#पूर्ण_अगर

	क्रमागत ieee80211_sta_rx_bandwidth cur_max_bandwidth;

	क्रमागत ieee80211_smps_mode known_smps_mode;
	स्थिर काष्ठा ieee80211_cipher_scheme *cipher_scheme;

	काष्ठा codel_params cparams;

	u8 reserved_tid;

	काष्ठा cfg80211_chan_def tdls_chandef;

	काष्ठा ieee80211_fragment_cache frags;

	/* keep last! */
	काष्ठा ieee80211_sta sta;
पूर्ण;

अटल अंतरभूत क्रमागत nl80211_plink_state sta_plink_state(काष्ठा sta_info *sta)
अणु
#अगर_घोषित CONFIG_MAC80211_MESH
	वापस sta->mesh->plink_state;
#पूर्ण_अगर
	वापस NL80211_PLINK_LISTEN;
पूर्ण

अटल अंतरभूत व्योम set_sta_flag(काष्ठा sta_info *sta,
				क्रमागत ieee80211_sta_info_flags flag)
अणु
	WARN_ON(flag == WLAN_STA_AUTH ||
		flag == WLAN_STA_ASSOC ||
		flag == WLAN_STA_AUTHORIZED);
	set_bit(flag, &sta->_flags);
पूर्ण

अटल अंतरभूत व्योम clear_sta_flag(काष्ठा sta_info *sta,
				  क्रमागत ieee80211_sta_info_flags flag)
अणु
	WARN_ON(flag == WLAN_STA_AUTH ||
		flag == WLAN_STA_ASSOC ||
		flag == WLAN_STA_AUTHORIZED);
	clear_bit(flag, &sta->_flags);
पूर्ण

अटल अंतरभूत पूर्णांक test_sta_flag(काष्ठा sta_info *sta,
				क्रमागत ieee80211_sta_info_flags flag)
अणु
	वापस test_bit(flag, &sta->_flags);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_clear_sta_flag(काष्ठा sta_info *sta,
					  क्रमागत ieee80211_sta_info_flags flag)
अणु
	WARN_ON(flag == WLAN_STA_AUTH ||
		flag == WLAN_STA_ASSOC ||
		flag == WLAN_STA_AUTHORIZED);
	वापस test_and_clear_bit(flag, &sta->_flags);
पूर्ण

अटल अंतरभूत पूर्णांक test_and_set_sta_flag(काष्ठा sta_info *sta,
					क्रमागत ieee80211_sta_info_flags flag)
अणु
	WARN_ON(flag == WLAN_STA_AUTH ||
		flag == WLAN_STA_ASSOC ||
		flag == WLAN_STA_AUTHORIZED);
	वापस test_and_set_bit(flag, &sta->_flags);
पूर्ण

पूर्णांक sta_info_move_state(काष्ठा sta_info *sta,
			क्रमागत ieee80211_sta_state new_state);

अटल अंतरभूत व्योम sta_info_pre_move_state(काष्ठा sta_info *sta,
					   क्रमागत ieee80211_sta_state new_state)
अणु
	पूर्णांक ret;

	WARN_ON_ONCE(test_sta_flag(sta, WLAN_STA_INSERTED));

	ret = sta_info_move_state(sta, new_state);
	WARN_ON_ONCE(ret);
पूर्ण


व्योम ieee80211_assign_tid_tx(काष्ठा sta_info *sta, पूर्णांक tid,
			     काष्ठा tid_ampdu_tx *tid_tx);

अटल अंतरभूत काष्ठा tid_ampdu_tx *
rcu_dereference_रक्षित_tid_tx(काष्ठा sta_info *sta, पूर्णांक tid)
अणु
	वापस rcu_dereference_रक्षित(sta->ampdu_mlme.tid_tx[tid],
					 lockdep_is_held(&sta->lock) ||
					 lockdep_is_held(&sta->ampdu_mlme.mtx));
पूर्ण

/* Maximum number of frames to buffer per घातer saving station per AC */
#घोषणा STA_MAX_TX_BUFFER	64

/* Minimum buffered frame expiry समय. If STA uses listen पूर्णांकerval that is
 * smaller than this value, the minimum value here is used instead. */
#घोषणा STA_TX_BUFFER_EXPIRE (10 * HZ)

/* How often station data is cleaned up (e.g., expiration of buffered frames)
 */
#घोषणा STA_INFO_CLEANUP_INTERVAL (10 * HZ)

काष्ठा rhlist_head *sta_info_hash_lookup(काष्ठा ieee80211_local *local,
					 स्थिर u8 *addr);

/*
 * Get a STA info, must be under RCU पढ़ो lock.
 */
काष्ठा sta_info *sta_info_get(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर u8 *addr);

काष्ठा sta_info *sta_info_get_bss(काष्ठा ieee80211_sub_अगर_data *sdata,
				  स्थिर u8 *addr);

/* user must hold sta_mtx or be in RCU critical section */
काष्ठा sta_info *sta_info_get_by_addrs(काष्ठा ieee80211_local *local,
				       स्थिर u8 *sta_addr, स्थिर u8 *vअगर_addr);

#घोषणा क्रम_each_sta_info(local, _addr, _sta, _पंचांगp)			\
	rhl_क्रम_each_entry_rcu(_sta, _पंचांगp,				\
			       sta_info_hash_lookup(local, _addr), hash_node)

/*
 * Get STA info by index, BROKEN!
 */
काष्ठा sta_info *sta_info_get_by_idx(काष्ठा ieee80211_sub_अगर_data *sdata,
				     पूर्णांक idx);
/*
 * Create a new STA info, caller owns वापसed काष्ठाure
 * until sta_info_insert().
 */
काष्ठा sta_info *sta_info_alloc(काष्ठा ieee80211_sub_अगर_data *sdata,
				स्थिर u8 *addr, gfp_t gfp);

व्योम sta_info_मुक्त(काष्ठा ieee80211_local *local, काष्ठा sta_info *sta);

/*
 * Insert STA info पूर्णांकo hash table/list, वापसs zero or a
 * -EEXIST अगर (अगर the same MAC address is alपढ़ोy present).
 *
 * Calling the non-rcu version makes the caller relinquish,
 * the _rcu version calls पढ़ो_lock_rcu() and must be called
 * without it held.
 */
पूर्णांक sta_info_insert(काष्ठा sta_info *sta);
पूर्णांक sta_info_insert_rcu(काष्ठा sta_info *sta) __acquires(RCU);

पूर्णांक __must_check __sta_info_destroy(काष्ठा sta_info *sta);
पूर्णांक sta_info_destroy_addr(काष्ठा ieee80211_sub_अगर_data *sdata,
			  स्थिर u8 *addr);
पूर्णांक sta_info_destroy_addr_bss(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर u8 *addr);

व्योम sta_info_recalc_tim(काष्ठा sta_info *sta);

पूर्णांक sta_info_init(काष्ठा ieee80211_local *local);
व्योम sta_info_stop(काष्ठा ieee80211_local *local);

/**
 * __sta_info_flush - flush matching STA entries from the STA table
 *
 * Returns the number of हटाओd STA entries.
 *
 * @sdata: sdata to हटाओ all stations from
 * @vlans: अगर the given पूर्णांकerface is an AP पूर्णांकerface, also flush VLANs
 */
पूर्णांक __sta_info_flush(काष्ठा ieee80211_sub_अगर_data *sdata, bool vlans);

/**
 * sta_info_flush - flush matching STA entries from the STA table
 *
 * Returns the number of हटाओd STA entries.
 *
 * @sdata: sdata to हटाओ all stations from
 */
अटल अंतरभूत पूर्णांक sta_info_flush(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	वापस __sta_info_flush(sdata, false);
पूर्ण

व्योम sta_set_rate_info_tx(काष्ठा sta_info *sta,
			  स्थिर काष्ठा ieee80211_tx_rate *rate,
			  काष्ठा rate_info *rinfo);
व्योम sta_set_sinfo(काष्ठा sta_info *sta, काष्ठा station_info *sinfo,
		   bool tidstats);

u32 sta_get_expected_throughput(काष्ठा sta_info *sta);

व्योम ieee80211_sta_expire(काष्ठा ieee80211_sub_अगर_data *sdata,
			  अचिन्हित दीर्घ exp_समय);
u8 sta_info_tx_streams(काष्ठा sta_info *sta);

व्योम ieee80211_sta_ps_deliver_wakeup(काष्ठा sta_info *sta);
व्योम ieee80211_sta_ps_deliver_poll_response(काष्ठा sta_info *sta);
व्योम ieee80211_sta_ps_deliver_uapsd(काष्ठा sta_info *sta);

अचिन्हित दीर्घ ieee80211_sta_last_active(काष्ठा sta_info *sta);

क्रमागत sta_stats_type अणु
	STA_STATS_RATE_TYPE_INVALID = 0,
	STA_STATS_RATE_TYPE_LEGACY,
	STA_STATS_RATE_TYPE_HT,
	STA_STATS_RATE_TYPE_VHT,
	STA_STATS_RATE_TYPE_HE,
	STA_STATS_RATE_TYPE_S1G,
पूर्ण;

#घोषणा STA_STATS_FIELD_HT_MCS		GENMASK( 7,  0)
#घोषणा STA_STATS_FIELD_LEGACY_IDX	GENMASK( 3,  0)
#घोषणा STA_STATS_FIELD_LEGACY_BAND	GENMASK( 7,  4)
#घोषणा STA_STATS_FIELD_VHT_MCS		GENMASK( 3,  0)
#घोषणा STA_STATS_FIELD_VHT_NSS		GENMASK( 7,  4)
#घोषणा STA_STATS_FIELD_HE_MCS		GENMASK( 3,  0)
#घोषणा STA_STATS_FIELD_HE_NSS		GENMASK( 7,  4)
#घोषणा STA_STATS_FIELD_BW		GENMASK(11,  8)
#घोषणा STA_STATS_FIELD_SGI		GENMASK(12, 12)
#घोषणा STA_STATS_FIELD_TYPE		GENMASK(15, 13)
#घोषणा STA_STATS_FIELD_HE_RU		GENMASK(18, 16)
#घोषणा STA_STATS_FIELD_HE_GI		GENMASK(20, 19)
#घोषणा STA_STATS_FIELD_HE_DCM		GENMASK(21, 21)

#घोषणा STA_STATS_FIELD(_n, _v)		FIELD_PREP(STA_STATS_FIELD_ ## _n, _v)
#घोषणा STA_STATS_GET(_n, _v)		FIELD_GET(STA_STATS_FIELD_ ## _n, _v)

#घोषणा STA_STATS_RATE_INVALID		0

अटल अंतरभूत u32 sta_stats_encode_rate(काष्ठा ieee80211_rx_status *s)
अणु
	u32 r;

	r = STA_STATS_FIELD(BW, s->bw);

	अगर (s->enc_flags & RX_ENC_FLAG_SHORT_GI)
		r |= STA_STATS_FIELD(SGI, 1);

	चयन (s->encoding) अणु
	हाल RX_ENC_VHT:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_VHT);
		r |= STA_STATS_FIELD(VHT_NSS, s->nss);
		r |= STA_STATS_FIELD(VHT_MCS, s->rate_idx);
		अवरोध;
	हाल RX_ENC_HT:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_HT);
		r |= STA_STATS_FIELD(HT_MCS, s->rate_idx);
		अवरोध;
	हाल RX_ENC_LEGACY:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_LEGACY);
		r |= STA_STATS_FIELD(LEGACY_BAND, s->band);
		r |= STA_STATS_FIELD(LEGACY_IDX, s->rate_idx);
		अवरोध;
	हाल RX_ENC_HE:
		r |= STA_STATS_FIELD(TYPE, STA_STATS_RATE_TYPE_HE);
		r |= STA_STATS_FIELD(HE_NSS, s->nss);
		r |= STA_STATS_FIELD(HE_MCS, s->rate_idx);
		r |= STA_STATS_FIELD(HE_GI, s->he_gi);
		r |= STA_STATS_FIELD(HE_RU, s->he_ru);
		r |= STA_STATS_FIELD(HE_DCM, s->he_dcm);
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस STA_STATS_RATE_INVALID;
	पूर्ण

	वापस r;
पूर्ण

#पूर्ण_अगर /* STA_INFO_H */
