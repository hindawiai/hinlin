<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

काष्ठा debug_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा debug_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	u32				msg_mask;
पूर्ण;

#घोषणा DEBUG_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा debug_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_debug_get_policy[] = अणु
	[ETHTOOL_A_DEBUG_HEADER]	=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक debug_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			      काष्ठा ethnl_reply_data *reply_base,
			      काष्ठा genl_info *info)
अणु
	काष्ठा debug_reply_data *data = DEBUG_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_msglevel)
		वापस -EOPNOTSUPP;

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	data->msg_mask = dev->ethtool_ops->get_msglevel(dev);
	ethnl_ops_complete(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक debug_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा debug_reply_data *data = DEBUG_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;

	वापस ethnl_bitset32_size(&data->msg_mask, शून्य, NETIF_MSG_CLASS_COUNT,
				   netअगर_msg_class_names, compact);
पूर्ण

अटल पूर्णांक debug_fill_reply(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा debug_reply_data *data = DEBUG_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;

	वापस ethnl_put_bitset32(skb, ETHTOOL_A_DEBUG_MSGMASK, &data->msg_mask,
				  शून्य, NETIF_MSG_CLASS_COUNT,
				  netअगर_msg_class_names, compact);
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_debug_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_DEBUG_GET,
	.reply_cmd		= ETHTOOL_MSG_DEBUG_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_DEBUG_HEADER,
	.req_info_size		= माप(काष्ठा debug_req_info),
	.reply_data_size	= माप(काष्ठा debug_reply_data),

	.prepare_data		= debug_prepare_data,
	.reply_size		= debug_reply_size,
	.fill_reply		= debug_fill_reply,
पूर्ण;

/* DEBUG_SET */

स्थिर काष्ठा nla_policy ethnl_debug_set_policy[] = अणु
	[ETHTOOL_A_DEBUG_HEADER]	=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_DEBUG_MSGMASK]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_debug(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा net_device *dev;
	bool mod = false;
	u32 msg_mask;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_DEBUG_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ret = -EOPNOTSUPP;
	अगर (!dev->ethtool_ops->get_msglevel || !dev->ethtool_ops->set_msglevel)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;

	msg_mask = dev->ethtool_ops->get_msglevel(dev);
	ret = ethnl_update_bitset32(&msg_mask, NETIF_MSG_CLASS_COUNT,
				    tb[ETHTOOL_A_DEBUG_MSGMASK],
				    netअगर_msg_class_names, info->extack, &mod);
	अगर (ret < 0 || !mod)
		जाओ out_ops;

	dev->ethtool_ops->set_msglevel(dev, msg_mask);
	ethtool_notअगरy(dev, ETHTOOL_MSG_DEBUG_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
