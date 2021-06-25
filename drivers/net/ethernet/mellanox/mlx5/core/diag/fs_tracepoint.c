<शैली गुरु>
/*
 * Copyright (c) 2017, Mellanox Technologies. All rights reserved.
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

#घोषणा CREATE_TRACE_POINTS

#समावेश "fs_tracepoint.h"
#समावेश <linux/stringअगरy.h>

#घोषणा DECLARE_MASK_VAL(type, name) काष्ठा अणुtype m; type v; पूर्ण name
#घोषणा MASK_VAL(type, spec, name, mask, val, fld)	\
		DECLARE_MASK_VAL(type, name) =		\
			अणु.m = MLX5_GET(spec, mask, fld),\
			 .v = MLX5_GET(spec, val, fld)पूर्ण
#घोषणा MASK_VAL_BE(type, spec, name, mask, val, fld)	\
		    DECLARE_MASK_VAL(type, name) =	\
			अणु.m = MLX5_GET_BE(type, spec, mask, fld),\
			 .v = MLX5_GET_BE(type, spec, val, fld)पूर्ण
#घोषणा GET_MASKED_VAL(name) (name.m & name.v)

#घोषणा GET_MASK_VAL(name, type, mask, val, fld)	\
		(name.m = MLX5_GET(type, mask, fld),	\
		 name.v = MLX5_GET(type, val, fld),	\
		 name.m & name.v)
#घोषणा PRINT_MASKED_VAL(name, p, क्रमmat) अणु		\
	अगर (name.m)			\
		trace_seq_म_लिखो(p, __stringअगरy(name) "=" क्रमmat " ", name.v); \
	पूर्ण
#घोषणा PRINT_MASKED_VALP(name, cast, p, क्रमmat) अणु	\
	अगर (name.m)			\
		trace_seq_म_लिखो(p, __stringअगरy(name) "=" क्रमmat " ",	       \
				 (cast)&name.v);\
	पूर्ण

अटल व्योम prपूर्णांक_lyr_2_4_hdrs(काष्ठा trace_seq *p,
			       स्थिर u32 *mask, स्थिर u32 *value)
अणु
#घोषणा MASK_VAL_L2(type, name, fld) \
	MASK_VAL(type, fte_match_set_lyr_2_4, name, mask, value, fld)
	DECLARE_MASK_VAL(u64, smac) = अणु
		.m = MLX5_GET(fte_match_set_lyr_2_4, mask, smac_47_16) << 16 |
		     MLX5_GET(fte_match_set_lyr_2_4, mask, smac_15_0),
		.v = MLX5_GET(fte_match_set_lyr_2_4, value, smac_47_16) << 16 |
		     MLX5_GET(fte_match_set_lyr_2_4, value, smac_15_0)पूर्ण;
	DECLARE_MASK_VAL(u64, dmac) = अणु
		.m = MLX5_GET(fte_match_set_lyr_2_4, mask, dmac_47_16) << 16 |
		     MLX5_GET(fte_match_set_lyr_2_4, mask, dmac_15_0),
		.v = MLX5_GET(fte_match_set_lyr_2_4, value, dmac_47_16) << 16 |
		     MLX5_GET(fte_match_set_lyr_2_4, value, dmac_15_0)पूर्ण;
	MASK_VAL_L2(u16, ethertype, ethertype);
	MASK_VAL_L2(u8, ip_version, ip_version);

	PRINT_MASKED_VALP(smac, u8 *, p, "%pM");
	PRINT_MASKED_VALP(dmac, u8 *, p, "%pM");
	PRINT_MASKED_VAL(ethertype, p, "%04x");

	अगर ((ethertype.m == 0xffff && ethertype.v == ETH_P_IP) ||
	    (ip_version.m == 0xf && ip_version.v == 4)) अणु
#घोषणा MASK_VAL_L2_BE(type, name, fld) \
	MASK_VAL_BE(type, fte_match_set_lyr_2_4, name, mask, value, fld)
		MASK_VAL_L2_BE(u32, src_ipv4,
			       src_ipv4_src_ipv6.ipv4_layout.ipv4);
		MASK_VAL_L2_BE(u32, dst_ipv4,
			       dst_ipv4_dst_ipv6.ipv4_layout.ipv4);

		PRINT_MASKED_VALP(src_ipv4, typeof(&src_ipv4.v), p,
				  "%pI4");
		PRINT_MASKED_VALP(dst_ipv4, typeof(&dst_ipv4.v), p,
				  "%pI4");
	पूर्ण अन्यथा अगर ((ethertype.m == 0xffff && ethertype.v == ETH_P_IPV6) ||
		   (ip_version.m == 0xf && ip_version.v == 6)) अणु
		अटल स्थिर काष्ठा in6_addr full_ones = अणु
			.in6_u.u6_addr32 = अणु__स्थिरant_htonl(0xffffffff),
					    __स्थिरant_htonl(0xffffffff),
					    __स्थिरant_htonl(0xffffffff),
					    __स्थिरant_htonl(0xffffffff)पूर्ण,
		पूर्ण;
		DECLARE_MASK_VAL(काष्ठा in6_addr, src_ipv6);
		DECLARE_MASK_VAL(काष्ठा in6_addr, dst_ipv6);

		स_नकल(src_ipv6.m.in6_u.u6_addr8,
		       MLX5_ADDR_OF(fte_match_set_lyr_2_4, mask,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       माप(src_ipv6.m));
		स_नकल(dst_ipv6.m.in6_u.u6_addr8,
		       MLX5_ADDR_OF(fte_match_set_lyr_2_4, mask,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       माप(dst_ipv6.m));
		स_नकल(src_ipv6.v.in6_u.u6_addr8,
		       MLX5_ADDR_OF(fte_match_set_lyr_2_4, value,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       माप(src_ipv6.v));
		स_नकल(dst_ipv6.v.in6_u.u6_addr8,
		       MLX5_ADDR_OF(fte_match_set_lyr_2_4, value,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       माप(dst_ipv6.v));

		अगर (!स_भेद(&src_ipv6.m, &full_ones, माप(full_ones)))
			trace_seq_म_लिखो(p, "src_ipv6=%pI6 ",
					 &src_ipv6.v);
		अगर (!स_भेद(&dst_ipv6.m, &full_ones, माप(full_ones)))
			trace_seq_म_लिखो(p, "dst_ipv6=%pI6 ",
					 &dst_ipv6.v);
	पूर्ण

#घोषणा PRINT_MASKED_VAL_L2(type, name, fld, p, क्रमmat) अणु\
	MASK_VAL_L2(type, name, fld);		         \
	PRINT_MASKED_VAL(name, p, क्रमmat);		 \
पूर्ण

	PRINT_MASKED_VAL_L2(u8, ip_protocol, ip_protocol, p, "%02x");
	PRINT_MASKED_VAL_L2(u16, tcp_flags, tcp_flags, p, "%x");
	PRINT_MASKED_VAL_L2(u16, tcp_sport, tcp_sport, p, "%u");
	PRINT_MASKED_VAL_L2(u16, tcp_dport, tcp_dport, p, "%u");
	PRINT_MASKED_VAL_L2(u16, udp_sport, udp_sport, p, "%u");
	PRINT_MASKED_VAL_L2(u16, udp_dport, udp_dport, p, "%u");
	PRINT_MASKED_VAL_L2(u16, first_vid, first_vid, p, "%04x");
	PRINT_MASKED_VAL_L2(u8, first_prio, first_prio, p, "%x");
	PRINT_MASKED_VAL_L2(u8, first_cfi, first_cfi, p, "%d");
	PRINT_MASKED_VAL_L2(u8, ip_dscp, ip_dscp, p, "%02x");
	PRINT_MASKED_VAL_L2(u8, ip_ecn, ip_ecn, p, "%x");
	PRINT_MASKED_VAL_L2(u8, cvlan_tag, cvlan_tag, p, "%d");
	PRINT_MASKED_VAL_L2(u8, svlan_tag, svlan_tag, p, "%d");
	PRINT_MASKED_VAL_L2(u8, frag, frag, p, "%d");
पूर्ण

अटल व्योम prपूर्णांक_misc_parameters_hdrs(काष्ठा trace_seq *p,
				       स्थिर u32 *mask, स्थिर u32 *value)
अणु
#घोषणा MASK_VAL_MISC(type, name, fld) \
	MASK_VAL(type, fte_match_set_misc, name, mask, value, fld)
#घोषणा PRINT_MASKED_VAL_MISC(type, name, fld, p, क्रमmat) अणु\
	MASK_VAL_MISC(type, name, fld);			   \
	PRINT_MASKED_VAL(name, p, क्रमmat);		   \
पूर्ण
	DECLARE_MASK_VAL(u64, gre_key) = अणु
		.m = MLX5_GET(fte_match_set_misc, mask, gre_key.nvgre.hi) << 8 |
		     MLX5_GET(fte_match_set_misc, mask, gre_key.nvgre.lo),
		.v = MLX5_GET(fte_match_set_misc, value, gre_key.nvgre.hi) << 8 |
		     MLX5_GET(fte_match_set_misc, value, gre_key.nvgre.lo)पूर्ण;

	PRINT_MASKED_VAL(gre_key, p, "%llu");
	PRINT_MASKED_VAL_MISC(u32, source_sqn, source_sqn, p, "%u");
	PRINT_MASKED_VAL_MISC(u16, source_port, source_port, p, "%u");
	PRINT_MASKED_VAL_MISC(u8, outer_second_prio, outer_second_prio,
			      p, "%u");
	PRINT_MASKED_VAL_MISC(u8, outer_second_cfi, outer_second_cfi, p, "%u");
	PRINT_MASKED_VAL_MISC(u16, outer_second_vid, outer_second_vid, p, "%u");
	PRINT_MASKED_VAL_MISC(u8, inner_second_prio, inner_second_prio,
			      p, "%u");
	PRINT_MASKED_VAL_MISC(u8, inner_second_cfi, inner_second_cfi, p, "%u");
	PRINT_MASKED_VAL_MISC(u16, inner_second_vid, inner_second_vid, p, "%u");

	PRINT_MASKED_VAL_MISC(u8, outer_second_cvlan_tag,
			      outer_second_cvlan_tag, p, "%u");
	PRINT_MASKED_VAL_MISC(u8, inner_second_cvlan_tag,
			      inner_second_cvlan_tag, p, "%u");
	PRINT_MASKED_VAL_MISC(u8, outer_second_svlan_tag,
			      outer_second_svlan_tag, p, "%u");
	PRINT_MASKED_VAL_MISC(u8, inner_second_svlan_tag,
			      inner_second_svlan_tag, p, "%u");

	PRINT_MASKED_VAL_MISC(u8, gre_protocol, gre_protocol, p, "%u");

	PRINT_MASKED_VAL_MISC(u32, vxlan_vni, vxlan_vni, p, "%u");
	PRINT_MASKED_VAL_MISC(u32, outer_ipv6_flow_label, outer_ipv6_flow_label,
			      p, "%x");
	PRINT_MASKED_VAL_MISC(u32, inner_ipv6_flow_label, inner_ipv6_flow_label,
			      p, "%x");
पूर्ण

स्थिर अक्षर *parse_fs_hdrs(काष्ठा trace_seq *p,
			  u8 match_criteria_enable,
			  स्थिर u32 *mask_outer,
			  स्थिर u32 *mask_misc,
			  स्थिर u32 *mask_inner,
			  स्थिर u32 *value_outer,
			  स्थिर u32 *value_misc,
			  स्थिर u32 *value_inner)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	अगर (match_criteria_enable &
	    1 << MLX5_CREATE_FLOW_GROUP_IN_MATCH_CRITERIA_ENABLE_OUTER_HEADERS) अणु
		trace_seq_म_लिखो(p, "[outer] ");
		prपूर्णांक_lyr_2_4_hdrs(p, mask_outer, value_outer);
	पूर्ण

	अगर (match_criteria_enable &
	    1 << MLX5_CREATE_FLOW_GROUP_IN_MATCH_CRITERIA_ENABLE_MISC_PARAMETERS) अणु
		trace_seq_म_लिखो(p, "[misc] ");
		prपूर्णांक_misc_parameters_hdrs(p, mask_misc, value_misc);
	पूर्ण
	अगर (match_criteria_enable &
	    1 << MLX5_CREATE_FLOW_GROUP_IN_MATCH_CRITERIA_ENABLE_INNER_HEADERS) अणु
		trace_seq_म_लिखो(p, "[inner] ");
		prपूर्णांक_lyr_2_4_hdrs(p, mask_inner, value_inner);
	पूर्ण
	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

स्थिर अक्षर *parse_fs_dst(काष्ठा trace_seq *p,
			 स्थिर काष्ठा mlx5_flow_destination *dst,
			 u32 counter_id)
अणु
	स्थिर अक्षर *ret = trace_seq_buffer_ptr(p);

	चयन (dst->type) अणु
	हाल MLX5_FLOW_DESTINATION_TYPE_VPORT:
		trace_seq_म_लिखो(p, "vport=%u\n", dst->vport.num);
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE:
		trace_seq_म_लिखो(p, "ft=%p\n", dst->ft);
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE_NUM:
		trace_seq_म_लिखो(p, "ft_num=%u\n", dst->ft_num);
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_TIR:
		trace_seq_म_लिखो(p, "tir=%u\n", dst->tir_num);
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_FLOW_SAMPLER:
		trace_seq_म_लिखो(p, "sampler_id=%u\n", dst->sampler_id);
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_COUNTER:
		trace_seq_म_लिखो(p, "counter_id=%u\n", counter_id);
		अवरोध;
	हाल MLX5_FLOW_DESTINATION_TYPE_PORT:
		trace_seq_म_लिखो(p, "port\n");
		अवरोध;
	पूर्ण

	trace_seq_अ_दो(p, 0);
	वापस ret;
पूर्ण

EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_add_ft);
EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_del_ft);
EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_add_fg);
EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_del_fg);
EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_set_fte);
EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_del_fte);
EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_add_rule);
EXPORT_TRACEPOINT_SYMBOL(mlx5_fs_del_rule);

