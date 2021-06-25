<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _FM10K_VF_H_
#घोषणा _FM10K_VF_H_

#समावेश "fm10k_type.h"
#समावेश "fm10k_common.h"

क्रमागत fm10k_vf_tlv_msg_id अणु
	FM10K_VF_MSG_ID_TEST = 0,	/* msg ID reserved क्रम testing */
	FM10K_VF_MSG_ID_MSIX,
	FM10K_VF_MSG_ID_MAC_VLAN,
	FM10K_VF_MSG_ID_LPORT_STATE,
	FM10K_VF_MSG_ID_MAX,
पूर्ण;

क्रमागत fm10k_tlv_mac_vlan_attr_id अणु
	FM10K_MAC_VLAN_MSG_VLAN,
	FM10K_MAC_VLAN_MSG_SET,
	FM10K_MAC_VLAN_MSG_MAC,
	FM10K_MAC_VLAN_MSG_DEFAULT_MAC,
	FM10K_MAC_VLAN_MSG_MULTICAST,
	FM10K_MAC_VLAN_MSG_ID_MAX
पूर्ण;

क्रमागत fm10k_tlv_lport_state_attr_id अणु
	FM10K_LPORT_STATE_MSG_DISABLE,
	FM10K_LPORT_STATE_MSG_XCAST_MODE,
	FM10K_LPORT_STATE_MSG_READY,
	FM10K_LPORT_STATE_MSG_MAX
पूर्ण;

#घोषणा FM10K_VF_MSG_MSIX_HANDLER(func) \
	 FM10K_MSG_HANDLER(FM10K_VF_MSG_ID_MSIX, शून्य, func)

s32 fm10k_msg_mac_vlan_vf(काष्ठा fm10k_hw *, u32 **, काष्ठा fm10k_mbx_info *);
बाह्य स्थिर काष्ठा fm10k_tlv_attr fm10k_mac_vlan_msg_attr[];
#घोषणा FM10K_VF_MSG_MAC_VLAN_HANDLER(func) \
	FM10K_MSG_HANDLER(FM10K_VF_MSG_ID_MAC_VLAN, \
			  fm10k_mac_vlan_msg_attr, func)

s32 fm10k_msg_lport_state_vf(काष्ठा fm10k_hw *, u32 **,
			     काष्ठा fm10k_mbx_info *);
बाह्य स्थिर काष्ठा fm10k_tlv_attr fm10k_lport_state_msg_attr[];
#घोषणा FM10K_VF_MSG_LPORT_STATE_HANDLER(func) \
	FM10K_MSG_HANDLER(FM10K_VF_MSG_ID_LPORT_STATE, \
			  fm10k_lport_state_msg_attr, func)

बाह्य स्थिर काष्ठा fm10k_info fm10k_vf_info;
#पूर्ण_अगर /* _FM10K_VF_H */
