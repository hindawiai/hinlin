<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tproxy.h>
#समावेश <net/inet_sock.h>
#समावेश <net/tcp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/netfilter/ipv4/nf_defrag_ipv4.h>
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
#समावेश <net/netfilter/ipv6/nf_defrag_ipv6.h>
#पूर्ण_अगर

काष्ठा nft_tproxy अणु
	u8	sreg_addr;
	u8	sreg_port;
	u8	family;
पूर्ण;

अटल व्योम nft_tproxy_eval_v4(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_tproxy *priv = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा udphdr _hdr, *hp;
	__be32 taddr = 0;
	__be16 tport = 0;
	काष्ठा sock *sk;

	hp = skb_header_poपूर्णांकer(skb, ip_hdrlen(skb), माप(_hdr), &_hdr);
	अगर (!hp) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	/* check अगर there's an ongoing connection on the packet addresses, this
	 * happens अगर the redirect alपढ़ोy happened and the current packet
	 * beदीर्घs to an alपढ़ोy established connection
	 */
	sk = nf_tproxy_get_sock_v4(nft_net(pkt), skb, iph->protocol,
				   iph->saddr, iph->daddr,
				   hp->source, hp->dest,
				   skb->dev, NF_TPROXY_LOOKUP_ESTABLISHED);

	अगर (priv->sreg_addr)
		taddr = regs->data[priv->sreg_addr];
	taddr = nf_tproxy_laddr4(skb, taddr, iph->daddr);

	अगर (priv->sreg_port)
		tport = nft_reg_load16(&regs->data[priv->sreg_port]);
	अगर (!tport)
		tport = hp->dest;

	/* UDP has no TCP_TIME_WAIT state, so we never enter here */
	अगर (sk && sk->sk_state == TCP_TIME_WAIT) अणु
		/* reखोलोing a TIME_WAIT connection needs special handling */
		sk = nf_tproxy_handle_समय_रुको4(nft_net(pkt), skb, taddr, tport, sk);
	पूर्ण अन्यथा अगर (!sk) अणु
		/* no, there's no established connection, check अगर
		 * there's a listener on the redirected addr/port
		 */
		sk = nf_tproxy_get_sock_v4(nft_net(pkt), skb, iph->protocol,
					   iph->saddr, taddr,
					   hp->source, tport,
					   skb->dev, NF_TPROXY_LOOKUP_LISTENER);
	पूर्ण

	अगर (sk && nf_tproxy_sk_is_transparent(sk))
		nf_tproxy_assign_sock(skb, sk);
	अन्यथा
		regs->verdict.code = NFT_BREAK;
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
अटल व्योम nft_tproxy_eval_v6(स्थिर काष्ठा nft_expr *expr,
			       काष्ठा nft_regs *regs,
			       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_tproxy *priv = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
	स्थिर काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा in6_addr taddr;
	पूर्णांक thoff = pkt->xt.thoff;
	काष्ठा udphdr _hdr, *hp;
	__be16 tport = 0;
	काष्ठा sock *sk;
	पूर्णांक l4proto;

	स_रखो(&taddr, 0, माप(taddr));

	अगर (!pkt->tprot_set) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण
	l4proto = pkt->tprot;

	hp = skb_header_poपूर्णांकer(skb, thoff, माप(_hdr), &_hdr);
	अगर (hp == शून्य) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	/* check अगर there's an ongoing connection on the packet addresses, this
	 * happens अगर the redirect alपढ़ोy happened and the current packet
	 * beदीर्घs to an alपढ़ोy established connection
	 */
	sk = nf_tproxy_get_sock_v6(nft_net(pkt), skb, thoff, l4proto,
				   &iph->saddr, &iph->daddr,
				   hp->source, hp->dest,
				   nft_in(pkt), NF_TPROXY_LOOKUP_ESTABLISHED);

	अगर (priv->sreg_addr)
		स_नकल(&taddr, &regs->data[priv->sreg_addr], माप(taddr));
	taddr = *nf_tproxy_laddr6(skb, &taddr, &iph->daddr);

	अगर (priv->sreg_port)
		tport = nft_reg_load16(&regs->data[priv->sreg_port]);
	अगर (!tport)
		tport = hp->dest;

	/* UDP has no TCP_TIME_WAIT state, so we never enter here */
	अगर (sk && sk->sk_state == TCP_TIME_WAIT) अणु
		/* reखोलोing a TIME_WAIT connection needs special handling */
		sk = nf_tproxy_handle_समय_रुको6(skb, l4proto, thoff,
						 nft_net(pkt),
						 &taddr,
						 tport,
						 sk);
	पूर्ण अन्यथा अगर (!sk) अणु
		/* no there's no established connection, check अगर
		 * there's a listener on the redirected addr/port
		 */
		sk = nf_tproxy_get_sock_v6(nft_net(pkt), skb, thoff,
					   l4proto, &iph->saddr, &taddr,
					   hp->source, tport,
					   nft_in(pkt), NF_TPROXY_LOOKUP_LISTENER);
	पूर्ण

	/* NOTE: assign_sock consumes our sk reference */
	अगर (sk && nf_tproxy_sk_is_transparent(sk))
		nf_tproxy_assign_sock(skb, sk);
	अन्यथा
		regs->verdict.code = NFT_BREAK;
पूर्ण
#पूर्ण_अगर

अटल व्योम nft_tproxy_eval(स्थिर काष्ठा nft_expr *expr,
			    काष्ठा nft_regs *regs,
			    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_tproxy *priv = nft_expr_priv(expr);

	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		चयन (priv->family) अणु
		हाल NFPROTO_IPV4:
		हाल NFPROTO_UNSPEC:
			nft_tproxy_eval_v4(expr, regs, pkt);
			वापस;
		पूर्ण
		अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
		चयन (priv->family) अणु
		हाल NFPROTO_IPV6:
		हाल NFPROTO_UNSPEC:
			nft_tproxy_eval_v6(expr, regs, pkt);
			वापस;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tproxy_policy[NFTA_TPROXY_MAX + 1] = अणु
	[NFTA_TPROXY_FAMILY]   = अणु .type = NLA_U32 पूर्ण,
	[NFTA_TPROXY_REG_ADDR] = अणु .type = NLA_U32 पूर्ण,
	[NFTA_TPROXY_REG_PORT] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tproxy_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_tproxy *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक alen = 0;
	पूर्णांक err;

	अगर (!tb[NFTA_TPROXY_FAMILY] ||
	    (!tb[NFTA_TPROXY_REG_ADDR] && !tb[NFTA_TPROXY_REG_PORT]))
		वापस -EINVAL;

	priv->family = ntohl(nla_get_be32(tb[NFTA_TPROXY_FAMILY]));

	चयन (ctx->family) अणु
	हाल NFPROTO_IPV4:
		अगर (priv->family != NFPROTO_IPV4)
			वापस -EINVAL;
		अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
		अगर (priv->family != NFPROTO_IPV6)
			वापस -EINVAL;
		अवरोध;
#पूर्ण_अगर
	हाल NFPROTO_INET:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Address is specअगरied but the rule family is not set accordingly */
	अगर (priv->family == NFPROTO_UNSPEC && tb[NFTA_TPROXY_REG_ADDR])
		वापस -EINVAL;

	चयन (priv->family) अणु
	हाल NFPROTO_IPV4:
		alen = माप_field(जोड़ nf_inet_addr, in);
		err = nf_defrag_ipv4_enable(ctx->net);
		अगर (err)
			वापस err;
		अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
		alen = माप_field(जोड़ nf_inet_addr, in6);
		err = nf_defrag_ipv6_enable(ctx->net);
		अगर (err)
			वापस err;
		अवरोध;
#पूर्ण_अगर
	हाल NFPROTO_UNSPEC:
		/* No address is specअगरied here */
		err = nf_defrag_ipv4_enable(ctx->net);
		अगर (err)
			वापस err;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
		err = nf_defrag_ipv6_enable(ctx->net);
		अगर (err)
			वापस err;
#पूर्ण_अगर
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (tb[NFTA_TPROXY_REG_ADDR]) अणु
		err = nft_parse_रेजिस्टर_load(tb[NFTA_TPROXY_REG_ADDR],
					      &priv->sreg_addr, alen);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (tb[NFTA_TPROXY_REG_PORT]) अणु
		err = nft_parse_रेजिस्टर_load(tb[NFTA_TPROXY_REG_PORT],
					      &priv->sreg_port, माप(u16));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nft_tproxy_destroy(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_tproxy *priv = nft_expr_priv(expr);

	चयन (priv->family) अणु
	हाल NFPROTO_IPV4:
		nf_defrag_ipv4_disable(ctx->net);
		अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
		nf_defrag_ipv6_disable(ctx->net);
		अवरोध;
#पूर्ण_अगर
	हाल NFPROTO_UNSPEC:
		nf_defrag_ipv4_disable(ctx->net);
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
		nf_defrag_ipv6_disable(ctx->net);
#पूर्ण_अगर
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक nft_tproxy_dump(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_tproxy *priv = nft_expr_priv(expr);

	अगर (nla_put_be32(skb, NFTA_TPROXY_FAMILY, htonl(priv->family)))
		वापस -1;

	अगर (priv->sreg_addr &&
	    nft_dump_रेजिस्टर(skb, NFTA_TPROXY_REG_ADDR, priv->sreg_addr))
		वापस -1;

	अगर (priv->sreg_port &&
	    nft_dump_रेजिस्टर(skb, NFTA_TPROXY_REG_PORT, priv->sreg_port))
			वापस -1;

	वापस 0;
पूर्ण

अटल काष्ठा nft_expr_type nft_tproxy_type;
अटल स्थिर काष्ठा nft_expr_ops nft_tproxy_ops = अणु
	.type		= &nft_tproxy_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_tproxy)),
	.eval		= nft_tproxy_eval,
	.init		= nft_tproxy_init,
	.destroy	= nft_tproxy_destroy,
	.dump		= nft_tproxy_dump,
पूर्ण;

अटल काष्ठा nft_expr_type nft_tproxy_type __पढ़ो_mostly = अणु
	.name		= "tproxy",
	.ops		= &nft_tproxy_ops,
	.policy		= nft_tproxy_policy,
	.maxattr	= NFTA_TPROXY_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_tproxy_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_tproxy_type);
पूर्ण

अटल व्योम __निकास nft_tproxy_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_tproxy_type);
पूर्ण

module_init(nft_tproxy_module_init);
module_निकास(nft_tproxy_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mथँtथऊ Eckl");
MODULE_DESCRIPTION("nf_tables tproxy support module");
MODULE_ALIAS_NFT_EXPR("tproxy");
