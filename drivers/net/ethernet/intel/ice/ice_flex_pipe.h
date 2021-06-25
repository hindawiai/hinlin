<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_FLEX_PIPE_H_
#घोषणा _ICE_FLEX_PIPE_H_

#समावेश "ice_type.h"

/* Package minimal version supported */
#घोषणा ICE_PKG_SUPP_VER_MAJ	1
#घोषणा ICE_PKG_SUPP_VER_MNR	3

/* Package क्रमmat version */
#घोषणा ICE_PKG_FMT_VER_MAJ	1
#घोषणा ICE_PKG_FMT_VER_MNR	0
#घोषणा ICE_PKG_FMT_VER_UPD	0
#घोषणा ICE_PKG_FMT_VER_DFT	0

#घोषणा ICE_PKG_CNT 4

bool
ice_get_खोलो_tunnel_port(काष्ठा ice_hw *hw, u16 *port);
पूर्णांक ice_udp_tunnel_set_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
			    अचिन्हित पूर्णांक idx, काष्ठा udp_tunnel_info *ti);
पूर्णांक ice_udp_tunnel_unset_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
			      अचिन्हित पूर्णांक idx, काष्ठा udp_tunnel_info *ti);

क्रमागत ice_status
ice_add_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 id, u8 ptypes[],
	     स्थिर काष्ठा ice_ptype_attributes *attr, u16 attr_cnt,
	     काष्ठा ice_fv_word *es, u16 *masks);
क्रमागत ice_status
ice_add_prof_id_flow(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u64 hdl);
क्रमागत ice_status
ice_rem_prof_id_flow(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u64 hdl);
क्रमागत ice_status ice_init_pkg(काष्ठा ice_hw *hw, u8 *buff, u32 len);
क्रमागत ice_status
ice_copy_and_init_pkg(काष्ठा ice_hw *hw, स्थिर u8 *buf, u32 len);
क्रमागत ice_status ice_init_hw_tbls(काष्ठा ice_hw *hw);
व्योम ice_मुक्त_seg(काष्ठा ice_hw *hw);
व्योम ice_fill_blk_tbls(काष्ठा ice_hw *hw);
व्योम ice_clear_hw_tbls(काष्ठा ice_hw *hw);
व्योम ice_मुक्त_hw_tbls(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_rem_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 id);
#पूर्ण_अगर /* _ICE_FLEX_PIPE_H_ */
