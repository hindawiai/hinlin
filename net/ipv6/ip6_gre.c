<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	GRE over IPv6 protocol decoder.
 *
 *	Authors: Dmitry Kozlov (xeb@mail.ru)
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
#समावेश <linux/hash.h>
#समावेश <linux/अगर_tunnel.h>
#समावेश <linux/ip6_tunnel.h>

#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/icmp.h>
#समावेश <net/protocol.h>
#समावेश <net/addrconf.h>
#समावेश <net/arp.h>
#समावेश <net/checksum.h>
#समावेश <net/dsfield.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <net/rtnetlink.h>

#समावेश <net/ipv6.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip6_tunnel.h>
#समावेश <net/gre.h>
#समावेश <net/erspan.h>
#समावेश <net/dst_metadata.h>


अटल bool log_ecn_error = true;
module_param(log_ecn_error, bool, 0644);
MODULE_PARM_DESC(log_ecn_error, "Log packets received with corrupted ECN");

#घोषणा IP6_GRE_HASH_SIZE_SHIFT  5
#घोषणा IP6_GRE_HASH_SIZE (1 << IP6_GRE_HASH_SIZE_SHIFT)

अटल अचिन्हित पूर्णांक ip6gre_net_id __पढ़ो_mostly;
काष्ठा ip6gre_net अणु
	काष्ठा ip6_tnl __rcu *tunnels[4][IP6_GRE_HASH_SIZE];

	काष्ठा ip6_tnl __rcu *collect_md_tun;
	काष्ठा ip6_tnl __rcu *collect_md_tun_erspan;
	काष्ठा net_device *fb_tunnel_dev;
पूर्ण;

अटल काष्ठा rtnl_link_ops ip6gre_link_ops __पढ़ो_mostly;
अटल काष्ठा rtnl_link_ops ip6gre_tap_ops __पढ़ो_mostly;
अटल काष्ठा rtnl_link_ops ip6erspan_tap_ops __पढ़ो_mostly;
अटल पूर्णांक ip6gre_tunnel_init(काष्ठा net_device *dev);
अटल व्योम ip6gre_tunnel_setup(काष्ठा net_device *dev);
अटल व्योम ip6gre_tunnel_link(काष्ठा ip6gre_net *ign, काष्ठा ip6_tnl *t);
अटल व्योम ip6gre_tnl_link_config(काष्ठा ip6_tnl *t, पूर्णांक set_mtu);
अटल व्योम ip6erspan_tnl_link_config(काष्ठा ip6_tnl *t, पूर्णांक set_mtu);

/* Tunnel hash table */

/*
   4 hash tables:

   3: (remote,local)
   2: (remote,*)
   1: (*,local)
   0: (*,*)

   We require exact key match i.e. अगर a key is present in packet
   it will match only tunnel with the same key; अगर it is not present,
   it will match only keyless tunnel.

   All keysless packets, अगर not matched configured keyless tunnels
   will match fallback tunnel.
 */

#घोषणा HASH_KEY(key) (((__क्रमce u32)key^((__क्रमce u32)key>>4))&(IP6_GRE_HASH_SIZE - 1))
अटल u32 HASH_ADDR(स्थिर काष्ठा in6_addr *addr)
अणु
	u32 hash = ipv6_addr_hash(addr);

	वापस hash_32(hash, IP6_GRE_HASH_SIZE_SHIFT);
पूर्ण

#घोषणा tunnels_r_l	tunnels[3]
#घोषणा tunnels_r	tunnels[2]
#घोषणा tunnels_l	tunnels[1]
#घोषणा tunnels_wc	tunnels[0]

/* Given src, dst and key, find appropriate क्रम input tunnel. */

अटल काष्ठा ip6_tnl *ip6gre_tunnel_lookup(काष्ठा net_device *dev,
		स्थिर काष्ठा in6_addr *remote, स्थिर काष्ठा in6_addr *local,
		__be32 key, __be16 gre_proto)
अणु
	काष्ठा net *net = dev_net(dev);
	पूर्णांक link = dev->अगरindex;
	अचिन्हित पूर्णांक h0 = HASH_ADDR(remote);
	अचिन्हित पूर्णांक h1 = HASH_KEY(key);
	काष्ठा ip6_tnl *t, *cand = शून्य;
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);
	पूर्णांक dev_type = (gre_proto == htons(ETH_P_TEB) ||
			gre_proto == htons(ETH_P_ERSPAN) ||
			gre_proto == htons(ETH_P_ERSPAN2)) ?
		       ARPHRD_ETHER : ARPHRD_IP6GRE;
	पूर्णांक score, cand_score = 4;
	काष्ठा net_device *ndev;

	क्रम_each_ip_tunnel_rcu(t, ign->tunnels_r_l[h0 ^ h1]) अणु
		अगर (!ipv6_addr_equal(local, &t->parms.laddr) ||
		    !ipv6_addr_equal(remote, &t->parms.raddr) ||
		    key != t->parms.i_key ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (t->dev->type != ARPHRD_IP6GRE &&
		    t->dev->type != dev_type)
			जारी;

		score = 0;
		अगर (t->parms.link != link)
			score |= 1;
		अगर (t->dev->type != dev_type)
			score |= 2;
		अगर (score == 0)
			वापस t;

		अगर (score < cand_score) अणु
			cand = t;
			cand_score = score;
		पूर्ण
	पूर्ण

	क्रम_each_ip_tunnel_rcu(t, ign->tunnels_r[h0 ^ h1]) अणु
		अगर (!ipv6_addr_equal(remote, &t->parms.raddr) ||
		    key != t->parms.i_key ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (t->dev->type != ARPHRD_IP6GRE &&
		    t->dev->type != dev_type)
			जारी;

		score = 0;
		अगर (t->parms.link != link)
			score |= 1;
		अगर (t->dev->type != dev_type)
			score |= 2;
		अगर (score == 0)
			वापस t;

		अगर (score < cand_score) अणु
			cand = t;
			cand_score = score;
		पूर्ण
	पूर्ण

	क्रम_each_ip_tunnel_rcu(t, ign->tunnels_l[h1]) अणु
		अगर ((!ipv6_addr_equal(local, &t->parms.laddr) &&
			  (!ipv6_addr_equal(local, &t->parms.raddr) ||
				 !ipv6_addr_is_multicast(local))) ||
		    key != t->parms.i_key ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (t->dev->type != ARPHRD_IP6GRE &&
		    t->dev->type != dev_type)
			जारी;

		score = 0;
		अगर (t->parms.link != link)
			score |= 1;
		अगर (t->dev->type != dev_type)
			score |= 2;
		अगर (score == 0)
			वापस t;

		अगर (score < cand_score) अणु
			cand = t;
			cand_score = score;
		पूर्ण
	पूर्ण

	क्रम_each_ip_tunnel_rcu(t, ign->tunnels_wc[h1]) अणु
		अगर (t->parms.i_key != key ||
		    !(t->dev->flags & IFF_UP))
			जारी;

		अगर (t->dev->type != ARPHRD_IP6GRE &&
		    t->dev->type != dev_type)
			जारी;

		score = 0;
		अगर (t->parms.link != link)
			score |= 1;
		अगर (t->dev->type != dev_type)
			score |= 2;
		अगर (score == 0)
			वापस t;

		अगर (score < cand_score) अणु
			cand = t;
			cand_score = score;
		पूर्ण
	पूर्ण

	अगर (cand)
		वापस cand;

	अगर (gre_proto == htons(ETH_P_ERSPAN) ||
	    gre_proto == htons(ETH_P_ERSPAN2))
		t = rcu_dereference(ign->collect_md_tun_erspan);
	अन्यथा
		t = rcu_dereference(ign->collect_md_tun);

	अगर (t && t->dev->flags & IFF_UP)
		वापस t;

	ndev = READ_ONCE(ign->fb_tunnel_dev);
	अगर (ndev && ndev->flags & IFF_UP)
		वापस netdev_priv(ndev);

	वापस शून्य;
पूर्ण

अटल काष्ठा ip6_tnl __rcu **__ip6gre_bucket(काष्ठा ip6gre_net *ign,
		स्थिर काष्ठा __ip6_tnl_parm *p)
अणु
	स्थिर काष्ठा in6_addr *remote = &p->raddr;
	स्थिर काष्ठा in6_addr *local = &p->laddr;
	अचिन्हित पूर्णांक h = HASH_KEY(p->i_key);
	पूर्णांक prio = 0;

	अगर (!ipv6_addr_any(local))
		prio |= 1;
	अगर (!ipv6_addr_any(remote) && !ipv6_addr_is_multicast(remote)) अणु
		prio |= 2;
		h ^= HASH_ADDR(remote);
	पूर्ण

	वापस &ign->tunnels[prio][h];
पूर्ण

अटल व्योम ip6gre_tunnel_link_md(काष्ठा ip6gre_net *ign, काष्ठा ip6_tnl *t)
अणु
	अगर (t->parms.collect_md)
		rcu_assign_poपूर्णांकer(ign->collect_md_tun, t);
पूर्ण

अटल व्योम ip6erspan_tunnel_link_md(काष्ठा ip6gre_net *ign, काष्ठा ip6_tnl *t)
अणु
	अगर (t->parms.collect_md)
		rcu_assign_poपूर्णांकer(ign->collect_md_tun_erspan, t);
पूर्ण

अटल व्योम ip6gre_tunnel_unlink_md(काष्ठा ip6gre_net *ign, काष्ठा ip6_tnl *t)
अणु
	अगर (t->parms.collect_md)
		rcu_assign_poपूर्णांकer(ign->collect_md_tun, शून्य);
पूर्ण

अटल व्योम ip6erspan_tunnel_unlink_md(काष्ठा ip6gre_net *ign,
				       काष्ठा ip6_tnl *t)
अणु
	अगर (t->parms.collect_md)
		rcu_assign_poपूर्णांकer(ign->collect_md_tun_erspan, शून्य);
पूर्ण

अटल अंतरभूत काष्ठा ip6_tnl __rcu **ip6gre_bucket(काष्ठा ip6gre_net *ign,
		स्थिर काष्ठा ip6_tnl *t)
अणु
	वापस __ip6gre_bucket(ign, &t->parms);
पूर्ण

अटल व्योम ip6gre_tunnel_link(काष्ठा ip6gre_net *ign, काष्ठा ip6_tnl *t)
अणु
	काष्ठा ip6_tnl __rcu **tp = ip6gre_bucket(ign, t);

	rcu_assign_poपूर्णांकer(t->next, rtnl_dereference(*tp));
	rcu_assign_poपूर्णांकer(*tp, t);
पूर्ण

अटल व्योम ip6gre_tunnel_unlink(काष्ठा ip6gre_net *ign, काष्ठा ip6_tnl *t)
अणु
	काष्ठा ip6_tnl __rcu **tp;
	काष्ठा ip6_tnl *iter;

	क्रम (tp = ip6gre_bucket(ign, t);
	     (iter = rtnl_dereference(*tp)) != शून्य;
	     tp = &iter->next) अणु
		अगर (t == iter) अणु
			rcu_assign_poपूर्णांकer(*tp, t->next);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल काष्ठा ip6_tnl *ip6gre_tunnel_find(काष्ठा net *net,
					   स्थिर काष्ठा __ip6_tnl_parm *parms,
					   पूर्णांक type)
अणु
	स्थिर काष्ठा in6_addr *remote = &parms->raddr;
	स्थिर काष्ठा in6_addr *local = &parms->laddr;
	__be32 key = parms->i_key;
	पूर्णांक link = parms->link;
	काष्ठा ip6_tnl *t;
	काष्ठा ip6_tnl __rcu **tp;
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);

	क्रम (tp = __ip6gre_bucket(ign, parms);
	     (t = rtnl_dereference(*tp)) != शून्य;
	     tp = &t->next)
		अगर (ipv6_addr_equal(local, &t->parms.laddr) &&
		    ipv6_addr_equal(remote, &t->parms.raddr) &&
		    key == t->parms.i_key &&
		    link == t->parms.link &&
		    type == t->dev->type)
			अवरोध;

	वापस t;
पूर्ण

अटल काष्ठा ip6_tnl *ip6gre_tunnel_locate(काष्ठा net *net,
		स्थिर काष्ठा __ip6_tnl_parm *parms, पूर्णांक create)
अणु
	काष्ठा ip6_tnl *t, *nt;
	काष्ठा net_device *dev;
	अक्षर name[IFNAMSIZ];
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);

	t = ip6gre_tunnel_find(net, parms, ARPHRD_IP6GRE);
	अगर (t && create)
		वापस शून्य;
	अगर (t || !create)
		वापस t;

	अगर (parms->name[0]) अणु
		अगर (!dev_valid_name(parms->name))
			वापस शून्य;
		strlcpy(name, parms->name, IFNAMSIZ);
	पूर्ण अन्यथा अणु
		म_नकल(name, "ip6gre%d");
	पूर्ण
	dev = alloc_netdev(माप(*t), name, NET_NAME_UNKNOWN,
			   ip6gre_tunnel_setup);
	अगर (!dev)
		वापस शून्य;

	dev_net_set(dev, net);

	nt = netdev_priv(dev);
	nt->parms = *parms;
	dev->rtnl_link_ops = &ip6gre_link_ops;

	nt->dev = dev;
	nt->net = dev_net(dev);

	अगर (रेजिस्टर_netdevice(dev) < 0)
		जाओ failed_मुक्त;

	ip6gre_tnl_link_config(nt, 1);

	/* Can use a lockless transmit, unless we generate output sequences */
	अगर (!(nt->parms.o_flags & TUNNEL_SEQ))
		dev->features |= NETIF_F_LLTX;

	ip6gre_tunnel_link(ign, nt);
	वापस nt;

failed_मुक्त:
	मुक्त_netdev(dev);
	वापस शून्य;
पूर्ण

अटल व्योम ip6erspan_tunnel_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा ip6gre_net *ign = net_generic(t->net, ip6gre_net_id);

	ip6erspan_tunnel_unlink_md(ign, t);
	ip6gre_tunnel_unlink(ign, t);
	dst_cache_reset(&t->dst_cache);
	dev_put(dev);
पूर्ण

अटल व्योम ip6gre_tunnel_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा ip6gre_net *ign = net_generic(t->net, ip6gre_net_id);

	ip6gre_tunnel_unlink_md(ign, t);
	ip6gre_tunnel_unlink(ign, t);
	अगर (ign->fb_tunnel_dev == dev)
		WRITE_ONCE(ign->fb_tunnel_dev, शून्य);
	dst_cache_reset(&t->dst_cache);
	dev_put(dev);
पूर्ण


अटल पूर्णांक ip6gre_err(काष्ठा sk_buff *skb, काष्ठा inet6_skb_parm *opt,
		       u8 type, u8 code, पूर्णांक offset, __be32 info)
अणु
	काष्ठा net *net = dev_net(skb->dev);
	स्थिर काष्ठा ipv6hdr *ipv6h;
	काष्ठा tnl_ptk_info tpi;
	काष्ठा ip6_tnl *t;

	अगर (gre_parse_header(skb, &tpi, शून्य, htons(ETH_P_IPV6),
			     offset) < 0)
		वापस -EINVAL;

	ipv6h = (स्थिर काष्ठा ipv6hdr *)skb->data;
	t = ip6gre_tunnel_lookup(skb->dev, &ipv6h->daddr, &ipv6h->saddr,
				 tpi.key, tpi.proto);
	अगर (!t)
		वापस -ENOENT;

	चयन (type) अणु
	हाल ICMPV6_DEST_UNREACH:
		net_dbg_ratelimited("%s: Path to destination invalid or inactive!\n",
				    t->parms.name);
		अगर (code != ICMPV6_PORT_UNREACH)
			अवरोध;
		वापस 0;
	हाल ICMPV6_TIME_EXCEED:
		अगर (code == ICMPV6_EXC_HOPLIMIT) अणु
			net_dbg_ratelimited("%s: Too small hop limit or routing loop in tunnel!\n",
					    t->parms.name);
			अवरोध;
		पूर्ण
		वापस 0;
	हाल ICMPV6_PARAMPROB: अणु
		काष्ठा ipv6_tlv_tnl_enc_lim *tel;
		__u32 teli;

		teli = 0;
		अगर (code == ICMPV6_HDR_FIELD)
			teli = ip6_tnl_parse_tlv_enc_lim(skb, skb->data);

		अगर (teli && teli == be32_to_cpu(info) - 2) अणु
			tel = (काष्ठा ipv6_tlv_tnl_enc_lim *) &skb->data[teli];
			अगर (tel->encap_limit == 0) अणु
				net_dbg_ratelimited("%s: Too small encapsulation limit or routing loop in tunnel!\n",
						    t->parms.name);
			पूर्ण
		पूर्ण अन्यथा अणु
			net_dbg_ratelimited("%s: Recipient unable to parse tunneled packet!\n",
					    t->parms.name);
		पूर्ण
		वापस 0;
	पूर्ण
	हाल ICMPV6_PKT_TOOBIG:
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, शून्य));
		वापस 0;
	हाल NDISC_REसूचीECT:
		ip6_redirect(skb, net, skb->dev->अगरindex, 0,
			     sock_net_uid(net, शून्य));
		वापस 0;
	पूर्ण

	अगर (समय_beक्रमe(jअगरfies, t->err_समय + IP6TUNNEL_ERR_TIMEO))
		t->err_count++;
	अन्यथा
		t->err_count = 1;
	t->err_समय = jअगरfies;

	वापस 0;
पूर्ण

अटल पूर्णांक ip6gre_rcv(काष्ठा sk_buff *skb, स्थिर काष्ठा tnl_ptk_info *tpi)
अणु
	स्थिर काष्ठा ipv6hdr *ipv6h;
	काष्ठा ip6_tnl *tunnel;

	ipv6h = ipv6_hdr(skb);
	tunnel = ip6gre_tunnel_lookup(skb->dev,
				      &ipv6h->saddr, &ipv6h->daddr, tpi->key,
				      tpi->proto);
	अगर (tunnel) अणु
		अगर (tunnel->parms.collect_md) अणु
			काष्ठा metadata_dst *tun_dst;
			__be64 tun_id;
			__be16 flags;

			flags = tpi->flags;
			tun_id = key32_to_tunnel_id(tpi->key);

			tun_dst = ipv6_tun_rx_dst(skb, flags, tun_id, 0);
			अगर (!tun_dst)
				वापस PACKET_REJECT;

			ip6_tnl_rcv(tunnel, skb, tpi, tun_dst, log_ecn_error);
		पूर्ण अन्यथा अणु
			ip6_tnl_rcv(tunnel, skb, tpi, शून्य, log_ecn_error);
		पूर्ण

		वापस PACKET_RCVD;
	पूर्ण

	वापस PACKET_REJECT;
पूर्ण

अटल पूर्णांक ip6erspan_rcv(काष्ठा sk_buff *skb,
			 काष्ठा tnl_ptk_info *tpi,
			 पूर्णांक gre_hdr_len)
अणु
	काष्ठा erspan_base_hdr *ershdr;
	स्थिर काष्ठा ipv6hdr *ipv6h;
	काष्ठा erspan_md2 *md2;
	काष्ठा ip6_tnl *tunnel;
	u8 ver;

	ipv6h = ipv6_hdr(skb);
	ershdr = (काष्ठा erspan_base_hdr *)skb->data;
	ver = ershdr->ver;

	tunnel = ip6gre_tunnel_lookup(skb->dev,
				      &ipv6h->saddr, &ipv6h->daddr, tpi->key,
				      tpi->proto);
	अगर (tunnel) अणु
		पूर्णांक len = erspan_hdr_len(ver);

		अगर (unlikely(!pskb_may_pull(skb, len)))
			वापस PACKET_REJECT;

		अगर (__iptunnel_pull_header(skb, len,
					   htons(ETH_P_TEB),
					   false, false) < 0)
			वापस PACKET_REJECT;

		अगर (tunnel->parms.collect_md) अणु
			काष्ठा erspan_metadata *pkt_md, *md;
			काष्ठा metadata_dst *tun_dst;
			काष्ठा ip_tunnel_info *info;
			अचिन्हित अक्षर *gh;
			__be64 tun_id;
			__be16 flags;

			tpi->flags |= TUNNEL_KEY;
			flags = tpi->flags;
			tun_id = key32_to_tunnel_id(tpi->key);

			tun_dst = ipv6_tun_rx_dst(skb, flags, tun_id,
						  माप(*md));
			अगर (!tun_dst)
				वापस PACKET_REJECT;

			/* skb can be uncloned in __iptunnel_pull_header, so
			 * old pkt_md is no दीर्घer valid and we need to reset
			 * it
			 */
			gh = skb_network_header(skb) +
			     skb_network_header_len(skb);
			pkt_md = (काष्ठा erspan_metadata *)(gh + gre_hdr_len +
							    माप(*ershdr));
			info = &tun_dst->u.tun_info;
			md = ip_tunnel_info_opts(info);
			md->version = ver;
			md2 = &md->u.md2;
			स_नकल(md2, pkt_md, ver == 1 ? ERSPAN_V1_MDSIZE :
						       ERSPAN_V2_MDSIZE);
			info->key.tun_flags |= TUNNEL_ERSPAN_OPT;
			info->options_len = माप(*md);

			ip6_tnl_rcv(tunnel, skb, tpi, tun_dst, log_ecn_error);

		पूर्ण अन्यथा अणु
			ip6_tnl_rcv(tunnel, skb, tpi, शून्य, log_ecn_error);
		पूर्ण

		वापस PACKET_RCVD;
	पूर्ण

	वापस PACKET_REJECT;
पूर्ण

अटल पूर्णांक gre_rcv(काष्ठा sk_buff *skb)
अणु
	काष्ठा tnl_ptk_info tpi;
	bool csum_err = false;
	पूर्णांक hdr_len;

	hdr_len = gre_parse_header(skb, &tpi, &csum_err, htons(ETH_P_IPV6), 0);
	अगर (hdr_len < 0)
		जाओ drop;

	अगर (iptunnel_pull_header(skb, hdr_len, tpi.proto, false))
		जाओ drop;

	अगर (unlikely(tpi.proto == htons(ETH_P_ERSPAN) ||
		     tpi.proto == htons(ETH_P_ERSPAN2))) अणु
		अगर (ip6erspan_rcv(skb, &tpi, hdr_len) == PACKET_RCVD)
			वापस 0;
		जाओ out;
	पूर्ण

	अगर (ip6gre_rcv(skb, &tpi) == PACKET_RCVD)
		वापस 0;

out:
	icmpv6_send(skb, ICMPV6_DEST_UNREACH, ICMPV6_PORT_UNREACH, 0);
drop:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण

अटल पूर्णांक gre_handle_offloads(काष्ठा sk_buff *skb, bool csum)
अणु
	वापस iptunnel_handle_offloads(skb,
					csum ? SKB_GSO_GRE_CSUM : SKB_GSO_GRE);
पूर्ण

अटल व्योम prepare_ip6gre_xmit_ipv4(काष्ठा sk_buff *skb,
				     काष्ठा net_device *dev,
				     काष्ठा flowi6 *fl6, __u8 *dsfield,
				     पूर्णांक *encap_limit)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा ip6_tnl *t = netdev_priv(dev);

	अगर (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
		*encap_limit = t->parms.encap_limit;

	स_नकल(fl6, &t->fl.u.ip6, माप(*fl6));

	अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_TCLASS)
		*dsfield = ipv4_get_dsfield(iph);
	अन्यथा
		*dsfield = ip6_tclass(t->parms.flowinfo);

	अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_FWMARK)
		fl6->flowi6_mark = skb->mark;
	अन्यथा
		fl6->flowi6_mark = t->parms.fwmark;

	fl6->flowi6_uid = sock_net_uid(dev_net(dev), शून्य);
पूर्ण

अटल पूर्णांक prepare_ip6gre_xmit_ipv6(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev,
				    काष्ठा flowi6 *fl6, __u8 *dsfield,
				    पूर्णांक *encap_limit)
अणु
	काष्ठा ipv6hdr *ipv6h;
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	__u16 offset;

	offset = ip6_tnl_parse_tlv_enc_lim(skb, skb_network_header(skb));
	/* ip6_tnl_parse_tlv_enc_lim() might have पुनः_स्मृतिated skb->head */
	ipv6h = ipv6_hdr(skb);

	अगर (offset > 0) अणु
		काष्ठा ipv6_tlv_tnl_enc_lim *tel;

		tel = (काष्ठा ipv6_tlv_tnl_enc_lim *)&skb_network_header(skb)[offset];
		अगर (tel->encap_limit == 0) अणु
			icmpv6_nकरो_send(skb, ICMPV6_PARAMPROB,
					ICMPV6_HDR_FIELD, offset + 2);
			वापस -1;
		पूर्ण
		*encap_limit = tel->encap_limit - 1;
	पूर्ण अन्यथा अगर (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT)) अणु
		*encap_limit = t->parms.encap_limit;
	पूर्ण

	स_नकल(fl6, &t->fl.u.ip6, माप(*fl6));

	अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_TCLASS)
		*dsfield = ipv6_get_dsfield(ipv6h);
	अन्यथा
		*dsfield = ip6_tclass(t->parms.flowinfo);

	अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_FLOWLABEL)
		fl6->flowlabel |= ip6_flowlabel(ipv6h);

	अगर (t->parms.flags & IP6_TNL_F_USE_ORIG_FWMARK)
		fl6->flowi6_mark = skb->mark;
	अन्यथा
		fl6->flowi6_mark = t->parms.fwmark;

	fl6->flowi6_uid = sock_net_uid(dev_net(dev), शून्य);

	वापस 0;
पूर्ण

अटल काष्ठा ip_tunnel_info *skb_tunnel_info_txcheck(काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_tunnel_info *tun_info;

	tun_info = skb_tunnel_info(skb);
	अगर (unlikely(!tun_info || !(tun_info->mode & IP_TUNNEL_INFO_TX)))
		वापस ERR_PTR(-EINVAL);

	वापस tun_info;
पूर्ण

अटल netdev_tx_t __gre6_xmit(काष्ठा sk_buff *skb,
			       काष्ठा net_device *dev, __u8 dsfield,
			       काष्ठा flowi6 *fl6, पूर्णांक encap_limit,
			       __u32 *pmtu, __be16 proto)
अणु
	काष्ठा ip6_tnl *tunnel = netdev_priv(dev);
	__be16 protocol;

	अगर (dev->type == ARPHRD_ETHER)
		IPCB(skb)->flags = 0;

	अगर (dev->header_ops && dev->type == ARPHRD_IP6GRE)
		fl6->daddr = ((काष्ठा ipv6hdr *)skb->data)->daddr;
	अन्यथा
		fl6->daddr = tunnel->parms.raddr;

	अगर (skb_cow_head(skb, dev->needed_headroom ?: tunnel->hlen))
		वापस -ENOMEM;

	/* Push GRE header. */
	protocol = (dev->type == ARPHRD_ETHER) ? htons(ETH_P_TEB) : proto;

	अगर (tunnel->parms.collect_md) अणु
		काष्ठा ip_tunnel_info *tun_info;
		स्थिर काष्ठा ip_tunnel_key *key;
		__be16 flags;

		tun_info = skb_tunnel_info_txcheck(skb);
		अगर (IS_ERR(tun_info) ||
		    unlikely(ip_tunnel_info_af(tun_info) != AF_INET6))
			वापस -EINVAL;

		key = &tun_info->key;
		स_रखो(fl6, 0, माप(*fl6));
		fl6->flowi6_proto = IPPROTO_GRE;
		fl6->daddr = key->u.ipv6.dst;
		fl6->flowlabel = key->label;
		fl6->flowi6_uid = sock_net_uid(dev_net(dev), शून्य);

		dsfield = key->tos;
		flags = key->tun_flags &
			(TUNNEL_CSUM | TUNNEL_KEY | TUNNEL_SEQ);
		tunnel->tun_hlen = gre_calc_hlen(flags);

		gre_build_header(skb, tunnel->tun_hlen,
				 flags, protocol,
				 tunnel_id_to_key32(tun_info->key.tun_id),
				 (flags & TUNNEL_SEQ) ? htonl(tunnel->o_seqno++)
						      : 0);

	पूर्ण अन्यथा अणु
		अगर (tunnel->parms.o_flags & TUNNEL_SEQ)
			tunnel->o_seqno++;

		gre_build_header(skb, tunnel->tun_hlen, tunnel->parms.o_flags,
				 protocol, tunnel->parms.o_key,
				 htonl(tunnel->o_seqno));
	पूर्ण

	वापस ip6_tnl_xmit(skb, dev, dsfield, fl6, encap_limit, pmtu,
			    NEXTHDR_GRE);
पूर्ण

अटल अंतरभूत पूर्णांक ip6gre_xmit_ipv4(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	पूर्णांक encap_limit = -1;
	काष्ठा flowi6 fl6;
	__u8 dsfield = 0;
	__u32 mtu;
	पूर्णांक err;

	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));

	अगर (!t->parms.collect_md)
		prepare_ip6gre_xmit_ipv4(skb, dev, &fl6,
					 &dsfield, &encap_limit);

	err = gre_handle_offloads(skb, !!(t->parms.o_flags & TUNNEL_CSUM));
	अगर (err)
		वापस -1;

	err = __gre6_xmit(skb, dev, dsfield, &fl6, encap_limit, &mtu,
			  skb->protocol);
	अगर (err != 0) अणु
		/* XXX: send ICMP error even अगर DF is not set. */
		अगर (err == -EMSGSIZE)
			icmp_nकरो_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				      htonl(mtu));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ip6gre_xmit_ipv6(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा ipv6hdr *ipv6h = ipv6_hdr(skb);
	पूर्णांक encap_limit = -1;
	काष्ठा flowi6 fl6;
	__u8 dsfield = 0;
	__u32 mtu;
	पूर्णांक err;

	अगर (ipv6_addr_equal(&t->parms.raddr, &ipv6h->saddr))
		वापस -1;

	अगर (!t->parms.collect_md &&
	    prepare_ip6gre_xmit_ipv6(skb, dev, &fl6, &dsfield, &encap_limit))
		वापस -1;

	अगर (gre_handle_offloads(skb, !!(t->parms.o_flags & TUNNEL_CSUM)))
		वापस -1;

	err = __gre6_xmit(skb, dev, dsfield, &fl6, encap_limit,
			  &mtu, skb->protocol);
	अगर (err != 0) अणु
		अगर (err == -EMSGSIZE)
			icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ip6gre_tnl_addr_conflict - compare packet addresses to tunnel's own
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

अटल अंतरभूत bool ip6gre_tnl_addr_conflict(स्थिर काष्ठा ip6_tnl *t,
	स्थिर काष्ठा ipv6hdr *hdr)
अणु
	वापस ipv6_addr_equal(&t->parms.raddr, &hdr->saddr);
पूर्ण

अटल पूर्णांक ip6gre_xmit_other(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	पूर्णांक encap_limit = -1;
	काष्ठा flowi6 fl6;
	__u32 mtu;
	पूर्णांक err;

	अगर (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
		encap_limit = t->parms.encap_limit;

	अगर (!t->parms.collect_md)
		स_नकल(&fl6, &t->fl.u.ip6, माप(fl6));

	err = gre_handle_offloads(skb, !!(t->parms.o_flags & TUNNEL_CSUM));
	अगर (err)
		वापस err;

	err = __gre6_xmit(skb, dev, 0, &fl6, encap_limit, &mtu, skb->protocol);

	वापस err;
पूर्ण

अटल netdev_tx_t ip6gre_tunnel_xmit(काष्ठा sk_buff *skb,
	काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &t->dev->stats;
	पूर्णांक ret;

	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_err;

	अगर (!ip6_tnl_xmit_ctl(t, &t->parms.laddr, &t->parms.raddr))
		जाओ tx_err;

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		ret = ip6gre_xmit_ipv4(skb, dev);
		अवरोध;
	हाल htons(ETH_P_IPV6):
		ret = ip6gre_xmit_ipv6(skb, dev);
		अवरोध;
	शेष:
		ret = ip6gre_xmit_other(skb, dev);
		अवरोध;
	पूर्ण

	अगर (ret < 0)
		जाओ tx_err;

	वापस NETDEV_TX_OK;

tx_err:
	अगर (!t->parms.collect_md || !IS_ERR(skb_tunnel_info_txcheck(skb)))
		stats->tx_errors++;
	stats->tx_dropped++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल netdev_tx_t ip6erspan_tunnel_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	काष्ठा ip_tunnel_info *tun_info = शून्य;
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net_device_stats *stats;
	bool truncate = false;
	पूर्णांक encap_limit = -1;
	__u8 dsfield = false;
	काष्ठा flowi6 fl6;
	पूर्णांक err = -EINVAL;
	__be16 proto;
	__u32 mtu;
	पूर्णांक nhoff;
	पूर्णांक thoff;

	अगर (!pskb_inet_may_pull(skb))
		जाओ tx_err;

	अगर (!ip6_tnl_xmit_ctl(t, &t->parms.laddr, &t->parms.raddr))
		जाओ tx_err;

	अगर (gre_handle_offloads(skb, false))
		जाओ tx_err;

	अगर (skb->len > dev->mtu + dev->hard_header_len) अणु
		pskb_trim(skb, dev->mtu + dev->hard_header_len);
		truncate = true;
	पूर्ण

	nhoff = skb_network_header(skb) - skb_mac_header(skb);
	अगर (skb->protocol == htons(ETH_P_IP) &&
	    (ntohs(ip_hdr(skb)->tot_len) > skb->len - nhoff))
		truncate = true;

	thoff = skb_transport_header(skb) - skb_mac_header(skb);
	अगर (skb->protocol == htons(ETH_P_IPV6) &&
	    (ntohs(ipv6_hdr(skb)->payload_len) > skb->len - thoff))
		truncate = true;

	अगर (skb_cow_head(skb, dev->needed_headroom ?: t->hlen))
		जाओ tx_err;

	t->parms.o_flags &= ~TUNNEL_KEY;
	IPCB(skb)->flags = 0;

	/* For collect_md mode, derive fl6 from the tunnel key,
	 * क्रम native mode, call prepare_ip6gre_xmit_अणुipv4,ipv6पूर्ण.
	 */
	अगर (t->parms.collect_md) अणु
		स्थिर काष्ठा ip_tunnel_key *key;
		काष्ठा erspan_metadata *md;
		__be32 tun_id;

		tun_info = skb_tunnel_info_txcheck(skb);
		अगर (IS_ERR(tun_info) ||
		    unlikely(ip_tunnel_info_af(tun_info) != AF_INET6))
			जाओ tx_err;

		key = &tun_info->key;
		स_रखो(&fl6, 0, माप(fl6));
		fl6.flowi6_proto = IPPROTO_GRE;
		fl6.daddr = key->u.ipv6.dst;
		fl6.flowlabel = key->label;
		fl6.flowi6_uid = sock_net_uid(dev_net(dev), शून्य);

		dsfield = key->tos;
		अगर (!(tun_info->key.tun_flags & TUNNEL_ERSPAN_OPT))
			जाओ tx_err;
		अगर (tun_info->options_len < माप(*md))
			जाओ tx_err;
		md = ip_tunnel_info_opts(tun_info);

		tun_id = tunnel_id_to_key32(key->tun_id);
		अगर (md->version == 1) अणु
			erspan_build_header(skb,
					    ntohl(tun_id),
					    ntohl(md->u.index), truncate,
					    false);
		पूर्ण अन्यथा अगर (md->version == 2) अणु
			erspan_build_header_v2(skb,
					       ntohl(tun_id),
					       md->u.md2.dir,
					       get_hwid(&md->u.md2),
					       truncate, false);
		पूर्ण अन्यथा अणु
			जाओ tx_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP):
			स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));
			prepare_ip6gre_xmit_ipv4(skb, dev, &fl6,
						 &dsfield, &encap_limit);
			अवरोध;
		हाल htons(ETH_P_IPV6):
			अगर (ipv6_addr_equal(&t->parms.raddr, &ipv6_hdr(skb)->saddr))
				जाओ tx_err;
			अगर (prepare_ip6gre_xmit_ipv6(skb, dev, &fl6,
						     &dsfield, &encap_limit))
				जाओ tx_err;
			अवरोध;
		शेष:
			स_नकल(&fl6, &t->fl.u.ip6, माप(fl6));
			अवरोध;
		पूर्ण

		अगर (t->parms.erspan_ver == 1)
			erspan_build_header(skb, ntohl(t->parms.o_key),
					    t->parms.index,
					    truncate, false);
		अन्यथा अगर (t->parms.erspan_ver == 2)
			erspan_build_header_v2(skb, ntohl(t->parms.o_key),
					       t->parms.dir,
					       t->parms.hwid,
					       truncate, false);
		अन्यथा
			जाओ tx_err;

		fl6.daddr = t->parms.raddr;
	पूर्ण

	/* Push GRE header. */
	proto = (t->parms.erspan_ver == 1) ? htons(ETH_P_ERSPAN)
					   : htons(ETH_P_ERSPAN2);
	gre_build_header(skb, 8, TUNNEL_SEQ, proto, 0, htonl(t->o_seqno++));

	/* TooBig packet may have updated dst->dev's mtu */
	अगर (!t->parms.collect_md && dst && dst_mtu(dst) > dst->dev->mtu)
		dst->ops->update_pmtu(dst, शून्य, skb, dst->dev->mtu, false);

	err = ip6_tnl_xmit(skb, dev, dsfield, &fl6, encap_limit, &mtu,
			   NEXTHDR_GRE);
	अगर (err != 0) अणु
		/* XXX: send ICMP error even अगर DF is not set. */
		अगर (err == -EMSGSIZE) अणु
			अगर (skb->protocol == htons(ETH_P_IP))
				icmp_nकरो_send(skb, ICMP_DEST_UNREACH,
					      ICMP_FRAG_NEEDED, htonl(mtu));
			अन्यथा
				icmpv6_nकरो_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		पूर्ण

		जाओ tx_err;
	पूर्ण
	वापस NETDEV_TX_OK;

tx_err:
	stats = &t->dev->stats;
	अगर (!IS_ERR(tun_info))
		stats->tx_errors++;
	stats->tx_dropped++;
	kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ip6gre_tnl_link_config_common(काष्ठा ip6_tnl *t)
अणु
	काष्ठा net_device *dev = t->dev;
	काष्ठा __ip6_tnl_parm *p = &t->parms;
	काष्ठा flowi6 *fl6 = &t->fl.u.ip6;

	अगर (dev->type != ARPHRD_ETHER) अणु
		स_नकल(dev->dev_addr, &p->laddr, माप(काष्ठा in6_addr));
		स_नकल(dev->broadcast, &p->raddr, माप(काष्ठा in6_addr));
	पूर्ण

	/* Set up flowi ढाँचा */
	fl6->saddr = p->laddr;
	fl6->daddr = p->raddr;
	fl6->flowi6_oअगर = p->link;
	fl6->flowlabel = 0;
	fl6->flowi6_proto = IPPROTO_GRE;

	अगर (!(p->flags&IP6_TNL_F_USE_ORIG_TCLASS))
		fl6->flowlabel |= IPV6_TCLASS_MASK & p->flowinfo;
	अगर (!(p->flags&IP6_TNL_F_USE_ORIG_FLOWLABEL))
		fl6->flowlabel |= IPV6_FLOWLABEL_MASK & p->flowinfo;

	p->flags &= ~(IP6_TNL_F_CAP_XMIT|IP6_TNL_F_CAP_RCV|IP6_TNL_F_CAP_PER_PACKET);
	p->flags |= ip6_tnl_get_cap(t, &p->laddr, &p->raddr);

	अगर (p->flags&IP6_TNL_F_CAP_XMIT &&
			p->flags&IP6_TNL_F_CAP_RCV && dev->type != ARPHRD_ETHER)
		dev->flags |= IFF_POINTOPOINT;
	अन्यथा
		dev->flags &= ~IFF_POINTOPOINT;
पूर्ण

अटल व्योम ip6gre_tnl_link_config_route(काष्ठा ip6_tnl *t, पूर्णांक set_mtu,
					 पूर्णांक t_hlen)
अणु
	स्थिर काष्ठा __ip6_tnl_parm *p = &t->parms;
	काष्ठा net_device *dev = t->dev;

	अगर (p->flags & IP6_TNL_F_CAP_XMIT) अणु
		पूर्णांक strict = (ipv6_addr_type(&p->raddr) &
			      (IPV6_ADDR_MULTICAST|IPV6_ADDR_LINKLOCAL));

		काष्ठा rt6_info *rt = rt6_lookup(t->net,
						 &p->raddr, &p->laddr,
						 p->link, शून्य, strict);

		अगर (!rt)
			वापस;

		अगर (rt->dst.dev) अणु
			अचिन्हित लघु dst_len = rt->dst.dev->hard_header_len +
						 t_hlen;

			अगर (t->dev->header_ops)
				dev->hard_header_len = dst_len;
			अन्यथा
				dev->needed_headroom = dst_len;

			अगर (set_mtu) अणु
				dev->mtu = rt->dst.dev->mtu - t_hlen;
				अगर (!(t->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
					dev->mtu -= 8;
				अगर (dev->type == ARPHRD_ETHER)
					dev->mtu -= ETH_HLEN;

				अगर (dev->mtu < IPV6_MIN_MTU)
					dev->mtu = IPV6_MIN_MTU;
			पूर्ण
		पूर्ण
		ip6_rt_put(rt);
	पूर्ण
पूर्ण

अटल पूर्णांक ip6gre_calc_hlen(काष्ठा ip6_tnl *tunnel)
अणु
	पूर्णांक t_hlen;

	tunnel->tun_hlen = gre_calc_hlen(tunnel->parms.o_flags);
	tunnel->hlen = tunnel->tun_hlen + tunnel->encap_hlen;

	t_hlen = tunnel->hlen + माप(काष्ठा ipv6hdr);

	अगर (tunnel->dev->header_ops)
		tunnel->dev->hard_header_len = LL_MAX_HEADER + t_hlen;
	अन्यथा
		tunnel->dev->needed_headroom = LL_MAX_HEADER + t_hlen;

	वापस t_hlen;
पूर्ण

अटल व्योम ip6gre_tnl_link_config(काष्ठा ip6_tnl *t, पूर्णांक set_mtu)
अणु
	ip6gre_tnl_link_config_common(t);
	ip6gre_tnl_link_config_route(t, set_mtu, ip6gre_calc_hlen(t));
पूर्ण

अटल व्योम ip6gre_tnl_copy_tnl_parm(काष्ठा ip6_tnl *t,
				     स्थिर काष्ठा __ip6_tnl_parm *p)
अणु
	t->parms.laddr = p->laddr;
	t->parms.raddr = p->raddr;
	t->parms.flags = p->flags;
	t->parms.hop_limit = p->hop_limit;
	t->parms.encap_limit = p->encap_limit;
	t->parms.flowinfo = p->flowinfo;
	t->parms.link = p->link;
	t->parms.proto = p->proto;
	t->parms.i_key = p->i_key;
	t->parms.o_key = p->o_key;
	t->parms.i_flags = p->i_flags;
	t->parms.o_flags = p->o_flags;
	t->parms.fwmark = p->fwmark;
	t->parms.erspan_ver = p->erspan_ver;
	t->parms.index = p->index;
	t->parms.dir = p->dir;
	t->parms.hwid = p->hwid;
	dst_cache_reset(&t->dst_cache);
पूर्ण

अटल पूर्णांक ip6gre_tnl_change(काष्ठा ip6_tnl *t, स्थिर काष्ठा __ip6_tnl_parm *p,
			     पूर्णांक set_mtu)
अणु
	ip6gre_tnl_copy_tnl_parm(t, p);
	ip6gre_tnl_link_config(t, set_mtu);
	वापस 0;
पूर्ण

अटल व्योम ip6gre_tnl_parm_from_user(काष्ठा __ip6_tnl_parm *p,
	स्थिर काष्ठा ip6_tnl_parm2 *u)
अणु
	p->laddr = u->laddr;
	p->raddr = u->raddr;
	p->flags = u->flags;
	p->hop_limit = u->hop_limit;
	p->encap_limit = u->encap_limit;
	p->flowinfo = u->flowinfo;
	p->link = u->link;
	p->i_key = u->i_key;
	p->o_key = u->o_key;
	p->i_flags = gre_flags_to_tnl_flags(u->i_flags);
	p->o_flags = gre_flags_to_tnl_flags(u->o_flags);
	स_नकल(p->name, u->name, माप(u->name));
पूर्ण

अटल व्योम ip6gre_tnl_parm_to_user(काष्ठा ip6_tnl_parm2 *u,
	स्थिर काष्ठा __ip6_tnl_parm *p)
अणु
	u->proto = IPPROTO_GRE;
	u->laddr = p->laddr;
	u->raddr = p->raddr;
	u->flags = p->flags;
	u->hop_limit = p->hop_limit;
	u->encap_limit = p->encap_limit;
	u->flowinfo = p->flowinfo;
	u->link = p->link;
	u->i_key = p->i_key;
	u->o_key = p->o_key;
	u->i_flags = gre_tnl_flags_to_gre_flags(p->i_flags);
	u->o_flags = gre_tnl_flags_to_gre_flags(p->o_flags);
	स_नकल(u->name, p->name, माप(u->name));
पूर्ण

अटल पूर्णांक ip6gre_tunnel_ioctl(काष्ठा net_device *dev,
	काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	पूर्णांक err = 0;
	काष्ठा ip6_tnl_parm2 p;
	काष्ठा __ip6_tnl_parm p1;
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा net *net = t->net;
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);

	स_रखो(&p1, 0, माप(p1));

	चयन (cmd) अणु
	हाल SIOCGETTUNNEL:
		अगर (dev == ign->fb_tunnel_dev) अणु
			अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p))) अणु
				err = -EFAULT;
				अवरोध;
			पूर्ण
			ip6gre_tnl_parm_from_user(&p1, &p);
			t = ip6gre_tunnel_locate(net, &p1, 0);
			अगर (!t)
				t = netdev_priv(dev);
		पूर्ण
		स_रखो(&p, 0, माप(p));
		ip6gre_tnl_parm_to_user(&p, &t->parms);
		अगर (copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &p, माप(p)))
			err = -EFAULT;
		अवरोध;

	हाल SIOCADDTUNNEL:
	हाल SIOCCHGTUNNEL:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			जाओ करोne;

		err = -EFAULT;
		अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p)))
			जाओ करोne;

		err = -EINVAL;
		अगर ((p.i_flags|p.o_flags)&(GRE_VERSION|GRE_ROUTING))
			जाओ करोne;

		अगर (!(p.i_flags&GRE_KEY))
			p.i_key = 0;
		अगर (!(p.o_flags&GRE_KEY))
			p.o_key = 0;

		ip6gre_tnl_parm_from_user(&p1, &p);
		t = ip6gre_tunnel_locate(net, &p1, cmd == SIOCADDTUNNEL);

		अगर (dev != ign->fb_tunnel_dev && cmd == SIOCCHGTUNNEL) अणु
			अगर (t) अणु
				अगर (t->dev != dev) अणु
					err = -EEXIST;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				t = netdev_priv(dev);

				ip6gre_tunnel_unlink(ign, t);
				synchronize_net();
				ip6gre_tnl_change(t, &p1, 1);
				ip6gre_tunnel_link(ign, t);
				netdev_state_change(dev);
			पूर्ण
		पूर्ण

		अगर (t) अणु
			err = 0;

			स_रखो(&p, 0, माप(p));
			ip6gre_tnl_parm_to_user(&p, &t->parms);
			अगर (copy_to_user(अगरr->अगरr_अगरru.अगरru_data, &p, माप(p)))
				err = -EFAULT;
		पूर्ण अन्यथा
			err = (cmd == SIOCADDTUNNEL ? -ENOBUFS : -ENOENT);
		अवरोध;

	हाल SIOCDELTUNNEL:
		err = -EPERM;
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN))
			जाओ करोne;

		अगर (dev == ign->fb_tunnel_dev) अणु
			err = -EFAULT;
			अगर (copy_from_user(&p, अगरr->अगरr_अगरru.अगरru_data, माप(p)))
				जाओ करोne;
			err = -ENOENT;
			ip6gre_tnl_parm_from_user(&p1, &p);
			t = ip6gre_tunnel_locate(net, &p1, 0);
			अगर (!t)
				जाओ करोne;
			err = -EPERM;
			अगर (t == netdev_priv(ign->fb_tunnel_dev))
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

अटल पूर्णांक ip6gre_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			 अचिन्हित लघु type, स्थिर व्योम *daddr,
			 स्थिर व्योम *saddr, अचिन्हित पूर्णांक len)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा ipv6hdr *ipv6h;
	__be16 *p;

	ipv6h = skb_push(skb, t->hlen + माप(*ipv6h));
	ip6_flow_hdr(ipv6h, 0, ip6_make_flowlabel(dev_net(dev), skb,
						  t->fl.u.ip6.flowlabel,
						  true, &t->fl.u.ip6));
	ipv6h->hop_limit = t->parms.hop_limit;
	ipv6h->nexthdr = NEXTHDR_GRE;
	ipv6h->saddr = t->parms.laddr;
	ipv6h->daddr = t->parms.raddr;

	p = (__be16 *)(ipv6h + 1);
	p[0] = t->parms.o_flags;
	p[1] = htons(type);

	/*
	 *	Set the source hardware address.
	 */

	अगर (saddr)
		स_नकल(&ipv6h->saddr, saddr, माप(काष्ठा in6_addr));
	अगर (daddr)
		स_नकल(&ipv6h->daddr, daddr, माप(काष्ठा in6_addr));
	अगर (!ipv6_addr_any(&ipv6h->daddr))
		वापस t->hlen;

	वापस -t->hlen;
पूर्ण

अटल स्थिर काष्ठा header_ops ip6gre_header_ops = अणु
	.create	= ip6gre_header,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ip6gre_netdev_ops = अणु
	.nकरो_init		= ip6gre_tunnel_init,
	.nकरो_uninit		= ip6gre_tunnel_uninit,
	.nकरो_start_xmit		= ip6gre_tunnel_xmit,
	.nकरो_करो_ioctl		= ip6gre_tunnel_ioctl,
	.nकरो_change_mtu		= ip6_tnl_change_mtu,
	.nकरो_get_stats64	= dev_get_tstats64,
	.nकरो_get_अगरlink		= ip6_tnl_get_अगरlink,
पूर्ण;

अटल व्योम ip6gre_dev_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);

	gro_cells_destroy(&t->gro_cells);
	dst_cache_destroy(&t->dst_cache);
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल व्योम ip6gre_tunnel_setup(काष्ठा net_device *dev)
अणु
	dev->netdev_ops = &ip6gre_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = ip6gre_dev_मुक्त;

	dev->type = ARPHRD_IP6GRE;

	dev->flags |= IFF_NOARP;
	dev->addr_len = माप(काष्ठा in6_addr);
	netअगर_keep_dst(dev);
	/* This perm addr will be used as पूर्णांकerface identअगरier by IPv6 */
	dev->addr_assign_type = NET_ADDR_RANDOM;
	eth_अक्रमom_addr(dev->perm_addr);
पूर्ण

#घोषणा GRE6_FEATURES (NETIF_F_SG |		\
		       NETIF_F_FRAGLIST |	\
		       NETIF_F_HIGHDMA |	\
		       NETIF_F_HW_CSUM)

अटल व्योम ip6gre_tnl_init_features(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *nt = netdev_priv(dev);

	dev->features		|= GRE6_FEATURES;
	dev->hw_features	|= GRE6_FEATURES;

	अगर (!(nt->parms.o_flags & TUNNEL_SEQ)) अणु
		/* TCP offload with GRE SEQ is not supported, nor
		 * can we support 2 levels of outer headers requiring
		 * an update.
		 */
		अगर (!(nt->parms.o_flags & TUNNEL_CSUM) ||
		    nt->encap.type == TUNNEL_ENCAP_NONE) अणु
			dev->features    |= NETIF_F_GSO_SOFTWARE;
			dev->hw_features |= NETIF_F_GSO_SOFTWARE;
		पूर्ण

		/* Can use a lockless transmit, unless we generate
		 * output sequences
		 */
		dev->features |= NETIF_F_LLTX;
	पूर्ण
पूर्ण

अटल पूर्णांक ip6gre_tunnel_init_common(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *tunnel;
	पूर्णांक ret;
	पूर्णांक t_hlen;

	tunnel = netdev_priv(dev);

	tunnel->dev = dev;
	tunnel->net = dev_net(dev);
	म_नकल(tunnel->parms.name, dev->name);

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	ret = dst_cache_init(&tunnel->dst_cache, GFP_KERNEL);
	अगर (ret)
		जाओ cleanup_alloc_pcpu_stats;

	ret = gro_cells_init(&tunnel->gro_cells, dev);
	अगर (ret)
		जाओ cleanup_dst_cache_init;

	t_hlen = ip6gre_calc_hlen(tunnel);
	dev->mtu = ETH_DATA_LEN - t_hlen;
	अगर (dev->type == ARPHRD_ETHER)
		dev->mtu -= ETH_HLEN;
	अगर (!(tunnel->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
		dev->mtu -= 8;

	अगर (tunnel->parms.collect_md) अणु
		netअगर_keep_dst(dev);
	पूर्ण
	ip6gre_tnl_init_features(dev);

	dev_hold(dev);
	वापस 0;

cleanup_dst_cache_init:
	dst_cache_destroy(&tunnel->dst_cache);
cleanup_alloc_pcpu_stats:
	मुक्त_percpu(dev->tstats);
	dev->tstats = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक ip6gre_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *tunnel;
	पूर्णांक ret;

	ret = ip6gre_tunnel_init_common(dev);
	अगर (ret)
		वापस ret;

	tunnel = netdev_priv(dev);

	अगर (tunnel->parms.collect_md)
		वापस 0;

	स_नकल(dev->dev_addr, &tunnel->parms.laddr, माप(काष्ठा in6_addr));
	स_नकल(dev->broadcast, &tunnel->parms.raddr, माप(काष्ठा in6_addr));

	अगर (ipv6_addr_any(&tunnel->parms.raddr))
		dev->header_ops = &ip6gre_header_ops;

	वापस 0;
पूर्ण

अटल व्योम ip6gre_fb_tunnel_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *tunnel = netdev_priv(dev);

	tunnel->dev = dev;
	tunnel->net = dev_net(dev);
	म_नकल(tunnel->parms.name, dev->name);

	tunnel->hlen		= माप(काष्ठा ipv6hdr) + 4;
पूर्ण

अटल काष्ठा inet6_protocol ip6gre_protocol __पढ़ो_mostly = अणु
	.handler     = gre_rcv,
	.err_handler = ip6gre_err,
	.flags       = INET6_PROTO_NOPOLICY|INET6_PROTO_FINAL,
पूर्ण;

अटल व्योम ip6gre_destroy_tunnels(काष्ठा net *net, काष्ठा list_head *head)
अणु
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);
	काष्ठा net_device *dev, *aux;
	पूर्णांक prio;

	क्रम_each_netdev_safe(net, dev, aux)
		अगर (dev->rtnl_link_ops == &ip6gre_link_ops ||
		    dev->rtnl_link_ops == &ip6gre_tap_ops ||
		    dev->rtnl_link_ops == &ip6erspan_tap_ops)
			unरेजिस्टर_netdevice_queue(dev, head);

	क्रम (prio = 0; prio < 4; prio++) अणु
		पूर्णांक h;
		क्रम (h = 0; h < IP6_GRE_HASH_SIZE; h++) अणु
			काष्ठा ip6_tnl *t;

			t = rtnl_dereference(ign->tunnels[prio][h]);

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

अटल पूर्णांक __net_init ip6gre_init_net(काष्ठा net *net)
अणु
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);
	काष्ठा net_device *ndev;
	पूर्णांक err;

	अगर (!net_has_fallback_tunnels(net))
		वापस 0;
	ndev = alloc_netdev(माप(काष्ठा ip6_tnl), "ip6gre0",
			    NET_NAME_UNKNOWN, ip6gre_tunnel_setup);
	अगर (!ndev) अणु
		err = -ENOMEM;
		जाओ err_alloc_dev;
	पूर्ण
	ign->fb_tunnel_dev = ndev;
	dev_net_set(ign->fb_tunnel_dev, net);
	/* FB netdevice is special: we have one, and only one per netns.
	 * Allowing to move it to another netns is clearly unsafe.
	 */
	ign->fb_tunnel_dev->features |= NETIF_F_NETNS_LOCAL;


	ip6gre_fb_tunnel_init(ign->fb_tunnel_dev);
	ign->fb_tunnel_dev->rtnl_link_ops = &ip6gre_link_ops;

	err = रेजिस्टर_netdev(ign->fb_tunnel_dev);
	अगर (err)
		जाओ err_reg_dev;

	rcu_assign_poपूर्णांकer(ign->tunnels_wc[0],
			   netdev_priv(ign->fb_tunnel_dev));
	वापस 0;

err_reg_dev:
	मुक्त_netdev(ndev);
err_alloc_dev:
	वापस err;
पूर्ण

अटल व्योम __net_निकास ip6gre_निकास_batch_net(काष्ठा list_head *net_list)
अणु
	काष्ठा net *net;
	LIST_HEAD(list);

	rtnl_lock();
	list_क्रम_each_entry(net, net_list, निकास_list)
		ip6gre_destroy_tunnels(net, &list);
	unरेजिस्टर_netdevice_many(&list);
	rtnl_unlock();
पूर्ण

अटल काष्ठा pernet_operations ip6gre_net_ops = अणु
	.init = ip6gre_init_net,
	.निकास_batch = ip6gre_निकास_batch_net,
	.id   = &ip6gre_net_id,
	.size = माप(काष्ठा ip6gre_net),
पूर्ण;

अटल पूर्णांक ip6gre_tunnel_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				  काष्ठा netlink_ext_ack *extack)
अणु
	__be16 flags;

	अगर (!data)
		वापस 0;

	flags = 0;
	अगर (data[IFLA_GRE_IFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_IFLAGS]);
	अगर (data[IFLA_GRE_OFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_OFLAGS]);
	अगर (flags & (GRE_VERSION|GRE_ROUTING))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ip6gre_tap_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा in6_addr daddr;

	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (!data)
		जाओ out;

	अगर (data[IFLA_GRE_REMOTE]) अणु
		daddr = nla_get_in6_addr(data[IFLA_GRE_REMOTE]);
		अगर (ipv6_addr_any(&daddr))
			वापस -EINVAL;
	पूर्ण

out:
	वापस ip6gre_tunnel_validate(tb, data, extack);
पूर्ण

अटल पूर्णांक ip6erspan_tap_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				  काष्ठा netlink_ext_ack *extack)
अणु
	__be16 flags = 0;
	पूर्णांक ret, ver = 0;

	अगर (!data)
		वापस 0;

	ret = ip6gre_tap_validate(tb, data, extack);
	अगर (ret)
		वापस ret;

	/* ERSPAN should only have GRE sequence and key flag */
	अगर (data[IFLA_GRE_OFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_OFLAGS]);
	अगर (data[IFLA_GRE_IFLAGS])
		flags |= nla_get_be16(data[IFLA_GRE_IFLAGS]);
	अगर (!data[IFLA_GRE_COLLECT_METADATA] &&
	    flags != (GRE_SEQ | GRE_KEY))
		वापस -EINVAL;

	/* ERSPAN Session ID only has 10-bit. Since we reuse
	 * 32-bit key field as ID, check it's range.
	 */
	अगर (data[IFLA_GRE_IKEY] &&
	    (ntohl(nla_get_be32(data[IFLA_GRE_IKEY])) & ~ID_MASK))
		वापस -EINVAL;

	अगर (data[IFLA_GRE_OKEY] &&
	    (ntohl(nla_get_be32(data[IFLA_GRE_OKEY])) & ~ID_MASK))
		वापस -EINVAL;

	अगर (data[IFLA_GRE_ERSPAN_VER]) अणु
		ver = nla_get_u8(data[IFLA_GRE_ERSPAN_VER]);
		अगर (ver != 1 && ver != 2)
			वापस -EINVAL;
	पूर्ण

	अगर (ver == 1) अणु
		अगर (data[IFLA_GRE_ERSPAN_INDEX]) अणु
			u32 index = nla_get_u32(data[IFLA_GRE_ERSPAN_INDEX]);

			अगर (index & ~INDEX_MASK)
				वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (ver == 2) अणु
		अगर (data[IFLA_GRE_ERSPAN_सूची]) अणु
			u16 dir = nla_get_u8(data[IFLA_GRE_ERSPAN_सूची]);

			अगर (dir & ~(सूची_MASK >> सूची_OFFSET))
				वापस -EINVAL;
		पूर्ण

		अगर (data[IFLA_GRE_ERSPAN_HWID]) अणु
			u16 hwid = nla_get_u16(data[IFLA_GRE_ERSPAN_HWID]);

			अगर (hwid & ~(HWID_MASK >> HWID_OFFSET))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ip6erspan_set_version(काष्ठा nlattr *data[],
				  काष्ठा __ip6_tnl_parm *parms)
अणु
	अगर (!data)
		वापस;

	parms->erspan_ver = 1;
	अगर (data[IFLA_GRE_ERSPAN_VER])
		parms->erspan_ver = nla_get_u8(data[IFLA_GRE_ERSPAN_VER]);

	अगर (parms->erspan_ver == 1) अणु
		अगर (data[IFLA_GRE_ERSPAN_INDEX])
			parms->index = nla_get_u32(data[IFLA_GRE_ERSPAN_INDEX]);
	पूर्ण अन्यथा अगर (parms->erspan_ver == 2) अणु
		अगर (data[IFLA_GRE_ERSPAN_सूची])
			parms->dir = nla_get_u8(data[IFLA_GRE_ERSPAN_सूची]);
		अगर (data[IFLA_GRE_ERSPAN_HWID])
			parms->hwid = nla_get_u16(data[IFLA_GRE_ERSPAN_HWID]);
	पूर्ण
पूर्ण

अटल व्योम ip6gre_netlink_parms(काष्ठा nlattr *data[],
				काष्ठा __ip6_tnl_parm *parms)
अणु
	स_रखो(parms, 0, माप(*parms));

	अगर (!data)
		वापस;

	अगर (data[IFLA_GRE_LINK])
		parms->link = nla_get_u32(data[IFLA_GRE_LINK]);

	अगर (data[IFLA_GRE_IFLAGS])
		parms->i_flags = gre_flags_to_tnl_flags(
				nla_get_be16(data[IFLA_GRE_IFLAGS]));

	अगर (data[IFLA_GRE_OFLAGS])
		parms->o_flags = gre_flags_to_tnl_flags(
				nla_get_be16(data[IFLA_GRE_OFLAGS]));

	अगर (data[IFLA_GRE_IKEY])
		parms->i_key = nla_get_be32(data[IFLA_GRE_IKEY]);

	अगर (data[IFLA_GRE_OKEY])
		parms->o_key = nla_get_be32(data[IFLA_GRE_OKEY]);

	अगर (data[IFLA_GRE_LOCAL])
		parms->laddr = nla_get_in6_addr(data[IFLA_GRE_LOCAL]);

	अगर (data[IFLA_GRE_REMOTE])
		parms->raddr = nla_get_in6_addr(data[IFLA_GRE_REMOTE]);

	अगर (data[IFLA_GRE_TTL])
		parms->hop_limit = nla_get_u8(data[IFLA_GRE_TTL]);

	अगर (data[IFLA_GRE_ENCAP_LIMIT])
		parms->encap_limit = nla_get_u8(data[IFLA_GRE_ENCAP_LIMIT]);

	अगर (data[IFLA_GRE_FLOWINFO])
		parms->flowinfo = nla_get_be32(data[IFLA_GRE_FLOWINFO]);

	अगर (data[IFLA_GRE_FLAGS])
		parms->flags = nla_get_u32(data[IFLA_GRE_FLAGS]);

	अगर (data[IFLA_GRE_FWMARK])
		parms->fwmark = nla_get_u32(data[IFLA_GRE_FWMARK]);

	अगर (data[IFLA_GRE_COLLECT_METADATA])
		parms->collect_md = true;
पूर्ण

अटल पूर्णांक ip6gre_tap_init(काष्ठा net_device *dev)
अणु
	पूर्णांक ret;

	ret = ip6gre_tunnel_init_common(dev);
	अगर (ret)
		वापस ret;

	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ip6gre_tap_netdev_ops = अणु
	.nकरो_init = ip6gre_tap_init,
	.nकरो_uninit = ip6gre_tunnel_uninit,
	.nकरो_start_xmit = ip6gre_tunnel_xmit,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_change_mtu = ip6_tnl_change_mtu,
	.nकरो_get_stats64 = dev_get_tstats64,
	.nकरो_get_अगरlink = ip6_tnl_get_अगरlink,
पूर्ण;

अटल पूर्णांक ip6erspan_calc_hlen(काष्ठा ip6_tnl *tunnel)
अणु
	पूर्णांक t_hlen;

	tunnel->tun_hlen = 8;
	tunnel->hlen = tunnel->tun_hlen + tunnel->encap_hlen +
		       erspan_hdr_len(tunnel->parms.erspan_ver);

	t_hlen = tunnel->hlen + माप(काष्ठा ipv6hdr);
	tunnel->dev->needed_headroom = LL_MAX_HEADER + t_hlen;
	वापस t_hlen;
पूर्ण

अटल पूर्णांक ip6erspan_tap_init(काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *tunnel;
	पूर्णांक t_hlen;
	पूर्णांक ret;

	tunnel = netdev_priv(dev);

	tunnel->dev = dev;
	tunnel->net = dev_net(dev);
	म_नकल(tunnel->parms.name, dev->name);

	dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!dev->tstats)
		वापस -ENOMEM;

	ret = dst_cache_init(&tunnel->dst_cache, GFP_KERNEL);
	अगर (ret)
		जाओ cleanup_alloc_pcpu_stats;

	ret = gro_cells_init(&tunnel->gro_cells, dev);
	अगर (ret)
		जाओ cleanup_dst_cache_init;

	t_hlen = ip6erspan_calc_hlen(tunnel);
	dev->mtu = ETH_DATA_LEN - t_hlen;
	अगर (dev->type == ARPHRD_ETHER)
		dev->mtu -= ETH_HLEN;
	अगर (!(tunnel->parms.flags & IP6_TNL_F_IGN_ENCAP_LIMIT))
		dev->mtu -= 8;

	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	ip6erspan_tnl_link_config(tunnel, 1);

	dev_hold(dev);
	वापस 0;

cleanup_dst_cache_init:
	dst_cache_destroy(&tunnel->dst_cache);
cleanup_alloc_pcpu_stats:
	मुक्त_percpu(dev->tstats);
	dev->tstats = शून्य;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ip6erspan_netdev_ops = अणु
	.nकरो_init =		ip6erspan_tap_init,
	.nकरो_uninit =		ip6erspan_tunnel_uninit,
	.nकरो_start_xmit =	ip6erspan_tunnel_xmit,
	.nकरो_set_mac_address =	eth_mac_addr,
	.nकरो_validate_addr =	eth_validate_addr,
	.nकरो_change_mtu =	ip6_tnl_change_mtu,
	.nकरो_get_stats64 =	dev_get_tstats64,
	.nकरो_get_अगरlink =	ip6_tnl_get_अगरlink,
पूर्ण;

अटल व्योम ip6gre_tap_setup(काष्ठा net_device *dev)
अणु

	ether_setup(dev);

	dev->max_mtu = 0;
	dev->netdev_ops = &ip6gre_tap_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = ip6gre_dev_मुक्त;

	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netअगर_keep_dst(dev);
पूर्ण

अटल bool ip6gre_netlink_encap_parms(काष्ठा nlattr *data[],
				       काष्ठा ip_tunnel_encap *ipencap)
अणु
	bool ret = false;

	स_रखो(ipencap, 0, माप(*ipencap));

	अगर (!data)
		वापस ret;

	अगर (data[IFLA_GRE_ENCAP_TYPE]) अणु
		ret = true;
		ipencap->type = nla_get_u16(data[IFLA_GRE_ENCAP_TYPE]);
	पूर्ण

	अगर (data[IFLA_GRE_ENCAP_FLAGS]) अणु
		ret = true;
		ipencap->flags = nla_get_u16(data[IFLA_GRE_ENCAP_FLAGS]);
	पूर्ण

	अगर (data[IFLA_GRE_ENCAP_SPORT]) अणु
		ret = true;
		ipencap->sport = nla_get_be16(data[IFLA_GRE_ENCAP_SPORT]);
	पूर्ण

	अगर (data[IFLA_GRE_ENCAP_DPORT]) अणु
		ret = true;
		ipencap->dport = nla_get_be16(data[IFLA_GRE_ENCAP_DPORT]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ip6gre_newlink_common(काष्ठा net *src_net, काष्ठा net_device *dev,
				 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6_tnl *nt;
	काष्ठा ip_tunnel_encap ipencap;
	पूर्णांक err;

	nt = netdev_priv(dev);

	अगर (ip6gre_netlink_encap_parms(data, &ipencap)) अणु
		पूर्णांक err = ip6_tnl_encap_setup(nt, &ipencap);

		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (dev->type == ARPHRD_ETHER && !tb[IFLA_ADDRESS])
		eth_hw_addr_अक्रमom(dev);

	nt->dev = dev;
	nt->net = dev_net(dev);

	err = रेजिस्टर_netdevice(dev);
	अगर (err)
		जाओ out;

	अगर (tb[IFLA_MTU])
		ip6_tnl_change_mtu(dev, nla_get_u32(tb[IFLA_MTU]));

out:
	वापस err;
पूर्ण

अटल पूर्णांक ip6gre_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6_tnl *nt = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6gre_net *ign;
	पूर्णांक err;

	ip6gre_netlink_parms(data, &nt->parms);
	ign = net_generic(net, ip6gre_net_id);

	अगर (nt->parms.collect_md) अणु
		अगर (rtnl_dereference(ign->collect_md_tun))
			वापस -EEXIST;
	पूर्ण अन्यथा अणु
		अगर (ip6gre_tunnel_find(net, &nt->parms, dev->type))
			वापस -EEXIST;
	पूर्ण

	err = ip6gre_newlink_common(src_net, dev, tb, data, extack);
	अगर (!err) अणु
		ip6gre_tnl_link_config(nt, !tb[IFLA_MTU]);
		ip6gre_tunnel_link_md(ign, nt);
		ip6gre_tunnel_link(net_generic(net, ip6gre_net_id), nt);
	पूर्ण
	वापस err;
पूर्ण

अटल काष्ठा ip6_tnl *
ip6gre_changelink_common(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			 काष्ठा nlattr *data[], काष्ठा __ip6_tnl_parm *p_p,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6_tnl *t, *nt = netdev_priv(dev);
	काष्ठा net *net = nt->net;
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);
	काष्ठा ip_tunnel_encap ipencap;

	अगर (dev == ign->fb_tunnel_dev)
		वापस ERR_PTR(-EINVAL);

	अगर (ip6gre_netlink_encap_parms(data, &ipencap)) अणु
		पूर्णांक err = ip6_tnl_encap_setup(nt, &ipencap);

		अगर (err < 0)
			वापस ERR_PTR(err);
	पूर्ण

	ip6gre_netlink_parms(data, p_p);

	t = ip6gre_tunnel_locate(net, p_p, 0);

	अगर (t) अणु
		अगर (t->dev != dev)
			वापस ERR_PTR(-EEXIST);
	पूर्ण अन्यथा अणु
		t = nt;
	पूर्ण

	वापस t;
पूर्ण

अटल पूर्णांक ip6gre_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
			     काष्ठा nlattr *data[],
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा ip6gre_net *ign = net_generic(t->net, ip6gre_net_id);
	काष्ठा __ip6_tnl_parm p;

	t = ip6gre_changelink_common(dev, tb, data, &p, extack);
	अगर (IS_ERR(t))
		वापस PTR_ERR(t);

	ip6gre_tunnel_unlink_md(ign, t);
	ip6gre_tunnel_unlink(ign, t);
	ip6gre_tnl_change(t, &p, !tb[IFLA_MTU]);
	ip6gre_tunnel_link_md(ign, t);
	ip6gre_tunnel_link(ign, t);
	वापस 0;
पूर्ण

अटल व्योम ip6gre_dellink(काष्ठा net_device *dev, काष्ठा list_head *head)
अणु
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6gre_net *ign = net_generic(net, ip6gre_net_id);

	अगर (dev != ign->fb_tunnel_dev)
		unरेजिस्टर_netdevice_queue(dev, head);
पूर्ण

अटल माप_प्रकार ip6gre_get_size(स्थिर काष्ठा net_device *dev)
अणु
	वापस
		/* IFLA_GRE_LINK */
		nla_total_size(4) +
		/* IFLA_GRE_IFLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_OFLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_IKEY */
		nla_total_size(4) +
		/* IFLA_GRE_OKEY */
		nla_total_size(4) +
		/* IFLA_GRE_LOCAL */
		nla_total_size(माप(काष्ठा in6_addr)) +
		/* IFLA_GRE_REMOTE */
		nla_total_size(माप(काष्ठा in6_addr)) +
		/* IFLA_GRE_TTL */
		nla_total_size(1) +
		/* IFLA_GRE_ENCAP_LIMIT */
		nla_total_size(1) +
		/* IFLA_GRE_FLOWINFO */
		nla_total_size(4) +
		/* IFLA_GRE_FLAGS */
		nla_total_size(4) +
		/* IFLA_GRE_ENCAP_TYPE */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_FLAGS */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_SPORT */
		nla_total_size(2) +
		/* IFLA_GRE_ENCAP_DPORT */
		nla_total_size(2) +
		/* IFLA_GRE_COLLECT_METADATA */
		nla_total_size(0) +
		/* IFLA_GRE_FWMARK */
		nla_total_size(4) +
		/* IFLA_GRE_ERSPAN_INDEX */
		nla_total_size(4) +
		0;
पूर्ण

अटल पूर्णांक ip6gre_fill_info(काष्ठा sk_buff *skb, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ip6_tnl *t = netdev_priv(dev);
	काष्ठा __ip6_tnl_parm *p = &t->parms;
	__be16 o_flags = p->o_flags;

	अगर (p->erspan_ver == 1 || p->erspan_ver == 2) अणु
		अगर (!p->collect_md)
			o_flags |= TUNNEL_KEY;

		अगर (nla_put_u8(skb, IFLA_GRE_ERSPAN_VER, p->erspan_ver))
			जाओ nla_put_failure;

		अगर (p->erspan_ver == 1) अणु
			अगर (nla_put_u32(skb, IFLA_GRE_ERSPAN_INDEX, p->index))
				जाओ nla_put_failure;
		पूर्ण अन्यथा अणु
			अगर (nla_put_u8(skb, IFLA_GRE_ERSPAN_सूची, p->dir))
				जाओ nla_put_failure;
			अगर (nla_put_u16(skb, IFLA_GRE_ERSPAN_HWID, p->hwid))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (nla_put_u32(skb, IFLA_GRE_LINK, p->link) ||
	    nla_put_be16(skb, IFLA_GRE_IFLAGS,
			 gre_tnl_flags_to_gre_flags(p->i_flags)) ||
	    nla_put_be16(skb, IFLA_GRE_OFLAGS,
			 gre_tnl_flags_to_gre_flags(o_flags)) ||
	    nla_put_be32(skb, IFLA_GRE_IKEY, p->i_key) ||
	    nla_put_be32(skb, IFLA_GRE_OKEY, p->o_key) ||
	    nla_put_in6_addr(skb, IFLA_GRE_LOCAL, &p->laddr) ||
	    nla_put_in6_addr(skb, IFLA_GRE_REMOTE, &p->raddr) ||
	    nla_put_u8(skb, IFLA_GRE_TTL, p->hop_limit) ||
	    nla_put_u8(skb, IFLA_GRE_ENCAP_LIMIT, p->encap_limit) ||
	    nla_put_be32(skb, IFLA_GRE_FLOWINFO, p->flowinfo) ||
	    nla_put_u32(skb, IFLA_GRE_FLAGS, p->flags) ||
	    nla_put_u32(skb, IFLA_GRE_FWMARK, p->fwmark))
		जाओ nla_put_failure;

	अगर (nla_put_u16(skb, IFLA_GRE_ENCAP_TYPE,
			t->encap.type) ||
	    nla_put_be16(skb, IFLA_GRE_ENCAP_SPORT,
			 t->encap.sport) ||
	    nla_put_be16(skb, IFLA_GRE_ENCAP_DPORT,
			 t->encap.dport) ||
	    nla_put_u16(skb, IFLA_GRE_ENCAP_FLAGS,
			t->encap.flags))
		जाओ nla_put_failure;

	अगर (p->collect_md) अणु
		अगर (nla_put_flag(skb, IFLA_GRE_COLLECT_METADATA))
			जाओ nla_put_failure;
	पूर्ण

	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल स्थिर काष्ठा nla_policy ip6gre_policy[IFLA_GRE_MAX + 1] = अणु
	[IFLA_GRE_LINK]        = अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_IFLAGS]      = अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_OFLAGS]      = अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_IKEY]        = अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_OKEY]        = अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_LOCAL]       = अणु .len = माप_field(काष्ठा ipv6hdr, saddr) पूर्ण,
	[IFLA_GRE_REMOTE]      = अणु .len = माप_field(काष्ठा ipv6hdr, daddr) पूर्ण,
	[IFLA_GRE_TTL]         = अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_ENCAP_LIMIT] = अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_FLOWINFO]    = अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_FLAGS]       = अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_ENCAP_TYPE]   = अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_ENCAP_FLAGS]  = अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_ENCAP_SPORT]  = अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_ENCAP_DPORT]  = अणु .type = NLA_U16 पूर्ण,
	[IFLA_GRE_COLLECT_METADATA] = अणु .type = NLA_FLAG पूर्ण,
	[IFLA_GRE_FWMARK]       = अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_ERSPAN_INDEX] = अणु .type = NLA_U32 पूर्ण,
	[IFLA_GRE_ERSPAN_VER]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_ERSPAN_सूची]	= अणु .type = NLA_U8 पूर्ण,
	[IFLA_GRE_ERSPAN_HWID]	= अणु .type = NLA_U16 पूर्ण,
पूर्ण;

अटल व्योम ip6erspan_tap_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->max_mtu = 0;
	dev->netdev_ops = &ip6erspan_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = ip6gre_dev_मुक्त;

	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netअगर_keep_dst(dev);
पूर्ण

अटल पूर्णांक ip6erspan_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
			     काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6_tnl *nt = netdev_priv(dev);
	काष्ठा net *net = dev_net(dev);
	काष्ठा ip6gre_net *ign;
	पूर्णांक err;

	ip6gre_netlink_parms(data, &nt->parms);
	ip6erspan_set_version(data, &nt->parms);
	ign = net_generic(net, ip6gre_net_id);

	अगर (nt->parms.collect_md) अणु
		अगर (rtnl_dereference(ign->collect_md_tun_erspan))
			वापस -EEXIST;
	पूर्ण अन्यथा अणु
		अगर (ip6gre_tunnel_find(net, &nt->parms, dev->type))
			वापस -EEXIST;
	पूर्ण

	err = ip6gre_newlink_common(src_net, dev, tb, data, extack);
	अगर (!err) अणु
		ip6erspan_tnl_link_config(nt, !tb[IFLA_MTU]);
		ip6erspan_tunnel_link_md(ign, nt);
		ip6gre_tunnel_link(net_generic(net, ip6gre_net_id), nt);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम ip6erspan_tnl_link_config(काष्ठा ip6_tnl *t, पूर्णांक set_mtu)
अणु
	ip6gre_tnl_link_config_common(t);
	ip6gre_tnl_link_config_route(t, set_mtu, ip6erspan_calc_hlen(t));
पूर्ण

अटल पूर्णांक ip6erspan_tnl_change(काष्ठा ip6_tnl *t,
				स्थिर काष्ठा __ip6_tnl_parm *p, पूर्णांक set_mtu)
अणु
	ip6gre_tnl_copy_tnl_parm(t, p);
	ip6erspan_tnl_link_config(t, set_mtu);
	वापस 0;
पूर्ण

अटल पूर्णांक ip6erspan_changelink(काष्ठा net_device *dev, काष्ठा nlattr *tb[],
				काष्ठा nlattr *data[],
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा ip6gre_net *ign = net_generic(dev_net(dev), ip6gre_net_id);
	काष्ठा __ip6_tnl_parm p;
	काष्ठा ip6_tnl *t;

	t = ip6gre_changelink_common(dev, tb, data, &p, extack);
	अगर (IS_ERR(t))
		वापस PTR_ERR(t);

	ip6erspan_set_version(data, &p);
	ip6gre_tunnel_unlink_md(ign, t);
	ip6gre_tunnel_unlink(ign, t);
	ip6erspan_tnl_change(t, &p, !tb[IFLA_MTU]);
	ip6erspan_tunnel_link_md(ign, t);
	ip6gre_tunnel_link(ign, t);
	वापस 0;
पूर्ण

अटल काष्ठा rtnl_link_ops ip6gre_link_ops __पढ़ो_mostly = अणु
	.kind		= "ip6gre",
	.maxtype	= IFLA_GRE_MAX,
	.policy		= ip6gre_policy,
	.priv_size	= माप(काष्ठा ip6_tnl),
	.setup		= ip6gre_tunnel_setup,
	.validate	= ip6gre_tunnel_validate,
	.newlink	= ip6gre_newlink,
	.changelink	= ip6gre_changelink,
	.dellink	= ip6gre_dellink,
	.get_size	= ip6gre_get_size,
	.fill_info	= ip6gre_fill_info,
	.get_link_net	= ip6_tnl_get_link_net,
पूर्ण;

अटल काष्ठा rtnl_link_ops ip6gre_tap_ops __पढ़ो_mostly = अणु
	.kind		= "ip6gretap",
	.maxtype	= IFLA_GRE_MAX,
	.policy		= ip6gre_policy,
	.priv_size	= माप(काष्ठा ip6_tnl),
	.setup		= ip6gre_tap_setup,
	.validate	= ip6gre_tap_validate,
	.newlink	= ip6gre_newlink,
	.changelink	= ip6gre_changelink,
	.get_size	= ip6gre_get_size,
	.fill_info	= ip6gre_fill_info,
	.get_link_net	= ip6_tnl_get_link_net,
पूर्ण;

अटल काष्ठा rtnl_link_ops ip6erspan_tap_ops __पढ़ो_mostly = अणु
	.kind		= "ip6erspan",
	.maxtype	= IFLA_GRE_MAX,
	.policy		= ip6gre_policy,
	.priv_size	= माप(काष्ठा ip6_tnl),
	.setup		= ip6erspan_tap_setup,
	.validate	= ip6erspan_tap_validate,
	.newlink	= ip6erspan_newlink,
	.changelink	= ip6erspan_changelink,
	.get_size	= ip6gre_get_size,
	.fill_info	= ip6gre_fill_info,
	.get_link_net	= ip6_tnl_get_link_net,
पूर्ण;

/*
 *	And now the modules code and kernel पूर्णांकerface.
 */

अटल पूर्णांक __init ip6gre_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("GRE over IPv6 tunneling driver\n");

	err = रेजिस्टर_pernet_device(&ip6gre_net_ops);
	अगर (err < 0)
		वापस err;

	err = inet6_add_protocol(&ip6gre_protocol, IPPROTO_GRE);
	अगर (err < 0) अणु
		pr_info("%s: can't add protocol\n", __func__);
		जाओ add_proto_failed;
	पूर्ण

	err = rtnl_link_रेजिस्टर(&ip6gre_link_ops);
	अगर (err < 0)
		जाओ rtnl_link_failed;

	err = rtnl_link_रेजिस्टर(&ip6gre_tap_ops);
	अगर (err < 0)
		जाओ tap_ops_failed;

	err = rtnl_link_रेजिस्टर(&ip6erspan_tap_ops);
	अगर (err < 0)
		जाओ erspan_link_failed;

out:
	वापस err;

erspan_link_failed:
	rtnl_link_unरेजिस्टर(&ip6gre_tap_ops);
tap_ops_failed:
	rtnl_link_unरेजिस्टर(&ip6gre_link_ops);
rtnl_link_failed:
	inet6_del_protocol(&ip6gre_protocol, IPPROTO_GRE);
add_proto_failed:
	unरेजिस्टर_pernet_device(&ip6gre_net_ops);
	जाओ out;
पूर्ण

अटल व्योम __निकास ip6gre_fini(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&ip6gre_tap_ops);
	rtnl_link_unरेजिस्टर(&ip6gre_link_ops);
	rtnl_link_unरेजिस्टर(&ip6erspan_tap_ops);
	inet6_del_protocol(&ip6gre_protocol, IPPROTO_GRE);
	unरेजिस्टर_pernet_device(&ip6gre_net_ops);
पूर्ण

module_init(ip6gre_init);
module_निकास(ip6gre_fini);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("D. Kozlov (xeb@mail.ru)");
MODULE_DESCRIPTION("GRE over IPv6 tunneling device");
MODULE_ALIAS_RTNL_LINK("ip6gre");
MODULE_ALIAS_RTNL_LINK("ip6gretap");
MODULE_ALIAS_RTNL_LINK("ip6erspan");
MODULE_ALIAS_NETDEV("ip6gre0");
