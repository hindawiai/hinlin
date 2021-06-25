<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL871X_MLME_H_
#घोषणा __RTL871X_MLME_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "wlan_bssdef.h"

#घोषणा	MAX_BSS_CNT	64
#घोषणा   MAX_JOIN_TIMEOUT	6000

#घोषणा		SCANNING_TIMEOUT	4500

#घोषणा	SCANQUEUE_LIFETIME 20 /* unit:sec */

#घोषणा		WIFI_शून्य_STATE	0x00000000
#घोषणा	WIFI_ASOC_STATE		0x00000001	/* Under Linked state...*/
#घोषणा		WIFI_REASOC_STATE 0x00000002
#घोषणा	WIFI_SLEEP_STATE	0x00000004
#घोषणा	WIFI_STATION_STATE	0x00000008
#घोषणा	WIFI_AP_STATE		0x00000010
#घोषणा	WIFI_ADHOC_STATE	0x00000020
#घोषणा   WIFI_ADHOC_MASTER_STATE 0x00000040
#घोषणा   WIFI_UNDER_LINKING	0x00000080
#घोषणा WIFI_SITE_MONITOR	0x00000800	/* to indicate the station
						 * is under site surveying
						 */
#घोषणा	WIFI_MP_STATE		0x00010000
#घोषणा	WIFI_MP_CTX_BACKGROUND	0x00020000	/* in cont. tx background*/
#घोषणा	WIFI_MP_CTX_ST		0x00040000	/* in cont. tx with
						 * single-tone
						 */
#घोषणा	WIFI_MP_CTX_BACKGROUND_PENDING	0x00080000 /* pending in cont, tx
						    * background due
						    * to out of skb
						    */
#घोषणा	WIFI_MP_CTX_CCK_HW	0x00100000	/* in continuous tx*/
#घोषणा	WIFI_MP_CTX_CCK_CS	0x00200000	/* in cont, tx with carrier
						 * suppression
						 */
#घोषणा   WIFI_MP_LPBK_STATE	0x00400000

#घोषणा _FW_UNDER_LINKING	WIFI_UNDER_LINKING
#घोषणा _FW_LINKED		WIFI_ASOC_STATE
#घोषणा _FW_UNDER_SURVEY	WIFI_SITE_MONITOR

/*
 * there are several "locks" in mlme_priv,
 * since mlme_priv is a shared resource between many thपढ़ोs,
 * like ISR/Call-Back functions, the OID handlers, and even समयr functions.
 * Each _queue has its own locks, alपढ़ोy.
 * Other items are रक्षित by mlme_priv.lock.
 * To aव्योम possible dead lock, any thपढ़ो trying to modअगरy mlme_priv
 * SHALL not lock up more than one lock at a समय!
 */

#घोषणा traffic_threshold	10
#घोषणा	traffic_scan_period	500

काष्ठा sitesurvey_ctrl अणु
	u64	last_tx_pkts;
	uपूर्णांक	last_rx_pkts;
	sपूर्णांक	traffic_busy;
	काष्ठा समयr_list sitesurvey_ctrl_समयr;
पूर्ण;

काष्ठा mlme_priv अणु
	spinlock_t lock;
	spinlock_t lock2;
	sपूर्णांक	fw_state;	/*shall we protect this variable? */
	u8 to_join; /*flag*/
	u8 *nic_hdl;
	काष्ठा list_head *pscanned;
	काष्ठा  __queue मुक्त_bss_pool;
	काष्ठा  __queue scanned_queue;
	u8 *मुक्त_bss_buf;
	अचिन्हित दीर्घ num_of_scanned;
	u8 passive_mode; /*add क्रम Android's SCAN-ACTIVE/SCAN-PASSIVE */
	काष्ठा ndis_802_11_ssid	assoc_ssid;
	u8 assoc_bssid[6];
	काष्ठा wlan_network cur_network;
	काष्ठा sitesurvey_ctrl sitesurveyctrl;
	काष्ठा समयr_list assoc_समयr;
	uपूर्णांक assoc_by_bssid;
	uपूर्णांक assoc_by_rssi;
	काष्ठा समयr_list scan_to_समयr; /* driver handles scan_समयout.*/
	काष्ठा समयr_list dhcp_समयr; /* set dhcp to अगर driver in ps mode.*/
	काष्ठा qos_priv qospriv;
	काष्ठा ht_priv	htpriv;
	काष्ठा समयr_list wdg_समयr; /*watchकरोg periodic समयr*/
पूर्ण;

अटल अंतरभूत u8 *get_bssid(काष्ठा mlme_priv *pmlmepriv)
अणु
	वापस pmlmepriv->cur_network.network.MacAddress;
पूर्ण

अटल अंतरभूत u8 check_fwstate(काष्ठा mlme_priv *pmlmepriv, sपूर्णांक state)
अणु
	अगर (pmlmepriv->fw_state & state)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत sपूर्णांक get_fwstate(काष्ठा mlme_priv *pmlmepriv)
अणु
	वापस pmlmepriv->fw_state;
पूर्ण

/*
 * No Limit on the calling context,
 * thereक्रमe set it to be the critical section...
 *
 * ### NOTE:#### (!!!!)
 * TAKE CARE BEFORE CALLING THIS FUNC, LOCK pmlmepriv->lock
 */
अटल अंतरभूत व्योम set_fwstate(काष्ठा mlme_priv *pmlmepriv, sपूर्णांक state)
अणु
	pmlmepriv->fw_state |= state;
पूर्ण

अटल अंतरभूत व्योम _clr_fwstate_(काष्ठा mlme_priv *pmlmepriv, sपूर्णांक state)
अणु
	pmlmepriv->fw_state &= ~state;
पूर्ण

/*
 * No Limit on the calling context,
 * thereक्रमe set it to be the critical section...
 */
अटल अंतरभूत व्योम clr_fwstate(काष्ठा mlme_priv *pmlmepriv, sपूर्णांक state)
अणु
	अचिन्हित दीर्घ irqL;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	अगर (check_fwstate(pmlmepriv, state))
		pmlmepriv->fw_state ^= state;
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
पूर्ण

अटल अंतरभूत व्योम set_scanned_network_val(काष्ठा mlme_priv *pmlmepriv,
					     sपूर्णांक val)
अणु
	अचिन्हित दीर्घ irqL;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	pmlmepriv->num_of_scanned = val;
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
पूर्ण

व्योम r8712_survey_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_surveyकरोne_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_joinbss_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_stassoc_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_stadel_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_atimकरोne_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_cpwm_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_wpspbc_event_callback(काष्ठा _adapter *adapter, u8 *pbuf);
व्योम r8712_मुक्त_network_queue(काष्ठा _adapter *adapter);
पूर्णांक r8712_init_mlme_priv(काष्ठा _adapter *adapter);
व्योम r8712_मुक्त_mlme_priv(काष्ठा mlme_priv *pmlmepriv);
पूर्णांक r8712_select_and_join_from_scan(काष्ठा mlme_priv *pmlmepriv);
पूर्णांक r8712_set_key(काष्ठा _adapter *adapter,
		  काष्ठा security_priv *psecuritypriv, sपूर्णांक keyid);
पूर्णांक r8712_set_auth(काष्ठा _adapter *adapter,
		   काष्ठा security_priv *psecuritypriv);
uपूर्णांक r8712_get_wlan_bssid_ex_sz(काष्ठा wlan_bssid_ex *bss);
व्योम r8712_generate_अक्रमom_ibss(u8 *pibss);
u8 *r8712_get_capability_from_ie(u8 *ie);
काष्ठा wlan_network *r8712_get_oldest_wlan_network(
				काष्ठा  __queue *scanned_queue);
व्योम r8712_मुक्त_assoc_resources(काष्ठा _adapter *adapter);
व्योम r8712_ind_disconnect(काष्ठा _adapter *adapter);
व्योम r8712_indicate_connect(काष्ठा _adapter *adapter);
पूर्णांक r8712_reकाष्ठा_sec_ie(काष्ठा _adapter *adapter, u8 *in_ie,
			  u8 *out_ie, uपूर्णांक in_len);
पूर्णांक r8712_reकाष्ठा_wmm_ie(काष्ठा _adapter *adapter, u8 *in_ie,
			  u8 *out_ie, uपूर्णांक in_len, uपूर्णांक initial_out_len);
व्योम r8712_init_registrypriv_dev_network(काष्ठा _adapter *adapter);
व्योम r8712_update_registrypriv_dev_network(काष्ठा _adapter *adapter);
व्योम _r8712_sitesurvey_ctrl_handler(काष्ठा _adapter *adapter);
व्योम _r8712_join_समयout_handler(काष्ठा _adapter *adapter);
व्योम r8712_scan_समयout_handler(काष्ठा _adapter *adapter);
व्योम _r8712_dhcp_समयout_handler(काष्ठा _adapter *adapter);
काष्ठा wlan_network *_r8712_alloc_network(काष्ठा mlme_priv *pmlmepriv);
sपूर्णांक r8712_अगर_up(काष्ठा _adapter *padapter);
व्योम r8712_joinbss_reset(काष्ठा _adapter *padapter);
अचिन्हित पूर्णांक r8712_reकाष्ठाure_ht_ie(काष्ठा _adapter *padapter, u8 *in_ie,
				     u8 *out_ie, uपूर्णांक in_len, uपूर्णांक *pout_len);
व्योम r8712_issue_addbareq_cmd(काष्ठा _adapter *padapter, पूर्णांक priority);
पूर्णांक r8712_is_same_ibss(काष्ठा _adapter *adapter, काष्ठा wlan_network *pnetwork);

#पूर्ण_अगर /*__RTL871X_MLME_H_*/
