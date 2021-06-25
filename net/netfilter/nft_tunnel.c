<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/seqlock.h>
#समावेश <linux/netlink.h>
#समावेश <linux/netfilter.h>
#समावेश <linux/netfilter/nf_tables.h>
#समावेश <net/netfilter/nf_tables.h>
#समावेश <net/dst_metadata.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/vxlan.h>
#समावेश <net/erspan.h>
#समावेश <net/geneve.h>

काष्ठा nft_tunnel अणु
	क्रमागत nft_tunnel_keys	key:8;
	u8			dreg;
	क्रमागत nft_tunnel_mode	mode:8;
पूर्ण;

अटल व्योम nft_tunnel_get_eval(स्थिर काष्ठा nft_expr *expr,
				काष्ठा nft_regs *regs,
				स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	स्थिर काष्ठा nft_tunnel *priv = nft_expr_priv(expr);
	u32 *dest = &regs->data[priv->dreg];
	काष्ठा ip_tunnel_info *tun_info;

	tun_info = skb_tunnel_info(pkt->skb);

	चयन (priv->key) अणु
	हाल NFT_TUNNEL_PATH:
		अगर (!tun_info) अणु
			nft_reg_store8(dest, false);
			वापस;
		पूर्ण
		अगर (priv->mode == NFT_TUNNEL_MODE_NONE ||
		    (priv->mode == NFT_TUNNEL_MODE_RX &&
		     !(tun_info->mode & IP_TUNNEL_INFO_TX)) ||
		    (priv->mode == NFT_TUNNEL_MODE_TX &&
		     (tun_info->mode & IP_TUNNEL_INFO_TX)))
			nft_reg_store8(dest, true);
		अन्यथा
			nft_reg_store8(dest, false);
		अवरोध;
	हाल NFT_TUNNEL_ID:
		अगर (!tun_info) अणु
			regs->verdict.code = NFT_BREAK;
			वापस;
		पूर्ण
		अगर (priv->mode == NFT_TUNNEL_MODE_NONE ||
		    (priv->mode == NFT_TUNNEL_MODE_RX &&
		     !(tun_info->mode & IP_TUNNEL_INFO_TX)) ||
		    (priv->mode == NFT_TUNNEL_MODE_TX &&
		     (tun_info->mode & IP_TUNNEL_INFO_TX)))
			*dest = ntohl(tunnel_id_to_key32(tun_info->key.tun_id));
		अन्यथा
			regs->verdict.code = NFT_BREAK;
		अवरोध;
	शेष:
		WARN_ON(1);
		regs->verdict.code = NFT_BREAK;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tunnel_policy[NFTA_TUNNEL_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_TUNNEL_DREG]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_TUNNEL_MODE]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tunnel_get_init(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nft_expr *expr,
			       स्थिर काष्ठा nlattr * स्थिर tb[])
अणु
	काष्ठा nft_tunnel *priv = nft_expr_priv(expr);
	u32 len;

	अगर (!tb[NFTA_TUNNEL_KEY] ||
	    !tb[NFTA_TUNNEL_DREG])
		वापस -EINVAL;

	priv->key = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY]));
	चयन (priv->key) अणु
	हाल NFT_TUNNEL_PATH:
		len = माप(u8);
		अवरोध;
	हाल NFT_TUNNEL_ID:
		len = माप(u32);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (tb[NFTA_TUNNEL_MODE]) अणु
		priv->mode = ntohl(nla_get_be32(tb[NFTA_TUNNEL_MODE]));
		अगर (priv->mode > NFT_TUNNEL_MODE_MAX)
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		priv->mode = NFT_TUNNEL_MODE_NONE;
	पूर्ण

	वापस nft_parse_रेजिस्टर_store(ctx, tb[NFTA_TUNNEL_DREG], &priv->dreg,
					शून्य, NFT_DATA_VALUE, len);
पूर्ण

अटल पूर्णांक nft_tunnel_get_dump(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा nft_expr *expr)
अणु
	स्थिर काष्ठा nft_tunnel *priv = nft_expr_priv(expr);

	अगर (nla_put_be32(skb, NFTA_TUNNEL_KEY, htonl(priv->key)))
		जाओ nla_put_failure;
	अगर (nft_dump_रेजिस्टर(skb, NFTA_TUNNEL_DREG, priv->dreg))
		जाओ nla_put_failure;
	अगर (nla_put_be32(skb, NFTA_TUNNEL_MODE, htonl(priv->mode)))
		जाओ nla_put_failure;
	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल काष्ठा nft_expr_type nft_tunnel_type;
अटल स्थिर काष्ठा nft_expr_ops nft_tunnel_get_ops = अणु
	.type		= &nft_tunnel_type,
	.size		= NFT_EXPR_SIZE(माप(काष्ठा nft_tunnel)),
	.eval		= nft_tunnel_get_eval,
	.init		= nft_tunnel_get_init,
	.dump		= nft_tunnel_get_dump,
पूर्ण;

अटल काष्ठा nft_expr_type nft_tunnel_type __पढ़ो_mostly = अणु
	.name		= "tunnel",
	.ops		= &nft_tunnel_get_ops,
	.policy		= nft_tunnel_policy,
	.maxattr	= NFTA_TUNNEL_MAX,
	.owner		= THIS_MODULE,
पूर्ण;

काष्ठा nft_tunnel_opts अणु
	जोड़ अणु
		काष्ठा vxlan_metadata	vxlan;
		काष्ठा erspan_metadata	erspan;
		u8	data[IP_TUNNEL_OPTS_MAX];
	पूर्ण u;
	u32	len;
	__be16	flags;
पूर्ण;

काष्ठा nft_tunnel_obj अणु
	काष्ठा metadata_dst	*md;
	काष्ठा nft_tunnel_opts	opts;
पूर्ण;

अटल स्थिर काष्ठा nla_policy nft_tunnel_ip_policy[NFTA_TUNNEL_KEY_IP_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY_IP_SRC]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_TUNNEL_KEY_IP_DST]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tunnel_obj_ip_init(स्थिर काष्ठा nft_ctx *ctx,
				  स्थिर काष्ठा nlattr *attr,
				  काष्ठा ip_tunnel_info *info)
अणु
	काष्ठा nlattr *tb[NFTA_TUNNEL_KEY_IP_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_TUNNEL_KEY_IP_MAX, attr,
					  nft_tunnel_ip_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_TUNNEL_KEY_IP_DST])
		वापस -EINVAL;

	अगर (tb[NFTA_TUNNEL_KEY_IP_SRC])
		info->key.u.ipv4.src = nla_get_be32(tb[NFTA_TUNNEL_KEY_IP_SRC]);
	अगर (tb[NFTA_TUNNEL_KEY_IP_DST])
		info->key.u.ipv4.dst = nla_get_be32(tb[NFTA_TUNNEL_KEY_IP_DST]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tunnel_ip6_policy[NFTA_TUNNEL_KEY_IP6_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY_IP6_SRC]	= अणु .len = माप(काष्ठा in6_addr), पूर्ण,
	[NFTA_TUNNEL_KEY_IP6_DST]	= अणु .len = माप(काष्ठा in6_addr), पूर्ण,
	[NFTA_TUNNEL_KEY_IP6_FLOWLABEL]	= अणु .type = NLA_U32, पूर्ण
पूर्ण;

अटल पूर्णांक nft_tunnel_obj_ip6_init(स्थिर काष्ठा nft_ctx *ctx,
				   स्थिर काष्ठा nlattr *attr,
				   काष्ठा ip_tunnel_info *info)
अणु
	काष्ठा nlattr *tb[NFTA_TUNNEL_KEY_IP6_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_TUNNEL_KEY_IP6_MAX, attr,
					  nft_tunnel_ip6_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_TUNNEL_KEY_IP6_DST])
		वापस -EINVAL;

	अगर (tb[NFTA_TUNNEL_KEY_IP6_SRC]) अणु
		स_नकल(&info->key.u.ipv6.src,
		       nla_data(tb[NFTA_TUNNEL_KEY_IP6_SRC]),
		       माप(काष्ठा in6_addr));
	पूर्ण
	अगर (tb[NFTA_TUNNEL_KEY_IP6_DST]) अणु
		स_नकल(&info->key.u.ipv6.dst,
		       nla_data(tb[NFTA_TUNNEL_KEY_IP6_DST]),
		       माप(काष्ठा in6_addr));
	पूर्ण
	अगर (tb[NFTA_TUNNEL_KEY_IP6_FLOWLABEL])
		info->key.label = nla_get_be32(tb[NFTA_TUNNEL_KEY_IP6_FLOWLABEL]);

	info->mode |= IP_TUNNEL_INFO_IPV6;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tunnel_opts_vxlan_policy[NFTA_TUNNEL_KEY_VXLAN_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY_VXLAN_GBP]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tunnel_obj_vxlan_init(स्थिर काष्ठा nlattr *attr,
				     काष्ठा nft_tunnel_opts *opts)
अणु
	काष्ठा nlattr *tb[NFTA_TUNNEL_KEY_VXLAN_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested_deprecated(tb, NFTA_TUNNEL_KEY_VXLAN_MAX, attr,
					  nft_tunnel_opts_vxlan_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_TUNNEL_KEY_VXLAN_GBP])
		वापस -EINVAL;

	opts->u.vxlan.gbp = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY_VXLAN_GBP]));

	opts->len	= माप(काष्ठा vxlan_metadata);
	opts->flags	= TUNNEL_VXLAN_OPT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tunnel_opts_erspan_policy[NFTA_TUNNEL_KEY_ERSPAN_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY_ERSPAN_VERSION]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX]	= अणु .type = NLA_U32 पूर्ण,
	[NFTA_TUNNEL_KEY_ERSPAN_V2_सूची]		= अणु .type = NLA_U8 पूर्ण,
	[NFTA_TUNNEL_KEY_ERSPAN_V2_HWID]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tunnel_obj_erspan_init(स्थिर काष्ठा nlattr *attr,
				      काष्ठा nft_tunnel_opts *opts)
अणु
	काष्ठा nlattr *tb[NFTA_TUNNEL_KEY_ERSPAN_MAX + 1];
	uपूर्णांक8_t hwid, dir;
	पूर्णांक err, version;

	err = nla_parse_nested_deprecated(tb, NFTA_TUNNEL_KEY_ERSPAN_MAX,
					  attr, nft_tunnel_opts_erspan_policy,
					  शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_TUNNEL_KEY_ERSPAN_VERSION])
		 वापस -EINVAL;

	version = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY_ERSPAN_VERSION]));
	चयन (version) अणु
	हाल ERSPAN_VERSION:
		अगर (!tb[NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX])
			वापस -EINVAL;

		opts->u.erspan.u.index =
			nla_get_be32(tb[NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX]);
		अवरोध;
	हाल ERSPAN_VERSION2:
		अगर (!tb[NFTA_TUNNEL_KEY_ERSPAN_V2_सूची] ||
		    !tb[NFTA_TUNNEL_KEY_ERSPAN_V2_HWID])
			वापस -EINVAL;

		hwid = nla_get_u8(tb[NFTA_TUNNEL_KEY_ERSPAN_V2_HWID]);
		dir = nla_get_u8(tb[NFTA_TUNNEL_KEY_ERSPAN_V2_सूची]);

		set_hwid(&opts->u.erspan.u.md2, hwid);
		opts->u.erspan.u.md2.dir = dir;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	opts->u.erspan.version = version;

	opts->len	= माप(काष्ठा erspan_metadata);
	opts->flags	= TUNNEL_ERSPAN_OPT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tunnel_opts_geneve_policy[NFTA_TUNNEL_KEY_GENEVE_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY_GENEVE_CLASS]	= अणु .type = NLA_U16 पूर्ण,
	[NFTA_TUNNEL_KEY_GENEVE_TYPE]	= अणु .type = NLA_U8 पूर्ण,
	[NFTA_TUNNEL_KEY_GENEVE_DATA]	= अणु .type = NLA_BINARY, .len = 128 पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tunnel_obj_geneve_init(स्थिर काष्ठा nlattr *attr,
				      काष्ठा nft_tunnel_opts *opts)
अणु
	काष्ठा geneve_opt *opt = (काष्ठा geneve_opt *)opts->u.data + opts->len;
	काष्ठा nlattr *tb[NFTA_TUNNEL_KEY_GENEVE_MAX + 1];
	पूर्णांक err, data_len;

	err = nla_parse_nested(tb, NFTA_TUNNEL_KEY_GENEVE_MAX, attr,
			       nft_tunnel_opts_geneve_policy, शून्य);
	अगर (err < 0)
		वापस err;

	अगर (!tb[NFTA_TUNNEL_KEY_GENEVE_CLASS] ||
	    !tb[NFTA_TUNNEL_KEY_GENEVE_TYPE] ||
	    !tb[NFTA_TUNNEL_KEY_GENEVE_DATA])
		वापस -EINVAL;

	attr = tb[NFTA_TUNNEL_KEY_GENEVE_DATA];
	data_len = nla_len(attr);
	अगर (data_len % 4)
		वापस -EINVAL;

	opts->len += माप(*opt) + data_len;
	अगर (opts->len > IP_TUNNEL_OPTS_MAX)
		वापस -EINVAL;

	स_नकल(opt->opt_data, nla_data(attr), data_len);
	opt->length = data_len / 4;
	opt->opt_class = nla_get_be16(tb[NFTA_TUNNEL_KEY_GENEVE_CLASS]);
	opt->type = nla_get_u8(tb[NFTA_TUNNEL_KEY_GENEVE_TYPE]);
	opts->flags = TUNNEL_GENEVE_OPT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tunnel_opts_policy[NFTA_TUNNEL_KEY_OPTS_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY_OPTS_UNSPEC]	= अणु
		.strict_start_type = NFTA_TUNNEL_KEY_OPTS_GENEVE पूर्ण,
	[NFTA_TUNNEL_KEY_OPTS_VXLAN]	= अणु .type = NLA_NESTED, पूर्ण,
	[NFTA_TUNNEL_KEY_OPTS_ERSPAN]	= अणु .type = NLA_NESTED, पूर्ण,
	[NFTA_TUNNEL_KEY_OPTS_GENEVE]	= अणु .type = NLA_NESTED, पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tunnel_obj_opts_init(स्थिर काष्ठा nft_ctx *ctx,
				    स्थिर काष्ठा nlattr *attr,
				    काष्ठा ip_tunnel_info *info,
				    काष्ठा nft_tunnel_opts *opts)
अणु
	पूर्णांक err, rem, type = 0;
	काष्ठा nlattr *nla;

	err = nla_validate_nested_deprecated(attr, NFTA_TUNNEL_KEY_OPTS_MAX,
					     nft_tunnel_opts_policy, शून्य);
	अगर (err < 0)
		वापस err;

	nla_क्रम_each_attr(nla, nla_data(attr), nla_len(attr), rem) अणु
		चयन (nla_type(nla)) अणु
		हाल NFTA_TUNNEL_KEY_OPTS_VXLAN:
			अगर (type)
				वापस -EINVAL;
			err = nft_tunnel_obj_vxlan_init(nla, opts);
			अगर (err)
				वापस err;
			type = TUNNEL_VXLAN_OPT;
			अवरोध;
		हाल NFTA_TUNNEL_KEY_OPTS_ERSPAN:
			अगर (type)
				वापस -EINVAL;
			err = nft_tunnel_obj_erspan_init(nla, opts);
			अगर (err)
				वापस err;
			type = TUNNEL_ERSPAN_OPT;
			अवरोध;
		हाल NFTA_TUNNEL_KEY_OPTS_GENEVE:
			अगर (type && type != TUNNEL_GENEVE_OPT)
				वापस -EINVAL;
			err = nft_tunnel_obj_geneve_init(nla, opts);
			अगर (err)
				वापस err;
			type = TUNNEL_GENEVE_OPT;
			अवरोध;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy nft_tunnel_key_policy[NFTA_TUNNEL_KEY_MAX + 1] = अणु
	[NFTA_TUNNEL_KEY_IP]	= अणु .type = NLA_NESTED, पूर्ण,
	[NFTA_TUNNEL_KEY_IP6]	= अणु .type = NLA_NESTED, पूर्ण,
	[NFTA_TUNNEL_KEY_ID]	= अणु .type = NLA_U32, पूर्ण,
	[NFTA_TUNNEL_KEY_FLAGS]	= अणु .type = NLA_U32, पूर्ण,
	[NFTA_TUNNEL_KEY_TOS]	= अणु .type = NLA_U8, पूर्ण,
	[NFTA_TUNNEL_KEY_TTL]	= अणु .type = NLA_U8, पूर्ण,
	[NFTA_TUNNEL_KEY_SPORT]	= अणु .type = NLA_U16, पूर्ण,
	[NFTA_TUNNEL_KEY_DPORT]	= अणु .type = NLA_U16, पूर्ण,
	[NFTA_TUNNEL_KEY_OPTS]	= अणु .type = NLA_NESTED, पूर्ण,
पूर्ण;

अटल पूर्णांक nft_tunnel_obj_init(स्थिर काष्ठा nft_ctx *ctx,
			       स्थिर काष्ठा nlattr * स्थिर tb[],
			       काष्ठा nft_object *obj)
अणु
	काष्ठा nft_tunnel_obj *priv = nft_obj_data(obj);
	काष्ठा ip_tunnel_info info;
	काष्ठा metadata_dst *md;
	पूर्णांक err;

	अगर (!tb[NFTA_TUNNEL_KEY_ID])
		वापस -EINVAL;

	स_रखो(&info, 0, माप(info));
	info.mode		= IP_TUNNEL_INFO_TX;
	info.key.tun_id		= key32_to_tunnel_id(nla_get_be32(tb[NFTA_TUNNEL_KEY_ID]));
	info.key.tun_flags	= TUNNEL_KEY | TUNNEL_CSUM | TUNNEL_NOCACHE;

	अगर (tb[NFTA_TUNNEL_KEY_IP]) अणु
		err = nft_tunnel_obj_ip_init(ctx, tb[NFTA_TUNNEL_KEY_IP], &info);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अगर (tb[NFTA_TUNNEL_KEY_IP6]) अणु
		err = nft_tunnel_obj_ip6_init(ctx, tb[NFTA_TUNNEL_KEY_IP6], &info);
		अगर (err < 0)
			वापस err;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (tb[NFTA_TUNNEL_KEY_SPORT]) अणु
		info.key.tp_src = nla_get_be16(tb[NFTA_TUNNEL_KEY_SPORT]);
	पूर्ण
	अगर (tb[NFTA_TUNNEL_KEY_DPORT]) अणु
		info.key.tp_dst = nla_get_be16(tb[NFTA_TUNNEL_KEY_DPORT]);
	पूर्ण

	अगर (tb[NFTA_TUNNEL_KEY_FLAGS]) अणु
		u32 tun_flags;

		tun_flags = ntohl(nla_get_be32(tb[NFTA_TUNNEL_KEY_FLAGS]));
		अगर (tun_flags & ~NFT_TUNNEL_F_MASK)
			वापस -EOPNOTSUPP;

		अगर (tun_flags & NFT_TUNNEL_F_ZERO_CSUM_TX)
			info.key.tun_flags &= ~TUNNEL_CSUM;
		अगर (tun_flags & NFT_TUNNEL_F_DONT_FRAGMENT)
			info.key.tun_flags |= TUNNEL_DONT_FRAGMENT;
		अगर (tun_flags & NFT_TUNNEL_F_SEQ_NUMBER)
			info.key.tun_flags |= TUNNEL_SEQ;
	पूर्ण
	अगर (tb[NFTA_TUNNEL_KEY_TOS])
		info.key.tos = nla_get_u8(tb[NFTA_TUNNEL_KEY_TOS]);
	अगर (tb[NFTA_TUNNEL_KEY_TTL])
		info.key.ttl = nla_get_u8(tb[NFTA_TUNNEL_KEY_TTL]);
	अन्यथा
		info.key.ttl = U8_MAX;

	अगर (tb[NFTA_TUNNEL_KEY_OPTS]) अणु
		err = nft_tunnel_obj_opts_init(ctx, tb[NFTA_TUNNEL_KEY_OPTS],
					       &info, &priv->opts);
		अगर (err < 0)
			वापस err;
	पूर्ण

	md = metadata_dst_alloc(priv->opts.len, METADATA_IP_TUNNEL, GFP_KERNEL);
	अगर (!md)
		वापस -ENOMEM;

	स_नकल(&md->u.tun_info, &info, माप(info));
#अगर_घोषित CONFIG_DST_CACHE
	err = dst_cache_init(&md->u.tun_info.dst_cache, GFP_KERNEL);
	अगर (err < 0) अणु
		metadata_dst_मुक्त(md);
		वापस err;
	पूर्ण
#पूर्ण_अगर
	ip_tunnel_info_opts_set(&md->u.tun_info, &priv->opts.u, priv->opts.len,
				priv->opts.flags);
	priv->md = md;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nft_tunnel_obj_eval(काष्ठा nft_object *obj,
				       काष्ठा nft_regs *regs,
				       स्थिर काष्ठा nft_pktinfo *pkt)
अणु
	काष्ठा nft_tunnel_obj *priv = nft_obj_data(obj);
	काष्ठा sk_buff *skb = pkt->skb;

	skb_dst_drop(skb);
	dst_hold((काष्ठा dst_entry *) priv->md);
	skb_dst_set(skb, (काष्ठा dst_entry *) priv->md);
पूर्ण

अटल पूर्णांक nft_tunnel_ip_dump(काष्ठा sk_buff *skb, काष्ठा ip_tunnel_info *info)
अणु
	काष्ठा nlattr *nest;

	अगर (info->mode & IP_TUNNEL_INFO_IPV6) अणु
		nest = nla_nest_start_noflag(skb, NFTA_TUNNEL_KEY_IP6);
		अगर (!nest)
			वापस -1;

		अगर (nla_put_in6_addr(skb, NFTA_TUNNEL_KEY_IP6_SRC,
				     &info->key.u.ipv6.src) < 0 ||
		    nla_put_in6_addr(skb, NFTA_TUNNEL_KEY_IP6_DST,
				     &info->key.u.ipv6.dst) < 0 ||
		    nla_put_be32(skb, NFTA_TUNNEL_KEY_IP6_FLOWLABEL,
				 info->key.label)) अणु
			nla_nest_cancel(skb, nest);
			वापस -1;
		पूर्ण

		nla_nest_end(skb, nest);
	पूर्ण अन्यथा अणु
		nest = nla_nest_start_noflag(skb, NFTA_TUNNEL_KEY_IP);
		अगर (!nest)
			वापस -1;

		अगर (nla_put_in_addr(skb, NFTA_TUNNEL_KEY_IP_SRC,
				    info->key.u.ipv4.src) < 0 ||
		    nla_put_in_addr(skb, NFTA_TUNNEL_KEY_IP_DST,
				    info->key.u.ipv4.dst) < 0) अणु
			nla_nest_cancel(skb, nest);
			वापस -1;
		पूर्ण

		nla_nest_end(skb, nest);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nft_tunnel_opts_dump(काष्ठा sk_buff *skb,
				काष्ठा nft_tunnel_obj *priv)
अणु
	काष्ठा nft_tunnel_opts *opts = &priv->opts;
	काष्ठा nlattr *nest, *inner;

	nest = nla_nest_start_noflag(skb, NFTA_TUNNEL_KEY_OPTS);
	अगर (!nest)
		वापस -1;

	अगर (opts->flags & TUNNEL_VXLAN_OPT) अणु
		inner = nla_nest_start_noflag(skb, NFTA_TUNNEL_KEY_OPTS_VXLAN);
		अगर (!inner)
			जाओ failure;
		अगर (nla_put_be32(skb, NFTA_TUNNEL_KEY_VXLAN_GBP,
				 htonl(opts->u.vxlan.gbp)))
			जाओ inner_failure;
		nla_nest_end(skb, inner);
	पूर्ण अन्यथा अगर (opts->flags & TUNNEL_ERSPAN_OPT) अणु
		inner = nla_nest_start_noflag(skb, NFTA_TUNNEL_KEY_OPTS_ERSPAN);
		अगर (!inner)
			जाओ failure;
		अगर (nla_put_be32(skb, NFTA_TUNNEL_KEY_ERSPAN_VERSION,
				 htonl(opts->u.erspan.version)))
			जाओ inner_failure;
		चयन (opts->u.erspan.version) अणु
		हाल ERSPAN_VERSION:
			अगर (nla_put_be32(skb, NFTA_TUNNEL_KEY_ERSPAN_V1_INDEX,
					 opts->u.erspan.u.index))
				जाओ inner_failure;
			अवरोध;
		हाल ERSPAN_VERSION2:
			अगर (nla_put_u8(skb, NFTA_TUNNEL_KEY_ERSPAN_V2_HWID,
				       get_hwid(&opts->u.erspan.u.md2)) ||
			    nla_put_u8(skb, NFTA_TUNNEL_KEY_ERSPAN_V2_सूची,
				       opts->u.erspan.u.md2.dir))
				जाओ inner_failure;
			अवरोध;
		पूर्ण
		nla_nest_end(skb, inner);
	पूर्ण अन्यथा अगर (opts->flags & TUNNEL_GENEVE_OPT) अणु
		काष्ठा geneve_opt *opt;
		पूर्णांक offset = 0;

		inner = nla_nest_start_noflag(skb, NFTA_TUNNEL_KEY_OPTS_GENEVE);
		अगर (!inner)
			जाओ failure;
		जबतक (opts->len > offset) अणु
			opt = (काष्ठा geneve_opt *)opts->u.data + offset;
			अगर (nla_put_be16(skb, NFTA_TUNNEL_KEY_GENEVE_CLASS,
					 opt->opt_class) ||
			    nla_put_u8(skb, NFTA_TUNNEL_KEY_GENEVE_TYPE,
				       opt->type) ||
			    nla_put(skb, NFTA_TUNNEL_KEY_GENEVE_DATA,
				    opt->length * 4, opt->opt_data))
				जाओ inner_failure;
			offset += माप(*opt) + opt->length * 4;
		पूर्ण
		nla_nest_end(skb, inner);
	पूर्ण
	nla_nest_end(skb, nest);
	वापस 0;

inner_failure:
	nla_nest_cancel(skb, inner);
failure:
	nla_nest_cancel(skb, nest);
	वापस -1;
पूर्ण

अटल पूर्णांक nft_tunnel_ports_dump(काष्ठा sk_buff *skb,
				 काष्ठा ip_tunnel_info *info)
अणु
	अगर (nla_put_be16(skb, NFTA_TUNNEL_KEY_SPORT, info->key.tp_src) < 0 ||
	    nla_put_be16(skb, NFTA_TUNNEL_KEY_DPORT, info->key.tp_dst) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_tunnel_flags_dump(काष्ठा sk_buff *skb,
				 काष्ठा ip_tunnel_info *info)
अणु
	u32 flags = 0;

	अगर (info->key.tun_flags & TUNNEL_DONT_FRAGMENT)
		flags |= NFT_TUNNEL_F_DONT_FRAGMENT;
	अगर (!(info->key.tun_flags & TUNNEL_CSUM))
		flags |= NFT_TUNNEL_F_ZERO_CSUM_TX;
	अगर (info->key.tun_flags & TUNNEL_SEQ)
		flags |= NFT_TUNNEL_F_SEQ_NUMBER;

	अगर (nla_put_be32(skb, NFTA_TUNNEL_KEY_FLAGS, htonl(flags)) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक nft_tunnel_obj_dump(काष्ठा sk_buff *skb,
			       काष्ठा nft_object *obj, bool reset)
अणु
	काष्ठा nft_tunnel_obj *priv = nft_obj_data(obj);
	काष्ठा ip_tunnel_info *info = &priv->md->u.tun_info;

	अगर (nla_put_be32(skb, NFTA_TUNNEL_KEY_ID,
			 tunnel_id_to_key32(info->key.tun_id)) ||
	    nft_tunnel_ip_dump(skb, info) < 0 ||
	    nft_tunnel_ports_dump(skb, info) < 0 ||
	    nft_tunnel_flags_dump(skb, info) < 0 ||
	    nla_put_u8(skb, NFTA_TUNNEL_KEY_TOS, info->key.tos) ||
	    nla_put_u8(skb, NFTA_TUNNEL_KEY_TTL, info->key.ttl) ||
	    nft_tunnel_opts_dump(skb, priv) < 0)
		जाओ nla_put_failure;

	वापस 0;

nla_put_failure:
	वापस -1;
पूर्ण

अटल व्योम nft_tunnel_obj_destroy(स्थिर काष्ठा nft_ctx *ctx,
				   काष्ठा nft_object *obj)
अणु
	काष्ठा nft_tunnel_obj *priv = nft_obj_data(obj);

	metadata_dst_मुक्त(priv->md);
पूर्ण

अटल काष्ठा nft_object_type nft_tunnel_obj_type;
अटल स्थिर काष्ठा nft_object_ops nft_tunnel_obj_ops = अणु
	.type		= &nft_tunnel_obj_type,
	.size		= माप(काष्ठा nft_tunnel_obj),
	.eval		= nft_tunnel_obj_eval,
	.init		= nft_tunnel_obj_init,
	.destroy	= nft_tunnel_obj_destroy,
	.dump		= nft_tunnel_obj_dump,
पूर्ण;

अटल काष्ठा nft_object_type nft_tunnel_obj_type __पढ़ो_mostly = अणु
	.type		= NFT_OBJECT_TUNNEL,
	.ops		= &nft_tunnel_obj_ops,
	.maxattr	= NFTA_TUNNEL_KEY_MAX,
	.policy		= nft_tunnel_key_policy,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init nft_tunnel_module_init(व्योम)
अणु
	पूर्णांक err;

	err = nft_रेजिस्टर_expr(&nft_tunnel_type);
	अगर (err < 0)
		वापस err;

	err = nft_रेजिस्टर_obj(&nft_tunnel_obj_type);
	अगर (err < 0)
		nft_unरेजिस्टर_expr(&nft_tunnel_type);

	वापस err;
पूर्ण

अटल व्योम __निकास nft_tunnel_module_निकास(व्योम)
अणु
	nft_unरेजिस्टर_obj(&nft_tunnel_obj_type);
	nft_unरेजिस्टर_expr(&nft_tunnel_type);
पूर्ण

module_init(nft_tunnel_module_init);
module_निकास(nft_tunnel_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pablo Neira Ayuso <pablo@netfilter.org>");
MODULE_ALIAS_NFT_EXPR("tunnel");
MODULE_ALIAS_NFT_OBJ(NFT_OBJECT_TUNNEL);
MODULE_DESCRIPTION("nftables tunnel expression support");
