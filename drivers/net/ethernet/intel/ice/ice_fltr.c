<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2018-2020, Intel Corporation. */

#समावेश "ice.h"
#समावेश "ice_fltr.h"

/**
 * ice_fltr_मुक्त_list - मुक्त filter lists helper
 * @dev: poपूर्णांकer to the device काष्ठा
 * @h: poपूर्णांकer to the list head to be मुक्तd
 *
 * Helper function to मुक्त filter lists previously created using
 * ice_fltr_add_mac_to_list
 */
व्योम ice_fltr_मुक्त_list(काष्ठा device *dev, काष्ठा list_head *h)
अणु
	काष्ठा ice_fltr_list_entry *e, *पंचांगp;

	list_क्रम_each_entry_safe(e, पंचांगp, h, list_entry) अणु
		list_del(&e->list_entry);
		devm_kमुक्त(dev, e);
	पूर्ण
पूर्ण

/**
 * ice_fltr_add_entry_to_list - allocate and add filter entry to list
 * @dev: poपूर्णांकer to device needed by alloc function
 * @info: filter info काष्ठा that माला_लो added to the passed in list
 * @list: poपूर्णांकer to the list which contains MAC filters entry
 */
अटल पूर्णांक
ice_fltr_add_entry_to_list(काष्ठा device *dev, काष्ठा ice_fltr_info *info,
			   काष्ठा list_head *list)
अणु
	काष्ठा ice_fltr_list_entry *entry;

	entry = devm_kzalloc(dev, माप(*entry), GFP_ATOMIC);
	अगर (!entry)
		वापस -ENOMEM;

	entry->fltr_info = *info;

	INIT_LIST_HEAD(&entry->list_entry);
	list_add(&entry->list_entry, list);

	वापस 0;
पूर्ण

/**
 * ice_fltr_add_mac_list - add list of MAC filters
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list of filters
 */
क्रमागत ice_status
ice_fltr_add_mac_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list)
अणु
	वापस ice_add_mac(&vsi->back->hw, list);
पूर्ण

/**
 * ice_fltr_हटाओ_mac_list - हटाओ list of MAC filters
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list of filters
 */
क्रमागत ice_status
ice_fltr_हटाओ_mac_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list)
अणु
	वापस ice_हटाओ_mac(&vsi->back->hw, list);
पूर्ण

/**
 * ice_fltr_add_vlan_list - add list of VLAN filters
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list of filters
 */
अटल क्रमागत ice_status
ice_fltr_add_vlan_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list)
अणु
	वापस ice_add_vlan(&vsi->back->hw, list);
पूर्ण

/**
 * ice_fltr_हटाओ_vlan_list - हटाओ list of VLAN filters
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list of filters
 */
अटल क्रमागत ice_status
ice_fltr_हटाओ_vlan_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list)
अणु
	वापस ice_हटाओ_vlan(&vsi->back->hw, list);
पूर्ण

/**
 * ice_fltr_add_eth_list - add list of ethertype filters
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list of filters
 */
अटल क्रमागत ice_status
ice_fltr_add_eth_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list)
अणु
	वापस ice_add_eth_mac(&vsi->back->hw, list);
पूर्ण

/**
 * ice_fltr_हटाओ_eth_list - हटाओ list of ethertype filters
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list of filters
 */
अटल क्रमागत ice_status
ice_fltr_हटाओ_eth_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list)
अणु
	वापस ice_हटाओ_eth_mac(&vsi->back->hw, list);
पूर्ण

/**
 * ice_fltr_हटाओ_all - हटाओ all filters associated with VSI
 * @vsi: poपूर्णांकer to VSI काष्ठा
 */
व्योम ice_fltr_हटाओ_all(काष्ठा ice_vsi *vsi)
अणु
	ice_हटाओ_vsi_fltr(&vsi->back->hw, vsi->idx);
पूर्ण

/**
 * ice_fltr_add_mac_to_list - add MAC filter info to exsisting list
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list to add filter info to
 * @mac: MAC address to add
 * @action: filter action
 */
पूर्णांक
ice_fltr_add_mac_to_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list,
			 स्थिर u8 *mac, क्रमागत ice_sw_fwd_act_type action)
अणु
	काष्ठा ice_fltr_info info = अणु 0 पूर्ण;

	info.flag = ICE_FLTR_TX;
	info.src_id = ICE_SRC_ID_VSI;
	info.lkup_type = ICE_SW_LKUP_MAC;
	info.fltr_act = action;
	info.vsi_handle = vsi->idx;

	ether_addr_copy(info.l_data.mac.mac_addr, mac);

	वापस ice_fltr_add_entry_to_list(ice_pf_to_dev(vsi->back), &info,
					  list);
पूर्ण

/**
 * ice_fltr_add_vlan_to_list - add VLAN filter info to exsisting list
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list to add filter info to
 * @vlan_id: VLAN ID to add
 * @action: filter action
 */
अटल पूर्णांक
ice_fltr_add_vlan_to_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list,
			  u16 vlan_id, क्रमागत ice_sw_fwd_act_type action)
अणु
	काष्ठा ice_fltr_info info = अणु 0 पूर्ण;

	info.flag = ICE_FLTR_TX;
	info.src_id = ICE_SRC_ID_VSI;
	info.lkup_type = ICE_SW_LKUP_VLAN;
	info.fltr_act = action;
	info.vsi_handle = vsi->idx;
	info.l_data.vlan.vlan_id = vlan_id;

	वापस ice_fltr_add_entry_to_list(ice_pf_to_dev(vsi->back), &info,
					  list);
पूर्ण

/**
 * ice_fltr_add_eth_to_list - add ethertype filter info to exsisting list
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @list: list to add filter info to
 * @ethertype: ethertype of packet that matches filter
 * @flag: filter direction, Tx or Rx
 * @action: filter action
 */
अटल पूर्णांक
ice_fltr_add_eth_to_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list,
			 u16 ethertype, u16 flag,
			 क्रमागत ice_sw_fwd_act_type action)
अणु
	काष्ठा ice_fltr_info info = अणु 0 पूर्ण;

	info.flag = flag;
	info.lkup_type = ICE_SW_LKUP_ETHERTYPE;
	info.fltr_act = action;
	info.vsi_handle = vsi->idx;
	info.l_data.ethertype_mac.ethertype = ethertype;

	अगर (flag == ICE_FLTR_TX)
		info.src_id = ICE_SRC_ID_VSI;
	अन्यथा
		info.src_id = ICE_SRC_ID_LPORT;

	वापस ice_fltr_add_entry_to_list(ice_pf_to_dev(vsi->back), &info,
					  list);
पूर्ण

/**
 * ice_fltr_prepare_mac - add or हटाओ MAC rule
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @mac: MAC address to add
 * @action: action to be perक्रमmed on filter match
 * @mac_action: poपूर्णांकer to add or हटाओ MAC function
 */
अटल क्रमागत ice_status
ice_fltr_prepare_mac(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
		     क्रमागत ice_sw_fwd_act_type action,
		     क्रमागत ice_status (*mac_action)(काष्ठा ice_vsi *,
						   काष्ठा list_head *))
अणु
	क्रमागत ice_status result;
	LIST_HEAD(पंचांगp_list);

	अगर (ice_fltr_add_mac_to_list(vsi, &पंचांगp_list, mac, action)) अणु
		ice_fltr_मुक्त_list(ice_pf_to_dev(vsi->back), &पंचांगp_list);
		वापस ICE_ERR_NO_MEMORY;
	पूर्ण

	result = mac_action(vsi, &पंचांगp_list);
	ice_fltr_मुक्त_list(ice_pf_to_dev(vsi->back), &पंचांगp_list);
	वापस result;
पूर्ण

/**
 * ice_fltr_prepare_mac_and_broadcast - add or हटाओ MAC and broadcast filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @mac: MAC address to add
 * @action: action to be perक्रमmed on filter match
 * @mac_action: poपूर्णांकer to add or हटाओ MAC function
 */
अटल क्रमागत ice_status
ice_fltr_prepare_mac_and_broadcast(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
				   क्रमागत ice_sw_fwd_act_type action,
				   क्रमागत ice_status(*mac_action)
				   (काष्ठा ice_vsi *, काष्ठा list_head *))
अणु
	u8 broadcast[ETH_ALEN];
	क्रमागत ice_status result;
	LIST_HEAD(पंचांगp_list);

	eth_broadcast_addr(broadcast);
	अगर (ice_fltr_add_mac_to_list(vsi, &पंचांगp_list, mac, action) ||
	    ice_fltr_add_mac_to_list(vsi, &पंचांगp_list, broadcast, action)) अणु
		ice_fltr_मुक्त_list(ice_pf_to_dev(vsi->back), &पंचांगp_list);
		वापस ICE_ERR_NO_MEMORY;
	पूर्ण

	result = mac_action(vsi, &पंचांगp_list);
	ice_fltr_मुक्त_list(ice_pf_to_dev(vsi->back), &पंचांगp_list);
	वापस result;
पूर्ण

/**
 * ice_fltr_prepare_vlan - add or हटाओ VLAN filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @vlan_id: VLAN ID to add
 * @action: action to be perक्रमmed on filter match
 * @vlan_action: poपूर्णांकer to add or हटाओ VLAN function
 */
अटल क्रमागत ice_status
ice_fltr_prepare_vlan(काष्ठा ice_vsi *vsi, u16 vlan_id,
		      क्रमागत ice_sw_fwd_act_type action,
		      क्रमागत ice_status (*vlan_action)(काष्ठा ice_vsi *,
						     काष्ठा list_head *))
अणु
	क्रमागत ice_status result;
	LIST_HEAD(पंचांगp_list);

	अगर (ice_fltr_add_vlan_to_list(vsi, &पंचांगp_list, vlan_id, action))
		वापस ICE_ERR_NO_MEMORY;

	result = vlan_action(vsi, &पंचांगp_list);
	ice_fltr_मुक्त_list(ice_pf_to_dev(vsi->back), &पंचांगp_list);
	वापस result;
पूर्ण

/**
 * ice_fltr_prepare_eth - add or हटाओ ethertype filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @ethertype: ethertype of packet to be filtered
 * @flag: direction of packet, Tx or Rx
 * @action: action to be perक्रमmed on filter match
 * @eth_action: poपूर्णांकer to add or हटाओ ethertype function
 */
अटल क्रमागत ice_status
ice_fltr_prepare_eth(काष्ठा ice_vsi *vsi, u16 ethertype, u16 flag,
		     क्रमागत ice_sw_fwd_act_type action,
		     क्रमागत ice_status (*eth_action)(काष्ठा ice_vsi *,
						   काष्ठा list_head *))
अणु
	क्रमागत ice_status result;
	LIST_HEAD(पंचांगp_list);

	अगर (ice_fltr_add_eth_to_list(vsi, &पंचांगp_list, ethertype, flag, action))
		वापस ICE_ERR_NO_MEMORY;

	result = eth_action(vsi, &पंचांगp_list);
	ice_fltr_मुक्त_list(ice_pf_to_dev(vsi->back), &पंचांगp_list);
	वापस result;
पूर्ण

/**
 * ice_fltr_add_mac - add single MAC filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @mac: MAC to add
 * @action: action to be perक्रमmed on filter match
 */
क्रमागत ice_status ice_fltr_add_mac(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
				 क्रमागत ice_sw_fwd_act_type action)
अणु
	वापस ice_fltr_prepare_mac(vsi, mac, action, ice_fltr_add_mac_list);
पूर्ण

/**
 * ice_fltr_add_mac_and_broadcast - add single MAC and broadcast
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @mac: MAC to add
 * @action: action to be perक्रमmed on filter match
 */
क्रमागत ice_status
ice_fltr_add_mac_and_broadcast(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
			       क्रमागत ice_sw_fwd_act_type action)
अणु
	वापस ice_fltr_prepare_mac_and_broadcast(vsi, mac, action,
						  ice_fltr_add_mac_list);
पूर्ण

/**
 * ice_fltr_हटाओ_mac - हटाओ MAC filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @mac: filter MAC to हटाओ
 * @action: action to हटाओ
 */
क्रमागत ice_status ice_fltr_हटाओ_mac(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
				    क्रमागत ice_sw_fwd_act_type action)
अणु
	वापस ice_fltr_prepare_mac(vsi, mac, action, ice_fltr_हटाओ_mac_list);
पूर्ण

/**
 * ice_fltr_add_vlan - add single VLAN filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @vlan_id: VLAN ID to add
 * @action: action to be perक्रमmed on filter match
 */
क्रमागत ice_status ice_fltr_add_vlan(काष्ठा ice_vsi *vsi, u16 vlan_id,
				  क्रमागत ice_sw_fwd_act_type action)
अणु
	वापस ice_fltr_prepare_vlan(vsi, vlan_id, action,
				     ice_fltr_add_vlan_list);
पूर्ण

/**
 * ice_fltr_हटाओ_vlan - हटाओ VLAN filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @vlan_id: filter VLAN to हटाओ
 * @action: action to हटाओ
 */
क्रमागत ice_status ice_fltr_हटाओ_vlan(काष्ठा ice_vsi *vsi, u16 vlan_id,
				     क्रमागत ice_sw_fwd_act_type action)
अणु
	वापस ice_fltr_prepare_vlan(vsi, vlan_id, action,
				     ice_fltr_हटाओ_vlan_list);
पूर्ण

/**
 * ice_fltr_add_eth - add specyfic ethertype filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @ethertype: ethertype of filter
 * @flag: direction of packet to be filtered, Tx or Rx
 * @action: action to be perक्रमmed on filter match
 */
क्रमागत ice_status ice_fltr_add_eth(काष्ठा ice_vsi *vsi, u16 ethertype, u16 flag,
				 क्रमागत ice_sw_fwd_act_type action)
अणु
	वापस ice_fltr_prepare_eth(vsi, ethertype, flag, action,
				    ice_fltr_add_eth_list);
पूर्ण

/**
 * ice_fltr_हटाओ_eth - हटाओ ethertype filter
 * @vsi: poपूर्णांकer to VSI काष्ठा
 * @ethertype: ethertype of filter
 * @flag: direction of filter
 * @action: action to हटाओ
 */
क्रमागत ice_status ice_fltr_हटाओ_eth(काष्ठा ice_vsi *vsi, u16 ethertype,
				    u16 flag, क्रमागत ice_sw_fwd_act_type action)
अणु
	वापस ice_fltr_prepare_eth(vsi, ethertype, flag, action,
				    ice_fltr_हटाओ_eth_list);
पूर्ण
