<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_UTIL_H__
#घोषणा __RTW_UTIL_H__

काष्ठा rtw_dev;

#घोषणा rtw_iterate_vअगरs(rtwdev, iterator, data)                               \
	ieee80211_iterate_active_पूर्णांकerfaces(rtwdev->hw,                        \
			IEEE80211_IFACE_ITER_NORMAL, iterator, data)
#घोषणा rtw_iterate_vअगरs_atomic(rtwdev, iterator, data)                        \
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(rtwdev->hw,                 \
			IEEE80211_IFACE_ITER_NORMAL, iterator, data)
#घोषणा rtw_iterate_stas_atomic(rtwdev, iterator, data)                        \
	ieee80211_iterate_stations_atomic(rtwdev->hw, iterator, data)
#घोषणा rtw_iterate_keys(rtwdev, vअगर, iterator, data)			       \
	ieee80211_iter_keys(rtwdev->hw, vअगर, iterator, data)
#घोषणा rtw_iterate_keys_rcu(rtwdev, vअगर, iterator, data)		       \
	ieee80211_iter_keys_rcu((rtwdev)->hw, vअगर, iterator, data)

अटल अंतरभूत u8 *get_hdr_bssid(काष्ठा ieee80211_hdr *hdr)
अणु
	__le16 fc = hdr->frame_control;
	u8 *bssid;

	अगर (ieee80211_has_tods(fc))
		bssid = hdr->addr1;
	अन्यथा अगर (ieee80211_has_fromds(fc))
		bssid = hdr->addr2;
	अन्यथा
		bssid = hdr->addr3;

	वापस bssid;
पूर्ण

#पूर्ण_अगर
