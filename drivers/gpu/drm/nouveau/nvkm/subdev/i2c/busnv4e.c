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
 * all copies or substantial busions of the Software.
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
#घोषणा nv4e_i2c_bus(p) container_of((p), काष्ठा nv4e_i2c_bus, base)
#समावेश "bus.h"

काष्ठा nv4e_i2c_bus अणु
	काष्ठा nvkm_i2c_bus base;
	u32 addr;
पूर्ण;

अटल व्योम
nv4e_i2c_bus_drive_scl(काष्ठा nvkm_i2c_bus *base, पूर्णांक state)
अणु
	काष्ठा nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	काष्ठा nvkm_device *device = bus->base.pad->i2c->subdev.device;
	nvkm_mask(device, bus->addr, 0x2f, state ? 0x21 : 0x01);
पूर्ण

अटल व्योम
nv4e_i2c_bus_drive_sda(काष्ठा nvkm_i2c_bus *base, पूर्णांक state)
अणु
	काष्ठा nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	काष्ठा nvkm_device *device = bus->base.pad->i2c->subdev.device;
	nvkm_mask(device, bus->addr, 0x1f, state ? 0x11 : 0x01);
पूर्ण

अटल पूर्णांक
nv4e_i2c_bus_sense_scl(काष्ठा nvkm_i2c_bus *base)
अणु
	काष्ठा nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	काष्ठा nvkm_device *device = bus->base.pad->i2c->subdev.device;
	वापस !!(nvkm_rd32(device, bus->addr) & 0x00040000);
पूर्ण

अटल पूर्णांक
nv4e_i2c_bus_sense_sda(काष्ठा nvkm_i2c_bus *base)
अणु
	काष्ठा nv4e_i2c_bus *bus = nv4e_i2c_bus(base);
	काष्ठा nvkm_device *device = bus->base.pad->i2c->subdev.device;
	वापस !!(nvkm_rd32(device, bus->addr) & 0x00080000);
पूर्ण

अटल स्थिर काष्ठा nvkm_i2c_bus_func
nv4e_i2c_bus_func = अणु
	.drive_scl = nv4e_i2c_bus_drive_scl,
	.drive_sda = nv4e_i2c_bus_drive_sda,
	.sense_scl = nv4e_i2c_bus_sense_scl,
	.sense_sda = nv4e_i2c_bus_sense_sda,
	.xfer = nvkm_i2c_bit_xfer,
पूर्ण;

पूर्णांक
nv4e_i2c_bus_new(काष्ठा nvkm_i2c_pad *pad, पूर्णांक id, u8 drive,
		 काष्ठा nvkm_i2c_bus **pbus)
अणु
	काष्ठा nv4e_i2c_bus *bus;

	अगर (!(bus = kzalloc(माप(*bus), GFP_KERNEL)))
		वापस -ENOMEM;
	*pbus = &bus->base;

	nvkm_i2c_bus_ctor(&nv4e_i2c_bus_func, pad, id, &bus->base);
	bus->addr = 0x600800 + drive;
	वापस 0;
पूर्ण
