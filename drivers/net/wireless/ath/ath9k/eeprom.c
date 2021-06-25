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
#समावेश <linux/ath9k_platक्रमm.h>

व्योम ath9k_hw_analog_shअगरt_regग_लिखो(काष्ठा ath_hw *ah, u32 reg, u32 val)
अणु
        REG_WRITE(ah, reg, val);

        अगर (ah->config.analog_shअगरtreg)
		udelay(100);
पूर्ण

व्योम ath9k_hw_analog_shअगरt_rmw(काष्ठा ath_hw *ah, u32 reg, u32 mask,
			       u32 shअगरt, u32 val)
अणु
	REG_RMW(ah, reg, ((val << shअगरt) & mask), mask);

	अगर (ah->config.analog_shअगरtreg)
		udelay(100);
पूर्ण

पूर्णांक16_t ath9k_hw_पूर्णांकerpolate(u16 target, u16 srcLeft, u16 srcRight,
			     पूर्णांक16_t targetLeft, पूर्णांक16_t targetRight)
अणु
	पूर्णांक16_t rv;

	अगर (srcRight == srcLeft) अणु
		rv = targetLeft;
	पूर्ण अन्यथा अणु
		rv = (पूर्णांक16_t) (((target - srcLeft) * targetRight +
				 (srcRight - target) * targetLeft) /
				(srcRight - srcLeft));
	पूर्ण
	वापस rv;
पूर्ण

bool ath9k_hw_get_lower_upper_index(u8 target, u8 *pList, u16 listSize,
				    u16 *indexL, u16 *indexR)
अणु
	u16 i;

	अगर (target <= pList[0]) अणु
		*indexL = *indexR = 0;
		वापस true;
	पूर्ण
	अगर (target >= pList[listSize - 1]) अणु
		*indexL = *indexR = (u16) (listSize - 1);
		वापस true;
	पूर्ण

	क्रम (i = 0; i < listSize - 1; i++) अणु
		अगर (pList[i] == target) अणु
			*indexL = *indexR = i;
			वापस true;
		पूर्ण
		अगर (target < pList[i + 1]) अणु
			*indexL = i;
			*indexR = (u16) (i + 1);
			वापस false;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

व्योम ath9k_hw_usb_gen_fill_eeprom(काष्ठा ath_hw *ah, u16 *eep_data,
				  पूर्णांक eep_start_loc, पूर्णांक size)
अणु
	पूर्णांक i = 0, j, addr;
	u32 addrdata[8];
	u32 data[8];

	क्रम (addr = 0; addr < size; addr++) अणु
		addrdata[i] = AR5416_EEPROM_OFFSET +
			((addr + eep_start_loc) << AR5416_EEPROM_S);
		i++;
		अगर (i == 8) अणु
			REG_READ_MULTI(ah, addrdata, data, i);

			क्रम (j = 0; j < i; j++) अणु
				*eep_data = data[j];
				eep_data++;
			पूर्ण
			i = 0;
		पूर्ण
	पूर्ण

	अगर (i != 0) अणु
		REG_READ_MULTI(ah, addrdata, data, i);

		क्रम (j = 0; j < i; j++) अणु
			*eep_data = data[j];
			eep_data++;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ath9k_hw_nvram_पढ़ो_array(u16 *blob, माप_प्रकार blob_size,
				      off_t offset, u16 *data)
अणु
	अगर (offset >= blob_size)
		वापस false;

	*data =  blob[offset];
	वापस true;
पूर्ण

अटल bool ath9k_hw_nvram_पढ़ो_pdata(काष्ठा ath9k_platक्रमm_data *pdata,
				      off_t offset, u16 *data)
अणु
	वापस ath9k_hw_nvram_पढ़ो_array(pdata->eeprom_data,
					 ARRAY_SIZE(pdata->eeprom_data),
					 offset, data);
पूर्ण

अटल bool ath9k_hw_nvram_पढ़ो_firmware(स्थिर काष्ठा firmware *eeprom_blob,
					 off_t offset, u16 *data)
अणु
	वापस ath9k_hw_nvram_पढ़ो_array((u16 *) eeprom_blob->data,
					 eeprom_blob->size / माप(u16),
					 offset, data);
पूर्ण

bool ath9k_hw_nvram_पढ़ो(काष्ठा ath_hw *ah, u32 off, u16 *data)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_platक्रमm_data *pdata = ah->dev->platक्रमm_data;
	bool ret;

	अगर (ah->eeprom_blob)
		ret = ath9k_hw_nvram_पढ़ो_firmware(ah->eeprom_blob, off, data);
	अन्यथा अगर (pdata && !pdata->use_eeprom)
		ret = ath9k_hw_nvram_पढ़ो_pdata(pdata, off, data);
	अन्यथा
		ret = common->bus_ops->eeprom_पढ़ो(common, off, data);

	अगर (!ret)
		ath_dbg(common, EEPROM,
			"unable to read eeprom region at offset %u\n", off);

	वापस ret;
पूर्ण

पूर्णांक ath9k_hw_nvram_swap_data(काष्ठा ath_hw *ah, bool *swap_needed, पूर्णांक size)
अणु
	u16 magic;
	u16 *eepdata;
	पूर्णांक i;
	bool needs_byteswap = false;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!ath9k_hw_nvram_पढ़ो(ah, AR5416_EEPROM_MAGIC_OFFSET, &magic)) अणु
		ath_err(common, "Reading Magic # failed\n");
		वापस -EIO;
	पूर्ण

	अगर (swab16(magic) == AR5416_EEPROM_MAGIC) अणु
		needs_byteswap = true;
		ath_dbg(common, EEPROM,
			"EEPROM needs byte-swapping to correct endianness.\n");
	पूर्ण अन्यथा अगर (magic != AR5416_EEPROM_MAGIC) अणु
		अगर (ath9k_hw_use_flash(ah)) अणु
			ath_dbg(common, EEPROM,
				"Ignoring invalid EEPROM magic (0x%04x).\n",
				magic);
		पूर्ण अन्यथा अणु
			ath_err(common,
				"Invalid EEPROM magic (0x%04x).\n", magic);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (needs_byteswap) अणु
		अगर (ah->ah_flags & AH_NO_EEP_SWAP) अणु
			ath_info(common,
				 "Ignoring endianness difference in EEPROM magic bytes.\n");
		पूर्ण अन्यथा अणु
			eepdata = (u16 *)(&ah->eeprom);

			क्रम (i = 0; i < size; i++)
				eepdata[i] = swab16(eepdata[i]);
		पूर्ण
	पूर्ण

	अगर (ah->eep_ops->get_eepmisc(ah) & AR5416_EEPMISC_BIG_ENDIAN) अणु
		*swap_needed = true;
		ath_dbg(common, EEPROM,
			"Big Endian EEPROM detected according to EEPMISC register.\n");
	पूर्ण अन्यथा अणु
		*swap_needed = false;
	पूर्ण

	वापस 0;
पूर्ण

bool ath9k_hw_nvram_validate_checksum(काष्ठा ath_hw *ah, पूर्णांक size)
अणु
	u32 i, sum = 0;
	u16 *eepdata = (u16 *)(&ah->eeprom);
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	क्रम (i = 0; i < size; i++)
		sum ^= eepdata[i];

	अगर (sum != 0xffff) अणु
		ath_err(common, "Bad EEPROM checksum 0x%x\n", sum);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool ath9k_hw_nvram_check_version(काष्ठा ath_hw *ah, पूर्णांक version, पूर्णांक minrev)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (ah->eep_ops->get_eeprom_ver(ah) != version ||
	    ah->eep_ops->get_eeprom_rev(ah) < minrev) अणु
		ath_err(common, "Bad EEPROM VER 0x%04x or REV 0x%04x\n",
			ah->eep_ops->get_eeprom_ver(ah),
			ah->eep_ops->get_eeprom_rev(ah));
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम ath9k_hw_fill_vpd_table(u8 pwrMin, u8 pwrMax, u8 *pPwrList,
			     u8 *pVpdList, u16 numIntercepts,
			     u8 *pRetVpdList)
अणु
	u16 i, k;
	u8 currPwr = pwrMin;
	u16 idxL = 0, idxR = 0;

	क्रम (i = 0; i <= (pwrMax - pwrMin) / 2; i++) अणु
		ath9k_hw_get_lower_upper_index(currPwr, pPwrList,
					       numIntercepts, &(idxL),
					       &(idxR));
		अगर (idxR < 1)
			idxR = 1;
		अगर (idxL == numIntercepts - 1)
			idxL = (u16) (numIntercepts - 2);
		अगर (pPwrList[idxL] == pPwrList[idxR])
			k = pVpdList[idxL];
		अन्यथा
			k = (u16)(((currPwr - pPwrList[idxL]) * pVpdList[idxR] +
				   (pPwrList[idxR] - currPwr) * pVpdList[idxL]) /
				  (pPwrList[idxR] - pPwrList[idxL]));
		pRetVpdList[i] = (u8) k;
		currPwr += 2;
	पूर्ण
पूर्ण

व्योम ath9k_hw_get_legacy_target_घातers(काष्ठा ath_hw *ah,
				       काष्ठा ath9k_channel *chan,
				       काष्ठा cal_target_घातer_leg *घातInfo,
				       u16 numChannels,
				       काष्ठा cal_target_घातer_leg *pNewPower,
				       u16 numRates, bool isExtTarget)
अणु
	काष्ठा chan_centers centers;
	u16 clo, chi;
	पूर्णांक i;
	पूर्णांक matchIndex = -1, lowIndex = -1;
	u16 freq;

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	freq = (isExtTarget) ? centers.ext_center : centers.ctl_center;

	अगर (freq <= ath9k_hw_fbin2freq(घातInfo[0].bChannel,
				       IS_CHAN_2GHZ(chan))) अणु
		matchIndex = 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; (i < numChannels) &&
			     (घातInfo[i].bChannel != AR5416_BCHAN_UNUSED); i++) अणु
			अगर (freq == ath9k_hw_fbin2freq(घातInfo[i].bChannel,
						       IS_CHAN_2GHZ(chan))) अणु
				matchIndex = i;
				अवरोध;
			पूर्ण अन्यथा अगर (freq < ath9k_hw_fbin2freq(घातInfo[i].bChannel,
						IS_CHAN_2GHZ(chan)) && i > 0 &&
				   freq > ath9k_hw_fbin2freq(घातInfo[i - 1].bChannel,
						IS_CHAN_2GHZ(chan))) अणु
				lowIndex = i - 1;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर ((matchIndex == -1) && (lowIndex == -1))
			matchIndex = i - 1;
	पूर्ण

	अगर (matchIndex != -1) अणु
		*pNewPower = घातInfo[matchIndex];
	पूर्ण अन्यथा अणु
		clo = ath9k_hw_fbin2freq(घातInfo[lowIndex].bChannel,
					 IS_CHAN_2GHZ(chan));
		chi = ath9k_hw_fbin2freq(घातInfo[lowIndex + 1].bChannel,
					 IS_CHAN_2GHZ(chan));

		क्रम (i = 0; i < numRates; i++) अणु
			pNewPower->tPow2x[i] =
				(u8)ath9k_hw_पूर्णांकerpolate(freq, clo, chi,
						घातInfo[lowIndex].tPow2x[i],
						घातInfo[lowIndex + 1].tPow2x[i]);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ath9k_hw_get_target_घातers(काष्ठा ath_hw *ah,
				काष्ठा ath9k_channel *chan,
				काष्ठा cal_target_घातer_ht *घातInfo,
				u16 numChannels,
				काष्ठा cal_target_घातer_ht *pNewPower,
				u16 numRates, bool isHt40Target)
अणु
	काष्ठा chan_centers centers;
	u16 clo, chi;
	पूर्णांक i;
	पूर्णांक matchIndex = -1, lowIndex = -1;
	u16 freq;

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	freq = isHt40Target ? centers.synth_center : centers.ctl_center;

	अगर (freq <= ath9k_hw_fbin2freq(घातInfo[0].bChannel, IS_CHAN_2GHZ(chan))) अणु
		matchIndex = 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; (i < numChannels) &&
			     (घातInfo[i].bChannel != AR5416_BCHAN_UNUSED); i++) अणु
			अगर (freq == ath9k_hw_fbin2freq(घातInfo[i].bChannel,
						       IS_CHAN_2GHZ(chan))) अणु
				matchIndex = i;
				अवरोध;
			पूर्ण अन्यथा
				अगर (freq < ath9k_hw_fbin2freq(घातInfo[i].bChannel,
						IS_CHAN_2GHZ(chan)) && i > 0 &&
				    freq > ath9k_hw_fbin2freq(घातInfo[i - 1].bChannel,
						IS_CHAN_2GHZ(chan))) अणु
					lowIndex = i - 1;
					अवरोध;
				पूर्ण
		पूर्ण
		अगर ((matchIndex == -1) && (lowIndex == -1))
			matchIndex = i - 1;
	पूर्ण

	अगर (matchIndex != -1) अणु
		*pNewPower = घातInfo[matchIndex];
	पूर्ण अन्यथा अणु
		clo = ath9k_hw_fbin2freq(घातInfo[lowIndex].bChannel,
					 IS_CHAN_2GHZ(chan));
		chi = ath9k_hw_fbin2freq(घातInfo[lowIndex + 1].bChannel,
					 IS_CHAN_2GHZ(chan));

		क्रम (i = 0; i < numRates; i++) अणु
			pNewPower->tPow2x[i] = (u8)ath9k_hw_पूर्णांकerpolate(freq,
						clo, chi,
						घातInfo[lowIndex].tPow2x[i],
						घातInfo[lowIndex + 1].tPow2x[i]);
		पूर्ण
	पूर्ण
पूर्ण

u16 ath9k_hw_get_max_edge_घातer(u16 freq, काष्ठा cal_ctl_edges *pRdEdgesPower,
				bool is2GHz, पूर्णांक num_band_edges)
अणु
	u16 twiceMaxEdgePower = MAX_RATE_POWER;
	पूर्णांक i;

	क्रम (i = 0; (i < num_band_edges) &&
		     (pRdEdgesPower[i].bChannel != AR5416_BCHAN_UNUSED); i++) अणु
		अगर (freq == ath9k_hw_fbin2freq(pRdEdgesPower[i].bChannel, is2GHz)) अणु
			twiceMaxEdgePower = CTL_EDGE_TPOWER(pRdEdgesPower[i].ctl);
			अवरोध;
		पूर्ण अन्यथा अगर ((i > 0) &&
			   (freq < ath9k_hw_fbin2freq(pRdEdgesPower[i].bChannel,
						      is2GHz))) अणु
			अगर (ath9k_hw_fbin2freq(pRdEdgesPower[i - 1].bChannel,
					       is2GHz) < freq &&
			    CTL_EDGE_FLAGS(pRdEdgesPower[i - 1].ctl)) अणु
				twiceMaxEdgePower =
					CTL_EDGE_TPOWER(pRdEdgesPower[i - 1].ctl);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	वापस twiceMaxEdgePower;
पूर्ण

u16 ath9k_hw_get_scaled_घातer(काष्ठा ath_hw *ah, u16 घातer_limit,
			      u8 antenna_reduction)
अणु
	u16 reduction = antenna_reduction;

	/*
	 * Reduce scaled Power by number of chains active
	 * to get the per chain tx घातer level.
	 */
	चयन (ar5416_get_ntxchains(ah->txchainmask)) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		reduction += POWER_CORRECTION_FOR_TWO_CHAIN;
		अवरोध;
	हाल 3:
		reduction += POWER_CORRECTION_FOR_THREE_CHAIN;
		अवरोध;
	पूर्ण

	अगर (घातer_limit > reduction)
		घातer_limit -= reduction;
	अन्यथा
		घातer_limit = 0;

	वापस min_t(u16, घातer_limit, MAX_RATE_POWER);
पूर्ण

व्योम ath9k_hw_update_regulatory_maxघातer(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_regulatory *regulatory = ath9k_hw_regulatory(ah);

	चयन (ar5416_get_ntxchains(ah->txchainmask)) अणु
	हाल 1:
		अवरोध;
	हाल 2:
		regulatory->max_घातer_level += POWER_CORRECTION_FOR_TWO_CHAIN;
		अवरोध;
	हाल 3:
		regulatory->max_घातer_level += POWER_CORRECTION_FOR_THREE_CHAIN;
		अवरोध;
	शेष:
		ath_dbg(common, EEPROM, "Invalid chainmask configuration\n");
		अवरोध;
	पूर्ण
पूर्ण

व्योम ath9k_hw_get_gain_boundaries_pdadcs(काष्ठा ath_hw *ah,
				काष्ठा ath9k_channel *chan,
				व्योम *pRawDataSet,
				u8 *bChans, u16 availPiers,
				u16 tPdGainOverlap,
				u16 *pPdGainBoundaries, u8 *pPDADCValues,
				u16 numXpdGains)
अणु
	पूर्णांक i, j, k;
	पूर्णांक16_t ss;
	u16 idxL = 0, idxR = 0, numPiers;
	अटल u8 vpdTableL[AR5416_NUM_PD_GAINS]
		[AR5416_MAX_PWR_RANGE_IN_HALF_DB];
	अटल u8 vpdTableR[AR5416_NUM_PD_GAINS]
		[AR5416_MAX_PWR_RANGE_IN_HALF_DB];
	अटल u8 vpdTableI[AR5416_NUM_PD_GAINS]
		[AR5416_MAX_PWR_RANGE_IN_HALF_DB];

	u8 *pVpdL, *pVpdR, *pPwrL, *pPwrR;
	u8 minPwrT4[AR5416_NUM_PD_GAINS];
	u8 maxPwrT4[AR5416_NUM_PD_GAINS];
	पूर्णांक16_t vpdStep;
	पूर्णांक16_t पंचांगpVal;
	u16 sizeCurrVpdTable, maxIndex, tgtIndex;
	bool match;
	पूर्णांक16_t minDelta = 0;
	काष्ठा chan_centers centers;
	पूर्णांक pdgain_boundary_शेष;
	काष्ठा cal_data_per_freq *data_def = pRawDataSet;
	काष्ठा cal_data_per_freq_4k *data_4k = pRawDataSet;
	काष्ठा cal_data_per_freq_ar9287 *data_9287 = pRawDataSet;
	bool eeprom_4k = AR_SREV_9285(ah) || AR_SREV_9271(ah);
	पूर्णांक पूर्णांकercepts;

	अगर (AR_SREV_9287(ah))
		पूर्णांकercepts = AR9287_PD_GAIN_ICEPTS;
	अन्यथा
		पूर्णांकercepts = AR5416_PD_GAIN_ICEPTS;

	स_रखो(&minPwrT4, 0, AR5416_NUM_PD_GAINS);
	ath9k_hw_get_channel_centers(ah, chan, &centers);

	क्रम (numPiers = 0; numPiers < availPiers; numPiers++) अणु
		अगर (bChans[numPiers] == AR5416_BCHAN_UNUSED)
			अवरोध;
	पूर्ण

	match = ath9k_hw_get_lower_upper_index((u8)FREQ2FBIN(centers.synth_center,
							     IS_CHAN_2GHZ(chan)),
					       bChans, numPiers, &idxL, &idxR);

	अगर (match) अणु
		अगर (AR_SREV_9287(ah)) अणु
			क्रम (i = 0; i < numXpdGains; i++) अणु
				minPwrT4[i] = data_9287[idxL].pwrPdg[i][0];
				maxPwrT4[i] = data_9287[idxL].pwrPdg[i][पूर्णांकercepts - 1];
				ath9k_hw_fill_vpd_table(minPwrT4[i], maxPwrT4[i],
						data_9287[idxL].pwrPdg[i],
						data_9287[idxL].vpdPdg[i],
						पूर्णांकercepts,
						vpdTableI[i]);
			पूर्ण
		पूर्ण अन्यथा अगर (eeprom_4k) अणु
			क्रम (i = 0; i < numXpdGains; i++) अणु
				minPwrT4[i] = data_4k[idxL].pwrPdg[i][0];
				maxPwrT4[i] = data_4k[idxL].pwrPdg[i][पूर्णांकercepts - 1];
				ath9k_hw_fill_vpd_table(minPwrT4[i], maxPwrT4[i],
						data_4k[idxL].pwrPdg[i],
						data_4k[idxL].vpdPdg[i],
						पूर्णांकercepts,
						vpdTableI[i]);
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < numXpdGains; i++) अणु
				minPwrT4[i] = data_def[idxL].pwrPdg[i][0];
				maxPwrT4[i] = data_def[idxL].pwrPdg[i][पूर्णांकercepts - 1];
				ath9k_hw_fill_vpd_table(minPwrT4[i], maxPwrT4[i],
						data_def[idxL].pwrPdg[i],
						data_def[idxL].vpdPdg[i],
						पूर्णांकercepts,
						vpdTableI[i]);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < numXpdGains; i++) अणु
			अगर (AR_SREV_9287(ah)) अणु
				pVpdL = data_9287[idxL].vpdPdg[i];
				pPwrL = data_9287[idxL].pwrPdg[i];
				pVpdR = data_9287[idxR].vpdPdg[i];
				pPwrR = data_9287[idxR].pwrPdg[i];
			पूर्ण अन्यथा अगर (eeprom_4k) अणु
				pVpdL = data_4k[idxL].vpdPdg[i];
				pPwrL = data_4k[idxL].pwrPdg[i];
				pVpdR = data_4k[idxR].vpdPdg[i];
				pPwrR = data_4k[idxR].pwrPdg[i];
			पूर्ण अन्यथा अणु
				pVpdL = data_def[idxL].vpdPdg[i];
				pPwrL = data_def[idxL].pwrPdg[i];
				pVpdR = data_def[idxR].vpdPdg[i];
				pPwrR = data_def[idxR].pwrPdg[i];
			पूर्ण

			minPwrT4[i] = max(pPwrL[0], pPwrR[0]);

			maxPwrT4[i] =
				min(pPwrL[पूर्णांकercepts - 1],
				    pPwrR[पूर्णांकercepts - 1]);


			ath9k_hw_fill_vpd_table(minPwrT4[i], maxPwrT4[i],
						pPwrL, pVpdL,
						पूर्णांकercepts,
						vpdTableL[i]);
			ath9k_hw_fill_vpd_table(minPwrT4[i], maxPwrT4[i],
						pPwrR, pVpdR,
						पूर्णांकercepts,
						vpdTableR[i]);

			क्रम (j = 0; j <= (maxPwrT4[i] - minPwrT4[i]) / 2; j++) अणु
				vpdTableI[i][j] =
					(u8)(ath9k_hw_पूर्णांकerpolate((u16)
					     FREQ2FBIN(centers.
						       synth_center,
						       IS_CHAN_2GHZ
						       (chan)),
					     bChans[idxL], bChans[idxR],
					     vpdTableL[i][j], vpdTableR[i][j]));
			पूर्ण
		पूर्ण
	पूर्ण

	k = 0;

	क्रम (i = 0; i < numXpdGains; i++) अणु
		अगर (i == (numXpdGains - 1))
			pPdGainBoundaries[i] =
				(u16)(maxPwrT4[i] / 2);
		अन्यथा
			pPdGainBoundaries[i] =
				(u16)((maxPwrT4[i] + minPwrT4[i + 1]) / 4);

		pPdGainBoundaries[i] =
			min((u16)MAX_RATE_POWER, pPdGainBoundaries[i]);

		minDelta = 0;

		अगर (i == 0) अणु
			अगर (AR_SREV_9280_20_OR_LATER(ah))
				ss = (पूर्णांक16_t)(0 - (minPwrT4[i] / 2));
			अन्यथा
				ss = 0;
		पूर्ण अन्यथा अणु
			ss = (पूर्णांक16_t)((pPdGainBoundaries[i - 1] -
					(minPwrT4[i] / 2)) -
				       tPdGainOverlap + 1 + minDelta);
		पूर्ण
		vpdStep = (पूर्णांक16_t)(vpdTableI[i][1] - vpdTableI[i][0]);
		vpdStep = (पूर्णांक16_t)((vpdStep < 1) ? 1 : vpdStep);

		जबतक ((ss < 0) && (k < (AR5416_NUM_PDADC_VALUES - 1))) अणु
			पंचांगpVal = (पूर्णांक16_t)(vpdTableI[i][0] + ss * vpdStep);
			pPDADCValues[k++] = (u8)((पंचांगpVal < 0) ? 0 : पंचांगpVal);
			ss++;
		पूर्ण

		sizeCurrVpdTable = (u8) ((maxPwrT4[i] - minPwrT4[i]) / 2 + 1);
		tgtIndex = (u8)(pPdGainBoundaries[i] + tPdGainOverlap -
				(minPwrT4[i] / 2));
		maxIndex = (tgtIndex < sizeCurrVpdTable) ?
			tgtIndex : sizeCurrVpdTable;

		जबतक ((ss < maxIndex) && (k < (AR5416_NUM_PDADC_VALUES - 1))) अणु
			pPDADCValues[k++] = vpdTableI[i][ss++];
		पूर्ण

		vpdStep = (पूर्णांक16_t)(vpdTableI[i][sizeCurrVpdTable - 1] -
				    vpdTableI[i][sizeCurrVpdTable - 2]);
		vpdStep = (पूर्णांक16_t)((vpdStep < 1) ? 1 : vpdStep);

		अगर (tgtIndex >= maxIndex) अणु
			जबतक ((ss <= tgtIndex) &&
			       (k < (AR5416_NUM_PDADC_VALUES - 1))) अणु
				पंचांगpVal = (पूर्णांक16_t)((vpdTableI[i][sizeCurrVpdTable - 1] +
						    (ss - maxIndex + 1) * vpdStep));
				pPDADCValues[k++] = (u8)((पंचांगpVal > 255) ?
							 255 : पंचांगpVal);
				ss++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (eeprom_4k)
		pdgain_boundary_शेष = 58;
	अन्यथा
		pdgain_boundary_शेष = pPdGainBoundaries[i - 1];

	जबतक (i < AR5416_PD_GAINS_IN_MASK) अणु
		pPdGainBoundaries[i] = pdgain_boundary_शेष;
		i++;
	पूर्ण

	जबतक (k < AR5416_NUM_PDADC_VALUES) अणु
		pPDADCValues[k] = pPDADCValues[k - 1];
		k++;
	पूर्ण
पूर्ण

पूर्णांक ath9k_hw_eeprom_init(काष्ठा ath_hw *ah)
अणु
	पूर्णांक status;

	अगर (AR_SREV_9300_20_OR_LATER(ah))
		ah->eep_ops = &eep_ar9300_ops;
	अन्यथा अगर (AR_SREV_9287(ah)) अणु
		ah->eep_ops = &eep_ar9287_ops;
	पूर्ण अन्यथा अगर (AR_SREV_9285(ah) || AR_SREV_9271(ah)) अणु
		ah->eep_ops = &eep_4k_ops;
	पूर्ण अन्यथा अणु
		ah->eep_ops = &eep_def_ops;
	पूर्ण

	अगर (!ah->eep_ops->fill_eeprom(ah))
		वापस -EIO;

	status = ah->eep_ops->check_eeprom(ah);

	वापस status;
पूर्ण
