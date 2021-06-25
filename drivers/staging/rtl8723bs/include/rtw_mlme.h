<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_MLME_H_
#घोषणा __RTW_MLME_H_


#घोषणा	MAX_BSS_CNT	128
/* define   MAX_JOIN_TIMEOUT	2000 */
/* define   MAX_JOIN_TIMEOUT	2500 */
#घोषणा   MAX_JOIN_TIMEOUT	6500

/* 	Commented by Albert 20101105 */
/* 	Increase the scanning समयout because of increasing the SURVEY_TO value. */

#घोषणा		SCANNING_TIMEOUT	8000

#अगर_घोषित PALTFORM_OS_WINCE
#घोषणा	SCANQUEUE_LIFETIME 12000000 /*  unit:us */
#अन्यथा
#घोषणा	SCANQUEUE_LIFETIME 20000 /*  20sec, unit:msec */
#पूर्ण_अगर

#घोषणा WIFI_शून्य_STATE		0x00000000
#घोषणा WIFI_ASOC_STATE		0x00000001		/*  Under Linked state... */
#घोषणा WIFI_REASOC_STATE	0x00000002
#घोषणा WIFI_SLEEP_STATE	0x00000004
#घोषणा WIFI_STATION_STATE	0x00000008
#घोषणा	WIFI_AP_STATE			0x00000010
#घोषणा	WIFI_ADHOC_STATE		0x00000020
#घोषणा WIFI_ADHOC_MASTER_STATE	0x00000040
#घोषणा WIFI_UNDER_LINKING	0x00000080

#घोषणा WIFI_UNDER_WPS			0x00000100
/* define	WIFI_UNDER_CMD			0x00000200 */
/* define	WIFI_UNDER_P2P			0x00000400 */
#घोषणा	WIFI_STA_ALIVE_CHK_STATE	0x00000400
#घोषणा	WIFI_SITE_MONITOR			0x00000800		/* to indicate the station is under site surveying */
#अगर_घोषित WDS
#घोषणा	WIFI_WDS				0x00001000
#घोषणा	WIFI_WDS_RX_BEACON	0x00002000		/*  alपढ़ोy rx WDS AP beacon */
#पूर्ण_अगर
#अगर_घोषित AUTO_CONFIG
#घोषणा	WIFI_AUTOCONF			0x00004000
#घोषणा	WIFI_AUTOCONF_IND	0x00008000
#पूर्ण_अगर

/**
*  ========== P2P Section Start ===============
#घोषणा	WIFI_P2P_LISTEN_STATE		0x00010000
#घोषणा	WIFI_P2P_GROUP_FORMATION_STATE		0x00020000
  ========== P2P Section End ===============
*/

/* अगरdef UNDER_MPTEST */
#घोषणा	WIFI_MP_STATE							0x00010000
#घोषणा	WIFI_MP_CTX_BACKGROUND				0x00020000	/*  in continuous tx background */
#घोषणा	WIFI_MP_CTX_ST						0x00040000	/*  in continuous tx with single-tone */
#घोषणा	WIFI_MP_CTX_BACKGROUND_PENDING	0x00080000	/*  pending in continuous tx background due to out of skb */
#घोषणा	WIFI_MP_CTX_CCK_HW					0x00100000	/*  in continuous tx */
#घोषणा	WIFI_MP_CTX_CCK_CS					0x00200000	/*  in continuous tx with carrier suppression */
#घोषणा   WIFI_MP_LPBK_STATE					0x00400000
/* endअगर */

/* define _FW_UNDER_CMD		WIFI_UNDER_CMD */
#घोषणा _FW_UNDER_LINKING	WIFI_UNDER_LINKING
#घोषणा _FW_LINKED			WIFI_ASOC_STATE
#घोषणा _FW_UNDER_SURVEY	WIFI_SITE_MONITOR


क्रमागत अणु
 करोt11AuthAlgrthm_Open = 0,
 करोt11AuthAlgrthm_Shared,
 करोt11AuthAlgrthm_8021X,
 करोt11AuthAlgrthm_Auto,
 करोt11AuthAlgrthm_WAPI,
 करोt11AuthAlgrthm_MaxNum
पूर्ण;

/*  Scan type including active and passive scan. */
क्रमागत rt_scan_type अणु
	SCAN_PASSIVE,
	SCAN_ACTIVE,
	SCAN_MIX,
पूर्ण;

क्रमागत अणु
	GHZ24_50 = 0,
	GHZ_50,
	GHZ_24,
	GHZ_MAX,
पूर्ण;

#घोषणा rtw_band_valid(band) ((band) >= GHZ24_50 && (band) < GHZ_MAX)

/*

there are several "locks" in mlme_priv,
since mlme_priv is a shared resource between many thपढ़ोs,
like ISR/Call-Back functions, the OID handlers, and even समयr functions.


Each काष्ठा __queue has its own locks, alपढ़ोy.
Other items are रक्षित by mlme_priv.lock.

To aव्योम possible dead lock, any thपढ़ो trying to modअगरiying mlme_priv
SHALL not lock up more than one locks at a समय!

*/


#घोषणा traffic_threshold	10
#घोषणा	traffic_scan_period	500

काष्ठा sitesurvey_ctrl अणु
	u64	last_tx_pkts;
	uपूर्णांक	last_rx_pkts;
	चिन्हित पूर्णांक	traffic_busy;
	काष्ठा समयr_list	sitesurvey_ctrl_समयr;
पूर्ण;

काष्ठा rt_link_detect_t अणु
	u32 			NumTxOkInPeriod;
	u32 			NumRxOkInPeriod;
	u32 			NumRxUnicastOkInPeriod;
	bool			bBusyTraffic;
	bool			bTxBusyTraffic;
	bool			bRxBusyTraffic;
	bool			bHigherBusyTraffic; /*  For पूर्णांकerrupt migration purpose. */
	bool			bHigherBusyRxTraffic; /*  We may disable Tx पूर्णांकerrupt according as Rx traffic. */
	bool			bHigherBusyTxTraffic; /*  We may disable Tx पूर्णांकerrupt according as Tx traffic. */
	/* u8 TrafficBusyState; */
	u8 TrafficTransitionCount;
	u32 LowPowerTransitionCount;
पूर्ण;

काष्ठा profile_info अणु
	u8 ssidlen;
	u8 ssid[WLAN_SSID_MAXLEN];
	u8 peermac[ETH_ALEN];
पूर्ण;

काष्ठा tx_invite_req_info अणु
	u8 			token;
	u8 			benable;
	u8			go_ssid[WLAN_SSID_MAXLEN];
	u8 			ssidlen;
	u8			go_bssid[ETH_ALEN];
	u8			peer_macaddr[ETH_ALEN];
	u8 			operating_ch;	/* 	This inक्रमmation will be set by using the p2p_set op_ch =x */
	u8 			peer_ch;		/* 	The listen channel क्रम peer P2P device */

पूर्ण;

काष्ठा tx_invite_resp_info अणु
	u8 			token;	/* 	Used to record the dialog token of p2p invitation request frame. */
पूर्ण;

काष्ठा tx_provdisc_req_info अणु
	u16 				wps_config_method_request;	/* 	Used when sending the provisioning request frame */
	u16 				peer_channel_num[2];		/* 	The channel number which the receiver stands. */
	काष्ठा ndis_802_11_ssid	ssid;
	u8			peerDevAddr[ETH_ALEN];		/*	Peer device address */
	u8			peerIFAddr[ETH_ALEN];		/*	Peer पूर्णांकerface address */
	u8 			benable;					/* 	This provision discovery request frame is trigger to send or not */
पूर्ण;

काष्ठा rx_provdisc_req_info अणु	/* When peer device issue prov_disc_req first, we should store the following inक्रमmation */
	u8			peerDevAddr[ETH_ALEN];		/*	Peer device address */
	u8 			strconfig_method_desc_of_prov_disc_req[4];	/* 	description क्रम the config method located in the provisioning discovery request frame. */
																	/* 	The UI must know this inक्रमmation to know which config method the remote p2p device is requiring. */
पूर्ण;

काष्ठा tx_nego_req_info अणु
	u16 				peer_channel_num[2];		/* 	The channel number which the receiver stands. */
	u8			peerDevAddr[ETH_ALEN];		/*	Peer device address */
	u8 			benable;					/* 	This negotiation request frame is trigger to send or not */
पूर्ण;

काष्ठा group_id_info अणु
	u8			go_device_addr[ETH_ALEN];	/*	The GO's device address of this P2P group */
	u8			ssid[WLAN_SSID_MAXLEN];	/*	The SSID of this P2P group */
पूर्ण;

काष्ठा scan_limit_info अणु
	u8 			scan_op_ch_only;			/* 	When this flag is set, the driver should just scan the operation channel */
	u8 			operation_ch[2];				/* 	Store the operation channel of invitation request frame */
पूर्ण;

काष्ठा wअगरidirect_info अणु
	काष्ठा adapter				*padapter;
	काष्ठा समयr_list					find_phase_समयr;
	काष्ठा समयr_list					restore_p2p_state_समयr;

	/* 	Used to करो the scanning. After confirming the peer is availalble, the driver transmits the P2P frame to peer. */
	काष्ठा समयr_list					pre_tx_scan_समयr;
	काष्ठा समयr_list					reset_ch_sitesurvey;
	काष्ठा समयr_list					reset_ch_sitesurvey2;	/* 	Just क्रम resetting the scan limit function by using p2p nego */
	काष्ठा tx_provdisc_req_info tx_prov_disc_info;
	काष्ठा rx_provdisc_req_info rx_prov_disc_info;
	काष्ठा tx_invite_req_info invitereq_info;
	काष्ठा profile_info		profileinfo[P2P_MAX_PERSISTENT_GROUP_NUM];	/*	Store the profile inक्रमmation of persistent group */
	काष्ठा tx_invite_resp_info inviteresp_info;
	काष्ठा tx_nego_req_info nego_req_info;
	काष्ठा group_id_info 	groupid_info;	/* 	Store the group id inक्रमmation when करोing the group negotiation handshake. */
	काष्ठा scan_limit_info 	rx_invitereq_info;	/* 	Used क्रम get the limit scan channel from the Invitation procedure */
	काष्ठा scan_limit_info 	p2p_info;		/* 	Used क्रम get the limit scan channel from the P2P negotiation handshake */
	क्रमागत p2p_role			role;
	क्रमागत p2p_state			pre_p2p_state;
	क्रमागत p2p_state			p2p_state;
	u8 				device_addr[ETH_ALEN];	/* 	The device address should be the mac address of this device. */
	u8 				पूर्णांकerface_addr[ETH_ALEN];
	u8 				social_chan[4];
	u8 				listen_channel;
	u8 				operating_channel;
	u8 				listen_dwell;		/* 	This value should be between 1 and 3 */
	u8 				support_rate[8];
	u8 				p2p_wildcard_ssid[P2P_WILDCARD_SSID_LEN];
	u8 				पूर्णांकent;		/* 	should only include the पूर्णांकent value. */
	u8				p2p_peer_पूर्णांकerface_addr[ETH_ALEN];
	u8				p2p_peer_device_addr[ETH_ALEN];
	u8 				peer_पूर्णांकent;	/* 	Included the पूर्णांकent value and tie अवरोधer value. */
	u8				device_name[WPS_MAX_DEVICE_NAME_LEN];	/*	Device name क्रम displaying on searching device screen */
	u8 				device_name_len;
	u8 				profileindex;	/* 	Used to poपूर्णांक to the index of profileinfo array */
	u8 				peer_operating_ch;
	u8 				find_phase_state_exchange_cnt;
	u16 					device_password_id_क्रम_nego;	/* 	The device password ID क्रम group negotiation */
	u8 				negotiation_dialog_token;
	u8				nego_ssid[WLAN_SSID_MAXLEN];	/*	SSID inक्रमmation क्रम group negotiation */
	u8 				nego_ssidlen;
	u8 				p2p_group_ssid[WLAN_SSID_MAXLEN];
	u8 				p2p_group_ssid_len;
	u8 				persistent_supported;		/* 	Flag to know the persistent function should be supported or not. */
														/* 	In the Sigma test, the Sigma will provide this enable from the sta_set_p2p CAPI. */
														/* 	0: disable */
														/* 	1: enable */
	u8 				session_available;			/* 	Flag to set the WFD session available to enable or disable "by Sigma" */
														/* 	In the Sigma test, the Sigma will disable the session available by using the sta_preset CAPI. */
														/* 	0: disable */
														/* 	1: enable */

	u8 				wfd_tdls_enable;			/* 	Flag to enable or disable the TDLS by WFD Sigma */
														/* 	0: disable */
														/* 	1: enable */
	u8 				wfd_tdls_weaksec;			/* 	Flag to enable or disable the weak security function क्रम TDLS by WFD Sigma */
														/* 	0: disable */
														/* 	In this हाल, the driver can't issue the tdsl setup request frame. */
														/* 	1: enable */
														/* 	In this हाल, the driver can issue the tdls setup request frame */
														/* 	even the current security is weak security. */

	क्रमागत	p2p_wpsinfo		ui_got_wps_info;			/* 	This field will store the WPS value (PIN value or PBC) that UI had got from the user. */
	u16 					supported_wps_cm;			/* 	This field describes the WPS config method which this driver supported. */
														/* 	The value should be the combination of config method defined in page104 of WPS v2.0 spec. */
	u8 				बाह्यal_uuid;				/*  UUID flag */
	u8 				uuid[16];					/*  UUID */
	uपूर्णांक						channel_list_attr_len;		/* 	This field will contain the length of body of P2P Channel List attribute of group negotitation response frame. */
	u8 				channel_list_attr[100];		/* 	This field will contain the body of P2P Channel List attribute of group negotitation response frame. */
														/* 	We will use the channel_cnt and channel_list fields when स्थिरructing the group negotitation confirm frame. */
	u8 				driver_पूर्णांकerface;			/* 	Indicate DRIVER_WEXT or DRIVER_CFG80211 */
पूर्ण;

काष्ठा tdls_ss_record अणु	/* संकेत strength record */
	u8 macaddr[ETH_ALEN];
	u8 rx_pwd_ba11;
	u8 is_tdls_sta;	/*  true: direct link sta, false: अन्यथा */
पूर्ण;

/* used क्रम mlme_priv.roam_flags */
क्रमागत अणु
	RTW_ROAM_ON_EXPIRED = BIT0,
	RTW_ROAM_ON_RESUME = BIT1,
	RTW_ROAM_ACTIVE = BIT2,
पूर्ण;

काष्ठा mlme_priv अणु

	spinlock_t	lock;
	चिन्हित पूर्णांक	fw_state;	/* shall we protect this variable? maybe not necessarily... */
	u8 bScanInProcess;
	u8 to_join; /* flag */

	u8 to_roam; /* roaming trying बार */
	काष्ठा wlan_network *roam_network; /* the target of active roam */
	u8 roam_flags;
	u8 roam_rssi_dअगरf_th; /* rssi dअगरference threshold क्रम active scan candidate selection */
	u32 roam_scan_पूर्णांक_ms; /* scan पूर्णांकerval क्रम active roam */
	u32 roam_scanr_exp_ms; /* scan result expire समय in ms  क्रम roam */
	u8 roam_tgt_addr[ETH_ALEN]; /* request to roam to speicअगरic target without other consideration */

	u8 *nic_hdl;

	u8 not_indic_disco;
	काष्ठा list_head		*pscanned;
	काष्ठा __queue	मुक्त_bss_pool;
	काष्ठा __queue	scanned_queue;
	u8 *मुक्त_bss_buf;
	u32 num_of_scanned;

	काष्ठा ndis_802_11_ssid	assoc_ssid;
	u8 assoc_bssid[6];

	काष्ठा wlan_network	cur_network;
	काष्ठा wlan_network *cur_network_scanned;

	/* uपूर्णांक wireless_mode; no used, हटाओ it */

	u32 स्वतः_scan_पूर्णांक_ms;

	काष्ठा समयr_list assoc_समयr;

	uपूर्णांक assoc_by_bssid;
	uपूर्णांक assoc_by_rssi;

	काष्ठा समयr_list scan_to_समयr; /*  driver itself handles scan_समयout status. */
	अचिन्हित दीर्घ scan_start_समय; /*  used to evaluate the समय spent in scanning */

	काष्ठा समयr_list set_scan_deny_समयr;
	atomic_t set_scan_deny; /* 0: allowed, 1: deny */

	काष्ठा qos_priv qospriv;

	/* Number of non-HT AP/stations */
	पूर्णांक num_sta_no_ht;

	/* Number of HT AP/stations 20 MHz */
	/* पूर्णांक num_sta_ht_20mhz; */


	पूर्णांक num_FortyMHzIntolerant;

	काष्ठा ht_priv htpriv;

	काष्ठा rt_link_detect_t	LinkDetectInfo;
	काष्ठा समयr_list	dynamic_chk_समयr; /* dynamic/periodic check समयr */

	u8 acm_mask; /*  क्रम wmm acm mask */
	u8 ChannelPlan;
	क्रमागत rt_scan_type	scan_mode; /*  active: 1, passive: 0 */

	u8 *wps_probe_req_ie;
	u32 wps_probe_req_ie_len;

	/* Number of associated Non-ERP stations (i.e., stations using 802.11b
	 * in 802.11g BSS) */
	पूर्णांक num_sta_non_erp;

	/* Number of associated stations that करो not support Short Slot Time */
	पूर्णांक num_sta_no_लघु_slot_समय;

	/* Number of associated stations that करो not support Short Preamble */
	पूर्णांक num_sta_no_लघु_preamble;

	पूर्णांक olbc; /* Overlapping Legacy BSS Condition */

	/* Number of HT associated stations that करो not support greenfield */
	पूर्णांक num_sta_ht_no_gf;

	/* Number of associated non-HT stations */
	/* पूर्णांक num_sta_no_ht; */

	/* Number of HT associated stations 20 MHz */
	पूर्णांक num_sta_ht_20mhz;

	/* Overlapping BSS inक्रमmation */
	पूर्णांक olbc_ht;

	u16 ht_op_mode;

	u8 *assoc_req;
	u32 assoc_req_len;
	u8 *assoc_rsp;
	u32 assoc_rsp_len;

	u8 *wps_beacon_ie;
	/* u8 *wps_probe_req_ie; */
	u8 *wps_probe_resp_ie;
	u8 *wps_assoc_resp_ie; /*  क्रम CONFIG_IOCTL_CFG80211, this IE could include p2p ie / wfd ie */

	u32 wps_beacon_ie_len;
	/* u32 wps_probe_req_ie_len; */
	u32 wps_probe_resp_ie_len;
	u32 wps_assoc_resp_ie_len; /*  क्रम CONFIG_IOCTL_CFG80211, this IE len could include p2p ie / wfd ie */

	u8 *p2p_beacon_ie;
	u8 *p2p_probe_req_ie;
	u8 *p2p_probe_resp_ie;
	u8 *p2p_go_probe_resp_ie; /* क्रम GO */
	u8 *p2p_assoc_req_ie;

	u32 p2p_beacon_ie_len;
	u32 p2p_probe_req_ie_len;
	u32 p2p_probe_resp_ie_len;
	u32 p2p_go_probe_resp_ie_len; /* क्रम GO */
	u32 p2p_assoc_req_ie_len;

	spinlock_t	bcn_update_lock;
	u8 update_bcn;

	u8 NumOfBcnInfoChkFail;
	अचिन्हित दीर्घ	समयBcnInfoChkStart;
पूर्ण;

#घोषणा rtw_mlme_set_स्वतः_scan_पूर्णांक(adapter, ms) \
	करो अणु \
		adapter->mlmepriv.स्वतः_scan_पूर्णांक_ms = ms; \
	जबतक (0)

व्योम rtw_mlme_reset_स्वतः_scan_पूर्णांक(काष्ठा adapter *adapter);

काष्ठा hostapd_priv अणु
	काष्ठा adapter *padapter;
पूर्ण;

बाह्य पूर्णांक hostapd_mode_init(काष्ठा adapter *padapter);
बाह्य व्योम hostapd_mode_unload(काष्ठा adapter *padapter);

बाह्य व्योम rtw_joinbss_event_prehandle(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_survey_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_surveyकरोne_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_joinbss_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_stassoc_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_stadel_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_atimकरोne_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_cpwm_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
बाह्य व्योम rtw_wmm_event_callback(काष्ठा adapter *padapter, u8 *pbuf);

बाह्य व्योम rtw_join_समयout_handler(काष्ठा समयr_list *t);
बाह्य व्योम _rtw_scan_समयout_handler(काष्ठा समयr_list *t);

पूर्णांक event_thपढ़ो(व्योम *context);

बाह्य व्योम rtw_मुक्त_network_queue(काष्ठा adapter *adapter, u8 isमुक्तall);
बाह्य पूर्णांक rtw_init_mlme_priv(काष्ठा adapter *adapter);/*  (काष्ठा mlme_priv *pmlmepriv); */

बाह्य व्योम rtw_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv);


बाह्य चिन्हित पूर्णांक rtw_select_and_join_from_scanned_queue(काष्ठा mlme_priv *pmlmepriv);
बाह्य चिन्हित पूर्णांक rtw_set_key(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv, चिन्हित पूर्णांक keyid, u8 set_tx, bool enqueue);
बाह्य चिन्हित पूर्णांक rtw_set_auth(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv);

अटल अंतरभूत u8 *get_bssid(काष्ठा mlme_priv *pmlmepriv)
अणु	/* अगर sta_mode:pmlmepriv->cur_network.network.MacAddress => bssid */
	/*  अगर adhoc_mode:pmlmepriv->cur_network.network.MacAddress => ibss mac address */
	वापस pmlmepriv->cur_network.network.MacAddress;
पूर्ण

अटल अंतरभूत चिन्हित पूर्णांक check_fwstate(काष्ठा mlme_priv *pmlmepriv, चिन्हित पूर्णांक state)
अणु
	अगर (pmlmepriv->fw_state & state)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत चिन्हित पूर्णांक get_fwstate(काष्ठा mlme_priv *pmlmepriv)
अणु
	वापस pmlmepriv->fw_state;
पूर्ण

/*
 * No Limit on the calling context,
 * thereक्रमe set it to be the critical section...
 *
 * ### NOTE:#### (!!!!)
 * MUST TAKE CARE THAT BEFORE CALLING THIS FUNC, YOU SHOULD HAVE LOCKED pmlmepriv->lock
 */
अटल अंतरभूत व्योम set_fwstate(काष्ठा mlme_priv *pmlmepriv, चिन्हित पूर्णांक state)
अणु
	pmlmepriv->fw_state |= state;
	/* FOR HW पूर्णांकegration */
	अगर (state == _FW_UNDER_SURVEY)
		pmlmepriv->bScanInProcess = true;
पूर्ण

अटल अंतरभूत व्योम _clr_fwstate_(काष्ठा mlme_priv *pmlmepriv, चिन्हित पूर्णांक state)
अणु
	pmlmepriv->fw_state &= ~state;
	/* FOR HW पूर्णांकegration */
	अगर (state == _FW_UNDER_SURVEY)
		pmlmepriv->bScanInProcess = false;
पूर्ण

/*
 * No Limit on the calling context,
 * thereक्रमe set it to be the critical section...
 */
अटल अंतरभूत व्योम clr_fwstate(काष्ठा mlme_priv *pmlmepriv, चिन्हित पूर्णांक state)
अणु
	spin_lock_bh(&pmlmepriv->lock);
	अगर (check_fwstate(pmlmepriv, state) == true)
		pmlmepriv->fw_state ^= state;
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

अटल अंतरभूत व्योम set_scanned_network_val(काष्ठा mlme_priv *pmlmepriv, चिन्हित पूर्णांक val)
अणु
	spin_lock_bh(&pmlmepriv->lock);
	pmlmepriv->num_of_scanned = val;
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

बाह्य u16 rtw_get_capability(काष्ठा wlan_bssid_ex *bss);
बाह्य व्योम rtw_update_scanned_network(काष्ठा adapter *adapter, काष्ठा wlan_bssid_ex *target);
बाह्य व्योम rtw_disconnect_hdl_under_linked(काष्ठा adapter *adapter, काष्ठा sta_info *psta, u8 मुक्त_assoc);
बाह्य व्योम rtw_generate_अक्रमom_ibss(u8 *pibss);
बाह्य काष्ठा wlan_network *rtw_find_network(काष्ठा __queue *scanned_queue, u8 *addr);
बाह्य काष्ठा wlan_network *rtw_get_oldest_wlan_network(काष्ठा __queue *scanned_queue);
काष्ठा wlan_network *_rtw_find_same_network(काष्ठा __queue *scanned_queue, काष्ठा wlan_network *network);

बाह्य व्योम rtw_मुक्त_assoc_resources(काष्ठा adapter *adapter, पूर्णांक lock_scanned_queue);
बाह्य व्योम rtw_indicate_disconnect(काष्ठा adapter *adapter);
बाह्य व्योम rtw_indicate_connect(काष्ठा adapter *adapter);
व्योम rtw_indicate_scan_करोne(काष्ठा adapter *padapter, bool पातed);
व्योम rtw_scan_पात(काष्ठा adapter *adapter);

बाह्य पूर्णांक rtw_reकाष्ठा_sec_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len);
बाह्य पूर्णांक rtw_reकाष्ठा_wmm_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len, uपूर्णांक initial_out_len);
बाह्य व्योम rtw_init_registrypriv_dev_network(काष्ठा adapter *adapter);

बाह्य व्योम rtw_update_registrypriv_dev_network(काष्ठा adapter *adapter);

बाह्य व्योम rtw_get_encrypt_decrypt_from_registrypriv(काष्ठा adapter *adapter);

बाह्य व्योम _rtw_join_समयout_handler(काष्ठा समयr_list *t);
बाह्य व्योम rtw_scan_समयout_handler(काष्ठा समयr_list *t);

बाह्य व्योम rtw_dynamic_check_समयr_handler(काष्ठा adapter *adapter);
bool rtw_is_scan_deny(काष्ठा adapter *adapter);
व्योम rtw_clear_scan_deny(काष्ठा adapter *adapter);
व्योम rtw_set_scan_deny(काष्ठा adapter *adapter, u32 ms);

व्योम rtw_मुक्त_mlme_priv_ie_data(काष्ठा mlme_priv *pmlmepriv);

बाह्य व्योम _rtw_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv);

/* बाह्य काष्ठा wlan_network* _rtw_dequeue_network(काष्ठा __queue *queue); */

बाह्य काष्ठा wlan_network *rtw_alloc_network(काष्ठा mlme_priv *pmlmepriv);


बाह्य व्योम _rtw_मुक्त_network(काष्ठा mlme_priv *pmlmepriv, काष्ठा wlan_network *pnetwork, u8 isमुक्तall);
बाह्य व्योम _rtw_मुक्त_network_nolock(काष्ठा mlme_priv *pmlmepriv, काष्ठा wlan_network *pnetwork);


बाह्य काष्ठा wlan_network *_rtw_find_network(काष्ठा __queue *scanned_queue, u8 *addr);

बाह्य चिन्हित पूर्णांक rtw_अगर_up(काष्ठा adapter *padapter);

चिन्हित पूर्णांक rtw_linked_check(काष्ठा adapter *padapter);

u8 *rtw_get_capability_from_ie(u8 *ie);
u8 *rtw_get_beacon_पूर्णांकerval_from_ie(u8 *ie);


व्योम rtw_joinbss_reset(काष्ठा adapter *padapter);

व्योम rtw_ht_use_शेष_setting(काष्ठा adapter *padapter);
व्योम rtw_build_wmm_ie_ht(काष्ठा adapter *padapter, u8 *out_ie, uपूर्णांक *pout_len);
अचिन्हित पूर्णांक rtw_reकाष्ठाure_ht_ie(काष्ठा adapter *padapter, u8 *in_ie, u8 *out_ie, uपूर्णांक in_len, uपूर्णांक *pout_len, u8 channel);
व्योम rtw_update_ht_cap(काष्ठा adapter *padapter, u8 *pie, uपूर्णांक ie_len, u8 channel);
व्योम rtw_issue_addbareq_cmd(काष्ठा adapter *padapter, काष्ठा xmit_frame *pxmitframe);
व्योम rtw_append_exented_cap(काष्ठा adapter *padapter, u8 *out_ie, uपूर्णांक *pout_len);

पूर्णांक rtw_is_same_ibss(काष्ठा adapter *adapter, काष्ठा wlan_network *pnetwork);
पूर्णांक is_same_network(काष्ठा wlan_bssid_ex *src, काष्ठा wlan_bssid_ex *dst, u8 feature);

#घोषणा rtw_roam_flags(adapter) ((adapter)->mlmepriv.roam_flags)
#घोषणा rtw_chk_roam_flags(adapter, flags) ((adapter)->mlmepriv.roam_flags & flags)
#घोषणा rtw_clr_roam_flags(adapter, flags) \
	करो अणु \
		((adapter)->mlmepriv.roam_flags &= ~flags); \
	पूर्ण जबतक (0)

#घोषणा rtw_set_roam_flags(adapter, flags) \
	करो अणु \
		((adapter)->mlmepriv.roam_flags |= flags); \
	पूर्ण जबतक (0)

#घोषणा rtw_assign_roam_flags(adapter, flags) \
	करो अणु \
		((adapter)->mlmepriv.roam_flags = flags); \
	पूर्ण जबतक (0)

व्योम _rtw_roaming(काष्ठा adapter *adapter, काष्ठा wlan_network *tgt_network);
व्योम rtw_roaming(काष्ठा adapter *adapter, काष्ठा wlan_network *tgt_network);
व्योम rtw_set_to_roam(काष्ठा adapter *adapter, u8 to_roam);
u8 rtw_dec_to_roam(काष्ठा adapter *adapter);
u8 rtw_to_roam(काष्ठा adapter *adapter);
पूर्णांक rtw_select_roaming_candidate(काष्ठा mlme_priv *pmlmepriv);

व्योम rtw_sta_media_status_rpt(काष्ठा adapter *adapter, काष्ठा sta_info *psta, u32 mstatus);

#पूर्ण_अगर /* __RTL871X_MLME_H_ */
