<शैली गुरु>
/*
 * via-pmu LED class device
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA  02110-1301 USA
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/leds.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश <यंत्र/prom.h>

अटल spinlock_t pmu_blink_lock;
अटल काष्ठा adb_request pmu_blink_req;
/* -1: no change, 0: request off, 1: request on */
अटल पूर्णांक requested_change;

अटल व्योम pmu_req_करोne(काष्ठा adb_request * req)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmu_blink_lock, flags);
	/* अगर someone requested a change in the meanसमय
	 * (we only see the last one which is fine)
	 * then apply it now */
	अगर (requested_change != -1 && !pmu_sys_suspended)
		pmu_request(&pmu_blink_req, शून्य, 4, 0xee, 4, 0, requested_change);
	/* reset requested change */
	requested_change = -1;
	spin_unlock_irqrestore(&pmu_blink_lock, flags);
पूर्ण

अटल व्योम pmu_led_set(काष्ठा led_classdev *led_cdev,
			क्रमागत led_brightness brightness)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pmu_blink_lock, flags);
	चयन (brightness) अणु
	हाल LED_OFF:
		requested_change = 0;
		अवरोध;
	हाल LED_FULL:
		requested_change = 1;
		अवरोध;
	शेष:
		जाओ out;
		अवरोध;
	पूर्ण
	/* अगर request isn't done, then don't करो anything */
	अगर (pmu_blink_req.complete && !pmu_sys_suspended)
		pmu_request(&pmu_blink_req, शून्य, 4, 0xee, 4, 0, requested_change);
 out:
 	spin_unlock_irqrestore(&pmu_blink_lock, flags);
पूर्ण

अटल काष्ठा led_classdev pmu_led = अणु
	.name = "pmu-led::front",
#अगर_घोषित CONFIG_ADB_PMU_LED_DISK
	.शेष_trigger = "disk-activity",
#पूर्ण_अगर
	.brightness_set = pmu_led_set,
पूर्ण;

अटल पूर्णांक __init via_pmu_led_init(व्योम)
अणु
	काष्ठा device_node *dt;
	स्थिर अक्षर *model;

	/* only करो this on keylargo based models */
	अगर (pmu_get_model() != PMU_KEYLARGO_BASED)
		वापस -ENODEV;

	dt = of_find_node_by_path("/");
	अगर (dt == शून्य)
		वापस -ENODEV;
	model = of_get_property(dt, "model", शून्य);
	अगर (model == शून्य) अणु
		of_node_put(dt);
		वापस -ENODEV;
	पूर्ण
	अगर (म_भेदन(model, "PowerBook", म_माप("PowerBook")) != 0 &&
	    म_भेदन(model, "iBook", म_माप("iBook")) != 0 &&
	    म_भेद(model, "PowerMac7,2") != 0 &&
	    म_भेद(model, "PowerMac7,3") != 0) अणु
		of_node_put(dt);
		/* ignore */
		वापस -ENODEV;
	पूर्ण
	of_node_put(dt);

	spin_lock_init(&pmu_blink_lock);
	/* no outstanding req */
	pmu_blink_req.complete = 1;
	pmu_blink_req.करोne = pmu_req_करोne;

	वापस led_classdev_रेजिस्टर(शून्य, &pmu_led);
पूर्ण

late_initcall(via_pmu_led_init);
