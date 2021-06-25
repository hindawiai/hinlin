<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/netfilter/nft_meta.h>
#समावेश <linux/अगर_bridge.h>

अटल स्थिर काष्ठा net_device *
nft_meta_get_bridge(स्थिर काष्ठा net_device *dev)
अणु
	अगर (dev && netअगर_is_bridge_port(dev))
		वापस netdev_master_upper_dev_get_rcu((काष्ठा net_device *)dev);

	वापस शून्य;
पूर्ण

अटल व्योम nft_meta_bridge_get_eval(स्थिर काष्ठा nft_expr *expr,
				     काष्ठा nft_regs *regs,
				     स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_meta *priv = nft_expr_priv(expr);
	स्थिर काष्ठा net_device *in = nft_in(pkt), *out = nft_out(pkt);
	u32 *dest = &regs->data[priv->dreg];
	स्थिर काष्ठा net_device *br_dev;

	चयन (priv->key) अणु
	हाल NFT_META_BRI_IIFNAME:
		br_dev = nft_meta_get_bridge(in);
		अवरोध;
	हाल NFT_META_BRI_OIFNAME:
		br_dev = nft_meta_get_bridge(out);
		अवरोध;
	हाल NFT_META_BRI_IIFPVID: अणु
		u16 p_pvid;

		br_dev = nft_meta_get_bridge(in);
		अगर (!br_dev || !br_vlan_enabled(br_dev))
			जाओ err;

		br_vlan_get_pvid_rcu(in, &p_pvid);
		nft_reg_store16(dest, p_pvid);
		वापस;
	पूर्ण
	हाल NFT_META_BRI_IIFVPROTO: अणु
		u16 p_proto;

		br_dev = nft_meta_get_bridge(in);
		अगर (!br_dev || !br_vlan_enabled(br_dev))
			जाओ err;

		br_vlan_get_proto(br_dev, &p_proto);
		nft_reg_store16(dest, htons(p_proto));
		वापस;
	पूर्ण
	शेष:
		वापस nft_meta_get_eval(expr, regs, pkt);
	पूर्ण

	म_नकलन((अक्षर *)dest, br_dev ? br_dev->name : "", IFNAMSIZ);
	वापस;
err:
	regs->verdict.code = NFT_BREAK;
पूर्ण

अटल पूर्णांक nft_meta_bridge_get_init(स्थिर काष्ठा nft_ctx *ctx,
				    स्थिर काष्ठा nft_expr *expr,
				    स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_meta *priv = nft_expr_priv(expr);
	अचिन्हित पूर्णांक len;

	priv->key = ntohl(nla_get_be32(tb[NFTA_META_KEY]));
	चयन (priv->key) अणु
	हाल NFT_META_BRI_IIFNAME:
	हाल NFT_META_BRI_OIFNAME:
		len = IFNAMSIZ;
		अवरोध;
	हाल NFT_META_BRI_IIFPVID:
	हाल NFT_META_BRI_IIFVPROTO:
		len = माप(u16);
		अवरोध;
	शेष:
		वापस nft_meta_get_init(ctx, expr, tb);
	पूर्ण

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_META_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, len);
पूर्ण

अटल काष्ठा nft_expr_type nft_meta_bridge_type;
अटल स्थिर काष्ठा nft_expr_ops nft_meta_bridge_get_ops = अणु
	.type		= &nft_meta_bridge_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_meta)),
	.eval		= nft_meta_bridge_get_eval,
	.init		= nft_meta_bridge_get_init,
	.dump		= nft_meta_get_dump,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops nft_meta_bridge_set_ops = अणु
	.type		= &nft_meta_bridge_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_meta)),
	.eval		= nft_meta_set_eval,
	.init		= nft_meta_set_init,
	.destroy	= nft_meta_set_destroy,
	.dump		= nft_meta_set_dump,
	.validate	= nft_meta_set_validate,
पूर्ण;

अटल स्थिर काष्ठा nft_expr_ops *
nft_meta_bridge_select_ops(स्थिर काष्ठा nft_ctx *ctx,
			   स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	अगर (tb[NFTA_META_KEY] == शून्य)
		वापस ERR_PTR(-EINVAL);

	अगर (tb[NFTA_META_DREG] && tb[NFTA_META_SREG])
		वापस ERR_PTR(-EINVAL);

	अगर (tb[NFTA_META_DREG])
		वापस &nft_meta_bridge_get_ops;

	अगर (tb[NFTA_META_SREG])
		वापस &nft_meta_bridge_set_ops;

	वापस ERR_PTR(-EINVAL);
पूर्ण

अटल काष्ठा nft_expr_type nft_meta_bridge_type __पढ़ो_mostly = अणु
	.family         = NFPROTO_BRIDGE,
	.name           = "meta",
	.select_ops     = nft_meta_bridge_select_ops,
	.policy         = nft_meta_policy,
	.maxattr        = NFTA_META_MAX,
	.owner          = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_meta_bridge_module_init(व्योम)
अणु
	वापस nft_रेजिस्टर_expr(&nft_meta_bridge_type);
पूर्ण

अटल व्योम __निकास nft_meta_bridge_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_expr(&nft_meta_bridge_type);
पूर्ण

module_init(nft_meta_bridge_module_init);
module_निकास(nft_meta_bridge_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wenxu <wenxu@ucloud.cn>");
MODULE_ALIAS_NFT_AF_EXPR(AF_BRIDGE, "meta");
MODULE_DESCRIPTION("Support for bridge dedicated meta key");
