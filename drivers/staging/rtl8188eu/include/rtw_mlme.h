<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_MLME_H_
#घोषणा __RTW_MLME_H_

#समावेश <osdep_service.h>
#समावेश <mlme_osdep.h>
#समावेश <drv_types.h>
#समावेश <wlan_bssdef.h>

#घोषणा	MAX_BSS_CNT	128
#घोषणा   MAX_JOIN_TIMEOUT	6500

/* Increase the scanning समयout because of increasing the SURVEY_TO value. */

#घोषणा		SCANNING_TIMEOUT	8000

#घोषणा	SCAN_INTERVAL	(30) /*  unit:2sec, 30*2=60sec */

#घोषणा	SCANQUEUE_LIFETIME 20 /*  unit:sec */

#घोषणा	WIFI_शून्य_STATE			0x00000000

#घोषणा	WIFI_ASOC_STATE			0x00000001	/* Under Linked state */
#घोषणा	WIFI_REASOC_STATE		0x00000002
#घोषणा	WIFI_SLEEP_STATE		0x00000004
#घोषणा	WIFI_STATION_STATE		0x00000008

#घोषणा	WIFI_AP_STATE			0x00000010
#घोषणा	WIFI_ADHOC_STATE		0x00000020
#घोषणा WIFI_ADHOC_MASTER_STATE		0x00000040
#घोषणा WIFI_UNDER_LINKING		0x00000080

#घोषणा	WIFI_UNDER_WPS			0x00000100
#घोषणा	WIFI_STA_ALIVE_CHK_STATE	0x00000400
#घोषणा	WIFI_SITE_MONITOR		0x00000800	/* to indicate the station is under site surveying */

#घोषणा _FW_UNDER_LINKING	WIFI_UNDER_LINKING
#घोषणा _FW_LINKED			WIFI_ASOC_STATE
#घोषणा _FW_UNDER_SURVEY	WIFI_SITE_MONITOR

क्रमागत करोt11AuthAlgrthmNum अणु
	करोt11AuthAlgrthm_Open = 0, /* खोलो प्रणाली */
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

क्रमागत SCAN_RESULT_TYPE अणु
	SCAN_RESULT_P2P_ONLY = 0,	/* Will वापस all the P2P devices. */
	SCAN_RESULT_ALL = 1,		/* Will वापस all the scanned device,
					 * include AP.
					 */
	SCAN_RESULT_WFD_TYPE = 2	/* Will just वापस the correct WFD
					 * device.
					 */
					/* If this device is Miracast sink
					 * device, it will just वापस all the
					 * Miracast source devices.
					 */
पूर्ण;

/*
 * there are several "locks" in mlme_priv,
 * since mlme_priv is a shared resource between many thपढ़ोs,
 * like ISR/Call-Back functions, the OID handlers, and even समयr functions.
 *
 * Each _queue has its own locks, alपढ़ोy.
 * Other items are रक्षित by mlme_priv.lock.
 *
 * To aव्योम possible dead lock, any thपढ़ो trying to modअगरiying mlme_priv
 * SHALL not lock up more than one lock at a समय!
 */

#घोषणा traffic_threshold	10
#घोषणा	traffic_scan_period	500

काष्ठा rt_link_detect अणु
	u32	NumTxOkInPeriod;
	u32	NumRxOkInPeriod;
	u32	NumRxUnicastOkInPeriod;
	bool	bBusyTraffic;
	bool	bTxBusyTraffic;
	bool	bRxBusyTraffic;
	bool	bHigherBusyTraffic; /*  For पूर्णांकerrupt migration purpose. */
	bool	bHigherBusyRxTraffic; /* We may disable Tx पूर्णांकerrupt according
				       * to Rx traffic.
				       */
	bool	bHigherBusyTxTraffic; /* We may disable Tx पूर्णांकerrupt according
				       * to Tx traffic.
				       */
पूर्ण;

काष्ठा mlme_priv अणु
	spinlock_t lock;
	पूर्णांक fw_state;	/* shall we protect this variable? maybe not necessarily... */
	u8 bScanInProcess;
	u8 to_join; /* flag */
	u8 to_roaming; /*  roaming trying बार */

	u8 *nic_hdl;

	काष्ठा list_head *pscanned;
	काष्ठा __queue मुक्त_bss_pool;
	काष्ठा __queue scanned_queue;
	u8 *मुक्त_bss_buf;

	काष्ठा ndis_802_11_ssid	assoc_ssid;
	u8	assoc_bssid[6];

	काष्ठा wlan_network	cur_network;

	u32	scan_पूर्णांकerval;

	काष्ठा समयr_list assoc_समयr;

	uपूर्णांक assoc_by_bssid;

	काष्ठा समयr_list scan_to_समयr; /*  driver itself handles scan_समयout status. */

	काष्ठा qos_priv qospriv;

	/* Number of non-HT AP/stations */
	पूर्णांक num_sta_no_ht;

	/* Number of HT AP/stations 20 MHz */
	/* पूर्णांक num_sta_ht_20mhz; */

	पूर्णांक num_FortyMHzIntolerant;
	काष्ठा ht_priv	htpriv;
	काष्ठा rt_link_detect LinkDetectInfo;
	काष्ठा समयr_list dynamic_chk_समयr; /* dynamic/periodic check समयr */

	u8	key_mask; /* use क्रम ips to set wep key after ips_leave */
	u8	acm_mask; /*  क्रम wmm acm mask */
	u8	ChannelPlan;
	क्रमागत rt_scan_type scan_mode; /*  active: 1, passive: 0 */

	/* u8 probereq_wpsie[MAX_WPS_IE_LEN];added in probe req */
	/* पूर्णांक probereq_wpsie_len; */
	u8 *wps_probe_req_ie;
	u32 wps_probe_req_ie_len;

	u8 *assoc_req;
	u32 assoc_req_len;
	u8 *assoc_rsp;
	u32 assoc_rsp_len;

#अगर defined(CONFIG_88EU_AP_MODE)
	/* Number of associated Non-ERP stations (i.e., stations using 802.11b
	 * in 802.11g BSS)
	 */
	पूर्णांक num_sta_non_erp;

	/* Number of associated stations that करो not support Short Slot Time */
	पूर्णांक num_sta_no_लघु_slot_समय;

	/* Number of associated stations that करो not support Short Preamble */
	पूर्णांक num_sta_no_लघु_preamble;

	पूर्णांक olbc; /* Overlapping Legacy BSS Condition */

	/* Number of HT assoc sta that करो not support greenfield */
	पूर्णांक num_sta_ht_no_gf;

	/* Number of associated non-HT stations */
	/* पूर्णांक num_sta_no_ht; */

	/* Number of HT associated stations 20 MHz */
	पूर्णांक num_sta_ht_20mhz;

	/* Overlapping BSS inक्रमmation */
	पूर्णांक olbc_ht;

	u16 ht_op_mode;

	u8 *wps_beacon_ie;
	/* u8 *wps_probe_req_ie; */
	u8 *wps_probe_resp_ie;
	u8 *wps_assoc_resp_ie;

	u32 wps_beacon_ie_len;
	u32 wps_probe_resp_ie_len;
	u32 wps_assoc_resp_ie_len;

	spinlock_t bcn_update_lock;
	u8		update_bcn;
#पूर्ण_अगर /* अगर defined (CONFIG_88EU_AP_MODE) */
पूर्ण;

#अगर_घोषित CONFIG_88EU_AP_MODE

काष्ठा hostapd_priv अणु
	काष्ठा adapter *padapter;
पूर्ण;

पूर्णांक hostapd_mode_init(काष्ठा adapter *padapter);
व्योम hostapd_mode_unload(काष्ठा adapter *padapter);
#पूर्ण_अगर

बाह्य स्थिर u8 WPA_TKIP_CIPHER[4];
बाह्य स्थिर u8 RSN_TKIP_CIPHER[4];
बाह्य u8 REALTEK_96B_IE[];
बाह्य स्थिर u8 MCS_rate_1R[16];

व्योम rtw_joinbss_event_prehandle(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_survey_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_surveyकरोne_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_joinbss_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_stassoc_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_stadel_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_atimकरोne_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम rtw_cpwm_event_callback(काष्ठा adapter *adapter, u8 *pbuf);
व्योम indicate_wx_scan_complete_event(काष्ठा adapter *padapter);
व्योम rtw_indicate_wx_assoc_event(काष्ठा adapter *padapter);
व्योम rtw_indicate_wx_disassoc_event(काष्ठा adapter *padapter);
पूर्णांक event_thपढ़ो(व्योम *context);
व्योम rtw_मुक्त_network_queue(काष्ठा adapter *adapter, u8 isमुक्तall);
पूर्णांक rtw_init_mlme_priv(काष्ठा adapter *adapter);
व्योम rtw_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv);
पूर्णांक rtw_select_and_join_from_scanned_queue(काष्ठा mlme_priv *pmlmepriv);
पूर्णांक rtw_set_key(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv,
		पूर्णांक keyid, u8 set_tx);
पूर्णांक rtw_set_auth(काष्ठा adapter *adapter, काष्ठा security_priv *psecuritypriv);

अटल अंतरभूत u8 *get_bssid(काष्ठा mlme_priv *pmlmepriv)
अणु	/* अगर sta_mode:pmlmepriv->cur_network.network.MacAddress=> bssid */
	/*  अगर adhoc_mode:pmlmepriv->cur_network.network.MacAddress=> ibss mac address */
	वापस pmlmepriv->cur_network.network.MacAddress;
पूर्ण

अटल अंतरभूत पूर्णांक check_fwstate(काष्ठा mlme_priv *pmlmepriv, पूर्णांक state)
अणु
	अगर (pmlmepriv->fw_state & state)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक get_fwstate(काष्ठा mlme_priv *pmlmepriv)
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
अटल अंतरभूत व्योम set_fwstate(काष्ठा mlme_priv *pmlmepriv, पूर्णांक state)
अणु
	pmlmepriv->fw_state |= state;
	/* FOR HW पूर्णांकegration */
	अगर (state == _FW_UNDER_SURVEY)
		pmlmepriv->bScanInProcess = true;
पूर्ण

अटल अंतरभूत व्योम _clr_fwstate_(काष्ठा mlme_priv *pmlmepriv, पूर्णांक state)
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
अटल अंतरभूत व्योम clr_fwstate(काष्ठा mlme_priv *pmlmepriv, पूर्णांक state)
अणु
	spin_lock_bh(&pmlmepriv->lock);
	अगर (check_fwstate(pmlmepriv, state))
		pmlmepriv->fw_state ^= state;
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

अटल अंतरभूत व्योम clr_fwstate_ex(काष्ठा mlme_priv *pmlmepriv, पूर्णांक state)
अणु
	spin_lock_bh(&pmlmepriv->lock);
	_clr_fwstate_(pmlmepriv, state);
	spin_unlock_bh(&pmlmepriv->lock);
पूर्ण

u16 rtw_get_capability(काष्ठा wlan_bssid_ex *bss);
व्योम rtw_update_scanned_network(काष्ठा adapter *adapter,
				काष्ठा wlan_bssid_ex *target);
व्योम rtw_disconnect_hdl_under_linked(काष्ठा adapter *adapter,
				     काष्ठा sta_info *psta, u8 मुक्त_assoc);
व्योम rtw_generate_अक्रमom_ibss(u8 *pibss);
काष्ठा wlan_network *rtw_find_network(काष्ठा __queue *scanned_queue, u8 *addr);
काष्ठा wlan_network *rtw_get_oldest_wlan_network(काष्ठा __queue *scanned_queue);

व्योम rtw_मुक्त_assoc_resources(काष्ठा adapter *adapter);
व्योम rtw_मुक्त_assoc_resources_locked(काष्ठा adapter *adapter);
व्योम rtw_indicate_disconnect(काष्ठा adapter *adapter);
व्योम rtw_indicate_connect(काष्ठा adapter *adapter);
व्योम rtw_indicate_scan_करोne(काष्ठा adapter *padapter, bool पातed);

पूर्णांक rtw_reकाष्ठा_sec_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie,
			uपूर्णांक in_len);
पूर्णांक rtw_reकाष्ठा_wmm_ie(काष्ठा adapter *adapter, u8 *in_ie, u8 *out_ie,
			uपूर्णांक in_len, uपूर्णांक initial_out_len);
व्योम rtw_init_registrypriv_dev_network(काष्ठा adapter *adapter);

व्योम rtw_update_registrypriv_dev_network(काष्ठा adapter *adapter);

व्योम rtw_get_encrypt_decrypt_from_registrypriv(काष्ठा adapter *adapter);

व्योम _rtw_join_समयout_handler(काष्ठा समयr_list *t);
व्योम rtw_scan_समयout_handler(काष्ठा समयr_list *t);

व्योम rtw_dynamic_check_समयr_handlder(काष्ठा समयr_list *t);
#घोषणा rtw_is_scan_deny(adapter) false
#घोषणा rtw_clear_scan_deny(adapter) करो अणुपूर्ण जबतक (0)
#घोषणा rtw_set_scan_deny_समयr_hdl(adapter) करो अणुपूर्ण जबतक (0)
#घोषणा rtw_set_scan_deny(adapter, ms) करो अणुपूर्ण जबतक (0)

व्योम rtw_मुक्त_mlme_priv_ie_data(काष्ठा mlme_priv *pmlmepriv);

काष्ठा wlan_network *rtw_alloc_network(काष्ठा mlme_priv *pmlmepriv);

पूर्णांक rtw_अगर_up(काष्ठा adapter *padapter);

u8 *rtw_get_capability_from_ie(u8 *ie);
u8 *rtw_get_beacon_पूर्णांकerval_from_ie(u8 *ie);

व्योम rtw_joinbss_reset(काष्ठा adapter *padapter);

अचिन्हित पूर्णांक rtw_reकाष्ठाure_ht_ie(काष्ठा adapter *padapter, u8 *in_ie,
				   u8 *out_ie, uपूर्णांक in_len, uपूर्णांक *pout_len);
व्योम rtw_update_ht_cap(काष्ठा adapter *padapter, u8 *pie, uपूर्णांक ie_len);
व्योम rtw_issue_addbareq_cmd(काष्ठा adapter *padapter,
			    काष्ठा xmit_frame *pxmitframe);

पूर्णांक rtw_is_same_ibss(काष्ठा adapter *adapter, काष्ठा wlan_network *pnetwork);
पूर्णांक is_same_network(काष्ठा wlan_bssid_ex *src, काष्ठा wlan_bssid_ex *dst);

व्योम rtw_roaming(काष्ठा adapter *padapter, काष्ठा wlan_network *tgt_network);
व्योम _rtw_roaming(काष्ठा adapter *padapter, काष्ठा wlan_network *tgt_network);

व्योम rtw_stassoc_hw_rpt(काष्ठा adapter *adapter, काष्ठा sta_info *psta);

#पूर्ण_अगर /* __RTL871X_MLME_H_ */
