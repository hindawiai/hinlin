<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __STA_INFO_H_
#घोषणा __STA_INFO_H_


#घोषणा IBSS_START_MAC_ID	2
#घोषणा NUM_STA 32
#घोषणा NUM_ACL 16


/* अगर mode == 0, then the sta is allowed once the addr is hit. */
/* अगर mode == 1, then the sta is rejected once the addr is non-hit. */
काष्ठा rtw_wlan_acl_node अणु
        काष्ठा list_head		        list;
        u8       addr[ETH_ALEN];
        u8       valid;
पूर्ण;

/* mode = 0, disable */
/* mode = 1, accept unless in deny list */
/* mode =2, deny unless in accept list */
काष्ठा wlan_acl_pool अणु
	पूर्णांक mode;
	पूर्णांक num;
	काष्ठा rtw_wlan_acl_node aclnode[NUM_ACL];
	काष्ठा __queue	acl_node_q;
पूर्ण;

काष्ठा rssi_sta अणु
	s32	UndecoratedSmoothedPWDB;
	s32	UndecoratedSmoothedCCK;
	s32	UndecoratedSmoothedOFDM;
	u64	PacketMap;
	u8 ValidBit;
पूर्ण;

काष्ठा	stainfo_stats	अणु

	u64 rx_mgnt_pkts;
		u64 rx_beacon_pkts;
		u64 rx_probereq_pkts;
		u64 rx_probersp_pkts;
		u64 rx_probersp_bm_pkts;
		u64 rx_probersp_uo_pkts;
	u64 rx_ctrl_pkts;
	u64 rx_data_pkts;

	u64	last_rx_mgnt_pkts;
		u64 last_rx_beacon_pkts;
		u64 last_rx_probereq_pkts;
		u64 last_rx_probersp_pkts;
		u64 last_rx_probersp_bm_pkts;
		u64 last_rx_probersp_uo_pkts;
	u64	last_rx_ctrl_pkts;
	u64	last_rx_data_pkts;

	u64	rx_bytes;
	u64	rx_drops;

	u64	tx_pkts;
	u64	tx_bytes;
	u64  tx_drops;
पूर्ण;

काष्ठा sta_info अणु

	spinlock_t	lock;
	काष्ठा list_head	list; /* मुक्त_sta_queue */
	काष्ठा list_head	hash_list; /* sta_hash */
	काष्ठा adapter *padapter;

	काष्ठा sta_xmit_priv sta_xmitpriv;
	काष्ठा sta_recv_priv sta_recvpriv;

	काष्ठा __queue sleep_q;
	अचिन्हित पूर्णांक sleepq_len;

	uपूर्णांक state;
	uपूर्णांक aid;
	uपूर्णांक mac_id;
	uपूर्णांक qos_option;
	u8 hwaddr[ETH_ALEN];

	uपूर्णांक	ieee8021x_blocked;	/* 0: allowed, 1:blocked */
	uपूर्णांक	करोt118021XPrivacy; /* aes, tkip... */
	जोड़ Keytype	करोt11tkiptxmickey;
	जोड़ Keytype	करोt11tkiprxmickey;
	जोड़ Keytype	करोt118021x_UncstKey;
	जोड़ pn48		करोt11txpn;			/*  PN48 used क्रम Unicast xmit */
	जोड़ pn48		करोt11wtxpn;			/*  PN48 used क्रम Unicast mgmt xmit. */
	जोड़ pn48		करोt11rxpn;			/*  PN48 used क्रम Unicast recv. */


	u8 bssrateset[16];
	u32 bssratelen;
	s32  rssi;
	s32	संकेत_quality;

	u8 cts2self;
	u8 rtsen;

	u8 raid;
	u8 init_rate;
	u32 ra_mask;
	u8 wireless_mode;	/*  NETWORK_TYPE */
	u8 bw_mode;

	u8 ldpc;
	u8 stbc;

	काष्ठा stainfo_stats sta_stats;

	/* क्रम A-MPDU TX, ADDBA समयout check */
	काष्ठा समयr_list addba_retry_समयr;

	/* क्रम A-MPDU Rx reordering buffer control */
	काष्ठा recv_reorder_ctrl recvreorder_ctrl[16];

	/* क्रम A-MPDU Tx */
	/* अचिन्हित अक्षर 	ampdu_txen_biपंचांगap; */
	u16 BA_starting_seqctrl[16];


	काष्ठा ht_priv htpriv;

	/* Notes: */
	/* STA_Mode: */
	/* curr_network(mlme_priv/security_priv/qos/ht) + sta_info: (STA & AP) CAP/INFO */
	/* scan_q: AP CAP/INFO */

	/* AP_Mode: */
	/* curr_network(mlme_priv/security_priv/qos/ht) : AP CAP/INFO */
	/* sta_info: (AP & STA) CAP/INFO */

	काष्ठा list_head asoc_list;
	काष्ठा list_head auth_list;

	अचिन्हित पूर्णांक expire_to;
	अचिन्हित पूर्णांक auth_seq;
	अचिन्हित पूर्णांक authalg;
	अचिन्हित अक्षर chg_txt[128];

	u16 capability;
	पूर्णांक flags;

	पूर्णांक करोt8021xalg;/* 0:disable, 1:psk, 2:802.1x */
	पूर्णांक wpa_psk;/* 0:disable, bit(0): WPA, bit(1):WPA2 */
	पूर्णांक wpa_group_cipher;
	पूर्णांक wpa2_group_cipher;
	पूर्णांक wpa_pairwise_cipher;
	पूर्णांक wpa2_pairwise_cipher;

	u8 bpairwise_key_installed;

	u8 wpa_ie[32];

	u8 nonerp_set;
	u8 no_लघु_slot_समय_set;
	u8 no_लघु_preamble_set;
	u8 no_ht_gf_set;
	u8 no_ht_set;
	u8 ht_20mhz_set;

	अचिन्हित पूर्णांक tx_ra_biपंचांगap;
	u8 qos_info;

	u8 max_sp_len;
	u8 uapsd_bk;/* BIT(0): Delivery enabled, BIT(1): Trigger enabled */
	u8 uapsd_be;
	u8 uapsd_vi;
	u8 uapsd_vo;

	u8 has_legacy_ac;
	अचिन्हित पूर्णांक sleepq_ac_len;

	u8 under_exist_checking;

	u8 keep_alive_trycnt;

	u8 *passoc_req;
	u32 assoc_req_len;

	/* क्रम DM */
	काष्ठा rssi_sta	 rssi_stat;

	/* ODM_STA_INFO_T */
	/*  ================ODM Relative Info ======================= */
	/*  Please be care, करोnt declare too much काष्ठाure here. It will cost memory * STA support num. */
	/*  */
	/*  */
	/*  2011/10/20 MH Add क्रम ODM STA info. */
	/*  */
	/*  Driver Write */
	u8 bValid;				/*  record the sta status link or not? */
	u8 IOTPeer;			/*  Enum value.	HT_IOT_PEER_E */
	/*  ODM Write */
	/* 1 PHY_STATUS_INFO */
	u8 RSSI_Path[4];		/*  */
	u8 RSSI_Ave;
	u8 RXEVM[4];
	u8 RXSNR[4];

	u8 rssi_level;			/* क्रम Refresh RA mask */
	/*  ODM Write */
	/* 1 TX_INFO (may changed by IC) */
	/* TX_INFO_T		pTxInfo;		 Define in IC folder. Move lower layer. */
	/*  */
	/*  ================ODM Relative Info ======================= */
	/*  */

	/* To store the sequence number of received management frame */
	u16 RxMgmtFrameSeqNum;
पूर्ण;

#घोषणा sta_rx_pkts(sta) \
	(sta->sta_stats.rx_mgnt_pkts \
	+ sta->sta_stats.rx_ctrl_pkts \
	+ sta->sta_stats.rx_data_pkts)

#घोषणा sta_last_rx_pkts(sta) \
	(sta->sta_stats.last_rx_mgnt_pkts \
	+ sta->sta_stats.last_rx_ctrl_pkts \
	+ sta->sta_stats.last_rx_data_pkts)

#घोषणा sta_rx_data_pkts(sta) \
	(sta->sta_stats.rx_data_pkts)

#घोषणा sta_last_rx_data_pkts(sta) \
	(sta->sta_stats.last_rx_data_pkts)

#घोषणा sta_rx_mgnt_pkts(sta) \
	(sta->sta_stats.rx_mgnt_pkts)

#घोषणा sta_last_rx_mgnt_pkts(sta) \
	(sta->sta_stats.last_rx_mgnt_pkts)

#घोषणा sta_rx_beacon_pkts(sta) \
	(sta->sta_stats.rx_beacon_pkts)

#घोषणा sta_last_rx_beacon_pkts(sta) \
	(sta->sta_stats.last_rx_beacon_pkts)

#घोषणा sta_rx_probereq_pkts(sta) \
	(sta->sta_stats.rx_probereq_pkts)

#घोषणा sta_last_rx_probereq_pkts(sta) \
	(sta->sta_stats.last_rx_probereq_pkts)

#घोषणा sta_rx_probersp_pkts(sta) \
	(sta->sta_stats.rx_probersp_pkts)

#घोषणा sta_last_rx_probersp_pkts(sta) \
	(sta->sta_stats.last_rx_probersp_pkts)

#घोषणा sta_rx_probersp_bm_pkts(sta) \
	(sta->sta_stats.rx_probersp_bm_pkts)

#घोषणा sta_last_rx_probersp_bm_pkts(sta) \
	(sta->sta_stats.last_rx_probersp_bm_pkts)

#घोषणा sta_rx_probersp_uo_pkts(sta) \
	(sta->sta_stats.rx_probersp_uo_pkts)

#घोषणा sta_last_rx_probersp_uo_pkts(sta) \
	(sta->sta_stats.last_rx_probersp_uo_pkts)

#घोषणा sta_update_last_rx_pkts(sta) \
	करो अणु \
		sta->sta_stats.last_rx_mgnt_pkts = sta->sta_stats.rx_mgnt_pkts; \
		sta->sta_stats.last_rx_beacon_pkts = sta->sta_stats.rx_beacon_pkts; \
		sta->sta_stats.last_rx_probereq_pkts = sta->sta_stats.rx_probereq_pkts; \
		sta->sta_stats.last_rx_probersp_pkts = sta->sta_stats.rx_probersp_pkts; \
		sta->sta_stats.last_rx_probersp_bm_pkts = sta->sta_stats.rx_probersp_bm_pkts; \
		sta->sta_stats.last_rx_probersp_uo_pkts = sta->sta_stats.rx_probersp_uo_pkts; \
		sta->sta_stats.last_rx_ctrl_pkts = sta->sta_stats.rx_ctrl_pkts; \
		sta->sta_stats.last_rx_data_pkts = sta->sta_stats.rx_data_pkts; \
	पूर्ण जबतक (0)

#घोषणा STA_RX_PKTS_ARG(sta) \
	sta->sta_stats.rx_mgnt_pkts \
	, sta->sta_stats.rx_ctrl_pkts \
	, sta->sta_stats.rx_data_pkts

#घोषणा STA_LAST_RX_PKTS_ARG(sta) \
	sta->sta_stats.last_rx_mgnt_pkts \
	, sta->sta_stats.last_rx_ctrl_pkts \
	, sta->sta_stats.last_rx_data_pkts

#घोषणा STA_RX_PKTS_DIFF_ARG(sta) \
	sta->sta_stats.rx_mgnt_pkts - sta->sta_stats.last_rx_mgnt_pkts \
	, sta->sta_stats.rx_ctrl_pkts - sta->sta_stats.last_rx_ctrl_pkts \
	, sta->sta_stats.rx_data_pkts - sta->sta_stats.last_rx_data_pkts

#घोषणा STA_PKTS_FMT "(m:%llu, c:%llu, d:%llu)"

काष्ठा	sta_priv अणु

	u8 *pallocated_stainfo_buf;
	u8 *pstainfo_buf;
	काष्ठा __queue	मुक्त_sta_queue;

	spinlock_t sta_hash_lock;
	काष्ठा list_head   sta_hash[NUM_STA];
	पूर्णांक asoc_sta_count;
	काष्ठा __queue sleep_q;
	काष्ठा __queue wakeup_q;

	काष्ठा adapter *padapter;

	काष्ठा list_head asoc_list;
	काष्ठा list_head auth_list;
	spinlock_t asoc_list_lock;
	spinlock_t auth_list_lock;
	u8 asoc_list_cnt;
	u8 auth_list_cnt;

	अचिन्हित पूर्णांक auth_to;  /* sec, समय to expire in authenticating. */
	अचिन्हित पूर्णांक assoc_to; /* sec, समय to expire beक्रमe associating. */
	अचिन्हित पूर्णांक expire_to; /* sec , समय to expire after associated. */

	/* poपूर्णांकers to STA info; based on allocated AID or शून्य अगर AID मुक्त
	 * AID is in the range 1-2007, so sta_aid[0] corresponders to AID 1
	 * and so on
	 */
	काष्ठा sta_info *sta_aid[NUM_STA];

	u16 sta_dz_biपंचांगap;/* only support क्रम 15 stations, aid biपंचांगap क्रम sleeping stations. */
	u16 tim_biपंचांगap;/* only support 15 stations, aid = 0~15 mapping bit0~bit15 */

	u16 max_num_sta;

	काष्ठा wlan_acl_pool acl_list;
पूर्ण;


अटल अंतरभूत u32 wअगरi_mac_hash(u8 *mac)
अणु
        u32 x;

        x = mac[0];
        x = (x << 2) ^ mac[1];
        x = (x << 2) ^ mac[2];
        x = (x << 2) ^ mac[3];
        x = (x << 2) ^ mac[4];
        x = (x << 2) ^ mac[5];

        x ^= x >> 8;
        x  = x & (NUM_STA - 1);

        वापस x;
पूर्ण


बाह्य u32 _rtw_init_sta_priv(काष्ठा sta_priv *pstapriv);
बाह्य u32 _rtw_मुक्त_sta_priv(काष्ठा sta_priv *pstapriv);

#घोषणा stainfo_offset_valid(offset) (offset < NUM_STA && offset >= 0)
पूर्णांक rtw_stainfo_offset(काष्ठा sta_priv *stapriv, काष्ठा sta_info *sta);
काष्ठा sta_info *rtw_get_stainfo_by_offset(काष्ठा sta_priv *stapriv, पूर्णांक offset);

बाह्य काष्ठा sta_info *rtw_alloc_stainfo(काष्ठा	sta_priv *pstapriv, u8 *hwaddr);
बाह्य u32 rtw_मुक्त_stainfo(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
बाह्य व्योम rtw_मुक्त_all_stainfo(काष्ठा adapter *padapter);
बाह्य काष्ठा sta_info *rtw_get_stainfo(काष्ठा sta_priv *pstapriv, u8 *hwaddr);
बाह्य u32 rtw_init_bcmc_stainfo(काष्ठा adapter *padapter);
बाह्य काष्ठा sta_info *rtw_get_bcmc_stainfo(काष्ठा adapter *padapter);
बाह्य u8 rtw_access_ctrl(काष्ठा adapter *padapter, u8 *mac_addr);

#पूर्ण_अगर /* _STA_INFO_H_ */
