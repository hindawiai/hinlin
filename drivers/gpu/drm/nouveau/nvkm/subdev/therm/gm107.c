<शैली गुरु>
/*
 * Copyright 2014 Martin Peres
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

अटल पूर्णांक
gm107_fan_pwm_ctrl(काष्ठा nvkm_therm *therm, पूर्णांक line, bool enable)
अणु
	/* nothing to करो, it seems hardwired */
	वापस 0;
पूर्ण

अटल पूर्णांक
gm107_fan_pwm_get(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 *भागs, u32 *duty)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	*भागs = nvkm_rd32(device, 0x10eb20) & 0x1fff;
	*duty = nvkm_rd32(device, 0x10eb24) & 0x1fff;
	वापस 0;
पूर्ण

अटल पूर्णांक
gm107_fan_pwm_set(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 भागs, u32 duty)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	nvkm_mask(device, 0x10eb10, 0x1fff, भागs); /* keep the high bits */
	nvkm_wr32(device, 0x10eb14, duty | 0x80000000);
	वापस 0;
पूर्ण

अटल पूर्णांक
gm107_fan_pwm_घड़ी(काष्ठा nvkm_therm *therm, पूर्णांक line)
अणु
	वापस therm->subdev.device->crystal * 1000;
पूर्ण

अटल स्थिर काष्ठा nvkm_therm_func
gm107_therm = अणु
	.init = gf119_therm_init,
	.fini = g84_therm_fini,
	.pwm_ctrl = gm107_fan_pwm_ctrl,
	.pwm_get = gm107_fan_pwm_get,
	.pwm_set = gm107_fan_pwm_set,
	.pwm_घड़ी = gm107_fan_pwm_घड़ी,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_therm_fan_sense,
	.program_alarms = nvkm_therm_program_alarms_polling,
पूर्ण;

पूर्णांक
gm107_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_therm **ptherm)
अणु
	वापस nvkm_therm_new_(&gm107_therm, device, type, inst, ptherm);
पूर्ण
