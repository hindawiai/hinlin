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

अटल पूर्णांक
pwm_info(काष्ठा nvkm_therm *therm, पूर्णांक *line, पूर्णांक *ctrl, पूर्णांक *indx)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;

	अगर (*line == 0x04) अणु
		*ctrl = 0x00e100;
		*line = 4;
		*indx = 0;
	पूर्ण अन्यथा
	अगर (*line == 0x09) अणु
		*ctrl = 0x00e100;
		*line = 9;
		*indx = 1;
	पूर्ण अन्यथा
	अगर (*line == 0x10) अणु
		*ctrl = 0x00e28c;
		*line = 0;
		*indx = 0;
	पूर्ण अन्यथा अणु
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", *line);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
nv50_fan_pwm_ctrl(काष्ठा nvkm_therm *therm, पूर्णांक line, bool enable)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	u32 data = enable ? 0x00000001 : 0x00000000;
	पूर्णांक ctrl, id, ret = pwm_info(therm, &line, &ctrl, &id);
	अगर (ret == 0)
		nvkm_mask(device, ctrl, 0x00010001 << line, data << line);
	वापस ret;
पूर्ण

पूर्णांक
nv50_fan_pwm_get(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 *भागs, u32 *duty)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	पूर्णांक ctrl, id, ret = pwm_info(therm, &line, &ctrl, &id);
	अगर (ret)
		वापस ret;

	अगर (nvkm_rd32(device, ctrl) & (1 << line)) अणु
		*भागs = nvkm_rd32(device, 0x00e114 + (id * 8));
		*duty = nvkm_rd32(device, 0x00e118 + (id * 8));
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक
nv50_fan_pwm_set(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 भागs, u32 duty)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	पूर्णांक ctrl, id, ret = pwm_info(therm, &line, &ctrl, &id);
	अगर (ret)
		वापस ret;

	nvkm_wr32(device, 0x00e114 + (id * 8), भागs);
	nvkm_wr32(device, 0x00e118 + (id * 8), duty | 0x80000000);
	वापस 0;
पूर्ण

पूर्णांक
nv50_fan_pwm_घड़ी(काष्ठा nvkm_therm *therm, पूर्णांक line)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	पूर्णांक pwm_घड़ी;

	/* determine the PWM source घड़ी */
	अगर (device->chipset > 0x50 && device->chipset < 0x94) अणु
		u8 pwm_भाग = nvkm_rd32(device, 0x410c);
		अगर (nvkm_rd32(device, 0xc040) & 0x800000) अणु
			/* Use the HOST घड़ी (100 MHz)
			* Where करोes this स्थिरant(2.4) comes from? */
			pwm_घड़ी = (100000000 >> pwm_भाग) * 10 / 24;
		पूर्ण अन्यथा अणु
			/* Where करोes this स्थिरant(20) comes from? */
			pwm_घड़ी = (device->crystal * 1000) >> pwm_भाग;
			pwm_घड़ी /= 20;
		पूर्ण
	पूर्ण अन्यथा अणु
		pwm_घड़ी = (device->crystal * 1000) / 20;
	पूर्ण

	वापस pwm_घड़ी;
पूर्ण

अटल व्योम
nv50_sensor_setup(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	nvkm_mask(device, 0x20010, 0x40000000, 0x0);
	mdelay(20); /* रुको क्रम the temperature to stabilize */
पूर्ण

अटल पूर्णांक
nv50_temp_get(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvbios_therm_sensor *sensor = &therm->bios_sensor;
	पूर्णांक core_temp;

	core_temp = nvkm_rd32(device, 0x20014) & 0x3fff;

	/* अगर the slope or the offset is unset, करो no use the sensor */
	अगर (!sensor->slope_भाग || !sensor->slope_mult ||
	    !sensor->offset_num || !sensor->offset_den)
	    वापस -ENODEV;

	core_temp = core_temp * sensor->slope_mult / sensor->slope_भाग;
	core_temp = core_temp + sensor->offset_num / sensor->offset_den;
	core_temp = core_temp + sensor->offset_स्थिरant - 8;

	/* reserve negative temperatures क्रम errors */
	अगर (core_temp < 0)
		core_temp = 0;

	वापस core_temp;
पूर्ण

अटल व्योम
nv50_therm_init(काष्ठा nvkm_therm *therm)
अणु
	nv50_sensor_setup(therm);
पूर्ण

अटल स्थिर काष्ठा nvkm_therm_func
nv50_therm = अणु
	.init = nv50_therm_init,
	.पूर्णांकr = nv40_therm_पूर्णांकr,
	.pwm_ctrl = nv50_fan_pwm_ctrl,
	.pwm_get = nv50_fan_pwm_get,
	.pwm_set = nv50_fan_pwm_set,
	.pwm_घड़ी = nv50_fan_pwm_घड़ी,
	.temp_get = nv50_temp_get,
	.program_alarms = nvkm_therm_program_alarms_polling,
पूर्ण;

पूर्णांक
nv50_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_therm **ptherm)
अणु
	वापस nvkm_therm_new_(&nv50_therm, device, type, inst, ptherm);
पूर्ण
