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
#समावेश "priv.h"

#समावेश <core/option.h>
#समावेश <subdev/vga.h>

u32
nvkm_devinit_mmio(काष्ठा nvkm_devinit *init, u32 addr)
अणु
	अगर (init->func->mmio)
		addr = init->func->mmio(init, addr);
	वापस addr;
पूर्ण

पूर्णांक
nvkm_devinit_pll_set(काष्ठा nvkm_devinit *init, u32 type, u32 khz)
अणु
	वापस init->func->pll_set(init, type, khz);
पूर्ण

व्योम
nvkm_devinit_meminit(काष्ठा nvkm_devinit *init)
अणु
	अगर (init->func->meminit)
		init->func->meminit(init);
पूर्ण

u64
nvkm_devinit_disable(काष्ठा nvkm_devinit *init)
अणु
	अगर (init && init->func->disable)
		वापस init->func->disable(init);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_devinit_post(काष्ठा nvkm_devinit *init)
अणु
	पूर्णांक ret = 0;
	अगर (init && init->func->post)
		ret = init->func->post(init, init->post);
	nvkm_devinit_disable(init);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_devinit_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_devinit *init = nvkm_devinit(subdev);
	/* क्रमce full reinit on resume */
	अगर (suspend)
		init->post = true;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_devinit_preinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_devinit *init = nvkm_devinit(subdev);

	अगर (init->func->preinit)
		init->func->preinit(init);

	/* Override the post flag during the first call अगर NvForcePost is set */
	अगर (init->क्रमce_post) अणु
		init->post = init->क्रमce_post;
		init->क्रमce_post = false;
	पूर्ण

	/* unlock the extended vga crtc regs */
	nvkm_lockvgac(subdev->device, false);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_devinit_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_devinit *init = nvkm_devinit(subdev);
	अगर (init->func->init)
		init->func->init(init);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_devinit_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_devinit *init = nvkm_devinit(subdev);
	व्योम *data = init;

	अगर (init->func->dtor)
		data = init->func->dtor(init);

	/* lock crtc regs */
	nvkm_lockvgac(subdev->device, true);
	वापस data;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_devinit = अणु
	.dtor = nvkm_devinit_dtor,
	.preinit = nvkm_devinit_preinit,
	.init = nvkm_devinit_init,
	.fini = nvkm_devinit_fini,
पूर्ण;

व्योम
nvkm_devinit_ctor(स्थिर काष्ठा nvkm_devinit_func *func, काष्ठा nvkm_device *device,
		  क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_devinit *init)
अणु
	nvkm_subdev_ctor(&nvkm_devinit, device, type, inst, &init->subdev);
	init->func = func;
	init->क्रमce_post = nvkm_boolopt(device->cfgopt, "NvForcePost", false);
पूर्ण
