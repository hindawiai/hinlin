<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nft_fib.h>

#समावेश <net/ip_fib.h>
#समावेश <net/route.h>

/* करोn't try to find route from mcast/bcast/zeronet */
अटल __be32 get_saddr(__be32 addr)
अणु
	अगर (ipv4_is_multicast(addr) || ipv4_is_lbcast(addr) ||
	    ipv4_is_zeronet(addr))
		वापस 0;
	वापस addr;
पूर्ण

#घोषणा DSCP_BITS     0xfc

व्योम nft_fib4_eval_type(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
			स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);
	पूर्णांक noff = skb_network_offset(pkt->skb);
	u32 *dst = &regs->data[priv->dreg];
	स्थिर काष्ठा net_device *dev = शून्य;
	काष्ठा iphdr *iph, _iph;
	__be32 addr;

	अगर (priv->flags & NFTA_FIB_F_IIF)
		dev = nft_in(pkt);
	अन्यथा अगर (priv->flags & NFTA_FIB_F_OIF)
		dev = nft_out(pkt);

	iph = skb_header_poपूर्णांकer(pkt->skb, noff, माप(_iph), &_iph);
	अगर (!iph) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	अगर (priv->flags & NFTA_FIB_F_DADDR)
		addr = iph->daddr;
	अन्यथा
		addr = iph->saddr;

	*dst = inet_dev_addr_type(nft_net(pkt), dev, addr);
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib4_eval_type);

व्योम nft_fib4_eval(स्थिर काष्ठा nft_expr *expr, काष्ठा nft_regs *regs,
		   स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_fib *priv = nft_expr_priv(expr);
	पूर्णांक noff = skb_network_offset(pkt->skb);
	u32 *dest = &regs->data[priv->dreg];
	काष्ठा iphdr *iph, _iph;
	काष्ठा fib_result res;
	काष्ठा flowi4 fl4 = अणु
		.flowi4_scope = RT_SCOPE_UNIVERSE,
		.flowi4_iअगर = LOOPBACK_IFINDEX,
	पूर्ण;
	स्थिर काष्ठा net_device *oअगर;
	स्थिर काष्ठा net_device *found;

	/*
	 * Do not set flowi4_oअगर, it restricts results (क्रम example, asking
	 * क्रम oअगर 3 will get RTN_UNICAST result even अगर the daddr निकासs
	 * on another पूर्णांकerface.
	 *
	 * Search results क्रम the desired outपूर्णांकerface instead.
	 */
	अगर (priv->flags & NFTA_FIB_F_OIF)
		oअगर = nft_out(pkt);
	अन्यथा अगर (priv->flags & NFTA_FIB_F_IIF)
		oअगर = nft_in(pkt);
	अन्यथा
		oअगर = शून्य;

	अगर (nft_hook(pkt) == NF_INET_PRE_ROUTING &&
	    nft_fib_is_loopback(pkt->skb, nft_in(pkt))) अणु
		nft_fib_store_result(dest, priv, nft_in(pkt));
		वापस;
	पूर्ण

	iph = skb_header_poपूर्णांकer(pkt->skb, noff, माप(_iph), &_iph);
	अगर (!iph) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	अगर (ipv4_is_zeronet(iph->saddr)) अणु
		अगर (ipv4_is_lbcast(iph->daddr) ||
		    ipv4_is_local_multicast(iph->daddr)) अणु
			nft_fib_store_result(dest, priv, pkt->skb->dev);
			वापस;
		पूर्ण
	पूर्ण

	अगर (priv->flags & NFTA_FIB_F_MARK)
		fl4.flowi4_mark = pkt->skb->mark;

	fl4.flowi4_tos = iph->tos & DSCP_BITS;

	अगर (priv->flags & NFTA_FIB_F_DADDR) अणु
		fl4.daddr = iph->daddr;
		fl4.saddr = get_saddr(iph->saddr);
	पूर्ण अन्यथा अणु
		fl4.daddr = iph->saddr;
		fl4.saddr = get_saddr(iph->daddr);
	पूर्ण

	*dest = 0;

	अगर (fib_lookup(nft_net(pkt), &fl4, &res, FIB_LOOKUP_IGNORE_LINKSTATE))
		वापस;

	चयन (res.type) अणु
	हाल RTN_UNICAST:
		अवरोध;
	हाल RTN_LOCAL: /* Should not see RTN_LOCAL here */
		वापस;
	शेष:
		अवरोध;
	पूर्ण

       अगर (!oअगर) अणु
               found = FIB_RES_DEV(res);
	पूर्ण अन्यथा अणु
		अगर (!fib_info_nh_uses_dev(res.fi, oअगर))
			वापस;

		found = oअगर;
	पूर्ण

	nft_fib_store_result(dest, priv, found);
पूर्ण
EXPORT_SYMBOL_GPL(nft_fib4_eval);

अटल काष्ठा nft_expr_type nft_fib4_type;

अटल स्थिर काष्ठा nft_expr_ops nft_fib4_type_ops = अणु
	.type		= &nft_fib4_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fib)),
	.eval		= nft_fib4_eval_type,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.validate	= nft_fib_validate,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_fib4_ops = अणु
	.type		= &nft_fib4_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_fib)),
	.eval		= nft_fib4_eval,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.validate	= nft_fib_validate,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_fib4_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	क्रमागत nft_fib_result result;

	अगर (!tb[NFTA_FIB_RESULT])
		वापस ERR_PTR(-EINVAL);

	result = ntohl(nla_get_be32(tb[NFTA_FIB_RESULT]));

	चयन (result) अणु
	हाल NFT_FIB_RESULT_OIF:
		वापस &nft_fib4_ops;
	हाल NFT_FIB_RESULT_OIFNAME:
		वापस &nft_fib4_ops;
	हाल NFT_FIB_RESULT_ADDRTYPE:
		वापस &nft_fib4_type_ops;
	शेष:
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण
पूर्ण

अटल काष्ठा nft_expr_type nft_fib4_type __पढ़ो_mostly = अणु
	.name		= "fib",
	.select_ops	= nft_fib4_select_ops,
	.policy		= nft_fib_policy,
	.maxattr	= NFTA_FIB_MAX,
	.family		= NFPROTO_IPV4,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_fib4_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_fib4_type);
पूर्ण

अटल व्योम __निकास nft_fib4_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_fib4_type);
पूर्ण

module_init(nft_fib4_module_init);
module_निकास(nft_fib4_module_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Florian Westphal <fw@strlen.de>");
MODULE_ALIAS_NFT_AF_EXPR(2, "fib");
MODULE_DESCRIPTION("nftables fib / ip route lookup support");
