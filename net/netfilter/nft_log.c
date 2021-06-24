<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 * Copyright (c) 2012-2014 Pablo Neira Ayuso <pablo@netfilter.org>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <linux/audit.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/ipv6.h>
#समावेश <net/ip.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_log.h>
#समावेश <linux/netdevice.h>

अटल स्थिर अक्षर *nft_log_null_prefix = "";

काष्ठा nft_log अणु
	काष्ठा nf_loginfo	loginfo;
	अक्षर			*prefix;
पूर्ण;

अटल bool audit_ip4(काष्ठा audit_buffer *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr _iph;
	स्थिर काष्ठा iphdr *ih;

	ih = skb_header_poपूर्णांकer(skb, skb_network_offset(skb), माप(_iph), &_iph);
	अगर (!ih)
		वापस false;

	audit_log_क्रमmat(ab, " saddr=%pI4 daddr=%pI4 proto=%hhu",
			 &ih->saddr, &ih->daddr, ih->protocol);

	वापस true;
पूर्ण

अटल bool audit_ip6(काष्ठा audit_buffer *ab, काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr _ip6h;
	स्थिर काष्ठा ipv6hdr *ih;
	u8 nexthdr;
	__be16 frag_off;

	ih = skb_header_poपूर्णांकer(skb, skb_network_offset(skb), माप(_ip6h), &_ip6h);
	अगर (!ih)
		वापस false;

	nexthdr = ih->nexthdr;
	ipv6_skip_exthdr(skb, skb_network_offset(skb) + माप(_ip6h), &nexthdr, &frag_off);

	audit_log_क्रमmat(ab, " saddr=%pI6c daddr=%pI6c proto=%hhu",
			 &ih->saddr, &ih->daddr, nexthdr);

	वापस true;
पूर्ण

अटल व्योम nft_log_eval_audit(स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा sk_buff *skb = pkt->skb;
	काष्ठा audit_buffer *ab;
	पूर्णांक fam = -1;

	अगर (!audit_enabled)
		वापस;

	ab = audit_log_start(शून्य, GFP_ATOMIC, AUDIT_NETFILTER_PKT);
	अगर (!ab)
		वापस;

	audit_log_क्रमmat(ab, "mark=%#x", skb->mark);

	चयन (nft_pf(pkt)) अणु
	हाल NFPROTO_BRIDGE:
		चयन (eth_hdr(skb)->h_proto) अणु
		हाल htons(ETH_P_IP):
			fam = audit_ip4(ab, skb) ? NFPROTO_IPV4 : -1;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			fam = audit_ip6(ab, skb) ? NFPROTO_IPV6 : -1;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल NFPROTO_IPV4:
		fam = audit_ip4(ab, skb) ? NFPROTO_IPV4 : -1;
		अवरोध;
	हाल NFPROTO_IPV6:
		fam = audit_ip6(ab, skb) ? NFPROTO_IPV6 : -1;
		अवरोध;
	पूर्ण

	अगर (fam == -1)
		audit_log_क्रमmat(ab, " saddr=? daddr=? proto=-1");

	audit_log_end(ab);
पूर्ण

अटल व्योम nft_log_eval(स्थिर काष्ठा nft_expr *expr,
			 काष्ठा nft_regs *regs,
			 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_log *priv = nft_expr_priv(expr);

	अगर (priv->loginfo.type == NF_LOG_TYPE_LOG &&
	    priv->loginfo.u.log.level == NFT_LOGLEVEL_AUDIT) अणु
		nft_log_eval_audit(pkt);
		वापस;
	पूर्ण

	nf_log_packet(nft_net(pkt), nft_pf(pkt), nft_hook(pkt), pkt->skb,
		      nft_in(pkt), nft_out(pkt), &priv->loginfo, "%s",
		      priv->prefix);
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_log_policy[NFTA_LOG_MAX + 1] = अणु
	[NFTA_LOG_GROUP]	= अणु .type = NLA_U16 पूर्ण,
	[NFTA_LOG_PREFIX]	= अणु .type = NLA_STRING,
				    .len = NF_LOG_PREFIXLEN - 1 पूर्ण,
	[NFTA_LOG_SNAPLEN]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_LOG_QTHRESHOLD]	= अणु .type = NLA_U16 पूर्ण,
	[NFTA_LOG_LEVEL]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_LOG_FLAGS]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_log_modprobe(काष्ठा net *net, क्रमागत nf_log_type t)
अणु
	चयन (t) अणु
	हाल NF_LOG_TYPE_LOG:
		वापस nft_request_module(net, "%s", "nf_log_syslog");
	हाल NF_LOG_TYPE_ULOG:
		वापस nft_request_module(net, "%s", "nfnetlink_log");
	हाल NF_LOG_TYPE_MAX:
		अवरोध;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक nft_log_init(स्थिर काष्ठा nft_ctx *ctx,
			स्थिर काष्ठा nft_expr *expr,
			स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_log *priv = nft_expr_priv(expr);
	काष्ठा nf_loginfo *li = &priv->loginfo;
	स्थिर काष्ठा nlattr *nla;
	पूर्णांक err;

	li->type = NF_LOG_TYPE_LOG;
	अगर (tb[NFTA_LOG_LEVEL] != शून्य &&
	    tb[NFTA_LOG_GROUP] != शून्य)
		वापस -EINVAL;
	अगर (tb[NFTA_LOG_GROUP] != शून्य) अणु
		li->type = NF_LOG_TYPE_ULOG;
		अगर (tb[NFTA_LOG_FLAGS] != शून्य)
			वापस -EINVAL;
	पूर्ण

	nla = tb[NFTA_LOG_PREFIX];
	अगर (nla != शून्य) अणु
		priv->prefix = kदो_स्मृति(nla_len(nla) + 1, GFP_KERNEL);
		अगर (priv->prefix == शून्य)
			वापस -ENOMEM;
		nla_strscpy(priv->prefix, nla, nla_len(nla) + 1);
	पूर्ण अन्यथा अणु
		priv->prefix = (अक्षर *)nft_log_null_prefix;
	पूर्ण

	चयन (li->type) अणु
	हाल NF_LOG_TYPE_LOG:
		अगर (tb[NFTA_LOG_LEVEL] != शून्य) अणु
			li->u.log.level =
				ntohl(nla_get_be32(tb[NFTA_LOG_LEVEL]));
		पूर्ण अन्यथा अणु
			li->u.log.level = NFT_LOGLEVEL_WARNING;
		पूर्ण
		अगर (li->u.log.level > NFT_LOGLEVEL_AUDIT) अणु
			err = -EINVAL;
			जाओ err1;
		पूर्ण

		अगर (tb[NFTA_LOG_FLAGS] != शून्य) अणु
			li->u.log.logflags =
				ntohl(nla_get_be32(tb[NFTA_LOG_FLAGS]));
			अगर (li->u.log.logflags & ~NF_LOG_MASK) अणु
				err = -EINVAL;
				जाओ err1;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NF_LOG_TYPE_ULOG:
		li->u.ulog.group = ntohs(nla_get_be16(tb[NFTA_LOG_GROUP]));
		अगर (tb[NFTA_LOG_SNAPLEN] != शून्य) अणु
			li->u.ulog.flags |= NF_LOG_F_COPY_LEN;
			li->u.ulog.copy_len =
				ntohl(nla_get_be32(tb[NFTA_LOG_SNAPLEN]));
		पूर्ण
		अगर (tb[NFTA_LOG_QTHRESHOLD] != शून्य) अणु
			li->u.ulog.qthreshold =
				ntohs(nla_get_be16(tb[NFTA_LOG_QTHRESHOLD]));
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (li->u.log.level == NFT_LOGLEVEL_AUDIT)
		वापस 0;

	err = nf_logger_find_get(ctx->family, li->type);
	अगर (err < 0) अणु
		अगर (nft_log_modprobe(ctx->net, li->type) == -EAGAIN)
			err = -EAGAIN;

		जाओ err1;
	पूर्ण

	वापस 0;

err1:
	अगर (priv->prefix != nft_log_null_prefix)
		kमुक्त(priv->prefix);
	वापस err;
पूर्ण

अटल व्योम nft_log_destroy(स्थिर काष्ठा nft_ctx *ctx,
			    स्थिर काष्ठा nft_expr *expr)
अणु
	काष्ठा nft_log *priv = nft_expr_priv(expr);
	काष्ठा nf_loginfo *li = &priv->loginfo;

	अगर (priv->prefix != nft_log_null_prefix)
		kमुक्त(priv->prefix);

	अगर (li->u.log.level == NFT_LOGLEVEL_AUDIT)
		वापस;

	nf_logger_put(ctx->family, li->type);
पूर्ण

अटल पूर्णांक nft_log_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_log *priv = nft_expr_priv(expr);
	स्थिर काष्ठा nf_loginfo *li = &priv->loginfo;

	अगर (priv->prefix != nft_log_null_prefix)
		अगर (nla_put_string(skb, NFTA_LOG_PREFIX, priv->prefix))
			जाओ nla_put_failure;
	चयन (li->type) अणु
	हाल NF_LOG_TYPE_LOG:
		अगर (nla_put_be32(skb, NFTA_LOG_LEVEL, htonl(li->u.log.level)))
			जाओ nla_put_failure;

		अगर (li->u.log.logflags) अणु
			अगर (nla_put_be32(skb, NFTA_LOG_FLAGS,
					 htonl(li->u.log.logflags)))
				जाओ nla_put_failure;
		पूर्ण
		अवरोध;
	हाल NF_LOG_TYPE_ULOG:
		अगर (nla_put_be16(skb, NFTA_LOG_GROUP, htons(li->u.ulog.group)))
			जाओ nla_put_failure;

		अगर (li->u.ulog.flags & NF_LOG_F_COPY_LEN) अणु
			अगर (nla_put_be32(skb, NFTA_LOG_SNAPLEN,
					 htonl(li->u.ulog.copy_len)))
				जाओ nla_put_failure;
		पूर्ण
		अगर (li->u.ulog.qthreshold) अणु
			अगर (nla_put_be16(skb, NFTA_LOG_QTHRESHOLD,
					 htons(li->u.ulog.qthreshold)))
				जाओ nla_put_failure;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा nft_expr_type nft_log_type;
अटल स्थिर काष्ठा nft_expr_ops nft_log_ops = अणु
	.type		= &nft_log_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_log)),
	.eval		= nft_log_eval,
	.init		= nft_log_init,
	.destroy	= nft_log_destroy,
	.dump		= nft_log_dump,
पूर्ण;

अटल काष्ठा nft_expr_type nft_log_type __पढ़ो_mostly = अणु
	.name		= "log",
	.ops		= &nft_log_ops,
	.policy		= nft_log_policy,
	.maxattr	= NFTA_LOG_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_log_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_log_type);
पूर्ण

अटल व्योम __निकास nft_log_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_log_type);
पूर्ण

module_init(nft_log_module_init);
module_निकास(nft_log_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick McHardy <kaber@trash.net>");
MODULE_ALIAS_NFT_EXPR("log");
MODULE_DESCRIPTION("Netfilter nf_tables log module");
