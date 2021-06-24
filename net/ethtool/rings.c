<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"

काष्ठा rings_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा rings_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_ringparam	ringparam;
पूर्ण;

#घोषणा RINGS_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा rings_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_rings_get_policy[] = अणु
	[ETHTOOL_A_RINGS_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक rings_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			      काष्ठा ethnl_reply_data *reply_base,
			      काष्ठा genl_info *info)
अणु
	काष्ठा rings_reply_data *data = RINGS_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_ringparam)
		वापस -EOPNOTSUPP;
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	dev->ethtool_ops->get_ringparam(dev, &data->ringparam);
	ethnl_ops_complete(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक rings_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	वापस nla_total_size(माप(u32)) +	/* _RINGS_RX_MAX */
	       nla_total_size(माप(u32)) +	/* _RINGS_RX_MINI_MAX */
	       nla_total_size(माप(u32)) +	/* _RINGS_RX_JUMBO_MAX */
	       nla_total_size(माप(u32)) +	/* _RINGS_TX_MAX */
	       nla_total_size(माप(u32)) +	/* _RINGS_RX */
	       nla_total_size(माप(u32)) +	/* _RINGS_RX_MINI */
	       nla_total_size(माप(u32)) +	/* _RINGS_RX_JUMBO */
	       nla_total_size(माप(u32));	/* _RINGS_TX */
पूर्ण

अटल पूर्णांक rings_fill_reply(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा rings_reply_data *data = RINGS_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_ringparam *ringparam = &data->ringparam;

	अगर ((ringparam->rx_max_pending &&
	     (nla_put_u32(skb, ETHTOOL_A_RINGS_RX_MAX,
			  ringparam->rx_max_pending) ||
	      nla_put_u32(skb, ETHTOOL_A_RINGS_RX,
			  ringparam->rx_pending))) ||
	    (ringparam->rx_mini_max_pending &&
	     (nla_put_u32(skb, ETHTOOL_A_RINGS_RX_MINI_MAX,
			  ringparam->rx_mini_max_pending) ||
	      nla_put_u32(skb, ETHTOOL_A_RINGS_RX_MINI,
			  ringparam->rx_mini_pending))) ||
	    (ringparam->rx_jumbo_max_pending &&
	     (nla_put_u32(skb, ETHTOOL_A_RINGS_RX_JUMBO_MAX,
			  ringparam->rx_jumbo_max_pending) ||
	      nla_put_u32(skb, ETHTOOL_A_RINGS_RX_JUMBO,
			  ringparam->rx_jumbo_pending))) ||
	    (ringparam->tx_max_pending &&
	     (nla_put_u32(skb, ETHTOOL_A_RINGS_TX_MAX,
			  ringparam->tx_max_pending) ||
	      nla_put_u32(skb, ETHTOOL_A_RINGS_TX,
			  ringparam->tx_pending))))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_rings_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_RINGS_GET,
	.reply_cmd		= ETHTOOL_MSG_RINGS_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_RINGS_HEADER,
	.req_info_size		= माप(काष्ठा rings_req_info),
	.reply_data_size	= माप(काष्ठा rings_reply_data),

	.prepare_data		= rings_prepare_data,
	.reply_size		= rings_reply_size,
	.fill_reply		= rings_fill_reply,
पूर्ण;

/* RINGS_SET */

स्थिर काष्ठा nla_policy ethnl_rings_set_policy[] = अणु
	[ETHTOOL_A_RINGS_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_RINGS_RX]			= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_RINGS_RX_MINI]		= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_RINGS_RX_JUMBO]		= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_RINGS_TX]			= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_rings(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethtool_ringparam ringparam = अणुपूर्ण;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	स्थिर काष्ठा nlattr *err_attr;
	स्थिर काष्ठा ethtool_ops *ops;
	काष्ठा net_device *dev;
	bool mod = false;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_RINGS_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	अगर (!ops->get_ringparam || !ops->set_ringparam)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;
	ops->get_ringparam(dev, &ringparam);

	ethnl_update_u32(&ringparam.rx_pending, tb[ETHTOOL_A_RINGS_RX], &mod);
	ethnl_update_u32(&ringparam.rx_mini_pending,
			 tb[ETHTOOL_A_RINGS_RX_MINI], &mod);
	ethnl_update_u32(&ringparam.rx_jumbo_pending,
			 tb[ETHTOOL_A_RINGS_RX_JUMBO], &mod);
	ethnl_update_u32(&ringparam.tx_pending, tb[ETHTOOL_A_RINGS_TX], &mod);
	ret = 0;
	अगर (!mod)
		जाओ out_ops;

	/* ensure new ring parameters are within limits */
	अगर (ringparam.rx_pending > ringparam.rx_max_pending)
		err_attr = tb[ETHTOOL_A_RINGS_RX];
	अन्यथा अगर (ringparam.rx_mini_pending > ringparam.rx_mini_max_pending)
		err_attr = tb[ETHTOOL_A_RINGS_RX_MINI];
	अन्यथा अगर (ringparam.rx_jumbo_pending > ringparam.rx_jumbo_max_pending)
		err_attr = tb[ETHTOOL_A_RINGS_RX_JUMBO];
	अन्यथा अगर (ringparam.tx_pending > ringparam.tx_max_pending)
		err_attr = tb[ETHTOOL_A_RINGS_TX];
	अन्यथा
		err_attr = शून्य;
	अगर (err_attr) अणु
		ret = -EINVAL;
		NL_SET_ERR_MSG_ATTR(info->extack, err_attr,
				    "requested ring size exceeds maximum");
		जाओ out_ops;
	पूर्ण

	ret = dev->ethtool_ops->set_ringparam(dev, &ringparam);
	अगर (ret < 0)
		जाओ out_ops;
	ethtool_notअगरy(dev, ETHTOOL_MSG_RINGS_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
