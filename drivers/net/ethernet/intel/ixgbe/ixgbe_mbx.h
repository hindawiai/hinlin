<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_MBX_H_
#घोषणा _IXGBE_MBX_H_

#समावेश "ixgbe_type.h"

#घोषणा IXGBE_VFMAILBOX_SIZE        16 /* 16 32 bit words - 64 bytes */
#घोषणा IXGBE_ERR_MBX               -100

#घोषणा IXGBE_VFMAILBOX             0x002FC
#घोषणा IXGBE_VFMBMEM               0x00200

#घोषणा IXGBE_PFMAILBOX_STS   0x00000001 /* Initiate message send to VF */
#घोषणा IXGBE_PFMAILBOX_ACK   0x00000002 /* Ack message recv'd from VF */
#घोषणा IXGBE_PFMAILBOX_VFU   0x00000004 /* VF owns the mailbox buffer */
#घोषणा IXGBE_PFMAILBOX_PFU   0x00000008 /* PF owns the mailbox buffer */
#घोषणा IXGBE_PFMAILBOX_RVFU  0x00000010 /* Reset VFU - used when VF stuck */

#घोषणा IXGBE_MBVFICR_VFREQ_MASK 0x0000FFFF /* bits क्रम VF messages */
#घोषणा IXGBE_MBVFICR_VFREQ_VF1  0x00000001 /* bit क्रम VF 1 message */
#घोषणा IXGBE_MBVFICR_VFACK_MASK 0xFFFF0000 /* bits क्रम VF acks */
#घोषणा IXGBE_MBVFICR_VFACK_VF1  0x00010000 /* bit क्रम VF 1 ack */


/* If it's a IXGBE_VF_* msg then it originates in the VF and is sent to the
 * PF.  The reverse is true अगर it is IXGBE_PF_*.
 * Message ACK's are the value or'd with 0xF0000000
 */
#घोषणा IXGBE_VT_MSGTYPE_ACK      0x80000000  /* Messages below or'd with
					       * this are the ACK */
#घोषणा IXGBE_VT_MSGTYPE_NACK     0x40000000  /* Messages below or'd with
					       * this are the NACK */
#घोषणा IXGBE_VT_MSGTYPE_CTS      0x20000000  /* Indicates that VF is still
						 clear to send requests */
#घोषणा IXGBE_VT_MSGINFO_SHIFT    16
/* bits 23:16 are used क्रम exra info क्रम certain messages */
#घोषणा IXGBE_VT_MSGINFO_MASK     (0xFF << IXGBE_VT_MSGINFO_SHIFT)

/* definitions to support mailbox API version negotiation */

/*
 * Each element denotes a version of the API; existing numbers may not
 * change; any additions must go at the end
 */
क्रमागत ixgbe_pfvf_api_rev अणु
	ixgbe_mbox_api_10,	/* API version 1.0, linux/मुक्तbsd VF driver */
	ixgbe_mbox_api_20,	/* API version 2.0, solaris Phase1 VF driver */
	ixgbe_mbox_api_11,	/* API version 1.1, linux/मुक्तbsd VF driver */
	ixgbe_mbox_api_12,	/* API version 1.2, linux/मुक्तbsd VF driver */
	ixgbe_mbox_api_13,	/* API version 1.3, linux/मुक्तbsd VF driver */
	ixgbe_mbox_api_14,	/* API version 1.4, linux/मुक्तbsd VF driver */
	/* This value should always be last */
	ixgbe_mbox_api_unknown,	/* indicates that API version is not known */
पूर्ण;

/* mailbox API, legacy requests */
#घोषणा IXGBE_VF_RESET            0x01 /* VF requests reset */
#घोषणा IXGBE_VF_SET_MAC_ADDR     0x02 /* VF requests PF to set MAC addr */
#घोषणा IXGBE_VF_SET_MULTICAST    0x03 /* VF requests PF to set MC addr */
#घोषणा IXGBE_VF_SET_VLAN         0x04 /* VF requests PF to set VLAN */

/* mailbox API, version 1.0 VF requests */
#घोषणा IXGBE_VF_SET_LPE	0x05 /* VF requests PF to set VMOLR.LPE */
#घोषणा IXGBE_VF_SET_MACVLAN	0x06 /* VF requests PF क्रम unicast filter */
#घोषणा IXGBE_VF_API_NEGOTIATE	0x08 /* negotiate API version */

/* mailbox API, version 1.1 VF requests */
#घोषणा IXGBE_VF_GET_QUEUES	0x09 /* get queue configuration */

/* GET_QUEUES वापस data indices within the mailbox */
#घोषणा IXGBE_VF_TX_QUEUES	1	/* number of Tx queues supported */
#घोषणा IXGBE_VF_RX_QUEUES	2	/* number of Rx queues supported */
#घोषणा IXGBE_VF_TRANS_VLAN	3	/* Indication of port vlan */
#घोषणा IXGBE_VF_DEF_QUEUE	4	/* Default queue offset */

/* mailbox API, version 1.2 VF requests */
#घोषणा IXGBE_VF_GET_RETA	0x0a	/* VF request क्रम RETA */
#घोषणा IXGBE_VF_GET_RSS_KEY	0x0b	/* get RSS key */

#घोषणा IXGBE_VF_UPDATE_XCAST_MODE	0x0c

/* mailbox API, version 1.4 VF requests */
#घोषणा IXGBE_VF_IPSEC_ADD	0x0d
#घोषणा IXGBE_VF_IPSEC_DEL	0x0e

/* length of permanent address message वापसed from PF */
#घोषणा IXGBE_VF_PERMADDR_MSG_LEN 4
/* word in permanent address message with the current multicast type */
#घोषणा IXGBE_VF_MC_TYPE_WORD     3

#घोषणा IXGBE_PF_CONTROL_MSG      0x0100 /* PF control message */

#घोषणा IXGBE_VF_MBX_INIT_TIMEOUT 2000 /* number of retries on mailbox */
#घोषणा IXGBE_VF_MBX_INIT_DELAY   500  /* microseconds between retries */

s32 ixgbe_पढ़ो_mbx(काष्ठा ixgbe_hw *, u32 *, u16, u16);
s32 ixgbe_ग_लिखो_mbx(काष्ठा ixgbe_hw *, u32 *, u16, u16);
s32 ixgbe_check_क्रम_msg(काष्ठा ixgbe_hw *, u16);
s32 ixgbe_check_क्रम_ack(काष्ठा ixgbe_hw *, u16);
s32 ixgbe_check_क्रम_rst(काष्ठा ixgbe_hw *, u16);
#अगर_घोषित CONFIG_PCI_IOV
व्योम ixgbe_init_mbx_params_pf(काष्ठा ixgbe_hw *);
#पूर्ण_अगर /* CONFIG_PCI_IOV */

बाह्य स्थिर काष्ठा ixgbe_mbx_operations mbx_ops_generic;

#पूर्ण_अगर /* _IXGBE_MBX_H_ */
