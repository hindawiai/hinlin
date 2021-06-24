<शैली गुरु>
/*
 * Copyright 2012 The Nouveau community
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Martin Peres
 */
#समावेश "priv.h"

अटल व्योम
nvkm_therm_temp_set_शेषs(काष्ठा nvkm_therm *therm)
अणु
	therm->bios_sensor.offset_स्थिरant = 0;

	therm->bios_sensor.thrs_fan_boost.temp = 90;
	therm->bios_sensor.thrs_fan_boost.hysteresis = 3;

	therm->bios_sensor.thrs_करोwn_घड़ी.temp = 95;
	therm->bios_sensor.thrs_करोwn_घड़ी.hysteresis = 3;

	therm->bios_sensor.thrs_critical.temp = 105;
	therm->bios_sensor.thrs_critical.hysteresis = 5;

	therm->bios_sensor.thrs_shutकरोwn.temp = 135;
	therm->bios_sensor.thrs_shutकरोwn.hysteresis = 5; /*not that it matters */
पूर्ण

अटल व्योम
nvkm_therm_temp_safety_checks(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvbios_therm_sensor *s = &therm->bios_sensor;

	/* enक्रमce a minimum hysteresis on thresholds */
	s->thrs_fan_boost.hysteresis = max_t(u8, s->thrs_fan_boost.hysteresis, 2);
	s->thrs_करोwn_घड़ी.hysteresis = max_t(u8, s->thrs_करोwn_घड़ी.hysteresis, 2);
	s->thrs_critical.hysteresis = max_t(u8, s->thrs_critical.hysteresis, 2);
	s->thrs_shutकरोwn.hysteresis = max_t(u8, s->thrs_shutकरोwn.hysteresis, 2);
पूर्ण

/* must be called with alarm_program_lock taken ! */
व्योम
nvkm_therm_sensor_set_threshold_state(काष्ठा nvkm_therm *therm,
				      क्रमागत nvkm_therm_thrs thrs,
				      क्रमागत nvkm_therm_thrs_state st)
अणु
	therm->sensor.alarm_state[thrs] = st;
पूर्ण

/* must be called with alarm_program_lock taken ! */
क्रमागत nvkm_therm_thrs_state
nvkm_therm_sensor_get_threshold_state(काष्ठा nvkm_therm *therm,
				      क्रमागत nvkm_therm_thrs thrs)
अणु
	वापस therm->sensor.alarm_state[thrs];
पूर्ण

अटल व्योम
nv_घातeroff_work(काष्ठा work_काष्ठा *work)
अणु
	orderly_घातeroff(true);
	kमुक्त(work);
पूर्ण

व्योम
nvkm_therm_sensor_event(काष्ठा nvkm_therm *therm, क्रमागत nvkm_therm_thrs thrs,
			क्रमागत nvkm_therm_thrs_direction dir)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	bool active;
	अटल स्थिर अक्षर * स्थिर thresholds[] = अणु
		"fanboost", "downclock", "critical", "shutdown"
	पूर्ण;
	पूर्णांक temperature = therm->func->temp_get(therm);

	अगर (thrs < 0 || thrs > 3)
		वापस;

	अगर (dir == NVKM_THERM_THRS_FALLING)
		nvkm_info(subdev,
			  "temperature (%i C) went below the '%s' threshold\n",
			  temperature, thresholds[thrs]);
	अन्यथा
		nvkm_info(subdev, "temperature (%i C) hit the '%s' threshold\n",
			  temperature, thresholds[thrs]);

	active = (dir == NVKM_THERM_THRS_RISING);
	चयन (thrs) अणु
	हाल NVKM_THERM_THRS_FANBOOST:
		अगर (active) अणु
			nvkm_therm_fan_set(therm, true, 100);
			nvkm_therm_fan_mode(therm, NVKM_THERM_CTRL_AUTO);
		पूर्ण
		अवरोध;
	हाल NVKM_THERM_THRS_DOWNCLOCK:
		अगर (therm->emergency.करोwnघड़ी)
			therm->emergency.करोwnघड़ी(therm, active);
		अवरोध;
	हाल NVKM_THERM_THRS_CRITICAL:
		अगर (therm->emergency.छोड़ो)
			therm->emergency.छोड़ो(therm, active);
		अवरोध;
	हाल NVKM_THERM_THRS_SHUTDOWN:
		अगर (active) अणु
			काष्ठा work_काष्ठा *work;

			work = kदो_स्मृति(माप(*work), GFP_ATOMIC);
			अगर (work) अणु
				INIT_WORK(work, nv_घातeroff_work);
				schedule_work(work);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NVKM_THERM_THRS_NR:
		अवरोध;
	पूर्ण

पूर्ण

/* must be called with alarm_program_lock taken ! */
अटल व्योम
nvkm_therm_threshold_hyst_polling(काष्ठा nvkm_therm *therm,
				  स्थिर काष्ठा nvbios_therm_threshold *thrs,
				  क्रमागत nvkm_therm_thrs thrs_name)
अणु
	क्रमागत nvkm_therm_thrs_direction direction;
	क्रमागत nvkm_therm_thrs_state prev_state, new_state;
	पूर्णांक temp = therm->func->temp_get(therm);

	prev_state = nvkm_therm_sensor_get_threshold_state(therm, thrs_name);

	अगर (temp >= thrs->temp && prev_state == NVKM_THERM_THRS_LOWER) अणु
		direction = NVKM_THERM_THRS_RISING;
		new_state = NVKM_THERM_THRS_HIGHER;
	पूर्ण अन्यथा अगर (temp <= thrs->temp - thrs->hysteresis &&
			prev_state == NVKM_THERM_THRS_HIGHER) अणु
		direction = NVKM_THERM_THRS_FALLING;
		new_state = NVKM_THERM_THRS_LOWER;
	पूर्ण अन्यथा
		वापस; /* nothing to करो */

	nvkm_therm_sensor_set_threshold_state(therm, thrs_name, new_state);
	nvkm_therm_sensor_event(therm, thrs_name, direction);
पूर्ण

अटल व्योम
alarm_समयr_callback(काष्ठा nvkm_alarm *alarm)
अणु
	काष्ठा nvkm_therm *therm =
		container_of(alarm, काष्ठा nvkm_therm, sensor.therm_poll_alarm);
	काष्ठा nvbios_therm_sensor *sensor = &therm->bios_sensor;
	काष्ठा nvkm_समयr *पंचांगr = therm->subdev.device->समयr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&therm->sensor.alarm_program_lock, flags);

	nvkm_therm_threshold_hyst_polling(therm, &sensor->thrs_fan_boost,
					  NVKM_THERM_THRS_FANBOOST);

	nvkm_therm_threshold_hyst_polling(therm,
					  &sensor->thrs_करोwn_घड़ी,
					  NVKM_THERM_THRS_DOWNCLOCK);

	nvkm_therm_threshold_hyst_polling(therm, &sensor->thrs_critical,
					  NVKM_THERM_THRS_CRITICAL);

	nvkm_therm_threshold_hyst_polling(therm, &sensor->thrs_shutकरोwn,
					  NVKM_THERM_THRS_SHUTDOWN);

	spin_unlock_irqrestore(&therm->sensor.alarm_program_lock, flags);

	/* schedule the next poll in one second */
	अगर (therm->func->temp_get(therm) >= 0)
		nvkm_समयr_alarm(पंचांगr, 1000000000ULL, alarm);
पूर्ण

व्योम
nvkm_therm_program_alarms_polling(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvbios_therm_sensor *sensor = &therm->bios_sensor;

	nvkm_debug(&therm->subdev,
		   "programmed thresholds [ %d(%d), %d(%d), %d(%d), %d(%d) ]\n",
		   sensor->thrs_fan_boost.temp,
		   sensor->thrs_fan_boost.hysteresis,
		   sensor->thrs_करोwn_घड़ी.temp,
		   sensor->thrs_करोwn_घड़ी.hysteresis,
		   sensor->thrs_critical.temp,
		   sensor->thrs_critical.hysteresis,
		   sensor->thrs_shutकरोwn.temp,
		   sensor->thrs_shutकरोwn.hysteresis);

	alarm_समयr_callback(&therm->sensor.therm_poll_alarm);
पूर्ण

पूर्णांक
nvkm_therm_sensor_init(काष्ठा nvkm_therm *therm)
अणु
	therm->func->program_alarms(therm);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_therm_sensor_fini(काष्ठा nvkm_therm *therm, bool suspend)
अणु
	काष्ठा nvkm_समयr *पंचांगr = therm->subdev.device->समयr;
	अगर (suspend)
		nvkm_समयr_alarm(पंचांगr, 0, &therm->sensor.therm_poll_alarm);
	वापस 0;
पूर्ण

व्योम
nvkm_therm_sensor_preinit(काष्ठा nvkm_therm *therm)
अणु
	स्थिर अक्षर *sensor_avail = "yes";

	अगर (therm->func->temp_get(therm) < 0)
		sensor_avail = "no";

	nvkm_debug(&therm->subdev, "internal sensor: %s\n", sensor_avail);
पूर्ण

पूर्णांक
nvkm_therm_sensor_ctor(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;

	nvkm_alarm_init(&therm->sensor.therm_poll_alarm, alarm_समयr_callback);

	nvkm_therm_temp_set_शेषs(therm);
	अगर (nvbios_therm_sensor_parse(bios, NVBIOS_THERM_DOMAIN_CORE,
				      &therm->bios_sensor))
		nvkm_error(subdev, "nvbios_therm_sensor_parse failed\n");
	nvkm_therm_temp_safety_checks(therm);

	वापस 0;
पूर्ण
