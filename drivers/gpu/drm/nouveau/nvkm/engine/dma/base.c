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

#समावेश <core/client.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>

अटल पूर्णांक
nvkm_dma_oclass_new(काष्ठा nvkm_device *device,
		    स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		    काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_dma *dma = nvkm_dma(oclass->engine);
	काष्ठा nvkm_dmaobj *dmaobj = शून्य;
	पूर्णांक ret;

	ret = dma->func->class_new(dma, oclass, data, size, &dmaobj);
	अगर (dmaobj)
		*pobject = &dmaobj->object;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_device_oclass
nvkm_dma_oclass_base = अणु
	.ctor = nvkm_dma_oclass_new,
पूर्ण;

अटल पूर्णांक
nvkm_dma_oclass_fअगरo_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
			 काष्ठा nvkm_object **pobject)
अणु
	वापस nvkm_dma_oclass_new(oclass->engine->subdev.device,
				   oclass, data, size, pobject);
पूर्ण

अटल स्थिर काष्ठा nvkm_sclass
nvkm_dma_sclass[] = अणु
	अणु 0, 0, NV_DMA_FROM_MEMORY, शून्य, nvkm_dma_oclass_fअगरo_new पूर्ण,
	अणु 0, 0, NV_DMA_TO_MEMORY, शून्य, nvkm_dma_oclass_fअगरo_new पूर्ण,
	अणु 0, 0, NV_DMA_IN_MEMORY, शून्य, nvkm_dma_oclass_fअगरo_new पूर्ण,
पूर्ण;

अटल पूर्णांक
nvkm_dma_oclass_base_get(काष्ठा nvkm_oclass *sclass, पूर्णांक index,
			 स्थिर काष्ठा nvkm_device_oclass **class)
अणु
	स्थिर पूर्णांक count = ARRAY_SIZE(nvkm_dma_sclass);
	अगर (index < count) अणु
		स्थिर काष्ठा nvkm_sclass *oclass = &nvkm_dma_sclass[index];
		sclass->base = oclass[0];
		sclass->engn = oclass;
		*class = &nvkm_dma_oclass_base;
		वापस index;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक
nvkm_dma_oclass_fअगरo_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index)
अणु
	स्थिर पूर्णांक count = ARRAY_SIZE(nvkm_dma_sclass);
	अगर (index < count) अणु
		oclass->base = nvkm_dma_sclass[index];
		वापस index;
	पूर्ण
	वापस count;
पूर्ण

अटल व्योम *
nvkm_dma_dtor(काष्ठा nvkm_engine *engine)
अणु
	वापस nvkm_dma(engine);
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_dma = अणु
	.dtor = nvkm_dma_dtor,
	.base.sclass = nvkm_dma_oclass_base_get,
	.fअगरo.sclass = nvkm_dma_oclass_fअगरo_get,
पूर्ण;

पूर्णांक
nvkm_dma_new_(स्थिर काष्ठा nvkm_dma_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_dma **pdma)
अणु
	काष्ठा nvkm_dma *dma;

	अगर (!(dma = *pdma = kzalloc(माप(*dma), GFP_KERNEL)))
		वापस -ENOMEM;
	dma->func = func;

	वापस nvkm_engine_ctor(&nvkm_dma, device, type, inst, true, &dma->engine);
पूर्ण
