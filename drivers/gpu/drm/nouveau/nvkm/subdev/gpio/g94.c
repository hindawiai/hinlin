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
g94_gpio_पूर्णांकr_stat(काष्ठा nvkm_gpio *gpio, u32 *hi, u32 *lo)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 पूर्णांकr0 = nvkm_rd32(device, 0x00e054);
	u32 पूर्णांकr1 = nvkm_rd32(device, 0x00e074);
	u32 stat0 = nvkm_rd32(device, 0x00e050) & पूर्णांकr0;
	u32 stat1 = nvkm_rd32(device, 0x00e070) & पूर्णांकr1;
	*lo = (stat1 & 0xffff0000) | (stat0 >> 16);
	*hi = (stat1 << 16) | (stat0 & 0x0000ffff);
	nvkm_wr32(device, 0x00e054, पूर्णांकr0);
	nvkm_wr32(device, 0x00e074, पूर्णांकr1);
पूर्ण

व्योम
g94_gpio_पूर्णांकr_mask(काष्ठा nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 पूर्णांकe0 = nvkm_rd32(device, 0x00e050);
	u32 पूर्णांकe1 = nvkm_rd32(device, 0x00e070);
	अगर (type & NVKM_GPIO_LO)
		पूर्णांकe0 = (पूर्णांकe0 & ~(mask << 16)) | (data << 16);
	अगर (type & NVKM_GPIO_HI)
		पूर्णांकe0 = (पूर्णांकe0 & ~(mask & 0xffff)) | (data & 0xffff);
	mask >>= 16;
	data >>= 16;
	अगर (type & NVKM_GPIO_LO)
		पूर्णांकe1 = (पूर्णांकe1 & ~(mask << 16)) | (data << 16);
	अगर (type & NVKM_GPIO_HI)
		पूर्णांकe1 = (पूर्णांकe1 & ~mask) | data;
	nvkm_wr32(device, 0x00e050, पूर्णांकe0);
	nvkm_wr32(device, 0x00e070, पूर्णांकe1);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpio_func
g94_gpio = अणु
	.lines = 32,
	.पूर्णांकr_stat = g94_gpio_पूर्णांकr_stat,
	.पूर्णांकr_mask = g94_gpio_पूर्णांकr_mask,
	.drive = nv50_gpio_drive,
	.sense = nv50_gpio_sense,
	.reset = nv50_gpio_reset,
पूर्ण;

पूर्णांक
g94_gpio_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_gpio **pgpio)
अणु
	वापस nvkm_gpio_new_(&g94_gpio, device, type, inst, pgpio);
पूर्ण
