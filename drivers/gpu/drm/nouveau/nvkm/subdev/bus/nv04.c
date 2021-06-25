<शैली गुरु>
/*
 * Copyright 2012 Nouveau Community
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
 * Authors: Martin Peres <martin.peres@labri.fr>
 *          Ben Skeggs
 */
#समावेश "priv.h"

#समावेश <subdev/gpपन.स>

अटल व्योम
nv04_bus_पूर्णांकr(काष्ठा nvkm_bus *bus)
अणु
	काष्ठा nvkm_subdev *subdev = &bus->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x001100) & nvkm_rd32(device, 0x001140);

	अगर (stat & 0x00000001) अणु
		nvkm_error(subdev, "BUS ERROR\n");
		stat &= ~0x00000001;
		nvkm_wr32(device, 0x001100, 0x00000001);
	पूर्ण

	अगर (stat & 0x00000110) अणु
		काष्ठा nvkm_gpio *gpio = device->gpio;
		अगर (gpio)
			nvkm_subdev_पूर्णांकr(&gpio->subdev);
		stat &= ~0x00000110;
		nvkm_wr32(device, 0x001100, 0x00000110);
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "intr %08x\n", stat);
		nvkm_mask(device, 0x001140, stat, 0x00000000);
	पूर्ण
पूर्ण

अटल व्योम
nv04_bus_init(काष्ठा nvkm_bus *bus)
अणु
	काष्ठा nvkm_device *device = bus->subdev.device;
	nvkm_wr32(device, 0x001100, 0xffffffff);
	nvkm_wr32(device, 0x001140, 0x00000111);
पूर्ण

अटल स्थिर काष्ठा nvkm_bus_func
nv04_bus = अणु
	.init = nv04_bus_init,
	.पूर्णांकr = nv04_bus_पूर्णांकr,
पूर्ण;

पूर्णांक
nv04_bus_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_bus **pbus)
अणु
	वापस nvkm_bus_new_(&nv04_bus, device, type, inst, pbus);
पूर्ण
