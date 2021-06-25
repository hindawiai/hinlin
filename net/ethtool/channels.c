<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <net/xdp_sock_drv.h>

#समावेश "netlink.h"
#समावेश "common.h"

काष्ठा channels_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा channels_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_channels		channels;
पूर्ण;

#घोषणा CHANNELS_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा channels_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_channels_get_policy[] = अणु
	[ETHTOOL_A_CHANNELS_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक channels_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
				 काष्ठा ethnl_reply_data *reply_base,
				 काष्ठा genl_info *info)
अणु
	काष्ठा channels_reply_data *data = CHANNELS_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_channels)
		वापस -EOPNOTSUPP;
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	dev->ethtool_ops->get_channels(dev, &data->channels);
	ethnl_ops_complete(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक channels_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	वापस nla_total_size(माप(u32)) +	/* _CHANNELS_RX_MAX */
	       nla_total_size(माप(u32)) +	/* _CHANNELS_TX_MAX */
	       nla_total_size(माप(u32)) +	/* _CHANNELS_OTHER_MAX */
	       nla_total_size(माप(u32)) +	/* _CHANNELS_COMBINED_MAX */
	       nla_total_size(माप(u32)) +	/* _CHANNELS_RX_COUNT */
	       nla_total_size(माप(u32)) +	/* _CHANNELS_TX_COUNT */
	       nla_total_size(माप(u32)) +	/* _CHANNELS_OTHER_COUNT */
	       nla_total_size(माप(u32));	/* _CHANNELS_COMBINED_COUNT */
पूर्ण

अटल पूर्णांक channels_fill_reply(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा channels_reply_data *data = CHANNELS_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_channels *channels = &data->channels;

	अगर ((channels->max_rx &&
	     (nla_put_u32(skb, ETHTOOL_A_CHANNELS_RX_MAX,
			  channels->max_rx) ||
	      nla_put_u32(skb, ETHTOOL_A_CHANNELS_RX_COUNT,
			  channels->rx_count))) ||
	    (channels->max_tx &&
	     (nla_put_u32(skb, ETHTOOL_A_CHANNELS_TX_MAX,
			  channels->max_tx) ||
	      nla_put_u32(skb, ETHTOOL_A_CHANNELS_TX_COUNT,
			  channels->tx_count))) ||
	    (channels->max_other &&
	     (nla_put_u32(skb, ETHTOOL_A_CHANNELS_OTHER_MAX,
			  channels->max_other) ||
	      nla_put_u32(skb, ETHTOOL_A_CHANNELS_OTHER_COUNT,
			  channels->other_count))) ||
	    (channels->max_combined &&
	     (nla_put_u32(skb, ETHTOOL_A_CHANNELS_COMBINED_MAX,
			  channels->max_combined) ||
	      nla_put_u32(skb, ETHTOOL_A_CHANNELS_COMBINED_COUNT,
			  channels->combined_count))))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_channels_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_CHANNELS_GET,
	.reply_cmd		= ETHTOOL_MSG_CHANNELS_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_CHANNELS_HEADER,
	.req_info_size		= माप(काष्ठा channels_req_info),
	.reply_data_size	= माप(काष्ठा channels_reply_data),

	.prepare_data		= channels_prepare_data,
	.reply_size		= channels_reply_size,
	.fill_reply		= channels_fill_reply,
पूर्ण;

/* CHANNELS_SET */

स्थिर काष्ठा nla_policy ethnl_channels_set_policy[] = अणु
	[ETHTOOL_A_CHANNELS_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_CHANNELS_RX_COUNT]		= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_CHANNELS_TX_COUNT]		= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_CHANNELS_OTHER_COUNT]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_CHANNELS_COMBINED_COUNT]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_channels(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अचिन्हित पूर्णांक from_channel, old_total, i;
	bool mod = false, mod_combined = false;
	काष्ठा ethtool_channels channels = अणुपूर्ण;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	u32 err_attr, max_rx_in_use = 0;
	स्थिर काष्ठा ethtool_ops *ops;
	काष्ठा net_device *dev;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_CHANNELS_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	अगर (!ops->get_channels || !ops->set_channels)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;
	ops->get_channels(dev, &channels);
	old_total = channels.combined_count +
		    max(channels.rx_count, channels.tx_count);

	ethnl_update_u32(&channels.rx_count, tb[ETHTOOL_A_CHANNELS_RX_COUNT],
			 &mod);
	ethnl_update_u32(&channels.tx_count, tb[ETHTOOL_A_CHANNELS_TX_COUNT],
			 &mod);
	ethnl_update_u32(&channels.other_count,
			 tb[ETHTOOL_A_CHANNELS_OTHER_COUNT], &mod);
	ethnl_update_u32(&channels.combined_count,
			 tb[ETHTOOL_A_CHANNELS_COMBINED_COUNT], &mod_combined);
	mod |= mod_combined;
	ret = 0;
	अगर (!mod)
		जाओ out_ops;

	/* ensure new channel counts are within limits */
	अगर (channels.rx_count > channels.max_rx)
		err_attr = ETHTOOL_A_CHANNELS_RX_COUNT;
	अन्यथा अगर (channels.tx_count > channels.max_tx)
		err_attr = ETHTOOL_A_CHANNELS_TX_COUNT;
	अन्यथा अगर (channels.other_count > channels.max_other)
		err_attr = ETHTOOL_A_CHANNELS_OTHER_COUNT;
	अन्यथा अगर (channels.combined_count > channels.max_combined)
		err_attr = ETHTOOL_A_CHANNELS_COMBINED_COUNT;
	अन्यथा
		err_attr = 0;
	अगर (err_attr) अणु
		ret = -EINVAL;
		NL_SET_ERR_MSG_ATTR(info->extack, tb[err_attr],
				    "requested channel count exceeds maximum");
		जाओ out_ops;
	पूर्ण

	/* ensure there is at least one RX and one TX channel */
	अगर (!channels.combined_count && !channels.rx_count)
		err_attr = ETHTOOL_A_CHANNELS_RX_COUNT;
	अन्यथा अगर (!channels.combined_count && !channels.tx_count)
		err_attr = ETHTOOL_A_CHANNELS_TX_COUNT;
	अन्यथा
		err_attr = 0;
	अगर (err_attr) अणु
		अगर (mod_combined)
			err_attr = ETHTOOL_A_CHANNELS_COMBINED_COUNT;
		ret = -EINVAL;
		NL_SET_ERR_MSG_ATTR(info->extack, tb[err_attr],
				    "requested channel counts would result in no RX or TX channel being configured");
		जाओ out_ops;
	पूर्ण

	/* ensure the new Rx count fits within the configured Rx flow
	 * indirection table settings
	 */
	अगर (netअगर_is_rxfh_configured(dev) &&
	    !ethtool_get_max_rxfh_channel(dev, &max_rx_in_use) &&
	    (channels.combined_count + channels.rx_count) <= max_rx_in_use) अणु
		ret = -EINVAL;
		GENL_SET_ERR_MSG(info, "requested channel counts are too low for existing indirection table settings");
		जाओ out_ops;
	पूर्ण

	/* Disabling channels, query zero-copy AF_XDP sockets */
	from_channel = channels.combined_count +
		       min(channels.rx_count, channels.tx_count);
	क्रम (i = from_channel; i < old_total; i++)
		अगर (xsk_get_pool_from_qid(dev, i)) अणु
			ret = -EINVAL;
			GENL_SET_ERR_MSG(info, "requested channel counts are too low for existing zerocopy AF_XDP sockets");
			जाओ out_ops;
		पूर्ण

	ret = dev->ethtool_ops->set_channels(dev, &channels);
	अगर (ret < 0)
		जाओ out_ops;
	ethtool_notअगरy(dev, ETHTOOL_MSG_CHANNELS_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
