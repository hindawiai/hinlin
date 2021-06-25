<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Operations on the network namespace
 */
#अगर_अघोषित __NET_NET_NAMESPACE_H
#घोषणा __NET_NET_NAMESPACE_H

#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/list.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/uidgid.h>

#समावेश <net/flow.h>
#समावेश <net/netns/core.h>
#समावेश <net/netns/mib.h>
#समावेश <net/netns/unix.h>
#समावेश <net/netns/packet.h>
#समावेश <net/netns/ipv4.h>
#समावेश <net/netns/ipv6.h>
#समावेश <net/netns/nexthop.h>
#समावेश <net/netns/ieee802154_6lowpan.h>
#समावेश <net/netns/sctp.h>
#समावेश <net/netns/netfilter.h>
#समावेश <net/netns/x_tables.h>
#अगर defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
#समावेश <net/netns/conntrack.h>
#पूर्ण_अगर
#समावेश <net/netns/nftables.h>
#समावेश <net/netns/xfrm.h>
#समावेश <net/netns/mpls.h>
#समावेश <net/netns/can.h>
#समावेश <net/netns/xdp.h>
#समावेश <net/netns/bpf.h>
#समावेश <linux/ns_common.h>
#समावेश <linux/idr.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/notअगरier.h>

काष्ठा user_namespace;
काष्ठा proc_dir_entry;
काष्ठा net_device;
काष्ठा sock;
काष्ठा ctl_table_header;
काष्ठा net_generic;
काष्ठा uevent_sock;
काष्ठा netns_ipvs;
काष्ठा bpf_prog;


#घोषणा NETDEV_HASHBITS    8
#घोषणा NETDEV_HASHENTRIES (1 << NETDEV_HASHBITS)

काष्ठा net अणु
	/* First cache line can be often dirtied.
	 * Do not place here पढ़ो-mostly fields.
	 */
	refcount_t		passive;	/* To decide when the network
						 * namespace should be मुक्तd.
						 */
	spinlock_t		rules_mod_lock;

	अचिन्हित पूर्णांक		dev_unreg_count;

	अचिन्हित पूर्णांक		dev_base_seq;	/* रक्षित by rtnl_mutex */
	पूर्णांक			अगरindex;

	spinlock_t		nsid_lock;
	atomic_t		fnhe_genid;

	काष्ठा list_head	list;		/* list of network namespaces */
	काष्ठा list_head	निकास_list;	/* To linked to call pernet निकास
						 * methods on dead net (
						 * pernet_ops_rwsem पढ़ो locked),
						 * or to unरेजिस्टर pernet ops
						 * (pernet_ops_rwsem ग_लिखो locked).
						 */
	काष्ठा llist_node	cleanup_list;	/* namespaces on death row */

#अगर_घोषित CONFIG_KEYS
	काष्ठा key_tag		*key_करोमुख्य;	/* Key करोमुख्य of operation tag */
#पूर्ण_अगर
	काष्ठा user_namespace   *user_ns;	/* Owning user namespace */
	काष्ठा ucounts		*ucounts;
	काष्ठा idr		netns_ids;

	काष्ठा ns_common	ns;

	काष्ठा list_head 	dev_base_head;
	काष्ठा proc_dir_entry 	*proc_net;
	काष्ठा proc_dir_entry 	*proc_net_stat;

#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table_set	sysctls;
#पूर्ण_अगर

	काष्ठा sock 		*rtnl;			/* rtnetlink socket */
	काष्ठा sock		*genl_sock;

	काष्ठा uevent_sock	*uevent_sock;		/* uevent socket */

	काष्ठा hlist_head 	*dev_name_head;
	काष्ठा hlist_head	*dev_index_head;
	काष्ठा raw_notअगरier_head	netdev_chain;

	/* Note that @hash_mix can be पढ़ो millions बार per second,
	 * it is critical that it is on a पढ़ो_mostly cache line.
	 */
	u32			hash_mix;

	काष्ठा net_device       *loopback_dev;          /* The loopback */

	/* core fib_rules */
	काष्ठा list_head	rules_ops;

	काष्ठा netns_core	core;
	काष्ठा netns_mib	mib;
	काष्ठा netns_packet	packet;
	काष्ठा netns_unix	unx;
	काष्ठा netns_nexthop	nexthop;
	काष्ठा netns_ipv4	ipv4;
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा netns_ipv6	ipv6;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_IEEE802154_6LOWPAN)
	काष्ठा netns_ieee802154_lowpan	ieee802154_lowpan;
#पूर्ण_अगर
#अगर defined(CONFIG_IP_SCTP) || defined(CONFIG_IP_SCTP_MODULE)
	काष्ठा netns_sctp	sctp;
#पूर्ण_अगर
#अगर_घोषित CONFIG_NETFILTER
	काष्ठा netns_nf		nf;
	काष्ठा netns_xt		xt;
#अगर defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	काष्ठा netns_ct		ct;
#पूर्ण_अगर
#अगर defined(CONFIG_NF_TABLES) || defined(CONFIG_NF_TABLES_MODULE)
	काष्ठा netns_nftables	nft;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_WEXT_CORE
	काष्ठा sk_buff_head	wext_nlevents;
#पूर्ण_अगर
	काष्ठा net_generic __rcu	*gen;

	/* Used to store attached BPF programs */
	काष्ठा netns_bpf	bpf;

	/* Note : following काष्ठाs are cache line aligned */
#अगर_घोषित CONFIG_XFRM
	काष्ठा netns_xfrm	xfrm;
#पूर्ण_अगर

	u64			net_cookie; /* written once */

#अगर IS_ENABLED(CONFIG_IP_VS)
	काष्ठा netns_ipvs	*ipvs;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_MPLS)
	काष्ठा netns_mpls	mpls;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CAN)
	काष्ठा netns_can	can;
#पूर्ण_अगर
#अगर_घोषित CONFIG_XDP_SOCKETS
	काष्ठा netns_xdp	xdp;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CRYPTO_USER)
	काष्ठा sock		*crypto_nlsk;
#पूर्ण_अगर
	काष्ठा sock		*diag_nlsk;
पूर्ण __अक्रमomize_layout;

#समावेश <linux/seq_file_net.h>

/* Init's network namespace */
बाह्य काष्ठा net init_net;

#अगर_घोषित CONFIG_NET_NS
काष्ठा net *copy_net_ns(अचिन्हित दीर्घ flags, काष्ठा user_namespace *user_ns,
			काष्ठा net *old_net);

व्योम net_ns_get_ownership(स्थिर काष्ठा net *net, kuid_t *uid, kgid_t *gid);

व्योम net_ns_barrier(व्योम);

काष्ठा ns_common *get_net_ns(काष्ठा ns_common *ns);
काष्ठा net *get_net_ns_by_fd(पूर्णांक fd);
#अन्यथा /* CONFIG_NET_NS */
#समावेश <linux/sched.h>
#समावेश <linux/nsproxy.h>
अटल अंतरभूत काष्ठा net *copy_net_ns(अचिन्हित दीर्घ flags,
	काष्ठा user_namespace *user_ns, काष्ठा net *old_net)
अणु
	अगर (flags & CLONE_NEWNET)
		वापस ERR_PTR(-EINVAL);
	वापस old_net;
पूर्ण

अटल अंतरभूत व्योम net_ns_get_ownership(स्थिर काष्ठा net *net,
					kuid_t *uid, kgid_t *gid)
अणु
	*uid = GLOBAL_ROOT_UID;
	*gid = GLOBAL_ROOT_GID;
पूर्ण

अटल अंतरभूत व्योम net_ns_barrier(व्योम) अणुपूर्ण

अटल अंतरभूत काष्ठा ns_common *get_net_ns(काष्ठा ns_common *ns)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल अंतरभूत काष्ठा net *get_net_ns_by_fd(पूर्णांक fd)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_NS */


बाह्य काष्ठा list_head net_namespace_list;

काष्ठा net *get_net_ns_by_pid(pid_t pid);

#अगर_घोषित CONFIG_SYSCTL
व्योम ipx_रेजिस्टर_sysctl(व्योम);
व्योम ipx_unरेजिस्टर_sysctl(व्योम);
#अन्यथा
#घोषणा ipx_रेजिस्टर_sysctl()
#घोषणा ipx_unरेजिस्टर_sysctl()
#पूर्ण_अगर

#अगर_घोषित CONFIG_NET_NS
व्योम __put_net(काष्ठा net *net);

अटल अंतरभूत काष्ठा net *get_net(काष्ठा net *net)
अणु
	refcount_inc(&net->ns.count);
	वापस net;
पूर्ण

अटल अंतरभूत काष्ठा net *maybe_get_net(काष्ठा net *net)
अणु
	/* Used when we know काष्ठा net exists but we
	 * aren't guaranteed a previous reference count
	 * exists.  If the reference count is zero this
	 * function fails and वापसs शून्य.
	 */
	अगर (!refcount_inc_not_zero(&net->ns.count))
		net = शून्य;
	वापस net;
पूर्ण

अटल अंतरभूत व्योम put_net(काष्ठा net *net)
अणु
	अगर (refcount_dec_and_test(&net->ns.count))
		__put_net(net);
पूर्ण

अटल अंतरभूत
पूर्णांक net_eq(स्थिर काष्ठा net *net1, स्थिर काष्ठा net *net2)
अणु
	वापस net1 == net2;
पूर्ण

अटल अंतरभूत पूर्णांक check_net(स्थिर काष्ठा net *net)
अणु
	वापस refcount_पढ़ो(&net->ns.count) != 0;
पूर्ण

व्योम net_drop_ns(व्योम *);

#अन्यथा

अटल अंतरभूत काष्ठा net *get_net(काष्ठा net *net)
अणु
	वापस net;
पूर्ण

अटल अंतरभूत व्योम put_net(काष्ठा net *net)
अणु
पूर्ण

अटल अंतरभूत काष्ठा net *maybe_get_net(काष्ठा net *net)
अणु
	वापस net;
पूर्ण

अटल अंतरभूत
पूर्णांक net_eq(स्थिर काष्ठा net *net1, स्थिर काष्ठा net *net2)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक check_net(स्थिर काष्ठा net *net)
अणु
	वापस 1;
पूर्ण

#घोषणा net_drop_ns शून्य
#पूर्ण_अगर


प्रकार काष्ठा अणु
#अगर_घोषित CONFIG_NET_NS
	काष्ठा net *net;
#पूर्ण_अगर
पूर्ण possible_net_t;

अटल अंतरभूत व्योम ग_लिखो_pnet(possible_net_t *pnet, काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_NET_NS
	pnet->net = net;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा net *पढ़ो_pnet(स्थिर possible_net_t *pnet)
अणु
#अगर_घोषित CONFIG_NET_NS
	वापस pnet->net;
#अन्यथा
	वापस &init_net;
#पूर्ण_अगर
पूर्ण

/* Protected by net_rwsem */
#घोषणा क्रम_each_net(VAR)				\
	list_क्रम_each_entry(VAR, &net_namespace_list, list)
#घोषणा क्रम_each_net_जारी_reverse(VAR)		\
	list_क्रम_each_entry_जारी_reverse(VAR, &net_namespace_list, list)
#घोषणा क्रम_each_net_rcu(VAR)				\
	list_क्रम_each_entry_rcu(VAR, &net_namespace_list, list)

#अगर_घोषित CONFIG_NET_NS
#घोषणा __net_init
#घोषणा __net_निकास
#घोषणा __net_initdata
#घोषणा __net_initस्थिर
#अन्यथा
#घोषणा __net_init	__init
#घोषणा __net_निकास	__ref
#घोषणा __net_initdata	__initdata
#घोषणा __net_initस्थिर	__initस्थिर
#पूर्ण_अगर

पूर्णांक peernet2id_alloc(काष्ठा net *net, काष्ठा net *peer, gfp_t gfp);
पूर्णांक peernet2id(स्थिर काष्ठा net *net, काष्ठा net *peer);
bool peernet_has_id(स्थिर काष्ठा net *net, काष्ठा net *peer);
काष्ठा net *get_net_ns_by_id(स्थिर काष्ठा net *net, पूर्णांक id);

काष्ठा pernet_operations अणु
	काष्ठा list_head list;
	/*
	 * Below methods are called without any exclusive locks.
	 * More than one net may be स्थिरructed and deकाष्ठाed
	 * in parallel on several cpus. Every pernet_operations
	 * have to keep in mind all other pernet_operations and
	 * to पूर्णांकroduce a locking, अगर they share common resources.
	 *
	 * The only समय they are called with exclusive lock is
	 * from रेजिस्टर_pernet_subsys(), unरेजिस्टर_pernet_subsys()
	 * रेजिस्टर_pernet_device() and unरेजिस्टर_pernet_device().
	 *
	 * Exit methods using blocking RCU primitives, such as
	 * synchronize_rcu(), should be implemented via निकास_batch.
	 * Then, deकाष्ठाion of a group of net requires single
	 * synchronize_rcu() related to these pernet_operations,
	 * instead of separate synchronize_rcu() क्रम every net.
	 * Please, aव्योम synchronize_rcu() at all, where it's possible.
	 *
	 * Note that a combination of pre_निकास() and निकास() can
	 * be used, since a synchronize_rcu() is guaranteed between
	 * the calls.
	 */
	पूर्णांक (*init)(काष्ठा net *net);
	व्योम (*pre_निकास)(काष्ठा net *net);
	व्योम (*निकास)(काष्ठा net *net);
	व्योम (*निकास_batch)(काष्ठा list_head *net_निकास_list);
	अचिन्हित पूर्णांक *id;
	माप_प्रकार size;
पूर्ण;

/*
 * Use these carefully.  If you implement a network device and it
 * needs per network namespace operations use device pernet operations,
 * otherwise use pernet subsys operations.
 *
 * Network पूर्णांकerfaces need to be हटाओd from a dying netns _beक्रमe_
 * subsys notअगरiers can be called, as most of the network code cleanup
 * (which is करोne from subsys notअगरiers) runs with the assumption that
 * dev_हटाओ_pack has been called so no new packets will arrive during
 * and after the cleanup functions have been called.  dev_हटाओ_pack
 * is not per namespace so instead the guarantee of no more packets
 * arriving in a network namespace is provided by ensuring that all
 * network devices and all sockets have left the network namespace
 * beक्रमe the cleanup methods are called.
 *
 * For the दीर्घest समय the ipv4 icmp code was रेजिस्टरed as a pernet
 * device which caused kernel oops, and panics during network
 * namespace cleanup.   So please करोn't get this wrong.
 */
पूर्णांक रेजिस्टर_pernet_subsys(काष्ठा pernet_operations *);
व्योम unरेजिस्टर_pernet_subsys(काष्ठा pernet_operations *);
पूर्णांक रेजिस्टर_pernet_device(काष्ठा pernet_operations *);
व्योम unरेजिस्टर_pernet_device(काष्ठा pernet_operations *);

काष्ठा ctl_table;

#अगर_घोषित CONFIG_SYSCTL
पूर्णांक net_sysctl_init(व्योम);
काष्ठा ctl_table_header *रेजिस्टर_net_sysctl(काष्ठा net *net, स्थिर अक्षर *path,
					     काष्ठा ctl_table *table);
व्योम unरेजिस्टर_net_sysctl_table(काष्ठा ctl_table_header *header);
#अन्यथा
अटल अंतरभूत पूर्णांक net_sysctl_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत काष्ठा ctl_table_header *रेजिस्टर_net_sysctl(काष्ठा net *net,
	स्थिर अक्षर *path, काष्ठा ctl_table *table)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_net_sysctl_table(काष्ठा ctl_table_header *header)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक rt_genid_ipv4(स्थिर काष्ठा net *net)
अणु
	वापस atomic_पढ़ो(&net->ipv4.rt_genid);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत पूर्णांक rt_genid_ipv6(स्थिर काष्ठा net *net)
अणु
	वापस atomic_पढ़ो(&net->ipv6.fib6_sernum);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम rt_genid_bump_ipv4(काष्ठा net *net)
अणु
	atomic_inc(&net->ipv4.rt_genid);
पूर्ण

बाह्य व्योम (*__fib6_flush_trees)(काष्ठा net *net);
अटल अंतरभूत व्योम rt_genid_bump_ipv6(काष्ठा net *net)
अणु
	अगर (__fib6_flush_trees)
		__fib6_flush_trees(net);
पूर्ण

#अगर IS_ENABLED(CONFIG_IEEE802154_6LOWPAN)
अटल अंतरभूत काष्ठा netns_ieee802154_lowpan *
net_ieee802154_lowpan(काष्ठा net *net)
अणु
	वापस &net->ieee802154_lowpan;
पूर्ण
#पूर्ण_अगर

/* For callers who करोn't really care about whether it's IPv4 or IPv6 */
अटल अंतरभूत व्योम rt_genid_bump_all(काष्ठा net *net)
अणु
	rt_genid_bump_ipv4(net);
	rt_genid_bump_ipv6(net);
पूर्ण

अटल अंतरभूत पूर्णांक fnhe_genid(स्थिर काष्ठा net *net)
अणु
	वापस atomic_पढ़ो(&net->fnhe_genid);
पूर्ण

अटल अंतरभूत व्योम fnhe_genid_bump(काष्ठा net *net)
अणु
	atomic_inc(&net->fnhe_genid);
पूर्ण

#पूर्ण_अगर /* __NET_NET_NAMESPACE_H */
