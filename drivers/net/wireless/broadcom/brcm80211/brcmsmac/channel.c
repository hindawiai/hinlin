<शैली गुरु>
/*
 * Copyright (c) 2010 Broadcom Corporation
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/types.h>
#समावेश <net/cfg80211.h>
#समावेश <net/mac80211.h>
#समावेश <net/regulatory.h>

#समावेश <defs.h>
#समावेश "pub.h"
#समावेश "phy/phy_hal.h"
#समावेश "main.h"
#समावेश "stf.h"
#समावेश "channel.h"
#समावेश "mac80211_if.h"
#समावेश "debug.h"

/* QDB() macro takes a dB value and converts to a quarter dB value */
#घोषणा QDB(n) ((n) * BRCMS_TXPWR_DB_FACTOR)

#घोषणा LOCALE_MIMO_IDX_bn		0
#घोषणा LOCALE_MIMO_IDX_11n		0

/* max of BAND_5G_PWR_LVLS and 14 क्रम 2.4 GHz */
#घोषणा BRCMS_MAXPWR_MIMO_TBL_SIZE	14

/* maxpwr mapping to 5GHz band channels:
 * maxpwr[0] - channels [34-48]
 * maxpwr[1] - channels [52-60]
 * maxpwr[2] - channels [62-64]
 * maxpwr[3] - channels [100-140]
 * maxpwr[4] - channels [149-165]
 */
#घोषणा BAND_5G_PWR_LVLS	5	/* 5 घातer levels क्रम 5G */

#घोषणा LC(id)	LOCALE_MIMO_IDX_ ## id

#घोषणा LOCALES(mimo2, mimo5) \
		अणुLC(mimo2), LC(mimo5)पूर्ण

/* macro to get 5 GHz channel group index क्रम tx घातer */
#घोषणा CHANNEL_POWER_IDX_5G(c) (((c) < 52) ? 0 : \
				 (((c) < 62) ? 1 : \
				 (((c) < 100) ? 2 : \
				 (((c) < 149) ? 3 : 4))))

#घोषणा BRCM_2GHZ_2412_2462	REG_RULE(2412-10, 2462+10, 40, 0, 19, 0)
#घोषणा BRCM_2GHZ_2467_2472	REG_RULE(2467-10, 2472+10, 20, 0, 19, \
					 NL80211_RRF_NO_IR)

#घोषणा BRCM_5GHZ_5180_5240	REG_RULE(5180-10, 5240+10, 40, 0, 21, \
					 NL80211_RRF_NO_IR)
#घोषणा BRCM_5GHZ_5260_5320	REG_RULE(5260-10, 5320+10, 40, 0, 21, \
					 NL80211_RRF_DFS | \
					 NL80211_RRF_NO_IR)
#घोषणा BRCM_5GHZ_5500_5700	REG_RULE(5500-10, 5700+10, 40, 0, 21, \
					 NL80211_RRF_DFS | \
					 NL80211_RRF_NO_IR)
#घोषणा BRCM_5GHZ_5745_5825	REG_RULE(5745-10, 5825+10, 40, 0, 21, \
					 NL80211_RRF_NO_IR)

अटल स्थिर काष्ठा ieee80211_regकरोमुख्य brcms_regकरोm_x2 = अणु
	.n_reg_rules = 6,
	.alpha2 = "X2",
	.reg_rules = अणु
		BRCM_2GHZ_2412_2462,
		BRCM_2GHZ_2467_2472,
		BRCM_5GHZ_5180_5240,
		BRCM_5GHZ_5260_5320,
		BRCM_5GHZ_5500_5700,
		BRCM_5GHZ_5745_5825,
	पूर्ण
पूर्ण;

 /* locale per-channel tx घातer limits क्रम MIMO frames
  * maxpwr arrays are index by channel क्रम 2.4 GHz limits, and
  * by sub-band क्रम 5 GHz limits using CHANNEL_POWER_IDX_5G(channel)
  */
काष्ठा locale_mimo_info अणु
	/* tx 20 MHz घातer limits, qdBm units */
	s8 maxpwr20[BRCMS_MAXPWR_MIMO_TBL_SIZE];
	/* tx 40 MHz घातer limits, qdBm units */
	s8 maxpwr40[BRCMS_MAXPWR_MIMO_TBL_SIZE];
पूर्ण;

/* Country names and abbreviations with locale defined from ISO 3166 */
काष्ठा country_info अणु
	स्थिर u8 locale_mimo_2G;	/* 2.4G mimo info */
	स्थिर u8 locale_mimo_5G;	/* 5G mimo info */
पूर्ण;

काष्ठा brcms_regd अणु
	काष्ठा country_info country;
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोमुख्य;
पूर्ण;

काष्ठा brcms_cm_info अणु
	काष्ठा brcms_pub *pub;
	काष्ठा brcms_c_info *wlc;
	स्थिर काष्ठा brcms_regd *world_regd;
पूर्ण;

/*
 * MIMO Locale Definitions - 2.4 GHz
 */
अटल स्थिर काष्ठा locale_mimo_info locale_bn = अणु
	अणुQDB(13), QDB(13), QDB(13), QDB(13), QDB(13),
	 QDB(13), QDB(13), QDB(13), QDB(13), QDB(13),
	 QDB(13), QDB(13), QDB(13)पूर्ण,
	अणु0, 0, QDB(13), QDB(13), QDB(13),
	 QDB(13), QDB(13), QDB(13), QDB(13), QDB(13),
	 QDB(13), 0, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा locale_mimo_info *g_mimo_2g_table[] = अणु
	&locale_bn
पूर्ण;

/*
 * MIMO Locale Definitions - 5 GHz
 */
अटल स्थिर काष्ठा locale_mimo_info locale_11n = अणु
	अणु /* 12.5 dBm */ 50, 50, 50, QDB(15), QDB(15)पूर्ण,
	अणुQDB(14), QDB(15), QDB(15), QDB(15), QDB(15)पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा locale_mimo_info *g_mimo_5g_table[] = अणु
	&locale_11n
पूर्ण;

अटल स्थिर काष्ठा brcms_regd cntry_locales[] = अणु
	/* Worldwide RoW 2, must always be at index 0 */
	अणु
		.country = LOCALES(bn, 11n),
		.regकरोमुख्य = &brcms_regकरोm_x2,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा locale_mimo_info *brcms_c_get_mimo_2g(u8 locale_idx)
अणु
	अगर (locale_idx >= ARRAY_SIZE(g_mimo_2g_table))
		वापस शून्य;

	वापस g_mimo_2g_table[locale_idx];
पूर्ण

अटल स्थिर काष्ठा locale_mimo_info *brcms_c_get_mimo_5g(u8 locale_idx)
अणु
	अगर (locale_idx >= ARRAY_SIZE(g_mimo_5g_table))
		वापस शून्य;

	वापस g_mimo_5g_table[locale_idx];
पूर्ण

/*
 * Indicates whether the country provided is valid to pass
 * to cfg80211 or not.
 *
 * वापसs true अगर valid; false अगर not.
 */
अटल bool brcms_c_country_valid(स्थिर अक्षर *ccode)
अणु
	/*
	 * only allow ascii alpha upperहाल क्रम the first 2
	 * अक्षरs.
	 */
	अगर (!((ccode[0] & 0x80) == 0 && ccode[0] >= 0x41 && ccode[0] <= 0x5A &&
	      (ccode[1] & 0x80) == 0 && ccode[1] >= 0x41 && ccode[1] <= 0x5A))
		वापस false;

	/*
	 * करो not match ISO 3166-1 user asचिन्हित country codes
	 * that may be in the driver table
	 */
	अगर (!म_भेद("AA", ccode) ||        /* AA */
	    !म_भेद("ZZ", ccode) ||        /* ZZ */
	    ccode[0] == 'X' ||             /* XA - XZ */
	    (ccode[0] == 'Q' &&            /* QM - QZ */
	     (ccode[1] >= 'M' && ccode[1] <= 'Z')))
		वापस false;

	अगर (!म_भेद("NA", ccode))
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा brcms_regd *brcms_world_regd(स्थिर अक्षर *regकरोm, पूर्णांक len)
अणु
	स्थिर काष्ठा brcms_regd *regd = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cntry_locales); i++) अणु
		अगर (!म_भेदन(regकरोm, cntry_locales[i].regकरोमुख्य->alpha2, len)) अणु
			regd = &cntry_locales[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस regd;
पूर्ण

अटल स्थिर काष्ठा brcms_regd *brcms_शेष_world_regd(व्योम)
अणु
	वापस &cntry_locales[0];
पूर्ण

/* JP, J1 - J10 are Japan ccodes */
अटल bool brcms_c_japan_ccode(स्थिर अक्षर *ccode)
अणु
	वापस (ccode[0] == 'J' &&
		(ccode[1] == 'P' || (ccode[1] >= '1' && ccode[1] <= '9')));
पूर्ण

अटल व्योम
brcms_c_channel_min_txघातer_limits_with_local_स्थिरraपूर्णांक(
		काष्ठा brcms_cm_info *wlc_cm, काष्ठा txpwr_limits *txpwr,
		u8 local_स्थिरraपूर्णांक_qdbm)
अणु
	पूर्णांक j;

	/* CCK Rates */
	क्रम (j = 0; j < WL_TX_POWER_CCK_NUM; j++)
		txpwr->cck[j] = min(txpwr->cck[j], local_स्थिरraपूर्णांक_qdbm);

	/* 20 MHz Legacy OFDM SISO */
	क्रम (j = 0; j < WL_TX_POWER_OFDM_NUM; j++)
		txpwr->ofdm[j] = min(txpwr->ofdm[j], local_स्थिरraपूर्णांक_qdbm);

	/* 20 MHz Legacy OFDM CDD */
	क्रम (j = 0; j < BRCMS_NUM_RATES_OFDM; j++)
		txpwr->ofdm_cdd[j] =
		    min(txpwr->ofdm_cdd[j], local_स्थिरraपूर्णांक_qdbm);

	/* 40 MHz Legacy OFDM SISO */
	क्रम (j = 0; j < BRCMS_NUM_RATES_OFDM; j++)
		txpwr->ofdm_40_siso[j] =
		    min(txpwr->ofdm_40_siso[j], local_स्थिरraपूर्णांक_qdbm);

	/* 40 MHz Legacy OFDM CDD */
	क्रम (j = 0; j < BRCMS_NUM_RATES_OFDM; j++)
		txpwr->ofdm_40_cdd[j] =
		    min(txpwr->ofdm_40_cdd[j], local_स्थिरraपूर्णांक_qdbm);

	/* 20MHz MCS 0-7 SISO */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_20_siso[j] =
		    min(txpwr->mcs_20_siso[j], local_स्थिरraपूर्णांक_qdbm);

	/* 20MHz MCS 0-7 CDD */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_20_cdd[j] =
		    min(txpwr->mcs_20_cdd[j], local_स्थिरraपूर्णांक_qdbm);

	/* 20MHz MCS 0-7 STBC */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_20_stbc[j] =
		    min(txpwr->mcs_20_stbc[j], local_स्थिरraपूर्णांक_qdbm);

	/* 20MHz MCS 8-15 MIMO */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_2_STREAM; j++)
		txpwr->mcs_20_mimo[j] =
		    min(txpwr->mcs_20_mimo[j], local_स्थिरraपूर्णांक_qdbm);

	/* 40MHz MCS 0-7 SISO */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_40_siso[j] =
		    min(txpwr->mcs_40_siso[j], local_स्थिरraपूर्णांक_qdbm);

	/* 40MHz MCS 0-7 CDD */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_40_cdd[j] =
		    min(txpwr->mcs_40_cdd[j], local_स्थिरraपूर्णांक_qdbm);

	/* 40MHz MCS 0-7 STBC */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_1_STREAM; j++)
		txpwr->mcs_40_stbc[j] =
		    min(txpwr->mcs_40_stbc[j], local_स्थिरraपूर्णांक_qdbm);

	/* 40MHz MCS 8-15 MIMO */
	क्रम (j = 0; j < BRCMS_NUM_RATES_MCS_2_STREAM; j++)
		txpwr->mcs_40_mimo[j] =
		    min(txpwr->mcs_40_mimo[j], local_स्थिरraपूर्णांक_qdbm);

	/* 40MHz MCS 32 */
	txpwr->mcs32 = min(txpwr->mcs32, local_स्थिरraपूर्णांक_qdbm);

पूर्ण

/*
 * set the driver's current country and regulatory inक्रमmation
 * using a country code as the source. Look up built in country
 * inक्रमmation found with the country code.
 */
अटल व्योम
brcms_c_set_country(काष्ठा brcms_cm_info *wlc_cm,
		    स्थिर काष्ठा brcms_regd *regd)
अणु
	काष्ठा brcms_c_info *wlc = wlc_cm->wlc;

	अगर ((wlc->pub->_n_enab & SUPPORT_11N) !=
	    wlc->protection->nmode_user)
		brcms_c_set_nmode(wlc);

	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_2G_INDEX]);
	brcms_c_stf_ss_update(wlc, wlc->bandstate[BAND_5G_INDEX]);

	brcms_c_set_gmode(wlc, wlc->protection->gmode_user, false);

	वापस;
पूर्ण

काष्ठा brcms_cm_info *brcms_c_channel_mgr_attach(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा brcms_cm_info *wlc_cm;
	काष्ठा brcms_pub *pub = wlc->pub;
	काष्ठा ssb_sprom *sprom = &wlc->hw->d11core->bus->sprom;
	स्थिर अक्षर *ccode = sprom->alpha2;
	पूर्णांक ccode_len = माप(sprom->alpha2);

	wlc_cm = kzalloc(माप(काष्ठा brcms_cm_info), GFP_ATOMIC);
	अगर (wlc_cm == शून्य)
		वापस शून्य;
	wlc_cm->pub = pub;
	wlc_cm->wlc = wlc;
	wlc->cmi = wlc_cm;

	/* store the country code क्रम passing up as a regulatory hपूर्णांक */
	wlc_cm->world_regd = brcms_world_regd(ccode, ccode_len);
	अगर (brcms_c_country_valid(ccode))
		म_नकलन(wlc->pub->srom_ccode, ccode, ccode_len);

	/*
	 * If no custom world करोमुख्य is found in the SROM, use the
	 * शेष "X2" करोमुख्य.
	 */
	अगर (!wlc_cm->world_regd) अणु
		wlc_cm->world_regd = brcms_शेष_world_regd();
		ccode = wlc_cm->world_regd->regकरोमुख्य->alpha2;
		ccode_len = BRCM_CNTRY_BUF_SZ - 1;
	पूर्ण

	/* save शेष country क्रम निकासing 11d regulatory mode */
	म_नकलन(wlc->country_शेष, ccode, ccode_len);

	/* initialize स्वतःcountry_शेष to driver शेष */
	म_नकलन(wlc->स्वतःcountry_शेष, ccode, ccode_len);

	brcms_c_set_country(wlc_cm, wlc_cm->world_regd);

	वापस wlc_cm;
पूर्ण

व्योम brcms_c_channel_mgr_detach(काष्ठा brcms_cm_info *wlc_cm)
अणु
	kमुक्त(wlc_cm);
पूर्ण

व्योम
brcms_c_channel_set_chanspec(काष्ठा brcms_cm_info *wlc_cm, u16 chanspec,
			 u8 local_स्थिरraपूर्णांक_qdbm)
अणु
	काष्ठा brcms_c_info *wlc = wlc_cm->wlc;
	काष्ठा ieee80211_channel *ch = wlc->pub->ieee_hw->conf.chandef.chan;
	काष्ठा txpwr_limits txpwr;

	brcms_c_channel_reg_limits(wlc_cm, chanspec, &txpwr);

	brcms_c_channel_min_txघातer_limits_with_local_स्थिरraपूर्णांक(
		wlc_cm, &txpwr, local_स्थिरraपूर्णांक_qdbm
	);

	/* set or restore gmode as required by regulatory */
	अगर (ch->flags & IEEE80211_CHAN_NO_OFDM)
		brcms_c_set_gmode(wlc, GMODE_LEGACY_B, false);
	अन्यथा
		brcms_c_set_gmode(wlc, wlc->protection->gmode_user, false);

	brcms_b_set_chanspec(wlc->hw, chanspec,
			      !!(ch->flags & IEEE80211_CHAN_NO_IR),
			      &txpwr);
पूर्ण

व्योम
brcms_c_channel_reg_limits(काष्ठा brcms_cm_info *wlc_cm, u16 chanspec,
		       काष्ठा txpwr_limits *txpwr)
अणु
	काष्ठा brcms_c_info *wlc = wlc_cm->wlc;
	काष्ठा ieee80211_channel *ch = wlc->pub->ieee_hw->conf.chandef.chan;
	uपूर्णांक i;
	uपूर्णांक chan;
	पूर्णांक maxpwr;
	पूर्णांक delta;
	स्थिर काष्ठा country_info *country;
	काष्ठा brcms_band *band;
	पूर्णांक conducted_max = BRCMS_TXPWR_MAX;
	स्थिर काष्ठा locale_mimo_info *li_mimo;
	पूर्णांक maxpwr20, maxpwr40;
	पूर्णांक maxpwr_idx;
	uपूर्णांक j;

	स_रखो(txpwr, 0, माप(काष्ठा txpwr_limits));

	अगर (WARN_ON(!ch))
		वापस;

	country = &wlc_cm->world_regd->country;

	chan = CHSPEC_CHANNEL(chanspec);
	band = wlc->bandstate[chspec_bandunit(chanspec)];
	li_mimo = (band->bandtype == BRCM_BAND_5G) ?
	    brcms_c_get_mimo_5g(country->locale_mimo_5G) :
	    brcms_c_get_mimo_2g(country->locale_mimo_2G);

	delta = band->antgain;

	अगर (band->bandtype == BRCM_BAND_2G)
		conducted_max = QDB(22);

	maxpwr = QDB(ch->max_घातer) - delta;
	maxpwr = max(maxpwr, 0);
	maxpwr = min(maxpwr, conducted_max);

	/* CCK txpwr limits क्रम 2.4G band */
	अगर (band->bandtype == BRCM_BAND_2G) अणु
		क्रम (i = 0; i < BRCMS_NUM_RATES_CCK; i++)
			txpwr->cck[i] = (u8) maxpwr;
	पूर्ण

	क्रम (i = 0; i < BRCMS_NUM_RATES_OFDM; i++) अणु
		txpwr->ofdm[i] = (u8) maxpwr;

		/*
		 * OFDM 40 MHz SISO has the same घातer as the corresponding
		 * MCS0-7 rate unless overriden by the locale specअगरic code.
		 * We set this value to 0 as a flag (presumably 0 dBm isn't
		 * a possibility) and then copy the MCS0-7 value to the 40 MHz
		 * value अगर it wasn't explicitly set.
		 */
		txpwr->ofdm_40_siso[i] = 0;

		txpwr->ofdm_cdd[i] = (u8) maxpwr;

		txpwr->ofdm_40_cdd[i] = 0;
	पूर्ण

	delta = 0;
	अगर (band->antgain > QDB(6))
		delta = band->antgain - QDB(6);	/* Excess over 6 dB */

	अगर (band->bandtype == BRCM_BAND_2G)
		maxpwr_idx = (chan - 1);
	अन्यथा
		maxpwr_idx = CHANNEL_POWER_IDX_5G(chan);

	maxpwr20 = li_mimo->maxpwr20[maxpwr_idx];
	maxpwr40 = li_mimo->maxpwr40[maxpwr_idx];

	maxpwr20 = maxpwr20 - delta;
	maxpwr20 = max(maxpwr20, 0);
	maxpwr40 = maxpwr40 - delta;
	maxpwr40 = max(maxpwr40, 0);

	/* Fill in the MCS 0-7 (SISO) rates */
	क्रम (i = 0; i < BRCMS_NUM_RATES_MCS_1_STREAM; i++) अणु

		/*
		 * 20 MHz has the same घातer as the corresponding OFDM rate
		 * unless overriden by the locale specअगरic code.
		 */
		txpwr->mcs_20_siso[i] = txpwr->ofdm[i];
		txpwr->mcs_40_siso[i] = 0;
	पूर्ण

	/* Fill in the MCS 0-7 CDD rates */
	क्रम (i = 0; i < BRCMS_NUM_RATES_MCS_1_STREAM; i++) अणु
		txpwr->mcs_20_cdd[i] = (u8) maxpwr20;
		txpwr->mcs_40_cdd[i] = (u8) maxpwr40;
	पूर्ण

	/*
	 * These locales have SISO expressed in the
	 * table and override CDD later
	 */
	अगर (li_mimo == &locale_bn) अणु
		maxpwr20 = QDB(16);
		maxpwr40 = 0;

		अगर (chan >= 3 && chan <= 11)
			maxpwr40 = QDB(16);

		क्रम (i = 0; i < BRCMS_NUM_RATES_MCS_1_STREAM; i++) अणु
			txpwr->mcs_20_siso[i] = (u8) maxpwr20;
			txpwr->mcs_40_siso[i] = (u8) maxpwr40;
		पूर्ण
	पूर्ण

	/* Fill in the MCS 0-7 STBC rates */
	क्रम (i = 0; i < BRCMS_NUM_RATES_MCS_1_STREAM; i++) अणु
		txpwr->mcs_20_stbc[i] = 0;
		txpwr->mcs_40_stbc[i] = 0;
	पूर्ण

	/* Fill in the MCS 8-15 SDM rates */
	क्रम (i = 0; i < BRCMS_NUM_RATES_MCS_2_STREAM; i++) अणु
		txpwr->mcs_20_mimo[i] = (u8) maxpwr20;
		txpwr->mcs_40_mimo[i] = (u8) maxpwr40;
	पूर्ण

	/* Fill in MCS32 */
	txpwr->mcs32 = (u8) maxpwr40;

	क्रम (i = 0, j = 0; i < BRCMS_NUM_RATES_OFDM; i++, j++) अणु
		अगर (txpwr->ofdm_40_cdd[i] == 0)
			txpwr->ofdm_40_cdd[i] = txpwr->mcs_40_cdd[j];
		अगर (i == 0) अणु
			i = i + 1;
			अगर (txpwr->ofdm_40_cdd[i] == 0)
				txpwr->ofdm_40_cdd[i] = txpwr->mcs_40_cdd[j];
		पूर्ण
	पूर्ण

	/*
	 * Copy the 40 MHZ MCS 0-7 CDD value to the 40 MHZ MCS 0-7 SISO
	 * value अगर it wasn't provided explicitly.
	 */
	क्रम (i = 0; i < BRCMS_NUM_RATES_MCS_1_STREAM; i++) अणु
		अगर (txpwr->mcs_40_siso[i] == 0)
			txpwr->mcs_40_siso[i] = txpwr->mcs_40_cdd[i];
	पूर्ण

	क्रम (i = 0, j = 0; i < BRCMS_NUM_RATES_OFDM; i++, j++) अणु
		अगर (txpwr->ofdm_40_siso[i] == 0)
			txpwr->ofdm_40_siso[i] = txpwr->mcs_40_siso[j];
		अगर (i == 0) अणु
			i = i + 1;
			अगर (txpwr->ofdm_40_siso[i] == 0)
				txpwr->ofdm_40_siso[i] = txpwr->mcs_40_siso[j];
		पूर्ण
	पूर्ण

	/*
	 * Copy the 20 and 40 MHz MCS0-7 CDD values to the corresponding
	 * STBC values अगर they weren't provided explicitly.
	 */
	क्रम (i = 0; i < BRCMS_NUM_RATES_MCS_1_STREAM; i++) अणु
		अगर (txpwr->mcs_20_stbc[i] == 0)
			txpwr->mcs_20_stbc[i] = txpwr->mcs_20_cdd[i];

		अगर (txpwr->mcs_40_stbc[i] == 0)
			txpwr->mcs_40_stbc[i] = txpwr->mcs_40_cdd[i];
	पूर्ण

	वापस;
पूर्ण

/*
 * Verअगरy the chanspec is using a legal set of parameters, i.e. that the
 * chanspec specअगरied a band, bw, ctl_sb and channel and that the
 * combination could be legal given any set of circumstances.
 * RETURNS: true is the chanspec is malक्रमmed, false अगर it looks good.
 */
अटल bool brcms_c_chspec_malक्रमmed(u16 chanspec)
अणु
	/* must be 2G or 5G band */
	अगर (!CHSPEC_IS5G(chanspec) && !CHSPEC_IS2G(chanspec))
		वापस true;
	/* must be 20 or 40 bandwidth */
	अगर (!CHSPEC_IS40(chanspec) && !CHSPEC_IS20(chanspec))
		वापस true;

	/* 20MHZ b/w must have no ctl sb, 40 must have a ctl sb */
	अगर (CHSPEC_IS20(chanspec)) अणु
		अगर (!CHSPEC_SB_NONE(chanspec))
			वापस true;
	पूर्ण अन्यथा अगर (!CHSPEC_SB_UPPER(chanspec) && !CHSPEC_SB_LOWER(chanspec)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Validate the chanspec क्रम this locale, क्रम 40MHZ we need to also
 * check that the sidebands are valid 20MZH channels in this locale
 * and they are also a legal HT combination
 */
अटल bool
brcms_c_valid_chanspec_ext(काष्ठा brcms_cm_info *wlc_cm, u16 chspec)
अणु
	काष्ठा brcms_c_info *wlc = wlc_cm->wlc;
	u8 channel = CHSPEC_CHANNEL(chspec);

	/* check the chanspec */
	अगर (brcms_c_chspec_malक्रमmed(chspec)) अणु
		brcms_err(wlc->hw->d11core, "wl%d: malformed chanspec 0x%x\n",
			  wlc->pub->unit, chspec);
		वापस false;
	पूर्ण

	अगर (CHANNEL_BANDUNIT(wlc_cm->wlc, channel) !=
	    chspec_bandunit(chspec))
		वापस false;

	वापस true;
पूर्ण

bool brcms_c_valid_chanspec_db(काष्ठा brcms_cm_info *wlc_cm, u16 chspec)
अणु
	वापस brcms_c_valid_chanspec_ext(wlc_cm, chspec);
पूर्ण

अटल bool brcms_is_radar_freq(u16 center_freq)
अणु
	वापस center_freq >= 5260 && center_freq <= 5700;
पूर्ण

अटल व्योम brcms_reg_apply_radar_flags(काष्ठा wiphy *wiphy)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	पूर्णांक i;

	sband = wiphy->bands[NL80211_BAND_5GHZ];
	अगर (!sband)
		वापस;

	क्रम (i = 0; i < sband->n_channels; i++) अणु
		ch = &sband->channels[i];

		अगर (!brcms_is_radar_freq(ch->center_freq))
			जारी;

		/*
		 * All channels in this range should be passive and have
		 * DFS enabled.
		 */
		अगर (!(ch->flags & IEEE80211_CHAN_DISABLED))
			ch->flags |= IEEE80211_CHAN_RADAR |
				     IEEE80211_CHAN_NO_IR;
	पूर्ण
पूर्ण

अटल व्योम
brcms_reg_apply_beaconing_flags(काष्ठा wiphy *wiphy,
				क्रमागत nl80211_reg_initiator initiator)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	स्थिर काष्ठा ieee80211_reg_rule *rule;
	पूर्णांक band, i;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		sband = wiphy->bands[band];
		अगर (!sband)
			जारी;

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			ch = &sband->channels[i];

			अगर (ch->flags &
			    (IEEE80211_CHAN_DISABLED | IEEE80211_CHAN_RADAR))
				जारी;

			अगर (initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE) अणु
				rule = freq_reg_info(wiphy,
						     MHZ_TO_KHZ(ch->center_freq));
				अगर (IS_ERR(rule))
					जारी;

				अगर (!(rule->flags & NL80211_RRF_NO_IR))
					ch->flags &= ~IEEE80211_CHAN_NO_IR;
			पूर्ण अन्यथा अगर (ch->beacon_found) अणु
				ch->flags &= ~IEEE80211_CHAN_NO_IR;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम brcms_reg_notअगरier(काष्ठा wiphy *wiphy,
			       काष्ठा regulatory_request *request)
अणु
	काष्ठा ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	काष्ठा brcms_info *wl = hw->priv;
	काष्ठा brcms_c_info *wlc = wl->wlc;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	पूर्णांक band, i;
	bool ch_found = false;

	brcms_reg_apply_radar_flags(wiphy);

	अगर (request->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE)
		brcms_reg_apply_beaconing_flags(wiphy, request->initiator);

	/* Disable radio अगर all channels disallowed by regulatory */
	क्रम (band = 0; !ch_found && band < NUM_NL80211_BANDS; band++) अणु
		sband = wiphy->bands[band];
		अगर (!sband)
			जारी;

		क्रम (i = 0; !ch_found && i < sband->n_channels; i++) अणु
			ch = &sband->channels[i];

			अगर (!(ch->flags & IEEE80211_CHAN_DISABLED))
				ch_found = true;
		पूर्ण
	पूर्ण

	अगर (ch_found) अणु
		mboolclr(wlc->pub->radio_disabled, WL_RADIO_COUNTRY_DISABLE);
	पूर्ण अन्यथा अणु
		mboolset(wlc->pub->radio_disabled, WL_RADIO_COUNTRY_DISABLE);
		brcms_err(wlc->hw->d11core,
			  "wl%d: %s: no valid channel for \"%s\"\n",
			  wlc->pub->unit, __func__, request->alpha2);
	पूर्ण

	अगर (wlc->pub->_nbands > 1 || wlc->band->bandtype == BRCM_BAND_2G)
		wlc_phy_chanspec_ch14_widefilter_set(wlc->band->pi,
					brcms_c_japan_ccode(request->alpha2));
पूर्ण

व्योम brcms_c_regd_init(काष्ठा brcms_c_info *wlc)
अणु
	काष्ठा wiphy *wiphy = wlc->wiphy;
	स्थिर काष्ठा brcms_regd *regd = wlc->cmi->world_regd;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *ch;
	काष्ठा brcms_chanvec sup_chan;
	काष्ठा brcms_band *band;
	पूर्णांक band_idx, i;

	/* Disable any channels not supported by the phy */
	क्रम (band_idx = 0; band_idx < wlc->pub->_nbands; band_idx++) अणु
		band = wlc->bandstate[band_idx];

		wlc_phy_chanspec_band_validch(band->pi, band->bandtype,
					      &sup_chan);

		अगर (band_idx == BAND_2G_INDEX)
			sband = wiphy->bands[NL80211_BAND_2GHZ];
		अन्यथा
			sband = wiphy->bands[NL80211_BAND_5GHZ];

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			ch = &sband->channels[i];
			अगर (!isset(sup_chan.vec, ch->hw_value))
				ch->flags |= IEEE80211_CHAN_DISABLED;
		पूर्ण
	पूर्ण

	wlc->wiphy->reg_notअगरier = brcms_reg_notअगरier;
	wlc->wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
					REGULATORY_STRICT_REG;
	wiphy_apply_custom_regulatory(wlc->wiphy, regd->regकरोमुख्य);
	brcms_reg_apply_beaconing_flags(wiphy, NL80211_REGDOM_SET_BY_DRIVER);
पूर्ण
