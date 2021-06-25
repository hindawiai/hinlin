<शैली गुरु>
/*
 * Copyright (C) 2010 Bruno Ranकरोlf <br1@einfach.org>
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

#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"
#समावेश "ani.h"

/**
 * DOC: Basic ANI Operation
 *
 * Adaptive Noise Immunity (ANI) controls five noise immunity parameters
 * depending on the amount of पूर्णांकerference in the environment, increasing
 * or reducing sensitivity as necessary.
 *
 * The parameters are:
 *
 *   - "noise immunity"
 *
 *   - "spur immunity"
 *
 *   - "firstep level"
 *
 *   - "OFDM weak signal detection"
 *
 *   - "CCK weak signal detection"
 *
 * Basically we look at the amount of ODFM and CCK timing errors we get and then
 * उठाओ or lower immunity accordingly by setting one or more of these
 * parameters.
 *
 * Newer chipsets have PHY error counters in hardware which will generate a MIB
 * पूर्णांकerrupt when they overflow. Older hardware has too enable PHY error frames
 * by setting a RX flag and then count every single PHY error. When a specअगरied
 * threshold of errors has been reached we will उठाओ immunity.
 * Also we regularly check the amount of errors and lower or उठाओ immunity as
 * necessary.
 */


/***********************\
* ANI parameter control *
\***********************/

/**
 * ath5k_ani_set_noise_immunity_level() - Set noise immunity level
 * @ah: The &काष्ठा ath5k_hw
 * @level: level between 0 and @ATH5K_ANI_MAX_NOISE_IMM_LVL
 */
व्योम
ath5k_ani_set_noise_immunity_level(काष्ठा ath5k_hw *ah, पूर्णांक level)
अणु
	/* TODO:
	 * ANI करोcuments suggest the following five levels to use, but the HAL
	 * and ath9k use only the last two levels, making this
	 * essentially an on/off option. There *may* be a reason क्रम this (???),
	 * so i stick with the HAL version क्रम now...
	 */
#अगर 0
	अटल स्थिर s8 lo[] = अणु -52, -56, -60, -64, -70 पूर्ण;
	अटल स्थिर s8 hi[] = अणु -18, -18, -16, -14, -12 पूर्ण;
	अटल स्थिर s8 sz[] = अणु -34, -41, -48, -55, -62 पूर्ण;
	अटल स्थिर s8 fr[] = अणु -70, -72, -75, -78, -80 पूर्ण;
#अन्यथा
	अटल स्थिर s8 lo[] = अणु -64, -70 पूर्ण;
	अटल स्थिर s8 hi[] = अणु -14, -12 पूर्ण;
	अटल स्थिर s8 sz[] = अणु -55, -62 पूर्ण;
	अटल स्थिर s8 fr[] = अणु -78, -80 पूर्ण;
#पूर्ण_अगर
	अगर (level < 0 || level >= ARRAY_SIZE(sz)) अणु
		ATH5K_ERR(ah, "noise immunity level %d out of range",
			  level);
		वापस;
	पूर्ण

	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_DESIRED_SIZE,
				AR5K_PHY_DESIRED_SIZE_TOT, sz[level]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_AGCCOARSE,
				AR5K_PHY_AGCCOARSE_LO, lo[level]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_AGCCOARSE,
				AR5K_PHY_AGCCOARSE_HI, hi[level]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_SIG,
				AR5K_PHY_SIG_FIRPWR, fr[level]);

	ah->ani_state.noise_imm_level = level;
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "new level %d", level);
पूर्ण

/**
 * ath5k_ani_set_spur_immunity_level() - Set spur immunity level
 * @ah: The &काष्ठा ath5k_hw
 * @level: level between 0 and @max_spur_level (the maximum level is dependent
 * on the chip revision).
 */
व्योम
ath5k_ani_set_spur_immunity_level(काष्ठा ath5k_hw *ah, पूर्णांक level)
अणु
	अटल स्थिर पूर्णांक val[] = अणु 2, 4, 6, 8, 10, 12, 14, 16 पूर्ण;

	अगर (level < 0 || level >= ARRAY_SIZE(val) ||
	    level > ah->ani_state.max_spur_level) अणु
		ATH5K_ERR(ah, "spur immunity level %d out of range",
			  level);
		वापस;
	पूर्ण

	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_OFDM_SELFCORR,
		AR5K_PHY_OFDM_SELFCORR_CYPWR_THR1, val[level]);

	ah->ani_state.spur_level = level;
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "new level %d", level);
पूर्ण

/**
 * ath5k_ani_set_firstep_level() - Set "firstep" level
 * @ah: The &काष्ठा ath5k_hw
 * @level: level between 0 and @ATH5K_ANI_MAX_FIRSTEP_LVL
 */
व्योम
ath5k_ani_set_firstep_level(काष्ठा ath5k_hw *ah, पूर्णांक level)
अणु
	अटल स्थिर पूर्णांक val[] = अणु 0, 4, 8 पूर्ण;

	अगर (level < 0 || level >= ARRAY_SIZE(val)) अणु
		ATH5K_ERR(ah, "firstep level %d out of range", level);
		वापस;
	पूर्ण

	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_SIG,
				AR5K_PHY_SIG_FIRSTEP, val[level]);

	ah->ani_state.firstep_level = level;
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "new level %d", level);
पूर्ण

/**
 * ath5k_ani_set_ofdm_weak_संकेत_detection() - Set OFDM weak संकेत detection
 * @ah: The &काष्ठा ath5k_hw
 * @on: turn on or off
 */
व्योम
ath5k_ani_set_ofdm_weak_संकेत_detection(काष्ठा ath5k_hw *ah, bool on)
अणु
	अटल स्थिर पूर्णांक m1l[] = अणु 127, 50 पूर्ण;
	अटल स्थिर पूर्णांक m2l[] = अणु 127, 40 पूर्ण;
	अटल स्थिर पूर्णांक m1[] = अणु 127, 0x4d पूर्ण;
	अटल स्थिर पूर्णांक m2[] = अणु 127, 0x40 पूर्ण;
	अटल स्थिर पूर्णांक m2cnt[] = अणु 31, 16 पूर्ण;
	अटल स्थिर पूर्णांक m2lcnt[] = अणु 63, 48 पूर्ण;

	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_WEAK_OFDM_LOW_THR,
				AR5K_PHY_WEAK_OFDM_LOW_THR_M1, m1l[on]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_WEAK_OFDM_LOW_THR,
				AR5K_PHY_WEAK_OFDM_LOW_THR_M2, m2l[on]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_WEAK_OFDM_HIGH_THR,
				AR5K_PHY_WEAK_OFDM_HIGH_THR_M1, m1[on]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_WEAK_OFDM_HIGH_THR,
				AR5K_PHY_WEAK_OFDM_HIGH_THR_M2, m2[on]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_WEAK_OFDM_HIGH_THR,
			AR5K_PHY_WEAK_OFDM_HIGH_THR_M2_COUNT, m2cnt[on]);
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_WEAK_OFDM_LOW_THR,
			AR5K_PHY_WEAK_OFDM_LOW_THR_M2_COUNT, m2lcnt[on]);

	अगर (on)
		AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_WEAK_OFDM_LOW_THR,
				AR5K_PHY_WEAK_OFDM_LOW_THR_SELFCOR_EN);
	अन्यथा
		AR5K_REG_DISABLE_BITS(ah, AR5K_PHY_WEAK_OFDM_LOW_THR,
				AR5K_PHY_WEAK_OFDM_LOW_THR_SELFCOR_EN);

	ah->ani_state.ofdm_weak_sig = on;
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "turned %s",
			  on ? "on" : "off");
पूर्ण

/**
 * ath5k_ani_set_cck_weak_संकेत_detection() - Set CCK weak संकेत detection
 * @ah: The &काष्ठा ath5k_hw
 * @on: turn on or off
 */
व्योम
ath5k_ani_set_cck_weak_संकेत_detection(काष्ठा ath5k_hw *ah, bool on)
अणु
	अटल स्थिर पूर्णांक val[] = अणु 8, 6 पूर्ण;
	AR5K_REG_WRITE_BITS(ah, AR5K_PHY_CCK_CROSSCORR,
				AR5K_PHY_CCK_CROSSCORR_WEAK_SIG_THR, val[on]);
	ah->ani_state.cck_weak_sig = on;
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "turned %s",
			  on ? "on" : "off");
पूर्ण


/***************\
* ANI algorithm *
\***************/

/**
 * ath5k_ani_उठाओ_immunity() - Increase noise immunity
 * @ah: The &काष्ठा ath5k_hw
 * @as: The &काष्ठा ath5k_ani_state
 * @ofdm_trigger: If this is true we are called because of too many OFDM errors,
 * the algorithm will tune more parameters then.
 *
 * Try to उठाओ noise immunity (=decrease sensitivity) in several steps
 * depending on the average RSSI of the beacons we received.
 */
अटल व्योम
ath5k_ani_उठाओ_immunity(काष्ठा ath5k_hw *ah, काष्ठा ath5k_ani_state *as,
			 bool ofdm_trigger)
अणु
	पूर्णांक rssi = ewma_beacon_rssi_पढ़ो(&ah->ah_beacon_rssi_avg);

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "raise immunity (%s)",
		ofdm_trigger ? "ODFM" : "CCK");

	/* first: उठाओ noise immunity */
	अगर (as->noise_imm_level < ATH5K_ANI_MAX_NOISE_IMM_LVL) अणु
		ath5k_ani_set_noise_immunity_level(ah, as->noise_imm_level + 1);
		वापस;
	पूर्ण

	/* only OFDM: उठाओ spur immunity level */
	अगर (ofdm_trigger &&
	    as->spur_level < ah->ani_state.max_spur_level) अणु
		ath5k_ani_set_spur_immunity_level(ah, as->spur_level + 1);
		वापस;
	पूर्ण

	/* AP mode */
	अगर (ah->opmode == NL80211_IFTYPE_AP) अणु
		अगर (as->firstep_level < ATH5K_ANI_MAX_FIRSTEP_LVL)
			ath5k_ani_set_firstep_level(ah, as->firstep_level + 1);
		वापस;
	पूर्ण

	/* STA and IBSS mode */

	/* TODO: क्रम IBSS mode it would be better to keep a beacon RSSI average
	 * per each neighbour node and use the minimum of these, to make sure we
	 * करोn't shut out a remote node by raising immunity too high. */

	अगर (rssi > ATH5K_ANI_RSSI_THR_HIGH) अणु
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
				  "beacon RSSI high");
		/* only OFDM: beacon RSSI is high, we can disable ODFM weak
		 * संकेत detection */
		अगर (ofdm_trigger && as->ofdm_weak_sig) अणु
			ath5k_ani_set_ofdm_weak_संकेत_detection(ah, false);
			ath5k_ani_set_spur_immunity_level(ah, 0);
			वापस;
		पूर्ण
		/* as a last resort or CCK: उठाओ firstep level */
		अगर (as->firstep_level < ATH5K_ANI_MAX_FIRSTEP_LVL) अणु
			ath5k_ani_set_firstep_level(ah, as->firstep_level + 1);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (rssi > ATH5K_ANI_RSSI_THR_LOW) अणु
		/* beacon RSSI in mid range, we need OFDM weak संकेत detect,
		 * but can उठाओ firstep level */
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
				  "beacon RSSI mid");
		अगर (ofdm_trigger && !as->ofdm_weak_sig)
			ath5k_ani_set_ofdm_weak_संकेत_detection(ah, true);
		अगर (as->firstep_level < ATH5K_ANI_MAX_FIRSTEP_LVL)
			ath5k_ani_set_firstep_level(ah, as->firstep_level + 1);
		वापस;
	पूर्ण अन्यथा अगर (ah->ah_current_channel->band == NL80211_BAND_2GHZ) अणु
		/* beacon RSSI is low. in B/G mode turn of OFDM weak संकेत
		 * detect and zero firstep level to maximize CCK sensitivity */
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
				  "beacon RSSI low, 2GHz");
		अगर (ofdm_trigger && as->ofdm_weak_sig)
			ath5k_ani_set_ofdm_weak_संकेत_detection(ah, false);
		अगर (as->firstep_level > 0)
			ath5k_ani_set_firstep_level(ah, 0);
		वापस;
	पूर्ण

	/* TODO: why not?:
	अगर (as->cck_weak_sig == true) अणु
		ath5k_ani_set_cck_weak_संकेत_detection(ah, false);
	पूर्ण
	*/
पूर्ण

/**
 * ath5k_ani_lower_immunity() - Decrease noise immunity
 * @ah: The &काष्ठा ath5k_hw
 * @as: The &काष्ठा ath5k_ani_state
 *
 * Try to lower noise immunity (=increase sensitivity) in several steps
 * depending on the average RSSI of the beacons we received.
 */
अटल व्योम
ath5k_ani_lower_immunity(काष्ठा ath5k_hw *ah, काष्ठा ath5k_ani_state *as)
अणु
	पूर्णांक rssi = ewma_beacon_rssi_पढ़ो(&ah->ah_beacon_rssi_avg);

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "lower immunity");

	अगर (ah->opmode == NL80211_IFTYPE_AP) अणु
		/* AP mode */
		अगर (as->firstep_level > 0) अणु
			ath5k_ani_set_firstep_level(ah, as->firstep_level - 1);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* STA and IBSS mode (see TODO above) */
		अगर (rssi > ATH5K_ANI_RSSI_THR_HIGH) अणु
			/* beacon संकेत is high, leave OFDM weak संकेत
			 * detection off or it may oscillate
			 * TODO: who said it's off??? */
		पूर्ण अन्यथा अगर (rssi > ATH5K_ANI_RSSI_THR_LOW) अणु
			/* beacon RSSI is mid-range: turn on ODFM weak संकेत
			 * detection and next, lower firstep level */
			अगर (!as->ofdm_weak_sig) अणु
				ath5k_ani_set_ofdm_weak_संकेत_detection(ah,
									 true);
				वापस;
			पूर्ण
			अगर (as->firstep_level > 0) अणु
				ath5k_ani_set_firstep_level(ah,
							as->firstep_level - 1);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* beacon संकेत is low: only reduce firstep level */
			अगर (as->firstep_level > 0) अणु
				ath5k_ani_set_firstep_level(ah,
							as->firstep_level - 1);
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	/* all modes */
	अगर (as->spur_level > 0) अणु
		ath5k_ani_set_spur_immunity_level(ah, as->spur_level - 1);
		वापस;
	पूर्ण

	/* finally, reduce noise immunity */
	अगर (as->noise_imm_level > 0) अणु
		ath5k_ani_set_noise_immunity_level(ah, as->noise_imm_level - 1);
		वापस;
	पूर्ण
पूर्ण

/**
 * ath5k_hw_ani_get_listen_समय() - Update counters and वापस listening समय
 * @ah: The &काष्ठा ath5k_hw
 * @as: The &काष्ठा ath5k_ani_state
 *
 * Return an approximation of the समय spent "listening" in milliseconds (ms)
 * since the last call of this function.
 * Save a snapshot of the counter values क्रम debugging/statistics.
 */
अटल पूर्णांक
ath5k_hw_ani_get_listen_समय(काष्ठा ath5k_hw *ah, काष्ठा ath5k_ani_state *as)
अणु
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	पूर्णांक listen;

	spin_lock_bh(&common->cc_lock);

	ath_hw_cycle_counters_update(common);
	स_नकल(&as->last_cc, &common->cc_ani, माप(as->last_cc));

	/* clears common->cc_ani */
	listen = ath_hw_get_listen_समय(common);

	spin_unlock_bh(&common->cc_lock);

	वापस listen;
पूर्ण

/**
 * ath5k_ani_save_and_clear_phy_errors() - Clear and save PHY error counters
 * @ah: The &काष्ठा ath5k_hw
 * @as: The &काष्ठा ath5k_ani_state
 *
 * Clear the PHY error counters as soon as possible, since this might be called
 * from a MIB पूर्णांकerrupt and we want to make sure we करोn't get पूर्णांकerrupted again.
 * Add the count of CCK and OFDM errors to our पूर्णांकernal state, so it can be used
 * by the algorithm later.
 *
 * Will be called from पूर्णांकerrupt and tasklet context.
 * Returns 0 अगर both counters are zero.
 */
अटल पूर्णांक
ath5k_ani_save_and_clear_phy_errors(काष्ठा ath5k_hw *ah,
				    काष्ठा ath5k_ani_state *as)
अणु
	अचिन्हित पूर्णांक ofdm_err, cck_err;

	अगर (!ah->ah_capabilities.cap_has_phyerr_counters)
		वापस 0;

	ofdm_err = ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT1);
	cck_err = ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT2);

	/* reset counters first, we might be in a hurry (पूर्णांकerrupt) */
	ath5k_hw_reg_ग_लिखो(ah, ATH5K_PHYERR_CNT_MAX - ATH5K_ANI_OFDM_TRIG_HIGH,
			   AR5K_PHYERR_CNT1);
	ath5k_hw_reg_ग_लिखो(ah, ATH5K_PHYERR_CNT_MAX - ATH5K_ANI_CCK_TRIG_HIGH,
			   AR5K_PHYERR_CNT2);

	ofdm_err = ATH5K_ANI_OFDM_TRIG_HIGH - (ATH5K_PHYERR_CNT_MAX - ofdm_err);
	cck_err = ATH5K_ANI_CCK_TRIG_HIGH - (ATH5K_PHYERR_CNT_MAX - cck_err);

	/* someबार both can be zero, especially when there is a superfluous
	 * second पूर्णांकerrupt. detect that here and वापस an error. */
	अगर (ofdm_err <= 0 && cck_err <= 0)
		वापस 0;

	/* aव्योम negative values should one of the रेजिस्टरs overflow */
	अगर (ofdm_err > 0) अणु
		as->ofdm_errors += ofdm_err;
		as->sum_ofdm_errors += ofdm_err;
	पूर्ण
	अगर (cck_err > 0) अणु
		as->cck_errors += cck_err;
		as->sum_cck_errors += cck_err;
	पूर्ण
	वापस 1;
पूर्ण

/**
 * ath5k_ani_period_restart() - Restart ANI period
 * @as: The &काष्ठा ath5k_ani_state
 *
 * Just reset counters, so they are clear क्रम the next "ani period".
 */
अटल व्योम
ath5k_ani_period_restart(काष्ठा ath5k_ani_state *as)
अणु
	/* keep last values क्रम debugging */
	as->last_ofdm_errors = as->ofdm_errors;
	as->last_cck_errors = as->cck_errors;
	as->last_listen = as->listen_समय;

	as->ofdm_errors = 0;
	as->cck_errors = 0;
	as->listen_समय = 0;
पूर्ण

/**
 * ath5k_ani_calibration() - The मुख्य ANI calibration function
 * @ah: The &काष्ठा ath5k_hw
 *
 * We count OFDM and CCK errors relative to the समय where we did not send or
 * receive ("listen" समय) and उठाओ or lower immunity accordingly.
 * This is called regularly (every second) from the calibration समयr, but also
 * when an error threshold has been reached.
 *
 * In order to synchronize access from dअगरferent contexts, this should be
 * called only indirectly by scheduling the ANI tasklet!
 */
व्योम
ath5k_ani_calibration(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_ani_state *as = &ah->ani_state;
	पूर्णांक listen, ofdm_high, ofdm_low, cck_high, cck_low;

	/* get listen समय since last call and add it to the counter because we
	 * might not have restarted the "ani period" last समय.
	 * always करो this to calculate the busy समय also in manual mode */
	listen = ath5k_hw_ani_get_listen_समय(ah, as);
	as->listen_समय += listen;

	अगर (as->ani_mode != ATH5K_ANI_MODE_AUTO)
		वापस;

	ath5k_ani_save_and_clear_phy_errors(ah, as);

	ofdm_high = as->listen_समय * ATH5K_ANI_OFDM_TRIG_HIGH / 1000;
	cck_high = as->listen_समय * ATH5K_ANI_CCK_TRIG_HIGH / 1000;
	ofdm_low = as->listen_समय * ATH5K_ANI_OFDM_TRIG_LOW / 1000;
	cck_low = as->listen_समय * ATH5K_ANI_CCK_TRIG_LOW / 1000;

	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
		"listen %d (now %d)", as->listen_समय, listen);
	ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
		"check high ofdm %d/%d cck %d/%d",
		as->ofdm_errors, ofdm_high, as->cck_errors, cck_high);

	अगर (as->ofdm_errors > ofdm_high || as->cck_errors > cck_high) अणु
		/* too many PHY errors - we have to उठाओ immunity */
		bool ofdm_flag = as->ofdm_errors > ofdm_high;
		ath5k_ani_उठाओ_immunity(ah, as, ofdm_flag);
		ath5k_ani_period_restart(as);

	पूर्ण अन्यथा अगर (as->listen_समय > 5 * ATH5K_ANI_LISTEN_PERIOD) अणु
		/* If more than 5 (TODO: why 5?) periods have passed and we got
		 * relatively little errors we can try to lower immunity */
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
			"check low ofdm %d/%d cck %d/%d",
			as->ofdm_errors, ofdm_low, as->cck_errors, cck_low);

		अगर (as->ofdm_errors <= ofdm_low && as->cck_errors <= cck_low)
			ath5k_ani_lower_immunity(ah, as);

		ath5k_ani_period_restart(as);
	पूर्ण
पूर्ण


/*******************\
* Interrupt handler *
\*******************/

/**
 * ath5k_ani_mib_पूर्णांकr() - Interrupt handler क्रम ANI MIB counters
 * @ah: The &काष्ठा ath5k_hw
 *
 * Just पढ़ो & reset the रेजिस्टरs quickly, so they करोn't generate more
 * पूर्णांकerrupts, save the counters and schedule the tasklet to decide whether
 * to उठाओ immunity or not.
 *
 * We just need to handle PHY error counters, ath5k_hw_update_mib_counters()
 * should take care of all "normal" MIB पूर्णांकerrupts.
 */
व्योम
ath5k_ani_mib_पूर्णांकr(काष्ठा ath5k_hw *ah)
अणु
	काष्ठा ath5k_ani_state *as = &ah->ani_state;

	/* nothing to करो here अगर HW करोes not have PHY error counters - they
	 * can't be the reason क्रम the MIB पूर्णांकerrupt then */
	अगर (!ah->ah_capabilities.cap_has_phyerr_counters)
		वापस;

	/* not in use but clear anyways */
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_OFDM_FIL_CNT);
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_CCK_FIL_CNT);

	अगर (ah->ani_state.ani_mode != ATH5K_ANI_MODE_AUTO)
		वापस;

	/* If one of the errors triggered, we can get a superfluous second
	 * पूर्णांकerrupt, even though we have alपढ़ोy reset the रेजिस्टर. The
	 * function detects that so we can वापस early. */
	अगर (ath5k_ani_save_and_clear_phy_errors(ah, as) == 0)
		वापस;

	अगर (as->ofdm_errors > ATH5K_ANI_OFDM_TRIG_HIGH ||
	    as->cck_errors > ATH5K_ANI_CCK_TRIG_HIGH)
		tasklet_schedule(&ah->ani_tasklet);
पूर्ण

/**
 * ath5k_ani_phy_error_report - Used by older HW to report PHY errors
 *
 * @ah: The &काष्ठा ath5k_hw
 * @phyerr: One of क्रमागत ath5k_phy_error_code
 *
 * This is used by hardware without PHY error counters to report PHY errors
 * on a frame-by-frame basis, instead of the पूर्णांकerrupt.
 */
व्योम
ath5k_ani_phy_error_report(काष्ठा ath5k_hw *ah,
			   क्रमागत ath5k_phy_error_code phyerr)
अणु
	काष्ठा ath5k_ani_state *as = &ah->ani_state;

	अगर (phyerr == AR5K_RX_PHY_ERROR_OFDM_TIMING) अणु
		as->ofdm_errors++;
		अगर (as->ofdm_errors > ATH5K_ANI_OFDM_TRIG_HIGH)
			tasklet_schedule(&ah->ani_tasklet);
	पूर्ण अन्यथा अगर (phyerr == AR5K_RX_PHY_ERROR_CCK_TIMING) अणु
		as->cck_errors++;
		अगर (as->cck_errors > ATH5K_ANI_CCK_TRIG_HIGH)
			tasklet_schedule(&ah->ani_tasklet);
	पूर्ण
पूर्ण


/****************\
* Initialization *
\****************/

/**
 * ath5k_enable_phy_err_counters() - Enable PHY error counters
 * @ah: The &काष्ठा ath5k_hw
 *
 * Enable PHY error counters क्रम OFDM and CCK timing errors.
 */
अटल व्योम
ath5k_enable_phy_err_counters(काष्ठा ath5k_hw *ah)
अणु
	ath5k_hw_reg_ग_लिखो(ah, ATH5K_PHYERR_CNT_MAX - ATH5K_ANI_OFDM_TRIG_HIGH,
			   AR5K_PHYERR_CNT1);
	ath5k_hw_reg_ग_लिखो(ah, ATH5K_PHYERR_CNT_MAX - ATH5K_ANI_CCK_TRIG_HIGH,
			   AR5K_PHYERR_CNT2);
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_ERR_FIL_OFDM, AR5K_PHYERR_CNT1_MASK);
	ath5k_hw_reg_ग_लिखो(ah, AR5K_PHY_ERR_FIL_CCK, AR5K_PHYERR_CNT2_MASK);

	/* not in use */
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_OFDM_FIL_CNT);
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_CCK_FIL_CNT);
पूर्ण

/**
 * ath5k_disable_phy_err_counters() - Disable PHY error counters
 * @ah: The &काष्ठा ath5k_hw
 *
 * Disable PHY error counters क्रम OFDM and CCK timing errors.
 */
अटल व्योम
ath5k_disable_phy_err_counters(काष्ठा ath5k_hw *ah)
अणु
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHYERR_CNT1);
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHYERR_CNT2);
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHYERR_CNT1_MASK);
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_PHYERR_CNT2_MASK);

	/* not in use */
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_OFDM_FIL_CNT);
	ath5k_hw_reg_ग_लिखो(ah, 0, AR5K_CCK_FIL_CNT);
पूर्ण

/**
 * ath5k_ani_init() - Initialize ANI
 * @ah: The &काष्ठा ath5k_hw
 * @mode: One of क्रमागत ath5k_ani_mode
 *
 * Initialize ANI according to mode.
 */
व्योम
ath5k_ani_init(काष्ठा ath5k_hw *ah, क्रमागत ath5k_ani_mode mode)
अणु
	/* ANI is only possible on 5212 and newer */
	अगर (ah->ah_version < AR5K_AR5212)
		वापस;

	अगर (mode < ATH5K_ANI_MODE_OFF || mode > ATH5K_ANI_MODE_AUTO) अणु
		ATH5K_ERR(ah, "ANI mode %d out of range", mode);
		वापस;
	पूर्ण

	/* clear old state inक्रमmation */
	स_रखो(&ah->ani_state, 0, माप(ah->ani_state));

	/* older hardware has more spur levels than newer */
	अगर (ah->ah_mac_srev < AR5K_SREV_AR2414)
		ah->ani_state.max_spur_level = 7;
	अन्यथा
		ah->ani_state.max_spur_level = 2;

	/* initial values क्रम our ani parameters */
	अगर (mode == ATH5K_ANI_MODE_OFF) अणु
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "ANI off\n");
	पूर्ण अन्यथा अगर (mode == ATH5K_ANI_MODE_MANUAL_LOW) अणु
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
			"ANI manual low -> high sensitivity\n");
		ath5k_ani_set_noise_immunity_level(ah, 0);
		ath5k_ani_set_spur_immunity_level(ah, 0);
		ath5k_ani_set_firstep_level(ah, 0);
		ath5k_ani_set_ofdm_weak_संकेत_detection(ah, true);
		ath5k_ani_set_cck_weak_संकेत_detection(ah, true);
	पूर्ण अन्यथा अगर (mode == ATH5K_ANI_MODE_MANUAL_HIGH) अणु
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI,
			"ANI manual high -> low sensitivity\n");
		ath5k_ani_set_noise_immunity_level(ah,
					ATH5K_ANI_MAX_NOISE_IMM_LVL);
		ath5k_ani_set_spur_immunity_level(ah,
					ah->ani_state.max_spur_level);
		ath5k_ani_set_firstep_level(ah, ATH5K_ANI_MAX_FIRSTEP_LVL);
		ath5k_ani_set_ofdm_weak_संकेत_detection(ah, false);
		ath5k_ani_set_cck_weak_संकेत_detection(ah, false);
	पूर्ण अन्यथा अगर (mode == ATH5K_ANI_MODE_AUTO) अणु
		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_ANI, "ANI auto\n");
		ath5k_ani_set_noise_immunity_level(ah, 0);
		ath5k_ani_set_spur_immunity_level(ah, 0);
		ath5k_ani_set_firstep_level(ah, 0);
		ath5k_ani_set_ofdm_weak_संकेत_detection(ah, true);
		ath5k_ani_set_cck_weak_संकेत_detection(ah, false);
	पूर्ण

	/* newer hardware has PHY error counter रेजिस्टरs which we can use to
	 * get OFDM and CCK error counts. older hardware has to set rxfilter and
	 * report every single PHY error by calling ath5k_ani_phy_error_report()
	 */
	अगर (mode == ATH5K_ANI_MODE_AUTO) अणु
		अगर (ah->ah_capabilities.cap_has_phyerr_counters)
			ath5k_enable_phy_err_counters(ah);
		अन्यथा
			ath5k_hw_set_rx_filter(ah, ath5k_hw_get_rx_filter(ah) |
						   AR5K_RX_FILTER_PHYERR);
	पूर्ण अन्यथा अणु
		अगर (ah->ah_capabilities.cap_has_phyerr_counters)
			ath5k_disable_phy_err_counters(ah);
		अन्यथा
			ath5k_hw_set_rx_filter(ah, ath5k_hw_get_rx_filter(ah) &
						   ~AR5K_RX_FILTER_PHYERR);
	पूर्ण

	ah->ani_state.ani_mode = mode;
पूर्ण


/**************\
* Debug output *
\**************/

#अगर_घोषित CONFIG_ATH5K_DEBUG

/**
 * ath5k_ani_prपूर्णांक_counters() - Prपूर्णांक ANI counters
 * @ah: The &काष्ठा ath5k_hw
 *
 * Used क्रम debugging ANI
 */
व्योम
ath5k_ani_prपूर्णांक_counters(काष्ठा ath5k_hw *ah)
अणु
	/* clears too */
	pr_notice("ACK fail\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_ACK_FAIL));
	pr_notice("RTS fail\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_RTS_FAIL));
	pr_notice("RTS success\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_RTS_OK));
	pr_notice("FCS error\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_FCS_FAIL));

	/* no clear */
	pr_notice("tx\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_PROFCNT_TX));
	pr_notice("rx\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_PROFCNT_RX));
	pr_notice("busy\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_PROFCNT_RXCLR));
	pr_notice("cycles\t%d\n", ath5k_hw_reg_पढ़ो(ah, AR5K_PROFCNT_CYCLE));

	pr_notice("AR5K_PHYERR_CNT1\t%d\n",
		  ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT1));
	pr_notice("AR5K_PHYERR_CNT2\t%d\n",
		  ath5k_hw_reg_पढ़ो(ah, AR5K_PHYERR_CNT2));
	pr_notice("AR5K_OFDM_FIL_CNT\t%d\n",
		  ath5k_hw_reg_पढ़ो(ah, AR5K_OFDM_FIL_CNT));
	pr_notice("AR5K_CCK_FIL_CNT\t%d\n",
		  ath5k_hw_reg_पढ़ो(ah, AR5K_CCK_FIL_CNT));
पूर्ण

#पूर्ण_अगर
