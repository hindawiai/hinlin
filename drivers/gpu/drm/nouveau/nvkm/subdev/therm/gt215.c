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
 */
#समावेश "priv.h"

#समावेश <subdev/gpपन.स>

पूर्णांक
gt215_therm_fan_sense(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	u32 tach = nvkm_rd32(device, 0x00e728) & 0x0000ffff;
	u32 ctrl = nvkm_rd32(device, 0x00e720);
	अगर (ctrl & 0x00000001)
		वापस tach * 60 / 2;
	वापस -ENODEV;
पूर्ण

अटल व्योम
gt215_therm_init(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा dcb_gpio_func *tach = &therm->fan->tach;

	g84_sensor_setup(therm);

	/* enable fan tach, count revolutions per-second */
	nvkm_mask(device, 0x00e720, 0x00000003, 0x00000002);
	अगर (tach->func != DCB_GPIO_UNUSED) अणु
		nvkm_wr32(device, 0x00e724, device->crystal * 1000);
		nvkm_mask(device, 0x00e720, 0x001f0000, tach->line << 16);
		nvkm_mask(device, 0x00e720, 0x00000001, 0x00000001);
	पूर्ण
	nvkm_mask(device, 0x00e720, 0x00000002, 0x00000000);
पूर्ण

अटल स्थिर काष्ठा nvkm_therm_func
gt215_therm = अणु
	.init = gt215_therm_init,
	.fini = g84_therm_fini,
	.pwm_ctrl = nv50_fan_pwm_ctrl,
	.pwm_get = nv50_fan_pwm_get,
	.pwm_set = nv50_fan_pwm_set,
	.pwm_घड़ी = nv50_fan_pwm_घड़ी,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_therm_fan_sense,
	.program_alarms = nvkm_therm_program_alarms_polling,
पूर्ण;

पूर्णांक
gt215_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_therm **ptherm)
अणु
	वापस nvkm_therm_new_(&gt215_therm, device, type, inst, ptherm);
पूर्ण
