<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <net/sock.h>
#समावेश <linux/ethtool_netlink.h>
#समावेश "netlink.h"

अटल काष्ठा genl_family ethtool_genl_family;

अटल bool ethnl_ok __पढ़ो_mostly;
अटल u32 ethnl_bcast_seq;

#घोषणा ETHTOOL_FLAGS_BASIC (ETHTOOL_FLAG_COMPACT_BITSETS |	\
			     ETHTOOL_FLAG_OMIT_REPLY)
#घोषणा ETHTOOL_FLAGS_STATS (ETHTOOL_FLAGS_BASIC | ETHTOOL_FLAG_STATS)

स्थिर काष्ठा nla_policy ethnl_header_policy[] = अणु
	[ETHTOOL_A_HEADER_DEV_INDEX]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_HEADER_DEV_NAME]	= अणु .type = NLA_NUL_STRING,
					    .len = ALTIFNAMSIZ - 1 पूर्ण,
	[ETHTOOL_A_HEADER_FLAGS]	= NLA_POLICY_MASK(NLA_U32,
							  ETHTOOL_FLAGS_BASIC),
पूर्ण;

स्थिर काष्ठा nla_policy ethnl_header_policy_stats[] = अणु
	[ETHTOOL_A_HEADER_DEV_INDEX]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_HEADER_DEV_NAME]	= अणु .type = NLA_NUL_STRING,
					    .len = ALTIFNAMSIZ - 1 पूर्ण,
	[ETHTOOL_A_HEADER_FLAGS]	= NLA_POLICY_MASK(NLA_U32,
							  ETHTOOL_FLAGS_STATS),
पूर्ण;

/**
 * ethnl_parse_header_dev_get() - parse request header
 * @req_info:    काष्ठाure to put results पूर्णांकo
 * @header:      nest attribute with request header
 * @net:         request netns
 * @extack:      netlink extack क्रम error reporting
 * @require_dev: fail अगर no device identअगरied in header
 *
 * Parse request header in nested attribute @nest and माला_दो results पूर्णांकo
 * the काष्ठाure poपूर्णांकed to by @req_info. Extack from @info is used क्रम error
 * reporting. If req_info->dev is not null on वापस, reference to it has
 * been taken. If error is वापसed, *req_info is null initialized and no
 * reference is held.
 *
 * Return: 0 on success or negative error code
 */
पूर्णांक ethnl_parse_header_dev_get(काष्ठा ethnl_req_info *req_info,
			       स्थिर काष्ठा nlattr *header, काष्ठा net *net,
			       काष्ठा netlink_ext_ack *extack, bool require_dev)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(ethnl_header_policy)];
	स्थिर काष्ठा nlattr *devname_attr;
	काष्ठा net_device *dev = शून्य;
	u32 flags = 0;
	पूर्णांक ret;

	अगर (!header) अणु
		NL_SET_ERR_MSG(extack, "request header missing");
		वापस -EINVAL;
	पूर्ण
	/* No validation here, command policy should have a nested policy set
	 * क्रम the header, thereक्रमe validation should have alपढ़ोy been करोne.
	 */
	ret = nla_parse_nested(tb, ARRAY_SIZE(ethnl_header_policy) - 1, header,
			       शून्य, extack);
	अगर (ret < 0)
		वापस ret;
	अगर (tb[ETHTOOL_A_HEADER_FLAGS])
		flags = nla_get_u32(tb[ETHTOOL_A_HEADER_FLAGS]);

	devname_attr = tb[ETHTOOL_A_HEADER_DEV_NAME];
	अगर (tb[ETHTOOL_A_HEADER_DEV_INDEX]) अणु
		u32 अगरindex = nla_get_u32(tb[ETHTOOL_A_HEADER_DEV_INDEX]);

		dev = dev_get_by_index(net, अगरindex);
		अगर (!dev) अणु
			NL_SET_ERR_MSG_ATTR(extack,
					    tb[ETHTOOL_A_HEADER_DEV_INDEX],
					    "no device matches ifindex");
			वापस -ENODEV;
		पूर्ण
		/* अगर both अगरindex and अगरname are passed, they must match */
		अगर (devname_attr &&
		    म_भेदन(dev->name, nla_data(devname_attr), IFNAMSIZ)) अणु
			dev_put(dev);
			NL_SET_ERR_MSG_ATTR(extack, header,
					    "ifindex and name do not match");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (devname_attr) अणु
		dev = dev_get_by_name(net, nla_data(devname_attr));
		अगर (!dev) अणु
			NL_SET_ERR_MSG_ATTR(extack, devname_attr,
					    "no device matches name");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अगर (require_dev) अणु
		NL_SET_ERR_MSG_ATTR(extack, header,
				    "neither ifindex nor name specified");
		वापस -EINVAL;
	पूर्ण

	अगर (dev && !netअगर_device_present(dev)) अणु
		dev_put(dev);
		NL_SET_ERR_MSG(extack, "device not present");
		वापस -ENODEV;
	पूर्ण

	req_info->dev = dev;
	req_info->flags = flags;
	वापस 0;
पूर्ण

/**
 * ethnl_fill_reply_header() - Put common header पूर्णांकo a reply message
 * @skb:      skb with the message
 * @dev:      network device to describe in header
 * @attrtype: attribute type to use क्रम the nest
 *
 * Create a nested attribute with attributes describing given network device.
 *
 * Return: 0 on success, error value (-EMSGSIZE only) on error
 */
पूर्णांक ethnl_fill_reply_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			    u16 attrtype)
अणु
	काष्ठा nlattr *nest;

	अगर (!dev)
		वापस 0;
	nest = nla_nest_start(skb, attrtype);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, ETHTOOL_A_HEADER_DEV_INDEX, (u32)dev->अगरindex) ||
	    nla_put_string(skb, ETHTOOL_A_HEADER_DEV_NAME, dev->name))
		जाओ nla_put_failure;
	/* If more attributes are put पूर्णांकo reply header, ethnl_header_size()
	 * must be updated to account क्रम them.
	 */

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

/**
 * ethnl_reply_init() - Create skb क्रम a reply and fill device identअगरication
 * @payload:      payload length (without netlink and genetlink header)
 * @dev:          device the reply is about (may be null)
 * @cmd:          ETHTOOL_MSG_* message type क्रम reply
 * @hdr_attrtype: attribute type क्रम common header
 * @info:         genetlink info of the received packet we respond to
 * @ehdrp:        place to store payload poपूर्णांकer वापसed by genlmsg_new()
 *
 * Return: poपूर्णांकer to allocated skb on success, शून्य on error
 */
काष्ठा sk_buff *ethnl_reply_init(माप_प्रकार payload, काष्ठा net_device *dev, u8 cmd,
				 u16 hdr_attrtype, काष्ठा genl_info *info,
				 व्योम **ehdrp)
अणु
	काष्ठा sk_buff *skb;

	skb = genlmsg_new(payload, GFP_KERNEL);
	अगर (!skb)
		जाओ err;
	*ehdrp = genlmsg_put_reply(skb, info, &ethtool_genl_family, 0, cmd);
	अगर (!*ehdrp)
		जाओ err_मुक्त;

	अगर (dev) अणु
		पूर्णांक ret;

		ret = ethnl_fill_reply_header(skb, dev, hdr_attrtype);
		अगर (ret < 0)
			जाओ err_मुक्त;
	पूर्ण
	वापस skb;

err_मुक्त:
	nlmsg_मुक्त(skb);
err:
	अगर (info)
		GENL_SET_ERR_MSG(info, "failed to setup reply message");
	वापस शून्य;
पूर्ण

व्योम *ethnl_dump_put(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb, u8 cmd)
अणु
	वापस genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			   &ethtool_genl_family, 0, cmd);
पूर्ण

व्योम *ethnl_bcasपंचांगsg_put(काष्ठा sk_buff *skb, u8 cmd)
अणु
	वापस genlmsg_put(skb, 0, ++ethnl_bcast_seq, &ethtool_genl_family, 0,
			   cmd);
पूर्ण

पूर्णांक ethnl_multicast(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	वापस genlmsg_multicast_netns(&ethtool_genl_family, dev_net(dev), skb,
				       0, ETHNL_MCGRP_MONITOR, GFP_KERNEL);
पूर्ण

/* GET request helpers */

/**
 * काष्ठा ethnl_dump_ctx - context काष्ठाure क्रम generic dumpit() callback
 * @ops:        request ops of currently processed message type
 * @req_info:   parsed request header of processed request
 * @reply_data: data needed to compose the reply
 * @pos_hash:   saved iteration position - hashbucket
 * @pos_idx:    saved iteration position - index
 *
 * These parameters are kept in काष्ठा netlink_callback as context preserved
 * between iterations. They are initialized by ethnl_शेष_start() and used
 * in ethnl_शेष_dumpit() and ethnl_शेष_करोne().
 */
काष्ठा ethnl_dump_ctx अणु
	स्थिर काष्ठा ethnl_request_ops	*ops;
	काष्ठा ethnl_req_info		*req_info;
	काष्ठा ethnl_reply_data		*reply_data;
	पूर्णांक				pos_hash;
	पूर्णांक				pos_idx;
पूर्ण;

अटल स्थिर काष्ठा ethnl_request_ops *
ethnl_शेष_requests[__ETHTOOL_MSG_USER_CNT] = अणु
	[ETHTOOL_MSG_STRSET_GET]	= &ethnl_strset_request_ops,
	[ETHTOOL_MSG_LINKINFO_GET]	= &ethnl_linkinfo_request_ops,
	[ETHTOOL_MSG_LINKMODES_GET]	= &ethnl_linkmodes_request_ops,
	[ETHTOOL_MSG_LINKSTATE_GET]	= &ethnl_linkstate_request_ops,
	[ETHTOOL_MSG_DEBUG_GET]		= &ethnl_debug_request_ops,
	[ETHTOOL_MSG_WOL_GET]		= &ethnl_wol_request_ops,
	[ETHTOOL_MSG_FEATURES_GET]	= &ethnl_features_request_ops,
	[ETHTOOL_MSG_PRIVFLAGS_GET]	= &ethnl_privflags_request_ops,
	[ETHTOOL_MSG_RINGS_GET]		= &ethnl_rings_request_ops,
	[ETHTOOL_MSG_CHANNELS_GET]	= &ethnl_channels_request_ops,
	[ETHTOOL_MSG_COALESCE_GET]	= &ethnl_coalesce_request_ops,
	[ETHTOOL_MSG_PAUSE_GET]		= &ethnl_छोड़ो_request_ops,
	[ETHTOOL_MSG_EEE_GET]		= &ethnl_eee_request_ops,
	[ETHTOOL_MSG_FEC_GET]		= &ethnl_fec_request_ops,
	[ETHTOOL_MSG_TSINFO_GET]	= &ethnl_tsinfo_request_ops,
	[ETHTOOL_MSG_MODULE_EEPROM_GET]	= &ethnl_module_eeprom_request_ops,
	[ETHTOOL_MSG_STATS_GET]		= &ethnl_stats_request_ops,
पूर्ण;

अटल काष्ठा ethnl_dump_ctx *ethnl_dump_context(काष्ठा netlink_callback *cb)
अणु
	वापस (काष्ठा ethnl_dump_ctx *)cb->ctx;
पूर्ण

/**
 * ethnl_शेष_parse() - Parse request message
 * @req_info:    poपूर्णांकer to काष्ठाure to put data पूर्णांकo
 * @tb:		 parsed attributes
 * @net:         request netns
 * @request_ops: काष्ठा request_ops क्रम request type
 * @extack:      netlink extack क्रम error reporting
 * @require_dev: fail अगर no device identअगरied in header
 *
 * Parse universal request header and call request specअगरic ->parse_request()
 * callback (अगर defined) to parse the rest of the message.
 *
 * Return: 0 on success or negative error code
 */
अटल पूर्णांक ethnl_शेष_parse(काष्ठा ethnl_req_info *req_info,
			       काष्ठा nlattr **tb, काष्ठा net *net,
			       स्थिर काष्ठा ethnl_request_ops *request_ops,
			       काष्ठा netlink_ext_ack *extack, bool require_dev)
अणु
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(req_info, tb[request_ops->hdr_attr],
					 net, extack, require_dev);
	अगर (ret < 0)
		वापस ret;

	अगर (request_ops->parse_request) अणु
		ret = request_ops->parse_request(req_info, tb, extack);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ethnl_init_reply_data() - Initialize reply data क्रम GET request
 * @reply_data: poपूर्णांकer to embedded काष्ठा ethnl_reply_data
 * @ops:        instance of काष्ठा ethnl_request_ops describing the layout
 * @dev:        network device to initialize the reply क्रम
 *
 * Fills the reply data part with zeros and sets the dev member. Must be called
 * beक्रमe calling the ->fill_reply() callback (क्रम each iteration when handling
 * dump requests).
 */
अटल व्योम ethnl_init_reply_data(काष्ठा ethnl_reply_data *reply_data,
				  स्थिर काष्ठा ethnl_request_ops *ops,
				  काष्ठा net_device *dev)
अणु
	स_रखो(reply_data, 0, ops->reply_data_size);
	reply_data->dev = dev;
पूर्ण

/* शेष ->करोit() handler क्रम GET type requests */
अटल पूर्णांक ethnl_शेष_करोit(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethnl_reply_data *reply_data = शून्य;
	काष्ठा ethnl_req_info *req_info = शून्य;
	स्थिर u8 cmd = info->genlhdr->cmd;
	स्थिर काष्ठा ethnl_request_ops *ops;
	काष्ठा sk_buff *rskb;
	व्योम *reply_payload;
	पूर्णांक reply_len;
	पूर्णांक ret;

	ops = ethnl_शेष_requests[cmd];
	अगर (WARN_ONCE(!ops, "cmd %u has no ethnl_request_ops\n", cmd))
		वापस -EOPNOTSUPP;
	req_info = kzalloc(ops->req_info_size, GFP_KERNEL);
	अगर (!req_info)
		वापस -ENOMEM;
	reply_data = kदो_स्मृति(ops->reply_data_size, GFP_KERNEL);
	अगर (!reply_data) अणु
		kमुक्त(req_info);
		वापस -ENOMEM;
	पूर्ण

	ret = ethnl_शेष_parse(req_info, info->attrs, genl_info_net(info),
				  ops, info->extack, !ops->allow_nodev_करो);
	अगर (ret < 0)
		जाओ err_dev;
	ethnl_init_reply_data(reply_data, ops, req_info->dev);

	rtnl_lock();
	ret = ops->prepare_data(req_info, reply_data, info);
	rtnl_unlock();
	अगर (ret < 0)
		जाओ err_cleanup;
	ret = ops->reply_size(req_info, reply_data);
	अगर (ret < 0)
		जाओ err_cleanup;
	reply_len = ret + ethnl_reply_header_size();
	ret = -ENOMEM;
	rskb = ethnl_reply_init(reply_len, req_info->dev, ops->reply_cmd,
				ops->hdr_attr, info, &reply_payload);
	अगर (!rskb)
		जाओ err_cleanup;
	ret = ops->fill_reply(rskb, req_info, reply_data);
	अगर (ret < 0)
		जाओ err_msg;
	अगर (ops->cleanup_data)
		ops->cleanup_data(reply_data);

	genlmsg_end(rskb, reply_payload);
	अगर (req_info->dev)
		dev_put(req_info->dev);
	kमुक्त(reply_data);
	kमुक्त(req_info);
	वापस genlmsg_reply(rskb, info);

err_msg:
	WARN_ONCE(ret == -EMSGSIZE, "calculated message payload length (%d) not sufficient\n", reply_len);
	nlmsg_मुक्त(rskb);
err_cleanup:
	अगर (ops->cleanup_data)
		ops->cleanup_data(reply_data);
err_dev:
	अगर (req_info->dev)
		dev_put(req_info->dev);
	kमुक्त(reply_data);
	kमुक्त(req_info);
	वापस ret;
पूर्ण

अटल पूर्णांक ethnl_शेष_dump_one(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				  स्थिर काष्ठा ethnl_dump_ctx *ctx,
				  काष्ठा netlink_callback *cb)
अणु
	व्योम *ehdr;
	पूर्णांक ret;

	ehdr = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			   &ethtool_genl_family, NLM_F_MULTI,
			   ctx->ops->reply_cmd);
	अगर (!ehdr)
		वापस -EMSGSIZE;

	ethnl_init_reply_data(ctx->reply_data, ctx->ops, dev);
	rtnl_lock();
	ret = ctx->ops->prepare_data(ctx->req_info, ctx->reply_data, शून्य);
	rtnl_unlock();
	अगर (ret < 0)
		जाओ out;
	ret = ethnl_fill_reply_header(skb, dev, ctx->ops->hdr_attr);
	अगर (ret < 0)
		जाओ out;
	ret = ctx->ops->fill_reply(skb, ctx->req_info, ctx->reply_data);

out:
	अगर (ctx->ops->cleanup_data)
		ctx->ops->cleanup_data(ctx->reply_data);
	ctx->reply_data->dev = शून्य;
	अगर (ret < 0)
		genlmsg_cancel(skb, ehdr);
	अन्यथा
		genlmsg_end(skb, ehdr);
	वापस ret;
पूर्ण

/* Default ->dumpit() handler क्रम GET requests. Device iteration copied from
 * rtnl_dump_अगरinfo(); we have to be more careful about device hashtable
 * persistence as we cannot guarantee to hold RTNL lock through the whole
 * function as rtnetnlink करोes.
 */
अटल पूर्णांक ethnl_शेष_dumpit(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	काष्ठा ethnl_dump_ctx *ctx = ethnl_dump_context(cb);
	काष्ठा net *net = sock_net(skb->sk);
	पूर्णांक s_idx = ctx->pos_idx;
	पूर्णांक h, idx = 0;
	पूर्णांक ret = 0;

	rtnl_lock();
	क्रम (h = ctx->pos_hash; h < NETDEV_HASHENTRIES; h++, s_idx = 0) अणु
		काष्ठा hlist_head *head;
		काष्ठा net_device *dev;
		अचिन्हित पूर्णांक seq;

		head = &net->dev_index_head[h];

restart_chain:
		seq = net->dev_base_seq;
		cb->seq = seq;
		idx = 0;
		hlist_क्रम_each_entry(dev, head, index_hlist) अणु
			अगर (idx < s_idx)
				जाओ cont;
			dev_hold(dev);
			rtnl_unlock();

			ret = ethnl_शेष_dump_one(skb, dev, ctx, cb);
			dev_put(dev);
			अगर (ret < 0) अणु
				अगर (ret == -EOPNOTSUPP)
					जाओ lock_and_cont;
				अगर (likely(skb->len))
					ret = skb->len;
				जाओ out;
			पूर्ण
lock_and_cont:
			rtnl_lock();
			अगर (net->dev_base_seq != seq) अणु
				s_idx = idx + 1;
				जाओ restart_chain;
			पूर्ण
cont:
			idx++;
		पूर्ण

	पूर्ण
	rtnl_unlock();

out:
	ctx->pos_hash = h;
	ctx->pos_idx = idx;
	nl_dump_check_consistent(cb, nlmsg_hdr(skb));

	वापस ret;
पूर्ण

/* generic ->start() handler क्रम GET requests */
अटल पूर्णांक ethnl_शेष_start(काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा genl_dumpit_info *info = genl_dumpit_info(cb);
	काष्ठा ethnl_dump_ctx *ctx = ethnl_dump_context(cb);
	काष्ठा ethnl_reply_data *reply_data;
	स्थिर काष्ठा ethnl_request_ops *ops;
	काष्ठा ethnl_req_info *req_info;
	काष्ठा genlmsghdr *ghdr;
	पूर्णांक ret;

	BUILD_BUG_ON(माप(*ctx) > माप(cb->ctx));

	ghdr = nlmsg_data(cb->nlh);
	ops = ethnl_शेष_requests[ghdr->cmd];
	अगर (WARN_ONCE(!ops, "cmd %u has no ethnl_request_ops\n", ghdr->cmd))
		वापस -EOPNOTSUPP;
	req_info = kzalloc(ops->req_info_size, GFP_KERNEL);
	अगर (!req_info)
		वापस -ENOMEM;
	reply_data = kदो_स्मृति(ops->reply_data_size, GFP_KERNEL);
	अगर (!reply_data) अणु
		ret = -ENOMEM;
		जाओ मुक्त_req_info;
	पूर्ण

	ret = ethnl_शेष_parse(req_info, info->attrs, sock_net(cb->skb->sk),
				  ops, cb->extack, false);
	अगर (req_info->dev) अणु
		/* We ignore device specअगरication in dump requests but as the
		 * same parser as क्रम non-dump (करोit) requests is used, it
		 * would take reference to the device अगर it finds one
		 */
		dev_put(req_info->dev);
		req_info->dev = शून्य;
	पूर्ण
	अगर (ret < 0)
		जाओ मुक्त_reply_data;

	ctx->ops = ops;
	ctx->req_info = req_info;
	ctx->reply_data = reply_data;
	ctx->pos_hash = 0;
	ctx->pos_idx = 0;

	वापस 0;

मुक्त_reply_data:
	kमुक्त(reply_data);
मुक्त_req_info:
	kमुक्त(req_info);

	वापस ret;
पूर्ण

/* शेष ->करोne() handler क्रम GET requests */
अटल पूर्णांक ethnl_शेष_करोne(काष्ठा netlink_callback *cb)
अणु
	काष्ठा ethnl_dump_ctx *ctx = ethnl_dump_context(cb);

	kमुक्त(ctx->reply_data);
	kमुक्त(ctx->req_info);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethnl_request_ops *
ethnl_शेष_notअगरy_ops[ETHTOOL_MSG_KERNEL_MAX + 1] = अणु
	[ETHTOOL_MSG_LINKINFO_NTF]	= &ethnl_linkinfo_request_ops,
	[ETHTOOL_MSG_LINKMODES_NTF]	= &ethnl_linkmodes_request_ops,
	[ETHTOOL_MSG_DEBUG_NTF]		= &ethnl_debug_request_ops,
	[ETHTOOL_MSG_WOL_NTF]		= &ethnl_wol_request_ops,
	[ETHTOOL_MSG_FEATURES_NTF]	= &ethnl_features_request_ops,
	[ETHTOOL_MSG_PRIVFLAGS_NTF]	= &ethnl_privflags_request_ops,
	[ETHTOOL_MSG_RINGS_NTF]		= &ethnl_rings_request_ops,
	[ETHTOOL_MSG_CHANNELS_NTF]	= &ethnl_channels_request_ops,
	[ETHTOOL_MSG_COALESCE_NTF]	= &ethnl_coalesce_request_ops,
	[ETHTOOL_MSG_PAUSE_NTF]		= &ethnl_छोड़ो_request_ops,
	[ETHTOOL_MSG_EEE_NTF]		= &ethnl_eee_request_ops,
	[ETHTOOL_MSG_FEC_NTF]		= &ethnl_fec_request_ops,
पूर्ण;

/* शेष notअगरication handler */
अटल व्योम ethnl_शेष_notअगरy(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd,
				 स्थिर व्योम *data)
अणु
	काष्ठा ethnl_reply_data *reply_data;
	स्थिर काष्ठा ethnl_request_ops *ops;
	काष्ठा ethnl_req_info *req_info;
	काष्ठा sk_buff *skb;
	व्योम *reply_payload;
	पूर्णांक reply_len;
	पूर्णांक ret;

	अगर (WARN_ONCE(cmd > ETHTOOL_MSG_KERNEL_MAX ||
		      !ethnl_शेष_notअगरy_ops[cmd],
		      "unexpected notification type %u\n", cmd))
		वापस;
	ops = ethnl_शेष_notअगरy_ops[cmd];
	req_info = kzalloc(ops->req_info_size, GFP_KERNEL);
	अगर (!req_info)
		वापस;
	reply_data = kदो_स्मृति(ops->reply_data_size, GFP_KERNEL);
	अगर (!reply_data) अणु
		kमुक्त(req_info);
		वापस;
	पूर्ण

	req_info->dev = dev;
	req_info->flags |= ETHTOOL_FLAG_COMPACT_BITSETS;

	ethnl_init_reply_data(reply_data, ops, dev);
	ret = ops->prepare_data(req_info, reply_data, शून्य);
	अगर (ret < 0)
		जाओ err_cleanup;
	ret = ops->reply_size(req_info, reply_data);
	अगर (ret < 0)
		जाओ err_cleanup;
	reply_len = ret + ethnl_reply_header_size();
	ret = -ENOMEM;
	skb = genlmsg_new(reply_len, GFP_KERNEL);
	अगर (!skb)
		जाओ err_cleanup;
	reply_payload = ethnl_bcasपंचांगsg_put(skb, cmd);
	अगर (!reply_payload)
		जाओ err_skb;
	ret = ethnl_fill_reply_header(skb, dev, ops->hdr_attr);
	अगर (ret < 0)
		जाओ err_msg;
	ret = ops->fill_reply(skb, req_info, reply_data);
	अगर (ret < 0)
		जाओ err_msg;
	अगर (ops->cleanup_data)
		ops->cleanup_data(reply_data);

	genlmsg_end(skb, reply_payload);
	kमुक्त(reply_data);
	kमुक्त(req_info);
	ethnl_multicast(skb, dev);
	वापस;

err_msg:
	WARN_ONCE(ret == -EMSGSIZE,
		  "calculated message payload length (%d) not sufficient\n",
		  reply_len);
err_skb:
	nlmsg_मुक्त(skb);
err_cleanup:
	अगर (ops->cleanup_data)
		ops->cleanup_data(reply_data);
	kमुक्त(reply_data);
	kमुक्त(req_info);
	वापस;
पूर्ण

/* notअगरications */

प्रकार व्योम (*ethnl_notअगरy_handler_t)(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd,
				       स्थिर व्योम *data);

अटल स्थिर ethnl_notअगरy_handler_t ethnl_notअगरy_handlers[] = अणु
	[ETHTOOL_MSG_LINKINFO_NTF]	= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_LINKMODES_NTF]	= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_DEBUG_NTF]		= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_WOL_NTF]		= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_FEATURES_NTF]	= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_PRIVFLAGS_NTF]	= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_RINGS_NTF]		= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_CHANNELS_NTF]	= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_COALESCE_NTF]	= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_PAUSE_NTF]		= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_EEE_NTF]		= ethnl_शेष_notअगरy,
	[ETHTOOL_MSG_FEC_NTF]		= ethnl_शेष_notअगरy,
पूर्ण;

व्योम ethtool_notअगरy(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd, स्थिर व्योम *data)
अणु
	अगर (unlikely(!ethnl_ok))
		वापस;
	ASSERT_RTNL();

	अगर (likely(cmd < ARRAY_SIZE(ethnl_notअगरy_handlers) &&
		   ethnl_notअगरy_handlers[cmd]))
		ethnl_notअगरy_handlers[cmd](dev, cmd, data);
	अन्यथा
		WARN_ONCE(1, "notification %u not implemented (dev=%s)\n",
			  cmd, netdev_name(dev));
पूर्ण
EXPORT_SYMBOL(ethtool_notअगरy);

अटल व्योम ethnl_notअगरy_features(काष्ठा netdev_notअगरier_info *info)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(info);

	ethtool_notअगरy(dev, ETHTOOL_MSG_FEATURES_NTF, शून्य);
पूर्ण

अटल पूर्णांक ethnl_netdev_event(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ event,
			      व्योम *ptr)
अणु
	चयन (event) अणु
	हाल NETDEV_FEAT_CHANGE:
		ethnl_notअगरy_features(ptr);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block ethnl_netdev_notअगरier = अणु
	.notअगरier_call = ethnl_netdev_event,
पूर्ण;

/* genetlink setup */

अटल स्थिर काष्ठा genl_ops ethtool_genl_ops[] = अणु
	अणु
		.cmd	= ETHTOOL_MSG_STRSET_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_strset_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_strset_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_LINKINFO_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_linkinfo_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_linkinfo_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_LINKINFO_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_linkinfo,
		.policy = ethnl_linkinfo_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_linkinfo_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_LINKMODES_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_linkmodes_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_linkmodes_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_LINKMODES_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_linkmodes,
		.policy = ethnl_linkmodes_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_linkmodes_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_LINKSTATE_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_linkstate_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_linkstate_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_DEBUG_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_debug_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_debug_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_DEBUG_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_debug,
		.policy = ethnl_debug_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_debug_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_WOL_GET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_wol_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_wol_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_WOL_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_wol,
		.policy = ethnl_wol_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_wol_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_FEATURES_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_features_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_features_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_FEATURES_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_features,
		.policy = ethnl_features_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_features_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_PRIVFLAGS_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_privflags_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_privflags_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_PRIVFLAGS_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_privflags,
		.policy = ethnl_privflags_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_privflags_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_RINGS_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_rings_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_rings_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_RINGS_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_rings,
		.policy = ethnl_rings_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_rings_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_CHANNELS_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_channels_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_channels_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_CHANNELS_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_channels,
		.policy = ethnl_channels_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_channels_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_COALESCE_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_coalesce_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_coalesce_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_COALESCE_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_coalesce,
		.policy = ethnl_coalesce_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_coalesce_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_PAUSE_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_छोड़ो_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_छोड़ो_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_PAUSE_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_छोड़ो,
		.policy = ethnl_छोड़ो_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_छोड़ो_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_EEE_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_eee_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_eee_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_EEE_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_eee,
		.policy = ethnl_eee_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_eee_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_TSINFO_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_tsinfo_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_tsinfo_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_CABLE_TEST_ACT,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_act_cable_test,
		.policy = ethnl_cable_test_act_policy,
		.maxattr = ARRAY_SIZE(ethnl_cable_test_act_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_CABLE_TEST_TDR_ACT,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_act_cable_test_tdr,
		.policy = ethnl_cable_test_tdr_act_policy,
		.maxattr = ARRAY_SIZE(ethnl_cable_test_tdr_act_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_TUNNEL_INFO_GET,
		.करोit	= ethnl_tunnel_info_करोit,
		.start	= ethnl_tunnel_info_start,
		.dumpit	= ethnl_tunnel_info_dumpit,
		.policy = ethnl_tunnel_info_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_tunnel_info_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_FEC_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_fec_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_fec_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_FEC_SET,
		.flags	= GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_set_fec,
		.policy = ethnl_fec_set_policy,
		.maxattr = ARRAY_SIZE(ethnl_fec_set_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_MODULE_EEPROM_GET,
		.flags  = GENL_UNS_ADMIN_PERM,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_module_eeprom_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_module_eeprom_get_policy) - 1,
	पूर्ण,
	अणु
		.cmd	= ETHTOOL_MSG_STATS_GET,
		.करोit	= ethnl_शेष_करोit,
		.start	= ethnl_शेष_start,
		.dumpit	= ethnl_शेष_dumpit,
		.करोne	= ethnl_शेष_करोne,
		.policy = ethnl_stats_get_policy,
		.maxattr = ARRAY_SIZE(ethnl_stats_get_policy) - 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group ethtool_nl_mcgrps[] = अणु
	[ETHNL_MCGRP_MONITOR] = अणु .name = ETHTOOL_MCGRP_MONITOR_NAME पूर्ण,
पूर्ण;

अटल काष्ठा genl_family ethtool_genl_family __ro_after_init = अणु
	.name		= ETHTOOL_GENL_NAME,
	.version	= ETHTOOL_GENL_VERSION,
	.netnsok	= true,
	.parallel_ops	= true,
	.ops		= ethtool_genl_ops,
	.n_ops		= ARRAY_SIZE(ethtool_genl_ops),
	.mcgrps		= ethtool_nl_mcgrps,
	.n_mcgrps	= ARRAY_SIZE(ethtool_nl_mcgrps),
पूर्ण;

/* module setup */

अटल पूर्णांक __init ethnl_init(व्योम)
अणु
	पूर्णांक ret;

	ret = genl_रेजिस्टर_family(&ethtool_genl_family);
	अगर (WARN(ret < 0, "ethtool: genetlink family registration failed"))
		वापस ret;
	ethnl_ok = true;

	ret = रेजिस्टर_netdevice_notअगरier(&ethnl_netdev_notअगरier);
	WARN(ret < 0, "ethtool: net device notifier registration failed");
	वापस ret;
पूर्ण

subsys_initcall(ethnl_init);
