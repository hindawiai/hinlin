<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ip_vs_xmit.c: various packet transmitters क्रम IPVS
 *
 * Authors:     Wensong Zhang <wensong@linuxभवserver.org>
 *              Julian Anastasov <ja@ssi.bg>
 *
 * Changes:
 *
 * Description of क्रमwarding methods:
 * - all transmitters are called from LOCAL_IN (remote clients) and
 * LOCAL_OUT (local clients) but क्रम ICMP can be called from FORWARD
 * - not all connections have destination server, क्रम example,
 * connections in backup server when fwmark is used
 * - bypass connections use daddr from packet
 * - we can use dst without ref जबतक sending in RCU section, we use
 * ref when वापसing NF_ACCEPT क्रम NAT-ed packet via loopback
 * LOCAL_OUT rules:
 * - skb->dev is शून्य, skb->protocol is not set (both are set in POST_ROUTING)
 * - skb->pkt_type is not set yet
 * - the only place where we can see skb->sk != शून्य
 */

#घोषणा KMSG_COMPONENT "IPVS"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/tcp.h>                  /* क्रम tcphdr */
#समावेश <net/ip.h>
#समावेश <net/gue.h>
#समावेश <net/gre.h>
#समावेश <net/tcp.h>                    /* क्रम csum_tcpudp_magic */
#समावेश <net/udp.h>
#समावेश <net/icmp.h>                   /* क्रम icmp_send */
#समावेश <net/route.h>                  /* क्रम ip_route_output */
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/addrconf.h>
#समावेश <linux/icmpv6.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>

#समावेश <net/ip_vs.h>

क्रमागत अणु
	IP_VS_RT_MODE_LOCAL	= 1, /* Allow local dest */
	IP_VS_RT_MODE_NON_LOCAL	= 2, /* Allow non-local dest */
	IP_VS_RT_MODE_RDR	= 4, /* Allow redirect from remote daddr to
				      * local
				      */
	IP_VS_RT_MODE_CONNECT	= 8, /* Always bind route to saddr */
	IP_VS_RT_MODE_KNOWN_NH	= 16,/* Route via remote addr */
	IP_VS_RT_MODE_TUNNEL	= 32,/* Tunnel mode */
पूर्ण;

अटल अंतरभूत काष्ठा ip_vs_dest_dst *ip_vs_dest_dst_alloc(व्योम)
अणु
	वापस kदो_स्मृति(माप(काष्ठा ip_vs_dest_dst), GFP_ATOMIC);
पूर्ण

अटल अंतरभूत व्योम ip_vs_dest_dst_मुक्त(काष्ठा ip_vs_dest_dst *dest_dst)
अणु
	kमुक्त(dest_dst);
पूर्ण

/*
 *      Destination cache to speed up outgoing route lookup
 */
अटल अंतरभूत व्योम
__ip_vs_dst_set(काष्ठा ip_vs_dest *dest, काष्ठा ip_vs_dest_dst *dest_dst,
		काष्ठा dst_entry *dst, u32 dst_cookie)
अणु
	काष्ठा ip_vs_dest_dst *old;

	old = rcu_dereference_रक्षित(dest->dest_dst,
					lockdep_is_held(&dest->dst_lock));

	अगर (dest_dst) अणु
		dest_dst->dst_cache = dst;
		dest_dst->dst_cookie = dst_cookie;
	पूर्ण
	rcu_assign_poपूर्णांकer(dest->dest_dst, dest_dst);

	अगर (old)
		call_rcu(&old->rcu_head, ip_vs_dest_dst_rcu_मुक्त);
पूर्ण

अटल अंतरभूत काष्ठा ip_vs_dest_dst *
__ip_vs_dst_check(काष्ठा ip_vs_dest *dest)
अणु
	काष्ठा ip_vs_dest_dst *dest_dst = rcu_dereference(dest->dest_dst);
	काष्ठा dst_entry *dst;

	अगर (!dest_dst)
		वापस शून्य;
	dst = dest_dst->dst_cache;
	अगर (dst->obsolete &&
	    dst->ops->check(dst, dest_dst->dst_cookie) == शून्य)
		वापस शून्य;
	वापस dest_dst;
पूर्ण

अटल अंतरभूत bool
__mtu_check_toobig_v6(स्थिर काष्ठा sk_buff *skb, u32 mtu)
अणु
	अगर (IP6CB(skb)->frag_max_size) अणु
		/* frag_max_size tell us that, this packet have been
		 * defragmented by netfilter IPv6 conntrack module.
		 */
		अगर (IP6CB(skb)->frag_max_size > mtu)
			वापस true; /* largest fragment violate MTU */
	पूर्ण
	अन्यथा अगर (skb->len > mtu && !skb_is_gso(skb)) अणु
		वापस true; /* Packet size violate MTU size */
	पूर्ण
	वापस false;
पूर्ण

/* Get route to daddr, update *saddr, optionally bind route to saddr */
अटल काष्ठा rtable *करो_output_route4(काष्ठा net *net, __be32 daddr,
				       पूर्णांक rt_mode, __be32 *saddr)
अणु
	काष्ठा flowi4 fl4;
	काष्ठा rtable *rt;
	bool loop = false;

	स_रखो(&fl4, 0, माप(fl4));
	fl4.daddr = daddr;
	fl4.flowi4_flags = (rt_mode & IP_VS_RT_MODE_KNOWN_NH) ?
			   FLOWI_FLAG_KNOWN_NH : 0;

retry:
	rt = ip_route_output_key(net, &fl4);
	अगर (IS_ERR(rt)) अणु
		/* Invalid saddr ? */
		अगर (PTR_ERR(rt) == -EINVAL && *saddr &&
		    rt_mode & IP_VS_RT_MODE_CONNECT && !loop) अणु
			*saddr = 0;
			flowi4_update_output(&fl4, 0, 0, daddr, 0);
			जाओ retry;
		पूर्ण
		IP_VS_DBG_RL("ip_route_output error, dest: %pI4\n", &daddr);
		वापस शून्य;
	पूर्ण अन्यथा अगर (!*saddr && rt_mode & IP_VS_RT_MODE_CONNECT && fl4.saddr) अणु
		ip_rt_put(rt);
		*saddr = fl4.saddr;
		flowi4_update_output(&fl4, 0, 0, daddr, fl4.saddr);
		loop = true;
		जाओ retry;
	पूर्ण
	*saddr = fl4.saddr;
	वापस rt;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल अंतरभूत पूर्णांक __ip_vs_is_local_route6(काष्ठा rt6_info *rt)
अणु
	वापस rt->dst.dev && rt->dst.dev->flags & IFF_LOOPBACK;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool crosses_local_route_boundary(पूर्णांक skb_af, काष्ठा sk_buff *skb,
						पूर्णांक rt_mode,
						bool new_rt_is_local)
अणु
	bool rt_mode_allow_local = !!(rt_mode & IP_VS_RT_MODE_LOCAL);
	bool rt_mode_allow_non_local = !!(rt_mode & IP_VS_RT_MODE_NON_LOCAL);
	bool rt_mode_allow_redirect = !!(rt_mode & IP_VS_RT_MODE_RDR);
	bool source_is_loopback;
	bool old_rt_is_local;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (skb_af == AF_INET6) अणु
		पूर्णांक addr_type = ipv6_addr_type(&ipv6_hdr(skb)->saddr);

		source_is_loopback =
			(!skb->dev || skb->dev->flags & IFF_LOOPBACK) &&
			(addr_type & IPV6_ADDR_LOOPBACK);
		old_rt_is_local = __ip_vs_is_local_route6(
			(काष्ठा rt6_info *)skb_dst(skb));
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		source_is_loopback = ipv4_is_loopback(ip_hdr(skb)->saddr);
		old_rt_is_local = skb_rtable(skb)->rt_flags & RTCF_LOCAL;
	पूर्ण

	अगर (unlikely(new_rt_is_local)) अणु
		अगर (!rt_mode_allow_local)
			वापस true;
		अगर (!rt_mode_allow_redirect && !old_rt_is_local)
			वापस true;
	पूर्ण अन्यथा अणु
		अगर (!rt_mode_allow_non_local)
			वापस true;
		अगर (source_is_loopback)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम maybe_update_pmtu(पूर्णांक skb_af, काष्ठा sk_buff *skb, पूर्णांक mtu)
अणु
	काष्ठा sock *sk = skb->sk;
	काष्ठा rtable *ort = skb_rtable(skb);

	अगर (!skb->dev && sk && sk_fullsock(sk))
		ort->dst.ops->update_pmtu(&ort->dst, sk, शून्य, mtu, true);
पूर्ण

अटल अंतरभूत bool ensure_mtu_is_adequate(काष्ठा netns_ipvs *ipvs, पूर्णांक skb_af,
					  पूर्णांक rt_mode,
					  काष्ठा ip_vs_iphdr *ipvsh,
					  काष्ठा sk_buff *skb, पूर्णांक mtu)
अणु
#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (skb_af == AF_INET6) अणु
		काष्ठा net *net = ipvs->net;

		अगर (unlikely(__mtu_check_toobig_v6(skb, mtu))) अणु
			अगर (!skb->dev)
				skb->dev = net->loopback_dev;
			/* only send ICMP too big on first fragment */
			अगर (!ipvsh->fragoffs && !ip_vs_iph_icmp(ipvsh))
				icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
			IP_VS_DBG(1, "frag needed for %pI6c\n",
				  &ipv6_hdr(skb)->saddr);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		/* If we're going to tunnel the packet and pmtu discovery
		 * is disabled, we'll just fragment it anyway
		 */
		अगर ((rt_mode & IP_VS_RT_MODE_TUNNEL) && !sysctl_pmtu_disc(ipvs))
			वापस true;

		अगर (unlikely(ip_hdr(skb)->frag_off & htons(IP_DF) &&
			     skb->len > mtu && !skb_is_gso(skb) &&
			     !ip_vs_iph_icmp(ipvsh))) अणु
			icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
				  htonl(mtu));
			IP_VS_DBG(1, "frag needed for %pI4\n",
				  &ip_hdr(skb)->saddr);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत bool decrement_ttl(काष्ठा netns_ipvs *ipvs,
				 पूर्णांक skb_af,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = ipvs->net;

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (skb_af == AF_INET6) अणु
		काष्ठा dst_entry *dst = skb_dst(skb);

		/* check and decrement ttl */
		अगर (ipv6_hdr(skb)->hop_limit <= 1) अणु
			काष्ठा inet6_dev *idev = __in6_dev_get_safely(skb->dev);

			/* Force OUTPUT device used as source address */
			skb->dev = dst->dev;
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPLIMIT, 0);
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDRERRORS);

			वापस false;
		पूर्ण

		/* करोn't propagate ttl change to cloned packets */
		अगर (skb_ensure_writable(skb, माप(काष्ठा ipv6hdr)))
			वापस false;

		ipv6_hdr(skb)->hop_limit--;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		अगर (ip_hdr(skb)->ttl <= 1) अणु
			/* Tell the sender its packet died... */
			__IP_INC_STATS(net, IPSTATS_MIB_INHDRERRORS);
			icmp_send(skb, ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, 0);
			वापस false;
		पूर्ण

		/* करोn't propagate ttl change to cloned packets */
		अगर (skb_ensure_writable(skb, माप(काष्ठा iphdr)))
			वापस false;

		/* Decrease ttl */
		ip_decrease_ttl(ip_hdr(skb));
	पूर्ण

	वापस true;
पूर्ण

/* Get route to destination or remote server */
अटल पूर्णांक
__ip_vs_get_out_rt(काष्ठा netns_ipvs *ipvs, पूर्णांक skb_af, काष्ठा sk_buff *skb,
		   काष्ठा ip_vs_dest *dest,
		   __be32 daddr, पूर्णांक rt_mode, __be32 *ret_saddr,
		   काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा net *net = ipvs->net;
	काष्ठा ip_vs_dest_dst *dest_dst;
	काष्ठा rtable *rt;			/* Route to the other host */
	पूर्णांक mtu;
	पूर्णांक local, noref = 1;

	अगर (dest) अणु
		dest_dst = __ip_vs_dst_check(dest);
		अगर (likely(dest_dst))
			rt = (काष्ठा rtable *) dest_dst->dst_cache;
		अन्यथा अणु
			dest_dst = ip_vs_dest_dst_alloc();
			spin_lock_bh(&dest->dst_lock);
			अगर (!dest_dst) अणु
				__ip_vs_dst_set(dest, शून्य, शून्य, 0);
				spin_unlock_bh(&dest->dst_lock);
				जाओ err_unreach;
			पूर्ण
			rt = करो_output_route4(net, dest->addr.ip, rt_mode,
					      &dest_dst->dst_saddr.ip);
			अगर (!rt) अणु
				__ip_vs_dst_set(dest, शून्य, शून्य, 0);
				spin_unlock_bh(&dest->dst_lock);
				ip_vs_dest_dst_मुक्त(dest_dst);
				जाओ err_unreach;
			पूर्ण
			__ip_vs_dst_set(dest, dest_dst, &rt->dst, 0);
			spin_unlock_bh(&dest->dst_lock);
			IP_VS_DBG(10, "new dst %pI4, src %pI4, refcnt=%d\n",
				  &dest->addr.ip, &dest_dst->dst_saddr.ip,
				  atomic_पढ़ो(&rt->dst.__refcnt));
		पूर्ण
		अगर (ret_saddr)
			*ret_saddr = dest_dst->dst_saddr.ip;
	पूर्ण अन्यथा अणु
		__be32 saddr = htonl(INADDR_ANY);

		noref = 0;

		/* For such unconfigured boxes aव्योम many route lookups
		 * क्रम perक्रमmance reasons because we करो not remember saddr
		 */
		rt_mode &= ~IP_VS_RT_MODE_CONNECT;
		rt = करो_output_route4(net, daddr, rt_mode, &saddr);
		अगर (!rt)
			जाओ err_unreach;
		अगर (ret_saddr)
			*ret_saddr = saddr;
	पूर्ण

	local = (rt->rt_flags & RTCF_LOCAL) ? 1 : 0;
	अगर (unlikely(crosses_local_route_boundary(skb_af, skb, rt_mode,
						  local))) अणु
		IP_VS_DBG_RL("We are crossing local and non-local addresses"
			     " daddr=%pI4\n", &daddr);
		जाओ err_put;
	पूर्ण

	अगर (unlikely(local)) अणु
		/* skb to local stack, preserve old route */
		अगर (!noref)
			ip_rt_put(rt);
		वापस local;
	पूर्ण

	अगर (!decrement_ttl(ipvs, skb_af, skb))
		जाओ err_put;

	अगर (likely(!(rt_mode & IP_VS_RT_MODE_TUNNEL))) अणु
		mtu = dst_mtu(&rt->dst);
	पूर्ण अन्यथा अणु
		mtu = dst_mtu(&rt->dst) - माप(काष्ठा iphdr);
		अगर (!dest)
			जाओ err_put;
		अगर (dest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
			mtu -= माप(काष्ठा udphdr) + माप(काष्ठा guehdr);
			अगर ((dest->tun_flags &
			     IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM) &&
			    skb->ip_summed == CHECKSUM_PARTIAL)
				mtu -= GUE_PLEN_REMCSUM + GUE_LEN_PRIV;
		पूर्ण अन्यथा अगर (dest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) अणु
			__be16 tflags = 0;

			अगर (dest->tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM)
				tflags |= TUNNEL_CSUM;
			mtu -= gre_calc_hlen(tflags);
		पूर्ण
		अगर (mtu < 68) अणु
			IP_VS_DBG_RL("%s(): mtu less than 68\n", __func__);
			जाओ err_put;
		पूर्ण
		maybe_update_pmtu(skb_af, skb, mtu);
	पूर्ण

	अगर (!ensure_mtu_is_adequate(ipvs, skb_af, rt_mode, ipvsh, skb, mtu))
		जाओ err_put;

	skb_dst_drop(skb);
	अगर (noref)
		skb_dst_set_noref(skb, &rt->dst);
	अन्यथा
		skb_dst_set(skb, &rt->dst);

	वापस local;

err_put:
	अगर (!noref)
		ip_rt_put(rt);
	वापस -1;

err_unreach:
	dst_link_failure(skb);
	वापस -1;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
अटल काष्ठा dst_entry *
__ip_vs_route_output_v6(काष्ठा net *net, काष्ठा in6_addr *daddr,
			काष्ठा in6_addr *ret_saddr, पूर्णांक करो_xfrm, पूर्णांक rt_mode)
अणु
	काष्ठा dst_entry *dst;
	काष्ठा flowi6 fl6 = अणु
		.daddr = *daddr,
	पूर्ण;

	अगर (rt_mode & IP_VS_RT_MODE_KNOWN_NH)
		fl6.flowi6_flags = FLOWI_FLAG_KNOWN_NH;

	dst = ip6_route_output(net, शून्य, &fl6);
	अगर (dst->error)
		जाओ out_err;
	अगर (!ret_saddr)
		वापस dst;
	अगर (ipv6_addr_any(&fl6.saddr) &&
	    ipv6_dev_get_saddr(net, ip6_dst_idev(dst)->dev,
			       &fl6.daddr, 0, &fl6.saddr) < 0)
		जाओ out_err;
	अगर (करो_xfrm) अणु
		dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), शून्य, 0);
		अगर (IS_ERR(dst)) अणु
			dst = शून्य;
			जाओ out_err;
		पूर्ण
	पूर्ण
	*ret_saddr = fl6.saddr;
	वापस dst;

out_err:
	dst_release(dst);
	IP_VS_DBG_RL("ip6_route_output error, dest: %pI6\n", daddr);
	वापस शून्य;
पूर्ण

/*
 * Get route to destination or remote server
 */
अटल पूर्णांक
__ip_vs_get_out_rt_v6(काष्ठा netns_ipvs *ipvs, पूर्णांक skb_af, काष्ठा sk_buff *skb,
		      काष्ठा ip_vs_dest *dest,
		      काष्ठा in6_addr *daddr, काष्ठा in6_addr *ret_saddr,
		      काष्ठा ip_vs_iphdr *ipvsh, पूर्णांक करो_xfrm, पूर्णांक rt_mode)
अणु
	काष्ठा net *net = ipvs->net;
	काष्ठा ip_vs_dest_dst *dest_dst;
	काष्ठा rt6_info *rt;			/* Route to the other host */
	काष्ठा dst_entry *dst;
	पूर्णांक mtu;
	पूर्णांक local, noref = 1;

	अगर (dest) अणु
		dest_dst = __ip_vs_dst_check(dest);
		अगर (likely(dest_dst))
			rt = (काष्ठा rt6_info *) dest_dst->dst_cache;
		अन्यथा अणु
			u32 cookie;

			dest_dst = ip_vs_dest_dst_alloc();
			spin_lock_bh(&dest->dst_lock);
			अगर (!dest_dst) अणु
				__ip_vs_dst_set(dest, शून्य, शून्य, 0);
				spin_unlock_bh(&dest->dst_lock);
				जाओ err_unreach;
			पूर्ण
			dst = __ip_vs_route_output_v6(net, &dest->addr.in6,
						      &dest_dst->dst_saddr.in6,
						      करो_xfrm, rt_mode);
			अगर (!dst) अणु
				__ip_vs_dst_set(dest, शून्य, शून्य, 0);
				spin_unlock_bh(&dest->dst_lock);
				ip_vs_dest_dst_मुक्त(dest_dst);
				जाओ err_unreach;
			पूर्ण
			rt = (काष्ठा rt6_info *) dst;
			cookie = rt6_get_cookie(rt);
			__ip_vs_dst_set(dest, dest_dst, &rt->dst, cookie);
			spin_unlock_bh(&dest->dst_lock);
			IP_VS_DBG(10, "new dst %pI6, src %pI6, refcnt=%d\n",
				  &dest->addr.in6, &dest_dst->dst_saddr.in6,
				  atomic_पढ़ो(&rt->dst.__refcnt));
		पूर्ण
		अगर (ret_saddr)
			*ret_saddr = dest_dst->dst_saddr.in6;
	पूर्ण अन्यथा अणु
		noref = 0;
		dst = __ip_vs_route_output_v6(net, daddr, ret_saddr, करो_xfrm,
					      rt_mode);
		अगर (!dst)
			जाओ err_unreach;
		rt = (काष्ठा rt6_info *) dst;
	पूर्ण

	local = __ip_vs_is_local_route6(rt);

	अगर (unlikely(crosses_local_route_boundary(skb_af, skb, rt_mode,
						  local))) अणु
		IP_VS_DBG_RL("We are crossing local and non-local addresses"
			     " daddr=%pI6\n", daddr);
		जाओ err_put;
	पूर्ण

	अगर (unlikely(local)) अणु
		/* skb to local stack, preserve old route */
		अगर (!noref)
			dst_release(&rt->dst);
		वापस local;
	पूर्ण

	अगर (!decrement_ttl(ipvs, skb_af, skb))
		जाओ err_put;

	/* MTU checking */
	अगर (likely(!(rt_mode & IP_VS_RT_MODE_TUNNEL)))
		mtu = dst_mtu(&rt->dst);
	अन्यथा अणु
		mtu = dst_mtu(&rt->dst) - माप(काष्ठा ipv6hdr);
		अगर (!dest)
			जाओ err_put;
		अगर (dest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
			mtu -= माप(काष्ठा udphdr) + माप(काष्ठा guehdr);
			अगर ((dest->tun_flags &
			     IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM) &&
			    skb->ip_summed == CHECKSUM_PARTIAL)
				mtu -= GUE_PLEN_REMCSUM + GUE_LEN_PRIV;
		पूर्ण अन्यथा अगर (dest->tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) अणु
			__be16 tflags = 0;

			अगर (dest->tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM)
				tflags |= TUNNEL_CSUM;
			mtu -= gre_calc_hlen(tflags);
		पूर्ण
		अगर (mtu < IPV6_MIN_MTU) अणु
			IP_VS_DBG_RL("%s(): mtu less than %d\n", __func__,
				     IPV6_MIN_MTU);
			जाओ err_put;
		पूर्ण
		maybe_update_pmtu(skb_af, skb, mtu);
	पूर्ण

	अगर (!ensure_mtu_is_adequate(ipvs, skb_af, rt_mode, ipvsh, skb, mtu))
		जाओ err_put;

	skb_dst_drop(skb);
	अगर (noref)
		skb_dst_set_noref(skb, &rt->dst);
	अन्यथा
		skb_dst_set(skb, &rt->dst);

	वापस local;

err_put:
	अगर (!noref)
		dst_release(&rt->dst);
	वापस -1;

err_unreach:
	/* The ip6_link_failure function requires the dev field to be set
	 * in order to get the net (further क्रम the sake of fwmark
	 * reflection).
	 */
	अगर (!skb->dev)
		skb->dev = skb_dst(skb)->dev;

	dst_link_failure(skb);
	वापस -1;
पूर्ण
#पूर्ण_अगर


/* वापस NF_ACCEPT to allow क्रमwarding or other NF_xxx on error */
अटल अंतरभूत पूर्णांक ip_vs_tunnel_xmit_prepare(काष्ठा sk_buff *skb,
					    काष्ठा ip_vs_conn *cp)
अणु
	पूर्णांक ret = NF_ACCEPT;

	skb->ipvs_property = 1;
	अगर (unlikely(cp->flags & IP_VS_CONN_F_NFCT))
		ret = ip_vs_confirm_conntrack(skb);
	अगर (ret == NF_ACCEPT) अणु
		nf_reset_ct(skb);
		skb_क्रमward_csum(skb);
		अगर (skb->dev)
			skb->tstamp = 0;
	पूर्ण
	वापस ret;
पूर्ण

/* In the event of a remote destination, it's possible that we would have
 * matches against an old socket (particularly a TIME-WAIT socket). This
 * causes havoc करोwn the line (ip_local_out et. al. expect regular sockets
 * and invalid memory accesses will happen) so simply drop the association
 * in this हाल.
*/
अटल अंतरभूत व्योम ip_vs_drop_early_demux_sk(काष्ठा sk_buff *skb)
अणु
	/* If dev is set, the packet came from the LOCAL_IN callback and
	 * not from a local TCP socket.
	 */
	अगर (skb->dev)
		skb_orphan(skb);
पूर्ण

/* वापस NF_STOLEN (sent) or NF_ACCEPT अगर local=1 (not sent) */
अटल अंतरभूत पूर्णांक ip_vs_nat_send_or_cont(पूर्णांक pf, काष्ठा sk_buff *skb,
					 काष्ठा ip_vs_conn *cp, पूर्णांक local)
अणु
	पूर्णांक ret = NF_STOLEN;

	skb->ipvs_property = 1;
	अगर (likely(!(cp->flags & IP_VS_CONN_F_NFCT)))
		ip_vs_notrack(skb);
	अन्यथा
		ip_vs_update_conntrack(skb, cp, 1);

	/* Remove the early_demux association unless it's bound क्रम the
	 * exact same port and address on this host after translation.
	 */
	अगर (!local || cp->vport != cp->dport ||
	    !ip_vs_addr_equal(cp->af, &cp->vaddr, &cp->daddr))
		ip_vs_drop_early_demux_sk(skb);

	अगर (!local) अणु
		skb_क्रमward_csum(skb);
		अगर (skb->dev)
			skb->tstamp = 0;
		NF_HOOK(pf, NF_INET_LOCAL_OUT, cp->ipvs->net, शून्य, skb,
			शून्य, skb_dst(skb)->dev, dst_output);
	पूर्ण अन्यथा
		ret = NF_ACCEPT;

	वापस ret;
पूर्ण

/* वापस NF_STOLEN (sent) or NF_ACCEPT अगर local=1 (not sent) */
अटल अंतरभूत पूर्णांक ip_vs_send_or_cont(पूर्णांक pf, काष्ठा sk_buff *skb,
				     काष्ठा ip_vs_conn *cp, पूर्णांक local)
अणु
	पूर्णांक ret = NF_STOLEN;

	skb->ipvs_property = 1;
	अगर (likely(!(cp->flags & IP_VS_CONN_F_NFCT)))
		ip_vs_notrack(skb);
	अगर (!local) अणु
		ip_vs_drop_early_demux_sk(skb);
		skb_क्रमward_csum(skb);
		अगर (skb->dev)
			skb->tstamp = 0;
		NF_HOOK(pf, NF_INET_LOCAL_OUT, cp->ipvs->net, शून्य, skb,
			शून्य, skb_dst(skb)->dev, dst_output);
	पूर्ण अन्यथा
		ret = NF_ACCEPT;
	वापस ret;
पूर्ण


/*
 *      शून्य transmitter (करो nothing except वापस NF_ACCEPT)
 */
पूर्णांक
ip_vs_null_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	/* we करो not touch skb and करो not need pskb ptr */
	वापस ip_vs_send_or_cont(NFPROTO_IPV4, skb, cp, 1);
पूर्ण


/*
 *      Bypass transmitter
 *      Let packets bypass the destination when the destination is not
 *      available, it may be only used in transparent cache cluster.
 */
पूर्णांक
ip_vs_bypass_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		  काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा iphdr  *iph = ip_hdr(skb);

	EnterFunction(10);

	अगर (__ip_vs_get_out_rt(cp->ipvs, cp->af, skb, शून्य, iph->daddr,
			       IP_VS_RT_MODE_NON_LOCAL, शून्य, ipvsh) < 0)
		जाओ tx_error;

	ip_send_check(iph);

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	ip_vs_send_or_cont(NFPROTO_IPV4, skb, cp, 0);

	LeaveFunction(10);
	वापस NF_STOLEN;

 tx_error:
	kमुक्त_skb(skb);
	LeaveFunction(10);
	वापस NF_STOLEN;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
पूर्णांक
ip_vs_bypass_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		     काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);

	EnterFunction(10);

	अगर (__ip_vs_get_out_rt_v6(cp->ipvs, cp->af, skb, शून्य,
				  &iph->daddr, शून्य,
				  ipvsh, 0, IP_VS_RT_MODE_NON_LOCAL) < 0)
		जाओ tx_error;

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	ip_vs_send_or_cont(NFPROTO_IPV6, skb, cp, 0);

	LeaveFunction(10);
	वापस NF_STOLEN;

 tx_error:
	kमुक्त_skb(skb);
	LeaveFunction(10);
	वापस NF_STOLEN;
पूर्ण
#पूर्ण_अगर

/*
 *      NAT transmitter (only क्रम outside-to-inside nat क्रमwarding)
 *      Not used क्रम related ICMP
 */
पूर्णांक
ip_vs_nat_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
	       काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा rtable *rt;		/* Route to the other host */
	पूर्णांक local, rc, was_input;

	EnterFunction(10);

	/* check अगर it is a connection of no-client-port */
	अगर (unlikely(cp->flags & IP_VS_CONN_F_NO_CPORT)) अणु
		__be16 _pt, *p;

		p = skb_header_poपूर्णांकer(skb, ipvsh->len, माप(_pt), &_pt);
		अगर (p == शून्य)
			जाओ tx_error;
		ip_vs_conn_fill_cport(cp, *p);
		IP_VS_DBG(10, "filled cport=%d\n", ntohs(*p));
	पूर्ण

	was_input = rt_is_input_route(skb_rtable(skb));
	local = __ip_vs_get_out_rt(cp->ipvs, cp->af, skb, cp->dest, cp->daddr.ip,
				   IP_VS_RT_MODE_LOCAL |
				   IP_VS_RT_MODE_NON_LOCAL |
				   IP_VS_RT_MODE_RDR, शून्य, ipvsh);
	अगर (local < 0)
		जाओ tx_error;
	rt = skb_rtable(skb);
	/*
	 * Aव्योम duplicate tuple in reply direction क्रम NAT traffic
	 * to local address when connection is sync-ed
	 */
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (cp->flags & IP_VS_CONN_F_SYNC && local) अणु
		क्रमागत ip_conntrack_info ctinfo;
		काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

		अगर (ct) अणु
			IP_VS_DBG_RL_PKT(10, AF_INET, pp, skb, ipvsh->off,
					 "ip_vs_nat_xmit(): "
					 "stopping DNAT to local address");
			जाओ tx_error;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* From world but DNAT to loopback address? */
	अगर (local && ipv4_is_loopback(cp->daddr.ip) && was_input) अणु
		IP_VS_DBG_RL_PKT(1, AF_INET, pp, skb, ipvsh->off,
				 "ip_vs_nat_xmit(): stopping DNAT to loopback "
				 "address");
		जाओ tx_error;
	पूर्ण

	/* copy-on-ग_लिखो the packet beक्रमe mangling it */
	अगर (skb_ensure_writable(skb, माप(काष्ठा iphdr)))
		जाओ tx_error;

	अगर (skb_cow(skb, rt->dst.dev->hard_header_len))
		जाओ tx_error;

	/* mangle the packet */
	अगर (pp->dnat_handler && !pp->dnat_handler(skb, pp, cp, ipvsh))
		जाओ tx_error;
	ip_hdr(skb)->daddr = cp->daddr.ip;
	ip_send_check(ip_hdr(skb));

	IP_VS_DBG_PKT(10, AF_INET, pp, skb, ipvsh->off, "After DNAT");

	/* FIXME: when application helper enlarges the packet and the length
	   is larger than the MTU of outgoing device, there will be still
	   MTU problem. */

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	rc = ip_vs_nat_send_or_cont(NFPROTO_IPV4, skb, cp, local);

	LeaveFunction(10);
	वापस rc;

  tx_error:
	kमुक्त_skb(skb);
	LeaveFunction(10);
	वापस NF_STOLEN;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
पूर्णांक
ip_vs_nat_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		  काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा rt6_info *rt;		/* Route to the other host */
	पूर्णांक local, rc;

	EnterFunction(10);

	/* check अगर it is a connection of no-client-port */
	अगर (unlikely(cp->flags & IP_VS_CONN_F_NO_CPORT && !ipvsh->fragoffs)) अणु
		__be16 _pt, *p;
		p = skb_header_poपूर्णांकer(skb, ipvsh->len, माप(_pt), &_pt);
		अगर (p == शून्य)
			जाओ tx_error;
		ip_vs_conn_fill_cport(cp, *p);
		IP_VS_DBG(10, "filled cport=%d\n", ntohs(*p));
	पूर्ण

	local = __ip_vs_get_out_rt_v6(cp->ipvs, cp->af, skb, cp->dest,
				      &cp->daddr.in6,
				      शून्य, ipvsh, 0,
				      IP_VS_RT_MODE_LOCAL |
				      IP_VS_RT_MODE_NON_LOCAL |
				      IP_VS_RT_MODE_RDR);
	अगर (local < 0)
		जाओ tx_error;
	rt = (काष्ठा rt6_info *) skb_dst(skb);
	/*
	 * Aव्योम duplicate tuple in reply direction क्रम NAT traffic
	 * to local address when connection is sync-ed
	 */
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (cp->flags & IP_VS_CONN_F_SYNC && local) अणु
		क्रमागत ip_conntrack_info ctinfo;
		काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

		अगर (ct) अणु
			IP_VS_DBG_RL_PKT(10, AF_INET6, pp, skb, ipvsh->off,
					 "ip_vs_nat_xmit_v6(): "
					 "stopping DNAT to local address");
			जाओ tx_error;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* From world but DNAT to loopback address? */
	अगर (local && skb->dev && !(skb->dev->flags & IFF_LOOPBACK) &&
	    ipv6_addr_type(&cp->daddr.in6) & IPV6_ADDR_LOOPBACK) अणु
		IP_VS_DBG_RL_PKT(1, AF_INET6, pp, skb, ipvsh->off,
				 "ip_vs_nat_xmit_v6(): "
				 "stopping DNAT to loopback address");
		जाओ tx_error;
	पूर्ण

	/* copy-on-ग_लिखो the packet beक्रमe mangling it */
	अगर (skb_ensure_writable(skb, माप(काष्ठा ipv6hdr)))
		जाओ tx_error;

	अगर (skb_cow(skb, rt->dst.dev->hard_header_len))
		जाओ tx_error;

	/* mangle the packet */
	अगर (pp->dnat_handler && !pp->dnat_handler(skb, pp, cp, ipvsh))
		जाओ tx_error;
	ipv6_hdr(skb)->daddr = cp->daddr.in6;

	IP_VS_DBG_PKT(10, AF_INET6, pp, skb, ipvsh->off, "After DNAT");

	/* FIXME: when application helper enlarges the packet and the length
	   is larger than the MTU of outgoing device, there will be still
	   MTU problem. */

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	rc = ip_vs_nat_send_or_cont(NFPROTO_IPV6, skb, cp, local);

	LeaveFunction(10);
	वापस rc;

tx_error:
	LeaveFunction(10);
	kमुक्त_skb(skb);
	वापस NF_STOLEN;
पूर्ण
#पूर्ण_अगर

/* When क्रमwarding a packet, we must ensure that we've got enough headroom
 * क्रम the encapsulation packet in the skb.  This also gives us an
 * opportunity to figure out what the payload_len, dsfield, ttl, and df
 * values should be, so that we won't need to look at the old ip header
 * again
 */
अटल काष्ठा sk_buff *
ip_vs_prepare_tunneled_skb(काष्ठा sk_buff *skb, पूर्णांक skb_af,
			   अचिन्हित पूर्णांक max_headroom, __u8 *next_protocol,
			   __u32 *payload_len, __u8 *dsfield, __u8 *ttl,
			   __be16 *df)
अणु
	काष्ठा sk_buff *new_skb = शून्य;
	काष्ठा iphdr *old_iph = शून्य;
	__u8 old_dsfield;
#अगर_घोषित CONFIG_IP_VS_IPV6
	काष्ठा ipv6hdr *old_ipv6h = शून्य;
#पूर्ण_अगर

	ip_vs_drop_early_demux_sk(skb);

	अगर (skb_headroom(skb) < max_headroom || skb_cloned(skb)) अणु
		new_skb = skb_पुनः_स्मृति_headroom(skb, max_headroom);
		अगर (!new_skb)
			जाओ error;
		अगर (skb->sk)
			skb_set_owner_w(new_skb, skb->sk);
		consume_skb(skb);
		skb = new_skb;
	पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
	अगर (skb_af == AF_INET6) अणु
		old_ipv6h = ipv6_hdr(skb);
		*next_protocol = IPPROTO_IPV6;
		अगर (payload_len)
			*payload_len =
				ntohs(old_ipv6h->payload_len) +
				माप(*old_ipv6h);
		old_dsfield = ipv6_get_dsfield(old_ipv6h);
		*ttl = old_ipv6h->hop_limit;
		अगर (df)
			*df = 0;
	पूर्ण अन्यथा
#पूर्ण_अगर
	अणु
		old_iph = ip_hdr(skb);
		/* Copy DF, reset fragment offset and MF */
		अगर (df)
			*df = (old_iph->frag_off & htons(IP_DF));
		*next_protocol = IPPROTO_IPIP;

		/* fix old IP header checksum */
		ip_send_check(old_iph);
		old_dsfield = ipv4_get_dsfield(old_iph);
		*ttl = old_iph->ttl;
		अगर (payload_len)
			*payload_len = ntohs(old_iph->tot_len);
	पूर्ण

	/* Implement full-functionality option क्रम ECN encapsulation */
	*dsfield = INET_ECN_encapsulate(old_dsfield, old_dsfield);

	वापस skb;
error:
	kमुक्त_skb(skb);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल अंतरभूत पूर्णांक __tun_gso_type_mask(पूर्णांक encaps_af, पूर्णांक orig_af)
अणु
	चयन (encaps_af) अणु
	हाल AF_INET:
		वापस SKB_GSO_IPXIP4;
	हाल AF_INET6:
		वापस SKB_GSO_IPXIP6;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
ipvs_gue_encap(काष्ठा net *net, काष्ठा sk_buff *skb,
	       काष्ठा ip_vs_conn *cp, __u8 *next_protocol)
अणु
	__be16 dport;
	__be16 sport = udp_flow_src_port(net, skb, 0, 0, false);
	काष्ठा udphdr  *udph;	/* Our new UDP header */
	काष्ठा guehdr  *gueh;	/* Our new GUE header */
	माप_प्रकार hdrlen, optlen = 0;
	व्योम *data;
	bool need_priv = false;

	अगर ((cp->dest->tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM) &&
	    skb->ip_summed == CHECKSUM_PARTIAL) अणु
		optlen += GUE_PLEN_REMCSUM + GUE_LEN_PRIV;
		need_priv = true;
	पूर्ण

	hdrlen = माप(काष्ठा guehdr) + optlen;

	skb_push(skb, hdrlen);

	gueh = (काष्ठा guehdr *)skb->data;

	gueh->control = 0;
	gueh->version = 0;
	gueh->hlen = optlen >> 2;
	gueh->flags = 0;
	gueh->proto_ctype = *next_protocol;

	data = &gueh[1];

	अगर (need_priv) अणु
		__be32 *flags = data;
		u16 csum_start = skb_checksum_start_offset(skb);
		__be16 *pd;

		gueh->flags |= GUE_FLAG_PRIV;
		*flags = 0;
		data += GUE_LEN_PRIV;

		अगर (csum_start < hdrlen)
			वापस -EINVAL;

		csum_start -= hdrlen;
		pd = data;
		pd[0] = htons(csum_start);
		pd[1] = htons(csum_start + skb->csum_offset);

		अगर (!skb_is_gso(skb)) अणु
			skb->ip_summed = CHECKSUM_NONE;
			skb->encapsulation = 0;
		पूर्ण

		*flags |= GUE_PFLAG_REMCSUM;
		data += GUE_PLEN_REMCSUM;
	पूर्ण

	skb_push(skb, माप(काष्ठा udphdr));
	skb_reset_transport_header(skb);

	udph = udp_hdr(skb);

	dport = cp->dest->tun_port;
	udph->dest = dport;
	udph->source = sport;
	udph->len = htons(skb->len);
	udph->check = 0;

	*next_protocol = IPPROTO_UDP;

	वापस 0;
पूर्ण

अटल व्योम
ipvs_gre_encap(काष्ठा net *net, काष्ठा sk_buff *skb,
	       काष्ठा ip_vs_conn *cp, __u8 *next_protocol)
अणु
	__be16 proto = *next_protocol == IPPROTO_IPIP ?
				htons(ETH_P_IP) : htons(ETH_P_IPV6);
	__be16 tflags = 0;
	माप_प्रकार hdrlen;

	अगर (cp->dest->tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM)
		tflags |= TUNNEL_CSUM;

	hdrlen = gre_calc_hlen(tflags);
	gre_build_header(skb, hdrlen, tflags, proto, 0, 0);

	*next_protocol = IPPROTO_GRE;
पूर्ण

/*
 *   IP Tunneling transmitter
 *
 *   This function encapsulates the packet in a new IP packet, its
 *   destination will be set to cp->daddr. Most code of this function
 *   is taken from ipip.c.
 *
 *   It is used in VS/TUN cluster. The load balancer selects a real
 *   server from a cluster based on a scheduling algorithm,
 *   encapsulates the request packet and क्रमwards it to the selected
 *   server. For example, all real servers are configured with
 *   "ifconfig tunl0 <Virtual IP Address> up". When the server receives
 *   the encapsulated packet, it will decapsulate the packet, processe
 *   the request and वापस the response packets directly to the client
 *   without passing the load balancer. This can greatly increase the
 *   scalability of भव server.
 *
 *   Used क्रम ANY protocol
 */
पूर्णांक
ip_vs_tunnel_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		  काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा netns_ipvs *ipvs = cp->ipvs;
	काष्ठा net *net = ipvs->net;
	काष्ठा rtable *rt;			/* Route to the other host */
	__be32 saddr;				/* Source क्रम tunnel */
	काष्ठा net_device *tdev;		/* Device to other host */
	__u8 next_protocol = 0;
	__u8 dsfield = 0;
	__u8 ttl = 0;
	__be16 df = 0;
	__be16 *dfp = शून्य;
	काष्ठा iphdr  *iph;			/* Our new IP header */
	अचिन्हित पूर्णांक max_headroom;		/* The extra header space needed */
	पूर्णांक ret, local;
	पूर्णांक tun_type, gso_type;
	पूर्णांक tun_flags;

	EnterFunction(10);

	local = __ip_vs_get_out_rt(ipvs, cp->af, skb, cp->dest, cp->daddr.ip,
				   IP_VS_RT_MODE_LOCAL |
				   IP_VS_RT_MODE_NON_LOCAL |
				   IP_VS_RT_MODE_CONNECT |
				   IP_VS_RT_MODE_TUNNEL, &saddr, ipvsh);
	अगर (local < 0)
		जाओ tx_error;
	अगर (local)
		वापस ip_vs_send_or_cont(NFPROTO_IPV4, skb, cp, 1);

	rt = skb_rtable(skb);
	tdev = rt->dst.dev;

	/*
	 * Okay, now see अगर we can stuff it in the buffer as-is.
	 */
	max_headroom = LL_RESERVED_SPACE(tdev) + माप(काष्ठा iphdr);

	tun_type = cp->dest->tun_type;
	tun_flags = cp->dest->tun_flags;

	अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		माप_प्रकार gue_hdrlen, gue_optlen = 0;

		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM) &&
		    skb->ip_summed == CHECKSUM_PARTIAL) अणु
			gue_optlen += GUE_PLEN_REMCSUM + GUE_LEN_PRIV;
		पूर्ण
		gue_hdrlen = माप(काष्ठा guehdr) + gue_optlen;

		max_headroom += माप(काष्ठा udphdr) + gue_hdrlen;
	पूर्ण अन्यथा अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) अणु
		माप_प्रकार gre_hdrlen;
		__be16 tflags = 0;

		अगर (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM)
			tflags |= TUNNEL_CSUM;
		gre_hdrlen = gre_calc_hlen(tflags);

		max_headroom += gre_hdrlen;
	पूर्ण

	/* We only care about the df field अगर sysctl_pmtu_disc(ipvs) is set */
	dfp = sysctl_pmtu_disc(ipvs) ? &df : शून्य;
	skb = ip_vs_prepare_tunneled_skb(skb, cp->af, max_headroom,
					 &next_protocol, शून्य, &dsfield,
					 &ttl, dfp);
	अगर (IS_ERR(skb))
		जाओ tx_error;

	gso_type = __tun_gso_type_mask(AF_INET, cp->af);
	अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM) ||
		    (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM))
			gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;
		अन्यथा
			gso_type |= SKB_GSO_UDP_TUNNEL;
		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM) &&
		    skb->ip_summed == CHECKSUM_PARTIAL) अणु
			gso_type |= SKB_GSO_TUNNEL_REMCSUM;
		पूर्ण
	पूर्ण अन्यथा अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) अणु
		अगर (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM)
			gso_type |= SKB_GSO_GRE_CSUM;
		अन्यथा
			gso_type |= SKB_GSO_GRE;
	पूर्ण

	अगर (iptunnel_handle_offloads(skb, gso_type))
		जाओ tx_error;

	skb->transport_header = skb->network_header;

	skb_set_inner_ipproto(skb, next_protocol);

	अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		bool check = false;

		अगर (ipvs_gue_encap(net, skb, cp, &next_protocol))
			जाओ tx_error;

		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM) ||
		    (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM))
			check = true;

		udp_set_csum(!check, skb, saddr, cp->daddr.ip, skb->len);
	पूर्ण अन्यथा अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE)
		ipvs_gre_encap(net, skb, cp, &next_protocol);

	skb_push(skb, माप(काष्ठा iphdr));
	skb_reset_network_header(skb);
	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));

	/*
	 *	Push करोwn and install the IPIP header.
	 */
	iph			=	ip_hdr(skb);
	iph->version		=	4;
	iph->ihl		=	माप(काष्ठा iphdr)>>2;
	iph->frag_off		=	df;
	iph->protocol		=	next_protocol;
	iph->tos		=	dsfield;
	iph->daddr		=	cp->daddr.ip;
	iph->saddr		=	saddr;
	iph->ttl		=	ttl;
	ip_select_ident(net, skb, शून्य);

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	ret = ip_vs_tunnel_xmit_prepare(skb, cp);
	अगर (ret == NF_ACCEPT)
		ip_local_out(net, skb->sk, skb);
	अन्यथा अगर (ret == NF_DROP)
		kमुक्त_skb(skb);

	LeaveFunction(10);

	वापस NF_STOLEN;

  tx_error:
	अगर (!IS_ERR(skb))
		kमुक्त_skb(skb);
	LeaveFunction(10);
	वापस NF_STOLEN;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
पूर्णांक
ip_vs_tunnel_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		     काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा netns_ipvs *ipvs = cp->ipvs;
	काष्ठा net *net = ipvs->net;
	काष्ठा rt6_info *rt;		/* Route to the other host */
	काष्ठा in6_addr saddr;		/* Source क्रम tunnel */
	काष्ठा net_device *tdev;	/* Device to other host */
	__u8 next_protocol = 0;
	__u32 payload_len = 0;
	__u8 dsfield = 0;
	__u8 ttl = 0;
	काष्ठा ipv6hdr  *iph;		/* Our new IP header */
	अचिन्हित पूर्णांक max_headroom;	/* The extra header space needed */
	पूर्णांक ret, local;
	पूर्णांक tun_type, gso_type;
	पूर्णांक tun_flags;

	EnterFunction(10);

	local = __ip_vs_get_out_rt_v6(ipvs, cp->af, skb, cp->dest,
				      &cp->daddr.in6,
				      &saddr, ipvsh, 1,
				      IP_VS_RT_MODE_LOCAL |
				      IP_VS_RT_MODE_NON_LOCAL |
				      IP_VS_RT_MODE_TUNNEL);
	अगर (local < 0)
		जाओ tx_error;
	अगर (local)
		वापस ip_vs_send_or_cont(NFPROTO_IPV6, skb, cp, 1);

	rt = (काष्ठा rt6_info *) skb_dst(skb);
	tdev = rt->dst.dev;

	/*
	 * Okay, now see अगर we can stuff it in the buffer as-is.
	 */
	max_headroom = LL_RESERVED_SPACE(tdev) + माप(काष्ठा ipv6hdr);

	tun_type = cp->dest->tun_type;
	tun_flags = cp->dest->tun_flags;

	अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		माप_प्रकार gue_hdrlen, gue_optlen = 0;

		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM) &&
		    skb->ip_summed == CHECKSUM_PARTIAL) अणु
			gue_optlen += GUE_PLEN_REMCSUM + GUE_LEN_PRIV;
		पूर्ण
		gue_hdrlen = माप(काष्ठा guehdr) + gue_optlen;

		max_headroom += माप(काष्ठा udphdr) + gue_hdrlen;
	पूर्ण अन्यथा अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) अणु
		माप_प्रकार gre_hdrlen;
		__be16 tflags = 0;

		अगर (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM)
			tflags |= TUNNEL_CSUM;
		gre_hdrlen = gre_calc_hlen(tflags);

		max_headroom += gre_hdrlen;
	पूर्ण

	skb = ip_vs_prepare_tunneled_skb(skb, cp->af, max_headroom,
					 &next_protocol, &payload_len,
					 &dsfield, &ttl, शून्य);
	अगर (IS_ERR(skb))
		जाओ tx_error;

	gso_type = __tun_gso_type_mask(AF_INET6, cp->af);
	अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM) ||
		    (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM))
			gso_type |= SKB_GSO_UDP_TUNNEL_CSUM;
		अन्यथा
			gso_type |= SKB_GSO_UDP_TUNNEL;
		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM) &&
		    skb->ip_summed == CHECKSUM_PARTIAL) अणु
			gso_type |= SKB_GSO_TUNNEL_REMCSUM;
		पूर्ण
	पूर्ण अन्यथा अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE) अणु
		अगर (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM)
			gso_type |= SKB_GSO_GRE_CSUM;
		अन्यथा
			gso_type |= SKB_GSO_GRE;
	पूर्ण

	अगर (iptunnel_handle_offloads(skb, gso_type))
		जाओ tx_error;

	skb->transport_header = skb->network_header;

	skb_set_inner_ipproto(skb, next_protocol);

	अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GUE) अणु
		bool check = false;

		अगर (ipvs_gue_encap(net, skb, cp, &next_protocol))
			जाओ tx_error;

		अगर ((tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_CSUM) ||
		    (tun_flags & IP_VS_TUNNEL_ENCAP_FLAG_REMCSUM))
			check = true;

		udp6_set_csum(!check, skb, &saddr, &cp->daddr.in6, skb->len);
	पूर्ण अन्यथा अगर (tun_type == IP_VS_CONN_F_TUNNEL_TYPE_GRE)
		ipvs_gre_encap(net, skb, cp, &next_protocol);

	skb_push(skb, माप(काष्ठा ipv6hdr));
	skb_reset_network_header(skb);
	स_रखो(&(IPCB(skb)->opt), 0, माप(IPCB(skb)->opt));

	/*
	 *	Push करोwn and install the IPIP header.
	 */
	iph			=	ipv6_hdr(skb);
	iph->version		=	6;
	iph->nexthdr		=	next_protocol;
	iph->payload_len	=	htons(payload_len);
	स_रखो(&iph->flow_lbl, 0, माप(iph->flow_lbl));
	ipv6_change_dsfield(iph, 0, dsfield);
	iph->daddr = cp->daddr.in6;
	iph->saddr = saddr;
	iph->hop_limit		=	ttl;

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	ret = ip_vs_tunnel_xmit_prepare(skb, cp);
	अगर (ret == NF_ACCEPT)
		ip6_local_out(net, skb->sk, skb);
	अन्यथा अगर (ret == NF_DROP)
		kमुक्त_skb(skb);

	LeaveFunction(10);

	वापस NF_STOLEN;

tx_error:
	अगर (!IS_ERR(skb))
		kमुक्त_skb(skb);
	LeaveFunction(10);
	वापस NF_STOLEN;
पूर्ण
#पूर्ण_अगर


/*
 *      Direct Routing transmitter
 *      Used क्रम ANY protocol
 */
पूर्णांक
ip_vs_dr_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
	      काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	पूर्णांक local;

	EnterFunction(10);

	local = __ip_vs_get_out_rt(cp->ipvs, cp->af, skb, cp->dest, cp->daddr.ip,
				   IP_VS_RT_MODE_LOCAL |
				   IP_VS_RT_MODE_NON_LOCAL |
				   IP_VS_RT_MODE_KNOWN_NH, शून्य, ipvsh);
	अगर (local < 0)
		जाओ tx_error;
	अगर (local)
		वापस ip_vs_send_or_cont(NFPROTO_IPV4, skb, cp, 1);

	ip_send_check(ip_hdr(skb));

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	ip_vs_send_or_cont(NFPROTO_IPV4, skb, cp, 0);

	LeaveFunction(10);
	वापस NF_STOLEN;

  tx_error:
	kमुक्त_skb(skb);
	LeaveFunction(10);
	वापस NF_STOLEN;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
पूर्णांक
ip_vs_dr_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		 काष्ठा ip_vs_protocol *pp, काष्ठा ip_vs_iphdr *ipvsh)
अणु
	पूर्णांक local;

	EnterFunction(10);

	local = __ip_vs_get_out_rt_v6(cp->ipvs, cp->af, skb, cp->dest,
				      &cp->daddr.in6,
				      शून्य, ipvsh, 0,
				      IP_VS_RT_MODE_LOCAL |
				      IP_VS_RT_MODE_NON_LOCAL |
				      IP_VS_RT_MODE_KNOWN_NH);
	अगर (local < 0)
		जाओ tx_error;
	अगर (local)
		वापस ip_vs_send_or_cont(NFPROTO_IPV6, skb, cp, 1);

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	ip_vs_send_or_cont(NFPROTO_IPV6, skb, cp, 0);

	LeaveFunction(10);
	वापस NF_STOLEN;

tx_error:
	kमुक्त_skb(skb);
	LeaveFunction(10);
	वापस NF_STOLEN;
पूर्ण
#पूर्ण_अगर


/*
 *	ICMP packet transmitter
 *	called by the ip_vs_in_icmp
 */
पूर्णांक
ip_vs_icmp_xmit(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		काष्ठा ip_vs_protocol *pp, पूर्णांक offset, अचिन्हित पूर्णांक hooknum,
		काष्ठा ip_vs_iphdr *iph)
अणु
	काष्ठा rtable	*rt;	/* Route to the other host */
	पूर्णांक rc;
	पूर्णांक local;
	पूर्णांक rt_mode, was_input;

	EnterFunction(10);

	/* The ICMP packet क्रम VS/TUN, VS/DR and LOCALNODE will be
	   क्रमwarded directly here, because there is no need to
	   translate address/port back */
	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ) अणु
		अगर (cp->packet_xmit)
			rc = cp->packet_xmit(skb, cp, pp, iph);
		अन्यथा
			rc = NF_ACCEPT;
		/* करो not touch skb anymore */
		atomic_inc(&cp->in_pkts);
		जाओ out;
	पूर्ण

	/*
	 * mangle and send the packet here (only क्रम VS/NAT)
	 */
	was_input = rt_is_input_route(skb_rtable(skb));

	/* LOCALNODE from FORWARD hook is not supported */
	rt_mode = (hooknum != NF_INET_FORWARD) ?
		  IP_VS_RT_MODE_LOCAL | IP_VS_RT_MODE_NON_LOCAL |
		  IP_VS_RT_MODE_RDR : IP_VS_RT_MODE_NON_LOCAL;
	local = __ip_vs_get_out_rt(cp->ipvs, cp->af, skb, cp->dest, cp->daddr.ip, rt_mode,
				   शून्य, iph);
	अगर (local < 0)
		जाओ tx_error;
	rt = skb_rtable(skb);

	/*
	 * Aव्योम duplicate tuple in reply direction क्रम NAT traffic
	 * to local address when connection is sync-ed
	 */
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (cp->flags & IP_VS_CONN_F_SYNC && local) अणु
		क्रमागत ip_conntrack_info ctinfo;
		काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

		अगर (ct) अणु
			IP_VS_DBG(10, "%s(): "
				  "stopping DNAT to local address %pI4\n",
				  __func__, &cp->daddr.ip);
			जाओ tx_error;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* From world but DNAT to loopback address? */
	अगर (local && ipv4_is_loopback(cp->daddr.ip) && was_input) अणु
		IP_VS_DBG(1, "%s(): "
			  "stopping DNAT to loopback %pI4\n",
			  __func__, &cp->daddr.ip);
		जाओ tx_error;
	पूर्ण

	/* copy-on-ग_लिखो the packet beक्रमe mangling it */
	अगर (skb_ensure_writable(skb, offset))
		जाओ tx_error;

	अगर (skb_cow(skb, rt->dst.dev->hard_header_len))
		जाओ tx_error;

	ip_vs_nat_icmp(skb, pp, cp, 0);

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	rc = ip_vs_nat_send_or_cont(NFPROTO_IPV4, skb, cp, local);
	जाओ out;

  tx_error:
	kमुक्त_skb(skb);
	rc = NF_STOLEN;
  out:
	LeaveFunction(10);
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_IP_VS_IPV6
पूर्णांक
ip_vs_icmp_xmit_v6(काष्ठा sk_buff *skb, काष्ठा ip_vs_conn *cp,
		काष्ठा ip_vs_protocol *pp, पूर्णांक offset, अचिन्हित पूर्णांक hooknum,
		काष्ठा ip_vs_iphdr *ipvsh)
अणु
	काष्ठा rt6_info	*rt;	/* Route to the other host */
	पूर्णांक rc;
	पूर्णांक local;
	पूर्णांक rt_mode;

	EnterFunction(10);

	/* The ICMP packet क्रम VS/TUN, VS/DR and LOCALNODE will be
	   क्रमwarded directly here, because there is no need to
	   translate address/port back */
	अगर (IP_VS_FWD_METHOD(cp) != IP_VS_CONN_F_MASQ) अणु
		अगर (cp->packet_xmit)
			rc = cp->packet_xmit(skb, cp, pp, ipvsh);
		अन्यथा
			rc = NF_ACCEPT;
		/* करो not touch skb anymore */
		atomic_inc(&cp->in_pkts);
		जाओ out;
	पूर्ण

	/*
	 * mangle and send the packet here (only क्रम VS/NAT)
	 */

	/* LOCALNODE from FORWARD hook is not supported */
	rt_mode = (hooknum != NF_INET_FORWARD) ?
		  IP_VS_RT_MODE_LOCAL | IP_VS_RT_MODE_NON_LOCAL |
		  IP_VS_RT_MODE_RDR : IP_VS_RT_MODE_NON_LOCAL;
	local = __ip_vs_get_out_rt_v6(cp->ipvs, cp->af, skb, cp->dest,
				      &cp->daddr.in6, शून्य, ipvsh, 0, rt_mode);
	अगर (local < 0)
		जाओ tx_error;
	rt = (काष्ठा rt6_info *) skb_dst(skb);
	/*
	 * Aव्योम duplicate tuple in reply direction क्रम NAT traffic
	 * to local address when connection is sync-ed
	 */
#अगर IS_ENABLED(CONFIG_NF_CONNTRACK)
	अगर (cp->flags & IP_VS_CONN_F_SYNC && local) अणु
		क्रमागत ip_conntrack_info ctinfo;
		काष्ठा nf_conn *ct = nf_ct_get(skb, &ctinfo);

		अगर (ct) अणु
			IP_VS_DBG(10, "%s(): "
				  "stopping DNAT to local address %pI6\n",
				  __func__, &cp->daddr.in6);
			जाओ tx_error;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* From world but DNAT to loopback address? */
	अगर (local && skb->dev && !(skb->dev->flags & IFF_LOOPBACK) &&
	    ipv6_addr_type(&cp->daddr.in6) & IPV6_ADDR_LOOPBACK) अणु
		IP_VS_DBG(1, "%s(): "
			  "stopping DNAT to loopback %pI6\n",
			  __func__, &cp->daddr.in6);
		जाओ tx_error;
	पूर्ण

	/* copy-on-ग_लिखो the packet beक्रमe mangling it */
	अगर (skb_ensure_writable(skb, offset))
		जाओ tx_error;

	अगर (skb_cow(skb, rt->dst.dev->hard_header_len))
		जाओ tx_error;

	ip_vs_nat_icmp_v6(skb, pp, cp, 0);

	/* Another hack: aव्योम icmp_send in ip_fragment */
	skb->ignore_df = 1;

	rc = ip_vs_nat_send_or_cont(NFPROTO_IPV6, skb, cp, local);
	जाओ out;

tx_error:
	kमुक्त_skb(skb);
	rc = NF_STOLEN;
out:
	LeaveFunction(10);
	वापस rc;
पूर्ण
#पूर्ण_अगर
