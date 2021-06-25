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

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/समय.स>
#समावेश <linux/bitops.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/gpपन.स>
#समावेश <यंत्र/unaligned.h>

#समावेश "hw.h"
#समावेश "hw-ops.h"
#समावेश "ar9003_mac.h"
#समावेश "ar9003_mci.h"
#समावेश "ar9003_phy.h"
#समावेश "ath9k.h"

अटल bool ath9k_hw_set_reset_reg(काष्ठा ath_hw *ah, u32 type);

MODULE_AUTHOR("Atheros Communications");
MODULE_DESCRIPTION("Support for Atheros 802.11n wireless LAN cards.");
MODULE_LICENSE("Dual BSD/GPL");

अटल व्योम ath9k_hw_set_घड़ीrate(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_channel *chan = ah->curchan;
	अचिन्हित पूर्णांक घड़ीrate;

	/* AR9287 v1.3+ uses async FIFO and runs the MAC at 117 MHz */
	अगर (AR_SREV_9287(ah) && AR_SREV_9287_13_OR_LATER(ah))
		घड़ीrate = 117;
	अन्यथा अगर (!chan) /* should really check क्रम CCK instead */
		घड़ीrate = ATH9K_CLOCK_RATE_CCK;
	अन्यथा अगर (IS_CHAN_2GHZ(chan))
		घड़ीrate = ATH9K_CLOCK_RATE_2GHZ_OFDM;
	अन्यथा अगर (ah->caps.hw_caps & ATH9K_HW_CAP_FASTCLOCK)
		घड़ीrate = ATH9K_CLOCK_FAST_RATE_5GHZ_OFDM;
	अन्यथा
		घड़ीrate = ATH9K_CLOCK_RATE_5GHZ_OFDM;

	अगर (chan) अणु
		अगर (IS_CHAN_HT40(chan))
			घड़ीrate *= 2;
		अगर (IS_CHAN_HALF_RATE(chan))
			घड़ीrate /= 2;
		अगर (IS_CHAN_QUARTER_RATE(chan))
			घड़ीrate /= 4;
	पूर्ण

	common->घड़ीrate = घड़ीrate;
पूर्ण

अटल u32 ath9k_hw_mac_to_clks(काष्ठा ath_hw *ah, u32 usecs)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	वापस usecs * common->घड़ीrate;
पूर्ण

bool ath9k_hw_रुको(काष्ठा ath_hw *ah, u32 reg, u32 mask, u32 val, u32 समयout)
अणु
	पूर्णांक i;

	BUG_ON(समयout < AH_TIME_QUANTUM);

	क्रम (i = 0; i < (समयout / AH_TIME_QUANTUM); i++) अणु
		अगर ((REG_READ(ah, reg) & mask) == val)
			वापस true;

		udelay(AH_TIME_QUANTUM);
	पूर्ण

	ath_dbg(ath9k_hw_common(ah), ANY,
		"timeout (%d us) on reg 0x%x: 0x%08x & 0x%08x != 0x%08x\n",
		समयout, reg, REG_READ(ah, reg), mask, val);

	वापस false;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_रुको);

व्योम ath9k_hw_synth_delay(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			  पूर्णांक hw_delay)
अणु
	hw_delay /= 10;

	अगर (IS_CHAN_HALF_RATE(chan))
		hw_delay *= 2;
	अन्यथा अगर (IS_CHAN_QUARTER_RATE(chan))
		hw_delay *= 4;

	udelay(hw_delay + BASE_ACTIVATE_DELAY);
पूर्ण

व्योम ath9k_hw_ग_लिखो_array(काष्ठा ath_hw *ah, स्थिर काष्ठा ar5416IniArray *array,
			  पूर्णांक column, अचिन्हित पूर्णांक *ग_लिखोcnt)
अणु
	पूर्णांक r;

	ENABLE_REGWRITE_BUFFER(ah);
	क्रम (r = 0; r < array->ia_rows; r++) अणु
		REG_WRITE(ah, INI_RA(array, r, 0),
			  INI_RA(array, r, column));
		DO_DELAY(*ग_लिखोcnt);
	पूर्ण
	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

व्योम ath9k_hw_पढ़ो_array(काष्ठा ath_hw *ah, u32 array[][2], पूर्णांक size)
अणु
	u32 *पंचांगp_reg_list, *पंचांगp_data;
	पूर्णांक i;

	पंचांगp_reg_list = kदो_स्मृति_array(size, माप(u32), GFP_KERNEL);
	अगर (!पंचांगp_reg_list) अणु
		dev_err(ah->dev, "%s: tmp_reg_list: alloc filed\n", __func__);
		वापस;
	पूर्ण

	पंचांगp_data = kदो_स्मृति_array(size, माप(u32), GFP_KERNEL);
	अगर (!पंचांगp_data) अणु
		dev_err(ah->dev, "%s tmp_data: alloc filed\n", __func__);
		जाओ error_पंचांगp_data;
	पूर्ण

	क्रम (i = 0; i < size; i++)
		पंचांगp_reg_list[i] = array[i][0];

	REG_READ_MULTI(ah, पंचांगp_reg_list, पंचांगp_data, size);

	क्रम (i = 0; i < size; i++)
		array[i][1] = पंचांगp_data[i];

	kमुक्त(पंचांगp_data);
error_पंचांगp_data:
	kमुक्त(पंचांगp_reg_list);
पूर्ण

u32 ath9k_hw_reverse_bits(u32 val, u32 n)
अणु
	u32 retval;
	पूर्णांक i;

	क्रम (i = 0, retval = 0; i < n; i++) अणु
		retval = (retval << 1) | (val & 1);
		val >>= 1;
	पूर्ण
	वापस retval;
पूर्ण

u16 ath9k_hw_computetxसमय(काष्ठा ath_hw *ah,
			   u8 phy, पूर्णांक kbps,
			   u32 frameLen, u16 rateix,
			   bool लघुPreamble)
अणु
	u32 bitsPerSymbol, numBits, numSymbols, phyTime, txTime;

	अगर (kbps == 0)
		वापस 0;

	चयन (phy) अणु
	हाल WLAN_RC_PHY_CCK:
		phyTime = CCK_PREAMBLE_BITS + CCK_PLCP_BITS;
		अगर (लघुPreamble)
			phyTime >>= 1;
		numBits = frameLen << 3;
		txTime = CCK_SIFS_TIME + phyTime + ((numBits * 1000) / kbps);
		अवरोध;
	हाल WLAN_RC_PHY_OFDM:
		अगर (ah->curchan && IS_CHAN_QUARTER_RATE(ah->curchan)) अणु
			bitsPerSymbol =
				((kbps >> 2) * OFDM_SYMBOL_TIME_QUARTER) / 1000;
			numBits = OFDM_PLCP_BITS + (frameLen << 3);
			numSymbols = DIV_ROUND_UP(numBits, bitsPerSymbol);
			txTime = OFDM_SIFS_TIME_QUARTER
				+ OFDM_PREAMBLE_TIME_QUARTER
				+ (numSymbols * OFDM_SYMBOL_TIME_QUARTER);
		पूर्ण अन्यथा अगर (ah->curchan &&
			   IS_CHAN_HALF_RATE(ah->curchan)) अणु
			bitsPerSymbol =
				((kbps >> 1) * OFDM_SYMBOL_TIME_HALF) / 1000;
			numBits = OFDM_PLCP_BITS + (frameLen << 3);
			numSymbols = DIV_ROUND_UP(numBits, bitsPerSymbol);
			txTime = OFDM_SIFS_TIME_HALF +
				OFDM_PREAMBLE_TIME_HALF
				+ (numSymbols * OFDM_SYMBOL_TIME_HALF);
		पूर्ण अन्यथा अणु
			bitsPerSymbol = (kbps * OFDM_SYMBOL_TIME) / 1000;
			numBits = OFDM_PLCP_BITS + (frameLen << 3);
			numSymbols = DIV_ROUND_UP(numBits, bitsPerSymbol);
			txTime = OFDM_SIFS_TIME + OFDM_PREAMBLE_TIME
				+ (numSymbols * OFDM_SYMBOL_TIME);
		पूर्ण
		अवरोध;
	शेष:
		ath_err(ath9k_hw_common(ah),
			"Unknown phy %u (rate ix %u)\n", phy, rateix);
		txTime = 0;
		अवरोध;
	पूर्ण

	वापस txTime;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_computetxसमय);

व्योम ath9k_hw_get_channel_centers(काष्ठा ath_hw *ah,
				  काष्ठा ath9k_channel *chan,
				  काष्ठा chan_centers *centers)
अणु
	पूर्णांक8_t extoff;

	अगर (!IS_CHAN_HT40(chan)) अणु
		centers->ctl_center = centers->ext_center =
			centers->synth_center = chan->channel;
		वापस;
	पूर्ण

	अगर (IS_CHAN_HT40PLUS(chan)) अणु
		centers->synth_center =
			chan->channel + HT40_CHANNEL_CENTER_SHIFT;
		extoff = 1;
	पूर्ण अन्यथा अणु
		centers->synth_center =
			chan->channel - HT40_CHANNEL_CENTER_SHIFT;
		extoff = -1;
	पूर्ण

	centers->ctl_center =
		centers->synth_center - (extoff * HT40_CHANNEL_CENTER_SHIFT);
	/* 25 MHz spacing is supported by hw but not on upper layers */
	centers->ext_center =
		centers->synth_center + (extoff * HT40_CHANNEL_CENTER_SHIFT);
पूर्ण

/******************/
/* Chip Revisions */
/******************/

अटल bool ath9k_hw_पढ़ो_revisions(काष्ठा ath_hw *ah)
अणु
	u32 srev;
	u32 val;

	अगर (ah->get_mac_revision)
		ah->hw_version.macRev = ah->get_mac_revision();

	चयन (ah->hw_version.devid) अणु
	हाल AR5416_AR9100_DEVID:
		ah->hw_version.macVersion = AR_SREV_VERSION_9100;
		अवरोध;
	हाल AR9300_DEVID_AR9330:
		ah->hw_version.macVersion = AR_SREV_VERSION_9330;
		अगर (!ah->get_mac_revision) अणु
			val = REG_READ(ah, AR_SREV);
			ah->hw_version.macRev = MS(val, AR_SREV_REVISION2);
		पूर्ण
		वापस true;
	हाल AR9300_DEVID_AR9340:
		ah->hw_version.macVersion = AR_SREV_VERSION_9340;
		वापस true;
	हाल AR9300_DEVID_QCA955X:
		ah->hw_version.macVersion = AR_SREV_VERSION_9550;
		वापस true;
	हाल AR9300_DEVID_AR953X:
		ah->hw_version.macVersion = AR_SREV_VERSION_9531;
		वापस true;
	हाल AR9300_DEVID_QCA956X:
		ah->hw_version.macVersion = AR_SREV_VERSION_9561;
		वापस true;
	पूर्ण

	srev = REG_READ(ah, AR_SREV);

	अगर (srev == -1) अणु
		ath_err(ath9k_hw_common(ah),
			"Failed to read SREV register");
		वापस false;
	पूर्ण

	val = srev & AR_SREV_ID;

	अगर (val == 0xFF) अणु
		val = srev;
		ah->hw_version.macVersion =
			(val & AR_SREV_VERSION2) >> AR_SREV_TYPE2_S;
		ah->hw_version.macRev = MS(val, AR_SREV_REVISION2);

		अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah))
			ah->is_pciexpress = true;
		अन्यथा
			ah->is_pciexpress = (val &
					     AR_SREV_TYPE2_HOST_MODE) ? 0 : 1;
	पूर्ण अन्यथा अणु
		अगर (!AR_SREV_9100(ah))
			ah->hw_version.macVersion = MS(val, AR_SREV_VERSION);

		ah->hw_version.macRev = val & AR_SREV_REVISION;

		अगर (ah->hw_version.macVersion == AR_SREV_VERSION_5416_PCIE)
			ah->is_pciexpress = true;
	पूर्ण

	वापस true;
पूर्ण

/************************************/
/* HW Attach, Detach, Init Routines */
/************************************/

अटल व्योम ath9k_hw_disablepcie(काष्ठा ath_hw *ah)
अणु
	अगर (!AR_SREV_5416(ah))
		वापस;

	REG_WRITE(ah, AR_PCIE_SERDES, 0x9248fc00);
	REG_WRITE(ah, AR_PCIE_SERDES, 0x24924924);
	REG_WRITE(ah, AR_PCIE_SERDES, 0x28000029);
	REG_WRITE(ah, AR_PCIE_SERDES, 0x57160824);
	REG_WRITE(ah, AR_PCIE_SERDES, 0x25980579);
	REG_WRITE(ah, AR_PCIE_SERDES, 0x00000000);
	REG_WRITE(ah, AR_PCIE_SERDES, 0x1aaabe40);
	REG_WRITE(ah, AR_PCIE_SERDES, 0xbe105554);
	REG_WRITE(ah, AR_PCIE_SERDES, 0x000e1007);

	REG_WRITE(ah, AR_PCIE_SERDES2, 0x00000000);
पूर्ण

/* This should work क्रम all families including legacy */
अटल bool ath9k_hw_chip_test(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 regAddr[2] = अणु AR_STA_ID0 पूर्ण;
	u32 regHold[2];
	अटल स्थिर u32 patternData[4] = अणु
		0x55555555, 0xaaaaaaaa, 0x66666666, 0x99999999
	पूर्ण;
	पूर्णांक i, j, loop_max;

	अगर (!AR_SREV_9300_20_OR_LATER(ah)) अणु
		loop_max = 2;
		regAddr[1] = AR_PHY_BASE + (8 << 2);
	पूर्ण अन्यथा
		loop_max = 1;

	क्रम (i = 0; i < loop_max; i++) अणु
		u32 addr = regAddr[i];
		u32 wrData, rdData;

		regHold[i] = REG_READ(ah, addr);
		क्रम (j = 0; j < 0x100; j++) अणु
			wrData = (j << 16) | j;
			REG_WRITE(ah, addr, wrData);
			rdData = REG_READ(ah, addr);
			अगर (rdData != wrData) अणु
				ath_err(common,
					"address test failed addr: 0x%08x - wr:0x%08x != rd:0x%08x\n",
					addr, wrData, rdData);
				वापस false;
			पूर्ण
		पूर्ण
		क्रम (j = 0; j < 4; j++) अणु
			wrData = patternData[j];
			REG_WRITE(ah, addr, wrData);
			rdData = REG_READ(ah, addr);
			अगर (wrData != rdData) अणु
				ath_err(common,
					"address test failed addr: 0x%08x - wr:0x%08x != rd:0x%08x\n",
					addr, wrData, rdData);
				वापस false;
			पूर्ण
		पूर्ण
		REG_WRITE(ah, regAddr[i], regHold[i]);
	पूर्ण
	udelay(100);

	वापस true;
पूर्ण

अटल व्योम ath9k_hw_init_config(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ah->config.dma_beacon_response_समय = 1;
	ah->config.sw_beacon_response_समय = 6;
	ah->config.cwm_ignore_extcca = false;
	ah->config.analog_shअगरtreg = 1;

	ah->config.rx_पूर्णांकr_mitigation = true;

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		ah->config.rimt_last = 500;
		ah->config.rimt_first = 2000;
	पूर्ण अन्यथा अणु
		ah->config.rimt_last = 250;
		ah->config.rimt_first = 700;
	पूर्ण

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah))
		ah->config.pll_pwrsave = 7;

	/*
	 * We need this क्रम PCI devices only (Cardbus, PCI, miniPCI)
	 * _and_ अगर on non-uniprocessor प्रणालीs (Multiprocessor/HT).
	 * This means we use it क्रम all AR5416 devices, and the few
	 * minor PCI AR9280 devices out there.
	 *
	 * Serialization is required because these devices करो not handle
	 * well the हाल of two concurrent पढ़ोs/ग_लिखोs due to the latency
	 * involved. During one पढ़ो/ग_लिखो another पढ़ो/ग_लिखो can be issued
	 * on another CPU जबतक the previous पढ़ो/ग_लिखो may still be working
	 * on our hardware, अगर we hit this हाल the hardware poops in a loop.
	 * We prevent this by serializing पढ़ोs and ग_लिखोs.
	 *
	 * This issue is not present on PCI-Express devices or pre-AR5416
	 * devices (legacy, 802.11abg).
	 */
	अगर (num_possible_cpus() > 1)
		ah->config.serialize_regmode = SER_REG_MODE_AUTO;

	अगर (NR_CPUS > 1 && ah->config.serialize_regmode == SER_REG_MODE_AUTO) अणु
		अगर (ah->hw_version.macVersion == AR_SREV_VERSION_5416_PCI ||
		    ((AR_SREV_9160(ah) || AR_SREV_9280(ah) || AR_SREV_9287(ah)) &&
		     !ah->is_pciexpress)) अणु
			ah->config.serialize_regmode = SER_REG_MODE_ON;
		पूर्ण अन्यथा अणु
			ah->config.serialize_regmode = SER_REG_MODE_OFF;
		पूर्ण
	पूर्ण

	ath_dbg(common, RESET, "serialize_regmode is %d\n",
		ah->config.serialize_regmode);

	अगर (AR_SREV_9285(ah) || AR_SREV_9271(ah))
		ah->config.max_txtrig_level = MAX_TX_FIFO_THRESHOLD >> 1;
	अन्यथा
		ah->config.max_txtrig_level = MAX_TX_FIFO_THRESHOLD;
पूर्ण

अटल व्योम ath9k_hw_init_शेषs(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_regulatory *regulatory = ath9k_hw_regulatory(ah);

	regulatory->country_code = CTRY_DEFAULT;
	regulatory->घातer_limit = MAX_COMBINED_POWER;

	ah->hw_version.magic = AR5416_MAGIC;
	ah->hw_version.subvenकरोrid = 0;

	ah->sta_id1_शेषs = AR_STA_ID1_CRPT_MIC_ENABLE |
			       AR_STA_ID1_MCAST_KSRCH;
	अगर (AR_SREV_9100(ah))
		ah->sta_id1_शेषs |= AR_STA_ID1_AR9100_BA_FIX;

	ah->slotसमय = 9;
	ah->globaltxसमयout = (u32) -1;
	ah->घातer_mode = ATH9K_PM_UNDEFINED;
	ah->htc_reset_init = true;

	ah->tpc_enabled = false;

	ah->ani_function = ATH9K_ANI_ALL;
	अगर (!AR_SREV_9300_20_OR_LATER(ah))
		ah->ani_function &= ~ATH9K_ANI_MRC_CCK;

	अगर (AR_SREV_9285(ah) || AR_SREV_9271(ah))
		ah->tx_trig_level = (AR_FTRIG_256B >> AR_FTRIG_S);
	अन्यथा
		ah->tx_trig_level = (AR_FTRIG_512B >> AR_FTRIG_S);
पूर्ण

अटल व्योम ath9k_hw_init_macaddr(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक i;
	u16 eeval;
	अटल स्थिर u32 EEP_MAC[] = अणु EEP_MAC_LSW, EEP_MAC_MID, EEP_MAC_MSW पूर्ण;

	/* MAC address may alपढ़ोy be loaded via ath9k_platक्रमm_data */
	अगर (is_valid_ether_addr(common->macaddr))
		वापस;

	क्रम (i = 0; i < 3; i++) अणु
		eeval = ah->eep_ops->get_eeprom(ah, EEP_MAC[i]);
		common->macaddr[2 * i] = eeval >> 8;
		common->macaddr[2 * i + 1] = eeval & 0xff;
	पूर्ण

	अगर (is_valid_ether_addr(common->macaddr))
		वापस;

	ath_err(common, "eeprom contains invalid mac address: %pM\n",
		common->macaddr);

	eth_अक्रमom_addr(common->macaddr);
	ath_err(common, "random mac address will be used: %pM\n",
		common->macaddr);

	वापस;
पूर्ण

अटल पूर्णांक ath9k_hw_post_init(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक ecode;

	अगर (common->bus_ops->ath_bus_type != ATH_USB) अणु
		अगर (!ath9k_hw_chip_test(ah))
			वापस -ENODEV;
	पूर्ण

	अगर (!AR_SREV_9300_20_OR_LATER(ah)) अणु
		ecode = ar9002_hw_rf_claim(ah);
		अगर (ecode != 0)
			वापस ecode;
	पूर्ण

	ecode = ath9k_hw_eeprom_init(ah);
	अगर (ecode != 0)
		वापस ecode;

	ath_dbg(ath9k_hw_common(ah), CONFIG, "Eeprom VER: %d, REV: %d\n",
		ah->eep_ops->get_eeprom_ver(ah),
		ah->eep_ops->get_eeprom_rev(ah));

	ath9k_hw_ani_init(ah);

	/*
	 * EEPROM needs to be initialized beक्रमe we करो this.
	 * This is required क्रम regulatory compliance.
	 */
	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		u16 regdmn = ah->eep_ops->get_eeprom(ah, EEP_REG_0);
		अगर ((regdmn & 0xF0) == CTL_FCC) अणु
			ah->nf_2g.max = AR_PHY_CCA_MAX_GOOD_VAL_9300_FCC_2GHZ;
			ah->nf_5g.max = AR_PHY_CCA_MAX_GOOD_VAL_9300_FCC_5GHZ;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_hw_attach_ops(काष्ठा ath_hw *ah)
अणु
	अगर (!AR_SREV_9300_20_OR_LATER(ah))
		वापस ar9002_hw_attach_ops(ah);

	ar9003_hw_attach_ops(ah);
	वापस 0;
पूर्ण

/* Called क्रम all hardware families */
अटल पूर्णांक __ath9k_hw_init(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक r = 0;

	अगर (!ath9k_hw_पढ़ो_revisions(ah)) अणु
		ath_err(common, "Could not read hardware revisions");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (ah->hw_version.macVersion) अणु
	हाल AR_SREV_VERSION_5416_PCI:
	हाल AR_SREV_VERSION_5416_PCIE:
	हाल AR_SREV_VERSION_9160:
	हाल AR_SREV_VERSION_9100:
	हाल AR_SREV_VERSION_9280:
	हाल AR_SREV_VERSION_9285:
	हाल AR_SREV_VERSION_9287:
	हाल AR_SREV_VERSION_9271:
	हाल AR_SREV_VERSION_9300:
	हाल AR_SREV_VERSION_9330:
	हाल AR_SREV_VERSION_9485:
	हाल AR_SREV_VERSION_9340:
	हाल AR_SREV_VERSION_9462:
	हाल AR_SREV_VERSION_9550:
	हाल AR_SREV_VERSION_9565:
	हाल AR_SREV_VERSION_9531:
	हाल AR_SREV_VERSION_9561:
		अवरोध;
	शेष:
		ath_err(common,
			"Mac Chip Rev 0x%02x.%x is not supported by this driver\n",
			ah->hw_version.macVersion, ah->hw_version.macRev);
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * Read back AR_WA पूर्णांकo a permanent copy and set bits 14 and 17.
	 * We need to करो this to aव्योम RMW of this रेजिस्टर. We cannot
	 * पढ़ो the reg when chip is asleep.
	 */
	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		ah->WARegVal = REG_READ(ah, AR_WA);
		ah->WARegVal |= (AR_WA_D3_L1_DISABLE |
				 AR_WA_ASPM_TIMER_BASED_DISABLE);
	पूर्ण

	अगर (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_POWER_ON)) अणु
		ath_err(common, "Couldn't reset chip\n");
		वापस -EIO;
	पूर्ण

	अगर (AR_SREV_9565(ah)) अणु
		ah->WARegVal |= AR_WA_BIT22;
		REG_WRITE(ah, AR_WA, ah->WARegVal);
	पूर्ण

	ath9k_hw_init_शेषs(ah);
	ath9k_hw_init_config(ah);

	r = ath9k_hw_attach_ops(ah);
	अगर (r)
		वापस r;

	अगर (!ath9k_hw_setघातer(ah, ATH9K_PM_AWAKE)) अणु
		ath_err(common, "Couldn't wakeup chip\n");
		वापस -EIO;
	पूर्ण

	अगर (AR_SREV_9271(ah) || AR_SREV_9100(ah) || AR_SREV_9340(ah) ||
	    AR_SREV_9330(ah) || AR_SREV_9550(ah))
		ah->is_pciexpress = false;

	ah->hw_version.phyRev = REG_READ(ah, AR_PHY_CHIP_ID);
	ath9k_hw_init_cal_settings(ah);

	अगर (!ah->is_pciexpress)
		ath9k_hw_disablepcie(ah);

	r = ath9k_hw_post_init(ah);
	अगर (r)
		वापस r;

	ath9k_hw_init_mode_gain_regs(ah);
	r = ath9k_hw_fill_cap_info(ah);
	अगर (r)
		वापस r;

	ath9k_hw_init_macaddr(ah);
	ath9k_hw_init_hang_checks(ah);

	common->state = ATH_HW_INITIALIZED;

	वापस 0;
पूर्ण

पूर्णांक ath9k_hw_init(काष्ठा ath_hw *ah)
अणु
	पूर्णांक ret;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	/* These are all the AR5008/AR9001/AR9002/AR9003 hardware family of chipsets */
	चयन (ah->hw_version.devid) अणु
	हाल AR5416_DEVID_PCI:
	हाल AR5416_DEVID_PCIE:
	हाल AR5416_AR9100_DEVID:
	हाल AR9160_DEVID_PCI:
	हाल AR9280_DEVID_PCI:
	हाल AR9280_DEVID_PCIE:
	हाल AR9285_DEVID_PCIE:
	हाल AR9287_DEVID_PCI:
	हाल AR9287_DEVID_PCIE:
	हाल AR2427_DEVID_PCIE:
	हाल AR9300_DEVID_PCIE:
	हाल AR9300_DEVID_AR9485_PCIE:
	हाल AR9300_DEVID_AR9330:
	हाल AR9300_DEVID_AR9340:
	हाल AR9300_DEVID_QCA955X:
	हाल AR9300_DEVID_AR9580:
	हाल AR9300_DEVID_AR9462:
	हाल AR9485_DEVID_AR1111:
	हाल AR9300_DEVID_AR9565:
	हाल AR9300_DEVID_AR953X:
	हाल AR9300_DEVID_QCA956X:
		अवरोध;
	शेष:
		अगर (common->bus_ops->ath_bus_type == ATH_USB)
			अवरोध;
		ath_err(common, "Hardware device ID 0x%04x not supported\n",
			ah->hw_version.devid);
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = __ath9k_hw_init(ah);
	अगर (ret) अणु
		ath_err(common,
			"Unable to initialize hardware; initialization status: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ath_dynack_init(ah);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_init);

अटल व्योम ath9k_hw_init_qos(काष्ठा ath_hw *ah)
अणु
	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_MIC_QOS_CONTROL, 0x100aa);
	REG_WRITE(ah, AR_MIC_QOS_SELECT, 0x3210);

	REG_WRITE(ah, AR_QOS_NO_ACK,
		  SM(2, AR_QOS_NO_ACK_TWO_BIT) |
		  SM(5, AR_QOS_NO_ACK_BIT_OFF) |
		  SM(0, AR_QOS_NO_ACK_BYTE_OFF));

	REG_WRITE(ah, AR_TXOP_X, AR_TXOP_X_VAL);
	REG_WRITE(ah, AR_TXOP_0_3, 0xFFFFFFFF);
	REG_WRITE(ah, AR_TXOP_4_7, 0xFFFFFFFF);
	REG_WRITE(ah, AR_TXOP_8_11, 0xFFFFFFFF);
	REG_WRITE(ah, AR_TXOP_12_15, 0xFFFFFFFF);

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण

u32 ar9003_get_pll_sqsum_dvc(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक i = 0;

	REG_CLR_BIT(ah, PLL3, PLL3_DO_MEAS_MASK);
	udelay(100);
	REG_SET_BIT(ah, PLL3, PLL3_DO_MEAS_MASK);

	जबतक ((REG_READ(ah, PLL4) & PLL4_MEAS_DONE) == 0) अणु

		udelay(100);

		अगर (WARN_ON_ONCE(i >= 100)) अणु
			ath_err(common, "PLL4 measurement not done\n");
			अवरोध;
		पूर्ण

		i++;
	पूर्ण

	वापस (REG_READ(ah, PLL3) & SQSUM_DVC_MASK) >> 3;
पूर्ण
EXPORT_SYMBOL(ar9003_get_pll_sqsum_dvc);

अटल व्योम ath9k_hw_init_pll(काष्ठा ath_hw *ah,
			      काष्ठा ath9k_channel *chan)
अणु
	u32 pll;

	pll = ath9k_hw_compute_pll_control(ah, chan);

	अगर (AR_SREV_9485(ah) || AR_SREV_9565(ah)) अणु
		/* program BB PLL ki and kd value, ki=0x4, kd=0x40 */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_PLL_PWD, 0x1);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_DPLL2_KD, 0x40);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_DPLL2_KI, 0x4);

		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL1,
			      AR_CH0_BB_DPLL1_REFDIV, 0x5);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL1,
			      AR_CH0_BB_DPLL1_NINI, 0x58);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL1,
			      AR_CH0_BB_DPLL1_NFRAC, 0x0);

		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_OUTDIV, 0x1);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_LOCAL_PLL, 0x1);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_EN_NEGTRIG, 0x1);

		/* program BB PLL phase_shअगरt to 0x6 */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL3,
			      AR_CH0_BB_DPLL3_PHASE_SHIFT, 0x6);

		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2,
			      AR_CH0_BB_DPLL2_PLL_PWD, 0x0);
		udelay(1000);
	पूर्ण अन्यथा अगर (AR_SREV_9330(ah)) अणु
		u32 ddr_dpll2, pll_control2, kd;

		अगर (ah->is_clk_25mhz) अणु
			ddr_dpll2 = 0x18e82f01;
			pll_control2 = 0xe04a3d;
			kd = 0x1d;
		पूर्ण अन्यथा अणु
			ddr_dpll2 = 0x19e82f01;
			pll_control2 = 0x886666;
			kd = 0x3d;
		पूर्ण

		/* program DDR PLL ki and kd value */
		REG_WRITE(ah, AR_CH0_DDR_DPLL2, ddr_dpll2);

		/* program DDR PLL phase_shअगरt */
		REG_RMW_FIELD(ah, AR_CH0_DDR_DPLL3,
			      AR_CH0_DPLL3_PHASE_SHIFT, 0x1);

		REG_WRITE(ah, AR_RTC_PLL_CONTROL,
			  pll | AR_RTC_9300_PLL_BYPASS);
		udelay(1000);

		/* program refभाग, nपूर्णांक, frac to RTC रेजिस्टर */
		REG_WRITE(ah, AR_RTC_PLL_CONTROL2, pll_control2);

		/* program BB PLL kd and ki value */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2, AR_CH0_DPLL2_KD, kd);
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL2, AR_CH0_DPLL2_KI, 0x06);

		/* program BB PLL phase_shअगरt */
		REG_RMW_FIELD(ah, AR_CH0_BB_DPLL3,
			      AR_CH0_BB_DPLL3_PHASE_SHIFT, 0x1);
	पूर्ण अन्यथा अगर (AR_SREV_9340(ah) || AR_SREV_9550(ah) || AR_SREV_9531(ah) ||
		   AR_SREV_9561(ah)) अणु
		u32 regval, pll2_भागपूर्णांक, pll2_भागfrac, refभाग;

		REG_WRITE(ah, AR_RTC_PLL_CONTROL,
			  pll | AR_RTC_9300_SOC_PLL_BYPASS);
		udelay(1000);

		REG_SET_BIT(ah, AR_PHY_PLL_MODE, 0x1 << 16);
		udelay(100);

		अगर (ah->is_clk_25mhz) अणु
			अगर (AR_SREV_9531(ah) || AR_SREV_9561(ah)) अणु
				pll2_भागपूर्णांक = 0x1c;
				pll2_भागfrac = 0xa3d2;
				refभाग = 1;
			पूर्ण अन्यथा अणु
				pll2_भागपूर्णांक = 0x54;
				pll2_भागfrac = 0x1eb85;
				refभाग = 3;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (AR_SREV_9340(ah)) अणु
				pll2_भागपूर्णांक = 88;
				pll2_भागfrac = 0;
				refभाग = 5;
			पूर्ण अन्यथा अणु
				pll2_भागपूर्णांक = 0x11;
				pll2_भागfrac = (AR_SREV_9531(ah) ||
						AR_SREV_9561(ah)) ?
						0x26665 : 0x26666;
				refभाग = 1;
			पूर्ण
		पूर्ण

		regval = REG_READ(ah, AR_PHY_PLL_MODE);
		अगर (AR_SREV_9531(ah) || AR_SREV_9561(ah))
			regval |= (0x1 << 22);
		अन्यथा
			regval |= (0x1 << 16);
		REG_WRITE(ah, AR_PHY_PLL_MODE, regval);
		udelay(100);

		REG_WRITE(ah, AR_PHY_PLL_CONTROL, (refभाग << 27) |
			  (pll2_भागपूर्णांक << 18) | pll2_भागfrac);
		udelay(100);

		regval = REG_READ(ah, AR_PHY_PLL_MODE);
		अगर (AR_SREV_9340(ah))
			regval = (regval & 0x80071fff) |
				(0x1 << 30) |
				(0x1 << 13) |
				(0x4 << 26) |
				(0x18 << 19);
		अन्यथा अगर (AR_SREV_9531(ah) || AR_SREV_9561(ah)) अणु
			regval = (regval & 0x01c00fff) |
				(0x1 << 31) |
				(0x2 << 29) |
				(0xa << 25) |
				(0x1 << 19);

			अगर (AR_SREV_9531(ah))
				regval |= (0x6 << 12);
		पूर्ण अन्यथा
			regval = (regval & 0x80071fff) |
				(0x3 << 30) |
				(0x1 << 13) |
				(0x4 << 26) |
				(0x60 << 19);
		REG_WRITE(ah, AR_PHY_PLL_MODE, regval);

		अगर (AR_SREV_9531(ah) || AR_SREV_9561(ah))
			REG_WRITE(ah, AR_PHY_PLL_MODE,
				  REG_READ(ah, AR_PHY_PLL_MODE) & 0xffbfffff);
		अन्यथा
			REG_WRITE(ah, AR_PHY_PLL_MODE,
				  REG_READ(ah, AR_PHY_PLL_MODE) & 0xfffeffff);

		udelay(1000);
	पूर्ण

	अगर (AR_SREV_9565(ah))
		pll |= 0x40000;
	REG_WRITE(ah, AR_RTC_PLL_CONTROL, pll);

	अगर (AR_SREV_9485(ah) || AR_SREV_9340(ah) || AR_SREV_9330(ah) ||
	    AR_SREV_9550(ah))
		udelay(1000);

	/* Switch the core घड़ी क्रम ar9271 to 117Mhz */
	अगर (AR_SREV_9271(ah)) अणु
		udelay(500);
		REG_WRITE(ah, 0x50040, 0x304);
	पूर्ण

	udelay(RTC_PLL_SETTLE_DELAY);

	REG_WRITE(ah, AR_RTC_SLEEP_CLK, AR_RTC_FORCE_DERIVED_CLK);
पूर्ण

अटल व्योम ath9k_hw_init_पूर्णांकerrupt_masks(काष्ठा ath_hw *ah,
					  क्रमागत nl80211_अगरtype opmode)
अणु
	u32 sync_शेष = AR_INTR_SYNC_DEFAULT;
	u32 imr_reg = AR_IMR_TXERR |
		AR_IMR_TXURN |
		AR_IMR_RXERR |
		AR_IMR_RXORN |
		AR_IMR_BCNMISC;
	u32 msi_cfg = 0;

	अगर (AR_SREV_9340(ah) || AR_SREV_9550(ah) || AR_SREV_9531(ah) ||
	    AR_SREV_9561(ah))
		sync_शेष &= ~AR_INTR_SYNC_HOST1_FATAL;

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		imr_reg |= AR_IMR_RXOK_HP;
		अगर (ah->config.rx_पूर्णांकr_mitigation) अणु
			imr_reg |= AR_IMR_RXINTM | AR_IMR_RXMINTR;
			msi_cfg |= AR_INTCFG_MSI_RXINTM | AR_INTCFG_MSI_RXMINTR;
		पूर्ण अन्यथा अणु
			imr_reg |= AR_IMR_RXOK_LP;
			msi_cfg |= AR_INTCFG_MSI_RXOK;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ah->config.rx_पूर्णांकr_mitigation) अणु
			imr_reg |= AR_IMR_RXINTM | AR_IMR_RXMINTR;
			msi_cfg |= AR_INTCFG_MSI_RXINTM | AR_INTCFG_MSI_RXMINTR;
		पूर्ण अन्यथा अणु
			imr_reg |= AR_IMR_RXOK;
			msi_cfg |= AR_INTCFG_MSI_RXOK;
		पूर्ण
	पूर्ण

	अगर (ah->config.tx_पूर्णांकr_mitigation) अणु
		imr_reg |= AR_IMR_TXINTM | AR_IMR_TXMINTR;
		msi_cfg |= AR_INTCFG_MSI_TXINTM | AR_INTCFG_MSI_TXMINTR;
	पूर्ण अन्यथा अणु
		imr_reg |= AR_IMR_TXOK;
		msi_cfg |= AR_INTCFG_MSI_TXOK;
	पूर्ण

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_IMR, imr_reg);
	ah->imrs2_reg |= AR_IMR_S2_GTT;
	REG_WRITE(ah, AR_IMR_S2, ah->imrs2_reg);

	अगर (ah->msi_enabled) अणु
		ah->msi_reg = REG_READ(ah, AR_PCIE_MSI);
		ah->msi_reg |= AR_PCIE_MSI_HW_DBI_WR_EN;
		ah->msi_reg &= AR_PCIE_MSI_HW_INT_PENDING_ADDR_MSI_64;
		REG_WRITE(ah, AR_INTCFG, msi_cfg);
		ath_dbg(ath9k_hw_common(ah), ANY,
			"value of AR_INTCFG=0x%X, msi_cfg=0x%X\n",
			REG_READ(ah, AR_INTCFG), msi_cfg);
	पूर्ण

	अगर (!AR_SREV_9100(ah)) अणु
		REG_WRITE(ah, AR_INTR_SYNC_CAUSE, 0xFFFFFFFF);
		REG_WRITE(ah, AR_INTR_SYNC_ENABLE, sync_शेष);
		REG_WRITE(ah, AR_INTR_SYNC_MASK, 0);
	पूर्ण

	REGWRITE_BUFFER_FLUSH(ah);

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		REG_WRITE(ah, AR_INTR_PRIO_ASYNC_ENABLE, 0);
		REG_WRITE(ah, AR_INTR_PRIO_ASYNC_MASK, 0);
		REG_WRITE(ah, AR_INTR_PRIO_SYNC_ENABLE, 0);
		REG_WRITE(ah, AR_INTR_PRIO_SYNC_MASK, 0);
	पूर्ण
पूर्ण

अटल व्योम ath9k_hw_set_sअगरs_समय(काष्ठा ath_hw *ah, u32 us)
अणु
	u32 val = ath9k_hw_mac_to_clks(ah, us - 2);
	val = min(val, (u32) 0xFFFF);
	REG_WRITE(ah, AR_D_GBL_IFS_SIFS, val);
पूर्ण

व्योम ath9k_hw_setslotसमय(काष्ठा ath_hw *ah, u32 us)
अणु
	u32 val = ath9k_hw_mac_to_clks(ah, us);
	val = min(val, (u32) 0xFFFF);
	REG_WRITE(ah, AR_D_GBL_IFS_SLOT, val);
पूर्ण

व्योम ath9k_hw_set_ack_समयout(काष्ठा ath_hw *ah, u32 us)
अणु
	u32 val = ath9k_hw_mac_to_clks(ah, us);
	val = min(val, (u32) MS(0xFFFFFFFF, AR_TIME_OUT_ACK));
	REG_RMW_FIELD(ah, AR_TIME_OUT, AR_TIME_OUT_ACK, val);
पूर्ण

व्योम ath9k_hw_set_cts_समयout(काष्ठा ath_hw *ah, u32 us)
अणु
	u32 val = ath9k_hw_mac_to_clks(ah, us);
	val = min(val, (u32) MS(0xFFFFFFFF, AR_TIME_OUT_CTS));
	REG_RMW_FIELD(ah, AR_TIME_OUT, AR_TIME_OUT_CTS, val);
पूर्ण

अटल bool ath9k_hw_set_global_txसमयout(काष्ठा ath_hw *ah, u32 tu)
अणु
	अगर (tu > 0xFFFF) अणु
		ath_dbg(ath9k_hw_common(ah), XMIT, "bad global tx timeout %u\n",
			tu);
		ah->globaltxसमयout = (u32) -1;
		वापस false;
	पूर्ण अन्यथा अणु
		REG_RMW_FIELD(ah, AR_GTXTO, AR_GTXTO_TIMEOUT_LIMIT, tu);
		ah->globaltxसमयout = tu;
		वापस true;
	पूर्ण
पूर्ण

व्योम ath9k_hw_init_global_settings(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	स्थिर काष्ठा ath9k_channel *chan = ah->curchan;
	पूर्णांक ackसमयout, ctsसमयout, ack_offset = 0;
	पूर्णांक slotसमय;
	पूर्णांक sअगरsसमय;
	पूर्णांक rx_lat = 0, tx_lat = 0, eअगरs = 0, ack_shअगरt = 0;
	u32 reg;

	ath_dbg(ath9k_hw_common(ah), RESET, "ah->misc_mode 0x%x\n",
		ah->misc_mode);

	अगर (!chan)
		वापस;

	अगर (ah->misc_mode != 0)
		REG_SET_BIT(ah, AR_PCU_MISC, ah->misc_mode);

	अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		rx_lat = 41;
	अन्यथा
		rx_lat = 37;
	tx_lat = 54;

	अगर (IS_CHAN_5GHZ(chan))
		sअगरsसमय = 16;
	अन्यथा
		sअगरsसमय = 10;

	अगर (IS_CHAN_HALF_RATE(chan)) अणु
		eअगरs = 175;
		rx_lat *= 2;
		tx_lat *= 2;
		अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		    tx_lat += 11;

		sअगरsसमय = 32;
		ack_offset = 16;
		ack_shअगरt = 3;
		slotसमय = 13;
	पूर्ण अन्यथा अगर (IS_CHAN_QUARTER_RATE(chan)) अणु
		eअगरs = 340;
		rx_lat = (rx_lat * 4) - 1;
		tx_lat *= 4;
		अगर (IS_CHAN_A_FAST_CLOCK(ah, chan))
		    tx_lat += 22;

		sअगरsसमय = 64;
		ack_offset = 32;
		ack_shअगरt = 1;
		slotसमय = 21;
	पूर्ण अन्यथा अणु
		अगर (AR_SREV_9287(ah) && AR_SREV_9287_13_OR_LATER(ah)) अणु
			eअगरs = AR_D_GBL_IFS_EIFS_ASYNC_FIFO;
			reg = AR_USEC_ASYNC_FIFO;
		पूर्ण अन्यथा अणु
			eअगरs = REG_READ(ah, AR_D_GBL_IFS_EIFS)/
				common->घड़ीrate;
			reg = REG_READ(ah, AR_USEC);
		पूर्ण
		rx_lat = MS(reg, AR_USEC_RX_LAT);
		tx_lat = MS(reg, AR_USEC_TX_LAT);

		slotसमय = ah->slotसमय;
	पूर्ण

	/* As defined by IEEE 802.11-2007 17.3.8.6 */
	slotसमय += 3 * ah->coverage_class;
	ackसमयout = slotसमय + sअगरsसमय + ack_offset;
	ctsसमयout = ackसमयout;

	/*
	 * Workaround क्रम early ACK समयouts, add an offset to match the
	 * initval's 64us ack समयout value. Use 48us क्रम the CTS समयout.
	 * This was initially only meant to work around an issue with delayed
	 * BA frames in some implementations, but it has been found to fix ACK
	 * समयout issues in other हालs as well.
	 */
	अगर (IS_CHAN_2GHZ(chan) &&
	    !IS_CHAN_HALF_RATE(chan) && !IS_CHAN_QUARTER_RATE(chan)) अणु
		ackसमयout += 64 - sअगरsसमय - ah->slotसमय;
		ctsसमयout += 48 - sअगरsसमय - ah->slotसमय;
	पूर्ण

	अगर (ah->dynack.enabled) अणु
		ackसमयout = ah->dynack.ackto;
		ctsसमयout = ackसमयout;
		slotसमय = (ackसमयout - 3) / 2;
	पूर्ण अन्यथा अणु
		ah->dynack.ackto = ackसमयout;
	पूर्ण

	ath9k_hw_set_sअगरs_समय(ah, sअगरsसमय);
	ath9k_hw_setslotसमय(ah, slotसमय);
	ath9k_hw_set_ack_समयout(ah, ackसमयout);
	ath9k_hw_set_cts_समयout(ah, ctsसमयout);
	अगर (ah->globaltxसमयout != (u32) -1)
		ath9k_hw_set_global_txसमयout(ah, ah->globaltxसमयout);

	REG_WRITE(ah, AR_D_GBL_IFS_EIFS, ath9k_hw_mac_to_clks(ah, eअगरs));
	REG_RMW(ah, AR_USEC,
		(common->घड़ीrate - 1) |
		SM(rx_lat, AR_USEC_RX_LAT) |
		SM(tx_lat, AR_USEC_TX_LAT),
		AR_USEC_TX_LAT | AR_USEC_RX_LAT | AR_USEC_USEC);

	अगर (IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan))
		REG_RMW(ah, AR_TXSIFS,
			sअगरsसमय | SM(ack_shअगरt, AR_TXSIFS_ACK_SHIFT),
			(AR_TXSIFS_TIME | AR_TXSIFS_ACK_SHIFT));
पूर्ण
EXPORT_SYMBOL(ath9k_hw_init_global_settings);

व्योम ath9k_hw_deinit(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (common->state < ATH_HW_INITIALIZED)
		वापस;

	ath9k_hw_setघातer(ah, ATH9K_PM_FULL_SLEEP);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_deinit);

/*******/
/* INI */
/*******/

u32 ath9k_regd_get_ctl(काष्ठा ath_regulatory *reg, काष्ठा ath9k_channel *chan)
अणु
	u32 ctl = ath_regd_get_band_ctl(reg, chan->chan->band);

	अगर (IS_CHAN_2GHZ(chan))
		ctl |= CTL_11G;
	अन्यथा
		ctl |= CTL_11A;

	वापस ctl;
पूर्ण

/****************************************/
/* Reset and Channel Switching Routines */
/****************************************/

अटल अंतरभूत व्योम ath9k_hw_set_dma(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक txbuf_size;

	ENABLE_REGWRITE_BUFFER(ah);

	/*
	 * set AHB_MODE not to करो cacheline prefetches
	*/
	अगर (!AR_SREV_9300_20_OR_LATER(ah))
		REG_SET_BIT(ah, AR_AHB_MODE, AR_AHB_PREFETCH_RD_EN);

	/*
	 * let mac dma पढ़ोs be in 128 byte chunks
	 */
	REG_RMW(ah, AR_TXCFG, AR_TXCFG_DMASZ_128B, AR_TXCFG_DMASZ_MASK);

	REGWRITE_BUFFER_FLUSH(ah);

	/*
	 * Restore TX Trigger Level to its pre-reset value.
	 * The initial value depends on whether aggregation is enabled, and is
	 * adjusted whenever underruns are detected.
	 */
	अगर (!AR_SREV_9300_20_OR_LATER(ah))
		REG_RMW_FIELD(ah, AR_TXCFG, AR_FTRIG, ah->tx_trig_level);

	ENABLE_REGWRITE_BUFFER(ah);

	/*
	 * let mac dma ग_लिखोs be in 128 byte chunks
	 */
	REG_RMW(ah, AR_RXCFG, AR_RXCFG_DMASZ_128B, AR_RXCFG_DMASZ_MASK);

	/*
	 * Setup receive FIFO threshold to hold off TX activities
	 */
	REG_WRITE(ah, AR_RXFIFO_CFG, 0x200);

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_HP, 0x1);
		REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_LP, 0x1);

		ath9k_hw_set_rx_bufsize(ah, common->rx_bufsize -
			ah->caps.rx_status_len);
	पूर्ण

	/*
	 * reduce the number of usable entries in PCU TXBUF to aव्योम
	 * wrap around issues.
	 */
	अगर (AR_SREV_9285(ah)) अणु
		/* For AR9285 the number of Fअगरos are reduced to half.
		 * So set the usable tx buf size also to half to
		 * aव्योम data/delimiter underruns
		 */
		txbuf_size = AR_9285_PCU_TXBUF_CTRL_USABLE_SIZE;
	पूर्ण अन्यथा अगर (AR_SREV_9340_13_OR_LATER(ah)) अणु
		/* Uses fewer entries क्रम AR934x v1.3+ to prevent rx overruns */
		txbuf_size = AR_9340_PCU_TXBUF_CTRL_USABLE_SIZE;
	पूर्ण अन्यथा अणु
		txbuf_size = AR_PCU_TXBUF_CTRL_USABLE_SIZE;
	पूर्ण

	अगर (!AR_SREV_9271(ah))
		REG_WRITE(ah, AR_PCU_TXBUF_CTRL, txbuf_size);

	REGWRITE_BUFFER_FLUSH(ah);

	अगर (AR_SREV_9300_20_OR_LATER(ah))
		ath9k_hw_reset_txstatus_ring(ah);
पूर्ण

अटल व्योम ath9k_hw_set_operating_mode(काष्ठा ath_hw *ah, पूर्णांक opmode)
अणु
	u32 mask = AR_STA_ID1_STA_AP | AR_STA_ID1_ADHOC;
	u32 set = AR_STA_ID1_KSRCH_MODE;

	ENABLE_REG_RMW_BUFFER(ah);
	चयन (opmode) अणु
	हाल NL80211_IFTYPE_ADHOC:
		अगर (!AR_SREV_9340_13(ah)) अणु
			set |= AR_STA_ID1_ADHOC;
			REG_SET_BIT(ah, AR_CFG, AR_CFG_AP_ADHOC_INDICATION);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल NL80211_IFTYPE_OCB:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		set |= AR_STA_ID1_STA_AP;
		fallthrough;
	हाल NL80211_IFTYPE_STATION:
		REG_CLR_BIT(ah, AR_CFG, AR_CFG_AP_ADHOC_INDICATION);
		अवरोध;
	शेष:
		अगर (!ah->is_monitoring)
			set = 0;
		अवरोध;
	पूर्ण
	REG_RMW(ah, AR_STA_ID1, set, mask);
	REG_RMW_BUFFER_FLUSH(ah);
पूर्ण

व्योम ath9k_hw_get_delta_slope_vals(काष्ठा ath_hw *ah, u32 coef_scaled,
				   u32 *coef_mantissa, u32 *coef_exponent)
अणु
	u32 coef_exp, coef_man;

	क्रम (coef_exp = 31; coef_exp > 0; coef_exp--)
		अगर ((coef_scaled >> coef_exp) & 0x1)
			अवरोध;

	coef_exp = 14 - (coef_exp - COEF_SCALE_S);

	coef_man = coef_scaled + (1 << (COEF_SCALE_S - coef_exp - 1));

	*coef_mantissa = coef_man >> (COEF_SCALE_S - coef_exp);
	*coef_exponent = coef_exp - 16;
पूर्ण

/* AR9330 WAR:
 * call बाह्यal reset function to reset WMAC अगर:
 * - करोing a cold reset
 * - we have pending frames in the TX queues.
 */
अटल bool ath9k_hw_ar9330_reset_war(काष्ठा ath_hw *ah, पूर्णांक type)
अणु
	पूर्णांक i, npend = 0;

	क्रम (i = 0; i < AR_NUM_QCU; i++) अणु
		npend = ath9k_hw_numtxpending(ah, i);
		अगर (npend)
			अवरोध;
	पूर्ण

	अगर (ah->बाह्यal_reset &&
	    (npend || type == ATH9K_RESET_COLD)) अणु
		पूर्णांक reset_err = 0;

		ath_dbg(ath9k_hw_common(ah), RESET,
			"reset MAC via external reset\n");

		reset_err = ah->बाह्यal_reset();
		अगर (reset_err) अणु
			ath_err(ath9k_hw_common(ah),
				"External reset failed, err=%d\n",
				reset_err);
			वापस false;
		पूर्ण

		REG_WRITE(ah, AR_RTC_RESET, 1);
	पूर्ण

	वापस true;
पूर्ण

अटल bool ath9k_hw_set_reset(काष्ठा ath_hw *ah, पूर्णांक type)
अणु
	u32 rst_flags;
	u32 पंचांगpReg;

	अगर (AR_SREV_9100(ah)) अणु
		REG_RMW_FIELD(ah, AR_RTC_DERIVED_CLK,
			      AR_RTC_DERIVED_CLK_PERIOD, 1);
		(व्योम)REG_READ(ah, AR_RTC_DERIVED_CLK);
	पूर्ण

	ENABLE_REGWRITE_BUFFER(ah);

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		REG_WRITE(ah, AR_WA, ah->WARegVal);
		udelay(10);
	पूर्ण

	REG_WRITE(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN |
		  AR_RTC_FORCE_WAKE_ON_INT);

	अगर (AR_SREV_9100(ah)) अणु
		rst_flags = AR_RTC_RC_MAC_WARM | AR_RTC_RC_MAC_COLD |
			AR_RTC_RC_COLD_RESET | AR_RTC_RC_WARM_RESET;
	पूर्ण अन्यथा अणु
		पंचांगpReg = REG_READ(ah, AR_INTR_SYNC_CAUSE);
		अगर (AR_SREV_9340(ah))
			पंचांगpReg &= AR9340_INTR_SYNC_LOCAL_TIMEOUT;
		अन्यथा
			पंचांगpReg &= AR_INTR_SYNC_LOCAL_TIMEOUT |
				  AR_INTR_SYNC_RADM_CPL_TIMEOUT;

		अगर (पंचांगpReg) अणु
			u32 val;
			REG_WRITE(ah, AR_INTR_SYNC_ENABLE, 0);

			val = AR_RC_HOSTIF;
			अगर (!AR_SREV_9300_20_OR_LATER(ah))
				val |= AR_RC_AHB;
			REG_WRITE(ah, AR_RC, val);

		पूर्ण अन्यथा अगर (!AR_SREV_9300_20_OR_LATER(ah))
			REG_WRITE(ah, AR_RC, AR_RC_AHB);

		rst_flags = AR_RTC_RC_MAC_WARM;
		अगर (type == ATH9K_RESET_COLD)
			rst_flags |= AR_RTC_RC_MAC_COLD;
	पूर्ण

	अगर (AR_SREV_9330(ah)) अणु
		अगर (!ath9k_hw_ar9330_reset_war(ah, type))
			वापस false;
	पूर्ण

	अगर (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_check_gpm_offset(ah);

	/* DMA HALT added to resolve ar9300 and ar9580 bus error during
	 * RTC_RC reg पढ़ो
	 */
	अगर (AR_SREV_9300(ah) || AR_SREV_9580(ah)) अणु
		REG_SET_BIT(ah, AR_CFG, AR_CFG_HALT_REQ);
		ath9k_hw_रुको(ah, AR_CFG, AR_CFG_HALT_ACK, AR_CFG_HALT_ACK,
			      20 * AH_WAIT_TIMEOUT);
		REG_CLR_BIT(ah, AR_CFG, AR_CFG_HALT_REQ);
	पूर्ण

	REG_WRITE(ah, AR_RTC_RC, rst_flags);

	REGWRITE_BUFFER_FLUSH(ah);

	अगर (AR_SREV_9300_20_OR_LATER(ah))
		udelay(50);
	अन्यथा अगर (AR_SREV_9100(ah))
		mdelay(10);
	अन्यथा
		udelay(100);

	REG_WRITE(ah, AR_RTC_RC, 0);
	अगर (!ath9k_hw_रुको(ah, AR_RTC_RC, AR_RTC_RC_M, 0, AH_WAIT_TIMEOUT)) अणु
		ath_dbg(ath9k_hw_common(ah), RESET, "RTC stuck in MAC reset\n");
		वापस false;
	पूर्ण

	अगर (!AR_SREV_9100(ah))
		REG_WRITE(ah, AR_RC, 0);

	अगर (AR_SREV_9100(ah))
		udelay(50);

	वापस true;
पूर्ण

अटल bool ath9k_hw_set_reset_घातer_on(काष्ठा ath_hw *ah)
अणु
	ENABLE_REGWRITE_BUFFER(ah);

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		REG_WRITE(ah, AR_WA, ah->WARegVal);
		udelay(10);
	पूर्ण

	REG_WRITE(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN |
		  AR_RTC_FORCE_WAKE_ON_INT);

	अगर (!AR_SREV_9100(ah) && !AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_RC, AR_RC_AHB);

	REG_WRITE(ah, AR_RTC_RESET, 0);

	REGWRITE_BUFFER_FLUSH(ah);

	udelay(2);

	अगर (!AR_SREV_9100(ah) && !AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_RC, 0);

	REG_WRITE(ah, AR_RTC_RESET, 1);

	अगर (!ath9k_hw_रुको(ah,
			   AR_RTC_STATUS,
			   AR_RTC_STATUS_M,
			   AR_RTC_STATUS_ON,
			   AH_WAIT_TIMEOUT)) अणु
		ath_dbg(ath9k_hw_common(ah), RESET, "RTC not waking up\n");
		वापस false;
	पूर्ण

	वापस ath9k_hw_set_reset(ah, ATH9K_RESET_WARM);
पूर्ण

अटल bool ath9k_hw_set_reset_reg(काष्ठा ath_hw *ah, u32 type)
अणु
	bool ret = false;

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		REG_WRITE(ah, AR_WA, ah->WARegVal);
		udelay(10);
	पूर्ण

	REG_WRITE(ah, AR_RTC_FORCE_WAKE,
		  AR_RTC_FORCE_WAKE_EN | AR_RTC_FORCE_WAKE_ON_INT);

	अगर (!ah->reset_घातer_on)
		type = ATH9K_RESET_POWER_ON;

	चयन (type) अणु
	हाल ATH9K_RESET_POWER_ON:
		ret = ath9k_hw_set_reset_घातer_on(ah);
		अगर (ret)
			ah->reset_घातer_on = true;
		अवरोध;
	हाल ATH9K_RESET_WARM:
	हाल ATH9K_RESET_COLD:
		ret = ath9k_hw_set_reset(ah, type);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool ath9k_hw_chip_reset(काष्ठा ath_hw *ah,
				काष्ठा ath9k_channel *chan)
अणु
	पूर्णांक reset_type = ATH9K_RESET_WARM;

	अगर (AR_SREV_9280(ah)) अणु
		अगर (ah->eep_ops->get_eeprom(ah, EEP_OL_PWRCTRL))
			reset_type = ATH9K_RESET_POWER_ON;
		अन्यथा
			reset_type = ATH9K_RESET_COLD;
	पूर्ण अन्यथा अगर (ah->chip_fullsleep || REG_READ(ah, AR_Q_TXE) ||
		   (REG_READ(ah, AR_CR) & AR_CR_RXE))
		reset_type = ATH9K_RESET_COLD;

	अगर (!ath9k_hw_set_reset_reg(ah, reset_type))
		वापस false;

	अगर (!ath9k_hw_setघातer(ah, ATH9K_PM_AWAKE))
		वापस false;

	ah->chip_fullsleep = false;

	अगर (AR_SREV_9330(ah))
		ar9003_hw_पूर्णांकernal_regulator_apply(ah);
	ath9k_hw_init_pll(ah, chan);

	वापस true;
पूर्ण

अटल bool ath9k_hw_channel_change(काष्ठा ath_hw *ah,
				    काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	bool band_चयन = false, mode_dअगरf = false;
	u8 ini_reloaded = 0;
	u32 qnum;
	पूर्णांक r;

	अगर (pCap->hw_caps & ATH9K_HW_CAP_FCC_BAND_SWITCH) अणु
		u32 flags_dअगरf = chan->channelFlags ^ ah->curchan->channelFlags;
		band_चयन = !!(flags_dअगरf & CHANNEL_5GHZ);
		mode_dअगरf = !!(flags_dअगरf & ~CHANNEL_HT);
	पूर्ण

	क्रम (qnum = 0; qnum < AR_NUM_QCU; qnum++) अणु
		अगर (ath9k_hw_numtxpending(ah, qnum)) अणु
			ath_dbg(common, QUEUE,
				"Transmit frames pending on queue %d\n", qnum);
			वापस false;
		पूर्ण
	पूर्ण

	अगर (!ath9k_hw_rfbus_req(ah)) अणु
		ath_err(common, "Could not kill baseband RX\n");
		वापस false;
	पूर्ण

	अगर (band_चयन || mode_dअगरf) अणु
		ath9k_hw_mark_phy_inactive(ah);
		udelay(5);

		अगर (band_चयन)
			ath9k_hw_init_pll(ah, chan);

		अगर (ath9k_hw_fast_chan_change(ah, chan, &ini_reloaded)) अणु
			ath_err(common, "Failed to do fast channel change\n");
			वापस false;
		पूर्ण
	पूर्ण

	ath9k_hw_set_channel_regs(ah, chan);

	r = ath9k_hw_rf_set_freq(ah, chan);
	अगर (r) अणु
		ath_err(common, "Failed to set channel\n");
		वापस false;
	पूर्ण
	ath9k_hw_set_घड़ीrate(ah);
	ath9k_hw_apply_txघातer(ah, chan, false);

	ath9k_hw_set_delta_slope(ah, chan);
	ath9k_hw_spur_mitigate_freq(ah, chan);

	अगर (band_चयन || ini_reloaded)
		ah->eep_ops->set_board_values(ah, chan);

	ath9k_hw_init_bb(ah, chan);
	ath9k_hw_rfbus_करोne(ah);

	अगर (band_चयन || ini_reloaded) अणु
		ah->ah_flags |= AH_FASTCC;
		ath9k_hw_init_cal(ah, chan);
		ah->ah_flags &= ~AH_FASTCC;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम ath9k_hw_apply_gpio_override(काष्ठा ath_hw *ah)
अणु
	u32 gpio_mask = ah->gpio_mask;
	पूर्णांक i;

	क्रम (i = 0; gpio_mask; i++, gpio_mask >>= 1) अणु
		अगर (!(gpio_mask & 1))
			जारी;

		ath9k_hw_gpio_request_out(ah, i, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_OUTPUT);
		ath9k_hw_set_gpio(ah, i, !!(ah->gpio_val & BIT(i)));
		ath9k_hw_gpio_मुक्त(ah, i);
	पूर्ण
पूर्ण

व्योम ath9k_hw_check_nav(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 val;

	val = REG_READ(ah, AR_NAV);
	अगर (val != 0xdeadbeef && val > 0x7fff) अणु
		ath_dbg(common, BSTUCK, "Abnormal NAV: 0x%x\n", val);
		REG_WRITE(ah, AR_NAV, 0);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_check_nav);

bool ath9k_hw_check_alive(काष्ठा ath_hw *ah)
अणु
	पूर्णांक count = 50;
	u32 reg, last_val;

	/* Check अगर chip failed to wake up */
	अगर (REG_READ(ah, AR_CFG) == 0xdeadbeef)
		वापस false;

	अगर (AR_SREV_9300(ah))
		वापस !ath9k_hw_detect_mac_hang(ah);

	अगर (AR_SREV_9285_12_OR_LATER(ah))
		वापस true;

	last_val = REG_READ(ah, AR_OBS_BUS_1);
	करो अणु
		reg = REG_READ(ah, AR_OBS_BUS_1);
		अगर (reg != last_val)
			वापस true;

		udelay(1);
		last_val = reg;
		अगर ((reg & 0x7E7FFFEF) == 0x00702400)
			जारी;

		चयन (reg & 0x7E000B00) अणु
		हाल 0x1E000000:
		हाल 0x52000B00:
		हाल 0x18000B00:
			जारी;
		शेष:
			वापस true;
		पूर्ण
	पूर्ण जबतक (count-- > 0);

	वापस false;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_check_alive);

अटल व्योम ath9k_hw_init_mfp(काष्ठा ath_hw *ah)
अणु
	/* Setup MFP options क्रम CCMP */
	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		/* Mask Retry(b11), PwrMgt(b12), MoreData(b13) to 0 in mgmt
		 * frames when स्थिरructing CCMP AAD. */
		REG_RMW_FIELD(ah, AR_AES_MUTE_MASK1, AR_AES_MUTE_MASK1_FC_MGMT,
			      0xc7ff);
		अगर (AR_SREV_9271(ah) || AR_DEVID_7010(ah))
			ah->sw_mgmt_crypto_tx = true;
		अन्यथा
			ah->sw_mgmt_crypto_tx = false;
		ah->sw_mgmt_crypto_rx = false;
	पूर्ण अन्यथा अगर (AR_SREV_9160_10_OR_LATER(ah)) अणु
		/* Disable hardware crypto क्रम management frames */
		REG_CLR_BIT(ah, AR_PCU_MISC_MODE2,
			    AR_PCU_MISC_MODE2_MGMT_CRYPTO_ENABLE);
		REG_SET_BIT(ah, AR_PCU_MISC_MODE2,
			    AR_PCU_MISC_MODE2_NO_CRYPTO_FOR_NON_DATA_PKT);
		ah->sw_mgmt_crypto_tx = true;
		ah->sw_mgmt_crypto_rx = true;
	पूर्ण अन्यथा अणु
		ah->sw_mgmt_crypto_tx = true;
		ah->sw_mgmt_crypto_rx = true;
	पूर्ण
पूर्ण

अटल व्योम ath9k_hw_reset_opmode(काष्ठा ath_hw *ah,
				  u32 macStaId1, u32 saveDefAntenna)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_RMW(ah, AR_STA_ID1, macStaId1
		  | AR_STA_ID1_RTS_USE_DEF
		  | ah->sta_id1_शेषs,
		  ~AR_STA_ID1_SADH_MASK);
	ath_hw_setbssidmask(common);
	REG_WRITE(ah, AR_DEF_ANTENNA, saveDefAntenna);
	ath9k_hw_ग_लिखो_associd(ah);
	REG_WRITE(ah, AR_ISR, ~0);
	REG_WRITE(ah, AR_RSSI_THR, INIT_RSSI_THR);

	REGWRITE_BUFFER_FLUSH(ah);

	ath9k_hw_set_operating_mode(ah, ah->opmode);
पूर्ण

अटल व्योम ath9k_hw_init_queues(काष्ठा ath_hw *ah)
अणु
	पूर्णांक i;

	ENABLE_REGWRITE_BUFFER(ah);

	क्रम (i = 0; i < AR_NUM_DCU; i++)
		REG_WRITE(ah, AR_DQCUMASK(i), 1 << i);

	REGWRITE_BUFFER_FLUSH(ah);

	ah->पूर्णांकr_txqs = 0;
	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		ath9k_hw_resettxqueue(ah, i);
पूर्ण

/*
 * For big endian प्रणालीs turn on swapping क्रम descriptors
 */
अटल व्योम ath9k_hw_init_desc(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (AR_SREV_9100(ah)) अणु
		u32 mask;
		mask = REG_READ(ah, AR_CFG);
		अगर (mask & (AR_CFG_SWRB | AR_CFG_SWTB | AR_CFG_SWRG)) अणु
			ath_dbg(common, RESET, "CFG Byte Swap Set 0x%x\n",
				mask);
		पूर्ण अन्यथा अणु
			mask = INIT_CONFIG_STATUS | AR_CFG_SWRB | AR_CFG_SWTB;
			REG_WRITE(ah, AR_CFG, mask);
			ath_dbg(common, RESET, "Setting CFG 0x%x\n",
				REG_READ(ah, AR_CFG));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (common->bus_ops->ath_bus_type == ATH_USB) अणु
			/* Configure AR9271 target WLAN */
			अगर (AR_SREV_9271(ah))
				REG_WRITE(ah, AR_CFG, AR_CFG_SWRB | AR_CFG_SWTB);
			अन्यथा
				REG_WRITE(ah, AR_CFG, AR_CFG_SWTD | AR_CFG_SWRD);
		पूर्ण
#अगर_घोषित __BIG_ENDIAN
		अन्यथा अगर (AR_SREV_9330(ah) || AR_SREV_9340(ah) ||
			 AR_SREV_9550(ah) || AR_SREV_9531(ah) ||
			 AR_SREV_9561(ah))
			REG_RMW(ah, AR_CFG, AR_CFG_SWRB | AR_CFG_SWTB, 0);
		अन्यथा
			REG_WRITE(ah, AR_CFG, AR_CFG_SWTD | AR_CFG_SWRD);
#पूर्ण_अगर
	पूर्ण
पूर्ण

/*
 * Fast channel change:
 * (Change synthesizer based on channel freq without resetting chip)
 */
अटल पूर्णांक ath9k_hw_करो_fastcc(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	पूर्णांक ret;

	अगर (AR_SREV_9280(ah) && common->bus_ops->ath_bus_type == ATH_PCI)
		जाओ fail;

	अगर (ah->chip_fullsleep)
		जाओ fail;

	अगर (!ah->curchan)
		जाओ fail;

	अगर (chan->channel == ah->curchan->channel)
		जाओ fail;

	अगर ((ah->curchan->channelFlags | chan->channelFlags) &
	    (CHANNEL_HALF | CHANNEL_QUARTER))
		जाओ fail;

	/*
	 * If cross-band fcc is not supoprted, bail out अगर channelFlags dअगरfer.
	 */
	अगर (!(pCap->hw_caps & ATH9K_HW_CAP_FCC_BAND_SWITCH) &&
	    ((chan->channelFlags ^ ah->curchan->channelFlags) & ~CHANNEL_HT))
		जाओ fail;

	अगर (!ath9k_hw_check_alive(ah))
		जाओ fail;

	/*
	 * For AR9462, make sure that calibration data क्रम
	 * re-using are present.
	 */
	अगर (AR_SREV_9462(ah) && (ah->caldata &&
				 (!test_bit(TXIQCAL_DONE, &ah->caldata->cal_flags) ||
				  !test_bit(TXCLCAL_DONE, &ah->caldata->cal_flags) ||
				  !test_bit(RTT_DONE, &ah->caldata->cal_flags))))
		जाओ fail;

	ath_dbg(common, RESET, "FastChannelChange for %d -> %d\n",
		ah->curchan->channel, chan->channel);

	ret = ath9k_hw_channel_change(ah, chan);
	अगर (!ret)
		जाओ fail;

	अगर (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_2g5g_चयन(ah, false);

	ath9k_hw_loadnf(ah, ah->curchan);
	ath9k_hw_start_nfcal(ah, true);

	अगर (AR_SREV_9271(ah))
		ar9002_hw_load_ani_reg(ah, chan);

	वापस 0;
fail:
	वापस -EINVAL;
पूर्ण

u32 ath9k_hw_get_tsf_offset(काष्ठा बारpec64 *last, काष्ठा बारpec64 *cur)
अणु
	काष्ठा बारpec64 ts;
	s64 usec;

	अगर (!cur) अणु
		kसमय_get_raw_ts64(&ts);
		cur = &ts;
	पूर्ण

	usec = cur->tv_sec * 1000000ULL + cur->tv_nsec / 1000;
	usec -= last->tv_sec * 1000000ULL + last->tv_nsec / 1000;

	वापस (u32) usec;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_get_tsf_offset);

पूर्णांक ath9k_hw_reset(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
		   काष्ठा ath9k_hw_cal_data *caldata, bool fastcc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u32 saveLedState;
	u32 saveDefAntenna;
	u32 macStaId1;
	काष्ठा बारpec64 tsf_ts;
	u32 tsf_offset;
	u64 tsf = 0;
	पूर्णांक r;
	bool start_mci_reset = false;
	bool save_fullsleep = ah->chip_fullsleep;

	अगर (ath9k_hw_mci_is_enabled(ah)) अणु
		start_mci_reset = ar9003_mci_start_reset(ah, chan);
		अगर (start_mci_reset)
			वापस 0;
	पूर्ण

	अगर (!ath9k_hw_setघातer(ah, ATH9K_PM_AWAKE))
		वापस -EIO;

	अगर (ah->curchan && !ah->chip_fullsleep)
		ath9k_hw_getnf(ah, ah->curchan);

	ah->caldata = caldata;
	अगर (caldata && (chan->channel != caldata->channel ||
			chan->channelFlags != caldata->channelFlags)) अणु
		/* Operating channel changed, reset channel calibration data */
		स_रखो(caldata, 0, माप(*caldata));
		ath9k_init_nfcal_hist_buffer(ah, chan);
	पूर्ण अन्यथा अगर (caldata) अणु
		clear_bit(PAPRD_PACKET_SENT, &caldata->cal_flags);
	पूर्ण
	ah->noise = ath9k_hw_अ_लोhan_noise(ah, chan, chan->noiseन्यूनमान);

	अगर (fastcc) अणु
		r = ath9k_hw_करो_fastcc(ah, chan);
		अगर (!r)
			वापस r;
	पूर्ण

	अगर (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_stop_bt(ah, save_fullsleep);

	saveDefAntenna = REG_READ(ah, AR_DEF_ANTENNA);
	अगर (saveDefAntenna == 0)
		saveDefAntenna = 1;

	macStaId1 = REG_READ(ah, AR_STA_ID1) & AR_STA_ID1_BASE_RATE_11B;

	/* Save TSF beक्रमe chip reset, a cold reset clears it */
	kसमय_get_raw_ts64(&tsf_ts);
	tsf = ath9k_hw_gettsf64(ah);

	saveLedState = REG_READ(ah, AR_CFG_LED) &
		(AR_CFG_LED_ASSOC_CTL | AR_CFG_LED_MODE_SEL |
		 AR_CFG_LED_BLINK_THRESH_SEL | AR_CFG_LED_BLINK_SLOW);

	ath9k_hw_mark_phy_inactive(ah);

	ah->paprd_table_ग_लिखो_करोne = false;

	/* Only required on the first reset */
	अगर (AR_SREV_9271(ah) && ah->htc_reset_init) अणु
		REG_WRITE(ah,
			  AR9271_RESET_POWER_DOWN_CONTROL,
			  AR9271_RADIO_RF_RST);
		udelay(50);
	पूर्ण

	अगर (!ath9k_hw_chip_reset(ah, chan)) अणु
		ath_err(common, "Chip reset failed\n");
		वापस -EINVAL;
	पूर्ण

	/* Only required on the first reset */
	अगर (AR_SREV_9271(ah) && ah->htc_reset_init) अणु
		ah->htc_reset_init = false;
		REG_WRITE(ah,
			  AR9271_RESET_POWER_DOWN_CONTROL,
			  AR9271_GATE_MAC_CTL);
		udelay(50);
	पूर्ण

	/* Restore TSF */
	tsf_offset = ath9k_hw_get_tsf_offset(&tsf_ts, शून्य);
	ath9k_hw_settsf64(ah, tsf + tsf_offset);

	अगर (AR_SREV_9280_20_OR_LATER(ah))
		REG_SET_BIT(ah, AR_GPIO_INPUT_EN_VAL, AR_GPIO_JTAG_DISABLE);

	अगर (!AR_SREV_9300_20_OR_LATER(ah))
		ar9002_hw_enable_async_fअगरo(ah);

	r = ath9k_hw_process_ini(ah, chan);
	अगर (r)
		वापस r;

	ath9k_hw_set_rभ_शेषe(ah, chan);

	अगर (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_reset(ah, false, IS_CHAN_2GHZ(chan), save_fullsleep);

	/*
	 * Some AR91xx SoC devices frequently fail to accept TSF ग_लिखोs
	 * right after the chip reset. When that happens, ग_लिखो a new
	 * value after the initvals have been applied.
	 */
	अगर (AR_SREV_9100(ah) && (ath9k_hw_gettsf64(ah) < tsf)) अणु
		tsf_offset = ath9k_hw_get_tsf_offset(&tsf_ts, शून्य);
		ath9k_hw_settsf64(ah, tsf + tsf_offset);
	पूर्ण

	ath9k_hw_init_mfp(ah);

	ath9k_hw_set_delta_slope(ah, chan);
	ath9k_hw_spur_mitigate_freq(ah, chan);
	ah->eep_ops->set_board_values(ah, chan);

	ath9k_hw_reset_opmode(ah, macStaId1, saveDefAntenna);

	r = ath9k_hw_rf_set_freq(ah, chan);
	अगर (r)
		वापस r;

	ath9k_hw_set_घड़ीrate(ah);

	ath9k_hw_init_queues(ah);
	ath9k_hw_init_पूर्णांकerrupt_masks(ah, ah->opmode);
	ath9k_hw_ani_cache_ini_regs(ah);
	ath9k_hw_init_qos(ah);

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_RFSILENT)
		ath9k_hw_gpio_request_in(ah, ah->rfसमाप्त_gpio, "ath9k-rfkill");

	ath9k_hw_init_global_settings(ah);

	अगर (AR_SREV_9287(ah) && AR_SREV_9287_13_OR_LATER(ah)) अणु
		REG_SET_BIT(ah, AR_MAC_PCU_LOGIC_ANALYZER,
			    AR_MAC_PCU_LOGIC_ANALYZER_DISBUG20768);
		REG_RMW_FIELD(ah, AR_AHB_MODE, AR_AHB_CUSTOM_BURST_EN,
			      AR_AHB_CUSTOM_BURST_ASYNC_FIFO_VAL);
		REG_SET_BIT(ah, AR_PCU_MISC_MODE2,
			    AR_PCU_MISC_MODE2_ENABLE_AGGWEP);
	पूर्ण

	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PRESERVE_SEQNUM);

	ath9k_hw_set_dma(ah);

	अगर (!ath9k_hw_mci_is_enabled(ah))
		REG_WRITE(ah, AR_OBS, 8);

	ENABLE_REG_RMW_BUFFER(ah);
	अगर (ah->config.rx_पूर्णांकr_mitigation) अणु
		REG_RMW_FIELD(ah, AR_RIMT, AR_RIMT_LAST, ah->config.rimt_last);
		REG_RMW_FIELD(ah, AR_RIMT, AR_RIMT_FIRST, ah->config.rimt_first);
	पूर्ण

	अगर (ah->config.tx_पूर्णांकr_mitigation) अणु
		REG_RMW_FIELD(ah, AR_TIMT, AR_TIMT_LAST, 300);
		REG_RMW_FIELD(ah, AR_TIMT, AR_TIMT_FIRST, 750);
	पूर्ण
	REG_RMW_BUFFER_FLUSH(ah);

	ath9k_hw_init_bb(ah, chan);

	अगर (caldata) अणु
		clear_bit(TXIQCAL_DONE, &caldata->cal_flags);
		clear_bit(TXCLCAL_DONE, &caldata->cal_flags);
	पूर्ण
	अगर (!ath9k_hw_init_cal(ah, chan))
		वापस -EIO;

	अगर (ath9k_hw_mci_is_enabled(ah) && ar9003_mci_end_reset(ah, chan, caldata))
		वापस -EIO;

	ENABLE_REGWRITE_BUFFER(ah);

	ath9k_hw_restore_chainmask(ah);
	REG_WRITE(ah, AR_CFG_LED, saveLedState | AR_CFG_SCLK_32KHZ);

	REGWRITE_BUFFER_FLUSH(ah);

	ath9k_hw_gen_समयr_start_tsf2(ah);

	ath9k_hw_init_desc(ah);

	अगर (ath9k_hw_btcoex_is_enabled(ah))
		ath9k_hw_btcoex_enable(ah);

	अगर (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_check_bt(ah);

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		ath9k_hw_loadnf(ah, chan);
		ath9k_hw_start_nfcal(ah, true);
	पूर्ण

	अगर (AR_SREV_9300_20_OR_LATER(ah))
		ar9003_hw_bb_watchकरोg_config(ah);

	अगर (ah->config.hw_hang_checks & HW_PHYRESTART_CLC_WAR)
		ar9003_hw_disable_phy_restart(ah);

	ath9k_hw_apply_gpio_override(ah);

	अगर (AR_SREV_9565(ah) && common->bt_ant_भागersity)
		REG_SET_BIT(ah, AR_BTCOEX_WL_LNADIV, AR_BTCOEX_WL_LNADIV_FORCE_ON);

	अगर (ah->hw->conf.radar_enabled) अणु
		/* set HW specअगरic DFS configuration */
		ah->radar_conf.ext_channel = IS_CHAN_HT40(chan);
		ath9k_hw_set_radar_params(ah);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_reset);

/******************************/
/* Power Management (Chipset) */
/******************************/

/*
 * Notअगरy Power Mgt is disabled in self-generated frames.
 * If requested, क्रमce chip to sleep.
 */
अटल व्योम ath9k_set_घातer_sleep(काष्ठा ath_hw *ah)
अणु
	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		REG_CLR_BIT(ah, AR_TIMER_MODE, 0xff);
		REG_CLR_BIT(ah, AR_NDP2_TIMER_MODE, 0xff);
		REG_CLR_BIT(ah, AR_SLP32_INC, 0xfffff);
		/* xxx Required क्रम WLAN only हाल ? */
		REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_EN, 0);
		udelay(100);
	पूर्ण

	/*
	 * Clear the RTC क्रमce wake bit to allow the
	 * mac to go to sleep.
	 */
	REG_CLR_BIT(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN);

	अगर (ath9k_hw_mci_is_enabled(ah))
		udelay(100);

	अगर (!AR_SREV_9100(ah) && !AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_RC, AR_RC_AHB | AR_RC_HOSTIF);

	/* Shutकरोwn chip. Active low */
	अगर (!AR_SREV_5416(ah) && !AR_SREV_9271(ah)) अणु
		REG_CLR_BIT(ah, AR_RTC_RESET, AR_RTC_RESET_EN);
		udelay(2);
	पूर्ण

	/* Clear Bit 14 of AR_WA after putting chip पूर्णांकo Full Sleep mode. */
	अगर (AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_WA, ah->WARegVal & ~AR_WA_D3_L1_DISABLE);
पूर्ण

/*
 * Notअगरy Power Management is enabled in self-generating
 * frames. If request, set घातer mode of chip to
 * स्वतः/normal.  Duration in units of 128us (1/8 TU).
 */
अटल व्योम ath9k_set_घातer_network_sleep(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;

	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);

	अगर (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP)) अणु
		/* Set WakeOnInterrupt bit; clear ForceWake bit */
		REG_WRITE(ah, AR_RTC_FORCE_WAKE,
			  AR_RTC_FORCE_WAKE_ON_INT);
	पूर्ण अन्यथा अणु

		/* When chip goes पूर्णांकo network sleep, it could be waken
		 * up by MCI_INT पूर्णांकerrupt caused by BT's HW messages
		 * (LNA_xxx, CONT_xxx) which chould be in a very fast
		 * rate (~100us). This will cause chip to leave and
		 * re-enter network sleep mode frequently, which in
		 * consequence will have WLAN MCI HW to generate lots of
		 * SYS_WAKING and SYS_SLEEPING messages which will make
		 * BT CPU to busy to process.
		 */
		अगर (ath9k_hw_mci_is_enabled(ah))
			REG_CLR_BIT(ah, AR_MCI_INTERRUPT_RX_MSG_EN,
				    AR_MCI_INTERRUPT_RX_HW_MSG_MASK);
		/*
		 * Clear the RTC क्रमce wake bit to allow the
		 * mac to go to sleep.
		 */
		REG_CLR_BIT(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN);

		अगर (ath9k_hw_mci_is_enabled(ah))
			udelay(30);
	पूर्ण

	/* Clear Bit 14 of AR_WA after putting chip पूर्णांकo Net Sleep mode. */
	अगर (AR_SREV_9300_20_OR_LATER(ah))
		REG_WRITE(ah, AR_WA, ah->WARegVal & ~AR_WA_D3_L1_DISABLE);
पूर्ण

अटल bool ath9k_hw_set_घातer_awake(काष्ठा ath_hw *ah)
अणु
	u32 val;
	पूर्णांक i;

	/* Set Bits 14 and 17 of AR_WA beक्रमe घातering on the chip. */
	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		REG_WRITE(ah, AR_WA, ah->WARegVal);
		udelay(10);
	पूर्ण

	अगर ((REG_READ(ah, AR_RTC_STATUS) &
	     AR_RTC_STATUS_M) == AR_RTC_STATUS_SHUTDOWN) अणु
		अगर (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_POWER_ON)) अणु
			वापस false;
		पूर्ण
		अगर (!AR_SREV_9300_20_OR_LATER(ah))
			ath9k_hw_init_pll(ah, शून्य);
	पूर्ण
	अगर (AR_SREV_9100(ah))
		REG_SET_BIT(ah, AR_RTC_RESET,
			    AR_RTC_RESET_EN);

	REG_SET_BIT(ah, AR_RTC_FORCE_WAKE,
		    AR_RTC_FORCE_WAKE_EN);
	अगर (AR_SREV_9100(ah))
		mdelay(10);
	अन्यथा
		udelay(50);

	क्रम (i = POWER_UP_TIME / 50; i > 0; i--) अणु
		val = REG_READ(ah, AR_RTC_STATUS) & AR_RTC_STATUS_M;
		अगर (val == AR_RTC_STATUS_ON)
			अवरोध;
		udelay(50);
		REG_SET_BIT(ah, AR_RTC_FORCE_WAKE,
			    AR_RTC_FORCE_WAKE_EN);
	पूर्ण
	अगर (i == 0) अणु
		ath_err(ath9k_hw_common(ah),
			"Failed to wakeup in %uus\n",
			POWER_UP_TIME / 20);
		वापस false;
	पूर्ण

	अगर (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_set_घातer_awake(ah);

	REG_CLR_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);

	वापस true;
पूर्ण

bool ath9k_hw_setघातer(काष्ठा ath_hw *ah, क्रमागत ath9k_घातer_mode mode)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक status = true;
	अटल स्थिर अक्षर *modes[] = अणु
		"AWAKE",
		"FULL-SLEEP",
		"NETWORK SLEEP",
		"UNDEFINED"
	पूर्ण;

	अगर (ah->घातer_mode == mode)
		वापस status;

	ath_dbg(common, RESET, "%s -> %s\n",
		modes[ah->घातer_mode], modes[mode]);

	चयन (mode) अणु
	हाल ATH9K_PM_AWAKE:
		status = ath9k_hw_set_घातer_awake(ah);
		अवरोध;
	हाल ATH9K_PM_FULL_SLEEP:
		अगर (ath9k_hw_mci_is_enabled(ah))
			ar9003_mci_set_full_sleep(ah);

		ath9k_set_घातer_sleep(ah);
		ah->chip_fullsleep = true;
		अवरोध;
	हाल ATH9K_PM_NETWORK_SLEEP:
		ath9k_set_घातer_network_sleep(ah);
		अवरोध;
	शेष:
		ath_err(common, "Unknown power mode %u\n", mode);
		वापस false;
	पूर्ण
	ah->घातer_mode = mode;

	/*
	 * XXX: If this warning never comes up after a जबतक then
	 * simply keep the ATH_DBG_WARN_ON_ONCE() but make
	 * ath9k_hw_setघातer() वापस type व्योम.
	 */

	अगर (!(ah->ah_flags & AH_UNPLUGGED))
		ATH_DBG_WARN_ON_ONCE(!status);

	वापस status;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setघातer);

/*******************/
/* Beacon Handling */
/*******************/

व्योम ath9k_hw_beaconinit(काष्ठा ath_hw *ah, u32 next_beacon, u32 beacon_period)
अणु
	पूर्णांक flags = 0;

	ENABLE_REGWRITE_BUFFER(ah);

	चयन (ah->opmode) अणु
	हाल NL80211_IFTYPE_ADHOC:
		REG_SET_BIT(ah, AR_TXCFG,
			    AR_TXCFG_ADHOC_BEACON_ATIM_TX_POLICY);
		fallthrough;
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_AP:
		REG_WRITE(ah, AR_NEXT_TBTT_TIMER, next_beacon);
		REG_WRITE(ah, AR_NEXT_DMA_BEACON_ALERT, next_beacon -
			  TU_TO_USEC(ah->config.dma_beacon_response_समय));
		REG_WRITE(ah, AR_NEXT_SWBA, next_beacon -
			  TU_TO_USEC(ah->config.sw_beacon_response_समय));
		flags |=
			AR_TBTT_TIMER_EN | AR_DBA_TIMER_EN | AR_SWBA_TIMER_EN;
		अवरोध;
	शेष:
		ath_dbg(ath9k_hw_common(ah), BEACON,
			"%s: unsupported opmode: %d\n", __func__, ah->opmode);
		वापस;
	पूर्ण

	REG_WRITE(ah, AR_BEACON_PERIOD, beacon_period);
	REG_WRITE(ah, AR_DMA_BEACON_PERIOD, beacon_period);
	REG_WRITE(ah, AR_SWBA_PERIOD, beacon_period);

	REGWRITE_BUFFER_FLUSH(ah);

	REG_SET_BIT(ah, AR_TIMER_MODE, flags);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_beaconinit);

व्योम ath9k_hw_set_sta_beacon_समयrs(काष्ठा ath_hw *ah,
				    स्थिर काष्ठा ath9k_beacon_state *bs)
अणु
	u32 nextTbtt, beaconपूर्णांकval, dtimperiod, beaconसमयout;
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_NEXT_TBTT_TIMER, bs->bs_nexttbtt);
	REG_WRITE(ah, AR_BEACON_PERIOD, bs->bs_पूर्णांकval);
	REG_WRITE(ah, AR_DMA_BEACON_PERIOD, bs->bs_पूर्णांकval);

	REGWRITE_BUFFER_FLUSH(ah);

	REG_RMW_FIELD(ah, AR_RSSI_THR,
		      AR_RSSI_THR_BM_THR, bs->bs_bmissthreshold);

	beaconपूर्णांकval = bs->bs_पूर्णांकval;

	अगर (bs->bs_sleepduration > beaconपूर्णांकval)
		beaconपूर्णांकval = bs->bs_sleepduration;

	dtimperiod = bs->bs_dtimperiod;
	अगर (bs->bs_sleepduration > dtimperiod)
		dtimperiod = bs->bs_sleepduration;

	अगर (beaconपूर्णांकval == dtimperiod)
		nextTbtt = bs->bs_nextdtim;
	अन्यथा
		nextTbtt = bs->bs_nexttbtt;

	ath_dbg(common, BEACON, "next DTIM %u\n", bs->bs_nextdtim);
	ath_dbg(common, BEACON, "next beacon %u\n", nextTbtt);
	ath_dbg(common, BEACON, "beacon period %u\n", beaconपूर्णांकval);
	ath_dbg(common, BEACON, "DTIM period %u\n", dtimperiod);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_NEXT_DTIM, bs->bs_nextdtim - SLEEP_SLOP);
	REG_WRITE(ah, AR_NEXT_TIM, nextTbtt - SLEEP_SLOP);

	REG_WRITE(ah, AR_SLEEP1,
		  SM((CAB_TIMEOUT_VAL << 3), AR_SLEEP1_CAB_TIMEOUT)
		  | AR_SLEEP1_ASSUME_DTIM);

	अगर (pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP)
		beaconसमयout = (BEACON_TIMEOUT_VAL << 3);
	अन्यथा
		beaconसमयout = MIN_BEACON_TIMEOUT_VAL;

	REG_WRITE(ah, AR_SLEEP2,
		  SM(beaconसमयout, AR_SLEEP2_BEACON_TIMEOUT));

	REG_WRITE(ah, AR_TIM_PERIOD, beaconपूर्णांकval);
	REG_WRITE(ah, AR_DTIM_PERIOD, dtimperiod);

	REGWRITE_BUFFER_FLUSH(ah);

	REG_SET_BIT(ah, AR_TIMER_MODE,
		    AR_TBTT_TIMER_EN | AR_TIM_TIMER_EN |
		    AR_DTIM_TIMER_EN);

	/* TSF Out of Range Threshold */
	REG_WRITE(ah, AR_TSFOOR_THRESHOLD, bs->bs_tsfoor_threshold);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_sta_beacon_समयrs);

/*******************/
/* HW Capabilities */
/*******************/

अटल u8 fixup_chainmask(u8 chip_chainmask, u8 eeprom_chainmask)
अणु
	eeprom_chainmask &= chip_chainmask;
	अगर (eeprom_chainmask)
		वापस eeprom_chainmask;
	अन्यथा
		वापस chip_chainmask;
पूर्ण

/**
 * ath9k_hw_dfs_tested - checks अगर DFS has been tested with used chipset
 * @ah: the atheros hardware data काष्ठाure
 *
 * We enable DFS support upstream on chipsets which have passed a series
 * of tests. The testing requirements are going to be करोcumented. Desired
 * test requirements are करोcumented at:
 *
 * https://wireless.wiki.kernel.org/en/users/Drivers/ath9k/dfs
 *
 * Once a new chipset माला_लो properly tested an inभागidual commit can be used
 * to करोcument the testing क्रम DFS क्रम that chipset.
 */
अटल bool ath9k_hw_dfs_tested(काष्ठा ath_hw *ah)
अणु

	चयन (ah->hw_version.macVersion) अणु
	/* क्रम temporary testing DFS with 9280 */
	हाल AR_SREV_VERSION_9280:
	/* AR9580 will likely be our first target to get testing on */
	हाल AR_SREV_VERSION_9580:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम ath9k_gpio_cap_init(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;

	अगर (AR_SREV_9271(ah)) अणु
		pCap->num_gpio_pins = AR9271_NUM_GPIO;
		pCap->gpio_mask = AR9271_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_DEVID_7010(ah)) अणु
		pCap->num_gpio_pins = AR7010_NUM_GPIO;
		pCap->gpio_mask = AR7010_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9287(ah)) अणु
		pCap->num_gpio_pins = AR9287_NUM_GPIO;
		pCap->gpio_mask = AR9287_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9285(ah)) अणु
		pCap->num_gpio_pins = AR9285_NUM_GPIO;
		pCap->gpio_mask = AR9285_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9280(ah)) अणु
		pCap->num_gpio_pins = AR9280_NUM_GPIO;
		pCap->gpio_mask = AR9280_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9300(ah)) अणु
		pCap->num_gpio_pins = AR9300_NUM_GPIO;
		pCap->gpio_mask = AR9300_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9330(ah)) अणु
		pCap->num_gpio_pins = AR9330_NUM_GPIO;
		pCap->gpio_mask = AR9330_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9340(ah)) अणु
		pCap->num_gpio_pins = AR9340_NUM_GPIO;
		pCap->gpio_mask = AR9340_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9462(ah)) अणु
		pCap->num_gpio_pins = AR9462_NUM_GPIO;
		pCap->gpio_mask = AR9462_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9485(ah)) अणु
		pCap->num_gpio_pins = AR9485_NUM_GPIO;
		pCap->gpio_mask = AR9485_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9531(ah)) अणु
		pCap->num_gpio_pins = AR9531_NUM_GPIO;
		pCap->gpio_mask = AR9531_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9550(ah)) अणु
		pCap->num_gpio_pins = AR9550_NUM_GPIO;
		pCap->gpio_mask = AR9550_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9561(ah)) अणु
		pCap->num_gpio_pins = AR9561_NUM_GPIO;
		pCap->gpio_mask = AR9561_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9565(ah)) अणु
		pCap->num_gpio_pins = AR9565_NUM_GPIO;
		pCap->gpio_mask = AR9565_GPIO_MASK;
	पूर्ण अन्यथा अगर (AR_SREV_9580(ah)) अणु
		pCap->num_gpio_pins = AR9580_NUM_GPIO;
		pCap->gpio_mask = AR9580_GPIO_MASK;
	पूर्ण अन्यथा अणु
		pCap->num_gpio_pins = AR_NUM_GPIO;
		pCap->gpio_mask = AR_GPIO_MASK;
	पूर्ण
पूर्ण

पूर्णांक ath9k_hw_fill_cap_info(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	काष्ठा ath_regulatory *regulatory = ath9k_hw_regulatory(ah);
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	u16 eeval;
	u8 ant_भाग_ctl1, tx_chainmask, rx_chainmask;

	eeval = ah->eep_ops->get_eeprom(ah, EEP_REG_0);
	regulatory->current_rd = eeval;

	अगर (ah->opmode != NL80211_IFTYPE_AP &&
	    ah->hw_version.subvenकरोrid == AR_SUBVENDOR_ID_NEW_A) अणु
		अगर (regulatory->current_rd == 0x64 ||
		    regulatory->current_rd == 0x65)
			regulatory->current_rd += 5;
		अन्यथा अगर (regulatory->current_rd == 0x41)
			regulatory->current_rd = 0x43;
		ath_dbg(common, REGULATORY, "regdomain mapped to 0x%x\n",
			regulatory->current_rd);
	पूर्ण

	eeval = ah->eep_ops->get_eeprom(ah, EEP_OP_MODE);

	अगर (eeval & AR5416_OPFLAGS_11A) अणु
		अगर (ah->disable_5ghz)
			ath_warn(common, "disabling 5GHz band\n");
		अन्यथा
			pCap->hw_caps |= ATH9K_HW_CAP_5GHZ;
	पूर्ण

	अगर (eeval & AR5416_OPFLAGS_11G) अणु
		अगर (ah->disable_2ghz)
			ath_warn(common, "disabling 2GHz band\n");
		अन्यथा
			pCap->hw_caps |= ATH9K_HW_CAP_2GHZ;
	पूर्ण

	अगर ((pCap->hw_caps & (ATH9K_HW_CAP_2GHZ | ATH9K_HW_CAP_5GHZ)) == 0) अणु
		ath_err(common, "both bands are disabled\n");
		वापस -EINVAL;
	पूर्ण

	ath9k_gpio_cap_init(ah);

	अगर (AR_SREV_9485(ah) ||
	    AR_SREV_9285(ah) ||
	    AR_SREV_9330(ah) ||
	    AR_SREV_9565(ah))
		pCap->chip_chainmask = 1;
	अन्यथा अगर (!AR_SREV_9280_20_OR_LATER(ah))
		pCap->chip_chainmask = 7;
	अन्यथा अगर (!AR_SREV_9300_20_OR_LATER(ah) ||
		 AR_SREV_9340(ah) ||
		 AR_SREV_9462(ah) ||
		 AR_SREV_9531(ah))
		pCap->chip_chainmask = 3;
	अन्यथा
		pCap->chip_chainmask = 7;

	pCap->tx_chainmask = ah->eep_ops->get_eeprom(ah, EEP_TX_MASK);
	/*
	 * For AR9271 we will temporarilly uses the rx chainmax as पढ़ो from
	 * the EEPROM.
	 */
	अगर ((ah->hw_version.devid == AR5416_DEVID_PCI) &&
	    !(eeval & AR5416_OPFLAGS_11A) &&
	    !(AR_SREV_9271(ah)))
		/* CB71: GPIO 0 is pulled करोwn to indicate 3 rx chains */
		pCap->rx_chainmask = ath9k_hw_gpio_get(ah, 0) ? 0x5 : 0x7;
	अन्यथा अगर (AR_SREV_9100(ah))
		pCap->rx_chainmask = 0x7;
	अन्यथा
		/* Use rx_chainmask from EEPROM. */
		pCap->rx_chainmask = ah->eep_ops->get_eeprom(ah, EEP_RX_MASK);

	pCap->tx_chainmask = fixup_chainmask(pCap->chip_chainmask, pCap->tx_chainmask);
	pCap->rx_chainmask = fixup_chainmask(pCap->chip_chainmask, pCap->rx_chainmask);
	ah->txchainmask = pCap->tx_chainmask;
	ah->rxchainmask = pCap->rx_chainmask;

	ah->misc_mode |= AR_PCU_MIC_NEW_LOC_ENA;

	/* enable key search क्रम every frame in an aggregate */
	अगर (AR_SREV_9300_20_OR_LATER(ah))
		ah->misc_mode |= AR_PCU_ALWAYS_PERFORM_KEYSEARCH;

	common->crypt_caps |= ATH_CRYPT_CAP_CIPHER_AESCCM;

	अगर (ah->hw_version.devid != AR2427_DEVID_PCIE)
		pCap->hw_caps |= ATH9K_HW_CAP_HT;
	अन्यथा
		pCap->hw_caps &= ~ATH9K_HW_CAP_HT;

	अगर (AR_SREV_9160_10_OR_LATER(ah) || AR_SREV_9100(ah))
		pCap->rts_aggr_limit = ATH_AMPDU_LIMIT_MAX;
	अन्यथा
		pCap->rts_aggr_limit = (8 * 1024);

#अगर_घोषित CONFIG_ATH9K_RFKILL
	ah->rfsilent = ah->eep_ops->get_eeprom(ah, EEP_RF_SILENT);
	अगर (ah->rfsilent & EEP_RFSILENT_ENABLED) अणु
		ah->rfसमाप्त_gpio =
			MS(ah->rfsilent, EEP_RFSILENT_GPIO_SEL);
		ah->rfसमाप्त_polarity =
			MS(ah->rfsilent, EEP_RFSILENT_POLARITY);

		pCap->hw_caps |= ATH9K_HW_CAP_RFSILENT;
	पूर्ण
#पूर्ण_अगर
	अगर (AR_SREV_9271(ah) || AR_SREV_9300_20_OR_LATER(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_AUTOSLEEP;
	अन्यथा
		pCap->hw_caps &= ~ATH9K_HW_CAP_AUTOSLEEP;

	अगर (AR_SREV_9280(ah) || AR_SREV_9285(ah))
		pCap->hw_caps &= ~ATH9K_HW_CAP_4KB_SPLITTRANS;
	अन्यथा
		pCap->hw_caps |= ATH9K_HW_CAP_4KB_SPLITTRANS;

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		pCap->hw_caps |= ATH9K_HW_CAP_EDMA | ATH9K_HW_CAP_FASTCLOCK;
		अगर (!AR_SREV_9330(ah) && !AR_SREV_9485(ah) &&
		    !AR_SREV_9561(ah) && !AR_SREV_9565(ah))
			pCap->hw_caps |= ATH9K_HW_CAP_LDPC;

		pCap->rx_hp_qdepth = ATH9K_HW_RX_HP_QDEPTH;
		pCap->rx_lp_qdepth = ATH9K_HW_RX_LP_QDEPTH;
		pCap->rx_status_len = माप(काष्ठा ar9003_rxs);
		pCap->tx_desc_len = माप(काष्ठा ar9003_txc);
		pCap->txs_len = माप(काष्ठा ar9003_txs);
	पूर्ण अन्यथा अणु
		pCap->tx_desc_len = माप(काष्ठा ath_desc);
		अगर (AR_SREV_9280_20(ah))
			pCap->hw_caps |= ATH9K_HW_CAP_FASTCLOCK;
	पूर्ण

	अगर (AR_SREV_9300_20_OR_LATER(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_RAC_SUPPORTED;

	अगर (AR_SREV_9561(ah))
		ah->ent_mode = 0x3BDA000;
	अन्यथा अगर (AR_SREV_9300_20_OR_LATER(ah))
		ah->ent_mode = REG_READ(ah, AR_ENT_OTP);

	अगर (AR_SREV_9287_11_OR_LATER(ah) || AR_SREV_9271(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_SGI_20;

	अगर (AR_SREV_9285(ah)) अणु
		अगर (ah->eep_ops->get_eeprom(ah, EEP_MODAL_VER) >= 3) अणु
			ant_भाग_ctl1 =
				ah->eep_ops->get_eeprom(ah, EEP_ANT_DIV_CTL1);
			अगर ((ant_भाग_ctl1 & 0x1) && ((ant_भाग_ctl1 >> 3) & 0x1)) अणु
				pCap->hw_caps |= ATH9K_HW_CAP_ANT_DIV_COMB;
				ath_info(common, "Enable LNA combining\n");
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		अगर (ah->eep_ops->get_eeprom(ah, EEP_CHAIN_MASK_REDUCE))
			pCap->hw_caps |= ATH9K_HW_CAP_APM;
	पूर्ण

	अगर (AR_SREV_9330(ah) || AR_SREV_9485(ah) || AR_SREV_9565(ah)) अणु
		ant_भाग_ctl1 = ah->eep_ops->get_eeprom(ah, EEP_ANT_DIV_CTL1);
		अगर ((ant_भाग_ctl1 >> 0x6) == 0x3) अणु
			pCap->hw_caps |= ATH9K_HW_CAP_ANT_DIV_COMB;
			ath_info(common, "Enable LNA combining\n");
		पूर्ण
	पूर्ण

	अगर (ath9k_hw_dfs_tested(ah))
		pCap->hw_caps |= ATH9K_HW_CAP_DFS;

	tx_chainmask = pCap->tx_chainmask;
	rx_chainmask = pCap->rx_chainmask;
	जबतक (tx_chainmask || rx_chainmask) अणु
		अगर (tx_chainmask & BIT(0))
			pCap->max_txchains++;
		अगर (rx_chainmask & BIT(0))
			pCap->max_rxchains++;

		tx_chainmask >>= 1;
		rx_chainmask >>= 1;
	पूर्ण

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		अगर (!(ah->ent_mode & AR_ENT_OTP_49GHZ_DISABLE))
			pCap->hw_caps |= ATH9K_HW_CAP_MCI;

		अगर (AR_SREV_9462_20_OR_LATER(ah))
			pCap->hw_caps |= ATH9K_HW_CAP_RTT;
	पूर्ण

	अगर (AR_SREV_9300_20_OR_LATER(ah) &&
	    ah->eep_ops->get_eeprom(ah, EEP_PAPRD))
			pCap->hw_caps |= ATH9K_HW_CAP_PAPRD;

#अगर_घोषित CONFIG_ATH9K_WOW
	अगर (AR_SREV_9462_20_OR_LATER(ah) || AR_SREV_9565_11_OR_LATER(ah))
		ah->wow.max_patterns = MAX_NUM_PATTERN;
	अन्यथा
		ah->wow.max_patterns = MAX_NUM_PATTERN_LEGACY;
#पूर्ण_अगर

	वापस 0;
पूर्ण

/****************************/
/* GPIO / RFKILL / Antennae */
/****************************/

अटल व्योम ath9k_hw_gpio_cfg_output_mux(काष्ठा ath_hw *ah, u32 gpio, u32 type)
अणु
	पूर्णांक addr;
	u32 gpio_shअगरt, पंचांगp;

	अगर (gpio > 11)
		addr = AR_GPIO_OUTPUT_MUX3;
	अन्यथा अगर (gpio > 5)
		addr = AR_GPIO_OUTPUT_MUX2;
	अन्यथा
		addr = AR_GPIO_OUTPUT_MUX1;

	gpio_shअगरt = (gpio % 6) * 5;

	अगर (AR_SREV_9280_20_OR_LATER(ah) ||
	    (addr != AR_GPIO_OUTPUT_MUX1)) अणु
		REG_RMW(ah, addr, (type << gpio_shअगरt),
			(0x1f << gpio_shअगरt));
	पूर्ण अन्यथा अणु
		पंचांगp = REG_READ(ah, addr);
		पंचांगp = ((पंचांगp & 0x1F0) << 1) | (पंचांगp & ~0x1F0);
		पंचांगp &= ~(0x1f << gpio_shअगरt);
		पंचांगp |= (type << gpio_shअगरt);
		REG_WRITE(ah, addr, पंचांगp);
	पूर्ण
पूर्ण

/* BSP should set the corresponding MUX रेजिस्टर correctly.
 */
अटल व्योम ath9k_hw_gpio_cfg_soc(काष्ठा ath_hw *ah, u32 gpio, bool out,
				  स्थिर अक्षर *label)
अणु
	अगर (ah->caps.gpio_requested & BIT(gpio))
		वापस;

	/* may be requested by BSP, मुक्त anyway */
	gpio_मुक्त(gpio);

	अगर (gpio_request_one(gpio, out ? GPIOF_OUT_INIT_LOW : GPIOF_IN, label))
		वापस;

	ah->caps.gpio_requested |= BIT(gpio);
पूर्ण

अटल व्योम ath9k_hw_gpio_cfg_wmac(काष्ठा ath_hw *ah, u32 gpio, bool out,
				   u32 ah_संकेत_type)
अणु
	u32 gpio_set, gpio_shअगरt = gpio;

	अगर (AR_DEVID_7010(ah)) अणु
		gpio_set = out ?
			AR7010_GPIO_OE_AS_OUTPUT : AR7010_GPIO_OE_AS_INPUT;
		REG_RMW(ah, AR7010_GPIO_OE, gpio_set << gpio_shअगरt,
			AR7010_GPIO_OE_MASK << gpio_shअगरt);
	पूर्ण अन्यथा अगर (AR_SREV_SOC(ah)) अणु
		gpio_set = out ? 1 : 0;
		REG_RMW(ah, AR_GPIO_OE_OUT, gpio_set << gpio_shअगरt,
			gpio_set << gpio_shअगरt);
	पूर्ण अन्यथा अणु
		gpio_shअगरt = gpio << 1;
		gpio_set = out ?
			AR_GPIO_OE_OUT_DRV_ALL : AR_GPIO_OE_OUT_DRV_NO;
		REG_RMW(ah, AR_GPIO_OE_OUT, gpio_set << gpio_shअगरt,
			AR_GPIO_OE_OUT_DRV << gpio_shअगरt);

		अगर (out)
			ath9k_hw_gpio_cfg_output_mux(ah, gpio, ah_संकेत_type);
	पूर्ण
पूर्ण

अटल व्योम ath9k_hw_gpio_request(काष्ठा ath_hw *ah, u32 gpio, bool out,
				  स्थिर अक्षर *label, u32 ah_संकेत_type)
अणु
	WARN_ON(gpio >= ah->caps.num_gpio_pins);

	अगर (BIT(gpio) & ah->caps.gpio_mask)
		ath9k_hw_gpio_cfg_wmac(ah, gpio, out, ah_संकेत_type);
	अन्यथा अगर (AR_SREV_SOC(ah))
		ath9k_hw_gpio_cfg_soc(ah, gpio, out, label);
	अन्यथा
		WARN_ON(1);
पूर्ण

व्योम ath9k_hw_gpio_request_in(काष्ठा ath_hw *ah, u32 gpio, स्थिर अक्षर *label)
अणु
	ath9k_hw_gpio_request(ah, gpio, false, label, 0);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gpio_request_in);

व्योम ath9k_hw_gpio_request_out(काष्ठा ath_hw *ah, u32 gpio, स्थिर अक्षर *label,
			       u32 ah_संकेत_type)
अणु
	ath9k_hw_gpio_request(ah, gpio, true, label, ah_संकेत_type);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gpio_request_out);

व्योम ath9k_hw_gpio_मुक्त(काष्ठा ath_hw *ah, u32 gpio)
अणु
	अगर (!AR_SREV_SOC(ah))
		वापस;

	WARN_ON(gpio >= ah->caps.num_gpio_pins);

	अगर (ah->caps.gpio_requested & BIT(gpio)) अणु
		gpio_मुक्त(gpio);
		ah->caps.gpio_requested &= ~BIT(gpio);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gpio_मुक्त);

u32 ath9k_hw_gpio_get(काष्ठा ath_hw *ah, u32 gpio)
अणु
	u32 val = 0xffffffff;

#घोषणा MS_REG_READ(x, y) \
	(MS(REG_READ(ah, AR_GPIO_IN_OUT), x##_GPIO_IN_VAL) & BIT(y))

	WARN_ON(gpio >= ah->caps.num_gpio_pins);

	अगर (BIT(gpio) & ah->caps.gpio_mask) अणु
		अगर (AR_SREV_9271(ah))
			val = MS_REG_READ(AR9271, gpio);
		अन्यथा अगर (AR_SREV_9287(ah))
			val = MS_REG_READ(AR9287, gpio);
		अन्यथा अगर (AR_SREV_9285(ah))
			val = MS_REG_READ(AR9285, gpio);
		अन्यथा अगर (AR_SREV_9280(ah))
			val = MS_REG_READ(AR928X, gpio);
		अन्यथा अगर (AR_DEVID_7010(ah))
			val = REG_READ(ah, AR7010_GPIO_IN) & BIT(gpio);
		अन्यथा अगर (AR_SREV_9300_20_OR_LATER(ah))
			val = REG_READ(ah, AR_GPIO_IN) & BIT(gpio);
		अन्यथा
			val = MS_REG_READ(AR, gpio);
	पूर्ण अन्यथा अगर (BIT(gpio) & ah->caps.gpio_requested) अणु
		val = gpio_get_value(gpio) & BIT(gpio);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
	पूर्ण

	वापस !!val;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gpio_get);

व्योम ath9k_hw_set_gpio(काष्ठा ath_hw *ah, u32 gpio, u32 val)
अणु
	WARN_ON(gpio >= ah->caps.num_gpio_pins);

	अगर (AR_DEVID_7010(ah) || AR_SREV_9271(ah))
		val = !val;
	अन्यथा
		val = !!val;

	अगर (BIT(gpio) & ah->caps.gpio_mask) अणु
		u32 out_addr = AR_DEVID_7010(ah) ?
			AR7010_GPIO_OUT : AR_GPIO_IN_OUT;

		REG_RMW(ah, out_addr, val << gpio, BIT(gpio));
	पूर्ण अन्यथा अगर (BIT(gpio) & ah->caps.gpio_requested) अणु
		gpio_set_value(gpio, val);
	पूर्ण अन्यथा अणु
		WARN_ON(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_gpio);

व्योम ath9k_hw_setantenna(काष्ठा ath_hw *ah, u32 antenna)
अणु
	REG_WRITE(ah, AR_DEF_ANTENNA, (antenna & 0x7));
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setantenna);

/*********************/
/* General Operation */
/*********************/

u32 ath9k_hw_getrxfilter(काष्ठा ath_hw *ah)
अणु
	u32 bits = REG_READ(ah, AR_RX_FILTER);
	u32 phybits = REG_READ(ah, AR_PHY_ERR);

	अगर (phybits & AR_PHY_ERR_RADAR)
		bits |= ATH9K_RX_FILTER_PHYRADAR;
	अगर (phybits & (AR_PHY_ERR_OFDM_TIMING | AR_PHY_ERR_CCK_TIMING))
		bits |= ATH9K_RX_FILTER_PHYERR;

	वापस bits;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_getrxfilter);

व्योम ath9k_hw_setrxfilter(काष्ठा ath_hw *ah, u32 bits)
अणु
	u32 phybits;

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_RX_FILTER, bits);

	phybits = 0;
	अगर (bits & ATH9K_RX_FILTER_PHYRADAR)
		phybits |= AR_PHY_ERR_RADAR;
	अगर (bits & ATH9K_RX_FILTER_PHYERR)
		phybits |= AR_PHY_ERR_OFDM_TIMING | AR_PHY_ERR_CCK_TIMING;
	REG_WRITE(ah, AR_PHY_ERR, phybits);

	अगर (phybits)
		REG_SET_BIT(ah, AR_RXCFG, AR_RXCFG_ZLFDMA);
	अन्यथा
		REG_CLR_BIT(ah, AR_RXCFG, AR_RXCFG_ZLFDMA);

	REGWRITE_BUFFER_FLUSH(ah);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setrxfilter);

bool ath9k_hw_phy_disable(काष्ठा ath_hw *ah)
अणु
	अगर (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_bt_gain_ctrl(ah);

	अगर (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_WARM))
		वापस false;

	ath9k_hw_init_pll(ah, शून्य);
	ah->htc_reset_init = true;
	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_phy_disable);

bool ath9k_hw_disable(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_setघातer(ah, ATH9K_PM_AWAKE))
		वापस false;

	अगर (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_COLD))
		वापस false;

	ath9k_hw_init_pll(ah, शून्य);
	वापस true;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_disable);

अटल पूर्णांक get_antenna_gain(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	क्रमागत eeprom_param gain_param;

	अगर (IS_CHAN_2GHZ(chan))
		gain_param = EEP_ANTENNA_GAIN_2G;
	अन्यथा
		gain_param = EEP_ANTENNA_GAIN_5G;

	वापस ah->eep_ops->get_eeprom(ah, gain_param);
पूर्ण

व्योम ath9k_hw_apply_txघातer(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan,
			    bool test)
अणु
	काष्ठा ath_regulatory *reg = ath9k_hw_regulatory(ah);
	काष्ठा ieee80211_channel *channel;
	पूर्णांक chan_pwr, new_pwr;
	u16 ctl = NO_CTL;

	अगर (!chan)
		वापस;

	अगर (!test)
		ctl = ath9k_regd_get_ctl(reg, chan);

	channel = chan->chan;
	chan_pwr = min_t(पूर्णांक, channel->max_घातer * 2, MAX_COMBINED_POWER);
	new_pwr = min_t(पूर्णांक, chan_pwr, reg->घातer_limit);

	ah->eep_ops->set_txघातer(ah, chan, ctl,
				 get_antenna_gain(ah, chan), new_pwr, test);
पूर्ण

व्योम ath9k_hw_set_txघातerlimit(काष्ठा ath_hw *ah, u32 limit, bool test)
अणु
	काष्ठा ath_regulatory *reg = ath9k_hw_regulatory(ah);
	काष्ठा ath9k_channel *chan = ah->curchan;
	काष्ठा ieee80211_channel *channel = chan->chan;

	reg->घातer_limit = min_t(u32, limit, MAX_COMBINED_POWER);
	अगर (test)
		channel->max_घातer = MAX_COMBINED_POWER / 2;

	ath9k_hw_apply_txघातer(ah, chan, test);

	अगर (test)
		channel->max_घातer = DIV_ROUND_UP(reg->max_घातer_level, 2);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_txघातerlimit);

व्योम ath9k_hw_setopmode(काष्ठा ath_hw *ah)
अणु
	ath9k_hw_set_operating_mode(ah, ah->opmode);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_setopmode);

व्योम ath9k_hw_seपंचांगcastfilter(काष्ठा ath_hw *ah, u32 filter0, u32 filter1)
अणु
	REG_WRITE(ah, AR_MCAST_FIL0, filter0);
	REG_WRITE(ah, AR_MCAST_FIL1, filter1);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_seपंचांगcastfilter);

व्योम ath9k_hw_ग_लिखो_associd(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	REG_WRITE(ah, AR_BSS_ID0, get_unaligned_le32(common->curbssid));
	REG_WRITE(ah, AR_BSS_ID1, get_unaligned_le16(common->curbssid + 4) |
		  ((common->curaid & 0x3fff) << AR_BSS_ID1_AID_S));
पूर्ण
EXPORT_SYMBOL(ath9k_hw_ग_लिखो_associd);

#घोषणा ATH9K_MAX_TSF_READ 10

u64 ath9k_hw_gettsf64(काष्ठा ath_hw *ah)
अणु
	u32 tsf_lower, tsf_upper1, tsf_upper2;
	पूर्णांक i;

	tsf_upper1 = REG_READ(ah, AR_TSF_U32);
	क्रम (i = 0; i < ATH9K_MAX_TSF_READ; i++) अणु
		tsf_lower = REG_READ(ah, AR_TSF_L32);
		tsf_upper2 = REG_READ(ah, AR_TSF_U32);
		अगर (tsf_upper2 == tsf_upper1)
			अवरोध;
		tsf_upper1 = tsf_upper2;
	पूर्ण

	WARN_ON( i == ATH9K_MAX_TSF_READ );

	वापस (((u64)tsf_upper1 << 32) | tsf_lower);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gettsf64);

व्योम ath9k_hw_settsf64(काष्ठा ath_hw *ah, u64 tsf64)
अणु
	REG_WRITE(ah, AR_TSF_L32, tsf64 & 0xffffffff);
	REG_WRITE(ah, AR_TSF_U32, (tsf64 >> 32) & 0xffffffff);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_settsf64);

व्योम ath9k_hw_reset_tsf(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_रुको(ah, AR_SLP32_MODE, AR_SLP32_TSF_WRITE_STATUS, 0,
			   AH_TSF_WRITE_TIMEOUT))
		ath_dbg(ath9k_hw_common(ah), RESET,
			"AR_SLP32_TSF_WRITE_STATUS limit exceeded\n");

	REG_WRITE(ah, AR_RESET_TSF, AR_RESET_TSF_ONCE);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_reset_tsf);

व्योम ath9k_hw_set_tsfadjust(काष्ठा ath_hw *ah, bool set)
अणु
	अगर (set)
		ah->misc_mode |= AR_PCU_TX_ADD_TSF;
	अन्यथा
		ah->misc_mode &= ~AR_PCU_TX_ADD_TSF;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_set_tsfadjust);

व्योम ath9k_hw_set11nmac2040(काष्ठा ath_hw *ah, काष्ठा ath9k_channel *chan)
अणु
	u32 macmode;

	अगर (IS_CHAN_HT40(chan) && !ah->config.cwm_ignore_extcca)
		macmode = AR_2040_JOINED_RX_CLEAR;
	अन्यथा
		macmode = 0;

	REG_WRITE(ah, AR_2040_MODE, macmode);
पूर्ण

/* HW Generic समयrs configuration */

अटल स्थिर काष्ठा ath_gen_समयr_configuration gen_पंचांगr_configuration[] =
अणु
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP_TIMER, AR_NDP_PERIOD, AR_TIMER_MODE, 0x0080पूर्ण,
	अणुAR_NEXT_NDP2_TIMER, AR_NDP2_PERIOD, AR_NDP2_TIMER_MODE, 0x0001पूर्ण,
	अणुAR_NEXT_NDP2_TIMER + 1*4, AR_NDP2_PERIOD + 1*4,
				AR_NDP2_TIMER_MODE, 0x0002पूर्ण,
	अणुAR_NEXT_NDP2_TIMER + 2*4, AR_NDP2_PERIOD + 2*4,
				AR_NDP2_TIMER_MODE, 0x0004पूर्ण,
	अणुAR_NEXT_NDP2_TIMER + 3*4, AR_NDP2_PERIOD + 3*4,
				AR_NDP2_TIMER_MODE, 0x0008पूर्ण,
	अणुAR_NEXT_NDP2_TIMER + 4*4, AR_NDP2_PERIOD + 4*4,
				AR_NDP2_TIMER_MODE, 0x0010पूर्ण,
	अणुAR_NEXT_NDP2_TIMER + 5*4, AR_NDP2_PERIOD + 5*4,
				AR_NDP2_TIMER_MODE, 0x0020पूर्ण,
	अणुAR_NEXT_NDP2_TIMER + 6*4, AR_NDP2_PERIOD + 6*4,
				AR_NDP2_TIMER_MODE, 0x0040पूर्ण,
	अणुAR_NEXT_NDP2_TIMER + 7*4, AR_NDP2_PERIOD + 7*4,
				AR_NDP2_TIMER_MODE, 0x0080पूर्ण
पूर्ण;

/* HW generic समयr primitives */

u32 ath9k_hw_gettsf32(काष्ठा ath_hw *ah)
अणु
	वापस REG_READ(ah, AR_TSF_L32);
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gettsf32);

व्योम ath9k_hw_gen_समयr_start_tsf2(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_gen_समयr_table *समयr_table = &ah->hw_gen_समयrs;

	अगर (समयr_table->tsf2_enabled) अणु
		REG_SET_BIT(ah, AR_सूचीECT_CONNECT, AR_DC_AP_STA_EN);
		REG_SET_BIT(ah, AR_RESET_TSF, AR_RESET_TSF2_ONCE);
	पूर्ण
पूर्ण

काष्ठा ath_gen_समयr *ath_gen_समयr_alloc(काष्ठा ath_hw *ah,
					  व्योम (*trigger)(व्योम *),
					  व्योम (*overflow)(व्योम *),
					  व्योम *arg,
					  u8 समयr_index)
अणु
	काष्ठा ath_gen_समयr_table *समयr_table = &ah->hw_gen_समयrs;
	काष्ठा ath_gen_समयr *समयr;

	अगर ((समयr_index < AR_FIRST_NDP_TIMER) ||
	    (समयr_index >= ATH_MAX_GEN_TIMER))
		वापस शून्य;

	अगर ((समयr_index > AR_FIRST_NDP_TIMER) &&
	    !AR_SREV_9300_20_OR_LATER(ah))
		वापस शून्य;

	समयr = kzalloc(माप(काष्ठा ath_gen_समयr), GFP_KERNEL);
	अगर (समयr == शून्य)
		वापस शून्य;

	/* allocate a hardware generic समयr slot */
	समयr_table->समयrs[समयr_index] = समयr;
	समयr->index = समयr_index;
	समयr->trigger = trigger;
	समयr->overflow = overflow;
	समयr->arg = arg;

	अगर ((समयr_index > AR_FIRST_NDP_TIMER) && !समयr_table->tsf2_enabled) अणु
		समयr_table->tsf2_enabled = true;
		ath9k_hw_gen_समयr_start_tsf2(ah);
	पूर्ण

	वापस समयr;
पूर्ण
EXPORT_SYMBOL(ath_gen_समयr_alloc);

व्योम ath9k_hw_gen_समयr_start(काष्ठा ath_hw *ah,
			      काष्ठा ath_gen_समयr *समयr,
			      u32 समयr_next,
			      u32 समयr_period)
अणु
	काष्ठा ath_gen_समयr_table *समयr_table = &ah->hw_gen_समयrs;
	u32 mask = 0;

	समयr_table->समयr_mask |= BIT(समयr->index);

	/*
	 * Program generic समयr रेजिस्टरs
	 */
	REG_WRITE(ah, gen_पंचांगr_configuration[समयr->index].next_addr,
		 समयr_next);
	REG_WRITE(ah, gen_पंचांगr_configuration[समयr->index].period_addr,
		  समयr_period);
	REG_SET_BIT(ah, gen_पंचांगr_configuration[समयr->index].mode_addr,
		    gen_पंचांगr_configuration[समयr->index].mode_mask);

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		/*
		 * Starting from AR9462, each generic समयr can select which tsf
		 * to use. But we still follow the old rule, 0 - 7 use tsf and
		 * 8 - 15  use tsf2.
		 */
		अगर ((समयr->index < AR_GEN_TIMER_BANK_1_LEN))
			REG_CLR_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				       (1 << समयr->index));
		अन्यथा
			REG_SET_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				       (1 << समयr->index));
	पूर्ण

	अगर (समयr->trigger)
		mask |= SM(AR_GENTMR_BIT(समयr->index),
			   AR_IMR_S5_GENTIMER_TRIG);
	अगर (समयr->overflow)
		mask |= SM(AR_GENTMR_BIT(समयr->index),
			   AR_IMR_S5_GENTIMER_THRESH);

	REG_SET_BIT(ah, AR_IMR_S5, mask);

	अगर ((ah->imask & ATH9K_INT_GENTIMER) == 0) अणु
		ah->imask |= ATH9K_INT_GENTIMER;
		ath9k_hw_set_पूर्णांकerrupts(ah);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gen_समयr_start);

व्योम ath9k_hw_gen_समयr_stop(काष्ठा ath_hw *ah, काष्ठा ath_gen_समयr *समयr)
अणु
	काष्ठा ath_gen_समयr_table *समयr_table = &ah->hw_gen_समयrs;

	/* Clear generic समयr enable bits. */
	REG_CLR_BIT(ah, gen_पंचांगr_configuration[समयr->index].mode_addr,
			gen_पंचांगr_configuration[समयr->index].mode_mask);

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		/*
		 * Need to चयन back to TSF अगर it was using TSF2.
		 */
		अगर ((समयr->index >= AR_GEN_TIMER_BANK_1_LEN)) अणु
			REG_CLR_BIT(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL,
				    (1 << समयr->index));
		पूर्ण
	पूर्ण

	/* Disable both trigger and thresh पूर्णांकerrupt masks */
	REG_CLR_BIT(ah, AR_IMR_S5,
		(SM(AR_GENTMR_BIT(समयr->index), AR_IMR_S5_GENTIMER_THRESH) |
		SM(AR_GENTMR_BIT(समयr->index), AR_IMR_S5_GENTIMER_TRIG)));

	समयr_table->समयr_mask &= ~BIT(समयr->index);

	अगर (समयr_table->समयr_mask == 0) अणु
		ah->imask &= ~ATH9K_INT_GENTIMER;
		ath9k_hw_set_पूर्णांकerrupts(ah);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath9k_hw_gen_समयr_stop);

व्योम ath_gen_समयr_मुक्त(काष्ठा ath_hw *ah, काष्ठा ath_gen_समयr *समयr)
अणु
	काष्ठा ath_gen_समयr_table *समयr_table = &ah->hw_gen_समयrs;

	/* मुक्त the hardware generic समयr slot */
	समयr_table->समयrs[समयr->index] = शून्य;
	kमुक्त(समयr);
पूर्ण
EXPORT_SYMBOL(ath_gen_समयr_मुक्त);

/*
 * Generic Timer Interrupts handling
 */
व्योम ath_gen_समयr_isr(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_gen_समयr_table *समयr_table = &ah->hw_gen_समयrs;
	काष्ठा ath_gen_समयr *समयr;
	अचिन्हित दीर्घ trigger_mask, thresh_mask;
	अचिन्हित पूर्णांक index;

	/* get hardware generic समयr पूर्णांकerrupt status */
	trigger_mask = ah->पूर्णांकr_gen_समयr_trigger;
	thresh_mask = ah->पूर्णांकr_gen_समयr_thresh;
	trigger_mask &= समयr_table->समयr_mask;
	thresh_mask &= समयr_table->समयr_mask;

	क्रम_each_set_bit(index, &thresh_mask, ARRAY_SIZE(समयr_table->समयrs)) अणु
		समयr = समयr_table->समयrs[index];
		अगर (!समयr)
		    जारी;
		अगर (!समयr->overflow)
		    जारी;

		trigger_mask &= ~BIT(index);
		समयr->overflow(समयr->arg);
	पूर्ण

	क्रम_each_set_bit(index, &trigger_mask, ARRAY_SIZE(समयr_table->समयrs)) अणु
		समयr = समयr_table->समयrs[index];
		अगर (!समयr)
		    जारी;
		अगर (!समयr->trigger)
		    जारी;
		समयr->trigger(समयr->arg);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ath_gen_समयr_isr);

/********/
/* HTC  */
/********/

अटल काष्ठा अणु
	u32 version;
	स्थिर अक्षर * name;
पूर्ण ath_mac_bb_names[] = अणु
	/* Devices with बाह्यal radios */
	अणु AR_SREV_VERSION_5416_PCI,	"5416" पूर्ण,
	अणु AR_SREV_VERSION_5416_PCIE,	"5418" पूर्ण,
	अणु AR_SREV_VERSION_9100,		"9100" पूर्ण,
	अणु AR_SREV_VERSION_9160,		"9160" पूर्ण,
	/* Single-chip solutions */
	अणु AR_SREV_VERSION_9280,		"9280" पूर्ण,
	अणु AR_SREV_VERSION_9285,		"9285" पूर्ण,
	अणु AR_SREV_VERSION_9287,         "9287" पूर्ण,
	अणु AR_SREV_VERSION_9271,         "9271" पूर्ण,
	अणु AR_SREV_VERSION_9300,         "9300" पूर्ण,
	अणु AR_SREV_VERSION_9330,         "9330" पूर्ण,
	अणु AR_SREV_VERSION_9340,		"9340" पूर्ण,
	अणु AR_SREV_VERSION_9485,         "9485" पूर्ण,
	अणु AR_SREV_VERSION_9462,         "9462" पूर्ण,
	अणु AR_SREV_VERSION_9550,         "9550" पूर्ण,
	अणु AR_SREV_VERSION_9565,         "9565" पूर्ण,
	अणु AR_SREV_VERSION_9531,         "9531" पूर्ण,
	अणु AR_SREV_VERSION_9561,         "9561" पूर्ण,
पूर्ण;

/* For devices with बाह्यal radios */
अटल काष्ठा अणु
	u16 version;
	स्थिर अक्षर * name;
पूर्ण ath_rf_names[] = अणु
	अणु 0,				"5133" पूर्ण,
	अणु AR_RAD5133_SREV_MAJOR,	"5133" पूर्ण,
	अणु AR_RAD5122_SREV_MAJOR,	"5122" पूर्ण,
	अणु AR_RAD2133_SREV_MAJOR,	"2133" पूर्ण,
	अणु AR_RAD2122_SREV_MAJOR,	"2122" पूर्ण
पूर्ण;

/*
 * Return the MAC/BB name. "????" is वापसed अगर the MAC/BB is unknown.
 */
अटल स्थिर अक्षर *ath9k_hw_mac_bb_name(u32 mac_bb_version)
अणु
	पूर्णांक i;

	क्रम (i=0; i<ARRAY_SIZE(ath_mac_bb_names); i++) अणु
		अगर (ath_mac_bb_names[i].version == mac_bb_version) अणु
			वापस ath_mac_bb_names[i].name;
		पूर्ण
	पूर्ण

	वापस "????";
पूर्ण

/*
 * Return the RF name. "????" is वापसed अगर the RF is unknown.
 * Used क्रम devices with बाह्यal radios.
 */
अटल स्थिर अक्षर *ath9k_hw_rf_name(u16 rf_version)
अणु
	पूर्णांक i;

	क्रम (i=0; i<ARRAY_SIZE(ath_rf_names); i++) अणु
		अगर (ath_rf_names[i].version == rf_version) अणु
			वापस ath_rf_names[i].name;
		पूर्ण
	पूर्ण

	वापस "????";
पूर्ण

व्योम ath9k_hw_name(काष्ठा ath_hw *ah, अक्षर *hw_name, माप_प्रकार len)
अणु
	पूर्णांक used;

	/* chipsets >= AR9280 are single-chip */
	अगर (AR_SREV_9280_20_OR_LATER(ah)) अणु
		used = scnम_लिखो(hw_name, len,
				 "Atheros AR%s Rev:%x",
				 ath9k_hw_mac_bb_name(ah->hw_version.macVersion),
				 ah->hw_version.macRev);
	पूर्ण
	अन्यथा अणु
		used = scnम_लिखो(hw_name, len,
				 "Atheros AR%s MAC/BB Rev:%x AR%s RF Rev:%x",
				 ath9k_hw_mac_bb_name(ah->hw_version.macVersion),
				 ah->hw_version.macRev,
				 ath9k_hw_rf_name((ah->hw_version.analog5GhzRev
						  & AR_RADIO_SREV_MAJOR)),
				 ah->hw_version.phyRev);
	पूर्ण

	hw_name[used] = '\0';
पूर्ण
EXPORT_SYMBOL(ath9k_hw_name);
