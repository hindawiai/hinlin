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

#समावेश "ath9k.h"

/********************************/
/*	 LED functions		*/
/********************************/

#अगर_घोषित CONFIG_MAC80211_LEDS

अटल व्योम ath_fill_led_pin(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	/* Set शेष led pin अगर invalid */
	अगर (ah->led_pin < 0) अणु
		अगर (AR_SREV_9287(ah))
			ah->led_pin = ATH_LED_PIN_9287;
		अन्यथा अगर (AR_SREV_9485(ah))
			ah->led_pin = ATH_LED_PIN_9485;
		अन्यथा अगर (AR_SREV_9300(ah))
			ah->led_pin = ATH_LED_PIN_9300;
		अन्यथा अगर (AR_SREV_9462(ah) || AR_SREV_9565(ah))
			ah->led_pin = ATH_LED_PIN_9462;
		अन्यथा
			ah->led_pin = ATH_LED_PIN_DEF;
	पूर्ण

	/* Configure gpio क्रम output */
	ath9k_hw_gpio_request_out(ah, ah->led_pin, "ath9k-led",
				  AR_GPIO_OUTPUT_MUX_AS_OUTPUT);

	/* LED off, active low */
	ath9k_hw_set_gpio(ah, ah->led_pin, ah->config.led_active_high ? 0 : 1);
पूर्ण

अटल व्योम ath_led_brightness(काष्ठा led_classdev *led_cdev,
			       क्रमागत led_brightness brightness)
अणु
	काष्ठा ath_softc *sc = container_of(led_cdev, काष्ठा ath_softc, led_cdev);
	u32 val = (brightness == LED_OFF);

	अगर (sc->sc_ah->config.led_active_high)
		val = !val;

	ath9k_hw_set_gpio(sc->sc_ah, sc->sc_ah->led_pin, val);
पूर्ण

व्योम ath_deinit_leds(काष्ठा ath_softc *sc)
अणु
	अगर (!sc->led_रेजिस्टरed)
		वापस;

	ath_led_brightness(&sc->led_cdev, LED_OFF);
	led_classdev_unरेजिस्टर(&sc->led_cdev);

	ath9k_hw_gpio_मुक्त(sc->sc_ah, sc->sc_ah->led_pin);
पूर्ण

व्योम ath_init_leds(काष्ठा ath_softc *sc)
अणु
	पूर्णांक ret;

	अगर (AR_SREV_9100(sc->sc_ah))
		वापस;

	ath_fill_led_pin(sc);

	अगर (!ath9k_led_blink)
		sc->led_cdev.शेष_trigger =
			ieee80211_get_radio_led_name(sc->hw);

	snम_लिखो(sc->led_name, माप(sc->led_name),
		"ath9k-%s", wiphy_name(sc->hw->wiphy));
	sc->led_cdev.name = sc->led_name;
	sc->led_cdev.brightness_set = ath_led_brightness;

	ret = led_classdev_रेजिस्टर(wiphy_dev(sc->hw->wiphy), &sc->led_cdev);
	अगर (ret < 0)
		वापस;

	sc->led_रेजिस्टरed = true;
पूर्ण
#पूर्ण_अगर

/*******************/
/*	Rfसमाप्त	   */
/*******************/

अटल bool ath_is_rfसमाप्त_set(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	bool is_blocked;

	ath9k_ps_wakeup(sc);
	is_blocked = ath9k_hw_gpio_get(ah, ah->rfसमाप्त_gpio) ==
				  ah->rfसमाप्त_polarity;
	ath9k_ps_restore(sc);

	वापस is_blocked;
पूर्ण

व्योम ath9k_rfसमाप्त_poll_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	bool blocked = !!ath_is_rfसमाप्त_set(sc);

	wiphy_rfसमाप्त_set_hw_state(hw->wiphy, blocked);
पूर्ण

व्योम ath_start_rfसमाप्त_poll(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_RFSILENT)
		wiphy_rfसमाप्त_start_polling(sc->hw->wiphy);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT

/******************/
/*     BTCOEX     */
/******************/

/*
 * Detects अगर there is any priority bt traffic
 */
अटल व्योम ath_detect_bt_priority(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (ath9k_hw_gpio_get(sc->sc_ah, ah->btcoex_hw.btpriority_gpio))
		btcoex->bt_priority_cnt++;

	अगर (समय_after(jअगरfies, btcoex->bt_priority_समय +
			msecs_to_jअगरfies(ATH_BT_PRIORITY_TIME_THRESHOLD))) अणु
		clear_bit(BT_OP_PRIORITY_DETECTED, &btcoex->op_flags);
		clear_bit(BT_OP_SCAN, &btcoex->op_flags);
		/* Detect अगर colocated bt started scanning */
		अगर (btcoex->bt_priority_cnt >= ATH_BT_CNT_SCAN_THRESHOLD) अणु
			ath_dbg(ath9k_hw_common(sc->sc_ah), BTCOEX,
				"BT scan detected\n");
			set_bit(BT_OP_PRIORITY_DETECTED, &btcoex->op_flags);
			set_bit(BT_OP_SCAN, &btcoex->op_flags);
		पूर्ण अन्यथा अगर (btcoex->bt_priority_cnt >= ATH_BT_CNT_THRESHOLD) अणु
			ath_dbg(ath9k_hw_common(sc->sc_ah), BTCOEX,
				"BT priority traffic detected\n");
			set_bit(BT_OP_PRIORITY_DETECTED, &btcoex->op_flags);
		पूर्ण

		btcoex->bt_priority_cnt = 0;
		btcoex->bt_priority_समय = jअगरfies;
	पूर्ण
पूर्ण

अटल व्योम ath_mci_ftp_adjust(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &btcoex->mci;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (btcoex->bt_रुको_समय > ATH_BTCOEX_RX_WAIT_TIME) अणु
		अगर (ar9003_mci_state(ah, MCI_STATE_NEED_FTP_STOMP) &&
		    (mci->num_pan || mci->num_other_acl))
			ah->btcoex_hw.mci.stomp_ftp =
				(sc->rx.num_pkts < ATH_BTCOEX_STOMP_FTP_THRESH);
		अन्यथा
			ah->btcoex_hw.mci.stomp_ftp = false;
		btcoex->bt_रुको_समय = 0;
		sc->rx.num_pkts = 0;
	पूर्ण
पूर्ण

/*
 * This is the master bt coex समयr which runs क्रम every
 * 45ms, bt traffic will be given priority during 55% of this
 * period जबतक wlan माला_लो reमुख्यing 45%
 */
अटल व्योम ath_btcoex_period_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath_softc *sc = from_समयr(sc, t, btcoex.period_समयr);
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	क्रमागत ath_stomp_type stomp_type;
	u32 समयr_period;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	अगर (sc->sc_ah->घातer_mode == ATH9K_PM_NETWORK_SLEEP) अणु
		btcoex->bt_रुको_समय += btcoex->btcoex_period;
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
		जाओ skip_hw_wakeup;
	पूर्ण
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	ath9k_ps_wakeup(sc);
	spin_lock_bh(&btcoex->btcoex_lock);

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_MCI) अणु
		ath9k_mci_update_rssi(sc);
		ath_mci_ftp_adjust(sc);
	पूर्ण

	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI))
		ath_detect_bt_priority(sc);

	stomp_type = btcoex->bt_stomp_type;
	समयr_period = btcoex->btcoex_no_stomp;

	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI)) अणु
		अगर (test_bit(BT_OP_SCAN, &btcoex->op_flags)) अणु
			stomp_type = ATH_BTCOEX_STOMP_ALL;
			समयr_period = btcoex->btscan_no_stomp;
		पूर्ण
	पूर्ण अन्यथा अगर (btcoex->stomp_audio >= 5) अणु
		stomp_type = ATH_BTCOEX_STOMP_AUDIO;
		btcoex->stomp_audio = 0;
	पूर्ण

	ath9k_hw_btcoex_bt_stomp(ah, stomp_type);
	ath9k_hw_btcoex_enable(ah);

	spin_unlock_bh(&btcoex->btcoex_lock);

	अगर (btcoex->btcoex_period != btcoex->btcoex_no_stomp)
		mod_समयr(&btcoex->no_stomp_समयr,
			 jअगरfies + msecs_to_jअगरfies(समयr_period));

	ath9k_ps_restore(sc);

skip_hw_wakeup:
	mod_समयr(&btcoex->period_समयr,
		  jअगरfies + msecs_to_jअगरfies(btcoex->btcoex_period));
पूर्ण

/*
 * Generic tsf based hw समयr which configures weight
 * रेजिस्टरs to समय slice between wlan and bt traffic
 */
अटल व्योम ath_btcoex_no_stomp_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath_softc *sc = from_समयr(sc, t, btcoex.no_stomp_समयr);
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;

	ath9k_ps_wakeup(sc);
	spin_lock_bh(&btcoex->btcoex_lock);

	अगर (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_LOW ||
	    (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI) &&
	     test_bit(BT_OP_SCAN, &btcoex->op_flags)))
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_NONE);
	अन्यथा अगर (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_ALL)
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_LOW);

	ath9k_hw_btcoex_enable(ah);
	spin_unlock_bh(&btcoex->btcoex_lock);
	ath9k_ps_restore(sc);
पूर्ण

अटल व्योम ath_init_btcoex_समयr(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;

	btcoex->btcoex_period = ATH_BTCOEX_DEF_BT_PERIOD;
	btcoex->btcoex_no_stomp = (100 - ATH_BTCOEX_DEF_DUTY_CYCLE) *
		btcoex->btcoex_period / 100;
	btcoex->btscan_no_stomp = (100 - ATH_BTCOEX_BTSCAN_DUTY_CYCLE) *
				   btcoex->btcoex_period / 100;
	btcoex->bt_stomp_type = ATH_BTCOEX_STOMP_LOW;

	समयr_setup(&btcoex->period_समयr, ath_btcoex_period_समयr, 0);
	समयr_setup(&btcoex->no_stomp_समयr, ath_btcoex_no_stomp_समयr, 0);

	spin_lock_init(&btcoex->btcoex_lock);
पूर्ण

/*
 * (Re)start btcoex समयrs
 */
व्योम ath9k_btcoex_समयr_resume(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_3WIRE &&
	    ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_MCI)
		वापस;

	ath_dbg(ath9k_hw_common(ah), BTCOEX, "Starting btcoex timers\n");

	/* make sure duty cycle समयr is also stopped when resuming */
	del_समयr_sync(&btcoex->no_stomp_समयr);

	btcoex->bt_priority_cnt = 0;
	btcoex->bt_priority_समय = jअगरfies;
	clear_bit(BT_OP_PRIORITY_DETECTED, &btcoex->op_flags);
	clear_bit(BT_OP_SCAN, &btcoex->op_flags);

	mod_समयr(&btcoex->period_समयr, jअगरfies);
पूर्ण

/*
 * Pause btcoex समयr and bt duty cycle समयr
 */
व्योम ath9k_btcoex_समयr_छोड़ो(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_3WIRE &&
	    ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_MCI)
		वापस;

	ath_dbg(ath9k_hw_common(ah), BTCOEX, "Stopping btcoex timers\n");

	del_समयr_sync(&btcoex->period_समयr);
	del_समयr_sync(&btcoex->no_stomp_समयr);
पूर्ण

व्योम ath9k_btcoex_stop_gen_समयr(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;

	del_समयr_sync(&btcoex->no_stomp_समयr);
पूर्ण

u16 ath9k_btcoex_aggr_limit(काष्ठा ath_softc *sc, u32 max_4ms_framelen)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &sc->btcoex.mci;
	u16 aggr_limit = 0;

	अगर ((sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_MCI) && mci->aggr_limit)
		aggr_limit = (max_4ms_framelen * mci->aggr_limit) >> 4;
	अन्यथा अगर (test_bit(BT_OP_PRIORITY_DETECTED, &btcoex->op_flags))
		aggr_limit = min((max_4ms_framelen * 3) / 8,
				 (u32)ATH_AMPDU_LIMIT_MAX);

	वापस aggr_limit;
पूर्ण

व्योम ath9k_btcoex_handle_पूर्णांकerrupt(काष्ठा ath_softc *sc, u32 status)
अणु
	अगर (status & ATH9K_INT_MCI)
		ath_mci_पूर्णांकr(sc);
पूर्ण

व्योम ath9k_start_btcoex(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (ah->btcoex_hw.enabled ||
	    ath9k_hw_get_btcoex_scheme(ah) == ATH_BTCOEX_CFG_NONE)
		वापस;

	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_MCI))
		ath9k_hw_btcoex_set_weight(ah, AR_BT_COEX_WGHT,
					   AR_STOMP_LOW_WLAN_WGHT, 0);
	अन्यथा
		ath9k_hw_btcoex_set_weight(ah, 0, 0,
					   ATH_BTCOEX_STOMP_NONE);
	ath9k_hw_btcoex_enable(ah);
	ath9k_btcoex_समयr_resume(sc);
पूर्ण

व्योम ath9k_stop_btcoex(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (!ah->btcoex_hw.enabled ||
	    ath9k_hw_get_btcoex_scheme(ah) == ATH_BTCOEX_CFG_NONE)
		वापस;

	ath9k_btcoex_समयr_छोड़ो(sc);
	ath9k_hw_btcoex_disable(ah);

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_MCI)
		ath_mci_flush_profile(&sc->btcoex.mci);
पूर्ण

व्योम ath9k_deinit_btcoex(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (ath9k_hw_mci_is_enabled(ah))
		ath_mci_cleanup(sc);
	अन्यथा अणु
		क्रमागत ath_btcoex_scheme scheme = ath9k_hw_get_btcoex_scheme(ah);

		अगर (scheme == ATH_BTCOEX_CFG_2WIRE ||
		    scheme == ATH_BTCOEX_CFG_3WIRE)
			ath9k_hw_btcoex_deinit(sc->sc_ah);
	पूर्ण
पूर्ण

पूर्णांक ath9k_init_btcoex(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_txq *txq;
	काष्ठा ath_hw *ah = sc->sc_ah;
	पूर्णांक r;

	ath9k_hw_btcoex_init_scheme(ah);

	चयन (ath9k_hw_get_btcoex_scheme(sc->sc_ah)) अणु
	हाल ATH_BTCOEX_CFG_NONE:
		अवरोध;
	हाल ATH_BTCOEX_CFG_2WIRE:
		ath9k_hw_btcoex_init_2wire(sc->sc_ah);
		अवरोध;
	हाल ATH_BTCOEX_CFG_3WIRE:
		ath9k_hw_btcoex_init_3wire(sc->sc_ah);
		ath_init_btcoex_समयr(sc);
		txq = sc->tx.txq_map[IEEE80211_AC_BE];
		ath9k_hw_init_btcoex_hw(sc->sc_ah, txq->axq_qnum);
		अवरोध;
	हाल ATH_BTCOEX_CFG_MCI:
		ath_init_btcoex_समयr(sc);

		sc->btcoex.duty_cycle = ATH_BTCOEX_DEF_DUTY_CYCLE;
		INIT_LIST_HEAD(&sc->btcoex.mci.info);
		ath9k_hw_btcoex_init_mci(ah);

		r = ath_mci_setup(sc);
		अगर (r)
			वापस r;

		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_dump_mci_btcoex(काष्ठा ath_softc *sc, u8 *buf, u32 size)
अणु
	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	काष्ठा ath_mci_profile *mci = &btcoex->mci;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;
	u32 len = 0;
	पूर्णांक i;

	ATH_DUMP_BTCOEX("Total BT profiles", NUM_PROF(mci));
	ATH_DUMP_BTCOEX("MGMT", mci->num_mgmt);
	ATH_DUMP_BTCOEX("SCO", mci->num_sco);
	ATH_DUMP_BTCOEX("A2DP", mci->num_a2dp);
	ATH_DUMP_BTCOEX("HID", mci->num_hid);
	ATH_DUMP_BTCOEX("PAN", mci->num_pan);
	ATH_DUMP_BTCOEX("ACL", mci->num_other_acl);
	ATH_DUMP_BTCOEX("BDR", mci->num_bdr);
	ATH_DUMP_BTCOEX("Aggr. Limit", mci->aggr_limit);
	ATH_DUMP_BTCOEX("Stomp Type", btcoex->bt_stomp_type);
	ATH_DUMP_BTCOEX("BTCoex Period (msec)", btcoex->btcoex_period);
	ATH_DUMP_BTCOEX("Duty Cycle", btcoex->duty_cycle);
	ATH_DUMP_BTCOEX("BT Wait time", btcoex->bt_रुको_समय);
	ATH_DUMP_BTCOEX("Concurrent Tx", btcoex_hw->mci.concur_tx);
	ATH_DUMP_BTCOEX("Concurrent RSSI cnt", btcoex->rssi_count);

	len += scnम_लिखो(buf + len, size - len, "BT Weights: ");
	क्रम (i = 0; i < AR9300_NUM_BT_WEIGHTS; i++)
		len += scnम_लिखो(buf + len, size - len, "%08x ",
				 btcoex_hw->bt_weight[i]);
	len += scnम_लिखो(buf + len, size - len, "\n");
	len += scnम_लिखो(buf + len, size - len, "WLAN Weights: ");
	क्रम (i = 0; i < AR9300_NUM_BT_WEIGHTS; i++)
		len += scnम_लिखो(buf + len, size - len, "%08x ",
				 btcoex_hw->wlan_weight[i]);
	len += scnम_लिखो(buf + len, size - len, "\n");
	len += scnम_लिखो(buf + len, size - len, "Tx Priorities: ");
	क्रम (i = 0; i < ATH_BTCOEX_STOMP_MAX; i++)
		len += scnम_लिखो(buf + len, size - len, "%08x ",
				btcoex_hw->tx_prio[i]);

	len += scnम_लिखो(buf + len, size - len, "\n");

	वापस len;
पूर्ण

अटल पूर्णांक ath9k_dump_legacy_btcoex(काष्ठा ath_softc *sc, u8 *buf, u32 size)
अणु

	काष्ठा ath_btcoex *btcoex = &sc->btcoex;
	u32 len = 0;

	ATH_DUMP_BTCOEX("Stomp Type", btcoex->bt_stomp_type);
	ATH_DUMP_BTCOEX("BTCoex Period (msec)", btcoex->btcoex_period);
	ATH_DUMP_BTCOEX("Duty Cycle", btcoex->duty_cycle);
	ATH_DUMP_BTCOEX("BT Wait time", btcoex->bt_रुको_समय);

	वापस len;
पूर्ण

पूर्णांक ath9k_dump_btcoex(काष्ठा ath_softc *sc, u8 *buf, u32 size)
अणु
	अगर (ath9k_hw_mci_is_enabled(sc->sc_ah))
		वापस ath9k_dump_mci_btcoex(sc, buf, size);
	अन्यथा
		वापस ath9k_dump_legacy_btcoex(sc, buf, size);
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */
