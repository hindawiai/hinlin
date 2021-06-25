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
#समावेश "../regd.h"
#समावेश "ar9002_phy.h"

/* All code below is क्रम AR5008, AR9001, AR9002 */

#घोषणा AR5008_OFDM_RATES		8
#घोषणा AR5008_HT_SS_RATES		8
#घोषणा AR5008_HT_DS_RATES		8

#घोषणा AR5008_HT20_SHIFT		16
#घोषणा AR5008_HT40_SHIFT		24

#घोषणा AR5008_11NA_OFDM_SHIFT		0
#घोषणा AR5008_11NA_HT_SS_SHIFT		8
#घोषणा AR5008_11NA_HT_DS_SHIFT		16

#घोषणा AR5008_11NG_OFDM_SHIFT		4
#घोषणा AR5008_11NG_HT_SS_SHIFT		12
#घोषणा AR5008_11NG_HT_DS_SHIFT		20

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

अटल स्थिर u32 ar5416Bank0[][2] = अणु
	/* Addr      allmodes  */
	अणु0x000098b0, 0x1e5795e5पूर्ण,
	अणु0x000098e0, 0x02008020पूर्ण,
पूर्ण;

अटल स्थिर u32 ar5416Bank1[][2] = अणु
	/* Addr      allmodes  */
	अणु0x000098b0, 0x02108421पूर्ण,
	अणु0x000098ec, 0x00000008पूर्ण,
पूर्ण;

अटल स्थिर u32 ar5416Bank2[][2] = अणु
	/* Addr      allmodes  */
	अणु0x000098b0, 0x0e73ff17पूर्ण,
	अणु0x000098e0, 0x00000420पूर्ण,
पूर्ण;

अटल स्थिर u32 ar5416Bank3[][3] = अणु
	/* Addr      5G          2G        */
	अणु0x000098f0, 0x01400018, 0x01c00018पूर्ण,
पूर्ण;

अटल स्थिर u32 ar5416Bank7[][2] = अणु
	/* Addr      allmodes  */
	अणु0x0000989c, 0x00000500पूर्ण,
	अणु0x0000989c, 0x00000800पूर्ण,
	अणु0x000098cc, 0x0000000eपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ar5416IniArray bank0 = STATIC_INI_ARRAY(ar5416Bank0);
अटल स्थिर काष्ठा ar5416IniArray bank1 = STATIC_INI_ARRAY(ar5416Bank1);
अटल स्थिर काष्ठा ar5416IniArray bank2 = STATIC_INI_ARRAY(ar5416Bank2);
अटल स्थिर काष्ठा ar5416IniArray bank3 = STATIC_INI_ARRAY(ar5416Bank3);
अटल स्थिर काष्ठा ar5416IniArray bank7 = STATIC_INI_ARRAY(ar5416Bank7);

अटल व्योम ar5008_ग_लिखो_bank6(काष्ठा ath_hw *ah, अचिन्हित पूर्णांक *ग_लिखोcnt)
अणु
	काष्ठा ar5416IniArray *array = &ah->iniBank6;
	u32 *data = ah->analogBank6Data;
	पूर्णांक r;

	ENABLE_REGWRITE_BUFFER(ah);

	क्रम (r = 0; r < array->ia_rows; r++) अणु
		REG_WRITE(ah, INI_RA(array, r, 0), data[r]);
		DO_DELAY(*ग_लिखोcnt);
	पूर्ण

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

/*
 * ar5008_hw_phy_modअगरy_rx_buffer() - perक्रमm analog swizzling of parameters
 *
 * Perक्रमms analog "swizzling" of parameters पूर्णांकo their location.
 * Used on बाह्यal AR2133/AR5133 radios.
 */
अटल व्योम ar5008_hw_phy_modअगरy_rx_buffer(u32 *rfBuf, u32 reg32,
					   u32 numBits, u32 firstBit,
					   u32 column)
अणु
	u32 पंचांगp32, mask, arrayEntry, lastBit;
	पूर्णांक32_t bitPosition, bitsLeft;

	पंचांगp32 = ath9k_hw_reverse_bits(reg32, numBits);
	arrayEntry = (firstBit - 1) / 8;
	bitPosition = (firstBit - 1) % 8;
	bitsLeft = numBits;
	जबतक (bitsLeft > 0) अणु
		lastBit = (bitPosition + bitsLeft > 8) ?
		    8 : bitPosition + bitsLeft;
		mask = (((1 << lastBit) - 1) ^ ((1 << bitPosition) - 1)) <<
		    (column * 8);
		rfBuf[arrayEntry] &= ~mask;
		rfBuf[arrayEntry] |= ((पंचांगp32 << bitPosition) <<
				      (column * 8)) & mask;
		bitsLeft -= 8 - bitPosition;
		पंचांगp32 = पंचांगp32 >> (8 - bitPosition);
		bitPosition = 0;
		arrayEntry++;
	पूर्ण
पूर्ण

/*
 * Fix on 2.4 GHz band क्रम orientation sensitivity issue by increasing
 * rf_pwd_icsynभाग.
 *
 * Theoretical Rules:
 *   अगर 2 GHz band
 *      अगर क्रमceBiasAuto
 *         अगर synth_freq < 2412
 *            bias = 0
 *         अन्यथा अगर 2412 <= synth_freq <= 2422
 *            bias = 1
 *         अन्यथा // synth_freq > 2422
 *            bias = 2
 *      अन्यथा अगर क्रमceBias > 0
 *         bias = क्रमceBias & 7
 *      अन्यथा
 *         no change, use value from ini file
 *   अन्यथा
 *      no change, invalid band
 *
 *  1st Mod:
 *    2422 also uses value of 2
 *    <approved>
 *
 *  2nd Mod:
 *    Less than 2412 uses value of 0, 2412 and above uses value of 2
 */
अटल व्योम ar5008_hw_क्रमce_bias(काष्ठा ath_hw *ah, u16 synth_freq)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 पंचांगp_reg;
	पूर्णांक reg_ग_लिखोs = 0;
	u32 new_bias = 0;

	अगर (!AR_SREV_5416(ah) || synth_freq >= 3000)
		वापस;

	BUG_ON(AR_SREV_9280_20_OR_LATER(ah));

	अगर (synth_freq < 2412)
		new_bias = 0;
	अन्यथा अगर (synth_freq < 2422)
		new_bias = 1;
	अन्यथा
		new_bias = 2;

	/* pre-reverse this field */
	पंचांगp_reg = ath9k_hw_reverse_bits(new_bias, 3);

	ath_dbg(common, CONFIG, "Force rf_pwd_icsyndiv to %1d on %4d\n",
		new_bias, synth_freq);

	/* swizzle rf_pwd_icsynभाग */
	ar5008_hw_phy_modअगरy_rx_buffer(ah->analogBank6Data, पंचांगp_reg, 3, 181, 3);

	/* ग_लिखो Bank 6 with new params */
	ar5008_ग_लिखो_bank6(ah, &reg_ग_लिखोs);
पूर्ण

/*
 * ar5008_hw_set_channel - tune to a channel on the बाह्यal AR2133/AR5133 radios
 *
 * For the बाह्यal AR2133/AR5133 radios, takes the MHz channel value and set
 * the channel value. Assumes ग_लिखोs enabled to analog bus and bank6 रेजिस्टर
 * cache in ah->analogBank6Data.
 */
अटल पूर्णांक ar5008_hw_set_channel(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 channelSel = 0;
	u32 bModeSynth = 0;
	u32 aModeRefSel = 0;
	u32 reg32 = 0;
	u16 freq;
	काष्ठा chan_centers centers;

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	freq = centers.synth_center;

	अगर (freq < 4800) अणु
		u32 txctl;

		अगर (((freq - 2192) % 5) == 0) अणु
			channelSel = ((freq - 672) * 2 - 3040) / 10;
			bModeSynth = 0;
		पूर्ण अन्यथा अगर (((freq - 2224) % 5) == 0) अणु
			channelSel = ((freq - 704) * 2 - 3040) / 10;
			bModeSynth = 1;
		पूर्ण अन्यथा अणु
			ath_err(common, "Invalid channel %u MHz\n", freq);
			वापस -EINVAL;
		पूर्ण

		channelSel = (channelSel << 2) & 0xff;
		channelSel = ath9k_hw_reverse_bits(channelSel, 8);

		txctl = REG_READ(ah, AR_PHY_CCK_TX_CTRL);
		अगर (freq == 2484) अणु

			REG_WRITE(ah, AR_PHY_CCK_TX_CTRL,
				  txctl | AR_PHY_CCK_TX_CTRL_JAPAN);
		पूर्ण अन्यथा अणु
			REG_WRITE(ah, AR_PHY_CCK_TX_CTRL,
				  txctl & ~AR_PHY_CCK_TX_CTRL_JAPAN);
		पूर्ण

	पूर्ण अन्यथा अगर ((freq % 20) == 0 && freq >= 5120) अणु
		channelSel =
		    ath9k_hw_reverse_bits(((freq - 4800) / 20 << 2), 8);
		aModeRefSel = ath9k_hw_reverse_bits(1, 2);
	पूर्ण अन्यथा अगर ((freq % 10) == 0) अणु
		channelSel =
		    ath9k_hw_reverse_bits(((freq - 4800) / 10 << 1), 8);
		अगर (AR_SREV_9100(ah) || AR_SREV_9160_10_OR_LATER(ah))
			aModeRefSel = ath9k_hw_reverse_bits(2, 2);
		अन्यथा
			aModeRefSel = ath9k_hw_reverse_bits(1, 2);
	पूर्ण अन्यथा अगर ((freq % 5) == 0) अणु
		channelSel = ath9k_hw_reverse_bits((freq - 4800) / 5, 8);
		aModeRefSel = ath9k_hw_reverse_bits(1, 2);
	पूर्ण अन्यथा अणु
		ath_err(common, "Invalid channel %u MHz\n", freq);
		वापस -EINVAL;
	पूर्ण

	ar5008_hw_क्रमce_bias(ah, freq);

	reg32 =
	    (channelSel << 8) | (aModeRefSel << 2) | (bModeSynth << 1) |
	    (1 << 5) | 0x1;

	REG_WRITE(ah, AR_PHY(0x37), reg32);

	ah->curchan = chan;

	वापस 0;
पूर्ण

व्योम ar5008_hw_cmn_spur_mitigate(काष्ठा ath_hw *ah,
			  काष्ठा ath9k_channel *chan, पूर्णांक bin)
अणु
	पूर्णांक cur_bin;
	पूर्णांक upper, lower, cur_vit_mask;
	पूर्णांक i;
	पूर्णांक8_t mask_m[123] = अणु0पूर्ण;
	पूर्णांक8_t mask_p[123] = अणु0पूर्ण;
	पूर्णांक8_t mask_amt;
	पूर्णांक पंचांगp_mask;
	अटल स्थिर पूर्णांक pilot_mask_reg[4] = अणु
		AR_PHY_TIMING7, AR_PHY_TIMING8,
		AR_PHY_PILOT_MASK_01_30, AR_PHY_PILOT_MASK_31_60
	पूर्ण;
	अटल स्थिर पूर्णांक chan_mask_reg[4] = अणु
		AR_PHY_TIMING9, AR_PHY_TIMING10,
		AR_PHY_CHANNEL_MASK_01_30, AR_PHY_CHANNEL_MASK_31_60
	पूर्ण;
	अटल स्थिर पूर्णांक inc[4] = अणु 0, 100, 0, 0 पूर्ण;

	cur_bin = -6000;
	upper = bin + 100;
	lower = bin - 100;

	क्रम (i = 0; i < 4; i++) अणु
		पूर्णांक pilot_mask = 0;
		पूर्णांक chan_mask = 0;
		पूर्णांक bp = 0;

		क्रम (bp = 0; bp < 30; bp++) अणु
			अगर ((cur_bin > lower) && (cur_bin < upper)) अणु
				pilot_mask = pilot_mask | 0x1 << bp;
				chan_mask = chan_mask | 0x1 << bp;
			पूर्ण
			cur_bin += 100;
		पूर्ण
		cur_bin += inc[i];
		REG_WRITE(ah, pilot_mask_reg[i], pilot_mask);
		REG_WRITE(ah, chan_mask_reg[i], chan_mask);
	पूर्ण

	cur_vit_mask = 6100;
	upper = bin + 120;
	lower = bin - 120;

	क्रम (i = 0; i < ARRAY_SIZE(mask_m); i++) अणु
		अगर ((cur_vit_mask > lower) && (cur_vit_mask < upper)) अणु
			/* workaround क्रम gcc bug #37014 */
			अस्थिर पूर्णांक पंचांगp_v = असल(cur_vit_mask - bin);

			अगर (पंचांगp_v < 75)
				mask_amt = 1;
			अन्यथा
				mask_amt = 0;
			अगर (cur_vit_mask < 0)
				mask_m[असल(cur_vit_mask / 100)] = mask_amt;
			अन्यथा
				mask_p[cur_vit_mask / 100] = mask_amt;
		पूर्ण
		cur_vit_mask -= 100;
	पूर्ण

	पंचांगp_mask = (mask_m[46] << 30) | (mask_m[47] << 28)
		| (mask_m[48] << 26) | (mask_m[49] << 24)
		| (mask_m[50] << 22) | (mask_m[51] << 20)
		| (mask_m[52] << 18) | (mask_m[53] << 16)
		| (mask_m[54] << 14) | (mask_m[55] << 12)
		| (mask_m[56] << 10) | (mask_m[57] << 8)
		| (mask_m[58] << 6) | (mask_m[59] << 4)
		| (mask_m[60] << 2) | (mask_m[61] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK_1, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_VIT_MASK2_M_46_61, पंचांगp_mask);

	पंचांगp_mask = (mask_m[31] << 28)
		| (mask_m[32] << 26) | (mask_m[33] << 24)
		| (mask_m[34] << 22) | (mask_m[35] << 20)
		| (mask_m[36] << 18) | (mask_m[37] << 16)
		| (mask_m[48] << 14) | (mask_m[39] << 12)
		| (mask_m[40] << 10) | (mask_m[41] << 8)
		| (mask_m[42] << 6) | (mask_m[43] << 4)
		| (mask_m[44] << 2) | (mask_m[45] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK_2, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_M_31_45, पंचांगp_mask);

	पंचांगp_mask = (mask_m[16] << 30) | (mask_m[16] << 28)
		| (mask_m[18] << 26) | (mask_m[18] << 24)
		| (mask_m[20] << 22) | (mask_m[20] << 20)
		| (mask_m[22] << 18) | (mask_m[22] << 16)
		| (mask_m[24] << 14) | (mask_m[24] << 12)
		| (mask_m[25] << 10) | (mask_m[26] << 8)
		| (mask_m[27] << 6) | (mask_m[28] << 4)
		| (mask_m[29] << 2) | (mask_m[30] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK_3, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_M_16_30, पंचांगp_mask);

	पंचांगp_mask = (mask_m[0] << 30) | (mask_m[1] << 28)
		| (mask_m[2] << 26) | (mask_m[3] << 24)
		| (mask_m[4] << 22) | (mask_m[5] << 20)
		| (mask_m[6] << 18) | (mask_m[7] << 16)
		| (mask_m[8] << 14) | (mask_m[9] << 12)
		| (mask_m[10] << 10) | (mask_m[11] << 8)
		| (mask_m[12] << 6) | (mask_m[13] << 4)
		| (mask_m[14] << 2) | (mask_m[15] << 0);
	REG_WRITE(ah, AR_PHY_MASK_CTL, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_M_00_15, पंचांगp_mask);

	पंचांगp_mask = (mask_p[15] << 28)
		| (mask_p[14] << 26) | (mask_p[13] << 24)
		| (mask_p[12] << 22) | (mask_p[11] << 20)
		| (mask_p[10] << 18) | (mask_p[9] << 16)
		| (mask_p[8] << 14) | (mask_p[7] << 12)
		| (mask_p[6] << 10) | (mask_p[5] << 8)
		| (mask_p[4] << 6) | (mask_p[3] << 4)
		| (mask_p[2] << 2) | (mask_p[1] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_1, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_15_01, पंचांगp_mask);

	पंचांगp_mask = (mask_p[30] << 28)
		| (mask_p[29] << 26) | (mask_p[28] << 24)
		| (mask_p[27] << 22) | (mask_p[26] << 20)
		| (mask_p[25] << 18) | (mask_p[24] << 16)
		| (mask_p[23] << 14) | (mask_p[22] << 12)
		| (mask_p[21] << 10) | (mask_p[20] << 8)
		| (mask_p[19] << 6) | (mask_p[18] << 4)
		| (mask_p[17] << 2) | (mask_p[16] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_2, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_30_16, पंचांगp_mask);

	पंचांगp_mask = (mask_p[45] << 28)
		| (mask_p[44] << 26) | (mask_p[43] << 24)
		| (mask_p[42] << 22) | (mask_p[41] << 20)
		| (mask_p[40] << 18) | (mask_p[39] << 16)
		| (mask_p[38] << 14) | (mask_p[37] << 12)
		| (mask_p[36] << 10) | (mask_p[35] << 8)
		| (mask_p[34] << 6) | (mask_p[33] << 4)
		| (mask_p[32] << 2) | (mask_p[31] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_3, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_45_31, पंचांगp_mask);

	पंचांगp_mask = (mask_p[61] << 30) | (mask_p[60] << 28)
		| (mask_p[59] << 26) | (mask_p[58] << 24)
		| (mask_p[57] << 22) | (mask_p[56] << 20)
		| (mask_p[55] << 18) | (mask_p[54] << 16)
		| (mask_p[53] << 14) | (mask_p[52] << 12)
		| (mask_p[51] << 10) | (mask_p[50] << 8)
		| (mask_p[49] << 6) | (mask_p[48] << 4)
		| (mask_p[47] << 2) | (mask_p[46] << 0);
	REG_WRITE(ah, AR_PHY_BIN_MASK2_4, पंचांगp_mask);
	REG_WRITE(ah, AR_PHY_MASK2_P_61_45, पंचांगp_mask);
पूर्ण

/*
 * ar5008_hw_spur_mitigate - convert baseband spur frequency क्रम बाह्यal radios
 *
 * For non single-chip solutions. Converts to baseband spur frequency given the
 * input channel frequency and compute रेजिस्टर settings below.
 */
अटल व्योम ar5008_hw_spur_mitigate(काष्ठा ath_hw *ah,
				    काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक bb_spur = AR_NO_SPUR;
	पूर्णांक bin;
	पूर्णांक spur_freq_sd;
	पूर्णांक spur_delta_phase;
	पूर्णांक denominator;
	पूर्णांक पंचांगp, new;
	पूर्णांक i;

	पूर्णांक cur_bb_spur;
	bool is2GHz = IS_CHAN_2GHZ(chan);

	क्रम (i = 0; i < AR_EEPROM_MODAL_SPURS; i++) अणु
		cur_bb_spur = ah->eep_ops->get_spur_channel(ah, i, is2GHz);
		अगर (AR_NO_SPUR == cur_bb_spur)
			अवरोध;
		cur_bb_spur = cur_bb_spur - (chan->channel * 10);
		अगर ((cur_bb_spur > -95) && (cur_bb_spur < 95)) अणु
			bb_spur = cur_bb_spur;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (AR_NO_SPUR == bb_spur)
		वापस;

	bin = bb_spur * 32;

	पंचांगp = REG_READ(ah, AR_PHY_TIMING_CTRL4(0));
	new = पंचांगp | (AR_PHY_TIMING_CTRL4_ENABLE_SPUR_RSSI |
		     AR_PHY_TIMING_CTRL4_ENABLE_SPUR_FILTER |
		     AR_PHY_TIMING_CTRL4_ENABLE_CHAN_MASK |
		     AR_PHY_TIMING_CTRL4_ENABLE_PILOT_MASK);

	REG_WRITE(ah, AR_PHY_TIMING_CTRL4(0), new);

	new = (AR_PHY_SPUR_REG_MASK_RATE_CNTL |
	       AR_PHY_SPUR_REG_ENABLE_MASK_PPM |
	       AR_PHY_SPUR_REG_MASK_RATE_SELECT |
	       AR_PHY_SPUR_REG_ENABLE_VIT_SPUR_RSSI |
	       SM(SPUR_RSSI_THRESH, AR_PHY_SPUR_REG_SPUR_RSSI_THRESH));
	REG_WRITE(ah, AR_PHY_SPUR_REG, new);

	spur_delta_phase = ((bb_spur * 524288) / 100) &
		AR_PHY_TIMING11_SPUR_DELTA_PHASE;

	denominator = IS_CHAN_2GHZ(chan) ? 440 : 400;
	spur_freq_sd = ((bb_spur * 2048) / denominator) & 0x3ff;

	new = (AR_PHY_TIMING11_USE_SPUR_IN_AGC |
	       SM(spur_freq_sd, AR_PHY_TIMING11_SPUR_FREQ_SD) |
	       SM(spur_delta_phase, AR_PHY_TIMING11_SPUR_DELTA_PHASE));
	REG_WRITE(ah, AR_PHY_TIMING11, new);

	ar5008_hw_cmn_spur_mitigate(ah, chan, bin);
पूर्ण

/**
 * ar5008_hw_rf_alloc_ext_banks - allocates banks क्रम बाह्यal radio programming
 * @ah: atheros hardware काष्ठाure
 *
 * Only required क्रम older devices with बाह्यal AR2133/AR5133 radios.
 */
अटल पूर्णांक ar5008_hw_rf_alloc_ext_banks(काष्ठा ath_hw *ah)
अणु
	पूर्णांक size = ah->iniBank6.ia_rows * माप(u32);

	अगर (AR_SREV_9280_20_OR_LATER(ah))
	    वापस 0;

	ah->analogBank6Data = devm_kzalloc(ah->dev, size, GFP_KERNEL);
	अगर (!ah->analogBank6Data)
		वापस -ENOMEM;

	वापस 0;
पूर्ण


/* *
 * ar5008_hw_set_rf_regs - programs rf रेजिस्टरs based on EEPROM
 * @ah: atheros hardware काष्ठाure
 * @chan:
 * @modesIndex:
 *
 * Used क्रम the बाह्यal AR2133/AR5133 radios.
 *
 * Reads the EEPROM header info from the device काष्ठाure and programs
 * all rf रेजिस्टरs. This routine requires access to the analog
 * rf device. This is not required क्रम single-chip devices.
 */
अटल bool ar5008_hw_set_rf_regs(काष्ठा ath_hw *ah,
				  काष्ठा ath9k_channel *chan,
				  u16 modesIndex)
अणु
	u32 eepMinorRev;
	u32 ob5GHz = 0, db5GHz = 0;
	u32 ob2GHz = 0, db2GHz = 0;
	पूर्णांक regWrites = 0;
	पूर्णांक i;

	/*
	 * Software करोes not need to program bank data
	 * क्रम single chip devices, that is AR9280 or anything
	 * after that.
	 */
	अगर (AR_SREV_9280_20_OR_LATER(ah))
		वापस true;

	/* Setup rf parameters */
	eepMinorRev = ah->eep_ops->get_eeprom_rev(ah);

	क्रम (i = 0; i < ah->iniBank6.ia_rows; i++)
		ah->analogBank6Data[i] = INI_RA(&ah->iniBank6, i, modesIndex);

	/* Only the 5 or 2 GHz OB/DB need to be set क्रम a mode */
	अगर (eepMinorRev >= 2) अणु
		अगर (IS_CHAN_2GHZ(chan)) अणु
			ob2GHz = ah->eep_ops->get_eeprom(ah, EEP_OB_2);
			db2GHz = ah->eep_ops->get_eeprom(ah, EEP_DB_2);
			ar5008_hw_phy_modअगरy_rx_buffer(ah->analogBank6Data,
						       ob2GHz, 3, 197, 0);
			ar5008_hw_phy_modअगरy_rx_buffer(ah->analogBank6Data,
						       db2GHz, 3, 194, 0);
		पूर्ण अन्यथा अणु
			ob5GHz = ah->eep_ops->get_eeprom(ah, EEP_OB_5);
			db5GHz = ah->eep_ops->get_eeprom(ah, EEP_DB_5);
			ar5008_hw_phy_modअगरy_rx_buffer(ah->analogBank6Data,
						       ob5GHz, 3, 203, 0);
			ar5008_hw_phy_modअगरy_rx_buffer(ah->analogBank6Data,
						       db5GHz, 3, 200, 0);
		पूर्ण
	पूर्ण

	/* Write Analog रेजिस्टरs */
	REG_WRITE_ARRAY(&bank0, 1, regWrites);
	REG_WRITE_ARRAY(&bank1, 1, regWrites);
	REG_WRITE_ARRAY(&bank2, 1, regWrites);
	REG_WRITE_ARRAY(&bank3, modesIndex, regWrites);
	ar5008_ग_लिखो_bank6(ah, &regWrites);
	REG_WRITE_ARRAY(&bank7, 1, regWrites);

	वापस true;
पूर्ण

अटल व्योम ar5008_hw_init_bb(काष्ठा ath_hw *ah,
			      काष्ठा ath9k_channel *chan)
अणु
	u32 synthDelay;

	synthDelay = REG_READ(ah, AR_PHY_RX_DELAY) & AR_PHY_RX_DELAY_DELAY;

	REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);

	ath9k_hw_synth_delay(ah, chan, synthDelay);
पूर्ण

अटल व्योम ar5008_hw_init_chain_masks(काष्ठा ath_hw *ah)
अणु
	पूर्णांक rx_chainmask, tx_chainmask;

	rx_chainmask = ah->rxchainmask;
	tx_chainmask = ah->txchainmask;


	चयन (rx_chainmask) अणु
	हाल 0x5:
		REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP,
			    AR_PHY_SWAP_ALT_CHAIN);
		fallthrough;
	हाल 0x3:
		अगर (ah->hw_version.macVersion == AR_SREV_REVISION_5416_10) अणु
			REG_WRITE(ah, AR_PHY_RX_CHAINMASK, 0x7);
			REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, 0x7);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 0x1:
	हाल 0x2:
	हाल 0x7:
		ENABLE_REGWRITE_BUFFER(ah);
		REG_WRITE(ah, AR_PHY_RX_CHAINMASK, rx_chainmask);
		REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, rx_chainmask);
		अवरोध;
	शेष:
		ENABLE_REGWRITE_BUFFER(ah);
		अवरोध;
	पूर्ण

	REG_WRITE(ah, AR_SELFGEN_MASK, tx_chainmask);

	REGWRITE_BUFFER_FLUSH(ah);

	अगर (tx_chainmask == 0x5) अणु
		REG_SET_BIT(ah, AR_PHY_ANALOG_SWAP,
			    AR_PHY_SWAP_ALT_CHAIN);
	पूर्ण
	अगर (AR_SREV_9100(ah))
		REG_WRITE(ah, AR_PHY_ANALOG_SWAP,
			  REG_READ(ah, AR_PHY_ANALOG_SWAP) | 0x00000001);
पूर्ण

अटल व्योम ar5008_hw_override_ini(काष्ठा ath_hw *ah,
				   काष्ठा ath9k_channel *chan)
अणु
	u32 val;

	/*
	 * Set the RX_ABORT and RX_DIS and clear अगर off only after
	 * RXE is set क्रम MAC. This prevents frames with corrupted
	 * descriptor status.
	 */
	REG_SET_BIT(ah, AR_DIAG_SW, (AR_DIAG_RX_DIS | AR_DIAG_RX_ABORT));

	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		/*
		 * For AR9280 and above, there is a new feature that allows
		 * Multicast search based on both MAC Address and Key ID.
		 * By शेष, this feature is enabled. But since the driver
		 * is not using this feature, we चयन it off; otherwise
		 * multicast search based on MAC addr only will fail.
		 */
		val = REG_READ(ah, AR_PCU_MISC_MODE2) &
			(~AR_ADHOC_MCAST_KEYID_ENABLE);

		अगर (!AR_SREV_9271(ah))
			val &= ~AR_PCU_MISC_MODE2_HWWAR1;

		अगर (AR_SREV_9287_11_OR_LATER(ah))
			val = val & (~AR_PCU_MISC_MODE2_HWWAR2);

		val |= AR_PCU_MISC_MODE2_CFP_IGNORE;

		REG_WRITE(ah, AR_PCU_MISC_MODE2, val);
	पूर्ण

	अगर (AR_SREV_9280_20_OR_LATER(ah))
		वापस;
	/*
	 * Disable BB घड़ी gating
	 * Necessary to aव्योम issues on AR5416 2.0
	 */
	REG_WRITE(ah, 0x9800 + (651 << 2), 0x11);

	/*
	 * Disable RIFS search on some chips to aव्योम baseband
	 * hang issues.
	 */
	अगर (AR_SREV_9100(ah) || AR_SREV_9160(ah)) अणु
		val = REG_READ(ah, AR_PHY_HEAVY_CLIP_FACTOR_RIFS);
		val &= ~AR_PHY_RIFS_INIT_DELAY;
		REG_WRITE(ah, AR_PHY_HEAVY_CLIP_FACTOR_RIFS, val);
	पूर्ण
पूर्ण

अटल व्योम ar5008_hw_set_channel_regs(काष्ठा ath_hw *ah,
				       काष्ठा ath9k_channel *chan)
अणु
	u32 phymode;
	u32 enableDacFअगरo = 0;

	अगर (AR_SREV_9285_12_OR_LATER(ah))
		enableDacFअगरo = (REG_READ(ah, AR_PHY_TURBO) &
					 AR_PHY_FC_ENABLE_DAC_FIFO);

	phymode = AR_PHY_FC_HT_EN | AR_PHY_FC_SHORT_GI_40
		| AR_PHY_FC_SINGLE_HT_LTF1 | AR_PHY_FC_WALSH | enableDacFअगरo;

	अगर (IS_CHAN_HT40(chan)) अणु
		phymode |= AR_PHY_FC_DYN2040_EN;

		अगर (IS_CHAN_HT40PLUS(chan))
			phymode |= AR_PHY_FC_DYN2040_PRI_CH;

	पूर्ण
	ENABLE_REGWRITE_BUFFER(ah);
	REG_WRITE(ah, AR_PHY_TURBO, phymode);

	/* This function करो only REG_WRITE, so
	 * we can include it to REGWRITE_BUFFER. */
	ath9k_hw_set11nmac2040(ah, chan);

	REG_WRITE(ah, AR_GTXTO, 25 << AR_GTXTO_TIMEOUT_LIMIT_S);
	REG_WRITE(ah, AR_CST, 0xF << AR_CST_TIMEOUT_LIMIT_S);

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण


अटल पूर्णांक ar5008_hw_process_ini(काष्ठा ath_hw *ah,
				 काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक i, regWrites = 0;
	u32 modesIndex, freqIndex;

	अगर (IS_CHAN_5GHZ(chan)) अणु
		freqIndex = 1;
		modesIndex = IS_CHAN_HT40(chan) ? 2 : 1;
	पूर्ण अन्यथा अणु
		freqIndex = 2;
		modesIndex = IS_CHAN_HT40(chan) ? 3 : 4;
	पूर्ण

	/*
	 * Set correct baseband to analog shअगरt setting to
	 * access analog chips.
	 */
	REG_WRITE(ah, AR_PHY(0), 0x00000007);

	/* Write ADDAC shअगरts */
	REG_WRITE(ah, AR_PHY_ADC_SERIAL_CTL, AR_PHY_SEL_EXTERNAL_RADIO);
	अगर (ah->eep_ops->set_addac)
		ah->eep_ops->set_addac(ah, chan);

	REG_WRITE_ARRAY(&ah->iniAddac, 1, regWrites);
	REG_WRITE(ah, AR_PHY_ADC_SERIAL_CTL, AR_PHY_SEL_INTERNAL_ADDAC);

	ENABLE_REGWRITE_BUFFER(ah);

	क्रम (i = 0; i < ah->iniModes.ia_rows; i++) अणु
		u32 reg = INI_RA(&ah->iniModes, i, 0);
		u32 val = INI_RA(&ah->iniModes, i, modesIndex);

		अगर (reg == AR_AN_TOP2 && ah->need_an_top2_fixup)
			val &= ~AR_AN_TOP2_PWDCLKIND;

		REG_WRITE(ah, reg, val);

		अगर (reg >= 0x7800 && reg < 0x78a0
		    && ah->config.analog_shअगरtreg
		    && (common->bus_ops->ath_bus_type != ATH_USB)) अणु
			udelay(100);
		पूर्ण

		DO_DELAY(regWrites);
	पूर्ण

	REGWRITE_BUFFER_FLUSH(ah);

	अगर (AR_SREV_9280(ah) || AR_SREV_9287_11_OR_LATER(ah))
		REG_WRITE_ARRAY(&ah->iniModesRxGain, modesIndex, regWrites);

	अगर (AR_SREV_9280(ah) || AR_SREV_9285_12_OR_LATER(ah) ||
	    AR_SREV_9287_11_OR_LATER(ah))
		REG_WRITE_ARRAY(&ah->iniModesTxGain, modesIndex, regWrites);

	अगर (AR_SREV_9271_10(ah)) अणु
		REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, AR_PHY_SPECTRAL_SCAN_ENA);
		REG_RMW_FIELD(ah, AR_PHY_RF_CTL3, AR_PHY_TX_END_TO_ADC_ON, 0xa);
	पूर्ण

	ENABLE_REGWRITE_BUFFER(ah);

	/* Write common array parameters */
	क्रम (i = 0; i < ah->iniCommon.ia_rows; i++) अणु
		u32 reg = INI_RA(&ah->iniCommon, i, 0);
		u32 val = INI_RA(&ah->iniCommon, i, 1);

		REG_WRITE(ah, reg, val);

		अगर (reg >= 0x7800 && reg < 0x78a0
		    && ah->config.analog_shअगरtreg
		    && (common->bus_ops->ath_bus_type != ATH_USB)) अणु
			udelay(100);
		पूर्ण

		DO_DELAY(regWrites);
	पूर्ण

	REGWRITE_BUFFER_FLUSH(ah);

	REG_WRITE_ARRAY(&ah->iniBB_RfGain, freqIndex, regWrites);

	अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		REG_WRITE_ARRAY(&ah->iniModesFastClock, modesIndex,
				regWrites);

	ar5008_hw_override_ini(ah, chan);
	ar5008_hw_set_channel_regs(ah, chan);
	ar5008_hw_init_chain_masks(ah);
	ath9k_olc_init(ah);
	ath9k_hw_apply_txघातer(ah, chan, false);

	/* Write analog रेजिस्टरs */
	अगर (!ath9k_hw_set_rf_regs(ah, chan, freqIndex)) अणु
		ath_err(ath9k_hw_common(ah), "ar5416SetRfRegs failed\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ar5008_hw_set_rभ_शेषe(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	u32 rfMode = 0;

	अगर (chan == शून्य)
		वापस;

	अगर (IS_CHAN_2GHZ(chan))
		rfMode |= AR_PHY_MODE_DYNAMIC;
	अन्यथा
		rfMode |= AR_PHY_MODE_OFDM;

	अगर (!AR_SREV_9280_20_OR_LATER(ah))
		rfMode |= (IS_CHAN_5GHZ(chan)) ?
			AR_PHY_MODE_RF5GHZ : AR_PHY_MODE_RF2GHZ;

	अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		rfMode |= (AR_PHY_MODE_DYNAMIC | AR_PHY_MODE_DYN_CCK_DISABLE);

	REG_WRITE(ah, AR_PHY_MODE, rfMode);
पूर्ण

अटल व्योम ar5008_hw_mark_phy_inactive(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_DIS);
पूर्ण

अटल व्योम ar5008_hw_set_delta_slope(काष्ठा ath_hw *ah,
				      काष्ठा ath9k_channel *chan)
अणु
	u32 coef_scaled, ds_coef_exp, ds_coef_man;
	u32 घड़ीMhzScaled = 0x64000000;
	काष्ठा chan_centers centers;

	अगर (IS_CHAN_HALF_RATE(chan))
		घड़ीMhzScaled = घड़ीMhzScaled >> 1;
	अन्यथा अगर (IS_CHAN_QUARTER_RATE(chan))
		घड़ीMhzScaled = घड़ीMhzScaled >> 2;

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	coef_scaled = घड़ीMhzScaled / centers.synth_center;

	ath9k_hw_get_delta_slope_vals(ah, coef_scaled, &ds_coef_man,
				      &ds_coef_exp);

	REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		      AR_PHY_TIMING3_DSC_MAN, ds_coef_man);
	REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		      AR_PHY_TIMING3_DSC_EXP, ds_coef_exp);

	coef_scaled = (9 * coef_scaled) / 10;

	ath9k_hw_get_delta_slope_vals(ah, coef_scaled, &ds_coef_man,
				      &ds_coef_exp);

	REG_RMW_FIELD(ah, AR_PHY_HALFGI,
		      AR_PHY_HALFGI_DSC_MAN, ds_coef_man);
	REG_RMW_FIELD(ah, AR_PHY_HALFGI,
		      AR_PHY_HALFGI_DSC_EXP, ds_coef_exp);
पूर्ण

अटल bool ar5008_hw_rfbus_req(काष्ठा ath_hw *ah)
अणु
	REG_WRITE(ah, AR_PHY_RFBUS_REQ, AR_PHY_RFBUS_REQ_EN);
	वापस ath9k_hw_रुको(ah, AR_PHY_RFBUS_GRANT, AR_PHY_RFBUS_GRANT_EN,
			   AR_PHY_RFBUS_GRANT_EN, AH_WAIT_TIMEOUT);
पूर्ण

अटल व्योम ar5008_hw_rfbus_करोne(काष्ठा ath_hw *ah)
अणु
	u32 synthDelay = REG_READ(ah, AR_PHY_RX_DELAY) & AR_PHY_RX_DELAY_DELAY;

	ath9k_hw_synth_delay(ah, ah->curchan, synthDelay);

	REG_WRITE(ah, AR_PHY_RFBUS_REQ, 0);
पूर्ण

अटल व्योम ar5008_restore_chainmask(काष्ठा ath_hw *ah)
अणु
	पूर्णांक rx_chainmask = ah->rxchainmask;

	अगर ((rx_chainmask == 0x5) || (rx_chainmask == 0x3)) अणु
		REG_WRITE(ah, AR_PHY_RX_CHAINMASK, rx_chainmask);
		REG_WRITE(ah, AR_PHY_CAL_CHAINMASK, rx_chainmask);
	पूर्ण
पूर्ण

अटल u32 ar9160_hw_compute_pll_control(काष्ठा ath_hw *ah,
					 काष्ठा ath9k_channel *chan)
अणु
	u32 pll;

	pll = SM(0x5, AR_RTC_9160_PLL_REFDIV);

	अगर (chan && IS_CHAN_HALF_RATE(chan))
		pll |= SM(0x1, AR_RTC_9160_PLL_CLKSEL);
	अन्यथा अगर (chan && IS_CHAN_QUARTER_RATE(chan))
		pll |= SM(0x2, AR_RTC_9160_PLL_CLKSEL);

	अगर (chan && IS_CHAN_5GHZ(chan))
		pll |= SM(0x50, AR_RTC_9160_PLL_DIV);
	अन्यथा
		pll |= SM(0x58, AR_RTC_9160_PLL_DIV);

	वापस pll;
पूर्ण

अटल u32 ar5008_hw_compute_pll_control(काष्ठा ath_hw *ah,
					 काष्ठा ath9k_channel *chan)
अणु
	u32 pll;

	pll = AR_RTC_PLL_REFDIV_5 | AR_RTC_PLL_DIV2;

	अगर (chan && IS_CHAN_HALF_RATE(chan))
		pll |= SM(0x1, AR_RTC_PLL_CLKSEL);
	अन्यथा अगर (chan && IS_CHAN_QUARTER_RATE(chan))
		pll |= SM(0x2, AR_RTC_PLL_CLKSEL);

	अगर (chan && IS_CHAN_5GHZ(chan))
		pll |= SM(0xa, AR_RTC_PLL_DIV);
	अन्यथा
		pll |= SM(0xb, AR_RTC_PLL_DIV);

	वापस pll;
पूर्ण

अटल bool ar5008_hw_ani_control_new(काष्ठा ath_hw *ah,
				      क्रमागत ath9k_ani_cmd cmd,
				      पूर्णांक param)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_channel *chan = ah->curchan;
	काष्ठा ar5416AniState *aniState = &ah->ani;
	s32 value;

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
		/*
		 * make रेजिस्टर setting क्रम शेष
		 * (weak sig detect ON) come from INI file
		 */
		पूर्णांक m1ThreshLow = on ?
			aniState->iniDef.m1ThreshLow : m1ThreshLow_off;
		पूर्णांक m2ThreshLow = on ?
			aniState->iniDef.m2ThreshLow : m2ThreshLow_off;
		पूर्णांक m1Thresh = on ?
			aniState->iniDef.m1Thresh : m1Thresh_off;
		पूर्णांक m2Thresh = on ?
			aniState->iniDef.m2Thresh : m2Thresh_off;
		पूर्णांक m2CountThr = on ?
			aniState->iniDef.m2CountThr : m2CountThr_off;
		पूर्णांक m2CountThrLow = on ?
			aniState->iniDef.m2CountThrLow : m2CountThrLow_off;
		पूर्णांक m1ThreshLowExt = on ?
			aniState->iniDef.m1ThreshLowExt : m1ThreshLowExt_off;
		पूर्णांक m2ThreshLowExt = on ?
			aniState->iniDef.m2ThreshLowExt : m2ThreshLowExt_off;
		पूर्णांक m1ThreshExt = on ?
			aniState->iniDef.m1ThreshExt : m1ThreshExt_off;
		पूर्णांक m2ThreshExt = on ?
			aniState->iniDef.m2ThreshExt : m2ThreshExt_off;

		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M1_THRESH_LOW,
			      m1ThreshLow);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M2_THRESH_LOW,
			      m2ThreshLow);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M1_THRESH, m1Thresh);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M2_THRESH, m2Thresh);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M2COUNT_THR, m2CountThr);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW,
			      m2CountThrLow);

		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M1_THRESH_LOW, m1ThreshLowExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M2_THRESH_LOW, m2ThreshLowExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M1_THRESH, m1ThreshExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M2_THRESH, m2ThreshExt);

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

		value = level * 2;
		REG_RMW_FIELD(ah, AR_PHY_FIND_SIG,
			      AR_PHY_FIND_SIG_FIRSTEP, value);
		REG_RMW_FIELD(ah, AR_PHY_FIND_SIG_LOW,
			      AR_PHY_FIND_SIG_FIRSTEP_LOW, value);

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
				value,
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

		value = (level + 1) * 2;
		REG_RMW_FIELD(ah, AR_PHY_TIMING5,
			      AR_PHY_TIMING5_CYCPWR_THR1, value);

		REG_RMW_FIELD(ah, AR_PHY_EXT_CCA,
				  AR_PHY_EXT_TIMING5_CYCPWR_THR1, value - 1);

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
				value,
				aniState->iniDef.cycpwrThr1Ext);
			अगर (level > aniState->spurImmunityLevel)
				ah->stats.ast_ani_spurup++;
			अन्यथा अगर (level < aniState->spurImmunityLevel)
				ah->stats.ast_ani_spurकरोwn++;
			aniState->spurImmunityLevel = level;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल ATH9K_ANI_MRC_CCK:
		/*
		 * You should not see this as AR5008, AR9001, AR9002
		 * करोes not have hardware support क्रम MRC CCK.
		 */
		WARN_ON(1);
		अवरोध;
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

अटल व्योम ar5008_hw_करो_getnf(काष्ठा ath_hw *ah,
			      पूर्णांक16_t nfarray[NUM_NF_READINGS])
अणु
	पूर्णांक16_t nf;

	nf = MS(REG_READ(ah, AR_PHY_CCA), AR_PHY_MINCCA_PWR);
	nfarray[0] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH1_CCA), AR_PHY_CH1_MINCCA_PWR);
	nfarray[1] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH2_CCA), AR_PHY_CH2_MINCCA_PWR);
	nfarray[2] = sign_extend32(nf, 8);

	अगर (!IS_CHAN_HT40(ah->curchan))
		वापस;

	nf = MS(REG_READ(ah, AR_PHY_EXT_CCA), AR_PHY_EXT_MINCCA_PWR);
	nfarray[3] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH1_EXT_CCA), AR_PHY_CH1_EXT_MINCCA_PWR);
	nfarray[4] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH2_EXT_CCA), AR_PHY_CH2_EXT_MINCCA_PWR);
	nfarray[5] = sign_extend32(nf, 8);
पूर्ण

/*
 * Initialize the ANI रेजिस्टर values with शेष (ini) values.
 * This routine is called during a (full) hardware reset after
 * all the रेजिस्टरs are initialised from the INI.
 */
अटल व्योम ar5008_hw_ani_cache_ini_regs(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_channel *chan = ah->curchan;
	काष्ठा ar5416AniState *aniState = &ah->ani;
	काष्ठा ath9k_ani_शेष *iniDef;
	u32 val;

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
					    AR_PHY_FIND_SIG_FIRSTEP_LOW);
	iniDef->cycpwrThr1 = REG_READ_FIELD(ah,
					    AR_PHY_TIMING5,
					    AR_PHY_TIMING5_CYCPWR_THR1);
	iniDef->cycpwrThr1Ext = REG_READ_FIELD(ah,
					       AR_PHY_EXT_CCA,
					       AR_PHY_EXT_TIMING5_CYCPWR_THR1);

	/* these levels just got reset to शेषs by the INI */
	aniState->spurImmunityLevel = ATH9K_ANI_SPUR_IMMUNE_LVL;
	aniState->firstepLevel = ATH9K_ANI_FIRSTEP_LVL;
	aniState->ofdmWeakSigDetect = true;
	aniState->mrcCCK = false; /* not available on pre AR9003 */
पूर्ण

अटल व्योम ar5008_hw_set_nf_limits(काष्ठा ath_hw *ah)
अणु
	ah->nf_2g.max = AR_PHY_CCA_MAX_GOOD_VAL_5416_2GHZ;
	ah->nf_2g.min = AR_PHY_CCA_MIN_GOOD_VAL_5416_2GHZ;
	ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_5416_2GHZ;
	ah->nf_5g.max = AR_PHY_CCA_MAX_GOOD_VAL_5416_5GHZ;
	ah->nf_5g.min = AR_PHY_CCA_MIN_GOOD_VAL_5416_5GHZ;
	ah->nf_5g.nominal = AR_PHY_CCA_NOM_VAL_5416_5GHZ;
पूर्ण

अटल व्योम ar5008_hw_set_radar_params(काष्ठा ath_hw *ah,
				       काष्ठा ath_hw_radar_conf *conf)
अणु
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
पूर्ण

अटल व्योम ar5008_hw_set_radar_conf(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_radar_conf *conf = &ah->radar_conf;

	conf->fir_घातer = -33;
	conf->radar_rssi = 20;
	conf->pulse_height = 10;
	conf->pulse_rssi = 15;
	conf->pulse_inband = 15;
	conf->pulse_maxlen = 255;
	conf->pulse_inband_step = 12;
	conf->radar_inband = 8;
पूर्ण

अटल व्योम ar5008_hw_init_txघातer_cck(काष्ठा ath_hw *ah, पूर्णांक16_t *rate_array)
अणु
#घोषणा CCK_DELTA(x) ((OLC_FOR_AR9280_20_LATER) ? max((x) - 2, 0) : (x))
	ah->tx_घातer[0] = CCK_DELTA(rate_array[rate1l]);
	ah->tx_घातer[1] = CCK_DELTA(min(rate_array[rate2l],
					rate_array[rate2s]));
	ah->tx_घातer[2] = CCK_DELTA(min(rate_array[rate5_5l],
					rate_array[rate5_5s]));
	ah->tx_घातer[3] = CCK_DELTA(min(rate_array[rate11l],
					rate_array[rate11s]));
#अघोषित CCK_DELTA
पूर्ण

अटल व्योम ar5008_hw_init_txघातer_ofdm(काष्ठा ath_hw *ah, पूर्णांक16_t *rate_array,
					पूर्णांक offset)
अणु
	पूर्णांक i, idx = 0;

	क्रम (i = offset; i < offset + AR5008_OFDM_RATES; i++) अणु
		ah->tx_घातer[i] = rate_array[idx];
		idx++;
	पूर्ण
पूर्ण

अटल व्योम ar5008_hw_init_txघातer_ht(काष्ठा ath_hw *ah, पूर्णांक16_t *rate_array,
				      पूर्णांक ss_offset, पूर्णांक ds_offset,
				      bool is_40, पूर्णांक ht40_delta)
अणु
	पूर्णांक i, mcs_idx = (is_40) ? AR5008_HT40_SHIFT : AR5008_HT20_SHIFT;

	क्रम (i = ss_offset; i < ss_offset + AR5008_HT_SS_RATES; i++) अणु
		ah->tx_घातer[i] = rate_array[mcs_idx] + ht40_delta;
		mcs_idx++;
	पूर्ण
	स_नकल(&ah->tx_घातer[ds_offset], &ah->tx_घातer[ss_offset],
	       AR5008_HT_SS_RATES);
पूर्ण

व्योम ar5008_hw_init_rate_txघातer(काष्ठा ath_hw *ah, पूर्णांक16_t *rate_array,
				 काष्ठा ath9k_channel *chan, पूर्णांक ht40_delta)
अणु
	अगर (IS_CHAN_5GHZ(chan)) अणु
		ar5008_hw_init_txघातer_ofdm(ah, rate_array,
					    AR5008_11NA_OFDM_SHIFT);
		अगर (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) अणु
			ar5008_hw_init_txघातer_ht(ah, rate_array,
						  AR5008_11NA_HT_SS_SHIFT,
						  AR5008_11NA_HT_DS_SHIFT,
						  IS_CHAN_HT40(chan),
						  ht40_delta);
		पूर्ण
	पूर्ण अन्यथा अणु
		ar5008_hw_init_txघातer_cck(ah, rate_array);
		ar5008_hw_init_txघातer_ofdm(ah, rate_array,
					    AR5008_11NG_OFDM_SHIFT);
		अगर (IS_CHAN_HT20(chan) || IS_CHAN_HT40(chan)) अणु
			ar5008_hw_init_txघातer_ht(ah, rate_array,
						  AR5008_11NG_HT_SS_SHIFT,
						  AR5008_11NG_HT_DS_SHIFT,
						  IS_CHAN_HT40(chan),
						  ht40_delta);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ar5008_hw_attach_phy_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_निजी_ops *priv_ops = ath9k_hw_निजी_ops(ah);
	अटल स्थिर u32 ar5416_cca_regs[6] = अणु
		AR_PHY_CCA,
		AR_PHY_CH1_CCA,
		AR_PHY_CH2_CCA,
		AR_PHY_EXT_CCA,
		AR_PHY_CH1_EXT_CCA,
		AR_PHY_CH2_EXT_CCA
	पूर्ण;
	पूर्णांक ret;

	ret = ar5008_hw_rf_alloc_ext_banks(ah);
	अगर (ret)
	    वापस ret;

	priv_ops->rf_set_freq = ar5008_hw_set_channel;
	priv_ops->spur_mitigate_freq = ar5008_hw_spur_mitigate;

	priv_ops->set_rf_regs = ar5008_hw_set_rf_regs;
	priv_ops->set_channel_regs = ar5008_hw_set_channel_regs;
	priv_ops->init_bb = ar5008_hw_init_bb;
	priv_ops->process_ini = ar5008_hw_process_ini;
	priv_ops->set_rभ_शेषe = ar5008_hw_set_rभ_शेषe;
	priv_ops->mark_phy_inactive = ar5008_hw_mark_phy_inactive;
	priv_ops->set_delta_slope = ar5008_hw_set_delta_slope;
	priv_ops->rfbus_req = ar5008_hw_rfbus_req;
	priv_ops->rfbus_करोne = ar5008_hw_rfbus_करोne;
	priv_ops->restore_chainmask = ar5008_restore_chainmask;
	priv_ops->करो_getnf = ar5008_hw_करो_getnf;
	priv_ops->set_radar_params = ar5008_hw_set_radar_params;

	priv_ops->ani_control = ar5008_hw_ani_control_new;
	priv_ops->ani_cache_ini_regs = ar5008_hw_ani_cache_ini_regs;

	अगर (AR_SREV_9100(ah) || AR_SREV_9160_10_OR_LATER(ah))
		priv_ops->compute_pll_control = ar9160_hw_compute_pll_control;
	अन्यथा
		priv_ops->compute_pll_control = ar5008_hw_compute_pll_control;

	ar5008_hw_set_nf_limits(ah);
	ar5008_hw_set_radar_conf(ah);
	स_नकल(ah->nf_regs, ar5416_cca_regs, माप(ah->nf_regs));
	वापस 0;
पूर्ण
