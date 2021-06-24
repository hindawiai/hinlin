<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/netdevice.h>
#समावेश <net/ip.h>
#समावेश <net/ip6_route.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_flow_table.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_l4proto.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>

अटल DEFINE_MUTEX(flowtable_lock);
अटल LIST_HEAD(flowtables);

अटल व्योम
flow_offload_fill_dir(काष्ठा flow_offload *flow,
		      क्रमागत flow_offload_tuple_dir dir)
अणु
	काष्ठा flow_offload_tuple *ft = &flow->tuplehash[dir].tuple;
	काष्ठा nf_conntrack_tuple *ctt = &flow->ct->tuplehash[dir].tuple;

	ft->dir = dir;

	चयन (ctt->src.l3num) अणु
	हाल NFPROTO_IPV4:
		ft->src_v4 = ctt->src.u3.in;
		ft->dst_v4 = ctt->dst.u3.in;
		अवरोध;
	हाल NFPROTO_IPV6:
		ft->src_v6 = ctt->src.u3.in6;
		ft->dst_v6 = ctt->dst.u3.in6;
		अवरोध;
	पूर्ण

	ft->l3proto = ctt->src.l3num;
	ft->l4proto = ctt->dst.protonum;
	ft->src_port = ctt->src.u.tcp.port;
	ft->dst_port = ctt->dst.u.tcp.port;
पूर्ण

काष्ठा flow_offload *flow_offload_alloc(काष्ठा nf_conn *ct)
अणु
	काष्ठा flow_offload *flow;

	अगर (unlikely(nf_ct_is_dying(ct) ||
	    !atomic_inc_not_zero(&ct->ct_general.use)))
		वापस शून्य;

	flow = kzalloc(माप(*flow), GFP_ATOMIC);
	अगर (!flow)
		जाओ err_ct_refcnt;

	flow->ct = ct;

	flow_offload_fill_dir(flow, FLOW_OFFLOAD_सूची_ORIGINAL);
	flow_offload_fill_dir(flow, FLOW_OFFLOAD_सूची_REPLY);

	अगर (ct->status & IPS_SRC_NAT)
		__set_bit(NF_FLOW_SNAT, &flow->flags);
	अगर (ct->status & IPS_DST_NAT)
		__set_bit(NF_FLOW_DNAT, &flow->flags);

	वापस flow;

err_ct_refcnt:
	nf_ct_put(ct);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(flow_offload_alloc);

अटल u32 flow_offload_dst_cookie(काष्ठा flow_offload_tuple *flow_tuple)
अणु
	स्थिर काष्ठा rt6_info *rt;

	अगर (flow_tuple->l3proto == NFPROTO_IPV6) अणु
		rt = (स्थिर काष्ठा rt6_info *)flow_tuple->dst_cache;
		वापस rt6_get_cookie(rt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक flow_offload_fill_route(काष्ठा flow_offload *flow,
				   स्थिर काष्ठा nf_flow_route *route,
				   क्रमागत flow_offload_tuple_dir dir)
अणु
	काष्ठा flow_offload_tuple *flow_tuple = &flow->tuplehash[dir].tuple;
	काष्ठा dst_entry *dst = route->tuple[dir].dst;
	पूर्णांक i, j = 0;

	चयन (flow_tuple->l3proto) अणु
	हाल NFPROTO_IPV4:
		flow_tuple->mtu = ip_dst_mtu_maybe_क्रमward(dst, true);
		अवरोध;
	हाल NFPROTO_IPV6:
		flow_tuple->mtu = ip6_dst_mtu_क्रमward(dst);
		अवरोध;
	पूर्ण

	flow_tuple->iअगरidx = route->tuple[dir].in.अगरindex;
	क्रम (i = route->tuple[dir].in.num_encaps - 1; i >= 0; i--) अणु
		flow_tuple->encap[j].id = route->tuple[dir].in.encap[i].id;
		flow_tuple->encap[j].proto = route->tuple[dir].in.encap[i].proto;
		अगर (route->tuple[dir].in.ingress_vlans & BIT(i))
			flow_tuple->in_vlan_ingress |= BIT(j);
		j++;
	पूर्ण
	flow_tuple->encap_num = route->tuple[dir].in.num_encaps;

	चयन (route->tuple[dir].xmit_type) अणु
	हाल FLOW_OFFLOAD_XMIT_सूचीECT:
		स_नकल(flow_tuple->out.h_dest, route->tuple[dir].out.h_dest,
		       ETH_ALEN);
		स_नकल(flow_tuple->out.h_source, route->tuple[dir].out.h_source,
		       ETH_ALEN);
		flow_tuple->out.अगरidx = route->tuple[dir].out.अगरindex;
		flow_tuple->out.hw_अगरidx = route->tuple[dir].out.hw_अगरindex;
		अवरोध;
	हाल FLOW_OFFLOAD_XMIT_XFRM:
	हाल FLOW_OFFLOAD_XMIT_NEIGH:
		अगर (!dst_hold_safe(route->tuple[dir].dst))
			वापस -1;

		flow_tuple->dst_cache = dst;
		flow_tuple->dst_cookie = flow_offload_dst_cookie(flow_tuple);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण
	flow_tuple->xmit_type = route->tuple[dir].xmit_type;

	वापस 0;
पूर्ण

अटल व्योम nft_flow_dst_release(काष्ठा flow_offload *flow,
				 क्रमागत flow_offload_tuple_dir dir)
अणु
	अगर (flow->tuplehash[dir].tuple.xmit_type == FLOW_OFFLOAD_XMIT_NEIGH ||
	    flow->tuplehash[dir].tuple.xmit_type == FLOW_OFFLOAD_XMIT_XFRM)
		dst_release(flow->tuplehash[dir].tuple.dst_cache);
पूर्ण

पूर्णांक flow_offload_route_init(काष्ठा flow_offload *flow,
			    स्थिर काष्ठा nf_flow_route *route)
अणु
	पूर्णांक err;

	err = flow_offload_fill_route(flow, route, FLOW_OFFLOAD_सूची_ORIGINAL);
	अगर (err < 0)
		वापस err;

	err = flow_offload_fill_route(flow, route, FLOW_OFFLOAD_सूची_REPLY);
	अगर (err < 0)
		जाओ err_route_reply;

	flow->type = NF_FLOW_OFFLOAD_ROUTE;

	वापस 0;

err_route_reply:
	nft_flow_dst_release(flow, FLOW_OFFLOAD_सूची_ORIGINAL);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(flow_offload_route_init);

अटल व्योम flow_offload_fixup_tcp(काष्ठा ip_ct_tcp *tcp)
अणु
	tcp->state = TCP_CONNTRACK_ESTABLISHED;
	tcp->seen[0].td_maxwin = 0;
	tcp->seen[1].td_maxwin = 0;
पूर्ण

#घोषणा NF_FLOWTABLE_TCP_PICKUP_TIMEOUT	(120 * HZ)
#घोषणा NF_FLOWTABLE_UDP_PICKUP_TIMEOUT	(30 * HZ)

अटल व्योम flow_offload_fixup_ct_समयout(काष्ठा nf_conn *ct)
अणु
	स्थिर काष्ठा nf_conntrack_l4proto *l4proto;
	पूर्णांक l4num = nf_ct_protonum(ct);
	अचिन्हित पूर्णांक समयout;

	l4proto = nf_ct_l4proto_find(l4num);
	अगर (!l4proto)
		वापस;

	अगर (l4num == IPPROTO_TCP)
		समयout = NF_FLOWTABLE_TCP_PICKUP_TIMEOUT;
	अन्यथा अगर (l4num == IPPROTO_UDP)
		समयout = NF_FLOWTABLE_UDP_PICKUP_TIMEOUT;
	अन्यथा
		वापस;

	अगर (nf_flow_समयout_delta(ct->समयout) > (__s32)समयout)
		ct->समयout = nfct_समय_stamp + समयout;
पूर्ण

अटल व्योम flow_offload_fixup_ct_state(काष्ठा nf_conn *ct)
अणु
	अगर (nf_ct_protonum(ct) == IPPROTO_TCP)
		flow_offload_fixup_tcp(&ct->proto.tcp);
पूर्ण

अटल व्योम flow_offload_fixup_ct(काष्ठा nf_conn *ct)
अणु
	flow_offload_fixup_ct_state(ct);
	flow_offload_fixup_ct_समयout(ct);
पूर्ण

अटल व्योम flow_offload_route_release(काष्ठा flow_offload *flow)
अणु
	nft_flow_dst_release(flow, FLOW_OFFLOAD_सूची_ORIGINAL);
	nft_flow_dst_release(flow, FLOW_OFFLOAD_सूची_REPLY);
पूर्ण

व्योम flow_offload_मुक्त(काष्ठा flow_offload *flow)
अणु
	चयन (flow->type) अणु
	हाल NF_FLOW_OFFLOAD_ROUTE:
		flow_offload_route_release(flow);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	nf_ct_put(flow->ct);
	kमुक्त_rcu(flow, rcu_head);
पूर्ण
EXPORT_SYMBOL_GPL(flow_offload_मुक्त);

अटल u32 flow_offload_hash(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा flow_offload_tuple *tuple = data;

	वापस jhash(tuple, दुरत्व(काष्ठा flow_offload_tuple, __hash), seed);
पूर्ण

अटल u32 flow_offload_hash_obj(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा flow_offload_tuple_rhash *tuplehash = data;

	वापस jhash(&tuplehash->tuple, दुरत्व(काष्ठा flow_offload_tuple, __hash), seed);
पूर्ण

अटल पूर्णांक flow_offload_hash_cmp(काष्ठा rhashtable_compare_arg *arg,
					स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा flow_offload_tuple *tuple = arg->key;
	स्थिर काष्ठा flow_offload_tuple_rhash *x = ptr;

	अगर (स_भेद(&x->tuple, tuple, दुरत्व(काष्ठा flow_offload_tuple, __hash)))
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rhashtable_params nf_flow_offload_rhash_params = अणु
	.head_offset		= दुरत्व(काष्ठा flow_offload_tuple_rhash, node),
	.hashfn			= flow_offload_hash,
	.obj_hashfn		= flow_offload_hash_obj,
	.obj_cmpfn		= flow_offload_hash_cmp,
	.स्वतःmatic_shrinking	= true,
पूर्ण;

पूर्णांक flow_offload_add(काष्ठा nf_flowtable *flow_table, काष्ठा flow_offload *flow)
अणु
	पूर्णांक err;

	flow->समयout = nf_flowtable_समय_stamp + NF_FLOW_TIMEOUT;

	err = rhashtable_insert_fast(&flow_table->rhashtable,
				     &flow->tuplehash[0].node,
				     nf_flow_offload_rhash_params);
	अगर (err < 0)
		वापस err;

	err = rhashtable_insert_fast(&flow_table->rhashtable,
				     &flow->tuplehash[1].node,
				     nf_flow_offload_rhash_params);
	अगर (err < 0) अणु
		rhashtable_हटाओ_fast(&flow_table->rhashtable,
				       &flow->tuplehash[0].node,
				       nf_flow_offload_rhash_params);
		वापस err;
	पूर्ण

	nf_ct_offload_समयout(flow->ct);

	अगर (nf_flowtable_hw_offload(flow_table)) अणु
		__set_bit(NF_FLOW_HW, &flow->flags);
		nf_flow_offload_add(flow_table, flow);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(flow_offload_add);

व्योम flow_offload_refresh(काष्ठा nf_flowtable *flow_table,
			  काष्ठा flow_offload *flow)
अणु
	flow->समयout = nf_flowtable_समय_stamp + NF_FLOW_TIMEOUT;

	अगर (likely(!nf_flowtable_hw_offload(flow_table)))
		वापस;

	nf_flow_offload_add(flow_table, flow);
पूर्ण
EXPORT_SYMBOL_GPL(flow_offload_refresh);

अटल अंतरभूत bool nf_flow_has_expired(स्थिर काष्ठा flow_offload *flow)
अणु
	वापस nf_flow_समयout_delta(flow->समयout) <= 0;
पूर्ण

अटल व्योम flow_offload_del(काष्ठा nf_flowtable *flow_table,
			     काष्ठा flow_offload *flow)
अणु
	rhashtable_हटाओ_fast(&flow_table->rhashtable,
			       &flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].node,
			       nf_flow_offload_rhash_params);
	rhashtable_हटाओ_fast(&flow_table->rhashtable,
			       &flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].node,
			       nf_flow_offload_rhash_params);

	clear_bit(IPS_OFFLOAD_BIT, &flow->ct->status);

	अगर (nf_flow_has_expired(flow))
		flow_offload_fixup_ct(flow->ct);
	अन्यथा
		flow_offload_fixup_ct_समयout(flow->ct);

	flow_offload_मुक्त(flow);
पूर्ण

व्योम flow_offload_tearकरोwn(काष्ठा flow_offload *flow)
अणु
	set_bit(NF_FLOW_TEARDOWN, &flow->flags);

	flow_offload_fixup_ct_state(flow->ct);
पूर्ण
EXPORT_SYMBOL_GPL(flow_offload_tearकरोwn);

काष्ठा flow_offload_tuple_rhash *
flow_offload_lookup(काष्ठा nf_flowtable *flow_table,
		    काष्ठा flow_offload_tuple *tuple)
अणु
	काष्ठा flow_offload_tuple_rhash *tuplehash;
	काष्ठा flow_offload *flow;
	पूर्णांक dir;

	tuplehash = rhashtable_lookup(&flow_table->rhashtable, tuple,
				      nf_flow_offload_rhash_params);
	अगर (!tuplehash)
		वापस शून्य;

	dir = tuplehash->tuple.dir;
	flow = container_of(tuplehash, काष्ठा flow_offload, tuplehash[dir]);
	अगर (test_bit(NF_FLOW_TEARDOWN, &flow->flags))
		वापस शून्य;

	अगर (unlikely(nf_ct_is_dying(flow->ct)))
		वापस शून्य;

	वापस tuplehash;
पूर्ण
EXPORT_SYMBOL_GPL(flow_offload_lookup);

अटल पूर्णांक
nf_flow_table_iterate(काष्ठा nf_flowtable *flow_table,
		      व्योम (*iter)(काष्ठा flow_offload *flow, व्योम *data),
		      व्योम *data)
अणु
	काष्ठा flow_offload_tuple_rhash *tuplehash;
	काष्ठा rhashtable_iter hti;
	काष्ठा flow_offload *flow;
	पूर्णांक err = 0;

	rhashtable_walk_enter(&flow_table->rhashtable, &hti);
	rhashtable_walk_start(&hti);

	जबतक ((tuplehash = rhashtable_walk_next(&hti))) अणु
		अगर (IS_ERR(tuplehash)) अणु
			अगर (PTR_ERR(tuplehash) != -EAGAIN) अणु
				err = PTR_ERR(tuplehash);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		अगर (tuplehash->tuple.dir)
			जारी;

		flow = container_of(tuplehash, काष्ठा flow_offload, tuplehash[0]);

		iter(flow, data);
	पूर्ण
	rhashtable_walk_stop(&hti);
	rhashtable_walk_निकास(&hti);

	वापस err;
पूर्ण

अटल bool flow_offload_stale_dst(काष्ठा flow_offload_tuple *tuple)
अणु
	काष्ठा dst_entry *dst;

	अगर (tuple->xmit_type == FLOW_OFFLOAD_XMIT_NEIGH ||
	    tuple->xmit_type == FLOW_OFFLOAD_XMIT_XFRM) अणु
		dst = tuple->dst_cache;
		अगर (!dst_check(dst, tuple->dst_cookie))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool nf_flow_has_stale_dst(काष्ठा flow_offload *flow)
अणु
	वापस flow_offload_stale_dst(&flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple) ||
	       flow_offload_stale_dst(&flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple);
पूर्ण

अटल व्योम nf_flow_offload_gc_step(काष्ठा flow_offload *flow, व्योम *data)
अणु
	काष्ठा nf_flowtable *flow_table = data;

	अगर (nf_flow_has_expired(flow) ||
	    nf_ct_is_dying(flow->ct) ||
	    nf_flow_has_stale_dst(flow))
		set_bit(NF_FLOW_TEARDOWN, &flow->flags);

	अगर (test_bit(NF_FLOW_TEARDOWN, &flow->flags)) अणु
		अगर (test_bit(NF_FLOW_HW, &flow->flags)) अणु
			अगर (!test_bit(NF_FLOW_HW_DYING, &flow->flags))
				nf_flow_offload_del(flow_table, flow);
			अन्यथा अगर (test_bit(NF_FLOW_HW_DEAD, &flow->flags))
				flow_offload_del(flow_table, flow);
		पूर्ण अन्यथा अणु
			flow_offload_del(flow_table, flow);
		पूर्ण
	पूर्ण अन्यथा अगर (test_bit(NF_FLOW_HW, &flow->flags)) अणु
		nf_flow_offload_stats(flow_table, flow);
	पूर्ण
पूर्ण

अटल व्योम nf_flow_offload_work_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nf_flowtable *flow_table;

	flow_table = container_of(work, काष्ठा nf_flowtable, gc_work.work);
	nf_flow_table_iterate(flow_table, nf_flow_offload_gc_step, flow_table);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &flow_table->gc_work, HZ);
पूर्ण

अटल व्योम nf_flow_nat_port_tcp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
				 __be16 port, __be16 new_port)
अणु
	काष्ठा tcphdr *tcph;

	tcph = (व्योम *)(skb_network_header(skb) + thoff);
	inet_proto_csum_replace2(&tcph->check, skb, port, new_port, false);
पूर्ण

अटल व्योम nf_flow_nat_port_udp(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
				 __be16 port, __be16 new_port)
अणु
	काष्ठा udphdr *udph;

	udph = (व्योम *)(skb_network_header(skb) + thoff);
	अगर (udph->check || skb->ip_summed == CHECKSUM_PARTIAL) अणु
		inet_proto_csum_replace2(&udph->check, skb, port,
					 new_port, false);
		अगर (!udph->check)
			udph->check = CSUM_MANGLED_0;
	पूर्ण
पूर्ण

अटल व्योम nf_flow_nat_port(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
			     u8 protocol, __be16 port, __be16 new_port)
अणु
	चयन (protocol) अणु
	हाल IPPROTO_TCP:
		nf_flow_nat_port_tcp(skb, thoff, port, new_port);
		अवरोध;
	हाल IPPROTO_UDP:
		nf_flow_nat_port_udp(skb, thoff, port, new_port);
		अवरोध;
	पूर्ण
पूर्ण

व्योम nf_flow_snat_port(स्थिर काष्ठा flow_offload *flow,
		       काष्ठा sk_buff *skb, अचिन्हित पूर्णांक thoff,
		       u8 protocol, क्रमागत flow_offload_tuple_dir dir)
अणु
	काष्ठा flow_ports *hdr;
	__be16 port, new_port;

	hdr = (व्योम *)(skb_network_header(skb) + thoff);

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		port = hdr->source;
		new_port = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.dst_port;
		hdr->source = new_port;
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		port = hdr->dest;
		new_port = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.src_port;
		hdr->dest = new_port;
		अवरोध;
	पूर्ण

	nf_flow_nat_port(skb, thoff, protocol, port, new_port);
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_snat_port);

व्योम nf_flow_dnat_port(स्थिर काष्ठा flow_offload *flow, काष्ठा sk_buff *skb,
		       अचिन्हित पूर्णांक thoff, u8 protocol,
		       क्रमागत flow_offload_tuple_dir dir)
अणु
	काष्ठा flow_ports *hdr;
	__be16 port, new_port;

	hdr = (व्योम *)(skb_network_header(skb) + thoff);

	चयन (dir) अणु
	हाल FLOW_OFFLOAD_सूची_ORIGINAL:
		port = hdr->dest;
		new_port = flow->tuplehash[FLOW_OFFLOAD_सूची_REPLY].tuple.src_port;
		hdr->dest = new_port;
		अवरोध;
	हाल FLOW_OFFLOAD_सूची_REPLY:
		port = hdr->source;
		new_port = flow->tuplehash[FLOW_OFFLOAD_सूची_ORIGINAL].tuple.dst_port;
		hdr->source = new_port;
		अवरोध;
	पूर्ण

	nf_flow_nat_port(skb, thoff, protocol, port, new_port);
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_dnat_port);

पूर्णांक nf_flow_table_init(काष्ठा nf_flowtable *flowtable)
अणु
	पूर्णांक err;

	INIT_DELAYED_WORK(&flowtable->gc_work, nf_flow_offload_work_gc);
	flow_block_init(&flowtable->flow_block);
	init_rwsem(&flowtable->flow_block_lock);

	err = rhashtable_init(&flowtable->rhashtable,
			      &nf_flow_offload_rhash_params);
	अगर (err < 0)
		वापस err;

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &flowtable->gc_work, HZ);

	mutex_lock(&flowtable_lock);
	list_add(&flowtable->list, &flowtables);
	mutex_unlock(&flowtable_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_table_init);

अटल व्योम nf_flow_table_करो_cleanup(काष्ठा flow_offload *flow, व्योम *data)
अणु
	काष्ठा net_device *dev = data;

	अगर (!dev) अणु
		flow_offload_tearकरोwn(flow);
		वापस;
	पूर्ण

	अगर (net_eq(nf_ct_net(flow->ct), dev_net(dev)) &&
	    (flow->tuplehash[0].tuple.iअगरidx == dev->अगरindex ||
	     flow->tuplehash[1].tuple.iअगरidx == dev->अगरindex))
		flow_offload_tearकरोwn(flow);
पूर्ण

व्योम nf_flow_table_gc_cleanup(काष्ठा nf_flowtable *flowtable,
			      काष्ठा net_device *dev)
अणु
	nf_flow_table_iterate(flowtable, nf_flow_table_करो_cleanup, dev);
	flush_delayed_work(&flowtable->gc_work);
	nf_flow_table_offload_flush(flowtable);
पूर्ण

व्योम nf_flow_table_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा nf_flowtable *flowtable;

	mutex_lock(&flowtable_lock);
	list_क्रम_each_entry(flowtable, &flowtables, list)
		nf_flow_table_gc_cleanup(flowtable, dev);
	mutex_unlock(&flowtable_lock);
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_table_cleanup);

व्योम nf_flow_table_मुक्त(काष्ठा nf_flowtable *flow_table)
अणु
	mutex_lock(&flowtable_lock);
	list_del(&flow_table->list);
	mutex_unlock(&flowtable_lock);

	cancel_delayed_work_sync(&flow_table->gc_work);
	nf_flow_table_iterate(flow_table, nf_flow_table_करो_cleanup, शून्य);
	nf_flow_table_iterate(flow_table, nf_flow_offload_gc_step, flow_table);
	nf_flow_table_offload_flush(flow_table);
	अगर (nf_flowtable_hw_offload(flow_table))
		nf_flow_table_iterate(flow_table, nf_flow_offload_gc_step,
				      flow_table);
	rhashtable_destroy(&flow_table->rhashtable);
पूर्ण
EXPORT_SYMBOL_GPL(nf_flow_table_मुक्त);

अटल पूर्णांक __init nf_flow_table_module_init(व्योम)
अणु
	वापस nf_flow_table_offload_init();
पूर्ण

अटल व्योम __निकास nf_flow_table_module_निकास(व्योम)
अणु
	nf_flow_table_offload_निकास();
पूर्ण

module_init(nf_flow_table_module_init);
module_निकास(nf_flow_table_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_DESCRIPTION("Netfilter flow table module");
