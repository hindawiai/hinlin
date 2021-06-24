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

#समावेश <core/gpuobj.h>

अटल व्योम
nv50_fअगरo_runlist_update_locked(काष्ठा nv50_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_memory *cur;
	पूर्णांक i, p;

	cur = fअगरo->runlist[fअगरo->cur_runlist];
	fअगरo->cur_runlist = !fअगरo->cur_runlist;

	nvkm_kmap(cur);
	क्रम (i = 0, p = 0; i < fअगरo->base.nr; i++) अणु
		अगर (nvkm_rd32(device, 0x002600 + (i * 4)) & 0x80000000)
			nvkm_wo32(cur, p++ * 4, i);
	पूर्ण
	nvkm_करोne(cur);

	nvkm_wr32(device, 0x0032f4, nvkm_memory_addr(cur) >> 12);
	nvkm_wr32(device, 0x0032ec, p);
	nvkm_wr32(device, 0x002500, 0x00000101);
पूर्ण

व्योम
nv50_fअगरo_runlist_update(काष्ठा nv50_fअगरo *fअगरo)
अणु
	mutex_lock(&fअगरo->base.mutex);
	nv50_fअगरo_runlist_update_locked(fअगरo);
	mutex_unlock(&fअगरo->base.mutex);
पूर्ण

पूर्णांक
nv50_fअगरo_oneinit(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा nv50_fअगरo *fअगरo = nv50_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 128 * 4, 0x1000,
			      false, &fअगरo->runlist[0]);
	अगर (ret)
		वापस ret;

	वापस nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 128 * 4, 0x1000,
			       false, &fअगरo->runlist[1]);
पूर्ण

व्योम
nv50_fअगरo_init(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा nv50_fअगरo *fअगरo = nv50_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक i;

	nvkm_mask(device, 0x000200, 0x00000100, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00000100, 0x00000100);
	nvkm_wr32(device, 0x00250c, 0x6f3cfc34);
	nvkm_wr32(device, 0x002044, 0x01003fff);

	nvkm_wr32(device, 0x002100, 0xffffffff);
	nvkm_wr32(device, 0x002140, 0xbfffffff);

	क्रम (i = 0; i < 128; i++)
		nvkm_wr32(device, 0x002600 + (i * 4), 0x00000000);
	nv50_fअगरo_runlist_update_locked(fअगरo);

	nvkm_wr32(device, 0x003200, 0x00000001);
	nvkm_wr32(device, 0x003250, 0x00000001);
	nvkm_wr32(device, 0x002500, 0x00000001);
पूर्ण

व्योम *
nv50_fअगरo_dtor(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा nv50_fअगरo *fअगरo = nv50_fअगरo(base);
	nvkm_memory_unref(&fअगरo->runlist[1]);
	nvkm_memory_unref(&fअगरo->runlist[0]);
	वापस fअगरo;
पूर्ण

पूर्णांक
nv50_fअगरo_new_(स्थिर काष्ठा nvkm_fअगरo_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	काष्ठा nv50_fअगरo *fअगरo;
	पूर्णांक ret;

	अगर (!(fअगरo = kzalloc(माप(*fअगरo), GFP_KERNEL)))
		वापस -ENOMEM;
	*pfअगरo = &fअगरo->base;

	ret = nvkm_fअगरo_ctor(func, device, type, inst, 128, &fअगरo->base);
	अगर (ret)
		वापस ret;

	set_bit(0, fअगरo->base.mask); /* PIO channel */
	set_bit(127, fअगरo->base.mask); /* inactive channel */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_func
nv50_fअगरo = अणु
	.dtor = nv50_fअगरo_dtor,
	.oneinit = nv50_fअगरo_oneinit,
	.init = nv50_fअगरo_init,
	.पूर्णांकr = nv04_fअगरo_पूर्णांकr,
	.engine_id = nv04_fअगरo_engine_id,
	.id_engine = nv04_fअगरo_id_engine,
	.छोड़ो = nv04_fअगरo_छोड़ो,
	.start = nv04_fअगरo_start,
	.chan = अणु
		&nv50_fअगरo_dma_oclass,
		&nv50_fअगरo_gpfअगरo_oclass,
		शून्य
	पूर्ण,
पूर्ण;

पूर्णांक
nv50_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस nv50_fअगरo_new_(&nv50_fअगरo, device, type, inst, pfअगरo);
पूर्ण
