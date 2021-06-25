<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __REALTEK_PCI92SE_TRX_H__
#घोषणा __REALTEK_PCI92SE_TRX_H__

व्योम rtl92se_tx_fill_desc(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_hdr *hdr, u8 *pdesc,
			  u8 *pbd_desc_tx, काष्ठा ieee80211_tx_info *info,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा sk_buff *skb, u8 hw_queue,
			  काष्ठा rtl_tcb_desc *ptcb_desc);
व्योम rtl92se_tx_fill_cmddesc(काष्ठा ieee80211_hw *hw, u8 *pdesc, bool firstseg,
			     bool lastseg, काष्ठा sk_buff *skb);
bool rtl92se_rx_query_desc(काष्ठा ieee80211_hw *hw, काष्ठा rtl_stats *stats,
			   काष्ठा ieee80211_rx_status *rx_status, u8 *pdesc,
			   काष्ठा sk_buff *skb);
व्योम rtl92se_set_desc(काष्ठा ieee80211_hw *hw, u8 *pdesc, bool istx,
		      u8 desc_name, u8 *val);
u64 rtl92se_get_desc(काष्ठा ieee80211_hw *hw,
		     u8 *desc, bool istx, u8 desc_name);
व्योम rtl92se_tx_polling(काष्ठा ieee80211_hw *hw, u8 hw_queue);

#पूर्ण_अगर
