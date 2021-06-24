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
#समावेश <core/option.h>
#समावेश <subdev/therm.h>

व्योम
gf100_fb_पूर्णांकr(काष्ठा nvkm_fb *base)
अणु
	काष्ठा gf100_fb *fb = gf100_fb(base);
	काष्ठा nvkm_subdev *subdev = &fb->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x000100);
	अगर (पूर्णांकr & 0x08000000)
		nvkm_debug(subdev, "PFFB intr\n");
	अगर (पूर्णांकr & 0x00002000)
		nvkm_debug(subdev, "PBFB intr\n");
पूर्ण

पूर्णांक
gf100_fb_oneinit(काष्ठा nvkm_fb *base)
अणु
	काष्ठा gf100_fb *fb = gf100_fb(base);
	काष्ठा nvkm_device *device = fb->base.subdev.device;
	पूर्णांक ret, size = 1 << (fb->base.page ? fb->base.page : 17);

	size = nvkm_दीर्घopt(device->cfgopt, "MmuDebugBufferSize", size);
	size = max(size, 0x1000);

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, size, 0x1000,
			      true, &fb->base.mmu_rd);
	अगर (ret)
		वापस ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, size, 0x1000,
			      true, &fb->base.mmu_wr);
	अगर (ret)
		वापस ret;

	fb->r100c10_page = alloc_page(GFP_KERNEL | __GFP_ZERO);
	अगर (fb->r100c10_page) अणु
		fb->r100c10 = dma_map_page(device->dev, fb->r100c10_page, 0,
					   PAGE_SIZE, DMA_BIसूचीECTIONAL);
		अगर (dma_mapping_error(device->dev, fb->r100c10))
			वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक
gf100_fb_init_page(काष्ठा nvkm_fb *fb)
अणु
	काष्ठा nvkm_device *device = fb->subdev.device;
	चयन (fb->page) अणु
	हाल 16: nvkm_mask(device, 0x100c80, 0x00000001, 0x00000001); अवरोध;
	हाल 17: nvkm_mask(device, 0x100c80, 0x00000001, 0x00000000); अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम
gf100_fb_init(काष्ठा nvkm_fb *base)
अणु
	काष्ठा gf100_fb *fb = gf100_fb(base);
	काष्ठा nvkm_device *device = fb->base.subdev.device;

	अगर (fb->r100c10_page)
		nvkm_wr32(device, 0x100c10, fb->r100c10 >> 8);

	अगर (base->func->clkgate_pack) अणु
		nvkm_therm_clkgate_init(device->therm,
					base->func->clkgate_pack);
	पूर्ण
पूर्ण

व्योम *
gf100_fb_dtor(काष्ठा nvkm_fb *base)
अणु
	काष्ठा gf100_fb *fb = gf100_fb(base);
	काष्ठा nvkm_device *device = fb->base.subdev.device;

	अगर (fb->r100c10_page) अणु
		dma_unmap_page(device->dev, fb->r100c10, PAGE_SIZE,
			       DMA_BIसूचीECTIONAL);
		__मुक्त_page(fb->r100c10_page);
	पूर्ण

	वापस fb;
पूर्ण

पूर्णांक
gf100_fb_new_(स्थिर काष्ठा nvkm_fb_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	काष्ठा gf100_fb *fb;

	अगर (!(fb = kzalloc(माप(*fb), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_fb_ctor(func, device, type, inst, &fb->base);
	*pfb = &fb->base;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_fb_func
gf100_fb = अणु
	.dtor = gf100_fb_dtor,
	.oneinit = gf100_fb_oneinit,
	.init = gf100_fb_init,
	.init_page = gf100_fb_init_page,
	.पूर्णांकr = gf100_fb_पूर्णांकr,
	.ram_new = gf100_ram_new,
	.शेष_bigpage = 17,
पूर्ण;

पूर्णांक
gf100_fb_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fb **pfb)
अणु
	वापस gf100_fb_new_(&gf100_fb, device, type, inst, pfb);
पूर्ण
