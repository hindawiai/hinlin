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
#समावेश "channv50.h"

अटल व्योम
g84_fअगरo_uevent_fini(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	nvkm_mask(device, 0x002140, 0x40000000, 0x00000000);
पूर्ण

अटल व्योम
g84_fअगरo_uevent_init(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	nvkm_mask(device, 0x002140, 0x40000000, 0x40000000);
पूर्ण

अटल काष्ठा nvkm_engine *
g84_fअगरo_id_engine(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक engi)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	काष्ठा nvkm_engine *engine;
	क्रमागत nvkm_subdev_type type;

	चयन (engi) अणु
	हाल G84_FIFO_ENGN_SW    : type = NVKM_ENGINE_SW; अवरोध;
	हाल G84_FIFO_ENGN_GR    : type = NVKM_ENGINE_GR; अवरोध;
	हाल G84_FIFO_ENGN_MPEG  :
		अगर ((engine = nvkm_device_engine(device, NVKM_ENGINE_MSPPP, 0)))
			वापस engine;
		type = NVKM_ENGINE_MPEG;
		अवरोध;
	हाल G84_FIFO_ENGN_ME    :
		अगर ((engine = nvkm_device_engine(device, NVKM_ENGINE_CE, 0)))
			वापस engine;
		type = NVKM_ENGINE_ME;
		अवरोध;
	हाल G84_FIFO_ENGN_VP    :
		अगर ((engine = nvkm_device_engine(device, NVKM_ENGINE_MSPDEC, 0)))
			वापस engine;
		type = NVKM_ENGINE_VP;
		अवरोध;
	हाल G84_FIFO_ENGN_CIPHER:
		अगर ((engine = nvkm_device_engine(device, NVKM_ENGINE_VIC, 0)))
			वापस engine;
		अगर ((engine = nvkm_device_engine(device, NVKM_ENGINE_SEC, 0)))
			वापस engine;
		type = NVKM_ENGINE_CIPHER;
		अवरोध;
	हाल G84_FIFO_ENGN_BSP   :
		अगर ((engine = nvkm_device_engine(device, NVKM_ENGINE_MSVLD, 0)))
			वापस engine;
		type = NVKM_ENGINE_BSP;
		अवरोध;
	हाल G84_FIFO_ENGN_DMA   : type = NVKM_ENGINE_DMAOBJ; अवरोध;
	शेष:
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	वापस nvkm_device_engine(fअगरo->engine.subdev.device, type, 0);
पूर्ण

अटल पूर्णांक
g84_fअगरo_engine_id(काष्ठा nvkm_fअगरo *base, काष्ठा nvkm_engine *engine)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_SW    : वापस G84_FIFO_ENGN_SW;
	हाल NVKM_ENGINE_GR    : वापस G84_FIFO_ENGN_GR;
	हाल NVKM_ENGINE_MPEG  :
	हाल NVKM_ENGINE_MSPPP : वापस G84_FIFO_ENGN_MPEG;
	हाल NVKM_ENGINE_CE    : वापस G84_FIFO_ENGN_CE0;
	हाल NVKM_ENGINE_VP    :
	हाल NVKM_ENGINE_MSPDEC: वापस G84_FIFO_ENGN_VP;
	हाल NVKM_ENGINE_CIPHER:
	हाल NVKM_ENGINE_SEC   : वापस G84_FIFO_ENGN_CIPHER;
	हाल NVKM_ENGINE_BSP   :
	हाल NVKM_ENGINE_MSVLD : वापस G84_FIFO_ENGN_BSP;
	हाल NVKM_ENGINE_DMAOBJ: वापस G84_FIFO_ENGN_DMA;
	शेष:
		WARN_ON(1);
		वापस -1;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_func
g84_fअगरo = अणु
	.dtor = nv50_fअगरo_dtor,
	.oneinit = nv50_fअगरo_oneinit,
	.init = nv50_fअगरo_init,
	.पूर्णांकr = nv04_fअगरo_पूर्णांकr,
	.engine_id = g84_fअगरo_engine_id,
	.id_engine = g84_fअगरo_id_engine,
	.छोड़ो = nv04_fअगरo_छोड़ो,
	.start = nv04_fअगरo_start,
	.uevent_init = g84_fअगरo_uevent_init,
	.uevent_fini = g84_fअगरo_uevent_fini,
	.chan = अणु
		&g84_fअगरo_dma_oclass,
		&g84_fअगरo_gpfअगरo_oclass,
		शून्य
	पूर्ण,
पूर्ण;

पूर्णांक
g84_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस nv50_fअगरo_new_(&g84_fअगरo, device, type, inst, pfअगरo);
पूर्ण
