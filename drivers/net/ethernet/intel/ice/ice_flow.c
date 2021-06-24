<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश "ice_common.h"
#समावेश "ice_flow.h"

/* Describe properties of a protocol header field */
काष्ठा ice_flow_field_info अणु
	क्रमागत ice_flow_seg_hdr hdr;
	s16 off;	/* Offset from start of a protocol header, in bits */
	u16 size;	/* Size of fields in bits */
	u16 mask;	/* 16-bit mask क्रम field */
पूर्ण;

#घोषणा ICE_FLOW_FLD_INFO(_hdr, _offset_bytes, _size_bytes) अणु \
	.hdr = _hdr, \
	.off = (_offset_bytes) * BITS_PER_BYTE, \
	.size = (_size_bytes) * BITS_PER_BYTE, \
	.mask = 0, \
पूर्ण

#घोषणा ICE_FLOW_FLD_INFO_MSK(_hdr, _offset_bytes, _size_bytes, _mask) अणु \
	.hdr = _hdr, \
	.off = (_offset_bytes) * BITS_PER_BYTE, \
	.size = (_size_bytes) * BITS_PER_BYTE, \
	.mask = _mask, \
पूर्ण

/* Table containing properties of supported protocol header fields */
अटल स्थिर
काष्ठा ice_flow_field_info ice_flds_info[ICE_FLOW_FIELD_IDX_MAX] = अणु
	/* Ether */
	/* ICE_FLOW_FIELD_IDX_ETH_DA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ETH, 0, ETH_ALEN),
	/* ICE_FLOW_FIELD_IDX_ETH_SA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ETH, ETH_ALEN, ETH_ALEN),
	/* ICE_FLOW_FIELD_IDX_S_VLAN */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_VLAN, 12, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_C_VLAN */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_VLAN, 14, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_ETH_TYPE */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ETH, 0, माप(__be16)),
	/* IPv4 / IPv6 */
	/* ICE_FLOW_FIELD_IDX_IPV4_DSCP */
	ICE_FLOW_FLD_INFO_MSK(ICE_FLOW_SEG_HDR_IPV4, 0, 1, 0x00fc),
	/* ICE_FLOW_FIELD_IDX_IPV6_DSCP */
	ICE_FLOW_FLD_INFO_MSK(ICE_FLOW_SEG_HDR_IPV6, 0, 1, 0x0ff0),
	/* ICE_FLOW_FIELD_IDX_IPV4_TTL */
	ICE_FLOW_FLD_INFO_MSK(ICE_FLOW_SEG_HDR_NONE, 8, 1, 0xff00),
	/* ICE_FLOW_FIELD_IDX_IPV4_PROT */
	ICE_FLOW_FLD_INFO_MSK(ICE_FLOW_SEG_HDR_NONE, 8, 1, 0x00ff),
	/* ICE_FLOW_FIELD_IDX_IPV6_TTL */
	ICE_FLOW_FLD_INFO_MSK(ICE_FLOW_SEG_HDR_NONE, 6, 1, 0x00ff),
	/* ICE_FLOW_FIELD_IDX_IPV6_PROT */
	ICE_FLOW_FLD_INFO_MSK(ICE_FLOW_SEG_HDR_NONE, 6, 1, 0xff00),
	/* ICE_FLOW_FIELD_IDX_IPV4_SA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_IPV4, 12, माप(काष्ठा in_addr)),
	/* ICE_FLOW_FIELD_IDX_IPV4_DA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_IPV4, 16, माप(काष्ठा in_addr)),
	/* ICE_FLOW_FIELD_IDX_IPV6_SA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_IPV6, 8, माप(काष्ठा in6_addr)),
	/* ICE_FLOW_FIELD_IDX_IPV6_DA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_IPV6, 24, माप(काष्ठा in6_addr)),
	/* Transport */
	/* ICE_FLOW_FIELD_IDX_TCP_SRC_PORT */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_TCP, 0, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_TCP_DST_PORT */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_TCP, 2, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_UDP_SRC_PORT */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_UDP, 0, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_UDP_DST_PORT */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_UDP, 2, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_SCTP, 0, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_SCTP_DST_PORT */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_SCTP, 2, माप(__be16)),
	/* ICE_FLOW_FIELD_IDX_TCP_FLAGS */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_TCP, 13, 1),
	/* ARP */
	/* ICE_FLOW_FIELD_IDX_ARP_SIP */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ARP, 14, माप(काष्ठा in_addr)),
	/* ICE_FLOW_FIELD_IDX_ARP_DIP */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ARP, 24, माप(काष्ठा in_addr)),
	/* ICE_FLOW_FIELD_IDX_ARP_SHA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ARP, 8, ETH_ALEN),
	/* ICE_FLOW_FIELD_IDX_ARP_DHA */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ARP, 18, ETH_ALEN),
	/* ICE_FLOW_FIELD_IDX_ARP_OP */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ARP, 6, माप(__be16)),
	/* ICMP */
	/* ICE_FLOW_FIELD_IDX_ICMP_TYPE */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ICMP, 0, 1),
	/* ICE_FLOW_FIELD_IDX_ICMP_CODE */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ICMP, 1, 1),
	/* GRE */
	/* ICE_FLOW_FIELD_IDX_GRE_KEYID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_GRE, 12,
			  माप_field(काष्ठा gre_full_hdr, key)),
	/* GTP */
	/* ICE_FLOW_FIELD_IDX_GTPC_TEID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_GTPC_TEID, 12, माप(__be32)),
	/* ICE_FLOW_FIELD_IDX_GTPU_IP_TEID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_GTPU_IP, 12, माप(__be32)),
	/* ICE_FLOW_FIELD_IDX_GTPU_EH_TEID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_GTPU_EH, 12, माप(__be32)),
	/* ICE_FLOW_FIELD_IDX_GTPU_EH_QFI */
	ICE_FLOW_FLD_INFO_MSK(ICE_FLOW_SEG_HDR_GTPU_EH, 22, माप(__be16),
			      0x3f00),
	/* ICE_FLOW_FIELD_IDX_GTPU_UP_TEID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_GTPU_UP, 12, माप(__be32)),
	/* ICE_FLOW_FIELD_IDX_GTPU_DWN_TEID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_GTPU_DWN, 12, माप(__be32)),
	/* PPPoE */
	/* ICE_FLOW_FIELD_IDX_PPPOE_SESS_ID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_PPPOE, 2, माप(__be16)),
	/* PFCP */
	/* ICE_FLOW_FIELD_IDX_PFCP_SEID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_PFCP_SESSION, 12, माप(__be64)),
	/* L2TPv3 */
	/* ICE_FLOW_FIELD_IDX_L2TPV3_SESS_ID */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_L2TPV3, 0, माप(__be32)),
	/* ESP */
	/* ICE_FLOW_FIELD_IDX_ESP_SPI */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_ESP, 0, माप(__be32)),
	/* AH */
	/* ICE_FLOW_FIELD_IDX_AH_SPI */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_AH, 4, माप(__be32)),
	/* NAT_T_ESP */
	/* ICE_FLOW_FIELD_IDX_NAT_T_ESP_SPI */
	ICE_FLOW_FLD_INFO(ICE_FLOW_SEG_HDR_NAT_T_ESP, 8, माप(__be32)),
पूर्ण;

/* Biपंचांगaps indicating relevant packet types क्रम a particular protocol header
 *
 * Packet types क्रम packets with an Outer/First/Single MAC header
 */
अटल स्थिर u32 ice_ptypes_mac_ofos[] = अणु
	0xFDC00846, 0xBFBF7F7E, 0xF70001DF, 0xFEFDFDFB,
	0x0000077E, 0x00000000, 0x00000000, 0x00000000,
	0x00400000, 0x03FFF000, 0x7FFFFFE0, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last MAC VLAN header */
अटल स्थिर u32 ice_ptypes_macvlan_il[] = अणु
	0x00000000, 0xBC000000, 0x000001DF, 0xF0000000,
	0x0000077E, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outer/First/Single IPv4 header, करोes NOT
 * include IPv4 other PTYPEs
 */
अटल स्थिर u32 ice_ptypes_ipv4_ofos[] = अणु
	0x1DC00000, 0x04000800, 0x00000000, 0x00000000,
	0x00000000, 0x00000155, 0x00000000, 0x00000000,
	0x00000000, 0x000FC000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outer/First/Single IPv4 header, includes
 * IPv4 other PTYPEs
 */
अटल स्थिर u32 ice_ptypes_ipv4_ofos_all[] = अणु
	0x1DC00000, 0x04000800, 0x00000000, 0x00000000,
	0x00000000, 0x00000155, 0x00000000, 0x00000000,
	0x00000000, 0x000FC000, 0x83E0F800, 0x00000101,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last IPv4 header */
अटल स्थिर u32 ice_ptypes_ipv4_il[] = अणु
	0xE0000000, 0xB807700E, 0x80000003, 0xE01DC03B,
	0x0000000E, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x001FF800, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outer/First/Single IPv6 header, करोes NOT
 * include IPv6 other PTYPEs
 */
अटल स्थिर u32 ice_ptypes_ipv6_ofos[] = अणु
	0x00000000, 0x00000000, 0x77000000, 0x10002000,
	0x00000000, 0x000002AA, 0x00000000, 0x00000000,
	0x00000000, 0x03F00000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outer/First/Single IPv6 header, includes
 * IPv6 other PTYPEs
 */
अटल स्थिर u32 ice_ptypes_ipv6_ofos_all[] = अणु
	0x00000000, 0x00000000, 0x77000000, 0x10002000,
	0x00000000, 0x000002AA, 0x00000000, 0x00000000,
	0x00080F00, 0x03F00000, 0x7C1F0000, 0x00000206,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last IPv6 header */
अटल स्थिर u32 ice_ptypes_ipv6_il[] = अणु
	0x00000000, 0x03B80770, 0x000001DC, 0x0EE00000,
	0x00000770, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x7FE00000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outer/First/Single IPv4 header - no L4 */
अटल स्थिर u32 ice_ptypes_ipv4_ofos_no_l4[] = अणु
	0x10C00000, 0x04000800, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outermost/First ARP header */
अटल स्थिर u32 ice_ptypes_arp_of[] = अणु
	0x00000800, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last IPv4 header - no L4 */
अटल स्थिर u32 ice_ptypes_ipv4_il_no_l4[] = अणु
	0x60000000, 0x18043008, 0x80000002, 0x6010c021,
	0x00000008, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outer/First/Single IPv6 header - no L4 */
अटल स्थिर u32 ice_ptypes_ipv6_ofos_no_l4[] = अणु
	0x00000000, 0x00000000, 0x43000000, 0x10002000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last IPv6 header - no L4 */
अटल स्थिर u32 ice_ptypes_ipv6_il_no_l4[] = अणु
	0x00000000, 0x02180430, 0x0000010c, 0x086010c0,
	0x00000430, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* UDP Packet types क्रम non-tunneled packets or tunneled
 * packets with inner UDP.
 */
अटल स्थिर u32 ice_ptypes_udp_il[] = अणु
	0x81000000, 0x20204040, 0x04000010, 0x80810102,
	0x00000040, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00410000, 0x90842000, 0x00000007,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last TCP header */
अटल स्थिर u32 ice_ptypes_tcp_il[] = अणु
	0x04000000, 0x80810102, 0x10000040, 0x02040408,
	0x00000102, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00820000, 0x21084000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last SCTP header */
अटल स्थिर u32 ice_ptypes_sctp_il[] = अणु
	0x08000000, 0x01020204, 0x20000081, 0x04080810,
	0x00000204, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x01040000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outermost/First ICMP header */
अटल स्थिर u32 ice_ptypes_icmp_of[] = अणु
	0x10000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last ICMP header */
अटल स्थिर u32 ice_ptypes_icmp_il[] = अणु
	0x00000000, 0x02040408, 0x40000102, 0x08101020,
	0x00000408, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x42108000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Outermost/First GRE header */
अटल स्थिर u32 ice_ptypes_gre_of[] = अणु
	0x00000000, 0xBFBF7800, 0x000001DF, 0xFEFDE000,
	0x0000017E, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with an Innermost/Last MAC header */
अटल स्थिर u32 ice_ptypes_mac_il[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम GTPC */
अटल स्थिर u32 ice_ptypes_gtpc[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000180, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम GTPC with TEID */
अटल स्थिर u32 ice_ptypes_gtpc_tid[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000060, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम GTPU */
अटल स्थिर काष्ठा ice_ptype_attributes ice_attr_gtpu_eh[] = अणु
	अणु ICE_MAC_IPV4_GTPU_IPV4_FRAG,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_PAY,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_UDP_PAY, ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_TCP,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_ICMP,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_FRAG,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_PAY,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_UDP_PAY, ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_TCP,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_ICMP,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_FRAG,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_PAY,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_UDP_PAY, ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_TCP,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_ICMPV6,  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_FRAG,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_PAY,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_UDP_PAY, ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_TCP,	  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_ICMPV6,  ICE_PTYPE_ATTR_GTP_PDU_EH पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ice_ptype_attributes ice_attr_gtpu_करोwn[] = अणु
	अणु ICE_MAC_IPV4_GTPU_IPV4_FRAG,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_PAY,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_UDP_PAY, ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_TCP,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_ICMP,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_FRAG,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_PAY,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_UDP_PAY, ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_TCP,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_ICMP,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_FRAG,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_PAY,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_UDP_PAY, ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_TCP,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_ICMPV6,  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_FRAG,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_PAY,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_UDP_PAY, ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_TCP,	  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_ICMPV6,  ICE_PTYPE_ATTR_GTP_DOWNLINK पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ice_ptype_attributes ice_attr_gtpu_up[] = अणु
	अणु ICE_MAC_IPV4_GTPU_IPV4_FRAG,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_PAY,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_UDP_PAY, ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_TCP,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV4_ICMP,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_FRAG,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_PAY,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_UDP_PAY, ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_TCP,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV4_ICMP,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_FRAG,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_PAY,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_UDP_PAY, ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_TCP,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV4_GTPU_IPV6_ICMPV6,  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_FRAG,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_PAY,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_UDP_PAY, ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_TCP,	  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
	अणु ICE_MAC_IPV6_GTPU_IPV6_ICMPV6,  ICE_PTYPE_ATTR_GTP_UPLINK पूर्ण,
पूर्ण;

अटल स्थिर u32 ice_ptypes_gtpu[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x7FFFFE00, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम PPPoE */
अटल स्थिर u32 ice_ptypes_pppoe[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x03ffe000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with PFCP NODE header */
अटल स्थिर u32 ice_ptypes_pfcp_node[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x80000000, 0x00000002,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with PFCP SESSION header */
अटल स्थिर u32 ice_ptypes_pfcp_session[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000005,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम L2TPv3 */
अटल स्थिर u32 ice_ptypes_l2tpv3[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000300,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम ESP */
अटल स्थिर u32 ice_ptypes_esp[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000003, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम AH */
अटल स्थिर u32 ice_ptypes_ah[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x0000000C, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Packet types क्रम packets with NAT_T ESP header */
अटल स्थिर u32 ice_ptypes_nat_t_esp[] = अणु
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000030, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

अटल स्थिर u32 ice_ptypes_mac_non_ip_ofos[] = अणु
	0x00000846, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00400000, 0x03FFF000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000,
पूर्ण;

/* Manage parameters and info. used during the creation of a flow profile */
काष्ठा ice_flow_prof_params अणु
	क्रमागत ice_block blk;
	u16 entry_length; /* # of bytes क्रमmatted entry will require */
	u8 es_cnt;
	काष्ठा ice_flow_prof *prof;

	/* For ACL, the es[0] will have the data of ICE_RX_MDID_PKT_FLAGS_15_0
	 * This will give us the direction flags.
	 */
	काष्ठा ice_fv_word es[ICE_MAX_FV_WORDS];
	/* attributes can be used to add attributes to a particular PTYPE */
	स्थिर काष्ठा ice_ptype_attributes *attr;
	u16 attr_cnt;

	u16 mask[ICE_MAX_FV_WORDS];
	DECLARE_BITMAP(ptypes, ICE_FLOW_PTYPE_MAX);
पूर्ण;

#घोषणा ICE_FLOW_RSS_HDRS_INNER_MASK \
	(ICE_FLOW_SEG_HDR_PPPOE | ICE_FLOW_SEG_HDR_GTPC | \
	ICE_FLOW_SEG_HDR_GTPC_TEID | ICE_FLOW_SEG_HDR_GTPU | \
	ICE_FLOW_SEG_HDR_PFCP_SESSION | ICE_FLOW_SEG_HDR_L2TPV3 | \
	ICE_FLOW_SEG_HDR_ESP | ICE_FLOW_SEG_HDR_AH | \
	ICE_FLOW_SEG_HDR_NAT_T_ESP)

#घोषणा ICE_FLOW_SEG_HDRS_L2_MASK	\
	(ICE_FLOW_SEG_HDR_ETH | ICE_FLOW_SEG_HDR_VLAN)
#घोषणा ICE_FLOW_SEG_HDRS_L3_MASK	\
	(ICE_FLOW_SEG_HDR_IPV4 | ICE_FLOW_SEG_HDR_IPV6 | ICE_FLOW_SEG_HDR_ARP)
#घोषणा ICE_FLOW_SEG_HDRS_L4_MASK	\
	(ICE_FLOW_SEG_HDR_ICMP | ICE_FLOW_SEG_HDR_TCP | ICE_FLOW_SEG_HDR_UDP | \
	 ICE_FLOW_SEG_HDR_SCTP)
/* mask क्रम L4 protocols that are NOT part of IPv4/6 OTHER PTYPE groups */
#घोषणा ICE_FLOW_SEG_HDRS_L4_MASK_NO_OTHER	\
	(ICE_FLOW_SEG_HDR_TCP | ICE_FLOW_SEG_HDR_UDP | ICE_FLOW_SEG_HDR_SCTP)

/**
 * ice_flow_val_hdrs - validates packet segments क्रम valid protocol headers
 * @segs: array of one or more packet segments that describe the flow
 * @segs_cnt: number of packet segments provided
 */
अटल क्रमागत ice_status
ice_flow_val_hdrs(काष्ठा ice_flow_seg_info *segs, u8 segs_cnt)
अणु
	u8 i;

	क्रम (i = 0; i < segs_cnt; i++) अणु
		/* Multiple L3 headers */
		अगर (segs[i].hdrs & ICE_FLOW_SEG_HDRS_L3_MASK &&
		    !is_घातer_of_2(segs[i].hdrs & ICE_FLOW_SEG_HDRS_L3_MASK))
			वापस ICE_ERR_PARAM;

		/* Multiple L4 headers */
		अगर (segs[i].hdrs & ICE_FLOW_SEG_HDRS_L4_MASK &&
		    !is_घातer_of_2(segs[i].hdrs & ICE_FLOW_SEG_HDRS_L4_MASK))
			वापस ICE_ERR_PARAM;
	पूर्ण

	वापस 0;
पूर्ण

/* Sizes of fixed known protocol headers without header options */
#घोषणा ICE_FLOW_PROT_HDR_SZ_MAC	14
#घोषणा ICE_FLOW_PROT_HDR_SZ_MAC_VLAN	(ICE_FLOW_PROT_HDR_SZ_MAC + 2)
#घोषणा ICE_FLOW_PROT_HDR_SZ_IPV4	20
#घोषणा ICE_FLOW_PROT_HDR_SZ_IPV6	40
#घोषणा ICE_FLOW_PROT_HDR_SZ_ARP	28
#घोषणा ICE_FLOW_PROT_HDR_SZ_ICMP	8
#घोषणा ICE_FLOW_PROT_HDR_SZ_TCP	20
#घोषणा ICE_FLOW_PROT_HDR_SZ_UDP	8
#घोषणा ICE_FLOW_PROT_HDR_SZ_SCTP	12

/**
 * ice_flow_calc_seg_sz - calculates size of a packet segment based on headers
 * @params: inक्रमmation about the flow to be processed
 * @seg: index of packet segment whose header size is to be determined
 */
अटल u16 ice_flow_calc_seg_sz(काष्ठा ice_flow_prof_params *params, u8 seg)
अणु
	u16 sz;

	/* L2 headers */
	sz = (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_VLAN) ?
		ICE_FLOW_PROT_HDR_SZ_MAC_VLAN : ICE_FLOW_PROT_HDR_SZ_MAC;

	/* L3 headers */
	अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_IPV4)
		sz += ICE_FLOW_PROT_HDR_SZ_IPV4;
	अन्यथा अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_IPV6)
		sz += ICE_FLOW_PROT_HDR_SZ_IPV6;
	अन्यथा अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_ARP)
		sz += ICE_FLOW_PROT_HDR_SZ_ARP;
	अन्यथा अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDRS_L4_MASK)
		/* An L3 header is required अगर L4 is specअगरied */
		वापस 0;

	/* L4 headers */
	अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_ICMP)
		sz += ICE_FLOW_PROT_HDR_SZ_ICMP;
	अन्यथा अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_TCP)
		sz += ICE_FLOW_PROT_HDR_SZ_TCP;
	अन्यथा अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_UDP)
		sz += ICE_FLOW_PROT_HDR_SZ_UDP;
	अन्यथा अगर (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_SCTP)
		sz += ICE_FLOW_PROT_HDR_SZ_SCTP;

	वापस sz;
पूर्ण

/**
 * ice_flow_proc_seg_hdrs - process protocol headers present in pkt segments
 * @params: inक्रमmation about the flow to be processed
 *
 * This function identअगरies the packet types associated with the protocol
 * headers being present in packet segments of the specअगरied flow profile.
 */
अटल क्रमागत ice_status
ice_flow_proc_seg_hdrs(काष्ठा ice_flow_prof_params *params)
अणु
	काष्ठा ice_flow_prof *prof;
	u8 i;

	स_रखो(params->ptypes, 0xff, माप(params->ptypes));

	prof = params->prof;

	क्रम (i = 0; i < params->prof->segs_cnt; i++) अणु
		स्थिर अचिन्हित दीर्घ *src;
		u32 hdrs;

		hdrs = prof->segs[i].hdrs;

		अगर (hdrs & ICE_FLOW_SEG_HDR_ETH) अणु
			src = !i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_mac_ofos :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_mac_il;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण

		अगर (i && hdrs & ICE_FLOW_SEG_HDR_VLAN) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_macvlan_il;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण

		अगर (!i && hdrs & ICE_FLOW_SEG_HDR_ARP) अणु
			biपंचांगap_and(params->ptypes, params->ptypes,
				   (स्थिर अचिन्हित दीर्घ *)ice_ptypes_arp_of,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण

		अगर ((hdrs & ICE_FLOW_SEG_HDR_IPV4) &&
		    (hdrs & ICE_FLOW_SEG_HDR_IPV_OTHER)) अणु
			src = i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv4_il :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv4_ofos_all;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर ((hdrs & ICE_FLOW_SEG_HDR_IPV6) &&
			   (hdrs & ICE_FLOW_SEG_HDR_IPV_OTHER)) अणु
			src = i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv6_il :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv6_ofos_all;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर ((hdrs & ICE_FLOW_SEG_HDR_IPV4) &&
			   !(hdrs & ICE_FLOW_SEG_HDRS_L4_MASK_NO_OTHER)) अणु
			src = !i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv4_ofos_no_l4 :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv4_il_no_l4;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_IPV4) अणु
			src = !i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv4_ofos :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv4_il;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर ((hdrs & ICE_FLOW_SEG_HDR_IPV6) &&
			   !(hdrs & ICE_FLOW_SEG_HDRS_L4_MASK_NO_OTHER)) अणु
			src = !i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv6_ofos_no_l4 :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv6_il_no_l4;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_IPV6) अणु
			src = !i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv6_ofos :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_ipv6_il;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण

		अगर (hdrs & ICE_FLOW_SEG_HDR_ETH_NON_IP) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_mac_non_ip_ofos;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_PPPOE) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_pppoe;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_pppoe;
			biपंचांगap_andnot(params->ptypes, params->ptypes, src,
				      ICE_FLOW_PTYPE_MAX);
		पूर्ण

		अगर (hdrs & ICE_FLOW_SEG_HDR_UDP) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_udp_il;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_TCP) अणु
			biपंचांगap_and(params->ptypes, params->ptypes,
				   (स्थिर अचिन्हित दीर्घ *)ice_ptypes_tcp_il,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_SCTP) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_sctp_il;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण

		अगर (hdrs & ICE_FLOW_SEG_HDR_ICMP) अणु
			src = !i ? (स्थिर अचिन्हित दीर्घ *)ice_ptypes_icmp_of :
				(स्थिर अचिन्हित दीर्घ *)ice_ptypes_icmp_il;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_GRE) अणु
			अगर (!i) अणु
				src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_gre_of;
				biपंचांगap_and(params->ptypes, params->ptypes,
					   src, ICE_FLOW_PTYPE_MAX);
			पूर्ण
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_GTPC) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_gtpc;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_GTPC_TEID) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_gtpc_tid;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_GTPU_DWN) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_gtpu;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);

			/* Attributes क्रम GTP packet with करोwnlink */
			params->attr = ice_attr_gtpu_करोwn;
			params->attr_cnt = ARRAY_SIZE(ice_attr_gtpu_करोwn);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_GTPU_UP) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_gtpu;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);

			/* Attributes क्रम GTP packet with uplink */
			params->attr = ice_attr_gtpu_up;
			params->attr_cnt = ARRAY_SIZE(ice_attr_gtpu_up);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_GTPU_EH) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_gtpu;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);

			/* Attributes क्रम GTP packet with Extension Header */
			params->attr = ice_attr_gtpu_eh;
			params->attr_cnt = ARRAY_SIZE(ice_attr_gtpu_eh);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_GTPU_IP) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_gtpu;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_L2TPV3) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_l2tpv3;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_ESP) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_esp;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_AH) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_ah;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अगर (hdrs & ICE_FLOW_SEG_HDR_NAT_T_ESP) अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_nat_t_esp;
			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण

		अगर (hdrs & ICE_FLOW_SEG_HDR_PFCP) अणु
			अगर (hdrs & ICE_FLOW_SEG_HDR_PFCP_NODE)
				src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_pfcp_node;
			अन्यथा
				src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_pfcp_session;

			biपंचांगap_and(params->ptypes, params->ptypes, src,
				   ICE_FLOW_PTYPE_MAX);
		पूर्ण अन्यथा अणु
			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_pfcp_node;
			biपंचांगap_andnot(params->ptypes, params->ptypes, src,
				      ICE_FLOW_PTYPE_MAX);

			src = (स्थिर अचिन्हित दीर्घ *)ice_ptypes_pfcp_session;
			biपंचांगap_andnot(params->ptypes, params->ptypes, src,
				      ICE_FLOW_PTYPE_MAX);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_flow_xtract_fld - Create an extraction sequence entry क्रम the given field
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @params: inक्रमmation about the flow to be processed
 * @seg: packet segment index of the field to be extracted
 * @fld: ID of field to be extracted
 * @match: bit field of all fields
 *
 * This function determines the protocol ID, offset, and size of the given
 * field. It then allocates one or more extraction sequence entries क्रम the
 * given field, and fill the entries with protocol ID and offset inक्रमmation.
 */
अटल क्रमागत ice_status
ice_flow_xtract_fld(काष्ठा ice_hw *hw, काष्ठा ice_flow_prof_params *params,
		    u8 seg, क्रमागत ice_flow_field fld, u64 match)
अणु
	क्रमागत ice_flow_field sib = ICE_FLOW_FIELD_IDX_MAX;
	क्रमागत ice_prot_id prot_id = ICE_PROT_ID_INVAL;
	u8 fv_words = hw->blk[params->blk].es.fvw;
	काष्ठा ice_flow_fld_info *flds;
	u16 cnt, ese_bits, i;
	u16 sib_mask = 0;
	u16 mask;
	u16 off;

	flds = params->prof->segs[seg].fields;

	चयन (fld) अणु
	हाल ICE_FLOW_FIELD_IDX_ETH_DA:
	हाल ICE_FLOW_FIELD_IDX_ETH_SA:
	हाल ICE_FLOW_FIELD_IDX_S_VLAN:
	हाल ICE_FLOW_FIELD_IDX_C_VLAN:
		prot_id = seg == 0 ? ICE_PROT_MAC_OF_OR_S : ICE_PROT_MAC_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_ETH_TYPE:
		prot_id = seg == 0 ? ICE_PROT_ETYPE_OL : ICE_PROT_ETYPE_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_IPV4_DSCP:
		prot_id = seg == 0 ? ICE_PROT_IPV4_OF_OR_S : ICE_PROT_IPV4_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_IPV6_DSCP:
		prot_id = seg == 0 ? ICE_PROT_IPV6_OF_OR_S : ICE_PROT_IPV6_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_IPV4_TTL:
	हाल ICE_FLOW_FIELD_IDX_IPV4_PROT:
		prot_id = seg == 0 ? ICE_PROT_IPV4_OF_OR_S : ICE_PROT_IPV4_IL;

		/* TTL and PROT share the same extraction seq. entry.
		 * Each is considered a sibling to the other in terms of sharing
		 * the same extraction sequence entry.
		 */
		अगर (fld == ICE_FLOW_FIELD_IDX_IPV4_TTL)
			sib = ICE_FLOW_FIELD_IDX_IPV4_PROT;
		अन्यथा अगर (fld == ICE_FLOW_FIELD_IDX_IPV4_PROT)
			sib = ICE_FLOW_FIELD_IDX_IPV4_TTL;

		/* If the sibling field is also included, that field's
		 * mask needs to be included.
		 */
		अगर (match & BIT(sib))
			sib_mask = ice_flds_info[sib].mask;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_IPV6_TTL:
	हाल ICE_FLOW_FIELD_IDX_IPV6_PROT:
		prot_id = seg == 0 ? ICE_PROT_IPV6_OF_OR_S : ICE_PROT_IPV6_IL;

		/* TTL and PROT share the same extraction seq. entry.
		 * Each is considered a sibling to the other in terms of sharing
		 * the same extraction sequence entry.
		 */
		अगर (fld == ICE_FLOW_FIELD_IDX_IPV6_TTL)
			sib = ICE_FLOW_FIELD_IDX_IPV6_PROT;
		अन्यथा अगर (fld == ICE_FLOW_FIELD_IDX_IPV6_PROT)
			sib = ICE_FLOW_FIELD_IDX_IPV6_TTL;

		/* If the sibling field is also included, that field's
		 * mask needs to be included.
		 */
		अगर (match & BIT(sib))
			sib_mask = ice_flds_info[sib].mask;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_IPV4_SA:
	हाल ICE_FLOW_FIELD_IDX_IPV4_DA:
		prot_id = seg == 0 ? ICE_PROT_IPV4_OF_OR_S : ICE_PROT_IPV4_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_IPV6_SA:
	हाल ICE_FLOW_FIELD_IDX_IPV6_DA:
		prot_id = seg == 0 ? ICE_PROT_IPV6_OF_OR_S : ICE_PROT_IPV6_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_TCP_SRC_PORT:
	हाल ICE_FLOW_FIELD_IDX_TCP_DST_PORT:
	हाल ICE_FLOW_FIELD_IDX_TCP_FLAGS:
		prot_id = ICE_PROT_TCP_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_UDP_SRC_PORT:
	हाल ICE_FLOW_FIELD_IDX_UDP_DST_PORT:
		prot_id = ICE_PROT_UDP_IL_OR_S;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT:
	हाल ICE_FLOW_FIELD_IDX_SCTP_DST_PORT:
		prot_id = ICE_PROT_SCTP_IL;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_GTPC_TEID:
	हाल ICE_FLOW_FIELD_IDX_GTPU_IP_TEID:
	हाल ICE_FLOW_FIELD_IDX_GTPU_UP_TEID:
	हाल ICE_FLOW_FIELD_IDX_GTPU_DWN_TEID:
	हाल ICE_FLOW_FIELD_IDX_GTPU_EH_TEID:
	हाल ICE_FLOW_FIELD_IDX_GTPU_EH_QFI:
		/* GTP is accessed through UDP OF protocol */
		prot_id = ICE_PROT_UDP_OF;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_PPPOE_SESS_ID:
		prot_id = ICE_PROT_PPPOE;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_PFCP_SEID:
		prot_id = ICE_PROT_UDP_IL_OR_S;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_L2TPV3_SESS_ID:
		prot_id = ICE_PROT_L2TPV3;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_ESP_SPI:
		prot_id = ICE_PROT_ESP_F;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_AH_SPI:
		prot_id = ICE_PROT_ESP_2;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_NAT_T_ESP_SPI:
		prot_id = ICE_PROT_UDP_IL_OR_S;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_ARP_SIP:
	हाल ICE_FLOW_FIELD_IDX_ARP_DIP:
	हाल ICE_FLOW_FIELD_IDX_ARP_SHA:
	हाल ICE_FLOW_FIELD_IDX_ARP_DHA:
	हाल ICE_FLOW_FIELD_IDX_ARP_OP:
		prot_id = ICE_PROT_ARP_OF;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_ICMP_TYPE:
	हाल ICE_FLOW_FIELD_IDX_ICMP_CODE:
		/* ICMP type and code share the same extraction seq. entry */
		prot_id = (params->prof->segs[seg].hdrs & ICE_FLOW_SEG_HDR_IPV4) ?
				ICE_PROT_ICMP_IL : ICE_PROT_ICMPV6_IL;
		sib = fld == ICE_FLOW_FIELD_IDX_ICMP_TYPE ?
			ICE_FLOW_FIELD_IDX_ICMP_CODE :
			ICE_FLOW_FIELD_IDX_ICMP_TYPE;
		अवरोध;
	हाल ICE_FLOW_FIELD_IDX_GRE_KEYID:
		prot_id = ICE_PROT_GRE_OF;
		अवरोध;
	शेष:
		वापस ICE_ERR_NOT_IMPL;
	पूर्ण

	/* Each extraction sequence entry is a word in size, and extracts a
	 * word-aligned offset from a protocol header.
	 */
	ese_bits = ICE_FLOW_FV_EXTRACT_SZ * BITS_PER_BYTE;

	flds[fld].xtrct.prot_id = prot_id;
	flds[fld].xtrct.off = (ice_flds_info[fld].off / ese_bits) *
		ICE_FLOW_FV_EXTRACT_SZ;
	flds[fld].xtrct.disp = (u8)(ice_flds_info[fld].off % ese_bits);
	flds[fld].xtrct.idx = params->es_cnt;
	flds[fld].xtrct.mask = ice_flds_info[fld].mask;

	/* Adjust the next field-entry index after accommodating the number of
	 * entries this field consumes
	 */
	cnt = DIV_ROUND_UP(flds[fld].xtrct.disp + ice_flds_info[fld].size,
			   ese_bits);

	/* Fill in the extraction sequence entries needed क्रम this field */
	off = flds[fld].xtrct.off;
	mask = flds[fld].xtrct.mask;
	क्रम (i = 0; i < cnt; i++) अणु
		/* Only consume an extraction sequence entry अगर there is no
		 * sibling field associated with this field or the sibling entry
		 * alपढ़ोy extracts the word shared with this field.
		 */
		अगर (sib == ICE_FLOW_FIELD_IDX_MAX ||
		    flds[sib].xtrct.prot_id == ICE_PROT_ID_INVAL ||
		    flds[sib].xtrct.off != off) अणु
			u8 idx;

			/* Make sure the number of extraction sequence required
			 * करोes not exceed the block's capability
			 */
			अगर (params->es_cnt >= fv_words)
				वापस ICE_ERR_MAX_LIMIT;

			/* some blocks require a reversed field vector layout */
			अगर (hw->blk[params->blk].es.reverse)
				idx = fv_words - params->es_cnt - 1;
			अन्यथा
				idx = params->es_cnt;

			params->es[idx].prot_id = prot_id;
			params->es[idx].off = off;
			params->mask[idx] = mask | sib_mask;
			params->es_cnt++;
		पूर्ण

		off += ICE_FLOW_FV_EXTRACT_SZ;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_flow_xtract_raws - Create extract sequence entries क्रम raw bytes
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @params: inक्रमmation about the flow to be processed
 * @seg: index of packet segment whose raw fields are to be extracted
 */
अटल क्रमागत ice_status
ice_flow_xtract_raws(काष्ठा ice_hw *hw, काष्ठा ice_flow_prof_params *params,
		     u8 seg)
अणु
	u16 fv_words;
	u16 hdrs_sz;
	u8 i;

	अगर (!params->prof->segs[seg].raws_cnt)
		वापस 0;

	अगर (params->prof->segs[seg].raws_cnt >
	    ARRAY_SIZE(params->prof->segs[seg].raws))
		वापस ICE_ERR_MAX_LIMIT;

	/* Offsets within the segment headers are not supported */
	hdrs_sz = ice_flow_calc_seg_sz(params, seg);
	अगर (!hdrs_sz)
		वापस ICE_ERR_PARAM;

	fv_words = hw->blk[params->blk].es.fvw;

	क्रम (i = 0; i < params->prof->segs[seg].raws_cnt; i++) अणु
		काष्ठा ice_flow_seg_fld_raw *raw;
		u16 off, cnt, j;

		raw = &params->prof->segs[seg].raws[i];

		/* Storing extraction inक्रमmation */
		raw->info.xtrct.prot_id = ICE_PROT_MAC_OF_OR_S;
		raw->info.xtrct.off = (raw->off / ICE_FLOW_FV_EXTRACT_SZ) *
			ICE_FLOW_FV_EXTRACT_SZ;
		raw->info.xtrct.disp = (raw->off % ICE_FLOW_FV_EXTRACT_SZ) *
			BITS_PER_BYTE;
		raw->info.xtrct.idx = params->es_cnt;

		/* Determine the number of field vector entries this raw field
		 * consumes.
		 */
		cnt = DIV_ROUND_UP(raw->info.xtrct.disp +
				   (raw->info.src.last * BITS_PER_BYTE),
				   (ICE_FLOW_FV_EXTRACT_SZ * BITS_PER_BYTE));
		off = raw->info.xtrct.off;
		क्रम (j = 0; j < cnt; j++) अणु
			u16 idx;

			/* Make sure the number of extraction sequence required
			 * करोes not exceed the block's capability
			 */
			अगर (params->es_cnt >= hw->blk[params->blk].es.count ||
			    params->es_cnt >= ICE_MAX_FV_WORDS)
				वापस ICE_ERR_MAX_LIMIT;

			/* some blocks require a reversed field vector layout */
			अगर (hw->blk[params->blk].es.reverse)
				idx = fv_words - params->es_cnt - 1;
			अन्यथा
				idx = params->es_cnt;

			params->es[idx].prot_id = raw->info.xtrct.prot_id;
			params->es[idx].off = off;
			params->es_cnt++;
			off += ICE_FLOW_FV_EXTRACT_SZ;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_flow_create_xtrct_seq - Create an extraction sequence क्रम given segments
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @params: inक्रमmation about the flow to be processed
 *
 * This function iterates through all matched fields in the given segments, and
 * creates an extraction sequence क्रम the fields.
 */
अटल क्रमागत ice_status
ice_flow_create_xtrct_seq(काष्ठा ice_hw *hw,
			  काष्ठा ice_flow_prof_params *params)
अणु
	काष्ठा ice_flow_prof *prof = params->prof;
	क्रमागत ice_status status = 0;
	u8 i;

	क्रम (i = 0; i < prof->segs_cnt; i++) अणु
		u64 match = params->prof->segs[i].match;
		क्रमागत ice_flow_field j;

		क्रम_each_set_bit(j, (अचिन्हित दीर्घ *)&match,
				 ICE_FLOW_FIELD_IDX_MAX) अणु
			status = ice_flow_xtract_fld(hw, params, i, j, match);
			अगर (status)
				वापस status;
			clear_bit(j, (अचिन्हित दीर्घ *)&match);
		पूर्ण

		/* Process raw matching bytes */
		status = ice_flow_xtract_raws(hw, params, i);
		अगर (status)
			वापस status;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_flow_proc_segs - process all packet segments associated with a profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @params: inक्रमmation about the flow to be processed
 */
अटल क्रमागत ice_status
ice_flow_proc_segs(काष्ठा ice_hw *hw, काष्ठा ice_flow_prof_params *params)
अणु
	क्रमागत ice_status status;

	status = ice_flow_proc_seg_hdrs(params);
	अगर (status)
		वापस status;

	status = ice_flow_create_xtrct_seq(hw, params);
	अगर (status)
		वापस status;

	चयन (params->blk) अणु
	हाल ICE_BLK_FD:
	हाल ICE_BLK_RSS:
		status = 0;
		अवरोध;
	शेष:
		वापस ICE_ERR_NOT_IMPL;
	पूर्ण

	वापस status;
पूर्ण

#घोषणा ICE_FLOW_FIND_PROF_CHK_FLDS	0x00000001
#घोषणा ICE_FLOW_FIND_PROF_CHK_VSI	0x00000002
#घोषणा ICE_FLOW_FIND_PROF_NOT_CHK_सूची	0x00000004

/**
 * ice_flow_find_prof_conds - Find a profile matching headers and conditions
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: classअगरication stage
 * @dir: flow direction
 * @segs: array of one or more packet segments that describe the flow
 * @segs_cnt: number of packet segments provided
 * @vsi_handle: software VSI handle to check VSI (ICE_FLOW_FIND_PROF_CHK_VSI)
 * @conds: additional conditions to be checked (ICE_FLOW_FIND_PROF_CHK_*)
 */
अटल काष्ठा ice_flow_prof *
ice_flow_find_prof_conds(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
			 क्रमागत ice_flow_dir dir, काष्ठा ice_flow_seg_info *segs,
			 u8 segs_cnt, u16 vsi_handle, u32 conds)
अणु
	काष्ठा ice_flow_prof *p, *prof = शून्य;

	mutex_lock(&hw->fl_profs_locks[blk]);
	list_क्रम_each_entry(p, &hw->fl_profs[blk], l_entry)
		अगर ((p->dir == dir || conds & ICE_FLOW_FIND_PROF_NOT_CHK_सूची) &&
		    segs_cnt && segs_cnt == p->segs_cnt) अणु
			u8 i;

			/* Check क्रम profile-VSI association अगर specअगरied */
			अगर ((conds & ICE_FLOW_FIND_PROF_CHK_VSI) &&
			    ice_is_vsi_valid(hw, vsi_handle) &&
			    !test_bit(vsi_handle, p->vsis))
				जारी;

			/* Protocol headers must be checked. Matched fields are
			 * checked अगर specअगरied.
			 */
			क्रम (i = 0; i < segs_cnt; i++)
				अगर (segs[i].hdrs != p->segs[i].hdrs ||
				    ((conds & ICE_FLOW_FIND_PROF_CHK_FLDS) &&
				     segs[i].match != p->segs[i].match))
					अवरोध;

			/* A match is found अगर all segments are matched */
			अगर (i == segs_cnt) अणु
				prof = p;
				अवरोध;
			पूर्ण
		पूर्ण
	mutex_unlock(&hw->fl_profs_locks[blk]);

	वापस prof;
पूर्ण

/**
 * ice_flow_find_prof_id - Look up a profile with given profile ID
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: classअगरication stage
 * @prof_id: unique ID to identअगरy this flow profile
 */
अटल काष्ठा ice_flow_prof *
ice_flow_find_prof_id(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 prof_id)
अणु
	काष्ठा ice_flow_prof *p;

	list_क्रम_each_entry(p, &hw->fl_profs[blk], l_entry)
		अगर (p->id == prof_id)
			वापस p;

	वापस शून्य;
पूर्ण

/**
 * ice_dealloc_flow_entry - Deallocate flow entry memory
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @entry: flow entry to be हटाओd
 */
अटल व्योम
ice_dealloc_flow_entry(काष्ठा ice_hw *hw, काष्ठा ice_flow_entry *entry)
अणु
	अगर (!entry)
		वापस;

	अगर (entry->entry)
		devm_kमुक्त(ice_hw_to_dev(hw), entry->entry);

	devm_kमुक्त(ice_hw_to_dev(hw), entry);
पूर्ण

/**
 * ice_flow_rem_entry_sync - Remove a flow entry
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: classअगरication stage
 * @entry: flow entry to be हटाओd
 */
अटल क्रमागत ice_status
ice_flow_rem_entry_sync(काष्ठा ice_hw *hw, क्रमागत ice_block __always_unused blk,
			काष्ठा ice_flow_entry *entry)
अणु
	अगर (!entry)
		वापस ICE_ERR_BAD_PTR;

	list_del(&entry->l_entry);

	ice_dealloc_flow_entry(hw, entry);

	वापस 0;
पूर्ण

/**
 * ice_flow_add_prof_sync - Add a flow profile क्रम packet segments and fields
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: classअगरication stage
 * @dir: flow direction
 * @prof_id: unique ID to identअगरy this flow profile
 * @segs: array of one or more packet segments that describe the flow
 * @segs_cnt: number of packet segments provided
 * @prof: stores the वापसed flow profile added
 *
 * Assumption: the caller has acquired the lock to the profile list
 */
अटल क्रमागत ice_status
ice_flow_add_prof_sync(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		       क्रमागत ice_flow_dir dir, u64 prof_id,
		       काष्ठा ice_flow_seg_info *segs, u8 segs_cnt,
		       काष्ठा ice_flow_prof **prof)
अणु
	काष्ठा ice_flow_prof_params *params;
	क्रमागत ice_status status;
	u8 i;

	अगर (!prof)
		वापस ICE_ERR_BAD_PTR;

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (!params)
		वापस ICE_ERR_NO_MEMORY;

	params->prof = devm_kzalloc(ice_hw_to_dev(hw), माप(*params->prof),
				    GFP_KERNEL);
	अगर (!params->prof) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ मुक्त_params;
	पूर्ण

	/* initialize extraction sequence to all invalid (0xff) */
	क्रम (i = 0; i < ICE_MAX_FV_WORDS; i++) अणु
		params->es[i].prot_id = ICE_PROT_INVALID;
		params->es[i].off = ICE_FV_OFFSET_INVAL;
	पूर्ण

	params->blk = blk;
	params->prof->id = prof_id;
	params->prof->dir = dir;
	params->prof->segs_cnt = segs_cnt;

	/* Make a copy of the segments that need to be persistent in the flow
	 * profile instance
	 */
	क्रम (i = 0; i < segs_cnt; i++)
		स_नकल(&params->prof->segs[i], &segs[i], माप(*segs));

	status = ice_flow_proc_segs(hw, params);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_FLOW, "Error processing a flow's packet segments\n");
		जाओ out;
	पूर्ण

	/* Add a HW profile क्रम this flow profile */
	status = ice_add_prof(hw, blk, prof_id, (u8 *)params->ptypes,
			      params->attr, params->attr_cnt, params->es,
			      params->mask);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_FLOW, "Error adding a HW flow profile\n");
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&params->prof->entries);
	mutex_init(&params->prof->entries_lock);
	*prof = params->prof;

out:
	अगर (status)
		devm_kमुक्त(ice_hw_to_dev(hw), params->prof);
मुक्त_params:
	kमुक्त(params);

	वापस status;
पूर्ण

/**
 * ice_flow_rem_prof_sync - हटाओ a flow profile
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: classअगरication stage
 * @prof: poपूर्णांकer to flow profile to हटाओ
 *
 * Assumption: the caller has acquired the lock to the profile list
 */
अटल क्रमागत ice_status
ice_flow_rem_prof_sync(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		       काष्ठा ice_flow_prof *prof)
अणु
	क्रमागत ice_status status;

	/* Remove all reमुख्यing flow entries beक्रमe removing the flow profile */
	अगर (!list_empty(&prof->entries)) अणु
		काष्ठा ice_flow_entry *e, *t;

		mutex_lock(&prof->entries_lock);

		list_क्रम_each_entry_safe(e, t, &prof->entries, l_entry) अणु
			status = ice_flow_rem_entry_sync(hw, blk, e);
			अगर (status)
				अवरोध;
		पूर्ण

		mutex_unlock(&prof->entries_lock);
	पूर्ण

	/* Remove all hardware profiles associated with this flow profile */
	status = ice_rem_prof(hw, blk, prof->id);
	अगर (!status) अणु
		list_del(&prof->l_entry);
		mutex_destroy(&prof->entries_lock);
		devm_kमुक्त(ice_hw_to_dev(hw), prof);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_flow_assoc_prof - associate a VSI with a flow profile
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: classअगरication stage
 * @prof: poपूर्णांकer to flow profile
 * @vsi_handle: software VSI handle
 *
 * Assumption: the caller has acquired the lock to the profile list
 * and the software VSI handle has been validated
 */
अटल क्रमागत ice_status
ice_flow_assoc_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		    काष्ठा ice_flow_prof *prof, u16 vsi_handle)
अणु
	क्रमागत ice_status status = 0;

	अगर (!test_bit(vsi_handle, prof->vsis)) अणु
		status = ice_add_prof_id_flow(hw, blk,
					      ice_get_hw_vsi_num(hw,
								 vsi_handle),
					      prof->id);
		अगर (!status)
			set_bit(vsi_handle, prof->vsis);
		अन्यथा
			ice_debug(hw, ICE_DBG_FLOW, "HW profile add failed, %d\n",
				  status);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_flow_disassoc_prof - disassociate a VSI from a flow profile
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: classअगरication stage
 * @prof: poपूर्णांकer to flow profile
 * @vsi_handle: software VSI handle
 *
 * Assumption: the caller has acquired the lock to the profile list
 * and the software VSI handle has been validated
 */
अटल क्रमागत ice_status
ice_flow_disassoc_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		       काष्ठा ice_flow_prof *prof, u16 vsi_handle)
अणु
	क्रमागत ice_status status = 0;

	अगर (test_bit(vsi_handle, prof->vsis)) अणु
		status = ice_rem_prof_id_flow(hw, blk,
					      ice_get_hw_vsi_num(hw,
								 vsi_handle),
					      prof->id);
		अगर (!status)
			clear_bit(vsi_handle, prof->vsis);
		अन्यथा
			ice_debug(hw, ICE_DBG_FLOW, "HW profile remove failed, %d\n",
				  status);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_flow_add_prof - Add a flow profile क्रम packet segments and matched fields
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: classअगरication stage
 * @dir: flow direction
 * @prof_id: unique ID to identअगरy this flow profile
 * @segs: array of one or more packet segments that describe the flow
 * @segs_cnt: number of packet segments provided
 * @prof: stores the वापसed flow profile added
 */
क्रमागत ice_status
ice_flow_add_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, क्रमागत ice_flow_dir dir,
		  u64 prof_id, काष्ठा ice_flow_seg_info *segs, u8 segs_cnt,
		  काष्ठा ice_flow_prof **prof)
अणु
	क्रमागत ice_status status;

	अगर (segs_cnt > ICE_FLOW_SEG_MAX)
		वापस ICE_ERR_MAX_LIMIT;

	अगर (!segs_cnt)
		वापस ICE_ERR_PARAM;

	अगर (!segs)
		वापस ICE_ERR_BAD_PTR;

	status = ice_flow_val_hdrs(segs, segs_cnt);
	अगर (status)
		वापस status;

	mutex_lock(&hw->fl_profs_locks[blk]);

	status = ice_flow_add_prof_sync(hw, blk, dir, prof_id, segs, segs_cnt,
					prof);
	अगर (!status)
		list_add(&(*prof)->l_entry, &hw->fl_profs[blk]);

	mutex_unlock(&hw->fl_profs_locks[blk]);

	वापस status;
पूर्ण

/**
 * ice_flow_rem_prof - Remove a flow profile and all entries associated with it
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block क्रम which the flow profile is to be हटाओd
 * @prof_id: unique ID of the flow profile to be हटाओd
 */
क्रमागत ice_status
ice_flow_rem_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 prof_id)
अणु
	काष्ठा ice_flow_prof *prof;
	क्रमागत ice_status status;

	mutex_lock(&hw->fl_profs_locks[blk]);

	prof = ice_flow_find_prof_id(hw, blk, prof_id);
	अगर (!prof) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ out;
	पूर्ण

	/* prof becomes invalid after the call */
	status = ice_flow_rem_prof_sync(hw, blk, prof);

out:
	mutex_unlock(&hw->fl_profs_locks[blk]);

	वापस status;
पूर्ण

/**
 * ice_flow_add_entry - Add a flow entry
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: classअगरication stage
 * @prof_id: ID of the profile to add a new flow entry to
 * @entry_id: unique ID to identअगरy this flow entry
 * @vsi_handle: software VSI handle क्रम the flow entry
 * @prio: priority of the flow entry
 * @data: poपूर्णांकer to a data buffer containing flow entry's match values/masks
 * @entry_h: poपूर्णांकer to buffer that receives the new flow entry's handle
 */
क्रमागत ice_status
ice_flow_add_entry(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 prof_id,
		   u64 entry_id, u16 vsi_handle, क्रमागत ice_flow_priority prio,
		   व्योम *data, u64 *entry_h)
अणु
	काष्ठा ice_flow_entry *e = शून्य;
	काष्ठा ice_flow_prof *prof;
	क्रमागत ice_status status;

	/* No flow entry data is expected क्रम RSS */
	अगर (!entry_h || (!data && blk != ICE_BLK_RSS))
		वापस ICE_ERR_BAD_PTR;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	mutex_lock(&hw->fl_profs_locks[blk]);

	prof = ice_flow_find_prof_id(hw, blk, prof_id);
	अगर (!prof) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
	पूर्ण अन्यथा अणु
		/* Allocate memory क्रम the entry being added and associate
		 * the VSI to the found flow profile
		 */
		e = devm_kzalloc(ice_hw_to_dev(hw), माप(*e), GFP_KERNEL);
		अगर (!e)
			status = ICE_ERR_NO_MEMORY;
		अन्यथा
			status = ice_flow_assoc_prof(hw, blk, prof, vsi_handle);
	पूर्ण

	mutex_unlock(&hw->fl_profs_locks[blk]);
	अगर (status)
		जाओ out;

	e->id = entry_id;
	e->vsi_handle = vsi_handle;
	e->prof = prof;
	e->priority = prio;

	चयन (blk) अणु
	हाल ICE_BLK_FD:
	हाल ICE_BLK_RSS:
		अवरोध;
	शेष:
		status = ICE_ERR_NOT_IMPL;
		जाओ out;
	पूर्ण

	mutex_lock(&prof->entries_lock);
	list_add(&e->l_entry, &prof->entries);
	mutex_unlock(&prof->entries_lock);

	*entry_h = ICE_FLOW_ENTRY_HNDL(e);

out:
	अगर (status && e) अणु
		अगर (e->entry)
			devm_kमुक्त(ice_hw_to_dev(hw), e->entry);
		devm_kमुक्त(ice_hw_to_dev(hw), e);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_flow_rem_entry - Remove a flow entry
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: classअगरication stage
 * @entry_h: handle to the flow entry to be हटाओd
 */
क्रमागत ice_status ice_flow_rem_entry(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
				   u64 entry_h)
अणु
	काष्ठा ice_flow_entry *entry;
	काष्ठा ice_flow_prof *prof;
	क्रमागत ice_status status = 0;

	अगर (entry_h == ICE_FLOW_ENTRY_HANDLE_INVAL)
		वापस ICE_ERR_PARAM;

	entry = ICE_FLOW_ENTRY_PTR(entry_h);

	/* Retain the poपूर्णांकer to the flow profile as the entry will be मुक्तd */
	prof = entry->prof;

	अगर (prof) अणु
		mutex_lock(&prof->entries_lock);
		status = ice_flow_rem_entry_sync(hw, blk, entry);
		mutex_unlock(&prof->entries_lock);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_flow_set_fld_ext - specअगरies locations of field from entry's input buffer
 * @seg: packet segment the field being set beदीर्घs to
 * @fld: field to be set
 * @field_type: type of the field
 * @val_loc: अगर not ICE_FLOW_FLD_OFF_INVAL, location of the value to match from
 *           entry's input buffer
 * @mask_loc: अगर not ICE_FLOW_FLD_OFF_INVAL, location of mask value from entry's
 *            input buffer
 * @last_loc: अगर not ICE_FLOW_FLD_OFF_INVAL, location of last/upper value from
 *            entry's input buffer
 *
 * This helper function stores inक्रमmation of a field being matched, including
 * the type of the field and the locations of the value to match, the mask, and
 * the upper-bound value in the start of the input buffer क्रम a flow entry.
 * This function should only be used क्रम fixed-size data काष्ठाures.
 *
 * This function also opportunistically determines the protocol headers to be
 * present based on the fields being set. Some fields cannot be used alone to
 * determine the protocol headers present. Someबार, fields क्रम particular
 * protocol headers are not matched. In those हालs, the protocol headers
 * must be explicitly set.
 */
अटल व्योम
ice_flow_set_fld_ext(काष्ठा ice_flow_seg_info *seg, क्रमागत ice_flow_field fld,
		     क्रमागत ice_flow_fld_match_type field_type, u16 val_loc,
		     u16 mask_loc, u16 last_loc)
अणु
	u64 bit = BIT_ULL(fld);

	seg->match |= bit;
	अगर (field_type == ICE_FLOW_FLD_TYPE_RANGE)
		seg->range |= bit;

	seg->fields[fld].type = field_type;
	seg->fields[fld].src.val = val_loc;
	seg->fields[fld].src.mask = mask_loc;
	seg->fields[fld].src.last = last_loc;

	ICE_FLOW_SET_HDRS(seg, ice_flds_info[fld].hdr);
पूर्ण

/**
 * ice_flow_set_fld - specअगरies locations of field from entry's input buffer
 * @seg: packet segment the field being set beदीर्घs to
 * @fld: field to be set
 * @val_loc: अगर not ICE_FLOW_FLD_OFF_INVAL, location of the value to match from
 *           entry's input buffer
 * @mask_loc: अगर not ICE_FLOW_FLD_OFF_INVAL, location of mask value from entry's
 *            input buffer
 * @last_loc: अगर not ICE_FLOW_FLD_OFF_INVAL, location of last/upper value from
 *            entry's input buffer
 * @range: indicate अगर field being matched is to be in a range
 *
 * This function specअगरies the locations, in the क्रमm of byte offsets from the
 * start of the input buffer क्रम a flow entry, from where the value to match,
 * the mask value, and upper value can be extracted. These locations are then
 * stored in the flow profile. When adding a flow entry associated with the
 * flow profile, these locations will be used to quickly extract the values and
 * create the content of a match entry. This function should only be used क्रम
 * fixed-size data काष्ठाures.
 */
व्योम
ice_flow_set_fld(काष्ठा ice_flow_seg_info *seg, क्रमागत ice_flow_field fld,
		 u16 val_loc, u16 mask_loc, u16 last_loc, bool range)
अणु
	क्रमागत ice_flow_fld_match_type t = range ?
		ICE_FLOW_FLD_TYPE_RANGE : ICE_FLOW_FLD_TYPE_REG;

	ice_flow_set_fld_ext(seg, fld, t, val_loc, mask_loc, last_loc);
पूर्ण

/**
 * ice_flow_add_fld_raw - sets locations of a raw field from entry's input buf
 * @seg: packet segment the field being set beदीर्घs to
 * @off: offset of the raw field from the beginning of the segment in bytes
 * @len: length of the raw pattern to be matched
 * @val_loc: location of the value to match from entry's input buffer
 * @mask_loc: location of mask value from entry's input buffer
 *
 * This function specअगरies the offset of the raw field to be match from the
 * beginning of the specअगरied packet segment, and the locations, in the क्रमm of
 * byte offsets from the start of the input buffer क्रम a flow entry, from where
 * the value to match and the mask value to be extracted. These locations are
 * then stored in the flow profile. When adding flow entries to the associated
 * flow profile, these locations can be used to quickly extract the values to
 * create the content of a match entry. This function should only be used क्रम
 * fixed-size data काष्ठाures.
 */
व्योम
ice_flow_add_fld_raw(काष्ठा ice_flow_seg_info *seg, u16 off, u8 len,
		     u16 val_loc, u16 mask_loc)
अणु
	अगर (seg->raws_cnt < ICE_FLOW_SEG_RAW_FLD_MAX) अणु
		seg->raws[seg->raws_cnt].off = off;
		seg->raws[seg->raws_cnt].info.type = ICE_FLOW_FLD_TYPE_SIZE;
		seg->raws[seg->raws_cnt].info.src.val = val_loc;
		seg->raws[seg->raws_cnt].info.src.mask = mask_loc;
		/* The "last" field is used to store the length of the field */
		seg->raws[seg->raws_cnt].info.src.last = len;
	पूर्ण

	/* Overflows of "raws" will be handled as an error condition later in
	 * the flow when this inक्रमmation is processed.
	 */
	seg->raws_cnt++;
पूर्ण

#घोषणा ICE_FLOW_RSS_SEG_HDR_L2_MASKS \
	(ICE_FLOW_SEG_HDR_ETH | ICE_FLOW_SEG_HDR_VLAN)

#घोषणा ICE_FLOW_RSS_SEG_HDR_L3_MASKS \
	(ICE_FLOW_SEG_HDR_IPV4 | ICE_FLOW_SEG_HDR_IPV6)

#घोषणा ICE_FLOW_RSS_SEG_HDR_L4_MASKS \
	(ICE_FLOW_SEG_HDR_TCP | ICE_FLOW_SEG_HDR_UDP | ICE_FLOW_SEG_HDR_SCTP)

#घोषणा ICE_FLOW_RSS_SEG_HDR_VAL_MASKS \
	(ICE_FLOW_RSS_SEG_HDR_L2_MASKS | \
	 ICE_FLOW_RSS_SEG_HDR_L3_MASKS | \
	 ICE_FLOW_RSS_SEG_HDR_L4_MASKS)

/**
 * ice_flow_set_rss_seg_info - setup packet segments क्रम RSS
 * @segs: poपूर्णांकer to the flow field segment(s)
 * @hash_fields: fields to be hashed on क्रम the segment(s)
 * @flow_hdr: protocol header fields within a packet segment
 *
 * Helper function to extract fields from hash biपंचांगap and use flow
 * header value to set flow field segment क्रम further use in flow
 * profile entry or removal.
 */
अटल क्रमागत ice_status
ice_flow_set_rss_seg_info(काष्ठा ice_flow_seg_info *segs, u64 hash_fields,
			  u32 flow_hdr)
अणु
	u64 val;
	u8 i;

	क्रम_each_set_bit(i, (अचिन्हित दीर्घ *)&hash_fields,
			 ICE_FLOW_FIELD_IDX_MAX)
		ice_flow_set_fld(segs, (क्रमागत ice_flow_field)i,
				 ICE_FLOW_FLD_OFF_INVAL, ICE_FLOW_FLD_OFF_INVAL,
				 ICE_FLOW_FLD_OFF_INVAL, false);

	ICE_FLOW_SET_HDRS(segs, flow_hdr);

	अगर (segs->hdrs & ~ICE_FLOW_RSS_SEG_HDR_VAL_MASKS &
	    ~ICE_FLOW_RSS_HDRS_INNER_MASK & ~ICE_FLOW_SEG_HDR_IPV_OTHER)
		वापस ICE_ERR_PARAM;

	val = (u64)(segs->hdrs & ICE_FLOW_RSS_SEG_HDR_L3_MASKS);
	अगर (val && !is_घातer_of_2(val))
		वापस ICE_ERR_CFG;

	val = (u64)(segs->hdrs & ICE_FLOW_RSS_SEG_HDR_L4_MASKS);
	अगर (val && !is_घातer_of_2(val))
		वापस ICE_ERR_CFG;

	वापस 0;
पूर्ण

/**
 * ice_rem_vsi_rss_list - हटाओ VSI from RSS list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 *
 * Remove the VSI from all RSS configurations in the list.
 */
व्योम ice_rem_vsi_rss_list(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	काष्ठा ice_rss_cfg *r, *पंचांगp;

	अगर (list_empty(&hw->rss_list_head))
		वापस;

	mutex_lock(&hw->rss_locks);
	list_क्रम_each_entry_safe(r, पंचांगp, &hw->rss_list_head, l_entry)
		अगर (test_and_clear_bit(vsi_handle, r->vsis))
			अगर (biपंचांगap_empty(r->vsis, ICE_MAX_VSI)) अणु
				list_del(&r->l_entry);
				devm_kमुक्त(ice_hw_to_dev(hw), r);
			पूर्ण
	mutex_unlock(&hw->rss_locks);
पूर्ण

/**
 * ice_rem_vsi_rss_cfg - हटाओ RSS configurations associated with VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 *
 * This function will iterate through all flow profiles and disassociate
 * the VSI from that profile. If the flow profile has no VSIs it will
 * be हटाओd.
 */
क्रमागत ice_status ice_rem_vsi_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	स्थिर क्रमागत ice_block blk = ICE_BLK_RSS;
	काष्ठा ice_flow_prof *p, *t;
	क्रमागत ice_status status = 0;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	अगर (list_empty(&hw->fl_profs[blk]))
		वापस 0;

	mutex_lock(&hw->rss_locks);
	list_क्रम_each_entry_safe(p, t, &hw->fl_profs[blk], l_entry)
		अगर (test_bit(vsi_handle, p->vsis)) अणु
			status = ice_flow_disassoc_prof(hw, blk, p, vsi_handle);
			अगर (status)
				अवरोध;

			अगर (biपंचांगap_empty(p->vsis, ICE_MAX_VSI)) अणु
				status = ice_flow_rem_prof(hw, blk, p->id);
				अगर (status)
					अवरोध;
			पूर्ण
		पूर्ण
	mutex_unlock(&hw->rss_locks);

	वापस status;
पूर्ण

/**
 * ice_rem_rss_list - हटाओ RSS configuration from list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @prof: poपूर्णांकer to flow profile
 *
 * Assumption: lock has alपढ़ोy been acquired क्रम RSS list
 */
अटल व्योम
ice_rem_rss_list(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_flow_prof *prof)
अणु
	काष्ठा ice_rss_cfg *r, *पंचांगp;

	/* Search क्रम RSS hash fields associated to the VSI that match the
	 * hash configurations associated to the flow profile. If found
	 * हटाओ from the RSS entry list of the VSI context and delete entry.
	 */
	list_क्रम_each_entry_safe(r, पंचांगp, &hw->rss_list_head, l_entry)
		अगर (r->hashed_flds == prof->segs[prof->segs_cnt - 1].match &&
		    r->packet_hdr == prof->segs[prof->segs_cnt - 1].hdrs) अणु
			clear_bit(vsi_handle, r->vsis);
			अगर (biपंचांगap_empty(r->vsis, ICE_MAX_VSI)) अणु
				list_del(&r->l_entry);
				devm_kमुक्त(ice_hw_to_dev(hw), r);
			पूर्ण
			वापस;
		पूर्ण
पूर्ण

/**
 * ice_add_rss_list - add RSS configuration to list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @prof: poपूर्णांकer to flow profile
 *
 * Assumption: lock has alपढ़ोy been acquired क्रम RSS list
 */
अटल क्रमागत ice_status
ice_add_rss_list(काष्ठा ice_hw *hw, u16 vsi_handle, काष्ठा ice_flow_prof *prof)
अणु
	काष्ठा ice_rss_cfg *r, *rss_cfg;

	list_क्रम_each_entry(r, &hw->rss_list_head, l_entry)
		अगर (r->hashed_flds == prof->segs[prof->segs_cnt - 1].match &&
		    r->packet_hdr == prof->segs[prof->segs_cnt - 1].hdrs) अणु
			set_bit(vsi_handle, r->vsis);
			वापस 0;
		पूर्ण

	rss_cfg = devm_kzalloc(ice_hw_to_dev(hw), माप(*rss_cfg),
			       GFP_KERNEL);
	अगर (!rss_cfg)
		वापस ICE_ERR_NO_MEMORY;

	rss_cfg->hashed_flds = prof->segs[prof->segs_cnt - 1].match;
	rss_cfg->packet_hdr = prof->segs[prof->segs_cnt - 1].hdrs;
	set_bit(vsi_handle, rss_cfg->vsis);

	list_add_tail(&rss_cfg->l_entry, &hw->rss_list_head);

	वापस 0;
पूर्ण

#घोषणा ICE_FLOW_PROF_HASH_S	0
#घोषणा ICE_FLOW_PROF_HASH_M	(0xFFFFFFFFULL << ICE_FLOW_PROF_HASH_S)
#घोषणा ICE_FLOW_PROF_HDR_S	32
#घोषणा ICE_FLOW_PROF_HDR_M	(0x3FFFFFFFULL << ICE_FLOW_PROF_HDR_S)
#घोषणा ICE_FLOW_PROF_ENCAP_S	63
#घोषणा ICE_FLOW_PROF_ENCAP_M	(BIT_ULL(ICE_FLOW_PROF_ENCAP_S))

#घोषणा ICE_RSS_OUTER_HEADERS	1
#घोषणा ICE_RSS_INNER_HEADERS	2

/* Flow profile ID क्रमmat:
 * [0:31] - Packet match fields
 * [32:62] - Protocol header
 * [63] - Encapsulation flag, 0 अगर non-tunneled, 1 अगर tunneled
 */
#घोषणा ICE_FLOW_GEN_PROFID(hash, hdr, segs_cnt) \
	((u64)(((u64)(hash) & ICE_FLOW_PROF_HASH_M) | \
	       (((u64)(hdr) << ICE_FLOW_PROF_HDR_S) & ICE_FLOW_PROF_HDR_M) | \
	       ((u8)((segs_cnt) - 1) ? ICE_FLOW_PROF_ENCAP_M : 0)))

/**
 * ice_add_rss_cfg_sync - add an RSS configuration
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @hashed_flds: hash bit fields (ICE_FLOW_HASH_*) to configure
 * @addl_hdrs: protocol header fields
 * @segs_cnt: packet segment count
 *
 * Assumption: lock has alपढ़ोy been acquired क्रम RSS list
 */
अटल क्रमागत ice_status
ice_add_rss_cfg_sync(काष्ठा ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		     u32 addl_hdrs, u8 segs_cnt)
अणु
	स्थिर क्रमागत ice_block blk = ICE_BLK_RSS;
	काष्ठा ice_flow_prof *prof = शून्य;
	काष्ठा ice_flow_seg_info *segs;
	क्रमागत ice_status status;

	अगर (!segs_cnt || segs_cnt > ICE_FLOW_SEG_MAX)
		वापस ICE_ERR_PARAM;

	segs = kसुस्मृति(segs_cnt, माप(*segs), GFP_KERNEL);
	अगर (!segs)
		वापस ICE_ERR_NO_MEMORY;

	/* Conकाष्ठा the packet segment info from the hashed fields */
	status = ice_flow_set_rss_seg_info(&segs[segs_cnt - 1], hashed_flds,
					   addl_hdrs);
	अगर (status)
		जाओ निकास;

	/* Search क्रम a flow profile that has matching headers, hash fields
	 * and has the input VSI associated to it. If found, no further
	 * operations required and निकास.
	 */
	prof = ice_flow_find_prof_conds(hw, blk, ICE_FLOW_RX, segs, segs_cnt,
					vsi_handle,
					ICE_FLOW_FIND_PROF_CHK_FLDS |
					ICE_FLOW_FIND_PROF_CHK_VSI);
	अगर (prof)
		जाओ निकास;

	/* Check अगर a flow profile exists with the same protocol headers and
	 * associated with the input VSI. If so disassociate the VSI from
	 * this profile. The VSI will be added to a new profile created with
	 * the protocol header and new hash field configuration.
	 */
	prof = ice_flow_find_prof_conds(hw, blk, ICE_FLOW_RX, segs, segs_cnt,
					vsi_handle, ICE_FLOW_FIND_PROF_CHK_VSI);
	अगर (prof) अणु
		status = ice_flow_disassoc_prof(hw, blk, prof, vsi_handle);
		अगर (!status)
			ice_rem_rss_list(hw, vsi_handle, prof);
		अन्यथा
			जाओ निकास;

		/* Remove profile अगर it has no VSIs associated */
		अगर (biपंचांगap_empty(prof->vsis, ICE_MAX_VSI)) अणु
			status = ice_flow_rem_prof(hw, blk, prof->id);
			अगर (status)
				जाओ निकास;
		पूर्ण
	पूर्ण

	/* Search क्रम a profile that has same match fields only. If this
	 * exists then associate the VSI to this profile.
	 */
	prof = ice_flow_find_prof_conds(hw, blk, ICE_FLOW_RX, segs, segs_cnt,
					vsi_handle,
					ICE_FLOW_FIND_PROF_CHK_FLDS);
	अगर (prof) अणु
		status = ice_flow_assoc_prof(hw, blk, prof, vsi_handle);
		अगर (!status)
			status = ice_add_rss_list(hw, vsi_handle, prof);
		जाओ निकास;
	पूर्ण

	/* Create a new flow profile with generated profile and packet
	 * segment inक्रमmation.
	 */
	status = ice_flow_add_prof(hw, blk, ICE_FLOW_RX,
				   ICE_FLOW_GEN_PROFID(hashed_flds,
						       segs[segs_cnt - 1].hdrs,
						       segs_cnt),
				   segs, segs_cnt, &prof);
	अगर (status)
		जाओ निकास;

	status = ice_flow_assoc_prof(hw, blk, prof, vsi_handle);
	/* If association to a new flow profile failed then this profile can
	 * be हटाओd.
	 */
	अगर (status) अणु
		ice_flow_rem_prof(hw, blk, prof->id);
		जाओ निकास;
	पूर्ण

	status = ice_add_rss_list(hw, vsi_handle, prof);

निकास:
	kमुक्त(segs);
	वापस status;
पूर्ण

/**
 * ice_add_rss_cfg - add an RSS configuration with specअगरied hashed fields
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @hashed_flds: hash bit fields (ICE_FLOW_HASH_*) to configure
 * @addl_hdrs: protocol header fields
 *
 * This function will generate a flow profile based on fields associated with
 * the input fields to hash on, the flow type and use the VSI number to add
 * a flow entry to the profile.
 */
क्रमागत ice_status
ice_add_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		u32 addl_hdrs)
अणु
	क्रमागत ice_status status;

	अगर (hashed_flds == ICE_HASH_INVALID ||
	    !ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	mutex_lock(&hw->rss_locks);
	status = ice_add_rss_cfg_sync(hw, vsi_handle, hashed_flds, addl_hdrs,
				      ICE_RSS_OUTER_HEADERS);
	अगर (!status)
		status = ice_add_rss_cfg_sync(hw, vsi_handle, hashed_flds,
					      addl_hdrs, ICE_RSS_INNER_HEADERS);
	mutex_unlock(&hw->rss_locks);

	वापस status;
पूर्ण

/**
 * ice_rem_rss_cfg_sync - हटाओ an existing RSS configuration
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @hashed_flds: Packet hash types (ICE_FLOW_HASH_*) to हटाओ
 * @addl_hdrs: Protocol header fields within a packet segment
 * @segs_cnt: packet segment count
 *
 * Assumption: lock has alपढ़ोy been acquired क्रम RSS list
 */
अटल क्रमागत ice_status
ice_rem_rss_cfg_sync(काष्ठा ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		     u32 addl_hdrs, u8 segs_cnt)
अणु
	स्थिर क्रमागत ice_block blk = ICE_BLK_RSS;
	काष्ठा ice_flow_seg_info *segs;
	काष्ठा ice_flow_prof *prof;
	क्रमागत ice_status status;

	segs = kसुस्मृति(segs_cnt, माप(*segs), GFP_KERNEL);
	अगर (!segs)
		वापस ICE_ERR_NO_MEMORY;

	/* Conकाष्ठा the packet segment info from the hashed fields */
	status = ice_flow_set_rss_seg_info(&segs[segs_cnt - 1], hashed_flds,
					   addl_hdrs);
	अगर (status)
		जाओ out;

	prof = ice_flow_find_prof_conds(hw, blk, ICE_FLOW_RX, segs, segs_cnt,
					vsi_handle,
					ICE_FLOW_FIND_PROF_CHK_FLDS);
	अगर (!prof) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ out;
	पूर्ण

	status = ice_flow_disassoc_prof(hw, blk, prof, vsi_handle);
	अगर (status)
		जाओ out;

	/* Remove RSS configuration from VSI context beक्रमe deleting
	 * the flow profile.
	 */
	ice_rem_rss_list(hw, vsi_handle, prof);

	अगर (biपंचांगap_empty(prof->vsis, ICE_MAX_VSI))
		status = ice_flow_rem_prof(hw, blk, prof->id);

out:
	kमुक्त(segs);
	वापस status;
पूर्ण

/**
 * ice_rem_rss_cfg - हटाओ an existing RSS config with matching hashed fields
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @hashed_flds: Packet hash types (ICE_FLOW_HASH_*) to हटाओ
 * @addl_hdrs: Protocol header fields within a packet segment
 *
 * This function will lookup the flow profile based on the input
 * hash field biपंचांगap, iterate through the profile entry list of
 * that profile and find entry associated with input VSI to be
 * हटाओd. Calls are made to underlying flow s which will APIs
 * turn build or update buffers क्रम RSS XLT1 section.
 */
क्रमागत ice_status __maybe_unused
ice_rem_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u64 hashed_flds,
		u32 addl_hdrs)
अणु
	क्रमागत ice_status status;

	अगर (hashed_flds == ICE_HASH_INVALID ||
	    !ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	mutex_lock(&hw->rss_locks);
	status = ice_rem_rss_cfg_sync(hw, vsi_handle, hashed_flds, addl_hdrs,
				      ICE_RSS_OUTER_HEADERS);
	अगर (!status)
		status = ice_rem_rss_cfg_sync(hw, vsi_handle, hashed_flds,
					      addl_hdrs, ICE_RSS_INNER_HEADERS);
	mutex_unlock(&hw->rss_locks);

	वापस status;
पूर्ण

/* Mapping of AVF hash bit fields to an L3-L4 hash combination.
 * As the ice_flow_avf_hdr_field represent inभागidual bit shअगरts in a hash,
 * convert its values to their appropriate flow L3, L4 values.
 */
#घोषणा ICE_FLOW_AVF_RSS_IPV4_MASKS \
	(BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_OTHER) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_FRAG_IPV4))
#घोषणा ICE_FLOW_AVF_RSS_TCP_IPV4_MASKS \
	(BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_TCP_SYN_NO_ACK) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_TCP))
#घोषणा ICE_FLOW_AVF_RSS_UDP_IPV4_MASKS \
	(BIT_ULL(ICE_AVF_FLOW_FIELD_UNICAST_IPV4_UDP) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_MULTICAST_IPV4_UDP) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_UDP))
#घोषणा ICE_FLOW_AVF_RSS_ALL_IPV4_MASKS \
	(ICE_FLOW_AVF_RSS_TCP_IPV4_MASKS | ICE_FLOW_AVF_RSS_UDP_IPV4_MASKS | \
	 ICE_FLOW_AVF_RSS_IPV4_MASKS | BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_SCTP))

#घोषणा ICE_FLOW_AVF_RSS_IPV6_MASKS \
	(BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_OTHER) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_FRAG_IPV6))
#घोषणा ICE_FLOW_AVF_RSS_UDP_IPV6_MASKS \
	(BIT_ULL(ICE_AVF_FLOW_FIELD_UNICAST_IPV6_UDP) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_MULTICAST_IPV6_UDP) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_UDP))
#घोषणा ICE_FLOW_AVF_RSS_TCP_IPV6_MASKS \
	(BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_TCP_SYN_NO_ACK) | \
	 BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_TCP))
#घोषणा ICE_FLOW_AVF_RSS_ALL_IPV6_MASKS \
	(ICE_FLOW_AVF_RSS_TCP_IPV6_MASKS | ICE_FLOW_AVF_RSS_UDP_IPV6_MASKS | \
	 ICE_FLOW_AVF_RSS_IPV6_MASKS | BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_SCTP))

/**
 * ice_add_avf_rss_cfg - add an RSS configuration क्रम AVF driver
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @avf_hash: hash bit fields (ICE_AVF_FLOW_FIELD_*) to configure
 *
 * This function will take the hash biपंचांगap provided by the AVF driver via a
 * message, convert it to ICE-compatible values, and configure RSS flow
 * profiles.
 */
क्रमागत ice_status
ice_add_avf_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u64 avf_hash)
अणु
	क्रमागत ice_status status = 0;
	u64 hash_flds;

	अगर (avf_hash == ICE_AVF_FLOW_FIELD_INVALID ||
	    !ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	/* Make sure no unsupported bits are specअगरied */
	अगर (avf_hash & ~(ICE_FLOW_AVF_RSS_ALL_IPV4_MASKS |
			 ICE_FLOW_AVF_RSS_ALL_IPV6_MASKS))
		वापस ICE_ERR_CFG;

	hash_flds = avf_hash;

	/* Always create an L3 RSS configuration क्रम any L4 RSS configuration */
	अगर (hash_flds & ICE_FLOW_AVF_RSS_ALL_IPV4_MASKS)
		hash_flds |= ICE_FLOW_AVF_RSS_IPV4_MASKS;

	अगर (hash_flds & ICE_FLOW_AVF_RSS_ALL_IPV6_MASKS)
		hash_flds |= ICE_FLOW_AVF_RSS_IPV6_MASKS;

	/* Create the corresponding RSS configuration क्रम each valid hash bit */
	जबतक (hash_flds) अणु
		u64 rss_hash = ICE_HASH_INVALID;

		अगर (hash_flds & ICE_FLOW_AVF_RSS_ALL_IPV4_MASKS) अणु
			अगर (hash_flds & ICE_FLOW_AVF_RSS_IPV4_MASKS) अणु
				rss_hash = ICE_FLOW_HASH_IPV4;
				hash_flds &= ~ICE_FLOW_AVF_RSS_IPV4_MASKS;
			पूर्ण अन्यथा अगर (hash_flds &
				   ICE_FLOW_AVF_RSS_TCP_IPV4_MASKS) अणु
				rss_hash = ICE_FLOW_HASH_IPV4 |
					ICE_FLOW_HASH_TCP_PORT;
				hash_flds &= ~ICE_FLOW_AVF_RSS_TCP_IPV4_MASKS;
			पूर्ण अन्यथा अगर (hash_flds &
				   ICE_FLOW_AVF_RSS_UDP_IPV4_MASKS) अणु
				rss_hash = ICE_FLOW_HASH_IPV4 |
					ICE_FLOW_HASH_UDP_PORT;
				hash_flds &= ~ICE_FLOW_AVF_RSS_UDP_IPV4_MASKS;
			पूर्ण अन्यथा अगर (hash_flds &
				   BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_SCTP)) अणु
				rss_hash = ICE_FLOW_HASH_IPV4 |
					ICE_FLOW_HASH_SCTP_PORT;
				hash_flds &=
					~BIT_ULL(ICE_AVF_FLOW_FIELD_IPV4_SCTP);
			पूर्ण
		पूर्ण अन्यथा अगर (hash_flds & ICE_FLOW_AVF_RSS_ALL_IPV6_MASKS) अणु
			अगर (hash_flds & ICE_FLOW_AVF_RSS_IPV6_MASKS) अणु
				rss_hash = ICE_FLOW_HASH_IPV6;
				hash_flds &= ~ICE_FLOW_AVF_RSS_IPV6_MASKS;
			पूर्ण अन्यथा अगर (hash_flds &
				   ICE_FLOW_AVF_RSS_TCP_IPV6_MASKS) अणु
				rss_hash = ICE_FLOW_HASH_IPV6 |
					ICE_FLOW_HASH_TCP_PORT;
				hash_flds &= ~ICE_FLOW_AVF_RSS_TCP_IPV6_MASKS;
			पूर्ण अन्यथा अगर (hash_flds &
				   ICE_FLOW_AVF_RSS_UDP_IPV6_MASKS) अणु
				rss_hash = ICE_FLOW_HASH_IPV6 |
					ICE_FLOW_HASH_UDP_PORT;
				hash_flds &= ~ICE_FLOW_AVF_RSS_UDP_IPV6_MASKS;
			पूर्ण अन्यथा अगर (hash_flds &
				   BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_SCTP)) अणु
				rss_hash = ICE_FLOW_HASH_IPV6 |
					ICE_FLOW_HASH_SCTP_PORT;
				hash_flds &=
					~BIT_ULL(ICE_AVF_FLOW_FIELD_IPV6_SCTP);
			पूर्ण
		पूर्ण

		अगर (rss_hash == ICE_HASH_INVALID)
			वापस ICE_ERR_OUT_OF_RANGE;

		status = ice_add_rss_cfg(hw, vsi_handle, rss_hash,
					 ICE_FLOW_SEG_HDR_NONE);
		अगर (status)
			अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_replay_rss_cfg - replay RSS configurations associated with VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 */
क्रमागत ice_status ice_replay_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	क्रमागत ice_status status = 0;
	काष्ठा ice_rss_cfg *r;

	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;

	mutex_lock(&hw->rss_locks);
	list_क्रम_each_entry(r, &hw->rss_list_head, l_entry) अणु
		अगर (test_bit(vsi_handle, r->vsis)) अणु
			status = ice_add_rss_cfg_sync(hw, vsi_handle,
						      r->hashed_flds,
						      r->packet_hdr,
						      ICE_RSS_OUTER_HEADERS);
			अगर (status)
				अवरोध;
			status = ice_add_rss_cfg_sync(hw, vsi_handle,
						      r->hashed_flds,
						      r->packet_hdr,
						      ICE_RSS_INNER_HEADERS);
			अगर (status)
				अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&hw->rss_locks);

	वापस status;
पूर्ण

/**
 * ice_get_rss_cfg - वापसs hashed fields क्रम the given header types
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: software VSI handle
 * @hdrs: protocol header type
 *
 * This function will वापस the match fields of the first instance of flow
 * profile having the given header types and containing input VSI
 */
u64 ice_get_rss_cfg(काष्ठा ice_hw *hw, u16 vsi_handle, u32 hdrs)
अणु
	u64 rss_hash = ICE_HASH_INVALID;
	काष्ठा ice_rss_cfg *r;

	/* verअगरy अगर the protocol header is non zero and VSI is valid */
	अगर (hdrs == ICE_FLOW_SEG_HDR_NONE || !ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_HASH_INVALID;

	mutex_lock(&hw->rss_locks);
	list_क्रम_each_entry(r, &hw->rss_list_head, l_entry)
		अगर (test_bit(vsi_handle, r->vsis) &&
		    r->packet_hdr == hdrs) अणु
			rss_hash = r->hashed_flds;
			अवरोध;
		पूर्ण
	mutex_unlock(&hw->rss_locks);

	वापस rss_hash;
पूर्ण
