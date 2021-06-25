<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

काष्ठा privflags_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा privflags_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	स्थिर अक्षर			(*priv_flag_names)[ETH_GSTRING_LEN];
	अचिन्हित पूर्णांक			n_priv_flags;
	u32				priv_flags;
पूर्ण;

#घोषणा PRIVFLAGS_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा privflags_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_privflags_get_policy[] = अणु
	[ETHTOOL_A_PRIVFLAGS_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक ethnl_get_priv_flags_info(काष्ठा net_device *dev,
				     अचिन्हित पूर्णांक *count,
				     स्थिर अक्षर (**names)[ETH_GSTRING_LEN])
अणु
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	पूर्णांक nflags;

	nflags = ops->get_sset_count(dev, ETH_SS_PRIV_FLAGS);
	अगर (nflags < 0)
		वापस nflags;

	अगर (names) अणु
		*names = kसुस्मृति(nflags, ETH_GSTRING_LEN, GFP_KERNEL);
		अगर (!*names)
			वापस -ENOMEM;
		ops->get_strings(dev, ETH_SS_PRIV_FLAGS, (u8 *)*names);
	पूर्ण

	/* We can pass more than 32 निजी flags to userspace via netlink but
	 * we cannot get more with ethtool_ops::get_priv_flags(). Note that we
	 * must not adjust nflags beक्रमe allocating the space क्रम flag names
	 * as the buffer must be large enough क्रम all flags.
	 */
	अगर (WARN_ONCE(nflags > 32,
		      "device %s reports more than 32 private flags (%d)\n",
		      netdev_name(dev), nflags))
		nflags = 32;
	*count = nflags;

	वापस 0;
पूर्ण

अटल पूर्णांक privflags_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
				  काष्ठा ethnl_reply_data *reply_base,
				  काष्ठा genl_info *info)
अणु
	काष्ठा privflags_reply_data *data = PRIVFLAGS_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	स्थिर अक्षर (*names)[ETH_GSTRING_LEN];
	स्थिर काष्ठा ethtool_ops *ops;
	अचिन्हित पूर्णांक nflags;
	पूर्णांक ret;

	ops = dev->ethtool_ops;
	अगर (!ops->get_priv_flags || !ops->get_sset_count || !ops->get_strings)
		वापस -EOPNOTSUPP;
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;

	ret = ethnl_get_priv_flags_info(dev, &nflags, &names);
	अगर (ret < 0)
		जाओ out_ops;
	data->priv_flags = ops->get_priv_flags(dev);
	data->priv_flag_names = names;
	data->n_priv_flags = nflags;

out_ops:
	ethnl_ops_complete(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक privflags_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
				स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा privflags_reply_data *data = PRIVFLAGS_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर u32 all_flags = ~(u32)0 >> (32 - data->n_priv_flags);

	वापस ethnl_bitset32_size(&data->priv_flags, &all_flags,
				   data->n_priv_flags,
				   data->priv_flag_names, compact);
पूर्ण

अटल पूर्णांक privflags_fill_reply(काष्ठा sk_buff *skb,
				स्थिर काष्ठा ethnl_req_info *req_base,
				स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा privflags_reply_data *data = PRIVFLAGS_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर u32 all_flags = ~(u32)0 >> (32 - data->n_priv_flags);

	वापस ethnl_put_bitset32(skb, ETHTOOL_A_PRIVFLAGS_FLAGS,
				  &data->priv_flags, &all_flags,
				  data->n_priv_flags, data->priv_flag_names,
				  compact);
पूर्ण

अटल व्योम privflags_cleanup_data(काष्ठा ethnl_reply_data *reply_data)
अणु
	काष्ठा privflags_reply_data *data = PRIVFLAGS_REPDATA(reply_data);

	kमुक्त(data->priv_flag_names);
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_privflags_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_PRIVFLAGS_GET,
	.reply_cmd		= ETHTOOL_MSG_PRIVFLAGS_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_PRIVFLAGS_HEADER,
	.req_info_size		= माप(काष्ठा privflags_req_info),
	.reply_data_size	= माप(काष्ठा privflags_reply_data),

	.prepare_data		= privflags_prepare_data,
	.reply_size		= privflags_reply_size,
	.fill_reply		= privflags_fill_reply,
	.cleanup_data		= privflags_cleanup_data,
पूर्ण;

/* PRIVFLAGS_SET */

स्थिर काष्ठा nla_policy ethnl_privflags_set_policy[] = अणु
	[ETHTOOL_A_PRIVFLAGS_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_PRIVFLAGS_FLAGS]		= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_privflags(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	स्थिर अक्षर (*names)[ETH_GSTRING_LEN] = शून्य;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	स्थिर काष्ठा ethtool_ops *ops;
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक nflags;
	bool mod = false;
	bool compact;
	u32 flags;
	पूर्णांक ret;

	अगर (!tb[ETHTOOL_A_PRIVFLAGS_FLAGS])
		वापस -EINVAL;
	ret = ethnl_bitset_is_compact(tb[ETHTOOL_A_PRIVFLAGS_FLAGS], &compact);
	अगर (ret < 0)
		वापस ret;
	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_PRIVFLAGS_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	अगर (!ops->get_priv_flags || !ops->set_priv_flags ||
	    !ops->get_sset_count || !ops->get_strings)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;
	ret = ethnl_get_priv_flags_info(dev, &nflags, compact ? शून्य : &names);
	अगर (ret < 0)
		जाओ out_ops;
	flags = ops->get_priv_flags(dev);

	ret = ethnl_update_bitset32(&flags, nflags,
				    tb[ETHTOOL_A_PRIVFLAGS_FLAGS], names,
				    info->extack, &mod);
	अगर (ret < 0 || !mod)
		जाओ out_मुक्त;
	ret = ops->set_priv_flags(dev, flags);
	अगर (ret < 0)
		जाओ out_मुक्त;
	ethtool_notअगरy(dev, ETHTOOL_MSG_PRIVFLAGS_NTF, शून्य);

out_मुक्त:
	kमुक्त(names);
out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
