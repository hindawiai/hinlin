<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_conntrack_labels.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
#समावेश <uapi/linux/tc_act/tc_pedit.h>
#समावेश <net/tc_act/tc_ct.h>
#समावेश <net/flow_offload.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/refcount.h>
#समावेश <linux/xarray.h>

#समावेश "lib/fs_chains.h"
#समावेश "en/tc_ct.h"
#समावेश "en/mod_hdr.h"
#समावेश "en/mapping.h"
#समावेश "en.h"
#समावेश "en_tc.h"
#समावेश "en_rep.h"

#घोषणा MLX5_CT_ZONE_BITS (mlx5e_tc_attr_to_reg_mappings[ZONE_TO_REG].mlen * 8)
#घोषणा MLX5_CT_ZONE_MASK GENMASK(MLX5_CT_ZONE_BITS - 1, 0)
#घोषणा MLX5_CT_STATE_ESTABLISHED_BIT BIT(1)
#घोषणा MLX5_CT_STATE_TRK_BIT BIT(2)
#घोषणा MLX5_CT_STATE_NAT_BIT BIT(3)
#घोषणा MLX5_CT_STATE_REPLY_BIT BIT(4)
#घोषणा MLX5_CT_STATE_RELATED_BIT BIT(5)
#घोषणा MLX5_CT_STATE_INVALID_BIT BIT(6)

#घोषणा MLX5_FTE_ID_BITS (mlx5e_tc_attr_to_reg_mappings[FTEID_TO_REG].mlen * 8)
#घोषणा MLX5_FTE_ID_MAX GENMASK(MLX5_FTE_ID_BITS - 1, 0)
#घोषणा MLX5_FTE_ID_MASK MLX5_FTE_ID_MAX

#घोषणा MLX5_CT_LABELS_BITS (mlx5e_tc_attr_to_reg_mappings[LABELS_TO_REG].mlen * 8)
#घोषणा MLX5_CT_LABELS_MASK GENMASK(MLX5_CT_LABELS_BITS - 1, 0)

#घोषणा ct_dbg(fmt, args...)\
	netdev_dbg(ct_priv->netdev, "ct_debug: " fmt "\n", ##args)

काष्ठा mlx5_tc_ct_priv अणु
	काष्ठा mlx5_core_dev *dev;
	स्थिर काष्ठा net_device *netdev;
	काष्ठा mod_hdr_tbl *mod_hdr_tbl;
	काष्ठा idr fte_ids;
	काष्ठा xarray tuple_ids;
	काष्ठा rhashtable zone_ht;
	काष्ठा rhashtable ct_tuples_ht;
	काष्ठा rhashtable ct_tuples_nat_ht;
	काष्ठा mlx5_flow_table *ct;
	काष्ठा mlx5_flow_table *ct_nat;
	काष्ठा mlx5_flow_table *post_ct;
	काष्ठा mutex control_lock; /* guards parallel adds/dels */
	काष्ठा mapping_ctx *zone_mapping;
	काष्ठा mapping_ctx *labels_mapping;
	क्रमागत mlx5_flow_namespace_type ns_type;
	काष्ठा mlx5_fs_chains *chains;
	spinlock_t ht_lock; /* protects ft entries */
पूर्ण;

काष्ठा mlx5_ct_flow अणु
	काष्ठा mlx5_flow_attr *pre_ct_attr;
	काष्ठा mlx5_flow_attr *post_ct_attr;
	काष्ठा mlx5_flow_handle *pre_ct_rule;
	काष्ठा mlx5_flow_handle *post_ct_rule;
	काष्ठा mlx5_ct_ft *ft;
	u32 fte_id;
	u32 chain_mapping;
पूर्ण;

काष्ठा mlx5_ct_zone_rule अणु
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5e_mod_hdr_handle *mh;
	काष्ठा mlx5_flow_attr *attr;
	bool nat;
पूर्ण;

काष्ठा mlx5_tc_ct_pre अणु
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *flow_grp;
	काष्ठा mlx5_flow_group *miss_grp;
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5_flow_handle *miss_rule;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
पूर्ण;

काष्ठा mlx5_ct_ft अणु
	काष्ठा rhash_head node;
	u16 zone;
	u32 zone_restore_id;
	refcount_t refcount;
	काष्ठा nf_flowtable *nf_ft;
	काष्ठा mlx5_tc_ct_priv *ct_priv;
	काष्ठा rhashtable ct_entries_ht;
	काष्ठा mlx5_tc_ct_pre pre_ct;
	काष्ठा mlx5_tc_ct_pre pre_ct_nat;
पूर्ण;

काष्ठा mlx5_ct_tuple अणु
	u16 addr_type;
	__be16 n_proto;
	u8 ip_proto;
	काष्ठा अणु
		जोड़ अणु
			__be32 src_v4;
			काष्ठा in6_addr src_v6;
		पूर्ण;
		जोड़ अणु
			__be32 dst_v4;
			काष्ठा in6_addr dst_v6;
		पूर्ण;
	पूर्ण ip;
	काष्ठा अणु
		__be16 src;
		__be16 dst;
	पूर्ण port;

	u16 zone;
पूर्ण;

काष्ठा mlx5_ct_counter अणु
	काष्ठा mlx5_fc *counter;
	refcount_t refcount;
	bool is_shared;
पूर्ण;

क्रमागत अणु
	MLX5_CT_ENTRY_FLAG_VALID,
पूर्ण;

काष्ठा mlx5_ct_entry अणु
	काष्ठा rhash_head node;
	काष्ठा rhash_head tuple_node;
	काष्ठा rhash_head tuple_nat_node;
	काष्ठा mlx5_ct_counter *counter;
	अचिन्हित दीर्घ cookie;
	अचिन्हित दीर्घ restore_cookie;
	काष्ठा mlx5_ct_tuple tuple;
	काष्ठा mlx5_ct_tuple tuple_nat;
	काष्ठा mlx5_ct_zone_rule zone_rules[2];

	काष्ठा mlx5_tc_ct_priv *ct_priv;
	काष्ठा work_काष्ठा work;

	refcount_t refcnt;
	अचिन्हित दीर्घ flags;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params cts_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mlx5_ct_entry, node),
	.key_offset = दुरत्व(काष्ठा mlx5_ct_entry, cookie),
	.key_len = माप(((काष्ठा mlx5_ct_entry *)0)->cookie),
	.स्वतःmatic_shrinking = true,
	.min_size = 16 * 1024,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params zone_params = अणु
	.head_offset = दुरत्व(काष्ठा mlx5_ct_ft, node),
	.key_offset = दुरत्व(काष्ठा mlx5_ct_ft, zone),
	.key_len = माप(((काष्ठा mlx5_ct_ft *)0)->zone),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params tuples_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mlx5_ct_entry, tuple_node),
	.key_offset = दुरत्व(काष्ठा mlx5_ct_entry, tuple),
	.key_len = माप(((काष्ठा mlx5_ct_entry *)0)->tuple),
	.स्वतःmatic_shrinking = true,
	.min_size = 16 * 1024,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params tuples_nat_ht_params = अणु
	.head_offset = दुरत्व(काष्ठा mlx5_ct_entry, tuple_nat_node),
	.key_offset = दुरत्व(काष्ठा mlx5_ct_entry, tuple_nat),
	.key_len = माप(((काष्ठा mlx5_ct_entry *)0)->tuple_nat),
	.स्वतःmatic_shrinking = true,
	.min_size = 16 * 1024,
पूर्ण;

अटल bool
mlx5_tc_ct_entry_has_nat(काष्ठा mlx5_ct_entry *entry)
अणु
	वापस !!(entry->tuple_nat_node.next);
पूर्ण

अटल पूर्णांक
mlx5_get_label_mapping(काष्ठा mlx5_tc_ct_priv *ct_priv,
		       u32 *labels, u32 *id)
अणु
	अगर (!स_प्रथम_inv(labels, 0, माप(u32) * 4)) अणु
		*id = 0;
		वापस 0;
	पूर्ण

	अगर (mapping_add(ct_priv->labels_mapping, labels, id))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल व्योम
mlx5_put_label_mapping(काष्ठा mlx5_tc_ct_priv *ct_priv, u32 id)
अणु
	अगर (id)
		mapping_हटाओ(ct_priv->labels_mapping, id);
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_rule_to_tuple(काष्ठा mlx5_ct_tuple *tuple, काष्ठा flow_rule *rule)
अणु
	काष्ठा flow_match_control control;
	काष्ठा flow_match_basic basic;

	flow_rule_match_basic(rule, &basic);
	flow_rule_match_control(rule, &control);

	tuple->n_proto = basic.key->n_proto;
	tuple->ip_proto = basic.key->ip_proto;
	tuple->addr_type = control.key->addr_type;

	अगर (tuple->addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		tuple->ip.src_v4 = match.key->src;
		tuple->ip.dst_v4 = match.key->dst;
	पूर्ण अन्यथा अगर (tuple->addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		tuple->ip.src_v6 = match.key->src;
		tuple->ip.dst_v6 = match.key->dst;
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		चयन (tuple->ip_proto) अणु
		हाल IPPROTO_TCP:
		हाल IPPROTO_UDP:
			tuple->port.src = match.key->src;
			tuple->port.dst = match.key->dst;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_rule_to_tuple_nat(काष्ठा mlx5_ct_tuple *tuple,
			     काष्ठा flow_rule *rule)
अणु
	काष्ठा flow_action *flow_action = &rule->action;
	काष्ठा flow_action_entry *act;
	u32 offset, val, ip6_offset;
	पूर्णांक i;

	flow_action_क्रम_each(i, act, flow_action) अणु
		अगर (act->id != FLOW_ACTION_MANGLE)
			जारी;

		offset = act->mangle.offset;
		val = act->mangle.val;
		चयन (act->mangle.htype) अणु
		हाल FLOW_ACT_MANGLE_HDR_TYPE_IP4:
			अगर (offset == दुरत्व(काष्ठा iphdr, saddr))
				tuple->ip.src_v4 = cpu_to_be32(val);
			अन्यथा अगर (offset == दुरत्व(काष्ठा iphdr, daddr))
				tuple->ip.dst_v4 = cpu_to_be32(val);
			अन्यथा
				वापस -EOPNOTSUPP;
			अवरोध;

		हाल FLOW_ACT_MANGLE_HDR_TYPE_IP6:
			ip6_offset = (offset - दुरत्व(काष्ठा ipv6hdr, saddr));
			ip6_offset /= 4;
			अगर (ip6_offset < 4)
				tuple->ip.src_v6.s6_addr32[ip6_offset] = cpu_to_be32(val);
			अन्यथा अगर (ip6_offset < 8)
				tuple->ip.dst_v6.s6_addr32[ip6_offset - 4] = cpu_to_be32(val);
			अन्यथा
				वापस -EOPNOTSUPP;
			अवरोध;

		हाल FLOW_ACT_MANGLE_HDR_TYPE_TCP:
			अगर (offset == दुरत्व(काष्ठा tcphdr, source))
				tuple->port.src = cpu_to_be16(val);
			अन्यथा अगर (offset == दुरत्व(काष्ठा tcphdr, dest))
				tuple->port.dst = cpu_to_be16(val);
			अन्यथा
				वापस -EOPNOTSUPP;
			अवरोध;

		हाल FLOW_ACT_MANGLE_HDR_TYPE_UDP:
			अगर (offset == दुरत्व(काष्ठा udphdr, source))
				tuple->port.src = cpu_to_be16(val);
			अन्यथा अगर (offset == दुरत्व(काष्ठा udphdr, dest))
				tuple->port.dst = cpu_to_be16(val);
			अन्यथा
				वापस -EOPNOTSUPP;
			अवरोध;

		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_set_tuple_match(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_flow_spec *spec,
			   काष्ठा flow_rule *rule)
अणु
	व्योम *headers_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
				       outer_headers);
	व्योम *headers_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				       outer_headers);
	u16 addr_type = 0;
	u8 ip_proto = 0;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) अणु
		काष्ठा flow_match_basic match;

		flow_rule_match_basic(rule, &match);

		mlx5e_tc_set_ethertype(priv->mdev, &match, true, headers_c,
				       headers_v);
		MLX5_SET(fte_match_set_lyr_2_4, headers_c, ip_protocol,
			 match.mask->ip_proto);
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, ip_protocol,
			 match.key->ip_proto);

		ip_proto = match.key->ip_proto;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) अणु
		काष्ठा flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		काष्ठा flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &match.mask->src, माप(match.mask->src));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    src_ipv4_src_ipv6.ipv4_layout.ipv4),
		       &match.key->src, माप(match.key->src));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &match.mask->dst, माप(match.mask->dst));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    dst_ipv4_dst_ipv6.ipv4_layout.ipv4),
		       &match.key->dst, माप(match.key->dst));
	पूर्ण

	अगर (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &match.mask->src, माप(match.mask->src));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    src_ipv4_src_ipv6.ipv6_layout.ipv6),
		       &match.key->src, माप(match.key->src));

		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_c,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &match.mask->dst, माप(match.mask->dst));
		स_नकल(MLX5_ADDR_OF(fte_match_set_lyr_2_4, headers_v,
				    dst_ipv4_dst_ipv6.ipv6_layout.ipv6),
		       &match.key->dst, माप(match.key->dst));
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) अणु
		काष्ठा flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		चयन (ip_proto) अणु
		हाल IPPROTO_TCP:
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 tcp_sport, ntohs(match.mask->src));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 tcp_sport, ntohs(match.key->src));

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 tcp_dport, ntohs(match.mask->dst));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 tcp_dport, ntohs(match.key->dst));
			अवरोध;

		हाल IPPROTO_UDP:
			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 udp_sport, ntohs(match.mask->src));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 udp_sport, ntohs(match.key->src));

			MLX5_SET(fte_match_set_lyr_2_4, headers_c,
				 udp_dport, ntohs(match.mask->dst));
			MLX5_SET(fte_match_set_lyr_2_4, headers_v,
				 udp_dport, ntohs(match.key->dst));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_TCP)) अणु
		काष्ठा flow_match_tcp match;

		flow_rule_match_tcp(rule, &match);
		MLX5_SET(fte_match_set_lyr_2_4, headers_c, tcp_flags,
			 ntohs(match.mask->flags));
		MLX5_SET(fte_match_set_lyr_2_4, headers_v, tcp_flags,
			 ntohs(match.key->flags));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mlx5_tc_ct_counter_put(काष्ठा mlx5_tc_ct_priv *ct_priv, काष्ठा mlx5_ct_entry *entry)
अणु
	अगर (entry->counter->is_shared &&
	    !refcount_dec_and_test(&entry->counter->refcount))
		वापस;

	mlx5_fc_destroy(ct_priv->dev, entry->counter->counter);
	kमुक्त(entry->counter);
पूर्ण

अटल व्योम
mlx5_tc_ct_entry_del_rule(काष्ठा mlx5_tc_ct_priv *ct_priv,
			  काष्ठा mlx5_ct_entry *entry,
			  bool nat)
अणु
	काष्ठा mlx5_ct_zone_rule *zone_rule = &entry->zone_rules[nat];
	काष्ठा mlx5_flow_attr *attr = zone_rule->attr;

	ct_dbg("Deleting ct entry rule in zone %d", entry->tuple.zone);

	mlx5_tc_rule_delete(netdev_priv(ct_priv->netdev), zone_rule->rule, attr);
	mlx5e_mod_hdr_detach(ct_priv->dev,
			     ct_priv->mod_hdr_tbl, zone_rule->mh);
	mlx5_put_label_mapping(ct_priv, attr->ct_attr.ct_labels_id);
	kमुक्त(attr);
पूर्ण

अटल व्योम
mlx5_tc_ct_entry_del_rules(काष्ठा mlx5_tc_ct_priv *ct_priv,
			   काष्ठा mlx5_ct_entry *entry)
अणु
	mlx5_tc_ct_entry_del_rule(ct_priv, entry, true);
	mlx5_tc_ct_entry_del_rule(ct_priv, entry, false);
पूर्ण

अटल काष्ठा flow_action_entry *
mlx5_tc_ct_get_ct_metadata_action(काष्ठा flow_rule *flow_rule)
अणु
	काष्ठा flow_action *flow_action = &flow_rule->action;
	काष्ठा flow_action_entry *act;
	पूर्णांक i;

	flow_action_क्रम_each(i, act, flow_action) अणु
		अगर (act->id == FLOW_ACTION_CT_METADATA)
			वापस act;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_entry_set_रेजिस्टरs(काष्ठा mlx5_tc_ct_priv *ct_priv,
			       काष्ठा mlx5e_tc_mod_hdr_acts *mod_acts,
			       u8 ct_state,
			       u32 mark,
			       u32 labels_id,
			       u8 zone_restore_id)
अणु
	क्रमागत mlx5_flow_namespace_type ns = ct_priv->ns_type;
	काष्ठा mlx5_core_dev *dev = ct_priv->dev;
	पूर्णांक err;

	err = mlx5e_tc_match_to_reg_set(dev, mod_acts, ns,
					CTSTATE_TO_REG, ct_state);
	अगर (err)
		वापस err;

	err = mlx5e_tc_match_to_reg_set(dev, mod_acts, ns,
					MARK_TO_REG, mark);
	अगर (err)
		वापस err;

	err = mlx5e_tc_match_to_reg_set(dev, mod_acts, ns,
					LABELS_TO_REG, labels_id);
	अगर (err)
		वापस err;

	err = mlx5e_tc_match_to_reg_set(dev, mod_acts, ns,
					ZONE_RESTORE_TO_REG, zone_restore_id);
	अगर (err)
		वापस err;

	/* Make another copy of zone id in reg_b क्रम
	 * NIC rx flows since we करोn't copy reg_c1 to
	 * reg_b upon miss.
	 */
	अगर (ns != MLX5_FLOW_NAMESPACE_FDB) अणु
		err = mlx5e_tc_match_to_reg_set(dev, mod_acts, ns,
						NIC_ZONE_RESTORE_TO_REG, zone_restore_id);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_parse_mangle_to_mod_act(काष्ठा flow_action_entry *act,
				   अक्षर *modact)
अणु
	u32 offset = act->mangle.offset, field;

	चयन (act->mangle.htype) अणु
	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP4:
		MLX5_SET(set_action_in, modact, length, 0);
		अगर (offset == दुरत्व(काष्ठा iphdr, saddr))
			field = MLX5_ACTION_IN_FIELD_OUT_SIPV4;
		अन्यथा अगर (offset == दुरत्व(काष्ठा iphdr, daddr))
			field = MLX5_ACTION_IN_FIELD_OUT_DIPV4;
		अन्यथा
			वापस -EOPNOTSUPP;
		अवरोध;

	हाल FLOW_ACT_MANGLE_HDR_TYPE_IP6:
		MLX5_SET(set_action_in, modact, length, 0);
		अगर (offset == दुरत्व(काष्ठा ipv6hdr, saddr) + 12)
			field = MLX5_ACTION_IN_FIELD_OUT_SIPV6_31_0;
		अन्यथा अगर (offset == दुरत्व(काष्ठा ipv6hdr, saddr) + 8)
			field = MLX5_ACTION_IN_FIELD_OUT_SIPV6_63_32;
		अन्यथा अगर (offset == दुरत्व(काष्ठा ipv6hdr, saddr) + 4)
			field = MLX5_ACTION_IN_FIELD_OUT_SIPV6_95_64;
		अन्यथा अगर (offset == दुरत्व(काष्ठा ipv6hdr, saddr))
			field = MLX5_ACTION_IN_FIELD_OUT_SIPV6_127_96;
		अन्यथा अगर (offset == दुरत्व(काष्ठा ipv6hdr, daddr) + 12)
			field = MLX5_ACTION_IN_FIELD_OUT_DIPV6_31_0;
		अन्यथा अगर (offset == दुरत्व(काष्ठा ipv6hdr, daddr) + 8)
			field = MLX5_ACTION_IN_FIELD_OUT_DIPV6_63_32;
		अन्यथा अगर (offset == दुरत्व(काष्ठा ipv6hdr, daddr) + 4)
			field = MLX5_ACTION_IN_FIELD_OUT_DIPV6_95_64;
		अन्यथा अगर (offset == दुरत्व(काष्ठा ipv6hdr, daddr))
			field = MLX5_ACTION_IN_FIELD_OUT_DIPV6_127_96;
		अन्यथा
			वापस -EOPNOTSUPP;
		अवरोध;

	हाल FLOW_ACT_MANGLE_HDR_TYPE_TCP:
		MLX5_SET(set_action_in, modact, length, 16);
		अगर (offset == दुरत्व(काष्ठा tcphdr, source))
			field = MLX5_ACTION_IN_FIELD_OUT_TCP_SPORT;
		अन्यथा अगर (offset == दुरत्व(काष्ठा tcphdr, dest))
			field = MLX5_ACTION_IN_FIELD_OUT_TCP_DPORT;
		अन्यथा
			वापस -EOPNOTSUPP;
		अवरोध;

	हाल FLOW_ACT_MANGLE_HDR_TYPE_UDP:
		MLX5_SET(set_action_in, modact, length, 16);
		अगर (offset == दुरत्व(काष्ठा udphdr, source))
			field = MLX5_ACTION_IN_FIELD_OUT_UDP_SPORT;
		अन्यथा अगर (offset == दुरत्व(काष्ठा udphdr, dest))
			field = MLX5_ACTION_IN_FIELD_OUT_UDP_DPORT;
		अन्यथा
			वापस -EOPNOTSUPP;
		अवरोध;

	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	MLX5_SET(set_action_in, modact, action_type, MLX5_ACTION_TYPE_SET);
	MLX5_SET(set_action_in, modact, offset, 0);
	MLX5_SET(set_action_in, modact, field, field);
	MLX5_SET(set_action_in, modact, data, act->mangle.val);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_entry_create_nat(काष्ठा mlx5_tc_ct_priv *ct_priv,
			    काष्ठा flow_rule *flow_rule,
			    काष्ठा mlx5e_tc_mod_hdr_acts *mod_acts)
अणु
	काष्ठा flow_action *flow_action = &flow_rule->action;
	काष्ठा mlx5_core_dev *mdev = ct_priv->dev;
	काष्ठा flow_action_entry *act;
	माप_प्रकार action_size;
	अक्षर *modact;
	पूर्णांक err, i;

	action_size = MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः);

	flow_action_क्रम_each(i, act, flow_action) अणु
		चयन (act->id) अणु
		हाल FLOW_ACTION_MANGLE: अणु
			err = alloc_mod_hdr_actions(mdev, ct_priv->ns_type,
						    mod_acts);
			अगर (err)
				वापस err;

			modact = mod_acts->actions +
				 mod_acts->num_actions * action_size;

			err = mlx5_tc_ct_parse_mangle_to_mod_act(act, modact);
			अगर (err)
				वापस err;

			mod_acts->num_actions++;
		पूर्ण
		अवरोध;

		हाल FLOW_ACTION_CT_METADATA:
			/* Handled earlier */
			जारी;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_entry_create_mod_hdr(काष्ठा mlx5_tc_ct_priv *ct_priv,
				काष्ठा mlx5_flow_attr *attr,
				काष्ठा flow_rule *flow_rule,
				काष्ठा mlx5e_mod_hdr_handle **mh,
				u8 zone_restore_id, bool nat)
अणु
	काष्ठा mlx5e_tc_mod_hdr_acts mod_acts = अणुपूर्ण;
	काष्ठा flow_action_entry *meta;
	u16 ct_state = 0;
	पूर्णांक err;

	meta = mlx5_tc_ct_get_ct_metadata_action(flow_rule);
	अगर (!meta)
		वापस -EOPNOTSUPP;

	err = mlx5_get_label_mapping(ct_priv, meta->ct_metadata.labels,
				     &attr->ct_attr.ct_labels_id);
	अगर (err)
		वापस -EOPNOTSUPP;
	अगर (nat) अणु
		err = mlx5_tc_ct_entry_create_nat(ct_priv, flow_rule,
						  &mod_acts);
		अगर (err)
			जाओ err_mapping;

		ct_state |= MLX5_CT_STATE_NAT_BIT;
	पूर्ण

	ct_state |= MLX5_CT_STATE_ESTABLISHED_BIT | MLX5_CT_STATE_TRK_BIT;
	ct_state |= meta->ct_metadata.orig_dir ? 0 : MLX5_CT_STATE_REPLY_BIT;
	err = mlx5_tc_ct_entry_set_रेजिस्टरs(ct_priv, &mod_acts,
					     ct_state,
					     meta->ct_metadata.mark,
					     attr->ct_attr.ct_labels_id,
					     zone_restore_id);
	अगर (err)
		जाओ err_mapping;

	*mh = mlx5e_mod_hdr_attach(ct_priv->dev,
				   ct_priv->mod_hdr_tbl,
				   ct_priv->ns_type,
				   &mod_acts);
	अगर (IS_ERR(*mh)) अणु
		err = PTR_ERR(*mh);
		जाओ err_mapping;
	पूर्ण
	attr->modअगरy_hdr = mlx5e_mod_hdr_get(*mh);

	dealloc_mod_hdr_actions(&mod_acts);
	वापस 0;

err_mapping:
	dealloc_mod_hdr_actions(&mod_acts);
	mlx5_put_label_mapping(ct_priv, attr->ct_attr.ct_labels_id);
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_entry_add_rule(काष्ठा mlx5_tc_ct_priv *ct_priv,
			  काष्ठा flow_rule *flow_rule,
			  काष्ठा mlx5_ct_entry *entry,
			  bool nat, u8 zone_restore_id)
अणु
	काष्ठा mlx5_ct_zone_rule *zone_rule = &entry->zone_rules[nat];
	काष्ठा mlx5e_priv *priv = netdev_priv(ct_priv->netdev);
	काष्ठा mlx5_flow_spec *spec = शून्य;
	काष्ठा mlx5_flow_attr *attr;
	पूर्णांक err;

	zone_rule->nat = nat;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	attr = mlx5_alloc_flow_attr(ct_priv->ns_type);
	अगर (!attr) अणु
		err = -ENOMEM;
		जाओ err_attr;
	पूर्ण

	err = mlx5_tc_ct_entry_create_mod_hdr(ct_priv, attr, flow_rule,
					      &zone_rule->mh,
					      zone_restore_id, nat);
	अगर (err) अणु
		ct_dbg("Failed to create ct entry mod hdr");
		जाओ err_mod_hdr;
	पूर्ण

	attr->action = MLX5_FLOW_CONTEXT_ACTION_MOD_HDR |
		       MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
		       MLX5_FLOW_CONTEXT_ACTION_COUNT;
	attr->dest_chain = 0;
	attr->dest_ft = ct_priv->post_ct;
	attr->ft = nat ? ct_priv->ct_nat : ct_priv->ct;
	attr->outer_match_level = MLX5_MATCH_L4;
	attr->counter = entry->counter->counter;
	attr->flags |= MLX5_ESW_ATTR_FLAG_NO_IN_PORT;
	अगर (ct_priv->ns_type == MLX5_FLOW_NAMESPACE_FDB)
		attr->esw_attr->in_mdev = priv->mdev;

	mlx5_tc_ct_set_tuple_match(netdev_priv(ct_priv->netdev), spec, flow_rule);
	mlx5e_tc_match_to_reg_match(spec, ZONE_TO_REG, entry->tuple.zone, MLX5_CT_ZONE_MASK);

	zone_rule->rule = mlx5_tc_rule_insert(priv, spec, attr);
	अगर (IS_ERR(zone_rule->rule)) अणु
		err = PTR_ERR(zone_rule->rule);
		ct_dbg("Failed to add ct entry rule, nat: %d", nat);
		जाओ err_rule;
	पूर्ण

	zone_rule->attr = attr;

	kvमुक्त(spec);
	ct_dbg("Offloaded ct entry rule in zone %d", entry->tuple.zone);

	वापस 0;

err_rule:
	mlx5e_mod_hdr_detach(ct_priv->dev,
			     ct_priv->mod_hdr_tbl, zone_rule->mh);
	mlx5_put_label_mapping(ct_priv, attr->ct_attr.ct_labels_id);
err_mod_hdr:
	kमुक्त(attr);
err_attr:
	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल bool
mlx5_tc_ct_entry_valid(काष्ठा mlx5_ct_entry *entry)
अणु
	वापस test_bit(MLX5_CT_ENTRY_FLAG_VALID, &entry->flags);
पूर्ण

अटल काष्ठा mlx5_ct_entry *
mlx5_tc_ct_entry_get(काष्ठा mlx5_tc_ct_priv *ct_priv, काष्ठा mlx5_ct_tuple *tuple)
अणु
	काष्ठा mlx5_ct_entry *entry;

	entry = rhashtable_lookup_fast(&ct_priv->ct_tuples_ht, tuple,
				       tuples_ht_params);
	अगर (entry && mlx5_tc_ct_entry_valid(entry) &&
	    refcount_inc_not_zero(&entry->refcnt)) अणु
		वापस entry;
	पूर्ण अन्यथा अगर (!entry) अणु
		entry = rhashtable_lookup_fast(&ct_priv->ct_tuples_nat_ht,
					       tuple, tuples_nat_ht_params);
		अगर (entry && mlx5_tc_ct_entry_valid(entry) &&
		    refcount_inc_not_zero(&entry->refcnt))
			वापस entry;
	पूर्ण

	वापस entry ? ERR_PTR(-EINVAL) : शून्य;
पूर्ण

अटल व्योम mlx5_tc_ct_entry_हटाओ_from_tuples(काष्ठा mlx5_ct_entry *entry)
अणु
	काष्ठा mlx5_tc_ct_priv *ct_priv = entry->ct_priv;

	rhashtable_हटाओ_fast(&ct_priv->ct_tuples_nat_ht,
			       &entry->tuple_nat_node,
			       tuples_nat_ht_params);
	rhashtable_हटाओ_fast(&ct_priv->ct_tuples_ht, &entry->tuple_node,
			       tuples_ht_params);
पूर्ण

अटल व्योम mlx5_tc_ct_entry_del(काष्ठा mlx5_ct_entry *entry)
अणु
	काष्ठा mlx5_tc_ct_priv *ct_priv = entry->ct_priv;

	mlx5_tc_ct_entry_del_rules(ct_priv, entry);

	spin_lock_bh(&ct_priv->ht_lock);
	mlx5_tc_ct_entry_हटाओ_from_tuples(entry);
	spin_unlock_bh(&ct_priv->ht_lock);

	mlx5_tc_ct_counter_put(ct_priv, entry);
	kमुक्त(entry);
पूर्ण

अटल व्योम
mlx5_tc_ct_entry_put(काष्ठा mlx5_ct_entry *entry)
अणु
	अगर (!refcount_dec_and_test(&entry->refcnt))
		वापस;

	mlx5_tc_ct_entry_del(entry);
पूर्ण

अटल व्योम mlx5_tc_ct_entry_del_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_ct_entry *entry = container_of(work, काष्ठा mlx5_ct_entry, work);

	mlx5_tc_ct_entry_del(entry);
पूर्ण

अटल व्योम
__mlx5_tc_ct_entry_put(काष्ठा mlx5_ct_entry *entry)
अणु
	काष्ठा mlx5e_priv *priv;

	अगर (!refcount_dec_and_test(&entry->refcnt))
		वापस;

	priv = netdev_priv(entry->ct_priv->netdev);
	INIT_WORK(&entry->work, mlx5_tc_ct_entry_del_work);
	queue_work(priv->wq, &entry->work);
पूर्ण

अटल काष्ठा mlx5_ct_counter *
mlx5_tc_ct_counter_create(काष्ठा mlx5_tc_ct_priv *ct_priv)
अणु
	काष्ठा mlx5_ct_counter *counter;
	पूर्णांक ret;

	counter = kzalloc(माप(*counter), GFP_KERNEL);
	अगर (!counter)
		वापस ERR_PTR(-ENOMEM);

	counter->is_shared = false;
	counter->counter = mlx5_fc_create(ct_priv->dev, true);
	अगर (IS_ERR(counter->counter)) अणु
		ct_dbg("Failed to create counter for ct entry");
		ret = PTR_ERR(counter->counter);
		kमुक्त(counter);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस counter;
पूर्ण

अटल काष्ठा mlx5_ct_counter *
mlx5_tc_ct_shared_counter_get(काष्ठा mlx5_tc_ct_priv *ct_priv,
			      काष्ठा mlx5_ct_entry *entry)
अणु
	काष्ठा mlx5_ct_tuple rev_tuple = entry->tuple;
	काष्ठा mlx5_ct_counter *shared_counter;
	काष्ठा mlx5_ct_entry *rev_entry;
	__be16 पंचांगp_port;

	/* get the reversed tuple */
	पंचांगp_port = rev_tuple.port.src;
	rev_tuple.port.src = rev_tuple.port.dst;
	rev_tuple.port.dst = पंचांगp_port;

	अगर (rev_tuple.addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) अणु
		__be32 पंचांगp_addr = rev_tuple.ip.src_v4;

		rev_tuple.ip.src_v4 = rev_tuple.ip.dst_v4;
		rev_tuple.ip.dst_v4 = पंचांगp_addr;
	पूर्ण अन्यथा अगर (rev_tuple.addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) अणु
		काष्ठा in6_addr पंचांगp_addr = rev_tuple.ip.src_v6;

		rev_tuple.ip.src_v6 = rev_tuple.ip.dst_v6;
		rev_tuple.ip.dst_v6 = पंचांगp_addr;
	पूर्ण अन्यथा अणु
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	/* Use the same counter as the reverse direction */
	spin_lock_bh(&ct_priv->ht_lock);
	rev_entry = mlx5_tc_ct_entry_get(ct_priv, &rev_tuple);

	अगर (IS_ERR(rev_entry)) अणु
		spin_unlock_bh(&ct_priv->ht_lock);
		जाओ create_counter;
	पूर्ण

	अगर (rev_entry && refcount_inc_not_zero(&rev_entry->counter->refcount)) अणु
		ct_dbg("Using shared counter entry=0x%p rev=0x%p\n", entry, rev_entry);
		shared_counter = rev_entry->counter;
		spin_unlock_bh(&ct_priv->ht_lock);

		mlx5_tc_ct_entry_put(rev_entry);
		वापस shared_counter;
	पूर्ण

	spin_unlock_bh(&ct_priv->ht_lock);

create_counter:

	shared_counter = mlx5_tc_ct_counter_create(ct_priv);
	अगर (IS_ERR(shared_counter))
		वापस shared_counter;

	shared_counter->is_shared = true;
	refcount_set(&shared_counter->refcount, 1);
	वापस shared_counter;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_entry_add_rules(काष्ठा mlx5_tc_ct_priv *ct_priv,
			   काष्ठा flow_rule *flow_rule,
			   काष्ठा mlx5_ct_entry *entry,
			   u8 zone_restore_id)
अणु
	पूर्णांक err;

	अगर (nf_ct_acct_enabled(dev_net(ct_priv->netdev)))
		entry->counter = mlx5_tc_ct_counter_create(ct_priv);
	अन्यथा
		entry->counter = mlx5_tc_ct_shared_counter_get(ct_priv, entry);

	अगर (IS_ERR(entry->counter)) अणु
		err = PTR_ERR(entry->counter);
		वापस err;
	पूर्ण

	err = mlx5_tc_ct_entry_add_rule(ct_priv, flow_rule, entry, false,
					zone_restore_id);
	अगर (err)
		जाओ err_orig;

	err = mlx5_tc_ct_entry_add_rule(ct_priv, flow_rule, entry, true,
					zone_restore_id);
	अगर (err)
		जाओ err_nat;

	वापस 0;

err_nat:
	mlx5_tc_ct_entry_del_rule(ct_priv, entry, false);
err_orig:
	mlx5_tc_ct_counter_put(ct_priv, entry);
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_block_flow_offload_add(काष्ठा mlx5_ct_ft *ft,
				  काष्ठा flow_cls_offload *flow)
अणु
	काष्ठा flow_rule *flow_rule = flow_cls_offload_flow_rule(flow);
	काष्ठा mlx5_tc_ct_priv *ct_priv = ft->ct_priv;
	काष्ठा flow_action_entry *meta_action;
	अचिन्हित दीर्घ cookie = flow->cookie;
	काष्ठा mlx5_ct_entry *entry;
	पूर्णांक err;

	meta_action = mlx5_tc_ct_get_ct_metadata_action(flow_rule);
	अगर (!meta_action)
		वापस -EOPNOTSUPP;

	spin_lock_bh(&ct_priv->ht_lock);
	entry = rhashtable_lookup_fast(&ft->ct_entries_ht, &cookie, cts_ht_params);
	अगर (entry && refcount_inc_not_zero(&entry->refcnt)) अणु
		spin_unlock_bh(&ct_priv->ht_lock);
		mlx5_tc_ct_entry_put(entry);
		वापस -EEXIST;
	पूर्ण
	spin_unlock_bh(&ct_priv->ht_lock);

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस -ENOMEM;

	entry->tuple.zone = ft->zone;
	entry->cookie = flow->cookie;
	entry->restore_cookie = meta_action->ct_metadata.cookie;
	refcount_set(&entry->refcnt, 2);
	entry->ct_priv = ct_priv;

	err = mlx5_tc_ct_rule_to_tuple(&entry->tuple, flow_rule);
	अगर (err)
		जाओ err_set;

	स_नकल(&entry->tuple_nat, &entry->tuple, माप(entry->tuple));
	err = mlx5_tc_ct_rule_to_tuple_nat(&entry->tuple_nat, flow_rule);
	अगर (err)
		जाओ err_set;

	spin_lock_bh(&ct_priv->ht_lock);

	err = rhashtable_lookup_insert_fast(&ft->ct_entries_ht, &entry->node,
					    cts_ht_params);
	अगर (err)
		जाओ err_entries;

	err = rhashtable_lookup_insert_fast(&ct_priv->ct_tuples_ht,
					    &entry->tuple_node,
					    tuples_ht_params);
	अगर (err)
		जाओ err_tuple;

	अगर (स_भेद(&entry->tuple, &entry->tuple_nat, माप(entry->tuple))) अणु
		err = rhashtable_lookup_insert_fast(&ct_priv->ct_tuples_nat_ht,
						    &entry->tuple_nat_node,
						    tuples_nat_ht_params);
		अगर (err)
			जाओ err_tuple_nat;
	पूर्ण
	spin_unlock_bh(&ct_priv->ht_lock);

	err = mlx5_tc_ct_entry_add_rules(ct_priv, flow_rule, entry,
					 ft->zone_restore_id);
	अगर (err)
		जाओ err_rules;

	set_bit(MLX5_CT_ENTRY_FLAG_VALID, &entry->flags);
	mlx5_tc_ct_entry_put(entry); /* this function reference */

	वापस 0;

err_rules:
	spin_lock_bh(&ct_priv->ht_lock);
	अगर (mlx5_tc_ct_entry_has_nat(entry))
		rhashtable_हटाओ_fast(&ct_priv->ct_tuples_nat_ht,
				       &entry->tuple_nat_node, tuples_nat_ht_params);
err_tuple_nat:
	rhashtable_हटाओ_fast(&ct_priv->ct_tuples_ht,
			       &entry->tuple_node,
			       tuples_ht_params);
err_tuple:
	rhashtable_हटाओ_fast(&ft->ct_entries_ht,
			       &entry->node,
			       cts_ht_params);
err_entries:
	spin_unlock_bh(&ct_priv->ht_lock);
err_set:
	kमुक्त(entry);
	अगर (err != -EEXIST)
		netdev_warn(ct_priv->netdev, "Failed to offload ct entry, err: %d\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_block_flow_offload_del(काष्ठा mlx5_ct_ft *ft,
				  काष्ठा flow_cls_offload *flow)
अणु
	काष्ठा mlx5_tc_ct_priv *ct_priv = ft->ct_priv;
	अचिन्हित दीर्घ cookie = flow->cookie;
	काष्ठा mlx5_ct_entry *entry;

	spin_lock_bh(&ct_priv->ht_lock);
	entry = rhashtable_lookup_fast(&ft->ct_entries_ht, &cookie, cts_ht_params);
	अगर (!entry) अणु
		spin_unlock_bh(&ct_priv->ht_lock);
		वापस -ENOENT;
	पूर्ण

	अगर (!mlx5_tc_ct_entry_valid(entry)) अणु
		spin_unlock_bh(&ct_priv->ht_lock);
		वापस -EINVAL;
	पूर्ण

	rhashtable_हटाओ_fast(&ft->ct_entries_ht, &entry->node, cts_ht_params);
	mlx5_tc_ct_entry_हटाओ_from_tuples(entry);
	spin_unlock_bh(&ct_priv->ht_lock);

	mlx5_tc_ct_entry_put(entry);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_block_flow_offload_stats(काष्ठा mlx5_ct_ft *ft,
				    काष्ठा flow_cls_offload *f)
अणु
	काष्ठा mlx5_tc_ct_priv *ct_priv = ft->ct_priv;
	अचिन्हित दीर्घ cookie = f->cookie;
	काष्ठा mlx5_ct_entry *entry;
	u64 lastuse, packets, bytes;

	spin_lock_bh(&ct_priv->ht_lock);
	entry = rhashtable_lookup_fast(&ft->ct_entries_ht, &cookie, cts_ht_params);
	अगर (!entry) अणु
		spin_unlock_bh(&ct_priv->ht_lock);
		वापस -ENOENT;
	पूर्ण

	अगर (!mlx5_tc_ct_entry_valid(entry) || !refcount_inc_not_zero(&entry->refcnt)) अणु
		spin_unlock_bh(&ct_priv->ht_lock);
		वापस -EINVAL;
	पूर्ण

	spin_unlock_bh(&ct_priv->ht_lock);

	mlx5_fc_query_cached(entry->counter->counter, &bytes, &packets, &lastuse);
	flow_stats_update(&f->stats, bytes, packets, 0, lastuse,
			  FLOW_ACTION_HW_STATS_DELAYED);

	mlx5_tc_ct_entry_put(entry);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_block_flow_offload(क्रमागत tc_setup_type type, व्योम *type_data,
			      व्योम *cb_priv)
अणु
	काष्ठा flow_cls_offload *f = type_data;
	काष्ठा mlx5_ct_ft *ft = cb_priv;

	अगर (type != TC_SETUP_CLSFLOWER)
		वापस -EOPNOTSUPP;

	चयन (f->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस mlx5_tc_ct_block_flow_offload_add(ft, f);
	हाल FLOW_CLS_DESTROY:
		वापस mlx5_tc_ct_block_flow_offload_del(ft, f);
	हाल FLOW_CLS_STATS:
		वापस mlx5_tc_ct_block_flow_offload_stats(ft, f);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल bool
mlx5_tc_ct_skb_to_tuple(काष्ठा sk_buff *skb, काष्ठा mlx5_ct_tuple *tuple,
			u16 zone)
अणु
	काष्ठा flow_keys flow_keys;

	skb_reset_network_header(skb);
	skb_flow_dissect_flow_keys(skb, &flow_keys, 0);

	tuple->zone = zone;

	अगर (flow_keys.basic.ip_proto != IPPROTO_TCP &&
	    flow_keys.basic.ip_proto != IPPROTO_UDP)
		वापस false;

	tuple->port.src = flow_keys.ports.src;
	tuple->port.dst = flow_keys.ports.dst;
	tuple->n_proto = flow_keys.basic.n_proto;
	tuple->ip_proto = flow_keys.basic.ip_proto;

	चयन (flow_keys.basic.n_proto) अणु
	हाल htons(ETH_P_IP):
		tuple->addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		tuple->ip.src_v4 = flow_keys.addrs.v4addrs.src;
		tuple->ip.dst_v4 = flow_keys.addrs.v4addrs.dst;
		अवरोध;

	हाल htons(ETH_P_IPV6):
		tuple->addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		tuple->ip.src_v6 = flow_keys.addrs.v6addrs.src;
		tuple->ip.dst_v6 = flow_keys.addrs.v6addrs.dst;
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	वापस true;

out:
	वापस false;
पूर्ण

पूर्णांक mlx5_tc_ct_add_no_trk_match(काष्ठा mlx5_flow_spec *spec)
अणु
	u32 ctstate = 0, ctstate_mask = 0;

	mlx5e_tc_match_to_reg_get_match(spec, CTSTATE_TO_REG,
					&ctstate, &ctstate_mask);

	अगर ((ctstate & ctstate_mask) == MLX5_CT_STATE_TRK_BIT)
		वापस -EOPNOTSUPP;

	ctstate_mask |= MLX5_CT_STATE_TRK_BIT;
	mlx5e_tc_match_to_reg_match(spec, CTSTATE_TO_REG,
				    ctstate, ctstate_mask);

	वापस 0;
पूर्ण

व्योम mlx5_tc_ct_match_del(काष्ठा mlx5_tc_ct_priv *priv, काष्ठा mlx5_ct_attr *ct_attr)
अणु
	अगर (!priv || !ct_attr->ct_labels_id)
		वापस;

	mlx5_put_label_mapping(priv, ct_attr->ct_labels_id);
पूर्ण

पूर्णांक
mlx5_tc_ct_match_add(काष्ठा mlx5_tc_ct_priv *priv,
		     काष्ठा mlx5_flow_spec *spec,
		     काष्ठा flow_cls_offload *f,
		     काष्ठा mlx5_ct_attr *ct_attr,
		     काष्ठा netlink_ext_ack *extack)
अणु
	bool trk, est, untrk, unest, new, rpl, unrpl, rel, unrel, inv, uninv;
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा flow_dissector_key_ct *mask, *key;
	u32 ctstate = 0, ctstate_mask = 0;
	u16 ct_state_on, ct_state_off;
	u16 ct_state, ct_state_mask;
	काष्ठा flow_match_ct match;
	u32 ct_labels[4];

	अगर (!flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CT))
		वापस 0;

	अगर (!priv) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "offload of ct matching isn't available");
		वापस -EOPNOTSUPP;
	पूर्ण

	flow_rule_match_ct(rule, &match);

	key = match.key;
	mask = match.mask;

	ct_state = key->ct_state;
	ct_state_mask = mask->ct_state;

	अगर (ct_state_mask & ~(TCA_FLOWER_KEY_CT_FLAGS_TRACKED |
			      TCA_FLOWER_KEY_CT_FLAGS_ESTABLISHED |
			      TCA_FLOWER_KEY_CT_FLAGS_NEW |
			      TCA_FLOWER_KEY_CT_FLAGS_REPLY |
			      TCA_FLOWER_KEY_CT_FLAGS_RELATED |
			      TCA_FLOWER_KEY_CT_FLAGS_INVALID)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "only ct_state trk, est, new and rpl are supported for offload");
		वापस -EOPNOTSUPP;
	पूर्ण

	ct_state_on = ct_state & ct_state_mask;
	ct_state_off = (ct_state & ct_state_mask) ^ ct_state_mask;
	trk = ct_state_on & TCA_FLOWER_KEY_CT_FLAGS_TRACKED;
	new = ct_state_on & TCA_FLOWER_KEY_CT_FLAGS_NEW;
	est = ct_state_on & TCA_FLOWER_KEY_CT_FLAGS_ESTABLISHED;
	rpl = ct_state_on & TCA_FLOWER_KEY_CT_FLAGS_REPLY;
	rel = ct_state_on & TCA_FLOWER_KEY_CT_FLAGS_RELATED;
	inv = ct_state_on & TCA_FLOWER_KEY_CT_FLAGS_INVALID;
	untrk = ct_state_off & TCA_FLOWER_KEY_CT_FLAGS_TRACKED;
	unest = ct_state_off & TCA_FLOWER_KEY_CT_FLAGS_ESTABLISHED;
	unrpl = ct_state_off & TCA_FLOWER_KEY_CT_FLAGS_REPLY;
	unrel = ct_state_off & TCA_FLOWER_KEY_CT_FLAGS_RELATED;
	uninv = ct_state_off & TCA_FLOWER_KEY_CT_FLAGS_INVALID;

	ctstate |= trk ? MLX5_CT_STATE_TRK_BIT : 0;
	ctstate |= est ? MLX5_CT_STATE_ESTABLISHED_BIT : 0;
	ctstate |= rpl ? MLX5_CT_STATE_REPLY_BIT : 0;
	ctstate_mask |= (untrk || trk) ? MLX5_CT_STATE_TRK_BIT : 0;
	ctstate_mask |= (unest || est) ? MLX5_CT_STATE_ESTABLISHED_BIT : 0;
	ctstate_mask |= (unrpl || rpl) ? MLX5_CT_STATE_REPLY_BIT : 0;
	ctstate_mask |= unrel ? MLX5_CT_STATE_RELATED_BIT : 0;
	ctstate_mask |= uninv ? MLX5_CT_STATE_INVALID_BIT : 0;

	अगर (rel) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "matching on ct_state +rel isn't supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (inv) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "matching on ct_state +inv isn't supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (new) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "matching on ct_state +new isn't supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (mask->ct_zone)
		mlx5e_tc_match_to_reg_match(spec, ZONE_TO_REG,
					    key->ct_zone, MLX5_CT_ZONE_MASK);
	अगर (ctstate_mask)
		mlx5e_tc_match_to_reg_match(spec, CTSTATE_TO_REG,
					    ctstate, ctstate_mask);
	अगर (mask->ct_mark)
		mlx5e_tc_match_to_reg_match(spec, MARK_TO_REG,
					    key->ct_mark, mask->ct_mark);
	अगर (mask->ct_labels[0] || mask->ct_labels[1] || mask->ct_labels[2] ||
	    mask->ct_labels[3]) अणु
		ct_labels[0] = key->ct_labels[0] & mask->ct_labels[0];
		ct_labels[1] = key->ct_labels[1] & mask->ct_labels[1];
		ct_labels[2] = key->ct_labels[2] & mask->ct_labels[2];
		ct_labels[3] = key->ct_labels[3] & mask->ct_labels[3];
		अगर (mlx5_get_label_mapping(priv, ct_labels, &ct_attr->ct_labels_id))
			वापस -EOPNOTSUPP;
		mlx5e_tc_match_to_reg_match(spec, LABELS_TO_REG, ct_attr->ct_labels_id,
					    MLX5_CT_LABELS_MASK);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
mlx5_tc_ct_parse_action(काष्ठा mlx5_tc_ct_priv *priv,
			काष्ठा mlx5_flow_attr *attr,
			स्थिर काष्ठा flow_action_entry *act,
			काष्ठा netlink_ext_ack *extack)
अणु
	अगर (!priv) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "offload of ct action isn't available");
		वापस -EOPNOTSUPP;
	पूर्ण

	attr->ct_attr.zone = act->ct.zone;
	attr->ct_attr.ct_action = act->ct.action;
	attr->ct_attr.nf_ft = act->ct.flow_table;

	वापस 0;
पूर्ण

अटल पूर्णांक tc_ct_pre_ct_add_rules(काष्ठा mlx5_ct_ft *ct_ft,
				  काष्ठा mlx5_tc_ct_pre *pre_ct,
				  bool nat)
अणु
	काष्ठा mlx5_tc_ct_priv *ct_priv = ct_ft->ct_priv;
	काष्ठा mlx5e_tc_mod_hdr_acts pre_mod_acts = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = ct_priv->dev;
	काष्ठा mlx5_flow_table *ft = pre_ct->ft;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_modअगरy_hdr *mod_hdr;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_spec *spec;
	u32 ctstate;
	u16 zone;
	पूर्णांक err;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	zone = ct_ft->zone & MLX5_CT_ZONE_MASK;
	err = mlx5e_tc_match_to_reg_set(dev, &pre_mod_acts, ct_priv->ns_type,
					ZONE_TO_REG, zone);
	अगर (err) अणु
		ct_dbg("Failed to set zone register mapping");
		जाओ err_mapping;
	पूर्ण

	mod_hdr = mlx5_modअगरy_header_alloc(dev, ct_priv->ns_type,
					   pre_mod_acts.num_actions,
					   pre_mod_acts.actions);

	अगर (IS_ERR(mod_hdr)) अणु
		err = PTR_ERR(mod_hdr);
		ct_dbg("Failed to create pre ct mod hdr");
		जाओ err_mapping;
	पूर्ण
	pre_ct->modअगरy_hdr = mod_hdr;

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
			  MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	flow_act.flags |= FLOW_ACT_IGNORE_FLOW_LEVEL;
	flow_act.modअगरy_hdr = mod_hdr;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;

	/* add flow rule */
	mlx5e_tc_match_to_reg_match(spec, ZONE_TO_REG,
				    zone, MLX5_CT_ZONE_MASK);
	ctstate = MLX5_CT_STATE_TRK_BIT;
	अगर (nat)
		ctstate |= MLX5_CT_STATE_NAT_BIT;
	mlx5e_tc_match_to_reg_match(spec, CTSTATE_TO_REG, ctstate, ctstate);

	dest.ft = ct_priv->post_ct;
	rule = mlx5_add_flow_rules(ft, spec, &flow_act, &dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		ct_dbg("Failed to add pre ct flow rule zone %d", zone);
		जाओ err_flow_rule;
	पूर्ण
	pre_ct->flow_rule = rule;

	/* add miss rule */
	dest.ft = nat ? ct_priv->ct_nat : ct_priv->ct;
	rule = mlx5_add_flow_rules(ft, शून्य, &flow_act, &dest, 1);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		ct_dbg("Failed to add pre ct miss rule zone %d", zone);
		जाओ err_miss_rule;
	पूर्ण
	pre_ct->miss_rule = rule;

	dealloc_mod_hdr_actions(&pre_mod_acts);
	kvमुक्त(spec);
	वापस 0;

err_miss_rule:
	mlx5_del_flow_rules(pre_ct->flow_rule);
err_flow_rule:
	mlx5_modअगरy_header_dealloc(dev, pre_ct->modअगरy_hdr);
err_mapping:
	dealloc_mod_hdr_actions(&pre_mod_acts);
	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल व्योम
tc_ct_pre_ct_del_rules(काष्ठा mlx5_ct_ft *ct_ft,
		       काष्ठा mlx5_tc_ct_pre *pre_ct)
अणु
	काष्ठा mlx5_tc_ct_priv *ct_priv = ct_ft->ct_priv;
	काष्ठा mlx5_core_dev *dev = ct_priv->dev;

	mlx5_del_flow_rules(pre_ct->flow_rule);
	mlx5_del_flow_rules(pre_ct->miss_rule);
	mlx5_modअगरy_header_dealloc(dev, pre_ct->modअगरy_hdr);
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_alloc_pre_ct(काष्ठा mlx5_ct_ft *ct_ft,
			काष्ठा mlx5_tc_ct_pre *pre_ct,
			bool nat)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_tc_ct_priv *ct_priv = ct_ft->ct_priv;
	काष्ठा mlx5_core_dev *dev = ct_priv->dev;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *ns;
	काष्ठा mlx5_flow_table *ft;
	काष्ठा mlx5_flow_group *g;
	u32 metadata_reg_c_2_mask;
	u32 *flow_group_in;
	व्योम *misc;
	पूर्णांक err;

	ns = mlx5_get_flow_namespace(dev, ct_priv->ns_type);
	अगर (!ns) अणु
		err = -EOPNOTSUPP;
		ct_dbg("Failed to get flow namespace");
		वापस err;
	पूर्ण

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in)
		वापस -ENOMEM;

	ft_attr.flags = MLX5_FLOW_TABLE_UNMANAGED;
	ft_attr.prio =  ct_priv->ns_type ==  MLX5_FLOW_NAMESPACE_FDB ?
			FDB_TC_OFFLOAD : MLX5E_TC_PRIO;
	ft_attr.max_fte = 2;
	ft_attr.level = 1;
	ft = mlx5_create_flow_table(ns, &ft_attr);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		ct_dbg("Failed to create pre ct table");
		जाओ out_मुक्त;
	पूर्ण
	pre_ct->ft = ft;

	/* create flow group */
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_MISC_PARAMETERS_2);

	misc = MLX5_ADDR_OF(create_flow_group_in, flow_group_in,
			    match_criteria.misc_parameters_2);

	metadata_reg_c_2_mask = MLX5_CT_ZONE_MASK;
	metadata_reg_c_2_mask |= (MLX5_CT_STATE_TRK_BIT << 16);
	अगर (nat)
		metadata_reg_c_2_mask |= (MLX5_CT_STATE_NAT_BIT << 16);

	MLX5_SET(fte_match_set_misc2, misc, metadata_reg_c_2,
		 metadata_reg_c_2_mask);

	g = mlx5_create_flow_group(ft, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		ct_dbg("Failed to create pre ct group");
		जाओ err_flow_grp;
	पूर्ण
	pre_ct->flow_grp = g;

	/* create miss group */
	स_रखो(flow_group_in, 0, inlen);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 1);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 1);
	g = mlx5_create_flow_group(ft, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		ct_dbg("Failed to create pre ct miss group");
		जाओ err_miss_grp;
	पूर्ण
	pre_ct->miss_grp = g;

	err = tc_ct_pre_ct_add_rules(ct_ft, pre_ct, nat);
	अगर (err)
		जाओ err_add_rules;

	kvमुक्त(flow_group_in);
	वापस 0;

err_add_rules:
	mlx5_destroy_flow_group(pre_ct->miss_grp);
err_miss_grp:
	mlx5_destroy_flow_group(pre_ct->flow_grp);
err_flow_grp:
	mlx5_destroy_flow_table(ft);
out_मुक्त:
	kvमुक्त(flow_group_in);
	वापस err;
पूर्ण

अटल व्योम
mlx5_tc_ct_मुक्त_pre_ct(काष्ठा mlx5_ct_ft *ct_ft,
		       काष्ठा mlx5_tc_ct_pre *pre_ct)
अणु
	tc_ct_pre_ct_del_rules(ct_ft, pre_ct);
	mlx5_destroy_flow_group(pre_ct->miss_grp);
	mlx5_destroy_flow_group(pre_ct->flow_grp);
	mlx5_destroy_flow_table(pre_ct->ft);
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_alloc_pre_ct_tables(काष्ठा mlx5_ct_ft *ft)
अणु
	पूर्णांक err;

	err = mlx5_tc_ct_alloc_pre_ct(ft, &ft->pre_ct, false);
	अगर (err)
		वापस err;

	err = mlx5_tc_ct_alloc_pre_ct(ft, &ft->pre_ct_nat, true);
	अगर (err)
		जाओ err_pre_ct_nat;

	वापस 0;

err_pre_ct_nat:
	mlx5_tc_ct_मुक्त_pre_ct(ft, &ft->pre_ct);
	वापस err;
पूर्ण

अटल व्योम
mlx5_tc_ct_मुक्त_pre_ct_tables(काष्ठा mlx5_ct_ft *ft)
अणु
	mlx5_tc_ct_मुक्त_pre_ct(ft, &ft->pre_ct_nat);
	mlx5_tc_ct_मुक्त_pre_ct(ft, &ft->pre_ct);
पूर्ण

/* To aव्योम false lock dependency warning set the ct_entries_ht lock
 * class dअगरferent than the lock class of the ht being used when deleting
 * last flow from a group and then deleting a group, we get पूर्णांकo del_sw_flow_group()
 * which call rhashtable_destroy on fg->ftes_hash which will take ht->mutex but
 * it's dअगरferent than the ht->mutex here.
 */
अटल काष्ठा lock_class_key ct_entries_ht_lock_key;

अटल काष्ठा mlx5_ct_ft *
mlx5_tc_ct_add_ft_cb(काष्ठा mlx5_tc_ct_priv *ct_priv, u16 zone,
		     काष्ठा nf_flowtable *nf_ft)
अणु
	काष्ठा mlx5_ct_ft *ft;
	पूर्णांक err;

	ft = rhashtable_lookup_fast(&ct_priv->zone_ht, &zone, zone_params);
	अगर (ft) अणु
		refcount_inc(&ft->refcount);
		वापस ft;
	पूर्ण

	ft = kzalloc(माप(*ft), GFP_KERNEL);
	अगर (!ft)
		वापस ERR_PTR(-ENOMEM);

	err = mapping_add(ct_priv->zone_mapping, &zone, &ft->zone_restore_id);
	अगर (err)
		जाओ err_mapping;

	ft->zone = zone;
	ft->nf_ft = nf_ft;
	ft->ct_priv = ct_priv;
	refcount_set(&ft->refcount, 1);

	err = mlx5_tc_ct_alloc_pre_ct_tables(ft);
	अगर (err)
		जाओ err_alloc_pre_ct;

	err = rhashtable_init(&ft->ct_entries_ht, &cts_ht_params);
	अगर (err)
		जाओ err_init;

	lockdep_set_class(&ft->ct_entries_ht.mutex, &ct_entries_ht_lock_key);

	err = rhashtable_insert_fast(&ct_priv->zone_ht, &ft->node,
				     zone_params);
	अगर (err)
		जाओ err_insert;

	err = nf_flow_table_offload_add_cb(ft->nf_ft,
					   mlx5_tc_ct_block_flow_offload, ft);
	अगर (err)
		जाओ err_add_cb;

	वापस ft;

err_add_cb:
	rhashtable_हटाओ_fast(&ct_priv->zone_ht, &ft->node, zone_params);
err_insert:
	rhashtable_destroy(&ft->ct_entries_ht);
err_init:
	mlx5_tc_ct_मुक्त_pre_ct_tables(ft);
err_alloc_pre_ct:
	mapping_हटाओ(ct_priv->zone_mapping, ft->zone_restore_id);
err_mapping:
	kमुक्त(ft);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlx5_tc_ct_flush_ft_entry(व्योम *ptr, व्योम *arg)
अणु
	काष्ठा mlx5_ct_entry *entry = ptr;

	mlx5_tc_ct_entry_put(entry);
पूर्ण

अटल व्योम
mlx5_tc_ct_del_ft_cb(काष्ठा mlx5_tc_ct_priv *ct_priv, काष्ठा mlx5_ct_ft *ft)
अणु
	अगर (!refcount_dec_and_test(&ft->refcount))
		वापस;

	nf_flow_table_offload_del_cb(ft->nf_ft,
				     mlx5_tc_ct_block_flow_offload, ft);
	rhashtable_हटाओ_fast(&ct_priv->zone_ht, &ft->node, zone_params);
	rhashtable_मुक्त_and_destroy(&ft->ct_entries_ht,
				    mlx5_tc_ct_flush_ft_entry,
				    ct_priv);
	mlx5_tc_ct_मुक्त_pre_ct_tables(ft);
	mapping_हटाओ(ct_priv->zone_mapping, ft->zone_restore_id);
	kमुक्त(ft);
पूर्ण

/* We translate the tc filter with CT action to the following HW model:
 *
 * +---------------------+
 * + ft prio (tc chain) +
 * + original match      +
 * +---------------------+
 *      | set chain miss mapping
 *      | set fte_id
 *      | set tunnel_id
 *      | करो decap
 *      v
 * +---------------------+
 * + pre_ct/pre_ct_nat   +  अगर matches     +---------------------+
 * + zone+nat match      +---------------->+ post_ct (see below) +
 * +---------------------+  set zone       +---------------------+
 *      | set zone
 *      v
 * +--------------------+
 * + CT (nat or no nat) +
 * + tuple + zone match +
 * +--------------------+
 *      | set mark
 *      | set labels_id
 *      | set established
 *	| set zone_restore
 *      | करो nat (अगर needed)
 *      v
 * +--------------+
 * + post_ct      + original filter actions
 * + fte_id match +------------------------>
 * +--------------+
 */
अटल काष्ठा mlx5_flow_handle *
__mlx5_tc_ct_flow_offload(काष्ठा mlx5_tc_ct_priv *ct_priv,
			  काष्ठा mlx5e_tc_flow *flow,
			  काष्ठा mlx5_flow_spec *orig_spec,
			  काष्ठा mlx5_flow_attr *attr)
अणु
	bool nat = attr->ct_attr.ct_action & TCA_CT_ACT_NAT;
	काष्ठा mlx5e_priv *priv = netdev_priv(ct_priv->netdev);
	काष्ठा mlx5e_tc_mod_hdr_acts pre_mod_acts = अणुपूर्ण;
	u32 attr_sz = ns_to_attr_sz(ct_priv->ns_type);
	काष्ठा mlx5_flow_spec *post_ct_spec = शून्य;
	काष्ठा mlx5_flow_attr *pre_ct_attr;
	काष्ठा mlx5_modअगरy_hdr *mod_hdr;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_ct_flow *ct_flow;
	पूर्णांक chain_mapping = 0, err;
	काष्ठा mlx5_ct_ft *ft;
	u32 fte_id = 1;

	post_ct_spec = kvzalloc(माप(*post_ct_spec), GFP_KERNEL);
	ct_flow = kzalloc(माप(*ct_flow), GFP_KERNEL);
	अगर (!post_ct_spec || !ct_flow) अणु
		kvमुक्त(post_ct_spec);
		kमुक्त(ct_flow);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* Register क्रम CT established events */
	ft = mlx5_tc_ct_add_ft_cb(ct_priv, attr->ct_attr.zone,
				  attr->ct_attr.nf_ft);
	अगर (IS_ERR(ft)) अणु
		err = PTR_ERR(ft);
		ct_dbg("Failed to register to ft callback");
		जाओ err_ft;
	पूर्ण
	ct_flow->ft = ft;

	err = idr_alloc_u32(&ct_priv->fte_ids, ct_flow, &fte_id,
			    MLX5_FTE_ID_MAX, GFP_KERNEL);
	अगर (err) अणु
		netdev_warn(priv->netdev,
			    "Failed to allocate fte id, err: %d\n", err);
		जाओ err_idr;
	पूर्ण
	ct_flow->fte_id = fte_id;

	/* Base flow attributes of both rules on original rule attribute */
	ct_flow->pre_ct_attr = mlx5_alloc_flow_attr(ct_priv->ns_type);
	अगर (!ct_flow->pre_ct_attr) अणु
		err = -ENOMEM;
		जाओ err_alloc_pre;
	पूर्ण

	ct_flow->post_ct_attr = mlx5_alloc_flow_attr(ct_priv->ns_type);
	अगर (!ct_flow->post_ct_attr) अणु
		err = -ENOMEM;
		जाओ err_alloc_post;
	पूर्ण

	pre_ct_attr = ct_flow->pre_ct_attr;
	स_नकल(pre_ct_attr, attr, attr_sz);
	स_नकल(ct_flow->post_ct_attr, attr, attr_sz);

	/* Modअगरy the original rule's action to fwd and modअगरy, leave decap */
	pre_ct_attr->action = attr->action & MLX5_FLOW_CONTEXT_ACTION_DECAP;
	pre_ct_attr->action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST |
			       MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;

	/* Write chain miss tag क्रम miss in ct table as we
	 * करोn't go though all prios of this chain as normal tc rules
	 * miss.
	 */
	err = mlx5_chains_get_chain_mapping(ct_priv->chains, attr->chain,
					    &chain_mapping);
	अगर (err) अणु
		ct_dbg("Failed to get chain register mapping for chain");
		जाओ err_get_chain;
	पूर्ण
	ct_flow->chain_mapping = chain_mapping;

	err = mlx5e_tc_match_to_reg_set(priv->mdev, &pre_mod_acts, ct_priv->ns_type,
					CHAIN_TO_REG, chain_mapping);
	अगर (err) अणु
		ct_dbg("Failed to set chain register mapping");
		जाओ err_mapping;
	पूर्ण

	err = mlx5e_tc_match_to_reg_set(priv->mdev, &pre_mod_acts, ct_priv->ns_type,
					FTEID_TO_REG, fte_id);
	अगर (err) अणु
		ct_dbg("Failed to set fte_id register mapping");
		जाओ err_mapping;
	पूर्ण

	/* If original flow is decap, we करो it beक्रमe going पूर्णांकo ct table
	 * so add a reग_लिखो क्रम the tunnel match_id.
	 */
	अगर ((pre_ct_attr->action & MLX5_FLOW_CONTEXT_ACTION_DECAP) &&
	    attr->chain == 0) अणु
		u32 tun_id = mlx5e_tc_get_flow_tun_id(flow);

		err = mlx5e_tc_match_to_reg_set(priv->mdev, &pre_mod_acts,
						ct_priv->ns_type,
						TUNNEL_TO_REG,
						tun_id);
		अगर (err) अणु
			ct_dbg("Failed to set tunnel register mapping");
			जाओ err_mapping;
		पूर्ण
	पूर्ण

	mod_hdr = mlx5_modअगरy_header_alloc(priv->mdev, ct_priv->ns_type,
					   pre_mod_acts.num_actions,
					   pre_mod_acts.actions);
	अगर (IS_ERR(mod_hdr)) अणु
		err = PTR_ERR(mod_hdr);
		ct_dbg("Failed to create pre ct mod hdr");
		जाओ err_mapping;
	पूर्ण
	pre_ct_attr->modअगरy_hdr = mod_hdr;

	/* Post ct rule matches on fte_id and executes original rule's
	 * tc rule action
	 */
	mlx5e_tc_match_to_reg_match(post_ct_spec, FTEID_TO_REG,
				    fte_id, MLX5_FTE_ID_MASK);

	/* Put post_ct rule on post_ct flow table */
	ct_flow->post_ct_attr->chain = 0;
	ct_flow->post_ct_attr->prio = 0;
	ct_flow->post_ct_attr->ft = ct_priv->post_ct;

	/* Splits were handled beक्रमe CT */
	अगर (ct_priv->ns_type == MLX5_FLOW_NAMESPACE_FDB)
		ct_flow->post_ct_attr->esw_attr->split_count = 0;

	ct_flow->post_ct_attr->inner_match_level = MLX5_MATCH_NONE;
	ct_flow->post_ct_attr->outer_match_level = MLX5_MATCH_NONE;
	ct_flow->post_ct_attr->action &= ~(MLX5_FLOW_CONTEXT_ACTION_DECAP);
	rule = mlx5_tc_rule_insert(priv, post_ct_spec,
				   ct_flow->post_ct_attr);
	ct_flow->post_ct_rule = rule;
	अगर (IS_ERR(ct_flow->post_ct_rule)) अणु
		err = PTR_ERR(ct_flow->post_ct_rule);
		ct_dbg("Failed to add post ct rule");
		जाओ err_insert_post_ct;
	पूर्ण

	/* Change original rule poपूर्णांक to ct table */
	pre_ct_attr->dest_chain = 0;
	pre_ct_attr->dest_ft = nat ? ft->pre_ct_nat.ft : ft->pre_ct.ft;
	ct_flow->pre_ct_rule = mlx5_tc_rule_insert(priv, orig_spec,
						   pre_ct_attr);
	अगर (IS_ERR(ct_flow->pre_ct_rule)) अणु
		err = PTR_ERR(ct_flow->pre_ct_rule);
		ct_dbg("Failed to add pre ct rule");
		जाओ err_insert_orig;
	पूर्ण

	attr->ct_attr.ct_flow = ct_flow;
	dealloc_mod_hdr_actions(&pre_mod_acts);
	kvमुक्त(post_ct_spec);

	वापस rule;

err_insert_orig:
	mlx5_tc_rule_delete(priv, ct_flow->post_ct_rule,
			    ct_flow->post_ct_attr);
err_insert_post_ct:
	mlx5_modअगरy_header_dealloc(priv->mdev, pre_ct_attr->modअगरy_hdr);
err_mapping:
	dealloc_mod_hdr_actions(&pre_mod_acts);
	mlx5_chains_put_chain_mapping(ct_priv->chains, ct_flow->chain_mapping);
err_get_chain:
	kमुक्त(ct_flow->post_ct_attr);
err_alloc_post:
	kमुक्त(ct_flow->pre_ct_attr);
err_alloc_pre:
	idr_हटाओ(&ct_priv->fte_ids, fte_id);
err_idr:
	mlx5_tc_ct_del_ft_cb(ct_priv, ft);
err_ft:
	kvमुक्त(post_ct_spec);
	kमुक्त(ct_flow);
	netdev_warn(priv->netdev, "Failed to offload ct flow, err %d\n", err);
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा mlx5_flow_handle *
__mlx5_tc_ct_flow_offload_clear(काष्ठा mlx5_tc_ct_priv *ct_priv,
				काष्ठा mlx5_flow_spec *orig_spec,
				काष्ठा mlx5_flow_attr *attr,
				काष्ठा mlx5e_tc_mod_hdr_acts *mod_acts)
अणु
	काष्ठा mlx5e_priv *priv = netdev_priv(ct_priv->netdev);
	u32 attr_sz = ns_to_attr_sz(ct_priv->ns_type);
	काष्ठा mlx5_flow_attr *pre_ct_attr;
	काष्ठा mlx5_modअगरy_hdr *mod_hdr;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_ct_flow *ct_flow;
	पूर्णांक err;

	ct_flow = kzalloc(माप(*ct_flow), GFP_KERNEL);
	अगर (!ct_flow)
		वापस ERR_PTR(-ENOMEM);

	/* Base esw attributes on original rule attribute */
	pre_ct_attr = mlx5_alloc_flow_attr(ct_priv->ns_type);
	अगर (!pre_ct_attr) अणु
		err = -ENOMEM;
		जाओ err_attr;
	पूर्ण

	स_नकल(pre_ct_attr, attr, attr_sz);

	err = mlx5_tc_ct_entry_set_रेजिस्टरs(ct_priv, mod_acts, 0, 0, 0, 0);
	अगर (err) अणु
		ct_dbg("Failed to set register for ct clear");
		जाओ err_set_रेजिस्टरs;
	पूर्ण

	mod_hdr = mlx5_modअगरy_header_alloc(priv->mdev, ct_priv->ns_type,
					   mod_acts->num_actions,
					   mod_acts->actions);
	अगर (IS_ERR(mod_hdr)) अणु
		err = PTR_ERR(mod_hdr);
		ct_dbg("Failed to add create ct clear mod hdr");
		जाओ err_set_रेजिस्टरs;
	पूर्ण

	pre_ct_attr->modअगरy_hdr = mod_hdr;
	pre_ct_attr->action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;

	rule = mlx5_tc_rule_insert(priv, orig_spec, pre_ct_attr);
	अगर (IS_ERR(rule)) अणु
		err = PTR_ERR(rule);
		ct_dbg("Failed to add ct clear rule");
		जाओ err_insert;
	पूर्ण

	attr->ct_attr.ct_flow = ct_flow;
	ct_flow->pre_ct_attr = pre_ct_attr;
	ct_flow->pre_ct_rule = rule;
	वापस rule;

err_insert:
	mlx5_modअगरy_header_dealloc(priv->mdev, mod_hdr);
err_set_रेजिस्टरs:
	netdev_warn(priv->netdev,
		    "Failed to offload ct clear flow, err %d\n", err);
	kमुक्त(pre_ct_attr);
err_attr:
	kमुक्त(ct_flow);

	वापस ERR_PTR(err);
पूर्ण

काष्ठा mlx5_flow_handle *
mlx5_tc_ct_flow_offload(काष्ठा mlx5_tc_ct_priv *priv,
			काष्ठा mlx5e_tc_flow *flow,
			काष्ठा mlx5_flow_spec *spec,
			काष्ठा mlx5_flow_attr *attr,
			काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts)
अणु
	bool clear_action = attr->ct_attr.ct_action & TCA_CT_ACT_CLEAR;
	काष्ठा mlx5_flow_handle *rule;

	अगर (!priv)
		वापस ERR_PTR(-EOPNOTSUPP);

	mutex_lock(&priv->control_lock);

	अगर (clear_action)
		rule = __mlx5_tc_ct_flow_offload_clear(priv, spec, attr, mod_hdr_acts);
	अन्यथा
		rule = __mlx5_tc_ct_flow_offload(priv, flow, spec, attr);
	mutex_unlock(&priv->control_lock);

	वापस rule;
पूर्ण

अटल व्योम
__mlx5_tc_ct_delete_flow(काष्ठा mlx5_tc_ct_priv *ct_priv,
			 काष्ठा mlx5e_tc_flow *flow,
			 काष्ठा mlx5_ct_flow *ct_flow)
अणु
	काष्ठा mlx5_flow_attr *pre_ct_attr = ct_flow->pre_ct_attr;
	काष्ठा mlx5e_priv *priv = netdev_priv(ct_priv->netdev);

	mlx5_tc_rule_delete(priv, ct_flow->pre_ct_rule,
			    pre_ct_attr);
	mlx5_modअगरy_header_dealloc(priv->mdev, pre_ct_attr->modअगरy_hdr);

	अगर (ct_flow->post_ct_rule) अणु
		mlx5_tc_rule_delete(priv, ct_flow->post_ct_rule,
				    ct_flow->post_ct_attr);
		mlx5_chains_put_chain_mapping(ct_priv->chains, ct_flow->chain_mapping);
		idr_हटाओ(&ct_priv->fte_ids, ct_flow->fte_id);
		mlx5_tc_ct_del_ft_cb(ct_priv, ct_flow->ft);
	पूर्ण

	kमुक्त(ct_flow->pre_ct_attr);
	kमुक्त(ct_flow->post_ct_attr);
	kमुक्त(ct_flow);
पूर्ण

व्योम
mlx5_tc_ct_delete_flow(काष्ठा mlx5_tc_ct_priv *priv,
		       काष्ठा mlx5e_tc_flow *flow,
		       काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_ct_flow *ct_flow = attr->ct_attr.ct_flow;

	/* We are called on error to clean up stuff from parsing
	 * but we करोn't have anything क्रम now
	 */
	अगर (!ct_flow)
		वापस;

	mutex_lock(&priv->control_lock);
	__mlx5_tc_ct_delete_flow(priv, flow, ct_flow);
	mutex_unlock(&priv->control_lock);
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_init_check_esw_support(काष्ठा mlx5_eचयन *esw,
				  स्थिर अक्षर **err_msg)
अणु
	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, ignore_flow_level)) अणु
		*err_msg = "firmware level support is missing";
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!mlx5_eचयन_vlan_actions_supported(esw->dev, 1)) अणु
		/* vlan workaround should be aव्योमed क्रम multi chain rules.
		 * This is just a sanity check as pop vlan action should
		 * be supported by any FW that supports ignore_flow_level
		 */

		*err_msg = "firmware vlan actions support is missing";
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!MLX5_CAP_ESW_FLOWTABLE(esw->dev,
				    fdb_modअगरy_header_fwd_to_table)) अणु
		/* CT always ग_लिखोs to रेजिस्टरs which are mod header actions.
		 * Thereक्रमe, mod header and जाओ is required
		 */

		*err_msg = "firmware fwd and modify support is missing";
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!mlx5_eचयन_reg_c1_loopback_enabled(esw)) अणु
		*err_msg = "register loopback isn't supported";
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_init_check_nic_support(काष्ठा mlx5e_priv *priv,
				  स्थिर अक्षर **err_msg)
अणु
	अगर (!MLX5_CAP_FLOWTABLE_NIC_RX(priv->mdev, ignore_flow_level)) अणु
		*err_msg = "firmware level support is missing";
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_tc_ct_init_check_support(काष्ठा mlx5e_priv *priv,
			      क्रमागत mlx5_flow_namespace_type ns_type,
			      स्थिर अक्षर **err_msg)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

#अगर !IS_ENABLED(CONFIG_NET_TC_SKB_EXT)
	/* cannot restore chain ID on HW miss */

	*err_msg = "tc skb extension missing";
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
	अगर (ns_type == MLX5_FLOW_NAMESPACE_FDB)
		वापस mlx5_tc_ct_init_check_esw_support(esw, err_msg);
	अन्यथा
		वापस mlx5_tc_ct_init_check_nic_support(priv, err_msg);
पूर्ण

#घोषणा INIT_ERR_PREFIX "tc ct offload init failed"

काष्ठा mlx5_tc_ct_priv *
mlx5_tc_ct_init(काष्ठा mlx5e_priv *priv, काष्ठा mlx5_fs_chains *chains,
		काष्ठा mod_hdr_tbl *mod_hdr,
		क्रमागत mlx5_flow_namespace_type ns_type)
अणु
	काष्ठा mlx5_tc_ct_priv *ct_priv;
	काष्ठा mlx5_core_dev *dev;
	स्थिर अक्षर *msg;
	पूर्णांक err;

	dev = priv->mdev;
	err = mlx5_tc_ct_init_check_support(priv, ns_type, &msg);
	अगर (err) अणु
		mlx5_core_warn(dev,
			       "tc ct offload not supported, %s\n",
			       msg);
		जाओ err_support;
	पूर्ण

	ct_priv = kzalloc(माप(*ct_priv), GFP_KERNEL);
	अगर (!ct_priv)
		जाओ err_alloc;

	ct_priv->zone_mapping = mapping_create(माप(u16), 0, true);
	अगर (IS_ERR(ct_priv->zone_mapping)) अणु
		err = PTR_ERR(ct_priv->zone_mapping);
		जाओ err_mapping_zone;
	पूर्ण

	ct_priv->labels_mapping = mapping_create(माप(u32) * 4, 0, true);
	अगर (IS_ERR(ct_priv->labels_mapping)) अणु
		err = PTR_ERR(ct_priv->labels_mapping);
		जाओ err_mapping_labels;
	पूर्ण

	spin_lock_init(&ct_priv->ht_lock);
	ct_priv->ns_type = ns_type;
	ct_priv->chains = chains;
	ct_priv->netdev = priv->netdev;
	ct_priv->dev = priv->mdev;
	ct_priv->mod_hdr_tbl = mod_hdr;
	ct_priv->ct = mlx5_chains_create_global_table(chains);
	अगर (IS_ERR(ct_priv->ct)) अणु
		err = PTR_ERR(ct_priv->ct);
		mlx5_core_warn(dev,
			       "%s, failed to create ct table err: %d\n",
			       INIT_ERR_PREFIX, err);
		जाओ err_ct_tbl;
	पूर्ण

	ct_priv->ct_nat = mlx5_chains_create_global_table(chains);
	अगर (IS_ERR(ct_priv->ct_nat)) अणु
		err = PTR_ERR(ct_priv->ct_nat);
		mlx5_core_warn(dev,
			       "%s, failed to create ct nat table err: %d\n",
			       INIT_ERR_PREFIX, err);
		जाओ err_ct_nat_tbl;
	पूर्ण

	ct_priv->post_ct = mlx5_chains_create_global_table(chains);
	अगर (IS_ERR(ct_priv->post_ct)) अणु
		err = PTR_ERR(ct_priv->post_ct);
		mlx5_core_warn(dev,
			       "%s, failed to create post ct table err: %d\n",
			       INIT_ERR_PREFIX, err);
		जाओ err_post_ct_tbl;
	पूर्ण

	idr_init(&ct_priv->fte_ids);
	mutex_init(&ct_priv->control_lock);
	rhashtable_init(&ct_priv->zone_ht, &zone_params);
	rhashtable_init(&ct_priv->ct_tuples_ht, &tuples_ht_params);
	rhashtable_init(&ct_priv->ct_tuples_nat_ht, &tuples_nat_ht_params);

	वापस ct_priv;

err_post_ct_tbl:
	mlx5_chains_destroy_global_table(chains, ct_priv->ct_nat);
err_ct_nat_tbl:
	mlx5_chains_destroy_global_table(chains, ct_priv->ct);
err_ct_tbl:
	mapping_destroy(ct_priv->labels_mapping);
err_mapping_labels:
	mapping_destroy(ct_priv->zone_mapping);
err_mapping_zone:
	kमुक्त(ct_priv);
err_alloc:
err_support:

	वापस शून्य;
पूर्ण

व्योम
mlx5_tc_ct_clean(काष्ठा mlx5_tc_ct_priv *ct_priv)
अणु
	काष्ठा mlx5_fs_chains *chains;

	अगर (!ct_priv)
		वापस;

	chains = ct_priv->chains;

	mlx5_chains_destroy_global_table(chains, ct_priv->post_ct);
	mlx5_chains_destroy_global_table(chains, ct_priv->ct_nat);
	mlx5_chains_destroy_global_table(chains, ct_priv->ct);
	mapping_destroy(ct_priv->zone_mapping);
	mapping_destroy(ct_priv->labels_mapping);

	rhashtable_destroy(&ct_priv->ct_tuples_ht);
	rhashtable_destroy(&ct_priv->ct_tuples_nat_ht);
	rhashtable_destroy(&ct_priv->zone_ht);
	mutex_destroy(&ct_priv->control_lock);
	idr_destroy(&ct_priv->fte_ids);
	kमुक्त(ct_priv);
पूर्ण

bool
mlx5e_tc_ct_restore_flow(काष्ठा mlx5_tc_ct_priv *ct_priv,
			 काष्ठा sk_buff *skb, u8 zone_restore_id)
अणु
	काष्ठा mlx5_ct_tuple tuple = अणुपूर्ण;
	काष्ठा mlx5_ct_entry *entry;
	u16 zone;

	अगर (!ct_priv || !zone_restore_id)
		वापस true;

	अगर (mapping_find(ct_priv->zone_mapping, zone_restore_id, &zone))
		वापस false;

	अगर (!mlx5_tc_ct_skb_to_tuple(skb, &tuple, zone))
		वापस false;

	spin_lock(&ct_priv->ht_lock);

	entry = mlx5_tc_ct_entry_get(ct_priv, &tuple);
	अगर (!entry) अणु
		spin_unlock(&ct_priv->ht_lock);
		वापस false;
	पूर्ण

	अगर (IS_ERR(entry)) अणु
		spin_unlock(&ct_priv->ht_lock);
		वापस false;
	पूर्ण
	spin_unlock(&ct_priv->ht_lock);

	tcf_ct_flow_table_restore_skb(skb, entry->restore_cookie);
	__mlx5_tc_ct_entry_put(entry);

	वापस true;
पूर्ण
