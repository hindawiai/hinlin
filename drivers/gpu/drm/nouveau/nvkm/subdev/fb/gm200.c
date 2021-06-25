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
#समावेश "gf100.h"
#समावेश "ram.h"

#समावेश <core/memory.h>

पूर्णांक
gm200_fb_init_page(काष्ठा nvkm_fb *fb)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	चयन (fb->page) अणु
	हाल 16: nvkm_mask(device, 0x100c80, 0x00001801, 0x00001001); अवरोध;
	हाल 17: nvkm_mask(device, 0x100c80, 0x00001801, 0x00000000); अवरोध;
	हाल  0: nvkm_mask(device, 0x100c80, 0x00001800, 0x00001800); अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम
gm200_fb_init(काष्ठा nvkm_fb *base)
अणु
	काष्ठा gf100_fb *fb = gf100_fb(base);
	काष्ठा nvkm_device *device = fb->base.subdev.device;

	अगर (fb->r100c10_page)
		nvkm_wr32(device, 0x100c10, fb->r100c10 >> 8);

	nvkm_wr32(device, 0x100cc8, nvkm_memory_addr(fb->base.mmu_wr) >> 8);
	nvkm_wr32(device, 0x100ccc, nvkm_memory_addr(fb->base.mmu_rd) >> 8);
	nvkm_mask(device, 0x100cc4, 0x00060000,
		  min(nvkm_memory_size(fb->base.mmu_rd) >> 16, (u64)2) << 17);
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
gm200_fb = अणु
	.dtor = gf100_fb_dtor,
	.oneinit = gf100_fb_oneinit,
	.init = gm200_fb_init,
	.init_page = gm200_fb_init_page,
	.पूर्णांकr = gf100_fb_पूर्णांकr,
	.ram_new = gm200_ram_new,
	.शेष_bigpage = 0 /* per-instance. */,
पूर्ण;

पूर्णांक
gm200_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस gf100_fb_new_(&gm200_fb, device, type, inst, pfb);
पूर्ण
