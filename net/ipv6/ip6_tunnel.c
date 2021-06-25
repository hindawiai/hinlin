<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	IPv6 tunneling device
 *	Linux INET6 implementation
 *
 *	Authors:
 *	Ville Nuorvala		<vnuorval@tcs.hut.fi>
 *	Yasuyuki Kozakai	<kozakai@linux-ipv6.org>
 *
 *      Based on:
 *      linux/net/ipv6/sit.c and linux/net/ipv4/ipip.c
 *
 *      RFC 2473
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

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
#समावेश <linux/etherdevice.h>

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
#समावेश <net/dsfield.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/dst_metadata.h>

MODULE_AUTHOR("Ville Nuorvala");
MODULE_DESCRIPTION("IPv6 tunneling device");
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK("ip6tnl");
MODULE_ALIAS_NETDEV("ip6tnl0");

#घोषणा IP6_TUNNEL_HASH_SIZE_SHIFT  5
#घोषणा IP6_TUNNEL_HASH_SIZE (1 << IP6_TUNNEL_HASH_SIZE_SHIFT)

अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

अटल u32 HASH(स्थिर काष्ठा in6_addr *addr1, स्थिर काष्ठा in6_addr *addr2)
अणु
	u32 hash = ipv6_addr_hash(addr1) ^ ipv6_addr_hash(addr2);

	वापस hash_32(hash, IP6_TUNNEL_HASH_SIZE_SHIFT);
पूर्ण

अटल पूर्णांक ip6_tnl_dev_init(काष्ठा net_device *dev);
अटल व्योम ip6_tnl_dev_setup(काष्ठा net_device *dev);
अटल काष्ठा rtnl_link_ops ip6_link_ops __पढ़ो_mostly;

अटल अचिन्हित पूर्णांक ip6_tnl_net_id __पढ़ो_mostly;
काष्ठा ip6_tnl_net अणु
	/* the IPv6 tunnel fallback device */
	काष्ठा net_device *fb_tnl_dev;
	/* lists क्रम storing tunnels in use */
	काष्ठा ip6_tnl __rcu *tnls_r_l[IP6_TUNNEL_HASH_SIZE];
	काष्ठा ip6_tnl __rcu *tnls_wc[1];
	काष्ठा ip6_tnl __rcu **tnls[2];
	काष्ठा ip6_tnl __rcu *collect_md_tun;
पूर्ण;

अटल अंतरभूत पूर्णांक ip6_tnl_mpls_supported(व्योम)
अणु
	वापस IS_ENABLED(CONFIG_MPLS);
पूर्ण

#घोषणा क्रम_each_ip6_tunnel_rcu(start) \
	क्रम (t = rcu_dereference(start); t; t = rcu_dereference(t->next))

/**
 * ip6_tnl_lookup - fetch tunnel matching the end-poपूर्णांक addresses
 *   @net: network namespace
 *   @link: अगरindex of underlying पूर्णांकerface
 *   @remote: the address of the tunnel निकास-poपूर्णांक
 *   @local: the address of the tunnel entry-poपूर्णांक
 *
 * Return:
 *   tunnel matching given end-poपूर्णांकs अगर found,
 *   अन्यथा fallback tunnel अगर its device is up,
 *   अन्यथा %शून्य
 **/

अटल काष्ठा ip6_tnl *
ip6_tnl_lookup(काष्ठा net *net, पूर्णांक link,
	       स्थिर काष्ठा in6_addr *remote, स्थिर काष्ठा in6_addr *local)
अणु
	अचिन्हित पूर्णांक hash = HASH(remote, local);
	काष्ठा ip6_tnl *t, *cand = शून्य;
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);
	काष्ठा in6_addr any;

	क्रम_each_ip6_tunnel_rcu(ip6n->tnls_r_l[hash]) अणु
		अगर (!ipv6_addr_equal(local, &t->parms.laddr) ||
		    !ipv6_addr_equal(remote, &t->parms.raddr) ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (link == t->parms.link)
			वापस t;
		अन्यथा
			cand = t;
	पूर्ण

	स_रखो(&any, 0, माप(any));
	hash = HASH(&any, local);
	क्रम_each_ip6_tunnel_rcu(ip6n->tnls_r_l[hash]) अणु
		अगर (!ipv6_addr_equal(local, &t->parms.laddr) ||
		    !ipv6_addr_any(&t->parms.raddr) ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (link == t->parms.link)
			वापस t;
		अन्यथा अगर (!cand)
			cand = t;
	पूर्ण

	hash = HASH(remote, &any);
	क्रम_each_ip6_tunnel_rcu(ip6n->tnls_r_l[hash]) अणु
		अगर (!ipv6_addr_equal(remote, &t->parms.raddr) ||
		    !ipv6_addr_any(&t->parms.laddr) ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (link == t->parms.link)
			वापस t;
		अन्यथा अगर (!cand)
			cand = t;
	पूर्ण

	अगर (cand)
		वापस cand;

	t = rcu_dereference(ip6n->collect_md_tun);
	अगर (t && t->dev->flags & IFF_UP)
		वापस t;

	t = rcu_dereference(ip6n->tnls_wc[0]);
	अगर (t && (t->dev->flags & IFF_UP))
		वापस t;

	वापस शून्य;
पूर्ण

/**
 * ip6_tnl_bucket - get head of list matching given tunnel parameters
 *   @ip6n: the निजी data क्रम ip6_vti in the netns
 *   @p: parameters containing tunnel end-poपूर्णांकs
 *
 * Description:
 *   ip6_tnl_bucket() वापसs the head of the list matching the
 *   &काष्ठा in6_addr entries laddr and raddr in @p.
 *
 * Return: head of IPv6 tunnel list
 **/

अटल काष्ठा ip6_tnl __rcu **
ip6_tnl_bucket(काष्ठा ip6_tnl_net *ip6n, स्थिर काष्ठा __ip6_tnl_parm *p)
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

/**
 * ip6_tnl_link - add tunnel to hash table
 *   @ip6n: the निजी data क्रम ip6_vti in the netns
 *   @t: tunnel to be added
 **/

अटल व्योम
ip6_tnl_link(काष्ठा ip6_tnl_net *ip6n, काष्ठा ip6_tnl *t)
अणु
	काष्ठा ip6_tnl __rcu **tp = ip6_tnl_bucket(ip6n, &t->parms);

	अगर (t->parms.collect_md)
		rcu_assign_poपूर्णांकer(ip6n->collect_md_tun, t);
	rcu_assign_poपूर्णांकer(t->next , rtnl_dereference(*tp));
	rcu_assign_poपूर्णांकer(*tp, t);
पूर्ण

/**
 * ip6_tnl_unlink - हटाओ tunnel from hash table
 *   @ip6n: the निजी data क्रम ip6_vti in the netns
 *   @t: tunnel to be हटाओd
 **/

अटल व्योम
ip6_tnl_unlink(काष्ठा ip6_tnl_net *ip6n, काष्ठा ip6_tnl *t)
अणु
	काष्ठा ip6_tnl __rcu **tp;
	काष्ठा ip6_tnl *iter;

	अगर (t->parms.collect_md)
		rcu_assign_poपूर्णांकer(ip6n->collect_md_tun, शून्य);

	क्रम (tp = ip6_tnl_bucket(ip6n, &t->parms);
	     (iter = rtnl_dereference(*tp)) != शून्य;
	     tp = &iter->next) अणु
		अगर (t == iter) अणु
			rcu_assign_poपूर्णांकer(*tp, t->next);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ip6_dev_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);

	gro_cells_destroy(&t->gro_cells);
	dst_cache_destroy(&t->dst_cache);
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल पूर्णांक ip6_tnl_create2(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);
	पूर्णांक err;

	t = netdev_priv(dev);

	dev->rtnl_link_ops = &ip6_link_ops;
	err = रेजिस्टर_netdevice(dev);
	अगर (err < 0)
		जाओ out;

	म_नकल(t->parms.name, dev->name);

	ip6_tnl_link(ip6n, t);
	वापस 0;

out:
	वापस err;
पूर्ण

/**
 * ip6_tnl_create - create a new tunnel
 *   @net: network namespace
 *   @p: tunnel parameters
 *
 * Description:
 *   Create tunnel matching given parameters.
 *
 * Return:
 *   created tunnel or error poपूर्णांकer
 **/

अटल काष्ठा ip6_tnl *ip6_tnl_create(काष्ठा net *net, काष्ठा __ip6_tnl_parm *p)
अणु
	काष्ठा net_device *dev;
	काष्ठा ip6_tnl *t;
	अक्षर name[IFNAMSIZ];
	पूर्णांक err = -E2BIG;

	अगर (p->name[0]) अणु
		अगर (!dev_valid_name(p->name))
			जाओ failed;
		strlcpy(name, p->name, IFNAMSIZ);
	पूर्ण अन्यथा अणु
		प्र_लिखो(name, "ip6tnl%%d");
	पूर्ण
	err = -ENOMEM;
	dev = alloc_netdev(माप(*t), name, NET_NAME_UNKNOWN,
			   ip6_tnl_dev_setup);
	अगर (!dev)
		जाओ failed;

	dev_net_set(dev, net);

	t = netdev_priv(dev);
	t->parms = *p;
	t->net = dev_net(dev);
	err = ip6_tnl_create2(dev);
	अगर (err < 0)
		जाओ failed_मुक्त;

	वापस t;

failed_मुक्त:
	मुक्त_netdev(dev);
failed:
	वापस ERR_PTR(err);
पूर्ण

/**
 * ip6_tnl_locate - find or create tunnel matching given parameters
 *   @net: network namespace
 *   @p: tunnel parameters
 *   @create: != 0 अगर allowed to create new tunnel अगर no match found
 *
 * Description:
 *   ip6_tnl_locate() first tries to locate an existing tunnel
 *   based on @parms. If this is unsuccessful, but @create is set a new
 *   tunnel device is created and रेजिस्टरed क्रम use.
 *
 * Return:
 *   matching tunnel or error poपूर्णांकer
 **/

अटल काष्ठा ip6_tnl *ip6_tnl_locate(काष्ठा net *net,
		काष्ठा __ip6_tnl_parm *p, पूर्णांक create)
अणु
	स्थिर काष्ठा in6_addr *remote = &p->raddr;
	स्थिर काष्ठा in6_addr *local = &p->laddr;
	काष्ठा ip6_tnl __rcu **tp;
	काष्ठा ip6_tnl *t;
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	क्रम (tp = ip6_tnl_bucket(ip6n, p);
	     (t = rtnl_dereference(*tp)) != शून्य;
	     tp = &t->next) अणु
		अगर (ipv6_addr_equal(local, &t->parms.laddr) &&
		    ipv6_addr_equal(remote, &t->parms.raddr) &&
		    p->link == t->parms.link) अणु
			अगर (create)
				वापस ERR_PTR(-EEXIST);

			वापस t;
		पूर्ण
	पूर्ण
	अगर (!create)
		वापस ERR_PTR(-ENODEV);
	वापस ip6_tnl_create(net, p);
पूर्ण

/**
 * ip6_tnl_dev_uninit - tunnel device uninitializer
 *   @dev: the device to be destroyed
 *
 * Description:
 *   ip6_tnl_dev_uninit() हटाओs tunnel from its list
 **/

अटल व्योम
ip6_tnl_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = t->net;
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	अगर (dev == ip6n->fb_tnl_dev)
		RCU_INIT_POINTER(ip6n->tnls_wc[0], शून्य);
	अन्यथा
		ip6_tnl_unlink(ip6n, t);
	dst_cache_reset(&t->dst_cache);
	dev_put(dev);
पूर्ण

/**
 * ip6_tnl_parse_tlv_enc_lim - handle encapsulation limit option
 *   @skb: received socket buffer
 *   @raw: the ICMPv6 error message data
 *
 * Return:
 *   0 अगर none was found,
 *   अन्यथा index to encapsulation limit
 **/

__u16 ip6_tnl_parse_tlv_enc_lim(काष्ठा sk_buff *skb, __u8 *raw)
अणु
	स्थिर काष्ठा ipv6hdr *ipv6h = (स्थिर काष्ठा ipv6hdr *)raw;
	अचिन्हित पूर्णांक nhoff = raw - skb->data;
	अचिन्हित पूर्णांक off = nhoff + माप(*ipv6h);
	u8 next, nexthdr = ipv6h->nexthdr;

	जबतक (ipv6_ext_hdr(nexthdr) && nexthdr != NEXTHDR_NONE) अणु
		काष्ठा ipv6_opt_hdr *hdr;
		u16 optlen;

		अगर (!pskb_may_pull(skb, off + माप(*hdr)))
			अवरोध;

		hdr = (काष्ठा ipv6_opt_hdr *)(skb->data + off);
		अगर (nexthdr == NEXTHDR_FRAGMENT) अणु
			काष्ठा frag_hdr *frag_hdr = (काष्ठा frag_hdr *) hdr;
			अगर (frag_hdr->frag_off)
				अवरोध;
			optlen = 8;
		पूर्ण अन्यथा अगर (nexthdr == NEXTHDR_AUTH) अणु
			optlen = ipv6_authlen(hdr);
		पूर्ण अन्यथा अणु
			optlen = ipv6_optlen(hdr);
		पूर्ण
		/* cache hdr->nexthdr, since pskb_may_pull() might
		 * invalidate hdr
		 */
		next = hdr->nexthdr;
		अगर (nexthdr == NEXTHDR_DEST) अणु
			u16 i = 2;

			/* Remember : hdr is no दीर्घer valid at this poपूर्णांक. */
			अगर (!pskb_may_pull(skb, off + optlen))
				अवरोध;

			जबतक (1) अणु
				काष्ठा ipv6_tlv_tnl_enc_lim *tel;

				/* No more room क्रम encapsulation limit */
				अगर (i + माप(*tel) > optlen)
					अवरोध;

				tel = (काष्ठा ipv6_tlv_tnl_enc_lim *)(skb->data + off + i);
				/* वापस index of option अगर found and valid */
				अगर (tel->type == IPV6_TLV_TNL_ENCAP_LIMIT &&
				    tel->length == 1)
					वापस i + off - nhoff;
				/* अन्यथा jump to next option */
				अगर (tel->type)
					i += tel->length + 2;
				अन्यथा
					i++;
			पूर्ण
		पूर्ण
		nexthdr = next;
		off += optlen;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_parse_tlv_enc_lim);

/* ip6_tnl_err() should handle errors in the tunnel according to the
 * specअगरications in RFC 2473.
 */
अटल पूर्णांक
ip6_tnl_err(काष्ठा sk_buff *skb, __u8 ipproto, काष्ठा inet6_skb_parm *opt,
	    u8 *type, u8 *code, पूर्णांक *msg, __u32 *info, पूर्णांक offset)
अणु
	स्थिर काष्ठा ipv6hdr *ipv6h = (स्थिर काष्ठा ipv6hdr *)skb->data;
	काष्ठा net *net = dev_net(skb->dev);
	u8 rel_type = ICMPV6_DEST_UNREACH;
	u8 rel_code = ICMPV6_ADDR_UNREACH;
	__u32 rel_info = 0;
	काष्ठा ip6_tnl *t;
	पूर्णांक err = -ENOENT;
	पूर्णांक rel_msg = 0;
	u8 tproto;
	__u16 len;

	/* If the packet करोesn't contain the original IPv6 header we are
	   in trouble since we might need the source address क्रम further
	   processing of the error. */

	rcu_पढ़ो_lock();
	t = ip6_tnl_lookup(dev_net(skb->dev), skb->dev->अगरindex, &ipv6h->daddr, &ipv6h->saddr);
	अगर (!t)
		जाओ out;

	tproto = READ_ONCE(t->parms.proto);
	अगर (tproto != ipproto && tproto != 0)
		जाओ out;

	err = 0;

	चयन (*type) अणु
	हाल ICMPV6_DEST_UNREACH:
		net_dbg_ratelimited("%s: Path to destination invalid or inactive!\n",
				    t->parms.name);
		rel_msg = 1;
		अवरोध;
	हाल ICMPV6_TIME_EXCEED:
		अगर ((*code) == ICMPV6_EXC_HOPLIMIT) अणु
			net_dbg_ratelimited("%s: Too small hop limit or routing loop in tunnel!\n",
					    t->parms.name);
			rel_msg = 1;
		पूर्ण
		अवरोध;
	हाल ICMPV6_PARAMPROB: अणु
		काष्ठा ipv6_tlv_tnl_enc_lim *tel;
		__u32 teli;

		teli = 0;
		अगर ((*code) == ICMPV6_HDR_FIELD)
			teli = ip6_tnl_parse_tlv_enc_lim(skb, skb->data);

		अगर (teli && teli == *info - 2) अणु
			tel = (काष्ठा ipv6_tlv_tnl_enc_lim *) &skb->data[teli];
			अगर (tel->encap_limit == 0) अणु
				net_dbg_ratelimited("%s: Too small encapsulation limit or routing loop in tunnel!\n",
						    t->parms.name);
				rel_msg = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			net_dbg_ratelimited("%s: Recipient unable to parse tunneled packet!\n",
					    t->parms.name);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ICMPV6_PKT_TOOBIG: अणु
		__u32 mtu;

		ip6_update_pmtu(skb, net, htonl(*info), 0, 0,
				sock_net_uid(net, शून्य));
		mtu = *info - offset;
		अगर (mtu < IPV6_MIN_MTU)
			mtu = IPV6_MIN_MTU;
		len = माप(*ipv6h) + ntohs(ipv6h->payload_len);
		अगर (len > mtu) अणु
			rel_type = ICMPV6_PKT_TOOBIG;
			rel_code = 0;
			rel_info = mtu;
			rel_msg = 1;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल NDISC_REसूचीECT:
		ip6_redirect(skb, net, skb->dev->अगरindex, 0,
			     sock_net_uid(net, शून्य));
		अवरोध;
	पूर्ण

	*type = rel_type;
	*code = rel_code;
	*info = rel_info;
	*msg = rel_msg;

out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक
ip4ip6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
	   u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	__u32 rel_info = ntohl(info);
	स्थिर काष्ठा iphdr *eiph;
	काष्ठा sk_buff *skb2;
	पूर्णांक err, rel_msg = 0;
	u8 rel_type = type;
	u8 rel_code = code;
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4;

	err = ip6_tnl_err(skb, IPPROTO_IPIP, opt, &rel_type, &rel_code,
			  &rel_msg, &rel_info, offset);
	अगर (err < 0)
		वापस err;

	अगर (rel_msg == 0)
		वापस 0;

	चयन (rel_type) अणु
	हाल ICMPV6_DEST_UNREACH:
		अगर (rel_code != ICMPV6_ADDR_UNREACH)
			वापस 0;
		rel_type = ICMP_DEST_UNREACH;
		rel_code = ICMP_HOST_UNREACH;
		अवरोध;
	हाल ICMPV6_PKT_TOOBIG:
		अगर (rel_code != 0)
			वापस 0;
		rel_type = ICMP_DEST_UNREACH;
		rel_code = ICMP_FRAG_NEEDED;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (!pskb_may_pull(skb, offset + माप(काष्ठा iphdr)))
		वापस 0;

	skb2 = skb_clone(skb, GFP_ATOMIC);
	अगर (!skb2)
		वापस 0;

	skb_dst_drop(skb2);

	skb_pull(skb2, offset);
	skb_reset_network_header(skb2);
	eiph = ip_hdr(skb2);

	/* Try to guess incoming पूर्णांकerface */
	rt = ip_route_output_ports(dev_net(skb->dev), &fl4, शून्य, eiph->saddr,
				   0, 0, 0, IPPROTO_IPIP, RT_TOS(eiph->tos), 0);
	अगर (IS_ERR(rt))
		जाओ out;

	skb2->dev = rt->dst.dev;
	ip_rt_put(rt);

	/* route "incoming" packet */
	अगर (rt->rt_flags & RTCF_LOCAL) अणु
		rt = ip_route_output_ports(dev_net(skb->dev), &fl4, शून्य,
					   eiph->daddr, eiph->saddr, 0, 0,
					   IPPROTO_IPIP, RT_TOS(eiph->tos), 0);
		अगर (IS_ERR(rt) || rt->dst.dev->type != ARPHRD_TUNNEL6) अणु
			अगर (!IS_ERR(rt))
				ip_rt_put(rt);
			जाओ out;
		पूर्ण
		skb_dst_set(skb2, &rt->dst);
	पूर्ण अन्यथा अणु
		अगर (ip_route_input(skb2, eiph->daddr, eiph->saddr, eiph->tos,
				   skb2->dev) ||
		    skb_dst(skb2)->dev->type != ARPHRD_TUNNEL6)
			जाओ out;
	पूर्ण

	/* change mtu on this route */
	अगर (rel_type == ICMP_DEST_UNREACH && rel_code == ICMP_FRAG_NEEDED) अणु
		अगर (rel_info > dst_mtu(skb_dst(skb2)))
			जाओ out;

		skb_dst_update_pmtu_no_confirm(skb2, rel_info);
	पूर्ण

	icmp_send(skb2, rel_type, rel_code, htonl(rel_info));

out:
	kमुक्त_skb(skb2);
	वापस 0;
पूर्ण

अटल पूर्णांक
ip6ip6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
	   u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	__u32 rel_info = ntohl(info);
	पूर्णांक err, rel_msg = 0;
	u8 rel_type = type;
	u8 rel_code = code;

	err = ip6_tnl_err(skb, IPPROTO_IPV6, opt, &rel_type, &rel_code,
			  &rel_msg, &rel_info, offset);
	अगर (err < 0)
		वापस err;

	अगर (rel_msg && pskb_may_pull(skb, offset + माप(काष्ठा ipv6hdr))) अणु
		काष्ठा rt6_info *rt;
		काष्ठा sk_buff *skb2 = skb_clone(skb, GFP_ATOMIC);

		अगर (!skb2)
			वापस 0;

		skb_dst_drop(skb2);
		skb_pull(skb2, offset);
		skb_reset_network_header(skb2);

		/* Try to guess incoming पूर्णांकerface */
		rt = rt6_lookup(dev_net(skb->dev), &ipv6_hdr(skb2)->saddr,
				शून्य, 0, skb2, 0);

		अगर (rt && rt->dst.dev)
			skb2->dev = rt->dst.dev;

		icmpv6_send(skb2, rel_type, rel_code, rel_info);

		ip6_rt_put(rt);

		kमुक्त_skb(skb2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mplsip6_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
	    u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	__u32 rel_info = ntohl(info);
	पूर्णांक err, rel_msg = 0;
	u8 rel_type = type;
	u8 rel_code = code;

	err = ip6_tnl_err(skb, IPPROTO_MPLS, opt, &rel_type, &rel_code,
			  &rel_msg, &rel_info, offset);
	वापस err;
पूर्ण

अटल पूर्णांक ip4ip6_dscp_ecn_decapsulate(स्थिर काष्ठा ip6_tnl *t,
				       स्थिर काष्ठा ipv6hdr *ipv6h,
				       काष्ठा sk_buff *skb)
अणु
	__u8 dsfield = ipv6_get_dsfield(ipv6h) & ~INET_ECN_MASK;

	अगर (t->parms.flags & IP6_TNL_F_RCV_DSCP_COPY)
		ipv4_change_dsfield(ip_hdr(skb), INET_ECN_MASK, dsfield);

	वापस IP6_ECN_decapsulate(ipv6h, skb);
पूर्ण

अटल पूर्णांक ip6ip6_dscp_ecn_decapsulate(स्थिर काष्ठा ip6_tnl *t,
				       स्थिर काष्ठा ipv6hdr *ipv6h,
				       काष्ठा sk_buff *skb)
अणु
	अगर (t->parms.flags & IP6_TNL_F_RCV_DSCP_COPY)
		ipv6_copy_dscp(ipv6_get_dsfield(ipv6h), ipv6_hdr(skb));

	वापस IP6_ECN_decapsulate(ipv6h, skb);
पूर्ण

अटल अंतरभूत पूर्णांक mplsip6_dscp_ecn_decapsulate(स्थिर काष्ठा ip6_tnl *t,
					       स्थिर काष्ठा ipv6hdr *ipv6h,
					       काष्ठा sk_buff *skb)
अणु
	/* ECN is not supported in AF_MPLS */
	वापस 0;
पूर्ण

__u32 ip6_tnl_get_cap(काष्ठा ip6_tnl *t,
			     स्थिर काष्ठा in6_addr *laddr,
			     स्थिर काष्ठा in6_addr *raddr)
अणु
	काष्ठा __ip6_tnl_parm *p = &t->parms;
	पूर्णांक ltype = ipv6_addr_type(laddr);
	पूर्णांक rtype = ipv6_addr_type(raddr);
	__u32 flags = 0;

	अगर (ltype == IPV6_ADDR_ANY || rtype == IPV6_ADDR_ANY) अणु
		flags = IP6_TNL_F_CAP_PER_PACKET;
	पूर्ण अन्यथा अगर (ltype & (IPV6_ADDR_UNICAST|IPV6_ADDR_MULTICAST) &&
		   rtype & (IPV6_ADDR_UNICAST|IPV6_ADDR_MULTICAST) &&
		   !((ltype|rtype) & IPV6_ADDR_LOOPBACK) &&
		   (!((ltype|rtype) & IPV6_ADDR_LINKLOCAL) || p->link)) अणु
		अगर (ltype&IPV6_ADDR_UNICAST)
			flags |= IP6_TNL_F_CAP_XMIT;
		अगर (rtype&IPV6_ADDR_UNICAST)
			flags |= IP6_TNL_F_CAP_RCV;
	पूर्ण
	वापस flags;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_get_cap);

/* called with rcu_पढ़ो_lock() */
पूर्णांक ip6_tnl_rcv_ctl(काष्ठा ip6_tnl *t,
				  स्थिर काष्ठा in6_addr *laddr,
				  स्थिर काष्ठा in6_addr *raddr)
अणु
	काष्ठा __ip6_tnl_parm *p = &t->parms;
	पूर्णांक ret = 0;
	काष्ठा net *net = t->net;

	अगर ((p->flags & IP6_TNL_F_CAP_RCV) ||
	    ((p->flags & IP6_TNL_F_CAP_PER_PACKET) &&
	     (ip6_tnl_get_cap(t, laddr, raddr) & IP6_TNL_F_CAP_RCV))) अणु
		काष्ठा net_device *ldev = शून्य;

		अगर (p->link)
			ldev = dev_get_by_index_rcu(net, p->link);

		अगर ((ipv6_addr_is_multicast(laddr) ||
		     likely(ipv6_chk_addr_and_flags(net, laddr, ldev, false,
						    0, IFA_F_TENTATIVE))) &&
		    ((p->flags & IP6_TNL_F_ALLOW_LOCAL_REMOTE) ||
		     likely(!ipv6_chk_addr_and_flags(net, raddr, ldev, true,
						     0, IFA_F_TENTATIVE))))
			ret = 1;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_tnl_rcv_ctl);

अटल पूर्णांक __ip6_tnl_rcv(काष्ठा ip6_tnl *tunnel, काष्ठा sk_buff *skb,
			 स्थिर काष्ठा tnl_ptk_info *tpi,
			 काष्ठा metadata_dst *tun_dst,
			 पूर्णांक (*dscp_ecn_decapsulate)(स्थिर काष्ठा ip6_tnl *t,
						स्थिर काष्ठा ipv6hdr *ipv6h,
						काष्ठा sk_buff *skb),
			 bool log_ecn_err)
अणु
	काष्ठा pcpu_sw_netstats *tstats;
	स्थिर काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	पूर्णांक err;

	अगर ((!(tpi->flags & TUNNEL_CSUM) &&
	     (tunnel->parms.i_flags & TUNNEL_CSUM)) ||
	    ((tpi->flags & TUNNEL_CSUM) &&
	     !(tunnel->parms.i_flags & TUNNEL_CSUM))) अणु
		tunnel->dev->stats.rx_crc_errors++;
		tunnel->dev->stats.rx_errors++;
		जाओ drop;
	पूर्ण

	अगर (tunnel->parms.i_flags & TUNNEL_SEQ) अणु
		अगर (!(tpi->flags & TUNNEL_SEQ) ||
		    (tunnel->i_seqno &&
		     (s32)(ntohl(tpi->seq) - tunnel->i_seqno) < 0)) अणु
			tunnel->dev->stats.rx_fअगरo_errors++;
			tunnel->dev->stats.rx_errors++;
			जाओ drop;
		पूर्ण
		tunnel->i_seqno = ntohl(tpi->seq) + 1;
	पूर्ण

	skb->protocol = tpi->proto;

	/* Warning: All skb poपूर्णांकers will be invalidated! */
	अगर (tunnel->dev->type == ARPHRD_ETHER) अणु
		अगर (!pskb_may_pull(skb, ETH_HLEN)) अणु
			tunnel->dev->stats.rx_length_errors++;
			tunnel->dev->stats.rx_errors++;
			जाओ drop;
		पूर्ण

		ipv6h = ipv6_hdr(skb);
		skb->protocol = eth_type_trans(skb, tunnel->dev);
		skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);
	पूर्ण अन्यथा अणु
		skb->dev = tunnel->dev;
	पूर्ण

	skb_reset_network_header(skb);
	स_रखो(skb->cb, 0, माप(काष्ठा inet6_skb_parm));

	__skb_tunnel_rx(skb, tunnel->dev, tunnel->net);

	err = dscp_ecn_decapsulate(tunnel, ipv6h, skb);
	अगर (unlikely(err)) अणु
		अगर (log_ecn_err)
			net_info_ratelimited("non-ECT from %pI6 with DS=%#x\n",
					     &ipv6h->saddr,
					     ipv6_get_dsfield(ipv6h));
		अगर (err > 1) अणु
			++tunnel->dev->stats.rx_frame_errors;
			++tunnel->dev->stats.rx_errors;
			जाओ drop;
		पूर्ण
	पूर्ण

	tstats = this_cpu_ptr(tunnel->dev->tstats);
	u64_stats_update_begin(&tstats->syncp);
	tstats->rx_packets++;
	tstats->rx_bytes += skb->len;
	u64_stats_update_end(&tstats->syncp);

	skb_scrub_packet(skb, !net_eq(tunnel->net, dev_net(tunnel->dev)));

	अगर (tun_dst)
		skb_dst_set(skb, (काष्ठा dst_entry *)tun_dst);

	gro_cells_receive(&tunnel->gro_cells, skb);
	वापस 0;

drop:
	अगर (tun_dst)
		dst_release((काष्ठा dst_entry *)tun_dst);
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

पूर्णांक ip6_tnl_rcv(काष्ठा ip6_tnl *t, काष्ठा sk_buff *skb,
		स्थिर काष्ठा tnl_ptk_info *tpi,
		काष्ठा metadata_dst *tun_dst,
		bool log_ecn_err)
अणु
	पूर्णांक (*dscp_ecn_decapsulate)(स्थिर काष्ठा ip6_tnl *t,
				    स्थिर काष्ठा ipv6hdr *ipv6h,
				    काष्ठा sk_buff *skb);

	dscp_ecn_decapsulate = ip6ip6_dscp_ecn_decapsulate;
	अगर (tpi->proto == htons(ETH_P_IP))
		dscp_ecn_decapsulate = ip4ip6_dscp_ecn_decapsulate;

	वापस __ip6_tnl_rcv(t, skb, tpi, tun_dst, dscp_ecn_decapsulate,
			     log_ecn_err);
पूर्ण
EXPORT_SYMBOL(ip6_tnl_rcv);

अटल स्थिर काष्ठा tnl_ptk_info tpi_v6 = अणु
	/* no tunnel info required क्रम ipxip6. */
	.proto = htons(ETH_P_IPV6),
पूर्ण;

अटल स्थिर काष्ठा tnl_ptk_info tpi_v4 = अणु
	/* no tunnel info required क्रम ipxip6. */
	.proto = htons(ETH_P_IP),
पूर्ण;

अटल स्थिर काष्ठा tnl_ptk_info tpi_mpls = अणु
	/* no tunnel info required क्रम mplsip6. */
	.proto = htons(ETH_P_MPLS_UC),
पूर्ण;

अटल पूर्णांक ipxip6_rcv(काष्ठा sk_buff *skb, u8 ipproto,
		      स्थिर काष्ठा tnl_ptk_info *tpi,
		      पूर्णांक (*dscp_ecn_decapsulate)(स्थिर काष्ठा ip6_tnl *t,
						  स्थिर काष्ठा ipv6hdr *ipv6h,
						  काष्ठा sk_buff *skb))
अणु
	काष्ठा ip6_tnl *t;
	स्थिर काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	काष्ठा metadata_dst *tun_dst = शून्य;
	पूर्णांक ret = -1;

	rcu_पढ़ो_lock();
	t = ip6_tnl_lookup(dev_net(skb->dev), skb->dev->अगरindex, &ipv6h->saddr, &ipv6h->daddr);

	अगर (t) अणु
		u8 tproto = READ_ONCE(t->parms.proto);

		अगर (tproto != ipproto && tproto != 0)
			जाओ drop;
		अगर (!xfrm6_policy_check(शून्य, XFRM_POLICY_IN, skb))
			जाओ drop;
		ipv6h = ipv6_hdr(skb);
		अगर (!ip6_tnl_rcv_ctl(t, &ipv6h->daddr, &ipv6h->saddr))
			जाओ drop;
		अगर (iptunnel_pull_header(skb, 0, tpi->proto, false))
			जाओ drop;
		अगर (t->parms.collect_md) अणु
			tun_dst = ipv6_tun_rx_dst(skb, 0, 0, 0);
			अगर (!tun_dst)
				जाओ drop;
		पूर्ण
		ret = __ip6_tnl_rcv(t, skb, tpi, tun_dst, dscp_ecn_decapsulate,
				    log_ecn_error);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस ret;

drop:
	rcu_पढ़ो_unlock();
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक ip4ip6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस ipxip6_rcv(skb, IPPROTO_IPIP, &tpi_v4,
			  ip4ip6_dscp_ecn_decapsulate);
पूर्ण

अटल पूर्णांक ip6ip6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस ipxip6_rcv(skb, IPPROTO_IPV6, &tpi_v6,
			  ip6ip6_dscp_ecn_decapsulate);
पूर्ण

अटल पूर्णांक mplsip6_rcv(काष्ठा sk_buff *skb)
अणु
	वापस ipxip6_rcv(skb, IPPROTO_MPLS, &tpi_mpls,
			  mplsip6_dscp_ecn_decapsulate);
पूर्ण

काष्ठा ipv6_tel_txoption अणु
	काष्ठा ipv6_txoptions ops;
	__u8 dst_opt[8];
पूर्ण;

अटल व्योम init_tel_txopt(काष्ठा ipv6_tel_txoption *opt, __u8 encap_limit)
अणु
	स_रखो(opt, 0, माप(काष्ठा ipv6_tel_txoption));

	opt->dst_opt[2] = IPV6_TLV_TNL_ENCAP_LIMIT;
	opt->dst_opt[3] = 1;
	opt->dst_opt[4] = encap_limit;
	opt->dst_opt[5] = IPV6_TLV_PADN;
	opt->dst_opt[6] = 1;

	opt->ops.dst1opt = (काष्ठा ipv6_opt_hdr *) opt->dst_opt;
	opt->ops.opt_nflen = 8;
पूर्ण

/**
 * ip6_tnl_addr_conflict - compare packet addresses to tunnel's own
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
ip6_tnl_addr_conflict(स्थिर काष्ठा ip6_tnl *t, स्थिर काष्ठा ipv6hdr *hdr)
अणु
	वापस ipv6_addr_equal(&t->parms.raddr, &hdr->saddr);
पूर्ण

पूर्णांक ip6_tnl_xmit_ctl(काष्ठा ip6_tnl *t,
		     स्थिर काष्ठा in6_addr *laddr,
		     स्थिर काष्ठा in6_addr *raddr)
अणु
	काष्ठा __ip6_tnl_parm *p = &t->parms;
	पूर्णांक ret = 0;
	काष्ठा net *net = t->net;

	अगर (t->parms.collect_md)
		वापस 1;

	अगर ((p->flags & IP6_TNL_F_CAP_XMIT) ||
	    ((p->flags & IP6_TNL_F_CAP_PER_PACKET) &&
	     (ip6_tnl_get_cap(t, laddr, raddr) & IP6_TNL_F_CAP_XMIT))) अणु
		काष्ठा net_device *ldev = शून्य;

		rcu_पढ़ो_lock();
		अगर (p->link)
			ldev = dev_get_by_index_rcu(net, p->link);

		अगर (unlikely(!ipv6_chk_addr_and_flags(net, laddr, ldev, false,
						      0, IFA_F_TENTATIVE)))
			pr_warn("%s xmit: Local address not yet configured!\n",
				p->name);
		अन्यथा अगर (!(p->flags & IP6_TNL_F_ALLOW_LOCAL_REMOTE) &&
			 !ipv6_addr_is_multicast(raddr) &&
			 unlikely(ipv6_chk_addr_and_flags(net, raddr, ldev,
							  true, 0, IFA_F_TENTATIVE)))
			pr_warn("%s xmit: Routing loop! Remote address found on this node!\n",
				p->name);
		अन्यथा
			ret = 1;
		rcu_पढ़ो_unlock();
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_tnl_xmit_ctl);

/**
 * ip6_tnl_xmit - encapsulate packet and send
 *   @skb: the outgoing socket buffer
 *   @dev: the outgoing tunnel device
 *   @dsfield: dscp code क्रम outer header
 *   @fl6: flow of tunneled packet
 *   @encap_limit: encapsulation limit
 *   @pmtu: Path MTU is stored अगर packet is too big
 *   @proto: next header value
 *
 * Description:
 *   Build new header and करो some sanity checks on the packet beक्रमe sending
 *   it.
 *
 * Return:
 *   0 on success
 *   -1 fail
 *   %-EMSGSIZE message too big. वापस mtu in this हाल.
 **/

पूर्णांक ip6_tnl_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev, __u8 dsfield,
		 काष्ठा flowi6 *fl6, पूर्णांक encap_limit, __u32 *pmtu,
		 __u8 proto)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = t->net;
	काष्ठा net_device_stats *stats = &t->dev->stats;
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा ipv6_tel_txoption opt;
	काष्ठा dst_entry *dst = शून्य, *ndst = शून्य;
	काष्ठा net_device *tdev;
	पूर्णांक mtu;
	अचिन्हित पूर्णांक eth_hlen = t->dev->type == ARPHRD_ETHER ? ETH_HLEN : 0;
	अचिन्हित पूर्णांक psh_hlen = माप(काष्ठा ipv6hdr) + t->encap_hlen;
	अचिन्हित पूर्णांक max_headroom = psh_hlen;
	bool use_cache = false;
	u8 hop_limit;
	पूर्णांक err = -1;

	अगर (t->parms.collect_md) अणु
		hop_limit = skb_tunnel_info(skb)->key.ttl;
		जाओ route_lookup;
	पूर्ण अन्यथा अणु
		hop_limit = t->parms.hop_limit;
	पूर्ण

	/* NBMA tunnel */
	अगर (ipv6_addr_any(&t->parms.raddr)) अणु
		अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			काष्ठा in6_addr *addr6;
			काष्ठा neighbour *neigh;
			पूर्णांक addr_type;

			अगर (!skb_dst(skb))
				जाओ tx_err_link_failure;

			neigh = dst_neigh_lookup(skb_dst(skb),
						 &ipv6_hdr(skb)->daddr);
			अगर (!neigh)
				जाओ tx_err_link_failure;

			addr6 = (काष्ठा in6_addr *)&neigh->primary_key;
			addr_type = ipv6_addr_type(addr6);

			अगर (addr_type == IPV6_ADDR_ANY)
				addr6 = &ipv6_hdr(skb)->daddr;

			स_नकल(&fl6->daddr, addr6, माप(fl6->daddr));
			neigh_release(neigh);
		पूर्ण
	पूर्ण अन्यथा अगर (t->parms.proto != 0 && !(t->parms.flags &
					    (IP6_TNL_F_USE_ORIG_TCLASS |
					     IP6_TNL_F_USE_ORIG_FWMARK))) अणु
		/* enable the cache only अगर neither the outer protocol nor the
		 * routing decision depends on the current inner header value
		 */
		use_cache = true;
	पूर्ण

	अगर (use_cache)
		dst = dst_cache_get(&t->dst_cache);

	अगर (!ip6_tnl_xmit_ctl(t, &fl6->saddr, &fl6->daddr))
		जाओ tx_err_link_failure;

	अगर (!dst) अणु
route_lookup:
		/* add dsfield to flowlabel क्रम route lookup */
		fl6->flowlabel = ip6_make_flowinfo(dsfield, fl6->flowlabel);

		dst = ip6_route_output(net, शून्य, fl6);

		अगर (dst->error)
			जाओ tx_err_link_failure;
		dst = xfrm_lookup(net, dst, flowi6_to_flowi(fl6), शून्य, 0);
		अगर (IS_ERR(dst)) अणु
			err = PTR_ERR(dst);
			dst = शून्य;
			जाओ tx_err_link_failure;
		पूर्ण
		अगर (t->parms.collect_md && ipv6_addr_any(&fl6->saddr) &&
		    ipv6_dev_get_saddr(net, ip6_dst_idev(dst)->dev,
				       &fl6->daddr, 0, &fl6->saddr))
			जाओ tx_err_link_failure;
		ndst = dst;
	पूर्ण

	tdev = dst->dev;

	अगर (tdev == dev) अणु
		stats->collisions++;
		net_warn_ratelimited("%s: Local routing loop detected!\n",
				     t->parms.name);
		जाओ tx_err_dst_release;
	पूर्ण
	mtu = dst_mtu(dst) - eth_hlen - psh_hlen - t->tun_hlen;
	अगर (encap_limit >= 0) अणु
		max_headroom += 8;
		mtu -= 8;
	पूर्ण
	mtu = max(mtu, skb->protocol == htons(ETH_P_IPV6) ?
		       IPV6_MIN_MTU : IPV4_MIN_MTU);

	skb_dst_update_pmtu_no_confirm(skb, mtu);
	अगर (skb->len - t->tun_hlen - eth_hlen > mtu && !skb_is_gso(skb)) अणु
		*pmtu = mtu;
		err = -EMSGSIZE;
		जाओ tx_err_dst_release;
	पूर्ण

	अगर (t->err_count > 0) अणु
		अगर (समय_beक्रमe(jअगरfies,
				t->err_समय + IP6TUNNEL_ERR_TIMEO)) अणु
			t->err_count--;

			dst_link_failure(skb);
		पूर्ण अन्यथा अणु
			t->err_count = 0;
		पूर्ण
	पूर्ण

	skb_scrub_packet(skb, !net_eq(t->net, dev_net(dev)));

	/*
	 * Okay, now see अगर we can stuff it in the buffer as-is.
	 */
	max_headroom += LL_RESERVED_SPACE(tdev);

	अगर (skb_headroom(skb) < max_headroom || skb_shared(skb) ||
	    (skb_cloned(skb) && !skb_clone_writable(skb, 0))) अणु
		काष्ठा sk_buff *new_skb;

		new_skb = skb_पुनः_स्मृति_headroom(skb, max_headroom);
		अगर (!new_skb)
			जाओ tx_err_dst_release;

		अगर (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
		consume_skb(skb);
		skb = new_skb;
	पूर्ण

	अगर (t->parms.collect_md) अणु
		अगर (t->encap.type != TUNNEL_ENCAP_NONE)
			जाओ tx_err_dst_release;
	पूर्ण अन्यथा अणु
		अगर (use_cache && ndst)
			dst_cache_set_ip6(&t->dst_cache, ndst, &fl6->saddr);
	पूर्ण
	skb_dst_set(skb, dst);

	अगर (hop_limit == 0) अणु
		अगर (skb->protocol == htons(ETH_P_IP))
			hop_limit = ip_hdr(skb)->ttl;
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			hop_limit = ipv6_hdr(skb)->hop_limit;
		अन्यथा
			hop_limit = ip6_dst_hoplimit(dst);
	पूर्ण

	/* Calculate max headroom क्रम all the headers and adjust
	 * needed_headroom अगर necessary.
	 */
	max_headroom = LL_RESERVED_SPACE(dst->dev) + माप(काष्ठा ipv6hdr)
			+ dst->header_len + t->hlen;
	अगर (max_headroom > dev->needed_headroom)
		dev->needed_headroom = max_headroom;

	skb_set_inner_ipproto(skb, proto);

	err = ip6_tnl_encap(skb, t, &proto, fl6);
	अगर (err)
		वापस err;

	अगर (encap_limit >= 0) अणु
		init_tel_txopt(&opt, encap_limit);
		ipv6_push_frag_opts(skb, &opt.ops, &proto);
	पूर्ण

	skb_push(skb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	ipv6h = ipv6_hdr(skb);
	ip6_flow_hdr(ipv6h, dsfield,
		     ip6_make_flowlabel(net, skb, fl6->flowlabel, true, fl6));
	ipv6h->hop_limit = hop_limit;
	ipv6h->nexthdr = proto;
	ipv6h->saddr = fl6->saddr;
	ipv6h->daddr = fl6->daddr;
	ip6tunnel_xmit(शून्य, skb, dev);
	वापस 0;
tx_err_link_failure:
	stats->tx_carrier_errors++;
	dst_link_failure(skb);
tx_err_dst_release:
	dst_release(dst);
	वापस err;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_xmit);

अटल अंतरभूत पूर्णांक
ipxip6_tnl_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		u8 protocol)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा ipv6hdr *ipv6h;
	स्थिर काष्ठा iphdr  *iph;
	पूर्णांक encap_limit = -1;
	__u16 offset;
	काष्ठा flowi6 fl6;
	__u8 dsfield, orig_dsfield;
	__u32 mtu;
	u8 tproto;
	पूर्णांक err;

	tproto = READ_ONCE(t->parms.proto);
	अगर (tproto != protocol && tproto != 0)
		वापस -1;

	अगर (t->parms.collect_md) अणु
		काष्ठा ip_tunnel_info *tun_info;
		स्थिर काष्ठा ip_tunnel_key *key;

		tun_info = skb_tunnel_info(skb);
		अगर (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
			     ip_tunnel_info_af(tun_info) != AF_INET6))
			वापस -1;
		key = &tun_info->key;
		स_रखो(&fl6, 0, माप(fl6));
		fl6.flowi6_proto = protocol;
		fl6.saddr = key->u.ipv6.src;
		fl6.daddr = key->u.ipv6.dst;
		fl6.flowlabel = key->label;
		dsfield =  key->tos;
		चयन (protocol) अणु
		हाल IPPROTO_IPIP:
			iph = ip_hdr(skb);
			orig_dsfield = ipv4_get_dsfield(iph);
			अवरोध;
		हाल IPPROTO_IPV6:
			ipv6h = ipv6_hdr(skb);
			orig_dsfield = ipv6_get_dsfield(ipv6h);
			अवरोध;
		शेष:
			orig_dsfield = dsfield;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
			encap_limit = t->parms.encap_limit;
		अगर (protocol == IPPROTO_IPV6) अणु
			offset = ip6_tnl_parse_tlv_enc_lim(skb,
						skb_network_header(skb));
			/* ip6_tnl_parse_tlv_enc_lim() might have
			 * पुनः_स्मृतिated skb->head
			 */
			अगर (offset > 0) अणु
				काष्ठा ipv6_tlv_tnl_enc_lim *tel;

				tel = (व्योम *)&skb_network_header(skb)[offset];
				अगर (tel->encap_limit == 0) अणु
					icmpv6_nकरो_send(skb, ICMPV6_PARAMPROB,
							ICMPV6_HDR_FIELD, offset + 2);
					वापस -1;
				पूर्ण
				encap_limit = tel->encap_limit - 1;
			पूर्ण
		पूर्ण

		स_नकल(&fl6, &t->fl.u.ip6, माप(fl6));
		fl6.flowi6_proto = protocol;

		अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_FWMARK)
			fl6.flowi6_mark = skb->mark;
		अन्यथा
			fl6.flowi6_mark = t->parms.fwmark;
		चयन (protocol) अणु
		हाल IPPROTO_IPIP:
			iph = ip_hdr(skb);
			orig_dsfield = ipv4_get_dsfield(iph);
			अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_TCLASS)
				dsfield = orig_dsfield;
			अन्यथा
				dsfield = ip6_tclass(t->parms.flowinfo);
			अवरोध;
		हाल IPPROTO_IPV6:
			ipv6h = ipv6_hdr(skb);
			orig_dsfield = ipv6_get_dsfield(ipv6h);
			अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_TCLASS)
				dsfield = orig_dsfield;
			अन्यथा
				dsfield = ip6_tclass(t->parms.flowinfo);
			अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_FLOWLABEL)
				fl6.flowlabel |= ip6_flowlabel(ipv6h);
			अवरोध;
		शेष:
			orig_dsfield = dsfield = ip6_tclass(t->parms.flowinfo);
			अवरोध;
		पूर्ण
	पूर्ण

	fl6.flowi6_uid = sock_net_uid(dev_net(dev), शून्य);
	dsfield = INET_ECN_encapsulate(dsfield, orig_dsfield);

	अगर (iptunnel_handle_offloads(skb, SKB_GSO_IPXIP6))
		वापस -1;

	err = ip6_tnl_xmit(skb, dev, dsfield, &fl6, encap_limit, &mtu,
			   protocol);
	अगर (err != 0) अणु
		/* XXX: send ICMP error even अगर DF is not set. */
		अगर (err == -EMSGSIZE)
			चयन (protocol) अणु
			हाल IPPROTO_IPIP:
				icmp_nकरो_send(skb, ICMP_DEST_UNREACH,
					      ICMP_FRAG_NEEDED, htonl(mtu));
				अवरोध;
			हाल IPPROTO_IPV6:
				icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_tx_t
ip6_tnl_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &t->dev->stats;
	u8 ipproto;
	पूर्णांक ret;

	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_err;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		ipproto = IPPROTO_IPIP;
		अवरोध;
	हाल htons(ETH_P_IPV6):
		अगर (ip6_tnl_addr_conflict(t, ipv6_hdr(skb)))
			जाओ tx_err;
		ipproto = IPPROTO_IPV6;
		अवरोध;
	हाल htons(ETH_P_MPLS_UC):
		ipproto = IPPROTO_MPLS;
		अवरोध;
	शेष:
		जाओ tx_err;
	पूर्ण

	ret = ipxip6_tnl_xmit(skb, dev, ipproto);
	अगर (ret < 0)
		जाओ tx_err;

	वापस NETDEV_TX_OK;

tx_err:
	stats->tx_errors++;
	stats->tx_dropped++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ip6_tnl_link_config(काष्ठा ip6_tnl *t)
अणु
	काष्ठा net_device *dev = t->dev;
	काष्ठा net_device *tdev = शून्य;
	काष्ठा __ip6_tnl_parm *p = &t->parms;
	काष्ठा flowi6 *fl6 = &t->fl.u.ip6;
	अचिन्हित पूर्णांक mtu;
	पूर्णांक t_hlen;

	स_नकल(dev->dev_addr, &p->laddr, माप(काष्ठा in6_addr));
	स_नकल(dev->broadcast, &p->raddr, माप(काष्ठा in6_addr));

	/* Set up flowi ढाँचा */
	fl6->saddr = p->laddr;
	fl6->daddr = p->raddr;
	fl6->flowi6_oअगर = p->link;
	fl6->flowlabel = 0;

	अगर (!(p->flags&IP6_TNL_F_USE_ORIG_TCLASS))
		fl6->flowlabel |= IPV6_TCLASS_MASK & p->flowinfo;
	अगर (!(p->flags&IP6_TNL_F_USE_ORIG_FLOWLABEL))
		fl6->flowlabel |= IPV6_FLOWLABEL_MASK & p->flowinfo;

	p->flags &= ~(IP6_TNL_F_CAP_XMIT|IP6_TNL_F_CAP_RCV|IP6_TNL_F_CAP_PER_PACKET);
	p->flags |= ip6_tnl_get_cap(t, &p->laddr, &p->raddr);

	अगर (p->flags&IP6_TNL_F_CAP_XMIT && p->flags&IP6_TNL_F_CAP_RCV)
		dev->flags |= IFF_POINTOPOINT;
	अन्यथा
		dev->flags &= ~IFF_POINTOPOINT;

	t->tun_hlen = 0;
	t->hlen = t->encap_hlen + t->tun_hlen;
	t_hlen = t->hlen + माप(काष्ठा ipv6hdr);

	अगर (p->flags & IP6_TNL_F_CAP_XMIT) अणु
		पूर्णांक strict = (ipv6_addr_type(&p->raddr) &
			      (IPV6_ADDR_MULTICAST|IPV6_ADDR_LINKLOCAL));

		काष्ठा rt6_info *rt = rt6_lookup(t->net,
						 &p->raddr, &p->laddr,
						 p->link, शून्य, strict);
		अगर (rt) अणु
			tdev = rt->dst.dev;
			ip6_rt_put(rt);
		पूर्ण

		अगर (!tdev && p->link)
			tdev = __dev_get_by_index(t->net, p->link);

		अगर (tdev) अणु
			dev->hard_header_len = tdev->hard_header_len + t_hlen;
			mtu = min_t(अचिन्हित पूर्णांक, tdev->mtu, IP6_MAX_MTU);

			dev->mtu = mtu - t_hlen;
			अगर (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
				dev->mtu -= 8;

			अगर (dev->mtu < IPV6_MIN_MTU)
				dev->mtu = IPV6_MIN_MTU;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ip6_tnl_change - update the tunnel parameters
 *   @t: tunnel to be changed
 *   @p: tunnel configuration parameters
 *
 * Description:
 *   ip6_tnl_change() updates the tunnel parameters
 **/

अटल पूर्णांक
ip6_tnl_change(काष्ठा ip6_tnl *t, स्थिर काष्ठा __ip6_tnl_parm *p)
अणु
	t->parms.laddr = p->laddr;
	t->parms.raddr = p->raddr;
	t->parms.flags = p->flags;
	t->parms.hop_limit = p->hop_limit;
	t->parms.encap_limit = p->encap_limit;
	t->parms.flowinfo = p->flowinfo;
	t->parms.link = p->link;
	t->parms.proto = p->proto;
	t->parms.fwmark = p->fwmark;
	dst_cache_reset(&t->dst_cache);
	ip6_tnl_link_config(t);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6_tnl_update(काष्ठा ip6_tnl *t, काष्ठा __ip6_tnl_parm *p)
अणु
	काष्ठा net *net = t->net;
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);
	पूर्णांक err;

	ip6_tnl_unlink(ip6n, t);
	synchronize_net();
	err = ip6_tnl_change(t, p);
	ip6_tnl_link(ip6n, t);
	netdev_state_change(t->dev);
	वापस err;
पूर्ण

अटल पूर्णांक ip6_tnl0_update(काष्ठा ip6_tnl *t, काष्ठा __ip6_tnl_parm *p)
अणु
	/* क्रम शेष tnl0 device allow to change only the proto */
	t->parms.proto = p->proto;
	netdev_state_change(t->dev);
	वापस 0;
पूर्ण

अटल व्योम
ip6_tnl_parm_from_user(काष्ठा __ip6_tnl_parm *p, स्थिर काष्ठा ip6_tnl_parm *u)
अणु
	p->laddr = u->laddr;
	p->raddr = u->raddr;
	p->flags = u->flags;
	p->hop_limit = u->hop_limit;
	p->encap_limit = u->encap_limit;
	p->flowinfo = u->flowinfo;
	p->link = u->link;
	p->proto = u->proto;
	स_नकल(p->name, u->name, माप(u->name));
पूर्ण

अटल व्योम
ip6_tnl_parm_to_user(काष्ठा ip6_tnl_parm *u, स्थिर काष्ठा __ip6_tnl_parm *p)
अणु
	u->laddr = p->laddr;
	u->raddr = p->raddr;
	u->flags = p->flags;
	u->hop_limit = p->hop_limit;
	u->encap_limit = p->encap_limit;
	u->flowinfo = p->flowinfo;
	u->link = p->link;
	u->proto = p->proto;
	स_नकल(u->name, p->name, माप(u->name));
पूर्ण

/**
 * ip6_tnl_ioctl - configure ipv6 tunnels from userspace
 *   @dev: भव device associated with tunnel
 *   @अगरr: parameters passed from userspace
 *   @cmd: command to be perक्रमmed
 *
 * Description:
 *   ip6_tnl_ioctl() is used क्रम managing IPv6 tunnels
 *   from userspace.
 *
 *   The possible commands are the following:
 *     %SIOCGETTUNNEL: get tunnel parameters क्रम device
 *     %SIOCADDTUNNEL: add tunnel matching given tunnel parameters
 *     %SIOCCHGTUNNEL: change tunnel parameters to those given
 *     %SIOCDELTUNNEL: delete tunnel
 *
 *   The fallback device "ip6tnl0", created during module
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
ip6_tnl_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक err = 0;
	काष्ठा ip6_tnl_parm p;
	काष्ठा __ip6_tnl_parm p1;
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = t->net;
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	स_रखो(&p1, 0, माप(p1));

	चयन (cmd) अणु
	हाल SIOCGETTUNNEL:
		अगर (dev == ip6n->fb_tnl_dev) अणु
			अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p))) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
			ip6_tnl_parm_from_user(&p1, &p);
			t = ip6_tnl_locate(net, &p1, 0);
			अगर (IS_ERR(t))
				t = netdev_priv(dev);
		पूर्ण अन्यथा अणु
			स_रखो(&p, 0, माप(p));
		पूर्ण
		ip6_tnl_parm_to_user(&p, &t->parms);
		अगर (copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &p, माप(p))) अणु
			err = -EFAULT;
		पूर्ण
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
		अगर (p.proto != IPPROTO_IPV6 && p.proto != IPPROTO_IPIP &&
		    p.proto != 0)
			अवरोध;
		ip6_tnl_parm_from_user(&p1, &p);
		t = ip6_tnl_locate(net, &p1, cmd == SIOCADDTUNNEL);
		अगर (cmd == SIOCCHGTUNNEL) अणु
			अगर (!IS_ERR(t)) अणु
				अगर (t->dev != dev) अणु
					err = -EEXIST;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा
				t = netdev_priv(dev);
			अगर (dev == ip6n->fb_tnl_dev)
				err = ip6_tnl0_update(t, &p1);
			अन्यथा
				err = ip6_tnl_update(t, &p1);
		पूर्ण
		अगर (!IS_ERR(t)) अणु
			err = 0;
			ip6_tnl_parm_to_user(&p, &t->parms);
			अगर (copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &p, माप(p)))
				err = -EFAULT;

		पूर्ण अन्यथा अणु
			err = PTR_ERR(t);
		पूर्ण
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
			ip6_tnl_parm_from_user(&p1, &p);
			t = ip6_tnl_locate(net, &p1, 0);
			अगर (IS_ERR(t))
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

/**
 * ip6_tnl_change_mtu - change mtu manually क्रम tunnel device
 *   @dev: भव device associated with tunnel
 *   @new_mtu: the new mtu
 *
 * Return:
 *   0 on success,
 *   %-EINVAL अगर mtu too small
 **/

पूर्णांक ip6_tnl_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा ip6_tnl *tnl = netdev_priv(dev);

	अगर (tnl->parms.proto == IPPROTO_IPV6) अणु
		अगर (new_mtu < IPV6_MIN_MTU)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (new_mtu < ETH_MIN_MTU)
			वापस -EINVAL;
	पूर्ण
	अगर (tnl->parms.proto == IPPROTO_IPV6 || tnl->parms.proto == 0) अणु
		अगर (new_mtu > IP6_MAX_MTU - dev->hard_header_len)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (new_mtu > IP_MAX_MTU - dev->hard_header_len)
			वापस -EINVAL;
	पूर्ण
	dev->mtu = new_mtu;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_change_mtu);

पूर्णांक ip6_tnl_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);

	वापस t->parms.link;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_get_अगरlink);

पूर्णांक ip6_tnl_encap_add_ops(स्थिर काष्ठा ip6_tnl_encap_ops *ops,
			  अचिन्हित पूर्णांक num)
अणु
	अगर (num >= MAX_IPTUN_ENCAP_OPS)
		वापस -दुस्फल;

	वापस !cmpxchg((स्थिर काष्ठा ip6_tnl_encap_ops **)
			&ip6tun_encaps[num],
			शून्य, ops) ? 0 : -1;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_encap_add_ops);

पूर्णांक ip6_tnl_encap_del_ops(स्थिर काष्ठा ip6_tnl_encap_ops *ops,
			  अचिन्हित पूर्णांक num)
अणु
	पूर्णांक ret;

	अगर (num >= MAX_IPTUN_ENCAP_OPS)
		वापस -दुस्फल;

	ret = (cmpxchg((स्थिर काष्ठा ip6_tnl_encap_ops **)
		       &ip6tun_encaps[num],
		       ops, शून्य) == ops) ? 0 : -1;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_encap_del_ops);

पूर्णांक ip6_tnl_encap_setup(काष्ठा ip6_tnl *t,
			काष्ठा ip_tunnel_encap *ipencap)
अणु
	पूर्णांक hlen;

	स_रखो(&t->encap, 0, माप(t->encap));

	hlen = ip6_encap_hlen(ipencap);
	अगर (hlen < 0)
		वापस hlen;

	t->encap.type = ipencap->type;
	t->encap.sport = ipencap->sport;
	t->encap.dport = ipencap->dport;
	t->encap.flags = ipencap->flags;

	t->encap_hlen = hlen;
	t->hlen = t->encap_hlen + t->tun_hlen;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip6_tnl_encap_setup);

अटल स्थिर काष्ठा net_device_ops ip6_tnl_netdev_ops = अणु
	.nकरो_init	= ip6_tnl_dev_init,
	.nकरो_uninit	= ip6_tnl_dev_uninit,
	.nकरो_start_xmit = ip6_tnl_start_xmit,
	.nकरो_करो_ioctl	= ip6_tnl_ioctl,
	.nकरो_change_mtu = ip6_tnl_change_mtu,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_get_अगरlink = ip6_tnl_get_अगरlink,
पूर्ण;

#घोषणा IPXIPX_FEATURES (NETIF_F_SG |		\
			 NETIF_F_FRAGLIST |	\
			 NETIF_F_HIGHDMA |	\
			 NETIF_F_GSO_SOFTWARE |	\
			 NETIF_F_HW_CSUM)

/**
 * ip6_tnl_dev_setup - setup भव tunnel device
 *   @dev: भव device associated with tunnel
 *
 * Description:
 *   Initialize function poपूर्णांकers and device parameters
 **/

अटल व्योम ip6_tnl_dev_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &ip6_tnl_netdev_ops;
	dev->header_ops = &ip_tunnel_header_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = ip6_dev_मुक्त;

	dev->type = ARPHRD_TUNNEL6;
	dev->flags |= IFF_NOARP;
	dev->addr_len = माप(काष्ठा in6_addr);
	dev->features |= NETIF_F_LLTX;
	netअगर_keep_dst(dev);

	dev->features		|= IPXIPX_FEATURES;
	dev->hw_features	|= IPXIPX_FEATURES;

	/* This perm addr will be used as पूर्णांकerface identअगरier by IPv6 */
	dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_अक्रमom_addr(dev->perm_addr);
पूर्ण


/**
 * ip6_tnl_dev_init_gen - general initializer क्रम all tunnel devices
 *   @dev: भव device associated with tunnel
 **/

अटल अंतरभूत पूर्णांक
ip6_tnl_dev_init_gen(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	पूर्णांक ret;
	पूर्णांक t_hlen;

	t->dev = dev;
	t->net = dev_net(dev);
	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	ret = dst_cache_init(&t->dst_cache, GFP_KERNEL);
	अगर (ret)
		जाओ मुक्त_stats;

	ret = gro_cells_init(&t->gro_cells, dev);
	अगर (ret)
		जाओ destroy_dst;

	t->tun_hlen = 0;
	t->hlen = t->encap_hlen + t->tun_hlen;
	t_hlen = t->hlen + माप(काष्ठा ipv6hdr);

	dev->type = ARPHRD_TUNNEL6;
	dev->hard_header_len = LL_MAX_HEADER + t_hlen;
	dev->mtu = ETH_DATA_LEN - t_hlen;
	अगर (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
		dev->mtu -= 8;
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = IP6_MAX_MTU - dev->hard_header_len;

	dev_hold(dev);
	वापस 0;

destroy_dst:
	dst_cache_destroy(&t->dst_cache);
मुक्त_stats:
	मुक्त_percpu(dev->tstats);
	dev->tstats = शून्य;

	वापस ret;
पूर्ण

/**
 * ip6_tnl_dev_init - initializer क्रम all non fallback tunnel devices
 *   @dev: भव device associated with tunnel
 **/

अटल पूर्णांक ip6_tnl_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	पूर्णांक err = ip6_tnl_dev_init_gen(dev);

	अगर (err)
		वापस err;
	ip6_tnl_link_config(t);
	अगर (t->parms.collect_md)
		netअगर_keep_dst(dev);
	वापस 0;
पूर्ण

/**
 * ip6_fb_tnl_dev_init - initializer क्रम fallback tunnel device
 *   @dev: fallback device
 *
 * Return: 0
 **/

अटल पूर्णांक __net_init ip6_fb_tnl_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	t->parms.proto = IPPROTO_IPV6;

	rcu_assign_poपूर्णांकer(ip6n->tnls_wc[0], t);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6_tnl_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			    काष्ठा netlink_ext_ack *extack)
अणु
	u8 proto;

	अगर (!data || !data[IFLA_IPTUN_PROTO])
		वापस 0;

	proto = nla_get_u8(data[IFLA_IPTUN_PROTO]);
	अगर (proto != IPPROTO_IPV6 &&
	    proto != IPPROTO_IPIP &&
	    proto != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम ip6_tnl_netlink_parms(काष्ठा nlattr *data[],
				  काष्ठा __ip6_tnl_parm *parms)
अणु
	स_रखो(parms, 0, माप(*parms));

	अगर (!data)
		वापस;

	अगर (data[IFLA_IPTUN_LINK])
		parms->link = nla_get_u32(data[IFLA_IPTUN_LINK]);

	अगर (data[IFLA_IPTUN_LOCAL])
		parms->laddr = nla_get_in6_addr(data[IFLA_IPTUN_LOCAL]);

	अगर (data[IFLA_IPTUN_REMOTE])
		parms->raddr = nla_get_in6_addr(data[IFLA_IPTUN_REMOTE]);

	अगर (data[IFLA_IPTUN_TTL])
		parms->hop_limit = nla_get_u8(data[IFLA_IPTUN_TTL]);

	अगर (data[IFLA_IPTUN_ENCAP_LIMIT])
		parms->encap_limit = nla_get_u8(data[IFLA_IPTUN_ENCAP_LIMIT]);

	अगर (data[IFLA_IPTUN_FLOWINFO])
		parms->flowinfo = nla_get_be32(data[IFLA_IPTUN_FLOWINFO]);

	अगर (data[IFLA_IPTUN_FLAGS])
		parms->flags = nla_get_u32(data[IFLA_IPTUN_FLAGS]);

	अगर (data[IFLA_IPTUN_PROTO])
		parms->proto = nla_get_u8(data[IFLA_IPTUN_PROTO]);

	अगर (data[IFLA_IPTUN_COLLECT_METADATA])
		parms->collect_md = true;

	अगर (data[IFLA_IPTUN_FWMARK])
		parms->fwmark = nla_get_u32(data[IFLA_IPTUN_FWMARK]);
पूर्ण

अटल bool ip6_tnl_netlink_encap_parms(काष्ठा nlattr *data[],
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

अटल पूर्णांक ip6_tnl_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			   काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);
	काष्ठा ip_tunnel_encap ipencap;
	काष्ठा ip6_tnl *nt, *t;
	पूर्णांक err;

	nt = netdev_priv(dev);

	अगर (ip6_tnl_netlink_encap_parms(data, &ipencap)) अणु
		err = ip6_tnl_encap_setup(nt, &ipencap);
		अगर (err < 0)
			वापस err;
	पूर्ण

	ip6_tnl_netlink_parms(data, &nt->parms);

	अगर (nt->parms.collect_md) अणु
		अगर (rtnl_dereference(ip6n->collect_md_tun))
			वापस -EEXIST;
	पूर्ण अन्यथा अणु
		t = ip6_tnl_locate(net, &nt->parms, 0);
		अगर (!IS_ERR(t))
			वापस -EEXIST;
	पूर्ण

	err = ip6_tnl_create2(dev);
	अगर (!err && tb[IFLA_MTU])
		ip6_tnl_change_mtu(dev, nla_get_u32(tb[IFLA_MTU]));

	वापस err;
पूर्ण

अटल पूर्णांक ip6_tnl_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			      काष्ठा nlattr *data[],
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा __ip6_tnl_parm p;
	काष्ठा net *net = t->net;
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);
	काष्ठा ip_tunnel_encap ipencap;

	अगर (dev == ip6n->fb_tnl_dev)
		वापस -EINVAL;

	अगर (ip6_tnl_netlink_encap_parms(data, &ipencap)) अणु
		पूर्णांक err = ip6_tnl_encap_setup(t, &ipencap);

		अगर (err < 0)
			वापस err;
	पूर्ण
	ip6_tnl_netlink_parms(data, &p);
	अगर (p.collect_md)
		वापस -EINVAL;

	t = ip6_tnl_locate(net, &p, 0);
	अगर (!IS_ERR(t)) अणु
		अगर (t->dev != dev)
			वापस -EEXIST;
	पूर्ण अन्यथा
		t = netdev_priv(dev);

	वापस ip6_tnl_update(t, &p);
पूर्ण

अटल व्योम ip6_tnl_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);

	अगर (dev != ip6n->fb_tnl_dev)
		unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल माप_प्रकार ip6_tnl_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_IPTUN_LINK */
		nla_total_size(4) +
		/* IFLA_IPTUN_LOCAL */
		nla_total_size(माप(काष्ठा in6_addr)) +
		/* IFLA_IPTUN_REMOTE */
		nla_total_size(माप(काष्ठा in6_addr)) +
		/* IFLA_IPTUN_TTL */
		nla_total_size(1) +
		/* IFLA_IPTUN_ENCAP_LIMIT */
		nla_total_size(1) +
		/* IFLA_IPTUN_FLOWINFO */
		nla_total_size(4) +
		/* IFLA_IPTUN_FLAGS */
		nla_total_size(4) +
		/* IFLA_IPTUN_PROTO */
		nla_total_size(1) +
		/* IFLA_IPTUN_ENCAP_TYPE */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_FLAGS */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_SPORT */
		nla_total_size(2) +
		/* IFLA_IPTUN_ENCAP_DPORT */
		nla_total_size(2) +
		/* IFLA_IPTUN_COLLECT_METADATA */
		nla_total_size(0) +
		/* IFLA_IPTUN_FWMARK */
		nla_total_size(4) +
		0;
पूर्ण

अटल पूर्णांक ip6_tnl_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *tunnel = netdev_priv(dev);
	काष्ठा __ip6_tnl_parm *parm = &tunnel->parms;

	अगर (nla_put_u32(skb, IFLA_IPTUN_LINK, parm->link) ||
	    nla_put_in6_addr(skb, IFLA_IPTUN_LOCAL, &parm->laddr) ||
	    nla_put_in6_addr(skb, IFLA_IPTUN_REMOTE, &parm->raddr) ||
	    nla_put_u8(skb, IFLA_IPTUN_TTL, parm->hop_limit) ||
	    nla_put_u8(skb, IFLA_IPTUN_ENCAP_LIMIT, parm->encap_limit) ||
	    nla_put_be32(skb, IFLA_IPTUN_FLOWINFO, parm->flowinfo) ||
	    nla_put_u32(skb, IFLA_IPTUN_FLAGS, parm->flags) ||
	    nla_put_u8(skb, IFLA_IPTUN_PROTO, parm->proto) ||
	    nla_put_u32(skb, IFLA_IPTUN_FWMARK, parm->fwmark))
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, IFLA_IPTUN_ENCAP_TYPE, tunnel->encap.type) ||
	    nla_put_be16(skb, IFLA_IPTUN_ENCAP_SPORT, tunnel->encap.sport) ||
	    nla_put_be16(skb, IFLA_IPTUN_ENCAP_DPORT, tunnel->encap.dport) ||
	    nla_put_u16(skb, IFLA_IPTUN_ENCAP_FLAGS, tunnel->encap.flags))
		जाओ nla_put_failure;

	अगर (parm->collect_md)
		अगर (nla_put_flag(skb, IFLA_IPTUN_COLLECT_METADATA))
			जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

काष्ठा net *ip6_tnl_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *tunnel = netdev_priv(dev);

	वापस tunnel->net;
पूर्ण
EXPORT_SYMBOL(ip6_tnl_get_link_net);

अटल स्थिर काष्ठा nla_policy ip6_tnl_policy[IFLA_IPTUN_MAX + 1] = अणु
	[IFLA_IPTUN_LINK]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_LOCAL]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_IPTUN_REMOTE]		= अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[IFLA_IPTUN_TTL]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_ENCAP_LIMIT]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_FLOWINFO]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[IFLA_IPTUN_PROTO]		= अणु .type = NLA_U8 पूर्ण,
	[IFLA_IPTUN_ENCAP_TYPE]		= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_FLAGS]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_SPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_ENCAP_DPORT]	= अणु .type = NLA_U16 पूर्ण,
	[IFLA_IPTUN_COLLECT_METADATA]	= अणु .type = NLA_FLAG पूर्ण,
	[IFLA_IPTUN_FWMARK]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल काष्ठा rtnl_link_ops ip6_link_ops __पढ़ो_mostly = अणु
	.kind		= "ip6tnl",
	.maxtype	= IFLA_IPTUN_MAX,
	.policy		= ip6_tnl_policy,
	.priv_size	= माप(काष्ठा ip6_tnl),
	.setup		= ip6_tnl_dev_setup,
	.validate	= ip6_tnl_validate,
	.newlink	= ip6_tnl_newlink,
	.changelink	= ip6_tnl_changelink,
	.dellink	= ip6_tnl_dellink,
	.get_size	= ip6_tnl_get_size,
	.fill_info	= ip6_tnl_fill_info,
	.get_link_net	= ip6_tnl_get_link_net,
पूर्ण;

अटल काष्ठा xfrm6_tunnel ip4ip6_handler __पढ़ो_mostly = अणु
	.handler	= ip4ip6_rcv,
	.err_handler	= ip4ip6_err,
	.priority	=	1,
पूर्ण;

अटल काष्ठा xfrm6_tunnel ip6ip6_handler __पढ़ो_mostly = अणु
	.handler	= ip6ip6_rcv,
	.err_handler	= ip6ip6_err,
	.priority	=	1,
पूर्ण;

अटल काष्ठा xfrm6_tunnel mplsip6_handler __पढ़ो_mostly = अणु
	.handler	= mplsip6_rcv,
	.err_handler	= mplsip6_err,
	.priority	=	1,
पूर्ण;

अटल व्योम __net_निकास ip6_tnl_destroy_tunnels(काष्ठा net *net, काष्ठा list_head *list)
अणु
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);
	काष्ठा net_device *dev, *aux;
	पूर्णांक h;
	काष्ठा ip6_tnl *t;

	क्रम_each_netdev_safe(net, dev, aux)
		अगर (dev->rtnl_link_ops == &ip6_link_ops)
			unरेजिस्टर_netdevice_queue(dev, list);

	क्रम (h = 0; h < IP6_TUNNEL_HASH_SIZE; h++) अणु
		t = rtnl_dereference(ip6n->tnls_r_l[h]);
		जबतक (t) अणु
			/* If dev is in the same netns, it has alपढ़ोy
			 * been added to the list by the previous loop.
			 */
			अगर (!net_eq(dev_net(t->dev), net))
				unरेजिस्टर_netdevice_queue(t->dev, list);
			t = rtnl_dereference(t->next);
		पूर्ण
	पूर्ण

	t = rtnl_dereference(ip6n->tnls_wc[0]);
	जबतक (t) अणु
		/* If dev is in the same netns, it has alपढ़ोy
		 * been added to the list by the previous loop.
		 */
		अगर (!net_eq(dev_net(t->dev), net))
			unरेजिस्टर_netdevice_queue(t->dev, list);
		t = rtnl_dereference(t->next);
	पूर्ण
पूर्ण

अटल पूर्णांक __net_init ip6_tnl_init_net(काष्ठा net *net)
अणु
	काष्ठा ip6_tnl_net *ip6n = net_generic(net, ip6_tnl_net_id);
	काष्ठा ip6_tnl *t = शून्य;
	पूर्णांक err;

	ip6n->tnls[0] = ip6n->tnls_wc;
	ip6n->tnls[1] = ip6n->tnls_r_l;

	अगर (!net_has_fallback_tunnels(net))
		वापस 0;
	err = -ENOMEM;
	ip6n->fb_tnl_dev = alloc_netdev(माप(काष्ठा ip6_tnl), "ip6tnl0",
					NET_NAME_UNKNOWN, ip6_tnl_dev_setup);

	अगर (!ip6n->fb_tnl_dev)
		जाओ err_alloc_dev;
	dev_net_set(ip6n->fb_tnl_dev, net);
	ip6n->fb_tnl_dev->rtnl_link_ops = &ip6_link_ops;
	/* FB netdevice is special: we have one, and only one per netns.
	 * Allowing to move it to another netns is clearly unsafe.
	 */
	ip6n->fb_tnl_dev->features |= NETIF_F_NETNS_LOCAL;

	err = ip6_fb_tnl_dev_init(ip6n->fb_tnl_dev);
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

अटल व्योम __net_निकास ip6_tnl_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	काष्ठा net *net;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list)
		ip6_tnl_destroy_tunnels(net, &list);
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations ip6_tnl_net_ops = अणु
	.init = ip6_tnl_init_net,
	.निकास_batch = ip6_tnl_निकास_batch_net,
	.id   = &ip6_tnl_net_id,
	.size = माप(काष्ठा ip6_tnl_net),
पूर्ण;

/**
 * ip6_tunnel_init - रेजिस्टर protocol and reserve needed resources
 *
 * Return: 0 on success
 **/

अटल पूर्णांक __init ip6_tunnel_init(व्योम)
अणु
	पूर्णांक  err;

	अगर (!ipv6_mod_enabled())
		वापस -EOPNOTSUPP;

	err = रेजिस्टर_pernet_device(&ip6_tnl_net_ops);
	अगर (err < 0)
		जाओ out_pernet;

	err = xfrm6_tunnel_रेजिस्टर(&ip4ip6_handler, AF_INET);
	अगर (err < 0) अणु
		pr_err("%s: can't register ip4ip6\n", __func__);
		जाओ out_ip4ip6;
	पूर्ण

	err = xfrm6_tunnel_रेजिस्टर(&ip6ip6_handler, AF_INET6);
	अगर (err < 0) अणु
		pr_err("%s: can't register ip6ip6\n", __func__);
		जाओ out_ip6ip6;
	पूर्ण

	अगर (ip6_tnl_mpls_supported()) अणु
		err = xfrm6_tunnel_रेजिस्टर(&mplsip6_handler, AF_MPLS);
		अगर (err < 0) अणु
			pr_err("%s: can't register mplsip6\n", __func__);
			जाओ out_mplsip6;
		पूर्ण
	पूर्ण

	err = rtnl_link_रेजिस्टर(&ip6_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

	वापस 0;

rtnl_link_failed:
	अगर (ip6_tnl_mpls_supported())
		xfrm6_tunnel_deरेजिस्टर(&mplsip6_handler, AF_MPLS);
out_mplsip6:
	xfrm6_tunnel_deरेजिस्टर(&ip6ip6_handler, AF_INET6);
out_ip6ip6:
	xfrm6_tunnel_deरेजिस्टर(&ip4ip6_handler, AF_INET);
out_ip4ip6:
	unरेजिस्टर_pernet_device(&ip6_tnl_net_ops);
out_pernet:
	वापस err;
पूर्ण

/**
 * ip6_tunnel_cleanup - मुक्त resources and unरेजिस्टर protocol
 **/

अटल व्योम __निकास ip6_tunnel_cleanup(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&ip6_link_ops);
	अगर (xfrm6_tunnel_deरेजिस्टर(&ip4ip6_handler, AF_INET))
		pr_info("%s: can't deregister ip4ip6\n", __func__);

	अगर (xfrm6_tunnel_deरेजिस्टर(&ip6ip6_handler, AF_INET6))
		pr_info("%s: can't deregister ip6ip6\n", __func__);

	अगर (ip6_tnl_mpls_supported() &&
	    xfrm6_tunnel_deरेजिस्टर(&mplsip6_handler, AF_MPLS))
		pr_info("%s: can't deregister mplsip6\n", __func__);
	unरेजिस्टर_pernet_device(&ip6_tnl_net_ops);
पूर्ण

module_init(ip6_tunnel_init);
module_निकास(ip6_tunnel_cleanup);
