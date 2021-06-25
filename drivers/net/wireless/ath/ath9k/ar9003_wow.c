<शैली गुरु>
/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
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
#समावेश "ath9k.h"
#समावेश "reg.h"
#समावेश "reg_wow.h"
#समावेश "hw-ops.h"

अटल व्योम ath9k_hw_set_sta_घातersave(काष्ठा ath_hw *ah)
अणु
	अगर (!ath9k_hw_mci_is_enabled(ah))
		जाओ set;
	/*
	 * If MCI is being used, set PWR_SAV only when MCI's
	 * PS state is disabled.
	 */
	अगर (ar9003_mci_state(ah, MCI_STATE_GET_WLAN_PS_STATE) != MCI_PS_DISABLE)
		वापस;
set:
	REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);
पूर्ण

अटल व्योम ath9k_hw_set_घातermode_wow_sleep(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ath9k_hw_set_sta_घातersave(ah);

	/* set rx disable bit */
	REG_WRITE(ah, AR_CR, AR_CR_RXD);

	अगर (!ath9k_hw_रुको(ah, AR_CR, AR_CR_RXE, 0, AH_WAIT_TIMEOUT)) अणु
		ath_err(common, "Failed to stop Rx DMA in 10ms AR_CR=0x%08x AR_DIAG_SW=0x%08x\n",
			REG_READ(ah, AR_CR), REG_READ(ah, AR_DIAG_SW));
		वापस;
	पूर्ण

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah)) अणु
		अगर (!REG_READ(ah, AR_MAC_PCU_GEN_TIMER_TSF_SEL))
			REG_CLR_BIT(ah, AR_सूचीECT_CONNECT, AR_DC_TSF2_ENABLE);
	पूर्ण अन्यथा अगर (AR_SREV_9485(ah))अणु
		अगर (!(REG_READ(ah, AR_NDP2_TIMER_MODE) &
		      AR_GEN_TIMERS2_MODE_ENABLE_MASK))
			REG_CLR_BIT(ah, AR_सूचीECT_CONNECT, AR_DC_TSF2_ENABLE);
	पूर्ण

	अगर (ath9k_hw_mci_is_enabled(ah))
		REG_WRITE(ah, AR_RTC_KEEP_AWAKE, 0x2);

	REG_WRITE(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_ON_INT);
पूर्ण

अटल व्योम ath9k_wow_create_keep_alive_pattern(काष्ठा ath_hw *ah)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u8 sta_mac_addr[ETH_ALEN], ap_mac_addr[ETH_ALEN];
	u32 ctl[13] = अणु0पूर्ण;
	u32 data_word[KAL_NUM_DATA_WORDS];
	u8 i;
	u32 wow_ka_data_word0;

	स_नकल(sta_mac_addr, common->macaddr, ETH_ALEN);
	स_नकल(ap_mac_addr, common->curbssid, ETH_ALEN);

	/* set the transmit buffer */
	ctl[0] = (KAL_FRAME_LEN | (MAX_RATE_POWER << 16));
	ctl[1] = 0;
	ctl[4] = 0;
	ctl[7] = (ah->txchainmask) << 2;
	ctl[2] = 0xf << 16; /* tx_tries 0 */

	अगर (IS_CHAN_2GHZ(ah->curchan))
		ctl[3] = 0x1b;	/* CCK_1M */
	अन्यथा
		ctl[3] = 0xb;	/* OFDM_6M */

	क्रम (i = 0; i < KAL_NUM_DESC_WORDS; i++)
		REG_WRITE(ah, (AR_WOW_KA_DESC_WORD2 + i * 4), ctl[i]);

	data_word[0] = (KAL_FRAME_TYPE << 2) | (KAL_FRAME_SUB_TYPE << 4) |
		       (KAL_TO_DS << 8) | (KAL_DURATION_ID << 16);
	data_word[1] = (ap_mac_addr[3] << 24) | (ap_mac_addr[2] << 16) |
		       (ap_mac_addr[1] << 8) | (ap_mac_addr[0]);
	data_word[2] = (sta_mac_addr[1] << 24) | (sta_mac_addr[0] << 16) |
		       (ap_mac_addr[5] << 8) | (ap_mac_addr[4]);
	data_word[3] = (sta_mac_addr[5] << 24) | (sta_mac_addr[4] << 16) |
		       (sta_mac_addr[3] << 8) | (sta_mac_addr[2]);
	data_word[4] = (ap_mac_addr[3] << 24) | (ap_mac_addr[2] << 16) |
		       (ap_mac_addr[1] << 8) | (ap_mac_addr[0]);
	data_word[5] = (ap_mac_addr[5] << 8) | (ap_mac_addr[4]);

	अगर (AR_SREV_9462_20_OR_LATER(ah) || AR_SREV_9565(ah)) अणु
		/*
		 * AR9462 2.0 and AR9565 have an extra descriptor word
		 * (समय based discard) compared to other chips.
		 */
		REG_WRITE(ah, (AR_WOW_KA_DESC_WORD2 + (12 * 4)), 0);
		wow_ka_data_word0 = AR_WOW_TXBUF(13);
	पूर्ण अन्यथा अणु
		wow_ka_data_word0 = AR_WOW_TXBUF(12);
	पूर्ण

	क्रम (i = 0; i < KAL_NUM_DATA_WORDS; i++)
		REG_WRITE(ah, (wow_ka_data_word0 + i*4), data_word[i]);
पूर्ण

पूर्णांक ath9k_hw_wow_apply_pattern(काष्ठा ath_hw *ah, u8 *user_pattern,
			       u8 *user_mask, पूर्णांक pattern_count,
			       पूर्णांक pattern_len)
अणु
	पूर्णांक i;
	u32 pattern_val, mask_val;
	u32 set, clr;

	अगर (pattern_count >= ah->wow.max_patterns)
		वापस -ENOSPC;

	अगर (pattern_count < MAX_NUM_PATTERN_LEGACY)
		REG_SET_BIT(ah, AR_WOW_PATTERN, BIT(pattern_count));
	अन्यथा
		REG_SET_BIT(ah, AR_MAC_PCU_WOW4, BIT(pattern_count - 8));

	क्रम (i = 0; i < MAX_PATTERN_SIZE; i += 4) अणु
		स_नकल(&pattern_val, user_pattern, 4);
		REG_WRITE(ah, (AR_WOW_TB_PATTERN(pattern_count) + i),
			  pattern_val);
		user_pattern += 4;
	पूर्ण

	क्रम (i = 0; i < MAX_PATTERN_MASK_SIZE; i += 4) अणु
		स_नकल(&mask_val, user_mask, 4);
		REG_WRITE(ah, (AR_WOW_TB_MASK(pattern_count) + i), mask_val);
		user_mask += 4;
	पूर्ण

	अगर (pattern_count < MAX_NUM_PATTERN_LEGACY)
		ah->wow.wow_event_mask |=
			BIT(pattern_count + AR_WOW_PAT_FOUND_SHIFT);
	अन्यथा
		ah->wow.wow_event_mask2 |=
			BIT((pattern_count - 8) + AR_WOW_PAT_FOUND_SHIFT);

	अगर (pattern_count < 4) अणु
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN1_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH1_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH1, set, clr);
	पूर्ण अन्यथा अगर (pattern_count < 8) अणु
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN2_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH2_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH2, set, clr);
	पूर्ण अन्यथा अगर (pattern_count < 12) अणु
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN3_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH3_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH3, set, clr);
	पूर्ण अन्यथा अगर (pattern_count < MAX_NUM_PATTERN) अणु
		set = (pattern_len & AR_WOW_LENGTH_MAX) <<
		       AR_WOW_LEN4_SHIFT(pattern_count);
		clr = AR_WOW_LENGTH4_MASK(pattern_count);
		REG_RMW(ah, AR_WOW_LENGTH4, set, clr);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_wow_apply_pattern);

u32 ath9k_hw_wow_wakeup(काष्ठा ath_hw *ah)
अणु
	u32 wow_status = 0;
	u32 val = 0, rval;

	/*
	 * Read the WoW status रेजिस्टर to know
	 * the wakeup reason.
	 */
	rval = REG_READ(ah, AR_WOW_PATTERN);
	val = AR_WOW_STATUS(rval);

	/*
	 * Mask only the WoW events that we have enabled. Someबार
	 * we have spurious WoW events from the AR_WOW_PATTERN
	 * रेजिस्टर. This mask will clean it up.
	 */
	val &= ah->wow.wow_event_mask;

	अगर (val) अणु
		अगर (val & AR_WOW_MAGIC_PAT_FOUND)
			wow_status |= AH_WOW_MAGIC_PATTERN_EN;
		अगर (AR_WOW_PATTERN_FOUND(val))
			wow_status |= AH_WOW_USER_PATTERN_EN;
		अगर (val & AR_WOW_KEEP_ALIVE_FAIL)
			wow_status |= AH_WOW_LINK_CHANGE;
		अगर (val & AR_WOW_BEACON_FAIL)
			wow_status |= AH_WOW_BEACON_MISS;
	पूर्ण

	rval = REG_READ(ah, AR_MAC_PCU_WOW4);
	val = AR_WOW_STATUS2(rval);
	val &= ah->wow.wow_event_mask2;

	अगर (val) अणु
		अगर (AR_WOW2_PATTERN_FOUND(val))
			wow_status |= AH_WOW_USER_PATTERN_EN;
	पूर्ण

	/*
	 * set and clear WOW_PME_CLEAR रेजिस्टरs क्रम the chip to
	 * generate next wow संकेत.
	 * disable D3 beक्रमe accessing other रेजिस्टरs ?
	 */

	/* करो we need to check the bit value 0x01000000 (7-10) ?? */
	REG_RMW(ah, AR_PCIE_PM_CTRL, AR_PMCTRL_WOW_PME_CLR,
		AR_PMCTRL_PWR_STATE_D1D3);

	/*
	 * Clear all events.
	 */
	REG_WRITE(ah, AR_WOW_PATTERN,
		  AR_WOW_CLEAR_EVENTS(REG_READ(ah, AR_WOW_PATTERN)));
	REG_WRITE(ah, AR_MAC_PCU_WOW4,
		  AR_WOW_CLEAR_EVENTS2(REG_READ(ah, AR_MAC_PCU_WOW4)));

	/*
	 * restore the beacon threshold to init value
	 */
	REG_WRITE(ah, AR_RSSI_THR, INIT_RSSI_THR);

	/*
	 * Restore the way the PCI-E reset, Power-On-Reset, बाह्यal
	 * PCIE_POR_SHORT pins are tied to its original value.
	 * Previously just beक्रमe WoW sleep, we untie the PCI-E
	 * reset to our Chip's Power On Reset so that any PCI-E
	 * reset from the bus will not reset our chip
	 */
	अगर (ah->is_pciexpress)
		ath9k_hw_configpciघातersave(ah, false);

	अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah) || AR_SREV_9485(ah)) अणु
		u32 dc = REG_READ(ah, AR_सूचीECT_CONNECT);

		अगर (!(dc & AR_DC_TSF2_ENABLE))
			ath9k_hw_gen_समयr_start_tsf2(ah);
	पूर्ण

	ah->wow.wow_event_mask = 0;
	ah->wow.wow_event_mask2 = 0;

	वापस wow_status;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_wow_wakeup);

अटल व्योम ath9k_hw_wow_set_arwr_reg(काष्ठा ath_hw *ah)
अणु
	u32 wa_reg;

	अगर (!ah->is_pciexpress)
		वापस;

	/*
	 * We need to untie the पूर्णांकernal POR (घातer-on-reset)
	 * to the बाह्यal PCI-E reset. We also need to tie
	 * the PCI-E Phy reset to the PCI-E reset.
	 */
	wa_reg = REG_READ(ah, AR_WA);
	wa_reg &= ~AR_WA_UNTIE_RESET_EN;
	wa_reg |= AR_WA_RESET_EN;
	wa_reg |= AR_WA_POR_SHORT;

	REG_WRITE(ah, AR_WA, wa_reg);
पूर्ण

व्योम ath9k_hw_wow_enable(काष्ठा ath_hw *ah, u32 pattern_enable)
अणु
	u32 wow_event_mask;
	u32 keep_alive, magic_pattern, host_pm_ctrl;

	wow_event_mask = ah->wow.wow_event_mask;

	/*
	 * AR_PMCTRL_HOST_PME_EN - Override PME enable in configuration
	 *                         space and allow MAC to generate WoW anyway.
	 *
	 * AR_PMCTRL_PWR_PM_CTRL_ENA - ???
	 *
	 * AR_PMCTRL_AUX_PWR_DET - PCI core SYS_AUX_PWR_DET संकेत,
	 *                         needs to be set क्रम WoW in PCI mode.
	 *
	 * AR_PMCTRL_WOW_PME_CLR - WoW Clear Signal going to the MAC.
	 *
	 * Set the घातer states appropriately and enable PME.
	 *
	 * Set and clear WOW_PME_CLEAR क्रम the chip
	 * to generate next wow संकेत.
	 */
	REG_SET_BIT(ah, AR_PCIE_PM_CTRL, AR_PMCTRL_HOST_PME_EN |
		    			 AR_PMCTRL_PWR_PM_CTRL_ENA |
		    			 AR_PMCTRL_AUX_PWR_DET |
		    			 AR_PMCTRL_WOW_PME_CLR);
	REG_CLR_BIT(ah, AR_PCIE_PM_CTRL, AR_PMCTRL_WOW_PME_CLR);

	/*
	 * Ranकरोm Backoff.
	 *
	 * 31:28 in AR_WOW_PATTERN : Indicates the number of bits used in the
	 *                           contention winकरोw. For value N,
	 *                           the अक्रमom backoff will be selected between
	 *                           0 and (2 ^ N) - 1.
	 */
	REG_SET_BIT(ah, AR_WOW_PATTERN,
		    AR_WOW_BACK_OFF_SHIFT(AR_WOW_PAT_BACKOFF));

	/*
	 * AIFS समय, Slot समय, Keep Alive count.
	 */
	REG_SET_BIT(ah, AR_WOW_COUNT, AR_WOW_AIFS_CNT(AR_WOW_CNT_AIFS_CNT) |
		    		      AR_WOW_SLOT_CNT(AR_WOW_CNT_SLOT_CNT) |
		    		      AR_WOW_KEEP_ALIVE_CNT(AR_WOW_CNT_KA_CNT));
	/*
	 * Beacon समयout.
	 */
	अगर (pattern_enable & AH_WOW_BEACON_MISS)
		REG_WRITE(ah, AR_WOW_BCN_TIMO, AR_WOW_BEACON_TIMO);
	अन्यथा
		REG_WRITE(ah, AR_WOW_BCN_TIMO, AR_WOW_BEACON_TIMO_MAX);

	/*
	 * Keep alive समयout in ms.
	 */
	अगर (!pattern_enable)
		REG_WRITE(ah, AR_WOW_KEEP_ALIVE_TIMO, AR_WOW_KEEP_ALIVE_NEVER);
	अन्यथा
		REG_WRITE(ah, AR_WOW_KEEP_ALIVE_TIMO, KAL_TIMEOUT * 32);

	/*
	 * Keep alive delay in us.
	 */
	REG_WRITE(ah, AR_WOW_KEEP_ALIVE_DELAY, KAL_DELAY * 1000);

	/*
	 * Create keep alive pattern to respond to beacons.
	 */
	ath9k_wow_create_keep_alive_pattern(ah);

	/*
	 * Configure keep alive रेजिस्टर.
	 */
	keep_alive = REG_READ(ah, AR_WOW_KEEP_ALIVE);

	/* Send keep alive समयouts anyway */
	keep_alive &= ~AR_WOW_KEEP_ALIVE_AUTO_DIS;

	अगर (pattern_enable & AH_WOW_LINK_CHANGE) अणु
		keep_alive &= ~AR_WOW_KEEP_ALIVE_FAIL_DIS;
		wow_event_mask |= AR_WOW_KEEP_ALIVE_FAIL;
	पूर्ण अन्यथा अणु
		keep_alive |= AR_WOW_KEEP_ALIVE_FAIL_DIS;
	पूर्ण

	REG_WRITE(ah, AR_WOW_KEEP_ALIVE, keep_alive);

	/*
	 * We are relying on a bmiss failure, ensure we have
	 * enough threshold to prevent false positives.
	 */
	REG_RMW_FIELD(ah, AR_RSSI_THR, AR_RSSI_THR_BM_THR,
		      AR_WOW_BMISSTHRESHOLD);

	अगर (pattern_enable & AH_WOW_BEACON_MISS) अणु
		wow_event_mask |= AR_WOW_BEACON_FAIL;
		REG_SET_BIT(ah, AR_WOW_BCN_EN, AR_WOW_BEACON_FAIL_EN);
	पूर्ण अन्यथा अणु
		REG_CLR_BIT(ah, AR_WOW_BCN_EN, AR_WOW_BEACON_FAIL_EN);
	पूर्ण

	/*
	 * Enable the magic packet रेजिस्टरs.
	 */
	magic_pattern = REG_READ(ah, AR_WOW_PATTERN);
	magic_pattern |= AR_WOW_MAC_INTR_EN;

	अगर (pattern_enable & AH_WOW_MAGIC_PATTERN_EN) अणु
		magic_pattern |= AR_WOW_MAGIC_EN;
		wow_event_mask |= AR_WOW_MAGIC_PAT_FOUND;
	पूर्ण अन्यथा अणु
		magic_pattern &= ~AR_WOW_MAGIC_EN;
	पूर्ण

	REG_WRITE(ah, AR_WOW_PATTERN, magic_pattern);

	/*
	 * Enable pattern matching क्रम packets which are less
	 * than 256 bytes.
	 */
	REG_WRITE(ah, AR_WOW_PATTERN_MATCH_LT_256B,
		  AR_WOW_PATTERN_SUPPORTED);

	/*
	 * Set the घातer states appropriately and enable PME.
	 */
	host_pm_ctrl = REG_READ(ah, AR_PCIE_PM_CTRL);
	host_pm_ctrl |= AR_PMCTRL_PWR_STATE_D1D3 |
			AR_PMCTRL_HOST_PME_EN |
			AR_PMCTRL_PWR_PM_CTRL_ENA;
	host_pm_ctrl &= ~AR_PCIE_PM_CTRL_ENA;

	अगर (AR_SREV_9462(ah)) अणु
		/*
		 * This is needed to prevent the chip waking up
		 * the host within 3-4 seconds with certain
		 * platक्रमm/BIOS.
		 */
		host_pm_ctrl &= ~AR_PMCTRL_PWR_STATE_D1D3;
		host_pm_ctrl |= AR_PMCTRL_PWR_STATE_D1D3_REAL;
	पूर्ण

	REG_WRITE(ah, AR_PCIE_PM_CTRL, host_pm_ctrl);

	/*
	 * Enable sequence number generation when asleep.
	 */
	REG_CLR_BIT(ah, AR_STA_ID1, AR_STA_ID1_PRESERVE_SEQNUM);

	/* To bring करोwn WOW घातer low margin */
	REG_SET_BIT(ah, AR_PCIE_PHY_REG3, BIT(13));

	ath9k_hw_wow_set_arwr_reg(ah);

	अगर (ath9k_hw_mci_is_enabled(ah))
		REG_WRITE(ah, AR_RTC_KEEP_AWAKE, 0x2);

	/* HW WoW */
	REG_CLR_BIT(ah, AR_PCU_MISC_MODE3, BIT(5));

	ath9k_hw_set_घातermode_wow_sleep(ah);
	ah->wow.wow_event_mask = wow_event_mask;
पूर्ण
EXPORT_SYMBOL(ath9k_hw_wow_enable);
