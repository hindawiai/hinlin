<शैली गुरु>
/*
 * Atheros CARL9170 driver
 *
 * LED handling
 *
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2009, 2010, Christian Lamparer <chunkeey@googlemail.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; see the file COPYING.  If not, see
 * http://www.gnu.org/licenses/.
 *
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *    Copyright (c) 2007-2008 Atheros Communications, Inc.
 *
 *    Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश "carl9170.h"
#समावेश "cmd.h"

पूर्णांक carl9170_led_set_state(काष्ठा ar9170 *ar, स्थिर u32 led_state)
अणु
	वापस carl9170_ग_लिखो_reg(ar, AR9170_GPIO_REG_PORT_DATA, led_state);
पूर्ण

पूर्णांक carl9170_led_init(काष्ठा ar9170 *ar)
अणु
	पूर्णांक err;

	/* disable LEDs */
	/* GPIO [0/1 mode: output, 2/3: input] */
	err = carl9170_ग_लिखो_reg(ar, AR9170_GPIO_REG_PORT_TYPE, 3);
	अगर (err)
		जाओ out;

	/* GPIO 0/1 value: off */
	err = carl9170_led_set_state(ar, 0);

out:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_CARL9170_LEDS
अटल व्योम carl9170_led_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9170 *ar = container_of(work, काष्ठा ar9170, led_work.work);
	पूर्णांक i, पंचांगp = 300, blink_delay = 1000;
	u32 led_val = 0;
	bool rerun = false;

	अगर (!IS_ACCEPTING_CMD(ar))
		वापस;

	mutex_lock(&ar->mutex);
	क्रम (i = 0; i < AR9170_NUM_LEDS; i++) अणु
		अगर (ar->leds[i].रेजिस्टरed) अणु
			अगर (ar->leds[i].last_state ||
			    ar->leds[i].toggled) अणु

				अगर (ar->leds[i].toggled)
					पंचांगp = 70 + 200 / (ar->leds[i].toggled);

				अगर (पंचांगp < blink_delay)
					blink_delay = पंचांगp;

				led_val |= 1 << i;
				ar->leds[i].toggled = 0;
				rerun = true;
			पूर्ण
		पूर्ण
	पूर्ण

	carl9170_led_set_state(ar, led_val);
	mutex_unlock(&ar->mutex);

	अगर (!rerun)
		वापस;

	ieee80211_queue_delayed_work(ar->hw,
				     &ar->led_work,
				     msecs_to_jअगरfies(blink_delay));
पूर्ण

अटल व्योम carl9170_led_set_brightness(काष्ठा led_classdev *led,
					क्रमागत led_brightness brightness)
अणु
	काष्ठा carl9170_led *arl = container_of(led, काष्ठा carl9170_led, l);
	काष्ठा ar9170 *ar = arl->ar;

	अगर (!arl->रेजिस्टरed)
		वापस;

	अगर (arl->last_state != !!brightness) अणु
		arl->toggled++;
		arl->last_state = !!brightness;
	पूर्ण

	अगर (likely(IS_ACCEPTING_CMD(ar) && arl->toggled))
		ieee80211_queue_delayed_work(ar->hw, &ar->led_work, HZ / 10);
पूर्ण

अटल पूर्णांक carl9170_led_रेजिस्टर_led(काष्ठा ar9170 *ar, पूर्णांक i, अक्षर *name,
				     स्थिर अक्षर *trigger)
अणु
	पूर्णांक err;

	snम_लिखो(ar->leds[i].name, माप(ar->leds[i].name),
		 "carl9170-%s::%s", wiphy_name(ar->hw->wiphy), name);

	ar->leds[i].ar = ar;
	ar->leds[i].l.name = ar->leds[i].name;
	ar->leds[i].l.brightness_set = carl9170_led_set_brightness;
	ar->leds[i].l.brightness = 0;
	ar->leds[i].l.शेष_trigger = trigger;

	err = led_classdev_रेजिस्टर(wiphy_dev(ar->hw->wiphy),
				    &ar->leds[i].l);
	अगर (err) अणु
		wiphy_err(ar->hw->wiphy, "failed to register %s LED (%d).\n",
			ar->leds[i].name, err);
	पूर्ण अन्यथा अणु
		ar->leds[i].रेजिस्टरed = true;
	पूर्ण

	वापस err;
पूर्ण

व्योम carl9170_led_unरेजिस्टर(काष्ठा ar9170 *ar)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AR9170_NUM_LEDS; i++)
		अगर (ar->leds[i].रेजिस्टरed) अणु
			led_classdev_unरेजिस्टर(&ar->leds[i].l);
			ar->leds[i].रेजिस्टरed = false;
			ar->leds[i].toggled = 0;
		पूर्ण

	cancel_delayed_work_sync(&ar->led_work);
पूर्ण

पूर्णांक carl9170_led_रेजिस्टर(काष्ठा ar9170 *ar)
अणु
	पूर्णांक err;

	INIT_DELAYED_WORK(&ar->led_work, carl9170_led_update);

	err = carl9170_led_रेजिस्टर_led(ar, 0, "tx",
					ieee80211_get_tx_led_name(ar->hw));
	अगर (err)
		जाओ fail;

	अगर (ar->features & CARL9170_ONE_LED)
		वापस 0;

	err = carl9170_led_रेजिस्टर_led(ar, 1, "assoc",
					ieee80211_get_assoc_led_name(ar->hw));
	अगर (err)
		जाओ fail;

	वापस 0;

fail:
	carl9170_led_unरेजिस्टर(ar);
	वापस err;
पूर्ण

#पूर्ण_अगर /* CONFIG_CARL9170_LEDS */
