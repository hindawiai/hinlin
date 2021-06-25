<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	NET3	IP device support routines.
 *
 *	Derived from the IP parts of dev.c 1.0.19
 * 		Authors:	Ross Biro
 *				Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *				Mark Evans, <evansmp@uhura.aston.ac.uk>
 *
 *	Additional Authors:
 *		Alan Cox, <gw4pts@gw4pts.ampr.org>
 *		Alexey Kuznetsov, <kuznet@ms2.inr.ac.ru>
 *
 *	Changes:
 *		Alexey Kuznetsov:	pa_* fields are replaced with अगरaddr
 *					lists.
 *		Cyrus Durgin:		updated क्रम kmod
 *		Matthias Andree:	in devinet_ioctl, compare label and
 *					address (4.4BSD alias style support),
 *					fall back to comparing just the label
 *					अगर no match found.
 */


#समावेश <linux/uaccess.h>
#समावेश <linux/bitops.h>
#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/in.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_addr.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>
#अगर_घोषित CONFIG_SYSCTL
#समावेश <linux/sysctl.h>
#पूर्ण_अगर
#समावेश <linux/kmod.h>
#समावेश <linux/netconf.h>

#समावेश <net/arp.h>
#समावेश <net/ip.h>
#समावेश <net/route.h>
#समावेश <net/ip_fib.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/net_namespace.h>
#समावेश <net/addrconf.h>

#घोषणा IPV6ONLY_FLAGS	\
		(IFA_F_NODAD | IFA_F_OPTIMISTIC | IFA_F_DADFAILED | \
		 IFA_F_HOMEADDRESS | IFA_F_TENTATIVE | \
		 IFA_F_MANAGETEMPADDR | IFA_F_STABLE_PRIVACY)

अटल काष्ठा ipv4_devconf ipv4_devconf = अणु
	.data = अणु
		[IPV4_DEVCONF_ACCEPT_REसूचीECTS - 1] = 1,
		[IPV4_DEVCONF_SEND_REसूचीECTS - 1] = 1,
		[IPV4_DEVCONF_SECURE_REसूचीECTS - 1] = 1,
		[IPV4_DEVCONF_SHARED_MEDIA - 1] = 1,
		[IPV4_DEVCONF_IGMPV2_UNSOLICITED_REPORT_INTERVAL - 1] = 10000 /*ms*/,
		[IPV4_DEVCONF_IGMPV3_UNSOLICITED_REPORT_INTERVAL - 1] =  1000 /*ms*/,
	पूर्ण,
पूर्ण;

अटल काष्ठा ipv4_devconf ipv4_devconf_dflt = अणु
	.data = अणु
		[IPV4_DEVCONF_ACCEPT_REसूचीECTS - 1] = 1,
		[IPV4_DEVCONF_SEND_REसूचीECTS - 1] = 1,
		[IPV4_DEVCONF_SECURE_REसूचीECTS - 1] = 1,
		[IPV4_DEVCONF_SHARED_MEDIA - 1] = 1,
		[IPV4_DEVCONF_ACCEPT_SOURCE_ROUTE - 1] = 1,
		[IPV4_DEVCONF_IGMPV2_UNSOLICITED_REPORT_INTERVAL - 1] = 10000 /*ms*/,
		[IPV4_DEVCONF_IGMPV3_UNSOLICITED_REPORT_INTERVAL - 1] =  1000 /*ms*/,
	पूर्ण,
पूर्ण;

#घोषणा IPV4_DEVCONF_DFLT(net, attr) \
	IPV4_DEVCONF((*net->ipv4.devconf_dflt), attr)

अटल स्थिर काष्ठा nla_policy अगरa_ipv4_policy[IFA_MAX+1] = अणु
	[IFA_LOCAL]     	= अणु .type = NLA_U32 पूर्ण,
	[IFA_ADDRESS]   	= अणु .type = NLA_U32 पूर्ण,
	[IFA_BROADCAST] 	= अणु .type = NLA_U32 पूर्ण,
	[IFA_LABEL]     	= अणु .type = NLA_STRING, .len = IFNAMSIZ - 1 पूर्ण,
	[IFA_CACHEINFO]		= अणु .len = माप(काष्ठा अगरa_cacheinfo) पूर्ण,
	[IFA_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[IFA_RT_PRIORITY]	= अणु .type = NLA_U32 पूर्ण,
	[IFA_TARGET_NETNSID]	= अणु .type = NLA_S32 पूर्ण,
पूर्ण;

काष्ठा inet_fill_args अणु
	u32 portid;
	u32 seq;
	पूर्णांक event;
	अचिन्हित पूर्णांक flags;
	पूर्णांक netnsid;
	पूर्णांक अगरindex;
पूर्ण;

#घोषणा IN4_ADDR_HSIZE_SHIFT	8
#घोषणा IN4_ADDR_HSIZE		(1U << IN4_ADDR_HSIZE_SHIFT)

अटल काष्ठा hlist_head inet_addr_lst[IN4_ADDR_HSIZE];

अटल u32 inet_addr_hash(स्थिर काष्ठा net *net, __be32 addr)
अणु
	u32 val = (__क्रमce u32) addr ^ net_hash_mix(net);

	वापस hash_32(val, IN4_ADDR_HSIZE_SHIFT);
पूर्ण

अटल व्योम inet_hash_insert(काष्ठा net *net, काष्ठा in_अगरaddr *अगरa)
अणु
	u32 hash = inet_addr_hash(net, अगरa->अगरa_local);

	ASSERT_RTNL();
	hlist_add_head_rcu(&अगरa->hash, &inet_addr_lst[hash]);
पूर्ण

अटल व्योम inet_hash_हटाओ(काष्ठा in_अगरaddr *अगरa)
अणु
	ASSERT_RTNL();
	hlist_del_init_rcu(&अगरa->hash);
पूर्ण

/**
 * __ip_dev_find - find the first device with a given source address.
 * @net: the net namespace
 * @addr: the source address
 * @devref: अगर true, take a reference on the found device
 *
 * If a caller uses devref=false, it should be रक्षित by RCU, or RTNL
 */
काष्ठा net_device *__ip_dev_find(काष्ठा net *net, __be32 addr, bool devref)
अणु
	काष्ठा net_device *result = शून्य;
	काष्ठा in_अगरaddr *अगरa;

	rcu_पढ़ो_lock();
	अगरa = inet_lookup_अगरaddr_rcu(net, addr);
	अगर (!अगरa) अणु
		काष्ठा flowi4 fl4 = अणु .daddr = addr पूर्ण;
		काष्ठा fib_result res = अणु 0 पूर्ण;
		काष्ठा fib_table *local;

		/* Fallback to FIB local table so that communication
		 * over loopback subnets work.
		 */
		local = fib_get_table(net, RT_TABLE_LOCAL);
		अगर (local &&
		    !fib_table_lookup(local, &fl4, &res, FIB_LOOKUP_NOREF) &&
		    res.type == RTN_LOCAL)
			result = FIB_RES_DEV(res);
	पूर्ण अन्यथा अणु
		result = अगरa->अगरa_dev->dev;
	पूर्ण
	अगर (result && devref)
		dev_hold(result);
	rcu_पढ़ो_unlock();
	वापस result;
पूर्ण
EXPORT_SYMBOL(__ip_dev_find);

/* called under RCU lock */
काष्ठा in_अगरaddr *inet_lookup_अगरaddr_rcu(काष्ठा net *net, __be32 addr)
अणु
	u32 hash = inet_addr_hash(net, addr);
	काष्ठा in_अगरaddr *अगरa;

	hlist_क्रम_each_entry_rcu(अगरa, &inet_addr_lst[hash], hash)
		अगर (अगरa->अगरa_local == addr &&
		    net_eq(dev_net(अगरa->अगरa_dev->dev), net))
			वापस अगरa;

	वापस शून्य;
पूर्ण

अटल व्योम rपंचांगsg_अगरa(पूर्णांक event, काष्ठा in_अगरaddr *, काष्ठा nlmsghdr *, u32);

अटल BLOCKING_NOTIFIER_HEAD(inetaddr_chain);
अटल BLOCKING_NOTIFIER_HEAD(inetaddr_validator_chain);
अटल व्योम inet_del_अगरa(काष्ठा in_device *in_dev,
			 काष्ठा in_अगरaddr __rcu **अगरap,
			 पूर्णांक destroy);
#अगर_घोषित CONFIG_SYSCTL
अटल पूर्णांक devinet_sysctl_रेजिस्टर(काष्ठा in_device *idev);
अटल व्योम devinet_sysctl_unरेजिस्टर(काष्ठा in_device *idev);
#अन्यथा
अटल पूर्णांक devinet_sysctl_रेजिस्टर(काष्ठा in_device *idev)
अणु
	वापस 0;
पूर्ण
अटल व्योम devinet_sysctl_unरेजिस्टर(काष्ठा in_device *idev)
अणु
पूर्ण
#पूर्ण_अगर

/* Locks all the inet devices. */

अटल काष्ठा in_अगरaddr *inet_alloc_अगरa(व्योम)
अणु
	वापस kzalloc(माप(काष्ठा in_अगरaddr), GFP_KERNEL);
पूर्ण

अटल व्योम inet_rcu_मुक्त_अगरa(काष्ठा rcu_head *head)
अणु
	काष्ठा in_अगरaddr *अगरa = container_of(head, काष्ठा in_अगरaddr, rcu_head);
	अगर (अगरa->अगरa_dev)
		in_dev_put(अगरa->अगरa_dev);
	kमुक्त(अगरa);
पूर्ण

अटल व्योम inet_मुक्त_अगरa(काष्ठा in_अगरaddr *अगरa)
अणु
	call_rcu(&अगरa->rcu_head, inet_rcu_मुक्त_अगरa);
पूर्ण

व्योम in_dev_finish_destroy(काष्ठा in_device *idev)
अणु
	काष्ठा net_device *dev = idev->dev;

	WARN_ON(idev->अगरa_list);
	WARN_ON(idev->mc_list);
	kमुक्त(rcu_dereference_रक्षित(idev->mc_hash, 1));
#अगर_घोषित NET_REFCNT_DEBUG
	pr_debug("%s: %p=%s\n", __func__, idev, dev ? dev->name : "NIL");
#पूर्ण_अगर
	dev_put(dev);
	अगर (!idev->dead)
		pr_err("Freeing alive in_device %p\n", idev);
	अन्यथा
		kमुक्त(idev);
पूर्ण
EXPORT_SYMBOL(in_dev_finish_destroy);

अटल काष्ठा in_device *inetdev_init(काष्ठा net_device *dev)
अणु
	काष्ठा in_device *in_dev;
	पूर्णांक err = -ENOMEM;

	ASSERT_RTNL();

	in_dev = kzalloc(माप(*in_dev), GFP_KERNEL);
	अगर (!in_dev)
		जाओ out;
	स_नकल(&in_dev->cnf, dev_net(dev)->ipv4.devconf_dflt,
			माप(in_dev->cnf));
	in_dev->cnf.sysctl = शून्य;
	in_dev->dev = dev;
	in_dev->arp_parms = neigh_parms_alloc(dev, &arp_tbl);
	अगर (!in_dev->arp_parms)
		जाओ out_kमुक्त;
	अगर (IPV4_DEVCONF(in_dev->cnf, FORWARDING))
		dev_disable_lro(dev);
	/* Reference in_dev->dev */
	dev_hold(dev);
	/* Account क्रम reference dev->ip_ptr (below) */
	refcount_set(&in_dev->refcnt, 1);

	err = devinet_sysctl_रेजिस्टर(in_dev);
	अगर (err) अणु
		in_dev->dead = 1;
		neigh_parms_release(&arp_tbl, in_dev->arp_parms);
		in_dev_put(in_dev);
		in_dev = शून्य;
		जाओ out;
	पूर्ण
	ip_mc_init_dev(in_dev);
	अगर (dev->flags & IFF_UP)
		ip_mc_up(in_dev);

	/* we can receive as soon as ip_ptr is set -- करो this last */
	rcu_assign_poपूर्णांकer(dev->ip_ptr, in_dev);
out:
	वापस in_dev ?: ERR_PTR(err);
out_kमुक्त:
	kमुक्त(in_dev);
	in_dev = शून्य;
	जाओ out;
पूर्ण

अटल व्योम in_dev_rcu_put(काष्ठा rcu_head *head)
अणु
	काष्ठा in_device *idev = container_of(head, काष्ठा in_device, rcu_head);
	in_dev_put(idev);
पूर्ण

अटल व्योम inetdev_destroy(काष्ठा in_device *in_dev)
अणु
	काष्ठा net_device *dev;
	काष्ठा in_अगरaddr *अगरa;

	ASSERT_RTNL();

	dev = in_dev->dev;

	in_dev->dead = 1;

	ip_mc_destroy_dev(in_dev);

	जबतक ((अगरa = rtnl_dereference(in_dev->अगरa_list)) != शून्य) अणु
		inet_del_अगरa(in_dev, &in_dev->अगरa_list, 0);
		inet_मुक्त_अगरa(अगरa);
	पूर्ण

	RCU_INIT_POINTER(dev->ip_ptr, शून्य);

	devinet_sysctl_unरेजिस्टर(in_dev);
	neigh_parms_release(&arp_tbl, in_dev->arp_parms);
	arp_अगरकरोwn(dev);

	call_rcu(&in_dev->rcu_head, in_dev_rcu_put);
पूर्ण

पूर्णांक inet_addr_onlink(काष्ठा in_device *in_dev, __be32 a, __be32 b)
अणु
	स्थिर काष्ठा in_अगरaddr *अगरa;

	rcu_पढ़ो_lock();
	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अगर (inet_अगरa_match(a, अगरa)) अणु
			अगर (!b || inet_अगरa_match(b, अगरa)) अणु
				rcu_पढ़ो_unlock();
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल व्योम __inet_del_अगरa(काष्ठा in_device *in_dev,
			   काष्ठा in_अगरaddr __rcu **अगरap,
			   पूर्णांक destroy, काष्ठा nlmsghdr *nlh, u32 portid)
अणु
	काष्ठा in_अगरaddr *promote = शून्य;
	काष्ठा in_अगरaddr *अगरa, *अगरa1;
	काष्ठा in_अगरaddr *last_prim;
	काष्ठा in_अगरaddr *prev_prom = शून्य;
	पूर्णांक करो_promote = IN_DEV_PROMOTE_SECONDARIES(in_dev);

	ASSERT_RTNL();

	अगरa1 = rtnl_dereference(*अगरap);
	last_prim = rtnl_dereference(in_dev->अगरa_list);
	अगर (in_dev->dead)
		जाओ no_promotions;

	/* 1. Deleting primary अगरaddr क्रमces deletion all secondaries
	 * unless alias promotion is set
	 **/

	अगर (!(अगरa1->अगरa_flags & IFA_F_SECONDARY)) अणु
		काष्ठा in_अगरaddr __rcu **अगरap1 = &अगरa1->अगरa_next;

		जबतक ((अगरa = rtnl_dereference(*अगरap1)) != शून्य) अणु
			अगर (!(अगरa->अगरa_flags & IFA_F_SECONDARY) &&
			    अगरa1->अगरa_scope <= अगरa->अगरa_scope)
				last_prim = अगरa;

			अगर (!(अगरa->अगरa_flags & IFA_F_SECONDARY) ||
			    अगरa1->अगरa_mask != अगरa->अगरa_mask ||
			    !inet_अगरa_match(अगरa1->अगरa_address, अगरa)) अणु
				अगरap1 = &अगरa->अगरa_next;
				prev_prom = अगरa;
				जारी;
			पूर्ण

			अगर (!करो_promote) अणु
				inet_hash_हटाओ(अगरa);
				*अगरap1 = अगरa->अगरa_next;

				rपंचांगsg_अगरa(RTM_DELADDR, अगरa, nlh, portid);
				blocking_notअगरier_call_chain(&inetaddr_chain,
						NETDEV_DOWN, अगरa);
				inet_मुक्त_अगरa(अगरa);
			पूर्ण अन्यथा अणु
				promote = अगरa;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* On promotion all secondaries from subnet are changing
	 * the primary IP, we must हटाओ all their routes silently
	 * and later to add them back with new prefsrc. Do this
	 * जबतक all addresses are on the device list.
	 */
	क्रम (अगरa = promote; अगरa; अगरa = rtnl_dereference(अगरa->अगरa_next)) अणु
		अगर (अगरa1->अगरa_mask == अगरa->अगरa_mask &&
		    inet_अगरa_match(अगरa1->अगरa_address, अगरa))
			fib_del_अगरaddr(अगरa, अगरa1);
	पूर्ण

no_promotions:
	/* 2. Unlink it */

	*अगरap = अगरa1->अगरa_next;
	inet_hash_हटाओ(अगरa1);

	/* 3. Announce address deletion */

	/* Send message first, then call notअगरier.
	   At first sight, FIB update triggered by notअगरier
	   will refer to alपढ़ोy deleted अगरaddr, that could confuse
	   netlink listeners. It is not true: look, gated sees
	   that route deleted and अगर it still thinks that अगरaddr
	   is valid, it will try to restore deleted routes... Grr.
	   So that, this order is correct.
	 */
	rपंचांगsg_अगरa(RTM_DELADDR, अगरa1, nlh, portid);
	blocking_notअगरier_call_chain(&inetaddr_chain, NETDEV_DOWN, अगरa1);

	अगर (promote) अणु
		काष्ठा in_अगरaddr *next_sec;

		next_sec = rtnl_dereference(promote->अगरa_next);
		अगर (prev_prom) अणु
			काष्ठा in_अगरaddr *last_sec;

			rcu_assign_poपूर्णांकer(prev_prom->अगरa_next, next_sec);

			last_sec = rtnl_dereference(last_prim->अगरa_next);
			rcu_assign_poपूर्णांकer(promote->अगरa_next, last_sec);
			rcu_assign_poपूर्णांकer(last_prim->अगरa_next, promote);
		पूर्ण

		promote->अगरa_flags &= ~IFA_F_SECONDARY;
		rपंचांगsg_अगरa(RTM_NEWADDR, promote, nlh, portid);
		blocking_notअगरier_call_chain(&inetaddr_chain,
				NETDEV_UP, promote);
		क्रम (अगरa = next_sec; अगरa;
		     अगरa = rtnl_dereference(अगरa->अगरa_next)) अणु
			अगर (अगरa1->अगरa_mask != अगरa->अगरa_mask ||
			    !inet_अगरa_match(अगरa1->अगरa_address, अगरa))
					जारी;
			fib_add_अगरaddr(अगरa);
		पूर्ण

	पूर्ण
	अगर (destroy)
		inet_मुक्त_अगरa(अगरa1);
पूर्ण

अटल व्योम inet_del_अगरa(काष्ठा in_device *in_dev,
			 काष्ठा in_अगरaddr __rcu **अगरap,
			 पूर्णांक destroy)
अणु
	__inet_del_अगरa(in_dev, अगरap, destroy, शून्य, 0);
पूर्ण

अटल व्योम check_lअगरeसमय(काष्ठा work_काष्ठा *work);

अटल DECLARE_DELAYED_WORK(check_lअगरeसमय_work, check_lअगरeसमय);

अटल पूर्णांक __inet_insert_अगरa(काष्ठा in_अगरaddr *अगरa, काष्ठा nlmsghdr *nlh,
			     u32 portid, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा in_अगरaddr __rcu **last_primary, **अगरap;
	काष्ठा in_device *in_dev = अगरa->अगरa_dev;
	काष्ठा in_validator_info ivi;
	काष्ठा in_अगरaddr *अगरa1;
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (!अगरa->अगरa_local) अणु
		inet_मुक्त_अगरa(अगरa);
		वापस 0;
	पूर्ण

	अगरa->अगरa_flags &= ~IFA_F_SECONDARY;
	last_primary = &in_dev->अगरa_list;

	/* Don't set IPv6 only flags to IPv4 addresses */
	अगरa->अगरa_flags &= ~IPV6ONLY_FLAGS;

	अगरap = &in_dev->अगरa_list;
	अगरa1 = rtnl_dereference(*अगरap);

	जबतक (अगरa1) अणु
		अगर (!(अगरa1->अगरa_flags & IFA_F_SECONDARY) &&
		    अगरa->अगरa_scope <= अगरa1->अगरa_scope)
			last_primary = &अगरa1->अगरa_next;
		अगर (अगरa1->अगरa_mask == अगरa->अगरa_mask &&
		    inet_अगरa_match(अगरa1->अगरa_address, अगरa)) अणु
			अगर (अगरa1->अगरa_local == अगरa->अगरa_local) अणु
				inet_मुक्त_अगरa(अगरa);
				वापस -EEXIST;
			पूर्ण
			अगर (अगरa1->अगरa_scope != अगरa->अगरa_scope) अणु
				inet_मुक्त_अगरa(अगरa);
				वापस -EINVAL;
			पूर्ण
			अगरa->अगरa_flags |= IFA_F_SECONDARY;
		पूर्ण

		अगरap = &अगरa1->अगरa_next;
		अगरa1 = rtnl_dereference(*अगरap);
	पूर्ण

	/* Allow any devices that wish to रेजिस्टर अगरaddr validtors to weigh
	 * in now, beक्रमe changes are committed.  The rntl lock is serializing
	 * access here, so the state should not change between a validator call
	 * and a final notअगरy on commit.  This isn't invoked on promotion under
	 * the assumption that validators are checking the address itself, and
	 * not the flags.
	 */
	ivi.ivi_addr = अगरa->अगरa_address;
	ivi.ivi_dev = अगरa->अगरa_dev;
	ivi.extack = extack;
	ret = blocking_notअगरier_call_chain(&inetaddr_validator_chain,
					   NETDEV_UP, &ivi);
	ret = notअगरier_to_त्रुटि_सं(ret);
	अगर (ret) अणु
		inet_मुक्त_अगरa(अगरa);
		वापस ret;
	पूर्ण

	अगर (!(अगरa->अगरa_flags & IFA_F_SECONDARY)) अणु
		pअक्रमom_seed((__क्रमce u32) अगरa->अगरa_local);
		अगरap = last_primary;
	पूर्ण

	rcu_assign_poपूर्णांकer(अगरa->अगरa_next, *अगरap);
	rcu_assign_poपूर्णांकer(*अगरap, अगरa);

	inet_hash_insert(dev_net(in_dev->dev), अगरa);

	cancel_delayed_work(&check_lअगरeसमय_work);
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &check_lअगरeसमय_work, 0);

	/* Send message first, then call notअगरier.
	   Notअगरier will trigger FIB update, so that
	   listeners of netlink will know about new अगरaddr */
	rपंचांगsg_अगरa(RTM_NEWADDR, अगरa, nlh, portid);
	blocking_notअगरier_call_chain(&inetaddr_chain, NETDEV_UP, अगरa);

	वापस 0;
पूर्ण

अटल पूर्णांक inet_insert_अगरa(काष्ठा in_अगरaddr *अगरa)
अणु
	वापस __inet_insert_अगरa(अगरa, शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक inet_set_अगरa(काष्ठा net_device *dev, काष्ठा in_अगरaddr *अगरa)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rtnl(dev);

	ASSERT_RTNL();

	अगर (!in_dev) अणु
		inet_मुक्त_अगरa(अगरa);
		वापस -ENOBUFS;
	पूर्ण
	ipv4_devconf_setall(in_dev);
	neigh_parms_data_state_setall(in_dev->arp_parms);
	अगर (अगरa->अगरa_dev != in_dev) अणु
		WARN_ON(अगरa->अगरa_dev);
		in_dev_hold(in_dev);
		अगरa->अगरa_dev = in_dev;
	पूर्ण
	अगर (ipv4_is_loopback(अगरa->अगरa_local))
		अगरa->अगरa_scope = RT_SCOPE_HOST;
	वापस inet_insert_अगरa(अगरa);
पूर्ण

/* Caller must hold RCU or RTNL :
 * We करोnt take a reference on found in_device
 */
काष्ठा in_device *inetdev_by_index(काष्ठा net *net, पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev;
	काष्ठा in_device *in_dev = शून्य;

	rcu_पढ़ो_lock();
	dev = dev_get_by_index_rcu(net, अगरindex);
	अगर (dev)
		in_dev = rcu_dereference_rtnl(dev->ip_ptr);
	rcu_पढ़ो_unlock();
	वापस in_dev;
पूर्ण
EXPORT_SYMBOL(inetdev_by_index);

/* Called only from RTNL semaphored context. No locks. */

काष्ठा in_अगरaddr *inet_अगरa_byprefix(काष्ठा in_device *in_dev, __be32 prefix,
				    __be32 mask)
अणु
	काष्ठा in_अगरaddr *अगरa;

	ASSERT_RTNL();

	in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev) अणु
		अगर (अगरa->अगरa_mask == mask && inet_अगरa_match(prefix, अगरa))
			वापस अगरa;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक ip_mc_स्वतःjoin_config(काष्ठा net *net, bool join,
				 स्थिर काष्ठा in_अगरaddr *अगरa)
अणु
#अगर defined(CONFIG_IP_MULTICAST)
	काष्ठा ip_mreqn mreq = अणु
		.imr_multiaddr.s_addr = अगरa->अगरa_address,
		.imr_अगरindex = अगरa->अगरa_dev->dev->अगरindex,
	पूर्ण;
	काष्ठा sock *sk = net->ipv4.mc_स्वतःjoin_sk;
	पूर्णांक ret;

	ASSERT_RTNL();

	lock_sock(sk);
	अगर (join)
		ret = ip_mc_join_group(sk, &mreq);
	अन्यथा
		ret = ip_mc_leave_group(sk, &mreq);
	release_sock(sk);

	वापस ret;
#अन्यथा
	वापस -EOPNOTSUPP;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक inet_rपंचांग_deladdr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा in_अगरaddr __rcu **अगरap;
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा in_device *in_dev;
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा in_अगरaddr *अगरa;
	पूर्णांक err;

	ASSERT_RTNL();

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
				     अगरa_ipv4_policy, extack);
	अगर (err < 0)
		जाओ errout;

	अगरm = nlmsg_data(nlh);
	in_dev = inetdev_by_index(net, अगरm->अगरa_index);
	अगर (!in_dev) अणु
		err = -ENODEV;
		जाओ errout;
	पूर्ण

	क्रम (अगरap = &in_dev->अगरa_list; (अगरa = rtnl_dereference(*अगरap)) != शून्य;
	     अगरap = &अगरa->अगरa_next) अणु
		अगर (tb[IFA_LOCAL] &&
		    अगरa->अगरa_local != nla_get_in_addr(tb[IFA_LOCAL]))
			जारी;

		अगर (tb[IFA_LABEL] && nla_म_भेद(tb[IFA_LABEL], अगरa->अगरa_label))
			जारी;

		अगर (tb[IFA_ADDRESS] &&
		    (अगरm->अगरa_prefixlen != अगरa->अगरa_prefixlen ||
		    !inet_अगरa_match(nla_get_in_addr(tb[IFA_ADDRESS]), अगरa)))
			जारी;

		अगर (ipv4_is_multicast(अगरa->अगरa_address))
			ip_mc_स्वतःjoin_config(net, false, अगरa);
		__inet_del_अगरa(in_dev, अगरap, 1, nlh, NETLINK_CB(skb).portid);
		वापस 0;
	पूर्ण

	err = -EADDRNOTAVAIL;
errout:
	वापस err;
पूर्ण

#घोषणा अनन्त_LIFE_TIME	0xFFFFFFFF

अटल व्योम check_lअगरeसमय(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ now, next, next_sec, next_sched;
	काष्ठा in_अगरaddr *अगरa;
	काष्ठा hlist_node *n;
	पूर्णांक i;

	now = jअगरfies;
	next = round_jअगरfies_up(now + ADDR_CHECK_FREQUENCY);

	क्रम (i = 0; i < IN4_ADDR_HSIZE; i++) अणु
		bool change_needed = false;

		rcu_पढ़ो_lock();
		hlist_क्रम_each_entry_rcu(अगरa, &inet_addr_lst[i], hash) अणु
			अचिन्हित दीर्घ age;

			अगर (अगरa->अगरa_flags & IFA_F_PERMANENT)
				जारी;

			/* We try to batch several events at once. */
			age = (now - अगरa->अगरa_tstamp +
			       ADDRCONF_TIMER_FUZZ_MINUS) / HZ;

			अगर (अगरa->अगरa_valid_lft != अनन्त_LIFE_TIME &&
			    age >= अगरa->अगरa_valid_lft) अणु
				change_needed = true;
			पूर्ण अन्यथा अगर (अगरa->अगरa_preferred_lft ==
				   अनन्त_LIFE_TIME) अणु
				जारी;
			पूर्ण अन्यथा अगर (age >= अगरa->अगरa_preferred_lft) अणु
				अगर (समय_beक्रमe(अगरa->अगरa_tstamp +
						अगरa->अगरa_valid_lft * HZ, next))
					next = अगरa->अगरa_tstamp +
					       अगरa->अगरa_valid_lft * HZ;

				अगर (!(अगरa->अगरa_flags & IFA_F_DEPRECATED))
					change_needed = true;
			पूर्ण अन्यथा अगर (समय_beक्रमe(अगरa->अगरa_tstamp +
					       अगरa->अगरa_preferred_lft * HZ,
					       next)) अणु
				next = अगरa->अगरa_tstamp +
				       अगरa->अगरa_preferred_lft * HZ;
			पूर्ण
		पूर्ण
		rcu_पढ़ो_unlock();
		अगर (!change_needed)
			जारी;
		rtnl_lock();
		hlist_क्रम_each_entry_safe(अगरa, n, &inet_addr_lst[i], hash) अणु
			अचिन्हित दीर्घ age;

			अगर (अगरa->अगरa_flags & IFA_F_PERMANENT)
				जारी;

			/* We try to batch several events at once. */
			age = (now - अगरa->अगरa_tstamp +
			       ADDRCONF_TIMER_FUZZ_MINUS) / HZ;

			अगर (अगरa->अगरa_valid_lft != अनन्त_LIFE_TIME &&
			    age >= अगरa->अगरa_valid_lft) अणु
				काष्ठा in_अगरaddr __rcu **अगरap;
				काष्ठा in_अगरaddr *पंचांगp;

				अगरap = &अगरa->अगरa_dev->अगरa_list;
				पंचांगp = rtnl_dereference(*अगरap);
				जबतक (पंचांगp) अणु
					अगर (पंचांगp == अगरa) अणु
						inet_del_अगरa(अगरa->अगरa_dev,
							     अगरap, 1);
						अवरोध;
					पूर्ण
					अगरap = &पंचांगp->अगरa_next;
					पंचांगp = rtnl_dereference(*अगरap);
				पूर्ण
			पूर्ण अन्यथा अगर (अगरa->अगरa_preferred_lft !=
				   अनन्त_LIFE_TIME &&
				   age >= अगरa->अगरa_preferred_lft &&
				   !(अगरa->अगरa_flags & IFA_F_DEPRECATED)) अणु
				अगरa->अगरa_flags |= IFA_F_DEPRECATED;
				rपंचांगsg_अगरa(RTM_NEWADDR, अगरa, शून्य, 0);
			पूर्ण
		पूर्ण
		rtnl_unlock();
	पूर्ण

	next_sec = round_jअगरfies_up(next);
	next_sched = next;

	/* If rounded समयout is accurate enough, accept it. */
	अगर (समय_beक्रमe(next_sec, next + ADDRCONF_TIMER_FUZZ))
		next_sched = next_sec;

	now = jअगरfies;
	/* And minimum पूर्णांकerval is ADDRCONF_TIMER_FUZZ_MAX. */
	अगर (समय_beक्रमe(next_sched, now + ADDRCONF_TIMER_FUZZ_MAX))
		next_sched = now + ADDRCONF_TIMER_FUZZ_MAX;

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &check_lअगरeसमय_work,
			next_sched - now);
पूर्ण

अटल व्योम set_अगरa_lअगरeसमय(काष्ठा in_अगरaddr *अगरa, __u32 valid_lft,
			     __u32 prefered_lft)
अणु
	अचिन्हित दीर्घ समयout;

	अगरa->अगरa_flags &= ~(IFA_F_PERMANENT | IFA_F_DEPRECATED);

	समयout = addrconf_समयout_fixup(valid_lft, HZ);
	अगर (addrconf_finite_समयout(समयout))
		अगरa->अगरa_valid_lft = समयout;
	अन्यथा
		अगरa->अगरa_flags |= IFA_F_PERMANENT;

	समयout = addrconf_समयout_fixup(prefered_lft, HZ);
	अगर (addrconf_finite_समयout(समयout)) अणु
		अगर (समयout == 0)
			अगरa->अगरa_flags |= IFA_F_DEPRECATED;
		अगरa->अगरa_preferred_lft = समयout;
	पूर्ण
	अगरa->अगरa_tstamp = jअगरfies;
	अगर (!अगरa->अगरa_cstamp)
		अगरa->अगरa_cstamp = अगरa->अगरa_tstamp;
पूर्ण

अटल काष्ठा in_अगरaddr *rपंचांग_to_अगरaddr(काष्ठा net *net, काष्ठा nlmsghdr *nlh,
				       __u32 *pvalid_lft, __u32 *pprefered_lft,
				       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा in_अगरaddr *अगरa;
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा net_device *dev;
	काष्ठा in_device *in_dev;
	पूर्णांक err;

	err = nlmsg_parse_deprecated(nlh, माप(*अगरm), tb, IFA_MAX,
				     अगरa_ipv4_policy, extack);
	अगर (err < 0)
		जाओ errout;

	अगरm = nlmsg_data(nlh);
	err = -EINVAL;
	अगर (अगरm->अगरa_prefixlen > 32 || !tb[IFA_LOCAL])
		जाओ errout;

	dev = __dev_get_by_index(net, अगरm->अगरa_index);
	err = -ENODEV;
	अगर (!dev)
		जाओ errout;

	in_dev = __in_dev_get_rtnl(dev);
	err = -ENOBUFS;
	अगर (!in_dev)
		जाओ errout;

	अगरa = inet_alloc_अगरa();
	अगर (!अगरa)
		/*
		 * A potential indev allocation can be left alive, it stays
		 * asचिन्हित to its device and is destroy with it.
		 */
		जाओ errout;

	ipv4_devconf_setall(in_dev);
	neigh_parms_data_state_setall(in_dev->arp_parms);
	in_dev_hold(in_dev);

	अगर (!tb[IFA_ADDRESS])
		tb[IFA_ADDRESS] = tb[IFA_LOCAL];

	INIT_HLIST_NODE(&अगरa->hash);
	अगरa->अगरa_prefixlen = अगरm->अगरa_prefixlen;
	अगरa->अगरa_mask = inet_make_mask(अगरm->अगरa_prefixlen);
	अगरa->अगरa_flags = tb[IFA_FLAGS] ? nla_get_u32(tb[IFA_FLAGS]) :
					 अगरm->अगरa_flags;
	अगरa->अगरa_scope = अगरm->अगरa_scope;
	अगरa->अगरa_dev = in_dev;

	अगरa->अगरa_local = nla_get_in_addr(tb[IFA_LOCAL]);
	अगरa->अगरa_address = nla_get_in_addr(tb[IFA_ADDRESS]);

	अगर (tb[IFA_BROADCAST])
		अगरa->अगरa_broadcast = nla_get_in_addr(tb[IFA_BROADCAST]);

	अगर (tb[IFA_LABEL])
		nla_strscpy(अगरa->अगरa_label, tb[IFA_LABEL], IFNAMSIZ);
	अन्यथा
		स_नकल(अगरa->अगरa_label, dev->name, IFNAMSIZ);

	अगर (tb[IFA_RT_PRIORITY])
		अगरa->अगरa_rt_priority = nla_get_u32(tb[IFA_RT_PRIORITY]);

	अगर (tb[IFA_CACHEINFO]) अणु
		काष्ठा अगरa_cacheinfo *ci;

		ci = nla_data(tb[IFA_CACHEINFO]);
		अगर (!ci->अगरa_valid || ci->अगरa_prefered > ci->अगरa_valid) अणु
			err = -EINVAL;
			जाओ errout_मुक्त;
		पूर्ण
		*pvalid_lft = ci->अगरa_valid;
		*pprefered_lft = ci->अगरa_prefered;
	पूर्ण

	वापस अगरa;

errout_मुक्त:
	inet_मुक्त_अगरa(अगरa);
errout:
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा in_अगरaddr *find_matching_अगरa(काष्ठा in_अगरaddr *अगरa)
अणु
	काष्ठा in_device *in_dev = अगरa->अगरa_dev;
	काष्ठा in_अगरaddr *अगरa1;

	अगर (!अगरa->अगरa_local)
		वापस शून्य;

	in_dev_क्रम_each_अगरa_rtnl(अगरa1, in_dev) अणु
		अगर (अगरa1->अगरa_mask == अगरa->अगरa_mask &&
		    inet_अगरa_match(अगरa1->अगरa_address, अगरa) &&
		    अगरa1->अगरa_local == अगरa->अगरa_local)
			वापस अगरa1;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक inet_rपंचांग_newaddr(काष्ठा sk_buff *skb, काष्ठा nlmsghdr *nlh,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा in_अगरaddr *अगरa;
	काष्ठा in_अगरaddr *अगरa_existing;
	__u32 valid_lft = अनन्त_LIFE_TIME;
	__u32 prefered_lft = अनन्त_LIFE_TIME;

	ASSERT_RTNL();

	अगरa = rपंचांग_to_अगरaddr(net, nlh, &valid_lft, &prefered_lft, extack);
	अगर (IS_ERR(अगरa))
		वापस PTR_ERR(अगरa);

	अगरa_existing = find_matching_अगरa(अगरa);
	अगर (!अगरa_existing) अणु
		/* It would be best to check क्रम !NLM_F_CREATE here but
		 * userspace alपढ़ोy relies on not having to provide this.
		 */
		set_अगरa_lअगरeसमय(अगरa, valid_lft, prefered_lft);
		अगर (अगरa->अगरa_flags & IFA_F_MCAUTOJOIN) अणु
			पूर्णांक ret = ip_mc_स्वतःjoin_config(net, true, अगरa);

			अगर (ret < 0) अणु
				inet_मुक्त_अगरa(अगरa);
				वापस ret;
			पूर्ण
		पूर्ण
		वापस __inet_insert_अगरa(अगरa, nlh, NETLINK_CB(skb).portid,
					 extack);
	पूर्ण अन्यथा अणु
		u32 new_metric = अगरa->अगरa_rt_priority;

		inet_मुक्त_अगरa(अगरa);

		अगर (nlh->nlmsg_flags & NLM_F_EXCL ||
		    !(nlh->nlmsg_flags & NLM_F_REPLACE))
			वापस -EEXIST;
		अगरa = अगरa_existing;

		अगर (अगरa->अगरa_rt_priority != new_metric) अणु
			fib_modअगरy_prefix_metric(अगरa, new_metric);
			अगरa->अगरa_rt_priority = new_metric;
		पूर्ण

		set_अगरa_lअगरeसमय(अगरa, valid_lft, prefered_lft);
		cancel_delayed_work(&check_lअगरeसमय_work);
		queue_delayed_work(प्रणाली_घातer_efficient_wq,
				&check_lअगरeसमय_work, 0);
		rपंचांगsg_अगरa(RTM_NEWADDR, अगरa, nlh, NETLINK_CB(skb).portid);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	Determine a शेष network mask, based on the IP address.
 */

अटल पूर्णांक inet_abc_len(__be32 addr)
अणु
	पूर्णांक rc = -1;	/* Something अन्यथा, probably a multicast. */

	अगर (ipv4_is_zeronet(addr) || ipv4_is_lbcast(addr))
		rc = 0;
	अन्यथा अणु
		__u32 haddr = ntohl(addr);
		अगर (IN_CLASSA(haddr))
			rc = 8;
		अन्यथा अगर (IN_CLASSB(haddr))
			rc = 16;
		अन्यथा अगर (IN_CLASSC(haddr))
			rc = 24;
		अन्यथा अगर (IN_CLASSE(haddr))
			rc = 32;
	पूर्ण

	वापस rc;
पूर्ण


पूर्णांक devinet_ioctl(काष्ठा net *net, अचिन्हित पूर्णांक cmd, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा sockaddr_in sin_orig;
	काष्ठा sockaddr_in *sin = (काष्ठा sockaddr_in *)&अगरr->अगरr_addr;
	काष्ठा in_अगरaddr __rcu **अगरap = शून्य;
	काष्ठा in_device *in_dev;
	काष्ठा in_अगरaddr *अगरa = शून्य;
	काष्ठा net_device *dev;
	अक्षर *colon;
	पूर्णांक ret = -EFAULT;
	पूर्णांक tryaddrmatch = 0;

	अगरr->अगरr_name[IFNAMSIZ - 1] = 0;

	/* save original address क्रम comparison */
	स_नकल(&sin_orig, sin, माप(*sin));

	colon = म_अक्षर(अगरr->अगरr_name, ':');
	अगर (colon)
		*colon = 0;

	dev_load(net, अगरr->अगरr_name);

	चयन (cmd) अणु
	हाल SIOCGIFADDR:	/* Get पूर्णांकerface address */
	हाल SIOCGIFBRDADDR:	/* Get the broadcast address */
	हाल SIOCGIFDSTADDR:	/* Get the destination address */
	हाल SIOCGIFNETMASK:	/* Get the neपंचांगask क्रम the पूर्णांकerface */
		/* Note that these ioctls will not sleep,
		   so that we करो not impose a lock.
		   One day we will be क्रमced to put shlock here (I mean SMP)
		 */
		tryaddrmatch = (sin_orig.sin_family == AF_INET);
		स_रखो(sin, 0, माप(*sin));
		sin->sin_family = AF_INET;
		अवरोध;

	हाल SIOCSIFFLAGS:
		ret = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			जाओ out;
		अवरोध;
	हाल SIOCSIFADDR:	/* Set पूर्णांकerface address (and family) */
	हाल SIOCSIFBRDADDR:	/* Set the broadcast address */
	हाल SIOCSIFDSTADDR:	/* Set the destination address */
	हाल SIOCSIFNETMASK: 	/* Set the neपंचांगask क्रम the पूर्णांकerface */
		ret = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			जाओ out;
		ret = -EINVAL;
		अगर (sin->sin_family != AF_INET)
			जाओ out;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	rtnl_lock();

	ret = -ENODEV;
	dev = __dev_get_by_name(net, अगरr->अगरr_name);
	अगर (!dev)
		जाओ करोne;

	अगर (colon)
		*colon = ':';

	in_dev = __in_dev_get_rtnl(dev);
	अगर (in_dev) अणु
		अगर (tryaddrmatch) अणु
			/* Matthias Andree */
			/* compare label and address (4.4BSD style) */
			/* note: we only करो this क्रम a limited set of ioctls
			   and only अगर the original address family was AF_INET.
			   This is checked above. */

			क्रम (अगरap = &in_dev->अगरa_list;
			     (अगरa = rtnl_dereference(*अगरap)) != शून्य;
			     अगरap = &अगरa->अगरa_next) अणु
				अगर (!म_भेद(अगरr->अगरr_name, अगरa->अगरa_label) &&
				    sin_orig.sin_addr.s_addr ==
							अगरa->अगरa_local) अणु
					अवरोध; /* found */
				पूर्ण
			पूर्ण
		पूर्ण
		/* we didn't get a match, maybe the application is
		   4.3BSD-style and passed in junk so we fall back to
		   comparing just the label */
		अगर (!अगरa) अणु
			क्रम (अगरap = &in_dev->अगरa_list;
			     (अगरa = rtnl_dereference(*अगरap)) != शून्य;
			     अगरap = &अगरa->अगरa_next)
				अगर (!म_भेद(अगरr->अगरr_name, अगरa->अगरa_label))
					अवरोध;
		पूर्ण
	पूर्ण

	ret = -EADDRNOTAVAIL;
	अगर (!अगरa && cmd != SIOCSIFADDR && cmd != SIOCSIFFLAGS)
		जाओ करोne;

	चयन (cmd) अणु
	हाल SIOCGIFADDR:	/* Get पूर्णांकerface address */
		ret = 0;
		sin->sin_addr.s_addr = अगरa->अगरa_local;
		अवरोध;

	हाल SIOCGIFBRDADDR:	/* Get the broadcast address */
		ret = 0;
		sin->sin_addr.s_addr = अगरa->अगरa_broadcast;
		अवरोध;

	हाल SIOCGIFDSTADDR:	/* Get the destination address */
		ret = 0;
		sin->sin_addr.s_addr = अगरa->अगरa_address;
		अवरोध;

	हाल SIOCGIFNETMASK:	/* Get the neपंचांगask क्रम the पूर्णांकerface */
		ret = 0;
		sin->sin_addr.s_addr = अगरa->अगरa_mask;
		अवरोध;

	हाल SIOCSIFFLAGS:
		अगर (colon) अणु
			ret = -EADDRNOTAVAIL;
			अगर (!अगरa)
				अवरोध;
			ret = 0;
			अगर (!(अगरr->अगरr_flags & IFF_UP))
				inet_del_अगरa(in_dev, अगरap, 1);
			अवरोध;
		पूर्ण
		ret = dev_change_flags(dev, अगरr->अगरr_flags, शून्य);
		अवरोध;

	हाल SIOCSIFADDR:	/* Set पूर्णांकerface address (and family) */
		ret = -EINVAL;
		अगर (inet_abc_len(sin->sin_addr.s_addr) < 0)
			अवरोध;

		अगर (!अगरa) अणु
			ret = -ENOBUFS;
			अगरa = inet_alloc_अगरa();
			अगर (!अगरa)
				अवरोध;
			INIT_HLIST_NODE(&अगरa->hash);
			अगर (colon)
				स_नकल(अगरa->अगरa_label, अगरr->अगरr_name, IFNAMSIZ);
			अन्यथा
				स_नकल(अगरa->अगरa_label, dev->name, IFNAMSIZ);
		पूर्ण अन्यथा अणु
			ret = 0;
			अगर (अगरa->अगरa_local == sin->sin_addr.s_addr)
				अवरोध;
			inet_del_अगरa(in_dev, अगरap, 0);
			अगरa->अगरa_broadcast = 0;
			अगरa->अगरa_scope = 0;
		पूर्ण

		अगरa->अगरa_address = अगरa->अगरa_local = sin->sin_addr.s_addr;

		अगर (!(dev->flags & IFF_POINTOPOINT)) अणु
			अगरa->अगरa_prefixlen = inet_abc_len(अगरa->अगरa_address);
			अगरa->अगरa_mask = inet_make_mask(अगरa->अगरa_prefixlen);
			अगर ((dev->flags & IFF_BROADCAST) &&
			    अगरa->अगरa_prefixlen < 31)
				अगरa->अगरa_broadcast = अगरa->अगरa_address |
						     ~अगरa->अगरa_mask;
		पूर्ण अन्यथा अणु
			अगरa->अगरa_prefixlen = 32;
			अगरa->अगरa_mask = inet_make_mask(32);
		पूर्ण
		set_अगरa_lअगरeसमय(अगरa, अनन्त_LIFE_TIME, अनन्त_LIFE_TIME);
		ret = inet_set_अगरa(dev, अगरa);
		अवरोध;

	हाल SIOCSIFBRDADDR:	/* Set the broadcast address */
		ret = 0;
		अगर (अगरa->अगरa_broadcast != sin->sin_addr.s_addr) अणु
			inet_del_अगरa(in_dev, अगरap, 0);
			अगरa->अगरa_broadcast = sin->sin_addr.s_addr;
			inet_insert_अगरa(अगरa);
		पूर्ण
		अवरोध;

	हाल SIOCSIFDSTADDR:	/* Set the destination address */
		ret = 0;
		अगर (अगरa->अगरa_address == sin->sin_addr.s_addr)
			अवरोध;
		ret = -EINVAL;
		अगर (inet_abc_len(sin->sin_addr.s_addr) < 0)
			अवरोध;
		ret = 0;
		inet_del_अगरa(in_dev, अगरap, 0);
		अगरa->अगरa_address = sin->sin_addr.s_addr;
		inet_insert_अगरa(अगरa);
		अवरोध;

	हाल SIOCSIFNETMASK: 	/* Set the neपंचांगask क्रम the पूर्णांकerface */

		/*
		 *	The mask we set must be legal.
		 */
		ret = -EINVAL;
		अगर (bad_mask(sin->sin_addr.s_addr, 0))
			अवरोध;
		ret = 0;
		अगर (अगरa->अगरa_mask != sin->sin_addr.s_addr) अणु
			__be32 old_mask = अगरa->अगरa_mask;
			inet_del_अगरa(in_dev, अगरap, 0);
			अगरa->अगरa_mask = sin->sin_addr.s_addr;
			अगरa->अगरa_prefixlen = inet_mask_len(अगरa->अगरa_mask);

			/* See अगर current broadcast address matches
			 * with current neपंचांगask, then recalculate
			 * the broadcast address. Otherwise it's a
			 * funny address, so करोn't touch it since
			 * the user seems to know what (s)he's करोing...
			 */
			अगर ((dev->flags & IFF_BROADCAST) &&
			    (अगरa->अगरa_prefixlen < 31) &&
			    (अगरa->अगरa_broadcast ==
			     (अगरa->अगरa_local|~old_mask))) अणु
				अगरa->अगरa_broadcast = (अगरa->अगरa_local |
						      ~sin->sin_addr.s_addr);
			पूर्ण
			inet_insert_अगरa(अगरa);
		पूर्ण
		अवरोध;
	पूर्ण
करोne:
	rtnl_unlock();
out:
	वापस ret;
पूर्ण

अटल पूर्णांक inet_gअगरconf(काष्ठा net_device *dev, अक्षर __user *buf, पूर्णांक len, पूर्णांक size)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rtnl(dev);
	स्थिर काष्ठा in_अगरaddr *अगरa;
	काष्ठा अगरreq अगरr;
	पूर्णांक करोne = 0;

	अगर (WARN_ON(size > माप(काष्ठा अगरreq)))
		जाओ out;

	अगर (!in_dev)
		जाओ out;

	in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev) अणु
		अगर (!buf) अणु
			करोne += size;
			जारी;
		पूर्ण
		अगर (len < size)
			अवरोध;
		स_रखो(&अगरr, 0, माप(काष्ठा अगरreq));
		म_नकल(अगरr.अगरr_name, अगरa->अगरa_label);

		(*(काष्ठा sockaddr_in *)&अगरr.अगरr_addr).sin_family = AF_INET;
		(*(काष्ठा sockaddr_in *)&अगरr.अगरr_addr).sin_addr.s_addr =
								अगरa->अगरa_local;

		अगर (copy_to_user(buf + करोne, &अगरr, size)) अणु
			करोne = -EFAULT;
			अवरोध;
		पूर्ण
		len  -= size;
		करोne += size;
	पूर्ण
out:
	वापस करोne;
पूर्ण

अटल __be32 in_dev_select_addr(स्थिर काष्ठा in_device *in_dev,
				 पूर्णांक scope)
अणु
	स्थिर काष्ठा in_अगरaddr *अगरa;

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अगर (अगरa->अगरa_flags & IFA_F_SECONDARY)
			जारी;
		अगर (अगरa->अगरa_scope != RT_SCOPE_LINK &&
		    अगरa->अगरa_scope <= scope)
			वापस अगरa->अगरa_local;
	पूर्ण

	वापस 0;
पूर्ण

__be32 inet_select_addr(स्थिर काष्ठा net_device *dev, __be32 dst, पूर्णांक scope)
अणु
	स्थिर काष्ठा in_अगरaddr *अगरa;
	__be32 addr = 0;
	अचिन्हित अक्षर localnet_scope = RT_SCOPE_HOST;
	काष्ठा in_device *in_dev;
	काष्ठा net *net = dev_net(dev);
	पूर्णांक master_idx;

	rcu_पढ़ो_lock();
	in_dev = __in_dev_get_rcu(dev);
	अगर (!in_dev)
		जाओ no_in_dev;

	अगर (unlikely(IN_DEV_ROUTE_LOCALNET(in_dev)))
		localnet_scope = RT_SCOPE_LINK;

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अगर (अगरa->अगरa_flags & IFA_F_SECONDARY)
			जारी;
		अगर (min(अगरa->अगरa_scope, localnet_scope) > scope)
			जारी;
		अगर (!dst || inet_अगरa_match(dst, अगरa)) अणु
			addr = अगरa->अगरa_local;
			अवरोध;
		पूर्ण
		अगर (!addr)
			addr = अगरa->अगरa_local;
	पूर्ण

	अगर (addr)
		जाओ out_unlock;
no_in_dev:
	master_idx = l3mdev_master_अगरindex_rcu(dev);

	/* For VRFs, the VRF device takes the place of the loopback device,
	 * with addresses on it being preferred.  Note in such हालs the
	 * loopback device will be among the devices that fail the master_idx
	 * equality check in the loop below.
	 */
	अगर (master_idx &&
	    (dev = dev_get_by_index_rcu(net, master_idx)) &&
	    (in_dev = __in_dev_get_rcu(dev))) अणु
		addr = in_dev_select_addr(in_dev, scope);
		अगर (addr)
			जाओ out_unlock;
	पूर्ण

	/* Not loopback addresses on loopback should be preferred
	   in this हाल. It is important that lo is the first पूर्णांकerface
	   in dev_base list.
	 */
	क्रम_each_netdev_rcu(net, dev) अणु
		अगर (l3mdev_master_अगरindex_rcu(dev) != master_idx)
			जारी;

		in_dev = __in_dev_get_rcu(dev);
		अगर (!in_dev)
			जारी;

		addr = in_dev_select_addr(in_dev, scope);
		अगर (addr)
			जाओ out_unlock;
	पूर्ण
out_unlock:
	rcu_पढ़ो_unlock();
	वापस addr;
पूर्ण
EXPORT_SYMBOL(inet_select_addr);

अटल __be32 confirm_addr_indev(काष्ठा in_device *in_dev, __be32 dst,
			      __be32 local, पूर्णांक scope)
अणु
	अचिन्हित अक्षर localnet_scope = RT_SCOPE_HOST;
	स्थिर काष्ठा in_अगरaddr *अगरa;
	__be32 addr = 0;
	पूर्णांक same = 0;

	अगर (unlikely(IN_DEV_ROUTE_LOCALNET(in_dev)))
		localnet_scope = RT_SCOPE_LINK;

	in_dev_क्रम_each_अगरa_rcu(अगरa, in_dev) अणु
		अचिन्हित अक्षर min_scope = min(अगरa->अगरa_scope, localnet_scope);

		अगर (!addr &&
		    (local == अगरa->अगरa_local || !local) &&
		    min_scope <= scope) अणु
			addr = अगरa->अगरa_local;
			अगर (same)
				अवरोध;
		पूर्ण
		अगर (!same) अणु
			same = (!local || inet_अगरa_match(local, अगरa)) &&
				(!dst || inet_अगरa_match(dst, अगरa));
			अगर (same && addr) अणु
				अगर (local || !dst)
					अवरोध;
				/* Is the selected addr पूर्णांकo dst subnet? */
				अगर (inet_अगरa_match(addr, अगरa))
					अवरोध;
				/* No, then can we use new local src? */
				अगर (min_scope <= scope) अणु
					addr = अगरa->अगरa_local;
					अवरोध;
				पूर्ण
				/* search क्रम large dst subnet क्रम addr */
				same = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस same ? addr : 0;
पूर्ण

/*
 * Confirm that local IP address exists using wildcards:
 * - net: netns to check, cannot be शून्य
 * - in_dev: only on this पूर्णांकerface, शून्य=any पूर्णांकerface
 * - dst: only in the same subnet as dst, 0=any dst
 * - local: address, 0=स्वतःselect the local address
 * - scope: maximum allowed scope value क्रम the local address
 */
__be32 inet_confirm_addr(काष्ठा net *net, काष्ठा in_device *in_dev,
			 __be32 dst, __be32 local, पूर्णांक scope)
अणु
	__be32 addr = 0;
	काष्ठा net_device *dev;

	अगर (in_dev)
		वापस confirm_addr_indev(in_dev, dst, local, scope);

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		in_dev = __in_dev_get_rcu(dev);
		अगर (in_dev) अणु
			addr = confirm_addr_indev(in_dev, dst, local, scope);
			अगर (addr)
				अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस addr;
पूर्ण
EXPORT_SYMBOL(inet_confirm_addr);

/*
 *	Device notअगरier
 */

पूर्णांक रेजिस्टर_inetaddr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&inetaddr_chain, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_inetaddr_notअगरier);

पूर्णांक unरेजिस्टर_inetaddr_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&inetaddr_chain, nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_inetaddr_notअगरier);

पूर्णांक रेजिस्टर_inetaddr_validator_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&inetaddr_validator_chain, nb);
पूर्ण
EXPORT_SYMBOL(रेजिस्टर_inetaddr_validator_notअगरier);

पूर्णांक unरेजिस्टर_inetaddr_validator_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&inetaddr_validator_chain,
	    nb);
पूर्ण
EXPORT_SYMBOL(unरेजिस्टर_inetaddr_validator_notअगरier);

/* Rename अगरa_labels क्रम a device name change. Make some efक्रमt to preserve
 * existing alias numbering and to create unique labels अगर possible.
*/
अटल व्योम inetdev_changename(काष्ठा net_device *dev, काष्ठा in_device *in_dev)
अणु
	काष्ठा in_अगरaddr *अगरa;
	पूर्णांक named = 0;

	in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev) अणु
		अक्षर old[IFNAMSIZ], *करोt;

		स_नकल(old, अगरa->अगरa_label, IFNAMSIZ);
		स_नकल(अगरa->अगरa_label, dev->name, IFNAMSIZ);
		अगर (named++ == 0)
			जाओ skip;
		करोt = म_अक्षर(old, ':');
		अगर (!करोt) अणु
			प्र_लिखो(old, ":%d", named);
			करोt = old;
		पूर्ण
		अगर (म_माप(करोt) + म_माप(dev->name) < IFNAMSIZ)
			म_जोड़ो(अगरa->अगरa_label, करोt);
		अन्यथा
			म_नकल(अगरa->अगरa_label + (IFNAMSIZ - म_माप(करोt) - 1), करोt);
skip:
		rपंचांगsg_अगरa(RTM_NEWADDR, अगरa, शून्य, 0);
	पूर्ण
पूर्ण

अटल व्योम inetdev_send_gratuitous_arp(काष्ठा net_device *dev,
					काष्ठा in_device *in_dev)

अणु
	स्थिर काष्ठा in_अगरaddr *अगरa;

	in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev) अणु
		arp_send(ARPOP_REQUEST, ETH_P_ARP,
			 अगरa->अगरa_local, dev,
			 अगरa->अगरa_local, शून्य,
			 dev->dev_addr, शून्य);
	पूर्ण
पूर्ण

/* Called only under RTNL semaphore */

अटल पूर्णांक inetdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			 व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा in_device *in_dev = __in_dev_get_rtnl(dev);

	ASSERT_RTNL();

	अगर (!in_dev) अणु
		अगर (event == NETDEV_REGISTER) अणु
			in_dev = inetdev_init(dev);
			अगर (IS_ERR(in_dev))
				वापस notअगरier_from_त्रुटि_सं(PTR_ERR(in_dev));
			अगर (dev->flags & IFF_LOOPBACK) अणु
				IN_DEV_CONF_SET(in_dev, NOXFRM, 1);
				IN_DEV_CONF_SET(in_dev, NOPOLICY, 1);
			पूर्ण
		पूर्ण अन्यथा अगर (event == NETDEV_CHANGEMTU) अणु
			/* Re-enabling IP */
			अगर (inetdev_valid_mtu(dev->mtu))
				in_dev = inetdev_init(dev);
		पूर्ण
		जाओ out;
	पूर्ण

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		pr_debug("%s: bug\n", __func__);
		RCU_INIT_POINTER(dev->ip_ptr, शून्य);
		अवरोध;
	हाल NETDEV_UP:
		अगर (!inetdev_valid_mtu(dev->mtu))
			अवरोध;
		अगर (dev->flags & IFF_LOOPBACK) अणु
			काष्ठा in_अगरaddr *अगरa = inet_alloc_अगरa();

			अगर (अगरa) अणु
				INIT_HLIST_NODE(&अगरa->hash);
				अगरa->अगरa_local =
				  अगरa->अगरa_address = htonl(INADDR_LOOPBACK);
				अगरa->अगरa_prefixlen = 8;
				अगरa->अगरa_mask = inet_make_mask(8);
				in_dev_hold(in_dev);
				अगरa->अगरa_dev = in_dev;
				अगरa->अगरa_scope = RT_SCOPE_HOST;
				स_नकल(अगरa->अगरa_label, dev->name, IFNAMSIZ);
				set_अगरa_lअगरeसमय(अगरa, अनन्त_LIFE_TIME,
						 अनन्त_LIFE_TIME);
				ipv4_devconf_setall(in_dev);
				neigh_parms_data_state_setall(in_dev->arp_parms);
				inet_insert_अगरa(अगरa);
			पूर्ण
		पूर्ण
		ip_mc_up(in_dev);
		fallthrough;
	हाल NETDEV_CHANGEADDR:
		अगर (!IN_DEV_ARP_NOTIFY(in_dev))
			अवरोध;
		fallthrough;
	हाल NETDEV_NOTIFY_PEERS:
		/* Send gratuitous ARP to notअगरy of link change */
		inetdev_send_gratuitous_arp(dev, in_dev);
		अवरोध;
	हाल NETDEV_DOWN:
		ip_mc_करोwn(in_dev);
		अवरोध;
	हाल NETDEV_PRE_TYPE_CHANGE:
		ip_mc_unmap(in_dev);
		अवरोध;
	हाल NETDEV_POST_TYPE_CHANGE:
		ip_mc_remap(in_dev);
		अवरोध;
	हाल NETDEV_CHANGEMTU:
		अगर (inetdev_valid_mtu(dev->mtu))
			अवरोध;
		/* disable IP when MTU is not enough */
		fallthrough;
	हाल NETDEV_UNREGISTER:
		inetdev_destroy(in_dev);
		अवरोध;
	हाल NETDEV_CHANGENAME:
		/* Do not notअगरy about label change, this event is
		 * not पूर्णांकeresting to applications using netlink.
		 */
		inetdev_changename(dev, in_dev);

		devinet_sysctl_unरेजिस्टर(in_dev);
		devinet_sysctl_रेजिस्टर(in_dev);
		अवरोध;
	पूर्ण
out:
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ip_netdev_notअगरier = अणु
	.notअगरier_call = inetdev_event,
पूर्ण;

अटल माप_प्रकार inet_nlmsg_size(व्योम)
अणु
	वापस NLMSG_ALIGN(माप(काष्ठा अगरaddrmsg))
	       + nla_total_size(4) /* IFA_ADDRESS */
	       + nla_total_size(4) /* IFA_LOCAL */
	       + nla_total_size(4) /* IFA_BROADCAST */
	       + nla_total_size(IFNAMSIZ) /* IFA_LABEL */
	       + nla_total_size(4)  /* IFA_FLAGS */
	       + nla_total_size(4)  /* IFA_RT_PRIORITY */
	       + nla_total_size(माप(काष्ठा अगरa_cacheinfo)); /* IFA_CACHEINFO */
पूर्ण

अटल अंतरभूत u32 cstamp_delta(अचिन्हित दीर्घ cstamp)
अणु
	वापस (cstamp - INITIAL_JIFFIES) * 100UL / HZ;
पूर्ण

अटल पूर्णांक put_cacheinfo(काष्ठा sk_buff *skb, अचिन्हित दीर्घ cstamp,
			 अचिन्हित दीर्घ tstamp, u32 preferred, u32 valid)
अणु
	काष्ठा अगरa_cacheinfo ci;

	ci.cstamp = cstamp_delta(cstamp);
	ci.tstamp = cstamp_delta(tstamp);
	ci.अगरa_prefered = preferred;
	ci.अगरa_valid = valid;

	वापस nla_put(skb, IFA_CACHEINFO, माप(ci), &ci);
पूर्ण

अटल पूर्णांक inet_fill_अगरaddr(काष्ठा sk_buff *skb, काष्ठा in_अगरaddr *अगरa,
			    काष्ठा inet_fill_args *args)
अणु
	काष्ठा अगरaddrmsg *अगरm;
	काष्ठा nlmsghdr  *nlh;
	u32 preferred, valid;

	nlh = nlmsg_put(skb, args->portid, args->seq, args->event, माप(*अगरm),
			args->flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगरm = nlmsg_data(nlh);
	अगरm->अगरa_family = AF_INET;
	अगरm->अगरa_prefixlen = अगरa->अगरa_prefixlen;
	अगरm->अगरa_flags = अगरa->अगरa_flags;
	अगरm->अगरa_scope = अगरa->अगरa_scope;
	अगरm->अगरa_index = अगरa->अगरa_dev->dev->अगरindex;

	अगर (args->netnsid >= 0 &&
	    nla_put_s32(skb, IFA_TARGET_NETNSID, args->netnsid))
		जाओ nla_put_failure;

	अगर (!(अगरm->अगरa_flags & IFA_F_PERMANENT)) अणु
		preferred = अगरa->अगरa_preferred_lft;
		valid = अगरa->अगरa_valid_lft;
		अगर (preferred != अनन्त_LIFE_TIME) अणु
			दीर्घ tval = (jअगरfies - अगरa->अगरa_tstamp) / HZ;

			अगर (preferred > tval)
				preferred -= tval;
			अन्यथा
				preferred = 0;
			अगर (valid != अनन्त_LIFE_TIME) अणु
				अगर (valid > tval)
					valid -= tval;
				अन्यथा
					valid = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		preferred = अनन्त_LIFE_TIME;
		valid = अनन्त_LIFE_TIME;
	पूर्ण
	अगर ((अगरa->अगरa_address &&
	     nla_put_in_addr(skb, IFA_ADDRESS, अगरa->अगरa_address)) ||
	    (अगरa->अगरa_local &&
	     nla_put_in_addr(skb, IFA_LOCAL, अगरa->अगरa_local)) ||
	    (अगरa->अगरa_broadcast &&
	     nla_put_in_addr(skb, IFA_BROADCAST, अगरa->अगरa_broadcast)) ||
	    (अगरa->अगरa_label[0] &&
	     nla_put_string(skb, IFA_LABEL, अगरa->अगरa_label)) ||
	    nla_put_u32(skb, IFA_FLAGS, अगरa->अगरa_flags) ||
	    (अगरa->अगरa_rt_priority &&
	     nla_put_u32(skb, IFA_RT_PRIORITY, अगरa->अगरa_rt_priority)) ||
	    put_cacheinfo(skb, अगरa->अगरa_cstamp, अगरa->अगरa_tstamp,
			  preferred, valid))
		जाओ nla_put_failure;

	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक inet_valid_dump_अगरaddr_req(स्थिर काष्ठा nlmsghdr *nlh,
				      काष्ठा inet_fill_args *fillargs,
				      काष्ठा net **tgt_net, काष्ठा sock *sk,
				      काष्ठा netlink_callback *cb)
अणु
	काष्ठा netlink_ext_ack *extack = cb->extack;
	काष्ठा nlattr *tb[IFA_MAX+1];
	काष्ठा अगरaddrmsg *अगरm;
	पूर्णांक err, i;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*अगरm))) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Invalid header for address dump request");
		वापस -EINVAL;
	पूर्ण

	अगरm = nlmsg_data(nlh);
	अगर (अगरm->अगरa_prefixlen || अगरm->अगरa_flags || अगरm->अगरa_scope) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Invalid values in header for address dump request");
		वापस -EINVAL;
	पूर्ण

	fillargs->अगरindex = अगरm->अगरa_index;
	अगर (fillargs->अगरindex) अणु
		cb->answer_flags |= NLM_F_DUMP_FILTERED;
		fillargs->flags |= NLM_F_DUMP_FILTERED;
	पूर्ण

	err = nlmsg_parse_deprecated_strict(nlh, माप(*अगरm), tb, IFA_MAX,
					    अगरa_ipv4_policy, extack);
	अगर (err < 0)
		वापस err;

	क्रम (i = 0; i <= IFA_MAX; ++i) अणु
		अगर (!tb[i])
			जारी;

		अगर (i == IFA_TARGET_NETNSID) अणु
			काष्ठा net *net;

			fillargs->netnsid = nla_get_s32(tb[i]);

			net = rtnl_get_net_ns_capable(sk, fillargs->netnsid);
			अगर (IS_ERR(net)) अणु
				fillargs->netnsid = -1;
				NL_SET_ERR_MSG(extack, "ipv4: Invalid target network namespace id");
				वापस PTR_ERR(net);
			पूर्ण
			*tgt_net = net;
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG(extack, "ipv4: Unsupported attribute in dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक in_dev_dump_addr(काष्ठा in_device *in_dev, काष्ठा sk_buff *skb,
			    काष्ठा netlink_callback *cb, पूर्णांक s_ip_idx,
			    काष्ठा inet_fill_args *fillargs)
अणु
	काष्ठा in_अगरaddr *अगरa;
	पूर्णांक ip_idx = 0;
	पूर्णांक err;

	in_dev_क्रम_each_अगरa_rtnl(अगरa, in_dev) अणु
		अगर (ip_idx < s_ip_idx) अणु
			ip_idx++;
			जारी;
		पूर्ण
		err = inet_fill_अगरaddr(skb, अगरa, fillargs);
		अगर (err < 0)
			जाओ करोne;

		nl_dump_check_consistent(cb, nlmsg_hdr(skb));
		ip_idx++;
	पूर्ण
	err = 0;

करोne:
	cb->args[2] = ip_idx;

	वापस err;
पूर्ण

अटल पूर्णांक inet_dump_अगरaddr(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा inet_fill_args fillargs = अणु
		.portid = NETLINK_CB(cb->skb).portid,
		.seq = nlh->nlmsg_seq,
		.event = RTM_NEWADDR,
		.flags = NLM_F_MULTI,
		.netnsid = -1,
	पूर्ण;
	काष्ठा net *net = sock_net(skb->sk);
	काष्ठा net *tgt_net = net;
	पूर्णांक h, s_h;
	पूर्णांक idx, s_idx;
	पूर्णांक s_ip_idx;
	काष्ठा net_device *dev;
	काष्ठा in_device *in_dev;
	काष्ठा hlist_head *head;
	पूर्णांक err = 0;

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];
	s_ip_idx = cb->args[2];

	अगर (cb->strict_check) अणु
		err = inet_valid_dump_अगरaddr_req(nlh, &fillargs, &tgt_net,
						 skb->sk, cb);
		अगर (err < 0)
			जाओ put_tgt_net;

		err = 0;
		अगर (fillargs.अगरindex) अणु
			dev = __dev_get_by_index(tgt_net, fillargs.अगरindex);
			अगर (!dev) अणु
				err = -ENODEV;
				जाओ put_tgt_net;
			पूर्ण

			in_dev = __in_dev_get_rtnl(dev);
			अगर (in_dev) अणु
				err = in_dev_dump_addr(in_dev, skb, cb, s_ip_idx,
						       &fillargs);
			पूर्ण
			जाओ put_tgt_net;
		पूर्ण
	पूर्ण

	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &tgt_net->dev_index_head[h];
		rcu_पढ़ो_lock();
		cb->seq = atomic_पढ़ो(&tgt_net->ipv4.dev_addr_genid) ^
			  tgt_net->dev_base_seq;
		hlist_क्रम_each_entry_rcu(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			अगर (h > s_h || idx > s_idx)
				s_ip_idx = 0;
			in_dev = __in_dev_get_rcu(dev);
			अगर (!in_dev)
				जाओ cont;

			err = in_dev_dump_addr(in_dev, skb, cb, s_ip_idx,
					       &fillargs);
			अगर (err < 0) अणु
				rcu_पढ़ो_unlock();
				जाओ करोne;
			पूर्ण
cont:
			idx++;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

करोne:
	cb->args[0] = h;
	cb->args[1] = idx;
put_tgt_net:
	अगर (fillargs.netnsid >= 0)
		put_net(tgt_net);

	वापस skb->len ? : err;
पूर्ण

अटल व्योम rपंचांगsg_अगरa(पूर्णांक event, काष्ठा in_अगरaddr *अगरa, काष्ठा nlmsghdr *nlh,
		      u32 portid)
अणु
	काष्ठा inet_fill_args fillargs = अणु
		.portid = portid,
		.seq = nlh ? nlh->nlmsg_seq : 0,
		.event = event,
		.flags = 0,
		.netnsid = -1,
	पूर्ण;
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;
	काष्ठा net *net;

	net = dev_net(अगरa->अगरa_dev->dev);
	skb = nlmsg_new(inet_nlmsg_size(), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = inet_fill_अगरaddr(skb, अगरa, &fillargs);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet_nlmsg_size() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, portid, RTNLGRP_IPV4_IFADDR, nlh, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV4_IFADDR, err);
पूर्ण

अटल माप_प्रकार inet_get_link_af_size(स्थिर काष्ठा net_device *dev,
				    u32 ext_filter_mask)
अणु
	काष्ठा in_device *in_dev = rcu_dereference_rtnl(dev->ip_ptr);

	अगर (!in_dev)
		वापस 0;

	वापस nla_total_size(IPV4_DEVCONF_MAX * 4); /* IFLA_INET_CONF */
पूर्ण

अटल पूर्णांक inet_fill_link_af(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev,
			     u32 ext_filter_mask)
अणु
	काष्ठा in_device *in_dev = rcu_dereference_rtnl(dev->ip_ptr);
	काष्ठा nlattr *nla;
	पूर्णांक i;

	अगर (!in_dev)
		वापस -ENODATA;

	nla = nla_reserve(skb, IFLA_INET_CONF, IPV4_DEVCONF_MAX * 4);
	अगर (!nla)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < IPV4_DEVCONF_MAX; i++)
		((u32 *) nla_data(nla))[i] = in_dev->cnf.data[i];

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy inet_af_policy[IFLA_INET_MAX+1] = अणु
	[IFLA_INET_CONF]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक inet_validate_link_af(स्थिर काष्ठा net_device *dev,
				 स्थिर काष्ठा nlattr *nla)
अणु
	काष्ठा nlattr *a, *tb[IFLA_INET_MAX+1];
	पूर्णांक err, rem;

	अगर (dev && !__in_dev_get_rcu(dev))
		वापस -EAFNOSUPPORT;

	err = nla_parse_nested_deprecated(tb, IFLA_INET_MAX, nla,
					  inet_af_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFLA_INET_CONF]) अणु
		nla_क्रम_each_nested(a, tb[IFLA_INET_CONF], rem) अणु
			पूर्णांक cfgid = nla_type(a);

			अगर (nla_len(a) < 4)
				वापस -EINVAL;

			अगर (cfgid <= 0 || cfgid > IPV4_DEVCONF_MAX)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet_set_link_af(काष्ठा net_device *dev, स्थिर काष्ठा nlattr *nla,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा in_device *in_dev = __in_dev_get_rcu(dev);
	काष्ठा nlattr *a, *tb[IFLA_INET_MAX+1];
	पूर्णांक rem;

	अगर (!in_dev)
		वापस -EAFNOSUPPORT;

	अगर (nla_parse_nested_deprecated(tb, IFLA_INET_MAX, nla, शून्य, शून्य) < 0)
		वापस -EINVAL;

	अगर (tb[IFLA_INET_CONF]) अणु
		nla_क्रम_each_nested(a, tb[IFLA_INET_CONF], rem)
			ipv4_devconf_set(in_dev, nla_type(a), nla_get_u32(a));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet_netconf_msgsize_devconf(पूर्णांक type)
अणु
	पूर्णांक size = NLMSG_ALIGN(माप(काष्ठा netconfmsg))
		   + nla_total_size(4);	/* NETCONFA_IFINDEX */
	bool all = false;

	अगर (type == NETCONFA_ALL)
		all = true;

	अगर (all || type == NETCONFA_FORWARDING)
		size += nla_total_size(4);
	अगर (all || type == NETCONFA_RP_FILTER)
		size += nla_total_size(4);
	अगर (all || type == NETCONFA_MC_FORWARDING)
		size += nla_total_size(4);
	अगर (all || type == NETCONFA_BC_FORWARDING)
		size += nla_total_size(4);
	अगर (all || type == NETCONFA_PROXY_NEIGH)
		size += nla_total_size(4);
	अगर (all || type == NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN)
		size += nla_total_size(4);

	वापस size;
पूर्ण

अटल पूर्णांक inet_netconf_fill_devconf(काष्ठा sk_buff *skb, पूर्णांक अगरindex,
				     काष्ठा ipv4_devconf *devconf, u32 portid,
				     u32 seq, पूर्णांक event, अचिन्हित पूर्णांक flags,
				     पूर्णांक type)
अणु
	काष्ठा nlmsghdr  *nlh;
	काष्ठा netconfmsg *ncm;
	bool all = false;

	nlh = nlmsg_put(skb, portid, seq, event, माप(काष्ठा netconfmsg),
			flags);
	अगर (!nlh)
		वापस -EMSGSIZE;

	अगर (type == NETCONFA_ALL)
		all = true;

	ncm = nlmsg_data(nlh);
	ncm->ncm_family = AF_INET;

	अगर (nla_put_s32(skb, NETCONFA_IFINDEX, अगरindex) < 0)
		जाओ nla_put_failure;

	अगर (!devconf)
		जाओ out;

	अगर ((all || type == NETCONFA_FORWARDING) &&
	    nla_put_s32(skb, NETCONFA_FORWARDING,
			IPV4_DEVCONF(*devconf, FORWARDING)) < 0)
		जाओ nla_put_failure;
	अगर ((all || type == NETCONFA_RP_FILTER) &&
	    nla_put_s32(skb, NETCONFA_RP_FILTER,
			IPV4_DEVCONF(*devconf, RP_FILTER)) < 0)
		जाओ nla_put_failure;
	अगर ((all || type == NETCONFA_MC_FORWARDING) &&
	    nla_put_s32(skb, NETCONFA_MC_FORWARDING,
			IPV4_DEVCONF(*devconf, MC_FORWARDING)) < 0)
		जाओ nla_put_failure;
	अगर ((all || type == NETCONFA_BC_FORWARDING) &&
	    nla_put_s32(skb, NETCONFA_BC_FORWARDING,
			IPV4_DEVCONF(*devconf, BC_FORWARDING)) < 0)
		जाओ nla_put_failure;
	अगर ((all || type == NETCONFA_PROXY_NEIGH) &&
	    nla_put_s32(skb, NETCONFA_PROXY_NEIGH,
			IPV4_DEVCONF(*devconf, PROXY_ARP)) < 0)
		जाओ nla_put_failure;
	अगर ((all || type == NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN) &&
	    nla_put_s32(skb, NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
			IPV4_DEVCONF(*devconf, IGNORE_ROUTES_WITH_LINKDOWN)) < 0)
		जाओ nla_put_failure;

out:
	nlmsg_end(skb, nlh);
	वापस 0;

nla_put_failure:
	nlmsg_cancel(skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

व्योम inet_netconf_notअगरy_devconf(काष्ठा net *net, पूर्णांक event, पूर्णांक type,
				 पूर्णांक अगरindex, काष्ठा ipv4_devconf *devconf)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक err = -ENOBUFS;

	skb = nlmsg_new(inet_netconf_msgsize_devconf(type), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = inet_netconf_fill_devconf(skb, अगरindex, devconf, 0, 0,
					event, 0, type);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	rtnl_notअगरy(skb, net, 0, RTNLGRP_IPV4_NETCONF, शून्य, GFP_KERNEL);
	वापस;
errout:
	अगर (err < 0)
		rtnl_set_sk_err(net, RTNLGRP_IPV4_NETCONF, err);
पूर्ण

अटल स्थिर काष्ठा nla_policy devconf_ipv4_policy[NETCONFA_MAX+1] = अणु
	[NETCONFA_IFINDEX]	= अणु .len = माप(पूर्णांक) पूर्ण,
	[NETCONFA_FORWARDING]	= अणु .len = माप(पूर्णांक) पूर्ण,
	[NETCONFA_RP_FILTER]	= अणु .len = माप(पूर्णांक) पूर्ण,
	[NETCONFA_PROXY_NEIGH]	= अणु .len = माप(पूर्णांक) पूर्ण,
	[NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN]	= अणु .len = माप(पूर्णांक) पूर्ण,
पूर्ण;

अटल पूर्णांक inet_netconf_valid_get_req(काष्ठा sk_buff *skb,
				      स्थिर काष्ठा nlmsghdr *nlh,
				      काष्ठा nlattr **tb,
				      काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक i, err;

	अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(काष्ठा netconfmsg))) अणु
		NL_SET_ERR_MSG(extack, "ipv4: Invalid header for netconf get request");
		वापस -EINVAL;
	पूर्ण

	अगर (!netlink_strict_get_check(skb))
		वापस nlmsg_parse_deprecated(nlh, माप(काष्ठा netconfmsg),
					      tb, NETCONFA_MAX,
					      devconf_ipv4_policy, extack);

	err = nlmsg_parse_deprecated_strict(nlh, माप(काष्ठा netconfmsg),
					    tb, NETCONFA_MAX,
					    devconf_ipv4_policy, extack);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= NETCONFA_MAX; i++) अणु
		अगर (!tb[i])
			जारी;

		चयन (i) अणु
		हाल NETCONFA_IFINDEX:
			अवरोध;
		शेष:
			NL_SET_ERR_MSG(extack, "ipv4: Unsupported attribute in netconf get request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inet_netconf_get_devconf(काष्ठा sk_buff *in_skb,
				    काष्ठा nlmsghdr *nlh,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = sock_net(in_skb->sk);
	काष्ठा nlattr *tb[NETCONFA_MAX+1];
	काष्ठा sk_buff *skb;
	काष्ठा ipv4_devconf *devconf;
	काष्ठा in_device *in_dev;
	काष्ठा net_device *dev;
	पूर्णांक अगरindex;
	पूर्णांक err;

	err = inet_netconf_valid_get_req(in_skb, nlh, tb, extack);
	अगर (err)
		जाओ errout;

	err = -EINVAL;
	अगर (!tb[NETCONFA_IFINDEX])
		जाओ errout;

	अगरindex = nla_get_s32(tb[NETCONFA_IFINDEX]);
	चयन (अगरindex) अणु
	हाल NETCONFA_IFINDEX_ALL:
		devconf = net->ipv4.devconf_all;
		अवरोध;
	हाल NETCONFA_IFINDEX_DEFAULT:
		devconf = net->ipv4.devconf_dflt;
		अवरोध;
	शेष:
		dev = __dev_get_by_index(net, अगरindex);
		अगर (!dev)
			जाओ errout;
		in_dev = __in_dev_get_rtnl(dev);
		अगर (!in_dev)
			जाओ errout;
		devconf = &in_dev->cnf;
		अवरोध;
	पूर्ण

	err = -ENOBUFS;
	skb = nlmsg_new(inet_netconf_msgsize_devconf(NETCONFA_ALL), GFP_KERNEL);
	अगर (!skb)
		जाओ errout;

	err = inet_netconf_fill_devconf(skb, अगरindex, devconf,
					NETLINK_CB(in_skb).portid,
					nlh->nlmsg_seq, RTM_NEWNETCONF, 0,
					NETCONFA_ALL);
	अगर (err < 0) अणु
		/* -EMSGSIZE implies BUG in inet_netconf_msgsize_devconf() */
		WARN_ON(err == -EMSGSIZE);
		kमुक्त_skb(skb);
		जाओ errout;
	पूर्ण
	err = rtnl_unicast(skb, net, NETLINK_CB(in_skb).portid);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक inet_netconf_dump_devconf(काष्ठा sk_buff *skb,
				     काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा nlmsghdr *nlh = cb->nlh;
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक h, s_h;
	पूर्णांक idx, s_idx;
	काष्ठा net_device *dev;
	काष्ठा in_device *in_dev;
	काष्ठा hlist_head *head;

	अगर (cb->strict_check) अणु
		काष्ठा netlink_ext_ack *extack = cb->extack;
		काष्ठा netconfmsg *ncm;

		अगर (nlh->nlmsg_len < nlmsg_msg_size(माप(*ncm))) अणु
			NL_SET_ERR_MSG(extack, "ipv4: Invalid header for netconf dump request");
			वापस -EINVAL;
		पूर्ण

		अगर (nlmsg_attrlen(nlh, माप(*ncm))) अणु
			NL_SET_ERR_MSG(extack, "ipv4: Invalid data after header in netconf dump request");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	s_h = cb->args[0];
	s_idx = idx = cb->args[1];

	क्रम (h = s_h; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		idx = 0;
		head = &net->dev_index_head[h];
		rcu_पढ़ो_lock();
		cb->seq = atomic_पढ़ो(&net->ipv4.dev_addr_genid) ^
			  net->dev_base_seq;
		hlist_क्रम_each_entry_rcu(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			in_dev = __in_dev_get_rcu(dev);
			अगर (!in_dev)
				जाओ cont;

			अगर (inet_netconf_fill_devconf(skb, dev->अगरindex,
						      &in_dev->cnf,
						      NETLINK_CB(cb->skb).portid,
						      nlh->nlmsg_seq,
						      RTM_NEWNETCONF,
						      NLM_F_MULTI,
						      NETCONFA_ALL) < 0) अणु
				rcu_पढ़ो_unlock();
				जाओ करोne;
			पूर्ण
			nl_dump_check_consistent(cb, nlmsg_hdr(skb));
cont:
			idx++;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण
	अगर (h == NETDEV_HASHENTRIES) अणु
		अगर (inet_netconf_fill_devconf(skb, NETCONFA_IFINDEX_ALL,
					      net->ipv4.devconf_all,
					      NETLINK_CB(cb->skb).portid,
					      nlh->nlmsg_seq,
					      RTM_NEWNETCONF, NLM_F_MULTI,
					      NETCONFA_ALL) < 0)
			जाओ करोne;
		अन्यथा
			h++;
	पूर्ण
	अगर (h == NETDEV_HASHENTRIES + 1) अणु
		अगर (inet_netconf_fill_devconf(skb, NETCONFA_IFINDEX_DEFAULT,
					      net->ipv4.devconf_dflt,
					      NETLINK_CB(cb->skb).portid,
					      nlh->nlmsg_seq,
					      RTM_NEWNETCONF, NLM_F_MULTI,
					      NETCONFA_ALL) < 0)
			जाओ करोne;
		अन्यथा
			h++;
	पूर्ण
करोne:
	cb->args[0] = h;
	cb->args[1] = idx;

	वापस skb->len;
पूर्ण

#अगर_घोषित CONFIG_SYSCTL

अटल व्योम devinet_copy_dflt_conf(काष्ठा net *net, पूर्णांक i)
अणु
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(net, dev) अणु
		काष्ठा in_device *in_dev;

		in_dev = __in_dev_get_rcu(dev);
		अगर (in_dev && !test_bit(i, in_dev->cnf.state))
			in_dev->cnf.data[i] = net->ipv4.devconf_dflt->data[i];
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* called with RTNL locked */
अटल व्योम inet_क्रमward_change(काष्ठा net *net)
अणु
	काष्ठा net_device *dev;
	पूर्णांक on = IPV4_DEVCONF_ALL(net, FORWARDING);

	IPV4_DEVCONF_ALL(net, ACCEPT_REसूचीECTS) = !on;
	IPV4_DEVCONF_DFLT(net, FORWARDING) = on;
	inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
				    NETCONFA_FORWARDING,
				    NETCONFA_IFINDEX_ALL,
				    net->ipv4.devconf_all);
	inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
				    NETCONFA_FORWARDING,
				    NETCONFA_IFINDEX_DEFAULT,
				    net->ipv4.devconf_dflt);

	क्रम_each_netdev(net, dev) अणु
		काष्ठा in_device *in_dev;

		अगर (on)
			dev_disable_lro(dev);

		in_dev = __in_dev_get_rtnl(dev);
		अगर (in_dev) अणु
			IN_DEV_CONF_SET(in_dev, FORWARDING, on);
			inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_FORWARDING,
						    dev->अगरindex, &in_dev->cnf);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक devinet_conf_अगरindex(काष्ठा net *net, काष्ठा ipv4_devconf *cnf)
अणु
	अगर (cnf == net->ipv4.devconf_dflt)
		वापस NETCONFA_IFINDEX_DEFAULT;
	अन्यथा अगर (cnf == net->ipv4.devconf_all)
		वापस NETCONFA_IFINDEX_ALL;
	अन्यथा अणु
		काष्ठा in_device *idev
			= container_of(cnf, काष्ठा in_device, cnf);
		वापस idev->dev->अगरindex;
	पूर्ण
पूर्ण

अटल पूर्णांक devinet_conf_proc(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
			     व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक old_value = *(पूर्णांक *)ctl->data;
	पूर्णांक ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);
	पूर्णांक new_value = *(पूर्णांक *)ctl->data;

	अगर (ग_लिखो) अणु
		काष्ठा ipv4_devconf *cnf = ctl->extra1;
		काष्ठा net *net = ctl->extra2;
		पूर्णांक i = (पूर्णांक *)ctl->data - cnf->data;
		पूर्णांक अगरindex;

		set_bit(i, cnf->state);

		अगर (cnf == net->ipv4.devconf_dflt)
			devinet_copy_dflt_conf(net, i);
		अगर (i == IPV4_DEVCONF_ACCEPT_LOCAL - 1 ||
		    i == IPV4_DEVCONF_ROUTE_LOCALNET - 1)
			अगर ((new_value == 0) && (old_value != 0))
				rt_cache_flush(net);

		अगर (i == IPV4_DEVCONF_BC_FORWARDING - 1 &&
		    new_value != old_value)
			rt_cache_flush(net);

		अगर (i == IPV4_DEVCONF_RP_FILTER - 1 &&
		    new_value != old_value) अणु
			अगरindex = devinet_conf_अगरindex(net, cnf);
			inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_RP_FILTER,
						    अगरindex, cnf);
		पूर्ण
		अगर (i == IPV4_DEVCONF_PROXY_ARP - 1 &&
		    new_value != old_value) अणु
			अगरindex = devinet_conf_अगरindex(net, cnf);
			inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_PROXY_NEIGH,
						    अगरindex, cnf);
		पूर्ण
		अगर (i == IPV4_DEVCONF_IGNORE_ROUTES_WITH_LINKDOWN - 1 &&
		    new_value != old_value) अणु
			अगरindex = devinet_conf_अगरindex(net, cnf);
			inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_IGNORE_ROUTES_WITH_LINKDOWN,
						    अगरindex, cnf);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक devinet_sysctl_क्रमward(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				  व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = ctl->data;
	पूर्णांक val = *valp;
	loff_t pos = *ppos;
	पूर्णांक ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);

	अगर (ग_लिखो && *valp != val) अणु
		काष्ठा net *net = ctl->extra2;

		अगर (valp != &IPV4_DEVCONF_DFLT(net, FORWARDING)) अणु
			अगर (!rtnl_trylock()) अणु
				/* Restore the original values beक्रमe restarting */
				*valp = val;
				*ppos = pos;
				वापस restart_syscall();
			पूर्ण
			अगर (valp == &IPV4_DEVCONF_ALL(net, FORWARDING)) अणु
				inet_क्रमward_change(net);
			पूर्ण अन्यथा अणु
				काष्ठा ipv4_devconf *cnf = ctl->extra1;
				काष्ठा in_device *idev =
					container_of(cnf, काष्ठा in_device, cnf);
				अगर (*valp)
					dev_disable_lro(idev->dev);
				inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
							    NETCONFA_FORWARDING,
							    idev->dev->अगरindex,
							    cnf);
			पूर्ण
			rtnl_unlock();
			rt_cache_flush(net);
		पूर्ण अन्यथा
			inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF,
						    NETCONFA_FORWARDING,
						    NETCONFA_IFINDEX_DEFAULT,
						    net->ipv4.devconf_dflt);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ipv4_करोपूर्णांक_and_flush(काष्ठा ctl_table *ctl, पूर्णांक ग_लिखो,
				व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक *valp = ctl->data;
	पूर्णांक val = *valp;
	पूर्णांक ret = proc_करोपूर्णांकvec(ctl, ग_लिखो, buffer, lenp, ppos);
	काष्ठा net *net = ctl->extra2;

	अगर (ग_लिखो && *valp != val)
		rt_cache_flush(net);

	वापस ret;
पूर्ण

#घोषणा DEVINET_SYSCTL_ENTRY(attr, name, mval, proc) \
	अणु \
		.procname	= name, \
		.data		= ipv4_devconf.data + \
				  IPV4_DEVCONF_ ## attr - 1, \
		.maxlen		= माप(पूर्णांक), \
		.mode		= mval, \
		.proc_handler	= proc, \
		.extra1		= &ipv4_devconf, \
	पूर्ण

#घोषणा DEVINET_SYSCTL_RW_ENTRY(attr, name) \
	DEVINET_SYSCTL_ENTRY(attr, name, 0644, devinet_conf_proc)

#घोषणा DEVINET_SYSCTL_RO_ENTRY(attr, name) \
	DEVINET_SYSCTL_ENTRY(attr, name, 0444, devinet_conf_proc)

#घोषणा DEVINET_SYSCTL_COMPLEX_ENTRY(attr, name, proc) \
	DEVINET_SYSCTL_ENTRY(attr, name, 0644, proc)

#घोषणा DEVINET_SYSCTL_FLUSHING_ENTRY(attr, name) \
	DEVINET_SYSCTL_COMPLEX_ENTRY(attr, name, ipv4_करोपूर्णांक_and_flush)

अटल काष्ठा devinet_sysctl_table अणु
	काष्ठा ctl_table_header *sysctl_header;
	काष्ठा ctl_table devinet_vars[__IPV4_DEVCONF_MAX];
पूर्ण devinet_sysctl = अणु
	.devinet_vars = अणु
		DEVINET_SYSCTL_COMPLEX_ENTRY(FORWARDING, "forwarding",
					     devinet_sysctl_क्रमward),
		DEVINET_SYSCTL_RO_ENTRY(MC_FORWARDING, "mc_forwarding"),
		DEVINET_SYSCTL_RW_ENTRY(BC_FORWARDING, "bc_forwarding"),

		DEVINET_SYSCTL_RW_ENTRY(ACCEPT_REसूचीECTS, "accept_redirects"),
		DEVINET_SYSCTL_RW_ENTRY(SECURE_REसूचीECTS, "secure_redirects"),
		DEVINET_SYSCTL_RW_ENTRY(SHARED_MEDIA, "shared_media"),
		DEVINET_SYSCTL_RW_ENTRY(RP_FILTER, "rp_filter"),
		DEVINET_SYSCTL_RW_ENTRY(SEND_REसूचीECTS, "send_redirects"),
		DEVINET_SYSCTL_RW_ENTRY(ACCEPT_SOURCE_ROUTE,
					"accept_source_route"),
		DEVINET_SYSCTL_RW_ENTRY(ACCEPT_LOCAL, "accept_local"),
		DEVINET_SYSCTL_RW_ENTRY(SRC_VMARK, "src_valid_mark"),
		DEVINET_SYSCTL_RW_ENTRY(PROXY_ARP, "proxy_arp"),
		DEVINET_SYSCTL_RW_ENTRY(MEDIUM_ID, "medium_id"),
		DEVINET_SYSCTL_RW_ENTRY(BOOTP_RELAY, "bootp_relay"),
		DEVINET_SYSCTL_RW_ENTRY(LOG_MARTIANS, "log_martians"),
		DEVINET_SYSCTL_RW_ENTRY(TAG, "tag"),
		DEVINET_SYSCTL_RW_ENTRY(ARPFILTER, "arp_filter"),
		DEVINET_SYSCTL_RW_ENTRY(ARP_ANNOUNCE, "arp_announce"),
		DEVINET_SYSCTL_RW_ENTRY(ARP_IGNORE, "arp_ignore"),
		DEVINET_SYSCTL_RW_ENTRY(ARP_ACCEPT, "arp_accept"),
		DEVINET_SYSCTL_RW_ENTRY(ARP_NOTIFY, "arp_notify"),
		DEVINET_SYSCTL_RW_ENTRY(PROXY_ARP_PVLAN, "proxy_arp_pvlan"),
		DEVINET_SYSCTL_RW_ENTRY(FORCE_IGMP_VERSION,
					"force_igmp_version"),
		DEVINET_SYSCTL_RW_ENTRY(IGMPV2_UNSOLICITED_REPORT_INTERVAL,
					"igmpv2_unsolicited_report_interval"),
		DEVINET_SYSCTL_RW_ENTRY(IGMPV3_UNSOLICITED_REPORT_INTERVAL,
					"igmpv3_unsolicited_report_interval"),
		DEVINET_SYSCTL_RW_ENTRY(IGNORE_ROUTES_WITH_LINKDOWN,
					"ignore_routes_with_linkdown"),
		DEVINET_SYSCTL_RW_ENTRY(DROP_GRATUITOUS_ARP,
					"drop_gratuitous_arp"),

		DEVINET_SYSCTL_FLUSHING_ENTRY(NOXFRM, "disable_xfrm"),
		DEVINET_SYSCTL_FLUSHING_ENTRY(NOPOLICY, "disable_policy"),
		DEVINET_SYSCTL_FLUSHING_ENTRY(PROMOTE_SECONDARIES,
					      "promote_secondaries"),
		DEVINET_SYSCTL_FLUSHING_ENTRY(ROUTE_LOCALNET,
					      "route_localnet"),
		DEVINET_SYSCTL_FLUSHING_ENTRY(DROP_UNICAST_IN_L2_MULTICAST,
					      "drop_unicast_in_l2_multicast"),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __devinet_sysctl_रेजिस्टर(काष्ठा net *net, अक्षर *dev_name,
				     पूर्णांक अगरindex, काष्ठा ipv4_devconf *p)
अणु
	पूर्णांक i;
	काष्ठा devinet_sysctl_table *t;
	अक्षर path[माप("net/ipv4/conf/") + IFNAMSIZ];

	t = kmemdup(&devinet_sysctl, माप(*t), GFP_KERNEL);
	अगर (!t)
		जाओ out;

	क्रम (i = 0; i < ARRAY_SIZE(t->devinet_vars) - 1; i++) अणु
		t->devinet_vars[i].data += (अक्षर *)p - (अक्षर *)&ipv4_devconf;
		t->devinet_vars[i].extra1 = p;
		t->devinet_vars[i].extra2 = net;
	पूर्ण

	snम_लिखो(path, माप(path), "net/ipv4/conf/%s", dev_name);

	t->sysctl_header = रेजिस्टर_net_sysctl(net, path, t->devinet_vars);
	अगर (!t->sysctl_header)
		जाओ मुक्त;

	p->sysctl = t;

	inet_netconf_notअगरy_devconf(net, RTM_NEWNETCONF, NETCONFA_ALL,
				    अगरindex, p);
	वापस 0;

मुक्त:
	kमुक्त(t);
out:
	वापस -ENOBUFS;
पूर्ण

अटल व्योम __devinet_sysctl_unरेजिस्टर(काष्ठा net *net,
					काष्ठा ipv4_devconf *cnf, पूर्णांक अगरindex)
अणु
	काष्ठा devinet_sysctl_table *t = cnf->sysctl;

	अगर (t) अणु
		cnf->sysctl = शून्य;
		unरेजिस्टर_net_sysctl_table(t->sysctl_header);
		kमुक्त(t);
	पूर्ण

	inet_netconf_notअगरy_devconf(net, RTM_DELNETCONF, 0, अगरindex, शून्य);
पूर्ण

अटल पूर्णांक devinet_sysctl_रेजिस्टर(काष्ठा in_device *idev)
अणु
	पूर्णांक err;

	अगर (!sysctl_dev_name_is_allowed(idev->dev->name))
		वापस -EINVAL;

	err = neigh_sysctl_रेजिस्टर(idev->dev, idev->arp_parms, शून्य);
	अगर (err)
		वापस err;
	err = __devinet_sysctl_रेजिस्टर(dev_net(idev->dev), idev->dev->name,
					idev->dev->अगरindex, &idev->cnf);
	अगर (err)
		neigh_sysctl_unरेजिस्टर(idev->arp_parms);
	वापस err;
पूर्ण

अटल व्योम devinet_sysctl_unरेजिस्टर(काष्ठा in_device *idev)
अणु
	काष्ठा net *net = dev_net(idev->dev);

	__devinet_sysctl_unरेजिस्टर(net, &idev->cnf, idev->dev->अगरindex);
	neigh_sysctl_unरेजिस्टर(idev->arp_parms);
पूर्ण

अटल काष्ठा ctl_table ctl_क्रमward_entry[] = अणु
	अणु
		.procname	= "ip_forward",
		.data		= &ipv4_devconf.data[
					IPV4_DEVCONF_FORWARDING - 1],
		.maxlen		= माप(पूर्णांक),
		.mode		= 0644,
		.proc_handler	= devinet_sysctl_क्रमward,
		.extra1		= &ipv4_devconf,
		.extra2		= &init_net,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल __net_init पूर्णांक devinet_init_net(काष्ठा net *net)
अणु
	पूर्णांक err;
	काष्ठा ipv4_devconf *all, *dflt;
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table *tbl;
	काष्ठा ctl_table_header *क्रमw_hdr;
#पूर्ण_अगर

	err = -ENOMEM;
	all = kmemdup(&ipv4_devconf, माप(ipv4_devconf), GFP_KERNEL);
	अगर (!all)
		जाओ err_alloc_all;

	dflt = kmemdup(&ipv4_devconf_dflt, माप(ipv4_devconf_dflt), GFP_KERNEL);
	अगर (!dflt)
		जाओ err_alloc_dflt;

#अगर_घोषित CONFIG_SYSCTL
	tbl = kmemdup(ctl_क्रमward_entry, माप(ctl_क्रमward_entry), GFP_KERNEL);
	अगर (!tbl)
		जाओ err_alloc_ctl;

	tbl[0].data = &all->data[IPV4_DEVCONF_FORWARDING - 1];
	tbl[0].extra1 = all;
	tbl[0].extra2 = net;
#पूर्ण_अगर

	अगर (!net_eq(net, &init_net)) अणु
		अगर (IS_ENABLED(CONFIG_SYSCTL) &&
		    sysctl_devconf_inherit_init_net == 3) अणु
			/* copy from the current netns */
			स_नकल(all, current->nsproxy->net_ns->ipv4.devconf_all,
			       माप(ipv4_devconf));
			स_नकल(dflt,
			       current->nsproxy->net_ns->ipv4.devconf_dflt,
			       माप(ipv4_devconf_dflt));
		पूर्ण अन्यथा अगर (!IS_ENABLED(CONFIG_SYSCTL) ||
			   sysctl_devconf_inherit_init_net != 2) अणु
			/* inherit == 0 or 1: copy from init_net */
			स_नकल(all, init_net.ipv4.devconf_all,
			       माप(ipv4_devconf));
			स_नकल(dflt, init_net.ipv4.devconf_dflt,
			       माप(ipv4_devconf_dflt));
		पूर्ण
		/* अन्यथा inherit == 2: use compiled values */
	पूर्ण

#अगर_घोषित CONFIG_SYSCTL
	err = __devinet_sysctl_रेजिस्टर(net, "all", NETCONFA_IFINDEX_ALL, all);
	अगर (err < 0)
		जाओ err_reg_all;

	err = __devinet_sysctl_रेजिस्टर(net, "default",
					NETCONFA_IFINDEX_DEFAULT, dflt);
	अगर (err < 0)
		जाओ err_reg_dflt;

	err = -ENOMEM;
	क्रमw_hdr = रेजिस्टर_net_sysctl(net, "net/ipv4", tbl);
	अगर (!क्रमw_hdr)
		जाओ err_reg_ctl;
	net->ipv4.क्रमw_hdr = क्रमw_hdr;
#पूर्ण_अगर

	net->ipv4.devconf_all = all;
	net->ipv4.devconf_dflt = dflt;
	वापस 0;

#अगर_घोषित CONFIG_SYSCTL
err_reg_ctl:
	__devinet_sysctl_unरेजिस्टर(net, dflt, NETCONFA_IFINDEX_DEFAULT);
err_reg_dflt:
	__devinet_sysctl_unरेजिस्टर(net, all, NETCONFA_IFINDEX_ALL);
err_reg_all:
	kमुक्त(tbl);
err_alloc_ctl:
#पूर्ण_अगर
	kमुक्त(dflt);
err_alloc_dflt:
	kमुक्त(all);
err_alloc_all:
	वापस err;
पूर्ण

अटल __net_निकास व्योम devinet_निकास_net(काष्ठा net *net)
अणु
#अगर_घोषित CONFIG_SYSCTL
	काष्ठा ctl_table *tbl;

	tbl = net->ipv4.क्रमw_hdr->ctl_table_arg;
	unरेजिस्टर_net_sysctl_table(net->ipv4.क्रमw_hdr);
	__devinet_sysctl_unरेजिस्टर(net, net->ipv4.devconf_dflt,
				    NETCONFA_IFINDEX_DEFAULT);
	__devinet_sysctl_unरेजिस्टर(net, net->ipv4.devconf_all,
				    NETCONFA_IFINDEX_ALL);
	kमुक्त(tbl);
#पूर्ण_अगर
	kमुक्त(net->ipv4.devconf_dflt);
	kमुक्त(net->ipv4.devconf_all);
पूर्ण

अटल __net_initdata काष्ठा pernet_operations devinet_ops = अणु
	.init = devinet_init_net,
	.निकास = devinet_निकास_net,
पूर्ण;

अटल काष्ठा rtnl_af_ops inet_af_ops __पढ़ो_mostly = अणु
	.family		  = AF_INET,
	.fill_link_af	  = inet_fill_link_af,
	.get_link_af_size = inet_get_link_af_size,
	.validate_link_af = inet_validate_link_af,
	.set_link_af	  = inet_set_link_af,
पूर्ण;

व्योम __init devinet_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IN4_ADDR_HSIZE; i++)
		INIT_HLIST_HEAD(&inet_addr_lst[i]);

	रेजिस्टर_pernet_subsys(&devinet_ops);

	रेजिस्टर_gअगरconf(PF_INET, inet_gअगरconf);
	रेजिस्टर_netdevice_notअगरier(&ip_netdev_notअगरier);

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &check_lअगरeसमय_work, 0);

	rtnl_af_रेजिस्टर(&inet_af_ops);

	rtnl_रेजिस्टर(PF_INET, RTM_NEWADDR, inet_rपंचांग_newaddr, शून्य, 0);
	rtnl_रेजिस्टर(PF_INET, RTM_DELADDR, inet_rपंचांग_deladdr, शून्य, 0);
	rtnl_रेजिस्टर(PF_INET, RTM_GETADDR, शून्य, inet_dump_अगरaddr, 0);
	rtnl_रेजिस्टर(PF_INET, RTM_GETNETCONF, inet_netconf_get_devconf,
		      inet_netconf_dump_devconf, 0);
पूर्ण
