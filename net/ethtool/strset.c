<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश "netlink.h"
#समावेश "common.h"

काष्ठा strset_info अणु
	bool per_dev;
	bool मुक्त_strings;
	अचिन्हित पूर्णांक count;
	स्थिर अक्षर (*strings)[ETH_GSTRING_LEN];
पूर्ण;

अटल स्थिर काष्ठा strset_info info_ढाँचा[] = अणु
	[ETH_SS_TEST] = अणु
		.per_dev	= true,
	पूर्ण,
	[ETH_SS_STATS] = अणु
		.per_dev	= true,
	पूर्ण,
	[ETH_SS_PRIV_FLAGS] = अणु
		.per_dev	= true,
	पूर्ण,
	[ETH_SS_FEATURES] = अणु
		.per_dev	= false,
		.count		= ARRAY_SIZE(netdev_features_strings),
		.strings	= netdev_features_strings,
	पूर्ण,
	[ETH_SS_RSS_HASH_FUNCS] = अणु
		.per_dev	= false,
		.count		= ARRAY_SIZE(rss_hash_func_strings),
		.strings	= rss_hash_func_strings,
	पूर्ण,
	[ETH_SS_TUNABLES] = अणु
		.per_dev	= false,
		.count		= ARRAY_SIZE(tunable_strings),
		.strings	= tunable_strings,
	पूर्ण,
	[ETH_SS_PHY_STATS] = अणु
		.per_dev	= true,
	पूर्ण,
	[ETH_SS_PHY_TUNABLES] = अणु
		.per_dev	= false,
		.count		= ARRAY_SIZE(phy_tunable_strings),
		.strings	= phy_tunable_strings,
	पूर्ण,
	[ETH_SS_LINK_MODES] = अणु
		.per_dev	= false,
		.count		= __ETHTOOL_LINK_MODE_MASK_NBITS,
		.strings	= link_mode_names,
	पूर्ण,
	[ETH_SS_MSG_CLASSES] = अणु
		.per_dev	= false,
		.count		= NETIF_MSG_CLASS_COUNT,
		.strings	= netअगर_msg_class_names,
	पूर्ण,
	[ETH_SS_WOL_MODES] = अणु
		.per_dev	= false,
		.count		= WOL_MODE_COUNT,
		.strings	= wol_mode_names,
	पूर्ण,
	[ETH_SS_SOF_TIMESTAMPING] = अणु
		.per_dev	= false,
		.count		= __SOF_TIMESTAMPING_CNT,
		.strings	= sof_बारtamping_names,
	पूर्ण,
	[ETH_SS_TS_TX_TYPES] = अणु
		.per_dev	= false,
		.count		= __HWTSTAMP_TX_CNT,
		.strings	= ts_tx_type_names,
	पूर्ण,
	[ETH_SS_TS_RX_FILTERS] = अणु
		.per_dev	= false,
		.count		= __HWTSTAMP_FILTER_CNT,
		.strings	= ts_rx_filter_names,
	पूर्ण,
	[ETH_SS_UDP_TUNNEL_TYPES] = अणु
		.per_dev	= false,
		.count		= __ETHTOOL_UDP_TUNNEL_TYPE_CNT,
		.strings	= udp_tunnel_type_names,
	पूर्ण,
	[ETH_SS_STATS_STD] = अणु
		.per_dev	= false,
		.count		= __ETHTOOL_STATS_CNT,
		.strings	= stats_std_names,
	पूर्ण,
	[ETH_SS_STATS_ETH_PHY] = अणु
		.per_dev	= false,
		.count		= __ETHTOOL_A_STATS_ETH_PHY_CNT,
		.strings	= stats_eth_phy_names,
	पूर्ण,
	[ETH_SS_STATS_ETH_MAC] = अणु
		.per_dev	= false,
		.count		= __ETHTOOL_A_STATS_ETH_MAC_CNT,
		.strings	= stats_eth_mac_names,
	पूर्ण,
	[ETH_SS_STATS_ETH_CTRL] = अणु
		.per_dev	= false,
		.count		= __ETHTOOL_A_STATS_ETH_CTRL_CNT,
		.strings	= stats_eth_ctrl_names,
	पूर्ण,
	[ETH_SS_STATS_RMON] = अणु
		.per_dev	= false,
		.count		= __ETHTOOL_A_STATS_RMON_CNT,
		.strings	= stats_rmon_names,
	पूर्ण,
पूर्ण;

काष्ठा strset_req_info अणु
	काष्ठा ethnl_req_info		base;
	u32				req_ids;
	bool				counts_only;
पूर्ण;

#घोषणा STRSET_REQINFO(__req_base) \
	container_of(__req_base, काष्ठा strset_req_info, base)

काष्ठा strset_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा strset_info		sets[ETH_SS_COUNT];
पूर्ण;

#घोषणा STRSET_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा strset_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_strset_get_policy[] = अणु
	[ETHTOOL_A_STRSET_HEADER]	=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_STRSET_STRINGSETS]	= अणु .type = NLA_NESTED पूर्ण,
	[ETHTOOL_A_STRSET_COUNTS_ONLY]	= अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy get_stringset_policy[] = अणु
	[ETHTOOL_A_STRINGSET_ID]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

/**
 * strset_include() - test अगर a string set should be included in reply
 * @info: parsed client request
 * @data: poपूर्णांकer to request data काष्ठाure
 * @id:   id of string set to check (ETH_SS_* स्थिरants)
 */
अटल bool strset_include(स्थिर काष्ठा strset_req_info *info,
			   स्थिर काष्ठा strset_reply_data *data, u32 id)
अणु
	bool per_dev;

	BUILD_BUG_ON(ETH_SS_COUNT >= BITS_PER_BYTE * माप(info->req_ids));

	अगर (info->req_ids)
		वापस info->req_ids & (1U << id);
	per_dev = data->sets[id].per_dev;
	अगर (!per_dev && !data->sets[id].strings)
		वापस false;

	वापस data->base.dev ? per_dev : !per_dev;
पूर्ण

अटल पूर्णांक strset_get_id(स्थिर काष्ठा nlattr *nest, u32 *val,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा nlattr *tb[ARRAY_SIZE(get_stringset_policy)];
	पूर्णांक ret;

	ret = nla_parse_nested(tb, ARRAY_SIZE(get_stringset_policy) - 1, nest,
			       get_stringset_policy, extack);
	अगर (ret < 0)
		वापस ret;
	अगर (!tb[ETHTOOL_A_STRINGSET_ID])
		वापस -EINVAL;

	*val = nla_get_u32(tb[ETHTOOL_A_STRINGSET_ID]);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nla_policy strset_stringsets_policy[] = अणु
	[ETHTOOL_A_STRINGSETS_STRINGSET]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक strset_parse_request(काष्ठा ethnl_req_info *req_base,
				काष्ठा nlattr **tb,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा strset_req_info *req_info = STRSET_REQINFO(req_base);
	काष्ठा nlattr *nest = tb[ETHTOOL_A_STRSET_STRINGSETS];
	काष्ठा nlattr *attr;
	पूर्णांक rem, ret;

	अगर (!nest)
		वापस 0;
	ret = nla_validate_nested(nest,
				  ARRAY_SIZE(strset_stringsets_policy) - 1,
				  strset_stringsets_policy, extack);
	अगर (ret < 0)
		वापस ret;

	req_info->counts_only = tb[ETHTOOL_A_STRSET_COUNTS_ONLY];
	nla_क्रम_each_nested(attr, nest, rem) अणु
		u32 id;

		अगर (WARN_ONCE(nla_type(attr) != ETHTOOL_A_STRINGSETS_STRINGSET,
			      "unexpected attrtype %u in ETHTOOL_A_STRSET_STRINGSETS\n",
			      nla_type(attr)))
			वापस -EINVAL;

		ret = strset_get_id(attr, &id, extack);
		अगर (ret < 0)
			वापस ret;
		अगर (id >= ETH_SS_COUNT) अणु
			NL_SET_ERR_MSG_ATTR(extack, attr,
					    "unknown string set id");
			वापस -EOPNOTSUPP;
		पूर्ण

		req_info->req_ids |= (1U << id);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम strset_cleanup_data(काष्ठा ethnl_reply_data *reply_base)
अणु
	काष्ठा strset_reply_data *data = STRSET_REPDATA(reply_base);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ETH_SS_COUNT; i++)
		अगर (data->sets[i].मुक्त_strings) अणु
			kमुक्त(data->sets[i].strings);
			data->sets[i].strings = शून्य;
			data->sets[i].मुक्त_strings = false;
		पूर्ण
पूर्ण

अटल पूर्णांक strset_prepare_set(काष्ठा strset_info *info, काष्ठा net_device *dev,
			      अचिन्हित पूर्णांक id, bool counts_only)
अणु
	स्थिर काष्ठा ethtool_phy_ops *phy_ops = ethtool_phy_ops;
	स्थिर काष्ठा ethtool_ops *ops = dev->ethtool_ops;
	व्योम *strings;
	पूर्णांक count, ret;

	अगर (id == ETH_SS_PHY_STATS && dev->phydev &&
	    !ops->get_ethtool_phy_stats && phy_ops &&
	    phy_ops->get_sset_count)
		ret = phy_ops->get_sset_count(dev->phydev);
	अन्यथा अगर (ops->get_sset_count && ops->get_strings)
		ret = ops->get_sset_count(dev, id);
	अन्यथा
		ret = -EOPNOTSUPP;
	अगर (ret <= 0) अणु
		info->count = 0;
		वापस 0;
	पूर्ण

	count = ret;
	अगर (!counts_only) अणु
		strings = kसुस्मृति(count, ETH_GSTRING_LEN, GFP_KERNEL);
		अगर (!strings)
			वापस -ENOMEM;
		अगर (id == ETH_SS_PHY_STATS && dev->phydev &&
		    !ops->get_ethtool_phy_stats && phy_ops &&
		    phy_ops->get_strings)
			phy_ops->get_strings(dev->phydev, strings);
		अन्यथा
			ops->get_strings(dev, id, strings);
		info->strings = strings;
		info->मुक्त_strings = true;
	पूर्ण
	info->count = count;

	वापस 0;
पूर्ण

अटल पूर्णांक strset_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			       काष्ठा ethnl_reply_data *reply_base,
			       काष्ठा genl_info *info)
अणु
	स्थिर काष्ठा strset_req_info *req_info = STRSET_REQINFO(req_base);
	काष्ठा strset_reply_data *data = STRSET_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	BUILD_BUG_ON(ARRAY_SIZE(info_ढाँचा) != ETH_SS_COUNT);
	स_नकल(&data->sets, &info_ढाँचा, माप(data->sets));

	अगर (!dev) अणु
		क्रम (i = 0; i < ETH_SS_COUNT; i++) अणु
			अगर ((req_info->req_ids & (1U << i)) &&
			    data->sets[i].per_dev) अणु
				अगर (info)
					GENL_SET_ERR_MSG(info, "requested per device strings without dev");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ err_strset;
	क्रम (i = 0; i < ETH_SS_COUNT; i++) अणु
		अगर (!strset_include(req_info, data, i) ||
		    !data->sets[i].per_dev)
			जारी;

		ret = strset_prepare_set(&data->sets[i], dev, i,
					 req_info->counts_only);
		अगर (ret < 0)
			जाओ err_ops;
	पूर्ण
	ethnl_ops_complete(dev);

	वापस 0;
err_ops:
	ethnl_ops_complete(dev);
err_strset:
	strset_cleanup_data(reply_base);
	वापस ret;
पूर्ण

/* calculate size of ETHTOOL_A_STRSET_STRINGSET nest क्रम one string set */
अटल पूर्णांक strset_set_size(स्थिर काष्ठा strset_info *info, bool counts_only)
अणु
	अचिन्हित पूर्णांक len = 0;
	अचिन्हित पूर्णांक i;

	अगर (info->count == 0)
		वापस 0;
	अगर (counts_only)
		वापस nla_total_size(2 * nla_total_size(माप(u32)));

	क्रम (i = 0; i < info->count; i++) अणु
		स्थिर अक्षर *str = info->strings[i];

		/* ETHTOOL_A_STRING_INDEX, ETHTOOL_A_STRING_VALUE, nest */
		len += nla_total_size(nla_total_size(माप(u32)) +
				      ethnl_strz_size(str));
	पूर्ण
	/* ETHTOOL_A_STRINGSET_ID, ETHTOOL_A_STRINGSET_COUNT */
	len = 2 * nla_total_size(माप(u32)) + nla_total_size(len);

	वापस nla_total_size(len);
पूर्ण

अटल पूर्णांक strset_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			     स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा strset_req_info *req_info = STRSET_REQINFO(req_base);
	स्थिर काष्ठा strset_reply_data *data = STRSET_REPDATA(reply_base);
	अचिन्हित पूर्णांक i;
	पूर्णांक len = 0;
	पूर्णांक ret;

	len += nla_total_size(0); /* ETHTOOL_A_STRSET_STRINGSETS */

	क्रम (i = 0; i < ETH_SS_COUNT; i++) अणु
		स्थिर काष्ठा strset_info *set_info = &data->sets[i];

		अगर (!strset_include(req_info, data, i))
			जारी;

		ret = strset_set_size(set_info, req_info->counts_only);
		अगर (ret < 0)
			वापस ret;
		len += ret;
	पूर्ण

	वापस len;
पूर्ण

/* fill one string पूर्णांकo reply */
अटल पूर्णांक strset_fill_string(काष्ठा sk_buff *skb,
			      स्थिर काष्ठा strset_info *set_info, u32 idx)
अणु
	काष्ठा nlattr *string_attr;
	स्थिर अक्षर *value;

	value = set_info->strings[idx];

	string_attr = nla_nest_start(skb, ETHTOOL_A_STRINGS_STRING);
	अगर (!string_attr)
		वापस -EMSGSIZE;
	अगर (nla_put_u32(skb, ETHTOOL_A_STRING_INDEX, idx) ||
	    ethnl_put_strz(skb, ETHTOOL_A_STRING_VALUE, value))
		जाओ nla_put_failure;
	nla_nest_end(skb, string_attr);

	वापस 0;
nla_put_failure:
	nla_nest_cancel(skb, string_attr);
	वापस -EMSGSIZE;
पूर्ण

/* fill one string set पूर्णांकo reply */
अटल पूर्णांक strset_fill_set(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा strset_info *set_info, u32 id,
			   bool counts_only)
अणु
	काष्ठा nlattr *stringset_attr;
	काष्ठा nlattr *strings_attr;
	अचिन्हित पूर्णांक i;

	अगर (!set_info->per_dev && !set_info->strings)
		वापस -EOPNOTSUPP;
	अगर (set_info->count == 0)
		वापस 0;
	stringset_attr = nla_nest_start(skb, ETHTOOL_A_STRINGSETS_STRINGSET);
	अगर (!stringset_attr)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, ETHTOOL_A_STRINGSET_ID, id) ||
	    nla_put_u32(skb, ETHTOOL_A_STRINGSET_COUNT, set_info->count))
		जाओ nla_put_failure;

	अगर (!counts_only) अणु
		strings_attr = nla_nest_start(skb, ETHTOOL_A_STRINGSET_STRINGS);
		अगर (!strings_attr)
			जाओ nla_put_failure;
		क्रम (i = 0; i < set_info->count; i++) अणु
			अगर (strset_fill_string(skb, set_info, i) < 0)
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(skb, strings_attr);
	पूर्ण

	nla_nest_end(skb, stringset_attr);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, stringset_attr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक strset_fill_reply(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा ethnl_req_info *req_base,
			     स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा strset_req_info *req_info = STRSET_REQINFO(req_base);
	स्थिर काष्ठा strset_reply_data *data = STRSET_REPDATA(reply_base);
	काष्ठा nlattr *nest;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	nest = nla_nest_start(skb, ETHTOOL_A_STRSET_STRINGSETS);
	अगर (!nest)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < ETH_SS_COUNT; i++) अणु
		अगर (strset_include(req_info, data, i)) अणु
			ret = strset_fill_set(skb, &data->sets[i], i,
					      req_info->counts_only);
			अगर (ret < 0)
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;

nla_put_failure:
	nla_nest_cancel(skb, nest);
	वापस ret;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_strset_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_STRSET_GET,
	.reply_cmd		= ETHTOOL_MSG_STRSET_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_STRSET_HEADER,
	.req_info_size		= माप(काष्ठा strset_req_info),
	.reply_data_size	= माप(काष्ठा strset_reply_data),
	.allow_nodev_करो		= true,

	.parse_request		= strset_parse_request,
	.prepare_data		= strset_prepare_data,
	.reply_size		= strset_reply_size,
	.fill_reply		= strset_fill_reply,
	.cleanup_data		= strset_cleanup_data,
पूर्ण;
