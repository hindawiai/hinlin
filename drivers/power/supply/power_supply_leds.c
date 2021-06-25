<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  LEDs triggers क्रम घातer supply class
 *
 *  Copyright तऊ 2007  Anton Vorontsov <cbou@mail.ru>
 *  Copyright तऊ 2004  Szabolcs Gyurko
 *  Copyright तऊ 2003  Ian Molton <spyro@f2s.com>
 *
 *  Modअगरied: 2004, Oct     Szabolcs Gyurko
 */

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

#समावेश "power_supply.h"

/* Battery specअगरic LEDs triggers. */

अटल व्योम घातer_supply_update_bat_leds(काष्ठा घातer_supply *psy)
अणु
	जोड़ घातer_supply_propval status;
	अचिन्हित दीर्घ delay_on = 0;
	अचिन्हित दीर्घ delay_off = 0;

	अगर (घातer_supply_get_property(psy, POWER_SUPPLY_PROP_STATUS, &status))
		वापस;

	dev_dbg(&psy->dev, "%s %d\n", __func__, status.पूर्णांकval);

	चयन (status.पूर्णांकval) अणु
	हाल POWER_SUPPLY_STATUS_FULL:
		led_trigger_event(psy->अक्षरging_full_trig, LED_FULL);
		led_trigger_event(psy->अक्षरging_trig, LED_OFF);
		led_trigger_event(psy->full_trig, LED_FULL);
		led_trigger_event(psy->अक्षरging_blink_full_solid_trig,
			LED_FULL);
		अवरोध;
	हाल POWER_SUPPLY_STATUS_CHARGING:
		led_trigger_event(psy->अक्षरging_full_trig, LED_FULL);
		led_trigger_event(psy->अक्षरging_trig, LED_FULL);
		led_trigger_event(psy->full_trig, LED_OFF);
		led_trigger_blink(psy->अक्षरging_blink_full_solid_trig,
			&delay_on, &delay_off);
		अवरोध;
	शेष:
		led_trigger_event(psy->अक्षरging_full_trig, LED_OFF);
		led_trigger_event(psy->अक्षरging_trig, LED_OFF);
		led_trigger_event(psy->full_trig, LED_OFF);
		led_trigger_event(psy->अक्षरging_blink_full_solid_trig,
			LED_OFF);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक घातer_supply_create_bat_triggers(काष्ठा घातer_supply *psy)
अणु
	psy->अक्षरging_full_trig_name = kaप्र_लिखो(GFP_KERNEL,
					"%s-charging-or-full", psy->desc->name);
	अगर (!psy->अक्षरging_full_trig_name)
		जाओ अक्षरging_full_failed;

	psy->अक्षरging_trig_name = kaप्र_लिखो(GFP_KERNEL,
					"%s-charging", psy->desc->name);
	अगर (!psy->अक्षरging_trig_name)
		जाओ अक्षरging_failed;

	psy->full_trig_name = kaप्र_लिखो(GFP_KERNEL, "%s-full", psy->desc->name);
	अगर (!psy->full_trig_name)
		जाओ full_failed;

	psy->अक्षरging_blink_full_solid_trig_name = kaप्र_लिखो(GFP_KERNEL,
		"%s-charging-blink-full-solid", psy->desc->name);
	अगर (!psy->अक्षरging_blink_full_solid_trig_name)
		जाओ अक्षरging_blink_full_solid_failed;

	led_trigger_रेजिस्टर_simple(psy->अक्षरging_full_trig_name,
				    &psy->अक्षरging_full_trig);
	led_trigger_रेजिस्टर_simple(psy->अक्षरging_trig_name,
				    &psy->अक्षरging_trig);
	led_trigger_रेजिस्टर_simple(psy->full_trig_name,
				    &psy->full_trig);
	led_trigger_रेजिस्टर_simple(psy->अक्षरging_blink_full_solid_trig_name,
				    &psy->अक्षरging_blink_full_solid_trig);

	वापस 0;

अक्षरging_blink_full_solid_failed:
	kमुक्त(psy->full_trig_name);
full_failed:
	kमुक्त(psy->अक्षरging_trig_name);
अक्षरging_failed:
	kमुक्त(psy->अक्षरging_full_trig_name);
अक्षरging_full_failed:
	वापस -ENOMEM;
पूर्ण

अटल व्योम घातer_supply_हटाओ_bat_triggers(काष्ठा घातer_supply *psy)
अणु
	led_trigger_unरेजिस्टर_simple(psy->अक्षरging_full_trig);
	led_trigger_unरेजिस्टर_simple(psy->अक्षरging_trig);
	led_trigger_unरेजिस्टर_simple(psy->full_trig);
	led_trigger_unरेजिस्टर_simple(psy->अक्षरging_blink_full_solid_trig);
	kमुक्त(psy->अक्षरging_blink_full_solid_trig_name);
	kमुक्त(psy->full_trig_name);
	kमुक्त(psy->अक्षरging_trig_name);
	kमुक्त(psy->अक्षरging_full_trig_name);
पूर्ण

/* Generated घातer specअगरic LEDs triggers. */

अटल व्योम घातer_supply_update_gen_leds(काष्ठा घातer_supply *psy)
अणु
	जोड़ घातer_supply_propval online;

	अगर (घातer_supply_get_property(psy, POWER_SUPPLY_PROP_ONLINE, &online))
		वापस;

	dev_dbg(&psy->dev, "%s %d\n", __func__, online.पूर्णांकval);

	अगर (online.पूर्णांकval)
		led_trigger_event(psy->online_trig, LED_FULL);
	अन्यथा
		led_trigger_event(psy->online_trig, LED_OFF);
पूर्ण

अटल पूर्णांक घातer_supply_create_gen_triggers(काष्ठा घातer_supply *psy)
अणु
	psy->online_trig_name = kaप्र_लिखो(GFP_KERNEL, "%s-online",
					  psy->desc->name);
	अगर (!psy->online_trig_name)
		वापस -ENOMEM;

	led_trigger_रेजिस्टर_simple(psy->online_trig_name, &psy->online_trig);

	वापस 0;
पूर्ण

अटल व्योम घातer_supply_हटाओ_gen_triggers(काष्ठा घातer_supply *psy)
अणु
	led_trigger_unरेजिस्टर_simple(psy->online_trig);
	kमुक्त(psy->online_trig_name);
पूर्ण

/* Choice what triggers to create&update. */

व्योम घातer_supply_update_leds(काष्ठा घातer_supply *psy)
अणु
	अगर (psy->desc->type == POWER_SUPPLY_TYPE_BATTERY)
		घातer_supply_update_bat_leds(psy);
	अन्यथा
		घातer_supply_update_gen_leds(psy);
पूर्ण

पूर्णांक घातer_supply_create_triggers(काष्ठा घातer_supply *psy)
अणु
	अगर (psy->desc->type == POWER_SUPPLY_TYPE_BATTERY)
		वापस घातer_supply_create_bat_triggers(psy);
	वापस घातer_supply_create_gen_triggers(psy);
पूर्ण

व्योम घातer_supply_हटाओ_triggers(काष्ठा घातer_supply *psy)
अणु
	अगर (psy->desc->type == POWER_SUPPLY_TYPE_BATTERY)
		घातer_supply_हटाओ_bat_triggers(psy);
	अन्यथा
		घातer_supply_हटाओ_gen_triggers(psy);
पूर्ण
