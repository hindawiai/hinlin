<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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
 * Authors: Ben Skeggs
 * 	    Martin Peres
 */
#समावेश "priv.h"

#समावेश <subdev/bios/fan.h>
#समावेश <subdev/gpपन.स>
#समावेश <subdev/समयr.h>

अटल पूर्णांक
nvkm_fan_update(काष्ठा nvkm_fan *fan, bool immediate, पूर्णांक target)
अणु
	काष्ठा nvkm_therm *therm = fan->parent;
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_समयr *पंचांगr = subdev->device->समयr;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	पूर्णांक duty;

	/* update target fan speed, restricting to allowed range */
	spin_lock_irqsave(&fan->lock, flags);
	अगर (target < 0)
		target = fan->percent;
	target = max_t(u8, target, fan->bios.min_duty);
	target = min_t(u8, target, fan->bios.max_duty);
	अगर (fan->percent != target) अणु
		nvkm_debug(subdev, "FAN target: %d\n", target);
		fan->percent = target;
	पूर्ण

	/* check that we're not alपढ़ोy at the target duty cycle */
	duty = fan->get(therm);
	अगर (duty == target) अणु
		spin_unlock_irqrestore(&fan->lock, flags);
		वापस 0;
	पूर्ण

	/* smooth out the fanspeed increase/decrease */
	अगर (!immediate && duty >= 0) अणु
		/* the स्थिरant "3" is a rough approximation taken from
		 * nvidia's behaviour.
		 * it is meant to bump the fan speed more incrementally
		 */
		अगर (duty < target)
			duty = min(duty + 3, target);
		अन्यथा अगर (duty > target)
			duty = max(duty - 3, target);
	पूर्ण अन्यथा अणु
		duty = target;
	पूर्ण

	nvkm_debug(subdev, "FAN update: %d\n", duty);
	ret = fan->set(therm, duty);
	अगर (ret) अणु
		spin_unlock_irqrestore(&fan->lock, flags);
		वापस ret;
	पूर्ण

	/* fan speed updated, drop the fan lock beक्रमe grabbing the
	 * alarm-scheduling lock and risking a deadlock
	 */
	spin_unlock_irqrestore(&fan->lock, flags);

	/* schedule next fan update, अगर not at target speed alपढ़ोy */
	अगर (target != duty) अणु
		u16 bump_period = fan->bios.bump_period;
		u16 slow_करोwn_period = fan->bios.slow_करोwn_period;
		u64 delay;

		अगर (duty > target)
			delay = slow_करोwn_period;
		अन्यथा अगर (duty == target)
			delay = min(bump_period, slow_करोwn_period) ;
		अन्यथा
			delay = bump_period;

		nvkm_समयr_alarm(पंचांगr, delay * 1000 * 1000, &fan->alarm);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
nvkm_fan_alarm(काष्ठा nvkm_alarm *alarm)
अणु
	काष्ठा nvkm_fan *fan = container_of(alarm, काष्ठा nvkm_fan, alarm);
	nvkm_fan_update(fan, false, -1);
पूर्ण

पूर्णांक
nvkm_therm_fan_get(काष्ठा nvkm_therm *therm)
अणु
	वापस therm->fan->get(therm);
पूर्ण

पूर्णांक
nvkm_therm_fan_set(काष्ठा nvkm_therm *therm, bool immediate, पूर्णांक percent)
अणु
	वापस nvkm_fan_update(therm->fan, immediate, percent);
पूर्ण

पूर्णांक
nvkm_therm_fan_sense(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvkm_समयr *पंचांगr = device->समयr;
	काष्ठा nvkm_gpio *gpio = device->gpio;
	u32 cycles, cur, prev;
	u64 start, end, tach;

	अगर (therm->func->fan_sense)
		वापस therm->func->fan_sense(therm);

	अगर (therm->fan->tach.func == DCB_GPIO_UNUSED)
		वापस -ENODEV;

	/* Time a complete rotation and extrapolate to RPM:
	 * When the fan spins, it changes the value of GPIO FAN_SENSE.
	 * We get 4 changes (0 -> 1 -> 0 -> 1) per complete rotation.
	 */
	start = nvkm_समयr_पढ़ो(पंचांगr);
	prev = nvkm_gpio_get(gpio, 0, therm->fan->tach.func,
				      therm->fan->tach.line);
	cycles = 0;
	करो अणु
		usleep_range(500, 1000); /* supports 0 < rpm < 7500 */

		cur = nvkm_gpio_get(gpio, 0, therm->fan->tach.func,
					     therm->fan->tach.line);
		अगर (prev != cur) अणु
			अगर (!start)
				start = nvkm_समयr_पढ़ो(पंचांगr);
			cycles++;
			prev = cur;
		पूर्ण
	पूर्ण जबतक (cycles < 5 && nvkm_समयr_पढ़ो(पंचांगr) - start < 250000000);
	end = nvkm_समयr_पढ़ो(पंचांगr);

	अगर (cycles == 5) अणु
		tach = (u64)60000000000ULL;
		करो_भाग(tach, (end - start));
		वापस tach;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

पूर्णांक
nvkm_therm_fan_user_get(काष्ठा nvkm_therm *therm)
अणु
	वापस nvkm_therm_fan_get(therm);
पूर्ण

पूर्णांक
nvkm_therm_fan_user_set(काष्ठा nvkm_therm *therm, पूर्णांक percent)
अणु
	अगर (therm->mode != NVKM_THERM_CTRL_MANUAL)
		वापस -EINVAL;

	वापस nvkm_therm_fan_set(therm, true, percent);
पूर्ण

अटल व्योम
nvkm_therm_fan_set_शेषs(काष्ठा nvkm_therm *therm)
अणु
	therm->fan->bios.pwm_freq = 0;
	therm->fan->bios.min_duty = 0;
	therm->fan->bios.max_duty = 100;
	therm->fan->bios.bump_period = 500;
	therm->fan->bios.slow_करोwn_period = 2000;
	therm->fan->bios.linear_min_temp = 40;
	therm->fan->bios.linear_max_temp = 85;
पूर्ण

अटल व्योम
nvkm_therm_fan_safety_checks(काष्ठा nvkm_therm *therm)
अणु
	अगर (therm->fan->bios.min_duty > 100)
		therm->fan->bios.min_duty = 100;
	अगर (therm->fan->bios.max_duty > 100)
		therm->fan->bios.max_duty = 100;

	अगर (therm->fan->bios.min_duty > therm->fan->bios.max_duty)
		therm->fan->bios.min_duty = therm->fan->bios.max_duty;
पूर्ण

पूर्णांक
nvkm_therm_fan_init(काष्ठा nvkm_therm *therm)
अणु
	वापस 0;
पूर्ण

पूर्णांक
nvkm_therm_fan_fini(काष्ठा nvkm_therm *therm, bool suspend)
अणु
	काष्ठा nvkm_समयr *पंचांगr = therm->subdev.device->समयr;
	अगर (suspend)
		nvkm_समयr_alarm(पंचांगr, 0, &therm->fan->alarm);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_therm_fan_ctor(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_gpio *gpio = device->gpio;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा dcb_gpio_func func;
	पूर्णांक ret;

	/* attempt to locate a drivable fan, and determine control method */
	ret = nvkm_gpio_find(gpio, 0, DCB_GPIO_FAN, 0xff, &func);
	अगर (ret == 0) अणु
		/* FIXME: is this really the place to perक्रमm such checks ? */
		अगर (func.line != 16 && func.log[0] & DCB_GPIO_LOG_सूची_IN) अणु
			nvkm_debug(subdev, "GPIO_FAN is in input mode\n");
			ret = -EINVAL;
		पूर्ण अन्यथा अणु
			ret = nvkm_fanpwm_create(therm, &func);
			अगर (ret != 0)
				ret = nvkm_fantog_create(therm, &func);
		पूर्ण
	पूर्ण

	/* no controllable fan found, create a dummy fan module */
	अगर (ret != 0) अणु
		ret = nvkm_fannil_create(therm);
		अगर (ret)
			वापस ret;
	पूर्ण

	nvkm_debug(subdev, "FAN control: %s\n", therm->fan->type);

	/* पढ़ो the current speed, it is useful when resuming */
	therm->fan->percent = nvkm_therm_fan_get(therm);

	/* attempt to detect a tachometer connection */
	ret = nvkm_gpio_find(gpio, 0, DCB_GPIO_FAN_SENSE, 0xff,
			     &therm->fan->tach);
	अगर (ret)
		therm->fan->tach.func = DCB_GPIO_UNUSED;

	/* initialise fan bump/slow update handling */
	therm->fan->parent = therm;
	nvkm_alarm_init(&therm->fan->alarm, nvkm_fan_alarm);
	spin_lock_init(&therm->fan->lock);

	/* other अक्रमom init... */
	nvkm_therm_fan_set_शेषs(therm);
	nvbios_perf_fan_parse(bios, &therm->fan->perf);
	अगर (!nvbios_fan_parse(bios, &therm->fan->bios)) अणु
		nvkm_debug(subdev, "parsing the fan table failed\n");
		अगर (nvbios_therm_fan_parse(bios, &therm->fan->bios))
			nvkm_error(subdev, "parsing both fan tables failed\n");
	पूर्ण
	nvkm_therm_fan_safety_checks(therm);
	वापस 0;
पूर्ण
