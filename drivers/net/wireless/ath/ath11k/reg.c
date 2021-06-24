<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause-Clear
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */
#समावेश "core.h"
#समावेश "debug.h"

/* World regकरोm to be used in हाल शेष regd from fw is unavailable */
#घोषणा ATH11K_2GHZ_CH01_11      REG_RULE(2412 - 10, 2462 + 10, 40, 0, 20, 0)
#घोषणा ATH11K_5GHZ_5150_5350    REG_RULE(5150 - 10, 5350 + 10, 80, 0, 30,\
					  NL80211_RRF_NO_IR)
#घोषणा ATH11K_5GHZ_5725_5850    REG_RULE(5725 - 10, 5850 + 10, 80, 0, 30,\
					  NL80211_RRF_NO_IR)

#घोषणा ETSI_WEATHER_RADAR_BAND_LOW		5590
#घोषणा ETSI_WEATHER_RADAR_BAND_HIGH		5650
#घोषणा ETSI_WEATHER_RADAR_BAND_CAC_TIMEOUT	600000

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य ath11k_world_regd = अणु
	.n_reg_rules = 3,
	.alpha2 =  "00",
	.reg_rules = अणु
		ATH11K_2GHZ_CH01_11,
		ATH11K_5GHZ_5150_5350,
		ATH11K_5GHZ_5725_5850,
	पूर्ण
पूर्ण;

अटल bool ath11k_regकरोm_changes(काष्ठा ath11k *ar, अक्षर *alpha2)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;

	regd = rcu_dereference_rtnl(ar->hw->wiphy->regd);
	/* This can happen during wiphy registration where the previous
	 * user request is received beक्रमe we update the regd received
	 * from firmware.
	 */
	अगर (!regd)
		वापस true;

	वापस स_भेद(regd->alpha2, alpha2, 2) != 0;
पूर्ण

अटल व्योम
ath11k_reg_notअगरier(काष्ठा wiphy *wiphy, काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा wmi_init_country_params init_country_param;
	काष्ठा ath11k *ar = hw->priv;
	पूर्णांक ret;

	ath11k_dbg(ar->ab, ATH11K_DBG_REG,
		   "Regulatory Notification received for %s\n", wiphy_name(wiphy));

	/* Currently supporting only General User Hपूर्णांकs. Cell base user
	 * hपूर्णांकs to be handled later.
	 * Hपूर्णांकs from other sources like Core, Beacons are not expected क्रम
	 * self managed wiphy's
	 */
	अगर (!(request->initiator == NL80211_REGDOM_SET_BY_USER &&
	      request->user_reg_hपूर्णांक_type == NL80211_USER_REG_HINT_USER)) अणु
		ath11k_warn(ar->ab, "Unexpected Regulatory event for this wiphy\n");
		वापस;
	पूर्ण

	अगर (!IS_ENABLED(CONFIG_ATH_REG_DYNAMIC_USER_REG_HINTS)) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_REG,
			   "Country Setting is not allowed\n");
		वापस;
	पूर्ण

	अगर (!ath11k_regकरोm_changes(ar, request->alpha2)) अणु
		ath11k_dbg(ar->ab, ATH11K_DBG_REG, "Country is already set\n");
		वापस;
	पूर्ण

	/* Set the country code to the firmware and रुको क्रम
	 * the WMI_REG_CHAN_LIST_CC EVENT क्रम updating the
	 * reg info
	 */
	init_country_param.flags = ALPHA_IS_SET;
	स_नकल(&init_country_param.cc_info.alpha2, request->alpha2, 2);
	init_country_param.cc_info.alpha2[2] = 0;

	ret = ath11k_wmi_send_init_country_cmd(ar, init_country_param);
	अगर (ret)
		ath11k_warn(ar->ab,
			    "INIT Country code set to fw failed : %d\n", ret);
पूर्ण

पूर्णांक ath11k_reg_update_chan_list(काष्ठा ath11k *ar)
अणु
	काष्ठा ieee80211_supported_band **bands;
	काष्ठा scan_chan_list_params *params;
	काष्ठा ieee80211_channel *channel;
	काष्ठा ieee80211_hw *hw = ar->hw;
	काष्ठा channel_param *ch;
	क्रमागत nl80211_band band;
	पूर्णांक num_channels = 0;
	पूर्णांक params_len;
	पूर्णांक i, ret;

	bands = hw->wiphy->bands;
	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!bands[band])
			जारी;

		क्रम (i = 0; i < bands[band]->n_channels; i++) अणु
			अगर (bands[band]->channels[i].flags &
			    IEEE80211_CHAN_DISABLED)
				जारी;

			num_channels++;
		पूर्ण
	पूर्ण

	अगर (WARN_ON(!num_channels))
		वापस -EINVAL;

	params_len = माप(काष्ठा scan_chan_list_params) +
			num_channels * माप(काष्ठा channel_param);
	params = kzalloc(params_len, GFP_KERNEL);

	अगर (!params)
		वापस -ENOMEM;

	params->pdev_id = ar->pdev->pdev_id;
	params->nallchans = num_channels;

	ch = params->ch_param;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!bands[band])
			जारी;

		क्रम (i = 0; i < bands[band]->n_channels; i++) अणु
			channel = &bands[band]->channels[i];

			अगर (channel->flags & IEEE80211_CHAN_DISABLED)
				जारी;

			/* TODO: Set to true/false based on some condition? */
			ch->allow_ht = true;
			ch->allow_vht = true;
			ch->allow_he = true;

			ch->dfs_set =
				!!(channel->flags & IEEE80211_CHAN_RADAR);
			ch->is_chan_passive = !!(channel->flags &
						IEEE80211_CHAN_NO_IR);
			ch->is_chan_passive |= ch->dfs_set;
			ch->mhz = channel->center_freq;
			ch->cfreq1 = channel->center_freq;
			ch->minघातer = 0;
			ch->maxघातer = channel->max_घातer * 2;
			ch->maxregघातer = channel->max_reg_घातer * 2;
			ch->antennamax = channel->max_antenna_gain * 2;

			/* TODO: Use appropriate phymodes */
			अगर (channel->band == NL80211_BAND_2GHZ)
				ch->phy_mode = MODE_11G;
			अन्यथा
				ch->phy_mode = MODE_11A;

			अगर (channel->band == NL80211_BAND_6GHZ &&
			    cfg80211_channel_is_psc(channel))
				ch->psc_channel = true;

			ath11k_dbg(ar->ab, ATH11K_DBG_WMI,
				   "mac channel [%d/%d] freq %d maxpower %d regpower %d antenna %d mode %d\n",
				   i, params->nallchans,
				   ch->mhz, ch->maxघातer, ch->maxregघातer,
				   ch->antennamax, ch->phy_mode);

			ch++;
			/* TODO: use quarrter/half rate, cfreq12, dfs_cfreq2
			 * set_agile, reg_class_idx
			 */
		पूर्ण
	पूर्ण

	ret = ath11k_wmi_send_scan_chan_list_cmd(ar, params);
	kमुक्त(params);

	वापस ret;
पूर्ण

अटल व्योम ath11k_copy_regd(काष्ठा ieee80211_regकरोमुख्य *regd_orig,
			     काष्ठा ieee80211_regकरोमुख्य *regd_copy)
अणु
	u8 i;

	/* The caller should have checked error conditions */
	स_नकल(regd_copy, regd_orig, माप(*regd_orig));

	क्रम (i = 0; i < regd_orig->n_reg_rules; i++)
		स_नकल(&regd_copy->reg_rules[i], &regd_orig->reg_rules[i],
		       माप(काष्ठा ieee80211_reg_rule));
पूर्ण

पूर्णांक ath11k_regd_update(काष्ठा ath11k *ar, bool init)
अणु
	काष्ठा ieee80211_regकरोमुख्य *regd, *regd_copy = शून्य;
	पूर्णांक ret, regd_len, pdev_id;
	काष्ठा ath11k_base *ab;

	ab = ar->ab;
	pdev_id = ar->pdev_idx;

	spin_lock_bh(&ab->base_lock);

	अगर (init) अणु
		/* Apply the regd received during init through
		 * WMI_REG_CHAN_LIST_CC event. In हाल of failure to
		 * receive the regd, initialize with a शेष world
		 * regulatory.
		 */
		अगर (ab->शेष_regd[pdev_id]) अणु
			regd = ab->शेष_regd[pdev_id];
		पूर्ण अन्यथा अणु
			ath11k_warn(ab,
				    "failed to receive default regd during init\n");
			regd = (काष्ठा ieee80211_regकरोमुख्य *)&ath11k_world_regd;
		पूर्ण
	पूर्ण अन्यथा अणु
		regd = ab->new_regd[pdev_id];
	पूर्ण

	अगर (!regd) अणु
		ret = -EINVAL;
		spin_unlock_bh(&ab->base_lock);
		जाओ err;
	पूर्ण

	regd_len = माप(*regd) + (regd->n_reg_rules *
		माप(काष्ठा ieee80211_reg_rule));

	regd_copy = kzalloc(regd_len, GFP_ATOMIC);
	अगर (regd_copy)
		ath11k_copy_regd(regd, regd_copy);

	spin_unlock_bh(&ab->base_lock);

	अगर (!regd_copy) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	rtnl_lock();
	wiphy_lock(ar->hw->wiphy);
	ret = regulatory_set_wiphy_regd_sync(ar->hw->wiphy, regd_copy);
	wiphy_unlock(ar->hw->wiphy);
	rtnl_unlock();

	kमुक्त(regd_copy);

	अगर (ret)
		जाओ err;

	अगर (ar->state == ATH11K_STATE_ON) अणु
		ret = ath11k_reg_update_chan_list(ar);
		अगर (ret)
			जाओ err;
	पूर्ण

	वापस 0;
err:
	ath11k_warn(ab, "failed to perform regd update : %d\n", ret);
	वापस ret;
पूर्ण

अटल क्रमागत nl80211_dfs_regions
ath11k_map_fw_dfs_region(क्रमागत ath11k_dfs_region dfs_region)
अणु
	चयन (dfs_region) अणु
	हाल ATH11K_DFS_REG_FCC:
	हाल ATH11K_DFS_REG_CN:
		वापस NL80211_DFS_FCC;
	हाल ATH11K_DFS_REG_ETSI:
	हाल ATH11K_DFS_REG_KR:
		वापस NL80211_DFS_ETSI;
	हाल ATH11K_DFS_REG_MKK:
	हाल ATH11K_DFS_REG_MKK_N:
		वापस NL80211_DFS_JP;
	शेष:
		वापस NL80211_DFS_UNSET;
	पूर्ण
पूर्ण

अटल u32 ath11k_map_fw_reg_flags(u16 reg_flags)
अणु
	u32 flags = 0;

	अगर (reg_flags & REGULATORY_CHAN_NO_IR)
		flags = NL80211_RRF_NO_IR;

	अगर (reg_flags & REGULATORY_CHAN_RADAR)
		flags |= NL80211_RRF_DFS;

	अगर (reg_flags & REGULATORY_CHAN_NO_OFDM)
		flags |= NL80211_RRF_NO_OFDM;

	अगर (reg_flags & REGULATORY_CHAN_INDOOR_ONLY)
		flags |= NL80211_RRF_NO_OUTDOOR;

	अगर (reg_flags & REGULATORY_CHAN_NO_HT40)
		flags |= NL80211_RRF_NO_HT40;

	अगर (reg_flags & REGULATORY_CHAN_NO_80MHZ)
		flags |= NL80211_RRF_NO_80MHZ;

	अगर (reg_flags & REGULATORY_CHAN_NO_160MHZ)
		flags |= NL80211_RRF_NO_160MHZ;

	वापस flags;
पूर्ण

अटल bool
ath11k_reg_can_पूर्णांकersect(काष्ठा ieee80211_reg_rule *rule1,
			 काष्ठा ieee80211_reg_rule *rule2)
अणु
	u32 start_freq1, end_freq1;
	u32 start_freq2, end_freq2;

	start_freq1 = rule1->freq_range.start_freq_khz;
	start_freq2 = rule2->freq_range.start_freq_khz;

	end_freq1 = rule1->freq_range.end_freq_khz;
	end_freq2 = rule2->freq_range.end_freq_khz;

	अगर ((start_freq1 >= start_freq2 &&
	     start_freq1 < end_freq2) ||
	    (start_freq2 > start_freq1 &&
	     start_freq2 < end_freq1))
		वापस true;

	/* TODO: Should we restrict पूर्णांकersection feasibility
	 *  based on min bandwidth of the पूर्णांकersected region also,
	 *  say the पूर्णांकersected rule should have a  min bandwidth
	 * of 20MHz?
	 */

	वापस false;
पूर्ण

अटल व्योम ath11k_reg_पूर्णांकersect_rules(काष्ठा ieee80211_reg_rule *rule1,
				       काष्ठा ieee80211_reg_rule *rule2,
				       काष्ठा ieee80211_reg_rule *new_rule)
अणु
	u32 start_freq1, end_freq1;
	u32 start_freq2, end_freq2;
	u32 freq_dअगरf, max_bw;

	start_freq1 = rule1->freq_range.start_freq_khz;
	start_freq2 = rule2->freq_range.start_freq_khz;

	end_freq1 = rule1->freq_range.end_freq_khz;
	end_freq2 = rule2->freq_range.end_freq_khz;

	new_rule->freq_range.start_freq_khz = max_t(u32, start_freq1,
						    start_freq2);
	new_rule->freq_range.end_freq_khz = min_t(u32, end_freq1, end_freq2);

	freq_dअगरf = new_rule->freq_range.end_freq_khz -
			new_rule->freq_range.start_freq_khz;
	max_bw = min_t(u32, rule1->freq_range.max_bandwidth_khz,
		       rule2->freq_range.max_bandwidth_khz);
	new_rule->freq_range.max_bandwidth_khz = min_t(u32, max_bw, freq_dअगरf);

	new_rule->घातer_rule.max_antenna_gain =
		min_t(u32, rule1->घातer_rule.max_antenna_gain,
		      rule2->घातer_rule.max_antenna_gain);

	new_rule->घातer_rule.max_eirp = min_t(u32, rule1->घातer_rule.max_eirp,
					      rule2->घातer_rule.max_eirp);

	/* Use the flags of both the rules */
	new_rule->flags = rule1->flags | rule2->flags;

	/* To be safe, lts use the max cac समयout of both rules */
	new_rule->dfs_cac_ms = max_t(u32, rule1->dfs_cac_ms,
				     rule2->dfs_cac_ms);
पूर्ण

अटल काष्ठा ieee80211_regकरोमुख्य *
ath11k_regd_पूर्णांकersect(काष्ठा ieee80211_regकरोमुख्य *शेष_regd,
		      काष्ठा ieee80211_regकरोमुख्य *curr_regd)
अणु
	u8 num_old_regd_rules, num_curr_regd_rules, num_new_regd_rules;
	काष्ठा ieee80211_reg_rule *old_rule, *curr_rule, *new_rule;
	काष्ठा ieee80211_regकरोमुख्य *new_regd = शून्य;
	u8 i, j, k;

	num_old_regd_rules = शेष_regd->n_reg_rules;
	num_curr_regd_rules = curr_regd->n_reg_rules;
	num_new_regd_rules = 0;

	/* Find the number of पूर्णांकersecting rules to allocate new regd memory */
	क्रम (i = 0; i < num_old_regd_rules; i++) अणु
		old_rule = शेष_regd->reg_rules + i;
		क्रम (j = 0; j < num_curr_regd_rules; j++) अणु
			curr_rule = curr_regd->reg_rules + j;

			अगर (ath11k_reg_can_पूर्णांकersect(old_rule, curr_rule))
				num_new_regd_rules++;
		पूर्ण
	पूर्ण

	अगर (!num_new_regd_rules)
		वापस शून्य;

	new_regd = kzalloc(माप(*new_regd) + (num_new_regd_rules *
			माप(काष्ठा ieee80211_reg_rule)),
			GFP_ATOMIC);

	अगर (!new_regd)
		वापस शून्य;

	/* We set the new country and dfs region directly and only trim
	 * the freq, घातer, antenna gain by पूर्णांकersecting with the
	 * शेष regकरोमुख्य. Also MAX of the dfs cac समयout is selected.
	 */
	new_regd->n_reg_rules = num_new_regd_rules;
	स_नकल(new_regd->alpha2, curr_regd->alpha2, माप(new_regd->alpha2));
	new_regd->dfs_region = curr_regd->dfs_region;
	new_rule = new_regd->reg_rules;

	क्रम (i = 0, k = 0; i < num_old_regd_rules; i++) अणु
		old_rule = शेष_regd->reg_rules + i;
		क्रम (j = 0; j < num_curr_regd_rules; j++) अणु
			curr_rule = curr_regd->reg_rules + j;

			अगर (ath11k_reg_can_पूर्णांकersect(old_rule, curr_rule))
				ath11k_reg_पूर्णांकersect_rules(old_rule, curr_rule,
							   (new_rule + k++));
		पूर्ण
	पूर्ण
	वापस new_regd;
पूर्ण

अटल स्थिर अक्षर *
ath11k_reg_get_regकरोm_str(क्रमागत nl80211_dfs_regions dfs_region)
अणु
	चयन (dfs_region) अणु
	हाल NL80211_DFS_FCC:
		वापस "FCC";
	हाल NL80211_DFS_ETSI:
		वापस "ETSI";
	हाल NL80211_DFS_JP:
		वापस "JP";
	शेष:
		वापस "UNSET";
	पूर्ण
पूर्ण

अटल u16
ath11k_reg_adjust_bw(u16 start_freq, u16 end_freq, u16 max_bw)
अणु
	u16 bw;

	bw = end_freq - start_freq;
	bw = min_t(u16, bw, max_bw);

	अगर (bw >= 80 && bw < 160)
		bw = 80;
	अन्यथा अगर (bw >= 40 && bw < 80)
		bw = 40;
	अन्यथा अगर (bw < 40)
		bw = 20;

	वापस bw;
पूर्ण

अटल व्योम
ath11k_reg_update_rule(काष्ठा ieee80211_reg_rule *reg_rule, u32 start_freq,
		       u32 end_freq, u32 bw, u32 ant_gain, u32 reg_pwr,
		       u32 reg_flags)
अणु
	reg_rule->freq_range.start_freq_khz = MHZ_TO_KHZ(start_freq);
	reg_rule->freq_range.end_freq_khz = MHZ_TO_KHZ(end_freq);
	reg_rule->freq_range.max_bandwidth_khz = MHZ_TO_KHZ(bw);
	reg_rule->घातer_rule.max_antenna_gain = DBI_TO_MBI(ant_gain);
	reg_rule->घातer_rule.max_eirp = DBM_TO_MBM(reg_pwr);
	reg_rule->flags = reg_flags;
पूर्ण

अटल व्योम
ath11k_reg_update_weather_radar_band(काष्ठा ath11k_base *ab,
				     काष्ठा ieee80211_regकरोमुख्य *regd,
				     काष्ठा cur_reg_rule *reg_rule,
				     u8 *rule_idx, u32 flags, u16 max_bw)
अणु
	u32 end_freq;
	u16 bw;
	u8 i;

	i = *rule_idx;

	bw = ath11k_reg_adjust_bw(reg_rule->start_freq,
				  ETSI_WEATHER_RADAR_BAND_LOW, max_bw);

	ath11k_reg_update_rule(regd->reg_rules + i, reg_rule->start_freq,
			       ETSI_WEATHER_RADAR_BAND_LOW, bw,
			       reg_rule->ant_gain, reg_rule->reg_घातer,
			       flags);

	ath11k_dbg(ab, ATH11K_DBG_REG,
		   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FLAGS %d)\n",
		   i + 1, reg_rule->start_freq, ETSI_WEATHER_RADAR_BAND_LOW,
		   bw, reg_rule->ant_gain, reg_rule->reg_घातer,
		   regd->reg_rules[i].dfs_cac_ms,
		   flags);

	अगर (reg_rule->end_freq > ETSI_WEATHER_RADAR_BAND_HIGH)
		end_freq = ETSI_WEATHER_RADAR_BAND_HIGH;
	अन्यथा
		end_freq = reg_rule->end_freq;

	bw = ath11k_reg_adjust_bw(ETSI_WEATHER_RADAR_BAND_LOW, end_freq,
				  max_bw);

	i++;

	ath11k_reg_update_rule(regd->reg_rules + i,
			       ETSI_WEATHER_RADAR_BAND_LOW, end_freq, bw,
			       reg_rule->ant_gain, reg_rule->reg_घातer,
			       flags);

	regd->reg_rules[i].dfs_cac_ms = ETSI_WEATHER_RADAR_BAND_CAC_TIMEOUT;

	ath11k_dbg(ab, ATH11K_DBG_REG,
		   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FLAGS %d)\n",
		   i + 1, ETSI_WEATHER_RADAR_BAND_LOW, end_freq,
		   bw, reg_rule->ant_gain, reg_rule->reg_घातer,
		   regd->reg_rules[i].dfs_cac_ms,
		   flags);

	अगर (end_freq == reg_rule->end_freq) अणु
		regd->n_reg_rules--;
		*rule_idx = i;
		वापस;
	पूर्ण

	bw = ath11k_reg_adjust_bw(ETSI_WEATHER_RADAR_BAND_HIGH,
				  reg_rule->end_freq, max_bw);

	i++;

	ath11k_reg_update_rule(regd->reg_rules + i, ETSI_WEATHER_RADAR_BAND_HIGH,
			       reg_rule->end_freq, bw,
			       reg_rule->ant_gain, reg_rule->reg_घातer,
			       flags);

	ath11k_dbg(ab, ATH11K_DBG_REG,
		   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FLAGS %d)\n",
		   i + 1, ETSI_WEATHER_RADAR_BAND_HIGH, reg_rule->end_freq,
		   bw, reg_rule->ant_gain, reg_rule->reg_घातer,
		   regd->reg_rules[i].dfs_cac_ms,
		   flags);

	*rule_idx = i;
पूर्ण

काष्ठा ieee80211_regकरोमुख्य *
ath11k_reg_build_regd(काष्ठा ath11k_base *ab,
		      काष्ठा cur_regulatory_info *reg_info, bool पूर्णांकersect)
अणु
	काष्ठा ieee80211_regकरोमुख्य *पंचांगp_regd, *शेष_regd, *new_regd = शून्य;
	काष्ठा cur_reg_rule *reg_rule;
	u8 i = 0, j = 0;
	u8 num_rules;
	u16 max_bw;
	u32 flags;
	अक्षर alpha2[3];

	num_rules = reg_info->num_5g_reg_rules + reg_info->num_2g_reg_rules;

	अगर (!num_rules)
		जाओ ret;

	/* Add max additional rules to accommodate weather radar band */
	अगर (reg_info->dfs_region == ATH11K_DFS_REG_ETSI)
		num_rules += 2;

	पंचांगp_regd =  kzalloc(माप(*पंचांगp_regd) +
			(num_rules * माप(काष्ठा ieee80211_reg_rule)),
			GFP_ATOMIC);
	अगर (!पंचांगp_regd)
		जाओ ret;

	स_नकल(पंचांगp_regd->alpha2, reg_info->alpha2, REG_ALPHA2_LEN + 1);
	स_नकल(alpha2, reg_info->alpha2, REG_ALPHA2_LEN + 1);
	alpha2[2] = '\0';
	पंचांगp_regd->dfs_region = ath11k_map_fw_dfs_region(reg_info->dfs_region);

	ath11k_dbg(ab, ATH11K_DBG_REG,
		   "\r\nCountry %s, CFG Regdomain %s FW Regdomain %d, num_reg_rules %d\n",
		   alpha2, ath11k_reg_get_regकरोm_str(पंचांगp_regd->dfs_region),
		   reg_info->dfs_region, num_rules);
	/* Update reg_rules[] below. Firmware is expected to
	 * send these rules in order(2G rules first and then 5G)
	 */
	क्रम (; i < num_rules; i++) अणु
		अगर (reg_info->num_2g_reg_rules &&
		    (i < reg_info->num_2g_reg_rules)) अणु
			reg_rule = reg_info->reg_rules_2g_ptr + i;
			max_bw = min_t(u16, reg_rule->max_bw,
				       reg_info->max_bw_2g);
			flags = 0;
		पूर्ण अन्यथा अगर (reg_info->num_5g_reg_rules &&
			   (j < reg_info->num_5g_reg_rules)) अणु
			reg_rule = reg_info->reg_rules_5g_ptr + j++;
			max_bw = min_t(u16, reg_rule->max_bw,
				       reg_info->max_bw_5g);

			/* FW करोesn't pass NL80211_RRF_AUTO_BW flag क्रम
			 * BW Auto correction, we can enable this by शेष
			 * क्रम all 5G rules here. The regulatory core perक्रमms
			 * BW correction अगर required and applies flags as
			 * per other BW rule flags we pass from here
			 */
			flags = NL80211_RRF_AUTO_BW;
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण

		flags |= ath11k_map_fw_reg_flags(reg_rule->flags);

		ath11k_reg_update_rule(पंचांगp_regd->reg_rules + i,
				       reg_rule->start_freq,
				       reg_rule->end_freq, max_bw,
				       reg_rule->ant_gain, reg_rule->reg_घातer,
				       flags);

		/* Update dfs cac समयout अगर the dfs करोमुख्य is ETSI and the
		 * new rule covers weather radar band.
		 * Default value of '0' corresponds to 60s समयout, so no
		 * need to update that क्रम other rules.
		 */
		अगर (flags & NL80211_RRF_DFS &&
		    reg_info->dfs_region == ATH11K_DFS_REG_ETSI &&
		    (reg_rule->end_freq > ETSI_WEATHER_RADAR_BAND_LOW &&
		    reg_rule->start_freq < ETSI_WEATHER_RADAR_BAND_HIGH))अणु
			ath11k_reg_update_weather_radar_band(ab, पंचांगp_regd,
							     reg_rule, &i,
							     flags, max_bw);
			जारी;
		पूर्ण

		ath11k_dbg(ab, ATH11K_DBG_REG,
			   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FLAGS %d)\n",
			   i + 1, reg_rule->start_freq, reg_rule->end_freq,
			   max_bw, reg_rule->ant_gain, reg_rule->reg_घातer,
			   पंचांगp_regd->reg_rules[i].dfs_cac_ms,
			   flags);
	पूर्ण

	पंचांगp_regd->n_reg_rules = i;

	अगर (पूर्णांकersect) अणु
		शेष_regd = ab->शेष_regd[reg_info->phy_id];

		/* Get a new regd by पूर्णांकersecting the received regd with
		 * our शेष regd.
		 */
		new_regd = ath11k_regd_पूर्णांकersect(शेष_regd, पंचांगp_regd);
		kमुक्त(पंचांगp_regd);
		अगर (!new_regd) अणु
			ath11k_warn(ab, "Unable to create intersected regdomain\n");
			जाओ ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		new_regd = पंचांगp_regd;
	पूर्ण

ret:
	वापस new_regd;
पूर्ण

व्योम ath11k_regd_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath11k *ar = container_of(work, काष्ठा ath11k,
					 regd_update_work);
	पूर्णांक ret;

	ret = ath11k_regd_update(ar, false);
	अगर (ret) अणु
		/* Firmware has alपढ़ोy moved to the new regd. We need
		 * to मुख्यtain channel consistency across FW, Host driver
		 * and userspace. Hence as a fallback mechanism we can set
		 * the prev or शेष country code to the firmware.
		 */
		/* TODO: Implement Fallback Mechanism */
	पूर्ण
पूर्ण

व्योम ath11k_reg_init(काष्ठा ath11k *ar)
अणु
	ar->hw->wiphy->regulatory_flags = REGULATORY_WIPHY_SELF_MANAGED;
	ar->hw->wiphy->reg_notअगरier = ath11k_reg_notअगरier;
पूर्ण

व्योम ath11k_reg_मुक्त(काष्ठा ath11k_base *ab)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ab->hw_params.max_radios; i++) अणु
		kमुक्त(ab->शेष_regd[i]);
		kमुक्त(ab->new_regd[i]);
	पूर्ण
पूर्ण
