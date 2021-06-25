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
gf119_gpio_reset(काष्ठा nvkm_gpio *gpio, u8 match)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	काष्ठा nvkm_bios *bios = device->bios;
	u8 ver, len;
	u16 entry;
	पूर्णांक ent = -1;

	जबतक ((entry = dcb_gpio_entry(bios, 0, ++ent, &ver, &len))) अणु
		u32 data = nvbios_rd32(bios, entry);
		u8  line =   (data & 0x0000003f);
		u8  defs = !!(data & 0x00000080);
		u8  func =   (data & 0x0000ff00) >> 8;
		u8  unk0 =   (data & 0x00ff0000) >> 16;
		u8  unk1 =   (data & 0x1f000000) >> 24;

		अगर ( func  == DCB_GPIO_UNUSED ||
		    (match != DCB_GPIO_UNUSED && match != func))
			जारी;

		nvkm_gpio_set(gpio, 0, func, line, defs);

		nvkm_mask(device, 0x00d610 + (line * 4), 0xff, unk0);
		अगर (unk1--)
			nvkm_mask(device, 0x00d740 + (unk1 * 4), 0xff, line);
	पूर्ण
पूर्ण

पूर्णांक
gf119_gpio_drive(काष्ठा nvkm_gpio *gpio, पूर्णांक line, पूर्णांक dir, पूर्णांक out)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 data = ((dir ^ 1) << 13) | (out << 12);
	nvkm_mask(device, 0x00d610 + (line * 4), 0x00003000, data);
	nvkm_mask(device, 0x00d604, 0x00000001, 0x00000001); /* update? */
	वापस 0;
पूर्ण

पूर्णांक
gf119_gpio_sense(काष्ठा nvkm_gpio *gpio, पूर्णांक line)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	वापस !!(nvkm_rd32(device, 0x00d610 + (line * 4)) & 0x00004000);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpio_func
gf119_gpio = अणु
	.lines = 32,
	.पूर्णांकr_stat = g94_gpio_पूर्णांकr_stat,
	.पूर्णांकr_mask = g94_gpio_पूर्णांकr_mask,
	.drive = gf119_gpio_drive,
	.sense = gf119_gpio_sense,
	.reset = gf119_gpio_reset,
पूर्ण;

पूर्णांक
gf119_gpio_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_gpio **pgpio)
अणु
	वापस nvkm_gpio_new_(&gf119_gpio, device, type, inst, pgpio);
पूर्ण
