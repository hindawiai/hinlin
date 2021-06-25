<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 */

#अगर_अघोषित IB_PACK_H
#घोषणा IB_PACK_H

#समावेश <rdma/ib_verbs.h>
#समावेश <uapi/linux/अगर_ether.h>

क्रमागत अणु
	IB_LRH_BYTES		= 8,
	IB_ETH_BYTES		= 14,
	IB_VLAN_BYTES		= 4,
	IB_GRH_BYTES		= 40,
	IB_IP4_BYTES		= 20,
	IB_UDP_BYTES		= 8,
	IB_BTH_BYTES		= 12,
	IB_DETH_BYTES		= 8,
	IB_EXT_ATOMICETH_BYTES	= 28,
	IB_EXT_XRC_BYTES	= 4,
	IB_ICRC_BYTES		= 4
पूर्ण;

काष्ठा ib_field अणु
	माप_प्रकार काष्ठा_offset_bytes;
	माप_प्रकार काष्ठा_size_bytes;
	पूर्णांक    offset_words;
	पूर्णांक    offset_bits;
	पूर्णांक    size_bits;
	अक्षर  *field_name;
पूर्ण;

#घोषणा RESERVED \
	.field_name          = "reserved"

/*
 * This macro cleans up the definitions of स्थिरants क्रम BTH opcodes.
 * It is used to define स्थिरants such as IB_OPCODE_UD_SEND_ONLY,
 * which becomes IB_OPCODE_UD + IB_OPCODE_SEND_ONLY, and this gives
 * the correct value.
 *
 * In लघु, user code should use the स्थिरants defined using the
 * macro rather than worrying about adding together other स्थिरants.
*/
#घोषणा IB_OPCODE(transport, op) \
	IB_OPCODE_ ## transport ## _ ## op = \
		IB_OPCODE_ ## transport + IB_OPCODE_ ## op

क्रमागत अणु
	/* transport types -- just used to define real स्थिरants */
	IB_OPCODE_RC                                = 0x00,
	IB_OPCODE_UC                                = 0x20,
	IB_OPCODE_RD                                = 0x40,
	IB_OPCODE_UD                                = 0x60,
	/* per IBTA 1.3 vol 1 Table 38, A10.3.2 */
	IB_OPCODE_CNP                               = 0x80,
	/* Manufacturer specअगरic */
	IB_OPCODE_MSP                               = 0xe0,

	/* operations -- just used to define real स्थिरants */
	IB_OPCODE_SEND_FIRST                        = 0x00,
	IB_OPCODE_SEND_MIDDLE                       = 0x01,
	IB_OPCODE_SEND_LAST                         = 0x02,
	IB_OPCODE_SEND_LAST_WITH_IMMEDIATE          = 0x03,
	IB_OPCODE_SEND_ONLY                         = 0x04,
	IB_OPCODE_SEND_ONLY_WITH_IMMEDIATE          = 0x05,
	IB_OPCODE_RDMA_WRITE_FIRST                  = 0x06,
	IB_OPCODE_RDMA_WRITE_MIDDLE                 = 0x07,
	IB_OPCODE_RDMA_WRITE_LAST                   = 0x08,
	IB_OPCODE_RDMA_WRITE_LAST_WITH_IMMEDIATE    = 0x09,
	IB_OPCODE_RDMA_WRITE_ONLY                   = 0x0a,
	IB_OPCODE_RDMA_WRITE_ONLY_WITH_IMMEDIATE    = 0x0b,
	IB_OPCODE_RDMA_READ_REQUEST                 = 0x0c,
	IB_OPCODE_RDMA_READ_RESPONSE_FIRST          = 0x0d,
	IB_OPCODE_RDMA_READ_RESPONSE_MIDDLE         = 0x0e,
	IB_OPCODE_RDMA_READ_RESPONSE_LAST           = 0x0f,
	IB_OPCODE_RDMA_READ_RESPONSE_ONLY           = 0x10,
	IB_OPCODE_ACKNOWLEDGE                       = 0x11,
	IB_OPCODE_ATOMIC_ACKNOWLEDGE                = 0x12,
	IB_OPCODE_COMPARE_SWAP                      = 0x13,
	IB_OPCODE_FETCH_ADD                         = 0x14,
	/* opcode 0x15 is reserved */
	IB_OPCODE_SEND_LAST_WITH_INVALIDATE         = 0x16,
	IB_OPCODE_SEND_ONLY_WITH_INVALIDATE         = 0x17,

	/* real स्थिरants follow -- see comment about above IB_OPCODE()
	   macro क्रम more details */

	/* RC */
	IB_OPCODE(RC, SEND_FIRST),
	IB_OPCODE(RC, SEND_MIDDLE),
	IB_OPCODE(RC, SEND_LAST),
	IB_OPCODE(RC, SEND_LAST_WITH_IMMEDIATE),
	IB_OPCODE(RC, SEND_ONLY),
	IB_OPCODE(RC, SEND_ONLY_WITH_IMMEDIATE),
	IB_OPCODE(RC, RDMA_WRITE_FIRST),
	IB_OPCODE(RC, RDMA_WRITE_MIDDLE),
	IB_OPCODE(RC, RDMA_WRITE_LAST),
	IB_OPCODE(RC, RDMA_WRITE_LAST_WITH_IMMEDIATE),
	IB_OPCODE(RC, RDMA_WRITE_ONLY),
	IB_OPCODE(RC, RDMA_WRITE_ONLY_WITH_IMMEDIATE),
	IB_OPCODE(RC, RDMA_READ_REQUEST),
	IB_OPCODE(RC, RDMA_READ_RESPONSE_FIRST),
	IB_OPCODE(RC, RDMA_READ_RESPONSE_MIDDLE),
	IB_OPCODE(RC, RDMA_READ_RESPONSE_LAST),
	IB_OPCODE(RC, RDMA_READ_RESPONSE_ONLY),
	IB_OPCODE(RC, ACKNOWLEDGE),
	IB_OPCODE(RC, ATOMIC_ACKNOWLEDGE),
	IB_OPCODE(RC, COMPARE_SWAP),
	IB_OPCODE(RC, FETCH_ADD),
	IB_OPCODE(RC, SEND_LAST_WITH_INVALIDATE),
	IB_OPCODE(RC, SEND_ONLY_WITH_INVALIDATE),

	/* UC */
	IB_OPCODE(UC, SEND_FIRST),
	IB_OPCODE(UC, SEND_MIDDLE),
	IB_OPCODE(UC, SEND_LAST),
	IB_OPCODE(UC, SEND_LAST_WITH_IMMEDIATE),
	IB_OPCODE(UC, SEND_ONLY),
	IB_OPCODE(UC, SEND_ONLY_WITH_IMMEDIATE),
	IB_OPCODE(UC, RDMA_WRITE_FIRST),
	IB_OPCODE(UC, RDMA_WRITE_MIDDLE),
	IB_OPCODE(UC, RDMA_WRITE_LAST),
	IB_OPCODE(UC, RDMA_WRITE_LAST_WITH_IMMEDIATE),
	IB_OPCODE(UC, RDMA_WRITE_ONLY),
	IB_OPCODE(UC, RDMA_WRITE_ONLY_WITH_IMMEDIATE),

	/* RD */
	IB_OPCODE(RD, SEND_FIRST),
	IB_OPCODE(RD, SEND_MIDDLE),
	IB_OPCODE(RD, SEND_LAST),
	IB_OPCODE(RD, SEND_LAST_WITH_IMMEDIATE),
	IB_OPCODE(RD, SEND_ONLY),
	IB_OPCODE(RD, SEND_ONLY_WITH_IMMEDIATE),
	IB_OPCODE(RD, RDMA_WRITE_FIRST),
	IB_OPCODE(RD, RDMA_WRITE_MIDDLE),
	IB_OPCODE(RD, RDMA_WRITE_LAST),
	IB_OPCODE(RD, RDMA_WRITE_LAST_WITH_IMMEDIATE),
	IB_OPCODE(RD, RDMA_WRITE_ONLY),
	IB_OPCODE(RD, RDMA_WRITE_ONLY_WITH_IMMEDIATE),
	IB_OPCODE(RD, RDMA_READ_REQUEST),
	IB_OPCODE(RD, RDMA_READ_RESPONSE_FIRST),
	IB_OPCODE(RD, RDMA_READ_RESPONSE_MIDDLE),
	IB_OPCODE(RD, RDMA_READ_RESPONSE_LAST),
	IB_OPCODE(RD, RDMA_READ_RESPONSE_ONLY),
	IB_OPCODE(RD, ACKNOWLEDGE),
	IB_OPCODE(RD, ATOMIC_ACKNOWLEDGE),
	IB_OPCODE(RD, COMPARE_SWAP),
	IB_OPCODE(RD, FETCH_ADD),

	/* UD */
	IB_OPCODE(UD, SEND_ONLY),
	IB_OPCODE(UD, SEND_ONLY_WITH_IMMEDIATE)
पूर्ण;

क्रमागत अणु
	IB_LNH_RAW        = 0,
	IB_LNH_IP         = 1,
	IB_LNH_IBA_LOCAL  = 2,
	IB_LNH_IBA_GLOBAL = 3
पूर्ण;

काष्ठा ib_unpacked_lrh अणु
	u8        भव_lane;
	u8        link_version;
	u8        service_level;
	u8        link_next_header;
	__be16    destination_lid;
	__be16    packet_length;
	__be16    source_lid;
पूर्ण;

काष्ठा ib_unpacked_grh अणु
	u8    	     ip_version;
	u8    	     traffic_class;
	__be32 	     flow_label;
	__be16       payload_length;
	u8    	     next_header;
	u8    	     hop_limit;
	जोड़ ib_gid source_gid;
	जोड़ ib_gid destination_gid;
पूर्ण;

काष्ठा ib_unpacked_bth अणु
	u8           opcode;
	u8           solicited_event;
	u8           mig_req;
	u8           pad_count;
	u8           transport_header_version;
	__be16       pkey;
	__be32       destination_qpn;
	u8           ack_req;
	__be32       psn;
पूर्ण;

काष्ठा ib_unpacked_deth अणु
	__be32       qkey;
	__be32       source_qpn;
पूर्ण;

काष्ठा ib_unpacked_eth अणु
	u8	dmac_h[4];
	u8	dmac_l[2];
	u8	smac_h[2];
	u8	smac_l[4];
	__be16	type;
पूर्ण;

काष्ठा ib_unpacked_ip4 अणु
	u8	ver;
	u8	hdr_len;
	u8	tos;
	__be16	tot_len;
	__be16	id;
	__be16	frag_off;
	u8	ttl;
	u8	protocol;
	__sum16	check;
	__be32	saddr;
	__be32	daddr;
पूर्ण;

काष्ठा ib_unpacked_udp अणु
	__be16	sport;
	__be16	dport;
	__be16	length;
	__be16	csum;
पूर्ण;

काष्ठा ib_unpacked_vlan अणु
	__be16  tag;
	__be16  type;
पूर्ण;

काष्ठा ib_ud_header अणु
	पूर्णांक                     lrh_present;
	काष्ठा ib_unpacked_lrh  lrh;
	पूर्णांक			eth_present;
	काष्ठा ib_unpacked_eth	eth;
	पूर्णांक                     vlan_present;
	काष्ठा ib_unpacked_vlan vlan;
	पूर्णांक			grh_present;
	काष्ठा ib_unpacked_grh	grh;
	पूर्णांक			ipv4_present;
	काष्ठा ib_unpacked_ip4	ip4;
	पूर्णांक			udp_present;
	काष्ठा ib_unpacked_udp	udp;
	काष्ठा ib_unpacked_bth	bth;
	काष्ठा ib_unpacked_deth deth;
	पूर्णांक			immediate_present;
	__be32			immediate_data;
पूर्ण;

व्योम ib_pack(स्थिर काष्ठा ib_field        *desc,
	     पूर्णांक                           desc_len,
	     व्योम                         *काष्ठाure,
	     व्योम                         *buf);

व्योम ib_unpack(स्थिर काष्ठा ib_field        *desc,
	       पूर्णांक                           desc_len,
	       व्योम                         *buf,
	       व्योम                         *काष्ठाure);

__sum16 ib_ud_ip4_csum(काष्ठा ib_ud_header *header);

पूर्णांक ib_ud_header_init(पूर्णांक		    payload_bytes,
		      पूर्णांक		    lrh_present,
		      पूर्णांक		    eth_present,
		      पूर्णांक		    vlan_present,
		      पूर्णांक		    grh_present,
		      पूर्णांक		    ip_version,
		      पूर्णांक		    udp_present,
		      पूर्णांक		    immediate_present,
		      काष्ठा ib_ud_header *header);

पूर्णांक ib_ud_header_pack(काष्ठा ib_ud_header *header,
		      व्योम                *buf);

पूर्णांक ib_ud_header_unpack(व्योम                *buf,
			काष्ठा ib_ud_header *header);

#पूर्ण_अगर /* IB_PACK_H */
