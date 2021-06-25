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

#समावेश <core/memory.h>
#समावेश <core/option.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/mmu.h>

काष्ठा nvkm_vmm *
gf100_bar_bar1_vmm(काष्ठा nvkm_bar *base)
अणु
	वापस gf100_bar(base)->bar[1].vmm;
पूर्ण

व्योम
gf100_bar_bar1_रुको(काष्ठा nvkm_bar *base)
अणु
	/* NFI why it's twice. */
	nvkm_bar_flush(base);
	nvkm_bar_flush(base);
पूर्ण

व्योम
gf100_bar_bar1_fini(काष्ठा nvkm_bar *bar)
अणु
	nvkm_mask(bar->subdev.device, 0x001704, 0x80000000, 0x00000000);
पूर्ण

व्योम
gf100_bar_bar1_init(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nvkm_device *device = base->subdev.device;
	काष्ठा gf100_bar *bar = gf100_bar(base);
	स्थिर u32 addr = nvkm_memory_addr(bar->bar[1].inst) >> 12;
	nvkm_wr32(device, 0x001704, 0x80000000 | addr);
पूर्ण

काष्ठा nvkm_vmm *
gf100_bar_bar2_vmm(काष्ठा nvkm_bar *base)
अणु
	वापस gf100_bar(base)->bar[0].vmm;
पूर्ण

व्योम
gf100_bar_bar2_fini(काष्ठा nvkm_bar *bar)
अणु
	nvkm_mask(bar->subdev.device, 0x001714, 0x80000000, 0x00000000);
पूर्ण

व्योम
gf100_bar_bar2_init(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nvkm_device *device = base->subdev.device;
	काष्ठा gf100_bar *bar = gf100_bar(base);
	u32 addr = nvkm_memory_addr(bar->bar[0].inst) >> 12;
	अगर (bar->bar2_halve)
		addr |= 0x40000000;
	nvkm_wr32(device, 0x001714, 0x80000000 | addr);
पूर्ण

अटल पूर्णांक
gf100_bar_oneinit_bar(काष्ठा gf100_bar *bar, काष्ठा gf100_barN *bar_vm,
		      काष्ठा lock_class_key *key, पूर्णांक bar_nr)
अणु
	काष्ठा nvkm_device *device = bar->base.subdev.device;
	resource_माप_प्रकार bar_len;
	पूर्णांक ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0, false,
			      &bar_vm->inst);
	अगर (ret)
		वापस ret;

	bar_len = device->func->resource_size(device, bar_nr);
	अगर (!bar_len)
		वापस -ENOMEM;
	अगर (bar_nr == 3 && bar->bar2_halve)
		bar_len >>= 1;

	ret = nvkm_vmm_new(device, 0, bar_len, शून्य, 0, key,
			   (bar_nr == 3) ? "bar2" : "bar1", &bar_vm->vmm);
	अगर (ret)
		वापस ret;

	atomic_inc(&bar_vm->vmm->engref[NVKM_SUBDEV_BAR]);
	bar_vm->vmm->debug = bar->base.subdev.debug;

	/*
	 * Bootstrap page table lookup.
	 */
	अगर (bar_nr == 3) अणु
		ret = nvkm_vmm_boot(bar_vm->vmm);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस nvkm_vmm_join(bar_vm->vmm, bar_vm->inst);
पूर्ण

पूर्णांक
gf100_bar_oneinit(काष्ठा nvkm_bar *base)
अणु
	अटल काष्ठा lock_class_key bar1_lock;
	अटल काष्ठा lock_class_key bar2_lock;
	काष्ठा gf100_bar *bar = gf100_bar(base);
	पूर्णांक ret;

	/* BAR2 */
	अगर (bar->base.func->bar2.init) अणु
		ret = gf100_bar_oneinit_bar(bar, &bar->bar[0], &bar2_lock, 3);
		अगर (ret)
			वापस ret;

		bar->base.subdev.oneinit = true;
		nvkm_bar_bar2_init(bar->base.subdev.device);
	पूर्ण

	/* BAR1 */
	ret = gf100_bar_oneinit_bar(bar, &bar->bar[1], &bar1_lock, 1);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

व्योम *
gf100_bar_dtor(काष्ठा nvkm_bar *base)
अणु
	काष्ठा gf100_bar *bar = gf100_bar(base);

	nvkm_vmm_part(bar->bar[1].vmm, bar->bar[1].inst);
	nvkm_vmm_unref(&bar->bar[1].vmm);
	nvkm_memory_unref(&bar->bar[1].inst);

	nvkm_vmm_part(bar->bar[0].vmm, bar->bar[0].inst);
	nvkm_vmm_unref(&bar->bar[0].vmm);
	nvkm_memory_unref(&bar->bar[0].inst);
	वापस bar;
पूर्ण

पूर्णांक
gf100_bar_new_(स्थिर काष्ठा nvkm_bar_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_bar **pbar)
अणु
	काष्ठा gf100_bar *bar;
	अगर (!(bar = kzalloc(माप(*bar), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_bar_ctor(func, device, type, inst, &bar->base);
	bar->bar2_halve = nvkm_boolopt(device->cfgopt, "NvBar2Halve", false);
	*pbar = &bar->base;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_bar_func
gf100_bar_func = अणु
	.dtor = gf100_bar_dtor,
	.oneinit = gf100_bar_oneinit,
	.bar1.init = gf100_bar_bar1_init,
	.bar1.fini = gf100_bar_bar1_fini,
	.bar1.रुको = gf100_bar_bar1_रुको,
	.bar1.vmm = gf100_bar_bar1_vmm,
	.bar2.init = gf100_bar_bar2_init,
	.bar2.fini = gf100_bar_bar2_fini,
	.bar2.रुको = gf100_bar_bar1_रुको,
	.bar2.vmm = gf100_bar_bar2_vmm,
	.flush = g84_bar_flush,
पूर्ण;

पूर्णांक
gf100_bar_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_bar **pbar)
अणु
	वापस gf100_bar_new_(&gf100_bar_func, device, type, inst, pbar);
पूर्ण
