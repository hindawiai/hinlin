<शैली गुरु>
/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
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

#समावेश "ath9k.h"

अटल स्थिर काष्ठा wiphy_wowlan_support ath9k_wowlan_support_legacy = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT,
	.n_patterns = MAX_NUM_USER_PATTERN,
	.pattern_min_len = 1,
	.pattern_max_len = MAX_PATTERN_SIZE,
पूर्ण;

अटल स्थिर काष्ठा wiphy_wowlan_support ath9k_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_MAGIC_PKT | WIPHY_WOWLAN_DISCONNECT,
	.n_patterns = MAX_NUM_PATTERN - 2,
	.pattern_min_len = 1,
	.pattern_max_len = MAX_PATTERN_SIZE,
पूर्ण;

अटल u8 ath9k_wow_map_triggers(काष्ठा ath_softc *sc,
				 काष्ठा cfg80211_wowlan *wowlan)
अणु
	u8 wow_triggers = 0;

	अगर (wowlan->disconnect)
		wow_triggers |= AH_WOW_LINK_CHANGE |
				AH_WOW_BEACON_MISS;
	अगर (wowlan->magic_pkt)
		wow_triggers |= AH_WOW_MAGIC_PATTERN_EN;

	अगर (wowlan->n_patterns)
		wow_triggers |= AH_WOW_USER_PATTERN_EN;

	वापस wow_triggers;
पूर्ण

अटल पूर्णांक ath9k_wow_add_disassoc_deauth_pattern(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक pattern_count = 0;
	पूर्णांक ret, i, byte_cnt = 0;
	u8 dis_deauth_pattern[MAX_PATTERN_SIZE];
	u8 dis_deauth_mask[MAX_PATTERN_SIZE];

	स_रखो(dis_deauth_pattern, 0, MAX_PATTERN_SIZE);
	स_रखो(dis_deauth_mask, 0, MAX_PATTERN_SIZE);

	/*
	 * Create Dissassociate / Deauthenticate packet filter
	 *
	 *     2 bytes        2 byte    6 bytes   6 bytes  6 bytes
	 *  +--------------+----------+---------+--------+--------+----
	 *  + Frame Control+ Duration +   DA    +  SA    +  BSSID +
	 *  +--------------+----------+---------+--------+--------+----
	 *
	 * The above is the management frame क्रमmat क्रम disassociate/
	 * deauthenticate pattern, from this we need to match the first byte
	 * of 'Frame Control' and DA, SA, and BSSID fields
	 * (skipping 2nd byte of FC and Duration feild.
	 *
	 * Disassociate pattern
	 * --------------------
	 * Frame control = 00 00 1010
	 * DA, SA, BSSID = x:x:x:x:x:x
	 * Pattern will be A0000000 | x:x:x:x:x:x | x:x:x:x:x:x
	 *			    | x:x:x:x:x:x  -- 22 bytes
	 *
	 * Deauthenticate pattern
	 * ----------------------
	 * Frame control = 00 00 1100
	 * DA, SA, BSSID = x:x:x:x:x:x
	 * Pattern will be C0000000 | x:x:x:x:x:x | x:x:x:x:x:x
	 *			    | x:x:x:x:x:x  -- 22 bytes
	 */

	/* Fill out the mask with all FF's */
	क्रम (i = 0; i < MAX_PATTERN_MASK_SIZE; i++)
		dis_deauth_mask[i] = 0xff;

	/* copy the first byte of frame control field */
	dis_deauth_pattern[byte_cnt] = 0xa0;
	byte_cnt++;

	/* skip 2nd byte of frame control and Duration field */
	byte_cnt += 3;

	/*
	 * need not match the destination mac address, it can be a broadcast
	 * mac address or an unicast to this station
	 */
	byte_cnt += 6;

	/* copy the source mac address */
	स_नकल((dis_deauth_pattern + byte_cnt), common->curbssid, ETH_ALEN);

	byte_cnt += 6;

	/* copy the bssid, its same as the source mac address */
	स_नकल((dis_deauth_pattern + byte_cnt), common->curbssid, ETH_ALEN);

	/* Create Disassociate pattern mask */
	dis_deauth_mask[0] = 0xfe;
	dis_deauth_mask[1] = 0x03;
	dis_deauth_mask[2] = 0xc0;

	ret = ath9k_hw_wow_apply_pattern(ah, dis_deauth_pattern, dis_deauth_mask,
					 pattern_count, byte_cnt);
	अगर (ret)
		जाओ निकास;

	pattern_count++;
	/*
	 * क्रम de-authenticate pattern, only the first byte of the frame
	 * control field माला_लो changed from 0xA0 to 0xC0
	 */
	dis_deauth_pattern[0] = 0xC0;

	ret = ath9k_hw_wow_apply_pattern(ah, dis_deauth_pattern, dis_deauth_mask,
					 pattern_count, byte_cnt);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_wow_add_pattern(काष्ठा ath_softc *sc,
				 काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा cfg80211_pkt_pattern *patterns = wowlan->patterns;
	u8 wow_pattern[MAX_PATTERN_SIZE];
	u8 wow_mask[MAX_PATTERN_SIZE];
	पूर्णांक mask_len, ret = 0;
	s8 i = 0;

	क्रम (i = 0; i < wowlan->n_patterns; i++) अणु
		mask_len = DIV_ROUND_UP(patterns[i].pattern_len, 8);
		स_रखो(wow_pattern, 0, MAX_PATTERN_SIZE);
		स_रखो(wow_mask, 0, MAX_PATTERN_SIZE);
		स_नकल(wow_pattern, patterns[i].pattern, patterns[i].pattern_len);
		स_नकल(wow_mask, patterns[i].mask, mask_len);

		ret = ath9k_hw_wow_apply_pattern(ah,
						 wow_pattern,
						 wow_mask,
						 i + 2,
						 patterns[i].pattern_len);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ath9k_suspend(काष्ठा ieee80211_hw *hw,
		  काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u8 triggers;
	पूर्णांक ret = 0;

	ath9k_deinit_channel_context(sc);

	mutex_lock(&sc->mutex);

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags)) अणु
		ath_err(common, "Device not present\n");
		ret = -ENODEV;
		जाओ fail_wow;
	पूर्ण

	अगर (WARN_ON(!wowlan)) अणु
		ath_err(common, "None of the WoW triggers enabled\n");
		ret = -EINVAL;
		जाओ fail_wow;
	पूर्ण

	अगर (sc->cur_chan->nvअगरs > 1) अणु
		ath_dbg(common, WOW, "WoW for multivif is not yet supported\n");
		ret = 1;
		जाओ fail_wow;
	पूर्ण

	अगर (ath9k_is_chanctx_enabled()) अणु
		अगर (test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags)) अणु
			ath_dbg(common, WOW,
				"Multi-channel WOW is not supported\n");
			ret = 1;
			जाओ fail_wow;
		पूर्ण
	पूर्ण

	अगर (!test_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags)) अणु
		ath_dbg(common, WOW, "None of the STA vifs are associated\n");
		ret = 1;
		जाओ fail_wow;
	पूर्ण

	triggers = ath9k_wow_map_triggers(sc, wowlan);
	अगर (!triggers) अणु
		ath_dbg(common, WOW, "No valid WoW triggers\n");
		ret = 1;
		जाओ fail_wow;
	पूर्ण

	ath_cancel_work(sc);
	ath_stop_ani(sc);

	ath9k_ps_wakeup(sc);

	ath9k_stop_btcoex(sc);

	/*
	 * Enable wake up on recieving disassoc/deauth
	 * frame by शेष.
	 */
	ret = ath9k_wow_add_disassoc_deauth_pattern(sc);
	अगर (ret) अणु
		ath_err(common,
			"Unable to add disassoc/deauth pattern: %d\n", ret);
		जाओ fail_wow;
	पूर्ण

	अगर (triggers & AH_WOW_USER_PATTERN_EN) अणु
		ret = ath9k_wow_add_pattern(sc, wowlan);
		अगर (ret) अणु
			ath_err(common,
				"Unable to add user pattern: %d\n", ret);
			जाओ fail_wow;
		पूर्ण
	पूर्ण

	spin_lock_bh(&sc->sc_pcu_lock);
	/*
	 * To aव्योम false wake, we enable beacon miss पूर्णांकerrupt only
	 * when we go to sleep. We save the current पूर्णांकerrupt mask
	 * so we can restore it after the प्रणाली wakes up
	 */
	sc->wow_पूर्णांकr_beक्रमe_sleep = ah->imask;
	ah->imask &= ~ATH9K_INT_GLOBAL;
	ath9k_hw_disable_पूर्णांकerrupts(ah);
	ah->imask = ATH9K_INT_BMISS | ATH9K_INT_GLOBAL;
	ath9k_hw_set_पूर्णांकerrupts(ah);
	ath9k_hw_enable_पूर्णांकerrupts(ah);

	spin_unlock_bh(&sc->sc_pcu_lock);

	/*
	 * we can now sync irq and समाप्त any running tasklets, since we alपढ़ोy
	 * disabled पूर्णांकerrupts and not holding a spin lock
	 */
	synchronize_irq(sc->irq);
	tasklet_समाप्त(&sc->पूर्णांकr_tq);

	ath9k_hw_wow_enable(ah, triggers);

	ath9k_ps_restore(sc);
	ath_dbg(common, WOW, "Suspend with WoW triggers: 0x%x\n", triggers);

	set_bit(ATH_OP_WOW_ENABLED, &common->op_flags);
fail_wow:
	mutex_unlock(&sc->mutex);
	वापस ret;
पूर्ण

पूर्णांक ath9k_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	u8 status;

	mutex_lock(&sc->mutex);

	ath9k_ps_wakeup(sc);

	spin_lock_bh(&sc->sc_pcu_lock);

	ath9k_hw_disable_पूर्णांकerrupts(ah);
	ah->imask = sc->wow_पूर्णांकr_beक्रमe_sleep;
	ath9k_hw_set_पूर्णांकerrupts(ah);
	ath9k_hw_enable_पूर्णांकerrupts(ah);

	spin_unlock_bh(&sc->sc_pcu_lock);

	status = ath9k_hw_wow_wakeup(ah);
	ath_dbg(common, WOW, "Resume with WoW status: 0x%x\n", status);

	ath_restart_work(sc);
	ath9k_start_btcoex(sc);

	clear_bit(ATH_OP_WOW_ENABLED, &common->op_flags);

	ath9k_ps_restore(sc);
	mutex_unlock(&sc->mutex);

	वापस 0;
पूर्ण

व्योम ath9k_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	mutex_lock(&sc->mutex);
	device_set_wakeup_enable(sc->dev, enabled);
	mutex_unlock(&sc->mutex);

	ath_dbg(common, WOW, "WoW wakeup source is %s\n",
		(enabled) ? "enabled" : "disabled");
पूर्ण

व्योम ath9k_init_wow(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर ((sc->driver_data & ATH9K_PCI_WOW) || sc->क्रमce_wow) अणु
		अगर (AR_SREV_9462_20_OR_LATER(ah) || AR_SREV_9565_11_OR_LATER(ah))
			hw->wiphy->wowlan = &ath9k_wowlan_support;
		अन्यथा
			hw->wiphy->wowlan = &ath9k_wowlan_support_legacy;

		device_init_wakeup(sc->dev, 1);
	पूर्ण
पूर्ण

व्योम ath9k_deinit_wow(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;

	अगर ((sc->driver_data & ATH9K_PCI_WOW) || sc->क्रमce_wow)
		device_init_wakeup(sc->dev, 0);
पूर्ण
