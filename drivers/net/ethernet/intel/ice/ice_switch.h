<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_SWITCH_H_
#घोषणा _ICE_SWITCH_H_

#समावेश "ice_common.h"

#घोषणा ICE_SW_CFG_MAX_BUF_LEN 2048
#घोषणा ICE_DFLT_VSI_INVAL 0xff
#घोषणा ICE_FLTR_RX BIT(0)
#घोषणा ICE_FLTR_TX BIT(1)
#घोषणा ICE_FLTR_TX_RX (ICE_FLTR_RX | ICE_FLTR_TX)
#घोषणा ICE_VSI_INVAL_ID 0xffff
#घोषणा ICE_INVAL_Q_HANDLE 0xFFFF

/* VSI context काष्ठाure क्रम add/get/update/मुक्त operations */
काष्ठा ice_vsi_ctx अणु
	u16 vsi_num;
	u16 vsis_allocd;
	u16 vsis_unallocated;
	u16 flags;
	काष्ठा ice_aqc_vsi_props info;
	काष्ठा ice_sched_vsi_info sched;
	u8 alloc_from_pool;
	u8 vf_num;
	u16 num_lan_q_entries[ICE_MAX_TRAFFIC_CLASS];
	काष्ठा ice_q_ctx *lan_q_ctx[ICE_MAX_TRAFFIC_CLASS];
पूर्ण;

क्रमागत ice_sw_fwd_act_type अणु
	ICE_FWD_TO_VSI = 0,
	ICE_FWD_TO_VSI_LIST, /* Do not use this when adding filter */
	ICE_FWD_TO_Q,
	ICE_FWD_TO_QGRP,
	ICE_DROP_PACKET,
	ICE_INVAL_ACT
पूर्ण;

/* Switch recipe ID क्रमागत values are specअगरic to hardware */
क्रमागत ice_sw_lkup_type अणु
	ICE_SW_LKUP_ETHERTYPE = 0,
	ICE_SW_LKUP_MAC = 1,
	ICE_SW_LKUP_MAC_VLAN = 2,
	ICE_SW_LKUP_PROMISC = 3,
	ICE_SW_LKUP_VLAN = 4,
	ICE_SW_LKUP_DFLT = 5,
	ICE_SW_LKUP_ETHERTYPE_MAC = 8,
	ICE_SW_LKUP_PROMISC_VLAN = 9,
	ICE_SW_LKUP_LAST
पूर्ण;

/* type of filter src ID */
क्रमागत ice_src_id अणु
	ICE_SRC_ID_UNKNOWN = 0,
	ICE_SRC_ID_VSI,
	ICE_SRC_ID_QUEUE,
	ICE_SRC_ID_LPORT,
पूर्ण;

काष्ठा ice_fltr_info अणु
	/* Look up inक्रमmation: how to look up packet */
	क्रमागत ice_sw_lkup_type lkup_type;
	/* Forward action: filter action to करो after lookup */
	क्रमागत ice_sw_fwd_act_type fltr_act;
	/* rule ID वापसed by firmware once filter rule is created */
	u16 fltr_rule_id;
	u16 flag;

	/* Source VSI क्रम LOOKUP_TX or source port क्रम LOOKUP_RX */
	u16 src;
	क्रमागत ice_src_id src_id;

	जोड़ अणु
		काष्ठा अणु
			u8 mac_addr[ETH_ALEN];
		पूर्ण mac;
		काष्ठा अणु
			u8 mac_addr[ETH_ALEN];
			u16 vlan_id;
		पूर्ण mac_vlan;
		काष्ठा अणु
			u16 vlan_id;
		पूर्ण vlan;
		/* Set lkup_type as ICE_SW_LKUP_ETHERTYPE
		 * अगर just using ethertype as filter. Set lkup_type as
		 * ICE_SW_LKUP_ETHERTYPE_MAC अगर MAC also needs to be
		 * passed in as filter.
		 */
		काष्ठा अणु
			u16 ethertype;
			u8 mac_addr[ETH_ALEN]; /* optional */
		पूर्ण ethertype_mac;
	पूर्ण l_data; /* Make sure to zero out the memory of l_data beक्रमe using
		   * it or only set the data associated with lookup match
		   * rest everything should be zero
		   */

	/* Depending on filter action */
	जोड़ अणु
		/* queue ID in हाल of ICE_FWD_TO_Q and starting
		 * queue ID in हाल of ICE_FWD_TO_QGRP.
		 */
		u16 q_id:11;
		u16 hw_vsi_id:10;
		u16 vsi_list_id:10;
	पूर्ण fwd_id;

	/* Sw VSI handle */
	u16 vsi_handle;

	/* Set to num_queues अगर action is ICE_FWD_TO_QGRP. This field
	 * determines the range of queues the packet needs to be क्रमwarded to.
	 * Note that qgrp_size must be set to a घातer of 2.
	 */
	u8 qgrp_size;

	/* Rule creations populate these indicators basing on the चयन type */
	u8 lb_en;	/* Indicate अगर packet can be looped back */
	u8 lan_en;	/* Indicate अगर packet can be क्रमwarded to the uplink */
पूर्ण;

काष्ठा ice_sw_recipe अणु
	काष्ठा list_head l_entry;

	/* To protect modअगरication of filt_rule list
	 * defined below
	 */
	काष्ठा mutex filt_rule_lock;

	/* List of type ice_fltr_mgmt_list_entry */
	काष्ठा list_head filt_rules;
	काष्ठा list_head filt_replay_rules;

	/* linked list of type recipe_list_entry */
	काष्ठा list_head rg_list;
	/* linked list of type ice_sw_fv_list_entry*/
	काष्ठा list_head fv_list;
	काष्ठा ice_aqc_recipe_data_elem *r_buf;
	u8 recp_count;
	u8 root_rid;
	u8 num_profs;
	u8 *prof_ids;

	/* recipe biपंचांगap: what all recipes makes this recipe */
	DECLARE_BITMAP(r_biपंचांगap, ICE_MAX_NUM_RECIPES);
पूर्ण;

/* Bookkeeping काष्ठाure to hold biपंचांगap of VSIs corresponding to VSI list ID */
काष्ठा ice_vsi_list_map_info अणु
	काष्ठा list_head list_entry;
	DECLARE_BITMAP(vsi_map, ICE_MAX_VSI);
	u16 vsi_list_id;
	/* counter to track how many rules are reusing this VSI list */
	u16 ref_cnt;
पूर्ण;

काष्ठा ice_fltr_list_entry अणु
	काष्ठा list_head list_entry;
	क्रमागत ice_status status;
	काष्ठा ice_fltr_info fltr_info;
पूर्ण;

/* This defines an entry in the list that मुख्यtains MAC or VLAN membership
 * to HW list mapping, since multiple VSIs can subscribe to the same MAC or
 * VLAN. As an optimization the VSI list should be created only when a
 * second VSI becomes a subscriber to the same MAC address. VSI lists are always
 * used क्रम VLAN membership.
 */
काष्ठा ice_fltr_mgmt_list_entry अणु
	/* back poपूर्णांकer to VSI list ID to VSI list mapping */
	काष्ठा ice_vsi_list_map_info *vsi_list_info;
	u16 vsi_count;
#घोषणा ICE_INVAL_LG_ACT_INDEX 0xffff
	u16 lg_act_idx;
#घोषणा ICE_INVAL_SW_MARKER_ID 0xffff
	u16 sw_marker_id;
	काष्ठा list_head list_entry;
	काष्ठा ice_fltr_info fltr_info;
#घोषणा ICE_INVAL_COUNTER_ID 0xff
	u8 counter_index;
पूर्ण;

क्रमागत ice_promisc_flags अणु
	ICE_PROMISC_UCAST_RX = 0x1,
	ICE_PROMISC_UCAST_TX = 0x2,
	ICE_PROMISC_MCAST_RX = 0x4,
	ICE_PROMISC_MCAST_TX = 0x8,
	ICE_PROMISC_BCAST_RX = 0x10,
	ICE_PROMISC_BCAST_TX = 0x20,
	ICE_PROMISC_VLAN_RX = 0x40,
	ICE_PROMISC_VLAN_TX = 0x80,
पूर्ण;

/* VSI related commands */
क्रमागत ice_status
ice_add_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_vsi_ctx *vsi_ctx,
	    काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_मुक्त_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_vsi_ctx *vsi_ctx,
	     bool keep_vsi_alloc, काष्ठा ice_sq_cd *cd);
क्रमागत ice_status
ice_update_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_vsi_ctx *vsi_ctx,
	       काष्ठा ice_sq_cd *cd);
bool ice_is_vsi_valid(काष्ठा ice_hw *hw, u16 vsi_handle);
काष्ठा ice_vsi_ctx *ice_get_vsi_ctx(काष्ठा ice_hw *hw, u16 vsi_handle);
व्योम ice_clear_all_vsi_ctx(काष्ठा ice_hw *hw);
/* Switch config */
क्रमागत ice_status ice_get_initial_sw_cfg(काष्ठा ice_hw *hw);

क्रमागत ice_status
ice_alloc_res_cntr(काष्ठा ice_hw *hw, u8 type, u8 alloc_shared, u16 num_items,
		   u16 *counter_id);
क्रमागत ice_status
ice_मुक्त_res_cntr(काष्ठा ice_hw *hw, u8 type, u8 alloc_shared, u16 num_items,
		  u16 counter_id);

/* Switch/bridge related commands */
क्रमागत ice_status ice_update_sw_rule_bridge_mode(काष्ठा ice_hw *hw);
क्रमागत ice_status ice_add_mac(काष्ठा ice_hw *hw, काष्ठा list_head *m_lst);
क्रमागत ice_status ice_हटाओ_mac(काष्ठा ice_hw *hw, काष्ठा list_head *m_lst);
क्रमागत ice_status
ice_add_eth_mac(काष्ठा ice_hw *hw, काष्ठा list_head *em_list);
क्रमागत ice_status
ice_हटाओ_eth_mac(काष्ठा ice_hw *hw, काष्ठा list_head *em_list);
व्योम ice_हटाओ_vsi_fltr(काष्ठा ice_hw *hw, u16 vsi_handle);
क्रमागत ice_status
ice_add_vlan(काष्ठा ice_hw *hw, काष्ठा list_head *m_list);
क्रमागत ice_status ice_हटाओ_vlan(काष्ठा ice_hw *hw, काष्ठा list_head *v_list);

/* Promisc/defport setup क्रम VSIs */
क्रमागत ice_status
ice_cfg_dflt_vsi(काष्ठा ice_hw *hw, u16 vsi_handle, bool set, u8 direction);
क्रमागत ice_status
ice_set_vsi_promisc(काष्ठा ice_hw *hw, u16 vsi_handle, u8 promisc_mask,
		    u16 vid);
क्रमागत ice_status
ice_clear_vsi_promisc(काष्ठा ice_hw *hw, u16 vsi_handle, u8 promisc_mask,
		      u16 vid);
क्रमागत ice_status
ice_set_vlan_vsi_promisc(काष्ठा ice_hw *hw, u16 vsi_handle, u8 promisc_mask,
			 bool rm_vlan_promisc);

क्रमागत ice_status ice_init_def_sw_recp(काष्ठा ice_hw *hw);
u16 ice_get_hw_vsi_num(काष्ठा ice_hw *hw, u16 vsi_handle);
bool ice_is_vsi_valid(काष्ठा ice_hw *hw, u16 vsi_handle);

क्रमागत ice_status ice_replay_vsi_all_fltr(काष्ठा ice_hw *hw, u16 vsi_handle);
व्योम ice_rm_all_sw_replay_rule_info(काष्ठा ice_hw *hw);

#पूर्ण_अगर /* _ICE_SWITCH_H_ */
