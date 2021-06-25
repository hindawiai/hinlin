<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <net/ip.h>
#समावेश <net/tcp.h>
#समावेश <net/netlink.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_conntrack.h>
#समावेश <net/netfilter/nf_conntrack_synproxy.h>
#समावेश <net/netfilter/nf_synproxy.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <linux/netfilter/nf_synproxy.h>

काष्ठा nft_synproxy अणु
	काष्ठा nf_synproxy_info	info;
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_synproxy_policy[NFTA_SYNPROXY_MAX + 1] = अणु
	[NFTA_SYNPROXY_MSS]		= अणु .type = NLA_U16 पूर्ण,
	[NFTA_SYNPROXY_WSCALE]		= अणु .type = NLA_U8 पूर्ण,
	[NFTA_SYNPROXY_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल व्योम nft_synproxy_tcp_options(काष्ठा synproxy_options *opts,
				     स्थिर काष्ठा tcphdr *tcp,
				     काष्ठा synproxy_net *snet,
				     काष्ठा nf_synproxy_info *info,
				     स्थिर काष्ठा nft_synproxy *priv)
अणु
	this_cpu_inc(snet->stats->syn_received);
	अगर (tcp->ece && tcp->cwr)
		opts->options |= NF_SYNPROXY_OPT_ECN;

	opts->options &= priv->info.options;
	opts->mss_encode = opts->mss_option;
	opts->mss_option = info->mss;
	अगर (opts->options & NF_SYNPROXY_OPT_TIMESTAMP)
		synproxy_init_बारtamp_cookie(info, opts);
	अन्यथा
		opts->options &= ~(NF_SYNPROXY_OPT_WSCALE |
				   NF_SYNPROXY_OPT_SACK_PERM |
				   NF_SYNPROXY_OPT_ECN);
पूर्ण

अटल व्योम nft_synproxy_eval_v4(स्थिर काष्ठा nft_synproxy *priv,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt,
				 स्थिर काष्ठा tcphdr *tcp,
				 काष्ठा tcphdr *_tcph,
				 काष्ठा synproxy_options *opts)
अणु
	काष्ठा nf_synproxy_info info = priv->info;
	काष्ठा net *net = nft_net(pkt);
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	काष्ठा sk_buff *skb = pkt->skb;

	अगर (tcp->syn) अणु
		/* Initial SYN from client */
		nft_synproxy_tcp_options(opts, tcp, snet, &info, priv);
		synproxy_send_client_synack(net, skb, tcp, opts);
		consume_skb(skb);
		regs->verdict.code = NF_STOLEN;
	पूर्ण अन्यथा अगर (tcp->ack) अणु
		/* ACK from client */
		अगर (synproxy_recv_client_ack(net, skb, tcp, opts,
					     ntohl(tcp->seq))) अणु
			consume_skb(skb);
			regs->verdict.code = NF_STOLEN;
		पूर्ण अन्यथा अणु
			regs->verdict.code = NF_DROP;
		पूर्ण
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
अटल व्योम nft_synproxy_eval_v6(स्थिर काष्ठा nft_synproxy *priv,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt,
				 स्थिर काष्ठा tcphdr *tcp,
				 काष्ठा tcphdr *_tcph,
				 काष्ठा synproxy_options *opts)
अणु
	काष्ठा nf_synproxy_info info = priv->info;
	काष्ठा net *net = nft_net(pkt);
	काष्ठा synproxy_net *snet = synproxy_pernet(net);
	काष्ठा sk_buff *skb = pkt->skb;

	अगर (tcp->syn) अणु
		/* Initial SYN from client */
		nft_synproxy_tcp_options(opts, tcp, snet, &info, priv);
		synproxy_send_client_synack_ipv6(net, skb, tcp, opts);
		consume_skb(skb);
		regs->verdict.code = NF_STOLEN;
	पूर्ण अन्यथा अगर (tcp->ack) अणु
		/* ACK from client */
		अगर (synproxy_recv_client_ack_ipv6(net, skb, tcp, opts,
						  ntohl(tcp->seq))) अणु
			consume_skb(skb);
			regs->verdict.code = NF_STOLEN;
		पूर्ण अन्यथा अणु
			regs->verdict.code = NF_DROP;
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_NF_TABLES_IPV6*/

अटल व्योम nft_synproxy_करो_eval(स्थिर काष्ठा nft_synproxy *priv,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा synproxy_options opts = अणुपूर्ण;
	काष्ठा sk_buff *skb = pkt->skb;
	पूर्णांक thoff = pkt->xt.thoff;
	स्थिर काष्ठा tcphdr *tcp;
	काष्ठा tcphdr _tcph;

	अगर (pkt->tprot != IPPROTO_TCP) अणु
		regs->verdict.code = NFT_BREAK;
		वापस;
	पूर्ण

	अगर (nf_ip_checksum(skb, nft_hook(pkt), thoff, IPPROTO_TCP)) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण

	tcp = skb_header_poपूर्णांकer(skb, pkt->xt.thoff,
				 माप(काष्ठा tcphdr),
				 &_tcph);
	अगर (!tcp) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण

	अगर (!synproxy_parse_options(skb, thoff, tcp, &opts)) अणु
		regs->verdict.code = NF_DROP;
		वापस;
	पूर्ण

	चयन (skb->protocol) अणु
	हाल htons(ETH_P_IP):
		nft_synproxy_eval_v4(priv, regs, pkt, tcp, &_tcph, &opts);
		वापस;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल htons(ETH_P_IPV6):
		nft_synproxy_eval_v6(priv, regs, pkt, tcp, &_tcph, &opts);
		वापस;
#पूर्ण_अगर
	पूर्ण
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल पूर्णांक nft_synproxy_करो_init(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nlattr * स्थिर tb[],
				काष्ठा nft_synproxy *priv)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(ctx->net);
	u32 flags;
	पूर्णांक err;

	अगर (tb[NFTA_SYNPROXY_MSS])
		priv->info.mss = ntohs(nla_get_be16(tb[NFTA_SYNPROXY_MSS]));
	अगर (tb[NFTA_SYNPROXY_WSCALE])
		priv->info.wscale = nla_get_u8(tb[NFTA_SYNPROXY_WSCALE]);
	अगर (tb[NFTA_SYNPROXY_FLAGS]) अणु
		flags = ntohl(nla_get_be32(tb[NFTA_SYNPROXY_FLAGS]));
		अगर (flags & ~NF_SYNPROXY_OPT_MASK)
			वापस -EOPNOTSUPP;
		priv->info.options = flags;
	पूर्ण

	err = nf_ct_netns_get(ctx->net, ctx->family);
	अगर (err)
		वापस err;

	चयन (ctx->family) अणु
	हाल NFPROTO_IPV4:
		err = nf_synproxy_ipv4_init(snet, ctx->net);
		अगर (err)
			जाओ nf_ct_failure;
		अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
		err = nf_synproxy_ipv6_init(snet, ctx->net);
		अगर (err)
			जाओ nf_ct_failure;
		अवरोध;
#पूर्ण_अगर
	हाल NFPROTO_INET:
	हाल NFPROTO_BRIDGE:
		err = nf_synproxy_ipv4_init(snet, ctx->net);
		अगर (err)
			जाओ nf_ct_failure;
		err = nf_synproxy_ipv6_init(snet, ctx->net);
		अगर (err)
			जाओ nf_ct_failure;
		अवरोध;
	पूर्ण

	वापस 0;

nf_ct_failure:
	nf_ct_netns_put(ctx->net, ctx->family);
	वापस err;
पूर्ण

अटल व्योम nft_synproxy_करो_destroy(स्थिर काष्ठा nft_ctx *ctx)
अणु
	काष्ठा synproxy_net *snet = synproxy_pernet(ctx->net);

	चयन (ctx->family) अणु
	हाल NFPROTO_IPV4:
		nf_synproxy_ipv4_fini(snet, ctx->net);
		अवरोध;
#अगर IS_ENABLED(CONFIG_NF_TABLES_IPV6)
	हाल NFPROTO_IPV6:
		nf_synproxy_ipv6_fini(snet, ctx->net);
		अवरोध;
#पूर्ण_अगर
	हाल NFPROTO_INET:
	हाल NFPROTO_BRIDGE:
		nf_synproxy_ipv4_fini(snet, ctx->net);
		nf_synproxy_ipv6_fini(snet, ctx->net);
		अवरोध;
	पूर्ण
	nf_ct_netns_put(ctx->net, ctx->family);
पूर्ण

अटल पूर्णांक nft_synproxy_करो_dump(काष्ठा sk_buff *skb, काष्ठा nft_synproxy *priv)
अणु
	अगर (nla_put_be16(skb, NFTA_SYNPROXY_MSS, htons(priv->info.mss)) ||
	    nla_put_u8(skb, NFTA_SYNPROXY_WSCALE, priv->info.wscale) ||
	    nla_put_be32(skb, NFTA_SYNPROXY_FLAGS, htonl(priv->info.options)))
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल व्योम nft_synproxy_eval(स्थिर काष्ठा nft_expr *expr,
			      काष्ठा nft_regs *regs,
			      स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_synproxy *priv = nft_expr_priv(expr);

	nft_synproxy_करो_eval(priv, regs, pkt);
पूर्ण

अटल पूर्णांक nft_synproxy_validate(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_expr *expr,
				 स्थिर काष्ठा nft_data **data)
अणु
	वापस nft_chain_validate_hooks(ctx->chain, (1 << NF_INET_LOCAL_IN) |
						    (1 << NF_INET_FORWARD));
पूर्ण

अटल पूर्णांक nft_synproxy_init(स्थिर काष्ठा nft_ctx *ctx,
			     स्थिर काष्ठा nft_expr *expr,
			     स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_synproxy *priv = nft_expr_priv(expr);

	वापस nft_synproxy_करो_init(ctx, tb, priv);
पूर्ण

अटल व्योम nft_synproxy_destroy(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nft_expr *expr)
अणु
	nft_synproxy_करो_destroy(ctx);
पूर्ण

अटल पूर्णांक nft_synproxy_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_synproxy *priv = nft_expr_priv(expr);

	वापस nft_synproxy_करो_dump(skb, priv);
पूर्ण

अटल काष्ठा nft_expr_type nft_synproxy_type;
अटल स्थिर काष्ठा nft_expr_ops nft_synproxy_ops = अणु
	.eval		= nft_synproxy_eval,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_synproxy)),
	.init		= nft_synproxy_init,
	.destroy	= nft_synproxy_destroy,
	.dump		= nft_synproxy_dump,
	.type		= &nft_synproxy_type,
	.validate	= nft_synproxy_validate,
पूर्ण;

अटल काष्ठा nft_expr_type nft_synproxy_type __पढ़ो_mostly = अणु
	.ops		= &nft_synproxy_ops,
	.name		= "synproxy",
	.owner		= THIS_MODULE,
	.policy		= nft_synproxy_policy,
	.maxattr	= NFTA_SYNPROXY_MAX,
पूर्ण;

अटल पूर्णांक nft_synproxy_obj_init(स्थिर काष्ठा nft_ctx *ctx,
				 स्थिर काष्ठा nlattr * स्थिर tb[],
				 काष्ठा nft_object *obj)
अणु
	काष्ठा nft_synproxy *priv = nft_obj_data(obj);

	वापस nft_synproxy_करो_init(ctx, tb, priv);
पूर्ण

अटल व्योम nft_synproxy_obj_destroy(स्थिर काष्ठा nft_ctx *ctx,
				     काष्ठा nft_object *obj)
अणु
	nft_synproxy_करो_destroy(ctx);
पूर्ण

अटल पूर्णांक nft_synproxy_obj_dump(काष्ठा sk_buff *skb,
				 काष्ठा nft_object *obj, bool reset)
अणु
	काष्ठा nft_synproxy *priv = nft_obj_data(obj);

	वापस nft_synproxy_करो_dump(skb, priv);
पूर्ण

अटल व्योम nft_synproxy_obj_eval(काष्ठा nft_object *obj,
				  काष्ठा nft_regs *regs,
				  स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_synproxy *priv = nft_obj_data(obj);

	nft_synproxy_करो_eval(priv, regs, pkt);
पूर्ण

अटल व्योम nft_synproxy_obj_update(काष्ठा nft_object *obj,
				    काष्ठा nft_object *newobj)
अणु
	काष्ठा nft_synproxy *newpriv = nft_obj_data(newobj);
	काष्ठा nft_synproxy *priv = nft_obj_data(obj);

	priv->info = newpriv->info;
पूर्ण

अटल काष्ठा nft_object_type nft_synproxy_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_synproxy_obj_ops = अणु
	.type		= &nft_synproxy_obj_type,
	.size		= माप(काष्ठा nft_synproxy),
	.init		= nft_synproxy_obj_init,
	.destroy	= nft_synproxy_obj_destroy,
	.dump		= nft_synproxy_obj_dump,
	.eval		= nft_synproxy_obj_eval,
	.update		= nft_synproxy_obj_update,
पूर्ण;

अटल काष्ठा nft_object_type nft_synproxy_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_SYNPROXY,
	.ops		= &nft_synproxy_obj_ops,
	.maxattr	= NFTA_SYNPROXY_MAX,
	.policy		= nft_synproxy_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_synproxy_module_init(व्योम)
अणु
	पूर्णांक err;

	err = nft_रेजिस्टर_obj(&nft_synproxy_obj_type);
	अगर (err < 0)
		वापस err;

	err = nft_रेजिस्टर_expr(&nft_synproxy_type);
	अगर (err < 0)
		जाओ err;

	वापस 0;

err:
	nft_unरेजिस्टर_obj(&nft_synproxy_obj_type);
	वापस err;
पूर्ण

अटल व्योम __निकास nft_synproxy_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_synproxy_type);
	nft_unरेजिस्टर_obj(&nft_synproxy_obj_type);
पूर्ण

module_init(nft_synproxy_module_init);
module_निकास(nft_synproxy_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fernando Fernandez <ffmancera@riseup.net>");
MODULE_ALIAS_NFT_EXPR("synproxy");
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_SYNPROXY);
MODULE_DESCRIPTION("nftables SYNPROXY expression support");
