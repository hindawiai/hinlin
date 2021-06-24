<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

काष्ठा wol_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा wol_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_wolinfo		wol;
	bool				show_sopass;
पूर्ण;

#घोषणा WOL_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा wol_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_wol_get_policy[] = अणु
	[ETHTOOL_A_WOL_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक wol_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			    काष्ठा ethnl_reply_data *reply_base,
			    काष्ठा genl_info *info)
अणु
	काष्ठा wol_reply_data *data = WOL_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_wol)
		वापस -EOPNOTSUPP;

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	dev->ethtool_ops->get_wol(dev, &data->wol);
	ethnl_ops_complete(dev);
	/* करो not include password in notअगरications */
	data->show_sopass = info && (data->wol.supported & WAKE_MAGICSECURE);

	वापस 0;
पूर्ण

अटल पूर्णांक wol_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			  स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा wol_reply_data *data = WOL_REPDATA(reply_base);
	पूर्णांक len;

	len = ethnl_bitset32_size(&data->wol.wolopts, &data->wol.supported,
				  WOL_MODE_COUNT, wol_mode_names, compact);
	अगर (len < 0)
		वापस len;
	अगर (data->show_sopass)
		len += nla_total_size(माप(data->wol.sopass));

	वापस len;
पूर्ण

अटल पूर्णांक wol_fill_reply(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा ethnl_req_info *req_base,
			  स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा wol_reply_data *data = WOL_REPDATA(reply_base);
	पूर्णांक ret;

	ret = ethnl_put_bitset32(skb, ETHTOOL_A_WOL_MODES, &data->wol.wolopts,
				 &data->wol.supported, WOL_MODE_COUNT,
				 wol_mode_names, compact);
	अगर (ret < 0)
		वापस ret;
	अगर (data->show_sopass &&
	    nla_put(skb, ETHTOOL_A_WOL_SOPASS, माप(data->wol.sopass),
		    data->wol.sopass))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_wol_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_WOL_GET,
	.reply_cmd		= ETHTOOL_MSG_WOL_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_WOL_HEADER,
	.req_info_size		= माप(काष्ठा wol_req_info),
	.reply_data_size	= माप(काष्ठा wol_reply_data),

	.prepare_data		= wol_prepare_data,
	.reply_size		= wol_reply_size,
	.fill_reply		= wol_fill_reply,
पूर्ण;

/* WOL_SET */

स्थिर काष्ठा nla_policy ethnl_wol_set_policy[] = अणु
	[ETHTOOL_A_WOL_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_WOL_MODES]		= अणु .type = NLA_NESTED पूर्ण,
	[ETHTOOL_A_WOL_SOPASS]		= अणु .type = NLA_BINARY,
					    .len = SOPASS_MAX पूर्ण,
पूर्ण;

पूर्णांक ethnl_set_wol(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा ethtool_wolinfo wol = अणु .cmd = ETHTOOL_GWOL पूर्ण;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा net_device *dev;
	bool mod = false;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info, tb[ETHTOOL_A_WOL_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ret = -EOPNOTSUPP;
	अगर (!dev->ethtool_ops->get_wol || !dev->ethtool_ops->set_wol)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;

	dev->ethtool_ops->get_wol(dev, &wol);
	ret = ethnl_update_bitset32(&wol.wolopts, WOL_MODE_COUNT,
				    tb[ETHTOOL_A_WOL_MODES], wol_mode_names,
				    info->extack, &mod);
	अगर (ret < 0)
		जाओ out_ops;
	अगर (wol.wolopts & ~wol.supported) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, tb[ETHTOOL_A_WOL_MODES],
				    "cannot enable unsupported WoL mode");
		ret = -EINVAL;
		जाओ out_ops;
	पूर्ण
	अगर (tb[ETHTOOL_A_WOL_SOPASS]) अणु
		अगर (!(wol.supported & WAKE_MAGICSECURE)) अणु
			NL_SET_ERR_MSG_ATTR(info->extack,
					    tb[ETHTOOL_A_WOL_SOPASS],
					    "magicsecure not supported, cannot set password");
			ret = -EINVAL;
			जाओ out_ops;
		पूर्ण
		ethnl_update_binary(wol.sopass, माप(wol.sopass),
				    tb[ETHTOOL_A_WOL_SOPASS], &mod);
	पूर्ण

	अगर (!mod)
		जाओ out_ops;
	ret = dev->ethtool_ops->set_wol(dev, &wol);
	अगर (ret)
		जाओ out_ops;
	dev->wol_enabled = !!wol.wolopts;
	ethtool_notअगरy(dev, ETHTOOL_MSG_WOL_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
