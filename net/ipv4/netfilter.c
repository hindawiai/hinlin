<शैली गुरु>
/*
 * IPv4 specअगरic functions of netfilter core
 *
 * Rusty Russell (C) 2000 -- This code is GPL.
 * Patrick McHardy (C) 2006-2012
 */
#समावेश <linux/kernel.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv4.h>
#समावेश <linux/ip.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>
#समावेश <net/route.h>
#समावेश <net/xfrm.h>
#समावेश <net/ip.h>
#समावेश <net/netfilter/nf_queue.h>

/* route_me_harder function, used by iptable_nat, iptable_mangle + ip_queue */
पूर्णांक ip_route_me_harder(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb, अचिन्हित पूर्णांक addr_type)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा rtable *rt;
	काष्ठा flowi4 fl4 = अणुपूर्ण;
	__be32 saddr = iph->saddr;
	__u8 flags;
	काष्ठा net_device *dev = skb_dst(skb)->dev;
	काष्ठा flow_keys flkeys;
	अचिन्हित पूर्णांक hh_len;

	sk = sk_to_full_sk(sk);
	flags = sk ? inet_sk_flowi_flags(sk) : 0;

	अगर (addr_type == RTN_UNSPEC)
		addr_type = inet_addr_type_dev_table(net, dev, saddr);
	अगर (addr_type == RTN_LOCAL || addr_type == RTN_UNICAST)
		flags |= FLOWI_FLAG_ANYSRC;
	अन्यथा
		saddr = 0;

	/* some non-standard hacks like ipt_REJECT.c:send_reset() can cause
	 * packets with क्रमeign saddr to appear on the NF_INET_LOCAL_OUT hook.
	 */
	fl4.daddr = iph->daddr;
	fl4.saddr = saddr;
	fl4.flowi4_tos = RT_TOS(iph->tos);
	fl4.flowi4_oअगर = sk ? sk->sk_bound_dev_अगर : 0;
	अगर (!fl4.flowi4_oअगर)
		fl4.flowi4_oअगर = l3mdev_master_अगरindex(dev);
	fl4.flowi4_mark = skb->mark;
	fl4.flowi4_flags = flags;
	fib4_rules_early_flow_dissect(net, skb, &fl4, &flkeys);
	rt = ip_route_output_key(net, &fl4);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);

	/* Drop old route. */
	skb_dst_drop(skb);
	skb_dst_set(skb, &rt->dst);

	अगर (skb_dst(skb)->error)
		वापस skb_dst(skb)->error;

#अगर_घोषित CONFIG_XFRM
	अगर (!(IPCB(skb)->flags & IPSKB_XFRM_TRANSFORMED) &&
	    xfrm_decode_session(skb, flowi4_to_flowi(&fl4), AF_INET) == 0) अणु
		काष्ठा dst_entry *dst = skb_dst(skb);
		skb_dst_set(skb, शून्य);
		dst = xfrm_lookup(net, dst, flowi4_to_flowi(&fl4), sk, 0);
		अगर (IS_ERR(dst))
			वापस PTR_ERR(dst);
		skb_dst_set(skb, dst);
	पूर्ण
#पूर्ण_अगर

	/* Change in oअगर may mean change in hh_len. */
	hh_len = skb_dst(skb)->dev->hard_header_len;
	अगर (skb_headroom(skb) < hh_len &&
	    pskb_expand_head(skb, HH_DATA_ALIGN(hh_len - skb_headroom(skb)),
				0, GFP_ATOMIC))
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ip_route_me_harder);

पूर्णांक nf_ip_route(काष्ठा net *net, काष्ठा dst_entry **dst, काष्ठा flowi *fl,
		bool strict __always_unused)
अणु
	काष्ठा rtable *rt = ip_route_output_key(net, &fl->u.ip4);
	अगर (IS_ERR(rt))
		वापस PTR_ERR(rt);
	*dst = &rt->dst;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nf_ip_route);
