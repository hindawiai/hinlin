<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2016 National Instruments Corp. */
#समावेश <linux/leds.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_led_triggers.h>
#समावेश <linux/netdevice.h>

अटल काष्ठा phy_led_trigger *phy_speed_to_led_trigger(काष्ठा phy_device *phy,
							अचिन्हित पूर्णांक speed)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < phy->phy_num_led_triggers; i++) अणु
		अगर (phy->phy_led_triggers[i].speed == speed)
			वापस &phy->phy_led_triggers[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम phy_led_trigger_no_link(काष्ठा phy_device *phy)
अणु
	अगर (phy->last_triggered) अणु
		led_trigger_event(&phy->last_triggered->trigger, LED_OFF);
		led_trigger_event(&phy->led_link_trigger->trigger, LED_OFF);
		phy->last_triggered = शून्य;
	पूर्ण
पूर्ण

व्योम phy_led_trigger_change_speed(काष्ठा phy_device *phy)
अणु
	काष्ठा phy_led_trigger *plt;

	अगर (!phy->link)
		वापस phy_led_trigger_no_link(phy);

	अगर (phy->speed == 0)
		वापस;

	plt = phy_speed_to_led_trigger(phy, phy->speed);
	अगर (!plt) अणु
		netdev_alert(phy->attached_dev,
			     "No phy led trigger registered for speed(%d)\n",
			     phy->speed);
		वापस phy_led_trigger_no_link(phy);
	पूर्ण

	अगर (plt != phy->last_triggered) अणु
		अगर (!phy->last_triggered)
			led_trigger_event(&phy->led_link_trigger->trigger,
					  LED_FULL);
		अन्यथा
			led_trigger_event(&phy->last_triggered->trigger, LED_OFF);

		led_trigger_event(&plt->trigger, LED_FULL);
		phy->last_triggered = plt;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(phy_led_trigger_change_speed);

अटल व्योम phy_led_trigger_क्रमmat_name(काष्ठा phy_device *phy, अक्षर *buf,
					माप_प्रकार size, स्थिर अक्षर *suffix)
अणु
	snम_लिखो(buf, size, PHY_ID_FMT ":%s",
		 phy->mdio.bus->id, phy->mdio.addr, suffix);
पूर्ण

अटल पूर्णांक phy_led_trigger_रेजिस्टर(काष्ठा phy_device *phy,
				    काष्ठा phy_led_trigger *plt,
				    अचिन्हित पूर्णांक speed,
				    स्थिर अक्षर *suffix)
अणु
	plt->speed = speed;
	phy_led_trigger_क्रमmat_name(phy, plt->name, माप(plt->name), suffix);
	plt->trigger.name = plt->name;

	वापस led_trigger_रेजिस्टर(&plt->trigger);
पूर्ण

अटल व्योम phy_led_trigger_unरेजिस्टर(काष्ठा phy_led_trigger *plt)
अणु
	led_trigger_unरेजिस्टर(&plt->trigger);
पूर्ण

पूर्णांक phy_led_triggers_रेजिस्टर(काष्ठा phy_device *phy)
अणु
	पूर्णांक i, err;
	अचिन्हित पूर्णांक speeds[50];

	phy->phy_num_led_triggers = phy_supported_speeds(phy, speeds,
							 ARRAY_SIZE(speeds));
	अगर (!phy->phy_num_led_triggers)
		वापस 0;

	phy->led_link_trigger = devm_kzalloc(&phy->mdio.dev,
					     माप(*phy->led_link_trigger),
					     GFP_KERNEL);
	अगर (!phy->led_link_trigger) अणु
		err = -ENOMEM;
		जाओ out_clear;
	पूर्ण

	err = phy_led_trigger_रेजिस्टर(phy, phy->led_link_trigger, 0, "link");
	अगर (err)
		जाओ out_मुक्त_link;

	phy->phy_led_triggers = devm_kसुस्मृति(&phy->mdio.dev,
					    phy->phy_num_led_triggers,
					    माप(काष्ठा phy_led_trigger),
					    GFP_KERNEL);
	अगर (!phy->phy_led_triggers) अणु
		err = -ENOMEM;
		जाओ out_unreg_link;
	पूर्ण

	क्रम (i = 0; i < phy->phy_num_led_triggers; i++) अणु
		err = phy_led_trigger_रेजिस्टर(phy, &phy->phy_led_triggers[i],
					       speeds[i],
					       phy_speed_to_str(speeds[i]));
		अगर (err)
			जाओ out_unreg;
	पूर्ण

	phy->last_triggered = शून्य;
	phy_led_trigger_change_speed(phy);

	वापस 0;
out_unreg:
	जबतक (i--)
		phy_led_trigger_unरेजिस्टर(&phy->phy_led_triggers[i]);
	devm_kमुक्त(&phy->mdio.dev, phy->phy_led_triggers);
out_unreg_link:
	phy_led_trigger_unरेजिस्टर(phy->led_link_trigger);
out_मुक्त_link:
	devm_kमुक्त(&phy->mdio.dev, phy->led_link_trigger);
	phy->led_link_trigger = शून्य;
out_clear:
	phy->phy_num_led_triggers = 0;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(phy_led_triggers_रेजिस्टर);

व्योम phy_led_triggers_unरेजिस्टर(काष्ठा phy_device *phy)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < phy->phy_num_led_triggers; i++)
		phy_led_trigger_unरेजिस्टर(&phy->phy_led_triggers[i]);

	अगर (phy->led_link_trigger)
		phy_led_trigger_unरेजिस्टर(phy->led_link_trigger);
पूर्ण
EXPORT_SYMBOL_GPL(phy_led_triggers_unरेजिस्टर);
