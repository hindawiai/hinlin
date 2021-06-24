<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_AP_H_
#घोषणा __RTW_AP_H_

व्योम init_mlme_ap_info(काष्ठा adapter *padapter);
व्योम मुक्त_mlme_ap_info(काष्ठा adapter *padapter);
/* व्योम update_BCNTIM(काष्ठा adapter *padapter); */
व्योम update_beacon(काष्ठा adapter *padapter, u8 ie_id, u8 *oui, u8 tx);
व्योम add_RATid(काष्ठा adapter *padapter, काष्ठा sta_info *psta, u8 rssi_level);
व्योम expire_समयout_chk(काष्ठा adapter *padapter);
व्योम update_sta_info_apmode(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम start_bss_network(काष्ठा adapter *padapter, u8 *pbuf);
पूर्णांक rtw_check_beacon_data(काष्ठा adapter *padapter, u8 *pbuf,  पूर्णांक len);
व्योम rtw_ap_restore_network(काष्ठा adapter *padapter);
व्योम rtw_set_macaddr_acl(काष्ठा adapter *padapter, पूर्णांक mode);
पूर्णांक rtw_acl_add_sta(काष्ठा adapter *padapter, u8 *addr);
व्योम rtw_acl_हटाओ_sta(काष्ठा adapter *padapter, u8 *addr);

u8 rtw_ap_set_pairwise_key(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
पूर्णांक rtw_ap_set_group_key(काष्ठा adapter *padapter, u8 *key, u8 alg, पूर्णांक keyid);
पूर्णांक rtw_ap_set_wep_key(काष्ठा adapter *padapter, u8 *key, u8 keylen, पूर्णांक keyid, u8 set_tx);

व्योम associated_clients_update(काष्ठा adapter *padapter, u8 updated);
व्योम bss_cap_update_on_sta_join(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
u8 bss_cap_update_on_sta_leave(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम sta_info_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
व्योम ap_sta_info_defer_update(काष्ठा adapter *padapter, काष्ठा sta_info *psta);
u8 ap_मुक्त_sta(काष्ठा adapter *padapter, काष्ठा sta_info *psta, bool active, u16 reason);
व्योम rtw_sta_flush(काष्ठा adapter *padapter);
व्योम start_ap_mode(काष्ठा adapter *padapter);
व्योम stop_ap_mode(काष्ठा adapter *padapter);

#पूर्ण_अगर
व्योम update_bmc_sta(काष्ठा adapter *padapter);
