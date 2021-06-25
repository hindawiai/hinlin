<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Common निजी data क्रम ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on the mac80211 Prism54 code, which is
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 *
 * Based on the islsm (sofपंचांगac prism54) driver, which is:
 * Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 */

#अगर_अघोषित CW1200_H
#घोषणा CW1200_H

#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <net/mac80211.h>

#समावेश "queue.h"
#समावेश "wsm.h"
#समावेश "scan.h"
#समावेश "txrx.h"
#समावेश "pm.h"

/* Forward declarations */
काष्ठा hwbus_ops;
काष्ठा task_काष्ठा;
काष्ठा cw1200_debug_priv;
काष्ठा firmware;

#घोषणा CW1200_MAX_CTRL_FRAME_LEN	(0x1000)

#घोषणा CW1200_MAX_STA_IN_AP_MODE	(5)
#घोषणा CW1200_LINK_ID_AFTER_DTIM	(CW1200_MAX_STA_IN_AP_MODE + 1)
#घोषणा CW1200_LINK_ID_UAPSD		(CW1200_MAX_STA_IN_AP_MODE + 2)
#घोषणा CW1200_LINK_ID_MAX		(CW1200_MAX_STA_IN_AP_MODE + 3)
#घोषणा CW1200_MAX_REQUEUE_ATTEMPTS	(5)

#घोषणा CW1200_MAX_TID			(8)

#घोषणा CW1200_BLOCK_ACK_CNT		(30)
#घोषणा CW1200_BLOCK_ACK_THLD		(800)
#घोषणा CW1200_BLOCK_ACK_HIST		(3)
#घोषणा CW1200_BLOCK_ACK_INTERVAL	(1 * HZ / CW1200_BLOCK_ACK_HIST)

#घोषणा CW1200_JOIN_TIMEOUT		(1 * HZ)
#घोषणा CW1200_AUTH_TIMEOUT		(5 * HZ)

काष्ठा cw1200_ht_info अणु
	काष्ठा ieee80211_sta_ht_cap     ht_cap;
	क्रमागत nl80211_channel_type       channel_type;
	u16                             operation_mode;
पूर्ण;

/* Please keep order */
क्रमागत cw1200_join_status अणु
	CW1200_JOIN_STATUS_PASSIVE = 0,
	CW1200_JOIN_STATUS_MONITOR,
	CW1200_JOIN_STATUS_JOINING,
	CW1200_JOIN_STATUS_PRE_STA,
	CW1200_JOIN_STATUS_STA,
	CW1200_JOIN_STATUS_IBSS,
	CW1200_JOIN_STATUS_AP,
पूर्ण;

क्रमागत cw1200_link_status अणु
	CW1200_LINK_OFF,
	CW1200_LINK_RESERVE,
	CW1200_LINK_SOFT,
	CW1200_LINK_HARD,
	CW1200_LINK_RESET,
	CW1200_LINK_RESET_REMAP,
पूर्ण;

बाह्य पूर्णांक cw1200_घातer_mode;
बाह्य स्थिर अक्षर * स्थिर cw1200_fw_types[];

काष्ठा cw1200_link_entry अणु
	अचिन्हित दीर्घ			बारtamp;
	क्रमागत cw1200_link_status		status;
	क्रमागत cw1200_link_status		prev_status;
	u8				mac[ETH_ALEN];
	u8				buffered[CW1200_MAX_TID];
	काष्ठा sk_buff_head		rx_queue;
पूर्ण;

काष्ठा cw1200_common अणु
	/* पूर्णांकerfaces to the rest of the stack */
	काष्ठा ieee80211_hw		*hw;
	काष्ठा ieee80211_vअगर		*vअगर;
	काष्ठा device			*pdev;

	/* Statistics */
	काष्ठा ieee80211_low_level_stats stats;

	/* Our macaddr */
	u8 mac_addr[ETH_ALEN];

	/* Hardware पूर्णांकerface */
	स्थिर काष्ठा hwbus_ops		*hwbus_ops;
	काष्ठा hwbus_priv		*hwbus_priv;

	/* Hardware inक्रमmation */
	क्रमागत अणु
		HIF_9000_SILICON_VERSATILE = 0,
		HIF_8601_VERSATILE,
		HIF_8601_SILICON,
	पूर्ण hw_type;
	क्रमागत अणु
		CW1200_HW_REV_CUT10 = 10,
		CW1200_HW_REV_CUT11 = 11,
		CW1200_HW_REV_CUT20 = 20,
		CW1200_HW_REV_CUT22 = 22,
		CW1X60_HW_REV       = 40,
	पूर्ण hw_revision;
	पूर्णांक                             hw_refclk;
	bool				hw_have_5ghz;
	स्थिर काष्ठा firmware		*sdd;
	अक्षर                            *sdd_path;

	काष्ठा cw1200_debug_priv	*debug;

	काष्ठा workqueue_काष्ठा		*workqueue;
	काष्ठा mutex			conf_mutex;

	काष्ठा cw1200_queue		tx_queue[4];
	काष्ठा cw1200_queue_stats	tx_queue_stats;
	पूर्णांक				tx_burst_idx;

	/* firmware/hardware info */
	अचिन्हित पूर्णांक tx_hdr_len;

	/* Radio data */
	पूर्णांक output_घातer;

	/* BBP/MAC state */
	काष्ठा ieee80211_rate		*rates;
	काष्ठा ieee80211_rate		*mcs_rates;
	काष्ठा ieee80211_channel	*channel;
	काष्ठा wsm_edca_params		edca;
	काष्ठा wsm_tx_queue_params	tx_queue_params;
	काष्ठा wsm_mib_association_mode	association_mode;
	काष्ठा wsm_set_bss_params	bss_params;
	काष्ठा cw1200_ht_info		ht_info;
	काष्ठा wsm_set_pm		घातersave_mode;
	काष्ठा wsm_set_pm		firmware_ps_mode;
	पूर्णांक				cqm_rssi_thold;
	अचिन्हित			cqm_rssi_hyst;
	bool				cqm_use_rssi;
	पूर्णांक				cqm_beacon_loss_count;
	पूर्णांक				channel_चयन_in_progress;
	रुको_queue_head_t		channel_चयन_करोne;
	u8				दीर्घ_frame_max_tx_count;
	u8				लघु_frame_max_tx_count;
	पूर्णांक				mode;
	bool				enable_beacon;
	पूर्णांक				beacon_पूर्णांक;
	bool				listening;
	काष्ठा wsm_rx_filter		rx_filter;
	काष्ठा wsm_mib_multicast_filter multicast_filter;
	bool				has_multicast_subscription;
	bool				disable_beacon_filter;
	काष्ठा work_काष्ठा		update_filtering_work;
	काष्ठा work_काष्ठा		set_beacon_wakeup_period_work;

	u8				ba_rx_tid_mask;
	u8				ba_tx_tid_mask;

	काष्ठा cw1200_pm_state		pm_state;

	काष्ठा wsm_p2p_ps_modeinfo	p2p_ps_modeinfo;
	काष्ठा wsm_uapsd_info		uapsd_info;
	bool				setbssparams_करोne;
	bool				bt_present;
	u8				conf_listen_पूर्णांकerval;
	u32				listen_पूर्णांकerval;
	u32				erp_info;
	u32				rts_threshold;

	/* BH */
	atomic_t			bh_rx;
	atomic_t			bh_tx;
	atomic_t			bh_term;
	atomic_t			bh_suspend;

	काष्ठा workqueue_काष्ठा         *bh_workqueue;
	काष्ठा work_काष्ठा              bh_work;

	पूर्णांक				bh_error;
	रुको_queue_head_t		bh_wq;
	रुको_queue_head_t		bh_evt_wq;
	u8				buf_id_tx;
	u8				buf_id_rx;
	u8				wsm_rx_seq;
	u8				wsm_tx_seq;
	पूर्णांक				hw_bufs_used;
	bool				घातersave_enabled;
	bool				device_can_sleep;

	/* Scan status */
	काष्ठा cw1200_scan scan;
	/* Keep cw1200 awake (WUP = 1) 1 second after each scan to aव्योम
	 * FW issue with sleeping/waking up.
	 */
	atomic_t			recent_scan;
	काष्ठा delayed_work		clear_recent_scan_work;

	/* WSM */
	काष्ठा wsm_startup_ind		wsm_caps;
	काष्ठा mutex			wsm_cmd_mux;
	काष्ठा wsm_buf			wsm_cmd_buf;
	काष्ठा wsm_cmd			wsm_cmd;
	रुको_queue_head_t		wsm_cmd_wq;
	रुको_queue_head_t		wsm_startup_करोne;
	पूर्णांक                             firmware_पढ़ोy;
	atomic_t			tx_lock;

	/* WSM debug */
	पूर्णांक				wsm_enable_wsm_dumps;

	/* WSM Join */
	क्रमागत cw1200_join_status	join_status;
	u32			pending_frame_id;
	bool			join_pending;
	काष्ठा delayed_work	join_समयout;
	काष्ठा work_काष्ठा	unjoin_work;
	काष्ठा work_काष्ठा	join_complete_work;
	पूर्णांक			join_complete_status;
	पूर्णांक			join_dtim_period;
	bool			delayed_unjoin;

	/* TX/RX and security */
	s8			wep_शेष_key_id;
	काष्ठा work_काष्ठा	wep_key_work;
	u32			key_map;
	काष्ठा wsm_add_key	keys[WSM_KEY_MAX_INDEX + 1];

	/* AP घातersave */
	u32			link_id_map;
	काष्ठा cw1200_link_entry link_id_db[CW1200_MAX_STA_IN_AP_MODE];
	काष्ठा work_काष्ठा	link_id_work;
	काष्ठा delayed_work	link_id_gc_work;
	u32			sta_asleep_mask;
	u32			pspoll_mask;
	bool			aid0_bit_set;
	spinlock_t		ps_state_lock; /* Protect घातer save state */
	bool			buffered_multicasts;
	bool			tx_multicast;
	काष्ठा work_काष्ठा	set_tim_work;
	काष्ठा work_काष्ठा	set_cts_work;
	काष्ठा work_काष्ठा	multicast_start_work;
	काष्ठा work_काष्ठा	multicast_stop_work;
	काष्ठा समयr_list	mcast_समयout;

	/* WSM events and CQM implementation */
	spinlock_t		event_queue_lock; /* Protect event queue */
	काष्ठा list_head	event_queue;
	काष्ठा work_काष्ठा	event_handler;

	काष्ठा delayed_work	bss_loss_work;
	spinlock_t		bss_loss_lock; /* Protect BSS loss state */
	पूर्णांक                     bss_loss_state;
	u32                     bss_loss_confirm_id;
	पूर्णांक			delayed_link_loss;
	काष्ठा work_काष्ठा	bss_params_work;

	/* TX rate policy cache */
	काष्ठा tx_policy_cache tx_policy_cache;
	काष्ठा work_काष्ठा tx_policy_upload_work;

	/* legacy PS mode चयन in suspend */
	पूर्णांक			ps_mode_चयन_in_progress;
	रुको_queue_head_t	ps_mode_चयन_करोne;

	/* Workaround क्रम WFD testहाल 6.1.10*/
	काष्ठा work_काष्ठा	linkid_reset_work;
	u8			action_frame_sa[ETH_ALEN];
	u8			action_linkid;
पूर्ण;

काष्ठा cw1200_sta_priv अणु
	पूर्णांक link_id;
पूर्ण;

/* पूर्णांकerfaces क्रम the drivers */
पूर्णांक cw1200_core_probe(स्थिर काष्ठा hwbus_ops *hwbus_ops,
		      काष्ठा hwbus_priv *hwbus,
		      काष्ठा device *pdev,
		      काष्ठा cw1200_common **pself,
		      पूर्णांक ref_clk, स्थिर u8 *macaddr,
		      स्थिर अक्षर *sdd_path, bool have_5ghz);
व्योम cw1200_core_release(काष्ठा cw1200_common *self);

#घोषणा FWLOAD_BLOCK_SIZE (1024)

अटल अंतरभूत पूर्णांक cw1200_is_ht(स्थिर काष्ठा cw1200_ht_info *ht_info)
अणु
	वापस ht_info->channel_type != NL80211_CHAN_NO_HT;
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_ht_greenfield(स्थिर काष्ठा cw1200_ht_info *ht_info)
अणु
	वापस cw1200_is_ht(ht_info) &&
		(ht_info->ht_cap.cap & IEEE80211_HT_CAP_GRN_FLD) &&
		!(ht_info->operation_mode &
		  IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
पूर्ण

अटल अंतरभूत पूर्णांक cw1200_ht_ampdu_density(स्थिर काष्ठा cw1200_ht_info *ht_info)
अणु
	अगर (!cw1200_is_ht(ht_info))
		वापस 0;
	वापस ht_info->ht_cap.ampdu_density;
पूर्ण

#पूर्ण_अगर /* CW1200_H */
