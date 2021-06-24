<शैली गुरु>
/*
 * via-pmu event device क्रम reporting some events that come through the PMU
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

#समावेश <linux/input.h>
#समावेश <linux/adb.h>
#समावेश <linux/pmu.h>
#समावेश "via-pmu-event.h"

अटल काष्ठा input_dev *pmu_input_dev;

अटल पूर्णांक __init via_pmu_event_init(व्योम)
अणु
	पूर्णांक err;

	/* करो other models report button/lid status? */
	अगर (pmu_get_model() != PMU_KEYLARGO_BASED)
		वापस -ENODEV;

	pmu_input_dev = input_allocate_device();
	अगर (!pmu_input_dev)
		वापस -ENOMEM;

	pmu_input_dev->name = "PMU";
	pmu_input_dev->id.bustype = BUS_HOST;
	pmu_input_dev->id.venकरोr = 0x0001;
	pmu_input_dev->id.product = 0x0001;
	pmu_input_dev->id.version = 0x0100;

	set_bit(EV_KEY, pmu_input_dev->evbit);
	set_bit(EV_SW, pmu_input_dev->evbit);
	set_bit(KEY_POWER, pmu_input_dev->keybit);
	set_bit(SW_LID, pmu_input_dev->swbit);

	err = input_रेजिस्टर_device(pmu_input_dev);
	अगर (err)
		input_मुक्त_device(pmu_input_dev);
	वापस err;
पूर्ण

व्योम via_pmu_event(पूर्णांक key, पूर्णांक करोwn)
अणु

	अगर (unlikely(!pmu_input_dev))
		वापस;

	चयन (key) अणु
	हाल PMU_EVT_POWER:
		input_report_key(pmu_input_dev, KEY_POWER, करोwn);
		अवरोध;
	हाल PMU_EVT_LID:
		input_report_चयन(pmu_input_dev, SW_LID, करोwn);
		अवरोध;
	शेष:
		/* no such key handled */
		वापस;
	पूर्ण

	input_sync(pmu_input_dev);
पूर्ण

late_initcall(via_pmu_event_init);
