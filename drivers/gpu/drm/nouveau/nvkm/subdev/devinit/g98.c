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
#समावेश "nv50.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>

अटल u64
g98_devinit_disable(काष्ठा nvkm_devinit *init)
अणु
	काष्ठा nvkm_device *device = init->subdev.device;
	u32 r001540 = nvkm_rd32(device, 0x001540);
	u32 r00154c = nvkm_rd32(device, 0x00154c);
	u64 disable = 0ULL;

	अगर (!(r001540 & 0x40000000)) अणु
		nvkm_subdev_disable(device, NVKM_ENGINE_MSPDEC, 0);
		nvkm_subdev_disable(device, NVKM_ENGINE_MSVLD, 0);
		nvkm_subdev_disable(device, NVKM_ENGINE_MSPPP, 0);
	पूर्ण

	अगर (!(r00154c & 0x00000004))
		nvkm_subdev_disable(device, NVKM_ENGINE_DISP, 0);
	अगर (!(r00154c & 0x00000020))
		nvkm_subdev_disable(device, NVKM_ENGINE_MSVLD, 0);
	अगर (!(r00154c & 0x00000040))
		nvkm_subdev_disable(device, NVKM_ENGINE_SEC, 0);

	वापस disable;
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
g98_devinit = अणु
	.preinit = nv50_devinit_preinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.pll_set = nv50_devinit_pll_set,
	.disable = g98_devinit_disable,
पूर्ण;

पूर्णांक
g98_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv50_devinit_new_(&g98_devinit, device, type, inst, pinit);
पूर्ण
