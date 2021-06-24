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
#अगर_अघोषित __STA_INFO_H_
#घोषणा __STA_INFO_H_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "wifi.h"

#घोषणा NUM_STA 32
#घोषणा NUM_ACL 64


/* अगर mode ==0, then the sta is allowed once the addr is hit.
 * अगर mode ==1, then the sta is rejected once the addr is non-hit.
 */
काष्ठा wlan_acl_node अणु
	काष्ठा list_head list;
	u8       addr[ETH_ALEN];
	u8       mode;
पूर्ण;

काष्ठा wlan_acl_pool अणु
	काष्ठा wlan_acl_node aclnode[NUM_ACL];
पूर्ण;

काष्ठा	stainfo_stats अणु
	uपूर्णांक	rx_pkts;
	uपूर्णांक	rx_bytes;
	u64	tx_pkts;
	uपूर्णांक	tx_bytes;
पूर्ण;

काष्ठा sta_info अणु
	spinlock_t lock;
	काष्ठा list_head list; /*मुक्त_sta_queue*/
	काष्ठा list_head hash_list; /*sta_hash*/
	काष्ठा sta_xmit_priv sta_xmitpriv;
	काष्ठा sta_recv_priv sta_recvpriv;
	uपूर्णांक state;
	uपूर्णांक aid;
	uपूर्णांक	mac_id;
	uपूर्णांक	qos_option;
	u8	hwaddr[ETH_ALEN];
	uपूर्णांक	ieee8021x_blocked;	/*0: allowed, 1:blocked */
	uपूर्णांक	XPrivacy; /*aes, tkip...*/
	जोड़ Keytype	tkiptxmickey;
	जोड़ Keytype	tkiprxmickey;
	जोड़ Keytype	x_UncstKey;
	जोड़ pn48		txpn;	/* PN48 used क्रम Unicast xmit.*/
	जोड़ pn48		rxpn;	/* PN48 used क्रम Unicast recv.*/
	u8	bssrateset[16];
	uपूर्णांक	bssratelen;
	s32  rssi;
	s32	संकेत_quality;
	काष्ठा stainfo_stats sta_stats;
	/*क्रम A-MPDU Rx reordering buffer control */
	काष्ठा recv_reorder_ctrl recvreorder_ctrl[16];
	काष्ठा ht_priv	htpriv;
	/* Notes:
	 * STA_Mode:
	 * curr_network(mlme_priv/security_priv/qos/ht)
	 *   + sta_info: (STA & AP) CAP/INFO
	 * scan_q: AP CAP/INFO
	 * AP_Mode:
	 * curr_network(mlme_priv/security_priv/qos/ht) : AP CAP/INFO
	 * sta_info: (AP & STA) CAP/INFO
	 */
	काष्ठा list_head asoc_list;
	काष्ठा list_head auth_list;
	अचिन्हित पूर्णांक expire_to;
	अचिन्हित पूर्णांक auth_seq;
	अचिन्हित पूर्णांक authalg;
	अचिन्हित अक्षर chg_txt[128];
	अचिन्हित पूर्णांक tx_ra_biपंचांगap;
पूर्ण;

काष्ठा	sta_priv अणु
	u8 *pallocated_stainfo_buf;
	u8 *pstainfo_buf;
	काष्ठा  __queue	मुक्त_sta_queue;
	spinlock_t sta_hash_lock;
	काष्ठा list_head sta_hash[NUM_STA];
	पूर्णांक asoc_sta_count;
	काष्ठा  __queue sleep_q;
	काष्ठा  __queue wakeup_q;
	काष्ठा _adapter *padapter;
	काष्ठा list_head asoc_list;
	काष्ठा list_head auth_list;
	अचिन्हित पूर्णांक auth_to;  /* sec, समय to expire in authenticating. */
	अचिन्हित पूर्णांक assoc_to; /* sec, समय to expire beक्रमe associating. */
	अचिन्हित पूर्णांक expire_to; /* sec , समय to expire after associated. */
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

पूर्णांक _r8712_init_sta_priv(काष्ठा sta_priv *pstapriv);
व्योम _r8712_मुक्त_sta_priv(काष्ठा sta_priv *pstapriv);
काष्ठा sta_info *r8712_alloc_stainfo(काष्ठा sta_priv *pstapriv,
				     u8 *hwaddr);
व्योम r8712_मुक्त_stainfo(काष्ठा _adapter *padapter, काष्ठा sta_info *psta);
व्योम r8712_मुक्त_all_stainfo(काष्ठा _adapter *padapter);
काष्ठा sta_info *r8712_get_stainfo(काष्ठा sta_priv *pstapriv, u8 *hwaddr);
व्योम r8712_init_bcmc_stainfo(काष्ठा _adapter *padapter);
काष्ठा sta_info *r8712_get_bcmc_stainfo(काष्ठा _adapter *padapter);
u8 r8712_access_ctrl(काष्ठा wlan_acl_pool *pacl_list, u8 *mac_addr);

#पूर्ण_अगर /* _STA_INFO_H_ */

