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
#समावेश "ar9003_eeprom.h"

#घोषणा AR9300_OFDM_RATES	8
#घोषणा AR9300_HT_SS_RATES	8
#घोषणा AR9300_HT_DS_RATES	8
#घोषणा AR9300_HT_TS_RATES	8

#घोषणा AR9300_11NA_OFDM_SHIFT		0
#घोषणा AR9300_11NA_HT_SS_SHIFT		8
#घोषणा AR9300_11NA_HT_DS_SHIFT		16
#घोषणा AR9300_11NA_HT_TS_SHIFT		24

#घोषणा AR9300_11NG_OFDM_SHIFT		4
#घोषणा AR9300_11NG_HT_SS_SHIFT		12
#घोषणा AR9300_11NG_HT_DS_SHIFT		20
#घोषणा AR9300_11NG_HT_TS_SHIFT		28

अटल स्थिर पूर्णांक firstep_table[] =
/* level:  0   1   2   3   4   5   6   7   8  */
	अणु -4, -2,  0,  2,  4,  6,  8, 10, 12 पूर्ण; /* lvl 0-8, शेष 2 */

अटल स्थिर पूर्णांक cycpwrThr1_table[] =
/* level:  0   1   2   3   4   5   6   7   8  */
	अणु -6, -4, -2,  0,  2,  4,  6,  8 पूर्ण;     /* lvl 0-7, शेष 3 */

/*
 * रेजिस्टर values to turn OFDM weak संकेत detection OFF
 */
अटल स्थिर पूर्णांक m1ThreshLow_off = 127;
अटल स्थिर पूर्णांक m2ThreshLow_off = 127;
अटल स्थिर पूर्णांक m1Thresh_off = 127;
अटल स्थिर पूर्णांक m2Thresh_off = 127;
अटल स्थिर पूर्णांक m2CountThr_off =  31;
अटल स्थिर पूर्णांक m2CountThrLow_off =  63;
अटल स्थिर पूर्णांक m1ThreshLowExt_off = 127;
अटल स्थिर पूर्णांक m2ThreshLowExt_off = 127;
अटल स्थिर पूर्णांक m1ThreshExt_off = 127;
अटल स्थिर पूर्णांक m2ThreshExt_off = 127;

अटल स्थिर u8 ofdm2pwr[] = अणु
	ALL_TARGET_LEGACY_6_24,
	ALL_TARGET_LEGACY_6_24,
	ALL_TARGET_LEGACY_6_24,
	ALL_TARGET_LEGACY_6_24,
	ALL_TARGET_LEGACY_6_24,
	ALL_TARGET_LEGACY_36,
	ALL_TARGET_LEGACY_48,
	ALL_TARGET_LEGACY_54
पूर्ण;

अटल स्थिर u8 mcs2pwr_ht20[] = अणु
	ALL_TARGET_HT20_0_8_16,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_4,
	ALL_TARGET_HT20_5,
	ALL_TARGET_HT20_6,
	ALL_TARGET_HT20_7,
	ALL_TARGET_HT20_0_8_16,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_12,
	ALL_TARGET_HT20_13,
	ALL_TARGET_HT20_14,
	ALL_TARGET_HT20_15,
	ALL_TARGET_HT20_0_8_16,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_1_3_9_11_17_19,
	ALL_TARGET_HT20_20,
	ALL_TARGET_HT20_21,
	ALL_TARGET_HT20_22,
	ALL_TARGET_HT20_23
पूर्ण;

अटल स्थिर u8 mcs2pwr_ht40[] = अणु
	ALL_TARGET_HT40_0_8_16,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_4,
	ALL_TARGET_HT40_5,
	ALL_TARGET_HT40_6,
	ALL_TARGET_HT40_7,
	ALL_TARGET_HT40_0_8_16,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_12,
	ALL_TARGET_HT40_13,
	ALL_TARGET_HT40_14,
	ALL_TARGET_HT40_15,
	ALL_TARGET_HT40_0_8_16,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_1_3_9_11_17_19,
	ALL_TARGET_HT40_20,
	ALL_TARGET_HT40_21,
	ALL_TARGET_HT40_22,
	ALL_TARGET_HT40_23,
पूर्ण;

/**
 * ar9003_hw_set_channel - set channel on single-chip device
 * @ah: atheros hardware काष्ठाure
 * @chan:
 *
 * This is the function to change channel on single-chip devices, that is
 * क्रम AR9300 family of chipsets.
 *
 * This function takes the channel value in MHz and sets
 * hardware channel value. Assumes ग_लिखोs have been enabled to analog bus.
 *
 * Actual Expression,
 *
 * For 2GHz channel,
 * Channel Frequency = (3/4) * freq_ref * (chansel[8:0] + chanfrac[16:0]/2^17)
 * (freq_ref = 40MHz)
 *
 * For 5GHz channel,
 * Channel Frequency = (3/2) * freq_ref * (chansel[8:0] + chanfrac[16:0]/2^10)
 * (freq_ref = 40MHz/(24>>amodeRefSel))
 *
 * For 5GHz channels which are 5MHz spaced,
 * Channel Frequency = (3/2) * freq_ref * (chansel[8:0] + chanfrac[16:0]/2^17)
 * (freq_ref = 40MHz)
 */
अटल पूर्णांक ar9003_hw_set_channel(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	u16 bMode, fracMode = 0, aModeRefSel = 0;
	u32 freq, chan_frac, भाग, channelSel = 0, reg32 = 0;
	काष्ठा chan_centers centers;
	पूर्णांक loadSynthChannel;

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	freq = centers.synth_center;

	अगर (freq < 4800) अणु     /* 2 GHz, fractional mode */
		अगर (AR_SREV_9330(ah) || AR_SREV_9485(ah) ||
		    AR_SREV_9531(ah) || AR_SREV_9550(ah) ||
		    AR_SREV_9561(ah) || AR_SREV_9565(ah)) अणु
			अगर (ah->is_clk_25mhz)
				भाग = 75;
			अन्यथा
				भाग = 120;

			channelSel = (freq * 4) / भाग;
			chan_frac = (((freq * 4) % भाग) * 0x20000) / भाग;
			channelSel = (channelSel << 17) | chan_frac;
		पूर्ण अन्यथा अगर (AR_SREV_9340(ah)) अणु
			अगर (ah->is_clk_25mhz) अणु
				channelSel = (freq * 2) / 75;
				chan_frac = (((freq * 2) % 75) * 0x20000) / 75;
				channelSel = (channelSel << 17) | chan_frac;
			पूर्ण अन्यथा अणु
				channelSel = CHANSEL_2G(freq) >> 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			channelSel = CHANSEL_2G(freq);
		पूर्ण
		/* Set to 2G mode */
		bMode = 1;
	पूर्ण अन्यथा अणु
		अगर ((AR_SREV_9340(ah) || AR_SREV_9550(ah) ||
		     AR_SREV_9531(ah) || AR_SREV_9561(ah)) &&
		    ah->is_clk_25mhz) अणु
			channelSel = freq / 75;
			chan_frac = ((freq % 75) * 0x20000) / 75;
			channelSel = (channelSel << 17) | chan_frac;
		पूर्ण अन्यथा अणु
			channelSel = CHANSEL_5G(freq);
			/* Doubler is ON, so, भागide channelSel by 2. */
			channelSel >>= 1;
		पूर्ण
		/* Set to 5G mode */
		bMode = 0;
	पूर्ण

	/* Enable fractional mode क्रम all channels */
	fracMode = 1;
	aModeRefSel = 0;
	loadSynthChannel = 0;

	reg32 = (bMode << 29);
	REG_WRITE(ah, AR_PHY_SYNTH_CONTROL, reg32);

	/* Enable Long shअगरt Select क्रम Synthesizer */
	REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_SYNTH4,
		      AR_PHY_SYNTH4_LONG_SHIFT_SELECT, 1);

	/* Program Synth. setting */
	reg32 = (channelSel << 2) | (fracMode << 30) |
		(aModeRefSel << 28) | (loadSynthChannel << 31);
	REG_WRITE(ah, AR_PHY_65NM_CH0_SYNTH7, reg32);

	/* Toggle Load Synth channel bit */
	loadSynthChannel = 1;
	reg32 = (channelSel << 2) | (fracMode << 30) |
		(aModeRefSel << 28) | (loadSynthChannel << 31);
	REG_WRITE(ah, AR_PHY_65NM_CH0_SYNTH7, reg32);

	ah->curchan = chan;

	वापस 0;
पूर्ण

/**
 * ar9003_hw_spur_mitigate_mrc_cck - convert baseband spur frequency
 * @ah: atheros hardware काष्ठाure
 * @chan:
 *
 * For single-chip solutions. Converts to baseband spur frequency given the
 * input channel frequency and compute रेजिस्टर settings below.
 *
 * Spur mitigation क्रम MRC CCK
 */
अटल व्योम ar9003_hw_spur_mitigate_mrc_cck(काष्ठा ath_hw *ah,
					    काष्ठा ath9k_channel *chan)
अणु
	अटल स्थिर u32 spur_freq[4] = अणु 2420, 2440, 2464, 2480 पूर्ण;
	पूर्णांक cur_bb_spur, negative = 0, cck_spur_freq;
	पूर्णांक i;
	पूर्णांक range, max_spur_cnts, synth_freq;
	u8 *spur_fbin_ptr = ar9003_get_spur_chan_ptr(ah, IS_CHAN_2GHZ(chan));

	/*
	 * Need to verअगरy range +/- 10 MHz in control channel, otherwise spur
	 * is out-of-band and can be ignored.
	 */

	अगर (AR_SREV_9485(ah) || AR_SREV_9340(ah) || AR_SREV_9330(ah) ||
	    AR_SREV_9550(ah) || AR_SREV_9561(ah)) अणु
		अगर (spur_fbin_ptr[0] == 0) /* No spur */
			वापस;
		max_spur_cnts = 5;
		अगर (IS_CHAN_HT40(chan)) अणु
			range = 19;
			अगर (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
					   AR_PHY_GC_DYN2040_PRI_CH) == 0)
				synth_freq = chan->channel + 10;
			अन्यथा
				synth_freq = chan->channel - 10;
		पूर्ण अन्यथा अणु
			range = 10;
			synth_freq = chan->channel;
		पूर्ण
	पूर्ण अन्यथा अणु
		range = AR_SREV_9462(ah) ? 5 : 10;
		max_spur_cnts = 4;
		synth_freq = chan->channel;
	पूर्ण

	क्रम (i = 0; i < max_spur_cnts; i++) अणु
		अगर (AR_SREV_9462(ah) && (i == 0 || i == 3))
			जारी;

		negative = 0;
		अगर (AR_SREV_9485(ah) || AR_SREV_9340(ah) || AR_SREV_9330(ah) ||
		    AR_SREV_9550(ah) || AR_SREV_9561(ah))
			cur_bb_spur = ath9k_hw_fbin2freq(spur_fbin_ptr[i],
							 IS_CHAN_2GHZ(chan));
		अन्यथा
			cur_bb_spur = spur_freq[i];

		cur_bb_spur -= synth_freq;
		अगर (cur_bb_spur < 0) अणु
			negative = 1;
			cur_bb_spur = -cur_bb_spur;
		पूर्ण
		अगर (cur_bb_spur < range) अणु
			cck_spur_freq = (पूर्णांक)((cur_bb_spur << 19) / 11);

			अगर (negative == 1)
				cck_spur_freq = -cck_spur_freq;

			cck_spur_freq = cck_spur_freq & 0xfffff;

			REG_RMW_FIELD(ah, AR_PHY_AGC_CONTROL,
				      AR_PHY_AGC_CONTROL_YCOK_MAX, 0x7);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_SPUR_RSSI_THR, 0x7f);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_SPUR_FILTER_TYPE,
				      0x2);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_USE_CCK_SPUR_MIT,
				      0x1);
			REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
				      AR_PHY_CCK_SPUR_MIT_CCK_SPUR_FREQ,
				      cck_spur_freq);

			वापस;
		पूर्ण
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_AGC_CONTROL,
		      AR_PHY_AGC_CONTROL_YCOK_MAX, 0x5);
	REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
		      AR_PHY_CCK_SPUR_MIT_USE_CCK_SPUR_MIT, 0x0);
	REG_RMW_FIELD(ah, AR_PHY_CCK_SPUR_MIT,
		      AR_PHY_CCK_SPUR_MIT_CCK_SPUR_FREQ, 0x0);
पूर्ण

/* Clean all spur रेजिस्टर fields */
अटल व्योम ar9003_hw_spur_ofdm_clear(काष्ठा ath_hw *ah)
अणु
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_SPUR_FILTER, 0);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_SPUR_FREQ_SD, 0);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_SPUR_DELTA_PHASE, 0);
	REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
		      AR_PHY_SFCORR_EXT_SPUR_SUBCHANNEL_SD, 0);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_USE_SPUR_FILTER_IN_AGC, 0);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_USE_SPUR_FILTER_IN_SELFCOR, 0);
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_SPUR_RSSI, 0);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_EN_VIT_SPUR_RSSI, 0);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_ENABLE_NF_RSSI_SPUR_MIT, 0);

	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_ENABLE_MASK_PPM, 0);
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_PILOT_MASK, 0);
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_CHAN_MASK, 0);
	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_A, 0);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_A,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A, 0);
	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_A, 0);
	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_A, 0);
	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_A, 0);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_A,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A, 0);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_MASK_RATE_CNTL, 0);
पूर्ण

अटल व्योम ar9003_hw_spur_ofdm(काष्ठा ath_hw *ah,
				पूर्णांक freq_offset,
				पूर्णांक spur_freq_sd,
				पूर्णांक spur_delta_phase,
				पूर्णांक spur_subchannel_sd,
				पूर्णांक range,
				पूर्णांक synth_freq)
अणु
	पूर्णांक mask_index = 0;

	/* OFDM Spur mitigation */
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		 AR_PHY_TIMING4_ENABLE_SPUR_FILTER, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_SPUR_FREQ_SD, spur_freq_sd);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_SPUR_DELTA_PHASE, spur_delta_phase);
	REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
		      AR_PHY_SFCORR_EXT_SPUR_SUBCHANNEL_SD, spur_subchannel_sd);
	REG_RMW_FIELD(ah, AR_PHY_TIMING11,
		      AR_PHY_TIMING11_USE_SPUR_FILTER_IN_AGC, 0x1);

	अगर (!(AR_SREV_9565(ah) && range == 10 && synth_freq == 2437))
		REG_RMW_FIELD(ah, AR_PHY_TIMING11,
			      AR_PHY_TIMING11_USE_SPUR_FILTER_IN_SELFCOR, 0x1);

	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_SPUR_RSSI, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_SPUR_RSSI_THRESH, 34);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_EN_VIT_SPUR_RSSI, 1);

	अगर (!AR_SREV_9340(ah) &&
	    REG_READ_FIELD(ah, AR_PHY_MODE,
			   AR_PHY_MODE_DYNAMIC) == 0x1)
		REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
			      AR_PHY_SPUR_REG_ENABLE_NF_RSSI_SPUR_MIT, 1);

	mask_index = (freq_offset << 4) / 5;
	अगर (mask_index < 0)
		mask_index = mask_index - 1;

	mask_index = mask_index & 0x7f;

	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_ENABLE_MASK_PPM, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_PILOT_MASK, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_TIMING4,
		      AR_PHY_TIMING4_ENABLE_CHAN_MASK, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_A, mask_index);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_A,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A, mask_index);
	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_A, mask_index);
	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_A, 0xc);
	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_A, 0xc);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_A,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A, 0xa0);
	REG_RMW_FIELD(ah, AR_PHY_SPUR_REG,
		      AR_PHY_SPUR_REG_MASK_RATE_CNTL, 0xff);
पूर्ण

अटल व्योम ar9003_hw_spur_ofdm_9565(काष्ठा ath_hw *ah,
				     पूर्णांक freq_offset)
अणु
	पूर्णांक mask_index = 0;

	mask_index = (freq_offset << 4) / 5;
	अगर (mask_index < 0)
		mask_index = mask_index - 1;

	mask_index = mask_index & 0x7f;

	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_IDX_B,
		      mask_index);

	/* A == B */
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_B,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_IDX_A,
		      mask_index);

	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_IDX_B,
		      mask_index);
	REG_RMW_FIELD(ah, AR_PHY_PILOT_SPUR_MASK,
		      AR_PHY_PILOT_SPUR_MASK_CF_PILOT_MASK_B, 0xe);
	REG_RMW_FIELD(ah, AR_PHY_CHAN_SPUR_MASK,
		      AR_PHY_CHAN_SPUR_MASK_CF_CHAN_MASK_B, 0xe);

	/* A == B */
	REG_RMW_FIELD(ah, AR_PHY_SPUR_MASK_B,
		      AR_PHY_SPUR_MASK_A_CF_PUNC_MASK_A, 0xa0);
पूर्ण

अटल व्योम ar9003_hw_spur_ofdm_work(काष्ठा ath_hw *ah,
				     काष्ठा ath9k_channel *chan,
				     पूर्णांक freq_offset,
				     पूर्णांक range,
				     पूर्णांक synth_freq)
अणु
	पूर्णांक spur_freq_sd = 0;
	पूर्णांक spur_subchannel_sd = 0;
	पूर्णांक spur_delta_phase = 0;

	अगर (IS_CHAN_HT40(chan)) अणु
		अगर (freq_offset < 0) अणु
			अगर (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
					   AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
				spur_subchannel_sd = 1;
			अन्यथा
				spur_subchannel_sd = 0;

			spur_freq_sd = ((freq_offset + 10) << 9) / 11;

		पूर्ण अन्यथा अणु
			अगर (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
			    AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
				spur_subchannel_sd = 0;
			अन्यथा
				spur_subchannel_sd = 1;

			spur_freq_sd = ((freq_offset - 10) << 9) / 11;

		पूर्ण

		spur_delta_phase = (freq_offset << 17) / 5;

	पूर्ण अन्यथा अणु
		spur_subchannel_sd = 0;
		spur_freq_sd = (freq_offset << 9) /11;
		spur_delta_phase = (freq_offset << 18) / 5;
	पूर्ण

	spur_freq_sd = spur_freq_sd & 0x3ff;
	spur_delta_phase = spur_delta_phase & 0xfffff;

	ar9003_hw_spur_ofdm(ah,
			    freq_offset,
			    spur_freq_sd,
			    spur_delta_phase,
			    spur_subchannel_sd,
			    range, synth_freq);
पूर्ण

/* Spur mitigation क्रम OFDM */
अटल व्योम ar9003_hw_spur_mitigate_ofdm(काष्ठा ath_hw *ah,
					 काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक synth_freq;
	पूर्णांक range = 10;
	पूर्णांक freq_offset = 0;
	पूर्णांक mode;
	u8* spurChansPtr;
	अचिन्हित पूर्णांक i;
	काष्ठा ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;

	अगर (IS_CHAN_5GHZ(chan)) अणु
		spurChansPtr = &(eep->modalHeader5G.spurChans[0]);
		mode = 0;
	पूर्ण
	अन्यथा अणु
		spurChansPtr = &(eep->modalHeader2G.spurChans[0]);
		mode = 1;
	पूर्ण

	अगर (spurChansPtr[0] == 0)
		वापस; /* No spur in the mode */

	अगर (IS_CHAN_HT40(chan)) अणु
		range = 19;
		अगर (REG_READ_FIELD(ah, AR_PHY_GEN_CTRL,
				   AR_PHY_GC_DYN2040_PRI_CH) == 0x0)
			synth_freq = chan->channel - 10;
		अन्यथा
			synth_freq = chan->channel + 10;
	पूर्ण अन्यथा अणु
		range = 10;
		synth_freq = chan->channel;
	पूर्ण

	ar9003_hw_spur_ofdm_clear(ah);

	क्रम (i = 0; i < AR_EEPROM_MODAL_SPURS && spurChansPtr[i]; i++) अणु
		freq_offset = ath9k_hw_fbin2freq(spurChansPtr[i], mode);
		freq_offset -= synth_freq;
		अगर (असल(freq_offset) < range) अणु
			ar9003_hw_spur_ofdm_work(ah, chan, freq_offset,
						 range, synth_freq);

			अगर (AR_SREV_9565(ah) && (i < 4)) अणु
				freq_offset = ath9k_hw_fbin2freq(spurChansPtr[i + 1],
								 mode);
				freq_offset -= synth_freq;
				अगर (असल(freq_offset) < range)
					ar9003_hw_spur_ofdm_9565(ah, freq_offset);
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_spur_mitigate(काष्ठा ath_hw *ah,
				    काष्ठा ath9k_channel *chan)
अणु
	अगर (!AR_SREV_9565(ah))
		ar9003_hw_spur_mitigate_mrc_cck(ah, chan);
	ar9003_hw_spur_mitigate_ofdm(ah, chan);
पूर्ण

अटल u32 ar9003_hw_compute_pll_control_soc(काष्ठा ath_hw *ah,
					     काष्ठा ath9k_channel *chan)
अणु
	u32 pll;

	pll = SM(0x5, AR_RTC_9300_SOC_PLL_REFDIV);

	अगर (chan && IS_CHAN_HALF_RATE(chan))
		pll |= SM(0x1, AR_RTC_9300_SOC_PLL_CLKSEL);
	अन्यथा अगर (chan && IS_CHAN_QUARTER_RATE(chan))
		pll |= SM(0x2, AR_RTC_9300_SOC_PLL_CLKSEL);

	pll |= SM(0x2c, AR_RTC_9300_SOC_PLL_DIV_INT);

	वापस pll;
पूर्ण

अटल u32 ar9003_hw_compute_pll_control(काष्ठा ath_hw *ah,
					 काष्ठा ath9k_channel *chan)
अणु
	u32 pll;

	pll = SM(0x5, AR_RTC_9300_PLL_REFDIV);

	अगर (chan && IS_CHAN_HALF_RATE(chan))
		pll |= SM(0x1, AR_RTC_9300_PLL_CLKSEL);
	अन्यथा अगर (chan && IS_CHAN_QUARTER_RATE(chan))
		pll |= SM(0x2, AR_RTC_9300_PLL_CLKSEL);

	pll |= SM(0x2c, AR_RTC_9300_PLL_DIV);

	वापस pll;
पूर्ण

अटल व्योम ar9003_hw_set_channel_regs(काष्ठा ath_hw *ah,
				       काष्ठा ath9k_channel *chan)
अणु
	u32 phymode;
	u32 enableDacFअगरo = 0;

	enableDacFअगरo =
		(REG_READ(ah, AR_PHY_GEN_CTRL) & AR_PHY_GC_ENABLE_DAC_FIFO);

	/* Enable 11n HT, 20 MHz */
	phymode = AR_PHY_GC_HT_EN | AR_PHY_GC_SHORT_GI_40 | enableDacFअगरo;

	अगर (!AR_SREV_9561(ah))
		phymode |= AR_PHY_GC_SINGLE_HT_LTF1;

	/* Configure baseband क्रम dynamic 20/40 operation */
	अगर (IS_CHAN_HT40(chan)) अणु
		phymode |= AR_PHY_GC_DYN2040_EN;
		/* Configure control (primary) channel at +-10MHz */
		अगर (IS_CHAN_HT40PLUS(chan))
			phymode |= AR_PHY_GC_DYN2040_PRI_CH;

	पूर्ण

	/* make sure we preserve INI settings */
	phymode |= REG_READ(ah, AR_PHY_GEN_CTRL);
	/* turn off Green Field detection क्रम STA क्रम now */
	phymode &= ~AR_PHY_GC_GF_DETECT_EN;

	REG_WRITE(ah, AR_PHY_GEN_CTRL, phymode);

	/* Configure MAC क्रम 20/40 operation */
	ath9k_hw_set11nmac2040(ah, chan);

	/* global transmit समयout (25 TUs शेष)*/
	REG_WRITE(ah, AR_GTXTO, 25 << AR_GTXTO_TIMEOUT_LIMIT_S);
	/* carrier sense समयout */
	REG_WRITE(ah, AR_CST, 0xF << AR_CST_TIMEOUT_LIMIT_S);
पूर्ण

अटल व्योम ar9003_hw_init_bb(काष्ठा ath_hw *ah,
			      काष्ठा ath9k_channel *chan)
अणु
	u32 synthDelay;

	/*
	 * Wait क्रम the frequency synth to settle (synth goes on
	 * via AR_PHY_ACTIVE_EN).  Read the phy active delay रेजिस्टर.
	 * Value is in 100ns increments.
	 */
	synthDelay = REG_READ(ah, AR_PHY_RX_DELAY) & AR_PHY_RX_DELAY_DELAY;

	/* Activate the PHY (includes baseband activate + synthesizer on) */
	REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);
	ath9k_hw_synth_delay(ah, chan, synthDelay);
पूर्ण

व्योम ar9003_hw_set_chain_masks(काष्ठा ath_hw *ah, u8 rx, u8 tx)
अणु
	अगर (ah->caps.tx_chainmask == 5 || ah->caps.rx_chainmask == 5)
		REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP,
			    AR_PHY_SWAP_ALT_CHAIN);

	REG_WRITE(ah, AR_PHY_RX_CHAINMASK, rx);
	REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, rx);

	अगर ((ah->caps.hw_caps & ATH9K_HW_CAP_APM) && (tx == 0x7))
		tx = 3;

	REG_WRITE(ah, AR_SELFGEN_MASK, tx);
पूर्ण

/*
 * Override INI values with chip specअगरic configuration.
 */
अटल व्योम ar9003_hw_override_ini(काष्ठा ath_hw *ah)
अणु
	u32 val;

	/*
	 * Set the RX_ABORT and RX_DIS and clear it only after
	 * RXE is set क्रम MAC. This prevents frames with
	 * corrupted descriptor status.
	 */
	REG_SET_BIT(ah, AR_DIAG_SW, (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

	/*
	 * For AR9280 and above, there is a new feature that allows
	 * Multicast search based on both MAC Address and Key ID. By शेष,
	 * this feature is enabled. But since the driver is not using this
	 * feature, we चयन it off; otherwise multicast search based on
	 * MAC addr only will fail.
	 */
	val = REG_READ(ah, AR_PCU_MISC_MODE2) & (~AR_ADHOC_MCAST_KEYID_ENABLE);
	val |= AR_AGG_WEP_ENABLE_FIX |
	       AR_AGG_WEP_ENABLE |
	       AR_PCU_MISC_MODE2_CFP_IGNORE;
	REG_WRITE(ah, AR_PCU_MISC_MODE2, val);

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		REG_WRITE(ah, AR_GLB_SWREG_DISCONT_MODE,
			  AR_GLB_SWREG_DISCONT_EN_BT_WLAN);

		अगर (REG_READ_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				   AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL))
			ah->enabled_cals |= TX_IQ_CAL;
		अन्यथा
			ah->enabled_cals &= ~TX_IQ_CAL;

	पूर्ण

	अगर (REG_READ(ah, AR_PHY_CL_CAL_CTL) & AR_PHY_CL_CAL_ENABLE)
		ah->enabled_cals |= TX_CL_CAL;
	अन्यथा
		ah->enabled_cals &= ~TX_CL_CAL;

	अगर (AR_SREV_9340(ah) || AR_SREV_9531(ah) || AR_SREV_9550(ah) ||
	    AR_SREV_9561(ah)) अणु
		अगर (ah->is_clk_25mhz) अणु
			REG_WRITE(ah, AR_RTC_DERIVED_CLK, 0x17c << 1);
			REG_WRITE(ah, AR_SLP32_MODE, 0x0010f3d7);
			REG_WRITE(ah, AR_SLP32_INC, 0x0001e7ae);
		पूर्ण अन्यथा अणु
			REG_WRITE(ah, AR_RTC_DERIVED_CLK, 0x261 << 1);
			REG_WRITE(ah, AR_SLP32_MODE, 0x0010f400);
			REG_WRITE(ah, AR_SLP32_INC, 0x0001e800);
		पूर्ण
		udelay(100);
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_prog_ini(काष्ठा ath_hw *ah,
			       काष्ठा ar5416IniArray *iniArr,
			       पूर्णांक column)
अणु
	अचिन्हित पूर्णांक i, regWrites = 0;

	/* New INI क्रमmat: Array may be undefined (pre, core, post arrays) */
	अगर (!iniArr->ia_array)
		वापस;

	/*
	 * New INI क्रमmat: Pre, core, and post arrays क्रम a given subप्रणाली
	 * may be modal (> 2 columns) or non-modal (2 columns). Determine अगर
	 * the array is non-modal and क्रमce the column to 1.
	 */
	अगर (column >= iniArr->ia_columns)
		column = 1;

	क्रम (i = 0; i < iniArr->ia_rows; i++) अणु
		u32 reg = INI_RA(iniArr, i, 0);
		u32 val = INI_RA(iniArr, i, column);

		REG_WRITE(ah, reg, val);

		DO_DELAY(regWrites);
	पूर्ण
पूर्ण

अटल पूर्णांक ar9550_hw_get_modes_txgain_index(काष्ठा ath_hw *ah,
					    काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक ret;

	अगर (IS_CHAN_2GHZ(chan)) अणु
		अगर (IS_CHAN_HT40(chan))
			वापस 7;
		अन्यथा
			वापस 8;
	पूर्ण

	अगर (chan->channel <= 5350)
		ret = 1;
	अन्यथा अगर ((chan->channel > 5350) && (chan->channel <= 5600))
		ret = 3;
	अन्यथा
		ret = 5;

	अगर (IS_CHAN_HT40(chan))
		ret++;

	वापस ret;
पूर्ण

अटल पूर्णांक ar9561_hw_get_modes_txgain_index(काष्ठा ath_hw *ah,
					    काष्ठा ath9k_channel *chan)
अणु
	अगर (IS_CHAN_2GHZ(chan)) अणु
		अगर (IS_CHAN_HT40(chan))
			वापस 1;
		अन्यथा
			वापस 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ar9003_द्विगुनr_fix(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9300(ah) || AR_SREV_9580(ah) || AR_SREV_9550(ah)) अणु
		REG_RMW(ah, AR_PHY_65NM_CH0_RXTX2,
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK_S |
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHOVR_MASK_S, 0);
		REG_RMW(ah, AR_PHY_65NM_CH1_RXTX2,
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK_S |
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHOVR_MASK_S, 0);
		REG_RMW(ah, AR_PHY_65NM_CH2_RXTX2,
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK_S |
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHOVR_MASK_S, 0);

		udelay(200);

		REG_CLR_BIT(ah, AR_PHY_65NM_CH0_RXTX2,
			    AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK);
		REG_CLR_BIT(ah, AR_PHY_65NM_CH1_RXTX2,
			    AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK);
		REG_CLR_BIT(ah, AR_PHY_65NM_CH2_RXTX2,
			    AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK);

		udelay(1);

		REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_RXTX2,
			      AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK, 1);
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH1_RXTX2,
			      AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK, 1);
		REG_RMW_FIELD(ah, AR_PHY_65NM_CH2_RXTX2,
			      AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK, 1);

		udelay(200);

		REG_RMW_FIELD(ah, AR_PHY_65NM_CH0_SYNTH12,
			      AR_PHY_65NM_CH0_SYNTH12_VREFMUL3, 0xf);

		REG_RMW(ah, AR_PHY_65NM_CH0_RXTX2, 0,
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK_S |
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHOVR_MASK_S);
		REG_RMW(ah, AR_PHY_65NM_CH1_RXTX2, 0,
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK_S |
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHOVR_MASK_S);
		REG_RMW(ah, AR_PHY_65NM_CH2_RXTX2, 0,
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHON_MASK_S |
			1 << AR_PHY_65NM_CH0_RXTX2_SYNTHOVR_MASK_S);
	पूर्ण
पूर्ण

अटल पूर्णांक ar9003_hw_process_ini(काष्ठा ath_hw *ah,
				 काष्ठा ath9k_channel *chan)
अणु
	अचिन्हित पूर्णांक regWrites = 0, i;
	u32 modesIndex;

	अगर (IS_CHAN_5GHZ(chan))
		modesIndex = IS_CHAN_HT40(chan) ? 2 : 1;
	अन्यथा
		modesIndex = IS_CHAN_HT40(chan) ? 3 : 4;

	/*
	 * SOC, MAC, BB, RADIO initvals.
	 */
	क्रम (i = 0; i < ATH_INI_NUM_SPLIT; i++) अणु
		ar9003_hw_prog_ini(ah, &ah->iniSOC[i], modesIndex);
		ar9003_hw_prog_ini(ah, &ah->iniMac[i], modesIndex);
		ar9003_hw_prog_ini(ah, &ah->iniBB[i], modesIndex);
		ar9003_hw_prog_ini(ah, &ah->iniRadio[i], modesIndex);
		अगर (i == ATH_INI_POST && AR_SREV_9462_20_OR_LATER(ah))
			ar9003_hw_prog_ini(ah,
					   &ah->ini_radio_post_sys2ant,
					   modesIndex);
	पूर्ण

	ar9003_द्विगुनr_fix(ah);

	/*
	 * RXGAIN initvals.
	 */
	REG_WRITE_ARRAY(&ah->iniModesRxGain, 1, regWrites);

	अगर (AR_SREV_9462_20_OR_LATER(ah)) अणु
		/*
		 * CUS217 mix LNA mode.
		 */
		अगर (ar9003_hw_get_rx_gain_idx(ah) == 2) अणु
			REG_WRITE_ARRAY(&ah->ini_modes_rxgain_bb_core,
					1, regWrites);
			REG_WRITE_ARRAY(&ah->ini_modes_rxgain_bb_postamble,
					modesIndex, regWrites);
		पूर्ण

		/*
		 * 5G-XLNA
		 */
		अगर ((ar9003_hw_get_rx_gain_idx(ah) == 2) ||
		    (ar9003_hw_get_rx_gain_idx(ah) == 3)) अणु
			REG_WRITE_ARRAY(&ah->ini_modes_rxgain_xlna,
					modesIndex, regWrites);
		पूर्ण
	पूर्ण

	अगर (AR_SREV_9550(ah) || AR_SREV_9561(ah))
		REG_WRITE_ARRAY(&ah->ini_modes_rx_gain_bounds, modesIndex,
				regWrites);

	अगर (AR_SREV_9561(ah) && (ar9003_hw_get_rx_gain_idx(ah) == 0))
		REG_WRITE_ARRAY(&ah->ini_modes_rxgain_xlna,
				modesIndex, regWrites);
	/*
	 * TXGAIN initvals.
	 */
	अगर (AR_SREV_9550(ah) || AR_SREV_9531(ah) || AR_SREV_9561(ah)) अणु
		पूर्णांक modes_txgain_index = 1;

		अगर (AR_SREV_9550(ah))
			modes_txgain_index = ar9550_hw_get_modes_txgain_index(ah, chan);

		अगर (AR_SREV_9561(ah))
			modes_txgain_index =
				ar9561_hw_get_modes_txgain_index(ah, chan);

		अगर (modes_txgain_index < 0)
			वापस -EINVAL;

		REG_WRITE_ARRAY(&ah->iniModesTxGain, modes_txgain_index,
				regWrites);
	पूर्ण अन्यथा अणु
		REG_WRITE_ARRAY(&ah->iniModesTxGain, modesIndex, regWrites);
	पूर्ण

	/*
	 * For 5GHz channels requiring Fast Clock, apply
	 * dअगरferent modal values.
	 */
	अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		REG_WRITE_ARRAY(&ah->iniModesFastClock,
				modesIndex, regWrites);

	/*
	 * Clock frequency initvals.
	 */
	REG_WRITE_ARRAY(&ah->iniAdditional, 1, regWrites);

	/*
	 * JAPAN regulatory.
	 */
	अगर (chan->channel == 2484) अणु
		ar9003_hw_prog_ini(ah, &ah->iniCckfirJapan2484, 1);

		अगर (AR_SREV_9531(ah))
			REG_RMW_FIELD(ah, AR_PHY_FCAL_2_0,
				      AR_PHY_FLC_PWR_THRESH, 0);
	पूर्ण

	ah->modes_index = modesIndex;
	ar9003_hw_override_ini(ah);
	ar9003_hw_set_channel_regs(ah, chan);
	ar9003_hw_set_chain_masks(ah, ah->rxchainmask, ah->txchainmask);
	ath9k_hw_apply_txघातer(ah, chan, false);

	वापस 0;
पूर्ण

अटल व्योम ar9003_hw_set_rभ_शेषe(काष्ठा ath_hw *ah,
				 काष्ठा ath9k_channel *chan)
अणु
	u32 rfMode = 0;

	अगर (chan == शून्य)
		वापस;

	अगर (IS_CHAN_2GHZ(chan))
		rfMode |= AR_PHY_MODE_DYNAMIC;
	अन्यथा
		rfMode |= AR_PHY_MODE_OFDM;

	अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		rfMode |= (AR_PHY_MODE_DYNAMIC | AR_PHY_MODE_DYN_CCK_DISABLE);

	अगर (IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan))
		REG_RMW_FIELD(ah, AR_PHY_FRAME_CTL,
			      AR_PHY_FRAME_CTL_CF_OVERLAP_WINDOW, 3);

	REG_WRITE(ah, AR_PHY_MODE, rfMode);
पूर्ण

अटल व्योम ar9003_hw_mark_phy_inactive(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_DIS);
पूर्ण

अटल व्योम ar9003_hw_set_delta_slope(काष्ठा ath_hw *ah,
				      काष्ठा ath9k_channel *chan)
अणु
	u32 coef_scaled, ds_coef_exp, ds_coef_man;
	u32 घड़ीMhzScaled = 0x64000000;
	काष्ठा chan_centers centers;

	/*
	 * half and quarter rate can भागide the scaled घड़ी by 2 or 4
	 * scale क्रम selected channel bandwidth
	 */
	अगर (IS_CHAN_HALF_RATE(chan))
		घड़ीMhzScaled = घड़ीMhzScaled >> 1;
	अन्यथा अगर (IS_CHAN_QUARTER_RATE(chan))
		घड़ीMhzScaled = घड़ीMhzScaled >> 2;

	/*
	 * ALGO -> coef = 1e8/fcarrier*fघड़ी/40;
	 * scaled coef to provide precision क्रम this भग्नing calculation
	 */
	ath9k_hw_get_channel_centers(ah, chan, &centers);
	coef_scaled = घड़ीMhzScaled / centers.synth_center;

	ath9k_hw_get_delta_slope_vals(ah, coef_scaled, &ds_coef_man,
				      &ds_coef_exp);

	REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		      AR_PHY_TIMING3_DSC_MAN, ds_coef_man);
	REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		      AR_PHY_TIMING3_DSC_EXP, ds_coef_exp);

	/*
	 * For Short GI,
	 * scaled coeff is 9/10 that of normal coeff
	 */
	coef_scaled = (9 * coef_scaled) / 10;

	ath9k_hw_get_delta_slope_vals(ah, coef_scaled, &ds_coef_man,
				      &ds_coef_exp);

	/* क्रम लघु gi */
	REG_RMW_FIELD(ah, AR_PHY_SGI_DELTA,
		      AR_PHY_SGI_DSC_MAN, ds_coef_man);
	REG_RMW_FIELD(ah, AR_PHY_SGI_DELTA,
		      AR_PHY_SGI_DSC_EXP, ds_coef_exp);
पूर्ण

अटल bool ar9003_hw_rfbus_req(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_PHY_RFBUS_REQ, AR_PHY_RFBUS_REQ_EN);
	वापस ath9k_hw_रुको(ah, AR_PHY_RFBUS_GRANT, AR_PHY_RFBUS_GRANT_EN,
			     AR_PHY_RFBUS_GRANT_EN, AH_WAIT_TIMEOUT);
पूर्ण

/*
 * Wait क्रम the frequency synth to settle (synth goes on via PHY_ACTIVE_EN).
 * Read the phy active delay रेजिस्टर. Value is in 100ns increments.
 */
अटल व्योम ar9003_hw_rfbus_करोne(काष्ठा ath_hw *ah)
अणु
	u32 synthDelay = REG_READ(ah, AR_PHY_RX_DELAY) & AR_PHY_RX_DELAY_DELAY;

	ath9k_hw_synth_delay(ah, ah->curchan, synthDelay);

	REG_WRITE(ah, AR_PHY_RFBUS_REQ, 0);
पूर्ण

अटल bool ar9003_hw_ani_control(काष्ठा ath_hw *ah,
				  क्रमागत ath9k_ani_cmd cmd, पूर्णांक param)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_channel *chan = ah->curchan;
	काष्ठा ar5416AniState *aniState = &ah->ani;
	पूर्णांक m1ThreshLow, m2ThreshLow;
	पूर्णांक m1Thresh, m2Thresh;
	पूर्णांक m2CountThr, m2CountThrLow;
	पूर्णांक m1ThreshLowExt, m2ThreshLowExt;
	पूर्णांक m1ThreshExt, m2ThreshExt;
	s32 value, value2;

	चयन (cmd & ah->ani_function) अणु
	हाल ATH9K_ANI_OFDM_WEAK_SIGNAL_DETECTION:अणु
		/*
		 * on == 1 means ofdm weak संकेत detection is ON
		 * on == 1 is the शेष, क्रम less noise immunity
		 *
		 * on == 0 means ofdm weak संकेत detection is OFF
		 * on == 0 means more noise imm
		 */
		u32 on = param ? 1 : 0;

		अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah))
			जाओ skip_ws_det;

		m1ThreshLow = on ?
			aniState->iniDef.m1ThreshLow : m1ThreshLow_off;
		m2ThreshLow = on ?
			aniState->iniDef.m2ThreshLow : m2ThreshLow_off;
		m1Thresh = on ?
			aniState->iniDef.m1Thresh : m1Thresh_off;
		m2Thresh = on ?
			aniState->iniDef.m2Thresh : m2Thresh_off;
		m2CountThr = on ?
			aniState->iniDef.m2CountThr : m2CountThr_off;
		m2CountThrLow = on ?
			aniState->iniDef.m2CountThrLow : m2CountThrLow_off;
		m1ThreshLowExt = on ?
			aniState->iniDef.m1ThreshLowExt : m1ThreshLowExt_off;
		m2ThreshLowExt = on ?
			aniState->iniDef.m2ThreshLowExt : m2ThreshLowExt_off;
		m1ThreshExt = on ?
			aniState->iniDef.m1ThreshExt : m1ThreshExt_off;
		m2ThreshExt = on ?
			aniState->iniDef.m2ThreshExt : m2ThreshExt_off;

		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M1_THRESH_LOW,
			      m1ThreshLow);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M2_THRESH_LOW,
			      m2ThreshLow);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M1_THRESH,
			      m1Thresh);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M2_THRESH,
			      m2Thresh);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M2COUNT_THR,
			      m2CountThr);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW,
			      m2CountThrLow);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M1_THRESH_LOW,
			      m1ThreshLowExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M2_THRESH_LOW,
			      m2ThreshLowExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M1_THRESH,
			      m1ThreshExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M2_THRESH,
			      m2ThreshExt);
skip_ws_det:
		अगर (on)
			REG_SET_BIT(ah, AR_PHY_SFCORR_LOW,
				    AR_PHY_SFCORR_LOW_USE_SELF_CORR_LOW);
		अन्यथा
			REG_CLR_BIT(ah, AR_PHY_SFCORR_LOW,
				    AR_PHY_SFCORR_LOW_USE_SELF_CORR_LOW);

		अगर (on != aniState->ofdmWeakSigDetect) अणु
			ath_dbg(common, ANI,
				"** ch %d: ofdm weak signal: %s=>%s\n",
				chan->channel,
				aniState->ofdmWeakSigDetect ?
				"on" : "off",
				on ? "on" : "off");
			अगर (on)
				ah->stats.ast_ani_ofdmon++;
			अन्यथा
				ah->stats.ast_ani_ofdmoff++;
			aniState->ofdmWeakSigDetect = on;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ATH9K_ANI_FIRSTEP_LEVEL:अणु
		u32 level = param;

		अगर (level >= ARRAY_SIZE(firstep_table)) अणु
			ath_dbg(common, ANI,
				"ATH9K_ANI_FIRSTEP_LEVEL: level out of range (%u > %zu)\n",
				level, ARRAY_SIZE(firstep_table));
			वापस false;
		पूर्ण

		/*
		 * make रेजिस्टर setting relative to शेष
		 * from INI file & cap value
		 */
		value = firstep_table[level] -
			firstep_table[ATH9K_ANI_FIRSTEP_LVL] +
			aniState->iniDef.firstep;
		अगर (value < ATH9K_SIG_FIRSTEP_SETTING_MIN)
			value = ATH9K_SIG_FIRSTEP_SETTING_MIN;
		अगर (value > ATH9K_SIG_FIRSTEP_SETTING_MAX)
			value = ATH9K_SIG_FIRSTEP_SETTING_MAX;
		REG_RMW_FIELD(ah, AR_PHY_FIND_SIG,
			      AR_PHY_FIND_SIG_FIRSTEP,
			      value);
		/*
		 * we need to set first step low रेजिस्टर too
		 * make रेजिस्टर setting relative to शेष
		 * from INI file & cap value
		 */
		value2 = firstep_table[level] -
			 firstep_table[ATH9K_ANI_FIRSTEP_LVL] +
			 aniState->iniDef.firstepLow;
		अगर (value2 < ATH9K_SIG_FIRSTEP_SETTING_MIN)
			value2 = ATH9K_SIG_FIRSTEP_SETTING_MIN;
		अगर (value2 > ATH9K_SIG_FIRSTEP_SETTING_MAX)
			value2 = ATH9K_SIG_FIRSTEP_SETTING_MAX;

		REG_RMW_FIELD(ah, AR_PHY_FIND_SIG_LOW,
			      AR_PHY_FIND_SIG_LOW_FIRSTEP_LOW, value2);

		अगर (level != aniState->firstepLevel) अणु
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] firstep[level]=%d ini=%d\n",
				chan->channel,
				aniState->firstepLevel,
				level,
				ATH9K_ANI_FIRSTEP_LVL,
				value,
				aniState->iniDef.firstep);
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] firstep_low[level]=%d ini=%d\n",
				chan->channel,
				aniState->firstepLevel,
				level,
				ATH9K_ANI_FIRSTEP_LVL,
				value2,
				aniState->iniDef.firstepLow);
			अगर (level > aniState->firstepLevel)
				ah->stats.ast_ani_stepup++;
			अन्यथा अगर (level < aniState->firstepLevel)
				ah->stats.ast_ani_stepकरोwn++;
			aniState->firstepLevel = level;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ATH9K_ANI_SPUR_IMMUNITY_LEVEL:अणु
		u32 level = param;

		अगर (level >= ARRAY_SIZE(cycpwrThr1_table)) अणु
			ath_dbg(common, ANI,
				"ATH9K_ANI_SPUR_IMMUNITY_LEVEL: level out of range (%u > %zu)\n",
				level, ARRAY_SIZE(cycpwrThr1_table));
			वापस false;
		पूर्ण
		/*
		 * make रेजिस्टर setting relative to शेष
		 * from INI file & cap value
		 */
		value = cycpwrThr1_table[level] -
			cycpwrThr1_table[ATH9K_ANI_SPUR_IMMUNE_LVL] +
			aniState->iniDef.cycpwrThr1;
		अगर (value < ATH9K_SIG_SPUR_IMM_SETTING_MIN)
			value = ATH9K_SIG_SPUR_IMM_SETTING_MIN;
		अगर (value > ATH9K_SIG_SPUR_IMM_SETTING_MAX)
			value = ATH9K_SIG_SPUR_IMM_SETTING_MAX;
		REG_RMW_FIELD(ah, AR_PHY_TIMING5,
			      AR_PHY_TIMING5_CYCPWR_THR1,
			      value);

		/*
		 * set AR_PHY_EXT_CCA क्रम extension channel
		 * make रेजिस्टर setting relative to शेष
		 * from INI file & cap value
		 */
		value2 = cycpwrThr1_table[level] -
			 cycpwrThr1_table[ATH9K_ANI_SPUR_IMMUNE_LVL] +
			 aniState->iniDef.cycpwrThr1Ext;
		अगर (value2 < ATH9K_SIG_SPUR_IMM_SETTING_MIN)
			value2 = ATH9K_SIG_SPUR_IMM_SETTING_MIN;
		अगर (value2 > ATH9K_SIG_SPUR_IMM_SETTING_MAX)
			value2 = ATH9K_SIG_SPUR_IMM_SETTING_MAX;
		REG_RMW_FIELD(ah, AR_PHY_EXT_CCA,
			      AR_PHY_EXT_CYCPWR_THR1, value2);

		अगर (level != aniState->spurImmunityLevel) अणु
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] cycpwrThr1[level]=%d ini=%d\n",
				chan->channel,
				aniState->spurImmunityLevel,
				level,
				ATH9K_ANI_SPUR_IMMUNE_LVL,
				value,
				aniState->iniDef.cycpwrThr1);
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] cycpwrThr1Ext[level]=%d ini=%d\n",
				chan->channel,
				aniState->spurImmunityLevel,
				level,
				ATH9K_ANI_SPUR_IMMUNE_LVL,
				value2,
				aniState->iniDef.cycpwrThr1Ext);
			अगर (level > aniState->spurImmunityLevel)
				ah->stats.ast_ani_spurup++;
			अन्यथा अगर (level < aniState->spurImmunityLevel)
				ah->stats.ast_ani_spurकरोwn++;
			aniState->spurImmunityLevel = level;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ATH9K_ANI_MRC_CCK:अणु
		/*
		 * is_on == 1 means MRC CCK ON (शेष, less noise imm)
		 * is_on == 0 means MRC CCK is OFF (more noise imm)
		 */
		bool is_on = param ? 1 : 0;

		अगर (ah->caps.rx_chainmask == 1)
			अवरोध;

		REG_RMW_FIELD(ah, AR_PHY_MRC_CCK_CTRL,
			      AR_PHY_MRC_CCK_ENABLE, is_on);
		REG_RMW_FIELD(ah, AR_PHY_MRC_CCK_CTRL,
			      AR_PHY_MRC_CCK_MUX_REG, is_on);
		अगर (is_on != aniState->mrcCCK) अणु
			ath_dbg(common, ANI, "** ch %d: MRC CCK: %s=>%s\n",
				chan->channel,
				aniState->mrcCCK ? "on" : "off",
				is_on ? "on" : "off");
			अगर (is_on)
				ah->stats.ast_ani_ccklow++;
			अन्यथा
				ah->stats.ast_ani_cckhigh++;
			aniState->mrcCCK = is_on;
		पूर्ण
	अवरोध;
	पूर्ण
	शेष:
		ath_dbg(common, ANI, "invalid cmd %u\n", cmd);
		वापस false;
	पूर्ण

	ath_dbg(common, ANI,
		"ANI parameters: SI=%d, ofdmWS=%s FS=%d MRCcck=%s listenTime=%d ofdmErrs=%d cckErrs=%d\n",
		aniState->spurImmunityLevel,
		aniState->ofdmWeakSigDetect ? "on" : "off",
		aniState->firstepLevel,
		aniState->mrcCCK ? "on" : "off",
		aniState->listenTime,
		aniState->ofdmPhyErrCount,
		aniState->cckPhyErrCount);
	वापस true;
पूर्ण

अटल व्योम ar9003_hw_करो_getnf(काष्ठा ath_hw *ah,
			      पूर्णांक16_t nfarray[NUM_NF_READINGS])
अणु
#घोषणा AR_PHY_CH_MINCCA_PWR	0x1FF00000
#घोषणा AR_PHY_CH_MINCCA_PWR_S	20
#घोषणा AR_PHY_CH_EXT_MINCCA_PWR 0x01FF0000
#घोषणा AR_PHY_CH_EXT_MINCCA_PWR_S 16

	पूर्णांक16_t nf;
	पूर्णांक i;

	क्रम (i = 0; i < AR9300_MAX_CHAINS; i++) अणु
		अगर (ah->rxchainmask & BIT(i)) अणु
			nf = MS(REG_READ(ah, ah->nf_regs[i]),
					 AR_PHY_CH_MINCCA_PWR);
			nfarray[i] = sign_extend32(nf, 8);

			अगर (IS_CHAN_HT40(ah->curchan)) अणु
				u8 ext_idx = AR9300_MAX_CHAINS + i;

				nf = MS(REG_READ(ah, ah->nf_regs[ext_idx]),
						 AR_PHY_CH_EXT_MINCCA_PWR);
				nfarray[ext_idx] = sign_extend32(nf, 8);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_set_nf_limits(काष्ठा ath_hw *ah)
अणु
	ah->nf_2g.max = AR_PHY_CCA_MAX_GOOD_VAL_9300_2GHZ;
	ah->nf_2g.min = AR_PHY_CCA_MIN_GOOD_VAL_9300_2GHZ;
	ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_9300_2GHZ;
	ah->nf_5g.max = AR_PHY_CCA_MAX_GOOD_VAL_9300_5GHZ;
	ah->nf_5g.min = AR_PHY_CCA_MIN_GOOD_VAL_9300_5GHZ;
	ah->nf_5g.nominal = AR_PHY_CCA_NOM_VAL_9300_5GHZ;

	अगर (AR_SREV_9330(ah))
		ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_9330_2GHZ;

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		ah->nf_2g.min = AR_PHY_CCA_MIN_GOOD_VAL_9462_2GHZ;
		ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_9462_2GHZ;
		ah->nf_5g.min = AR_PHY_CCA_MIN_GOOD_VAL_9462_5GHZ;
		ah->nf_5g.nominal = AR_PHY_CCA_NOM_VAL_9462_5GHZ;
	पूर्ण
पूर्ण

/*
 * Initialize the ANI रेजिस्टर values with शेष (ini) values.
 * This routine is called during a (full) hardware reset after
 * all the रेजिस्टरs are initialised from the INI.
 */
अटल व्योम ar9003_hw_ani_cache_ini_regs(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar5416AniState *aniState;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_channel *chan = ah->curchan;
	काष्ठा ath9k_ani_शेष *iniDef;
	u32 val;

	aniState = &ah->ani;
	iniDef = &aniState->iniDef;

	ath_dbg(common, ANI, "ver %d.%d opmode %u chan %d Mhz\n",
		ah->hw_version.macVersion,
		ah->hw_version.macRev,
		ah->opmode,
		chan->channel);

	val = REG_READ(ah, AR_PHY_SFCORR);
	iniDef->m1Thresh = MS(val, AR_PHY_SFCORR_M1_THRESH);
	iniDef->m2Thresh = MS(val, AR_PHY_SFCORR_M2_THRESH);
	iniDef->m2CountThr = MS(val, AR_PHY_SFCORR_M2COUNT_THR);

	val = REG_READ(ah, AR_PHY_SFCORR_LOW);
	iniDef->m1ThreshLow = MS(val, AR_PHY_SFCORR_LOW_M1_THRESH_LOW);
	iniDef->m2ThreshLow = MS(val, AR_PHY_SFCORR_LOW_M2_THRESH_LOW);
	iniDef->m2CountThrLow = MS(val, AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW);

	val = REG_READ(ah, AR_PHY_SFCORR_EXT);
	iniDef->m1ThreshExt = MS(val, AR_PHY_SFCORR_EXT_M1_THRESH);
	iniDef->m2ThreshExt = MS(val, AR_PHY_SFCORR_EXT_M2_THRESH);
	iniDef->m1ThreshLowExt = MS(val, AR_PHY_SFCORR_EXT_M1_THRESH_LOW);
	iniDef->m2ThreshLowExt = MS(val, AR_PHY_SFCORR_EXT_M2_THRESH_LOW);
	iniDef->firstep = REG_READ_FIELD(ah,
					 AR_PHY_FIND_SIG,
					 AR_PHY_FIND_SIG_FIRSTEP);
	iniDef->firstepLow = REG_READ_FIELD(ah,
					    AR_PHY_FIND_SIG_LOW,
					    AR_PHY_FIND_SIG_LOW_FIRSTEP_LOW);
	iniDef->cycpwrThr1 = REG_READ_FIELD(ah,
					    AR_PHY_TIMING5,
					    AR_PHY_TIMING5_CYCPWR_THR1);
	iniDef->cycpwrThr1Ext = REG_READ_FIELD(ah,
					       AR_PHY_EXT_CCA,
					       AR_PHY_EXT_CYCPWR_THR1);

	/* these levels just got reset to शेषs by the INI */
	aniState->spurImmunityLevel = ATH9K_ANI_SPUR_IMMUNE_LVL;
	aniState->firstepLevel = ATH9K_ANI_FIRSTEP_LVL;
	aniState->ofdmWeakSigDetect = true;
	aniState->mrcCCK = true;
पूर्ण

अटल व्योम ar9003_hw_set_radar_params(काष्ठा ath_hw *ah,
				       काष्ठा ath_hw_radar_conf *conf)
अणु
	अचिन्हित पूर्णांक regWrites = 0;
	u32 radar_0 = 0, radar_1;

	अगर (!conf) अणु
		REG_CLR_BIT(ah, AR_PHY_RADAR_0, AR_PHY_RADAR_0_ENA);
		वापस;
	पूर्ण

	radar_0 |= AR_PHY_RADAR_0_ENA | AR_PHY_RADAR_0_FFT_ENA;
	radar_0 |= SM(conf->fir_घातer, AR_PHY_RADAR_0_FIRPWR);
	radar_0 |= SM(conf->radar_rssi, AR_PHY_RADAR_0_RRSSI);
	radar_0 |= SM(conf->pulse_height, AR_PHY_RADAR_0_HEIGHT);
	radar_0 |= SM(conf->pulse_rssi, AR_PHY_RADAR_0_PRSSI);
	radar_0 |= SM(conf->pulse_inband, AR_PHY_RADAR_0_INBAND);

	radar_1 = REG_READ(ah, AR_PHY_RADAR_1);
	radar_1 &= ~(AR_PHY_RADAR_1_MAXLEN | AR_PHY_RADAR_1_RELSTEP_THRESH |
		     AR_PHY_RADAR_1_RELPWR_THRESH);
	radar_1 |= AR_PHY_RADAR_1_MAX_RRSSI;
	radar_1 |= AR_PHY_RADAR_1_BLOCK_CHECK;
	radar_1 |= SM(conf->pulse_maxlen, AR_PHY_RADAR_1_MAXLEN);
	radar_1 |= SM(conf->pulse_inband_step, AR_PHY_RADAR_1_RELSTEP_THRESH);
	radar_1 |= SM(conf->radar_inband, AR_PHY_RADAR_1_RELPWR_THRESH);

	REG_WRITE(ah, AR_PHY_RADAR_0, radar_0);
	REG_WRITE(ah, AR_PHY_RADAR_1, radar_1);
	अगर (conf->ext_channel)
		REG_SET_BIT(ah, AR_PHY_RADAR_EXT, AR_PHY_RADAR_EXT_ENA);
	अन्यथा
		REG_CLR_BIT(ah, AR_PHY_RADAR_EXT, AR_PHY_RADAR_EXT_ENA);

	अगर (AR_SREV_9300(ah) || AR_SREV_9340(ah) || AR_SREV_9580(ah)) अणु
		REG_WRITE_ARRAY(&ah->ini_dfs,
				IS_CHAN_HT40(ah->curchan) ? 2 : 1, regWrites);
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_set_radar_conf(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_radar_conf *conf = &ah->radar_conf;

	conf->fir_घातer = -28;
	conf->radar_rssi = 0;
	conf->pulse_height = 10;
	conf->pulse_rssi = 15;
	conf->pulse_inband = 8;
	conf->pulse_maxlen = 255;
	conf->pulse_inband_step = 12;
	conf->radar_inband = 8;
पूर्ण

अटल व्योम ar9003_hw_antभाग_comb_conf_get(काष्ठा ath_hw *ah,
					   काष्ठा ath_hw_antcomb_conf *antconf)
अणु
	u32 regval;

	regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
	antconf->मुख्य_lna_conf = (regval & AR_PHY_ANT_DIV_MAIN_LNACONF) >>
				  AR_PHY_ANT_DIV_MAIN_LNACONF_S;
	antconf->alt_lna_conf = (regval & AR_PHY_ANT_DIV_ALT_LNACONF) >>
				 AR_PHY_ANT_DIV_ALT_LNACONF_S;
	antconf->fast_भाग_bias = (regval & AR_PHY_ANT_FAST_DIV_BIAS) >>
				  AR_PHY_ANT_FAST_DIV_BIAS_S;

	अगर (AR_SREV_9330_11(ah)) अणु
		antconf->lna1_lna2_चयन_delta = -1;
		antconf->lna1_lna2_delta = -9;
		antconf->भाग_group = 1;
	पूर्ण अन्यथा अगर (AR_SREV_9485(ah)) अणु
		antconf->lna1_lna2_चयन_delta = -1;
		antconf->lna1_lna2_delta = -9;
		antconf->भाग_group = 2;
	पूर्ण अन्यथा अगर (AR_SREV_9565(ah)) अणु
		antconf->lna1_lna2_चयन_delta = 3;
		antconf->lna1_lna2_delta = -9;
		antconf->भाग_group = 3;
	पूर्ण अन्यथा अणु
		antconf->lna1_lna2_चयन_delta = -1;
		antconf->lna1_lna2_delta = -3;
		antconf->भाग_group = 0;
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_antभाग_comb_conf_set(काष्ठा ath_hw *ah,
				   काष्ठा ath_hw_antcomb_conf *antconf)
अणु
	u32 regval;

	regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
	regval &= ~(AR_PHY_ANT_DIV_MAIN_LNACONF |
		    AR_PHY_ANT_DIV_ALT_LNACONF |
		    AR_PHY_ANT_FAST_DIV_BIAS |
		    AR_PHY_ANT_DIV_MAIN_GAINTB |
		    AR_PHY_ANT_DIV_ALT_GAINTB);
	regval |= ((antconf->मुख्य_lna_conf << AR_PHY_ANT_DIV_MAIN_LNACONF_S)
		   & AR_PHY_ANT_DIV_MAIN_LNACONF);
	regval |= ((antconf->alt_lna_conf << AR_PHY_ANT_DIV_ALT_LNACONF_S)
		   & AR_PHY_ANT_DIV_ALT_LNACONF);
	regval |= ((antconf->fast_भाग_bias << AR_PHY_ANT_FAST_DIV_BIAS_S)
		   & AR_PHY_ANT_FAST_DIV_BIAS);
	regval |= ((antconf->मुख्य_gaपूर्णांकb << AR_PHY_ANT_DIV_MAIN_GAINTB_S)
		   & AR_PHY_ANT_DIV_MAIN_GAINTB);
	regval |= ((antconf->alt_gaपूर्णांकb << AR_PHY_ANT_DIV_ALT_GAINTB_S)
		   & AR_PHY_ANT_DIV_ALT_GAINTB);

	REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT

अटल व्योम ar9003_hw_set_bt_ant_भागersity(काष्ठा ath_hw *ah, bool enable)
अणु
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	u8 ant_भाग_ctl1;
	u32 regval;

	अगर (!AR_SREV_9485(ah) && !AR_SREV_9565(ah))
		वापस;

	अगर (AR_SREV_9485(ah)) अणु
		regval = ar9003_hw_ant_ctrl_common_2_get(ah,
						 IS_CHAN_2GHZ(ah->curchan));
		अगर (enable) अणु
			regval &= ~AR_SWITCH_TABLE_COM2_ALL;
			regval |= ah->config.ant_ctrl_comm2g_चयन_enable;
		पूर्ण
		REG_RMW_FIELD(ah, AR_PHY_SWITCH_COM_2,
			      AR_SWITCH_TABLE_COM2_ALL, regval);
	पूर्ण

	ant_भाग_ctl1 = ah->eep_ops->get_eeprom(ah, EEP_ANT_DIV_CTL1);

	/*
	 * Set MAIN/ALT LNA conf.
	 * Set MAIN/ALT gain_tb.
	 */
	regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
	regval &= (~AR_ANT_DIV_CTRL_ALL);
	regval |= (ant_भाग_ctl1 & 0x3f) << AR_ANT_DIV_CTRL_ALL_S;
	REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);

	अगर (AR_SREV_9485_11_OR_LATER(ah)) अणु
		/*
		 * Enable LNA भागersity.
		 */
		regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
		regval &= ~AR_PHY_ANT_DIV_LNADIV;
		regval |= ((ant_भाग_ctl1 >> 6) & 0x1) << AR_PHY_ANT_DIV_LNADIV_S;
		अगर (enable)
			regval |= AR_ANT_DIV_ENABLE;

		REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);

		/*
		 * Enable fast antenna भागersity.
		 */
		regval = REG_READ(ah, AR_PHY_CCK_DETECT);
		regval &= ~AR_FAST_DIV_ENABLE;
		regval |= ((ant_भाग_ctl1 >> 7) & 0x1) << AR_FAST_DIV_ENABLE_S;
		अगर (enable)
			regval |= AR_FAST_DIV_ENABLE;

		REG_WRITE(ah, AR_PHY_CCK_DETECT, regval);

		अगर (pCap->hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB) अणु
			regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
			regval &= (~(AR_PHY_ANT_DIV_MAIN_LNACONF |
				     AR_PHY_ANT_DIV_ALT_LNACONF |
				     AR_PHY_ANT_DIV_ALT_GAINTB |
				     AR_PHY_ANT_DIV_MAIN_GAINTB));
			/*
			 * Set MAIN to LNA1 and ALT to LNA2 at the
			 * beginning.
			 */
			regval |= (ATH_ANT_DIV_COMB_LNA1 <<
				   AR_PHY_ANT_DIV_MAIN_LNACONF_S);
			regval |= (ATH_ANT_DIV_COMB_LNA2 <<
				   AR_PHY_ANT_DIV_ALT_LNACONF_S);
			REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);
		पूर्ण
	पूर्ण अन्यथा अगर (AR_SREV_9565(ah)) अणु
		अगर (enable) अणु
			REG_SET_BIT(ah, AR_PHY_MC_GAIN_CTRL,
				    AR_ANT_DIV_ENABLE);
			REG_SET_BIT(ah, AR_PHY_MC_GAIN_CTRL,
				    (1 << AR_PHY_ANT_SW_RX_PROT_S));
			REG_SET_BIT(ah, AR_PHY_CCK_DETECT,
				    AR_FAST_DIV_ENABLE);
			REG_SET_BIT(ah, AR_PHY_RESTART,
				    AR_PHY_RESTART_ENABLE_DIV_M2FLAG);
			REG_SET_BIT(ah, AR_BTCOEX_WL_LNADIV,
				    AR_BTCOEX_WL_LNADIV_FORCE_ON);
		पूर्ण अन्यथा अणु
			REG_CLR_BIT(ah, AR_PHY_MC_GAIN_CTRL,
				    AR_ANT_DIV_ENABLE);
			REG_CLR_BIT(ah, AR_PHY_MC_GAIN_CTRL,
				    (1 << AR_PHY_ANT_SW_RX_PROT_S));
			REG_CLR_BIT(ah, AR_PHY_CCK_DETECT,
				    AR_FAST_DIV_ENABLE);
			REG_CLR_BIT(ah, AR_PHY_RESTART,
				    AR_PHY_RESTART_ENABLE_DIV_M2FLAG);
			REG_CLR_BIT(ah, AR_BTCOEX_WL_LNADIV,
				    AR_BTCOEX_WL_LNADIV_FORCE_ON);

			regval = REG_READ(ah, AR_PHY_MC_GAIN_CTRL);
			regval &= ~(AR_PHY_ANT_DIV_MAIN_LNACONF |
				    AR_PHY_ANT_DIV_ALT_LNACONF |
				    AR_PHY_ANT_DIV_MAIN_GAINTB |
				    AR_PHY_ANT_DIV_ALT_GAINTB);
			regval |= (ATH_ANT_DIV_COMB_LNA1 <<
				   AR_PHY_ANT_DIV_MAIN_LNACONF_S);
			regval |= (ATH_ANT_DIV_COMB_LNA2 <<
				   AR_PHY_ANT_DIV_ALT_LNACONF_S);
			REG_WRITE(ah, AR_PHY_MC_GAIN_CTRL, regval);
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक ar9003_hw_fast_chan_change(काष्ठा ath_hw *ah,
				      काष्ठा ath9k_channel *chan,
				      u8 *ini_reloaded)
अणु
	अचिन्हित पूर्णांक regWrites = 0;
	u32 modesIndex, txgain_index;

	अगर (IS_CHAN_5GHZ(chan))
		modesIndex = IS_CHAN_HT40(chan) ? 2 : 1;
	अन्यथा
		modesIndex = IS_CHAN_HT40(chan) ? 3 : 4;

	txgain_index = AR_SREV_9531(ah) ? 1 : modesIndex;

	अगर (modesIndex == ah->modes_index) अणु
		*ini_reloaded = false;
		जाओ set_rभ_शेषe;
	पूर्ण

	ar9003_hw_prog_ini(ah, &ah->iniSOC[ATH_INI_POST], modesIndex);
	ar9003_hw_prog_ini(ah, &ah->iniMac[ATH_INI_POST], modesIndex);
	ar9003_hw_prog_ini(ah, &ah->iniBB[ATH_INI_POST], modesIndex);
	ar9003_hw_prog_ini(ah, &ah->iniRadio[ATH_INI_POST], modesIndex);

	अगर (AR_SREV_9462_20_OR_LATER(ah))
		ar9003_hw_prog_ini(ah, &ah->ini_radio_post_sys2ant,
				   modesIndex);

	REG_WRITE_ARRAY(&ah->iniModesTxGain, txgain_index, regWrites);

	अगर (AR_SREV_9462_20_OR_LATER(ah)) अणु
		/*
		 * CUS217 mix LNA mode.
		 */
		अगर (ar9003_hw_get_rx_gain_idx(ah) == 2) अणु
			REG_WRITE_ARRAY(&ah->ini_modes_rxgain_bb_core,
					1, regWrites);
			REG_WRITE_ARRAY(&ah->ini_modes_rxgain_bb_postamble,
					modesIndex, regWrites);
		पूर्ण
	पूर्ण

	/*
	 * For 5GHz channels requiring Fast Clock, apply
	 * dअगरferent modal values.
	 */
	अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		REG_WRITE_ARRAY(&ah->iniModesFastClock, modesIndex, regWrites);

	अगर (AR_SREV_9565(ah))
		REG_WRITE_ARRAY(&ah->iniModesFastClock, 1, regWrites);

	/*
	 * JAPAN regulatory.
	 */
	अगर (chan->channel == 2484)
		ar9003_hw_prog_ini(ah, &ah->iniCckfirJapan2484, 1);

	ah->modes_index = modesIndex;
	*ini_reloaded = true;

set_rभ_शेषe:
	ar9003_hw_set_rभ_शेषe(ah, chan);
	वापस 0;
पूर्ण

अटल व्योम ar9003_hw_spectral_scan_config(काष्ठा ath_hw *ah,
					   काष्ठा ath_spec_scan *param)
अणु
	u8 count;

	अगर (!param->enabled) अणु
		REG_CLR_BIT(ah, AR_PHY_SPECTRAL_SCAN,
			    AR_PHY_SPECTRAL_SCAN_ENABLE);
		वापस;
	पूर्ण

	REG_SET_BIT(ah, AR_PHY_RADAR_0, AR_PHY_RADAR_0_FFT_ENA);
	REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, AR_PHY_SPECTRAL_SCAN_ENABLE);

	/* on AR93xx and newer, count = 0 will make the the chip send
	 * spectral samples endlessly. Check अगर this really was पूर्णांकended,
	 * and fix otherwise.
	 */
	count = param->count;
	अगर (param->endless)
		count = 0;
	अन्यथा अगर (param->count == 0)
		count = 1;

	अगर (param->लघु_repeat)
		REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN,
			    AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT);
	अन्यथा
		REG_CLR_BIT(ah, AR_PHY_SPECTRAL_SCAN,
			    AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT);

	REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
		      AR_PHY_SPECTRAL_SCAN_COUNT, count);
	REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
		      AR_PHY_SPECTRAL_SCAN_PERIOD, param->period);
	REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
		      AR_PHY_SPECTRAL_SCAN_FFT_PERIOD, param->fft_period);

	वापस;
पूर्ण

अटल व्योम ar9003_hw_spectral_scan_trigger(काष्ठा ath_hw *ah)
अणु
	REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN,
		    AR_PHY_SPECTRAL_SCAN_ENABLE);
	/* Activate spectral scan */
	REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN,
		    AR_PHY_SPECTRAL_SCAN_ACTIVE);
पूर्ण

अटल व्योम ar9003_hw_spectral_scan_रुको(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	/* Poll क्रम spectral scan complete */
	अगर (!ath9k_hw_रुको(ah, AR_PHY_SPECTRAL_SCAN,
			   AR_PHY_SPECTRAL_SCAN_ACTIVE,
			   0, AH_WAIT_TIMEOUT)) अणु
		ath_err(common, "spectral scan wait failed\n");
		वापस;
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_tx99_start(काष्ठा ath_hw *ah, u32 qnum)
अणु
	REG_SET_BIT(ah, AR_PHY_TEST, PHY_AGC_CLR);
	REG_CLR_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_DIS);
	REG_WRITE(ah, AR_CR, AR_CR_RXD);
	REG_WRITE(ah, AR_DLCL_IFS(qnum), 0);
	REG_WRITE(ah, AR_D_GBL_IFS_SIFS, 20); /* 50 OK */
	REG_WRITE(ah, AR_D_GBL_IFS_EIFS, 20);
	REG_WRITE(ah, AR_TIME_OUT, 0x00000400);
	REG_WRITE(ah, AR_DRETRY_LIMIT(qnum), 0xffffffff);
	REG_SET_BIT(ah, AR_QMISC(qnum), AR_Q_MISC_DCU_EARLY_TERM_REQ);
पूर्ण

अटल व्योम ar9003_hw_tx99_stop(काष्ठा ath_hw *ah)
अणु
	REG_CLR_BIT(ah, AR_PHY_TEST, PHY_AGC_CLR);
	REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_DIS);
पूर्ण

अटल व्योम ar9003_hw_tx99_set_txघातer(काष्ठा ath_hw *ah, u8 txघातer)
अणु
	अटल u8 p_pwr_array[ar9300RateSize] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक i;

	txघातer = txघातer <= MAX_RATE_POWER ? txघातer : MAX_RATE_POWER;
	क्रम (i = 0; i < ar9300RateSize; i++)
		p_pwr_array[i] = txघातer;

	ar9003_hw_tx_घातer_regग_लिखो(ah, p_pwr_array);
पूर्ण

अटल व्योम ar9003_hw_init_txघातer_cck(काष्ठा ath_hw *ah, u8 *rate_array)
अणु
	ah->tx_घातer[0] = rate_array[ALL_TARGET_LEGACY_1L_5L];
	ah->tx_घातer[1] = rate_array[ALL_TARGET_LEGACY_1L_5L];
	ah->tx_घातer[2] = min(rate_array[ALL_TARGET_LEGACY_1L_5L],
			      rate_array[ALL_TARGET_LEGACY_5S]);
	ah->tx_घातer[3] = min(rate_array[ALL_TARGET_LEGACY_11L],
			      rate_array[ALL_TARGET_LEGACY_11S]);
पूर्ण

अटल व्योम ar9003_hw_init_txघातer_ofdm(काष्ठा ath_hw *ah, u8 *rate_array,
					पूर्णांक offset)
अणु
	पूर्णांक i, j;

	क्रम (i = offset; i < offset + AR9300_OFDM_RATES; i++) अणु
		/* OFDM rate to घातer table idx */
		j = ofdm2pwr[i - offset];
		ah->tx_घातer[i] = rate_array[j];
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_init_txघातer_ht(काष्ठा ath_hw *ah, u8 *rate_array,
				      पूर्णांक ss_offset, पूर्णांक ds_offset,
				      पूर्णांक ts_offset, bool is_40)
अणु
	पूर्णांक i, j, mcs_idx = 0;
	स्थिर u8 *mcs2pwr = (is_40) ? mcs2pwr_ht40 : mcs2pwr_ht20;

	क्रम (i = ss_offset; i < ss_offset + AR9300_HT_SS_RATES; i++) अणु
		j = mcs2pwr[mcs_idx];
		ah->tx_घातer[i] = rate_array[j];
		mcs_idx++;
	पूर्ण

	क्रम (i = ds_offset; i < ds_offset + AR9300_HT_DS_RATES; i++) अणु
		j = mcs2pwr[mcs_idx];
		ah->tx_घातer[i] = rate_array[j];
		mcs_idx++;
	पूर्ण

	क्रम (i = ts_offset; i < ts_offset + AR9300_HT_TS_RATES; i++) अणु
		j = mcs2pwr[mcs_idx];
		ah->tx_घातer[i] = rate_array[j];
		mcs_idx++;
	पूर्ण
पूर्ण

अटल व्योम ar9003_hw_init_txघातer_stbc(काष्ठा ath_hw *ah, पूर्णांक ss_offset,
					पूर्णांक ds_offset, पूर्णांक ts_offset)
अणु
	स_नकल(&ah->tx_घातer_stbc[ss_offset], &ah->tx_घातer[ss_offset],
	       AR9300_HT_SS_RATES);
	स_नकल(&ah->tx_घातer_stbc[ds_offset], &ah->tx_घातer[ds_offset],
	       AR9300_HT_DS_RATES);
	स_नकल(&ah->tx_घातer_stbc[ts_offset], &ah->tx_घातer[ts_offset],
	       AR9300_HT_TS_RATES);
पूर्ण

व्योम ar9003_hw_init_rate_txघातer(काष्ठा ath_hw *ah, u8 *rate_array,
				 काष्ठा ath9k_channel *chan)
अणु
	अगर (IS_CHAN_5GHZ(chan)) अणु
		ar9003_hw_init_txघातer_ofdm(ah, rate_array,
					    AR9300_11NA_OFDM_SHIFT);
		अगर (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) अणु
			ar9003_hw_init_txघातer_ht(ah, rate_array,
						  AR9300_11NA_HT_SS_SHIFT,
						  AR9300_11NA_HT_DS_SHIFT,
						  AR9300_11NA_HT_TS_SHIFT,
						  IS_CHAN_HT40(chan));
			ar9003_hw_init_txघातer_stbc(ah,
						    AR9300_11NA_HT_SS_SHIFT,
						    AR9300_11NA_HT_DS_SHIFT,
						    AR9300_11NA_HT_TS_SHIFT);
		पूर्ण
	पूर्ण अन्यथा अणु
		ar9003_hw_init_txघातer_cck(ah, rate_array);
		ar9003_hw_init_txघातer_ofdm(ah, rate_array,
					    AR9300_11NG_OFDM_SHIFT);
		अगर (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) अणु
			ar9003_hw_init_txघातer_ht(ah, rate_array,
						  AR9300_11NG_HT_SS_SHIFT,
						  AR9300_11NG_HT_DS_SHIFT,
						  AR9300_11NG_HT_TS_SHIFT,
						  IS_CHAN_HT40(chan));
			ar9003_hw_init_txघातer_stbc(ah,
						    AR9300_11NG_HT_SS_SHIFT,
						    AR9300_11NG_HT_DS_SHIFT,
						    AR9300_11NG_HT_TS_SHIFT);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ar9003_hw_attach_phy_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_निजी_ops *priv_ops = ath9k_hw_निजी_ops(ah);
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(ah);
	अटल स्थिर u32 ar9300_cca_regs[6] = अणु
		AR_PHY_CCA_0,
		AR_PHY_CCA_1,
		AR_PHY_CCA_2,
		AR_PHY_EXT_CCA,
		AR_PHY_EXT_CCA_1,
		AR_PHY_EXT_CCA_2,
	पूर्ण;

	priv_ops->rf_set_freq = ar9003_hw_set_channel;
	priv_ops->spur_mitigate_freq = ar9003_hw_spur_mitigate;

	अगर (AR_SREV_9340(ah) || AR_SREV_9550(ah) || AR_SREV_9531(ah) ||
	    AR_SREV_9561(ah))
		priv_ops->compute_pll_control = ar9003_hw_compute_pll_control_soc;
	अन्यथा
		priv_ops->compute_pll_control = ar9003_hw_compute_pll_control;

	priv_ops->set_channel_regs = ar9003_hw_set_channel_regs;
	priv_ops->init_bb = ar9003_hw_init_bb;
	priv_ops->process_ini = ar9003_hw_process_ini;
	priv_ops->set_rभ_शेषe = ar9003_hw_set_rभ_शेषe;
	priv_ops->mark_phy_inactive = ar9003_hw_mark_phy_inactive;
	priv_ops->set_delta_slope = ar9003_hw_set_delta_slope;
	priv_ops->rfbus_req = ar9003_hw_rfbus_req;
	priv_ops->rfbus_करोne = ar9003_hw_rfbus_करोne;
	priv_ops->ani_control = ar9003_hw_ani_control;
	priv_ops->करो_getnf = ar9003_hw_करो_getnf;
	priv_ops->ani_cache_ini_regs = ar9003_hw_ani_cache_ini_regs;
	priv_ops->set_radar_params = ar9003_hw_set_radar_params;
	priv_ops->fast_chan_change = ar9003_hw_fast_chan_change;

	ops->antभाग_comb_conf_get = ar9003_hw_antभाग_comb_conf_get;
	ops->antभाग_comb_conf_set = ar9003_hw_antभाग_comb_conf_set;
	ops->spectral_scan_config = ar9003_hw_spectral_scan_config;
	ops->spectral_scan_trigger = ar9003_hw_spectral_scan_trigger;
	ops->spectral_scan_रुको = ar9003_hw_spectral_scan_रुको;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	ops->set_bt_ant_भागersity = ar9003_hw_set_bt_ant_भागersity;
#पूर्ण_अगर
	ops->tx99_start = ar9003_hw_tx99_start;
	ops->tx99_stop = ar9003_hw_tx99_stop;
	ops->tx99_set_txघातer = ar9003_hw_tx99_set_txघातer;

	ar9003_hw_set_nf_limits(ah);
	ar9003_hw_set_radar_conf(ah);
	स_नकल(ah->nf_regs, ar9300_cca_regs, माप(ah->nf_regs));
पूर्ण

/*
 * Baseband Watchकरोg signatures:
 *
 * 0x04000539: BB hang when operating in HT40 DFS Channel.
 *             Full chip reset is not required, but a recovery
 *             mechanism is needed.
 *
 * 0x1300000a: Related to CAC deafness.
 *             Chip reset is not required.
 *
 * 0x0400000a: Related to CAC deafness.
 *             Full chip reset is required.
 *
 * 0x04000b09: RX state machine माला_लो पूर्णांकo an illegal state
 *             when a packet with unsupported rate is received.
 *             Full chip reset is required and PHY_RESTART has
 *             to be disabled.
 *
 * 0x04000409: Packet stuck on receive.
 *             Full chip reset is required क्रम all chips except
 *	       AR9340, AR9531 and AR9561.
 */

/*
 * ar9003_hw_bb_watchकरोg_check(): Returns true अगर a chip reset is required.
 */
bool ar9003_hw_bb_watchकरोg_check(काष्ठा ath_hw *ah)
अणु
	u32 val;

	चयन(ah->bb_watchकरोg_last_status) अणु
	हाल 0x04000539:
		val = REG_READ(ah, AR_PHY_RADAR_0);
		val &= (~AR_PHY_RADAR_0_FIRPWR);
		val |= SM(0x7f, AR_PHY_RADAR_0_FIRPWR);
		REG_WRITE(ah, AR_PHY_RADAR_0, val);
		udelay(1);
		val = REG_READ(ah, AR_PHY_RADAR_0);
		val &= ~AR_PHY_RADAR_0_FIRPWR;
		val |= SM(AR9300_DFS_FIRPWR, AR_PHY_RADAR_0_FIRPWR);
		REG_WRITE(ah, AR_PHY_RADAR_0, val);

		वापस false;
	हाल 0x1300000a:
		वापस false;
	हाल 0x0400000a:
	हाल 0x04000b09:
		वापस true;
	हाल 0x04000409:
		अगर (AR_SREV_9340(ah) || AR_SREV_9531(ah) || AR_SREV_9561(ah))
			वापस false;
		अन्यथा
			वापस true;
	शेष:
		/*
		 * For any other unknown signatures, करो a
		 * full chip reset.
		 */
		वापस true;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ar9003_hw_bb_watchकरोg_check);

व्योम ar9003_hw_bb_watchकरोg_config(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 idle_पंचांगo_ms = ah->bb_watchकरोg_समयout_ms;
	u32 val, idle_count;

	अगर (!idle_पंचांगo_ms) अणु
		/* disable IRQ, disable chip-reset क्रम BB panic */
		REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_2,
			  REG_READ(ah, AR_PHY_WATCHDOG_CTL_2) &
			  ~(AR_PHY_WATCHDOG_RST_ENABLE |
			    AR_PHY_WATCHDOG_IRQ_ENABLE));

		/* disable watchकरोg in non-IDLE mode, disable in IDLE mode */
		REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_1,
			  REG_READ(ah, AR_PHY_WATCHDOG_CTL_1) &
			  ~(AR_PHY_WATCHDOG_NON_IDLE_ENABLE |
			    AR_PHY_WATCHDOG_IDLE_ENABLE));

		ath_dbg(common, RESET, "Disabled BB Watchdog\n");
		वापस;
	पूर्ण

	/* enable IRQ, disable chip-reset क्रम BB watchकरोg */
	val = REG_READ(ah, AR_PHY_WATCHDOG_CTL_2) & AR_PHY_WATCHDOG_CNTL2_MASK;
	REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_2,
		  (val | AR_PHY_WATCHDOG_IRQ_ENABLE) &
		  ~AR_PHY_WATCHDOG_RST_ENABLE);

	/* bound limit to 10 secs */
	अगर (idle_पंचांगo_ms > 10000)
		idle_पंचांगo_ms = 10000;

	/*
	 * The समय unit क्रम watchकरोg event is 2^15 44/88MHz cycles.
	 *
	 * For HT20 we have a समय unit of 2^15/44 MHz = .74 ms per tick
	 * For HT40 we have a समय unit of 2^15/88 MHz = .37 ms per tick
	 *
	 * Given we use fast घड़ी now in 5 GHz, these समय units should
	 * be common क्रम both 2 GHz and 5 GHz.
	 */
	idle_count = (100 * idle_पंचांगo_ms) / 74;
	अगर (ah->curchan && IS_CHAN_HT40(ah->curchan))
		idle_count = (100 * idle_पंचांगo_ms) / 37;

	/*
	 * enable watchकरोg in non-IDLE mode, disable in IDLE mode,
	 * set idle समय-out.
	 */
	REG_WRITE(ah, AR_PHY_WATCHDOG_CTL_1,
		  AR_PHY_WATCHDOG_NON_IDLE_ENABLE |
		  AR_PHY_WATCHDOG_IDLE_MASK |
		  (AR_PHY_WATCHDOG_NON_IDLE_MASK & (idle_count << 2)));

	ath_dbg(common, RESET, "Enabled BB Watchdog timeout (%u ms)\n",
		idle_पंचांगo_ms);
पूर्ण

व्योम ar9003_hw_bb_watchकरोg_पढ़ो(काष्ठा ath_hw *ah)
अणु
	/*
	 * we want to aव्योम prपूर्णांकing in ISR context so we save the
	 * watchकरोg status to be prपूर्णांकed later in bottom half context.
	 */
	ah->bb_watchकरोg_last_status = REG_READ(ah, AR_PHY_WATCHDOG_STATUS);

	/*
	 * the watchकरोg समयr should reset on status पढ़ो but to be sure
	 * sure we ग_लिखो 0 to the watchकरोg status bit.
	 */
	REG_WRITE(ah, AR_PHY_WATCHDOG_STATUS,
		  ah->bb_watchकरोg_last_status & ~AR_PHY_WATCHDOG_STATUS_CLR);
पूर्ण

व्योम ar9003_hw_bb_watchकरोg_dbg_info(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 status;

	अगर (likely(!(common->debug_mask & ATH_DBG_RESET)))
		वापस;

	status = ah->bb_watchकरोg_last_status;
	ath_dbg(common, RESET,
		"\n==== BB update: BB status=0x%08x ====\n", status);
	ath_dbg(common, RESET,
		"** BB state: wd=%u det=%u rdar=%u rOFDM=%d rCCK=%u tOFDM=%u tCCK=%u agc=%u src=%u **\n",
		MS(status, AR_PHY_WATCHDOG_INFO),
		MS(status, AR_PHY_WATCHDOG_DET_HANG),
		MS(status, AR_PHY_WATCHDOG_RADAR_SM),
		MS(status, AR_PHY_WATCHDOG_RX_OFDM_SM),
		MS(status, AR_PHY_WATCHDOG_RX_CCK_SM),
		MS(status, AR_PHY_WATCHDOG_TX_OFDM_SM),
		MS(status, AR_PHY_WATCHDOG_TX_CCK_SM),
		MS(status, AR_PHY_WATCHDOG_AGC_SM),
		MS(status, AR_PHY_WATCHDOG_SRCH_SM));

	ath_dbg(common, RESET, "** BB WD cntl: cntl1=0x%08x cntl2=0x%08x **\n",
		REG_READ(ah, AR_PHY_WATCHDOG_CTL_1),
		REG_READ(ah, AR_PHY_WATCHDOG_CTL_2));
	ath_dbg(common, RESET, "** BB mode: BB_gen_controls=0x%08x **\n",
		REG_READ(ah, AR_PHY_GEN_CTRL));

#घोषणा PCT(_field) (common->cc_survey._field * 100 / common->cc_survey.cycles)
	अगर (common->cc_survey.cycles)
		ath_dbg(common, RESET,
			"** BB busy times: rx_clear=%d%%, rx_frame=%d%%, tx_frame=%d%% **\n",
			PCT(rx_busy), PCT(rx_frame), PCT(tx_frame));

	ath_dbg(common, RESET, "==== BB update: done ====\n\n");
पूर्ण
EXPORT_SYMBOL(ar9003_hw_bb_watchकरोg_dbg_info);

व्योम ar9003_hw_disable_phy_restart(काष्ठा ath_hw *ah)
अणु
	u8 result;
	u32 val;

	/* While receiving unsupported rate frame rx state machine
	 * माला_लो पूर्णांकo a state 0xb and अगर phy_restart happens in that
	 * state, BB would go hang. If RXSM is in 0xb state after
	 * first bb panic, ensure to disable the phy_restart.
	 */
	result = MS(ah->bb_watchकरोg_last_status, AR_PHY_WATCHDOG_RX_OFDM_SM);

	अगर ((result == 0xb) || ah->bb_hang_rx_ofdm) अणु
		ah->bb_hang_rx_ofdm = true;
		val = REG_READ(ah, AR_PHY_RESTART);
		val &= ~AR_PHY_RESTART_ENA;
		REG_WRITE(ah, AR_PHY_RESTART, val);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ar9003_hw_disable_phy_restart);
