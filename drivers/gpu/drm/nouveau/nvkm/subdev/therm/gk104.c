<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
 * Authors: Lyude Paul
 */
#समावेश <core/device.h>

#समावेश "priv.h"
#समावेश "gk104.h"

व्योम
gk104_clkgate_enable(काष्ठा nvkm_therm *base)
अणु
	काष्ठा gk104_therm *therm = gk104_therm(base);
	काष्ठा nvkm_device *dev = therm->base.subdev.device;
	स्थिर काष्ठा gk104_clkgate_engine_info *order = therm->clkgate_order;
	पूर्णांक i;

	/* Program ENG_MANT, ENG_FILTER */
	क्रम (i = 0; order[i].type != NVKM_SUBDEV_NR; i++) अणु
		अगर (!nvkm_device_subdev(dev, order[i].type, order[i].inst))
			जारी;

		nvkm_mask(dev, 0x20200 + order[i].offset, 0xff00, 0x4500);
	पूर्ण

	/* magic */
	nvkm_wr32(dev, 0x020288, therm->idle_filter->fecs);
	nvkm_wr32(dev, 0x02028c, therm->idle_filter->hubmmu);

	/* Enable घड़ीgating (ENG_CLK = RUN->AUTO) */
	क्रम (i = 0; order[i].type != NVKM_SUBDEV_NR; i++) अणु
		अगर (!nvkm_device_subdev(dev, order[i].type, order[i].inst))
			जारी;

		nvkm_mask(dev, 0x20200 + order[i].offset, 0x00ff, 0x0045);
	पूर्ण
पूर्ण

व्योम
gk104_clkgate_fini(काष्ठा nvkm_therm *base, bool suspend)
अणु
	काष्ठा gk104_therm *therm = gk104_therm(base);
	काष्ठा nvkm_device *dev = therm->base.subdev.device;
	स्थिर काष्ठा gk104_clkgate_engine_info *order = therm->clkgate_order;
	पूर्णांक i;

	/* ENG_CLK = AUTO->RUN, ENG_PWR = RUN->AUTO */
	क्रम (i = 0; order[i].type != NVKM_SUBDEV_NR; i++) अणु
		अगर (!nvkm_device_subdev(dev, order[i].type, order[i].inst))
			जारी;

		nvkm_mask(dev, 0x20200 + order[i].offset, 0xff, 0x54);
	पूर्ण
पूर्ण

स्थिर काष्ठा gk104_clkgate_engine_info gk104_clkgate_engine_info[] = अणु
	अणु NVKM_ENGINE_GR,     0, 0x00 पूर्ण,
	अणु NVKM_ENGINE_MSPDEC, 0, 0x04 पूर्ण,
	अणु NVKM_ENGINE_MSPPP,  0, 0x08 पूर्ण,
	अणु NVKM_ENGINE_MSVLD,  0, 0x0c पूर्ण,
	अणु NVKM_ENGINE_CE,     0, 0x10 पूर्ण,
	अणु NVKM_ENGINE_CE,     1, 0x14 पूर्ण,
	अणु NVKM_ENGINE_MSENC,  0, 0x18 पूर्ण,
	अणु NVKM_ENGINE_CE,     2, 0x1c पूर्ण,
	अणु NVKM_SUBDEV_NR पूर्ण,
पूर्ण;

स्थिर काष्ठा gf100_idle_filter gk104_idle_filter = अणु
	.fecs = 0x00001000,
	.hubmmu = 0x00001000,
पूर्ण;

अटल स्थिर काष्ठा nvkm_therm_func
gk104_therm_func = अणु
	.init = gf119_therm_init,
	.fini = g84_therm_fini,
	.pwm_ctrl = gf119_fan_pwm_ctrl,
	.pwm_get = gf119_fan_pwm_get,
	.pwm_set = gf119_fan_pwm_set,
	.pwm_घड़ी = gf119_fan_pwm_घड़ी,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_therm_fan_sense,
	.program_alarms = nvkm_therm_program_alarms_polling,
	.clkgate_init = gf100_clkgate_init,
	.clkgate_enable = gk104_clkgate_enable,
	.clkgate_fini = gk104_clkgate_fini,
पूर्ण;

अटल पूर्णांक
gk104_therm_new_(स्थिर काष्ठा nvkm_therm_func *func, काष्ठा nvkm_device *device,
		 क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		 स्थिर काष्ठा gk104_clkgate_engine_info *clkgate_order,
		 स्थिर काष्ठा gf100_idle_filter *idle_filter,
		 काष्ठा nvkm_therm **ptherm)
अणु
	काष्ठा gk104_therm *therm = kzalloc(माप(*therm), GFP_KERNEL);

	अगर (!therm)
		वापस -ENOMEM;

	nvkm_therm_ctor(&therm->base, device, type, inst, func);
	*ptherm = &therm->base;
	therm->clkgate_order = clkgate_order;
	therm->idle_filter = idle_filter;
	वापस 0;
पूर्ण

पूर्णांक
gk104_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_therm **ptherm)
अणु
	वापस gk104_therm_new_(&gk104_therm_func, device, type, inst,
				gk104_clkgate_engine_info, &gk104_idle_filter,
				ptherm);
पूर्ण
