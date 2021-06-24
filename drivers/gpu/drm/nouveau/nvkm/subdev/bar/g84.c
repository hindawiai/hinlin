<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "nv50.h"

#समावेश <subdev/समयr.h>

व्योम
g84_bar_flush(काष्ठा nvkm_bar *bar)
अणु
	काष्ठा nvkm_device *device = bar->subdev.device;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&bar->lock, flags);
	nvkm_wr32(device, 0x070000, 0x00000001);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x070000) & 0x00000002))
			अवरोध;
	);
	spin_unlock_irqrestore(&bar->lock, flags);
पूर्ण

अटल स्थिर काष्ठा nvkm_bar_func
g84_bar_func = अणु
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
	.flush = g84_bar_flush,
पूर्ण;

पूर्णांक
g84_bar_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	    काष्ठा nvkm_bar **pbar)
अणु
	वापस nv50_bar_new_(&g84_bar_func, device, type, inst, 0x200, pbar);
पूर्ण
