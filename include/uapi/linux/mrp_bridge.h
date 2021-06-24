<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */

#अगर_अघोषित _UAPI_LINUX_MRP_BRIDGE_H_
#घोषणा _UAPI_LINUX_MRP_BRIDGE_H_

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#घोषणा MRP_MAX_FRAME_LENGTH		200
#घोषणा MRP_DEFAULT_PRIO		0x8000
#घोषणा MRP_DOMAIN_UUID_LENGTH		16
#घोषणा MRP_VERSION			1
#घोषणा MRP_FRAME_PRIO			7
#घोषणा MRP_OUI_LENGTH			3
#घोषणा MRP_MANUFACTURE_DATA_LENGTH	2

क्रमागत br_mrp_ring_role_type अणु
	BR_MRP_RING_ROLE_DISABLED,
	BR_MRP_RING_ROLE_MRC,
	BR_MRP_RING_ROLE_MRM,
	BR_MRP_RING_ROLE_MRA,
पूर्ण;

क्रमागत br_mrp_in_role_type अणु
	BR_MRP_IN_ROLE_DISABLED,
	BR_MRP_IN_ROLE_MIC,
	BR_MRP_IN_ROLE_MIM,
पूर्ण;

क्रमागत br_mrp_ring_state_type अणु
	BR_MRP_RING_STATE_OPEN,
	BR_MRP_RING_STATE_CLOSED,
पूर्ण;

क्रमागत br_mrp_in_state_type अणु
	BR_MRP_IN_STATE_OPEN,
	BR_MRP_IN_STATE_CLOSED,
पूर्ण;

क्रमागत br_mrp_port_state_type अणु
	BR_MRP_PORT_STATE_DISABLED,
	BR_MRP_PORT_STATE_BLOCKED,
	BR_MRP_PORT_STATE_FORWARDING,
	BR_MRP_PORT_STATE_NOT_CONNECTED,
पूर्ण;

क्रमागत br_mrp_port_role_type अणु
	BR_MRP_PORT_ROLE_PRIMARY,
	BR_MRP_PORT_ROLE_SECONDARY,
	BR_MRP_PORT_ROLE_INTER,
पूर्ण;

क्रमागत br_mrp_tlv_header_type अणु
	BR_MRP_TLV_HEADER_END = 0x0,
	BR_MRP_TLV_HEADER_COMMON = 0x1,
	BR_MRP_TLV_HEADER_RING_TEST = 0x2,
	BR_MRP_TLV_HEADER_RING_TOPO = 0x3,
	BR_MRP_TLV_HEADER_RING_LINK_DOWN = 0x4,
	BR_MRP_TLV_HEADER_RING_LINK_UP = 0x5,
	BR_MRP_TLV_HEADER_IN_TEST = 0x6,
	BR_MRP_TLV_HEADER_IN_TOPO = 0x7,
	BR_MRP_TLV_HEADER_IN_LINK_DOWN = 0x8,
	BR_MRP_TLV_HEADER_IN_LINK_UP = 0x9,
	BR_MRP_TLV_HEADER_IN_LINK_STATUS = 0xa,
	BR_MRP_TLV_HEADER_OPTION = 0x7f,
पूर्ण;

क्रमागत br_mrp_sub_tlv_header_type अणु
	BR_MRP_SUB_TLV_HEADER_TEST_MGR_NACK = 0x1,
	BR_MRP_SUB_TLV_HEADER_TEST_PROPAGATE = 0x2,
	BR_MRP_SUB_TLV_HEADER_TEST_AUTO_MGR = 0x3,
पूर्ण;

#पूर्ण_अगर
