<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __RTL_CAM_H_
#घोषणा __RTL_CAM_H_

#घोषणा CAM_CONTENT_COUNT				8

#घोषणा CFG_VALID					BIT(15)

#घोषणा PAIRWISE_KEYIDX					0
#घोषणा CAM_PAIRWISE_KEY_POSITION			4

#घोषणा	CAM_CONFIG_NO_USEDK				0

व्योम rtl_cam_reset_all_entry(काष्ठा ieee80211_hw *hw);
u8 rtl_cam_add_one_entry(काष्ठा ieee80211_hw *hw, u8 *mac_addr,
				u32 ul_key_id, u32 ul_entry_idx, u32 ul_enc_alg,
				u32 ul_शेष_key, u8 *key_content);
पूर्णांक rtl_cam_delete_one_entry(काष्ठा ieee80211_hw *hw, u8 *mac_addr,
			     u32 ul_key_id);
व्योम rtl_cam_mark_invalid(काष्ठा ieee80211_hw *hw, u8 uc_index);
व्योम rtl_cam_empty_entry(काष्ठा ieee80211_hw *hw, u8 uc_index);
व्योम rtl_cam_reset_sec_info(काष्ठा ieee80211_hw *hw);
u8 rtl_cam_get_मुक्त_entry(काष्ठा ieee80211_hw *hw, u8 *sta_addr);
व्योम rtl_cam_del_entry(काष्ठा ieee80211_hw *hw, u8 *sta_addr);

#पूर्ण_अगर
