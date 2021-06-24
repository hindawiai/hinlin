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

#समावेश <यंत्र/unaligned.h>
#समावेश "hw.h"
#समावेश "ar9002_phy.h"

अटल व्योम ath9k_get_txgain_index(काष्ठा ath_hw *ah,
		काष्ठा ath9k_channel *chan,
		काष्ठा calDataPerFreqOpLoop *rawDatasetOpLoop,
		u8 *calChans,  u16 availPiers, u8 *pwr, u8 *pcdacIdx)
अणु
	u8 pcdac, i = 0;
	u16 idxL = 0, idxR = 0, numPiers;
	bool match;
	काष्ठा chan_centers centers;

	ath9k_hw_get_channel_centers(ah, chan, &centers);

	क्रम (numPiers = 0; numPiers < availPiers; numPiers++)
		अगर (calChans[numPiers] == AR5416_BCHAN_UNUSED)
			अवरोध;

	match = ath9k_hw_get_lower_upper_index(
			(u8)FREQ2FBIN(centers.synth_center, IS_CHAN_2GHZ(chan)),
			calChans, numPiers, &idxL, &idxR);
	अगर (match) अणु
		pcdac = rawDatasetOpLoop[idxL].pcdac[0][0];
		*pwr = rawDatasetOpLoop[idxL].pwrPdg[0][0];
	पूर्ण अन्यथा अणु
		pcdac = rawDatasetOpLoop[idxR].pcdac[0][0];
		*pwr = (rawDatasetOpLoop[idxL].pwrPdg[0][0] +
				rawDatasetOpLoop[idxR].pwrPdg[0][0])/2;
	पूर्ण

	जबतक (pcdac > ah->originalGain[i] &&
			i < (AR9280_TX_GAIN_TABLE_SIZE - 1))
		i++;

	*pcdacIdx = i;
पूर्ण

अटल व्योम ath9k_olc_get_pdadcs(काष्ठा ath_hw *ah,
				u32 initTxGain,
				पूर्णांक txPower,
				u8 *pPDADCValues)
अणु
	u32 i;
	u32 offset;

	REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL6_0,
			AR_PHY_TX_PWRCTRL_ERR_EST_MODE, 3);
	REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL6_1,
			AR_PHY_TX_PWRCTRL_ERR_EST_MODE, 3);

	REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL7,
			AR_PHY_TX_PWRCTRL_INIT_TX_GAIN, initTxGain);

	offset = txPower;
	क्रम (i = 0; i < AR5416_NUM_PDADC_VALUES; i++)
		अगर (i < offset)
			pPDADCValues[i] = 0x0;
		अन्यथा
			pPDADCValues[i] = 0xFF;
पूर्ण

अटल पूर्णांक ath9k_hw_def_get_eeprom_ver(काष्ठा ath_hw *ah)
अणु
	u16 version = le16_to_cpu(ah->eeprom.def.baseEepHeader.version);

	वापस (version & AR5416_EEP_VER_MAJOR_MASK) >>
		AR5416_EEP_VER_MAJOR_SHIFT;
पूर्ण

अटल पूर्णांक ath9k_hw_def_get_eeprom_rev(काष्ठा ath_hw *ah)
अणु
	u16 version = le16_to_cpu(ah->eeprom.def.baseEepHeader.version);

	वापस version & AR5416_EEP_VER_MINOR_MASK;
पूर्ण

#घोषणा SIZE_EEPROM_DEF (माप(काष्ठा ar5416_eeprom_def) / माप(u16))

अटल bool __ath9k_hw_def_fill_eeprom(काष्ठा ath_hw *ah)
अणु
	u16 *eep_data = (u16 *)&ah->eeprom.def;
	पूर्णांक addr, ar5416_eep_start_loc = 0x100;

	क्रम (addr = 0; addr < SIZE_EEPROM_DEF; addr++) अणु
		अगर (!ath9k_hw_nvram_पढ़ो(ah, addr + ar5416_eep_start_loc,
					 eep_data))
			वापस false;
		eep_data++;
	पूर्ण
	वापस true;
पूर्ण

अटल bool __ath9k_hw_usb_def_fill_eeprom(काष्ठा ath_hw *ah)
अणु
	u16 *eep_data = (u16 *)&ah->eeprom.def;

	ath9k_hw_usb_gen_fill_eeprom(ah, eep_data,
				     0x100, SIZE_EEPROM_DEF);
	वापस true;
पूर्ण

अटल bool ath9k_hw_def_fill_eeprom(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!ath9k_hw_use_flash(ah)) अणु
		ath_dbg(common, EEPROM, "Reading from EEPROM, not flash\n");
	पूर्ण

	अगर (common->bus_ops->ath_bus_type == ATH_USB)
		वापस __ath9k_hw_usb_def_fill_eeprom(ah);
	अन्यथा
		वापस __ath9k_hw_def_fill_eeprom(ah);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_COMMON_DEBUG
अटल u32 ath9k_def_dump_modal_eeprom(अक्षर *buf, u32 len, u32 size,
				       काष्ठा modal_eep_header *modal_hdr)
अणु
	PR_EEP("Chain0 Ant. Control", le16_to_cpu(modal_hdr->antCtrlChain[0]));
	PR_EEP("Chain1 Ant. Control", le16_to_cpu(modal_hdr->antCtrlChain[1]));
	PR_EEP("Chain2 Ant. Control", le16_to_cpu(modal_hdr->antCtrlChain[2]));
	PR_EEP("Ant. Common Control", le32_to_cpu(modal_hdr->antCtrlCommon));
	PR_EEP("Chain0 Ant. Gain", modal_hdr->antennaGainCh[0]);
	PR_EEP("Chain1 Ant. Gain", modal_hdr->antennaGainCh[1]);
	PR_EEP("Chain2 Ant. Gain", modal_hdr->antennaGainCh[2]);
	PR_EEP("Switch Settle", modal_hdr->चयनSettling);
	PR_EEP("Chain0 TxRxAtten", modal_hdr->txRxAttenCh[0]);
	PR_EEP("Chain1 TxRxAtten", modal_hdr->txRxAttenCh[1]);
	PR_EEP("Chain2 TxRxAtten", modal_hdr->txRxAttenCh[2]);
	PR_EEP("Chain0 RxTxMargin", modal_hdr->rxTxMarginCh[0]);
	PR_EEP("Chain1 RxTxMargin", modal_hdr->rxTxMarginCh[1]);
	PR_EEP("Chain2 RxTxMargin", modal_hdr->rxTxMarginCh[2]);
	PR_EEP("ADC Desired size", modal_hdr->adcDesiredSize);
	PR_EEP("PGA Desired size", modal_hdr->pgaDesiredSize);
	PR_EEP("Chain0 xlna Gain", modal_hdr->xlnaGainCh[0]);
	PR_EEP("Chain1 xlna Gain", modal_hdr->xlnaGainCh[1]);
	PR_EEP("Chain2 xlna Gain", modal_hdr->xlnaGainCh[2]);
	PR_EEP("txEndToXpaOff", modal_hdr->txEndToXpaOff);
	PR_EEP("txEndToRxOn", modal_hdr->txEndToRxOn);
	PR_EEP("txFrameToXpaOn", modal_hdr->txFrameToXpaOn);
	PR_EEP("CCA Threshold)", modal_hdr->thresh62);
	PR_EEP("Chain0 NF Threshold", modal_hdr->noiseFloorThreshCh[0]);
	PR_EEP("Chain1 NF Threshold", modal_hdr->noiseFloorThreshCh[1]);
	PR_EEP("Chain2 NF Threshold", modal_hdr->noiseFloorThreshCh[2]);
	PR_EEP("xpdGain", modal_hdr->xpdGain);
	PR_EEP("External PD", modal_hdr->xpd);
	PR_EEP("Chain0 I Coefficient", modal_hdr->iqCalICh[0]);
	PR_EEP("Chain1 I Coefficient", modal_hdr->iqCalICh[1]);
	PR_EEP("Chain2 I Coefficient", modal_hdr->iqCalICh[2]);
	PR_EEP("Chain0 Q Coefficient", modal_hdr->iqCalQCh[0]);
	PR_EEP("Chain1 Q Coefficient", modal_hdr->iqCalQCh[1]);
	PR_EEP("Chain2 Q Coefficient", modal_hdr->iqCalQCh[2]);
	PR_EEP("pdGainOverlap", modal_hdr->pdGainOverlap);
	PR_EEP("Chain0 OutputBias", modal_hdr->ob);
	PR_EEP("Chain0 DriverBias", modal_hdr->db);
	PR_EEP("xPA Bias Level", modal_hdr->xpaBiasLvl);
	PR_EEP("2chain pwr decrease", modal_hdr->pwrDecreaseFor2Chain);
	PR_EEP("3chain pwr decrease", modal_hdr->pwrDecreaseFor3Chain);
	PR_EEP("txFrameToDataStart", modal_hdr->txFrameToDataStart);
	PR_EEP("txFrameToPaOn", modal_hdr->txFrameToPaOn);
	PR_EEP("HT40 Power Inc.", modal_hdr->ht40PowerIncForPdadc);
	PR_EEP("Chain0 bswAtten", modal_hdr->bswAtten[0]);
	PR_EEP("Chain1 bswAtten", modal_hdr->bswAtten[1]);
	PR_EEP("Chain2 bswAtten", modal_hdr->bswAtten[2]);
	PR_EEP("Chain0 bswMargin", modal_hdr->bswMargin[0]);
	PR_EEP("Chain1 bswMargin", modal_hdr->bswMargin[1]);
	PR_EEP("Chain2 bswMargin", modal_hdr->bswMargin[2]);
	PR_EEP("HT40 Switch Settle", modal_hdr->swSettleHt40);
	PR_EEP("Chain0 xatten2Db", modal_hdr->xatten2Db[0]);
	PR_EEP("Chain1 xatten2Db", modal_hdr->xatten2Db[1]);
	PR_EEP("Chain2 xatten2Db", modal_hdr->xatten2Db[2]);
	PR_EEP("Chain0 xatten2Margin", modal_hdr->xatten2Margin[0]);
	PR_EEP("Chain1 xatten2Margin", modal_hdr->xatten2Margin[1]);
	PR_EEP("Chain2 xatten2Margin", modal_hdr->xatten2Margin[2]);
	PR_EEP("Chain1 OutputBias", modal_hdr->ob_ch1);
	PR_EEP("Chain1 DriverBias", modal_hdr->db_ch1);
	PR_EEP("LNA Control", modal_hdr->lna_ctl);
	PR_EEP("XPA Bias Freq0", le16_to_cpu(modal_hdr->xpaBiasLvlFreq[0]));
	PR_EEP("XPA Bias Freq1", le16_to_cpu(modal_hdr->xpaBiasLvlFreq[1]));
	PR_EEP("XPA Bias Freq2", le16_to_cpu(modal_hdr->xpaBiasLvlFreq[2]));

	वापस len;
पूर्ण

अटल u32 ath9k_hw_def_dump_eeprom(काष्ठा ath_hw *ah, bool dump_base_hdr,
				    u8 *buf, u32 len, u32 size)
अणु
	काष्ठा ar5416_eeprom_def *eep = &ah->eeprom.def;
	काष्ठा base_eep_header *pBase = &eep->baseEepHeader;
	u32 binBuildNumber = le32_to_cpu(pBase->binBuildNumber);

	अगर (!dump_base_hdr) अणु
		len += scnम_लिखो(buf + len, size - len,
				 "%20s :\n", "2GHz modal Header");
		len = ath9k_def_dump_modal_eeprom(buf, len, size,
						   &eep->modalHeader[0]);
		len += scnम_लिखो(buf + len, size - len,
				 "%20s :\n", "5GHz modal Header");
		len = ath9k_def_dump_modal_eeprom(buf, len, size,
						   &eep->modalHeader[1]);
		जाओ out;
	पूर्ण

	PR_EEP("Major Version", ath9k_hw_def_get_eeprom_ver(ah));
	PR_EEP("Minor Version", ath9k_hw_def_get_eeprom_rev(ah));
	PR_EEP("Checksum", le16_to_cpu(pBase->checksum));
	PR_EEP("Length", le16_to_cpu(pBase->length));
	PR_EEP("RegDomain1", le16_to_cpu(pBase->regDmn[0]));
	PR_EEP("RegDomain2", le16_to_cpu(pBase->regDmn[1]));
	PR_EEP("TX Mask", pBase->txMask);
	PR_EEP("RX Mask", pBase->rxMask);
	PR_EEP("Allow 5GHz", !!(pBase->opCapFlags & AR5416_OPFLAGS_11A));
	PR_EEP("Allow 2GHz", !!(pBase->opCapFlags & AR5416_OPFLAGS_11G));
	PR_EEP("Disable 2GHz HT20", !!(pBase->opCapFlags &
					AR5416_OPFLAGS_N_2G_HT20));
	PR_EEP("Disable 2GHz HT40", !!(pBase->opCapFlags &
					AR5416_OPFLAGS_N_2G_HT40));
	PR_EEP("Disable 5Ghz HT20", !!(pBase->opCapFlags &
					AR5416_OPFLAGS_N_5G_HT20));
	PR_EEP("Disable 5Ghz HT40", !!(pBase->opCapFlags &
					AR5416_OPFLAGS_N_5G_HT40));
	PR_EEP("Big Endian", !!(pBase->eepMisc & AR5416_EEPMISC_BIG_ENDIAN));
	PR_EEP("Cal Bin Major Ver", (binBuildNumber >> 24) & 0xFF);
	PR_EEP("Cal Bin Minor Ver", (binBuildNumber >> 16) & 0xFF);
	PR_EEP("Cal Bin Build", (binBuildNumber >> 8) & 0xFF);
	PR_EEP("OpenLoop Power Ctrl", pBase->खोलोLoopPwrCntl);

	len += scnम_लिखो(buf + len, size - len, "%20s : %pM\n", "MacAddress",
			 pBase->macAddr);

out:
	अगर (len > size)
		len = size;

	वापस len;
पूर्ण
#अन्यथा
अटल u32 ath9k_hw_def_dump_eeprom(काष्ठा ath_hw *ah, bool dump_base_hdr,
				    u8 *buf, u32 len, u32 size)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ath9k_hw_def_check_eeprom(काष्ठा ath_hw *ah)
अणु
	काष्ठा ar5416_eeprom_def *eep = &ah->eeprom.def;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 el;
	bool need_swap;
	पूर्णांक i, err;

	err = ath9k_hw_nvram_swap_data(ah, &need_swap, SIZE_EEPROM_DEF);
	अगर (err)
		वापस err;

	अगर (need_swap)
		el = swab16((__क्रमce u16)eep->baseEepHeader.length);
	अन्यथा
		el = le16_to_cpu(eep->baseEepHeader.length);

	el = min(el / माप(u16), SIZE_EEPROM_DEF);
	अगर (!ath9k_hw_nvram_validate_checksum(ah, el))
		वापस -EINVAL;

	अगर (need_swap) अणु
		u32 j;

		EEPROM_FIELD_SWAB16(eep->baseEepHeader.length);
		EEPROM_FIELD_SWAB16(eep->baseEepHeader.checksum);
		EEPROM_FIELD_SWAB16(eep->baseEepHeader.version);
		EEPROM_FIELD_SWAB16(eep->baseEepHeader.regDmn[0]);
		EEPROM_FIELD_SWAB16(eep->baseEepHeader.regDmn[1]);
		EEPROM_FIELD_SWAB16(eep->baseEepHeader.rfSilent);
		EEPROM_FIELD_SWAB16(eep->baseEepHeader.blueToothOptions);
		EEPROM_FIELD_SWAB16(eep->baseEepHeader.deviceCap);

		क्रम (j = 0; j < ARRAY_SIZE(eep->modalHeader); j++) अणु
			काष्ठा modal_eep_header *pModal =
				&eep->modalHeader[j];
			EEPROM_FIELD_SWAB32(pModal->antCtrlCommon);

			क्रम (i = 0; i < AR5416_MAX_CHAINS; i++)
				EEPROM_FIELD_SWAB32(pModal->antCtrlChain[i]);

			क्रम (i = 0; i < 3; i++)
				EEPROM_FIELD_SWAB16(pModal->xpaBiasLvlFreq[i]);

			क्रम (i = 0; i < AR_EEPROM_MODAL_SPURS; i++)
				EEPROM_FIELD_SWAB16(
					pModal->spurChans[i].spurChan);
		पूर्ण
	पूर्ण

	अगर (!ath9k_hw_nvram_check_version(ah, AR5416_EEP_VER,
	    AR5416_EEP_NO_BACK_VER))
		वापस -EINVAL;

	/* Enable fixup क्रम AR_AN_TOP2 अगर necessary */
	अगर ((ah->hw_version.devid == AR9280_DEVID_PCI) &&
	    ((le16_to_cpu(eep->baseEepHeader.version) & 0xff) > 0x0a) &&
	    (eep->baseEepHeader.pwdclkind == 0))
		ah->need_an_top2_fixup = true;

	अगर ((common->bus_ops->ath_bus_type == ATH_USB) &&
	    (AR_SREV_9280(ah)))
		eep->modalHeader[0].xpaBiasLvl = 0;

	वापस 0;
पूर्ण

#अघोषित SIZE_EEPROM_DEF

अटल u32 ath9k_hw_def_get_eeprom(काष्ठा ath_hw *ah,
				   क्रमागत eeprom_param param)
अणु
	काष्ठा ar5416_eeprom_def *eep = &ah->eeprom.def;
	काष्ठा modal_eep_header *pModal = eep->modalHeader;
	काष्ठा base_eep_header *pBase = &eep->baseEepHeader;
	पूर्णांक band = 0;

	चयन (param) अणु
	हाल EEP_NFTHRESH_5:
		वापस pModal[0].noiseFloorThreshCh[0];
	हाल EEP_NFTHRESH_2:
		वापस pModal[1].noiseFloorThreshCh[0];
	हाल EEP_MAC_LSW:
		वापस get_unaligned_be16(pBase->macAddr);
	हाल EEP_MAC_MID:
		वापस get_unaligned_be16(pBase->macAddr + 2);
	हाल EEP_MAC_MSW:
		वापस get_unaligned_be16(pBase->macAddr + 4);
	हाल EEP_REG_0:
		वापस le16_to_cpu(pBase->regDmn[0]);
	हाल EEP_OP_CAP:
		वापस le16_to_cpu(pBase->deviceCap);
	हाल EEP_OP_MODE:
		वापस pBase->opCapFlags;
	हाल EEP_RF_SILENT:
		वापस le16_to_cpu(pBase->rfSilent);
	हाल EEP_OB_5:
		वापस pModal[0].ob;
	हाल EEP_DB_5:
		वापस pModal[0].db;
	हाल EEP_OB_2:
		वापस pModal[1].ob;
	हाल EEP_DB_2:
		वापस pModal[1].db;
	हाल EEP_TX_MASK:
		वापस pBase->txMask;
	हाल EEP_RX_MASK:
		वापस pBase->rxMask;
	हाल EEP_FSTCLK_5G:
		वापस pBase->fastClk5g;
	हाल EEP_RXGAIN_TYPE:
		वापस pBase->rxGainType;
	हाल EEP_TXGAIN_TYPE:
		वापस pBase->txGainType;
	हाल EEP_OL_PWRCTRL:
		अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_19)
			वापस pBase->खोलोLoopPwrCntl ? true : false;
		अन्यथा
			वापस false;
	हाल EEP_RC_CHAIN_MASK:
		अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_19)
			वापस pBase->rcChainMask;
		अन्यथा
			वापस 0;
	हाल EEP_DAC_HPWR_5G:
		अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_20)
			वापस pBase->dacHiPwrMode_5G;
		अन्यथा
			वापस 0;
	हाल EEP_FRAC_N_5G:
		अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_22)
			वापस pBase->frac_n_5g;
		अन्यथा
			वापस 0;
	हाल EEP_PWR_TABLE_OFFSET:
		अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_21)
			वापस pBase->pwr_table_offset;
		अन्यथा
			वापस AR5416_PWR_TABLE_OFFSET_DB;
	हाल EEP_ANTENNA_GAIN_2G:
		band = 1;
		fallthrough;
	हाल EEP_ANTENNA_GAIN_5G:
		वापस max_t(u8, max_t(u8,
			pModal[band].antennaGainCh[0],
			pModal[band].antennaGainCh[1]),
			pModal[band].antennaGainCh[2]);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम ath9k_hw_def_set_gain(काष्ठा ath_hw *ah,
				  काष्ठा modal_eep_header *pModal,
				  काष्ठा ar5416_eeprom_def *eep,
				  u8 txRxAttenLocal, पूर्णांक regChainOffset, पूर्णांक i)
अणु
	ENABLE_REG_RMW_BUFFER(ah);
	अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_3) अणु
		txRxAttenLocal = pModal->txRxAttenCh[i];

		अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModal->bswAtten[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_MARGIN,
			      pModal->xatten2Margin[i]);
			REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN2_DB,
			      pModal->xatten2Db[i]);
		पूर्ण अन्यथा अणु
			REG_RMW(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
				SM(pModal-> bswMargin[i], AR_PHY_GAIN_2GHZ_BSW_MARGIN),
				AR_PHY_GAIN_2GHZ_BSW_MARGIN);
			REG_RMW(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
				SM(pModal->bswAtten[i], AR_PHY_GAIN_2GHZ_BSW_ATTEN),
				AR_PHY_GAIN_2GHZ_BSW_ATTEN);
		पूर्ण
	पूर्ण

	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_ATTEN, txRxAttenLocal);
		REG_RMW_FIELD(ah,
		      AR_PHY_RXGAIN + regChainOffset,
		      AR9280_PHY_RXGAIN_TXRX_MARGIN, pModal->rxTxMarginCh[i]);
	पूर्ण अन्यथा अणु
		REG_RMW(ah, AR_PHY_RXGAIN + regChainOffset,
			SM(txRxAttenLocal, AR_PHY_RXGAIN_TXRX_ATTEN),
			AR_PHY_RXGAIN_TXRX_ATTEN);
		REG_RMW(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			SM(pModal->rxTxMarginCh[i], AR_PHY_GAIN_2GHZ_RXTX_MARGIN),
			AR_PHY_GAIN_2GHZ_RXTX_MARGIN);
	पूर्ण
	REG_RMW_BUFFER_FLUSH(ah);
पूर्ण

अटल व्योम ath9k_hw_def_set_board_values(काष्ठा ath_hw *ah,
					  काष्ठा ath9k_channel *chan)
अणु
	काष्ठा modal_eep_header *pModal;
	काष्ठा ar5416_eeprom_def *eep = &ah->eeprom.def;
	पूर्णांक i, regChainOffset;
	u8 txRxAttenLocal;
	u32 antCtrlCommon;

	pModal = &(eep->modalHeader[IS_CHAN_2GHZ(chan)]);
	txRxAttenLocal = IS_CHAN_2GHZ(chan) ? 23 : 44;
	antCtrlCommon = le32_to_cpu(pModal->antCtrlCommon);

	REG_WRITE(ah, AR_PHY_SWITCH_COM, antCtrlCommon & 0xffff);

	क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
		अगर (AR_SREV_9280(ah)) अणु
			अगर (i >= 2)
				अवरोध;
		पूर्ण

		अगर ((ah->rxchainmask == 5 || ah->txchainmask == 5) && (i != 0))
			regChainOffset = (i == 1) ? 0x2000 : 0x1000;
		अन्यथा
			regChainOffset = i * 0x1000;

		REG_WRITE(ah, AR_PHY_SWITCH_CHAIN_0 + regChainOffset,
			  le32_to_cpu(pModal->antCtrlChain[i]));

		REG_WRITE(ah, AR_PHY_TIMING_CTRL4(0) + regChainOffset,
			  (REG_READ(ah, AR_PHY_TIMING_CTRL4(0) + regChainOffset) &
			   ~(AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF |
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF)) |
			  SM(pModal->iqCalICh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF) |
			  SM(pModal->iqCalQCh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF));

		ath9k_hw_def_set_gain(ah, pModal, eep, txRxAttenLocal,
				      regChainOffset, i);
	पूर्ण

	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		अगर (IS_CHAN_2GHZ(chan)) अणु
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF2G1_CH0,
						  AR_AN_RF2G1_CH0_OB,
						  AR_AN_RF2G1_CH0_OB_S,
						  pModal->ob);
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF2G1_CH0,
						  AR_AN_RF2G1_CH0_DB,
						  AR_AN_RF2G1_CH0_DB_S,
						  pModal->db);
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF2G1_CH1,
						  AR_AN_RF2G1_CH1_OB,
						  AR_AN_RF2G1_CH1_OB_S,
						  pModal->ob_ch1);
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF2G1_CH1,
						  AR_AN_RF2G1_CH1_DB,
						  AR_AN_RF2G1_CH1_DB_S,
						  pModal->db_ch1);
		पूर्ण अन्यथा अणु
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF5G1_CH0,
						  AR_AN_RF5G1_CH0_OB5,
						  AR_AN_RF5G1_CH0_OB5_S,
						  pModal->ob);
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF5G1_CH0,
						  AR_AN_RF5G1_CH0_DB5,
						  AR_AN_RF5G1_CH0_DB5_S,
						  pModal->db);
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF5G1_CH1,
						  AR_AN_RF5G1_CH1_OB5,
						  AR_AN_RF5G1_CH1_OB5_S,
						  pModal->ob_ch1);
			ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_RF5G1_CH1,
						  AR_AN_RF5G1_CH1_DB5,
						  AR_AN_RF5G1_CH1_DB5_S,
						  pModal->db_ch1);
		पूर्ण
		ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_TOP2,
					  AR_AN_TOP2_XPABIAS_LVL,
					  AR_AN_TOP2_XPABIAS_LVL_S,
					  pModal->xpaBiasLvl);
		ath9k_hw_analog_shअगरt_rmw(ah, AR_AN_TOP2,
					  AR_AN_TOP2_LOCALBIAS,
					  AR_AN_TOP2_LOCALBIAS_S,
					  !!(pModal->lna_ctl &
					     LNA_CTL_LOCAL_BIAS));
		REG_RMW_FIELD(ah, AR_PHY_XPA_CFG, AR_PHY_FORCE_XPA_CFG,
			      !!(pModal->lna_ctl & LNA_CTL_FORCE_XPA));
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_SETTLING, AR_PHY_SETTLING_SWITCH,
		      pModal->चयनSettling);
	REG_RMW_FIELD(ah, AR_PHY_DESIRED_SZ, AR_PHY_DESIRED_SZ_ADC,
		      pModal->adcDesiredSize);

	अगर (!AR_SREV_9280_20_OR_LATER(ah))
		REG_RMW_FIELD(ah, AR_PHY_DESIRED_SZ,
			      AR_PHY_DESIRED_SZ_PGA,
			      pModal->pgaDesiredSize);

	REG_WRITE(ah, AR_PHY_RF_CTL4,
		  SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAA_OFF)
		  | SM(pModal->txEndToXpaOff,
		       AR_PHY_RF_CTL4_TX_END_XPAB_OFF)
		  | SM(pModal->txFrameToXpaOn,
		       AR_PHY_RF_CTL4_FRAME_XPAA_ON)
		  | SM(pModal->txFrameToXpaOn,
		       AR_PHY_RF_CTL4_FRAME_XPAB_ON));

	REG_RMW_FIELD(ah, AR_PHY_RF_CTL3, AR_PHY_TX_END_TO_A2_RX_ON,
		      pModal->txEndToRxOn);

	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		REG_RMW_FIELD(ah, AR_PHY_CCA, AR9280_PHY_CCA_THRESH62,
			      pModal->thresh62);
		REG_RMW_FIELD(ah, AR_PHY_EXT_CCA0,
			      AR_PHY_EXT_CCA0_THRESH62,
			      pModal->thresh62);
	पूर्ण अन्यथा अणु
		REG_RMW_FIELD(ah, AR_PHY_CCA, AR_PHY_CCA_THRESH62,
			      pModal->thresh62);
		REG_RMW_FIELD(ah, AR_PHY_EXT_CCA,
			      AR_PHY_EXT_CCA_THRESH62,
			      pModal->thresh62);
	पूर्ण

	अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_2) अणु
		REG_RMW_FIELD(ah, AR_PHY_RF_CTL2,
			      AR_PHY_TX_END_DATA_START,
			      pModal->txFrameToDataStart);
		REG_RMW_FIELD(ah, AR_PHY_RF_CTL2, AR_PHY_TX_END_PA_ON,
			      pModal->txFrameToPaOn);
	पूर्ण

	अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_3) अणु
		अगर (IS_CHAN_HT40(chan))
			REG_RMW_FIELD(ah, AR_PHY_SETTLING,
				      AR_PHY_SETTLING_SWITCH,
				      pModal->swSettleHt40);
	पूर्ण

	अगर (AR_SREV_9280_20_OR_LATER(ah) &&
	    ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_19)
		REG_RMW_FIELD(ah, AR_PHY_CCK_TX_CTRL,
			      AR_PHY_CCK_TX_CTRL_TX_DAC_SCALE_CCK,
			      pModal->miscBits);


	अगर (AR_SREV_9280_20(ah) &&
	    ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_20) अणु
		अगर (IS_CHAN_2GHZ(chan))
			REG_RMW_FIELD(ah, AR_AN_TOP1, AR_AN_TOP1_DACIPMODE,
					eep->baseEepHeader.dacLpMode);
		अन्यथा अगर (eep->baseEepHeader.dacHiPwrMode_5G)
			REG_RMW_FIELD(ah, AR_AN_TOP1, AR_AN_TOP1_DACIPMODE, 0);
		अन्यथा
			REG_RMW_FIELD(ah, AR_AN_TOP1, AR_AN_TOP1_DACIPMODE,
				      eep->baseEepHeader.dacLpMode);

		udelay(100);

		REG_RMW_FIELD(ah, AR_PHY_FRAME_CTL, AR_PHY_FRAME_CTL_TX_CLIP,
			      pModal->miscBits >> 2);

		REG_RMW_FIELD(ah, AR_PHY_TX_PWRCTRL9,
			      AR_PHY_TX_DESIRED_SCALE_CCK,
			      eep->baseEepHeader.desiredScaleCCK);
	पूर्ण
पूर्ण

अटल व्योम ath9k_hw_def_set_addac(काष्ठा ath_hw *ah,
				   काष्ठा ath9k_channel *chan)
अणु
#घोषणा XPA_LVL_FREQ(cnt) (le16_to_cpu(pModal->xpaBiasLvlFreq[cnt]))
	काष्ठा modal_eep_header *pModal;
	काष्ठा ar5416_eeprom_def *eep = &ah->eeprom.def;
	u8 biaslevel;

	अगर (ah->hw_version.macVersion != AR_SREV_VERSION_9160)
		वापस;

	अगर (ah->eep_ops->get_eeprom_rev(ah) < AR5416_EEP_MINOR_VER_7)
		वापस;

	pModal = &(eep->modalHeader[IS_CHAN_2GHZ(chan)]);

	अगर (pModal->xpaBiasLvl != 0xff) अणु
		biaslevel = pModal->xpaBiasLvl;
	पूर्ण अन्यथा अणु
		u16 resetFreqBin, freqBin, freqCount = 0;
		काष्ठा chan_centers centers;

		ath9k_hw_get_channel_centers(ah, chan, &centers);

		resetFreqBin = FREQ2FBIN(centers.synth_center,
					 IS_CHAN_2GHZ(chan));
		freqBin = XPA_LVL_FREQ(0) & 0xff;
		biaslevel = (u8) (XPA_LVL_FREQ(0) >> 14);

		freqCount++;

		जबतक (freqCount < 3) अणु
			अगर (XPA_LVL_FREQ(freqCount) == 0x0)
				अवरोध;

			freqBin = XPA_LVL_FREQ(freqCount) & 0xff;
			अगर (resetFreqBin >= freqBin)
				biaslevel = (u8)(XPA_LVL_FREQ(freqCount) >> 14);
			अन्यथा
				अवरोध;
			freqCount++;
		पूर्ण
	पूर्ण

	अगर (IS_CHAN_2GHZ(chan)) अणु
		INI_RA(&ah->iniAddac, 7, 1) = (INI_RA(&ah->iniAddac,
					7, 1) & (~0x18)) | biaslevel << 3;
	पूर्ण अन्यथा अणु
		INI_RA(&ah->iniAddac, 6, 1) = (INI_RA(&ah->iniAddac,
					6, 1) & (~0xc0)) | biaslevel << 6;
	पूर्ण
#अघोषित XPA_LVL_FREQ
पूर्ण

अटल पूर्णांक16_t ath9k_change_gain_boundary_setting(काष्ठा ath_hw *ah,
				u16 *gb,
				u16 numXpdGain,
				u16 pdGainOverlap_t2,
				पूर्णांक8_t pwr_table_offset,
				पूर्णांक16_t *dअगरf)

अणु
	u16 k;

	/* Prior to writing the boundaries or the pdadc vs. घातer table
	 * पूर्णांकo the chip रेजिस्टरs the शेष starting poपूर्णांक on the pdadc
	 * vs. घातer table needs to be checked and the curve boundaries
	 * adjusted accordingly
	 */
	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		u16 gb_limit;

		अगर (AR5416_PWR_TABLE_OFFSET_DB != pwr_table_offset) अणु
			/* get the dअगरference in dB */
			*dअगरf = (u16)(pwr_table_offset - AR5416_PWR_TABLE_OFFSET_DB);
			/* get the number of half dB steps */
			*dअगरf *= 2;
			/* change the original gain boundary settings
			 * by the number of half dB steps
			 */
			क्रम (k = 0; k < numXpdGain; k++)
				gb[k] = (u16)(gb[k] - *dअगरf);
		पूर्ण
		/* Because of a hardware limitation, ensure the gain boundary
		 * is not larger than (63 - overlap)
		 */
		gb_limit = (u16)(MAX_RATE_POWER - pdGainOverlap_t2);

		क्रम (k = 0; k < numXpdGain; k++)
			gb[k] = (u16)min(gb_limit, gb[k]);
	पूर्ण

	वापस *dअगरf;
पूर्ण

अटल व्योम ath9k_adjust_pdadc_values(काष्ठा ath_hw *ah,
				      पूर्णांक8_t pwr_table_offset,
				      पूर्णांक16_t dअगरf,
				      u8 *pdadcValues)
अणु
#घोषणा NUM_PDADC(dअगरf) (AR5416_NUM_PDADC_VALUES - dअगरf)
	u16 k;

	/* If this is a board that has a pwrTableOffset that dअगरfers from
	 * the शेष AR5416_PWR_TABLE_OFFSET_DB then the start of the
	 * pdadc vs pwr table needs to be adjusted prior to writing to the
	 * chip.
	 */
	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		अगर (AR5416_PWR_TABLE_OFFSET_DB != pwr_table_offset) अणु
			/* shअगरt the table to start at the new offset */
			क्रम (k = 0; k < (u16)NUM_PDADC(dअगरf); k++ ) अणु
				pdadcValues[k] = pdadcValues[k + dअगरf];
			पूर्ण

			/* fill the back of the table */
			क्रम (k = (u16)NUM_PDADC(dअगरf); k < NUM_PDADC(0); k++) अणु
				pdadcValues[k] = pdadcValues[NUM_PDADC(dअगरf)];
			पूर्ण
		पूर्ण
	पूर्ण
#अघोषित NUM_PDADC
पूर्ण

अटल व्योम ath9k_hw_set_def_घातer_cal_table(काष्ठा ath_hw *ah,
				  काष्ठा ath9k_channel *chan)
अणु
#घोषणा SM_PD_GAIN(x) SM(0x38, AR_PHY_TPCRG5_PD_GAIN_BOUNDARY_##x)
#घोषणा SM_PDGAIN_B(x, y) \
		SM((gainBoundaries[x]), AR_PHY_TPCRG5_PD_GAIN_BOUNDARY_##y)
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ar5416_eeprom_def *pEepData = &ah->eeprom.def;
	काष्ठा cal_data_per_freq *pRawDataset;
	u8 *pCalBChans = शून्य;
	u16 pdGainOverlap_t2;
	अटल u8 pdadcValues[AR5416_NUM_PDADC_VALUES];
	u16 gainBoundaries[AR5416_PD_GAINS_IN_MASK];
	u16 numPiers, i, j;
	पूर्णांक16_t dअगरf = 0;
	u16 numXpdGain, xpdMask;
	u16 xpdGainValues[AR5416_NUM_PD_GAINS] = अणु 0, 0, 0, 0 पूर्ण;
	u32 reg32, regOffset, regChainOffset;
	पूर्णांक16_t modalIdx;
	पूर्णांक8_t pwr_table_offset;

	modalIdx = IS_CHAN_2GHZ(chan) ? 1 : 0;
	xpdMask = pEepData->modalHeader[modalIdx].xpdGain;

	pwr_table_offset = ah->eep_ops->get_eeprom(ah, EEP_PWR_TABLE_OFFSET);

	अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_2) अणु
		pdGainOverlap_t2 =
			pEepData->modalHeader[modalIdx].pdGainOverlap;
	पूर्ण अन्यथा अणु
		pdGainOverlap_t2 = (u16)(MS(REG_READ(ah, AR_PHY_TPCRG5),
					    AR_PHY_TPCRG5_PD_GAIN_OVERLAP));
	पूर्ण

	अगर (IS_CHAN_2GHZ(chan)) अणु
		pCalBChans = pEepData->calFreqPier2G;
		numPiers = AR5416_NUM_2G_CAL_PIERS;
	पूर्ण अन्यथा अणु
		pCalBChans = pEepData->calFreqPier5G;
		numPiers = AR5416_NUM_5G_CAL_PIERS;
	पूर्ण

	अगर (OLC_FOR_AR9280_20_LATER && IS_CHAN_2GHZ(chan)) अणु
		pRawDataset = pEepData->calPierData2G[0];
		ah->initPDADC = ((काष्ठा calDataPerFreqOpLoop *)
				 pRawDataset)->vpdPdg[0][0];
	पूर्ण

	numXpdGain = 0;

	क्रम (i = 1; i <= AR5416_PD_GAINS_IN_MASK; i++) अणु
		अगर ((xpdMask >> (AR5416_PD_GAINS_IN_MASK - i)) & 1) अणु
			अगर (numXpdGain >= AR5416_NUM_PD_GAINS)
				अवरोध;
			xpdGainValues[numXpdGain] =
				(u16)(AR5416_PD_GAINS_IN_MASK - i);
			numXpdGain++;
		पूर्ण
	पूर्ण

	REG_RMW_FIELD(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_NUM_PD_GAIN,
		      (numXpdGain - 1) & 0x3);
	REG_RMW_FIELD(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_PD_GAIN_1,
		      xpdGainValues[0]);
	REG_RMW_FIELD(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_PD_GAIN_2,
		      xpdGainValues[1]);
	REG_RMW_FIELD(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_PD_GAIN_3,
		      xpdGainValues[2]);

	क्रम (i = 0; i < AR5416_MAX_CHAINS; i++) अणु
		अगर ((ah->rxchainmask == 5 || ah->txchainmask == 5) &&
		    (i != 0)) अणु
			regChainOffset = (i == 1) ? 0x2000 : 0x1000;
		पूर्ण अन्यथा
			regChainOffset = i * 0x1000;

		अगर (pEepData->baseEepHeader.txMask & (1 << i)) अणु
			अगर (IS_CHAN_2GHZ(chan))
				pRawDataset = pEepData->calPierData2G[i];
			अन्यथा
				pRawDataset = pEepData->calPierData5G[i];


			अगर (OLC_FOR_AR9280_20_LATER) अणु
				u8 pcdacIdx;
				u8 txPower;

				ath9k_get_txgain_index(ah, chan,
				(काष्ठा calDataPerFreqOpLoop *)pRawDataset,
				pCalBChans, numPiers, &txPower, &pcdacIdx);
				ath9k_olc_get_pdadcs(ah, pcdacIdx,
						     txPower/2, pdadcValues);
			पूर्ण अन्यथा अणु
				ath9k_hw_get_gain_boundaries_pdadcs(ah,
							chan, pRawDataset,
							pCalBChans, numPiers,
							pdGainOverlap_t2,
							gainBoundaries,
							pdadcValues,
							numXpdGain);
			पूर्ण

			dअगरf = ath9k_change_gain_boundary_setting(ah,
							   gainBoundaries,
							   numXpdGain,
							   pdGainOverlap_t2,
							   pwr_table_offset,
							   &dअगरf);

			ENABLE_REGWRITE_BUFFER(ah);

			अगर (OLC_FOR_AR9280_20_LATER) अणु
				REG_WRITE(ah,
					AR_PHY_TPCRG5 + regChainOffset,
					SM(0x6,
					AR_PHY_TPCRG5_PD_GAIN_OVERLAP) |
					SM_PD_GAIN(1) | SM_PD_GAIN(2) |
					SM_PD_GAIN(3) | SM_PD_GAIN(4));
			पूर्ण अन्यथा अणु
				REG_WRITE(ah,
					AR_PHY_TPCRG5 + regChainOffset,
					SM(pdGainOverlap_t2,
					AR_PHY_TPCRG5_PD_GAIN_OVERLAP)|
					SM_PDGAIN_B(0, 1) |
					SM_PDGAIN_B(1, 2) |
					SM_PDGAIN_B(2, 3) |
					SM_PDGAIN_B(3, 4));
			पूर्ण

			ath9k_adjust_pdadc_values(ah, pwr_table_offset,
						  dअगरf, pdadcValues);

			regOffset = AR_PHY_BASE + (672 << 2) + regChainOffset;
			क्रम (j = 0; j < 32; j++) अणु
				reg32 = get_unaligned_le32(&pdadcValues[4 * j]);
				REG_WRITE(ah, regOffset, reg32);

				ath_dbg(common, EEPROM,
					"PDADC (%d,%4x): %4.4x %8.8x\n",
					i, regChainOffset, regOffset,
					reg32);
				ath_dbg(common, EEPROM,
					"PDADC: Chain %d | PDADC %3d Value %3d | PDADC %3d Value %3d | PDADC %3d Value %3d | PDADC %3d Value %3d |\n",
					i, 4 * j, pdadcValues[4 * j],
					4 * j + 1, pdadcValues[4 * j + 1],
					4 * j + 2, pdadcValues[4 * j + 2],
					4 * j + 3, pdadcValues[4 * j + 3]);

				regOffset += 4;
			पूर्ण
			REGWRITE_BUFFER_FLUSH(ah);
		पूर्ण
	पूर्ण

#अघोषित SM_PD_GAIN
#अघोषित SM_PDGAIN_B
पूर्ण

अटल व्योम ath9k_hw_set_def_घातer_per_rate_table(काष्ठा ath_hw *ah,
						  काष्ठा ath9k_channel *chan,
						  पूर्णांक16_t *ratesArray,
						  u16 cfgCtl,
						  u16 antenna_reduction,
						  u16 घातerLimit)
अणु
	काष्ठा ar5416_eeprom_def *pEepData = &ah->eeprom.def;
	u16 twiceMaxEdgePower;
	पूर्णांक i;
	काष्ठा cal_ctl_data *rep;
	काष्ठा cal_target_घातer_leg targetPowerOfdm, targetPowerCck = अणु
		0, अणु 0, 0, 0, 0पूर्ण
	पूर्ण;
	काष्ठा cal_target_घातer_leg targetPowerOfdmExt = अणु
		0, अणु 0, 0, 0, 0पूर्ण पूर्ण, targetPowerCckExt = अणु
		0, अणु 0, 0, 0, 0 पूर्ण
	पूर्ण;
	काष्ठा cal_target_घातer_ht targetPowerHt20, targetPowerHt40 = अणु
		0, अणु0, 0, 0, 0पूर्ण
	पूर्ण;
	u16 scaledPower = 0, minCtlPower;
	अटल स्थिर u16 ctlModesFor11a[] = अणु
		CTL_11A, CTL_5GHT20, CTL_11A_EXT, CTL_5GHT40
	पूर्ण;
	अटल स्थिर u16 ctlModesFor11g[] = अणु
		CTL_11B, CTL_11G, CTL_2GHT20,
		CTL_11B_EXT, CTL_11G_EXT, CTL_2GHT40
	पूर्ण;
	u16 numCtlModes;
	स्थिर u16 *pCtlMode;
	u16 ctlMode, freq;
	काष्ठा chan_centers centers;
	पूर्णांक tx_chainmask;
	u16 twiceMinEdgePower;

	tx_chainmask = ah->txchainmask;

	ath9k_hw_get_channel_centers(ah, chan, &centers);

	scaledPower = ath9k_hw_get_scaled_घातer(ah, घातerLimit,
						antenna_reduction);

	अगर (IS_CHAN_2GHZ(chan)) अणु
		numCtlModes = ARRAY_SIZE(ctlModesFor11g) -
			SUB_NUM_CTL_MODES_AT_2G_40;
		pCtlMode = ctlModesFor11g;

		ath9k_hw_get_legacy_target_घातers(ah, chan,
			pEepData->calTargetPowerCck,
			AR5416_NUM_2G_CCK_TARGET_POWERS,
			&targetPowerCck, 4, false);
		ath9k_hw_get_legacy_target_घातers(ah, chan,
			pEepData->calTargetPower2G,
			AR5416_NUM_2G_20_TARGET_POWERS,
			&targetPowerOfdm, 4, false);
		ath9k_hw_get_target_घातers(ah, chan,
			pEepData->calTargetPower2GHT20,
			AR5416_NUM_2G_20_TARGET_POWERS,
			&targetPowerHt20, 8, false);

		अगर (IS_CHAN_HT40(chan)) अणु
			numCtlModes = ARRAY_SIZE(ctlModesFor11g);
			ath9k_hw_get_target_घातers(ah, chan,
				pEepData->calTargetPower2GHT40,
				AR5416_NUM_2G_40_TARGET_POWERS,
				&targetPowerHt40, 8, true);
			ath9k_hw_get_legacy_target_घातers(ah, chan,
				pEepData->calTargetPowerCck,
				AR5416_NUM_2G_CCK_TARGET_POWERS,
				&targetPowerCckExt, 4, true);
			ath9k_hw_get_legacy_target_घातers(ah, chan,
				pEepData->calTargetPower2G,
				AR5416_NUM_2G_20_TARGET_POWERS,
				&targetPowerOfdmExt, 4, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		numCtlModes = ARRAY_SIZE(ctlModesFor11a) -
			SUB_NUM_CTL_MODES_AT_5G_40;
		pCtlMode = ctlModesFor11a;

		ath9k_hw_get_legacy_target_घातers(ah, chan,
			pEepData->calTargetPower5G,
			AR5416_NUM_5G_20_TARGET_POWERS,
			&targetPowerOfdm, 4, false);
		ath9k_hw_get_target_घातers(ah, chan,
			pEepData->calTargetPower5GHT20,
			AR5416_NUM_5G_20_TARGET_POWERS,
			&targetPowerHt20, 8, false);

		अगर (IS_CHAN_HT40(chan)) अणु
			numCtlModes = ARRAY_SIZE(ctlModesFor11a);
			ath9k_hw_get_target_घातers(ah, chan,
				pEepData->calTargetPower5GHT40,
				AR5416_NUM_5G_40_TARGET_POWERS,
				&targetPowerHt40, 8, true);
			ath9k_hw_get_legacy_target_घातers(ah, chan,
				pEepData->calTargetPower5G,
				AR5416_NUM_5G_20_TARGET_POWERS,
				&targetPowerOfdmExt, 4, true);
		पूर्ण
	पूर्ण

	क्रम (ctlMode = 0; ctlMode < numCtlModes; ctlMode++) अणु
		bool isHt40CtlMode = (pCtlMode[ctlMode] == CTL_5GHT40) ||
			(pCtlMode[ctlMode] == CTL_2GHT40);
		अगर (isHt40CtlMode)
			freq = centers.synth_center;
		अन्यथा अगर (pCtlMode[ctlMode] & EXT_ADDITIVE)
			freq = centers.ext_center;
		अन्यथा
			freq = centers.ctl_center;

		twiceMaxEdgePower = MAX_RATE_POWER;

		क्रम (i = 0; (i < AR5416_NUM_CTLS) && pEepData->ctlIndex[i]; i++) अणु
			अगर ((((cfgCtl & ~CTL_MODE_M) |
			      (pCtlMode[ctlMode] & CTL_MODE_M)) ==
			     pEepData->ctlIndex[i]) ||
			    (((cfgCtl & ~CTL_MODE_M) |
			      (pCtlMode[ctlMode] & CTL_MODE_M)) ==
			     ((pEepData->ctlIndex[i] & CTL_MODE_M) | SD_NO_CTL))) अणु
				rep = &(pEepData->ctlData[i]);

				twiceMinEdgePower = ath9k_hw_get_max_edge_घातer(freq,
				rep->ctlEdges[ar5416_get_ntxchains(tx_chainmask) - 1],
				IS_CHAN_2GHZ(chan), AR5416_NUM_BAND_EDGES);

				अगर ((cfgCtl & ~CTL_MODE_M) == SD_NO_CTL) अणु
					twiceMaxEdgePower = min(twiceMaxEdgePower,
								twiceMinEdgePower);
				पूर्ण अन्यथा अणु
					twiceMaxEdgePower = twiceMinEdgePower;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		minCtlPower = min(twiceMaxEdgePower, scaledPower);

		चयन (pCtlMode[ctlMode]) अणु
		हाल CTL_11B:
			क्रम (i = 0; i < ARRAY_SIZE(targetPowerCck.tPow2x); i++) अणु
				targetPowerCck.tPow2x[i] =
					min((u16)targetPowerCck.tPow2x[i],
					    minCtlPower);
			पूर्ण
			अवरोध;
		हाल CTL_11A:
		हाल CTL_11G:
			क्रम (i = 0; i < ARRAY_SIZE(targetPowerOfdm.tPow2x); i++) अणु
				targetPowerOfdm.tPow2x[i] =
					min((u16)targetPowerOfdm.tPow2x[i],
					    minCtlPower);
			पूर्ण
			अवरोध;
		हाल CTL_5GHT20:
		हाल CTL_2GHT20:
			क्रम (i = 0; i < ARRAY_SIZE(targetPowerHt20.tPow2x); i++) अणु
				targetPowerHt20.tPow2x[i] =
					min((u16)targetPowerHt20.tPow2x[i],
					    minCtlPower);
			पूर्ण
			अवरोध;
		हाल CTL_11B_EXT:
			targetPowerCckExt.tPow2x[0] = min((u16)
					targetPowerCckExt.tPow2x[0],
					minCtlPower);
			अवरोध;
		हाल CTL_11A_EXT:
		हाल CTL_11G_EXT:
			targetPowerOfdmExt.tPow2x[0] = min((u16)
					targetPowerOfdmExt.tPow2x[0],
					minCtlPower);
			अवरोध;
		हाल CTL_5GHT40:
		हाल CTL_2GHT40:
			क्रम (i = 0; i < ARRAY_SIZE(targetPowerHt40.tPow2x); i++) अणु
				targetPowerHt40.tPow2x[i] =
					min((u16)targetPowerHt40.tPow2x[i],
					    minCtlPower);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ratesArray[rate6mb] = ratesArray[rate9mb] = ratesArray[rate12mb] =
		ratesArray[rate18mb] = ratesArray[rate24mb] =
		targetPowerOfdm.tPow2x[0];
	ratesArray[rate36mb] = targetPowerOfdm.tPow2x[1];
	ratesArray[rate48mb] = targetPowerOfdm.tPow2x[2];
	ratesArray[rate54mb] = targetPowerOfdm.tPow2x[3];
	ratesArray[rateXr] = targetPowerOfdm.tPow2x[0];

	क्रम (i = 0; i < ARRAY_SIZE(targetPowerHt20.tPow2x); i++)
		ratesArray[rateHt20_0 + i] = targetPowerHt20.tPow2x[i];

	अगर (IS_CHAN_2GHZ(chan)) अणु
		ratesArray[rate1l] = targetPowerCck.tPow2x[0];
		ratesArray[rate2s] = ratesArray[rate2l] =
			targetPowerCck.tPow2x[1];
		ratesArray[rate5_5s] = ratesArray[rate5_5l] =
			targetPowerCck.tPow2x[2];
		ratesArray[rate11s] = ratesArray[rate11l] =
			targetPowerCck.tPow2x[3];
	पूर्ण
	अगर (IS_CHAN_HT40(chan)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(targetPowerHt40.tPow2x); i++) अणु
			ratesArray[rateHt40_0 + i] =
				targetPowerHt40.tPow2x[i];
		पूर्ण
		ratesArray[rateDupOfdm] = targetPowerHt40.tPow2x[0];
		ratesArray[rateDupCck] = targetPowerHt40.tPow2x[0];
		ratesArray[rateExtOfdm] = targetPowerOfdmExt.tPow2x[0];
		अगर (IS_CHAN_2GHZ(chan)) अणु
			ratesArray[rateExtCck] =
				targetPowerCckExt.tPow2x[0];
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath9k_hw_def_set_txघातer(काष्ठा ath_hw *ah,
				    काष्ठा ath9k_channel *chan,
				    u16 cfgCtl,
				    u8 twiceAntennaReduction,
				    u8 घातerLimit, bool test)
अणु
#घोषणा RT_AR_DELTA(x) (ratesArray[x] - cck_ofdm_delta)
	काष्ठा ath_regulatory *regulatory = ath9k_hw_regulatory(ah);
	काष्ठा ar5416_eeprom_def *pEepData = &ah->eeprom.def;
	काष्ठा modal_eep_header *pModal =
		&(pEepData->modalHeader[IS_CHAN_2GHZ(chan)]);
	पूर्णांक16_t ratesArray[Ar5416RateSize];
	u8 ht40PowerIncForPdadc = 2;
	पूर्णांक i, cck_ofdm_delta = 0;

	स_रखो(ratesArray, 0, माप(ratesArray));

	अगर (ath9k_hw_def_get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_2)
		ht40PowerIncForPdadc = pModal->ht40PowerIncForPdadc;

	ath9k_hw_set_def_घातer_per_rate_table(ah, chan,
					       &ratesArray[0], cfgCtl,
					       twiceAntennaReduction,
					       घातerLimit);

	ath9k_hw_set_def_घातer_cal_table(ah, chan);

	regulatory->max_घातer_level = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ratesArray); i++) अणु
		अगर (ratesArray[i] > MAX_RATE_POWER)
			ratesArray[i] = MAX_RATE_POWER;
		अगर (ratesArray[i] > regulatory->max_घातer_level)
			regulatory->max_घातer_level = ratesArray[i];
	पूर्ण

	ath9k_hw_update_regulatory_maxघातer(ah);

	अगर (test)
		वापस;

	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		क्रम (i = 0; i < Ar5416RateSize; i++) अणु
			पूर्णांक8_t pwr_table_offset;

			pwr_table_offset = ah->eep_ops->get_eeprom(ah,
							EEP_PWR_TABLE_OFFSET);
			ratesArray[i] -= pwr_table_offset * 2;
		पूर्ण
	पूर्ण

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_PHY_POWER_TX_RATE1,
		  ATH9K_POW_SM(ratesArray[rate18mb], 24)
		  | ATH9K_POW_SM(ratesArray[rate12mb], 16)
		  | ATH9K_POW_SM(ratesArray[rate9mb], 8)
		  | ATH9K_POW_SM(ratesArray[rate6mb], 0));
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE2,
		  ATH9K_POW_SM(ratesArray[rate54mb], 24)
		  | ATH9K_POW_SM(ratesArray[rate48mb], 16)
		  | ATH9K_POW_SM(ratesArray[rate36mb], 8)
		  | ATH9K_POW_SM(ratesArray[rate24mb], 0));

	अगर (IS_CHAN_2GHZ(chan)) अणु
		अगर (OLC_FOR_AR9280_20_LATER) अणु
			cck_ofdm_delta = 2;
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE3,
				ATH9K_POW_SM(RT_AR_DELTA(rate2s), 24)
				| ATH9K_POW_SM(RT_AR_DELTA(rate2l), 16)
				| ATH9K_POW_SM(ratesArray[rateXr], 8)
				| ATH9K_POW_SM(RT_AR_DELTA(rate1l), 0));
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE4,
				ATH9K_POW_SM(RT_AR_DELTA(rate11s), 24)
				| ATH9K_POW_SM(RT_AR_DELTA(rate11l), 16)
				| ATH9K_POW_SM(RT_AR_DELTA(rate5_5s), 8)
				| ATH9K_POW_SM(RT_AR_DELTA(rate5_5l), 0));
		पूर्ण अन्यथा अणु
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE3,
				ATH9K_POW_SM(ratesArray[rate2s], 24)
				| ATH9K_POW_SM(ratesArray[rate2l], 16)
				| ATH9K_POW_SM(ratesArray[rateXr], 8)
				| ATH9K_POW_SM(ratesArray[rate1l], 0));
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE4,
				ATH9K_POW_SM(ratesArray[rate11s], 24)
				| ATH9K_POW_SM(ratesArray[rate11l], 16)
				| ATH9K_POW_SM(ratesArray[rate5_5s], 8)
				| ATH9K_POW_SM(ratesArray[rate5_5l], 0));
		पूर्ण
	पूर्ण

	REG_WRITE(ah, AR_PHY_POWER_TX_RATE5,
		  ATH9K_POW_SM(ratesArray[rateHt20_3], 24)
		  | ATH9K_POW_SM(ratesArray[rateHt20_2], 16)
		  | ATH9K_POW_SM(ratesArray[rateHt20_1], 8)
		  | ATH9K_POW_SM(ratesArray[rateHt20_0], 0));
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE6,
		  ATH9K_POW_SM(ratesArray[rateHt20_7], 24)
		  | ATH9K_POW_SM(ratesArray[rateHt20_6], 16)
		  | ATH9K_POW_SM(ratesArray[rateHt20_5], 8)
		  | ATH9K_POW_SM(ratesArray[rateHt20_4], 0));

	अगर (IS_CHAN_HT40(chan)) अणु
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE7,
			  ATH9K_POW_SM(ratesArray[rateHt40_3] +
				       ht40PowerIncForPdadc, 24)
			  | ATH9K_POW_SM(ratesArray[rateHt40_2] +
					 ht40PowerIncForPdadc, 16)
			  | ATH9K_POW_SM(ratesArray[rateHt40_1] +
					 ht40PowerIncForPdadc, 8)
			  | ATH9K_POW_SM(ratesArray[rateHt40_0] +
					 ht40PowerIncForPdadc, 0));
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE8,
			  ATH9K_POW_SM(ratesArray[rateHt40_7] +
				       ht40PowerIncForPdadc, 24)
			  | ATH9K_POW_SM(ratesArray[rateHt40_6] +
					 ht40PowerIncForPdadc, 16)
			  | ATH9K_POW_SM(ratesArray[rateHt40_5] +
					 ht40PowerIncForPdadc, 8)
			  | ATH9K_POW_SM(ratesArray[rateHt40_4] +
					 ht40PowerIncForPdadc, 0));
		अगर (OLC_FOR_AR9280_20_LATER) अणु
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE9,
				ATH9K_POW_SM(ratesArray[rateExtOfdm], 24)
				| ATH9K_POW_SM(RT_AR_DELTA(rateExtCck), 16)
				| ATH9K_POW_SM(ratesArray[rateDupOfdm], 8)
				| ATH9K_POW_SM(RT_AR_DELTA(rateDupCck), 0));
		पूर्ण अन्यथा अणु
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE9,
				ATH9K_POW_SM(ratesArray[rateExtOfdm], 24)
				| ATH9K_POW_SM(ratesArray[rateExtCck], 16)
				| ATH9K_POW_SM(ratesArray[rateDupOfdm], 8)
				| ATH9K_POW_SM(ratesArray[rateDupCck], 0));
		पूर्ण
	पूर्ण

	REG_WRITE(ah, AR_PHY_POWER_TX_SUB,
		  ATH9K_POW_SM(pModal->pwrDecreaseFor3Chain, 6)
		  | ATH9K_POW_SM(pModal->pwrDecreaseFor2Chain, 0));

	/* TPC initializations */
	अगर (ah->tpc_enabled) अणु
		पूर्णांक ht40_delta;

		ht40_delta = (IS_CHAN_HT40(chan)) ? ht40PowerIncForPdadc : 0;
		ar5008_hw_init_rate_txघातer(ah, ratesArray, chan, ht40_delta);
		/* Enable TPC */
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE_MAX,
			MAX_RATE_POWER | AR_PHY_POWER_TX_RATE_MAX_TPC_ENABLE);
	पूर्ण अन्यथा अणु
		/* Disable TPC */
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE_MAX, MAX_RATE_POWER);
	पूर्ण

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

अटल u16 ath9k_hw_def_get_spur_channel(काष्ठा ath_hw *ah, u16 i, bool is2GHz)
अणु
	__le16 spch = ah->eeprom.def.modalHeader[is2GHz].spurChans[i].spurChan;

	वापस le16_to_cpu(spch);
पूर्ण

अटल u8 ath9k_hw_def_get_eepmisc(काष्ठा ath_hw *ah)
अणु
	वापस ah->eeprom.def.baseEepHeader.eepMisc;
पूर्ण

स्थिर काष्ठा eeprom_ops eep_def_ops = अणु
	.check_eeprom		= ath9k_hw_def_check_eeprom,
	.get_eeprom		= ath9k_hw_def_get_eeprom,
	.fill_eeprom		= ath9k_hw_def_fill_eeprom,
	.dump_eeprom		= ath9k_hw_def_dump_eeprom,
	.get_eeprom_ver		= ath9k_hw_def_get_eeprom_ver,
	.get_eeprom_rev		= ath9k_hw_def_get_eeprom_rev,
	.set_board_values	= ath9k_hw_def_set_board_values,
	.set_addac		= ath9k_hw_def_set_addac,
	.set_txघातer		= ath9k_hw_def_set_txघातer,
	.get_spur_channel	= ath9k_hw_def_get_spur_channel,
	.get_eepmisc		= ath9k_hw_def_get_eepmisc
पूर्ण;
