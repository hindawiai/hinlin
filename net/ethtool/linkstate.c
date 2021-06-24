<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश <linux/phy.h>

काष्ठा linkstate_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा linkstate_reply_data अणु
	काष्ठा ethnl_reply_data			base;
	पूर्णांक					link;
	पूर्णांक					sqi;
	पूर्णांक					sqi_max;
	bool					link_ext_state_provided;
	काष्ठा ethtool_link_ext_state_info	ethtool_link_ext_state_info;
पूर्ण;

#घोषणा LINKSTATE_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा linkstate_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_linkstate_get_policy[] = अणु
	[ETHTOOL_A_LINKSTATE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक linkstate_get_sqi(काष्ठा net_device *dev)
अणु
	काष्ठा phy_device *phydev = dev->phydev;
	पूर्णांक ret;

	अगर (!phydev)
		वापस -EOPNOTSUPP;

	mutex_lock(&phydev->lock);
	अगर (!phydev->drv || !phydev->drv->get_sqi)
		ret = -EOPNOTSUPP;
	अन्यथा
		ret = phydev->drv->get_sqi(phydev);
	mutex_unlock(&phydev->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक linkstate_get_sqi_max(काष्ठा net_device *dev)
अणु
	काष्ठा phy_device *phydev = dev->phydev;
	पूर्णांक ret;

	अगर (!phydev)
		वापस -EOPNOTSUPP;

	mutex_lock(&phydev->lock);
	अगर (!phydev->drv || !phydev->drv->get_sqi_max)
		ret = -EOPNOTSUPP;
	अन्यथा
		ret = phydev->drv->get_sqi_max(phydev);
	mutex_unlock(&phydev->lock);

	वापस ret;
पूर्ण;

अटल पूर्णांक linkstate_get_link_ext_state(काष्ठा net_device *dev,
					काष्ठा linkstate_reply_data *data)
अणु
	पूर्णांक err;

	अगर (!dev->ethtool_ops->get_link_ext_state)
		वापस -EOPNOTSUPP;

	err = dev->ethtool_ops->get_link_ext_state(dev, &data->ethtool_link_ext_state_info);
	अगर (err)
		वापस err;

	data->link_ext_state_provided = true;

	वापस 0;
पूर्ण

अटल पूर्णांक linkstate_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
				  काष्ठा ethnl_reply_data *reply_base,
				  काष्ठा genl_info *info)
अणु
	काष्ठा linkstate_reply_data *data = LINKSTATE_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	data->link = __ethtool_get_link(dev);

	ret = linkstate_get_sqi(dev);
	अगर (ret < 0 && ret != -EOPNOTSUPP)
		जाओ out;
	data->sqi = ret;

	ret = linkstate_get_sqi_max(dev);
	अगर (ret < 0 && ret != -EOPNOTSUPP)
		जाओ out;
	data->sqi_max = ret;

	अगर (dev->flags & IFF_UP) अणु
		ret = linkstate_get_link_ext_state(dev, data);
		अगर (ret < 0 && ret != -EOPNOTSUPP && ret != -ENODATA)
			जाओ out;
	पूर्ण

	ret = 0;
out:
	ethnl_ops_complete(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक linkstate_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
				स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	काष्ठा linkstate_reply_data *data = LINKSTATE_REPDATA(reply_base);
	पूर्णांक len;

	len = nla_total_size(माप(u8)) /* LINKSTATE_LINK */
		+ 0;

	अगर (data->sqi != -EOPNOTSUPP)
		len += nla_total_size(माप(u32));

	अगर (data->sqi_max != -EOPNOTSUPP)
		len += nla_total_size(माप(u32));

	अगर (data->link_ext_state_provided)
		len += nla_total_size(माप(u8)); /* LINKSTATE_EXT_STATE */

	अगर (data->ethtool_link_ext_state_info.__link_ext_substate)
		len += nla_total_size(माप(u8)); /* LINKSTATE_EXT_SUBSTATE */

	वापस len;
पूर्ण

अटल पूर्णांक linkstate_fill_reply(काष्ठा sk_buff *skb,
				स्थिर काष्ठा ethnl_req_info *req_base,
				स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	काष्ठा linkstate_reply_data *data = LINKSTATE_REPDATA(reply_base);

	अगर (data->link >= 0 &&
	    nla_put_u8(skb, ETHTOOL_A_LINKSTATE_LINK, !!data->link))
		वापस -EMSGSIZE;

	अगर (data->sqi != -EOPNOTSUPP &&
	    nla_put_u32(skb, ETHTOOL_A_LINKSTATE_SQI, data->sqi))
		वापस -EMSGSIZE;

	अगर (data->sqi_max != -EOPNOTSUPP &&
	    nla_put_u32(skb, ETHTOOL_A_LINKSTATE_SQI_MAX, data->sqi_max))
		वापस -EMSGSIZE;

	अगर (data->link_ext_state_provided) अणु
		अगर (nla_put_u8(skb, ETHTOOL_A_LINKSTATE_EXT_STATE,
			       data->ethtool_link_ext_state_info.link_ext_state))
			वापस -EMSGSIZE;

		अगर (data->ethtool_link_ext_state_info.__link_ext_substate &&
		    nla_put_u8(skb, ETHTOOL_A_LINKSTATE_EXT_SUBSTATE,
			       data->ethtool_link_ext_state_info.__link_ext_substate))
			वापस -EMSGSIZE;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_linkstate_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_LINKSTATE_GET,
	.reply_cmd		= ETHTOOL_MSG_LINKSTATE_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_LINKSTATE_HEADER,
	.req_info_size		= माप(काष्ठा linkstate_req_info),
	.reply_data_size	= माप(काष्ठा linkstate_reply_data),

	.prepare_data		= linkstate_prepare_data,
	.reply_size		= linkstate_reply_size,
	.fill_reply		= linkstate_fill_reply,
पूर्ण;
