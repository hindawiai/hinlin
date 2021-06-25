<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 भव tunneling पूर्णांकerface
 *
 *	Copyright (C) 2013 secunet Security Networks AG
 *
 *	Author:
 *	Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 *
 *	Based on:
 *	net/ipv6/ip6_tunnel.c
 */

#समावेश <linux/module.h>
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/sockios.h>
#समावेश <linux/icmp.h>
#समावेश <linux/अगर.h>
#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/init.h>
#समावेश <linux/route.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/slab.h>
#समावेश <linux/hash.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>

#समावेश <net/icmp.h>
#समावेश <net/ip.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/etherdevice.h>

#घोषणा IP6_VTI_HASH_SIZE_SHIFT  5
#घोषणा IP6_VTI_HASH_SIZE (1 << IP6_VTI_HASH_SIZE_SHIFT)

अटल u32 HASH(स्थिर काष्ठा in6_addr *addr1, स्थिर काष्ठा in6_addr *addr2)
अणु
	u32 hash = ipv6_addr_hash(addr1) ^ ipv6_addr_hash(addr2);

	वापस hash_32(hash, IP6_VTI_HASH_SIZE_SHIFT);
पूर्ण

अटल पूर्णांक vti6_dev_init(काष्ठा net_device *dev);
अटल व्योम vti6_dev_setup(काष्ठा net_device *dev);
अटल काष्ठा rtnl_link_ops vti6_link_ops __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक vti6_net_id __पढ़ो_mostly;
काष्ठा vti6_net अणु
	/* the vti6 tunnel fallback device */
	काष्ठा net_device *fb_tnl_dev;
	/* lists क्रम storing tunnels in use */
	काष्ठा ip6_tnl __rcu *tnls_r_l[IP6_VTI_HASH_SIZE];
	काष्ठा ip6_tnl __rcu *tnls_wc[1];
	काष्ठा ip6_tnl __rcu **tnls[2];
पूर्ण;

#घोषणा क्रम_each_vti6_tunnel_rcu(start) \
	क्रम (t = rcu_dereference(start); t; t = rcu_dereference(t->next))

/**
 * vti6_tnl_lookup - fetch tunnel matching the end-poपूर्णांक addresses
 *   @net: network namespace
 *   @remote: the address of the tunnel निकास-poपूर्णांक
 *   @local: the address of the tunnel entry-poपूर्णांक
 *
 * Return:
 *   tunnel matching given end-poपूर्णांकs अगर found,
 *   अन्यथा fallback tunnel अगर its device is up,
 *   अन्यथा %शून्य
 **/
अटल काष्ठा ip6_tnl *
vti6_tnl_lookup(काष्ठा net *net, स्थिर काष्ठा in6_addr *remote,
		स्थिर काष्ठा in6_addr *local)
अणु
	अचिन्हित पूर्णांक hash = HASH(remote, local);
	काष्ठा ip6_tnl *t;
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);
	काष्ठा in6_addr any;

	क्रम_each_vti6_tunnel_rcu(ip6n->tnls_r_l[hash]) अणु
		अगर (ipv6_addr_equal(local, &t->parms.laddr) &&
		    ipv6_addr_equal(remote, &t->parms.raddr) &&
		    (t->dev->flags & IFF_UP))
			वापस t;
	पूर्ण

	स_रखो(&any, 0, माप(any));
	hash = HASH(&any, local);
	क्रम_each_vti6_tunnel_rcu(ip6n->tnls_r_l[hash]) अणु
		अगर (ipv6_addr_equal(local, &t->parms.laddr) &&
		    (t->dev->flags & IFF_UP))
			वापस t;
	पूर्ण

	hash = HASH(remote, &any);
	क्रम_each_vti6_tunnel_rcu(ip6n->tnls_r_l[hash]) अणु
		अगर (ipv6_addr_equal(remote, &t->parms.raddr) &&
		    (t->dev->flags & IFF_UP))
			वापस t;
	पूर्ण

	t = rcu_dereference(ip6n->tnls_wc[0]);
	अगर (t && (t->dev->flags & IFF_UP))
		वापस t;

	वापस शून्य;
पूर्ण

/**
 * vti6_tnl_bucket - get head of list matching given tunnel parameters
 *   @ip6n: the निजी data क्रम ip6_vti in the netns
 *   @p: parameters containing tunnel end-poपूर्णांकs
 *
 * Description:
 *   vti6_tnl_bucket() वापसs the head of the list matching the
 *   &काष्ठा in6_addr entries laddr and raddr in @p.
 *
 * Return: head of IPv6 tunnel list
 **/
अटल काष्ठा ip6_tnl __rcu **
vti6_tnl_bucket(काष्ठा vti6_net *ip6n, स्थिर काष्ठा __ip6_tnl_parm *p)
अणु
	स्थिर काष्ठा in6_addr *remote = &p->raddr;
	स्थिर काष्ठा in6_addr *local = &p->laddr;
	अचिन्हित पूर्णांक h = 0;
	पूर्णांक prio = 0;

	अगर (!ipv6_addr_any(remote) || !ipv6_addr_any(local)) अणु
		prio = 1;
		h = HASH(remote, local);
	पूर्ण
	वापस &ip6n->tnls[prio][h];
पूर्ण

अटल व्योम
vti6_tnl_link(काष्ठा vti6_net *ip6n, काष्ठा ip6_tnl *t)
अणु
	काष्ठा ip6_tnl __rcu **tp = vti6_tnl_bucket(ip6n, &t->parms);

	rcu_assign_poपूर्णांकer(t->next , rtnl_dereference(*tp));
	rcu_assign_poपूर्णांकer(*tp, t);
पूर्ण

अटल व्योम
vti6_tnl_unlink(काष्ठा vti6_net *ip6n, काष्ठा ip6_tnl *t)
अणु
	काष्ठा ip6_tnl __rcu **tp;
	काष्ठा ip6_tnl *iter;

	क्रम (tp = vti6_tnl_bucket(ip6n, &t->parms);
	     (iter = rtnl_dereference(*tp)) != शून्य;
	     tp = &iter->next) अणु
		अगर (t == iter) अणु
			rcu_assign_poपूर्णांकer(*tp, t->next);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम vti6_dev_मुक्त(काष्ठा net_device *dev)
अणु
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल पूर्णांक vti6_tnl_create2(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);
	पूर्णांक err;

	dev->rtnl_link_ops = &vti6_link_ops;
	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ out;

	म_नकल(t->parms.name, dev->name);

	vti6_tnl_link(ip6n, t);

	वापस 0;

out:
	वापस err;
पूर्ण

अटल काष्ठा ip6_tnl *vti6_tnl_create(काष्ठा net *net, काष्ठा __ip6_tnl_parm *p)
अणु
	काष्ठा net_device *dev;
	काष्ठा ip6_tnl *t;
	अक्षर name[IFNAMSIZ];
	पूर्णांक err;

	अगर (p->name[0]) अणु
		अगर (!dev_valid_name(p->name))
			जाओ failed;
		strlcpy(name, p->name, IFNAMSIZ);
	पूर्ण अन्यथा अणु
		प्र_लिखो(name, "ip6_vti%%d");
	पूर्ण

	dev = alloc_netdev(माप(*t), name, NET_NAME_UNKNOWN, vti6_dev_setup);
	अगर (!dev)
		जाओ failed;

	dev_net_set(dev, net);

	t = netdev_priv(dev);
	t->parms = *p;
	t->net = dev_net(dev);

	err = vti6_tnl_create2(dev);
	अगर (err < 0)
		जाओ failed_मुक्त;

	वापस t;

failed_मुक्त:
	मुक्त_netdev(dev);
failed:
	वापस शून्य;
पूर्ण

/**
 * vti6_locate - find or create tunnel matching given parameters
 *   @net: network namespace
 *   @p: tunnel parameters
 *   @create: != 0 अगर allowed to create new tunnel अगर no match found
 *
 * Description:
 *   vti6_locate() first tries to locate an existing tunnel
 *   based on @parms. If this is unsuccessful, but @create is set a new
 *   tunnel device is created and रेजिस्टरed क्रम use.
 *
 * Return:
 *   matching tunnel or शून्य
 **/
अटल काष्ठा ip6_tnl *vti6_locate(काष्ठा net *net, काष्ठा __ip6_tnl_parm *p,
				   पूर्णांक create)
अणु
	स्थिर काष्ठा in6_addr *remote = &p->raddr;
	स्थिर काष्ठा in6_addr *local = &p->laddr;
	काष्ठा ip6_tnl __rcu **tp;
	काष्ठा ip6_tnl *t;
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);

	क्रम (tp = vti6_tnl_bucket(ip6n, p);
	     (t = rtnl_dereference(*tp)) != शून्य;
	     tp = &t->next) अणु
		अगर (ipv6_addr_equal(local, &t->parms.laddr) &&
		    ipv6_addr_equal(remote, &t->parms.raddr)) अणु
			अगर (create)
				वापस शून्य;

			वापस t;
		पूर्ण
	पूर्ण
	अगर (!create)
		वापस शून्य;
	वापस vti6_tnl_create(net, p);
पूर्ण

/**
 * vti6_dev_uninit - tunnel device uninitializer
 *   @dev: the device to be destroyed
 *
 * Description:
 *   vti6_dev_uninit() हटाओs tunnel from its list
 **/
अटल व्योम vti6_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा vti6_net *ip6n = net_generic(t->net, vti6_net_id);

	अगर (dev == ip6n->fb_tnl_dev)
		RCU_INIT_POINTER(ip6n->tnls_wc[0], शून्य);
	अन्यथा
		vti6_tnl_unlink(ip6n, t);
	dev_put(dev);
पूर्ण

अटल पूर्णांक vti6_input_proto(काष्ठा sk_buff *skb, पूर्णांक nexthdr, __be32 spi,
			    पूर्णांक encap_type)
अणु
	काष्ठा ip6_tnl *t;
	स्थिर काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);

	rcu_पढ़ो_lock();
	t = vti6_tnl_lookup(dev_net(skb->dev), &ipv6h->saddr, &ipv6h->daddr);
	अगर (t) अणु
		अगर (t->parms.proto != IPPROTO_IPV6 && t->parms.proto != 0) अणु
			rcu_पढ़ो_unlock();
			जाओ discard;
		पूर्ण

		अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb)) अणु
			rcu_पढ़ो_unlock();
			जाओ discard;
		पूर्ण

		ipv6h = ipv6_hdr(skb);
		अगर (!ip6_tnl_rcv_ctl(t, &ipv6h->daddr, &ipv6h->saddr)) अणु
			t->dev->stats.rx_dropped++;
			rcu_पढ़ो_unlock();
			जाओ discard;
		पूर्ण

		rcu_पढ़ो_unlock();

		XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6 = t;
		XFRM_SPI_SKB_CB(skb)->family = AF_INET6;
		XFRM_SPI_SKB_CB(skb)->daddroff = दुरत्व(काष्ठा ipv6hdr, daddr);
		वापस xfrm_input(skb, nexthdr, spi, encap_type);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस -EINVAL;
discard:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक vti6_rcv(काष्ठा sk_buff *skb)
अणु
	पूर्णांक nexthdr = skb_network_header(skb)[IP6CB(skb)->nhoff];

	वापस vti6_input_proto(skb, nexthdr, 0, 0);
पूर्ण

अटल पूर्णांक vti6_rcv_cb(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	अचिन्हित लघु family;
	काष्ठा net_device *dev;
	काष्ठा xfrm_state *x;
	स्थिर काष्ठा xfrm_mode *inner_mode;
	काष्ठा ip6_tnl *t = XFRM_TUNNEL_SKB_CB(skb)->tunnel.ip6;
	u32 orig_mark = skb->mark;
	पूर्णांक ret;

	अगर (!t)
		वापस 1;

	dev = t->dev;

	अगर (err) अणु
		dev->stats.rx_errors++;
		dev->stats.rx_dropped++;

		वापस 0;
	पूर्ण

	x = xfrm_input_state(skb);

	inner_mode = &x->inner_mode;

	अगर (x->sel.family == AF_UNSPEC) अणु
		inner_mode = xfrm_ip2inner_mode(x, XFRM_MODE_SKB_CB(skb)->protocol);
		अगर (inner_mode == शून्य) अणु
			XFRM_INC_STATS(dev_net(skb->dev),
				       LINUX_MIB_XFRMINSTATEMODEERROR);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	family = inner_mode->family;

	skb->mark = be32_to_cpu(t->parms.i_key);
	ret = xfrm_policy_check(शून्य, XFRM_POLICY_IN, skb, family);
	skb->mark = orig_mark;

	अगर (!ret)
		वापस -EPERM;

	skb_scrub_packet(skb, !net_eq(t->net, dev_net(skb->dev)));
	skb->dev = dev;
	dev_sw_netstats_rx_add(dev, skb->len);

	वापस 0;
पूर्ण

/**
 * vti6_addr_conflict - compare packet addresses to tunnel's own
 *   @t: the outgoing tunnel device
 *   @hdr: IPv6 header from the incoming packet
 *
 * Description:
 *   Aव्योम trivial tunneling loop by checking that tunnel निकास-poपूर्णांक
 *   करोesn't match source of incoming packet.
 *
 * Return:
 *   1 अगर conflict,
 *   0 अन्यथा
 **/
अटल अंतरभूत bool
vti6_addr_conflict(स्थिर काष्ठा ip6_tnl *t, स्थिर काष्ठा ipv6hdr *hdr)
अणु
	वापस ipv6_addr_equal(&t->parms.raddr, &hdr->saddr);
पूर्ण

अटल bool vti6_state_check(स्थिर काष्ठा xfrm_state *x,
			     स्थिर काष्ठा in6_addr *dst,
			     स्थिर काष्ठा in6_addr *src)
अणु
	xfrm_address_t *daddr = (xfrm_address_t *)dst;
	xfrm_address_t *saddr = (xfrm_address_t *)src;

	/* अगर there is no transक्रमm then this tunnel is not functional.
	 * Or अगर the xfrm is not mode tunnel.
	 */
	अगर (!x || x->props.mode != XFRM_MODE_TUNNEL ||
	    x->props.family != AF_INET6)
		वापस false;

	अगर (ipv6_addr_any(dst))
		वापस xfrm_addr_equal(saddr, &x->props.saddr, AF_INET6);

	अगर (!xfrm_state_addr_check(x, daddr, saddr, AF_INET6))
		वापस false;

	वापस true;
पूर्ण

/**
 * vti6_xmit - send a packet
 *   @skb: the outgoing socket buffer
 *   @dev: the outgoing tunnel device
 *   @fl: the flow inक्रमmations क्रम the xfrm_lookup
 **/
अटल पूर्णांक
vti6_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev, काष्ठा flowi *fl)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &t->dev->stats;
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net_device *tdev;
	काष्ठा xfrm_state *x;
	पूर्णांक pkt_len = skb->len;
	पूर्णांक err = -1;
	पूर्णांक mtu;

	अगर (!dst) अणु
		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP): अणु
			काष्ठा rtable *rt;

			fl->u.ip4.flowi4_oअगर = dev->अगरindex;
			fl->u.ip4.flowi4_flags |= FLOWI_FLAG_ANYSRC;
			rt = __ip_route_output_key(dev_net(dev), &fl->u.ip4);
			अगर (IS_ERR(rt))
				जाओ tx_err_link_failure;
			dst = &rt->dst;
			skb_dst_set(skb, dst);
			अवरोध;
		पूर्ण
		हाल htons(ETH_P_IPV6):
			fl->u.ip6.flowi6_oअगर = dev->अगरindex;
			fl->u.ip6.flowi6_flags |= FLOWI_FLAG_ANYSRC;
			dst = ip6_route_output(dev_net(dev), शून्य, &fl->u.ip6);
			अगर (dst->error) अणु
				dst_release(dst);
				dst = शून्य;
				जाओ tx_err_link_failure;
			पूर्ण
			skb_dst_set(skb, dst);
			अवरोध;
		शेष:
			जाओ tx_err_link_failure;
		पूर्ण
	पूर्ण

	dst_hold(dst);
	dst = xfrm_lookup_route(t->net, dst, fl, शून्य, 0);
	अगर (IS_ERR(dst)) अणु
		err = PTR_ERR(dst);
		dst = शून्य;
		जाओ tx_err_link_failure;
	पूर्ण

	अगर (dst->flags & DST_XFRM_QUEUE)
		जाओ xmit;

	x = dst->xfrm;
	अगर (!vti6_state_check(x, &t->parms.raddr, &t->parms.laddr))
		जाओ tx_err_link_failure;

	अगर (!ip6_tnl_xmit_ctl(t, (स्थिर काष्ठा in6_addr *)&x->props.saddr,
			      (स्थिर काष्ठा in6_addr *)&x->id.daddr))
		जाओ tx_err_link_failure;

	tdev = dst->dev;

	अगर (tdev == dev) अणु
		stats->collisions++;
		net_warn_ratelimited("%s: Local routing loop detected!\n",
				     t->parms.name);
		जाओ tx_err_dst_release;
	पूर्ण

	mtu = dst_mtu(dst);
	अगर (skb->len > mtu) अणु
		skb_dst_update_pmtu_no_confirm(skb, mtu);

		अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			अगर (mtu < IPV6_MIN_MTU)
				mtu = IPV6_MIN_MTU;

			icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		पूर्ण अन्यथा अणु
			अगर (!(ip_hdr(skb)->frag_off & htons(IP_DF)))
				जाओ xmit;
			icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				      htonl(mtu));
		पूर्ण

		err = -EMSGSIZE;
		जाओ tx_err_dst_release;
	पूर्ण

xmit:
	skb_scrub_packet(skb, !net_eq(t->net, dev_net(dev)));
	skb_dst_set(skb, dst);
	skb->dev = skb_dst(skb)->dev;

	err = dst_output(t->net, skb->sk, skb);
	अगर (net_xmit_eval(err) == 0)
		err = pkt_len;
	iptunnel_xmit_stats(dev, err);

	वापस 0;
tx_err_link_failure:
	stats->tx_carrier_errors++;
	dst_link_failure(skb);
tx_err_dst_release:
	dst_release(dst);
	वापस err;
पूर्ण

अटल netdev_tx_t
vti6_tnl_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &t->dev->stats;
	काष्ठा flowi fl;
	पूर्णांक ret;

	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_err;

	स_रखो(&fl, 0, माप(fl));

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IPV6):
		अगर ((t->parms.proto != IPPROTO_IPV6 && t->parms.proto != 0) ||
		    vti6_addr_conflict(t, ipv6_hdr(skb)))
			जाओ tx_err;

		xfrm_decode_session(skb, &fl, AF_INET6);
		स_रखो(IP6CB(skb), 0, माप(*IP6CB(skb)));
		अवरोध;
	हाल htons(ETH_P_IP):
		xfrm_decode_session(skb, &fl, AF_INET);
		स_रखो(IPCB(skb), 0, माप(*IPCB(skb)));
		अवरोध;
	शेष:
		जाओ tx_err;
	पूर्ण

	/* override mark with tunnel output key */
	fl.flowi_mark = be32_to_cpu(t->parms.o_key);

	ret = vti6_xmit(skb, dev, &fl);
	अगर (ret < 0)
		जाओ tx_err;

	वापस NETDEV_TX_OK;

tx_err:
	stats->tx_errors++;
	stats->tx_dropped++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक vti6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		    u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	__be32 spi;
	__u32 mark;
	काष्ठा xfrm_state *x;
	काष्ठा ip6_tnl *t;
	काष्ठा ip_esp_hdr *esph;
	काष्ठा ip_auth_hdr *ah;
	काष्ठा ip_comp_hdr *ipch;
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा ipv6hdr *iph = (स्थिर काष्ठा ipv6hdr *)skb->data;
	पूर्णांक protocol = iph->nexthdr;

	t = vti6_tnl_lookup(dev_net(skb->dev), &iph->daddr, &iph->saddr);
	अगर (!t)
		वापस -1;

	mark = be32_to_cpu(t->parms.o_key);

	चयन (protocol) अणु
	हाल IPPROTO_ESP:
		esph = (काष्ठा ip_esp_hdr *)(skb->data + offset);
		spi = esph->spi;
		अवरोध;
	हाल IPPROTO_AH:
		ah = (काष्ठा ip_auth_hdr *)(skb->data + offset);
		spi = ah->spi;
		अवरोध;
	हाल IPPROTO_COMP:
		ipch = (काष्ठा ip_comp_hdr *)(skb->data + offset);
		spi = htonl(ntohs(ipch->cpi));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_REसूचीECT)
		वापस 0;

	x = xfrm_state_lookup(net, mark, (स्थिर xfrm_address_t *)&iph->daddr,
			      spi, protocol, AF_INET6);
	अगर (!x)
		वापस 0;

	अगर (type == NDISC_REसूचीECT)
		ip6_redirect(skb, net, skb->dev->अगरindex, 0,
			     sock_net_uid(net, शून्य));
	अन्यथा
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, शून्य));
	xfrm_state_put(x);

	वापस 0;
पूर्ण

अटल व्योम vti6_link_config(काष्ठा ip6_tnl *t, bool keep_mtu)
अणु
	काष्ठा net_device *dev = t->dev;
	काष्ठा __ip6_tnl_parm *p = &t->parms;
	काष्ठा net_device *tdev = शून्य;
	पूर्णांक mtu;

	स_नकल(dev->dev_addr, &p->laddr, माप(काष्ठा in6_addr));
	स_नकल(dev->broadcast, &p->raddr, माप(काष्ठा in6_addr));

	p->flags &= ~(IP6_TNL_F_CAP_XMIT | IP6_TNL_F_CAP_RCV |
		      IP6_TNL_F_CAP_PER_PACKET);
	p->flags |= ip6_tnl_get_cap(t, &p->laddr, &p->raddr);

	अगर (p->flags & IP6_TNL_F_CAP_XMIT && p->flags & IP6_TNL_F_CAP_RCV)
		dev->flags |= IFF_POINTOPOINT;
	अन्यथा
		dev->flags &= ~IFF_POINTOPOINT;

	अगर (keep_mtu && dev->mtu) अणु
		dev->mtu = clamp(dev->mtu, dev->min_mtu, dev->max_mtu);
		वापस;
	पूर्ण

	अगर (p->flags & IP6_TNL_F_CAP_XMIT) अणु
		पूर्णांक strict = (ipv6_addr_type(&p->raddr) &
			      (IPV6_ADDR_MULTICAST | IPV6_ADDR_LINKLOCAL));
		काष्ठा rt6_info *rt = rt6_lookup(t->net,
						 &p->raddr, &p->laddr,
						 p->link, शून्य, strict);

		अगर (rt)
			tdev = rt->dst.dev;
		ip6_rt_put(rt);
	पूर्ण

	अगर (!tdev && p->link)
		tdev = __dev_get_by_index(t->net, p->link);

	अगर (tdev)
		mtu = tdev->mtu - माप(काष्ठा ipv6hdr);
	अन्यथा
		mtu = ETH_DATA_LEN - LL_MAX_HEADER - माप(काष्ठा ipv6hdr);

	dev->mtu = max_t(पूर्णांक, mtu, IPV4_MIN_MTU);
पूर्ण

/**
 * vti6_tnl_change - update the tunnel parameters
 *   @t: tunnel to be changed
 *   @p: tunnel configuration parameters
 *   @keep_mtu: MTU was set from userspace, करोn't re-compute it
 *
 * Description:
 *   vti6_tnl_change() updates the tunnel parameters
 **/
अटल पूर्णांक
vti6_tnl_change(काष्ठा ip6_tnl *t, स्थिर काष्ठा __ip6_tnl_parm *p,
		bool keep_mtu)
अणु
	t->parms.laddr = p->laddr;
	t->parms.raddr = p->raddr;
	t->parms.link = p->link;
	t->parms.i_key = p->i_key;
	t->parms.o_key = p->o_key;
	t->parms.proto = p->proto;
	t->parms.fwmark = p->fwmark;
	dst_cache_reset(&t->dst_cache);
	vti6_link_config(t, keep_mtu);
	वापस 0;
पूर्ण

अटल पूर्णांक vti6_update(काष्ठा ip6_tnl *t, काष्ठा __ip6_tnl_parm *p,
		       bool keep_mtu)
अणु
	काष्ठा net *net = dev_net(t->dev);
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);
	पूर्णांक err;

	vti6_tnl_unlink(ip6n, t);
	synchronize_net();
	err = vti6_tnl_change(t, p, keep_mtu);
	vti6_tnl_link(ip6n, t);
	netdev_state_change(t->dev);
	वापस err;
पूर्ण

अटल व्योम
vti6_parm_from_user(काष्ठा __ip6_tnl_parm *p, स्थिर काष्ठा ip6_tnl_parm2 *u)
अणु
	p->laddr = u->laddr;
	p->raddr = u->raddr;
	p->link = u->link;
	p->i_key = u->i_key;
	p->o_key = u->o_key;
	p->proto = u->proto;

	स_नकल(p->name, u->name, माप(u->name));
पूर्ण

अटल व्योम
vti6_parm_to_user(काष्ठा ip6_tnl_parm2 *u, स्थिर काष्ठा __ip6_tnl_parm *p)
अणु
	u->laddr = p->laddr;
	u->raddr = p->raddr;
	u->link = p->link;
	u->i_key = p->i_key;
	u->o_key = p->o_key;
	अगर (u->i_key)
		u->i_flags |= GRE_KEY;
	अगर (u->o_key)
		u->o_flags |= GRE_KEY;
	u->proto = p->proto;

	स_नकल(u->name, p->name, माप(u->name));
पूर्ण

/**
 * vti6_ioctl - configure vti6 tunnels from userspace
 *   @dev: भव device associated with tunnel
 *   @अगरr: parameters passed from userspace
 *   @cmd: command to be perक्रमmed
 *
 * Description:
 *   vti6_ioctl() is used क्रम managing vti6 tunnels
 *   from userspace.
 *
 *   The possible commands are the following:
 *     %SIOCGETTUNNEL: get tunnel parameters क्रम device
 *     %SIOCADDTUNNEL: add tunnel matching given tunnel parameters
 *     %SIOCCHGTUNNEL: change tunnel parameters to those given
 *     %SIOCDELTUNNEL: delete tunnel
 *
 *   The fallback device "ip6_vti0", created during module
 *   initialization, can be used क्रम creating other tunnel devices.
 *
 * Return:
 *   0 on success,
 *   %-EFAULT अगर unable to copy data to or from userspace,
 *   %-EPERM अगर current process hasn't %CAP_NET_ADMIN set
 *   %-EINVAL अगर passed tunnel parameters are invalid,
 *   %-EEXIST अगर changing a tunnel's parameters would cause a conflict
 *   %-ENODEV अगर attempting to change or delete a nonexisting device
 **/
अटल पूर्णांक
vti6_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक err = 0;
	काष्ठा ip6_tnl_parm2 p;
	काष्ठा __ip6_tnl_parm p1;
	काष्ठा ip6_tnl *t = शून्य;
	काष्ठा net *net = dev_net(dev);
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);

	चयन (cmd) अणु
	हाल SIOCGETTUNNEL:
		अगर (dev == ip6n->fb_tnl_dev) अणु
			अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p))) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
			vti6_parm_from_user(&p1, &p);
			t = vti6_locate(net, &p1, 0);
		पूर्ण अन्यथा अणु
			स_रखो(&p, 0, माप(p));
		पूर्ण
		अगर (!t)
			t = netdev_priv(dev);
		vti6_parm_to_user(&p, &t->parms);
		अगर (copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &p, माप(p)))
			err = -EFAULT;
		अवरोध;
	हाल SIOCADDTUNNEL:
	हाल SIOCCHGTUNNEL:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;
		err = -EFAULT;
		अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p)))
			अवरोध;
		err = -EINVAL;
		अगर (p.proto != IPPROTO_IPV6  && p.proto != 0)
			अवरोध;
		vti6_parm_from_user(&p1, &p);
		t = vti6_locate(net, &p1, cmd == SIOCADDTUNNEL);
		अगर (dev != ip6n->fb_tnl_dev && cmd == SIOCCHGTUNNEL) अणु
			अगर (t) अणु
				अगर (t->dev != dev) अणु
					err = -EEXIST;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा
				t = netdev_priv(dev);

			err = vti6_update(t, &p1, false);
		पूर्ण
		अगर (t) अणु
			err = 0;
			vti6_parm_to_user(&p, &t->parms);
			अगर (copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &p, माप(p)))
				err = -EFAULT;

		पूर्ण अन्यथा
			err = (cmd == SIOCADDTUNNEL ? -ENOBUFS : -ENOENT);
		अवरोध;
	हाल SIOCDELTUNNEL:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			अवरोध;

		अगर (dev == ip6n->fb_tnl_dev) अणु
			err = -EFAULT;
			अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p)))
				अवरोध;
			err = -ENOENT;
			vti6_parm_from_user(&p1, &p);
			t = vti6_locate(net, &p1, 0);
			अगर (!t)
				अवरोध;
			err = -EPERM;
			अगर (t->dev == ip6n->fb_tnl_dev)
				अवरोध;
			dev = t->dev;
		पूर्ण
		err = 0;
		unरेजिस्टर_netdevice(dev);
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vti6_netdev_ops = अणु
	.nकरो_init	= vti6_dev_init,
	.nकरो_uninit	= vti6_dev_uninit,
	.nकरो_start_xmit = vti6_tnl_xmit,
	.nकरो_करो_ioctl	= vti6_ioctl,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_get_अगरlink = ip6_tnl_get_अगरlink,
पूर्ण;

/**
 * vti6_dev_setup - setup भव tunnel device
 *   @dev: भव device associated with tunnel
 *
 * Description:
 *   Initialize function poपूर्णांकers and device parameters
 **/
अटल व्योम vti6_dev_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &vti6_netdev_ops;
	dev->header_ops = &ip_tunnel_header_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = vti6_dev_मुक्त;

	dev->type = ARPHRD_TUNNEL6;
	dev->min_mtu = IPV4_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - माप(काष्ठा ipv6hdr);
	dev->flags |= IFF_NOARP;
	dev->addr_len = माप(काष्ठा in6_addr);
	netअगर_keep_dst(dev);
	/* This perm addr will be used as पूर्णांकerface identअगरier by IPv6 */
	dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_अक्रमom_addr(dev->perm_addr);
पूर्ण

/**
 * vti6_dev_init_gen - general initializer क्रम all tunnel devices
 *   @dev: भव device associated with tunnel
 **/
अटल अंतरभूत पूर्णांक vti6_dev_init_gen(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);

	t->dev = dev;
	t->net = dev_net(dev);
	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;
	dev_hold(dev);
	वापस 0;
पूर्ण

/**
 * vti6_dev_init - initializer क्रम all non fallback tunnel devices
 *   @dev: भव device associated with tunnel
 **/
अटल पूर्णांक vti6_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	पूर्णांक err = vti6_dev_init_gen(dev);

	अगर (err)
		वापस err;
	vti6_link_config(t, true);
	वापस 0;
पूर्ण

/**
 * vti6_fb_tnl_dev_init - initializer क्रम fallback tunnel device
 *   @dev: fallback device
 *
 * Return: 0
 **/
अटल पूर्णांक __net_init vti6_fb_tnl_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);

	t->parms.proto = IPPROTO_IPV6;

	rcu_assign_poपूर्णांकer(ip6n->tnls_wc[0], t);
	वापस 0;
पूर्ण

अटल पूर्णांक vti6_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			 काष्ठा netlink_ext_ack *extack)
अणु
	वापस 0;
पूर्ण

अटल व्योम vti6_netlink_parms(काष्ठा nlattr *data[],
			       काष्ठा __ip6_tnl_parm *parms)
अणु
	स_रखो(parms, 0, माप(*parms));

	अगर (!data)
		वापस;

	अगर (data[IFLA_VTI_LINK])
		parms->link = nla_get_u32(data[IFLA_VTI_LINK]);

	अगर (data[IFLA_VTI_LOCAL])
		parms->laddr = nla_get_in6_addr(data[IFLA_VTI_LOCAL]);

	अगर (data[IFLA_VTI_REMOTE])
		parms->raddr = nla_get_in6_addr(data[IFLA_VTI_REMOTE]);

	अगर (data[IFLA_VTI_IKEY])
		parms->i_key = nla_get_be32(data[IFLA_VTI_IKEY]);

	अगर (data[IFLA_VTI_OKEY])
		parms->o_key = nla_get_be32(data[IFLA_VTI_OKEY]);

	अगर (data[IFLA_VTI_FWMARK])
		parms->fwmark = nla_get_u32(data[IFLA_VTI_FWMARK]);
पूर्ण

अटल पूर्णांक vti6_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6_tnl *nt;

	nt = netdev_priv(dev);
	vti6_netlink_parms(data, &nt->parms);

	nt->parms.proto = IPPROTO_IPV6;

	अगर (vti6_locate(net, &nt->parms, 0))
		वापस -EEXIST;

	वापस vti6_tnl_create2(dev);
पूर्ण

अटल व्योम vti6_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);

	अगर (dev != ip6n->fb_tnl_dev)
		unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल पूर्णांक vti6_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			   काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6_tnl *t;
	काष्ठा __ip6_tnl_parm p;
	काष्ठा net *net = dev_net(dev);
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);

	अगर (dev == ip6n->fb_tnl_dev)
		वापस -EINVAL;

	vti6_netlink_parms(data, &p);

	t = vti6_locate(net, &p, 0);

	अगर (t) अणु
		अगर (t->dev != dev)
			वापस -EEXIST;
	पूर्ण अन्यथा
		t = netdev_priv(dev);

	वापस vti6_update(t, &p, tb && tb[IFLA_MTU]);
पूर्ण

अटल माप_प्रकार vti6_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_VTI_LINK */
		nla_total_size(4) +
		/* IFLA_VTI_LOCAL */
		nla_total_size(माप(काष्ठा in6_addr)) +
		/* IFLA_VTI_REMOTE */
		nla_total_size(माप(काष्ठा in6_addr)) +
		/* IFLA_VTI_IKEY */
		nla_total_size(4) +
		/* IFLA_VTI_OKEY */
		nla_total_size(4) +
		/* IFLA_VTI_FWMARK */
		nla_total_size(4) +
		0;
पूर्ण

अटल पूर्णांक vti6_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *tunnel = netdev_priv(dev);
	काष्ठा __ip6_tnl_parm *parm = &tunnel->parms;

	अगर (nla_put_u32(skb, IFLA_VTI_LINK, parm->link) ||
	    nla_put_in6_addr(skb, IFLA_VTI_LOCAL, &parm->laddr) ||
	    nla_put_in6_addr(skb, IFLA_VTI_REMOTE, &parm->raddr) ||
	    nla_put_be32(skb, IFLA_VTI_IKEY, parm->i_key) ||
	    nla_put_be32(skb, IFLA_VTI_OKEY, parm->o_key) ||
	    nla_put_u32(skb, IFLA_VTI_FWMARK, parm->fwmark))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy vti6_policy[IFLA_VTI_MAX + 1] = अणु
	[IFLA_VTI_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VTI_LOCAL]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_VTI_REMOTE]	= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_VTI_IKEY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VTI_OKEY]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_VTI_FWMARK]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा rtnl_link_ops vti6_link_ops __पढ़ो_mostly = अणु
	.kind		= "vti6",
	.maxtype	= IFLA_VTI_MAX,
	.policy		= vti6_policy,
	.priv_size	= माप(काष्ठा ip6_tnl),
	.setup		= vti6_dev_setup,
	.validate	= vti6_validate,
	.newlink	= vti6_newlink,
	.dellink	= vti6_dellink,
	.changelink	= vti6_changelink,
	.get_size	= vti6_get_size,
	.fill_info	= vti6_fill_info,
	.get_link_net	= ip6_tnl_get_link_net,
पूर्ण;

अटल व्योम __net_निकास vti6_destroy_tunnels(काष्ठा vti6_net *ip6n,
					    काष्ठा list_head *list)
अणु
	पूर्णांक h;
	काष्ठा ip6_tnl *t;

	क्रम (h = 0; h < IP6_VTI_HASH_SIZE; h++) अणु
		t = rtnl_dereference(ip6n->tnls_r_l[h]);
		जबतक (t) अणु
			unरेजिस्टर_netdevice_queue(t->dev, list);
			t = rtnl_dereference(t->next);
		पूर्ण
	पूर्ण

	t = rtnl_dereference(ip6n->tnls_wc[0]);
	अगर (t)
		unरेजिस्टर_netdevice_queue(t->dev, list);
पूर्ण

अटल पूर्णांक __net_init vti6_init_net(काष्ठा net *net)
अणु
	काष्ठा vti6_net *ip6n = net_generic(net, vti6_net_id);
	काष्ठा ip6_tnl *t = शून्य;
	पूर्णांक err;

	ip6n->tnls[0] = ip6n->tnls_wc;
	ip6n->tnls[1] = ip6n->tnls_r_l;

	अगर (!net_has_fallback_tunnels(net))
		वापस 0;
	err = -ENOMEM;
	ip6n->fb_tnl_dev = alloc_netdev(माप(काष्ठा ip6_tnl), "ip6_vti0",
					NET_NAME_UNKNOWN, vti6_dev_setup);

	अगर (!ip6n->fb_tnl_dev)
		जाओ err_alloc_dev;
	dev_net_set(ip6n->fb_tnl_dev, net);
	ip6n->fb_tnl_dev->rtnl_link_ops = &vti6_link_ops;

	err = vti6_fb_tnl_dev_init(ip6n->fb_tnl_dev);
	अगर (err < 0)
		जाओ err_रेजिस्टर;

	err = रेजिस्टर_netdev(ip6n->fb_tnl_dev);
	अगर (err < 0)
		जाओ err_रेजिस्टर;

	t = netdev_priv(ip6n->fb_tnl_dev);

	म_नकल(t->parms.name, ip6n->fb_tnl_dev->name);
	वापस 0;

err_रेजिस्टर:
	मुक्त_netdev(ip6n->fb_tnl_dev);
err_alloc_dev:
	वापस err;
पूर्ण

अटल व्योम __net_निकास vti6_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	काष्ठा vti6_net *ip6n;
	काष्ठा net *net;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		ip6n = net_generic(net, vti6_net_id);
		vti6_destroy_tunnels(ip6n, &list);
	पूर्ण
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations vti6_net_ops = अणु
	.init = vti6_init_net,
	.निकास_batch = vti6_निकास_batch_net,
	.id   = &vti6_net_id,
	.size = माप(काष्ठा vti6_net),
पूर्ण;

अटल काष्ठा xfrm6_protocol vti_esp6_protocol __पढ़ो_mostly = अणु
	.handler	=	vti6_rcv,
	.input_handler	=	vti6_input_proto,
	.cb_handler	=	vti6_rcv_cb,
	.err_handler	=	vti6_err,
	.priority	=	100,
पूर्ण;

अटल काष्ठा xfrm6_protocol vti_ah6_protocol __पढ़ो_mostly = अणु
	.handler	=	vti6_rcv,
	.input_handler	=	vti6_input_proto,
	.cb_handler	=	vti6_rcv_cb,
	.err_handler	=	vti6_err,
	.priority	=	100,
पूर्ण;

अटल काष्ठा xfrm6_protocol vti_ipcomp6_protocol __पढ़ो_mostly = अणु
	.handler	=	vti6_rcv,
	.input_handler	=	vti6_input_proto,
	.cb_handler	=	vti6_rcv_cb,
	.err_handler	=	vti6_err,
	.priority	=	100,
पूर्ण;

#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
अटल पूर्णांक vti6_rcv_tunnel(काष्ठा sk_buff *skb)
अणु
	स्थिर xfrm_address_t *saddr;
	__be32 spi;

	saddr = (स्थिर xfrm_address_t *)&ipv6_hdr(skb)->saddr;
	spi = xfrm6_tunnel_spi_lookup(dev_net(skb->dev), saddr);

	वापस vti6_input_proto(skb, IPPROTO_IPV6, spi, 0);
पूर्ण

अटल काष्ठा xfrm6_tunnel vti_ipv6_handler __पढ़ो_mostly = अणु
	.handler	=	vti6_rcv_tunnel,
	.cb_handler	=	vti6_rcv_cb,
	.err_handler	=	vti6_err,
	.priority	=	0,
पूर्ण;

अटल काष्ठा xfrm6_tunnel vti_ip6ip_handler __पढ़ो_mostly = अणु
	.handler	=	vti6_rcv_tunnel,
	.cb_handler	=	vti6_rcv_cb,
	.err_handler	=	vti6_err,
	.priority	=	0,
पूर्ण;
#पूर्ण_अगर

/**
 * vti6_tunnel_init - रेजिस्टर protocol and reserve needed resources
 *
 * Return: 0 on success
 **/
अटल पूर्णांक __init vti6_tunnel_init(व्योम)
अणु
	स्थिर अक्षर *msg;
	पूर्णांक err;

	msg = "tunnel device";
	err = रेजिस्टर_pernet_device(&vti6_net_ops);
	अगर (err < 0)
		जाओ pernet_dev_failed;

	msg = "tunnel protocols";
	err = xfrm6_protocol_रेजिस्टर(&vti_esp6_protocol, IPPROTO_ESP);
	अगर (err < 0)
		जाओ xfrm_proto_esp_failed;
	err = xfrm6_protocol_रेजिस्टर(&vti_ah6_protocol, IPPROTO_AH);
	अगर (err < 0)
		जाओ xfrm_proto_ah_failed;
	err = xfrm6_protocol_रेजिस्टर(&vti_ipcomp6_protocol, IPPROTO_COMP);
	अगर (err < 0)
		जाओ xfrm_proto_comp_failed;
#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
	msg = "ipv6 tunnel";
	err = xfrm6_tunnel_रेजिस्टर(&vti_ipv6_handler, AF_INET6);
	अगर (err < 0)
		जाओ vti_tunnel_ipv6_failed;
	err = xfrm6_tunnel_रेजिस्टर(&vti_ip6ip_handler, AF_INET);
	अगर (err < 0)
		जाओ vti_tunnel_ip6ip_failed;
#पूर्ण_अगर

	msg = "netlink interface";
	err = rtnl_link_रेजिस्टर(&vti6_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

	वापस 0;

rtnl_link_failed:
#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
	err = xfrm6_tunnel_deरेजिस्टर(&vti_ip6ip_handler, AF_INET);
vti_tunnel_ip6ip_failed:
	err = xfrm6_tunnel_deरेजिस्टर(&vti_ipv6_handler, AF_INET6);
vti_tunnel_ipv6_failed:
#पूर्ण_अगर
	xfrm6_protocol_deरेजिस्टर(&vti_ipcomp6_protocol, IPPROTO_COMP);
xfrm_proto_comp_failed:
	xfrm6_protocol_deरेजिस्टर(&vti_ah6_protocol, IPPROTO_AH);
xfrm_proto_ah_failed:
	xfrm6_protocol_deरेजिस्टर(&vti_esp6_protocol, IPPROTO_ESP);
xfrm_proto_esp_failed:
	unरेजिस्टर_pernet_device(&vti6_net_ops);
pernet_dev_failed:
	pr_err("vti6 init: failed to register %s\n", msg);
	वापस err;
पूर्ण

/**
 * vti6_tunnel_cleanup - मुक्त resources and unरेजिस्टर protocol
 **/
अटल व्योम __निकास vti6_tunnel_cleanup(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&vti6_link_ops);
#अगर IS_REACHABLE(CONFIG_INET6_XFRM_TUNNEL)
	xfrm6_tunnel_deरेजिस्टर(&vti_ip6ip_handler, AF_INET);
	xfrm6_tunnel_deरेजिस्टर(&vti_ipv6_handler, AF_INET6);
#पूर्ण_अगर
	xfrm6_protocol_deरेजिस्टर(&vti_ipcomp6_protocol, IPPROTO_COMP);
	xfrm6_protocol_deरेजिस्टर(&vti_ah6_protocol, IPPROTO_AH);
	xfrm6_protocol_deरेजिस्टर(&vti_esp6_protocol, IPPROTO_ESP);
	unरेजिस्टर_pernet_device(&vti6_net_ops);
पूर्ण

module_init(vti6_tunnel_init);
module_निकास(vti6_tunnel_cleanup);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("vti6");
MODULE_ALIAS_NETDEV("ip6_vti0");
MODULE_AUTHOR("Steffen Klassert");
MODULE_DESCRIPTION("IPv6 virtual tunnel interface");
