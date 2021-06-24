<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Patrick McHardy <kaber@trash.net>
 *
 * Development of this code funded by Astaro AG (http://www.astaro.com/)
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables_core.h>
#समावेश <net/netfilter/nf_tables.h>

काष्ठा nft_byteorder अणु
	u8			sreg;
	u8			dreg;
	क्रमागत nft_byteorder_ops	op:8;
	u8			len;
	u8			size;
पूर्ण;

व्योम nft_byteorder_eval(स्थिर काष्ठा nft_expr *expr,
			काष्ठा nft_regs *regs,
			स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_byteorder *priv = nft_expr_priv(expr);
	u32 *src = &regs->data[priv->sreg];
	u32 *dst = &regs->data[priv->dreg];
	जोड़ अणु u32 u32; u16 u16; पूर्ण *s, *d;
	अचिन्हित पूर्णांक i;

	s = (व्योम *)src;
	d = (व्योम *)dst;

	चयन (priv->size) अणु
	हाल 8: अणु
		u64 src64;

		चयन (priv->op) अणु
		हाल NFT_BYTEORDER_NTOH:
			क्रम (i = 0; i < priv->len / 8; i++) अणु
				src64 = nft_reg_load64(&src[i]);
				nft_reg_store64(&dst[i], be64_to_cpu(src64));
			पूर्ण
			अवरोध;
		हाल NFT_BYTEORDER_HTON:
			क्रम (i = 0; i < priv->len / 8; i++) अणु
				src64 = (__क्रमce __u64)
					cpu_to_be64(nft_reg_load64(&src[i]));
				nft_reg_store64(&dst[i], src64);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल 4:
		चयन (priv->op) अणु
		हाल NFT_BYTEORDER_NTOH:
			क्रम (i = 0; i < priv->len / 4; i++)
				d[i].u32 = ntohl((__क्रमce __be32)s[i].u32);
			अवरोध;
		हाल NFT_BYTEORDER_HTON:
			क्रम (i = 0; i < priv->len / 4; i++)
				d[i].u32 = (__क्रमce __u32)htonl(s[i].u32);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन (priv->op) अणु
		हाल NFT_BYTEORDER_NTOH:
			क्रम (i = 0; i < priv->len / 2; i++)
				d[i].u16 = ntohs((__क्रमce __be16)s[i].u16);
			अवरोध;
		हाल NFT_BYTEORDER_HTON:
			क्रम (i = 0; i < priv->len / 2; i++)
				d[i].u16 = (__क्रमce __u16)htons(s[i].u16);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_byteorder_policy[NFTA_BYTEORDER_MAX + 1] = अणु
	[NFTA_BYTEORDER_SREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BYTEORDER_DREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BYTEORDER_OP]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BYTEORDER_LEN]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_BYTEORDER_SIZE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_byteorder_init(स्थिर काष्ठा nft_ctx *ctx,
			      स्थिर काष्ठा nft_expr *expr,
			      स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_byteorder *priv = nft_expr_priv(expr);
	u32 size, len;
	पूर्णांक err;

	अगर (tb[NFTA_BYTEORDER_SREG] == शून्य ||
	    tb[NFTA_BYTEORDER_DREG] == शून्य ||
	    tb[NFTA_BYTEORDER_LEN] == शून्य ||
	    tb[NFTA_BYTEORDER_SIZE] == शून्य ||
	    tb[NFTA_BYTEORDER_OP] == शून्य)
		वापस -EINVAL;

	priv->op = ntohl(nla_get_be32(tb[NFTA_BYTEORDER_OP]));
	चयन (priv->op) अणु
	हाल NFT_BYTEORDER_NTOH:
	हाल NFT_BYTEORDER_HTON:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = nft_parse_u32_check(tb[NFTA_BYTEORDER_SIZE], U8_MAX, &size);
	अगर (err < 0)
		वापस err;

	priv->size = size;

	चयन (priv->size) अणु
	हाल 2:
	हाल 4:
	हाल 8:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = nft_parse_u32_check(tb[NFTA_BYTEORDER_LEN], U8_MAX, &len);
	अगर (err < 0)
		वापस err;

	priv->len = len;

	err = nft_parse_रेजिस्टर_load(tb[NFTA_BYTEORDER_SREG], &priv->sreg,
				      priv->len);
	अगर (err < 0)
		वापस err;

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_BYTEORDER_DREG],
					&priv->dreg, शून्य, NFT_DATA_VALUE,
					priv->len);
पूर्ण

अटल पूर्णांक nft_byteorder_dump(काष्ठा sk_buff *skb, स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_byteorder *priv = nft_expr_priv(expr);

	अगर (nft_dump_रेजिस्टर(skb, NFTA_BYTEORDER_SREG, priv->sreg))
		जाओ nla_put_failure;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_BYTEORDER_DREG, priv->dreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_BYTEORDER_OP, htonl(priv->op)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_BYTEORDER_LEN, htonl(priv->len)))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_BYTEORDER_SIZE, htonl(priv->size)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल स्थिर काष्ठा nft_expr_ops nft_byteorder_ops = अणु
	.type		= &nft_byteorder_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_byteorder)),
	.eval		= nft_byteorder_eval,
	.init		= nft_byteorder_init,
	.dump		= nft_byteorder_dump,
पूर्ण;

काष्ठा nft_expr_type nft_byteorder_type __पढ़ो_mostly = अणु
	.name		= "byteorder",
	.ops		= &nft_byteorder_ops,
	.policy		= nft_byteorder_policy,
	.maxattr	= NFTA_BYTEORDER_MAX,
	.owner		= THIS_MODULE,
पूर्ण;
