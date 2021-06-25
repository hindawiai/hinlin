<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NETLINK      Kernel-user communication protocol.
 *
 * 		Authors:	Alan Cox <alan@lxorguk.ukuu.org.uk>
 * 				Alexey Kuznetsov <kuznet@ms2.inr.ac.ru>
 * 				Patrick McHardy <kaber@trash.net>
 *
 * Tue Jun 26 14:36:48 MEST 2001 Herbert "herp" Rosmanith
 *                               added netlink_proto_निकास
 * Tue Jan 22 18:32:44 BRST 2002 Arnalकरो C. de Melo <acme@conectiva.com.br>
 * 				 use nlk_sk, as sk->protinfo is on a diet 8)
 * Fri Jul 22 19:51:12 MEST 2005 Harald Welte <laक्रमge@gnumonks.org>
 * 				 - inc module use count of module that owns
 * 				   the kernel socket in हाल userspace खोलोs
 * 				   socket of same protocol
 * 				 - हटाओ all module support, since netlink is
 * 				   mandatory अगर CONFIG_NET=y these days
 */

#समावेश <linux/module.h>

#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/socket.h>
#समावेश <linux/un.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/termios.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/security.h>
#समावेश <linux/jhash.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mm.h>
#समावेश <linux/types.h>
#समावेश <linux/audit.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/rhashtable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/hash.h>
#समावेश <linux/genetlink.h>
#समावेश <linux/net_namespace.h>
#समावेश <linux/nospec.h>
#समावेश <linux/btf_ids.h>

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/sock.h>
#समावेश <net/scm.h>
#समावेश <net/netlink.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/netlink.h>

#समावेश "af_netlink.h"

काष्ठा listeners अणु
	काष्ठा rcu_head		rcu;
	अचिन्हित दीर्घ		masks[];
पूर्ण;

/* state bits */
#घोषणा NETLINK_S_CONGESTED		0x0

अटल अंतरभूत पूर्णांक netlink_is_kernel(काष्ठा sock *sk)
अणु
	वापस nlk_sk(sk)->flags & NETLINK_F_KERNEL_SOCKET;
पूर्ण

काष्ठा netlink_table *nl_table __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(nl_table);

अटल DECLARE_WAIT_QUEUE_HEAD(nl_table_रुको);

अटल काष्ठा lock_class_key nlk_cb_mutex_keys[MAX_LINKS];

अटल स्थिर अक्षर *स्थिर nlk_cb_mutex_key_strings[MAX_LINKS + 1] = अणु
	"nlk_cb_mutex-ROUTE",
	"nlk_cb_mutex-1",
	"nlk_cb_mutex-USERSOCK",
	"nlk_cb_mutex-FIREWALL",
	"nlk_cb_mutex-SOCK_DIAG",
	"nlk_cb_mutex-NFLOG",
	"nlk_cb_mutex-XFRM",
	"nlk_cb_mutex-SELINUX",
	"nlk_cb_mutex-ISCSI",
	"nlk_cb_mutex-AUDIT",
	"nlk_cb_mutex-FIB_LOOKUP",
	"nlk_cb_mutex-CONNECTOR",
	"nlk_cb_mutex-NETFILTER",
	"nlk_cb_mutex-IP6_FW",
	"nlk_cb_mutex-DNRTMSG",
	"nlk_cb_mutex-KOBJECT_UEVENT",
	"nlk_cb_mutex-GENERIC",
	"nlk_cb_mutex-17",
	"nlk_cb_mutex-SCSITRANSPORT",
	"nlk_cb_mutex-ECRYPTFS",
	"nlk_cb_mutex-RDMA",
	"nlk_cb_mutex-CRYPTO",
	"nlk_cb_mutex-SMC",
	"nlk_cb_mutex-23",
	"nlk_cb_mutex-24",
	"nlk_cb_mutex-25",
	"nlk_cb_mutex-26",
	"nlk_cb_mutex-27",
	"nlk_cb_mutex-28",
	"nlk_cb_mutex-29",
	"nlk_cb_mutex-30",
	"nlk_cb_mutex-31",
	"nlk_cb_mutex-MAX_LINKS"
पूर्ण;

अटल पूर्णांक netlink_dump(काष्ठा sock *sk);

/* nl_table locking explained:
 * Lookup and traversal are रक्षित with an RCU पढ़ो-side lock. Insertion
 * and removal are रक्षित with per bucket lock जबतक using RCU list
 * modअगरication primitives and may run in parallel to RCU रक्षित lookups.
 * Deकाष्ठाion of the Netlink socket may only occur *after* nl_table_lock has
 * been acquired * either during or after the socket has been हटाओd from
 * the list and after an RCU grace period.
 */
DEFINE_RWLOCK(nl_table_lock);
EXPORT_SYMBOL_GPL(nl_table_lock);
अटल atomic_t nl_table_users = ATOMIC_INIT(0);

#घोषणा nl_deref_रक्षित(X) rcu_dereference_रक्षित(X, lockdep_is_held(&nl_table_lock));

अटल BLOCKING_NOTIFIER_HEAD(netlink_chain);


अटल स्थिर काष्ठा rhashtable_params netlink_rhashtable_params;

व्योम करो_trace_netlink_extack(स्थिर अक्षर *msg)
अणु
	trace_netlink_extack(msg);
पूर्ण
EXPORT_SYMBOL(करो_trace_netlink_extack);

अटल अंतरभूत u32 netlink_group_mask(u32 group)
अणु
	वापस group ? 1 << (group - 1) : 0;
पूर्ण

अटल काष्ठा sk_buff *netlink_to_full_skb(स्थिर काष्ठा sk_buff *skb,
					   gfp_t gfp_mask)
अणु
	अचिन्हित पूर्णांक len = skb_end_offset(skb);
	काष्ठा sk_buff *new;

	new = alloc_skb(len, gfp_mask);
	अगर (new == शून्य)
		वापस शून्य;

	NETLINK_CB(new).portid = NETLINK_CB(skb).portid;
	NETLINK_CB(new).dst_group = NETLINK_CB(skb).dst_group;
	NETLINK_CB(new).creds = NETLINK_CB(skb).creds;

	skb_put_data(new, skb->data, len);
	वापस new;
पूर्ण

अटल अचिन्हित पूर्णांक netlink_tap_net_id;

काष्ठा netlink_tap_net अणु
	काष्ठा list_head netlink_tap_all;
	काष्ठा mutex netlink_tap_lock;
पूर्ण;

पूर्णांक netlink_add_tap(काष्ठा netlink_tap *nt)
अणु
	काष्ठा net *net = dev_net(nt->dev);
	काष्ठा netlink_tap_net *nn = net_generic(net, netlink_tap_net_id);

	अगर (unlikely(nt->dev->type != ARPHRD_NETLINK))
		वापस -EINVAL;

	mutex_lock(&nn->netlink_tap_lock);
	list_add_rcu(&nt->list, &nn->netlink_tap_all);
	mutex_unlock(&nn->netlink_tap_lock);

	__module_get(nt->module);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(netlink_add_tap);

अटल पूर्णांक __netlink_हटाओ_tap(काष्ठा netlink_tap *nt)
अणु
	काष्ठा net *net = dev_net(nt->dev);
	काष्ठा netlink_tap_net *nn = net_generic(net, netlink_tap_net_id);
	bool found = false;
	काष्ठा netlink_tap *पंचांगp;

	mutex_lock(&nn->netlink_tap_lock);

	list_क्रम_each_entry(पंचांगp, &nn->netlink_tap_all, list) अणु
		अगर (nt == पंचांगp) अणु
			list_del_rcu(&nt->list);
			found = true;
			जाओ out;
		पूर्ण
	पूर्ण

	pr_warn("__netlink_remove_tap: %p not found\n", nt);
out:
	mutex_unlock(&nn->netlink_tap_lock);

	अगर (found)
		module_put(nt->module);

	वापस found ? 0 : -ENODEV;
पूर्ण

पूर्णांक netlink_हटाओ_tap(काष्ठा netlink_tap *nt)
अणु
	पूर्णांक ret;

	ret = __netlink_हटाओ_tap(nt);
	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(netlink_हटाओ_tap);

अटल __net_init पूर्णांक netlink_tap_init_net(काष्ठा net *net)
अणु
	काष्ठा netlink_tap_net *nn = net_generic(net, netlink_tap_net_id);

	INIT_LIST_HEAD(&nn->netlink_tap_all);
	mutex_init(&nn->netlink_tap_lock);
	वापस 0;
पूर्ण

अटल काष्ठा pernet_operations netlink_tap_net_ops = अणु
	.init = netlink_tap_init_net,
	.id   = &netlink_tap_net_id,
	.size = माप(काष्ठा netlink_tap_net),
पूर्ण;

अटल bool netlink_filter_tap(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = skb->sk;

	/* We take the more conservative approach and
	 * whitelist socket protocols that may pass.
	 */
	चयन (sk->sk_protocol) अणु
	हाल NETLINK_ROUTE:
	हाल NETLINK_USERSOCK:
	हाल NETLINK_SOCK_DIAG:
	हाल NETLINK_NFLOG:
	हाल NETLINK_XFRM:
	हाल NETLINK_FIB_LOOKUP:
	हाल NETLINK_NETFILTER:
	हाल NETLINK_GENERIC:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक __netlink_deliver_tap_skb(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *nskb;
	काष्ठा sock *sk = skb->sk;
	पूर्णांक ret = -ENOMEM;

	अगर (!net_eq(dev_net(dev), sock_net(sk)))
		वापस 0;

	dev_hold(dev);

	अगर (is_vदो_स्मृति_addr(skb->head))
		nskb = netlink_to_full_skb(skb, GFP_ATOMIC);
	अन्यथा
		nskb = skb_clone(skb, GFP_ATOMIC);
	अगर (nskb) अणु
		nskb->dev = dev;
		nskb->protocol = htons((u16) sk->sk_protocol);
		nskb->pkt_type = netlink_is_kernel(sk) ?
				 PACKET_KERNEL : PACKET_USER;
		skb_reset_network_header(nskb);
		ret = dev_queue_xmit(nskb);
		अगर (unlikely(ret > 0))
			ret = net_xmit_त्रुटि_सं(ret);
	पूर्ण

	dev_put(dev);
	वापस ret;
पूर्ण

अटल व्योम __netlink_deliver_tap(काष्ठा sk_buff *skb, काष्ठा netlink_tap_net *nn)
अणु
	पूर्णांक ret;
	काष्ठा netlink_tap *पंचांगp;

	अगर (!netlink_filter_tap(skb))
		वापस;

	list_क्रम_each_entry_rcu(पंचांगp, &nn->netlink_tap_all, list) अणु
		ret = __netlink_deliver_tap_skb(skb, पंचांगp->dev);
		अगर (unlikely(ret))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम netlink_deliver_tap(काष्ठा net *net, काष्ठा sk_buff *skb)
अणु
	काष्ठा netlink_tap_net *nn = net_generic(net, netlink_tap_net_id);

	rcu_पढ़ो_lock();

	अगर (unlikely(!list_empty(&nn->netlink_tap_all)))
		__netlink_deliver_tap(skb, nn);

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम netlink_deliver_tap_kernel(काष्ठा sock *dst, काष्ठा sock *src,
				       काष्ठा sk_buff *skb)
अणु
	अगर (!(netlink_is_kernel(dst) && netlink_is_kernel(src)))
		netlink_deliver_tap(sock_net(dst), skb);
पूर्ण

अटल व्योम netlink_overrun(काष्ठा sock *sk)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	अगर (!(nlk->flags & NETLINK_F_RECV_NO_ENOBUFS)) अणु
		अगर (!test_and_set_bit(NETLINK_S_CONGESTED,
				      &nlk_sk(sk)->state)) अणु
			sk->sk_err = ENOBUFS;
			sk->sk_error_report(sk);
		पूर्ण
	पूर्ण
	atomic_inc(&sk->sk_drops);
पूर्ण

अटल व्योम netlink_rcv_wake(काष्ठा sock *sk)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	अगर (skb_queue_empty_lockless(&sk->sk_receive_queue))
		clear_bit(NETLINK_S_CONGESTED, &nlk->state);
	अगर (!test_bit(NETLINK_S_CONGESTED, &nlk->state))
		wake_up_पूर्णांकerruptible(&nlk->रुको);
पूर्ण

अटल व्योम netlink_skb_deकाष्ठाor(काष्ठा sk_buff *skb)
अणु
	अगर (is_vदो_स्मृति_addr(skb->head)) अणु
		अगर (!skb->cloned ||
		    !atomic_dec_वापस(&(skb_shinfo(skb)->dataref)))
			vमुक्त(skb->head);

		skb->head = शून्य;
	पूर्ण
	अगर (skb->sk != शून्य)
		sock_rमुक्त(skb);
पूर्ण

अटल व्योम netlink_skb_set_owner_r(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	WARN_ON(skb->sk != शून्य);
	skb->sk = sk;
	skb->deकाष्ठाor = netlink_skb_deकाष्ठाor;
	atomic_add(skb->truesize, &sk->sk_rmem_alloc);
	sk_mem_अक्षरge(sk, skb->truesize);
पूर्ण

अटल व्योम netlink_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	अगर (nlk->cb_running) अणु
		अगर (nlk->cb.करोne)
			nlk->cb.करोne(&nlk->cb);
		module_put(nlk->cb.module);
		kमुक्त_skb(nlk->cb.skb);
	पूर्ण

	skb_queue_purge(&sk->sk_receive_queue);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		prपूर्णांकk(KERN_ERR "Freeing alive netlink socket %p\n", sk);
		वापस;
	पूर्ण

	WARN_ON(atomic_पढ़ो(&sk->sk_rmem_alloc));
	WARN_ON(refcount_पढ़ो(&sk->sk_wmem_alloc));
	WARN_ON(nlk_sk(sk)->groups);
पूर्ण

अटल व्योम netlink_sock_deकाष्ठा_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा netlink_sock *nlk = container_of(work, काष्ठा netlink_sock,
						work);

	sk_मुक्त(&nlk->sk);
पूर्ण

/* This lock without WQ_FLAG_EXCLUSIVE is good on UP and it is _very_ bad on
 * SMP. Look, when several ग_लिखोrs sleep and पढ़ोer wakes them up, all but one
 * immediately hit ग_लिखो lock and grab all the cpus. Exclusive sleep solves
 * this, _but_ remember, it adds useless work on UP machines.
 */

व्योम netlink_table_grab(व्योम)
	__acquires(nl_table_lock)
अणु
	might_sleep();

	ग_लिखो_lock_irq(&nl_table_lock);

	अगर (atomic_पढ़ो(&nl_table_users)) अणु
		DECLARE_WAITQUEUE(रुको, current);

		add_रुको_queue_exclusive(&nl_table_रुको, &रुको);
		क्रम (;;) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			अगर (atomic_पढ़ो(&nl_table_users) == 0)
				अवरोध;
			ग_लिखो_unlock_irq(&nl_table_lock);
			schedule();
			ग_लिखो_lock_irq(&nl_table_lock);
		पूर्ण

		__set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&nl_table_रुको, &रुको);
	पूर्ण
पूर्ण

व्योम netlink_table_ungrab(व्योम)
	__releases(nl_table_lock)
अणु
	ग_लिखो_unlock_irq(&nl_table_lock);
	wake_up(&nl_table_रुको);
पूर्ण

अटल अंतरभूत व्योम
netlink_lock_table(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	/* पढ़ो_lock() synchronizes us to netlink_table_grab */

	पढ़ो_lock_irqsave(&nl_table_lock, flags);
	atomic_inc(&nl_table_users);
	पढ़ो_unlock_irqrestore(&nl_table_lock, flags);
पूर्ण

अटल अंतरभूत व्योम
netlink_unlock_table(व्योम)
अणु
	अगर (atomic_dec_and_test(&nl_table_users))
		wake_up(&nl_table_रुको);
पूर्ण

काष्ठा netlink_compare_arg
अणु
	possible_net_t pnet;
	u32 portid;
पूर्ण;

/* Doing माप directly may yield 4 extra bytes on 64-bit. */
#घोषणा netlink_compare_arg_len \
	(दुरत्व(काष्ठा netlink_compare_arg, portid) + माप(u32))

अटल अंतरभूत पूर्णांक netlink_compare(काष्ठा rhashtable_compare_arg *arg,
				  स्थिर व्योम *ptr)
अणु
	स्थिर काष्ठा netlink_compare_arg *x = arg->key;
	स्थिर काष्ठा netlink_sock *nlk = ptr;

	वापस nlk->portid != x->portid ||
	       !net_eq(sock_net(&nlk->sk), पढ़ो_pnet(&x->pnet));
पूर्ण

अटल व्योम netlink_compare_arg_init(काष्ठा netlink_compare_arg *arg,
				     काष्ठा net *net, u32 portid)
अणु
	स_रखो(arg, 0, माप(*arg));
	ग_लिखो_pnet(&arg->pnet, net);
	arg->portid = portid;
पूर्ण

अटल काष्ठा sock *__netlink_lookup(काष्ठा netlink_table *table, u32 portid,
				     काष्ठा net *net)
अणु
	काष्ठा netlink_compare_arg arg;

	netlink_compare_arg_init(&arg, net, portid);
	वापस rhashtable_lookup_fast(&table->hash, &arg,
				      netlink_rhashtable_params);
पूर्ण

अटल पूर्णांक __netlink_insert(काष्ठा netlink_table *table, काष्ठा sock *sk)
अणु
	काष्ठा netlink_compare_arg arg;

	netlink_compare_arg_init(&arg, sock_net(sk), nlk_sk(sk)->portid);
	वापस rhashtable_lookup_insert_key(&table->hash, &arg,
					    &nlk_sk(sk)->node,
					    netlink_rhashtable_params);
पूर्ण

अटल काष्ठा sock *netlink_lookup(काष्ठा net *net, पूर्णांक protocol, u32 portid)
अणु
	काष्ठा netlink_table *table = &nl_table[protocol];
	काष्ठा sock *sk;

	rcu_पढ़ो_lock();
	sk = __netlink_lookup(table, portid, net);
	अगर (sk)
		sock_hold(sk);
	rcu_पढ़ो_unlock();

	वापस sk;
पूर्ण

अटल स्थिर काष्ठा proto_ops netlink_ops;

अटल व्योम
netlink_update_listeners(काष्ठा sock *sk)
अणु
	काष्ठा netlink_table *tbl = &nl_table[sk->sk_protocol];
	अचिन्हित दीर्घ mask;
	अचिन्हित पूर्णांक i;
	काष्ठा listeners *listeners;

	listeners = nl_deref_रक्षित(tbl->listeners);
	अगर (!listeners)
		वापस;

	क्रम (i = 0; i < NLGRPLONGS(tbl->groups); i++) अणु
		mask = 0;
		sk_क्रम_each_bound(sk, &tbl->mc_list) अणु
			अगर (i < NLGRPLONGS(nlk_sk(sk)->ngroups))
				mask |= nlk_sk(sk)->groups[i];
		पूर्ण
		listeners->masks[i] = mask;
	पूर्ण
	/* this function is only called with the netlink table "grabbed", which
	 * makes sure updates are visible beक्रमe bind or setsockopt वापस. */
पूर्ण

अटल पूर्णांक netlink_insert(काष्ठा sock *sk, u32 portid)
अणु
	काष्ठा netlink_table *table = &nl_table[sk->sk_protocol];
	पूर्णांक err;

	lock_sock(sk);

	err = nlk_sk(sk)->portid == portid ? 0 : -EBUSY;
	अगर (nlk_sk(sk)->bound)
		जाओ err;

	nlk_sk(sk)->portid = portid;
	sock_hold(sk);

	err = __netlink_insert(table, sk);
	अगर (err) अणु
		/* In हाल the hashtable backend वापसs with -EBUSY
		 * from here, it must not escape to the caller.
		 */
		अगर (unlikely(err == -EBUSY))
			err = -EOVERFLOW;
		अगर (err == -EEXIST)
			err = -EADDRINUSE;
		sock_put(sk);
		जाओ err;
	पूर्ण

	/* We need to ensure that the socket is hashed and visible. */
	smp_wmb();
	nlk_sk(sk)->bound = portid;

err:
	release_sock(sk);
	वापस err;
पूर्ण

अटल व्योम netlink_हटाओ(काष्ठा sock *sk)
अणु
	काष्ठा netlink_table *table;

	table = &nl_table[sk->sk_protocol];
	अगर (!rhashtable_हटाओ_fast(&table->hash, &nlk_sk(sk)->node,
				    netlink_rhashtable_params)) अणु
		WARN_ON(refcount_पढ़ो(&sk->sk_refcnt) == 1);
		__sock_put(sk);
	पूर्ण

	netlink_table_grab();
	अगर (nlk_sk(sk)->subscriptions) अणु
		__sk_del_bind_node(sk);
		netlink_update_listeners(sk);
	पूर्ण
	अगर (sk->sk_protocol == NETLINK_GENERIC)
		atomic_inc(&genl_sk_deकाष्ठाing_cnt);
	netlink_table_ungrab();
पूर्ण

अटल काष्ठा proto netlink_proto = अणु
	.name	  = "NETLINK",
	.owner	  = THIS_MODULE,
	.obj_size = माप(काष्ठा netlink_sock),
पूर्ण;

अटल पूर्णांक __netlink_create(काष्ठा net *net, काष्ठा socket *sock,
			    काष्ठा mutex *cb_mutex, पूर्णांक protocol,
			    पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा netlink_sock *nlk;

	sock->ops = &netlink_ops;

	sk = sk_alloc(net, PF_NETLINK, GFP_KERNEL, &netlink_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);

	nlk = nlk_sk(sk);
	अगर (cb_mutex) अणु
		nlk->cb_mutex = cb_mutex;
	पूर्ण अन्यथा अणु
		nlk->cb_mutex = &nlk->cb_def_mutex;
		mutex_init(nlk->cb_mutex);
		lockdep_set_class_and_name(nlk->cb_mutex,
					   nlk_cb_mutex_keys + protocol,
					   nlk_cb_mutex_key_strings[protocol]);
	पूर्ण
	init_रुकोqueue_head(&nlk->रुको);

	sk->sk_deकाष्ठा = netlink_sock_deकाष्ठा;
	sk->sk_protocol = protocol;
	वापस 0;
पूर्ण

अटल पूर्णांक netlink_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			  पूर्णांक kern)
अणु
	काष्ठा module *module = शून्य;
	काष्ठा mutex *cb_mutex;
	काष्ठा netlink_sock *nlk;
	पूर्णांक (*bind)(काष्ठा net *net, पूर्णांक group);
	व्योम (*unbind)(काष्ठा net *net, पूर्णांक group);
	पूर्णांक err = 0;

	sock->state = SS_UNCONNECTED;

	अगर (sock->type != SOCK_RAW && sock->type != SOCK_DGRAM)
		वापस -ESOCKTNOSUPPORT;

	अगर (protocol < 0 || protocol >= MAX_LINKS)
		वापस -EPROTONOSUPPORT;
	protocol = array_index_nospec(protocol, MAX_LINKS);

	netlink_lock_table();
#अगर_घोषित CONFIG_MODULES
	अगर (!nl_table[protocol].रेजिस्टरed) अणु
		netlink_unlock_table();
		request_module("net-pf-%d-proto-%d", PF_NETLINK, protocol);
		netlink_lock_table();
	पूर्ण
#पूर्ण_अगर
	अगर (nl_table[protocol].रेजिस्टरed &&
	    try_module_get(nl_table[protocol].module))
		module = nl_table[protocol].module;
	अन्यथा
		err = -EPROTONOSUPPORT;
	cb_mutex = nl_table[protocol].cb_mutex;
	bind = nl_table[protocol].bind;
	unbind = nl_table[protocol].unbind;
	netlink_unlock_table();

	अगर (err < 0)
		जाओ out;

	err = __netlink_create(net, sock, cb_mutex, protocol, kern);
	अगर (err < 0)
		जाओ out_module;

	local_bh_disable();
	sock_prot_inuse_add(net, &netlink_proto, 1);
	local_bh_enable();

	nlk = nlk_sk(sock->sk);
	nlk->module = module;
	nlk->netlink_bind = bind;
	nlk->netlink_unbind = unbind;
out:
	वापस err;

out_module:
	module_put(module);
	जाओ out;
पूर्ण

अटल व्योम deferred_put_nlk_sk(काष्ठा rcu_head *head)
अणु
	काष्ठा netlink_sock *nlk = container_of(head, काष्ठा netlink_sock, rcu);
	काष्ठा sock *sk = &nlk->sk;

	kमुक्त(nlk->groups);
	nlk->groups = शून्य;

	अगर (!refcount_dec_and_test(&sk->sk_refcnt))
		वापस;

	अगर (nlk->cb_running && nlk->cb.करोne) अणु
		INIT_WORK(&nlk->work, netlink_sock_deकाष्ठा_work);
		schedule_work(&nlk->work);
		वापस;
	पूर्ण

	sk_मुक्त(sk);
पूर्ण

अटल पूर्णांक netlink_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा netlink_sock *nlk;

	अगर (!sk)
		वापस 0;

	netlink_हटाओ(sk);
	sock_orphan(sk);
	nlk = nlk_sk(sk);

	/*
	 * OK. Socket is unlinked, any packets that arrive now
	 * will be purged.
	 */

	/* must not acquire netlink_table_lock in any way again beक्रमe unbind
	 * and notअगरying genetlink is करोne as otherwise it might deadlock
	 */
	अगर (nlk->netlink_unbind) अणु
		पूर्णांक i;

		क्रम (i = 0; i < nlk->ngroups; i++)
			अगर (test_bit(i, nlk->groups))
				nlk->netlink_unbind(sock_net(sk), i + 1);
	पूर्ण
	अगर (sk->sk_protocol == NETLINK_GENERIC &&
	    atomic_dec_वापस(&genl_sk_deकाष्ठाing_cnt) == 0)
		wake_up(&genl_sk_deकाष्ठाing_रुकोq);

	sock->sk = शून्य;
	wake_up_पूर्णांकerruptible_all(&nlk->रुको);

	skb_queue_purge(&sk->sk_ग_लिखो_queue);

	अगर (nlk->portid && nlk->bound) अणु
		काष्ठा netlink_notअगरy n = अणु
						.net = sock_net(sk),
						.protocol = sk->sk_protocol,
						.portid = nlk->portid,
					  पूर्ण;
		blocking_notअगरier_call_chain(&netlink_chain,
				NETLINK_URELEASE, &n);
	पूर्ण

	module_put(nlk->module);

	अगर (netlink_is_kernel(sk)) अणु
		netlink_table_grab();
		BUG_ON(nl_table[sk->sk_protocol].रेजिस्टरed == 0);
		अगर (--nl_table[sk->sk_protocol].रेजिस्टरed == 0) अणु
			काष्ठा listeners *old;

			old = nl_deref_रक्षित(nl_table[sk->sk_protocol].listeners);
			RCU_INIT_POINTER(nl_table[sk->sk_protocol].listeners, शून्य);
			kमुक्त_rcu(old, rcu);
			nl_table[sk->sk_protocol].module = शून्य;
			nl_table[sk->sk_protocol].bind = शून्य;
			nl_table[sk->sk_protocol].unbind = शून्य;
			nl_table[sk->sk_protocol].flags = 0;
			nl_table[sk->sk_protocol].रेजिस्टरed = 0;
		पूर्ण
		netlink_table_ungrab();
	पूर्ण

	local_bh_disable();
	sock_prot_inuse_add(sock_net(sk), &netlink_proto, -1);
	local_bh_enable();
	call_rcu(&nlk->rcu, deferred_put_nlk_sk);
	वापस 0;
पूर्ण

अटल पूर्णांक netlink_स्वतःbind(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा netlink_table *table = &nl_table[sk->sk_protocol];
	s32 portid = task_tgid_vnr(current);
	पूर्णांक err;
	s32 rover = -4096;
	bool ok;

retry:
	cond_resched();
	rcu_पढ़ो_lock();
	ok = !__netlink_lookup(table, portid, net);
	rcu_पढ़ो_unlock();
	अगर (!ok) अणु
		/* Bind collision, search negative portid values. */
		अगर (rover == -4096)
			/* rover will be in range [S32_MIN, -4097] */
			rover = S32_MIN + pअक्रमom_u32_max(-4096 - S32_MIN);
		अन्यथा अगर (rover >= -4096)
			rover = -4097;
		portid = rover--;
		जाओ retry;
	पूर्ण

	err = netlink_insert(sk, portid);
	अगर (err == -EADDRINUSE)
		जाओ retry;

	/* If 2 thपढ़ोs race to स्वतःbind, that is fine.  */
	अगर (err == -EBUSY)
		err = 0;

	वापस err;
पूर्ण

/**
 * __netlink_ns_capable - General netlink message capability test
 * @nsp: NETLINK_CB of the socket buffer holding a netlink command from userspace.
 * @user_ns: The user namespace of the capability to use
 * @cap: The capability to use
 *
 * Test to see अगर the खोलोer of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has the capability @cap in the user namespace @user_ns.
 */
bool __netlink_ns_capable(स्थिर काष्ठा netlink_skb_parms *nsp,
			काष्ठा user_namespace *user_ns, पूर्णांक cap)
अणु
	वापस ((nsp->flags & NETLINK_SKB_DST) ||
		file_ns_capable(nsp->sk->sk_socket->file, user_ns, cap)) &&
		ns_capable(user_ns, cap);
पूर्ण
EXPORT_SYMBOL(__netlink_ns_capable);

/**
 * netlink_ns_capable - General netlink message capability test
 * @skb: socket buffer holding a netlink command from userspace
 * @user_ns: The user namespace of the capability to use
 * @cap: The capability to use
 *
 * Test to see अगर the खोलोer of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has the capability @cap in the user namespace @user_ns.
 */
bool netlink_ns_capable(स्थिर काष्ठा sk_buff *skb,
			काष्ठा user_namespace *user_ns, पूर्णांक cap)
अणु
	वापस __netlink_ns_capable(&NETLINK_CB(skb), user_ns, cap);
पूर्ण
EXPORT_SYMBOL(netlink_ns_capable);

/**
 * netlink_capable - Netlink global message capability test
 * @skb: socket buffer holding a netlink command from userspace
 * @cap: The capability to use
 *
 * Test to see अगर the खोलोer of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has the capability @cap in all user namespaces.
 */
bool netlink_capable(स्थिर काष्ठा sk_buff *skb, पूर्णांक cap)
अणु
	वापस netlink_ns_capable(skb, &init_user_ns, cap);
पूर्ण
EXPORT_SYMBOL(netlink_capable);

/**
 * netlink_net_capable - Netlink network namespace message capability test
 * @skb: socket buffer holding a netlink command from userspace
 * @cap: The capability to use
 *
 * Test to see अगर the खोलोer of the socket we received the message
 * from had when the netlink socket was created and the sender of the
 * message has the capability @cap over the network namespace of
 * the socket we received the message from.
 */
bool netlink_net_capable(स्थिर काष्ठा sk_buff *skb, पूर्णांक cap)
अणु
	वापस netlink_ns_capable(skb, sock_net(skb->sk)->user_ns, cap);
पूर्ण
EXPORT_SYMBOL(netlink_net_capable);

अटल अंतरभूत पूर्णांक netlink_allowed(स्थिर काष्ठा socket *sock, अचिन्हित पूर्णांक flag)
अणु
	वापस (nl_table[sock->sk->sk_protocol].flags & flag) ||
		ns_capable(sock_net(sock->sk)->user_ns, CAP_NET_ADMIN);
पूर्ण

अटल व्योम
netlink_update_subscriptions(काष्ठा sock *sk, अचिन्हित पूर्णांक subscriptions)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	अगर (nlk->subscriptions && !subscriptions)
		__sk_del_bind_node(sk);
	अन्यथा अगर (!nlk->subscriptions && subscriptions)
		sk_add_bind_node(sk, &nl_table[sk->sk_protocol].mc_list);
	nlk->subscriptions = subscriptions;
पूर्ण

अटल पूर्णांक netlink_पुनः_स्मृति_groups(काष्ठा sock *sk)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	अचिन्हित पूर्णांक groups;
	अचिन्हित दीर्घ *new_groups;
	पूर्णांक err = 0;

	netlink_table_grab();

	groups = nl_table[sk->sk_protocol].groups;
	अगर (!nl_table[sk->sk_protocol].रेजिस्टरed) अणु
		err = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	अगर (nlk->ngroups >= groups)
		जाओ out_unlock;

	new_groups = kपुनः_स्मृति(nlk->groups, NLGRPSZ(groups), GFP_ATOMIC);
	अगर (new_groups == शून्य) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	स_रखो((अक्षर *)new_groups + NLGRPSZ(nlk->ngroups), 0,
	       NLGRPSZ(groups) - NLGRPSZ(nlk->ngroups));

	nlk->groups = new_groups;
	nlk->ngroups = groups;
 out_unlock:
	netlink_table_ungrab();
	वापस err;
पूर्ण

अटल व्योम netlink_unकरो_bind(पूर्णांक group, दीर्घ अचिन्हित पूर्णांक groups,
			      काष्ठा sock *sk)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	पूर्णांक unकरो;

	अगर (!nlk->netlink_unbind)
		वापस;

	क्रम (unकरो = 0; unकरो < group; unकरो++)
		अगर (test_bit(unकरो, &groups))
			nlk->netlink_unbind(sock_net(sk), unकरो + 1);
पूर्ण

अटल पूर्णांक netlink_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा net *net = sock_net(sk);
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	काष्ठा sockaddr_nl *nladdr = (काष्ठा sockaddr_nl *)addr;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ groups;
	bool bound;

	अगर (addr_len < माप(काष्ठा sockaddr_nl))
		वापस -EINVAL;

	अगर (nladdr->nl_family != AF_NETLINK)
		वापस -EINVAL;
	groups = nladdr->nl_groups;

	/* Only superuser is allowed to listen multicasts */
	अगर (groups) अणु
		अगर (!netlink_allowed(sock, NL_CFG_F_NONROOT_RECV))
			वापस -EPERM;
		err = netlink_पुनः_स्मृति_groups(sk);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (nlk->ngroups < BITS_PER_LONG)
		groups &= (1UL << nlk->ngroups) - 1;

	bound = nlk->bound;
	अगर (bound) अणु
		/* Ensure nlk->portid is up-to-date. */
		smp_rmb();

		अगर (nladdr->nl_pid != nlk->portid)
			वापस -EINVAL;
	पूर्ण

	अगर (nlk->netlink_bind && groups) अणु
		पूर्णांक group;

		/* nl_groups is a u32, so cap the maximum groups we can bind */
		क्रम (group = 0; group < BITS_PER_TYPE(u32); group++) अणु
			अगर (!test_bit(group, &groups))
				जारी;
			err = nlk->netlink_bind(net, group + 1);
			अगर (!err)
				जारी;
			netlink_unकरो_bind(group, groups, sk);
			वापस err;
		पूर्ण
	पूर्ण

	/* No need क्रम barriers here as we वापस to user-space without
	 * using any of the bound attributes.
	 */
	netlink_lock_table();
	अगर (!bound) अणु
		err = nladdr->nl_pid ?
			netlink_insert(sk, nladdr->nl_pid) :
			netlink_स्वतःbind(sock);
		अगर (err) अणु
			netlink_unकरो_bind(BITS_PER_TYPE(u32), groups, sk);
			जाओ unlock;
		पूर्ण
	पूर्ण

	अगर (!groups && (nlk->groups == शून्य || !(u32)nlk->groups[0]))
		जाओ unlock;
	netlink_unlock_table();

	netlink_table_grab();
	netlink_update_subscriptions(sk, nlk->subscriptions +
					 hweight32(groups) -
					 hweight32(nlk->groups[0]));
	nlk->groups[0] = (nlk->groups[0] & ~0xffffffffUL) | groups;
	netlink_update_listeners(sk);
	netlink_table_ungrab();

	वापस 0;

unlock:
	netlink_unlock_table();
	वापस err;
पूर्ण

अटल पूर्णांक netlink_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			   पूर्णांक alen, पूर्णांक flags)
अणु
	पूर्णांक err = 0;
	काष्ठा sock *sk = sock->sk;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	काष्ठा sockaddr_nl *nladdr = (काष्ठा sockaddr_nl *)addr;

	अगर (alen < माप(addr->sa_family))
		वापस -EINVAL;

	अगर (addr->sa_family == AF_UNSPEC) अणु
		sk->sk_state	= NETLINK_UNCONNECTED;
		nlk->dst_portid	= 0;
		nlk->dst_group  = 0;
		वापस 0;
	पूर्ण
	अगर (addr->sa_family != AF_NETLINK)
		वापस -EINVAL;

	अगर (alen < माप(काष्ठा sockaddr_nl))
		वापस -EINVAL;

	अगर ((nladdr->nl_groups || nladdr->nl_pid) &&
	    !netlink_allowed(sock, NL_CFG_F_NONROOT_SEND))
		वापस -EPERM;

	/* No need क्रम barriers here as we वापस to user-space without
	 * using any of the bound attributes.
	 */
	अगर (!nlk->bound)
		err = netlink_स्वतःbind(sock);

	अगर (err == 0) अणु
		sk->sk_state	= NETLINK_CONNECTED;
		nlk->dst_portid = nladdr->nl_pid;
		nlk->dst_group  = ffs(nladdr->nl_groups);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक netlink_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			   पूर्णांक peer)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_nl *, nladdr, addr);

	nladdr->nl_family = AF_NETLINK;
	nladdr->nl_pad = 0;

	अगर (peer) अणु
		nladdr->nl_pid = nlk->dst_portid;
		nladdr->nl_groups = netlink_group_mask(nlk->dst_group);
	पूर्ण अन्यथा अणु
		nladdr->nl_pid = nlk->portid;
		netlink_lock_table();
		nladdr->nl_groups = nlk->groups ? nlk->groups[0] : 0;
		netlink_unlock_table();
	पूर्ण
	वापस माप(*nladdr);
पूर्ण

अटल पूर्णांक netlink_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	/* try to hand this ioctl करोwn to the NIC drivers.
	 */
	वापस -ENOIOCTLCMD;
पूर्ण

अटल काष्ठा sock *netlink_माला_लोockbyportid(काष्ठा sock *ssk, u32 portid)
अणु
	काष्ठा sock *sock;
	काष्ठा netlink_sock *nlk;

	sock = netlink_lookup(sock_net(ssk), ssk->sk_protocol, portid);
	अगर (!sock)
		वापस ERR_PTR(-ECONNREFUSED);

	/* Don't bother queuing skb अगर kernel socket has no input function */
	nlk = nlk_sk(sock);
	अगर (sock->sk_state == NETLINK_CONNECTED &&
	    nlk->dst_portid != nlk_sk(ssk)->portid) अणु
		sock_put(sock);
		वापस ERR_PTR(-ECONNREFUSED);
	पूर्ण
	वापस sock;
पूर्ण

काष्ठा sock *netlink_माला_लोockbyfilp(काष्ठा file *filp)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा sock *sock;

	अगर (!S_ISSOCK(inode->i_mode))
		वापस ERR_PTR(-ENOTSOCK);

	sock = SOCKET_I(inode)->sk;
	अगर (sock->sk_family != AF_NETLINK)
		वापस ERR_PTR(-EINVAL);

	sock_hold(sock);
	वापस sock;
पूर्ण

अटल काष्ठा sk_buff *netlink_alloc_large_skb(अचिन्हित पूर्णांक size,
					       पूर्णांक broadcast)
अणु
	काष्ठा sk_buff *skb;
	व्योम *data;

	अगर (size <= NLMSG_GOODSIZE || broadcast)
		वापस alloc_skb(size, GFP_KERNEL);

	size = SKB_DATA_ALIGN(size) +
	       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	data = vदो_स्मृति(size);
	अगर (data == शून्य)
		वापस शून्य;

	skb = __build_skb(data, size);
	अगर (skb == शून्य)
		vमुक्त(data);
	अन्यथा
		skb->deकाष्ठाor = netlink_skb_deकाष्ठाor;

	वापस skb;
पूर्ण

/*
 * Attach a skb to a netlink socket.
 * The caller must hold a reference to the destination socket. On error, the
 * reference is dropped. The skb is not send to the destination, just all
 * all error checks are perक्रमmed and memory in the queue is reserved.
 * Return values:
 * < 0: error. skb मुक्तd, reference to sock dropped.
 * 0: जारी
 * 1: repeat lookup - reference dropped जबतक रुकोing क्रम socket memory.
 */
पूर्णांक netlink_attachskb(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		      दीर्घ *समयo, काष्ठा sock *ssk)
अणु
	काष्ठा netlink_sock *nlk;

	nlk = nlk_sk(sk);

	अगर ((atomic_पढ़ो(&sk->sk_rmem_alloc) > sk->sk_rcvbuf ||
	     test_bit(NETLINK_S_CONGESTED, &nlk->state))) अणु
		DECLARE_WAITQUEUE(रुको, current);
		अगर (!*समयo) अणु
			अगर (!ssk || netlink_is_kernel(ssk))
				netlink_overrun(sk);
			sock_put(sk);
			kमुक्त_skb(skb);
			वापस -EAGAIN;
		पूर्ण

		__set_current_state(TASK_INTERRUPTIBLE);
		add_रुको_queue(&nlk->रुको, &रुको);

		अगर ((atomic_पढ़ो(&sk->sk_rmem_alloc) > sk->sk_rcvbuf ||
		     test_bit(NETLINK_S_CONGESTED, &nlk->state)) &&
		    !sock_flag(sk, SOCK_DEAD))
			*समयo = schedule_समयout(*समयo);

		__set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&nlk->रुको, &रुको);
		sock_put(sk);

		अगर (संकेत_pending(current)) अणु
			kमुक्त_skb(skb);
			वापस sock_पूर्णांकr_त्रुटि_सं(*समयo);
		पूर्ण
		वापस 1;
	पूर्ण
	netlink_skb_set_owner_r(skb, sk);
	वापस 0;
पूर्ण

अटल पूर्णांक __netlink_sendskb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = skb->len;

	netlink_deliver_tap(sock_net(sk), skb);

	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_पढ़ोy(sk);
	वापस len;
पूर्ण

पूर्णांक netlink_sendskb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक len = __netlink_sendskb(sk, skb);

	sock_put(sk);
	वापस len;
पूर्ण

व्योम netlink_detachskb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	kमुक्त_skb(skb);
	sock_put(sk);
पूर्ण

अटल काष्ठा sk_buff *netlink_trim(काष्ठा sk_buff *skb, gfp_t allocation)
अणु
	पूर्णांक delta;

	WARN_ON(skb->sk != शून्य);
	delta = skb->end - skb->tail;
	अगर (is_vदो_स्मृति_addr(skb->head) || delta * 2 < skb->truesize)
		वापस skb;

	अगर (skb_shared(skb)) अणु
		काष्ठा sk_buff *nskb = skb_clone(skb, allocation);
		अगर (!nskb)
			वापस skb;
		consume_skb(skb);
		skb = nskb;
	पूर्ण

	pskb_expand_head(skb, 0, -delta,
			 (allocation & ~__GFP_सूचीECT_RECLAIM) |
			 __GFP_NOWARN | __GFP_NORETRY);
	वापस skb;
पूर्ण

अटल पूर्णांक netlink_unicast_kernel(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				  काष्ठा sock *ssk)
अणु
	पूर्णांक ret;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	ret = -ECONNREFUSED;
	अगर (nlk->netlink_rcv != शून्य) अणु
		ret = skb->len;
		netlink_skb_set_owner_r(skb, sk);
		NETLINK_CB(skb).sk = ssk;
		netlink_deliver_tap_kernel(sk, ssk, skb);
		nlk->netlink_rcv(skb);
		consume_skb(skb);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
	पूर्ण
	sock_put(sk);
	वापस ret;
पूर्ण

पूर्णांक netlink_unicast(काष्ठा sock *ssk, काष्ठा sk_buff *skb,
		    u32 portid, पूर्णांक nonblock)
अणु
	काष्ठा sock *sk;
	पूर्णांक err;
	दीर्घ समयo;

	skb = netlink_trim(skb, gfp_any());

	समयo = sock_sndसमयo(ssk, nonblock);
retry:
	sk = netlink_माला_लोockbyportid(ssk, portid);
	अगर (IS_ERR(sk)) अणु
		kमुक्त_skb(skb);
		वापस PTR_ERR(sk);
	पूर्ण
	अगर (netlink_is_kernel(sk))
		वापस netlink_unicast_kernel(sk, skb, ssk);

	अगर (sk_filter(sk, skb)) अणु
		err = skb->len;
		kमुक्त_skb(skb);
		sock_put(sk);
		वापस err;
	पूर्ण

	err = netlink_attachskb(sk, skb, &समयo, ssk);
	अगर (err == 1)
		जाओ retry;
	अगर (err)
		वापस err;

	वापस netlink_sendskb(sk, skb);
पूर्ण
EXPORT_SYMBOL(netlink_unicast);

पूर्णांक netlink_has_listeners(काष्ठा sock *sk, अचिन्हित पूर्णांक group)
अणु
	पूर्णांक res = 0;
	काष्ठा listeners *listeners;

	BUG_ON(!netlink_is_kernel(sk));

	rcu_पढ़ो_lock();
	listeners = rcu_dereference(nl_table[sk->sk_protocol].listeners);

	अगर (listeners && group - 1 < nl_table[sk->sk_protocol].groups)
		res = test_bit(group - 1, listeners->masks);

	rcu_पढ़ो_unlock();

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(netlink_has_listeners);

bool netlink_strict_get_check(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा netlink_sock *nlk = nlk_sk(NETLINK_CB(skb).sk);

	वापस nlk->flags & NETLINK_F_STRICT_CHK;
पूर्ण
EXPORT_SYMBOL_GPL(netlink_strict_get_check);

अटल पूर्णांक netlink_broadcast_deliver(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf &&
	    !test_bit(NETLINK_S_CONGESTED, &nlk->state)) अणु
		netlink_skb_set_owner_r(skb, sk);
		__netlink_sendskb(sk, skb);
		वापस atomic_पढ़ो(&sk->sk_rmem_alloc) > (sk->sk_rcvbuf >> 1);
	पूर्ण
	वापस -1;
पूर्ण

काष्ठा netlink_broadcast_data अणु
	काष्ठा sock *exclude_sk;
	काष्ठा net *net;
	u32 portid;
	u32 group;
	पूर्णांक failure;
	पूर्णांक delivery_failure;
	पूर्णांक congested;
	पूर्णांक delivered;
	gfp_t allocation;
	काष्ठा sk_buff *skb, *skb2;
	पूर्णांक (*tx_filter)(काष्ठा sock *dsk, काष्ठा sk_buff *skb, व्योम *data);
	व्योम *tx_data;
पूर्ण;

अटल व्योम करो_one_broadcast(काष्ठा sock *sk,
				    काष्ठा netlink_broadcast_data *p)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	पूर्णांक val;

	अगर (p->exclude_sk == sk)
		वापस;

	अगर (nlk->portid == p->portid || p->group - 1 >= nlk->ngroups ||
	    !test_bit(p->group - 1, nlk->groups))
		वापस;

	अगर (!net_eq(sock_net(sk), p->net)) अणु
		अगर (!(nlk->flags & NETLINK_F_LISTEN_ALL_NSID))
			वापस;

		अगर (!peernet_has_id(sock_net(sk), p->net))
			वापस;

		अगर (!file_ns_capable(sk->sk_socket->file, p->net->user_ns,
				     CAP_NET_BROADCAST))
			वापस;
	पूर्ण

	अगर (p->failure) अणु
		netlink_overrun(sk);
		वापस;
	पूर्ण

	sock_hold(sk);
	अगर (p->skb2 == शून्य) अणु
		अगर (skb_shared(p->skb)) अणु
			p->skb2 = skb_clone(p->skb, p->allocation);
		पूर्ण अन्यथा अणु
			p->skb2 = skb_get(p->skb);
			/*
			 * skb ownership may have been set when
			 * delivered to a previous socket.
			 */
			skb_orphan(p->skb2);
		पूर्ण
	पूर्ण
	अगर (p->skb2 == शून्य) अणु
		netlink_overrun(sk);
		/* Clone failed. Notअगरy ALL listeners. */
		p->failure = 1;
		अगर (nlk->flags & NETLINK_F_BROADCAST_SEND_ERROR)
			p->delivery_failure = 1;
		जाओ out;
	पूर्ण
	अगर (p->tx_filter && p->tx_filter(sk, p->skb2, p->tx_data)) अणु
		kमुक्त_skb(p->skb2);
		p->skb2 = शून्य;
		जाओ out;
	पूर्ण
	अगर (sk_filter(sk, p->skb2)) अणु
		kमुक्त_skb(p->skb2);
		p->skb2 = शून्य;
		जाओ out;
	पूर्ण
	NETLINK_CB(p->skb2).nsid = peernet2id(sock_net(sk), p->net);
	अगर (NETLINK_CB(p->skb2).nsid != NETNSA_NSID_NOT_ASSIGNED)
		NETLINK_CB(p->skb2).nsid_is_set = true;
	val = netlink_broadcast_deliver(sk, p->skb2);
	अगर (val < 0) अणु
		netlink_overrun(sk);
		अगर (nlk->flags & NETLINK_F_BROADCAST_SEND_ERROR)
			p->delivery_failure = 1;
	पूर्ण अन्यथा अणु
		p->congested |= val;
		p->delivered = 1;
		p->skb2 = शून्य;
	पूर्ण
out:
	sock_put(sk);
पूर्ण

पूर्णांक netlink_broadcast_filtered(काष्ठा sock *ssk, काष्ठा sk_buff *skb, u32 portid,
	u32 group, gfp_t allocation,
	पूर्णांक (*filter)(काष्ठा sock *dsk, काष्ठा sk_buff *skb, व्योम *data),
	व्योम *filter_data)
अणु
	काष्ठा net *net = sock_net(ssk);
	काष्ठा netlink_broadcast_data info;
	काष्ठा sock *sk;

	skb = netlink_trim(skb, allocation);

	info.exclude_sk = ssk;
	info.net = net;
	info.portid = portid;
	info.group = group;
	info.failure = 0;
	info.delivery_failure = 0;
	info.congested = 0;
	info.delivered = 0;
	info.allocation = allocation;
	info.skb = skb;
	info.skb2 = शून्य;
	info.tx_filter = filter;
	info.tx_data = filter_data;

	/* While we sleep in clone, करो not allow to change socket list */

	netlink_lock_table();

	sk_क्रम_each_bound(sk, &nl_table[ssk->sk_protocol].mc_list)
		करो_one_broadcast(sk, &info);

	consume_skb(skb);

	netlink_unlock_table();

	अगर (info.delivery_failure) अणु
		kमुक्त_skb(info.skb2);
		वापस -ENOBUFS;
	पूर्ण
	consume_skb(info.skb2);

	अगर (info.delivered) अणु
		अगर (info.congested && gfpflags_allow_blocking(allocation))
			yield();
		वापस 0;
	पूर्ण
	वापस -ESRCH;
पूर्ण
EXPORT_SYMBOL(netlink_broadcast_filtered);

पूर्णांक netlink_broadcast(काष्ठा sock *ssk, काष्ठा sk_buff *skb, u32 portid,
		      u32 group, gfp_t allocation)
अणु
	वापस netlink_broadcast_filtered(ssk, skb, portid, group, allocation,
		शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL(netlink_broadcast);

काष्ठा netlink_set_err_data अणु
	काष्ठा sock *exclude_sk;
	u32 portid;
	u32 group;
	पूर्णांक code;
पूर्ण;

अटल पूर्णांक करो_one_set_err(काष्ठा sock *sk, काष्ठा netlink_set_err_data *p)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	पूर्णांक ret = 0;

	अगर (sk == p->exclude_sk)
		जाओ out;

	अगर (!net_eq(sock_net(sk), sock_net(p->exclude_sk)))
		जाओ out;

	अगर (nlk->portid == p->portid || p->group - 1 >= nlk->ngroups ||
	    !test_bit(p->group - 1, nlk->groups))
		जाओ out;

	अगर (p->code == ENOBUFS && nlk->flags & NETLINK_F_RECV_NO_ENOBUFS) अणु
		ret = 1;
		जाओ out;
	पूर्ण

	sk->sk_err = p->code;
	sk->sk_error_report(sk);
out:
	वापस ret;
पूर्ण

/**
 * netlink_set_err - report error to broadcast listeners
 * @ssk: the kernel netlink socket, as वापसed by netlink_kernel_create()
 * @portid: the PORTID of a process that we want to skip (अगर any)
 * @group: the broadcast group that will notice the error
 * @code: error code, must be negative (as usual in kernelspace)
 *
 * This function वापसs the number of broadcast listeners that have set the
 * NETLINK_NO_ENOBUFS socket option.
 */
पूर्णांक netlink_set_err(काष्ठा sock *ssk, u32 portid, u32 group, पूर्णांक code)
अणु
	काष्ठा netlink_set_err_data info;
	काष्ठा sock *sk;
	पूर्णांक ret = 0;

	info.exclude_sk = ssk;
	info.portid = portid;
	info.group = group;
	/* sk->sk_err wants a positive error value */
	info.code = -code;

	पढ़ो_lock(&nl_table_lock);

	sk_क्रम_each_bound(sk, &nl_table[ssk->sk_protocol].mc_list)
		ret += करो_one_set_err(sk, &info);

	पढ़ो_unlock(&nl_table_lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(netlink_set_err);

/* must be called with netlink table grabbed */
अटल व्योम netlink_update_socket_mc(काष्ठा netlink_sock *nlk,
				     अचिन्हित पूर्णांक group,
				     पूर्णांक is_new)
अणु
	पूर्णांक old, new = !!is_new, subscriptions;

	old = test_bit(group - 1, nlk->groups);
	subscriptions = nlk->subscriptions - old + new;
	अगर (new)
		__set_bit(group - 1, nlk->groups);
	अन्यथा
		__clear_bit(group - 1, nlk->groups);
	netlink_update_subscriptions(&nlk->sk, subscriptions);
	netlink_update_listeners(&nlk->sk);
पूर्ण

अटल पूर्णांक netlink_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			      sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक err;

	अगर (level != SOL_NETLINK)
		वापस -ENOPROTOOPT;

	अगर (optlen >= माप(पूर्णांक) &&
	    copy_from_sockptr(&val, optval, माप(val)))
		वापस -EFAULT;

	चयन (optname) अणु
	हाल NETLINK_PKTINFO:
		अगर (val)
			nlk->flags |= NETLINK_F_RECV_PKTINFO;
		अन्यथा
			nlk->flags &= ~NETLINK_F_RECV_PKTINFO;
		err = 0;
		अवरोध;
	हाल NETLINK_ADD_MEMBERSHIP:
	हाल NETLINK_DROP_MEMBERSHIP: अणु
		अगर (!netlink_allowed(sock, NL_CFG_F_NONROOT_RECV))
			वापस -EPERM;
		err = netlink_पुनः_स्मृति_groups(sk);
		अगर (err)
			वापस err;
		अगर (!val || val - 1 >= nlk->ngroups)
			वापस -EINVAL;
		अगर (optname == NETLINK_ADD_MEMBERSHIP && nlk->netlink_bind) अणु
			err = nlk->netlink_bind(sock_net(sk), val);
			अगर (err)
				वापस err;
		पूर्ण
		netlink_table_grab();
		netlink_update_socket_mc(nlk, val,
					 optname == NETLINK_ADD_MEMBERSHIP);
		netlink_table_ungrab();
		अगर (optname == NETLINK_DROP_MEMBERSHIP && nlk->netlink_unbind)
			nlk->netlink_unbind(sock_net(sk), val);

		err = 0;
		अवरोध;
	पूर्ण
	हाल NETLINK_BROADCAST_ERROR:
		अगर (val)
			nlk->flags |= NETLINK_F_BROADCAST_SEND_ERROR;
		अन्यथा
			nlk->flags &= ~NETLINK_F_BROADCAST_SEND_ERROR;
		err = 0;
		अवरोध;
	हाल NETLINK_NO_ENOBUFS:
		अगर (val) अणु
			nlk->flags |= NETLINK_F_RECV_NO_ENOBUFS;
			clear_bit(NETLINK_S_CONGESTED, &nlk->state);
			wake_up_पूर्णांकerruptible(&nlk->रुको);
		पूर्ण अन्यथा अणु
			nlk->flags &= ~NETLINK_F_RECV_NO_ENOBUFS;
		पूर्ण
		err = 0;
		अवरोध;
	हाल NETLINK_LISTEN_ALL_NSID:
		अगर (!ns_capable(sock_net(sk)->user_ns, CAP_NET_BROADCAST))
			वापस -EPERM;

		अगर (val)
			nlk->flags |= NETLINK_F_LISTEN_ALL_NSID;
		अन्यथा
			nlk->flags &= ~NETLINK_F_LISTEN_ALL_NSID;
		err = 0;
		अवरोध;
	हाल NETLINK_CAP_ACK:
		अगर (val)
			nlk->flags |= NETLINK_F_CAP_ACK;
		अन्यथा
			nlk->flags &= ~NETLINK_F_CAP_ACK;
		err = 0;
		अवरोध;
	हाल NETLINK_EXT_ACK:
		अगर (val)
			nlk->flags |= NETLINK_F_EXT_ACK;
		अन्यथा
			nlk->flags &= ~NETLINK_F_EXT_ACK;
		err = 0;
		अवरोध;
	हाल NETLINK_GET_STRICT_CHK:
		अगर (val)
			nlk->flags |= NETLINK_F_STRICT_CHK;
		अन्यथा
			nlk->flags &= ~NETLINK_F_STRICT_CHK;
		err = 0;
		अवरोध;
	शेष:
		err = -ENOPROTOOPT;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक netlink_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
			      अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	पूर्णांक len, val, err;

	अगर (level != SOL_NETLINK)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;
	अगर (len < 0)
		वापस -EINVAL;

	चयन (optname) अणु
	हाल NETLINK_PKTINFO:
		अगर (len < माप(पूर्णांक))
			वापस -EINVAL;
		len = माप(पूर्णांक);
		val = nlk->flags & NETLINK_F_RECV_PKTINFO ? 1 : 0;
		अगर (put_user(len, optlen) ||
		    put_user(val, optval))
			वापस -EFAULT;
		err = 0;
		अवरोध;
	हाल NETLINK_BROADCAST_ERROR:
		अगर (len < माप(पूर्णांक))
			वापस -EINVAL;
		len = माप(पूर्णांक);
		val = nlk->flags & NETLINK_F_BROADCAST_SEND_ERROR ? 1 : 0;
		अगर (put_user(len, optlen) ||
		    put_user(val, optval))
			वापस -EFAULT;
		err = 0;
		अवरोध;
	हाल NETLINK_NO_ENOBUFS:
		अगर (len < माप(पूर्णांक))
			वापस -EINVAL;
		len = माप(पूर्णांक);
		val = nlk->flags & NETLINK_F_RECV_NO_ENOBUFS ? 1 : 0;
		अगर (put_user(len, optlen) ||
		    put_user(val, optval))
			वापस -EFAULT;
		err = 0;
		अवरोध;
	हाल NETLINK_LIST_MEMBERSHIPS: अणु
		पूर्णांक pos, idx, shअगरt;

		err = 0;
		netlink_lock_table();
		क्रम (pos = 0; pos * 8 < nlk->ngroups; pos += माप(u32)) अणु
			अगर (len - pos < माप(u32))
				अवरोध;

			idx = pos / माप(अचिन्हित दीर्घ);
			shअगरt = (pos % माप(अचिन्हित दीर्घ)) * 8;
			अगर (put_user((u32)(nlk->groups[idx] >> shअगरt),
				     (u32 __user *)(optval + pos))) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (put_user(ALIGN(nlk->ngroups / 8, माप(u32)), optlen))
			err = -EFAULT;
		netlink_unlock_table();
		अवरोध;
	पूर्ण
	हाल NETLINK_CAP_ACK:
		अगर (len < माप(पूर्णांक))
			वापस -EINVAL;
		len = माप(पूर्णांक);
		val = nlk->flags & NETLINK_F_CAP_ACK ? 1 : 0;
		अगर (put_user(len, optlen) ||
		    put_user(val, optval))
			वापस -EFAULT;
		err = 0;
		अवरोध;
	हाल NETLINK_EXT_ACK:
		अगर (len < माप(पूर्णांक))
			वापस -EINVAL;
		len = माप(पूर्णांक);
		val = nlk->flags & NETLINK_F_EXT_ACK ? 1 : 0;
		अगर (put_user(len, optlen) || put_user(val, optval))
			वापस -EFAULT;
		err = 0;
		अवरोध;
	हाल NETLINK_GET_STRICT_CHK:
		अगर (len < माप(पूर्णांक))
			वापस -EINVAL;
		len = माप(पूर्णांक);
		val = nlk->flags & NETLINK_F_STRICT_CHK ? 1 : 0;
		अगर (put_user(len, optlen) || put_user(val, optval))
			वापस -EFAULT;
		err = 0;
		अवरोध;
	शेष:
		err = -ENOPROTOOPT;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम netlink_cmsg_recv_pktinfo(काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	काष्ठा nl_pktinfo info;

	info.group = NETLINK_CB(skb).dst_group;
	put_cmsg(msg, SOL_NETLINK, NETLINK_PKTINFO, माप(info), &info);
पूर्ण

अटल व्योम netlink_cmsg_listen_all_nsid(काष्ठा sock *sk, काष्ठा msghdr *msg,
					 काष्ठा sk_buff *skb)
अणु
	अगर (!NETLINK_CB(skb).nsid_is_set)
		वापस;

	put_cmsg(msg, SOL_NETLINK, NETLINK_LISTEN_ALL_NSID, माप(पूर्णांक),
		 &NETLINK_CB(skb).nsid);
पूर्ण

अटल पूर्णांक netlink_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_nl *, addr, msg->msg_name);
	u32 dst_portid;
	u32 dst_group;
	काष्ठा sk_buff *skb;
	पूर्णांक err;
	काष्ठा scm_cookie scm;
	u32 netlink_skb_flags = 0;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	err = scm_send(sock, msg, &scm, true);
	अगर (err < 0)
		वापस err;

	अगर (msg->msg_namelen) अणु
		err = -EINVAL;
		अगर (msg->msg_namelen < माप(काष्ठा sockaddr_nl))
			जाओ out;
		अगर (addr->nl_family != AF_NETLINK)
			जाओ out;
		dst_portid = addr->nl_pid;
		dst_group = ffs(addr->nl_groups);
		err =  -EPERM;
		अगर ((dst_group || dst_portid) &&
		    !netlink_allowed(sock, NL_CFG_F_NONROOT_SEND))
			जाओ out;
		netlink_skb_flags |= NETLINK_SKB_DST;
	पूर्ण अन्यथा अणु
		dst_portid = nlk->dst_portid;
		dst_group = nlk->dst_group;
	पूर्ण

	अगर (!nlk->bound) अणु
		err = netlink_स्वतःbind(sock);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		/* Ensure nlk is hashed and visible. */
		smp_rmb();
	पूर्ण

	err = -EMSGSIZE;
	अगर (len > sk->sk_sndbuf - 32)
		जाओ out;
	err = -ENOBUFS;
	skb = netlink_alloc_large_skb(len, dst_group);
	अगर (skb == शून्य)
		जाओ out;

	NETLINK_CB(skb).portid	= nlk->portid;
	NETLINK_CB(skb).dst_group = dst_group;
	NETLINK_CB(skb).creds	= scm.creds;
	NETLINK_CB(skb).flags	= netlink_skb_flags;

	err = -EFAULT;
	अगर (स_नकल_from_msg(skb_put(skb, len), msg, len)) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	err = security_netlink_send(sk, skb);
	अगर (err) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण

	अगर (dst_group) अणु
		refcount_inc(&skb->users);
		netlink_broadcast(sk, skb, dst_portid, dst_group, GFP_KERNEL);
	पूर्ण
	err = netlink_unicast(sk, skb, dst_portid, msg->msg_flags & MSG_DONTWAIT);

out:
	scm_destroy(&scm);
	वापस err;
पूर्ण

अटल पूर्णांक netlink_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
			   पूर्णांक flags)
अणु
	काष्ठा scm_cookie scm;
	काष्ठा sock *sk = sock->sk;
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	माप_प्रकार copied;
	काष्ठा sk_buff *skb, *data_skb;
	पूर्णांक err, ret;

	अगर (flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	copied = 0;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (skb == शून्य)
		जाओ out;

	data_skb = skb;

#अगर_घोषित CONFIG_COMPAT_NETLINK_MESSAGES
	अगर (unlikely(skb_shinfo(skb)->frag_list)) अणु
		/*
		 * If this skb has a frag_list, then here that means that we
		 * will have to use the frag_list skb's data क्रम compat tasks
		 * and the regular skb's data क्रम normal (non-compat) tasks.
		 *
		 * If we need to send the compat skb, assign it to the
		 * 'data_skb' variable so that it will be used below क्रम data
		 * copying. We keep 'skb' क्रम everything अन्यथा, including
		 * मुक्तing both later.
		 */
		अगर (flags & MSG_CMSG_COMPAT)
			data_skb = skb_shinfo(skb)->frag_list;
	पूर्ण
#पूर्ण_अगर

	/* Record the max length of recvmsg() calls क्रम future allocations */
	nlk->max_recvmsg_len = max(nlk->max_recvmsg_len, len);
	nlk->max_recvmsg_len = min_t(माप_प्रकार, nlk->max_recvmsg_len,
				     SKB_WITH_OVERHEAD(32768));

	copied = data_skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	skb_reset_transport_header(data_skb);
	err = skb_copy_datagram_msg(data_skb, 0, msg, copied);

	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_nl *, addr, msg->msg_name);
		addr->nl_family = AF_NETLINK;
		addr->nl_pad    = 0;
		addr->nl_pid	= NETLINK_CB(skb).portid;
		addr->nl_groups	= netlink_group_mask(NETLINK_CB(skb).dst_group);
		msg->msg_namelen = माप(*addr);
	पूर्ण

	अगर (nlk->flags & NETLINK_F_RECV_PKTINFO)
		netlink_cmsg_recv_pktinfo(msg, skb);
	अगर (nlk->flags & NETLINK_F_LISTEN_ALL_NSID)
		netlink_cmsg_listen_all_nsid(sk, msg, skb);

	स_रखो(&scm, 0, माप(scm));
	scm.creds = *NETLINK_CREDS(skb);
	अगर (flags & MSG_TRUNC)
		copied = data_skb->len;

	skb_मुक्त_datagram(sk, skb);

	अगर (nlk->cb_running &&
	    atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf / 2) अणु
		ret = netlink_dump(sk);
		अगर (ret) अणु
			sk->sk_err = -ret;
			sk->sk_error_report(sk);
		पूर्ण
	पूर्ण

	scm_recv(sock, msg, &scm, flags);
out:
	netlink_rcv_wake(sk);
	वापस err ? : copied;
पूर्ण

अटल व्योम netlink_data_पढ़ोy(काष्ठा sock *sk)
अणु
	BUG();
पूर्ण

/*
 *	We export these functions to other modules. They provide a
 *	complete set of kernel non-blocking support क्रम message
 *	queueing.
 */

काष्ठा sock *
__netlink_kernel_create(काष्ठा net *net, पूर्णांक unit, काष्ठा module *module,
			काष्ठा netlink_kernel_cfg *cfg)
अणु
	काष्ठा socket *sock;
	काष्ठा sock *sk;
	काष्ठा netlink_sock *nlk;
	काष्ठा listeners *listeners = शून्य;
	काष्ठा mutex *cb_mutex = cfg ? cfg->cb_mutex : शून्य;
	अचिन्हित पूर्णांक groups;

	BUG_ON(!nl_table);

	अगर (unit < 0 || unit >= MAX_LINKS)
		वापस शून्य;

	अगर (sock_create_lite(PF_NETLINK, SOCK_DGRAM, unit, &sock))
		वापस शून्य;

	अगर (__netlink_create(net, sock, cb_mutex, unit, 1) < 0)
		जाओ out_sock_release_nosk;

	sk = sock->sk;

	अगर (!cfg || cfg->groups < 32)
		groups = 32;
	अन्यथा
		groups = cfg->groups;

	listeners = kzalloc(माप(*listeners) + NLGRPSZ(groups), GFP_KERNEL);
	अगर (!listeners)
		जाओ out_sock_release;

	sk->sk_data_पढ़ोy = netlink_data_पढ़ोy;
	अगर (cfg && cfg->input)
		nlk_sk(sk)->netlink_rcv = cfg->input;

	अगर (netlink_insert(sk, 0))
		जाओ out_sock_release;

	nlk = nlk_sk(sk);
	nlk->flags |= NETLINK_F_KERNEL_SOCKET;

	netlink_table_grab();
	अगर (!nl_table[unit].रेजिस्टरed) अणु
		nl_table[unit].groups = groups;
		rcu_assign_poपूर्णांकer(nl_table[unit].listeners, listeners);
		nl_table[unit].cb_mutex = cb_mutex;
		nl_table[unit].module = module;
		अगर (cfg) अणु
			nl_table[unit].bind = cfg->bind;
			nl_table[unit].unbind = cfg->unbind;
			nl_table[unit].flags = cfg->flags;
			अगर (cfg->compare)
				nl_table[unit].compare = cfg->compare;
		पूर्ण
		nl_table[unit].रेजिस्टरed = 1;
	पूर्ण अन्यथा अणु
		kमुक्त(listeners);
		nl_table[unit].रेजिस्टरed++;
	पूर्ण
	netlink_table_ungrab();
	वापस sk;

out_sock_release:
	kमुक्त(listeners);
	netlink_kernel_release(sk);
	वापस शून्य;

out_sock_release_nosk:
	sock_release(sock);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(__netlink_kernel_create);

व्योम
netlink_kernel_release(काष्ठा sock *sk)
अणु
	अगर (sk == शून्य || sk->sk_socket == शून्य)
		वापस;

	sock_release(sk->sk_socket);
पूर्ण
EXPORT_SYMBOL(netlink_kernel_release);

पूर्णांक __netlink_change_ngroups(काष्ठा sock *sk, अचिन्हित पूर्णांक groups)
अणु
	काष्ठा listeners *new, *old;
	काष्ठा netlink_table *tbl = &nl_table[sk->sk_protocol];

	अगर (groups < 32)
		groups = 32;

	अगर (NLGRPSZ(tbl->groups) < NLGRPSZ(groups)) अणु
		new = kzalloc(माप(*new) + NLGRPSZ(groups), GFP_ATOMIC);
		अगर (!new)
			वापस -ENOMEM;
		old = nl_deref_रक्षित(tbl->listeners);
		स_नकल(new->masks, old->masks, NLGRPSZ(tbl->groups));
		rcu_assign_poपूर्णांकer(tbl->listeners, new);

		kमुक्त_rcu(old, rcu);
	पूर्ण
	tbl->groups = groups;

	वापस 0;
पूर्ण

/**
 * netlink_change_ngroups - change number of multicast groups
 *
 * This changes the number of multicast groups that are available
 * on a certain netlink family. Note that it is not possible to
 * change the number of groups to below 32. Also note that it करोes
 * not implicitly call netlink_clear_multicast_users() when the
 * number of groups is reduced.
 *
 * @sk: The kernel netlink socket, as वापसed by netlink_kernel_create().
 * @groups: The new number of groups.
 */
पूर्णांक netlink_change_ngroups(काष्ठा sock *sk, अचिन्हित पूर्णांक groups)
अणु
	पूर्णांक err;

	netlink_table_grab();
	err = __netlink_change_ngroups(sk, groups);
	netlink_table_ungrab();

	वापस err;
पूर्ण

व्योम __netlink_clear_multicast_users(काष्ठा sock *ksk, अचिन्हित पूर्णांक group)
अणु
	काष्ठा sock *sk;
	काष्ठा netlink_table *tbl = &nl_table[ksk->sk_protocol];

	sk_क्रम_each_bound(sk, &tbl->mc_list)
		netlink_update_socket_mc(nlk_sk(sk), group, 0);
पूर्ण

काष्ठा nlmsghdr *
__nlmsg_put(काष्ठा sk_buff *skb, u32 portid, u32 seq, पूर्णांक type, पूर्णांक len, पूर्णांक flags)
अणु
	काष्ठा nlmsghdr *nlh;
	पूर्णांक size = nlmsg_msg_size(len);

	nlh = skb_put(skb, NLMSG_ALIGN(size));
	nlh->nlmsg_type = type;
	nlh->nlmsg_len = size;
	nlh->nlmsg_flags = flags;
	nlh->nlmsg_pid = portid;
	nlh->nlmsg_seq = seq;
	अगर (!__builtin_स्थिरant_p(size) || NLMSG_ALIGN(size) - size != 0)
		स_रखो(nlmsg_data(nlh) + len, 0, NLMSG_ALIGN(size) - size);
	वापस nlh;
पूर्ण
EXPORT_SYMBOL(__nlmsg_put);

/*
 * It looks a bit ugly.
 * It would be better to create kernel thपढ़ो.
 */

अटल पूर्णांक netlink_dump_करोne(काष्ठा netlink_sock *nlk, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlmsghdr *nlh;

	nlh = nlmsg_put_answer(skb, cb, NLMSG_DONE, माप(nlk->dump_करोne_त्रुटि_सं),
			       NLM_F_MULTI | cb->answer_flags);
	अगर (WARN_ON(!nlh))
		वापस -ENOBUFS;

	nl_dump_check_consistent(cb, nlh);
	स_नकल(nlmsg_data(nlh), &nlk->dump_करोne_त्रुटि_सं, माप(nlk->dump_करोne_त्रुटि_सं));

	अगर (extack->_msg && nlk->flags & NETLINK_F_EXT_ACK) अणु
		nlh->nlmsg_flags |= NLM_F_ACK_TLVS;
		अगर (!nla_put_string(skb, NLMSGERR_ATTR_MSG, extack->_msg))
			nlmsg_end(skb, nlh);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक netlink_dump(काष्ठा sock *sk)
अणु
	काष्ठा netlink_sock *nlk = nlk_sk(sk);
	काष्ठा netlink_ext_ack extack = अणुपूर्ण;
	काष्ठा netlink_callback *cb;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा module *module;
	पूर्णांक err = -ENOBUFS;
	पूर्णांक alloc_min_size;
	पूर्णांक alloc_size;

	mutex_lock(nlk->cb_mutex);
	अगर (!nlk->cb_running) अणु
		err = -EINVAL;
		जाओ errout_skb;
	पूर्ण

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf)
		जाओ errout_skb;

	/* NLMSG_GOODSIZE is small to aव्योम high order allocations being
	 * required, but it makes sense to _attempt_ a 16K bytes allocation
	 * to reduce number of प्रणाली calls on dump operations, अगर user
	 * ever provided a big enough buffer.
	 */
	cb = &nlk->cb;
	alloc_min_size = max_t(पूर्णांक, cb->min_dump_alloc, NLMSG_GOODSIZE);

	अगर (alloc_min_size < nlk->max_recvmsg_len) अणु
		alloc_size = nlk->max_recvmsg_len;
		skb = alloc_skb(alloc_size,
				(GFP_KERNEL & ~__GFP_सूचीECT_RECLAIM) |
				__GFP_NOWARN | __GFP_NORETRY);
	पूर्ण
	अगर (!skb) अणु
		alloc_size = alloc_min_size;
		skb = alloc_skb(alloc_size, GFP_KERNEL);
	पूर्ण
	अगर (!skb)
		जाओ errout_skb;

	/* Trim skb to allocated size. User is expected to provide buffer as
	 * large as max(min_dump_alloc, 16KiB (mac_recvmsg_len capped at
	 * netlink_recvmsg())). dump will pack as many smaller messages as
	 * could fit within the allocated skb. skb is typically allocated
	 * with larger space than required (could be as much as near 2x the
	 * requested size with align to next घातer of 2 approach). Allowing
	 * dump to use the excess space makes it dअगरficult क्रम a user to have a
	 * reasonable अटल buffer based on the expected largest dump of a
	 * single netdev. The outcome is MSG_TRUNC error.
	 */
	skb_reserve(skb, skb_tailroom(skb) - alloc_size);
	netlink_skb_set_owner_r(skb, sk);

	अगर (nlk->dump_करोne_त्रुटि_सं > 0) अणु
		cb->extack = &extack;
		nlk->dump_करोne_त्रुटि_सं = cb->dump(skb, cb);
		cb->extack = शून्य;
	पूर्ण

	अगर (nlk->dump_करोne_त्रुटि_सं > 0 ||
	    skb_tailroom(skb) < nlmsg_total_size(माप(nlk->dump_करोne_त्रुटि_सं))) अणु
		mutex_unlock(nlk->cb_mutex);

		अगर (sk_filter(sk, skb))
			kमुक्त_skb(skb);
		अन्यथा
			__netlink_sendskb(sk, skb);
		वापस 0;
	पूर्ण

	अगर (netlink_dump_करोne(nlk, skb, cb, &extack))
		जाओ errout_skb;

#अगर_घोषित CONFIG_COMPAT_NETLINK_MESSAGES
	/* frag_list skb's data is used क्रम compat tasks
	 * and the regular skb's data क्रम normal (non-compat) tasks.
	 * See netlink_recvmsg().
	 */
	अगर (unlikely(skb_shinfo(skb)->frag_list)) अणु
		अगर (netlink_dump_करोne(nlk, skb_shinfo(skb)->frag_list, cb, &extack))
			जाओ errout_skb;
	पूर्ण
#पूर्ण_अगर

	अगर (sk_filter(sk, skb))
		kमुक्त_skb(skb);
	अन्यथा
		__netlink_sendskb(sk, skb);

	अगर (cb->करोne)
		cb->करोne(cb);

	nlk->cb_running = false;
	module = cb->module;
	skb = cb->skb;
	mutex_unlock(nlk->cb_mutex);
	module_put(module);
	consume_skb(skb);
	वापस 0;

errout_skb:
	mutex_unlock(nlk->cb_mutex);
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

पूर्णांक __netlink_dump_start(काष्ठा sock *ssk, काष्ठा sk_buff *skb,
			 स्थिर काष्ठा nlmsghdr *nlh,
			 काष्ठा netlink_dump_control *control)
अणु
	काष्ठा netlink_sock *nlk, *nlk2;
	काष्ठा netlink_callback *cb;
	काष्ठा sock *sk;
	पूर्णांक ret;

	refcount_inc(&skb->users);

	sk = netlink_lookup(sock_net(ssk), ssk->sk_protocol, NETLINK_CB(skb).portid);
	अगर (sk == शून्य) अणु
		ret = -ECONNREFUSED;
		जाओ error_मुक्त;
	पूर्ण

	nlk = nlk_sk(sk);
	mutex_lock(nlk->cb_mutex);
	/* A dump is in progress... */
	अगर (nlk->cb_running) अणु
		ret = -EBUSY;
		जाओ error_unlock;
	पूर्ण
	/* add reference of module which cb->dump beदीर्घs to */
	अगर (!try_module_get(control->module)) अणु
		ret = -EPROTONOSUPPORT;
		जाओ error_unlock;
	पूर्ण

	cb = &nlk->cb;
	स_रखो(cb, 0, माप(*cb));
	cb->dump = control->dump;
	cb->करोne = control->करोne;
	cb->nlh = nlh;
	cb->data = control->data;
	cb->module = control->module;
	cb->min_dump_alloc = control->min_dump_alloc;
	cb->skb = skb;

	nlk2 = nlk_sk(NETLINK_CB(skb).sk);
	cb->strict_check = !!(nlk2->flags & NETLINK_F_STRICT_CHK);

	अगर (control->start) अणु
		ret = control->start(cb);
		अगर (ret)
			जाओ error_put;
	पूर्ण

	nlk->cb_running = true;
	nlk->dump_करोne_त्रुटि_सं = पूर्णांक_उच्च;

	mutex_unlock(nlk->cb_mutex);

	ret = netlink_dump(sk);

	sock_put(sk);

	अगर (ret)
		वापस ret;

	/* We successfully started a dump, by वापसing -EINTR we
	 * संकेत not to send ACK even अगर it was requested.
	 */
	वापस -EINTR;

error_put:
	module_put(control->module);
error_unlock:
	sock_put(sk);
	mutex_unlock(nlk->cb_mutex);
error_मुक्त:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__netlink_dump_start);

व्योम netlink_ack(काष्ठा sk_buff *in_skb, काष्ठा nlmsghdr *nlh, पूर्णांक err,
		 स्थिर काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा nlmsghdr *rep;
	काष्ठा nlmsgerr *errmsg;
	माप_प्रकार payload = माप(*errmsg);
	माप_प्रकार tlvlen = 0;
	काष्ठा netlink_sock *nlk = nlk_sk(NETLINK_CB(in_skb).sk);
	अचिन्हित पूर्णांक flags = 0;
	bool nlk_has_extack = nlk->flags & NETLINK_F_EXT_ACK;

	/* Error messages get the original request appened, unless the user
	 * requests to cap the error message, and get extra error data अगर
	 * requested.
	 */
	अगर (nlk_has_extack && extack && extack->_msg)
		tlvlen += nla_total_size(म_माप(extack->_msg) + 1);

	अगर (err && !(nlk->flags & NETLINK_F_CAP_ACK))
		payload += nlmsg_len(nlh);
	अन्यथा
		flags |= NLM_F_CAPPED;
	अगर (err && nlk_has_extack && extack && extack->bad_attr)
		tlvlen += nla_total_size(माप(u32));
	अगर (nlk_has_extack && extack && extack->cookie_len)
		tlvlen += nla_total_size(extack->cookie_len);
	अगर (err && nlk_has_extack && extack && extack->policy)
		tlvlen += netlink_policy_dump_attr_size_estimate(extack->policy);

	अगर (tlvlen)
		flags |= NLM_F_ACK_TLVS;

	skb = nlmsg_new(payload + tlvlen, GFP_KERNEL);
	अगर (!skb) अणु
		NETLINK_CB(in_skb).sk->sk_err = ENOBUFS;
		NETLINK_CB(in_skb).sk->sk_error_report(NETLINK_CB(in_skb).sk);
		वापस;
	पूर्ण

	rep = __nlmsg_put(skb, NETLINK_CB(in_skb).portid, nlh->nlmsg_seq,
			  NLMSG_ERROR, payload, flags);
	errmsg = nlmsg_data(rep);
	errmsg->error = err;
	स_नकल(&errmsg->msg, nlh, payload > माप(*errmsg) ? nlh->nlmsg_len : माप(*nlh));

	अगर (nlk_has_extack && extack) अणु
		अगर (extack->_msg) अणु
			WARN_ON(nla_put_string(skb, NLMSGERR_ATTR_MSG,
					       extack->_msg));
		पूर्ण
		अगर (err && extack->bad_attr &&
		    !WARN_ON((u8 *)extack->bad_attr < in_skb->data ||
			     (u8 *)extack->bad_attr >= in_skb->data +
						       in_skb->len))
			WARN_ON(nla_put_u32(skb, NLMSGERR_ATTR_OFFS,
					    (u8 *)extack->bad_attr -
					    (u8 *)nlh));
		अगर (extack->cookie_len)
			WARN_ON(nla_put(skb, NLMSGERR_ATTR_COOKIE,
					extack->cookie_len, extack->cookie));
		अगर (extack->policy)
			netlink_policy_dump_ग_लिखो_attr(skb, extack->policy,
						       NLMSGERR_ATTR_POLICY);
	पूर्ण

	nlmsg_end(skb, rep);

	netlink_unicast(in_skb->sk, skb, NETLINK_CB(in_skb).portid, MSG_DONTWAIT);
पूर्ण
EXPORT_SYMBOL(netlink_ack);

पूर्णांक netlink_rcv_skb(काष्ठा sk_buff *skb, पूर्णांक (*cb)(काष्ठा sk_buff *,
						   काष्ठा nlmsghdr *,
						   काष्ठा netlink_ext_ack *))
अणु
	काष्ठा netlink_ext_ack extack;
	काष्ठा nlmsghdr *nlh;
	पूर्णांक err;

	जबतक (skb->len >= nlmsg_total_size(0)) अणु
		पूर्णांक msglen;

		स_रखो(&extack, 0, माप(extack));
		nlh = nlmsg_hdr(skb);
		err = 0;

		अगर (nlh->nlmsg_len < NLMSG_HDRLEN || skb->len < nlh->nlmsg_len)
			वापस 0;

		/* Only requests are handled by the kernel */
		अगर (!(nlh->nlmsg_flags & NLM_F_REQUEST))
			जाओ ack;

		/* Skip control messages */
		अगर (nlh->nlmsg_type < NLMSG_MIN_TYPE)
			जाओ ack;

		err = cb(skb, nlh, &extack);
		अगर (err == -EINTR)
			जाओ skip;

ack:
		अगर (nlh->nlmsg_flags & NLM_F_ACK || err)
			netlink_ack(skb, nlh, err, &extack);

skip:
		msglen = NLMSG_ALIGN(nlh->nlmsg_len);
		अगर (msglen > skb->len)
			msglen = skb->len;
		skb_pull(skb, msglen);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(netlink_rcv_skb);

/**
 * nlmsg_notअगरy - send a notअगरication netlink message
 * @sk: netlink socket to use
 * @skb: notअगरication message
 * @portid: destination netlink portid क्रम reports or 0
 * @group: destination multicast group or 0
 * @report: 1 to report back, 0 to disable
 * @flags: allocation flags
 */
पूर्णांक nlmsg_notअगरy(काष्ठा sock *sk, काष्ठा sk_buff *skb, u32 portid,
		 अचिन्हित पूर्णांक group, पूर्णांक report, gfp_t flags)
अणु
	पूर्णांक err = 0;

	अगर (group) अणु
		पूर्णांक exclude_portid = 0;

		अगर (report) अणु
			refcount_inc(&skb->users);
			exclude_portid = portid;
		पूर्ण

		/* errors reported via destination sk->sk_err, but propagate
		 * delivery errors अगर NETLINK_BROADCAST_ERROR flag is set */
		err = nlmsg_multicast(sk, skb, exclude_portid, group, flags);
	पूर्ण

	अगर (report) अणु
		पूर्णांक err2;

		err2 = nlmsg_unicast(sk, skb, portid);
		अगर (!err || err == -ESRCH)
			err = err2;
	पूर्ण

	वापस err;
पूर्ण
EXPORT_SYMBOL(nlmsg_notअगरy);

#अगर_घोषित CONFIG_PROC_FS
काष्ठा nl_seq_iter अणु
	काष्ठा seq_net_निजी p;
	काष्ठा rhashtable_iter hti;
	पूर्णांक link;
पूर्ण;

अटल व्योम netlink_walk_start(काष्ठा nl_seq_iter *iter)
अणु
	rhashtable_walk_enter(&nl_table[iter->link].hash, &iter->hti);
	rhashtable_walk_start(&iter->hti);
पूर्ण

अटल व्योम netlink_walk_stop(काष्ठा nl_seq_iter *iter)
अणु
	rhashtable_walk_stop(&iter->hti);
	rhashtable_walk_निकास(&iter->hti);
पूर्ण

अटल व्योम *__netlink_seq_next(काष्ठा seq_file *seq)
अणु
	काष्ठा nl_seq_iter *iter = seq->निजी;
	काष्ठा netlink_sock *nlk;

	करो अणु
		क्रम (;;) अणु
			nlk = rhashtable_walk_next(&iter->hti);

			अगर (IS_ERR(nlk)) अणु
				अगर (PTR_ERR(nlk) == -EAGAIN)
					जारी;

				वापस nlk;
			पूर्ण

			अगर (nlk)
				अवरोध;

			netlink_walk_stop(iter);
			अगर (++iter->link >= MAX_LINKS)
				वापस शून्य;

			netlink_walk_start(iter);
		पूर्ण
	पूर्ण जबतक (sock_net(&nlk->sk) != seq_file_net(seq));

	वापस nlk;
पूर्ण

अटल व्योम *netlink_seq_start(काष्ठा seq_file *seq, loff_t *posp)
	__acquires(RCU)
अणु
	काष्ठा nl_seq_iter *iter = seq->निजी;
	व्योम *obj = SEQ_START_TOKEN;
	loff_t pos;

	iter->link = 0;

	netlink_walk_start(iter);

	क्रम (pos = *posp; pos && obj && !IS_ERR(obj); pos--)
		obj = __netlink_seq_next(seq);

	वापस obj;
पूर्ण

अटल व्योम *netlink_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस __netlink_seq_next(seq);
पूर्ण

अटल व्योम netlink_native_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा nl_seq_iter *iter = seq->निजी;

	अगर (iter->link >= MAX_LINKS)
		वापस;

	netlink_walk_stop(iter);
पूर्ण


अटल पूर्णांक netlink_native_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq,
			 "sk               Eth Pid        Groups   "
			 "Rmem     Wmem     Dump  Locks    Drops    Inode\n");
	पूर्ण अन्यथा अणु
		काष्ठा sock *s = v;
		काष्ठा netlink_sock *nlk = nlk_sk(s);

		seq_म_लिखो(seq, "%pK %-3d %-10u %08x %-8d %-8d %-5d %-8d %-8u %-8lu\n",
			   s,
			   s->sk_protocol,
			   nlk->portid,
			   nlk->groups ? (u32)nlk->groups[0] : 0,
			   sk_rmem_alloc_get(s),
			   sk_wmem_alloc_get(s),
			   nlk->cb_running,
			   refcount_पढ़ो(&s->sk_refcnt),
			   atomic_पढ़ो(&s->sk_drops),
			   sock_i_ino(s)
			);

	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BPF_SYSCALL
काष्ठा bpf_iter__netlink अणु
	__bpf_md_ptr(काष्ठा bpf_iter_meta *, meta);
	__bpf_md_ptr(काष्ठा netlink_sock *, sk);
पूर्ण;

DEFINE_BPF_ITER_FUNC(netlink, काष्ठा bpf_iter_meta *meta, काष्ठा netlink_sock *sk)

अटल पूर्णांक netlink_prog_seq_show(काष्ठा bpf_prog *prog,
				  काष्ठा bpf_iter_meta *meta,
				  व्योम *v)
अणु
	काष्ठा bpf_iter__netlink ctx;

	meta->seq_num--;  /* skip SEQ_START_TOKEN */
	ctx.meta = meta;
	ctx.sk = nlk_sk((काष्ठा sock *)v);
	वापस bpf_iter_run_prog(prog, &ctx);
पूर्ण

अटल पूर्णांक netlink_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	meta.seq = seq;
	prog = bpf_iter_get_info(&meta, false);
	अगर (!prog)
		वापस netlink_native_seq_show(seq, v);

	अगर (v != SEQ_START_TOKEN)
		वापस netlink_prog_seq_show(prog, &meta, v);

	वापस 0;
पूर्ण

अटल व्योम netlink_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा bpf_iter_meta meta;
	काष्ठा bpf_prog *prog;

	अगर (!v) अणु
		meta.seq = seq;
		prog = bpf_iter_get_info(&meta, true);
		अगर (prog)
			(व्योम)netlink_prog_seq_show(prog, &meta, v);
	पूर्ण

	netlink_native_seq_stop(seq, v);
पूर्ण
#अन्यथा
अटल पूर्णांक netlink_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	वापस netlink_native_seq_show(seq, v);
पूर्ण

अटल व्योम netlink_seq_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
	netlink_native_seq_stop(seq, v);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा seq_operations netlink_seq_ops = अणु
	.start  = netlink_seq_start,
	.next   = netlink_seq_next,
	.stop   = netlink_seq_stop,
	.show   = netlink_seq_show,
पूर्ण;
#पूर्ण_अगर

पूर्णांक netlink_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&netlink_chain, nb);
पूर्ण
EXPORT_SYMBOL(netlink_रेजिस्टर_notअगरier);

पूर्णांक netlink_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&netlink_chain, nb);
पूर्ण
EXPORT_SYMBOL(netlink_unरेजिस्टर_notअगरier);

अटल स्थिर काष्ठा proto_ops netlink_ops = अणु
	.family =	PF_NETLINK,
	.owner =	THIS_MODULE,
	.release =	netlink_release,
	.bind =		netlink_bind,
	.connect =	netlink_connect,
	.socketpair =	sock_no_socketpair,
	.accept =	sock_no_accept,
	.getname =	netlink_getname,
	.poll =		datagram_poll,
	.ioctl =	netlink_ioctl,
	.listen =	sock_no_listen,
	.shutकरोwn =	sock_no_shutकरोwn,
	.setsockopt =	netlink_setsockopt,
	.माला_लोockopt =	netlink_माला_लोockopt,
	.sendmsg =	netlink_sendmsg,
	.recvmsg =	netlink_recvmsg,
	.mmap =		sock_no_mmap,
	.sendpage =	sock_no_sendpage,
पूर्ण;

अटल स्थिर काष्ठा net_proto_family netlink_family_ops = अणु
	.family = PF_NETLINK,
	.create = netlink_create,
	.owner	= THIS_MODULE,	/* क्रम consistency 8) */
पूर्ण;

अटल पूर्णांक __net_init netlink_net_init(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	अगर (!proc_create_net("netlink", 0, net->proc_net, &netlink_seq_ops,
			माप(काष्ठा nl_seq_iter)))
		वापस -ENOMEM;
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __net_निकास netlink_net_निकास(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_PROC_FS
	हटाओ_proc_entry("netlink", net->proc_net);
#पूर्ण_अगर
पूर्ण

अटल व्योम __init netlink_add_usersock_entry(व्योम)
अणु
	काष्ठा listeners *listeners;
	पूर्णांक groups = 32;

	listeners = kzalloc(माप(*listeners) + NLGRPSZ(groups), GFP_KERNEL);
	अगर (!listeners)
		panic("netlink_add_usersock_entry: Cannot allocate listeners\n");

	netlink_table_grab();

	nl_table[NETLINK_USERSOCK].groups = groups;
	rcu_assign_poपूर्णांकer(nl_table[NETLINK_USERSOCK].listeners, listeners);
	nl_table[NETLINK_USERSOCK].module = THIS_MODULE;
	nl_table[NETLINK_USERSOCK].रेजिस्टरed = 1;
	nl_table[NETLINK_USERSOCK].flags = NL_CFG_F_NONROOT_SEND;

	netlink_table_ungrab();
पूर्ण

अटल काष्ठा pernet_operations __net_initdata netlink_net_ops = अणु
	.init = netlink_net_init,
	.निकास = netlink_net_निकास,
पूर्ण;

अटल अंतरभूत u32 netlink_hash(स्थिर व्योम *data, u32 len, u32 seed)
अणु
	स्थिर काष्ठा netlink_sock *nlk = data;
	काष्ठा netlink_compare_arg arg;

	netlink_compare_arg_init(&arg, sock_net(&nlk->sk), nlk->portid);
	वापस jhash2((u32 *)&arg, netlink_compare_arg_len / माप(u32), seed);
पूर्ण

अटल स्थिर काष्ठा rhashtable_params netlink_rhashtable_params = अणु
	.head_offset = दुरत्व(काष्ठा netlink_sock, node),
	.key_len = netlink_compare_arg_len,
	.obj_hashfn = netlink_hash,
	.obj_cmpfn = netlink_compare,
	.स्वतःmatic_shrinking = true,
पूर्ण;

#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
BTF_ID_LIST(btf_netlink_sock_id)
BTF_ID(काष्ठा, netlink_sock)

अटल स्थिर काष्ठा bpf_iter_seq_info netlink_seq_info = अणु
	.seq_ops		= &netlink_seq_ops,
	.init_seq_निजी	= bpf_iter_init_seq_net,
	.fini_seq_निजी	= bpf_iter_fini_seq_net,
	.seq_priv_size		= माप(काष्ठा nl_seq_iter),
पूर्ण;

अटल काष्ठा bpf_iter_reg netlink_reg_info = अणु
	.target			= "netlink",
	.ctx_arg_info_size	= 1,
	.ctx_arg_info		= अणु
		अणु दुरत्व(काष्ठा bpf_iter__netlink, sk),
		  PTR_TO_BTF_ID_OR_शून्य पूर्ण,
	पूर्ण,
	.seq_info		= &netlink_seq_info,
पूर्ण;

अटल पूर्णांक __init bpf_iter_रेजिस्टर(व्योम)
अणु
	netlink_reg_info.ctx_arg_info[0].btf_id = *btf_netlink_sock_id;
	वापस bpf_iter_reg_target(&netlink_reg_info);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init netlink_proto_init(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक err = proto_रेजिस्टर(&netlink_proto, 0);

	अगर (err != 0)
		जाओ out;

#अगर defined(CONFIG_BPF_SYSCALL) && defined(CONFIG_PROC_FS)
	err = bpf_iter_रेजिस्टर();
	अगर (err)
		जाओ out;
#पूर्ण_अगर

	BUILD_BUG_ON(माप(काष्ठा netlink_skb_parms) > माप_field(काष्ठा sk_buff, cb));

	nl_table = kसुस्मृति(MAX_LINKS, माप(*nl_table), GFP_KERNEL);
	अगर (!nl_table)
		जाओ panic;

	क्रम (i = 0; i < MAX_LINKS; i++) अणु
		अगर (rhashtable_init(&nl_table[i].hash,
				    &netlink_rhashtable_params) < 0) अणु
			जबतक (--i > 0)
				rhashtable_destroy(&nl_table[i].hash);
			kमुक्त(nl_table);
			जाओ panic;
		पूर्ण
	पूर्ण

	netlink_add_usersock_entry();

	sock_रेजिस्टर(&netlink_family_ops);
	रेजिस्टर_pernet_subsys(&netlink_net_ops);
	रेजिस्टर_pernet_subsys(&netlink_tap_net_ops);
	/* The netlink device handler may be needed early. */
	rtnetlink_init();
out:
	वापस err;
panic:
	panic("netlink_init: Cannot allocate nl_table\n");
पूर्ण

core_initcall(netlink_proto_init);
