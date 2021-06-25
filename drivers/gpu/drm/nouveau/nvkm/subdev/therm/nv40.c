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

क्रमागत nv40_sensor_style अणु INVALID_STYLE = -1, OLD_STYLE = 0, NEW_STYLE = 1 पूर्ण;

अटल क्रमागत nv40_sensor_style
nv40_sensor_style(काष्ठा nvkm_therm *therm)
अणु
	चयन (therm->subdev.device->chipset) अणु
	हाल 0x43:
	हाल 0x44:
	हाल 0x4a:
	हाल 0x47:
		वापस OLD_STYLE;
	हाल 0x46:
	हाल 0x49:
	हाल 0x4b:
	हाल 0x4e:
	हाल 0x4c:
	हाल 0x67:
	हाल 0x68:
	हाल 0x63:
		वापस NEW_STYLE;
	शेष:
		वापस INVALID_STYLE;
	पूर्ण
पूर्ण

अटल पूर्णांक
nv40_sensor_setup(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	क्रमागत nv40_sensor_style style = nv40_sensor_style(therm);

	/* enable ADC पढ़ोout and disable the ALARM threshold */
	अगर (style == NEW_STYLE) अणु
		nvkm_mask(device, 0x15b8, 0x80000000, 0);
		nvkm_wr32(device, 0x15b0, 0x80003fff);
		mdelay(20); /* रुको क्रम the temperature to stabilize */
		वापस nvkm_rd32(device, 0x15b4) & 0x3fff;
	पूर्ण अन्यथा अगर (style == OLD_STYLE) अणु
		nvkm_wr32(device, 0x15b0, 0xff);
		mdelay(20); /* रुको क्रम the temperature to stabilize */
		वापस nvkm_rd32(device, 0x15b4) & 0xff;
	पूर्ण अन्यथा
		वापस -ENODEV;
पूर्ण

अटल पूर्णांक
nv40_temp_get(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvbios_therm_sensor *sensor = &therm->bios_sensor;
	क्रमागत nv40_sensor_style style = nv40_sensor_style(therm);
	पूर्णांक core_temp;

	अगर (style == NEW_STYLE) अणु
		nvkm_wr32(device, 0x15b0, 0x80003fff);
		core_temp = nvkm_rd32(device, 0x15b4) & 0x3fff;
	पूर्ण अन्यथा अगर (style == OLD_STYLE) अणु
		nvkm_wr32(device, 0x15b0, 0xff);
		core_temp = nvkm_rd32(device, 0x15b4) & 0xff;
	पूर्ण अन्यथा
		वापस -ENODEV;

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

अटल पूर्णांक
nv40_fan_pwm_ctrl(काष्ठा nvkm_therm *therm, पूर्णांक line, bool enable)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mask = enable ? 0x80000000 : 0x00000000;
	अगर      (line == 2) nvkm_mask(device, 0x0010f0, 0x80000000, mask);
	अन्यथा अगर (line == 9) nvkm_mask(device, 0x0015f4, 0x80000000, mask);
	अन्यथा अणु
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", line);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
nv40_fan_pwm_get(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 *भागs, u32 *duty)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अगर (line == 2) अणु
		u32 reg = nvkm_rd32(device, 0x0010f0);
		अगर (reg & 0x80000000) अणु
			*duty = (reg & 0x7fff0000) >> 16;
			*भागs = (reg & 0x00007fff);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा
	अगर (line == 9) अणु
		u32 reg = nvkm_rd32(device, 0x0015f4);
		अगर (reg & 0x80000000) अणु
			*भागs = nvkm_rd32(device, 0x0015f8);
			*duty = (reg & 0x7fffffff);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", line);
		वापस -ENODEV;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nv40_fan_pwm_set(काष्ठा nvkm_therm *therm, पूर्णांक line, u32 भागs, u32 duty)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अगर (line == 2) अणु
		nvkm_mask(device, 0x0010f0, 0x7fff7fff, (duty << 16) | भागs);
	पूर्ण अन्यथा
	अगर (line == 9) अणु
		nvkm_wr32(device, 0x0015f8, भागs);
		nvkm_mask(device, 0x0015f4, 0x7fffffff, duty);
	पूर्ण अन्यथा अणु
		nvkm_error(subdev, "unknown pwm ctrl for gpio %d\n", line);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
nv40_therm_पूर्णांकr(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	uपूर्णांक32_t stat = nvkm_rd32(device, 0x1100);

	/* traitement */

	/* ack all IRQs */
	nvkm_wr32(device, 0x1100, 0x70000);

	nvkm_error(subdev, "THERM received an IRQ: stat = %x\n", stat);
पूर्ण

अटल व्योम
nv40_therm_init(काष्ठा nvkm_therm *therm)
अणु
	nv40_sensor_setup(therm);
पूर्ण

अटल स्थिर काष्ठा nvkm_therm_func
nv40_therm = अणु
	.init = nv40_therm_init,
	.पूर्णांकr = nv40_therm_पूर्णांकr,
	.pwm_ctrl = nv40_fan_pwm_ctrl,
	.pwm_get = nv40_fan_pwm_get,
	.pwm_set = nv40_fan_pwm_set,
	.temp_get = nv40_temp_get,
	.program_alarms = nvkm_therm_program_alarms_polling,
पूर्ण;

पूर्णांक
nv40_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_therm **ptherm)
अणु
	वापस nvkm_therm_new_(&nv40_therm, device, type, inst, ptherm);
पूर्ण
