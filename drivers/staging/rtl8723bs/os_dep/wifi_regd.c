<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2009-2010  Realtek Corporation.
 *
 *****************************************************************************/

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>

#समावेश <rtw_wअगरi_regd.h>

/*
 * REG_RULE(freq start, freq end, bandwidth, max gain, eirp, reg_flags)
 */

/*
 * Only these channels all allow active
 * scan on all world regulatory करोमुख्यs
 */

/* 2G chan 01 - chan 11 */
#घोषणा RTW_2GHZ_CH01_11	\
	REG_RULE(2412 - 10, 2462 + 10, 40, 0, 20, 0)

/*
 * We enable active scan on these a हाल
 * by हाल basis by regulatory करोमुख्य
 */

/* 2G chan 12 - chan 13, PASSIV SCAN */
#घोषणा RTW_2GHZ_CH12_13	\
	REG_RULE(2467 - 10, 2472 + 10, 40, 0, 20,	\
	NL80211_RRF_PASSIVE_SCAN)

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtw_regकरोm_rd = अणु
	.n_reg_rules = 2,
	.alpha2 = "99",
	.reg_rules = अणु
		RTW_2GHZ_CH01_11,
		RTW_2GHZ_CH12_13,
	पूर्ण
पूर्ण;

अटल पूर्णांक rtw_ieee80211_channel_to_frequency(पूर्णांक chan, पूर्णांक band)
अणु
	/* see 802.11 17.3.8.3.2 and Annex J
	 * there are overlapping channel numbers in 5GHz and 2GHz bands
	 */

	/* NL80211_BAND_2GHZ */
	अगर (chan == 14)
		वापस 2484;
	अन्यथा अगर (chan < 14)
		वापस 2407 + chan * 5;
	अन्यथा
		वापस 0;	/* not supported */
पूर्ण

अटल व्योम _rtw_reg_apply_flags(काष्ठा wiphy *wiphy)
अणु
	काष्ठा adapter *padapter = wiphy_to_adapter(wiphy);
	काष्ठा mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	काष्ठा rt_channel_info *channel_set = pmlmeext->channel_set;
	u8 max_chan_nums = pmlmeext->max_chan_nums;

	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	अचिन्हित पूर्णांक i, j;
	u16 channel;
	u32 freq;

	/* all channels disable */
	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		sband = wiphy->bands[i];

		अगर (sband) अणु
			क्रम (j = 0; j < sband->n_channels; j++) अणु
				ch = &sband->channels[j];

				अगर (ch)
					ch->flags = IEEE80211_CHAN_DISABLED;
			पूर्ण
		पूर्ण
	पूर्ण

	/* channels apply by channel plans. */
	क्रम (i = 0; i < max_chan_nums; i++) अणु
		channel = channel_set[i].ChannelNum;
		freq =
		    rtw_ieee80211_channel_to_frequency(channel,
						       NL80211_BAND_2GHZ);

		ch = ieee80211_get_channel(wiphy, freq);
		अगर (ch) अणु
			अगर (channel_set[i].ScanType == SCAN_PASSIVE)
				ch->flags = IEEE80211_CHAN_NO_IR;
			अन्यथा
				ch->flags = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक _rtw_reg_notअगरier_apply(काष्ठा wiphy *wiphy,
				   काष्ठा regulatory_request *request,
				   काष्ठा rtw_regulatory *reg)
अणु
	/* Hard code flags */
	_rtw_reg_apply_flags(wiphy);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *_rtw_regकरोमुख्य_select(काष्ठा
							       rtw_regulatory
							       *reg)
अणु
	वापस &rtw_regकरोm_rd;
पूर्ण

अटल व्योम _rtw_regd_init_wiphy(काष्ठा rtw_regulatory *reg,
				 काष्ठा wiphy *wiphy,
				 व्योम (*reg_notअगरier)(काष्ठा wiphy *wiphy,
						      काष्ठा
						      regulatory_request *
						      request))
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;

	wiphy->reg_notअगरier = reg_notअगरier;

	wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG;
	wiphy->regulatory_flags &= ~REGULATORY_STRICT_REG;
	wiphy->regulatory_flags &= ~REGULATORY_DISABLE_BEACON_HINTS;

	regd = _rtw_regकरोमुख्य_select(reg);
	wiphy_apply_custom_regulatory(wiphy, regd);

	/* Hard code flags */
	_rtw_reg_apply_flags(wiphy);
पूर्ण

व्योम rtw_regd_init(काष्ठा wiphy *wiphy,
		   व्योम (*reg_notअगरier)(काष्ठा wiphy *wiphy,
					काष्ठा regulatory_request *request))
अणु
	_rtw_regd_init_wiphy(शून्य, wiphy, reg_notअगरier);
पूर्ण

व्योम rtw_reg_notअगरier(काष्ठा wiphy *wiphy, काष्ठा regulatory_request *request)
अणु
	काष्ठा rtw_regulatory *reg = शून्य;

	_rtw_reg_notअगरier_apply(wiphy, request, reg);
पूर्ण
