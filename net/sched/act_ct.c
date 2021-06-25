<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* -
 * net/sched/act_ct.c  Connection Tracking action
 *
 * Authors:   Paul Blakey <paulb@mellanox.com>
 *            Yossi Kuperman <yossiku@mellanox.com>
 *            Marcelo Ricarकरो Leitner <marcelo.leitner@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/pkt_cls.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/rhashtable.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/act_api.h>
#समावेश <net/ip.h>
#समावेश <net/ipv6_frag.h>
#समावेश <uapi/linux/tc_act/tc_ct.h>
#समावेश <net/tc_act/tc_ct.h>

#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>
#समावेश <net/netfilter/nf_conntrack_helper.h>
#समावेश <net/netfilter/nf_conntrack_acct.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#समावेश <uapi/linux/netfilter/nf_nat.h>

अटल काष्ठा workqueue_काष्ठा *act_ct_wq;
अटल काष्ठा rhashtable zones_ht;
अटल DEFINE_MUTEX(zones_mutex);

काष्ठा tcf_ct_flow_table अणु
	काष्ठा rhash_head node; /* In zones tables */

	काष्ठा rcu_work rwork;
	काष्ठा nf_flowtable nf_ft;
	refcount_t ref;
	u16 zone;

	bool dying;
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params zones_params = अणु
	.head_offset = दुरत्व(काष्ठा tcf_ct_flow_table, node),
	.key_offset = दुरत्व(काष्ठा tcf_ct_flow_table, zone),
	.key_len = माप_field(काष्ठा tcf_ct_flow_table, zone),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल काष्ठा flow_action_entry *
tcf_ct_flow_table_flow_action_get_next(काष्ठा flow_action *flow_action)
अणु
	पूर्णांक i = flow_action->num_entries++;

	वापस &flow_action->entries[i];
पूर्ण

अटल व्योम tcf_ct_add_mangle_action(काष्ठा flow_action *action,
				     क्रमागत flow_action_mangle_base htype,
				     u32 offset,
				     u32 mask,
				     u32 val)
अणु
	काष्ठा flow_action_entry *entry;

	entry = tcf_ct_flow_table_flow_action_get_next(action);
	entry->id = FLOW_ACTION_MANGLE;
	entry->mangle.htype = htype;
	entry->mangle.mask = ~mask;
	entry->mangle.offset = offset;
	entry->mangle.val = val;
पूर्ण

/* The following nat helper functions check अगर the inverted reverse tuple
 * (target) is dअगरferent then the current dir tuple - meaning nat क्रम ports
 * and/or ip is needed, and add the relevant mangle actions.
 */
अटल व्योम
tcf_ct_flow_table_add_action_nat_ipv4(स्थिर काष्ठा nf_conntrack_tuple *tuple,
				      काष्ठा nf_conntrack_tuple target,
				      काष्ठा flow_action *action)
अणु
	अगर (स_भेद(&target.src.u3, &tuple->src.u3, माप(target.src.u3)))
		tcf_ct_add_mangle_action(action, FLOW_ACT_MANGLE_HDR_TYPE_IP4,
					 दुरत्व(काष्ठा iphdr, saddr),
					 0xFFFFFFFF,
					 be32_to_cpu(target.src.u3.ip));
	अगर (स_भेद(&target.dst.u3, &tuple->dst.u3, माप(target.dst.u3)))
		tcf_ct_add_mangle_action(action, FLOW_ACT_MANGLE_HDR_TYPE_IP4,
					 दुरत्व(काष्ठा iphdr, daddr),
					 0xFFFFFFFF,
					 be32_to_cpu(target.dst.u3.ip));
पूर्ण

अटल व्योम
tcf_ct_add_ipv6_addr_mangle_action(काष्ठा flow_action *action,
				   जोड़ nf_inet_addr *addr,
				   u32 offset)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < माप(काष्ठा in6_addr) / माप(u32); i++)
		tcf_ct_add_mangle_action(action, FLOW_ACT_MANGLE_HDR_TYPE_IP6,
					 i * माप(u32) + offset,
					 0xFFFFFFFF, be32_to_cpu(addr->ip6[i]));
पूर्ण

अटल व्योम
tcf_ct_flow_table_add_action_nat_ipv6(स्थिर काष्ठा nf_conntrack_tuple *tuple,
				      काष्ठा nf_conntrack_tuple target,
				      काष्ठा flow_action *action)
अणु
	अगर (स_भेद(&target.src.u3, &tuple->src.u3, माप(target.src.u3)))
		tcf_ct_add_ipv6_addr_mangle_action(action, &target.src.u3,
						   दुरत्व(काष्ठा ipv6hdr,
							    saddr));
	अगर (स_भेद(&target.dst.u3, &tuple->dst.u3, माप(target.dst.u3)))
		tcf_ct_add_ipv6_addr_mangle_action(action, &target.dst.u3,
						   दुरत्व(काष्ठा ipv6hdr,
							    daddr));
पूर्ण

अटल व्योम
tcf_ct_flow_table_add_action_nat_tcp(स्थिर काष्ठा nf_conntrack_tuple *tuple,
				     काष्ठा nf_conntrack_tuple target,
				     काष्ठा flow_action *action)
अणु
	__be16 target_src = target.src.u.tcp.port;
	__be16 target_dst = target.dst.u.tcp.port;

	अगर (target_src != tuple->src.u.tcp.port)
		tcf_ct_add_mangle_action(action, FLOW_ACT_MANGLE_HDR_TYPE_TCP,
					 दुरत्व(काष्ठा tcphdr, source),
					 0xFFFF, be16_to_cpu(target_src));
	अगर (target_dst != tuple->dst.u.tcp.port)
		tcf_ct_add_mangle_action(action, FLOW_ACT_MANGLE_HDR_TYPE_TCP,
					 दुरत्व(काष्ठा tcphdr, dest),
					 0xFFFF, be16_to_cpu(target_dst));
पूर्ण

अटल व्योम
tcf_ct_flow_table_add_action_nat_udp(स्थिर काष्ठा nf_conntrack_tuple *tuple,
				     काष्ठा nf_conntrack_tuple target,
				     काष्ठा flow_action *action)
अणु
	__be16 target_src = target.src.u.udp.port;
	__be16 target_dst = target.dst.u.udp.port;

	अगर (target_src != tuple->src.u.udp.port)
		tcf_ct_add_mangle_action(action, FLOW_ACT_MANGLE_HDR_TYPE_UDP,
					 दुरत्व(काष्ठा udphdr, source),
					 0xFFFF, be16_to_cpu(target_src));
	अगर (target_dst != tuple->dst.u.udp.port)
		tcf_ct_add_mangle_action(action, FLOW_ACT_MANGLE_HDR_TYPE_UDP,
					 दुरत्व(काष्ठा udphdr, dest),
					 0xFFFF, be16_to_cpu(target_dst));
पूर्ण

अटल व्योम tcf_ct_flow_table_add_action_meta(काष्ठा nf_conn *ct,
					      क्रमागत ip_conntrack_dir dir,
					      काष्ठा flow_action *action)
अणु
	काष्ठा nf_conn_labels *ct_labels;
	काष्ठा flow_action_entry *entry;
	क्रमागत ip_conntrack_info ctinfo;
	u32 *act_ct_labels;

	entry = tcf_ct_flow_table_flow_action_get_next(action);
	entry->id = FLOW_ACTION_CT_METADATA;
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK_MARK)
	entry->ct_metadata.mark = ct->mark;
#पूर्ण_अगर
	ctinfo = dir == IP_CT_सूची_ORIGINAL ? IP_CT_ESTABLISHED :
					     IP_CT_ESTABLISHED_REPLY;
	/* aligns with the CT reference on the SKB nf_ct_set */
	entry->ct_metadata.cookie = (अचिन्हित दीर्घ)ct | ctinfo;
	entry->ct_metadata.orig_dir = dir == IP_CT_सूची_ORIGINAL;

	act_ct_labels = entry->ct_metadata.labels;
	ct_labels = nf_ct_labels_find(ct);
	अगर (ct_labels)
		स_नकल(act_ct_labels, ct_labels->bits, NF_CT_LABELS_MAX_SIZE);
	अन्यथा
		स_रखो(act_ct_labels, 0, NF_CT_LABELS_MAX_SIZE);
पूर्ण

अटल पूर्णांक tcf_ct_flow_table_add_action_nat(काष्ठा net *net,
					    काष्ठा nf_conn *ct,
					    क्रमागत ip_conntrack_dir dir,
					    काष्ठा flow_action *action)
अणु
	स्थिर काष्ठा nf_conntrack_tuple *tuple = &ct->tuplehash[dir].tuple;
	काष्ठा nf_conntrack_tuple target;

	अगर (!(ct->status & IPS_NAT_MASK))
		वापस 0;

	nf_ct_invert_tuple(&target, &ct->tuplehash[!dir].tuple);

	चयन (tuple->src.l3num) अणु
	हाल NFPROTO_IPV4:
		tcf_ct_flow_table_add_action_nat_ipv4(tuple, target,
						      action);
		अवरोध;
	हाल NFPROTO_IPV6:
		tcf_ct_flow_table_add_action_nat_ipv6(tuple, target,
						      action);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (nf_ct_protonum(ct)) अणु
	हाल IPPROTO_TCP:
		tcf_ct_flow_table_add_action_nat_tcp(tuple, target, action);
		अवरोध;
	हाल IPPROTO_UDP:
		tcf_ct_flow_table_add_action_nat_udp(tuple, target, action);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcf_ct_flow_table_fill_actions(काष्ठा net *net,
					  स्थिर काष्ठा flow_offload *flow,
					  क्रमागत flow_offload_tuple_dir tdir,
					  काष्ठा nf_flow_rule *flow_rule)
अणु
	काष्ठा flow_action *action = &flow_rule->rule->action;
	पूर्णांक num_entries = action->num_entries;
	काष्ठा nf_conn *ct = flow->ct;
	क्रमागत ip_conntrack_dir dir;
	पूर्णांक i, err;

	चयन (tdir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		dir = IP_CT_सूची_ORIGINAL;
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		dir = IP_CT_सूची_REPLY;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = tcf_ct_flow_table_add_action_nat(net, ct, dir, action);
	अगर (err)
		जाओ err_nat;

	tcf_ct_flow_table_add_action_meta(ct, dir, action);
	वापस 0;

err_nat:
	/* Clear filled actions */
	क्रम (i = num_entries; i < action->num_entries; i++)
		स_रखो(&action->entries[i], 0, माप(action->entries[i]));
	action->num_entries = num_entries;

	वापस err;
पूर्ण

अटल काष्ठा nf_flowtable_type flowtable_ct = अणु
	.action		= tcf_ct_flow_table_fill_actions,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक tcf_ct_flow_table_get(काष्ठा tcf_ct_params *params)
अणु
	काष्ठा tcf_ct_flow_table *ct_ft;
	पूर्णांक err = -ENOMEM;

	mutex_lock(&zones_mutex);
	ct_ft = rhashtable_lookup_fast(&zones_ht, &params->zone, zones_params);
	अगर (ct_ft && refcount_inc_not_zero(&ct_ft->ref))
		जाओ out_unlock;

	ct_ft = kzalloc(माप(*ct_ft), GFP_KERNEL);
	अगर (!ct_ft)
		जाओ err_alloc;
	refcount_set(&ct_ft->ref, 1);

	ct_ft->zone = params->zone;
	err = rhashtable_insert_fast(&zones_ht, &ct_ft->node, zones_params);
	अगर (err)
		जाओ err_insert;

	ct_ft->nf_ft.type = &flowtable_ct;
	ct_ft->nf_ft.flags |= NF_FLOWTABLE_HW_OFFLOAD |
			      NF_FLOWTABLE_COUNTER;
	err = nf_flow_table_init(&ct_ft->nf_ft);
	अगर (err)
		जाओ err_init;

	__module_get(THIS_MODULE);
out_unlock:
	params->ct_ft = ct_ft;
	params->nf_ft = &ct_ft->nf_ft;
	mutex_unlock(&zones_mutex);

	वापस 0;

err_init:
	rhashtable_हटाओ_fast(&zones_ht, &ct_ft->node, zones_params);
err_insert:
	kमुक्त(ct_ft);
err_alloc:
	mutex_unlock(&zones_mutex);
	वापस err;
पूर्ण

अटल व्योम tcf_ct_flow_table_cleanup_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tcf_ct_flow_table *ct_ft;

	ct_ft = container_of(to_rcu_work(work), काष्ठा tcf_ct_flow_table,
			     rwork);
	nf_flow_table_मुक्त(&ct_ft->nf_ft);
	kमुक्त(ct_ft);

	module_put(THIS_MODULE);
पूर्ण

अटल व्योम tcf_ct_flow_table_put(काष्ठा tcf_ct_params *params)
अणु
	काष्ठा tcf_ct_flow_table *ct_ft = params->ct_ft;

	अगर (refcount_dec_and_test(&params->ct_ft->ref)) अणु
		rhashtable_हटाओ_fast(&zones_ht, &ct_ft->node, zones_params);
		INIT_RCU_WORK(&ct_ft->rwork, tcf_ct_flow_table_cleanup_work);
		queue_rcu_work(act_ct_wq, &ct_ft->rwork);
	पूर्ण
पूर्ण

अटल व्योम tcf_ct_flow_table_add(काष्ठा tcf_ct_flow_table *ct_ft,
				  काष्ठा nf_conn *ct,
				  bool tcp)
अणु
	काष्ठा flow_offload *entry;
	पूर्णांक err;

	अगर (test_and_set_bit(IPS_OFFLOAD_BIT, &ct->status))
		वापस;

	entry = flow_offload_alloc(ct);
	अगर (!entry) अणु
		WARN_ON_ONCE(1);
		जाओ err_alloc;
	पूर्ण

	अगर (tcp) अणु
		ct->proto.tcp.seen[0].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
		ct->proto.tcp.seen[1].flags |= IP_CT_TCP_FLAG_BE_LIBERAL;
	पूर्ण

	err = flow_offload_add(&ct_ft->nf_ft, entry);
	अगर (err)
		जाओ err_add;

	वापस;

err_add:
	flow_offload_मुक्त(entry);
err_alloc:
	clear_bit(IPS_OFFLOAD_BIT, &ct->status);
पूर्ण

अटल व्योम tcf_ct_flow_table_process_conn(काष्ठा tcf_ct_flow_table *ct_ft,
					   काष्ठा nf_conn *ct,
					   क्रमागत ip_conntrack_info ctinfo)
अणु
	bool tcp = false;

	अगर (ctinfo != IP_CT_ESTABLISHED && ctinfo != IP_CT_ESTABLISHED_REPLY)
		वापस;

	चयन (nf_ct_protonum(ct)) अणु
	हाल IPPROTO_TCP:
		tcp = true;
		अगर (ct->proto.tcp.state != TCP_CONNTRACK_ESTABLISHED)
			वापस;
		अवरोध;
	हाल IPPROTO_UDP:
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (nf_ct_ext_exist(ct, NF_CT_EXT_HELPER) ||
	    ct->status & IPS_SEQ_ADJUST)
		वापस;

	tcf_ct_flow_table_add(ct_ft, ct, tcp);
पूर्ण

अटल bool
tcf_ct_flow_table_fill_tuple_ipv4(काष्ठा sk_buff *skb,
				  काष्ठा flow_offload_tuple *tuple,
				  काष्ठा tcphdr **tcph)
अणु
	काष्ठा flow_ports *ports;
	अचिन्हित पूर्णांक thoff;
	काष्ठा iphdr *iph;

	अगर (!pskb_network_may_pull(skb, माप(*iph)))
		वापस false;

	iph = ip_hdr(skb);
	thoff = iph->ihl * 4;

	अगर (ip_is_fragment(iph) ||
	    unlikely(thoff != माप(काष्ठा iphdr)))
		वापस false;

	अगर (iph->protocol != IPPROTO_TCP &&
	    iph->protocol != IPPROTO_UDP)
		वापस false;

	अगर (iph->ttl <= 1)
		वापस false;

	अगर (!pskb_network_may_pull(skb, iph->protocol == IPPROTO_TCP ?
					thoff + माप(काष्ठा tcphdr) :
					thoff + माप(*ports)))
		वापस false;

	iph = ip_hdr(skb);
	अगर (iph->protocol == IPPROTO_TCP)
		*tcph = (व्योम *)(skb_network_header(skb) + thoff);

	ports = (काष्ठा flow_ports *)(skb_network_header(skb) + thoff);
	tuple->src_v4.s_addr = iph->saddr;
	tuple->dst_v4.s_addr = iph->daddr;
	tuple->src_port = ports->source;
	tuple->dst_port = ports->dest;
	tuple->l3proto = AF_INET;
	tuple->l4proto = iph->protocol;

	वापस true;
पूर्ण

अटल bool
tcf_ct_flow_table_fill_tuple_ipv6(काष्ठा sk_buff *skb,
				  काष्ठा flow_offload_tuple *tuple,
				  काष्ठा tcphdr **tcph)
अणु
	काष्ठा flow_ports *ports;
	काष्ठा ipv6hdr *ip6h;
	अचिन्हित पूर्णांक thoff;

	अगर (!pskb_network_may_pull(skb, माप(*ip6h)))
		वापस false;

	ip6h = ipv6_hdr(skb);

	अगर (ip6h->nexthdr != IPPROTO_TCP &&
	    ip6h->nexthdr != IPPROTO_UDP)
		वापस false;

	अगर (ip6h->hop_limit <= 1)
		वापस false;

	thoff = माप(*ip6h);
	अगर (!pskb_network_may_pull(skb, ip6h->nexthdr == IPPROTO_TCP ?
					thoff + माप(काष्ठा tcphdr) :
					thoff + माप(*ports)))
		वापस false;

	ip6h = ipv6_hdr(skb);
	अगर (ip6h->nexthdr == IPPROTO_TCP)
		*tcph = (व्योम *)(skb_network_header(skb) + thoff);

	ports = (काष्ठा flow_ports *)(skb_network_header(skb) + thoff);
	tuple->src_v6 = ip6h->saddr;
	tuple->dst_v6 = ip6h->daddr;
	tuple->src_port = ports->source;
	tuple->dst_port = ports->dest;
	tuple->l3proto = AF_INET6;
	tuple->l4proto = ip6h->nexthdr;

	वापस true;
पूर्ण

अटल bool tcf_ct_flow_table_lookup(काष्ठा tcf_ct_params *p,
				     काष्ठा sk_buff *skb,
				     u8 family)
अणु
	काष्ठा nf_flowtable *nf_ft = &p->ct_ft->nf_ft;
	काष्ठा flow_offload_tuple_rhash *tuplehash;
	काष्ठा flow_offload_tuple tuple = अणुपूर्ण;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा tcphdr *tcph = शून्य;
	काष्ठा flow_offload *flow;
	काष्ठा nf_conn *ct;
	u8 dir;

	/* Previously seen or loopback */
	ct = nf_ct_get(skb, &ctinfo);
	अगर ((ct && !nf_ct_is_ढाँचा(ct)) || ctinfo == IP_CT_UNTRACKED)
		वापस false;

	चयन (family) अणु
	हाल NFPROTO_IPV4:
		अगर (!tcf_ct_flow_table_fill_tuple_ipv4(skb, &tuple, &tcph))
			वापस false;
		अवरोध;
	हाल NFPROTO_IPV6:
		अगर (!tcf_ct_flow_table_fill_tuple_ipv6(skb, &tuple, &tcph))
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	tuplehash = flow_offload_lookup(nf_ft, &tuple);
	अगर (!tuplehash)
		वापस false;

	dir = tuplehash->tuple.dir;
	flow = container_of(tuplehash, काष्ठा flow_offload, tuplehash[dir]);
	ct = flow->ct;

	अगर (tcph && (unlikely(tcph->fin || tcph->rst))) अणु
		flow_offload_tearकरोwn(flow);
		वापस false;
	पूर्ण

	ctinfo = dir == FLOW_OFFLOAD_सूची_ORIGINAL ? IP_CT_ESTABLISHED :
						    IP_CT_ESTABLISHED_REPLY;

	flow_offload_refresh(nf_ft, flow);
	nf_conntrack_get(&ct->ct_general);
	nf_ct_set(skb, ct, ctinfo);
	अगर (nf_ft->flags & NF_FLOWTABLE_COUNTER)
		nf_ct_acct_update(ct, dir, skb->len);

	वापस true;
पूर्ण

अटल पूर्णांक tcf_ct_flow_tables_init(व्योम)
अणु
	वापस rhashtable_init(&zones_ht, &zones_params);
पूर्ण

अटल व्योम tcf_ct_flow_tables_uninit(व्योम)
अणु
	rhashtable_destroy(&zones_ht);
पूर्ण

अटल काष्ठा tc_action_ops act_ct_ops;
अटल अचिन्हित पूर्णांक ct_net_id;

काष्ठा tc_ct_action_net अणु
	काष्ठा tc_action_net tn; /* Must be first */
	bool labels;
पूर्ण;

/* Determine whether skb->_nfct is equal to the result of conntrack lookup. */
अटल bool tcf_ct_skb_nfct_cached(काष्ठा net *net, काष्ठा sk_buff *skb,
				   u16 zone_id, bool क्रमce)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		वापस false;
	अगर (!net_eq(net, पढ़ो_pnet(&ct->ct_net)))
		वापस false;
	अगर (nf_ct_zone(ct)->id != zone_id)
		वापस false;

	/* Force conntrack entry direction. */
	अगर (क्रमce && CTINFO2सूची(ctinfo) != IP_CT_सूची_ORIGINAL) अणु
		अगर (nf_ct_is_confirmed(ct))
			nf_ct_समाप्त(ct);

		nf_conntrack_put(&ct->ct_general);
		nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);

		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* Trim the skb to the length specअगरied by the IP/IPv6 header,
 * removing any trailing lower-layer padding. This prepares the skb
 * क्रम higher-layer processing that assumes skb->len excludes padding
 * (such as nf_ip_checksum). The caller needs to pull the skb to the
 * network header, and ensure ip_hdr/ipv6_hdr poपूर्णांकs to valid data.
 */
अटल पूर्णांक tcf_ct_skb_network_trim(काष्ठा sk_buff *skb, पूर्णांक family)
अणु
	अचिन्हित पूर्णांक len;
	पूर्णांक err;

	चयन (family) अणु
	हाल NFPROTO_IPV4:
		len = ntohs(ip_hdr(skb)->tot_len);
		अवरोध;
	हाल NFPROTO_IPV6:
		len = माप(काष्ठा ipv6hdr)
			+ ntohs(ipv6_hdr(skb)->payload_len);
		अवरोध;
	शेष:
		len = skb->len;
	पूर्ण

	err = pskb_trim_rcsum(skb, len);

	वापस err;
पूर्ण

अटल u8 tcf_ct_skb_nf_family(काष्ठा sk_buff *skb)
अणु
	u8 family = NFPROTO_UNSPEC;

	चयन (skb_protocol(skb, true)) अणु
	हाल htons(ETH_P_IP):
		family = NFPROTO_IPV4;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		family = NFPROTO_IPV6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस family;
पूर्ण

अटल पूर्णांक tcf_ct_ipv4_is_fragment(काष्ठा sk_buff *skb, bool *frag)
अणु
	अचिन्हित पूर्णांक len;

	len =  skb_network_offset(skb) + माप(काष्ठा iphdr);
	अगर (unlikely(skb->len < len))
		वापस -EINVAL;
	अगर (unlikely(!pskb_may_pull(skb, len)))
		वापस -ENOMEM;

	*frag = ip_is_fragment(ip_hdr(skb));
	वापस 0;
पूर्ण

अटल पूर्णांक tcf_ct_ipv6_is_fragment(काष्ठा sk_buff *skb, bool *frag)
अणु
	अचिन्हित पूर्णांक flags = 0, len, payload_ofs = 0;
	अचिन्हित लघु frag_off;
	पूर्णांक nexthdr;

	len =  skb_network_offset(skb) + माप(काष्ठा ipv6hdr);
	अगर (unlikely(skb->len < len))
		वापस -EINVAL;
	अगर (unlikely(!pskb_may_pull(skb, len)))
		वापस -ENOMEM;

	nexthdr = ipv6_find_hdr(skb, &payload_ofs, -1, &frag_off, &flags);
	अगर (unlikely(nexthdr < 0))
		वापस -EPROTO;

	*frag = flags & IP6_FH_F_FRAG;
	वापस 0;
पूर्ण

अटल पूर्णांक tcf_ct_handle_fragments(काष्ठा net *net, काष्ठा sk_buff *skb,
				   u8 family, u16 zone, bool *defrag)
अणु
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा qdisc_skb_cb cb;
	काष्ठा nf_conn *ct;
	पूर्णांक err = 0;
	bool frag;

	/* Previously seen (loopback)? Ignore. */
	ct = nf_ct_get(skb, &ctinfo);
	अगर ((ct && !nf_ct_is_ढाँचा(ct)) || ctinfo == IP_CT_UNTRACKED)
		वापस 0;

	अगर (family == NFPROTO_IPV4)
		err = tcf_ct_ipv4_is_fragment(skb, &frag);
	अन्यथा
		err = tcf_ct_ipv6_is_fragment(skb, &frag);
	अगर (err || !frag)
		वापस err;

	skb_get(skb);
	cb = *qdisc_skb_cb(skb);

	अगर (family == NFPROTO_IPV4) अणु
		क्रमागत ip_defrag_users user = IP_DEFRAG_CONNTRACK_IN + zone;

		स_रखो(IPCB(skb), 0, माप(काष्ठा inet_skb_parm));
		local_bh_disable();
		err = ip_defrag(net, skb, user);
		local_bh_enable();
		अगर (err && err != -EINPROGRESS)
			वापस err;

		अगर (!err) अणु
			*defrag = true;
			cb.mru = IPCB(skb)->frag_max_size;
		पूर्ण
	पूर्ण अन्यथा अणु /* NFPROTO_IPV6 */
#अगर IS_ENABLED(CONFIG_NF_DEFRAG_IPV6)
		क्रमागत ip6_defrag_users user = IP6_DEFRAG_CONNTRACK_IN + zone;

		स_रखो(IP6CB(skb), 0, माप(काष्ठा inet6_skb_parm));
		err = nf_ct_frag6_gather(net, skb, user);
		अगर (err && err != -EINPROGRESS)
			जाओ out_मुक्त;

		अगर (!err) अणु
			*defrag = true;
			cb.mru = IP6CB(skb)->frag_max_size;
		पूर्ण
#अन्यथा
		err = -EOPNOTSUPP;
		जाओ out_मुक्त;
#पूर्ण_अगर
	पूर्ण

	अगर (err != -EINPROGRESS)
		*qdisc_skb_cb(skb) = cb;
	skb_clear_hash(skb);
	skb->ignore_df = 1;
	वापस err;

out_मुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल व्योम tcf_ct_params_मुक्त(काष्ठा rcu_head *head)
अणु
	काष्ठा tcf_ct_params *params = container_of(head,
						    काष्ठा tcf_ct_params, rcu);

	tcf_ct_flow_table_put(params);

	अगर (params->पंचांगpl)
		nf_conntrack_put(&params->पंचांगpl->ct_general);
	kमुक्त(params);
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_NAT)
/* Modelled after nf_nat_ipv[46]_fn().
 * range is only used क्रम new, uninitialized NAT state.
 * Returns either NF_ACCEPT or NF_DROP.
 */
अटल पूर्णांक ct_nat_execute(काष्ठा sk_buff *skb, काष्ठा nf_conn *ct,
			  क्रमागत ip_conntrack_info ctinfo,
			  स्थिर काष्ठा nf_nat_range2 *range,
			  क्रमागत nf_nat_manip_type maniptype)
अणु
	__be16 proto = skb_protocol(skb, true);
	पूर्णांक hooknum, err = NF_ACCEPT;

	/* See HOOK2MANIP(). */
	अगर (maniptype == NF_NAT_MANIP_SRC)
		hooknum = NF_INET_LOCAL_IN; /* Source NAT */
	अन्यथा
		hooknum = NF_INET_LOCAL_OUT; /* Destination NAT */

	चयन (ctinfo) अणु
	हाल IP_CT_RELATED:
	हाल IP_CT_RELATED_REPLY:
		अगर (proto == htons(ETH_P_IP) &&
		    ip_hdr(skb)->protocol == IPPROTO_ICMP) अणु
			अगर (!nf_nat_icmp_reply_translation(skb, ct, ctinfo,
							   hooknum))
				err = NF_DROP;
			जाओ out;
		पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_IPV6) && proto == htons(ETH_P_IPV6)) अणु
			__be16 frag_off;
			u8 nexthdr = ipv6_hdr(skb)->nexthdr;
			पूर्णांक hdrlen = ipv6_skip_exthdr(skb,
						      माप(काष्ठा ipv6hdr),
						      &nexthdr, &frag_off);

			अगर (hdrlen >= 0 && nexthdr == IPPROTO_ICMPV6) अणु
				अगर (!nf_nat_icmpv6_reply_translation(skb, ct,
								     ctinfo,
								     hooknum,
								     hdrlen))
					err = NF_DROP;
				जाओ out;
			पूर्ण
		पूर्ण
		/* Non-ICMP, fall thru to initialize अगर needed. */
		fallthrough;
	हाल IP_CT_NEW:
		/* Seen it beक्रमe?  This can happen क्रम loopback, retrans,
		 * or local packets.
		 */
		अगर (!nf_nat_initialized(ct, maniptype)) अणु
			/* Initialize according to the NAT action. */
			err = (range && range->flags & NF_NAT_RANGE_MAP_IPS)
				/* Action is set up to establish a new
				 * mapping.
				 */
				? nf_nat_setup_info(ct, range, maniptype)
				: nf_nat_alloc_null_binding(ct, hooknum);
			अगर (err != NF_ACCEPT)
				जाओ out;
		पूर्ण
		अवरोध;

	हाल IP_CT_ESTABLISHED:
	हाल IP_CT_ESTABLISHED_REPLY:
		अवरोध;

	शेष:
		err = NF_DROP;
		जाओ out;
	पूर्ण

	err = nf_nat_packet(ct, ctinfo, hooknum, skb);
out:
	वापस err;
पूर्ण
#पूर्ण_अगर /* CONFIG_NF_NAT */

अटल व्योम tcf_ct_act_set_mark(काष्ठा nf_conn *ct, u32 mark, u32 mask)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK_MARK)
	u32 new_mark;

	अगर (!mask)
		वापस;

	new_mark = mark | (ct->mark & ~(mask));
	अगर (ct->mark != new_mark) अणु
		ct->mark = new_mark;
		अगर (nf_ct_is_confirmed(ct))
			nf_conntrack_event_cache(IPCT_MARK, ct);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम tcf_ct_act_set_labels(काष्ठा nf_conn *ct,
				  u32 *labels,
				  u32 *labels_m)
अणु
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS)
	माप_प्रकार labels_sz = माप_field(काष्ठा tcf_ct_params, labels);

	अगर (!स_प्रथम_inv(labels_m, 0, labels_sz))
		वापस;

	nf_connlabels_replace(ct, labels, labels_m, 4);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक tcf_ct_act_nat(काष्ठा sk_buff *skb,
			  काष्ठा nf_conn *ct,
			  क्रमागत ip_conntrack_info ctinfo,
			  पूर्णांक ct_action,
			  काष्ठा nf_nat_range2 *range,
			  bool commit)
अणु
#अगर IS_ENABLED(CONFIG_NF_NAT)
	पूर्णांक err;
	क्रमागत nf_nat_manip_type maniptype;

	अगर (!(ct_action & TCA_CT_ACT_NAT))
		वापस NF_ACCEPT;

	/* Add NAT extension अगर not confirmed yet. */
	अगर (!nf_ct_is_confirmed(ct) && !nf_ct_nat_ext_add(ct))
		वापस NF_DROP;   /* Can't NAT. */

	अगर (ctinfo != IP_CT_NEW && (ct->status & IPS_NAT_MASK) &&
	    (ctinfo != IP_CT_RELATED || commit)) अणु
		/* NAT an established or related connection like beक्रमe. */
		अगर (CTINFO2सूची(ctinfo) == IP_CT_सूची_REPLY)
			/* This is the REPLY direction क्रम a connection
			 * क्रम which NAT was applied in the क्रमward
			 * direction.  Do the reverse NAT.
			 */
			maniptype = ct->status & IPS_SRC_NAT
				? NF_NAT_MANIP_DST : NF_NAT_MANIP_SRC;
		अन्यथा
			maniptype = ct->status & IPS_SRC_NAT
				? NF_NAT_MANIP_SRC : NF_NAT_MANIP_DST;
	पूर्ण अन्यथा अगर (ct_action & TCA_CT_ACT_NAT_SRC) अणु
		maniptype = NF_NAT_MANIP_SRC;
	पूर्ण अन्यथा अगर (ct_action & TCA_CT_ACT_NAT_DST) अणु
		maniptype = NF_NAT_MANIP_DST;
	पूर्ण अन्यथा अणु
		वापस NF_ACCEPT;
	पूर्ण

	err = ct_nat_execute(skb, ct, ctinfo, range, maniptype);
	अगर (err == NF_ACCEPT && ct->status & IPS_DST_NAT) अणु
		अगर (ct->status & IPS_SRC_NAT) अणु
			अगर (maniptype == NF_NAT_MANIP_SRC)
				maniptype = NF_NAT_MANIP_DST;
			अन्यथा
				maniptype = NF_NAT_MANIP_SRC;

			err = ct_nat_execute(skb, ct, ctinfo, range,
					     maniptype);
		पूर्ण अन्यथा अगर (CTINFO2सूची(ctinfo) == IP_CT_सूची_ORIGINAL) अणु
			err = ct_nat_execute(skb, ct, ctinfo, शून्य,
					     NF_NAT_MANIP_SRC);
		पूर्ण
	पूर्ण
	वापस err;
#अन्यथा
	वापस NF_ACCEPT;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक tcf_ct_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
		      काष्ठा tcf_result *res)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	bool cached, commit, clear, क्रमce;
	क्रमागत ip_conntrack_info ctinfo;
	काष्ठा tcf_ct *c = to_ct(a);
	काष्ठा nf_conn *पंचांगpl = शून्य;
	काष्ठा nf_hook_state state;
	पूर्णांक nh_ofs, err, retval;
	काष्ठा tcf_ct_params *p;
	bool skip_add = false;
	bool defrag = false;
	काष्ठा nf_conn *ct;
	u8 family;

	p = rcu_dereference_bh(c->params);

	retval = READ_ONCE(c->tcf_action);
	commit = p->ct_action & TCA_CT_ACT_COMMIT;
	clear = p->ct_action & TCA_CT_ACT_CLEAR;
	क्रमce = p->ct_action & TCA_CT_ACT_FORCE;
	पंचांगpl = p->पंचांगpl;

	tcf_lastuse_update(&c->tcf_पंचांग);

	अगर (clear) अणु
		qdisc_skb_cb(skb)->post_ct = false;
		ct = nf_ct_get(skb, &ctinfo);
		अगर (ct) अणु
			nf_conntrack_put(&ct->ct_general);
			nf_ct_set(skb, शून्य, IP_CT_UNTRACKED);
		पूर्ण

		जाओ out_clear;
	पूर्ण

	family = tcf_ct_skb_nf_family(skb);
	अगर (family == NFPROTO_UNSPEC)
		जाओ drop;

	/* The conntrack module expects to be working at L3.
	 * We also try to pull the IPv4/6 header to linear area
	 */
	nh_ofs = skb_network_offset(skb);
	skb_pull_rcsum(skb, nh_ofs);
	err = tcf_ct_handle_fragments(net, skb, family, p->zone, &defrag);
	अगर (err == -EINPROGRESS) अणु
		retval = TC_ACT_STOLEN;
		जाओ out_clear;
	पूर्ण
	अगर (err)
		जाओ drop;

	err = tcf_ct_skb_network_trim(skb, family);
	अगर (err)
		जाओ drop;

	/* If we are recirculating packets to match on ct fields and
	 * committing with a separate ct action, then we करोn't need to
	 * actually run the packet through conntrack twice unless it's क्रम a
	 * dअगरferent zone.
	 */
	cached = tcf_ct_skb_nfct_cached(net, skb, p->zone, क्रमce);
	अगर (!cached) अणु
		अगर (tcf_ct_flow_table_lookup(p, skb, family)) अणु
			skip_add = true;
			जाओ करो_nat;
		पूर्ण

		/* Associate skb with specअगरied zone. */
		अगर (पंचांगpl) अणु
			nf_conntrack_put(skb_nfct(skb));
			nf_conntrack_get(&पंचांगpl->ct_general);
			nf_ct_set(skb, पंचांगpl, IP_CT_NEW);
		पूर्ण

		state.hook = NF_INET_PRE_ROUTING;
		state.net = net;
		state.pf = family;
		err = nf_conntrack_in(skb, &state);
		अगर (err != NF_ACCEPT)
			जाओ out_push;
	पूर्ण

करो_nat:
	ct = nf_ct_get(skb, &ctinfo);
	अगर (!ct)
		जाओ out_push;
	nf_ct_deliver_cached_events(ct);

	err = tcf_ct_act_nat(skb, ct, ctinfo, p->ct_action, &p->range, commit);
	अगर (err != NF_ACCEPT)
		जाओ drop;

	अगर (commit) अणु
		tcf_ct_act_set_mark(ct, p->mark, p->mark_mask);
		tcf_ct_act_set_labels(ct, p->labels, p->labels_mask);

		/* This will take care of sending queued events
		 * even अगर the connection is alपढ़ोy confirmed.
		 */
		nf_conntrack_confirm(skb);
	पूर्ण

	अगर (!skip_add)
		tcf_ct_flow_table_process_conn(p->ct_ft, ct, ctinfo);

out_push:
	skb_push_rcsum(skb, nh_ofs);

	qdisc_skb_cb(skb)->post_ct = true;
out_clear:
	tcf_action_update_bstats(&c->common, skb);
	अगर (defrag)
		qdisc_skb_cb(skb)->pkt_len = skb->len;
	वापस retval;

drop:
	tcf_action_inc_drop_qstats(&c->common);
	वापस TC_ACT_SHOT;
पूर्ण

अटल स्थिर काष्ठा nla_policy ct_policy[TCA_CT_MAX + 1] = अणु
	[TCA_CT_ACTION] = अणु .type = NLA_U16 पूर्ण,
	[TCA_CT_PARMS] = NLA_POLICY_EXACT_LEN(माप(काष्ठा tc_ct)),
	[TCA_CT_ZONE] = अणु .type = NLA_U16 पूर्ण,
	[TCA_CT_MARK] = अणु .type = NLA_U32 पूर्ण,
	[TCA_CT_MARK_MASK] = अणु .type = NLA_U32 पूर्ण,
	[TCA_CT_LABELS] = अणु .type = NLA_BINARY,
			    .len = 128 / BITS_PER_BYTE पूर्ण,
	[TCA_CT_LABELS_MASK] = अणु .type = NLA_BINARY,
				 .len = 128 / BITS_PER_BYTE पूर्ण,
	[TCA_CT_NAT_IPV4_MIN] = अणु .type = NLA_U32 पूर्ण,
	[TCA_CT_NAT_IPV4_MAX] = अणु .type = NLA_U32 पूर्ण,
	[TCA_CT_NAT_IPV6_MIN] = NLA_POLICY_EXACT_LEN(माप(काष्ठा in6_addr)),
	[TCA_CT_NAT_IPV6_MAX] = NLA_POLICY_EXACT_LEN(माप(काष्ठा in6_addr)),
	[TCA_CT_NAT_PORT_MIN] = अणु .type = NLA_U16 पूर्ण,
	[TCA_CT_NAT_PORT_MAX] = अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल पूर्णांक tcf_ct_fill_params_nat(काष्ठा tcf_ct_params *p,
				  काष्ठा tc_ct *parm,
				  काष्ठा nlattr **tb,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nf_nat_range2 *range;

	अगर (!(p->ct_action & TCA_CT_ACT_NAT))
		वापस 0;

	अगर (!IS_ENABLED(CONFIG_NF_NAT)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Netfilter nat isn't enabled in kernel");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!(p->ct_action & (TCA_CT_ACT_NAT_SRC | TCA_CT_ACT_NAT_DST)))
		वापस 0;

	अगर ((p->ct_action & TCA_CT_ACT_NAT_SRC) &&
	    (p->ct_action & TCA_CT_ACT_NAT_DST)) अणु
		NL_SET_ERR_MSG_MOD(extack, "dnat and snat can't be enabled at the same time");
		वापस -EOPNOTSUPP;
	पूर्ण

	range = &p->range;
	अगर (tb[TCA_CT_NAT_IPV4_MIN]) अणु
		काष्ठा nlattr *max_attr = tb[TCA_CT_NAT_IPV4_MAX];

		p->ipv4_range = true;
		range->flags |= NF_NAT_RANGE_MAP_IPS;
		range->min_addr.ip =
			nla_get_in_addr(tb[TCA_CT_NAT_IPV4_MIN]);

		range->max_addr.ip = max_attr ?
				     nla_get_in_addr(max_attr) :
				     range->min_addr.ip;
	पूर्ण अन्यथा अगर (tb[TCA_CT_NAT_IPV6_MIN]) अणु
		काष्ठा nlattr *max_attr = tb[TCA_CT_NAT_IPV6_MAX];

		p->ipv4_range = false;
		range->flags |= NF_NAT_RANGE_MAP_IPS;
		range->min_addr.in6 =
			nla_get_in6_addr(tb[TCA_CT_NAT_IPV6_MIN]);

		range->max_addr.in6 = max_attr ?
				      nla_get_in6_addr(max_attr) :
				      range->min_addr.in6;
	पूर्ण

	अगर (tb[TCA_CT_NAT_PORT_MIN]) अणु
		range->flags |= NF_NAT_RANGE_PROTO_SPECIFIED;
		range->min_proto.all = nla_get_be16(tb[TCA_CT_NAT_PORT_MIN]);

		range->max_proto.all = tb[TCA_CT_NAT_PORT_MAX] ?
				       nla_get_be16(tb[TCA_CT_NAT_PORT_MAX]) :
				       range->min_proto.all;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tcf_ct_set_key_val(काष्ठा nlattr **tb,
			       व्योम *val, पूर्णांक val_type,
			       व्योम *mask, पूर्णांक mask_type,
			       पूर्णांक len)
अणु
	अगर (!tb[val_type])
		वापस;
	nla_स_नकल(val, tb[val_type], len);

	अगर (!mask)
		वापस;

	अगर (mask_type == TCA_CT_UNSPEC || !tb[mask_type])
		स_रखो(mask, 0xff, len);
	अन्यथा
		nla_स_नकल(mask, tb[mask_type], len);
पूर्ण

अटल पूर्णांक tcf_ct_fill_params(काष्ठा net *net,
			      काष्ठा tcf_ct_params *p,
			      काष्ठा tc_ct *parm,
			      काष्ठा nlattr **tb,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_ct_action_net *tn = net_generic(net, ct_net_id);
	काष्ठा nf_conntrack_zone zone;
	काष्ठा nf_conn *पंचांगpl;
	पूर्णांक err;

	p->zone = NF_CT_DEFAULT_ZONE_ID;

	tcf_ct_set_key_val(tb,
			   &p->ct_action, TCA_CT_ACTION,
			   शून्य, TCA_CT_UNSPEC,
			   माप(p->ct_action));

	अगर (p->ct_action & TCA_CT_ACT_CLEAR)
		वापस 0;

	err = tcf_ct_fill_params_nat(p, parm, tb, extack);
	अगर (err)
		वापस err;

	अगर (tb[TCA_CT_MARK]) अणु
		अगर (!IS_ENABLED(CONFIG_NF_CONNTRACK_MARK)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Conntrack mark isn't enabled.");
			वापस -EOPNOTSUPP;
		पूर्ण
		tcf_ct_set_key_val(tb,
				   &p->mark, TCA_CT_MARK,
				   &p->mark_mask, TCA_CT_MARK_MASK,
				   माप(p->mark));
	पूर्ण

	अगर (tb[TCA_CT_LABELS]) अणु
		अगर (!IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Conntrack labels isn't enabled.");
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (!tn->labels) अणु
			NL_SET_ERR_MSG_MOD(extack, "Failed to set connlabel length");
			वापस -EOPNOTSUPP;
		पूर्ण
		tcf_ct_set_key_val(tb,
				   p->labels, TCA_CT_LABELS,
				   p->labels_mask, TCA_CT_LABELS_MASK,
				   माप(p->labels));
	पूर्ण

	अगर (tb[TCA_CT_ZONE]) अणु
		अगर (!IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Conntrack zones isn't enabled.");
			वापस -EOPNOTSUPP;
		पूर्ण

		tcf_ct_set_key_val(tb,
				   &p->zone, TCA_CT_ZONE,
				   शून्य, TCA_CT_UNSPEC,
				   माप(p->zone));
	पूर्ण

	nf_ct_zone_init(&zone, p->zone, NF_CT_DEFAULT_ZONE_सूची, 0);
	पंचांगpl = nf_ct_पंचांगpl_alloc(net, &zone, GFP_KERNEL);
	अगर (!पंचांगpl) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to allocate conntrack template");
		वापस -ENOMEM;
	पूर्ण
	__set_bit(IPS_CONFIRMED_BIT, &पंचांगpl->status);
	nf_conntrack_get(&पंचांगpl->ct_general);
	p->पंचांगpl = पंचांगpl;

	वापस 0;
पूर्ण

अटल पूर्णांक tcf_ct_init(काष्ठा net *net, काष्ठा nlattr *nla,
		       काष्ठा nlattr *est, काष्ठा tc_action **a,
		       पूर्णांक replace, पूर्णांक bind, bool rtnl_held,
		       काष्ठा tcf_proto *tp, u32 flags,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ct_net_id);
	काष्ठा tcf_ct_params *params = शून्य;
	काष्ठा nlattr *tb[TCA_CT_MAX + 1];
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_ct *parm;
	काष्ठा tcf_ct *c;
	पूर्णांक err, res = 0;
	u32 index;

	अगर (!nla) अणु
		NL_SET_ERR_MSG_MOD(extack, "Ct requires attributes to be passed");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested(tb, TCA_CT_MAX, nla, ct_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_CT_PARMS]) अणु
		NL_SET_ERR_MSG_MOD(extack, "Missing required ct parameters");
		वापस -EINVAL;
	पूर्ण
	parm = nla_data(tb[TCA_CT_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;

	अगर (!err) अणु
		err = tcf_idr_create_from_flags(tn, index, est, a,
						&act_ct_ops, bind, flags);
		अगर (err) अणु
			tcf_idr_cleanup(tn, index);
			वापस err;
		पूर्ण
		res = ACT_P_CREATED;
	पूर्ण अन्यथा अणु
		अगर (bind)
			वापस 0;

		अगर (!replace) अणु
			tcf_idr_release(*a, bind);
			वापस -EEXIST;
		पूर्ण
	पूर्ण
	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0)
		जाओ cleanup;

	c = to_ct(*a);

	params = kzalloc(माप(*params), GFP_KERNEL);
	अगर (unlikely(!params)) अणु
		err = -ENOMEM;
		जाओ cleanup;
	पूर्ण

	err = tcf_ct_fill_params(net, params, parm, tb, extack);
	अगर (err)
		जाओ cleanup;

	err = tcf_ct_flow_table_get(params);
	अगर (err)
		जाओ cleanup;

	spin_lock_bh(&c->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	params = rcu_replace_poपूर्णांकer(c->params, params,
				     lockdep_is_held(&c->tcf_lock));
	spin_unlock_bh(&c->tcf_lock);

	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	अगर (params)
		call_rcu(&params->rcu, tcf_ct_params_मुक्त);

	वापस res;

cleanup:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);
	kमुक्त(params);
	tcf_idr_release(*a, bind);
	वापस err;
पूर्ण

अटल व्योम tcf_ct_cleanup(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_ct_params *params;
	काष्ठा tcf_ct *c = to_ct(a);

	params = rcu_dereference_रक्षित(c->params, 1);
	अगर (params)
		call_rcu(&params->rcu, tcf_ct_params_मुक्त);
पूर्ण

अटल पूर्णांक tcf_ct_dump_key_val(काष्ठा sk_buff *skb,
			       व्योम *val, पूर्णांक val_type,
			       व्योम *mask, पूर्णांक mask_type,
			       पूर्णांक len)
अणु
	पूर्णांक err;

	अगर (mask && !स_प्रथम_inv(mask, 0, len))
		वापस 0;

	err = nla_put(skb, val_type, len, val);
	अगर (err)
		वापस err;

	अगर (mask_type != TCA_CT_UNSPEC) अणु
		err = nla_put(skb, mask_type, len, mask);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcf_ct_dump_nat(काष्ठा sk_buff *skb, काष्ठा tcf_ct_params *p)
अणु
	काष्ठा nf_nat_range2 *range = &p->range;

	अगर (!(p->ct_action & TCA_CT_ACT_NAT))
		वापस 0;

	अगर (!(p->ct_action & (TCA_CT_ACT_NAT_SRC | TCA_CT_ACT_NAT_DST)))
		वापस 0;

	अगर (range->flags & NF_NAT_RANGE_MAP_IPS) अणु
		अगर (p->ipv4_range) अणु
			अगर (nla_put_in_addr(skb, TCA_CT_NAT_IPV4_MIN,
					    range->min_addr.ip))
				वापस -1;
			अगर (nla_put_in_addr(skb, TCA_CT_NAT_IPV4_MAX,
					    range->max_addr.ip))
				वापस -1;
		पूर्ण अन्यथा अणु
			अगर (nla_put_in6_addr(skb, TCA_CT_NAT_IPV6_MIN,
					     &range->min_addr.in6))
				वापस -1;
			अगर (nla_put_in6_addr(skb, TCA_CT_NAT_IPV6_MAX,
					     &range->max_addr.in6))
				वापस -1;
		पूर्ण
	पूर्ण

	अगर (range->flags & NF_NAT_RANGE_PROTO_SPECIFIED) अणु
		अगर (nla_put_be16(skb, TCA_CT_NAT_PORT_MIN,
				 range->min_proto.all))
			वापस -1;
		अगर (nla_put_be16(skb, TCA_CT_NAT_PORT_MAX,
				 range->max_proto.all))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक tcf_ct_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			      पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_ct *c = to_ct(a);
	काष्ठा tcf_ct_params *p;

	काष्ठा tc_ct opt = अणु
		.index   = c->tcf_index,
		.refcnt  = refcount_पढ़ो(&c->tcf_refcnt) - ref,
		.bindcnt = atomic_पढ़ो(&c->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t t;

	spin_lock_bh(&c->tcf_lock);
	p = rcu_dereference_रक्षित(c->params,
				      lockdep_is_held(&c->tcf_lock));
	opt.action = c->tcf_action;

	अगर (tcf_ct_dump_key_val(skb,
				&p->ct_action, TCA_CT_ACTION,
				शून्य, TCA_CT_UNSPEC,
				माप(p->ct_action)))
		जाओ nla_put_failure;

	अगर (p->ct_action & TCA_CT_ACT_CLEAR)
		जाओ skip_dump;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_MARK) &&
	    tcf_ct_dump_key_val(skb,
				&p->mark, TCA_CT_MARK,
				&p->mark_mask, TCA_CT_MARK_MASK,
				माप(p->mark)))
		जाओ nla_put_failure;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_LABELS) &&
	    tcf_ct_dump_key_val(skb,
				p->labels, TCA_CT_LABELS,
				p->labels_mask, TCA_CT_LABELS_MASK,
				माप(p->labels)))
		जाओ nla_put_failure;

	अगर (IS_ENABLED(CONFIG_NF_CONNTRACK_ZONES) &&
	    tcf_ct_dump_key_val(skb,
				&p->zone, TCA_CT_ZONE,
				शून्य, TCA_CT_UNSPEC,
				माप(p->zone)))
		जाओ nla_put_failure;

	अगर (tcf_ct_dump_nat(skb, p))
		जाओ nla_put_failure;

skip_dump:
	अगर (nla_put(skb, TCA_CT_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	tcf_पंचांग_dump(&t, &c->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_CT_TM, माप(t), &t, TCA_CT_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&c->tcf_lock);

	वापस skb->len;
nla_put_failure:
	spin_unlock_bh(&c->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tcf_ct_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			 काष्ठा netlink_callback *cb, पूर्णांक type,
			 स्थिर काष्ठा tc_action_ops *ops,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ct_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tcf_ct_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, ct_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल व्योम tcf_stats_update(काष्ठा tc_action *a, u64 bytes, u64 packets,
			     u64 drops, u64 lastuse, bool hw)
अणु
	काष्ठा tcf_ct *c = to_ct(a);

	tcf_action_update_stats(a, bytes, packets, drops, hw);
	c->tcf_पंचांग.lastuse = max_t(u64, c->tcf_पंचांग.lastuse, lastuse);
पूर्ण

अटल काष्ठा tc_action_ops act_ct_ops = अणु
	.kind		=	"ct",
	.id		=	TCA_ID_CT,
	.owner		=	THIS_MODULE,
	.act		=	tcf_ct_act,
	.dump		=	tcf_ct_dump,
	.init		=	tcf_ct_init,
	.cleanup	=	tcf_ct_cleanup,
	.walk		=	tcf_ct_walker,
	.lookup		=	tcf_ct_search,
	.stats_update	=	tcf_stats_update,
	.size		=	माप(काष्ठा tcf_ct),
पूर्ण;

अटल __net_init पूर्णांक ct_init_net(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक n_bits = माप_field(काष्ठा tcf_ct_params, labels) * 8;
	काष्ठा tc_ct_action_net *tn = net_generic(net, ct_net_id);

	अगर (nf_connlabels_get(net, n_bits - 1)) अणु
		tn->labels = false;
		pr_err("act_ct: Failed to set connlabels length");
	पूर्ण अन्यथा अणु
		tn->labels = true;
	पूर्ण

	वापस tc_action_net_init(net, &tn->tn, &act_ct_ops);
पूर्ण

अटल व्योम __net_निकास ct_निकास_net(काष्ठा list_head *net_list)
अणु
	काष्ठा net *net;

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		काष्ठा tc_ct_action_net *tn = net_generic(net, ct_net_id);

		अगर (tn->labels)
			nf_connlabels_put(net);
	पूर्ण
	rtnl_unlock();

	tc_action_net_निकास(net_list, ct_net_id);
पूर्ण

अटल काष्ठा pernet_operations ct_net_ops = अणु
	.init = ct_init_net,
	.निकास_batch = ct_निकास_net,
	.id   = &ct_net_id,
	.size = माप(काष्ठा tc_ct_action_net),
पूर्ण;

अटल पूर्णांक __init ct_init_module(व्योम)
अणु
	पूर्णांक err;

	act_ct_wq = alloc_ordered_workqueue("act_ct_workqueue", 0);
	अगर (!act_ct_wq)
		वापस -ENOMEM;

	err = tcf_ct_flow_tables_init();
	अगर (err)
		जाओ err_tbl_init;

	err = tcf_रेजिस्टर_action(&act_ct_ops, &ct_net_ops);
	अगर (err)
		जाओ err_रेजिस्टर;

	अटल_branch_inc(&tcf_frag_xmit_count);

	वापस 0;

err_रेजिस्टर:
	tcf_ct_flow_tables_uninit();
err_tbl_init:
	destroy_workqueue(act_ct_wq);
	वापस err;
पूर्ण

अटल व्योम __निकास ct_cleanup_module(व्योम)
अणु
	अटल_branch_dec(&tcf_frag_xmit_count);
	tcf_unरेजिस्टर_action(&act_ct_ops, &ct_net_ops);
	tcf_ct_flow_tables_uninit();
	destroy_workqueue(act_ct_wq);
पूर्ण

module_init(ct_init_module);
module_निकास(ct_cleanup_module);
MODULE_AUTHOR("Paul Blakey <paulb@mellanox.com>");
MODULE_AUTHOR("Yossi Kuperman <yossiku@mellanox.com>");
MODULE_AUTHOR("Marcelo Ricardo Leitner <marcelo.leitner@gmail.com>");
MODULE_DESCRIPTION("Connection tracking action");
MODULE_LICENSE("GPL v2");
