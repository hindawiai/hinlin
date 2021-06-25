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

#समावेश <core/option.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/fan.h>
#समावेश <subdev/gpपन.स>

काष्ठा nvkm_fanpwm अणु
	काष्ठा nvkm_fan base;
	काष्ठा dcb_gpio_func func;
पूर्ण;

अटल पूर्णांक
nvkm_fanpwm_get(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_fanpwm *fan = (व्योम *)therm->fan;
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvkm_gpio *gpio = device->gpio;
	पूर्णांक card_type = device->card_type;
	u32 भागs, duty;
	पूर्णांक ret;

	ret = therm->func->pwm_get(therm, fan->func.line, &भागs, &duty);
	अगर (ret == 0 && भागs) अणु
		भागs = max(भागs, duty);
		अगर (card_type <= NV_40 || (fan->func.log[0] & 1))
			duty = भागs - duty;
		वापस (duty * 100) / भागs;
	पूर्ण

	वापस nvkm_gpio_get(gpio, 0, fan->func.func, fan->func.line) * 100;
पूर्ण

अटल पूर्णांक
nvkm_fanpwm_set(काष्ठा nvkm_therm *therm, पूर्णांक percent)
अणु
	काष्ठा nvkm_fanpwm *fan = (व्योम *)therm->fan;
	पूर्णांक card_type = therm->subdev.device->card_type;
	u32 भागs, duty;
	पूर्णांक ret;

	भागs = fan->base.perf.pwm_भागisor;
	अगर (fan->base.bios.pwm_freq) अणु
		भागs = 1;
		अगर (therm->func->pwm_घड़ी)
			भागs = therm->func->pwm_घड़ी(therm, fan->func.line);
		भागs /= fan->base.bios.pwm_freq;
	पूर्ण

	duty = ((भागs * percent) + 99) / 100;
	अगर (card_type <= NV_40 || (fan->func.log[0] & 1))
		duty = भागs - duty;

	ret = therm->func->pwm_set(therm, fan->func.line, भागs, duty);
	अगर (ret == 0)
		ret = therm->func->pwm_ctrl(therm, fan->func.line, true);
	वापस ret;
पूर्ण

पूर्णांक
nvkm_fanpwm_create(काष्ठा nvkm_therm *therm, काष्ठा dcb_gpio_func *func)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	काष्ठा nvkm_fanpwm *fan;
	काष्ठा nvbios_therm_fan info = अणुपूर्ण;
	u32 भागs, duty;

	nvbios_fan_parse(bios, &info);

	अगर (!nvkm_boolopt(device->cfgopt, "NvFanPWM", func->param) ||
	    !therm->func->pwm_ctrl || info.type == NVBIOS_THERM_FAN_TOGGLE ||
	     therm->func->pwm_get(therm, func->line, &भागs, &duty) == -ENODEV)
		वापस -ENODEV;

	fan = kzalloc(माप(*fan), GFP_KERNEL);
	therm->fan = &fan->base;
	अगर (!fan)
		वापस -ENOMEM;

	fan->base.type = "PWM";
	fan->base.get = nvkm_fanpwm_get;
	fan->base.set = nvkm_fanpwm_set;
	fan->func = *func;
	वापस 0;
पूर्ण
