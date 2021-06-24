<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2016 Chelsio Communications, Inc. All rights reserved.
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

#अगर_अघोषित __CXGB4_TC_U32_PARSE_H
#घोषणा __CXGB4_TC_U32_PARSE_H

काष्ठा cxgb4_match_field अणु
	पूर्णांक off; /* Offset from the beginning of the header to match */
	/* Fill the value/mask pair in the spec अगर matched */
	पूर्णांक (*val)(काष्ठा ch_filter_specअगरication *f, __be32 val, __be32 mask);
पूर्ण;

/* IPv4 match fields */
अटल अंतरभूत पूर्णांक cxgb4_fill_ipv4_tos(काष्ठा ch_filter_specअगरication *f,
				      __be32 val, __be32 mask)
अणु
	f->val.tos  = (ntohl(val)  >> 16) & 0x000000FF;
	f->mask.tos = (ntohl(mask) >> 16) & 0x000000FF;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv4_frag(काष्ठा ch_filter_specअगरication *f,
				       __be32 val, __be32 mask)
अणु
	u32 mask_val;
	u8 frag_val;

	frag_val = (ntohl(val) >> 13) & 0x00000007;
	mask_val = ntohl(mask) & 0x0000FFFF;

	अगर (frag_val == 0x1 && mask_val != 0x3FFF) अणु /* MF set */
		f->val.frag = 1;
		f->mask.frag = 1;
	पूर्ण अन्यथा अगर (frag_val == 0x2 && mask_val != 0x3FFF) अणु /* DF set */
		f->val.frag = 0;
		f->mask.frag = 1;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv4_proto(काष्ठा ch_filter_specअगरication *f,
					__be32 val, __be32 mask)
अणु
	f->val.proto  = (ntohl(val)  >> 16) & 0x000000FF;
	f->mask.proto = (ntohl(mask) >> 16) & 0x000000FF;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv4_src_ip(काष्ठा ch_filter_specअगरication *f,
					 __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.fip[0],  &val,  माप(u32));
	स_नकल(&f->mask.fip[0], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv4_dst_ip(काष्ठा ch_filter_specअगरication *f,
					 __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.lip[0],  &val,  माप(u32));
	स_नकल(&f->mask.lip[0], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cxgb4_match_field cxgb4_ipv4_fields[] = अणु
	अणु .off = 0,  .val = cxgb4_fill_ipv4_tos पूर्ण,
	अणु .off = 4,  .val = cxgb4_fill_ipv4_frag पूर्ण,
	अणु .off = 8,  .val = cxgb4_fill_ipv4_proto पूर्ण,
	अणु .off = 12, .val = cxgb4_fill_ipv4_src_ip पूर्ण,
	अणु .off = 16, .val = cxgb4_fill_ipv4_dst_ip पूर्ण,
	अणु .val = शून्य पूर्ण
पूर्ण;

/* IPv6 match fields */
अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_tos(काष्ठा ch_filter_specअगरication *f,
				      __be32 val, __be32 mask)
अणु
	f->val.tos  = (ntohl(val)  >> 20) & 0x000000FF;
	f->mask.tos = (ntohl(mask) >> 20) & 0x000000FF;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_proto(काष्ठा ch_filter_specअगरication *f,
					__be32 val, __be32 mask)
अणु
	f->val.proto  = (ntohl(val)  >> 8) & 0x000000FF;
	f->mask.proto = (ntohl(mask) >> 8) & 0x000000FF;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_src_ip0(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.fip[0],  &val,  माप(u32));
	स_नकल(&f->mask.fip[0], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_src_ip1(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.fip[4],  &val,  माप(u32));
	स_नकल(&f->mask.fip[4], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_src_ip2(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.fip[8],  &val,  माप(u32));
	स_नकल(&f->mask.fip[8], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_src_ip3(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.fip[12],  &val,  माप(u32));
	स_नकल(&f->mask.fip[12], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_dst_ip0(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.lip[0],  &val,  माप(u32));
	स_नकल(&f->mask.lip[0], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_dst_ip1(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.lip[4],  &val,  माप(u32));
	स_नकल(&f->mask.lip[4], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_dst_ip2(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.lip[8],  &val,  माप(u32));
	स_नकल(&f->mask.lip[8], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cxgb4_fill_ipv6_dst_ip3(काष्ठा ch_filter_specअगरication *f,
					  __be32 val, __be32 mask)
अणु
	स_नकल(&f->val.lip[12],  &val,  माप(u32));
	स_नकल(&f->mask.lip[12], &mask, माप(u32));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cxgb4_match_field cxgb4_ipv6_fields[] = अणु
	अणु .off = 0,  .val = cxgb4_fill_ipv6_tos पूर्ण,
	अणु .off = 4,  .val = cxgb4_fill_ipv6_proto पूर्ण,
	अणु .off = 8,  .val = cxgb4_fill_ipv6_src_ip0 पूर्ण,
	अणु .off = 12, .val = cxgb4_fill_ipv6_src_ip1 पूर्ण,
	अणु .off = 16, .val = cxgb4_fill_ipv6_src_ip2 पूर्ण,
	अणु .off = 20, .val = cxgb4_fill_ipv6_src_ip3 पूर्ण,
	अणु .off = 24, .val = cxgb4_fill_ipv6_dst_ip0 पूर्ण,
	अणु .off = 28, .val = cxgb4_fill_ipv6_dst_ip1 पूर्ण,
	अणु .off = 32, .val = cxgb4_fill_ipv6_dst_ip2 पूर्ण,
	अणु .off = 36, .val = cxgb4_fill_ipv6_dst_ip3 पूर्ण,
	अणु .val = शून्य पूर्ण
पूर्ण;

/* TCP/UDP match */
अटल अंतरभूत पूर्णांक cxgb4_fill_l4_ports(काष्ठा ch_filter_specअगरication *f,
				      __be32 val, __be32 mask)
अणु
	f->val.fport  = ntohl(val)  >> 16;
	f->mask.fport = ntohl(mask) >> 16;
	f->val.lport  = ntohl(val)  & 0x0000FFFF;
	f->mask.lport = ntohl(mask) & 0x0000FFFF;

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा cxgb4_match_field cxgb4_tcp_fields[] = अणु
	अणु .off = 0, .val = cxgb4_fill_l4_ports पूर्ण,
	अणु .val = शून्य पूर्ण
पूर्ण;

अटल स्थिर काष्ठा cxgb4_match_field cxgb4_udp_fields[] = अणु
	अणु .off = 0, .val = cxgb4_fill_l4_ports पूर्ण,
	अणु .val = शून्य पूर्ण
पूर्ण;

काष्ठा cxgb4_next_header अणु
	/* Offset, shअगरt, and mask added to beginning of the header
	 * to get to next header.  Useful when using a header
	 * field's value to jump to next header such as IHL field
	 * in IPv4 header.
	 */
	काष्ठा tc_u32_sel sel;
	काष्ठा tc_u32_key key;
	/* location of jump to make */
	स्थिर काष्ठा cxgb4_match_field *jump;
पूर्ण;

/* Accept a rule with a jump to transport layer header based on IHL field in
 * IPv4 header.
 */
अटल स्थिर काष्ठा cxgb4_next_header cxgb4_ipv4_jumps[] = अणु
	अणु
		/* TCP Jump */
		.sel = अणु
			.off = 0,
			.offoff = 0,
			.offshअगरt = 6,
			.offmask = cpu_to_be16(0x0f00),
		पूर्ण,
		.key = अणु
			.off = 8,
			.val = cpu_to_be32(0x00060000),
			.mask = cpu_to_be32(0x00ff0000),
		पूर्ण,
		.jump = cxgb4_tcp_fields,
	पूर्ण,
	अणु
		/* UDP Jump */
		.sel = अणु
			.off = 0,
			.offoff = 0,
			.offshअगरt = 6,
			.offmask = cpu_to_be16(0x0f00),
		पूर्ण,
		.key = अणु
			.off = 8,
			.val = cpu_to_be32(0x00110000),
			.mask = cpu_to_be32(0x00ff0000),
		पूर्ण,
		.jump = cxgb4_udp_fields,
	पूर्ण,
	अणु .jump = शून्य पूर्ण,
पूर्ण;

/* Accept a rule with a jump directly past the 40 Bytes of IPv6 fixed header
 * to get to transport layer header.
 */
अटल स्थिर काष्ठा cxgb4_next_header cxgb4_ipv6_jumps[] = अणु
	अणु
		/* TCP Jump */
		.sel = अणु
			.off = 40,
			.offoff = 0,
			.offshअगरt = 0,
			.offmask = 0,
		पूर्ण,
		.key = अणु
			.off = 4,
			.val = cpu_to_be32(0x00000600),
			.mask = cpu_to_be32(0x0000ff00),
		पूर्ण,
		.jump = cxgb4_tcp_fields,
	पूर्ण,
	अणु
		/* UDP Jump */
		.sel = अणु
			.off = 40,
			.offoff = 0,
			.offshअगरt = 0,
			.offmask = 0,
		पूर्ण,
		.key = अणु
			.off = 4,
			.val = cpu_to_be32(0x00001100),
			.mask = cpu_to_be32(0x0000ff00),
		पूर्ण,
		.jump = cxgb4_udp_fields,
	पूर्ण,
	अणु .jump = शून्य पूर्ण,
पूर्ण;

काष्ठा cxgb4_link अणु
	स्थिर काष्ठा cxgb4_match_field *match_field;  /* Next header */
	काष्ठा ch_filter_specअगरication fs; /* Match spec associated with link */
	u32 link_handle;         /* Knode handle associated with the link */
	अचिन्हित दीर्घ *tid_map;  /* Biपंचांगap क्रम filter tids */
पूर्ण;

काष्ठा cxgb4_tc_u32_table अणु
	अचिन्हित पूर्णांक size;          /* number of entries in table */
	काष्ठा cxgb4_link table[]; /* Jump table */
पूर्ण;
#पूर्ण_अगर /* __CXGB4_TC_U32_PARSE_H */
