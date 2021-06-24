<शैली गुरु>
/*
 * Copyright 2014 Red Hat Inc.
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
#समावेश "priv.h"

#समावेश <core/memory.h>

व्योम
nvkm_ltc_tags_clear(काष्ठा nvkm_device *device, u32 first, u32 count)
अणु
	काष्ठा nvkm_ltc *ltc = device->ltc;
	स्थिर u32 limit = first + count - 1;

	BUG_ON((first > limit) || (limit >= ltc->num_tags));

	mutex_lock(&ltc->mutex);
	ltc->func->cbc_clear(ltc, first, limit);
	ltc->func->cbc_रुको(ltc);
	mutex_unlock(&ltc->mutex);
पूर्ण

पूर्णांक
nvkm_ltc_zbc_color_get(काष्ठा nvkm_ltc *ltc, पूर्णांक index, स्थिर u32 color[4])
अणु
	स_नकल(ltc->zbc_color[index], color, माप(ltc->zbc_color[index]));
	ltc->func->zbc_clear_color(ltc, index, color);
	वापस index;
पूर्ण

पूर्णांक
nvkm_ltc_zbc_depth_get(काष्ठा nvkm_ltc *ltc, पूर्णांक index, स्थिर u32 depth)
अणु
	ltc->zbc_depth[index] = depth;
	ltc->func->zbc_clear_depth(ltc, index, depth);
	वापस index;
पूर्ण

पूर्णांक
nvkm_ltc_zbc_stencil_get(काष्ठा nvkm_ltc *ltc, पूर्णांक index, स्थिर u32 stencil)
अणु
	ltc->zbc_stencil[index] = stencil;
	ltc->func->zbc_clear_stencil(ltc, index, stencil);
	वापस index;
पूर्ण

व्योम
nvkm_ltc_invalidate(काष्ठा nvkm_ltc *ltc)
अणु
	अगर (ltc->func->invalidate)
		ltc->func->invalidate(ltc);
पूर्ण

व्योम
nvkm_ltc_flush(काष्ठा nvkm_ltc *ltc)
अणु
	अगर (ltc->func->flush)
		ltc->func->flush(ltc);
पूर्ण

अटल व्योम
nvkm_ltc_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_ltc *ltc = nvkm_ltc(subdev);
	ltc->func->पूर्णांकr(ltc);
पूर्ण

अटल पूर्णांक
nvkm_ltc_oneinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_ltc *ltc = nvkm_ltc(subdev);
	वापस ltc->func->oneinit(ltc);
पूर्ण

अटल पूर्णांक
nvkm_ltc_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_ltc *ltc = nvkm_ltc(subdev);
	पूर्णांक i;

	क्रम (i = ltc->zbc_min; i <= ltc->zbc_max; i++) अणु
		ltc->func->zbc_clear_color(ltc, i, ltc->zbc_color[i]);
		ltc->func->zbc_clear_depth(ltc, i, ltc->zbc_depth[i]);
		अगर (ltc->func->zbc_clear_stencil)
			ltc->func->zbc_clear_stencil(ltc, i, ltc->zbc_stencil[i]);
	पूर्ण

	ltc->func->init(ltc);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_ltc_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_ltc *ltc = nvkm_ltc(subdev);
	nvkm_memory_unref(&ltc->tag_ram);
	mutex_destroy(&ltc->mutex);
	वापस ltc;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_ltc = अणु
	.dtor = nvkm_ltc_dtor,
	.oneinit = nvkm_ltc_oneinit,
	.init = nvkm_ltc_init,
	.पूर्णांकr = nvkm_ltc_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_ltc_new_(स्थिर काष्ठा nvkm_ltc_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_ltc **pltc)
अणु
	काष्ठा nvkm_ltc *ltc;

	अगर (!(ltc = *pltc = kzalloc(माप(*ltc), GFP_KERNEL)))
		वापस -ENOMEM;

	nvkm_subdev_ctor(&nvkm_ltc, device, type, inst, &ltc->subdev);
	ltc->func = func;
	mutex_init(&ltc->mutex);
	ltc->zbc_min = 1; /* reserve 0 क्रम disabled */
	ltc->zbc_max = min(func->zbc, NVKM_LTC_MAX_ZBC_CNT) - 1;
	वापस 0;
पूर्ण
