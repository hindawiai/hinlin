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

#समावेश <linux/export.h>
#समावेश "hw.h"
#समावेश "ar9003_phy.h"

व्योम ar9003_paprd_enable(काष्ठा ath_hw *ah, bool val)
अणु
	काष्ठा ath9k_channel *chan = ah->curchan;
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	/*
	 * 3 bits क्रम modalHeader5G.papdRateMaskHt20
	 * is used क्रम sub-band disabling of PAPRD.
	 * 5G band is भागided पूर्णांकo 3 sub-bands -- upper,
	 * middle, lower.
	 * अगर bit 30 of modalHeader5G.papdRateMaskHt20 is set
	 * -- disable PAPRD क्रम upper band 5GHz
	 * अगर bit 29 of modalHeader5G.papdRateMaskHt20 is set
	 * -- disable PAPRD क्रम middle band 5GHz
	 * अगर bit 28 of modalHeader5G.papdRateMaskHt20 is set
	 * -- disable PAPRD क्रम lower band 5GHz
	 */

	अगर (IS_CHAN_5GHZ(chan)) अणु
		अगर (chan->channel >= UPPER_5G_SUB_BAND_START) अणु
			अगर (le32_to_cpu(eep->modalHeader5G.papdRateMaskHt20)
								  & BIT(30))
				val = false;
		पूर्ण अन्यथा अगर (chan->channel >= MID_5G_SUB_BAND_START) अणु
			अगर (le32_to_cpu(eep->modalHeader5G.papdRateMaskHt20)
								  & BIT(29))
				val = false;
		पूर्ण अन्यथा अणु
			अगर (le32_to_cpu(eep->modalHeader5G.papdRateMaskHt20)
								  & BIT(28))
				val = false;
		पूर्ण
	पूर्ण

	अगर (val) अणु
		ah->paprd_table_ग_लिखो_करोne = true;
		ath9k_hw_apply_txघातer(ah, chan, false);
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_CTRL0_B0,
		      AR_PHY_PAPRD_CTRL0_PAPRD_ENABLE, !!val);
	अगर (ah->caps.tx_chainmask & BIT(1))
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_CTRL0_B1,
			      AR_PHY_PAPRD_CTRL0_PAPRD_ENABLE, !!val);
	अगर (ah->caps.tx_chainmask & BIT(2))
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_CTRL0_B2,
			      AR_PHY_PAPRD_CTRL0_PAPRD_ENABLE, !!val);
पूर्ण
EXPORT_SYMBOL(ar9003_paprd_enable);

अटल पूर्णांक ar9003_get_training_घातer_2g(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_channel *chan = ah->curchan;
	अचिन्हित पूर्णांक घातer, scale, delta;

	scale = ar9003_get_paprd_scale_factor(ah, chan);

	अगर (AR_SREV_9330(ah) || AR_SREV_9340(ah) ||
	    AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		घातer = ah->paprd_target_घातer + 2;
	पूर्ण अन्यथा अगर (AR_SREV_9485(ah)) अणु
		घातer = 25;
	पूर्ण अन्यथा अणु
		घातer = REG_READ_FIELD(ah, AR_PHY_POWERTX_RATE5,
				       AR_PHY_POWERTX_RATE5_POWERTXHT20_0);

		delta = असल((पूर्णांक) ah->paprd_target_घातer - (पूर्णांक) घातer);
		अगर (delta > scale)
			वापस -1;

		अगर (delta < 4)
			घातer -= 4 - delta;
	पूर्ण

	वापस घातer;
पूर्ण

अटल पूर्णांक ar9003_get_training_घातer_5g(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_channel *chan = ah->curchan;
	अचिन्हित पूर्णांक घातer, scale, delta;

	scale = ar9003_get_paprd_scale_factor(ah, chan);

	अगर (IS_CHAN_HT40(chan))
		घातer = REG_READ_FIELD(ah, AR_PHY_POWERTX_RATE8,
			AR_PHY_POWERTX_RATE8_POWERTXHT40_5);
	अन्यथा
		घातer = REG_READ_FIELD(ah, AR_PHY_POWERTX_RATE6,
			AR_PHY_POWERTX_RATE6_POWERTXHT20_5);

	घातer += scale;
	delta = असल((पूर्णांक) ah->paprd_target_घातer - (पूर्णांक) घातer);
	अगर (delta > scale)
		वापस -1;

	चयन (get_streams(ah->txchainmask)) अणु
	हाल 1:
		delta = 6;
		अवरोध;
	हाल 2:
		delta = 4;
		अवरोध;
	हाल 3:
		delta = 2;
		अवरोध;
	शेष:
		delta = 0;
		ath_dbg(common, CALIBRATE, "Invalid tx-chainmask: %u\n",
			ah->txchainmask);
	पूर्ण

	घातer += delta;
	वापस घातer;
पूर्ण

अटल पूर्णांक ar9003_paprd_setup_single_table(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	अटल स्थिर u32 ctrl0[3] = अणु
		AR_PHY_PAPRD_CTRL0_B0,
		AR_PHY_PAPRD_CTRL0_B1,
		AR_PHY_PAPRD_CTRL0_B2
	पूर्ण;
	अटल स्थिर u32 ctrl1[3] = अणु
		AR_PHY_PAPRD_CTRL1_B0,
		AR_PHY_PAPRD_CTRL1_B1,
		AR_PHY_PAPRD_CTRL1_B2
	पूर्ण;
	पूर्णांक training_घातer;
	पूर्णांक i, val;
	u32 am2pm_mask = ah->paprd_ratemask;

	अगर (IS_CHAN_2GHZ(ah->curchan))
		training_घातer = ar9003_get_training_घातer_2g(ah);
	अन्यथा
		training_घातer = ar9003_get_training_घातer_5g(ah);

	ath_dbg(common, CALIBRATE, "Training power: %d, Target power: %d\n",
		training_घातer, ah->paprd_target_घातer);

	अगर (training_घातer < 0) अणु
		ath_dbg(common, CALIBRATE,
			"PAPRD target power delta out of range\n");
		वापस -दुस्फल;
	पूर्ण
	ah->paprd_training_घातer = training_घातer;

	अगर (AR_SREV_9330(ah))
		am2pm_mask = 0;

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_AM2AM, AR_PHY_PAPRD_AM2AM_MASK,
		      ah->paprd_ratemask);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_AM2PM, AR_PHY_PAPRD_AM2PM_MASK,
		      am2pm_mask);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_HT40, AR_PHY_PAPRD_HT40_MASK,
		      ah->paprd_ratemask_ht40);

	ath_dbg(common, CALIBRATE, "PAPRD HT20 mask: 0x%x, HT40 mask: 0x%x\n",
		ah->paprd_ratemask, ah->paprd_ratemask_ht40);

	क्रम (i = 0; i < ah->caps.max_txchains; i++) अणु
		REG_RMW_FIELD(ah, ctrl0[i],
			      AR_PHY_PAPRD_CTRL0_USE_SINGLE_TABLE_MASK, 1);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_AM2PM_ENABLE, 1);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_AM2AM_ENABLE, 1);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_SCALING_ENA, 0);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_PA_GAIN_SCALE_FACT_MASK, 181);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_PAPRD_MAG_SCALE_FACT, 361);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_SCALING_ENA, 0);
		REG_RMW_FIELD(ah, ctrl0[i],
			      AR_PHY_PAPRD_CTRL0_PAPRD_MAG_THRSH, 3);
	पूर्ण

	ar9003_paprd_enable(ah, false);

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_LB_SKIP, 0x30);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_LB_ENABLE, 1);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_TX_GAIN_FORCE, 1);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_RX_BB_GAIN_FORCE, 0);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_IQCORR_ENABLE, 0);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_AGC2_SETTLING, 28);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_CF_PAPRD_TRAIN_ENABLE, 1);

	अगर (AR_SREV_9485(ah)) अणु
		val = 148;
	पूर्ण अन्यथा अणु
		अगर (IS_CHAN_2GHZ(ah->curchan)) अणु
			अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah))
				val = 145;
			अन्यथा
				val = 147;
		पूर्ण अन्यथा अणु
			val = 137;
		पूर्ण
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL2,
		      AR_PHY_PAPRD_TRAINER_CNTL2_CF_PAPRD_INIT_RX_BB_GAIN, val);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_FINE_CORR_LEN, 4);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_COARSE_CORR_LEN, 4);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_NUM_CORR_STAGES, 7);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_MIN_LOOPBACK_DEL, 1);

	अगर (AR_SREV_9485(ah) ||
	    AR_SREV_9462(ah) ||
	    AR_SREV_9565(ah) ||
	    AR_SREV_9550(ah) ||
	    AR_SREV_9330(ah) ||
	    AR_SREV_9340(ah))
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
			      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, -3);
	अन्यथा
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
			      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, -6);

	val = -10;

	अगर (IS_CHAN_2GHZ(ah->curchan) && !AR_SREV_9462(ah) && !AR_SREV_9565(ah))
		val = -15;

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_ADC_DESIRED_SIZE,
		      val);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_BBTXMIX_DISABLE, 1);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL4,
		      AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_SAFETY_DELTA, 0);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL4,
		      AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_MIN_CORR, 400);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL4,
		      AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_NUM_TRAIN_SAMPLES,
		      100);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_0_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 261376);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_1_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 248079);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_2_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 233759);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_3_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 220464);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_4_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 208194);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_5_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 196949);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_6_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 185706);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_7_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 175487);
	वापस 0;
पूर्ण

अटल व्योम ar9003_paprd_get_gain_table(काष्ठा ath_hw *ah)
अणु
	u32 *entry = ah->paprd_gain_table_entries;
	u8 *index = ah->paprd_gain_table_index;
	u32 reg = AR_PHY_TXGAIN_TABLE;
	पूर्णांक i;

	क्रम (i = 0; i < PAPRD_GAIN_TABLE_ENTRIES; i++) अणु
		entry[i] = REG_READ(ah, reg);
		index[i] = (entry[i] >> 24) & 0xff;
		reg += 4;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ar9003_get_desired_gain(काष्ठा ath_hw *ah, पूर्णांक chain,
					    पूर्णांक target_घातer)
अणु
	पूर्णांक olpc_gain_delta = 0, cl_gain_mod;
	पूर्णांक alpha_therm, alpha_volt;
	पूर्णांक therm_cal_value, volt_cal_value;
	पूर्णांक therm_value, volt_value;
	पूर्णांक thermal_gain_corr, voltage_gain_corr;
	पूर्णांक desired_scale, desired_gain = 0;
	u32 reg_olpc  = 0, reg_cl_gain  = 0;

	REG_CLR_BIT(ah, AR_PHY_PAPRD_TRAINER_STAT1,
		    AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE);
	desired_scale = REG_READ_FIELD(ah, AR_PHY_TPC_12,
				       AR_PHY_TPC_12_DESIRED_SCALE_HT40_5);
	alpha_therm = REG_READ_FIELD(ah, AR_PHY_TPC_19,
				     AR_PHY_TPC_19_ALPHA_THERM);
	alpha_volt = REG_READ_FIELD(ah, AR_PHY_TPC_19,
				    AR_PHY_TPC_19_ALPHA_VOLT);
	therm_cal_value = REG_READ_FIELD(ah, AR_PHY_TPC_18,
					 AR_PHY_TPC_18_THERM_CAL_VALUE);
	volt_cal_value = REG_READ_FIELD(ah, AR_PHY_TPC_18,
					AR_PHY_TPC_18_VOLT_CAL_VALUE);
	therm_value = REG_READ_FIELD(ah, AR_PHY_BB_THERM_ADC_4,
				     AR_PHY_BB_THERM_ADC_4_LATEST_THERM_VALUE);
	volt_value = REG_READ_FIELD(ah, AR_PHY_BB_THERM_ADC_4,
				    AR_PHY_BB_THERM_ADC_4_LATEST_VOLT_VALUE);

	चयन (chain) अणु
	हाल 0:
		reg_olpc = AR_PHY_TPC_11_B0;
		reg_cl_gain = AR_PHY_CL_TAB_0;
		अवरोध;
	हाल 1:
		reg_olpc = AR_PHY_TPC_11_B1;
		reg_cl_gain = AR_PHY_CL_TAB_1;
		अवरोध;
	हाल 2:
		reg_olpc = AR_PHY_TPC_11_B2;
		reg_cl_gain = AR_PHY_CL_TAB_2;
		अवरोध;
	शेष:
		ath_dbg(ath9k_hw_common(ah), CALIBRATE,
			"Invalid chainmask: %d\n", chain);
		अवरोध;
	पूर्ण

	olpc_gain_delta = REG_READ_FIELD(ah, reg_olpc,
					 AR_PHY_TPC_11_OLPC_GAIN_DELTA);
	cl_gain_mod = REG_READ_FIELD(ah, reg_cl_gain,
					 AR_PHY_CL_TAB_CL_GAIN_MOD);

	अगर (olpc_gain_delta >= 128)
		olpc_gain_delta = olpc_gain_delta - 256;

	thermal_gain_corr = (alpha_therm * (therm_value - therm_cal_value) +
			     (256 / 2)) / 256;
	voltage_gain_corr = (alpha_volt * (volt_value - volt_cal_value) +
			     (128 / 2)) / 128;
	desired_gain = target_घातer - olpc_gain_delta - thermal_gain_corr -
	    voltage_gain_corr + desired_scale + cl_gain_mod;

	वापस desired_gain;
पूर्ण

अटल व्योम ar9003_tx_क्रमce_gain(काष्ठा ath_hw *ah, अचिन्हित पूर्णांक gain_index)
अणु
	पूर्णांक selected_gain_entry, txbb1dbgain, txbb6dbgain, txmxrgain;
	पूर्णांक padrvgnA, padrvgnB, padrvgnC, padrvgnD;
	u32 *gain_table_entries = ah->paprd_gain_table_entries;

	selected_gain_entry = gain_table_entries[gain_index];
	txbb1dbgain = selected_gain_entry & 0x7;
	txbb6dbgain = (selected_gain_entry >> 3) & 0x3;
	txmxrgain = (selected_gain_entry >> 5) & 0xf;
	padrvgnA = (selected_gain_entry >> 9) & 0xf;
	padrvgnB = (selected_gain_entry >> 13) & 0xf;
	padrvgnC = (selected_gain_entry >> 17) & 0xf;
	padrvgnD = (selected_gain_entry >> 21) & 0x3;

	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_TXBB1DBGAIN, txbb1dbgain);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_TXBB6DBGAIN, txbb6dbgain);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_TXMXRGAIN, txmxrgain);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNA, padrvgnA);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNB, padrvgnB);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGNC, padrvgnC);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_PADRVGND, padrvgnD);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCED_ENABLE_PAL, 0);
	REG_RMW_FIELD(ah, AR_PHY_TX_FORCED_GAIN,
		      AR_PHY_TX_FORCED_GAIN_FORCE_TX_GAIN, 0);
	REG_RMW_FIELD(ah, AR_PHY_TPC_1, AR_PHY_TPC_1_FORCED_DAC_GAIN, 0);
	REG_RMW_FIELD(ah, AR_PHY_TPC_1, AR_PHY_TPC_1_FORCE_DAC_GAIN, 0);
पूर्ण

अटल अंतरभूत पूर्णांक find_expn(पूर्णांक num)
अणु
	वापस fls(num) - 1;
पूर्ण

अटल अंतरभूत पूर्णांक find_proper_scale(पूर्णांक expn, पूर्णांक N)
अणु
	वापस (expn > N) ? expn - 10 : 0;
पूर्ण

#घोषणा NUM_BIN 23

अटल bool create_pa_curve(u32 *data_L, u32 *data_U, u32 *pa_table, u16 *gain)
अणु
	अचिन्हित पूर्णांक thresh_accum_cnt;
	पूर्णांक x_est[NUM_BIN + 1], Y[NUM_BIN + 1], theta[NUM_BIN + 1];
	पूर्णांक PA_in[NUM_BIN + 1];
	पूर्णांक B1_पंचांगp[NUM_BIN + 1], B2_पंचांगp[NUM_BIN + 1];
	अचिन्हित पूर्णांक B1_असल_max, B2_असल_max;
	पूर्णांक max_index, scale_factor;
	पूर्णांक y_est[NUM_BIN + 1];
	पूर्णांक x_est_fxp1_nonlin, x_tilde[NUM_BIN + 1];
	अचिन्हित पूर्णांक x_tilde_असल;
	पूर्णांक G_fxp, Y_पूर्णांकercept, order_x_by_y, M, I, L, sum_y_sqr, sum_y_quad;
	पूर्णांक Q_x, Q_B1, Q_B2, beta_raw, alpha_raw, scale_B;
	पूर्णांक Q_scale_B, Q_beta, Q_alpha, alpha, beta, order_1, order_2;
	पूर्णांक order1_5x, order2_3x, order1_5x_rem, order2_3x_rem;
	पूर्णांक y5, y3, पंचांगp;
	पूर्णांक theta_low_bin = 0;
	पूर्णांक i;

	/* disregard any bin that contains <= 16 samples */
	thresh_accum_cnt = 16;
	scale_factor = 5;
	max_index = 0;
	स_रखो(theta, 0, माप(theta));
	स_रखो(x_est, 0, माप(x_est));
	स_रखो(Y, 0, माप(Y));
	स_रखो(y_est, 0, माप(y_est));
	स_रखो(x_tilde, 0, माप(x_tilde));

	क्रम (i = 0; i < NUM_BIN; i++) अणु
		s32 accum_cnt, accum_tx, accum_rx, accum_ang;

		/* number of samples */
		accum_cnt = data_L[i] & 0xffff;

		अगर (accum_cnt <= thresh_accum_cnt)
			जारी;

		max_index++;

		/* sum(tx amplitude) */
		accum_tx = ((data_L[i] >> 16) & 0xffff) |
		    ((data_U[i] & 0x7ff) << 16);

		/* sum(rx amplitude distance to lower bin edge) */
		accum_rx = ((data_U[i] >> 11) & 0x1f) |
		    ((data_L[i + 23] & 0xffff) << 5);

		/* sum(angles) */
		accum_ang = ((data_L[i + 23] >> 16) & 0xffff) |
		    ((data_U[i + 23] & 0x7ff) << 16);

		accum_tx <<= scale_factor;
		accum_rx <<= scale_factor;
		x_est[max_index] =
			(((accum_tx + accum_cnt) / accum_cnt) + 32) >>
			scale_factor;

		Y[max_index] =
			((((accum_rx + accum_cnt) / accum_cnt) + 32) >>
			    scale_factor) +
			(1 << scale_factor) * i + 16;

		अगर (accum_ang >= (1 << 26))
			accum_ang -= 1 << 27;

		theta[max_index] =
			((accum_ang * (1 << scale_factor)) + accum_cnt) /
			accum_cnt;
	पूर्ण

	/*
	 * Find average theta of first 5 bin and all of those to same value.
	 * Curve is linear at that range.
	 */
	क्रम (i = 1; i < 6; i++)
		theta_low_bin += theta[i];

	theta_low_bin = theta_low_bin / 5;
	क्रम (i = 1; i < 6; i++)
		theta[i] = theta_low_bin;

	/* Set values at origin */
	theta[0] = theta_low_bin;
	क्रम (i = 0; i <= max_index; i++)
		theta[i] -= theta_low_bin;

	x_est[0] = 0;
	Y[0] = 0;
	scale_factor = 8;

	/* low संकेत gain */
	अगर (x_est[6] == x_est[3])
		वापस false;

	G_fxp =
	    (((Y[6] - Y[3]) * 1 << scale_factor) +
	     (x_est[6] - x_est[3])) / (x_est[6] - x_est[3]);

	/* prevent भागision by zero */
	अगर (G_fxp == 0)
		वापस false;

	Y_पूर्णांकercept =
	    (G_fxp * (x_est[0] - x_est[3]) +
	     (1 << scale_factor)) / (1 << scale_factor) + Y[3];

	क्रम (i = 0; i <= max_index; i++)
		y_est[i] = Y[i] - Y_पूर्णांकercept;

	क्रम (i = 0; i <= 3; i++) अणु
		y_est[i] = i * 32;
		x_est[i] = ((y_est[i] * 1 << scale_factor) + G_fxp) / G_fxp;
	पूर्ण

	अगर (y_est[max_index] == 0)
		वापस false;

	x_est_fxp1_nonlin =
	    x_est[max_index] - ((1 << scale_factor) * y_est[max_index] +
				G_fxp) / G_fxp;

	order_x_by_y =
	    (x_est_fxp1_nonlin + y_est[max_index]) / y_est[max_index];

	अगर (order_x_by_y == 0)
		M = 10;
	अन्यथा अगर (order_x_by_y == 1)
		M = 9;
	अन्यथा
		M = 8;

	I = (max_index > 15) ? 7 : max_index >> 1;
	L = max_index - I;
	scale_factor = 8;
	sum_y_sqr = 0;
	sum_y_quad = 0;
	x_tilde_असल = 0;

	क्रम (i = 0; i <= L; i++) अणु
		अचिन्हित पूर्णांक y_sqr;
		अचिन्हित पूर्णांक y_quad;
		अचिन्हित पूर्णांक पंचांगp_असल;

		/* prevent भागision by zero */
		अगर (y_est[i + I] == 0)
			वापस false;

		x_est_fxp1_nonlin =
		    x_est[i + I] - ((1 << scale_factor) * y_est[i + I] +
				    G_fxp) / G_fxp;

		x_tilde[i] =
		    (x_est_fxp1_nonlin * (1 << M) + y_est[i + I]) / y_est[i +
									  I];
		x_tilde[i] =
		    (x_tilde[i] * (1 << M) + y_est[i + I]) / y_est[i + I];
		x_tilde[i] =
		    (x_tilde[i] * (1 << M) + y_est[i + I]) / y_est[i + I];
		y_sqr =
		    (y_est[i + I] * y_est[i + I] +
		     (scale_factor * scale_factor)) / (scale_factor *
						       scale_factor);
		पंचांगp_असल = असल(x_tilde[i]);
		अगर (पंचांगp_असल > x_tilde_असल)
			x_tilde_असल = पंचांगp_असल;

		y_quad = y_sqr * y_sqr;
		sum_y_sqr = sum_y_sqr + y_sqr;
		sum_y_quad = sum_y_quad + y_quad;
		B1_पंचांगp[i] = y_sqr * (L + 1);
		B2_पंचांगp[i] = y_sqr;
	पूर्ण

	B1_असल_max = 0;
	B2_असल_max = 0;
	क्रम (i = 0; i <= L; i++) अणु
		पूर्णांक असल_val;

		B1_पंचांगp[i] -= sum_y_sqr;
		B2_पंचांगp[i] = sum_y_quad - sum_y_sqr * B2_पंचांगp[i];

		असल_val = असल(B1_पंचांगp[i]);
		अगर (असल_val > B1_असल_max)
			B1_असल_max = असल_val;

		असल_val = असल(B2_पंचांगp[i]);
		अगर (असल_val > B2_असल_max)
			B2_असल_max = असल_val;
	पूर्ण

	Q_x = find_proper_scale(find_expn(x_tilde_असल), 10);
	Q_B1 = find_proper_scale(find_expn(B1_असल_max), 10);
	Q_B2 = find_proper_scale(find_expn(B2_असल_max), 10);

	beta_raw = 0;
	alpha_raw = 0;
	क्रम (i = 0; i <= L; i++) अणु
		x_tilde[i] = x_tilde[i] / (1 << Q_x);
		B1_पंचांगp[i] = B1_पंचांगp[i] / (1 << Q_B1);
		B2_पंचांगp[i] = B2_पंचांगp[i] / (1 << Q_B2);
		beta_raw = beta_raw + B1_पंचांगp[i] * x_tilde[i];
		alpha_raw = alpha_raw + B2_पंचांगp[i] * x_tilde[i];
	पूर्ण

	scale_B =
	    ((sum_y_quad / scale_factor) * (L + 1) -
	     (sum_y_sqr / scale_factor) * sum_y_sqr) * scale_factor;

	Q_scale_B = find_proper_scale(find_expn(असल(scale_B)), 10);
	scale_B = scale_B / (1 << Q_scale_B);
	अगर (scale_B == 0)
		वापस false;
	Q_beta = find_proper_scale(find_expn(असल(beta_raw)), 10);
	Q_alpha = find_proper_scale(find_expn(असल(alpha_raw)), 10);
	beta_raw = beta_raw / (1 << Q_beta);
	alpha_raw = alpha_raw / (1 << Q_alpha);
	alpha = (alpha_raw << 10) / scale_B;
	beta = (beta_raw << 10) / scale_B;
	order_1 = 3 * M - Q_x - Q_B1 - Q_beta + 10 + Q_scale_B;
	order_2 = 3 * M - Q_x - Q_B2 - Q_alpha + 10 + Q_scale_B;
	order1_5x = order_1 / 5;
	order2_3x = order_2 / 3;
	order1_5x_rem = order_1 - 5 * order1_5x;
	order2_3x_rem = order_2 - 3 * order2_3x;

	क्रम (i = 0; i < PAPRD_TABLE_SZ; i++) अणु
		पंचांगp = i * 32;
		y5 = ((beta * पंचांगp) >> 6) >> order1_5x;
		y5 = (y5 * पंचांगp) >> order1_5x;
		y5 = (y5 * पंचांगp) >> order1_5x;
		y5 = (y5 * पंचांगp) >> order1_5x;
		y5 = (y5 * पंचांगp) >> order1_5x;
		y5 = y5 >> order1_5x_rem;
		y3 = (alpha * पंचांगp) >> order2_3x;
		y3 = (y3 * पंचांगp) >> order2_3x;
		y3 = (y3 * पंचांगp) >> order2_3x;
		y3 = y3 >> order2_3x_rem;
		PA_in[i] = y5 + y3 + (256 * पंचांगp) / G_fxp;

		अगर (i >= 2) अणु
			पंचांगp = PA_in[i] - PA_in[i - 1];
			अगर (पंचांगp < 0)
				PA_in[i] =
				    PA_in[i - 1] + (PA_in[i - 1] -
						    PA_in[i - 2]);
		पूर्ण

		PA_in[i] = (PA_in[i] < 1400) ? PA_in[i] : 1400;
	पूर्ण

	beta_raw = 0;
	alpha_raw = 0;

	क्रम (i = 0; i <= L; i++) अणु
		पूर्णांक theta_tilde =
		    ((theta[i + I] << M) + y_est[i + I]) / y_est[i + I];
		theta_tilde =
		    ((theta_tilde << M) + y_est[i + I]) / y_est[i + I];
		theta_tilde =
		    ((theta_tilde << M) + y_est[i + I]) / y_est[i + I];
		beta_raw = beta_raw + B1_पंचांगp[i] * theta_tilde;
		alpha_raw = alpha_raw + B2_पंचांगp[i] * theta_tilde;
	पूर्ण

	Q_beta = find_proper_scale(find_expn(असल(beta_raw)), 10);
	Q_alpha = find_proper_scale(find_expn(असल(alpha_raw)), 10);
	beta_raw = beta_raw / (1 << Q_beta);
	alpha_raw = alpha_raw / (1 << Q_alpha);

	alpha = (alpha_raw << 10) / scale_B;
	beta = (beta_raw << 10) / scale_B;
	order_1 = 3 * M - Q_x - Q_B1 - Q_beta + 10 + Q_scale_B + 5;
	order_2 = 3 * M - Q_x - Q_B2 - Q_alpha + 10 + Q_scale_B + 5;
	order1_5x = order_1 / 5;
	order2_3x = order_2 / 3;
	order1_5x_rem = order_1 - 5 * order1_5x;
	order2_3x_rem = order_2 - 3 * order2_3x;

	क्रम (i = 0; i < PAPRD_TABLE_SZ; i++) अणु
		पूर्णांक PA_angle;

		/* pa_table[4] is calculated from PA_angle क्रम i=5 */
		अगर (i == 4)
			जारी;

		पंचांगp = i * 32;
		अगर (beta > 0)
			y5 = (((beta * पंचांगp - 64) >> 6) -
			      (1 << order1_5x)) / (1 << order1_5x);
		अन्यथा
			y5 = ((((beta * पंचांगp - 64) >> 6) +
			       (1 << order1_5x)) / (1 << order1_5x));

		y5 = (y5 * पंचांगp) / (1 << order1_5x);
		y5 = (y5 * पंचांगp) / (1 << order1_5x);
		y5 = (y5 * पंचांगp) / (1 << order1_5x);
		y5 = (y5 * पंचांगp) / (1 << order1_5x);
		y5 = y5 / (1 << order1_5x_rem);

		अगर (beta > 0)
			y3 = (alpha * पंचांगp -
			      (1 << order2_3x)) / (1 << order2_3x);
		अन्यथा
			y3 = (alpha * पंचांगp +
			      (1 << order2_3x)) / (1 << order2_3x);
		y3 = (y3 * पंचांगp) / (1 << order2_3x);
		y3 = (y3 * पंचांगp) / (1 << order2_3x);
		y3 = y3 / (1 << order2_3x_rem);

		अगर (i < 4) अणु
			PA_angle = 0;
		पूर्ण अन्यथा अणु
			PA_angle = y5 + y3;
			अगर (PA_angle < -150)
				PA_angle = -150;
			अन्यथा अगर (PA_angle > 150)
				PA_angle = 150;
		पूर्ण

		pa_table[i] = ((PA_in[i] & 0x7ff) << 11) + (PA_angle & 0x7ff);
		अगर (i == 5) अणु
			PA_angle = (PA_angle + 2) >> 1;
			pa_table[i - 1] = ((PA_in[i - 1] & 0x7ff) << 11) +
			    (PA_angle & 0x7ff);
		पूर्ण
	पूर्ण

	*gain = G_fxp;
	वापस true;
पूर्ण

व्योम ar9003_paprd_populate_single_table(काष्ठा ath_hw *ah,
					काष्ठा ath9k_hw_cal_data *caldata,
					पूर्णांक chain)
अणु
	u32 *paprd_table_val = caldata->pa_table[chain];
	u32 small_संकेत_gain = caldata->small_संकेत_gain[chain];
	u32 training_घातer = ah->paprd_training_घातer;
	u32 reg = 0;
	पूर्णांक i;

	अगर (chain == 0)
		reg = AR_PHY_PAPRD_MEM_TAB_B0;
	अन्यथा अगर (chain == 1)
		reg = AR_PHY_PAPRD_MEM_TAB_B1;
	अन्यथा अगर (chain == 2)
		reg = AR_PHY_PAPRD_MEM_TAB_B2;

	क्रम (i = 0; i < PAPRD_TABLE_SZ; i++) अणु
		REG_WRITE(ah, reg, paprd_table_val[i]);
		reg = reg + 4;
	पूर्ण

	अगर (chain == 0)
		reg = AR_PHY_PA_GAIN123_B0;
	अन्यथा अगर (chain == 1)
		reg = AR_PHY_PA_GAIN123_B1;
	अन्यथा
		reg = AR_PHY_PA_GAIN123_B2;

	REG_RMW_FIELD(ah, reg, AR_PHY_PA_GAIN123_PA_GAIN1, small_संकेत_gain);

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_CTRL1_B0,
		      AR_PHY_PAPRD_CTRL1_PAPRD_POWER_AT_AM2AM_CAL,
		      training_घातer);

	अगर (ah->caps.tx_chainmask & BIT(1))
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_CTRL1_B1,
			      AR_PHY_PAPRD_CTRL1_PAPRD_POWER_AT_AM2AM_CAL,
			      training_घातer);

	अगर (ah->caps.tx_chainmask & BIT(2))
		/* val AR_PHY_PAPRD_CTRL1_PAPRD_POWER_AT_AM2AM_CAL correct? */
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_CTRL1_B2,
			      AR_PHY_PAPRD_CTRL1_PAPRD_POWER_AT_AM2AM_CAL,
			      training_घातer);
पूर्ण
EXPORT_SYMBOL(ar9003_paprd_populate_single_table);

व्योम ar9003_paprd_setup_gain_table(काष्ठा ath_hw *ah, पूर्णांक chain)
अणु
	अचिन्हित पूर्णांक i, desired_gain, gain_index;
	अचिन्हित पूर्णांक train_घातer = ah->paprd_training_घातer;

	desired_gain = ar9003_get_desired_gain(ah, chain, train_घातer);

	gain_index = 0;
	क्रम (i = 0; i < PAPRD_GAIN_TABLE_ENTRIES; i++) अणु
		अगर (ah->paprd_gain_table_index[i] >= desired_gain)
			अवरोध;
		gain_index++;
	पूर्ण

	ar9003_tx_क्रमce_gain(ah, gain_index);

	REG_CLR_BIT(ah, AR_PHY_PAPRD_TRAINER_STAT1,
			AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE);
पूर्ण
EXPORT_SYMBOL(ar9003_paprd_setup_gain_table);

अटल bool ar9003_paprd_retrain_pa_in(काष्ठा ath_hw *ah,
				       काष्ठा ath9k_hw_cal_data *caldata,
				       पूर्णांक chain)
अणु
	u32 *pa_in = caldata->pa_table[chain];
	पूर्णांक capभाग_offset, quick_drop_offset;
	पूर्णांक capभाग2g, quick_drop;
	पूर्णांक count = 0;
	पूर्णांक i;

	अगर (!AR_SREV_9485(ah) && !AR_SREV_9330(ah))
		वापस false;

	capभाग2g = REG_READ_FIELD(ah, AR_PHY_65NM_CH0_TXRF3,
				  AR_PHY_65NM_CH0_TXRF3_CAPDIV2G);

	quick_drop = REG_READ_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
				    AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP);

	अगर (quick_drop)
		quick_drop -= 0x40;

	क्रम (i = 0; i < NUM_BIN + 1; i++) अणु
		अगर (pa_in[i] == 1400)
			count++;
	पूर्ण

	अगर (AR_SREV_9485(ah)) अणु
		अगर (pa_in[23] < 800) अणु
			capभाग_offset = (पूर्णांक)((1000 - pa_in[23] + 75) / 150);
			capभाग2g += capभाग_offset;
			अगर (capभाग2g > 7) अणु
				capभाग2g = 7;
				अगर (pa_in[23] < 600) अणु
					quick_drop++;
					अगर (quick_drop > 0)
						quick_drop = 0;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (pa_in[23] == 1400) अणु
			quick_drop_offset = min_t(पूर्णांक, count / 3, 2);
			quick_drop += quick_drop_offset;
			capभाग2g += quick_drop_offset / 2;

			अगर (capभाग2g > 7)
				capभाग2g = 7;

			अगर (quick_drop > 0) अणु
				quick_drop = 0;
				capभाग2g -= quick_drop_offset;
				अगर (capभाग2g < 0)
					capभाग2g = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण अन्यथा अगर (AR_SREV_9330(ah)) अणु
		अगर (pa_in[23] < 1000) अणु
			capभाग_offset = (1000 - pa_in[23]) / 100;
			capभाग2g += capभाग_offset;
			अगर (capभाग_offset > 3) अणु
				capभाग_offset = 1;
				quick_drop--;
			पूर्ण

			capभाग2g += capभाग_offset;
			अगर (capभाग2g > 6)
				capभाग2g = 6;
			अगर (quick_drop < -4)
				quick_drop = -4;
		पूर्ण अन्यथा अगर (pa_in[23] == 1400) अणु
			अगर (count > 3) अणु
				quick_drop++;
				capभाग2g -= count / 4;
				अगर (quick_drop > -2)
					quick_drop = -2;
			पूर्ण अन्यथा अणु
				capभाग2g--;
			पूर्ण

			अगर (capभाग2g < 0)
				capभाग2g = 0;
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_TXRF3,
		      AR_PHY_65NM_CH0_TXRF3_CAPDIV2G, capभाग2g);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP,
		      quick_drop);

	वापस true;
पूर्ण

पूर्णांक ar9003_paprd_create_curve(काष्ठा ath_hw *ah,
			      काष्ठा ath9k_hw_cal_data *caldata, पूर्णांक chain)
अणु
	u16 *small_संकेत_gain = &caldata->small_संकेत_gain[chain];
	u32 *pa_table = caldata->pa_table[chain];
	u32 *data_L, *data_U;
	पूर्णांक i, status = 0;
	u32 *buf;
	u32 reg;

	स_रखो(caldata->pa_table[chain], 0, माप(caldata->pa_table[chain]));

	buf = kदो_स्मृति_array(2 * 48, माप(u32), GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	data_L = &buf[0];
	data_U = &buf[48];

	REG_CLR_BIT(ah, AR_PHY_CHAN_INFO_MEMORY,
		    AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ);

	reg = AR_PHY_CHAN_INFO_TAB_0;
	क्रम (i = 0; i < 48; i++)
		data_L[i] = REG_READ(ah, reg + (i << 2));

	REG_SET_BIT(ah, AR_PHY_CHAN_INFO_MEMORY,
		    AR_PHY_CHAN_INFO_MEMORY_CHANINFOMEM_S2_READ);

	क्रम (i = 0; i < 48; i++)
		data_U[i] = REG_READ(ah, reg + (i << 2));

	अगर (!create_pa_curve(data_L, data_U, pa_table, small_संकेत_gain))
		status = -2;

	अगर (ar9003_paprd_retrain_pa_in(ah, caldata, chain))
		status = -EINPROGRESS;

	REG_CLR_BIT(ah, AR_PHY_PAPRD_TRAINER_STAT1,
		    AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE);

	kमुक्त(buf);

	वापस status;
पूर्ण
EXPORT_SYMBOL(ar9003_paprd_create_curve);

पूर्णांक ar9003_paprd_init_table(काष्ठा ath_hw *ah)
अणु
	पूर्णांक ret;

	ret = ar9003_paprd_setup_single_table(ah);
	अगर (ret < 0)
	    वापस ret;

	ar9003_paprd_get_gain_table(ah);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ar9003_paprd_init_table);

bool ar9003_paprd_is_करोne(काष्ठा ath_hw *ah)
अणु
	पूर्णांक paprd_करोne, agc2_pwr;

	paprd_करोne = REG_READ_FIELD(ah, AR_PHY_PAPRD_TRAINER_STAT1,
				AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_TRAIN_DONE);

	अगर (AR_SREV_9485(ah))
		जाओ निकास;

	अगर (paprd_करोne == 0x1) अणु
		agc2_pwr = REG_READ_FIELD(ah, AR_PHY_PAPRD_TRAINER_STAT1,
				AR_PHY_PAPRD_TRAINER_STAT1_PAPRD_AGC2_PWR);

		ath_dbg(ath9k_hw_common(ah), CALIBRATE,
			"AGC2_PWR = 0x%x training done = 0x%x\n",
			agc2_pwr, paprd_करोne);
	/*
	 * agc2_pwr range should not be less than 'IDEAL_AGC2_PWR_CHANGE'
	 * when the training is completely करोne, otherwise retraining is
	 * करोne to make sure the value is in ideal range
	 */
		अगर (agc2_pwr <= PAPRD_IDEAL_AGC2_PWR_RANGE)
			paprd_करोne = 0;
	पूर्ण
निकास:
	वापस !!paprd_करोne;
पूर्ण
EXPORT_SYMBOL(ar9003_paprd_is_करोne);

bool ar9003_is_paprd_enabled(काष्ठा ath_hw *ah)
अणु
	अगर ((ah->caps.hw_caps & ATH9K_HW_CAP_PAPRD) && ah->config.enable_paprd)
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(ar9003_is_paprd_enabled);
