<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2016 Anders K. Pedersen <akp@cohaesio.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/dst.h>
#समावेश <net/ip6_route.h>
#समावेश <net/route.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>

काष्ठा nft_rt अणु
	क्रमागत nft_rt_keys	key:8;
	u8			dreg;
पूर्ण;

अटल u16 get_tcpmss(स्थिर काष्ठा nft_pktinfo *pkt, स्थिर काष्ठा dst_entry *skbdst)
अणु
	u32 minlen = माप(काष्ठा ipv6hdr), mtu = dst_mtu(skbdst);
	स्थिर काष्ठा sk_buff *skb = pkt->skb;
	काष्ठा dst_entry *dst = शून्य;
	काष्ठा flowi fl;

	स_रखो(&fl, 0, माप(fl));

	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		fl.u.ip4.daddr = ip_hdr(skb)->saddr;
		minlen = माप(काष्ठा iphdr) + माप(काष्ठा tcphdr);
		अवरोध;
	हाल NFPROTO_IPV6:
		fl.u.ip6.daddr = ipv6_hdr(skb)->saddr;
		minlen = माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr);
		अवरोध;
	पूर्ण

	nf_route(nft_net(pkt), &dst, &fl, false, nft_pf(pkt));
	अगर (dst) अणु
		mtu = min(mtu, dst_mtu(dst));
		dst_release(dst);
	पूर्ण

	अगर (mtu <= minlen || mtu > 0xffff)
		वापस TCP_MSS_DEFAULT;

	वापस mtu - minlen;
पूर्ण

व्योम nft_rt_get_eval(स्थिर काष्ठा nft_expr *expr,
		     काष्ठा nft_regs *regs,
		     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_rt *priv = nft_expr_priv(expr);
	स्थिर काष्ठा sk_buff *skb = pkt->skb;
	u32 *dest = &regs->data[priv->dreg];
	स्थिर काष्ठा dst_entry *dst;

	dst = skb_dst(skb);
	अगर (!dst)
		जाओ err;

	चयन (priv->key) अणु
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	हाल NFT_RT_CLASSID:
		*dest = dst->tclassid;
		अवरोध;
#पूर्ण_अगर
	हाल NFT_RT_NEXTHOP4:
		अगर (nft_pf(pkt) != NFPROTO_IPV4)
			जाओ err;

		*dest = (__क्रमce u32)rt_nexthop((स्थिर काष्ठा rtable *)dst,
						ip_hdr(skb)->daddr);
		अवरोध;
	हाल NFT_RT_NEXTHOP6:
		अगर (nft_pf(pkt) != NFPROTO_IPV6)
			जाओ err;

		स_नकल(dest, rt6_nexthop((काष्ठा rt6_info *)dst,
					 &ipv6_hdr(skb)->daddr),
		       माप(काष्ठा in6_addr));
		अवरोध;
	हाल NFT_RT_TCPMSS:
		nft_reg_store16(dest, get_tcpmss(pkt, dst));
		अवरोध;
#अगर_घोषित CONFIG_XFRM
	हाल NFT_RT_XFRM:
		nft_reg_store8(dest, !!dst->xfrm);
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON(1);
		जाओ err;
	पूर्ण
	वापस;

err:
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_rt_policy[NFTA_RT_MAX + 1] = अणु
	[NFTA_RT_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_RT_KEY]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_rt_get_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_rt *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;

	अगर (tb[NFTA_RT_KEY] == शून्य ||
	    tb[NFTA_RT_DREG] == शून्य)
		वापस -EINVAL;

	priv->key = ntohl(nla_get_be32(tb[NFTA_RT_KEY]));
	चयन (priv->key) अणु
#अगर_घोषित CONFIG_IP_ROUTE_CLASSID
	हाल NFT_RT_CLASSID:
#पूर्ण_अगर
	हाल NFT_RT_NEXTHOP4:
		len = माप(u32);
		अवरोध;
	हाल NFT_RT_NEXTHOP6:
		len = माप(काष्ठा in6_addr);
		अवरोध;
	हाल NFT_RT_TCPMSS:
		len = माप(u16);
		अवरोध;
#अगर_घोषित CONFIG_XFRM
	हाल NFT_RT_XFRM:
		len = माप(u8);
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_RT_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, len);
पूर्ण

अटल पूर्णांक nft_rt_get_dump(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_rt *priv = nft_expr_priv(expr);

	अगर (nla_put_be32(skb, NFTA_RT_KEY, htonl(priv->key)))
		जाओ nla_put_failure;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_RT_DREG, priv->dreg))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_rt_validate(स्थिर काष्ठा nft_ctx *ctx, स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nft_data **data)
अणु
	स्थिर काष्ठा nft_rt *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक hooks;

	चयन (priv->key) अणु
	हाल NFT_RT_NEXTHOP4:
	हाल NFT_RT_NEXTHOP6:
	हाल NFT_RT_CLASSID:
	हाल NFT_RT_XFRM:
		वापस 0;
	हाल NFT_RT_TCPMSS:
		hooks = (1 << NF_INET_FORWARD) |
			(1 << NF_INET_LOCAL_OUT) |
			(1 << NF_INET_POST_ROUTING);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस nft_chain_validate_hooks(ctx->chain, hooks);
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_rt_get_ops = अणु
	.type		= &nft_rt_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_rt)),
	.eval		= nft_rt_get_eval,
	.init		= nft_rt_get_init,
	.dump		= nft_rt_get_dump,
	.validate	= nft_rt_validate,
पूर्ण;

काष्ठा nft_expr_type nft_rt_type __पढ़ो_mostly = अणु
	.name		= "rt",
	.ops		= &nft_rt_get_ops,
	.policy		= nft_rt_policy,
	.maxattr	= NFTA_RT_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
