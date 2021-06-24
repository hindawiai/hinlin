<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  SR-IPv6 implementation
 *
 *  Author:
 *  David Lebrun <david.lebrun@uclouvain.be>
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/net.h>
#समावेश <linux/in6.h>
#समावेश <linux/slab.h>
#समावेश <linux/rhashtable.h>

#समावेश <net/ipv6.h>
#समावेश <net/protocol.h>

#समावेश <net/seg6.h>
#समावेश <net/genetlink.h>
#समावेश <linux/seg6.h>
#समावेश <linux/seg6_genl.h>
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
#समावेश <net/seg6_hmac.h>
#पूर्ण_अगर

bool seg6_validate_srh(काष्ठा ipv6_sr_hdr *srh, पूर्णांक len, bool reduced)
अणु
	अचिन्हित पूर्णांक tlv_offset;
	पूर्णांक max_last_entry;
	पूर्णांक trailing;

	अगर (srh->type != IPV6_SRCRT_TYPE_4)
		वापस false;

	अगर (((srh->hdrlen + 1) << 3) != len)
		वापस false;

	अगर (!reduced && srh->segments_left > srh->first_segment) अणु
		वापस false;
	पूर्ण अन्यथा अणु
		max_last_entry = (srh->hdrlen / 2) - 1;

		अगर (srh->first_segment > max_last_entry)
			वापस false;

		अगर (srh->segments_left > srh->first_segment + 1)
			वापस false;
	पूर्ण

	tlv_offset = माप(*srh) + ((srh->first_segment + 1) << 4);

	trailing = len - tlv_offset;
	अगर (trailing < 0)
		वापस false;

	जबतक (trailing) अणु
		काष्ठा sr6_tlv *tlv;
		अचिन्हित पूर्णांक tlv_len;

		अगर (trailing < माप(*tlv))
			वापस false;

		tlv = (काष्ठा sr6_tlv *)((अचिन्हित अक्षर *)srh + tlv_offset);
		tlv_len = माप(*tlv) + tlv->len;

		trailing -= tlv_len;
		अगर (trailing < 0)
			वापस false;

		tlv_offset += tlv_len;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा genl_family seg6_genl_family;

अटल स्थिर काष्ठा nla_policy seg6_genl_policy[SEG6_ATTR_MAX + 1] = अणु
	[SEG6_ATTR_DST]				= अणु .type = NLA_BINARY,
		.len = माप(काष्ठा in6_addr) पूर्ण,
	[SEG6_ATTR_DSTLEN]			= अणु .type = NLA_S32, पूर्ण,
	[SEG6_ATTR_HMACKEYID]		= अणु .type = NLA_U32, पूर्ण,
	[SEG6_ATTR_SECRET]			= अणु .type = NLA_BINARY, पूर्ण,
	[SEG6_ATTR_SECRETLEN]		= अणु .type = NLA_U8, पूर्ण,
	[SEG6_ATTR_ALGID]			= अणु .type = NLA_U8, पूर्ण,
	[SEG6_ATTR_HMACINFO]		= अणु .type = NLA_NESTED, पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC

अटल पूर्णांक seg6_genl_sethmac(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा seg6_pernet_data *sdata;
	काष्ठा seg6_hmac_info *hinfo;
	u32 hmackeyid;
	अक्षर *secret;
	पूर्णांक err = 0;
	u8 algid;
	u8 slen;

	sdata = seg6_pernet(net);

	अगर (!info->attrs[SEG6_ATTR_HMACKEYID] ||
	    !info->attrs[SEG6_ATTR_SECRETLEN] ||
	    !info->attrs[SEG6_ATTR_ALGID])
		वापस -EINVAL;

	hmackeyid = nla_get_u32(info->attrs[SEG6_ATTR_HMACKEYID]);
	slen = nla_get_u8(info->attrs[SEG6_ATTR_SECRETLEN]);
	algid = nla_get_u8(info->attrs[SEG6_ATTR_ALGID]);

	अगर (hmackeyid == 0)
		वापस -EINVAL;

	अगर (slen > SEG6_HMAC_SECRET_LEN)
		वापस -EINVAL;

	mutex_lock(&sdata->lock);
	hinfo = seg6_hmac_info_lookup(net, hmackeyid);

	अगर (!slen) अणु
		err = seg6_hmac_info_del(net, hmackeyid);

		जाओ out_unlock;
	पूर्ण

	अगर (!info->attrs[SEG6_ATTR_SECRET]) अणु
		err = -EINVAL;
		जाओ out_unlock;
	पूर्ण

	अगर (hinfo) अणु
		err = seg6_hmac_info_del(net, hmackeyid);
		अगर (err)
			जाओ out_unlock;
	पूर्ण

	secret = (अक्षर *)nla_data(info->attrs[SEG6_ATTR_SECRET]);

	hinfo = kzalloc(माप(*hinfo), GFP_KERNEL);
	अगर (!hinfo) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	स_नकल(hinfo->secret, secret, slen);
	hinfo->slen = slen;
	hinfo->alg_id = algid;
	hinfo->hmackeyid = hmackeyid;

	err = seg6_hmac_info_add(net, hmackeyid, hinfo);
	अगर (err)
		kमुक्त(hinfo);

out_unlock:
	mutex_unlock(&sdata->lock);
	वापस err;
पूर्ण

#अन्यथा

अटल पूर्णांक seg6_genl_sethmac(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस -ENOTSUPP;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक seg6_genl_set_tunsrc(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा in6_addr *val, *t_old, *t_new;
	काष्ठा seg6_pernet_data *sdata;

	sdata = seg6_pernet(net);

	अगर (!info->attrs[SEG6_ATTR_DST])
		वापस -EINVAL;

	val = nla_data(info->attrs[SEG6_ATTR_DST]);
	t_new = kmemdup(val, माप(*val), GFP_KERNEL);
	अगर (!t_new)
		वापस -ENOMEM;

	mutex_lock(&sdata->lock);

	t_old = sdata->tun_src;
	rcu_assign_poपूर्णांकer(sdata->tun_src, t_new);

	mutex_unlock(&sdata->lock);

	synchronize_net();
	kमुक्त(t_old);

	वापस 0;
पूर्ण

अटल पूर्णांक seg6_genl_get_tunsrc(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा net *net = genl_info_net(info);
	काष्ठा in6_addr *tun_src;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = genlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			  &seg6_genl_family, 0, SEG6_CMD_GET_TUNSRC);
	अगर (!hdr)
		जाओ मुक्त_msg;

	rcu_पढ़ो_lock();
	tun_src = rcu_dereference(seg6_pernet(net)->tun_src);

	अगर (nla_put(msg, SEG6_ATTR_DST, माप(काष्ठा in6_addr), tun_src))
		जाओ nla_put_failure;

	rcu_पढ़ो_unlock();

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

nla_put_failure:
	rcu_पढ़ो_unlock();
मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस -ENOMEM;
पूर्ण

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC

अटल पूर्णांक __seg6_hmac_fill_info(काष्ठा seg6_hmac_info *hinfo,
				 काष्ठा sk_buff *msg)
अणु
	अगर (nla_put_u32(msg, SEG6_ATTR_HMACKEYID, hinfo->hmackeyid) ||
	    nla_put_u8(msg, SEG6_ATTR_SECRETLEN, hinfo->slen) ||
	    nla_put(msg, SEG6_ATTR_SECRET, hinfo->slen, hinfo->secret) ||
	    nla_put_u8(msg, SEG6_ATTR_ALGID, hinfo->alg_id))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक __seg6_genl_dumphmac_element(काष्ठा seg6_hmac_info *hinfo,
					u32 portid, u32 seq, u32 flags,
					काष्ठा sk_buff *skb, u8 cmd)
अणु
	व्योम *hdr;

	hdr = genlmsg_put(skb, portid, seq, &seg6_genl_family, flags, cmd);
	अगर (!hdr)
		वापस -ENOMEM;

	अगर (__seg6_hmac_fill_info(hinfo, skb) < 0)
		जाओ nla_put_failure;

	genlmsg_end(skb, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(skb, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक seg6_genl_dumphmac_start(काष्ठा netlink_callback *cb)
अणु
	काष्ठा net *net = sock_net(cb->skb->sk);
	काष्ठा seg6_pernet_data *sdata;
	काष्ठा rhashtable_iter *iter;

	sdata = seg6_pernet(net);
	iter = (काष्ठा rhashtable_iter *)cb->args[0];

	अगर (!iter) अणु
		iter = kदो_स्मृति(माप(*iter), GFP_KERNEL);
		अगर (!iter)
			वापस -ENOMEM;

		cb->args[0] = (दीर्घ)iter;
	पूर्ण

	rhashtable_walk_enter(&sdata->hmac_infos, iter);

	वापस 0;
पूर्ण

अटल पूर्णांक seg6_genl_dumphmac_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा rhashtable_iter *iter = (काष्ठा rhashtable_iter *)cb->args[0];

	rhashtable_walk_निकास(iter);

	kमुक्त(iter);

	वापस 0;
पूर्ण

अटल पूर्णांक seg6_genl_dumphmac(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा rhashtable_iter *iter = (काष्ठा rhashtable_iter *)cb->args[0];
	काष्ठा seg6_hmac_info *hinfo;
	पूर्णांक ret;

	rhashtable_walk_start(iter);

	क्रम (;;) अणु
		hinfo = rhashtable_walk_next(iter);

		अगर (IS_ERR(hinfo)) अणु
			अगर (PTR_ERR(hinfo) == -EAGAIN)
				जारी;
			ret = PTR_ERR(hinfo);
			जाओ करोne;
		पूर्ण अन्यथा अगर (!hinfo) अणु
			अवरोध;
		पूर्ण

		ret = __seg6_genl_dumphmac_element(hinfo,
						   NETLINK_CB(cb->skb).portid,
						   cb->nlh->nlmsg_seq,
						   NLM_F_MULTI,
						   skb, SEG6_CMD_DUMPHMAC);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	ret = skb->len;

करोne:
	rhashtable_walk_stop(iter);
	वापस ret;
पूर्ण

#अन्यथा

अटल पूर्णांक seg6_genl_dumphmac_start(काष्ठा netlink_callback *cb)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक seg6_genl_dumphmac_करोne(काष्ठा netlink_callback *cb)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक seg6_genl_dumphmac(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	वापस -ENOTSUPP;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __net_init seg6_net_init(काष्ठा net *net)
अणु
	काष्ठा seg6_pernet_data *sdata;

	sdata = kzalloc(माप(*sdata), GFP_KERNEL);
	अगर (!sdata)
		वापस -ENOMEM;

	mutex_init(&sdata->lock);

	sdata->tun_src = kzalloc(माप(*sdata->tun_src), GFP_KERNEL);
	अगर (!sdata->tun_src) अणु
		kमुक्त(sdata);
		वापस -ENOMEM;
	पूर्ण

	net->ipv6.seg6_data = sdata;

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	seg6_hmac_net_init(net);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल व्योम __net_निकास seg6_net_निकास(काष्ठा net *net)
अणु
	काष्ठा seg6_pernet_data *sdata = seg6_pernet(net);

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	seg6_hmac_net_निकास(net);
#पूर्ण_अगर

	kमुक्त(sdata->tun_src);
	kमुक्त(sdata);
पूर्ण

अटल काष्ठा pernet_operations ip6_segments_ops = अणु
	.init = seg6_net_init,
	.निकास = seg6_net_निकास,
पूर्ण;

अटल स्थिर काष्ठा genl_ops seg6_genl_ops[] = अणु
	अणु
		.cmd	= SEG6_CMD_SETHMAC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= seg6_genl_sethmac,
		.flags	= GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd	= SEG6_CMD_DUMPHMAC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.start	= seg6_genl_dumphmac_start,
		.dumpit	= seg6_genl_dumphmac,
		.करोne	= seg6_genl_dumphmac_करोne,
		.flags	= GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd	= SEG6_CMD_SET_TUNSRC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= seg6_genl_set_tunsrc,
		.flags	= GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd	= SEG6_CMD_GET_TUNSRC,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit	= seg6_genl_get_tunsrc,
		.flags	= GENL_ADMIN_PERM,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family seg6_genl_family __ro_after_init = अणु
	.hdrsize	= 0,
	.name		= SEG6_GENL_NAME,
	.version	= SEG6_GENL_VERSION,
	.maxattr	= SEG6_ATTR_MAX,
	.policy = seg6_genl_policy,
	.netnsok	= true,
	.parallel_ops	= true,
	.ops		= seg6_genl_ops,
	.n_ops		= ARRAY_SIZE(seg6_genl_ops),
	.module		= THIS_MODULE,
पूर्ण;

पूर्णांक __init seg6_init(व्योम)
अणु
	पूर्णांक err;

	err = genl_रेजिस्टर_family(&seg6_genl_family);
	अगर (err)
		जाओ out;

	err = रेजिस्टर_pernet_subsys(&ip6_segments_ops);
	अगर (err)
		जाओ out_unरेजिस्टर_genl;

#अगर_घोषित CONFIG_IPV6_SEG6_LWTUNNEL
	err = seg6_iptunnel_init();
	अगर (err)
		जाओ out_unरेजिस्टर_pernet;

	err = seg6_local_init();
	अगर (err)
		जाओ out_unरेजिस्टर_pernet;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	err = seg6_hmac_init();
	अगर (err)
		जाओ out_unरेजिस्टर_iptun;
#पूर्ण_अगर

	pr_info("Segment Routing with IPv6\n");

out:
	वापस err;
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
out_unरेजिस्टर_iptun:
#अगर_घोषित CONFIG_IPV6_SEG6_LWTUNNEL
	seg6_local_निकास();
	seg6_iptunnel_निकास();
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPV6_SEG6_LWTUNNEL
out_unरेजिस्टर_pernet:
	unरेजिस्टर_pernet_subsys(&ip6_segments_ops);
#पूर्ण_अगर
out_unरेजिस्टर_genl:
	genl_unरेजिस्टर_family(&seg6_genl_family);
	जाओ out;
पूर्ण

व्योम seg6_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_IPV6_SEG6_HMAC
	seg6_hmac_निकास();
#पूर्ण_अगर
#अगर_घोषित CONFIG_IPV6_SEG6_LWTUNNEL
	seg6_iptunnel_निकास();
#पूर्ण_अगर
	unरेजिस्टर_pernet_subsys(&ip6_segments_ops);
	genl_unरेजिस्टर_family(&seg6_genl_family);
पूर्ण
