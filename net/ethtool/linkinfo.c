<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"

काष्ठा linkinfo_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा linkinfo_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_link_ksettings	ksettings;
	काष्ठा ethtool_link_settings	*lsettings;
पूर्ण;

#घोषणा LINKINFO_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा linkinfo_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_linkinfo_get_policy[] = अणु
	[ETHTOOL_A_LINKINFO_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक linkinfo_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
				 काष्ठा ethnl_reply_data *reply_base,
				 काष्ठा genl_info *info)
अणु
	काष्ठा linkinfo_reply_data *data = LINKINFO_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	data->lsettings = &data->ksettings.base;

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	ret = __ethtool_get_link_ksettings(dev, &data->ksettings);
	अगर (ret < 0 && info)
		GENL_SET_ERR_MSG(info, "failed to retrieve link settings");
	ethnl_ops_complete(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक linkinfo_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	वापस nla_total_size(माप(u8)) /* LINKINFO_PORT */
		+ nla_total_size(माप(u8)) /* LINKINFO_PHYADDR */
		+ nla_total_size(माप(u8)) /* LINKINFO_TP_MDIX */
		+ nla_total_size(माप(u8)) /* LINKINFO_TP_MDIX_CTRL */
		+ nla_total_size(माप(u8)) /* LINKINFO_TRANSCEIVER */
		+ 0;
पूर्ण

अटल पूर्णांक linkinfo_fill_reply(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा ethnl_req_info *req_base,
			       स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा linkinfo_reply_data *data = LINKINFO_REPDATA(reply_base);

	अगर (nla_put_u8(skb, ETHTOOL_A_LINKINFO_PORT, data->lsettings->port) ||
	    nla_put_u8(skb, ETHTOOL_A_LINKINFO_PHYADDR,
		       data->lsettings->phy_address) ||
	    nla_put_u8(skb, ETHTOOL_A_LINKINFO_TP_MDIX,
		       data->lsettings->eth_tp_mdix) ||
	    nla_put_u8(skb, ETHTOOL_A_LINKINFO_TP_MDIX_CTRL,
		       data->lsettings->eth_tp_mdix_ctrl) ||
	    nla_put_u8(skb, ETHTOOL_A_LINKINFO_TRANSCEIVER,
		       data->lsettings->transceiver))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_linkinfo_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_LINKINFO_GET,
	.reply_cmd		= ETHTOOL_MSG_LINKINFO_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_LINKINFO_HEADER,
	.req_info_size		= माप(काष्ठा linkinfo_req_info),
	.reply_data_size	= माप(काष्ठा linkinfo_reply_data),

	.prepare_data		= linkinfo_prepare_data,
	.reply_size		= linkinfo_reply_size,
	.fill_reply		= linkinfo_fill_reply,
पूर्ण;

/* LINKINFO_SET */

स्थिर काष्ठा nla_policy ethnl_linkinfo_set_policy[] = अणु
	[ETHTOOL_A_LINKINFO_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_LINKINFO_PORT]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_LINKINFO_PHYADDR]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_LINKINFO_TP_MDIX_CTRL]	= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_linkinfo(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethtool_link_ksettings ksettings = अणुपूर्ण;
	काष्ठा ethtool_link_settings *lsettings;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा net_device *dev;
	bool mod = false;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_LINKINFO_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ret = -EOPNOTSUPP;
	अगर (!dev->ethtool_ops->get_link_ksettings ||
	    !dev->ethtool_ops->set_link_ksettings)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;

	ret = __ethtool_get_link_ksettings(dev, &ksettings);
	अगर (ret < 0) अणु
		GENL_SET_ERR_MSG(info, "failed to retrieve link settings");
		जाओ out_ops;
	पूर्ण
	lsettings = &ksettings.base;

	ethnl_update_u8(&lsettings->port, tb[ETHTOOL_A_LINKINFO_PORT], &mod);
	ethnl_update_u8(&lsettings->phy_address, tb[ETHTOOL_A_LINKINFO_PHYADDR],
			&mod);
	ethnl_update_u8(&lsettings->eth_tp_mdix_ctrl,
			tb[ETHTOOL_A_LINKINFO_TP_MDIX_CTRL], &mod);
	ret = 0;
	अगर (!mod)
		जाओ out_ops;

	ret = dev->ethtool_ops->set_link_ksettings(dev, &ksettings);
	अगर (ret < 0)
		GENL_SET_ERR_MSG(info, "link settings update failed");
	अन्यथा
		ethtool_notअगरy(dev, ETHTOOL_MSG_LINKINFO_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
