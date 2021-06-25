<शैली गुरु>
/*
 * Copyright (c) 2008-2009 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश "regd.h"
#समावेश "regd_common.h"

अटल पूर्णांक __ath_regd_init(काष्ठा ath_regulatory *reg);

/*
 * This is a set of common rules used by our world regulatory करोमुख्यs.
 * We have 12 world regulatory करोमुख्यs. To save space we consolidate
 * the regulatory करोमुख्यs in 5 काष्ठाures by frequency and change
 * the flags on our reg_notअगरier() on a हाल by हाल basis.
 */

/* Only these channels all allow active scan on all world regulatory करोमुख्यs */
#घोषणा ATH_2GHZ_CH01_11	REG_RULE(2412-10, 2462+10, 40, 0, 20, 0)

/* We enable active scan on these a हाल by हाल basis by regulatory करोमुख्य */
#घोषणा ATH_2GHZ_CH12_13	REG_RULE(2467-10, 2472+10, 40, 0, 20,\
					 NL80211_RRF_NO_IR)
#घोषणा ATH_2GHZ_CH14		REG_RULE(2484-10, 2484+10, 40, 0, 20,\
					 NL80211_RRF_NO_IR | \
					 NL80211_RRF_NO_OFDM)

/* We allow IBSS on these on a हाल by हाल basis by regulatory करोमुख्य */
#घोषणा ATH_5GHZ_5150_5350	REG_RULE(5150-10, 5350+10, 80, 0, 30,\
					 NL80211_RRF_NO_IR)
#घोषणा ATH_5GHZ_5470_5850	REG_RULE(5470-10, 5850+10, 80, 0, 30,\
					 NL80211_RRF_NO_IR)
#घोषणा ATH_5GHZ_5725_5850	REG_RULE(5725-10, 5850+10, 80, 0, 30,\
					 NL80211_RRF_NO_IR)

#घोषणा ATH_2GHZ_ALL		ATH_2GHZ_CH01_11, \
				ATH_2GHZ_CH12_13, \
				ATH_2GHZ_CH14

#घोषणा ATH_5GHZ_ALL		ATH_5GHZ_5150_5350, \
				ATH_5GHZ_5470_5850

/* This one skips what we call "mid band" */
#घोषणा ATH_5GHZ_NO_MIDBAND	ATH_5GHZ_5150_5350, \
				ATH_5GHZ_5725_5850

/* Can be used क्रम:
 * 0x60, 0x61, 0x62 */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य ath_world_regकरोm_60_61_62 = अणु
	.n_reg_rules = 5,
	.alpha2 =  "99",
	.reg_rules = अणु
		ATH_2GHZ_ALL,
		ATH_5GHZ_ALL,
	पूर्ण
पूर्ण;

/* Can be used by 0x63 and 0x65 */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य ath_world_regकरोm_63_65 = अणु
	.n_reg_rules = 4,
	.alpha2 =  "99",
	.reg_rules = अणु
		ATH_2GHZ_CH01_11,
		ATH_2GHZ_CH12_13,
		ATH_5GHZ_NO_MIDBAND,
	पूर्ण
पूर्ण;

/* Can be used by 0x64 only */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य ath_world_regकरोm_64 = अणु
	.n_reg_rules = 3,
	.alpha2 =  "99",
	.reg_rules = अणु
		ATH_2GHZ_CH01_11,
		ATH_5GHZ_NO_MIDBAND,
	पूर्ण
पूर्ण;

/* Can be used by 0x66 and 0x69 */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य ath_world_regकरोm_66_69 = अणु
	.n_reg_rules = 3,
	.alpha2 =  "99",
	.reg_rules = अणु
		ATH_2GHZ_CH01_11,
		ATH_5GHZ_ALL,
	पूर्ण
पूर्ण;

/* Can be used by 0x67, 0x68, 0x6A and 0x6C */
अटल स्थिर काष्ठा ieee80211_regकरोमुख्य ath_world_regकरोm_67_68_6A_6C = अणु
	.n_reg_rules = 4,
	.alpha2 =  "99",
	.reg_rules = अणु
		ATH_2GHZ_CH01_11,
		ATH_2GHZ_CH12_13,
		ATH_5GHZ_ALL,
	पूर्ण
पूर्ण;

अटल bool dynamic_country_user_possible(काष्ठा ath_regulatory *reg)
अणु
	अगर (IS_ENABLED(CONFIG_ATH_REG_DYNAMIC_USER_CERT_TESTING))
		वापस true;

	चयन (reg->country_code) अणु
	हाल CTRY_UNITED_STATES:
	हाल CTRY_JAPAN1:
	हाल CTRY_JAPAN2:
	हाल CTRY_JAPAN3:
	हाल CTRY_JAPAN4:
	हाल CTRY_JAPAN5:
	हाल CTRY_JAPAN6:
	हाल CTRY_JAPAN7:
	हाल CTRY_JAPAN8:
	हाल CTRY_JAPAN9:
	हाल CTRY_JAPAN10:
	हाल CTRY_JAPAN11:
	हाल CTRY_JAPAN12:
	हाल CTRY_JAPAN13:
	हाल CTRY_JAPAN14:
	हाल CTRY_JAPAN15:
	हाल CTRY_JAPAN16:
	हाल CTRY_JAPAN17:
	हाल CTRY_JAPAN18:
	हाल CTRY_JAPAN19:
	हाल CTRY_JAPAN20:
	हाल CTRY_JAPAN21:
	हाल CTRY_JAPAN22:
	हाल CTRY_JAPAN23:
	हाल CTRY_JAPAN24:
	हाल CTRY_JAPAN25:
	हाल CTRY_JAPAN26:
	हाल CTRY_JAPAN27:
	हाल CTRY_JAPAN28:
	हाल CTRY_JAPAN29:
	हाल CTRY_JAPAN30:
	हाल CTRY_JAPAN31:
	हाल CTRY_JAPAN32:
	हाल CTRY_JAPAN33:
	हाल CTRY_JAPAN34:
	हाल CTRY_JAPAN35:
	हाल CTRY_JAPAN36:
	हाल CTRY_JAPAN37:
	हाल CTRY_JAPAN38:
	हाल CTRY_JAPAN39:
	हाल CTRY_JAPAN40:
	हाल CTRY_JAPAN41:
	हाल CTRY_JAPAN42:
	हाल CTRY_JAPAN43:
	हाल CTRY_JAPAN44:
	हाल CTRY_JAPAN45:
	हाल CTRY_JAPAN46:
	हाल CTRY_JAPAN47:
	हाल CTRY_JAPAN48:
	हाल CTRY_JAPAN49:
	हाल CTRY_JAPAN50:
	हाल CTRY_JAPAN51:
	हाल CTRY_JAPAN52:
	हाल CTRY_JAPAN53:
	हाल CTRY_JAPAN54:
	हाल CTRY_JAPAN55:
	हाल CTRY_JAPAN56:
	हाल CTRY_JAPAN57:
	हाल CTRY_JAPAN58:
	हाल CTRY_JAPAN59:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ath_reg_dyn_country_user_allow(काष्ठा ath_regulatory *reg)
अणु
	अगर (!IS_ENABLED(CONFIG_ATH_REG_DYNAMIC_USER_REG_HINTS))
		वापस false;
	अगर (!dynamic_country_user_possible(reg))
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool is_wwr_sku(u16 regd)
अणु
	वापस ((regd & COUNTRY_ERD_FLAG) != COUNTRY_ERD_FLAG) &&
		(((regd & WORLD_SKU_MASK) == WORLD_SKU_PREFIX) ||
		(regd == WORLD));
पूर्ण

अटल u16 ath_regd_get_eepromRD(काष्ठा ath_regulatory *reg)
अणु
	वापस reg->current_rd & ~WORLDWIDE_ROAMING_FLAG;
पूर्ण

bool ath_is_world_regd(काष्ठा ath_regulatory *reg)
अणु
	वापस is_wwr_sku(ath_regd_get_eepromRD(reg));
पूर्ण
EXPORT_SYMBOL(ath_is_world_regd);

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य *ath_शेष_world_regकरोमुख्य(व्योम)
अणु
	/* this is the most restrictive */
	वापस &ath_world_regकरोm_64;
पूर्ण

अटल स्थिर काष्ठा
ieee80211_regकरोमुख्य *ath_world_regकरोमुख्य(काष्ठा ath_regulatory *reg)
अणु
	चयन (reg->regpair->reg_करोमुख्य) अणु
	हाल 0x60:
	हाल 0x61:
	हाल 0x62:
		वापस &ath_world_regकरोm_60_61_62;
	हाल 0x63:
	हाल 0x65:
		वापस &ath_world_regकरोm_63_65;
	हाल 0x64:
		वापस &ath_world_regकरोm_64;
	हाल 0x66:
	हाल 0x69:
		वापस &ath_world_regकरोm_66_69;
	हाल 0x67:
	हाल 0x68:
	हाल 0x6A:
	हाल 0x6C:
		वापस &ath_world_regकरोm_67_68_6A_6C;
	शेष:
		WARN_ON(1);
		वापस ath_शेष_world_regकरोमुख्य();
	पूर्ण
पूर्ण

bool ath_is_49ghz_allowed(u16 regकरोमुख्य)
अणु
	/* possibly more */
	वापस regकरोमुख्य == MKK9_MKKC;
पूर्ण
EXPORT_SYMBOL(ath_is_49ghz_allowed);

/* Frequency is one where radar detection is required */
अटल bool ath_is_radar_freq(u16 center_freq,
			      काष्ठा ath_regulatory *reg)

अणु
	अगर (reg->country_code == CTRY_INDIA)
		वापस (center_freq >= 5500 && center_freq <= 5700);
	वापस (center_freq >= 5260 && center_freq <= 5700);
पूर्ण

अटल व्योम ath_क्रमce_clear_no_ir_chan(काष्ठा wiphy *wiphy,
				       काष्ठा ieee80211_channel *ch)
अणु
	स्थिर काष्ठा ieee80211_reg_rule *reg_rule;

	reg_rule = freq_reg_info(wiphy, MHZ_TO_KHZ(ch->center_freq));
	अगर (IS_ERR(reg_rule))
		वापस;

	अगर (!(reg_rule->flags & NL80211_RRF_NO_IR))
		अगर (ch->flags & IEEE80211_CHAN_NO_IR)
			ch->flags &= ~IEEE80211_CHAN_NO_IR;
पूर्ण

अटल व्योम ath_क्रमce_clear_no_ir_freq(काष्ठा wiphy *wiphy, u16 center_freq)
अणु
	काष्ठा ieee80211_channel *ch;

	ch = ieee80211_get_channel(wiphy, center_freq);
	अगर (!ch)
		वापस;

	ath_क्रमce_clear_no_ir_chan(wiphy, ch);
पूर्ण

अटल व्योम ath_क्रमce_no_ir_chan(काष्ठा ieee80211_channel *ch)
अणु
	ch->flags |= IEEE80211_CHAN_NO_IR;
पूर्ण

अटल व्योम ath_क्रमce_no_ir_freq(काष्ठा wiphy *wiphy, u16 center_freq)
अणु
	काष्ठा ieee80211_channel *ch;

	ch = ieee80211_get_channel(wiphy, center_freq);
	अगर (!ch)
		वापस;

	ath_क्रमce_no_ir_chan(ch);
पूर्ण

अटल व्योम
__ath_reg_apply_beaconing_flags(काष्ठा wiphy *wiphy,
				काष्ठा ath_regulatory *reg,
				क्रमागत nl80211_reg_initiator initiator,
				काष्ठा ieee80211_channel *ch)
अणु
	अगर (ath_is_radar_freq(ch->center_freq, reg) ||
	    (ch->flags & IEEE80211_CHAN_RADAR))
		वापस;

	चयन (initiator) अणु
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		ath_क्रमce_clear_no_ir_chan(wiphy, ch);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_USER:
		अगर (ath_reg_dyn_country_user_allow(reg))
			ath_क्रमce_clear_no_ir_chan(wiphy, ch);
		अवरोध;
	शेष:
		अगर (ch->beacon_found)
			ch->flags &= ~IEEE80211_CHAN_NO_IR;
	पूर्ण
पूर्ण

/*
 * These exception rules करो not apply radar frequencies.
 *
 * - We enable initiating radiation अगर the country IE says its fine:
 * - If no country IE has been processed and a we determine we have
 *   received a beacon on a channel we can enable initiating radiation.
 */
अटल व्योम
ath_reg_apply_beaconing_flags(काष्ठा wiphy *wiphy,
			      काष्ठा ath_regulatory *reg,
			      क्रमागत nl80211_reg_initiator initiator)
अणु
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	अचिन्हित पूर्णांक i;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		अगर (!wiphy->bands[band])
			जारी;
		sband = wiphy->bands[band];
		क्रम (i = 0; i < sband->n_channels; i++) अणु
			ch = &sband->channels[i];
			__ath_reg_apply_beaconing_flags(wiphy, reg,
							initiator, ch);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ath_reg_apply_ir_flags()
 * @wiphy: the wiphy to use
 * @reg: regulatory काष्ठाure - used क्रम country selection
 * @initiator: the regulatory hपूर्णांक initiator
 *
 * If no country IE has been received always enable passive scan
 * and no-ibss on these channels. This is only करोne क्रम specअगरic
 * regulatory SKUs.
 *
 * If a country IE has been received check its rule क्रम this
 * channel first beक्रमe enabling active scan. The passive scan
 * would have been enक्रमced by the initial processing of our
 * custom regulatory करोमुख्य.
 */
अटल व्योम
ath_reg_apply_ir_flags(काष्ठा wiphy *wiphy,
		       काष्ठा ath_regulatory *reg,
		       क्रमागत nl80211_reg_initiator initiator)
अणु
	काष्ठा ieee80211_supported_band *sband;

	sband = wiphy->bands[NL80211_BAND_2GHZ];
	अगर (!sband)
		वापस;

	चयन(initiator) अणु
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		ath_क्रमce_clear_no_ir_freq(wiphy, 2467);
		ath_क्रमce_clear_no_ir_freq(wiphy, 2472);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_USER:
		अगर (!ath_reg_dyn_country_user_allow(reg))
			अवरोध;
		ath_क्रमce_clear_no_ir_freq(wiphy, 2467);
		ath_क्रमce_clear_no_ir_freq(wiphy, 2472);
		अवरोध;
	शेष:
		ath_क्रमce_no_ir_freq(wiphy, 2467);
		ath_क्रमce_no_ir_freq(wiphy, 2472);
	पूर्ण
पूर्ण

/* Always apply Radar/DFS rules on freq range 5500 MHz - 5700 MHz */
अटल व्योम ath_reg_apply_radar_flags(काष्ठा wiphy *wiphy,
				      काष्ठा ath_regulatory *reg)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	अचिन्हित पूर्णांक i;

	अगर (!wiphy->bands[NL80211_BAND_5GHZ])
		वापस;

	sband = wiphy->bands[NL80211_BAND_5GHZ];

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		ch = &sband->channels[i];
		अगर (!ath_is_radar_freq(ch->center_freq, reg))
			जारी;
		/* We always enable radar detection/DFS on this
		 * frequency range. Additionally we also apply on
		 * this frequency range:
		 * - If STA mode करोes not yet have DFS supports disable
		 *   active scanning
		 * - If adhoc mode करोes not support DFS yet then
		 *   disable adhoc in the frequency.
		 * - If AP mode करोes not yet support radar detection/DFS
		 *   करो not allow AP mode
		 */
		अगर (!(ch->flags & IEEE80211_CHAN_DISABLED))
			ch->flags |= IEEE80211_CHAN_RADAR |
				     IEEE80211_CHAN_NO_IR;
	पूर्ण
पूर्ण

अटल व्योम ath_reg_apply_world_flags(काष्ठा wiphy *wiphy,
				      क्रमागत nl80211_reg_initiator initiator,
				      काष्ठा ath_regulatory *reg)
अणु
	चयन (reg->regpair->reg_करोमुख्य) अणु
	हाल 0x60:
	हाल 0x63:
	हाल 0x66:
	हाल 0x67:
	हाल 0x6C:
		ath_reg_apply_beaconing_flags(wiphy, reg, initiator);
		अवरोध;
	हाल 0x68:
		ath_reg_apply_beaconing_flags(wiphy, reg, initiator);
		ath_reg_apply_ir_flags(wiphy, reg, initiator);
		अवरोध;
	शेष:
		अगर (ath_reg_dyn_country_user_allow(reg))
			ath_reg_apply_beaconing_flags(wiphy, reg, initiator);
	पूर्ण
पूर्ण

u16 ath_regd_find_country_by_name(अक्षर *alpha2)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(allCountries); i++) अणु
		अगर (!स_भेद(allCountries[i].isoName, alpha2, 2))
			वापस allCountries[i].countryCode;
	पूर्ण

	वापस -1;
पूर्ण
EXPORT_SYMBOL(ath_regd_find_country_by_name);

अटल पूर्णांक __ath_reg_dyn_country(काष्ठा wiphy *wiphy,
				 काष्ठा ath_regulatory *reg,
				 काष्ठा regulatory_request *request)
अणु
	u16 country_code;

	अगर (request->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    !ath_is_world_regd(reg))
		वापस -EINVAL;

	country_code = ath_regd_find_country_by_name(request->alpha2);
	अगर (country_code == (u16) -1)
		वापस -EINVAL;

	reg->current_rd = COUNTRY_ERD_FLAG;
	reg->current_rd |= country_code;

	__ath_regd_init(reg);

	ath_reg_apply_world_flags(wiphy, request->initiator, reg);

	वापस 0;
पूर्ण

अटल व्योम ath_reg_dyn_country(काष्ठा wiphy *wiphy,
				काष्ठा ath_regulatory *reg,
				काष्ठा regulatory_request *request)
अणु
	अगर (__ath_reg_dyn_country(wiphy, reg, request))
		वापस;

	prपूर्णांकk(KERN_DEBUG "ath: regdomain 0x%0x "
			  "dynamically updated by %s\n",
	       reg->current_rd,
	       reg_initiator_name(request->initiator));
पूर्ण

व्योम ath_reg_notअगरier_apply(काष्ठा wiphy *wiphy,
			    काष्ठा regulatory_request *request,
			    काष्ठा ath_regulatory *reg)
अणु
	काष्ठा ath_common *common = container_of(reg, काष्ठा ath_common,
						 regulatory);
	/* We always apply this */
	ath_reg_apply_radar_flags(wiphy, reg);

	/*
	 * This would happen when we have sent a custom regulatory request
	 * a world regulatory करोमुख्य and the scheduler hasn't yet processed
	 * any pending requests in the queue.
	 */
	अगर (!request)
		वापस;

	reg->region = request->dfs_region;
	चयन (request->initiator) अणु
	हाल NL80211_REGDOM_SET_BY_CORE:
		/*
		 * If common->reg_world_copy is world roaming it means we *were*
		 * world roaming... so we now have to restore that data.
		 */
		अगर (!ath_is_world_regd(&common->reg_world_copy))
			अवरोध;

		स_नकल(reg, &common->reg_world_copy,
		       माप(काष्ठा ath_regulatory));
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_DRIVER:
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_USER:
		अगर (ath_reg_dyn_country_user_allow(reg))
			ath_reg_dyn_country(wiphy, reg, request);
		अवरोध;
	हाल NL80211_REGDOM_SET_BY_COUNTRY_IE:
		ath_reg_dyn_country(wiphy, reg, request);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath_reg_notअगरier_apply);

अटल bool ath_regd_is_eeprom_valid(काष्ठा ath_regulatory *reg)
अणु
	u16 rd = ath_regd_get_eepromRD(reg);
	पूर्णांक i;

	अगर (rd & COUNTRY_ERD_FLAG) अणु
		/* EEPROM value is a country code */
		u16 cc = rd & ~COUNTRY_ERD_FLAG;
		prपूर्णांकk(KERN_DEBUG
		       "ath: EEPROM indicates we should expect "
			"a country code\n");
		क्रम (i = 0; i < ARRAY_SIZE(allCountries); i++)
			अगर (allCountries[i].countryCode == cc)
				वापस true;
	पूर्ण अन्यथा अणु
		/* EEPROM value is a regpair value */
		अगर (rd != CTRY_DEFAULT)
			prपूर्णांकk(KERN_DEBUG "ath: EEPROM indicates we "
			       "should expect a direct regpair map\n");
		क्रम (i = 0; i < ARRAY_SIZE(regDoमुख्यPairs); i++)
			अगर (regDoमुख्यPairs[i].reg_करोमुख्य == rd)
				वापस true;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG
		 "ath: invalid regulatory domain/country code 0x%x\n", rd);
	वापस false;
पूर्ण

/* EEPROM country code to regpair mapping */
अटल काष्ठा country_code_to_क्रमागत_rd*
ath_regd_find_country(u16 countryCode)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(allCountries); i++) अणु
		अगर (allCountries[i].countryCode == countryCode)
			वापस &allCountries[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/* EEPROM rd code to regpair mapping */
अटल काष्ठा country_code_to_क्रमागत_rd*
ath_regd_find_country_by_rd(पूर्णांक regdmn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(allCountries); i++) अणु
		अगर (allCountries[i].regDmnEnum == regdmn)
			वापस &allCountries[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/* Returns the map of the EEPROM set RD to a country code */
अटल u16 ath_regd_get_शेष_country(u16 rd)
अणु
	अगर (rd & COUNTRY_ERD_FLAG) अणु
		काष्ठा country_code_to_क्रमागत_rd *country = शून्य;
		u16 cc = rd & ~COUNTRY_ERD_FLAG;

		country = ath_regd_find_country(cc);
		अगर (country != शून्य)
			वापस cc;
	पूर्ण

	वापस CTRY_DEFAULT;
पूर्ण

अटल काष्ठा reg_dmn_pair_mapping*
ath_get_regpair(पूर्णांक regdmn)
अणु
	पूर्णांक i;

	अगर (regdmn == NO_ENUMRD)
		वापस शून्य;
	क्रम (i = 0; i < ARRAY_SIZE(regDoमुख्यPairs); i++) अणु
		अगर (regDoमुख्यPairs[i].reg_करोमुख्य == regdmn)
			वापस &regDoमुख्यPairs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
ath_regd_init_wiphy(काष्ठा ath_regulatory *reg,
		    काष्ठा wiphy *wiphy,
		    व्योम (*reg_notअगरier)(काष्ठा wiphy *wiphy,
					 काष्ठा regulatory_request *request))
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regd;

	wiphy->reg_notअगरier = reg_notअगरier;
	wiphy->regulatory_flags |= REGULATORY_STRICT_REG |
				   REGULATORY_CUSTOM_REG;

	अगर (ath_is_world_regd(reg)) अणु
		/*
		 * Anything applied here (prior to wiphy registration) माला_लो
		 * saved on the wiphy orig_* parameters
		 */
		regd = ath_world_regकरोमुख्य(reg);
		wiphy->regulatory_flags |= REGULATORY_COUNTRY_IE_FOLLOW_POWER;
	पूर्ण अन्यथा अणु
		/*
		 * This माला_लो applied in the हाल of the असलence of CRDA,
		 * it's our own custom world regulatory करोमुख्य, similar to
		 * cfg80211's but we enable passive scanning.
		 */
		regd = ath_शेष_world_regकरोमुख्य();
	पूर्ण

	wiphy_apply_custom_regulatory(wiphy, regd);
	ath_reg_apply_radar_flags(wiphy, reg);
	ath_reg_apply_world_flags(wiphy, NL80211_REGDOM_SET_BY_DRIVER, reg);
	वापस 0;
पूर्ण

/*
 * Some users have reported their EEPROM programmed with
 * 0x8000 or 0x0 set, this is not a supported regulatory
 * करोमुख्य but since we have more than one user with it we
 * need a solution क्रम them. We शेष to 0x64, which is
 * the शेष Atheros world regulatory करोमुख्य.
 */
अटल व्योम ath_regd_sanitize(काष्ठा ath_regulatory *reg)
अणु
	अगर (reg->current_rd != COUNTRY_ERD_FLAG && reg->current_rd != 0)
		वापस;
	prपूर्णांकk(KERN_DEBUG "ath: EEPROM regdomain sanitized\n");
	reg->current_rd = 0x64;
पूर्ण

अटल पूर्णांक __ath_regd_init(काष्ठा ath_regulatory *reg)
अणु
	काष्ठा country_code_to_क्रमागत_rd *country = शून्य;
	u16 regdmn;

	अगर (!reg)
		वापस -EINVAL;

	ath_regd_sanitize(reg);

	prपूर्णांकk(KERN_DEBUG "ath: EEPROM regdomain: 0x%0x\n", reg->current_rd);

	अगर (!ath_regd_is_eeprom_valid(reg)) अणु
		pr_err("Invalid EEPROM contents\n");
		वापस -EINVAL;
	पूर्ण

	regdmn = ath_regd_get_eepromRD(reg);
	reg->country_code = ath_regd_get_शेष_country(regdmn);

	अगर (reg->country_code == CTRY_DEFAULT &&
	    regdmn == CTRY_DEFAULT) अणु
		prपूर्णांकk(KERN_DEBUG "ath: EEPROM indicates default "
		       "country code should be used\n");
		reg->country_code = CTRY_UNITED_STATES;
	पूर्ण

	अगर (reg->country_code == CTRY_DEFAULT) अणु
		country = शून्य;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "ath: doing EEPROM country->regdmn "
		       "map search\n");
		country = ath_regd_find_country(reg->country_code);
		अगर (country == शून्य) अणु
			prपूर्णांकk(KERN_DEBUG
				"ath: no valid country maps found for "
				"country code: 0x%0x\n",
				reg->country_code);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			regdmn = country->regDmnEnum;
			prपूर्णांकk(KERN_DEBUG "ath: country maps to "
			       "regdmn code: 0x%0x\n",
			       regdmn);
		पूर्ण
	पूर्ण

	reg->regpair = ath_get_regpair(regdmn);

	अगर (!reg->regpair) अणु
		prपूर्णांकk(KERN_DEBUG "ath: "
			"No regulatory domain pair found, cannot continue\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!country)
		country = ath_regd_find_country_by_rd(regdmn);

	अगर (country) अणु
		reg->alpha2[0] = country->isoName[0];
		reg->alpha2[1] = country->isoName[1];
	पूर्ण अन्यथा अणु
		reg->alpha2[0] = '0';
		reg->alpha2[1] = '0';
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "ath: Country alpha2 being used: %c%c\n",
		reg->alpha2[0], reg->alpha2[1]);
	prपूर्णांकk(KERN_DEBUG "ath: Regpair used: 0x%0x\n",
		reg->regpair->reg_करोमुख्य);

	वापस 0;
पूर्ण

पूर्णांक
ath_regd_init(काष्ठा ath_regulatory *reg,
	      काष्ठा wiphy *wiphy,
	      व्योम (*reg_notअगरier)(काष्ठा wiphy *wiphy,
				   काष्ठा regulatory_request *request))
अणु
	काष्ठा ath_common *common = container_of(reg, काष्ठा ath_common,
						 regulatory);
	पूर्णांक r;

	r = __ath_regd_init(reg);
	अगर (r)
		वापस r;

	अगर (ath_is_world_regd(reg))
		स_नकल(&common->reg_world_copy, reg,
		       माप(काष्ठा ath_regulatory));

	ath_regd_init_wiphy(reg, wiphy, reg_notअगरier);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath_regd_init);

u32 ath_regd_get_band_ctl(काष्ठा ath_regulatory *reg,
			  क्रमागत nl80211_band band)
अणु
	अगर (!reg->regpair ||
	    (reg->country_code == CTRY_DEFAULT &&
	     is_wwr_sku(ath_regd_get_eepromRD(reg)))) अणु
		वापस SD_NO_CTL;
	पूर्ण

	अगर (ath_regd_get_eepromRD(reg) == CTRY_DEFAULT) अणु
		चयन (reg->region) अणु
		हाल NL80211_DFS_FCC:
			वापस CTL_FCC;
		हाल NL80211_DFS_ETSI:
			वापस CTL_ETSI;
		हाल NL80211_DFS_JP:
			वापस CTL_MKK;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		वापस reg->regpair->reg_2ghz_ctl;
	हाल NL80211_BAND_5GHZ:
		वापस reg->regpair->reg_5ghz_ctl;
	शेष:
		वापस NO_CTL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath_regd_get_band_ctl);
