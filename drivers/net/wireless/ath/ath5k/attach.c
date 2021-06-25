<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Reyk Floeter <reyk@खोलोbsd.org>
 * Copyright (c) 2006-2008 Nick Kossअगरidis <mickflemm@gmail.com>
 *
 * Permission to use, copy, modअगरy, and distribute this software क्रम any
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
 *
 */

/*************************************\
* Attach/Detach Functions and helpers *
\*************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "ath5k.h"
#समावेश "reg.h"
#समावेश "debug.h"

/**
 * ath5k_hw_post() - Power On Self Test helper function
 * @ah: The &काष्ठा ath5k_hw
 */
अटल पूर्णांक ath5k_hw_post(काष्ठा ath5k_hw *ah)
अणु

	अटल स्थिर u32 अटल_pattern[4] = अणु
		0x55555555,	0xaaaaaaaa,
		0x66666666,	0x99999999
	पूर्ण;
	अटल स्थिर u16 regs[2] = अणु AR5K_STA_ID0, AR5K_PHY(8) पूर्ण;
	पूर्णांक i, c;
	u16 cur_reg;
	u32 var_pattern;
	u32 init_val;
	u32 cur_val;

	क्रम (c = 0; c < 2; c++) अणु

		cur_reg = regs[c];

		/* Save previous value */
		init_val = ath5k_hw_reg_पढ़ो(ah, cur_reg);

		क्रम (i = 0; i < 256; i++) अणु
			var_pattern = i << 16 | i;
			ath5k_hw_reg_ग_लिखो(ah, var_pattern, cur_reg);
			cur_val = ath5k_hw_reg_पढ़ो(ah, cur_reg);

			अगर (cur_val != var_pattern) अणु
				ATH5K_ERR(ah, "POST Failed !!!\n");
				वापस -EAGAIN;
			पूर्ण

			/* Found on ndiswrapper dumps */
			var_pattern = 0x0039080f;
			ath5k_hw_reg_ग_लिखो(ah, var_pattern, cur_reg);
		पूर्ण

		क्रम (i = 0; i < 4; i++) अणु
			var_pattern = अटल_pattern[i];
			ath5k_hw_reg_ग_लिखो(ah, var_pattern, cur_reg);
			cur_val = ath5k_hw_reg_पढ़ो(ah, cur_reg);

			अगर (cur_val != var_pattern) अणु
				ATH5K_ERR(ah, "POST Failed !!!\n");
				वापस -EAGAIN;
			पूर्ण

			/* Found on ndiswrapper dumps */
			var_pattern = 0x003b080f;
			ath5k_hw_reg_ग_लिखो(ah, var_pattern, cur_reg);
		पूर्ण

		/* Restore previous value */
		ath5k_hw_reg_ग_लिखो(ah, init_val, cur_reg);

	पूर्ण

	वापस 0;

पूर्ण

/**
 * ath5k_hw_init() - Check अगर hw is supported and init the needed काष्ठाs
 * @ah: The &काष्ठा ath5k_hw associated with the device
 *
 * Check अगर the device is supported, perक्रमm a POST and initialize the needed
 * काष्ठाs. Returns -ENOMEM अगर we करोn't have memory क्रम the needed काष्ठाs,
 * -ENODEV अगर the device is not supported or prपूर्णांकs an error msg अगर something
 * अन्यथा went wrong.
 */
पूर्णांक ath5k_hw_init(काष्ठा ath5k_hw *ah)
अणु
	अटल स्थिर u8 zero_mac[ETH_ALEN] = अणु पूर्ण;
	काष्ठा ath_common *common = ath5k_hw_common(ah);
	काष्ठा pci_dev *pdev = ah->pdev;
	काष्ठा ath5k_eeprom_info *ee;
	पूर्णांक ret;
	u32 srev;

	/*
	 * HW inक्रमmation
	 */
	ah->ah_bwmode = AR5K_BWMODE_DEFAULT;
	ah->ah_txघातer.txp_tpc = AR5K_TUNE_TPC_TXPOWER;
	ah->ah_imr = 0;
	ah->ah_retry_लघु = AR5K_INIT_RETRY_SHORT;
	ah->ah_retry_दीर्घ = AR5K_INIT_RETRY_LONG;
	ah->ah_ant_mode = AR5K_ANTMODE_DEFAULT;
	ah->ah_noise_न्यूनमान = -95;	/* until first NF calibration is run */
	ah->ani_state.ani_mode = ATH5K_ANI_MODE_AUTO;
	ah->ah_current_channel = &ah->channels[0];

	/*
	 * Find the mac version
	 */
	ath5k_hw_पढ़ो_srev(ah);
	srev = ah->ah_mac_srev;
	अगर (srev < AR5K_SREV_AR5311)
		ah->ah_version = AR5K_AR5210;
	अन्यथा अगर (srev < AR5K_SREV_AR5212)
		ah->ah_version = AR5K_AR5211;
	अन्यथा
		ah->ah_version = AR5K_AR5212;

	/* Get the MAC version */
	ah->ah_mac_version = AR5K_REG_MS(srev, AR5K_SREV_VER);

	/* Fill the ath5k_hw काष्ठा with the needed functions */
	ret = ath5k_hw_init_desc_functions(ah);
	अगर (ret)
		जाओ err;

	/* Bring device out of sleep and reset its units */
	ret = ath5k_hw_nic_wakeup(ah, शून्य);
	अगर (ret)
		जाओ err;

	/* Get PHY and RADIO revisions */
	ah->ah_phy_revision = ath5k_hw_reg_पढ़ो(ah, AR5K_PHY_CHIP_ID) &
			0xffffffff;
	ah->ah_radio_5ghz_revision = ath5k_hw_radio_revision(ah,
			NL80211_BAND_5GHZ);

	/* Try to identअगरy radio chip based on its srev */
	चयन (ah->ah_radio_5ghz_revision & 0xf0) अणु
	हाल AR5K_SREV_RAD_5111:
		ah->ah_radio = AR5K_RF5111;
		ah->ah_single_chip = false;
		ah->ah_radio_2ghz_revision = ath5k_hw_radio_revision(ah,
							NL80211_BAND_2GHZ);
		अवरोध;
	हाल AR5K_SREV_RAD_5112:
	हाल AR5K_SREV_RAD_2112:
		ah->ah_radio = AR5K_RF5112;
		ah->ah_single_chip = false;
		ah->ah_radio_2ghz_revision = ath5k_hw_radio_revision(ah,
							NL80211_BAND_2GHZ);
		अवरोध;
	हाल AR5K_SREV_RAD_2413:
		ah->ah_radio = AR5K_RF2413;
		ah->ah_single_chip = true;
		अवरोध;
	हाल AR5K_SREV_RAD_5413:
		ah->ah_radio = AR5K_RF5413;
		ah->ah_single_chip = true;
		अवरोध;
	हाल AR5K_SREV_RAD_2316:
		ah->ah_radio = AR5K_RF2316;
		ah->ah_single_chip = true;
		अवरोध;
	हाल AR5K_SREV_RAD_2317:
		ah->ah_radio = AR5K_RF2317;
		ah->ah_single_chip = true;
		अवरोध;
	हाल AR5K_SREV_RAD_5424:
		अगर (ah->ah_mac_version == AR5K_SREV_AR2425 ||
		    ah->ah_mac_version == AR5K_SREV_AR2417) अणु
			ah->ah_radio = AR5K_RF2425;
			ah->ah_single_chip = true;
		पूर्ण अन्यथा अणु
			ah->ah_radio = AR5K_RF5413;
			ah->ah_single_chip = true;
		पूर्ण
		अवरोध;
	शेष:
		/* Identअगरy radio based on mac/phy srev */
		अगर (ah->ah_version == AR5K_AR5210) अणु
			ah->ah_radio = AR5K_RF5110;
			ah->ah_single_chip = false;
		पूर्ण अन्यथा अगर (ah->ah_version == AR5K_AR5211) अणु
			ah->ah_radio = AR5K_RF5111;
			ah->ah_single_chip = false;
			ah->ah_radio_2ghz_revision = ath5k_hw_radio_revision(ah,
							NL80211_BAND_2GHZ);
		पूर्ण अन्यथा अगर (ah->ah_mac_version == (AR5K_SREV_AR2425 >> 4) ||
			   ah->ah_mac_version == (AR5K_SREV_AR2417 >> 4) ||
			   ah->ah_phy_revision == AR5K_SREV_PHY_2425) अणु
			ah->ah_radio = AR5K_RF2425;
			ah->ah_single_chip = true;
			ah->ah_radio_5ghz_revision = AR5K_SREV_RAD_2425;
		पूर्ण अन्यथा अगर (srev == AR5K_SREV_AR5213A &&
			   ah->ah_phy_revision == AR5K_SREV_PHY_5212B) अणु
			ah->ah_radio = AR5K_RF5112;
			ah->ah_single_chip = false;
			ah->ah_radio_5ghz_revision = AR5K_SREV_RAD_5112B;
		पूर्ण अन्यथा अगर (ah->ah_mac_version == (AR5K_SREV_AR2415 >> 4) ||
			   ah->ah_mac_version == (AR5K_SREV_AR2315_R6 >> 4)) अणु
			ah->ah_radio = AR5K_RF2316;
			ah->ah_single_chip = true;
			ah->ah_radio_5ghz_revision = AR5K_SREV_RAD_2316;
		पूर्ण अन्यथा अगर (ah->ah_mac_version == (AR5K_SREV_AR5414 >> 4) ||
			   ah->ah_phy_revision == AR5K_SREV_PHY_5413) अणु
			ah->ah_radio = AR5K_RF5413;
			ah->ah_single_chip = true;
			ah->ah_radio_5ghz_revision = AR5K_SREV_RAD_5413;
		पूर्ण अन्यथा अगर (ah->ah_mac_version == (AR5K_SREV_AR2414 >> 4) ||
			   ah->ah_phy_revision == AR5K_SREV_PHY_2413) अणु
			ah->ah_radio = AR5K_RF2413;
			ah->ah_single_chip = true;
			ah->ah_radio_5ghz_revision = AR5K_SREV_RAD_2413;
		पूर्ण अन्यथा अणु
			ATH5K_ERR(ah, "Couldn't identify radio revision.\n");
			ret = -ENODEV;
			जाओ err;
		पूर्ण
	पूर्ण


	/* Return on unsupported chips (unsupported eeprom etc) */
	अगर ((srev >= AR5K_SREV_AR5416) && (srev < AR5K_SREV_AR2425)) अणु
		ATH5K_ERR(ah, "Device not yet supported.\n");
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	/*
	 * POST
	 */
	ret = ath5k_hw_post(ah);
	अगर (ret)
		जाओ err;

	/* Enable pci core retry fix on Hainan (5213A) and later chips */
	अगर (srev >= AR5K_SREV_AR5213A)
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, AR5K_PCICFG_RETRY_FIX);

	/*
	 * Get card capabilities, calibration values etc
	 * TODO: EEPROM work
	 */
	ret = ath5k_eeprom_init(ah);
	अगर (ret) अणु
		ATH5K_ERR(ah, "unable to init EEPROM\n");
		जाओ err;
	पूर्ण

	ee = &ah->ah_capabilities.cap_eeprom;

	/*
	 * Write PCI-E घातer save settings
	 */
	अगर ((ah->ah_version == AR5K_AR5212) && pdev && (pci_is_pcie(pdev))) अणु
		ath5k_hw_reg_ग_लिखो(ah, 0x9248fc00, AR5K_PCIE_SERDES);
		ath5k_hw_reg_ग_लिखो(ah, 0x24924924, AR5K_PCIE_SERDES);

		/* Shut off RX when elecidle is निश्चितed */
		ath5k_hw_reg_ग_लिखो(ah, 0x28000039, AR5K_PCIE_SERDES);
		ath5k_hw_reg_ग_लिखो(ah, 0x53160824, AR5K_PCIE_SERDES);

		/* If serdes programming is enabled, increase PCI-E
		 * tx घातer क्रम प्रणालीs with दीर्घ trace from host
		 * to minicard connector. */
		अगर (ee->ee_serdes)
			ath5k_hw_reg_ग_लिखो(ah, 0xe5980579, AR5K_PCIE_SERDES);
		अन्यथा
			ath5k_hw_reg_ग_लिखो(ah, 0xf6800579, AR5K_PCIE_SERDES);

		/* Shut off PLL and CLKREQ active in L1 */
		ath5k_hw_reg_ग_लिखो(ah, 0x001defff, AR5K_PCIE_SERDES);

		/* Preserve other settings */
		ath5k_hw_reg_ग_लिखो(ah, 0x1aaabe40, AR5K_PCIE_SERDES);
		ath5k_hw_reg_ग_लिखो(ah, 0xbe105554, AR5K_PCIE_SERDES);
		ath5k_hw_reg_ग_लिखो(ah, 0x000e3007, AR5K_PCIE_SERDES);

		/* Reset SERDES to load new settings */
		ath5k_hw_reg_ग_लिखो(ah, 0x00000000, AR5K_PCIE_SERDES_RESET);
		usleep_range(1000, 1500);
	पूर्ण

	/* Get misc capabilities */
	ret = ath5k_hw_set_capabilities(ah);
	अगर (ret) अणु
		ATH5K_ERR(ah, "unable to get device capabilities\n");
		जाओ err;
	पूर्ण

	/* Crypto settings */
	common->keymax = (ah->ah_version == AR5K_AR5210 ?
			  AR5K_KEYTABLE_SIZE_5210 : AR5K_KEYTABLE_SIZE_5211);

	अगर (srev >= AR5K_SREV_AR5212_V4 &&
	    (ee->ee_version < AR5K_EEPROM_VERSION_5_0 ||
	    !AR5K_EEPROM_AES_DIS(ee->ee_misc5)))
		common->crypt_caps |= ATH_CRYPT_CAP_CIPHER_AESCCM;

	अगर (srev >= AR5K_SREV_AR2414) अणु
		common->crypt_caps |= ATH_CRYPT_CAP_MIC_COMBINED;
		AR5K_REG_ENABLE_BITS(ah, AR5K_MISC_MODE,
			AR5K_MISC_MODE_COMBINED_MIC);
	पूर्ण

	/* MAC address is cleared until add_पूर्णांकerface */
	ath5k_hw_set_lladdr(ah, zero_mac);

	/* Set BSSID to bcast address: ff:ff:ff:ff:ff:ff क्रम now */
	eth_broadcast_addr(common->curbssid);
	ath5k_hw_set_bssid(ah);
	ath5k_hw_set_opmode(ah, ah->opmode);

	ath5k_hw_rfgain_opt_init(ah);

	ath5k_hw_init_nfcal_hist(ah);

	/* turn on HW LEDs */
	ath5k_hw_set_ledstate(ah, AR5K_LED_INIT);

	वापस 0;
err:
	वापस ret;
पूर्ण

/**
 * ath5k_hw_deinit() - Free the &काष्ठा ath5k_hw
 * @ah: The &काष्ठा ath5k_hw
 */
व्योम ath5k_hw_deinit(काष्ठा ath5k_hw *ah)
अणु
	__set_bit(ATH_STAT_INVALID, ah->status);

	kमुक्त(ah->ah_rf_banks);

	ath5k_eeprom_detach(ah);

	/* assume पूर्णांकerrupts are करोwn */
पूर्ण
