<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_LIB_H_
#घोषणा _ICE_LIB_H_

#समावेश "ice.h"

स्थिर अक्षर *ice_vsi_type_str(क्रमागत ice_vsi_type vsi_type);

bool ice_pf_state_is_nominal(काष्ठा ice_pf *pf);

व्योम ice_update_eth_stats(काष्ठा ice_vsi *vsi);

पूर्णांक ice_vsi_cfg_rxqs(काष्ठा ice_vsi *vsi);

पूर्णांक ice_vsi_cfg_lan_txqs(काष्ठा ice_vsi *vsi);

व्योम ice_vsi_cfg_msix(काष्ठा ice_vsi *vsi);

पूर्णांक
ice_vsi_add_vlan(काष्ठा ice_vsi *vsi, u16 vid, क्रमागत ice_sw_fwd_act_type action);

पूर्णांक ice_vsi_समाप्त_vlan(काष्ठा ice_vsi *vsi, u16 vid);

पूर्णांक ice_vsi_manage_vlan_insertion(काष्ठा ice_vsi *vsi);

पूर्णांक ice_vsi_manage_vlan_stripping(काष्ठा ice_vsi *vsi, bool ena);

पूर्णांक ice_vsi_start_all_rx_rings(काष्ठा ice_vsi *vsi);

पूर्णांक ice_vsi_stop_all_rx_rings(काष्ठा ice_vsi *vsi);

पूर्णांक
ice_vsi_stop_lan_tx_rings(काष्ठा ice_vsi *vsi, क्रमागत ice_disq_rst_src rst_src,
			  u16 rel_vmvf_num);

पूर्णांक ice_vsi_cfg_xdp_txqs(काष्ठा ice_vsi *vsi);

पूर्णांक ice_vsi_stop_xdp_tx_rings(काष्ठा ice_vsi *vsi);

bool ice_vsi_is_vlan_pruning_ena(काष्ठा ice_vsi *vsi);

पूर्णांक ice_cfg_vlan_pruning(काष्ठा ice_vsi *vsi, bool ena, bool vlan_promisc);

व्योम ice_cfg_sw_lldp(काष्ठा ice_vsi *vsi, bool tx, bool create);

पूर्णांक ice_set_link(काष्ठा ice_vsi *vsi, bool ena);

#अगर_घोषित CONFIG_DCB
पूर्णांक ice_vsi_cfg_tc(काष्ठा ice_vsi *vsi, u8 ena_tc);
#पूर्ण_अगर /* CONFIG_DCB */

काष्ठा ice_vsi *
ice_vsi_setup(काष्ठा ice_pf *pf, काष्ठा ice_port_info *pi,
	      क्रमागत ice_vsi_type vsi_type, u16 vf_id);

व्योम ice_napi_del(काष्ठा ice_vsi *vsi);

पूर्णांक ice_vsi_release(काष्ठा ice_vsi *vsi);

व्योम ice_vsi_बंद(काष्ठा ice_vsi *vsi);

पूर्णांक ice_ena_vsi(काष्ठा ice_vsi *vsi, bool locked);

व्योम ice_dis_vsi(काष्ठा ice_vsi *vsi, bool locked);

पूर्णांक ice_मुक्त_res(काष्ठा ice_res_tracker *res, u16 index, u16 id);

पूर्णांक
ice_get_res(काष्ठा ice_pf *pf, काष्ठा ice_res_tracker *res, u16 needed, u16 id);

पूर्णांक ice_vsi_rebuild(काष्ठा ice_vsi *vsi, bool init_vsi);

bool ice_is_reset_in_progress(अचिन्हित दीर्घ *state);

व्योम
ice_ग_लिखो_qrxflxp_cntxt(काष्ठा ice_hw *hw, u16 pf_q, u32 rxdid, u32 prio);

व्योम ice_vsi_dis_irq(काष्ठा ice_vsi *vsi);

व्योम ice_vsi_मुक्त_irq(काष्ठा ice_vsi *vsi);

व्योम ice_vsi_मुक्त_rx_rings(काष्ठा ice_vsi *vsi);

व्योम ice_vsi_मुक्त_tx_rings(काष्ठा ice_vsi *vsi);

व्योम ice_vsi_manage_rss_lut(काष्ठा ice_vsi *vsi, bool ena);

व्योम ice_update_tx_ring_stats(काष्ठा ice_ring *ring, u64 pkts, u64 bytes);

व्योम ice_update_rx_ring_stats(काष्ठा ice_ring *ring, u64 pkts, u64 bytes);

व्योम ice_vsi_cfg_frame_size(काष्ठा ice_vsi *vsi);

पूर्णांक ice_status_to_त्रुटि_सं(क्रमागत ice_status err);

व्योम ice_ग_लिखो_पूर्णांकrl(काष्ठा ice_q_vector *q_vector, u8 पूर्णांकrl);
व्योम ice_ग_लिखो_itr(काष्ठा ice_ring_container *rc, u16 itr);

क्रमागत ice_status
ice_vsi_cfg_mac_fltr(काष्ठा ice_vsi *vsi, स्थिर u8 *macaddr, bool set);

bool ice_is_safe_mode(काष्ठा ice_pf *pf);

bool ice_is_dflt_vsi_in_use(काष्ठा ice_sw *sw);

bool ice_is_vsi_dflt_vsi(काष्ठा ice_sw *sw, काष्ठा ice_vsi *vsi);

पूर्णांक ice_set_dflt_vsi(काष्ठा ice_sw *sw, काष्ठा ice_vsi *vsi);

पूर्णांक ice_clear_dflt_vsi(काष्ठा ice_sw *sw);
#पूर्ण_अगर /* !_ICE_LIB_H_ */
