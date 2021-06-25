<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/workqueue.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/cache.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/idr.h>
#समावेश <linux/rculist.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/fs.h>
#समावेश <linux/proc_ns.h>
#समावेश <linux/file.h>
#समावेश <linux/export.h>
#समावेश <linux/user_namespace.h>
#समावेश <linux/net_namespace.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/uidgid.h>
#समावेश <linux/cookie.h>

#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

/*
 *	Our network namespace स्थिरructor/deकाष्ठाor lists
 */

अटल LIST_HEAD(pernet_list);
अटल काष्ठा list_head *first_device = &pernet_list;

LIST_HEAD(net_namespace_list);
EXPORT_SYMBOL_GPL(net_namespace_list);

/* Protects net_namespace_list. Nests iside rtnl_lock() */
DECLARE_RWSEM(net_rwsem);
EXPORT_SYMBOL_GPL(net_rwsem);

#अगर_घोषित CONFIG_KEYS
अटल काष्ठा key_tag init_net_key_करोमुख्य = अणु .usage = REFCOUNT_INIT(1) पूर्ण;
#पूर्ण_अगर

काष्ठा net init_net = अणु
	.ns.count	= REFCOUNT_INIT(1),
	.dev_base_head	= LIST_HEAD_INIT(init_net.dev_base_head),
#अगर_घोषित CONFIG_KEYS
	.key_करोमुख्य	= &init_net_key_करोमुख्य,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(init_net);

अटल bool init_net_initialized;
/*
 * pernet_ops_rwsem: protects: pernet_list, net_generic_ids,
 * init_net_initialized and first_device poपूर्णांकer.
 * This is पूर्णांकernal net namespace object. Please, करोn't use it
 * outside.
 */
DECLARE_RWSEM(pernet_ops_rwsem);
EXPORT_SYMBOL_GPL(pernet_ops_rwsem);

#घोषणा MIN_PERNET_OPS_ID	\
	((माप(काष्ठा net_generic) + माप(व्योम *) - 1) / माप(व्योम *))

#घोषणा INITIAL_NET_GEN_PTRS	13 /* +1 क्रम len +2 क्रम rcu_head */

अटल अचिन्हित पूर्णांक max_gen_ptrs = INITIAL_NET_GEN_PTRS;

DEFINE_COOKIE(net_cookie);

अटल काष्ठा net_generic *net_alloc_generic(व्योम)
अणु
	काष्ठा net_generic *ng;
	अचिन्हित पूर्णांक generic_size = दुरत्व(काष्ठा net_generic, ptr[max_gen_ptrs]);

	ng = kzalloc(generic_size, GFP_KERNEL);
	अगर (ng)
		ng->s.len = max_gen_ptrs;

	वापस ng;
पूर्ण

अटल पूर्णांक net_assign_generic(काष्ठा net *net, अचिन्हित पूर्णांक id, व्योम *data)
अणु
	काष्ठा net_generic *ng, *old_ng;

	BUG_ON(id < MIN_PERNET_OPS_ID);

	old_ng = rcu_dereference_रक्षित(net->gen,
					   lockdep_is_held(&pernet_ops_rwsem));
	अगर (old_ng->s.len > id) अणु
		old_ng->ptr[id] = data;
		वापस 0;
	पूर्ण

	ng = net_alloc_generic();
	अगर (ng == शून्य)
		वापस -ENOMEM;

	/*
	 * Some synchronisation notes:
	 *
	 * The net_generic explores the net->gen array inside rcu
	 * पढ़ो section. Besides once set the net->gen->ptr[x]
	 * poपूर्णांकer never changes (see rules in netns/generic.h).
	 *
	 * That said, we simply duplicate this array and schedule
	 * the old copy क्रम kमुक्त after a grace period.
	 */

	स_नकल(&ng->ptr[MIN_PERNET_OPS_ID], &old_ng->ptr[MIN_PERNET_OPS_ID],
	       (old_ng->s.len - MIN_PERNET_OPS_ID) * माप(व्योम *));
	ng->ptr[id] = data;

	rcu_assign_poपूर्णांकer(net->gen, ng);
	kमुक्त_rcu(old_ng, s.rcu);
	वापस 0;
पूर्ण

अटल पूर्णांक ops_init(स्थिर काष्ठा pernet_operations *ops, काष्ठा net *net)
अणु
	पूर्णांक err = -ENOMEM;
	व्योम *data = शून्य;

	अगर (ops->id && ops->size) अणु
		data = kzalloc(ops->size, GFP_KERNEL);
		अगर (!data)
			जाओ out;

		err = net_assign_generic(net, *ops->id, data);
		अगर (err)
			जाओ cleanup;
	पूर्ण
	err = 0;
	अगर (ops->init)
		err = ops->init(net);
	अगर (!err)
		वापस 0;

cleanup:
	kमुक्त(data);

out:
	वापस err;
पूर्ण

अटल व्योम ops_मुक्त(स्थिर काष्ठा pernet_operations *ops, काष्ठा net *net)
अणु
	अगर (ops->id && ops->size) अणु
		kमुक्त(net_generic(net, *ops->id));
	पूर्ण
पूर्ण

अटल व्योम ops_pre_निकास_list(स्थिर काष्ठा pernet_operations *ops,
			      काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;

	अगर (ops->pre_निकास) अणु
		list_क्रम_each_entry(net, net_निकास_list, निकास_list)
			ops->pre_निकास(net);
	पूर्ण
पूर्ण

अटल व्योम ops_निकास_list(स्थिर काष्ठा pernet_operations *ops,
			  काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;
	अगर (ops->निकास) अणु
		list_क्रम_each_entry(net, net_निकास_list, निकास_list)
			ops->निकास(net);
	पूर्ण
	अगर (ops->निकास_batch)
		ops->निकास_batch(net_निकास_list);
पूर्ण

अटल व्योम ops_मुक्त_list(स्थिर काष्ठा pernet_operations *ops,
			  काष्ठा list_head *net_निकास_list)
अणु
	काष्ठा net *net;
	अगर (ops->size && ops->id) अणु
		list_क्रम_each_entry(net, net_निकास_list, निकास_list)
			ops_मुक्त(ops, net);
	पूर्ण
पूर्ण

/* should be called with nsid_lock held */
अटल पूर्णांक alloc_netid(काष्ठा net *net, काष्ठा net *peer, पूर्णांक reqid)
अणु
	पूर्णांक min = 0, max = 0;

	अगर (reqid >= 0) अणु
		min = reqid;
		max = reqid + 1;
	पूर्ण

	वापस idr_alloc(&net->netns_ids, peer, min, max, GFP_ATOMIC);
पूर्ण

/* This function is used by idr_क्रम_each(). If net is equal to peer, the
 * function वापसs the id so that idr_क्रम_each() stops. Because we cannot
 * वापसs the id 0 (idr_क्रम_each() will not stop), we वापस the magic value
 * NET_ID_ZERO (-1) क्रम it.
 */
#घोषणा NET_ID_ZERO -1
अटल पूर्णांक net_eq_idr(पूर्णांक id, व्योम *net, व्योम *peer)
अणु
	अगर (net_eq(net, peer))
		वापस id ? : NET_ID_ZERO;
	वापस 0;
पूर्ण

/* Must be called from RCU-critical section or with nsid_lock held */
अटल पूर्णांक __peernet2id(स्थिर काष्ठा net *net, काष्ठा net *peer)
अणु
	पूर्णांक id = idr_क्रम_each(&net->netns_ids, net_eq_idr, peer);

	/* Magic value क्रम id 0. */
	अगर (id == NET_ID_ZERO)
		वापस 0;
	अगर (id > 0)
		वापस id;

	वापस NETNSA_NSID_NOT_ASSIGNED;
पूर्ण

अटल व्योम rtnl_net_notअगरyid(काष्ठा net *net, पूर्णांक cmd, पूर्णांक id, u32 portid,
			      काष्ठा nlmsghdr *nlh, gfp_t gfp);
/* This function वापसs the id of a peer netns. If no id is asचिन्हित, one will
 * be allocated and वापसed.
 */
पूर्णांक peernet2id_alloc(काष्ठा net *net, काष्ठा net *peer, gfp_t gfp)
अणु
	पूर्णांक id;

	अगर (refcount_पढ़ो(&net->ns.count) == 0)
		वापस NETNSA_NSID_NOT_ASSIGNED;

	spin_lock_bh(&net->nsid_lock);
	id = __peernet2id(net, peer);
	अगर (id >= 0) अणु
		spin_unlock_bh(&net->nsid_lock);
		वापस id;
	पूर्ण

	/* When peer is obtained from RCU lists, we may race with
	 * its cleanup. Check whether it's alive, and this guarantees
	 * we never hash a peer back to net->netns_ids, after it has
	 * just been idr_हटाओ()'d from there in cleanup_net().
	 */
	अगर (!maybe_get_net(peer)) अणु
		spin_unlock_bh(&net->nsid_lock);
		वापस NETNSA_NSID_NOT_ASSIGNED;
	पूर्ण

	id = alloc_netid(net, peer, -1);
	spin_unlock_bh(&net->nsid_lock);

	put_net(peer);
	अगर (id < 0)
		वापस NETNSA_NSID_NOT_ASSIGNED;

	rtnl_net_notअगरyid(net, RTM_NEWNSID, id, 0, शून्य, gfp);

	वापस id;
पूर्ण
EXPORT_SYMBOL_GPL(peernet2id_alloc);

/* This function वापसs, अगर asचिन्हित, the id of a peer netns. */
पूर्णांक peernet2id(स्थिर काष्ठा net *net, काष्ठा net *peer)
अणु
	पूर्णांक id;

	rcu_पढ़ो_lock();
	id = __peernet2id(net, peer);
	rcu_पढ़ो_unlock();

	वापस id;
पूर्ण
EXPORT_SYMBOL(peernet2id);

/* This function वापसs true is the peer netns has an id asचिन्हित पूर्णांकo the
 * current netns.
 */
bool peernet_has_id(स्थिर काष्ठा net *net, काष्ठा net *peer)
अणु
	वापस peernet2id(net, peer) >= 0;
पूर्ण

काष्ठा net *get_net_ns_by_id(स्थिर काष्ठा net *net, पूर्णांक id)
अणु
	काष्ठा net *peer;

	अगर (id < 0)
		वापस शून्य;

	rcu_पढ़ो_lock();
	peer = idr_find(&net->netns_ids, id);
	अगर (peer)
		peer = maybe_get_net(peer);
	rcu_पढ़ो_unlock();

	वापस peer;
पूर्ण

/*
 * setup_net runs the initializers क्रम the network namespace object.
 */
अटल __net_init पूर्णांक setup_net(काष्ठा net *net, काष्ठा user_namespace *user_ns)
अणु
	/* Must be called with pernet_ops_rwsem held */
	स्थिर काष्ठा pernet_operations *ops, *saved_ops;
	पूर्णांक error = 0;
	LIST_HEAD(net_निकास_list);

	refcount_set(&net->ns.count, 1);
	refcount_set(&net->passive, 1);
	get_अक्रमom_bytes(&net->hash_mix, माप(u32));
	preempt_disable();
	net->net_cookie = gen_cookie_next(&net_cookie);
	preempt_enable();
	net->dev_base_seq = 1;
	net->user_ns = user_ns;
	idr_init(&net->netns_ids);
	spin_lock_init(&net->nsid_lock);
	mutex_init(&net->ipv4.ra_mutex);

	list_क्रम_each_entry(ops, &pernet_list, list) अणु
		error = ops_init(ops, net);
		अगर (error < 0)
			जाओ out_unकरो;
	पूर्ण
	करोwn_ग_लिखो(&net_rwsem);
	list_add_tail_rcu(&net->list, &net_namespace_list);
	up_ग_लिखो(&net_rwsem);
out:
	वापस error;

out_unकरो:
	/* Walk through the list backwards calling the निकास functions
	 * क्रम the pernet modules whose init functions did not fail.
	 */
	list_add(&net->निकास_list, &net_निकास_list);
	saved_ops = ops;
	list_क्रम_each_entry_जारी_reverse(ops, &pernet_list, list)
		ops_pre_निकास_list(ops, &net_निकास_list);

	synchronize_rcu();

	ops = saved_ops;
	list_क्रम_each_entry_जारी_reverse(ops, &pernet_list, list)
		ops_निकास_list(ops, &net_निकास_list);

	ops = saved_ops;
	list_क्रम_each_entry_जारी_reverse(ops, &pernet_list, list)
		ops_मुक्त_list(ops, &net_निकास_list);

	rcu_barrier();
	जाओ out;
पूर्ण

अटल पूर्णांक __net_init net_शेषs_init_net(काष्ठा net *net)
अणु
	net->core.sysctl_somaxconn = SOMAXCONN;
	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations net_शेषs_ops = अणु
	.init = net_शेषs_init_net,
पूर्ण;

अटल __init पूर्णांक net_शेषs_init(व्योम)
अणु
	अगर (रेजिस्टर_pernet_subsys(&net_शेषs_ops))
		panic("Cannot initialize net default settings");

	वापस 0;
पूर्ण

core_initcall(net_शेषs_init);

#अगर_घोषित CONFIG_NET_NS
अटल काष्ठा ucounts *inc_net_namespaces(काष्ठा user_namespace *ns)
अणु
	वापस inc_ucount(ns, current_euid(), UCOUNT_NET_NAMESPACES);
पूर्ण

अटल व्योम dec_net_namespaces(काष्ठा ucounts *ucounts)
अणु
	dec_ucount(ucounts, UCOUNT_NET_NAMESPACES);
पूर्ण

अटल काष्ठा kmem_cache *net_cachep __ro_after_init;
अटल काष्ठा workqueue_काष्ठा *netns_wq;

अटल काष्ठा net *net_alloc(व्योम)
अणु
	काष्ठा net *net = शून्य;
	काष्ठा net_generic *ng;

	ng = net_alloc_generic();
	अगर (!ng)
		जाओ out;

	net = kmem_cache_zalloc(net_cachep, GFP_KERNEL);
	अगर (!net)
		जाओ out_मुक्त;

#अगर_घोषित CONFIG_KEYS
	net->key_करोमुख्य = kzalloc(माप(काष्ठा key_tag), GFP_KERNEL);
	अगर (!net->key_करोमुख्य)
		जाओ out_मुक्त_2;
	refcount_set(&net->key_करोमुख्य->usage, 1);
#पूर्ण_अगर

	rcu_assign_poपूर्णांकer(net->gen, ng);
out:
	वापस net;

#अगर_घोषित CONFIG_KEYS
out_मुक्त_2:
	kmem_cache_मुक्त(net_cachep, net);
	net = शून्य;
#पूर्ण_अगर
out_मुक्त:
	kमुक्त(ng);
	जाओ out;
पूर्ण

अटल व्योम net_मुक्त(काष्ठा net *net)
अणु
	kमुक्त(rcu_access_poपूर्णांकer(net->gen));
	kmem_cache_मुक्त(net_cachep, net);
पूर्ण

व्योम net_drop_ns(व्योम *p)
अणु
	काष्ठा net *ns = p;
	अगर (ns && refcount_dec_and_test(&ns->passive))
		net_मुक्त(ns);
पूर्ण

काष्ठा net *copy_net_ns(अचिन्हित दीर्घ flags,
			काष्ठा user_namespace *user_ns, काष्ठा net *old_net)
अणु
	काष्ठा ucounts *ucounts;
	काष्ठा net *net;
	पूर्णांक rv;

	अगर (!(flags & CLONE_NEWNET))
		वापस get_net(old_net);

	ucounts = inc_net_namespaces(user_ns);
	अगर (!ucounts)
		वापस ERR_PTR(-ENOSPC);

	net = net_alloc();
	अगर (!net) अणु
		rv = -ENOMEM;
		जाओ dec_ucounts;
	पूर्ण
	refcount_set(&net->passive, 1);
	net->ucounts = ucounts;
	get_user_ns(user_ns);

	rv = करोwn_पढ़ो_समाप्तable(&pernet_ops_rwsem);
	अगर (rv < 0)
		जाओ put_userns;

	rv = setup_net(net, user_ns);

	up_पढ़ो(&pernet_ops_rwsem);

	अगर (rv < 0) अणु
put_userns:
		key_हटाओ_करोमुख्य(net->key_करोमुख्य);
		put_user_ns(user_ns);
		net_drop_ns(net);
dec_ucounts:
		dec_net_namespaces(ucounts);
		वापस ERR_PTR(rv);
	पूर्ण
	वापस net;
पूर्ण

/**
 * net_ns_get_ownership - get sysfs ownership data क्रम @net
 * @net: network namespace in question (can be शून्य)
 * @uid: kernel user ID क्रम sysfs objects
 * @gid: kernel group ID क्रम sysfs objects
 *
 * Returns the uid/gid pair of root in the user namespace associated with the
 * given network namespace.
 */
व्योम net_ns_get_ownership(स्थिर काष्ठा net *net, kuid_t *uid, kgid_t *gid)
अणु
	अगर (net) अणु
		kuid_t ns_root_uid = make_kuid(net->user_ns, 0);
		kgid_t ns_root_gid = make_kgid(net->user_ns, 0);

		अगर (uid_valid(ns_root_uid))
			*uid = ns_root_uid;

		अगर (gid_valid(ns_root_gid))
			*gid = ns_root_gid;
	पूर्ण अन्यथा अणु
		*uid = GLOBAL_ROOT_UID;
		*gid = GLOBAL_ROOT_GID;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(net_ns_get_ownership);

अटल व्योम unhash_nsid(काष्ठा net *net, काष्ठा net *last)
अणु
	काष्ठा net *पंचांगp;
	/* This function is only called from cleanup_net() work,
	 * and this work is the only process, that may delete
	 * a net from net_namespace_list. So, when the below
	 * is executing, the list may only grow. Thus, we करो not
	 * use क्रम_each_net_rcu() or net_rwsem.
	 */
	क्रम_each_net(पंचांगp) अणु
		पूर्णांक id;

		spin_lock_bh(&पंचांगp->nsid_lock);
		id = __peernet2id(पंचांगp, net);
		अगर (id >= 0)
			idr_हटाओ(&पंचांगp->netns_ids, id);
		spin_unlock_bh(&पंचांगp->nsid_lock);
		अगर (id >= 0)
			rtnl_net_notअगरyid(पंचांगp, RTM_DELNSID, id, 0, शून्य,
					  GFP_KERNEL);
		अगर (पंचांगp == last)
			अवरोध;
	पूर्ण
	spin_lock_bh(&net->nsid_lock);
	idr_destroy(&net->netns_ids);
	spin_unlock_bh(&net->nsid_lock);
पूर्ण

अटल LLIST_HEAD(cleanup_list);

अटल व्योम cleanup_net(काष्ठा work_काष्ठा *work)
अणु
	स्थिर काष्ठा pernet_operations *ops;
	काष्ठा net *net, *पंचांगp, *last;
	काष्ठा llist_node *net_समाप्त_list;
	LIST_HEAD(net_निकास_list);

	/* Atomically snapshot the list of namespaces to cleanup */
	net_समाप्त_list = llist_del_all(&cleanup_list);

	करोwn_पढ़ो(&pernet_ops_rwsem);

	/* Don't let anyone अन्यथा find us. */
	करोwn_ग_लिखो(&net_rwsem);
	llist_क्रम_each_entry(net, net_समाप्त_list, cleanup_list)
		list_del_rcu(&net->list);
	/* Cache last net. After we unlock rtnl, no one new net
	 * added to net_namespace_list can assign nsid poपूर्णांकer
	 * to a net from net_समाप्त_list (see peernet2id_alloc()).
	 * So, we skip them in unhash_nsid().
	 *
	 * Note, that unhash_nsid() करोes not delete nsid links
	 * between net_समाप्त_list's nets, as they've alपढ़ोy
	 * deleted from net_namespace_list. But, this would be
	 * useless anyway, as netns_ids are destroyed there.
	 */
	last = list_last_entry(&net_namespace_list, काष्ठा net, list);
	up_ग_लिखो(&net_rwsem);

	llist_क्रम_each_entry(net, net_समाप्त_list, cleanup_list) अणु
		unhash_nsid(net, last);
		list_add_tail(&net->निकास_list, &net_निकास_list);
	पूर्ण

	/* Run all of the network namespace pre_निकास methods */
	list_क्रम_each_entry_reverse(ops, &pernet_list, list)
		ops_pre_निकास_list(ops, &net_निकास_list);

	/*
	 * Another CPU might be rcu-iterating the list, रुको क्रम it.
	 * This needs to be beक्रमe calling the निकास() notअगरiers, so
	 * the rcu_barrier() below isn't sufficient alone.
	 * Also the pre_निकास() and निकास() methods need this barrier.
	 */
	synchronize_rcu();

	/* Run all of the network namespace निकास methods */
	list_क्रम_each_entry_reverse(ops, &pernet_list, list)
		ops_निकास_list(ops, &net_निकास_list);

	/* Free the net generic variables */
	list_क्रम_each_entry_reverse(ops, &pernet_list, list)
		ops_मुक्त_list(ops, &net_निकास_list);

	up_पढ़ो(&pernet_ops_rwsem);

	/* Ensure there are no outstanding rcu callbacks using this
	 * network namespace.
	 */
	rcu_barrier();

	/* Finally it is safe to मुक्त my network namespace काष्ठाure */
	list_क्रम_each_entry_safe(net, पंचांगp, &net_निकास_list, निकास_list) अणु
		list_del_init(&net->निकास_list);
		dec_net_namespaces(net->ucounts);
		key_हटाओ_करोमुख्य(net->key_करोमुख्य);
		put_user_ns(net->user_ns);
		net_drop_ns(net);
	पूर्ण
पूर्ण

/**
 * net_ns_barrier - रुको until concurrent net_cleanup_work is करोne
 *
 * cleanup_net runs from work queue and will first हटाओ namespaces
 * from the global list, then run net निकास functions.
 *
 * Call this in module निकास path to make sure that all netns
 * ->निकास ops have been invoked beक्रमe the function is हटाओd.
 */
व्योम net_ns_barrier(व्योम)
अणु
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	up_ग_लिखो(&pernet_ops_rwsem);
पूर्ण
EXPORT_SYMBOL(net_ns_barrier);

अटल DECLARE_WORK(net_cleanup_work, cleanup_net);

व्योम __put_net(काष्ठा net *net)
अणु
	/* Cleanup the network namespace in process context */
	अगर (llist_add(&net->cleanup_list, &cleanup_list))
		queue_work(netns_wq, &net_cleanup_work);
पूर्ण
EXPORT_SYMBOL_GPL(__put_net);

/**
 * get_net_ns - increment the refcount of the network namespace
 * @ns: common namespace (net)
 *
 * Returns the net's common namespace.
 */
काष्ठा ns_common *get_net_ns(काष्ठा ns_common *ns)
अणु
	वापस &get_net(container_of(ns, काष्ठा net, ns))->ns;
पूर्ण
EXPORT_SYMBOL_GPL(get_net_ns);

काष्ठा net *get_net_ns_by_fd(पूर्णांक fd)
अणु
	काष्ठा file *file;
	काष्ठा ns_common *ns;
	काष्ठा net *net;

	file = proc_ns_fget(fd);
	अगर (IS_ERR(file))
		वापस ERR_CAST(file);

	ns = get_proc_ns(file_inode(file));
	अगर (ns->ops == &netns_operations)
		net = get_net(container_of(ns, काष्ठा net, ns));
	अन्यथा
		net = ERR_PTR(-EINVAL);

	fput(file);
	वापस net;
पूर्ण
EXPORT_SYMBOL_GPL(get_net_ns_by_fd);
#पूर्ण_अगर

काष्ठा net *get_net_ns_by_pid(pid_t pid)
अणु
	काष्ठा task_काष्ठा *tsk;
	काष्ठा net *net;

	/* Lookup the network namespace */
	net = ERR_PTR(-ESRCH);
	rcu_पढ़ो_lock();
	tsk = find_task_by_vpid(pid);
	अगर (tsk) अणु
		काष्ठा nsproxy *nsproxy;
		task_lock(tsk);
		nsproxy = tsk->nsproxy;
		अगर (nsproxy)
			net = get_net(nsproxy->net_ns);
		task_unlock(tsk);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस net;
पूर्ण
EXPORT_SYMBOL_GPL(get_net_ns_by_pid);

अटल __net_init पूर्णांक net_ns_net_init(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NET_NS
	net->ns.ops = &netns_operations;
#पूर्ण_अगर
	वापस ns_alloc_inum(&net->ns);
पूर्ण

अटल __net_निकास व्योम net_ns_net_निकास(काष्ठा net *net)
अणु
	ns_मुक्त_inum(&net->ns);
पूर्ण

अटल काष्ठा pernet_operations __net_initdata net_ns_ops = अणु
	.init = net_ns_net_init,
	.निकास = net_ns_net_निकास,
पूर्ण;

अटल स्थिर काष्ठा nla_policy rtnl_net_policy[NETNSA_MAX + 1] = अणु
	[NETNSA_NONE]		= अणु .type = NLA_UNSPEC पूर्ण,
	[NETNSA_NSID]		= अणु .type = NLA_S32 पूर्ण,
	[NETNSA_PID]		= अणु .type = NLA_U32 पूर्ण,
	[NETNSA_FD]		= अणु .type = NLA_U32 पूर्ण,
	[NETNSA_TARGET_NSID]	= अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल पूर्णांक rtnl_net_newid(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tb[NETNSA_MAX + 1];
	काष्ठा nlattr *nla;
	काष्ठा net *peer;
	पूर्णांक nsid, err;

	err = nlmsg_parse_deprecated(nlh, माप(काष्ठा rtgenmsg), tb,
				     NETNSA_MAX, rtnl_net_policy, extack);
	अगर (err < 0)
		वापस err;
	अगर (!tb[NETNSA_NSID]) अणु
		NL_SET_ERR_MSG(extack, "nsid is missing");
		वापस -EINVAL;
	पूर्ण
	nsid = nla_get_s32(tb[NETNSA_NSID]);

	अगर (tb[NETNSA_PID]) अणु
		peer = get_net_ns_by_pid(nla_get_u32(tb[NETNSA_PID]));
		nla = tb[NETNSA_PID];
	पूर्ण अन्यथा अगर (tb[NETNSA_FD]) अणु
		peer = get_net_ns_by_fd(nla_get_u32(tb[NETNSA_FD]));
		nla = tb[NETNSA_FD];
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG(extack, "Peer netns reference is missing");
		वापस -EINVAL;
	पूर्ण
	अगर (IS_ERR(peer)) अणु
		NL_SET_BAD_ATTR(extack, nla);
		NL_SET_ERR_MSG(extack, "Peer netns reference is invalid");
		वापस PTR_ERR(peer);
	पूर्ण

	spin_lock_bh(&net->nsid_lock);
	अगर (__peernet2id(net, peer) >= 0) अणु
		spin_unlock_bh(&net->nsid_lock);
		err = -EEXIST;
		NL_SET_BAD_ATTR(extack, nla);
		NL_SET_ERR_MSG(extack,
			       "Peer netns already has a nsid assigned");
		जाओ out;
	पूर्ण

	err = alloc_netid(net, peer, nsid);
	spin_unlock_bh(&net->nsid_lock);
	अगर (err >= 0) अणु
		rtnl_net_notअगरyid(net, RTM_NEWNSID, err, NETLINK_CB(skb).portid,
				  nlh, GFP_KERNEL);
		err = 0;
	पूर्ण अन्यथा अगर (err == -ENOSPC && nsid >= 0) अणु
		err = -EEXIST;
		NL_SET_BAD_ATTR(extack, tb[NETNSA_NSID]);
		NL_SET_ERR_MSG(extack, "The specified nsid is already used");
	पूर्ण
out:
	put_net(peer);
	वापस err;
पूर्ण

अटल पूर्णांक rtnl_net_get_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा rtgenmsg))
	       + nla_total_size(माप(s32)) /* NETNSA_NSID */
	       + nla_total_size(माप(s32)) /* NETNSA_CURRENT_NSID */
	       ;
पूर्ण

काष्ठा net_fill_args अणु
	u32 portid;
	u32 seq;
	पूर्णांक flags;
	पूर्णांक cmd;
	पूर्णांक nsid;
	bool add_ref;
	पूर्णांक ref_nsid;
पूर्ण;

अटल पूर्णांक rtnl_net_fill(काष्ठा sk_buff *skb, काष्ठा net_fill_args *args)
अणु
	काष्ठा nlmsghdr *nlh;
	काष्ठा rtgenmsg *rth;

	nlh = nlmsg_put(skb, args->portid, args->seq, args->cmd, माप(*rth),
			args->flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	rth = nlmsg_data(nlh);
	rth->rtgen_family = AF_UNSPEC;

	अगर (nla_put_s32(skb, NETNSA_NSID, args->nsid))
		जाओ nla_put_failure;

	अगर (args->add_ref &&
	    nla_put_s32(skb, NETNSA_CURRENT_NSID, args->ref_nsid))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक rtnl_net_valid_getid_req(काष्ठा sk_buff *skb,
				    स्थिर काष्ठा nlmsghdr *nlh,
				    काष्ठा nlattr **tb,
				    काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i, err;

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(काष्ठा rtgenmsg),
					      tb, NETNSA_MAX, rtnl_net_policy,
					      extack);

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा rtgenmsg), tb,
					    NETNSA_MAX, rtnl_net_policy,
					    extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= NETNSA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल NETNSA_PID:
		हाल NETNSA_FD:
		हाल NETNSA_NSID:
		हाल NETNSA_TARGET_NSID:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in peer netns getid request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_net_getid(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा nlattr *tb[NETNSA_MAX + 1];
	काष्ठा net_fill_args fillargs = अणु
		.portid = NETLINK_CB(skb).portid,
		.seq = nlh->nlmsg_seq,
		.cmd = RTM_NEWNSID,
	पूर्ण;
	काष्ठा net *peer, *target = net;
	काष्ठा nlattr *nla;
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	err = rtnl_net_valid_getid_req(skb, nlh, tb, extack);
	अगर (err < 0)
		वापस err;
	अगर (tb[NETNSA_PID]) अणु
		peer = get_net_ns_by_pid(nla_get_u32(tb[NETNSA_PID]));
		nla = tb[NETNSA_PID];
	पूर्ण अन्यथा अगर (tb[NETNSA_FD]) अणु
		peer = get_net_ns_by_fd(nla_get_u32(tb[NETNSA_FD]));
		nla = tb[NETNSA_FD];
	पूर्ण अन्यथा अगर (tb[NETNSA_NSID]) अणु
		peer = get_net_ns_by_id(net, nla_get_s32(tb[NETNSA_NSID]));
		अगर (!peer)
			peer = ERR_PTR(-ENOENT);
		nla = tb[NETNSA_NSID];
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG(extack, "Peer netns reference is missing");
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(peer)) अणु
		NL_SET_BAD_ATTR(extack, nla);
		NL_SET_ERR_MSG(extack, "Peer netns reference is invalid");
		वापस PTR_ERR(peer);
	पूर्ण

	अगर (tb[NETNSA_TARGET_NSID]) अणु
		पूर्णांक id = nla_get_s32(tb[NETNSA_TARGET_NSID]);

		target = rtnl_get_net_ns_capable(NETLINK_CB(skb).sk, id);
		अगर (IS_ERR(target)) अणु
			NL_SET_BAD_ATTR(extack, tb[NETNSA_TARGET_NSID]);
			NL_SET_ERR_MSG(extack,
				       "Target netns reference is invalid");
			err = PTR_ERR(target);
			जाओ out;
		पूर्ण
		fillargs.add_ref = true;
		fillargs.ref_nsid = peernet2id(net, peer);
	पूर्ण

	msg = nlmsg_new(rtnl_net_get_size(), GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	fillargs.nsid = peernet2id(target, peer);
	err = rtnl_net_fill(msg, &fillargs);
	अगर (err < 0)
		जाओ err_out;

	err = rtnl_unicast(msg, net, NETLINK_CB(skb).portid);
	जाओ out;

err_out:
	nlmsg_मुक्त(msg);
out:
	अगर (fillargs.add_ref)
		put_net(target);
	put_net(peer);
	वापस err;
पूर्ण

काष्ठा rtnl_net_dump_cb अणु
	काष्ठा net *tgt_net;
	काष्ठा net *ref_net;
	काष्ठा sk_buff *skb;
	काष्ठा net_fill_args fillargs;
	पूर्णांक idx;
	पूर्णांक s_idx;
पूर्ण;

/* Runs in RCU-critical section. */
अटल पूर्णांक rtnl_net_dumpid_one(पूर्णांक id, व्योम *peer, व्योम *data)
अणु
	काष्ठा rtnl_net_dump_cb *net_cb = (काष्ठा rtnl_net_dump_cb *)data;
	पूर्णांक ret;

	अगर (net_cb->idx < net_cb->s_idx)
		जाओ cont;

	net_cb->fillargs.nsid = id;
	अगर (net_cb->fillargs.add_ref)
		net_cb->fillargs.ref_nsid = __peernet2id(net_cb->ref_net, peer);
	ret = rtnl_net_fill(net_cb->skb, &net_cb->fillargs);
	अगर (ret < 0)
		वापस ret;

cont:
	net_cb->idx++;
	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_valid_dump_net_req(स्थिर काष्ठा nlmsghdr *nlh, काष्ठा sock *sk,
				   काष्ठा rtnl_net_dump_cb *net_cb,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_ext_ack *extack = cb->extack;
	काष्ठा nlattr *tb[NETNSA_MAX + 1];
	पूर्णांक err, i;

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा rtgenmsg), tb,
					    NETNSA_MAX, rtnl_net_policy,
					    extack);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= NETNSA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		अगर (i == NETNSA_TARGET_NSID) अणु
			काष्ठा net *net;

			net = rtnl_get_net_ns_capable(sk, nla_get_s32(tb[i]));
			अगर (IS_ERR(net)) अणु
				NL_SET_BAD_ATTR(extack, tb[i]);
				NL_SET_ERR_MSG(extack,
					       "Invalid target network namespace id");
				वापस PTR_ERR(net);
			पूर्ण
			net_cb->fillargs.add_ref = true;
			net_cb->ref_net = net_cb->tgt_net;
			net_cb->tgt_net = net;
		पूर्ण अन्यथा अणु
			NL_SET_BAD_ATTR(extack, tb[i]);
			NL_SET_ERR_MSG(extack,
				       "Unsupported attribute in dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtnl_net_dumpid(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा rtnl_net_dump_cb net_cb = अणु
		.tgt_net = sock_net(skb->sk),
		.skb = skb,
		.fillargs = अणु
			.portid = NETLINK_CB(cb->skb).portid,
			.seq = cb->nlh->nlmsg_seq,
			.flags = NLM_F_MULTI,
			.cmd = RTM_NEWNSID,
		पूर्ण,
		.idx = 0,
		.s_idx = cb->args[0],
	पूर्ण;
	पूर्णांक err = 0;

	अगर (cb->strict_check) अणु
		err = rtnl_valid_dump_net_req(cb->nlh, skb->sk, &net_cb, cb);
		अगर (err < 0)
			जाओ end;
	पूर्ण

	rcu_पढ़ो_lock();
	idr_क्रम_each(&net_cb.tgt_net->netns_ids, rtnl_net_dumpid_one, &net_cb);
	rcu_पढ़ो_unlock();

	cb->args[0] = net_cb.idx;
end:
	अगर (net_cb.fillargs.add_ref)
		put_net(net_cb.tgt_net);
	वापस err < 0 ? err : skb->len;
पूर्ण

अटल व्योम rtnl_net_notअगरyid(काष्ठा net *net, पूर्णांक cmd, पूर्णांक id, u32 portid,
			      काष्ठा nlmsghdr *nlh, gfp_t gfp)
अणु
	काष्ठा net_fill_args fillargs = अणु
		.portid = portid,
		.seq = nlh ? nlh->nlmsg_seq : 0,
		.cmd = cmd,
		.nsid = id,
	पूर्ण;
	काष्ठा sk_buff *msg;
	पूर्णांक err = -ENOMEM;

	msg = nlmsg_new(rtnl_net_get_size(), gfp);
	अगर (!msg)
		जाओ out;

	err = rtnl_net_fill(msg, &fillargs);
	अगर (err < 0)
		जाओ err_out;

	rtnl_notअगरy(msg, net, portid, RTNLGRP_NSID, nlh, gfp);
	वापस;

err_out:
	nlmsg_मुक्त(msg);
out:
	rtnl_set_sk_err(net, RTNLGRP_NSID, err);
पूर्ण

अटल पूर्णांक __init net_ns_init(व्योम)
अणु
	काष्ठा net_generic *ng;

#अगर_घोषित CONFIG_NET_NS
	net_cachep = kmem_cache_create("net_namespace", माप(काष्ठा net),
					SMP_CACHE_BYTES,
					SLAB_PANIC|SLAB_ACCOUNT, शून्य);

	/* Create workqueue क्रम cleanup */
	netns_wq = create_singlethपढ़ो_workqueue("netns");
	अगर (!netns_wq)
		panic("Could not create netns workq");
#पूर्ण_अगर

	ng = net_alloc_generic();
	अगर (!ng)
		panic("Could not allocate generic netns");

	rcu_assign_poपूर्णांकer(init_net.gen, ng);

	करोwn_ग_लिखो(&pernet_ops_rwsem);
	अगर (setup_net(&init_net, &init_user_ns))
		panic("Could not setup the initial network namespace");

	init_net_initialized = true;
	up_ग_लिखो(&pernet_ops_rwsem);

	अगर (रेजिस्टर_pernet_subsys(&net_ns_ops))
		panic("Could not register network namespace subsystems");

	rtnl_रेजिस्टर(PF_UNSPEC, RTM_NEWNSID, rtnl_net_newid, शून्य,
		      RTNL_FLAG_DOIT_UNLOCKED);
	rtnl_रेजिस्टर(PF_UNSPEC, RTM_GETNSID, rtnl_net_getid, rtnl_net_dumpid,
		      RTNL_FLAG_DOIT_UNLOCKED);

	वापस 0;
पूर्ण

pure_initcall(net_ns_init);

#अगर_घोषित CONFIG_NET_NS
अटल पूर्णांक __रेजिस्टर_pernet_operations(काष्ठा list_head *list,
					काष्ठा pernet_operations *ops)
अणु
	काष्ठा net *net;
	पूर्णांक error;
	LIST_HEAD(net_निकास_list);

	list_add_tail(&ops->list, list);
	अगर (ops->init || (ops->id && ops->size)) अणु
		/* We held ग_लिखो locked pernet_ops_rwsem, and parallel
		 * setup_net() and cleanup_net() are not possible.
		 */
		क्रम_each_net(net) अणु
			error = ops_init(ops, net);
			अगर (error)
				जाओ out_unकरो;
			list_add_tail(&net->निकास_list, &net_निकास_list);
		पूर्ण
	पूर्ण
	वापस 0;

out_unकरो:
	/* If I have an error cleanup all namespaces I initialized */
	list_del(&ops->list);
	ops_pre_निकास_list(ops, &net_निकास_list);
	synchronize_rcu();
	ops_निकास_list(ops, &net_निकास_list);
	ops_मुक्त_list(ops, &net_निकास_list);
	वापस error;
पूर्ण

अटल व्योम __unरेजिस्टर_pernet_operations(काष्ठा pernet_operations *ops)
अणु
	काष्ठा net *net;
	LIST_HEAD(net_निकास_list);

	list_del(&ops->list);
	/* See comment in __रेजिस्टर_pernet_operations() */
	क्रम_each_net(net)
		list_add_tail(&net->निकास_list, &net_निकास_list);
	ops_pre_निकास_list(ops, &net_निकास_list);
	synchronize_rcu();
	ops_निकास_list(ops, &net_निकास_list);
	ops_मुक्त_list(ops, &net_निकास_list);
पूर्ण

#अन्यथा

अटल पूर्णांक __रेजिस्टर_pernet_operations(काष्ठा list_head *list,
					काष्ठा pernet_operations *ops)
अणु
	अगर (!init_net_initialized) अणु
		list_add_tail(&ops->list, list);
		वापस 0;
	पूर्ण

	वापस ops_init(ops, &init_net);
पूर्ण

अटल व्योम __unरेजिस्टर_pernet_operations(काष्ठा pernet_operations *ops)
अणु
	अगर (!init_net_initialized) अणु
		list_del(&ops->list);
	पूर्ण अन्यथा अणु
		LIST_HEAD(net_निकास_list);
		list_add(&init_net.निकास_list, &net_निकास_list);
		ops_pre_निकास_list(ops, &net_निकास_list);
		synchronize_rcu();
		ops_निकास_list(ops, &net_निकास_list);
		ops_मुक्त_list(ops, &net_निकास_list);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_NET_NS */

अटल DEFINE_IDA(net_generic_ids);

अटल पूर्णांक रेजिस्टर_pernet_operations(काष्ठा list_head *list,
				      काष्ठा pernet_operations *ops)
अणु
	पूर्णांक error;

	अगर (ops->id) अणु
		error = ida_alloc_min(&net_generic_ids, MIN_PERNET_OPS_ID,
				GFP_KERNEL);
		अगर (error < 0)
			वापस error;
		*ops->id = error;
		max_gen_ptrs = max(max_gen_ptrs, *ops->id + 1);
	पूर्ण
	error = __रेजिस्टर_pernet_operations(list, ops);
	अगर (error) अणु
		rcu_barrier();
		अगर (ops->id)
			ida_मुक्त(&net_generic_ids, *ops->id);
	पूर्ण

	वापस error;
पूर्ण

अटल व्योम unरेजिस्टर_pernet_operations(काष्ठा pernet_operations *ops)
अणु
	__unरेजिस्टर_pernet_operations(ops);
	rcu_barrier();
	अगर (ops->id)
		ida_मुक्त(&net_generic_ids, *ops->id);
पूर्ण

/**
 *      रेजिस्टर_pernet_subsys - रेजिस्टर a network namespace subप्रणाली
 *	@ops:  pernet operations काष्ठाure क्रम the subप्रणाली
 *
 *	Register a subप्रणाली which has init and निकास functions
 *	that are called when network namespaces are created and
 *	destroyed respectively.
 *
 *	When रेजिस्टरed all network namespace init functions are
 *	called क्रम every existing network namespace.  Allowing kernel
 *	modules to have a race मुक्त view of the set of network namespaces.
 *
 *	When a new network namespace is created all of the init
 *	methods are called in the order in which they were रेजिस्टरed.
 *
 *	When a network namespace is destroyed all of the निकास methods
 *	are called in the reverse of the order with which they were
 *	रेजिस्टरed.
 */
पूर्णांक रेजिस्टर_pernet_subsys(काष्ठा pernet_operations *ops)
अणु
	पूर्णांक error;
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	error =  रेजिस्टर_pernet_operations(first_device, ops);
	up_ग_लिखो(&pernet_ops_rwsem);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_pernet_subsys);

/**
 *      unरेजिस्टर_pernet_subsys - unरेजिस्टर a network namespace subप्रणाली
 *	@ops: pernet operations काष्ठाure to manipulate
 *
 *	Remove the pernet operations काष्ठाure from the list to be
 *	used when network namespaces are created or destroyed.  In
 *	addition run the निकास method क्रम all existing network
 *	namespaces.
 */
व्योम unरेजिस्टर_pernet_subsys(काष्ठा pernet_operations *ops)
अणु
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	unरेजिस्टर_pernet_operations(ops);
	up_ग_लिखो(&pernet_ops_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_pernet_subsys);

/**
 *      रेजिस्टर_pernet_device - रेजिस्टर a network namespace device
 *	@ops:  pernet operations काष्ठाure क्रम the subप्रणाली
 *
 *	Register a device which has init and निकास functions
 *	that are called when network namespaces are created and
 *	destroyed respectively.
 *
 *	When रेजिस्टरed all network namespace init functions are
 *	called क्रम every existing network namespace.  Allowing kernel
 *	modules to have a race मुक्त view of the set of network namespaces.
 *
 *	When a new network namespace is created all of the init
 *	methods are called in the order in which they were रेजिस्टरed.
 *
 *	When a network namespace is destroyed all of the निकास methods
 *	are called in the reverse of the order with which they were
 *	रेजिस्टरed.
 */
पूर्णांक रेजिस्टर_pernet_device(काष्ठा pernet_operations *ops)
अणु
	पूर्णांक error;
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	error = रेजिस्टर_pernet_operations(&pernet_list, ops);
	अगर (!error && (first_device == &pernet_list))
		first_device = &ops->list;
	up_ग_लिखो(&pernet_ops_rwsem);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_pernet_device);

/**
 *      unरेजिस्टर_pernet_device - unरेजिस्टर a network namespace netdevice
 *	@ops: pernet operations काष्ठाure to manipulate
 *
 *	Remove the pernet operations काष्ठाure from the list to be
 *	used when network namespaces are created or destroyed.  In
 *	addition run the निकास method क्रम all existing network
 *	namespaces.
 */
व्योम unरेजिस्टर_pernet_device(काष्ठा pernet_operations *ops)
अणु
	करोwn_ग_लिखो(&pernet_ops_rwsem);
	अगर (&ops->list == first_device)
		first_device = first_device->next;
	unरेजिस्टर_pernet_operations(ops);
	up_ग_लिखो(&pernet_ops_rwsem);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_pernet_device);

#अगर_घोषित CONFIG_NET_NS
अटल काष्ठा ns_common *netns_get(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा net *net = शून्य;
	काष्ठा nsproxy *nsproxy;

	task_lock(task);
	nsproxy = task->nsproxy;
	अगर (nsproxy)
		net = get_net(nsproxy->net_ns);
	task_unlock(task);

	वापस net ? &net->ns : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा net *to_net_ns(काष्ठा ns_common *ns)
अणु
	वापस container_of(ns, काष्ठा net, ns);
पूर्ण

अटल व्योम netns_put(काष्ठा ns_common *ns)
अणु
	put_net(to_net_ns(ns));
पूर्ण

अटल पूर्णांक netns_install(काष्ठा nsset *nsset, काष्ठा ns_common *ns)
अणु
	काष्ठा nsproxy *nsproxy = nsset->nsproxy;
	काष्ठा net *net = to_net_ns(ns);

	अगर (!ns_capable(net->user_ns, CAP_SYS_ADMIN) ||
	    !ns_capable(nsset->cred->user_ns, CAP_SYS_ADMIN))
		वापस -EPERM;

	put_net(nsproxy->net_ns);
	nsproxy->net_ns = get_net(net);
	वापस 0;
पूर्ण

अटल काष्ठा user_namespace *netns_owner(काष्ठा ns_common *ns)
अणु
	वापस to_net_ns(ns)->user_ns;
पूर्ण

स्थिर काष्ठा proc_ns_operations netns_operations = अणु
	.name		= "net",
	.type		= CLONE_NEWNET,
	.get		= netns_get,
	.put		= netns_put,
	.install	= netns_install,
	.owner		= netns_owner,
पूर्ण;
#पूर्ण_अगर
