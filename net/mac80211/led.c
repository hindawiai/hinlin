<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2006, Johannes Berg <johannes@sipsolutions.net>
 */

/* just क्रम IFNAMSIZ */
#समावेश <linux/अगर.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश "led.h"

व्योम ieee80211_led_assoc(काष्ठा ieee80211_local *local, bool associated)
अणु
	अगर (!atomic_पढ़ो(&local->assoc_led_active))
		वापस;
	अगर (associated)
		led_trigger_event(&local->assoc_led, LED_FULL);
	अन्यथा
		led_trigger_event(&local->assoc_led, LED_OFF);
पूर्ण

व्योम ieee80211_led_radio(काष्ठा ieee80211_local *local, bool enabled)
अणु
	अगर (!atomic_पढ़ो(&local->radio_led_active))
		वापस;
	अगर (enabled)
		led_trigger_event(&local->radio_led, LED_FULL);
	अन्यथा
		led_trigger_event(&local->radio_led, LED_OFF);
पूर्ण

व्योम ieee80211_alloc_led_names(काष्ठा ieee80211_local *local)
अणु
	local->rx_led.name = kaप्र_लिखो(GFP_KERNEL, "%srx",
				       wiphy_name(local->hw.wiphy));
	local->tx_led.name = kaप्र_लिखो(GFP_KERNEL, "%stx",
				       wiphy_name(local->hw.wiphy));
	local->assoc_led.name = kaप्र_लिखो(GFP_KERNEL, "%sassoc",
					  wiphy_name(local->hw.wiphy));
	local->radio_led.name = kaप्र_लिखो(GFP_KERNEL, "%sradio",
					  wiphy_name(local->hw.wiphy));
पूर्ण

व्योम ieee80211_मुक्त_led_names(काष्ठा ieee80211_local *local)
अणु
	kमुक्त(local->rx_led.name);
	kमुक्त(local->tx_led.name);
	kमुक्त(local->assoc_led.name);
	kमुक्त(local->radio_led.name);
पूर्ण

अटल पूर्णांक ieee80211_tx_led_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     tx_led);

	atomic_inc(&local->tx_led_active);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_tx_led_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     tx_led);

	atomic_dec(&local->tx_led_active);
पूर्ण

अटल पूर्णांक ieee80211_rx_led_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     rx_led);

	atomic_inc(&local->rx_led_active);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_rx_led_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     rx_led);

	atomic_dec(&local->rx_led_active);
पूर्ण

अटल पूर्णांक ieee80211_assoc_led_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     assoc_led);

	atomic_inc(&local->assoc_led_active);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_assoc_led_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     assoc_led);

	atomic_dec(&local->assoc_led_active);
पूर्ण

अटल पूर्णांक ieee80211_radio_led_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     radio_led);

	atomic_inc(&local->radio_led_active);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_radio_led_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     radio_led);

	atomic_dec(&local->radio_led_active);
पूर्ण

अटल पूर्णांक ieee80211_tpt_led_activate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     tpt_led);

	atomic_inc(&local->tpt_led_active);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_tpt_led_deactivate(काष्ठा led_classdev *led_cdev)
अणु
	काष्ठा ieee80211_local *local = container_of(led_cdev->trigger,
						     काष्ठा ieee80211_local,
						     tpt_led);

	atomic_dec(&local->tpt_led_active);
पूर्ण

व्योम ieee80211_led_init(काष्ठा ieee80211_local *local)
अणु
	atomic_set(&local->rx_led_active, 0);
	local->rx_led.activate = ieee80211_rx_led_activate;
	local->rx_led.deactivate = ieee80211_rx_led_deactivate;
	अगर (local->rx_led.name && led_trigger_रेजिस्टर(&local->rx_led)) अणु
		kमुक्त(local->rx_led.name);
		local->rx_led.name = शून्य;
	पूर्ण

	atomic_set(&local->tx_led_active, 0);
	local->tx_led.activate = ieee80211_tx_led_activate;
	local->tx_led.deactivate = ieee80211_tx_led_deactivate;
	अगर (local->tx_led.name && led_trigger_रेजिस्टर(&local->tx_led)) अणु
		kमुक्त(local->tx_led.name);
		local->tx_led.name = शून्य;
	पूर्ण

	atomic_set(&local->assoc_led_active, 0);
	local->assoc_led.activate = ieee80211_assoc_led_activate;
	local->assoc_led.deactivate = ieee80211_assoc_led_deactivate;
	अगर (local->assoc_led.name && led_trigger_रेजिस्टर(&local->assoc_led)) अणु
		kमुक्त(local->assoc_led.name);
		local->assoc_led.name = शून्य;
	पूर्ण

	atomic_set(&local->radio_led_active, 0);
	local->radio_led.activate = ieee80211_radio_led_activate;
	local->radio_led.deactivate = ieee80211_radio_led_deactivate;
	अगर (local->radio_led.name && led_trigger_रेजिस्टर(&local->radio_led)) अणु
		kमुक्त(local->radio_led.name);
		local->radio_led.name = शून्य;
	पूर्ण

	atomic_set(&local->tpt_led_active, 0);
	अगर (local->tpt_led_trigger) अणु
		local->tpt_led.activate = ieee80211_tpt_led_activate;
		local->tpt_led.deactivate = ieee80211_tpt_led_deactivate;
		अगर (led_trigger_रेजिस्टर(&local->tpt_led)) अणु
			kमुक्त(local->tpt_led_trigger);
			local->tpt_led_trigger = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ieee80211_led_निकास(काष्ठा ieee80211_local *local)
अणु
	अगर (local->radio_led.name)
		led_trigger_unरेजिस्टर(&local->radio_led);
	अगर (local->assoc_led.name)
		led_trigger_unरेजिस्टर(&local->assoc_led);
	अगर (local->tx_led.name)
		led_trigger_unरेजिस्टर(&local->tx_led);
	अगर (local->rx_led.name)
		led_trigger_unरेजिस्टर(&local->rx_led);

	अगर (local->tpt_led_trigger) अणु
		led_trigger_unरेजिस्टर(&local->tpt_led);
		kमुक्त(local->tpt_led_trigger);
	पूर्ण
पूर्ण

स्थिर अक्षर *__ieee80211_get_radio_led_name(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	वापस local->radio_led.name;
पूर्ण
EXPORT_SYMBOL(__ieee80211_get_radio_led_name);

स्थिर अक्षर *__ieee80211_get_assoc_led_name(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	वापस local->assoc_led.name;
पूर्ण
EXPORT_SYMBOL(__ieee80211_get_assoc_led_name);

स्थिर अक्षर *__ieee80211_get_tx_led_name(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	वापस local->tx_led.name;
पूर्ण
EXPORT_SYMBOL(__ieee80211_get_tx_led_name);

स्थिर अक्षर *__ieee80211_get_rx_led_name(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	वापस local->rx_led.name;
पूर्ण
EXPORT_SYMBOL(__ieee80211_get_rx_led_name);

अटल अचिन्हित दीर्घ tpt_trig_traffic(काष्ठा ieee80211_local *local,
				      काष्ठा tpt_led_trigger *tpt_trig)
अणु
	अचिन्हित दीर्घ traffic, delta;

	traffic = tpt_trig->tx_bytes + tpt_trig->rx_bytes;

	delta = traffic - tpt_trig->prev_traffic;
	tpt_trig->prev_traffic = traffic;
	वापस DIV_ROUND_UP(delta, 1024 / 8);
पूर्ण

अटल व्योम tpt_trig_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा tpt_led_trigger *tpt_trig = from_समयr(tpt_trig, t, समयr);
	काष्ठा ieee80211_local *local = tpt_trig->local;
	काष्ठा led_classdev *led_cdev;
	अचिन्हित दीर्घ on, off, tpt;
	पूर्णांक i;

	अगर (!tpt_trig->running)
		वापस;

	mod_समयr(&tpt_trig->समयr, round_jअगरfies(jअगरfies + HZ));

	tpt = tpt_trig_traffic(local, tpt_trig);

	/* शेष to just solid on */
	on = 1;
	off = 0;

	क्रम (i = tpt_trig->blink_table_len - 1; i >= 0; i--) अणु
		अगर (tpt_trig->blink_table[i].throughput < 0 ||
		    tpt > tpt_trig->blink_table[i].throughput) अणु
			off = tpt_trig->blink_table[i].blink_समय / 2;
			on = tpt_trig->blink_table[i].blink_समय - off;
			अवरोध;
		पूर्ण
	पूर्ण

	पढ़ो_lock(&local->tpt_led.leddev_list_lock);
	list_क्रम_each_entry(led_cdev, &local->tpt_led.led_cdevs, trig_list)
		led_blink_set(led_cdev, &on, &off);
	पढ़ो_unlock(&local->tpt_led.leddev_list_lock);
पूर्ण

स्थिर अक्षर *
__ieee80211_create_tpt_led_trigger(काष्ठा ieee80211_hw *hw,
				   अचिन्हित पूर्णांक flags,
				   स्थिर काष्ठा ieee80211_tpt_blink *blink_table,
				   अचिन्हित पूर्णांक blink_table_len)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा tpt_led_trigger *tpt_trig;

	अगर (WARN_ON(local->tpt_led_trigger))
		वापस शून्य;

	tpt_trig = kzalloc(माप(काष्ठा tpt_led_trigger), GFP_KERNEL);
	अगर (!tpt_trig)
		वापस शून्य;

	snम_लिखो(tpt_trig->name, माप(tpt_trig->name),
		 "%stpt", wiphy_name(local->hw.wiphy));

	local->tpt_led.name = tpt_trig->name;

	tpt_trig->blink_table = blink_table;
	tpt_trig->blink_table_len = blink_table_len;
	tpt_trig->want = flags;
	tpt_trig->local = local;

	समयr_setup(&tpt_trig->समयr, tpt_trig_समयr, 0);

	local->tpt_led_trigger = tpt_trig;

	वापस tpt_trig->name;
पूर्ण
EXPORT_SYMBOL(__ieee80211_create_tpt_led_trigger);

अटल व्योम ieee80211_start_tpt_led_trig(काष्ठा ieee80211_local *local)
अणु
	काष्ठा tpt_led_trigger *tpt_trig = local->tpt_led_trigger;

	अगर (tpt_trig->running)
		वापस;

	/* reset traffic */
	tpt_trig_traffic(local, tpt_trig);
	tpt_trig->running = true;

	tpt_trig_समयr(&tpt_trig->समयr);
	mod_समयr(&tpt_trig->समयr, round_jअगरfies(jअगरfies + HZ));
पूर्ण

अटल व्योम ieee80211_stop_tpt_led_trig(काष्ठा ieee80211_local *local)
अणु
	काष्ठा tpt_led_trigger *tpt_trig = local->tpt_led_trigger;
	काष्ठा led_classdev *led_cdev;

	अगर (!tpt_trig->running)
		वापस;

	tpt_trig->running = false;
	del_समयr_sync(&tpt_trig->समयr);

	पढ़ो_lock(&local->tpt_led.leddev_list_lock);
	list_क्रम_each_entry(led_cdev, &local->tpt_led.led_cdevs, trig_list)
		led_set_brightness(led_cdev, LED_OFF);
	पढ़ो_unlock(&local->tpt_led.leddev_list_lock);
पूर्ण

व्योम ieee80211_mod_tpt_led_trig(काष्ठा ieee80211_local *local,
				अचिन्हित पूर्णांक types_on, अचिन्हित पूर्णांक types_off)
अणु
	काष्ठा tpt_led_trigger *tpt_trig = local->tpt_led_trigger;
	bool allowed;

	WARN_ON(types_on & types_off);

	अगर (!tpt_trig)
		वापस;

	tpt_trig->active &= ~types_off;
	tpt_trig->active |= types_on;

	/*
	 * Regardless of wanted state, we shouldn't blink when
	 * the radio is disabled -- this can happen due to some
	 * code ordering issues with __ieee80211_recalc_idle()
	 * being called beक्रमe the radio is started.
	 */
	allowed = tpt_trig->active & IEEE80211_TPT_LEDTRIG_FL_RADIO;

	अगर (!allowed || !(tpt_trig->active & tpt_trig->want))
		ieee80211_stop_tpt_led_trig(local);
	अन्यथा
		ieee80211_start_tpt_led_trig(local);
पूर्ण
