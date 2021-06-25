<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

काष्ठा features_req_info अणु
	काष्ठा ethnl_req_info	base;
पूर्ण;

काष्ठा features_reply_data अणु
	काष्ठा ethnl_reply_data	base;
	u32			hw[ETHTOOL_DEV_FEATURE_WORDS];
	u32			wanted[ETHTOOL_DEV_FEATURE_WORDS];
	u32			active[ETHTOOL_DEV_FEATURE_WORDS];
	u32			nochange[ETHTOOL_DEV_FEATURE_WORDS];
	u32			all[ETHTOOL_DEV_FEATURE_WORDS];
पूर्ण;

#घोषणा FEATURES_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा features_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_features_get_policy[] = अणु
	[ETHTOOL_A_FEATURES_HEADER]	=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल व्योम ethnl_features_to_biपंचांगap32(u32 *dest, netdev_features_t src)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ETHTOOL_DEV_FEATURE_WORDS; i++)
		dest[i] = src >> (32 * i);
पूर्ण

अटल पूर्णांक features_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
				 काष्ठा ethnl_reply_data *reply_base,
				 काष्ठा genl_info *info)
अणु
	काष्ठा features_reply_data *data = FEATURES_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	netdev_features_t all_features;

	ethnl_features_to_biपंचांगap32(data->hw, dev->hw_features);
	ethnl_features_to_biपंचांगap32(data->wanted, dev->wanted_features);
	ethnl_features_to_biपंचांगap32(data->active, dev->features);
	ethnl_features_to_biपंचांगap32(data->nochange, NETIF_F_NEVER_CHANGE);
	all_features = GENMASK_ULL(NETDEV_FEATURE_COUNT - 1, 0);
	ethnl_features_to_biपंचांगap32(data->all, all_features);

	वापस 0;
पूर्ण

अटल पूर्णांक features_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा features_reply_data *data = FEATURES_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	अचिन्हित पूर्णांक len = 0;
	पूर्णांक ret;

	ret = ethnl_bitset32_size(data->hw, data->all, NETDEV_FEATURE_COUNT,
				  netdev_features_strings, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;
	ret = ethnl_bitset32_size(data->wanted, शून्य, NETDEV_FEATURE_COUNT,
				  netdev_features_strings, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;
	ret = ethnl_bitset32_size(data->active, शून्य, NETDEV_FEATURE_COUNT,
				  netdev_features_strings, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;
	ret = ethnl_bitset32_size(data->nochange, शून्य, NETDEV_FEATURE_COUNT,
				  netdev_features_strings, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;

	वापस len;
पूर्ण

अटल पूर्णांक features_fill_reply(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा features_reply_data *data = FEATURES_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	पूर्णांक ret;

	ret = ethnl_put_bitset32(skb, ETHTOOL_A_FEATURES_HW, data->hw,
				 data->all, NETDEV_FEATURE_COUNT,
				 netdev_features_strings, compact);
	अगर (ret < 0)
		वापस ret;
	ret = ethnl_put_bitset32(skb, ETHTOOL_A_FEATURES_WANTED, data->wanted,
				 शून्य, NETDEV_FEATURE_COUNT,
				 netdev_features_strings, compact);
	अगर (ret < 0)
		वापस ret;
	ret = ethnl_put_bitset32(skb, ETHTOOL_A_FEATURES_ACTIVE, data->active,
				 शून्य, NETDEV_FEATURE_COUNT,
				 netdev_features_strings, compact);
	अगर (ret < 0)
		वापस ret;
	वापस ethnl_put_bitset32(skb, ETHTOOL_A_FEATURES_NOCHANGE,
				  data->nochange, शून्य, NETDEV_FEATURE_COUNT,
				  netdev_features_strings, compact);
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_features_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_FEATURES_GET,
	.reply_cmd		= ETHTOOL_MSG_FEATURES_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_FEATURES_HEADER,
	.req_info_size		= माप(काष्ठा features_req_info),
	.reply_data_size	= माप(काष्ठा features_reply_data),

	.prepare_data		= features_prepare_data,
	.reply_size		= features_reply_size,
	.fill_reply		= features_fill_reply,
पूर्ण;

/* FEATURES_SET */

स्थिर काष्ठा nla_policy ethnl_features_set_policy[] = अणु
	[ETHTOOL_A_FEATURES_HEADER]	=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_FEATURES_WANTED]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल व्योम ethnl_features_to_biपंचांगap(अचिन्हित दीर्घ *dest, netdev_features_t val)
अणु
	स्थिर अचिन्हित पूर्णांक words = BITS_TO_LONGS(NETDEV_FEATURE_COUNT);
	अचिन्हित पूर्णांक i;

	biपंचांगap_zero(dest, NETDEV_FEATURE_COUNT);
	क्रम (i = 0; i < words; i++)
		dest[i] = (अचिन्हित दीर्घ)(val >> (i * BITS_PER_LONG));
पूर्ण

अटल netdev_features_t ethnl_biपंचांगap_to_features(अचिन्हित दीर्घ *src)
अणु
	स्थिर अचिन्हित पूर्णांक nft_bits = माप(netdev_features_t) * BITS_PER_BYTE;
	स्थिर अचिन्हित पूर्णांक words = BITS_TO_LONGS(NETDEV_FEATURE_COUNT);
	netdev_features_t ret = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < words; i++)
		ret |= (netdev_features_t)(src[i]) << (i * BITS_PER_LONG);
	ret &= ~(netdev_features_t)0 >> (nft_bits - NETDEV_FEATURE_COUNT);
	वापस ret;
पूर्ण

अटल पूर्णांक features_send_reply(काष्ठा net_device *dev, काष्ठा genl_info *info,
			       स्थिर अचिन्हित दीर्घ *wanted,
			       स्थिर अचिन्हित दीर्घ *wanted_mask,
			       स्थिर अचिन्हित दीर्घ *active,
			       स्थिर अचिन्हित दीर्घ *active_mask, bool compact)
अणु
	काष्ठा sk_buff *rskb;
	व्योम *reply_payload;
	पूर्णांक reply_len = 0;
	पूर्णांक ret;

	reply_len = ethnl_reply_header_size();
	ret = ethnl_bitset_size(wanted, wanted_mask, NETDEV_FEATURE_COUNT,
				netdev_features_strings, compact);
	अगर (ret < 0)
		जाओ err;
	reply_len += ret;
	ret = ethnl_bitset_size(active, active_mask, NETDEV_FEATURE_COUNT,
				netdev_features_strings, compact);
	अगर (ret < 0)
		जाओ err;
	reply_len += ret;

	ret = -ENOMEM;
	rskb = ethnl_reply_init(reply_len, dev, ETHTOOL_MSG_FEATURES_SET_REPLY,
				ETHTOOL_A_FEATURES_HEADER, info,
				&reply_payload);
	अगर (!rskb)
		जाओ err;

	ret = ethnl_put_bitset(rskb, ETHTOOL_A_FEATURES_WANTED, wanted,
			       wanted_mask, NETDEV_FEATURE_COUNT,
			       netdev_features_strings, compact);
	अगर (ret < 0)
		जाओ nla_put_failure;
	ret = ethnl_put_bitset(rskb, ETHTOOL_A_FEATURES_ACTIVE, active,
			       active_mask, NETDEV_FEATURE_COUNT,
			       netdev_features_strings, compact);
	अगर (ret < 0)
		जाओ nla_put_failure;

	genlmsg_end(rskb, reply_payload);
	ret = genlmsg_reply(rskb, info);
	वापस ret;

nla_put_failure:
	nlmsg_मुक्त(rskb);
	WARN_ONCE(1, "calculated message payload length (%d) not sufficient\n",
		  reply_len);
err:
	GENL_SET_ERR_MSG(info, "failed to send reply message");
	वापस ret;
पूर्ण

पूर्णांक ethnl_set_features(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	DECLARE_BITMAP(wanted_dअगरf_mask, NETDEV_FEATURE_COUNT);
	DECLARE_BITMAP(active_dअगरf_mask, NETDEV_FEATURE_COUNT);
	DECLARE_BITMAP(old_active, NETDEV_FEATURE_COUNT);
	DECLARE_BITMAP(old_wanted, NETDEV_FEATURE_COUNT);
	DECLARE_BITMAP(new_active, NETDEV_FEATURE_COUNT);
	DECLARE_BITMAP(new_wanted, NETDEV_FEATURE_COUNT);
	DECLARE_BITMAP(req_wanted, NETDEV_FEATURE_COUNT);
	DECLARE_BITMAP(req_mask, NETDEV_FEATURE_COUNT);
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा net_device *dev;
	bool mod;
	पूर्णांक ret;

	अगर (!tb[ETHTOOL_A_FEATURES_WANTED])
		वापस -EINVAL;
	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_FEATURES_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;

	rtnl_lock();
	ethnl_features_to_biपंचांगap(old_active, dev->features);
	ethnl_features_to_biपंचांगap(old_wanted, dev->wanted_features);
	ret = ethnl_parse_bitset(req_wanted, req_mask, NETDEV_FEATURE_COUNT,
				 tb[ETHTOOL_A_FEATURES_WANTED],
				 netdev_features_strings, info->extack);
	अगर (ret < 0)
		जाओ out_rtnl;
	अगर (ethnl_biपंचांगap_to_features(req_mask) & ~NETIF_F_ETHTOOL_BITS) अणु
		GENL_SET_ERR_MSG(info, "attempt to change non-ethtool features");
		ret = -EINVAL;
		जाओ out_rtnl;
	पूर्ण

	/* set req_wanted bits not in req_mask from old_wanted */
	biपंचांगap_and(req_wanted, req_wanted, req_mask, NETDEV_FEATURE_COUNT);
	biपंचांगap_andnot(new_wanted, old_wanted, req_mask, NETDEV_FEATURE_COUNT);
	biपंचांगap_or(req_wanted, new_wanted, req_wanted, NETDEV_FEATURE_COUNT);
	अगर (!biपंचांगap_equal(req_wanted, old_wanted, NETDEV_FEATURE_COUNT)) अणु
		dev->wanted_features &= ~dev->hw_features;
		dev->wanted_features |= ethnl_biपंचांगap_to_features(req_wanted) & dev->hw_features;
		__netdev_update_features(dev);
	पूर्ण
	ethnl_features_to_biपंचांगap(new_active, dev->features);
	mod = !biपंचांगap_equal(old_active, new_active, NETDEV_FEATURE_COUNT);

	ret = 0;
	अगर (!(req_info.flags & ETHTOOL_FLAG_OMIT_REPLY)) अणु
		bool compact = req_info.flags & ETHTOOL_FLAG_COMPACT_BITSETS;

		biपंचांगap_xor(wanted_dअगरf_mask, req_wanted, new_active,
			   NETDEV_FEATURE_COUNT);
		biपंचांगap_xor(active_dअगरf_mask, old_active, new_active,
			   NETDEV_FEATURE_COUNT);
		biपंचांगap_and(wanted_dअगरf_mask, wanted_dअगरf_mask, req_mask,
			   NETDEV_FEATURE_COUNT);
		biपंचांगap_and(req_wanted, req_wanted, wanted_dअगरf_mask,
			   NETDEV_FEATURE_COUNT);
		biपंचांगap_and(new_active, new_active, active_dअगरf_mask,
			   NETDEV_FEATURE_COUNT);

		ret = features_send_reply(dev, info, req_wanted,
					  wanted_dअगरf_mask, new_active,
					  active_dअगरf_mask, compact);
	पूर्ण
	अगर (mod)
		netdev_features_change(dev);

out_rtnl:
	rtnl_unlock();
	dev_put(dev);
	वापस ret;
पूर्ण
