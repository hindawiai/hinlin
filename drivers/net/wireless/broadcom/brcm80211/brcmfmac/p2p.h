<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012 Broadcom Corporation
 */
#अगर_अघोषित WL_CFGP2P_H_
#घोषणा WL_CFGP2P_H_

#समावेश <net/cfg80211.h>

काष्ठा brcmf_cfg80211_info;

/**
 * क्रमागत p2p_bss_type - dअगरferent type of BSS configurations.
 *
 * @P2PAPI_BSSCFG_PRIMARY: maps to driver's primary bsscfg.
 * @P2PAPI_BSSCFG_DEVICE: maps to driver's P2P device discovery bsscfg.
 * @P2PAPI_BSSCFG_CONNECTION: maps to driver's 1st P2P connection bsscfg.
 * @P2PAPI_BSSCFG_CONNECTION2: maps to driver's 2nd P2P connection bsscfg.
 * @P2PAPI_BSSCFG_MAX: used क्रम range checking.
 */
क्रमागत p2p_bss_type अणु
	P2PAPI_BSSCFG_PRIMARY, /* maps to driver's primary bsscfg */
	P2PAPI_BSSCFG_DEVICE, /* maps to driver's P2P device discovery bsscfg */
	P2PAPI_BSSCFG_CONNECTION, /* driver's 1st P2P connection bsscfg */
	P2PAPI_BSSCFG_CONNECTION2, /* driver's 2nd P2P connection bsscfg */
	P2PAPI_BSSCFG_MAX
पूर्ण;

/**
 * काष्ठा p2p_bss - peer-to-peer bss related inक्रमmation.
 *
 * @vअगर: भव पूर्णांकerface of this P2P bss.
 * @निजी_data: TBD
 */
काष्ठा p2p_bss अणु
	काष्ठा brcmf_cfg80211_vअगर *vअगर;
	व्योम *निजी_data;
पूर्ण;

/**
 * क्रमागत brcmf_p2p_status - P2P specअगरic करोngle status.
 *
 * @BRCMF_P2P_STATUS_IF_ADD: peer-to-peer vअगर add sent to करोngle.
 * @BRCMF_P2P_STATUS_IF_DEL: NOT-USED?
 * @BRCMF_P2P_STATUS_IF_DELETING: peer-to-peer vअगर delete sent to करोngle.
 * @BRCMF_P2P_STATUS_IF_CHANGING: peer-to-peer vअगर change sent to करोngle.
 * @BRCMF_P2P_STATUS_IF_CHANGED: peer-to-peer vअगर change completed on करोngle.
 * @BRCMF_P2P_STATUS_ACTION_TX_COMPLETED: action frame tx completed.
 * @BRCMF_P2P_STATUS_ACTION_TX_NOACK: action frame tx not acked.
 * @BRCMF_P2P_STATUS_GO_NEG_PHASE: P2P GO negotiation ongoing.
 * @BRCMF_P2P_STATUS_DISCOVER_LISTEN: P2P listen, reमुख्यing on channel.
 * @BRCMF_P2P_STATUS_SENDING_ACT_FRAME: In the process of sending action frame.
 * @BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN: extra listen समय क्रम af tx.
 * @BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME: रुकोing क्रम action frame response.
 * @BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL: search channel क्रम AF active.
 */
क्रमागत brcmf_p2p_status अणु
	BRCMF_P2P_STATUS_ENABLED,
	BRCMF_P2P_STATUS_IF_ADD,
	BRCMF_P2P_STATUS_IF_DEL,
	BRCMF_P2P_STATUS_IF_DELETING,
	BRCMF_P2P_STATUS_IF_CHANGING,
	BRCMF_P2P_STATUS_IF_CHANGED,
	BRCMF_P2P_STATUS_ACTION_TX_COMPLETED,
	BRCMF_P2P_STATUS_ACTION_TX_NOACK,
	BRCMF_P2P_STATUS_GO_NEG_PHASE,
	BRCMF_P2P_STATUS_DISCOVER_LISTEN,
	BRCMF_P2P_STATUS_SENDING_ACT_FRAME,
	BRCMF_P2P_STATUS_WAITING_NEXT_AF_LISTEN,
	BRCMF_P2P_STATUS_WAITING_NEXT_ACT_FRAME,
	BRCMF_P2P_STATUS_FINDING_COMMON_CHANNEL
पूर्ण;

/**
 * काष्ठा afx_hdl - action frame off channel storage.
 *
 * @afx_work: worker thपढ़ो क्रम searching channel
 * @act_frm_scan: thपढ़ो synchronizing काष्ठा.
 * @is_active: channel searching active.
 * @peer_chan: current channel.
 * @is_listen: sets mode क्रम afx worker.
 * @my_listen_chan: this peers listen channel.
 * @peer_listen_chan: remote peers listen channel.
 * @tx_dst_addr: mac address where tx af should be sent to.
 */
काष्ठा afx_hdl अणु
	काष्ठा work_काष्ठा afx_work;
	काष्ठा completion act_frm_scan;
	bool is_active;
	s32 peer_chan;
	bool is_listen;
	u16 my_listen_chan;
	u16 peer_listen_chan;
	u8 tx_dst_addr[ETH_ALEN];
पूर्ण;

/**
 * काष्ठा brcmf_p2p_info - p2p specअगरic driver inक्रमmation.
 *
 * @cfg: driver निजी data क्रम cfg80211 पूर्णांकerface.
 * @status: status of P2P (see क्रमागत brcmf_p2p_status).
 * @dev_addr: P2P device address.
 * @पूर्णांक_addr: P2P पूर्णांकerface address.
 * @bss_idx: inक्रमmate क्रम P2P bss types.
 * @listen_समयr: समयr क्रम @WL_P2P_DISC_ST_LISTEN discover state.
 * @listen_channel: channel क्रम @WL_P2P_DISC_ST_LISTEN discover state.
 * @reमुख्य_on_channel: contains copy of काष्ठा used by cfg80211.
 * @reमुख्य_on_channel_cookie: cookie counter क्रम reमुख्य on channel cmd
 * @next_af_subtype: expected action frame subtype.
 * @send_af_करोne: indication that action frame tx is complete.
 * @afx_hdl: action frame search handler info.
 * @af_sent_channel: channel action frame is sent.
 * @af_tx_sent_jअगरfies: jअगरfies समय when af tx was transmitted.
 * @रुको_next_af: thपढ़ो synchronizing काष्ठा.
 * @gon_req_action: about to send go negotiation requets frame.
 * @block_gon_req_tx: drop tx go negotiation requets frame.
 * @p2pdev_dynamically: is p2p device अगर created by module param or supplicant.
 * @रुको_क्रम_offchan_complete: रुको क्रम off-channel tx completion event.
 */
काष्ठा brcmf_p2p_info अणु
	काष्ठा brcmf_cfg80211_info *cfg;
	अचिन्हित दीर्घ status;
	u8 dev_addr[ETH_ALEN];
	u8 conn_पूर्णांक_addr[ETH_ALEN];
	u8 conn2_पूर्णांक_addr[ETH_ALEN];
	काष्ठा p2p_bss bss_idx[P2PAPI_BSSCFG_MAX];
	काष्ठा समयr_list listen_समयr;
	u8 listen_channel;
	काष्ठा ieee80211_channel reमुख्य_on_channel;
	u32 reमुख्य_on_channel_cookie;
	u8 next_af_subtype;
	काष्ठा completion send_af_करोne;
	काष्ठा afx_hdl afx_hdl;
	u32 af_sent_channel;
	अचिन्हित दीर्घ af_tx_sent_jअगरfies;
	काष्ठा completion रुको_next_af;
	bool gon_req_action;
	bool block_gon_req_tx;
	bool p2pdev_dynamically;
	bool रुको_क्रम_offchan_complete;
पूर्ण;

s32 brcmf_p2p_attach(काष्ठा brcmf_cfg80211_info *cfg, bool p2pdev_क्रमced);
व्योम brcmf_p2p_detach(काष्ठा brcmf_p2p_info *p2p);
काष्ठा wireless_dev *brcmf_p2p_add_vअगर(काष्ठा wiphy *wiphy, स्थिर अक्षर *name,
				       अचिन्हित अक्षर name_assign_type,
				       क्रमागत nl80211_अगरtype type,
				       काष्ठा vअगर_params *params);
पूर्णांक brcmf_p2p_del_vअगर(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev);
पूर्णांक brcmf_p2p_अगरchange(काष्ठा brcmf_cfg80211_info *cfg,
		       क्रमागत brcmf_fil_p2p_अगर_types अगर_type);
व्योम brcmf_p2p_अगरp_हटाओd(काष्ठा brcmf_अगर *अगरp, bool rtnl_locked);
पूर्णांक brcmf_p2p_start_device(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev);
व्योम brcmf_p2p_stop_device(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev);
पूर्णांक brcmf_p2p_scan_prep(काष्ठा wiphy *wiphy,
			काष्ठा cfg80211_scan_request *request,
			काष्ठा brcmf_cfg80211_vअगर *vअगर);
पूर्णांक brcmf_p2p_reमुख्य_on_channel(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				काष्ठा ieee80211_channel *channel,
				अचिन्हित पूर्णांक duration, u64 *cookie);
पूर्णांक brcmf_p2p_notअगरy_listen_complete(काष्ठा brcmf_अगर *अगरp,
				     स्थिर काष्ठा brcmf_event_msg *e,
				     व्योम *data);
व्योम brcmf_p2p_cancel_reमुख्य_on_channel(काष्ठा brcmf_अगर *अगरp);
पूर्णांक brcmf_p2p_notअगरy_action_frame_rx(काष्ठा brcmf_अगर *अगरp,
				     स्थिर काष्ठा brcmf_event_msg *e,
				     व्योम *data);
पूर्णांक brcmf_p2p_notअगरy_action_tx_complete(काष्ठा brcmf_अगर *अगरp,
					स्थिर काष्ठा brcmf_event_msg *e,
					व्योम *data);
bool brcmf_p2p_send_action_frame(काष्ठा brcmf_cfg80211_info *cfg,
				 काष्ठा net_device *ndev,
				 काष्ठा brcmf_fil_af_params_le *af_params);
bool brcmf_p2p_scan_finding_common_channel(काष्ठा brcmf_cfg80211_info *cfg,
					   काष्ठा brcmf_bss_info_le *bi);
s32 brcmf_p2p_notअगरy_rx_mgmt_p2p_probereq(काष्ठा brcmf_अगर *अगरp,
					  स्थिर काष्ठा brcmf_event_msg *e,
					  व्योम *data);
#पूर्ण_अगर /* WL_CFGP2P_H_ */
