<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

/* LINKMODES_GET */

काष्ठा linkmodes_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा linkmodes_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_link_ksettings	ksettings;
	काष्ठा ethtool_link_settings	*lsettings;
	bool				peer_empty;
पूर्ण;

#घोषणा LINKMODES_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा linkmodes_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_linkmodes_get_policy[] = अणु
	[ETHTOOL_A_LINKMODES_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक linkmodes_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
				  काष्ठा ethnl_reply_data *reply_base,
				  काष्ठा genl_info *info)
अणु
	काष्ठा linkmodes_reply_data *data = LINKMODES_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	data->lsettings = &data->ksettings.base;

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;

	ret = __ethtool_get_link_ksettings(dev, &data->ksettings);
	अगर (ret < 0 && info) अणु
		GENL_SET_ERR_MSG(info, "failed to retrieve link settings");
		जाओ out;
	पूर्ण

	अगर (!dev->ethtool_ops->cap_link_lanes_supported)
		data->ksettings.lanes = 0;

	data->peer_empty =
		biपंचांगap_empty(data->ksettings.link_modes.lp_advertising,
			     __ETHTOOL_LINK_MODE_MASK_NBITS);

out:
	ethnl_ops_complete(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक linkmodes_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
				स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा linkmodes_reply_data *data = LINKMODES_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_link_ksettings *ksettings = &data->ksettings;
	स्थिर काष्ठा ethtool_link_settings *lsettings = &ksettings->base;
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	पूर्णांक len, ret;

	len = nla_total_size(माप(u8)) /* LINKMODES_AUTONEG */
		+ nla_total_size(माप(u32)) /* LINKMODES_SPEED */
		+ nla_total_size(माप(u32)) /* LINKMODES_LANES */
		+ nla_total_size(माप(u8)) /* LINKMODES_DUPLEX */
		+ 0;
	ret = ethnl_bitset_size(ksettings->link_modes.advertising,
				ksettings->link_modes.supported,
				__ETHTOOL_LINK_MODE_MASK_NBITS,
				link_mode_names, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;
	अगर (!data->peer_empty) अणु
		ret = ethnl_bitset_size(ksettings->link_modes.lp_advertising,
					शून्य, __ETHTOOL_LINK_MODE_MASK_NBITS,
					link_mode_names, compact);
		अगर (ret < 0)
			वापस ret;
		len += ret;
	पूर्ण

	अगर (lsettings->master_slave_cfg != MASTER_SLAVE_CFG_UNSUPPORTED)
		len += nla_total_size(माप(u8));

	अगर (lsettings->master_slave_state != MASTER_SLAVE_STATE_UNSUPPORTED)
		len += nla_total_size(माप(u8));

	वापस len;
पूर्ण

अटल पूर्णांक linkmodes_fill_reply(काष्ठा sk_buff *skb,
				स्थिर काष्ठा ethnl_req_info *req_base,
				स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा linkmodes_reply_data *data = LINKMODES_REPDATA(reply_base);
	स्थिर काष्ठा ethtool_link_ksettings *ksettings = &data->ksettings;
	स्थिर काष्ठा ethtool_link_settings *lsettings = &ksettings->base;
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	पूर्णांक ret;

	अगर (nla_put_u8(skb, ETHTOOL_A_LINKMODES_AUTONEG, lsettings->स्वतःneg))
		वापस -EMSGSIZE;

	ret = ethnl_put_bitset(skb, ETHTOOL_A_LINKMODES_OURS,
			       ksettings->link_modes.advertising,
			       ksettings->link_modes.supported,
			       __ETHTOOL_LINK_MODE_MASK_NBITS, link_mode_names,
			       compact);
	अगर (ret < 0)
		वापस -EMSGSIZE;
	अगर (!data->peer_empty) अणु
		ret = ethnl_put_bitset(skb, ETHTOOL_A_LINKMODES_PEER,
				       ksettings->link_modes.lp_advertising,
				       शून्य, __ETHTOOL_LINK_MODE_MASK_NBITS,
				       link_mode_names, compact);
		अगर (ret < 0)
			वापस -EMSGSIZE;
	पूर्ण

	अगर (nla_put_u32(skb, ETHTOOL_A_LINKMODES_SPEED, lsettings->speed) ||
	    nla_put_u8(skb, ETHTOOL_A_LINKMODES_DUPLEX, lsettings->duplex))
		वापस -EMSGSIZE;

	अगर (ksettings->lanes &&
	    nla_put_u32(skb, ETHTOOL_A_LINKMODES_LANES, ksettings->lanes))
		वापस -EMSGSIZE;

	अगर (lsettings->master_slave_cfg != MASTER_SLAVE_CFG_UNSUPPORTED &&
	    nla_put_u8(skb, ETHTOOL_A_LINKMODES_MASTER_SLAVE_CFG,
		       lsettings->master_slave_cfg))
		वापस -EMSGSIZE;

	अगर (lsettings->master_slave_state != MASTER_SLAVE_STATE_UNSUPPORTED &&
	    nla_put_u8(skb, ETHTOOL_A_LINKMODES_MASTER_SLAVE_STATE,
		       lsettings->master_slave_state))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_linkmodes_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_LINKMODES_GET,
	.reply_cmd		= ETHTOOL_MSG_LINKMODES_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_LINKMODES_HEADER,
	.req_info_size		= माप(काष्ठा linkmodes_req_info),
	.reply_data_size	= माप(काष्ठा linkmodes_reply_data),

	.prepare_data		= linkmodes_prepare_data,
	.reply_size		= linkmodes_reply_size,
	.fill_reply		= linkmodes_fill_reply,
पूर्ण;

/* LINKMODES_SET */

स्थिर काष्ठा nla_policy ethnl_linkmodes_set_policy[] = अणु
	[ETHTOOL_A_LINKMODES_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_LINKMODES_AUTONEG]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_LINKMODES_OURS]		= अणु .type = NLA_NESTED पूर्ण,
	[ETHTOOL_A_LINKMODES_SPEED]		= अणु .type = NLA_U32 पूर्ण,
	[ETHTOOL_A_LINKMODES_DUPLEX]		= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_LINKMODES_MASTER_SLAVE_CFG]	= अणु .type = NLA_U8 पूर्ण,
	[ETHTOOL_A_LINKMODES_LANES]		= NLA_POLICY_RANGE(NLA_U32, 1, 8),
पूर्ण;

/* Set advertised link modes to all supported modes matching requested speed,
 * lanes and duplex values. Called when स्वतःnegotiation is on, speed, lanes or
 * duplex is requested but no link mode change. This is करोne in userspace with
 * ioctl() पूर्णांकerface, move it पूर्णांकo kernel क्रम netlink.
 * Returns true अगर advertised modes biपंचांगap was modअगरied.
 */
अटल bool ethnl_स्वतः_linkmodes(काष्ठा ethtool_link_ksettings *ksettings,
				 bool req_speed, bool req_lanes, bool req_duplex)
अणु
	अचिन्हित दीर्घ *advertising = ksettings->link_modes.advertising;
	अचिन्हित दीर्घ *supported = ksettings->link_modes.supported;
	DECLARE_BITMAP(old_adv, __ETHTOOL_LINK_MODE_MASK_NBITS);
	अचिन्हित पूर्णांक i;

	biपंचांगap_copy(old_adv, advertising, __ETHTOOL_LINK_MODE_MASK_NBITS);

	क्रम (i = 0; i < __ETHTOOL_LINK_MODE_MASK_NBITS; i++) अणु
		स्थिर काष्ठा link_mode_info *info = &link_mode_params[i];

		अगर (info->speed == SPEED_UNKNOWN)
			जारी;
		अगर (test_bit(i, supported) &&
		    (!req_speed || info->speed == ksettings->base.speed) &&
		    (!req_lanes || info->lanes == ksettings->lanes) &&
		    (!req_duplex || info->duplex == ksettings->base.duplex))
			set_bit(i, advertising);
		अन्यथा
			clear_bit(i, advertising);
	पूर्ण

	वापस !biपंचांगap_equal(old_adv, advertising,
			     __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल bool ethnl_validate_master_slave_cfg(u8 cfg)
अणु
	चयन (cfg) अणु
	हाल MASTER_SLAVE_CFG_MASTER_PREFERRED:
	हाल MASTER_SLAVE_CFG_SLAVE_PREFERRED:
	हाल MASTER_SLAVE_CFG_MASTER_FORCE:
	हाल MASTER_SLAVE_CFG_SLAVE_FORCE:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ethnl_check_linkmodes(काष्ठा genl_info *info, काष्ठा nlattr **tb)
अणु
	स्थिर काष्ठा nlattr *master_slave_cfg, *lanes_cfg;

	master_slave_cfg = tb[ETHTOOL_A_LINKMODES_MASTER_SLAVE_CFG];
	अगर (master_slave_cfg &&
	    !ethnl_validate_master_slave_cfg(nla_get_u8(master_slave_cfg))) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, master_slave_cfg,
				    "master/slave value is invalid");
		वापस -EOPNOTSUPP;
	पूर्ण

	lanes_cfg = tb[ETHTOOL_A_LINKMODES_LANES];
	अगर (lanes_cfg && !is_घातer_of_2(nla_get_u32(lanes_cfg))) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, lanes_cfg,
				    "lanes value is invalid");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ethnl_update_linkmodes(काष्ठा genl_info *info, काष्ठा nlattr **tb,
				  काष्ठा ethtool_link_ksettings *ksettings,
				  bool *mod, स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा ethtool_link_settings *lsettings = &ksettings->base;
	bool req_speed, req_lanes, req_duplex;
	स्थिर काष्ठा nlattr *master_slave_cfg, *lanes_cfg;
	पूर्णांक ret;

	master_slave_cfg = tb[ETHTOOL_A_LINKMODES_MASTER_SLAVE_CFG];
	अगर (master_slave_cfg) अणु
		अगर (lsettings->master_slave_cfg == MASTER_SLAVE_CFG_UNSUPPORTED) अणु
			NL_SET_ERR_MSG_ATTR(info->extack, master_slave_cfg,
					    "master/slave configuration not supported by device");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	*mod = false;
	req_speed = tb[ETHTOOL_A_LINKMODES_SPEED];
	req_lanes = tb[ETHTOOL_A_LINKMODES_LANES];
	req_duplex = tb[ETHTOOL_A_LINKMODES_DUPLEX];

	ethnl_update_u8(&lsettings->स्वतःneg, tb[ETHTOOL_A_LINKMODES_AUTONEG],
			mod);

	lanes_cfg = tb[ETHTOOL_A_LINKMODES_LANES];
	अगर (lanes_cfg) अणु
		/* If स्वतःneg is off and lanes parameter is not supported by the
		 * driver, वापस an error.
		 */
		अगर (!lsettings->स्वतःneg &&
		    !dev->ethtool_ops->cap_link_lanes_supported) अणु
			NL_SET_ERR_MSG_ATTR(info->extack, lanes_cfg,
					    "lanes configuration not supported by device");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अगर (!lsettings->स्वतःneg) अणु
		/* If स्वतःneg is off and lanes parameter is not passed from user,
		 * set the lanes parameter to 0.
		 */
		ksettings->lanes = 0;
	पूर्ण

	ret = ethnl_update_bitset(ksettings->link_modes.advertising,
				  __ETHTOOL_LINK_MODE_MASK_NBITS,
				  tb[ETHTOOL_A_LINKMODES_OURS], link_mode_names,
				  info->extack, mod);
	अगर (ret < 0)
		वापस ret;
	ethnl_update_u32(&lsettings->speed, tb[ETHTOOL_A_LINKMODES_SPEED],
			 mod);
	ethnl_update_u32(&ksettings->lanes, lanes_cfg, mod);
	ethnl_update_u8(&lsettings->duplex, tb[ETHTOOL_A_LINKMODES_DUPLEX],
			mod);
	ethnl_update_u8(&lsettings->master_slave_cfg, master_slave_cfg, mod);

	अगर (!tb[ETHTOOL_A_LINKMODES_OURS] && lsettings->स्वतःneg &&
	    (req_speed || req_lanes || req_duplex) &&
	    ethnl_स्वतः_linkmodes(ksettings, req_speed, req_lanes, req_duplex))
		*mod = true;

	वापस 0;
पूर्ण

पूर्णांक ethnl_set_linkmodes(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethtool_link_ksettings ksettings = अणुपूर्ण;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा net_device *dev;
	bool mod = false;
	पूर्णांक ret;

	ret = ethnl_check_linkmodes(info, tb);
	अगर (ret < 0)
		वापस ret;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_LINKMODES_HEADER],
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

	ret = ethnl_update_linkmodes(info, tb, &ksettings, &mod, dev);
	अगर (ret < 0)
		जाओ out_ops;

	अगर (mod) अणु
		ret = dev->ethtool_ops->set_link_ksettings(dev, &ksettings);
		अगर (ret < 0)
			GENL_SET_ERR_MSG(info, "link settings update failed");
		अन्यथा
			ethtool_notअगरy(dev, ETHTOOL_MSG_LINKMODES_NTF, शून्य);
	पूर्ण

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
