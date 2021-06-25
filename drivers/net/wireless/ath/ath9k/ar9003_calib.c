<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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
#समावेश "ar9003_phy.h"
#समावेश "ar9003_rtt.h"
#समावेश "ar9003_mci.h"

#घोषणा MAX_MEASUREMENT	MAX_IQCAL_MEASUREMENT
#घोषणा MAX_MAG_DELTA	11
#घोषणा MAX_PHS_DELTA	10
#घोषणा MAXIQCAL        3

काष्ठा coeff अणु
	पूर्णांक mag_coeff[AR9300_MAX_CHAINS][MAX_MEASUREMENT][MAXIQCAL];
	पूर्णांक phs_coeff[AR9300_MAX_CHAINS][MAX_MEASUREMENT][MAXIQCAL];
	पूर्णांक iqc_coeff[2];
पूर्ण;

क्रमागत ar9003_cal_types अणु
	IQ_MISMATCH_CAL = BIT(0),
पूर्ण;

अटल व्योम ar9003_hw_setup_calibration(काष्ठा ath_hw *ah,
					काष्ठा ath9k_cal_list *currCal)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	/* Select calibration to run */
	चयन (currCal->calData->calType) अणु
	हाल IQ_MISMATCH_CAL:
		/*
		 * Start calibration with
		 * 2^(INIT_IQCAL_LOG_COUNT_MAX+1) samples
		 */
		REG_RMW_FIELD(ah, AR_PHY_TIMING4,
			      AR_PHY_TIMING4_IQCAL_LOG_COUNT_MAX,
			      currCal->calData->calCountMax);
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_IQ);

		ath_dbg(common, CALIBRATE,
			"starting IQ Mismatch Calibration\n");

		/* Kick-off cal */
		REG_SET_BIT(ah, AR_PHY_TIMING4, AR_PHY_TIMING4_DO_CAL);
		अवरोध;
	शेष:
		ath_err(common, "Invalid calibration type\n");
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Generic calibration routine.
 * Recalibrate the lower PHY chips to account क्रम temperature/environment
 * changes.
 */
अटल bool ar9003_hw_per_calibration(काष्ठा ath_hw *ah,
				      काष्ठा ath9k_channel *ichan,
				      u8 rxchainmask,
				      काष्ठा ath9k_cal_list *currCal)
अणु
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	स्थिर काष्ठा ath9k_percal_data *cur_caldata = currCal->calData;

	/* Calibration in progress. */
	अगर (currCal->calState == CAL_RUNNING) अणु
		/* Check to see अगर it has finished. */
		अगर (REG_READ(ah, AR_PHY_TIMING4) & AR_PHY_TIMING4_DO_CAL)
			वापस false;

		/*
		* Accumulate cal measures क्रम active chains
		*/
		cur_caldata->calCollect(ah);
		ah->cal_samples++;

		अगर (ah->cal_samples >= cur_caldata->calNumSamples) अणु
			अचिन्हित पूर्णांक i, numChains = 0;
			क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
				अगर (rxchainmask & (1 << i))
					numChains++;
			पूर्ण

			/*
			* Process accumulated data
			*/
			cur_caldata->calPostProc(ah, numChains);

			/* Calibration has finished. */
			caldata->CalValid |= cur_caldata->calType;
			currCal->calState = CAL_DONE;
			वापस true;
		पूर्ण अन्यथा अणु
			/*
			 * Set-up collection of another sub-sample until we
			 * get desired number
			 */
			ar9003_hw_setup_calibration(ah, currCal);
		पूर्ण
	पूर्ण अन्यथा अगर (!(caldata->CalValid & cur_caldata->calType)) अणु
		/* If current cal is marked invalid in channel, kick it off */
		ath9k_hw_reset_calibration(ah, currCal);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ar9003_hw_calibrate(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			       u8 rxchainmask, bool दीर्घcal)
अणु
	bool iscalकरोne = true;
	काष्ठा ath9k_cal_list *currCal = ah->cal_list_curr;
	पूर्णांक ret;

	/*
	 * For given calibration:
	 * 1. Call generic cal routine
	 * 2. When this cal is करोne (isCalDone) अगर we have more cals रुकोing
	 *    (eg after reset), mask this to upper layers by not propagating
	 *    isCalDone अगर it is set to TRUE.
	 *    Instead, change isCalDone to FALSE and setup the रुकोing cal(s)
	 *    to be run.
	 */
	अगर (currCal &&
	    (currCal->calState == CAL_RUNNING ||
	     currCal->calState == CAL_WAITING)) अणु
		iscalकरोne = ar9003_hw_per_calibration(ah, chan,
						      rxchainmask, currCal);
		अगर (iscalकरोne) अणु
			ah->cal_list_curr = currCal = currCal->calNext;

			अगर (currCal->calState == CAL_WAITING) अणु
				iscalकरोne = false;
				ath9k_hw_reset_calibration(ah, currCal);
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Do NF cal only at दीर्घer पूर्णांकervals. Get the value from
	 * the previous NF cal and update history buffer.
	 */
	अगर (दीर्घcal && ath9k_hw_getnf(ah, chan)) अणु
		/*
		 * Load the NF from history buffer of the current channel.
		 * NF is slow समय-variant, so it is OK to use a historical
		 * value.
		 */
		ret = ath9k_hw_loadnf(ah, ah->curchan);
		अगर (ret < 0)
			वापस ret;

		/* start NF calibration, without updating BB NF रेजिस्टर */
		ath9k_hw_start_nfcal(ah, false);
	पूर्ण

	वापस iscalकरोne;
पूर्ण

अटल व्योम ar9003_hw_iqcal_collect(काष्ठा ath_hw *ah)
अणु
	पूर्णांक i;

	/* Accumulate IQ cal measures क्रम active chains */
	क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
		अगर (ah->txchainmask & BIT(i)) अणु
			ah->totalPowerMeasI[i] +=
				REG_READ(ah, AR_PHY_CAL_MEAS_0(i));
			ah->totalPowerMeasQ[i] +=
				REG_READ(ah, AR_PHY_CAL_MEAS_1(i));
			ah->totalIqCorrMeas[i] +=
				(पूर्णांक32_t) REG_READ(ah, AR_PHY_CAL_MEAS_2(i));
			ath_dbg(ath9k_hw_common(ah), CALIBRATE,
				"%d: Chn %d pmi=0x%08x;pmq=0x%08x;iqcm=0x%08x;\n",
				ah->cal_samples, i, ah->totalPowerMeasI[i],
				ah->totalPowerMeasQ[i],
				ah->totalIqCorrMeas[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_iqcalibrate(काष्ठा ath_hw *ah, u8 numChains)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 घातerMeasQ, घातerMeasI, iqCorrMeas;
	u32 qCoffDenom, iCoffDenom;
	पूर्णांक32_t qCoff, iCoff;
	पूर्णांक iqCorrNeg, i;
	अटल स्थिर u_पूर्णांक32_t offset_array[3] = अणु
		AR_PHY_RX_IQCAL_CORR_B0,
		AR_PHY_RX_IQCAL_CORR_B1,
		AR_PHY_RX_IQCAL_CORR_B2,
	पूर्ण;

	क्रम (i = 0; i < numChains; i++) अणु
		घातerMeasI = ah->totalPowerMeasI[i];
		घातerMeasQ = ah->totalPowerMeasQ[i];
		iqCorrMeas = ah->totalIqCorrMeas[i];

		ath_dbg(common, CALIBRATE,
			"Starting IQ Cal and Correction for Chain %d\n", i);

		ath_dbg(common, CALIBRATE,
			"Original: Chn %d iq_corr_meas = 0x%08x\n",
			i, ah->totalIqCorrMeas[i]);

		iqCorrNeg = 0;

		अगर (iqCorrMeas > 0x80000000) अणु
			iqCorrMeas = (0xffffffff - iqCorrMeas) + 1;
			iqCorrNeg = 1;
		पूर्ण

		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_i = 0x%08x\n",
			i, घातerMeasI);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_q = 0x%08x\n",
			i, घातerMeasQ);
		ath_dbg(common, CALIBRATE, "iqCorrNeg is 0x%08x\n", iqCorrNeg);

		iCoffDenom = (घातerMeasI / 2 + घातerMeasQ / 2) / 256;
		qCoffDenom = घातerMeasQ / 64;

		अगर ((iCoffDenom != 0) && (qCoffDenom != 0)) अणु
			iCoff = iqCorrMeas / iCoffDenom;
			qCoff = घातerMeasI / qCoffDenom - 64;
			ath_dbg(common, CALIBRATE, "Chn %d iCoff = 0x%08x\n",
				i, iCoff);
			ath_dbg(common, CALIBRATE, "Chn %d qCoff = 0x%08x\n",
				i, qCoff);

			/* Force bounds on iCoff */
			अगर (iCoff >= 63)
				iCoff = 63;
			अन्यथा अगर (iCoff <= -63)
				iCoff = -63;

			/* Negate iCoff अगर iqCorrNeg == 0 */
			अगर (iqCorrNeg == 0x0)
				iCoff = -iCoff;

			/* Force bounds on qCoff */
			अगर (qCoff >= 63)
				qCoff = 63;
			अन्यथा अगर (qCoff <= -63)
				qCoff = -63;

			iCoff = iCoff & 0x7f;
			qCoff = qCoff & 0x7f;

			ath_dbg(common, CALIBRATE,
				"Chn %d : iCoff = 0x%x  qCoff = 0x%x\n",
				i, iCoff, qCoff);
			ath_dbg(common, CALIBRATE,
				"Register offset (0x%04x) before update = 0x%x\n",
				offset_array[i],
				REG_READ(ah, offset_array[i]));

			अगर (AR_SREV_9565(ah) &&
			    (iCoff == 63 || qCoff == 63 ||
			     iCoff == -63 || qCoff == -63))
				वापस;

			REG_RMW_FIELD(ah, offset_array[i],
				      AR_PHY_RX_IQCAL_CORR_IQCORR_Q_I_COFF,
				      iCoff);
			REG_RMW_FIELD(ah, offset_array[i],
				      AR_PHY_RX_IQCAL_CORR_IQCORR_Q_Q_COFF,
				      qCoff);
			ath_dbg(common, CALIBRATE,
				"Register offset (0x%04x) QI COFF (bitfields 0x%08x) after update = 0x%x\n",
				offset_array[i],
				AR_PHY_RX_IQCAL_CORR_IQCORR_Q_I_COFF,
				REG_READ(ah, offset_array[i]));
			ath_dbg(common, CALIBRATE,
				"Register offset (0x%04x) QQ COFF (bitfields 0x%08x) after update = 0x%x\n",
				offset_array[i],
				AR_PHY_RX_IQCAL_CORR_IQCORR_Q_Q_COFF,
				REG_READ(ah, offset_array[i]));

			ath_dbg(common, CALIBRATE,
				"IQ Cal and Correction done for Chain %d\n", i);
		पूर्ण
	पूर्ण

	REG_SET_BIT(ah, AR_PHY_RX_IQCAL_CORR_B0,
		    AR_PHY_RX_IQCAL_CORR_IQCORR_ENABLE);
	ath_dbg(common, CALIBRATE,
		"IQ Cal and Correction (offset 0x%04x) enabled (bit position 0x%08x). New Value 0x%08x\n",
		(अचिन्हित) (AR_PHY_RX_IQCAL_CORR_B0),
		AR_PHY_RX_IQCAL_CORR_IQCORR_ENABLE,
		REG_READ(ah, AR_PHY_RX_IQCAL_CORR_B0));
पूर्ण

अटल स्थिर काष्ठा ath9k_percal_data iq_cal_single_sample = अणु
	IQ_MISMATCH_CAL,
	MIN_CAL_SAMPLES,
	PER_MAX_LOG_COUNT,
	ar9003_hw_iqcal_collect,
	ar9003_hw_iqcalibrate
पूर्ण;

अटल व्योम ar9003_hw_init_cal_settings(काष्ठा ath_hw *ah)
अणु
	ah->iq_caldata.calData = &iq_cal_single_sample;

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		ah->enabled_cals |= TX_IQ_CAL;
		अगर (AR_SREV_9485_OR_LATER(ah) && !AR_SREV_9340(ah))
			ah->enabled_cals |= TX_IQ_ON_AGC_CAL;
	पूर्ण

	ah->supp_cals = IQ_MISMATCH_CAL;
पूर्ण

#घोषणा OFF_UPPER_LT 24
#घोषणा OFF_LOWER_LT 7

अटल bool ar9003_hw_dynamic_osdac_selection(काष्ठा ath_hw *ah,
					      bool txiqcal_करोne)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक ch0_करोne, osdac_ch0, dc_off_ch0_i1, dc_off_ch0_q1, dc_off_ch0_i2,
		dc_off_ch0_q2, dc_off_ch0_i3, dc_off_ch0_q3;
	पूर्णांक ch1_करोne, osdac_ch1, dc_off_ch1_i1, dc_off_ch1_q1, dc_off_ch1_i2,
		dc_off_ch1_q2, dc_off_ch1_i3, dc_off_ch1_q3;
	पूर्णांक ch2_करोne, osdac_ch2, dc_off_ch2_i1, dc_off_ch2_q1, dc_off_ch2_i2,
		dc_off_ch2_q2, dc_off_ch2_i3, dc_off_ch2_q3;
	bool status;
	u32 temp, val;

	/*
	 * Clear offset and IQ calibration, run AGC cal.
	 */
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_OFFSET_CAL);
	REG_CLR_BIT(ah, AR_PHY_TX_IQCAL_CONTROL_0,
		    AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL);
	REG_WRITE(ah, AR_PHY_AGC_CONTROL,
		  REG_READ(ah, AR_PHY_AGC_CONTROL) | AR_PHY_AGC_CONTROL_CAL);

	status = ath9k_hw_रुको(ah, AR_PHY_AGC_CONTROL,
			       AR_PHY_AGC_CONTROL_CAL,
			       0, AH_WAIT_TIMEOUT);
	अगर (!status) अणु
		ath_dbg(common, CALIBRATE,
			"AGC cal without offset cal failed to complete in 1ms");
		वापस false;
	पूर्ण

	/*
	 * Allow only offset calibration and disable the others
	 * (Carrier Leak calibration, TX Filter calibration and
	 *  Peak Detector offset calibration).
	 */
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_OFFSET_CAL);
	REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL,
		    AR_PHY_CL_CAL_ENABLE);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_FLTR_CAL);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_PKDET_CAL);

	ch0_करोne = 0;
	ch1_करोne = 0;
	ch2_करोne = 0;

	जबतक ((ch0_करोne == 0) || (ch1_करोne == 0) || (ch2_करोne == 0)) अणु
		osdac_ch0 = (REG_READ(ah, AR_PHY_65NM_CH0_BB1) >> 30) & 0x3;
		osdac_ch1 = (REG_READ(ah, AR_PHY_65NM_CH1_BB1) >> 30) & 0x3;
		osdac_ch2 = (REG_READ(ah, AR_PHY_65NM_CH2_BB1) >> 30) & 0x3;

		REG_SET_BIT(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);

		REG_WRITE(ah, AR_PHY_AGC_CONTROL,
			  REG_READ(ah, AR_PHY_AGC_CONTROL) | AR_PHY_AGC_CONTROL_CAL);

		status = ath9k_hw_रुको(ah, AR_PHY_AGC_CONTROL,
				       AR_PHY_AGC_CONTROL_CAL,
				       0, AH_WAIT_TIMEOUT);
		अगर (!status) अणु
			ath_dbg(common, CALIBRATE,
				"DC offset cal failed to complete in 1ms");
			वापस false;
		पूर्ण

		REG_CLR_BIT(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);

		/*
		 * High gain.
		 */
		REG_WRITE(ah, AR_PHY_65NM_CH0_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH0_BB3) & 0xfffffcff) | (1 << 8)));
		REG_WRITE(ah, AR_PHY_65NM_CH1_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH1_BB3) & 0xfffffcff) | (1 << 8)));
		REG_WRITE(ah, AR_PHY_65NM_CH2_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH2_BB3) & 0xfffffcff) | (1 << 8)));

		temp = REG_READ(ah, AR_PHY_65NM_CH0_BB3);
		dc_off_ch0_i1 = (temp >> 26) & 0x1f;
		dc_off_ch0_q1 = (temp >> 21) & 0x1f;

		temp = REG_READ(ah, AR_PHY_65NM_CH1_BB3);
		dc_off_ch1_i1 = (temp >> 26) & 0x1f;
		dc_off_ch1_q1 = (temp >> 21) & 0x1f;

		temp = REG_READ(ah, AR_PHY_65NM_CH2_BB3);
		dc_off_ch2_i1 = (temp >> 26) & 0x1f;
		dc_off_ch2_q1 = (temp >> 21) & 0x1f;

		/*
		 * Low gain.
		 */
		REG_WRITE(ah, AR_PHY_65NM_CH0_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH0_BB3) & 0xfffffcff) | (2 << 8)));
		REG_WRITE(ah, AR_PHY_65NM_CH1_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH1_BB3) & 0xfffffcff) | (2 << 8)));
		REG_WRITE(ah, AR_PHY_65NM_CH2_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH2_BB3) & 0xfffffcff) | (2 << 8)));

		temp = REG_READ(ah, AR_PHY_65NM_CH0_BB3);
		dc_off_ch0_i2 = (temp >> 26) & 0x1f;
		dc_off_ch0_q2 = (temp >> 21) & 0x1f;

		temp = REG_READ(ah, AR_PHY_65NM_CH1_BB3);
		dc_off_ch1_i2 = (temp >> 26) & 0x1f;
		dc_off_ch1_q2 = (temp >> 21) & 0x1f;

		temp = REG_READ(ah, AR_PHY_65NM_CH2_BB3);
		dc_off_ch2_i2 = (temp >> 26) & 0x1f;
		dc_off_ch2_q2 = (temp >> 21) & 0x1f;

		/*
		 * Loopback.
		 */
		REG_WRITE(ah, AR_PHY_65NM_CH0_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH0_BB3) & 0xfffffcff) | (3 << 8)));
		REG_WRITE(ah, AR_PHY_65NM_CH1_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH1_BB3) & 0xfffffcff) | (3 << 8)));
		REG_WRITE(ah, AR_PHY_65NM_CH2_BB3,
			  ((REG_READ(ah, AR_PHY_65NM_CH2_BB3) & 0xfffffcff) | (3 << 8)));

		temp = REG_READ(ah, AR_PHY_65NM_CH0_BB3);
		dc_off_ch0_i3 = (temp >> 26) & 0x1f;
		dc_off_ch0_q3 = (temp >> 21) & 0x1f;

		temp = REG_READ(ah, AR_PHY_65NM_CH1_BB3);
		dc_off_ch1_i3 = (temp >> 26) & 0x1f;
		dc_off_ch1_q3 = (temp >> 21) & 0x1f;

		temp = REG_READ(ah, AR_PHY_65NM_CH2_BB3);
		dc_off_ch2_i3 = (temp >> 26) & 0x1f;
		dc_off_ch2_q3 = (temp >> 21) & 0x1f;

		अगर ((dc_off_ch0_i1 > OFF_UPPER_LT) || (dc_off_ch0_i1 < OFF_LOWER_LT) ||
		    (dc_off_ch0_i2 > OFF_UPPER_LT) || (dc_off_ch0_i2 < OFF_LOWER_LT) ||
		    (dc_off_ch0_i3 > OFF_UPPER_LT) || (dc_off_ch0_i3 < OFF_LOWER_LT) ||
		    (dc_off_ch0_q1 > OFF_UPPER_LT) || (dc_off_ch0_q1 < OFF_LOWER_LT) ||
		    (dc_off_ch0_q2 > OFF_UPPER_LT) || (dc_off_ch0_q2 < OFF_LOWER_LT) ||
		    (dc_off_ch0_q3 > OFF_UPPER_LT) || (dc_off_ch0_q3 < OFF_LOWER_LT)) अणु
			अगर (osdac_ch0 == 3) अणु
				ch0_करोne = 1;
			पूर्ण अन्यथा अणु
				osdac_ch0++;

				val = REG_READ(ah, AR_PHY_65NM_CH0_BB1) & 0x3fffffff;
				val |= (osdac_ch0 << 30);
				REG_WRITE(ah, AR_PHY_65NM_CH0_BB1, val);

				ch0_करोne = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			ch0_करोne = 1;
		पूर्ण

		अगर ((dc_off_ch1_i1 > OFF_UPPER_LT) || (dc_off_ch1_i1 < OFF_LOWER_LT) ||
		    (dc_off_ch1_i2 > OFF_UPPER_LT) || (dc_off_ch1_i2 < OFF_LOWER_LT) ||
		    (dc_off_ch1_i3 > OFF_UPPER_LT) || (dc_off_ch1_i3 < OFF_LOWER_LT) ||
		    (dc_off_ch1_q1 > OFF_UPPER_LT) || (dc_off_ch1_q1 < OFF_LOWER_LT) ||
		    (dc_off_ch1_q2 > OFF_UPPER_LT) || (dc_off_ch1_q2 < OFF_LOWER_LT) ||
		    (dc_off_ch1_q3 > OFF_UPPER_LT) || (dc_off_ch1_q3 < OFF_LOWER_LT)) अणु
			अगर (osdac_ch1 == 3) अणु
				ch1_करोne = 1;
			पूर्ण अन्यथा अणु
				osdac_ch1++;

				val = REG_READ(ah, AR_PHY_65NM_CH1_BB1) & 0x3fffffff;
				val |= (osdac_ch1 << 30);
				REG_WRITE(ah, AR_PHY_65NM_CH1_BB1, val);

				ch1_करोne = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			ch1_करोne = 1;
		पूर्ण

		अगर ((dc_off_ch2_i1 > OFF_UPPER_LT) || (dc_off_ch2_i1 < OFF_LOWER_LT) ||
		    (dc_off_ch2_i2 > OFF_UPPER_LT) || (dc_off_ch2_i2 < OFF_LOWER_LT) ||
		    (dc_off_ch2_i3 > OFF_UPPER_LT) || (dc_off_ch2_i3 < OFF_LOWER_LT) ||
		    (dc_off_ch2_q1 > OFF_UPPER_LT) || (dc_off_ch2_q1 < OFF_LOWER_LT) ||
		    (dc_off_ch2_q2 > OFF_UPPER_LT) || (dc_off_ch2_q2 < OFF_LOWER_LT) ||
		    (dc_off_ch2_q3 > OFF_UPPER_LT) || (dc_off_ch2_q3 < OFF_LOWER_LT)) अणु
			अगर (osdac_ch2 == 3) अणु
				ch2_करोne = 1;
			पूर्ण अन्यथा अणु
				osdac_ch2++;

				val = REG_READ(ah, AR_PHY_65NM_CH2_BB1) & 0x3fffffff;
				val |= (osdac_ch2 << 30);
				REG_WRITE(ah, AR_PHY_65NM_CH2_BB1, val);

				ch2_करोne = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			ch2_करोne = 1;
		पूर्ण
	पूर्ण

	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
		    AR_PHY_AGC_CONTROL_OFFSET_CAL);
	REG_SET_BIT(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);

	/*
	 * We करोn't need to check txiqcal_करोne here since it is always
	 * set क्रम AR9550.
	 */
	REG_SET_BIT(ah, AR_PHY_TX_IQCAL_CONTROL_0,
		    AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL);

	वापस true;
पूर्ण

/*
 * solve 4x4 linear equation used in loopback iq cal.
 */
अटल bool ar9003_hw_solve_iq_cal(काष्ठा ath_hw *ah,
				   s32 sin_2phi_1,
				   s32 cos_2phi_1,
				   s32 sin_2phi_2,
				   s32 cos_2phi_2,
				   s32 mag_a0_d0,
				   s32 phs_a0_d0,
				   s32 mag_a1_d0,
				   s32 phs_a1_d0,
				   s32 solved_eq[])
अणु
	s32 f1 = cos_2phi_1 - cos_2phi_2,
	    f3 = sin_2phi_1 - sin_2phi_2,
	    f2;
	s32 mag_tx, phs_tx, mag_rx, phs_rx;
	स्थिर s32 result_shअगरt = 1 << 15;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	f2 = ((f1 >> 3) * (f1 >> 3) + (f3 >> 3) * (f3 >> 3)) >> 9;

	अगर (!f2) अणु
		ath_dbg(common, CALIBRATE, "Divide by 0\n");
		वापस false;
	पूर्ण

	/* mag mismatch, tx */
	mag_tx = f1 * (mag_a0_d0  - mag_a1_d0) + f3 * (phs_a0_d0 - phs_a1_d0);
	/* phs mismatch, tx */
	phs_tx = f3 * (-mag_a0_d0 + mag_a1_d0) + f1 * (phs_a0_d0 - phs_a1_d0);

	mag_tx = (mag_tx / f2);
	phs_tx = (phs_tx / f2);

	/* mag mismatch, rx */
	mag_rx = mag_a0_d0 - (cos_2phi_1 * mag_tx + sin_2phi_1 * phs_tx) /
		 result_shअगरt;
	/* phs mismatch, rx */
	phs_rx = phs_a0_d0 + (sin_2phi_1 * mag_tx - cos_2phi_1 * phs_tx) /
		 result_shअगरt;

	solved_eq[0] = mag_tx;
	solved_eq[1] = phs_tx;
	solved_eq[2] = mag_rx;
	solved_eq[3] = phs_rx;

	वापस true;
पूर्ण

अटल s32 ar9003_hw_find_mag_approx(काष्ठा ath_hw *ah, s32 in_re, s32 in_im)
अणु
	s32 असल_i = असल(in_re),
	    असल_q = असल(in_im),
	    max_असल, min_असल;

	अगर (असल_i > असल_q) अणु
		max_असल = असल_i;
		min_असल = असल_q;
	पूर्ण अन्यथा अणु
		max_असल = असल_q;
		min_असल = असल_i;
	पूर्ण

	वापस max_असल - (max_असल / 32) + (min_असल / 8) + (min_असल / 4);
पूर्ण

#घोषणा DELPT 32

अटल bool ar9003_hw_calc_iq_corr(काष्ठा ath_hw *ah,
				   s32 chain_idx,
				   स्थिर s32 iq_res[],
				   s32 iqc_coeff[])
अणु
	s32 i2_m_q2_a0_d0, i2_p_q2_a0_d0, iq_corr_a0_d0,
	    i2_m_q2_a0_d1, i2_p_q2_a0_d1, iq_corr_a0_d1,
	    i2_m_q2_a1_d0, i2_p_q2_a1_d0, iq_corr_a1_d0,
	    i2_m_q2_a1_d1, i2_p_q2_a1_d1, iq_corr_a1_d1;
	s32 mag_a0_d0, mag_a1_d0, mag_a0_d1, mag_a1_d1,
	    phs_a0_d0, phs_a1_d0, phs_a0_d1, phs_a1_d1,
	    sin_2phi_1, cos_2phi_1,
	    sin_2phi_2, cos_2phi_2;
	s32 mag_tx, phs_tx, mag_rx, phs_rx;
	s32 solved_eq[4], mag_corr_tx, phs_corr_tx, mag_corr_rx, phs_corr_rx,
	    q_q_coff, q_i_coff;
	स्थिर s32 res_scale = 1 << 15;
	स्थिर s32 delpt_shअगरt = 1 << 8;
	s32 mag1, mag2;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	i2_m_q2_a0_d0 = iq_res[0] & 0xfff;
	i2_p_q2_a0_d0 = (iq_res[0] >> 12) & 0xfff;
	iq_corr_a0_d0 = ((iq_res[0] >> 24) & 0xff) + ((iq_res[1] & 0xf) << 8);

	अगर (i2_m_q2_a0_d0 > 0x800)
		i2_m_q2_a0_d0 = -((0xfff - i2_m_q2_a0_d0) + 1);

	अगर (i2_p_q2_a0_d0 > 0x800)
		i2_p_q2_a0_d0 = -((0xfff - i2_p_q2_a0_d0) + 1);

	अगर (iq_corr_a0_d0 > 0x800)
		iq_corr_a0_d0 = -((0xfff - iq_corr_a0_d0) + 1);

	i2_m_q2_a0_d1 = (iq_res[1] >> 4) & 0xfff;
	i2_p_q2_a0_d1 = (iq_res[2] & 0xfff);
	iq_corr_a0_d1 = (iq_res[2] >> 12) & 0xfff;

	अगर (i2_m_q2_a0_d1 > 0x800)
		i2_m_q2_a0_d1 = -((0xfff - i2_m_q2_a0_d1) + 1);

	अगर (iq_corr_a0_d1 > 0x800)
		iq_corr_a0_d1 = -((0xfff - iq_corr_a0_d1) + 1);

	i2_m_q2_a1_d0 = ((iq_res[2] >> 24) & 0xff) + ((iq_res[3] & 0xf) << 8);
	i2_p_q2_a1_d0 = (iq_res[3] >> 4) & 0xfff;
	iq_corr_a1_d0 = iq_res[4] & 0xfff;

	अगर (i2_m_q2_a1_d0 > 0x800)
		i2_m_q2_a1_d0 = -((0xfff - i2_m_q2_a1_d0) + 1);

	अगर (i2_p_q2_a1_d0 > 0x800)
		i2_p_q2_a1_d0 = -((0xfff - i2_p_q2_a1_d0) + 1);

	अगर (iq_corr_a1_d0 > 0x800)
		iq_corr_a1_d0 = -((0xfff - iq_corr_a1_d0) + 1);

	i2_m_q2_a1_d1 = (iq_res[4] >> 12) & 0xfff;
	i2_p_q2_a1_d1 = ((iq_res[4] >> 24) & 0xff) + ((iq_res[5] & 0xf) << 8);
	iq_corr_a1_d1 = (iq_res[5] >> 4) & 0xfff;

	अगर (i2_m_q2_a1_d1 > 0x800)
		i2_m_q2_a1_d1 = -((0xfff - i2_m_q2_a1_d1) + 1);

	अगर (i2_p_q2_a1_d1 > 0x800)
		i2_p_q2_a1_d1 = -((0xfff - i2_p_q2_a1_d1) + 1);

	अगर (iq_corr_a1_d1 > 0x800)
		iq_corr_a1_d1 = -((0xfff - iq_corr_a1_d1) + 1);

	अगर ((i2_p_q2_a0_d0 == 0) || (i2_p_q2_a0_d1 == 0) ||
	    (i2_p_q2_a1_d0 == 0) || (i2_p_q2_a1_d1 == 0)) अणु
		ath_dbg(common, CALIBRATE,
			"Divide by 0:\n"
			"a0_d0=%d\n"
			"a0_d1=%d\n"
			"a2_d0=%d\n"
			"a1_d1=%d\n",
			i2_p_q2_a0_d0, i2_p_q2_a0_d1,
			i2_p_q2_a1_d0, i2_p_q2_a1_d1);
		वापस false;
	पूर्ण

	अगर ((i2_p_q2_a0_d0 < 1024) || (i2_p_q2_a0_d0 > 2047) ||
            (i2_p_q2_a1_d0 < 0) || (i2_p_q2_a1_d1 < 0) ||
            (i2_p_q2_a0_d0 <= i2_m_q2_a0_d0) ||
            (i2_p_q2_a0_d0 <= iq_corr_a0_d0) ||
            (i2_p_q2_a0_d1 <= i2_m_q2_a0_d1) ||
            (i2_p_q2_a0_d1 <= iq_corr_a0_d1) ||
            (i2_p_q2_a1_d0 <= i2_m_q2_a1_d0) ||
            (i2_p_q2_a1_d0 <= iq_corr_a1_d0) ||
            (i2_p_q2_a1_d1 <= i2_m_q2_a1_d1) ||
            (i2_p_q2_a1_d1 <= iq_corr_a1_d1)) अणु
		वापस false;
	पूर्ण

	mag_a0_d0 = (i2_m_q2_a0_d0 * res_scale) / i2_p_q2_a0_d0;
	phs_a0_d0 = (iq_corr_a0_d0 * res_scale) / i2_p_q2_a0_d0;

	mag_a0_d1 = (i2_m_q2_a0_d1 * res_scale) / i2_p_q2_a0_d1;
	phs_a0_d1 = (iq_corr_a0_d1 * res_scale) / i2_p_q2_a0_d1;

	mag_a1_d0 = (i2_m_q2_a1_d0 * res_scale) / i2_p_q2_a1_d0;
	phs_a1_d0 = (iq_corr_a1_d0 * res_scale) / i2_p_q2_a1_d0;

	mag_a1_d1 = (i2_m_q2_a1_d1 * res_scale) / i2_p_q2_a1_d1;
	phs_a1_d1 = (iq_corr_a1_d1 * res_scale) / i2_p_q2_a1_d1;

	/* w/o analog phase shअगरt */
	sin_2phi_1 = (((mag_a0_d0 - mag_a0_d1) * delpt_shअगरt) / DELPT);
	/* w/o analog phase shअगरt */
	cos_2phi_1 = (((phs_a0_d1 - phs_a0_d0) * delpt_shअगरt) / DELPT);
	/* w/  analog phase shअगरt */
	sin_2phi_2 = (((mag_a1_d0 - mag_a1_d1) * delpt_shअगरt) / DELPT);
	/* w/  analog phase shअगरt */
	cos_2phi_2 = (((phs_a1_d1 - phs_a1_d0) * delpt_shअगरt) / DELPT);

	/*
	 * क्रमce sin^2 + cos^2 = 1;
	 * find magnitude by approximation
	 */
	mag1 = ar9003_hw_find_mag_approx(ah, cos_2phi_1, sin_2phi_1);
	mag2 = ar9003_hw_find_mag_approx(ah, cos_2phi_2, sin_2phi_2);

	अगर ((mag1 == 0) || (mag2 == 0)) अणु
		ath_dbg(common, CALIBRATE, "Divide by 0: mag1=%d, mag2=%d\n",
			mag1, mag2);
		वापस false;
	पूर्ण

	/* normalization sin and cos by mag */
	sin_2phi_1 = (sin_2phi_1 * res_scale / mag1);
	cos_2phi_1 = (cos_2phi_1 * res_scale / mag1);
	sin_2phi_2 = (sin_2phi_2 * res_scale / mag2);
	cos_2phi_2 = (cos_2phi_2 * res_scale / mag2);

	/* calculate IQ mismatch */
	अगर (!ar9003_hw_solve_iq_cal(ah,
			     sin_2phi_1, cos_2phi_1,
			     sin_2phi_2, cos_2phi_2,
			     mag_a0_d0, phs_a0_d0,
			     mag_a1_d0,
			     phs_a1_d0, solved_eq)) अणु
		ath_dbg(common, CALIBRATE,
			"Call to ar9003_hw_solve_iq_cal() failed\n");
		वापस false;
	पूर्ण

	mag_tx = solved_eq[0];
	phs_tx = solved_eq[1];
	mag_rx = solved_eq[2];
	phs_rx = solved_eq[3];

	ath_dbg(common, CALIBRATE,
		"chain %d: mag mismatch=%d phase mismatch=%d\n",
		chain_idx, mag_tx/res_scale, phs_tx/res_scale);

	अगर (res_scale == mag_tx) अणु
		ath_dbg(common, CALIBRATE,
			"Divide by 0: mag_tx=%d, res_scale=%d\n",
			mag_tx, res_scale);
		वापस false;
	पूर्ण

	/* calculate and quantize Tx IQ correction factor */
	mag_corr_tx = (mag_tx * res_scale) / (res_scale - mag_tx);
	phs_corr_tx = -phs_tx;

	q_q_coff = (mag_corr_tx * 128 / res_scale);
	q_i_coff = (phs_corr_tx * 256 / res_scale);

	ath_dbg(common, CALIBRATE, "tx chain %d: mag corr=%d  phase corr=%d\n",
		chain_idx, q_q_coff, q_i_coff);

	अगर (q_i_coff < -63)
		q_i_coff = -63;
	अगर (q_i_coff > 63)
		q_i_coff = 63;
	अगर (q_q_coff < -63)
		q_q_coff = -63;
	अगर (q_q_coff > 63)
		q_q_coff = 63;

	iqc_coeff[0] = (q_q_coff * 128) + (0x7f & q_i_coff);

	ath_dbg(common, CALIBRATE, "tx chain %d: iq corr coeff=%x\n",
		chain_idx, iqc_coeff[0]);

	अगर (-mag_rx == res_scale) अणु
		ath_dbg(common, CALIBRATE,
			"Divide by 0: mag_rx=%d, res_scale=%d\n",
			mag_rx, res_scale);
		वापस false;
	पूर्ण

	/* calculate and quantize Rx IQ correction factors */
	mag_corr_rx = (-mag_rx * res_scale) / (res_scale + mag_rx);
	phs_corr_rx = -phs_rx;

	q_q_coff = (mag_corr_rx * 128 / res_scale);
	q_i_coff = (phs_corr_rx * 256 / res_scale);

	ath_dbg(common, CALIBRATE, "rx chain %d: mag corr=%d  phase corr=%d\n",
		chain_idx, q_q_coff, q_i_coff);

	अगर (q_i_coff < -63)
		q_i_coff = -63;
	अगर (q_i_coff > 63)
		q_i_coff = 63;
	अगर (q_q_coff < -63)
		q_q_coff = -63;
	अगर (q_q_coff > 63)
		q_q_coff = 63;

	iqc_coeff[1] = (q_q_coff * 128) + (0x7f & q_i_coff);

	ath_dbg(common, CALIBRATE, "rx chain %d: iq corr coeff=%x\n",
		chain_idx, iqc_coeff[1]);

	वापस true;
पूर्ण

अटल व्योम ar9003_hw_detect_outlier(पूर्णांक mp_coeff[][MAXIQCAL],
				     पूर्णांक nmeasurement,
				     पूर्णांक max_delta)
अणु
	पूर्णांक mp_max = -64, max_idx = 0;
	पूर्णांक mp_min = 63, min_idx = 0;
	पूर्णांक mp_avg = 0, i, outlier_idx = 0, mp_count = 0;

	/* find min/max mismatch across all calibrated gains */
	क्रम (i = 0; i < nmeasurement; i++) अणु
		अगर (mp_coeff[i][0] > mp_max) अणु
			mp_max = mp_coeff[i][0];
			max_idx = i;
		पूर्ण अन्यथा अगर (mp_coeff[i][0] < mp_min) अणु
			mp_min = mp_coeff[i][0];
			min_idx = i;
		पूर्ण
	पूर्ण

	/* find average (exclude max असल value) */
	क्रम (i = 0; i < nmeasurement; i++) अणु
		अगर ((असल(mp_coeff[i][0]) < असल(mp_max)) ||
		    (असल(mp_coeff[i][0]) < असल(mp_min))) अणु
			mp_avg += mp_coeff[i][0];
			mp_count++;
		पूर्ण
	पूर्ण

	/*
	 * finding mean magnitude/phase अगर possible, otherwise
	 * just use the last value as the mean
	 */
	अगर (mp_count)
		mp_avg /= mp_count;
	अन्यथा
		mp_avg = mp_coeff[nmeasurement - 1][0];

	/* detect outlier */
	अगर (असल(mp_max - mp_min) > max_delta) अणु
		अगर (असल(mp_max - mp_avg) > असल(mp_min - mp_avg))
			outlier_idx = max_idx;
		अन्यथा
			outlier_idx = min_idx;

		mp_coeff[outlier_idx][0] = mp_avg;
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_tx_iq_cal_outlier_detection(काष्ठा ath_hw *ah,
						  काष्ठा coeff *coeff,
						  bool is_reusable)
अणु
	पूर्णांक i, im, nmeasurement;
	पूर्णांक magnitude, phase;
	u32 tx_corr_coeff[MAX_MEASUREMENT][AR9300_MAX_CHAINS];
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;

	स_रखो(tx_corr_coeff, 0, माप(tx_corr_coeff));
	क्रम (i = 0; i < MAX_MEASUREMENT / 2; i++) अणु
		tx_corr_coeff[i * 2][0] = tx_corr_coeff[(i * 2) + 1][0] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B0(i);
		अगर (!AR_SREV_9485(ah)) अणु
			tx_corr_coeff[i * 2][1] =
			tx_corr_coeff[(i * 2) + 1][1] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B1(i);

			tx_corr_coeff[i * 2][2] =
			tx_corr_coeff[(i * 2) + 1][2] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B2(i);
		पूर्ण
	पूर्ण

	/* Load the average of 2 passes */
	क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
		अगर (!(ah->txchainmask & (1 << i)))
			जारी;
		nmeasurement = REG_READ_FIELD(ah,
				AR_PHY_TX_IQCAL_STATUS_B0,
				AR_PHY_CALIBRATED_GAINS_0);

		अगर (nmeasurement > MAX_MEASUREMENT)
			nmeasurement = MAX_MEASUREMENT;

		/*
		 * Skip normal outlier detection क्रम AR9550.
		 */
		अगर (!AR_SREV_9550(ah)) अणु
			/* detect outlier only अगर nmeasurement > 1 */
			अगर (nmeasurement > 1) अणु
				/* Detect magnitude outlier */
				ar9003_hw_detect_outlier(coeff->mag_coeff[i],
							 nmeasurement,
							 MAX_MAG_DELTA);

				/* Detect phase outlier */
				ar9003_hw_detect_outlier(coeff->phs_coeff[i],
							 nmeasurement,
							 MAX_PHS_DELTA);
			पूर्ण
		पूर्ण

		क्रम (im = 0; im < nmeasurement; im++) अणु
			magnitude = coeff->mag_coeff[i][im][0];
			phase = coeff->phs_coeff[i][im][0];

			coeff->iqc_coeff[0] =
				(phase & 0x7f) | ((magnitude & 0x7f) << 7);

			अगर ((im % 2) == 0)
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
					AR_PHY_TX_IQCAL_CORR_COEFF_00_COEFF_TABLE,
					coeff->iqc_coeff[0]);
			अन्यथा
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
					AR_PHY_TX_IQCAL_CORR_COEFF_01_COEFF_TABLE,
					coeff->iqc_coeff[0]);

			अगर (caldata)
				caldata->tx_corr_coeff[im][i] =
					coeff->iqc_coeff[0];
		पूर्ण
		अगर (caldata)
			caldata->num_measures[i] = nmeasurement;
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_3,
		      AR_PHY_TX_IQCAL_CONTROL_3_IQCORR_EN, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_RX_IQCAL_CORR_B0,
		      AR_PHY_RX_IQCAL_CORR_B0_LOOPBACK_IQCORR_EN, 0x1);

	अगर (caldata) अणु
		अगर (is_reusable)
			set_bit(TXIQCAL_DONE, &caldata->cal_flags);
		अन्यथा
			clear_bit(TXIQCAL_DONE, &caldata->cal_flags);
	पूर्ण

	वापस;
पूर्ण

अटल bool ar9003_hw_tx_iq_cal_run(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u8 tx_gain_क्रमced;

	tx_gain_क्रमced = REG_READ_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
					AR_PHY_TXGAIN_FORCE);
	अगर (tx_gain_क्रमced)
		REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
			      AR_PHY_TXGAIN_FORCE, 0);

	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_START,
		      AR_PHY_TX_IQCAL_START_DO_CAL, 1);

	अगर (!ath9k_hw_रुको(ah, AR_PHY_TX_IQCAL_START,
			AR_PHY_TX_IQCAL_START_DO_CAL, 0,
			AH_WAIT_TIMEOUT)) अणु
		ath_dbg(common, CALIBRATE, "Tx IQ Cal is not completed\n");
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम __ar955x_tx_iq_cal_sort(काष्ठा ath_hw *ah,
				    काष्ठा coeff *coeff,
				    पूर्णांक i, पूर्णांक nmeasurement)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक im, ix, iy, temp;

	क्रम (im = 0; im < nmeasurement; im++) अणु
		क्रम (ix = 0; ix < MAXIQCAL - 1; ix++) अणु
			क्रम (iy = ix + 1; iy <= MAXIQCAL - 1; iy++) अणु
				अगर (coeff->mag_coeff[i][im][iy] <
				    coeff->mag_coeff[i][im][ix]) अणु
					temp = coeff->mag_coeff[i][im][ix];
					coeff->mag_coeff[i][im][ix] =
						coeff->mag_coeff[i][im][iy];
					coeff->mag_coeff[i][im][iy] = temp;
				पूर्ण
				अगर (coeff->phs_coeff[i][im][iy] <
				    coeff->phs_coeff[i][im][ix]) अणु
					temp = coeff->phs_coeff[i][im][ix];
					coeff->phs_coeff[i][im][ix] =
						coeff->phs_coeff[i][im][iy];
					coeff->phs_coeff[i][im][iy] = temp;
				पूर्ण
			पूर्ण
		पूर्ण
		coeff->mag_coeff[i][im][0] = coeff->mag_coeff[i][im][MAXIQCAL / 2];
		coeff->phs_coeff[i][im][0] = coeff->phs_coeff[i][im][MAXIQCAL / 2];

		ath_dbg(common, CALIBRATE,
			"IQCAL: Median [ch%d][gain%d]: mag = %d phase = %d\n",
			i, im,
			coeff->mag_coeff[i][im][0],
			coeff->phs_coeff[i][im][0]);
	पूर्ण
पूर्ण

अटल bool ar955x_tx_iq_cal_median(काष्ठा ath_hw *ah,
				    काष्ठा coeff *coeff,
				    पूर्णांक iqcal_idx,
				    पूर्णांक nmeasurement)
अणु
	पूर्णांक i;

	अगर ((iqcal_idx + 1) != MAXIQCAL)
		वापस false;

	क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
		__ar955x_tx_iq_cal_sort(ah, coeff, i, nmeasurement);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम ar9003_hw_tx_iq_cal_post_proc(काष्ठा ath_hw *ah,
					  पूर्णांक iqcal_idx,
					  bool is_reusable)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	स्थिर u32 txiqcal_status[AR9300_MAX_CHAINS] = अणु
		AR_PHY_TX_IQCAL_STATUS_B0,
		AR_PHY_TX_IQCAL_STATUS_B1,
		AR_PHY_TX_IQCAL_STATUS_B2,
	पूर्ण;
	स्थिर u_पूर्णांक32_t chan_info_tab[] = अणु
		AR_PHY_CHAN_INFO_TAB_0,
		AR_PHY_CHAN_INFO_TAB_1,
		AR_PHY_CHAN_INFO_TAB_2,
	पूर्ण;
	अटल काष्ठा coeff coeff;
	s32 iq_res[6];
	पूर्णांक i, im, j;
	पूर्णांक nmeasurement = 0;
	bool outlier_detect = true;

	क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
		अगर (!(ah->txchainmask & (1 << i)))
			जारी;

		nmeasurement = REG_READ_FIELD(ah,
				AR_PHY_TX_IQCAL_STATUS_B0,
				AR_PHY_CALIBRATED_GAINS_0);
		अगर (nmeasurement > MAX_MEASUREMENT)
			nmeasurement = MAX_MEASUREMENT;

		क्रम (im = 0; im < nmeasurement; im++) अणु
			ath_dbg(common, CALIBRATE,
				"Doing Tx IQ Cal for chain %d\n", i);

			अगर (REG_READ(ah, txiqcal_status[i]) &
					AR_PHY_TX_IQCAL_STATUS_FAILED) अणु
				ath_dbg(common, CALIBRATE,
					"Tx IQ Cal failed for chain %d\n", i);
				जाओ tx_iqcal_fail;
			पूर्ण

			क्रम (j = 0; j < 3; j++) अणु
				u32 idx = 2 * j, offset = 4 * (3 * im + j);

				REG_RMW_FIELD(ah,
						AR_PHY_CHAN_INFO_MEMORY,
						AR_PHY_CHAN_INFO_TAB_S2_READ,
						0);

				/* 32 bits */
				iq_res[idx] = REG_READ(ah,
						chan_info_tab[i] +
						offset);

				REG_RMW_FIELD(ah,
						AR_PHY_CHAN_INFO_MEMORY,
						AR_PHY_CHAN_INFO_TAB_S2_READ,
						1);

				/* 16 bits */
				iq_res[idx + 1] = 0xffff & REG_READ(ah,
						chan_info_tab[i] + offset);

				ath_dbg(common, CALIBRATE,
					"IQ_RES[%d]=0x%x IQ_RES[%d]=0x%x\n",
					idx, iq_res[idx], idx + 1,
					iq_res[idx + 1]);
			पूर्ण

			अगर (!ar9003_hw_calc_iq_corr(ah, i, iq_res,
						coeff.iqc_coeff)) अणु
				ath_dbg(common, CALIBRATE,
					"Failed in calculation of IQ correction\n");
				जाओ tx_iqcal_fail;
			पूर्ण

			coeff.phs_coeff[i][im][iqcal_idx] =
				coeff.iqc_coeff[0] & 0x7f;
			coeff.mag_coeff[i][im][iqcal_idx] =
				(coeff.iqc_coeff[0] >> 7) & 0x7f;

			अगर (coeff.mag_coeff[i][im][iqcal_idx] > 63)
				coeff.mag_coeff[i][im][iqcal_idx] -= 128;
			अगर (coeff.phs_coeff[i][im][iqcal_idx] > 63)
				coeff.phs_coeff[i][im][iqcal_idx] -= 128;
		पूर्ण
	पूर्ण

	अगर (AR_SREV_9550(ah))
		outlier_detect = ar955x_tx_iq_cal_median(ah, &coeff,
							 iqcal_idx, nmeasurement);
	अगर (outlier_detect)
		ar9003_hw_tx_iq_cal_outlier_detection(ah, &coeff, is_reusable);

	वापस;

tx_iqcal_fail:
	ath_dbg(common, CALIBRATE, "Tx IQ Cal failed\n");
	वापस;
पूर्ण

अटल व्योम ar9003_hw_tx_iq_cal_reload(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	u32 tx_corr_coeff[MAX_MEASUREMENT][AR9300_MAX_CHAINS];
	पूर्णांक i, im;

	स_रखो(tx_corr_coeff, 0, माप(tx_corr_coeff));
	क्रम (i = 0; i < MAX_MEASUREMENT / 2; i++) अणु
		tx_corr_coeff[i * 2][0] = tx_corr_coeff[(i * 2) + 1][0] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B0(i);
		अगर (!AR_SREV_9485(ah)) अणु
			tx_corr_coeff[i * 2][1] =
			tx_corr_coeff[(i * 2) + 1][1] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B1(i);

			tx_corr_coeff[i * 2][2] =
			tx_corr_coeff[(i * 2) + 1][2] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B2(i);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
		अगर (!(ah->txchainmask & (1 << i)))
			जारी;

		क्रम (im = 0; im < caldata->num_measures[i]; im++) अणु
			अगर ((im % 2) == 0)
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
				     AR_PHY_TX_IQCAL_CORR_COEFF_00_COEFF_TABLE,
				     caldata->tx_corr_coeff[im][i]);
			अन्यथा
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
				     AR_PHY_TX_IQCAL_CORR_COEFF_01_COEFF_TABLE,
				     caldata->tx_corr_coeff[im][i]);
		पूर्ण
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_3,
		      AR_PHY_TX_IQCAL_CONTROL_3_IQCORR_EN, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_RX_IQCAL_CORR_B0,
		      AR_PHY_RX_IQCAL_CORR_B0_LOOPBACK_IQCORR_EN, 0x1);
पूर्ण

अटल व्योम ar9003_hw_manual_peak_cal(काष्ठा ath_hw *ah, u8 chain, bool is_2g)
अणु
	पूर्णांक offset[8] = अणु0पूर्ण, total = 0, test;
	पूर्णांक agc_out, i, peak_detect_threshold = 0;

	अगर (AR_SREV_9550(ah) || AR_SREV_9531(ah))
		peak_detect_threshold = 8;
	अन्यथा अगर (AR_SREV_9561(ah))
		peak_detect_threshold = 11;

	/*
	 * Turn off LNA/SW.
	 */
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
		      AR_PHY_65NM_RXRF_GAINSTAGES_RX_OVERRIDE, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
		      AR_PHY_65NM_RXRF_GAINSTAGES_LNAON_CALDC, 0x0);

	अगर (AR_SREV_9003_PCOEM(ah) || AR_SREV_9330_11(ah)) अणु
		अगर (is_2g)
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
				      AR_PHY_65NM_RXRF_GAINSTAGES_LNA2G_GAIN_OVR, 0x0);
		अन्यथा
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
				      AR_PHY_65NM_RXRF_GAINSTAGES_LNA5G_GAIN_OVR, 0x0);
	पूर्ण

	/*
	 * Turn off RXON.
	 */
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXTX2(chain),
		      AR_PHY_65NM_RXTX2_RXON_OVR, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXTX2(chain),
		      AR_PHY_65NM_RXTX2_RXON, 0x0);

	/*
	 * Turn on AGC क्रम cal.
	 */
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_OVERRIDE, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_ON_OVR, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_CAL_OVR, 0x1);

	अगर (AR_SREV_9330_11(ah))
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR, 0x0);

	अगर (is_2g)
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC2G_DBDAC_OVR,
			      peak_detect_threshold);
	अन्यथा
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC5G_DBDAC_OVR,
			      peak_detect_threshold);

	क्रम (i = 6; i > 0; i--) अणु
		offset[i] = BIT(i - 1);
		test = total + offset[i];

		अगर (is_2g)
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
				      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR,
				      test);
		अन्यथा
			REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
				      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR,
				      test);
		udelay(100);
		agc_out = REG_READ_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
					 AR_PHY_65NM_RXRF_AGC_AGC_OUT);
		offset[i] = (agc_out) ? 0 : 1;
		total += (offset[i] << (i - 1));
	पूर्ण

	अगर (is_2g)
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR, total);
	अन्यथा
		REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
			      AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR, total);

	/*
	 * Turn on LNA.
	 */
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_GAINSTAGES(chain),
		      AR_PHY_65NM_RXRF_GAINSTAGES_RX_OVERRIDE, 0);
	/*
	 * Turn off RXON.
	 */
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXTX2(chain),
		      AR_PHY_65NM_RXTX2_RXON_OVR, 0);
	/*
	 * Turn off peak detect calibration.
	 */
	REG_RMW_FIELD(ah, AR_PHY_65NM_RXRF_AGC(chain),
		      AR_PHY_65NM_RXRF_AGC_AGC_CAL_OVR, 0);
पूर्ण

अटल व्योम ar9003_hw_करो_pcoem_manual_peak_cal(काष्ठा ath_hw *ah,
					       काष्ठा ath9k_channel *chan,
					       bool run_rtt_cal)
अणु
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	पूर्णांक i;

	अगर ((ah->caps.hw_caps & ATH9K_HW_CAP_RTT) && !run_rtt_cal)
		वापस;

	क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
		अगर (!(ah->rxchainmask & (1 << i)))
			जारी;
		ar9003_hw_manual_peak_cal(ah, i, IS_CHAN_2GHZ(chan));
	पूर्ण

	अगर (caldata)
		set_bit(SW_PKDET_DONE, &caldata->cal_flags);

	अगर ((ah->caps.hw_caps & ATH9K_HW_CAP_RTT) && caldata) अणु
		अगर (IS_CHAN_2GHZ(chan))अणु
			caldata->caldac[0] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(0),
						    AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR);
			caldata->caldac[1] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(1),
						    AR_PHY_65NM_RXRF_AGC_AGC2G_CALDAC_OVR);
		पूर्ण अन्यथा अणु
			caldata->caldac[0] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(0),
						    AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR);
			caldata->caldac[1] = REG_READ_FIELD(ah,
						    AR_PHY_65NM_RXRF_AGC(1),
						    AR_PHY_65NM_RXRF_AGC_AGC5G_CALDAC_OVR);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_cl_cal_post_proc(काष्ठा ath_hw *ah, bool is_reusable)
अणु
	u32 cl_idx[AR9300_MAX_CHAINS] = अणु AR_PHY_CL_TAB_0,
					  AR_PHY_CL_TAB_1,
					  AR_PHY_CL_TAB_2 पूर्ण;
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	bool txclcal_करोne = false;
	पूर्णांक i, j;

	अगर (!caldata || !(ah->enabled_cals & TX_CL_CAL))
		वापस;

	txclcal_करोne = !!(REG_READ(ah, AR_PHY_AGC_CONTROL) &
			  AR_PHY_AGC_CONTROL_CLC_SUCCESS);

	अगर (test_bit(TXCLCAL_DONE, &caldata->cal_flags)) अणु
		क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
			अगर (!(ah->txchainmask & (1 << i)))
				जारी;
			क्रम (j = 0; j < MAX_CL_TAB_ENTRY; j++)
				REG_WRITE(ah, CL_TAB_ENTRY(cl_idx[i]),
					  caldata->tx_clcal[i][j]);
		पूर्ण
	पूर्ण अन्यथा अगर (is_reusable && txclcal_करोne) अणु
		क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
			अगर (!(ah->txchainmask & (1 << i)))
				जारी;
			क्रम (j = 0; j < MAX_CL_TAB_ENTRY; j++)
				caldata->tx_clcal[i][j] =
					REG_READ(ah, CL_TAB_ENTRY(cl_idx[i]));
		पूर्ण
		set_bit(TXCLCAL_DONE, &caldata->cal_flags);
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_init_cal_common(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;

	/* Initialize list poपूर्णांकers */
	ah->cal_list = ah->cal_list_last = ah->cal_list_curr = शून्य;

	INIT_CAL(&ah->iq_caldata);
	INSERT_CAL(ah, &ah->iq_caldata);

	/* Initialize current poपूर्णांकer to first element in list */
	ah->cal_list_curr = ah->cal_list;

	अगर (ah->cal_list_curr)
		ath9k_hw_reset_calibration(ah, ah->cal_list_curr);

	अगर (caldata)
		caldata->CalValid = 0;
पूर्ण

अटल bool ar9003_hw_init_cal_pcoem(काष्ठा ath_hw *ah,
				     काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	bool txiqcal_करोne = false;
	bool is_reusable = true, status = true;
	bool run_rtt_cal = false, run_agc_cal;
	bool rtt = !!(ah->caps.hw_caps & ATH9K_HW_CAP_RTT);
	u32 rx_delay = 0;
	u32 agc_ctrl = 0, agc_supp_cals = AR_PHY_AGC_CONTROL_OFFSET_CAL |
					  AR_PHY_AGC_CONTROL_FLTR_CAL   |
					  AR_PHY_AGC_CONTROL_PKDET_CAL;

	/* Use chip chainmask only क्रम calibration */
	ar9003_hw_set_chain_masks(ah, ah->caps.rx_chainmask, ah->caps.tx_chainmask);

	अगर (rtt) अणु
		अगर (!ar9003_hw_rtt_restore(ah, chan))
			run_rtt_cal = true;

		अगर (run_rtt_cal)
			ath_dbg(common, CALIBRATE, "RTT calibration to be done\n");
	पूर्ण

	run_agc_cal = run_rtt_cal;

	अगर (run_rtt_cal) अणु
		ar9003_hw_rtt_enable(ah);
		ar9003_hw_rtt_set_mask(ah, 0x00);
		ar9003_hw_rtt_clear_hist(ah);
	पूर्ण

	अगर (rtt) अणु
		अगर (!run_rtt_cal) अणु
			agc_ctrl = REG_READ(ah, AR_PHY_AGC_CONTROL);
			agc_supp_cals &= agc_ctrl;
			agc_ctrl &= ~(AR_PHY_AGC_CONTROL_OFFSET_CAL |
				      AR_PHY_AGC_CONTROL_FLTR_CAL |
				      AR_PHY_AGC_CONTROL_PKDET_CAL);
			REG_WRITE(ah, AR_PHY_AGC_CONTROL, agc_ctrl);
		पूर्ण अन्यथा अणु
			अगर (ah->ah_flags & AH_FASTCC)
				run_agc_cal = true;
		पूर्ण
	पूर्ण

	अगर (ah->enabled_cals & TX_CL_CAL) अणु
		अगर (caldata && test_bit(TXCLCAL_DONE, &caldata->cal_flags))
			REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL,
				    AR_PHY_CL_CAL_ENABLE);
		अन्यथा अणु
			REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL,
				    AR_PHY_CL_CAL_ENABLE);
			run_agc_cal = true;
		पूर्ण
	पूर्ण

	अगर ((IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan)) ||
	    !(ah->enabled_cals & TX_IQ_CAL))
		जाओ skip_tx_iqcal;

	/* Do Tx IQ Calibration */
	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_1,
		      AR_PHY_TX_IQCAL_CONTROL_1_IQCORR_I_Q_COFF_DELPT,
		      DELPT);

	/*
	 * For AR9485 or later chips, TxIQ cal runs as part of
	 * AGC calibration
	 */
	अगर (ah->enabled_cals & TX_IQ_ON_AGC_CAL) अणु
		अगर (caldata && !test_bit(TXIQCAL_DONE, &caldata->cal_flags))
			REG_SET_BIT(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				    AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL);
		अन्यथा
			REG_CLR_BIT(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				    AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL);
		txiqcal_करोne = run_agc_cal = true;
	पूर्ण

skip_tx_iqcal:
	अगर (ath9k_hw_mci_is_enabled(ah) && IS_CHAN_2GHZ(chan) && run_agc_cal)
		ar9003_mci_init_cal_req(ah, &is_reusable);

	अगर (REG_READ(ah, AR_PHY_CL_CAL_CTL) & AR_PHY_CL_CAL_ENABLE) अणु
		rx_delay = REG_READ(ah, AR_PHY_RX_DELAY);
		/* Disable BB_active */
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_DIS);
		udelay(5);
		REG_WRITE(ah, AR_PHY_RX_DELAY, AR_PHY_RX_DELAY_DELAY);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);
	पूर्ण

	अगर (run_agc_cal || !(ah->ah_flags & AH_FASTCC)) अणु
		/* Calibrate the AGC */
		REG_WRITE(ah, AR_PHY_AGC_CONTROL,
			  REG_READ(ah, AR_PHY_AGC_CONTROL) |
			  AR_PHY_AGC_CONTROL_CAL);

		/* Poll क्रम offset calibration complete */
		status = ath9k_hw_रुको(ah, AR_PHY_AGC_CONTROL,
				       AR_PHY_AGC_CONTROL_CAL,
				       0, AH_WAIT_TIMEOUT);

		ar9003_hw_करो_pcoem_manual_peak_cal(ah, chan, run_rtt_cal);
	पूर्ण

	अगर (REG_READ(ah, AR_PHY_CL_CAL_CTL) & AR_PHY_CL_CAL_ENABLE) अणु
		REG_WRITE(ah, AR_PHY_RX_DELAY, rx_delay);
		udelay(5);
	पूर्ण

	अगर (ath9k_hw_mci_is_enabled(ah) && IS_CHAN_2GHZ(chan) && run_agc_cal)
		ar9003_mci_init_cal_करोne(ah);

	अगर (rtt && !run_rtt_cal) अणु
		agc_ctrl |= agc_supp_cals;
		REG_WRITE(ah, AR_PHY_AGC_CONTROL, agc_ctrl);
	पूर्ण

	अगर (!status) अणु
		अगर (run_rtt_cal)
			ar9003_hw_rtt_disable(ah);

		ath_dbg(common, CALIBRATE,
			"offset calibration failed to complete in %d ms; noisy environment?\n",
			AH_WAIT_TIMEOUT / 1000);
		वापस false;
	पूर्ण

	अगर (txiqcal_करोne)
		ar9003_hw_tx_iq_cal_post_proc(ah, 0, is_reusable);
	अन्यथा अगर (caldata && test_bit(TXIQCAL_DONE, &caldata->cal_flags))
		ar9003_hw_tx_iq_cal_reload(ah);

	ar9003_hw_cl_cal_post_proc(ah, is_reusable);

	अगर (run_rtt_cal && caldata) अणु
		अगर (is_reusable) अणु
			अगर (!ath9k_hw_rfbus_req(ah)) अणु
				ath_err(ath9k_hw_common(ah),
					"Could not stop baseband\n");
			पूर्ण अन्यथा अणु
				ar9003_hw_rtt_fill_hist(ah);

				अगर (test_bit(SW_PKDET_DONE, &caldata->cal_flags))
					ar9003_hw_rtt_load_hist(ah);
			पूर्ण

			ath9k_hw_rfbus_करोne(ah);
		पूर्ण

		ar9003_hw_rtt_disable(ah);
	पूर्ण

	/* Revert chainmask to runसमय parameters */
	ar9003_hw_set_chain_masks(ah, ah->rxchainmask, ah->txchainmask);

	ar9003_hw_init_cal_common(ah);

	वापस true;
पूर्ण

अटल bool करो_ar9003_agc_cal(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	bool status;

	REG_WRITE(ah, AR_PHY_AGC_CONTROL,
		  REG_READ(ah, AR_PHY_AGC_CONTROL) |
		  AR_PHY_AGC_CONTROL_CAL);

	status = ath9k_hw_रुको(ah, AR_PHY_AGC_CONTROL,
			       AR_PHY_AGC_CONTROL_CAL,
			       0, AH_WAIT_TIMEOUT);
	अगर (!status) अणु
		ath_dbg(common, CALIBRATE,
			"offset calibration failed to complete in %d ms,"
			"noisy environment?\n",
			AH_WAIT_TIMEOUT / 1000);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool ar9003_hw_init_cal_soc(काष्ठा ath_hw *ah,
				   काष्ठा ath9k_channel *chan)
अणु
	bool txiqcal_करोne = false;
	bool status = true;
	bool run_agc_cal = false, sep_iq_cal = false;
	पूर्णांक i = 0;

	/* Use chip chainmask only क्रम calibration */
	ar9003_hw_set_chain_masks(ah, ah->caps.rx_chainmask, ah->caps.tx_chainmask);

	अगर (ah->enabled_cals & TX_CL_CAL) अणु
		REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
		run_agc_cal = true;
	पूर्ण

	अगर (IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan))
		जाओ skip_tx_iqcal;

	/* Do Tx IQ Calibration */
	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_1,
		      AR_PHY_TX_IQCAL_CONTROL_1_IQCORR_I_Q_COFF_DELPT,
		      DELPT);

	/*
	 * For AR9485 or later chips, TxIQ cal runs as part of
	 * AGC calibration. Specअगरically, AR9550 in SoC chips.
	 */
	अगर (ah->enabled_cals & TX_IQ_ON_AGC_CAL) अणु
		अगर (REG_READ_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				   AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL)) अणु
				txiqcal_करोne = true;
		पूर्ण अन्यथा अणु
			txiqcal_करोne = false;
		पूर्ण
		run_agc_cal = true;
	पूर्ण अन्यथा अणु
		sep_iq_cal = true;
		run_agc_cal = true;
	पूर्ण

	/*
	 * In the SoC family, this will run क्रम AR9300, AR9331 and AR9340.
	 */
	अगर (sep_iq_cal) अणु
		txiqcal_करोne = ar9003_hw_tx_iq_cal_run(ah);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_DIS);
		udelay(5);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);
	पूर्ण

	अगर (AR_SREV_9550(ah) && IS_CHAN_2GHZ(chan)) अणु
		अगर (!ar9003_hw_dynamic_osdac_selection(ah, txiqcal_करोne))
			वापस false;
	पूर्ण

skip_tx_iqcal:
	अगर (run_agc_cal || !(ah->ah_flags & AH_FASTCC)) अणु
		क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
			अगर (!(ah->rxchainmask & (1 << i)))
				जारी;

			ar9003_hw_manual_peak_cal(ah, i,
						  IS_CHAN_2GHZ(chan));
		पूर्ण

		/*
		 * For non-AR9550 chips, we just trigger AGC calibration
		 * in the HW, poll क्रम completion and then process
		 * the results.
		 *
		 * For AR955x, we run it multiple बार and use
		 * median IQ correction.
		 */
		अगर (!AR_SREV_9550(ah)) अणु
			status = करो_ar9003_agc_cal(ah);
			अगर (!status)
				वापस false;

			अगर (txiqcal_करोne)
				ar9003_hw_tx_iq_cal_post_proc(ah, 0, false);
		पूर्ण अन्यथा अणु
			अगर (!txiqcal_करोne) अणु
				status = करो_ar9003_agc_cal(ah);
				अगर (!status)
					वापस false;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < MAXIQCAL; i++) अणु
					status = करो_ar9003_agc_cal(ah);
					अगर (!status)
						वापस false;
					ar9003_hw_tx_iq_cal_post_proc(ah, i, false);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Revert chainmask to runसमय parameters */
	ar9003_hw_set_chain_masks(ah, ah->rxchainmask, ah->txchainmask);

	ar9003_hw_init_cal_common(ah);

	वापस true;
पूर्ण

व्योम ar9003_hw_attach_calib_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_निजी_ops *priv_ops = ath9k_hw_निजी_ops(ah);
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(ah);

	अगर (AR_SREV_9003_PCOEM(ah))
		priv_ops->init_cal = ar9003_hw_init_cal_pcoem;
	अन्यथा
		priv_ops->init_cal = ar9003_hw_init_cal_soc;

	priv_ops->init_cal_settings = ar9003_hw_init_cal_settings;
	priv_ops->setup_calibration = ar9003_hw_setup_calibration;

	ops->calibrate = ar9003_hw_calibrate;
पूर्ण
