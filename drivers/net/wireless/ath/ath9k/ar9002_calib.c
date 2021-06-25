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
#समावेश "ar9002_phy.h"

#घोषणा AR9285_CLCAL_REDO_THRESH    1
/* AGC & I/Q calibrations समय limit, ms */
#घोषणा AR9002_CAL_MAX_TIME		30000

क्रमागत ar9002_cal_types अणु
	ADC_GAIN_CAL = BIT(0),
	ADC_DC_CAL = BIT(1),
	IQ_MISMATCH_CAL = BIT(2),
पूर्ण;

अटल bool ar9002_hw_is_cal_supported(काष्ठा ath_hw *ah,
				काष्ठा ath9k_channel *chan,
				क्रमागत ar9002_cal_types cal_type)
अणु
	bool supported = false;
	चयन (ah->supp_cals & cal_type) अणु
	हाल IQ_MISMATCH_CAL:
		supported = true;
		अवरोध;
	हाल ADC_GAIN_CAL:
	हाल ADC_DC_CAL:
		/* Run even/odd ADCs calibrations क्रम HT40 channels only */
		अगर (IS_CHAN_HT40(chan))
			supported = true;
		अवरोध;
	पूर्ण
	वापस supported;
पूर्ण

अटल व्योम ar9002_hw_setup_calibration(काष्ठा ath_hw *ah,
					काष्ठा ath9k_cal_list *currCal)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	REG_RMW_FIELD(ah, AR_PHY_TIMING_CTRL4(0),
		      AR_PHY_TIMING_CTRL4_IQCAL_LOG_COUNT_MAX,
		      currCal->calData->calCountMax);

	चयन (currCal->calData->calType) अणु
	हाल IQ_MISMATCH_CAL:
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_IQ);
		ath_dbg(common, CALIBRATE,
			"starting IQ Mismatch Calibration\n");
		अवरोध;
	हाल ADC_GAIN_CAL:
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_ADC_GAIN);
		ath_dbg(common, CALIBRATE, "starting ADC Gain Calibration\n");
		अवरोध;
	हाल ADC_DC_CAL:
		REG_WRITE(ah, AR_PHY_CALMODE, AR_PHY_CALMODE_ADC_DC_PER);
		ath_dbg(common, CALIBRATE, "starting ADC DC Calibration\n");
		अवरोध;
	पूर्ण

	REG_SET_BIT(ah, AR_PHY_TIMING_CTRL4(0),
		    AR_PHY_TIMING_CTRL4_DO_CAL);
पूर्ण

अटल bool ar9002_hw_per_calibration(काष्ठा ath_hw *ah,
				      काष्ठा ath9k_channel *ichan,
				      u8 rxchainmask,
				      काष्ठा ath9k_cal_list *currCal)
अणु
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	bool iscalकरोne = false;

	अगर (currCal->calState == CAL_RUNNING) अणु
		अगर (!(REG_READ(ah, AR_PHY_TIMING_CTRL4(0)) &
		      AR_PHY_TIMING_CTRL4_DO_CAL)) अणु

			currCal->calData->calCollect(ah);
			ah->cal_samples++;

			अगर (ah->cal_samples >=
			    currCal->calData->calNumSamples) अणु
				पूर्णांक i, numChains = 0;
				क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
					अगर (rxchainmask & (1 << i))
						numChains++;
				पूर्ण

				currCal->calData->calPostProc(ah, numChains);
				caldata->CalValid |= currCal->calData->calType;
				currCal->calState = CAL_DONE;
				iscalकरोne = true;
			पूर्ण अन्यथा अणु
				ar9002_hw_setup_calibration(ah, currCal);
			पूर्ण
		पूर्ण अन्यथा अगर (समय_after(jअगरfies, ah->cal_start_समय +
				      msecs_to_jअगरfies(AR9002_CAL_MAX_TIME))) अणु
			REG_CLR_BIT(ah, AR_PHY_TIMING_CTRL4(0),
				    AR_PHY_TIMING_CTRL4_DO_CAL);
			ath_dbg(ath9k_hw_common(ah), CALIBRATE,
				"calibration timeout\n");
			currCal->calState = CAL_WAITING;	/* Try later */
			iscalकरोne = true;
		पूर्ण
	पूर्ण अन्यथा अगर (!(caldata->CalValid & currCal->calData->calType)) अणु
		ath9k_hw_reset_calibration(ah, currCal);
	पूर्ण

	वापस iscalकरोne;
पूर्ण

अटल व्योम ar9002_hw_iqcal_collect(काष्ठा ath_hw *ah)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
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

अटल व्योम ar9002_hw_adc_gaincal_collect(काष्ठा ath_hw *ah)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
		ah->totalAdcIOddPhase[i] +=
			REG_READ(ah, AR_PHY_CAL_MEAS_0(i));
		ah->totalAdcIEvenPhase[i] +=
			REG_READ(ah, AR_PHY_CAL_MEAS_1(i));
		ah->totalAdcQOddPhase[i] +=
			REG_READ(ah, AR_PHY_CAL_MEAS_2(i));
		ah->totalAdcQEvenPhase[i] +=
			REG_READ(ah, AR_PHY_CAL_MEAS_3(i));

		ath_dbg(ath9k_hw_common(ah), CALIBRATE,
			"%d: Chn %d oddi=0x%08x; eveni=0x%08x; oddq=0x%08x; evenq=0x%08x;\n",
			ah->cal_samples, i,
			ah->totalAdcIOddPhase[i],
			ah->totalAdcIEvenPhase[i],
			ah->totalAdcQOddPhase[i],
			ah->totalAdcQEvenPhase[i]);
	पूर्ण
पूर्ण

अटल व्योम ar9002_hw_adc_dccal_collect(काष्ठा ath_hw *ah)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
		ah->totalAdcDcOffsetIOddPhase[i] +=
			(पूर्णांक32_t) REG_READ(ah, AR_PHY_CAL_MEAS_0(i));
		ah->totalAdcDcOffsetIEvenPhase[i] +=
			(पूर्णांक32_t) REG_READ(ah, AR_PHY_CAL_MEAS_1(i));
		ah->totalAdcDcOffsetQOddPhase[i] +=
			(पूर्णांक32_t) REG_READ(ah, AR_PHY_CAL_MEAS_2(i));
		ah->totalAdcDcOffsetQEvenPhase[i] +=
			(पूर्णांक32_t) REG_READ(ah, AR_PHY_CAL_MEAS_3(i));

		ath_dbg(ath9k_hw_common(ah), CALIBRATE,
			"%d: Chn %d oddi=0x%08x; eveni=0x%08x; oddq=0x%08x; evenq=0x%08x;\n",
			ah->cal_samples, i,
			ah->totalAdcDcOffsetIOddPhase[i],
			ah->totalAdcDcOffsetIEvenPhase[i],
			ah->totalAdcDcOffsetQOddPhase[i],
			ah->totalAdcDcOffsetQEvenPhase[i]);
	पूर्ण
पूर्ण

अटल व्योम ar9002_hw_iqcalibrate(काष्ठा ath_hw *ah, u8 numChains)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 घातerMeasQ, घातerMeasI, iqCorrMeas;
	u32 qCoffDenom, iCoffDenom;
	पूर्णांक32_t qCoff, iCoff;
	पूर्णांक iqCorrNeg, i;

	क्रम (i = 0; i < numChains; i++) अणु
		घातerMeasI = ah->totalPowerMeasI[i];
		घातerMeasQ = ah->totalPowerMeasQ[i];
		iqCorrMeas = ah->totalIqCorrMeas[i];

		ath_dbg(common, CALIBRATE,
			"Starting IQ Cal and Correction for Chain %d\n",
			i);

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

		iCoffDenom = (घातerMeasI / 2 + घातerMeasQ / 2) / 128;
		qCoffDenom = घातerMeasQ / 64;

		अगर ((घातerMeasQ != 0) && (iCoffDenom != 0) &&
		    (qCoffDenom != 0)) अणु
			iCoff = iqCorrMeas / iCoffDenom;
			qCoff = घातerMeasI / qCoffDenom - 64;
			ath_dbg(common, CALIBRATE, "Chn %d iCoff = 0x%08x\n",
				i, iCoff);
			ath_dbg(common, CALIBRATE, "Chn %d qCoff = 0x%08x\n",
				i, qCoff);

			iCoff = iCoff & 0x3f;
			ath_dbg(common, CALIBRATE,
				"New: Chn %d iCoff = 0x%08x\n", i, iCoff);
			अगर (iqCorrNeg == 0x0)
				iCoff = 0x40 - iCoff;

			अगर (qCoff > 15)
				qCoff = 15;
			अन्यथा अगर (qCoff <= -16)
				qCoff = -16;

			ath_dbg(common, CALIBRATE,
				"Chn %d : iCoff = 0x%x  qCoff = 0x%x\n",
				i, iCoff, qCoff);

			REG_RMW_FIELD(ah, AR_PHY_TIMING_CTRL4(i),
				      AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF,
				      iCoff);
			REG_RMW_FIELD(ah, AR_PHY_TIMING_CTRL4(i),
				      AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF,
				      qCoff);
			ath_dbg(common, CALIBRATE,
				"IQ Cal and Correction done for Chain %d\n",
				i);
		पूर्ण
	पूर्ण

	REG_SET_BIT(ah, AR_PHY_TIMING_CTRL4(0),
		    AR_PHY_TIMING_CTRL4_IQCORR_ENABLE);
पूर्ण

अटल व्योम ar9002_hw_adc_gaincal_calibrate(काष्ठा ath_hw *ah, u8 numChains)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 iOddMeasOffset, iEvenMeasOffset, qOddMeasOffset, qEvenMeasOffset;
	u32 qGainMismatch, iGainMismatch, val, i;

	क्रम (i = 0; i < numChains; i++) अणु
		iOddMeasOffset = ah->totalAdcIOddPhase[i];
		iEvenMeasOffset = ah->totalAdcIEvenPhase[i];
		qOddMeasOffset = ah->totalAdcQOddPhase[i];
		qEvenMeasOffset = ah->totalAdcQEvenPhase[i];

		ath_dbg(common, CALIBRATE,
			"Starting ADC Gain Cal for Chain %d\n", i);

		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_i = 0x%08x\n",
			i, iOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_i = 0x%08x\n",
			i, iEvenMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_q = 0x%08x\n",
			i, qOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_q = 0x%08x\n",
			i, qEvenMeasOffset);

		अगर (iOddMeasOffset != 0 && qEvenMeasOffset != 0) अणु
			iGainMismatch =
				((iEvenMeasOffset * 32) /
				 iOddMeasOffset) & 0x3f;
			qGainMismatch =
				((qOddMeasOffset * 32) /
				 qEvenMeasOffset) & 0x3f;

			ath_dbg(common, CALIBRATE,
				"Chn %d gain_mismatch_i = 0x%08x\n",
				i, iGainMismatch);
			ath_dbg(common, CALIBRATE,
				"Chn %d gain_mismatch_q = 0x%08x\n",
				i, qGainMismatch);

			val = REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i));
			val &= 0xfffff000;
			val |= (qGainMismatch) | (iGainMismatch << 6);
			REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i), val);

			ath_dbg(common, CALIBRATE,
				"ADC Gain Cal done for Chain %d\n", i);
		पूर्ण
	पूर्ण

	REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0),
		  REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0)) |
		  AR_PHY_NEW_ADC_GAIN_CORR_ENABLE);
पूर्ण

अटल व्योम ar9002_hw_adc_dccal_calibrate(काष्ठा ath_hw *ah, u8 numChains)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 iOddMeasOffset, iEvenMeasOffset, val, i;
	पूर्णांक32_t qOddMeasOffset, qEvenMeasOffset, qDcMismatch, iDcMismatch;
	स्थिर काष्ठा ath9k_percal_data *calData =
		ah->cal_list_curr->calData;
	u32 numSamples =
		(1 << (calData->calCountMax + 5)) * calData->calNumSamples;

	क्रम (i = 0; i < numChains; i++) अणु
		iOddMeasOffset = ah->totalAdcDcOffsetIOddPhase[i];
		iEvenMeasOffset = ah->totalAdcDcOffsetIEvenPhase[i];
		qOddMeasOffset = ah->totalAdcDcOffsetQOddPhase[i];
		qEvenMeasOffset = ah->totalAdcDcOffsetQEvenPhase[i];

		ath_dbg(common, CALIBRATE,
			"Starting ADC DC Offset Cal for Chain %d\n", i);

		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_i = %d\n",
			i, iOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_i = %d\n",
			i, iEvenMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_odd_q = %d\n",
			i, qOddMeasOffset);
		ath_dbg(common, CALIBRATE, "Chn %d pwr_meas_even_q = %d\n",
			i, qEvenMeasOffset);

		iDcMismatch = (((iEvenMeasOffset - iOddMeasOffset) * 2) /
			       numSamples) & 0x1ff;
		qDcMismatch = (((qOddMeasOffset - qEvenMeasOffset) * 2) /
			       numSamples) & 0x1ff;

		ath_dbg(common, CALIBRATE,
			"Chn %d dc_offset_mismatch_i = 0x%08x\n",
			i, iDcMismatch);
		ath_dbg(common, CALIBRATE,
			"Chn %d dc_offset_mismatch_q = 0x%08x\n",
			i, qDcMismatch);

		val = REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i));
		val &= 0xc0000fff;
		val |= (qDcMismatch << 12) | (iDcMismatch << 21);
		REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(i), val);

		ath_dbg(common, CALIBRATE,
			"ADC DC Offset Cal done for Chain %d\n", i);
	पूर्ण

	REG_WRITE(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0),
		  REG_READ(ah, AR_PHY_NEW_ADC_DC_GAIN_CORR(0)) |
		  AR_PHY_NEW_ADC_DC_OFFSET_CORR_ENABLE);
पूर्ण

अटल व्योम ar9287_hw_olc_temp_compensation(काष्ठा ath_hw *ah)
अणु
	u32 rddata;
	पूर्णांक32_t delta, currPDADC, slope;

	rddata = REG_READ(ah, AR_PHY_TX_PWRCTRL4);
	currPDADC = MS(rddata, AR_PHY_TX_PWRCTRL_PD_AVG_OUT);

	अगर (ah->initPDADC == 0 || currPDADC == 0) अणु
		/*
		 * Zero value indicates that no frames have been transmitted
		 * yet, can't करो temperature compensation until frames are
		 * transmitted.
		 */
		वापस;
	पूर्ण अन्यथा अणु
		slope = ah->eep_ops->get_eeprom(ah, EEP_TEMPSENSE_SLOPE);

		अगर (slope == 0) अणु /* to aव्योम भागide by zero हाल */
			delta = 0;
		पूर्ण अन्यथा अणु
			delta = ((currPDADC - ah->initPDADC)*4) / slope;
		पूर्ण
		REG_RMW_FIELD(ah, AR_PHY_CH0_TX_PWRCTRL11,
			      AR_PHY_TX_PWRCTRL_OLPC_TEMP_COMP, delta);
		REG_RMW_FIELD(ah, AR_PHY_CH1_TX_PWRCTRL11,
			      AR_PHY_TX_PWRCTRL_OLPC_TEMP_COMP, delta);
	पूर्ण
पूर्ण

अटल व्योम ar9280_hw_olc_temp_compensation(काष्ठा ath_hw *ah)
अणु
	u32 rddata, i;
	पूर्णांक delta, currPDADC, regval;

	rddata = REG_READ(ah, AR_PHY_TX_PWRCTRL4);
	currPDADC = MS(rddata, AR_PHY_TX_PWRCTRL_PD_AVG_OUT);

	अगर (ah->initPDADC == 0 || currPDADC == 0)
		वापस;

	अगर (ah->eep_ops->get_eeprom(ah, EEP_DAC_HPWR_5G))
		delta = (currPDADC - ah->initPDADC + 4) / 8;
	अन्यथा
		delta = (currPDADC - ah->initPDADC + 5) / 10;

	अगर (delta != ah->PDADCdelta) अणु
		ah->PDADCdelta = delta;
		क्रम (i = 1; i < AR9280_TX_GAIN_TABLE_SIZE; i++) अणु
			regval = ah->originalGain[i] - delta;
			अगर (regval < 0)
				regval = 0;

			REG_RMW_FIELD(ah,
				      AR_PHY_TX_GAIN_TBL1 + i * 4,
				      AR_PHY_TX_GAIN, regval);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar9271_hw_pa_cal(काष्ठा ath_hw *ah, bool is_reset)
अणु
	u32 regVal;
	अचिन्हित पूर्णांक i;
	u32 regList[][2] = अणु
		अणु AR9285_AN_TOP3, 0 पूर्ण,
		अणु AR9285_AN_RXTXBB1, 0 पूर्ण,
		अणु AR9285_AN_RF2G1, 0 पूर्ण,
		अणु AR9285_AN_RF2G2, 0 पूर्ण,
		अणु AR9285_AN_TOP2, 0 पूर्ण,
		अणु AR9285_AN_RF2G8, 0 पूर्ण,
		अणु AR9285_AN_RF2G7, 0 पूर्ण,
		अणु AR9285_AN_RF2G3, 0 पूर्ण,
	पूर्ण;

	REG_READ_ARRAY(ah, regList, ARRAY_SIZE(regList));

	ENABLE_REG_RMW_BUFFER(ah);
	/* 7834, b1=0 */
	REG_CLR_BIT(ah, AR9285_AN_RF2G6, 1 << 0);
	/* 9808, b27=1 */
	REG_SET_BIT(ah, 0x9808, 1 << 27);
	/* 786c,b23,1, pwddac=1 */
	REG_SET_BIT(ah, AR9285_AN_TOP3, AR9285_AN_TOP3_PWDDAC);
	/* 7854, b5,1, pdrxtxbb=1 */
	REG_SET_BIT(ah, AR9285_AN_RXTXBB1, AR9285_AN_RXTXBB1_PDRXTXBB1);
	/* 7854, b7,1, pdv2i=1 */
	REG_SET_BIT(ah, AR9285_AN_RXTXBB1, AR9285_AN_RXTXBB1_PDV2I);
	/* 7854, b8,1, pddacपूर्णांकerface=1 */
	REG_SET_BIT(ah, AR9285_AN_RXTXBB1, AR9285_AN_RXTXBB1_PDDACIF);
	/* 7824,b12,0, offcal=0 */
	REG_CLR_BIT(ah, AR9285_AN_RF2G2, AR9285_AN_RF2G2_OFFCAL);
	/* 7838, b1,0, pwddb=0 */
	REG_CLR_BIT(ah, AR9285_AN_RF2G7, AR9285_AN_RF2G7_PWDDB);
	/* 7820,b11,0, enpacal=0 */
	REG_CLR_BIT(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_ENPACAL);
	/* 7820,b25,1, pdpadrv1=0 */
	REG_CLR_BIT(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_PDPADRV1);
	/* 7820,b24,0, pdpadrv2=0 */
	REG_CLR_BIT(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_PDPADRV2);
	/* 7820,b23,0, pdpaout=0 */
	REG_CLR_BIT(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_PDPAOUT);
	/* 783c,b14-16,7, padrvgn2tab_0=7 */
	REG_RMW_FIELD(ah, AR9285_AN_RF2G8, AR9285_AN_RF2G8_PADRVGN2TAB0, 7);
	/*
	 * 7838,b29-31,0, padrvgn1tab_0=0
	 * करोes not matter since we turn it off
	 */
	REG_RMW_FIELD(ah, AR9285_AN_RF2G7, AR9285_AN_RF2G7_PADRVGN2TAB0, 0);
	/* 7828, b0-11, ccom=fff */
	REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9271_AN_RF2G3_CCOMP, 0xfff);
	REG_RMW_BUFFER_FLUSH(ah);

	/* Set:
	 * localmode=1,bmode=1,bmoderxtx=1,synthon=1,
	 * txon=1,paon=1,oscon=1,synthon_क्रमce=1
	 */
	REG_WRITE(ah, AR9285_AN_TOP2, 0xca0358a0);
	udelay(30);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G6, AR9271_AN_RF2G6_OFFS, 0);

	/* find off_6_1; */
	क्रम (i = 6; i > 0; i--) अणु
		regVal = REG_READ(ah, AR9285_AN_RF2G6);
		regVal |= (1 << (20 + i));
		REG_WRITE(ah, AR9285_AN_RF2G6, regVal);
		udelay(1);
		/* regVal = REG_READ(ah, 0x7834); */
		regVal &= (~(0x1 << (20 + i)));
		regVal |= (MS(REG_READ(ah, AR9285_AN_RF2G9),
			      AR9285_AN_RXTXBB1_SPARE9)
			    << (20 + i));
		REG_WRITE(ah, AR9285_AN_RF2G6, regVal);
	पूर्ण

	regVal = (regVal >> 20) & 0x7f;

	/* Update PA cal info */
	अगर ((!is_reset) && (ah->pacal_info.prev_offset == regVal)) अणु
		अगर (ah->pacal_info.max_skipcount < MAX_PACAL_SKIPCOUNT)
			ah->pacal_info.max_skipcount =
				2 * ah->pacal_info.max_skipcount;
		ah->pacal_info.skipcount = ah->pacal_info.max_skipcount;
	पूर्ण अन्यथा अणु
		ah->pacal_info.max_skipcount = 1;
		ah->pacal_info.skipcount = 0;
		ah->pacal_info.prev_offset = regVal;
	पूर्ण


	ENABLE_REG_RMW_BUFFER(ah);
	/* 7834, b1=1 */
	REG_SET_BIT(ah, AR9285_AN_RF2G6, 1 << 0);
	/* 9808, b27=0 */
	REG_CLR_BIT(ah, 0x9808, 1 << 27);
	REG_RMW_BUFFER_FLUSH(ah);

	ENABLE_REGWRITE_BUFFER(ah);
	क्रम (i = 0; i < ARRAY_SIZE(regList); i++)
		REG_WRITE(ah, regList[i][0], regList[i][1]);

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

अटल अंतरभूत व्योम ar9285_hw_pa_cal(काष्ठा ath_hw *ah, bool is_reset)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 regVal;
	पूर्णांक i, offset, offs_6_1, offs_0;
	u32 ccomp_org, reg_field;
	u32 regList[][2] = अणु
		अणु 0x786c, 0 पूर्ण,
		अणु 0x7854, 0 पूर्ण,
		अणु 0x7820, 0 पूर्ण,
		अणु 0x7824, 0 पूर्ण,
		अणु 0x7868, 0 पूर्ण,
		अणु 0x783c, 0 पूर्ण,
		अणु 0x7838, 0 पूर्ण,
	पूर्ण;

	ath_dbg(common, CALIBRATE, "Running PA Calibration\n");

	/* PA CAL is not needed क्रम high घातer solution */
	अगर (ah->eep_ops->get_eeprom(ah, EEP_TXGAIN_TYPE) ==
	    AR5416_EEP_TXGAIN_HIGH_POWER)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(regList); i++)
		regList[i][1] = REG_READ(ah, regList[i][0]);

	regVal = REG_READ(ah, 0x7834);
	regVal &= (~(0x1));
	REG_WRITE(ah, 0x7834, regVal);
	regVal = REG_READ(ah, 0x9808);
	regVal |= (0x1 << 27);
	REG_WRITE(ah, 0x9808, regVal);

	REG_RMW_FIELD(ah, AR9285_AN_TOP3, AR9285_AN_TOP3_PWDDAC, 1);
	REG_RMW_FIELD(ah, AR9285_AN_RXTXBB1, AR9285_AN_RXTXBB1_PDRXTXBB1, 1);
	REG_RMW_FIELD(ah, AR9285_AN_RXTXBB1, AR9285_AN_RXTXBB1_PDV2I, 1);
	REG_RMW_FIELD(ah, AR9285_AN_RXTXBB1, AR9285_AN_RXTXBB1_PDDACIF, 1);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G2, AR9285_AN_RF2G2_OFFCAL, 0);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G7, AR9285_AN_RF2G7_PWDDB, 0);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_ENPACAL, 0);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_PDPADRV1, 0);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_PDPADRV2, 0);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G1, AR9285_AN_RF2G1_PDPAOUT, 0);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G8, AR9285_AN_RF2G8_PADRVGN2TAB0, 7);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G7, AR9285_AN_RF2G7_PADRVGN2TAB0, 0);
	ccomp_org = MS(REG_READ(ah, AR9285_AN_RF2G6), AR9285_AN_RF2G6_CCOMP);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G6, AR9285_AN_RF2G6_CCOMP, 0xf);

	REG_WRITE(ah, AR9285_AN_TOP2, 0xca0358a0);
	udelay(30);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G6, AR9285_AN_RF2G6_OFFS, 0);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_PDVCCOMP, 0);

	क्रम (i = 6; i > 0; i--) अणु
		regVal = REG_READ(ah, 0x7834);
		regVal |= (1 << (19 + i));
		REG_WRITE(ah, 0x7834, regVal);
		udelay(1);
		regVal = REG_READ(ah, 0x7834);
		regVal &= (~(0x1 << (19 + i)));
		reg_field = MS(REG_READ(ah, 0x7840), AR9285_AN_RXTXBB1_SPARE9);
		regVal |= (reg_field << (19 + i));
		REG_WRITE(ah, 0x7834, regVal);
	पूर्ण

	REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_PDVCCOMP, 1);
	udelay(1);
	reg_field = MS(REG_READ(ah, AR9285_AN_RF2G9), AR9285_AN_RXTXBB1_SPARE9);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_PDVCCOMP, reg_field);
	offs_6_1 = MS(REG_READ(ah, AR9285_AN_RF2G6), AR9285_AN_RF2G6_OFFS);
	offs_0   = MS(REG_READ(ah, AR9285_AN_RF2G3), AR9285_AN_RF2G3_PDVCCOMP);

	offset = (offs_6_1<<1) | offs_0;
	offset = offset - 0;
	offs_6_1 = offset>>1;
	offs_0 = offset & 1;

	अगर ((!is_reset) && (ah->pacal_info.prev_offset == offset)) अणु
		अगर (ah->pacal_info.max_skipcount < MAX_PACAL_SKIPCOUNT)
			ah->pacal_info.max_skipcount =
				2 * ah->pacal_info.max_skipcount;
		ah->pacal_info.skipcount = ah->pacal_info.max_skipcount;
	पूर्ण अन्यथा अणु
		ah->pacal_info.max_skipcount = 1;
		ah->pacal_info.skipcount = 0;
		ah->pacal_info.prev_offset = offset;
	पूर्ण

	REG_RMW_FIELD(ah, AR9285_AN_RF2G6, AR9285_AN_RF2G6_OFFS, offs_6_1);
	REG_RMW_FIELD(ah, AR9285_AN_RF2G3, AR9285_AN_RF2G3_PDVCCOMP, offs_0);

	regVal = REG_READ(ah, 0x7834);
	regVal |= 0x1;
	REG_WRITE(ah, 0x7834, regVal);
	regVal = REG_READ(ah, 0x9808);
	regVal &= (~(0x1 << 27));
	REG_WRITE(ah, 0x9808, regVal);

	क्रम (i = 0; i < ARRAY_SIZE(regList); i++)
		REG_WRITE(ah, regList[i][0], regList[i][1]);

	REG_RMW_FIELD(ah, AR9285_AN_RF2G6, AR9285_AN_RF2G6_CCOMP, ccomp_org);
पूर्ण

अटल व्योम ar9002_hw_pa_cal(काष्ठा ath_hw *ah, bool is_reset)
अणु
	अगर (AR_SREV_9271(ah)) अणु
		अगर (is_reset || !ah->pacal_info.skipcount)
			ar9271_hw_pa_cal(ah, is_reset);
		अन्यथा
			ah->pacal_info.skipcount--;
	पूर्ण अन्यथा अगर (AR_SREV_9285_12_OR_LATER(ah)) अणु
		अगर (is_reset || !ah->pacal_info.skipcount)
			ar9285_hw_pa_cal(ah, is_reset);
		अन्यथा
			ah->pacal_info.skipcount--;
	पूर्ण
पूर्ण

अटल व्योम ar9002_hw_olc_temp_compensation(काष्ठा ath_hw *ah)
अणु
	अगर (OLC_FOR_AR9287_10_LATER)
		ar9287_hw_olc_temp_compensation(ah);
	अन्यथा अगर (OLC_FOR_AR9280_20_LATER)
		ar9280_hw_olc_temp_compensation(ah);
पूर्ण

अटल पूर्णांक ar9002_hw_calibrate(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			       u8 rxchainmask, bool दीर्घcal)
अणु
	काष्ठा ath9k_cal_list *currCal = ah->cal_list_curr;
	bool nfcal, nfcal_pending = false, percal_pending;
	पूर्णांक ret;

	nfcal = !!(REG_READ(ah, AR_PHY_AGC_CONTROL) & AR_PHY_AGC_CONTROL_NF);
	अगर (ah->caldata) अणु
		nfcal_pending = test_bit(NFCAL_PENDING, &ah->caldata->cal_flags);
		अगर (दीर्घcal)		/* Remember to not miss */
			set_bit(LONGCAL_PENDING, &ah->caldata->cal_flags);
		अन्यथा अगर (test_bit(LONGCAL_PENDING, &ah->caldata->cal_flags))
			दीर्घcal = true;	/* Respin a previous one */
	पूर्ण

	percal_pending = (currCal &&
			  (currCal->calState == CAL_RUNNING ||
			   currCal->calState == CAL_WAITING));

	अगर (percal_pending && !nfcal) अणु
		अगर (!ar9002_hw_per_calibration(ah, chan, rxchainmask, currCal))
			वापस 0;

		/* Looking क्रम next रुकोing calibration अगर any */
		क्रम (currCal = currCal->calNext; currCal != ah->cal_list_curr;
		     currCal = currCal->calNext) अणु
			अगर (currCal->calState == CAL_WAITING)
				अवरोध;
		पूर्ण
		अगर (currCal->calState == CAL_WAITING) अणु
			percal_pending = true;
			ah->cal_list_curr = currCal;
		पूर्ण अन्यथा अणु
			percal_pending = false;
			ah->cal_list_curr = ah->cal_list;
		पूर्ण
	पूर्ण

	/* Do not start a next calibration अगर the दीर्घcal is in action */
	अगर (percal_pending && !nfcal && !दीर्घcal) अणु
		ath9k_hw_reset_calibration(ah, currCal);

		वापस 0;
	पूर्ण

	/* Do NF cal only at दीर्घer पूर्णांकervals */
	अगर (दीर्घcal || nfcal_pending) अणु
		/*
		 * Get the value from the previous NF cal and update
		 * history buffer.
		 */
		अगर (ath9k_hw_getnf(ah, chan)) अणु
			/*
			 * Load the NF from history buffer of the current
			 * channel.
			 * NF is slow समय-variant, so it is OK to use a
			 * historical value.
			 */
			ret = ath9k_hw_loadnf(ah, ah->curchan);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		अगर (दीर्घcal) अणु
			अगर (ah->caldata)
				clear_bit(LONGCAL_PENDING,
					  &ah->caldata->cal_flags);
			ath9k_hw_start_nfcal(ah, false);
			/* Do periodic PAOffset Cal */
			ar9002_hw_pa_cal(ah, false);
			ar9002_hw_olc_temp_compensation(ah);
		पूर्ण
	पूर्ण

	वापस !percal_pending;
पूर्ण

/* Carrier leakage Calibration fix */
अटल bool ar9285_hw_cl_cal(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
	अगर (IS_CHAN_HT20(chan)) अणु
		REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_PARALLEL_CAL_ENABLE);
		REG_SET_BIT(ah, AR_PHY_TURBO, AR_PHY_FC_DYN2040_EN);
		REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
			    AR_PHY_AGC_CONTROL_FLTR_CAL);
		REG_CLR_BIT(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_PD_CAL_ENABLE);
		REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_CAL);
		अगर (!ath9k_hw_रुको(ah, AR_PHY_AGC_CONTROL,
				  AR_PHY_AGC_CONTROL_CAL, 0, AH_WAIT_TIMEOUT)) अणु
			ath_dbg(common, CALIBRATE,
				"offset calibration failed to complete in %d ms; noisy environment?\n",
				AH_WAIT_TIMEOUT / 1000);
			वापस false;
		पूर्ण
		REG_CLR_BIT(ah, AR_PHY_TURBO, AR_PHY_FC_DYN2040_EN);
		REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_PARALLEL_CAL_ENABLE);
		REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
	पूर्ण
	REG_CLR_BIT(ah, AR_PHY_ADC_CTL, AR_PHY_ADC_CTL_OFF_PWDADC);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_FLTR_CAL);
	REG_SET_BIT(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_PD_CAL_ENABLE);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_CAL);
	अगर (!ath9k_hw_रुको(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_CAL,
			  0, AH_WAIT_TIMEOUT)) अणु
		ath_dbg(common, CALIBRATE,
			"offset calibration failed to complete in %d ms; noisy environment?\n",
			AH_WAIT_TIMEOUT / 1000);
		वापस false;
	पूर्ण

	REG_SET_BIT(ah, AR_PHY_ADC_CTL, AR_PHY_ADC_CTL_OFF_PWDADC);
	REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_FLTR_CAL);

	वापस true;
पूर्ण

अटल bool ar9285_hw_clc(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक i;
	u_पूर्णांक32_t txgain_max;
	u_पूर्णांक32_t clc_gain, gain_mask = 0, clc_num = 0;
	u_पूर्णांक32_t reg_clc_I0, reg_clc_Q0;
	u_पूर्णांक32_t i0_num = 0;
	u_पूर्णांक32_t q0_num = 0;
	u_पूर्णांक32_t total_num = 0;
	u_पूर्णांक32_t reg_rf2g5_org;
	bool retv = true;

	अगर (!(ar9285_hw_cl_cal(ah, chan)))
		वापस false;

	txgain_max = MS(REG_READ(ah, AR_PHY_TX_PWRCTRL7),
			AR_PHY_TX_PWRCTRL_TX_GAIN_TAB_MAX);

	क्रम (i = 0; i < (txgain_max+1); i++) अणु
		clc_gain = (REG_READ(ah, (AR_PHY_TX_GAIN_TBL1+(i<<2))) &
			   AR_PHY_TX_GAIN_CLC) >> AR_PHY_TX_GAIN_CLC_S;
		अगर (!(gain_mask & (1 << clc_gain))) अणु
			gain_mask |= (1 << clc_gain);
			clc_num++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < clc_num; i++) अणु
		reg_clc_I0 = (REG_READ(ah, (AR_PHY_CLC_TBL1 + (i << 2)))
			      & AR_PHY_CLC_I0) >> AR_PHY_CLC_I0_S;
		reg_clc_Q0 = (REG_READ(ah, (AR_PHY_CLC_TBL1 + (i << 2)))
			      & AR_PHY_CLC_Q0) >> AR_PHY_CLC_Q0_S;
		अगर (reg_clc_I0 == 0)
			i0_num++;

		अगर (reg_clc_Q0 == 0)
			q0_num++;
	पूर्ण
	total_num = i0_num + q0_num;
	अगर (total_num > AR9285_CLCAL_REDO_THRESH) अणु
		reg_rf2g5_org = REG_READ(ah, AR9285_RF2G5);
		अगर (AR_SREV_9285E_20(ah)) अणु
			REG_WRITE(ah, AR9285_RF2G5,
				  (reg_rf2g5_org & AR9285_RF2G5_IC50TX) |
				  AR9285_RF2G5_IC50TX_XE_SET);
		पूर्ण अन्यथा अणु
			REG_WRITE(ah, AR9285_RF2G5,
				  (reg_rf2g5_org & AR9285_RF2G5_IC50TX) |
				  AR9285_RF2G5_IC50TX_SET);
		पूर्ण
		retv = ar9285_hw_cl_cal(ah, chan);
		REG_WRITE(ah, AR9285_RF2G5, reg_rf2g5_org);
	पूर्ण
	वापस retv;
पूर्ण

अटल bool ar9002_hw_init_cal(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (AR_SREV_9271(ah)) अणु
		अगर (!ar9285_hw_cl_cal(ah, chan))
			वापस false;
	पूर्ण अन्यथा अगर (AR_SREV_9285(ah) && AR_SREV_9285_12_OR_LATER(ah)) अणु
		अगर (!ar9285_hw_clc(ah, chan))
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
			अगर (!AR_SREV_9287_11_OR_LATER(ah))
				REG_CLR_BIT(ah, AR_PHY_ADC_CTL,
					    AR_PHY_ADC_CTL_OFF_PWDADC);
			REG_SET_BIT(ah, AR_PHY_AGC_CONTROL,
				    AR_PHY_AGC_CONTROL_FLTR_CAL);
		पूर्ण

		/* Calibrate the AGC */
		REG_WRITE(ah, AR_PHY_AGC_CONTROL,
			  REG_READ(ah, AR_PHY_AGC_CONTROL) |
			  AR_PHY_AGC_CONTROL_CAL);

		/* Poll क्रम offset calibration complete */
		अगर (!ath9k_hw_रुको(ah, AR_PHY_AGC_CONTROL,
				   AR_PHY_AGC_CONTROL_CAL,
				   0, AH_WAIT_TIMEOUT)) अणु
			ath_dbg(common, CALIBRATE,
				"offset calibration failed to complete in %d ms; noisy environment?\n",
				AH_WAIT_TIMEOUT / 1000);
			वापस false;
		पूर्ण

		अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
			अगर (!AR_SREV_9287_11_OR_LATER(ah))
				REG_SET_BIT(ah, AR_PHY_ADC_CTL,
					    AR_PHY_ADC_CTL_OFF_PWDADC);
			REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
				    AR_PHY_AGC_CONTROL_FLTR_CAL);
		पूर्ण
	पूर्ण

	/* Do PA Calibration */
	ar9002_hw_pa_cal(ah, true);
	ath9k_hw_loadnf(ah, chan);
	ath9k_hw_start_nfcal(ah, true);

	ah->cal_list = ah->cal_list_last = ah->cal_list_curr = शून्य;

	/* Enable IQ, ADC Gain and ADC DC offset CALs */
	अगर (AR_SREV_9100(ah) || AR_SREV_9160_10_OR_LATER(ah)) अणु
		ah->supp_cals = IQ_MISMATCH_CAL;

		अगर (AR_SREV_9160_10_OR_LATER(ah))
			ah->supp_cals |= ADC_GAIN_CAL | ADC_DC_CAL;

		अगर (AR_SREV_9287(ah))
			ah->supp_cals &= ~ADC_GAIN_CAL;

		अगर (ar9002_hw_is_cal_supported(ah, chan, ADC_GAIN_CAL)) अणु
			INIT_CAL(&ah->adcgain_caldata);
			INSERT_CAL(ah, &ah->adcgain_caldata);
			ath_dbg(common, CALIBRATE,
					"enabling ADC Gain Calibration\n");
		पूर्ण

		अगर (ar9002_hw_is_cal_supported(ah, chan, ADC_DC_CAL)) अणु
			INIT_CAL(&ah->adcdc_caldata);
			INSERT_CAL(ah, &ah->adcdc_caldata);
			ath_dbg(common, CALIBRATE,
					"enabling ADC DC Calibration\n");
		पूर्ण

		अगर (ar9002_hw_is_cal_supported(ah, chan, IQ_MISMATCH_CAL)) अणु
			INIT_CAL(&ah->iq_caldata);
			INSERT_CAL(ah, &ah->iq_caldata);
			ath_dbg(common, CALIBRATE, "enabling IQ Calibration\n");
		पूर्ण

		ah->cal_list_curr = ah->cal_list;

		अगर (ah->cal_list_curr)
			ath9k_hw_reset_calibration(ah, ah->cal_list_curr);
	पूर्ण

	अगर (ah->caldata)
		ah->caldata->CalValid = 0;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा ath9k_percal_data iq_cal_multi_sample = अणु
	IQ_MISMATCH_CAL,
	MAX_CAL_SAMPLES,
	PER_MIN_LOG_COUNT,
	ar9002_hw_iqcal_collect,
	ar9002_hw_iqcalibrate
पूर्ण;
अटल स्थिर काष्ठा ath9k_percal_data iq_cal_single_sample = अणु
	IQ_MISMATCH_CAL,
	MIN_CAL_SAMPLES,
	PER_MAX_LOG_COUNT,
	ar9002_hw_iqcal_collect,
	ar9002_hw_iqcalibrate
पूर्ण;
अटल स्थिर काष्ठा ath9k_percal_data adc_gain_cal_multi_sample = अणु
	ADC_GAIN_CAL,
	MAX_CAL_SAMPLES,
	PER_MIN_LOG_COUNT,
	ar9002_hw_adc_gaincal_collect,
	ar9002_hw_adc_gaincal_calibrate
पूर्ण;
अटल स्थिर काष्ठा ath9k_percal_data adc_gain_cal_single_sample = अणु
	ADC_GAIN_CAL,
	MIN_CAL_SAMPLES,
	PER_MAX_LOG_COUNT,
	ar9002_hw_adc_gaincal_collect,
	ar9002_hw_adc_gaincal_calibrate
पूर्ण;
अटल स्थिर काष्ठा ath9k_percal_data adc_dc_cal_multi_sample = अणु
	ADC_DC_CAL,
	MAX_CAL_SAMPLES,
	PER_MIN_LOG_COUNT,
	ar9002_hw_adc_dccal_collect,
	ar9002_hw_adc_dccal_calibrate
पूर्ण;
अटल स्थिर काष्ठा ath9k_percal_data adc_dc_cal_single_sample = अणु
	ADC_DC_CAL,
	MIN_CAL_SAMPLES,
	PER_MAX_LOG_COUNT,
	ar9002_hw_adc_dccal_collect,
	ar9002_hw_adc_dccal_calibrate
पूर्ण;

अटल व्योम ar9002_hw_init_cal_settings(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9100(ah)) अणु
		ah->iq_caldata.calData = &iq_cal_multi_sample;
		ah->supp_cals = IQ_MISMATCH_CAL;
		वापस;
	पूर्ण

	अगर (AR_SREV_9160_10_OR_LATER(ah)) अणु
		अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
			ah->iq_caldata.calData = &iq_cal_single_sample;
			ah->adcgain_caldata.calData =
				&adc_gain_cal_single_sample;
			ah->adcdc_caldata.calData =
				&adc_dc_cal_single_sample;
		पूर्ण अन्यथा अणु
			ah->iq_caldata.calData = &iq_cal_multi_sample;
			ah->adcgain_caldata.calData =
				&adc_gain_cal_multi_sample;
			ah->adcdc_caldata.calData =
				&adc_dc_cal_multi_sample;
		पूर्ण
		ah->supp_cals = ADC_GAIN_CAL | ADC_DC_CAL | IQ_MISMATCH_CAL;

		अगर (AR_SREV_9287(ah))
			ah->supp_cals &= ~ADC_GAIN_CAL;
	पूर्ण
पूर्ण

व्योम ar9002_hw_attach_calib_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_निजी_ops *priv_ops = ath9k_hw_निजी_ops(ah);
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(ah);

	priv_ops->init_cal_settings = ar9002_hw_init_cal_settings;
	priv_ops->init_cal = ar9002_hw_init_cal;
	priv_ops->setup_calibration = ar9002_hw_setup_calibration;

	ops->calibrate = ar9002_hw_calibrate;
पूर्ण
