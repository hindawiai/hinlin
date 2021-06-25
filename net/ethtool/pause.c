<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"

काष्ठा छोड़ो_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा छोड़ो_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_छोड़ोparam	छोड़ोparam;
	काष्ठा ethtool_छोड़ो_stats	छोड़ोstat;
पूर्ण;

#घोषणा PAUSE_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा छोड़ो_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_छोड़ो_get_policy[] = अणु
	[ETHTOOL_A_PAUSE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy_stats),
पूर्ण;

अटल पूर्णांक छोड़ो_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			      काष्ठा ethnl_reply_data *reply_base,
			      काष्ठा genl_info *info)
अणु
	काष्ठा छोड़ो_reply_data *data = PAUSE_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_छोड़ोparam)
		वापस -EOPNOTSUPP;

	ethtool_stats_init((u64 *)&data->छोड़ोstat,
			   माप(data->छोड़ोstat) / 8);

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	dev->ethtool_ops->get_छोड़ोparam(dev, &data->छोड़ोparam);
	अगर (req_base->flags & ETHTOOL_FLAG_STATS &&
	    dev->ethtool_ops->get_छोड़ो_stats)
		dev->ethtool_ops->get_छोड़ो_stats(dev, &data->छोड़ोstat);
	ethnl_ops_complete(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक छोड़ो_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	पूर्णांक n = nla_total_size(माप(u8)) +	/* _PAUSE_AUTONEG */
		nla_total_size(माप(u8)) +	/* _PAUSE_RX */
		nla_total_size(माप(u8));	/* _PAUSE_TX */

	अगर (req_base->flags & ETHTOOL_FLAG_STATS)
		n += nla_total_size(0) +	/* _PAUSE_STATS */
			nla_total_size_64bit(माप(u64)) *
				(ETHTOOL_A_PAUSE_STAT_MAX - 2);
	वापस n;
पूर्ण

अटल पूर्णांक ethtool_put_stat(काष्ठा sk_buff *skb, u64 val, u16 attrtype,
			    u16 padtype)
अणु
	अगर (val == ETHTOOL_STAT_NOT_SET)
		वापस 0;
	अगर (nla_put_u64_64bit(skb, attrtype, val, padtype))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक छोड़ो_put_stats(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा ethtool_छोड़ो_stats *छोड़ो_stats)
अणु
	स्थिर u16 pad = ETHTOOL_A_PAUSE_STAT_PAD;
	काष्ठा nlattr *nest;

	nest = nla_nest_start(skb, ETHTOOL_A_PAUSE_STATS);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (ethtool_put_stat(skb, छोड़ो_stats->tx_छोड़ो_frames,
			     ETHTOOL_A_PAUSE_STAT_TX_FRAMES, pad) ||
	    ethtool_put_stat(skb, छोड़ो_stats->rx_छोड़ो_frames,
			     ETHTOOL_A_PAUSE_STAT_RX_FRAMES, pad))
		जाओ err_cancel;

	nla_nest_end(skb, nest);
	वापस 0;

err_cancel:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक छोड़ो_fill_reply(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा छोड़ो_reply_data *data = PAUSE_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_छोड़ोparam *छोड़ोparam = &data->छोड़ोparam;

	अगर (nla_put_u8(skb, ETHTOOL_A_PAUSE_AUTONEG, !!छोड़ोparam->स्वतःneg) ||
	    nla_put_u8(skb, ETHTOOL_A_PAUSE_RX, !!छोड़ोparam->rx_छोड़ो) ||
	    nla_put_u8(skb, ETHTOOL_A_PAUSE_TX, !!छोड़ोparam->tx_छोड़ो))
		वापस -EMSGSIZE;

	अगर (req_base->flags & ETHTOOL_FLAG_STATS &&
	    छोड़ो_put_stats(skb, &data->छोड़ोstat))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_छोड़ो_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_PAUSE_GET,
	.reply_cmd		= ETHTOOL_MSG_PAUSE_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_PAUSE_HEADER,
	.req_info_size		= माप(काष्ठा छोड़ो_req_info),
	.reply_data_size	= माप(काष्ठा छोड़ो_reply_data),

	.prepare_data		= छोड़ो_prepare_data,
	.reply_size		= छोड़ो_reply_size,
	.fill_reply		= छोड़ो_fill_reply,
पूर्ण;

/* PAUSE_SET */

स्थिर काष्ठा nla_policy ethnl_छोड़ो_set_policy[] = अणु
	[ETHTOOL_A_PAUSE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_PAUSE_AUTONEG]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_PAUSE_RX]			= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_PAUSE_TX]			= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_छोड़ो(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethtool_छोड़ोparam params = अणुपूर्ण;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	स्थिर काष्ठा ethtool_ops *ops;
	काष्ठा net_device *dev;
	bool mod = false;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_PAUSE_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	अगर (!ops->get_छोड़ोparam || !ops->set_छोड़ोparam)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;
	ops->get_छोड़ोparam(dev, &params);

	ethnl_update_bool32(&params.स्वतःneg, tb[ETHTOOL_A_PAUSE_AUTONEG], &mod);
	ethnl_update_bool32(&params.rx_छोड़ो, tb[ETHTOOL_A_PAUSE_RX], &mod);
	ethnl_update_bool32(&params.tx_छोड़ो, tb[ETHTOOL_A_PAUSE_TX], &mod);
	ret = 0;
	अगर (!mod)
		जाओ out_ops;

	ret = dev->ethtool_ops->set_छोड़ोparam(dev, &params);
	अगर (ret < 0)
		जाओ out_ops;
	ethtool_notअगरy(dev, ETHTOOL_MSG_PAUSE_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
