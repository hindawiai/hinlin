<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_BASE_H_
#घोषणा _ICE_BASE_H_

#समावेश "ice.h"

पूर्णांक ice_setup_rx_ctx(काष्ठा ice_ring *ring);
पूर्णांक __ice_vsi_get_qs(काष्ठा ice_qs_cfg *qs_cfg);
पूर्णांक
ice_vsi_ctrl_one_rx_ring(काष्ठा ice_vsi *vsi, bool ena, u16 rxq_idx, bool रुको);
पूर्णांक ice_vsi_रुको_one_rx_ring(काष्ठा ice_vsi *vsi, bool ena, u16 rxq_idx);
पूर्णांक ice_vsi_alloc_q_vectors(काष्ठा ice_vsi *vsi);
व्योम ice_vsi_map_rings_to_vectors(काष्ठा ice_vsi *vsi);
व्योम ice_vsi_मुक्त_q_vectors(काष्ठा ice_vsi *vsi);
पूर्णांक
ice_vsi_cfg_txq(काष्ठा ice_vsi *vsi, काष्ठा ice_ring *ring,
		काष्ठा ice_aqc_add_tx_qgrp *qg_buf);
व्योम ice_cfg_itr(काष्ठा ice_hw *hw, काष्ठा ice_q_vector *q_vector);
व्योम
ice_cfg_txq_पूर्णांकerrupt(काष्ठा ice_vsi *vsi, u16 txq, u16 msix_idx, u16 itr_idx);
व्योम
ice_cfg_rxq_पूर्णांकerrupt(काष्ठा ice_vsi *vsi, u16 rxq, u16 msix_idx, u16 itr_idx);
व्योम ice_trigger_sw_पूर्णांकr(काष्ठा ice_hw *hw, काष्ठा ice_q_vector *q_vector);
पूर्णांक
ice_vsi_stop_tx_ring(काष्ठा ice_vsi *vsi, क्रमागत ice_disq_rst_src rst_src,
		     u16 rel_vmvf_num, काष्ठा ice_ring *ring,
		     काष्ठा ice_txq_meta *txq_meta);
व्योम
ice_fill_txq_meta(काष्ठा ice_vsi *vsi, काष्ठा ice_ring *ring,
		  काष्ठा ice_txq_meta *txq_meta);
#पूर्ण_अगर /* _ICE_BASE_H_ */
