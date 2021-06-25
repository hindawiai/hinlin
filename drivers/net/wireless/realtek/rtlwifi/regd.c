<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "regd.h"

अटल काष्ठा country_code_to_क्रमागत_rd all_countries[] = अणु
	अणुCOUNTRY_CODE_FCC, "US"पूर्ण,
	अणुCOUNTRY_CODE_IC, "US"पूर्ण,
	अणुCOUNTRY_CODE_ETSI, "EC"पूर्ण,
	अणुCOUNTRY_CODE_SPAIN, "EC"पूर्ण,
	अणुCOUNTRY_CODE_FRANCE, "EC"पूर्ण,
	अणुCOUNTRY_CODE_MKK, "JP"पूर्ण,
	अणुCOUNTRY_CODE_MKK1, "JP"पूर्ण,
	अणुCOUNTRY_CODE_ISRAEL, "EC"पूर्ण,
	अणुCOUNTRY_CODE_TELEC, "JP"पूर्ण,
	अणुCOUNTRY_CODE_MIC, "JP"पूर्ण,
	अणुCOUNTRY_CODE_GLOBAL_DOMAIN, "JP"पूर्ण,
	अणुCOUNTRY_CODE_WORLD_WIDE_13, "EC"पूर्ण,
	अणुCOUNTRY_CODE_TELEC_NETGEAR, "EC"पूर्ण,
	अणुCOUNTRY_CODE_WORLD_WIDE_13_5G_ALL, "US"पूर्ण,
पूर्ण;

/*
 *Only these channels all allow active
 *scan on all world regulatory करोमुख्यs
 */
#घोषणा RTL819x_2GHZ_CH01_11	\
	REG_RULE(2412-10, 2462+10, 40, 0, 20, 0)

/*
 *We enable active scan on these a हाल
 *by हाल basis by regulatory करोमुख्य
 */
#घोषणा RTL819x_2GHZ_CH12_13	\
	REG_RULE(2467-10, 2472+10, 40, 0, 20,\
	NL80211_RRF_PASSIVE_SCAN)

#घोषणा RTL819x_2GHZ_CH14	\
	REG_RULE(2484-10, 2484+10, 40, 0, 20, \
	NL80211_RRF_PASSIVE_SCAN | \
	NL80211_RRF_NO_OFDM)

/* 5G chan 36 - chan 64*/
#घोषणा RTL819x_5GHZ_5150_5350	\
	REG_RULE(5150-10, 5350+10, 80, 0, 30, 0)
/* 5G chan 100 - chan 165*/
#घोषणा RTL819x_5GHZ_5470_5850	\
	REG_RULE(5470-10, 5850+10, 80, 0, 30, 0)
/* 5G chan 149 - chan 165*/
#घोषणा RTL819x_5GHZ_5725_5850	\
	REG_RULE(5725-10, 5850+10, 80, 0, 30, 0)

#घोषणा RTL819x_5GHZ_ALL	\
	(RTL819x_5GHZ_5150_5350, RTL819x_5GHZ_5470_5850)

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtl_regकरोm_11 = अणु
	.n_reg_rules = 1,
	.alpha2 = "99",
	.reg_rules = अणु
		      RTL819x_2GHZ_CH01_11,
		      पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtl_regकरोm_12_13 = अणु
	.n_reg_rules = 2,
	.alpha2 = "99",
	.reg_rules = अणु
		      RTL819x_2GHZ_CH01_11,
			  RTL819x_2GHZ_CH12_13,
		      पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtl_regकरोm_no_midband = अणु
	.n_reg_rules = 3,
	.alpha2 = "99",
	.reg_rules = अणु
		      RTL819x_2GHZ_CH01_11,
			  RTL819x_5GHZ_5150_5350,
			  RTL819x_5GHZ_5725_5850,
		      पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtl_regकरोm_60_64 = अणु
	.n_reg_rules = 3,
	.alpha2 = "99",
	.reg_rules = अणु
		      RTL819x_2GHZ_CH01_11,
			  RTL819x_2GHZ_CH12_13,
			  RTL819x_5GHZ_5725_5850,
		      पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtl_regकरोm_14_60_64 = अणु
	.n_reg_rules = 4,
	.alpha2 = "99",
	.reg_rules = अणु
		      RTL819x_2GHZ_CH01_11,
			  RTL819x_2GHZ_CH12_13,
			  RTL819x_2GHZ_CH14,
			  RTL819x_5GHZ_5725_5850,
		      पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtl_regकरोm_12_13_5g_all = अणु
	.n_reg_rules = 4,
	.alpha2 = "99",
	.reg_rules = अणु
			RTL819x_2GHZ_CH01_11,
			RTL819x_2GHZ_CH12_13,
			RTL819x_5GHZ_5150_5350,
			RTL819x_5GHZ_5470_5850,
		पूर्ण
पूर्ण;

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य rtl_regकरोm_14 = अणु
	.n_reg_rules = 3,
	.alpha2 = "99",
	.reg_rules = अणु
		      RTL819x_2GHZ_CH01_11,
			  RTL819x_2GHZ_CH12_13,
			  RTL819x_2GHZ_CH14,
		      पूर्ण
पूर्ण;

अटल bool _rtl_is_radar_freq(u16 center_freq)
अणु
	वापस center_freq >= 5260 && center_freq <= 5700;
पूर्ण

अटल व्योम _rtl_reg_apply_beaconing_flags(काष्ठा wiphy *wiphy,
					   क्रमागत nl80211_reg_initiator initiator)
अणु
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा ieee80211_reg_rule *reg_rule;
	काष्ठा ieee80211_channel *ch;
	अचिन्हित पूर्णांक i;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु

		अगर (!wiphy->bands[band])
			जारी;

		sband = wiphy->bands[band];

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			ch = &sband->channels[i];
			अगर (_rtl_is_radar_freq(ch->center_freq) ||
			    (ch->flags & IEEE80211_CHAN_RADAR))
				जारी;
			अगर (initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE) अणु
				reg_rule = freq_reg_info(wiphy,
							 ch->center_freq);
				अगर (IS_ERR(reg_rule))
					जारी;
				/*
				 *If 11d had a rule क्रम this channel ensure
				 *we enable adhoc/beaconing अगर it allows us to
				 *use it. Note that we would have disabled it
				 *by applying our अटल world regकरोमुख्य by
				 *शेष during init, prior to calling our
				 *regulatory_hपूर्णांक().
				 */

				अगर (!(reg_rule->flags & NL80211_RRF_NO_IBSS))
					ch->flags &= ~IEEE80211_CHAN_NO_IBSS;
				अगर (!(reg_rule->flags &
				      NL80211_RRF_PASSIVE_SCAN))
					ch->flags &=
					    ~IEEE80211_CHAN_PASSIVE_SCAN;
			पूर्ण अन्यथा अणु
				अगर (ch->beacon_found)
					ch->flags &= ~(IEEE80211_CHAN_NO_IBSS |
						   IEEE80211_CHAN_PASSIVE_SCAN);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Allows active scan scan on Ch 12 and 13 */
अटल व्योम _rtl_reg_apply_active_scan_flags(काष्ठा wiphy *wiphy,
					     क्रमागत nl80211_reg_initiator
					     initiator)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	स्थिर काष्ठा ieee80211_reg_rule *reg_rule;

	अगर (!wiphy->bands[NL80211_BAND_2GHZ])
		वापस;
	sband = wiphy->bands[NL80211_BAND_2GHZ];

	/*
	 *If no country IE has been received always enable active scan
	 *on these channels. This is only करोne क्रम specअगरic regulatory SKUs
	 */
	अगर (initiator != NL80211_REGDOM_SET_BY_COUNTRY_IE) अणु
		ch = &sband->channels[11];	/* CH 12 */
		अगर (ch->flags & IEEE80211_CHAN_PASSIVE_SCAN)
			ch->flags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
		ch = &sband->channels[12];	/* CH 13 */
		अगर (ch->flags & IEEE80211_CHAN_PASSIVE_SCAN)
			ch->flags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
		वापस;
	पूर्ण

	/*
	 *If a country IE has been recieved check its rule क्रम this
	 *channel first beक्रमe enabling active scan. The passive scan
	 *would have been enक्रमced by the initial processing of our
	 *custom regulatory करोमुख्य.
	 */

	ch = &sband->channels[11];	/* CH 12 */
	reg_rule = freq_reg_info(wiphy, ch->center_freq);
	अगर (!IS_ERR(reg_rule)) अणु
		अगर (!(reg_rule->flags & NL80211_RRF_PASSIVE_SCAN))
			अगर (ch->flags & IEEE80211_CHAN_PASSIVE_SCAN)
				ch->flags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
	पूर्ण

	ch = &sband->channels[12];	/* CH 13 */
	reg_rule = freq_reg_info(wiphy, ch->center_freq);
	अगर (!IS_ERR(reg_rule)) अणु
		अगर (!(reg_rule->flags & NL80211_RRF_PASSIVE_SCAN))
			अगर (ch->flags & IEEE80211_CHAN_PASSIVE_SCAN)
				ch->flags &= ~IEEE80211_CHAN_PASSIVE_SCAN;
	पूर्ण
पूर्ण

/*
 *Always apply Radar/DFS rules on
 *freq range 5260 MHz - 5700 MHz
 */
अटल व्योम _rtl_reg_apply_radar_flags(काष्ठा wiphy *wiphy)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	अचिन्हित पूर्णांक i;

	अगर (!wiphy->bands[NL80211_BAND_5GHZ])
		वापस;

	sband = wiphy->bands[NL80211_BAND_5GHZ];

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		ch = &sband->channels[i];
		अगर (!_rtl_is_radar_freq(ch->center_freq))
			जारी;

		/*
		 *We always enable radar detection/DFS on this
		 *frequency range. Additionally we also apply on
		 *this frequency range:
		 *- If STA mode करोes not yet have DFS supports disable
		 * active scanning
		 *- If adhoc mode करोes not support DFS yet then disable
		 * adhoc in the frequency.
		 *- If AP mode करोes not yet support radar detection/DFS
		 *करो not allow AP mode
		 */
		अगर (!(ch->flags & IEEE80211_CHAN_DISABLED))
			ch->flags |= IEEE80211_CHAN_RADAR |
			    IEEE80211_CHAN_NO_IBSS |
			    IEEE80211_CHAN_PASSIVE_SCAN;
	पूर्ण
पूर्ण

अटल व्योम _rtl_reg_apply_world_flags(काष्ठा wiphy *wiphy,
				       क्रमागत nl80211_reg_initiator initiator,
				       काष्ठा rtl_regulatory *reg)
अणु
	_rtl_reg_apply_beaconing_flags(wiphy, initiator);
	_rtl_reg_apply_active_scan_flags(wiphy, initiator);
	वापस;
पूर्ण

अटल पूर्णांक _rtl_reg_notअगरier_apply(काष्ठा wiphy *wiphy,
				   काष्ठा regulatory_request *request,
				   काष्ठा rtl_regulatory *reg)
अणु
	/* We always apply this */
	_rtl_reg_apply_radar_flags(wiphy);

	चयन (request->initiator) अणु
	हाल NL80211_REGDOM_SET_BY_DRIVER:
	हाल NL80211_REGDOM_SET_BY_CORE:
	हाल NL80211_REGDOM_SET_BY_USER:
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		_rtl_reg_apply_world_flags(wiphy, request->initiator, reg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *_rtl_regकरोमुख्य_select(
						काष्ठा rtl_regulatory *reg)
अणु
	चयन (reg->country_code) अणु
	हाल COUNTRY_CODE_FCC:
		वापस &rtl_regकरोm_no_midband;
	हाल COUNTRY_CODE_IC:
		वापस &rtl_regकरोm_11;
	हाल COUNTRY_CODE_TELEC_NETGEAR:
		वापस &rtl_regकरोm_60_64;
	हाल COUNTRY_CODE_ETSI:
	हाल COUNTRY_CODE_SPAIN:
	हाल COUNTRY_CODE_FRANCE:
	हाल COUNTRY_CODE_ISRAEL:
		वापस &rtl_regकरोm_12_13;
	हाल COUNTRY_CODE_MKK:
	हाल COUNTRY_CODE_MKK1:
	हाल COUNTRY_CODE_TELEC:
	हाल COUNTRY_CODE_MIC:
		वापस &rtl_regकरोm_14_60_64;
	हाल COUNTRY_CODE_GLOBAL_DOMAIN:
		वापस &rtl_regकरोm_14;
	हाल COUNTRY_CODE_WORLD_WIDE_13:
	हाल COUNTRY_CODE_WORLD_WIDE_13_5G_ALL:
		वापस &rtl_regकरोm_12_13_5g_all;
	शेष:
		वापस &rtl_regकरोm_no_midband;
	पूर्ण
पूर्ण

अटल पूर्णांक _rtl_regd_init_wiphy(काष्ठा rtl_regulatory *reg,
				काष्ठा wiphy *wiphy,
				व्योम (*reg_notअगरier)(काष्ठा wiphy *wiphy,
						     काष्ठा regulatory_request *
						     request))
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;

	wiphy->reg_notअगरier = reg_notअगरier;

	wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG;
	wiphy->regulatory_flags &= ~REGULATORY_STRICT_REG;
	wiphy->regulatory_flags &= ~REGULATORY_DISABLE_BEACON_HINTS;
	regd = _rtl_regकरोमुख्य_select(reg);
	wiphy_apply_custom_regulatory(wiphy, regd);
	_rtl_reg_apply_radar_flags(wiphy);
	_rtl_reg_apply_world_flags(wiphy, NL80211_REGDOM_SET_BY_DRIVER, reg);
	वापस 0;
पूर्ण

अटल काष्ठा country_code_to_क्रमागत_rd *_rtl_regd_find_country(u16 countrycode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(all_countries); i++) अणु
		अगर (all_countries[i].countrycode == countrycode)
			वापस &all_countries[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल u8 channel_plan_to_country_code(u8 channelplan)
अणु
	चयन (channelplan) अणु
	हाल 0x20:
	हाल 0x21:
		वापस COUNTRY_CODE_WORLD_WIDE_13;
	हाल 0x22:
		वापस COUNTRY_CODE_IC;
	हाल 0x25:
		वापस COUNTRY_CODE_ETSI;
	हाल 0x32:
		वापस COUNTRY_CODE_TELEC_NETGEAR;
	हाल 0x41:
		वापस COUNTRY_CODE_GLOBAL_DOMAIN;
	हाल 0x7f:
		वापस COUNTRY_CODE_WORLD_WIDE_13_5G_ALL;
	शेष:
		वापस COUNTRY_CODE_MAX; /*Error*/
	पूर्ण
पूर्ण

पूर्णांक rtl_regd_init(काष्ठा ieee80211_hw *hw,
		  व्योम (*reg_notअगरier)(काष्ठा wiphy *wiphy,
				       काष्ठा regulatory_request *request))
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा wiphy *wiphy = hw->wiphy;
	काष्ठा country_code_to_क्रमागत_rd *country = शून्य;

	अगर (!wiphy)
		वापस -EINVAL;

	/* init country_code from efuse channel plan */
	rtlpriv->regd.country_code =
		channel_plan_to_country_code(rtlpriv->efuse.channel_plan);

	rtl_dbg(rtlpriv, COMP_REGD, DBG_DMESG,
		"rtl: EEPROM regdomain: 0x%0x country code: %d\n",
		rtlpriv->efuse.channel_plan, rtlpriv->regd.country_code);

	अगर (rtlpriv->regd.country_code >= COUNTRY_CODE_MAX) अणु
		rtl_dbg(rtlpriv, COMP_REGD, DBG_DMESG,
			"rtl: EEPROM indicates invalid country code, world wide 13 should be used\n");

		rtlpriv->regd.country_code = COUNTRY_CODE_WORLD_WIDE_13;
	पूर्ण

	country = _rtl_regd_find_country(rtlpriv->regd.country_code);

	अगर (country) अणु
		rtlpriv->regd.alpha2[0] = country->iso_name[0];
		rtlpriv->regd.alpha2[1] = country->iso_name[1];
	पूर्ण अन्यथा अणु
		rtlpriv->regd.alpha2[0] = '0';
		rtlpriv->regd.alpha2[1] = '0';
	पूर्ण

	rtl_dbg(rtlpriv, COMP_REGD, DBG_TRACE,
		"rtl: Country alpha2 being used: %c%c\n",
		rtlpriv->regd.alpha2[0], rtlpriv->regd.alpha2[1]);

	_rtl_regd_init_wiphy(&rtlpriv->regd, wiphy, reg_notअगरier);

	वापस 0;
पूर्ण

व्योम rtl_reg_notअगरier(काष्ठा wiphy *wiphy, काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_REGD, DBG_LOUD, "\n");

	_rtl_reg_notअगरier_apply(wiphy, request, &rtlpriv->regd);
पूर्ण
