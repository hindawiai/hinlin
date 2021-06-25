<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 over IPv4 tunnel device - Simple Internet Transition (SIT)
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Pedro Roque		<roque@di.fc.ul.pt>
 *	Alexey Kuznetsov	<kuznet@ms2.inr.ac.ru>
 *
 *	Changes:
 * Roger Venning <r.venning@telstra.com>:	6to4 support
 * Nate Thompson <nate@thebog.net>:		6to4 support
 * Fred Templin <fred.l.templin@boeing.com>:	isatap support
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/sockios.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/icmp.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/अगर_ether.h>

#समावेश <net/sock.h>
#समावेश <net/snmp.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>
#समावेश <net/transp_v6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ndisc.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip.h>
#समावेश <net/udp.h>
#समावेश <net/icmp.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>
#समावेश <net/dsfield.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

/*
   This version of net/ipv6/sit.c is cloned of net/ipv4/ip_gre.c

   For comments look at net/ipv4/ip_gre.c --ANK
 */

#घोषणा IP6_SIT_HASH_SIZE  16
#घोषणा HASH(addr) (((__क्रमce u32)addr^((__क्रमce u32)addr>>4))&0xF)

अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

अटल पूर्णांक ipip6_tunnel_init(काष्ठा net_device *dev);
अटल व्योम ipip6_tunnel_setup(काष्ठा net_device *dev);
अटल व्योम ipip6_dev_मुक्त(काष्ठा net_device *dev);
अटल bool check_6rd(काष्ठा ip_tunnel *tunnel, स्थिर काष्ठा in6_addr *v6dst,
		      __be32 *v4dst);
अटल काष्ठा rtnl_link_ops sit_link_ops __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक sit_net_id __पढ़ो_mostly;
काष्ठा sit_net अणु
	काष्ठा ip_tunnel __rcu *tunnels_r_l[IP6_SIT_HASH_SIZE];
	काष्ठा ip_tunnel __rcu *tunnels_r[IP6_SIT_HASH_SIZE];
	काष्ठा ip_tunnel __rcu *tunnels_l[IP6_SIT_HASH_SIZE];
	काष्ठा ip_tunnel __rcu *tunnels_wc[1];
	काष्ठा ip_tunnel __rcu **tunnels[4];

	काष्ठा net_device *fb_tunnel_dev;
पूर्ण;

अटल अंतरभूत काष्ठा sit_net *dev_to_sit_net(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	वापस net_generic(t->net, sit_net_id);
पूर्ण

/*
 * Must be invoked with rcu_पढ़ो_lock
 */
अटल काष्ठा ip_tunnel *ipip6_tunnel_lookup(काष्ठा net *net,
					     काष्ठा net_device *dev,
					     __be32 remote, __be32 local,
					     पूर्णांक sअगरindex)
अणु
	अचिन्हित पूर्णांक h0 = HASH(remote);
	अचिन्हित पूर्णांक h1 = HASH(local);
	काष्ठा ip_tunnel *t;
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);
	पूर्णांक अगरindex = dev ? dev->अगरindex : 0;

	क्रम_each_ip_tunnel_rcu(t, sitn->tunnels_r_l[h0 ^ h1]) अणु
		अगर (local == t->parms.iph.saddr &&
		    remote == t->parms.iph.daddr &&
		    (!dev || !t->parms.link || अगरindex == t->parms.link ||
		     sअगरindex == t->parms.link) &&
		    (t->dev->flags & IFF_UP))
			वापस t;
	पूर्ण
	क्रम_each_ip_tunnel_rcu(t, sitn->tunnels_r[h0]) अणु
		अगर (remote == t->parms.iph.daddr &&
		    (!dev || !t->parms.link || अगरindex == t->parms.link ||
		     sअगरindex == t->parms.link) &&
		    (t->dev->flags & IFF_UP))
			वापस t;
	पूर्ण
	क्रम_each_ip_tunnel_rcu(t, sitn->tunnels_l[h1]) अणु
		अगर (local == t->parms.iph.saddr &&
		    (!dev || !t->parms.link || अगरindex == t->parms.link ||
		     sअगरindex == t->parms.link) &&
		    (t->dev->flags & IFF_UP))
			वापस t;
	पूर्ण
	t = rcu_dereference(sitn->tunnels_wc[0]);
	अगर (t && (t->dev->flags & IFF_UP))
		वापस t;
	वापस शून्य;
पूर्ण

अटल काष्ठा ip_tunnel __rcu **__ipip6_bucket(काष्ठा sit_net *sitn,
		काष्ठा ip_tunnel_parm *parms)
अणु
	__be32 remote = parms->iph.daddr;
	__be32 local = parms->iph.saddr;
	अचिन्हित पूर्णांक h = 0;
	पूर्णांक prio = 0;

	अगर (remote) अणु
		prio |= 2;
		h ^= HASH(remote);
	पूर्ण
	अगर (local) अणु
		prio |= 1;
		h ^= HASH(local);
	पूर्ण
	वापस &sitn->tunnels[prio][h];
पूर्ण

अटल अंतरभूत काष्ठा ip_tunnel __rcu **ipip6_bucket(काष्ठा sit_net *sitn,
		काष्ठा ip_tunnel *t)
अणु
	वापस __ipip6_bucket(sitn, &t->parms);
पूर्ण

अटल व्योम ipip6_tunnel_unlink(काष्ठा sit_net *sitn, काष्ठा ip_tunnel *t)
अणु
	काष्ठा ip_tunnel __rcu **tp;
	काष्ठा ip_tunnel *iter;

	क्रम (tp = ipip6_bucket(sitn, t);
	     (iter = rtnl_dereference(*tp)) != शून्य;
	     tp = &iter->next) अणु
		अगर (t == iter) अणु
			rcu_assign_poपूर्णांकer(*tp, t->next);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ipip6_tunnel_link(काष्ठा sit_net *sitn, काष्ठा ip_tunnel *t)
अणु
	काष्ठा ip_tunnel __rcu **tp = ipip6_bucket(sitn, t);

	rcu_assign_poपूर्णांकer(t->next, rtnl_dereference(*tp));
	rcu_assign_poपूर्णांकer(*tp, t);
पूर्ण

अटल व्योम ipip6_tunnel_clone_6rd(काष्ठा net_device *dev, काष्ठा sit_net *sitn)
अणु
#अगर_घोषित CONFIG_IPV6_SIT_6RD
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	अगर (dev == sitn->fb_tunnel_dev || !sitn->fb_tunnel_dev) अणु
		ipv6_addr_set(&t->ip6rd.prefix, htonl(0x20020000), 0, 0, 0);
		t->ip6rd.relay_prefix = 0;
		t->ip6rd.prefixlen = 16;
		t->ip6rd.relay_prefixlen = 0;
	पूर्ण अन्यथा अणु
		काष्ठा ip_tunnel *t0 = netdev_priv(sitn->fb_tunnel_dev);
		स_नकल(&t->ip6rd, &t0->ip6rd, माप(t->ip6rd));
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ipip6_tunnel_create(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);
	पूर्णांक err;

	स_नकल(dev->dev_addr, &t->parms.iph.saddr, 4);
	स_नकल(dev->broadcast, &t->parms.iph.daddr, 4);

	अगर ((__क्रमce u16)t->parms.i_flags & SIT_ISATAP)
		dev->priv_flags |= IFF_ISATAP;

	dev->rtnl_link_ops = &sit_link_ops;

	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ out;

	ipip6_tunnel_clone_6rd(dev, sitn);

	ipip6_tunnel_link(sitn, t);
	वापस 0;

out:
	वापस err;
पूर्ण

अटल काष्ठा ip_tunnel *ipip6_tunnel_locate(काष्ठा net *net,
		काष्ठा ip_tunnel_parm *parms, पूर्णांक create)
अणु
	__be32 remote = parms->iph.daddr;
	__be32 local = parms->iph.saddr;
	काष्ठा ip_tunnel *t, *nt;
	काष्ठा ip_tunnel __rcu **tp;
	काष्ठा net_device *dev;
	अक्षर name[IFNAMSIZ];
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);

	क्रम (tp = __ipip6_bucket(sitn, parms);
	    (t = rtnl_dereference(*tp)) != शून्य;
	     tp = &t->next) अणु
		अगर (local == t->parms.iph.saddr &&
		    remote == t->parms.iph.daddr &&
		    parms->link == t->parms.link) अणु
			अगर (create)
				वापस शून्य;
			अन्यथा
				वापस t;
		पूर्ण
	पूर्ण
	अगर (!create)
		जाओ failed;

	अगर (parms->name[0]) अणु
		अगर (!dev_valid_name(parms->name))
			जाओ failed;
		strlcpy(name, parms->name, IFNAMSIZ);
	पूर्ण अन्यथा अणु
		म_नकल(name, "sit%d");
	पूर्ण
	dev = alloc_netdev(माप(*t), name, NET_NAME_UNKNOWN,
			   ipip6_tunnel_setup);
	अगर (!dev)
		वापस शून्य;

	dev_net_set(dev, net);

	nt = netdev_priv(dev);

	nt->parms = *parms;
	अगर (ipip6_tunnel_create(dev) < 0)
		जाओ failed_मुक्त;

	अगर (!parms->name[0])
		म_नकल(parms->name, dev->name);

	वापस nt;

failed_मुक्त:
	मुक्त_netdev(dev);
failed:
	वापस शून्य;
पूर्ण

#घोषणा क्रम_each_prl_rcu(start)			\
	क्रम (prl = rcu_dereference(start);	\
	     prl;				\
	     prl = rcu_dereference(prl->next))

अटल काष्ठा ip_tunnel_prl_entry *
__ipip6_tunnel_locate_prl(काष्ठा ip_tunnel *t, __be32 addr)
अणु
	काष्ठा ip_tunnel_prl_entry *prl;

	क्रम_each_prl_rcu(t->prl)
		अगर (prl->addr == addr)
			अवरोध;
	वापस prl;

पूर्ण

अटल पूर्णांक ipip6_tunnel_get_prl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा ip_tunnel_prl __user *a = अगरr->अगरr_अगरru.अगरru_data;
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_prl kprl, *kp;
	काष्ठा ip_tunnel_prl_entry *prl;
	अचिन्हित पूर्णांक cmax, c = 0, ca, len;
	पूर्णांक ret = 0;

	अगर (dev == dev_to_sit_net(dev)->fb_tunnel_dev)
		वापस -EINVAL;

	अगर (copy_from_user(&kprl, a, माप(kprl)))
		वापस -EFAULT;
	cmax = kprl.datalen / माप(kprl);
	अगर (cmax > 1 && kprl.addr != htonl(INADDR_ANY))
		cmax = 1;

	/* For simple GET or क्रम root users,
	 * we try harder to allocate.
	 */
	kp = (cmax <= 1 || capable(CAP_NET_ADMIN)) ?
		kसुस्मृति(cmax, माप(*kp), GFP_KERNEL | __GFP_NOWARN) :
		शून्य;

	rcu_पढ़ो_lock();

	ca = min(t->prl_count, cmax);

	अगर (!kp) अणु
		/* We करोn't try hard to allocate much memory क्रम
		 * non-root users.
		 * For root users, retry allocating enough memory क्रम
		 * the answer.
		 */
		kp = kसुस्मृति(ca, माप(*kp), GFP_ATOMIC);
		अगर (!kp) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	c = 0;
	क्रम_each_prl_rcu(t->prl) अणु
		अगर (c >= cmax)
			अवरोध;
		अगर (kprl.addr != htonl(INADDR_ANY) && prl->addr != kprl.addr)
			जारी;
		kp[c].addr = prl->addr;
		kp[c].flags = prl->flags;
		c++;
		अगर (kprl.addr != htonl(INADDR_ANY))
			अवरोध;
	पूर्ण
out:
	rcu_पढ़ो_unlock();

	len = माप(*kp) * c;
	ret = 0;
	अगर ((len && copy_to_user(a + 1, kp, len)) || put_user(len, &a->datalen))
		ret = -EFAULT;

	kमुक्त(kp);

	वापस ret;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_add_prl(काष्ठा ip_tunnel *t, काष्ठा ip_tunnel_prl *a, पूर्णांक chg)
अणु
	काष्ठा ip_tunnel_prl_entry *p;
	पूर्णांक err = 0;

	अगर (a->addr == htonl(INADDR_ANY))
		वापस -EINVAL;

	ASSERT_RTNL();

	क्रम (p = rtnl_dereference(t->prl); p; p = rtnl_dereference(p->next)) अणु
		अगर (p->addr == a->addr) अणु
			अगर (chg) अणु
				p->flags = a->flags;
				जाओ out;
			पूर्ण
			err = -EEXIST;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (chg) अणु
		err = -ENXIO;
		जाओ out;
	पूर्ण

	p = kzalloc(माप(काष्ठा ip_tunnel_prl_entry), GFP_KERNEL);
	अगर (!p) अणु
		err = -ENOBUFS;
		जाओ out;
	पूर्ण

	p->next = t->prl;
	p->addr = a->addr;
	p->flags = a->flags;
	t->prl_count++;
	rcu_assign_poपूर्णांकer(t->prl, p);
out:
	वापस err;
पूर्ण

अटल व्योम prl_list_destroy_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा ip_tunnel_prl_entry *p, *n;

	p = container_of(head, काष्ठा ip_tunnel_prl_entry, rcu_head);
	करो अणु
		n = rcu_dereference_रक्षित(p->next, 1);
		kमुक्त(p);
		p = n;
	पूर्ण जबतक (p);
पूर्ण

अटल पूर्णांक
ipip6_tunnel_del_prl(काष्ठा ip_tunnel *t, काष्ठा ip_tunnel_prl *a)
अणु
	काष्ठा ip_tunnel_prl_entry *x;
	काष्ठा ip_tunnel_prl_entry __rcu **p;
	पूर्णांक err = 0;

	ASSERT_RTNL();

	अगर (a && a->addr != htonl(INADDR_ANY)) अणु
		क्रम (p = &t->prl;
		     (x = rtnl_dereference(*p)) != शून्य;
		     p = &x->next) अणु
			अगर (x->addr == a->addr) अणु
				*p = x->next;
				kमुक्त_rcu(x, rcu_head);
				t->prl_count--;
				जाओ out;
			पूर्ण
		पूर्ण
		err = -ENXIO;
	पूर्ण अन्यथा अणु
		x = rtnl_dereference(t->prl);
		अगर (x) अणु
			t->prl_count = 0;
			call_rcu(&x->rcu_head, prl_list_destroy_rcu);
			t->prl = शून्य;
		पूर्ण
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक ipip6_tunnel_prl_ctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr,
		पूर्णांक cmd)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_prl prl;
	पूर्णांक err;

	अगर (!ns_capable(t->net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (dev == dev_to_sit_net(dev)->fb_tunnel_dev)
		वापस -EINVAL;

	अगर (copy_from_user(&prl, अगरr->अगरr_अगरru.अगरru_data, माप(prl)))
		वापस -EFAULT;

	चयन (cmd) अणु
	हाल SIOCDELPRL:
		err = ipip6_tunnel_del_prl(t, &prl);
		अवरोध;
	हाल SIOCADDPRL:
	हाल SIOCCHGPRL:
		err = ipip6_tunnel_add_prl(t, &prl, cmd == SIOCCHGPRL);
		अवरोध;
	पूर्ण
	dst_cache_reset(&t->dst_cache);
	netdev_state_change(dev);
	वापस err;
पूर्ण

अटल पूर्णांक
isatap_chksrc(काष्ठा sk_buff *skb, स्थिर काष्ठा iphdr *iph, काष्ठा ip_tunnel *t)
अणु
	काष्ठा ip_tunnel_prl_entry *p;
	पूर्णांक ok = 1;

	rcu_पढ़ो_lock();
	p = __ipip6_tunnel_locate_prl(t, iph->saddr);
	अगर (p) अणु
		अगर (p->flags & PRL_DEFAULT)
			skb->ndisc_nodetype = NDISC_NODETYPE_DEFAULT;
		अन्यथा
			skb->ndisc_nodetype = NDISC_NODETYPE_NODEFAULT;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा in6_addr *addr6 = &ipv6_hdr(skb)->saddr;

		अगर (ipv6_addr_is_isatap(addr6) &&
		    (addr6->s6_addr32[3] == iph->saddr) &&
		    ipv6_chk_prefix(addr6, t->dev))
			skb->ndisc_nodetype = NDISC_NODETYPE_HOST;
		अन्यथा
			ok = 0;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ok;
पूर्ण

अटल व्योम ipip6_tunnel_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा sit_net *sitn = net_generic(tunnel->net, sit_net_id);

	अगर (dev == sitn->fb_tunnel_dev) अणु
		RCU_INIT_POINTER(sitn->tunnels_wc[0], शून्य);
	पूर्ण अन्यथा अणु
		ipip6_tunnel_unlink(sitn, tunnel);
		ipip6_tunnel_del_prl(tunnel, शून्य);
	पूर्ण
	dst_cache_reset(&tunnel->dst_cache);
	dev_put(dev);
पूर्ण

अटल पूर्णांक ipip6_err(काष्ठा sk_buff *skb, u32 info)
अणु
	स्थिर काष्ठा iphdr *iph = (स्थिर काष्ठा iphdr *)skb->data;
	स्थिर पूर्णांक type = icmp_hdr(skb)->type;
	स्थिर पूर्णांक code = icmp_hdr(skb)->code;
	अचिन्हित पूर्णांक data_len = 0;
	काष्ठा ip_tunnel *t;
	पूर्णांक sअगरindex;
	पूर्णांक err;

	चयन (type) अणु
	शेष:
	हाल ICMP_PARAMETERPROB:
		वापस 0;

	हाल ICMP_DEST_UNREACH:
		चयन (code) अणु
		हाल ICMP_SR_FAILED:
			/* Impossible event. */
			वापस 0;
		शेष:
			/* All others are translated to HOST_UNREACH.
			   rfc2003 contains "deep thoughts" about NET_UNREACH,
			   I believe they are just ether pollution. --ANK
			 */
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ICMP_TIME_EXCEEDED:
		अगर (code != ICMP_EXC_TTL)
			वापस 0;
		data_len = icmp_hdr(skb)->un.reserved[1] * 4; /* RFC 4884 4.1 */
		अवरोध;
	हाल ICMP_REसूचीECT:
		अवरोध;
	पूर्ण

	err = -ENOENT;

	sअगरindex = netअगर_is_l3_master(skb->dev) ? IPCB(skb)->iअगर : 0;
	t = ipip6_tunnel_lookup(dev_net(skb->dev), skb->dev,
				iph->daddr, iph->saddr, sअगरindex);
	अगर (!t)
		जाओ out;

	अगर (type == ICMP_DEST_UNREACH && code == ICMP_FRAG_NEEDED) अणु
		ipv4_update_pmtu(skb, dev_net(skb->dev), info,
				 t->parms.link, iph->protocol);
		err = 0;
		जाओ out;
	पूर्ण
	अगर (type == ICMP_REसूचीECT) अणु
		ipv4_redirect(skb, dev_net(skb->dev), t->parms.link,
			      iph->protocol);
		err = 0;
		जाओ out;
	पूर्ण

	err = 0;
	अगर (__in6_dev_get(skb->dev) &&
	    !ip6_err_gen_icmpv6_unreach(skb, iph->ihl * 4, type, data_len))
		जाओ out;

	अगर (t->parms.iph.daddr == 0)
		जाओ out;

	अगर (t->parms.iph.ttl == 0 && type == ICMP_TIME_EXCEEDED)
		जाओ out;

	अगर (समय_beक्रमe(jअगरfies, t->err_समय + IPTUNNEL_ERR_TIMEO))
		t->err_count++;
	अन्यथा
		t->err_count = 1;
	t->err_समय = jअगरfies;
out:
	वापस err;
पूर्ण

अटल अंतरभूत bool is_spoofed_6rd(काष्ठा ip_tunnel *tunnel, स्थिर __be32 v4addr,
				  स्थिर काष्ठा in6_addr *v6addr)
अणु
	__be32 v4embed = 0;
	अगर (check_6rd(tunnel, v6addr, &v4embed) && v4addr != v4embed)
		वापस true;
	वापस false;
पूर्ण

/* Checks अगर an address matches an address on the tunnel पूर्णांकerface.
 * Used to detect the NAT of proto 41 packets and let them pass spoofing test.
 * Long story:
 * This function is called after we considered the packet as spoofed
 * in is_spoofed_6rd.
 * We may have a router that is करोing NAT क्रम proto 41 packets
 * क्रम an पूर्णांकernal station. Destination a.a.a.a/PREFIX:bbbb:bbbb
 * will be translated to n.n.n.n/PREFIX:bbbb:bbbb. And is_spoofed_6rd
 * function will वापस true, dropping the packet.
 * But, we can still check अगर is spoofed against the IP
 * addresses associated with the पूर्णांकerface.
 */
अटल bool only_dnatted(स्थिर काष्ठा ip_tunnel *tunnel,
	स्थिर काष्ठा in6_addr *v6dst)
अणु
	पूर्णांक prefix_len;

#अगर_घोषित CONFIG_IPV6_SIT_6RD
	prefix_len = tunnel->ip6rd.prefixlen + 32
		- tunnel->ip6rd.relay_prefixlen;
#अन्यथा
	prefix_len = 48;
#पूर्ण_अगर
	वापस ipv6_chk_custom_prefix(v6dst, prefix_len, tunnel->dev);
पूर्ण

/* Returns true अगर a packet is spoofed */
अटल bool packet_is_spoofed(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा iphdr *iph,
			      काष्ठा ip_tunnel *tunnel)
अणु
	स्थिर काष्ठा ipv6hdr *ipv6h;

	अगर (tunnel->dev->priv_flags & IFF_ISATAP) अणु
		अगर (!isatap_chksrc(skb, iph, tunnel))
			वापस true;

		वापस false;
	पूर्ण

	अगर (tunnel->dev->flags & IFF_POINTOPOINT)
		वापस false;

	ipv6h = ipv6_hdr(skb);

	अगर (unlikely(is_spoofed_6rd(tunnel, iph->saddr, &ipv6h->saddr))) अणु
		net_warn_ratelimited("Src spoofed %pI4/%pI6c -> %pI4/%pI6c\n",
				     &iph->saddr, &ipv6h->saddr,
				     &iph->daddr, &ipv6h->daddr);
		वापस true;
	पूर्ण

	अगर (likely(!is_spoofed_6rd(tunnel, iph->daddr, &ipv6h->daddr)))
		वापस false;

	अगर (only_dnatted(tunnel, &ipv6h->daddr))
		वापस false;

	net_warn_ratelimited("Dst spoofed %pI4/%pI6c -> %pI4/%pI6c\n",
			     &iph->saddr, &ipv6h->saddr,
			     &iph->daddr, &ipv6h->daddr);
	वापस true;
पूर्ण

अटल पूर्णांक ipip6_rcv(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा ip_tunnel *tunnel;
	पूर्णांक sअगरindex;
	पूर्णांक err;

	sअगरindex = netअगर_is_l3_master(skb->dev) ? IPCB(skb)->iअगर : 0;
	tunnel = ipip6_tunnel_lookup(dev_net(skb->dev), skb->dev,
				     iph->saddr, iph->daddr, sअगरindex);
	अगर (tunnel) अणु
		काष्ठा pcpu_sw_netstats *tstats;

		अगर (tunnel->parms.iph.protocol != IPPROTO_IPV6 &&
		    tunnel->parms.iph.protocol != 0)
			जाओ out;

		skb->mac_header = skb->network_header;
		skb_reset_network_header(skb);
		IPCB(skb)->flags = 0;
		skb->dev = tunnel->dev;

		अगर (packet_is_spoofed(skb, iph, tunnel)) अणु
			tunnel->dev->stats.rx_errors++;
			जाओ out;
		पूर्ण

		अगर (iptunnel_pull_header(skb, 0, htons(ETH_P_IPV6),
		    !net_eq(tunnel->net, dev_net(tunnel->dev))))
			जाओ out;

		/* skb can be uncloned in iptunnel_pull_header, so
		 * old iph is no दीर्घer valid
		 */
		iph = (स्थिर काष्ठा iphdr *)skb_mac_header(skb);
		err = IP_ECN_decapsulate(iph, skb);
		अगर (unlikely(err)) अणु
			अगर (log_ecn_error)
				net_info_ratelimited("non-ECT from %pI4 with TOS=%#x\n",
						     &iph->saddr, iph->tos);
			अगर (err > 1) अणु
				++tunnel->dev->stats.rx_frame_errors;
				++tunnel->dev->stats.rx_errors;
				जाओ out;
			पूर्ण
		पूर्ण

		tstats = this_cpu_ptr(tunnel->dev->tstats);
		u64_stats_update_begin(&tstats->syncp);
		tstats->rx_packets++;
		tstats->rx_bytes += skb->len;
		u64_stats_update_end(&tstats->syncp);

		netअगर_rx(skb);

		वापस 0;
	पूर्ण

	/* no tunnel matched,  let upstream know, ipsec may handle it */
	वापस 1;
out:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा tnl_ptk_info ipip_tpi = अणु
	/* no tunnel info required क्रम ipip. */
	.proto = htons(ETH_P_IP),
पूर्ण;

#अगर IS_ENABLED(CONFIG_MPLS)
अटल स्थिर काष्ठा tnl_ptk_info mplsip_tpi = अणु
	/* no tunnel info required क्रम mplsip. */
	.proto = htons(ETH_P_MPLS_UC),
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक sit_tunnel_rcv(काष्ठा sk_buff *skb, u8 ipproto)
अणु
	स्थिर काष्ठा iphdr *iph;
	काष्ठा ip_tunnel *tunnel;
	पूर्णांक sअगरindex;

	sअगरindex = netअगर_is_l3_master(skb->dev) ? IPCB(skb)->iअगर : 0;

	iph = ip_hdr(skb);
	tunnel = ipip6_tunnel_lookup(dev_net(skb->dev), skb->dev,
				     iph->saddr, iph->daddr, sअगरindex);
	अगर (tunnel) अणु
		स्थिर काष्ठा tnl_ptk_info *tpi;

		अगर (tunnel->parms.iph.protocol != ipproto &&
		    tunnel->parms.iph.protocol != 0)
			जाओ drop;

		अगर (!xfrm4_policy_check(शून्य, XFRM_POLICY_IN, skb))
			जाओ drop;
#अगर IS_ENABLED(CONFIG_MPLS)
		अगर (ipproto == IPPROTO_MPLS)
			tpi = &mplsip_tpi;
		अन्यथा
#पूर्ण_अगर
			tpi = &ipip_tpi;
		अगर (iptunnel_pull_header(skb, 0, tpi->proto, false))
			जाओ drop;
		वापस ip_tunnel_rcv(tunnel, skb, tpi, शून्य, log_ecn_error);
	पूर्ण

	वापस 1;

drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक ipip_rcv(काष्ठा sk_buff *skb)
अणु
	वापस sit_tunnel_rcv(skb, IPPROTO_IPIP);
पूर्ण

#अगर IS_ENABLED(CONFIG_MPLS)
अटल पूर्णांक mplsip_rcv(काष्ठा sk_buff *skb)
अणु
	वापस sit_tunnel_rcv(skb, IPPROTO_MPLS);
पूर्ण
#पूर्ण_अगर

/*
 * If the IPv6 address comes from 6rd / 6to4 (RFC 3056) addr space this function
 * stores the embedded IPv4 address in v4dst and वापसs true.
 */
अटल bool check_6rd(काष्ठा ip_tunnel *tunnel, स्थिर काष्ठा in6_addr *v6dst,
		      __be32 *v4dst)
अणु
#अगर_घोषित CONFIG_IPV6_SIT_6RD
	अगर (ipv6_prefix_equal(v6dst, &tunnel->ip6rd.prefix,
			      tunnel->ip6rd.prefixlen)) अणु
		अचिन्हित पूर्णांक pbw0, pbi0;
		पूर्णांक pbi1;
		u32 d;

		pbw0 = tunnel->ip6rd.prefixlen >> 5;
		pbi0 = tunnel->ip6rd.prefixlen & 0x1f;

		d = tunnel->ip6rd.relay_prefixlen < 32 ?
			(ntohl(v6dst->s6_addr32[pbw0]) << pbi0) >>
		    tunnel->ip6rd.relay_prefixlen : 0;

		pbi1 = pbi0 - tunnel->ip6rd.relay_prefixlen;
		अगर (pbi1 > 0)
			d |= ntohl(v6dst->s6_addr32[pbw0 + 1]) >>
			     (32 - pbi1);

		*v4dst = tunnel->ip6rd.relay_prefix | htonl(d);
		वापस true;
	पूर्ण
#अन्यथा
	अगर (v6dst->s6_addr16[0] == htons(0x2002)) अणु
		/* 6to4 v6 addr has 16 bits prefix, 32 v4addr, 16 SLA, ... */
		स_नकल(v4dst, &v6dst->s6_addr16[1], 4);
		वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण

अटल अंतरभूत __be32 try_6rd(काष्ठा ip_tunnel *tunnel,
			     स्थिर काष्ठा in6_addr *v6dst)
अणु
	__be32 dst = 0;
	check_6rd(tunnel, v6dst, &dst);
	वापस dst;
पूर्ण

/*
 *	This function assumes it is being called from dev_queue_xmit()
 *	and that skb is filled properly by that function.
 */

अटल netdev_tx_t ipip6_tunnel_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	स्थिर काष्ठा iphdr  *tiph = &tunnel->parms.iph;
	स्थिर काष्ठा ipv6hdr *iph6 = ipv6_hdr(skb);
	u8     tos = tunnel->parms.iph.tos;
	__be16 df = tiph->frag_off;
	काष्ठा rtable *rt;		/* Route to the other host */
	काष्ठा net_device *tdev;	/* Device to other host */
	अचिन्हित पूर्णांक max_headroom;	/* The extra header space needed */
	__be32 dst = tiph->daddr;
	काष्ठा flowi4 fl4;
	पूर्णांक    mtu;
	स्थिर काष्ठा in6_addr *addr6;
	पूर्णांक addr_type;
	u8 ttl;
	u8 protocol = IPPROTO_IPV6;
	पूर्णांक t_hlen = tunnel->hlen + माप(काष्ठा iphdr);

	अगर (tos == 1)
		tos = ipv6_get_dsfield(iph6);

	/* ISATAP (RFC4214) - must come beक्रमe 6to4 */
	अगर (dev->priv_flags & IFF_ISATAP) अणु
		काष्ठा neighbour *neigh = शून्य;
		bool करो_tx_error = false;

		अगर (skb_dst(skb))
			neigh = dst_neigh_lookup(skb_dst(skb), &iph6->daddr);

		अगर (!neigh) अणु
			net_dbg_ratelimited("nexthop == NULL\n");
			जाओ tx_error;
		पूर्ण

		addr6 = (स्थिर काष्ठा in6_addr *)&neigh->primary_key;
		addr_type = ipv6_addr_type(addr6);

		अगर ((addr_type & IPV6_ADDR_UNICAST) &&
		     ipv6_addr_is_isatap(addr6))
			dst = addr6->s6_addr32[3];
		अन्यथा
			करो_tx_error = true;

		neigh_release(neigh);
		अगर (करो_tx_error)
			जाओ tx_error;
	पूर्ण

	अगर (!dst)
		dst = try_6rd(tunnel, &iph6->daddr);

	अगर (!dst) अणु
		काष्ठा neighbour *neigh = शून्य;
		bool करो_tx_error = false;

		अगर (skb_dst(skb))
			neigh = dst_neigh_lookup(skb_dst(skb), &iph6->daddr);

		अगर (!neigh) अणु
			net_dbg_ratelimited("nexthop == NULL\n");
			जाओ tx_error;
		पूर्ण

		addr6 = (स्थिर काष्ठा in6_addr *)&neigh->primary_key;
		addr_type = ipv6_addr_type(addr6);

		अगर (addr_type == IPV6_ADDR_ANY) अणु
			addr6 = &ipv6_hdr(skb)->daddr;
			addr_type = ipv6_addr_type(addr6);
		पूर्ण

		अगर ((addr_type & IPV6_ADDR_COMPATv4) != 0)
			dst = addr6->s6_addr32[3];
		अन्यथा
			करो_tx_error = true;

		neigh_release(neigh);
		अगर (करो_tx_error)
			जाओ tx_error;
	पूर्ण

	flowi4_init_output(&fl4, tunnel->parms.link, tunnel->fwmark,
			   RT_TOS(tos), RT_SCOPE_UNIVERSE, IPPROTO_IPV6,
			   0, dst, tiph->saddr, 0, 0,
			   sock_net_uid(tunnel->net, शून्य));

	rt = dst_cache_get_ip4(&tunnel->dst_cache, &fl4.saddr);
	अगर (!rt) अणु
		rt = ip_route_output_flow(tunnel->net, &fl4, शून्य);
		अगर (IS_ERR(rt)) अणु
			dev->stats.tx_carrier_errors++;
			जाओ tx_error_icmp;
		पूर्ण
		dst_cache_set_ip4(&tunnel->dst_cache, &rt->dst, fl4.saddr);
	पूर्ण

	अगर (rt->rt_type != RTN_UNICAST) अणु
		ip_rt_put(rt);
		dev->stats.tx_carrier_errors++;
		जाओ tx_error_icmp;
	पूर्ण
	tdev = rt->dst.dev;

	अगर (tdev == dev) अणु
		ip_rt_put(rt);
		dev->stats.collisions++;
		जाओ tx_error;
	पूर्ण

	अगर (iptunnel_handle_offloads(skb, SKB_GSO_IPXIP4)) अणु
		ip_rt_put(rt);
		जाओ tx_error;
	पूर्ण

	अगर (df) अणु
		mtu = dst_mtu(&rt->dst) - t_hlen;

		अगर (mtu < 68) अणु
			dev->stats.collisions++;
			ip_rt_put(rt);
			जाओ tx_error;
		पूर्ण

		अगर (mtu < IPV6_MIN_MTU) अणु
			mtu = IPV6_MIN_MTU;
			df = 0;
		पूर्ण

		अगर (tunnel->parms.iph.daddr)
			skb_dst_update_pmtu_no_confirm(skb, mtu);

		अगर (skb->len > mtu && !skb_is_gso(skb)) अणु
			icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
			ip_rt_put(rt);
			जाओ tx_error;
		पूर्ण
	पूर्ण

	अगर (tunnel->err_count > 0) अणु
		अगर (समय_beक्रमe(jअगरfies,
				tunnel->err_समय + IPTUNNEL_ERR_TIMEO)) अणु
			tunnel->err_count--;
			dst_link_failure(skb);
		पूर्ण अन्यथा
			tunnel->err_count = 0;
	पूर्ण

	/*
	 * Okay, now see अगर we can stuff it in the buffer as-is.
	 */
	max_headroom = LL_RESERVED_SPACE(tdev) + t_hlen;

	अगर (skb_headroom(skb) < max_headroom || skb_shared(skb) ||
	    (skb_cloned(skb) && !skb_clone_writable(skb, 0))) अणु
		काष्ठा sk_buff *new_skb = skb_पुनः_स्मृति_headroom(skb, max_headroom);
		अगर (!new_skb) अणु
			ip_rt_put(rt);
			dev->stats.tx_dropped++;
			kमुक्त_skb(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
		अगर (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
		dev_kमुक्त_skb(skb);
		skb = new_skb;
		iph6 = ipv6_hdr(skb);
	पूर्ण
	ttl = tiph->ttl;
	अगर (ttl == 0)
		ttl = iph6->hop_limit;
	tos = INET_ECN_encapsulate(tos, ipv6_get_dsfield(iph6));

	अगर (ip_tunnel_encap(skb, tunnel, &protocol, &fl4) < 0) अणु
		ip_rt_put(rt);
		जाओ tx_error;
	पूर्ण

	skb_set_inner_ipproto(skb, IPPROTO_IPV6);

	iptunnel_xmit(शून्य, rt, skb, fl4.saddr, fl4.daddr, protocol, tos, ttl,
		      df, !net_eq(tunnel->net, dev_net(dev)));
	वापस NETDEV_TX_OK;

tx_error_icmp:
	dst_link_failure(skb);
tx_error:
	kमुक्त_skb(skb);
	dev->stats.tx_errors++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t sit_tunnel_xmit__(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev, u8 ipproto)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	स्थिर काष्ठा iphdr  *tiph = &tunnel->parms.iph;

	अगर (iptunnel_handle_offloads(skb, SKB_GSO_IPXIP4))
		जाओ tx_error;

	skb_set_inner_ipproto(skb, ipproto);

	ip_tunnel_xmit(skb, dev, tiph, ipproto);
	वापस NETDEV_TX_OK;
tx_error:
	kमुक्त_skb(skb);
	dev->stats.tx_errors++;
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t sit_tunnel_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *dev)
अणु
	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_err;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		sit_tunnel_xmit__(skb, dev, IPPROTO_IPIP);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		ipip6_tunnel_xmit(skb, dev);
		अवरोध;
#अगर IS_ENABLED(CONFIG_MPLS)
	हाल htons(ETH_P_MPLS_UC):
		sit_tunnel_xmit__(skb, dev, IPPROTO_MPLS);
		अवरोध;
#पूर्ण_अगर
	शेष:
		जाओ tx_err;
	पूर्ण

	वापस NETDEV_TX_OK;

tx_err:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;

पूर्ण

अटल व्योम ipip6_tunnel_bind_dev(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *tdev = शून्य;
	काष्ठा ip_tunnel *tunnel;
	स्थिर काष्ठा iphdr *iph;
	काष्ठा flowi4 fl4;

	tunnel = netdev_priv(dev);
	iph = &tunnel->parms.iph;

	अगर (iph->daddr) अणु
		काष्ठा rtable *rt = ip_route_output_ports(tunnel->net, &fl4,
							  शून्य,
							  iph->daddr, iph->saddr,
							  0, 0,
							  IPPROTO_IPV6,
							  RT_TOS(iph->tos),
							  tunnel->parms.link);

		अगर (!IS_ERR(rt)) अणु
			tdev = rt->dst.dev;
			ip_rt_put(rt);
		पूर्ण
		dev->flags |= IFF_POINTOPOINT;
	पूर्ण

	अगर (!tdev && tunnel->parms.link)
		tdev = __dev_get_by_index(tunnel->net, tunnel->parms.link);

	अगर (tdev && !netअगर_is_l3_master(tdev)) अणु
		पूर्णांक t_hlen = tunnel->hlen + माप(काष्ठा iphdr);

		dev->mtu = tdev->mtu - t_hlen;
		अगर (dev->mtu < IPV6_MIN_MTU)
			dev->mtu = IPV6_MIN_MTU;
	पूर्ण
पूर्ण

अटल व्योम ipip6_tunnel_update(काष्ठा ip_tunnel *t, काष्ठा ip_tunnel_parm *p,
				__u32 fwmark)
अणु
	काष्ठा net *net = t->net;
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);

	ipip6_tunnel_unlink(sitn, t);
	synchronize_net();
	t->parms.iph.saddr = p->iph.saddr;
	t->parms.iph.daddr = p->iph.daddr;
	स_नकल(t->dev->dev_addr, &p->iph.saddr, 4);
	स_नकल(t->dev->broadcast, &p->iph.daddr, 4);
	ipip6_tunnel_link(sitn, t);
	t->parms.iph.ttl = p->iph.ttl;
	t->parms.iph.tos = p->iph.tos;
	t->parms.iph.frag_off = p->iph.frag_off;
	अगर (t->parms.link != p->link || t->fwmark != fwmark) अणु
		t->parms.link = p->link;
		t->fwmark = fwmark;
		ipip6_tunnel_bind_dev(t->dev);
	पूर्ण
	dst_cache_reset(&t->dst_cache);
	netdev_state_change(t->dev);
पूर्ण

#अगर_घोषित CONFIG_IPV6_SIT_6RD
अटल पूर्णांक ipip6_tunnel_update_6rd(काष्ठा ip_tunnel *t,
				   काष्ठा ip_tunnel_6rd *ip6rd)
अणु
	काष्ठा in6_addr prefix;
	__be32 relay_prefix;

	अगर (ip6rd->relay_prefixlen > 32 ||
	    ip6rd->prefixlen + (32 - ip6rd->relay_prefixlen) > 64)
		वापस -EINVAL;

	ipv6_addr_prefix(&prefix, &ip6rd->prefix, ip6rd->prefixlen);
	अगर (!ipv6_addr_equal(&prefix, &ip6rd->prefix))
		वापस -EINVAL;
	अगर (ip6rd->relay_prefixlen)
		relay_prefix = ip6rd->relay_prefix &
			       htonl(0xffffffffUL <<
				     (32 - ip6rd->relay_prefixlen));
	अन्यथा
		relay_prefix = 0;
	अगर (relay_prefix != ip6rd->relay_prefix)
		वापस -EINVAL;

	t->ip6rd.prefix = prefix;
	t->ip6rd.relay_prefix = relay_prefix;
	t->ip6rd.prefixlen = ip6rd->prefixlen;
	t->ip6rd.relay_prefixlen = ip6rd->relay_prefixlen;
	dst_cache_reset(&t->dst_cache);
	netdev_state_change(t->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_get6rd(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_6rd ip6rd;
	काष्ठा ip_tunnel_parm p;

	अगर (dev == dev_to_sit_net(dev)->fb_tunnel_dev) अणु
		अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p)))
			वापस -EFAULT;
		t = ipip6_tunnel_locate(t->net, &p, 0);
	पूर्ण
	अगर (!t)
		t = netdev_priv(dev);

	ip6rd.prefix = t->ip6rd.prefix;
	ip6rd.relay_prefix = t->ip6rd.relay_prefix;
	ip6rd.prefixlen = t->ip6rd.prefixlen;
	ip6rd.relay_prefixlen = t->ip6rd.relay_prefixlen;
	अगर (copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &ip6rd, माप(ip6rd)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_6rdctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_6rd ip6rd;
	पूर्णांक err;

	अगर (!ns_capable(t->net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;
	अगर (copy_from_user(&ip6rd, अगरr->अगरr_अगरru.अगरru_data, माप(ip6rd)))
		वापस -EFAULT;

	अगर (cmd != SIOCDEL6RD) अणु
		err = ipip6_tunnel_update_6rd(t, &ip6rd);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा
		ipip6_tunnel_clone_6rd(dev, dev_to_sit_net(dev));
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_IPV6_SIT_6RD */

अटल bool ipip6_valid_ip_proto(u8 ipproto)
अणु
	वापस ipproto == IPPROTO_IPV6 ||
		ipproto == IPPROTO_IPIP ||
#अगर IS_ENABLED(CONFIG_MPLS)
		ipproto == IPPROTO_MPLS ||
#पूर्ण_अगर
		ipproto == 0;
पूर्ण

अटल पूर्णांक
__ipip6_tunnel_ioctl_validate(काष्ठा net *net, काष्ठा ip_tunnel_parm *p)
अणु
	अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (!ipip6_valid_ip_proto(p->iph.protocol))
		वापस -EINVAL;
	अगर (p->iph.version != 4 ||
	    p->iph.ihl != 5 || (p->iph.frag_off & htons(~IP_DF)))
		वापस -EINVAL;

	अगर (p->iph.ttl)
		p->iph.frag_off |= htons(IP_DF);
	वापस 0;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_get(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	अगर (dev == dev_to_sit_net(dev)->fb_tunnel_dev)
		t = ipip6_tunnel_locate(t->net, p, 0);
	अगर (!t)
		t = netdev_priv(dev);
	स_नकल(p, &t->parms, माप(*p));
	वापस 0;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_add(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	पूर्णांक err;

	err = __ipip6_tunnel_ioctl_validate(t->net, p);
	अगर (err)
		वापस err;

	t = ipip6_tunnel_locate(t->net, p, 1);
	अगर (!t)
		वापस -ENOBUFS;
	वापस 0;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_change(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	पूर्णांक err;

	err = __ipip6_tunnel_ioctl_validate(t->net, p);
	अगर (err)
		वापस err;

	t = ipip6_tunnel_locate(t->net, p, 0);
	अगर (dev == dev_to_sit_net(dev)->fb_tunnel_dev) अणु
		अगर (!t)
			वापस -ENOENT;
	पूर्ण अन्यथा अणु
		अगर (t) अणु
			अगर (t->dev != dev)
				वापस -EEXIST;
		पूर्ण अन्यथा अणु
			अगर (((dev->flags & IFF_POINTOPOINT) && !p->iph.daddr) ||
			    (!(dev->flags & IFF_POINTOPOINT) && p->iph.daddr))
				वापस -EINVAL;
			t = netdev_priv(dev);
		पूर्ण

		ipip6_tunnel_update(t, p, t->fwmark);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_del(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);

	अगर (!ns_capable(t->net->user_ns, CAP_NET_ADMIN))
		वापस -EPERM;

	अगर (dev == dev_to_sit_net(dev)->fb_tunnel_dev) अणु
		t = ipip6_tunnel_locate(t->net, p, 0);
		अगर (!t)
			वापस -ENOENT;
		अगर (t == netdev_priv(dev_to_sit_net(dev)->fb_tunnel_dev))
			वापस -EPERM;
		dev = t->dev;
	पूर्ण
	unरेजिस्टर_netdevice(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक
ipip6_tunnel_ctl(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGETTUNNEL:
		वापस ipip6_tunnel_get(dev, p);
	हाल SIOCADDTUNNEL:
		वापस ipip6_tunnel_add(dev, p);
	हाल SIOCCHGTUNNEL:
		वापस ipip6_tunnel_change(dev, p);
	हाल SIOCDELTUNNEL:
		वापस ipip6_tunnel_del(dev, p);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक
ipip6_tunnel_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGETTUNNEL:
	हाल SIOCADDTUNNEL:
	हाल SIOCCHGTUNNEL:
	हाल SIOCDELTUNNEL:
		वापस ip_tunnel_ioctl(dev, अगरr, cmd);
	हाल SIOCGETPRL:
		वापस ipip6_tunnel_get_prl(dev, अगरr);
	हाल SIOCADDPRL:
	हाल SIOCDELPRL:
	हाल SIOCCHGPRL:
		वापस ipip6_tunnel_prl_ctl(dev, अगरr, cmd);
#अगर_घोषित CONFIG_IPV6_SIT_6RD
	हाल SIOCGET6RD:
		वापस ipip6_tunnel_get6rd(dev, अगरr);
	हाल SIOCADD6RD:
	हाल SIOCCHG6RD:
	हाल SIOCDEL6RD:
		वापस ipip6_tunnel_6rdctl(dev, अगरr, cmd);
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा net_device_ops ipip6_netdev_ops = अणु
	.nकरो_init	= ipip6_tunnel_init,
	.nकरो_uninit	= ipip6_tunnel_uninit,
	.nकरो_start_xmit	= sit_tunnel_xmit,
	.nकरो_करो_ioctl	= ipip6_tunnel_ioctl,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_get_अगरlink = ip_tunnel_get_अगरlink,
	.nकरो_tunnel_ctl = ipip6_tunnel_ctl,
पूर्ण;

अटल व्योम ipip6_dev_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	dst_cache_destroy(&tunnel->dst_cache);
	मुक्त_percpu(dev->tstats);
पूर्ण

#घोषणा SIT_FEATURES (NETIF_F_SG	   | \
		      NETIF_F_FRAGLIST	   | \
		      NETIF_F_HIGHDMA	   | \
		      NETIF_F_GSO_SOFTWARE | \
		      NETIF_F_HW_CSUM)

अटल व्योम ipip6_tunnel_setup(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	पूर्णांक t_hlen = tunnel->hlen + माप(काष्ठा iphdr);

	dev->netdev_ops		= &ipip6_netdev_ops;
	dev->header_ops		= &ip_tunnel_header_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->priv_deकाष्ठाor	= ipip6_dev_मुक्त;

	dev->type		= ARPHRD_SIT;
	dev->mtu		= ETH_DATA_LEN - t_hlen;
	dev->min_mtu		= IPV6_MIN_MTU;
	dev->max_mtu		= IP6_MAX_MTU - t_hlen;
	dev->flags		= IFF_NOARP;
	netअगर_keep_dst(dev);
	dev->addr_len		= 4;
	dev->features		|= NETIF_F_LLTX;
	dev->features		|= SIT_FEATURES;
	dev->hw_features	|= SIT_FEATURES;
पूर्ण

अटल पूर्णांक ipip6_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	पूर्णांक err;

	tunnel->dev = dev;
	tunnel->net = dev_net(dev);
	म_नकल(tunnel->parms.name, dev->name);

	ipip6_tunnel_bind_dev(dev);
	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = dst_cache_init(&tunnel->dst_cache, GFP_KERNEL);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		dev->tstats = शून्य;
		वापस err;
	पूर्ण
	dev_hold(dev);
	वापस 0;
पूर्ण

अटल व्योम __net_init ipip6_fb_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा iphdr *iph = &tunnel->parms.iph;
	काष्ठा net *net = dev_net(dev);
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);

	iph->version		= 4;
	iph->protocol		= IPPROTO_IPV6;
	iph->ihl		= 5;
	iph->ttl		= 64;

	rcu_assign_poपूर्णांकer(sitn->tunnels_wc[0], tunnel);
पूर्ण

अटल पूर्णांक ipip6_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	u8 proto;

	अगर (!data || !data[IFLA_IPTUN_PROTO])
		वापस 0;

	proto = nla_get_u8(data[IFLA_IPTUN_PROTO]);
	अगर (!ipip6_valid_ip_proto(proto))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम ipip6_netlink_parms(काष्ठा nlattr *data[],
				काष्ठा ip_tunnel_parm *parms,
				__u32 *fwmark)
अणु
	स_रखो(parms, 0, माप(*parms));

	parms->iph.version = 4;
	parms->iph.protocol = IPPROTO_IPV6;
	parms->iph.ihl = 5;
	parms->iph.ttl = 64;

	अगर (!data)
		वापस;

	अगर (data[IFLA_IPTUN_LINK])
		parms->link = nla_get_u32(data[IFLA_IPTUN_LINK]);

	अगर (data[IFLA_IPTUN_LOCAL])
		parms->iph.saddr = nla_get_be32(data[IFLA_IPTUN_LOCAL]);

	अगर (data[IFLA_IPTUN_REMOTE])
		parms->iph.daddr = nla_get_be32(data[IFLA_IPTUN_REMOTE]);

	अगर (data[IFLA_IPTUN_TTL]) अणु
		parms->iph.ttl = nla_get_u8(data[IFLA_IPTUN_TTL]);
		अगर (parms->iph.ttl)
			parms->iph.frag_off = htons(IP_DF);
	पूर्ण

	अगर (data[IFLA_IPTUN_TOS])
		parms->iph.tos = nla_get_u8(data[IFLA_IPTUN_TOS]);

	अगर (!data[IFLA_IPTUN_PMTUDISC] || nla_get_u8(data[IFLA_IPTUN_PMTUDISC]))
		parms->iph.frag_off = htons(IP_DF);

	अगर (data[IFLA_IPTUN_FLAGS])
		parms->i_flags = nla_get_be16(data[IFLA_IPTUN_FLAGS]);

	अगर (data[IFLA_IPTUN_PROTO])
		parms->iph.protocol = nla_get_u8(data[IFLA_IPTUN_PROTO]);

	अगर (data[IFLA_IPTUN_FWMARK])
		*fwmark = nla_get_u32(data[IFLA_IPTUN_FWMARK]);
पूर्ण

/* This function वापसs true when ENCAP attributes are present in the nl msg */
अटल bool ipip6_netlink_encap_parms(काष्ठा nlattr *data[],
				      काष्ठा ip_tunnel_encap *ipencap)
अणु
	bool ret = false;

	स_रखो(ipencap, 0, माप(*ipencap));

	अगर (!data)
		वापस ret;

	अगर (data[IFLA_IPTUN_ENCAP_TYPE]) अणु
		ret = true;
		ipencap->type = nla_get_u16(data[IFLA_IPTUN_ENCAP_TYPE]);
	पूर्ण

	अगर (data[IFLA_IPTUN_ENCAP_FLAGS]) अणु
		ret = true;
		ipencap->flags = nla_get_u16(data[IFLA_IPTUN_ENCAP_FLAGS]);
	पूर्ण

	अगर (data[IFLA_IPTUN_ENCAP_SPORT]) अणु
		ret = true;
		ipencap->sport = nla_get_be16(data[IFLA_IPTUN_ENCAP_SPORT]);
	पूर्ण

	अगर (data[IFLA_IPTUN_ENCAP_DPORT]) अणु
		ret = true;
		ipencap->dport = nla_get_be16(data[IFLA_IPTUN_ENCAP_DPORT]);
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_IPV6_SIT_6RD
/* This function वापसs true when 6RD attributes are present in the nl msg */
अटल bool ipip6_netlink_6rd_parms(काष्ठा nlattr *data[],
				    काष्ठा ip_tunnel_6rd *ip6rd)
अणु
	bool ret = false;
	स_रखो(ip6rd, 0, माप(*ip6rd));

	अगर (!data)
		वापस ret;

	अगर (data[IFLA_IPTUN_6RD_PREFIX]) अणु
		ret = true;
		ip6rd->prefix = nla_get_in6_addr(data[IFLA_IPTUN_6RD_PREFIX]);
	पूर्ण

	अगर (data[IFLA_IPTUN_6RD_RELAY_PREFIX]) अणु
		ret = true;
		ip6rd->relay_prefix =
			nla_get_be32(data[IFLA_IPTUN_6RD_RELAY_PREFIX]);
	पूर्ण

	अगर (data[IFLA_IPTUN_6RD_PREFIXLEN]) अणु
		ret = true;
		ip6rd->prefixlen = nla_get_u16(data[IFLA_IPTUN_6RD_PREFIXLEN]);
	पूर्ण

	अगर (data[IFLA_IPTUN_6RD_RELAY_PREFIXLEN]) अणु
		ret = true;
		ip6rd->relay_prefixlen =
			nla_get_u16(data[IFLA_IPTUN_6RD_RELAY_PREFIXLEN]);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ipip6_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip_tunnel *nt;
	काष्ठा ip_tunnel_encap ipencap;
#अगर_घोषित CONFIG_IPV6_SIT_6RD
	काष्ठा ip_tunnel_6rd ip6rd;
#पूर्ण_अगर
	पूर्णांक err;

	nt = netdev_priv(dev);

	अगर (ipip6_netlink_encap_parms(data, &ipencap)) अणु
		err = ip_tunnel_encap_setup(nt, &ipencap);
		अगर (err < 0)
			वापस err;
	पूर्ण

	ipip6_netlink_parms(data, &nt->parms, &nt->fwmark);

	अगर (ipip6_tunnel_locate(net, &nt->parms, 0))
		वापस -EEXIST;

	err = ipip6_tunnel_create(dev);
	अगर (err < 0)
		वापस err;

	अगर (tb[IFLA_MTU]) अणु
		u32 mtu = nla_get_u32(tb[IFLA_MTU]);

		अगर (mtu >= IPV6_MIN_MTU &&
		    mtu <= IP6_MAX_MTU - dev->hard_header_len)
			dev->mtu = mtu;
	पूर्ण

#अगर_घोषित CONFIG_IPV6_SIT_6RD
	अगर (ipip6_netlink_6rd_parms(data, &ip6rd)) अणु
		err = ipip6_tunnel_update_6rd(nt, &ip6rd);
		अगर (err < 0)
			unरेजिस्टर_netdevice_queue(dev, शून्य);
	पूर्ण
#पूर्ण_अगर

	वापस err;
पूर्ण

अटल पूर्णांक ipip6_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			    काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा ip_tunnel_parm p;
	काष्ठा ip_tunnel_encap ipencap;
	काष्ठा net *net = t->net;
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);
#अगर_घोषित CONFIG_IPV6_SIT_6RD
	काष्ठा ip_tunnel_6rd ip6rd;
#पूर्ण_अगर
	__u32 fwmark = t->fwmark;
	पूर्णांक err;

	अगर (dev == sitn->fb_tunnel_dev)
		वापस -EINVAL;

	अगर (ipip6_netlink_encap_parms(data, &ipencap)) अणु
		err = ip_tunnel_encap_setup(t, &ipencap);
		अगर (err < 0)
			वापस err;
	पूर्ण

	ipip6_netlink_parms(data, &p, &fwmark);

	अगर (((dev->flags & IFF_POINTOPOINT) && !p.iph.daddr) ||
	    (!(dev->flags & IFF_POINTOPOINT) && p.iph.daddr))
		वापस -EINVAL;

	t = ipip6_tunnel_locate(net, &p, 0);

	अगर (t) अणु
		अगर (t->dev != dev)
			वापस -EEXIST;
	पूर्ण अन्यथा
		t = netdev_priv(dev);

	ipip6_tunnel_update(t, &p, fwmark);

#अगर_घोषित CONFIG_IPV6_SIT_6RD
	अगर (ipip6_netlink_6rd_parms(data, &ip6rd))
		वापस ipip6_tunnel_update_6rd(t, &ip6rd);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल माप_प्रकार ipip6_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_IPTUN_LINK */
		nla_total_size(4) +
		/* IFLA_IPTUN_LOCAL */
		nla_total_size(4) +
		/* IFLA_IPTUN_REMOTE */
		nla_total_size(4) +
		/* IFLA_IPTUN_TTL */
		nla_total_size(1) +
		/* IFLA_IPTUN_TOS */
		nla_total_size(1) +
		/* IFLA_IPTUN_PMTUDISC */
		nla_total_size(1) +
		/* IFLA_IPTUN_FLAGS */
		nla_total_size(2) +
		/* IFLA_IPTUN_PROTO */
		nla_total_size(1) +
#अगर_घोषित CONFIG_IPV6_SIT_6RD
		/* IFLA_IPTUN_6RD_PREFIX */
		nla_total_size(माप(काष्ठा in6_addr)) +
		/* IFLA_IPTUN_6RD_RELAY_PREFIX */
		nla_total_size(4) +
		/* IFLA_IPTUN_6RD_PREFIXLEN */
		nla_total_size(2) +
		/* IFLA_IPTUN_6RD_RELAY_PREFIXLEN */
		nla_total_size(2) +
#पूर्ण_अगर
		/* IFLA_IPTUN_ENCAP_TYPE */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_FLAGS */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_SPORT */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_DPORT */
		nla_total_size(2) +
		/* IFLA_IPTUN_FWMARK */
		nla_total_size(4) +
		0;
पूर्ण

अटल पूर्णांक ipip6_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा ip_tunnel_parm *parm = &tunnel->parms;

	अगर (nla_put_u32(skb, IFLA_IPTUN_LINK, parm->link) ||
	    nla_put_in_addr(skb, IFLA_IPTUN_LOCAL, parm->iph.saddr) ||
	    nla_put_in_addr(skb, IFLA_IPTUN_REMOTE, parm->iph.daddr) ||
	    nla_put_u8(skb, IFLA_IPTUN_TTL, parm->iph.ttl) ||
	    nla_put_u8(skb, IFLA_IPTUN_TOS, parm->iph.tos) ||
	    nla_put_u8(skb, IFLA_IPTUN_PMTUDISC,
		       !!(parm->iph.frag_off & htons(IP_DF))) ||
	    nla_put_u8(skb, IFLA_IPTUN_PROTO, parm->iph.protocol) ||
	    nla_put_be16(skb, IFLA_IPTUN_FLAGS, parm->i_flags) ||
	    nla_put_u32(skb, IFLA_IPTUN_FWMARK, tunnel->fwmark))
		जाओ nla_put_failure;

#अगर_घोषित CONFIG_IPV6_SIT_6RD
	अगर (nla_put_in6_addr(skb, IFLA_IPTUN_6RD_PREFIX,
			     &tunnel->ip6rd.prefix) ||
	    nla_put_in_addr(skb, IFLA_IPTUN_6RD_RELAY_PREFIX,
			    tunnel->ip6rd.relay_prefix) ||
	    nla_put_u16(skb, IFLA_IPTUN_6RD_PREFIXLEN,
			tunnel->ip6rd.prefixlen) ||
	    nla_put_u16(skb, IFLA_IPTUN_6RD_RELAY_PREFIXLEN,
			tunnel->ip6rd.relay_prefixlen))
		जाओ nla_put_failure;
#पूर्ण_अगर

	अगर (nla_put_u16(skb, IFLA_IPTUN_ENCAP_TYPE,
			tunnel->encap.type) ||
	    nla_put_be16(skb, IFLA_IPTUN_ENCAP_SPORT,
			tunnel->encap.sport) ||
	    nla_put_be16(skb, IFLA_IPTUN_ENCAP_DPORT,
			tunnel->encap.dport) ||
	    nla_put_u16(skb, IFLA_IPTUN_ENCAP_FLAGS,
			tunnel->encap.flags))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy ipip6_policy[IFLA_IPTUN_MAX + 1] = अणु
	[IFLA_IPTUN_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_LOCAL]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_REMOTE]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_TTL]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_TOS]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_PMTUDISC]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_FLAGS]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_PROTO]		= अणु .type = NLA_U8 पूर्ण,
#अगर_घोषित CONFIG_IPV6_SIT_6RD
	[IFLA_IPTUN_6RD_PREFIX]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_IPTUN_6RD_RELAY_PREFIX]	= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_6RD_PREFIXLEN]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_6RD_RELAY_PREFIXLEN] = अणु .type = NLA_U16 पूर्ण,
#पूर्ण_अगर
	[IFLA_IPTUN_ENCAP_TYPE]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_SPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_DPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_FWMARK]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल व्योम ipip6_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);

	अगर (dev != sitn->fb_tunnel_dev)
		unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल काष्ठा rtnl_link_ops sit_link_ops __पढ़ो_mostly = अणु
	.kind		= "sit",
	.maxtype	= IFLA_IPTUN_MAX,
	.policy		= ipip6_policy,
	.priv_size	= माप(काष्ठा ip_tunnel),
	.setup		= ipip6_tunnel_setup,
	.validate	= ipip6_validate,
	.newlink	= ipip6_newlink,
	.changelink	= ipip6_changelink,
	.get_size	= ipip6_get_size,
	.fill_info	= ipip6_fill_info,
	.dellink	= ipip6_dellink,
	.get_link_net	= ip_tunnel_get_link_net,
पूर्ण;

अटल काष्ठा xfrm_tunnel sit_handler __पढ़ो_mostly = अणु
	.handler	=	ipip6_rcv,
	.err_handler	=	ipip6_err,
	.priority	=	1,
पूर्ण;

अटल काष्ठा xfrm_tunnel ipip_handler __पढ़ो_mostly = अणु
	.handler	=	ipip_rcv,
	.err_handler	=	ipip6_err,
	.priority	=	2,
पूर्ण;

#अगर IS_ENABLED(CONFIG_MPLS)
अटल काष्ठा xfrm_tunnel mplsip_handler __पढ़ो_mostly = अणु
	.handler	=	mplsip_rcv,
	.err_handler	=	ipip6_err,
	.priority	=	2,
पूर्ण;
#पूर्ण_अगर

अटल व्योम __net_निकास sit_destroy_tunnels(काष्ठा net *net,
					   काष्ठा list_head *head)
अणु
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);
	काष्ठा net_device *dev, *aux;
	पूर्णांक prio;

	क्रम_each_netdev_safe(net, dev, aux)
		अगर (dev->rtnl_link_ops == &sit_link_ops)
			unरेजिस्टर_netdevice_queue(dev, head);

	क्रम (prio = 0; prio < 4; prio++) अणु
		पूर्णांक h;
		क्रम (h = 0; h < (prio ? IP6_SIT_HASH_SIZE : 1); h++) अणु
			काष्ठा ip_tunnel *t;

			t = rtnl_dereference(sitn->tunnels[prio][h]);
			जबतक (t) अणु
				/* If dev is in the same netns, it has alपढ़ोy
				 * been added to the list by the previous loop.
				 */
				अगर (!net_eq(dev_net(t->dev), net))
					unरेजिस्टर_netdevice_queue(t->dev,
								   head);
				t = rtnl_dereference(t->next);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __net_init sit_init_net(काष्ठा net *net)
अणु
	काष्ठा sit_net *sitn = net_generic(net, sit_net_id);
	काष्ठा ip_tunnel *t;
	पूर्णांक err;

	sitn->tunnels[0] = sitn->tunnels_wc;
	sitn->tunnels[1] = sitn->tunnels_l;
	sitn->tunnels[2] = sitn->tunnels_r;
	sitn->tunnels[3] = sitn->tunnels_r_l;

	अगर (!net_has_fallback_tunnels(net))
		वापस 0;

	sitn->fb_tunnel_dev = alloc_netdev(माप(काष्ठा ip_tunnel), "sit0",
					   NET_NAME_UNKNOWN,
					   ipip6_tunnel_setup);
	अगर (!sitn->fb_tunnel_dev) अणु
		err = -ENOMEM;
		जाओ err_alloc_dev;
	पूर्ण
	dev_net_set(sitn->fb_tunnel_dev, net);
	sitn->fb_tunnel_dev->rtnl_link_ops = &sit_link_ops;
	/* FB netdevice is special: we have one, and only one per netns.
	 * Allowing to move it to another netns is clearly unsafe.
	 */
	sitn->fb_tunnel_dev->features |= NETIF_F_NETNS_LOCAL;

	err = रेजिस्टर_netdev(sitn->fb_tunnel_dev);
	अगर (err)
		जाओ err_reg_dev;

	ipip6_tunnel_clone_6rd(sitn->fb_tunnel_dev, sitn);
	ipip6_fb_tunnel_init(sitn->fb_tunnel_dev);

	t = netdev_priv(sitn->fb_tunnel_dev);

	म_नकल(t->parms.name, sitn->fb_tunnel_dev->name);
	वापस 0;

err_reg_dev:
	ipip6_dev_मुक्त(sitn->fb_tunnel_dev);
	मुक्त_netdev(sitn->fb_tunnel_dev);
err_alloc_dev:
	वापस err;
पूर्ण

अटल व्योम __net_निकास sit_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	LIST_HEAD(list);
	काष्ठा net *net;

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list)
		sit_destroy_tunnels(net, &list);

	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations sit_net_ops = अणु
	.init = sit_init_net,
	.निकास_batch = sit_निकास_batch_net,
	.id   = &sit_net_id,
	.size = माप(काष्ठा sit_net),
पूर्ण;

अटल व्योम __निकास sit_cleanup(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&sit_link_ops);
	xfrm4_tunnel_deरेजिस्टर(&sit_handler, AF_INET6);
	xfrm4_tunnel_deरेजिस्टर(&ipip_handler, AF_INET);
#अगर IS_ENABLED(CONFIG_MPLS)
	xfrm4_tunnel_deरेजिस्टर(&mplsip_handler, AF_MPLS);
#पूर्ण_अगर

	unरेजिस्टर_pernet_device(&sit_net_ops);
	rcu_barrier(); /* Wait क्रम completion of call_rcu()'s */
पूर्ण

अटल पूर्णांक __init sit_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("IPv6, IPv4 and MPLS over IPv4 tunneling driver\n");

	err = रेजिस्टर_pernet_device(&sit_net_ops);
	अगर (err < 0)
		वापस err;
	err = xfrm4_tunnel_रेजिस्टर(&sit_handler, AF_INET6);
	अगर (err < 0) अणु
		pr_info("%s: can't register ip6ip4\n", __func__);
		जाओ xfrm_tunnel_failed;
	पूर्ण
	err = xfrm4_tunnel_रेजिस्टर(&ipip_handler, AF_INET);
	अगर (err < 0) अणु
		pr_info("%s: can't register ip4ip4\n", __func__);
		जाओ xfrm_tunnel4_failed;
	पूर्ण
#अगर IS_ENABLED(CONFIG_MPLS)
	err = xfrm4_tunnel_रेजिस्टर(&mplsip_handler, AF_MPLS);
	अगर (err < 0) अणु
		pr_info("%s: can't register mplsip\n", __func__);
		जाओ xfrm_tunnel_mpls_failed;
	पूर्ण
#पूर्ण_अगर
	err = rtnl_link_रेजिस्टर(&sit_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

out:
	वापस err;

rtnl_link_failed:
#अगर IS_ENABLED(CONFIG_MPLS)
	xfrm4_tunnel_deरेजिस्टर(&mplsip_handler, AF_MPLS);
xfrm_tunnel_mpls_failed:
#पूर्ण_अगर
	xfrm4_tunnel_deरेजिस्टर(&ipip_handler, AF_INET);
xfrm_tunnel4_failed:
	xfrm4_tunnel_deरेजिस्टर(&sit_handler, AF_INET6);
xfrm_tunnel_failed:
	unरेजिस्टर_pernet_device(&sit_net_ops);
	जाओ out;
पूर्ण

module_init(sit_init);
module_निकास(sit_cleanup);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("sit");
MODULE_ALIAS_NETDEV("sit0");
