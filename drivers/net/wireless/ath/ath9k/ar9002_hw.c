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

#समावेश <linux/moduleparam.h>
#समावेश "hw.h"
#समावेश "ar5008_initvals.h"
#समावेश "ar9001_initvals.h"
#समावेश "ar9002_initvals.h"
#समावेश "ar9002_phy.h"

/* General hardware code क्रम the A5008/AR9001/AR9002 hadware families */

अटल पूर्णांक ar9002_hw_init_mode_regs(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9271(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModes, ar9271Modes_9271);
		INIT_INI_ARRAY(&ah->iniCommon, ar9271Common_9271);
		INIT_INI_ARRAY(&ah->iniModes_9271_ANI_reg, ar9271Modes_9271_ANI_reg);
		वापस 0;
	पूर्ण

	INIT_INI_ARRAY(&ah->iniPcieSerdes,
		       ar9280PciePhy_clkreq_always_on_L1_9280);

	अगर (AR_SREV_9287_11_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModes, ar9287Modes_9287_1_1);
		INIT_INI_ARRAY(&ah->iniCommon, ar9287Common_9287_1_1);
	पूर्ण अन्यथा अगर (AR_SREV_9285_12_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModes, ar9285Modes_9285_1_2);
		INIT_INI_ARRAY(&ah->iniCommon, ar9285Common_9285_1_2);
	पूर्ण अन्यथा अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModes, ar9280Modes_9280_2);
		INIT_INI_ARRAY(&ah->iniCommon, ar9280Common_9280_2);

		INIT_INI_ARRAY(&ah->iniModesFastClock,
			       ar9280Modes_fast_घड़ी_9280_2);
	पूर्ण अन्यथा अगर (AR_SREV_9160_10_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModes, ar5416Modes_9160);
		INIT_INI_ARRAY(&ah->iniCommon, ar5416Common_9160);
		अगर (AR_SREV_9160_11(ah)) अणु
			INIT_INI_ARRAY(&ah->iniAddac,
				       ar5416Addac_9160_1_1);
		पूर्ण अन्यथा अणु
			INIT_INI_ARRAY(&ah->iniAddac, ar5416Addac_9160);
		पूर्ण
	पूर्ण अन्यथा अगर (AR_SREV_9100_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModes, ar5416Modes_9100);
		INIT_INI_ARRAY(&ah->iniCommon, ar5416Common_9100);
		INIT_INI_ARRAY(&ah->iniAddac, ar5416Addac_9100);
	पूर्ण अन्यथा अणु
		INIT_INI_ARRAY(&ah->iniModes, ar5416Modes);
		INIT_INI_ARRAY(&ah->iniCommon, ar5416Common);
		INIT_INI_ARRAY(&ah->iniAddac, ar5416Addac);
	पूर्ण

	अगर (!AR_SREV_9280_20_OR_LATER(ah)) अणु
		/* Common क्रम AR5416, AR913x, AR9160 */
		INIT_INI_ARRAY(&ah->iniBB_RfGain, ar5416BB_RfGain);

		/* Common क्रम AR913x, AR9160 */
		अगर (!AR_SREV_5416(ah))
			INIT_INI_ARRAY(&ah->iniBank6, ar5416Bank6TPC_9100);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniBank6, ar5416Bank6TPC);
	पूर्ण

	/* iniAddac needs to be modअगरied क्रम these chips */
	अगर (AR_SREV_9160(ah) || !AR_SREV_5416_22_OR_LATER(ah)) अणु
		काष्ठा ar5416IniArray *addac = &ah->iniAddac;
		u32 size = माप(u32) * addac->ia_rows * addac->ia_columns;
		u32 *data;

		data = devm_kzalloc(ah->dev, size, GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;

		स_नकल(data, addac->ia_array, size);
		addac->ia_array = data;

		अगर (!AR_SREV_5416_22_OR_LATER(ah)) अणु
			/* override CLKDRV value */
			INI_RA(addac, 31,1) = 0;
		पूर्ण
	पूर्ण
	अगर (AR_SREV_9287_11_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniCckfirNormal,
		       ar9287Common_normal_cck_fir_coeff_9287_1_1);
		INIT_INI_ARRAY(&ah->iniCckfirJapan2484,
		       ar9287Common_japan_2484_cck_fir_coeff_9287_1_1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ar9280_20_hw_init_rxgain_ini(काष्ठा ath_hw *ah)
अणु
	u32 rxgain_type;

	अगर (ah->eep_ops->get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_17) अणु
		rxgain_type = ah->eep_ops->get_eeprom(ah, EEP_RXGAIN_TYPE);

		अगर (rxgain_type == AR5416_EEP_RXGAIN_13DB_BACKOFF)
			INIT_INI_ARRAY(&ah->iniModesRxGain,
				       ar9280Modes_backoff_13db_rxgain_9280_2);
		अन्यथा अगर (rxgain_type == AR5416_EEP_RXGAIN_23DB_BACKOFF)
			INIT_INI_ARRAY(&ah->iniModesRxGain,
				       ar9280Modes_backoff_23db_rxgain_9280_2);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniModesRxGain,
				       ar9280Modes_original_rxgain_9280_2);
	पूर्ण अन्यथा अणु
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9280Modes_original_rxgain_9280_2);
	पूर्ण
पूर्ण

अटल व्योम ar9280_20_hw_init_txgain_ini(काष्ठा ath_hw *ah, u32 txgain_type)
अणु
	अगर (ah->eep_ops->get_eeprom_rev(ah) >= AR5416_EEP_MINOR_VER_19) अणु
		अगर (txgain_type == AR5416_EEP_TXGAIN_HIGH_POWER)
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       ar9280Modes_high_घातer_tx_gain_9280_2);
		अन्यथा
			INIT_INI_ARRAY(&ah->iniModesTxGain,
				       ar9280Modes_original_tx_gain_9280_2);
	पूर्ण अन्यथा अणु
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9280Modes_original_tx_gain_9280_2);
	पूर्ण
पूर्ण

अटल व्योम ar9271_hw_init_txgain_ini(काष्ठा ath_hw *ah, u32 txgain_type)
अणु
	अगर (txgain_type == AR5416_EEP_TXGAIN_HIGH_POWER)
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9271Modes_high_घातer_tx_gain_9271);
	अन्यथा
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9271Modes_normal_घातer_tx_gain_9271);
पूर्ण

अटल व्योम ar9002_hw_init_mode_gain_regs(काष्ठा ath_hw *ah)
अणु
	u32 txgain_type = ah->eep_ops->get_eeprom(ah, EEP_TXGAIN_TYPE);

	अगर (AR_SREV_9287_11_OR_LATER(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9287Modes_rx_gain_9287_1_1);
	अन्यथा अगर (AR_SREV_9280_20(ah))
		ar9280_20_hw_init_rxgain_ini(ah);

	अगर (AR_SREV_9271(ah)) अणु
		ar9271_hw_init_txgain_ini(ah, txgain_type);
	पूर्ण अन्यथा अगर (AR_SREV_9287_11_OR_LATER(ah)) अणु
		INIT_INI_ARRAY(&ah->iniModesTxGain,
			       ar9287Modes_tx_gain_9287_1_1);
	पूर्ण अन्यथा अगर (AR_SREV_9280_20(ah)) अणु
		ar9280_20_hw_init_txgain_ini(ah, txgain_type);
	पूर्ण अन्यथा अगर (AR_SREV_9285_12_OR_LATER(ah)) अणु
		/* txgain table */
		अगर (txgain_type == AR5416_EEP_TXGAIN_HIGH_POWER) अणु
			अगर (AR_SREV_9285E_20(ah)) अणु
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					       ar9285Modes_XE2_0_high_घातer);
			पूर्ण अन्यथा अणु
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					ar9285Modes_high_घातer_tx_gain_9285_1_2);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (AR_SREV_9285E_20(ah)) अणु
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					       ar9285Modes_XE2_0_normal_घातer);
			पूर्ण अन्यथा अणु
				INIT_INI_ARRAY(&ah->iniModesTxGain,
					ar9285Modes_original_tx_gain_9285_1_2);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Helper क्रम ASPM support.
 *
 * Disable PLL when in L0s as well as receiver घड़ी when in L1.
 * This घातer saving option must be enabled through the SerDes.
 *
 * Programming the SerDes must go through the same 288 bit serial shअगरt
 * रेजिस्टर as the other analog रेजिस्टरs.  Hence the 9 ग_लिखोs.
 */
अटल व्योम ar9002_hw_configpciघातersave(काष्ठा ath_hw *ah,
					 bool घातer_off)
अणु
	u8 i;
	u32 val;

	/* Nothing to करो on restore क्रम 11N */
	अगर (!घातer_off /* !restore */) अणु
		अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
			/*
			 * AR9280 2.0 or later chips use SerDes values from the
			 * initvals.h initialized depending on chipset during
			 * __ath9k_hw_init()
			 */
			क्रम (i = 0; i < ah->iniPcieSerdes.ia_rows; i++) अणु
				REG_WRITE(ah, INI_RA(&ah->iniPcieSerdes, i, 0),
					  INI_RA(&ah->iniPcieSerdes, i, 1));
			पूर्ण
		पूर्ण अन्यथा अणु
			ENABLE_REGWRITE_BUFFER(ah);

			REG_WRITE(ah, AR_PCIE_SERDES, 0x9248fc00);
			REG_WRITE(ah, AR_PCIE_SERDES, 0x24924924);

			/* RX shut off when elecidle is निश्चितed */
			REG_WRITE(ah, AR_PCIE_SERDES, 0x28000039);
			REG_WRITE(ah, AR_PCIE_SERDES, 0x53160824);
			REG_WRITE(ah, AR_PCIE_SERDES, 0xe5980579);

			/*
			 * Ignore ah->ah_config.pcie_घड़ी_req setting क्रम
			 * pre-AR9280 11n
			 */
			REG_WRITE(ah, AR_PCIE_SERDES, 0x001defff);

			REG_WRITE(ah, AR_PCIE_SERDES, 0x1aaabe40);
			REG_WRITE(ah, AR_PCIE_SERDES, 0xbe105554);
			REG_WRITE(ah, AR_PCIE_SERDES, 0x000e3007);

			/* Load the new settings */
			REG_WRITE(ah, AR_PCIE_SERDES2, 0x00000000);

			REGWRITE_BUFFER_FLUSH(ah);
		पूर्ण

		udelay(1000);
	पूर्ण

	अगर (घातer_off) अणु
		/* clear bit 19 to disable L1 */
		REG_CLR_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);

		val = REG_READ(ah, AR_WA);

		/*
		 * Set PCIe workaround bits
		 * In AR9280 and AR9285, bit 14 in WA रेजिस्टर (disable L1)
		 * should only  be set when device enters D3 and be
		 * cleared when device comes back to D0.
		 */
		अगर (ah->config.pcie_waen) अणु
			अगर (ah->config.pcie_waen & AR_WA_D3_L1_DISABLE)
				val |= AR_WA_D3_L1_DISABLE;
		पूर्ण अन्यथा अणु
			अगर (AR_SREV_9285(ah) || AR_SREV_9271(ah) || AR_SREV_9287(ah)) अणु
				अगर (AR9285_WA_DEFAULT & AR_WA_D3_L1_DISABLE)
					val |= AR_WA_D3_L1_DISABLE;
			पूर्ण अन्यथा अगर (AR_SREV_9280(ah)) अणु
				अगर (AR9280_WA_DEFAULT & AR_WA_D3_L1_DISABLE)
					val |= AR_WA_D3_L1_DISABLE;
			पूर्ण
		पूर्ण

		अगर (AR_SREV_9280(ah) || AR_SREV_9285(ah) || AR_SREV_9287(ah)) अणु
			/*
			 * Disable bit 6 and 7 beक्रमe entering D3 to
			 * prevent प्रणाली hang.
			 */
			val &= ~(AR_WA_BIT6 | AR_WA_BIT7);
		पूर्ण

		अगर (AR_SREV_9280(ah))
			val |= AR_WA_BIT22;

		अगर (AR_SREV_9285E_20(ah))
			val |= AR_WA_BIT23;

		REG_WRITE(ah, AR_WA, val);
	पूर्ण अन्यथा अणु
		अगर (ah->config.pcie_waen) अणु
			val = ah->config.pcie_waen;
			val &= (~AR_WA_D3_L1_DISABLE);
		पूर्ण अन्यथा अणु
			अगर (AR_SREV_9285(ah) || AR_SREV_9271(ah) || AR_SREV_9287(ah)) अणु
				val = AR9285_WA_DEFAULT;
				val &= (~AR_WA_D3_L1_DISABLE);
			पूर्ण अन्यथा अगर (AR_SREV_9280(ah)) अणु
				/*
				 * For AR9280 chips, bit 22 of 0x4004
				 * needs to be set.
				 */
				val = AR9280_WA_DEFAULT;
				val &= (~AR_WA_D3_L1_DISABLE);
			पूर्ण अन्यथा अणु
				val = AR_WA_DEFAULT;
			पूर्ण
		पूर्ण

		/* WAR क्रम ASPM प्रणाली hang */
		अगर (AR_SREV_9285(ah) || AR_SREV_9287(ah))
			val |= (AR_WA_BIT6 | AR_WA_BIT7);

		अगर (AR_SREV_9285E_20(ah))
			val |= AR_WA_BIT23;

		REG_WRITE(ah, AR_WA, val);

		/* set bit 19 to allow क्रमcing of pcie core पूर्णांकo L1 state */
		REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PCIE_PM_CTRL_ENA);
	पूर्ण
पूर्ण

अटल पूर्णांक ar9002_hw_get_radiorev(काष्ठा ath_hw *ah)
अणु
	u32 val;
	पूर्णांक i;

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_PHY(0x36), 0x00007058);
	क्रम (i = 0; i < 8; i++)
		REG_WRITE(ah, AR_PHY(0x20), 0x00010000);

	REGWRITE_BUFFER_FLUSH(ah);

	val = (REG_READ(ah, AR_PHY(256)) >> 24) & 0xff;
	val = ((val & 0xf0) >> 4) | ((val & 0x0f) << 4);

	वापस ath9k_hw_reverse_bits(val, 8);
पूर्ण

पूर्णांक ar9002_hw_rf_claim(काष्ठा ath_hw *ah)
अणु
	u32 val;

	REG_WRITE(ah, AR_PHY(0), 0x00000007);

	val = ar9002_hw_get_radiorev(ah);
	चयन (val & AR_RADIO_SREV_MAJOR) अणु
	हाल 0:
		val = AR_RAD5133_SREV_MAJOR;
		अवरोध;
	हाल AR_RAD5133_SREV_MAJOR:
	हाल AR_RAD5122_SREV_MAJOR:
	हाल AR_RAD2133_SREV_MAJOR:
	हाल AR_RAD2122_SREV_MAJOR:
		अवरोध;
	शेष:
		ath_err(ath9k_hw_common(ah),
			"Radio Chip Rev 0x%02X not supported\n",
			val & AR_RADIO_SREV_MAJOR);
		वापस -EOPNOTSUPP;
	पूर्ण

	ah->hw_version.analog5GhzRev = val;

	वापस 0;
पूर्ण

व्योम ar9002_hw_enable_async_fअगरo(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9287_13_OR_LATER(ah)) अणु
		REG_SET_BIT(ah, AR_MAC_PCU_ASYNC_FIFO_REG3,
				AR_MAC_PCU_ASYNC_FIFO_REG3_DATAPATH_SEL);
		REG_SET_BIT(ah, AR_PHY_MODE, AR_PHY_MODE_ASYNCFIFO);
		REG_CLR_BIT(ah, AR_MAC_PCU_ASYNC_FIFO_REG3,
				AR_MAC_PCU_ASYNC_FIFO_REG3_SOFT_RESET);
		REG_SET_BIT(ah, AR_MAC_PCU_ASYNC_FIFO_REG3,
				AR_MAC_PCU_ASYNC_FIFO_REG3_SOFT_RESET);
	पूर्ण
पूर्ण

अटल व्योम ar9002_hw_init_hang_checks(काष्ठा ath_hw *ah)
अणु
	अगर (AR_SREV_9100(ah) || AR_SREV_9160(ah)) अणु
		ah->config.hw_hang_checks |= HW_BB_RIFS_HANG;
		ah->config.hw_hang_checks |= HW_BB_DFS_HANG;
	पूर्ण

	अगर (AR_SREV_9280(ah))
		ah->config.hw_hang_checks |= HW_BB_RX_CLEAR_STUCK_HANG;

	अगर (AR_SREV_5416(ah) || AR_SREV_9100(ah) || AR_SREV_9160(ah))
		ah->config.hw_hang_checks |= HW_MAC_HANG;
पूर्ण

/* Sets up the AR5008/AR9001/AR9002 hardware familiy callbacks */
पूर्णांक ar9002_hw_attach_ops(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_hw_निजी_ops *priv_ops = ath9k_hw_निजी_ops(ah);
	काष्ठा ath_hw_ops *ops = ath9k_hw_ops(ah);
	पूर्णांक ret;

	ret = ar9002_hw_init_mode_regs(ah);
	अगर (ret)
		वापस ret;

	priv_ops->init_mode_gain_regs = ar9002_hw_init_mode_gain_regs;
	priv_ops->init_hang_checks = ar9002_hw_init_hang_checks;

	ops->config_pci_घातersave = ar9002_hw_configpciघातersave;

	ret = ar5008_hw_attach_phy_ops(ah);
	अगर (ret)
		वापस ret;

	अगर (AR_SREV_9280_20_OR_LATER(ah))
		ar9002_hw_attach_phy_ops(ah);

	ar9002_hw_attach_calib_ops(ah);
	ar9002_hw_attach_mac_ops(ah);
	वापस 0;
पूर्ण

व्योम ar9002_hw_load_ani_reg(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	u32 modesIndex;
	पूर्णांक i;

	अगर (IS_CHAN_5GHZ(chan))
		modesIndex = IS_CHAN_HT40(chan) ? 2 : 1;
	अन्यथा
		modesIndex = IS_CHAN_HT40(chan) ? 3 : 4;

	ENABLE_REGWRITE_BUFFER(ah);

	क्रम (i = 0; i < ah->iniModes_9271_ANI_reg.ia_rows; i++) अणु
		u32 reg = INI_RA(&ah->iniModes_9271_ANI_reg, i, 0);
		u32 val = INI_RA(&ah->iniModes_9271_ANI_reg, i, modesIndex);
		u32 val_orig;

		अगर (reg == AR_PHY_CCK_DETECT) अणु
			val_orig = REG_READ(ah, reg);
			val &= AR_PHY_CCK_DETECT_WEAK_SIG_THR_CCK;
			val_orig &= ~AR_PHY_CCK_DETECT_WEAK_SIG_THR_CCK;

			REG_WRITE(ah, reg, val|val_orig);
		पूर्ण अन्यथा
			REG_WRITE(ah, reg, val);
	पूर्ण

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण
