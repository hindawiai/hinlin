<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_MBX_H_
#घोषणा _E1000_MBX_H_

#समावेश "vf.h"

#घोषणा E1000_V2PMAILBOX_REQ	0x00000001 /* Request क्रम PF Ready bit */
#घोषणा E1000_V2PMAILBOX_ACK	0x00000002 /* Ack PF message received */
#घोषणा E1000_V2PMAILBOX_VFU	0x00000004 /* VF owns the mailbox buffer */
#घोषणा E1000_V2PMAILBOX_PFU	0x00000008 /* PF owns the mailbox buffer */
#घोषणा E1000_V2PMAILBOX_PFSTS	0x00000010 /* PF wrote a message in the MB */
#घोषणा E1000_V2PMAILBOX_PFACK	0x00000020 /* PF ack the previous VF msg */
#घोषणा E1000_V2PMAILBOX_RSTI	0x00000040 /* PF has reset indication */
#घोषणा E1000_V2PMAILBOX_RSTD	0x00000080 /* PF has indicated reset करोne */
#घोषणा E1000_V2PMAILBOX_R2C_BITS 0x000000B0 /* All पढ़ो to clear bits */

#घोषणा E1000_VFMAILBOX_SIZE	16 /* 16 32 bit words - 64 bytes */

/* If it's a E1000_VF_* msg then it originates in the VF and is sent to the
 * PF.  The reverse is true अगर it is E1000_PF_*.
 * Message ACK's are the value or'd with 0xF0000000
 */
/* Messages below or'd with this are the ACK */
#घोषणा E1000_VT_MSGTYPE_ACK	0x80000000
/* Messages below or'd with this are the NACK */
#घोषणा E1000_VT_MSGTYPE_NACK	0x40000000
/* Indicates that VF is still clear to send requests */
#घोषणा E1000_VT_MSGTYPE_CTS	0x20000000

/* We have a total रुको समय of 1s क्रम vf mailbox posted messages */
#घोषणा E1000_VF_MBX_INIT_TIMEOUT	2000 /* retry count क्रम mbx समयout */
#घोषणा E1000_VF_MBX_INIT_DELAY		500  /* usec delay between retries */

#घोषणा E1000_VT_MSGINFO_SHIFT	16
/* bits 23:16 are used क्रम exra info क्रम certain messages */
#घोषणा E1000_VT_MSGINFO_MASK	(0xFF << E1000_VT_MSGINFO_SHIFT)

#घोषणा E1000_VF_RESET		0x01 /* VF requests reset */
#घोषणा E1000_VF_SET_MAC_ADDR	0x02 /* VF requests PF to set MAC addr */
/* VF requests PF to clear all unicast MAC filters */
#घोषणा E1000_VF_MAC_FILTER_CLR (0x01 << E1000_VT_MSGINFO_SHIFT)
/* VF requests PF to add unicast MAC filter */
#घोषणा E1000_VF_MAC_FILTER_ADD (0x02 << E1000_VT_MSGINFO_SHIFT)
#घोषणा E1000_VF_SET_MULTICAST	0x03 /* VF requests PF to set MC addr */
#घोषणा E1000_VF_SET_VLAN	0x04 /* VF requests PF to set VLAN */
#घोषणा E1000_VF_SET_LPE	0x05 /* VF requests PF to set VMOLR.LPE */

#घोषणा E1000_PF_CONTROL_MSG	0x0100 /* PF control message */

व्योम e1000_init_mbx_ops_generic(काष्ठा e1000_hw *hw);
s32 e1000_init_mbx_params_vf(काष्ठा e1000_hw *);

#पूर्ण_अगर /* _E1000_MBX_H_ */
