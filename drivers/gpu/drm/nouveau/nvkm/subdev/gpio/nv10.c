<शैली गुरु>
/*
 * Copyright (C) 2009 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश "priv.h"

अटल पूर्णांक
nv10_gpio_sense(काष्ठा nvkm_gpio *gpio, पूर्णांक line)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	अगर (line < 2) अणु
		line = line * 16;
		line = nvkm_rd32(device, 0x600818) >> line;
		वापस !!(line & 0x0100);
	पूर्ण अन्यथा
	अगर (line < 10) अणु
		line = (line - 2) * 4;
		line = nvkm_rd32(device, 0x60081c) >> line;
		वापस !!(line & 0x04);
	पूर्ण अन्यथा
	अगर (line < 14) अणु
		line = (line - 10) * 4;
		line = nvkm_rd32(device, 0x600850) >> line;
		वापस !!(line & 0x04);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nv10_gpio_drive(काष्ठा nvkm_gpio *gpio, पूर्णांक line, पूर्णांक dir, पूर्णांक out)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 reg, mask, data;

	अगर (line < 2) अणु
		line = line * 16;
		reg  = 0x600818;
		mask = 0x00000011;
		data = (dir << 4) | out;
	पूर्ण अन्यथा
	अगर (line < 10) अणु
		line = (line - 2) * 4;
		reg  = 0x60081c;
		mask = 0x00000003;
		data = (dir << 1) | out;
	पूर्ण अन्यथा
	अगर (line < 14) अणु
		line = (line - 10) * 4;
		reg  = 0x600850;
		mask = 0x00000003;
		data = (dir << 1) | out;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	nvkm_mask(device, reg, mask << line, data << line);
	वापस 0;
पूर्ण

अटल व्योम
nv10_gpio_पूर्णांकr_stat(काष्ठा nvkm_gpio *gpio, u32 *hi, u32 *lo)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x001104);
	u32 stat = nvkm_rd32(device, 0x001144) & पूर्णांकr;
	*lo = (stat & 0xffff0000) >> 16;
	*hi = (stat & 0x0000ffff);
	nvkm_wr32(device, 0x001104, पूर्णांकr);
पूर्ण

अटल व्योम
nv10_gpio_पूर्णांकr_mask(काष्ठा nvkm_gpio *gpio, u32 type, u32 mask, u32 data)
अणु
	काष्ठा nvkm_device *device = gpio->subdev.device;
	u32 पूर्णांकe = nvkm_rd32(device, 0x001144);
	अगर (type & NVKM_GPIO_LO)
		पूर्णांकe = (पूर्णांकe & ~(mask << 16)) | (data << 16);
	अगर (type & NVKM_GPIO_HI)
		पूर्णांकe = (पूर्णांकe & ~mask) | data;
	nvkm_wr32(device, 0x001144, पूर्णांकe);
पूर्ण

अटल स्थिर काष्ठा nvkm_gpio_func
nv10_gpio = अणु
	.lines = 16,
	.पूर्णांकr_stat = nv10_gpio_पूर्णांकr_stat,
	.पूर्णांकr_mask = nv10_gpio_पूर्णांकr_mask,
	.drive = nv10_gpio_drive,
	.sense = nv10_gpio_sense,
पूर्ण;

पूर्णांक
nv10_gpio_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_gpio **pgpio)
अणु
	वापस nvkm_gpio_new_(&nv10_gpio, device, type, inst, pgpio);
पूर्ण
