<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/tcp.h>

काष्ठा nft_exthdr अणु
	u8			type;
	u8			offset;
	u8			len;
	u8			op;
	u8			dreg;
	u8			sreg;
	u8			flags;
पूर्ण;

अटल अचिन्हित पूर्णांक optlen(स्थिर u8 *opt, अचिन्हित पूर्णांक offset)
अणु
	/* Beware zero-length options: make finite progress */
	अगर (opt[offset] <= TCPOPT_NOP || opt[offset + 1] == 0)
		वापस 1;
	अन्यथा
		वापस opt[offset + 1];
पूर्ण

अटल व्योम nft_exthdr_ipv6_eval(स्थिर काष्ठा nft_expr *expr,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_exthdr *priv = nft_expr_priv(expr);
	u32 *dest = &regs->data[priv->dreg];
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक err;

	err = ipv6_find_hdr(pkt->skb, &offset, priv->type, शून्य, शून्य);
	अगर (priv->flags & NFT_EXTHDR_F_PRESENT) अणु
		nft_reg_store8(dest, err >= 0);
		वापस;
	पूर्ण अन्यथा अगर (err < 0) अणु
		जाओ err;
	पूर्ण
	offset += priv->offset;

	dest[priv->len / NFT_REG32_SIZE] = 0;
	अगर (skb_copy_bits(pkt->skb, offset, dest, priv->len) < 0)
		जाओ err;
	वापस;
err:
	regs->verdict.code = NFT_BREAK;
पूर्ण

/* find the offset to specअगरied option.
 *
 * If target header is found, its offset is set in *offset and वापस option
 * number. Otherwise, वापस negative error.
 *
 * If the first fragment करोesn't contain the End of Options it is considered
 * invalid.
 */
अटल पूर्णांक ipv4_find_option(काष्ठा net *net, काष्ठा sk_buff *skb,
			    अचिन्हित पूर्णांक *offset, पूर्णांक target)
अणु
	अचिन्हित अक्षर optbuf[माप(काष्ठा ip_options) + 40];
	काष्ठा ip_options *opt = (काष्ठा ip_options *)optbuf;
	काष्ठा iphdr *iph, _iph;
	अचिन्हित पूर्णांक start;
	bool found = false;
	__be32 info;
	पूर्णांक optlen;

	iph = skb_header_poपूर्णांकer(skb, 0, माप(_iph), &_iph);
	अगर (!iph)
		वापस -EBADMSG;
	start = माप(काष्ठा iphdr);

	optlen = iph->ihl * 4 - (पूर्णांक)माप(काष्ठा iphdr);
	अगर (optlen <= 0)
		वापस -ENOENT;

	स_रखो(opt, 0, माप(काष्ठा ip_options));
	/* Copy the options since __ip_options_compile() modअगरies
	 * the options.
	 */
	अगर (skb_copy_bits(skb, start, opt->__data, optlen))
		वापस -EBADMSG;
	opt->optlen = optlen;

	अगर (__ip_options_compile(net, opt, शून्य, &info))
		वापस -EBADMSG;

	चयन (target) अणु
	हाल IPOPT_SSRR:
	हाल IPOPT_LSRR:
		अगर (!opt->srr)
			अवरोध;
		found = target == IPOPT_SSRR ? opt->is_strictroute :
					       !opt->is_strictroute;
		अगर (found)
			*offset = opt->srr + start;
		अवरोध;
	हाल IPOPT_RR:
		अगर (!opt->rr)
			अवरोध;
		*offset = opt->rr + start;
		found = true;
		अवरोध;
	हाल IPOPT_RA:
		अगर (!opt->router_alert)
			अवरोध;
		*offset = opt->router_alert + start;
		found = true;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस found ? target : -ENOENT;
पूर्ण

अटल व्योम nft_exthdr_ipv4_eval(स्थिर काष्ठा nft_expr *expr,
				 काष्ठा nft_regs *regs,
				 स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_exthdr *priv = nft_expr_priv(expr);
	u32 *dest = &regs->data[priv->dreg];
	काष्ठा sk_buff *skb = pkt->skb;
	अचिन्हित पूर्णांक offset;
	पूर्णांक err;

	अगर (skb->protocol != htons(ETH_P_IP))
		जाओ err;

	err = ipv4_find_option(nft_net(pkt), skb, &offset, priv->type);
	अगर (priv->flags & NFT_EXTHDR_F_PRESENT) अणु
		nft_reg_store8(dest, err >= 0);
		वापस;
	पूर्ण अन्यथा अगर (err < 0) अणु
		जाओ err;
	पूर्ण
	offset += priv->offset;

	dest[priv->len / NFT_REG32_SIZE] = 0;
	अगर (skb_copy_bits(pkt->skb, offset, dest, priv->len) < 0)
		जाओ err;
	वापस;
err:
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल व्योम *
nft_tcp_header_poपूर्णांकer(स्थिर काष्ठा nft_pktinfo *pkt,
		       अचिन्हित पूर्णांक len, व्योम *buffer, अचिन्हित पूर्णांक *tcphdr_len)
अणु
	काष्ठा tcphdr *tcph;

	अगर (!pkt->tprot_set || pkt->tprot != IPPROTO_TCP)
		वापस शून्य;

	tcph = skb_header_poपूर्णांकer(pkt->skb, pkt->xt.thoff, माप(*tcph), buffer);
	अगर (!tcph)
		वापस शून्य;

	*tcphdr_len = __tcp_hdrlen(tcph);
	अगर (*tcphdr_len < माप(*tcph) || *tcphdr_len > len)
		वापस शून्य;

	वापस skb_header_poपूर्णांकer(pkt->skb, pkt->xt.thoff, *tcphdr_len, buffer);
पूर्ण

अटल व्योम nft_exthdr_tcp_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	u8 buff[माप(काष्ठा tcphdr) + MAX_TCP_OPTION_SPACE];
	काष्ठा nft_exthdr *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक i, optl, tcphdr_len, offset;
	u32 *dest = &regs->data[priv->dreg];
	काष्ठा tcphdr *tcph;
	u8 *opt;

	tcph = nft_tcp_header_poपूर्णांकer(pkt, माप(buff), buff, &tcphdr_len);
	अगर (!tcph)
		जाओ err;

	opt = (u8 *)tcph;
	क्रम (i = माप(*tcph); i < tcphdr_len - 1; i += optl) अणु
		optl = optlen(opt, i);

		अगर (priv->type != opt[i])
			जारी;

		अगर (i + optl > tcphdr_len || priv->len + priv->offset > optl)
			जाओ err;

		offset = i + priv->offset;
		अगर (priv->flags & NFT_EXTHDR_F_PRESENT) अणु
			*dest = 1;
		पूर्ण अन्यथा अणु
			dest[priv->len / NFT_REG32_SIZE] = 0;
			स_नकल(dest, opt + offset, priv->len);
		पूर्ण

		वापस;
	पूर्ण

err:
	अगर (priv->flags & NFT_EXTHDR_F_PRESENT)
		*dest = 0;
	अन्यथा
		regs->verdict.code = NFT_BREAK;
पूर्ण

अटल व्योम nft_exthdr_tcp_set_eval(स्थिर काष्ठा nft_expr *expr,
				    काष्ठा nft_regs *regs,
				    स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	u8 buff[माप(काष्ठा tcphdr) + MAX_TCP_OPTION_SPACE];
	काष्ठा nft_exthdr *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक i, optl, tcphdr_len, offset;
	काष्ठा tcphdr *tcph;
	u8 *opt;

	tcph = nft_tcp_header_poपूर्णांकer(pkt, माप(buff), buff, &tcphdr_len);
	अगर (!tcph)
		वापस;

	opt = (u8 *)tcph;
	क्रम (i = माप(*tcph); i < tcphdr_len - 1; i += optl) अणु
		जोड़ अणु
			__be16 v16;
			__be32 v32;
		पूर्ण old, new;

		optl = optlen(opt, i);

		अगर (priv->type != opt[i])
			जारी;

		अगर (i + optl > tcphdr_len || priv->len + priv->offset > optl)
			वापस;

		अगर (skb_ensure_writable(pkt->skb,
					pkt->xt.thoff + i + priv->len))
			वापस;

		tcph = nft_tcp_header_poपूर्णांकer(pkt, माप(buff), buff,
					      &tcphdr_len);
		अगर (!tcph)
			वापस;

		offset = i + priv->offset;

		चयन (priv->len) अणु
		हाल 2:
			old.v16 = get_unaligned((u16 *)(opt + offset));
			new.v16 = (__क्रमce __be16)nft_reg_load16(
				&regs->data[priv->sreg]);

			चयन (priv->type) अणु
			हाल TCPOPT_MSS:
				/* increase can cause connection to stall */
				अगर (ntohs(old.v16) <= ntohs(new.v16))
					वापस;
			अवरोध;
			पूर्ण

			अगर (old.v16 == new.v16)
				वापस;

			put_unaligned(new.v16, (u16*)(opt + offset));
			inet_proto_csum_replace2(&tcph->check, pkt->skb,
						 old.v16, new.v16, false);
			अवरोध;
		हाल 4:
			new.v32 = regs->data[priv->sreg];
			old.v32 = get_unaligned((u32 *)(opt + offset));

			अगर (old.v32 == new.v32)
				वापस;

			put_unaligned(new.v32, (u32*)(opt + offset));
			inet_proto_csum_replace4(&tcph->check, pkt->skb,
						 old.v32, new.v32, false);
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
			अवरोध;
		पूर्ण

		वापस;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_exthdr_policy[NFTA_EXTHDR_MAX + 1] = अणु
	[NFTA_EXTHDR_DREG]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_EXTHDR_TYPE]		= अणु .type = NLA_U8 पूर्ण,
	[NFTA_EXTHDR_OFFSET]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_EXTHDR_LEN]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_EXTHDR_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_EXTHDR_OP]		= अणु .type = NLA_U32 पूर्ण,
	[NFTA_EXTHDR_SREG]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_exthdr_init(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nft_expr *expr,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_exthdr *priv = nft_expr_priv(expr);
	u32 offset, len, flags = 0, op = NFT_EXTHDR_OP_IPV6;
	पूर्णांक err;

	अगर (!tb[NFTA_EXTHDR_DREG] ||
	    !tb[NFTA_EXTHDR_TYPE] ||
	    !tb[NFTA_EXTHDR_OFFSET] ||
	    !tb[NFTA_EXTHDR_LEN])
		वापस -EINVAL;

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_OFFSET], U8_MAX, &offset);
	अगर (err < 0)
		वापस err;

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_LEN], U8_MAX, &len);
	अगर (err < 0)
		वापस err;

	अगर (tb[NFTA_EXTHDR_FLAGS]) अणु
		err = nft_parse_u32_check(tb[NFTA_EXTHDR_FLAGS], U8_MAX, &flags);
		अगर (err < 0)
			वापस err;

		अगर (flags & ~NFT_EXTHDR_F_PRESENT)
			वापस -EINVAL;
	पूर्ण

	अगर (tb[NFTA_EXTHDR_OP]) अणु
		err = nft_parse_u32_check(tb[NFTA_EXTHDR_OP], U8_MAX, &op);
		अगर (err < 0)
			वापस err;
	पूर्ण

	priv->type   = nla_get_u8(tb[NFTA_EXTHDR_TYPE]);
	priv->offset = offset;
	priv->len    = len;
	priv->flags  = flags;
	priv->op     = op;

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_EXTHDR_DREG],
					&priv->dreg, शून्य, NFT_DATA_VALUE,
					priv->len);
पूर्ण

अटल पूर्णांक nft_exthdr_tcp_set_init(स्थिर काष्ठा nft_ctx *ctx,
				   स्थिर काष्ठा nft_expr *expr,
				   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_exthdr *priv = nft_expr_priv(expr);
	u32 offset, len, flags = 0, op = NFT_EXTHDR_OP_IPV6;
	पूर्णांक err;

	अगर (!tb[NFTA_EXTHDR_SREG] ||
	    !tb[NFTA_EXTHDR_TYPE] ||
	    !tb[NFTA_EXTHDR_OFFSET] ||
	    !tb[NFTA_EXTHDR_LEN])
		वापस -EINVAL;

	अगर (tb[NFTA_EXTHDR_DREG] || tb[NFTA_EXTHDR_FLAGS])
		वापस -EINVAL;

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_OFFSET], U8_MAX, &offset);
	अगर (err < 0)
		वापस err;

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_LEN], U8_MAX, &len);
	अगर (err < 0)
		वापस err;

	अगर (offset < 2)
		वापस -EOPNOTSUPP;

	चयन (len) अणु
	हाल 2: अवरोध;
	हाल 4: अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	err = nft_parse_u32_check(tb[NFTA_EXTHDR_OP], U8_MAX, &op);
	अगर (err < 0)
		वापस err;

	priv->type   = nla_get_u8(tb[NFTA_EXTHDR_TYPE]);
	priv->offset = offset;
	priv->len    = len;
	priv->flags  = flags;
	priv->op     = op;

	वापस nft_parse_रेजिस्टर_load(tb[NFTA_EXTHDR_SREG], &priv->sreg,
				       priv->len);
पूर्ण

अटल पूर्णांक nft_exthdr_ipv4_init(स्थिर काष्ठा nft_ctx *ctx,
				स्थिर काष्ठा nft_expr *expr,
				स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_exthdr *priv = nft_expr_priv(expr);
	पूर्णांक err = nft_exthdr_init(ctx, expr, tb);

	अगर (err < 0)
		वापस err;

	चयन (priv->type) अणु
	हाल IPOPT_SSRR:
	हाल IPOPT_LSRR:
	हाल IPOPT_RR:
	हाल IPOPT_RA:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nft_exthdr_dump_common(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_exthdr *priv)
अणु
	अगर (nla_put_u8(skb, NFTA_EXTHDR_TYPE, priv->type))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_EXTHDR_OFFSET, htonl(priv->offset)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_EXTHDR_LEN, htonl(priv->len)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_EXTHDR_FLAGS, htonl(priv->flags)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_EXTHDR_OP, htonl(priv->op)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल पूर्णांक nft_exthdr_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_exthdr *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_EXTHDR_DREG, priv->dreg))
		वापस -1;

	वापस nft_exthdr_dump_common(skb, priv);
पूर्ण

अटल पूर्णांक nft_exthdr_dump_set(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_exthdr *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_EXTHDR_SREG, priv->sreg))
		वापस -1;

	वापस nft_exthdr_dump_common(skb, priv);
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_exthdr_ipv6_ops = अणु
	.type		= &nft_exthdr_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_exthdr)),
	.eval		= nft_exthdr_ipv6_eval,
	.init		= nft_exthdr_init,
	.dump		= nft_exthdr_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_exthdr_ipv4_ops = अणु
	.type		= &nft_exthdr_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_exthdr)),
	.eval		= nft_exthdr_ipv4_eval,
	.init		= nft_exthdr_ipv4_init,
	.dump		= nft_exthdr_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_exthdr_tcp_ops = अणु
	.type		= &nft_exthdr_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_exthdr)),
	.eval		= nft_exthdr_tcp_eval,
	.init		= nft_exthdr_init,
	.dump		= nft_exthdr_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_exthdr_tcp_set_ops = अणु
	.type		= &nft_exthdr_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_exthdr)),
	.eval		= nft_exthdr_tcp_set_eval,
	.init		= nft_exthdr_tcp_set_init,
	.dump		= nft_exthdr_dump_set,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_exthdr_select_ops(स्थिर काष्ठा nft_ctx *ctx,
		      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	u32 op;

	अगर (!tb[NFTA_EXTHDR_OP])
		वापस &nft_exthdr_ipv6_ops;

	अगर (tb[NFTA_EXTHDR_SREG] && tb[NFTA_EXTHDR_DREG])
		वापस ERR_PTR(-EOPNOTSUPP);

	op = ntohl(nla_get_be32(tb[NFTA_EXTHDR_OP]));
	चयन (op) अणु
	हाल NFT_EXTHDR_OP_TCPOPT:
		अगर (tb[NFTA_EXTHDR_SREG])
			वापस &nft_exthdr_tcp_set_ops;
		अगर (tb[NFTA_EXTHDR_DREG])
			वापस &nft_exthdr_tcp_ops;
		अवरोध;
	हाल NFT_EXTHDR_OP_IPV6:
		अगर (tb[NFTA_EXTHDR_DREG])
			वापस &nft_exthdr_ipv6_ops;
		अवरोध;
	हाल NFT_EXTHDR_OP_IPV4:
		अगर (ctx->family != NFPROTO_IPV6) अणु
			अगर (tb[NFTA_EXTHDR_DREG])
				वापस &nft_exthdr_ipv4_ops;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

काष्ठा nft_expr_type nft_exthdr_type __पढ़ो_mostly = अणु
	.name		= "exthdr",
	.select_ops	= nft_exthdr_select_ops,
	.policy		= nft_exthdr_policy,
	.maxattr	= NFTA_EXTHDR_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
