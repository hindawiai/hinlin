<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Linux INET6 implementation
 *	Forwarding Inक्रमmation Database
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Changes:
 *	Yuji SEKIYA @USAGI:	Support शेष route on router node;
 *				हटाओ ip6_null_entry from the top of
 *				routing table.
 *	Ville Nuorvala:		Fixed routing subtrees.
 */

#घोषणा pr_fmt(fmt) "IPv6: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/route.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in6.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <net/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/ndisc.h>
#समावेश <net/addrconf.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/fib_notअगरier.h>

#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>

अटल काष्ठा kmem_cache *fib6_node_kmem __पढ़ो_mostly;

काष्ठा fib6_cleaner अणु
	काष्ठा fib6_walker w;
	काष्ठा net *net;
	पूर्णांक (*func)(काष्ठा fib6_info *, व्योम *arg);
	पूर्णांक sernum;
	व्योम *arg;
	bool skip_notअगरy;
पूर्ण;

#अगर_घोषित CONFIG_IPV6_SUBTREES
#घोषणा FWS_INIT FWS_S
#अन्यथा
#घोषणा FWS_INIT FWS_L
#पूर्ण_अगर

अटल काष्ठा fib6_info *fib6_find_prefix(काष्ठा net *net,
					 काष्ठा fib6_table *table,
					 काष्ठा fib6_node *fn);
अटल काष्ठा fib6_node *fib6_repair_tree(काष्ठा net *net,
					  काष्ठा fib6_table *table,
					  काष्ठा fib6_node *fn);
अटल पूर्णांक fib6_walk(काष्ठा net *net, काष्ठा fib6_walker *w);
अटल पूर्णांक fib6_walk_जारी(काष्ठा fib6_walker *w);

/*
 *	A routing update causes an increase of the serial number on the
 *	affected subtree. This allows क्रम cached routes to be asynchronously
 *	tested when modअगरications are made to the destination cache as a
 *	result of redirects, path MTU changes, etc.
 */

अटल व्योम fib6_gc_समयr_cb(काष्ठा समयr_list *t);

#घोषणा FOR_WALKERS(net, w) \
	list_क्रम_each_entry(w, &(net)->ipv6.fib6_walkers, lh)

अटल व्योम fib6_walker_link(काष्ठा net *net, काष्ठा fib6_walker *w)
अणु
	ग_लिखो_lock_bh(&net->ipv6.fib6_walker_lock);
	list_add(&w->lh, &net->ipv6.fib6_walkers);
	ग_लिखो_unlock_bh(&net->ipv6.fib6_walker_lock);
पूर्ण

अटल व्योम fib6_walker_unlink(काष्ठा net *net, काष्ठा fib6_walker *w)
अणु
	ग_लिखो_lock_bh(&net->ipv6.fib6_walker_lock);
	list_del(&w->lh);
	ग_लिखो_unlock_bh(&net->ipv6.fib6_walker_lock);
पूर्ण

अटल पूर्णांक fib6_new_sernum(काष्ठा net *net)
अणु
	पूर्णांक new, old;

	करो अणु
		old = atomic_पढ़ो(&net->ipv6.fib6_sernum);
		new = old < पूर्णांक_उच्च ? old + 1 : 1;
	पूर्ण जबतक (atomic_cmpxchg(&net->ipv6.fib6_sernum,
				old, new) != old);
	वापस new;
पूर्ण

क्रमागत अणु
	FIB6_NO_SERNUM_CHANGE = 0,
पूर्ण;

व्योम fib6_update_sernum(काष्ठा net *net, काष्ठा fib6_info *f6i)
अणु
	काष्ठा fib6_node *fn;

	fn = rcu_dereference_रक्षित(f6i->fib6_node,
			lockdep_is_held(&f6i->fib6_table->tb6_lock));
	अगर (fn)
		fn->fn_sernum = fib6_new_sernum(net);
पूर्ण

/*
 *	Auxiliary address test functions क्रम the radix tree.
 *
 *	These assume a 32bit processor (although it will work on
 *	64bit processors)
 */

/*
 *	test bit
 */
#अगर defined(__LITTLE_ENDIAN)
# define BITOP_BE32_SWIZZLE	(0x1F & ~7)
#अन्यथा
# define BITOP_BE32_SWIZZLE	0
#पूर्ण_अगर

अटल __be32 addr_bit_set(स्थिर व्योम *token, पूर्णांक fn_bit)
अणु
	स्थिर __be32 *addr = token;
	/*
	 * Here,
	 *	1 << ((~fn_bit ^ BITOP_BE32_SWIZZLE) & 0x1f)
	 * is optimized version of
	 *	htonl(1 << ((~fn_bit)&0x1F))
	 * See include/यंत्र-generic/bitops/le.h.
	 */
	वापस (__क्रमce __be32)(1 << ((~fn_bit ^ BITOP_BE32_SWIZZLE) & 0x1f)) &
	       addr[fn_bit >> 5];
पूर्ण

काष्ठा fib6_info *fib6_info_alloc(gfp_t gfp_flags, bool with_fib6_nh)
अणु
	काष्ठा fib6_info *f6i;
	माप_प्रकार sz = माप(*f6i);

	अगर (with_fib6_nh)
		sz += माप(काष्ठा fib6_nh);

	f6i = kzalloc(sz, gfp_flags);
	अगर (!f6i)
		वापस शून्य;

	/* fib6_siblings is a जोड़ with nh_list, so this initializes both */
	INIT_LIST_HEAD(&f6i->fib6_siblings);
	refcount_set(&f6i->fib6_ref, 1);

	वापस f6i;
पूर्ण

व्योम fib6_info_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा fib6_info *f6i = container_of(head, काष्ठा fib6_info, rcu);

	WARN_ON(f6i->fib6_node);

	अगर (f6i->nh)
		nexthop_put(f6i->nh);
	अन्यथा
		fib6_nh_release(f6i->fib6_nh);

	ip_fib_metrics_put(f6i->fib6_metrics);
	kमुक्त(f6i);
पूर्ण
EXPORT_SYMBOL_GPL(fib6_info_destroy_rcu);

अटल काष्ठा fib6_node *node_alloc(काष्ठा net *net)
अणु
	काष्ठा fib6_node *fn;

	fn = kmem_cache_zalloc(fib6_node_kmem, GFP_ATOMIC);
	अगर (fn)
		net->ipv6.rt6_stats->fib_nodes++;

	वापस fn;
पूर्ण

अटल व्योम node_मुक्त_immediate(काष्ठा net *net, काष्ठा fib6_node *fn)
अणु
	kmem_cache_मुक्त(fib6_node_kmem, fn);
	net->ipv6.rt6_stats->fib_nodes--;
पूर्ण

अटल व्योम node_मुक्त_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा fib6_node *fn = container_of(head, काष्ठा fib6_node, rcu);

	kmem_cache_मुक्त(fib6_node_kmem, fn);
पूर्ण

अटल व्योम node_मुक्त(काष्ठा net *net, काष्ठा fib6_node *fn)
अणु
	call_rcu(&fn->rcu, node_मुक्त_rcu);
	net->ipv6.rt6_stats->fib_nodes--;
पूर्ण

अटल व्योम fib6_मुक्त_table(काष्ठा fib6_table *table)
अणु
	inetpeer_invalidate_tree(&table->tb6_peers);
	kमुक्त(table);
पूर्ण

अटल व्योम fib6_link_table(काष्ठा net *net, काष्ठा fib6_table *tb)
अणु
	अचिन्हित पूर्णांक h;

	/*
	 * Initialize table lock at a single place to give lockdep a key,
	 * tables aren't visible prior to being linked to the list.
	 */
	spin_lock_init(&tb->tb6_lock);
	h = tb->tb6_id & (FIB6_TABLE_HASHSZ - 1);

	/*
	 * No protection necessary, this is the only list mutatation
	 * operation, tables never disappear once they exist.
	 */
	hlist_add_head_rcu(&tb->tb6_hlist, &net->ipv6.fib_table_hash[h]);
पूर्ण

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES

अटल काष्ठा fib6_table *fib6_alloc_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा fib6_table *table;

	table = kzalloc(माप(*table), GFP_ATOMIC);
	अगर (table) अणु
		table->tb6_id = id;
		rcu_assign_poपूर्णांकer(table->tb6_root.leaf,
				   net->ipv6.fib6_null_entry);
		table->tb6_root.fn_flags = RTN_ROOT | RTN_TL_ROOT | RTN_RTINFO;
		inet_peer_base_init(&table->tb6_peers);
	पूर्ण

	वापस table;
पूर्ण

काष्ठा fib6_table *fib6_new_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा fib6_table *tb;

	अगर (id == 0)
		id = RT6_TABLE_MAIN;
	tb = fib6_get_table(net, id);
	अगर (tb)
		वापस tb;

	tb = fib6_alloc_table(net, id);
	अगर (tb)
		fib6_link_table(net, tb);

	वापस tb;
पूर्ण
EXPORT_SYMBOL_GPL(fib6_new_table);

काष्ठा fib6_table *fib6_get_table(काष्ठा net *net, u32 id)
अणु
	काष्ठा fib6_table *tb;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक h;

	अगर (id == 0)
		id = RT6_TABLE_MAIN;
	h = id & (FIB6_TABLE_HASHSZ - 1);
	rcu_पढ़ो_lock();
	head = &net->ipv6.fib_table_hash[h];
	hlist_क्रम_each_entry_rcu(tb, head, tb6_hlist) अणु
		अगर (tb->tb6_id == id) अणु
			rcu_पढ़ो_unlock();
			वापस tb;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fib6_get_table);

अटल व्योम __net_init fib6_tables_init(काष्ठा net *net)
अणु
	fib6_link_table(net, net->ipv6.fib6_मुख्य_tbl);
	fib6_link_table(net, net->ipv6.fib6_local_tbl);
पूर्ण
#अन्यथा

काष्ठा fib6_table *fib6_new_table(काष्ठा net *net, u32 id)
अणु
	वापस fib6_get_table(net, id);
पूर्ण

काष्ठा fib6_table *fib6_get_table(काष्ठा net *net, u32 id)
अणु
	  वापस net->ipv6.fib6_मुख्य_tbl;
पूर्ण

काष्ठा dst_entry *fib6_rule_lookup(काष्ठा net *net, काष्ठा flowi6 *fl6,
				   स्थिर काष्ठा sk_buff *skb,
				   पूर्णांक flags, pol_lookup_t lookup)
अणु
	काष्ठा rt6_info *rt;

	rt = pol_lookup_func(lookup,
			net, net->ipv6.fib6_मुख्य_tbl, fl6, skb, flags);
	अगर (rt->dst.error == -EAGAIN) अणु
		ip6_rt_put_flags(rt, flags);
		rt = net->ipv6.ip6_null_entry;
		अगर (!(flags & RT6_LOOKUP_F_DST_NOREF))
			dst_hold(&rt->dst);
	पूर्ण

	वापस &rt->dst;
पूर्ण

/* called with rcu lock held; no reference taken on fib6_info */
पूर्णांक fib6_lookup(काष्ठा net *net, पूर्णांक oअगर, काष्ठा flowi6 *fl6,
		काष्ठा fib6_result *res, पूर्णांक flags)
अणु
	वापस fib6_table_lookup(net, net->ipv6.fib6_मुख्य_tbl, oअगर, fl6,
				 res, flags);
पूर्ण

अटल व्योम __net_init fib6_tables_init(काष्ठा net *net)
अणु
	fib6_link_table(net, net->ipv6.fib6_मुख्य_tbl);
पूर्ण

#पूर्ण_अगर

अचिन्हित पूर्णांक fib6_tables_seq_पढ़ो(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक h, fib_seq = 0;

	rcu_पढ़ो_lock();
	क्रम (h = 0; h < FIB6_TABLE_HASHSZ; h++) अणु
		काष्ठा hlist_head *head = &net->ipv6.fib_table_hash[h];
		काष्ठा fib6_table *tb;

		hlist_क्रम_each_entry_rcu(tb, head, tb6_hlist)
			fib_seq += tb->fib_seq;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस fib_seq;
पूर्ण

अटल पूर्णांक call_fib6_entry_notअगरier(काष्ठा notअगरier_block *nb,
				    क्रमागत fib_event_type event_type,
				    काष्ठा fib6_info *rt,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_entry_notअगरier_info info = अणु
		.info.extack = extack,
		.rt = rt,
	पूर्ण;

	वापस call_fib6_notअगरier(nb, event_type, &info.info);
पूर्ण

अटल पूर्णांक call_fib6_multipath_entry_notअगरier(काष्ठा notअगरier_block *nb,
					      क्रमागत fib_event_type event_type,
					      काष्ठा fib6_info *rt,
					      अचिन्हित पूर्णांक nsiblings,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_entry_notअगरier_info info = अणु
		.info.extack = extack,
		.rt = rt,
		.nsiblings = nsiblings,
	पूर्ण;

	वापस call_fib6_notअगरier(nb, event_type, &info.info);
पूर्ण

पूर्णांक call_fib6_entry_notअगरiers(काष्ठा net *net,
			      क्रमागत fib_event_type event_type,
			      काष्ठा fib6_info *rt,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_entry_notअगरier_info info = अणु
		.info.extack = extack,
		.rt = rt,
	पूर्ण;

	rt->fib6_table->fib_seq++;
	वापस call_fib6_notअगरiers(net, event_type, &info.info);
पूर्ण

पूर्णांक call_fib6_multipath_entry_notअगरiers(काष्ठा net *net,
					क्रमागत fib_event_type event_type,
					काष्ठा fib6_info *rt,
					अचिन्हित पूर्णांक nsiblings,
					काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_entry_notअगरier_info info = अणु
		.info.extack = extack,
		.rt = rt,
		.nsiblings = nsiblings,
	पूर्ण;

	rt->fib6_table->fib_seq++;
	वापस call_fib6_notअगरiers(net, event_type, &info.info);
पूर्ण

पूर्णांक call_fib6_entry_notअगरiers_replace(काष्ठा net *net, काष्ठा fib6_info *rt)
अणु
	काष्ठा fib6_entry_notअगरier_info info = अणु
		.rt = rt,
		.nsiblings = rt->fib6_nsiblings,
	पूर्ण;

	rt->fib6_table->fib_seq++;
	वापस call_fib6_notअगरiers(net, FIB_EVENT_ENTRY_REPLACE, &info.info);
पूर्ण

काष्ठा fib6_dump_arg अणु
	काष्ठा net *net;
	काष्ठा notअगरier_block *nb;
	काष्ठा netlink_ext_ack *extack;
पूर्ण;

अटल पूर्णांक fib6_rt_dump(काष्ठा fib6_info *rt, काष्ठा fib6_dump_arg *arg)
अणु
	क्रमागत fib_event_type fib_event = FIB_EVENT_ENTRY_REPLACE;
	पूर्णांक err;

	अगर (!rt || rt == arg->net->ipv6.fib6_null_entry)
		वापस 0;

	अगर (rt->fib6_nsiblings)
		err = call_fib6_multipath_entry_notअगरier(arg->nb, fib_event,
							 rt,
							 rt->fib6_nsiblings,
							 arg->extack);
	अन्यथा
		err = call_fib6_entry_notअगरier(arg->nb, fib_event, rt,
					       arg->extack);

	वापस err;
पूर्ण

अटल पूर्णांक fib6_node_dump(काष्ठा fib6_walker *w)
अणु
	पूर्णांक err;

	err = fib6_rt_dump(w->leaf, w->args);
	w->leaf = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक fib6_table_dump(काष्ठा net *net, काष्ठा fib6_table *tb,
			   काष्ठा fib6_walker *w)
अणु
	पूर्णांक err;

	w->root = &tb->tb6_root;
	spin_lock_bh(&tb->tb6_lock);
	err = fib6_walk(net, w);
	spin_unlock_bh(&tb->tb6_lock);
	वापस err;
पूर्ण

/* Called with rcu_पढ़ो_lock() */
पूर्णांक fib6_tables_dump(काष्ठा net *net, काष्ठा notअगरier_block *nb,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_dump_arg arg;
	काष्ठा fib6_walker *w;
	अचिन्हित पूर्णांक h;
	पूर्णांक err = 0;

	w = kzalloc(माप(*w), GFP_ATOMIC);
	अगर (!w)
		वापस -ENOMEM;

	w->func = fib6_node_dump;
	arg.net = net;
	arg.nb = nb;
	arg.extack = extack;
	w->args = &arg;

	क्रम (h = 0; h < FIB6_TABLE_HASHSZ; h++) अणु
		काष्ठा hlist_head *head = &net->ipv6.fib_table_hash[h];
		काष्ठा fib6_table *tb;

		hlist_क्रम_each_entry_rcu(tb, head, tb6_hlist) अणु
			err = fib6_table_dump(net, tb, w);
			अगर (err)
				जाओ out;
		पूर्ण
	पूर्ण

out:
	kमुक्त(w);

	/* The tree traversal function should never वापस a positive value. */
	वापस err > 0 ? -EINVAL : err;
पूर्ण

अटल पूर्णांक fib6_dump_node(काष्ठा fib6_walker *w)
अणु
	पूर्णांक res;
	काष्ठा fib6_info *rt;

	क्रम_each_fib6_walker_rt(w) अणु
		res = rt6_dump_route(rt, w->args, w->skip_in_node);
		अगर (res >= 0) अणु
			/* Frame is full, suspend walking */
			w->leaf = rt;

			/* We'll restart from this node, so अगर some routes were
			 * alपढ़ोy dumped, skip them next समय.
			 */
			w->skip_in_node += res;

			वापस 1;
		पूर्ण
		w->skip_in_node = 0;

		/* Multipath routes are dumped in one route with the
		 * RTA_MULTIPATH attribute. Jump 'rt' to poपूर्णांक to the
		 * last sibling of this route (no need to dump the
		 * sibling routes again)
		 */
		अगर (rt->fib6_nsiblings)
			rt = list_last_entry(&rt->fib6_siblings,
					     काष्ठा fib6_info,
					     fib6_siblings);
	पूर्ण
	w->leaf = शून्य;
	वापस 0;
पूर्ण

अटल व्योम fib6_dump_end(काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा fib6_walker *w = (व्योम *)cb->args[2];

	अगर (w) अणु
		अगर (cb->args[4]) अणु
			cb->args[4] = 0;
			fib6_walker_unlink(net, w);
		पूर्ण
		cb->args[2] = 0;
		kमुक्त(w);
	पूर्ण
	cb->करोne = (व्योम *)cb->args[3];
	cb->args[1] = 3;
पूर्ण

अटल पूर्णांक fib6_dump_करोne(काष्ठा netlink_callback *cb)
अणु
	fib6_dump_end(cb);
	वापस cb->करोne ? cb->करोne(cb) : 0;
पूर्ण

अटल पूर्णांक fib6_dump_table(काष्ठा fib6_table *table, काष्ठा sk_buff *skb,
			   काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा fib6_walker *w;
	पूर्णांक res;

	w = (व्योम *)cb->args[2];
	w->root = &table->tb6_root;

	अगर (cb->args[4] == 0) अणु
		w->count = 0;
		w->skip = 0;
		w->skip_in_node = 0;

		spin_lock_bh(&table->tb6_lock);
		res = fib6_walk(net, w);
		spin_unlock_bh(&table->tb6_lock);
		अगर (res > 0) अणु
			cb->args[4] = 1;
			cb->args[5] = w->root->fn_sernum;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cb->args[5] != w->root->fn_sernum) अणु
			/* Begin at the root अगर the tree changed */
			cb->args[5] = w->root->fn_sernum;
			w->state = FWS_INIT;
			w->node = w->root;
			w->skip = w->count;
			w->skip_in_node = 0;
		पूर्ण अन्यथा
			w->skip = 0;

		spin_lock_bh(&table->tb6_lock);
		res = fib6_walk_जारी(w);
		spin_unlock_bh(&table->tb6_lock);
		अगर (res <= 0) अणु
			fib6_walker_unlink(net, w);
			cb->args[4] = 0;
		पूर्ण
	पूर्ण

	वापस res;
पूर्ण

अटल पूर्णांक inet6_dump_fib(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा rt6_rtnl_dump_arg arg = अणु .filter.dump_exceptions = true,
					 .filter.dump_routes = true पूर्ण;
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	अचिन्हित पूर्णांक h, s_h;
	अचिन्हित पूर्णांक e = 0, s_e;
	काष्ठा fib6_walker *w;
	काष्ठा fib6_table *tb;
	काष्ठा hlist_head *head;
	पूर्णांक res = 0;

	अगर (cb->strict_check) अणु
		पूर्णांक err;

		err = ip_valid_fib_dump_req(net, nlh, &arg.filter, cb);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (nlmsg_len(nlh) >= माप(काष्ठा rपंचांगsg)) अणु
		काष्ठा rपंचांगsg *rपंचांग = nlmsg_data(nlh);

		अगर (rपंचांग->rपंचांग_flags & RTM_F_PREFIX)
			arg.filter.flags = RTM_F_PREFIX;
	पूर्ण

	w = (व्योम *)cb->args[2];
	अगर (!w) अणु
		/* New dump:
		 *
		 * 1. hook callback deकाष्ठाor.
		 */
		cb->args[3] = (दीर्घ)cb->करोne;
		cb->करोne = fib6_dump_करोne;

		/*
		 * 2. allocate and initialize walker.
		 */
		w = kzalloc(माप(*w), GFP_ATOMIC);
		अगर (!w)
			वापस -ENOMEM;
		w->func = fib6_dump_node;
		cb->args[2] = (दीर्घ)w;
	पूर्ण

	arg.skb = skb;
	arg.cb = cb;
	arg.net = net;
	w->args = &arg;

	अगर (arg.filter.table_id) अणु
		tb = fib6_get_table(net, arg.filter.table_id);
		अगर (!tb) अणु
			अगर (rtnl_msg_family(cb->nlh) != PF_INET6)
				जाओ out;

			NL_SET_ERR_MSG_MOD(cb->extack, "FIB table does not exist");
			वापस -ENOENT;
		पूर्ण

		अगर (!cb->args[0]) अणु
			res = fib6_dump_table(tb, skb, cb);
			अगर (!res)
				cb->args[0] = 1;
		पूर्ण
		जाओ out;
	पूर्ण

	s_h = cb->args[0];
	s_e = cb->args[1];

	rcu_पढ़ो_lock();
	क्रम (h = s_h; h < FIB6_TABLE_HASHSZ; h++, s_e = 0) अणु
		e = 0;
		head = &net->ipv6.fib_table_hash[h];
		hlist_क्रम_each_entry_rcu(tb, head, tb6_hlist) अणु
			अगर (e < s_e)
				जाओ next;
			res = fib6_dump_table(tb, skb, cb);
			अगर (res != 0)
				जाओ out_unlock;
next:
			e++;
		पूर्ण
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	cb->args[1] = e;
	cb->args[0] = h;
out:
	res = res < 0 ? res : skb->len;
	अगर (res <= 0)
		fib6_dump_end(cb);
	वापस res;
पूर्ण

व्योम fib6_metric_set(काष्ठा fib6_info *f6i, पूर्णांक metric, u32 val)
अणु
	अगर (!f6i)
		वापस;

	अगर (f6i->fib6_metrics == &dst_शेष_metrics) अणु
		काष्ठा dst_metrics *p = kzalloc(माप(*p), GFP_ATOMIC);

		अगर (!p)
			वापस;

		refcount_set(&p->refcnt, 1);
		f6i->fib6_metrics = p;
	पूर्ण

	f6i->fib6_metrics->metrics[metric - 1] = val;
पूर्ण

/*
 *	Routing Table
 *
 *	वापस the appropriate node क्रम a routing tree "add" operation
 *	by either creating and inserting or by वापसing an existing
 *	node.
 */

अटल काष्ठा fib6_node *fib6_add_1(काष्ठा net *net,
				    काष्ठा fib6_table *table,
				    काष्ठा fib6_node *root,
				    काष्ठा in6_addr *addr, पूर्णांक plen,
				    पूर्णांक offset, पूर्णांक allow_create,
				    पूर्णांक replace_required,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_node *fn, *in, *ln;
	काष्ठा fib6_node *pn = शून्य;
	काष्ठा rt6key *key;
	पूर्णांक	bit;
	__be32	dir = 0;

	RT6_TRACE("fib6_add_1\n");

	/* insert node in tree */

	fn = root;

	करो अणु
		काष्ठा fib6_info *leaf = rcu_dereference_रक्षित(fn->leaf,
					    lockdep_is_held(&table->tb6_lock));
		key = (काष्ठा rt6key *)((u8 *)leaf + offset);

		/*
		 *	Prefix match
		 */
		अगर (plen < fn->fn_bit ||
		    !ipv6_prefix_equal(&key->addr, addr, fn->fn_bit)) अणु
			अगर (!allow_create) अणु
				अगर (replace_required) अणु
					NL_SET_ERR_MSG(extack,
						       "Can not replace route - no match found");
					pr_warn("Can't replace route, no match found\n");
					वापस ERR_PTR(-ENOENT);
				पूर्ण
				pr_warn("NLM_F_CREATE should be set when creating new route\n");
			पूर्ण
			जाओ insert_above;
		पूर्ण

		/*
		 *	Exact match ?
		 */

		अगर (plen == fn->fn_bit) अणु
			/* clean up an पूर्णांकermediate node */
			अगर (!(fn->fn_flags & RTN_RTINFO)) अणु
				RCU_INIT_POINTER(fn->leaf, शून्य);
				fib6_info_release(leaf);
			/* हटाओ null_entry in the root node */
			पूर्ण अन्यथा अगर (fn->fn_flags & RTN_TL_ROOT &&
				   rcu_access_poपूर्णांकer(fn->leaf) ==
				   net->ipv6.fib6_null_entry) अणु
				RCU_INIT_POINTER(fn->leaf, शून्य);
			पूर्ण

			वापस fn;
		पूर्ण

		/*
		 *	We have more bits to go
		 */

		/* Try to walk करोwn on tree. */
		dir = addr_bit_set(addr, fn->fn_bit);
		pn = fn;
		fn = dir ?
		     rcu_dereference_रक्षित(fn->right,
					lockdep_is_held(&table->tb6_lock)) :
		     rcu_dereference_रक्षित(fn->left,
					lockdep_is_held(&table->tb6_lock));
	पूर्ण जबतक (fn);

	अगर (!allow_create) अणु
		/* We should not create new node because
		 * NLM_F_REPLACE was specअगरied without NLM_F_CREATE
		 * I assume it is safe to require NLM_F_CREATE when
		 * REPLACE flag is used! Later we may want to हटाओ the
		 * check क्रम replace_required, because according
		 * to netlink specअगरication, NLM_F_CREATE
		 * MUST be specअगरied अगर new route is created.
		 * That would keep IPv6 consistent with IPv4
		 */
		अगर (replace_required) अणु
			NL_SET_ERR_MSG(extack,
				       "Can not replace route - no match found");
			pr_warn("Can't replace route, no match found\n");
			वापस ERR_PTR(-ENOENT);
		पूर्ण
		pr_warn("NLM_F_CREATE should be set when creating new route\n");
	पूर्ण
	/*
	 *	We walked to the bottom of tree.
	 *	Create new leaf node without children.
	 */

	ln = node_alloc(net);

	अगर (!ln)
		वापस ERR_PTR(-ENOMEM);
	ln->fn_bit = plen;
	RCU_INIT_POINTER(ln->parent, pn);

	अगर (dir)
		rcu_assign_poपूर्णांकer(pn->right, ln);
	अन्यथा
		rcu_assign_poपूर्णांकer(pn->left, ln);

	वापस ln;


insert_above:
	/*
	 * split since we करोn't have a common prefix anymore or
	 * we have a less signअगरicant route.
	 * we've to insert an पूर्णांकermediate node on the list
	 * this new node will poपूर्णांक to the one we need to create
	 * and the current
	 */

	pn = rcu_dereference_रक्षित(fn->parent,
				       lockdep_is_held(&table->tb6_lock));

	/* find 1st bit in dअगरference between the 2 addrs.

	   See comment in __ipv6_addr_dअगरf: bit may be an invalid value,
	   but अगर it is >= plen, the value is ignored in any हाल.
	 */

	bit = __ipv6_addr_dअगरf(addr, &key->addr, माप(*addr));

	/*
	 *		(पूर्णांकermediate)[in]
	 *	          /	   \
	 *	(new leaf node)[ln] (old node)[fn]
	 */
	अगर (plen > bit) अणु
		in = node_alloc(net);
		ln = node_alloc(net);

		अगर (!in || !ln) अणु
			अगर (in)
				node_मुक्त_immediate(net, in);
			अगर (ln)
				node_मुक्त_immediate(net, ln);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		/*
		 * new पूर्णांकermediate node.
		 * RTN_RTINFO will
		 * be off since that an address that chooses one of
		 * the branches would not match less specअगरic routes
		 * in the other branch
		 */

		in->fn_bit = bit;

		RCU_INIT_POINTER(in->parent, pn);
		in->leaf = fn->leaf;
		fib6_info_hold(rcu_dereference_रक्षित(in->leaf,
				lockdep_is_held(&table->tb6_lock)));

		/* update parent poपूर्णांकer */
		अगर (dir)
			rcu_assign_poपूर्णांकer(pn->right, in);
		अन्यथा
			rcu_assign_poपूर्णांकer(pn->left, in);

		ln->fn_bit = plen;

		RCU_INIT_POINTER(ln->parent, in);
		rcu_assign_poपूर्णांकer(fn->parent, in);

		अगर (addr_bit_set(addr, bit)) अणु
			rcu_assign_poपूर्णांकer(in->right, ln);
			rcu_assign_poपूर्णांकer(in->left, fn);
		पूर्ण अन्यथा अणु
			rcu_assign_poपूर्णांकer(in->left, ln);
			rcu_assign_poपूर्णांकer(in->right, fn);
		पूर्ण
	पूर्ण अन्यथा अणु /* plen <= bit */

		/*
		 *		(new leaf node)[ln]
		 *	          /	   \
		 *	     (old node)[fn] शून्य
		 */

		ln = node_alloc(net);

		अगर (!ln)
			वापस ERR_PTR(-ENOMEM);

		ln->fn_bit = plen;

		RCU_INIT_POINTER(ln->parent, pn);

		अगर (addr_bit_set(&key->addr, plen))
			RCU_INIT_POINTER(ln->right, fn);
		अन्यथा
			RCU_INIT_POINTER(ln->left, fn);

		rcu_assign_poपूर्णांकer(fn->parent, ln);

		अगर (dir)
			rcu_assign_poपूर्णांकer(pn->right, ln);
		अन्यथा
			rcu_assign_poपूर्णांकer(pn->left, ln);
	पूर्ण
	वापस ln;
पूर्ण

अटल व्योम __fib6_drop_pcpu_from(काष्ठा fib6_nh *fib6_nh,
				  स्थिर काष्ठा fib6_info *match,
				  स्थिर काष्ठा fib6_table *table)
अणु
	पूर्णांक cpu;

	अगर (!fib6_nh->rt6i_pcpu)
		वापस;

	/* release the reference to this fib entry from
	 * all of its cached pcpu routes
	 */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा rt6_info **ppcpu_rt;
		काष्ठा rt6_info *pcpu_rt;

		ppcpu_rt = per_cpu_ptr(fib6_nh->rt6i_pcpu, cpu);
		pcpu_rt = *ppcpu_rt;

		/* only dropping the 'from' reference अगर the cached route
		 * is using 'match'. The cached pcpu_rt->from only changes
		 * from a fib6_info to शून्य (ip6_dst_destroy); it can never
		 * change from one fib6_info reference to another
		 */
		अगर (pcpu_rt && rcu_access_poपूर्णांकer(pcpu_rt->from) == match) अणु
			काष्ठा fib6_info *from;

			from = xchg((__क्रमce काष्ठा fib6_info **)&pcpu_rt->from, शून्य);
			fib6_info_release(from);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा fib6_nh_pcpu_arg अणु
	काष्ठा fib6_info	*from;
	स्थिर काष्ठा fib6_table *table;
पूर्ण;

अटल पूर्णांक fib6_nh_drop_pcpu_from(काष्ठा fib6_nh *nh, व्योम *_arg)
अणु
	काष्ठा fib6_nh_pcpu_arg *arg = _arg;

	__fib6_drop_pcpu_from(nh, arg->from, arg->table);
	वापस 0;
पूर्ण

अटल व्योम fib6_drop_pcpu_from(काष्ठा fib6_info *f6i,
				स्थिर काष्ठा fib6_table *table)
अणु
	/* Make sure rt6_make_pcpu_route() wont add other percpu routes
	 * जबतक we are cleaning them here.
	 */
	f6i->fib6_destroying = 1;
	mb(); /* paired with the cmpxchg() in rt6_make_pcpu_route() */

	अगर (f6i->nh) अणु
		काष्ठा fib6_nh_pcpu_arg arg = अणु
			.from = f6i,
			.table = table
		पूर्ण;

		nexthop_क्रम_each_fib6_nh(f6i->nh, fib6_nh_drop_pcpu_from,
					 &arg);
	पूर्ण अन्यथा अणु
		काष्ठा fib6_nh *fib6_nh;

		fib6_nh = f6i->fib6_nh;
		__fib6_drop_pcpu_from(fib6_nh, f6i, table);
	पूर्ण
पूर्ण

अटल व्योम fib6_purge_rt(काष्ठा fib6_info *rt, काष्ठा fib6_node *fn,
			  काष्ठा net *net)
अणु
	काष्ठा fib6_table *table = rt->fib6_table;

	/* Flush all cached dst in exception table */
	rt6_flush_exceptions(rt);
	fib6_drop_pcpu_from(rt, table);

	अगर (rt->nh && !list_empty(&rt->nh_list))
		list_del_init(&rt->nh_list);

	अगर (refcount_पढ़ो(&rt->fib6_ref) != 1) अणु
		/* This route is used as dummy address holder in some split
		 * nodes. It is not leaked, but it still holds other resources,
		 * which must be released in समय. So, scan ascendant nodes
		 * and replace dummy references to this route with references
		 * to still alive ones.
		 */
		जबतक (fn) अणु
			काष्ठा fib6_info *leaf = rcu_dereference_रक्षित(fn->leaf,
					    lockdep_is_held(&table->tb6_lock));
			काष्ठा fib6_info *new_leaf;
			अगर (!(fn->fn_flags & RTN_RTINFO) && leaf == rt) अणु
				new_leaf = fib6_find_prefix(net, table, fn);
				fib6_info_hold(new_leaf);

				rcu_assign_poपूर्णांकer(fn->leaf, new_leaf);
				fib6_info_release(rt);
			पूर्ण
			fn = rcu_dereference_रक्षित(fn->parent,
				    lockdep_is_held(&table->tb6_lock));
		पूर्ण
	पूर्ण
पूर्ण

/*
 *	Insert routing inक्रमmation in a node.
 */

अटल पूर्णांक fib6_add_rt2node(काष्ठा fib6_node *fn, काष्ठा fib6_info *rt,
			    काष्ठा nl_info *info,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_info *leaf = rcu_dereference_रक्षित(fn->leaf,
				    lockdep_is_held(&rt->fib6_table->tb6_lock));
	काष्ठा fib6_info *iter = शून्य;
	काष्ठा fib6_info __rcu **ins;
	काष्ठा fib6_info __rcu **fallback_ins = शून्य;
	पूर्णांक replace = (info->nlh &&
		       (info->nlh->nlmsg_flags & NLM_F_REPLACE));
	पूर्णांक add = (!info->nlh ||
		   (info->nlh->nlmsg_flags & NLM_F_CREATE));
	पूर्णांक found = 0;
	bool rt_can_ecmp = rt6_qualअगरy_क्रम_ecmp(rt);
	bool notअगरy_sibling_rt = false;
	u16 nlflags = NLM_F_EXCL;
	पूर्णांक err;

	अगर (info->nlh && (info->nlh->nlmsg_flags & NLM_F_APPEND))
		nlflags |= NLM_F_APPEND;

	ins = &fn->leaf;

	क्रम (iter = leaf; iter;
	     iter = rcu_dereference_रक्षित(iter->fib6_next,
				lockdep_is_held(&rt->fib6_table->tb6_lock))) अणु
		/*
		 *	Search क्रम duplicates
		 */

		अगर (iter->fib6_metric == rt->fib6_metric) अणु
			/*
			 *	Same priority level
			 */
			अगर (info->nlh &&
			    (info->nlh->nlmsg_flags & NLM_F_EXCL))
				वापस -EEXIST;

			nlflags &= ~NLM_F_EXCL;
			अगर (replace) अणु
				अगर (rt_can_ecmp == rt6_qualअगरy_क्रम_ecmp(iter)) अणु
					found++;
					अवरोध;
				पूर्ण
				fallback_ins = fallback_ins ?: ins;
				जाओ next_iter;
			पूर्ण

			अगर (rt6_duplicate_nexthop(iter, rt)) अणु
				अगर (rt->fib6_nsiblings)
					rt->fib6_nsiblings = 0;
				अगर (!(iter->fib6_flags & RTF_EXPIRES))
					वापस -EEXIST;
				अगर (!(rt->fib6_flags & RTF_EXPIRES))
					fib6_clean_expires(iter);
				अन्यथा
					fib6_set_expires(iter, rt->expires);

				अगर (rt->fib6_pmtu)
					fib6_metric_set(iter, RTAX_MTU,
							rt->fib6_pmtu);
				वापस -EEXIST;
			पूर्ण
			/* If we have the same destination and the same metric,
			 * but not the same gateway, then the route we try to
			 * add is sibling to this route, increment our counter
			 * of siblings, and later we will add our route to the
			 * list.
			 * Only अटल routes (which करोn't have flag
			 * RTF_EXPIRES) are used क्रम ECMPv6.
			 *
			 * To aव्योम दीर्घ list, we only had siblings अगर the
			 * route have a gateway.
			 */
			अगर (rt_can_ecmp &&
			    rt6_qualअगरy_क्रम_ecmp(iter))
				rt->fib6_nsiblings++;
		पूर्ण

		अगर (iter->fib6_metric > rt->fib6_metric)
			अवरोध;

next_iter:
		ins = &iter->fib6_next;
	पूर्ण

	अगर (fallback_ins && !found) अणु
		/* No matching route with same ecmp-able-ness found, replace
		 * first matching route
		 */
		ins = fallback_ins;
		iter = rcu_dereference_रक्षित(*ins,
				    lockdep_is_held(&rt->fib6_table->tb6_lock));
		found++;
	पूर्ण

	/* Reset round-robin state, अगर necessary */
	अगर (ins == &fn->leaf)
		fn->rr_ptr = शून्य;

	/* Link this route to others same route. */
	अगर (rt->fib6_nsiblings) अणु
		अचिन्हित पूर्णांक fib6_nsiblings;
		काष्ठा fib6_info *sibling, *temp_sibling;

		/* Find the first route that have the same metric */
		sibling = leaf;
		notअगरy_sibling_rt = true;
		जबतक (sibling) अणु
			अगर (sibling->fib6_metric == rt->fib6_metric &&
			    rt6_qualअगरy_क्रम_ecmp(sibling)) अणु
				list_add_tail(&rt->fib6_siblings,
					      &sibling->fib6_siblings);
				अवरोध;
			पूर्ण
			sibling = rcu_dereference_रक्षित(sibling->fib6_next,
				    lockdep_is_held(&rt->fib6_table->tb6_lock));
			notअगरy_sibling_rt = false;
		पूर्ण
		/* For each sibling in the list, increment the counter of
		 * siblings. BUG() अगर counters करोes not match, list of siblings
		 * is broken!
		 */
		fib6_nsiblings = 0;
		list_क्रम_each_entry_safe(sibling, temp_sibling,
					 &rt->fib6_siblings, fib6_siblings) अणु
			sibling->fib6_nsiblings++;
			BUG_ON(sibling->fib6_nsiblings != rt->fib6_nsiblings);
			fib6_nsiblings++;
		पूर्ण
		BUG_ON(fib6_nsiblings != rt->fib6_nsiblings);
		rt6_multipath_rebalance(temp_sibling);
	पूर्ण

	/*
	 *	insert node
	 */
	अगर (!replace) अणु
		अगर (!add)
			pr_warn("NLM_F_CREATE should be set when creating new route\n");

add:
		nlflags |= NLM_F_CREATE;

		/* The route should only be notअगरied अगर it is the first
		 * route in the node or अगर it is added as a sibling
		 * route to the first route in the node.
		 */
		अगर (!info->skip_notअगरy_kernel &&
		    (notअगरy_sibling_rt || ins == &fn->leaf)) अणु
			क्रमागत fib_event_type fib_event;

			अगर (notअगरy_sibling_rt)
				fib_event = FIB_EVENT_ENTRY_APPEND;
			अन्यथा
				fib_event = FIB_EVENT_ENTRY_REPLACE;
			err = call_fib6_entry_notअगरiers(info->nl_net,
							fib_event, rt,
							extack);
			अगर (err) अणु
				काष्ठा fib6_info *sibling, *next_sibling;

				/* If the route has siblings, then it first
				 * needs to be unlinked from them.
				 */
				अगर (!rt->fib6_nsiblings)
					वापस err;

				list_क्रम_each_entry_safe(sibling, next_sibling,
							 &rt->fib6_siblings,
							 fib6_siblings)
					sibling->fib6_nsiblings--;
				rt->fib6_nsiblings = 0;
				list_del_init(&rt->fib6_siblings);
				rt6_multipath_rebalance(next_sibling);
				वापस err;
			पूर्ण
		पूर्ण

		rcu_assign_poपूर्णांकer(rt->fib6_next, iter);
		fib6_info_hold(rt);
		rcu_assign_poपूर्णांकer(rt->fib6_node, fn);
		rcu_assign_poपूर्णांकer(*ins, rt);
		अगर (!info->skip_notअगरy)
			inet6_rt_notअगरy(RTM_NEWROUTE, rt, info, nlflags);
		info->nl_net->ipv6.rt6_stats->fib_rt_entries++;

		अगर (!(fn->fn_flags & RTN_RTINFO)) अणु
			info->nl_net->ipv6.rt6_stats->fib_route_nodes++;
			fn->fn_flags |= RTN_RTINFO;
		पूर्ण

	पूर्ण अन्यथा अणु
		पूर्णांक nsiblings;

		अगर (!found) अणु
			अगर (add)
				जाओ add;
			pr_warn("NLM_F_REPLACE set, but no existing node found!\n");
			वापस -ENOENT;
		पूर्ण

		अगर (!info->skip_notअगरy_kernel && ins == &fn->leaf) अणु
			err = call_fib6_entry_notअगरiers(info->nl_net,
							FIB_EVENT_ENTRY_REPLACE,
							rt, extack);
			अगर (err)
				वापस err;
		पूर्ण

		fib6_info_hold(rt);
		rcu_assign_poपूर्णांकer(rt->fib6_node, fn);
		rt->fib6_next = iter->fib6_next;
		rcu_assign_poपूर्णांकer(*ins, rt);
		अगर (!info->skip_notअगरy)
			inet6_rt_notअगरy(RTM_NEWROUTE, rt, info, NLM_F_REPLACE);
		अगर (!(fn->fn_flags & RTN_RTINFO)) अणु
			info->nl_net->ipv6.rt6_stats->fib_route_nodes++;
			fn->fn_flags |= RTN_RTINFO;
		पूर्ण
		nsiblings = iter->fib6_nsiblings;
		iter->fib6_node = शून्य;
		fib6_purge_rt(iter, fn, info->nl_net);
		अगर (rcu_access_poपूर्णांकer(fn->rr_ptr) == iter)
			fn->rr_ptr = शून्य;
		fib6_info_release(iter);

		अगर (nsiblings) अणु
			/* Replacing an ECMP route, हटाओ all siblings */
			ins = &rt->fib6_next;
			iter = rcu_dereference_रक्षित(*ins,
				    lockdep_is_held(&rt->fib6_table->tb6_lock));
			जबतक (iter) अणु
				अगर (iter->fib6_metric > rt->fib6_metric)
					अवरोध;
				अगर (rt6_qualअगरy_क्रम_ecmp(iter)) अणु
					*ins = iter->fib6_next;
					iter->fib6_node = शून्य;
					fib6_purge_rt(iter, fn, info->nl_net);
					अगर (rcu_access_poपूर्णांकer(fn->rr_ptr) == iter)
						fn->rr_ptr = शून्य;
					fib6_info_release(iter);
					nsiblings--;
					info->nl_net->ipv6.rt6_stats->fib_rt_entries--;
				पूर्ण अन्यथा अणु
					ins = &iter->fib6_next;
				पूर्ण
				iter = rcu_dereference_रक्षित(*ins,
					lockdep_is_held(&rt->fib6_table->tb6_lock));
			पूर्ण
			WARN_ON(nsiblings != 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fib6_start_gc(काष्ठा net *net, काष्ठा fib6_info *rt)
अणु
	अगर (!समयr_pending(&net->ipv6.ip6_fib_समयr) &&
	    (rt->fib6_flags & RTF_EXPIRES))
		mod_समयr(&net->ipv6.ip6_fib_समयr,
			  jअगरfies + net->ipv6.sysctl.ip6_rt_gc_पूर्णांकerval);
पूर्ण

व्योम fib6_क्रमce_start_gc(काष्ठा net *net)
अणु
	अगर (!समयr_pending(&net->ipv6.ip6_fib_समयr))
		mod_समयr(&net->ipv6.ip6_fib_समयr,
			  jअगरfies + net->ipv6.sysctl.ip6_rt_gc_पूर्णांकerval);
पूर्ण

अटल व्योम __fib6_update_sernum_upto_root(काष्ठा fib6_info *rt,
					   पूर्णांक sernum)
अणु
	काष्ठा fib6_node *fn = rcu_dereference_रक्षित(rt->fib6_node,
				lockdep_is_held(&rt->fib6_table->tb6_lock));

	/* paired with smp_rmb() in rt6_get_cookie_safe() */
	smp_wmb();
	जबतक (fn) अणु
		fn->fn_sernum = sernum;
		fn = rcu_dereference_रक्षित(fn->parent,
				lockdep_is_held(&rt->fib6_table->tb6_lock));
	पूर्ण
पूर्ण

व्योम fib6_update_sernum_upto_root(काष्ठा net *net, काष्ठा fib6_info *rt)
अणु
	__fib6_update_sernum_upto_root(rt, fib6_new_sernum(net));
पूर्ण

/* allow ipv4 to update sernum via ipv6_stub */
व्योम fib6_update_sernum_stub(काष्ठा net *net, काष्ठा fib6_info *f6i)
अणु
	spin_lock_bh(&f6i->fib6_table->tb6_lock);
	fib6_update_sernum_upto_root(net, f6i);
	spin_unlock_bh(&f6i->fib6_table->tb6_lock);
पूर्ण

/*
 *	Add routing inक्रमmation to the routing tree.
 *	<destination addr>/<source addr>
 *	with source addr info in sub-trees
 *	Need to own table->tb6_lock
 */

पूर्णांक fib6_add(काष्ठा fib6_node *root, काष्ठा fib6_info *rt,
	     काष्ठा nl_info *info, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा fib6_table *table = rt->fib6_table;
	काष्ठा fib6_node *fn, *pn = शून्य;
	पूर्णांक err = -ENOMEM;
	पूर्णांक allow_create = 1;
	पूर्णांक replace_required = 0;
	पूर्णांक sernum = fib6_new_sernum(info->nl_net);

	अगर (info->nlh) अणु
		अगर (!(info->nlh->nlmsg_flags & NLM_F_CREATE))
			allow_create = 0;
		अगर (info->nlh->nlmsg_flags & NLM_F_REPLACE)
			replace_required = 1;
	पूर्ण
	अगर (!allow_create && !replace_required)
		pr_warn("RTM_NEWROUTE with no NLM_F_CREATE or NLM_F_REPLACE\n");

	fn = fib6_add_1(info->nl_net, table, root,
			&rt->fib6_dst.addr, rt->fib6_dst.plen,
			दुरत्व(काष्ठा fib6_info, fib6_dst), allow_create,
			replace_required, extack);
	अगर (IS_ERR(fn)) अणु
		err = PTR_ERR(fn);
		fn = शून्य;
		जाओ out;
	पूर्ण

	pn = fn;

#अगर_घोषित CONFIG_IPV6_SUBTREES
	अगर (rt->fib6_src.plen) अणु
		काष्ठा fib6_node *sn;

		अगर (!rcu_access_poपूर्णांकer(fn->subtree)) अणु
			काष्ठा fib6_node *sfn;

			/*
			 * Create subtree.
			 *
			 *		fn[मुख्य tree]
			 *		|
			 *		sfn[subtree root]
			 *		   \
			 *		    sn[new leaf node]
			 */

			/* Create subtree root node */
			sfn = node_alloc(info->nl_net);
			अगर (!sfn)
				जाओ failure;

			fib6_info_hold(info->nl_net->ipv6.fib6_null_entry);
			rcu_assign_poपूर्णांकer(sfn->leaf,
					   info->nl_net->ipv6.fib6_null_entry);
			sfn->fn_flags = RTN_ROOT;

			/* Now add the first leaf node to new subtree */

			sn = fib6_add_1(info->nl_net, table, sfn,
					&rt->fib6_src.addr, rt->fib6_src.plen,
					दुरत्व(काष्ठा fib6_info, fib6_src),
					allow_create, replace_required, extack);

			अगर (IS_ERR(sn)) अणु
				/* If it is failed, discard just allocated
				   root, and then (in failure) stale node
				   in मुख्य tree.
				 */
				node_मुक्त_immediate(info->nl_net, sfn);
				err = PTR_ERR(sn);
				जाओ failure;
			पूर्ण

			/* Now link new subtree to मुख्य tree */
			rcu_assign_poपूर्णांकer(sfn->parent, fn);
			rcu_assign_poपूर्णांकer(fn->subtree, sfn);
		पूर्ण अन्यथा अणु
			sn = fib6_add_1(info->nl_net, table, FIB6_SUBTREE(fn),
					&rt->fib6_src.addr, rt->fib6_src.plen,
					दुरत्व(काष्ठा fib6_info, fib6_src),
					allow_create, replace_required, extack);

			अगर (IS_ERR(sn)) अणु
				err = PTR_ERR(sn);
				जाओ failure;
			पूर्ण
		पूर्ण

		अगर (!rcu_access_poपूर्णांकer(fn->leaf)) अणु
			अगर (fn->fn_flags & RTN_TL_ROOT) अणु
				/* put back null_entry क्रम root node */
				rcu_assign_poपूर्णांकer(fn->leaf,
					    info->nl_net->ipv6.fib6_null_entry);
			पूर्ण अन्यथा अणु
				fib6_info_hold(rt);
				rcu_assign_poपूर्णांकer(fn->leaf, rt);
			पूर्ण
		पूर्ण
		fn = sn;
	पूर्ण
#पूर्ण_अगर

	err = fib6_add_rt2node(fn, rt, info, extack);
	अगर (!err) अणु
		अगर (rt->nh)
			list_add(&rt->nh_list, &rt->nh->f6i_list);
		__fib6_update_sernum_upto_root(rt, sernum);
		fib6_start_gc(info->nl_net, rt);
	पूर्ण

out:
	अगर (err) अणु
#अगर_घोषित CONFIG_IPV6_SUBTREES
		/*
		 * If fib6_add_1 has cleared the old leaf poपूर्णांकer in the
		 * super-tree leaf node we have to find a new one क्रम it.
		 */
		अगर (pn != fn) अणु
			काष्ठा fib6_info *pn_leaf =
				rcu_dereference_रक्षित(pn->leaf,
				    lockdep_is_held(&table->tb6_lock));
			अगर (pn_leaf == rt) अणु
				pn_leaf = शून्य;
				RCU_INIT_POINTER(pn->leaf, शून्य);
				fib6_info_release(rt);
			पूर्ण
			अगर (!pn_leaf && !(pn->fn_flags & RTN_RTINFO)) अणु
				pn_leaf = fib6_find_prefix(info->nl_net, table,
							   pn);
#अगर RT6_DEBUG >= 2
				अगर (!pn_leaf) अणु
					WARN_ON(!pn_leaf);
					pn_leaf =
					    info->nl_net->ipv6.fib6_null_entry;
				पूर्ण
#पूर्ण_अगर
				fib6_info_hold(pn_leaf);
				rcu_assign_poपूर्णांकer(pn->leaf, pn_leaf);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		जाओ failure;
	पूर्ण अन्यथा अगर (fib6_requires_src(rt)) अणु
		fib6_routes_require_src_inc(info->nl_net);
	पूर्ण
	वापस err;

failure:
	/* fn->leaf could be शून्य and fib6_repair_tree() needs to be called अगर:
	 * 1. fn is an पूर्णांकermediate node and we failed to add the new
	 * route to it in both subtree creation failure and fib6_add_rt2node()
	 * failure हाल.
	 * 2. fn is the root node in the table and we fail to add the first
	 * शेष route to it.
	 */
	अगर (fn &&
	    (!(fn->fn_flags & (RTN_RTINFO|RTN_ROOT)) ||
	     (fn->fn_flags & RTN_TL_ROOT &&
	      !rcu_access_poपूर्णांकer(fn->leaf))))
		fib6_repair_tree(info->nl_net, table, fn);
	वापस err;
पूर्ण

/*
 *	Routing tree lookup
 *
 */

काष्ठा lookup_args अणु
	पूर्णांक			offset;		/* key offset on fib6_info */
	स्थिर काष्ठा in6_addr	*addr;		/* search key			*/
पूर्ण;

अटल काष्ठा fib6_node *fib6_node_lookup_1(काष्ठा fib6_node *root,
					    काष्ठा lookup_args *args)
अणु
	काष्ठा fib6_node *fn;
	__be32 dir;

	अगर (unlikely(args->offset == 0))
		वापस शून्य;

	/*
	 *	Descend on a tree
	 */

	fn = root;

	क्रम (;;) अणु
		काष्ठा fib6_node *next;

		dir = addr_bit_set(args->addr, fn->fn_bit);

		next = dir ? rcu_dereference(fn->right) :
			     rcu_dereference(fn->left);

		अगर (next) अणु
			fn = next;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	जबतक (fn) अणु
		काष्ठा fib6_node *subtree = FIB6_SUBTREE(fn);

		अगर (subtree || fn->fn_flags & RTN_RTINFO) अणु
			काष्ठा fib6_info *leaf = rcu_dereference(fn->leaf);
			काष्ठा rt6key *key;

			अगर (!leaf)
				जाओ backtrack;

			key = (काष्ठा rt6key *) ((u8 *)leaf + args->offset);

			अगर (ipv6_prefix_equal(&key->addr, args->addr, key->plen)) अणु
#अगर_घोषित CONFIG_IPV6_SUBTREES
				अगर (subtree) अणु
					काष्ठा fib6_node *sfn;
					sfn = fib6_node_lookup_1(subtree,
								 args + 1);
					अगर (!sfn)
						जाओ backtrack;
					fn = sfn;
				पूर्ण
#पूर्ण_अगर
				अगर (fn->fn_flags & RTN_RTINFO)
					वापस fn;
			पूर्ण
		पूर्ण
backtrack:
		अगर (fn->fn_flags & RTN_ROOT)
			अवरोध;

		fn = rcu_dereference(fn->parent);
	पूर्ण

	वापस शून्य;
पूर्ण

/* called with rcu_पढ़ो_lock() held
 */
काष्ठा fib6_node *fib6_node_lookup(काष्ठा fib6_node *root,
				   स्थिर काष्ठा in6_addr *daddr,
				   स्थिर काष्ठा in6_addr *saddr)
अणु
	काष्ठा fib6_node *fn;
	काष्ठा lookup_args args[] = अणु
		अणु
			.offset = दुरत्व(काष्ठा fib6_info, fib6_dst),
			.addr = daddr,
		पूर्ण,
#अगर_घोषित CONFIG_IPV6_SUBTREES
		अणु
			.offset = दुरत्व(काष्ठा fib6_info, fib6_src),
			.addr = saddr,
		पूर्ण,
#पूर्ण_अगर
		अणु
			.offset = 0,	/* sentinel */
		पूर्ण
	पूर्ण;

	fn = fib6_node_lookup_1(root, daddr ? args : args + 1);
	अगर (!fn || fn->fn_flags & RTN_TL_ROOT)
		fn = root;

	वापस fn;
पूर्ण

/*
 *	Get node with specअगरied destination prefix (and source prefix,
 *	अगर subtrees are used)
 *	exact_match == true means we try to find fn with exact match of
 *	the passed in prefix addr
 *	exact_match == false means we try to find fn with दीर्घest prefix
 *	match of the passed in prefix addr. This is useful क्रम finding fn
 *	क्रम cached route as it will be stored in the exception table under
 *	the node with दीर्घest prefix length.
 */


अटल काष्ठा fib6_node *fib6_locate_1(काष्ठा fib6_node *root,
				       स्थिर काष्ठा in6_addr *addr,
				       पूर्णांक plen, पूर्णांक offset,
				       bool exact_match)
अणु
	काष्ठा fib6_node *fn, *prev = शून्य;

	क्रम (fn = root; fn ; ) अणु
		काष्ठा fib6_info *leaf = rcu_dereference(fn->leaf);
		काष्ठा rt6key *key;

		/* This node is being deleted */
		अगर (!leaf) अणु
			अगर (plen <= fn->fn_bit)
				जाओ out;
			अन्यथा
				जाओ next;
		पूर्ण

		key = (काष्ठा rt6key *)((u8 *)leaf + offset);

		/*
		 *	Prefix match
		 */
		अगर (plen < fn->fn_bit ||
		    !ipv6_prefix_equal(&key->addr, addr, fn->fn_bit))
			जाओ out;

		अगर (plen == fn->fn_bit)
			वापस fn;

		अगर (fn->fn_flags & RTN_RTINFO)
			prev = fn;

next:
		/*
		 *	We have more bits to go
		 */
		अगर (addr_bit_set(addr, fn->fn_bit))
			fn = rcu_dereference(fn->right);
		अन्यथा
			fn = rcu_dereference(fn->left);
	पूर्ण
out:
	अगर (exact_match)
		वापस शून्य;
	अन्यथा
		वापस prev;
पूर्ण

काष्ठा fib6_node *fib6_locate(काष्ठा fib6_node *root,
			      स्थिर काष्ठा in6_addr *daddr, पूर्णांक dst_len,
			      स्थिर काष्ठा in6_addr *saddr, पूर्णांक src_len,
			      bool exact_match)
अणु
	काष्ठा fib6_node *fn;

	fn = fib6_locate_1(root, daddr, dst_len,
			   दुरत्व(काष्ठा fib6_info, fib6_dst),
			   exact_match);

#अगर_घोषित CONFIG_IPV6_SUBTREES
	अगर (src_len) अणु
		WARN_ON(saddr == शून्य);
		अगर (fn) अणु
			काष्ठा fib6_node *subtree = FIB6_SUBTREE(fn);

			अगर (subtree) अणु
				fn = fib6_locate_1(subtree, saddr, src_len,
					   दुरत्व(काष्ठा fib6_info, fib6_src),
					   exact_match);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (fn && fn->fn_flags & RTN_RTINFO)
		वापस fn;

	वापस शून्य;
पूर्ण


/*
 *	Deletion
 *
 */

अटल काष्ठा fib6_info *fib6_find_prefix(काष्ठा net *net,
					 काष्ठा fib6_table *table,
					 काष्ठा fib6_node *fn)
अणु
	काष्ठा fib6_node *child_left, *child_right;

	अगर (fn->fn_flags & RTN_ROOT)
		वापस net->ipv6.fib6_null_entry;

	जबतक (fn) अणु
		child_left = rcu_dereference_रक्षित(fn->left,
				    lockdep_is_held(&table->tb6_lock));
		child_right = rcu_dereference_रक्षित(fn->right,
				    lockdep_is_held(&table->tb6_lock));
		अगर (child_left)
			वापस rcu_dereference_रक्षित(child_left->leaf,
					lockdep_is_held(&table->tb6_lock));
		अगर (child_right)
			वापस rcu_dereference_रक्षित(child_right->leaf,
					lockdep_is_held(&table->tb6_lock));

		fn = FIB6_SUBTREE(fn);
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 *	Called to trim the tree of पूर्णांकermediate nodes when possible. "fn"
 *	is the node we want to try and हटाओ.
 *	Need to own table->tb6_lock
 */

अटल काष्ठा fib6_node *fib6_repair_tree(काष्ठा net *net,
					  काष्ठा fib6_table *table,
					  काष्ठा fib6_node *fn)
अणु
	पूर्णांक children;
	पूर्णांक nstate;
	काष्ठा fib6_node *child;
	काष्ठा fib6_walker *w;
	पूर्णांक iter = 0;

	/* Set fn->leaf to null_entry क्रम root node. */
	अगर (fn->fn_flags & RTN_TL_ROOT) अणु
		rcu_assign_poपूर्णांकer(fn->leaf, net->ipv6.fib6_null_entry);
		वापस fn;
	पूर्ण

	क्रम (;;) अणु
		काष्ठा fib6_node *fn_r = rcu_dereference_रक्षित(fn->right,
					    lockdep_is_held(&table->tb6_lock));
		काष्ठा fib6_node *fn_l = rcu_dereference_रक्षित(fn->left,
					    lockdep_is_held(&table->tb6_lock));
		काष्ठा fib6_node *pn = rcu_dereference_रक्षित(fn->parent,
					    lockdep_is_held(&table->tb6_lock));
		काष्ठा fib6_node *pn_r = rcu_dereference_रक्षित(pn->right,
					    lockdep_is_held(&table->tb6_lock));
		काष्ठा fib6_node *pn_l = rcu_dereference_रक्षित(pn->left,
					    lockdep_is_held(&table->tb6_lock));
		काष्ठा fib6_info *fn_leaf = rcu_dereference_रक्षित(fn->leaf,
					    lockdep_is_held(&table->tb6_lock));
		काष्ठा fib6_info *pn_leaf = rcu_dereference_रक्षित(pn->leaf,
					    lockdep_is_held(&table->tb6_lock));
		काष्ठा fib6_info *new_fn_leaf;

		RT6_TRACE("fixing tree: plen=%d iter=%d\n", fn->fn_bit, iter);
		iter++;

		WARN_ON(fn->fn_flags & RTN_RTINFO);
		WARN_ON(fn->fn_flags & RTN_TL_ROOT);
		WARN_ON(fn_leaf);

		children = 0;
		child = शून्य;
		अगर (fn_r) अणु
			child = fn_r;
			children |= 1;
		पूर्ण
		अगर (fn_l) अणु
			child = fn_l;
			children |= 2;
		पूर्ण

		अगर (children == 3 || FIB6_SUBTREE(fn)
#अगर_घोषित CONFIG_IPV6_SUBTREES
		    /* Subtree root (i.e. fn) may have one child */
		    || (children && fn->fn_flags & RTN_ROOT)
#पूर्ण_अगर
		    ) अणु
			new_fn_leaf = fib6_find_prefix(net, table, fn);
#अगर RT6_DEBUG >= 2
			अगर (!new_fn_leaf) अणु
				WARN_ON(!new_fn_leaf);
				new_fn_leaf = net->ipv6.fib6_null_entry;
			पूर्ण
#पूर्ण_अगर
			fib6_info_hold(new_fn_leaf);
			rcu_assign_poपूर्णांकer(fn->leaf, new_fn_leaf);
			वापस pn;
		पूर्ण

#अगर_घोषित CONFIG_IPV6_SUBTREES
		अगर (FIB6_SUBTREE(pn) == fn) अणु
			WARN_ON(!(fn->fn_flags & RTN_ROOT));
			RCU_INIT_POINTER(pn->subtree, शून्य);
			nstate = FWS_L;
		पूर्ण अन्यथा अणु
			WARN_ON(fn->fn_flags & RTN_ROOT);
#पूर्ण_अगर
			अगर (pn_r == fn)
				rcu_assign_poपूर्णांकer(pn->right, child);
			अन्यथा अगर (pn_l == fn)
				rcu_assign_poपूर्णांकer(pn->left, child);
#अगर RT6_DEBUG >= 2
			अन्यथा
				WARN_ON(1);
#पूर्ण_अगर
			अगर (child)
				rcu_assign_poपूर्णांकer(child->parent, pn);
			nstate = FWS_R;
#अगर_घोषित CONFIG_IPV6_SUBTREES
		पूर्ण
#पूर्ण_अगर

		पढ़ो_lock(&net->ipv6.fib6_walker_lock);
		FOR_WALKERS(net, w) अणु
			अगर (!child) अणु
				अगर (w->node == fn) अणु
					RT6_TRACE("W %p adjusted by delnode 1, s=%d/%d\n", w, w->state, nstate);
					w->node = pn;
					w->state = nstate;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (w->node == fn) अणु
					w->node = child;
					अगर (children&2) अणु
						RT6_TRACE("W %p adjusted by delnode 2, s=%d\n", w, w->state);
						w->state = w->state >= FWS_R ? FWS_U : FWS_INIT;
					पूर्ण अन्यथा अणु
						RT6_TRACE("W %p adjusted by delnode 2, s=%d\n", w, w->state);
						w->state = w->state >= FWS_C ? FWS_U : FWS_INIT;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		पढ़ो_unlock(&net->ipv6.fib6_walker_lock);

		node_मुक्त(net, fn);
		अगर (pn->fn_flags & RTN_RTINFO || FIB6_SUBTREE(pn))
			वापस pn;

		RCU_INIT_POINTER(pn->leaf, शून्य);
		fib6_info_release(pn_leaf);
		fn = pn;
	पूर्ण
पूर्ण

अटल व्योम fib6_del_route(काष्ठा fib6_table *table, काष्ठा fib6_node *fn,
			   काष्ठा fib6_info __rcu **rtp, काष्ठा nl_info *info)
अणु
	काष्ठा fib6_info *leaf, *replace_rt = शून्य;
	काष्ठा fib6_walker *w;
	काष्ठा fib6_info *rt = rcu_dereference_रक्षित(*rtp,
				    lockdep_is_held(&table->tb6_lock));
	काष्ठा net *net = info->nl_net;
	bool notअगरy_del = false;

	RT6_TRACE("fib6_del_route\n");

	/* If the deleted route is the first in the node and it is not part of
	 * a multipath route, then we need to replace it with the next route
	 * in the node, अगर exists.
	 */
	leaf = rcu_dereference_रक्षित(fn->leaf,
					 lockdep_is_held(&table->tb6_lock));
	अगर (leaf == rt && !rt->fib6_nsiblings) अणु
		अगर (rcu_access_poपूर्णांकer(rt->fib6_next))
			replace_rt = rcu_dereference_रक्षित(rt->fib6_next,
					    lockdep_is_held(&table->tb6_lock));
		अन्यथा
			notअगरy_del = true;
	पूर्ण

	/* Unlink it */
	*rtp = rt->fib6_next;
	rt->fib6_node = शून्य;
	net->ipv6.rt6_stats->fib_rt_entries--;
	net->ipv6.rt6_stats->fib_discarded_routes++;

	/* Reset round-robin state, अगर necessary */
	अगर (rcu_access_poपूर्णांकer(fn->rr_ptr) == rt)
		fn->rr_ptr = शून्य;

	/* Remove this entry from other siblings */
	अगर (rt->fib6_nsiblings) अणु
		काष्ठा fib6_info *sibling, *next_sibling;

		/* The route is deleted from a multipath route. If this
		 * multipath route is the first route in the node, then we need
		 * to emit a delete notअगरication. Otherwise, we need to skip
		 * the notअगरication.
		 */
		अगर (rt->fib6_metric == leaf->fib6_metric &&
		    rt6_qualअगरy_क्रम_ecmp(leaf))
			notअगरy_del = true;
		list_क्रम_each_entry_safe(sibling, next_sibling,
					 &rt->fib6_siblings, fib6_siblings)
			sibling->fib6_nsiblings--;
		rt->fib6_nsiblings = 0;
		list_del_init(&rt->fib6_siblings);
		rt6_multipath_rebalance(next_sibling);
	पूर्ण

	/* Adjust walkers */
	पढ़ो_lock(&net->ipv6.fib6_walker_lock);
	FOR_WALKERS(net, w) अणु
		अगर (w->state == FWS_C && w->leaf == rt) अणु
			RT6_TRACE("walker %p adjusted by delroute\n", w);
			w->leaf = rcu_dereference_रक्षित(rt->fib6_next,
					    lockdep_is_held(&table->tb6_lock));
			अगर (!w->leaf)
				w->state = FWS_U;
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&net->ipv6.fib6_walker_lock);

	/* If it was last route, call fib6_repair_tree() to:
	 * 1. For root node, put back null_entry as how the table was created.
	 * 2. For other nodes, expunge its radix tree node.
	 */
	अगर (!rcu_access_poपूर्णांकer(fn->leaf)) अणु
		अगर (!(fn->fn_flags & RTN_TL_ROOT)) अणु
			fn->fn_flags &= ~RTN_RTINFO;
			net->ipv6.rt6_stats->fib_route_nodes--;
		पूर्ण
		fn = fib6_repair_tree(net, table, fn);
	पूर्ण

	fib6_purge_rt(rt, fn, net);

	अगर (!info->skip_notअगरy_kernel) अणु
		अगर (notअगरy_del)
			call_fib6_entry_notअगरiers(net, FIB_EVENT_ENTRY_DEL,
						  rt, शून्य);
		अन्यथा अगर (replace_rt)
			call_fib6_entry_notअगरiers_replace(net, replace_rt);
	पूर्ण
	अगर (!info->skip_notअगरy)
		inet6_rt_notअगरy(RTM_DELROUTE, rt, info, 0);

	fib6_info_release(rt);
पूर्ण

/* Need to own table->tb6_lock */
पूर्णांक fib6_del(काष्ठा fib6_info *rt, काष्ठा nl_info *info)
अणु
	काष्ठा net *net = info->nl_net;
	काष्ठा fib6_info __rcu **rtp;
	काष्ठा fib6_info __rcu **rtp_next;
	काष्ठा fib6_table *table;
	काष्ठा fib6_node *fn;

	अगर (rt == net->ipv6.fib6_null_entry)
		वापस -ENOENT;

	table = rt->fib6_table;
	fn = rcu_dereference_रक्षित(rt->fib6_node,
				       lockdep_is_held(&table->tb6_lock));
	अगर (!fn)
		वापस -ENOENT;

	WARN_ON(!(fn->fn_flags & RTN_RTINFO));

	/*
	 *	Walk the leaf entries looking क्रम ourself
	 */

	क्रम (rtp = &fn->leaf; *rtp; rtp = rtp_next) अणु
		काष्ठा fib6_info *cur = rcu_dereference_रक्षित(*rtp,
					lockdep_is_held(&table->tb6_lock));
		अगर (rt == cur) अणु
			अगर (fib6_requires_src(cur))
				fib6_routes_require_src_dec(info->nl_net);
			fib6_del_route(table, fn, rtp, info);
			वापस 0;
		पूर्ण
		rtp_next = &cur->fib6_next;
	पूर्ण
	वापस -ENOENT;
पूर्ण

/*
 *	Tree traversal function.
 *
 *	Certainly, it is not पूर्णांकerrupt safe.
 *	However, it is पूर्णांकernally reenterable wrt itself and fib6_add/fib6_del.
 *	It means, that we can modअगरy tree during walking
 *	and use this function क्रम garbage collection, clone pruning,
 *	cleaning tree when a device goes करोwn etc. etc.
 *
 *	It guarantees that every node will be traversed,
 *	and that it will be traversed only once.
 *
 *	Callback function w->func may वापस:
 *	0 -> जारी walking.
 *	positive value -> walking is suspended (used by tree dumps,
 *	and probably by gc, अगर it will be split to several slices)
 *	negative value -> terminate walking.
 *
 *	The function itself वापसs:
 *	0   -> walk is complete.
 *	>0  -> walk is incomplete (i.e. suspended)
 *	<0  -> walk is terminated by an error.
 *
 *	This function is called with tb6_lock held.
 */

अटल पूर्णांक fib6_walk_जारी(काष्ठा fib6_walker *w)
अणु
	काष्ठा fib6_node *fn, *pn, *left, *right;

	/* w->root should always be table->tb6_root */
	WARN_ON_ONCE(!(w->root->fn_flags & RTN_TL_ROOT));

	क्रम (;;) अणु
		fn = w->node;
		अगर (!fn)
			वापस 0;

		चयन (w->state) अणु
#अगर_घोषित CONFIG_IPV6_SUBTREES
		हाल FWS_S:
			अगर (FIB6_SUBTREE(fn)) अणु
				w->node = FIB6_SUBTREE(fn);
				जारी;
			पूर्ण
			w->state = FWS_L;
			fallthrough;
#पूर्ण_अगर
		हाल FWS_L:
			left = rcu_dereference_रक्षित(fn->left, 1);
			अगर (left) अणु
				w->node = left;
				w->state = FWS_INIT;
				जारी;
			पूर्ण
			w->state = FWS_R;
			fallthrough;
		हाल FWS_R:
			right = rcu_dereference_रक्षित(fn->right, 1);
			अगर (right) अणु
				w->node = right;
				w->state = FWS_INIT;
				जारी;
			पूर्ण
			w->state = FWS_C;
			w->leaf = rcu_dereference_रक्षित(fn->leaf, 1);
			fallthrough;
		हाल FWS_C:
			अगर (w->leaf && fn->fn_flags & RTN_RTINFO) अणु
				पूर्णांक err;

				अगर (w->skip) अणु
					w->skip--;
					जाओ skip;
				पूर्ण

				err = w->func(w);
				अगर (err)
					वापस err;

				w->count++;
				जारी;
			पूर्ण
skip:
			w->state = FWS_U;
			fallthrough;
		हाल FWS_U:
			अगर (fn == w->root)
				वापस 0;
			pn = rcu_dereference_रक्षित(fn->parent, 1);
			left = rcu_dereference_रक्षित(pn->left, 1);
			right = rcu_dereference_रक्षित(pn->right, 1);
			w->node = pn;
#अगर_घोषित CONFIG_IPV6_SUBTREES
			अगर (FIB6_SUBTREE(pn) == fn) अणु
				WARN_ON(!(fn->fn_flags & RTN_ROOT));
				w->state = FWS_L;
				जारी;
			पूर्ण
#पूर्ण_अगर
			अगर (left == fn) अणु
				w->state = FWS_R;
				जारी;
			पूर्ण
			अगर (right == fn) अणु
				w->state = FWS_C;
				w->leaf = rcu_dereference_रक्षित(w->node->leaf, 1);
				जारी;
			पूर्ण
#अगर RT6_DEBUG >= 2
			WARN_ON(1);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक fib6_walk(काष्ठा net *net, काष्ठा fib6_walker *w)
अणु
	पूर्णांक res;

	w->state = FWS_INIT;
	w->node = w->root;

	fib6_walker_link(net, w);
	res = fib6_walk_जारी(w);
	अगर (res <= 0)
		fib6_walker_unlink(net, w);
	वापस res;
पूर्ण

अटल पूर्णांक fib6_clean_node(काष्ठा fib6_walker *w)
अणु
	पूर्णांक res;
	काष्ठा fib6_info *rt;
	काष्ठा fib6_cleaner *c = container_of(w, काष्ठा fib6_cleaner, w);
	काष्ठा nl_info info = अणु
		.nl_net = c->net,
		.skip_notअगरy = c->skip_notअगरy,
	पूर्ण;

	अगर (c->sernum != FIB6_NO_SERNUM_CHANGE &&
	    w->node->fn_sernum != c->sernum)
		w->node->fn_sernum = c->sernum;

	अगर (!c->func) अणु
		WARN_ON_ONCE(c->sernum == FIB6_NO_SERNUM_CHANGE);
		w->leaf = शून्य;
		वापस 0;
	पूर्ण

	क्रम_each_fib6_walker_rt(w) अणु
		res = c->func(rt, c->arg);
		अगर (res == -1) अणु
			w->leaf = rt;
			res = fib6_del(rt, &info);
			अगर (res) अणु
#अगर RT6_DEBUG >= 2
				pr_debug("%s: del failed: rt=%p@%p err=%d\n",
					 __func__, rt,
					 rcu_access_poपूर्णांकer(rt->fib6_node),
					 res);
#पूर्ण_अगर
				जारी;
			पूर्ण
			वापस 0;
		पूर्ण अन्यथा अगर (res == -2) अणु
			अगर (WARN_ON(!rt->fib6_nsiblings))
				जारी;
			rt = list_last_entry(&rt->fib6_siblings,
					     काष्ठा fib6_info, fib6_siblings);
			जारी;
		पूर्ण
		WARN_ON(res != 0);
	पूर्ण
	w->leaf = rt;
	वापस 0;
पूर्ण

/*
 *	Convenient frontend to tree walker.
 *
 *	func is called on each route.
 *		It may वापस -2 -> skip multipath route.
 *			      -1 -> delete this route.
 *		              0  -> जारी walking
 */

अटल व्योम fib6_clean_tree(काष्ठा net *net, काष्ठा fib6_node *root,
			    पूर्णांक (*func)(काष्ठा fib6_info *, व्योम *arg),
			    पूर्णांक sernum, व्योम *arg, bool skip_notअगरy)
अणु
	काष्ठा fib6_cleaner c;

	c.w.root = root;
	c.w.func = fib6_clean_node;
	c.w.count = 0;
	c.w.skip = 0;
	c.w.skip_in_node = 0;
	c.func = func;
	c.sernum = sernum;
	c.arg = arg;
	c.net = net;
	c.skip_notअगरy = skip_notअगरy;

	fib6_walk(net, &c.w);
पूर्ण

अटल व्योम __fib6_clean_all(काष्ठा net *net,
			     पूर्णांक (*func)(काष्ठा fib6_info *, व्योम *),
			     पूर्णांक sernum, व्योम *arg, bool skip_notअगरy)
अणु
	काष्ठा fib6_table *table;
	काष्ठा hlist_head *head;
	अचिन्हित पूर्णांक h;

	rcu_पढ़ो_lock();
	क्रम (h = 0; h < FIB6_TABLE_HASHSZ; h++) अणु
		head = &net->ipv6.fib_table_hash[h];
		hlist_क्रम_each_entry_rcu(table, head, tb6_hlist) अणु
			spin_lock_bh(&table->tb6_lock);
			fib6_clean_tree(net, &table->tb6_root,
					func, sernum, arg, skip_notअगरy);
			spin_unlock_bh(&table->tb6_lock);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

व्योम fib6_clean_all(काष्ठा net *net, पूर्णांक (*func)(काष्ठा fib6_info *, व्योम *),
		    व्योम *arg)
अणु
	__fib6_clean_all(net, func, FIB6_NO_SERNUM_CHANGE, arg, false);
पूर्ण

व्योम fib6_clean_all_skip_notअगरy(काष्ठा net *net,
				पूर्णांक (*func)(काष्ठा fib6_info *, व्योम *),
				व्योम *arg)
अणु
	__fib6_clean_all(net, func, FIB6_NO_SERNUM_CHANGE, arg, true);
पूर्ण

अटल व्योम fib6_flush_trees(काष्ठा net *net)
अणु
	पूर्णांक new_sernum = fib6_new_sernum(net);

	__fib6_clean_all(net, शून्य, new_sernum, शून्य, false);
पूर्ण

/*
 *	Garbage collection
 */

अटल पूर्णांक fib6_age(काष्ठा fib6_info *rt, व्योम *arg)
अणु
	काष्ठा fib6_gc_args *gc_args = arg;
	अचिन्हित दीर्घ now = jअगरfies;

	/*
	 *	check addrconf expiration here.
	 *	Routes are expired even अगर they are in use.
	 */

	अगर (rt->fib6_flags & RTF_EXPIRES && rt->expires) अणु
		अगर (समय_after(now, rt->expires)) अणु
			RT6_TRACE("expiring %p\n", rt);
			वापस -1;
		पूर्ण
		gc_args->more++;
	पूर्ण

	/*	Also age clones in the exception table.
	 *	Note, that clones are aged out
	 *	only अगर they are not in use now.
	 */
	rt6_age_exceptions(rt, gc_args, now);

	वापस 0;
पूर्ण

व्योम fib6_run_gc(अचिन्हित दीर्घ expires, काष्ठा net *net, bool क्रमce)
अणु
	काष्ठा fib6_gc_args gc_args;
	अचिन्हित दीर्घ now;

	अगर (क्रमce) अणु
		spin_lock_bh(&net->ipv6.fib6_gc_lock);
	पूर्ण अन्यथा अगर (!spin_trylock_bh(&net->ipv6.fib6_gc_lock)) अणु
		mod_समयr(&net->ipv6.ip6_fib_समयr, jअगरfies + HZ);
		वापस;
	पूर्ण
	gc_args.समयout = expires ? (पूर्णांक)expires :
			  net->ipv6.sysctl.ip6_rt_gc_पूर्णांकerval;
	gc_args.more = 0;

	fib6_clean_all(net, fib6_age, &gc_args);
	now = jअगरfies;
	net->ipv6.ip6_rt_last_gc = now;

	अगर (gc_args.more)
		mod_समयr(&net->ipv6.ip6_fib_समयr,
			  round_jअगरfies(now
					+ net->ipv6.sysctl.ip6_rt_gc_पूर्णांकerval));
	अन्यथा
		del_समयr(&net->ipv6.ip6_fib_समयr);
	spin_unlock_bh(&net->ipv6.fib6_gc_lock);
पूर्ण

अटल व्योम fib6_gc_समयr_cb(काष्ठा समयr_list *t)
अणु
	काष्ठा net *arg = from_समयr(arg, t, ipv6.ip6_fib_समयr);

	fib6_run_gc(0, arg, true);
पूर्ण

अटल पूर्णांक __net_init fib6_net_init(काष्ठा net *net)
अणु
	माप_प्रकार size = माप(काष्ठा hlist_head) * FIB6_TABLE_HASHSZ;
	पूर्णांक err;

	err = fib6_notअगरier_init(net);
	अगर (err)
		वापस err;

	spin_lock_init(&net->ipv6.fib6_gc_lock);
	rwlock_init(&net->ipv6.fib6_walker_lock);
	INIT_LIST_HEAD(&net->ipv6.fib6_walkers);
	समयr_setup(&net->ipv6.ip6_fib_समयr, fib6_gc_समयr_cb, 0);

	net->ipv6.rt6_stats = kzalloc(माप(*net->ipv6.rt6_stats), GFP_KERNEL);
	अगर (!net->ipv6.rt6_stats)
		जाओ out_समयr;

	/* Aव्योम false sharing : Use at least a full cache line */
	size = max_t(माप_प्रकार, size, L1_CACHE_BYTES);

	net->ipv6.fib_table_hash = kzalloc(size, GFP_KERNEL);
	अगर (!net->ipv6.fib_table_hash)
		जाओ out_rt6_stats;

	net->ipv6.fib6_मुख्य_tbl = kzalloc(माप(*net->ipv6.fib6_मुख्य_tbl),
					  GFP_KERNEL);
	अगर (!net->ipv6.fib6_मुख्य_tbl)
		जाओ out_fib_table_hash;

	net->ipv6.fib6_मुख्य_tbl->tb6_id = RT6_TABLE_MAIN;
	rcu_assign_poपूर्णांकer(net->ipv6.fib6_मुख्य_tbl->tb6_root.leaf,
			   net->ipv6.fib6_null_entry);
	net->ipv6.fib6_मुख्य_tbl->tb6_root.fn_flags =
		RTN_ROOT | RTN_TL_ROOT | RTN_RTINFO;
	inet_peer_base_init(&net->ipv6.fib6_मुख्य_tbl->tb6_peers);

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
	net->ipv6.fib6_local_tbl = kzalloc(माप(*net->ipv6.fib6_local_tbl),
					   GFP_KERNEL);
	अगर (!net->ipv6.fib6_local_tbl)
		जाओ out_fib6_मुख्य_tbl;
	net->ipv6.fib6_local_tbl->tb6_id = RT6_TABLE_LOCAL;
	rcu_assign_poपूर्णांकer(net->ipv6.fib6_local_tbl->tb6_root.leaf,
			   net->ipv6.fib6_null_entry);
	net->ipv6.fib6_local_tbl->tb6_root.fn_flags =
		RTN_ROOT | RTN_TL_ROOT | RTN_RTINFO;
	inet_peer_base_init(&net->ipv6.fib6_local_tbl->tb6_peers);
#पूर्ण_अगर
	fib6_tables_init(net);

	वापस 0;

#अगर_घोषित CONFIG_IPV6_MULTIPLE_TABLES
out_fib6_मुख्य_tbl:
	kमुक्त(net->ipv6.fib6_मुख्य_tbl);
#पूर्ण_अगर
out_fib_table_hash:
	kमुक्त(net->ipv6.fib_table_hash);
out_rt6_stats:
	kमुक्त(net->ipv6.rt6_stats);
out_समयr:
	fib6_notअगरier_निकास(net);
	वापस -ENOMEM;
पूर्ण

अटल व्योम fib6_net_निकास(काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक i;

	del_समयr_sync(&net->ipv6.ip6_fib_समयr);

	क्रम (i = 0; i < FIB6_TABLE_HASHSZ; i++) अणु
		काष्ठा hlist_head *head = &net->ipv6.fib_table_hash[i];
		काष्ठा hlist_node *पंचांगp;
		काष्ठा fib6_table *tb;

		hlist_क्रम_each_entry_safe(tb, पंचांगp, head, tb6_hlist) अणु
			hlist_del(&tb->tb6_hlist);
			fib6_मुक्त_table(tb);
		पूर्ण
	पूर्ण

	kमुक्त(net->ipv6.fib_table_hash);
	kमुक्त(net->ipv6.rt6_stats);
	fib6_notअगरier_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations fib6_net_ops = अणु
	.init = fib6_net_init,
	.निकास = fib6_net_निकास,
पूर्ण;

पूर्णांक __init fib6_init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	fib6_node_kmem = kmem_cache_create("fib6_nodes",
					   माप(काष्ठा fib6_node),
					   0, SLAB_HWCACHE_ALIGN,
					   शून्य);
	अगर (!fib6_node_kmem)
		जाओ out;

	ret = रेजिस्टर_pernet_subsys(&fib6_net_ops);
	अगर (ret)
		जाओ out_kmem_cache_create;

	ret = rtnl_रेजिस्टर_module(THIS_MODULE, PF_INET6, RTM_GETROUTE, शून्य,
				   inet6_dump_fib, 0);
	अगर (ret)
		जाओ out_unरेजिस्टर_subsys;

	__fib6_flush_trees = fib6_flush_trees;
out:
	वापस ret;

out_unरेजिस्टर_subsys:
	unरेजिस्टर_pernet_subsys(&fib6_net_ops);
out_kmem_cache_create:
	kmem_cache_destroy(fib6_node_kmem);
	जाओ out;
पूर्ण

व्योम fib6_gc_cleanup(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&fib6_net_ops);
	kmem_cache_destroy(fib6_node_kmem);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
अटल पूर्णांक ipv6_route_native_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा fib6_info *rt = v;
	काष्ठा ipv6_route_iter *iter = seq->निजी;
	काष्ठा fib6_nh *fib6_nh = rt->fib6_nh;
	अचिन्हित पूर्णांक flags = rt->fib6_flags;
	स्थिर काष्ठा net_device *dev;

	अगर (rt->nh)
		fib6_nh = nexthop_fib6_nh_bh(rt->nh);

	seq_म_लिखो(seq, "%pi6 %02x ", &rt->fib6_dst.addr, rt->fib6_dst.plen);

#अगर_घोषित CONFIG_IPV6_SUBTREES
	seq_म_लिखो(seq, "%pi6 %02x ", &rt->fib6_src.addr, rt->fib6_src.plen);
#अन्यथा
	seq_माला_दो(seq, "00000000000000000000000000000000 00 ");
#पूर्ण_अगर
	अगर (fib6_nh->fib_nh_gw_family) अणु
		flags |= RTF_GATEWAY;
		seq_म_लिखो(seq, "%pi6", &fib6_nh->fib_nh_gw6);
	पूर्ण अन्यथा अणु
		seq_माला_दो(seq, "00000000000000000000000000000000");
	पूर्ण

	dev = fib6_nh->fib_nh_dev;
	seq_म_लिखो(seq, " %08x %08x %08x %08x %8s\n",
		   rt->fib6_metric, refcount_पढ़ो(&rt->fib6_ref), 0,
		   flags, dev ? dev->name : "");
	iter->w.leaf = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक ipv6_route_yield(काष्ठा fib6_walker *w)
अणु
	काष्ठा ipv6_route_iter *iter = w->args;

	अगर (!iter->skip)
		वापस 1;

	करो अणु
		iter->w.leaf = rcu_dereference_रक्षित(
				iter->w.leaf->fib6_next,
				lockdep_is_held(&iter->tbl->tb6_lock));
		iter->skip--;
		अगर (!iter->skip && iter->w.leaf)
			वापस 1;
	पूर्ण जबतक (iter->w.leaf);

	वापस 0;
पूर्ण

अटल व्योम ipv6_route_seq_setup_walk(काष्ठा ipv6_route_iter *iter,
				      काष्ठा net *net)
अणु
	स_रखो(&iter->w, 0, माप(iter->w));
	iter->w.func = ipv6_route_yield;
	iter->w.root = &iter->tbl->tb6_root;
	iter->w.state = FWS_INIT;
	iter->w.node = iter->w.root;
	iter->w.args = iter;
	iter->sernum = iter->w.root->fn_sernum;
	INIT_LIST_HEAD(&iter->w.lh);
	fib6_walker_link(net, &iter->w);
पूर्ण

अटल काष्ठा fib6_table *ipv6_route_seq_next_table(काष्ठा fib6_table *tbl,
						    काष्ठा net *net)
अणु
	अचिन्हित पूर्णांक h;
	काष्ठा hlist_node *node;

	अगर (tbl) अणु
		h = (tbl->tb6_id & (FIB6_TABLE_HASHSZ - 1)) + 1;
		node = rcu_dereference_bh(hlist_next_rcu(&tbl->tb6_hlist));
	पूर्ण अन्यथा अणु
		h = 0;
		node = शून्य;
	पूर्ण

	जबतक (!node && h < FIB6_TABLE_HASHSZ) अणु
		node = rcu_dereference_bh(
			hlist_first_rcu(&net->ipv6.fib_table_hash[h++]));
	पूर्ण
	वापस hlist_entry_safe(node, काष्ठा fib6_table, tb6_hlist);
पूर्ण

अटल व्योम ipv6_route_check_sernum(काष्ठा ipv6_route_iter *iter)
अणु
	अगर (iter->sernum != iter->w.root->fn_sernum) अणु
		iter->sernum = iter->w.root->fn_sernum;
		iter->w.state = FWS_INIT;
		iter->w.node = iter->w.root;
		WARN_ON(iter->w.skip);
		iter->w.skip = iter->w.count;
	पूर्ण
पूर्ण

अटल व्योम *ipv6_route_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	पूर्णांक r;
	काष्ठा fib6_info *n;
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा ipv6_route_iter *iter = seq->निजी;

	++(*pos);
	अगर (!v)
		जाओ iter_table;

	n = rcu_dereference_bh(((काष्ठा fib6_info *)v)->fib6_next);
	अगर (n)
		वापस n;

iter_table:
	ipv6_route_check_sernum(iter);
	spin_lock_bh(&iter->tbl->tb6_lock);
	r = fib6_walk_जारी(&iter->w);
	spin_unlock_bh(&iter->tbl->tb6_lock);
	अगर (r > 0) अणु
		वापस iter->w.leaf;
	पूर्ण अन्यथा अगर (r < 0) अणु
		fib6_walker_unlink(net, &iter->w);
		वापस शून्य;
	पूर्ण
	fib6_walker_unlink(net, &iter->w);

	iter->tbl = ipv6_route_seq_next_table(iter->tbl, net);
	अगर (!iter->tbl)
		वापस शून्य;

	ipv6_route_seq_setup_walk(iter, net);
	जाओ iter_table;
पूर्ण

अटल व्योम *ipv6_route_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU_BH)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा ipv6_route_iter *iter = seq->निजी;

	rcu_पढ़ो_lock_bh();
	iter->tbl = ipv6_route_seq_next_table(शून्य, net);
	iter->skip = *pos;

	अगर (iter->tbl) अणु
		loff_t p = 0;

		ipv6_route_seq_setup_walk(iter, net);
		वापस ipv6_route_seq_next(seq, शून्य, &p);
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण
पूर्ण

अटल bool ipv6_route_iter_active(काष्ठा ipv6_route_iter *iter)
अणु
	काष्ठा fib6_walker *w = &iter->w;
	वापस w->node && !(w->state == FWS_U && w->node == w->root);
पूर्ण

अटल व्योम ipv6_route_native_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU_BH)
अणु
	काष्ठा net *net = seq_file_net(seq);
	काष्ठा ipv6_route_iter *iter = seq->निजी;

	अगर (ipv6_route_iter_active(iter))
		fib6_walker_unlink(net, &iter->w);

	rcu_पढ़ो_unlock_bh();
पूर्ण

#अगर IS_BUILTIN(CONFIG_IPV6) && defined(CONFIG_BPF_SYSCALL)
अटल पूर्णांक ipv6_route_prog_seq_show(काष्ठा bpf_prog *prog,
				    काष्ठा bpf_iter_meta *meta,
				    व्योम *v)
अणु
	काष्ठा bpf_iter__ipv6_route ctx;

	ctx.meta = meta;
	ctx.rt = v;
	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक ipv6_route_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ipv6_route_iter *iter = seq->निजी;
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, false);
	अगर (!prog)
		वापस ipv6_route_native_seq_show(seq, v);

	ret = ipv6_route_prog_seq_show(prog, &meta, v);
	iter->w.leaf = शून्य;

	वापस ret;
पूर्ण

अटल व्योम ipv6_route_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	अगर (!v) अणु
		meta.seq = seq;
		prog = bpf_iter_get_info(&meta, true);
		अगर (prog)
			(व्योम)ipv6_route_prog_seq_show(prog, &meta, v);
	पूर्ण

	ipv6_route_native_seq_stop(seq, v);
पूर्ण
#अन्यथा
अटल पूर्णांक ipv6_route_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस ipv6_route_native_seq_show(seq, v);
पूर्ण

अटल व्योम ipv6_route_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	ipv6_route_native_seq_stop(seq, v);
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा seq_operations ipv6_route_seq_ops = अणु
	.start	= ipv6_route_seq_start,
	.next	= ipv6_route_seq_next,
	.stop	= ipv6_route_seq_stop,
	.show	= ipv6_route_seq_show
पूर्ण;
#पूर्ण_अगर /* CONFIG_PROC_FS */
