<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2013 Nicira, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/init.h>
#समावेश <linux/in6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/igmp.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/rculist.h>
#समावेश <linux/err.h>

#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/protocol.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/arp.h>
#समावेश <net/checksum.h>
#समावेश <net/dsfield.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/udp.h>
#समावेश <net/dst_metadata.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक ip_tunnel_hash(__be32 key, __be32 remote)
अणु
	वापस hash_32((__क्रमce u32)key ^ (__क्रमce u32)remote,
			 IP_TNL_HASH_BITS);
पूर्ण

अटल bool ip_tunnel_key_match(स्थिर काष्ठा ip_tunnel_parm *p,
				__be16 flags, __be32 key)
अणु
	अगर (p->i_flags & TUNNEL_KEY) अणु
		अगर (flags & TUNNEL_KEY)
			वापस key == p->i_key;
		अन्यथा
			/* key expected, none present */
			वापस false;
	पूर्ण अन्यथा
		वापस !(flags & TUNNEL_KEY);
पूर्ण

/* Fallback tunnel: no source, no destination, no key, no options

   Tunnel hash table:
   We require exact key match i.e. अगर a key is present in packet
   it will match only tunnel with the same key; अगर it is not present,
   it will match only keyless tunnel.

   All keysless packets, अगर not matched configured keyless tunnels
   will match fallback tunnel.
   Given src, dst and key, find appropriate क्रम input tunnel.
*/
काष्ठा ip_tunnel *ip_tunnel_lookup(काष्ठा ip_tunnel_net *itn,
				   पूर्णांक link, __be16 flags,
				   __be32 remote, __be32 local,
				   __be32 key)
अणु
	काष्ठा ip_tunnel *t, *cand = शून्य;
	काष्ठा hlist_head *head;
	काष्ठा net_device *ndev;
	अचिन्हित पूर्णांक hash;

	hash = ip_tunnel_hash(key, remote);
	head = &itn->tunnels[hash];

	hlist_क्रम_each_entry_rcu(t, head, hash_node) अणु
		अगर (local != t->parms.iph.saddr ||
		    remote != t->parms.iph.daddr ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (!ip_tunnel_key_match(&t->parms, flags, key))
			जारी;

		अगर (t->parms.link == link)
			वापस t;
		अन्यथा
			cand = t;
	पूर्ण

	hlist_क्रम_each_entry_rcu(t, head, hash_node) अणु
		अगर (remote != t->parms.iph.daddr ||
		    t->parms.iph.saddr != 0 ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (!ip_tunnel_key_match(&t->parms, flags, key))
			जारी;

		अगर (t->parms.link == link)
			वापस t;
		अन्यथा अगर (!cand)
			cand = t;
	पूर्ण

	hash = ip_tunnel_hash(key, 0);
	head = &itn->tunnels[hash];

	hlist_क्रम_each_entry_rcu(t, head, hash_node) अणु
		अगर ((local != t->parms.iph.saddr || t->parms.iph.daddr != 0) &&
		    (local != t->parms.iph.daddr || !ipv4_is_multicast(local)))
			जारी;

		अगर (!(t->dev->flags & IFF_UP))
			जारी;

		अगर (!ip_tunnel_key_match(&t->parms, flags, key))
			जारी;

		अगर (t->parms.link == link)
			वापस t;
		अन्यथा अगर (!cand)
			cand = t;
	पूर्ण

	hlist_क्रम_each_entry_rcu(t, head, hash_node) अणु
		अगर ((!(flags & TUNNEL_NO_KEY) && t->parms.i_key != key) ||
		    t->parms.iph.saddr != 0 ||
		    t->parms.iph.daddr != 0 ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (t->parms.link == link)
			वापस t;
		अन्यथा अगर (!cand)
			cand = t;
	पूर्ण

	अगर (cand)
		वापस cand;

	t = rcu_dereference(itn->collect_md_tun);
	अगर (t && t->dev->flags & IFF_UP)
		वापस t;

	ndev = READ_ONCE(itn->fb_tunnel_dev);
	अगर (ndev && ndev->flags & IFF_UP)
		वापस netdev_priv(ndev);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_lookup);

अटल काष्ठा hlist_head *ip_bucket(काष्ठा ip_tunnel_net *itn,
				    काष्ठा ip_tunnel_parm *parms)
अणु
	अचिन्हित पूर्णांक h;
	__be32 remote;
	__be32 i_key = parms->i_key;

	अगर (parms->iph.daddr && !ipv4_is_multicast(parms->iph.daddr))
		remote = parms->iph.daddr;
	अन्यथा
		remote = 0;

	अगर (!(parms->i_flags & TUNNEL_KEY) && (parms->i_flags & VTI_ISVTI))
		i_key = 0;

	h = ip_tunnel_hash(i_key, remote);
	वापस &itn->tunnels[h];
पूर्ण

अटल व्योम ip_tunnel_add(काष्ठा ip_tunnel_net *itn, काष्ठा ip_tunnel *t)
अणु
	काष्ठा hlist_head *head = ip_bucket(itn, &t->parms);

	अगर (t->collect_md)
		rcu_assign_poपूर्णांकer(itn->collect_md_tun, t);
	hlist_add_head_rcu(&t->hash_node, head);
पूर्ण

अटल व्योम ip_tunnel_del(काष्ठा ip_tunnel_net *itn, काष्ठा ip_tunnel *t)
अणु
	अगर (t->collect_md)
		rcu_assign_poपूर्णांकer(itn->collect_md_tun, शून्य);
	hlist_del_init_rcu(&t->hash_node);
पूर्ण

अटल काष्ठा ip_tunnel *ip_tunnel_find(काष्ठा ip_tunnel_net *itn,
					काष्ठा ip_tunnel_parm *parms,
					पूर्णांक type)
अणु
	__be32 remote = parms->iph.daddr;
	__be32 local = parms->iph.saddr;
	__be32 key = parms->i_key;
	__be16 flags = parms->i_flags;
	पूर्णांक link = parms->link;
	काष्ठा ip_tunnel *t = शून्य;
	काष्ठा hlist_head *head = ip_bucket(itn, parms);

	hlist_क्रम_each_entry_rcu(t, head, hash_node) अणु
		अगर (local == t->parms.iph.saddr &&
		    remote == t->parms.iph.daddr &&
		    link == t->parms.link &&
		    type == t->dev->type &&
		    ip_tunnel_key_match(&t->parms, flags, key))
			अवरोध;
	पूर्ण
	वापस t;
पूर्ण

अटल काष्ठा net_device *__ip_tunnel_create(काष्ठा net *net,
					     स्थिर काष्ठा rtnl_link_ops *ops,
					     काष्ठा ip_tunnel_parm *parms)
अणु
	पूर्णांक err;
	काष्ठा ip_tunnel *tunnel;
	काष्ठा net_device *dev;
	अक्षर name[IFNAMSIZ];

	err = -E2BIG;
	अगर (parms->name[0]) अणु
		अगर (!dev_valid_name(parms->name))
			जाओ failed;
		strlcpy(name, parms->name, IFNAMSIZ);
	पूर्ण अन्यथा अणु
		अगर (म_माप(ops->kind) > (IFNAMSIZ - 3))
			जाओ failed;
		म_नकल(name, ops->kind);
		म_जोड़ो(name, "%d");
	पूर्ण

	ASSERT_RTNL();
	dev = alloc_netdev(ops->priv_size, name, NET_NAME_UNKNOWN, ops->setup);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ failed;
	पूर्ण
	dev_net_set(dev, net);

	dev->rtnl_link_ops = ops;

	tunnel = netdev_priv(dev);
	tunnel->parms = *parms;
	tunnel->net = net;

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		जाओ failed_मुक्त;

	वापस dev;

failed_मुक्त:
	मुक्त_netdev(dev);
failed:
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक ip_tunnel_bind_dev(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *tdev = शून्य;
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	स्थिर काष्ठा iphdr *iph;
	पूर्णांक hlen = LL_MAX_HEADER;
	पूर्णांक mtu = ETH_DATA_LEN;
	पूर्णांक t_hlen = tunnel->hlen + माप(काष्ठा iphdr);

	iph = &tunnel->parms.iph;

	/* Guess output device to choose reasonable mtu and needed_headroom */
	अगर (iph->daddr) अणु
		काष्ठा flowi4 fl4;
		काष्ठा rtable *rt;

		ip_tunnel_init_flow(&fl4, iph->protocol, iph->daddr,
				    iph->saddr, tunnel->parms.o_key,
				    RT_TOS(iph->tos), tunnel->parms.link,
				    tunnel->fwmark, 0);
		rt = ip_route_output_key(tunnel->net, &fl4);

		अगर (!IS_ERR(rt)) अणु
			tdev = rt->dst.dev;
			ip_rt_put(rt);
		पूर्ण
		अगर (dev->type != ARPHRD_ETHER)
			dev->flags |= IFF_POINTOPOINT;

		dst_cache_reset(&tunnel->dst_cache);
	पूर्ण

	अगर (!tdev && tunnel->parms.link)
		tdev = __dev_get_by_index(tunnel->net, tunnel->parms.link);

	अगर (tdev) अणु
		hlen = tdev->hard_header_len + tdev->needed_headroom;
		mtu = min(tdev->mtu, IP_MAX_MTU);
	पूर्ण

	dev->needed_headroom = t_hlen + hlen;
	mtu -= t_hlen;

	अगर (mtu < IPV4_MIN_MTU)
		mtu = IPV4_MIN_MTU;

	वापस mtu;
पूर्ण

अटल काष्ठा ip_tunnel *ip_tunnel_create(काष्ठा net *net,
					  काष्ठा ip_tunnel_net *itn,
					  काष्ठा ip_tunnel_parm *parms)
अणु
	काष्ठा ip_tunnel *nt;
	काष्ठा net_device *dev;
	पूर्णांक t_hlen;
	पूर्णांक mtu;
	पूर्णांक err;

	dev = __ip_tunnel_create(net, itn->rtnl_link_ops, parms);
	अगर (IS_ERR(dev))
		वापस ERR_CAST(dev);

	mtu = ip_tunnel_bind_dev(dev);
	err = dev_set_mtu(dev, mtu);
	अगर (err)
		जाओ err_dev_set_mtu;

	nt = netdev_priv(dev);
	t_hlen = nt->hlen + माप(काष्ठा iphdr);
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - t_hlen;
	ip_tunnel_add(itn, nt);
	वापस nt;

err_dev_set_mtu:
	unरेजिस्टर_netdevice(dev);
	वापस ERR_PTR(err);
पूर्ण

पूर्णांक ip_tunnel_rcv(काष्ठा ip_tunnel *tunnel, काष्ठा sk_buff *skb,
		  स्थिर काष्ठा tnl_ptk_info *tpi, काष्ठा metadata_dst *tun_dst,
		  bool log_ecn_error)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	पूर्णांक err;

#अगर_घोषित CONFIG_NET_IPGRE_BROADCAST
	अगर (ipv4_is_multicast(iph->daddr)) अणु
		tunnel->dev->stats.multicast++;
		skb->pkt_type = PACKET_BROADCAST;
	पूर्ण
#पूर्ण_अगर

	अगर ((!(tpi->flags&TUNNEL_CSUM) &&  (tunnel->parms.i_flags&TUNNEL_CSUM)) ||
	     ((tpi->flags&TUNNEL_CSUM) && !(tunnel->parms.i_flags&TUNNEL_CSUM))) अणु
		tunnel->dev->stats.rx_crc_errors++;
		tunnel->dev->stats.rx_errors++;
		जाओ drop;
	पूर्ण

	अगर (tunnel->parms.i_flags&TUNNEL_SEQ) अणु
		अगर (!(tpi->flags&TUNNEL_SEQ) ||
		    (tunnel->i_seqno && (s32)(ntohl(tpi->seq) - tunnel->i_seqno) < 0)) अणु
			tunnel->dev->stats.rx_fअगरo_errors++;
			tunnel->dev->stats.rx_errors++;
			जाओ drop;
		पूर्ण
		tunnel->i_seqno = ntohl(tpi->seq) + 1;
	पूर्ण

	skb_reset_network_header(skb);

	err = IP_ECN_decapsulate(iph, skb);
	अगर (unlikely(err)) अणु
		अगर (log_ecn_error)
			net_info_ratelimited("non-ECT from %pI4 with TOS=%#x\n",
					&iph->saddr, iph->tos);
		अगर (err > 1) अणु
			++tunnel->dev->stats.rx_frame_errors;
			++tunnel->dev->stats.rx_errors;
			जाओ drop;
		पूर्ण
	पूर्ण

	dev_sw_netstats_rx_add(tunnel->dev, skb->len);
	skb_scrub_packet(skb, !net_eq(tunnel->net, dev_net(tunnel->dev)));

	अगर (tunnel->dev->type == ARPHRD_ETHER) अणु
		skb->protocol = eth_type_trans(skb, tunnel->dev);
		skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);
	पूर्ण अन्यथा अणु
		skb->dev = tunnel->dev;
	पूर्ण

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
EXPORT_SYMBOL_GPL(ip_tunnel_rcv);

पूर्णांक ip_tunnel_encap_add_ops(स्थिर काष्ठा ip_tunnel_encap_ops *ops,
			    अचिन्हित पूर्णांक num)
अणु
	अगर (num >= MAX_IPTUN_ENCAP_OPS)
		वापस -दुस्फल;

	वापस !cmpxchg((स्थिर काष्ठा ip_tunnel_encap_ops **)
			&iptun_encaps[num],
			शून्य, ops) ? 0 : -1;
पूर्ण
EXPORT_SYMBOL(ip_tunnel_encap_add_ops);

पूर्णांक ip_tunnel_encap_del_ops(स्थिर काष्ठा ip_tunnel_encap_ops *ops,
			    अचिन्हित पूर्णांक num)
अणु
	पूर्णांक ret;

	अगर (num >= MAX_IPTUN_ENCAP_OPS)
		वापस -दुस्फल;

	ret = (cmpxchg((स्थिर काष्ठा ip_tunnel_encap_ops **)
		       &iptun_encaps[num],
		       ops, शून्य) == ops) ? 0 : -1;

	synchronize_net();

	वापस ret;
पूर्ण
EXPORT_SYMBOL(ip_tunnel_encap_del_ops);

पूर्णांक ip_tunnel_encap_setup(काष्ठा ip_tunnel *t,
			  काष्ठा ip_tunnel_encap *ipencap)
अणु
	पूर्णांक hlen;

	स_रखो(&t->encap, 0, माप(t->encap));

	hlen = ip_encap_hlen(ipencap);
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
EXPORT_SYMBOL_GPL(ip_tunnel_encap_setup);

अटल पूर्णांक tnl_update_pmtu(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			    काष्ठा rtable *rt, __be16 df,
			    स्थिर काष्ठा iphdr *inner_iph,
			    पूर्णांक tunnel_hlen, __be32 dst, bool md)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	पूर्णांक pkt_size;
	पूर्णांक mtu;

	tunnel_hlen = md ? tunnel_hlen : tunnel->hlen;
	pkt_size = skb->len - tunnel_hlen;

	अगर (df)
		mtu = dst_mtu(&rt->dst) - (माप(काष्ठा iphdr) + tunnel_hlen);
	अन्यथा
		mtu = skb_valid_dst(skb) ? dst_mtu(skb_dst(skb)) : dev->mtu;

	अगर (skb_valid_dst(skb))
		skb_dst_update_pmtu_no_confirm(skb, mtu);

	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		अगर (!skb_is_gso(skb) &&
		    (inner_iph->frag_off & htons(IP_DF)) &&
		    mtu < pkt_size) अणु
			icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED, htonl(mtu));
			वापस -E2BIG;
		पूर्ण
	पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		काष्ठा rt6_info *rt6;
		__be32 daddr;

		rt6 = skb_valid_dst(skb) ? (काष्ठा rt6_info *)skb_dst(skb) :
					   शून्य;
		daddr = md ? dst : tunnel->parms.iph.daddr;

		अगर (rt6 && mtu < dst_mtu(skb_dst(skb)) &&
			   mtu >= IPV6_MIN_MTU) अणु
			अगर ((daddr && !ipv4_is_multicast(daddr)) ||
			    rt6->rt6i_dst.plen == 128) अणु
				rt6->rt6i_flags |= RTF_MODIFIED;
				dst_metric_set(skb_dst(skb), RTAX_MTU, mtu);
			पूर्ण
		पूर्ण

		अगर (!skb_is_gso(skb) && mtu >= IPV6_MIN_MTU &&
					mtu < pkt_size) अणु
			icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
			वापस -E2BIG;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

व्योम ip_md_tunnel_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		       u8 proto, पूर्णांक tunnel_hlen)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	u32 headroom = माप(काष्ठा iphdr);
	काष्ठा ip_tunnel_info *tun_info;
	स्थिर काष्ठा ip_tunnel_key *key;
	स्थिर काष्ठा iphdr *inner_iph;
	काष्ठा rtable *rt = शून्य;
	काष्ठा flowi4 fl4;
	__be16 df = 0;
	u8 tos, ttl;
	bool use_cache;

	tun_info = skb_tunnel_info(skb);
	अगर (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX) ||
		     ip_tunnel_info_af(tun_info) != AF_INET))
		जाओ tx_error;
	key = &tun_info->key;
	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));
	inner_iph = (स्थिर काष्ठा iphdr *)skb_inner_network_header(skb);
	tos = key->tos;
	अगर (tos == 1) अणु
		अगर (skb->protocol == htons(ETH_P_IP))
			tos = inner_iph->tos;
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			tos = ipv6_get_dsfield((स्थिर काष्ठा ipv6hdr *)inner_iph);
	पूर्ण
	ip_tunnel_init_flow(&fl4, proto, key->u.ipv4.dst, key->u.ipv4.src,
			    tunnel_id_to_key32(key->tun_id), RT_TOS(tos),
			    0, skb->mark, skb_get_hash(skb));
	अगर (tunnel->encap.type != TUNNEL_ENCAP_NONE)
		जाओ tx_error;

	use_cache = ip_tunnel_dst_cache_usable(skb, tun_info);
	अगर (use_cache)
		rt = dst_cache_get_ip4(&tun_info->dst_cache, &fl4.saddr);
	अगर (!rt) अणु
		rt = ip_route_output_key(tunnel->net, &fl4);
		अगर (IS_ERR(rt)) अणु
			dev->stats.tx_carrier_errors++;
			जाओ tx_error;
		पूर्ण
		अगर (use_cache)
			dst_cache_set_ip4(&tun_info->dst_cache, &rt->dst,
					  fl4.saddr);
	पूर्ण
	अगर (rt->dst.dev == dev) अणु
		ip_rt_put(rt);
		dev->stats.collisions++;
		जाओ tx_error;
	पूर्ण

	अगर (key->tun_flags & TUNNEL_DONT_FRAGMENT)
		df = htons(IP_DF);
	अगर (tnl_update_pmtu(dev, skb, rt, df, inner_iph, tunnel_hlen,
			    key->u.ipv4.dst, true)) अणु
		ip_rt_put(rt);
		जाओ tx_error;
	पूर्ण

	tos = ip_tunnel_ecn_encap(tos, inner_iph, skb);
	ttl = key->ttl;
	अगर (ttl == 0) अणु
		अगर (skb->protocol == htons(ETH_P_IP))
			ttl = inner_iph->ttl;
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			ttl = ((स्थिर काष्ठा ipv6hdr *)inner_iph)->hop_limit;
		अन्यथा
			ttl = ip4_dst_hoplimit(&rt->dst);
	पूर्ण

	headroom += LL_RESERVED_SPACE(rt->dst.dev) + rt->dst.header_len;
	अगर (headroom > dev->needed_headroom)
		dev->needed_headroom = headroom;

	अगर (skb_cow_head(skb, dev->needed_headroom)) अणु
		ip_rt_put(rt);
		जाओ tx_dropped;
	पूर्ण
	iptunnel_xmit(शून्य, rt, skb, fl4.saddr, fl4.daddr, proto, tos, ttl,
		      df, !net_eq(tunnel->net, dev_net(dev)));
	वापस;
tx_error:
	dev->stats.tx_errors++;
	जाओ kमुक्त;
tx_dropped:
	dev->stats.tx_dropped++;
kमुक्त:
	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(ip_md_tunnel_xmit);

व्योम ip_tunnel_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		    स्थिर काष्ठा iphdr *tnl_params, u8 protocol)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा ip_tunnel_info *tun_info = शून्य;
	स्थिर काष्ठा iphdr *inner_iph;
	अचिन्हित पूर्णांक max_headroom;	/* The extra header space needed */
	काष्ठा rtable *rt = शून्य;		/* Route to the other host */
	bool use_cache = false;
	काष्ठा flowi4 fl4;
	bool md = false;
	bool connected;
	u8 tos, ttl;
	__be32 dst;
	__be16 df;

	inner_iph = (स्थिर काष्ठा iphdr *)skb_inner_network_header(skb);
	connected = (tunnel->parms.iph.daddr != 0);

	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));

	dst = tnl_params->daddr;
	अगर (dst == 0) अणु
		/* NBMA tunnel */

		अगर (!skb_dst(skb)) अणु
			dev->stats.tx_fअगरo_errors++;
			जाओ tx_error;
		पूर्ण

		tun_info = skb_tunnel_info(skb);
		अगर (tun_info && (tun_info->mode & IP_TUNNEL_INFO_TX) &&
		    ip_tunnel_info_af(tun_info) == AF_INET &&
		    tun_info->key.u.ipv4.dst) अणु
			dst = tun_info->key.u.ipv4.dst;
			md = true;
			connected = true;
		पूर्ण
		अन्यथा अगर (skb->protocol == htons(ETH_P_IP)) अणु
			rt = skb_rtable(skb);
			dst = rt_nexthop(rt, inner_iph->daddr);
		पूर्ण
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			स्थिर काष्ठा in6_addr *addr6;
			काष्ठा neighbour *neigh;
			bool करो_tx_error_icmp;
			पूर्णांक addr_type;

			neigh = dst_neigh_lookup(skb_dst(skb),
						 &ipv6_hdr(skb)->daddr);
			अगर (!neigh)
				जाओ tx_error;

			addr6 = (स्थिर काष्ठा in6_addr *)&neigh->primary_key;
			addr_type = ipv6_addr_type(addr6);

			अगर (addr_type == IPV6_ADDR_ANY) अणु
				addr6 = &ipv6_hdr(skb)->daddr;
				addr_type = ipv6_addr_type(addr6);
			पूर्ण

			अगर ((addr_type & IPV6_ADDR_COMPATv4) == 0)
				करो_tx_error_icmp = true;
			अन्यथा अणु
				करो_tx_error_icmp = false;
				dst = addr6->s6_addr32[3];
			पूर्ण
			neigh_release(neigh);
			अगर (करो_tx_error_icmp)
				जाओ tx_error_icmp;
		पूर्ण
#पूर्ण_अगर
		अन्यथा
			जाओ tx_error;

		अगर (!md)
			connected = false;
	पूर्ण

	tos = tnl_params->tos;
	अगर (tos & 0x1) अणु
		tos &= ~0x1;
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			tos = inner_iph->tos;
			connected = false;
		पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
			tos = ipv6_get_dsfield((स्थिर काष्ठा ipv6hdr *)inner_iph);
			connected = false;
		पूर्ण
	पूर्ण

	ip_tunnel_init_flow(&fl4, protocol, dst, tnl_params->saddr,
			    tunnel->parms.o_key, RT_TOS(tos), tunnel->parms.link,
			    tunnel->fwmark, skb_get_hash(skb));

	अगर (ip_tunnel_encap(skb, tunnel, &protocol, &fl4) < 0)
		जाओ tx_error;

	अगर (connected && md) अणु
		use_cache = ip_tunnel_dst_cache_usable(skb, tun_info);
		अगर (use_cache)
			rt = dst_cache_get_ip4(&tun_info->dst_cache,
					       &fl4.saddr);
	पूर्ण अन्यथा अणु
		rt = connected ? dst_cache_get_ip4(&tunnel->dst_cache,
						&fl4.saddr) : शून्य;
	पूर्ण

	अगर (!rt) अणु
		rt = ip_route_output_key(tunnel->net, &fl4);

		अगर (IS_ERR(rt)) अणु
			dev->stats.tx_carrier_errors++;
			जाओ tx_error;
		पूर्ण
		अगर (use_cache)
			dst_cache_set_ip4(&tun_info->dst_cache, &rt->dst,
					  fl4.saddr);
		अन्यथा अगर (!md && connected)
			dst_cache_set_ip4(&tunnel->dst_cache, &rt->dst,
					  fl4.saddr);
	पूर्ण

	अगर (rt->dst.dev == dev) अणु
		ip_rt_put(rt);
		dev->stats.collisions++;
		जाओ tx_error;
	पूर्ण

	df = tnl_params->frag_off;
	अगर (skb->protocol == htons(ETH_P_IP) && !tunnel->ignore_df)
		df |= (inner_iph->frag_off & htons(IP_DF));

	अगर (tnl_update_pmtu(dev, skb, rt, df, inner_iph, 0, 0, false)) अणु
		ip_rt_put(rt);
		जाओ tx_error;
	पूर्ण

	अगर (tunnel->err_count > 0) अणु
		अगर (समय_beक्रमe(jअगरfies,
				tunnel->err_समय + IPTUNNEL_ERR_TIMEO)) अणु
			tunnel->err_count--;

			dst_link_failure(skb);
		पूर्ण अन्यथा
			tunnel->err_count = 0;
	पूर्ण

	tos = ip_tunnel_ecn_encap(tos, inner_iph, skb);
	ttl = tnl_params->ttl;
	अगर (ttl == 0) अणु
		अगर (skb->protocol == htons(ETH_P_IP))
			ttl = inner_iph->ttl;
#अगर IS_ENABLED(CONFIG_IPV6)
		अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
			ttl = ((स्थिर काष्ठा ipv6hdr *)inner_iph)->hop_limit;
#पूर्ण_अगर
		अन्यथा
			ttl = ip4_dst_hoplimit(&rt->dst);
	पूर्ण

	max_headroom = LL_RESERVED_SPACE(rt->dst.dev) + माप(काष्ठा iphdr)
			+ rt->dst.header_len + ip_encap_hlen(&tunnel->encap);
	अगर (max_headroom > dev->needed_headroom)
		dev->needed_headroom = max_headroom;

	अगर (skb_cow_head(skb, dev->needed_headroom)) अणु
		ip_rt_put(rt);
		dev->stats.tx_dropped++;
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	iptunnel_xmit(शून्य, rt, skb, fl4.saddr, fl4.daddr, protocol, tos, ttl,
		      df, !net_eq(tunnel->net, dev_net(dev)));
	वापस;

#अगर IS_ENABLED(CONFIG_IPV6)
tx_error_icmp:
	dst_link_failure(skb);
#पूर्ण_अगर
tx_error:
	dev->stats.tx_errors++;
	kमुक्त_skb(skb);
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_xmit);

अटल व्योम ip_tunnel_update(काष्ठा ip_tunnel_net *itn,
			     काष्ठा ip_tunnel *t,
			     काष्ठा net_device *dev,
			     काष्ठा ip_tunnel_parm *p,
			     bool set_mtu,
			     __u32 fwmark)
अणु
	ip_tunnel_del(itn, t);
	t->parms.iph.saddr = p->iph.saddr;
	t->parms.iph.daddr = p->iph.daddr;
	t->parms.i_key = p->i_key;
	t->parms.o_key = p->o_key;
	अगर (dev->type != ARPHRD_ETHER) अणु
		स_नकल(dev->dev_addr, &p->iph.saddr, 4);
		स_नकल(dev->broadcast, &p->iph.daddr, 4);
	पूर्ण
	ip_tunnel_add(itn, t);

	t->parms.iph.ttl = p->iph.ttl;
	t->parms.iph.tos = p->iph.tos;
	t->parms.iph.frag_off = p->iph.frag_off;

	अगर (t->parms.link != p->link || t->fwmark != fwmark) अणु
		पूर्णांक mtu;

		t->parms.link = p->link;
		t->fwmark = fwmark;
		mtu = ip_tunnel_bind_dev(dev);
		अगर (set_mtu)
			dev->mtu = mtu;
	पूर्ण
	dst_cache_reset(&t->dst_cache);
	netdev_state_change(dev);
पूर्ण

पूर्णांक ip_tunnel_ctl(काष्ठा net_device *dev, काष्ठा ip_tunnel_parm *p, पूर्णांक cmd)
अणु
	पूर्णांक err = 0;
	काष्ठा ip_tunnel *t = netdev_priv(dev);
	काष्ठा net *net = t->net;
	काष्ठा ip_tunnel_net *itn = net_generic(net, t->ip_tnl_net_id);

	चयन (cmd) अणु
	हाल SIOCGETTUNNEL:
		अगर (dev == itn->fb_tunnel_dev) अणु
			t = ip_tunnel_find(itn, p, itn->fb_tunnel_dev->type);
			अगर (!t)
				t = netdev_priv(dev);
		पूर्ण
		स_नकल(p, &t->parms, माप(*p));
		अवरोध;

	हाल SIOCADDTUNNEL:
	हाल SIOCCHGTUNNEL:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			जाओ करोne;
		अगर (p->iph.ttl)
			p->iph.frag_off |= htons(IP_DF);
		अगर (!(p->i_flags & VTI_ISVTI)) अणु
			अगर (!(p->i_flags & TUNNEL_KEY))
				p->i_key = 0;
			अगर (!(p->o_flags & TUNNEL_KEY))
				p->o_key = 0;
		पूर्ण

		t = ip_tunnel_find(itn, p, itn->type);

		अगर (cmd == SIOCADDTUNNEL) अणु
			अगर (!t) अणु
				t = ip_tunnel_create(net, itn, p);
				err = PTR_ERR_OR_ZERO(t);
				अवरोध;
			पूर्ण

			err = -EEXIST;
			अवरोध;
		पूर्ण
		अगर (dev != itn->fb_tunnel_dev && cmd == SIOCCHGTUNNEL) अणु
			अगर (t) अणु
				अगर (t->dev != dev) अणु
					err = -EEXIST;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक nflags = 0;

				अगर (ipv4_is_multicast(p->iph.daddr))
					nflags = IFF_BROADCAST;
				अन्यथा अगर (p->iph.daddr)
					nflags = IFF_POINTOPOINT;

				अगर ((dev->flags^nflags)&(IFF_POINTOPOINT|IFF_BROADCAST)) अणु
					err = -EINVAL;
					अवरोध;
				पूर्ण

				t = netdev_priv(dev);
			पूर्ण
		पूर्ण

		अगर (t) अणु
			err = 0;
			ip_tunnel_update(itn, t, dev, p, true, 0);
		पूर्ण अन्यथा अणु
			err = -ENOENT;
		पूर्ण
		अवरोध;

	हाल SIOCDELTUNNEL:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			जाओ करोne;

		अगर (dev == itn->fb_tunnel_dev) अणु
			err = -ENOENT;
			t = ip_tunnel_find(itn, p, itn->fb_tunnel_dev->type);
			अगर (!t)
				जाओ करोne;
			err = -EPERM;
			अगर (t == netdev_priv(itn->fb_tunnel_dev))
				जाओ करोne;
			dev = t->dev;
		पूर्ण
		unरेजिस्टर_netdevice(dev);
		err = 0;
		अवरोध;

	शेष:
		err = -EINVAL;
	पूर्ण

करोne:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_ctl);

पूर्णांक ip_tunnel_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा ip_tunnel_parm p;
	पूर्णांक err;

	अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p)))
		वापस -EFAULT;
	err = dev->netdev_ops->nकरो_tunnel_ctl(dev, &p, cmd);
	अगर (!err && copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &p, माप(p)))
		वापस -EFAULT;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_ioctl);

पूर्णांक __ip_tunnel_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu, bool strict)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	पूर्णांक t_hlen = tunnel->hlen + माप(काष्ठा iphdr);
	पूर्णांक max_mtu = IP_MAX_MTU - t_hlen;

	अगर (new_mtu < ETH_MIN_MTU)
		वापस -EINVAL;

	अगर (new_mtu > max_mtu) अणु
		अगर (strict)
			वापस -EINVAL;

		new_mtu = max_mtu;
	पूर्ण

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__ip_tunnel_change_mtu);

पूर्णांक ip_tunnel_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	वापस __ip_tunnel_change_mtu(dev, new_mtu, true);
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_change_mtu);

अटल व्योम ip_tunnel_dev_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	gro_cells_destroy(&tunnel->gro_cells);
	dst_cache_destroy(&tunnel->dst_cache);
	मुक्त_percpu(dev->tstats);
पूर्ण

व्योम ip_tunnel_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा ip_tunnel_net *itn;

	itn = net_generic(tunnel->net, tunnel->ip_tnl_net_id);

	अगर (itn->fb_tunnel_dev != dev) अणु
		ip_tunnel_del(itn, netdev_priv(dev));
		unरेजिस्टर_netdevice_queue(dev, head);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_dellink);

काष्ठा net *ip_tunnel_get_link_net(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	वापस tunnel->net;
पूर्ण
EXPORT_SYMBOL(ip_tunnel_get_link_net);

पूर्णांक ip_tunnel_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);

	वापस tunnel->parms.link;
पूर्ण
EXPORT_SYMBOL(ip_tunnel_get_अगरlink);

पूर्णांक ip_tunnel_init_net(काष्ठा net *net, अचिन्हित पूर्णांक ip_tnl_net_id,
				  काष्ठा rtnl_link_ops *ops, अक्षर *devname)
अणु
	काष्ठा ip_tunnel_net *itn = net_generic(net, ip_tnl_net_id);
	काष्ठा ip_tunnel_parm parms;
	अचिन्हित पूर्णांक i;

	itn->rtnl_link_ops = ops;
	क्रम (i = 0; i < IP_TNL_HASH_SIZE; i++)
		INIT_HLIST_HEAD(&itn->tunnels[i]);

	अगर (!ops || !net_has_fallback_tunnels(net)) अणु
		काष्ठा ip_tunnel_net *it_init_net;

		it_init_net = net_generic(&init_net, ip_tnl_net_id);
		itn->type = it_init_net->type;
		itn->fb_tunnel_dev = शून्य;
		वापस 0;
	पूर्ण

	स_रखो(&parms, 0, माप(parms));
	अगर (devname)
		strlcpy(parms.name, devname, IFNAMSIZ);

	rtnl_lock();
	itn->fb_tunnel_dev = __ip_tunnel_create(net, ops, &parms);
	/* FB netdevice is special: we have one, and only one per netns.
	 * Allowing to move it to another netns is clearly unsafe.
	 */
	अगर (!IS_ERR(itn->fb_tunnel_dev)) अणु
		itn->fb_tunnel_dev->features |= NETIF_F_NETNS_LOCAL;
		itn->fb_tunnel_dev->mtu = ip_tunnel_bind_dev(itn->fb_tunnel_dev);
		ip_tunnel_add(itn, netdev_priv(itn->fb_tunnel_dev));
		itn->type = itn->fb_tunnel_dev->type;
	पूर्ण
	rtnl_unlock();

	वापस PTR_ERR_OR_ZERO(itn->fb_tunnel_dev);
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_init_net);

अटल व्योम ip_tunnel_destroy(काष्ठा net *net, काष्ठा ip_tunnel_net *itn,
			      काष्ठा list_head *head,
			      काष्ठा rtnl_link_ops *ops)
अणु
	काष्ठा net_device *dev, *aux;
	पूर्णांक h;

	क्रम_each_netdev_safe(net, dev, aux)
		अगर (dev->rtnl_link_ops == ops)
			unरेजिस्टर_netdevice_queue(dev, head);

	क्रम (h = 0; h < IP_TNL_HASH_SIZE; h++) अणु
		काष्ठा ip_tunnel *t;
		काष्ठा hlist_node *n;
		काष्ठा hlist_head *thead = &itn->tunnels[h];

		hlist_क्रम_each_entry_safe(t, n, thead, hash_node)
			/* If dev is in the same netns, it has alपढ़ोy
			 * been added to the list by the previous loop.
			 */
			अगर (!net_eq(dev_net(t->dev), net))
				unरेजिस्टर_netdevice_queue(t->dev, head);
	पूर्ण
पूर्ण

व्योम ip_tunnel_delete_nets(काष्ठा list_head *net_list, अचिन्हित पूर्णांक id,
			   काष्ठा rtnl_link_ops *ops)
अणु
	काष्ठा ip_tunnel_net *itn;
	काष्ठा net *net;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list) अणु
		itn = net_generic(net, id);
		ip_tunnel_destroy(net, itn, &list, ops);
	पूर्ण
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_delete_nets);

पूर्णांक ip_tunnel_newlink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
		      काष्ठा ip_tunnel_parm *p, __u32 fwmark)
अणु
	काष्ठा ip_tunnel *nt;
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip_tunnel_net *itn;
	पूर्णांक mtu;
	पूर्णांक err;

	nt = netdev_priv(dev);
	itn = net_generic(net, nt->ip_tnl_net_id);

	अगर (nt->collect_md) अणु
		अगर (rtnl_dereference(itn->collect_md_tun))
			वापस -EEXIST;
	पूर्ण अन्यथा अणु
		अगर (ip_tunnel_find(itn, p, dev->type))
			वापस -EEXIST;
	पूर्ण

	nt->net = net;
	nt->parms = *p;
	nt->fwmark = fwmark;
	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		जाओ err_रेजिस्टर_netdevice;

	अगर (dev->type == ARPHRD_ETHER && !tb[IFLA_ADDRESS])
		eth_hw_addr_अक्रमom(dev);

	mtu = ip_tunnel_bind_dev(dev);
	अगर (tb[IFLA_MTU]) अणु
		अचिन्हित पूर्णांक max = IP_MAX_MTU - (nt->hlen + माप(काष्ठा iphdr));

		mtu = clamp(dev->mtu, (अचिन्हित पूर्णांक)ETH_MIN_MTU, max);
	पूर्ण

	err = dev_set_mtu(dev, mtu);
	अगर (err)
		जाओ err_dev_set_mtu;

	ip_tunnel_add(itn, nt);
	वापस 0;

err_dev_set_mtu:
	unरेजिस्टर_netdevice(dev);
err_रेजिस्टर_netdevice:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_newlink);

पूर्णांक ip_tunnel_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			 काष्ठा ip_tunnel_parm *p, __u32 fwmark)
अणु
	काष्ठा ip_tunnel *t;
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा net *net = tunnel->net;
	काष्ठा ip_tunnel_net *itn = net_generic(net, tunnel->ip_tnl_net_id);

	अगर (dev == itn->fb_tunnel_dev)
		वापस -EINVAL;

	t = ip_tunnel_find(itn, p, dev->type);

	अगर (t) अणु
		अगर (t->dev != dev)
			वापस -EEXIST;
	पूर्ण अन्यथा अणु
		t = tunnel;

		अगर (dev->type != ARPHRD_ETHER) अणु
			अचिन्हित पूर्णांक nflags = 0;

			अगर (ipv4_is_multicast(p->iph.daddr))
				nflags = IFF_BROADCAST;
			अन्यथा अगर (p->iph.daddr)
				nflags = IFF_POINTOPOINT;

			अगर ((dev->flags ^ nflags) &
			    (IFF_POINTOPOINT | IFF_BROADCAST))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	ip_tunnel_update(itn, t, dev, p, !tb[IFLA_MTU], fwmark);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_changelink);

पूर्णांक ip_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा iphdr *iph = &tunnel->parms.iph;
	पूर्णांक err;

	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = ip_tunnel_dev_मुक्त;
	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	err = dst_cache_init(&tunnel->dst_cache, GFP_KERNEL);
	अगर (err) अणु
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण

	err = gro_cells_init(&tunnel->gro_cells, dev);
	अगर (err) अणु
		dst_cache_destroy(&tunnel->dst_cache);
		मुक्त_percpu(dev->tstats);
		वापस err;
	पूर्ण

	tunnel->dev = dev;
	tunnel->net = dev_net(dev);
	म_नकल(tunnel->parms.name, dev->name);
	iph->version		= 4;
	iph->ihl		= 5;

	अगर (tunnel->collect_md)
		netअगर_keep_dst(dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_init);

व्योम ip_tunnel_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	काष्ठा net *net = tunnel->net;
	काष्ठा ip_tunnel_net *itn;

	itn = net_generic(net, tunnel->ip_tnl_net_id);
	ip_tunnel_del(itn, netdev_priv(dev));
	अगर (itn->fb_tunnel_dev == dev)
		WRITE_ONCE(itn->fb_tunnel_dev, शून्य);

	dst_cache_reset(&tunnel->dst_cache);
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_uninit);

/* Do least required initialization, rest of init is करोne in tunnel_init call */
व्योम ip_tunnel_setup(काष्ठा net_device *dev, अचिन्हित पूर्णांक net_id)
अणु
	काष्ठा ip_tunnel *tunnel = netdev_priv(dev);
	tunnel->ip_tnl_net_id = net_id;
पूर्ण
EXPORT_SYMBOL_GPL(ip_tunnel_setup);

MODULE_LICENSE("GPL");
