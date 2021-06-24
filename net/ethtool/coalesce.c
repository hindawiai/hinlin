<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"

काष्ठा coalesce_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा coalesce_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_coalesce		coalesce;
	u32				supported_params;
पूर्ण;

#घोषणा COALESCE_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा coalesce_reply_data, base)

#घोषणा __SUPPORTED_OFFSET ETHTOOL_A_COALESCE_RX_USECS
अटल u32 attr_to_mask(अचिन्हित पूर्णांक attr_type)
अणु
	वापस BIT(attr_type - __SUPPORTED_OFFSET);
पूर्ण

/* build समय check that indices in ethtool_ops::supported_coalesce_params
 * match corresponding attribute types with an offset
 */
#घोषणा __CHECK_SUPPORTED_OFFSET(x) \
	अटल_निश्चित((ETHTOOL_ ## x) == \
		      BIT((ETHTOOL_A_ ## x) - __SUPPORTED_OFFSET))
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_STATS_BLOCK_USECS);
__CHECK_SUPPORTED_OFFSET(COALESCE_USE_ADAPTIVE_RX);
__CHECK_SUPPORTED_OFFSET(COALESCE_USE_ADAPTIVE_TX);
__CHECK_SUPPORTED_OFFSET(COALESCE_PKT_RATE_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_PKT_RATE_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_RATE_SAMPLE_INTERVAL);

स्थिर काष्ठा nla_policy ethnl_coalesce_get_policy[] = अणु
	[ETHTOOL_A_COALESCE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक coalesce_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
				 काष्ठा ethnl_reply_data *reply_base,
				 काष्ठा genl_info *info)
अणु
	काष्ठा coalesce_reply_data *data = COALESCE_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_coalesce)
		वापस -EOPNOTSUPP;
	data->supported_params = dev->ethtool_ops->supported_coalesce_params;
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	ret = dev->ethtool_ops->get_coalesce(dev, &data->coalesce);
	ethnl_ops_complete(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक coalesce_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	वापस nla_total_size(माप(u32)) +	/* _RX_USECS */
	       nla_total_size(माप(u32)) +	/* _RX_MAX_FRAMES */
	       nla_total_size(माप(u32)) +	/* _RX_USECS_IRQ */
	       nla_total_size(माप(u32)) +	/* _RX_MAX_FRAMES_IRQ */
	       nla_total_size(माप(u32)) +	/* _TX_USECS */
	       nla_total_size(माप(u32)) +	/* _TX_MAX_FRAMES */
	       nla_total_size(माप(u32)) +	/* _TX_USECS_IRQ */
	       nla_total_size(माप(u32)) +	/* _TX_MAX_FRAMES_IRQ */
	       nla_total_size(माप(u32)) +	/* _STATS_BLOCK_USECS */
	       nla_total_size(माप(u8)) +	/* _USE_ADAPTIVE_RX */
	       nla_total_size(माप(u8)) +	/* _USE_ADAPTIVE_TX */
	       nla_total_size(माप(u32)) +	/* _PKT_RATE_LOW */
	       nla_total_size(माप(u32)) +	/* _RX_USECS_LOW */
	       nla_total_size(माप(u32)) +	/* _RX_MAX_FRAMES_LOW */
	       nla_total_size(माप(u32)) +	/* _TX_USECS_LOW */
	       nla_total_size(माप(u32)) +	/* _TX_MAX_FRAMES_LOW */
	       nla_total_size(माप(u32)) +	/* _PKT_RATE_HIGH */
	       nla_total_size(माप(u32)) +	/* _RX_USECS_HIGH */
	       nla_total_size(माप(u32)) +	/* _RX_MAX_FRAMES_HIGH */
	       nla_total_size(माप(u32)) +	/* _TX_USECS_HIGH */
	       nla_total_size(माप(u32)) +	/* _TX_MAX_FRAMES_HIGH */
	       nla_total_size(माप(u32));	/* _RATE_SAMPLE_INTERVAL */
पूर्ण

अटल bool coalesce_put_u32(काष्ठा sk_buff *skb, u16 attr_type, u32 val,
			     u32 supported_params)
अणु
	अगर (!val && !(supported_params & attr_to_mask(attr_type)))
		वापस false;
	वापस nla_put_u32(skb, attr_type, val);
पूर्ण

अटल bool coalesce_put_bool(काष्ठा sk_buff *skb, u16 attr_type, u32 val,
			      u32 supported_params)
अणु
	अगर (!val && !(supported_params & attr_to_mask(attr_type)))
		वापस false;
	वापस nla_put_u8(skb, attr_type, !!val);
पूर्ण

अटल पूर्णांक coalesce_fill_reply(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा coalesce_reply_data *data = COALESCE_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_coalesce *coal = &data->coalesce;
	u32 supported = data->supported_params;

	अगर (coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS,
			     coal->rx_coalesce_usecs, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES,
			     coal->rx_max_coalesced_frames, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS_IRQ,
			     coal->rx_coalesce_usecs_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES_IRQ,
			     coal->rx_max_coalesced_frames_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS,
			     coal->tx_coalesce_usecs, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES,
			     coal->tx_max_coalesced_frames, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS_IRQ,
			     coal->tx_coalesce_usecs_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES_IRQ,
			     coal->tx_max_coalesced_frames_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_STATS_BLOCK_USECS,
			     coal->stats_block_coalesce_usecs, supported) ||
	    coalesce_put_bool(skb, ETHTOOL_A_COALESCE_USE_ADAPTIVE_RX,
			      coal->use_adaptive_rx_coalesce, supported) ||
	    coalesce_put_bool(skb, ETHTOOL_A_COALESCE_USE_ADAPTIVE_TX,
			      coal->use_adaptive_tx_coalesce, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_PKT_RATE_LOW,
			     coal->pkt_rate_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS_LOW,
			     coal->rx_coalesce_usecs_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES_LOW,
			     coal->rx_max_coalesced_frames_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS_LOW,
			     coal->tx_coalesce_usecs_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES_LOW,
			     coal->tx_max_coalesced_frames_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_PKT_RATE_HIGH,
			     coal->pkt_rate_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS_HIGH,
			     coal->rx_coalesce_usecs_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES_HIGH,
			     coal->rx_max_coalesced_frames_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS_HIGH,
			     coal->tx_coalesce_usecs_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES_HIGH,
			     coal->tx_max_coalesced_frames_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RATE_SAMPLE_INTERVAL,
			     coal->rate_sample_पूर्णांकerval, supported))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_coalesce_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_COALESCE_GET,
	.reply_cmd		= ETHTOOL_MSG_COALESCE_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_COALESCE_HEADER,
	.req_info_size		= माप(काष्ठा coalesce_req_info),
	.reply_data_size	= माप(काष्ठा coalesce_reply_data),

	.prepare_data		= coalesce_prepare_data,
	.reply_size		= coalesce_reply_size,
	.fill_reply		= coalesce_fill_reply,
पूर्ण;

/* COALESCE_SET */

स्थिर काष्ठा nla_policy ethnl_coalesce_set_policy[] = अणु
	[ETHTOOL_A_COALESCE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_COALESCE_RX_USECS]		= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RX_USECS_IRQ]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_IRQ]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_USECS]		= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_USECS_IRQ]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_IRQ]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_STATS_BLOCK_USECS]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_USE_ADAPTIVE_RX]	= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_COALESCE_USE_ADAPTIVE_TX]	= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_COALESCE_PKT_RATE_LOW]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RX_USECS_LOW]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_LOW]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_USECS_LOW]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_LOW]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_PKT_RATE_HIGH]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RX_USECS_HIGH]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_HIGH]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_USECS_HIGH]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_HIGH]	= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_COALESCE_RATE_SAMPLE_INTERVAL] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_coalesce(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethtool_coalesce coalesce = अणुपूर्ण;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	स्थिर काष्ठा ethtool_ops *ops;
	काष्ठा net_device *dev;
	u32 supported_params;
	bool mod = false;
	पूर्णांक ret;
	u16 a;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_COALESCE_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	अगर (!ops->get_coalesce || !ops->set_coalesce)
		जाओ out_dev;

	/* make sure that only supported parameters are present */
	supported_params = ops->supported_coalesce_params;
	क्रम (a = ETHTOOL_A_COALESCE_RX_USECS; a < __ETHTOOL_A_COALESCE_CNT; a++)
		अगर (tb[a] && !(supported_params & attr_to_mask(a))) अणु
			ret = -EINVAL;
			NL_SET_ERR_MSG_ATTR(info->extack, tb[a],
					    "cannot modify an unsupported parameter");
			जाओ out_dev;
		पूर्ण

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;
	ret = ops->get_coalesce(dev, &coalesce);
	अगर (ret < 0)
		जाओ out_ops;

	ethnl_update_u32(&coalesce.rx_coalesce_usecs,
			 tb[ETHTOOL_A_COALESCE_RX_USECS], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES], &mod);
	ethnl_update_u32(&coalesce.rx_coalesce_usecs_irq,
			 tb[ETHTOOL_A_COALESCE_RX_USECS_IRQ], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames_irq,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_IRQ], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs,
			 tb[ETHTOOL_A_COALESCE_TX_USECS], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs_irq,
			 tb[ETHTOOL_A_COALESCE_TX_USECS_IRQ], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames_irq,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_IRQ], &mod);
	ethnl_update_u32(&coalesce.stats_block_coalesce_usecs,
			 tb[ETHTOOL_A_COALESCE_STATS_BLOCK_USECS], &mod);
	ethnl_update_bool32(&coalesce.use_adaptive_rx_coalesce,
			    tb[ETHTOOL_A_COALESCE_USE_ADAPTIVE_RX], &mod);
	ethnl_update_bool32(&coalesce.use_adaptive_tx_coalesce,
			    tb[ETHTOOL_A_COALESCE_USE_ADAPTIVE_TX], &mod);
	ethnl_update_u32(&coalesce.pkt_rate_low,
			 tb[ETHTOOL_A_COALESCE_PKT_RATE_LOW], &mod);
	ethnl_update_u32(&coalesce.rx_coalesce_usecs_low,
			 tb[ETHTOOL_A_COALESCE_RX_USECS_LOW], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames_low,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_LOW], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs_low,
			 tb[ETHTOOL_A_COALESCE_TX_USECS_LOW], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames_low,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_LOW], &mod);
	ethnl_update_u32(&coalesce.pkt_rate_high,
			 tb[ETHTOOL_A_COALESCE_PKT_RATE_HIGH], &mod);
	ethnl_update_u32(&coalesce.rx_coalesce_usecs_high,
			 tb[ETHTOOL_A_COALESCE_RX_USECS_HIGH], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames_high,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_HIGH], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs_high,
			 tb[ETHTOOL_A_COALESCE_TX_USECS_HIGH], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames_high,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_HIGH], &mod);
	ethnl_update_u32(&coalesce.rate_sample_पूर्णांकerval,
			 tb[ETHTOOL_A_COALESCE_RATE_SAMPLE_INTERVAL], &mod);
	ret = 0;
	अगर (!mod)
		जाओ out_ops;

	ret = dev->ethtool_ops->set_coalesce(dev, &coalesce);
	अगर (ret < 0)
		जाओ out_ops;
	ethtool_notअगरy(dev, ETHTOOL_MSG_COALESCE_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
