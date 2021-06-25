<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C)2003-2006 Helsinki University of Technology
 * Copyright (C)2003-2006 USAGI/WIDE Project
 */
/*
 * Authors:
 *	Noriaki TAKAMIYA @USAGI
 *	Masahide NAKAMURA @USAGI
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/समय.स>
#समावेश <linux/ipv6.h>
#समावेश <linux/icmpv6.h>
#समावेश <net/sock.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip6_checksum.h>
#समावेश <net/rawv6.h>
#समावेश <net/xfrm.h>
#समावेश <net/mip6.h>

अटल अंतरभूत अचिन्हित पूर्णांक calc_padlen(अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक n)
अणु
	वापस (n - len + 16) & 0x7;
पूर्ण

अटल अंतरभूत व्योम *mip6_padn(__u8 *data, __u8 padlen)
अणु
	अगर (!data)
		वापस शून्य;
	अगर (padlen == 1) अणु
		data[0] = IPV6_TLV_PAD1;
	पूर्ण अन्यथा अगर (padlen > 1) अणु
		data[0] = IPV6_TLV_PADN;
		data[1] = padlen - 2;
		अगर (padlen > 2)
			स_रखो(data+2, 0, data[1]);
	पूर्ण
	वापस data + padlen;
पूर्ण

अटल अंतरभूत व्योम mip6_param_prob(काष्ठा sk_buff *skb, u8 code, पूर्णांक pos)
अणु
	icmpv6_send(skb, ICMPV6_PARAMPROB, code, pos);
पूर्ण

अटल पूर्णांक mip6_mh_len(पूर्णांक type)
अणु
	पूर्णांक len = 0;

	चयन (type) अणु
	हाल IP6_MH_TYPE_BRR:
		len = 0;
		अवरोध;
	हाल IP6_MH_TYPE_HOTI:
	हाल IP6_MH_TYPE_COTI:
	हाल IP6_MH_TYPE_BU:
	हाल IP6_MH_TYPE_BACK:
		len = 1;
		अवरोध;
	हाल IP6_MH_TYPE_HOT:
	हाल IP6_MH_TYPE_COT:
	हाल IP6_MH_TYPE_BERROR:
		len = 2;
		अवरोध;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक mip6_mh_filter(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा ip6_mh _hdr;
	स्थिर काष्ठा ip6_mh *mh;

	mh = skb_header_poपूर्णांकer(skb, skb_transport_offset(skb),
				माप(_hdr), &_hdr);
	अगर (!mh)
		वापस -1;

	अगर (((mh->ip6mh_hdrlen + 1) << 3) > skb->len)
		वापस -1;

	अगर (mh->ip6mh_hdrlen < mip6_mh_len(mh->ip6mh_type)) अणु
		net_dbg_ratelimited("mip6: MH message too short: %d vs >=%d\n",
				    mh->ip6mh_hdrlen,
				    mip6_mh_len(mh->ip6mh_type));
		mip6_param_prob(skb, 0, दुरत्व(काष्ठा ip6_mh, ip6mh_hdrlen) +
				skb_network_header_len(skb));
		वापस -1;
	पूर्ण

	अगर (mh->ip6mh_proto != IPPROTO_NONE) अणु
		net_dbg_ratelimited("mip6: MH invalid payload proto = %d\n",
				    mh->ip6mh_proto);
		mip6_param_prob(skb, 0, दुरत्व(काष्ठा ip6_mh, ip6mh_proto) +
				skb_network_header_len(skb));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा mip6_report_rate_limiter अणु
	spinlock_t lock;
	kसमय_प्रकार stamp;
	पूर्णांक iअगर;
	काष्ठा in6_addr src;
	काष्ठा in6_addr dst;
पूर्ण;

अटल काष्ठा mip6_report_rate_limiter mip6_report_rl = अणु
	.lock = __SPIN_LOCK_UNLOCKED(mip6_report_rl.lock)
पूर्ण;

अटल पूर्णांक mip6_destopt_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा ipv6_destopt_hdr *destopt = (काष्ठा ipv6_destopt_hdr *)skb->data;
	पूर्णांक err = destopt->nexthdr;

	spin_lock(&x->lock);
	अगर (!ipv6_addr_equal(&iph->saddr, (काष्ठा in6_addr *)x->coaddr) &&
	    !ipv6_addr_any((काष्ठा in6_addr *)x->coaddr))
		err = -ENOENT;
	spin_unlock(&x->lock);

	वापस err;
पूर्ण

/* Destination Option Header is inserted.
 * IP Header's src address is replaced with Home Address Option in
 * Destination Option Header.
 */
अटल पूर्णांक mip6_destopt_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *iph;
	काष्ठा ipv6_destopt_hdr *dstopt;
	काष्ठा ipv6_destopt_hao *hao;
	u8 nexthdr;
	पूर्णांक len;

	skb_push(skb, -skb_network_offset(skb));
	iph = ipv6_hdr(skb);

	nexthdr = *skb_mac_header(skb);
	*skb_mac_header(skb) = IPPROTO_DSTOPTS;

	dstopt = (काष्ठा ipv6_destopt_hdr *)skb_transport_header(skb);
	dstopt->nexthdr = nexthdr;

	hao = mip6_padn((अक्षर *)(dstopt + 1),
			calc_padlen(माप(*dstopt), 6));

	hao->type = IPV6_TLV_HAO;
	BUILD_BUG_ON(माप(*hao) != 18);
	hao->length = माप(*hao) - 2;

	len = ((अक्षर *)hao - (अक्षर *)dstopt) + माप(*hao);

	स_नकल(&hao->addr, &iph->saddr, माप(hao->addr));
	spin_lock_bh(&x->lock);
	स_नकल(&iph->saddr, x->coaddr, माप(iph->saddr));
	spin_unlock_bh(&x->lock);

	WARN_ON(len != x->props.header_len);
	dstopt->hdrlen = (x->props.header_len >> 3) - 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mip6_report_rl_allow(kसमय_प्रकार stamp,
				       स्थिर काष्ठा in6_addr *dst,
				       स्थिर काष्ठा in6_addr *src, पूर्णांक iअगर)
अणु
	पूर्णांक allow = 0;

	spin_lock_bh(&mip6_report_rl.lock);
	अगर (mip6_report_rl.stamp != stamp ||
	    mip6_report_rl.iअगर != iअगर ||
	    !ipv6_addr_equal(&mip6_report_rl.src, src) ||
	    !ipv6_addr_equal(&mip6_report_rl.dst, dst)) अणु
		mip6_report_rl.stamp = stamp;
		mip6_report_rl.iअगर = iअगर;
		mip6_report_rl.src = *src;
		mip6_report_rl.dst = *dst;
		allow = 1;
	पूर्ण
	spin_unlock_bh(&mip6_report_rl.lock);
	वापस allow;
पूर्ण

अटल पूर्णांक mip6_destopt_reject(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			       स्थिर काष्ठा flowi *fl)
अणु
	काष्ठा net *net = xs_net(x);
	काष्ठा inet6_skb_parm *opt = (काष्ठा inet6_skb_parm *)skb->cb;
	स्थिर काष्ठा flowi6 *fl6 = &fl->u.ip6;
	काष्ठा ipv6_destopt_hao *hao = शून्य;
	काष्ठा xfrm_selector sel;
	पूर्णांक offset;
	kसमय_प्रकार stamp;
	पूर्णांक err = 0;

	अगर (unlikely(fl6->flowi6_proto == IPPROTO_MH &&
		     fl6->fl6_mh_type <= IP6_MH_TYPE_MAX))
		जाओ out;

	अगर (likely(opt->dsthao)) अणु
		offset = ipv6_find_tlv(skb, opt->dsthao, IPV6_TLV_HAO);
		अगर (likely(offset >= 0))
			hao = (काष्ठा ipv6_destopt_hao *)
					(skb_network_header(skb) + offset);
	पूर्ण

	stamp = skb_get_kसमय(skb);

	अगर (!mip6_report_rl_allow(stamp, &ipv6_hdr(skb)->daddr,
				  hao ? &hao->addr : &ipv6_hdr(skb)->saddr,
				  opt->iअगर))
		जाओ out;

	स_रखो(&sel, 0, माप(sel));
	स_नकल(&sel.daddr, (xfrm_address_t *)&ipv6_hdr(skb)->daddr,
	       माप(sel.daddr));
	sel.prefixlen_d = 128;
	स_नकल(&sel.saddr, (xfrm_address_t *)&ipv6_hdr(skb)->saddr,
	       माप(sel.saddr));
	sel.prefixlen_s = 128;
	sel.family = AF_INET6;
	sel.proto = fl6->flowi6_proto;
	sel.dport = xfrm_flowi_dport(fl, &fl6->uli);
	अगर (sel.dport)
		sel.dport_mask = htons(~0);
	sel.sport = xfrm_flowi_sport(fl, &fl6->uli);
	अगर (sel.sport)
		sel.sport_mask = htons(~0);
	sel.अगरindex = fl6->flowi6_oअगर;

	err = km_report(net, IPPROTO_DSTOPTS, &sel,
			(hao ? (xfrm_address_t *)&hao->addr : शून्य));

 out:
	वापस err;
पूर्ण

अटल पूर्णांक mip6_destopt_offset(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			       u8 **nexthdr)
अणु
	u16 offset = माप(काष्ठा ipv6hdr);
	काष्ठा ipv6_opt_hdr *exthdr =
				   (काष्ठा ipv6_opt_hdr *)(ipv6_hdr(skb) + 1);
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
	अचिन्हित पूर्णांक packet_len = skb_tail_poपूर्णांकer(skb) -
		skb_network_header(skb);
	पूर्णांक found_rhdr = 0;

	*nexthdr = &ipv6_hdr(skb)->nexthdr;

	जबतक (offset + 1 <= packet_len) अणु

		चयन (**nexthdr) अणु
		हाल NEXTHDR_HOP:
			अवरोध;
		हाल NEXTHDR_ROUTING:
			found_rhdr = 1;
			अवरोध;
		हाल NEXTHDR_DEST:
			/*
			 * HAO MUST NOT appear more than once.
			 * XXX: It is better to try to find by the end of
			 * XXX: packet अगर HAO exists.
			 */
			अगर (ipv6_find_tlv(skb, offset, IPV6_TLV_HAO) >= 0) अणु
				net_dbg_ratelimited("mip6: hao exists already, override\n");
				वापस offset;
			पूर्ण

			अगर (found_rhdr)
				वापस offset;

			अवरोध;
		शेष:
			वापस offset;
		पूर्ण

		offset += ipv6_optlen(exthdr);
		*nexthdr = &exthdr->nexthdr;
		exthdr = (काष्ठा ipv6_opt_hdr *)(nh + offset);
	पूर्ण

	वापस offset;
पूर्ण

अटल पूर्णांक mip6_destopt_init_state(काष्ठा xfrm_state *x)
अणु
	अगर (x->id.spi) अणु
		pr_info("%s: spi is not 0: %u\n", __func__, x->id.spi);
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.mode != XFRM_MODE_ROUTEOPTIMIZATION) अणु
		pr_info("%s: state's mode is not %u: %u\n",
			__func__, XFRM_MODE_ROUTEOPTIMIZATION, x->props.mode);
		वापस -EINVAL;
	पूर्ण

	x->props.header_len = माप(काष्ठा ipv6_destopt_hdr) +
		calc_padlen(माप(काष्ठा ipv6_destopt_hdr), 6) +
		माप(काष्ठा ipv6_destopt_hao);
	WARN_ON(x->props.header_len != 24);

	वापस 0;
पूर्ण

/*
 * Do nothing about destroying since it has no specअगरic operation क्रम
 * destination options header unlike IPsec protocols.
 */
अटल व्योम mip6_destopt_destroy(काष्ठा xfrm_state *x)
अणु
पूर्ण

अटल स्थिर काष्ठा xfrm_type mip6_destopt_type = अणु
	.description	= "MIP6DESTOPT",
	.owner		= THIS_MODULE,
	.proto		= IPPROTO_DSTOPTS,
	.flags		= XFRM_TYPE_NON_FRAGMENT | XFRM_TYPE_LOCAL_COADDR,
	.init_state	= mip6_destopt_init_state,
	.deकाष्ठाor	= mip6_destopt_destroy,
	.input		= mip6_destopt_input,
	.output		= mip6_destopt_output,
	.reject		= mip6_destopt_reject,
	.hdr_offset	= mip6_destopt_offset,
पूर्ण;

अटल पूर्णांक mip6_rthdr_input(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा rt2_hdr *rt2 = (काष्ठा rt2_hdr *)skb->data;
	पूर्णांक err = rt2->rt_hdr.nexthdr;

	spin_lock(&x->lock);
	अगर (!ipv6_addr_equal(&iph->daddr, (काष्ठा in6_addr *)x->coaddr) &&
	    !ipv6_addr_any((काष्ठा in6_addr *)x->coaddr))
		err = -ENOENT;
	spin_unlock(&x->lock);

	वापस err;
पूर्ण

/* Routing Header type 2 is inserted.
 * IP Header's dst address is replaced with Routing Header's Home Address.
 */
अटल पूर्णांक mip6_rthdr_output(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *iph;
	काष्ठा rt2_hdr *rt2;
	u8 nexthdr;

	skb_push(skb, -skb_network_offset(skb));
	iph = ipv6_hdr(skb);

	nexthdr = *skb_mac_header(skb);
	*skb_mac_header(skb) = IPPROTO_ROUTING;

	rt2 = (काष्ठा rt2_hdr *)skb_transport_header(skb);
	rt2->rt_hdr.nexthdr = nexthdr;
	rt2->rt_hdr.hdrlen = (x->props.header_len >> 3) - 1;
	rt2->rt_hdr.type = IPV6_SRCRT_TYPE_2;
	rt2->rt_hdr.segments_left = 1;
	स_रखो(&rt2->reserved, 0, माप(rt2->reserved));

	WARN_ON(rt2->rt_hdr.hdrlen != 2);

	स_नकल(&rt2->addr, &iph->daddr, माप(rt2->addr));
	spin_lock_bh(&x->lock);
	स_नकल(&iph->daddr, x->coaddr, माप(iph->daddr));
	spin_unlock_bh(&x->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mip6_rthdr_offset(काष्ठा xfrm_state *x, काष्ठा sk_buff *skb,
			     u8 **nexthdr)
अणु
	u16 offset = माप(काष्ठा ipv6hdr);
	काष्ठा ipv6_opt_hdr *exthdr =
				   (काष्ठा ipv6_opt_hdr *)(ipv6_hdr(skb) + 1);
	स्थिर अचिन्हित अक्षर *nh = skb_network_header(skb);
	अचिन्हित पूर्णांक packet_len = skb_tail_poपूर्णांकer(skb) -
		skb_network_header(skb);
	पूर्णांक found_rhdr = 0;

	*nexthdr = &ipv6_hdr(skb)->nexthdr;

	जबतक (offset + 1 <= packet_len) अणु

		चयन (**nexthdr) अणु
		हाल NEXTHDR_HOP:
			अवरोध;
		हाल NEXTHDR_ROUTING:
			अगर (offset + 3 <= packet_len) अणु
				काष्ठा ipv6_rt_hdr *rt;
				rt = (काष्ठा ipv6_rt_hdr *)(nh + offset);
				अगर (rt->type != 0)
					वापस offset;
			पूर्ण
			found_rhdr = 1;
			अवरोध;
		हाल NEXTHDR_DEST:
			अगर (ipv6_find_tlv(skb, offset, IPV6_TLV_HAO) >= 0)
				वापस offset;

			अगर (found_rhdr)
				वापस offset;

			अवरोध;
		शेष:
			वापस offset;
		पूर्ण

		offset += ipv6_optlen(exthdr);
		*nexthdr = &exthdr->nexthdr;
		exthdr = (काष्ठा ipv6_opt_hdr *)(nh + offset);
	पूर्ण

	वापस offset;
पूर्ण

अटल पूर्णांक mip6_rthdr_init_state(काष्ठा xfrm_state *x)
अणु
	अगर (x->id.spi) अणु
		pr_info("%s: spi is not 0: %u\n", __func__, x->id.spi);
		वापस -EINVAL;
	पूर्ण
	अगर (x->props.mode != XFRM_MODE_ROUTEOPTIMIZATION) अणु
		pr_info("%s: state's mode is not %u: %u\n",
			__func__, XFRM_MODE_ROUTEOPTIMIZATION, x->props.mode);
		वापस -EINVAL;
	पूर्ण

	x->props.header_len = माप(काष्ठा rt2_hdr);

	वापस 0;
पूर्ण

/*
 * Do nothing about destroying since it has no specअगरic operation क्रम routing
 * header type 2 unlike IPsec protocols.
 */
अटल व्योम mip6_rthdr_destroy(काष्ठा xfrm_state *x)
अणु
पूर्ण

अटल स्थिर काष्ठा xfrm_type mip6_rthdr_type = अणु
	.description	= "MIP6RT",
	.owner		= THIS_MODULE,
	.proto		= IPPROTO_ROUTING,
	.flags		= XFRM_TYPE_NON_FRAGMENT | XFRM_TYPE_REMOTE_COADDR,
	.init_state	= mip6_rthdr_init_state,
	.deकाष्ठाor	= mip6_rthdr_destroy,
	.input		= mip6_rthdr_input,
	.output		= mip6_rthdr_output,
	.hdr_offset	= mip6_rthdr_offset,
पूर्ण;

अटल पूर्णांक __init mip6_init(व्योम)
अणु
	pr_info("Mobile IPv6\n");

	अगर (xfrm_रेजिस्टर_type(&mip6_destopt_type, AF_INET6) < 0) अणु
		pr_info("%s: can't add xfrm type(destopt)\n", __func__);
		जाओ mip6_destopt_xfrm_fail;
	पूर्ण
	अगर (xfrm_रेजिस्टर_type(&mip6_rthdr_type, AF_INET6) < 0) अणु
		pr_info("%s: can't add xfrm type(rthdr)\n", __func__);
		जाओ mip6_rthdr_xfrm_fail;
	पूर्ण
	अगर (rawv6_mh_filter_रेजिस्टर(mip6_mh_filter) < 0) अणु
		pr_info("%s: can't add rawv6 mh filter\n", __func__);
		जाओ mip6_rawv6_mh_fail;
	पूर्ण


	वापस 0;

 mip6_rawv6_mh_fail:
	xfrm_unरेजिस्टर_type(&mip6_rthdr_type, AF_INET6);
 mip6_rthdr_xfrm_fail:
	xfrm_unरेजिस्टर_type(&mip6_destopt_type, AF_INET6);
 mip6_destopt_xfrm_fail:
	वापस -EAGAIN;
पूर्ण

अटल व्योम __निकास mip6_fini(व्योम)
अणु
	अगर (rawv6_mh_filter_unरेजिस्टर(mip6_mh_filter) < 0)
		pr_info("%s: can't remove rawv6 mh filter\n", __func__);
	xfrm_unरेजिस्टर_type(&mip6_rthdr_type, AF_INET6);
	xfrm_unरेजिस्टर_type(&mip6_destopt_type, AF_INET6);
पूर्ण

module_init(mip6_init);
module_निकास(mip6_fini);

MODULE_LICENSE("GPL");
MODULE_ALIAS_XFRM_TYPE(AF_INET6, XFRM_PROTO_DSTOPTS);
MODULE_ALIAS_XFRM_TYPE(AF_INET6, XFRM_PROTO_ROUTING);
