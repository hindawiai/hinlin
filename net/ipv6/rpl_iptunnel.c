<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Authors:
 * (C) 2020 Alexander Aring <alex.aring@gmail.com>
 */

#समावेश <linux/rpl_iptunnel.h>

#समावेश <net/dst_cache.h>
#समावेश <net/ip6_route.h>
#समावेश <net/lwtunnel.h>
#समावेश <net/ipv6.h>
#समावेश <net/rpl.h>

काष्ठा rpl_iptunnel_encap अणु
	काष्ठा ipv6_rpl_sr_hdr srh[0];
पूर्ण;

काष्ठा rpl_lwt अणु
	काष्ठा dst_cache cache;
	काष्ठा rpl_iptunnel_encap tuninfo;
पूर्ण;

अटल अंतरभूत काष्ठा rpl_lwt *rpl_lwt_lwtunnel(काष्ठा lwtunnel_state *lwt)
अणु
	वापस (काष्ठा rpl_lwt *)lwt->data;
पूर्ण

अटल अंतरभूत काष्ठा rpl_iptunnel_encap *
rpl_encap_lwtunnel(काष्ठा lwtunnel_state *lwt)
अणु
	वापस &rpl_lwt_lwtunnel(lwt)->tuninfo;
पूर्ण

अटल स्थिर काष्ठा nla_policy rpl_iptunnel_policy[RPL_IPTUNNEL_MAX + 1] = अणु
	[RPL_IPTUNNEL_SRH]	= अणु .type = NLA_BINARY पूर्ण,
पूर्ण;

अटल bool rpl_validate_srh(काष्ठा net *net, काष्ठा ipv6_rpl_sr_hdr *srh,
			     माप_प्रकार seglen)
अणु
	पूर्णांक err;

	अगर ((srh->hdrlen << 3) != seglen)
		वापस false;

	/* check at least one segment and seglen fit with segments_left */
	अगर (!srh->segments_left ||
	    (srh->segments_left * माप(काष्ठा in6_addr)) != seglen)
		वापस false;

	अगर (srh->cmpri || srh->cmpre)
		वापस false;

	err = ipv6_chk_rpl_srh_loop(net, srh->rpl_segaddr,
				    srh->segments_left);
	अगर (err)
		वापस false;

	अगर (ipv6_addr_type(&srh->rpl_segaddr[srh->segments_left - 1]) &
	    IPV6_ADDR_MULTICAST)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक rpl_build_state(काष्ठा net *net, काष्ठा nlattr *nla,
			   अचिन्हित पूर्णांक family, स्थिर व्योम *cfg,
			   काष्ठा lwtunnel_state **ts,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[RPL_IPTUNNEL_MAX + 1];
	काष्ठा lwtunnel_state *newts;
	काष्ठा ipv6_rpl_sr_hdr *srh;
	काष्ठा rpl_lwt *rlwt;
	पूर्णांक err, srh_len;

	अगर (family != AF_INET6)
		वापस -EINVAL;

	err = nla_parse_nested(tb, RPL_IPTUNNEL_MAX, nla,
			       rpl_iptunnel_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[RPL_IPTUNNEL_SRH])
		वापस -EINVAL;

	srh = nla_data(tb[RPL_IPTUNNEL_SRH]);
	srh_len = nla_len(tb[RPL_IPTUNNEL_SRH]);

	अगर (srh_len < माप(*srh))
		वापस -EINVAL;

	/* verअगरy that SRH is consistent */
	अगर (!rpl_validate_srh(net, srh, srh_len - माप(*srh)))
		वापस -EINVAL;

	newts = lwtunnel_state_alloc(srh_len + माप(*rlwt));
	अगर (!newts)
		वापस -ENOMEM;

	rlwt = rpl_lwt_lwtunnel(newts);

	err = dst_cache_init(&rlwt->cache, GFP_ATOMIC);
	अगर (err) अणु
		kमुक्त(newts);
		वापस err;
	पूर्ण

	स_नकल(&rlwt->tuninfo.srh, srh, srh_len);

	newts->type = LWTUNNEL_ENCAP_RPL;
	newts->flags |= LWTUNNEL_STATE_INPUT_REसूचीECT;
	newts->flags |= LWTUNNEL_STATE_OUTPUT_REसूचीECT;

	*ts = newts;

	वापस 0;
पूर्ण

अटल व्योम rpl_destroy_state(काष्ठा lwtunnel_state *lwt)
अणु
	dst_cache_destroy(&rpl_lwt_lwtunnel(lwt)->cache);
पूर्ण

अटल पूर्णांक rpl_करो_srh_अंतरभूत(काष्ठा sk_buff *skb, स्थिर काष्ठा rpl_lwt *rlwt,
			     स्थिर काष्ठा ipv6_rpl_sr_hdr *srh)
अणु
	काष्ठा ipv6_rpl_sr_hdr *isrh, *csrh;
	स्थिर काष्ठा ipv6hdr *oldhdr;
	काष्ठा ipv6hdr *hdr;
	अचिन्हित अक्षर *buf;
	माप_प्रकार hdrlen;
	पूर्णांक err;

	oldhdr = ipv6_hdr(skb);

	buf = kसुस्मृति(काष्ठा_size(srh, segments.addr, srh->segments_left), 2, GFP_ATOMIC);
	अगर (!buf)
		वापस -ENOMEM;

	isrh = (काष्ठा ipv6_rpl_sr_hdr *)buf;
	csrh = (काष्ठा ipv6_rpl_sr_hdr *)(buf + ((srh->hdrlen + 1) << 3));

	स_नकल(isrh, srh, माप(*isrh));
	स_नकल(isrh->rpl_segaddr, &srh->rpl_segaddr[1],
	       (srh->segments_left - 1) * 16);
	isrh->rpl_segaddr[srh->segments_left - 1] = oldhdr->daddr;

	ipv6_rpl_srh_compress(csrh, isrh, &srh->rpl_segaddr[0],
			      isrh->segments_left - 1);

	hdrlen = ((csrh->hdrlen + 1) << 3);

	err = skb_cow_head(skb, hdrlen + skb->mac_len);
	अगर (unlikely(err)) अणु
		kमुक्त(buf);
		वापस err;
	पूर्ण

	skb_pull(skb, माप(काष्ठा ipv6hdr));
	skb_postpull_rcsum(skb, skb_network_header(skb),
			   माप(काष्ठा ipv6hdr));

	skb_push(skb, माप(काष्ठा ipv6hdr) + hdrlen);
	skb_reset_network_header(skb);
	skb_mac_header_rebuild(skb);

	hdr = ipv6_hdr(skb);
	स_हटाओ(hdr, oldhdr, माप(*hdr));
	isrh = (व्योम *)hdr + माप(*hdr);
	स_नकल(isrh, csrh, hdrlen);

	isrh->nexthdr = hdr->nexthdr;
	hdr->nexthdr = NEXTHDR_ROUTING;
	hdr->daddr = srh->rpl_segaddr[0];

	ipv6_hdr(skb)->payload_len = htons(skb->len - माप(काष्ठा ipv6hdr));
	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));

	skb_postpush_rcsum(skb, hdr, माप(काष्ठा ipv6hdr) + hdrlen);

	kमुक्त(buf);

	वापस 0;
पूर्ण

अटल पूर्णांक rpl_करो_srh(काष्ठा sk_buff *skb, स्थिर काष्ठा rpl_lwt *rlwt)
अणु
	काष्ठा dst_entry *dst = skb_dst(skb);
	काष्ठा rpl_iptunnel_encap *tinfo;

	अगर (skb->protocol != htons(ETH_P_IPV6))
		वापस -EINVAL;

	tinfo = rpl_encap_lwtunnel(dst->lwtstate);

	वापस rpl_करो_srh_अंतरभूत(skb, rlwt, tinfo->srh);
पूर्ण

अटल पूर्णांक rpl_output(काष्ठा net *net, काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *orig_dst = skb_dst(skb);
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा rpl_lwt *rlwt;
	पूर्णांक err;

	rlwt = rpl_lwt_lwtunnel(orig_dst->lwtstate);

	err = rpl_करो_srh(skb, rlwt);
	अगर (unlikely(err))
		जाओ drop;

	preempt_disable();
	dst = dst_cache_get(&rlwt->cache);
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
		dst_cache_set_ip6(&rlwt->cache, dst, &fl6.saddr);
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

अटल पूर्णांक rpl_input(काष्ठा sk_buff *skb)
अणु
	काष्ठा dst_entry *orig_dst = skb_dst(skb);
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा rpl_lwt *rlwt;
	पूर्णांक err;

	rlwt = rpl_lwt_lwtunnel(orig_dst->lwtstate);

	err = rpl_करो_srh(skb, rlwt);
	अगर (unlikely(err)) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	preempt_disable();
	dst = dst_cache_get(&rlwt->cache);
	preempt_enable();

	skb_dst_drop(skb);

	अगर (!dst) अणु
		ip6_route_input(skb);
		dst = skb_dst(skb);
		अगर (!dst->error) अणु
			preempt_disable();
			dst_cache_set_ip6(&rlwt->cache, dst,
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

अटल पूर्णांक nla_put_rpl_srh(काष्ठा sk_buff *skb, पूर्णांक attrtype,
			   काष्ठा rpl_iptunnel_encap *tuninfo)
अणु
	काष्ठा rpl_iptunnel_encap *data;
	काष्ठा nlattr *nla;
	पूर्णांक len;

	len = RPL_IPTUNNEL_SRH_SIZE(tuninfo->srh);

	nla = nla_reserve(skb, attrtype, len);
	अगर (!nla)
		वापस -EMSGSIZE;

	data = nla_data(nla);
	स_नकल(data, tuninfo->srh, len);

	वापस 0;
पूर्ण

अटल पूर्णांक rpl_fill_encap_info(काष्ठा sk_buff *skb,
			       काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा rpl_iptunnel_encap *tuninfo = rpl_encap_lwtunnel(lwtstate);

	अगर (nla_put_rpl_srh(skb, RPL_IPTUNNEL_SRH, tuninfo))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक rpl_encap_nlsize(काष्ठा lwtunnel_state *lwtstate)
अणु
	काष्ठा rpl_iptunnel_encap *tuninfo = rpl_encap_lwtunnel(lwtstate);

	वापस nla_total_size(RPL_IPTUNNEL_SRH_SIZE(tuninfo->srh));
पूर्ण

अटल पूर्णांक rpl_encap_cmp(काष्ठा lwtunnel_state *a, काष्ठा lwtunnel_state *b)
अणु
	काष्ठा rpl_iptunnel_encap *a_hdr = rpl_encap_lwtunnel(a);
	काष्ठा rpl_iptunnel_encap *b_hdr = rpl_encap_lwtunnel(b);
	पूर्णांक len = RPL_IPTUNNEL_SRH_SIZE(a_hdr->srh);

	अगर (len != RPL_IPTUNNEL_SRH_SIZE(b_hdr->srh))
		वापस 1;

	वापस स_भेद(a_hdr, b_hdr, len);
पूर्ण

अटल स्थिर काष्ठा lwtunnel_encap_ops rpl_ops = अणु
	.build_state	= rpl_build_state,
	.destroy_state	= rpl_destroy_state,
	.output		= rpl_output,
	.input		= rpl_input,
	.fill_encap	= rpl_fill_encap_info,
	.get_encap_size	= rpl_encap_nlsize,
	.cmp_encap	= rpl_encap_cmp,
	.owner		= THIS_MODULE,
पूर्ण;

पूर्णांक __init rpl_init(व्योम)
अणु
	पूर्णांक err;

	err = lwtunnel_encap_add_ops(&rpl_ops, LWTUNNEL_ENCAP_RPL);
	अगर (err)
		जाओ out;

	pr_info("RPL Segment Routing with IPv6\n");

	वापस 0;

out:
	वापस err;
पूर्ण

व्योम rpl_निकास(व्योम)
अणु
	lwtunnel_encap_del_ops(&rpl_ops, LWTUNNEL_ENCAP_RPL);
पूर्ण
