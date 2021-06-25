<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 ethtool hooks क्रम cfg80211
 *
 * Copied from cfg.c - originally
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2014	Intel Corporation (Author: Johannes Berg)
 * Copyright (C) 2018 Intel Corporation
 */
#समावेश <linux/types.h>
#समावेश <net/cfg80211.h>
#समावेश "ieee80211_i.h"
#समावेश "sta_info.h"
#समावेश "driver-ops.h"

अटल पूर्णांक ieee80211_set_ringparam(काष्ठा net_device *dev,
				   काष्ठा ethtool_ringparam *rp)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(dev->ieee80211_ptr->wiphy);

	अगर (rp->rx_mini_pending != 0 || rp->rx_jumbo_pending != 0)
		वापस -EINVAL;

	वापस drv_set_ringparam(local, rp->tx_pending, rp->rx_pending);
पूर्ण

अटल व्योम ieee80211_get_ringparam(काष्ठा net_device *dev,
				    काष्ठा ethtool_ringparam *rp)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(dev->ieee80211_ptr->wiphy);

	स_रखो(rp, 0, माप(*rp));

	drv_get_ringparam(local, &rp->tx_pending, &rp->tx_max_pending,
			  &rp->rx_pending, &rp->rx_max_pending);
पूर्ण

अटल स्थिर अक्षर ieee80211_gstrings_sta_stats[][ETH_GSTRING_LEN] = अणु
	"rx_packets", "rx_bytes",
	"rx_duplicates", "rx_fragments", "rx_dropped",
	"tx_packets", "tx_bytes",
	"tx_filtered", "tx_retry_failed", "tx_retries",
	"sta_state", "txrate", "rxrate", "signal",
	"channel", "noise", "ch_time", "ch_time_busy",
	"ch_time_ext_busy", "ch_time_rx", "ch_time_tx"
पूर्ण;
#घोषणा STA_STATS_LEN	ARRAY_SIZE(ieee80211_gstrings_sta_stats)

अटल पूर्णांक ieee80211_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	पूर्णांक rv = 0;

	अगर (sset == ETH_SS_STATS)
		rv += STA_STATS_LEN;

	rv += drv_get_et_sset_count(sdata, sset);

	अगर (rv == 0)
		वापस -EOPNOTSUPP;
	वापस rv;
पूर्ण

अटल व्योम ieee80211_get_stats(काष्ठा net_device *dev,
				काष्ठा ethtool_stats *stats,
				u64 *data)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_channel *channel;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा station_info sinfo;
	काष्ठा survey_info survey;
	पूर्णांक i, q;
#घोषणा STA_STATS_SURVEY_LEN 7

	स_रखो(data, 0, माप(u64) * STA_STATS_LEN);

#घोषणा ADD_STA_STATS(sta)					\
	करो अणु							\
		data[i++] += sta->rx_stats.packets;		\
		data[i++] += sta->rx_stats.bytes;		\
		data[i++] += sta->rx_stats.num_duplicates;	\
		data[i++] += sta->rx_stats.fragments;		\
		data[i++] += sta->rx_stats.dropped;		\
								\
		data[i++] += sinfo.tx_packets;			\
		data[i++] += sinfo.tx_bytes;			\
		data[i++] += sta->status_stats.filtered;	\
		data[i++] += sta->status_stats.retry_failed;	\
		data[i++] += sta->status_stats.retry_count;	\
	पूर्ण जबतक (0)

	/* For Managed stations, find the single station based on BSSID
	 * and use that.  For पूर्णांकerface types, iterate through all available
	 * stations and add stats क्रम any station that is asचिन्हित to this
	 * network device.
	 */

	mutex_lock(&local->sta_mtx);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION) अणु
		sta = sta_info_get_bss(sdata, sdata->u.mgd.bssid);

		अगर (!(sta && !WARN_ON(sta->sdata->dev != dev)))
			जाओ करो_survey;

		स_रखो(&sinfo, 0, माप(sinfo));
		sta_set_sinfo(sta, &sinfo, false);

		i = 0;
		ADD_STA_STATS(sta);

		data[i++] = sta->sta_state;


		अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_TX_BITRATE))
			data[i] = 100000ULL *
				cfg80211_calculate_bitrate(&sinfo.txrate);
		i++;
		अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_RX_BITRATE))
			data[i] = 100000ULL *
				cfg80211_calculate_bitrate(&sinfo.rxrate);
		i++;

		अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_SIGNAL_AVG))
			data[i] = (u8)sinfo.संकेत_avg;
		i++;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(sta, &local->sta_list, list) अणु
			/* Make sure this station beदीर्घs to the proper dev */
			अगर (sta->sdata->dev != dev)
				जारी;

			स_रखो(&sinfo, 0, माप(sinfo));
			sta_set_sinfo(sta, &sinfo, false);
			i = 0;
			ADD_STA_STATS(sta);
		पूर्ण
	पूर्ण

करो_survey:
	i = STA_STATS_LEN - STA_STATS_SURVEY_LEN;
	/* Get survey stats क्रम current channel */
	survey.filled = 0;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (chanctx_conf)
		channel = chanctx_conf->def.chan;
	अन्यथा
		channel = शून्य;
	rcu_पढ़ो_unlock();

	अगर (channel) अणु
		q = 0;
		करो अणु
			survey.filled = 0;
			अगर (drv_get_survey(local, q, &survey) != 0) अणु
				survey.filled = 0;
				अवरोध;
			पूर्ण
			q++;
		पूर्ण जबतक (channel != survey.channel);
	पूर्ण

	अगर (survey.filled)
		data[i++] = survey.channel->center_freq;
	अन्यथा
		data[i++] = 0;
	अगर (survey.filled & SURVEY_INFO_NOISE_DBM)
		data[i++] = (u8)survey.noise;
	अन्यथा
		data[i++] = -1LL;
	अगर (survey.filled & SURVEY_INFO_TIME)
		data[i++] = survey.समय;
	अन्यथा
		data[i++] = -1LL;
	अगर (survey.filled & SURVEY_INFO_TIME_BUSY)
		data[i++] = survey.समय_busy;
	अन्यथा
		data[i++] = -1LL;
	अगर (survey.filled & SURVEY_INFO_TIME_EXT_BUSY)
		data[i++] = survey.समय_ext_busy;
	अन्यथा
		data[i++] = -1LL;
	अगर (survey.filled & SURVEY_INFO_TIME_RX)
		data[i++] = survey.समय_rx;
	अन्यथा
		data[i++] = -1LL;
	अगर (survey.filled & SURVEY_INFO_TIME_TX)
		data[i++] = survey.समय_प्रकारx;
	अन्यथा
		data[i++] = -1LL;

	mutex_unlock(&local->sta_mtx);

	अगर (WARN_ON(i != STA_STATS_LEN))
		वापस;

	drv_get_et_stats(sdata, stats, &(data[STA_STATS_LEN]));
पूर्ण

अटल व्योम ieee80211_get_strings(काष्ठा net_device *dev, u32 sset, u8 *data)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	पूर्णांक sz_sta_stats = 0;

	अगर (sset == ETH_SS_STATS) अणु
		sz_sta_stats = माप(ieee80211_gstrings_sta_stats);
		स_नकल(data, ieee80211_gstrings_sta_stats, sz_sta_stats);
	पूर्ण
	drv_get_et_strings(sdata, sset, &(data[sz_sta_stats]));
पूर्ण

अटल पूर्णांक ieee80211_get_regs_len(काष्ठा net_device *dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम ieee80211_get_regs(काष्ठा net_device *dev,
			       काष्ठा ethtool_regs *regs,
			       व्योम *data)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	regs->version = wdev->wiphy->hw_version;
	regs->len = 0;
पूर्ण

स्थिर काष्ठा ethtool_ops ieee80211_ethtool_ops = अणु
	.get_drvinfo = cfg80211_get_drvinfo,
	.get_regs_len = ieee80211_get_regs_len,
	.get_regs = ieee80211_get_regs,
	.get_link = ethtool_op_get_link,
	.get_ringparam = ieee80211_get_ringparam,
	.set_ringparam = ieee80211_set_ringparam,
	.get_strings = ieee80211_get_strings,
	.get_ethtool_stats = ieee80211_get_stats,
	.get_sset_count = ieee80211_get_sset_count,
पूर्ण;
