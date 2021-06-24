<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Anycast support क्रम IPv6
 *	Linux INET6 implementation
 *
 *	Authors:
 *	David L Stevens (dlstevens@us.ibm.com)
 *
 *	based heavily on net/ipv6/mcast.c
 */

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/route.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>

#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/ndisc.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>

#समावेश <net/checksum.h>

#घोषणा IN6_ADDR_HSIZE_SHIFT	8
#घोषणा IN6_ADDR_HSIZE		BIT(IN6_ADDR_HSIZE_SHIFT)
/*	anycast address hash table
 */
अटल काष्ठा hlist_head inet6_acaddr_lst[IN6_ADDR_HSIZE];
अटल DEFINE_SPINLOCK(acaddr_hash_lock);

अटल पूर्णांक ipv6_dev_ac_dec(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr);

अटल u32 inet6_acaddr_hash(काष्ठा net *net, स्थिर काष्ठा in6_addr *addr)
अणु
	u32 val = ipv6_addr_hash(addr) ^ net_hash_mix(net);

	वापस hash_32(val, IN6_ADDR_HSIZE_SHIFT);
पूर्ण

/*
 *	socket join an anycast group
 */

पूर्णांक ipv6_sock_ac_join(काष्ठा sock *sk, पूर्णांक अगरindex, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net_device *dev = शून्य;
	काष्ठा inet6_dev *idev;
	काष्ठा ipv6_ac_socklist *pac;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक	ishost = !net->ipv6.devconf_all->क्रमwarding;
	पूर्णांक	err = 0;

	ASSERT_RTNL();

	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (ipv6_addr_is_multicast(addr))
		वापस -EINVAL;

	अगर (अगरindex)
		dev = __dev_get_by_index(net, अगरindex);

	अगर (ipv6_chk_addr_and_flags(net, addr, dev, true, 0, IFA_F_TENTATIVE))
		वापस -EINVAL;

	pac = sock_kदो_स्मृति(sk, माप(काष्ठा ipv6_ac_socklist), GFP_KERNEL);
	अगर (!pac)
		वापस -ENOMEM;
	pac->acl_next = शून्य;
	pac->acl_addr = *addr;

	अगर (अगरindex == 0) अणु
		काष्ठा rt6_info *rt;

		rt = rt6_lookup(net, addr, शून्य, 0, शून्य, 0);
		अगर (rt) अणु
			dev = rt->dst.dev;
			ip6_rt_put(rt);
		पूर्ण अन्यथा अगर (ishost) अणु
			err = -EADDRNOTAVAIL;
			जाओ error;
		पूर्ण अन्यथा अणु
			/* router, no matching पूर्णांकerface: just pick one */
			dev = __dev_get_by_flags(net, IFF_UP,
						 IFF_UP | IFF_LOOPBACK);
		पूर्ण
	पूर्ण

	अगर (!dev) अणु
		err = -ENODEV;
		जाओ error;
	पूर्ण

	idev = __in6_dev_get(dev);
	अगर (!idev) अणु
		अगर (अगरindex)
			err = -ENODEV;
		अन्यथा
			err = -EADDRNOTAVAIL;
		जाओ error;
	पूर्ण
	/* reset ishost, now that we have a specअगरic device */
	ishost = !idev->cnf.क्रमwarding;

	pac->acl_अगरindex = dev->अगरindex;

	/* XXX
	 * For hosts, allow link-local or matching prefix anycasts.
	 * This obviates the need क्रम propagating anycast routes जबतक
	 * still allowing some non-router anycast participation.
	 */
	अगर (!ipv6_chk_prefix(addr, dev)) अणु
		अगर (ishost)
			err = -EADDRNOTAVAIL;
		अगर (err)
			जाओ error;
	पूर्ण

	err = __ipv6_dev_ac_inc(idev, addr);
	अगर (!err) अणु
		pac->acl_next = np->ipv6_ac_list;
		np->ipv6_ac_list = pac;
		pac = शून्य;
	पूर्ण

error:
	अगर (pac)
		sock_kमुक्त_s(sk, pac, माप(*pac));
	वापस err;
पूर्ण

/*
 *	socket leave an anycast group
 */
पूर्णांक ipv6_sock_ac_drop(काष्ठा sock *sk, पूर्णांक अगरindex, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net_device *dev;
	काष्ठा ipv6_ac_socklist *pac, *prev_pac;
	काष्ठा net *net = sock_net(sk);

	ASSERT_RTNL();

	prev_pac = शून्य;
	क्रम (pac = np->ipv6_ac_list; pac; pac = pac->acl_next) अणु
		अगर ((अगरindex == 0 || pac->acl_अगरindex == अगरindex) &&
		     ipv6_addr_equal(&pac->acl_addr, addr))
			अवरोध;
		prev_pac = pac;
	पूर्ण
	अगर (!pac)
		वापस -ENOENT;
	अगर (prev_pac)
		prev_pac->acl_next = pac->acl_next;
	अन्यथा
		np->ipv6_ac_list = pac->acl_next;

	dev = __dev_get_by_index(net, pac->acl_अगरindex);
	अगर (dev)
		ipv6_dev_ac_dec(dev, &pac->acl_addr);

	sock_kमुक्त_s(sk, pac, माप(*pac));
	वापस 0;
पूर्ण

व्योम __ipv6_sock_ac_बंद(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net_device *dev = शून्य;
	काष्ठा ipv6_ac_socklist *pac;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक	prev_index;

	ASSERT_RTNL();
	pac = np->ipv6_ac_list;
	np->ipv6_ac_list = शून्य;

	prev_index = 0;
	जबतक (pac) अणु
		काष्ठा ipv6_ac_socklist *next = pac->acl_next;

		अगर (pac->acl_अगरindex != prev_index) अणु
			dev = __dev_get_by_index(net, pac->acl_अगरindex);
			prev_index = pac->acl_अगरindex;
		पूर्ण
		अगर (dev)
			ipv6_dev_ac_dec(dev, &pac->acl_addr);
		sock_kमुक्त_s(sk, pac, माप(*pac));
		pac = next;
	पूर्ण
पूर्ण

व्योम ipv6_sock_ac_बंद(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	अगर (!np->ipv6_ac_list)
		वापस;
	rtnl_lock();
	__ipv6_sock_ac_बंद(sk);
	rtnl_unlock();
पूर्ण

अटल व्योम ipv6_add_acaddr_hash(काष्ठा net *net, काष्ठा अगरacaddr6 *aca)
अणु
	अचिन्हित पूर्णांक hash = inet6_acaddr_hash(net, &aca->aca_addr);

	spin_lock(&acaddr_hash_lock);
	hlist_add_head_rcu(&aca->aca_addr_lst, &inet6_acaddr_lst[hash]);
	spin_unlock(&acaddr_hash_lock);
पूर्ण

अटल व्योम ipv6_del_acaddr_hash(काष्ठा अगरacaddr6 *aca)
अणु
	spin_lock(&acaddr_hash_lock);
	hlist_del_init_rcu(&aca->aca_addr_lst);
	spin_unlock(&acaddr_hash_lock);
पूर्ण

अटल व्योम aca_get(काष्ठा अगरacaddr6 *aca)
अणु
	refcount_inc(&aca->aca_refcnt);
पूर्ण

अटल व्योम aca_मुक्त_rcu(काष्ठा rcu_head *h)
अणु
	काष्ठा अगरacaddr6 *aca = container_of(h, काष्ठा अगरacaddr6, rcu);

	fib6_info_release(aca->aca_rt);
	kमुक्त(aca);
पूर्ण

अटल व्योम aca_put(काष्ठा अगरacaddr6 *ac)
अणु
	अगर (refcount_dec_and_test(&ac->aca_refcnt)) अणु
		call_rcu(&ac->rcu, aca_मुक्त_rcu);
	पूर्ण
पूर्ण

अटल काष्ठा अगरacaddr6 *aca_alloc(काष्ठा fib6_info *f6i,
				   स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा अगरacaddr6 *aca;

	aca = kzalloc(माप(*aca), GFP_ATOMIC);
	अगर (!aca)
		वापस शून्य;

	aca->aca_addr = *addr;
	fib6_info_hold(f6i);
	aca->aca_rt = f6i;
	INIT_HLIST_NODE(&aca->aca_addr_lst);
	aca->aca_users = 1;
	/* aca_tstamp should be updated upon changes */
	aca->aca_cstamp = aca->aca_tstamp = jअगरfies;
	refcount_set(&aca->aca_refcnt, 1);

	वापस aca;
पूर्ण

/*
 *	device anycast group inc (add अगर not found)
 */
पूर्णांक __ipv6_dev_ac_inc(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा अगरacaddr6 *aca;
	काष्ठा fib6_info *f6i;
	काष्ठा net *net;
	पूर्णांक err;

	ASSERT_RTNL();

	ग_लिखो_lock_bh(&idev->lock);
	अगर (idev->dead) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	क्रम (aca = idev->ac_list; aca; aca = aca->aca_next) अणु
		अगर (ipv6_addr_equal(&aca->aca_addr, addr)) अणु
			aca->aca_users++;
			err = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	net = dev_net(idev->dev);
	f6i = addrconf_f6i_alloc(net, idev, addr, true, GFP_ATOMIC);
	अगर (IS_ERR(f6i)) अणु
		err = PTR_ERR(f6i);
		जाओ out;
	पूर्ण
	aca = aca_alloc(f6i, addr);
	अगर (!aca) अणु
		fib6_info_release(f6i);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	aca->aca_next = idev->ac_list;
	idev->ac_list = aca;

	/* Hold this क्रम addrconf_join_solict() below beक्रमe we unlock,
	 * it is alपढ़ोy exposed via idev->ac_list.
	 */
	aca_get(aca);
	ग_लिखो_unlock_bh(&idev->lock);

	ipv6_add_acaddr_hash(net, aca);

	ip6_ins_rt(net, f6i);

	addrconf_join_solict(idev->dev, &aca->aca_addr);

	aca_put(aca);
	वापस 0;
out:
	ग_लिखो_unlock_bh(&idev->lock);
	वापस err;
पूर्ण

/*
 *	device anycast group decrement
 */
पूर्णांक __ipv6_dev_ac_dec(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा अगरacaddr6 *aca, *prev_aca;

	ASSERT_RTNL();

	ग_लिखो_lock_bh(&idev->lock);
	prev_aca = शून्य;
	क्रम (aca = idev->ac_list; aca; aca = aca->aca_next) अणु
		अगर (ipv6_addr_equal(&aca->aca_addr, addr))
			अवरोध;
		prev_aca = aca;
	पूर्ण
	अगर (!aca) अणु
		ग_लिखो_unlock_bh(&idev->lock);
		वापस -ENOENT;
	पूर्ण
	अगर (--aca->aca_users > 0) अणु
		ग_लिखो_unlock_bh(&idev->lock);
		वापस 0;
	पूर्ण
	अगर (prev_aca)
		prev_aca->aca_next = aca->aca_next;
	अन्यथा
		idev->ac_list = aca->aca_next;
	ग_लिखो_unlock_bh(&idev->lock);
	ipv6_del_acaddr_hash(aca);
	addrconf_leave_solict(idev, &aca->aca_addr);

	ip6_del_rt(dev_net(idev->dev), aca->aca_rt, false);

	aca_put(aca);
	वापस 0;
पूर्ण

/* called with rtnl_lock() */
अटल पूर्णांक ipv6_dev_ac_dec(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);

	अगर (!idev)
		वापस -ENODEV;
	वापस __ipv6_dev_ac_dec(idev, addr);
पूर्ण

व्योम ipv6_ac_destroy_dev(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरacaddr6 *aca;

	ग_लिखो_lock_bh(&idev->lock);
	जबतक ((aca = idev->ac_list) != शून्य) अणु
		idev->ac_list = aca->aca_next;
		ग_लिखो_unlock_bh(&idev->lock);

		ipv6_del_acaddr_hash(aca);

		addrconf_leave_solict(idev, &aca->aca_addr);

		ip6_del_rt(dev_net(idev->dev), aca->aca_rt, false);

		aca_put(aca);

		ग_लिखो_lock_bh(&idev->lock);
	पूर्ण
	ग_लिखो_unlock_bh(&idev->lock);
पूर्ण

/*
 *	check अगर the पूर्णांकerface has this anycast address
 *	called with rcu_पढ़ो_lock()
 */
अटल bool ipv6_chk_acast_dev(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा inet6_dev *idev;
	काष्ठा अगरacaddr6 *aca;

	idev = __in6_dev_get(dev);
	अगर (idev) अणु
		पढ़ो_lock_bh(&idev->lock);
		क्रम (aca = idev->ac_list; aca; aca = aca->aca_next)
			अगर (ipv6_addr_equal(&aca->aca_addr, addr))
				अवरोध;
		पढ़ो_unlock_bh(&idev->lock);
		वापस aca != शून्य;
	पूर्ण
	वापस false;
पूर्ण

/*
 *	check अगर given पूर्णांकerface (or any, अगर dev==0) has this anycast address
 */
bool ipv6_chk_acast_addr(काष्ठा net *net, काष्ठा net_device *dev,
			 स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा net_device *nh_dev;
	काष्ठा अगरacaddr6 *aca;
	bool found = false;

	rcu_पढ़ो_lock();
	अगर (dev)
		found = ipv6_chk_acast_dev(dev, addr);
	अन्यथा अणु
		अचिन्हित पूर्णांक hash = inet6_acaddr_hash(net, addr);

		hlist_क्रम_each_entry_rcu(aca, &inet6_acaddr_lst[hash],
					 aca_addr_lst) अणु
			nh_dev = fib6_info_nh_dev(aca->aca_rt);
			अगर (!nh_dev || !net_eq(dev_net(nh_dev), net))
				जारी;
			अगर (ipv6_addr_equal(&aca->aca_addr, addr)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस found;
पूर्ण

/*	check अगर this anycast address is link-local on given पूर्णांकerface or
 *	is global
 */
bool ipv6_chk_acast_addr_src(काष्ठा net *net, काष्ठा net_device *dev,
			     स्थिर काष्ठा in6_addr *addr)
अणु
	वापस ipv6_chk_acast_addr(net,
				   (ipv6_addr_type(addr) & IPV6_ADDR_LINKLOCAL ?
				    dev : शून्य),
				   addr);
पूर्ण

#अगर_घोषित CONFIG_PROC_FS
काष्ठा ac6_iter_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
पूर्ण;

#घोषणा ac6_seq_निजी(seq)	((काष्ठा ac6_iter_state *)(seq)->निजी)

अटल अंतरभूत काष्ठा अगरacaddr6 *ac6_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा अगरacaddr6 *im = शून्य;
	काष्ठा ac6_iter_state *state = ac6_seq_निजी(seq);
	काष्ठा net *net = seq_file_net(seq);

	state->idev = शून्य;
	क्रम_each_netdev_rcu(net, state->dev) अणु
		काष्ठा inet6_dev *idev;
		idev = __in6_dev_get(state->dev);
		अगर (!idev)
			जारी;
		पढ़ो_lock_bh(&idev->lock);
		im = idev->ac_list;
		अगर (im) अणु
			state->idev = idev;
			अवरोध;
		पूर्ण
		पढ़ो_unlock_bh(&idev->lock);
	पूर्ण
	वापस im;
पूर्ण

अटल काष्ठा अगरacaddr6 *ac6_get_next(काष्ठा seq_file *seq, काष्ठा अगरacaddr6 *im)
अणु
	काष्ठा ac6_iter_state *state = ac6_seq_निजी(seq);

	im = im->aca_next;
	जबतक (!im) अणु
		अगर (likely(state->idev != शून्य))
			पढ़ो_unlock_bh(&state->idev->lock);

		state->dev = next_net_device_rcu(state->dev);
		अगर (!state->dev) अणु
			state->idev = शून्य;
			अवरोध;
		पूर्ण
		state->idev = __in6_dev_get(state->dev);
		अगर (!state->idev)
			जारी;
		पढ़ो_lock_bh(&state->idev->lock);
		im = state->idev->ac_list;
	पूर्ण
	वापस im;
पूर्ण

अटल काष्ठा अगरacaddr6 *ac6_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा अगरacaddr6 *im = ac6_get_first(seq);
	अगर (im)
		जबतक (pos && (im = ac6_get_next(seq, im)) != शून्य)
			--pos;
	वापस pos ? शून्य : im;
पूर्ण

अटल व्योम *ac6_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस ac6_get_idx(seq, *pos);
पूर्ण

अटल व्योम *ac6_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा अगरacaddr6 *im = ac6_get_next(seq, v);

	++*pos;
	वापस im;
पूर्ण

अटल व्योम ac6_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	काष्ठा ac6_iter_state *state = ac6_seq_निजी(seq);

	अगर (likely(state->idev != शून्य)) अणु
		पढ़ो_unlock_bh(&state->idev->lock);
		state->idev = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक ac6_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा अगरacaddr6 *im = (काष्ठा अगरacaddr6 *)v;
	काष्ठा ac6_iter_state *state = ac6_seq_निजी(seq);

	seq_म_लिखो(seq, "%-4d %-15s %pi6 %5d\n",
		   state->dev->अगरindex, state->dev->name,
		   &im->aca_addr, im->aca_users);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations ac6_seq_ops = अणु
	.start	=	ac6_seq_start,
	.next	=	ac6_seq_next,
	.stop	=	ac6_seq_stop,
	.show	=	ac6_seq_show,
पूर्ण;

पूर्णांक __net_init ac6_proc_init(काष्ठा net *net)
अणु
	अगर (!proc_create_net("anycast6", 0444, net->proc_net, &ac6_seq_ops,
			माप(काष्ठा ac6_iter_state)))
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम ac6_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("anycast6", net->proc_net);
पूर्ण
#पूर्ण_अगर

/*	Init / cleanup code
 */
पूर्णांक __init ipv6_anycast_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IN6_ADDR_HSIZE; i++)
		INIT_HLIST_HEAD(&inet6_acaddr_lst[i]);
	वापस 0;
पूर्ण

व्योम ipv6_anycast_cleanup(व्योम)
अणु
	पूर्णांक i;

	spin_lock(&acaddr_hash_lock);
	क्रम (i = 0; i < IN6_ADDR_HSIZE; i++)
		WARN_ON(!hlist_empty(&inet6_acaddr_lst[i]));
	spin_unlock(&acaddr_hash_lock);
पूर्ण
