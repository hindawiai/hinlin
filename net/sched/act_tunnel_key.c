<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016, Amir Vadai <amir@vadai.me>
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/geneve.h>
#समावेश <net/vxlan.h>
#समावेश <net/erspan.h>
#समावेश <net/netlink.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/dst.h>
#समावेश <net/pkt_cls.h>

#समावेश <linux/tc_act/tc_tunnel_key.h>
#समावेश <net/tc_act/tc_tunnel_key.h>

अटल अचिन्हित पूर्णांक tunnel_key_net_id;
अटल काष्ठा tc_action_ops act_tunnel_key_ops;

अटल पूर्णांक tunnel_key_act(काष्ठा sk_buff *skb, स्थिर काष्ठा tc_action *a,
			  काष्ठा tcf_result *res)
अणु
	काष्ठा tcf_tunnel_key *t = to_tunnel_key(a);
	काष्ठा tcf_tunnel_key_params *params;
	पूर्णांक action;

	params = rcu_dereference_bh(t->params);

	tcf_lastuse_update(&t->tcf_पंचांग);
	tcf_action_update_bstats(&t->common, skb);
	action = READ_ONCE(t->tcf_action);

	चयन (params->tcft_action) अणु
	हाल TCA_TUNNEL_KEY_ACT_RELEASE:
		skb_dst_drop(skb);
		अवरोध;
	हाल TCA_TUNNEL_KEY_ACT_SET:
		skb_dst_drop(skb);
		skb_dst_set(skb, dst_clone(&params->tcft_enc_metadata->dst));
		अवरोध;
	शेष:
		WARN_ONCE(1, "Bad tunnel_key action %d.\n",
			  params->tcft_action);
		अवरोध;
	पूर्ण

	वापस action;
पूर्ण

अटल स्थिर काष्ठा nla_policy
enc_opts_policy[TCA_TUNNEL_KEY_ENC_OPTS_MAX + 1] = अणु
	[TCA_TUNNEL_KEY_ENC_OPTS_UNSPEC]	= अणु
		.strict_start_type = TCA_TUNNEL_KEY_ENC_OPTS_VXLAN पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPTS_GENEVE]	= अणु .type = NLA_NESTED पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPTS_VXLAN]		= अणु .type = NLA_NESTED पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPTS_ERSPAN]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
geneve_opt_policy[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX + 1] = अणु
	[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS]	   = अणु .type = NLA_U16 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE]	   = अणु .type = NLA_U8 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA]	   = अणु .type = NLA_BINARY,
						       .len = 128 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
vxlan_opt_policy[TCA_TUNNEL_KEY_ENC_OPT_VXLAN_MAX + 1] = अणु
	[TCA_TUNNEL_KEY_ENC_OPT_VXLAN_GBP]	   = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
erspan_opt_policy[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_MAX + 1] = अणु
	[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_VER]	   = अणु .type = NLA_U8 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_INDEX]	   = अणु .type = NLA_U32 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_सूची]	   = अणु .type = NLA_U8 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_HWID]	   = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक
tunnel_key_copy_geneve_opt(स्थिर काष्ठा nlattr *nla, व्योम *dst, पूर्णांक dst_len,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX + 1];
	पूर्णांक err, data_len, opt_len;
	u8 *data;

	err = nla_parse_nested_deprecated(tb,
					  TCA_TUNNEL_KEY_ENC_OPT_GENEVE_MAX,
					  nla, geneve_opt_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS] ||
	    !tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE] ||
	    !tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA]) अणु
		NL_SET_ERR_MSG(extack, "Missing tunnel key geneve option class, type or data");
		वापस -EINVAL;
	पूर्ण

	data = nla_data(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA]);
	data_len = nla_len(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA]);
	अगर (data_len < 4) अणु
		NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is less than 4 bytes long");
		वापस -दुस्फल;
	पूर्ण
	अगर (data_len % 4) अणु
		NL_SET_ERR_MSG(extack, "Tunnel key geneve option data is not a multiple of 4 bytes long");
		वापस -दुस्फल;
	पूर्ण

	opt_len = माप(काष्ठा geneve_opt) + data_len;
	अगर (dst) अणु
		काष्ठा geneve_opt *opt = dst;

		WARN_ON(dst_len < opt_len);

		opt->opt_class =
			nla_get_be16(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS]);
		opt->type = nla_get_u8(tb[TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE]);
		opt->length = data_len / 4; /* length is in units of 4 bytes */
		opt->r1 = 0;
		opt->r2 = 0;
		opt->r3 = 0;

		स_नकल(opt + 1, data, data_len);
	पूर्ण

	वापस opt_len;
पूर्ण

अटल पूर्णांक
tunnel_key_copy_vxlan_opt(स्थिर काष्ठा nlattr *nla, व्योम *dst, पूर्णांक dst_len,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_TUNNEL_KEY_ENC_OPT_VXLAN_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested(tb, TCA_TUNNEL_KEY_ENC_OPT_VXLAN_MAX, nla,
			       vxlan_opt_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_TUNNEL_KEY_ENC_OPT_VXLAN_GBP]) अणु
		NL_SET_ERR_MSG(extack, "Missing tunnel key vxlan option gbp");
		वापस -EINVAL;
	पूर्ण

	अगर (dst) अणु
		काष्ठा vxlan_metadata *md = dst;

		md->gbp = nla_get_u32(tb[TCA_TUNNEL_KEY_ENC_OPT_VXLAN_GBP]);
		md->gbp &= VXLAN_GBP_MASK;
	पूर्ण

	वापस माप(काष्ठा vxlan_metadata);
पूर्ण

अटल पूर्णांक
tunnel_key_copy_erspan_opt(स्थिर काष्ठा nlattr *nla, व्योम *dst, पूर्णांक dst_len,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_MAX + 1];
	पूर्णांक err;
	u8 ver;

	err = nla_parse_nested(tb, TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_MAX, nla,
			       erspan_opt_policy, extack);
	अगर (err < 0)
		वापस err;

	अगर (!tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_VER]) अणु
		NL_SET_ERR_MSG(extack, "Missing tunnel key erspan option ver");
		वापस -EINVAL;
	पूर्ण

	ver = nla_get_u8(tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_VER]);
	अगर (ver == 1) अणु
		अगर (!tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_INDEX]) अणु
			NL_SET_ERR_MSG(extack, "Missing tunnel key erspan option index");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (ver == 2) अणु
		अगर (!tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_सूची] ||
		    !tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_HWID]) अणु
			NL_SET_ERR_MSG(extack, "Missing tunnel key erspan option dir or hwid");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG(extack, "Tunnel key erspan option ver is incorrect");
		वापस -EINVAL;
	पूर्ण

	अगर (dst) अणु
		काष्ठा erspan_metadata *md = dst;

		md->version = ver;
		अगर (ver == 1) अणु
			nla = tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_INDEX];
			md->u.index = nla_get_be32(nla);
		पूर्ण अन्यथा अणु
			nla = tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_सूची];
			md->u.md2.dir = nla_get_u8(nla);
			nla = tb[TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_HWID];
			set_hwid(&md->u.md2, nla_get_u8(nla));
		पूर्ण
	पूर्ण

	वापस माप(काष्ठा erspan_metadata);
पूर्ण

अटल पूर्णांक tunnel_key_copy_opts(स्थिर काष्ठा nlattr *nla, u8 *dst,
				पूर्णांक dst_len, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err, rem, opt_len, len = nla_len(nla), opts_len = 0, type = 0;
	स्थिर काष्ठा nlattr *attr, *head = nla_data(nla);

	err = nla_validate_deprecated(head, len, TCA_TUNNEL_KEY_ENC_OPTS_MAX,
				      enc_opts_policy, extack);
	अगर (err)
		वापस err;

	nla_क्रम_each_attr(attr, head, len, rem) अणु
		चयन (nla_type(attr)) अणु
		हाल TCA_TUNNEL_KEY_ENC_OPTS_GENEVE:
			अगर (type && type != TUNNEL_GENEVE_OPT) अणु
				NL_SET_ERR_MSG(extack, "Duplicate type for geneve options");
				वापस -EINVAL;
			पूर्ण
			opt_len = tunnel_key_copy_geneve_opt(attr, dst,
							     dst_len, extack);
			अगर (opt_len < 0)
				वापस opt_len;
			opts_len += opt_len;
			अगर (opts_len > IP_TUNNEL_OPTS_MAX) अणु
				NL_SET_ERR_MSG(extack, "Tunnel options exceeds max size");
				वापस -EINVAL;
			पूर्ण
			अगर (dst) अणु
				dst_len -= opt_len;
				dst += opt_len;
			पूर्ण
			type = TUNNEL_GENEVE_OPT;
			अवरोध;
		हाल TCA_TUNNEL_KEY_ENC_OPTS_VXLAN:
			अगर (type) अणु
				NL_SET_ERR_MSG(extack, "Duplicate type for vxlan options");
				वापस -EINVAL;
			पूर्ण
			opt_len = tunnel_key_copy_vxlan_opt(attr, dst,
							    dst_len, extack);
			अगर (opt_len < 0)
				वापस opt_len;
			opts_len += opt_len;
			type = TUNNEL_VXLAN_OPT;
			अवरोध;
		हाल TCA_TUNNEL_KEY_ENC_OPTS_ERSPAN:
			अगर (type) अणु
				NL_SET_ERR_MSG(extack, "Duplicate type for erspan options");
				वापस -EINVAL;
			पूर्ण
			opt_len = tunnel_key_copy_erspan_opt(attr, dst,
							     dst_len, extack);
			अगर (opt_len < 0)
				वापस opt_len;
			opts_len += opt_len;
			type = TUNNEL_ERSPAN_OPT;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!opts_len) अणु
		NL_SET_ERR_MSG(extack, "Empty list of tunnel options");
		वापस -EINVAL;
	पूर्ण

	अगर (rem > 0) अणु
		NL_SET_ERR_MSG(extack, "Trailing data after parsing tunnel key options attributes");
		वापस -EINVAL;
	पूर्ण

	वापस opts_len;
पूर्ण

अटल पूर्णांक tunnel_key_get_opts_len(काष्ठा nlattr *nla,
				   काष्ठा netlink_ext_ack *extack)
अणु
	वापस tunnel_key_copy_opts(nla, शून्य, 0, extack);
पूर्ण

अटल पूर्णांक tunnel_key_opts_set(काष्ठा nlattr *nla, काष्ठा ip_tunnel_info *info,
			       पूर्णांक opts_len, काष्ठा netlink_ext_ack *extack)
अणु
	info->options_len = opts_len;
	चयन (nla_type(nla_data(nla))) अणु
	हाल TCA_TUNNEL_KEY_ENC_OPTS_GENEVE:
#अगर IS_ENABLED(CONFIG_INET)
		info->key.tun_flags |= TUNNEL_GENEVE_OPT;
		वापस tunnel_key_copy_opts(nla, ip_tunnel_info_opts(info),
					    opts_len, extack);
#अन्यथा
		वापस -EAFNOSUPPORT;
#पूर्ण_अगर
	हाल TCA_TUNNEL_KEY_ENC_OPTS_VXLAN:
#अगर IS_ENABLED(CONFIG_INET)
		info->key.tun_flags |= TUNNEL_VXLAN_OPT;
		वापस tunnel_key_copy_opts(nla, ip_tunnel_info_opts(info),
					    opts_len, extack);
#अन्यथा
		वापस -EAFNOSUPPORT;
#पूर्ण_अगर
	हाल TCA_TUNNEL_KEY_ENC_OPTS_ERSPAN:
#अगर IS_ENABLED(CONFIG_INET)
		info->key.tun_flags |= TUNNEL_ERSPAN_OPT;
		वापस tunnel_key_copy_opts(nla, ip_tunnel_info_opts(info),
					    opts_len, extack);
#अन्यथा
		वापस -EAFNOSUPPORT;
#पूर्ण_अगर
	शेष:
		NL_SET_ERR_MSG(extack, "Cannot set tunnel options for unknown tunnel type");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nla_policy tunnel_key_policy[TCA_TUNNEL_KEY_MAX + 1] = अणु
	[TCA_TUNNEL_KEY_PARMS]	    = अणु .len = माप(काष्ठा tc_tunnel_key) पूर्ण,
	[TCA_TUNNEL_KEY_ENC_IPV4_SRC] = अणु .type = NLA_U32 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_IPV4_DST] = अणु .type = NLA_U32 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_IPV6_SRC] = अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_TUNNEL_KEY_ENC_IPV6_DST] = अणु .len = माप(काष्ठा in6_addr) पूर्ण,
	[TCA_TUNNEL_KEY_ENC_KEY_ID]   = अणु .type = NLA_U32 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_DST_PORT] = अणु.type = NLA_U16पूर्ण,
	[TCA_TUNNEL_KEY_NO_CSUM]      = अणु .type = NLA_U8 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_OPTS]     = अणु .type = NLA_NESTED पूर्ण,
	[TCA_TUNNEL_KEY_ENC_TOS]      = अणु .type = NLA_U8 पूर्ण,
	[TCA_TUNNEL_KEY_ENC_TTL]      = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल व्योम tunnel_key_release_params(काष्ठा tcf_tunnel_key_params *p)
अणु
	अगर (!p)
		वापस;
	अगर (p->tcft_action == TCA_TUNNEL_KEY_ACT_SET)
		dst_release(&p->tcft_enc_metadata->dst);

	kमुक्त_rcu(p, rcu);
पूर्ण

अटल पूर्णांक tunnel_key_init(काष्ठा net *net, काष्ठा nlattr *nla,
			   काष्ठा nlattr *est, काष्ठा tc_action **a,
			   पूर्णांक ovr, पूर्णांक bind, bool rtnl_held,
			   काष्ठा tcf_proto *tp, u32 act_flags,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, tunnel_key_net_id);
	काष्ठा nlattr *tb[TCA_TUNNEL_KEY_MAX + 1];
	काष्ठा tcf_tunnel_key_params *params_new;
	काष्ठा metadata_dst *metadata = शून्य;
	काष्ठा tcf_chain *जाओ_ch = शून्य;
	काष्ठा tc_tunnel_key *parm;
	काष्ठा tcf_tunnel_key *t;
	bool exists = false;
	__be16 dst_port = 0;
	__be64 key_id = 0;
	पूर्णांक opts_len = 0;
	__be16 flags = 0;
	u8 tos, ttl;
	पूर्णांक ret = 0;
	u32 index;
	पूर्णांक err;

	अगर (!nla) अणु
		NL_SET_ERR_MSG(extack, "Tunnel requires attributes to be passed");
		वापस -EINVAL;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, TCA_TUNNEL_KEY_MAX, nla,
					  tunnel_key_policy, extack);
	अगर (err < 0) अणु
		NL_SET_ERR_MSG(extack, "Failed to parse nested tunnel key attributes");
		वापस err;
	पूर्ण

	अगर (!tb[TCA_TUNNEL_KEY_PARMS]) अणु
		NL_SET_ERR_MSG(extack, "Missing tunnel key parameters");
		वापस -EINVAL;
	पूर्ण

	parm = nla_data(tb[TCA_TUNNEL_KEY_PARMS]);
	index = parm->index;
	err = tcf_idr_check_alloc(tn, &index, a, bind);
	अगर (err < 0)
		वापस err;
	exists = err;
	अगर (exists && bind)
		वापस 0;

	चयन (parm->t_action) अणु
	हाल TCA_TUNNEL_KEY_ACT_RELEASE:
		अवरोध;
	हाल TCA_TUNNEL_KEY_ACT_SET:
		अगर (tb[TCA_TUNNEL_KEY_ENC_KEY_ID]) अणु
			__be32 key32;

			key32 = nla_get_be32(tb[TCA_TUNNEL_KEY_ENC_KEY_ID]);
			key_id = key32_to_tunnel_id(key32);
			flags = TUNNEL_KEY;
		पूर्ण

		flags |= TUNNEL_CSUM;
		अगर (tb[TCA_TUNNEL_KEY_NO_CSUM] &&
		    nla_get_u8(tb[TCA_TUNNEL_KEY_NO_CSUM]))
			flags &= ~TUNNEL_CSUM;

		अगर (tb[TCA_TUNNEL_KEY_ENC_DST_PORT])
			dst_port = nla_get_be16(tb[TCA_TUNNEL_KEY_ENC_DST_PORT]);

		अगर (tb[TCA_TUNNEL_KEY_ENC_OPTS]) अणु
			opts_len = tunnel_key_get_opts_len(tb[TCA_TUNNEL_KEY_ENC_OPTS],
							   extack);
			अगर (opts_len < 0) अणु
				ret = opts_len;
				जाओ err_out;
			पूर्ण
		पूर्ण

		tos = 0;
		अगर (tb[TCA_TUNNEL_KEY_ENC_TOS])
			tos = nla_get_u8(tb[TCA_TUNNEL_KEY_ENC_TOS]);
		ttl = 0;
		अगर (tb[TCA_TUNNEL_KEY_ENC_TTL])
			ttl = nla_get_u8(tb[TCA_TUNNEL_KEY_ENC_TTL]);

		अगर (tb[TCA_TUNNEL_KEY_ENC_IPV4_SRC] &&
		    tb[TCA_TUNNEL_KEY_ENC_IPV4_DST]) अणु
			__be32 saddr;
			__be32 daddr;

			saddr = nla_get_in_addr(tb[TCA_TUNNEL_KEY_ENC_IPV4_SRC]);
			daddr = nla_get_in_addr(tb[TCA_TUNNEL_KEY_ENC_IPV4_DST]);

			metadata = __ip_tun_set_dst(saddr, daddr, tos, ttl,
						    dst_port, flags,
						    key_id, opts_len);
		पूर्ण अन्यथा अगर (tb[TCA_TUNNEL_KEY_ENC_IPV6_SRC] &&
			   tb[TCA_TUNNEL_KEY_ENC_IPV6_DST]) अणु
			काष्ठा in6_addr saddr;
			काष्ठा in6_addr daddr;

			saddr = nla_get_in6_addr(tb[TCA_TUNNEL_KEY_ENC_IPV6_SRC]);
			daddr = nla_get_in6_addr(tb[TCA_TUNNEL_KEY_ENC_IPV6_DST]);

			metadata = __ipv6_tun_set_dst(&saddr, &daddr, tos, ttl, dst_port,
						      0, flags,
						      key_id, opts_len);
		पूर्ण अन्यथा अणु
			NL_SET_ERR_MSG(extack, "Missing either ipv4 or ipv6 src and dst");
			ret = -EINVAL;
			जाओ err_out;
		पूर्ण

		अगर (!metadata) अणु
			NL_SET_ERR_MSG(extack, "Cannot allocate tunnel metadata dst");
			ret = -ENOMEM;
			जाओ err_out;
		पूर्ण

#अगर_घोषित CONFIG_DST_CACHE
		ret = dst_cache_init(&metadata->u.tun_info.dst_cache, GFP_KERNEL);
		अगर (ret)
			जाओ release_tun_meta;
#पूर्ण_अगर

		अगर (opts_len) अणु
			ret = tunnel_key_opts_set(tb[TCA_TUNNEL_KEY_ENC_OPTS],
						  &metadata->u.tun_info,
						  opts_len, extack);
			अगर (ret < 0)
				जाओ release_tun_meta;
		पूर्ण

		metadata->u.tun_info.mode |= IP_TUNNEL_INFO_TX;
		अवरोध;
	शेष:
		NL_SET_ERR_MSG(extack, "Unknown tunnel key action");
		ret = -EINVAL;
		जाओ err_out;
	पूर्ण

	अगर (!exists) अणु
		ret = tcf_idr_create_from_flags(tn, index, est, a,
						&act_tunnel_key_ops, bind,
						act_flags);
		अगर (ret) अणु
			NL_SET_ERR_MSG(extack, "Cannot create TC IDR");
			जाओ release_tun_meta;
		पूर्ण

		ret = ACT_P_CREATED;
	पूर्ण अन्यथा अगर (!ovr) अणु
		NL_SET_ERR_MSG(extack, "TC IDR already exists");
		ret = -EEXIST;
		जाओ release_tun_meta;
	पूर्ण

	err = tcf_action_check_ctrlact(parm->action, tp, &जाओ_ch, extack);
	अगर (err < 0) अणु
		ret = err;
		exists = true;
		जाओ release_tun_meta;
	पूर्ण
	t = to_tunnel_key(*a);

	params_new = kzalloc(माप(*params_new), GFP_KERNEL);
	अगर (unlikely(!params_new)) अणु
		NL_SET_ERR_MSG(extack, "Cannot allocate tunnel key parameters");
		ret = -ENOMEM;
		exists = true;
		जाओ put_chain;
	पूर्ण
	params_new->tcft_action = parm->t_action;
	params_new->tcft_enc_metadata = metadata;

	spin_lock_bh(&t->tcf_lock);
	जाओ_ch = tcf_action_set_ctrlact(*a, parm->action, जाओ_ch);
	params_new = rcu_replace_poपूर्णांकer(t->params, params_new,
					 lockdep_is_held(&t->tcf_lock));
	spin_unlock_bh(&t->tcf_lock);
	tunnel_key_release_params(params_new);
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

	वापस ret;

put_chain:
	अगर (जाओ_ch)
		tcf_chain_put_by_act(जाओ_ch);

release_tun_meta:
	अगर (metadata)
		dst_release(&metadata->dst);

err_out:
	अगर (exists)
		tcf_idr_release(*a, bind);
	अन्यथा
		tcf_idr_cleanup(tn, index);
	वापस ret;
पूर्ण

अटल व्योम tunnel_key_release(काष्ठा tc_action *a)
अणु
	काष्ठा tcf_tunnel_key *t = to_tunnel_key(a);
	काष्ठा tcf_tunnel_key_params *params;

	params = rcu_dereference_रक्षित(t->params, 1);
	tunnel_key_release_params(params);
पूर्ण

अटल पूर्णांक tunnel_key_geneve_opts_dump(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा ip_tunnel_info *info)
अणु
	पूर्णांक len = info->options_len;
	u8 *src = (u8 *)(info + 1);
	काष्ठा nlattr *start;

	start = nla_nest_start_noflag(skb, TCA_TUNNEL_KEY_ENC_OPTS_GENEVE);
	अगर (!start)
		वापस -EMSGSIZE;

	जबतक (len > 0) अणु
		काष्ठा geneve_opt *opt = (काष्ठा geneve_opt *)src;

		अगर (nla_put_be16(skb, TCA_TUNNEL_KEY_ENC_OPT_GENEVE_CLASS,
				 opt->opt_class) ||
		    nla_put_u8(skb, TCA_TUNNEL_KEY_ENC_OPT_GENEVE_TYPE,
			       opt->type) ||
		    nla_put(skb, TCA_TUNNEL_KEY_ENC_OPT_GENEVE_DATA,
			    opt->length * 4, opt + 1)) अणु
			nla_nest_cancel(skb, start);
			वापस -EMSGSIZE;
		पूर्ण

		len -= माप(काष्ठा geneve_opt) + opt->length * 4;
		src += माप(काष्ठा geneve_opt) + opt->length * 4;
	पूर्ण

	nla_nest_end(skb, start);
	वापस 0;
पूर्ण

अटल पूर्णांक tunnel_key_vxlan_opts_dump(काष्ठा sk_buff *skb,
				      स्थिर काष्ठा ip_tunnel_info *info)
अणु
	काष्ठा vxlan_metadata *md = (काष्ठा vxlan_metadata *)(info + 1);
	काष्ठा nlattr *start;

	start = nla_nest_start_noflag(skb, TCA_TUNNEL_KEY_ENC_OPTS_VXLAN);
	अगर (!start)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, TCA_TUNNEL_KEY_ENC_OPT_VXLAN_GBP, md->gbp)) अणु
		nla_nest_cancel(skb, start);
		वापस -EMSGSIZE;
	पूर्ण

	nla_nest_end(skb, start);
	वापस 0;
पूर्ण

अटल पूर्णांक tunnel_key_erspan_opts_dump(काष्ठा sk_buff *skb,
				       स्थिर काष्ठा ip_tunnel_info *info)
अणु
	काष्ठा erspan_metadata *md = (काष्ठा erspan_metadata *)(info + 1);
	काष्ठा nlattr *start;

	start = nla_nest_start_noflag(skb, TCA_TUNNEL_KEY_ENC_OPTS_ERSPAN);
	अगर (!start)
		वापस -EMSGSIZE;

	अगर (nla_put_u8(skb, TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_VER, md->version))
		जाओ err;

	अगर (md->version == 1 &&
	    nla_put_be32(skb, TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_INDEX, md->u.index))
		जाओ err;

	अगर (md->version == 2 &&
	    (nla_put_u8(skb, TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_सूची,
			md->u.md2.dir) ||
	     nla_put_u8(skb, TCA_TUNNEL_KEY_ENC_OPT_ERSPAN_HWID,
			get_hwid(&md->u.md2))))
		जाओ err;

	nla_nest_end(skb, start);
	वापस 0;
err:
	nla_nest_cancel(skb, start);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक tunnel_key_opts_dump(काष्ठा sk_buff *skb,
				स्थिर काष्ठा ip_tunnel_info *info)
अणु
	काष्ठा nlattr *start;
	पूर्णांक err = -EINVAL;

	अगर (!info->options_len)
		वापस 0;

	start = nla_nest_start_noflag(skb, TCA_TUNNEL_KEY_ENC_OPTS);
	अगर (!start)
		वापस -EMSGSIZE;

	अगर (info->key.tun_flags & TUNNEL_GENEVE_OPT) अणु
		err = tunnel_key_geneve_opts_dump(skb, info);
		अगर (err)
			जाओ err_out;
	पूर्ण अन्यथा अगर (info->key.tun_flags & TUNNEL_VXLAN_OPT) अणु
		err = tunnel_key_vxlan_opts_dump(skb, info);
		अगर (err)
			जाओ err_out;
	पूर्ण अन्यथा अगर (info->key.tun_flags & TUNNEL_ERSPAN_OPT) अणु
		err = tunnel_key_erspan_opts_dump(skb, info);
		अगर (err)
			जाओ err_out;
	पूर्ण अन्यथा अणु
err_out:
		nla_nest_cancel(skb, start);
		वापस err;
	पूर्ण

	nla_nest_end(skb, start);
	वापस 0;
पूर्ण

अटल पूर्णांक tunnel_key_dump_addresses(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा ip_tunnel_info *info)
अणु
	अचिन्हित लघु family = ip_tunnel_info_af(info);

	अगर (family == AF_INET) अणु
		__be32 saddr = info->key.u.ipv4.src;
		__be32 daddr = info->key.u.ipv4.dst;

		अगर (!nla_put_in_addr(skb, TCA_TUNNEL_KEY_ENC_IPV4_SRC, saddr) &&
		    !nla_put_in_addr(skb, TCA_TUNNEL_KEY_ENC_IPV4_DST, daddr))
			वापस 0;
	पूर्ण

	अगर (family == AF_INET6) अणु
		स्थिर काष्ठा in6_addr *saddr6 = &info->key.u.ipv6.src;
		स्थिर काष्ठा in6_addr *daddr6 = &info->key.u.ipv6.dst;

		अगर (!nla_put_in6_addr(skb,
				      TCA_TUNNEL_KEY_ENC_IPV6_SRC, saddr6) &&
		    !nla_put_in6_addr(skb,
				      TCA_TUNNEL_KEY_ENC_IPV6_DST, daddr6))
			वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tunnel_key_dump(काष्ठा sk_buff *skb, काष्ठा tc_action *a,
			   पूर्णांक bind, पूर्णांक ref)
अणु
	अचिन्हित अक्षर *b = skb_tail_poपूर्णांकer(skb);
	काष्ठा tcf_tunnel_key *t = to_tunnel_key(a);
	काष्ठा tcf_tunnel_key_params *params;
	काष्ठा tc_tunnel_key opt = अणु
		.index    = t->tcf_index,
		.refcnt   = refcount_पढ़ो(&t->tcf_refcnt) - ref,
		.bindcnt  = atomic_पढ़ो(&t->tcf_bindcnt) - bind,
	पूर्ण;
	काष्ठा tcf_t पंचांग;

	spin_lock_bh(&t->tcf_lock);
	params = rcu_dereference_रक्षित(t->params,
					   lockdep_is_held(&t->tcf_lock));
	opt.action   = t->tcf_action;
	opt.t_action = params->tcft_action;

	अगर (nla_put(skb, TCA_TUNNEL_KEY_PARMS, माप(opt), &opt))
		जाओ nla_put_failure;

	अगर (params->tcft_action == TCA_TUNNEL_KEY_ACT_SET) अणु
		काष्ठा ip_tunnel_info *info =
			&params->tcft_enc_metadata->u.tun_info;
		काष्ठा ip_tunnel_key *key = &info->key;
		__be32 key_id = tunnel_id_to_key32(key->tun_id);

		अगर (((key->tun_flags & TUNNEL_KEY) &&
		     nla_put_be32(skb, TCA_TUNNEL_KEY_ENC_KEY_ID, key_id)) ||
		    tunnel_key_dump_addresses(skb,
					      &params->tcft_enc_metadata->u.tun_info) ||
		    (key->tp_dst &&
		      nla_put_be16(skb, TCA_TUNNEL_KEY_ENC_DST_PORT,
				   key->tp_dst)) ||
		    nla_put_u8(skb, TCA_TUNNEL_KEY_NO_CSUM,
			       !(key->tun_flags & TUNNEL_CSUM)) ||
		    tunnel_key_opts_dump(skb, info))
			जाओ nla_put_failure;

		अगर (key->tos && nla_put_u8(skb, TCA_TUNNEL_KEY_ENC_TOS, key->tos))
			जाओ nla_put_failure;

		अगर (key->ttl && nla_put_u8(skb, TCA_TUNNEL_KEY_ENC_TTL, key->ttl))
			जाओ nla_put_failure;
	पूर्ण

	tcf_पंचांग_dump(&पंचांग, &t->tcf_पंचांग);
	अगर (nla_put_64bit(skb, TCA_TUNNEL_KEY_TM, माप(पंचांग),
			  &पंचांग, TCA_TUNNEL_KEY_PAD))
		जाओ nla_put_failure;
	spin_unlock_bh(&t->tcf_lock);

	वापस skb->len;

nla_put_failure:
	spin_unlock_bh(&t->tcf_lock);
	nlmsg_trim(skb, b);
	वापस -1;
पूर्ण

अटल पूर्णांक tunnel_key_walker(काष्ठा net *net, काष्ठा sk_buff *skb,
			     काष्ठा netlink_callback *cb, पूर्णांक type,
			     स्थिर काष्ठा tc_action_ops *ops,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, tunnel_key_net_id);

	वापस tcf_generic_walker(tn, skb, cb, type, ops, extack);
पूर्ण

अटल पूर्णांक tunnel_key_search(काष्ठा net *net, काष्ठा tc_action **a, u32 index)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, tunnel_key_net_id);

	वापस tcf_idr_search(tn, a, index);
पूर्ण

अटल काष्ठा tc_action_ops act_tunnel_key_ops = अणु
	.kind		=	"tunnel_key",
	.id		=	TCA_ID_TUNNEL_KEY,
	.owner		=	THIS_MODULE,
	.act		=	tunnel_key_act,
	.dump		=	tunnel_key_dump,
	.init		=	tunnel_key_init,
	.cleanup	=	tunnel_key_release,
	.walk		=	tunnel_key_walker,
	.lookup		=	tunnel_key_search,
	.size		=	माप(काष्ठा tcf_tunnel_key),
पूर्ण;

अटल __net_init पूर्णांक tunnel_key_init_net(काष्ठा net *net)
अणु
	काष्ठा tc_action_net *tn = net_generic(net, tunnel_key_net_id);

	वापस tc_action_net_init(net, tn, &act_tunnel_key_ops);
पूर्ण

अटल व्योम __net_निकास tunnel_key_निकास_net(काष्ठा list_head *net_list)
अणु
	tc_action_net_निकास(net_list, tunnel_key_net_id);
पूर्ण

अटल काष्ठा pernet_operations tunnel_key_net_ops = अणु
	.init = tunnel_key_init_net,
	.निकास_batch = tunnel_key_निकास_net,
	.id   = &tunnel_key_net_id,
	.size = माप(काष्ठा tc_action_net),
पूर्ण;

अटल पूर्णांक __init tunnel_key_init_module(व्योम)
अणु
	वापस tcf_रेजिस्टर_action(&act_tunnel_key_ops, &tunnel_key_net_ops);
पूर्ण

अटल व्योम __निकास tunnel_key_cleanup_module(व्योम)
अणु
	tcf_unरेजिस्टर_action(&act_tunnel_key_ops, &tunnel_key_net_ops);
पूर्ण

module_init(tunnel_key_init_module);
module_निकास(tunnel_key_cleanup_module);

MODULE_AUTHOR("Amir Vadai <amir@vadai.me>");
MODULE_DESCRIPTION("ip tunnel manipulation actions");
MODULE_LICENSE("GPL v2");
