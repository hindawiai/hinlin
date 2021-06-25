<शैली गुरु>
/*
 * Copyright (c) 2011 Atheros Communications Inc.
 * Copyright (c) 2011-2012 Qualcomm Atheros, Inc.
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

#अगर_अघोषित ATH6KL_CFG80211_H
#घोषणा ATH6KL_CFG80211_H

क्रमागत ath6kl_cfg_suspend_mode अणु
	ATH6KL_CFG_SUSPEND_DEEPSLEEP,
	ATH6KL_CFG_SUSPEND_CUTPOWER,
	ATH6KL_CFG_SUSPEND_WOW,
पूर्ण;

काष्ठा wireless_dev *ath6kl_पूर्णांकerface_add(काष्ठा ath6kl *ar, स्थिर अक्षर *name,
					  अचिन्हित अक्षर name_assign_type,
					  क्रमागत nl80211_अगरtype type,
					  u8 fw_vअगर_idx, u8 nw_type);
व्योम ath6kl_cfg80211_ch_चयन_notअगरy(काष्ठा ath6kl_vअगर *vअगर, पूर्णांक freq,
				      क्रमागत wmi_phy_mode mode);
व्योम ath6kl_cfg80211_scan_complete_event(काष्ठा ath6kl_vअगर *vअगर, bool पातed);

व्योम ath6kl_cfg80211_connect_event(काष्ठा ath6kl_vअगर *vअगर, u16 channel,
				   u8 *bssid, u16 listen_पूर्णांकvl,
				   u16 beacon_पूर्णांकvl,
				   क्रमागत network_type nw_type,
				   u8 beacon_ie_len, u8 assoc_req_len,
				   u8 assoc_resp_len, u8 *assoc_info);

व्योम ath6kl_cfg80211_disconnect_event(काष्ठा ath6kl_vअगर *vअगर, u8 reason,
				      u8 *bssid, u8 assoc_resp_len,
				      u8 *assoc_info, u16 proto_reason);

व्योम ath6kl_cfg80211_tkip_micerr_event(काष्ठा ath6kl_vअगर *vअगर, u8 keyid,
				     bool ismcast);

पूर्णांक ath6kl_cfg80211_suspend(काष्ठा ath6kl *ar,
			    क्रमागत ath6kl_cfg_suspend_mode mode,
			    काष्ठा cfg80211_wowlan *wow);

पूर्णांक ath6kl_cfg80211_resume(काष्ठा ath6kl *ar);

व्योम ath6kl_cfg80211_vअगर_cleanup(काष्ठा ath6kl_vअगर *vअगर);

व्योम ath6kl_cfg80211_stop(काष्ठा ath6kl_vअगर *vअगर);
व्योम ath6kl_cfg80211_stop_all(काष्ठा ath6kl *ar);

पूर्णांक ath6kl_cfg80211_init(काष्ठा ath6kl *ar);
व्योम ath6kl_cfg80211_cleanup(काष्ठा ath6kl *ar);

काष्ठा ath6kl *ath6kl_cfg80211_create(व्योम);
व्योम ath6kl_cfg80211_destroy(काष्ठा ath6kl *ar);

#पूर्ण_अगर /* ATH6KL_CFG80211_H */
