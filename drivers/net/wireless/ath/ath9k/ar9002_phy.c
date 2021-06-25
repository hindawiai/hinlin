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

/**
 * DOC: Programming Atheros 802.11n analog front end radios
 *
 * AR5416 MAC based PCI devices and AR518 MAC based PCI-Express
 * devices have either an बाह्यal AR2133 analog front end radio क्रम single
 * band 2.4 GHz communication or an AR5133 analog front end radio क्रम dual
 * band 2.4 GHz / 5 GHz communication.
 *
 * All devices after the AR5416 and AR5418 family starting with the AR9280
 * have their analog front radios, MAC/BB and host PCIe/USB पूर्णांकerface embedded
 * पूर्णांकo a single-chip and require less programming.
 *
 * The following single-chips exist with a respective embedded radio:
 *
 * AR9280 - 11n dual-band 2x2 MIMO क्रम PCIe
 * AR9281 - 11n single-band 1x2 MIMO क्रम PCIe
 * AR9285 - 11n single-band 1x1 क्रम PCIe
 * AR9287 - 11n single-band 2x2 MIMO क्रम PCIe
 *
 * AR9220 - 11n dual-band 2x2 MIMO क्रम PCI
 * AR9223 - 11n single-band 2x2 MIMO क्रम PCI
 *
 * AR9287 - 11n single-band 1x1 MIMO क्रम USB
 */

#समावेश "hw.h"
#समावेश "ar9002_phy.h"

/**
 * ar9002_hw_set_channel - set channel on single-chip device
 * @ah: atheros hardware काष्ठाure
 * @chan:
 *
 * This is the function to change channel on single-chip devices, that is
 * all devices after ar9280.
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
 */
अटल पूर्णांक ar9002_hw_set_channel(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	u16 bMode, fracMode, aModeRefSel = 0;
	u32 freq, nभाग, channelSel = 0, channelFrac = 0, reg32 = 0;
	काष्ठा chan_centers centers;
	u32 refDivA = 24;

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	freq = centers.synth_center;

	reg32 = REG_READ(ah, AR_PHY_SYNTH_CONTROL);
	reg32 &= 0xc0000000;

	अगर (freq < 4800) अणु /* 2 GHz, fractional mode */
		u32 txctl;
		पूर्णांक regWrites = 0;

		bMode = 1;
		fracMode = 1;
		aModeRefSel = 0;
		channelSel = CHANSEL_2G(freq);

		अगर (AR_SREV_9287_11_OR_LATER(ah)) अणु
			अगर (freq == 2484) अणु
				/* Enable channel spपढ़ोing क्रम channel 14 */
				REG_WRITE_ARRAY(&ah->iniCckfirJapan2484,
						1, regWrites);
			पूर्ण अन्यथा अणु
				REG_WRITE_ARRAY(&ah->iniCckfirNormal,
						1, regWrites);
			पूर्ण
		पूर्ण अन्यथा अणु
			txctl = REG_READ(ah, AR_PHY_CCK_TX_CTRL);
			अगर (freq == 2484) अणु
				/* Enable channel spपढ़ोing क्रम channel 14 */
				REG_WRITE(ah, AR_PHY_CCK_TX_CTRL,
					  txctl | AR_PHY_CCK_TX_CTRL_JAPAN);
			पूर्ण अन्यथा अणु
				REG_WRITE(ah, AR_PHY_CCK_TX_CTRL,
					  txctl & ~AR_PHY_CCK_TX_CTRL_JAPAN);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		bMode = 0;
		fracMode = 0;

		चयन (ah->eep_ops->get_eeprom(ah, EEP_FRAC_N_5G)) अणु
		हाल 0:
			अगर (IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan))
				aModeRefSel = 0;
			अन्यथा अगर ((freq % 20) == 0)
				aModeRefSel = 3;
			अन्यथा अगर ((freq % 10) == 0)
				aModeRefSel = 2;
			अगर (aModeRefSel)
				अवरोध;
			fallthrough;
		हाल 1:
		शेष:
			aModeRefSel = 0;
			/*
			 * Enable 2G (fractional) mode क्रम channels
			 * which are 5MHz spaced.
			 */
			fracMode = 1;
			refDivA = 1;
			channelSel = CHANSEL_5G(freq);

			/* RefDivA setting */
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_SYNTH9,
				      AR_AN_SYNTH9_REFDIVA,
				      AR_AN_SYNTH9_REFDIVA_S, refDivA);

		पूर्ण

		अगर (!fracMode) अणु
			nभाग = (freq * (refDivA >> aModeRefSel)) / 60;
			channelSel = nभाग & 0x1ff;
			channelFrac = (nभाग & 0xfffffe00) * 2;
			channelSel = (channelSel << 17) | channelFrac;
		पूर्ण
	पूर्ण

	reg32 = reg32 |
	    (bMode << 29) |
	    (fracMode << 28) | (aModeRefSel << 26) | (channelSel);

	REG_WRITE(ah, AR_PHY_SYNTH_CONTROL, reg32);

	ah->curchan = chan;

	वापस 0;
पूर्ण

/**
 * ar9002_hw_spur_mitigate - convert baseband spur frequency
 * @ah: atheros hardware काष्ठाure
 * @chan:
 *
 * For single-chip solutions. Converts to baseband spur frequency given the
 * input channel frequency and compute रेजिस्टर settings below.
 */
अटल व्योम ar9002_hw_spur_mitigate(काष्ठा ath_hw *ah,
				    काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक bb_spur = AR_NO_SPUR;
	पूर्णांक freq;
	पूर्णांक bin;
	पूर्णांक bb_spur_off, spur_subchannel_sd;
	पूर्णांक spur_freq_sd;
	पूर्णांक spur_delta_phase;
	पूर्णांक denominator;
	पूर्णांक पंचांगp, newVal;
	पूर्णांक i;
	काष्ठा chan_centers centers;

	पूर्णांक cur_bb_spur;
	bool is2GHz = IS_CHAN_2GHZ(chan);

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	freq = centers.synth_center;

	क्रम (i = 0; i < AR_EEPROM_MODAL_SPURS; i++) अणु
		cur_bb_spur = ah->eep_ops->get_spur_channel(ah, i, is2GHz);

		अगर (AR_NO_SPUR == cur_bb_spur)
			अवरोध;

		अगर (is2GHz)
			cur_bb_spur = (cur_bb_spur / 10) + AR_BASE_FREQ_2GHZ;
		अन्यथा
			cur_bb_spur = (cur_bb_spur / 10) + AR_BASE_FREQ_5GHZ;

		cur_bb_spur = cur_bb_spur - freq;

		अगर (IS_CHAN_HT40(chan)) अणु
			अगर ((cur_bb_spur > -AR_SPUR_FEEQ_BOUND_HT40) &&
			    (cur_bb_spur < AR_SPUR_FEEQ_BOUND_HT40)) अणु
				bb_spur = cur_bb_spur;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((cur_bb_spur > -AR_SPUR_FEEQ_BOUND_HT20) &&
			   (cur_bb_spur < AR_SPUR_FEEQ_BOUND_HT20)) अणु
			bb_spur = cur_bb_spur;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (AR_NO_SPUR == bb_spur) अणु
		REG_CLR_BIT(ah, AR_PHY_FORCE_CLKEN_CCK,
			    AR_PHY_FORCE_CLKEN_CCK_MRC_MUX);
		वापस;
	पूर्ण अन्यथा अणु
		REG_CLR_BIT(ah, AR_PHY_FORCE_CLKEN_CCK,
			    AR_PHY_FORCE_CLKEN_CCK_MRC_MUX);
	पूर्ण

	bin = bb_spur * 320;

	पंचांगp = REG_READ(ah, AR_PHY_TIMING_CTRL4(0));

	ENABLE_REGWRITE_BUFFER(ah);

	newVal = पंचांगp | (AR_PHY_TIMING_CTRL4_ENABLE_SPUR_RSSI |
			AR_PHY_TIMING_CTRL4_ENABLE_SPUR_FILTER |
			AR_PHY_TIMING_CTRL4_ENABLE_CHAN_MASK |
			AR_PHY_TIMING_CTRL4_ENABLE_PILOT_MASK);
	REG_WRITE(ah, AR_PHY_TIMING_CTRL4(0), newVal);

	newVal = (AR_PHY_SPUR_REG_MASK_RATE_CNTL |
		  AR_PHY_SPUR_REG_ENABLE_MASK_PPM |
		  AR_PHY_SPUR_REG_MASK_RATE_SELECT |
		  AR_PHY_SPUR_REG_ENABLE_VIT_SPUR_RSSI |
		  SM(SPUR_RSSI_THRESH, AR_PHY_SPUR_REG_SPUR_RSSI_THRESH));
	REG_WRITE(ah, AR_PHY_SPUR_REG, newVal);

	अगर (IS_CHAN_HT40(chan)) अणु
		अगर (bb_spur < 0) अणु
			spur_subchannel_sd = 1;
			bb_spur_off = bb_spur + 10;
		पूर्ण अन्यथा अणु
			spur_subchannel_sd = 0;
			bb_spur_off = bb_spur - 10;
		पूर्ण
	पूर्ण अन्यथा अणु
		spur_subchannel_sd = 0;
		bb_spur_off = bb_spur;
	पूर्ण

	अगर (IS_CHAN_HT40(chan))
		spur_delta_phase =
			((bb_spur * 262144) /
			 10) & AR_PHY_TIMING11_SPUR_DELTA_PHASE;
	अन्यथा
		spur_delta_phase =
			((bb_spur * 524288) /
			 10) & AR_PHY_TIMING11_SPUR_DELTA_PHASE;

	denominator = IS_CHAN_2GHZ(chan) ? 44 : 40;
	spur_freq_sd = ((bb_spur_off * 2048) / denominator) & 0x3ff;

	newVal = (AR_PHY_TIMING11_USE_SPUR_IN_AGC |
		  SM(spur_freq_sd, AR_PHY_TIMING11_SPUR_FREQ_SD) |
		  SM(spur_delta_phase, AR_PHY_TIMING11_SPUR_DELTA_PHASE));
	REG_WRITE(ah, AR_PHY_TIMING11, newVal);

	newVal = spur_subchannel_sd << AR_PHY_SFCORR_SPUR_SUBCHNL_SD_S;
	REG_WRITE(ah, AR_PHY_SFCORR_EXT, newVal);

	ar5008_hw_cmn_spur_mitigate(ah, chan, bin);

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

अटल व्योम ar9002_olc_init(काष्ठा ath_hw *ah)
अणु
	u32 i;

	अगर (!OLC_FOR_AR9280_20_LATER)
		वापस;

	अगर (OLC_FOR_AR9287_10_LATER) अणु
		REG_SET_BIT(ah, AR_PHY_TX_PWRCTRL9,
				AR_PHY_TX_PWRCTRL9_RES_DC_REMOVAL);
		ath9k_hw_analog_shअगरt_rmw(ah, AR9287_AN_TXPC0,
				AR9287_AN_TXPC0_TXPCMODE,
				AR9287_AN_TXPC0_TXPCMODE_S,
				AR9287_AN_TXPC0_TXPCMODE_TEMPSENSE);
		udelay(100);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < AR9280_TX_GAIN_TABLE_SIZE; i++)
			ah->originalGain[i] =
				MS(REG_READ(ah, AR_PHY_TX_GAIN_TBL1 + i * 4),
						AR_PHY_TX_GAIN);
		ah->PDADCdelta = 0;
	पूर्ण
पूर्ण

अटल u32 ar9002_hw_compute_pll_control(काष्ठा ath_hw *ah,
					 काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक ref_भाग = 5;
	पूर्णांक pll_भाग = 0x2c;
	u32 pll;

	अगर (chan && IS_CHAN_5GHZ(chan) && !IS_CHAN_A_FAST_CLOCK(ah, chan)) अणु
		अगर (AR_SREV_9280_20(ah)) अणु
			ref_भाग = 10;
			pll_भाग = 0x50;
		पूर्ण अन्यथा अणु
			pll_भाग = 0x28;
		पूर्ण
	पूर्ण

	pll = SM(ref_भाग, AR_RTC_9160_PLL_REFDIV);
	pll |= SM(pll_भाग, AR_RTC_9160_PLL_DIV);

	अगर (chan && IS_CHAN_HALF_RATE(chan))
		pll |= SM(0x1, AR_RTC_9160_PLL_CLKSEL);
	अन्यथा अगर (chan && IS_CHAN_QUARTER_RATE(chan))
		pll |= SM(0x2, AR_RTC_9160_PLL_CLKSEL);

	वापस pll;
पूर्ण

अटल व्योम ar9002_hw_करो_getnf(काष्ठा ath_hw *ah,
			      पूर्णांक16_t nfarray[NUM_NF_READINGS])
अणु
	पूर्णांक16_t nf;

	nf = MS(REG_READ(ah, AR_PHY_CCA), AR9280_PHY_MINCCA_PWR);
	nfarray[0] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_EXT_CCA), AR9280_PHY_EXT_MINCCA_PWR);
	अगर (IS_CHAN_HT40(ah->curchan))
		nfarray[3] = sign_extend32(nf, 8);

	अगर (!(ah->rxchainmask & BIT(1)))
		वापस;

	nf = MS(REG_READ(ah, AR_PHY_CH1_CCA), AR9280_PHY_CH1_MINCCA_PWR);
	nfarray[1] = sign_extend32(nf, 8);

	nf = MS(REG_READ(ah, AR_PHY_CH1_EXT_CCA), AR9280_PHY_CH1_EXT_MINCCA_PWR);
	अगर (IS_CHAN_HT40(ah->curchan))
		nfarray[4] = sign_extend32(nf, 8);
पूर्ण

अटल व्योम ar9002_hw_set_nf_limits(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9285(ah)) अणु
		ah->nf_2g.max = AR_PHY_CCA_MAX_GOOD_VAL_9285_2GHZ;
		ah->nf_2g.min = AR_PHY_CCA_MIN_GOOD_VAL_9285_2GHZ;
		ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_9285_2GHZ;
	पूर्ण अन्यथा अगर (AR_SREV_9287(ah)) अणु
		ah->nf_2g.max = AR_PHY_CCA_MAX_GOOD_VAL_9287_2GHZ;
		ah->nf_2g.min = AR_PHY_CCA_MIN_GOOD_VAL_9287_2GHZ;
		ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_9287_2GHZ;
	पूर्ण अन्यथा अगर (AR_SREV_9271(ah)) अणु
		ah->nf_2g.max = AR_PHY_CCA_MAX_GOOD_VAL_9271_2GHZ;
		ah->nf_2g.min = AR_PHY_CCA_MIN_GOOD_VAL_9271_2GHZ;
		ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_9271_2GHZ;
	पूर्ण अन्यथा अणु
		ah->nf_2g.max = AR_PHY_CCA_MAX_GOOD_VAL_9280_2GHZ;
		ah->nf_2g.min = AR_PHY_CCA_MIN_GOOD_VAL_9280_2GHZ;
		ah->nf_2g.nominal = AR_PHY_CCA_NOM_VAL_9280_2GHZ;
		ah->nf_5g.max = AR_PHY_CCA_MAX_GOOD_VAL_9280_5GHZ;
		ah->nf_5g.min = AR_PHY_CCA_MIN_GOOD_VAL_9280_5GHZ;
		ah->nf_5g.nominal = AR_PHY_CCA_NOM_VAL_9280_5GHZ;
	पूर्ण
पूर्ण

अटल व्योम ar9002_hw_antभाग_comb_conf_get(काष्ठा ath_hw *ah,
				   काष्ठा ath_hw_antcomb_conf *antconf)
अणु
	u32 regval;

	regval = REG_READ(ah, AR_PHY_MULTICHAIN_GAIN_CTL);
	antconf->मुख्य_lna_conf = (regval & AR_PHY_9285_ANT_DIV_MAIN_LNACONF) >>
				  AR_PHY_9285_ANT_DIV_MAIN_LNACONF_S;
	antconf->alt_lna_conf = (regval & AR_PHY_9285_ANT_DIV_ALT_LNACONF) >>
				 AR_PHY_9285_ANT_DIV_ALT_LNACONF_S;
	antconf->fast_भाग_bias = (regval & AR_PHY_9285_FAST_DIV_BIAS) >>
				  AR_PHY_9285_FAST_DIV_BIAS_S;
	antconf->lna1_lna2_चयन_delta = -1;
	antconf->lna1_lna2_delta = -3;
	antconf->भाग_group = 0;
पूर्ण

अटल व्योम ar9002_hw_antभाग_comb_conf_set(काष्ठा ath_hw *ah,
				   काष्ठा ath_hw_antcomb_conf *antconf)
अणु
	u32 regval;

	regval = REG_READ(ah, AR_PHY_MULTICHAIN_GAIN_CTL);
	regval &= ~(AR_PHY_9285_ANT_DIV_MAIN_LNACONF |
		    AR_PHY_9285_ANT_DIV_ALT_LNACONF |
		    AR_PHY_9285_FAST_DIV_BIAS);
	regval |= ((antconf->मुख्य_lna_conf << AR_PHY_9285_ANT_DIV_MAIN_LNACONF_S)
		   & AR_PHY_9285_ANT_DIV_MAIN_LNACONF);
	regval |= ((antconf->alt_lna_conf << AR_PHY_9285_ANT_DIV_ALT_LNACONF_S)
		   & AR_PHY_9285_ANT_DIV_ALT_LNACONF);
	regval |= ((antconf->fast_भाग_bias << AR_PHY_9285_FAST_DIV_BIAS_S)
		   & AR_PHY_9285_FAST_DIV_BIAS);

	REG_WRITE(ah, AR_PHY_MULTICHAIN_GAIN_CTL, regval);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT

अटल व्योम ar9002_hw_set_bt_ant_भागersity(काष्ठा ath_hw *ah, bool enable)
अणु
	काष्ठा ath_btcoex_hw *btcoex = &ah->btcoex_hw;
	u8 antभाग_ctrl1, antभाग_ctrl2;
	u32 regval;

	अगर (enable) अणु
		antभाग_ctrl1 = ATH_BT_COEX_ANTDIV_CONTROL1_ENABLE;
		antभाग_ctrl2 = ATH_BT_COEX_ANTDIV_CONTROL2_ENABLE;

		/*
		 * Don't disable BT ant to allow BB to control SWCOM.
		 */
		btcoex->bt_coex_mode2 &= (~(AR_BT_DISABLE_BT_ANT));
		REG_WRITE(ah, AR_BT_COEX_MODE2, btcoex->bt_coex_mode2);

		REG_WRITE(ah, AR_PHY_SWITCH_COM, ATH_BT_COEX_ANT_DIV_SWITCH_COM);
		REG_RMW(ah, AR_PHY_SWITCH_CHAIN_0, 0, 0xf0000000);
	पूर्ण अन्यथा अणु
		/*
		 * Disable antenna भागersity, use LNA1 only.
		 */
		antभाग_ctrl1 = ATH_BT_COEX_ANTDIV_CONTROL1_FIXED_A;
		antभाग_ctrl2 = ATH_BT_COEX_ANTDIV_CONTROL2_FIXED_A;

		/*
		 * Disable BT Ant. to allow concurrent BT and WLAN receive.
		 */
		btcoex->bt_coex_mode2 |= AR_BT_DISABLE_BT_ANT;
		REG_WRITE(ah, AR_BT_COEX_MODE2, btcoex->bt_coex_mode2);

		/*
		 * Program SWCOM table to make sure RF चयन always parks
		 * at BT side.
		 */
		REG_WRITE(ah, AR_PHY_SWITCH_COM, 0);
		REG_RMW(ah, AR_PHY_SWITCH_CHAIN_0, 0, 0xf0000000);
	पूर्ण

	regval = REG_READ(ah, AR_PHY_MULTICHAIN_GAIN_CTL);
	regval &= (~(AR_PHY_9285_ANT_DIV_CTL_ALL));
        /*
	 * Clear ant_fast_भाग_bias [14:9] since क्रम WB195,
	 * the मुख्य LNA is always LNA1.
	 */
	regval &= (~(AR_PHY_9285_FAST_DIV_BIAS));
	regval |= SM(antभाग_ctrl1, AR_PHY_9285_ANT_DIV_CTL);
	regval |= SM(antभाग_ctrl2, AR_PHY_9285_ANT_DIV_ALT_LNACONF);
	regval |= SM((antभाग_ctrl2 >> 2), AR_PHY_9285_ANT_DIV_MAIN_LNACONF);
	regval |= SM((antभाग_ctrl1 >> 1), AR_PHY_9285_ANT_DIV_ALT_GAINTB);
	regval |= SM((antभाग_ctrl1 >> 2), AR_PHY_9285_ANT_DIV_MAIN_GAINTB);
	REG_WRITE(ah, AR_PHY_MULTICHAIN_GAIN_CTL, regval);

	regval = REG_READ(ah, AR_PHY_CCK_DETECT);
	regval &= (~AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV);
	regval |= SM((antभाग_ctrl1 >> 3), AR_PHY_CCK_DETECT_BB_ENABLE_ANT_FAST_DIV);
	REG_WRITE(ah, AR_PHY_CCK_DETECT, regval);
पूर्ण

#पूर्ण_अगर

अटल व्योम ar9002_hw_spectral_scan_config(काष्ठा ath_hw *ah,
				    काष्ठा ath_spec_scan *param)
अणु
	u32 repeat_bit;
	u8 count;

	अगर (!param->enabled) अणु
		REG_CLR_BIT(ah, AR_PHY_SPECTRAL_SCAN,
			    AR_PHY_SPECTRAL_SCAN_ENABLE);
		वापस;
	पूर्ण
	REG_SET_BIT(ah, AR_PHY_RADAR_0, AR_PHY_RADAR_0_FFT_ENA);
	REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, AR_PHY_SPECTRAL_SCAN_ENABLE);

	अगर (AR_SREV_9280(ah))
		repeat_bit = AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT;
	अन्यथा
		repeat_bit = AR_PHY_SPECTRAL_SCAN_SHORT_REPEAT_KIWI;

	अगर (param->लघु_repeat)
		REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, repeat_bit);
	अन्यथा
		REG_CLR_BIT(ah, AR_PHY_SPECTRAL_SCAN, repeat_bit);

	/* on AR92xx, the highest bit of count will make the the chip send
	 * spectral samples endlessly. Check अगर this really was पूर्णांकended,
	 * and fix otherwise.
	 */
	count = param->count;
	अगर (param->endless) अणु
		अगर (AR_SREV_9280(ah))
			count = 0x80;
		अन्यथा
			count = 0;
	पूर्ण अन्यथा अगर (count & 0x80)
		count = 0x7f;
	अन्यथा अगर (!count)
		count = 1;

	अगर (AR_SREV_9280(ah)) अणु
		REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
			      AR_PHY_SPECTRAL_SCAN_COUNT, count);
	पूर्ण अन्यथा अणु
		REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
			      AR_PHY_SPECTRAL_SCAN_COUNT_KIWI, count);
		REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN,
			    AR_PHY_SPECTRAL_SCAN_PHYERR_MASK_SELECT);
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
		      AR_PHY_SPECTRAL_SCAN_PERIOD, param->period);
	REG_RMW_FIELD(ah, AR_PHY_SPECTRAL_SCAN,
		      AR_PHY_SPECTRAL_SCAN_FFT_PERIOD, param->fft_period);

	वापस;
पूर्ण

अटल व्योम ar9002_hw_spectral_scan_trigger(काष्ठा ath_hw *ah)
अणु
	REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN, AR_PHY_SPECTRAL_SCAN_ENABLE);
	/* Activate spectral scan */
	REG_SET_BIT(ah, AR_PHY_SPECTRAL_SCAN,
		    AR_PHY_SPECTRAL_SCAN_ACTIVE);
पूर्ण

अटल व्योम ar9002_hw_spectral_scan_रुको(काष्ठा ath_hw *ah)
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

अटल व्योम ar9002_hw_tx99_start(काष्ठा ath_hw *ah, u32 qnum)
अणु
	REG_SET_BIT(ah, 0x9864, 0x7f000);
	REG_SET_BIT(ah, 0x9924, 0x7f00fe);
	REG_CLR_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_DIS);
	REG_WRITE(ah, AR_CR, AR_CR_RXD);
	REG_WRITE(ah, AR_DLCL_IFS(qnum), 0);
	REG_WRITE(ah, AR_D_GBL_IFS_SIFS, 20);
	REG_WRITE(ah, AR_D_GBL_IFS_EIFS, 20);
	REG_WRITE(ah, AR_D_FPCTL, 0x10|qnum);
	REG_WRITE(ah, AR_TIME_OUT, 0x00000400);
	REG_WRITE(ah, AR_DRETRY_LIMIT(qnum), 0xffffffff);
	REG_SET_BIT(ah, AR_QMISC(qnum), AR_Q_MISC_DCU_EARLY_TERM_REQ);
पूर्ण

अटल व्योम ar9002_hw_tx99_stop(काष्ठा ath_hw *ah)
अणु
	REG_SET_BIT(ah, AR_DIAG_SW, AR_DIAG_RX_DIS);
पूर्ण

व्योम ar9002_hw_attach_phy_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_निजी_ops *priv_ops = ath9k_hw_निजी_ops(ah);
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(ah);

	priv_ops->set_rf_regs = शून्य;
	priv_ops->rf_set_freq = ar9002_hw_set_channel;
	priv_ops->spur_mitigate_freq = ar9002_hw_spur_mitigate;
	priv_ops->olc_init = ar9002_olc_init;
	priv_ops->compute_pll_control = ar9002_hw_compute_pll_control;
	priv_ops->करो_getnf = ar9002_hw_करो_getnf;

	ops->antभाग_comb_conf_get = ar9002_hw_antभाग_comb_conf_get;
	ops->antभाग_comb_conf_set = ar9002_hw_antभाग_comb_conf_set;
	ops->spectral_scan_config = ar9002_hw_spectral_scan_config;
	ops->spectral_scan_trigger = ar9002_hw_spectral_scan_trigger;
	ops->spectral_scan_रुको = ar9002_hw_spectral_scan_रुको;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	ops->set_bt_ant_भागersity = ar9002_hw_set_bt_ant_भागersity;
#पूर्ण_अगर
	ops->tx99_start = ar9002_hw_tx99_start;
	ops->tx99_stop = ar9002_hw_tx99_stop;

	ar9002_hw_set_nf_limits(ah);
पूर्ण
