<शैली गुरु>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/tc_act/tc_csum.h>
#समावेश <net/flow_offload.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>

अटल काष्ठा workqueue_काष्ठा *nf_flow_offload_add_wq;
अटल काष्ठा workqueue_काष्ठा *nf_flow_offload_del_wq;
अटल काष्ठा workqueue_काष्ठा *nf_flow_offload_stats_wq;

काष्ठा flow_offload_work अणु
	काष्ठा list_head	list;
	क्रमागत flow_cls_command	cmd;
	पूर्णांक			priority;
	काष्ठा nf_flowtable	*flowtable;
	काष्ठा flow_offload	*flow;
	काष्ठा work_काष्ठा	work;
पूर्ण;

#घोषणा NF_FLOW_DISSECTOR(__match, __type, __field)	\
	(__match)->dissector.offset[__type] =		\
		दुरत्व(काष्ठा nf_flow_key, __field)

अटल व्योम nf_flow_rule_lwt_match(काष्ठा nf_flow_match *match,
				   काष्ठा ip_tunnel_info *tun_info)
अणु
	काष्ठा nf_flow_key *mask = &match->mask;
	काष्ठा nf_flow_key *key = &match->key;
	अचिन्हित पूर्णांक enc_keys;

	अगर (!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX))
		वापस;

	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_ENC_CONTROL, enc_control);
	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_ENC_KEYID, enc_key_id);
	key->enc_key_id.keyid = tunnel_id_to_key32(tun_info->key.tun_id);
	mask->enc_key_id.keyid = 0xffffffff;
	enc_keys = BIT(FLOW_DISSECTOR_KEY_ENC_KEYID) |
		   BIT(FLOW_DISSECTOR_KEY_ENC_CONTROL);

	अगर (ip_tunnel_info_af(tun_info) == AF_INET) अणु
		NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS,
				  enc_ipv4);
		key->enc_ipv4.src = tun_info->key.u.ipv4.dst;
		key->enc_ipv4.dst = tun_info->key.u.ipv4.src;
		अगर (key->enc_ipv4.src)
			mask->enc_ipv4.src = 0xffffffff;
		अगर (key->enc_ipv4.dst)
			mask->enc_ipv4.dst = 0xffffffff;
		enc_keys |= BIT(FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS);
		key->enc_control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
	पूर्ण अन्यथा अणु
		स_नकल(&key->enc_ipv6.src, &tun_info->key.u.ipv6.dst,
		       माप(काष्ठा in6_addr));
		स_नकल(&key->enc_ipv6.dst, &tun_info->key.u.ipv6.src,
		       माप(काष्ठा in6_addr));
		अगर (स_भेद(&key->enc_ipv6.src, &in6addr_any,
			   माप(काष्ठा in6_addr)))
			स_रखो(&key->enc_ipv6.src, 0xff,
			       माप(काष्ठा in6_addr));
		अगर (स_भेद(&key->enc_ipv6.dst, &in6addr_any,
			   माप(काष्ठा in6_addr)))
			स_रखो(&key->enc_ipv6.dst, 0xff,
			       माप(काष्ठा in6_addr));
		enc_keys |= BIT(FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS);
		key->enc_control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
	पूर्ण

	match->dissector.used_keys |= enc_keys;
पूर्ण

अटल व्योम nf_flow_rule_vlan_match(काष्ठा flow_dissector_key_vlan *key,
				    काष्ठा flow_dissector_key_vlan *mask,
				    u16 vlan_id, __be16 proto)
अणु
	key->vlan_id = vlan_id;
	mask->vlan_id = VLAN_VID_MASK;
	key->vlan_tpid = proto;
	mask->vlan_tpid = 0xffff;
पूर्ण

अटल पूर्णांक nf_flow_rule_match(काष्ठा nf_flow_match *match,
			      स्थिर काष्ठा flow_offload_tuple *tuple,
			      काष्ठा dst_entry *other_dst)
अणु
	काष्ठा nf_flow_key *mask = &match->mask;
	काष्ठा nf_flow_key *key = &match->key;
	काष्ठा ip_tunnel_info *tun_info;
	bool vlan_encap = false;

	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_META, meta);
	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_CONTROL, control);
	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_BASIC, basic);
	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_IPV4_ADDRS, ipv4);
	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_IPV6_ADDRS, ipv6);
	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_TCP, tcp);
	NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_PORTS, tp);

	अगर (other_dst && other_dst->lwtstate) अणु
		tun_info = lwt_tun_info(other_dst->lwtstate);
		nf_flow_rule_lwt_match(match, tun_info);
	पूर्ण

	key->meta.ingress_अगरindex = tuple->iअगरidx;
	mask->meta.ingress_अगरindex = 0xffffffff;

	अगर (tuple->encap_num > 0 && !(tuple->in_vlan_ingress & BIT(0)) &&
	    tuple->encap[0].proto == htons(ETH_P_8021Q)) अणु
		NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_VLAN, vlan);
		nf_flow_rule_vlan_match(&key->vlan, &mask->vlan,
					tuple->encap[0].id,
					tuple->encap[0].proto);
		vlan_encap = true;
	पूर्ण

	अगर (tuple->encap_num > 1 && !(tuple->in_vlan_ingress & BIT(1)) &&
	    tuple->encap[1].proto == htons(ETH_P_8021Q)) अणु
		अगर (vlan_encap) अणु
			NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_CVLAN,
					  cvlan);
			nf_flow_rule_vlan_match(&key->cvlan, &mask->cvlan,
						tuple->encap[1].id,
						tuple->encap[1].proto);
		पूर्ण अन्यथा अणु
			NF_FLOW_DISSECTOR(match, FLOW_DISSECTOR_KEY_VLAN,
					  vlan);
			nf_flow_rule_vlan_match(&key->vlan, &mask->vlan,
						tuple->encap[1].id,
						tuple->encap[1].proto);
		पूर्ण
	पूर्ण

	चयन (tuple->l3proto) अणु
	हाल AF_INET:
		key->control.addr_type = FLOW_DISSECTOR_KEY_IPV4_ADDRS;
		key->basic.n_proto = htons(ETH_P_IP);
		key->ipv4.src = tuple->src_v4.s_addr;
		mask->ipv4.src = 0xffffffff;
		key->ipv4.dst = tuple->dst_v4.s_addr;
		mask->ipv4.dst = 0xffffffff;
		अवरोध;
       हाल AF_INET6:
		key->control.addr_type = FLOW_DISSECTOR_KEY_IPV6_ADDRS;
		key->basic.n_proto = htons(ETH_P_IPV6);
		key->ipv6.src = tuple->src_v6;
		स_रखो(&mask->ipv6.src, 0xff, माप(mask->ipv6.src));
		key->ipv6.dst = tuple->dst_v6;
		स_रखो(&mask->ipv6.dst, 0xff, माप(mask->ipv6.dst));
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	mask->control.addr_type = 0xffff;
	match->dissector.used_keys |= BIT(key->control.addr_type);
	mask->basic.n_proto = 0xffff;

	चयन (tuple->l4proto) अणु
	हाल IPPROTO_TCP:
		key->tcp.flags = 0;
		mask->tcp.flags = cpu_to_be16(be32_to_cpu(TCP_FLAG_RST | TCP_FLAG_FIN) >> 16);
		match->dissector.used_keys |= BIT(FLOW_DISSECTOR_KEY_TCP);
		अवरोध;
	हाल IPPROTO_UDP:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	key->basic.ip_proto = tuple->l4proto;
	mask->basic.ip_proto = 0xff;

	key->tp.src = tuple->src_port;
	mask->tp.src = 0xffff;
	key->tp.dst = tuple->dst_port;
	mask->tp.dst = 0xffff;

	match->dissector.used_keys |= BIT(FLOW_DISSECTOR_KEY_META) |
				      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
				      BIT(FLOW_DISSECTOR_KEY_BASIC) |
				      BIT(FLOW_DISSECTOR_KEY_PORTS);
	वापस 0;
पूर्ण

अटल व्योम flow_offload_mangle(काष्ठा flow_action_entry *entry,
				क्रमागत flow_action_mangle_base htype, u32 offset,
				स्थिर __be32 *value, स्थिर __be32 *mask)
अणु
	entry->id = FLOW_ACTION_MANGLE;
	entry->mangle.htype = htype;
	entry->mangle.offset = offset;
	स_नकल(&entry->mangle.mask, mask, माप(u32));
	स_नकल(&entry->mangle.val, value, माप(u32));
पूर्ण

अटल अंतरभूत काष्ठा flow_action_entry *
flow_action_entry_next(काष्ठा nf_flow_rule *flow_rule)
अणु
	पूर्णांक i = flow_rule->rule->action.num_entries++;

	वापस &flow_rule->rule->action.entries[i];
पूर्ण

अटल पूर्णांक flow_offload_eth_src(काष्ठा net *net,
				स्थिर काष्ठा flow_offload *flow,
				क्रमागत flow_offload_tuple_dir dir,
				काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action_entry *entry0 = flow_action_entry_next(flow_rule);
	काष्ठा flow_action_entry *entry1 = flow_action_entry_next(flow_rule);
	स्थिर काष्ठा flow_offload_tuple *other_tuple, *this_tuple;
	काष्ठा net_device *dev = शून्य;
	स्थिर अचिन्हित अक्षर *addr;
	u32 mask, val;
	u16 val16;

	this_tuple = &flow->tuplehash[dir].tuple;

	चयन (this_tuple->xmit_type) अणु
	हाल FLOW_OFFLOAD_XMIT_सूचीECT:
		addr = this_tuple->out.h_source;
		अवरोध;
	हाल FLOW_OFFLOAD_XMIT_NEIGH:
		other_tuple = &flow->tuplehash[!dir].tuple;
		dev = dev_get_by_index(net, other_tuple->iअगरidx);
		अगर (!dev)
			वापस -ENOENT;

		addr = dev->dev_addr;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mask = ~0xffff0000;
	स_नकल(&val16, addr, 2);
	val = val16 << 16;
	flow_offload_mangle(entry0, FLOW_ACT_MANGLE_HDR_TYPE_ETH, 4,
			    &val, &mask);

	mask = ~0xffffffff;
	स_नकल(&val, addr + 2, 4);
	flow_offload_mangle(entry1, FLOW_ACT_MANGLE_HDR_TYPE_ETH, 8,
			    &val, &mask);

	अगर (dev)
		dev_put(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक flow_offload_eth_dst(काष्ठा net *net,
				स्थिर काष्ठा flow_offload *flow,
				क्रमागत flow_offload_tuple_dir dir,
				काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action_entry *entry0 = flow_action_entry_next(flow_rule);
	काष्ठा flow_action_entry *entry1 = flow_action_entry_next(flow_rule);
	स्थिर काष्ठा flow_offload_tuple *other_tuple, *this_tuple;
	स्थिर काष्ठा dst_entry *dst_cache;
	अचिन्हित अक्षर ha[ETH_ALEN];
	काष्ठा neighbour *n;
	स्थिर व्योम *daddr;
	u32 mask, val;
	u8 nud_state;
	u16 val16;

	this_tuple = &flow->tuplehash[dir].tuple;

	चयन (this_tuple->xmit_type) अणु
	हाल FLOW_OFFLOAD_XMIT_सूचीECT:
		ether_addr_copy(ha, this_tuple->out.h_dest);
		अवरोध;
	हाल FLOW_OFFLOAD_XMIT_NEIGH:
		other_tuple = &flow->tuplehash[!dir].tuple;
		daddr = &other_tuple->src_v4;
		dst_cache = this_tuple->dst_cache;
		n = dst_neigh_lookup(dst_cache, daddr);
		अगर (!n)
			वापस -ENOENT;

		पढ़ो_lock_bh(&n->lock);
		nud_state = n->nud_state;
		ether_addr_copy(ha, n->ha);
		पढ़ो_unlock_bh(&n->lock);
		neigh_release(n);

		अगर (!(nud_state & NUD_VALID))
			वापस -ENOENT;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	mask = ~0xffffffff;
	स_नकल(&val, ha, 4);
	flow_offload_mangle(entry0, FLOW_ACT_MANGLE_HDR_TYPE_ETH, 0,
			    &val, &mask);

	mask = ~0x0000ffff;
	स_नकल(&val16, ha + 4, 2);
	val = val16;
	flow_offload_mangle(entry1, FLOW_ACT_MANGLE_HDR_TYPE_ETH, 4,
			    &val, &mask);

	वापस 0;
पूर्ण

अटल व्योम flow_offload_ipv4_snat(काष्ठा net *net,
				   स्थिर काष्ठा flow_offload *flow,
				   क्रमागत flow_offload_tuple_dir dir,
				   काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action_entry *entry = flow_action_entry_next(flow_rule);
	u32 mask = ~htonl(0xffffffff);
	__be32 addr;
	u32 offset;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.dst_v4.s_addr;
		offset = दुरत्व(काष्ठा iphdr, saddr);
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.src_v4.s_addr;
		offset = दुरत्व(काष्ठा iphdr, daddr);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	flow_offload_mangle(entry, FLOW_ACT_MANGLE_HDR_TYPE_IP4, offset,
			    &addr, &mask);
पूर्ण

अटल व्योम flow_offload_ipv4_dnat(काष्ठा net *net,
				   स्थिर काष्ठा flow_offload *flow,
				   क्रमागत flow_offload_tuple_dir dir,
				   काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action_entry *entry = flow_action_entry_next(flow_rule);
	u32 mask = ~htonl(0xffffffff);
	__be32 addr;
	u32 offset;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.src_v4.s_addr;
		offset = दुरत्व(काष्ठा iphdr, daddr);
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.dst_v4.s_addr;
		offset = दुरत्व(काष्ठा iphdr, saddr);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	flow_offload_mangle(entry, FLOW_ACT_MANGLE_HDR_TYPE_IP4, offset,
			    &addr, &mask);
पूर्ण

अटल व्योम flow_offload_ipv6_mangle(काष्ठा nf_flow_rule *flow_rule,
				     अचिन्हित पूर्णांक offset,
				     स्थिर __be32 *addr, स्थिर __be32 *mask)
अणु
	काष्ठा flow_action_entry *entry;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < माप(काष्ठा in6_addr) / माप(u32); i += माप(u32), j++) अणु
		entry = flow_action_entry_next(flow_rule);
		flow_offload_mangle(entry, FLOW_ACT_MANGLE_HDR_TYPE_IP6,
				    offset + i, &addr[j], mask);
	पूर्ण
पूर्ण

अटल व्योम flow_offload_ipv6_snat(काष्ठा net *net,
				   स्थिर काष्ठा flow_offload *flow,
				   क्रमागत flow_offload_tuple_dir dir,
				   काष्ठा nf_flow_rule *flow_rule)
अणु
	u32 mask = ~htonl(0xffffffff);
	स्थिर __be32 *addr;
	u32 offset;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.dst_v6.s6_addr32;
		offset = दुरत्व(काष्ठा ipv6hdr, saddr);
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.src_v6.s6_addr32;
		offset = दुरत्व(काष्ठा ipv6hdr, daddr);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	flow_offload_ipv6_mangle(flow_rule, offset, addr, &mask);
पूर्ण

अटल व्योम flow_offload_ipv6_dnat(काष्ठा net *net,
				   स्थिर काष्ठा flow_offload *flow,
				   क्रमागत flow_offload_tuple_dir dir,
				   काष्ठा nf_flow_rule *flow_rule)
अणु
	u32 mask = ~htonl(0xffffffff);
	स्थिर __be32 *addr;
	u32 offset;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.src_v6.s6_addr32;
		offset = दुरत्व(काष्ठा ipv6hdr, daddr);
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		addr = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.dst_v6.s6_addr32;
		offset = दुरत्व(काष्ठा ipv6hdr, saddr);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	flow_offload_ipv6_mangle(flow_rule, offset, addr, &mask);
पूर्ण

अटल पूर्णांक flow_offload_l4proto(स्थिर काष्ठा flow_offload *flow)
अणु
	u8 protonum = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.l4proto;
	u8 type = 0;

	चयन (protonum) अणु
	हाल IPPROTO_TCP:
		type = FLOW_ACT_MANGLE_HDR_TYPE_TCP;
		अवरोध;
	हाल IPPROTO_UDP:
		type = FLOW_ACT_MANGLE_HDR_TYPE_UDP;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस type;
पूर्ण

अटल व्योम flow_offload_port_snat(काष्ठा net *net,
				   स्थिर काष्ठा flow_offload *flow,
				   क्रमागत flow_offload_tuple_dir dir,
				   काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action_entry *entry = flow_action_entry_next(flow_rule);
	u32 mask, port;
	u32 offset;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		port = ntohs(flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.dst_port);
		offset = 0; /* दुरत्व(काष्ठा tcphdr, source); */
		port = htonl(port << 16);
		mask = ~htonl(0xffff0000);
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		port = ntohs(flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.src_port);
		offset = 0; /* दुरत्व(काष्ठा tcphdr, dest); */
		port = htonl(port);
		mask = ~htonl(0xffff);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	flow_offload_mangle(entry, flow_offload_l4proto(flow), offset,
			    &port, &mask);
पूर्ण

अटल व्योम flow_offload_port_dnat(काष्ठा net *net,
				   स्थिर काष्ठा flow_offload *flow,
				   क्रमागत flow_offload_tuple_dir dir,
				   काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action_entry *entry = flow_action_entry_next(flow_rule);
	u32 mask, port;
	u32 offset;

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		port = ntohs(flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.src_port);
		offset = 0; /* दुरत्व(काष्ठा tcphdr, dest); */
		port = htonl(port);
		mask = ~htonl(0xffff);
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		port = ntohs(flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.dst_port);
		offset = 0; /* दुरत्व(काष्ठा tcphdr, source); */
		port = htonl(port << 16);
		mask = ~htonl(0xffff0000);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	flow_offload_mangle(entry, flow_offload_l4proto(flow), offset,
			    &port, &mask);
पूर्ण

अटल व्योम flow_offload_ipv4_checksum(काष्ठा net *net,
				       स्थिर काष्ठा flow_offload *flow,
				       काष्ठा nf_flow_rule *flow_rule)
अणु
	u8 protonum = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.l4proto;
	काष्ठा flow_action_entry *entry = flow_action_entry_next(flow_rule);

	entry->id = FLOW_ACTION_CSUM;
	entry->csum_flags = TCA_CSUM_UPDATE_FLAG_IPV4HDR;

	चयन (protonum) अणु
	हाल IPPROTO_TCP:
		entry->csum_flags |= TCA_CSUM_UPDATE_FLAG_TCP;
		अवरोध;
	हाल IPPROTO_UDP:
		entry->csum_flags |= TCA_CSUM_UPDATE_FLAG_UDP;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम flow_offload_redirect(काष्ठा net *net,
				  स्थिर काष्ठा flow_offload *flow,
				  क्रमागत flow_offload_tuple_dir dir,
				  काष्ठा nf_flow_rule *flow_rule)
अणु
	स्थिर काष्ठा flow_offload_tuple *this_tuple, *other_tuple;
	काष्ठा flow_action_entry *entry;
	काष्ठा net_device *dev;
	पूर्णांक अगरindex;

	this_tuple = &flow->tuplehash[dir].tuple;
	चयन (this_tuple->xmit_type) अणु
	हाल FLOW_OFFLOAD_XMIT_सूचीECT:
		this_tuple = &flow->tuplehash[dir].tuple;
		अगरindex = this_tuple->out.hw_अगरidx;
		अवरोध;
	हाल FLOW_OFFLOAD_XMIT_NEIGH:
		other_tuple = &flow->tuplehash[!dir].tuple;
		अगरindex = other_tuple->iअगरidx;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	dev = dev_get_by_index(net, अगरindex);
	अगर (!dev)
		वापस;

	entry = flow_action_entry_next(flow_rule);
	entry->id = FLOW_ACTION_REसूचीECT;
	entry->dev = dev;
पूर्ण

अटल व्योम flow_offload_encap_tunnel(स्थिर काष्ठा flow_offload *flow,
				      क्रमागत flow_offload_tuple_dir dir,
				      काष्ठा nf_flow_rule *flow_rule)
अणु
	स्थिर काष्ठा flow_offload_tuple *this_tuple;
	काष्ठा flow_action_entry *entry;
	काष्ठा dst_entry *dst;

	this_tuple = &flow->tuplehash[dir].tuple;
	अगर (this_tuple->xmit_type == FLOW_OFFLOAD_XMIT_सूचीECT)
		वापस;

	dst = this_tuple->dst_cache;
	अगर (dst && dst->lwtstate) अणु
		काष्ठा ip_tunnel_info *tun_info;

		tun_info = lwt_tun_info(dst->lwtstate);
		अगर (tun_info && (tun_info->mode & IP_TUNNEL_INFO_TX)) अणु
			entry = flow_action_entry_next(flow_rule);
			entry->id = FLOW_ACTION_TUNNEL_ENCAP;
			entry->tunnel = tun_info;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम flow_offload_decap_tunnel(स्थिर काष्ठा flow_offload *flow,
				      क्रमागत flow_offload_tuple_dir dir,
				      काष्ठा nf_flow_rule *flow_rule)
अणु
	स्थिर काष्ठा flow_offload_tuple *other_tuple;
	काष्ठा flow_action_entry *entry;
	काष्ठा dst_entry *dst;

	other_tuple = &flow->tuplehash[!dir].tuple;
	अगर (other_tuple->xmit_type == FLOW_OFFLOAD_XMIT_सूचीECT)
		वापस;

	dst = other_tuple->dst_cache;
	अगर (dst && dst->lwtstate) अणु
		काष्ठा ip_tunnel_info *tun_info;

		tun_info = lwt_tun_info(dst->lwtstate);
		अगर (tun_info && (tun_info->mode & IP_TUNNEL_INFO_TX)) अणु
			entry = flow_action_entry_next(flow_rule);
			entry->id = FLOW_ACTION_TUNNEL_DECAP;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
nf_flow_rule_route_common(काष्ठा net *net, स्थिर काष्ठा flow_offload *flow,
			  क्रमागत flow_offload_tuple_dir dir,
			  काष्ठा nf_flow_rule *flow_rule)
अणु
	स्थिर काष्ठा flow_offload_tuple *other_tuple;
	स्थिर काष्ठा flow_offload_tuple *tuple;
	पूर्णांक i;

	flow_offload_decap_tunnel(flow, dir, flow_rule);
	flow_offload_encap_tunnel(flow, dir, flow_rule);

	अगर (flow_offload_eth_src(net, flow, dir, flow_rule) < 0 ||
	    flow_offload_eth_dst(net, flow, dir, flow_rule) < 0)
		वापस -1;

	tuple = &flow->tuplehash[dir].tuple;

	क्रम (i = 0; i < tuple->encap_num; i++) अणु
		काष्ठा flow_action_entry *entry;

		अगर (tuple->in_vlan_ingress & BIT(i))
			जारी;

		अगर (tuple->encap[i].proto == htons(ETH_P_8021Q)) अणु
			entry = flow_action_entry_next(flow_rule);
			entry->id = FLOW_ACTION_VLAN_POP;
		पूर्ण
	पूर्ण

	other_tuple = &flow->tuplehash[!dir].tuple;

	क्रम (i = 0; i < other_tuple->encap_num; i++) अणु
		काष्ठा flow_action_entry *entry;

		अगर (other_tuple->in_vlan_ingress & BIT(i))
			जारी;

		entry = flow_action_entry_next(flow_rule);

		चयन (other_tuple->encap[i].proto) अणु
		हाल htons(ETH_P_PPP_SES):
			entry->id = FLOW_ACTION_PPPOE_PUSH;
			entry->pppoe.sid = other_tuple->encap[i].id;
			अवरोध;
		हाल htons(ETH_P_8021Q):
			entry->id = FLOW_ACTION_VLAN_PUSH;
			entry->vlan.vid = other_tuple->encap[i].id;
			entry->vlan.proto = other_tuple->encap[i].proto;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nf_flow_rule_route_ipv4(काष्ठा net *net, स्थिर काष्ठा flow_offload *flow,
			    क्रमागत flow_offload_tuple_dir dir,
			    काष्ठा nf_flow_rule *flow_rule)
अणु
	अगर (nf_flow_rule_route_common(net, flow, dir, flow_rule) < 0)
		वापस -1;

	अगर (test_bit(NF_FLOW_SNAT, &flow->flags)) अणु
		flow_offload_ipv4_snat(net, flow, dir, flow_rule);
		flow_offload_port_snat(net, flow, dir, flow_rule);
	पूर्ण
	अगर (test_bit(NF_FLOW_DNAT, &flow->flags)) अणु
		flow_offload_ipv4_dnat(net, flow, dir, flow_rule);
		flow_offload_port_dnat(net, flow, dir, flow_rule);
	पूर्ण
	अगर (test_bit(NF_FLOW_SNAT, &flow->flags) ||
	    test_bit(NF_FLOW_DNAT, &flow->flags))
		flow_offload_ipv4_checksum(net, flow, flow_rule);

	flow_offload_redirect(net, flow, dir, flow_rule);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_rule_route_ipv4);

पूर्णांक nf_flow_rule_route_ipv6(काष्ठा net *net, स्थिर काष्ठा flow_offload *flow,
			    क्रमागत flow_offload_tuple_dir dir,
			    काष्ठा nf_flow_rule *flow_rule)
अणु
	अगर (nf_flow_rule_route_common(net, flow, dir, flow_rule) < 0)
		वापस -1;

	अगर (test_bit(NF_FLOW_SNAT, &flow->flags)) अणु
		flow_offload_ipv6_snat(net, flow, dir, flow_rule);
		flow_offload_port_snat(net, flow, dir, flow_rule);
	पूर्ण
	अगर (test_bit(NF_FLOW_DNAT, &flow->flags)) अणु
		flow_offload_ipv6_dnat(net, flow, dir, flow_rule);
		flow_offload_port_dnat(net, flow, dir, flow_rule);
	पूर्ण

	flow_offload_redirect(net, flow, dir, flow_rule);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_rule_route_ipv6);

#घोषणा NF_FLOW_RULE_ACTION_MAX	16

अटल काष्ठा nf_flow_rule *
nf_flow_offload_rule_alloc(काष्ठा net *net,
			   स्थिर काष्ठा flow_offload_work *offload,
			   क्रमागत flow_offload_tuple_dir dir)
अणु
	स्थिर काष्ठा nf_flowtable *flowtable = offload->flowtable;
	स्थिर काष्ठा flow_offload_tuple *tuple, *other_tuple;
	स्थिर काष्ठा flow_offload *flow = offload->flow;
	काष्ठा dst_entry *other_dst = शून्य;
	काष्ठा nf_flow_rule *flow_rule;
	पूर्णांक err = -ENOMEM;

	flow_rule = kzalloc(माप(*flow_rule), GFP_KERNEL);
	अगर (!flow_rule)
		जाओ err_flow;

	flow_rule->rule = flow_rule_alloc(NF_FLOW_RULE_ACTION_MAX);
	अगर (!flow_rule->rule)
		जाओ err_flow_rule;

	flow_rule->rule->match.dissector = &flow_rule->match.dissector;
	flow_rule->rule->match.mask = &flow_rule->match.mask;
	flow_rule->rule->match.key = &flow_rule->match.key;

	tuple = &flow->tuplehash[dir].tuple;
	other_tuple = &flow->tuplehash[!dir].tuple;
	अगर (other_tuple->xmit_type == FLOW_OFFLOAD_XMIT_NEIGH)
		other_dst = other_tuple->dst_cache;

	err = nf_flow_rule_match(&flow_rule->match, tuple, other_dst);
	अगर (err < 0)
		जाओ err_flow_match;

	flow_rule->rule->action.num_entries = 0;
	अगर (flowtable->type->action(net, flow, dir, flow_rule) < 0)
		जाओ err_flow_match;

	वापस flow_rule;

err_flow_match:
	kमुक्त(flow_rule->rule);
err_flow_rule:
	kमुक्त(flow_rule);
err_flow:
	वापस शून्य;
पूर्ण

अटल व्योम __nf_flow_offload_destroy(काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action_entry *entry;
	पूर्णांक i;

	क्रम (i = 0; i < flow_rule->rule->action.num_entries; i++) अणु
		entry = &flow_rule->rule->action.entries[i];
		अगर (entry->id != FLOW_ACTION_REसूचीECT)
			जारी;

		dev_put(entry->dev);
	पूर्ण
	kमुक्त(flow_rule->rule);
	kमुक्त(flow_rule);
पूर्ण

अटल व्योम nf_flow_offload_destroy(काष्ठा nf_flow_rule *flow_rule[])
अणु
	पूर्णांक i;

	क्रम (i = 0; i < FLOW_OFFLOAD_सूची_MAX; i++)
		__nf_flow_offload_destroy(flow_rule[i]);
पूर्ण

अटल पूर्णांक nf_flow_offload_alloc(स्थिर काष्ठा flow_offload_work *offload,
				 काष्ठा nf_flow_rule *flow_rule[])
अणु
	काष्ठा net *net = पढ़ो_pnet(&offload->flowtable->net);

	flow_rule[0] = nf_flow_offload_rule_alloc(net, offload,
						  FLOW_OFFLOAD_सूची_ORIGINAL);
	अगर (!flow_rule[0])
		वापस -ENOMEM;

	flow_rule[1] = nf_flow_offload_rule_alloc(net, offload,
						  FLOW_OFFLOAD_सूची_REPLY);
	अगर (!flow_rule[1]) अणु
		__nf_flow_offload_destroy(flow_rule[0]);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nf_flow_offload_init(काष्ठा flow_cls_offload *cls_flow,
				 __be16 proto, पूर्णांक priority,
				 क्रमागत flow_cls_command cmd,
				 स्थिर काष्ठा flow_offload_tuple *tuple,
				 काष्ठा netlink_ext_ack *extack)
अणु
	cls_flow->common.protocol = proto;
	cls_flow->common.prio = priority;
	cls_flow->common.extack = extack;
	cls_flow->command = cmd;
	cls_flow->cookie = (अचिन्हित दीर्घ)tuple;
पूर्ण

अटल पूर्णांक nf_flow_offload_tuple(काष्ठा nf_flowtable *flowtable,
				 काष्ठा flow_offload *flow,
				 काष्ठा nf_flow_rule *flow_rule,
				 क्रमागत flow_offload_tuple_dir dir,
				 पूर्णांक priority, पूर्णांक cmd,
				 काष्ठा flow_stats *stats,
				 काष्ठा list_head *block_cb_list)
अणु
	काष्ठा flow_cls_offload cls_flow = अणुपूर्ण;
	काष्ठा flow_block_cb *block_cb;
	काष्ठा netlink_ext_ack extack;
	__be16 proto = ETH_P_ALL;
	पूर्णांक err, i = 0;

	nf_flow_offload_init(&cls_flow, proto, priority, cmd,
			     &flow->tuplehash[dir].tuple, &extack);
	अगर (cmd == FLOW_CLS_REPLACE)
		cls_flow.rule = flow_rule->rule;

	करोwn_पढ़ो(&flowtable->flow_block_lock);
	list_क्रम_each_entry(block_cb, block_cb_list, list) अणु
		err = block_cb->cb(TC_SETUP_CLSFLOWER, &cls_flow,
				   block_cb->cb_priv);
		अगर (err < 0)
			जारी;

		i++;
	पूर्ण
	up_पढ़ो(&flowtable->flow_block_lock);

	अगर (cmd == FLOW_CLS_STATS)
		स_नकल(stats, &cls_flow.stats, माप(*stats));

	वापस i;
पूर्ण

अटल पूर्णांक flow_offload_tuple_add(काष्ठा flow_offload_work *offload,
				  काष्ठा nf_flow_rule *flow_rule,
				  क्रमागत flow_offload_tuple_dir dir)
अणु
	वापस nf_flow_offload_tuple(offload->flowtable, offload->flow,
				     flow_rule, dir, offload->priority,
				     FLOW_CLS_REPLACE, शून्य,
				     &offload->flowtable->flow_block.cb_list);
पूर्ण

अटल व्योम flow_offload_tuple_del(काष्ठा flow_offload_work *offload,
				   क्रमागत flow_offload_tuple_dir dir)
अणु
	nf_flow_offload_tuple(offload->flowtable, offload->flow, शून्य, dir,
			      offload->priority, FLOW_CLS_DESTROY, शून्य,
			      &offload->flowtable->flow_block.cb_list);
पूर्ण

अटल पूर्णांक flow_offload_rule_add(काष्ठा flow_offload_work *offload,
				 काष्ठा nf_flow_rule *flow_rule[])
अणु
	पूर्णांक ok_count = 0;

	ok_count += flow_offload_tuple_add(offload, flow_rule[0],
					   FLOW_OFFLOAD_सूची_ORIGINAL);
	ok_count += flow_offload_tuple_add(offload, flow_rule[1],
					   FLOW_OFFLOAD_सूची_REPLY);
	अगर (ok_count == 0)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल व्योम flow_offload_work_add(काष्ठा flow_offload_work *offload)
अणु
	काष्ठा nf_flow_rule *flow_rule[FLOW_OFFLOAD_सूची_MAX];
	पूर्णांक err;

	err = nf_flow_offload_alloc(offload, flow_rule);
	अगर (err < 0)
		वापस;

	err = flow_offload_rule_add(offload, flow_rule);
	अगर (err < 0)
		जाओ out;

	set_bit(IPS_HW_OFFLOAD_BIT, &offload->flow->ct->status);

out:
	nf_flow_offload_destroy(flow_rule);
पूर्ण

अटल व्योम flow_offload_work_del(काष्ठा flow_offload_work *offload)
अणु
	clear_bit(IPS_HW_OFFLOAD_BIT, &offload->flow->ct->status);
	flow_offload_tuple_del(offload, FLOW_OFFLOAD_सूची_ORIGINAL);
	flow_offload_tuple_del(offload, FLOW_OFFLOAD_सूची_REPLY);
	set_bit(NF_FLOW_HW_DEAD, &offload->flow->flags);
पूर्ण

अटल व्योम flow_offload_tuple_stats(काष्ठा flow_offload_work *offload,
				     क्रमागत flow_offload_tuple_dir dir,
				     काष्ठा flow_stats *stats)
अणु
	nf_flow_offload_tuple(offload->flowtable, offload->flow, शून्य, dir,
			      offload->priority, FLOW_CLS_STATS, stats,
			      &offload->flowtable->flow_block.cb_list);
पूर्ण

अटल व्योम flow_offload_work_stats(काष्ठा flow_offload_work *offload)
अणु
	काष्ठा flow_stats stats[FLOW_OFFLOAD_सूची_MAX] = अणुपूर्ण;
	u64 lastused;

	flow_offload_tuple_stats(offload, FLOW_OFFLOAD_सूची_ORIGINAL, &stats[0]);
	flow_offload_tuple_stats(offload, FLOW_OFFLOAD_सूची_REPLY, &stats[1]);

	lastused = max_t(u64, stats[0].lastused, stats[1].lastused);
	offload->flow->समयout = max_t(u64, offload->flow->समयout,
				       lastused + NF_FLOW_TIMEOUT);

	अगर (offload->flowtable->flags & NF_FLOWTABLE_COUNTER) अणु
		अगर (stats[0].pkts)
			nf_ct_acct_add(offload->flow->ct,
				       FLOW_OFFLOAD_सूची_ORIGINAL,
				       stats[0].pkts, stats[0].bytes);
		अगर (stats[1].pkts)
			nf_ct_acct_add(offload->flow->ct,
				       FLOW_OFFLOAD_सूची_REPLY,
				       stats[1].pkts, stats[1].bytes);
	पूर्ण
पूर्ण

अटल व्योम flow_offload_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा flow_offload_work *offload;

	offload = container_of(work, काष्ठा flow_offload_work, work);
	चयन (offload->cmd) अणु
		हाल FLOW_CLS_REPLACE:
			flow_offload_work_add(offload);
			अवरोध;
		हाल FLOW_CLS_DESTROY:
			flow_offload_work_del(offload);
			अवरोध;
		हाल FLOW_CLS_STATS:
			flow_offload_work_stats(offload);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
	पूर्ण

	clear_bit(NF_FLOW_HW_PENDING, &offload->flow->flags);
	kमुक्त(offload);
पूर्ण

अटल व्योम flow_offload_queue_work(काष्ठा flow_offload_work *offload)
अणु
	अगर (offload->cmd == FLOW_CLS_REPLACE)
		queue_work(nf_flow_offload_add_wq, &offload->work);
	अन्यथा अगर (offload->cmd == FLOW_CLS_DESTROY)
		queue_work(nf_flow_offload_del_wq, &offload->work);
	अन्यथा
		queue_work(nf_flow_offload_stats_wq, &offload->work);
पूर्ण

अटल काष्ठा flow_offload_work *
nf_flow_offload_work_alloc(काष्ठा nf_flowtable *flowtable,
			   काष्ठा flow_offload *flow, अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा flow_offload_work *offload;

	अगर (test_and_set_bit(NF_FLOW_HW_PENDING, &flow->flags))
		वापस शून्य;

	offload = kदो_स्मृति(माप(काष्ठा flow_offload_work), GFP_ATOMIC);
	अगर (!offload) अणु
		clear_bit(NF_FLOW_HW_PENDING, &flow->flags);
		वापस शून्य;
	पूर्ण

	offload->cmd = cmd;
	offload->flow = flow;
	offload->priority = flowtable->priority;
	offload->flowtable = flowtable;
	INIT_WORK(&offload->work, flow_offload_work_handler);

	वापस offload;
पूर्ण


व्योम nf_flow_offload_add(काष्ठा nf_flowtable *flowtable,
			 काष्ठा flow_offload *flow)
अणु
	काष्ठा flow_offload_work *offload;

	offload = nf_flow_offload_work_alloc(flowtable, flow, FLOW_CLS_REPLACE);
	अगर (!offload)
		वापस;

	flow_offload_queue_work(offload);
पूर्ण

व्योम nf_flow_offload_del(काष्ठा nf_flowtable *flowtable,
			 काष्ठा flow_offload *flow)
अणु
	काष्ठा flow_offload_work *offload;

	offload = nf_flow_offload_work_alloc(flowtable, flow, FLOW_CLS_DESTROY);
	अगर (!offload)
		वापस;

	set_bit(NF_FLOW_HW_DYING, &flow->flags);
	flow_offload_queue_work(offload);
पूर्ण

व्योम nf_flow_offload_stats(काष्ठा nf_flowtable *flowtable,
			   काष्ठा flow_offload *flow)
अणु
	काष्ठा flow_offload_work *offload;
	__s32 delta;

	delta = nf_flow_समयout_delta(flow->समयout);
	अगर ((delta >= (9 * NF_FLOW_TIMEOUT) / 10))
		वापस;

	offload = nf_flow_offload_work_alloc(flowtable, flow, FLOW_CLS_STATS);
	अगर (!offload)
		वापस;

	flow_offload_queue_work(offload);
पूर्ण

व्योम nf_flow_table_offload_flush(काष्ठा nf_flowtable *flowtable)
अणु
	अगर (nf_flowtable_hw_offload(flowtable)) अणु
		flush_workqueue(nf_flow_offload_add_wq);
		flush_workqueue(nf_flow_offload_del_wq);
		flush_workqueue(nf_flow_offload_stats_wq);
	पूर्ण
पूर्ण

अटल पूर्णांक nf_flow_table_block_setup(काष्ठा nf_flowtable *flowtable,
				     काष्ठा flow_block_offload *bo,
				     क्रमागत flow_block_command cmd)
अणु
	काष्ठा flow_block_cb *block_cb, *next;
	पूर्णांक err = 0;

	चयन (cmd) अणु
	हाल FLOW_BLOCK_BIND:
		list_splice(&bo->cb_list, &flowtable->flow_block.cb_list);
		अवरोध;
	हाल FLOW_BLOCK_UNBIND:
		list_क्रम_each_entry_safe(block_cb, next, &bo->cb_list, list) अणु
			list_del(&block_cb->list);
			flow_block_cb_मुक्त(block_cb);
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम nf_flow_table_block_offload_init(काष्ठा flow_block_offload *bo,
					     काष्ठा net *net,
					     क्रमागत flow_block_command cmd,
					     काष्ठा nf_flowtable *flowtable,
					     काष्ठा netlink_ext_ack *extack)
अणु
	स_रखो(bo, 0, माप(*bo));
	bo->net		= net;
	bo->block	= &flowtable->flow_block;
	bo->command	= cmd;
	bo->binder_type	= FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS;
	bo->extack	= extack;
	INIT_LIST_HEAD(&bo->cb_list);
पूर्ण

अटल व्योम nf_flow_table_indr_cleanup(काष्ठा flow_block_cb *block_cb)
अणु
	काष्ठा nf_flowtable *flowtable = block_cb->indr.data;
	काष्ठा net_device *dev = block_cb->indr.dev;

	nf_flow_table_gc_cleanup(flowtable, dev);
	करोwn_ग_लिखो(&flowtable->flow_block_lock);
	list_del(&block_cb->list);
	list_del(&block_cb->driver_list);
	flow_block_cb_मुक्त(block_cb);
	up_ग_लिखो(&flowtable->flow_block_lock);
पूर्ण

अटल पूर्णांक nf_flow_table_indr_offload_cmd(काष्ठा flow_block_offload *bo,
					  काष्ठा nf_flowtable *flowtable,
					  काष्ठा net_device *dev,
					  क्रमागत flow_block_command cmd,
					  काष्ठा netlink_ext_ack *extack)
अणु
	nf_flow_table_block_offload_init(bo, dev_net(dev), cmd, flowtable,
					 extack);

	वापस flow_indr_dev_setup_offload(dev, शून्य, TC_SETUP_FT, flowtable, bo,
					   nf_flow_table_indr_cleanup);
पूर्ण

अटल पूर्णांक nf_flow_table_offload_cmd(काष्ठा flow_block_offload *bo,
				     काष्ठा nf_flowtable *flowtable,
				     काष्ठा net_device *dev,
				     क्रमागत flow_block_command cmd,
				     काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	nf_flow_table_block_offload_init(bo, dev_net(dev), cmd, flowtable,
					 extack);
	err = dev->netdev_ops->nकरो_setup_tc(dev, TC_SETUP_FT, bo);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

पूर्णांक nf_flow_table_offload_setup(काष्ठा nf_flowtable *flowtable,
				काष्ठा net_device *dev,
				क्रमागत flow_block_command cmd)
अणु
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा flow_block_offload bo;
	पूर्णांक err;

	अगर (!nf_flowtable_hw_offload(flowtable))
		वापस 0;

	अगर (dev->netdev_ops->nकरो_setup_tc)
		err = nf_flow_table_offload_cmd(&bo, flowtable, dev, cmd,
						&extack);
	अन्यथा
		err = nf_flow_table_indr_offload_cmd(&bo, flowtable, dev, cmd,
						     &extack);
	अगर (err < 0)
		वापस err;

	वापस nf_flow_table_block_setup(flowtable, &bo, cmd);
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_table_offload_setup);

पूर्णांक nf_flow_table_offload_init(व्योम)
अणु
	nf_flow_offload_add_wq  = alloc_workqueue("nf_ft_offload_add",
						  WQ_UNBOUND | WQ_SYSFS, 0);
	अगर (!nf_flow_offload_add_wq)
		वापस -ENOMEM;

	nf_flow_offload_del_wq  = alloc_workqueue("nf_ft_offload_del",
						  WQ_UNBOUND | WQ_SYSFS, 0);
	अगर (!nf_flow_offload_del_wq)
		जाओ err_del_wq;

	nf_flow_offload_stats_wq  = alloc_workqueue("nf_ft_offload_stats",
						    WQ_UNBOUND | WQ_SYSFS, 0);
	अगर (!nf_flow_offload_stats_wq)
		जाओ err_stats_wq;

	वापस 0;

err_stats_wq:
	destroy_workqueue(nf_flow_offload_del_wq);
err_del_wq:
	destroy_workqueue(nf_flow_offload_add_wq);
	वापस -ENOMEM;
पूर्ण

व्योम nf_flow_table_offload_निकास(व्योम)
अणु
	destroy_workqueue(nf_flow_offload_add_wq);
	destroy_workqueue(nf_flow_offload_del_wq);
	destroy_workqueue(nf_flow_offload_stats_wq);
पूर्ण
