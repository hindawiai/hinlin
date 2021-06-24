<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * net/psample/psample.c - Netlink channel क्रम packet sampling
 * Copyright (c) 2017 Yotam Gigi <yotamg@mellanox.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/module.h>
#समावेश <linux/समयkeeping.h>
#समावेश <net/net_namespace.h>
#समावेश <net/sock.h>
#समावेश <net/netlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/psample.h>
#समावेश <linux/spinlock.h>
#समावेश <net/ip_tunnels.h>
#समावेश <net/dst_metadata.h>

#घोषणा PSAMPLE_MAX_PACKET_SIZE 0xffff

अटल LIST_HEAD(psample_groups_list);
अटल DEFINE_SPINLOCK(psample_groups_lock);

/* multicast groups */
क्रमागत psample_nl_multicast_groups अणु
	PSAMPLE_NL_MCGRP_CONFIG,
	PSAMPLE_NL_MCGRP_SAMPLE,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group psample_nl_mcgrps[] = अणु
	[PSAMPLE_NL_MCGRP_CONFIG] = अणु .name = PSAMPLE_NL_MCGRP_CONFIG_NAME पूर्ण,
	[PSAMPLE_NL_MCGRP_SAMPLE] = अणु .name = PSAMPLE_NL_MCGRP_SAMPLE_NAME पूर्ण,
पूर्ण;

अटल काष्ठा genl_family psample_nl_family __ro_after_init;

अटल पूर्णांक psample_group_nl_fill(काष्ठा sk_buff *msg,
				 काष्ठा psample_group *group,
				 क्रमागत psample_command cmd, u32 portid, u32 seq,
				 पूर्णांक flags)
अणु
	व्योम *hdr;
	पूर्णांक ret;

	hdr = genlmsg_put(msg, portid, seq, &psample_nl_family, flags, cmd);
	अगर (!hdr)
		वापस -EMSGSIZE;

	ret = nla_put_u32(msg, PSAMPLE_ATTR_SAMPLE_GROUP, group->group_num);
	अगर (ret < 0)
		जाओ error;

	ret = nla_put_u32(msg, PSAMPLE_ATTR_GROUP_REFCOUNT, group->refcount);
	अगर (ret < 0)
		जाओ error;

	ret = nla_put_u32(msg, PSAMPLE_ATTR_GROUP_SEQ, group->seq);
	अगर (ret < 0)
		जाओ error;

	genlmsg_end(msg, hdr);
	वापस 0;

error:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक psample_nl_cmd_get_group_dumpit(काष्ठा sk_buff *msg,
					   काष्ठा netlink_callback *cb)
अणु
	काष्ठा psample_group *group;
	पूर्णांक start = cb->args[0];
	पूर्णांक idx = 0;
	पूर्णांक err;

	spin_lock_bh(&psample_groups_lock);
	list_क्रम_each_entry(group, &psample_groups_list, list) अणु
		अगर (!net_eq(group->net, sock_net(msg->sk)))
			जारी;
		अगर (idx < start) अणु
			idx++;
			जारी;
		पूर्ण
		err = psample_group_nl_fill(msg, group, PSAMPLE_CMD_NEW_GROUP,
					    NETLINK_CB(cb->skb).portid,
					    cb->nlh->nlmsg_seq, NLM_F_MULTI);
		अगर (err)
			अवरोध;
		idx++;
	पूर्ण

	spin_unlock_bh(&psample_groups_lock);
	cb->args[0] = idx;
	वापस msg->len;
पूर्ण

अटल स्थिर काष्ठा genl_small_ops psample_nl_ops[] = अणु
	अणु
		.cmd = PSAMPLE_CMD_GET_GROUP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit = psample_nl_cmd_get_group_dumpit,
		/* can be retrieved by unprivileged users */
	पूर्ण
पूर्ण;

अटल काष्ठा genl_family psample_nl_family __ro_after_init = अणु
	.name		= PSAMPLE_GENL_NAME,
	.version	= PSAMPLE_GENL_VERSION,
	.maxattr	= PSAMPLE_ATTR_MAX,
	.netnsok	= true,
	.module		= THIS_MODULE,
	.mcgrps		= psample_nl_mcgrps,
	.small_ops	= psample_nl_ops,
	.n_small_ops	= ARRAY_SIZE(psample_nl_ops),
	.n_mcgrps	= ARRAY_SIZE(psample_nl_mcgrps),
पूर्ण;

अटल व्योम psample_group_notअगरy(काष्ठा psample_group *group,
				 क्रमागत psample_command cmd)
अणु
	काष्ठा sk_buff *msg;
	पूर्णांक err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!msg)
		वापस;

	err = psample_group_nl_fill(msg, group, cmd, 0, 0, NLM_F_MULTI);
	अगर (!err)
		genlmsg_multicast_netns(&psample_nl_family, group->net, msg, 0,
					PSAMPLE_NL_MCGRP_CONFIG, GFP_ATOMIC);
	अन्यथा
		nlmsg_मुक्त(msg);
पूर्ण

अटल काष्ठा psample_group *psample_group_create(काष्ठा net *net,
						  u32 group_num)
अणु
	काष्ठा psample_group *group;

	group = kzalloc(माप(*group), GFP_ATOMIC);
	अगर (!group)
		वापस शून्य;

	group->net = net;
	group->group_num = group_num;
	list_add_tail(&group->list, &psample_groups_list);

	psample_group_notअगरy(group, PSAMPLE_CMD_NEW_GROUP);
	वापस group;
पूर्ण

अटल व्योम psample_group_destroy(काष्ठा psample_group *group)
अणु
	psample_group_notअगरy(group, PSAMPLE_CMD_DEL_GROUP);
	list_del(&group->list);
	kमुक्त_rcu(group, rcu);
पूर्ण

अटल काष्ठा psample_group *
psample_group_lookup(काष्ठा net *net, u32 group_num)
अणु
	काष्ठा psample_group *group;

	list_क्रम_each_entry(group, &psample_groups_list, list)
		अगर ((group->group_num == group_num) && (group->net == net))
			वापस group;
	वापस शून्य;
पूर्ण

काष्ठा psample_group *psample_group_get(काष्ठा net *net, u32 group_num)
अणु
	काष्ठा psample_group *group;

	spin_lock_bh(&psample_groups_lock);

	group = psample_group_lookup(net, group_num);
	अगर (!group) अणु
		group = psample_group_create(net, group_num);
		अगर (!group)
			जाओ out;
	पूर्ण
	group->refcount++;

out:
	spin_unlock_bh(&psample_groups_lock);
	वापस group;
पूर्ण
EXPORT_SYMBOL_GPL(psample_group_get);

व्योम psample_group_take(काष्ठा psample_group *group)
अणु
	spin_lock_bh(&psample_groups_lock);
	group->refcount++;
	spin_unlock_bh(&psample_groups_lock);
पूर्ण
EXPORT_SYMBOL_GPL(psample_group_take);

व्योम psample_group_put(काष्ठा psample_group *group)
अणु
	spin_lock_bh(&psample_groups_lock);

	अगर (--group->refcount == 0)
		psample_group_destroy(group);

	spin_unlock_bh(&psample_groups_lock);
पूर्ण
EXPORT_SYMBOL_GPL(psample_group_put);

#अगर_घोषित CONFIG_INET
अटल पूर्णांक __psample_ip_tun_to_nlattr(काष्ठा sk_buff *skb,
			      काष्ठा ip_tunnel_info *tun_info)
अणु
	अचिन्हित लघु tun_proto = ip_tunnel_info_af(tun_info);
	स्थिर व्योम *tun_opts = ip_tunnel_info_opts(tun_info);
	स्थिर काष्ठा ip_tunnel_key *tun_key = &tun_info->key;
	पूर्णांक tun_opts_len = tun_info->options_len;

	अगर (tun_key->tun_flags & TUNNEL_KEY &&
	    nla_put_be64(skb, PSAMPLE_TUNNEL_KEY_ATTR_ID, tun_key->tun_id,
			 PSAMPLE_TUNNEL_KEY_ATTR_PAD))
		वापस -EMSGSIZE;

	अगर (tun_info->mode & IP_TUNNEL_INFO_BRIDGE &&
	    nla_put_flag(skb, PSAMPLE_TUNNEL_KEY_ATTR_IPV4_INFO_BRIDGE))
		वापस -EMSGSIZE;

	चयन (tun_proto) अणु
	हाल AF_INET:
		अगर (tun_key->u.ipv4.src &&
		    nla_put_in_addr(skb, PSAMPLE_TUNNEL_KEY_ATTR_IPV4_SRC,
				    tun_key->u.ipv4.src))
			वापस -EMSGSIZE;
		अगर (tun_key->u.ipv4.dst &&
		    nla_put_in_addr(skb, PSAMPLE_TUNNEL_KEY_ATTR_IPV4_DST,
				    tun_key->u.ipv4.dst))
			वापस -EMSGSIZE;
		अवरोध;
	हाल AF_INET6:
		अगर (!ipv6_addr_any(&tun_key->u.ipv6.src) &&
		    nla_put_in6_addr(skb, PSAMPLE_TUNNEL_KEY_ATTR_IPV6_SRC,
				     &tun_key->u.ipv6.src))
			वापस -EMSGSIZE;
		अगर (!ipv6_addr_any(&tun_key->u.ipv6.dst) &&
		    nla_put_in6_addr(skb, PSAMPLE_TUNNEL_KEY_ATTR_IPV6_DST,
				     &tun_key->u.ipv6.dst))
			वापस -EMSGSIZE;
		अवरोध;
	पूर्ण
	अगर (tun_key->tos &&
	    nla_put_u8(skb, PSAMPLE_TUNNEL_KEY_ATTR_TOS, tun_key->tos))
		वापस -EMSGSIZE;
	अगर (nla_put_u8(skb, PSAMPLE_TUNNEL_KEY_ATTR_TTL, tun_key->ttl))
		वापस -EMSGSIZE;
	अगर ((tun_key->tun_flags & TUNNEL_DONT_FRAGMENT) &&
	    nla_put_flag(skb, PSAMPLE_TUNNEL_KEY_ATTR_DONT_FRAGMENT))
		वापस -EMSGSIZE;
	अगर ((tun_key->tun_flags & TUNNEL_CSUM) &&
	    nla_put_flag(skb, PSAMPLE_TUNNEL_KEY_ATTR_CSUM))
		वापस -EMSGSIZE;
	अगर (tun_key->tp_src &&
	    nla_put_be16(skb, PSAMPLE_TUNNEL_KEY_ATTR_TP_SRC, tun_key->tp_src))
		वापस -EMSGSIZE;
	अगर (tun_key->tp_dst &&
	    nla_put_be16(skb, PSAMPLE_TUNNEL_KEY_ATTR_TP_DST, tun_key->tp_dst))
		वापस -EMSGSIZE;
	अगर ((tun_key->tun_flags & TUNNEL_OAM) &&
	    nla_put_flag(skb, PSAMPLE_TUNNEL_KEY_ATTR_OAM))
		वापस -EMSGSIZE;
	अगर (tun_opts_len) अणु
		अगर (tun_key->tun_flags & TUNNEL_GENEVE_OPT &&
		    nla_put(skb, PSAMPLE_TUNNEL_KEY_ATTR_GENEVE_OPTS,
			    tun_opts_len, tun_opts))
			वापस -EMSGSIZE;
		अन्यथा अगर (tun_key->tun_flags & TUNNEL_ERSPAN_OPT &&
			 nla_put(skb, PSAMPLE_TUNNEL_KEY_ATTR_ERSPAN_OPTS,
				 tun_opts_len, tun_opts))
			वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psample_ip_tun_to_nlattr(काष्ठा sk_buff *skb,
			    काष्ठा ip_tunnel_info *tun_info)
अणु
	काष्ठा nlattr *nla;
	पूर्णांक err;

	nla = nla_nest_start_noflag(skb, PSAMPLE_ATTR_TUNNEL);
	अगर (!nla)
		वापस -EMSGSIZE;

	err = __psample_ip_tun_to_nlattr(skb, tun_info);
	अगर (err) अणु
		nla_nest_cancel(skb, nla);
		वापस err;
	पूर्ण

	nla_nest_end(skb, nla);

	वापस 0;
पूर्ण

अटल पूर्णांक psample_tunnel_meta_len(काष्ठा ip_tunnel_info *tun_info)
अणु
	अचिन्हित लघु tun_proto = ip_tunnel_info_af(tun_info);
	स्थिर काष्ठा ip_tunnel_key *tun_key = &tun_info->key;
	पूर्णांक tun_opts_len = tun_info->options_len;
	पूर्णांक sum = nla_total_size(0);	/* PSAMPLE_ATTR_TUNNEL */

	अगर (tun_key->tun_flags & TUNNEL_KEY)
		sum += nla_total_size_64bit(माप(u64));

	अगर (tun_info->mode & IP_TUNNEL_INFO_BRIDGE)
		sum += nla_total_size(0);

	चयन (tun_proto) अणु
	हाल AF_INET:
		अगर (tun_key->u.ipv4.src)
			sum += nla_total_size(माप(u32));
		अगर (tun_key->u.ipv4.dst)
			sum += nla_total_size(माप(u32));
		अवरोध;
	हाल AF_INET6:
		अगर (!ipv6_addr_any(&tun_key->u.ipv6.src))
			sum += nla_total_size(माप(काष्ठा in6_addr));
		अगर (!ipv6_addr_any(&tun_key->u.ipv6.dst))
			sum += nla_total_size(माप(काष्ठा in6_addr));
		अवरोध;
	पूर्ण
	अगर (tun_key->tos)
		sum += nla_total_size(माप(u8));
	sum += nla_total_size(माप(u8));	/* TTL */
	अगर (tun_key->tun_flags & TUNNEL_DONT_FRAGMENT)
		sum += nla_total_size(0);
	अगर (tun_key->tun_flags & TUNNEL_CSUM)
		sum += nla_total_size(0);
	अगर (tun_key->tp_src)
		sum += nla_total_size(माप(u16));
	अगर (tun_key->tp_dst)
		sum += nla_total_size(माप(u16));
	अगर (tun_key->tun_flags & TUNNEL_OAM)
		sum += nla_total_size(0);
	अगर (tun_opts_len) अणु
		अगर (tun_key->tun_flags & TUNNEL_GENEVE_OPT)
			sum += nla_total_size(tun_opts_len);
		अन्यथा अगर (tun_key->tun_flags & TUNNEL_ERSPAN_OPT)
			sum += nla_total_size(tun_opts_len);
	पूर्ण

	वापस sum;
पूर्ण
#पूर्ण_अगर

व्योम psample_sample_packet(काष्ठा psample_group *group, काष्ठा sk_buff *skb,
			   u32 sample_rate, स्थिर काष्ठा psample_metadata *md)
अणु
	kसमय_प्रकार tstamp = kसमय_get_real();
	पूर्णांक out_अगरindex = md->out_अगरindex;
	पूर्णांक in_अगरindex = md->in_अगरindex;
	u32 trunc_size = md->trunc_size;
#अगर_घोषित CONFIG_INET
	काष्ठा ip_tunnel_info *tun_info;
#पूर्ण_अगर
	काष्ठा sk_buff *nl_skb;
	पूर्णांक data_len;
	पूर्णांक meta_len;
	व्योम *data;
	पूर्णांक ret;

	meta_len = (in_अगरindex ? nla_total_size(माप(u16)) : 0) +
		   (out_अगरindex ? nla_total_size(माप(u16)) : 0) +
		   (md->out_tc_valid ? nla_total_size(माप(u16)) : 0) +
		   (md->out_tc_occ_valid ? nla_total_size_64bit(माप(u64)) : 0) +
		   (md->latency_valid ? nla_total_size_64bit(माप(u64)) : 0) +
		   nla_total_size(माप(u32)) +	/* sample_rate */
		   nla_total_size(माप(u32)) +	/* orig_size */
		   nla_total_size(माप(u32)) +	/* group_num */
		   nla_total_size(माप(u32)) +	/* seq */
		   nla_total_size_64bit(माप(u64)) +	/* बारtamp */
		   nla_total_size(माप(u16));		/* protocol */

#अगर_घोषित CONFIG_INET
	tun_info = skb_tunnel_info(skb);
	अगर (tun_info)
		meta_len += psample_tunnel_meta_len(tun_info);
#पूर्ण_अगर

	data_len = min(skb->len, trunc_size);
	अगर (meta_len + nla_total_size(data_len) > PSAMPLE_MAX_PACKET_SIZE)
		data_len = PSAMPLE_MAX_PACKET_SIZE - meta_len - NLA_HDRLEN
			    - NLA_ALIGNTO;

	nl_skb = genlmsg_new(meta_len + nla_total_size(data_len), GFP_ATOMIC);
	अगर (unlikely(!nl_skb))
		वापस;

	data = genlmsg_put(nl_skb, 0, 0, &psample_nl_family, 0,
			   PSAMPLE_CMD_SAMPLE);
	अगर (unlikely(!data))
		जाओ error;

	अगर (in_अगरindex) अणु
		ret = nla_put_u16(nl_skb, PSAMPLE_ATTR_IIFINDEX, in_अगरindex);
		अगर (unlikely(ret < 0))
			जाओ error;
	पूर्ण

	अगर (out_अगरindex) अणु
		ret = nla_put_u16(nl_skb, PSAMPLE_ATTR_OIFINDEX, out_अगरindex);
		अगर (unlikely(ret < 0))
			जाओ error;
	पूर्ण

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_SAMPLE_RATE, sample_rate);
	अगर (unlikely(ret < 0))
		जाओ error;

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_ORIGSIZE, skb->len);
	अगर (unlikely(ret < 0))
		जाओ error;

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_SAMPLE_GROUP, group->group_num);
	अगर (unlikely(ret < 0))
		जाओ error;

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_GROUP_SEQ, group->seq++);
	अगर (unlikely(ret < 0))
		जाओ error;

	अगर (md->out_tc_valid) अणु
		ret = nla_put_u16(nl_skb, PSAMPLE_ATTR_OUT_TC, md->out_tc);
		अगर (unlikely(ret < 0))
			जाओ error;
	पूर्ण

	अगर (md->out_tc_occ_valid) अणु
		ret = nla_put_u64_64bit(nl_skb, PSAMPLE_ATTR_OUT_TC_OCC,
					md->out_tc_occ, PSAMPLE_ATTR_PAD);
		अगर (unlikely(ret < 0))
			जाओ error;
	पूर्ण

	अगर (md->latency_valid) अणु
		ret = nla_put_u64_64bit(nl_skb, PSAMPLE_ATTR_LATENCY,
					md->latency, PSAMPLE_ATTR_PAD);
		अगर (unlikely(ret < 0))
			जाओ error;
	पूर्ण

	ret = nla_put_u64_64bit(nl_skb, PSAMPLE_ATTR_TIMESTAMP,
				kसमय_प्रकारo_ns(tstamp), PSAMPLE_ATTR_PAD);
	अगर (unlikely(ret < 0))
		जाओ error;

	ret = nla_put_u16(nl_skb, PSAMPLE_ATTR_PROTO,
			  be16_to_cpu(skb->protocol));
	अगर (unlikely(ret < 0))
		जाओ error;

	अगर (data_len) अणु
		पूर्णांक nla_len = nla_total_size(data_len);
		काष्ठा nlattr *nla;

		nla = skb_put(nl_skb, nla_len);
		nla->nla_type = PSAMPLE_ATTR_DATA;
		nla->nla_len = nla_attr_size(data_len);

		अगर (skb_copy_bits(skb, 0, nla_data(nla), data_len))
			जाओ error;
	पूर्ण

#अगर_घोषित CONFIG_INET
	अगर (tun_info) अणु
		ret = psample_ip_tun_to_nlattr(nl_skb, tun_info);
		अगर (unlikely(ret < 0))
			जाओ error;
	पूर्ण
#पूर्ण_अगर

	genlmsg_end(nl_skb, data);
	genlmsg_multicast_netns(&psample_nl_family, group->net, nl_skb, 0,
				PSAMPLE_NL_MCGRP_SAMPLE, GFP_ATOMIC);

	वापस;
error:
	pr_err_ratelimited("Could not create psample log message\n");
	nlmsg_मुक्त(nl_skb);
पूर्ण
EXPORT_SYMBOL_GPL(psample_sample_packet);

अटल पूर्णांक __init psample_module_init(व्योम)
अणु
	वापस genl_रेजिस्टर_family(&psample_nl_family);
पूर्ण

अटल व्योम __निकास psample_module_निकास(व्योम)
अणु
	genl_unरेजिस्टर_family(&psample_nl_family);
पूर्ण

module_init(psample_module_init);
module_निकास(psample_module_निकास);

MODULE_AUTHOR("Yotam Gigi <yotam.gi@gmail.com>");
MODULE_DESCRIPTION("netlink channel for packet sampling");
MODULE_LICENSE("GPL v2");
