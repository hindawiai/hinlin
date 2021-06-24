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

अटल पूर्णांक
nv50_fअगरo_chan_engine_addr(काष्ठा nvkm_engine *engine)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_DMAOBJ:
	हाल NVKM_ENGINE_SW    : वापस -1;
	हाल NVKM_ENGINE_GR    : वापस 0x0000;
	हाल NVKM_ENGINE_MPEG  : वापस 0x0060;
	शेष:
		WARN_ON(1);
		वापस -1;
	पूर्ण
पूर्ण

काष्ठा nvkm_gpuobj **
nv50_fअगरo_chan_engine(काष्ठा nv50_fअगरo_chan *chan, काष्ठा nvkm_engine *engine)
अणु
	पूर्णांक engi = chan->base.fअगरo->func->engine_id(chan->base.fअगरo, engine);
	अगर (engi >= 0)
		वापस &chan->engn[engi];
	वापस शून्य;
पूर्ण

अटल पूर्णांक
nv50_fअगरo_chan_engine_fini(काष्ठा nvkm_fअगरo_chan *base,
			   काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	काष्ठा nv50_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक offset, ret = 0;
	u32 me;

	offset = nv50_fअगरo_chan_engine_addr(engine);
	अगर (offset < 0)
		वापस 0;

	/* HW bug workaround:
	 *
	 * PFIFO will hang क्रमever अगर the connected engines करोn't report
	 * that they've processed the context चयन request.
	 *
	 * In order क्रम the kickoff to work, we need to ensure all the
	 * connected engines are in a state where they can answer.
	 *
	 * Newer chipsets करोn't seem to suffer from this issue, and well,
	 * there's also a "ignore these engines" biपंचांगask reg we can use
	 * अगर we hit the issue there..
	 */
	me = nvkm_mask(device, 0x00b860, 0x00000001, 0x00000001);

	/* करो the kickoff... */
	nvkm_wr32(device, 0x0032fc, chan->base.inst->addr >> 12);
	अगर (nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x0032fc) != 0xffffffff)
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "channel %d [%s] unload timeout\n",
			   chan->base.chid, chan->base.object.client->name);
		अगर (suspend)
			ret = -EBUSY;
	पूर्ण
	nvkm_wr32(device, 0x00b860, me);

	अगर (ret == 0) अणु
		nvkm_kmap(chan->eng);
		nvkm_wo32(chan->eng, offset + 0x00, 0x00000000);
		nvkm_wo32(chan->eng, offset + 0x04, 0x00000000);
		nvkm_wo32(chan->eng, offset + 0x08, 0x00000000);
		nvkm_wo32(chan->eng, offset + 0x0c, 0x00000000);
		nvkm_wo32(chan->eng, offset + 0x10, 0x00000000);
		nvkm_wo32(chan->eng, offset + 0x14, 0x00000000);
		nvkm_करोne(chan->eng);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
nv50_fअगरo_chan_engine_init(काष्ठा nvkm_fअगरo_chan *base,
			   काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	काष्ठा nvkm_gpuobj *engn = *nv50_fअगरo_chan_engine(chan, engine);
	u64 limit, start;
	पूर्णांक offset;

	offset = nv50_fअगरo_chan_engine_addr(engine);
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

व्योम
nv50_fअगरo_chan_engine_dtor(काष्ठा nvkm_fअगरo_chan *base,
			   काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	nvkm_gpuobj_del(nv50_fअगरo_chan_engine(chan, engine));
पूर्ण

अटल पूर्णांक
nv50_fअगरo_chan_engine_ctor(काष्ठा nvkm_fअगरo_chan *base,
			   काष्ठा nvkm_engine *engine,
			   काष्ठा nvkm_object *object)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);

	अगर (nv50_fअगरo_chan_engine_addr(engine) < 0)
		वापस 0;

	वापस nvkm_object_bind(object, शून्य, 0, nv50_fअगरo_chan_engine(chan, engine));
पूर्ण

व्योम
nv50_fअगरo_chan_object_dtor(काष्ठा nvkm_fअगरo_chan *base, पूर्णांक cookie)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	nvkm_ramht_हटाओ(chan->ramht, cookie);
पूर्ण

अटल पूर्णांक
nv50_fअगरo_chan_object_ctor(काष्ठा nvkm_fअगरo_chan *base,
			   काष्ठा nvkm_object *object)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	u32 handle = object->handle;
	u32 context;

	चयन (object->engine->subdev.type) अणु
	हाल NVKM_ENGINE_DMAOBJ:
	हाल NVKM_ENGINE_SW    : context = 0x00000000; अवरोध;
	हाल NVKM_ENGINE_GR    : context = 0x00100000; अवरोध;
	हाल NVKM_ENGINE_MPEG  : context = 0x00200000; अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	वापस nvkm_ramht_insert(chan->ramht, object, 0, 4, handle, context);
पूर्ण

व्योम
nv50_fअगरo_chan_fini(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	काष्ठा nv50_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 chid = chan->base.chid;

	/* हटाओ channel from runlist, fअगरo will unload context */
	nvkm_mask(device, 0x002600 + (chid * 4), 0x80000000, 0x00000000);
	nv50_fअगरo_runlist_update(fअगरo);
	nvkm_wr32(device, 0x002600 + (chid * 4), 0x00000000);
पूर्ण

अटल व्योम
nv50_fअगरo_chan_init(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	काष्ठा nv50_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u64 addr = chan->ramfc->addr >> 12;
	u32 chid = chan->base.chid;

	nvkm_wr32(device, 0x002600 + (chid * 4), 0x80000000 | addr);
	nv50_fअगरo_runlist_update(fअगरo);
पूर्ण

व्योम *
nv50_fअगरo_chan_dtor(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा nv50_fअगरo_chan *chan = nv50_fअगरo_chan(base);
	nvkm_ramht_del(&chan->ramht);
	nvkm_gpuobj_del(&chan->pgd);
	nvkm_gpuobj_del(&chan->eng);
	nvkm_gpuobj_del(&chan->cache);
	nvkm_gpuobj_del(&chan->ramfc);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_chan_func
nv50_fअगरo_chan_func = अणु
	.dtor = nv50_fअगरo_chan_dtor,
	.init = nv50_fअगरo_chan_init,
	.fini = nv50_fअगरo_chan_fini,
	.engine_ctor = nv50_fअगरo_chan_engine_ctor,
	.engine_dtor = nv50_fअगरo_chan_engine_dtor,
	.engine_init = nv50_fअगरo_chan_engine_init,
	.engine_fini = nv50_fअगरo_chan_engine_fini,
	.object_ctor = nv50_fअगरo_chan_object_ctor,
	.object_dtor = nv50_fअगरo_chan_object_dtor,
पूर्ण;

पूर्णांक
nv50_fअगरo_chan_ctor(काष्ठा nv50_fअगरo *fअगरo, u64 vmm, u64 push,
		    स्थिर काष्ठा nvkm_oclass *oclass,
		    काष्ठा nv50_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक ret;

	अगर (!vmm)
		वापस -EINVAL;

	ret = nvkm_fअगरo_chan_ctor(&nv50_fअगरo_chan_func, &fअगरo->base,
				  0x10000, 0x1000, false, vmm, push,
				  BIT(NV50_FIFO_ENGN_SW) |
				  BIT(NV50_FIFO_ENGN_GR) |
				  BIT(NV50_FIFO_ENGN_MPEG) |
				  BIT(NV50_FIFO_ENGN_DMA),
				  0, 0xc00000, 0x2000, oclass, &chan->base);
	chan->fअगरo = fअगरo;
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x0200, 0x1000, true, chan->base.inst,
			      &chan->ramfc);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x1200, 0, true, chan->base.inst,
			      &chan->eng);
	अगर (ret)
		वापस ret;

	ret = nvkm_gpuobj_new(device, 0x4000, 0, false, chan->base.inst,
			      &chan->pgd);
	अगर (ret)
		वापस ret;

	वापस nvkm_ramht_new(device, 0x8000, 16, chan->base.inst, &chan->ramht);
पूर्ण
