<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#समावेश "ram.h"
#समावेश "regsnv04.h"

स्थिर काष्ठा nvkm_ram_func
nv04_ram_func = अणु
पूर्ण;

पूर्णांक
nv04_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	u32 boot0 = nvkm_rd32(device, NV04_PFB_BOOT_0);
	u64 size;
	क्रमागत nvkm_ram_type type;

	अगर (boot0 & 0x00000100) अणु
		size  = ((boot0 >> 12) & 0xf) * 2 + 2;
		size *= 1024 * 1024;
	पूर्ण अन्यथा अणु
		चयन (boot0 & NV04_PFB_BOOT_0_RAM_AMOUNT) अणु
		हाल NV04_PFB_BOOT_0_RAM_AMOUNT_32MB:
			size = 32 * 1024 * 1024;
			अवरोध;
		हाल NV04_PFB_BOOT_0_RAM_AMOUNT_16MB:
			size = 16 * 1024 * 1024;
			अवरोध;
		हाल NV04_PFB_BOOT_0_RAM_AMOUNT_8MB:
			size = 8 * 1024 * 1024;
			अवरोध;
		हाल NV04_PFB_BOOT_0_RAM_AMOUNT_4MB:
			size = 4 * 1024 * 1024;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर ((boot0 & 0x00000038) <= 0x10)
		type = NVKM_RAM_TYPE_SGRAM;
	अन्यथा
		type = NVKM_RAM_TYPE_SDRAM;

	वापस nvkm_ram_new_(&nv04_ram_func, fb, type, size, pram);
पूर्ण
