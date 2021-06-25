<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * count the number of connections matching an arbitrary key.
 *
 * (C) 2017 Red Hat GmbH
 * Author: Florian Westphal <fw@म_माप.de>
 *
 * split from xt_connlimit.c:
 *   (c) 2000 Gerd Knorr <kraxel@bytesex.org>
 *   Nov 2002: Martin Bene <martin.bene@icomedias.com>:
 *		only ignore TIME_WAIT or gone connections
 *   (C) CC Computer Consultants GmbH, 2007
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/jhash.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/netfilter/nf_conntrack_tcp.h>
#समावेश <linux/netfilter/x_tables.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_count.h>
#समावेश <net/netfilter/nf_conntrack_core.h>
#समावेश <net/netfilter/nf_conntrack_tuple.h>
#समावेश <net/netfilter/nf_conntrack_zones.h>

#घोषणा CONNCOUNT_SLOTS		256U

#घोषणा CONNCOUNT_GC_MAX_NODES	8
#घोषणा MAX_KEYLEN		5

/* we will save the tuples of all connections we care about */
काष्ठा nf_conncount_tuple अणु
	काष्ठा list_head		node;
	काष्ठा nf_conntrack_tuple	tuple;
	काष्ठा nf_conntrack_zone	zone;
	पूर्णांक				cpu;
	u32				jअगरfies32;
पूर्ण;

काष्ठा nf_conncount_rb अणु
	काष्ठा rb_node node;
	काष्ठा nf_conncount_list list;
	u32 key[MAX_KEYLEN];
	काष्ठा rcu_head rcu_head;
पूर्ण;

अटल spinlock_t nf_conncount_locks[CONNCOUNT_SLOTS] __cacheline_aligned_in_smp;

काष्ठा nf_conncount_data अणु
	अचिन्हित पूर्णांक keylen;
	काष्ठा rb_root root[CONNCOUNT_SLOTS];
	काष्ठा net *net;
	काष्ठा work_काष्ठा gc_work;
	अचिन्हित दीर्घ pending_trees[BITS_TO_LONGS(CONNCOUNT_SLOTS)];
	अचिन्हित पूर्णांक gc_tree;
पूर्ण;

अटल u_पूर्णांक32_t conncount_rnd __पढ़ो_mostly;
अटल काष्ठा kmem_cache *conncount_rb_cachep __पढ़ो_mostly;
अटल काष्ठा kmem_cache *conncount_conn_cachep __पढ़ो_mostly;

अटल अंतरभूत bool alपढ़ोy_बंदd(स्थिर काष्ठा nf_conn *conn)
अणु
	अगर (nf_ct_protonum(conn) == IPPROTO_TCP)
		वापस conn->proto.tcp.state == TCP_CONNTRACK_TIME_WAIT ||
		       conn->proto.tcp.state == TCP_CONNTRACK_CLOSE;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक key_dअगरf(स्थिर u32 *a, स्थिर u32 *b, अचिन्हित पूर्णांक klen)
अणु
	वापस स_भेद(a, b, klen * माप(u32));
पूर्ण

अटल व्योम conn_मुक्त(काष्ठा nf_conncount_list *list,
		      काष्ठा nf_conncount_tuple *conn)
अणु
	lockdep_निश्चित_held(&list->list_lock);

	list->count--;
	list_del(&conn->node);

	kmem_cache_मुक्त(conncount_conn_cachep, conn);
पूर्ण

अटल स्थिर काष्ठा nf_conntrack_tuple_hash *
find_or_evict(काष्ठा net *net, काष्ठा nf_conncount_list *list,
	      काष्ठा nf_conncount_tuple *conn)
अणु
	स्थिर काष्ठा nf_conntrack_tuple_hash *found;
	अचिन्हित दीर्घ a, b;
	पूर्णांक cpu = raw_smp_processor_id();
	u32 age;

	found = nf_conntrack_find_get(net, &conn->zone, &conn->tuple);
	अगर (found)
		वापस found;
	b = conn->jअगरfies32;
	a = (u32)jअगरfies;

	/* conn might have been added just beक्रमe by another cpu and
	 * might still be unconfirmed.  In this हाल, nf_conntrack_find()
	 * वापसs no result.  Thus only evict अगर this cpu added the
	 * stale entry or अगर the entry is older than two jअगरfies.
	 */
	age = a - b;
	अगर (conn->cpu == cpu || age >= 2) अणु
		conn_मुक्त(list, conn);
		वापस ERR_PTR(-ENOENT);
	पूर्ण

	वापस ERR_PTR(-EAGAIN);
पूर्ण

अटल पूर्णांक __nf_conncount_add(काष्ठा net *net,
			      काष्ठा nf_conncount_list *list,
			      स्थिर काष्ठा nf_conntrack_tuple *tuple,
			      स्थिर काष्ठा nf_conntrack_zone *zone)
अणु
	स्थिर काष्ठा nf_conntrack_tuple_hash *found;
	काष्ठा nf_conncount_tuple *conn, *conn_n;
	काष्ठा nf_conn *found_ct;
	अचिन्हित पूर्णांक collect = 0;

	/* check the saved connections */
	list_क्रम_each_entry_safe(conn, conn_n, &list->head, node) अणु
		अगर (collect > CONNCOUNT_GC_MAX_NODES)
			अवरोध;

		found = find_or_evict(net, list, conn);
		अगर (IS_ERR(found)) अणु
			/* Not found, but might be about to be confirmed */
			अगर (PTR_ERR(found) == -EAGAIN) अणु
				अगर (nf_ct_tuple_equal(&conn->tuple, tuple) &&
				    nf_ct_zone_id(&conn->zone, conn->zone.dir) ==
				    nf_ct_zone_id(zone, zone->dir))
					वापस 0; /* alपढ़ोy exists */
			पूर्ण अन्यथा अणु
				collect++;
			पूर्ण
			जारी;
		पूर्ण

		found_ct = nf_ct_tuplehash_to_ctrack(found);

		अगर (nf_ct_tuple_equal(&conn->tuple, tuple) &&
		    nf_ct_zone_equal(found_ct, zone, zone->dir)) अणु
			/*
			 * We should not see tuples twice unless someone hooks
			 * this पूर्णांकo a table without "-p tcp --syn".
			 *
			 * Attempt to aव्योम a re-add in this हाल.
			 */
			nf_ct_put(found_ct);
			वापस 0;
		पूर्ण अन्यथा अगर (alपढ़ोy_बंदd(found_ct)) अणु
			/*
			 * we करो not care about connections which are
			 * बंदd alपढ़ोy -> ditch it
			 */
			nf_ct_put(found_ct);
			conn_मुक्त(list, conn);
			collect++;
			जारी;
		पूर्ण

		nf_ct_put(found_ct);
	पूर्ण

	अगर (WARN_ON_ONCE(list->count > पूर्णांक_उच्च))
		वापस -EOVERFLOW;

	conn = kmem_cache_alloc(conncount_conn_cachep, GFP_ATOMIC);
	अगर (conn == शून्य)
		वापस -ENOMEM;

	conn->tuple = *tuple;
	conn->zone = *zone;
	conn->cpu = raw_smp_processor_id();
	conn->jअगरfies32 = (u32)jअगरfies;
	list_add_tail(&conn->node, &list->head);
	list->count++;
	वापस 0;
पूर्ण

पूर्णांक nf_conncount_add(काष्ठा net *net,
		     काष्ठा nf_conncount_list *list,
		     स्थिर काष्ठा nf_conntrack_tuple *tuple,
		     स्थिर काष्ठा nf_conntrack_zone *zone)
अणु
	पूर्णांक ret;

	/* check the saved connections */
	spin_lock_bh(&list->list_lock);
	ret = __nf_conncount_add(net, list, tuple, zone);
	spin_unlock_bh(&list->list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conncount_add);

व्योम nf_conncount_list_init(काष्ठा nf_conncount_list *list)
अणु
	spin_lock_init(&list->list_lock);
	INIT_LIST_HEAD(&list->head);
	list->count = 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conncount_list_init);

/* Return true अगर the list is empty. Must be called with BH disabled. */
bool nf_conncount_gc_list(काष्ठा net *net,
			  काष्ठा nf_conncount_list *list)
अणु
	स्थिर काष्ठा nf_conntrack_tuple_hash *found;
	काष्ठा nf_conncount_tuple *conn, *conn_n;
	काष्ठा nf_conn *found_ct;
	अचिन्हित पूर्णांक collected = 0;
	bool ret = false;

	/* करोn't bother अगर other cpu is alपढ़ोy करोing GC */
	अगर (!spin_trylock(&list->list_lock))
		वापस false;

	list_क्रम_each_entry_safe(conn, conn_n, &list->head, node) अणु
		found = find_or_evict(net, list, conn);
		अगर (IS_ERR(found)) अणु
			अगर (PTR_ERR(found) == -ENOENT)
				collected++;
			जारी;
		पूर्ण

		found_ct = nf_ct_tuplehash_to_ctrack(found);
		अगर (alपढ़ोy_बंदd(found_ct)) अणु
			/*
			 * we करो not care about connections which are
			 * बंदd alपढ़ोy -> ditch it
			 */
			nf_ct_put(found_ct);
			conn_मुक्त(list, conn);
			collected++;
			जारी;
		पूर्ण

		nf_ct_put(found_ct);
		अगर (collected > CONNCOUNT_GC_MAX_NODES)
			अवरोध;
	पूर्ण

	अगर (!list->count)
		ret = true;
	spin_unlock(&list->list_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conncount_gc_list);

अटल व्योम __tree_nodes_मुक्त(काष्ठा rcu_head *h)
अणु
	काष्ठा nf_conncount_rb *rbconn;

	rbconn = container_of(h, काष्ठा nf_conncount_rb, rcu_head);
	kmem_cache_मुक्त(conncount_rb_cachep, rbconn);
पूर्ण

/* caller must hold tree nf_conncount_locks[] lock */
अटल व्योम tree_nodes_मुक्त(काष्ठा rb_root *root,
			    काष्ठा nf_conncount_rb *gc_nodes[],
			    अचिन्हित पूर्णांक gc_count)
अणु
	काष्ठा nf_conncount_rb *rbconn;

	जबतक (gc_count) अणु
		rbconn = gc_nodes[--gc_count];
		spin_lock(&rbconn->list.list_lock);
		अगर (!rbconn->list.count) अणु
			rb_erase(&rbconn->node, root);
			call_rcu(&rbconn->rcu_head, __tree_nodes_मुक्त);
		पूर्ण
		spin_unlock(&rbconn->list.list_lock);
	पूर्ण
पूर्ण

अटल व्योम schedule_gc_worker(काष्ठा nf_conncount_data *data, पूर्णांक tree)
अणु
	set_bit(tree, data->pending_trees);
	schedule_work(&data->gc_work);
पूर्ण

अटल अचिन्हित पूर्णांक
insert_tree(काष्ठा net *net,
	    काष्ठा nf_conncount_data *data,
	    काष्ठा rb_root *root,
	    अचिन्हित पूर्णांक hash,
	    स्थिर u32 *key,
	    स्थिर काष्ठा nf_conntrack_tuple *tuple,
	    स्थिर काष्ठा nf_conntrack_zone *zone)
अणु
	काष्ठा nf_conncount_rb *gc_nodes[CONNCOUNT_GC_MAX_NODES];
	काष्ठा rb_node **rbnode, *parent;
	काष्ठा nf_conncount_rb *rbconn;
	काष्ठा nf_conncount_tuple *conn;
	अचिन्हित पूर्णांक count = 0, gc_count = 0;
	u8 keylen = data->keylen;
	bool करो_gc = true;

	spin_lock_bh(&nf_conncount_locks[hash]);
restart:
	parent = शून्य;
	rbnode = &(root->rb_node);
	जबतक (*rbnode) अणु
		पूर्णांक dअगरf;
		rbconn = rb_entry(*rbnode, काष्ठा nf_conncount_rb, node);

		parent = *rbnode;
		dअगरf = key_dअगरf(key, rbconn->key, keylen);
		अगर (dअगरf < 0) अणु
			rbnode = &((*rbnode)->rb_left);
		पूर्ण अन्यथा अगर (dअगरf > 0) अणु
			rbnode = &((*rbnode)->rb_right);
		पूर्ण अन्यथा अणु
			पूर्णांक ret;

			ret = nf_conncount_add(net, &rbconn->list, tuple, zone);
			अगर (ret)
				count = 0; /* hotdrop */
			अन्यथा
				count = rbconn->list.count;
			tree_nodes_मुक्त(root, gc_nodes, gc_count);
			जाओ out_unlock;
		पूर्ण

		अगर (gc_count >= ARRAY_SIZE(gc_nodes))
			जारी;

		अगर (करो_gc && nf_conncount_gc_list(net, &rbconn->list))
			gc_nodes[gc_count++] = rbconn;
	पूर्ण

	अगर (gc_count) अणु
		tree_nodes_मुक्त(root, gc_nodes, gc_count);
		schedule_gc_worker(data, hash);
		gc_count = 0;
		करो_gc = false;
		जाओ restart;
	पूर्ण

	/* expected हाल: match, insert new node */
	rbconn = kmem_cache_alloc(conncount_rb_cachep, GFP_ATOMIC);
	अगर (rbconn == शून्य)
		जाओ out_unlock;

	conn = kmem_cache_alloc(conncount_conn_cachep, GFP_ATOMIC);
	अगर (conn == शून्य) अणु
		kmem_cache_मुक्त(conncount_rb_cachep, rbconn);
		जाओ out_unlock;
	पूर्ण

	conn->tuple = *tuple;
	conn->zone = *zone;
	स_नकल(rbconn->key, key, माप(u32) * keylen);

	nf_conncount_list_init(&rbconn->list);
	list_add(&conn->node, &rbconn->list.head);
	count = 1;
	rbconn->list.count = count;

	rb_link_node_rcu(&rbconn->node, parent, rbnode);
	rb_insert_color(&rbconn->node, root);
out_unlock:
	spin_unlock_bh(&nf_conncount_locks[hash]);
	वापस count;
पूर्ण

अटल अचिन्हित पूर्णांक
count_tree(काष्ठा net *net,
	   काष्ठा nf_conncount_data *data,
	   स्थिर u32 *key,
	   स्थिर काष्ठा nf_conntrack_tuple *tuple,
	   स्थिर काष्ठा nf_conntrack_zone *zone)
अणु
	काष्ठा rb_root *root;
	काष्ठा rb_node *parent;
	काष्ठा nf_conncount_rb *rbconn;
	अचिन्हित पूर्णांक hash;
	u8 keylen = data->keylen;

	hash = jhash2(key, data->keylen, conncount_rnd) % CONNCOUNT_SLOTS;
	root = &data->root[hash];

	parent = rcu_dereference_raw(root->rb_node);
	जबतक (parent) अणु
		पूर्णांक dअगरf;

		rbconn = rb_entry(parent, काष्ठा nf_conncount_rb, node);

		dअगरf = key_dअगरf(key, rbconn->key, keylen);
		अगर (dअगरf < 0) अणु
			parent = rcu_dereference_raw(parent->rb_left);
		पूर्ण अन्यथा अगर (dअगरf > 0) अणु
			parent = rcu_dereference_raw(parent->rb_right);
		पूर्ण अन्यथा अणु
			पूर्णांक ret;

			अगर (!tuple) अणु
				nf_conncount_gc_list(net, &rbconn->list);
				वापस rbconn->list.count;
			पूर्ण

			spin_lock_bh(&rbconn->list.list_lock);
			/* Node might be about to be मुक्त'd.
			 * We need to defer to insert_tree() in this हाल.
			 */
			अगर (rbconn->list.count == 0) अणु
				spin_unlock_bh(&rbconn->list.list_lock);
				अवरोध;
			पूर्ण

			/* same source network -> be counted! */
			ret = __nf_conncount_add(net, &rbconn->list, tuple, zone);
			spin_unlock_bh(&rbconn->list.list_lock);
			अगर (ret)
				वापस 0; /* hotdrop */
			अन्यथा
				वापस rbconn->list.count;
		पूर्ण
	पूर्ण

	अगर (!tuple)
		वापस 0;

	वापस insert_tree(net, data, root, hash, key, tuple, zone);
पूर्ण

अटल व्योम tree_gc_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nf_conncount_data *data = container_of(work, काष्ठा nf_conncount_data, gc_work);
	काष्ठा nf_conncount_rb *gc_nodes[CONNCOUNT_GC_MAX_NODES], *rbconn;
	काष्ठा rb_root *root;
	काष्ठा rb_node *node;
	अचिन्हित पूर्णांक tree, next_tree, gc_count = 0;

	tree = data->gc_tree % CONNCOUNT_SLOTS;
	root = &data->root[tree];

	local_bh_disable();
	rcu_पढ़ो_lock();
	क्रम (node = rb_first(root); node != शून्य; node = rb_next(node)) अणु
		rbconn = rb_entry(node, काष्ठा nf_conncount_rb, node);
		अगर (nf_conncount_gc_list(data->net, &rbconn->list))
			gc_count++;
	पूर्ण
	rcu_पढ़ो_unlock();
	local_bh_enable();

	cond_resched();

	spin_lock_bh(&nf_conncount_locks[tree]);
	अगर (gc_count < ARRAY_SIZE(gc_nodes))
		जाओ next; /* करो not bother */

	gc_count = 0;
	node = rb_first(root);
	जबतक (node != शून्य) अणु
		rbconn = rb_entry(node, काष्ठा nf_conncount_rb, node);
		node = rb_next(node);

		अगर (rbconn->list.count > 0)
			जारी;

		gc_nodes[gc_count++] = rbconn;
		अगर (gc_count >= ARRAY_SIZE(gc_nodes)) अणु
			tree_nodes_मुक्त(root, gc_nodes, gc_count);
			gc_count = 0;
		पूर्ण
	पूर्ण

	tree_nodes_मुक्त(root, gc_nodes, gc_count);
next:
	clear_bit(tree, data->pending_trees);

	next_tree = (tree + 1) % CONNCOUNT_SLOTS;
	next_tree = find_next_bit(data->pending_trees, CONNCOUNT_SLOTS, next_tree);

	अगर (next_tree < CONNCOUNT_SLOTS) अणु
		data->gc_tree = next_tree;
		schedule_work(work);
	पूर्ण

	spin_unlock_bh(&nf_conncount_locks[tree]);
पूर्ण

/* Count and वापस number of conntrack entries in 'net' with particular 'key'.
 * If 'tuple' is not null, insert it पूर्णांकo the accounting data काष्ठाure.
 * Call with RCU पढ़ो lock.
 */
अचिन्हित पूर्णांक nf_conncount_count(काष्ठा net *net,
				काष्ठा nf_conncount_data *data,
				स्थिर u32 *key,
				स्थिर काष्ठा nf_conntrack_tuple *tuple,
				स्थिर काष्ठा nf_conntrack_zone *zone)
अणु
	वापस count_tree(net, data, key, tuple, zone);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conncount_count);

काष्ठा nf_conncount_data *nf_conncount_init(काष्ठा net *net, अचिन्हित पूर्णांक family,
					    अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा nf_conncount_data *data;
	पूर्णांक ret, i;

	अगर (keylen % माप(u32) ||
	    keylen / माप(u32) > MAX_KEYLEN ||
	    keylen == 0)
		वापस ERR_PTR(-EINVAL);

	net_get_अक्रमom_once(&conncount_rnd, माप(conncount_rnd));

	data = kदो_स्मृति(माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस ERR_PTR(-ENOMEM);

	ret = nf_ct_netns_get(net, family);
	अगर (ret < 0) अणु
		kमुक्त(data);
		वापस ERR_PTR(ret);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data->root); ++i)
		data->root[i] = RB_ROOT;

	data->keylen = keylen / माप(u32);
	data->net = net;
	INIT_WORK(&data->gc_work, tree_gc_worker);

	वापस data;
पूर्ण
EXPORT_SYMBOL_GPL(nf_conncount_init);

व्योम nf_conncount_cache_मुक्त(काष्ठा nf_conncount_list *list)
अणु
	काष्ठा nf_conncount_tuple *conn, *conn_n;

	list_क्रम_each_entry_safe(conn, conn_n, &list->head, node)
		kmem_cache_मुक्त(conncount_conn_cachep, conn);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conncount_cache_मुक्त);

अटल व्योम destroy_tree(काष्ठा rb_root *r)
अणु
	काष्ठा nf_conncount_rb *rbconn;
	काष्ठा rb_node *node;

	जबतक ((node = rb_first(r)) != शून्य) अणु
		rbconn = rb_entry(node, काष्ठा nf_conncount_rb, node);

		rb_erase(node, r);

		nf_conncount_cache_मुक्त(&rbconn->list);

		kmem_cache_मुक्त(conncount_rb_cachep, rbconn);
	पूर्ण
पूर्ण

व्योम nf_conncount_destroy(काष्ठा net *net, अचिन्हित पूर्णांक family,
			  काष्ठा nf_conncount_data *data)
अणु
	अचिन्हित पूर्णांक i;

	cancel_work_sync(&data->gc_work);
	nf_ct_netns_put(net, family);

	क्रम (i = 0; i < ARRAY_SIZE(data->root); ++i)
		destroy_tree(&data->root[i]);

	kमुक्त(data);
पूर्ण
EXPORT_SYMBOL_GPL(nf_conncount_destroy);

अटल पूर्णांक __init nf_conncount_modinit(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CONNCOUNT_SLOTS; ++i)
		spin_lock_init(&nf_conncount_locks[i]);

	conncount_conn_cachep = kmem_cache_create("nf_conncount_tuple",
					   माप(काष्ठा nf_conncount_tuple),
					   0, 0, शून्य);
	अगर (!conncount_conn_cachep)
		वापस -ENOMEM;

	conncount_rb_cachep = kmem_cache_create("nf_conncount_rb",
					   माप(काष्ठा nf_conncount_rb),
					   0, 0, शून्य);
	अगर (!conncount_rb_cachep) अणु
		kmem_cache_destroy(conncount_conn_cachep);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास nf_conncount_modनिकास(व्योम)
अणु
	kmem_cache_destroy(conncount_conn_cachep);
	kmem_cache_destroy(conncount_rb_cachep);
पूर्ण

module_init(nf_conncount_modinit);
module_निकास(nf_conncount_modनिकास);
MODULE_AUTHOR("Jan Engelhardt <jengelh@medozas.de>");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_DESCRIPTION("netfilter: count number of connections matching a key");
MODULE_LICENSE("GPL");
