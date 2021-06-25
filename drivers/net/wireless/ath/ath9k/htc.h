<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित HTC_H
#घोषणा HTC_H

#समावेश <linux/module.h>
#समावेश <linux/usb.h>
#समावेश <linux/firmware.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>

#समावेश "common.h"
#समावेश "htc_hst.h"
#समावेश "hif_usb.h"
#समावेश "wmi.h"

#घोषणा ATH_STA_SHORT_CALINTERVAL 1000    /* 1 second */
#घोषणा ATH_AP_SHORT_CALINTERVAL  100     /* 100 ms */
#घोषणा ATH_ANI_POLLINTERVAL      100     /* 100 ms */
#घोषणा ATH_LONG_CALINTERVAL      30000   /* 30 seconds */
#घोषणा ATH_RESTART_CALINTERVAL   1200000 /* 20 minutes */

#घोषणा ATH_DEFAULT_BMISS_LIMIT 10
#घोषणा TSF_TO_TU(_h, _l) \
	((((u32)(_h)) << 22) | (((u32)(_l)) >> 10))

बाह्य काष्ठा ieee80211_ops ath9k_htc_ops;
बाह्य पूर्णांक htc_modparam_nohwcrypt;
#अगर_घोषित CONFIG_MAC80211_LEDS
बाह्य पूर्णांक ath9k_htc_led_blink;
#पूर्ण_अगर

क्रमागत htc_phymode अणु
	HTC_MODE_11NA		= 0,
	HTC_MODE_11NG		= 1
पूर्ण;

क्रमागत htc_opmode अणु
	HTC_M_STA	= 1,
	HTC_M_IBSS	= 0,
	HTC_M_AHDEMO	= 3,
	HTC_M_HOSTAP	= 6,
	HTC_M_MONITOR	= 8,
	HTC_M_WDS	= 2
पूर्ण;

#घोषणा ATH9K_HTC_AMPDU  1
#घोषणा ATH9K_HTC_NORMAL 2
#घोषणा ATH9K_HTC_BEACON 3
#घोषणा ATH9K_HTC_MGMT   4

#घोषणा ATH9K_HTC_TX_CTSONLY      0x1
#घोषणा ATH9K_HTC_TX_RTSCTS       0x2

काष्ठा tx_frame_hdr अणु
	u8 data_type;
	u8 node_idx;
	u8 vअगर_idx;
	u8 tidno;
	__be32 flags; /* ATH9K_HTC_TX_* */
	u8 key_type;
	u8 keyix;
	u8 cookie;
	u8 pad;
पूर्ण __packed;

काष्ठा tx_mgmt_hdr अणु
	u8 node_idx;
	u8 vअगर_idx;
	u8 tidno;
	u8 flags;
	u8 key_type;
	u8 keyix;
	u8 cookie;
	u8 pad;
पूर्ण __packed;

काष्ठा tx_beacon_header अणु
	u8 vअगर_index;
	u8 len_changed;
	u16 rev;
पूर्ण __packed;

#घोषणा MAX_TX_AMPDU_SUBFRAMES_9271 17
#घोषणा MAX_TX_AMPDU_SUBFRAMES_7010 22

काष्ठा ath9k_htc_cap_target अणु
	__be32 ampdu_limit;
	u8 ampdu_subframes;
	u8 enable_coex;
	u8 tx_chainmask;
	u8 pad;
पूर्ण __packed;

काष्ठा ath9k_htc_target_vअगर अणु
	u8 index;
	u8 opmode;
	u8 myaddr[ETH_ALEN];
	u8 ath_cap;
	__be16 rtsthreshold;
	u8 pad;
पूर्ण __packed;

काष्ठा ath9k_htc_target_sta अणु
	u8 macaddr[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	u8 sta_index;
	u8 vअगर_index;
	u8 is_vअगर_sta;
	__be16 flags;
	__be16 htcap;
	__be16 maxampdu;
	u8 pad;
पूर्ण __packed;

काष्ठा ath9k_htc_target_aggr अणु
	u8 sta_index;
	u8 tidno;
	u8 aggr_enable;
	u8 padding;
पूर्ण __packed;

#घोषणा ATH_HTC_RATE_MAX 30

#घोषणा WLAN_RC_DS_FLAG  0x01
#घोषणा WLAN_RC_40_FLAG  0x02
#घोषणा WLAN_RC_SGI_FLAG 0x04
#घोषणा WLAN_RC_HT_FLAG  0x08
#घोषणा ATH_RC_TX_STBC_FLAG 0x20

काष्ठा ath9k_htc_rateset अणु
	u8 rs_nrates;
	u8 rs_rates[ATH_HTC_RATE_MAX];
पूर्ण;

काष्ठा ath9k_htc_rate अणु
	काष्ठा ath9k_htc_rateset legacy_rates;
	काष्ठा ath9k_htc_rateset ht_rates;
पूर्ण __packed;

काष्ठा ath9k_htc_target_rate अणु
	u8 sta_index;
	u8 isnew;
	__be32 capflags;
	काष्ठा ath9k_htc_rate rates;
पूर्ण;

काष्ठा ath9k_htc_target_rate_mask अणु
	u8 vअगर_index;
	u8 band;
	__be32 mask;
	u16 pad;
पूर्ण __packed;

काष्ठा ath9k_htc_target_पूर्णांक_stats अणु
	__be32 rx;
	__be32 rxorn;
	__be32 rxeol;
	__be32 txurn;
	__be32 txto;
	__be32 cst;
पूर्ण __packed;

काष्ठा ath9k_htc_target_tx_stats अणु
	__be32 xretries;
	__be32 fअगरoerr;
	__be32 filtered;
	__be32 समयr_exp;
	__be32 लघुretries;
	__be32 दीर्घretries;
	__be32 qnull;
	__be32 encap_fail;
	__be32 nobuf;
पूर्ण __packed;

काष्ठा ath9k_htc_target_rx_stats अणु
	__be32 nobuf;
	__be32 host_send;
	__be32 host_करोne;
पूर्ण __packed;

#घोषणा ATH9K_HTC_MAX_VIF 2
#घोषणा ATH9K_HTC_MAX_BCN_VIF 2

#घोषणा INC_VIF(_priv, _type) करो अणु		\
		चयन (_type) अणु		\
		हाल NL80211_IFTYPE_STATION:	\
			_priv->num_sta_vअगर++;	\
			अवरोध;			\
		हाल NL80211_IFTYPE_ADHOC:	\
			_priv->num_ibss_vअगर++;	\
			अवरोध;			\
		हाल NL80211_IFTYPE_AP:		\
			_priv->num_ap_vअगर++;	\
			अवरोध;			\
		हाल NL80211_IFTYPE_MESH_POINT:	\
			_priv->num_mbss_vअगर++;	\
			अवरोध;			\
		शेष:			\
			अवरोध;			\
		पूर्ण				\
	पूर्ण जबतक (0)

#घोषणा DEC_VIF(_priv, _type) करो अणु		\
		चयन (_type) अणु		\
		हाल NL80211_IFTYPE_STATION:	\
			_priv->num_sta_vअगर--;	\
			अवरोध;			\
		हाल NL80211_IFTYPE_ADHOC:	\
			_priv->num_ibss_vअगर--;	\
			अवरोध;			\
		हाल NL80211_IFTYPE_AP:		\
			_priv->num_ap_vअगर--;	\
			अवरोध;			\
		हाल NL80211_IFTYPE_MESH_POINT:	\
			_priv->num_mbss_vअगर--;	\
			अवरोध;			\
		शेष:			\
			अवरोध;			\
		पूर्ण				\
	पूर्ण जबतक (0)

काष्ठा ath9k_htc_vअगर अणु
	u8 index;
	u16 seq_no;
	bool beacon_configured;
	पूर्णांक bslot;
	__le64 tsfadjust;
पूर्ण;

काष्ठा ath9k_vअगर_iter_data अणु
	स्थिर u8 *hw_macaddr;
	u8 mask[ETH_ALEN];
पूर्ण;

#घोषणा ATH9K_HTC_MAX_STA 8
#घोषणा ATH9K_HTC_MAX_TID 8

क्रमागत tid_aggr_state अणु
	AGGR_STOP = 0,
	AGGR_PROGRESS,
	AGGR_START,
	AGGR_OPERATIONAL
पूर्ण;

काष्ठा ath9k_htc_sta अणु
	u8 index;
	क्रमागत tid_aggr_state tid_state[ATH9K_HTC_MAX_TID];
	काष्ठा work_काष्ठा rc_update_work;
	काष्ठा ath9k_htc_priv *htc_priv;
पूर्ण;

#घोषणा ATH9K_HTC_RXBUF 256
#घोषणा HTC_RX_FRAME_HEADER_SIZE 40

काष्ठा ath9k_htc_rxbuf अणु
	bool in_process;
	काष्ठा sk_buff *skb;
	काष्ठा ath_htc_rx_status rxstatus;
	काष्ठा list_head list;
पूर्ण;

काष्ठा ath9k_htc_rx अणु
	काष्ठा list_head rxbuf;
	spinlock_t rxbuflock;
पूर्ण;

#घोषणा ATH9K_HTC_TX_CLEANUP_INTERVAL 50 /* ms */
#घोषणा ATH9K_HTC_TX_TIMEOUT_INTERVAL 3000 /* ms */
#घोषणा ATH9K_HTC_TX_RESERVE 10
#घोषणा ATH9K_HTC_TX_TIMEOUT_COUNT 40
#घोषणा ATH9K_HTC_TX_THRESHOLD (MAX_TX_BUF_NUM - ATH9K_HTC_TX_RESERVE)

#घोषणा ATH9K_HTC_OP_TX_QUEUES_STOP BIT(0)
#घोषणा ATH9K_HTC_OP_TX_DRAIN       BIT(1)

काष्ठा ath9k_htc_tx अणु
	u8 flags;
	पूर्णांक queued_cnt;
	काष्ठा sk_buff_head mgmt_ep_queue;
	काष्ठा sk_buff_head cab_ep_queue;
	काष्ठा sk_buff_head data_be_queue;
	काष्ठा sk_buff_head data_bk_queue;
	काष्ठा sk_buff_head data_vi_queue;
	काष्ठा sk_buff_head data_vo_queue;
	काष्ठा sk_buff_head tx_failed;
	DECLARE_BITMAP(tx_slot, MAX_TX_BUF_NUM);
	काष्ठा समयr_list cleanup_समयr;
	spinlock_t tx_lock;
पूर्ण;

काष्ठा ath9k_htc_tx_ctl अणु
	u8 type; /* ATH9K_HTC_* */
	u8 epid;
	u8 txok;
	u8 sta_idx;
	अचिन्हित दीर्घ बारtamp;
पूर्ण;

अटल अंतरभूत काष्ठा ath9k_htc_tx_ctl *HTC_SKB_CB(काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);

	BUILD_BUG_ON(माप(काष्ठा ath9k_htc_tx_ctl) >
		     IEEE80211_TX_INFO_DRIVER_DATA_SIZE);
	वापस (काष्ठा ath9k_htc_tx_ctl *) &tx_info->driver_data;
पूर्ण

#अगर_घोषित CONFIG_ATH9K_HTC_DEBUGFS

#घोषणा TX_STAT_INC(c) (hअगर_dev->htc_handle->drv_priv->debug.tx_stats.c++)
#घोषणा TX_STAT_ADD(c, a) (hअगर_dev->htc_handle->drv_priv->debug.tx_stats.c += a)
#घोषणा RX_STAT_INC(c) (hअगर_dev->htc_handle->drv_priv->debug.skbrx_stats.c++)
#घोषणा RX_STAT_ADD(c, a) (hअगर_dev->htc_handle->drv_priv->debug.skbrx_stats.c += a)
#घोषणा CAB_STAT_INC   priv->debug.tx_stats.cab_queued++

#घोषणा TX_QSTAT_INC(q) (priv->debug.tx_stats.queue_stats[q]++)

व्योम ath9k_htc_err_stat_rx(काष्ठा ath9k_htc_priv *priv,
			   काष्ठा ath_rx_status *rs);

काष्ठा ath_tx_stats अणु
	u32 buf_queued;
	u32 buf_completed;
	u32 skb_queued;
	u32 skb_success;
	u32 skb_success_bytes;
	u32 skb_failed;
	u32 cab_queued;
	u32 queue_stats[IEEE80211_NUM_ACS];
पूर्ण;

काष्ठा ath_skbrx_stats अणु
	u32 skb_allocated;
	u32 skb_completed;
	u32 skb_completed_bytes;
	u32 skb_dropped;
पूर्ण;

काष्ठा ath9k_debug अणु
	काष्ठा dentry *debugfs_phy;
	काष्ठा ath_tx_stats tx_stats;
	काष्ठा ath_rx_stats rx_stats;
	काष्ठा ath_skbrx_stats skbrx_stats;
पूर्ण;

व्योम ath9k_htc_get_et_strings(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      u32 sset, u8 *data);
पूर्णांक ath9k_htc_get_et_sset_count(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर, पूर्णांक sset);
व्योम ath9k_htc_get_et_stats(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ethtool_stats *stats, u64 *data);
#अन्यथा

#घोषणा TX_STAT_INC(c) करो अणु पूर्ण जबतक (0)
#घोषणा TX_STAT_ADD(c, a) करो अणु पूर्ण जबतक (0)
#घोषणा RX_STAT_INC(c) करो अणु पूर्ण जबतक (0)
#घोषणा RX_STAT_ADD(c, a) करो अणु पूर्ण जबतक (0)
#घोषणा CAB_STAT_INC   करो अणु पूर्ण जबतक (0)

#घोषणा TX_QSTAT_INC(c) करो अणु पूर्ण जबतक (0)

अटल अंतरभूत व्योम ath9k_htc_err_stat_rx(काष्ठा ath9k_htc_priv *priv,
					 काष्ठा ath_rx_status *rs)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_HTC_DEBUGFS */

#घोषणा ATH_LED_PIN_DEF             1
#घोषणा ATH_LED_PIN_9287            10
#घोषणा ATH_LED_PIN_9271            15
#घोषणा ATH_LED_PIN_7010            12

#घोषणा BSTUCK_THRESHOLD 10

/*
 * Adjust these when the max. no of beaconing पूर्णांकerfaces is
 * increased.
 */
#घोषणा DEFAULT_SWBA_RESPONSE 40 /* in TUs */
#घोषणा MIN_SWBA_RESPONSE     10 /* in TUs */

काष्ठा htc_beacon अणु
	क्रमागत अणु
		OK,		/* no change needed */
		UPDATE,		/* update pending */
		COMMIT		/* beacon sent, commit change */
	पूर्ण updateslot;		/* slot समय update fsm */

	काष्ठा ieee80211_vअगर *bslot[ATH9K_HTC_MAX_BCN_VIF];
	u32 bmisscnt;
	u32 beaconq;
	पूर्णांक slotसमय;
	पूर्णांक slotupdate;
पूर्ण;

काष्ठा ath_btcoex अणु
	u32 bt_priority_cnt;
	अचिन्हित दीर्घ bt_priority_समय;
	पूर्णांक bt_stomp_type; /* Types of BT stomping */
	u32 btcoex_no_stomp;
	u32 btcoex_period;
	u32 btscan_no_stomp;
पूर्ण;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
व्योम ath9k_htc_init_btcoex(काष्ठा ath9k_htc_priv *priv, अक्षर *product);
व्योम ath9k_htc_start_btcoex(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_stop_btcoex(काष्ठा ath9k_htc_priv *priv);
#अन्यथा
अटल अंतरभूत व्योम ath9k_htc_init_btcoex(काष्ठा ath9k_htc_priv *priv, अक्षर *product)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_htc_start_btcoex(काष्ठा ath9k_htc_priv *priv)
अणु
पूर्ण
अटल अंतरभूत व्योम ath9k_htc_stop_btcoex(काष्ठा ath9k_htc_priv *priv)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */

#घोषणा OP_BT_PRIORITY_DETECTED    3
#घोषणा OP_BT_SCAN                 4
#घोषणा OP_TSF_RESET               6

क्रमागत htc_op_flags अणु
	HTC_FWFLAG_NO_RMW,
पूर्ण;

काष्ठा ath9k_htc_priv अणु
	काष्ठा device *dev;
	काष्ठा ieee80211_hw *hw;
	काष्ठा ath_hw *ah;
	काष्ठा htc_target *htc;
	काष्ठा wmi *wmi;

	u16 fw_version_major;
	u16 fw_version_minor;

	क्रमागत htc_endpoपूर्णांक_id wmi_cmd_ep;
	क्रमागत htc_endpoपूर्णांक_id beacon_ep;
	क्रमागत htc_endpoपूर्णांक_id cab_ep;
	क्रमागत htc_endpoपूर्णांक_id uapsd_ep;
	क्रमागत htc_endpoपूर्णांक_id mgmt_ep;
	क्रमागत htc_endpoपूर्णांक_id data_be_ep;
	क्रमागत htc_endpoपूर्णांक_id data_bk_ep;
	क्रमागत htc_endpoपूर्णांक_id data_vi_ep;
	क्रमागत htc_endpoपूर्णांक_id data_vo_ep;

	u8 vअगर_slot;
	u8 mon_vअगर_idx;
	u8 sta_slot;
	u8 vअगर_sta_pos[ATH9K_HTC_MAX_VIF];
	u8 num_ibss_vअगर;
	u8 num_mbss_vअगर;
	u8 num_sta_vअगर;
	u8 num_sta_assoc_vअगर;
	u8 num_ap_vअगर;

	u16 curtxघात;
	u16 txघातlimit;
	u16 nvअगरs;
	u16 nstations;
	bool rearm_ani;
	bool reconfig_beacon;
	अचिन्हित पूर्णांक rxfilter;
	अचिन्हित दीर्घ op_flags;
	अचिन्हित दीर्घ fw_flags;

	काष्ठा ath9k_hw_cal_data caldata;
	काष्ठा ath_spec_scan_priv spec_priv;

	spinlock_t beacon_lock;
	काष्ठा ath_beacon_config cur_beacon_conf;
	काष्ठा htc_beacon beacon;

	काष्ठा ath9k_htc_rx rx;
	काष्ठा ath9k_htc_tx tx;

	काष्ठा tasklet_काष्ठा swba_tasklet;
	काष्ठा tasklet_काष्ठा rx_tasklet;
	काष्ठा delayed_work ani_work;
	काष्ठा tasklet_काष्ठा tx_failed_tasklet;
	काष्ठा work_काष्ठा ps_work;
	काष्ठा work_काष्ठा fatal_work;

	काष्ठा mutex htc_pm_lock;
	अचिन्हित दीर्घ ps_usecount;
	bool ps_enabled;
	bool ps_idle;

#अगर_घोषित CONFIG_MAC80211_LEDS
	क्रमागत led_brightness brightness;
	bool led_रेजिस्टरed;
	अक्षर led_name[32];
	काष्ठा led_classdev led_cdev;
	काष्ठा work_काष्ठा led_work;
#पूर्ण_अगर

	पूर्णांक cabq;
	पूर्णांक hwq_map[IEEE80211_NUM_ACS];

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	काष्ठा ath_btcoex btcoex;
#पूर्ण_अगर

	काष्ठा delayed_work coex_period_work;
	काष्ठा delayed_work duty_cycle_work;
#अगर_घोषित CONFIG_ATH9K_HTC_DEBUGFS
	काष्ठा ath9k_debug debug;
#पूर्ण_अगर
	काष्ठा mutex mutex;
	काष्ठा ieee80211_vअगर *csa_vअगर;
पूर्ण;

अटल अंतरभूत व्योम ath_पढ़ो_cachesize(काष्ठा ath_common *common, पूर्णांक *csz)
अणु
	common->bus_ops->पढ़ो_cachesize(common, csz);
पूर्ण

व्योम ath9k_htc_reset(काष्ठा ath9k_htc_priv *priv);

व्योम ath9k_htc_assign_bslot(काष्ठा ath9k_htc_priv *priv,
			    काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_htc_हटाओ_bslot(काष्ठा ath9k_htc_priv *priv,
			    काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_htc_set_tsfadjust(काष्ठा ath9k_htc_priv *priv,
			     काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_htc_beaconq_config(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_beacon_config(काष्ठा ath9k_htc_priv *priv,
			     काष्ठा ieee80211_vअगर *vअगर);
व्योम ath9k_htc_beacon_reconfig(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_swba(काष्ठा ath9k_htc_priv *priv,
		    काष्ठा wmi_event_swba *swba);

व्योम ath9k_htc_rxep(व्योम *priv, काष्ठा sk_buff *skb,
		    क्रमागत htc_endpoपूर्णांक_id ep_id);
व्योम ath9k_htc_txep(व्योम *priv, काष्ठा sk_buff *skb, क्रमागत htc_endpoपूर्णांक_id ep_id,
		    bool txok);
व्योम ath9k_htc_beaconep(व्योम *drv_priv, काष्ठा sk_buff *skb,
			क्रमागत htc_endpoपूर्णांक_id ep_id, bool txok);

पूर्णांक ath9k_htc_update_cap_target(काष्ठा ath9k_htc_priv *priv,
				u8 enable_coex);
व्योम ath9k_htc_ani_work(काष्ठा work_काष्ठा *work);
व्योम ath9k_htc_start_ani(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_stop_ani(काष्ठा ath9k_htc_priv *priv);

पूर्णांक ath9k_tx_init(काष्ठा ath9k_htc_priv *priv);
पूर्णांक ath9k_htc_tx_start(काष्ठा ath9k_htc_priv *priv,
		       काष्ठा ieee80211_sta *sta,
		       काष्ठा sk_buff *skb, u8 slot, bool is_cab);
व्योम ath9k_tx_cleanup(काष्ठा ath9k_htc_priv *priv);
bool ath9k_htc_txq_setup(काष्ठा ath9k_htc_priv *priv, पूर्णांक subtype);
पूर्णांक ath9k_htc_cabq_setup(काष्ठा ath9k_htc_priv *priv);
पूर्णांक get_hw_qnum(u16 queue, पूर्णांक *hwq_map);
पूर्णांक ath_htc_txq_update(काष्ठा ath9k_htc_priv *priv, पूर्णांक qnum,
		       काष्ठा ath9k_tx_queue_info *qinfo);
व्योम ath9k_htc_check_stop_queues(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_check_wake_queues(काष्ठा ath9k_htc_priv *priv);
पूर्णांक ath9k_htc_tx_get_slot(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_tx_clear_slot(काष्ठा ath9k_htc_priv *priv, पूर्णांक slot);
व्योम ath9k_htc_tx_drain(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_txstatus(काष्ठा ath9k_htc_priv *priv, व्योम *wmi_event);
व्योम ath9k_tx_failed_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम ath9k_htc_tx_cleanup_समयr(काष्ठा समयr_list *t);
bool ath9k_htc_csa_is_finished(काष्ठा ath9k_htc_priv *priv);

पूर्णांक ath9k_rx_init(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_rx_cleanup(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_host_rx_init(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_rx_tasklet(काष्ठा tasklet_काष्ठा *t);
u32 ath9k_htc_calcrxfilter(काष्ठा ath9k_htc_priv *priv);

व्योम ath9k_htc_ps_wakeup(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_ps_restore(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_ps_work(काष्ठा work_काष्ठा *work);
bool ath9k_htc_setघातer(काष्ठा ath9k_htc_priv *priv,
			क्रमागत ath9k_घातer_mode mode);

व्योम ath9k_start_rfसमाप्त_poll(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_htc_rfसमाप्त_poll_state(काष्ठा ieee80211_hw *hw);

काष्ठा base_eep_header *ath9k_htc_get_eeprom_base(काष्ठा ath9k_htc_priv *priv);

#अगर_घोषित CONFIG_MAC80211_LEDS
व्योम ath9k_configure_leds(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_init_leds(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_deinit_leds(काष्ठा ath9k_htc_priv *priv);
व्योम ath9k_led_work(काष्ठा work_काष्ठा *work);
#अन्यथा
अटल अंतरभूत व्योम ath9k_configure_leds(काष्ठा ath9k_htc_priv *priv)
अणु
पूर्ण

अटल अंतरभूत व्योम ath9k_init_leds(काष्ठा ath9k_htc_priv *priv)
अणु
पूर्ण

अटल अंतरभूत व्योम ath9k_deinit_leds(काष्ठा ath9k_htc_priv *priv)
अणु
पूर्ण

अटल अंतरभूत व्योम ath9k_led_work(काष्ठा work_काष्ठा *work)
अणु
पूर्ण
#पूर्ण_अगर

पूर्णांक ath9k_htc_probe_device(काष्ठा htc_target *htc_handle, काष्ठा device *dev,
			   u16 devid, अक्षर *product, u32 drv_info);
व्योम ath9k_htc_disconnect_device(काष्ठा htc_target *htc_handle, bool hotunplug);
#अगर_घोषित CONFIG_PM
व्योम ath9k_htc_suspend(काष्ठा htc_target *htc_handle);
पूर्णांक ath9k_htc_resume(काष्ठा htc_target *htc_handle);
#पूर्ण_अगर
#अगर_घोषित CONFIG_ATH9K_HTC_DEBUGFS
पूर्णांक ath9k_htc_init_debug(काष्ठा ath_hw *ah);
व्योम ath9k_htc_deinit_debug(काष्ठा ath9k_htc_priv *priv);
#अन्यथा
अटल अंतरभूत पूर्णांक ath9k_htc_init_debug(काष्ठा ath_hw *ah) अणु वापस 0; पूर्ण;
अटल अंतरभूत व्योम ath9k_htc_deinit_debug(काष्ठा ath9k_htc_priv *priv)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_ATH9K_HTC_DEBUGFS */

#पूर्ण_अगर /* HTC_H */
