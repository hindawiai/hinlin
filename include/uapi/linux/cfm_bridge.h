<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */

#अगर_अघोषित _UAPI_LINUX_CFM_BRIDGE_H_
#घोषणा _UAPI_LINUX_CFM_BRIDGE_H_

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#घोषणा ETHER_HEADER_LENGTH		(6+6+4+2)
#घोषणा CFM_MAID_LENGTH			48
#घोषणा CFM_CCM_PDU_LENGTH		75
#घोषणा CFM_PORT_STATUS_TLV_LENGTH	4
#घोषणा CFM_IF_STATUS_TLV_LENGTH	4
#घोषणा CFM_IF_STATUS_TLV_TYPE		4
#घोषणा CFM_PORT_STATUS_TLV_TYPE	2
#घोषणा CFM_ENDE_TLV_TYPE		0
#घोषणा CFM_CCM_MAX_FRAME_LENGTH	(ETHER_HEADER_LENGTH+\
					 CFM_CCM_PDU_LENGTH+\
					 CFM_PORT_STATUS_TLV_LENGTH+\
					 CFM_IF_STATUS_TLV_LENGTH)
#घोषणा CFM_FRAME_PRIO			7
#घोषणा CFM_CCM_TLV_OFFSET		70
#घोषणा CFM_CCM_PDU_MAID_OFFSET		10
#घोषणा CFM_CCM_PDU_MEPID_OFFSET	8
#घोषणा CFM_CCM_PDU_SEQNR_OFFSET	4
#घोषणा CFM_CCM_PDU_TLV_OFFSET		74
#घोषणा CFM_CCM_ITU_RESERVED_SIZE	16

काष्ठा br_cfm_common_hdr अणु
	__u8 mdlevel_version;
	__u8 opcode;
	__u8 flags;
	__u8 tlv_offset;
पूर्ण;

क्रमागत br_cfm_opcodes अणु
	BR_CFM_OPCODE_CCM = 0x1,
पूर्ण;

/* MEP करोमुख्य */
क्रमागत br_cfm_करोमुख्य अणु
	BR_CFM_PORT,
	BR_CFM_VLAN,
पूर्ण;

/* MEP direction */
क्रमागत br_cfm_mep_direction अणु
	BR_CFM_MEP_सूचीECTION_DOWN,
	BR_CFM_MEP_सूचीECTION_UP,
पूर्ण;

/* CCM पूर्णांकerval supported. */
क्रमागत br_cfm_ccm_पूर्णांकerval अणु
	BR_CFM_CCM_INTERVAL_NONE,
	BR_CFM_CCM_INTERVAL_3_3_MS,
	BR_CFM_CCM_INTERVAL_10_MS,
	BR_CFM_CCM_INTERVAL_100_MS,
	BR_CFM_CCM_INTERVAL_1_SEC,
	BR_CFM_CCM_INTERVAL_10_SEC,
	BR_CFM_CCM_INTERVAL_1_MIN,
	BR_CFM_CCM_INTERVAL_10_MIN,
पूर्ण;

#पूर्ण_अगर
