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

अटल पूर्णांक
pwm_info(काष्ठा nvkm_therm *therm, पूर्णांक line)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 gpio = nvkm_rd32(device, 0x00d610 + (line * 0x04));

	चयन (gpio & 0x000000c0) अणु
	हाल 0x00000000: /* normal mode, possibly pwm क्रमced off by us */
	हाल 0x00000040: /* nvio special */
		चयन (gpio & 0x0000001f) अणु
		हाल 0x00: वापस 2;
		हाल 0x19: वापस 1;
		हाल 0x1c: वापस 0;
		हाल 0x1e: वापस 2;
		शेष:
			अवरोध;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	nvkm_error(subdev, "GPIO %d unknown PWM: %08x\n", line, gpio);
	वापस -ENODEV;
पूर्ण

पूर्णांक
gf119_fan_pwm_ctrl(काष्ठा nvkm_therm *therm, पूर्णांक line, bool enable)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	u32 data = enable ? 0x00000040 : 0x00000000;
	पूर्णांक indx = pwm_info(therm, line);
	अगर (indx < 0)
		वापस indx;
	अन्यथा अगर (indx < 2)
		nvkm_mask(device, 0x00d610 + (line * 0x04), 0x000000c0, data);
	/* nothing to करो क्रम indx == 2, it seems hardwired to PTHERM */
	वापस 0;
पूर्ण

पूर्णांक
gf119_fan_pwm_get(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 *भागs, u32 *duty)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	पूर्णांक indx = pwm_info(therm, line);
	अगर (indx < 0)
		वापस indx;
	अन्यथा अगर (indx < 2) अणु
		अगर (nvkm_rd32(device, 0x00d610 + (line * 0x04)) & 0x00000040) अणु
			*भागs = nvkm_rd32(device, 0x00e114 + (indx * 8));
			*duty = nvkm_rd32(device, 0x00e118 + (indx * 8));
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (indx == 2) अणु
		*भागs = nvkm_rd32(device, 0x0200d8) & 0x1fff;
		*duty = nvkm_rd32(device, 0x0200dc) & 0x1fff;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

पूर्णांक
gf119_fan_pwm_set(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 भागs, u32 duty)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	पूर्णांक indx = pwm_info(therm, line);
	अगर (indx < 0)
		वापस indx;
	अन्यथा अगर (indx < 2) अणु
		nvkm_wr32(device, 0x00e114 + (indx * 8), भागs);
		nvkm_wr32(device, 0x00e118 + (indx * 8), duty | 0x80000000);
	पूर्ण अन्यथा अगर (indx == 2) अणु
		nvkm_mask(device, 0x0200d8, 0x1fff, भागs); /* keep the high bits */
		nvkm_wr32(device, 0x0200dc, duty | 0x40000000);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
gf119_fan_pwm_घड़ी(काष्ठा nvkm_therm *therm, पूर्णांक line)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	पूर्णांक indx = pwm_info(therm, line);
	अगर (indx < 0)
		वापस 0;
	अन्यथा अगर (indx < 2)
		वापस (device->crystal * 1000) / 20;
	अन्यथा
		वापस device->crystal * 1000 / 10;
पूर्ण

व्योम
gf119_therm_init(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;

	g84_sensor_setup(therm);

	/* enable fan tach, count revolutions per-second */
	nvkm_mask(device, 0x00e720, 0x00000003, 0x00000002);
	अगर (therm->fan->tach.func != DCB_GPIO_UNUSED) अणु
		nvkm_mask(device, 0x00d79c, 0x000000ff, therm->fan->tach.line);
		nvkm_wr32(device, 0x00e724, device->crystal * 1000);
		nvkm_mask(device, 0x00e720, 0x00000001, 0x00000001);
	पूर्ण
	nvkm_mask(device, 0x00e720, 0x00000002, 0x00000000);
पूर्ण

अटल स्थिर काष्ठा nvkm_therm_func
gf119_therm = अणु
	.init = gf119_therm_init,
	.fini = g84_therm_fini,
	.pwm_ctrl = gf119_fan_pwm_ctrl,
	.pwm_get = gf119_fan_pwm_get,
	.pwm_set = gf119_fan_pwm_set,
	.pwm_घड़ी = gf119_fan_pwm_घड़ी,
	.temp_get = g84_temp_get,
	.fan_sense = gt215_therm_fan_sense,
	.program_alarms = nvkm_therm_program_alarms_polling,
पूर्ण;

पूर्णांक
gf119_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_therm **ptherm)
अणु
	वापस nvkm_therm_new_(&gf119_therm, device, type, inst, ptherm);
पूर्ण
