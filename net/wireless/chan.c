<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains helper code to handle channel
 * settings and keeping track of what is possible at
 * any poपूर्णांक in समय.
 *
 * Copyright 2009	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright 2018-2020	Intel Corporation
 */

#समावेश <linux/export.h>
#समावेश <linux/bitfield.h>
#समावेश <net/cfg80211.h>
#समावेश "core.h"
#समावेश "rdev-ops.h"

अटल bool cfg80211_valid_60g_freq(u32 freq)
अणु
	वापस freq >= 58320 && freq <= 70200;
पूर्ण

व्योम cfg80211_chandef_create(काष्ठा cfg80211_chan_def *chandef,
			     काष्ठा ieee80211_channel *chan,
			     क्रमागत nl80211_channel_type chan_type)
अणु
	अगर (WARN_ON(!chan))
		वापस;

	chandef->chan = chan;
	chandef->freq1_offset = chan->freq_offset;
	chandef->center_freq2 = 0;
	chandef->edmg.bw_config = 0;
	chandef->edmg.channels = 0;

	चयन (chan_type) अणु
	हाल NL80211_CHAN_NO_HT:
		chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
		chandef->center_freq1 = chan->center_freq;
		अवरोध;
	हाल NL80211_CHAN_HT20:
		chandef->width = NL80211_CHAN_WIDTH_20;
		chandef->center_freq1 = chan->center_freq;
		अवरोध;
	हाल NL80211_CHAN_HT40PLUS:
		chandef->width = NL80211_CHAN_WIDTH_40;
		chandef->center_freq1 = chan->center_freq + 10;
		अवरोध;
	हाल NL80211_CHAN_HT40MINUS:
		chandef->width = NL80211_CHAN_WIDTH_40;
		chandef->center_freq1 = chan->center_freq - 10;
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(cfg80211_chandef_create);

अटल bool cfg80211_edmg_chandef_valid(स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक max_contiguous = 0;
	पूर्णांक num_of_enabled = 0;
	पूर्णांक contiguous = 0;
	पूर्णांक i;

	अगर (!chandef->edmg.channels || !chandef->edmg.bw_config)
		वापस false;

	अगर (!cfg80211_valid_60g_freq(chandef->chan->center_freq))
		वापस false;

	क्रम (i = 0; i < 6; i++) अणु
		अगर (chandef->edmg.channels & BIT(i)) अणु
			contiguous++;
			num_of_enabled++;
		पूर्ण अन्यथा अणु
			contiguous = 0;
		पूर्ण

		max_contiguous = max(contiguous, max_contiguous);
	पूर्ण
	/* basic verअगरication of edmg configuration according to
	 * IEEE P802.11ay/D4.0 section 9.4.2.251
	 */
	/* check bw_config against contiguous edmg channels */
	चयन (chandef->edmg.bw_config) अणु
	हाल IEEE80211_EDMG_BW_CONFIG_4:
	हाल IEEE80211_EDMG_BW_CONFIG_8:
	हाल IEEE80211_EDMG_BW_CONFIG_12:
		अगर (max_contiguous < 1)
			वापस false;
		अवरोध;
	हाल IEEE80211_EDMG_BW_CONFIG_5:
	हाल IEEE80211_EDMG_BW_CONFIG_9:
	हाल IEEE80211_EDMG_BW_CONFIG_13:
		अगर (max_contiguous < 2)
			वापस false;
		अवरोध;
	हाल IEEE80211_EDMG_BW_CONFIG_6:
	हाल IEEE80211_EDMG_BW_CONFIG_10:
	हाल IEEE80211_EDMG_BW_CONFIG_14:
		अगर (max_contiguous < 3)
			वापस false;
		अवरोध;
	हाल IEEE80211_EDMG_BW_CONFIG_7:
	हाल IEEE80211_EDMG_BW_CONFIG_11:
	हाल IEEE80211_EDMG_BW_CONFIG_15:
		अगर (max_contiguous < 4)
			वापस false;
		अवरोध;

	शेष:
		वापस false;
	पूर्ण

	/* check bw_config against aggregated (non contiguous) edmg channels */
	चयन (chandef->edmg.bw_config) अणु
	हाल IEEE80211_EDMG_BW_CONFIG_4:
	हाल IEEE80211_EDMG_BW_CONFIG_5:
	हाल IEEE80211_EDMG_BW_CONFIG_6:
	हाल IEEE80211_EDMG_BW_CONFIG_7:
		अवरोध;
	हाल IEEE80211_EDMG_BW_CONFIG_8:
	हाल IEEE80211_EDMG_BW_CONFIG_9:
	हाल IEEE80211_EDMG_BW_CONFIG_10:
	हाल IEEE80211_EDMG_BW_CONFIG_11:
		अगर (num_of_enabled < 2)
			वापस false;
		अवरोध;
	हाल IEEE80211_EDMG_BW_CONFIG_12:
	हाल IEEE80211_EDMG_BW_CONFIG_13:
	हाल IEEE80211_EDMG_BW_CONFIG_14:
	हाल IEEE80211_EDMG_BW_CONFIG_15:
		अगर (num_of_enabled < 4 || max_contiguous < 2)
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक nl80211_chan_width_to_mhz(क्रमागत nl80211_chan_width chan_width)
अणु
	पूर्णांक mhz;

	चयन (chan_width) अणु
	हाल NL80211_CHAN_WIDTH_1:
		mhz = 1;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_2:
		mhz = 2;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_4:
		mhz = 4;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_8:
		mhz = 8;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_16:
		mhz = 16;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_5:
		mhz = 5;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
		mhz = 10;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		mhz = 20;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		mhz = 40;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_80:
		mhz = 80;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		mhz = 160;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -1;
	पूर्ण
	वापस mhz;
पूर्ण

अटल पूर्णांक cfg80211_chandef_get_width(स्थिर काष्ठा cfg80211_chan_def *c)
अणु
	वापस nl80211_chan_width_to_mhz(c->width);
पूर्ण

bool cfg80211_chandef_valid(स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	u32 control_freq, oper_freq;
	पूर्णांक oper_width, control_width;

	अगर (!chandef->chan)
		वापस false;

	अगर (chandef->freq1_offset >= 1000)
		वापस false;

	control_freq = chandef->chan->center_freq;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		अगर (ieee80211_chandef_to_khz(chandef) !=
		    ieee80211_channel_to_khz(chandef->chan))
			वापस false;
		अगर (chandef->center_freq2)
			वापस false;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_1:
	हाल NL80211_CHAN_WIDTH_2:
	हाल NL80211_CHAN_WIDTH_4:
	हाल NL80211_CHAN_WIDTH_8:
	हाल NL80211_CHAN_WIDTH_16:
		अगर (chandef->chan->band != NL80211_BAND_S1GHZ)
			वापस false;

		control_freq = ieee80211_channel_to_khz(chandef->chan);
		oper_freq = ieee80211_chandef_to_khz(chandef);
		control_width = nl80211_chan_width_to_mhz(
					ieee80211_s1g_channel_width(
								chandef->chan));
		oper_width = cfg80211_chandef_get_width(chandef);

		अगर (oper_width < 0 || control_width < 0)
			वापस false;
		अगर (chandef->center_freq2)
			वापस false;

		अगर (control_freq + MHZ_TO_KHZ(control_width) / 2 >
		    oper_freq + MHZ_TO_KHZ(oper_width) / 2)
			वापस false;

		अगर (control_freq - MHZ_TO_KHZ(control_width) / 2 <
		    oper_freq - MHZ_TO_KHZ(oper_width) / 2)
			वापस false;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		अगर (chandef->center_freq1 != control_freq + 10 &&
		    chandef->center_freq1 != control_freq - 10)
			वापस false;
		अगर (chandef->center_freq2)
			वापस false;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		अगर (chandef->center_freq1 != control_freq + 30 &&
		    chandef->center_freq1 != control_freq + 10 &&
		    chandef->center_freq1 != control_freq - 10 &&
		    chandef->center_freq1 != control_freq - 30)
			वापस false;
		अगर (!chandef->center_freq2)
			वापस false;
		/* adjacent is not allowed -- that's a 160 MHz channel */
		अगर (chandef->center_freq1 - chandef->center_freq2 == 80 ||
		    chandef->center_freq2 - chandef->center_freq1 == 80)
			वापस false;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
		अगर (chandef->center_freq1 != control_freq + 30 &&
		    chandef->center_freq1 != control_freq + 10 &&
		    chandef->center_freq1 != control_freq - 10 &&
		    chandef->center_freq1 != control_freq - 30)
			वापस false;
		अगर (chandef->center_freq2)
			वापस false;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		अगर (chandef->center_freq1 != control_freq + 70 &&
		    chandef->center_freq1 != control_freq + 50 &&
		    chandef->center_freq1 != control_freq + 30 &&
		    chandef->center_freq1 != control_freq + 10 &&
		    chandef->center_freq1 != control_freq - 10 &&
		    chandef->center_freq1 != control_freq - 30 &&
		    chandef->center_freq1 != control_freq - 50 &&
		    chandef->center_freq1 != control_freq - 70)
			वापस false;
		अगर (chandef->center_freq2)
			वापस false;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	/* channel 14 is only क्रम IEEE 802.11b */
	अगर (chandef->center_freq1 == 2484 &&
	    chandef->width != NL80211_CHAN_WIDTH_20_NOHT)
		वापस false;

	अगर (cfg80211_chandef_is_edmg(chandef) &&
	    !cfg80211_edmg_chandef_valid(chandef))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(cfg80211_chandef_valid);

अटल व्योम chandef_primary_freqs(स्थिर काष्ठा cfg80211_chan_def *c,
				  u32 *pri40, u32 *pri80)
अणु
	पूर्णांक पंचांगp;

	चयन (c->width) अणु
	हाल NL80211_CHAN_WIDTH_40:
		*pri40 = c->center_freq1;
		*pri80 = 0;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_80P80:
		*pri80 = c->center_freq1;
		/* n_P20 */
		पंचांगp = (30 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P40 */
		पंचांगp /= 2;
		/* freq_P40 */
		*pri40 = c->center_freq1 - 20 + 40 * पंचांगp;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		/* n_P20 */
		पंचांगp = (70 + c->chan->center_freq - c->center_freq1)/20;
		/* n_P40 */
		पंचांगp /= 2;
		/* freq_P40 */
		*pri40 = c->center_freq1 - 60 + 40 * पंचांगp;
		/* n_P80 */
		पंचांगp /= 2;
		*pri80 = c->center_freq1 - 40 + 80 * पंचांगp;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

स्थिर काष्ठा cfg80211_chan_def *
cfg80211_chandef_compatible(स्थिर काष्ठा cfg80211_chan_def *c1,
			    स्थिर काष्ठा cfg80211_chan_def *c2)
अणु
	u32 c1_pri40, c1_pri80, c2_pri40, c2_pri80;

	/* If they are identical, वापस */
	अगर (cfg80211_chandef_identical(c1, c2))
		वापस c1;

	/* otherwise, must have same control channel */
	अगर (c1->chan != c2->chan)
		वापस शून्य;

	/*
	 * If they have the same width, but aren't identical,
	 * then they can't be compatible.
	 */
	अगर (c1->width == c2->width)
		वापस शून्य;

	/*
	 * can't be compatible अगर one of them is 5 or 10 MHz,
	 * but they करोn't have the same width.
	 */
	अगर (c1->width == NL80211_CHAN_WIDTH_5 ||
	    c1->width == NL80211_CHAN_WIDTH_10 ||
	    c2->width == NL80211_CHAN_WIDTH_5 ||
	    c2->width == NL80211_CHAN_WIDTH_10)
		वापस शून्य;

	अगर (c1->width == NL80211_CHAN_WIDTH_20_NOHT ||
	    c1->width == NL80211_CHAN_WIDTH_20)
		वापस c2;

	अगर (c2->width == NL80211_CHAN_WIDTH_20_NOHT ||
	    c2->width == NL80211_CHAN_WIDTH_20)
		वापस c1;

	chandef_primary_freqs(c1, &c1_pri40, &c1_pri80);
	chandef_primary_freqs(c2, &c2_pri40, &c2_pri80);

	अगर (c1_pri40 != c2_pri40)
		वापस शून्य;

	WARN_ON(!c1_pri80 && !c2_pri80);
	अगर (c1_pri80 && c2_pri80 && c1_pri80 != c2_pri80)
		वापस शून्य;

	अगर (c1->width > c2->width)
		वापस c1;
	वापस c2;
पूर्ण
EXPORT_SYMBOL(cfg80211_chandef_compatible);

अटल व्योम cfg80211_set_chans_dfs_state(काष्ठा wiphy *wiphy, u32 center_freq,
					 u32 bandwidth,
					 क्रमागत nl80211_dfs_state dfs_state)
अणु
	काष्ठा ieee80211_channel *c;
	u32 freq;

	क्रम (freq = center_freq - bandwidth/2 + 10;
	     freq <= center_freq + bandwidth/2 - 10;
	     freq += 20) अणु
		c = ieee80211_get_channel(wiphy, freq);
		अगर (!c || !(c->flags & IEEE80211_CHAN_RADAR))
			जारी;

		c->dfs_state = dfs_state;
		c->dfs_state_entered = jअगरfies;
	पूर्ण
पूर्ण

व्योम cfg80211_set_dfs_state(काष्ठा wiphy *wiphy,
			    स्थिर काष्ठा cfg80211_chan_def *chandef,
			    क्रमागत nl80211_dfs_state dfs_state)
अणु
	पूर्णांक width;

	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस;

	width = cfg80211_chandef_get_width(chandef);
	अगर (width < 0)
		वापस;

	cfg80211_set_chans_dfs_state(wiphy, chandef->center_freq1,
				     width, dfs_state);

	अगर (!chandef->center_freq2)
		वापस;
	cfg80211_set_chans_dfs_state(wiphy, chandef->center_freq2,
				     width, dfs_state);
पूर्ण

अटल u32 cfg80211_get_start_freq(u32 center_freq,
				   u32 bandwidth)
अणु
	u32 start_freq;

	bandwidth = MHZ_TO_KHZ(bandwidth);
	अगर (bandwidth <= MHZ_TO_KHZ(20))
		start_freq = center_freq;
	अन्यथा
		start_freq = center_freq - bandwidth / 2 + MHZ_TO_KHZ(10);

	वापस start_freq;
पूर्ण

अटल u32 cfg80211_get_end_freq(u32 center_freq,
				 u32 bandwidth)
अणु
	u32 end_freq;

	bandwidth = MHZ_TO_KHZ(bandwidth);
	अगर (bandwidth <= MHZ_TO_KHZ(20))
		end_freq = center_freq;
	अन्यथा
		end_freq = center_freq + bandwidth / 2 - MHZ_TO_KHZ(10);

	वापस end_freq;
पूर्ण

अटल पूर्णांक cfg80211_get_chans_dfs_required(काष्ठा wiphy *wiphy,
					    u32 center_freq,
					    u32 bandwidth)
अणु
	काष्ठा ieee80211_channel *c;
	u32 freq, start_freq, end_freq;

	start_freq = cfg80211_get_start_freq(center_freq, bandwidth);
	end_freq = cfg80211_get_end_freq(center_freq, bandwidth);

	क्रम (freq = start_freq; freq <= end_freq; freq += MHZ_TO_KHZ(20)) अणु
		c = ieee80211_get_channel_khz(wiphy, freq);
		अगर (!c)
			वापस -EINVAL;

		अगर (c->flags & IEEE80211_CHAN_RADAR)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक cfg80211_chandef_dfs_required(काष्ठा wiphy *wiphy,
				  स्थिर काष्ठा cfg80211_chan_def *chandef,
				  क्रमागत nl80211_अगरtype अगरtype)
अणु
	पूर्णांक width;
	पूर्णांक ret;

	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस -EINVAL;

	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_MESH_POINT:
		width = cfg80211_chandef_get_width(chandef);
		अगर (width < 0)
			वापस -EINVAL;

		ret = cfg80211_get_chans_dfs_required(wiphy,
					ieee80211_chandef_to_khz(chandef),
					width);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret > 0)
			वापस BIT(chandef->width);

		अगर (!chandef->center_freq2)
			वापस 0;

		ret = cfg80211_get_chans_dfs_required(wiphy,
					MHZ_TO_KHZ(chandef->center_freq2),
					width);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret > 0)
			वापस BIT(chandef->width);

		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_OCB:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_न_अंक:
		अवरोध;
	हाल NL80211_IFTYPE_WDS:
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NUM_NL80211_IFTYPES:
		WARN_ON(1);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfg80211_chandef_dfs_required);

अटल पूर्णांक cfg80211_get_chans_dfs_usable(काष्ठा wiphy *wiphy,
					 u32 center_freq,
					 u32 bandwidth)
अणु
	काष्ठा ieee80211_channel *c;
	u32 freq, start_freq, end_freq;
	पूर्णांक count = 0;

	start_freq = cfg80211_get_start_freq(center_freq, bandwidth);
	end_freq = cfg80211_get_end_freq(center_freq, bandwidth);

	/*
	 * Check entire range of channels क्रम the bandwidth.
	 * Check all channels are DFS channels (DFS_USABLE or
	 * DFS_AVAILABLE). Return number of usable channels
	 * (require CAC). Allow DFS and non-DFS channel mix.
	 */
	क्रम (freq = start_freq; freq <= end_freq; freq += MHZ_TO_KHZ(20)) अणु
		c = ieee80211_get_channel_khz(wiphy, freq);
		अगर (!c)
			वापस -EINVAL;

		अगर (c->flags & IEEE80211_CHAN_DISABLED)
			वापस -EINVAL;

		अगर (c->flags & IEEE80211_CHAN_RADAR) अणु
			अगर (c->dfs_state == NL80211_DFS_UNAVAILABLE)
				वापस -EINVAL;

			अगर (c->dfs_state == NL80211_DFS_USABLE)
				count++;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

bool cfg80211_chandef_dfs_usable(काष्ठा wiphy *wiphy,
				 स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक width;
	पूर्णांक r1, r2 = 0;

	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस false;

	width = cfg80211_chandef_get_width(chandef);
	अगर (width < 0)
		वापस false;

	r1 = cfg80211_get_chans_dfs_usable(wiphy,
					   MHZ_TO_KHZ(chandef->center_freq1),
					   width);

	अगर (r1 < 0)
		वापस false;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_80P80:
		WARN_ON(!chandef->center_freq2);
		r2 = cfg80211_get_chans_dfs_usable(wiphy,
					MHZ_TO_KHZ(chandef->center_freq2),
					width);
		अगर (r2 < 0)
			वापस false;
		अवरोध;
	शेष:
		WARN_ON(chandef->center_freq2);
		अवरोध;
	पूर्ण

	वापस (r1 + r2 > 0);
पूर्ण

/*
 * Checks अगर center frequency of chan falls with in the bandwidth
 * range of chandef.
 */
bool cfg80211_is_sub_chan(काष्ठा cfg80211_chan_def *chandef,
			  काष्ठा ieee80211_channel *chan)
अणु
	पूर्णांक width;
	u32 freq;

	अगर (chandef->chan->center_freq == chan->center_freq)
		वापस true;

	width = cfg80211_chandef_get_width(chandef);
	अगर (width <= 20)
		वापस false;

	क्रम (freq = chandef->center_freq1 - width / 2 + 10;
	     freq <= chandef->center_freq1 + width / 2 - 10; freq += 20) अणु
		अगर (chan->center_freq == freq)
			वापस true;
	पूर्ण

	अगर (!chandef->center_freq2)
		वापस false;

	क्रम (freq = chandef->center_freq2 - width / 2 + 10;
	     freq <= chandef->center_freq2 + width / 2 - 10; freq += 20) अणु
		अगर (chan->center_freq == freq)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool cfg80211_beaconing_अगरace_active(काष्ठा wireless_dev *wdev)
अणु
	bool active = false;

	ASSERT_WDEV_LOCK(wdev);

	अगर (!wdev->chandef.chan)
		वापस false;

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		active = wdev->beacon_पूर्णांकerval != 0;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		active = wdev->ssid_len != 0;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		active = wdev->mesh_id_len != 0;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_OCB:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	/* Can न_अंक type be considered as beaconing पूर्णांकerface? */
	हाल NL80211_IFTYPE_न_अंक:
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_WDS:
	हाल NUM_NL80211_IFTYPES:
		WARN_ON(1);
	पूर्ण

	वापस active;
पूर्ण

अटल bool cfg80211_is_wiphy_oper_chan(काष्ठा wiphy *wiphy,
					काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा wireless_dev *wdev;

	list_क्रम_each_entry(wdev, &wiphy->wdev_list, list) अणु
		wdev_lock(wdev);
		अगर (!cfg80211_beaconing_अगरace_active(wdev)) अणु
			wdev_unlock(wdev);
			जारी;
		पूर्ण

		अगर (cfg80211_is_sub_chan(&wdev->chandef, chan)) अणु
			wdev_unlock(wdev);
			वापस true;
		पूर्ण
		wdev_unlock(wdev);
	पूर्ण

	वापस false;
पूर्ण

bool cfg80211_any_wiphy_oper_chan(काष्ठा wiphy *wiphy,
				  काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	ASSERT_RTNL();

	अगर (!(chan->flags & IEEE80211_CHAN_RADAR))
		वापस false;

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (!reg_dfs_करोमुख्य_same(wiphy, &rdev->wiphy))
			जारी;

		अगर (cfg80211_is_wiphy_oper_chan(&rdev->wiphy, chan))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool cfg80211_get_chans_dfs_available(काष्ठा wiphy *wiphy,
					     u32 center_freq,
					     u32 bandwidth)
अणु
	काष्ठा ieee80211_channel *c;
	u32 freq, start_freq, end_freq;
	bool dfs_offload;

	dfs_offload = wiphy_ext_feature_isset(wiphy,
					      NL80211_EXT_FEATURE_DFS_OFFLOAD);

	start_freq = cfg80211_get_start_freq(center_freq, bandwidth);
	end_freq = cfg80211_get_end_freq(center_freq, bandwidth);

	/*
	 * Check entire range of channels क्रम the bandwidth.
	 * If any channel in between is disabled or has not
	 * had gone through CAC वापस false
	 */
	क्रम (freq = start_freq; freq <= end_freq; freq += MHZ_TO_KHZ(20)) अणु
		c = ieee80211_get_channel_khz(wiphy, freq);
		अगर (!c)
			वापस false;

		अगर (c->flags & IEEE80211_CHAN_DISABLED)
			वापस false;

		अगर ((c->flags & IEEE80211_CHAN_RADAR) &&
		    (c->dfs_state != NL80211_DFS_AVAILABLE) &&
		    !(c->dfs_state == NL80211_DFS_USABLE && dfs_offload))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool cfg80211_chandef_dfs_available(काष्ठा wiphy *wiphy,
				स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक width;
	पूर्णांक r;

	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस false;

	width = cfg80211_chandef_get_width(chandef);
	अगर (width < 0)
		वापस false;

	r = cfg80211_get_chans_dfs_available(wiphy,
					     MHZ_TO_KHZ(chandef->center_freq1),
					     width);

	/* If any of channels unavailable क्रम cf1 just वापस */
	अगर (!r)
		वापस r;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_80P80:
		WARN_ON(!chandef->center_freq2);
		r = cfg80211_get_chans_dfs_available(wiphy,
					MHZ_TO_KHZ(chandef->center_freq2),
					width);
		अवरोध;
	शेष:
		WARN_ON(chandef->center_freq2);
		अवरोध;
	पूर्ण

	वापस r;
पूर्ण

अटल अचिन्हित पूर्णांक cfg80211_get_chans_dfs_cac_समय(काष्ठा wiphy *wiphy,
						    u32 center_freq,
						    u32 bandwidth)
अणु
	काष्ठा ieee80211_channel *c;
	u32 start_freq, end_freq, freq;
	अचिन्हित पूर्णांक dfs_cac_ms = 0;

	start_freq = cfg80211_get_start_freq(center_freq, bandwidth);
	end_freq = cfg80211_get_end_freq(center_freq, bandwidth);

	क्रम (freq = start_freq; freq <= end_freq; freq += MHZ_TO_KHZ(20)) अणु
		c = ieee80211_get_channel_khz(wiphy, freq);
		अगर (!c)
			वापस 0;

		अगर (c->flags & IEEE80211_CHAN_DISABLED)
			वापस 0;

		अगर (!(c->flags & IEEE80211_CHAN_RADAR))
			जारी;

		अगर (c->dfs_cac_ms > dfs_cac_ms)
			dfs_cac_ms = c->dfs_cac_ms;
	पूर्ण

	वापस dfs_cac_ms;
पूर्ण

अचिन्हित पूर्णांक
cfg80211_chandef_dfs_cac_समय(काष्ठा wiphy *wiphy,
			      स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	पूर्णांक width;
	अचिन्हित पूर्णांक t1 = 0, t2 = 0;

	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस 0;

	width = cfg80211_chandef_get_width(chandef);
	अगर (width < 0)
		वापस 0;

	t1 = cfg80211_get_chans_dfs_cac_समय(wiphy,
					     MHZ_TO_KHZ(chandef->center_freq1),
					     width);

	अगर (!chandef->center_freq2)
		वापस t1;

	t2 = cfg80211_get_chans_dfs_cac_समय(wiphy,
					     MHZ_TO_KHZ(chandef->center_freq2),
					     width);

	वापस max(t1, t2);
पूर्ण

अटल bool cfg80211_secondary_chans_ok(काष्ठा wiphy *wiphy,
					u32 center_freq, u32 bandwidth,
					u32 prohibited_flags)
अणु
	काष्ठा ieee80211_channel *c;
	u32 freq, start_freq, end_freq;

	start_freq = cfg80211_get_start_freq(center_freq, bandwidth);
	end_freq = cfg80211_get_end_freq(center_freq, bandwidth);

	क्रम (freq = start_freq; freq <= end_freq; freq += MHZ_TO_KHZ(20)) अणु
		c = ieee80211_get_channel_khz(wiphy, freq);
		अगर (!c || c->flags & prohibited_flags)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/* check अगर the operating channels are valid and supported */
अटल bool cfg80211_edmg_usable(काष्ठा wiphy *wiphy, u8 edmg_channels,
				 क्रमागत ieee80211_edmg_bw_config edmg_bw_config,
				 पूर्णांक primary_channel,
				 काष्ठा ieee80211_edmg *edmg_cap)
अणु
	काष्ठा ieee80211_channel *chan;
	पूर्णांक i, freq;
	पूर्णांक channels_counter = 0;

	अगर (!edmg_channels && !edmg_bw_config)
		वापस true;

	अगर ((!edmg_channels && edmg_bw_config) ||
	    (edmg_channels && !edmg_bw_config))
		वापस false;

	अगर (!(edmg_channels & BIT(primary_channel - 1)))
		वापस false;

	/* 60GHz channels 1..6 */
	क्रम (i = 0; i < 6; i++) अणु
		अगर (!(edmg_channels & BIT(i)))
			जारी;

		अगर (!(edmg_cap->channels & BIT(i)))
			वापस false;

		channels_counter++;

		freq = ieee80211_channel_to_frequency(i + 1,
						      NL80211_BAND_60GHZ);
		chan = ieee80211_get_channel(wiphy, freq);
		अगर (!chan || chan->flags & IEEE80211_CHAN_DISABLED)
			वापस false;
	पूर्ण

	/* IEEE802.11 allows max 4 channels */
	अगर (channels_counter > 4)
		वापस false;

	/* check bw_config is a subset of what driver supports
	 * (see IEEE P802.11ay/D4.0 section 9.4.2.251, Table 13)
	 */
	अगर ((edmg_bw_config % 4) > (edmg_cap->bw_config % 4))
		वापस false;

	अगर (edmg_bw_config > edmg_cap->bw_config)
		वापस false;

	वापस true;
पूर्ण

bool cfg80211_chandef_usable(काष्ठा wiphy *wiphy,
			     स्थिर काष्ठा cfg80211_chan_def *chandef,
			     u32 prohibited_flags)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap;
	काष्ठा ieee80211_edmg *edmg_cap;
	u32 width, control_freq, cap;
	bool support_80_80 = false;

	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस false;

	ht_cap = &wiphy->bands[chandef->chan->band]->ht_cap;
	vht_cap = &wiphy->bands[chandef->chan->band]->vht_cap;
	edmg_cap = &wiphy->bands[chandef->chan->band]->edmg_cap;

	अगर (edmg_cap->channels &&
	    !cfg80211_edmg_usable(wiphy,
				  chandef->edmg.channels,
				  chandef->edmg.bw_config,
				  chandef->chan->hw_value,
				  edmg_cap))
		वापस false;

	control_freq = chandef->chan->center_freq;

	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_1:
		width = 1;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_2:
		width = 2;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_4:
		width = 4;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_8:
		width = 8;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_16:
		width = 16;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_5:
		width = 5;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_10:
		prohibited_flags |= IEEE80211_CHAN_NO_10MHZ;
		width = 10;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
		अगर (!ht_cap->ht_supported &&
		    chandef->chan->band != NL80211_BAND_6GHZ)
			वापस false;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		prohibited_flags |= IEEE80211_CHAN_NO_20MHZ;
		width = 20;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
		width = 40;
		अगर (chandef->chan->band == NL80211_BAND_6GHZ)
			अवरोध;
		अगर (!ht_cap->ht_supported)
			वापस false;
		अगर (!(ht_cap->cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) ||
		    ht_cap->cap & IEEE80211_HT_CAP_40MHZ_INTOLERANT)
			वापस false;
		अगर (chandef->center_freq1 < control_freq &&
		    chandef->chan->flags & IEEE80211_CHAN_NO_HT40MINUS)
			वापस false;
		अगर (chandef->center_freq1 > control_freq &&
		    chandef->chan->flags & IEEE80211_CHAN_NO_HT40PLUS)
			वापस false;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80P80:
		cap = vht_cap->cap;
		support_80_80 =
			(cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ) ||
			(cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ &&
			 cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK) ||
			u32_get_bits(cap, IEEE80211_VHT_CAP_EXT_NSS_BW_MASK) > 1;
		अगर (chandef->chan->band != NL80211_BAND_6GHZ && !support_80_80)
			वापस false;
		fallthrough;
	हाल NL80211_CHAN_WIDTH_80:
		prohibited_flags |= IEEE80211_CHAN_NO_80MHZ;
		width = 80;
		अगर (chandef->chan->band == NL80211_BAND_6GHZ)
			अवरोध;
		अगर (!vht_cap->vht_supported)
			वापस false;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		prohibited_flags |= IEEE80211_CHAN_NO_160MHZ;
		width = 160;
		अगर (chandef->chan->band == NL80211_BAND_6GHZ)
			अवरोध;
		अगर (!vht_cap->vht_supported)
			वापस false;
		cap = vht_cap->cap & IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_MASK;
		अगर (cap != IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ &&
		    cap != IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160_80PLUS80MHZ &&
		    !(vht_cap->cap & IEEE80211_VHT_CAP_EXT_NSS_BW_MASK))
			वापस false;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण

	/*
	 * TODO: What अगर there are only certain 80/160/80+80 MHz channels
	 *	 allowed by the driver, or only certain combinations?
	 *	 For 40 MHz the driver can set the NO_HT40 flags, but क्रम
	 *	 80/160 MHz and in particular 80+80 MHz this isn't really
	 *	 feasible and we only have NO_80MHZ/NO_160MHZ so far but
	 *	 no way to cover 80+80 MHz or more complex restrictions.
	 *	 Note that such restrictions also need to be advertised to
	 *	 userspace, क्रम example क्रम P2P channel selection.
	 */

	अगर (width > 20)
		prohibited_flags |= IEEE80211_CHAN_NO_OFDM;

	/* 5 and 10 MHz are only defined क्रम the OFDM PHY */
	अगर (width < 20)
		prohibited_flags |= IEEE80211_CHAN_NO_OFDM;


	अगर (!cfg80211_secondary_chans_ok(wiphy,
					 ieee80211_chandef_to_khz(chandef),
					 width, prohibited_flags))
		वापस false;

	अगर (!chandef->center_freq2)
		वापस true;
	वापस cfg80211_secondary_chans_ok(wiphy,
					   MHZ_TO_KHZ(chandef->center_freq2),
					   width, prohibited_flags);
पूर्ण
EXPORT_SYMBOL(cfg80211_chandef_usable);

/*
 * Check अगर the channel can be used under permissive conditions mandated by
 * some regulatory bodies, i.e., the channel is marked with
 * IEEE80211_CHAN_IR_CONCURRENT and there is an additional station पूर्णांकerface
 * associated to an AP on the same channel or on the same UNII band
 * (assuming that the AP is an authorized master).
 * In addition allow operation on a channel on which inकरोor operation is
 * allowed, अगरf we are currently operating in an inकरोor environment.
 */
अटल bool cfg80211_ir_permissive_chan(काष्ठा wiphy *wiphy,
					क्रमागत nl80211_अगरtype अगरtype,
					काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा wireless_dev *wdev;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	अगर (!IS_ENABLED(CONFIG_CFG80211_REG_RELAX_NO_IR) ||
	    !(wiphy->regulatory_flags & REGULATORY_ENABLE_RELAX_NO_IR))
		वापस false;

	/* only valid क्रम GO and TDLS off-channel (station/p2p-CL) */
	अगर (अगरtype != NL80211_IFTYPE_P2P_GO &&
	    अगरtype != NL80211_IFTYPE_STATION &&
	    अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस false;

	अगर (regulatory_inकरोor_allowed() &&
	    (chan->flags & IEEE80211_CHAN_INDOOR_ONLY))
		वापस true;

	अगर (!(chan->flags & IEEE80211_CHAN_IR_CONCURRENT))
		वापस false;

	/*
	 * Generally, it is possible to rely on another device/driver to allow
	 * the IR concurrent relaxation, however, since the device can further
	 * enक्रमce the relaxation (by करोing a similar verअगरications as this),
	 * and thus fail the GO instantiation, consider only the पूर्णांकerfaces of
	 * the current रेजिस्टरed device.
	 */
	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		काष्ठा ieee80211_channel *other_chan = शून्य;
		पूर्णांक r1, r2;

		wdev_lock(wdev);
		अगर (wdev->अगरtype == NL80211_IFTYPE_STATION &&
		    wdev->current_bss)
			other_chan = wdev->current_bss->pub.channel;

		/*
		 * If a GO alपढ़ोy operates on the same GO_CONCURRENT channel,
		 * this one (maybe the same one) can beacon as well. We allow
		 * the operation even अगर the station we relied on with
		 * GO_CONCURRENT is disconnected now. But then we must make sure
		 * we're not outकरोor on an inकरोor-only channel.
		 */
		अगर (अगरtype == NL80211_IFTYPE_P2P_GO &&
		    wdev->अगरtype == NL80211_IFTYPE_P2P_GO &&
		    wdev->beacon_पूर्णांकerval &&
		    !(chan->flags & IEEE80211_CHAN_INDOOR_ONLY))
			other_chan = wdev->chandef.chan;
		wdev_unlock(wdev);

		अगर (!other_chan)
			जारी;

		अगर (chan == other_chan)
			वापस true;

		अगर (chan->band != NL80211_BAND_5GHZ &&
		    chan->band != NL80211_BAND_6GHZ)
			जारी;

		r1 = cfg80211_get_unii(chan->center_freq);
		r2 = cfg80211_get_unii(other_chan->center_freq);

		अगर (r1 != -EINVAL && r1 == r2) अणु
			/*
			 * At some locations channels 149-165 are considered a
			 * bundle, but at other locations, e.g., Inकरोnesia,
			 * channels 149-161 are considered a bundle जबतक
			 * channel 165 is left out and considered to be in a
			 * dअगरferent bundle. Thus, in हाल that there is a
			 * station पूर्णांकerface connected to an AP on channel 165,
			 * it is assumed that channels 149-161 are allowed क्रम
			 * GO operations. However, having a station पूर्णांकerface
			 * connected to an AP on channels 149-161, करोes not
			 * allow GO operation on channel 165.
			 */
			अगर (chan->center_freq == 5825 &&
			    other_chan->center_freq != 5825)
				जारी;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool _cfg80211_reg_can_beacon(काष्ठा wiphy *wiphy,
				     काष्ठा cfg80211_chan_def *chandef,
				     क्रमागत nl80211_अगरtype अगरtype,
				     bool check_no_ir)
अणु
	bool res;
	u32 prohibited_flags = IEEE80211_CHAN_DISABLED |
			       IEEE80211_CHAN_RADAR;

	trace_cfg80211_reg_can_beacon(wiphy, chandef, अगरtype, check_no_ir);

	अगर (check_no_ir)
		prohibited_flags |= IEEE80211_CHAN_NO_IR;

	अगर (cfg80211_chandef_dfs_required(wiphy, chandef, अगरtype) > 0 &&
	    cfg80211_chandef_dfs_available(wiphy, chandef)) अणु
		/* We can skip IEEE80211_CHAN_NO_IR अगर chandef dfs available */
		prohibited_flags = IEEE80211_CHAN_DISABLED;
	पूर्ण

	res = cfg80211_chandef_usable(wiphy, chandef, prohibited_flags);

	trace_cfg80211_वापस_bool(res);
	वापस res;
पूर्ण

bool cfg80211_reg_can_beacon(काष्ठा wiphy *wiphy,
			     काष्ठा cfg80211_chan_def *chandef,
			     क्रमागत nl80211_अगरtype अगरtype)
अणु
	वापस _cfg80211_reg_can_beacon(wiphy, chandef, अगरtype, true);
पूर्ण
EXPORT_SYMBOL(cfg80211_reg_can_beacon);

bool cfg80211_reg_can_beacon_relax(काष्ठा wiphy *wiphy,
				   काष्ठा cfg80211_chan_def *chandef,
				   क्रमागत nl80211_अगरtype अगरtype)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	bool check_no_ir;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	/*
	 * Under certain conditions suggested by some regulatory bodies a
	 * GO/STA can IR on channels marked with IEEE80211_NO_IR. Set this flag
	 * only अगर such relaxations are not enabled and the conditions are not
	 * met.
	 */
	check_no_ir = !cfg80211_ir_permissive_chan(wiphy, अगरtype,
						   chandef->chan);

	वापस _cfg80211_reg_can_beacon(wiphy, chandef, अगरtype, check_no_ir);
पूर्ण
EXPORT_SYMBOL(cfg80211_reg_can_beacon_relax);

पूर्णांक cfg80211_set_monitor_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा cfg80211_chan_def *chandef)
अणु
	अगर (!rdev->ops->set_monitor_channel)
		वापस -EOPNOTSUPP;
	अगर (!cfg80211_has_monitors_only(rdev))
		वापस -EBUSY;

	वापस rdev_set_monitor_channel(rdev, chandef);
पूर्ण

व्योम
cfg80211_get_chan_state(काष्ठा wireless_dev *wdev,
		        काष्ठा ieee80211_channel **chan,
		        क्रमागत cfg80211_chan_mode *chanmode,
		        u8 *radar_detect)
अणु
	पूर्णांक ret;

	*chan = शून्य;
	*chanmode = CHAN_MODE_UNDEFINED;

	ASSERT_WDEV_LOCK(wdev);

	अगर (wdev->netdev && !netअगर_running(wdev->netdev))
		वापस;

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_ADHOC:
		अगर (wdev->current_bss) अणु
			*chan = wdev->current_bss->pub.channel;
			*chanmode = (wdev->ibss_fixed &&
				     !wdev->ibss_dfs_possible)
				  ? CHAN_MODE_SHARED
				  : CHAN_MODE_EXCLUSIVE;

			/* consider worst-हाल - IBSS can try to वापस to the
			 * original user-specअगरied channel as creator */
			अगर (wdev->ibss_dfs_possible)
				*radar_detect |= BIT(wdev->chandef.width);
			वापस;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (wdev->current_bss) अणु
			*chan = wdev->current_bss->pub.channel;
			*chanmode = CHAN_MODE_SHARED;
			वापस;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (wdev->cac_started) अणु
			*chan = wdev->chandef.chan;
			*chanmode = CHAN_MODE_SHARED;
			*radar_detect |= BIT(wdev->chandef.width);
		पूर्ण अन्यथा अगर (wdev->beacon_पूर्णांकerval) अणु
			*chan = wdev->chandef.chan;
			*chanmode = CHAN_MODE_SHARED;

			ret = cfg80211_chandef_dfs_required(wdev->wiphy,
							    &wdev->chandef,
							    wdev->अगरtype);
			WARN_ON(ret < 0);
			अगर (ret > 0)
				*radar_detect |= BIT(wdev->chandef.width);
		पूर्ण
		वापस;
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (wdev->mesh_id_len) अणु
			*chan = wdev->chandef.chan;
			*chanmode = CHAN_MODE_SHARED;

			ret = cfg80211_chandef_dfs_required(wdev->wiphy,
							    &wdev->chandef,
							    wdev->अगरtype);
			WARN_ON(ret < 0);
			अगर (ret > 0)
				*radar_detect |= BIT(wdev->chandef.width);
		पूर्ण
		वापस;
	हाल NL80211_IFTYPE_OCB:
		अगर (wdev->chandef.chan) अणु
			*chan = wdev->chandef.chan;
			*chanmode = CHAN_MODE_SHARED;
			वापस;
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_न_अंक:
		/* these पूर्णांकerface types करोn't really have a channel */
		वापस;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_WDS:
	हाल NUM_NL80211_IFTYPES:
		WARN_ON(1);
	पूर्ण
पूर्ण
