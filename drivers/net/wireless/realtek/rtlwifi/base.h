<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_BASE_H__
#घोषणा __RTL_BASE_H__

क्रमागत ap_peer अणु
	PEER_UNKNOWN = 0,
	PEER_RTL = 1,
	PEER_RTL_92SE = 2,
	PEER_BROAD = 3,
	PEER_RAL = 4,
	PEER_ATH = 5,
	PEER_CISCO = 6,
	PEER_MARV = 7,
	PEER_AIRGO = 9,
	PEER_MAX = 10,
पूर्ण;

#घोषणा RTL_DUMMY_OFFSET	0
#घोषणा RTL_DUMMY_UNIT		8
#घोषणा RTL_TX_DUMMY_SIZE	(RTL_DUMMY_OFFSET * RTL_DUMMY_UNIT)
#घोषणा RTL_TX_DESC_SIZE	32
#घोषणा RTL_TX_HEADER_SIZE	(RTL_TX_DESC_SIZE + RTL_TX_DUMMY_SIZE)

#घोषणा MAX_BIT_RATE_40MHZ_MCS15	300	/* Mbps */
#घोषणा MAX_BIT_RATE_40MHZ_MCS7		150	/* Mbps */

#घोषणा MAX_BIT_RATE_SHORT_GI_2NSS_80MHZ_MCS9	867	/* Mbps */
#घोषणा MAX_BIT_RATE_SHORT_GI_2NSS_80MHZ_MCS7	650	/* Mbps */
#घोषणा MAX_BIT_RATE_LONG_GI_2NSS_80MHZ_MCS9	780	/* Mbps */
#घोषणा MAX_BIT_RATE_LONG_GI_2NSS_80MHZ_MCS7	585	/* Mbps */

#घोषणा MAX_BIT_RATE_SHORT_GI_1NSS_80MHZ_MCS9	434	/* Mbps */
#घोषणा MAX_BIT_RATE_SHORT_GI_1NSS_80MHZ_MCS7	325	/* Mbps */
#घोषणा MAX_BIT_RATE_LONG_GI_1NSS_80MHZ_MCS9	390	/* Mbps */
#घोषणा MAX_BIT_RATE_LONG_GI_1NSS_80MHZ_MCS7	293	/* Mbps */

#घोषणा FRAME_OFFSET_FRAME_CONTROL	0
#घोषणा FRAME_OFFSET_DURATION		2
#घोषणा FRAME_OFFSET_ADDRESS1		4
#घोषणा FRAME_OFFSET_ADDRESS2		10
#घोषणा FRAME_OFFSET_ADDRESS3		16
#घोषणा FRAME_OFFSET_SEQUENCE		22
#घोषणा FRAME_OFFSET_ADDRESS4		24
#घोषणा MAX_LISTEN_INTERVAL		10
#घोषणा MAX_RATE_TRIES			4

#घोषणा SET_80211_PS_POLL_AID(_hdr, _val)		\
	(*(u16 *)((u8 *)(_hdr) + 2) = _val)
#घोषणा SET_80211_PS_POLL_BSSID(_hdr, _val)		\
	ether_addr_copy(((u8 *)(_hdr)) + 4, (u8 *)(_val))
#घोषणा SET_80211_PS_POLL_TA(_hdr, _val)		\
	ether_addr_copy(((u8 *)(_hdr))+10, (u8 *)(_val))

#घोषणा SET_80211_HDR_ADDRESS1(_hdr, _val)	\
	CP_MACADDR((u8 *)(_hdr)+FRAME_OFFSET_ADDRESS1, (u8 *)(_val))
#घोषणा SET_80211_HDR_ADDRESS2(_hdr, _val)	\
	CP_MACADDR((u8 *)(_hdr)+FRAME_OFFSET_ADDRESS2, (u8 *)(_val))
#घोषणा SET_80211_HDR_ADDRESS3(_hdr, _val)	\
	CP_MACADDR((u8 *)(_hdr)+FRAME_OFFSET_ADDRESS3, (u8 *)(_val))

#घोषणा SET_TX_DESC_SPE_RPT(__pdesc, __val)			\
	le32p_replace_bits((__le32 *)(__pdesc + 8), __val, BIT(19))
#घोषणा SET_TX_DESC_SW_DEFINE(__pdesc, __val)	\
	le32p_replace_bits((__le32 *)(__pdesc + 24), __val, GENMASK(11, 0))

पूर्णांक rtl_init_core(काष्ठा ieee80211_hw *hw);
व्योम rtl_deinit_core(काष्ठा ieee80211_hw *hw);
व्योम rtl_init_rx_config(काष्ठा ieee80211_hw *hw);
व्योम rtl_init_rfसमाप्त(काष्ठा ieee80211_hw *hw);
व्योम rtl_deinit_rfसमाप्त(काष्ठा ieee80211_hw *hw);

व्योम rtl_watch_करोg_समयr_callback(काष्ठा समयr_list *t);
व्योम rtl_deinit_deferred_work(काष्ठा ieee80211_hw *hw, bool ips_wq);

bool rtl_action_proc(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb, u8 is_tx);
पूर्णांक rtlwअगरi_rate_mapping(काष्ठा ieee80211_hw *hw, bool isht,
			 bool isvht, u8 desc_rate);
bool rtl_tx_mgmt_proc(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);
u8 rtl_is_special_data(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb, u8 is_tx,
		       bool is_enc);

व्योम rtl_tx_ackqueue(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);
bool rtl_is_tx_report_skb(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);
व्योम rtl_set_tx_report(काष्ठा rtl_tcb_desc *ptcb_desc, u8 *pdesc,
		       काष्ठा ieee80211_hw *hw, काष्ठा rtlwअगरi_tx_info *info);
व्योम rtl_tx_report_handler(काष्ठा ieee80211_hw *hw, u8 *पंचांगp_buf,
			   u8 c2h_cmd_len);
bool rtl_check_tx_report_acked(काष्ठा ieee80211_hw *hw);
व्योम rtl_रुको_tx_report_acked(काष्ठा ieee80211_hw *hw, u32 रुको_ms);
u32 rtl_get_hal_edca_param(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर,
			   क्रमागत wireless_mode wirelessmode,
			   काष्ठा ieee80211_tx_queue_params *param);

व्योम rtl_beacon_statistic(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);
व्योम rtl_collect_scan_list(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);
व्योम rtl_scan_list_expire(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl_tx_agg_start(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	काष्ठा ieee80211_sta *sta, u16 tid, u16 *ssn);
पूर्णांक rtl_tx_agg_stop(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
	काष्ठा ieee80211_sta *sta, u16 tid);
पूर्णांक rtl_tx_agg_oper(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_sta *sta, u16 tid);
पूर्णांक rtl_rx_agg_start(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_sta *sta, u16 tid);
पूर्णांक rtl_rx_agg_stop(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_sta *sta, u16 tid);
व्योम rtl_rx_ampdu_apply(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_c2hcmd_launcher(काष्ठा ieee80211_hw *hw, पूर्णांक exec);
व्योम rtl_c2hcmd_enqueue(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb);

u8 rtl_mrate_idx_to_arfr_id(काष्ठा ieee80211_hw *hw, u8 rate_index,
			    क्रमागत wireless_mode wirelessmode);
व्योम rtl_get_tcb_desc(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_info *info,
		      काष्ठा ieee80211_sta *sta,
		      काष्ठा sk_buff *skb, काष्ठा rtl_tcb_desc *tcb_desc);

पूर्णांक rtl_send_smps_action(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta,
		क्रमागत ieee80211_smps_mode smps);
u8 *rtl_find_ie(u8 *data, अचिन्हित पूर्णांक len, u8 ie);
व्योम rtl_recognize_peer(काष्ठा ieee80211_hw *hw, u8 *data, अचिन्हित पूर्णांक len);
u8 rtl_tid_to_ac(u8 tid);
व्योम rtl_easy_concurrent_retryसमयr_callback(काष्ठा समयr_list *t);
बाह्य काष्ठा rtl_global_var rtl_global_var;
व्योम rtl_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw, u8 operation);

#पूर्ण_अगर
