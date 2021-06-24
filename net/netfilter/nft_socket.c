<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/module.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_socket.h>
#समावेश <net/inet_sock.h>
#समावेश <net/tcp.h>

काष्ठा nft_socket अणु
	क्रमागत nft_socket_keys		key:8;
	u8				level;
	जोड़ अणु
		u8			dreg;
	पूर्ण;
पूर्ण;

अटल व्योम nft_socket_wildcard(स्थिर काष्ठा nft_pktinfo *pkt,
				काष्ठा nft_regs *regs, काष्ठा sock *sk,
				u32 *dest)
अणु
	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_IPV4:
		nft_reg_store8(dest, inet_sk(sk)->inet_rcv_saddr == 0);
		अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
		nft_reg_store8(dest, ipv6_addr_any(&sk->sk_v6_rcv_saddr));
		अवरोध;
#पूर्ण_अगर
	शेष:
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
अटल noअंतरभूत bool
nft_sock_get_eval_cgroupv2(u32 *dest, स्थिर काष्ठा nft_pktinfo *pkt, u32 level)
अणु
	काष्ठा sock *sk = skb_to_full_sk(pkt->skb);
	काष्ठा cgroup *cgrp;

	अगर (!sk || !sk_fullsock(sk) || !net_eq(nft_net(pkt), sock_net(sk)))
		वापस false;

	cgrp = sock_cgroup_ptr(&sk->sk_cgrp_data);
	अगर (level > cgrp->level)
		वापस false;

	स_नकल(dest, &cgrp->ancestor_ids[level], माप(u64));

	वापस true;
पूर्ण
#पूर्ण_अगर

अटल व्योम nft_socket_eval(स्थिर काष्ठा nft_expr *expr,
			    काष्ठा nft_regs *regs,
			    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_socket *priv = nft_expr_priv(expr);
	काष्ठा sk_buff *skb = pkt->skb;
	काष्ठा sock *sk = skb->sk;
	u32 *dest = &regs->data[priv->dreg];

	अगर (sk && !net_eq(nft_net(pkt), sock_net(sk)))
		sk = शून्य;

	अगर (!sk)
		चयन(nft_pf(pkt)) अणु
		हाल NFPROTO_IPV4:
			sk = nf_sk_lookup_slow_v4(nft_net(pkt), skb, nft_in(pkt));
			अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
		हाल NFPROTO_IPV6:
			sk = nf_sk_lookup_slow_v6(nft_net(pkt), skb, nft_in(pkt));
			अवरोध;
#पूर्ण_अगर
		शेष:
			WARN_ON_ONCE(1);
			regs->verdict.code = NFT_BREAK;
			वापस;
		पूर्ण

	अगर (!sk) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	चयन(priv->key) अणु
	हाल NFT_SOCKET_TRANSPARENT:
		nft_reg_store8(dest, inet_sk_transparent(sk));
		अवरोध;
	हाल NFT_SOCKET_MARK:
		अगर (sk_fullsock(sk)) अणु
			*dest = sk->sk_mark;
		पूर्ण अन्यथा अणु
			regs->verdict.code = NFT_BREAK;
			वापस;
		पूर्ण
		अवरोध;
	हाल NFT_SOCKET_WILDCARD:
		अगर (!sk_fullsock(sk)) अणु
			regs->verdict.code = NFT_BREAK;
			वापस;
		पूर्ण
		nft_socket_wildcard(pkt, regs, sk, dest);
		अवरोध;
#अगर_घोषित CONFIG_SOCK_CGROUP_DATA
	हाल NFT_SOCKET_CGROUPV2:
		अगर (!nft_sock_get_eval_cgroupv2(dest, pkt, priv->level)) अणु
			regs->verdict.code = NFT_BREAK;
			वापस;
		पूर्ण
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON(1);
		regs->verdict.code = NFT_BREAK;
	पूर्ण

	अगर (sk != skb->sk)
		sock_gen_put(sk);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_socket_policy[NFTA_SOCKET_MAX + 1] = अणु
	[NFTA_SOCKET_KEY]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SOCKET_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_SOCKET_LEVEL]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_socket_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_socket *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;

	अगर (!tb[NFTA_SOCKET_DREG] || !tb[NFTA_SOCKET_KEY])
		वापस -EINVAL;

	चयन(ctx->family) अणु
	हाल NFPROTO_IPV4:
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
#पूर्ण_अगर
	हाल NFPROTO_INET:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->key = ntohl(nla_get_u32(tb[NFTA_SOCKET_KEY]));
	चयन(priv->key) अणु
	हाल NFT_SOCKET_TRANSPARENT:
	हाल NFT_SOCKET_WILDCARD:
		len = माप(u8);
		अवरोध;
	हाल NFT_SOCKET_MARK:
		len = माप(u32);
		अवरोध;
#अगर_घोषित CONFIG_CGROUPS
	हाल NFT_SOCKET_CGROUPV2: अणु
		अचिन्हित पूर्णांक level;

		अगर (!tb[NFTA_SOCKET_LEVEL])
			वापस -EINVAL;

		level = ntohl(nla_get_u32(tb[NFTA_SOCKET_LEVEL]));
		अगर (level > 255)
			वापस -EOPNOTSUPP;

		priv->level = level;
		len = माप(u64);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_SOCKET_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, len);
पूर्ण

अटल पूर्णांक nft_socket_dump(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_socket *priv = nft_expr_priv(expr);

	अगर (nla_put_u32(skb, NFTA_SOCKET_KEY, htonl(priv->key)))
		वापस -1;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_SOCKET_DREG, priv->dreg))
		वापस -1;
	अगर (priv->key == NFT_SOCKET_CGROUPV2 &&
	    nla_put_u32(skb, NFTA_SOCKET_LEVEL, htonl(priv->level)))
		वापस -1;
	वापस 0;
पूर्ण

अटल काष्ठा nft_expr_type nft_socket_type;
अटल स्थिर काष्ठा nft_expr_ops nft_socket_ops = अणु
	.type		= &nft_socket_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_socket)),
	.eval		= nft_socket_eval,
	.init		= nft_socket_init,
	.dump		= nft_socket_dump,
पूर्ण;

अटल काष्ठा nft_expr_type nft_socket_type __पढ़ो_mostly = अणु
	.name		= "socket",
	.ops		= &nft_socket_ops,
	.policy		= nft_socket_policy,
	.maxattr	= NFTA_SOCKET_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_socket_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_socket_type);
पूर्ण

अटल व्योम __निकास nft_socket_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_socket_type);
पूर्ण

module_init(nft_socket_module_init);
module_निकास(nft_socket_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mथँtथऊ Eckl");
MODULE_DESCRIPTION("nf_tables socket match module");
MODULE_ALIAS_NFT_EXPR("socket");
