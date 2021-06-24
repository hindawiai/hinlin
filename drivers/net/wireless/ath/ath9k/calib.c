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

#समावेश "hw.h"
#समावेश "hw-ops.h"
#समावेश <linux/export.h>

/* Common calibration code */


अटल पूर्णांक16_t ath9k_hw_get_nf_hist_mid(पूर्णांक16_t *nfCalBuffer)
अणु
	पूर्णांक16_t nfval;
	पूर्णांक16_t sort[ATH9K_NF_CAL_HIST_MAX];
	पूर्णांक i, j;

	क्रम (i = 0; i < ATH9K_NF_CAL_HIST_MAX; i++)
		sort[i] = nfCalBuffer[i];

	क्रम (i = 0; i < ATH9K_NF_CAL_HIST_MAX - 1; i++) अणु
		क्रम (j = 1; j < ATH9K_NF_CAL_HIST_MAX - i; j++) अणु
			अगर (sort[j] > sort[j - 1]) अणु
				nfval = sort[j];
				sort[j] = sort[j - 1];
				sort[j - 1] = nfval;
			पूर्ण
		पूर्ण
	पूर्ण
	nfval = sort[(ATH9K_NF_CAL_HIST_MAX - 1) >> 1];

	वापस nfval;
पूर्ण

अटल काष्ठा ath_nf_limits *ath9k_hw_get_nf_limits(काष्ठा ath_hw *ah,
						    काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_nf_limits *limit;

	अगर (!chan || IS_CHAN_2GHZ(chan))
		limit = &ah->nf_2g;
	अन्यथा
		limit = &ah->nf_5g;

	वापस limit;
पूर्ण

अटल s16 ath9k_hw_get_शेष_nf(काष्ठा ath_hw *ah,
				   काष्ठा ath9k_channel *chan,
				   पूर्णांक chain)
अणु
	s16 calib_nf = ath9k_hw_get_nf_limits(ah, chan)->cal[chain];

	अगर (calib_nf)
		वापस calib_nf;
	अन्यथा
		वापस ath9k_hw_get_nf_limits(ah, chan)->nominal;
पूर्ण

s16 ath9k_hw_अ_लोhan_noise(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			   s16 nf)
अणु
	s8 noise = ATH_DEFAULT_NOISE_FLOOR;

	अगर (nf) अणु
		s8 delta = nf - ATH9K_NF_CAL_NOISE_THRESH -
			   ath9k_hw_get_शेष_nf(ah, chan, 0);
		अगर (delta > 0)
			noise += delta;
	पूर्ण
	वापस noise;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_अ_लोhan_noise);

अटल व्योम ath9k_hw_update_nfcal_hist_buffer(काष्ठा ath_hw *ah,
					      काष्ठा ath9k_hw_cal_data *cal,
					      पूर्णांक16_t *nfarray)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_nf_limits *limit;
	काष्ठा ath9k_nfcal_hist *h;
	bool high_nf_mid = false;
	u8 chainmask = (ah->rxchainmask << 3) | ah->rxchainmask;
	पूर्णांक i;

	h = cal->nfCalHist;
	limit = ath9k_hw_get_nf_limits(ah, ah->curchan);

	क्रम (i = 0; i < NUM_NF_READINGS; i++) अणु
		अगर (!(chainmask & (1 << i)) ||
		    ((i >= AR5416_MAX_CHAINS) && !IS_CHAN_HT40(ah->curchan)))
			जारी;

		h[i].nfCalBuffer[h[i].currIndex] = nfarray[i];

		अगर (++h[i].currIndex >= ATH9K_NF_CAL_HIST_MAX)
			h[i].currIndex = 0;

		अगर (h[i].invalidNFcount > 0) अणु
			h[i].invalidNFcount--;
			h[i].privNF = nfarray[i];
		पूर्ण अन्यथा अणु
			h[i].privNF =
				ath9k_hw_get_nf_hist_mid(h[i].nfCalBuffer);
		पूर्ण

		अगर (!h[i].privNF)
			जारी;

		अगर (h[i].privNF > limit->max) अणु
			high_nf_mid = true;

			ath_dbg(common, CALIBRATE,
				"NFmid[%d] (%d) > MAX (%d), %s\n",
				i, h[i].privNF, limit->max,
				(test_bit(NFCAL_INTF, &cal->cal_flags) ?
				 "not corrected (due to interference)" :
				 "correcting to MAX"));

			/*
			 * Normally we limit the average noise न्यूनमान by the
			 * hardware specअगरic maximum here. However अगर we have
			 * encountered stuck beacons because of पूर्णांकerference,
			 * we bypass this limit here in order to better deal
			 * with our environment.
			 */
			अगर (!test_bit(NFCAL_INTF, &cal->cal_flags))
				h[i].privNF = limit->max;
		पूर्ण
	पूर्ण

	/*
	 * If the noise न्यूनमान seems normal क्रम all chains, assume that
	 * there is no signअगरicant पूर्णांकerference in the environment anymore.
	 * Re-enable the enक्रमcement of the NF maximum again.
	 */
	अगर (!high_nf_mid)
		clear_bit(NFCAL_INTF, &cal->cal_flags);
पूर्ण

अटल bool ath9k_hw_get_nf_thresh(काष्ठा ath_hw *ah,
				   क्रमागत nl80211_band band,
				   पूर्णांक16_t *nft)
अणु
	चयन (band) अणु
	हाल NL80211_BAND_5GHZ:
		*nft = (पूर्णांक8_t)ah->eep_ops->get_eeprom(ah, EEP_NFTHRESH_5);
		अवरोध;
	हाल NL80211_BAND_2GHZ:
		*nft = (पूर्णांक8_t)ah->eep_ops->get_eeprom(ah, EEP_NFTHRESH_2);
		अवरोध;
	शेष:
		BUG_ON(1);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम ath9k_hw_reset_calibration(काष्ठा ath_hw *ah,
				काष्ठा ath9k_cal_list *currCal)
अणु
	पूर्णांक i;

	ath9k_hw_setup_calibration(ah, currCal);

	ah->cal_start_समय = jअगरfies;
	currCal->calState = CAL_RUNNING;

	क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
		ah->meas0.sign[i] = 0;
		ah->meas1.sign[i] = 0;
		ah->meas2.sign[i] = 0;
		ah->meas3.sign[i] = 0;
	पूर्ण

	ah->cal_samples = 0;
पूर्ण

/* This is करोne क्रम the currently configured channel */
bool ath9k_hw_reset_calvalid(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_cal_list *currCal = ah->cal_list_curr;

	अगर (!ah->caldata)
		वापस true;

	अगर (!AR_SREV_9100(ah) && !AR_SREV_9160_10_OR_LATER(ah))
		वापस true;

	अगर (currCal == शून्य)
		वापस true;

	अगर (currCal->calState != CAL_DONE) अणु
		ath_dbg(common, CALIBRATE, "Calibration state incorrect, %d\n",
			currCal->calState);
		वापस true;
	पूर्ण

	currCal = ah->cal_list;
	करो अणु
		ath_dbg(common, CALIBRATE, "Resetting Cal %d state for channel %u\n",
			currCal->calData->calType,
			ah->curchan->chan->center_freq);

		ah->caldata->CalValid &= ~currCal->calData->calType;
		currCal->calState = CAL_WAITING;

		currCal = currCal->calNext;
	पूर्ण जबतक (currCal != ah->cal_list);

	वापस false;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_reset_calvalid);

व्योम ath9k_hw_start_nfcal(काष्ठा ath_hw *ah, bool update)
अणु
	अगर (ah->caldata)
		set_bit(NFCAL_PENDING, &ah->caldata->cal_flags);

	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_ENABLE_NF);

	अगर (update)
		REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);
	अन्यथा
		REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);

	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);
पूर्ण

पूर्णांक ath9k_hw_loadnf(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath9k_nfcal_hist *h = शून्य;
	अचिन्हित i, j;
	u8 chainmask = (ah->rxchainmask << 3) | ah->rxchainmask;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	s16 शेष_nf = ath9k_hw_get_nf_limits(ah, chan)->nominal;
	u32 bb_agc_ctl = REG_READ(ah, AR_PHY_AGC_CONTROL);

	अगर (ah->caldata)
		h = ah->caldata->nfCalHist;

	ENABLE_REG_RMW_BUFFER(ah);
	क्रम (i = 0; i < NUM_NF_READINGS; i++) अणु
		अगर (chainmask & (1 << i)) अणु
			s16 nfval;

			अगर ((i >= AR5416_MAX_CHAINS) && !IS_CHAN_HT40(chan))
				जारी;

			अगर (ah->nf_override)
				nfval = ah->nf_override;
			अन्यथा अगर (h)
				nfval = h[i].privNF;
			अन्यथा अणु
				/* Try to get calibrated noise न्यूनमान value */
				nfval =
				    ath9k_hw_get_nf_limits(ah, chan)->cal[i];
				अगर (nfval > -60 || nfval < -127)
					nfval = शेष_nf;
			पूर्ण

			REG_RMW(ah, ah->nf_regs[i],
				(((u32) nfval << 1) & 0x1ff), 0x1ff);
		पूर्ण
	पूर्ण

	/*
	 * stop NF cal अगर ongoing to ensure NF load completes immediately
	 * (or after end rx/tx frame अगर ongoing)
	 */
	अगर (bb_agc_ctl & AR_PHY_AGC_CONTROL_NF) अणु
		REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);
		REG_RMW_BUFFER_FLUSH(ah);
		ENABLE_REG_RMW_BUFFER(ah);
	पूर्ण

	/*
	 * Load software filtered NF value पूर्णांकo baseband पूर्णांकernal minCCApwr
	 * variable.
	 */
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_ENABLE_NF);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);
	REG_RMW_BUFFER_FLUSH(ah);

	/*
	 * Wait क्रम load to complete, should be fast, a few 10s of us.
	 * The max delay was changed from an original 250us to 22.2 msec.
	 * This would increase समयout to the दीर्घest possible frame
	 * (11n max length 22.1 msec)
	 */
	क्रम (j = 0; j < 22200; j++) अणु
		अगर ((REG_READ(ah, AR_PHY_AGC_CONTROL) &
			      AR_PHY_AGC_CONTROL_NF) == 0)
			अवरोध;
		udelay(10);
	पूर्ण

	/*
	 * Restart NF so it can जारी.
	 */
	अगर (bb_agc_ctl & AR_PHY_AGC_CONTROL_NF) अणु
		ENABLE_REG_RMW_BUFFER(ah);
		अगर (bb_agc_ctl & AR_PHY_AGC_CONTROL_ENABLE_NF)
			REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
				    AR_PHY_AGC_CONTROL_ENABLE_NF);
		अगर (bb_agc_ctl & AR_PHY_AGC_CONTROL_NO_UPDATE_NF)
			REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
				    AR_PHY_AGC_CONTROL_NO_UPDATE_NF);
		REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_NF);
		REG_RMW_BUFFER_FLUSH(ah);
	पूर्ण

	/*
	 * We समयd out रुकोing क्रम the noiseन्यूनमान to load, probably due to an
	 * in-progress rx. Simply वापस here and allow the load plenty of समय
	 * to complete beक्रमe the next calibration पूर्णांकerval.  We need to aव्योम
	 * trying to load -50 (which happens below) जबतक the previous load is
	 * still in progress as this can cause rx deafness. Instead by वापसing
	 * here, the baseband nf cal will just be capped by our present
	 * noiseन्यूनमान until the next calibration समयr.
	 */
	अगर (j == 22200) अणु
		ath_dbg(common, ANY,
			"Timeout while waiting for nf to load: AR_PHY_AGC_CONTROL=0x%x\n",
			REG_READ(ah, AR_PHY_AGC_CONTROL));
		वापस -ETIMEDOUT;
	पूर्ण

	/*
	 * Restore maxCCAPower रेजिस्टर parameter again so that we're not capped
	 * by the median we just loaded.  This will be initial (and max) value
	 * of next noise न्यूनमान calibration the baseband करोes.
	 */
	ENABLE_REG_RMW_BUFFER(ah);
	क्रम (i = 0; i < NUM_NF_READINGS; i++) अणु
		अगर (chainmask & (1 << i)) अणु
			अगर ((i >= AR5416_MAX_CHAINS) && !IS_CHAN_HT40(chan))
				जारी;

			REG_RMW(ah, ah->nf_regs[i],
					(((u32) (-50) << 1) & 0x1ff), 0x1ff);
		पूर्ण
	पूर्ण
	REG_RMW_BUFFER_FLUSH(ah);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_loadnf);


अटल व्योम ath9k_hw_nf_sanitize(काष्ठा ath_hw *ah, s16 *nf)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_nf_limits *limit;
	पूर्णांक i;

	अगर (IS_CHAN_2GHZ(ah->curchan))
		limit = &ah->nf_2g;
	अन्यथा
		limit = &ah->nf_5g;

	क्रम (i = 0; i < NUM_NF_READINGS; i++) अणु
		अगर (!nf[i])
			जारी;

		ath_dbg(common, CALIBRATE,
			"NF calibrated [%s] [chain %d] is %d\n",
			(i >= 3 ? "ext" : "ctl"), i % 3, nf[i]);

		अगर (nf[i] > limit->max) अणु
			ath_dbg(common, CALIBRATE,
				"NF[%d] (%d) > MAX (%d), correcting to MAX\n",
				i, nf[i], limit->max);
			nf[i] = limit->max;
		पूर्ण अन्यथा अगर (nf[i] < limit->min) अणु
			ath_dbg(common, CALIBRATE,
				"NF[%d] (%d) < MIN (%d), correcting to NOM\n",
				i, nf[i], limit->min);
			nf[i] = limit->nominal;
		पूर्ण
	पूर्ण
पूर्ण

bool ath9k_hw_getnf(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक16_t nf, nfThresh;
	पूर्णांक16_t nfarray[NUM_NF_READINGS] = अणु 0 पूर्ण;
	काष्ठा ath9k_nfcal_hist *h;
	काष्ठा ieee80211_channel *c = chan->chan;
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;

	अगर (REG_READ(ah, AR_PHY_AGC_CONTROL) & AR_PHY_AGC_CONTROL_NF) अणु
		ath_dbg(common, CALIBRATE,
			"NF did not complete in calibration window\n");
		वापस false;
	पूर्ण

	ath9k_hw_करो_getnf(ah, nfarray);
	ath9k_hw_nf_sanitize(ah, nfarray);
	nf = nfarray[0];
	अगर (ath9k_hw_get_nf_thresh(ah, c->band, &nfThresh)
	    && nf > nfThresh) अणु
		ath_dbg(common, CALIBRATE,
			"noise floor failed detected; detected %d, threshold %d\n",
			nf, nfThresh);
	पूर्ण

	अगर (!caldata) अणु
		chan->noiseन्यूनमान = nf;
		वापस false;
	पूर्ण

	h = caldata->nfCalHist;
	clear_bit(NFCAL_PENDING, &caldata->cal_flags);
	ath9k_hw_update_nfcal_hist_buffer(ah, caldata, nfarray);
	chan->noiseन्यूनमान = h[0].privNF;
	ah->noise = ath9k_hw_अ_लोhan_noise(ah, chan, chan->noiseन्यूनमान);
	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_getnf);

व्योम ath9k_init_nfcal_hist_buffer(काष्ठा ath_hw *ah,
				  काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath9k_nfcal_hist *h;
	पूर्णांक i, j, k = 0;

	ah->caldata->channel = chan->channel;
	ah->caldata->channelFlags = chan->channelFlags;
	h = ah->caldata->nfCalHist;
	क्रम (i = 0; i < NUM_NF_READINGS; i++) अणु
		h[i].currIndex = 0;
		h[i].privNF = ath9k_hw_get_शेष_nf(ah, chan, k);
		h[i].invalidNFcount = AR_PHY_CCA_FILTERWINDOW_LENGTH;
		क्रम (j = 0; j < ATH9K_NF_CAL_HIST_MAX; j++)
			h[i].nfCalBuffer[j] = h[i].privNF;
		अगर (++k >= AR5416_MAX_CHAINS)
			k = 0;
	पूर्ण
पूर्ण


व्योम ath9k_hw_bstuck_nfcal(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;

	अगर (unlikely(!caldata))
		वापस;

	/*
	 * If beacons are stuck, the most likely cause is पूर्णांकerference.
	 * Triggering a noise न्यूनमान calibration at this poपूर्णांक helps the
	 * hardware adapt to a noisy environment much faster.
	 * To ensure that we recover from stuck beacons quickly, let
	 * the baseband update the पूर्णांकernal NF value itself, similar to
	 * what is being करोne after a full reset.
	 */
	अगर (!test_bit(NFCAL_PENDING, &caldata->cal_flags))
		ath9k_hw_start_nfcal(ah, true);
	अन्यथा अगर (!(REG_READ(ah, AR_PHY_AGC_CONTROL) & AR_PHY_AGC_CONTROL_NF))
		ath9k_hw_getnf(ah, ah->curchan);

	set_bit(NFCAL_INTF, &caldata->cal_flags);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_bstuck_nfcal);

