<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

काष्ठा stats_req_info अणु
	काष्ठा ethnl_req_info		base;
	DECLARE_BITMAP(stat_mask, __ETHTOOL_STATS_CNT);
पूर्ण;

#घोषणा STATS_REQINFO(__req_base) \
	container_of(__req_base, काष्ठा stats_req_info, base)

काष्ठा stats_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	काष्ठा ethtool_eth_phy_stats	phy_stats;
	काष्ठा ethtool_eth_mac_stats	mac_stats;
	काष्ठा ethtool_eth_ctrl_stats	ctrl_stats;
	काष्ठा ethtool_rmon_stats	rmon_stats;
	स्थिर काष्ठा ethtool_rmon_hist_range	*rmon_ranges;
पूर्ण;

#घोषणा STATS_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा stats_reply_data, base)

स्थिर अक्षर stats_std_names[__ETHTOOL_STATS_CNT][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_STATS_ETH_PHY]			= "eth-phy",
	[ETHTOOL_STATS_ETH_MAC]			= "eth-mac",
	[ETHTOOL_STATS_ETH_CTRL]		= "eth-ctrl",
	[ETHTOOL_STATS_RMON]			= "rmon",
पूर्ण;

स्थिर अक्षर stats_eth_phy_names[__ETHTOOL_A_STATS_ETH_PHY_CNT][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_A_STATS_ETH_PHY_5_SYM_ERR]	= "SymbolErrorDuringCarrier",
पूर्ण;

स्थिर अक्षर stats_eth_mac_names[__ETHTOOL_A_STATS_ETH_MAC_CNT][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_A_STATS_ETH_MAC_2_TX_PKT]	= "FramesTransmittedOK",
	[ETHTOOL_A_STATS_ETH_MAC_3_SINGLE_COL]	= "SingleCollisionFrames",
	[ETHTOOL_A_STATS_ETH_MAC_4_MULTI_COL]	= "MultipleCollisionFrames",
	[ETHTOOL_A_STATS_ETH_MAC_5_RX_PKT]	= "FramesReceivedOK",
	[ETHTOOL_A_STATS_ETH_MAC_6_FCS_ERR]	= "FrameCheckSequenceErrors",
	[ETHTOOL_A_STATS_ETH_MAC_7_ALIGN_ERR]	= "AlignmentErrors",
	[ETHTOOL_A_STATS_ETH_MAC_8_TX_BYTES]	= "OctetsTransmittedOK",
	[ETHTOOL_A_STATS_ETH_MAC_9_TX_DEFER]	= "FramesWithDeferredXmissions",
	[ETHTOOL_A_STATS_ETH_MAC_10_LATE_COL]	= "LateCollisions",
	[ETHTOOL_A_STATS_ETH_MAC_11_XS_COL]	= "FramesAbortedDueToXSColls",
	[ETHTOOL_A_STATS_ETH_MAC_12_TX_INT_ERR]	= "FramesLostDueToIntMACXmitError",
	[ETHTOOL_A_STATS_ETH_MAC_13_CS_ERR]	= "CarrierSenseErrors",
	[ETHTOOL_A_STATS_ETH_MAC_14_RX_BYTES]	= "OctetsReceivedOK",
	[ETHTOOL_A_STATS_ETH_MAC_15_RX_INT_ERR]	= "FramesLostDueToIntMACRcvError",
	[ETHTOOL_A_STATS_ETH_MAC_18_TX_MCAST]	= "MulticastFramesXmittedOK",
	[ETHTOOL_A_STATS_ETH_MAC_19_TX_BCAST]	= "BroadcastFramesXmittedOK",
	[ETHTOOL_A_STATS_ETH_MAC_20_XS_DEFER]	= "FramesWithExcessiveDeferral",
	[ETHTOOL_A_STATS_ETH_MAC_21_RX_MCAST]	= "MulticastFramesReceivedOK",
	[ETHTOOL_A_STATS_ETH_MAC_22_RX_BCAST]	= "BroadcastFramesReceivedOK",
	[ETHTOOL_A_STATS_ETH_MAC_23_IR_LEN_ERR]	= "InRangeLengthErrors",
	[ETHTOOL_A_STATS_ETH_MAC_24_OOR_LEN]	= "OutOfRangeLengthField",
	[ETHTOOL_A_STATS_ETH_MAC_25_TOO_LONG_ERR]	= "FrameTooLongErrors",
पूर्ण;

स्थिर अक्षर stats_eth_ctrl_names[__ETHTOOL_A_STATS_ETH_CTRL_CNT][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_A_STATS_ETH_CTRL_3_TX]		= "MACControlFramesTransmitted",
	[ETHTOOL_A_STATS_ETH_CTRL_4_RX]		= "MACControlFramesReceived",
	[ETHTOOL_A_STATS_ETH_CTRL_5_RX_UNSUP]	= "UnsupportedOpcodesReceived",
पूर्ण;

स्थिर अक्षर stats_rmon_names[__ETHTOOL_A_STATS_RMON_CNT][ETH_GSTRING_LEN] = अणु
	[ETHTOOL_A_STATS_RMON_UNDERSIZE]	= "etherStatsUndersizePkts",
	[ETHTOOL_A_STATS_RMON_OVERSIZE]		= "etherStatsOversizePkts",
	[ETHTOOL_A_STATS_RMON_FRAG]		= "etherStatsFragments",
	[ETHTOOL_A_STATS_RMON_JABBER]		= "etherStatsJabbers",
पूर्ण;

स्थिर काष्ठा nla_policy ethnl_stats_get_policy[ETHTOOL_A_STATS_GROUPS + 1] = अणु
	[ETHTOOL_A_STATS_HEADER]	=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_STATS_GROUPS]	= अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल पूर्णांक stats_parse_request(काष्ठा ethnl_req_info *req_base,
			       काष्ठा nlattr **tb,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा stats_req_info *req_info = STATS_REQINFO(req_base);
	bool mod = false;
	पूर्णांक err;

	err = ethnl_update_bitset(req_info->stat_mask, __ETHTOOL_STATS_CNT,
				  tb[ETHTOOL_A_STATS_GROUPS], stats_std_names,
				  extack, &mod);
	अगर (err)
		वापस err;

	अगर (!mod) अणु
		NL_SET_ERR_MSG(extack, "no stats requested");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक stats_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			      काष्ठा ethnl_reply_data *reply_base,
			      काष्ठा genl_info *info)
अणु
	स्थिर काष्ठा stats_req_info *req_info = STATS_REQINFO(req_base);
	काष्ठा stats_reply_data *data = STATS_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	पूर्णांक ret;

	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;

	/* Mark all stats as unset (see ETHTOOL_STAT_NOT_SET) to prevent them
	 * from being reported to user space in हाल driver did not set them.
	 */
	स_रखो(&data->phy_stats, 0xff, माप(data->phy_stats));
	स_रखो(&data->mac_stats, 0xff, माप(data->mac_stats));
	स_रखो(&data->ctrl_stats, 0xff, माप(data->ctrl_stats));
	स_रखो(&data->rmon_stats, 0xff, माप(data->rmon_stats));

	अगर (test_bit(ETHTOOL_STATS_ETH_PHY, req_info->stat_mask) &&
	    dev->ethtool_ops->get_eth_phy_stats)
		dev->ethtool_ops->get_eth_phy_stats(dev, &data->phy_stats);
	अगर (test_bit(ETHTOOL_STATS_ETH_MAC, req_info->stat_mask) &&
	    dev->ethtool_ops->get_eth_mac_stats)
		dev->ethtool_ops->get_eth_mac_stats(dev, &data->mac_stats);
	अगर (test_bit(ETHTOOL_STATS_ETH_CTRL, req_info->stat_mask) &&
	    dev->ethtool_ops->get_eth_ctrl_stats)
		dev->ethtool_ops->get_eth_ctrl_stats(dev, &data->ctrl_stats);
	अगर (test_bit(ETHTOOL_STATS_RMON, req_info->stat_mask) &&
	    dev->ethtool_ops->get_rmon_stats)
		dev->ethtool_ops->get_rmon_stats(dev, &data->rmon_stats,
						 &data->rmon_ranges);

	ethnl_ops_complete(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक stats_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा stats_req_info *req_info = STATS_REQINFO(req_base);
	अचिन्हित पूर्णांक n_grps = 0, n_stats = 0;
	पूर्णांक len = 0;

	अगर (test_bit(ETHTOOL_STATS_ETH_PHY, req_info->stat_mask)) अणु
		n_stats += माप(काष्ठा ethtool_eth_phy_stats) / माप(u64);
		n_grps++;
	पूर्ण
	अगर (test_bit(ETHTOOL_STATS_ETH_MAC, req_info->stat_mask)) अणु
		n_stats += माप(काष्ठा ethtool_eth_mac_stats) / माप(u64);
		n_grps++;
	पूर्ण
	अगर (test_bit(ETHTOOL_STATS_ETH_CTRL, req_info->stat_mask)) अणु
		n_stats += माप(काष्ठा ethtool_eth_ctrl_stats) / माप(u64);
		n_grps++;
	पूर्ण
	अगर (test_bit(ETHTOOL_STATS_RMON, req_info->stat_mask)) अणु
		n_stats += माप(काष्ठा ethtool_rmon_stats) / माप(u64);
		n_grps++;
		/* Above includes the space क्रम _A_STATS_GRP_HIST_VALs */

		len += (nla_total_size(0) +	/* _A_STATS_GRP_HIST */
			nla_total_size(4) +	/* _A_STATS_GRP_HIST_BKT_LOW */
			nla_total_size(4)) *	/* _A_STATS_GRP_HIST_BKT_HI */
			ETHTOOL_RMON_HIST_MAX * 2;
	पूर्ण

	len += n_grps * (nla_total_size(0) + /* _A_STATS_GRP */
			 nla_total_size(4) + /* _A_STATS_GRP_ID */
			 nla_total_size(4)); /* _A_STATS_GRP_SS_ID */
	len += n_stats * (nla_total_size(0) + /* _A_STATS_GRP_STAT */
			  nla_total_size_64bit(माप(u64)));

	वापस len;
पूर्ण

अटल पूर्णांक stat_put(काष्ठा sk_buff *skb, u16 attrtype, u64 val)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक ret;

	अगर (val == ETHTOOL_STAT_NOT_SET)
		वापस 0;

	/* We want to start stats attr types from 0, so we करोn't have a type
	 * क्रम pad inside ETHTOOL_A_STATS_GRP_STAT. Pad things on the outside
	 * of ETHTOOL_A_STATS_GRP_STAT. Since we're one nest away from the
	 * actual attr we're 4B off - nla_need_padding_क्रम_64bit() & co.
	 * can't be used.
	 */
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (!IS_ALIGNED((अचिन्हित दीर्घ)skb_tail_poपूर्णांकer(skb), 8))
		अगर (!nla_reserve(skb, ETHTOOL_A_STATS_GRP_PAD, 0))
			वापस -EMSGSIZE;
#पूर्ण_अगर

	nest = nla_nest_start(skb, ETHTOOL_A_STATS_GRP_STAT);
	अगर (!nest)
		वापस -EMSGSIZE;

	ret = nla_put_u64_64bit(skb, attrtype, val, -1 /* not used */);
	अगर (ret) अणु
		nla_nest_cancel(skb, nest);
		वापस ret;
	पूर्ण

	nla_nest_end(skb, nest);
	वापस 0;
पूर्ण

अटल पूर्णांक stats_put_phy_stats(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा stats_reply_data *data)
अणु
	अगर (stat_put(skb, ETHTOOL_A_STATS_ETH_PHY_5_SYM_ERR,
		     data->phy_stats.SymbolErrorDuringCarrier))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक stats_put_mac_stats(काष्ठा sk_buff *skb,
			       स्थिर काष्ठा stats_reply_data *data)
अणु
	अगर (stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_2_TX_PKT,
		     data->mac_stats.FramesTransmittedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_3_SINGLE_COL,
		     data->mac_stats.SingleCollisionFrames) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_4_MULTI_COL,
		     data->mac_stats.MultipleCollisionFrames) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_5_RX_PKT,
		     data->mac_stats.FramesReceivedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_6_FCS_ERR,
		     data->mac_stats.FrameCheckSequenceErrors) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_7_ALIGN_ERR,
		     data->mac_stats.AlignmentErrors) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_8_TX_BYTES,
		     data->mac_stats.OctetsTransmittedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_9_TX_DEFER,
		     data->mac_stats.FramesWithDeferredXmissions) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_10_LATE_COL,
		     data->mac_stats.LateCollisions) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_11_XS_COL,
		     data->mac_stats.FramesAbortedDueToXSColls) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_12_TX_INT_ERR,
		     data->mac_stats.FramesLostDueToIntMACXmitError) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_13_CS_ERR,
		     data->mac_stats.CarrierSenseErrors) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_14_RX_BYTES,
		     data->mac_stats.OctetsReceivedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_15_RX_INT_ERR,
		     data->mac_stats.FramesLostDueToIntMACRcvError) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_18_TX_MCAST,
		     data->mac_stats.MulticastFramesXmittedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_19_TX_BCAST,
		     data->mac_stats.BroadcastFramesXmittedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_20_XS_DEFER,
		     data->mac_stats.FramesWithExcessiveDeferral) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_21_RX_MCAST,
		     data->mac_stats.MulticastFramesReceivedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_22_RX_BCAST,
		     data->mac_stats.BroadcastFramesReceivedOK) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_23_IR_LEN_ERR,
		     data->mac_stats.InRangeLengthErrors) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_24_OOR_LEN,
		     data->mac_stats.OutOfRangeLengthField) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_MAC_25_TOO_LONG_ERR,
		     data->mac_stats.FrameTooLongErrors))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक stats_put_ctrl_stats(काष्ठा sk_buff *skb,
				स्थिर काष्ठा stats_reply_data *data)
अणु
	अगर (stat_put(skb, ETHTOOL_A_STATS_ETH_CTRL_3_TX,
		     data->ctrl_stats.MACControlFramesTransmitted) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_CTRL_4_RX,
		     data->ctrl_stats.MACControlFramesReceived) ||
	    stat_put(skb, ETHTOOL_A_STATS_ETH_CTRL_5_RX_UNSUP,
		     data->ctrl_stats.UnsupportedOpcodesReceived))
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

अटल पूर्णांक stats_put_rmon_hist(काष्ठा sk_buff *skb, u32 attr, स्थिर u64 *hist,
			       स्थिर काष्ठा ethtool_rmon_hist_range *ranges)
अणु
	काष्ठा nlattr *nest;
	पूर्णांक i;

	अगर (!ranges)
		वापस 0;

	क्रम (i = 0; i <	ETHTOOL_RMON_HIST_MAX; i++) अणु
		अगर (!ranges[i].low && !ranges[i].high)
			अवरोध;
		अगर (hist[i] == ETHTOOL_STAT_NOT_SET)
			जारी;

		nest = nla_nest_start(skb, attr);
		अगर (!nest)
			वापस -EMSGSIZE;

		अगर (nla_put_u32(skb, ETHTOOL_A_STATS_GRP_HIST_BKT_LOW,
				ranges[i].low) ||
		    nla_put_u32(skb, ETHTOOL_A_STATS_GRP_HIST_BKT_HI,
				ranges[i].high) ||
		    nla_put_u64_64bit(skb, ETHTOOL_A_STATS_GRP_HIST_VAL,
				      hist[i], ETHTOOL_A_STATS_GRP_PAD))
			जाओ err_cancel_hist;

		nla_nest_end(skb, nest);
	पूर्ण

	वापस 0;

err_cancel_hist:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक stats_put_rmon_stats(काष्ठा sk_buff *skb,
				स्थिर काष्ठा stats_reply_data *data)
अणु
	अगर (stats_put_rmon_hist(skb, ETHTOOL_A_STATS_GRP_HIST_RX,
				data->rmon_stats.hist, data->rmon_ranges) ||
	    stats_put_rmon_hist(skb, ETHTOOL_A_STATS_GRP_HIST_TX,
				data->rmon_stats.hist_tx, data->rmon_ranges))
		वापस -EMSGSIZE;

	अगर (stat_put(skb, ETHTOOL_A_STATS_RMON_UNDERSIZE,
		     data->rmon_stats.undersize_pkts) ||
	    stat_put(skb, ETHTOOL_A_STATS_RMON_OVERSIZE,
		     data->rmon_stats.oversize_pkts) ||
	    stat_put(skb, ETHTOOL_A_STATS_RMON_FRAG,
		     data->rmon_stats.fragments) ||
	    stat_put(skb, ETHTOOL_A_STATS_RMON_JABBER,
		     data->rmon_stats.jabbers))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

अटल पूर्णांक stats_put_stats(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा stats_reply_data *data,
			   u32 id, u32 ss_id,
			   पूर्णांक (*cb)(काष्ठा sk_buff *skb,
				     स्थिर काष्ठा stats_reply_data *data))
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start(skb, ETHTOOL_A_STATS_GRP);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_u32(skb, ETHTOOL_A_STATS_GRP_ID, id) ||
	    nla_put_u32(skb, ETHTOOL_A_STATS_GRP_SS_ID, ss_id))
		जाओ err_cancel;

	अगर (cb(skb, data))
		जाओ err_cancel;

	nla_nest_end(skb, nest);
	वापस 0;

err_cancel:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक stats_fill_reply(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा ethnl_req_info *req_base,
			    स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	स्थिर काष्ठा stats_req_info *req_info = STATS_REQINFO(req_base);
	स्थिर काष्ठा stats_reply_data *data = STATS_REPDATA(reply_base);
	पूर्णांक ret = 0;

	अगर (!ret && test_bit(ETHTOOL_STATS_ETH_PHY, req_info->stat_mask))
		ret = stats_put_stats(skb, data, ETHTOOL_STATS_ETH_PHY,
				      ETH_SS_STATS_ETH_PHY,
				      stats_put_phy_stats);
	अगर (!ret && test_bit(ETHTOOL_STATS_ETH_MAC, req_info->stat_mask))
		ret = stats_put_stats(skb, data, ETHTOOL_STATS_ETH_MAC,
				      ETH_SS_STATS_ETH_MAC,
				      stats_put_mac_stats);
	अगर (!ret && test_bit(ETHTOOL_STATS_ETH_CTRL, req_info->stat_mask))
		ret = stats_put_stats(skb, data, ETHTOOL_STATS_ETH_CTRL,
				      ETH_SS_STATS_ETH_CTRL,
				      stats_put_ctrl_stats);
	अगर (!ret && test_bit(ETHTOOL_STATS_RMON, req_info->stat_mask))
		ret = stats_put_stats(skb, data, ETHTOOL_STATS_RMON,
				      ETH_SS_STATS_RMON, stats_put_rmon_stats);

	वापस ret;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_stats_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_STATS_GET,
	.reply_cmd		= ETHTOOL_MSG_STATS_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_STATS_HEADER,
	.req_info_size		= माप(काष्ठा stats_req_info),
	.reply_data_size	= माप(काष्ठा stats_reply_data),

	.parse_request		= stats_parse_request,
	.prepare_data		= stats_prepare_data,
	.reply_size		= stats_reply_size,
	.fill_reply		= stats_fill_reply,
पूर्ण;
