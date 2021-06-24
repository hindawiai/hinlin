<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_WOW_H__
#घोषणा __RTW_WOW_H__

#घोषणा PNO_CHECK_BYTE 4

क्रमागत rtw_wow_pattern_type अणु
	RTW_PATTERN_BROADCAST = 0,
	RTW_PATTERN_MULTICAST,
	RTW_PATTERN_UNICAST,
	RTW_PATTERN_VALID,
	RTW_PATTERN_INVALID,
पूर्ण;

क्रमागत rtw_wake_reason अणु
	RTW_WOW_RSN_RX_PTK_REKEY = 0x1,
	RTW_WOW_RSN_RX_GTK_REKEY = 0x2,
	RTW_WOW_RSN_RX_DEAUTH = 0x8,
	RTW_WOW_RSN_DISCONNECT = 0x10,
	RTW_WOW_RSN_RX_MAGIC_PKT = 0x21,
	RTW_WOW_RSN_RX_PATTERN_MATCH = 0x23,
	RTW_WOW_RSN_RX_NLO = 0x55,
पूर्ण;

काष्ठा rtw_fw_media_status_iter_data अणु
	काष्ठा rtw_dev *rtwdev;
	u8 connect;
पूर्ण;

काष्ठा rtw_fw_key_type_iter_data अणु
	काष्ठा rtw_dev *rtwdev;
	u8 group_key_type;
	u8 pairwise_key_type;
पूर्ण;

अटल अंतरभूत bool rtw_wow_mgd_linked(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा ieee80211_vअगर *wow_vअगर = rtwdev->wow.wow_vअगर;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)wow_vअगर->drv_priv;

	वापस (rtwvअगर->net_type == RTW_NET_MGD_LINKED);
पूर्ण

अटल अंतरभूत bool rtw_wow_no_link(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा ieee80211_vअगर *wow_vअगर = rtwdev->wow.wow_vअगर;
	काष्ठा rtw_vअगर *rtwvअगर = (काष्ठा rtw_vअगर *)wow_vअगर->drv_priv;

	वापस (rtwvअगर->net_type == RTW_NET_NO_LINK);
पूर्ण

पूर्णांक rtw_wow_suspend(काष्ठा rtw_dev *rtwdev, काष्ठा cfg80211_wowlan *wowlan);
पूर्णांक rtw_wow_resume(काष्ठा rtw_dev *rtwdev);

#पूर्ण_अगर
