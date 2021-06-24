<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/net_tstamp.h>

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

काष्ठा tsinfo_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा tsinfo_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_ts_info		ts_info;
पूर्ण;

#घोषणा TSINFO_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा tsinfo_reply_data, base)

स्थिर काष्ठा nla_policy ethnl_tsinfo_get_policy[] = अणु
	[ETHTOOL_A_TSINFO_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
पूर्ण;

अटल पूर्णांक tsinfo_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			       काष्ठा ethnl_reply_data *reply_base,
			       काष्ठा genl_info *info)
अणु
	काष्ठा tsinfo_reply_data *data = TSINFO_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	ret = __ethtool_get_ts_info(dev, &data->ts_info);
	ethnl_ops_complete(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक tsinfo_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			     स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा tsinfo_reply_data *data = TSINFO_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा ethtool_ts_info *ts_info = &data->ts_info;
	पूर्णांक len = 0;
	पूर्णांक ret;

	BUILD_BUG_ON(__SOF_TIMESTAMPING_CNT > 32);
	BUILD_BUG_ON(__HWTSTAMP_TX_CNT > 32);
	BUILD_BUG_ON(__HWTSTAMP_FILTER_CNT > 32);

	अगर (ts_info->so_बारtamping) अणु
		ret = ethnl_bitset32_size(&ts_info->so_बारtamping, शून्य,
					  __SOF_TIMESTAMPING_CNT,
					  sof_बारtamping_names, compact);
		अगर (ret < 0)
			वापस ret;
		len += ret;	/* _TSINFO_TIMESTAMPING */
	पूर्ण
	अगर (ts_info->tx_types) अणु
		ret = ethnl_bitset32_size(&ts_info->tx_types, शून्य,
					  __HWTSTAMP_TX_CNT,
					  ts_tx_type_names, compact);
		अगर (ret < 0)
			वापस ret;
		len += ret;	/* _TSINFO_TX_TYPES */
	पूर्ण
	अगर (ts_info->rx_filters) अणु
		ret = ethnl_bitset32_size(&ts_info->rx_filters, शून्य,
					  __HWTSTAMP_FILTER_CNT,
					  ts_rx_filter_names, compact);
		अगर (ret < 0)
			वापस ret;
		len += ret;	/* _TSINFO_RX_FILTERS */
	पूर्ण
	अगर (ts_info->phc_index >= 0)
		len += nla_total_size(माप(u32));	/* _TSINFO_PHC_INDEX */

	वापस len;
पूर्ण

अटल पूर्णांक tsinfo_fill_reply(काष्ठा sk_buff *skb,
			     स्थिर काष्ठा ethnl_req_info *req_base,
			     स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा tsinfo_reply_data *data = TSINFO_REPDATA(reply_base);
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा ethtool_ts_info *ts_info = &data->ts_info;
	पूर्णांक ret;

	अगर (ts_info->so_बारtamping) अणु
		ret = ethnl_put_bitset32(skb, ETHTOOL_A_TSINFO_TIMESTAMPING,
					 &ts_info->so_बारtamping, शून्य,
					 __SOF_TIMESTAMPING_CNT,
					 sof_बारtamping_names, compact);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (ts_info->tx_types) अणु
		ret = ethnl_put_bitset32(skb, ETHTOOL_A_TSINFO_TX_TYPES,
					 &ts_info->tx_types, शून्य,
					 __HWTSTAMP_TX_CNT,
					 ts_tx_type_names, compact);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (ts_info->rx_filters) अणु
		ret = ethnl_put_bitset32(skb, ETHTOOL_A_TSINFO_RX_FILTERS,
					 &ts_info->rx_filters, शून्य,
					 __HWTSTAMP_FILTER_CNT,
					 ts_rx_filter_names, compact);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	अगर (ts_info->phc_index >= 0 &&
	    nla_put_u32(skb, ETHTOOL_A_TSINFO_PHC_INDEX, ts_info->phc_index))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_tsinfo_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_TSINFO_GET,
	.reply_cmd		= ETHTOOL_MSG_TSINFO_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_TSINFO_HEADER,
	.req_info_size		= माप(काष्ठा tsinfo_req_info),
	.reply_data_size	= माप(काष्ठा tsinfo_reply_data),

	.prepare_data		= tsinfo_prepare_data,
	.reply_size		= tsinfo_reply_size,
	.fill_reply		= tsinfo_fill_reply,
पूर्ण;
