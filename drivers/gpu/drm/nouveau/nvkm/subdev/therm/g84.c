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

#समावेश <subdev/fuse.h>

पूर्णांक
g84_temp_get(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;

	अगर (nvkm_fuse_पढ़ो(device->fuse, 0x1a8) == 1)
		वापस nvkm_rd32(device, 0x20400);
	अन्यथा
		वापस -ENODEV;
पूर्ण

व्योम
g84_sensor_setup(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;

	/* enable temperature पढ़ोing क्रम cards with insane शेषs */
	अगर (nvkm_fuse_पढ़ो(device->fuse, 0x1a8) == 1) अणु
		nvkm_mask(device, 0x20008, 0x80008000, 0x80000000);
		nvkm_mask(device, 0x2000c, 0x80000003, 0x00000000);
		mdelay(20); /* रुको क्रम the temperature to stabilize */
	पूर्ण
पूर्ण

अटल व्योम
g84_therm_program_alarms(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvbios_therm_sensor *sensor = &therm->bios_sensor;
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&therm->sensor.alarm_program_lock, flags);

	/* enable RISING and FALLING IRQs क्रम shutकरोwn, THRS 0, 1, 2 and 4 */
	nvkm_wr32(device, 0x20000, 0x000003ff);

	/* shutकरोwn: The computer should be shutकरोwn when reached */
	nvkm_wr32(device, 0x20484, sensor->thrs_shutकरोwn.hysteresis);
	nvkm_wr32(device, 0x20480, sensor->thrs_shutकरोwn.temp);

	/* THRS_1 : fan boost*/
	nvkm_wr32(device, 0x204c4, sensor->thrs_fan_boost.temp);

	/* THRS_2 : critical */
	nvkm_wr32(device, 0x204c0, sensor->thrs_critical.temp);

	/* THRS_4 : करोwn घड़ी */
	nvkm_wr32(device, 0x20414, sensor->thrs_करोwn_घड़ी.temp);
	spin_unlock_irqrestore(&therm->sensor.alarm_program_lock, flags);

	nvkm_debug(subdev,
		   "Programmed thresholds [ %d(%d), %d(%d), %d(%d), %d(%d) ]\n",
		   sensor->thrs_fan_boost.temp,
		   sensor->thrs_fan_boost.hysteresis,
		   sensor->thrs_करोwn_घड़ी.temp,
		   sensor->thrs_करोwn_घड़ी.hysteresis,
		   sensor->thrs_critical.temp,
		   sensor->thrs_critical.hysteresis,
		   sensor->thrs_shutकरोwn.temp,
		   sensor->thrs_shutकरोwn.hysteresis);

पूर्ण

/* must be called with alarm_program_lock taken ! */
अटल व्योम
g84_therm_threshold_hyst_emulation(काष्ठा nvkm_therm *therm,
				   uपूर्णांक32_t thrs_reg, u8 status_bit,
				   स्थिर काष्ठा nvbios_therm_threshold *thrs,
				   क्रमागत nvkm_therm_thrs thrs_name)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	क्रमागत nvkm_therm_thrs_direction direction;
	क्रमागत nvkm_therm_thrs_state prev_state, new_state;
	पूर्णांक temp, cur;

	prev_state = nvkm_therm_sensor_get_threshold_state(therm, thrs_name);
	temp = nvkm_rd32(device, thrs_reg);

	/* program the next threshold */
	अगर (temp == thrs->temp) अणु
		nvkm_wr32(device, thrs_reg, thrs->temp - thrs->hysteresis);
		new_state = NVKM_THERM_THRS_HIGHER;
	पूर्ण अन्यथा अणु
		nvkm_wr32(device, thrs_reg, thrs->temp);
		new_state = NVKM_THERM_THRS_LOWER;
	पूर्ण

	/* fix the state (in हाल someone reprogrammed the alarms) */
	cur = therm->func->temp_get(therm);
	अगर (new_state == NVKM_THERM_THRS_LOWER && cur > thrs->temp)
		new_state = NVKM_THERM_THRS_HIGHER;
	अन्यथा अगर (new_state == NVKM_THERM_THRS_HIGHER &&
		cur < thrs->temp - thrs->hysteresis)
		new_state = NVKM_THERM_THRS_LOWER;
	nvkm_therm_sensor_set_threshold_state(therm, thrs_name, new_state);

	/* find the direction */
	अगर (prev_state < new_state)
		direction = NVKM_THERM_THRS_RISING;
	अन्यथा अगर (prev_state > new_state)
		direction = NVKM_THERM_THRS_FALLING;
	अन्यथा
		वापस;

	/* advertise a change in direction */
	nvkm_therm_sensor_event(therm, thrs_name, direction);
पूर्ण

अटल व्योम
g84_therm_पूर्णांकr(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvbios_therm_sensor *sensor = &therm->bios_sensor;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t पूर्णांकr;

	spin_lock_irqsave(&therm->sensor.alarm_program_lock, flags);

	पूर्णांकr = nvkm_rd32(device, 0x20100) & 0x3ff;

	/* THRS_4: करोwnघड़ी */
	अगर (पूर्णांकr & 0x002) अणु
		g84_therm_threshold_hyst_emulation(therm, 0x20414, 24,
						   &sensor->thrs_करोwn_घड़ी,
						   NVKM_THERM_THRS_DOWNCLOCK);
		पूर्णांकr &= ~0x002;
	पूर्ण

	/* shutकरोwn */
	अगर (पूर्णांकr & 0x004) अणु
		g84_therm_threshold_hyst_emulation(therm, 0x20480, 20,
						   &sensor->thrs_shutकरोwn,
						   NVKM_THERM_THRS_SHUTDOWN);
		पूर्णांकr &= ~0x004;
	पूर्ण

	/* THRS_1 : fan boost */
	अगर (पूर्णांकr & 0x008) अणु
		g84_therm_threshold_hyst_emulation(therm, 0x204c4, 21,
						   &sensor->thrs_fan_boost,
						   NVKM_THERM_THRS_FANBOOST);
		पूर्णांकr &= ~0x008;
	पूर्ण

	/* THRS_2 : critical */
	अगर (पूर्णांकr & 0x010) अणु
		g84_therm_threshold_hyst_emulation(therm, 0x204c0, 22,
						   &sensor->thrs_critical,
						   NVKM_THERM_THRS_CRITICAL);
		पूर्णांकr &= ~0x010;
	पूर्ण

	अगर (पूर्णांकr)
		nvkm_error(subdev, "intr %08x\n", पूर्णांकr);

	/* ACK everything */
	nvkm_wr32(device, 0x20100, 0xffffffff);
	nvkm_wr32(device, 0x1100, 0x10000); /* PBUS */

	spin_unlock_irqrestore(&therm->sensor.alarm_program_lock, flags);
पूर्ण

व्योम
g84_therm_fini(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;

	/* Disable PTherm IRQs */
	nvkm_wr32(device, 0x20000, 0x00000000);

	/* ACK all PTherm IRQs */
	nvkm_wr32(device, 0x20100, 0xffffffff);
	nvkm_wr32(device, 0x1100, 0x10000); /* PBUS */
पूर्ण

व्योम
g84_therm_init(काष्ठा nvkm_therm *therm)
अणु
	g84_sensor_setup(therm);
पूर्ण

अटल स्थिर काष्ठा nvkm_therm_func
g84_therm = अणु
	.init = g84_therm_init,
	.fini = g84_therm_fini,
	.पूर्णांकr = g84_therm_पूर्णांकr,
	.pwm_ctrl = nv50_fan_pwm_ctrl,
	.pwm_get = nv50_fan_pwm_get,
	.pwm_set = nv50_fan_pwm_set,
	.pwm_घड़ी = nv50_fan_pwm_घड़ी,
	.temp_get = g84_temp_get,
	.program_alarms = g84_therm_program_alarms,
पूर्ण;

पूर्णांक
g84_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_therm **ptherm)
अणु
	काष्ठा nvkm_therm *therm;
	पूर्णांक ret;

	ret = nvkm_therm_new_(&g84_therm, device, type, inst, &therm);
	*ptherm = therm;
	अगर (ret)
		वापस ret;

	/* init the thresholds */
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_SHUTDOWN,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_FANBOOST,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_CRITICAL,
						     NVKM_THERM_THRS_LOWER);
	nvkm_therm_sensor_set_threshold_state(therm, NVKM_THERM_THRS_DOWNCLOCK,
						     NVKM_THERM_THRS_LOWER);
	वापस 0;
पूर्ण
