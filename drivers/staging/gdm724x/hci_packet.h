<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2012 GCT Semiconductor, Inc. All rights reserved. */

#अगर_अघोषित _HCI_PACKET_H_
#घोषणा _HCI_PACKET_H_

#घोषणा HCI_HEADER_SIZE 4

/*
 * The NIC type definition:
 * For backward compatibility, lower 16 bits used as they were.
 * Lower 16 bit: NIC_TYPE values
 * Uppoer 16 bit: NIC_TYPE Flags
 */
#घोषणा NIC_TYPE_NIC0		0x00000010
#घोषणा NIC_TYPE_NIC1		0x00000011
#घोषणा NIC_TYPE_NIC2		0x00000012
#घोषणा NIC_TYPE_NIC3		0x00000013
#घोषणा NIC_TYPE_ARP		0x00000100
#घोषणा NIC_TYPE_ICMPV6		0x00000200
#घोषणा NIC_TYPE_MASK		0x0000FFFF
#घोषणा NIC_TYPE_F_IPV4		0x00010000
#घोषणा NIC_TYPE_F_IPV6		0x00020000
#घोषणा NIC_TYPE_F_DHCP		0x00040000
#घोषणा NIC_TYPE_F_NDP		0x00080000
#घोषणा NIC_TYPE_F_VLAN		0x00100000

काष्ठा hci_packet अणु
	__dev16 cmd_evt;
	__dev16 len;
	u8 data[];
पूर्ण __packed;

काष्ठा tlv अणु
	u8 type;
	u8 len;
	u8 *data[1];
पूर्ण __packed;

काष्ठा sdu_header अणु
	__dev16 cmd_evt;
	__dev16 len;
	__dev32 dft_eps_id;
	__dev32 bearer_ID;
	__dev32 nic_type;
पूर्ण __packed;

काष्ठा sdu अणु
	__dev16 cmd_evt;
	__dev16 len;
	__dev32 dft_eps_ID;
	__dev32 bearer_ID;
	__dev32 nic_type;
	u8 data[];
पूर्ण __packed;

काष्ठा multi_sdu अणु
	__dev16 cmd_evt;
	__dev16 len;
	__dev16 num_packet;
	__dev16 reserved;
	u8 data[];
पूर्ण __packed;

काष्ठा hci_pdn_table_ind अणु
	__dev16 cmd_evt;
	__dev16 len;
	u8 activate;
	__dev32 dft_eps_id;
	__dev32 nic_type;
	u8 pdn_type;
	u8 ipv4_addr[4];
	u8 ipv6_पूर्णांकf_id[8];
पूर्ण __packed;

काष्ठा hci_connect_ind अणु
	__dev16 cmd_evt;
	__dev16 len;
	__dev32 connect;
पूर्ण __packed;

#पूर्ण_अगर /* _HCI_PACKET_H_ */
