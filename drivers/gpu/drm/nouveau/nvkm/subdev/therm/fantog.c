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

#समावेश <subdev/gpपन.स>
#समावेश <subdev/समयr.h>

काष्ठा nvkm_fantog अणु
	काष्ठा nvkm_fan base;
	काष्ठा nvkm_alarm alarm;
	spinlock_t lock;
	u32 period_us;
	u32 percent;
	काष्ठा dcb_gpio_func func;
पूर्ण;

अटल व्योम
nvkm_fantog_update(काष्ठा nvkm_fantog *fan, पूर्णांक percent)
अणु
	काष्ठा nvkm_therm *therm = fan->base.parent;
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvkm_समयr *पंचांगr = device->समयr;
	काष्ठा nvkm_gpio *gpio = device->gpio;
	अचिन्हित दीर्घ flags;
	पूर्णांक duty;

	spin_lock_irqsave(&fan->lock, flags);
	अगर (percent < 0)
		percent = fan->percent;
	fan->percent = percent;

	duty = !nvkm_gpio_get(gpio, 0, DCB_GPIO_FAN, 0xff);
	nvkm_gpio_set(gpio, 0, DCB_GPIO_FAN, 0xff, duty);

	अगर (percent != (duty * 100)) अणु
		u64 next_change = (percent * fan->period_us) / 100;
		अगर (!duty)
			next_change = fan->period_us - next_change;
		nvkm_समयr_alarm(पंचांगr, next_change * 1000, &fan->alarm);
	पूर्ण
	spin_unlock_irqrestore(&fan->lock, flags);
पूर्ण

अटल व्योम
nvkm_fantog_alarm(काष्ठा nvkm_alarm *alarm)
अणु
	काष्ठा nvkm_fantog *fan =
	       container_of(alarm, काष्ठा nvkm_fantog, alarm);
	nvkm_fantog_update(fan, -1);
पूर्ण

अटल पूर्णांक
nvkm_fantog_get(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_fantog *fan = (व्योम *)therm->fan;
	वापस fan->percent;
पूर्ण

अटल पूर्णांक
nvkm_fantog_set(काष्ठा nvkm_therm *therm, पूर्णांक percent)
अणु
	काष्ठा nvkm_fantog *fan = (व्योम *)therm->fan;
	अगर (therm->func->pwm_ctrl)
		therm->func->pwm_ctrl(therm, fan->func.line, false);
	nvkm_fantog_update(fan, percent);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_fantog_create(काष्ठा nvkm_therm *therm, काष्ठा dcb_gpio_func *func)
अणु
	काष्ठा nvkm_fantog *fan;
	पूर्णांक ret;

	अगर (therm->func->pwm_ctrl) अणु
		ret = therm->func->pwm_ctrl(therm, func->line, false);
		अगर (ret)
			वापस ret;
	पूर्ण

	fan = kzalloc(माप(*fan), GFP_KERNEL);
	therm->fan = &fan->base;
	अगर (!fan)
		वापस -ENOMEM;

	fan->base.type = "toggle";
	fan->base.get = nvkm_fantog_get;
	fan->base.set = nvkm_fantog_set;
	nvkm_alarm_init(&fan->alarm, nvkm_fantog_alarm);
	fan->period_us = 100000; /* 10Hz */
	fan->percent = 100;
	fan->func = *func;
	spin_lock_init(&fan->lock);
	वापस 0;
पूर्ण
