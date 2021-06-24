<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#अगर_अघोषित _FM10K_PF_H_
#घोषणा _FM10K_PF_H_

#समावेश "fm10k_type.h"
#समावेश "fm10k_common.h"

bool fm10k_glort_valid_pf(काष्ठा fm10k_hw *hw, u16 glort);
u16 fm10k_queues_per_pool(काष्ठा fm10k_hw *hw);
u16 fm10k_vf_queue_index(काष्ठा fm10k_hw *hw, u16 vf_idx);

क्रमागत fm10k_pf_tlv_msg_id_v1 अणु
	FM10K_PF_MSG_ID_TEST			= 0x000, /* msg ID reserved */
	FM10K_PF_MSG_ID_XCAST_MODES		= 0x001,
	FM10K_PF_MSG_ID_UPDATE_MAC_FWD_RULE	= 0x002,
	FM10K_PF_MSG_ID_LPORT_MAP		= 0x100,
	FM10K_PF_MSG_ID_LPORT_CREATE		= 0x200,
	FM10K_PF_MSG_ID_LPORT_DELETE		= 0x201,
	FM10K_PF_MSG_ID_CONFIG			= 0x300,
	FM10K_PF_MSG_ID_UPDATE_PVID		= 0x400,
	FM10K_PF_MSG_ID_CREATE_FLOW_TABLE	= 0x501,
	FM10K_PF_MSG_ID_DELETE_FLOW_TABLE	= 0x502,
	FM10K_PF_MSG_ID_UPDATE_FLOW		= 0x503,
	FM10K_PF_MSG_ID_DELETE_FLOW		= 0x504,
	FM10K_PF_MSG_ID_SET_FLOW_STATE		= 0x505,
पूर्ण;

क्रमागत fm10k_pf_tlv_attr_id_v1 अणु
	FM10K_PF_ATTR_ID_ERR			= 0x00,
	FM10K_PF_ATTR_ID_LPORT_MAP		= 0x01,
	FM10K_PF_ATTR_ID_XCAST_MODE		= 0x02,
	FM10K_PF_ATTR_ID_MAC_UPDATE		= 0x03,
	FM10K_PF_ATTR_ID_VLAN_UPDATE		= 0x04,
	FM10K_PF_ATTR_ID_CONFIG			= 0x05,
	FM10K_PF_ATTR_ID_CREATE_FLOW_TABLE	= 0x06,
	FM10K_PF_ATTR_ID_DELETE_FLOW_TABLE	= 0x07,
	FM10K_PF_ATTR_ID_UPDATE_FLOW		= 0x08,
	FM10K_PF_ATTR_ID_FLOW_STATE		= 0x09,
	FM10K_PF_ATTR_ID_FLOW_HANDLE		= 0x0A,
	FM10K_PF_ATTR_ID_DELETE_FLOW		= 0x0B,
	FM10K_PF_ATTR_ID_PORT			= 0x0C,
	FM10K_PF_ATTR_ID_UPDATE_PVID		= 0x0D,
पूर्ण;

#घोषणा FM10K_MSG_LPORT_MAP_GLORT_SHIFT	0
#घोषणा FM10K_MSG_LPORT_MAP_GLORT_SIZE	16
#घोषणा FM10K_MSG_LPORT_MAP_MASK_SHIFT	16
#घोषणा FM10K_MSG_LPORT_MAP_MASK_SIZE	16

#घोषणा FM10K_MSG_UPDATE_PVID_GLORT_SHIFT	0
#घोषणा FM10K_MSG_UPDATE_PVID_GLORT_SIZE	16
#घोषणा FM10K_MSG_UPDATE_PVID_PVID_SHIFT	16
#घोषणा FM10K_MSG_UPDATE_PVID_PVID_SIZE		16

#घोषणा FM10K_MSG_ERR_PEP_NOT_SCHEDULED	280

/* The following data काष्ठाures are overlayed directly onto TLV mailbox
 * messages, and must not अवरोध 4 byte alignment. Ensure the काष्ठाures line
 * up correctly as per their TLV definition.
 */

काष्ठा fm10k_mac_update अणु
	__le32	mac_lower;
	__le16	mac_upper;
	__le16	vlan;
	__le16	glort;
	u8	flags;
	u8	action;
पूर्ण __aligned(4) __packed;

काष्ठा fm10k_global_table_data अणु
	__le32	used;
	__le32	avail;
पूर्ण __aligned(4) __packed;

काष्ठा fm10k_swapi_error अणु
	__le32				status;
	काष्ठा fm10k_global_table_data	mac;
	काष्ठा fm10k_global_table_data	nexthop;
	काष्ठा fm10k_global_table_data	ffu;
पूर्ण __aligned(4) __packed;

s32 fm10k_msg_lport_map_pf(काष्ठा fm10k_hw *, u32 **, काष्ठा fm10k_mbx_info *);
बाह्य स्थिर काष्ठा fm10k_tlv_attr fm10k_lport_map_msg_attr[];
#घोषणा FM10K_PF_MSG_LPORT_MAP_HANDLER(func) \
	FM10K_MSG_HANDLER(FM10K_PF_MSG_ID_LPORT_MAP, \
			  fm10k_lport_map_msg_attr, func)
बाह्य स्थिर काष्ठा fm10k_tlv_attr fm10k_update_pvid_msg_attr[];
#घोषणा FM10K_PF_MSG_UPDATE_PVID_HANDLER(func) \
	FM10K_MSG_HANDLER(FM10K_PF_MSG_ID_UPDATE_PVID, \
			  fm10k_update_pvid_msg_attr, func)

s32 fm10k_msg_err_pf(काष्ठा fm10k_hw *, u32 **, काष्ठा fm10k_mbx_info *);
बाह्य स्थिर काष्ठा fm10k_tlv_attr fm10k_err_msg_attr[];
#घोषणा FM10K_PF_MSG_ERR_HANDLER(msg, func) \
	FM10K_MSG_HANDLER(FM10K_PF_MSG_ID_##msg, fm10k_err_msg_attr, func)

s32 fm10k_iov_select_vid(काष्ठा fm10k_vf_info *vf_info, u16 vid);
s32 fm10k_iov_msg_msix_pf(काष्ठा fm10k_hw *, u32 **, काष्ठा fm10k_mbx_info *);
s32 fm10k_iov_msg_mac_vlan_pf(काष्ठा fm10k_hw *, u32 **,
			      काष्ठा fm10k_mbx_info *);
s32 fm10k_iov_msg_lport_state_pf(काष्ठा fm10k_hw *, u32 **,
				 काष्ठा fm10k_mbx_info *);

बाह्य स्थिर काष्ठा fm10k_info fm10k_pf_info;
#पूर्ण_अगर /* _FM10K_PF_H */
