<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
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

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश "hw.h"
#समावेश "hw-ops.h"

काष्ठा ani_ofdm_level_entry अणु
	पूर्णांक spur_immunity_level;
	पूर्णांक fir_step_level;
	पूर्णांक ofdm_weak_संकेत_on;
पूर्ण;

/* values here are relative to the INI */

/*
 * Legend:
 *
 * SI: Spur immunity
 * FS: FIR Step
 * WS: OFDM / CCK Weak Signal detection
 * MRC-CCK: Maximal Ratio Combining क्रम CCK
 */

अटल स्थिर काष्ठा ani_ofdm_level_entry ofdm_level_table[] = अणु
	/* SI  FS  WS */
	अणु  0,  0,  1  पूर्ण, /* lvl 0 */
	अणु  1,  1,  1  पूर्ण, /* lvl 1 */
	अणु  2,  2,  1  पूर्ण, /* lvl 2 */
	अणु  3,  2,  1  पूर्ण, /* lvl 3  (शेष) */
	अणु  4,  3,  1  पूर्ण, /* lvl 4 */
	अणु  5,  4,  1  पूर्ण, /* lvl 5 */
	अणु  6,  5,  1  पूर्ण, /* lvl 6 */
	अणु  7,  6,  1  पूर्ण, /* lvl 7 */
	अणु  7,  7,  1  पूर्ण, /* lvl 8 */
	अणु  7,  8,  0  पूर्ण  /* lvl 9 */
पूर्ण;
#घोषणा ATH9K_ANI_OFDM_NUM_LEVEL \
	ARRAY_SIZE(ofdm_level_table)
#घोषणा ATH9K_ANI_OFDM_MAX_LEVEL \
	(ATH9K_ANI_OFDM_NUM_LEVEL-1)
#घोषणा ATH9K_ANI_OFDM_DEF_LEVEL \
	3 /* शेष level - matches the INI settings */

/*
 * MRC (Maximal Ratio Combining) has always been used with multi-antenna ofdm.
 * With OFDM क्रम single stream you just add up all antenna inमाला_दो, you're
 * only पूर्णांकerested in what you get after FFT. Signal alignment is also not
 * required क्रम OFDM because any phase dअगरference adds up in the frequency
 * करोमुख्य.
 *
 * MRC requires extra work क्रम use with CCK. You need to align the antenna
 * संकेतs from the dअगरferent antenna beक्रमe you can add the संकेतs together.
 * You need alignment of संकेतs as CCK is in समय करोमुख्य, so addition can cancel
 * your संकेत completely अगर phase is 180 degrees (think of adding sine waves).
 * You also need to हटाओ noise beक्रमe the addition and this is where ANI
 * MRC CCK comes पूर्णांकo play. One of the antenna inमाला_दो may be stronger but
 * lower SNR, so just adding after alignment can be dangerous.
 *
 * Regardless of alignment in समय, the antenna संकेतs add स्थिरructively after
 * FFT and improve your reception. For more inक्रमmation:
 *
 * https://en.wikipedia.org/wiki/Maximal-ratio_combining
 */

काष्ठा ani_cck_level_entry अणु
	पूर्णांक fir_step_level;
	पूर्णांक mrc_cck_on;
पूर्ण;

अटल स्थिर काष्ठा ani_cck_level_entry cck_level_table[] = अणु
	/* FS  MRC-CCK  */
	अणु  0,  1  पूर्ण, /* lvl 0 */
	अणु  1,  1  पूर्ण, /* lvl 1 */
	अणु  2,  1  पूर्ण, /* lvl 2  (शेष) */
	अणु  3,  1  पूर्ण, /* lvl 3 */
	अणु  4,  0  पूर्ण, /* lvl 4 */
	अणु  5,  0  पूर्ण, /* lvl 5 */
	अणु  6,  0  पूर्ण, /* lvl 6 */
	अणु  7,  0  पूर्ण, /* lvl 7 (only क्रम high rssi) */
	अणु  8,  0  पूर्ण  /* lvl 8 (only क्रम high rssi) */
पूर्ण;

#घोषणा ATH9K_ANI_CCK_NUM_LEVEL \
	ARRAY_SIZE(cck_level_table)
#घोषणा ATH9K_ANI_CCK_MAX_LEVEL \
	(ATH9K_ANI_CCK_NUM_LEVEL-1)
#घोषणा ATH9K_ANI_CCK_MAX_LEVEL_LOW_RSSI \
	(ATH9K_ANI_CCK_NUM_LEVEL-3)
#घोषणा ATH9K_ANI_CCK_DEF_LEVEL \
	2 /* शेष level - matches the INI settings */

अटल व्योम ath9k_hw_update_mibstats(काष्ठा ath_hw *ah,
				     काष्ठा ath9k_mib_stats *stats)
अणु
	u32 addr[5] = अणुAR_RTS_OK, AR_RTS_FAIL, AR_ACK_FAIL,
		       AR_FCS_FAIL, AR_BEACON_CNTपूर्ण;
	u32 data[5];

	REG_READ_MULTI(ah, &addr[0], &data[0], 5);
	/* AR_RTS_OK */
	stats->rts_good += data[0];
	/* AR_RTS_FAIL */
	stats->rts_bad += data[1];
	/* AR_ACK_FAIL */
	stats->ackrcv_bad += data[2];
	/* AR_FCS_FAIL */
	stats->fcs_bad += data[3];
	/* AR_BEACON_CNT */
	stats->beacons += data[4];
पूर्ण

अटल व्योम ath9k_ani_restart(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;

	aniState->listenTime = 0;

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_PHY_ERR_1, 0);
	REG_WRITE(ah, AR_PHY_ERR_2, 0);
	REG_WRITE(ah, AR_PHY_ERR_MASK_1, AR_PHY_ERR_OFDM_TIMING);
	REG_WRITE(ah, AR_PHY_ERR_MASK_2, AR_PHY_ERR_CCK_TIMING);

	REGWRITE_BUFFER_FLUSH(ah);

	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);

	aniState->ofdmPhyErrCount = 0;
	aniState->cckPhyErrCount = 0;
पूर्ण

/* Adjust the OFDM Noise Immunity Level */
अटल व्योम ath9k_hw_set_ofdm_nil(काष्ठा ath_hw *ah, u8 immunityLevel,
				  bool scan)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	स्थिर काष्ठा ani_ofdm_level_entry *entry_ofdm;
	स्थिर काष्ठा ani_cck_level_entry *entry_cck;
	bool weak_sig;

	ath_dbg(common, ANI, "**** ofdmlevel %d=>%d, rssi=%d[lo=%d hi=%d]\n",
		aniState->ofdmNoiseImmunityLevel,
		immunityLevel, BEACON_RSSI(ah),
		ATH9K_ANI_RSSI_THR_LOW,
		ATH9K_ANI_RSSI_THR_HIGH);

	अगर (AR_SREV_9100(ah) && immunityLevel < ATH9K_ANI_OFDM_DEF_LEVEL)
		immunityLevel = ATH9K_ANI_OFDM_DEF_LEVEL;

	अगर (!scan)
		aniState->ofdmNoiseImmunityLevel = immunityLevel;

	entry_ofdm = &ofdm_level_table[aniState->ofdmNoiseImmunityLevel];
	entry_cck = &cck_level_table[aniState->cckNoiseImmunityLevel];

	अगर (aniState->spurImmunityLevel != entry_ofdm->spur_immunity_level)
		ath9k_hw_ani_control(ah,
				     ATH9K_ANI_SPUR_IMMUNITY_LEVEL,
				     entry_ofdm->spur_immunity_level);

	अगर (aniState->firstepLevel != entry_ofdm->fir_step_level &&
	    entry_ofdm->fir_step_level >= entry_cck->fir_step_level)
		ath9k_hw_ani_control(ah,
				     ATH9K_ANI_FIRSTEP_LEVEL,
				     entry_ofdm->fir_step_level);

	weak_sig = entry_ofdm->ofdm_weak_संकेत_on;
	अगर (ah->opmode == NL80211_IFTYPE_STATION &&
	    BEACON_RSSI(ah) <= ATH9K_ANI_RSSI_THR_HIGH)
		weak_sig = true;
	/*
	 * Newer chipsets are better at dealing with high PHY error counts -
	 * keep weak संकेत detection enabled when no RSSI threshold is
	 * available to determine अगर it is needed (mode != STA)
	 */
	अन्यथा अगर (AR_SREV_9300_20_OR_LATER(ah) &&
		 ah->opmode != NL80211_IFTYPE_STATION)
		weak_sig = true;

	/* Older chipsets are more sensitive to high PHY error counts */
	अन्यथा अगर (!AR_SREV_9300_20_OR_LATER(ah) &&
		 aniState->ofdmNoiseImmunityLevel >= 8)
		weak_sig = false;

	अगर (aniState->ofdmWeakSigDetect != weak_sig)
		ath9k_hw_ani_control(ah, ATH9K_ANI_OFDM_WEAK_SIGNAL_DETECTION,
				     weak_sig);

	अगर (!AR_SREV_9300_20_OR_LATER(ah))
		वापस;

	अगर (aniState->ofdmNoiseImmunityLevel >= ATH9K_ANI_OFDM_DEF_LEVEL) अणु
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW_ABOVE_INI;
	पूर्ण अन्यथा अणु
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH_BELOW_INI;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW;
	पूर्ण
पूर्ण

अटल व्योम ath9k_hw_ani_ofdm_err_trigger(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;

	अगर (aniState->ofdmNoiseImmunityLevel < ATH9K_ANI_OFDM_MAX_LEVEL)
		ath9k_hw_set_ofdm_nil(ah, aniState->ofdmNoiseImmunityLevel + 1, false);
पूर्ण

/*
 * Set the ANI settings to match an CCK level.
 */
अटल व्योम ath9k_hw_set_cck_nil(काष्ठा ath_hw *ah, u_पूर्णांक8_t immunityLevel,
				 bool scan)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	स्थिर काष्ठा ani_ofdm_level_entry *entry_ofdm;
	स्थिर काष्ठा ani_cck_level_entry *entry_cck;

	ath_dbg(common, ANI, "**** ccklevel %d=>%d, rssi=%d[lo=%d hi=%d]\n",
		aniState->cckNoiseImmunityLevel, immunityLevel,
		BEACON_RSSI(ah), ATH9K_ANI_RSSI_THR_LOW,
		ATH9K_ANI_RSSI_THR_HIGH);

	अगर (AR_SREV_9100(ah) && immunityLevel < ATH9K_ANI_CCK_DEF_LEVEL)
		immunityLevel = ATH9K_ANI_CCK_DEF_LEVEL;

	अगर (ah->opmode == NL80211_IFTYPE_STATION &&
	    BEACON_RSSI(ah) <= ATH9K_ANI_RSSI_THR_LOW &&
	    immunityLevel > ATH9K_ANI_CCK_MAX_LEVEL_LOW_RSSI)
		immunityLevel = ATH9K_ANI_CCK_MAX_LEVEL_LOW_RSSI;

	अगर (!scan)
		aniState->cckNoiseImmunityLevel = immunityLevel;

	entry_ofdm = &ofdm_level_table[aniState->ofdmNoiseImmunityLevel];
	entry_cck = &cck_level_table[aniState->cckNoiseImmunityLevel];

	अगर (aniState->firstepLevel != entry_cck->fir_step_level &&
	    entry_cck->fir_step_level >= entry_ofdm->fir_step_level)
		ath9k_hw_ani_control(ah,
				     ATH9K_ANI_FIRSTEP_LEVEL,
				     entry_cck->fir_step_level);

	/* Skip MRC CCK क्रम pre AR9003 families */
	अगर (!AR_SREV_9300_20_OR_LATER(ah) || AR_SREV_9485(ah) ||
	    AR_SREV_9565(ah) || AR_SREV_9561(ah))
		वापस;

	अगर (aniState->mrcCCK != entry_cck->mrc_cck_on)
		ath9k_hw_ani_control(ah,
				     ATH9K_ANI_MRC_CCK,
				     entry_cck->mrc_cck_on);
पूर्ण

अटल व्योम ath9k_hw_ani_cck_err_trigger(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;

	अगर (aniState->cckNoiseImmunityLevel < ATH9K_ANI_CCK_MAX_LEVEL)
		ath9k_hw_set_cck_nil(ah, aniState->cckNoiseImmunityLevel + 1,
				     false);
पूर्ण

/*
 * only lower either OFDM or CCK errors per turn
 * we lower the other one next समय
 */
अटल व्योम ath9k_hw_ani_lower_immunity(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;

	/* lower OFDM noise immunity */
	अगर (aniState->ofdmNoiseImmunityLevel > 0 &&
	    (aniState->ofdmsTurn || aniState->cckNoiseImmunityLevel == 0)) अणु
		ath9k_hw_set_ofdm_nil(ah, aniState->ofdmNoiseImmunityLevel - 1,
				      false);
		वापस;
	पूर्ण

	/* lower CCK noise immunity */
	अगर (aniState->cckNoiseImmunityLevel > 0)
		ath9k_hw_set_cck_nil(ah, aniState->cckNoiseImmunityLevel - 1,
				     false);
पूर्ण

/*
 * Restore the ANI parameters in the HAL and reset the statistics.
 * This routine should be called क्रम every hardware reset and क्रम
 * every channel change.
 */
व्योम ath9k_ani_reset(काष्ठा ath_hw *ah, bool is_scanning)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;
	काष्ठा ath9k_channel *chan = ah->curchan;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक ofdm_nil, cck_nil;

	अगर (!chan)
		वापस;

	BUG_ON(aniState == शून्य);
	ah->stats.ast_ani_reset++;

	ofdm_nil = max_t(पूर्णांक, ATH9K_ANI_OFDM_DEF_LEVEL,
			 aniState->ofdmNoiseImmunityLevel);
	cck_nil = max_t(पूर्णांक, ATH9K_ANI_CCK_DEF_LEVEL,
			 aniState->cckNoiseImmunityLevel);

	अगर (is_scanning ||
	    (ah->opmode != NL80211_IFTYPE_STATION &&
	     ah->opmode != NL80211_IFTYPE_ADHOC)) अणु
		/*
		 * If we're scanning or in AP mode, the शेषs (ini)
		 * should be in place. For an AP we assume the historical
		 * levels क्रम this channel are probably outdated so start
		 * from शेषs instead.
		 */
		अगर (aniState->ofdmNoiseImmunityLevel !=
		    ATH9K_ANI_OFDM_DEF_LEVEL ||
		    aniState->cckNoiseImmunityLevel !=
		    ATH9K_ANI_CCK_DEF_LEVEL) अणु
			ath_dbg(common, ANI,
				"Restore defaults: opmode %u chan %d Mhz is_scanning=%d ofdm:%d cck:%d\n",
				ah->opmode,
				chan->channel,
				is_scanning,
				aniState->ofdmNoiseImmunityLevel,
				aniState->cckNoiseImmunityLevel);

			ofdm_nil = ATH9K_ANI_OFDM_DEF_LEVEL;
			cck_nil = ATH9K_ANI_CCK_DEF_LEVEL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * restore historical levels क्रम this channel
		 */
		ath_dbg(common, ANI,
			"Restore history: opmode %u chan %d Mhz is_scanning=%d ofdm:%d cck:%d\n",
			ah->opmode,
			chan->channel,
			is_scanning,
			aniState->ofdmNoiseImmunityLevel,
			aniState->cckNoiseImmunityLevel);
	पूर्ण
	ath9k_hw_set_ofdm_nil(ah, ofdm_nil, is_scanning);
	ath9k_hw_set_cck_nil(ah, cck_nil, is_scanning);

	ath9k_ani_restart(ah);
पूर्ण

अटल bool ath9k_hw_ani_पढ़ो_counters(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ar5416AniState *aniState = &ah->ani;
	u32 phyCnt1, phyCnt2;
	पूर्णांक32_t listenTime;

	ath_hw_cycle_counters_update(common);
	listenTime = ath_hw_get_listen_समय(common);

	अगर (listenTime <= 0) अणु
		ah->stats.ast_ani_lneg_or_lzero++;
		ath9k_ani_restart(ah);
		वापस false;
	पूर्ण

	aniState->listenTime += listenTime;

	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);

	phyCnt1 = REG_READ(ah, AR_PHY_ERR_1);
	phyCnt2 = REG_READ(ah, AR_PHY_ERR_2);

	ah->stats.ast_ani_ofdmerrs += phyCnt1 - aniState->ofdmPhyErrCount;
	aniState->ofdmPhyErrCount = phyCnt1;

	ah->stats.ast_ani_cckerrs += phyCnt2 - aniState->cckPhyErrCount;
	aniState->cckPhyErrCount = phyCnt2;

	वापस true;
पूर्ण

व्योम ath9k_hw_ani_monitor(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ar5416AniState *aniState = &ah->ani;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 ofdmPhyErrRate, cckPhyErrRate;

	अगर (!ath9k_hw_ani_पढ़ो_counters(ah))
		वापस;

	ofdmPhyErrRate = aniState->ofdmPhyErrCount * 1000 /
			 aniState->listenTime;
	cckPhyErrRate =  aniState->cckPhyErrCount * 1000 /
			 aniState->listenTime;

	ath_dbg(common, ANI,
		"listenTime=%d OFDM:%d errs=%d/s CCK:%d errs=%d/s ofdm_turn=%d\n",
		aniState->listenTime,
		aniState->ofdmNoiseImmunityLevel,
		ofdmPhyErrRate, aniState->cckNoiseImmunityLevel,
		cckPhyErrRate, aniState->ofdmsTurn);

	अगर (aniState->listenTime > ah->aniperiod) अणु
		अगर (cckPhyErrRate < ah->config.cck_trig_low &&
		    ofdmPhyErrRate < ah->config.ofdm_trig_low) अणु
			ath9k_hw_ani_lower_immunity(ah);
			aniState->ofdmsTurn = !aniState->ofdmsTurn;
		पूर्ण अन्यथा अगर (ofdmPhyErrRate > ah->config.ofdm_trig_high) अणु
			ath9k_hw_ani_ofdm_err_trigger(ah);
			aniState->ofdmsTurn = false;
		पूर्ण अन्यथा अगर (cckPhyErrRate > ah->config.cck_trig_high) अणु
			ath9k_hw_ani_cck_err_trigger(ah);
			aniState->ofdmsTurn = true;
		पूर्ण अन्यथा
			वापस;
			
		ath9k_ani_restart(ah);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_ani_monitor);

व्योम ath9k_enable_mib_counters(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, ANI, "Enable MIB counters\n");

	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_FILT_OFDM, 0);
	REG_WRITE(ah, AR_FILT_CCK, 0);
	REG_WRITE(ah, AR_MIBC,
		  ~(AR_MIBC_COW | AR_MIBC_FMC | AR_MIBC_CMC | AR_MIBC_MCS)
		  & 0x0f);
	REG_WRITE(ah, AR_PHY_ERR_MASK_1, AR_PHY_ERR_OFDM_TIMING);
	REG_WRITE(ah, AR_PHY_ERR_MASK_2, AR_PHY_ERR_CCK_TIMING);

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

/* Freeze the MIB counters, get the stats and then clear them */
व्योम ath9k_hw_disable_mib_counters(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, ANI, "Disable MIB counters\n");

	REG_WRITE(ah, AR_MIBC, AR_MIBC_FMC);
	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);
	REG_WRITE(ah, AR_MIBC, AR_MIBC_CMC);
	REG_WRITE(ah, AR_FILT_OFDM, 0);
	REG_WRITE(ah, AR_FILT_CCK, 0);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_disable_mib_counters);

व्योम ath9k_hw_ani_init(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ar5416AniState *ani = &ah->ani;

	ath_dbg(common, ANI, "Initialize ANI\n");

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW;
		ah->config.cck_trig_high = ATH9K_ANI_CCK_TRIG_HIGH;
		ah->config.cck_trig_low = ATH9K_ANI_CCK_TRIG_LOW;
	पूर्ण अन्यथा अणु
		ah->config.ofdm_trig_high = ATH9K_ANI_OFDM_TRIG_HIGH_OLD;
		ah->config.ofdm_trig_low = ATH9K_ANI_OFDM_TRIG_LOW_OLD;
		ah->config.cck_trig_high = ATH9K_ANI_CCK_TRIG_HIGH_OLD;
		ah->config.cck_trig_low = ATH9K_ANI_CCK_TRIG_LOW_OLD;
	पूर्ण

	ani->spurImmunityLevel = ATH9K_ANI_SPUR_IMMUNE_LVL;
	ani->firstepLevel = ATH9K_ANI_FIRSTEP_LVL;
	ani->mrcCCK = AR_SREV_9300_20_OR_LATER(ah) ? true : false;
	ani->ofdmsTurn = true;
	ani->ofdmWeakSigDetect = true;
	ani->cckNoiseImmunityLevel = ATH9K_ANI_CCK_DEF_LEVEL;
	ani->ofdmNoiseImmunityLevel = ATH9K_ANI_OFDM_DEF_LEVEL;

	/*
	 * since we expect some ongoing मुख्यtenance on the tables, let's sanity
	 * check here शेष level should not modअगरy INI setting.
	 */
	ah->aniperiod = ATH9K_ANI_PERIOD;
	ah->config.ani_poll_पूर्णांकerval = ATH9K_ANI_POLLINTERVAL;

	ath9k_ani_restart(ah);
	ath9k_enable_mib_counters(ah);
पूर्ण
