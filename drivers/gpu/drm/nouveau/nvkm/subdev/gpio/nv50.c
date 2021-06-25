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

व्योम
nv50_gpio_reset(काष्ठा nvkm_gpio *gpio, u8 match)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	u8 ver, len;
	u16 entry;
	पूर्णांक ent = -1;

	जबतक ((entry = dcb_gpio_entry(bios, 0, ++ent, &ver, &len))) अणु
		अटल स्थिर u32 regs[] = अणु 0xe100, 0xe28c पूर्ण;
		u32 data = nvbios_rd32(bios, entry);
		u8  line =   (data & 0x0000001f);
		u8  func =   (data & 0x0000ff00) >> 8;
		u8  defs = !!(data & 0x01000000);
		u8  unk0 = !!(data & 0x02000000);
		u8  unk1 = !!(data & 0x04000000);
		u32 val = (unk1 << 16) | unk0;
		u32 reg = regs[line >> 4];
		u32 lsh = line & 0x0f;

		अगर ( func  == DCB_GPIO_UNUSED ||
		    (match != DCB_GPIO_UNUSED && match != func))
			जारी;

		nvkm_gpio_set(gpio, 0, func, line, defs);

		nvkm_mask(device, reg, 0x00010001 << lsh, val << lsh);
	पूर्ण
पूर्ण

अटल पूर्णांक
nv50_gpio_location(पूर्णांक line, u32 *reg, u32 *shअगरt)
अणु
	स्थिर u32 nv50_gpio_reg[4] = अणु 0xe104, 0xe108, 0xe280, 0xe284 पूर्ण;

	अगर (line >= 32)
		वापस -EINVAL;

	*reg = nv50_gpio_reg[line >> 3];
	*shअगरt = (line & 7) << 2;
	वापस 0;
पूर्ण

पूर्णांक
nv50_gpio_drive(काष्ठा nvkm_gpio *gpio, पूर्णांक line, पूर्णांक dir, पूर्णांक out)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 reg, shअगरt;

	अगर (nv50_gpio_location(line, &reg, &shअगरt))
		वापस -EINVAL;

	nvkm_mask(device, reg, 3 << shअगरt, (((dir ^ 1) << 1) | out) << shअगरt);
	वापस 0;
पूर्ण

पूर्णांक
nv50_gpio_sense(काष्ठा nvkm_gpio *gpio, पूर्णांक line)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 reg, shअगरt;

	अगर (nv50_gpio_location(line, &reg, &shअगरt))
		वापस -EINVAL;

	वापस !!(nvkm_rd32(device, reg) & (4 << shअगरt));
पूर्ण

अटल व्योम
nv50_gpio_पूर्णांकr_stat(काष्ठा nvkm_gpio *gpio, u32 *hi, u32 *lo)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x00e054);
	u32 stat = nvkm_rd32(device, 0x00e050) & पूर्णांकr;
	*lo = (stat & 0xffff0000) >> 16;
	*hi = (stat & 0x0000ffff);
	nvkm_wr32(device, 0x00e054, पूर्णांकr);
पूर्ण

अटल व्योम
nv50_gpio_पूर्णांकr_mask(काष्ठा nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 पूर्णांकe = nvkm_rd32(device, 0x00e050);
	अगर (type & NVKM_GPIO_LO)
		पूर्णांकe = (पूर्णांकe & ~(mask << 16)) | (data << 16);
	अगर (type & NVKM_GPIO_HI)
		पूर्णांकe = (पूर्णांकe & ~mask) | data;
	nvkm_wr32(device, 0x00e050, पूर्णांकe);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpio_func
nv50_gpio = अणु
	.lines = 16,
	.पूर्णांकr_stat = nv50_gpio_पूर्णांकr_stat,
	.पूर्णांकr_mask = nv50_gpio_पूर्णांकr_mask,
	.drive = nv50_gpio_drive,
	.sense = nv50_gpio_sense,
	.reset = nv50_gpio_reset,
पूर्ण;

पूर्णांक
nv50_gpio_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_gpio **pgpio)
अणु
	वापस nvkm_gpio_new_(&nv50_gpio, device, type, inst, pgpio);
पूर्ण
