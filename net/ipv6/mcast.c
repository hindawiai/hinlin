<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Multicast support क्रम IPv6
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *
 *	Based on linux/ipv4/igmp.c and linux/ipv4/ip_sockglue.c
 */

/* Changes:
 *
 *	yoshfuji	: fix क्रमmat of router-alert option
 *	YOSHIFUJI Hideaki @USAGI:
 *		Fixed source address क्रम MLD message based on
 *		<draft-ietf-magma-mld-source-05.txt>.
 *	YOSHIFUJI Hideaki @USAGI:
 *		- Ignore Queries क्रम invalid addresses.
 *		- MLD क्रम link-local addresses.
 *	David L Stevens <dlstevens@us.ibm.com>:
 *		- MLDv2 support
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/net.h>
#समावेश <linux/in.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/route.h>
#समावेश <linux/init.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/mld.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>

#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/अगर_inet6.h>
#समावेश <net/ndisc.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>
#समावेश <net/inet_common.h>

#समावेश <net/ip6_checksum.h>

/* Ensure that we have काष्ठा in6_addr aligned on 32bit word. */
अटल पूर्णांक __mld2_query_bugs[] __attribute__((__unused__)) = अणु
	BUILD_BUG_ON_ZERO(दुरत्व(काष्ठा mld2_query, mld2q_srcs) % 4),
	BUILD_BUG_ON_ZERO(दुरत्व(काष्ठा mld2_report, mld2r_grec) % 4),
	BUILD_BUG_ON_ZERO(दुरत्व(काष्ठा mld2_grec, grec_mca) % 4)
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *mld_wq;
अटल काष्ठा in6_addr mld2_all_mcr = MLD2_ALL_MCR_INIT;

अटल व्योम igmp6_join_group(काष्ठा अगरmcaddr6 *ma);
अटल व्योम igmp6_leave_group(काष्ठा अगरmcaddr6 *ma);
अटल व्योम mld_mca_work(काष्ठा work_काष्ठा *work);

अटल व्योम mld_अगरc_event(काष्ठा inet6_dev *idev);
अटल bool mld_in_v1_mode(स्थिर काष्ठा inet6_dev *idev);
अटल पूर्णांक sf_setstate(काष्ठा अगरmcaddr6 *pmc);
अटल व्योम sf_markstate(काष्ठा अगरmcaddr6 *pmc);
अटल व्योम ip6_mc_clear_src(काष्ठा अगरmcaddr6 *pmc);
अटल पूर्णांक ip6_mc_del_src(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *pmca,
			  पूर्णांक sभ_शेषe, पूर्णांक sfcount, स्थिर काष्ठा in6_addr *psfsrc,
			  पूर्णांक delta);
अटल पूर्णांक ip6_mc_add_src(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *pmca,
			  पूर्णांक sभ_शेषe, पूर्णांक sfcount, स्थिर काष्ठा in6_addr *psfsrc,
			  पूर्णांक delta);
अटल पूर्णांक ip6_mc_leave_src(काष्ठा sock *sk, काष्ठा ipv6_mc_socklist *iml,
			    काष्ठा inet6_dev *idev);
अटल पूर्णांक __ipv6_dev_mc_inc(काष्ठा net_device *dev,
			     स्थिर काष्ठा in6_addr *addr, अचिन्हित पूर्णांक mode);

#घोषणा MLD_QRV_DEFAULT		2
/* RFC3810, 9.2. Query Interval */
#घोषणा MLD_QI_DEFAULT		(125 * HZ)
/* RFC3810, 9.3. Query Response Interval */
#घोषणा MLD_QRI_DEFAULT		(10 * HZ)

/* RFC3810, 8.1 Query Version Distinctions */
#घोषणा MLD_V1_QUERY_LEN	24
#घोषणा MLD_V2_QUERY_LEN_MIN	28

#घोषणा IPV6_MLD_MAX_MSF	64

पूर्णांक sysctl_mld_max_msf __पढ़ो_mostly = IPV6_MLD_MAX_MSF;
पूर्णांक sysctl_mld_qrv __पढ़ो_mostly = MLD_QRV_DEFAULT;

/*
 *	socket join on multicast group
 */
#घोषणा mc_dereference(e, idev) \
	rcu_dereference_रक्षित(e, lockdep_is_held(&(idev)->mc_lock))

#घोषणा sock_dereference(e, sk) \
	rcu_dereference_रक्षित(e, lockdep_sock_is_held(sk))

#घोषणा क्रम_each_pmc_socklock(np, sk, pmc)			\
	क्रम (pmc = sock_dereference((np)->ipv6_mc_list, sk);	\
	     pmc;						\
	     pmc = sock_dereference(pmc->next, sk))

#घोषणा क्रम_each_pmc_rcu(np, pmc)				\
	क्रम (pmc = rcu_dereference((np)->ipv6_mc_list);		\
	     pmc;						\
	     pmc = rcu_dereference(pmc->next))

#घोषणा क्रम_each_psf_mघड़ी(mc, psf)				\
	क्रम (psf = mc_dereference((mc)->mca_sources, mc->idev);	\
	     psf;						\
	     psf = mc_dereference(psf->sf_next, mc->idev))

#घोषणा क्रम_each_psf_rcu(mc, psf)				\
	क्रम (psf = rcu_dereference((mc)->mca_sources);		\
	     psf;						\
	     psf = rcu_dereference(psf->sf_next))

#घोषणा क्रम_each_psf_tomb(mc, psf)				\
	क्रम (psf = mc_dereference((mc)->mca_tomb, mc->idev);	\
	     psf;						\
	     psf = mc_dereference(psf->sf_next, mc->idev))

#घोषणा क्रम_each_mc_mघड़ी(idev, mc)				\
	क्रम (mc = mc_dereference((idev)->mc_list, idev);	\
	     mc;						\
	     mc = mc_dereference(mc->next, idev))

#घोषणा क्रम_each_mc_rcu(idev, mc)				\
	क्रम (mc = rcu_dereference((idev)->mc_list);             \
	     mc;                                                \
	     mc = rcu_dereference(mc->next))

#घोषणा क्रम_each_mc_tomb(idev, mc)				\
	क्रम (mc = mc_dereference((idev)->mc_tomb, idev);	\
	     mc;						\
	     mc = mc_dereference(mc->next, idev))

अटल पूर्णांक unsolicited_report_पूर्णांकerval(काष्ठा inet6_dev *idev)
अणु
	पूर्णांक iv;

	अगर (mld_in_v1_mode(idev))
		iv = idev->cnf.mldv1_unsolicited_report_पूर्णांकerval;
	अन्यथा
		iv = idev->cnf.mldv2_unsolicited_report_पूर्णांकerval;

	वापस iv > 0 ? iv : 1;
पूर्ण

अटल पूर्णांक __ipv6_sock_mc_join(काष्ठा sock *sk, पूर्णांक अगरindex,
			       स्थिर काष्ठा in6_addr *addr, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा ipv6_mc_socklist *mc_lst;
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक err;

	ASSERT_RTNL();

	अगर (!ipv6_addr_is_multicast(addr))
		वापस -EINVAL;

	क्रम_each_pmc_socklock(np, sk, mc_lst) अणु
		अगर ((अगरindex == 0 || mc_lst->अगरindex == अगरindex) &&
		    ipv6_addr_equal(&mc_lst->addr, addr))
			वापस -EADDRINUSE;
	पूर्ण

	mc_lst = sock_kदो_स्मृति(sk, माप(काष्ठा ipv6_mc_socklist), GFP_KERNEL);

	अगर (!mc_lst)
		वापस -ENOMEM;

	mc_lst->next = शून्य;
	mc_lst->addr = *addr;

	अगर (अगरindex == 0) अणु
		काष्ठा rt6_info *rt;
		rt = rt6_lookup(net, addr, शून्य, 0, शून्य, 0);
		अगर (rt) अणु
			dev = rt->dst.dev;
			ip6_rt_put(rt);
		पूर्ण
	पूर्ण अन्यथा
		dev = __dev_get_by_index(net, अगरindex);

	अगर (!dev) अणु
		sock_kमुक्त_s(sk, mc_lst, माप(*mc_lst));
		वापस -ENODEV;
	पूर्ण

	mc_lst->अगरindex = dev->अगरindex;
	mc_lst->sभ_शेषe = mode;
	RCU_INIT_POINTER(mc_lst->sflist, शून्य);

	/*
	 *	now add/increase the group membership on the device
	 */

	err = __ipv6_dev_mc_inc(dev, addr, mode);

	अगर (err) अणु
		sock_kमुक्त_s(sk, mc_lst, माप(*mc_lst));
		वापस err;
	पूर्ण

	mc_lst->next = np->ipv6_mc_list;
	rcu_assign_poपूर्णांकer(np->ipv6_mc_list, mc_lst);

	वापस 0;
पूर्ण

पूर्णांक ipv6_sock_mc_join(काष्ठा sock *sk, पूर्णांक अगरindex, स्थिर काष्ठा in6_addr *addr)
अणु
	वापस __ipv6_sock_mc_join(sk, अगरindex, addr, MCAST_EXCLUDE);
पूर्ण
EXPORT_SYMBOL(ipv6_sock_mc_join);

पूर्णांक ipv6_sock_mc_join_ssm(काष्ठा sock *sk, पूर्णांक अगरindex,
			  स्थिर काष्ठा in6_addr *addr, अचिन्हित पूर्णांक mode)
अणु
	वापस __ipv6_sock_mc_join(sk, अगरindex, addr, mode);
पूर्ण

/*
 *	socket leave on multicast group
 */
पूर्णांक ipv6_sock_mc_drop(काष्ठा sock *sk, पूर्णांक अगरindex, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_mc_socklist *mc_lst;
	काष्ठा ipv6_mc_socklist __rcu **lnk;
	काष्ठा net *net = sock_net(sk);

	ASSERT_RTNL();

	अगर (!ipv6_addr_is_multicast(addr))
		वापस -EINVAL;

	क्रम (lnk = &np->ipv6_mc_list;
	     (mc_lst = sock_dereference(*lnk, sk)) != शून्य;
	      lnk = &mc_lst->next) अणु
		अगर ((अगरindex == 0 || mc_lst->अगरindex == अगरindex) &&
		    ipv6_addr_equal(&mc_lst->addr, addr)) अणु
			काष्ठा net_device *dev;

			*lnk = mc_lst->next;

			dev = __dev_get_by_index(net, mc_lst->अगरindex);
			अगर (dev) अणु
				काष्ठा inet6_dev *idev = __in6_dev_get(dev);

				ip6_mc_leave_src(sk, mc_lst, idev);
				अगर (idev)
					__ipv6_dev_mc_dec(idev, &mc_lst->addr);
			पूर्ण अन्यथा अणु
				ip6_mc_leave_src(sk, mc_lst, शून्य);
			पूर्ण

			atomic_sub(माप(*mc_lst), &sk->sk_omem_alloc);
			kमुक्त_rcu(mc_lst, rcu);
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EADDRNOTAVAIL;
पूर्ण
EXPORT_SYMBOL(ipv6_sock_mc_drop);

अटल काष्ठा inet6_dev *ip6_mc_find_dev_rtnl(काष्ठा net *net,
					      स्थिर काष्ठा in6_addr *group,
					      पूर्णांक अगरindex)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा inet6_dev *idev = शून्य;

	अगर (अगरindex == 0) अणु
		काष्ठा rt6_info *rt = rt6_lookup(net, group, शून्य, 0, शून्य, 0);

		अगर (rt) अणु
			dev = rt->dst.dev;
			ip6_rt_put(rt);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev = __dev_get_by_index(net, अगरindex);
	पूर्ण

	अगर (!dev)
		वापस शून्य;
	idev = __in6_dev_get(dev);
	अगर (!idev)
		वापस शून्य;
	अगर (idev->dead)
		वापस शून्य;
	वापस idev;
पूर्ण

व्योम __ipv6_sock_mc_बंद(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_mc_socklist *mc_lst;
	काष्ठा net *net = sock_net(sk);

	ASSERT_RTNL();

	जबतक ((mc_lst = sock_dereference(np->ipv6_mc_list, sk)) != शून्य) अणु
		काष्ठा net_device *dev;

		np->ipv6_mc_list = mc_lst->next;

		dev = __dev_get_by_index(net, mc_lst->अगरindex);
		अगर (dev) अणु
			काष्ठा inet6_dev *idev = __in6_dev_get(dev);

			ip6_mc_leave_src(sk, mc_lst, idev);
			अगर (idev)
				__ipv6_dev_mc_dec(idev, &mc_lst->addr);
		पूर्ण अन्यथा अणु
			ip6_mc_leave_src(sk, mc_lst, शून्य);
		पूर्ण

		atomic_sub(माप(*mc_lst), &sk->sk_omem_alloc);
		kमुक्त_rcu(mc_lst, rcu);
	पूर्ण
पूर्ण

व्योम ipv6_sock_mc_बंद(काष्ठा sock *sk)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);

	अगर (!rcu_access_poपूर्णांकer(np->ipv6_mc_list))
		वापस;

	rtnl_lock();
	lock_sock(sk);
	__ipv6_sock_mc_बंद(sk);
	release_sock(sk);
	rtnl_unlock();
पूर्ण

पूर्णांक ip6_mc_source(पूर्णांक add, पूर्णांक omode, काष्ठा sock *sk,
	काष्ठा group_source_req *pgsr)
अणु
	काष्ठा in6_addr *source, *group;
	काष्ठा ipv6_mc_socklist *pmc;
	काष्ठा inet6_dev *idev;
	काष्ठा ipv6_pinfo *inet6 = inet6_sk(sk);
	काष्ठा ip6_sf_socklist *psl;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक i, j, rv;
	पूर्णांक leavegroup = 0;
	पूर्णांक err;

	source = &((काष्ठा sockaddr_in6 *)&pgsr->gsr_source)->sin6_addr;
	group = &((काष्ठा sockaddr_in6 *)&pgsr->gsr_group)->sin6_addr;

	अगर (!ipv6_addr_is_multicast(group))
		वापस -EINVAL;

	idev = ip6_mc_find_dev_rtnl(net, group, pgsr->gsr_पूर्णांकerface);
	अगर (!idev)
		वापस -ENODEV;

	err = -EADDRNOTAVAIL;

	mutex_lock(&idev->mc_lock);
	क्रम_each_pmc_socklock(inet6, sk, pmc) अणु
		अगर (pgsr->gsr_पूर्णांकerface && pmc->अगरindex != pgsr->gsr_पूर्णांकerface)
			जारी;
		अगर (ipv6_addr_equal(&pmc->addr, group))
			अवरोध;
	पूर्ण
	अगर (!pmc) अणु		/* must have a prior join */
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	/* अगर a source filter was set, must be the same mode as beक्रमe */
	अगर (rcu_access_poपूर्णांकer(pmc->sflist)) अणु
		अगर (pmc->sभ_शेषe != omode) अणु
			err = -EINVAL;
			जाओ करोne;
		पूर्ण
	पूर्ण अन्यथा अगर (pmc->sभ_शेषe != omode) अणु
		/* allow mode चयनes क्रम empty-set filters */
		ip6_mc_add_src(idev, group, omode, 0, शून्य, 0);
		ip6_mc_del_src(idev, group, pmc->sभ_शेषe, 0, शून्य, 0);
		pmc->sभ_शेषe = omode;
	पूर्ण

	psl = sock_dereference(pmc->sflist, sk);
	अगर (!add) अणु
		अगर (!psl)
			जाओ करोne;	/* err = -EADDRNOTAVAIL */
		rv = !0;
		क्रम (i = 0; i < psl->sl_count; i++) अणु
			rv = !ipv6_addr_equal(&psl->sl_addr[i], source);
			अगर (rv == 0)
				अवरोध;
		पूर्ण
		अगर (rv)		/* source not found */
			जाओ करोne;	/* err = -EADDRNOTAVAIL */

		/* special हाल - (INCLUDE, empty) == LEAVE_GROUP */
		अगर (psl->sl_count == 1 && omode == MCAST_INCLUDE) अणु
			leavegroup = 1;
			जाओ करोne;
		पूर्ण

		/* update the पूर्णांकerface filter */
		ip6_mc_del_src(idev, group, omode, 1, source, 1);

		क्रम (j = i+1; j < psl->sl_count; j++)
			psl->sl_addr[j-1] = psl->sl_addr[j];
		psl->sl_count--;
		err = 0;
		जाओ करोne;
	पूर्ण
	/* अन्यथा, add a new source to the filter */

	अगर (psl && psl->sl_count >= sysctl_mld_max_msf) अणु
		err = -ENOBUFS;
		जाओ करोne;
	पूर्ण
	अगर (!psl || psl->sl_count == psl->sl_max) अणु
		काष्ठा ip6_sf_socklist *newpsl;
		पूर्णांक count = IP6_SFBLOCK;

		अगर (psl)
			count += psl->sl_max;
		newpsl = sock_kदो_स्मृति(sk, IP6_SFLSIZE(count), GFP_KERNEL);
		अगर (!newpsl) अणु
			err = -ENOBUFS;
			जाओ करोne;
		पूर्ण
		newpsl->sl_max = count;
		newpsl->sl_count = count - IP6_SFBLOCK;
		अगर (psl) अणु
			क्रम (i = 0; i < psl->sl_count; i++)
				newpsl->sl_addr[i] = psl->sl_addr[i];
			atomic_sub(IP6_SFLSIZE(psl->sl_max), &sk->sk_omem_alloc);
			kमुक्त_rcu(psl, rcu);
		पूर्ण
		psl = newpsl;
		rcu_assign_poपूर्णांकer(pmc->sflist, psl);
	पूर्ण
	rv = 1;	/* > 0 क्रम insert logic below अगर sl_count is 0 */
	क्रम (i = 0; i < psl->sl_count; i++) अणु
		rv = !ipv6_addr_equal(&psl->sl_addr[i], source);
		अगर (rv == 0) /* There is an error in the address. */
			जाओ करोne;
	पूर्ण
	क्रम (j = psl->sl_count-1; j >= i; j--)
		psl->sl_addr[j+1] = psl->sl_addr[j];
	psl->sl_addr[i] = *source;
	psl->sl_count++;
	err = 0;
	/* update the पूर्णांकerface list */
	ip6_mc_add_src(idev, group, omode, 1, source, 1);
करोne:
	mutex_unlock(&idev->mc_lock);
	अगर (leavegroup)
		err = ipv6_sock_mc_drop(sk, pgsr->gsr_पूर्णांकerface, group);
	वापस err;
पूर्ण

पूर्णांक ip6_mc_msfilter(काष्ठा sock *sk, काष्ठा group_filter *gsf,
		    काष्ठा sockaddr_storage *list)
अणु
	स्थिर काष्ठा in6_addr *group;
	काष्ठा ipv6_mc_socklist *pmc;
	काष्ठा inet6_dev *idev;
	काष्ठा ipv6_pinfo *inet6 = inet6_sk(sk);
	काष्ठा ip6_sf_socklist *newpsl, *psl;
	काष्ठा net *net = sock_net(sk);
	पूर्णांक leavegroup = 0;
	पूर्णांक i, err;

	group = &((काष्ठा sockaddr_in6 *)&gsf->gf_group)->sin6_addr;

	अगर (!ipv6_addr_is_multicast(group))
		वापस -EINVAL;
	अगर (gsf->gf_भ_शेषe != MCAST_INCLUDE &&
	    gsf->gf_भ_शेषe != MCAST_EXCLUDE)
		वापस -EINVAL;

	idev = ip6_mc_find_dev_rtnl(net, group, gsf->gf_पूर्णांकerface);
	अगर (!idev)
		वापस -ENODEV;

	err = 0;

	अगर (gsf->gf_भ_शेषe == MCAST_INCLUDE && gsf->gf_numsrc == 0) अणु
		leavegroup = 1;
		जाओ करोne;
	पूर्ण

	क्रम_each_pmc_socklock(inet6, sk, pmc) अणु
		अगर (pmc->अगरindex != gsf->gf_पूर्णांकerface)
			जारी;
		अगर (ipv6_addr_equal(&pmc->addr, group))
			अवरोध;
	पूर्ण
	अगर (!pmc) अणु		/* must have a prior join */
		err = -EINVAL;
		जाओ करोne;
	पूर्ण
	अगर (gsf->gf_numsrc) अणु
		newpsl = sock_kदो_स्मृति(sk, IP6_SFLSIZE(gsf->gf_numsrc),
							  GFP_KERNEL);
		अगर (!newpsl) अणु
			err = -ENOBUFS;
			जाओ करोne;
		पूर्ण
		newpsl->sl_max = newpsl->sl_count = gsf->gf_numsrc;
		क्रम (i = 0; i < newpsl->sl_count; ++i, ++list) अणु
			काष्ठा sockaddr_in6 *psin6;

			psin6 = (काष्ठा sockaddr_in6 *)list;
			newpsl->sl_addr[i] = psin6->sin6_addr;
		पूर्ण
		mutex_lock(&idev->mc_lock);
		err = ip6_mc_add_src(idev, group, gsf->gf_भ_शेषe,
				     newpsl->sl_count, newpsl->sl_addr, 0);
		अगर (err) अणु
			mutex_unlock(&idev->mc_lock);
			sock_kमुक्त_s(sk, newpsl, IP6_SFLSIZE(newpsl->sl_max));
			जाओ करोne;
		पूर्ण
		mutex_unlock(&idev->mc_lock);
	पूर्ण अन्यथा अणु
		newpsl = शून्य;
		mutex_lock(&idev->mc_lock);
		ip6_mc_add_src(idev, group, gsf->gf_भ_शेषe, 0, शून्य, 0);
		mutex_unlock(&idev->mc_lock);
	पूर्ण

	mutex_lock(&idev->mc_lock);
	psl = sock_dereference(pmc->sflist, sk);
	अगर (psl) अणु
		ip6_mc_del_src(idev, group, pmc->sभ_शेषe,
			       psl->sl_count, psl->sl_addr, 0);
		atomic_sub(IP6_SFLSIZE(psl->sl_max), &sk->sk_omem_alloc);
		kमुक्त_rcu(psl, rcu);
	पूर्ण अन्यथा अणु
		ip6_mc_del_src(idev, group, pmc->sभ_शेषe, 0, शून्य, 0);
	पूर्ण
	mutex_unlock(&idev->mc_lock);
	rcu_assign_poपूर्णांकer(pmc->sflist, newpsl);
	pmc->sभ_शेषe = gsf->gf_भ_शेषe;
	err = 0;
करोne:
	अगर (leavegroup)
		err = ipv6_sock_mc_drop(sk, gsf->gf_पूर्णांकerface, group);
	वापस err;
पूर्ण

पूर्णांक ip6_mc_msfget(काष्ठा sock *sk, काष्ठा group_filter *gsf,
		  काष्ठा sockaddr_storage __user *p)
अणु
	काष्ठा ipv6_pinfo *inet6 = inet6_sk(sk);
	स्थिर काष्ठा in6_addr *group;
	काष्ठा ipv6_mc_socklist *pmc;
	काष्ठा ip6_sf_socklist *psl;
	पूर्णांक i, count, copycount;

	group = &((काष्ठा sockaddr_in6 *)&gsf->gf_group)->sin6_addr;

	अगर (!ipv6_addr_is_multicast(group))
		वापस -EINVAL;

	/* changes to the ipv6_mc_list require the socket lock and
	 * rtnl lock. We have the socket lock, so पढ़ोing the list is safe.
	 */

	क्रम_each_pmc_socklock(inet6, sk, pmc) अणु
		अगर (pmc->अगरindex != gsf->gf_पूर्णांकerface)
			जारी;
		अगर (ipv6_addr_equal(group, &pmc->addr))
			अवरोध;
	पूर्ण
	अगर (!pmc)		/* must have a prior join */
		वापस -EADDRNOTAVAIL;

	gsf->gf_भ_शेषe = pmc->sभ_शेषe;
	psl = sock_dereference(pmc->sflist, sk);
	count = psl ? psl->sl_count : 0;

	copycount = count < gsf->gf_numsrc ? count : gsf->gf_numsrc;
	gsf->gf_numsrc = count;

	क्रम (i = 0; i < copycount; i++, p++) अणु
		काष्ठा sockaddr_in6 *psin6;
		काष्ठा sockaddr_storage ss;

		psin6 = (काष्ठा sockaddr_in6 *)&ss;
		स_रखो(&ss, 0, माप(ss));
		psin6->sin6_family = AF_INET6;
		psin6->sin6_addr = psl->sl_addr[i];
		अगर (copy_to_user(p, &ss, माप(ss)))
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

bool inet6_mc_check(काष्ठा sock *sk, स्थिर काष्ठा in6_addr *mc_addr,
		    स्थिर काष्ठा in6_addr *src_addr)
अणु
	काष्ठा ipv6_pinfo *np = inet6_sk(sk);
	काष्ठा ipv6_mc_socklist *mc;
	काष्ठा ip6_sf_socklist *psl;
	bool rv = true;

	rcu_पढ़ो_lock();
	क्रम_each_pmc_rcu(np, mc) अणु
		अगर (ipv6_addr_equal(&mc->addr, mc_addr))
			अवरोध;
	पूर्ण
	अगर (!mc) अणु
		rcu_पढ़ो_unlock();
		वापस np->mc_all;
	पूर्ण
	psl = rcu_dereference(mc->sflist);
	अगर (!psl) अणु
		rv = mc->sभ_शेषe == MCAST_EXCLUDE;
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		क्रम (i = 0; i < psl->sl_count; i++) अणु
			अगर (ipv6_addr_equal(&psl->sl_addr[i], src_addr))
				अवरोध;
		पूर्ण
		अगर (mc->sभ_शेषe == MCAST_INCLUDE && i >= psl->sl_count)
			rv = false;
		अगर (mc->sभ_शेषe == MCAST_EXCLUDE && i < psl->sl_count)
			rv = false;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस rv;
पूर्ण

/* called with mc_lock */
अटल व्योम igmp6_group_added(काष्ठा अगरmcaddr6 *mc)
अणु
	काष्ठा net_device *dev = mc->idev->dev;
	अक्षर buf[MAX_ADDR_LEN];

	अगर (IPV6_ADDR_MC_SCOPE(&mc->mca_addr) <
	    IPV6_ADDR_SCOPE_LINKLOCAL)
		वापस;

	अगर (!(mc->mca_flags&MAF_LOADED)) अणु
		mc->mca_flags |= MAF_LOADED;
		अगर (ndisc_mc_map(&mc->mca_addr, buf, dev, 0) == 0)
			dev_mc_add(dev, buf);
	पूर्ण

	अगर (!(dev->flags & IFF_UP) || (mc->mca_flags & MAF_NOREPORT))
		वापस;

	अगर (mld_in_v1_mode(mc->idev)) अणु
		igmp6_join_group(mc);
		वापस;
	पूर्ण
	/* अन्यथा v2 */

	/* Based on RFC3810 6.1, क्रम newly added INCLUDE SSM, we
	 * should not send filter-mode change record as the mode
	 * should be from IN() to IN(A).
	 */
	अगर (mc->mca_sभ_शेषe == MCAST_EXCLUDE)
		mc->mca_crcount = mc->idev->mc_qrv;

	mld_अगरc_event(mc->idev);
पूर्ण

/* called with mc_lock */
अटल व्योम igmp6_group_dropped(काष्ठा अगरmcaddr6 *mc)
अणु
	काष्ठा net_device *dev = mc->idev->dev;
	अक्षर buf[MAX_ADDR_LEN];

	अगर (IPV6_ADDR_MC_SCOPE(&mc->mca_addr) <
	    IPV6_ADDR_SCOPE_LINKLOCAL)
		वापस;

	अगर (mc->mca_flags&MAF_LOADED) अणु
		mc->mca_flags &= ~MAF_LOADED;
		अगर (ndisc_mc_map(&mc->mca_addr, buf, dev, 0) == 0)
			dev_mc_del(dev, buf);
	पूर्ण

	अगर (mc->mca_flags & MAF_NOREPORT)
		वापस;

	अगर (!mc->idev->dead)
		igmp6_leave_group(mc);

	अगर (cancel_delayed_work(&mc->mca_work))
		refcount_dec(&mc->mca_refcnt);
पूर्ण

/*
 * deleted अगरmcaddr6 manipulation
 * called with mc_lock
 */
अटल व्योम mld_add_delrec(काष्ठा inet6_dev *idev, काष्ठा अगरmcaddr6 *im)
अणु
	काष्ठा अगरmcaddr6 *pmc;

	/* this is an "ifmcaddr6" क्रम convenience; only the fields below
	 * are actually used. In particular, the refcnt and users are not
	 * used क्रम management of the delete list. Using the same काष्ठाure
	 * क्रम deleted items allows change reports to use common code with
	 * non-deleted or query-response MCA's.
	 */
	pmc = kzalloc(माप(*pmc), GFP_KERNEL);
	अगर (!pmc)
		वापस;

	pmc->idev = im->idev;
	in6_dev_hold(idev);
	pmc->mca_addr = im->mca_addr;
	pmc->mca_crcount = idev->mc_qrv;
	pmc->mca_sभ_शेषe = im->mca_sभ_शेषe;
	अगर (pmc->mca_sभ_शेषe == MCAST_INCLUDE) अणु
		काष्ठा ip6_sf_list *psf;

		rcu_assign_poपूर्णांकer(pmc->mca_tomb,
				   mc_dereference(im->mca_tomb, idev));
		rcu_assign_poपूर्णांकer(pmc->mca_sources,
				   mc_dereference(im->mca_sources, idev));
		RCU_INIT_POINTER(im->mca_tomb, शून्य);
		RCU_INIT_POINTER(im->mca_sources, शून्य);

		क्रम_each_psf_mघड़ी(pmc, psf)
			psf->sf_crcount = pmc->mca_crcount;
	पूर्ण

	rcu_assign_poपूर्णांकer(pmc->next, idev->mc_tomb);
	rcu_assign_poपूर्णांकer(idev->mc_tomb, pmc);
पूर्ण

/* called with mc_lock */
अटल व्योम mld_del_delrec(काष्ठा inet6_dev *idev, काष्ठा अगरmcaddr6 *im)
अणु
	काष्ठा ip6_sf_list *psf, *sources, *tomb;
	काष्ठा in6_addr *pmca = &im->mca_addr;
	काष्ठा अगरmcaddr6 *pmc, *pmc_prev;

	pmc_prev = शून्य;
	क्रम_each_mc_tomb(idev, pmc) अणु
		अगर (ipv6_addr_equal(&pmc->mca_addr, pmca))
			अवरोध;
		pmc_prev = pmc;
	पूर्ण
	अगर (pmc) अणु
		अगर (pmc_prev)
			rcu_assign_poपूर्णांकer(pmc_prev->next, pmc->next);
		अन्यथा
			rcu_assign_poपूर्णांकer(idev->mc_tomb, pmc->next);
	पूर्ण

	अगर (pmc) अणु
		im->idev = pmc->idev;
		अगर (im->mca_sभ_शेषe == MCAST_INCLUDE) अणु
			tomb = rcu_replace_poपूर्णांकer(im->mca_tomb,
						   mc_dereference(pmc->mca_tomb, pmc->idev),
						   lockdep_is_held(&im->idev->mc_lock));
			rcu_assign_poपूर्णांकer(pmc->mca_tomb, tomb);

			sources = rcu_replace_poपूर्णांकer(im->mca_sources,
						      mc_dereference(pmc->mca_sources, pmc->idev),
						      lockdep_is_held(&im->idev->mc_lock));
			rcu_assign_poपूर्णांकer(pmc->mca_sources, sources);
			क्रम_each_psf_mघड़ी(im, psf)
				psf->sf_crcount = idev->mc_qrv;
		पूर्ण अन्यथा अणु
			im->mca_crcount = idev->mc_qrv;
		पूर्ण
		in6_dev_put(pmc->idev);
		ip6_mc_clear_src(pmc);
		kमुक्त_rcu(pmc, rcu);
	पूर्ण
पूर्ण

/* called with mc_lock */
अटल व्योम mld_clear_delrec(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरmcaddr6 *pmc, *nextpmc;

	pmc = mc_dereference(idev->mc_tomb, idev);
	RCU_INIT_POINTER(idev->mc_tomb, शून्य);

	क्रम (; pmc; pmc = nextpmc) अणु
		nextpmc = mc_dereference(pmc->next, idev);
		ip6_mc_clear_src(pmc);
		in6_dev_put(pmc->idev);
		kमुक्त_rcu(pmc, rcu);
	पूर्ण

	/* clear dead sources, too */
	क्रम_each_mc_mघड़ी(idev, pmc) अणु
		काष्ठा ip6_sf_list *psf, *psf_next;

		psf = mc_dereference(pmc->mca_tomb, idev);
		RCU_INIT_POINTER(pmc->mca_tomb, शून्य);
		क्रम (; psf; psf = psf_next) अणु
			psf_next = mc_dereference(psf->sf_next, idev);
			kमुक्त_rcu(psf, rcu);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mld_clear_query(काष्ठा inet6_dev *idev)
अणु
	काष्ठा sk_buff *skb;

	spin_lock_bh(&idev->mc_query_lock);
	जबतक ((skb = __skb_dequeue(&idev->mc_query_queue)))
		kमुक्त_skb(skb);
	spin_unlock_bh(&idev->mc_query_lock);
पूर्ण

अटल व्योम mld_clear_report(काष्ठा inet6_dev *idev)
अणु
	काष्ठा sk_buff *skb;

	spin_lock_bh(&idev->mc_report_lock);
	जबतक ((skb = __skb_dequeue(&idev->mc_report_queue)))
		kमुक्त_skb(skb);
	spin_unlock_bh(&idev->mc_report_lock);
पूर्ण

अटल व्योम mca_get(काष्ठा अगरmcaddr6 *mc)
अणु
	refcount_inc(&mc->mca_refcnt);
पूर्ण

अटल व्योम ma_put(काष्ठा अगरmcaddr6 *mc)
अणु
	अगर (refcount_dec_and_test(&mc->mca_refcnt)) अणु
		in6_dev_put(mc->idev);
		kमुक्त_rcu(mc, rcu);
	पूर्ण
पूर्ण

/* called with mc_lock */
अटल काष्ठा अगरmcaddr6 *mca_alloc(काष्ठा inet6_dev *idev,
				   स्थिर काष्ठा in6_addr *addr,
				   अचिन्हित पूर्णांक mode)
अणु
	काष्ठा अगरmcaddr6 *mc;

	mc = kzalloc(माप(*mc), GFP_KERNEL);
	अगर (!mc)
		वापस शून्य;

	INIT_DELAYED_WORK(&mc->mca_work, mld_mca_work);

	mc->mca_addr = *addr;
	mc->idev = idev; /* reference taken by caller */
	mc->mca_users = 1;
	/* mca_stamp should be updated upon changes */
	mc->mca_cstamp = mc->mca_tstamp = jअगरfies;
	refcount_set(&mc->mca_refcnt, 1);

	mc->mca_sभ_शेषe = mode;
	mc->mca_sfcount[mode] = 1;

	अगर (ipv6_addr_is_ll_all_nodes(&mc->mca_addr) ||
	    IPV6_ADDR_MC_SCOPE(&mc->mca_addr) < IPV6_ADDR_SCOPE_LINKLOCAL)
		mc->mca_flags |= MAF_NOREPORT;

	वापस mc;
पूर्ण

/*
 *	device multicast group inc (add अगर not found)
 */
अटल पूर्णांक __ipv6_dev_mc_inc(काष्ठा net_device *dev,
			     स्थिर काष्ठा in6_addr *addr, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा अगरmcaddr6 *mc;
	काष्ठा inet6_dev *idev;

	ASSERT_RTNL();

	/* we need to take a reference on idev */
	idev = in6_dev_get(dev);

	अगर (!idev)
		वापस -EINVAL;

	अगर (idev->dead) अणु
		in6_dev_put(idev);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&idev->mc_lock);
	क्रम_each_mc_mघड़ी(idev, mc) अणु
		अगर (ipv6_addr_equal(&mc->mca_addr, addr)) अणु
			mc->mca_users++;
			ip6_mc_add_src(idev, &mc->mca_addr, mode, 0, शून्य, 0);
			mutex_unlock(&idev->mc_lock);
			in6_dev_put(idev);
			वापस 0;
		पूर्ण
	पूर्ण

	mc = mca_alloc(idev, addr, mode);
	अगर (!mc) अणु
		mutex_unlock(&idev->mc_lock);
		in6_dev_put(idev);
		वापस -ENOMEM;
	पूर्ण

	rcu_assign_poपूर्णांकer(mc->next, idev->mc_list);
	rcu_assign_poपूर्णांकer(idev->mc_list, mc);

	mca_get(mc);

	mld_del_delrec(idev, mc);
	igmp6_group_added(mc);
	mutex_unlock(&idev->mc_lock);
	ma_put(mc);
	वापस 0;
पूर्ण

पूर्णांक ipv6_dev_mc_inc(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr)
अणु
	वापस __ipv6_dev_mc_inc(dev, addr, MCAST_EXCLUDE);
पूर्ण
EXPORT_SYMBOL(ipv6_dev_mc_inc);

/*
 * device multicast group del
 */
पूर्णांक __ipv6_dev_mc_dec(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा अगरmcaddr6 *ma, __rcu **map;

	ASSERT_RTNL();

	mutex_lock(&idev->mc_lock);
	क्रम (map = &idev->mc_list;
	     (ma = mc_dereference(*map, idev));
	     map = &ma->next) अणु
		अगर (ipv6_addr_equal(&ma->mca_addr, addr)) अणु
			अगर (--ma->mca_users == 0) अणु
				*map = ma->next;

				igmp6_group_dropped(ma);
				ip6_mc_clear_src(ma);
				mutex_unlock(&idev->mc_lock);

				ma_put(ma);
				वापस 0;
			पूर्ण
			mutex_unlock(&idev->mc_lock);
			वापस 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&idev->mc_lock);
	वापस -ENOENT;
पूर्ण

पूर्णांक ipv6_dev_mc_dec(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *addr)
अणु
	काष्ठा inet6_dev *idev;
	पूर्णांक err;

	ASSERT_RTNL();

	idev = __in6_dev_get(dev);
	अगर (!idev)
		err = -ENODEV;
	अन्यथा
		err = __ipv6_dev_mc_dec(idev, addr);

	वापस err;
पूर्ण
EXPORT_SYMBOL(ipv6_dev_mc_dec);

/*
 *	check अगर the पूर्णांकerface/address pair is valid
 */
bool ipv6_chk_mcast_addr(काष्ठा net_device *dev, स्थिर काष्ठा in6_addr *group,
			 स्थिर काष्ठा in6_addr *src_addr)
अणु
	काष्ठा inet6_dev *idev;
	काष्ठा अगरmcaddr6 *mc;
	bool rv = false;

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(dev);
	अगर (idev) अणु
		क्रम_each_mc_rcu(idev, mc) अणु
			अगर (ipv6_addr_equal(&mc->mca_addr, group))
				अवरोध;
		पूर्ण
		अगर (mc) अणु
			अगर (src_addr && !ipv6_addr_any(src_addr)) अणु
				काष्ठा ip6_sf_list *psf;

				क्रम_each_psf_rcu(mc, psf) अणु
					अगर (ipv6_addr_equal(&psf->sf_addr, src_addr))
						अवरोध;
				पूर्ण
				अगर (psf)
					rv = psf->sf_count[MCAST_INCLUDE] ||
						psf->sf_count[MCAST_EXCLUDE] !=
						mc->mca_sfcount[MCAST_EXCLUDE];
				अन्यथा
					rv = mc->mca_sfcount[MCAST_EXCLUDE] != 0;
			पूर्ण अन्यथा
				rv = true; /* करोn't filter unspecअगरied source */
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस rv;
पूर्ण

/* called with mc_lock */
अटल व्योम mld_gq_start_work(काष्ठा inet6_dev *idev)
अणु
	अचिन्हित दीर्घ tv = pअक्रमom_u32() % idev->mc_maxdelay;

	idev->mc_gq_running = 1;
	अगर (!mod_delayed_work(mld_wq, &idev->mc_gq_work, tv + 2))
		in6_dev_hold(idev);
पूर्ण

/* called with mc_lock */
अटल व्योम mld_gq_stop_work(काष्ठा inet6_dev *idev)
अणु
	idev->mc_gq_running = 0;
	अगर (cancel_delayed_work(&idev->mc_gq_work))
		__in6_dev_put(idev);
पूर्ण

/* called with mc_lock */
अटल व्योम mld_अगरc_start_work(काष्ठा inet6_dev *idev, अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ tv = pअक्रमom_u32() % delay;

	अगर (!mod_delayed_work(mld_wq, &idev->mc_अगरc_work, tv + 2))
		in6_dev_hold(idev);
पूर्ण

/* called with mc_lock */
अटल व्योम mld_अगरc_stop_work(काष्ठा inet6_dev *idev)
अणु
	idev->mc_अगरc_count = 0;
	अगर (cancel_delayed_work(&idev->mc_अगरc_work))
		__in6_dev_put(idev);
पूर्ण

/* called with mc_lock */
अटल व्योम mld_dad_start_work(काष्ठा inet6_dev *idev, अचिन्हित दीर्घ delay)
अणु
	अचिन्हित दीर्घ tv = pअक्रमom_u32() % delay;

	अगर (!mod_delayed_work(mld_wq, &idev->mc_dad_work, tv + 2))
		in6_dev_hold(idev);
पूर्ण

अटल व्योम mld_dad_stop_work(काष्ठा inet6_dev *idev)
अणु
	अगर (cancel_delayed_work(&idev->mc_dad_work))
		__in6_dev_put(idev);
पूर्ण

अटल व्योम mld_query_stop_work(काष्ठा inet6_dev *idev)
अणु
	spin_lock_bh(&idev->mc_query_lock);
	अगर (cancel_delayed_work(&idev->mc_query_work))
		__in6_dev_put(idev);
	spin_unlock_bh(&idev->mc_query_lock);
पूर्ण

अटल व्योम mld_report_stop_work(काष्ठा inet6_dev *idev)
अणु
	अगर (cancel_delayed_work_sync(&idev->mc_report_work))
		__in6_dev_put(idev);
पूर्ण

/*
 * IGMP handling (alias multicast ICMPv6 messages)
 * called with mc_lock
 */
अटल व्योम igmp6_group_queried(काष्ठा अगरmcaddr6 *ma, अचिन्हित दीर्घ respसमय)
अणु
	अचिन्हित दीर्घ delay = respसमय;

	/* Do not start work क्रम these addresses */
	अगर (ipv6_addr_is_ll_all_nodes(&ma->mca_addr) ||
	    IPV6_ADDR_MC_SCOPE(&ma->mca_addr) < IPV6_ADDR_SCOPE_LINKLOCAL)
		वापस;

	अगर (cancel_delayed_work(&ma->mca_work)) अणु
		refcount_dec(&ma->mca_refcnt);
		delay = ma->mca_work.समयr.expires - jअगरfies;
	पूर्ण

	अगर (delay >= respसमय)
		delay = pअक्रमom_u32() % respसमय;

	अगर (!mod_delayed_work(mld_wq, &ma->mca_work, delay))
		refcount_inc(&ma->mca_refcnt);
	ma->mca_flags |= MAF_TIMER_RUNNING;
पूर्ण

/* mark EXCLUDE-mode sources
 * called with mc_lock
 */
अटल bool mld_xmarksources(काष्ठा अगरmcaddr6 *pmc, पूर्णांक nsrcs,
			     स्थिर काष्ठा in6_addr *srcs)
अणु
	काष्ठा ip6_sf_list *psf;
	पूर्णांक i, scount;

	scount = 0;
	क्रम_each_psf_mघड़ी(pmc, psf) अणु
		अगर (scount == nsrcs)
			अवरोध;
		क्रम (i = 0; i < nsrcs; i++) अणु
			/* skip inactive filters */
			अगर (psf->sf_count[MCAST_INCLUDE] ||
			    pmc->mca_sfcount[MCAST_EXCLUDE] !=
			    psf->sf_count[MCAST_EXCLUDE])
				अवरोध;
			अगर (ipv6_addr_equal(&srcs[i], &psf->sf_addr)) अणु
				scount++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	pmc->mca_flags &= ~MAF_GSQUERY;
	अगर (scount == nsrcs)	/* all sources excluded */
		वापस false;
	वापस true;
पूर्ण

/* called with mc_lock */
अटल bool mld_marksources(काष्ठा अगरmcaddr6 *pmc, पूर्णांक nsrcs,
			    स्थिर काष्ठा in6_addr *srcs)
अणु
	काष्ठा ip6_sf_list *psf;
	पूर्णांक i, scount;

	अगर (pmc->mca_sभ_शेषe == MCAST_EXCLUDE)
		वापस mld_xmarksources(pmc, nsrcs, srcs);

	/* mark INCLUDE-mode sources */

	scount = 0;
	क्रम_each_psf_mघड़ी(pmc, psf) अणु
		अगर (scount == nsrcs)
			अवरोध;
		क्रम (i = 0; i < nsrcs; i++) अणु
			अगर (ipv6_addr_equal(&srcs[i], &psf->sf_addr)) अणु
				psf->sf_gsresp = 1;
				scount++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!scount) अणु
		pmc->mca_flags &= ~MAF_GSQUERY;
		वापस false;
	पूर्ण
	pmc->mca_flags |= MAF_GSQUERY;
	वापस true;
पूर्ण

अटल पूर्णांक mld_क्रमce_mld_version(स्थिर काष्ठा inet6_dev *idev)
अणु
	/* Normally, both are 0 here. If enक्रमcement to a particular is
	 * being used, inभागidual device enक्रमcement will have a lower
	 * precedence over 'all' device (.../conf/all/क्रमce_mld_version).
	 */

	अगर (dev_net(idev->dev)->ipv6.devconf_all->क्रमce_mld_version != 0)
		वापस dev_net(idev->dev)->ipv6.devconf_all->क्रमce_mld_version;
	अन्यथा
		वापस idev->cnf.क्रमce_mld_version;
पूर्ण

अटल bool mld_in_v2_mode_only(स्थिर काष्ठा inet6_dev *idev)
अणु
	वापस mld_क्रमce_mld_version(idev) == 2;
पूर्ण

अटल bool mld_in_v1_mode_only(स्थिर काष्ठा inet6_dev *idev)
अणु
	वापस mld_क्रमce_mld_version(idev) == 1;
पूर्ण

अटल bool mld_in_v1_mode(स्थिर काष्ठा inet6_dev *idev)
अणु
	अगर (mld_in_v2_mode_only(idev))
		वापस false;
	अगर (mld_in_v1_mode_only(idev))
		वापस true;
	अगर (idev->mc_v1_seen && समय_beक्रमe(jअगरfies, idev->mc_v1_seen))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम mld_set_v1_mode(काष्ठा inet6_dev *idev)
अणु
	/* RFC3810, relevant sections:
	 *  - 9.1. Robustness Variable
	 *  - 9.2. Query Interval
	 *  - 9.3. Query Response Interval
	 *  - 9.12. Older Version Querier Present Timeout
	 */
	अचिन्हित दीर्घ चयनback;

	चयनback = (idev->mc_qrv * idev->mc_qi) + idev->mc_qri;

	idev->mc_v1_seen = jअगरfies + चयनback;
पूर्ण

अटल व्योम mld_update_qrv(काष्ठा inet6_dev *idev,
			   स्थिर काष्ठा mld2_query *mlh2)
अणु
	/* RFC3810, relevant sections:
	 *  - 5.1.8. QRV (Querier's Robustness Variable)
	 *  - 9.1. Robustness Variable
	 */

	/* The value of the Robustness Variable MUST NOT be zero,
	 * and SHOULD NOT be one. Catch this here अगर we ever run
	 * पूर्णांकo such a हाल in future.
	 */
	स्थिर पूर्णांक min_qrv = min(MLD_QRV_DEFAULT, sysctl_mld_qrv);
	WARN_ON(idev->mc_qrv == 0);

	अगर (mlh2->mld2q_qrv > 0)
		idev->mc_qrv = mlh2->mld2q_qrv;

	अगर (unlikely(idev->mc_qrv < min_qrv)) अणु
		net_warn_ratelimited("IPv6: MLD: clamping QRV from %u to %u!\n",
				     idev->mc_qrv, min_qrv);
		idev->mc_qrv = min_qrv;
	पूर्ण
पूर्ण

अटल व्योम mld_update_qi(काष्ठा inet6_dev *idev,
			  स्थिर काष्ठा mld2_query *mlh2)
अणु
	/* RFC3810, relevant sections:
	 *  - 5.1.9. QQIC (Querier's Query Interval Code)
	 *  - 9.2. Query Interval
	 *  - 9.12. Older Version Querier Present Timeout
	 *    (the [Query Interval] in the last Query received)
	 */
	अचिन्हित दीर्घ mc_qqi;

	अगर (mlh2->mld2q_qqic < 128) अणु
		mc_qqi = mlh2->mld2q_qqic;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ mc_man, mc_exp;

		mc_exp = MLDV2_QQIC_EXP(mlh2->mld2q_qqic);
		mc_man = MLDV2_QQIC_MAN(mlh2->mld2q_qqic);

		mc_qqi = (mc_man | 0x10) << (mc_exp + 3);
	पूर्ण

	idev->mc_qi = mc_qqi * HZ;
पूर्ण

अटल व्योम mld_update_qri(काष्ठा inet6_dev *idev,
			   स्थिर काष्ठा mld2_query *mlh2)
अणु
	/* RFC3810, relevant sections:
	 *  - 5.1.3. Maximum Response Code
	 *  - 9.3. Query Response Interval
	 */
	idev->mc_qri = msecs_to_jअगरfies(mldv2_mrc(mlh2));
पूर्ण

अटल पूर्णांक mld_process_v1(काष्ठा inet6_dev *idev, काष्ठा mld_msg *mld,
			  अचिन्हित दीर्घ *max_delay, bool v1_query)
अणु
	अचिन्हित दीर्घ mldv1_md;

	/* Ignore v1 queries */
	अगर (mld_in_v2_mode_only(idev))
		वापस -EINVAL;

	mldv1_md = ntohs(mld->mld_maxdelay);

	/* When in MLDv1 fallback and a MLDv2 router start-up being
	 * unaware of current MLDv1 operation, the MRC == MRD mapping
	 * only works when the exponential algorithm is not being
	 * used (as MLDv1 is unaware of such things).
	 *
	 * According to the RFC author, the MLDv2 implementations
	 * he's aware of all use a MRC < 32768 on start up queries.
	 *
	 * Thus, should we *ever* encounter something अन्यथा larger
	 * than that, just assume the maximum possible within our
	 * reach.
	 */
	अगर (!v1_query)
		mldv1_md = min(mldv1_md, MLDV1_MRD_MAX_COMPAT);

	*max_delay = max(msecs_to_jअगरfies(mldv1_md), 1UL);

	/* MLDv1 router present: we need to go पूर्णांकo v1 mode *only*
	 * when an MLDv1 query is received as per section 9.12. of
	 * RFC3810! And we know from RFC2710 section 3.7 that MLDv1
	 * queries MUST be of exactly 24 octets.
	 */
	अगर (v1_query)
		mld_set_v1_mode(idev);

	/* cancel MLDv2 report work */
	mld_gq_stop_work(idev);
	/* cancel the पूर्णांकerface change work */
	mld_अगरc_stop_work(idev);
	/* clear deleted report items */
	mld_clear_delrec(idev);

	वापस 0;
पूर्ण

अटल पूर्णांक mld_process_v2(काष्ठा inet6_dev *idev, काष्ठा mld2_query *mld,
			  अचिन्हित दीर्घ *max_delay)
अणु
	*max_delay = max(msecs_to_jअगरfies(mldv2_mrc(mld)), 1UL);

	mld_update_qrv(idev, mld);
	mld_update_qi(idev, mld);
	mld_update_qri(idev, mld);

	idev->mc_maxdelay = *max_delay;

	वापस 0;
पूर्ण

/* called with rcu_पढ़ो_lock() */
पूर्णांक igmp6_event_query(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(skb->dev);

	अगर (!idev)
		वापस -EINVAL;

	अगर (idev->dead) अणु
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	spin_lock_bh(&idev->mc_query_lock);
	अगर (skb_queue_len(&idev->mc_query_queue) < MLD_MAX_SKBS) अणु
		__skb_queue_tail(&idev->mc_query_queue, skb);
		अगर (!mod_delayed_work(mld_wq, &idev->mc_query_work, 0))
			in6_dev_hold(idev);
	पूर्ण
	spin_unlock_bh(&idev->mc_query_lock);

	वापस 0;
पूर्ण

अटल व्योम __mld_query_work(काष्ठा sk_buff *skb)
अणु
	काष्ठा mld2_query *mlh2 = शून्य;
	स्थिर काष्ठा in6_addr *group;
	अचिन्हित दीर्घ max_delay;
	काष्ठा inet6_dev *idev;
	काष्ठा अगरmcaddr6 *ma;
	काष्ठा mld_msg *mld;
	पूर्णांक group_type;
	पूर्णांक mark = 0;
	पूर्णांक len, err;

	अगर (!pskb_may_pull(skb, माप(काष्ठा in6_addr)))
		जाओ kमुक्त_skb;

	/* compute payload length excluding extension headers */
	len = ntohs(ipv6_hdr(skb)->payload_len) + माप(काष्ठा ipv6hdr);
	len -= skb_network_header_len(skb);

	/* RFC3810 6.2
	 * Upon reception of an MLD message that contains a Query, the node
	 * checks अगर the source address of the message is a valid link-local
	 * address, अगर the Hop Limit is set to 1, and अगर the Router Alert
	 * option is present in the Hop-By-Hop Options header of the IPv6
	 * packet.  If any of these checks fails, the packet is dropped.
	 */
	अगर (!(ipv6_addr_type(&ipv6_hdr(skb)->saddr) & IPV6_ADDR_LINKLOCAL) ||
	    ipv6_hdr(skb)->hop_limit != 1 ||
	    !(IP6CB(skb)->flags & IP6SKB_ROUTERALERT) ||
	    IP6CB(skb)->ra != htons(IPV6_OPT_ROUTERALERT_MLD))
		जाओ kमुक्त_skb;

	idev = in6_dev_get(skb->dev);
	अगर (!idev)
		जाओ kमुक्त_skb;

	mld = (काष्ठा mld_msg *)icmp6_hdr(skb);
	group = &mld->mld_mca;
	group_type = ipv6_addr_type(group);

	अगर (group_type != IPV6_ADDR_ANY &&
	    !(group_type&IPV6_ADDR_MULTICAST))
		जाओ out;

	अगर (len < MLD_V1_QUERY_LEN) अणु
		जाओ out;
	पूर्ण अन्यथा अगर (len == MLD_V1_QUERY_LEN || mld_in_v1_mode(idev)) अणु
		err = mld_process_v1(idev, mld, &max_delay,
				     len == MLD_V1_QUERY_LEN);
		अगर (err < 0)
			जाओ out;
	पूर्ण अन्यथा अगर (len >= MLD_V2_QUERY_LEN_MIN) अणु
		पूर्णांक srcs_offset = माप(काष्ठा mld2_query) -
				  माप(काष्ठा icmp6hdr);

		अगर (!pskb_may_pull(skb, srcs_offset))
			जाओ out;

		mlh2 = (काष्ठा mld2_query *)skb_transport_header(skb);

		err = mld_process_v2(idev, mlh2, &max_delay);
		अगर (err < 0)
			जाओ out;

		अगर (group_type == IPV6_ADDR_ANY) अणु /* general query */
			अगर (mlh2->mld2q_nsrcs)
				जाओ out; /* no sources allowed */

			mld_gq_start_work(idev);
			जाओ out;
		पूर्ण
		/* mark sources to include, अगर group & source-specअगरic */
		अगर (mlh2->mld2q_nsrcs != 0) अणु
			अगर (!pskb_may_pull(skb, srcs_offset +
			    ntohs(mlh2->mld2q_nsrcs) * माप(काष्ठा in6_addr)))
				जाओ out;

			mlh2 = (काष्ठा mld2_query *)skb_transport_header(skb);
			mark = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		जाओ out;
	पूर्ण

	अगर (group_type == IPV6_ADDR_ANY) अणु
		क्रम_each_mc_mघड़ी(idev, ma) अणु
			igmp6_group_queried(ma, max_delay);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम_each_mc_mघड़ी(idev, ma) अणु
			अगर (!ipv6_addr_equal(group, &ma->mca_addr))
				जारी;
			अगर (ma->mca_flags & MAF_TIMER_RUNNING) अणु
				/* gsquery <- gsquery && mark */
				अगर (!mark)
					ma->mca_flags &= ~MAF_GSQUERY;
			पूर्ण अन्यथा अणु
				/* gsquery <- mark */
				अगर (mark)
					ma->mca_flags |= MAF_GSQUERY;
				अन्यथा
					ma->mca_flags &= ~MAF_GSQUERY;
			पूर्ण
			अगर (!(ma->mca_flags & MAF_GSQUERY) ||
			    mld_marksources(ma, ntohs(mlh2->mld2q_nsrcs), mlh2->mld2q_srcs))
				igmp6_group_queried(ma, max_delay);
			अवरोध;
		पूर्ण
	पूर्ण

out:
	in6_dev_put(idev);
kमुक्त_skb:
	consume_skb(skb);
पूर्ण

अटल व्योम mld_query_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा inet6_dev *idev = container_of(to_delayed_work(work),
					      काष्ठा inet6_dev,
					      mc_query_work);
	काष्ठा sk_buff_head q;
	काष्ठा sk_buff *skb;
	bool rework = false;
	पूर्णांक cnt = 0;

	skb_queue_head_init(&q);

	spin_lock_bh(&idev->mc_query_lock);
	जबतक ((skb = __skb_dequeue(&idev->mc_query_queue))) अणु
		__skb_queue_tail(&q, skb);

		अगर (++cnt >= MLD_MAX_QUEUE) अणु
			rework = true;
			schedule_delayed_work(&idev->mc_query_work, 0);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&idev->mc_query_lock);

	mutex_lock(&idev->mc_lock);
	जबतक ((skb = __skb_dequeue(&q)))
		__mld_query_work(skb);
	mutex_unlock(&idev->mc_lock);

	अगर (!rework)
		in6_dev_put(idev);
पूर्ण

/* called with rcu_पढ़ो_lock() */
पूर्णांक igmp6_event_report(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_dev *idev = __in6_dev_get(skb->dev);

	अगर (!idev)
		वापस -EINVAL;

	अगर (idev->dead) अणु
		kमुक्त_skb(skb);
		वापस -ENODEV;
	पूर्ण

	spin_lock_bh(&idev->mc_report_lock);
	अगर (skb_queue_len(&idev->mc_report_queue) < MLD_MAX_SKBS) अणु
		__skb_queue_tail(&idev->mc_report_queue, skb);
		अगर (!mod_delayed_work(mld_wq, &idev->mc_report_work, 0))
			in6_dev_hold(idev);
	पूर्ण
	spin_unlock_bh(&idev->mc_report_lock);

	वापस 0;
पूर्ण

अटल व्योम __mld_report_work(काष्ठा sk_buff *skb)
अणु
	काष्ठा inet6_dev *idev;
	काष्ठा अगरmcaddr6 *ma;
	काष्ठा mld_msg *mld;
	पूर्णांक addr_type;

	/* Our own report looped back. Ignore it. */
	अगर (skb->pkt_type == PACKET_LOOPBACK)
		जाओ kमुक्त_skb;

	/* send our report अगर the MC router may not have heard this report */
	अगर (skb->pkt_type != PACKET_MULTICAST &&
	    skb->pkt_type != PACKET_BROADCAST)
		जाओ kमुक्त_skb;

	अगर (!pskb_may_pull(skb, माप(*mld) - माप(काष्ठा icmp6hdr)))
		जाओ kमुक्त_skb;

	mld = (काष्ठा mld_msg *)icmp6_hdr(skb);

	/* Drop reports with not link local source */
	addr_type = ipv6_addr_type(&ipv6_hdr(skb)->saddr);
	अगर (addr_type != IPV6_ADDR_ANY &&
	    !(addr_type&IPV6_ADDR_LINKLOCAL))
		जाओ kमुक्त_skb;

	idev = in6_dev_get(skb->dev);
	अगर (!idev)
		जाओ kमुक्त_skb;

	/*
	 *	Cancel the work क्रम this group
	 */

	क्रम_each_mc_mघड़ी(idev, ma) अणु
		अगर (ipv6_addr_equal(&ma->mca_addr, &mld->mld_mca)) अणु
			अगर (cancel_delayed_work(&ma->mca_work))
				refcount_dec(&ma->mca_refcnt);
			ma->mca_flags &= ~(MAF_LAST_REPORTER |
					   MAF_TIMER_RUNNING);
			अवरोध;
		पूर्ण
	पूर्ण

	in6_dev_put(idev);
kमुक्त_skb:
	consume_skb(skb);
पूर्ण

अटल व्योम mld_report_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा inet6_dev *idev = container_of(to_delayed_work(work),
					      काष्ठा inet6_dev,
					      mc_report_work);
	काष्ठा sk_buff_head q;
	काष्ठा sk_buff *skb;
	bool rework = false;
	पूर्णांक cnt = 0;

	skb_queue_head_init(&q);
	spin_lock_bh(&idev->mc_report_lock);
	जबतक ((skb = __skb_dequeue(&idev->mc_report_queue))) अणु
		__skb_queue_tail(&q, skb);

		अगर (++cnt >= MLD_MAX_QUEUE) अणु
			rework = true;
			schedule_delayed_work(&idev->mc_report_work, 0);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_bh(&idev->mc_report_lock);

	mutex_lock(&idev->mc_lock);
	जबतक ((skb = __skb_dequeue(&q)))
		__mld_report_work(skb);
	mutex_unlock(&idev->mc_lock);

	अगर (!rework)
		in6_dev_put(idev);
पूर्ण

अटल bool is_in(काष्ठा अगरmcaddr6 *pmc, काष्ठा ip6_sf_list *psf, पूर्णांक type,
		  पूर्णांक gdeleted, पूर्णांक sdeleted)
अणु
	चयन (type) अणु
	हाल MLD2_MODE_IS_INCLUDE:
	हाल MLD2_MODE_IS_EXCLUDE:
		अगर (gdeleted || sdeleted)
			वापस false;
		अगर (!((pmc->mca_flags & MAF_GSQUERY) && !psf->sf_gsresp)) अणु
			अगर (pmc->mca_sभ_शेषe == MCAST_INCLUDE)
				वापस true;
			/* करोn't include अगर this source is excluded
			 * in all filters
			 */
			अगर (psf->sf_count[MCAST_INCLUDE])
				वापस type == MLD2_MODE_IS_INCLUDE;
			वापस pmc->mca_sfcount[MCAST_EXCLUDE] ==
				psf->sf_count[MCAST_EXCLUDE];
		पूर्ण
		वापस false;
	हाल MLD2_CHANGE_TO_INCLUDE:
		अगर (gdeleted || sdeleted)
			वापस false;
		वापस psf->sf_count[MCAST_INCLUDE] != 0;
	हाल MLD2_CHANGE_TO_EXCLUDE:
		अगर (gdeleted || sdeleted)
			वापस false;
		अगर (pmc->mca_sfcount[MCAST_EXCLUDE] == 0 ||
		    psf->sf_count[MCAST_INCLUDE])
			वापस false;
		वापस pmc->mca_sfcount[MCAST_EXCLUDE] ==
			psf->sf_count[MCAST_EXCLUDE];
	हाल MLD2_ALLOW_NEW_SOURCES:
		अगर (gdeleted || !psf->sf_crcount)
			वापस false;
		वापस (pmc->mca_sभ_शेषe == MCAST_INCLUDE) ^ sdeleted;
	हाल MLD2_BLOCK_OLD_SOURCES:
		अगर (pmc->mca_sभ_शेषe == MCAST_INCLUDE)
			वापस gdeleted || (psf->sf_crcount && sdeleted);
		वापस psf->sf_crcount && !gdeleted && !sdeleted;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक
mld_scount(काष्ठा अगरmcaddr6 *pmc, पूर्णांक type, पूर्णांक gdeleted, पूर्णांक sdeleted)
अणु
	काष्ठा ip6_sf_list *psf;
	पूर्णांक scount = 0;

	क्रम_each_psf_mघड़ी(pmc, psf) अणु
		अगर (!is_in(pmc, psf, type, gdeleted, sdeleted))
			जारी;
		scount++;
	पूर्ण
	वापस scount;
पूर्ण

अटल व्योम ip6_mc_hdr(काष्ठा sock *sk, काष्ठा sk_buff *skb,
		       काष्ठा net_device *dev,
		       स्थिर काष्ठा in6_addr *saddr,
		       स्थिर काष्ठा in6_addr *daddr,
		       पूर्णांक proto, पूर्णांक len)
अणु
	काष्ठा ipv6hdr *hdr;

	skb->protocol = htons(ETH_P_IPV6);
	skb->dev = dev;

	skb_reset_network_header(skb);
	skb_put(skb, माप(काष्ठा ipv6hdr));
	hdr = ipv6_hdr(skb);

	ip6_flow_hdr(hdr, 0, 0);

	hdr->payload_len = htons(len);
	hdr->nexthdr = proto;
	hdr->hop_limit = inet6_sk(sk)->hop_limit;

	hdr->saddr = *saddr;
	hdr->daddr = *daddr;
पूर्ण

अटल काष्ठा sk_buff *mld_newpack(काष्ठा inet6_dev *idev, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा net_device *dev = idev->dev;
	काष्ठा net *net = dev_net(dev);
	काष्ठा sock *sk = net->ipv6.igmp_sk;
	काष्ठा sk_buff *skb;
	काष्ठा mld2_report *pmr;
	काष्ठा in6_addr addr_buf;
	स्थिर काष्ठा in6_addr *saddr;
	पूर्णांक hlen = LL_RESERVED_SPACE(dev);
	पूर्णांक tlen = dev->needed_tailroom;
	अचिन्हित पूर्णांक size = mtu + hlen + tlen;
	पूर्णांक err;
	u8 ra[8] = अणु IPPROTO_ICMPV6, 0,
		     IPV6_TLV_ROUTERALERT, 2, 0, 0,
		     IPV6_TLV_PADN, 0 पूर्ण;

	/* we assume size > माप(ra) here */
	skb = sock_alloc_send_skb(sk, size, 1, &err);
	अगर (!skb)
		वापस शून्य;

	skb->priority = TC_PRIO_CONTROL;
	skb_reserve(skb, hlen);
	skb_tailroom_reserve(skb, mtu, tlen);

	अगर (__ipv6_get_lladdr(idev, &addr_buf, IFA_F_TENTATIVE)) अणु
		/* <draft-ietf-magma-mld-source-05.txt>:
		 * use unspecअगरied address as the source address
		 * when a valid link-local address is not available.
		 */
		saddr = &in6addr_any;
	पूर्ण अन्यथा
		saddr = &addr_buf;

	ip6_mc_hdr(sk, skb, dev, saddr, &mld2_all_mcr, NEXTHDR_HOP, 0);

	skb_put_data(skb, ra, माप(ra));

	skb_set_transport_header(skb, skb_tail_poपूर्णांकer(skb) - skb->data);
	skb_put(skb, माप(*pmr));
	pmr = (काष्ठा mld2_report *)skb_transport_header(skb);
	pmr->mld2r_type = ICMPV6_MLD2_REPORT;
	pmr->mld2r_resv1 = 0;
	pmr->mld2r_cksum = 0;
	pmr->mld2r_resv2 = 0;
	pmr->mld2r_ngrec = 0;
	वापस skb;
पूर्ण

अटल व्योम mld_sendpack(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *pip6 = ipv6_hdr(skb);
	काष्ठा mld2_report *pmr =
			      (काष्ठा mld2_report *)skb_transport_header(skb);
	पूर्णांक payload_len, mldlen;
	काष्ठा inet6_dev *idev;
	काष्ठा net *net = dev_net(skb->dev);
	पूर्णांक err;
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(skb->dev);
	IP6_UPD_PO_STATS(net, idev, IPSTATS_MIB_OUT, skb->len);

	payload_len = (skb_tail_poपूर्णांकer(skb) - skb_network_header(skb)) -
		माप(*pip6);
	mldlen = skb_tail_poपूर्णांकer(skb) - skb_transport_header(skb);
	pip6->payload_len = htons(payload_len);

	pmr->mld2r_cksum = csum_ipv6_magic(&pip6->saddr, &pip6->daddr, mldlen,
					   IPPROTO_ICMPV6,
					   csum_partial(skb_transport_header(skb),
							mldlen, 0));

	icmpv6_flow_init(net->ipv6.igmp_sk, &fl6, ICMPV6_MLD2_REPORT,
			 &ipv6_hdr(skb)->saddr, &ipv6_hdr(skb)->daddr,
			 skb->dev->अगरindex);
	dst = icmp6_dst_alloc(skb->dev, &fl6);

	err = 0;
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		dst = शून्य;
	पूर्ण
	skb_dst_set(skb, dst);
	अगर (err)
		जाओ err_out;

	err = NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT,
		      net, net->ipv6.igmp_sk, skb, शून्य, skb->dev,
		      dst_output);
out:
	अगर (!err) अणु
		ICMP6MSGOUT_INC_STATS(net, idev, ICMPV6_MLD2_REPORT);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	पूर्ण अन्यथा अणु
		IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTDISCARDS);
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस;

err_out:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

अटल पूर्णांक grec_size(काष्ठा अगरmcaddr6 *pmc, पूर्णांक type, पूर्णांक gdel, पूर्णांक sdel)
अणु
	वापस माप(काष्ठा mld2_grec) + 16 * mld_scount(pmc,type,gdel,sdel);
पूर्ण

अटल काष्ठा sk_buff *add_grhead(काष्ठा sk_buff *skb, काष्ठा अगरmcaddr6 *pmc,
	पूर्णांक type, काष्ठा mld2_grec **ppgr, अचिन्हित पूर्णांक mtu)
अणु
	काष्ठा mld2_report *pmr;
	काष्ठा mld2_grec *pgr;

	अगर (!skb) अणु
		skb = mld_newpack(pmc->idev, mtu);
		अगर (!skb)
			वापस शून्य;
	पूर्ण
	pgr = skb_put(skb, माप(काष्ठा mld2_grec));
	pgr->grec_type = type;
	pgr->grec_auxwords = 0;
	pgr->grec_nsrcs = 0;
	pgr->grec_mca = pmc->mca_addr;	/* काष्ठाure copy */
	pmr = (काष्ठा mld2_report *)skb_transport_header(skb);
	pmr->mld2r_ngrec = htons(ntohs(pmr->mld2r_ngrec)+1);
	*ppgr = pgr;
	वापस skb;
पूर्ण

#घोषणा AVAILABLE(skb)	((skb) ? skb_availroom(skb) : 0)

/* called with mc_lock */
अटल काष्ठा sk_buff *add_grec(काष्ठा sk_buff *skb, काष्ठा अगरmcaddr6 *pmc,
				पूर्णांक type, पूर्णांक gdeleted, पूर्णांक sdeleted,
				पूर्णांक crsend)
अणु
	काष्ठा ip6_sf_list *psf, *psf_prev, *psf_next;
	पूर्णांक scount, stotal, first, isquery, truncate;
	काष्ठा ip6_sf_list __rcu **psf_list;
	काष्ठा inet6_dev *idev = pmc->idev;
	काष्ठा net_device *dev = idev->dev;
	काष्ठा mld2_grec *pgr = शून्य;
	काष्ठा mld2_report *pmr;
	अचिन्हित पूर्णांक mtu;

	अगर (pmc->mca_flags & MAF_NOREPORT)
		वापस skb;

	mtu = READ_ONCE(dev->mtu);
	अगर (mtu < IPV6_MIN_MTU)
		वापस skb;

	isquery = type == MLD2_MODE_IS_INCLUDE ||
		  type == MLD2_MODE_IS_EXCLUDE;
	truncate = type == MLD2_MODE_IS_EXCLUDE ||
		    type == MLD2_CHANGE_TO_EXCLUDE;

	stotal = scount = 0;

	psf_list = sdeleted ? &pmc->mca_tomb : &pmc->mca_sources;

	अगर (!rcu_access_poपूर्णांकer(*psf_list))
		जाओ empty_source;

	pmr = skb ? (काष्ठा mld2_report *)skb_transport_header(skb) : शून्य;

	/* EX and TO_EX get a fresh packet, अगर needed */
	अगर (truncate) अणु
		अगर (pmr && pmr->mld2r_ngrec &&
		    AVAILABLE(skb) < grec_size(pmc, type, gdeleted, sdeleted)) अणु
			अगर (skb)
				mld_sendpack(skb);
			skb = mld_newpack(idev, mtu);
		पूर्ण
	पूर्ण
	first = 1;
	psf_prev = शून्य;
	क्रम (psf = mc_dereference(*psf_list, idev);
	     psf;
	     psf = psf_next) अणु
		काष्ठा in6_addr *psrc;

		psf_next = mc_dereference(psf->sf_next, idev);

		अगर (!is_in(pmc, psf, type, gdeleted, sdeleted) && !crsend) अणु
			psf_prev = psf;
			जारी;
		पूर्ण

		/* Based on RFC3810 6.1. Should not send source-list change
		 * records when there is a filter mode change.
		 */
		अगर (((gdeleted && pmc->mca_sभ_शेषe == MCAST_EXCLUDE) ||
		     (!gdeleted && pmc->mca_crcount)) &&
		    (type == MLD2_ALLOW_NEW_SOURCES ||
		     type == MLD2_BLOCK_OLD_SOURCES) && psf->sf_crcount)
			जाओ decrease_sf_crcount;

		/* clear marks on query responses */
		अगर (isquery)
			psf->sf_gsresp = 0;

		अगर (AVAILABLE(skb) < माप(*psrc) +
		    first*माप(काष्ठा mld2_grec)) अणु
			अगर (truncate && !first)
				अवरोध;	 /* truncate these */
			अगर (pgr)
				pgr->grec_nsrcs = htons(scount);
			अगर (skb)
				mld_sendpack(skb);
			skb = mld_newpack(idev, mtu);
			first = 1;
			scount = 0;
		पूर्ण
		अगर (first) अणु
			skb = add_grhead(skb, pmc, type, &pgr, mtu);
			first = 0;
		पूर्ण
		अगर (!skb)
			वापस शून्य;
		psrc = skb_put(skb, माप(*psrc));
		*psrc = psf->sf_addr;
		scount++; stotal++;
		अगर ((type == MLD2_ALLOW_NEW_SOURCES ||
		     type == MLD2_BLOCK_OLD_SOURCES) && psf->sf_crcount) अणु
decrease_sf_crcount:
			psf->sf_crcount--;
			अगर ((sdeleted || gdeleted) && psf->sf_crcount == 0) अणु
				अगर (psf_prev)
					rcu_assign_poपूर्णांकer(psf_prev->sf_next,
							   mc_dereference(psf->sf_next, idev));
				अन्यथा
					rcu_assign_poपूर्णांकer(*psf_list,
							   mc_dereference(psf->sf_next, idev));
				kमुक्त_rcu(psf, rcu);
				जारी;
			पूर्ण
		पूर्ण
		psf_prev = psf;
	पूर्ण

empty_source:
	अगर (!stotal) अणु
		अगर (type == MLD2_ALLOW_NEW_SOURCES ||
		    type == MLD2_BLOCK_OLD_SOURCES)
			वापस skb;
		अगर (pmc->mca_crcount || isquery || crsend) अणु
			/* make sure we have room क्रम group header */
			अगर (skb && AVAILABLE(skb) < माप(काष्ठा mld2_grec)) अणु
				mld_sendpack(skb);
				skb = शून्य; /* add_grhead will get a new one */
			पूर्ण
			skb = add_grhead(skb, pmc, type, &pgr, mtu);
		पूर्ण
	पूर्ण
	अगर (pgr)
		pgr->grec_nsrcs = htons(scount);

	अगर (isquery)
		pmc->mca_flags &= ~MAF_GSQUERY;	/* clear query state */
	वापस skb;
पूर्ण

/* called with mc_lock */
अटल व्योम mld_send_report(काष्ठा inet6_dev *idev, काष्ठा अगरmcaddr6 *pmc)
अणु
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक type;

	अगर (!pmc) अणु
		क्रम_each_mc_mघड़ी(idev, pmc) अणु
			अगर (pmc->mca_flags & MAF_NOREPORT)
				जारी;
			अगर (pmc->mca_sfcount[MCAST_EXCLUDE])
				type = MLD2_MODE_IS_EXCLUDE;
			अन्यथा
				type = MLD2_MODE_IS_INCLUDE;
			skb = add_grec(skb, pmc, type, 0, 0, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pmc->mca_sfcount[MCAST_EXCLUDE])
			type = MLD2_MODE_IS_EXCLUDE;
		अन्यथा
			type = MLD2_MODE_IS_INCLUDE;
		skb = add_grec(skb, pmc, type, 0, 0, 0);
	पूर्ण
	अगर (skb)
		mld_sendpack(skb);
पूर्ण

/*
 * हटाओ zero-count source records from a source filter list
 * called with mc_lock
 */
अटल व्योम mld_clear_zeros(काष्ठा ip6_sf_list __rcu **ppsf, काष्ठा inet6_dev *idev)
अणु
	काष्ठा ip6_sf_list *psf_prev, *psf_next, *psf;

	psf_prev = शून्य;
	क्रम (psf = mc_dereference(*ppsf, idev);
	     psf;
	     psf = psf_next) अणु
		psf_next = mc_dereference(psf->sf_next, idev);
		अगर (psf->sf_crcount == 0) अणु
			अगर (psf_prev)
				rcu_assign_poपूर्णांकer(psf_prev->sf_next,
						   mc_dereference(psf->sf_next, idev));
			अन्यथा
				rcu_assign_poपूर्णांकer(*ppsf,
						   mc_dereference(psf->sf_next, idev));
			kमुक्त_rcu(psf, rcu);
		पूर्ण अन्यथा अणु
			psf_prev = psf;
		पूर्ण
	पूर्ण
पूर्ण

/* called with mc_lock */
अटल व्योम mld_send_cr(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरmcaddr6 *pmc, *pmc_prev, *pmc_next;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक type, dtype;

	/* deleted MCA's */
	pmc_prev = शून्य;
	क्रम (pmc = mc_dereference(idev->mc_tomb, idev);
	     pmc;
	     pmc = pmc_next) अणु
		pmc_next = mc_dereference(pmc->next, idev);
		अगर (pmc->mca_sभ_शेषe == MCAST_INCLUDE) अणु
			type = MLD2_BLOCK_OLD_SOURCES;
			dtype = MLD2_BLOCK_OLD_SOURCES;
			skb = add_grec(skb, pmc, type, 1, 0, 0);
			skb = add_grec(skb, pmc, dtype, 1, 1, 0);
		पूर्ण
		अगर (pmc->mca_crcount) अणु
			अगर (pmc->mca_sभ_शेषe == MCAST_EXCLUDE) अणु
				type = MLD2_CHANGE_TO_INCLUDE;
				skb = add_grec(skb, pmc, type, 1, 0, 0);
			पूर्ण
			pmc->mca_crcount--;
			अगर (pmc->mca_crcount == 0) अणु
				mld_clear_zeros(&pmc->mca_tomb, idev);
				mld_clear_zeros(&pmc->mca_sources, idev);
			पूर्ण
		पूर्ण
		अगर (pmc->mca_crcount == 0 &&
		    !rcu_access_poपूर्णांकer(pmc->mca_tomb) &&
		    !rcu_access_poपूर्णांकer(pmc->mca_sources)) अणु
			अगर (pmc_prev)
				rcu_assign_poपूर्णांकer(pmc_prev->next, pmc_next);
			अन्यथा
				rcu_assign_poपूर्णांकer(idev->mc_tomb, pmc_next);
			in6_dev_put(pmc->idev);
			kमुक्त_rcu(pmc, rcu);
		पूर्ण अन्यथा
			pmc_prev = pmc;
	पूर्ण

	/* change recs */
	क्रम_each_mc_mघड़ी(idev, pmc) अणु
		अगर (pmc->mca_sfcount[MCAST_EXCLUDE]) अणु
			type = MLD2_BLOCK_OLD_SOURCES;
			dtype = MLD2_ALLOW_NEW_SOURCES;
		पूर्ण अन्यथा अणु
			type = MLD2_ALLOW_NEW_SOURCES;
			dtype = MLD2_BLOCK_OLD_SOURCES;
		पूर्ण
		skb = add_grec(skb, pmc, type, 0, 0, 0);
		skb = add_grec(skb, pmc, dtype, 0, 1, 0);	/* deleted sources */

		/* filter mode changes */
		अगर (pmc->mca_crcount) अणु
			अगर (pmc->mca_sभ_शेषe == MCAST_EXCLUDE)
				type = MLD2_CHANGE_TO_EXCLUDE;
			अन्यथा
				type = MLD2_CHANGE_TO_INCLUDE;
			skb = add_grec(skb, pmc, type, 0, 0, 0);
			pmc->mca_crcount--;
		पूर्ण
	पूर्ण
	अगर (!skb)
		वापस;
	(व्योम) mld_sendpack(skb);
पूर्ण

अटल व्योम igmp6_send(काष्ठा in6_addr *addr, काष्ठा net_device *dev, पूर्णांक type)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा sock *sk = net->ipv6.igmp_sk;
	काष्ठा inet6_dev *idev;
	काष्ठा sk_buff *skb;
	काष्ठा mld_msg *hdr;
	स्थिर काष्ठा in6_addr *snd_addr, *saddr;
	काष्ठा in6_addr addr_buf;
	पूर्णांक hlen = LL_RESERVED_SPACE(dev);
	पूर्णांक tlen = dev->needed_tailroom;
	पूर्णांक err, len, payload_len, full_len;
	u8 ra[8] = अणु IPPROTO_ICMPV6, 0,
		     IPV6_TLV_ROUTERALERT, 2, 0, 0,
		     IPV6_TLV_PADN, 0 पूर्ण;
	काष्ठा flowi6 fl6;
	काष्ठा dst_entry *dst;

	अगर (type == ICMPV6_MGM_REDUCTION)
		snd_addr = &in6addr_linklocal_allrouters;
	अन्यथा
		snd_addr = addr;

	len = माप(काष्ठा icmp6hdr) + माप(काष्ठा in6_addr);
	payload_len = len + माप(ra);
	full_len = माप(काष्ठा ipv6hdr) + payload_len;

	rcu_पढ़ो_lock();
	IP6_UPD_PO_STATS(net, __in6_dev_get(dev),
		      IPSTATS_MIB_OUT, full_len);
	rcu_पढ़ो_unlock();

	skb = sock_alloc_send_skb(sk, hlen + tlen + full_len, 1, &err);

	अगर (!skb) अणु
		rcu_पढ़ो_lock();
		IP6_INC_STATS(net, __in6_dev_get(dev),
			      IPSTATS_MIB_OUTDISCARDS);
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	skb->priority = TC_PRIO_CONTROL;
	skb_reserve(skb, hlen);

	अगर (ipv6_get_lladdr(dev, &addr_buf, IFA_F_TENTATIVE)) अणु
		/* <draft-ietf-magma-mld-source-05.txt>:
		 * use unspecअगरied address as the source address
		 * when a valid link-local address is not available.
		 */
		saddr = &in6addr_any;
	पूर्ण अन्यथा
		saddr = &addr_buf;

	ip6_mc_hdr(sk, skb, dev, saddr, snd_addr, NEXTHDR_HOP, payload_len);

	skb_put_data(skb, ra, माप(ra));

	hdr = skb_put_zero(skb, माप(काष्ठा mld_msg));
	hdr->mld_type = type;
	hdr->mld_mca = *addr;

	hdr->mld_cksum = csum_ipv6_magic(saddr, snd_addr, len,
					 IPPROTO_ICMPV6,
					 csum_partial(hdr, len, 0));

	rcu_पढ़ो_lock();
	idev = __in6_dev_get(skb->dev);

	icmpv6_flow_init(sk, &fl6, type,
			 &ipv6_hdr(skb)->saddr, &ipv6_hdr(skb)->daddr,
			 skb->dev->अगरindex);
	dst = icmp6_dst_alloc(skb->dev, &fl6);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		जाओ err_out;
	पूर्ण

	skb_dst_set(skb, dst);
	err = NF_HOOK(NFPROTO_IPV6, NF_INET_LOCAL_OUT,
		      net, sk, skb, शून्य, skb->dev,
		      dst_output);
out:
	अगर (!err) अणु
		ICMP6MSGOUT_INC_STATS(net, idev, type);
		ICMP6_INC_STATS(net, idev, ICMP6_MIB_OUTMSGS);
	पूर्ण अन्यथा
		IP6_INC_STATS(net, idev, IPSTATS_MIB_OUTDISCARDS);

	rcu_पढ़ो_unlock();
	वापस;

err_out:
	kमुक्त_skb(skb);
	जाओ out;
पूर्ण

/* called with mc_lock */
अटल व्योम mld_send_initial_cr(काष्ठा inet6_dev *idev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा अगरmcaddr6 *pmc;
	पूर्णांक type;

	अगर (mld_in_v1_mode(idev))
		वापस;

	skb = शून्य;
	क्रम_each_mc_mघड़ी(idev, pmc) अणु
		अगर (pmc->mca_sfcount[MCAST_EXCLUDE])
			type = MLD2_CHANGE_TO_EXCLUDE;
		अन्यथा
			type = MLD2_ALLOW_NEW_SOURCES;
		skb = add_grec(skb, pmc, type, 0, 0, 1);
	पूर्ण
	अगर (skb)
		mld_sendpack(skb);
पूर्ण

व्योम ipv6_mc_dad_complete(काष्ठा inet6_dev *idev)
अणु
	mutex_lock(&idev->mc_lock);
	idev->mc_dad_count = idev->mc_qrv;
	अगर (idev->mc_dad_count) अणु
		mld_send_initial_cr(idev);
		idev->mc_dad_count--;
		अगर (idev->mc_dad_count)
			mld_dad_start_work(idev,
					   unsolicited_report_पूर्णांकerval(idev));
	पूर्ण
	mutex_unlock(&idev->mc_lock);
पूर्ण

अटल व्योम mld_dad_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा inet6_dev *idev = container_of(to_delayed_work(work),
					      काष्ठा inet6_dev,
					      mc_dad_work);
	mutex_lock(&idev->mc_lock);
	mld_send_initial_cr(idev);
	अगर (idev->mc_dad_count) अणु
		idev->mc_dad_count--;
		अगर (idev->mc_dad_count)
			mld_dad_start_work(idev,
					   unsolicited_report_पूर्णांकerval(idev));
	पूर्ण
	mutex_unlock(&idev->mc_lock);
	in6_dev_put(idev);
पूर्ण

/* called with mc_lock */
अटल पूर्णांक ip6_mc_del1_src(काष्ठा अगरmcaddr6 *pmc, पूर्णांक sभ_शेषe,
	स्थिर काष्ठा in6_addr *psfsrc)
अणु
	काष्ठा ip6_sf_list *psf, *psf_prev;
	पूर्णांक rv = 0;

	psf_prev = शून्य;
	क्रम_each_psf_mघड़ी(pmc, psf) अणु
		अगर (ipv6_addr_equal(&psf->sf_addr, psfsrc))
			अवरोध;
		psf_prev = psf;
	पूर्ण
	अगर (!psf || psf->sf_count[sभ_शेषe] == 0) अणु
		/* source filter not found, or count wrong =>  bug */
		वापस -ESRCH;
	पूर्ण
	psf->sf_count[sभ_शेषe]--;
	अगर (!psf->sf_count[MCAST_INCLUDE] && !psf->sf_count[MCAST_EXCLUDE]) अणु
		काष्ठा inet6_dev *idev = pmc->idev;

		/* no more filters क्रम this source */
		अगर (psf_prev)
			rcu_assign_poपूर्णांकer(psf_prev->sf_next,
					   mc_dereference(psf->sf_next, idev));
		अन्यथा
			rcu_assign_poपूर्णांकer(pmc->mca_sources,
					   mc_dereference(psf->sf_next, idev));

		अगर (psf->sf_oldin && !(pmc->mca_flags & MAF_NOREPORT) &&
		    !mld_in_v1_mode(idev)) अणु
			psf->sf_crcount = idev->mc_qrv;
			rcu_assign_poपूर्णांकer(psf->sf_next,
					   mc_dereference(pmc->mca_tomb, idev));
			rcu_assign_poपूर्णांकer(pmc->mca_tomb, psf);
			rv = 1;
		पूर्ण अन्यथा अणु
			kमुक्त_rcu(psf, rcu);
		पूर्ण
	पूर्ण
	वापस rv;
पूर्ण

/* called with mc_lock */
अटल पूर्णांक ip6_mc_del_src(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *pmca,
			  पूर्णांक sभ_शेषe, पूर्णांक sfcount, स्थिर काष्ठा in6_addr *psfsrc,
			  पूर्णांक delta)
अणु
	काष्ठा अगरmcaddr6 *pmc;
	पूर्णांक	changerec = 0;
	पूर्णांक	i, err;

	अगर (!idev)
		वापस -ENODEV;

	क्रम_each_mc_mघड़ी(idev, pmc) अणु
		अगर (ipv6_addr_equal(pmca, &pmc->mca_addr))
			अवरोध;
	पूर्ण
	अगर (!pmc)
		वापस -ESRCH;

	sf_markstate(pmc);
	अगर (!delta) अणु
		अगर (!pmc->mca_sfcount[sभ_शेषe])
			वापस -EINVAL;

		pmc->mca_sfcount[sभ_शेषe]--;
	पूर्ण
	err = 0;
	क्रम (i = 0; i < sfcount; i++) अणु
		पूर्णांक rv = ip6_mc_del1_src(pmc, sभ_शेषe, &psfsrc[i]);

		changerec |= rv > 0;
		अगर (!err && rv < 0)
			err = rv;
	पूर्ण
	अगर (pmc->mca_sभ_शेषe == MCAST_EXCLUDE &&
	    pmc->mca_sfcount[MCAST_EXCLUDE] == 0 &&
	    pmc->mca_sfcount[MCAST_INCLUDE]) अणु
		काष्ठा ip6_sf_list *psf;

		/* filter mode change */
		pmc->mca_sभ_शेषe = MCAST_INCLUDE;
		pmc->mca_crcount = idev->mc_qrv;
		idev->mc_अगरc_count = pmc->mca_crcount;
		क्रम_each_psf_mघड़ी(pmc, psf)
			psf->sf_crcount = 0;
		mld_अगरc_event(pmc->idev);
	पूर्ण अन्यथा अगर (sf_setstate(pmc) || changerec) अणु
		mld_अगरc_event(pmc->idev);
	पूर्ण

	वापस err;
पूर्ण

/*
 * Add multicast single-source filter to the पूर्णांकerface list
 * called with mc_lock
 */
अटल पूर्णांक ip6_mc_add1_src(काष्ठा अगरmcaddr6 *pmc, पूर्णांक sभ_शेषe,
	स्थिर काष्ठा in6_addr *psfsrc)
अणु
	काष्ठा ip6_sf_list *psf, *psf_prev;

	psf_prev = शून्य;
	क्रम_each_psf_mघड़ी(pmc, psf) अणु
		अगर (ipv6_addr_equal(&psf->sf_addr, psfsrc))
			अवरोध;
		psf_prev = psf;
	पूर्ण
	अगर (!psf) अणु
		psf = kzalloc(माप(*psf), GFP_KERNEL);
		अगर (!psf)
			वापस -ENOBUFS;

		psf->sf_addr = *psfsrc;
		अगर (psf_prev) अणु
			rcu_assign_poपूर्णांकer(psf_prev->sf_next, psf);
		पूर्ण अन्यथा अणु
			rcu_assign_poपूर्णांकer(pmc->mca_sources, psf);
		पूर्ण
	पूर्ण
	psf->sf_count[sभ_शेषe]++;
	वापस 0;
पूर्ण

/* called with mc_lock */
अटल व्योम sf_markstate(काष्ठा अगरmcaddr6 *pmc)
अणु
	काष्ठा ip6_sf_list *psf;
	पूर्णांक mca_xcount = pmc->mca_sfcount[MCAST_EXCLUDE];

	क्रम_each_psf_mघड़ी(pmc, psf) अणु
		अगर (pmc->mca_sfcount[MCAST_EXCLUDE]) अणु
			psf->sf_oldin = mca_xcount ==
				psf->sf_count[MCAST_EXCLUDE] &&
				!psf->sf_count[MCAST_INCLUDE];
		पूर्ण अन्यथा अणु
			psf->sf_oldin = psf->sf_count[MCAST_INCLUDE] != 0;
		पूर्ण
	पूर्ण
पूर्ण

/* called with mc_lock */
अटल पूर्णांक sf_setstate(काष्ठा अगरmcaddr6 *pmc)
अणु
	काष्ठा ip6_sf_list *psf, *dpsf;
	पूर्णांक mca_xcount = pmc->mca_sfcount[MCAST_EXCLUDE];
	पूर्णांक qrv = pmc->idev->mc_qrv;
	पूर्णांक new_in, rv;

	rv = 0;
	क्रम_each_psf_mघड़ी(pmc, psf) अणु
		अगर (pmc->mca_sfcount[MCAST_EXCLUDE]) अणु
			new_in = mca_xcount == psf->sf_count[MCAST_EXCLUDE] &&
				!psf->sf_count[MCAST_INCLUDE];
		पूर्ण अन्यथा
			new_in = psf->sf_count[MCAST_INCLUDE] != 0;
		अगर (new_in) अणु
			अगर (!psf->sf_oldin) अणु
				काष्ठा ip6_sf_list *prev = शून्य;

				क्रम_each_psf_tomb(pmc, dpsf) अणु
					अगर (ipv6_addr_equal(&dpsf->sf_addr,
					    &psf->sf_addr))
						अवरोध;
					prev = dpsf;
				पूर्ण
				अगर (dpsf) अणु
					अगर (prev)
						rcu_assign_poपूर्णांकer(prev->sf_next,
								   mc_dereference(dpsf->sf_next,
										  pmc->idev));
					अन्यथा
						rcu_assign_poपूर्णांकer(pmc->mca_tomb,
								   mc_dereference(dpsf->sf_next,
										  pmc->idev));
					kमुक्त_rcu(dpsf, rcu);
				पूर्ण
				psf->sf_crcount = qrv;
				rv++;
			पूर्ण
		पूर्ण अन्यथा अगर (psf->sf_oldin) अणु
			psf->sf_crcount = 0;
			/*
			 * add or update "delete" records अगर an active filter
			 * is now inactive
			 */

			क्रम_each_psf_tomb(pmc, dpsf)
				अगर (ipv6_addr_equal(&dpsf->sf_addr,
				    &psf->sf_addr))
					अवरोध;
			अगर (!dpsf) अणु
				dpsf = kदो_स्मृति(माप(*dpsf), GFP_KERNEL);
				अगर (!dpsf)
					जारी;
				*dpsf = *psf;
				rcu_assign_poपूर्णांकer(dpsf->sf_next,
						   mc_dereference(pmc->mca_tomb, pmc->idev));
				rcu_assign_poपूर्णांकer(pmc->mca_tomb, dpsf);
			पूर्ण
			dpsf->sf_crcount = qrv;
			rv++;
		पूर्ण
	पूर्ण
	वापस rv;
पूर्ण

/*
 * Add multicast source filter list to the पूर्णांकerface list
 * called with mc_lock
 */
अटल पूर्णांक ip6_mc_add_src(काष्ठा inet6_dev *idev, स्थिर काष्ठा in6_addr *pmca,
			  पूर्णांक sभ_शेषe, पूर्णांक sfcount, स्थिर काष्ठा in6_addr *psfsrc,
			  पूर्णांक delta)
अणु
	काष्ठा अगरmcaddr6 *pmc;
	पूर्णांक	isexclude;
	पूर्णांक	i, err;

	अगर (!idev)
		वापस -ENODEV;

	क्रम_each_mc_mघड़ी(idev, pmc) अणु
		अगर (ipv6_addr_equal(pmca, &pmc->mca_addr))
			अवरोध;
	पूर्ण
	अगर (!pmc)
		वापस -ESRCH;

	sf_markstate(pmc);
	isexclude = pmc->mca_sभ_शेषe == MCAST_EXCLUDE;
	अगर (!delta)
		pmc->mca_sfcount[sभ_शेषe]++;
	err = 0;
	क्रम (i = 0; i < sfcount; i++) अणु
		err = ip6_mc_add1_src(pmc, sभ_शेषe, &psfsrc[i]);
		अगर (err)
			अवरोध;
	पूर्ण
	अगर (err) अणु
		पूर्णांक j;

		अगर (!delta)
			pmc->mca_sfcount[sभ_शेषe]--;
		क्रम (j = 0; j < i; j++)
			ip6_mc_del1_src(pmc, sभ_शेषe, &psfsrc[j]);
	पूर्ण अन्यथा अगर (isexclude != (pmc->mca_sfcount[MCAST_EXCLUDE] != 0)) अणु
		काष्ठा ip6_sf_list *psf;

		/* filter mode change */
		अगर (pmc->mca_sfcount[MCAST_EXCLUDE])
			pmc->mca_sभ_शेषe = MCAST_EXCLUDE;
		अन्यथा अगर (pmc->mca_sfcount[MCAST_INCLUDE])
			pmc->mca_sभ_शेषe = MCAST_INCLUDE;
		/* अन्यथा no filters; keep old mode क्रम reports */

		pmc->mca_crcount = idev->mc_qrv;
		idev->mc_अगरc_count = pmc->mca_crcount;
		क्रम_each_psf_mघड़ी(pmc, psf)
			psf->sf_crcount = 0;
		mld_अगरc_event(idev);
	पूर्ण अन्यथा अगर (sf_setstate(pmc)) अणु
		mld_अगरc_event(idev);
	पूर्ण
	वापस err;
पूर्ण

/* called with mc_lock */
अटल व्योम ip6_mc_clear_src(काष्ठा अगरmcaddr6 *pmc)
अणु
	काष्ठा ip6_sf_list *psf, *nextpsf;

	क्रम (psf = mc_dereference(pmc->mca_tomb, pmc->idev);
	     psf;
	     psf = nextpsf) अणु
		nextpsf = mc_dereference(psf->sf_next, pmc->idev);
		kमुक्त_rcu(psf, rcu);
	पूर्ण
	RCU_INIT_POINTER(pmc->mca_tomb, शून्य);
	क्रम (psf = mc_dereference(pmc->mca_sources, pmc->idev);
	     psf;
	     psf = nextpsf) अणु
		nextpsf = mc_dereference(psf->sf_next, pmc->idev);
		kमुक्त_rcu(psf, rcu);
	पूर्ण
	RCU_INIT_POINTER(pmc->mca_sources, शून्य);
	pmc->mca_sभ_शेषe = MCAST_EXCLUDE;
	pmc->mca_sfcount[MCAST_INCLUDE] = 0;
	pmc->mca_sfcount[MCAST_EXCLUDE] = 1;
पूर्ण

/* called with mc_lock */
अटल व्योम igmp6_join_group(काष्ठा अगरmcaddr6 *ma)
अणु
	अचिन्हित दीर्घ delay;

	अगर (ma->mca_flags & MAF_NOREPORT)
		वापस;

	igmp6_send(&ma->mca_addr, ma->idev->dev, ICMPV6_MGM_REPORT);

	delay = pअक्रमom_u32() % unsolicited_report_पूर्णांकerval(ma->idev);

	अगर (cancel_delayed_work(&ma->mca_work)) अणु
		refcount_dec(&ma->mca_refcnt);
		delay = ma->mca_work.समयr.expires - jअगरfies;
	पूर्ण

	अगर (!mod_delayed_work(mld_wq, &ma->mca_work, delay))
		refcount_inc(&ma->mca_refcnt);
	ma->mca_flags |= MAF_TIMER_RUNNING | MAF_LAST_REPORTER;
पूर्ण

अटल पूर्णांक ip6_mc_leave_src(काष्ठा sock *sk, काष्ठा ipv6_mc_socklist *iml,
			    काष्ठा inet6_dev *idev)
अणु
	काष्ठा ip6_sf_socklist *psl;
	पूर्णांक err;

	psl = sock_dereference(iml->sflist, sk);

	अगर (idev)
		mutex_lock(&idev->mc_lock);

	अगर (!psl) अणु
		/* any-source empty exclude हाल */
		err = ip6_mc_del_src(idev, &iml->addr, iml->sभ_शेषe, 0, शून्य, 0);
	पूर्ण अन्यथा अणु
		err = ip6_mc_del_src(idev, &iml->addr, iml->sभ_शेषe,
				     psl->sl_count, psl->sl_addr, 0);
		RCU_INIT_POINTER(iml->sflist, शून्य);
		atomic_sub(IP6_SFLSIZE(psl->sl_max), &sk->sk_omem_alloc);
		kमुक्त_rcu(psl, rcu);
	पूर्ण

	अगर (idev)
		mutex_unlock(&idev->mc_lock);

	वापस err;
पूर्ण

/* called with mc_lock */
अटल व्योम igmp6_leave_group(काष्ठा अगरmcaddr6 *ma)
अणु
	अगर (mld_in_v1_mode(ma->idev)) अणु
		अगर (ma->mca_flags & MAF_LAST_REPORTER) अणु
			igmp6_send(&ma->mca_addr, ma->idev->dev,
				ICMPV6_MGM_REDUCTION);
		पूर्ण
	पूर्ण अन्यथा अणु
		mld_add_delrec(ma->idev, ma);
		mld_अगरc_event(ma->idev);
	पूर्ण
पूर्ण

अटल व्योम mld_gq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा inet6_dev *idev = container_of(to_delayed_work(work),
					      काष्ठा inet6_dev,
					      mc_gq_work);

	mutex_lock(&idev->mc_lock);
	mld_send_report(idev, शून्य);
	idev->mc_gq_running = 0;
	mutex_unlock(&idev->mc_lock);

	in6_dev_put(idev);
पूर्ण

अटल व्योम mld_अगरc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा inet6_dev *idev = container_of(to_delayed_work(work),
					      काष्ठा inet6_dev,
					      mc_अगरc_work);

	mutex_lock(&idev->mc_lock);
	mld_send_cr(idev);

	अगर (idev->mc_अगरc_count) अणु
		idev->mc_अगरc_count--;
		अगर (idev->mc_अगरc_count)
			mld_अगरc_start_work(idev,
					   unsolicited_report_पूर्णांकerval(idev));
	पूर्ण
	mutex_unlock(&idev->mc_lock);
	in6_dev_put(idev);
पूर्ण

/* called with mc_lock */
अटल व्योम mld_अगरc_event(काष्ठा inet6_dev *idev)
अणु
	अगर (mld_in_v1_mode(idev))
		वापस;

	idev->mc_अगरc_count = idev->mc_qrv;
	mld_अगरc_start_work(idev, 1);
पूर्ण

अटल व्योम mld_mca_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा अगरmcaddr6 *ma = container_of(to_delayed_work(work),
					    काष्ठा अगरmcaddr6, mca_work);

	mutex_lock(&ma->idev->mc_lock);
	अगर (mld_in_v1_mode(ma->idev))
		igmp6_send(&ma->mca_addr, ma->idev->dev, ICMPV6_MGM_REPORT);
	अन्यथा
		mld_send_report(ma->idev, ma);
	ma->mca_flags |=  MAF_LAST_REPORTER;
	ma->mca_flags &= ~MAF_TIMER_RUNNING;
	mutex_unlock(&ma->idev->mc_lock);

	ma_put(ma);
पूर्ण

/* Device changing type */

व्योम ipv6_mc_unmap(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरmcaddr6 *i;

	/* Install multicast list, except क्रम all-nodes (alपढ़ोy installed) */

	mutex_lock(&idev->mc_lock);
	क्रम_each_mc_mघड़ी(idev, i)
		igmp6_group_dropped(i);
	mutex_unlock(&idev->mc_lock);
पूर्ण

व्योम ipv6_mc_remap(काष्ठा inet6_dev *idev)
अणु
	ipv6_mc_up(idev);
पूर्ण

/* Device going करोwn */
व्योम ipv6_mc_करोwn(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरmcaddr6 *i;

	mutex_lock(&idev->mc_lock);
	/* Withdraw multicast list */
	क्रम_each_mc_mघड़ी(idev, i)
		igmp6_group_dropped(i);
	mutex_unlock(&idev->mc_lock);

	/* Should stop work after group drop. or we will
	 * start work again in mld_अगरc_event()
	 */
	synchronize_net();
	mld_query_stop_work(idev);
	mld_report_stop_work(idev);
	mld_अगरc_stop_work(idev);
	mld_gq_stop_work(idev);
	mld_dad_stop_work(idev);
पूर्ण

अटल व्योम ipv6_mc_reset(काष्ठा inet6_dev *idev)
अणु
	idev->mc_qrv = sysctl_mld_qrv;
	idev->mc_qi = MLD_QI_DEFAULT;
	idev->mc_qri = MLD_QRI_DEFAULT;
	idev->mc_v1_seen = 0;
	idev->mc_maxdelay = unsolicited_report_पूर्णांकerval(idev);
पूर्ण

/* Device going up */

व्योम ipv6_mc_up(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरmcaddr6 *i;

	/* Install multicast list, except क्रम all-nodes (alपढ़ोy installed) */

	ipv6_mc_reset(idev);
	mutex_lock(&idev->mc_lock);
	क्रम_each_mc_mघड़ी(idev, i) अणु
		mld_del_delrec(idev, i);
		igmp6_group_added(i);
	पूर्ण
	mutex_unlock(&idev->mc_lock);
पूर्ण

/* IPv6 device initialization. */

व्योम ipv6_mc_init_dev(काष्ठा inet6_dev *idev)
अणु
	idev->mc_gq_running = 0;
	INIT_DELAYED_WORK(&idev->mc_gq_work, mld_gq_work);
	RCU_INIT_POINTER(idev->mc_tomb, शून्य);
	idev->mc_अगरc_count = 0;
	INIT_DELAYED_WORK(&idev->mc_अगरc_work, mld_अगरc_work);
	INIT_DELAYED_WORK(&idev->mc_dad_work, mld_dad_work);
	INIT_DELAYED_WORK(&idev->mc_query_work, mld_query_work);
	INIT_DELAYED_WORK(&idev->mc_report_work, mld_report_work);
	skb_queue_head_init(&idev->mc_query_queue);
	skb_queue_head_init(&idev->mc_report_queue);
	spin_lock_init(&idev->mc_query_lock);
	spin_lock_init(&idev->mc_report_lock);
	mutex_init(&idev->mc_lock);
	ipv6_mc_reset(idev);
पूर्ण

/*
 *	Device is about to be destroyed: clean up.
 */

व्योम ipv6_mc_destroy_dev(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरmcaddr6 *i;

	/* Deactivate works */
	ipv6_mc_करोwn(idev);
	mutex_lock(&idev->mc_lock);
	mld_clear_delrec(idev);
	mutex_unlock(&idev->mc_lock);
	mld_clear_query(idev);
	mld_clear_report(idev);

	/* Delete all-nodes address. */
	/* We cannot call ipv6_dev_mc_dec() directly, our caller in
	 * addrconf.c has शून्य'd out dev->ip6_ptr so in6_dev_get() will
	 * fail.
	 */
	__ipv6_dev_mc_dec(idev, &in6addr_linklocal_allnodes);

	अगर (idev->cnf.क्रमwarding)
		__ipv6_dev_mc_dec(idev, &in6addr_linklocal_allrouters);

	mutex_lock(&idev->mc_lock);
	जबतक ((i = mc_dereference(idev->mc_list, idev))) अणु
		rcu_assign_poपूर्णांकer(idev->mc_list, mc_dereference(i->next, idev));

		ip6_mc_clear_src(i);
		ma_put(i);
	पूर्ण
	mutex_unlock(&idev->mc_lock);
पूर्ण

अटल व्योम ipv6_mc_rejoin_groups(काष्ठा inet6_dev *idev)
अणु
	काष्ठा अगरmcaddr6 *pmc;

	ASSERT_RTNL();

	mutex_lock(&idev->mc_lock);
	अगर (mld_in_v1_mode(idev)) अणु
		क्रम_each_mc_mघड़ी(idev, pmc)
			igmp6_join_group(pmc);
	पूर्ण अन्यथा अणु
		mld_send_report(idev, शून्य);
	पूर्ण
	mutex_unlock(&idev->mc_lock);
पूर्ण

अटल पूर्णांक ipv6_mc_netdev_event(काष्ठा notअगरier_block *this,
				अचिन्हित दीर्घ event,
				व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा inet6_dev *idev = __in6_dev_get(dev);

	चयन (event) अणु
	हाल NETDEV_RESEND_IGMP:
		अगर (idev)
			ipv6_mc_rejoin_groups(idev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block igmp6_netdev_notअगरier = अणु
	.notअगरier_call = ipv6_mc_netdev_event,
पूर्ण;

#अगर_घोषित CONFIG_PROC_FS
काष्ठा igmp6_mc_iter_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
पूर्ण;

#घोषणा igmp6_mc_seq_निजी(seq)	((काष्ठा igmp6_mc_iter_state *)(seq)->निजी)

अटल अंतरभूत काष्ठा अगरmcaddr6 *igmp6_mc_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा अगरmcaddr6 *im = शून्य;
	काष्ठा igmp6_mc_iter_state *state = igmp6_mc_seq_निजी(seq);
	काष्ठा net *net = seq_file_net(seq);

	state->idev = शून्य;
	क्रम_each_netdev_rcu(net, state->dev) अणु
		काष्ठा inet6_dev *idev;
		idev = __in6_dev_get(state->dev);
		अगर (!idev)
			जारी;

		im = rcu_dereference(idev->mc_list);
		अगर (im) अणु
			state->idev = idev;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस im;
पूर्ण

अटल काष्ठा अगरmcaddr6 *igmp6_mc_get_next(काष्ठा seq_file *seq, काष्ठा अगरmcaddr6 *im)
अणु
	काष्ठा igmp6_mc_iter_state *state = igmp6_mc_seq_निजी(seq);

	im = rcu_dereference(im->next);
	जबतक (!im) अणु
		state->dev = next_net_device_rcu(state->dev);
		अगर (!state->dev) अणु
			state->idev = शून्य;
			अवरोध;
		पूर्ण
		state->idev = __in6_dev_get(state->dev);
		अगर (!state->idev)
			जारी;
		im = rcu_dereference(state->idev->mc_list);
	पूर्ण
	वापस im;
पूर्ण

अटल काष्ठा अगरmcaddr6 *igmp6_mc_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा अगरmcaddr6 *im = igmp6_mc_get_first(seq);
	अगर (im)
		जबतक (pos && (im = igmp6_mc_get_next(seq, im)) != शून्य)
			--pos;
	वापस pos ? शून्य : im;
पूर्ण

अटल व्योम *igmp6_mc_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस igmp6_mc_get_idx(seq, *pos);
पूर्ण

अटल व्योम *igmp6_mc_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा अगरmcaddr6 *im = igmp6_mc_get_next(seq, v);

	++*pos;
	वापस im;
पूर्ण

अटल व्योम igmp6_mc_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	काष्ठा igmp6_mc_iter_state *state = igmp6_mc_seq_निजी(seq);

	अगर (likely(state->idev))
		state->idev = शून्य;
	state->dev = शून्य;
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक igmp6_mc_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा अगरmcaddr6 *im = (काष्ठा अगरmcaddr6 *)v;
	काष्ठा igmp6_mc_iter_state *state = igmp6_mc_seq_निजी(seq);

	seq_म_लिखो(seq,
		   "%-4d %-15s %pi6 %5d %08X %ld\n",
		   state->dev->अगरindex, state->dev->name,
		   &im->mca_addr,
		   im->mca_users, im->mca_flags,
		   (im->mca_flags & MAF_TIMER_RUNNING) ?
		   jअगरfies_to_घड़ी_प्रकार(im->mca_work.समयr.expires - jअगरfies) : 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations igmp6_mc_seq_ops = अणु
	.start	=	igmp6_mc_seq_start,
	.next	=	igmp6_mc_seq_next,
	.stop	=	igmp6_mc_seq_stop,
	.show	=	igmp6_mc_seq_show,
पूर्ण;

काष्ठा igmp6_mcf_iter_state अणु
	काष्ठा seq_net_निजी p;
	काष्ठा net_device *dev;
	काष्ठा inet6_dev *idev;
	काष्ठा अगरmcaddr6 *im;
पूर्ण;

#घोषणा igmp6_mcf_seq_निजी(seq)	((काष्ठा igmp6_mcf_iter_state *)(seq)->निजी)

अटल अंतरभूत काष्ठा ip6_sf_list *igmp6_mcf_get_first(काष्ठा seq_file *seq)
अणु
	काष्ठा ip6_sf_list *psf = शून्य;
	काष्ठा अगरmcaddr6 *im = शून्य;
	काष्ठा igmp6_mcf_iter_state *state = igmp6_mcf_seq_निजी(seq);
	काष्ठा net *net = seq_file_net(seq);

	state->idev = शून्य;
	state->im = शून्य;
	क्रम_each_netdev_rcu(net, state->dev) अणु
		काष्ठा inet6_dev *idev;
		idev = __in6_dev_get(state->dev);
		अगर (unlikely(idev == शून्य))
			जारी;

		im = rcu_dereference(idev->mc_list);
		अगर (likely(im)) अणु
			psf = rcu_dereference(im->mca_sources);
			अगर (likely(psf)) अणु
				state->im = im;
				state->idev = idev;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस psf;
पूर्ण

अटल काष्ठा ip6_sf_list *igmp6_mcf_get_next(काष्ठा seq_file *seq, काष्ठा ip6_sf_list *psf)
अणु
	काष्ठा igmp6_mcf_iter_state *state = igmp6_mcf_seq_निजी(seq);

	psf = rcu_dereference(psf->sf_next);
	जबतक (!psf) अणु
		state->im = rcu_dereference(state->im->next);
		जबतक (!state->im) अणु
			state->dev = next_net_device_rcu(state->dev);
			अगर (!state->dev) अणु
				state->idev = शून्य;
				जाओ out;
			पूर्ण
			state->idev = __in6_dev_get(state->dev);
			अगर (!state->idev)
				जारी;
			state->im = rcu_dereference(state->idev->mc_list);
		पूर्ण
		अगर (!state->im)
			अवरोध;
		psf = rcu_dereference(state->im->mca_sources);
	पूर्ण
out:
	वापस psf;
पूर्ण

अटल काष्ठा ip6_sf_list *igmp6_mcf_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा ip6_sf_list *psf = igmp6_mcf_get_first(seq);
	अगर (psf)
		जबतक (pos && (psf = igmp6_mcf_get_next(seq, psf)) != शून्य)
			--pos;
	वापस pos ? शून्य : psf;
पूर्ण

अटल व्योम *igmp6_mcf_seq_start(काष्ठा seq_file *seq, loff_t *pos)
	__acquires(RCU)
अणु
	rcu_पढ़ो_lock();
	वापस *pos ? igmp6_mcf_get_idx(seq, *pos - 1) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *igmp6_mcf_seq_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा ip6_sf_list *psf;
	अगर (v == SEQ_START_TOKEN)
		psf = igmp6_mcf_get_first(seq);
	अन्यथा
		psf = igmp6_mcf_get_next(seq, v);
	++*pos;
	वापस psf;
पूर्ण

अटल व्योम igmp6_mcf_seq_stop(काष्ठा seq_file *seq, व्योम *v)
	__releases(RCU)
अणु
	काष्ठा igmp6_mcf_iter_state *state = igmp6_mcf_seq_निजी(seq);

	अगर (likely(state->im))
		state->im = शून्य;
	अगर (likely(state->idev))
		state->idev = शून्य;

	state->dev = शून्य;
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक igmp6_mcf_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा ip6_sf_list *psf = (काष्ठा ip6_sf_list *)v;
	काष्ठा igmp6_mcf_iter_state *state = igmp6_mcf_seq_निजी(seq);

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Idx Device                Multicast Address                   Source Address    INC    EXC\n");
	पूर्ण अन्यथा अणु
		seq_म_लिखो(seq,
			   "%3d %6.6s %pi6 %pi6 %6lu %6lu\n",
			   state->dev->अगरindex, state->dev->name,
			   &state->im->mca_addr,
			   &psf->sf_addr,
			   psf->sf_count[MCAST_INCLUDE],
			   psf->sf_count[MCAST_EXCLUDE]);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations igmp6_mcf_seq_ops = अणु
	.start	=	igmp6_mcf_seq_start,
	.next	=	igmp6_mcf_seq_next,
	.stop	=	igmp6_mcf_seq_stop,
	.show	=	igmp6_mcf_seq_show,
पूर्ण;

अटल पूर्णांक __net_init igmp6_proc_init(काष्ठा net *net)
अणु
	पूर्णांक err;

	err = -ENOMEM;
	अगर (!proc_create_net("igmp6", 0444, net->proc_net, &igmp6_mc_seq_ops,
			माप(काष्ठा igmp6_mc_iter_state)))
		जाओ out;
	अगर (!proc_create_net("mcfilter6", 0444, net->proc_net,
			&igmp6_mcf_seq_ops,
			माप(काष्ठा igmp6_mcf_iter_state)))
		जाओ out_proc_net_igmp6;

	err = 0;
out:
	वापस err;

out_proc_net_igmp6:
	हटाओ_proc_entry("igmp6", net->proc_net);
	जाओ out;
पूर्ण

अटल व्योम __net_निकास igmp6_proc_निकास(काष्ठा net *net)
अणु
	हटाओ_proc_entry("mcfilter6", net->proc_net);
	हटाओ_proc_entry("igmp6", net->proc_net);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक igmp6_proc_init(काष्ठा net *net)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम igmp6_proc_निकास(काष्ठा net *net)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __net_init igmp6_net_init(काष्ठा net *net)
अणु
	पूर्णांक err;

	err = inet_ctl_sock_create(&net->ipv6.igmp_sk, PF_INET6,
				   SOCK_RAW, IPPROTO_ICMPV6, net);
	अगर (err < 0) अणु
		pr_err("Failed to initialize the IGMP6 control socket (err %d)\n",
		       err);
		जाओ out;
	पूर्ण

	inet6_sk(net->ipv6.igmp_sk)->hop_limit = 1;
	net->ipv6.igmp_sk->sk_allocation = GFP_KERNEL;

	err = inet_ctl_sock_create(&net->ipv6.mc_स्वतःjoin_sk, PF_INET6,
				   SOCK_RAW, IPPROTO_ICMPV6, net);
	अगर (err < 0) अणु
		pr_err("Failed to initialize the IGMP6 autojoin socket (err %d)\n",
		       err);
		जाओ out_sock_create;
	पूर्ण

	err = igmp6_proc_init(net);
	अगर (err)
		जाओ out_sock_create_स्वतःjoin;

	वापस 0;

out_sock_create_स्वतःjoin:
	inet_ctl_sock_destroy(net->ipv6.mc_स्वतःjoin_sk);
out_sock_create:
	inet_ctl_sock_destroy(net->ipv6.igmp_sk);
out:
	वापस err;
पूर्ण

अटल व्योम __net_निकास igmp6_net_निकास(काष्ठा net *net)
अणु
	inet_ctl_sock_destroy(net->ipv6.igmp_sk);
	inet_ctl_sock_destroy(net->ipv6.mc_स्वतःjoin_sk);
	igmp6_proc_निकास(net);
पूर्ण

अटल काष्ठा pernet_operations igmp6_net_ops = अणु
	.init = igmp6_net_init,
	.निकास = igmp6_net_निकास,
पूर्ण;

पूर्णांक __init igmp6_init(व्योम)
अणु
	पूर्णांक err;

	err = रेजिस्टर_pernet_subsys(&igmp6_net_ops);
	अगर (err)
		वापस err;

	mld_wq = create_workqueue("mld");
	अगर (!mld_wq) अणु
		unरेजिस्टर_pernet_subsys(&igmp6_net_ops);
		वापस -ENOMEM;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक __init igmp6_late_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&igmp6_netdev_notअगरier);
पूर्ण

व्योम igmp6_cleanup(व्योम)
अणु
	unरेजिस्टर_pernet_subsys(&igmp6_net_ops);
	destroy_workqueue(mld_wq);
पूर्ण

व्योम igmp6_late_cleanup(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&igmp6_netdev_notअगरier);
पूर्ण
