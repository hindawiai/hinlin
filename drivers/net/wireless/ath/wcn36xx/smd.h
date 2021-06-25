<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#अगर_अघोषित _SMD_H_
#घोषणा _SMD_H_

#समावेश "wcn36xx.h"

/* Max shared size is 4k but we take less.*/
#घोषणा WCN36XX_NV_FRAGMENT_SIZE			3072

#घोषणा WCN36XX_HAL_BUF_SIZE				4096

#घोषणा HAL_MSG_TIMEOUT 10000
#घोषणा WCN36XX_SMSM_WLAN_TX_ENABLE			0x00000400
#घोषणा WCN36XX_SMSM_WLAN_TX_RINGS_EMPTY		0x00000200
/* The PNO version info be contained in the rsp msg */
#घोषणा WCN36XX_FW_MSG_PNO_VERSION_MASK			0x8000

क्रमागत wcn36xx_fw_msg_result अणु
	WCN36XX_FW_MSG_RESULT_SUCCESS			= 0,
	WCN36XX_FW_MSG_RESULT_SUCCESS_SYNC		= 1,

	WCN36XX_FW_MSG_RESULT_MEM_FAIL			= 5,
पूर्ण;

/******************************/
/* SMD requests and responses */
/******************************/
काष्ठा wcn36xx_fw_msg_status_rsp अणु
	u32	status;
पूर्ण __packed;

काष्ठा wcn36xx_hal_ind_msg अणु
	काष्ठा list_head list;
	माप_प्रकार msg_len;
	u8 msg[];
पूर्ण;

काष्ठा wcn36xx;
काष्ठा rpmsg_device;

पूर्णांक wcn36xx_smd_खोलो(काष्ठा wcn36xx *wcn);
व्योम wcn36xx_smd_बंद(काष्ठा wcn36xx *wcn);

पूर्णांक wcn36xx_smd_load_nv(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_smd_start(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_smd_stop(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_smd_start_scan(काष्ठा wcn36xx *wcn, u8 scan_channel);
पूर्णांक wcn36xx_smd_end_scan(काष्ठा wcn36xx *wcn, u8 scan_channel);
पूर्णांक wcn36xx_smd_finish_scan(काष्ठा wcn36xx *wcn, क्रमागत wcn36xx_hal_sys_mode mode,
			    काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wcn36xx_smd_init_scan(काष्ठा wcn36xx *wcn, क्रमागत wcn36xx_hal_sys_mode mode,
			  काष्ठा ieee80211_vअगर *vअगर);

पूर्णांक wcn36xx_smd_update_scan_params(काष्ठा wcn36xx *wcn, u8 *channels, माप_प्रकार channel_count);
पूर्णांक wcn36xx_smd_start_hw_scan(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा cfg80211_scan_request *req);
पूर्णांक wcn36xx_smd_stop_hw_scan(काष्ठा wcn36xx *wcn);
पूर्णांक wcn36xx_smd_add_sta_self(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wcn36xx_smd_delete_sta_self(काष्ठा wcn36xx *wcn, u8 *addr);
पूर्णांक wcn36xx_smd_delete_sta(काष्ठा wcn36xx *wcn, u8 sta_index);
पूर्णांक wcn36xx_smd_join(काष्ठा wcn36xx *wcn, स्थिर u8 *bssid, u8 *vअगर, u8 ch);
पूर्णांक wcn36xx_smd_set_link_st(काष्ठा wcn36xx *wcn, स्थिर u8 *bssid,
			    स्थिर u8 *sta_mac,
			    क्रमागत wcn36xx_hal_link_state state);
पूर्णांक wcn36xx_smd_config_bss(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta, स्थिर u8 *bssid,
			   bool update);
पूर्णांक wcn36xx_smd_delete_bss(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wcn36xx_smd_config_sta(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta);
पूर्णांक wcn36xx_smd_send_beacon(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा sk_buff *skb_beacon, u16 tim_off,
			    u16 p2p_off);
पूर्णांक wcn36xx_smd_चयन_channel(काष्ठा wcn36xx *wcn,
			       काष्ठा ieee80211_vअगर *vअगर, पूर्णांक ch);
पूर्णांक wcn36xx_smd_process_ptt_msg(काष्ठा wcn36xx *wcn,
				काष्ठा ieee80211_vअगर *vअगर,
				व्योम *ptt_msg, माप_प्रकार len,
				व्योम **ptt_rsp_msg);
पूर्णांक wcn36xx_smd_update_proberesp_पंचांगpl(काष्ठा wcn36xx *wcn,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा sk_buff *skb);
पूर्णांक wcn36xx_smd_set_stakey(काष्ठा wcn36xx *wcn,
			   क्रमागत ani_ed_type enc_type,
			   u8 keyidx,
			   u8 keylen,
			   u8 *key,
			   u8 sta_index);
पूर्णांक wcn36xx_smd_set_bsskey(काष्ठा wcn36xx *wcn,
			   क्रमागत ani_ed_type enc_type,
			   u8 bssidx,
			   u8 keyidx,
			   u8 keylen,
			   u8 *key);
पूर्णांक wcn36xx_smd_हटाओ_stakey(काष्ठा wcn36xx *wcn,
			      क्रमागत ani_ed_type enc_type,
			      u8 keyidx,
			      u8 sta_index);
पूर्णांक wcn36xx_smd_हटाओ_bsskey(काष्ठा wcn36xx *wcn,
			      क्रमागत ani_ed_type enc_type,
			      u8 bssidx,
			      u8 keyidx);
पूर्णांक wcn36xx_smd_enter_bmps(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wcn36xx_smd_निकास_bmps(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक wcn36xx_smd_set_घातer_params(काष्ठा wcn36xx *wcn, bool ignore_dtim);
पूर्णांक wcn36xx_smd_keep_alive_req(काष्ठा wcn36xx *wcn,
			       काष्ठा ieee80211_vअगर *vअगर,
			       पूर्णांक packet_type);
पूर्णांक wcn36xx_smd_dump_cmd_req(काष्ठा wcn36xx *wcn, u32 arg1, u32 arg2,
			     u32 arg3, u32 arg4, u32 arg5);
पूर्णांक wcn36xx_smd_feature_caps_exchange(काष्ठा wcn36xx *wcn);
व्योम set_feat_caps(u32 *biपंचांगap, क्रमागत place_holder_in_cap_biपंचांगap cap);
पूर्णांक get_feat_caps(u32 *biपंचांगap, क्रमागत place_holder_in_cap_biपंचांगap cap);
व्योम clear_feat_caps(u32 *biपंचांगap, क्रमागत place_holder_in_cap_biपंचांगap cap);

पूर्णांक wcn36xx_smd_add_ba_session(काष्ठा wcn36xx *wcn,
		काष्ठा ieee80211_sta *sta,
		u16 tid,
		u16 *ssn,
		u8 direction,
		u8 sta_index);
पूर्णांक wcn36xx_smd_add_ba(काष्ठा wcn36xx *wcn, u8 session_id);
पूर्णांक wcn36xx_smd_del_ba(काष्ठा wcn36xx *wcn, u16 tid, u8 direction, u8 sta_index);
पूर्णांक wcn36xx_smd_trigger_ba(काष्ठा wcn36xx *wcn, u8 sta_index, u16 tid, u8 session_id);

पूर्णांक wcn36xx_smd_update_cfg(काष्ठा wcn36xx *wcn, u32 cfg_id, u32 value);

पूर्णांक wcn36xx_smd_rsp_process(काष्ठा rpmsg_device *rpdev,
			    व्योम *buf, पूर्णांक len, व्योम *priv, u32 addr);

पूर्णांक wcn36xx_smd_set_mc_list(काष्ठा wcn36xx *wcn,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा wcn36xx_hal_rcv_flt_mc_addr_list_type *fp);
#पूर्ण_अगर	/* _SMD_H_ */
