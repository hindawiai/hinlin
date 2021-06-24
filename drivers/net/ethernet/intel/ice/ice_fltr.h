<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018-2020, Intel Corporation. */

#अगर_अघोषित _ICE_FLTR_H_
#घोषणा _ICE_FLTR_H_

व्योम ice_fltr_मुक्त_list(काष्ठा device *dev, काष्ठा list_head *h);
क्रमागत ice_status
ice_fltr_add_mac_to_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list,
			 स्थिर u8 *mac, क्रमागत ice_sw_fwd_act_type action);
क्रमागत ice_status
ice_fltr_add_mac(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
		 क्रमागत ice_sw_fwd_act_type action);
क्रमागत ice_status
ice_fltr_add_mac_and_broadcast(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
			       क्रमागत ice_sw_fwd_act_type action);
क्रमागत ice_status
ice_fltr_add_mac_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list);
क्रमागत ice_status
ice_fltr_हटाओ_mac(काष्ठा ice_vsi *vsi, स्थिर u8 *mac,
		    क्रमागत ice_sw_fwd_act_type action);
क्रमागत ice_status
ice_fltr_हटाओ_mac_list(काष्ठा ice_vsi *vsi, काष्ठा list_head *list);

क्रमागत ice_status
ice_fltr_add_vlan(काष्ठा ice_vsi *vsi, u16 vid,
		  क्रमागत ice_sw_fwd_act_type action);
क्रमागत ice_status
ice_fltr_हटाओ_vlan(काष्ठा ice_vsi *vsi, u16 vid,
		     क्रमागत ice_sw_fwd_act_type action);

क्रमागत ice_status
ice_fltr_add_eth(काष्ठा ice_vsi *vsi, u16 ethertype, u16 flag,
		 क्रमागत ice_sw_fwd_act_type action);
क्रमागत ice_status
ice_fltr_हटाओ_eth(काष्ठा ice_vsi *vsi, u16 ethertype, u16 flag,
		    क्रमागत ice_sw_fwd_act_type action);
व्योम ice_fltr_हटाओ_all(काष्ठा ice_vsi *vsi);
#पूर्ण_अगर
