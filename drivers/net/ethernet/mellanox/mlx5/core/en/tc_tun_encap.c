<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2021 Mellanox Technologies. */

#समावेश <net/fib_notअगरier.h>
#समावेश <net/nexthop.h>
#समावेश "tc_tun_encap.h"
#समावेश "en_tc.h"
#समावेश "tc_tun.h"
#समावेश "rep/tc.h"
#समावेश "diag/en_tc_tracepoint.h"

क्रमागत अणु
	MLX5E_ROUTE_ENTRY_VALID     = BIT(0),
पूर्ण;

काष्ठा mlx5e_route_key अणु
	पूर्णांक ip_version;
	जोड़ अणु
		__be32 v4;
		काष्ठा in6_addr v6;
	पूर्ण endpoपूर्णांक_ip;
पूर्ण;

काष्ठा mlx5e_route_entry अणु
	काष्ठा mlx5e_route_key key;
	काष्ठा list_head encap_entries;
	काष्ठा list_head decap_flows;
	u32 flags;
	काष्ठा hlist_node hlist;
	refcount_t refcnt;
	पूर्णांक tunnel_dev_index;
	काष्ठा rcu_head rcu;
पूर्ण;

काष्ठा mlx5e_tc_tun_encap अणु
	काष्ठा mlx5e_priv *priv;
	काष्ठा notअगरier_block fib_nb;
	spinlock_t route_lock; /* protects route_tbl */
	अचिन्हित दीर्घ route_tbl_last_update;
	DECLARE_HASHTABLE(route_tbl, 8);
पूर्ण;

अटल bool mlx5e_route_entry_valid(काष्ठा mlx5e_route_entry *r)
अणु
	वापस r->flags & MLX5E_ROUTE_ENTRY_VALID;
पूर्ण

पूर्णांक mlx5e_tc_set_attr_rx_tun(काष्ठा mlx5e_tc_flow *flow,
			     काष्ठा mlx5_flow_spec *spec)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = flow->attr->esw_attr;
	काष्ठा mlx5_rx_tun_attr *tun_attr;
	व्योम *daddr, *saddr;
	u8 ip_version;

	tun_attr = kvzalloc(माप(*tun_attr), GFP_KERNEL);
	अगर (!tun_attr)
		वापस -ENOMEM;

	esw_attr->rx_tun_attr = tun_attr;
	ip_version = mlx5e_tc_get_ip_version(spec, true);

	अगर (ip_version == 4) अणु
		daddr = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				     outer_headers.dst_ipv4_dst_ipv6.ipv4_layout.ipv4);
		saddr = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				     outer_headers.src_ipv4_src_ipv6.ipv4_layout.ipv4);
		tun_attr->dst_ip.v4 = *(__be32 *)daddr;
		tun_attr->src_ip.v4 = *(__be32 *)saddr;
		अगर (!tun_attr->dst_ip.v4 || !tun_attr->src_ip.v4)
			वापस 0;
	पूर्ण
#अगर IS_ENABLED(CONFIG_INET) && IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (ip_version == 6) अणु
		पूर्णांक ipv6_size = MLX5_FLD_SZ_BYTES(ipv6_layout, ipv6);
		काष्ठा in6_addr zerov6 = अणुपूर्ण;

		daddr = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				     outer_headers.dst_ipv4_dst_ipv6.ipv6_layout.ipv6);
		saddr = MLX5_ADDR_OF(fte_match_param, spec->match_value,
				     outer_headers.src_ipv4_src_ipv6.ipv6_layout.ipv6);
		स_नकल(&tun_attr->dst_ip.v6, daddr, ipv6_size);
		स_नकल(&tun_attr->src_ip.v6, saddr, ipv6_size);
		अगर (!स_भेद(&tun_attr->dst_ip.v6, &zerov6, माप(zerov6)) ||
		    !स_भेद(&tun_attr->src_ip.v6, &zerov6, माप(zerov6)))
			वापस 0;
	पूर्ण
#पूर्ण_अगर
	/* Only set the flag अगर both src and dst ip addresses exist. They are
	 * required to establish routing.
	 */
	flow_flag_set(flow, TUN_RX);
	flow->attr->tun_ip_version = ip_version;
	वापस 0;
पूर्ण

अटल bool mlx5e_tc_flow_all_encaps_valid(काष्ठा mlx5_esw_flow_attr *esw_attr)
अणु
	bool all_flow_encaps_valid = true;
	पूर्णांक i;

	/* Flow can be associated with multiple encap entries.
	 * Beक्रमe offloading the flow verअगरy that all of them have
	 * a valid neighbour.
	 */
	क्रम (i = 0; i < MLX5_MAX_FLOW_FWD_VPORTS; i++) अणु
		अगर (!(esw_attr->dests[i].flags & MLX5_ESW_DEST_ENCAP))
			जारी;
		अगर (!(esw_attr->dests[i].flags & MLX5_ESW_DEST_ENCAP_VALID)) अणु
			all_flow_encaps_valid = false;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस all_flow_encaps_valid;
पूर्ण

व्योम mlx5e_tc_encap_flows_add(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_encap_entry *e,
			      काष्ठा list_head *flow_list)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_esw_flow_attr *esw_attr;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_attr *attr;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक err;

	अगर (e->flags & MLX5_ENCAP_ENTRY_NO_ROUTE)
		वापस;

	e->pkt_reक्रमmat = mlx5_packet_reक्रमmat_alloc(priv->mdev,
						     e->reक्रमmat_type,
						     e->encap_size, e->encap_header,
						     MLX5_FLOW_NAMESPACE_FDB);
	अगर (IS_ERR(e->pkt_reक्रमmat)) अणु
		mlx5_core_warn(priv->mdev, "Failed to offload cached encapsulation header, %lu\n",
			       PTR_ERR(e->pkt_reक्रमmat));
		वापस;
	पूर्ण
	e->flags |= MLX5_ENCAP_ENTRY_VALID;
	mlx5e_rep_queue_neigh_stats_work(priv);

	list_क्रम_each_entry(flow, flow_list, पंचांगp_list) अणु
		अगर (!mlx5e_is_offloaded_flow(flow))
			जारी;
		attr = flow->attr;
		esw_attr = attr->esw_attr;
		spec = &attr->parse_attr->spec;

		esw_attr->dests[flow->पंचांगp_entry_index].pkt_reक्रमmat = e->pkt_reक्रमmat;
		esw_attr->dests[flow->पंचांगp_entry_index].flags |= MLX5_ESW_DEST_ENCAP_VALID;

		/* Do not offload flows with unresolved neighbors */
		अगर (!mlx5e_tc_flow_all_encaps_valid(esw_attr))
			जारी;
		/* update from slow path rule to encap rule */
		rule = mlx5e_tc_offload_fdb_rules(esw, flow, spec, attr);
		अगर (IS_ERR(rule)) अणु
			err = PTR_ERR(rule);
			mlx5_core_warn(priv->mdev, "Failed to update cached encapsulation flow, %d\n",
				       err);
			जारी;
		पूर्ण

		mlx5e_tc_unoffload_from_slow_path(esw, flow);
		flow->rule[0] = rule;
		/* was unset when slow path rule हटाओd */
		flow_flag_set(flow, OFFLOADED);
	पूर्ण
पूर्ण

व्योम mlx5e_tc_encap_flows_del(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_encap_entry *e,
			      काष्ठा list_head *flow_list)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_esw_flow_attr *esw_attr;
	काष्ठा mlx5_flow_handle *rule;
	काष्ठा mlx5_flow_attr *attr;
	काष्ठा mlx5_flow_spec *spec;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक err;

	list_क्रम_each_entry(flow, flow_list, पंचांगp_list) अणु
		अगर (!mlx5e_is_offloaded_flow(flow))
			जारी;
		attr = flow->attr;
		esw_attr = attr->esw_attr;
		spec = &attr->parse_attr->spec;

		/* update from encap rule to slow path rule */
		rule = mlx5e_tc_offload_to_slow_path(esw, flow, spec);
		/* mark the flow's encap dest as non-valid */
		esw_attr->dests[flow->पंचांगp_entry_index].flags &= ~MLX5_ESW_DEST_ENCAP_VALID;

		अगर (IS_ERR(rule)) अणु
			err = PTR_ERR(rule);
			mlx5_core_warn(priv->mdev, "Failed to update slow path (encap) flow, %d\n",
				       err);
			जारी;
		पूर्ण

		mlx5e_tc_unoffload_fdb_rules(esw, flow, attr);
		flow->rule[0] = rule;
		/* was unset when fast path rule हटाओd */
		flow_flag_set(flow, OFFLOADED);
	पूर्ण

	/* we know that the encap is valid */
	e->flags &= ~MLX5_ENCAP_ENTRY_VALID;
	mlx5_packet_reक्रमmat_dealloc(priv->mdev, e->pkt_reक्रमmat);
पूर्ण

अटल व्योम mlx5e_take_पंचांगp_flow(काष्ठा mlx5e_tc_flow *flow,
				काष्ठा list_head *flow_list,
				पूर्णांक index)
अणु
	अगर (IS_ERR(mlx5e_flow_get(flow)))
		वापस;
	रुको_क्रम_completion(&flow->init_करोne);

	flow->पंचांगp_entry_index = index;
	list_add(&flow->पंचांगp_list, flow_list);
पूर्ण

/* Takes reference to all flows attached to encap and adds the flows to
 * flow_list using 'tmp_list' list_head in mlx5e_tc_flow.
 */
व्योम mlx5e_take_all_encap_flows(काष्ठा mlx5e_encap_entry *e, काष्ठा list_head *flow_list)
अणु
	काष्ठा encap_flow_item *efi;
	काष्ठा mlx5e_tc_flow *flow;

	list_क्रम_each_entry(efi, &e->flows, list) अणु
		flow = container_of(efi, काष्ठा mlx5e_tc_flow, encaps[efi->index]);
		mlx5e_take_पंचांगp_flow(flow, flow_list, efi->index);
	पूर्ण
पूर्ण

/* Takes reference to all flows attached to route and adds the flows to
 * flow_list using 'tmp_list' list_head in mlx5e_tc_flow.
 */
अटल व्योम mlx5e_take_all_route_decap_flows(काष्ठा mlx5e_route_entry *r,
					     काष्ठा list_head *flow_list)
अणु
	काष्ठा mlx5e_tc_flow *flow;

	list_क्रम_each_entry(flow, &r->decap_flows, decap_routes)
		mlx5e_take_पंचांगp_flow(flow, flow_list, 0);
पूर्ण

प्रकार bool (match_cb)(काष्ठा mlx5e_encap_entry *);

अटल काष्ठा mlx5e_encap_entry *
mlx5e_get_next_matching_encap(काष्ठा mlx5e_neigh_hash_entry *nhe,
			      काष्ठा mlx5e_encap_entry *e,
			      match_cb match)
अणु
	काष्ठा mlx5e_encap_entry *next = शून्य;

retry:
	rcu_पढ़ो_lock();

	/* find encap with non-zero reference counter value */
	क्रम (next = e ?
		     list_next_or_null_rcu(&nhe->encap_list,
					   &e->encap_list,
					   काष्ठा mlx5e_encap_entry,
					   encap_list) :
		     list_first_or_null_rcu(&nhe->encap_list,
					    काष्ठा mlx5e_encap_entry,
					    encap_list);
	     next;
	     next = list_next_or_null_rcu(&nhe->encap_list,
					  &next->encap_list,
					  काष्ठा mlx5e_encap_entry,
					  encap_list))
		अगर (mlx5e_encap_take(next))
			अवरोध;

	rcu_पढ़ो_unlock();

	/* release starting encap */
	अगर (e)
		mlx5e_encap_put(netdev_priv(e->out_dev), e);
	अगर (!next)
		वापस next;

	/* रुको क्रम encap to be fully initialized */
	रुको_क्रम_completion(&next->res_पढ़ोy);
	/* जारी searching अगर encap entry is not in valid state after completion */
	अगर (!match(next)) अणु
		e = next;
		जाओ retry;
	पूर्ण

	वापस next;
पूर्ण

अटल bool mlx5e_encap_valid(काष्ठा mlx5e_encap_entry *e)
अणु
	वापस e->flags & MLX5_ENCAP_ENTRY_VALID;
पूर्ण

अटल काष्ठा mlx5e_encap_entry *
mlx5e_get_next_valid_encap(काष्ठा mlx5e_neigh_hash_entry *nhe,
			   काष्ठा mlx5e_encap_entry *e)
अणु
	वापस mlx5e_get_next_matching_encap(nhe, e, mlx5e_encap_valid);
पूर्ण

अटल bool mlx5e_encap_initialized(काष्ठा mlx5e_encap_entry *e)
अणु
	वापस e->compl_result >= 0;
पूर्ण

काष्ठा mlx5e_encap_entry *
mlx5e_get_next_init_encap(काष्ठा mlx5e_neigh_hash_entry *nhe,
			  काष्ठा mlx5e_encap_entry *e)
अणु
	वापस mlx5e_get_next_matching_encap(nhe, e, mlx5e_encap_initialized);
पूर्ण

व्योम mlx5e_tc_update_neigh_used_value(काष्ठा mlx5e_neigh_hash_entry *nhe)
अणु
	काष्ठा mlx5e_neigh *m_neigh = &nhe->m_neigh;
	काष्ठा mlx5e_encap_entry *e = शून्य;
	काष्ठा mlx5e_tc_flow *flow;
	काष्ठा mlx5_fc *counter;
	काष्ठा neigh_table *tbl;
	bool neigh_used = false;
	काष्ठा neighbour *n;
	u64 lastuse;

	अगर (m_neigh->family == AF_INET)
		tbl = &arp_tbl;
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (m_neigh->family == AF_INET6)
		tbl = ipv6_stub->nd_tbl;
#पूर्ण_अगर
	अन्यथा
		वापस;

	/* mlx5e_get_next_valid_encap() releases previous encap beक्रमe वापसing
	 * next one.
	 */
	जबतक ((e = mlx5e_get_next_valid_encap(nhe, e)) != शून्य) अणु
		काष्ठा mlx5e_priv *priv = netdev_priv(e->out_dev);
		काष्ठा encap_flow_item *efi, *पंचांगp;
		काष्ठा mlx5_eचयन *esw;
		LIST_HEAD(flow_list);

		esw = priv->mdev->priv.eचयन;
		mutex_lock(&esw->offloads.encap_tbl_lock);
		list_क्रम_each_entry_safe(efi, पंचांगp, &e->flows, list) अणु
			flow = container_of(efi, काष्ठा mlx5e_tc_flow,
					    encaps[efi->index]);
			अगर (IS_ERR(mlx5e_flow_get(flow)))
				जारी;
			list_add(&flow->पंचांगp_list, &flow_list);

			अगर (mlx5e_is_offloaded_flow(flow)) अणु
				counter = mlx5e_tc_get_counter(flow);
				lastuse = mlx5_fc_query_lastuse(counter);
				अगर (समय_after((अचिन्हित दीर्घ)lastuse, nhe->reported_lastuse)) अणु
					neigh_used = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		mutex_unlock(&esw->offloads.encap_tbl_lock);

		mlx5e_put_flow_list(priv, &flow_list);
		अगर (neigh_used) अणु
			/* release current encap beक्रमe अवरोधing the loop */
			mlx5e_encap_put(priv, e);
			अवरोध;
		पूर्ण
	पूर्ण

	trace_mlx5e_tc_update_neigh_used_value(nhe, neigh_used);

	अगर (neigh_used) अणु
		nhe->reported_lastuse = jअगरfies;

		/* find the relevant neigh according to the cached device and
		 * dst ip pair
		 */
		n = neigh_lookup(tbl, &m_neigh->dst_ip, READ_ONCE(nhe->neigh_dev));
		अगर (!n)
			वापस;

		neigh_event_send(n, शून्य);
		neigh_release(n);
	पूर्ण
पूर्ण

अटल व्योम mlx5e_encap_dealloc(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_encap_entry *e)
अणु
	WARN_ON(!list_empty(&e->flows));

	अगर (e->compl_result > 0) अणु
		mlx5e_rep_encap_entry_detach(netdev_priv(e->out_dev), e);

		अगर (e->flags & MLX5_ENCAP_ENTRY_VALID)
			mlx5_packet_reक्रमmat_dealloc(priv->mdev, e->pkt_reक्रमmat);
	पूर्ण

	kमुक्त(e->tun_info);
	kमुक्त(e->encap_header);
	kमुक्त_rcu(e, rcu);
पूर्ण

अटल व्योम mlx5e_decap_dealloc(काष्ठा mlx5e_priv *priv,
				काष्ठा mlx5e_decap_entry *d)
अणु
	WARN_ON(!list_empty(&d->flows));

	अगर (!d->compl_result)
		mlx5_packet_reक्रमmat_dealloc(priv->mdev, d->pkt_reक्रमmat);

	kमुक्त_rcu(d, rcu);
पूर्ण

व्योम mlx5e_encap_put(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_encap_entry *e)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	अगर (!refcount_dec_and_mutex_lock(&e->refcnt, &esw->offloads.encap_tbl_lock))
		वापस;
	list_del(&e->route_list);
	hash_del_rcu(&e->encap_hlist);
	mutex_unlock(&esw->offloads.encap_tbl_lock);

	mlx5e_encap_dealloc(priv, e);
पूर्ण

अटल व्योम mlx5e_decap_put(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_decap_entry *d)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	अगर (!refcount_dec_and_mutex_lock(&d->refcnt, &esw->offloads.decap_tbl_lock))
		वापस;
	hash_del_rcu(&d->hlist);
	mutex_unlock(&esw->offloads.decap_tbl_lock);

	mlx5e_decap_dealloc(priv, d);
पूर्ण

अटल व्योम mlx5e_detach_encap_route(काष्ठा mlx5e_priv *priv,
				     काष्ठा mlx5e_tc_flow *flow,
				     पूर्णांक out_index);

व्योम mlx5e_detach_encap(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_tc_flow *flow, पूर्णांक out_index)
अणु
	काष्ठा mlx5e_encap_entry *e = flow->encaps[out_index].e;
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	अगर (flow->attr->esw_attr->dests[out_index].flags &
	    MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE)
		mlx5e_detach_encap_route(priv, flow, out_index);

	/* flow wasn't fully initialized */
	अगर (!e)
		वापस;

	mutex_lock(&esw->offloads.encap_tbl_lock);
	list_del(&flow->encaps[out_index].list);
	flow->encaps[out_index].e = शून्य;
	अगर (!refcount_dec_and_test(&e->refcnt)) अणु
		mutex_unlock(&esw->offloads.encap_tbl_lock);
		वापस;
	पूर्ण
	list_del(&e->route_list);
	hash_del_rcu(&e->encap_hlist);
	mutex_unlock(&esw->offloads.encap_tbl_lock);

	mlx5e_encap_dealloc(priv, e);
पूर्ण

व्योम mlx5e_detach_decap(काष्ठा mlx5e_priv *priv,
			काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_decap_entry *d = flow->decap_reक्रमmat;

	अगर (!d)
		वापस;

	mutex_lock(&esw->offloads.decap_tbl_lock);
	list_del(&flow->l3_to_l2_reक्रमmat);
	flow->decap_reक्रमmat = शून्य;

	अगर (!refcount_dec_and_test(&d->refcnt)) अणु
		mutex_unlock(&esw->offloads.decap_tbl_lock);
		वापस;
	पूर्ण
	hash_del_rcu(&d->hlist);
	mutex_unlock(&esw->offloads.decap_tbl_lock);

	mlx5e_decap_dealloc(priv, d);
पूर्ण

bool mlx5e_tc_tun_encap_info_equal_generic(काष्ठा mlx5e_encap_key *a,
					   काष्ठा mlx5e_encap_key *b)
अणु
	वापस स_भेद(a->ip_tun_key, b->ip_tun_key, माप(*a->ip_tun_key)) == 0 &&
		a->tc_tunnel->tunnel_type == b->tc_tunnel->tunnel_type;
पूर्ण

अटल पूर्णांक cmp_decap_info(काष्ठा mlx5e_decap_key *a,
			  काष्ठा mlx5e_decap_key *b)
अणु
	वापस स_भेद(&a->key, &b->key, माप(b->key));
पूर्ण

अटल पूर्णांक hash_encap_info(काष्ठा mlx5e_encap_key *key)
अणु
	वापस jhash(key->ip_tun_key, माप(*key->ip_tun_key),
		     key->tc_tunnel->tunnel_type);
पूर्ण

अटल पूर्णांक hash_decap_info(काष्ठा mlx5e_decap_key *key)
अणु
	वापस jhash(&key->key, माप(key->key), 0);
पूर्ण

bool mlx5e_encap_take(काष्ठा mlx5e_encap_entry *e)
अणु
	वापस refcount_inc_not_zero(&e->refcnt);
पूर्ण

अटल bool mlx5e_decap_take(काष्ठा mlx5e_decap_entry *e)
अणु
	वापस refcount_inc_not_zero(&e->refcnt);
पूर्ण

अटल काष्ठा mlx5e_encap_entry *
mlx5e_encap_get(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_encap_key *key,
		uपूर्णांकptr_t hash_key)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_encap_key e_key;
	काष्ठा mlx5e_encap_entry *e;

	hash_क्रम_each_possible_rcu(esw->offloads.encap_tbl, e,
				   encap_hlist, hash_key) अणु
		e_key.ip_tun_key = &e->tun_info->key;
		e_key.tc_tunnel = e->tunnel;
		अगर (e->tunnel->encap_info_equal(&e_key, key) &&
		    mlx5e_encap_take(e))
			वापस e;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5e_decap_entry *
mlx5e_decap_get(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_decap_key *key,
		uपूर्णांकptr_t hash_key)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_decap_key r_key;
	काष्ठा mlx5e_decap_entry *e;

	hash_क्रम_each_possible_rcu(esw->offloads.decap_tbl, e,
				   hlist, hash_key) अणु
		r_key = e->key;
		अगर (!cmp_decap_info(&r_key, key) &&
		    mlx5e_decap_take(e))
			वापस e;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा ip_tunnel_info *mlx5e_dup_tun_info(स्थिर काष्ठा ip_tunnel_info *tun_info)
अणु
	माप_प्रकार tun_size = माप(*tun_info) + tun_info->options_len;

	वापस kmemdup(tun_info, tun_size, GFP_KERNEL);
पूर्ण

अटल bool is_duplicated_encap_entry(काष्ठा mlx5e_priv *priv,
				      काष्ठा mlx5e_tc_flow *flow,
				      पूर्णांक out_index,
				      काष्ठा mlx5e_encap_entry *e,
				      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < out_index; i++) अणु
		अगर (flow->encaps[i].e != e)
			जारी;
		NL_SET_ERR_MSG_MOD(extack, "can't duplicate encap action");
		netdev_err(priv->netdev, "can't duplicate encap action\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक mlx5e_set_vf_tunnel(काष्ठा mlx5_eचयन *esw,
			       काष्ठा mlx5_flow_attr *attr,
			       काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
			       काष्ठा net_device *out_dev,
			       पूर्णांक route_dev_अगरindex,
			       पूर्णांक out_index)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा net_device *route_dev;
	u16 vport_num;
	पूर्णांक err = 0;
	u32 data;

	route_dev = dev_get_by_index(dev_net(out_dev), route_dev_अगरindex);

	अगर (!route_dev || route_dev->netdev_ops != &mlx5e_netdev_ops ||
	    !mlx5e_tc_is_vf_tunnel(out_dev, route_dev))
		जाओ out;

	err = mlx5e_tc_query_route_vport(out_dev, route_dev, &vport_num);
	अगर (err)
		जाओ out;

	attr->dest_chain = 0;
	attr->action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	esw_attr->dests[out_index].flags |= MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE;
	data = mlx5_eचयन_get_vport_metadata_क्रम_set(esw_attr->in_mdev->priv.eचयन,
						       vport_num);
	err = mlx5e_tc_match_to_reg_set_and_get_id(esw->dev, mod_hdr_acts,
						   MLX5_FLOW_NAMESPACE_FDB,
						   VPORT_TO_REG, data);
	अगर (err >= 0) अणु
		esw_attr->dests[out_index].src_port_reग_लिखो_act_id = err;
		err = 0;
	पूर्ण

out:
	अगर (route_dev)
		dev_put(route_dev);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_update_vf_tunnel(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_esw_flow_attr *attr,
				  काष्ठा mlx5e_tc_mod_hdr_acts *mod_hdr_acts,
				  काष्ठा net_device *out_dev,
				  पूर्णांक route_dev_अगरindex,
				  पूर्णांक out_index)
अणु
	पूर्णांक act_id = attr->dests[out_index].src_port_reग_लिखो_act_id;
	काष्ठा net_device *route_dev;
	u16 vport_num;
	पूर्णांक err = 0;
	u32 data;

	route_dev = dev_get_by_index(dev_net(out_dev), route_dev_अगरindex);

	अगर (!route_dev || route_dev->netdev_ops != &mlx5e_netdev_ops ||
	    !mlx5e_tc_is_vf_tunnel(out_dev, route_dev)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = mlx5e_tc_query_route_vport(out_dev, route_dev, &vport_num);
	अगर (err)
		जाओ out;

	data = mlx5_eचयन_get_vport_metadata_क्रम_set(attr->in_mdev->priv.eचयन,
						       vport_num);
	mlx5e_tc_match_to_reg_mod_hdr_change(esw->dev, mod_hdr_acts, VPORT_TO_REG, act_id, data);

out:
	अगर (route_dev)
		dev_put(route_dev);
	वापस err;
पूर्ण

अटल अचिन्हित पूर्णांक mlx5e_route_tbl_get_last_update(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;
	काष्ठा mlx5e_tc_tun_encap *encap;
	अचिन्हित पूर्णांक ret;

	uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &uplink_rpriv->uplink_priv;
	encap = uplink_priv->encap;

	spin_lock_bh(&encap->route_lock);
	ret = encap->route_tbl_last_update;
	spin_unlock_bh(&encap->route_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx5e_attach_encap_route(काष्ठा mlx5e_priv *priv,
				    काष्ठा mlx5e_tc_flow *flow,
				    काष्ठा mlx5e_encap_entry *e,
				    bool new_encap_entry,
				    अचिन्हित दीर्घ tbl_समय_beक्रमe,
				    पूर्णांक out_index);

पूर्णांक mlx5e_attach_encap(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5e_tc_flow *flow,
		       काष्ठा net_device *mirred_dev,
		       पूर्णांक out_index,
		       काष्ठा netlink_ext_ack *extack,
		       काष्ठा net_device **encap_dev,
		       bool *encap_valid)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	स्थिर काष्ठा ip_tunnel_info *tun_info;
	अचिन्हित दीर्घ tbl_समय_beक्रमe = 0;
	काष्ठा mlx5e_encap_entry *e;
	काष्ठा mlx5e_encap_key key;
	bool entry_created = false;
	अचिन्हित लघु family;
	uपूर्णांकptr_t hash_key;
	पूर्णांक err = 0;

	parse_attr = attr->parse_attr;
	tun_info = parse_attr->tun_info[out_index];
	family = ip_tunnel_info_af(tun_info);
	key.ip_tun_key = &tun_info->key;
	key.tc_tunnel = mlx5e_get_tc_tun(mirred_dev);
	अगर (!key.tc_tunnel) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported tunnel");
		वापस -EOPNOTSUPP;
	पूर्ण

	hash_key = hash_encap_info(&key);

	mutex_lock(&esw->offloads.encap_tbl_lock);
	e = mlx5e_encap_get(priv, &key, hash_key);

	/* must verअगरy अगर encap is valid or not */
	अगर (e) अणु
		/* Check that entry was not alपढ़ोy attached to this flow */
		अगर (is_duplicated_encap_entry(priv, flow, out_index, e, extack)) अणु
			err = -EOPNOTSUPP;
			जाओ out_err;
		पूर्ण

		mutex_unlock(&esw->offloads.encap_tbl_lock);
		रुको_क्रम_completion(&e->res_पढ़ोy);

		/* Protect against concurrent neigh update. */
		mutex_lock(&esw->offloads.encap_tbl_lock);
		अगर (e->compl_result < 0) अणु
			err = -EREMOTEIO;
			जाओ out_err;
		पूर्ण
		जाओ attach_flow;
	पूर्ण

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	refcount_set(&e->refcnt, 1);
	init_completion(&e->res_पढ़ोy);
	entry_created = true;
	INIT_LIST_HEAD(&e->route_list);

	tun_info = mlx5e_dup_tun_info(tun_info);
	अगर (!tun_info) अणु
		err = -ENOMEM;
		जाओ out_err_init;
	पूर्ण
	e->tun_info = tun_info;
	err = mlx5e_tc_tun_init_encap_attr(mirred_dev, priv, e, extack);
	अगर (err)
		जाओ out_err_init;

	INIT_LIST_HEAD(&e->flows);
	hash_add_rcu(esw->offloads.encap_tbl, &e->encap_hlist, hash_key);
	tbl_समय_beक्रमe = mlx5e_route_tbl_get_last_update(priv);
	mutex_unlock(&esw->offloads.encap_tbl_lock);

	अगर (family == AF_INET)
		err = mlx5e_tc_tun_create_header_ipv4(priv, mirred_dev, e);
	अन्यथा अगर (family == AF_INET6)
		err = mlx5e_tc_tun_create_header_ipv6(priv, mirred_dev, e);

	/* Protect against concurrent neigh update. */
	mutex_lock(&esw->offloads.encap_tbl_lock);
	complete_all(&e->res_पढ़ोy);
	अगर (err) अणु
		e->compl_result = err;
		जाओ out_err;
	पूर्ण
	e->compl_result = 1;

attach_flow:
	err = mlx5e_attach_encap_route(priv, flow, e, entry_created, tbl_समय_beक्रमe,
				       out_index);
	अगर (err)
		जाओ out_err;

	flow->encaps[out_index].e = e;
	list_add(&flow->encaps[out_index].list, &e->flows);
	flow->encaps[out_index].index = out_index;
	*encap_dev = e->out_dev;
	अगर (e->flags & MLX5_ENCAP_ENTRY_VALID) अणु
		attr->esw_attr->dests[out_index].pkt_reक्रमmat = e->pkt_reक्रमmat;
		attr->esw_attr->dests[out_index].flags |= MLX5_ESW_DEST_ENCAP_VALID;
		*encap_valid = true;
	पूर्ण अन्यथा अणु
		*encap_valid = false;
	पूर्ण
	mutex_unlock(&esw->offloads.encap_tbl_lock);

	वापस err;

out_err:
	mutex_unlock(&esw->offloads.encap_tbl_lock);
	अगर (e)
		mlx5e_encap_put(priv, e);
	वापस err;

out_err_init:
	mutex_unlock(&esw->offloads.encap_tbl_lock);
	kमुक्त(tun_info);
	kमुक्त(e);
	वापस err;
पूर्ण

पूर्णांक mlx5e_attach_decap(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5e_tc_flow *flow,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_esw_flow_attr *attr = flow->attr->esw_attr;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5e_decap_entry *d;
	काष्ठा mlx5e_decap_key key;
	uपूर्णांकptr_t hash_key;
	पूर्णांक err = 0;

	parse_attr = flow->attr->parse_attr;
	अगर (माप(parse_attr->eth) > MLX5_CAP_ESW(priv->mdev, max_encap_header_size)) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "encap header larger than max supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	key.key = parse_attr->eth;
	hash_key = hash_decap_info(&key);
	mutex_lock(&esw->offloads.decap_tbl_lock);
	d = mlx5e_decap_get(priv, &key, hash_key);
	अगर (d) अणु
		mutex_unlock(&esw->offloads.decap_tbl_lock);
		रुको_क्रम_completion(&d->res_पढ़ोy);
		mutex_lock(&esw->offloads.decap_tbl_lock);
		अगर (d->compl_result) अणु
			err = -EREMOTEIO;
			जाओ out_मुक्त;
		पूर्ण
		जाओ found;
	पूर्ण

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	d->key = key;
	refcount_set(&d->refcnt, 1);
	init_completion(&d->res_पढ़ोy);
	INIT_LIST_HEAD(&d->flows);
	hash_add_rcu(esw->offloads.decap_tbl, &d->hlist, hash_key);
	mutex_unlock(&esw->offloads.decap_tbl_lock);

	d->pkt_reक्रमmat = mlx5_packet_reक्रमmat_alloc(priv->mdev,
						     MLX5_REFORMAT_TYPE_L3_TUNNEL_TO_L2,
						     माप(parse_attr->eth),
						     &parse_attr->eth,
						     MLX5_FLOW_NAMESPACE_FDB);
	अगर (IS_ERR(d->pkt_reक्रमmat)) अणु
		err = PTR_ERR(d->pkt_reक्रमmat);
		d->compl_result = err;
	पूर्ण
	mutex_lock(&esw->offloads.decap_tbl_lock);
	complete_all(&d->res_पढ़ोy);
	अगर (err)
		जाओ out_मुक्त;

found:
	flow->decap_reक्रमmat = d;
	attr->decap_pkt_reक्रमmat = d->pkt_reक्रमmat;
	list_add(&flow->l3_to_l2_reक्रमmat, &d->flows);
	mutex_unlock(&esw->offloads.decap_tbl_lock);
	वापस 0;

out_मुक्त:
	mutex_unlock(&esw->offloads.decap_tbl_lock);
	mlx5e_decap_put(priv, d);
	वापस err;

out_err:
	mutex_unlock(&esw->offloads.decap_tbl_lock);
	वापस err;
पूर्ण

अटल पूर्णांक cmp_route_info(काष्ठा mlx5e_route_key *a,
			  काष्ठा mlx5e_route_key *b)
अणु
	अगर (a->ip_version == 4 && b->ip_version == 4)
		वापस स_भेद(&a->endpoपूर्णांक_ip.v4, &b->endpoपूर्णांक_ip.v4,
			      माप(a->endpoपूर्णांक_ip.v4));
	अन्यथा अगर (a->ip_version == 6 && b->ip_version == 6)
		वापस स_भेद(&a->endpoपूर्णांक_ip.v6, &b->endpoपूर्णांक_ip.v6,
			      माप(a->endpoपूर्णांक_ip.v6));
	वापस 1;
पूर्ण

अटल u32 hash_route_info(काष्ठा mlx5e_route_key *key)
अणु
	अगर (key->ip_version == 4)
		वापस jhash(&key->endpoपूर्णांक_ip.v4, माप(key->endpoपूर्णांक_ip.v4), 0);
	वापस jhash(&key->endpoपूर्णांक_ip.v6, माप(key->endpoपूर्णांक_ip.v6), 0);
पूर्ण

अटल व्योम mlx5e_route_dealloc(काष्ठा mlx5e_priv *priv,
				काष्ठा mlx5e_route_entry *r)
अणु
	WARN_ON(!list_empty(&r->decap_flows));
	WARN_ON(!list_empty(&r->encap_entries));

	kमुक्त_rcu(r, rcu);
पूर्ण

अटल व्योम mlx5e_route_put(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_route_entry *r)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	अगर (!refcount_dec_and_mutex_lock(&r->refcnt, &esw->offloads.encap_tbl_lock))
		वापस;

	hash_del_rcu(&r->hlist);
	mutex_unlock(&esw->offloads.encap_tbl_lock);

	mlx5e_route_dealloc(priv, r);
पूर्ण

अटल व्योम mlx5e_route_put_locked(काष्ठा mlx5e_priv *priv, काष्ठा mlx5e_route_entry *r)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;

	lockdep_निश्चित_held(&esw->offloads.encap_tbl_lock);

	अगर (!refcount_dec_and_test(&r->refcnt))
		वापस;
	hash_del_rcu(&r->hlist);
	mlx5e_route_dealloc(priv, r);
पूर्ण

अटल काष्ठा mlx5e_route_entry *
mlx5e_route_get(काष्ठा mlx5e_tc_tun_encap *encap, काष्ठा mlx5e_route_key *key,
		u32 hash_key)
अणु
	काष्ठा mlx5e_route_key r_key;
	काष्ठा mlx5e_route_entry *r;

	hash_क्रम_each_possible(encap->route_tbl, r, hlist, hash_key) अणु
		r_key = r->key;
		अगर (!cmp_route_info(&r_key, key) &&
		    refcount_inc_not_zero(&r->refcnt))
			वापस r;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5e_route_entry *
mlx5e_route_get_create(काष्ठा mlx5e_priv *priv,
		       काष्ठा mlx5e_route_key *key,
		       पूर्णांक tunnel_dev_index,
		       अचिन्हित दीर्घ *route_tbl_change_समय)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5_rep_uplink_priv *uplink_priv;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;
	काष्ठा mlx5e_tc_tun_encap *encap;
	काष्ठा mlx5e_route_entry *r;
	u32 hash_key;

	uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	uplink_priv = &uplink_rpriv->uplink_priv;
	encap = uplink_priv->encap;

	hash_key = hash_route_info(key);
	spin_lock_bh(&encap->route_lock);
	r = mlx5e_route_get(encap, key, hash_key);
	spin_unlock_bh(&encap->route_lock);
	अगर (r) अणु
		अगर (!mlx5e_route_entry_valid(r)) अणु
			mlx5e_route_put_locked(priv, r);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		वापस r;
	पूर्ण

	r = kzalloc(माप(*r), GFP_KERNEL);
	अगर (!r)
		वापस ERR_PTR(-ENOMEM);

	r->key = *key;
	r->flags |= MLX5E_ROUTE_ENTRY_VALID;
	r->tunnel_dev_index = tunnel_dev_index;
	refcount_set(&r->refcnt, 1);
	INIT_LIST_HEAD(&r->decap_flows);
	INIT_LIST_HEAD(&r->encap_entries);

	spin_lock_bh(&encap->route_lock);
	*route_tbl_change_समय = encap->route_tbl_last_update;
	hash_add(encap->route_tbl, &r->hlist, hash_key);
	spin_unlock_bh(&encap->route_lock);

	वापस r;
पूर्ण

अटल काष्ठा mlx5e_route_entry *
mlx5e_route_lookup_क्रम_update(काष्ठा mlx5e_tc_tun_encap *encap, काष्ठा mlx5e_route_key *key)
अणु
	u32 hash_key = hash_route_info(key);
	काष्ठा mlx5e_route_entry *r;

	spin_lock_bh(&encap->route_lock);
	encap->route_tbl_last_update = jअगरfies;
	r = mlx5e_route_get(encap, key, hash_key);
	spin_unlock_bh(&encap->route_lock);

	वापस r;
पूर्ण

काष्ठा mlx5e_tc_fib_event_data अणु
	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ event;
	काष्ठा mlx5e_route_entry *r;
	काष्ठा net_device *ul_dev;
पूर्ण;

अटल व्योम mlx5e_tc_fib_event_work(काष्ठा work_काष्ठा *work);
अटल काष्ठा mlx5e_tc_fib_event_data *
mlx5e_tc_init_fib_work(अचिन्हित दीर्घ event, काष्ठा net_device *ul_dev, gfp_t flags)
अणु
	काष्ठा mlx5e_tc_fib_event_data *fib_work;

	fib_work = kzalloc(माप(*fib_work), flags);
	अगर (WARN_ON(!fib_work))
		वापस शून्य;

	INIT_WORK(&fib_work->work, mlx5e_tc_fib_event_work);
	fib_work->event = event;
	fib_work->ul_dev = ul_dev;

	वापस fib_work;
पूर्ण

अटल पूर्णांक
mlx5e_route_enqueue_update(काष्ठा mlx5e_priv *priv,
			   काष्ठा mlx5e_route_entry *r,
			   अचिन्हित दीर्घ event)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_fib_event_data *fib_work;
	काष्ठा mlx5e_rep_priv *uplink_rpriv;
	काष्ठा net_device *ul_dev;

	uplink_rpriv = mlx5_eचयन_get_uplink_priv(esw, REP_ETH);
	ul_dev = uplink_rpriv->netdev;

	fib_work = mlx5e_tc_init_fib_work(event, ul_dev, GFP_KERNEL);
	अगर (!fib_work)
		वापस -ENOMEM;

	dev_hold(ul_dev);
	refcount_inc(&r->refcnt);
	fib_work->r = r;
	queue_work(priv->wq, &fib_work->work);

	वापस 0;
पूर्ण

पूर्णांक mlx5e_attach_decap_route(काष्ठा mlx5e_priv *priv,
			     काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	अचिन्हित दीर्घ tbl_समय_beक्रमe, tbl_समय_after;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	काष्ठा mlx5_esw_flow_attr *esw_attr;
	काष्ठा mlx5e_route_entry *r;
	काष्ठा mlx5e_route_key key;
	पूर्णांक err = 0;

	esw_attr = attr->esw_attr;
	parse_attr = attr->parse_attr;
	mutex_lock(&esw->offloads.encap_tbl_lock);
	अगर (!esw_attr->rx_tun_attr)
		जाओ out;

	tbl_समय_beक्रमe = mlx5e_route_tbl_get_last_update(priv);
	tbl_समय_after = tbl_समय_beक्रमe;
	err = mlx5e_tc_tun_route_lookup(priv, &parse_attr->spec, attr);
	अगर (err || !esw_attr->rx_tun_attr->decap_vport)
		जाओ out;

	key.ip_version = attr->tun_ip_version;
	अगर (key.ip_version == 4)
		key.endpoपूर्णांक_ip.v4 = esw_attr->rx_tun_attr->dst_ip.v4;
	अन्यथा
		key.endpoपूर्णांक_ip.v6 = esw_attr->rx_tun_attr->dst_ip.v6;

	r = mlx5e_route_get_create(priv, &key, parse_attr->filter_dev->अगरindex,
				   &tbl_समय_after);
	अगर (IS_ERR(r)) अणु
		err = PTR_ERR(r);
		जाओ out;
	पूर्ण
	/* Routing changed concurrently. FIB event handler might have missed new
	 * entry, schedule update.
	 */
	अगर (tbl_समय_beक्रमe != tbl_समय_after) अणु
		err = mlx5e_route_enqueue_update(priv, r, FIB_EVENT_ENTRY_REPLACE);
		अगर (err) अणु
			mlx5e_route_put_locked(priv, r);
			जाओ out;
		पूर्ण
	पूर्ण

	flow->decap_route = r;
	list_add(&flow->decap_routes, &r->decap_flows);
	mutex_unlock(&esw->offloads.encap_tbl_lock);
	वापस 0;

out:
	mutex_unlock(&esw->offloads.encap_tbl_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5e_attach_encap_route(काष्ठा mlx5e_priv *priv,
				    काष्ठा mlx5e_tc_flow *flow,
				    काष्ठा mlx5e_encap_entry *e,
				    bool new_encap_entry,
				    अचिन्हित दीर्घ tbl_समय_beक्रमe,
				    पूर्णांक out_index)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	अचिन्हित दीर्घ tbl_समय_after = tbl_समय_beक्रमe;
	काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
	काष्ठा mlx5_flow_attr *attr = flow->attr;
	स्थिर काष्ठा ip_tunnel_info *tun_info;
	काष्ठा mlx5_esw_flow_attr *esw_attr;
	काष्ठा mlx5e_route_entry *r;
	काष्ठा mlx5e_route_key key;
	अचिन्हित लघु family;
	पूर्णांक err = 0;

	esw_attr = attr->esw_attr;
	parse_attr = attr->parse_attr;
	tun_info = parse_attr->tun_info[out_index];
	family = ip_tunnel_info_af(tun_info);

	अगर (family == AF_INET) अणु
		key.endpoपूर्णांक_ip.v4 = tun_info->key.u.ipv4.src;
		key.ip_version = 4;
	पूर्ण अन्यथा अगर (family == AF_INET6) अणु
		key.endpoपूर्णांक_ip.v6 = tun_info->key.u.ipv6.src;
		key.ip_version = 6;
	पूर्ण

	err = mlx5e_set_vf_tunnel(esw, attr, &parse_attr->mod_hdr_acts, e->out_dev,
				  e->route_dev_अगरindex, out_index);
	अगर (err || !(esw_attr->dests[out_index].flags &
		     MLX5_ESW_DEST_CHAIN_WITH_SRC_PORT_CHANGE))
		वापस err;

	r = mlx5e_route_get_create(priv, &key, parse_attr->mirred_अगरindex[out_index],
				   &tbl_समय_after);
	अगर (IS_ERR(r))
		वापस PTR_ERR(r);
	/* Routing changed concurrently. FIB event handler might have missed new
	 * entry, schedule update.
	 */
	अगर (tbl_समय_beक्रमe != tbl_समय_after) अणु
		err = mlx5e_route_enqueue_update(priv, r, FIB_EVENT_ENTRY_REPLACE);
		अगर (err) अणु
			mlx5e_route_put_locked(priv, r);
			वापस err;
		पूर्ण
	पूर्ण

	flow->encap_routes[out_index].r = r;
	अगर (new_encap_entry)
		list_add(&e->route_list, &r->encap_entries);
	flow->encap_routes[out_index].index = out_index;
	वापस 0;
पूर्ण

व्योम mlx5e_detach_decap_route(काष्ठा mlx5e_priv *priv,
			      काष्ठा mlx5e_tc_flow *flow)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_route_entry *r = flow->decap_route;

	अगर (!r)
		वापस;

	mutex_lock(&esw->offloads.encap_tbl_lock);
	list_del(&flow->decap_routes);
	flow->decap_route = शून्य;

	अगर (!refcount_dec_and_test(&r->refcnt)) अणु
		mutex_unlock(&esw->offloads.encap_tbl_lock);
		वापस;
	पूर्ण
	hash_del_rcu(&r->hlist);
	mutex_unlock(&esw->offloads.encap_tbl_lock);

	mlx5e_route_dealloc(priv, r);
पूर्ण

अटल व्योम mlx5e_detach_encap_route(काष्ठा mlx5e_priv *priv,
				     काष्ठा mlx5e_tc_flow *flow,
				     पूर्णांक out_index)
अणु
	काष्ठा mlx5e_route_entry *r = flow->encap_routes[out_index].r;
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_encap_entry *e, *पंचांगp;

	अगर (!r)
		वापस;

	mutex_lock(&esw->offloads.encap_tbl_lock);
	flow->encap_routes[out_index].r = शून्य;

	अगर (!refcount_dec_and_test(&r->refcnt)) अणु
		mutex_unlock(&esw->offloads.encap_tbl_lock);
		वापस;
	पूर्ण
	list_क्रम_each_entry_safe(e, पंचांगp, &r->encap_entries, route_list)
		list_del_init(&e->route_list);
	hash_del_rcu(&r->hlist);
	mutex_unlock(&esw->offloads.encap_tbl_lock);

	mlx5e_route_dealloc(priv, r);
पूर्ण

अटल व्योम mlx5e_invalidate_encap(काष्ठा mlx5e_priv *priv,
				   काष्ठा mlx5e_encap_entry *e,
				   काष्ठा list_head *encap_flows)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_flow *flow;

	list_क्रम_each_entry(flow, encap_flows, पंचांगp_list) अणु
		काष्ठा mlx5_flow_attr *attr = flow->attr;
		काष्ठा mlx5_esw_flow_attr *esw_attr;

		अगर (!mlx5e_is_offloaded_flow(flow))
			जारी;
		esw_attr = attr->esw_attr;

		अगर (flow_flag_test(flow, SLOW))
			mlx5e_tc_unoffload_from_slow_path(esw, flow);
		अन्यथा
			mlx5e_tc_unoffload_fdb_rules(esw, flow, flow->attr);
		mlx5_modअगरy_header_dealloc(priv->mdev, attr->modअगरy_hdr);
		attr->modअगरy_hdr = शून्य;

		esw_attr->dests[flow->पंचांगp_entry_index].flags &=
			~MLX5_ESW_DEST_ENCAP_VALID;
		esw_attr->dests[flow->पंचांगp_entry_index].pkt_reक्रमmat = शून्य;
	पूर्ण

	e->flags |= MLX5_ENCAP_ENTRY_NO_ROUTE;
	अगर (e->flags & MLX5_ENCAP_ENTRY_VALID) अणु
		e->flags &= ~MLX5_ENCAP_ENTRY_VALID;
		mlx5_packet_reक्रमmat_dealloc(priv->mdev, e->pkt_reक्रमmat);
		e->pkt_reक्रमmat = शून्य;
	पूर्ण
पूर्ण

अटल व्योम mlx5e_reoffload_encap(काष्ठा mlx5e_priv *priv,
				  काष्ठा net_device *tunnel_dev,
				  काष्ठा mlx5e_encap_entry *e,
				  काष्ठा list_head *encap_flows)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_flow *flow;
	पूर्णांक err;

	err = ip_tunnel_info_af(e->tun_info) == AF_INET ?
		mlx5e_tc_tun_update_header_ipv4(priv, tunnel_dev, e) :
		mlx5e_tc_tun_update_header_ipv6(priv, tunnel_dev, e);
	अगर (err)
		mlx5_core_warn(priv->mdev, "Failed to update encap header, %d", err);
	e->flags &= ~MLX5_ENCAP_ENTRY_NO_ROUTE;

	list_क्रम_each_entry(flow, encap_flows, पंचांगp_list) अणु
		काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
		काष्ठा mlx5_flow_attr *attr = flow->attr;
		काष्ठा mlx5_esw_flow_attr *esw_attr;
		काष्ठा mlx5_flow_handle *rule;
		काष्ठा mlx5_flow_spec *spec;

		अगर (flow_flag_test(flow, FAILED))
			जारी;

		esw_attr = attr->esw_attr;
		parse_attr = attr->parse_attr;
		spec = &parse_attr->spec;

		err = mlx5e_update_vf_tunnel(esw, esw_attr, &parse_attr->mod_hdr_acts,
					     e->out_dev, e->route_dev_अगरindex,
					     flow->पंचांगp_entry_index);
		अगर (err) अणु
			mlx5_core_warn(priv->mdev, "Failed to update VF tunnel err=%d", err);
			जारी;
		पूर्ण

		err = mlx5e_tc_add_flow_mod_hdr(priv, parse_attr, flow);
		अगर (err) अणु
			mlx5_core_warn(priv->mdev, "Failed to update flow mod_hdr err=%d",
				       err);
			जारी;
		पूर्ण

		अगर (e->flags & MLX5_ENCAP_ENTRY_VALID) अणु
			esw_attr->dests[flow->पंचांगp_entry_index].pkt_reक्रमmat = e->pkt_reक्रमmat;
			esw_attr->dests[flow->पंचांगp_entry_index].flags |= MLX5_ESW_DEST_ENCAP_VALID;
			अगर (!mlx5e_tc_flow_all_encaps_valid(esw_attr))
				जाओ offload_to_slow_path;
			/* update from slow path rule to encap rule */
			rule = mlx5e_tc_offload_fdb_rules(esw, flow, spec, attr);
			अगर (IS_ERR(rule)) अणु
				err = PTR_ERR(rule);
				mlx5_core_warn(priv->mdev, "Failed to update cached encapsulation flow, %d\n",
					       err);
			पूर्ण अन्यथा अणु
				flow->rule[0] = rule;
			पूर्ण
		पूर्ण अन्यथा अणु
offload_to_slow_path:
			rule = mlx5e_tc_offload_to_slow_path(esw, flow, spec);
			/* mark the flow's encap dest as non-valid */
			esw_attr->dests[flow->पंचांगp_entry_index].flags &=
				~MLX5_ESW_DEST_ENCAP_VALID;

			अगर (IS_ERR(rule)) अणु
				err = PTR_ERR(rule);
				mlx5_core_warn(priv->mdev, "Failed to update slow path (encap) flow, %d\n",
					       err);
			पूर्ण अन्यथा अणु
				flow->rule[0] = rule;
			पूर्ण
		पूर्ण
		flow_flag_set(flow, OFFLOADED);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_update_route_encaps(काष्ठा mlx5e_priv *priv,
				     काष्ठा mlx5e_route_entry *r,
				     काष्ठा list_head *flow_list,
				     bool replace)
अणु
	काष्ठा net_device *tunnel_dev;
	काष्ठा mlx5e_encap_entry *e;

	tunnel_dev = __dev_get_by_index(dev_net(priv->netdev), r->tunnel_dev_index);
	अगर (!tunnel_dev)
		वापस -ENODEV;

	list_क्रम_each_entry(e, &r->encap_entries, route_list) अणु
		LIST_HEAD(encap_flows);

		mlx5e_take_all_encap_flows(e, &encap_flows);
		अगर (list_empty(&encap_flows))
			जारी;

		अगर (mlx5e_route_entry_valid(r))
			mlx5e_invalidate_encap(priv, e, &encap_flows);

		अगर (!replace) अणु
			list_splice(&encap_flows, flow_list);
			जारी;
		पूर्ण

		mlx5e_reoffload_encap(priv, tunnel_dev, e, &encap_flows);
		list_splice(&encap_flows, flow_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5e_unoffload_flow_list(काष्ठा mlx5e_priv *priv,
				      काष्ठा list_head *flow_list)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_flow *flow;

	list_क्रम_each_entry(flow, flow_list, पंचांगp_list)
		अगर (mlx5e_is_offloaded_flow(flow))
			mlx5e_tc_unoffload_fdb_rules(esw, flow, flow->attr);
पूर्ण

अटल व्योम mlx5e_reoffload_decap(काष्ठा mlx5e_priv *priv,
				  काष्ठा list_head *decap_flows)
अणु
	काष्ठा mlx5_eचयन *esw = priv->mdev->priv.eचयन;
	काष्ठा mlx5e_tc_flow *flow;

	list_क्रम_each_entry(flow, decap_flows, पंचांगp_list) अणु
		काष्ठा mlx5e_tc_flow_parse_attr *parse_attr;
		काष्ठा mlx5_flow_attr *attr = flow->attr;
		काष्ठा mlx5_flow_handle *rule;
		काष्ठा mlx5_flow_spec *spec;
		पूर्णांक err;

		अगर (flow_flag_test(flow, FAILED))
			जारी;

		parse_attr = attr->parse_attr;
		spec = &parse_attr->spec;
		err = mlx5e_tc_tun_route_lookup(priv, spec, attr);
		अगर (err) अणु
			mlx5_core_warn(priv->mdev, "Failed to lookup route for flow, %d\n",
				       err);
			जारी;
		पूर्ण

		rule = mlx5e_tc_offload_fdb_rules(esw, flow, spec, attr);
		अगर (IS_ERR(rule)) अणु
			err = PTR_ERR(rule);
			mlx5_core_warn(priv->mdev, "Failed to update cached decap flow, %d\n",
				       err);
		पूर्ण अन्यथा अणु
			flow->rule[0] = rule;
			flow_flag_set(flow, OFFLOADED);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5e_update_route_decap_flows(काष्ठा mlx5e_priv *priv,
					  काष्ठा mlx5e_route_entry *r,
					  काष्ठा list_head *flow_list,
					  bool replace)
अणु
	काष्ठा net_device *tunnel_dev;
	LIST_HEAD(decap_flows);

	tunnel_dev = __dev_get_by_index(dev_net(priv->netdev), r->tunnel_dev_index);
	अगर (!tunnel_dev)
		वापस -ENODEV;

	mlx5e_take_all_route_decap_flows(r, &decap_flows);
	अगर (mlx5e_route_entry_valid(r))
		mlx5e_unoffload_flow_list(priv, &decap_flows);
	अगर (replace)
		mlx5e_reoffload_decap(priv, &decap_flows);

	list_splice(&decap_flows, flow_list);

	वापस 0;
पूर्ण

अटल व्योम mlx5e_tc_fib_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5e_tc_fib_event_data *event_data =
		container_of(work, काष्ठा mlx5e_tc_fib_event_data, work);
	काष्ठा net_device *ul_dev = event_data->ul_dev;
	काष्ठा mlx5e_priv *priv = netdev_priv(ul_dev);
	काष्ठा mlx5e_route_entry *r = event_data->r;
	काष्ठा mlx5_eचयन *esw;
	LIST_HEAD(flow_list);
	bool replace;
	पूर्णांक err;

	/* sync with concurrent neigh updates */
	rtnl_lock();
	esw = priv->mdev->priv.eचयन;
	mutex_lock(&esw->offloads.encap_tbl_lock);
	replace = event_data->event == FIB_EVENT_ENTRY_REPLACE;

	अगर (!mlx5e_route_entry_valid(r) && !replace)
		जाओ out;

	err = mlx5e_update_route_encaps(priv, r, &flow_list, replace);
	अगर (err)
		mlx5_core_warn(priv->mdev, "Failed to update route encaps, %d\n",
			       err);

	err = mlx5e_update_route_decap_flows(priv, r, &flow_list, replace);
	अगर (err)
		mlx5_core_warn(priv->mdev, "Failed to update route decap flows, %d\n",
			       err);

	अगर (replace)
		r->flags |= MLX5E_ROUTE_ENTRY_VALID;
out:
	mutex_unlock(&esw->offloads.encap_tbl_lock);
	rtnl_unlock();

	mlx5e_put_flow_list(priv, &flow_list);
	mlx5e_route_put(priv, event_data->r);
	dev_put(event_data->ul_dev);
	kमुक्त(event_data);
पूर्ण

अटल काष्ठा mlx5e_tc_fib_event_data *
mlx5e_init_fib_work_ipv4(काष्ठा mlx5e_priv *priv,
			 काष्ठा net_device *ul_dev,
			 काष्ठा mlx5e_tc_tun_encap *encap,
			 अचिन्हित दीर्घ event,
			 काष्ठा fib_notअगरier_info *info)
अणु
	काष्ठा fib_entry_notअगरier_info *fen_info;
	काष्ठा mlx5e_tc_fib_event_data *fib_work;
	काष्ठा mlx5e_route_entry *r;
	काष्ठा mlx5e_route_key key;
	काष्ठा net_device *fib_dev;

	fen_info = container_of(info, काष्ठा fib_entry_notअगरier_info, info);
	fib_dev = fib_info_nh(fen_info->fi, 0)->fib_nh_dev;
	अगर (!fib_dev || fib_dev->netdev_ops != &mlx5e_netdev_ops ||
	    fen_info->dst_len != 32)
		वापस शून्य;

	fib_work = mlx5e_tc_init_fib_work(event, ul_dev, GFP_ATOMIC);
	अगर (!fib_work)
		वापस ERR_PTR(-ENOMEM);

	key.endpoपूर्णांक_ip.v4 = htonl(fen_info->dst);
	key.ip_version = 4;

	/* Can't fail after this poपूर्णांक because releasing reference to r
	 * requires obtaining sleeping mutex which we can't करो in atomic
	 * context.
	 */
	r = mlx5e_route_lookup_क्रम_update(encap, &key);
	अगर (!r)
		जाओ out;
	fib_work->r = r;
	dev_hold(ul_dev);

	वापस fib_work;

out:
	kमुक्त(fib_work);
	वापस शून्य;
पूर्ण

अटल काष्ठा mlx5e_tc_fib_event_data *
mlx5e_init_fib_work_ipv6(काष्ठा mlx5e_priv *priv,
			 काष्ठा net_device *ul_dev,
			 काष्ठा mlx5e_tc_tun_encap *encap,
			 अचिन्हित दीर्घ event,
			 काष्ठा fib_notअगरier_info *info)
अणु
	काष्ठा fib6_entry_notअगरier_info *fen_info;
	काष्ठा mlx5e_tc_fib_event_data *fib_work;
	काष्ठा mlx5e_route_entry *r;
	काष्ठा mlx5e_route_key key;
	काष्ठा net_device *fib_dev;

	fen_info = container_of(info, काष्ठा fib6_entry_notअगरier_info, info);
	fib_dev = fib6_info_nh_dev(fen_info->rt);
	अगर (fib_dev->netdev_ops != &mlx5e_netdev_ops ||
	    fen_info->rt->fib6_dst.plen != 128)
		वापस शून्य;

	fib_work = mlx5e_tc_init_fib_work(event, ul_dev, GFP_ATOMIC);
	अगर (!fib_work)
		वापस ERR_PTR(-ENOMEM);

	स_नकल(&key.endpoपूर्णांक_ip.v6, &fen_info->rt->fib6_dst.addr,
	       माप(fen_info->rt->fib6_dst.addr));
	key.ip_version = 6;

	/* Can't fail after this poपूर्णांक because releasing reference to r
	 * requires obtaining sleeping mutex which we can't करो in atomic
	 * context.
	 */
	r = mlx5e_route_lookup_क्रम_update(encap, &key);
	अगर (!r)
		जाओ out;
	fib_work->r = r;
	dev_hold(ul_dev);

	वापस fib_work;

out:
	kमुक्त(fib_work);
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlx5e_tc_tun_fib_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा mlx5e_tc_fib_event_data *fib_work;
	काष्ठा fib_notअगरier_info *info = ptr;
	काष्ठा mlx5e_tc_tun_encap *encap;
	काष्ठा net_device *ul_dev;
	काष्ठा mlx5e_priv *priv;

	encap = container_of(nb, काष्ठा mlx5e_tc_tun_encap, fib_nb);
	priv = encap->priv;
	ul_dev = priv->netdev;
	priv = netdev_priv(ul_dev);

	चयन (event) अणु
	हाल FIB_EVENT_ENTRY_REPLACE:
	हाल FIB_EVENT_ENTRY_DEL:
		अगर (info->family == AF_INET)
			fib_work = mlx5e_init_fib_work_ipv4(priv, ul_dev, encap, event, info);
		अन्यथा अगर (info->family == AF_INET6)
			fib_work = mlx5e_init_fib_work_ipv6(priv, ul_dev, encap, event, info);
		अन्यथा
			वापस NOTIFY_DONE;

		अगर (!IS_ERR_OR_शून्य(fib_work)) अणु
			queue_work(priv->wq, &fib_work->work);
		पूर्ण अन्यथा अगर (IS_ERR(fib_work)) अणु
			NL_SET_ERR_MSG_MOD(info->extack, "Failed to init fib work");
			mlx5_core_warn(priv->mdev, "Failed to init fib work, %ld\n",
				       PTR_ERR(fib_work));
		पूर्ण

		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

काष्ठा mlx5e_tc_tun_encap *mlx5e_tc_tun_init(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5e_tc_tun_encap *encap;
	पूर्णांक err;

	encap = kvzalloc(माप(*encap), GFP_KERNEL);
	अगर (!encap)
		वापस ERR_PTR(-ENOMEM);

	encap->priv = priv;
	encap->fib_nb.notअगरier_call = mlx5e_tc_tun_fib_event;
	spin_lock_init(&encap->route_lock);
	hash_init(encap->route_tbl);
	err = रेजिस्टर_fib_notअगरier(dev_net(priv->netdev), &encap->fib_nb,
				    शून्य, शून्य);
	अगर (err) अणु
		kvमुक्त(encap);
		वापस ERR_PTR(err);
	पूर्ण

	वापस encap;
पूर्ण

व्योम mlx5e_tc_tun_cleanup(काष्ठा mlx5e_tc_tun_encap *encap)
अणु
	अगर (!encap)
		वापस;

	unरेजिस्टर_fib_notअगरier(dev_net(encap->priv->netdev), &encap->fib_nb);
	flush_workqueue(encap->priv->wq); /* flush fib event works */
	kvमुक्त(encap);
पूर्ण
