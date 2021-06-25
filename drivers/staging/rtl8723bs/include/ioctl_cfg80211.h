<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __IOCTL_CFG80211_H__
#घोषणा __IOCTL_CFG80211_H__

काष्ठा rtw_wdev_invit_info अणु
	u8 state; /* 0: req, 1:rep */
	u8 peer_mac[ETH_ALEN];
	u8 active;
	u8 token;
	u8 flags;
	u8 status;
	u8 req_op_ch;
	u8 rsp_op_ch;
पूर्ण;

#घोषणा rtw_wdev_invit_info_init(invit_info) \
	करो अणु \
		(invit_info)->state = 0xff; \
		स_रखो((invit_info)->peer_mac, 0, ETH_ALEN); \
		(invit_info)->active = 0xff; \
		(invit_info)->token = 0; \
		(invit_info)->flags = 0x00; \
		(invit_info)->status = 0xff; \
		(invit_info)->req_op_ch = 0; \
		(invit_info)->rsp_op_ch = 0; \
	पूर्ण जबतक (0)

काष्ठा rtw_wdev_nego_info अणु
	u8 state; /* 0: req, 1:rep, 2:conf */
	u8 peer_mac[ETH_ALEN];
	u8 active;
	u8 token;
	u8 status;
	u8 req_पूर्णांकent;
	u8 req_op_ch;
	u8 req_listen_ch;
	u8 rsp_पूर्णांकent;
	u8 rsp_op_ch;
	u8 conf_op_ch;
पूर्ण;

#घोषणा rtw_wdev_nego_info_init(nego_info) \
	करो अणु \
		(nego_info)->state = 0xff; \
		स_रखो((nego_info)->peer_mac, 0, ETH_ALEN); \
		(nego_info)->active = 0xff; \
		(nego_info)->token = 0; \
		(nego_info)->status = 0xff; \
		(nego_info)->req_पूर्णांकent = 0xff; \
		(nego_info)->req_op_ch = 0; \
		(nego_info)->req_listen_ch = 0; \
		(nego_info)->rsp_पूर्णांकent = 0xff; \
		(nego_info)->rsp_op_ch = 0; \
		(nego_info)->conf_op_ch = 0; \
	पूर्ण जबतक (0)

काष्ठा rtw_wdev_priv अणु
	काष्ठा wireless_dev *rtw_wdev;

	काष्ठा adapter *padapter;

	काष्ठा cfg80211_scan_request *scan_request;
	spinlock_t scan_req_lock;

	काष्ठा net_device *pmon_ndev;/* क्रम monitor पूर्णांकerface */
	अक्षर अगरname_mon[IFNAMSIZ + 1]; /* पूर्णांकerface name क्रम monitor पूर्णांकerface */

	u8 p2p_enabled;

	u8 provdisc_req_issued;

	काष्ठा rtw_wdev_invit_info invit_info;
	काष्ठा rtw_wdev_nego_info nego_info;

	u8 bandroid_scan;
	bool block;
	bool घातer_mgmt;
पूर्ण;

#घोषणा wiphy_to_adapter(x) (*((काष्ठा adapter **)wiphy_priv(x)))

#घोषणा wdev_to_ndev(w) ((w)->netdev)

पूर्णांक rtw_wdev_alloc(काष्ठा adapter *padapter, काष्ठा device *dev);
व्योम rtw_wdev_मुक्त(काष्ठा wireless_dev *wdev);
व्योम rtw_wdev_unरेजिस्टर(काष्ठा wireless_dev *wdev);

व्योम rtw_cfg80211_init_wiphy(काष्ठा adapter *padapter);

व्योम rtw_cfg80211_unlink_bss(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork);
व्योम rtw_cfg80211_surveyकरोne_event_callback(काष्ठा adapter *padapter);
काष्ठा cfg80211_bss *rtw_cfg80211_inक्रमm_bss(काष्ठा adapter *padapter, काष्ठा wlan_network *pnetwork);
पूर्णांक rtw_cfg80211_check_bss(काष्ठा adapter *padapter);
व्योम rtw_cfg80211_ibss_indicate_connect(काष्ठा adapter *padapter);
व्योम rtw_cfg80211_indicate_connect(काष्ठा adapter *padapter);
व्योम rtw_cfg80211_indicate_disconnect(काष्ठा adapter *padapter);
व्योम rtw_cfg80211_indicate_scan_करोne(काष्ठा adapter *adapter, bool पातed);

व्योम rtw_cfg80211_indicate_sta_assoc(काष्ठा adapter *padapter, u8 *pmgmt_frame, uपूर्णांक frame_len);
व्योम rtw_cfg80211_indicate_sta_disassoc(काष्ठा adapter *padapter, अचिन्हित अक्षर *da, अचिन्हित लघु reason);

व्योम rtw_cfg80211_rx_action(काष्ठा adapter *adapter, u8 *frame, uपूर्णांक frame_len, स्थिर अक्षर *msg);

bool rtw_cfg80211_pwr_mgmt(काष्ठा adapter *adapter);

#घोषणा rtw_cfg80211_rx_mgmt(adapter, freq, sig_dbm, buf, len, gfp) cfg80211_rx_mgmt((adapter)->rtw_wdev, freq, sig_dbm, buf, len, 0)
#घोषणा rtw_cfg80211_send_rx_assoc(adapter, bss, buf, len) cfg80211_send_rx_assoc((adapter)->pnetdev, bss, buf, len)
#घोषणा rtw_cfg80211_mgmt_tx_status(adapter, cookie, buf, len, ack, gfp) cfg80211_mgmt_tx_status((adapter)->rtw_wdev, cookie, buf, len, ack, gfp)
#घोषणा rtw_cfg80211_पढ़ोy_on_channel(adapter, cookie, chan, channel_type, duration, gfp)  cfg80211_पढ़ोy_on_channel((adapter)->rtw_wdev, cookie, chan, duration, gfp)
#घोषणा rtw_cfg80211_reमुख्य_on_channel_expired(adapter, cookie, chan, chan_type, gfp) cfg80211_reमुख्य_on_channel_expired((adapter)->rtw_wdev, cookie, chan, gfp)

#पूर्ण_अगर /* __IOCTL_CFG80211_H__ */
