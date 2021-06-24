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

अटल स्थिर काष्ठा nv04_fअगरo_ramfc
nv10_fअगरo_ramfc[] = अणु
	अणु 32,  0, 0x00,  0, NV04_PFIFO_CACHE1_DMA_PUT पूर्ण,
	अणु 32,  0, 0x04,  0, NV04_PFIFO_CACHE1_DMA_GET पूर्ण,
	अणु 32,  0, 0x08,  0, NV10_PFIFO_CACHE1_REF_CNT पूर्ण,
	अणु 16,  0, 0x0c,  0, NV04_PFIFO_CACHE1_DMA_INSTANCE पूर्ण,
	अणु 16, 16, 0x0c,  0, NV04_PFIFO_CACHE1_DMA_DCOUNT पूर्ण,
	अणु 32,  0, 0x10,  0, NV04_PFIFO_CACHE1_DMA_STATE पूर्ण,
	अणु 32,  0, 0x14,  0, NV04_PFIFO_CACHE1_DMA_FETCH पूर्ण,
	अणु 32,  0, 0x18,  0, NV04_PFIFO_CACHE1_ENGINE पूर्ण,
	अणु 32,  0, 0x1c,  0, NV04_PFIFO_CACHE1_PULL1 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_fअगरo_func
nv10_fअगरo = अणु
	.init = nv04_fअगरo_init,
	.पूर्णांकr = nv04_fअगरo_पूर्णांकr,
	.engine_id = nv04_fअगरo_engine_id,
	.id_engine = nv04_fअगरo_id_engine,
	.छोड़ो = nv04_fअगरo_छोड़ो,
	.start = nv04_fअगरo_start,
	.chan = अणु
		&nv10_fअगरo_dma_oclass,
		शून्य
	पूर्ण,
पूर्ण;

पूर्णांक
nv10_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस nv04_fअगरo_new_(&nv10_fअगरo, device, type, inst, 32, nv10_fअगरo_ramfc, pfअगरo);
पूर्ण
