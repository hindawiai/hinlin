<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

#घोषणा EEE_MODES_COUNT \
	(माप_field(काष्ठा ethtool_eee, supported) * BITS_PER_BYTE)

काष्ठा eee_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा eee_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_eee		eee;
पूर्ण;

#घोषणा EEE_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा eee_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_eee_get_policy[] = अणु
	[ETHTOOL_A_EEE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक eee_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			    काष्ठा ethnl_reply_data *reply_base,
			    काष्ठा genl_info *info)
अणु
	काष्ठा eee_reply_data *data = EEE_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_eee)
		वापस -EOPNOTSUPP;
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	ret = dev->ethtool_ops->get_eee(dev, &data->eee);
	ethnl_ops_complete(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक eee_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			  स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा eee_reply_data *data = EEE_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_eee *eee = &data->eee;
	पूर्णांक len = 0;
	पूर्णांक ret;

	BUILD_BUG_ON(माप(eee->advertised) * BITS_PER_BYTE !=
		     EEE_MODES_COUNT);
	BUILD_BUG_ON(माप(eee->lp_advertised) * BITS_PER_BYTE !=
		     EEE_MODES_COUNT);

	/* MODES_OURS */
	ret = ethnl_bitset32_size(&eee->advertised, &eee->supported,
				  EEE_MODES_COUNT, link_mode_names, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;
	/* MODES_PEERS */
	ret = ethnl_bitset32_size(&eee->lp_advertised, शून्य,
				  EEE_MODES_COUNT, link_mode_names, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;

	len += nla_total_size(माप(u8)) +	/* _EEE_ACTIVE */
	       nla_total_size(माप(u8)) +	/* _EEE_ENABLED */
	       nla_total_size(माप(u8)) +	/* _EEE_TX_LPI_ENABLED */
	       nla_total_size(माप(u32));	/* _EEE_TX_LPI_TIMER */

	वापस len;
पूर्ण

अटल पूर्णांक eee_fill_reply(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा ethnl_req_info *req_base,
			  स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा eee_reply_data *data = EEE_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_eee *eee = &data->eee;
	पूर्णांक ret;

	ret = ethnl_put_bitset32(skb, ETHTOOL_A_EEE_MODES_OURS,
				 &eee->advertised, &eee->supported,
				 EEE_MODES_COUNT, link_mode_names, compact);
	अगर (ret < 0)
		वापस ret;
	ret = ethnl_put_bitset32(skb, ETHTOOL_A_EEE_MODES_PEER,
				 &eee->lp_advertised, शून्य, EEE_MODES_COUNT,
				 link_mode_names, compact);
	अगर (ret < 0)
		वापस ret;

	अगर (nla_put_u8(skb, ETHTOOL_A_EEE_ACTIVE, !!eee->eee_active) ||
	    nla_put_u8(skb, ETHTOOL_A_EEE_ENABLED, !!eee->eee_enabled) ||
	    nla_put_u8(skb, ETHTOOL_A_EEE_TX_LPI_ENABLED,
		       !!eee->tx_lpi_enabled) ||
	    nla_put_u32(skb, ETHTOOL_A_EEE_TX_LPI_TIMER, eee->tx_lpi_समयr))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_eee_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_EEE_GET,
	.reply_cmd		= ETHTOOL_MSG_EEE_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_EEE_HEADER,
	.req_info_size		= माप(काष्ठा eee_req_info),
	.reply_data_size	= माप(काष्ठा eee_reply_data),

	.prepare_data		= eee_prepare_data,
	.reply_size		= eee_reply_size,
	.fill_reply		= eee_fill_reply,
पूर्ण;

/* EEE_SET */

स्थिर काष्ठा nla_policy ethnl_eee_set_policy[] = अणु
	[ETHTOOL_A_EEE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_EEE_MODES_OURS]	= अणु .type = NLA_NESTED पूर्ण,
	[ETHTOOL_A_EEE_ENABLED]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_EEE_TX_LPI_ENABLED]	= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_EEE_TX_LPI_TIMER]	= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_eee(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	स्थिर काष्ठा ethtool_ops *ops;
	काष्ठा ethtool_eee eee = अणुपूर्ण;
	काष्ठा net_device *dev;
	bool mod = false;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_EEE_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	अगर (!ops->get_eee || !ops->set_eee)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;
	ret = ops->get_eee(dev, &eee);
	अगर (ret < 0)
		जाओ out_ops;

	ret = ethnl_update_bitset32(&eee.advertised, EEE_MODES_COUNT,
				    tb[ETHTOOL_A_EEE_MODES_OURS],
				    link_mode_names, info->extack, &mod);
	अगर (ret < 0)
		जाओ out_ops;
	ethnl_update_bool32(&eee.eee_enabled, tb[ETHTOOL_A_EEE_ENABLED], &mod);
	ethnl_update_bool32(&eee.tx_lpi_enabled,
			    tb[ETHTOOL_A_EEE_TX_LPI_ENABLED], &mod);
	ethnl_update_u32(&eee.tx_lpi_समयr, tb[ETHTOOL_A_EEE_TX_LPI_TIMER],
			 &mod);
	ret = 0;
	अगर (!mod)
		जाओ out_ops;

	ret = dev->ethtool_ops->set_eee(dev, &eee);
	अगर (ret < 0)
		जाओ out_ops;
	ethtool_notअगरy(dev, ETHTOOL_MSG_EEE_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
