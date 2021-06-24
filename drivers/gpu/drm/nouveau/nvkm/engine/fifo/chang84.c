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
#समावेश "channv50.h"

#समावेश <core/client.h>
#समावेश <core/ramht.h>
#समावेश <subdev/mmu.h>
#समावेश <subdev/समयr.h>

#समावेश <nvअगर/cl826e.h>

अटल पूर्णांक
g84_fअगरo_chan_ntfy(काष्ठा nvkm_fअगरo_chan *chan, u32 type,
		   काष्ठा nvkm_event **pevent)
अणु
	चयन (type) अणु
	हाल NV826E_V0_NTFY_NON_STALL_INTERRUPT:
		*pevent = &chan->fअगरo->uevent;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
g84_fअगरo_chan_engine_addr(काष्ठा nvkm_engine *engine)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_DMAOBJ:
	हाल NVKM_ENGINE_SW    : वापस -1;
	हाल NVKM_ENGINE_GR    : वापस 0x0020;
	हाल NVKM_ENGINE_VP    :
	हाल NVKM_ENGINE_MSPDEC: वापस 0x0040;
	हाल NVKM_ENGINE_MPEG  :
	हाल NVKM_ENGINE_MSPPP : वापस 0x0060;
	हाल NVKM_ENGINE_BSP   :
	हाल NVKM_ENGINE_MSVLD : वापस 0x0080;
	हाल NVKM_ENGINE_CIPHER:
	हाल NVKM_ENGINE_SEC   : वापस 0x00a0;
	हाल NVKM_ENGINE_CE    : वापस 0x00c0;
	शेष:
		WARN_ON(1);
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक
g84_fअगरo_chan_engine_fini(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	काष्ठा nv50_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 engn, save;
	पूर्णांक offset;
	bool करोne;

	offset = g84_fअगरo_chan_engine_addr(engine);
	अगर (offset < 0)
		वापस 0;

	engn = fअगरo->base.func->engine_id(&fअगरo->base, engine);
	save = nvkm_mask(device, 0x002520, 0x0000003f, 1 << engn);
	nvkm_wr32(device, 0x0032fc, chan->base.inst->addr >> 12);
	करोne = nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x0032fc) != 0xffffffff)
			अवरोध;
	) >= 0;
	nvkm_wr32(device, 0x002520, save);
	अगर (!करोne) अणु
		nvkm_error(subdev, "channel %d [%s] unload timeout\n",
			   chan->base.chid, chan->base.object.client->name);
		अगर (suspend)
			वापस -EBUSY;
	पूर्ण

	nvkm_kmap(chan->eng);
	nvkm_wo32(chan->eng, offset + 0x00, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x04, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x08, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x0c, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x10, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x14, 0x00000000);
	nvkm_करोne(chan->eng);
	वापस 0;
पूर्ण


अटल पूर्णांक
g84_fअगरo_chan_engine_init(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	काष्ठा nvkm_gpuobj *engn = *nv50_fअगरo_chan_engine(chan, engine);
	u64 limit, start;
	पूर्णांक offset;

	offset = g84_fअगरo_chan_engine_addr(engine);
	अगर (offset < 0)
		वापस 0;
	limit = engn->addr + engn->size - 1;
	start = engn->addr;

	nvkm_kmap(chan->eng);
	nvkm_wo32(chan->eng, offset + 0x00, 0x00190000);
	nvkm_wo32(chan->eng, offset + 0x04, lower_32_bits(limit));
	nvkm_wo32(chan->eng, offset + 0x08, lower_32_bits(start));
	nvkm_wo32(chan->eng, offset + 0x0c, upper_32_bits(limit) << 24 |
					    upper_32_bits(start));
	nvkm_wo32(chan->eng, offset + 0x10, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x14, 0x00000000);
	nvkm_करोne(chan->eng);
	वापस 0;
पूर्ण

अटल पूर्णांक
g84_fअगरo_chan_engine_ctor(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_engine *engine,
			  काष्ठा nvkm_object *object)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);

	अगर (g84_fअगरo_chan_engine_addr(engine) < 0)
		वापस 0;

	वापस nvkm_object_bind(object, शून्य, 0, nv50_fअगरo_chan_engine(chan, engine));
पूर्ण

अटल पूर्णांक
g84_fअगरo_chan_object_ctor(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_object *object)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	u32 handle = object->handle;
	u32 context;

	चयन (object->engine->subdev.type) अणु
	हाल NVKM_ENGINE_DMAOBJ:
	हाल NVKM_ENGINE_SW    : context = 0x00000000; अवरोध;
	हाल NVKM_ENGINE_GR    : context = 0x00100000; अवरोध;
	हाल NVKM_ENGINE_MPEG  :
	हाल NVKM_ENGINE_MSPPP : context = 0x00200000; अवरोध;
	हाल NVKM_ENGINE_ME    :
	हाल NVKM_ENGINE_CE    : context = 0x00300000; अवरोध;
	हाल NVKM_ENGINE_VP    :
	हाल NVKM_ENGINE_MSPDEC: context = 0x00400000; अवरोध;
	हाल NVKM_ENGINE_CIPHER:
	हाल NVKM_ENGINE_SEC   :
	हाल NVKM_ENGINE_VIC   : context = 0x00500000; अवरोध;
	हाल NVKM_ENGINE_BSP   :
	हाल NVKM_ENGINE_MSVLD : context = 0x00600000; अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	वापस nvkm_ramht_insert(chan->ramht, object, 0, 4, handle, context);
पूर्ण

अटल व्योम
g84_fअगरo_chan_init(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	काष्ठा nv50_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u64 addr = chan->ramfc->addr >> 8;
	u32 chid = chan->base.chid;

	nvkm_wr32(device, 0x002600 + (chid * 4), 0x80000000 | addr);
	nv50_fअगरo_runlist_update(fअगरo);
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_chan_func
g84_fअगरo_chan_func = अणु
	.dtor = nv50_fअगरo_chan_dtor,
	.init = g84_fअगरo_chan_init,
	.fini = nv50_fअगरo_chan_fini,
	.ntfy = g84_fअगरo_chan_ntfy,
	.engine_ctor = g84_fअगरo_chan_engine_ctor,
	.engine_dtor = nv50_fअगरo_chan_engine_dtor,
	.engine_init = g84_fअगरo_chan_engine_init,
	.engine_fini = g84_fअगरo_chan_engine_fini,
	.object_ctor = g84_fअगरo_chan_object_ctor,
	.object_dtor = nv50_fअगरo_chan_object_dtor,
पूर्ण;

पूर्णांक
g84_fअगरo_chan_ctor(काष्ठा nv50_fअगरo *fअगरo, u64 vmm, u64 push,
		   स्थिर काष्ठा nvkm_oclass *oclass,
		   काष्ठा nv50_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक ret;

	अगर (!vmm)
		वापस -EINVAL;

	ret = nvkm_fअगरo_chan_ctor(&g84_fअगरo_chan_func, &fअगरo->base,
				  0x10000, 0x1000, false, vmm, push,
				  BIT(G84_FIFO_ENGN_SW) |
				  BIT(G84_FIFO_ENGN_GR) |
				  BIT(G84_FIFO_ENGN_MPEG) |
				  BIT(G84_FIFO_ENGN_MSPPP) |
				  BIT(G84_FIFO_ENGN_ME) |
				  BIT(G84_FIFO_ENGN_CE0) |
				  BIT(G84_FIFO_ENGN_VP) |
				  BIT(G84_FIFO_ENGN_MSPDEC) |
				  BIT(G84_FIFO_ENGN_CIPHER) |
				  BIT(G84_FIFO_ENGN_SEC) |
				  BIT(G84_FIFO_ENGN_VIC) |
				  BIT(G84_FIFO_ENGN_BSP) |
				  BIT(G84_FIFO_ENGN_MSVLD) |
				  BIT(G84_FIFO_ENGN_DMA),
				  0, 0xc00000, 0x2000, oclass, &chan->base);
	chan->fअगरo = fअगरo;
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x0200, 0, true, chan->base.inst,
			      &chan->eng);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x4000, 0, false, chan->base.inst,
			      &chan->pgd);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x1000, 0x400, true, chan->base.inst,
			      &chan->cache);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x100, 0x100, true, chan->base.inst,
			      &chan->ramfc);
	अगर (ret)
		वापस ret;

	वापस nvkm_ramht_new(device, 0x8000, 16, chan->base.inst, &chan->ramht);
पूर्ण
