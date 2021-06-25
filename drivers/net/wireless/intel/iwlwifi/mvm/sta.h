<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2016 Intel Deutschland GmbH
 */
#अगर_अघोषित __sta_h__
#घोषणा __sta_h__

#समावेश <linux/spinlock.h>
#समावेश <net/mac80211.h>
#समावेश <linux/रुको.h>

#समावेश "iwl-trans.h" /* क्रम IWL_MAX_TID_COUNT */
#समावेश "fw-api.h" /* IWL_MVM_STATION_COUNT_MAX */
#समावेश "rs.h"

काष्ठा iwl_mvm;
काष्ठा iwl_mvm_vअगर;

/**
 * DOC: DQA - Dynamic Queue Allocation -पूर्णांकroduction
 *
 * Dynamic Queue Allocation (AKA "DQA") is a feature implemented in iwlwअगरi
 * driver to allow dynamic allocation of queues on-demand, rather than allocate
 * them अटलally ahead of समय. Ideally, we would like to allocate one queue
 * per RA/TID, thus allowing an AP - क्रम example - to send BE traffic to STA2
 * even अगर it also needs to send traffic to a sleeping STA1, without being
 * blocked by the sleeping station.
 *
 * Although the queues in DQA mode are dynamically allocated, there are still
 * some queues that are अटलally allocated:
 *	TXQ #0 - command queue
 *	TXQ #1 - aux frames
 *	TXQ #2 - P2P device frames
 *	TXQ #3 - P2P GO/SoftAP GCAST/BCAST frames
 *	TXQ #4 - BSS DATA frames queue
 *	TXQ #5-8 - Non-QoS and MGMT frames queue pool
 *	TXQ #9 - P2P GO/SoftAP probe responses
 *	TXQ #10-31 - DATA frames queue pool
 * The queues are dynamically taken from either the MGMT frames queue pool or
 * the DATA frames one. See the %iwl_mvm_dqa_txq क्रम more inक्रमmation on every
 * queue.
 *
 * When a frame क्रम a previously unseen RA/TID comes in, it needs to be deferred
 * until a queue is allocated क्रम it, and only then can be TXed. Thereक्रमe, it
 * is placed पूर्णांकo %iwl_mvm_tid_data.deferred_tx_frames, and a worker called
 * %mvm->add_stream_wk later allocates the queues and TXes the deferred frames.
 *
 * For convenience, MGMT is considered as अगर it has TID=8, and go to the MGMT
 * queues in the pool. If there is no दीर्घer a मुक्त MGMT queue to allocate, a
 * queue will be allocated from the DATA pool instead. Since QoS NDPs can create
 * a problem क्रम aggregations, they too will use a MGMT queue.
 *
 * When adding a STA, a DATA queue is reserved क्रम it so that it can TX from
 * it. If no such मुक्त queue exists क्रम reserving, the STA addition will fail.
 *
 * If the DATA queue pool माला_लो exhausted, no new STA will be accepted, and अगर a
 * new RA/TID comes in क्रम an existing STA, one of the STA's queues will become
 * shared and will serve more than the single TID (but always क्रम the same RA!).
 *
 * When a RA/TID needs to become aggregated, no new queue is required to be
 * allocated, only mark the queue as aggregated via the ADD_STA command. Note,
 * however, that a shared queue cannot be aggregated, and only after the other
 * TIDs become inactive and are हटाओd - only then can the queue be
 * reconfigured and become aggregated.
 *
 * When removing a station, its queues are वापसed to the pool क्रम reuse. Here
 * we also need to make sure that we are synced with the worker thपढ़ो that TXes
 * the deferred frames so we करोn't get पूर्णांकo a situation where the queues are
 * हटाओd and then the worker माला_दो deferred frames onto the released queues or
 * tries to allocate new queues क्रम a STA we करोn't need anymore.
 */

/**
 * DOC: station table - पूर्णांकroduction
 *
 * The station table is a list of data काष्ठाure that reprensent the stations.
 * In STA/P2P client mode, the driver will hold one station क्रम the AP/ GO.
 * In GO/AP mode, the driver will have as many stations as associated clients.
 * All these stations are reflected in the fw's station table. The driver
 * keeps the fw's station table up to date with the ADD_STA command. Stations
 * can be हटाओd by the REMOVE_STA command.
 *
 * All the data related to a station is held in the काष्ठाure %iwl_mvm_sta
 * which is embed in the mac80211's %ieee80211_sta (in the drv_priv) area.
 * This data includes the index of the station in the fw, per tid inक्रमmation
 * (sequence numbers, Block-ack state machine, etc...). The stations are
 * created and deleted by the %sta_state callback from %ieee80211_ops.
 *
 * The driver holds a map: %fw_id_to_mac_id that allows to fetch a
 * %ieee80211_sta (and the %iwl_mvm_sta embedded पूर्णांकo it) based on a fw
 * station index. That way, the driver is able to get the tid related data in
 * O(1) in समय sensitive paths (Tx / Tx response / BA notअगरication). These
 * paths are triggered by the fw, and the driver needs to get a poपूर्णांकer to the
 * %ieee80211 काष्ठाure. This map helps to get that poपूर्णांकer quickly.
 */

/**
 * DOC: station table - locking
 *
 * As stated beक्रमe, the station is created / deleted by mac80211's %sta_state
 * callback from %ieee80211_ops which can sleep. The next paragraph explains
 * the locking of a single stations, the next ones relates to the station
 * table.
 *
 * The station holds the sequence number per tid. So this data needs to be
 * accessed in the Tx path (which is softIRQ). It also holds the Block-Ack
 * inक्रमmation (the state machine / and the logic that checks अगर the queues
 * were drained), so it also needs to be accessible from the Tx response flow.
 * In लघु, the station needs to be access from sleepable context as well as
 * from tasklets, so the station itself needs a spinlock.
 *
 * The ग_लिखोrs of %fw_id_to_mac_id map are serialized by the global mutex of
 * the mvm op_mode. This is possible since %sta_state can sleep.
 * The poपूर्णांकers in this map are RCU रक्षित, hence we won't replace the
 * station जबतक we have Tx / Tx response / BA notअगरication running.
 *
 * If a station is deleted जबतक it still has packets in its A-MPDU queues,
 * then the reclaim flow will notice that there is no station in the map क्रम
 * sta_id and it will dump the responses.
 */

/**
 * DOC: station table - पूर्णांकernal stations
 *
 * The FW needs a few पूर्णांकernal stations that are not reflected in
 * mac80211, such as broadcast station in AP / GO mode, or AUX sta क्रम
 * scanning and P2P device (during the GO negotiation).
 * For these kind of stations we have %iwl_mvm_पूर्णांक_sta काष्ठा which holds the
 * data relevant क्रम them from both %iwl_mvm_sta and %ieee80211_sta.
 * Usually the data क्रम these stations is अटल, so no locking is required,
 * and no TID data as this is also not needed.
 * One thing to note, is that these stations have an ID in the fw, but not
 * in mac80211. In order to "reserve" them a sta_id in %fw_id_to_mac_id
 * we fill ERR_PTR(EINVAL) in this mapping and all other dereferencing of
 * poपूर्णांकers from this mapping need to check that the value is not error
 * or शून्य.
 *
 * Currently there is only one auxiliary station क्रम scanning, initialized
 * on init.
 */

/**
 * DOC: station table - AP Station in STA mode
 *
 * %iwl_mvm_vअगर includes the index of the AP station in the fw's STA table:
 * %ap_sta_id. To get the poपूर्णांक to the corresponding %ieee80211_sta,
 * &fw_id_to_mac_id can be used. Due to the way the fw works, we must not हटाओ
 * the AP station from the fw beक्रमe setting the MAC context as unassociated.
 * Hence, %fw_id_to_mac_id[%ap_sta_id] will be शून्यed when the AP station is
 * हटाओd by mac80211, but the station won't be हटाओd in the fw until the
 * VIF is set as unassociated. Then, %ap_sta_id will be invalidated.
 */

/**
 * DOC: station table - Drain vs. Flush
 *
 * Flush means that all the frames in the SCD queue are dumped regardless the
 * station to which they were sent. We करो that when we disassociate and beक्रमe
 * we हटाओ the STA of the AP. The flush can be करोne synchronously against the
 * fw.
 * Drain means that the fw will drop all the frames sent to a specअगरic station.
 * This is useful when a client (अगर we are IBSS / GO or AP) disassociates.
 */

/**
 * DOC: station table - fw restart
 *
 * When the fw निश्चितs, or we have any other issue that requires to reset the
 * driver, we require mac80211 to reconfigure the driver. Since the निजी
 * data of the stations is embed in mac80211's %ieee80211_sta, that data will
 * not be zeroed and needs to be reinitialized manually.
 * %IWL_MVM_STATUS_IN_HW_RESTART is set during restart and that will hपूर्णांक us
 * that we must not allocate a new sta_id but reuse the previous one. This
 * means that the stations being re-added after the reset will have the same
 * place in the fw as beक्रमe the reset. We करो need to zero the %fw_id_to_mac_id
 * map, since the stations aren't in the fw any more. Internal stations that
 * are not added by mac80211 will be re-added in the init flow that is called
 * after the restart: mac80211 call's %iwl_mvm_mac_start which calls to
 * %iwl_mvm_up.
 */

/**
 * DOC: AP mode - PS
 *
 * When a station is asleep, the fw will set it as "asleep". All frames on
 * shared queues (i.e. non-aggregation queues) to that station will be dropped
 * by the fw (%TX_STATUS_FAIL_DEST_PS failure code).
 *
 * AMPDUs are in a separate queue that is stopped by the fw. We just need to
 * let mac80211 know when there are frames in these queues so that it can
 * properly handle trigger frames.
 *
 * When a trigger frame is received, mac80211 tells the driver to send frames
 * from the AMPDU queues or sends frames to non-aggregation queues itself,
 * depending on which ACs are delivery-enabled and what TID has frames to
 * transmit. Note that mac80211 has all the knowledge since all the non-agg
 * frames are buffered / filtered, and the driver tells mac80211 about agg
 * frames). The driver needs to tell the fw to let frames out even अगर the
 * station is asleep. This is करोne by %iwl_mvm_sta_modअगरy_sleep_tx_count.
 *
 * When we receive a frame from that station with PM bit unset, the driver
 * needs to let the fw know that this station isn't asleep any more. This is
 * करोne by %iwl_mvm_sta_modअगरy_ps_wake in response to mac80211 संकेतing the
 * station's wakeup.
 *
 * For a GO, the Service Period might be cut लघु due to an असलence period
 * of the GO. In this (and all other हालs) the firmware notअगरies us with the
 * EOSP_NOTIFICATION, and we notअगरy mac80211 of that. Further frames that we
 * alपढ़ोy sent to the device will be rejected again.
 *
 * See also "AP support for powersaving clients" in mac80211.h.
 */

/**
 * क्रमागत iwl_mvm_agg_state
 *
 * The state machine of the BA agreement establishment / tear करोwn.
 * These states relate to a specअगरic RA / TID.
 *
 * @IWL_AGG_OFF: aggregation is not used
 * @IWL_AGG_QUEUED: aggregation start work has been queued
 * @IWL_AGG_STARTING: aggregation are starting (between start and oper)
 * @IWL_AGG_ON: aggregation session is up
 * @IWL_EMPTYING_HW_QUEUE_ADDBA: establishing a BA session - रुकोing क्रम the
 *	HW queue to be empty from packets क्रम this RA /TID.
 * @IWL_EMPTYING_HW_QUEUE_DELBA: tearing करोwn a BA session - रुकोing क्रम the
 *	HW queue to be empty from packets क्रम this RA /TID.
 */
क्रमागत iwl_mvm_agg_state अणु
	IWL_AGG_OFF = 0,
	IWL_AGG_QUEUED,
	IWL_AGG_STARTING,
	IWL_AGG_ON,
	IWL_EMPTYING_HW_QUEUE_ADDBA,
	IWL_EMPTYING_HW_QUEUE_DELBA,
पूर्ण;

/**
 * काष्ठा iwl_mvm_tid_data - holds the states क्रम each RA / TID
 * @seq_number: the next WiFi sequence number to use
 * @next_reclaimed: the WiFi sequence number of the next packet to be acked.
 *	This is basically (last acked packet++).
 * @rate_n_flags: Rate at which Tx was attempted. Holds the data between the
 *	Tx response (TX_CMD), and the block ack notअगरication (COMPRESSED_BA).
 * @lq_color: the color of the LQ command as it appears in tx response.
 * @amsdu_in_ampdu_allowed: true अगर A-MSDU in A-MPDU is allowed.
 * @state: state of the BA agreement establishment / tear करोwn.
 * @txq_id: Tx queue used by the BA session / DQA
 * @ssn: the first packet to be sent in AGG HW queue in Tx AGG start flow, or
 *	the first packet to be sent in legacy HW queue in Tx AGG stop flow.
 *	Basically when next_reclaimed reaches ssn, we can tell mac80211 that
 *	we are पढ़ोy to finish the Tx AGG stop / start flow.
 * @tx_समय: medium समय consumed by this A-MPDU
 * @tpt_meas_start: समय of the throughput measurements start, is reset every HZ
 * @tx_count_last: number of frames transmitted during the last second
 * @tx_count: counts the number of frames transmitted since the last reset of
 *	 tpt_meas_start
 */
काष्ठा iwl_mvm_tid_data अणु
	u16 seq_number;
	u16 next_reclaimed;
	/* The rest is Tx AGG related */
	u32 rate_n_flags;
	u8 lq_color;
	bool amsdu_in_ampdu_allowed;
	क्रमागत iwl_mvm_agg_state state;
	u16 txq_id;
	u16 ssn;
	u16 tx_समय;
	अचिन्हित दीर्घ tpt_meas_start;
	u32 tx_count_last;
	u32 tx_count;
पूर्ण;

काष्ठा iwl_mvm_key_pn अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा अणु
		u8 pn[IWL_MAX_TID_COUNT][IEEE80211_CCMP_PN_LEN];
	पूर्ण ____cacheline_aligned_in_smp q[];
पूर्ण;

/**
 * क्रमागत iwl_mvm_rxq_notअगर_type - Internal message identअगरier
 *
 * @IWL_MVM_RXQ_EMPTY: empty sync notअगरication
 * @IWL_MVM_RXQ_NOTIF_DEL_BA: notअगरy RSS queues of delBA
 * @IWL_MVM_RXQ_NSSN_SYNC: notअगरy all the RSS queues with the new NSSN
 */
क्रमागत iwl_mvm_rxq_notअगर_type अणु
	IWL_MVM_RXQ_EMPTY,
	IWL_MVM_RXQ_NOTIF_DEL_BA,
	IWL_MVM_RXQ_NSSN_SYNC,
पूर्ण;

/**
 * काष्ठा iwl_mvm_पूर्णांकernal_rxq_notअगर - Internal representation of the data sent
 * in &iwl_rxq_sync_cmd. Should be DWORD aligned.
 * FW is agnostic to the payload, so there are no endianity requirements.
 *
 * @type: value from &iwl_mvm_rxq_notअगर_type
 * @sync: ctrl path is रुकोing क्रम all notअगरications to be received
 * @cookie: पूर्णांकernal cookie to identअगरy old notअगरications
 * @data: payload
 */
काष्ठा iwl_mvm_पूर्णांकernal_rxq_notअगर अणु
	u16 type;
	u16 sync;
	u32 cookie;
	u8 data[];
पूर्ण __packed;

काष्ठा iwl_mvm_delba_data अणु
	u32 baid;
पूर्ण __packed;

काष्ठा iwl_mvm_nssn_sync_data अणु
	u32 baid;
	u32 nssn;
पूर्ण __packed;

/**
 * काष्ठा iwl_mvm_rxq_dup_data - per station per rx queue data
 * @last_seq: last sequence per tid क्रम duplicate packet detection
 * @last_sub_frame: last subframe packet
 */
काष्ठा iwl_mvm_rxq_dup_data अणु
	__le16 last_seq[IWL_MAX_TID_COUNT + 1];
	u8 last_sub_frame[IWL_MAX_TID_COUNT + 1];
पूर्ण ____cacheline_aligned_in_smp;

/**
 * काष्ठा iwl_mvm_sta - representation of a station in the driver
 * @sta_id: the index of the station in the fw (will be replaced by id_n_color)
 * @tfd_queue_msk: the tfd queues used by the station
 * @mac_id_n_color: the MAC context this station is linked to
 * @tid_disable_agg: biपंचांगap: अगर bit(tid) is set, the fw won't send ampdus क्रम
 *	tid.
 * @max_agg_bufsize: the maximal size of the AGG buffer क्रम this station
 * @sta_type: station type
 * @sta_state: station state according to क्रमागत %ieee80211_sta_state
 * @bt_reduced_txघातer: is reduced tx घातer enabled क्रम this station
 * @next_status_eosp: the next reclaimed packet is a PS-Poll response and
 *	we need to संकेत the EOSP
 * @lock: lock to protect the whole काष्ठा. Since %tid_data is access from Tx
 * and from Tx response flow, it needs a spinlock.
 * @tid_data: per tid data + mgmt. Look at %iwl_mvm_tid_data.
 * @tid_to_baid: a simple map of TID to baid
 * @lq_sta: holds rate scaling data, either क्रम the हाल when RS is करोne in
 *	the driver - %rs_drv or in the FW - %rs_fw.
 * @reserved_queue: the queue reserved क्रम this STA क्रम DQA purposes
 *	Every STA has is given one reserved queue to allow it to operate. If no
 *	such queue can be guaranteed, the STA addition will fail.
 * @tx_protection: reference counter क्रम controlling the Tx protection.
 * @tt_tx_protection: is thermal throttling enable Tx protection?
 * @disable_tx: is tx to this STA disabled?
 * @amsdu_enabled: biपंचांगap of TX AMSDU allowed TIDs.
 *	In हाल TLC offload is not active it is either 0xFFFF or 0.
 * @max_amsdu_len: max AMSDU length
 * @orig_amsdu_len: used to save the original amsdu_len when it is changed via
 *      debugfs.  If it's set to 0, it means that it is it's not set via
 *      debugfs.
 * @agg_tids: biपंचांगap of tids whose status is operational aggregated (IWL_AGG_ON)
 * @sleep_tx_count: the number of frames that we told the firmware to let out
 *	even when that station is asleep. This is useful in हाल the queue
 *	माला_लो empty beक्रमe all the frames were sent, which can happen when
 *	we are sending frames from an AMPDU queue and there was a hole in
 *	the BA winकरोw. To be used क्रम UAPSD only.
 * @ptk_pn: per-queue PTK PN data काष्ठाures
 * @dup_data: per queue duplicate packet detection data
 * @deferred_traffic_tid_map: indication biपंचांगap of deferred traffic per-TID
 * @tx_ant: the index of the antenna to use क्रम data tx to this station. Only
 *	used during connection establishment (e.g. क्रम the 4 way handshake
 *	exchange).
 *
 * When mac80211 creates a station it reserves some space (hw->sta_data_size)
 * in the काष्ठाure क्रम use by driver. This काष्ठाure is placed in that
 * space.
 *
 */
काष्ठा iwl_mvm_sta अणु
	u32 sta_id;
	u32 tfd_queue_msk;
	u32 mac_id_n_color;
	u16 tid_disable_agg;
	u16 max_agg_bufsize;
	क्रमागत iwl_sta_type sta_type;
	क्रमागत ieee80211_sta_state sta_state;
	bool bt_reduced_txघातer;
	bool next_status_eosp;
	spinlock_t lock;
	काष्ठा iwl_mvm_tid_data tid_data[IWL_MAX_TID_COUNT + 1];
	u8 tid_to_baid[IWL_MAX_TID_COUNT];
	जोड़ अणु
		काष्ठा iwl_lq_sta_rs_fw rs_fw;
		काष्ठा iwl_lq_sta rs_drv;
	पूर्ण lq_sta;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा iwl_mvm_key_pn __rcu *ptk_pn[4];
	काष्ठा iwl_mvm_rxq_dup_data *dup_data;

	u8 reserved_queue;

	/* Temporary, until the new TLC will control the Tx protection */
	s8 tx_protection;
	bool tt_tx_protection;

	bool disable_tx;
	u16 amsdu_enabled;
	u16 max_amsdu_len;
	u16 orig_amsdu_len;
	bool sleeping;
	u8 agg_tids;
	u8 sleep_tx_count;
	u8 avg_energy;
	u8 tx_ant;
पूर्ण;

u16 iwl_mvm_tid_queued(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_tid_data *tid_data);

अटल अंतरभूत काष्ठा iwl_mvm_sta *
iwl_mvm_sta_from_mac80211(काष्ठा ieee80211_sta *sta)
अणु
	वापस (व्योम *)sta->drv_priv;
पूर्ण

/**
 * काष्ठा iwl_mvm_पूर्णांक_sta - representation of an पूर्णांकernal station (auxiliary or
 * broadcast)
 * @sta_id: the index of the station in the fw (will be replaced by id_n_color)
 * @type: station type
 * @tfd_queue_msk: the tfd queues used by the station
 */
काष्ठा iwl_mvm_पूर्णांक_sta अणु
	u32 sta_id;
	क्रमागत iwl_sta_type type;
	u32 tfd_queue_msk;
पूर्ण;

/**
 * Send the STA info to the FW.
 *
 * @mvm: the iwl_mvm* to use
 * @sta: the STA
 * @update: this is true अगर the FW is being updated about a STA it alपढ़ोy knows
 *	about. Otherwise (अगर this is a new STA), this should be false.
 * @flags: अगर update==true, this marks what is being changed via ORs of values
 *	from क्रमागत iwl_sta_modअगरy_flag. Otherwise, this is ignored.
 */
पूर्णांक iwl_mvm_sta_send_to_fw(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			   bool update, अचिन्हित पूर्णांक flags);
पूर्णांक iwl_mvm_add_sta(काष्ठा iwl_mvm *mvm,
		    काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta);

अटल अंतरभूत पूर्णांक iwl_mvm_update_sta(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta)
अणु
	वापस iwl_mvm_sta_send_to_fw(mvm, sta, true, 0);
पूर्ण

पूर्णांक iwl_mvm_रुको_sta_queues_empty(काष्ठा iwl_mvm *mvm,
				  काष्ठा iwl_mvm_sta *mvm_sta);
पूर्णांक iwl_mvm_rm_sta(काष्ठा iwl_mvm *mvm,
		   काष्ठा ieee80211_vअगर *vअगर,
		   काष्ठा ieee80211_sta *sta);
पूर्णांक iwl_mvm_rm_sta_id(काष्ठा iwl_mvm *mvm,
		      काष्ठा ieee80211_vअगर *vअगर,
		      u8 sta_id);
पूर्णांक iwl_mvm_set_sta_key(काष्ठा iwl_mvm *mvm,
			काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta,
			काष्ठा ieee80211_key_conf *keyconf,
			u8 key_offset);
पूर्णांक iwl_mvm_हटाओ_sta_key(काष्ठा iwl_mvm *mvm,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा ieee80211_key_conf *keyconf);

व्योम iwl_mvm_update_tkip_key(काष्ठा iwl_mvm *mvm,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_key_conf *keyconf,
			     काष्ठा ieee80211_sta *sta, u32 iv32,
			     u16 *phase1key);

व्योम iwl_mvm_rx_eosp_notअगर(काष्ठा iwl_mvm *mvm,
			   काष्ठा iwl_rx_cmd_buffer *rxb);

/* AMPDU */
पूर्णांक iwl_mvm_sta_rx_agg(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
		       पूर्णांक tid, u16 ssn, bool start, u16 buf_size, u16 समयout);
पूर्णांक iwl_mvm_sta_tx_agg_start(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_sta *sta, u16 tid, u16 *ssn);
पूर्णांक iwl_mvm_sta_tx_agg_oper(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u16 tid, u16 buf_size,
			    bool amsdu);
पूर्णांक iwl_mvm_sta_tx_agg_stop(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u16 tid);
पूर्णांक iwl_mvm_sta_tx_agg_flush(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta, u16 tid);

पूर्णांक iwl_mvm_sta_tx_agg(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
		       पूर्णांक tid, u8 queue, bool start);

पूर्णांक iwl_mvm_add_aux_sta(काष्ठा iwl_mvm *mvm, u32 lmac_id);
पूर्णांक iwl_mvm_rm_aux_sta(काष्ठा iwl_mvm *mvm);

पूर्णांक iwl_mvm_alloc_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_send_add_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_add_p2p_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_send_rm_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_rm_p2p_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_add_mcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_rm_mcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_allocate_पूर्णांक_sta(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_mvm_पूर्णांक_sta *sta,
				    u32 qmask, क्रमागत nl80211_अगरtype अगरtype,
				    क्रमागत iwl_sta_type type);
व्योम iwl_mvm_dealloc_bcast_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_dealloc_पूर्णांक_sta(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_पूर्णांक_sta *sta);
पूर्णांक iwl_mvm_add_snअगर_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_rm_snअगर_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_dealloc_snअगर_sta(काष्ठा iwl_mvm *mvm);

व्योम iwl_mvm_sta_modअगरy_ps_wake(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_sta *sta);
व्योम iwl_mvm_sta_modअगरy_sleep_tx_count(काष्ठा iwl_mvm *mvm,
				       काष्ठा ieee80211_sta *sta,
				       क्रमागत ieee80211_frame_release_type reason,
				       u16 cnt, u16 tids, bool more_data,
				       bool single_sta_queue);
पूर्णांक iwl_mvm_drain_sta(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
		      bool drain);
व्योम iwl_mvm_sta_modअगरy_disable_tx(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_mvm_sta *mvmsta, bool disable);
व्योम iwl_mvm_sta_modअगरy_disable_tx_ap(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_sta *sta,
				      bool disable);
व्योम iwl_mvm_modअगरy_all_sta_disable_tx(काष्ठा iwl_mvm *mvm,
				       काष्ठा iwl_mvm_vअगर *mvmvअगर,
				       bool disable);
व्योम iwl_mvm_csa_client_असलent(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_add_new_dqa_stream_wk(काष्ठा work_काष्ठा *wk);
पूर्णांक iwl_mvm_add_pasn_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा iwl_mvm_पूर्णांक_sta *sta, u8 *addr, u32 cipher,
			 u8 *key, u32 key_len);
#पूर्ण_अगर /* __sta_h__ */
