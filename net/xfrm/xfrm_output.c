<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * xfrm_output.c - Common IPsec encapsulation code.
 *
 * Copyright (c) 2007 Herbert Xu <herbert@gonकरोr.apana.org.au>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <net/dst.h>
#समावेश <net/icmp.h>
#समावेश <net/inet_ecn.h>
#समावेश <net/xfrm.h>

#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ip6_route.h>
#समावेश <net/ipv6_stubs.h>
#पूर्ण_अगर

#समावेश "xfrm_inout.h"

अटल पूर्णांक xfrm_output2(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb);
अटल पूर्णांक xfrm_inner_extract_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb);

अटल पूर्णांक xfrm_skb_check_space(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	पूर्णांक nhead = dst->header_len + LL_RESERVED_SPACE(dst->dev)
		- skb_headroom(skb);
	पूर्णांक ntail = dst->dev->needed_tailroom - skb_tailroom(skb);

	अगर (nhead <= 0) अणु
		अगर (ntail <= 0)
			वापस 0;
		nhead = 0;
	पूर्ण अन्यथा अगर (ntail < 0)
		ntail = 0;

	वापस pskb_expand_head(skb, nhead, ntail, GFP_ATOMIC);
पूर्ण

/* Children define the path of the packet through the
 * Linux networking.  Thus, destinations are stackable.
 */

अटल काष्ठा dst_entry *skb_dst_pop(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *child = dst_clone(xfrm_dst_child(skb_dst(skb)));

	skb_dst_drop(skb);
	वापस child;
पूर्ण

/* Add encapsulation header.
 *
 * The IP header will be moved क्रमward to make space क्रम the encapsulation
 * header.
 */
अटल पूर्णांक xfrm4_transport_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph = ip_hdr(skb);
	पूर्णांक ihl = iph->ihl * 4;

	skb_set_inner_transport_header(skb, skb_transport_offset(skb));

	skb_set_network_header(skb, -x->props.header_len);
	skb->mac_header = skb->network_header +
			  दुरत्व(काष्ठा iphdr, protocol);
	skb->transport_header = skb->network_header + ihl;
	__skb_pull(skb, ihl);
	स_हटाओ(skb_network_header(skb), iph, ihl);
	वापस 0;
पूर्ण

/* Add encapsulation header.
 *
 * The IP header and mutable extension headers will be moved क्रमward to make
 * space क्रम the encapsulation header.
 */
अटल पूर्णांक xfrm6_transport_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6hdr *iph;
	u8 *prevhdr;
	पूर्णांक hdr_len;

	iph = ipv6_hdr(skb);
	skb_set_inner_transport_header(skb, skb_transport_offset(skb));

	hdr_len = x->type->hdr_offset(x, skb, &prevhdr);
	अगर (hdr_len < 0)
		वापस hdr_len;
	skb_set_mac_header(skb,
			   (prevhdr - x->props.header_len) - skb->data);
	skb_set_network_header(skb, -x->props.header_len);
	skb->transport_header = skb->network_header + hdr_len;
	__skb_pull(skb, hdr_len);
	स_हटाओ(ipv6_hdr(skb), iph, hdr_len);
	वापस 0;
#अन्यथा
	WARN_ON_ONCE(1);
	वापस -EAFNOSUPPORT;
#पूर्ण_अगर
पूर्ण

/* Add route optimization header space.
 *
 * The IP header and mutable extension headers will be moved क्रमward to make
 * space क्रम the route optimization header.
 */
अटल पूर्णांक xfrm6_ro_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	काष्ठा ipv6hdr *iph;
	u8 *prevhdr;
	पूर्णांक hdr_len;

	iph = ipv6_hdr(skb);

	hdr_len = x->type->hdr_offset(x, skb, &prevhdr);
	अगर (hdr_len < 0)
		वापस hdr_len;
	skb_set_mac_header(skb,
			   (prevhdr - x->props.header_len) - skb->data);
	skb_set_network_header(skb, -x->props.header_len);
	skb->transport_header = skb->network_header + hdr_len;
	__skb_pull(skb, hdr_len);
	स_हटाओ(ipv6_hdr(skb), iph, hdr_len);

	x->lastused = kसमय_get_real_seconds();

	वापस 0;
#अन्यथा
	WARN_ON_ONCE(1);
	वापस -EAFNOSUPPORT;
#पूर्ण_अगर
पूर्ण

/* Add encapsulation header.
 *
 * The top IP header will be स्थिरructed per draft-nikander-esp-beet-mode-06.txt.
 */
अटल पूर्णांक xfrm4_beet_encap_add(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip_beet_phdr *ph;
	काष्ठा iphdr *top_iph;
	पूर्णांक hdrlen, optlen;

	hdrlen = 0;
	optlen = XFRM_MODE_SKB_CB(skb)->optlen;
	अगर (unlikely(optlen))
		hdrlen += IPV4_BEET_PHMAXLEN - (optlen & 4);

	skb_set_network_header(skb, -x->props.header_len - hdrlen +
			       (XFRM_MODE_SKB_CB(skb)->ihl - माप(*top_iph)));
	अगर (x->sel.family != AF_INET6)
		skb->network_header += IPV4_BEET_PHMAXLEN;
	skb->mac_header = skb->network_header +
			  दुरत्व(काष्ठा iphdr, protocol);
	skb->transport_header = skb->network_header + माप(*top_iph);

	xfrm4_beet_make_header(skb);

	ph = __skb_pull(skb, XFRM_MODE_SKB_CB(skb)->ihl - hdrlen);

	top_iph = ip_hdr(skb);

	अगर (unlikely(optlen)) अणु
		अगर (WARN_ON(optlen < 0))
			वापस -EINVAL;

		ph->padlen = 4 - (optlen & 4);
		ph->hdrlen = optlen / 8;
		ph->nexthdr = top_iph->protocol;
		अगर (ph->padlen)
			स_रखो(ph + 1, IPOPT_NOP, ph->padlen);

		top_iph->protocol = IPPROTO_BEETPH;
		top_iph->ihl = माप(काष्ठा iphdr) / 4;
	पूर्ण

	top_iph->saddr = x->props.saddr.a4;
	top_iph->daddr = x->id.daddr.a4;

	वापस 0;
पूर्ण

/* Add encapsulation header.
 *
 * The top IP header will be स्थिरructed per RFC 2401.
 */
अटल पूर्णांक xfrm4_tunnel_encap_add(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा iphdr *top_iph;
	पूर्णांक flags;

	skb_set_inner_network_header(skb, skb_network_offset(skb));
	skb_set_inner_transport_header(skb, skb_transport_offset(skb));

	skb_set_network_header(skb, -x->props.header_len);
	skb->mac_header = skb->network_header +
			  दुरत्व(काष्ठा iphdr, protocol);
	skb->transport_header = skb->network_header + माप(*top_iph);
	top_iph = ip_hdr(skb);

	top_iph->ihl = 5;
	top_iph->version = 4;

	top_iph->protocol = xfrm_af2proto(skb_dst(skb)->ops->family);

	/* DS disclosing depends on XFRM_SA_XFLAG_DONT_ENCAP_DSCP */
	अगर (x->props.extra_flags & XFRM_SA_XFLAG_DONT_ENCAP_DSCP)
		top_iph->tos = 0;
	अन्यथा
		top_iph->tos = XFRM_MODE_SKB_CB(skb)->tos;
	top_iph->tos = INET_ECN_encapsulate(top_iph->tos,
					    XFRM_MODE_SKB_CB(skb)->tos);

	flags = x->props.flags;
	अगर (flags & XFRM_STATE_NOECN)
		IP_ECN_clear(top_iph);

	top_iph->frag_off = (flags & XFRM_STATE_NOPMTUDISC) ?
		0 : (XFRM_MODE_SKB_CB(skb)->frag_off & htons(IP_DF));

	top_iph->ttl = ip4_dst_hoplimit(xfrm_dst_child(dst));

	top_iph->saddr = x->props.saddr.a4;
	top_iph->daddr = x->id.daddr.a4;
	ip_select_ident(dev_net(dst->dev), skb, शून्य);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक xfrm6_tunnel_encap_add(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा ipv6hdr *top_iph;
	पूर्णांक dsfield;

	skb_set_inner_network_header(skb, skb_network_offset(skb));
	skb_set_inner_transport_header(skb, skb_transport_offset(skb));

	skb_set_network_header(skb, -x->props.header_len);
	skb->mac_header = skb->network_header +
			  दुरत्व(काष्ठा ipv6hdr, nexthdr);
	skb->transport_header = skb->network_header + माप(*top_iph);
	top_iph = ipv6_hdr(skb);

	top_iph->version = 6;

	स_नकल(top_iph->flow_lbl, XFRM_MODE_SKB_CB(skb)->flow_lbl,
	       माप(top_iph->flow_lbl));
	top_iph->nexthdr = xfrm_af2proto(skb_dst(skb)->ops->family);

	अगर (x->props.extra_flags & XFRM_SA_XFLAG_DONT_ENCAP_DSCP)
		dsfield = 0;
	अन्यथा
		dsfield = XFRM_MODE_SKB_CB(skb)->tos;
	dsfield = INET_ECN_encapsulate(dsfield, XFRM_MODE_SKB_CB(skb)->tos);
	अगर (x->props.flags & XFRM_STATE_NOECN)
		dsfield &= ~INET_ECN_MASK;
	ipv6_change_dsfield(top_iph, 0, dsfield);
	top_iph->hop_limit = ip6_dst_hoplimit(xfrm_dst_child(dst));
	top_iph->saddr = *(काष्ठा in6_addr *)&x->props.saddr;
	top_iph->daddr = *(काष्ठा in6_addr *)&x->id.daddr;
	वापस 0;
पूर्ण

अटल पूर्णांक xfrm6_beet_encap_add(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *top_iph;
	काष्ठा ip_beet_phdr *ph;
	पूर्णांक optlen, hdr_len;

	hdr_len = 0;
	optlen = XFRM_MODE_SKB_CB(skb)->optlen;
	अगर (unlikely(optlen))
		hdr_len += IPV4_BEET_PHMAXLEN - (optlen & 4);

	skb_set_network_header(skb, -x->props.header_len - hdr_len);
	अगर (x->sel.family != AF_INET6)
		skb->network_header += IPV4_BEET_PHMAXLEN;
	skb->mac_header = skb->network_header +
			  दुरत्व(काष्ठा ipv6hdr, nexthdr);
	skb->transport_header = skb->network_header + माप(*top_iph);
	ph = __skb_pull(skb, XFRM_MODE_SKB_CB(skb)->ihl - hdr_len);

	xfrm6_beet_make_header(skb);

	top_iph = ipv6_hdr(skb);
	अगर (unlikely(optlen)) अणु
		अगर (WARN_ON(optlen < 0))
			वापस -EINVAL;

		ph->padlen = 4 - (optlen & 4);
		ph->hdrlen = optlen / 8;
		ph->nexthdr = top_iph->nexthdr;
		अगर (ph->padlen)
			स_रखो(ph + 1, IPOPT_NOP, ph->padlen);

		top_iph->nexthdr = IPPROTO_BEETPH;
	पूर्ण

	top_iph->saddr = *(काष्ठा in6_addr *)&x->props.saddr;
	top_iph->daddr = *(काष्ठा in6_addr *)&x->id.daddr;
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* Add encapsulation header.
 *
 * On निकास, the transport header will be set to the start of the
 * encapsulation header to be filled in by x->type->output and the mac
 * header will be set to the nextheader (protocol क्रम IPv4) field of the
 * extension header directly preceding the encapsulation header, or in
 * its असलence, that of the top IP header.
 * The value of the network header will always poपूर्णांक to the top IP header
 * जबतक skb->data will poपूर्णांक to the payload.
 */
अटल पूर्णांक xfrm4_prepare_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = xfrm_inner_extract_output(x, skb);
	अगर (err)
		वापस err;

	IPCB(skb)->flags |= IPSKB_XFRM_TUNNEL_SIZE;
	skb->protocol = htons(ETH_P_IP);

	चयन (x->outer_mode.encap) अणु
	हाल XFRM_MODE_BEET:
		वापस xfrm4_beet_encap_add(x, skb);
	हाल XFRM_MODE_TUNNEL:
		वापस xfrm4_tunnel_encap_add(x, skb);
	पूर्ण

	WARN_ON_ONCE(1);
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक xfrm6_prepare_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	पूर्णांक err;

	err = xfrm_inner_extract_output(x, skb);
	अगर (err)
		वापस err;

	skb->ignore_df = 1;
	skb->protocol = htons(ETH_P_IPV6);

	चयन (x->outer_mode.encap) अणु
	हाल XFRM_MODE_BEET:
		वापस xfrm6_beet_encap_add(x, skb);
	हाल XFRM_MODE_TUNNEL:
		वापस xfrm6_tunnel_encap_add(x, skb);
	शेष:
		WARN_ON_ONCE(1);
		वापस -EOPNOTSUPP;
	पूर्ण
#पूर्ण_अगर
	WARN_ON_ONCE(1);
	वापस -EAFNOSUPPORT;
पूर्ण

अटल पूर्णांक xfrm_outer_mode_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	चयन (x->outer_mode.encap) अणु
	हाल XFRM_MODE_BEET:
	हाल XFRM_MODE_TUNNEL:
		अगर (x->outer_mode.family == AF_INET)
			वापस xfrm4_prepare_output(x, skb);
		अगर (x->outer_mode.family == AF_INET6)
			वापस xfrm6_prepare_output(x, skb);
		अवरोध;
	हाल XFRM_MODE_TRANSPORT:
		अगर (x->outer_mode.family == AF_INET)
			वापस xfrm4_transport_output(x, skb);
		अगर (x->outer_mode.family == AF_INET6)
			वापस xfrm6_transport_output(x, skb);
		अवरोध;
	हाल XFRM_MODE_ROUTEOPTIMIZATION:
		अगर (x->outer_mode.family == AF_INET6)
			वापस xfrm6_ro_output(x, skb);
		WARN_ON_ONCE(1);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

#अगर IS_ENABLED(CONFIG_NET_PKTGEN)
पूर्णांक pktgen_xfrm_outer_mode_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	वापस xfrm_outer_mode_output(x, skb);
पूर्ण
EXPORT_SYMBOL_GPL(pktgen_xfrm_outer_mode_output);
#पूर्ण_अगर

अटल पूर्णांक xfrm_output_one(काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा xfrm_state *x = dst->xfrm;
	काष्ठा net *net = xs_net(x);

	अगर (err <= 0)
		जाओ resume;

	करो अणु
		err = xfrm_skb_check_space(skb);
		अगर (err) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			जाओ error_nolock;
		पूर्ण

		skb->mark = xfrm_smark_get(skb->mark, x);

		err = xfrm_outer_mode_output(x, skb);
		अगर (err) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEMODEERROR);
			जाओ error_nolock;
		पूर्ण

		spin_lock_bh(&x->lock);

		अगर (unlikely(x->km.state != XFRM_STATE_VALID)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEINVALID);
			err = -EINVAL;
			जाओ error;
		पूर्ण

		err = xfrm_state_check_expire(x);
		अगर (err) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEEXPIRED);
			जाओ error;
		पूर्ण

		err = x->repl->overflow(x, skb);
		अगर (err) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATESEQERROR);
			जाओ error;
		पूर्ण

		x->curlft.bytes += skb->len;
		x->curlft.packets++;

		spin_unlock_bh(&x->lock);

		skb_dst_क्रमce(skb);
		अगर (!skb_dst(skb)) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			err = -EHOSTUNREACH;
			जाओ error_nolock;
		पूर्ण

		अगर (xfrm_offload(skb)) अणु
			x->type_offload->encap(x, skb);
		पूर्ण अन्यथा अणु
			/* Inner headers are invalid now. */
			skb->encapsulation = 0;

			err = x->type->output(x, skb);
			अगर (err == -EINPROGRESS)
				जाओ out;
		पूर्ण

resume:
		अगर (err) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTSTATEPROTOERROR);
			जाओ error_nolock;
		पूर्ण

		dst = skb_dst_pop(skb);
		अगर (!dst) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			err = -EHOSTUNREACH;
			जाओ error_nolock;
		पूर्ण
		skb_dst_set(skb, dst);
		x = dst->xfrm;
	पूर्ण जबतक (x && !(x->outer_mode.flags & XFRM_MODE_FLAG_TUNNEL));

	वापस 0;

error:
	spin_unlock_bh(&x->lock);
error_nolock:
	kमुक्त_skb(skb);
out:
	वापस err;
पूर्ण

पूर्णांक xfrm_output_resume(काष्ठा sock *sk, काष्ठा sk_buff *skb, पूर्णांक err)
अणु
	काष्ठा net *net = xs_net(skb_dst(skb)->xfrm);

	जबतक (likely((err = xfrm_output_one(skb, err)) == 0)) अणु
		nf_reset_ct(skb);

		err = skb_dst(skb)->ops->local_out(net, sk, skb);
		अगर (unlikely(err != 1))
			जाओ out;

		अगर (!skb_dst(skb)->xfrm)
			वापस dst_output(net, sk, skb);

		err = nf_hook(skb_dst(skb)->ops->family,
			      NF_INET_POST_ROUTING, net, sk, skb,
			      शून्य, skb_dst(skb)->dev, xfrm_output2);
		अगर (unlikely(err != 1))
			जाओ out;
	पूर्ण

	अगर (err == -EINPROGRESS)
		err = 0;

out:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_output_resume);

अटल पूर्णांक xfrm_output2(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	वापस xfrm_output_resume(sk, skb, 1);
पूर्ण

अटल पूर्णांक xfrm_output_gso(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *segs, *nskb;

	BUILD_BUG_ON(माप(*IPCB(skb)) > SKB_GSO_CB_OFFSET);
	BUILD_BUG_ON(माप(*IP6CB(skb)) > SKB_GSO_CB_OFFSET);
	segs = skb_gso_segment(skb, 0);
	kमुक्त_skb(skb);
	अगर (IS_ERR(segs))
		वापस PTR_ERR(segs);
	अगर (segs == शून्य)
		वापस -EINVAL;

	skb_list_walk_safe(segs, segs, nskb) अणु
		पूर्णांक err;

		skb_mark_not_on_list(segs);
		err = xfrm_output2(net, sk, segs);

		अगर (unlikely(err)) अणु
			kमुक्त_skb_list(nskb);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक xfrm_output(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा net *net = dev_net(skb_dst(skb)->dev);
	काष्ठा xfrm_state *x = skb_dst(skb)->xfrm;
	पूर्णांक err;

	चयन (x->outer_mode.family) अणु
	हाल AF_INET:
		स_रखो(IPCB(skb), 0, माप(*IPCB(skb)));
		IPCB(skb)->flags |= IPSKB_XFRM_TRANSFORMED;
		अवरोध;
	हाल AF_INET6:
		स_रखो(IP6CB(skb), 0, माप(*IP6CB(skb)));

		IP6CB(skb)->flags |= IP6SKB_XFRM_TRANSFORMED;
		अवरोध;
	पूर्ण

	secpath_reset(skb);

	अगर (xfrm_dev_offload_ok(skb, x)) अणु
		काष्ठा sec_path *sp;

		sp = secpath_set(skb);
		अगर (!sp) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
		skb->encapsulation = 1;

		sp->olen++;
		sp->xvec[sp->len++] = x;
		xfrm_state_hold(x);

		अगर (skb_is_gso(skb)) अणु
			अगर (skb->inner_protocol)
				वापस xfrm_output_gso(net, sk, skb);

			skb_shinfo(skb)->gso_type |= SKB_GSO_ESP;
			जाओ out;
		पूर्ण

		अगर (x->xso.dev && x->xso.dev->features & NETIF_F_HW_ESP_TX_CSUM)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (skb_is_gso(skb))
			वापस xfrm_output_gso(net, sk, skb);
	पूर्ण

	अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		err = skb_checksum_help(skb);
		अगर (err) अणु
			XFRM_INC_STATS(net, LINUX_MIB_XFRMOUTERROR);
			kमुक्त_skb(skb);
			वापस err;
		पूर्ण
	पूर्ण

out:
	वापस xfrm_output2(net, sk, skb);
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_output);

अटल पूर्णांक xfrm4_tunnel_check_size(काष्ठा sk_buff *skb)
अणु
	पूर्णांक mtu, ret = 0;

	अगर (IPCB(skb)->flags & IPSKB_XFRM_TUNNEL_SIZE)
		जाओ out;

	अगर (!(ip_hdr(skb)->frag_off & htons(IP_DF)) || skb->ignore_df)
		जाओ out;

	mtu = dst_mtu(skb_dst(skb));
	अगर ((!skb_is_gso(skb) && skb->len > mtu) ||
	    (skb_is_gso(skb) &&
	     !skb_gso_validate_network_len(skb, ip_skb_dst_mtu(skb->sk, skb)))) अणु
		skb->protocol = htons(ETH_P_IP);

		अगर (skb->sk)
			xfrm_local_error(skb, mtu);
		अन्यथा
			icmp_send(skb, ICMP_DEST_UNREACH,
				  ICMP_FRAG_NEEDED, htonl(mtu));
		ret = -EMSGSIZE;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक xfrm4_extract_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	अगर (x->outer_mode.encap == XFRM_MODE_BEET &&
	    ip_is_fragment(ip_hdr(skb))) अणु
		net_warn_ratelimited("BEET mode doesn't support inner IPv4 fragments\n");
		वापस -EAFNOSUPPORT;
	पूर्ण

	err = xfrm4_tunnel_check_size(skb);
	अगर (err)
		वापस err;

	XFRM_MODE_SKB_CB(skb)->protocol = ip_hdr(skb)->protocol;

	xfrm4_extract_header(skb);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल पूर्णांक xfrm6_tunnel_check_size(काष्ठा sk_buff *skb)
अणु
	पूर्णांक mtu, ret = 0;
	काष्ठा dst_entry *dst = skb_dst(skb);

	अगर (skb->ignore_df)
		जाओ out;

	mtu = dst_mtu(dst);
	अगर (mtu < IPV6_MIN_MTU)
		mtu = IPV6_MIN_MTU;

	अगर ((!skb_is_gso(skb) && skb->len > mtu) ||
	    (skb_is_gso(skb) &&
	     !skb_gso_validate_network_len(skb, ip6_skb_dst_mtu(skb)))) अणु
		skb->dev = dst->dev;
		skb->protocol = htons(ETH_P_IPV6);

		अगर (xfrm6_local_करोntfrag(skb->sk))
			ipv6_stub->xfrm6_local_rxpmtu(skb, mtu);
		अन्यथा अगर (skb->sk)
			xfrm_local_error(skb, mtu);
		अन्यथा
			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		ret = -EMSGSIZE;
	पूर्ण
out:
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक xfrm6_extract_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
#अगर IS_ENABLED(CONFIG_IPV6)
	अचिन्हित पूर्णांक ptr = 0;
	पूर्णांक err;

	अगर (x->outer_mode.encap == XFRM_MODE_BEET &&
	    ipv6_find_hdr(skb, &ptr, NEXTHDR_FRAGMENT, शून्य, शून्य) >= 0) अणु
		net_warn_ratelimited("BEET mode doesn't support inner IPv6 fragments\n");
		वापस -EAFNOSUPPORT;
	पूर्ण

	err = xfrm6_tunnel_check_size(skb);
	अगर (err)
		वापस err;

	XFRM_MODE_SKB_CB(skb)->protocol = ipv6_hdr(skb)->nexthdr;

	xfrm6_extract_header(skb);
	वापस 0;
#अन्यथा
	WARN_ON_ONCE(1);
	वापस -EAFNOSUPPORT;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक xfrm_inner_extract_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा xfrm_mode *inner_mode;

	अगर (x->sel.family == AF_UNSPEC)
		inner_mode = xfrm_ip2inner_mode(x,
				xfrm_af2proto(skb_dst(skb)->ops->family));
	अन्यथा
		inner_mode = &x->inner_mode;

	अगर (inner_mode == शून्य)
		वापस -EAFNOSUPPORT;

	चयन (inner_mode->family) अणु
	हाल AF_INET:
		वापस xfrm4_extract_output(x, skb);
	हाल AF_INET6:
		वापस xfrm6_extract_output(x, skb);
	पूर्ण

	वापस -EAFNOSUPPORT;
पूर्ण

व्योम xfrm_local_error(काष्ठा sk_buff *skb, पूर्णांक mtu)
अणु
	अचिन्हित पूर्णांक proto;
	काष्ठा xfrm_state_afinfo *afinfo;

	अगर (skb->protocol == htons(ETH_P_IP))
		proto = AF_INET;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6) &&
		 skb->sk->sk_family == AF_INET6)
		proto = AF_INET6;
	अन्यथा
		वापस;

	afinfo = xfrm_state_get_afinfo(proto);
	अगर (afinfo) अणु
		afinfo->local_error(skb, mtu);
		rcu_पढ़ो_unlock();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(xfrm_local_error);
