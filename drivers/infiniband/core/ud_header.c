<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Corporation.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/export.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>

#समावेश <rdma/ib_pack.h>

#घोषणा STRUCT_FIELD(header, field) \
	.काष्ठा_offset_bytes = दुरत्व(काष्ठा ib_unpacked_ ## header, field),      \
	.काष्ठा_size_bytes   = माप_field(काष्ठा ib_unpacked_ ## header, field), \
	.field_name          = #header ":" #field

अटल स्थिर काष्ठा ib_field lrh_table[]  = अणु
	अणु STRUCT_FIELD(lrh, भव_lane),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 4 पूर्ण,
	अणु STRUCT_FIELD(lrh, link_version),
	  .offset_words = 0,
	  .offset_bits  = 4,
	  .size_bits    = 4 पूर्ण,
	अणु STRUCT_FIELD(lrh, service_level),
	  .offset_words = 0,
	  .offset_bits  = 8,
	  .size_bits    = 4 पूर्ण,
	अणु RESERVED,
	  .offset_words = 0,
	  .offset_bits  = 12,
	  .size_bits    = 2 पूर्ण,
	अणु STRUCT_FIELD(lrh, link_next_header),
	  .offset_words = 0,
	  .offset_bits  = 14,
	  .size_bits    = 2 पूर्ण,
	अणु STRUCT_FIELD(lrh, destination_lid),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु RESERVED,
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 5 पूर्ण,
	अणु STRUCT_FIELD(lrh, packet_length),
	  .offset_words = 1,
	  .offset_bits  = 5,
	  .size_bits    = 11 पूर्ण,
	अणु STRUCT_FIELD(lrh, source_lid),
	  .offset_words = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ib_field eth_table[]  = अणु
	अणु STRUCT_FIELD(eth, dmac_h),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु STRUCT_FIELD(eth, dmac_l),
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(eth, smac_h),
	  .offset_words = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(eth, smac_l),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु STRUCT_FIELD(eth, type),
	  .offset_words = 3,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ib_field vlan_table[]  = अणु
	अणु STRUCT_FIELD(vlan, tag),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(vlan, type),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ib_field ip4_table[]  = अणु
	अणु STRUCT_FIELD(ip4, ver),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 4 पूर्ण,
	अणु STRUCT_FIELD(ip4, hdr_len),
	  .offset_words = 0,
	  .offset_bits  = 4,
	  .size_bits    = 4 पूर्ण,
	अणु STRUCT_FIELD(ip4, tos),
	  .offset_words = 0,
	  .offset_bits  = 8,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(ip4, tot_len),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(ip4, id),
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(ip4, frag_off),
	  .offset_words = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(ip4, ttl),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(ip4, protocol),
	  .offset_words = 2,
	  .offset_bits  = 8,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(ip4, check),
	  .offset_words = 2,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(ip4, saddr),
	  .offset_words = 3,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु STRUCT_FIELD(ip4, daddr),
	  .offset_words = 4,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ib_field udp_table[]  = अणु
	अणु STRUCT_FIELD(udp, sport),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(udp, dport),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(udp, length),
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(udp, csum),
	  .offset_words = 1,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ib_field grh_table[]  = अणु
	अणु STRUCT_FIELD(grh, ip_version),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 4 पूर्ण,
	अणु STRUCT_FIELD(grh, traffic_class),
	  .offset_words = 0,
	  .offset_bits  = 4,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(grh, flow_label),
	  .offset_words = 0,
	  .offset_bits  = 12,
	  .size_bits    = 20 पूर्ण,
	अणु STRUCT_FIELD(grh, payload_length),
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 16 पूर्ण,
	अणु STRUCT_FIELD(grh, next_header),
	  .offset_words = 1,
	  .offset_bits  = 16,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(grh, hop_limit),
	  .offset_words = 1,
	  .offset_bits  = 24,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(grh, source_gid),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण,
	अणु STRUCT_FIELD(grh, destination_gid),
	  .offset_words = 6,
	  .offset_bits  = 0,
	  .size_bits    = 128 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ib_field bth_table[]  = अणु
	अणु STRUCT_FIELD(bth, opcode),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(bth, solicited_event),
	  .offset_words = 0,
	  .offset_bits  = 8,
	  .size_bits    = 1 पूर्ण,
	अणु STRUCT_FIELD(bth, mig_req),
	  .offset_words = 0,
	  .offset_bits  = 9,
	  .size_bits    = 1 पूर्ण,
	अणु STRUCT_FIELD(bth, pad_count),
	  .offset_words = 0,
	  .offset_bits  = 10,
	  .size_bits    = 2 पूर्ण,
	अणु STRUCT_FIELD(bth, transport_header_version),
	  .offset_words = 0,
	  .offset_bits  = 12,
	  .size_bits    = 4 पूर्ण,
	अणु STRUCT_FIELD(bth, pkey),
	  .offset_words = 0,
	  .offset_bits  = 16,
	  .size_bits    = 16 पूर्ण,
	अणु RESERVED,
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(bth, destination_qpn),
	  .offset_words = 1,
	  .offset_bits  = 8,
	  .size_bits    = 24 पूर्ण,
	अणु STRUCT_FIELD(bth, ack_req),
	  .offset_words = 2,
	  .offset_bits  = 0,
	  .size_bits    = 1 पूर्ण,
	अणु RESERVED,
	  .offset_words = 2,
	  .offset_bits  = 1,
	  .size_bits    = 7 पूर्ण,
	अणु STRUCT_FIELD(bth, psn),
	  .offset_words = 2,
	  .offset_bits  = 8,
	  .size_bits    = 24 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ib_field deth_table[] = अणु
	अणु STRUCT_FIELD(deth, qkey),
	  .offset_words = 0,
	  .offset_bits  = 0,
	  .size_bits    = 32 पूर्ण,
	अणु RESERVED,
	  .offset_words = 1,
	  .offset_bits  = 0,
	  .size_bits    = 8 पूर्ण,
	अणु STRUCT_FIELD(deth, source_qpn),
	  .offset_words = 1,
	  .offset_bits  = 8,
	  .size_bits    = 24 पूर्ण
पूर्ण;

__sum16 ib_ud_ip4_csum(काष्ठा ib_ud_header *header)
अणु
	काष्ठा iphdr iph;

	iph.ihl		= 5;
	iph.version	= 4;
	iph.tos		= header->ip4.tos;
	iph.tot_len	= header->ip4.tot_len;
	iph.id		= header->ip4.id;
	iph.frag_off	= header->ip4.frag_off;
	iph.ttl		= header->ip4.ttl;
	iph.protocol	= header->ip4.protocol;
	iph.check	= 0;
	iph.saddr	= header->ip4.saddr;
	iph.daddr	= header->ip4.daddr;

	वापस ip_fast_csum((u8 *)&iph, iph.ihl);
पूर्ण
EXPORT_SYMBOL(ib_ud_ip4_csum);

/**
 * ib_ud_header_init - Initialize UD header काष्ठाure
 * @payload_bytes:Length of packet payload
 * @lrh_present: specअगरy अगर LRH is present
 * @eth_present: specअगरy अगर Eth header is present
 * @vlan_present: packet is tagged vlan
 * @grh_present: GRH flag (अगर non-zero, GRH will be included)
 * @ip_version: अगर non-zero, IP header, V4 or V6, will be included
 * @udp_present :अगर non-zero, UDP header will be included
 * @immediate_present: specअगरy अगर immediate data is present
 * @header:Structure to initialize
 */
पूर्णांक ib_ud_header_init(पूर्णांक     payload_bytes,
		      पूर्णांक    lrh_present,
		      पूर्णांक    eth_present,
		      पूर्णांक    vlan_present,
		      पूर्णांक    grh_present,
		      पूर्णांक    ip_version,
		      पूर्णांक    udp_present,
		      पूर्णांक    immediate_present,
		      काष्ठा ib_ud_header *header)
अणु
	माप_प्रकार udp_bytes = udp_present ? IB_UDP_BYTES : 0;

	grh_present = grh_present && !ip_version;
	स_रखो(header, 0, माप *header);

	/*
	 * UDP header without IP header करोesn't make sense
	 */
	अगर (udp_present && ip_version != 4 && ip_version != 6)
		वापस -EINVAL;

	अगर (lrh_present) अणु
		u16 packet_length;

		header->lrh.link_version     = 0;
		header->lrh.link_next_header =
			grh_present ? IB_LNH_IBA_GLOBAL : IB_LNH_IBA_LOCAL;
		packet_length = (IB_LRH_BYTES	+
				 IB_BTH_BYTES	+
				 IB_DETH_BYTES	+
				 (grh_present ? IB_GRH_BYTES : 0) +
				 payload_bytes	+
				 4		+ /* ICRC     */
				 3) / 4;	  /* round up */
		header->lrh.packet_length = cpu_to_be16(packet_length);
	पूर्ण

	अगर (vlan_present)
		header->eth.type = cpu_to_be16(ETH_P_8021Q);

	अगर (ip_version == 6 || grh_present) अणु
		header->grh.ip_version      = 6;
		header->grh.payload_length  =
			cpu_to_be16((udp_bytes        +
				     IB_BTH_BYTES     +
				     IB_DETH_BYTES    +
				     payload_bytes    +
				     4                + /* ICRC     */
				     3) & ~3);          /* round up */
		header->grh.next_header     = udp_present ? IPPROTO_UDP : 0x1b;
	पूर्ण

	अगर (ip_version == 4) अणु
		header->ip4.ver = 4; /* version 4 */
		header->ip4.hdr_len = 5; /* 5 words */
		header->ip4.tot_len =
			cpu_to_be16(IB_IP4_BYTES   +
				     udp_bytes     +
				     IB_BTH_BYTES  +
				     IB_DETH_BYTES +
				     payload_bytes +
				     4);     /* ICRC     */
		header->ip4.protocol = IPPROTO_UDP;
	पूर्ण
	अगर (udp_present && ip_version)
		header->udp.length =
			cpu_to_be16(IB_UDP_BYTES   +
				     IB_BTH_BYTES  +
				     IB_DETH_BYTES +
				     payload_bytes +
				     4);     /* ICRC     */

	अगर (immediate_present)
		header->bth.opcode           = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
	अन्यथा
		header->bth.opcode           = IB_OPCODE_UD_SEND_ONLY;
	header->bth.pad_count                = (4 - payload_bytes) & 3;
	header->bth.transport_header_version = 0;

	header->lrh_present = lrh_present;
	header->eth_present = eth_present;
	header->vlan_present = vlan_present;
	header->grh_present = grh_present || (ip_version == 6);
	header->ipv4_present = ip_version == 4;
	header->udp_present = udp_present;
	header->immediate_present = immediate_present;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_ud_header_init);

/**
 * ib_ud_header_pack - Pack UD header काष्ठा पूर्णांकo wire क्रमmat
 * @header:UD header काष्ठा
 * @buf:Buffer to pack पूर्णांकo
 *
 * ib_ud_header_pack() packs the UD header काष्ठाure @header पूर्णांकo wire
 * क्रमmat in the buffer @buf.
 */
पूर्णांक ib_ud_header_pack(काष्ठा ib_ud_header *header,
		      व्योम                *buf)
अणु
	पूर्णांक len = 0;

	अगर (header->lrh_present) अणु
		ib_pack(lrh_table, ARRAY_SIZE(lrh_table),
			&header->lrh, buf + len);
		len += IB_LRH_BYTES;
	पूर्ण
	अगर (header->eth_present) अणु
		ib_pack(eth_table, ARRAY_SIZE(eth_table),
			&header->eth, buf + len);
		len += IB_ETH_BYTES;
	पूर्ण
	अगर (header->vlan_present) अणु
		ib_pack(vlan_table, ARRAY_SIZE(vlan_table),
			&header->vlan, buf + len);
		len += IB_VLAN_BYTES;
	पूर्ण
	अगर (header->grh_present) अणु
		ib_pack(grh_table, ARRAY_SIZE(grh_table),
			&header->grh, buf + len);
		len += IB_GRH_BYTES;
	पूर्ण
	अगर (header->ipv4_present) अणु
		ib_pack(ip4_table, ARRAY_SIZE(ip4_table),
			&header->ip4, buf + len);
		len += IB_IP4_BYTES;
	पूर्ण
	अगर (header->udp_present) अणु
		ib_pack(udp_table, ARRAY_SIZE(udp_table),
			&header->udp, buf + len);
		len += IB_UDP_BYTES;
	पूर्ण

	ib_pack(bth_table, ARRAY_SIZE(bth_table),
		&header->bth, buf + len);
	len += IB_BTH_BYTES;

	ib_pack(deth_table, ARRAY_SIZE(deth_table),
		&header->deth, buf + len);
	len += IB_DETH_BYTES;

	अगर (header->immediate_present) अणु
		स_नकल(buf + len, &header->immediate_data, माप header->immediate_data);
		len += माप header->immediate_data;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL(ib_ud_header_pack);

/**
 * ib_ud_header_unpack - Unpack UD header काष्ठा from wire क्रमmat
 * @header:UD header काष्ठा
 * @buf:Buffer to pack पूर्णांकo
 *
 * ib_ud_header_pack() unpacks the UD header काष्ठाure @header from wire
 * क्रमmat in the buffer @buf.
 */
पूर्णांक ib_ud_header_unpack(व्योम                *buf,
			काष्ठा ib_ud_header *header)
अणु
	ib_unpack(lrh_table, ARRAY_SIZE(lrh_table),
		  buf, &header->lrh);
	buf += IB_LRH_BYTES;

	अगर (header->lrh.link_version != 0) अणु
		pr_warn("Invalid LRH.link_version %d\n",
			header->lrh.link_version);
		वापस -EINVAL;
	पूर्ण

	चयन (header->lrh.link_next_header) अणु
	हाल IB_LNH_IBA_LOCAL:
		header->grh_present = 0;
		अवरोध;

	हाल IB_LNH_IBA_GLOBAL:
		header->grh_present = 1;
		ib_unpack(grh_table, ARRAY_SIZE(grh_table),
			  buf, &header->grh);
		buf += IB_GRH_BYTES;

		अगर (header->grh.ip_version != 6) अणु
			pr_warn("Invalid GRH.ip_version %d\n",
				header->grh.ip_version);
			वापस -EINVAL;
		पूर्ण
		अगर (header->grh.next_header != 0x1b) अणु
			pr_warn("Invalid GRH.next_header 0x%02x\n",
				header->grh.next_header);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		pr_warn("Invalid LRH.link_next_header %d\n",
			header->lrh.link_next_header);
		वापस -EINVAL;
	पूर्ण

	ib_unpack(bth_table, ARRAY_SIZE(bth_table),
		  buf, &header->bth);
	buf += IB_BTH_BYTES;

	चयन (header->bth.opcode) अणु
	हाल IB_OPCODE_UD_SEND_ONLY:
		header->immediate_present = 0;
		अवरोध;
	हाल IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE:
		header->immediate_present = 1;
		अवरोध;
	शेष:
		pr_warn("Invalid BTH.opcode 0x%02x\n", header->bth.opcode);
		वापस -EINVAL;
	पूर्ण

	अगर (header->bth.transport_header_version != 0) अणु
		pr_warn("Invalid BTH.transport_header_version %d\n",
			header->bth.transport_header_version);
		वापस -EINVAL;
	पूर्ण

	ib_unpack(deth_table, ARRAY_SIZE(deth_table),
		  buf, &header->deth);
	buf += IB_DETH_BYTES;

	अगर (header->immediate_present)
		स_नकल(&header->immediate_data, buf, माप header->immediate_data);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ib_ud_header_unpack);
