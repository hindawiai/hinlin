<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <linux/netfilter_ipv6.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nft_fib.h>

#समावेश <net/ip6_fib.h>
#समावेश <net/ip6_route.h>

अटल पूर्णांक get_अगरindex(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev ? dev->अगरindex : 0;
पूर्ण

अटल पूर्णांक nft_fib6_flowi_init(काष्ठा flowi6 *fl6, स्थिर काष्ठा nft_fib *priv,
			       स्थिर काष्ठा nft_pktinfo *pkt,
			       स्थिर काष्ठा net_device *dev,
			       काष्ठा ipv6hdr *iph)
अणु
	पूर्णांक lookup_flags = 0;

	अगर (priv->flags & NFTA_FIB_F_DADDR) अणु
		fl6->daddr = iph->daddr;
		fl6->saddr = iph->saddr;
	पूर्ण अन्यथा अणु
		fl6->daddr = iph->saddr;
		fl6->saddr = iph->daddr;
	पूर्ण

	अगर (ipv6_addr_type(&fl6->daddr) & IPV6_ADDR_LINKLOCAL) अणु
		lookup_flags |= RT6_LOOKUP_F_IFACE;
		fl6->flowi6_oअगर = get_अगरindex(dev ? dev : pkt->skb->dev);
	पूर्ण

	अगर (ipv6_addr_type(&fl6->saddr) & IPV6_ADDR_UNICAST)
		lookup_flags |= RT6_LOOKUP_F_HAS_SADDR;

	अगर (priv->flags & NFTA_FIB_F_MARK)
		fl6->flowi6_mark = pkt->skb->mark;

	fl6->flowlabel = (*(__be32 *)iph) & IPV6_FLOWINFO_MASK;

	वापस lookup_flags;
पूर्ण

अटल u32 __nft_fib6_eval_type(स्थिर काष्ठा nft_fib *priv,
				स्थिर काष्ठा nft_pktinfo *pkt,
				काष्ठा ipv6hdr *iph)
अणु
	स्थिर काष्ठा net_device *dev = शून्य;
	पूर्णांक route_err, addrtype;
	काष्ठा rt6_info *rt;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर = LOOPBACK_IFINDEX,
		.flowi6_proto = pkt->tprot,
	पूर्ण;
	u32 ret = 0;

	अगर (priv->flags & NFTA_FIB_F_IIF)
		dev = nft_in(pkt);
	अन्यथा अगर (priv->flags & NFTA_FIB_F_OIF)
		dev = nft_out(pkt);

	nft_fib6_flowi_init(&fl6, priv, pkt, dev, iph);

	अगर (dev && nf_ipv6_chk_addr(nft_net(pkt), &fl6.daddr, dev, true))
		ret = RTN_LOCAL;

	route_err = nf_ip6_route(nft_net(pkt), (काष्ठा dst_entry **)&rt,
				 flowi6_to_flowi(&fl6), false);
	अगर (route_err)
		जाओ err;

	अगर (rt->rt6i_flags & RTF_REJECT) अणु
		route_err = rt->dst.error;
		dst_release(&rt->dst);
		जाओ err;
	पूर्ण

	अगर (ipv6_anycast_destination((काष्ठा dst_entry *)rt, &fl6.daddr))
		ret = RTN_ANYCAST;
	अन्यथा अगर (!dev && rt->rt6i_flags & RTF_LOCAL)
		ret = RTN_LOCAL;

	dst_release(&rt->dst);

	अगर (ret)
		वापस ret;

	addrtype = ipv6_addr_type(&fl6.daddr);

	अगर (addrtype & IPV6_ADDR_MULTICAST)
		वापस RTN_MULTICAST;
	अगर (addrtype & IPV6_ADDR_UNICAST)
		वापस RTN_UNICAST;

	वापस RTN_UNSPEC;
 err:
	चयन (route_err) अणु
	हाल -EINVAL:
		वापस RTN_BLACKHOLE;
	हाल -EACCES:
		वापस RTN_PROHIBIT;
	हाल -EAGAIN:
		वापस RTN_THROW;
	शेष:
		अवरोध;
	पूर्ण

	वापस RTN_UNREACHABLE;
पूर्ण

व्योम nft_fib6_eval_type(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
			स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);
	पूर्णांक noff = skb_network_offset(pkt->skb);
	u32 *dest = &regs->data[priv->dreg];
	काष्ठा ipv6hdr *iph, _iph;

	iph = skb_header_poपूर्णांकer(pkt->skb, noff, माप(_iph), &_iph);
	अगर (!iph) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	*dest = __nft_fib6_eval_type(priv, pkt, iph);
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib6_eval_type);

अटल bool nft_fib_v6_skip_icmpv6(स्थिर काष्ठा sk_buff *skb, u8 next, स्थिर काष्ठा ipv6hdr *iph)
अणु
	अगर (likely(next != IPPROTO_ICMPV6))
		वापस false;

	अगर (ipv6_addr_type(&iph->saddr) != IPV6_ADDR_ANY)
		वापस false;

	वापस ipv6_addr_type(&iph->daddr) & IPV6_ADDR_LINKLOCAL;
पूर्ण

व्योम nft_fib6_eval(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
		   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);
	पूर्णांक noff = skb_network_offset(pkt->skb);
	स्थिर काष्ठा net_device *oअगर = शून्य;
	u32 *dest = &regs->data[priv->dreg];
	काष्ठा ipv6hdr *iph, _iph;
	काष्ठा flowi6 fl6 = अणु
		.flowi6_iअगर = LOOPBACK_IFINDEX,
		.flowi6_proto = pkt->tprot,
	पूर्ण;
	काष्ठा rt6_info *rt;
	पूर्णांक lookup_flags;

	अगर (priv->flags & NFTA_FIB_F_IIF)
		oअगर = nft_in(pkt);
	अन्यथा अगर (priv->flags & NFTA_FIB_F_OIF)
		oअगर = nft_out(pkt);

	iph = skb_header_poपूर्णांकer(pkt->skb, noff, माप(_iph), &_iph);
	अगर (!iph) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	lookup_flags = nft_fib6_flowi_init(&fl6, priv, pkt, oअगर, iph);

	अगर (nft_hook(pkt) == NF_INET_PRE_ROUTING ||
	    nft_hook(pkt) == NF_INET_INGRESS) अणु
		अगर (nft_fib_is_loopback(pkt->skb, nft_in(pkt)) ||
		    nft_fib_v6_skip_icmpv6(pkt->skb, pkt->tprot, iph)) अणु
			nft_fib_store_result(dest, priv, nft_in(pkt));
			वापस;
		पूर्ण
	पूर्ण

	*dest = 0;
	rt = (व्योम *)ip6_route_lookup(nft_net(pkt), &fl6, pkt->skb,
				      lookup_flags);
	अगर (rt->dst.error)
		जाओ put_rt_err;

	/* Should not see RTF_LOCAL here */
	अगर (rt->rt6i_flags & (RTF_REJECT | RTF_ANYCAST | RTF_LOCAL))
		जाओ put_rt_err;

	अगर (oअगर && oअगर != rt->rt6i_idev->dev)
		जाओ put_rt_err;

	nft_fib_store_result(dest, priv, rt->rt6i_idev->dev);
 put_rt_err:
	ip6_rt_put(rt);
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib6_eval);

अटल काष्ठा nft_expr_type nft_fib6_type;

अटल स्थिर काष्ठा nft_expr_ops nft_fib6_type_ops = अणु
	.type		= &nft_fib6_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fib)),
	.eval		= nft_fib6_eval_type,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.validate	= nft_fib_validate,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_fib6_ops = अणु
	.type		= &nft_fib6_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fib)),
	.eval		= nft_fib6_eval,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.validate	= nft_fib_validate,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_fib6_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	क्रमागत nft_fib_result result;

	अगर (!tb[NFTA_FIB_RESULT])
		वापस ERR_PTR(-EINVAL);

	result = ntohl(nla_get_be32(tb[NFTA_FIB_RESULT]));

	चयन (result) अणु
	हाल NFT_FIB_RESULT_OIF:
		वापस &nft_fib6_ops;
	हाल NFT_FIB_RESULT_OIFNAME:
		वापस &nft_fib6_ops;
	हाल NFT_FIB_RESULT_ADDRTYPE:
		वापस &nft_fib6_type_ops;
	शेष:
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण
पूर्ण

अटल काष्ठा nft_expr_type nft_fib6_type __पढ़ो_mostly = अणु
	.name		= "fib",
	.select_ops	= nft_fib6_select_ops,
	.policy		= nft_fib_policy,
	.maxattr	= NFTA_FIB_MAX,
	.family		= NFPROTO_IPV6,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_fib6_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_fib6_type);
पूर्ण

अटल व्योम __निकास nft_fib6_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_fib6_type);
पूर्ण
module_init(nft_fib6_module_init);
module_निकास(nft_fib6_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_ALIAS_NFT_AF_EXPR(10, "fib");
MODULE_DESCRIPTION("nftables fib / ipv6 route lookup support");
