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

अटल व्योम
gf100_bus_पूर्णांकr(काष्ठा nvkm_bus *bus)
अणु
	काष्ठा nvkm_subdev *subdev = &bus->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x001100) & nvkm_rd32(device, 0x001140);

	अगर (stat & 0x0000000e) अणु
		u32 addr = nvkm_rd32(device, 0x009084);
		u32 data = nvkm_rd32(device, 0x009088);

		nvkm_error(subdev,
			   "MMIO %s of %08x FAULT at %06x [ %s%s%s]\n",
			   (addr & 0x00000002) ? "write" : "read", data,
			   (addr & 0x00fffffc),
			   (stat & 0x00000002) ? "!ENGINE " : "",
			   (stat & 0x00000004) ? "PRIVRING " : "",
			   (stat & 0x00000008) ? "TIMEOUT " : "");

		nvkm_wr32(device, 0x009084, 0x00000000);
		nvkm_wr32(device, 0x001100, (stat & 0x0000000e));
		stat &= ~0x0000000e;
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "intr %08x\n", stat);
		nvkm_mask(device, 0x001140, stat, 0x00000000);
	पूर्ण
पूर्ण

अटल व्योम
gf100_bus_init(काष्ठा nvkm_bus *bus)
अणु
	काष्ठा nvkm_device *device = bus->subdev.device;
	nvkm_wr32(device, 0x001100, 0xffffffff);
	nvkm_wr32(device, 0x001140, 0x0000000e);
पूर्ण

अटल स्थिर काष्ठा nvkm_bus_func
gf100_bus = अणु
	.init = gf100_bus_init,
	.पूर्णांकr = gf100_bus_पूर्णांकr,
पूर्ण;

पूर्णांक
gf100_bus_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_bus **pbus)
अणु
	वापस nvkm_bus_new_(&gf100_bus, device, type, inst, pbus);
पूर्ण
