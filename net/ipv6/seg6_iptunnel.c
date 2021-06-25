<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  SR-IPv6 implementation
 *
 *  Author:
 *  David Lebrun <david.lebrun@uclouvain.be>
 */

#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/net.h>
#समावेश <linux/module.h>
#समावेश <net/ip.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/netevent.h>
#समावेश <net/netns/generic.h>
#समावेश <net/ip6_fib.h>
#समावेश <net/route.h>
#समावेश <net/seg6.h>
#समावेश <linux/seg6.h>
#समावेश <linux/seg6_iptunnel.h>
#समावेश <net/addrconf.h>
#समावेश <net/ip6_route.h>
#समावेश <net/dst_cache.h>
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
#समावेश <net/seg6_hmac.h>
#पूर्ण_अगर

अटल माप_प्रकार seg6_lwt_headroom(काष्ठा seg6_iptunnel_encap *tuninfo)
अणु
	पूर्णांक head = 0;

	चयन (tuninfo->mode) अणु
	हाल SEG6_IPTUN_MODE_INLINE:
		अवरोध;
	हाल SEG6_IPTUN_MODE_ENCAP:
		head = माप(काष्ठा ipv6hdr);
		अवरोध;
	हाल SEG6_IPTUN_MODE_L2ENCAP:
		वापस 0;
	पूर्ण

	वापस ((tuninfo->srh->hdrlen + 1) << 3) + head;
पूर्ण

काष्ठा seg6_lwt अणु
	काष्ठा dst_cache cache;
	काष्ठा seg6_iptunnel_encap tuninfo[];
पूर्ण;

अटल अंतरभूत काष्ठा seg6_lwt *seg6_lwt_lwtunnel(काष्ठा lwtunnel_state *lwt)
अणु
	वापस (काष्ठा seg6_lwt *)lwt->data;
पूर्ण

अटल अंतरभूत काष्ठा seg6_iptunnel_encap *
seg6_encap_lwtunnel(काष्ठा lwtunnel_state *lwt)
अणु
	वापस seg6_lwt_lwtunnel(lwt)->tuninfo;
पूर्ण

अटल स्थिर काष्ठा nla_policy seg6_iptunnel_policy[SEG6_IPTUNNEL_MAX + 1] = अणु
	[SEG6_IPTUNNEL_SRH]	= अणु .type = NLA_BINARY पूर्ण,
पूर्ण;

अटल पूर्णांक nla_put_srh(काष्ठा sk_buff *skb, पूर्णांक attrtype,
		       काष्ठा seg6_iptunnel_encap *tuninfo)
अणु
	काष्ठा seg6_iptunnel_encap *data;
	काष्ठा nlattr *nla;
	पूर्णांक len;

	len = SEG6_IPTUN_ENCAP_SIZE(tuninfo);

	nla = nla_reserve(skb, attrtype, len);
	अगर (!nla)
		वापस -EMSGSIZE;

	data = nla_data(nla);
	स_नकल(data, tuninfo, len);

	वापस 0;
पूर्ण

अटल व्योम set_tun_src(काष्ठा net *net, काष्ठा net_device *dev,
			काष्ठा in6_addr *daddr, काष्ठा in6_addr *saddr)
अणु
	काष्ठा seg6_pernet_data *sdata = seg6_pernet(net);
	काष्ठा in6_addr *tun_src;

	rcu_पढ़ो_lock();

	tun_src = rcu_dereference(sdata->tun_src);

	अगर (!ipv6_addr_any(tun_src)) अणु
		स_नकल(saddr, tun_src, माप(काष्ठा in6_addr));
	पूर्ण अन्यथा अणु
		ipv6_dev_get_saddr(net, dev, daddr, IPV6_PREFER_SRC_PUBLIC,
				   saddr);
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

/* Compute flowlabel क्रम outer IPv6 header */
अटल __be32 seg6_make_flowlabel(काष्ठा net *net, काष्ठा sk_buff *skb,
				  काष्ठा ipv6hdr *inner_hdr)
अणु
	पूर्णांक करो_flowlabel = net->ipv6.sysctl.seg6_flowlabel;
	__be32 flowlabel = 0;
	u32 hash;

	अगर (करो_flowlabel > 0) अणु
		hash = skb_get_hash(skb);
		hash = rol32(hash, 16);
		flowlabel = (__क्रमce __be32)hash & IPV6_FLOWLABEL_MASK;
	पूर्ण अन्यथा अगर (!करो_flowlabel && skb->protocol == htons(ETH_P_IPV6)) अणु
		flowlabel = ip6_flowlabel(inner_hdr);
	पूर्ण
	वापस flowlabel;
पूर्ण

/* encapsulate an IPv6 packet within an outer IPv6 header with a given SRH */
पूर्णांक seg6_करो_srh_encap(काष्ठा sk_buff *skb, काष्ठा ipv6_sr_hdr *osrh, पूर्णांक proto)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा net *net = dev_net(dst->dev);
	काष्ठा ipv6hdr *hdr, *inner_hdr;
	काष्ठा ipv6_sr_hdr *isrh;
	पूर्णांक hdrlen, tot_len, err;
	__be32 flowlabel;

	hdrlen = (osrh->hdrlen + 1) << 3;
	tot_len = hdrlen + माप(*hdr);

	err = skb_cow_head(skb, tot_len + skb->mac_len);
	अगर (unlikely(err))
		वापस err;

	inner_hdr = ipv6_hdr(skb);
	flowlabel = seg6_make_flowlabel(net, skb, inner_hdr);

	skb_push(skb, tot_len);
	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);
	hdr = ipv6_hdr(skb);

	/* inherit tc, flowlabel and hlim
	 * hlim will be decremented in ip6_क्रमward() afterwards and
	 * decapsulation will overग_लिखो inner hlim with outer hlim
	 */

	अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		ip6_flow_hdr(hdr, ip6_tclass(ip6_flowinfo(inner_hdr)),
			     flowlabel);
		hdr->hop_limit = inner_hdr->hop_limit;
	पूर्ण अन्यथा अणु
		ip6_flow_hdr(hdr, 0, flowlabel);
		hdr->hop_limit = ip6_dst_hoplimit(skb_dst(skb));

		स_रखो(IP6CB(skb), 0, माप(*IP6CB(skb)));
	पूर्ण

	hdr->nexthdr = NEXTHDR_ROUTING;

	isrh = (व्योम *)hdr + माप(*hdr);
	स_नकल(isrh, osrh, hdrlen);

	isrh->nexthdr = proto;

	hdr->daddr = isrh->segments[isrh->first_segment];
	set_tun_src(net, dst->dev, &hdr->daddr, &hdr->saddr);

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	अगर (sr_has_hmac(isrh)) अणु
		err = seg6_push_hmac(net, &hdr->saddr, isrh);
		अगर (unlikely(err))
			वापस err;
	पूर्ण
#पूर्ण_अगर

	skb_postpush_rcsum(skb, hdr, tot_len);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(seg6_करो_srh_encap);

/* insert an SRH within an IPv6 packet, just after the IPv6 header */
पूर्णांक seg6_करो_srh_अंतरभूत(काष्ठा sk_buff *skb, काष्ठा ipv6_sr_hdr *osrh)
अणु
	काष्ठा ipv6hdr *hdr, *oldhdr;
	काष्ठा ipv6_sr_hdr *isrh;
	पूर्णांक hdrlen, err;

	hdrlen = (osrh->hdrlen + 1) << 3;

	err = skb_cow_head(skb, hdrlen + skb->mac_len);
	अगर (unlikely(err))
		वापस err;

	oldhdr = ipv6_hdr(skb);

	skb_pull(skb, माप(काष्ठा ipv6hdr));
	skb_postpull_rcsum(skb, skb_network_header(skb),
			   माप(काष्ठा ipv6hdr));

	skb_push(skb, माप(काष्ठा ipv6hdr) + hdrlen);
	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);

	hdr = ipv6_hdr(skb);

	स_हटाओ(hdr, oldhdr, माप(*hdr));

	isrh = (व्योम *)hdr + माप(*hdr);
	स_नकल(isrh, osrh, hdrlen);

	isrh->nexthdr = hdr->nexthdr;
	hdr->nexthdr = NEXTHDR_ROUTING;

	isrh->segments[0] = hdr->daddr;
	hdr->daddr = isrh->segments[isrh->first_segment];

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	अगर (sr_has_hmac(isrh)) अणु
		काष्ठा net *net = dev_net(skb_dst(skb)->dev);

		err = seg6_push_hmac(net, &hdr->saddr, isrh);
		अगर (unlikely(err))
			वापस err;
	पूर्ण
#पूर्ण_अगर

	skb_postpush_rcsum(skb, hdr, माप(काष्ठा ipv6hdr) + hdrlen);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(seg6_करो_srh_अंतरभूत);

अटल पूर्णांक seg6_करो_srh(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा seg6_iptunnel_encap *tinfo;
	पूर्णांक proto, err = 0;

	tinfo = seg6_encap_lwtunnel(dst->lwtstate);

	चयन (tinfo->mode) अणु
	हाल SEG6_IPTUN_MODE_INLINE:
		अगर (skb->protocol != htons(ETH_P_IPV6))
			वापस -EINVAL;

		err = seg6_करो_srh_अंतरभूत(skb, tinfo->srh);
		अगर (err)
			वापस err;
		अवरोध;
	हाल SEG6_IPTUN_MODE_ENCAP:
		err = iptunnel_handle_offloads(skb, SKB_GSO_IPXIP6);
		अगर (err)
			वापस err;

		अगर (skb->protocol == htons(ETH_P_IPV6))
			proto = IPPROTO_IPV6;
		अन्यथा अगर (skb->protocol == htons(ETH_P_IP))
			proto = IPPROTO_IPIP;
		अन्यथा
			वापस -EINVAL;

		err = seg6_करो_srh_encap(skb, tinfo->srh, proto);
		अगर (err)
			वापस err;

		skb_set_inner_transport_header(skb, skb_transport_offset(skb));
		skb_set_inner_protocol(skb, skb->protocol);
		skb->protocol = htons(ETH_P_IPV6);
		अवरोध;
	हाल SEG6_IPTUN_MODE_L2ENCAP:
		अगर (!skb_mac_header_was_set(skb))
			वापस -EINVAL;

		अगर (pskb_expand_head(skb, skb->mac_len, 0, GFP_ATOMIC) < 0)
			वापस -ENOMEM;

		skb_mac_header_rebuild(skb);
		skb_push(skb, skb->mac_len);

		err = seg6_करो_srh_encap(skb, tinfo->srh, IPPROTO_ETHERNET);
		अगर (err)
			वापस err;

		skb->protocol = htons(ETH_P_IPV6);
		अवरोध;
	पूर्ण

	ipv6_hdr(skb)->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));
	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	वापस 0;
पूर्ण

अटल पूर्णांक seg6_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *orig_dst = skb_dst(skb);
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा seg6_lwt *slwt;
	पूर्णांक err;

	err = seg6_करो_srh(skb);
	अगर (unlikely(err)) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	slwt = seg6_lwt_lwtunnel(orig_dst->lwtstate);

	preempt_disable();
	dst = dst_cache_get(&slwt->cache);
	preempt_enable();

	skb_dst_drop(skb);

	अगर (!dst) अणु
		ip6_route_input(skb);
		dst = skb_dst(skb);
		अगर (!dst->error) अणु
			preempt_disable();
			dst_cache_set_ip6(&slwt->cache, dst,
					  &ipv6_hdr(skb)->saddr);
			preempt_enable();
		पूर्ण
	पूर्ण अन्यथा अणु
		skb_dst_set(skb, dst);
	पूर्ण

	err = skb_cow_head(skb, LL_RESERVED_SPACE(dst->dev));
	अगर (unlikely(err))
		वापस err;

	वापस dst_input(skb);
पूर्ण

अटल पूर्णांक seg6_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *orig_dst = skb_dst(skb);
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा seg6_lwt *slwt;
	पूर्णांक err = -EINVAL;

	err = seg6_करो_srh(skb);
	अगर (unlikely(err))
		जाओ drop;

	slwt = seg6_lwt_lwtunnel(orig_dst->lwtstate);

	preempt_disable();
	dst = dst_cache_get(&slwt->cache);
	preempt_enable();

	अगर (unlikely(!dst)) अणु
		काष्ठा ipv6hdr *hdr = ipv6_hdr(skb);
		काष्ठा flowi6 fl6;

		स_रखो(&fl6, 0, माप(fl6));
		fl6.daddr = hdr->daddr;
		fl6.saddr = hdr->saddr;
		fl6.flowlabel = ip6_flowinfo(hdr);
		fl6.flowi6_mark = skb->mark;
		fl6.flowi6_proto = hdr->nexthdr;

		dst = ip6_route_output(net, शून्य, &fl6);
		अगर (dst->error) अणु
			err = dst->error;
			dst_release(dst);
			जाओ drop;
		पूर्ण

		preempt_disable();
		dst_cache_set_ip6(&slwt->cache, dst, &fl6.saddr);
		preempt_enable();
	पूर्ण

	skb_dst_drop(skb);
	skb_dst_set(skb, dst);

	err = skb_cow_head(skb, LL_RESERVED_SPACE(dst->dev));
	अगर (unlikely(err))
		जाओ drop;

	वापस dst_output(net, sk, skb);
drop:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल पूर्णांक seg6_build_state(काष्ठा net *net, काष्ठा nlattr *nla,
			    अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			    काष्ठा lwtunnel_state **ts,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[SEG6_IPTUNNEL_MAX + 1];
	काष्ठा seg6_iptunnel_encap *tuninfo;
	काष्ठा lwtunnel_state *newts;
	पूर्णांक tuninfo_len, min_size;
	काष्ठा seg6_lwt *slwt;
	पूर्णांक err;

	अगर (family != AF_INET && family != AF_INET6)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, SEG6_IPTUNNEL_MAX, nla,
					  seg6_iptunnel_policy, extack);

	अगर (err < 0)
		वापस err;

	अगर (!tb[SEG6_IPTUNNEL_SRH])
		वापस -EINVAL;

	tuninfo = nla_data(tb[SEG6_IPTUNNEL_SRH]);
	tuninfo_len = nla_len(tb[SEG6_IPTUNNEL_SRH]);

	/* tuninfo must contain at least the iptunnel encap काष्ठाure,
	 * the SRH and one segment
	 */
	min_size = माप(*tuninfo) + माप(काष्ठा ipv6_sr_hdr) +
		   माप(काष्ठा in6_addr);
	अगर (tuninfo_len < min_size)
		वापस -EINVAL;

	चयन (tuninfo->mode) अणु
	हाल SEG6_IPTUN_MODE_INLINE:
		अगर (family != AF_INET6)
			वापस -EINVAL;

		अवरोध;
	हाल SEG6_IPTUN_MODE_ENCAP:
		अवरोध;
	हाल SEG6_IPTUN_MODE_L2ENCAP:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* verअगरy that SRH is consistent */
	अगर (!seg6_validate_srh(tuninfo->srh, tuninfo_len - माप(*tuninfo), false))
		वापस -EINVAL;

	newts = lwtunnel_state_alloc(tuninfo_len + माप(*slwt));
	अगर (!newts)
		वापस -ENOMEM;

	slwt = seg6_lwt_lwtunnel(newts);

	err = dst_cache_init(&slwt->cache, GFP_ATOMIC);
	अगर (err) अणु
		kमुक्त(newts);
		वापस err;
	पूर्ण

	स_नकल(&slwt->tuninfo, tuninfo, tuninfo_len);

	newts->type = LWTUNNEL_ENCAP_SEG6;
	newts->flags |= LWTUNNEL_STATE_INPUT_REसूचीECT;

	अगर (tuninfo->mode != SEG6_IPTUN_MODE_L2ENCAP)
		newts->flags |= LWTUNNEL_STATE_OUTPUT_REसूचीECT;

	newts->headroom = seg6_lwt_headroom(tuninfo);

	*ts = newts;

	वापस 0;
पूर्ण

अटल व्योम seg6_destroy_state(काष्ठा lwtunnel_state *lwt)
अणु
	dst_cache_destroy(&seg6_lwt_lwtunnel(lwt)->cache);
पूर्ण

अटल पूर्णांक seg6_fill_encap_info(काष्ठा sk_buff *skb,
				काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा seg6_iptunnel_encap *tuninfo = seg6_encap_lwtunnel(lwtstate);

	अगर (nla_put_srh(skb, SEG6_IPTUNNEL_SRH, tuninfo))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक seg6_encap_nlsize(काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा seg6_iptunnel_encap *tuninfo = seg6_encap_lwtunnel(lwtstate);

	वापस nla_total_size(SEG6_IPTUN_ENCAP_SIZE(tuninfo));
पूर्ण

अटल पूर्णांक seg6_encap_cmp(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b)
अणु
	काष्ठा seg6_iptunnel_encap *a_hdr = seg6_encap_lwtunnel(a);
	काष्ठा seg6_iptunnel_encap *b_hdr = seg6_encap_lwtunnel(b);
	पूर्णांक len = SEG6_IPTUN_ENCAP_SIZE(a_hdr);

	अगर (len != SEG6_IPTUN_ENCAP_SIZE(b_hdr))
		वापस 1;

	वापस स_भेद(a_hdr, b_hdr, len);
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops seg6_iptun_ops = अणु
	.build_state = seg6_build_state,
	.destroy_state = seg6_destroy_state,
	.output = seg6_output,
	.input = seg6_input,
	.fill_encap = seg6_fill_encap_info,
	.get_encap_size = seg6_encap_nlsize,
	.cmp_encap = seg6_encap_cmp,
	.owner = THIS_MODULE,
पूर्ण;

पूर्णांक __init seg6_iptunnel_init(व्योम)
अणु
	वापस lwtunnel_encap_add_ops(&seg6_iptun_ops, LWTUNNEL_ENCAP_SEG6);
पूर्ण

व्योम seg6_iptunnel_निकास(व्योम)
अणु
	lwtunnel_encap_del_ops(&seg6_iptun_ops, LWTUNNEL_ENCAP_SEG6);
पूर्ण
