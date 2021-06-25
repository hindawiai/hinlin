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
#समावेश "ramnv40.h"

पूर्णांक
nv44_ram_new(काष्ठा nvkm_fb *fb, काष्ठा nvkm_ram **pram)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	u32  size = nvkm_rd32(device, 0x10020c) & 0xff000000;
	u32 fb474 = nvkm_rd32(device, 0x100474);
	क्रमागत nvkm_ram_type type = NVKM_RAM_TYPE_UNKNOWN;

	अगर (fb474 & 0x00000004)
		type = NVKM_RAM_TYPE_GDDR3;
	अगर (fb474 & 0x00000002)
		type = NVKM_RAM_TYPE_DDR2;
	अगर (fb474 & 0x00000001)
		type = NVKM_RAM_TYPE_DDR1;

	वापस nv40_ram_new_(fb, type, size, pram);
पूर्ण
