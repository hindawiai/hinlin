<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश "netlink.h"
#समावेश "common.h"
#समावेश "bitset.h"

काष्ठा fec_req_info अणु
	काष्ठा ethnl_req_info		base;
पूर्ण;

काष्ठा fec_reply_data अणु
	काष्ठा ethnl_reply_data		base;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(fec_link_modes);
	u32 active_fec;
	u8 fec_स्वतः;
	काष्ठा fec_stat_grp अणु
		u64 stats[1 + ETHTOOL_MAX_LANES];
		u8 cnt;
	पूर्ण corr, uncorr, corr_bits;
पूर्ण;

#घोषणा FEC_REPDATA(__reply_base) \
	container_of(__reply_base, काष्ठा fec_reply_data, base)

#घोषणा ETHTOOL_FEC_MASK	((ETHTOOL_FEC_LLRS << 1) - 1)

स्थिर काष्ठा nla_policy ethnl_fec_get_policy[ETHTOOL_A_FEC_HEADER + 1] = अणु
	[ETHTOOL_A_FEC_HEADER]	= NLA_POLICY_NESTED(ethnl_header_policy_stats),
पूर्ण;

अटल व्योम
ethtool_fec_to_link_modes(u32 fec, अचिन्हित दीर्घ *link_modes, u8 *fec_स्वतः)
अणु
	अगर (fec_स्वतः)
		*fec_स्वतः = !!(fec & ETHTOOL_FEC_AUTO);

	अगर (fec & ETHTOOL_FEC_OFF)
		__set_bit(ETHTOOL_LINK_MODE_FEC_NONE_BIT, link_modes);
	अगर (fec & ETHTOOL_FEC_RS)
		__set_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT, link_modes);
	अगर (fec & ETHTOOL_FEC_BASER)
		__set_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT, link_modes);
	अगर (fec & ETHTOOL_FEC_LLRS)
		__set_bit(ETHTOOL_LINK_MODE_FEC_LLRS_BIT, link_modes);
पूर्ण

अटल पूर्णांक
ethtool_link_modes_to_fecparam(काष्ठा ethtool_fecparam *fec,
			       अचिन्हित दीर्घ *link_modes, u8 fec_स्वतः)
अणु
	स_रखो(fec, 0, माप(*fec));

	अगर (fec_स्वतः)
		fec->fec |= ETHTOOL_FEC_AUTO;

	अगर (__test_and_clear_bit(ETHTOOL_LINK_MODE_FEC_NONE_BIT, link_modes))
		fec->fec |= ETHTOOL_FEC_OFF;
	अगर (__test_and_clear_bit(ETHTOOL_LINK_MODE_FEC_RS_BIT, link_modes))
		fec->fec |= ETHTOOL_FEC_RS;
	अगर (__test_and_clear_bit(ETHTOOL_LINK_MODE_FEC_BASER_BIT, link_modes))
		fec->fec |= ETHTOOL_FEC_BASER;
	अगर (__test_and_clear_bit(ETHTOOL_LINK_MODE_FEC_LLRS_BIT, link_modes))
		fec->fec |= ETHTOOL_FEC_LLRS;

	अगर (!biपंचांगap_empty(link_modes, __ETHTOOL_LINK_MODE_MASK_NBITS))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम
fec_stats_recalc(काष्ठा fec_stat_grp *grp, काष्ठा ethtool_fec_stat *stats)
अणु
	पूर्णांक i;

	अगर (stats->lanes[0] == ETHTOOL_STAT_NOT_SET) अणु
		grp->stats[0] = stats->total;
		grp->cnt = stats->total != ETHTOOL_STAT_NOT_SET;
		वापस;
	पूर्ण

	grp->cnt = 1;
	grp->stats[0] = 0;
	क्रम (i = 0; i < ETHTOOL_MAX_LANES; i++) अणु
		अगर (stats->lanes[i] == ETHTOOL_STAT_NOT_SET)
			अवरोध;

		grp->stats[0] += stats->lanes[i];
		grp->stats[grp->cnt++] = stats->lanes[i];
	पूर्ण
पूर्ण

अटल पूर्णांक fec_prepare_data(स्थिर काष्ठा ethnl_req_info *req_base,
			    काष्ठा ethnl_reply_data *reply_base,
			    काष्ठा genl_info *info)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(active_fec_modes) = अणुपूर्ण;
	काष्ठा fec_reply_data *data = FEC_REPDATA(reply_base);
	काष्ठा net_device *dev = reply_base->dev;
	काष्ठा ethtool_fecparam fec = अणुपूर्ण;
	पूर्णांक ret;

	अगर (!dev->ethtool_ops->get_fecparam)
		वापस -EOPNOTSUPP;
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		वापस ret;
	ret = dev->ethtool_ops->get_fecparam(dev, &fec);
	अगर (ret)
		जाओ out_complete;
	अगर (req_base->flags & ETHTOOL_FLAG_STATS &&
	    dev->ethtool_ops->get_fec_stats) अणु
		काष्ठा ethtool_fec_stats stats;

		ethtool_stats_init((u64 *)&stats, माप(stats) / 8);
		dev->ethtool_ops->get_fec_stats(dev, &stats);

		fec_stats_recalc(&data->corr, &stats.corrected_blocks);
		fec_stats_recalc(&data->uncorr, &stats.uncorrectable_blocks);
		fec_stats_recalc(&data->corr_bits, &stats.corrected_bits);
	पूर्ण

	WARN_ON_ONCE(fec.reserved);

	ethtool_fec_to_link_modes(fec.fec, data->fec_link_modes,
				  &data->fec_स्वतः);

	ethtool_fec_to_link_modes(fec.active_fec, active_fec_modes, शून्य);
	data->active_fec = find_first_bit(active_fec_modes,
					  __ETHTOOL_LINK_MODE_MASK_NBITS);
	/* Don't report attr अगर no FEC mode set. Note that
	 * ethtool_fecparam_to_link_modes() ignores NONE and AUTO.
	 */
	अगर (data->active_fec == __ETHTOOL_LINK_MODE_MASK_NBITS)
		data->active_fec = 0;

out_complete:
	ethnl_ops_complete(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक fec_reply_size(स्थिर काष्ठा ethnl_req_info *req_base,
			  स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा fec_reply_data *data = FEC_REPDATA(reply_base);
	पूर्णांक len = 0;
	पूर्णांक ret;

	ret = ethnl_bitset_size(data->fec_link_modes, शून्य,
				__ETHTOOL_LINK_MODE_MASK_NBITS,
				link_mode_names, compact);
	अगर (ret < 0)
		वापस ret;
	len += ret;

	len += nla_total_size(माप(u8)) +	/* _FEC_AUTO */
	       nla_total_size(माप(u32));	/* _FEC_ACTIVE */

	अगर (req_base->flags & ETHTOOL_FLAG_STATS)
		len += 3 * nla_total_size_64bit(माप(u64) *
						(1 + ETHTOOL_MAX_LANES));

	वापस len;
पूर्ण

अटल पूर्णांक fec_put_stats(काष्ठा sk_buff *skb, स्थिर काष्ठा fec_reply_data *data)
अणु
	काष्ठा nlattr *nest;

	nest = nla_nest_start(skb, ETHTOOL_A_FEC_STATS);
	अगर (!nest)
		वापस -EMSGSIZE;

	अगर (nla_put_64bit(skb, ETHTOOL_A_FEC_STAT_CORRECTED,
			  माप(u64) * data->corr.cnt,
			  data->corr.stats, ETHTOOL_A_FEC_STAT_PAD) ||
	    nla_put_64bit(skb, ETHTOOL_A_FEC_STAT_UNCORR,
			  माप(u64) * data->uncorr.cnt,
			  data->uncorr.stats, ETHTOOL_A_FEC_STAT_PAD) ||
	    nla_put_64bit(skb, ETHTOOL_A_FEC_STAT_CORR_BITS,
			  माप(u64) * data->corr_bits.cnt,
			  data->corr_bits.stats, ETHTOOL_A_FEC_STAT_PAD))
		जाओ err_cancel;

	nla_nest_end(skb, nest);
	वापस 0;

err_cancel:
	nla_nest_cancel(skb, nest);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fec_fill_reply(काष्ठा sk_buff *skb,
			  स्थिर काष्ठा ethnl_req_info *req_base,
			  स्थिर काष्ठा ethnl_reply_data *reply_base)
अणु
	bool compact = req_base->flags & ETHTOOL_FLAG_COMPACT_BITSETS;
	स्थिर काष्ठा fec_reply_data *data = FEC_REPDATA(reply_base);
	पूर्णांक ret;

	ret = ethnl_put_bitset(skb, ETHTOOL_A_FEC_MODES,
			       data->fec_link_modes, शून्य,
			       __ETHTOOL_LINK_MODE_MASK_NBITS,
			       link_mode_names, compact);
	अगर (ret < 0)
		वापस ret;

	अगर (nla_put_u8(skb, ETHTOOL_A_FEC_AUTO, data->fec_स्वतः) ||
	    (data->active_fec &&
	     nla_put_u32(skb, ETHTOOL_A_FEC_ACTIVE, data->active_fec)))
		वापस -EMSGSIZE;

	अगर (req_base->flags & ETHTOOL_FLAG_STATS && fec_put_stats(skb, data))
		वापस -EMSGSIZE;

	वापस 0;
पूर्ण

स्थिर काष्ठा ethnl_request_ops ethnl_fec_request_ops = अणु
	.request_cmd		= ETHTOOL_MSG_FEC_GET,
	.reply_cmd		= ETHTOOL_MSG_FEC_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_FEC_HEADER,
	.req_info_size		= माप(काष्ठा fec_req_info),
	.reply_data_size	= माप(काष्ठा fec_reply_data),

	.prepare_data		= fec_prepare_data,
	.reply_size		= fec_reply_size,
	.fill_reply		= fec_fill_reply,
पूर्ण;

/* FEC_SET */

स्थिर काष्ठा nla_policy ethnl_fec_set_policy[ETHTOOL_A_FEC_AUTO + 1] = अणु
	[ETHTOOL_A_FEC_HEADER]	= NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_FEC_MODES]	= अणु .type = NLA_NESTED पूर्ण,
	[ETHTOOL_A_FEC_AUTO]	= NLA_POLICY_MAX(NLA_U8, 1),
पूर्ण;

पूर्णांक ethnl_set_fec(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(fec_link_modes) = अणुपूर्ण;
	काष्ठा ethnl_req_info req_info = अणुपूर्ण;
	काष्ठा nlattr **tb = info->attrs;
	काष्ठा ethtool_fecparam fec = अणुपूर्ण;
	स्थिर काष्ठा ethtool_ops *ops;
	काष्ठा net_device *dev;
	bool mod = false;
	u8 fec_स्वतः;
	पूर्णांक ret;

	ret = ethnl_parse_header_dev_get(&req_info, tb[ETHTOOL_A_FEC_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	अगर (ret < 0)
		वापस ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	अगर (!ops->get_fecparam || !ops->set_fecparam)
		जाओ out_dev;

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	अगर (ret < 0)
		जाओ out_rtnl;
	ret = ops->get_fecparam(dev, &fec);
	अगर (ret < 0)
		जाओ out_ops;

	ethtool_fec_to_link_modes(fec.fec, fec_link_modes, &fec_स्वतः);

	ret = ethnl_update_bitset(fec_link_modes,
				  __ETHTOOL_LINK_MODE_MASK_NBITS,
				  tb[ETHTOOL_A_FEC_MODES],
				  link_mode_names, info->extack, &mod);
	अगर (ret < 0)
		जाओ out_ops;
	ethnl_update_u8(&fec_स्वतः, tb[ETHTOOL_A_FEC_AUTO], &mod);

	ret = 0;
	अगर (!mod)
		जाओ out_ops;

	ret = ethtool_link_modes_to_fecparam(&fec, fec_link_modes, fec_स्वतः);
	अगर (ret) अणु
		NL_SET_ERR_MSG_ATTR(info->extack, tb[ETHTOOL_A_FEC_MODES],
				    "invalid FEC modes requested");
		जाओ out_ops;
	पूर्ण
	अगर (!fec.fec) अणु
		ret = -EINVAL;
		NL_SET_ERR_MSG_ATTR(info->extack, tb[ETHTOOL_A_FEC_MODES],
				    "no FEC modes set");
		जाओ out_ops;
	पूर्ण

	ret = dev->ethtool_ops->set_fecparam(dev, &fec);
	अगर (ret < 0)
		जाओ out_ops;
	ethtool_notअगरy(dev, ETHTOOL_MSG_FEC_NTF, शून्य);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	वापस ret;
पूर्ण
