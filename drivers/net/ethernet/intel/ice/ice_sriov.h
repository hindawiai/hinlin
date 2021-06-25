<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2018, Intel Corporation. */

#अगर_अघोषित _ICE_SRIOV_H_
#घोषणा _ICE_SRIOV_H_

#समावेश "ice_type.h"
#समावेश "ice_controlq.h"

/* Defining the mailbox message threshold as 63 asynchronous
 * pending messages. Normal VF functionality करोes not require
 * sending more than 63 asynchronous pending message.
 */
#घोषणा ICE_ASYNC_VF_MSG_THRESHOLD	63

#अगर_घोषित CONFIG_PCI_IOV
क्रमागत ice_status
ice_aq_send_msg_to_vf(काष्ठा ice_hw *hw, u16 vfid, u32 v_opcode, u32 v_retval,
		      u8 *msg, u16 msglen, काष्ठा ice_sq_cd *cd);

u32 ice_conv_link_speed_to_virtchnl(bool adv_link_support, u16 link_speed);
क्रमागत ice_status
ice_mbx_vf_state_handler(काष्ठा ice_hw *hw, काष्ठा ice_mbx_data *mbx_data,
			 u16 vf_id, bool *is_mal_vf);
क्रमागत ice_status
ice_mbx_clear_malvf(काष्ठा ice_mbx_snapshot *snap, अचिन्हित दीर्घ *all_malvfs,
		    u16 biपंचांगap_len, u16 vf_id);
क्रमागत ice_status ice_mbx_init_snapshot(काष्ठा ice_hw *hw, u16 vf_count);
व्योम ice_mbx_deinit_snapshot(काष्ठा ice_hw *hw);
क्रमागत ice_status
ice_mbx_report_malvf(काष्ठा ice_hw *hw, अचिन्हित दीर्घ *all_malvfs,
		     u16 biपंचांगap_len, u16 vf_id, bool *report_malvf);
#अन्यथा /* CONFIG_PCI_IOV */
अटल अंतरभूत क्रमागत ice_status
ice_aq_send_msg_to_vf(काष्ठा ice_hw __always_unused *hw,
		      u16 __always_unused vfid, u32 __always_unused v_opcode,
		      u32 __always_unused v_retval, u8 __always_unused *msg,
		      u16 __always_unused msglen,
		      काष्ठा ice_sq_cd __always_unused *cd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32
ice_conv_link_speed_to_virtchnl(bool __always_unused adv_link_support,
				u16 __always_unused link_speed)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI_IOV */
#पूर्ण_अगर /* _ICE_SRIOV_H_ */
