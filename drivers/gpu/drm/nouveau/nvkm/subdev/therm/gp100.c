<शैली गुरु>
/*
 * Copyright 2017 Rhys Kidd
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
 * Authors: Rhys Kidd
 */
#समावेश "priv.h"

अटल पूर्णांक
gp100_temp_get(काष्ठा nvkm_therm *therm)
अणु
	काष्ठा nvkm_device *device = therm->subdev.device;
	काष्ठा nvkm_subdev *subdev = &therm->subdev;
	u32 tsensor = nvkm_rd32(device, 0x020460);
	u32 पूर्णांकtemp = (tsensor & 0x0001fff8);

	/* device SHADOWed */
	अगर (tsensor & 0x40000000)
		nvkm_trace(subdev, "reading temperature from SHADOWed sensor\n");

	/* device valid */
	अगर (tsensor & 0x20000000)
		वापस (पूर्णांकtemp >> 8);
	अन्यथा
		वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा nvkm_therm_func
gp100_therm = अणु
	.temp_get = gp100_temp_get,
	.program_alarms = nvkm_therm_program_alarms_polling,
पूर्ण;

पूर्णांक
gp100_therm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_therm **ptherm)
अणु
	वापस nvkm_therm_new_(&gp100_therm, device, type, inst, ptherm);
पूर्ण
