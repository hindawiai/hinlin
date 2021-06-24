<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/mlx5/fs.h>
#समावेश "en.h"
#समावेश "en/params.h"
#समावेश "en/xsk/pool.h"

काष्ठा mlx5e_ethtool_rule अणु
	काष्ठा list_head             list;
	काष्ठा ethtool_rx_flow_spec  flow_spec;
	काष्ठा mlx5_flow_handle	     *rule;
	काष्ठा mlx5e_ethtool_table   *eth_ft;
पूर्ण;

अटल व्योम put_flow_table(काष्ठा mlx5e_ethtool_table *eth_ft)
अणु
	अगर (!--eth_ft->num_rules) अणु
		mlx5_destroy_flow_table(eth_ft->ft);
		eth_ft->ft = शून्य;
	पूर्ण
पूर्ण

#घोषणा MLX5E_ETHTOOL_L3_L4_PRIO 0
#घोषणा MLX5E_ETHTOOL_L2_PRIO (MLX5E_ETHTOOL_L3_L4_PRIO + ETHTOOL_NUM_L3_L4_FTS)
#घोषणा MLX5E_ETHTOOL_NUM_ENTRIES 64000
#घोषणा MLX5E_ETHTOOL_NUM_GROUPS  10
अटल काष्ठा mlx5e_ethtool_table *get_flow_table(काष्ठा mlx5e_priv *priv,
						  काष्ठा ethtool_rx_flow_spec *fs,
						  पूर्णांक num_tuples)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5e_ethtool_table *eth_ft;
	काष्ठा mlx5_flow_namespace *ns;
	काष्ठा mlx5_flow_table *ft;
	पूर्णांक max_tuples;
	पूर्णांक table_size;
	पूर्णांक prio;

	चयन (fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) अणु
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		max_tuples = ETHTOOL_NUM_L3_L4_FTS;
		prio = MLX5E_ETHTOOL_L3_L4_PRIO + (max_tuples - num_tuples);
		eth_ft = &priv->fs.ethtool.l3_l4_ft[prio];
		अवरोध;
	हाल IP_USER_FLOW:
	हाल IPV6_USER_FLOW:
		max_tuples = ETHTOOL_NUM_L3_L4_FTS;
		prio = MLX5E_ETHTOOL_L3_L4_PRIO + (max_tuples - num_tuples);
		eth_ft = &priv->fs.ethtool.l3_l4_ft[prio];
		अवरोध;
	हाल ETHER_FLOW:
		max_tuples = ETHTOOL_NUM_L2_FTS;
		prio = max_tuples - num_tuples;
		eth_ft = &priv->fs.ethtool.l2_ft[prio];
		prio += MLX5E_ETHTOOL_L2_PRIO;
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	eth_ft->num_rules++;
	अगर (eth_ft->ft)
		वापस eth_ft;

	ns = mlx5_get_flow_namespace(priv->mdev,
				     MLX5_FLOW_NAMESPACE_ETHTOOL);
	अगर (!ns)
		वापस ERR_PTR(-EOPNOTSUPP);

	table_size = min_t(u32, BIT(MLX5_CAP_FLOWTABLE(priv->mdev,
						       flow_table_properties_nic_receive.log_max_ft_size)),
			   MLX5E_ETHTOOL_NUM_ENTRIES);

	ft_attr.prio = prio;
	ft_attr.max_fte = table_size;
	ft_attr.स्वतःgroup.max_num_groups = MLX5E_ETHTOOL_NUM_GROUPS;
	ft = mlx5_create_स्वतः_grouped_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft))
		वापस (व्योम *)ft;

	eth_ft->ft = ft;
	वापस eth_ft;
पूर्ण

अटल व्योम mask_spec(u8 *mask, u8 *val, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < size; i++, mask++, val++)
		*((u8 *)val) = *((u8 *)mask) & *((u8 *)val);
पूर्ण

#घोषणा MLX5E_FTE_SET(header_p, fld, v)  \
	MLX5_SET(fte_match_set_lyr_2_4, header_p, fld, v)

#घोषणा MLX5E_FTE_ADDR_OF(header_p, fld) \
	MLX5_ADDR_OF(fte_match_set_lyr_2_4, header_p, fld)

अटल व्योम
set_ip4(व्योम *headers_c, व्योम *headers_v, __be32 ip4src_m,
	__be32 ip4src_v, __be32 ip4dst_m, __be32 ip4dst_v)
अणु
	अगर (ip4src_m) अणु
		स_नकल(MLX5E_FTE_ADDR_OF(headers_v, src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &ip4src_v, माप(ip4src_v));
		स_नकल(MLX5E_FTE_ADDR_OF(headers_c, src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &ip4src_m, माप(ip4src_m));
	पूर्ण
	अगर (ip4dst_m) अणु
		स_नकल(MLX5E_FTE_ADDR_OF(headers_v, dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &ip4dst_v, माप(ip4dst_v));
		स_नकल(MLX5E_FTE_ADDR_OF(headers_c, dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &ip4dst_m, माप(ip4dst_m));
	पूर्ण

	MLX5E_FTE_SET(headers_c, ethertype, 0xffff);
	MLX5E_FTE_SET(headers_v, ethertype, ETH_P_IP);
पूर्ण

अटल व्योम
set_ip6(व्योम *headers_c, व्योम *headers_v, __be32 ip6src_m[4],
	__be32 ip6src_v[4], __be32 ip6dst_m[4], __be32 ip6dst_v[4])
अणु
	u8 ip6_sz = MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6);

	अगर (!ipv6_addr_any((काष्ठा in6_addr *)ip6src_m)) अणु
		स_नकल(MLX5E_FTE_ADDR_OF(headers_v, src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       ip6src_v, ip6_sz);
		स_नकल(MLX5E_FTE_ADDR_OF(headers_c, src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       ip6src_m, ip6_sz);
	पूर्ण
	अगर (!ipv6_addr_any((काष्ठा in6_addr *)ip6dst_m)) अणु
		स_नकल(MLX5E_FTE_ADDR_OF(headers_v, dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       ip6dst_v, ip6_sz);
		स_नकल(MLX5E_FTE_ADDR_OF(headers_c, dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       ip6dst_m, ip6_sz);
	पूर्ण

	MLX5E_FTE_SET(headers_c, ethertype, 0xffff);
	MLX5E_FTE_SET(headers_v, ethertype, ETH_P_IPV6);
पूर्ण

अटल व्योम
set_tcp(व्योम *headers_c, व्योम *headers_v, __be16 psrc_m, __be16 psrc_v,
	__be16 pdst_m, __be16 pdst_v)
अणु
	अगर (psrc_m) अणु
		MLX5E_FTE_SET(headers_c, tcp_sport, ntohs(psrc_m));
		MLX5E_FTE_SET(headers_v, tcp_sport, ntohs(psrc_v));
	पूर्ण
	अगर (pdst_m) अणु
		MLX5E_FTE_SET(headers_c, tcp_dport, ntohs(pdst_m));
		MLX5E_FTE_SET(headers_v, tcp_dport, ntohs(pdst_v));
	पूर्ण

	MLX5E_FTE_SET(headers_c, ip_protocol, 0xffff);
	MLX5E_FTE_SET(headers_v, ip_protocol, IPPROTO_TCP);
पूर्ण

अटल व्योम
set_udp(व्योम *headers_c, व्योम *headers_v, __be16 psrc_m, __be16 psrc_v,
	__be16 pdst_m, __be16 pdst_v)
अणु
	अगर (psrc_m) अणु
		MLX5E_FTE_SET(headers_c, udp_sport, ntohs(psrc_m));
		MLX5E_FTE_SET(headers_v, udp_sport, ntohs(psrc_v));
	पूर्ण

	अगर (pdst_m) अणु
		MLX5E_FTE_SET(headers_c, udp_dport, ntohs(pdst_m));
		MLX5E_FTE_SET(headers_v, udp_dport, ntohs(pdst_v));
	पूर्ण

	MLX5E_FTE_SET(headers_c, ip_protocol, 0xffff);
	MLX5E_FTE_SET(headers_v, ip_protocol, IPPROTO_UDP);
पूर्ण

अटल व्योम
parse_tcp4(व्योम *headers_c, व्योम *headers_v, काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_tcpip4_spec *l4_mask = &fs->m_u.tcp_ip4_spec;
	काष्ठा ethtool_tcpip4_spec *l4_val  = &fs->h_u.tcp_ip4_spec;

	set_ip4(headers_c, headers_v, l4_mask->ip4src, l4_val->ip4src,
		l4_mask->ip4dst, l4_val->ip4dst);

	set_tcp(headers_c, headers_v, l4_mask->psrc, l4_val->psrc,
		l4_mask->pdst, l4_val->pdst);
पूर्ण

अटल व्योम
parse_udp4(व्योम *headers_c, व्योम *headers_v, काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_tcpip4_spec *l4_mask = &fs->m_u.udp_ip4_spec;
	काष्ठा ethtool_tcpip4_spec *l4_val  = &fs->h_u.udp_ip4_spec;

	set_ip4(headers_c, headers_v, l4_mask->ip4src, l4_val->ip4src,
		l4_mask->ip4dst, l4_val->ip4dst);

	set_udp(headers_c, headers_v, l4_mask->psrc, l4_val->psrc,
		l4_mask->pdst, l4_val->pdst);
पूर्ण

अटल व्योम
parse_ip4(व्योम *headers_c, व्योम *headers_v, काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_usrip4_spec *l3_mask = &fs->m_u.usr_ip4_spec;
	काष्ठा ethtool_usrip4_spec *l3_val  = &fs->h_u.usr_ip4_spec;

	set_ip4(headers_c, headers_v, l3_mask->ip4src, l3_val->ip4src,
		l3_mask->ip4dst, l3_val->ip4dst);

	अगर (l3_mask->proto) अणु
		MLX5E_FTE_SET(headers_c, ip_protocol, l3_mask->proto);
		MLX5E_FTE_SET(headers_v, ip_protocol, l3_val->proto);
	पूर्ण
पूर्ण

अटल व्योम
parse_ip6(व्योम *headers_c, व्योम *headers_v, काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_usrip6_spec *l3_mask = &fs->m_u.usr_ip6_spec;
	काष्ठा ethtool_usrip6_spec *l3_val  = &fs->h_u.usr_ip6_spec;

	set_ip6(headers_c, headers_v, l3_mask->ip6src,
		l3_val->ip6src, l3_mask->ip6dst, l3_val->ip6dst);

	अगर (l3_mask->l4_proto) अणु
		MLX5E_FTE_SET(headers_c, ip_protocol, l3_mask->l4_proto);
		MLX5E_FTE_SET(headers_v, ip_protocol, l3_val->l4_proto);
	पूर्ण
पूर्ण

अटल व्योम
parse_tcp6(व्योम *headers_c, व्योम *headers_v, काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_tcpip6_spec *l4_mask = &fs->m_u.tcp_ip6_spec;
	काष्ठा ethtool_tcpip6_spec *l4_val  = &fs->h_u.tcp_ip6_spec;

	set_ip6(headers_c, headers_v, l4_mask->ip6src,
		l4_val->ip6src, l4_mask->ip6dst, l4_val->ip6dst);

	set_tcp(headers_c, headers_v, l4_mask->psrc, l4_val->psrc,
		l4_mask->pdst, l4_val->pdst);
पूर्ण

अटल व्योम
parse_udp6(व्योम *headers_c, व्योम *headers_v, काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_tcpip6_spec *l4_mask = &fs->m_u.udp_ip6_spec;
	काष्ठा ethtool_tcpip6_spec *l4_val  = &fs->h_u.udp_ip6_spec;

	set_ip6(headers_c, headers_v, l4_mask->ip6src,
		l4_val->ip6src, l4_mask->ip6dst, l4_val->ip6dst);

	set_udp(headers_c, headers_v, l4_mask->psrc, l4_val->psrc,
		l4_mask->pdst, l4_val->pdst);
पूर्ण

अटल व्योम
parse_ether(व्योम *headers_c, व्योम *headers_v, काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethhdr *eth_mask = &fs->m_u.ether_spec;
	काष्ठा ethhdr *eth_val = &fs->h_u.ether_spec;

	mask_spec((u8 *)eth_mask, (u8 *)eth_val, माप(*eth_mask));
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_c, smac_47_16), eth_mask->h_source);
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_v, smac_47_16), eth_val->h_source);
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_c, dmac_47_16), eth_mask->h_dest);
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_v, dmac_47_16), eth_val->h_dest);
	MLX5E_FTE_SET(headers_c, ethertype, ntohs(eth_mask->h_proto));
	MLX5E_FTE_SET(headers_v, ethertype, ntohs(eth_val->h_proto));
पूर्ण

अटल व्योम
set_cvlan(व्योम *headers_c, व्योम *headers_v, __be16 vlan_tci)
अणु
	MLX5E_FTE_SET(headers_c, cvlan_tag, 1);
	MLX5E_FTE_SET(headers_v, cvlan_tag, 1);
	MLX5E_FTE_SET(headers_c, first_vid, 0xfff);
	MLX5E_FTE_SET(headers_v, first_vid, ntohs(vlan_tci));
पूर्ण

अटल व्योम
set_dmac(व्योम *headers_c, व्योम *headers_v,
	 अचिन्हित अक्षर m_dest[ETH_ALEN], अचिन्हित अक्षर v_dest[ETH_ALEN])
अणु
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_c, dmac_47_16), m_dest);
	ether_addr_copy(MLX5E_FTE_ADDR_OF(headers_v, dmac_47_16), v_dest);
पूर्ण

अटल पूर्णांक set_flow_attrs(u32 *match_c, u32 *match_v,
			  काष्ठा ethtool_rx_flow_spec *fs)
अणु
	व्योम *outer_headers_c = MLX5_ADDR_OF(fte_match_param, match_c,
					     outer_headers);
	व्योम *outer_headers_v = MLX5_ADDR_OF(fte_match_param, match_v,
					     outer_headers);
	u32 flow_type = fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT);

	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
		parse_tcp4(outer_headers_c, outer_headers_v, fs);
		अवरोध;
	हाल UDP_V4_FLOW:
		parse_udp4(outer_headers_c, outer_headers_v, fs);
		अवरोध;
	हाल IP_USER_FLOW:
		parse_ip4(outer_headers_c, outer_headers_v, fs);
		अवरोध;
	हाल TCP_V6_FLOW:
		parse_tcp6(outer_headers_c, outer_headers_v, fs);
		अवरोध;
	हाल UDP_V6_FLOW:
		parse_udp6(outer_headers_c, outer_headers_v, fs);
		अवरोध;
	हाल IPV6_USER_FLOW:
		parse_ip6(outer_headers_c, outer_headers_v, fs);
		अवरोध;
	हाल ETHER_FLOW:
		parse_ether(outer_headers_c, outer_headers_v, fs);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((fs->flow_type & FLOW_EXT) &&
	    (fs->m_ext.vlan_tci & cpu_to_be16(VLAN_VID_MASK)))
		set_cvlan(outer_headers_c, outer_headers_v, fs->h_ext.vlan_tci);

	अगर (fs->flow_type & FLOW_MAC_EXT &&
	    !is_zero_ether_addr(fs->m_ext.h_dest)) अणु
		mask_spec(fs->m_ext.h_dest, fs->h_ext.h_dest, ETH_ALEN);
		set_dmac(outer_headers_c, outer_headers_v, fs->m_ext.h_dest,
			 fs->h_ext.h_dest);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम add_rule_to_list(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_ethtool_rule *rule)
अणु
	काष्ठा mlx5e_ethtool_rule *iter;
	काष्ठा list_head *head = &priv->fs.ethtool.rules;

	list_क्रम_each_entry(iter, &priv->fs.ethtool.rules, list) अणु
		अगर (iter->flow_spec.location > rule->flow_spec.location)
			अवरोध;
		head = &iter->list;
	पूर्ण
	priv->fs.ethtool.tot_num_rules++;
	list_add(&rule->list, head);
पूर्ण

अटल bool outer_header_zero(u32 *match_criteria)
अणु
	पूर्णांक size = MLX5_FLD_SZ_BYTES(fte_match_param, outer_headers);
	अक्षर *outer_headers_c = MLX5_ADDR_OF(fte_match_param, match_criteria,
					     outer_headers);

	वापस outer_headers_c[0] == 0 && !स_भेद(outer_headers_c,
						  outer_headers_c + 1,
						  size - 1);
पूर्ण

अटल काष्ठा mlx5_flow_handle *
add_ethtool_flow_rule(काष्ठा mlx5e_priv *priv,
		      काष्ठा mlx5_flow_table *ft,
		      काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा mlx5_flow_act flow_act = अणु .flags = FLOW_ACT_NO_APPEND पूर्ण;
	काष्ठा mlx5_flow_destination *dst = शून्य;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस ERR_PTR(-ENOMEM);
	err = set_flow_attrs(spec->match_criteria, spec->match_value,
			     fs);
	अगर (err)
		जाओ मुक्त;

	अगर (fs->ring_cookie == RX_CLS_FLOW_DISC) अणु
		flow_act.action = MLX5_FLOW_CONTEXT_ACTION_DROP;
	पूर्ण अन्यथा अणु
		काष्ठा mlx5e_params *params = &priv->channels.params;
		क्रमागत mlx5e_rq_group group;
		काष्ठा mlx5e_tir *tir;
		u16 ix;

		mlx5e_qid_get_ch_and_group(params, fs->ring_cookie, &ix, &group);
		tir = group == MLX5E_RQ_GROUP_XSK ? priv->xsk_tir : priv->direct_tir;

		dst = kzalloc(माप(*dst), GFP_KERNEL);
		अगर (!dst) अणु
			err = -ENOMEM;
			जाओ मुक्त;
		पूर्ण

		dst->type = MLX5_FLOW_DESTINATION_TYPE_TIR;
		dst->tir_num = tir[ix].tirn;
		flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	पूर्ण

	spec->match_criteria_enable = (!outer_header_zero(spec->match_criteria));
	spec->flow_context.flow_tag = MLX5_FS_DEFAULT_FLOW_TAG;
	rule = mlx5_add_flow_rules(ft, spec, &flow_act, dst, dst ? 1 : 0);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		netdev_err(priv->netdev, "%s: failed to add ethtool steering rule: %d\n",
			   __func__, err);
		जाओ मुक्त;
	पूर्ण
मुक्त:
	kvमुक्त(spec);
	kमुक्त(dst);
	वापस err ? ERR_PTR(err) : rule;
पूर्ण

अटल व्योम del_ethtool_rule(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_ethtool_rule *eth_rule)
अणु
	अगर (eth_rule->rule)
		mlx5_del_flow_rules(eth_rule->rule);
	list_del(&eth_rule->list);
	priv->fs.ethtool.tot_num_rules--;
	put_flow_table(eth_rule->eth_ft);
	kमुक्त(eth_rule);
पूर्ण

अटल काष्ठा mlx5e_ethtool_rule *find_ethtool_rule(काष्ठा mlx5e_priv *priv,
						    पूर्णांक location)
अणु
	काष्ठा mlx5e_ethtool_rule *iter;

	list_क्रम_each_entry(iter, &priv->fs.ethtool.rules, list) अणु
		अगर (iter->flow_spec.location == location)
			वापस iter;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5e_ethtool_rule *get_ethtool_rule(काष्ठा mlx5e_priv *priv,
						   पूर्णांक location)
अणु
	काष्ठा mlx5e_ethtool_rule *eth_rule;

	eth_rule = find_ethtool_rule(priv, location);
	अगर (eth_rule)
		del_ethtool_rule(priv, eth_rule);

	eth_rule = kzalloc(माप(*eth_rule), GFP_KERNEL);
	अगर (!eth_rule)
		वापस ERR_PTR(-ENOMEM);

	add_rule_to_list(priv, eth_rule);
	वापस eth_rule;
पूर्ण

#घोषणा MAX_NUM_OF_ETHTOOL_RULES BIT(10)

#घोषणा all_ones(field) (field == (__क्रमce typeof(field))-1)
#घोषणा all_zeros_or_all_ones(field)		\
	((field) == 0 || (field) == (__क्रमce typeof(field))-1)

अटल पूर्णांक validate_ethter(काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethhdr *eth_mask = &fs->m_u.ether_spec;
	पूर्णांक ntuples = 0;

	अगर (!is_zero_ether_addr(eth_mask->h_dest))
		ntuples++;
	अगर (!is_zero_ether_addr(eth_mask->h_source))
		ntuples++;
	अगर (eth_mask->h_proto)
		ntuples++;
	वापस ntuples;
पूर्ण

अटल पूर्णांक validate_tcpudp4(काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_tcpip4_spec *l4_mask = &fs->m_u.tcp_ip4_spec;
	पूर्णांक ntuples = 0;

	अगर (l4_mask->tos)
		वापस -EINVAL;

	अगर (l4_mask->ip4src)
		ntuples++;
	अगर (l4_mask->ip4dst)
		ntuples++;
	अगर (l4_mask->psrc)
		ntuples++;
	अगर (l4_mask->pdst)
		ntuples++;
	/* Flow is TCP/UDP */
	वापस ++ntuples;
पूर्ण

अटल पूर्णांक validate_ip4(काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_usrip4_spec *l3_mask = &fs->m_u.usr_ip4_spec;
	पूर्णांक ntuples = 0;

	अगर (l3_mask->l4_4_bytes || l3_mask->tos ||
	    fs->h_u.usr_ip4_spec.ip_ver != ETH_RX_NFC_IP4)
		वापस -EINVAL;
	अगर (l3_mask->ip4src)
		ntuples++;
	अगर (l3_mask->ip4dst)
		ntuples++;
	अगर (l3_mask->proto)
		ntuples++;
	/* Flow is IPv4 */
	वापस ++ntuples;
पूर्ण

अटल पूर्णांक validate_ip6(काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_usrip6_spec *l3_mask = &fs->m_u.usr_ip6_spec;
	पूर्णांक ntuples = 0;

	अगर (l3_mask->l4_4_bytes || l3_mask->tclass)
		वापस -EINVAL;
	अगर (!ipv6_addr_any((काष्ठा in6_addr *)l3_mask->ip6src))
		ntuples++;

	अगर (!ipv6_addr_any((काष्ठा in6_addr *)l3_mask->ip6dst))
		ntuples++;
	अगर (l3_mask->l4_proto)
		ntuples++;
	/* Flow is IPv6 */
	वापस ++ntuples;
पूर्ण

अटल पूर्णांक validate_tcpudp6(काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा ethtool_tcpip6_spec *l4_mask = &fs->m_u.tcp_ip6_spec;
	पूर्णांक ntuples = 0;

	अगर (l4_mask->tclass)
		वापस -EINVAL;

	अगर (!ipv6_addr_any((काष्ठा in6_addr *)l4_mask->ip6src))
		ntuples++;

	अगर (!ipv6_addr_any((काष्ठा in6_addr *)l4_mask->ip6dst))
		ntuples++;

	अगर (l4_mask->psrc)
		ntuples++;
	अगर (l4_mask->pdst)
		ntuples++;
	/* Flow is TCP/UDP */
	वापस ++ntuples;
पूर्ण

अटल पूर्णांक validate_vlan(काष्ठा ethtool_rx_flow_spec *fs)
अणु
	अगर (fs->m_ext.vlan_etype ||
	    fs->m_ext.vlan_tci != cpu_to_be16(VLAN_VID_MASK))
		वापस -EINVAL;

	अगर (fs->m_ext.vlan_tci &&
	    (be16_to_cpu(fs->h_ext.vlan_tci) >= VLAN_N_VID))
		वापस -EINVAL;

	वापस 1;
पूर्ण

अटल पूर्णांक validate_flow(काष्ठा mlx5e_priv *priv,
			 काष्ठा ethtool_rx_flow_spec *fs)
अणु
	पूर्णांक num_tuples = 0;
	पूर्णांक ret = 0;

	अगर (fs->location >= MAX_NUM_OF_ETHTOOL_RULES)
		वापस -ENOSPC;

	अगर (fs->ring_cookie != RX_CLS_FLOW_DISC)
		अगर (!mlx5e_qid_validate(priv->profile, &priv->channels.params,
					fs->ring_cookie))
			वापस -EINVAL;

	चयन (fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) अणु
	हाल ETHER_FLOW:
		num_tuples += validate_ethter(fs);
		अवरोध;
	हाल TCP_V4_FLOW:
	हाल UDP_V4_FLOW:
		ret = validate_tcpudp4(fs);
		अगर (ret < 0)
			वापस ret;
		num_tuples += ret;
		अवरोध;
	हाल IP_USER_FLOW:
		ret = validate_ip4(fs);
		अगर (ret < 0)
			वापस ret;
		num_tuples += ret;
		अवरोध;
	हाल TCP_V6_FLOW:
	हाल UDP_V6_FLOW:
		ret = validate_tcpudp6(fs);
		अगर (ret < 0)
			वापस ret;
		num_tuples += ret;
		अवरोध;
	हाल IPV6_USER_FLOW:
		ret = validate_ip6(fs);
		अगर (ret < 0)
			वापस ret;
		num_tuples += ret;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
	अगर ((fs->flow_type & FLOW_EXT)) अणु
		ret = validate_vlan(fs);
		अगर (ret < 0)
			वापस ret;
		num_tuples += ret;
	पूर्ण

	अगर (fs->flow_type & FLOW_MAC_EXT &&
	    !is_zero_ether_addr(fs->m_ext.h_dest))
		num_tuples++;

	वापस num_tuples;
पूर्ण

अटल पूर्णांक
mlx5e_ethtool_flow_replace(काष्ठा mlx5e_priv *priv,
			   काष्ठा ethtool_rx_flow_spec *fs)
अणु
	काष्ठा mlx5e_ethtool_table *eth_ft;
	काष्ठा mlx5e_ethtool_rule *eth_rule;
	काष्ठा mlx5_flow_handle *rule;
	पूर्णांक num_tuples;
	पूर्णांक err;

	num_tuples = validate_flow(priv, fs);
	अगर (num_tuples <= 0) अणु
		netdev_warn(priv->netdev, "%s: flow is not valid %d\n",
			    __func__, num_tuples);
		वापस num_tuples;
	पूर्ण

	eth_ft = get_flow_table(priv, fs, num_tuples);
	अगर (IS_ERR(eth_ft))
		वापस PTR_ERR(eth_ft);

	eth_rule = get_ethtool_rule(priv, fs->location);
	अगर (IS_ERR(eth_rule)) अणु
		put_flow_table(eth_ft);
		वापस PTR_ERR(eth_rule);
	पूर्ण

	eth_rule->flow_spec = *fs;
	eth_rule->eth_ft = eth_ft;
	अगर (!eth_ft->ft) अणु
		err = -EINVAL;
		जाओ del_ethtool_rule;
	पूर्ण
	rule = add_ethtool_flow_rule(priv, eth_ft->ft, fs);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		जाओ del_ethtool_rule;
	पूर्ण

	eth_rule->rule = rule;

	वापस 0;

del_ethtool_rule:
	del_ethtool_rule(priv, eth_rule);

	वापस err;
पूर्ण

अटल पूर्णांक
mlx5e_ethtool_flow_हटाओ(काष्ठा mlx5e_priv *priv, पूर्णांक location)
अणु
	काष्ठा mlx5e_ethtool_rule *eth_rule;
	पूर्णांक err = 0;

	अगर (location >= MAX_NUM_OF_ETHTOOL_RULES)
		वापस -ENOSPC;

	eth_rule = find_ethtool_rule(priv, location);
	अगर (!eth_rule) अणु
		err =  -ENOENT;
		जाओ out;
	पूर्ण

	del_ethtool_rule(priv, eth_rule);
out:
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5e_ethtool_get_flow(काष्ठा mlx5e_priv *priv,
		       काष्ठा ethtool_rxnfc *info, पूर्णांक location)
अणु
	काष्ठा mlx5e_ethtool_rule *eth_rule;

	अगर (location < 0 || location >= MAX_NUM_OF_ETHTOOL_RULES)
		वापस -EINVAL;

	list_क्रम_each_entry(eth_rule, &priv->fs.ethtool.rules, list) अणु
		अगर (eth_rule->flow_spec.location == location) अणु
			info->fs = eth_rule->flow_spec;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक
mlx5e_ethtool_get_all_flows(काष्ठा mlx5e_priv *priv,
			    काष्ठा ethtool_rxnfc *info, u32 *rule_locs)
अणु
	पूर्णांक location = 0;
	पूर्णांक idx = 0;
	पूर्णांक err = 0;

	info->data = MAX_NUM_OF_ETHTOOL_RULES;
	जबतक ((!err || err == -ENOENT) && idx < info->rule_cnt) अणु
		err = mlx5e_ethtool_get_flow(priv, info, location);
		अगर (!err)
			rule_locs[idx++] = location;
		location++;
	पूर्ण
	वापस err;
पूर्ण

व्योम mlx5e_ethtool_cleanup_steering(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_ethtool_rule *iter;
	काष्ठा mlx5e_ethtool_rule *temp;

	list_क्रम_each_entry_safe(iter, temp, &priv->fs.ethtool.rules, list)
		del_ethtool_rule(priv, iter);
पूर्ण

व्योम mlx5e_ethtool_init_steering(काष्ठा mlx5e_priv *priv)
अणु
	INIT_LIST_HEAD(&priv->fs.ethtool.rules);
पूर्ण

अटल क्रमागत mlx5e_traffic_types flow_type_to_traffic_type(u32 flow_type)
अणु
	चयन (flow_type) अणु
	हाल TCP_V4_FLOW:
		वापस  MLX5E_TT_IPV4_TCP;
	हाल TCP_V6_FLOW:
		वापस MLX5E_TT_IPV6_TCP;
	हाल UDP_V4_FLOW:
		वापस MLX5E_TT_IPV4_UDP;
	हाल UDP_V6_FLOW:
		वापस MLX5E_TT_IPV6_UDP;
	हाल AH_V4_FLOW:
		वापस MLX5E_TT_IPV4_IPSEC_AH;
	हाल AH_V6_FLOW:
		वापस MLX5E_TT_IPV6_IPSEC_AH;
	हाल ESP_V4_FLOW:
		वापस MLX5E_TT_IPV4_IPSEC_ESP;
	हाल ESP_V6_FLOW:
		वापस MLX5E_TT_IPV6_IPSEC_ESP;
	हाल IPV4_FLOW:
		वापस MLX5E_TT_IPV4;
	हाल IPV6_FLOW:
		वापस MLX5E_TT_IPV6;
	शेष:
		वापस MLX5E_NUM_INसूची_TIRS;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_set_rss_hash_opt(काष्ठा mlx5e_priv *priv,
				  काष्ठा ethtool_rxnfc *nfc)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(modअगरy_tir_in);
	क्रमागत mlx5e_traffic_types tt;
	u8 rx_hash_field = 0;
	व्योम *in;

	tt = flow_type_to_traffic_type(nfc->flow_type);
	अगर (tt == MLX5E_NUM_INसूची_TIRS)
		वापस -EINVAL;

	/*  RSS करोes not support anything other than hashing to queues
	 *  on src IP, dest IP, TCP/UDP src port and TCP/UDP dest
	 *  port.
	 */
	अगर (nfc->flow_type != TCP_V4_FLOW &&
	    nfc->flow_type != TCP_V6_FLOW &&
	    nfc->flow_type != UDP_V4_FLOW &&
	    nfc->flow_type != UDP_V6_FLOW)
		वापस -EOPNOTSUPP;

	अगर (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EOPNOTSUPP;

	अगर (nfc->data & RXH_IP_SRC)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_SRC_IP;
	अगर (nfc->data & RXH_IP_DST)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_DST_IP;
	अगर (nfc->data & RXH_L4_B_0_1)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_L4_SPORT;
	अगर (nfc->data & RXH_L4_B_2_3)
		rx_hash_field |= MLX5_HASH_FIELD_SEL_L4_DPORT;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	mutex_lock(&priv->state_lock);

	अगर (rx_hash_field == priv->rss_params.rx_hash_fields[tt])
		जाओ out;

	priv->rss_params.rx_hash_fields[tt] = rx_hash_field;
	mlx5e_modअगरy_tirs_hash(priv, in);

out:
	mutex_unlock(&priv->state_lock);
	kvमुक्त(in);
	वापस 0;
पूर्ण

अटल पूर्णांक mlx5e_get_rss_hash_opt(काष्ठा mlx5e_priv *priv,
				  काष्ठा ethtool_rxnfc *nfc)
अणु
	क्रमागत mlx5e_traffic_types tt;
	u32 hash_field = 0;

	tt = flow_type_to_traffic_type(nfc->flow_type);
	अगर (tt == MLX5E_NUM_INसूची_TIRS)
		वापस -EINVAL;

	hash_field = priv->rss_params.rx_hash_fields[tt];
	nfc->data = 0;

	अगर (hash_field & MLX5_HASH_FIELD_SEL_SRC_IP)
		nfc->data |= RXH_IP_SRC;
	अगर (hash_field & MLX5_HASH_FIELD_SEL_DST_IP)
		nfc->data |= RXH_IP_DST;
	अगर (hash_field & MLX5_HASH_FIELD_SEL_L4_SPORT)
		nfc->data |= RXH_L4_B_0_1;
	अगर (hash_field & MLX5_HASH_FIELD_SEL_L4_DPORT)
		nfc->data |= RXH_L4_B_2_3;

	वापस 0;
पूर्ण

पूर्णांक mlx5e_ethtool_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		err = mlx5e_ethtool_flow_replace(priv, &cmd->fs);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		err = mlx5e_ethtool_flow_हटाओ(priv, cmd->fs.location);
		अवरोध;
	हाल ETHTOOL_SRXFH:
		err = mlx5e_set_rss_hash_opt(priv, cmd);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mlx5e_ethtool_get_rxnfc(काष्ठा net_device *dev,
			    काष्ठा ethtool_rxnfc *info, u32 *rule_locs)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXCLSRLCNT:
		info->rule_cnt = priv->fs.ethtool.tot_num_rules;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		err = mlx5e_ethtool_get_flow(priv, info, info->fs.location);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		err = mlx5e_ethtool_get_all_flows(priv, info, rule_locs);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		err =  mlx5e_get_rss_hash_opt(priv, info);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

