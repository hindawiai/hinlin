<शैली गुरु>
/*
 * Copyright (c) 2010-2011 Atheros Communications Inc.
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

#समावेश "htc.h"

/******************/
/*     BTCOEX     */
/******************/

#घोषणा ATH_HTC_BTCOEX_PRODUCT_ID "wb193"

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT

/*
 * Detects अगर there is any priority bt traffic
 */
अटल व्योम ath_detect_bt_priority(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_btcoex *btcoex = &priv->btcoex;
	काष्ठा ath_hw *ah = priv->ah;

	अगर (ath9k_hw_gpio_get(ah, ah->btcoex_hw.btpriority_gpio))
		btcoex->bt_priority_cnt++;

	अगर (समय_after(jअगरfies, btcoex->bt_priority_समय +
			msecs_to_jअगरfies(ATH_BT_PRIORITY_TIME_THRESHOLD))) अणु
		clear_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags);
		clear_bit(OP_BT_SCAN, &priv->op_flags);
		/* Detect अगर colocated bt started scanning */
		अगर (btcoex->bt_priority_cnt >= ATH_BT_CNT_SCAN_THRESHOLD) अणु
			ath_dbg(ath9k_hw_common(ah), BTCOEX,
				"BT scan detected\n");
			set_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags);
			set_bit(OP_BT_SCAN, &priv->op_flags);
		पूर्ण अन्यथा अगर (btcoex->bt_priority_cnt >= ATH_BT_CNT_THRESHOLD) अणु
			ath_dbg(ath9k_hw_common(ah), BTCOEX,
				"BT priority traffic detected\n");
			set_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags);
		पूर्ण

		btcoex->bt_priority_cnt = 0;
		btcoex->bt_priority_समय = jअगरfies;
	पूर्ण
पूर्ण

/*
 * This is the master bt coex work which runs क्रम every
 * 45ms, bt traffic will be given priority during 55% of this
 * period जबतक wlan माला_लो reमुख्यing 45%
 */
अटल व्योम ath_btcoex_period_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath9k_htc_priv *priv = container_of(work, काष्ठा ath9k_htc_priv,
						   coex_period_work.work);
	काष्ठा ath_btcoex *btcoex = &priv->btcoex;
	काष्ठा ath_common *common = ath9k_hw_common(priv->ah);
	u32 समयr_period;
	पूर्णांक ret;

	ath_detect_bt_priority(priv);

	ret = ath9k_htc_update_cap_target(priv,
			  test_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags));
	अगर (ret) अणु
		ath_err(common, "Unable to set BTCOEX parameters\n");
		वापस;
	पूर्ण

	ath9k_hw_btcoex_bt_stomp(priv->ah, test_bit(OP_BT_SCAN, &priv->op_flags) ?
				 ATH_BTCOEX_STOMP_ALL : btcoex->bt_stomp_type);

	ath9k_hw_btcoex_enable(priv->ah);
	समयr_period = test_bit(OP_BT_SCAN, &priv->op_flags) ?
		btcoex->btscan_no_stomp : btcoex->btcoex_no_stomp;
	ieee80211_queue_delayed_work(priv->hw, &priv->duty_cycle_work,
				     msecs_to_jअगरfies(समयr_period));
	ieee80211_queue_delayed_work(priv->hw, &priv->coex_period_work,
				     msecs_to_jअगरfies(btcoex->btcoex_period));
पूर्ण

/*
 * Work to समय slice between wlan and bt traffic and
 * configure weight रेजिस्टरs
 */
अटल व्योम ath_btcoex_duty_cycle_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath9k_htc_priv *priv = container_of(work, काष्ठा ath9k_htc_priv,
						   duty_cycle_work.work);
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_btcoex *btcoex = &priv->btcoex;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, BTCOEX, "time slice work for bt and wlan\n");

	अगर (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_LOW ||
	    test_bit(OP_BT_SCAN, &priv->op_flags))
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_NONE);
	अन्यथा अगर (btcoex->bt_stomp_type == ATH_BTCOEX_STOMP_ALL)
		ath9k_hw_btcoex_bt_stomp(ah, ATH_BTCOEX_STOMP_LOW);

	ath9k_hw_btcoex_enable(priv->ah);
पूर्ण

अटल व्योम ath_htc_init_btcoex_work(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_btcoex *btcoex = &priv->btcoex;

	btcoex->btcoex_period = ATH_BTCOEX_DEF_BT_PERIOD;
	btcoex->btcoex_no_stomp = (100 - ATH_BTCOEX_DEF_DUTY_CYCLE) *
		btcoex->btcoex_period / 100;
	btcoex->btscan_no_stomp = (100 - ATH_BTCOEX_BTSCAN_DUTY_CYCLE) *
				   btcoex->btcoex_period / 100;
	INIT_DELAYED_WORK(&priv->coex_period_work, ath_btcoex_period_work);
	INIT_DELAYED_WORK(&priv->duty_cycle_work, ath_btcoex_duty_cycle_work);
पूर्ण

/*
 * (Re)start btcoex work
 */

अटल व्योम ath_htc_resume_btcoex_work(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_btcoex *btcoex = &priv->btcoex;
	काष्ठा ath_hw *ah = priv->ah;

	ath_dbg(ath9k_hw_common(ah), BTCOEX, "Starting btcoex work\n");

	btcoex->bt_priority_cnt = 0;
	btcoex->bt_priority_समय = jअगरfies;
	clear_bit(OP_BT_PRIORITY_DETECTED, &priv->op_flags);
	clear_bit(OP_BT_SCAN, &priv->op_flags);
	ieee80211_queue_delayed_work(priv->hw, &priv->coex_period_work, 0);
पूर्ण


/*
 * Cancel btcoex and bt duty cycle work.
 */
अटल व्योम ath_htc_cancel_btcoex_work(काष्ठा ath9k_htc_priv *priv)
अणु
	cancel_delayed_work_sync(&priv->coex_period_work);
	cancel_delayed_work_sync(&priv->duty_cycle_work);
पूर्ण

व्योम ath9k_htc_start_btcoex(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_hw *ah = priv->ah;

	अगर (ath9k_hw_get_btcoex_scheme(ah) == ATH_BTCOEX_CFG_3WIRE) अणु
		ath9k_hw_btcoex_set_weight(ah, AR_BT_COEX_WGHT,
					   AR_STOMP_LOW_WLAN_WGHT, 0);
		ath9k_hw_btcoex_enable(ah);
		ath_htc_resume_btcoex_work(priv);
	पूर्ण
पूर्ण

व्योम ath9k_htc_stop_btcoex(काष्ठा ath9k_htc_priv *priv)
अणु
	काष्ठा ath_hw *ah = priv->ah;

	अगर (ah->btcoex_hw.enabled &&
	    ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_NONE) अणु
		अगर (ah->btcoex_hw.scheme == ATH_BTCOEX_CFG_3WIRE)
			ath_htc_cancel_btcoex_work(priv);
		ath9k_hw_btcoex_disable(ah);
	पूर्ण
पूर्ण

व्योम ath9k_htc_init_btcoex(काष्ठा ath9k_htc_priv *priv, अक्षर *product)
अणु
	काष्ठा ath_hw *ah = priv->ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक qnum;

	/*
	 * Check अगर BTCOEX is globally disabled.
	 */
	अगर (!common->btcoex_enabled) अणु
		ah->btcoex_hw.scheme = ATH_BTCOEX_CFG_NONE;
		वापस;
	पूर्ण

	अगर (product && म_भेदन(product, ATH_HTC_BTCOEX_PRODUCT_ID, 5) == 0) अणु
		ah->btcoex_hw.scheme = ATH_BTCOEX_CFG_3WIRE;
	पूर्ण

	चयन (ath9k_hw_get_btcoex_scheme(priv->ah)) अणु
	हाल ATH_BTCOEX_CFG_NONE:
		अवरोध;
	हाल ATH_BTCOEX_CFG_3WIRE:
		priv->ah->btcoex_hw.btactive_gpio = 7;
		priv->ah->btcoex_hw.btpriority_gpio = 6;
		priv->ah->btcoex_hw.wlanactive_gpio = 8;
		priv->btcoex.bt_stomp_type = ATH_BTCOEX_STOMP_LOW;
		ath9k_hw_btcoex_init_3wire(priv->ah);
		ath_htc_init_btcoex_work(priv);
		qnum = priv->hwq_map[IEEE80211_AC_BE];
		ath9k_hw_init_btcoex_hw(priv->ah, qnum);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_BTCOEX_SUPPORT */

/*******/
/* LED */
/*******/

#अगर_घोषित CONFIG_MAC80211_LEDS
व्योम ath9k_led_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath9k_htc_priv *priv = container_of(work,
						   काष्ठा ath9k_htc_priv,
						   led_work);

	ath9k_hw_set_gpio(priv->ah, priv->ah->led_pin,
			  (priv->brightness == LED_OFF));
पूर्ण

अटल व्योम ath9k_led_brightness(काष्ठा led_classdev *led_cdev,
				 क्रमागत led_brightness brightness)
अणु
	काष्ठा ath9k_htc_priv *priv = container_of(led_cdev,
						   काष्ठा ath9k_htc_priv,
						   led_cdev);

	/* Not locked, but it's just a tiny green light..*/
	priv->brightness = brightness;
	ieee80211_queue_work(priv->hw, &priv->led_work);
पूर्ण

व्योम ath9k_deinit_leds(काष्ठा ath9k_htc_priv *priv)
अणु
	अगर (!priv->led_रेजिस्टरed)
		वापस;

	ath9k_led_brightness(&priv->led_cdev, LED_OFF);
	led_classdev_unरेजिस्टर(&priv->led_cdev);
	cancel_work_sync(&priv->led_work);

	ath9k_hw_gpio_मुक्त(priv->ah, priv->ah->led_pin);
पूर्ण


व्योम ath9k_configure_leds(काष्ठा ath9k_htc_priv *priv)
अणु
	/* Configure gpio 1 क्रम output */
	ath9k_hw_gpio_request_out(priv->ah, priv->ah->led_pin,
				  "ath9k-led",
				  AR_GPIO_OUTPUT_MUX_AS_OUTPUT);
	/* LED off, active low */
	ath9k_hw_set_gpio(priv->ah, priv->ah->led_pin, 1);
पूर्ण

व्योम ath9k_init_leds(काष्ठा ath9k_htc_priv *priv)
अणु
	पूर्णांक ret;

	अगर (AR_SREV_9287(priv->ah))
		priv->ah->led_pin = ATH_LED_PIN_9287;
	अन्यथा अगर (AR_SREV_9271(priv->ah))
		priv->ah->led_pin = ATH_LED_PIN_9271;
	अन्यथा अगर (AR_DEVID_7010(priv->ah))
		priv->ah->led_pin = ATH_LED_PIN_7010;
	अन्यथा
		priv->ah->led_pin = ATH_LED_PIN_DEF;

	अगर (!ath9k_htc_led_blink)
		priv->led_cdev.शेष_trigger =
			ieee80211_get_radio_led_name(priv->hw);

	ath9k_configure_leds(priv);

	snम_लिखो(priv->led_name, माप(priv->led_name),
		"ath9k_htc-%s", wiphy_name(priv->hw->wiphy));
	priv->led_cdev.name = priv->led_name;
	priv->led_cdev.brightness_set = ath9k_led_brightness;

	ret = led_classdev_रेजिस्टर(wiphy_dev(priv->hw->wiphy), &priv->led_cdev);
	अगर (ret < 0)
		वापस;

	INIT_WORK(&priv->led_work, ath9k_led_work);
	priv->led_रेजिस्टरed = true;

	वापस;
पूर्ण
#पूर्ण_अगर

/*******************/
/*	Rfसमाप्त	   */
/*******************/

अटल bool ath_is_rfसमाप्त_set(काष्ठा ath9k_htc_priv *priv)
अणु
	bool is_blocked;

	ath9k_htc_ps_wakeup(priv);
	is_blocked = ath9k_hw_gpio_get(priv->ah, priv->ah->rfसमाप्त_gpio) ==
						 priv->ah->rfसमाप्त_polarity;
	ath9k_htc_ps_restore(priv);

	वापस is_blocked;
पूर्ण

व्योम ath9k_htc_rfसमाप्त_poll_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath9k_htc_priv *priv = hw->priv;
	bool blocked = !!ath_is_rfसमाप्त_set(priv);

	wiphy_rfसमाप्त_set_hw_state(hw->wiphy, blocked);
पूर्ण

व्योम ath9k_start_rfसमाप्त_poll(काष्ठा ath9k_htc_priv *priv)
अणु
	अगर (priv->ah->caps.hw_caps & ATH9K_HW_CAP_RFSILENT)
		wiphy_rfसमाप्त_start_polling(priv->hw->wiphy);
पूर्ण
