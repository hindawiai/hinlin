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
#समावेश "nv04.h"
#समावेश "channv04.h"
#समावेश "regsnv04.h"

#समावेश <core/ramht.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/insपंचांगem.h>

अटल स्थिर काष्ठा nv04_fअगरo_ramfc
nv40_fअगरo_ramfc[] = अणु
	अणु 32,  0, 0x00,  0, NV04_PFIFO_CACHE1_DMA_PUT पूर्ण,
	अणु 32,  0, 0x04,  0, NV04_PFIFO_CACHE1_DMA_GET पूर्ण,
	अणु 32,  0, 0x08,  0, NV10_PFIFO_CACHE1_REF_CNT पूर्ण,
	अणु 32,  0, 0x0c,  0, NV04_PFIFO_CACHE1_DMA_INSTANCE पूर्ण,
	अणु 32,  0, 0x10,  0, NV04_PFIFO_CACHE1_DMA_DCOUNT पूर्ण,
	अणु 32,  0, 0x14,  0, NV04_PFIFO_CACHE1_DMA_STATE पूर्ण,
	अणु 28,  0, 0x18,  0, NV04_PFIFO_CACHE1_DMA_FETCH पूर्ण,
	अणु  2, 28, 0x18, 28, 0x002058 पूर्ण,
	अणु 32,  0, 0x1c,  0, NV04_PFIFO_CACHE1_ENGINE पूर्ण,
	अणु 32,  0, 0x20,  0, NV04_PFIFO_CACHE1_PULL1 पूर्ण,
	अणु 32,  0, 0x24,  0, NV10_PFIFO_CACHE1_ACQUIRE_VALUE पूर्ण,
	अणु 32,  0, 0x28,  0, NV10_PFIFO_CACHE1_ACQUIRE_TIMESTAMP पूर्ण,
	अणु 32,  0, 0x2c,  0, NV10_PFIFO_CACHE1_ACQUIRE_TIMEOUT पूर्ण,
	अणु 32,  0, 0x30,  0, NV10_PFIFO_CACHE1_SEMAPHORE पूर्ण,
	अणु 32,  0, 0x34,  0, NV10_PFIFO_CACHE1_DMA_SUBROUTINE पूर्ण,
	अणु 32,  0, 0x38,  0, NV40_PFIFO_GRCTX_INSTANCE पूर्ण,
	अणु 17,  0, 0x3c,  0, NV04_PFIFO_DMA_TIMESLICE पूर्ण,
	अणु 32,  0, 0x40,  0, 0x0032e4 पूर्ण,
	अणु 32,  0, 0x44,  0, 0x0032e8 पूर्ण,
	अणु 32,  0, 0x4c,  0, 0x002088 पूर्ण,
	अणु 32,  0, 0x50,  0, 0x003300 पूर्ण,
	अणु 32,  0, 0x54,  0, 0x00330c पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
nv40_fअगरo_init(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा nv04_fअगरo *fअगरo = nv04_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_fb *fb = device->fb;
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	काष्ठा nvkm_ramht *ramht = imem->ramht;
	काष्ठा nvkm_memory *ramro = imem->ramro;
	काष्ठा nvkm_memory *ramfc = imem->ramfc;

	nvkm_wr32(device, 0x002040, 0x000000ff);
	nvkm_wr32(device, 0x002044, 0x2101ffff);
	nvkm_wr32(device, 0x002058, 0x00000001);

	nvkm_wr32(device, NV03_PFIFO_RAMHT, (0x03 << 24) /* search 128 */ |
					    ((ramht->bits - 9) << 16) |
					    (ramht->gpuobj->addr >> 8));
	nvkm_wr32(device, NV03_PFIFO_RAMRO, nvkm_memory_addr(ramro) >> 8);

	चयन (device->chipset) अणु
	हाल 0x47:
	हाल 0x49:
	हाल 0x4b:
		nvkm_wr32(device, 0x002230, 0x00000001);
		fallthrough;
	हाल 0x40:
	हाल 0x41:
	हाल 0x42:
	हाल 0x43:
	हाल 0x45:
	हाल 0x48:
		nvkm_wr32(device, 0x002220, 0x00030002);
		अवरोध;
	शेष:
		nvkm_wr32(device, 0x002230, 0x00000000);
		nvkm_wr32(device, 0x002220, ((fb->ram->size - 512 * 1024 +
					      nvkm_memory_addr(ramfc)) >> 16) |
					    0x00030000);
		अवरोध;
	पूर्ण

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH1, fअगरo->base.nr - 1);

	nvkm_wr32(device, NV03_PFIFO_INTR_0, 0xffffffff);
	nvkm_wr32(device, NV03_PFIFO_INTR_EN_0, 0xffffffff);

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
	nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 1);
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_func
nv40_fअगरo = अणु
	.init = nv40_fअगरo_init,
	.पूर्णांकr = nv04_fअगरo_पूर्णांकr,
	.engine_id = nv04_fअगरo_engine_id,
	.id_engine = nv04_fअगरo_id_engine,
	.छोड़ो = nv04_fअगरo_छोड़ो,
	.start = nv04_fअगरo_start,
	.chan = अणु
		&nv40_fअगरo_dma_oclass,
		शून्य
	पूर्ण,
पूर्ण;

पूर्णांक
nv40_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस nv04_fअगरo_new_(&nv40_fअगरo, device, type, inst, 32, nv40_fअगरo_ramfc, pfअगरo);
पूर्ण
