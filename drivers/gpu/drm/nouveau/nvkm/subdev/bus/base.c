<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "priv.h"

अटल व्योम
nvkm_bus_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_bus *bus = nvkm_bus(subdev);
	bus->func->पूर्णांकr(bus);
पूर्ण

अटल पूर्णांक
nvkm_bus_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_bus *bus = nvkm_bus(subdev);
	bus->func->init(bus);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_bus_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	वापस nvkm_bus(subdev);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_bus = अणु
	.dtor = nvkm_bus_dtor,
	.init = nvkm_bus_init,
	.पूर्णांकr = nvkm_bus_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_bus_new_(स्थिर काष्ठा nvkm_bus_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_bus **pbus)
अणु
	काष्ठा nvkm_bus *bus;
	अगर (!(bus = *pbus = kzalloc(माप(*bus), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_subdev_ctor(&nvkm_bus, device, type, inst, &bus->subdev);
	bus->func = func;
	वापस 0;
पूर्ण
