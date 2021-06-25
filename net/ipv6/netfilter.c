<शैली गुरु>
/*
 * IPv6 specअगरic functions of netfilter core
 *
 * Rusty Russell (C) 2000 -- This code is GPL.
 * Patrick McHardy (C) 2006-2012
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <linux/export.h>
#समावेश <net/addrconf.h>
#समावेश <net/dst.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/xfrm.h>
#समावेश <net/netfilter/nf_queue.h>
#समावेश <net/netfilter/nf_conntrack_bridge.h>
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#समावेश "../bridge/br_private.h"

पूर्णांक ip6_route_me_harder(काष्ठा net *net, काष्ठा sock *sk_partial, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा sock *sk = sk_to_full_sk(sk_partial);
	काष्ठा flow_keys flkeys;
	अचिन्हित पूर्णांक hh_len;
	काष्ठा dst_entry *dst;
	पूर्णांक strict = (ipv6_addr_type(&iph->daddr) &
		      (IPV6_ADDR_MULTICAST | IPV6_ADDR_LINKLOCAL));
	काष्ठा flowi6 fl6 = अणु
		.flowi6_oअगर = sk && sk->sk_bound_dev_अगर ? sk->sk_bound_dev_अगर :
			strict ? skb_dst(skb)->dev->अगरindex : 0,
		.flowi6_mark = skb->mark,
		.flowi6_uid = sock_net_uid(net, sk),
		.daddr = iph->daddr,
		.saddr = iph->saddr,
	पूर्ण;
	पूर्णांक err;

	fib6_rules_early_flow_dissect(net, skb, &fl6, &flkeys);
	dst = ip6_route_output(net, sk, &fl6);
	err = dst->error;
	अगर (err) अणु
		IP6_INC_STATS(net, ip6_dst_idev(dst), IPSTATS_MIB_OUTNOROUTES);
		net_dbg_ratelimited("ip6_route_me_harder: No more route\n");
		dst_release(dst);
		वापस err;
	पूर्ण

	/* Drop old route. */
	skb_dst_drop(skb);

	skb_dst_set(skb, dst);

#अगर_घोषित CONFIG_XFRM
	अगर (!(IP6CB(skb)->flags & IP6SKB_XFRM_TRANSFORMED) &&
	    xfrm_decode_session(skb, flowi6_to_flowi(&fl6), AF_INET6) == 0) अणु
		skb_dst_set(skb, शून्य);
		dst = xfrm_lookup(net, dst, flowi6_to_flowi(&fl6), sk, 0);
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
EXPORT_SYMBOL(ip6_route_me_harder);

अटल पूर्णांक nf_ip6_reroute(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा nf_queue_entry *entry)
अणु
	काष्ठा ip6_rt_info *rt_info = nf_queue_entry_reroute(entry);

	अगर (entry->state.hook == NF_INET_LOCAL_OUT) अणु
		स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
		अगर (!ipv6_addr_equal(&iph->daddr, &rt_info->daddr) ||
		    !ipv6_addr_equal(&iph->saddr, &rt_info->saddr) ||
		    skb->mark != rt_info->mark)
			वापस ip6_route_me_harder(entry->state.net, entry->state.sk, skb);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __nf_ip6_route(काष्ठा net *net, काष्ठा dst_entry **dst,
		   काष्ठा flowi *fl, bool strict)
अणु
	अटल स्थिर काष्ठा ipv6_pinfo fake_pinfo;
	अटल स्थिर काष्ठा inet_sock fake_sk = अणु
		/* makes ip6_route_output set RT6_LOOKUP_F_IFACE: */
		.sk.sk_bound_dev_अगर = 1,
		.pinet6 = (काष्ठा ipv6_pinfo *) &fake_pinfo,
	पूर्ण;
	स्थिर व्योम *sk = strict ? &fake_sk : शून्य;
	काष्ठा dst_entry *result;
	पूर्णांक err;

	result = ip6_route_output(net, sk, &fl->u.ip6);
	err = result->error;
	अगर (err)
		dst_release(result);
	अन्यथा
		*dst = result;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(__nf_ip6_route);

पूर्णांक br_ip6_fragment(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb,
		    काष्ठा nf_bridge_frag_data *data,
		    पूर्णांक (*output)(काष्ठा net *, काष्ठा sock *sk,
				  स्थिर काष्ठा nf_bridge_frag_data *data,
				  काष्ठा sk_buff *))
अणु
	पूर्णांक frag_max_size = BR_INPUT_SKB_CB(skb)->frag_max_size;
	kसमय_प्रकार tstamp = skb->tstamp;
	काष्ठा ip6_frag_state state;
	u8 *prevhdr, nexthdr = 0;
	अचिन्हित पूर्णांक mtu, hlen;
	पूर्णांक hroom, err = 0;
	__be32 frag_id;

	err = ip6_find_1stfragopt(skb, &prevhdr);
	अगर (err < 0)
		जाओ blackhole;
	hlen = err;
	nexthdr = *prevhdr;

	mtu = skb->dev->mtu;
	अगर (frag_max_size > mtu ||
	    frag_max_size < IPV6_MIN_MTU)
		जाओ blackhole;

	mtu = frag_max_size;
	अगर (mtu < hlen + माप(काष्ठा frag_hdr) + 8)
		जाओ blackhole;
	mtu -= hlen + माप(काष्ठा frag_hdr);

	frag_id = ipv6_select_ident(net, &ipv6_hdr(skb)->daddr,
				    &ipv6_hdr(skb)->saddr);

	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    (err = skb_checksum_help(skb)))
		जाओ blackhole;

	hroom = LL_RESERVED_SPACE(skb->dev);
	अगर (skb_has_frag_list(skb)) अणु
		अचिन्हित पूर्णांक first_len = skb_pagelen(skb);
		काष्ठा ip6_fraglist_iter iter;
		काष्ठा sk_buff *frag2;

		अगर (first_len - hlen > mtu ||
		    skb_headroom(skb) < (hroom + माप(काष्ठा frag_hdr)))
			जाओ blackhole;

		अगर (skb_cloned(skb))
			जाओ slow_path;

		skb_walk_frags(skb, frag2) अणु
			अगर (frag2->len > mtu ||
			    skb_headroom(frag2) < (hlen + hroom + माप(काष्ठा frag_hdr)))
				जाओ blackhole;

			/* Partially cloned skb? */
			अगर (skb_shared(frag2))
				जाओ slow_path;
		पूर्ण

		err = ip6_fraglist_init(skb, hlen, prevhdr, nexthdr, frag_id,
					&iter);
		अगर (err < 0)
			जाओ blackhole;

		क्रम (;;) अणु
			/* Prepare header of the next frame,
			 * beक्रमe previous one went करोwn.
			 */
			अगर (iter.frag)
				ip6_fraglist_prepare(skb, &iter);

			skb->tstamp = tstamp;
			err = output(net, sk, data, skb);
			अगर (err || !iter.frag)
				अवरोध;

			skb = ip6_fraglist_next(&iter);
		पूर्ण

		kमुक्त(iter.पंचांगp_hdr);
		अगर (!err)
			वापस 0;

		kमुक्त_skb_list(iter.frag);
		वापस err;
	पूर्ण
slow_path:
	/* This is a linearized skbuff, the original geometry is lost क्रम us.
	 * This may also be a clone skbuff, we could preserve the geometry क्रम
	 * the copies but probably not worth the efक्रमt.
	 */
	ip6_frag_init(skb, hlen, mtu, skb->dev->needed_tailroom,
		      LL_RESERVED_SPACE(skb->dev), prevhdr, nexthdr, frag_id,
		      &state);

	जबतक (state.left > 0) अणु
		काष्ठा sk_buff *skb2;

		skb2 = ip6_frag_next(skb, &state);
		अगर (IS_ERR(skb2)) अणु
			err = PTR_ERR(skb2);
			जाओ blackhole;
		पूर्ण

		skb2->tstamp = tstamp;
		err = output(net, sk, data, skb2);
		अगर (err)
			जाओ blackhole;
	पूर्ण
	consume_skb(skb);
	वापस err;

blackhole:
	kमुक्त_skb(skb);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(br_ip6_fragment);

अटल स्थिर काष्ठा nf_ipv6_ops ipv6ops = अणु
#अगर IS_MODULE(CONFIG_IPV6)
	.chk_addr		= ipv6_chk_addr,
	.route_me_harder	= ip6_route_me_harder,
	.dev_get_saddr		= ipv6_dev_get_saddr,
	.route			= __nf_ip6_route,
#अगर IS_ENABLED(CONFIG_SYN_COOKIES)
	.cookie_init_sequence	= __cookie_v6_init_sequence,
	.cookie_v6_check	= __cookie_v6_check,
#पूर्ण_अगर
#पूर्ण_अगर
	.route_input		= ip6_route_input,
	.fragment		= ip6_fragment,
	.reroute		= nf_ip6_reroute,
#अगर IS_MODULE(CONFIG_IPV6)
	.br_fragment		= br_ip6_fragment,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init ipv6_netfilter_init(व्योम)
अणु
	RCU_INIT_POINTER(nf_ipv6_ops, &ipv6ops);
	वापस 0;
पूर्ण

/* This can be called from inet6_init() on errors, so it cannot
 * be marked __निकास. -DaveM
 */
व्योम ipv6_netfilter_fini(व्योम)
अणु
	RCU_INIT_POINTER(nf_ipv6_ops, शून्य);
पूर्ण
