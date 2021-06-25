<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
 */
#समावेश "gf100.h"

#समावेश <core/memory.h>
#समावेश <subdev/समयr.h>

अटल व्योम
tu102_bar_bar2_रुको(काष्ठा nvkm_bar *bar)
अणु
	काष्ठा nvkm_device *device = bar->subdev.device;
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0xb80f50) & 0x0000000c))
			अवरोध;
	);
पूर्ण

अटल व्योम
tu102_bar_bar2_fini(काष्ठा nvkm_bar *bar)
अणु
	nvkm_mask(bar->subdev.device, 0xb80f48, 0x80000000, 0x00000000);
पूर्ण

अटल व्योम
tu102_bar_bar2_init(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nvkm_device *device = base->subdev.device;
	काष्ठा gf100_bar *bar = gf100_bar(base);
	u32 addr = nvkm_memory_addr(bar->bar[0].inst) >> 12;
	अगर (bar->bar2_halve)
		addr |= 0x40000000;
	nvkm_wr32(device, 0xb80f48, 0x80000000 | addr);
पूर्ण

अटल व्योम
tu102_bar_bar1_रुको(काष्ठा nvkm_bar *bar)
अणु
	काष्ठा nvkm_device *device = bar->subdev.device;
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0xb80f50) & 0x00000003))
			अवरोध;
	);
पूर्ण

अटल व्योम
tu102_bar_bar1_fini(काष्ठा nvkm_bar *bar)
अणु
	nvkm_mask(bar->subdev.device, 0xb80f40, 0x80000000, 0x00000000);
पूर्ण

अटल व्योम
tu102_bar_bar1_init(काष्ठा nvkm_bar *base)
अणु
	काष्ठा nvkm_device *device = base->subdev.device;
	काष्ठा gf100_bar *bar = gf100_bar(base);
	स्थिर u32 addr = nvkm_memory_addr(bar->bar[1].inst) >> 12;
	nvkm_wr32(device, 0xb80f40, 0x80000000 | addr);
पूर्ण

अटल स्थिर काष्ठा nvkm_bar_func
tu102_bar = अणु
	.dtor = gf100_bar_dtor,
	.oneinit = gf100_bar_oneinit,
	.bar1.init = tu102_bar_bar1_init,
	.bar1.fini = tu102_bar_bar1_fini,
	.bar1.रुको = tu102_bar_bar1_रुको,
	.bar1.vmm = gf100_bar_bar1_vmm,
	.bar2.init = tu102_bar_bar2_init,
	.bar2.fini = tu102_bar_bar2_fini,
	.bar2.रुको = tu102_bar_bar2_रुको,
	.bar2.vmm = gf100_bar_bar2_vmm,
	.flush = g84_bar_flush,
पूर्ण;

पूर्णांक
tu102_bar_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_bar **pbar)
अणु
	वापस gf100_bar_new_(&tu102_bar, device, type, inst, pbar);
पूर्ण
