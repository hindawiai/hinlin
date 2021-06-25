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

#समावेश <core/option.h>
#समावेश <subdev/pmu.h>

पूर्णांक
nvkm_therm_temp_get(काष्ठा nvkm_therm *therm)
अणु
	अगर (therm->func->temp_get)
		वापस therm->func->temp_get(therm);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
nvkm_therm_update_trip(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvbios_therm_trip_poपूर्णांक *trip = therm->fan->bios.trip,
				       *cur_trip = शून्य,
				       *last_trip = therm->last_trip;
	u8  temp = therm->func->temp_get(therm);
	u16 duty, i;

	/* look क्रम the trip poपूर्णांक corresponding to the current temperature */
	cur_trip = शून्य;
	क्रम (i = 0; i < therm->fan->bios.nr_fan_trip; i++) अणु
		अगर (temp >= trip[i].temp)
			cur_trip = &trip[i];
	पूर्ण

	/* account क्रम the hysteresis cycle */
	अगर (last_trip && temp <= (last_trip->temp) &&
	    temp > (last_trip->temp - last_trip->hysteresis))
		cur_trip = last_trip;

	अगर (cur_trip) अणु
		duty = cur_trip->fan_duty;
		therm->last_trip = cur_trip;
	पूर्ण अन्यथा अणु
		duty = 0;
		therm->last_trip = शून्य;
	पूर्ण

	वापस duty;
पूर्ण

अटल पूर्णांक
nvkm_therm_compute_linear_duty(काष्ठा nvkm_therm *therm, u8 linear_min_temp,
                               u8 linear_max_temp)
अणु
	u8  temp = therm->func->temp_get(therm);
	u16 duty;

	/* handle the non-linear part first */
	अगर (temp < linear_min_temp)
		वापस therm->fan->bios.min_duty;
	अन्यथा अगर (temp > linear_max_temp)
		वापस therm->fan->bios.max_duty;

	/* we are in the linear zone */
	duty  = (temp - linear_min_temp);
	duty *= (therm->fan->bios.max_duty - therm->fan->bios.min_duty);
	duty /= (linear_max_temp - linear_min_temp);
	duty += therm->fan->bios.min_duty;
	वापस duty;
पूर्ण

अटल पूर्णांक
nvkm_therm_update_linear(काष्ठा nvkm_therm *therm)
अणु
	u8  min = therm->fan->bios.linear_min_temp;
	u8  max = therm->fan->bios.linear_max_temp;
	वापस nvkm_therm_compute_linear_duty(therm, min, max);
पूर्ण

अटल पूर्णांक
nvkm_therm_update_linear_fallback(काष्ठा nvkm_therm *therm)
अणु
	u8 max = therm->bios_sensor.thrs_fan_boost.temp;
	वापस nvkm_therm_compute_linear_duty(therm, 30, max);
पूर्ण

अटल व्योम
nvkm_therm_update(काष्ठा nvkm_therm *therm, पूर्णांक mode)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_समयr *पंचांगr = subdev->device->समयr;
	अचिन्हित दीर्घ flags;
	bool immd = true;
	bool poll = true;
	पूर्णांक duty = -1;

	spin_lock_irqsave(&therm->lock, flags);
	अगर (mode < 0)
		mode = therm->mode;
	therm->mode = mode;

	चयन (mode) अणु
	हाल NVKM_THERM_CTRL_MANUAL:
		nvkm_समयr_alarm(पंचांगr, 0, &therm->alarm);
		duty = nvkm_therm_fan_get(therm);
		अगर (duty < 0)
			duty = 100;
		poll = false;
		अवरोध;
	हाल NVKM_THERM_CTRL_AUTO:
		चयन(therm->fan->bios.fan_mode) अणु
		हाल NVBIOS_THERM_FAN_TRIP:
			duty = nvkm_therm_update_trip(therm);
			अवरोध;
		हाल NVBIOS_THERM_FAN_LINEAR:
			duty = nvkm_therm_update_linear(therm);
			अवरोध;
		हाल NVBIOS_THERM_FAN_OTHER:
			अगर (therm->cstate) अणु
				duty = therm->cstate;
				poll = false;
			पूर्ण अन्यथा अणु
				duty = nvkm_therm_update_linear_fallback(therm);
			पूर्ण
			अवरोध;
		पूर्ण
		immd = false;
		अवरोध;
	हाल NVKM_THERM_CTRL_NONE:
	शेष:
		nvkm_समयr_alarm(पंचांगr, 0, &therm->alarm);
		poll = false;
	पूर्ण

	अगर (poll)
		nvkm_समयr_alarm(पंचांगr, 1000000000ULL, &therm->alarm);
	spin_unlock_irqrestore(&therm->lock, flags);

	अगर (duty >= 0) अणु
		nvkm_debug(subdev, "FAN target request: %d%%\n", duty);
		nvkm_therm_fan_set(therm, immd, duty);
	पूर्ण
पूर्ण

पूर्णांक
nvkm_therm_cstate(काष्ठा nvkm_therm *therm, पूर्णांक fan, पूर्णांक dir)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	अगर (!dir || (dir < 0 && fan < therm->cstate) ||
		    (dir > 0 && fan > therm->cstate)) अणु
		nvkm_debug(subdev, "default fan speed -> %d%%\n", fan);
		therm->cstate = fan;
		nvkm_therm_update(therm, -1);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
nvkm_therm_alarm(काष्ठा nvkm_alarm *alarm)
अणु
	काष्ठा nvkm_therm *therm =
	       container_of(alarm, काष्ठा nvkm_therm, alarm);
	nvkm_therm_update(therm, -1);
पूर्ण

पूर्णांक
nvkm_therm_fan_mode(काष्ठा nvkm_therm *therm, पूर्णांक mode)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अटल स्थिर अक्षर *name[] = अणु
		"disabled",
		"manual",
		"automatic"
	पूर्ण;

	/* The शेष PPWR ucode on fermi पूर्णांकerferes with fan management */
	अगर ((mode >= ARRAY_SIZE(name)) ||
	    (mode != NVKM_THERM_CTRL_NONE && nvkm_pmu_fan_controlled(device)))
		वापस -EINVAL;

	/* करो not allow स्वतःmatic fan management अगर the thermal sensor is
	 * not available */
	अगर (mode == NVKM_THERM_CTRL_AUTO &&
	    therm->func->temp_get(therm) < 0)
		वापस -EINVAL;

	अगर (therm->mode == mode)
		वापस 0;

	nvkm_debug(subdev, "fan management: %s\n", name[mode]);
	nvkm_therm_update(therm, mode);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_therm_attr_get(काष्ठा nvkm_therm *therm, क्रमागत nvkm_therm_attr_type type)
अणु
	चयन (type) अणु
	हाल NVKM_THERM_ATTR_FAN_MIN_DUTY:
		वापस therm->fan->bios.min_duty;
	हाल NVKM_THERM_ATTR_FAN_MAX_DUTY:
		वापस therm->fan->bios.max_duty;
	हाल NVKM_THERM_ATTR_FAN_MODE:
		वापस therm->mode;
	हाल NVKM_THERM_ATTR_THRS_FAN_BOOST:
		वापस therm->bios_sensor.thrs_fan_boost.temp;
	हाल NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST:
		वापस therm->bios_sensor.thrs_fan_boost.hysteresis;
	हाल NVKM_THERM_ATTR_THRS_DOWN_CLK:
		वापस therm->bios_sensor.thrs_करोwn_घड़ी.temp;
	हाल NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST:
		वापस therm->bios_sensor.thrs_करोwn_घड़ी.hysteresis;
	हाल NVKM_THERM_ATTR_THRS_CRITICAL:
		वापस therm->bios_sensor.thrs_critical.temp;
	हाल NVKM_THERM_ATTR_THRS_CRITICAL_HYST:
		वापस therm->bios_sensor.thrs_critical.hysteresis;
	हाल NVKM_THERM_ATTR_THRS_SHUTDOWN:
		वापस therm->bios_sensor.thrs_shutकरोwn.temp;
	हाल NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST:
		वापस therm->bios_sensor.thrs_shutकरोwn.hysteresis;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक
nvkm_therm_attr_set(काष्ठा nvkm_therm *therm,
		    क्रमागत nvkm_therm_attr_type type, पूर्णांक value)
अणु
	चयन (type) अणु
	हाल NVKM_THERM_ATTR_FAN_MIN_DUTY:
		अगर (value < 0)
			value = 0;
		अगर (value > therm->fan->bios.max_duty)
			value = therm->fan->bios.max_duty;
		therm->fan->bios.min_duty = value;
		वापस 0;
	हाल NVKM_THERM_ATTR_FAN_MAX_DUTY:
		अगर (value < 0)
			value = 0;
		अगर (value < therm->fan->bios.min_duty)
			value = therm->fan->bios.min_duty;
		therm->fan->bios.max_duty = value;
		वापस 0;
	हाल NVKM_THERM_ATTR_FAN_MODE:
		वापस nvkm_therm_fan_mode(therm, value);
	हाल NVKM_THERM_ATTR_THRS_FAN_BOOST:
		therm->bios_sensor.thrs_fan_boost.temp = value;
		therm->func->program_alarms(therm);
		वापस 0;
	हाल NVKM_THERM_ATTR_THRS_FAN_BOOST_HYST:
		therm->bios_sensor.thrs_fan_boost.hysteresis = value;
		therm->func->program_alarms(therm);
		वापस 0;
	हाल NVKM_THERM_ATTR_THRS_DOWN_CLK:
		therm->bios_sensor.thrs_करोwn_घड़ी.temp = value;
		therm->func->program_alarms(therm);
		वापस 0;
	हाल NVKM_THERM_ATTR_THRS_DOWN_CLK_HYST:
		therm->bios_sensor.thrs_करोwn_घड़ी.hysteresis = value;
		therm->func->program_alarms(therm);
		वापस 0;
	हाल NVKM_THERM_ATTR_THRS_CRITICAL:
		therm->bios_sensor.thrs_critical.temp = value;
		therm->func->program_alarms(therm);
		वापस 0;
	हाल NVKM_THERM_ATTR_THRS_CRITICAL_HYST:
		therm->bios_sensor.thrs_critical.hysteresis = value;
		therm->func->program_alarms(therm);
		वापस 0;
	हाल NVKM_THERM_ATTR_THRS_SHUTDOWN:
		therm->bios_sensor.thrs_shutकरोwn.temp = value;
		therm->func->program_alarms(therm);
		वापस 0;
	हाल NVKM_THERM_ATTR_THRS_SHUTDOWN_HYST:
		therm->bios_sensor.thrs_shutकरोwn.hysteresis = value;
		therm->func->program_alarms(therm);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

व्योम
nvkm_therm_clkgate_enable(काष्ठा nvkm_therm *therm)
अणु
	अगर (!therm || !therm->func->clkgate_enable || !therm->clkgating_enabled)
		वापस;

	nvkm_debug(&therm->subdev,
		   "Enabling clockgating\n");
	therm->func->clkgate_enable(therm);
पूर्ण

व्योम
nvkm_therm_clkgate_fini(काष्ठा nvkm_therm *therm, bool suspend)
अणु
	अगर (!therm || !therm->func->clkgate_fini || !therm->clkgating_enabled)
		वापस;

	nvkm_debug(&therm->subdev,
		   "Preparing clockgating for %s\n",
		   suspend ? "suspend" : "fini");
	therm->func->clkgate_fini(therm, suspend);
पूर्ण

अटल व्योम
nvkm_therm_clkgate_oneinit(काष्ठा nvkm_therm *therm)
अणु
	अगर (!therm->func->clkgate_enable || !therm->clkgating_enabled)
		वापस;

	nvkm_info(&therm->subdev, "Clockgating enabled\n");
पूर्ण

अटल व्योम
nvkm_therm_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_therm *therm = nvkm_therm(subdev);
	अगर (therm->func->पूर्णांकr)
		therm->func->पूर्णांकr(therm);
पूर्ण

अटल पूर्णांक
nvkm_therm_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_therm *therm = nvkm_therm(subdev);

	अगर (therm->func->fini)
		therm->func->fini(therm);

	nvkm_therm_fan_fini(therm, suspend);
	nvkm_therm_sensor_fini(therm, suspend);

	अगर (suspend) अणु
		therm->suspend = therm->mode;
		therm->mode = NVKM_THERM_CTRL_NONE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_therm_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_therm *therm = nvkm_therm(subdev);
	nvkm_therm_sensor_ctor(therm);
	nvkm_therm_ic_ctor(therm);
	nvkm_therm_fan_ctor(therm);
	nvkm_therm_fan_mode(therm, NVKM_THERM_CTRL_AUTO);
	nvkm_therm_sensor_preinit(therm);
	nvkm_therm_clkgate_oneinit(therm);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_therm_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_therm *therm = nvkm_therm(subdev);

	अगर (therm->func->init)
		therm->func->init(therm);

	अगर (therm->suspend >= 0) अणु
		/* restore the pwm value only when on manual or स्वतः mode */
		अगर (therm->suspend > 0)
			nvkm_therm_fan_set(therm, true, therm->fan->percent);

		nvkm_therm_fan_mode(therm, therm->suspend);
	पूर्ण

	nvkm_therm_sensor_init(therm);
	nvkm_therm_fan_init(therm);
	वापस 0;
पूर्ण

व्योम
nvkm_therm_clkgate_init(काष्ठा nvkm_therm *therm,
			स्थिर काष्ठा nvkm_therm_clkgate_pack *p)
अणु
	अगर (!therm || !therm->func->clkgate_init || !therm->clkgating_enabled)
		वापस;

	therm->func->clkgate_init(therm, p);
पूर्ण

अटल व्योम *
nvkm_therm_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_therm *therm = nvkm_therm(subdev);
	kमुक्त(therm->fan);
	वापस therm;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_therm = अणु
	.dtor = nvkm_therm_dtor,
	.oneinit = nvkm_therm_oneinit,
	.init = nvkm_therm_init,
	.fini = nvkm_therm_fini,
	.पूर्णांकr = nvkm_therm_पूर्णांकr,
पूर्ण;

व्योम
nvkm_therm_ctor(काष्ठा nvkm_therm *therm, काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type,
		पूर्णांक inst, स्थिर काष्ठा nvkm_therm_func *func)
अणु
	nvkm_subdev_ctor(&nvkm_therm, device, type, inst, &therm->subdev);
	therm->func = func;

	nvkm_alarm_init(&therm->alarm, nvkm_therm_alarm);
	spin_lock_init(&therm->lock);
	spin_lock_init(&therm->sensor.alarm_program_lock);

	therm->fan_get = nvkm_therm_fan_user_get;
	therm->fan_set = nvkm_therm_fan_user_set;
	therm->attr_get = nvkm_therm_attr_get;
	therm->attr_set = nvkm_therm_attr_set;
	therm->mode = therm->suspend = -1; /* undefined */

	therm->clkgating_enabled = nvkm_boolopt(device->cfgopt,
						"NvPmEnableGating", false);
पूर्ण

पूर्णांक
nvkm_therm_new_(स्थिर काष्ठा nvkm_therm_func *func, काष्ठा nvkm_device *device,
		क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_therm **ptherm)
अणु
	काष्ठा nvkm_therm *therm;

	अगर (!(therm = *ptherm = kzalloc(माप(*therm), GFP_KERNEL)))
		वापस -ENOMEM;

	nvkm_therm_ctor(therm, device, type, inst, func);
	वापस 0;
पूर्ण
