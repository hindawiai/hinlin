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
#समावेश "nv50.h"

#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/mmu.h>
#समावेश <subdev/समयr.h>

अटल व्योम
nv50_bar_flush(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nv50_bar *bar = nv50_bar(base);
	काष्ठा nvkm_device *device = bar->base.subdev.device;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&bar->base.lock, flags);
	nvkm_wr32(device, 0x00330c, 0x00000001);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x00330c) & 0x00000002))
			अवरोध;
	);
	spin_unlock_irqrestore(&bar->base.lock, flags);
पूर्ण

काष्ठा nvkm_vmm *
nv50_bar_bar1_vmm(काष्ठा nvkm_bar *base)
अणु
	वापस nv50_bar(base)->bar1_vmm;
पूर्ण

व्योम
nv50_bar_bar1_रुको(काष्ठा nvkm_bar *base)
अणु
	nvkm_bar_flush(base);
पूर्ण

व्योम
nv50_bar_bar1_fini(काष्ठा nvkm_bar *bar)
अणु
	nvkm_wr32(bar->subdev.device, 0x001708, 0x00000000);
पूर्ण

व्योम
nv50_bar_bar1_init(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nvkm_device *device = base->subdev.device;
	काष्ठा nv50_bar *bar = nv50_bar(base);
	nvkm_wr32(device, 0x001708, 0x80000000 | bar->bar1->node->offset >> 4);
पूर्ण

काष्ठा nvkm_vmm *
nv50_bar_bar2_vmm(काष्ठा nvkm_bar *base)
अणु
	वापस nv50_bar(base)->bar2_vmm;
पूर्ण

व्योम
nv50_bar_bar2_fini(काष्ठा nvkm_bar *bar)
अणु
	nvkm_wr32(bar->subdev.device, 0x00170c, 0x00000000);
पूर्ण

व्योम
nv50_bar_bar2_init(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nvkm_device *device = base->subdev.device;
	काष्ठा nv50_bar *bar = nv50_bar(base);
	nvkm_wr32(device, 0x001704, 0x00000000 | bar->mem->addr >> 12);
	nvkm_wr32(device, 0x001704, 0x40000000 | bar->mem->addr >> 12);
	nvkm_wr32(device, 0x00170c, 0x80000000 | bar->bar2->node->offset >> 4);
पूर्ण

व्योम
nv50_bar_init(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nv50_bar *bar = nv50_bar(base);
	काष्ठा nvkm_device *device = bar->base.subdev.device;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		nvkm_wr32(device, 0x001900 + (i * 4), 0x00000000);
पूर्ण

पूर्णांक
nv50_bar_oneinit(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nv50_bar *bar = nv50_bar(base);
	काष्ठा nvkm_device *device = bar->base.subdev.device;
	अटल काष्ठा lock_class_key bar1_lock;
	अटल काष्ठा lock_class_key bar2_lock;
	u64 start, limit, size;
	पूर्णांक ret;

	ret = nvkm_gpuobj_new(device, 0x20000, 0, false, शून्य, &bar->mem);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, bar->pgd_addr, 0, false, bar->mem,
			      &bar->pad);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x4000, 0, false, bar->mem, &bar->pgd);
	अगर (ret)
		वापस ret;

	/* BAR2 */
	start = 0x0100000000ULL;
	size = device->func->resource_size(device, 3);
	अगर (!size)
		वापस -ENOMEM;
	limit = start + size;

	ret = nvkm_vmm_new(device, start, limit-- - start, शून्य, 0,
			   &bar2_lock, "bar2", &bar->bar2_vmm);
	अगर (ret)
		वापस ret;

	atomic_inc(&bar->bar2_vmm->engref[NVKM_SUBDEV_BAR]);
	bar->bar2_vmm->debug = bar->base.subdev.debug;

	ret = nvkm_vmm_boot(bar->bar2_vmm);
	अगर (ret)
		वापस ret;

	ret = nvkm_vmm_join(bar->bar2_vmm, bar->mem->memory);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 24, 16, false, bar->mem, &bar->bar2);
	अगर (ret)
		वापस ret;

	nvkm_kmap(bar->bar2);
	nvkm_wo32(bar->bar2, 0x00, 0x7fc00000);
	nvkm_wo32(bar->bar2, 0x04, lower_32_bits(limit));
	nvkm_wo32(bar->bar2, 0x08, lower_32_bits(start));
	nvkm_wo32(bar->bar2, 0x0c, upper_32_bits(limit) << 24 |
				   upper_32_bits(start));
	nvkm_wo32(bar->bar2, 0x10, 0x00000000);
	nvkm_wo32(bar->bar2, 0x14, 0x00000000);
	nvkm_करोne(bar->bar2);

	bar->base.subdev.oneinit = true;
	nvkm_bar_bar2_init(device);

	/* BAR1 */
	start = 0x0000000000ULL;
	size = device->func->resource_size(device, 1);
	अगर (!size)
		वापस -ENOMEM;
	limit = start + size;

	ret = nvkm_vmm_new(device, start, limit-- - start, शून्य, 0,
			   &bar1_lock, "bar1", &bar->bar1_vmm);
	अगर (ret)
		वापस ret;

	atomic_inc(&bar->bar1_vmm->engref[NVKM_SUBDEV_BAR]);
	bar->bar1_vmm->debug = bar->base.subdev.debug;

	ret = nvkm_vmm_join(bar->bar1_vmm, bar->mem->memory);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 24, 16, false, bar->mem, &bar->bar1);
	अगर (ret)
		वापस ret;

	nvkm_kmap(bar->bar1);
	nvkm_wo32(bar->bar1, 0x00, 0x7fc00000);
	nvkm_wo32(bar->bar1, 0x04, lower_32_bits(limit));
	nvkm_wo32(bar->bar1, 0x08, lower_32_bits(start));
	nvkm_wo32(bar->bar1, 0x0c, upper_32_bits(limit) << 24 |
				   upper_32_bits(start));
	nvkm_wo32(bar->bar1, 0x10, 0x00000000);
	nvkm_wo32(bar->bar1, 0x14, 0x00000000);
	nvkm_करोne(bar->bar1);
	वापस 0;
पूर्ण

व्योम *
nv50_bar_dtor(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nv50_bar *bar = nv50_bar(base);
	अगर (bar->mem) अणु
		nvkm_gpuobj_del(&bar->bar1);
		nvkm_vmm_part(bar->bar1_vmm, bar->mem->memory);
		nvkm_vmm_unref(&bar->bar1_vmm);
		nvkm_gpuobj_del(&bar->bar2);
		nvkm_vmm_part(bar->bar2_vmm, bar->mem->memory);
		nvkm_vmm_unref(&bar->bar2_vmm);
		nvkm_gpuobj_del(&bar->pgd);
		nvkm_gpuobj_del(&bar->pad);
		nvkm_gpuobj_del(&bar->mem);
	पूर्ण
	वापस bar;
पूर्ण

पूर्णांक
nv50_bar_new_(स्थिर काष्ठा nvkm_bar_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, u32 pgd_addr, काष्ठा nvkm_bar **pbar)
अणु
	काष्ठा nv50_bar *bar;
	अगर (!(bar = kzalloc(माप(*bar), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_bar_ctor(func, device, type, inst, &bar->base);
	bar->pgd_addr = pgd_addr;
	*pbar = &bar->base;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_bar_func
nv50_bar_func = अणु
	.dtor = nv50_bar_dtor,
	.oneinit = nv50_bar_oneinit,
	.init = nv50_bar_init,
	.bar1.init = nv50_bar_bar1_init,
	.bar1.fini = nv50_bar_bar1_fini,
	.bar1.रुको = nv50_bar_bar1_रुको,
	.bar1.vmm = nv50_bar_bar1_vmm,
	.bar2.init = nv50_bar_bar2_init,
	.bar2.fini = nv50_bar_bar2_fini,
	.bar2.रुको = nv50_bar_bar1_रुको,
	.bar2.vmm = nv50_bar_bar2_vmm,
	.flush = nv50_bar_flush,
पूर्ण;

पूर्णांक
nv50_bar_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_bar **pbar)
अणु
	वापस nv50_bar_new_(&nv50_bar_func, device, type, inst, 0x1400, pbar);
पूर्ण
