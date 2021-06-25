<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2015  Intel Mobile Communications GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */

#अगर_अघोषित IEEE80211_I_H
#घोषणा IEEE80211_I_H

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/leds.h>
#समावेश <linux/idr.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश <net/fq.h>
#समावेश "key.h"
#समावेश "sta_info.h"
#समावेश "debug.h"

बाह्य स्थिर काष्ठा cfg80211_ops mac80211_config_ops;

काष्ठा ieee80211_local;

/* Maximum number of broadcast/multicast frames to buffer when some of the
 * associated stations are using घातer saving. */
#घोषणा AP_MAX_BC_BUFFER 128

/* Maximum number of frames buffered to all STAs, including multicast frames.
 * Note: increasing this limit increases the potential memory requirement. Each
 * frame can be up to about 2 kB दीर्घ. */
#घोषणा TOTAL_MAX_TX_BUFFER 512

/* Required encryption head and tailroom */
#घोषणा IEEE80211_ENCRYPT_HEADROOM 8
#घोषणा IEEE80211_ENCRYPT_TAILROOM 18

/* घातer level hasn't been configured (or set to स्वतःmatic) */
#घोषणा IEEE80211_UNSET_POWER_LEVEL	पूर्णांक_न्यून

/*
 * Some APs experience problems when working with U-APSD. Decreasing the
 * probability of that happening by using legacy mode क्रम all ACs but VO isn't
 * enough.
 *
 * Cisco 4410N originally क्रमced us to enable VO by शेष only because it
 * treated non-VO ACs as legacy.
 *
 * However some APs (notably Netgear R7000) silently reclassअगरy packets to
 * dअगरferent ACs. Since u-APSD ACs require trigger frames क्रम frame retrieval
 * clients would never see some frames (e.g. ARP responses) or would fetch them
 * accidentally after a दीर्घ समय.
 *
 * It makes little sense to enable u-APSD queues by शेष because it needs
 * userspace applications to be aware of it to actually take advantage of the
 * possible additional घातersavings. Implicitly depending on driver स्वतःtrigger
 * frame support करोesn't make much sense.
 */
#घोषणा IEEE80211_DEFAULT_UAPSD_QUEUES 0

#घोषणा IEEE80211_DEFAULT_MAX_SP_LEN		\
	IEEE80211_WMM_IE_STA_QOSINFO_SP_ALL

बाह्य स्थिर u8 ieee80211_ac_to_qos_mask[IEEE80211_NUM_ACS];

#घोषणा IEEE80211_DEAUTH_FRAME_LEN	(24 /* hdr */ + 2 /* reason */)

#घोषणा IEEE80211_MAX_न_अंक_INSTANCE_ID 255

काष्ठा ieee80211_bss अणु
	u32 device_ts_beacon, device_ts_presp;

	bool wmm_used;
	bool uapsd_supported;

#घोषणा IEEE80211_MAX_SUPP_RATES 32
	u8 supp_rates[IEEE80211_MAX_SUPP_RATES];
	माप_प्रकार supp_rates_len;
	काष्ठा ieee80211_rate *beacon_rate;

	u32 vht_cap_info;

	/*
	 * During association, we save an ERP value from a probe response so
	 * that we can feed ERP info to the driver when handling the
	 * association completes. these fields probably won't be up-to-date
	 * otherwise, you probably करोn't want to use them.
	 */
	bool has_erp_value;
	u8 erp_value;

	/* Keep track of the corruption of the last beacon/probe response. */
	u8 corrupt_data;

	/* Keep track of what bits of inक्रमmation we have valid info क्रम. */
	u8 valid_data;
पूर्ण;

/**
 * क्रमागत ieee80211_corrupt_data_flags - BSS data corruption flags
 * @IEEE80211_BSS_CORRUPT_BEACON: last beacon frame received was corrupted
 * @IEEE80211_BSS_CORRUPT_PROBE_RESP: last probe response received was corrupted
 *
 * These are bss flags that are attached to a bss in the
 * @corrupt_data field of &काष्ठा ieee80211_bss.
 */
क्रमागत ieee80211_bss_corrupt_data_flags अणु
	IEEE80211_BSS_CORRUPT_BEACON		= BIT(0),
	IEEE80211_BSS_CORRUPT_PROBE_RESP	= BIT(1)
पूर्ण;

/**
 * क्रमागत ieee80211_valid_data_flags - BSS valid data flags
 * @IEEE80211_BSS_VALID_WMM: WMM/UAPSD data was gathered from non-corrupt IE
 * @IEEE80211_BSS_VALID_RATES: Supported rates were gathered from non-corrupt IE
 * @IEEE80211_BSS_VALID_ERP: ERP flag was gathered from non-corrupt IE
 *
 * These are bss flags that are attached to a bss in the
 * @valid_data field of &काष्ठा ieee80211_bss.  They show which parts
 * of the data काष्ठाure were received as a result of an un-corrupted
 * beacon/probe response.
 */
क्रमागत ieee80211_bss_valid_data_flags अणु
	IEEE80211_BSS_VALID_WMM			= BIT(1),
	IEEE80211_BSS_VALID_RATES		= BIT(2),
	IEEE80211_BSS_VALID_ERP			= BIT(3)
पूर्ण;

प्रकार अचिन्हित __bitwise ieee80211_tx_result;
#घोषणा TX_CONTINUE	((__क्रमce ieee80211_tx_result) 0u)
#घोषणा TX_DROP		((__क्रमce ieee80211_tx_result) 1u)
#घोषणा TX_QUEUED	((__क्रमce ieee80211_tx_result) 2u)

#घोषणा IEEE80211_TX_UNICAST		BIT(1)
#घोषणा IEEE80211_TX_PS_BUFFERED	BIT(2)

काष्ठा ieee80211_tx_data अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff_head skbs;
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_key *key;
	काष्ठा ieee80211_tx_rate rate;

	अचिन्हित पूर्णांक flags;
पूर्ण;


प्रकार अचिन्हित __bitwise ieee80211_rx_result;
#घोषणा RX_CONTINUE		((__क्रमce ieee80211_rx_result) 0u)
#घोषणा RX_DROP_UNUSABLE	((__क्रमce ieee80211_rx_result) 1u)
#घोषणा RX_DROP_MONITOR		((__क्रमce ieee80211_rx_result) 2u)
#घोषणा RX_QUEUED		((__क्रमce ieee80211_rx_result) 3u)

/**
 * क्रमागत ieee80211_packet_rx_flags - packet RX flags
 * @IEEE80211_RX_AMSDU: a-MSDU packet
 * @IEEE80211_RX_MALFORMED_ACTION_FRM: action frame is malक्रमmed
 * @IEEE80211_RX_DEFERRED_RELEASE: frame was subjected to receive reordering
 *
 * These are per-frame flags that are attached to a frame in the
 * @rx_flags field of &काष्ठा ieee80211_rx_status.
 */
क्रमागत ieee80211_packet_rx_flags अणु
	IEEE80211_RX_AMSDU			= BIT(3),
	IEEE80211_RX_MALFORMED_ACTION_FRM	= BIT(4),
	IEEE80211_RX_DEFERRED_RELEASE		= BIT(5),
पूर्ण;

/**
 * क्रमागत ieee80211_rx_flags - RX data flags
 *
 * @IEEE80211_RX_CMNTR: received on cooked monitor alपढ़ोy
 * @IEEE80211_RX_BEACON_REPORTED: This frame was alपढ़ोy reported
 *	to cfg80211_report_obss_beacon().
 *
 * These flags are used across handling multiple पूर्णांकerfaces
 * क्रम a single frame.
 */
क्रमागत ieee80211_rx_flags अणु
	IEEE80211_RX_CMNTR		= BIT(0),
	IEEE80211_RX_BEACON_REPORTED	= BIT(1),
पूर्ण;

काष्ठा ieee80211_rx_data अणु
	काष्ठा list_head *list;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_key *key;

	अचिन्हित पूर्णांक flags;

	/*
	 * Index पूर्णांकo sequence numbers array, 0..16
	 * since the last (16) is used क्रम non-QoS,
	 * will be 16 on non-QoS frames.
	 */
	पूर्णांक seqno_idx;

	/*
	 * Index पूर्णांकo the security IV/PN arrays, 0..16
	 * since the last (16) is used क्रम CCMP-encrypted
	 * management frames, will be set to 16 on mgmt
	 * frames and 0 on non-QoS frames.
	 */
	पूर्णांक security_idx;

	जोड़ अणु
		काष्ठा अणु
			u32 iv32;
			u16 iv16;
		पूर्ण tkip;
		काष्ठा अणु
			u8 pn[IEEE80211_CCMP_PN_LEN];
		पूर्ण ccm_gcm;
	पूर्ण;
पूर्ण;

काष्ठा ieee80211_csa_settings अणु
	स्थिर u16 *counter_offsets_beacon;
	स्थिर u16 *counter_offsets_presp;

	पूर्णांक n_counter_offsets_beacon;
	पूर्णांक n_counter_offsets_presp;

	u8 count;
पूर्ण;

काष्ठा beacon_data अणु
	u8 *head, *tail;
	पूर्णांक head_len, tail_len;
	काष्ठा ieee80211_meshconf_ie *meshconf;
	u16 cntdwn_counter_offsets[IEEE80211_MAX_CNTDWN_COUNTERS_NUM];
	u8 cntdwn_current_counter;
	काष्ठा rcu_head rcu_head;
पूर्ण;

काष्ठा probe_resp अणु
	काष्ठा rcu_head rcu_head;
	पूर्णांक len;
	u16 cntdwn_counter_offsets[IEEE80211_MAX_CNTDWN_COUNTERS_NUM];
	u8 data[];
पूर्ण;

काष्ठा fils_discovery_data अणु
	काष्ठा rcu_head rcu_head;
	पूर्णांक len;
	u8 data[];
पूर्ण;

काष्ठा unsol_bcast_probe_resp_data अणु
	काष्ठा rcu_head rcu_head;
	पूर्णांक len;
	u8 data[];
पूर्ण;

काष्ठा ps_data अणु
	/* yes, this looks ugly, but guarantees that we can later use
	 * biपंचांगap_empty :)
	 * NB: करोn't touch this biपंचांगap, use sta_info_अणुset,clearपूर्ण_tim_bit */
	u8 tim[माप(अचिन्हित दीर्घ) * BITS_TO_LONGS(IEEE80211_MAX_AID + 1)]
			__aligned(__alignof__(अचिन्हित दीर्घ));
	काष्ठा sk_buff_head bc_buf;
	atomic_t num_sta_ps; /* number of stations in PS mode */
	पूर्णांक dtim_count;
	bool dtim_bc_mc;
पूर्ण;

काष्ठा ieee80211_अगर_ap अणु
	काष्ठा beacon_data __rcu *beacon;
	काष्ठा probe_resp __rcu *probe_resp;
	काष्ठा fils_discovery_data __rcu *fils_discovery;
	काष्ठा unsol_bcast_probe_resp_data __rcu *unsol_bcast_probe_resp;

	/* to be used after channel चयन. */
	काष्ठा cfg80211_beacon_data *next_beacon;
	काष्ठा list_head vlans; /* ग_लिखो-रक्षित with RTNL and local->mtx */

	काष्ठा ps_data ps;
	atomic_t num_mcast_sta; /* number of stations receiving multicast */

	bool multicast_to_unicast;
पूर्ण;

काष्ठा ieee80211_अगर_vlan अणु
	काष्ठा list_head list; /* ग_लिखो-रक्षित with RTNL and local->mtx */

	/* used क्रम all tx अगर the VLAN is configured to 4-addr mode */
	काष्ठा sta_info __rcu *sta;
	atomic_t num_mcast_sta; /* number of stations receiving multicast */
पूर्ण;

काष्ठा mesh_stats अणु
	__u32 fwded_mcast;		/* Mesh क्रमwarded multicast frames */
	__u32 fwded_unicast;		/* Mesh क्रमwarded unicast frames */
	__u32 fwded_frames;		/* Mesh total क्रमwarded frames */
	__u32 dropped_frames_ttl;	/* Not transmitted since mesh_ttl == 0*/
	__u32 dropped_frames_no_route;	/* Not transmitted, no route found */
	__u32 dropped_frames_congestion;/* Not क्रमwarded due to congestion */
पूर्ण;

#घोषणा PREQ_Q_F_START		0x1
#घोषणा PREQ_Q_F_REFRESH	0x2
काष्ठा mesh_preq_queue अणु
	काष्ठा list_head list;
	u8 dst[ETH_ALEN];
	u8 flags;
पूर्ण;

काष्ठा ieee80211_roc_work अणु
	काष्ठा list_head list;

	काष्ठा ieee80211_sub_अगर_data *sdata;

	काष्ठा ieee80211_channel *chan;

	bool started, पात, hw_begun, notअगरied;
	bool on_channel;

	अचिन्हित दीर्घ start_समय;

	u32 duration, req_duration;
	काष्ठा sk_buff *frame;
	u64 cookie, mgmt_tx_cookie;
	क्रमागत ieee80211_roc_type type;
पूर्ण;

/* flags used in काष्ठा ieee80211_अगर_managed.flags */
क्रमागत ieee80211_sta_flags अणु
	IEEE80211_STA_CONNECTION_POLL	= BIT(1),
	IEEE80211_STA_CONTROL_PORT	= BIT(2),
	IEEE80211_STA_DISABLE_HT	= BIT(4),
	IEEE80211_STA_MFP_ENABLED	= BIT(6),
	IEEE80211_STA_UAPSD_ENABLED	= BIT(7),
	IEEE80211_STA_शून्यFUNC_ACKED	= BIT(8),
	IEEE80211_STA_RESET_SIGNAL_AVE	= BIT(9),
	IEEE80211_STA_DISABLE_40MHZ	= BIT(10),
	IEEE80211_STA_DISABLE_VHT	= BIT(11),
	IEEE80211_STA_DISABLE_80P80MHZ	= BIT(12),
	IEEE80211_STA_DISABLE_160MHZ	= BIT(13),
	IEEE80211_STA_DISABLE_WMM	= BIT(14),
	IEEE80211_STA_ENABLE_RRM	= BIT(15),
	IEEE80211_STA_DISABLE_HE	= BIT(16),
पूर्ण;

काष्ठा ieee80211_mgd_auth_data अणु
	काष्ठा cfg80211_bss *bss;
	अचिन्हित दीर्घ समयout;
	पूर्णांक tries;
	u16 algorithm, expected_transaction;

	u8 key[WLAN_KEY_LEN_WEP104];
	u8 key_len, key_idx;
	bool करोne;
	bool peer_confirmed;
	bool समयout_started;

	u16 sae_trans, sae_status;
	माप_प्रकार data_len;
	u8 data[];
पूर्ण;

काष्ठा ieee80211_mgd_assoc_data अणु
	काष्ठा cfg80211_bss *bss;
	स्थिर u8 *supp_rates;

	अचिन्हित दीर्घ समयout;
	पूर्णांक tries;

	u16 capability;
	u8 prev_bssid[ETH_ALEN];
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 ssid_len;
	u8 supp_rates_len;
	bool wmm, uapsd;
	bool need_beacon;
	bool synced;
	bool समयout_started;

	u8 ap_ht_param;

	काष्ठा ieee80211_vht_cap ap_vht_cap;

	u8 fils_nonces[2 * FILS_NONCE_LEN];
	u8 fils_kek[FILS_MAX_KEK_LEN];
	माप_प्रकार fils_kek_len;

	माप_प्रकार ie_len;
	u8 ie[];
पूर्ण;

काष्ठा ieee80211_sta_tx_tspec अणु
	/* बारtamp of the first packet in the समय slice */
	अचिन्हित दीर्घ समय_slice_start;

	u32 admitted_समय; /* in usecs, unlike over the air */
	u8 tsid;
	s8 up; /* चिन्हित to be able to invalidate with -1 during tearकरोwn */

	/* consumed TX समय in microseconds in the समय slice */
	u32 consumed_tx_समय;
	क्रमागत अणु
		TX_TSPEC_ACTION_NONE = 0,
		TX_TSPEC_ACTION_DOWNGRADE,
		TX_TSPEC_ACTION_STOP_DOWNGRADE,
	पूर्ण action;
	bool करोwngraded;
पूर्ण;

DECLARE_EWMA(beacon_संकेत, 4, 4)

काष्ठा ieee80211_अगर_managed अणु
	काष्ठा समयr_list समयr;
	काष्ठा समयr_list conn_mon_समयr;
	काष्ठा समयr_list bcn_mon_समयr;
	काष्ठा समयr_list chचयन_समयr;
	काष्ठा work_काष्ठा monitor_work;
	काष्ठा work_काष्ठा chचयन_work;
	काष्ठा work_काष्ठा beacon_connection_loss_work;
	काष्ठा work_काष्ठा csa_connection_drop_work;

	अचिन्हित दीर्घ beacon_समयout;
	अचिन्हित दीर्घ probe_समयout;
	पूर्णांक probe_send_count;
	bool nullfunc_failed;
	u8 connection_loss:1,
	   driver_disconnect:1,
	   reconnect:1;

	काष्ठा cfg80211_bss *associated;
	काष्ठा ieee80211_mgd_auth_data *auth_data;
	काष्ठा ieee80211_mgd_assoc_data *assoc_data;

	u8 bssid[ETH_ALEN] __aligned(2);

	bool घातersave; /* घातersave requested क्रम this अगरace */
	bool broken_ap; /* AP is broken -- turn off घातersave */
	bool have_beacon;
	u8 dtim_period;
	क्रमागत ieee80211_smps_mode req_smps, /* requested smps mode */
				 driver_smps_mode; /* smps mode request */

	काष्ठा work_काष्ठा request_smps_work;

	अचिन्हित पूर्णांक flags;

	bool csa_रुकोing_bcn;
	bool csa_ignored_same_chan;

	bool beacon_crc_valid;
	u32 beacon_crc;

	bool status_acked;
	bool status_received;
	__le16 status_fc;

	क्रमागत अणु
		IEEE80211_MFP_DISABLED,
		IEEE80211_MFP_OPTIONAL,
		IEEE80211_MFP_REQUIRED
	पूर्ण mfp; /* management frame protection */

	/*
	 * Biपंचांगask of enabled u-apsd queues,
	 * IEEE80211_WMM_IE_STA_QOSINFO_AC_BE & co. Needs a new association
	 * to take effect.
	 */
	अचिन्हित पूर्णांक uapsd_queues;

	/*
	 * Maximum number of buffered frames AP can deliver during a
	 * service period, IEEE80211_WMM_IE_STA_QOSINFO_SP_ALL or similar.
	 * Needs a new association to take effect.
	 */
	अचिन्हित पूर्णांक uapsd_max_sp_len;

	पूर्णांक wmm_last_param_set;
	पूर्णांक mu_edca_last_param_set;

	u8 use_4addr;

	s16 p2p_noa_index;

	काष्ठा ewma_beacon_संकेत ave_beacon_संकेत;

	/*
	 * Number of Beacon frames used in ave_beacon_संकेत. This can be used
	 * to aव्योम generating less reliable cqm events that would be based
	 * only on couple of received frames.
	 */
	अचिन्हित पूर्णांक count_beacon_संकेत;

	/* Number of बार beacon loss was invoked. */
	अचिन्हित पूर्णांक beacon_loss_count;

	/*
	 * Last Beacon frame संकेत strength average (ave_beacon_संकेत / 16)
	 * that triggered a cqm event. 0 indicates that no event has been
	 * generated क्रम the current association.
	 */
	पूर्णांक last_cqm_event_संकेत;

	/*
	 * State variables क्रम keeping track of RSSI of the AP currently
	 * connected to and inक्रमming driver when RSSI has gone
	 * below/above a certain threshold.
	 */
	पूर्णांक rssi_min_thold, rssi_max_thold;
	पूर्णांक last_ave_beacon_संकेत;

	काष्ठा ieee80211_ht_cap ht_capa; /* configured ht-cap over-rides */
	काष्ठा ieee80211_ht_cap ht_capa_mask; /* Valid parts of ht_capa */
	काष्ठा ieee80211_vht_cap vht_capa; /* configured VHT overrides */
	काष्ठा ieee80211_vht_cap vht_capa_mask; /* Valid parts of vht_capa */
	काष्ठा ieee80211_s1g_cap s1g_capa; /* configured S1G overrides */
	काष्ठा ieee80211_s1g_cap s1g_capa_mask; /* valid s1g_capa bits */

	/* TDLS support */
	u8 tdls_peer[ETH_ALEN] __aligned(2);
	काष्ठा delayed_work tdls_peer_del_work;
	काष्ठा sk_buff *orig_tearकरोwn_skb; /* The original tearकरोwn skb */
	काष्ठा sk_buff *tearकरोwn_skb; /* A copy to send through the AP */
	spinlock_t tearकरोwn_lock; /* To lock changing tearकरोwn_skb */
	bool tdls_chan_चयन_prohibited;
	bool tdls_wider_bw_prohibited;

	/* WMM-AC TSPEC support */
	काष्ठा ieee80211_sta_tx_tspec tx_tspec[IEEE80211_NUM_ACS];
	/* Use a separate work काष्ठा so that we can करो something here
	 * जबतक the sdata->work is flushing the queues, क्रम example.
	 * otherwise, in scenarios where we hardly get any traffic out
	 * on the BE queue, but there's a lot of VO traffic, we might
	 * get stuck in a करोwngraded situation and flush takes क्रमever.
	 */
	काष्ठा delayed_work tx_tspec_wk;

	/* Inक्रमmation elements from the last transmitted (Re)Association
	 * Request frame.
	 */
	u8 *assoc_req_ies;
	माप_प्रकार assoc_req_ies_len;
पूर्ण;

काष्ठा ieee80211_अगर_ibss अणु
	काष्ठा समयr_list समयr;
	काष्ठा work_काष्ठा csa_connection_drop_work;

	अचिन्हित दीर्घ last_scan_completed;

	u32 basic_rates;

	bool fixed_bssid;
	bool fixed_channel;
	bool privacy;

	bool control_port;
	bool userspace_handles_dfs;

	u8 bssid[ETH_ALEN] __aligned(2);
	u8 ssid[IEEE80211_MAX_SSID_LEN];
	u8 ssid_len, ie_len;
	u8 *ie;
	काष्ठा cfg80211_chan_def chandef;

	अचिन्हित दीर्घ ibss_join_req;
	/* probe response/beacon क्रम IBSS */
	काष्ठा beacon_data __rcu *presp;

	काष्ठा ieee80211_ht_cap ht_capa; /* configured ht-cap over-rides */
	काष्ठा ieee80211_ht_cap ht_capa_mask; /* Valid parts of ht_capa */

	spinlock_t incomplete_lock;
	काष्ठा list_head incomplete_stations;

	क्रमागत अणु
		IEEE80211_IBSS_MLME_SEARCH,
		IEEE80211_IBSS_MLME_JOINED,
	पूर्ण state;
पूर्ण;

/**
 * काष्ठा ieee80211_अगर_ocb - OCB mode state
 *
 * @housekeeping_समयr: समयr क्रम periodic invocation of a housekeeping task
 * @wrkq_flags: OCB deferred task action
 * @incomplete_lock: delayed STA insertion lock
 * @incomplete_stations: list of STAs रुकोing क्रम delayed insertion
 * @joined: indication अगर the पूर्णांकerface is connected to an OCB network
 */
काष्ठा ieee80211_अगर_ocb अणु
	काष्ठा समयr_list housekeeping_समयr;
	अचिन्हित दीर्घ wrkq_flags;

	spinlock_t incomplete_lock;
	काष्ठा list_head incomplete_stations;

	bool joined;
पूर्ण;

/**
 * काष्ठा ieee80211_mesh_sync_ops - Extensible synchronization framework पूर्णांकerface
 *
 * these declarations define the पूर्णांकerface, which enables
 * venकरोr-specअगरic mesh synchronization
 *
 */
काष्ठा ieee802_11_elems;
काष्ठा ieee80211_mesh_sync_ops अणु
	व्योम (*rx_bcn_presp)(काष्ठा ieee80211_sub_अगर_data *sdata,
			     u16 stype,
			     काष्ठा ieee80211_mgmt *mgmt,
			     काष्ठा ieee802_11_elems *elems,
			     काष्ठा ieee80211_rx_status *rx_status);

	/* should be called with beacon_data under RCU पढ़ो lock */
	व्योम (*adjust_tsf)(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा beacon_data *beacon);
	/* add other framework functions here */
पूर्ण;

काष्ठा mesh_csa_settings अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा cfg80211_csa_settings settings;
पूर्ण;

काष्ठा ieee80211_अगर_mesh अणु
	काष्ठा समयr_list housekeeping_समयr;
	काष्ठा समयr_list mesh_path_समयr;
	काष्ठा समयr_list mesh_path_root_समयr;

	अचिन्हित दीर्घ wrkq_flags;
	अचिन्हित दीर्घ mbss_changed;

	bool userspace_handles_dfs;

	u8 mesh_id[IEEE80211_MAX_MESH_ID_LEN];
	माप_प्रकार mesh_id_len;
	/* Active Path Selection Protocol Identअगरier */
	u8 mesh_pp_id;
	/* Active Path Selection Metric Identअगरier */
	u8 mesh_pm_id;
	/* Congestion Control Mode Identअगरier */
	u8 mesh_cc_id;
	/* Synchronization Protocol Identअगरier */
	u8 mesh_sp_id;
	/* Authentication Protocol Identअगरier */
	u8 mesh_auth_id;
	/* Local mesh Sequence Number */
	u32 sn;
	/* Last used PREQ ID */
	u32 preq_id;
	atomic_t mpaths;
	/* Timestamp of last SN update */
	अचिन्हित दीर्घ last_sn_update;
	/* Time when it's ok to send next PERR */
	अचिन्हित दीर्घ next_perr;
	/* Timestamp of last PREQ sent */
	अचिन्हित दीर्घ last_preq;
	काष्ठा mesh_rmc *rmc;
	spinlock_t mesh_preq_queue_lock;
	काष्ठा mesh_preq_queue preq_queue;
	पूर्णांक preq_queue_len;
	काष्ठा mesh_stats mshstats;
	काष्ठा mesh_config mshcfg;
	atomic_t estab_plinks;
	u32 mesh_seqnum;
	bool accepting_plinks;
	पूर्णांक num_gates;
	काष्ठा beacon_data __rcu *beacon;
	स्थिर u8 *ie;
	u8 ie_len;
	क्रमागत अणु
		IEEE80211_MESH_SEC_NONE = 0x0,
		IEEE80211_MESH_SEC_AUTHED = 0x1,
		IEEE80211_MESH_SEC_SECURED = 0x2,
	पूर्ण security;
	bool user_mpm;
	/* Extensible Synchronization Framework */
	स्थिर काष्ठा ieee80211_mesh_sync_ops *sync_ops;
	s64 sync_offset_घड़ीdrअगरt_max;
	spinlock_t sync_offset_lock;
	/* mesh घातer save */
	क्रमागत nl80211_mesh_घातer_mode nonpeer_pm;
	पूर्णांक ps_peers_light_sleep;
	पूर्णांक ps_peers_deep_sleep;
	काष्ठा ps_data ps;
	/* Channel Switching Support */
	काष्ठा mesh_csa_settings __rcu *csa;
	क्रमागत अणु
		IEEE80211_MESH_CSA_ROLE_NONE,
		IEEE80211_MESH_CSA_ROLE_INIT,
		IEEE80211_MESH_CSA_ROLE_REPEATER,
	पूर्ण csa_role;
	u8 chsw_ttl;
	u16 pre_value;

	/* offset from skb->data जबतक building IE */
	पूर्णांक meshconf_offset;

	काष्ठा mesh_table *mesh_paths;
	काष्ठा mesh_table *mpp_paths; /* Store paths क्रम MPP&MAP */
	पूर्णांक mesh_paths_generation;
	पूर्णांक mpp_paths_generation;
पूर्ण;

#अगर_घोषित CONFIG_MAC80211_MESH
#घोषणा IEEE80211_IFSTA_MESH_CTR_INC(msh, name)	\
	करो अणु (msh)->mshstats.name++; पूर्ण जबतक (0)
#अन्यथा
#घोषणा IEEE80211_IFSTA_MESH_CTR_INC(msh, name) \
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/**
 * क्रमागत ieee80211_sub_अगर_data_flags - भव पूर्णांकerface flags
 *
 * @IEEE80211_SDATA_ALLMULTI: पूर्णांकerface wants all multicast packets
 * @IEEE80211_SDATA_OPERATING_GMODE: operating in G-only mode
 * @IEEE80211_SDATA_DONT_BRIDGE_PACKETS: bridge packets between
 *	associated stations and deliver multicast frames both
 *	back to wireless media and to the local net stack.
 * @IEEE80211_SDATA_DISCONNECT_RESUME: Disconnect after resume.
 * @IEEE80211_SDATA_IN_DRIVER: indicates पूर्णांकerface was added to driver
 */
क्रमागत ieee80211_sub_अगर_data_flags अणु
	IEEE80211_SDATA_ALLMULTI		= BIT(0),
	IEEE80211_SDATA_OPERATING_GMODE		= BIT(2),
	IEEE80211_SDATA_DONT_BRIDGE_PACKETS	= BIT(3),
	IEEE80211_SDATA_DISCONNECT_RESUME	= BIT(4),
	IEEE80211_SDATA_IN_DRIVER		= BIT(5),
पूर्ण;

/**
 * क्रमागत ieee80211_sdata_state_bits - भव पूर्णांकerface state bits
 * @SDATA_STATE_RUNNING: भव पूर्णांकerface is up & running; this
 *	mirrors netअगर_running() but is separate क्रम पूर्णांकerface type
 *	change handling जबतक the पूर्णांकerface is up
 * @SDATA_STATE_OFFCHANNEL: This पूर्णांकerface is currently in offchannel
 *	mode, so queues are stopped
 * @SDATA_STATE_OFFCHANNEL_BEACON_STOPPED: Beaconing was stopped due
 *	to offchannel, reset when offchannel वापसs
 */
क्रमागत ieee80211_sdata_state_bits अणु
	SDATA_STATE_RUNNING,
	SDATA_STATE_OFFCHANNEL,
	SDATA_STATE_OFFCHANNEL_BEACON_STOPPED,
पूर्ण;

/**
 * क्रमागत ieee80211_chanctx_mode - channel context configuration mode
 *
 * @IEEE80211_CHANCTX_SHARED: channel context may be used by
 *	multiple पूर्णांकerfaces
 * @IEEE80211_CHANCTX_EXCLUSIVE: channel context can be used
 *	only by a single पूर्णांकerface. This can be used क्रम example क्रम
 *	non-fixed channel IBSS.
 */
क्रमागत ieee80211_chanctx_mode अणु
	IEEE80211_CHANCTX_SHARED,
	IEEE80211_CHANCTX_EXCLUSIVE
पूर्ण;

/**
 * क्रमागत ieee80211_chanctx_replace_state - channel context replacement state
 *
 * This is used क्रम channel context in-place reservations that require channel
 * context चयन/swap.
 *
 * @IEEE80211_CHANCTX_REPLACE_NONE: no replacement is taking place
 * @IEEE80211_CHANCTX_WILL_BE_REPLACED: this channel context will be replaced
 *	by a (not yet रेजिस्टरed) channel context poपूर्णांकed by %replace_ctx.
 * @IEEE80211_CHANCTX_REPLACES_OTHER: this (not yet रेजिस्टरed) channel context
 *	replaces an existing channel context poपूर्णांकed to by %replace_ctx.
 */
क्रमागत ieee80211_chanctx_replace_state अणु
	IEEE80211_CHANCTX_REPLACE_NONE,
	IEEE80211_CHANCTX_WILL_BE_REPLACED,
	IEEE80211_CHANCTX_REPLACES_OTHER,
पूर्ण;

काष्ठा ieee80211_chanctx अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu_head;

	काष्ठा list_head asचिन्हित_vअगरs;
	काष्ठा list_head reserved_vअगरs;

	क्रमागत ieee80211_chanctx_replace_state replace_state;
	काष्ठा ieee80211_chanctx *replace_ctx;

	क्रमागत ieee80211_chanctx_mode mode;
	bool driver_present;

	काष्ठा ieee80211_chanctx_conf conf;
पूर्ण;

काष्ठा mac80211_qos_map अणु
	काष्ठा cfg80211_qos_map qos_map;
	काष्ठा rcu_head rcu_head;
पूर्ण;

क्रमागत txq_info_flags अणु
	IEEE80211_TXQ_STOP,
	IEEE80211_TXQ_AMPDU,
	IEEE80211_TXQ_NO_AMSDU,
	IEEE80211_TXQ_STOP_NETIF_TX,
पूर्ण;

/**
 * काष्ठा txq_info - per tid queue
 *
 * @tin: contains packets split पूर्णांकo multiple flows
 * @def_flow: used as a fallback flow when a packet destined to @tin hashes to
 *	a fq_flow which is alपढ़ोy owned by a dअगरferent tin
 * @def_cvars: codel vars क्रम @def_flow
 * @frags: used to keep fragments created after dequeue
 * @schedule_order: used with ieee80211_local->active_txqs
 * @schedule_round: counter to prevent infinite loops on TXQ scheduling
 */
काष्ठा txq_info अणु
	काष्ठा fq_tin tin;
	काष्ठा codel_vars def_cvars;
	काष्ठा codel_stats cstats;
	काष्ठा sk_buff_head frags;
	काष्ठा list_head schedule_order;
	u16 schedule_round;
	अचिन्हित दीर्घ flags;

	/* keep last! */
	काष्ठा ieee80211_txq txq;
पूर्ण;

काष्ठा ieee80211_अगर_mntr अणु
	u32 flags;
	u8 mu_follow_addr[ETH_ALEN] __aligned(2);

	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा ieee80211_अगर_nan - न_अंक state
 *
 * @conf: current न_अंक configuration
 * @func_ids: a biपंचांगap of available instance_id's
 */
काष्ठा ieee80211_अगर_nan अणु
	काष्ठा cfg80211_nan_conf conf;

	/* protects function_inst_ids */
	spinlock_t func_lock;
	काष्ठा idr function_inst_ids;
पूर्ण;

काष्ठा ieee80211_sub_अगर_data अणु
	काष्ठा list_head list;

	काष्ठा wireless_dev wdev;

	/* keys */
	काष्ठा list_head key_list;

	/* count क्रम keys needing tailroom space allocation */
	पूर्णांक crypto_tx_tailroom_needed_cnt;
	पूर्णांक crypto_tx_tailroom_pending_dec;
	काष्ठा delayed_work dec_tailroom_needed_wk;

	काष्ठा net_device *dev;
	काष्ठा ieee80211_local *local;

	अचिन्हित पूर्णांक flags;

	अचिन्हित दीर्घ state;

	अक्षर name[IFNAMSIZ];

	काष्ठा ieee80211_fragment_cache frags;

	/* TID biपंचांगap क्रम NoAck policy */
	u16 noack_map;

	/* bit field of ACM bits (BIT(802.1D tag)) */
	u8 wmm_acm;

	काष्ठा ieee80211_key __rcu *keys[NUM_DEFAULT_KEYS +
					 NUM_DEFAULT_MGMT_KEYS +
					 NUM_DEFAULT_BEACON_KEYS];
	काष्ठा ieee80211_key __rcu *शेष_unicast_key;
	काष्ठा ieee80211_key __rcu *शेष_multicast_key;
	काष्ठा ieee80211_key __rcu *शेष_mgmt_key;
	काष्ठा ieee80211_key __rcu *शेष_beacon_key;

	u16 sequence_number;
	__be16 control_port_protocol;
	bool control_port_no_encrypt;
	bool control_port_no_preauth;
	bool control_port_over_nl80211;
	पूर्णांक encrypt_headroom;

	atomic_t num_tx_queued;
	काष्ठा ieee80211_tx_queue_params tx_conf[IEEE80211_NUM_ACS];
	काष्ठा mac80211_qos_map __rcu *qos_map;

	काष्ठा work_काष्ठा csa_finalize_work;
	bool csa_block_tx; /* ग_लिखो-रक्षित by sdata_lock and local->mtx */
	काष्ठा cfg80211_chan_def csa_chandef;

	काष्ठा list_head asचिन्हित_chanctx_list; /* रक्षित by chanctx_mtx */
	काष्ठा list_head reserved_chanctx_list; /* रक्षित by chanctx_mtx */

	/* context reservation -- रक्षित with chanctx_mtx */
	काष्ठा ieee80211_chanctx *reserved_chanctx;
	काष्ठा cfg80211_chan_def reserved_chandef;
	bool reserved_radar_required;
	bool reserved_पढ़ोy;

	/* used to reconfigure hardware SM PS */
	काष्ठा work_काष्ठा recalc_smps;

	काष्ठा work_काष्ठा work;
	काष्ठा sk_buff_head skb_queue;

	u8 needed_rx_chains;
	क्रमागत ieee80211_smps_mode smps_mode;

	पूर्णांक user_घातer_level; /* in dBm */
	पूर्णांक ap_घातer_level; /* in dBm */

	bool radar_required;
	काष्ठा delayed_work dfs_cac_समयr_work;

	/*
	 * AP this beदीर्घs to: self in AP mode and
	 * corresponding AP in VLAN mode, शून्य क्रम
	 * all others (might be needed later in IBSS)
	 */
	काष्ठा ieee80211_अगर_ap *bss;

	/* biपंचांगap of allowed (non-MCS) rate indexes क्रम rate control */
	u32 rc_rateidx_mask[NUM_NL80211_BANDS];

	bool rc_has_mcs_mask[NUM_NL80211_BANDS];
	u8  rc_rateidx_mcs_mask[NUM_NL80211_BANDS][IEEE80211_HT_MCS_MASK_LEN];

	bool rc_has_vht_mcs_mask[NUM_NL80211_BANDS];
	u16 rc_rateidx_vht_mcs_mask[NUM_NL80211_BANDS][NL80211_VHT_NSS_MAX];

	/* Beacon frame (non-MCS) rate (as a biपंचांगap) */
	u32 beacon_rateidx_mask[NUM_NL80211_BANDS];
	bool beacon_rate_set;

	जोड़ अणु
		काष्ठा ieee80211_अगर_ap ap;
		काष्ठा ieee80211_अगर_vlan vlan;
		काष्ठा ieee80211_अगर_managed mgd;
		काष्ठा ieee80211_अगर_ibss ibss;
		काष्ठा ieee80211_अगर_mesh mesh;
		काष्ठा ieee80211_अगर_ocb ocb;
		काष्ठा ieee80211_अगर_mntr mntr;
		काष्ठा ieee80211_अगर_nan nan;
	पूर्ण u;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	काष्ठा अणु
		काष्ठा dentry *subdir_stations;
		काष्ठा dentry *शेष_unicast_key;
		काष्ठा dentry *शेष_multicast_key;
		काष्ठा dentry *शेष_mgmt_key;
		काष्ठा dentry *शेष_beacon_key;
	पूर्ण debugfs;
#पूर्ण_अगर

	/* must be last, dynamically sized area in this! */
	काष्ठा ieee80211_vअगर vअगर;
पूर्ण;

अटल अंतरभूत
काष्ठा ieee80211_sub_अगर_data *vअगर_to_sdata(काष्ठा ieee80211_vअगर *p)
अणु
	वापस container_of(p, काष्ठा ieee80211_sub_अगर_data, vअगर);
पूर्ण

अटल अंतरभूत व्योम sdata_lock(काष्ठा ieee80211_sub_अगर_data *sdata)
	__acquires(&sdata->wdev.mtx)
अणु
	mutex_lock(&sdata->wdev.mtx);
	__acquire(&sdata->wdev.mtx);
पूर्ण

अटल अंतरभूत व्योम sdata_unlock(काष्ठा ieee80211_sub_अगर_data *sdata)
	__releases(&sdata->wdev.mtx)
अणु
	mutex_unlock(&sdata->wdev.mtx);
	__release(&sdata->wdev.mtx);
पूर्ण

#घोषणा sdata_dereference(p, sdata) \
	rcu_dereference_रक्षित(p, lockdep_is_held(&sdata->wdev.mtx))

अटल अंतरभूत व्योम
sdata_निश्चित_lock(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	lockdep_निश्चित_held(&sdata->wdev.mtx);
पूर्ण

अटल अंतरभूत पूर्णांक
ieee80211_chandef_get_shअगरt(काष्ठा cfg80211_chan_def *chandef)
अणु
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_5:
		वापस 2;
	हाल NL80211_CHAN_WIDTH_10:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
ieee80211_vअगर_get_shअगरt(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	पूर्णांक shअगरt = 0;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);
	अगर (chanctx_conf)
		shअगरt = ieee80211_chandef_get_shअगरt(&chanctx_conf->def);
	rcu_पढ़ो_unlock();

	वापस shअगरt;
पूर्ण

क्रमागत अणु
	IEEE80211_RX_MSG	= 1,
	IEEE80211_TX_STATUS_MSG	= 2,
पूर्ण;

क्रमागत queue_stop_reason अणु
	IEEE80211_QUEUE_STOP_REASON_DRIVER,
	IEEE80211_QUEUE_STOP_REASON_PS,
	IEEE80211_QUEUE_STOP_REASON_CSA,
	IEEE80211_QUEUE_STOP_REASON_AGGREGATION,
	IEEE80211_QUEUE_STOP_REASON_SUSPEND,
	IEEE80211_QUEUE_STOP_REASON_SKB_ADD,
	IEEE80211_QUEUE_STOP_REASON_OFFCHANNEL,
	IEEE80211_QUEUE_STOP_REASON_FLUSH,
	IEEE80211_QUEUE_STOP_REASON_TDLS_TEARDOWN,
	IEEE80211_QUEUE_STOP_REASON_RESERVE_TID,
	IEEE80211_QUEUE_STOP_REASON_IFTYPE_CHANGE,

	IEEE80211_QUEUE_STOP_REASONS,
पूर्ण;

#अगर_घोषित CONFIG_MAC80211_LEDS
काष्ठा tpt_led_trigger अणु
	अक्षर name[32];
	स्थिर काष्ठा ieee80211_tpt_blink *blink_table;
	अचिन्हित पूर्णांक blink_table_len;
	काष्ठा समयr_list समयr;
	काष्ठा ieee80211_local *local;
	अचिन्हित दीर्घ prev_traffic;
	अचिन्हित दीर्घ tx_bytes, rx_bytes;
	अचिन्हित पूर्णांक active, want;
	bool running;
पूर्ण;
#पूर्ण_अगर

/**
 * mac80211 scan flags - currently active scan mode
 *
 * @SCAN_SW_SCANNING: We're currently in the process of scanning but may as
 *	well be on the operating channel
 * @SCAN_HW_SCANNING: The hardware is scanning क्रम us, we have no way to
 *	determine अगर we are on the operating channel or not
 * @SCAN_ONCHANNEL_SCANNING:  Do a software scan on only the current operating
 *	channel. This should not पूर्णांकerrupt normal traffic.
 * @SCAN_COMPLETED: Set क्रम our scan work function when the driver reported
 *	that the scan completed.
 * @SCAN_ABORTED: Set क्रम our scan work function when the driver reported
 *	a scan complete क्रम an पातed scan.
 * @SCAN_HW_CANCELLED: Set क्रम our scan work function when the scan is being
 *	cancelled.
 */
क्रमागत अणु
	SCAN_SW_SCANNING,
	SCAN_HW_SCANNING,
	SCAN_ONCHANNEL_SCANNING,
	SCAN_COMPLETED,
	SCAN_ABORTED,
	SCAN_HW_CANCELLED,
पूर्ण;

/**
 * क्रमागत mac80211_scan_state - scan state machine states
 *
 * @SCAN_DECISION: Main entry poपूर्णांक to the scan state machine, this state
 *	determines अगर we should keep on scanning or चयन back to the
 *	operating channel
 * @SCAN_SET_CHANNEL: Set the next channel to be scanned
 * @SCAN_SEND_PROBE: Send probe requests and रुको क्रम probe responses
 * @SCAN_SUSPEND: Suspend the scan and go back to operating channel to
 *	send out data
 * @SCAN_RESUME: Resume the scan and scan the next channel
 * @SCAN_ABORT: Abort the scan and go back to operating channel
 */
क्रमागत mac80211_scan_state अणु
	SCAN_DECISION,
	SCAN_SET_CHANNEL,
	SCAN_SEND_PROBE,
	SCAN_SUSPEND,
	SCAN_RESUME,
	SCAN_ABORT,
पूर्ण;

DECLARE_STATIC_KEY_FALSE(aql_disable);

काष्ठा ieee80211_local अणु
	/* embed the driver visible part.
	 * करोn't cast (use the अटल अंतरभूतs below), but we keep
	 * it first anyway so they become a no-op */
	काष्ठा ieee80211_hw hw;

	काष्ठा fq fq;
	काष्ठा codel_vars *cvars;
	काष्ठा codel_params cparams;

	/* protects active_txqs and txqi->schedule_order */
	spinlock_t active_txq_lock[IEEE80211_NUM_ACS];
	काष्ठा list_head active_txqs[IEEE80211_NUM_ACS];
	u16 schedule_round[IEEE80211_NUM_ACS];

	u16 airसमय_flags;
	u32 aql_txq_limit_low[IEEE80211_NUM_ACS];
	u32 aql_txq_limit_high[IEEE80211_NUM_ACS];
	u32 aql_threshold;
	atomic_t aql_total_pending_airसमय;

	स्थिर काष्ठा ieee80211_ops *ops;

	/*
	 * निजी workqueue to mac80211. mac80211 makes this accessible
	 * via ieee80211_queue_work()
	 */
	काष्ठा workqueue_काष्ठा *workqueue;

	अचिन्हित दीर्घ queue_stop_reasons[IEEE80211_MAX_QUEUES];
	पूर्णांक q_stop_reasons[IEEE80211_MAX_QUEUES][IEEE80211_QUEUE_STOP_REASONS];
	/* also used to protect ampdu_ac_queue and amdpu_ac_stop_refcnt */
	spinlock_t queue_stop_reason_lock;

	पूर्णांक खोलो_count;
	पूर्णांक monitors, cooked_mntrs;
	/* number of पूर्णांकerfaces with corresponding FIF_ flags */
	पूर्णांक fअगर_fcsfail, fअगर_plcpfail, fअगर_control, fअगर_other_bss, fअगर_pspoll,
	    fअगर_probe_req;
	bool probe_req_reg;
	bool rx_mcast_action_reg;
	अचिन्हित पूर्णांक filter_flags; /* FIF_* */

	bool wiphy_ciphers_allocated;

	bool use_chanctx;

	/* protects the aggregated multicast list and filter calls */
	spinlock_t filter_lock;

	/* used क्रम uploading changed mc list */
	काष्ठा work_काष्ठा reconfig_filter;

	/* aggregated multicast list */
	काष्ठा netdev_hw_addr_list mc_list;

	bool tim_in_locked_section; /* see ieee80211_beacon_get() */

	/*
	 * suspended is true अगर we finished all the suspend _and_ we have
	 * not yet come up from resume. This is to be used by mac80211
	 * to ensure driver sanity during suspend and mac80211's own
	 * sanity. It can eventually be used क्रम WoW as well.
	 */
	bool suspended;

	/*
	 * Resuming is true जबतक suspended, but when we're reprogramming the
	 * hardware -- at that समय it's allowed to use ieee80211_queue_work()
	 * again even though some other parts of the stack are still suspended
	 * and we still drop received frames to aव्योम waking the stack.
	 */
	bool resuming;

	/*
	 * quiescing is true during the suspend process _only_ to
	 * ease समयr cancelling etc.
	 */
	bool quiescing;

	/* device is started */
	bool started;

	/* device is during a HW reconfig */
	bool in_reconfig;

	/* wowlan is enabled -- करोn't reconfig on resume */
	bool wowlan;

	काष्ठा work_काष्ठा radar_detected_work;

	/* number of RX chains the hardware has */
	u8 rx_chains;

	/* biपंचांगap of which sbands were copied */
	u8 sband_allocated;

	पूर्णांक tx_headroom; /* required headroom क्रम hardware/radiotap */

	/* Tasklet and skb queue to process calls from IRQ mode. All frames
	 * added to skb_queue will be processed, but frames in
	 * skb_queue_unreliable may be dropped अगर the total length of these
	 * queues increases over the limit. */
#घोषणा IEEE80211_IRQSAFE_QUEUE_LIMIT 128
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा sk_buff_head skb_queue;
	काष्ठा sk_buff_head skb_queue_unreliable;

	spinlock_t rx_path_lock;

	/* Station data */
	/*
	 * The mutex only protects the list, hash table and
	 * counter, पढ़ोs are करोne with RCU.
	 */
	काष्ठा mutex sta_mtx;
	spinlock_t tim_lock;
	अचिन्हित दीर्घ num_sta;
	काष्ठा list_head sta_list;
	काष्ठा rhltable sta_hash;
	काष्ठा समयr_list sta_cleanup;
	पूर्णांक sta_generation;

	काष्ठा sk_buff_head pending[IEEE80211_MAX_QUEUES];
	काष्ठा tasklet_काष्ठा tx_pending_tasklet;
	काष्ठा tasklet_काष्ठा wake_txqs_tasklet;

	atomic_t agg_queue_stop[IEEE80211_MAX_QUEUES];

	/* number of पूर्णांकerfaces with allmulti RX */
	atomic_t अगरf_allmultis;

	काष्ठा rate_control_ref *rate_ctrl;

	काष्ठा arc4_ctx wep_tx_ctx;
	काष्ठा arc4_ctx wep_rx_ctx;
	u32 wep_iv;

	/* see अगरace.c */
	काष्ठा list_head पूर्णांकerfaces;
	काष्ठा list_head mon_list; /* only that are IFF_UP && !cooked */
	काष्ठा mutex अगरlist_mtx;

	/*
	 * Key mutex, protects sdata's key_list and sta_info's
	 * key poपूर्णांकers and ptk_idx (ग_लिखो access, they're RCU.)
	 */
	काष्ठा mutex key_mtx;

	/* mutex क्रम scan and work locking */
	काष्ठा mutex mtx;

	/* Scanning and BSS list */
	अचिन्हित दीर्घ scanning;
	काष्ठा cfg80211_ssid scan_ssid;
	काष्ठा cfg80211_scan_request *पूर्णांक_scan_req;
	काष्ठा cfg80211_scan_request __rcu *scan_req;
	काष्ठा ieee80211_scan_request *hw_scan_req;
	काष्ठा cfg80211_chan_def scan_chandef;
	क्रमागत nl80211_band hw_scan_band;
	पूर्णांक scan_channel_idx;
	पूर्णांक scan_ies_len;
	पूर्णांक hw_scan_ies_bufsize;
	काष्ठा cfg80211_scan_info scan_info;

	काष्ठा work_काष्ठा sched_scan_stopped_work;
	काष्ठा ieee80211_sub_अगर_data __rcu *sched_scan_sdata;
	काष्ठा cfg80211_sched_scan_request __rcu *sched_scan_req;
	u8 scan_addr[ETH_ALEN];

	अचिन्हित दीर्घ leave_oper_channel_समय;
	क्रमागत mac80211_scan_state next_scan_state;
	काष्ठा delayed_work scan_work;
	काष्ठा ieee80211_sub_अगर_data __rcu *scan_sdata;
	/* For backward compatibility only -- करो not use */
	काष्ठा cfg80211_chan_def _oper_chandef;

	/* Temporary reमुख्य-on-channel क्रम off-channel operations */
	काष्ठा ieee80211_channel *पंचांगp_channel;

	/* channel contexts */
	काष्ठा list_head chanctx_list;
	काष्ठा mutex chanctx_mtx;

#अगर_घोषित CONFIG_MAC80211_LEDS
	काष्ठा led_trigger tx_led, rx_led, assoc_led, radio_led;
	काष्ठा led_trigger tpt_led;
	atomic_t tx_led_active, rx_led_active, assoc_led_active;
	atomic_t radio_led_active, tpt_led_active;
	काष्ठा tpt_led_trigger *tpt_led_trigger;
#पूर्ण_अगर

#अगर_घोषित CONFIG_MAC80211_DEBUG_COUNTERS
	/* SNMP counters */
	/* करोt11CountersTable */
	u32 करोt11TransmittedFragmentCount;
	u32 करोt11MulticastTransmittedFrameCount;
	u32 करोt11FailedCount;
	u32 करोt11RetryCount;
	u32 करोt11MultipleRetryCount;
	u32 करोt11FrameDuplicateCount;
	u32 करोt11ReceivedFragmentCount;
	u32 करोt11MulticastReceivedFrameCount;
	u32 करोt11TransmittedFrameCount;

	/* TX/RX handler statistics */
	अचिन्हित पूर्णांक tx_handlers_drop;
	अचिन्हित पूर्णांक tx_handlers_queued;
	अचिन्हित पूर्णांक tx_handlers_drop_wep;
	अचिन्हित पूर्णांक tx_handlers_drop_not_assoc;
	अचिन्हित पूर्णांक tx_handlers_drop_unauth_port;
	अचिन्हित पूर्णांक rx_handlers_drop;
	अचिन्हित पूर्णांक rx_handlers_queued;
	अचिन्हित पूर्णांक rx_handlers_drop_nullfunc;
	अचिन्हित पूर्णांक rx_handlers_drop_defrag;
	अचिन्हित पूर्णांक tx_expand_skb_head;
	अचिन्हित पूर्णांक tx_expand_skb_head_cloned;
	अचिन्हित पूर्णांक rx_expand_skb_head_defrag;
	अचिन्हित पूर्णांक rx_handlers_fragments;
	अचिन्हित पूर्णांक tx_status_drop;
#घोषणा I802_DEBUG_INC(c) (c)++
#अन्यथा /* CONFIG_MAC80211_DEBUG_COUNTERS */
#घोषणा I802_DEBUG_INC(c) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_MAC80211_DEBUG_COUNTERS */


	पूर्णांक total_ps_buffered; /* total number of all buffered unicast and
				* multicast packets क्रम घातer saving stations
				*/

	bool pspolling;
	/*
	 * PS can only be enabled when we have exactly one managed
	 * पूर्णांकerface (and monitors) in PS, this then poपूर्णांकs there.
	 */
	काष्ठा ieee80211_sub_अगर_data *ps_sdata;
	काष्ठा work_काष्ठा dynamic_ps_enable_work;
	काष्ठा work_काष्ठा dynamic_ps_disable_work;
	काष्ठा समयr_list dynamic_ps_समयr;
	काष्ठा notअगरier_block अगरa_notअगरier;
	काष्ठा notअगरier_block अगरa6_notअगरier;

	/*
	 * The dynamic ps समयout configured from user space via WEXT -
	 * this will override whatever chosen by mac80211 पूर्णांकernally.
	 */
	पूर्णांक dynamic_ps_क्रमced_समयout;

	पूर्णांक user_घातer_level; /* in dBm, क्रम all पूर्णांकerfaces */

	क्रमागत ieee80211_smps_mode smps_mode;

	काष्ठा work_काष्ठा restart_work;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	काष्ठा local_debugfsdentries अणु
		काष्ठा dentry *rcdir;
		काष्ठा dentry *keys;
	पूर्ण debugfs;
	bool क्रमce_tx_status;
#पूर्ण_अगर

	/*
	 * Reमुख्य-on-channel support
	 */
	काष्ठा delayed_work roc_work;
	काष्ठा list_head roc_list;
	काष्ठा work_काष्ठा hw_roc_start, hw_roc_करोne;
	अचिन्हित दीर्घ hw_roc_start_समय;
	u64 roc_cookie_counter;

	काष्ठा idr ack_status_frames;
	spinlock_t ack_status_lock;

	काष्ठा ieee80211_sub_अगर_data __rcu *p2p_sdata;

	/* भव monitor पूर्णांकerface */
	काष्ठा ieee80211_sub_अगर_data __rcu *monitor_sdata;
	काष्ठा cfg80211_chan_def monitor_chandef;

	/* extended capabilities provided by mac80211 */
	u8 ext_capa[8];

	/* TDLS channel चयन */
	काष्ठा work_काष्ठा tdls_chsw_work;
	काष्ठा sk_buff_head skb_queue_tdls_chsw;
पूर्ण;

अटल अंतरभूत काष्ठा ieee80211_sub_अगर_data *
IEEE80211_DEV_TO_SUB_IF(काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_sub_अगर_data *
IEEE80211_WDEV_TO_SUB_IF(काष्ठा wireless_dev *wdev)
अणु
	वापस container_of(wdev, काष्ठा ieee80211_sub_अगर_data, wdev);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_supported_band *
ieee80211_get_sband(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	क्रमागत nl80211_band band;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);

	अगर (!chanctx_conf) अणु
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण

	band = chanctx_conf->def.chan->band;
	rcu_पढ़ो_unlock();

	वापस local->hw.wiphy->bands[band];
पूर्ण

/* this काष्ठा holds the value parsing from channel चयन IE  */
काष्ठा ieee80211_csa_ie अणु
	काष्ठा cfg80211_chan_def chandef;
	u8 mode;
	u8 count;
	u8 ttl;
	u16 pre_value;
	u16 reason_code;
	u32 max_चयन_समय;
पूर्ण;

/* Parsed Inक्रमmation Elements */
काष्ठा ieee802_11_elems अणु
	स्थिर u8 *ie_start;
	माप_प्रकार total_len;

	/* poपूर्णांकers to IEs */
	स्थिर काष्ठा ieee80211_tdls_lnkie *lnk_id;
	स्थिर काष्ठा ieee80211_ch_चयन_timing *ch_sw_timing;
	स्थिर u8 *ext_capab;
	स्थिर u8 *ssid;
	स्थिर u8 *supp_rates;
	स्थिर u8 *ds_params;
	स्थिर काष्ठा ieee80211_tim_ie *tim;
	स्थिर u8 *challenge;
	स्थिर u8 *rsn;
	स्थिर u8 *rsnx;
	स्थिर u8 *erp_info;
	स्थिर u8 *ext_supp_rates;
	स्थिर u8 *wmm_info;
	स्थिर u8 *wmm_param;
	स्थिर काष्ठा ieee80211_ht_cap *ht_cap_elem;
	स्थिर काष्ठा ieee80211_ht_operation *ht_operation;
	स्थिर काष्ठा ieee80211_vht_cap *vht_cap_elem;
	स्थिर काष्ठा ieee80211_vht_operation *vht_operation;
	स्थिर काष्ठा ieee80211_meshconf_ie *mesh_config;
	स्थिर u8 *he_cap;
	स्थिर काष्ठा ieee80211_he_operation *he_operation;
	स्थिर काष्ठा ieee80211_he_spr *he_spr;
	स्थिर काष्ठा ieee80211_mu_edca_param_set *mu_edca_param_set;
	स्थिर काष्ठा ieee80211_he_6ghz_capa *he_6ghz_capa;
	स्थिर u8 *uora_element;
	स्थिर u8 *mesh_id;
	स्थिर u8 *peering;
	स्थिर __le16 *awake_winकरोw;
	स्थिर u8 *preq;
	स्थिर u8 *prep;
	स्थिर u8 *perr;
	स्थिर काष्ठा ieee80211_rann_ie *rann;
	स्थिर काष्ठा ieee80211_channel_sw_ie *ch_चयन_ie;
	स्थिर काष्ठा ieee80211_ext_chansw_ie *ext_chansw_ie;
	स्थिर काष्ठा ieee80211_wide_bw_chansw_ie *wide_bw_chansw_ie;
	स्थिर u8 *max_channel_चयन_समय;
	स्थिर u8 *country_elem;
	स्थिर u8 *pwr_स्थिरr_elem;
	स्थिर u8 *cisco_dtpc_elem;
	स्थिर काष्ठा ieee80211_समयout_पूर्णांकerval_ie *समयout_पूर्णांक;
	स्थिर u8 *opmode_notअगर;
	स्थिर काष्ठा ieee80211_sec_chan_offs_ie *sec_chan_offs;
	काष्ठा ieee80211_mesh_chansw_params_ie *mesh_chansw_params_ie;
	स्थिर काष्ठा ieee80211_bss_max_idle_period_ie *max_idle_period_ie;
	स्थिर काष्ठा ieee80211_multiple_bssid_configuration *mbssid_config_ie;
	स्थिर काष्ठा ieee80211_bssid_index *bssid_index;
	u8 max_bssid_indicator;
	u8 dtim_count;
	u8 dtim_period;
	स्थिर काष्ठा ieee80211_addba_ext_ie *addba_ext_ie;
	स्थिर काष्ठा ieee80211_s1g_cap *s1g_capab;
	स्थिर काष्ठा ieee80211_s1g_oper_ie *s1g_oper;
	स्थिर काष्ठा ieee80211_s1g_bcn_compat_ie *s1g_bcn_compat;
	स्थिर काष्ठा ieee80211_aid_response_ie *aid_resp;

	/* length of them, respectively */
	u8 ext_capab_len;
	u8 ssid_len;
	u8 supp_rates_len;
	u8 tim_len;
	u8 challenge_len;
	u8 rsn_len;
	u8 rsnx_len;
	u8 ext_supp_rates_len;
	u8 wmm_info_len;
	u8 wmm_param_len;
	u8 he_cap_len;
	u8 mesh_id_len;
	u8 peering_len;
	u8 preq_len;
	u8 prep_len;
	u8 perr_len;
	u8 country_elem_len;
	u8 bssid_index_len;

	/* whether a parse error occurred जबतक retrieving these elements */
	bool parse_error;
पूर्ण;

अटल अंतरभूत काष्ठा ieee80211_local *hw_to_local(
	काष्ठा ieee80211_hw *hw)
अणु
	वापस container_of(hw, काष्ठा ieee80211_local, hw);
पूर्ण

अटल अंतरभूत काष्ठा txq_info *to_txq_info(काष्ठा ieee80211_txq *txq)
अणु
	वापस container_of(txq, काष्ठा txq_info, txq);
पूर्ण

अटल अंतरभूत bool txq_has_queue(काष्ठा ieee80211_txq *txq)
अणु
	काष्ठा txq_info *txqi = to_txq_info(txq);

	वापस !(skb_queue_empty(&txqi->frags) && !txqi->tin.backlog_packets);
पूर्ण

अटल अंतरभूत पूर्णांक ieee80211_bssid_match(स्थिर u8 *raddr, स्थिर u8 *addr)
अणु
	वापस ether_addr_equal(raddr, addr) ||
	       is_broadcast_ether_addr(raddr);
पूर्ण

अटल अंतरभूत bool
ieee80211_have_rx_बारtamp(काष्ठा ieee80211_rx_status *status)
अणु
	WARN_ON_ONCE(status->flag & RX_FLAG_MACTIME_START &&
		     status->flag & RX_FLAG_MACTIME_END);
	वापस !!(status->flag & (RX_FLAG_MACTIME_START | RX_FLAG_MACTIME_END |
				  RX_FLAG_MACTIME_PLCP_START));
पूर्ण

व्योम ieee80211_vअगर_inc_num_mcast(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_vअगर_dec_num_mcast(काष्ठा ieee80211_sub_अगर_data *sdata);

/* This function वापसs the number of multicast stations connected to this
 * पूर्णांकerface. It वापसs -1 अगर that number is not tracked, that is क्रम netdevs
 * not in AP or AP_VLAN mode or when using 4addr.
 */
अटल अंतरभूत पूर्णांक
ieee80211_vअगर_get_num_mcast_अगर(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		वापस atomic_पढ़ो(&sdata->u.ap.num_mcast_sta);
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN && !sdata->u.vlan.sta)
		वापस atomic_पढ़ो(&sdata->u.vlan.num_mcast_sta);
	वापस -1;
पूर्ण

u64 ieee80211_calculate_rx_बारtamp(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_rx_status *status,
				     अचिन्हित पूर्णांक mpdu_len,
				     अचिन्हित पूर्णांक mpdu_offset);
पूर्णांक ieee80211_hw_config(काष्ठा ieee80211_local *local, u32 changed);
व्योम ieee80211_tx_set_रक्षित(काष्ठा ieee80211_tx_data *tx);
व्योम ieee80211_bss_info_change_notअगरy(काष्ठा ieee80211_sub_अगर_data *sdata,
				      u32 changed);
व्योम ieee80211_configure_filter(काष्ठा ieee80211_local *local);
u32 ieee80211_reset_erp_info(काष्ठा ieee80211_sub_अगर_data *sdata);

u64 ieee80211_mgmt_tx_cookie(काष्ठा ieee80211_local *local);
पूर्णांक ieee80211_attach_ack_skb(काष्ठा ieee80211_local *local, काष्ठा sk_buff *skb,
			     u64 *cookie, gfp_t gfp);

व्योम ieee80211_check_fast_rx(काष्ठा sta_info *sta);
व्योम __ieee80211_check_fast_rx_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_check_fast_rx_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_clear_fast_rx(काष्ठा sta_info *sta);

/* STA code */
व्योम ieee80211_sta_setup_sdata(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_mgd_auth(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा cfg80211_auth_request *req);
पूर्णांक ieee80211_mgd_assoc(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा cfg80211_assoc_request *req);
पूर्णांक ieee80211_mgd_deauth(काष्ठा ieee80211_sub_अगर_data *sdata,
			 काष्ठा cfg80211_deauth_request *req);
पूर्णांक ieee80211_mgd_disassoc(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा cfg80211_disassoc_request *req);
व्योम ieee80211_send_pspoll(काष्ठा ieee80211_local *local,
			   काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_recalc_ps(काष्ठा ieee80211_local *local);
व्योम ieee80211_recalc_ps_vअगर(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_set_arp_filter(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_sta_work(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_sta_rx_queued_mgmt(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा sk_buff *skb);
व्योम ieee80211_sta_rx_queued_ext(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb);
व्योम ieee80211_sta_reset_beacon_monitor(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_sta_reset_conn_monitor(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_mgd_stop(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_mgd_conn_tx_status(काष्ठा ieee80211_sub_अगर_data *sdata,
				  __le16 fc, bool acked);
व्योम ieee80211_mgd_quiesce(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_sta_restart(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_sta_handle_tspec_ac_params(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_sta_connection_lost(काष्ठा ieee80211_sub_अगर_data *sdata,
				   u8 *bssid, u8 reason, bool tx);

/* IBSS code */
व्योम ieee80211_ibss_notअगरy_scan_completed(काष्ठा ieee80211_local *local);
व्योम ieee80211_ibss_setup_sdata(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_ibss_rx_no_sta(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर u8 *bssid, स्थिर u8 *addr, u32 supp_rates);
पूर्णांक ieee80211_ibss_join(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा cfg80211_ibss_params *params);
पूर्णांक ieee80211_ibss_leave(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_ibss_work(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_ibss_rx_queued_mgmt(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sk_buff *skb);
पूर्णांक ieee80211_ibss_csa_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा cfg80211_csa_settings *csa_settings);
पूर्णांक ieee80211_ibss_finish_csa(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_ibss_stop(काष्ठा ieee80211_sub_अगर_data *sdata);

/* OCB code */
व्योम ieee80211_ocb_work(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_ocb_rx_no_sta(काष्ठा ieee80211_sub_अगर_data *sdata,
			     स्थिर u8 *bssid, स्थिर u8 *addr, u32 supp_rates);
व्योम ieee80211_ocb_setup_sdata(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_ocb_join(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा ocb_setup *setup);
पूर्णांक ieee80211_ocb_leave(काष्ठा ieee80211_sub_अगर_data *sdata);

/* mesh code */
व्योम ieee80211_mesh_work(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_mesh_rx_queued_mgmt(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sk_buff *skb);
पूर्णांक ieee80211_mesh_csa_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा cfg80211_csa_settings *csa_settings);
पूर्णांक ieee80211_mesh_finish_csa(काष्ठा ieee80211_sub_अगर_data *sdata);

/* scan/BSS handling */
व्योम ieee80211_scan_work(काष्ठा work_काष्ठा *work);
पूर्णांक ieee80211_request_ibss_scan(काष्ठा ieee80211_sub_अगर_data *sdata,
				स्थिर u8 *ssid, u8 ssid_len,
				काष्ठा ieee80211_channel **channels,
				अचिन्हित पूर्णांक n_channels,
				क्रमागत nl80211_bss_scan_width scan_width);
पूर्णांक ieee80211_request_scan(काष्ठा ieee80211_sub_अगर_data *sdata,
			   काष्ठा cfg80211_scan_request *req);
व्योम ieee80211_scan_cancel(काष्ठा ieee80211_local *local);
व्योम ieee80211_run_deferred_scan(काष्ठा ieee80211_local *local);
व्योम ieee80211_scan_rx(काष्ठा ieee80211_local *local, काष्ठा sk_buff *skb);

व्योम ieee80211_mlme_notअगरy_scan_completed(काष्ठा ieee80211_local *local);
काष्ठा ieee80211_bss *
ieee80211_bss_info_update(काष्ठा ieee80211_local *local,
			  काष्ठा ieee80211_rx_status *rx_status,
			  काष्ठा ieee80211_mgmt *mgmt,
			  माप_प्रकार len,
			  काष्ठा ieee80211_channel *channel);
व्योम ieee80211_rx_bss_put(काष्ठा ieee80211_local *local,
			  काष्ठा ieee80211_bss *bss);

/* scheduled scan handling */
पूर्णांक
__ieee80211_request_sched_scan_start(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा cfg80211_sched_scan_request *req);
पूर्णांक ieee80211_request_sched_scan_start(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा cfg80211_sched_scan_request *req);
पूर्णांक ieee80211_request_sched_scan_stop(काष्ठा ieee80211_local *local);
व्योम ieee80211_sched_scan_end(काष्ठा ieee80211_local *local);
व्योम ieee80211_sched_scan_stopped_work(काष्ठा work_काष्ठा *work);

/* off-channel/mgmt-tx */
व्योम ieee80211_offchannel_stop_vअगरs(काष्ठा ieee80211_local *local);
व्योम ieee80211_offchannel_वापस(काष्ठा ieee80211_local *local);
व्योम ieee80211_roc_setup(काष्ठा ieee80211_local *local);
व्योम ieee80211_start_next_roc(काष्ठा ieee80211_local *local);
व्योम ieee80211_roc_purge(काष्ठा ieee80211_local *local,
			 काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_reमुख्य_on_channel(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				काष्ठा ieee80211_channel *chan,
				अचिन्हित पूर्णांक duration, u64 *cookie);
पूर्णांक ieee80211_cancel_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
				       काष्ठा wireless_dev *wdev, u64 cookie);
पूर्णांक ieee80211_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		      काष्ठा cfg80211_mgmt_tx_params *params, u64 *cookie);
पूर्णांक ieee80211_mgmt_tx_cancel_रुको(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev, u64 cookie);

/* channel चयन handling */
व्योम ieee80211_csa_finalize_work(काष्ठा work_काष्ठा *work);
पूर्णांक ieee80211_channel_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     काष्ठा cfg80211_csa_settings *params);

/* पूर्णांकerface handling */
#घोषणा MAC80211_SUPPORTED_FEATURES_TX	(NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM | \
					 NETIF_F_HW_CSUM | NETIF_F_SG | \
					 NETIF_F_HIGHDMA | NETIF_F_GSO_SOFTWARE)
#घोषणा MAC80211_SUPPORTED_FEATURES_RX	(NETIF_F_RXCSUM)
#घोषणा MAC80211_SUPPORTED_FEATURES	(MAC80211_SUPPORTED_FEATURES_TX | \
					 MAC80211_SUPPORTED_FEATURES_RX)

पूर्णांक ieee80211_अगरace_init(व्योम);
व्योम ieee80211_अगरace_निकास(व्योम);
पूर्णांक ieee80211_अगर_add(काष्ठा ieee80211_local *local, स्थिर अक्षर *name,
		     अचिन्हित अक्षर name_assign_type,
		     काष्ठा wireless_dev **new_wdev, क्रमागत nl80211_अगरtype type,
		     काष्ठा vअगर_params *params);
पूर्णांक ieee80211_अगर_change_type(काष्ठा ieee80211_sub_अगर_data *sdata,
			     क्रमागत nl80211_अगरtype type);
व्योम ieee80211_अगर_हटाओ(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_हटाओ_पूर्णांकerfaces(काष्ठा ieee80211_local *local);
u32 ieee80211_idle_off(काष्ठा ieee80211_local *local);
व्योम ieee80211_recalc_idle(काष्ठा ieee80211_local *local);
व्योम ieee80211_adjust_monitor_flags(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर पूर्णांक offset);
पूर्णांक ieee80211_करो_खोलो(काष्ठा wireless_dev *wdev, bool coming_up);
व्योम ieee80211_sdata_stop(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_add_भव_monitor(काष्ठा ieee80211_local *local);
व्योम ieee80211_del_भव_monitor(काष्ठा ieee80211_local *local);

bool __ieee80211_recalc_txघातer(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_recalc_txघातer(काष्ठा ieee80211_sub_अगर_data *sdata,
			      bool update_bss);
व्योम ieee80211_recalc_offload(काष्ठा ieee80211_local *local);

अटल अंतरभूत bool ieee80211_sdata_running(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	वापस test_bit(SDATA_STATE_RUNNING, &sdata->state);
पूर्ण

/* tx handling */
व्योम ieee80211_clear_tx_pending(काष्ठा ieee80211_local *local);
व्योम ieee80211_tx_pending(काष्ठा tasklet_काष्ठा *t);
netdev_tx_t ieee80211_monitor_start_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev);
netdev_tx_t ieee80211_subअगर_start_xmit(काष्ठा sk_buff *skb,
				       काष्ठा net_device *dev);
netdev_tx_t ieee80211_subअगर_start_xmit_8023(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev);
व्योम __ieee80211_subअगर_start_xmit(काष्ठा sk_buff *skb,
				  काष्ठा net_device *dev,
				  u32 info_flags,
				  u32 ctrl_flags,
				  u64 *cookie);
व्योम ieee80211_purge_tx_queue(काष्ठा ieee80211_hw *hw,
			      काष्ठा sk_buff_head *skbs);
काष्ठा sk_buff *
ieee80211_build_data_ढाँचा(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा sk_buff *skb, u32 info_flags);
व्योम ieee80211_tx_monitor(काष्ठा ieee80211_local *local, काष्ठा sk_buff *skb,
			  काष्ठा ieee80211_supported_band *sband,
			  पूर्णांक retry_count, पूर्णांक shअगरt, bool send_to_cooked,
			  काष्ठा ieee80211_tx_status *status);

व्योम ieee80211_check_fast_xmit(काष्ठा sta_info *sta);
व्योम ieee80211_check_fast_xmit_all(काष्ठा ieee80211_local *local);
व्योम ieee80211_check_fast_xmit_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_clear_fast_xmit(काष्ठा sta_info *sta);
पूर्णांक ieee80211_tx_control_port(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      स्थिर u8 *buf, माप_प्रकार len,
			      स्थिर u8 *dest, __be16 proto, bool unencrypted,
			      u64 *cookie);
पूर्णांक ieee80211_probe_mesh_link(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      स्थिर u8 *buf, माप_प्रकार len);

/* HT */
व्योम ieee80211_apply_htcap_overrides(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा ieee80211_sta_ht_cap *ht_cap);
bool ieee80211_ht_cap_ie_to_sta_ht_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_supported_band *sband,
				       स्थिर काष्ठा ieee80211_ht_cap *ht_cap_ie,
				       काष्ठा sta_info *sta);
व्योम ieee80211_send_delba(काष्ठा ieee80211_sub_अगर_data *sdata,
			  स्थिर u8 *da, u16 tid,
			  u16 initiator, u16 reason_code);
पूर्णांक ieee80211_send_smps_action(काष्ठा ieee80211_sub_अगर_data *sdata,
			       क्रमागत ieee80211_smps_mode smps, स्थिर u8 *da,
			       स्थिर u8 *bssid);
व्योम ieee80211_request_smps_ap_work(काष्ठा work_काष्ठा *work);
व्योम ieee80211_request_smps_mgd_work(काष्ठा work_काष्ठा *work);
bool ieee80211_smps_is_restrictive(क्रमागत ieee80211_smps_mode smps_mode_old,
				   क्रमागत ieee80211_smps_mode smps_mode_new);

व्योम ___ieee80211_stop_rx_ba_session(काष्ठा sta_info *sta, u16 tid,
				     u16 initiator, u16 reason, bool stop);
व्योम __ieee80211_stop_rx_ba_session(काष्ठा sta_info *sta, u16 tid,
				    u16 initiator, u16 reason, bool stop);
व्योम ___ieee80211_start_rx_ba_session(काष्ठा sta_info *sta,
				      u8 dialog_token, u16 समयout,
				      u16 start_seq_num, u16 ba_policy, u16 tid,
				      u16 buf_size, bool tx, bool स्वतः_seq,
				      स्थिर काष्ठा ieee80211_addba_ext_ie *addbaext);
व्योम ieee80211_sta_tear_करोwn_BA_sessions(काष्ठा sta_info *sta,
					 क्रमागत ieee80211_agg_stop_reason reason);
व्योम ieee80211_process_delba(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा sta_info *sta,
			     काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len);
व्योम ieee80211_process_addba_resp(काष्ठा ieee80211_local *local,
				  काष्ठा sta_info *sta,
				  काष्ठा ieee80211_mgmt *mgmt,
				  माप_प्रकार len);
व्योम ieee80211_process_addba_request(काष्ठा ieee80211_local *local,
				     काष्ठा sta_info *sta,
				     काष्ठा ieee80211_mgmt *mgmt,
				     माप_प्रकार len);

पूर्णांक __ieee80211_stop_tx_ba_session(काष्ठा sta_info *sta, u16 tid,
				   क्रमागत ieee80211_agg_stop_reason reason);
पूर्णांक ___ieee80211_stop_tx_ba_session(काष्ठा sta_info *sta, u16 tid,
				    क्रमागत ieee80211_agg_stop_reason reason);
व्योम ieee80211_start_tx_ba_cb(काष्ठा sta_info *sta, पूर्णांक tid,
			      काष्ठा tid_ampdu_tx *tid_tx);
व्योम ieee80211_stop_tx_ba_cb(काष्ठा sta_info *sta, पूर्णांक tid,
			     काष्ठा tid_ampdu_tx *tid_tx);
व्योम ieee80211_ba_session_work(काष्ठा work_काष्ठा *work);
व्योम ieee80211_tx_ba_session_handle_start(काष्ठा sta_info *sta, पूर्णांक tid);
व्योम ieee80211_release_reorder_समयout(काष्ठा sta_info *sta, पूर्णांक tid);

u8 ieee80211_mcs_to_chains(स्थिर काष्ठा ieee80211_mcs_info *mcs);
क्रमागत nl80211_smps_mode
ieee80211_smps_mode_to_smps_mode(क्रमागत ieee80211_smps_mode smps);

/* VHT */
व्योम
ieee80211_vht_cap_ie_to_sta_vht_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_supported_band *sband,
				    स्थिर काष्ठा ieee80211_vht_cap *vht_cap_ie,
				    काष्ठा sta_info *sta);
क्रमागत ieee80211_sta_rx_bandwidth ieee80211_sta_cap_rx_bw(काष्ठा sta_info *sta);
क्रमागत ieee80211_sta_rx_bandwidth ieee80211_sta_cur_vht_bw(काष्ठा sta_info *sta);
व्योम ieee80211_sta_set_rx_nss(काष्ठा sta_info *sta);
क्रमागत ieee80211_sta_rx_bandwidth
ieee80211_chan_width_to_rx_bw(क्रमागत nl80211_chan_width width);
क्रमागत nl80211_chan_width ieee80211_sta_cap_chan_bw(काष्ठा sta_info *sta);
व्योम ieee80211_sta_set_rx_nss(काष्ठा sta_info *sta);
व्योम ieee80211_process_mu_groups(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा ieee80211_mgmt *mgmt);
u32 __ieee80211_vht_handle_opmode(काष्ठा ieee80211_sub_अगर_data *sdata,
                                  काष्ठा sta_info *sta, u8 opmode,
				  क्रमागत nl80211_band band);
व्योम ieee80211_vht_handle_opmode(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sta_info *sta, u8 opmode,
				 क्रमागत nl80211_band band);
व्योम ieee80211_apply_vhtcap_overrides(काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा ieee80211_sta_vht_cap *vht_cap);
व्योम ieee80211_get_vht_mask_from_cap(__le16 vht_cap,
				     u16 vht_mask[NL80211_VHT_NSS_MAX]);
क्रमागत nl80211_chan_width
ieee80211_sta_rx_bw_to_chan_width(काष्ठा sta_info *sta);

/* HE */
व्योम
ieee80211_he_cap_ie_to_sta_he_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा ieee80211_supported_band *sband,
				  स्थिर u8 *he_cap_ie, u8 he_cap_len,
				  स्थिर काष्ठा ieee80211_he_6ghz_capa *he_6ghz_capa,
				  काष्ठा sta_info *sta);
व्योम
ieee80211_he_spr_ie_to_bss_conf(काष्ठा ieee80211_vअगर *vअगर,
				स्थिर काष्ठा ieee80211_he_spr *he_spr_ie_elem);

व्योम
ieee80211_he_op_ie_to_bss_conf(काष्ठा ieee80211_vअगर *vअगर,
			स्थिर काष्ठा ieee80211_he_operation *he_op_ie_elem);

/* S1G */
व्योम ieee80211_s1g_sta_rate_init(काष्ठा sta_info *sta);

/* Spectrum management */
व्योम ieee80211_process_measurement_req(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_mgmt *mgmt,
				       माप_प्रकार len);
/**
 * ieee80211_parse_ch_चयन_ie - parses channel चयन IEs
 * @sdata: the sdata of the पूर्णांकerface which has received the frame
 * @elems: parsed 802.11 elements received with the frame
 * @current_band: indicates the current band
 * @vht_cap_info: VHT capabilities of the transmitter
 * @sta_flags: contains inक्रमmation about own capabilities and restrictions
 *	to decide which channel चयन announcements can be accepted. Only the
 *	following subset of &क्रमागत ieee80211_sta_flags are evaluated:
 *	%IEEE80211_STA_DISABLE_HT, %IEEE80211_STA_DISABLE_VHT,
 *	%IEEE80211_STA_DISABLE_40MHZ, %IEEE80211_STA_DISABLE_80P80MHZ,
 *	%IEEE80211_STA_DISABLE_160MHZ.
 * @bssid: the currently connected bssid (क्रम reporting)
 * @csa_ie: parsed 802.11 csa elements on count, mode, chandef and mesh ttl.
	All of them will be filled with अगर success only.
 * Return: 0 on success, <0 on error and >0 अगर there is nothing to parse.
 */
पूर्णांक ieee80211_parse_ch_चयन_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा ieee802_11_elems *elems,
				 क्रमागत nl80211_band current_band,
				 u32 vht_cap_info,
				 u32 sta_flags, u8 *bssid,
				 काष्ठा ieee80211_csa_ie *csa_ie);

/* Suspend/resume and hw reconfiguration */
पूर्णांक ieee80211_reconfig(काष्ठा ieee80211_local *local);
व्योम ieee80211_stop_device(काष्ठा ieee80211_local *local);

पूर्णांक __ieee80211_suspend(काष्ठा ieee80211_hw *hw,
			काष्ठा cfg80211_wowlan *wowlan);

अटल अंतरभूत पूर्णांक __ieee80211_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	WARN(test_bit(SCAN_HW_SCANNING, &local->scanning) &&
	     !test_bit(SCAN_COMPLETED, &local->scanning),
		"%s: resume with hardware scan still in progress\n",
		wiphy_name(hw->wiphy));

	वापस ieee80211_reconfig(hw_to_local(hw));
पूर्ण

/* utility functions/स्थिरants */
बाह्य स्थिर व्योम *स्थिर mac80211_wiphy_privid; /* क्रम wiphy privid */
पूर्णांक ieee80211_frame_duration(क्रमागत nl80211_band band, माप_प्रकार len,
			     पूर्णांक rate, पूर्णांक erp, पूर्णांक लघु_preamble,
			     पूर्णांक shअगरt);
व्योम ieee80211_regulatory_limit_wmm_params(काष्ठा ieee80211_sub_अगर_data *sdata,
					   काष्ठा ieee80211_tx_queue_params *qparam,
					   पूर्णांक ac);
व्योम ieee80211_set_wmm_शेष(काष्ठा ieee80211_sub_अगर_data *sdata,
			       bool bss_notअगरy, bool enable_qos);
व्योम ieee80211_xmit(काष्ठा ieee80211_sub_अगर_data *sdata,
		    काष्ठा sta_info *sta, काष्ठा sk_buff *skb);

व्योम __ieee80211_tx_skb_tid_band(काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा sk_buff *skb, पूर्णांक tid,
				 क्रमागत nl80211_band band);

/* sta_out needs to be checked क्रम ERR_PTR() beक्रमe using */
पूर्णांक ieee80211_lookup_ra_sta(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा sk_buff *skb,
			    काष्ठा sta_info **sta_out);

अटल अंतरभूत व्योम
ieee80211_tx_skb_tid_band(काष्ठा ieee80211_sub_अगर_data *sdata,
			  काष्ठा sk_buff *skb, पूर्णांक tid,
			  क्रमागत nl80211_band band)
अणु
	rcu_पढ़ो_lock();
	__ieee80211_tx_skb_tid_band(sdata, skb, tid, band);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम ieee80211_tx_skb_tid(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा sk_buff *skb, पूर्णांक tid)
अणु
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	__ieee80211_tx_skb_tid_band(sdata, skb, tid,
				    chanctx_conf->def.chan->band);
	rcu_पढ़ो_unlock();
पूर्ण

अटल अंतरभूत व्योम ieee80211_tx_skb(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा sk_buff *skb)
अणु
	/* Send all पूर्णांकernal mgmt frames on VO. Accordingly set TID to 7. */
	ieee80211_tx_skb_tid(sdata, skb, 7);
पूर्ण

u32 ieee802_11_parse_elems_crc(स्थिर u8 *start, माप_प्रकार len, bool action,
			       काष्ठा ieee802_11_elems *elems,
			       u64 filter, u32 crc, u8 *transmitter_bssid,
			       u8 *bss_bssid);
अटल अंतरभूत व्योम ieee802_11_parse_elems(स्थिर u8 *start, माप_प्रकार len,
					  bool action,
					  काष्ठा ieee802_11_elems *elems,
					  u8 *transmitter_bssid,
					  u8 *bss_bssid)
अणु
	ieee802_11_parse_elems_crc(start, len, action, elems, 0, 0,
				   transmitter_bssid, bss_bssid);
पूर्ण


बाह्य स्थिर पूर्णांक ieee802_1d_to_ac[8];

अटल अंतरभूत पूर्णांक ieee80211_ac_from_tid(पूर्णांक tid)
अणु
	वापस ieee802_1d_to_ac[tid & 7];
पूर्ण

व्योम ieee80211_dynamic_ps_enable_work(काष्ठा work_काष्ठा *work);
व्योम ieee80211_dynamic_ps_disable_work(काष्ठा work_काष्ठा *work);
व्योम ieee80211_dynamic_ps_समयr(काष्ठा समयr_list *t);
व्योम ieee80211_send_nullfunc(काष्ठा ieee80211_local *local,
			     काष्ठा ieee80211_sub_अगर_data *sdata,
			     bool घातersave);
व्योम ieee80211_sta_tx_notअगरy(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा ieee80211_hdr *hdr, bool ack, u16 tx_समय);

व्योम ieee80211_wake_queues_by_reason(काष्ठा ieee80211_hw *hw,
				     अचिन्हित दीर्घ queues,
				     क्रमागत queue_stop_reason reason,
				     bool refcounted);
व्योम ieee80211_stop_vअगर_queues(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata,
			       क्रमागत queue_stop_reason reason);
व्योम ieee80211_wake_vअगर_queues(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata,
			       क्रमागत queue_stop_reason reason);
व्योम ieee80211_stop_queues_by_reason(काष्ठा ieee80211_hw *hw,
				     अचिन्हित दीर्घ queues,
				     क्रमागत queue_stop_reason reason,
				     bool refcounted);
व्योम ieee80211_wake_queue_by_reason(काष्ठा ieee80211_hw *hw, पूर्णांक queue,
				    क्रमागत queue_stop_reason reason,
				    bool refcounted);
व्योम ieee80211_stop_queue_by_reason(काष्ठा ieee80211_hw *hw, पूर्णांक queue,
				    क्रमागत queue_stop_reason reason,
				    bool refcounted);
व्योम ieee80211_propagate_queue_wake(काष्ठा ieee80211_local *local, पूर्णांक queue);
व्योम ieee80211_add_pending_skb(काष्ठा ieee80211_local *local,
			       काष्ठा sk_buff *skb);
व्योम ieee80211_add_pending_skbs(काष्ठा ieee80211_local *local,
				काष्ठा sk_buff_head *skbs);
व्योम ieee80211_flush_queues(काष्ठा ieee80211_local *local,
			    काष्ठा ieee80211_sub_अगर_data *sdata, bool drop);
व्योम __ieee80211_flush_queues(काष्ठा ieee80211_local *local,
			      काष्ठा ieee80211_sub_अगर_data *sdata,
			      अचिन्हित पूर्णांक queues, bool drop);

अटल अंतरभूत bool ieee80211_can_run_worker(काष्ठा ieee80211_local *local)
अणु
	/*
	 * It's unsafe to try to करो any work during reconfigure flow.
	 * When the flow ends the work will be requeued.
	 */
	अगर (local->in_reconfig)
		वापस false;

	/*
	 * If quiescing is set, we are racing with __ieee80211_suspend.
	 * __ieee80211_suspend flushes the workers after setting quiescing,
	 * and we check quiescing / suspended beक्रमe enqueing new workers.
	 * We should पात the worker to aव्योम the races below.
	 */
	अगर (local->quiescing)
		वापस false;

	/*
	 * We might alपढ़ोy be suspended अगर the following scenario occurs:
	 * __ieee80211_suspend		Control path
	 *
	 *				अगर (local->quiescing)
	 *					वापस;
	 * local->quiescing = true;
	 * flush_workqueue();
	 *				queue_work(...);
	 * local->suspended = true;
	 * local->quiescing = false;
	 *				worker starts running...
	 */
	अगर (local->suspended)
		वापस false;

	वापस true;
पूर्ण

पूर्णांक ieee80211_txq_setup_flows(काष्ठा ieee80211_local *local);
व्योम ieee80211_txq_set_params(काष्ठा ieee80211_local *local);
व्योम ieee80211_txq_tearकरोwn_flows(काष्ठा ieee80211_local *local);
व्योम ieee80211_txq_init(काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा sta_info *sta,
			काष्ठा txq_info *txq, पूर्णांक tid);
व्योम ieee80211_txq_purge(काष्ठा ieee80211_local *local,
			 काष्ठा txq_info *txqi);
व्योम ieee80211_txq_हटाओ_vlan(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_fill_txq_stats(काष्ठा cfg80211_txq_stats *txqstats,
			      काष्ठा txq_info *txqi);
व्योम ieee80211_wake_txqs(काष्ठा tasklet_काष्ठा *t);
व्योम ieee80211_send_auth(काष्ठा ieee80211_sub_अगर_data *sdata,
			 u16 transaction, u16 auth_alg, u16 status,
			 स्थिर u8 *extra, माप_प्रकार extra_len, स्थिर u8 *bssid,
			 स्थिर u8 *da, स्थिर u8 *key, u8 key_len, u8 key_idx,
			 u32 tx_flags);
व्योम ieee80211_send_deauth_disassoc(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर u8 *da, स्थिर u8 *bssid,
				    u16 stype, u16 reason,
				    bool send_frame, u8 *frame_buf);

क्रमागत अणु
	IEEE80211_PROBE_FLAG_सूचीECTED		= BIT(0),
	IEEE80211_PROBE_FLAG_MIN_CONTENT	= BIT(1),
	IEEE80211_PROBE_FLAG_RANDOM_SN		= BIT(2),
पूर्ण;

पूर्णांक ieee80211_build_preq_ies(काष्ठा ieee80211_sub_अगर_data *sdata, u8 *buffer,
			     माप_प्रकार buffer_len,
			     काष्ठा ieee80211_scan_ies *ie_desc,
			     स्थिर u8 *ie, माप_प्रकार ie_len,
			     u8 bands_used, u32 *rate_masks,
			     काष्ठा cfg80211_chan_def *chandef,
			     u32 flags);
काष्ठा sk_buff *ieee80211_build_probe_req(काष्ठा ieee80211_sub_अगर_data *sdata,
					  स्थिर u8 *src, स्थिर u8 *dst,
					  u32 ratemask,
					  काष्ठा ieee80211_channel *chan,
					  स्थिर u8 *ssid, माप_प्रकार ssid_len,
					  स्थिर u8 *ie, माप_प्रकार ie_len,
					  u32 flags);
u32 ieee80211_sta_get_rates(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा ieee802_11_elems *elems,
			    क्रमागत nl80211_band band, u32 *basic_rates);
पूर्णांक __ieee80211_request_smps_mgd(काष्ठा ieee80211_sub_अगर_data *sdata,
				 क्रमागत ieee80211_smps_mode smps_mode);
व्योम ieee80211_recalc_smps(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_recalc_min_chandef(काष्ठा ieee80211_sub_अगर_data *sdata);

माप_प्रकार ieee80211_ie_split_venकरोr(स्थिर u8 *ies, माप_प्रकार ielen, माप_प्रकार offset);
u8 *ieee80211_ie_build_ht_cap(u8 *pos, काष्ठा ieee80211_sta_ht_cap *ht_cap,
			      u16 cap);
u8 *ieee80211_ie_build_ht_oper(u8 *pos, काष्ठा ieee80211_sta_ht_cap *ht_cap,
			       स्थिर काष्ठा cfg80211_chan_def *chandef,
			       u16 prot_mode, bool rअगरs_mode);
व्योम ieee80211_ie_build_wide_bw_cs(u8 *pos,
				   स्थिर काष्ठा cfg80211_chan_def *chandef);
u8 *ieee80211_ie_build_vht_cap(u8 *pos, काष्ठा ieee80211_sta_vht_cap *vht_cap,
			       u32 cap);
u8 *ieee80211_ie_build_vht_oper(u8 *pos, काष्ठा ieee80211_sta_vht_cap *vht_cap,
				स्थिर काष्ठा cfg80211_chan_def *chandef);
u8 ieee80211_ie_len_he_cap(काष्ठा ieee80211_sub_अगर_data *sdata, u8 अगरtype);
u8 *ieee80211_ie_build_he_cap(u8 *pos,
			      स्थिर काष्ठा ieee80211_sta_he_cap *he_cap,
			      u8 *end);
व्योम ieee80211_ie_build_he_6ghz_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा sk_buff *skb);
u8 *ieee80211_ie_build_he_oper(u8 *pos, काष्ठा cfg80211_chan_def *chandef);
पूर्णांक ieee80211_parse_bitrates(काष्ठा cfg80211_chan_def *chandef,
			     स्थिर काष्ठा ieee80211_supported_band *sband,
			     स्थिर u8 *srates, पूर्णांक srates_len, u32 *rates);
पूर्णांक ieee80211_add_srates_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा sk_buff *skb, bool need_basic,
			    क्रमागत nl80211_band band);
पूर्णांक ieee80211_add_ext_srates_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा sk_buff *skb, bool need_basic,
				क्रमागत nl80211_band band);
u8 *ieee80211_add_wmm_info_ie(u8 *buf, u8 qosinfo);
व्योम ieee80211_add_s1g_capab_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा ieee80211_sta_s1g_cap *caps,
				काष्ठा sk_buff *skb);
व्योम ieee80211_add_aid_request_ie(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा sk_buff *skb);

/* channel management */
bool ieee80211_chandef_ht_oper(स्थिर काष्ठा ieee80211_ht_operation *ht_oper,
			       काष्ठा cfg80211_chan_def *chandef);
bool ieee80211_chandef_vht_oper(काष्ठा ieee80211_hw *hw, u32 vht_cap_info,
				स्थिर काष्ठा ieee80211_vht_operation *oper,
				स्थिर काष्ठा ieee80211_ht_operation *htop,
				काष्ठा cfg80211_chan_def *chandef);
bool ieee80211_chandef_he_6ghz_oper(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर काष्ठा ieee80211_he_operation *he_oper,
				    काष्ठा cfg80211_chan_def *chandef);
bool ieee80211_chandef_s1g_oper(स्थिर काष्ठा ieee80211_s1g_oper_ie *oper,
				काष्ठा cfg80211_chan_def *chandef);
u32 ieee80211_chandef_करोwngrade(काष्ठा cfg80211_chan_def *c);

पूर्णांक __must_check
ieee80211_vअगर_use_channel(काष्ठा ieee80211_sub_अगर_data *sdata,
			  स्थिर काष्ठा cfg80211_chan_def *chandef,
			  क्रमागत ieee80211_chanctx_mode mode);
पूर्णांक __must_check
ieee80211_vअगर_reserve_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर काष्ठा cfg80211_chan_def *chandef,
			      क्रमागत ieee80211_chanctx_mode mode,
			      bool radar_required);
पूर्णांक __must_check
ieee80211_vअगर_use_reserved_context(काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_vअगर_unreserve_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata);

पूर्णांक __must_check
ieee80211_vअगर_change_bandwidth(काष्ठा ieee80211_sub_अगर_data *sdata,
			       स्थिर काष्ठा cfg80211_chan_def *chandef,
			       u32 *changed);
व्योम ieee80211_vअगर_release_channel(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_vअगर_vlan_copy_chanctx(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_vअगर_copy_chanctx_to_vlans(काष्ठा ieee80211_sub_अगर_data *sdata,
					 bool clear);
पूर्णांक ieee80211_chanctx_refcount(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_chanctx *ctx);

व्योम ieee80211_recalc_smps_chanctx(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_chanctx *chanctx);
व्योम ieee80211_recalc_chanctx_min_def(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_chanctx *ctx);
bool ieee80211_is_radar_required(काष्ठा ieee80211_local *local);

व्योम ieee80211_dfs_cac_समयr(अचिन्हित दीर्घ data);
व्योम ieee80211_dfs_cac_समयr_work(काष्ठा work_काष्ठा *work);
व्योम ieee80211_dfs_cac_cancel(काष्ठा ieee80211_local *local);
व्योम ieee80211_dfs_radar_detected_work(काष्ठा work_काष्ठा *work);
पूर्णांक ieee80211_send_action_csa(काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा cfg80211_csa_settings *csa_settings);

bool ieee80211_cs_valid(स्थिर काष्ठा ieee80211_cipher_scheme *cs);
bool ieee80211_cs_list_valid(स्थिर काष्ठा ieee80211_cipher_scheme *cs, पूर्णांक n);
स्थिर काष्ठा ieee80211_cipher_scheme *
ieee80211_cs_get(काष्ठा ieee80211_local *local, u32 cipher,
		 क्रमागत nl80211_अगरtype अगरtype);
पूर्णांक ieee80211_cs_headroom(काष्ठा ieee80211_local *local,
			  काष्ठा cfg80211_crypto_settings *crypto,
			  क्रमागत nl80211_अगरtype अगरtype);
व्योम ieee80211_recalc_dtim(काष्ठा ieee80211_local *local,
			   काष्ठा ieee80211_sub_अगर_data *sdata);
पूर्णांक ieee80211_check_combinations(काष्ठा ieee80211_sub_अगर_data *sdata,
				 स्थिर काष्ठा cfg80211_chan_def *chandef,
				 क्रमागत ieee80211_chanctx_mode chanmode,
				 u8 radar_detect);
पूर्णांक ieee80211_max_num_channels(काष्ठा ieee80211_local *local);
व्योम ieee80211_recalc_chanctx_chantype(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_chanctx *ctx);

/* TDLS */
पूर्णांक ieee80211_tdls_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			स्थिर u8 *peer, u8 action_code, u8 dialog_token,
			u16 status_code, u32 peer_capability,
			bool initiator, स्थिर u8 *extra_ies,
			माप_प्रकार extra_ies_len);
पूर्णांक ieee80211_tdls_oper(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			स्थिर u8 *peer, क्रमागत nl80211_tdls_operation oper);
व्योम ieee80211_tdls_peer_del_work(काष्ठा work_काष्ठा *wk);
पूर्णांक ieee80211_tdls_channel_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर u8 *addr, u8 oper_class,
				  काष्ठा cfg80211_chan_def *chandef);
व्योम ieee80211_tdls_cancel_channel_चयन(काष्ठा wiphy *wiphy,
					  काष्ठा net_device *dev,
					  स्थिर u8 *addr);
व्योम ieee80211_tearकरोwn_tdls_peers(काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम ieee80211_tdls_chsw_work(काष्ठा work_काष्ठा *wk);
व्योम ieee80211_tdls_handle_disconnect(काष्ठा ieee80211_sub_अगर_data *sdata,
				      स्थिर u8 *peer, u16 reason);
स्थिर अक्षर *ieee80211_get_reason_code_string(u16 reason_code);
u16 ieee80211_encode_usf(पूर्णांक val);
u8 *ieee80211_get_bssid(काष्ठा ieee80211_hdr *hdr, माप_प्रकार len,
			क्रमागत nl80211_अगरtype type);

बाह्य स्थिर काष्ठा ethtool_ops ieee80211_ethtool_ops;

u32 ieee80211_calc_expected_tx_airसमय(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *pubsta,
				       पूर्णांक len, bool ampdu);
#अगर_घोषित CONFIG_MAC80211_NOINLINE
#घोषणा debug_noअंतरभूत noअंतरभूत
#अन्यथा
#घोषणा debug_noअंतरभूत
#पूर्ण_अगर

व्योम ieee80211_init_frag_cache(काष्ठा ieee80211_fragment_cache *cache);
व्योम ieee80211_destroy_frag_cache(काष्ठा ieee80211_fragment_cache *cache);

#पूर्ण_अगर /* IEEE80211_I_H */
