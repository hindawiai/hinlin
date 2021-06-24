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
#समावेश "channv04.h"
#समावेश "regsnv04.h"

#समावेश <core/client.h>
#समावेश <core/ramht.h>
#समावेश <subdev/insपंचांगem.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl006b.h>
#समावेश <nvअगर/unpack.h>

अटल bool
nv40_fअगरo_dma_engine(काष्ठा nvkm_engine *engine, u32 *reg, u32 *ctx)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_DMAOBJ:
	हाल NVKM_ENGINE_SW:
		वापस false;
	हाल NVKM_ENGINE_GR:
		*reg = 0x0032e0;
		*ctx = 0x38;
		वापस true;
	हाल NVKM_ENGINE_MPEG:
		अगर (engine->subdev.device->chipset < 0x44)
			वापस false;
		*reg = 0x00330c;
		*ctx = 0x54;
		वापस true;
	शेष:
		WARN_ON(1);
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा nvkm_gpuobj **
nv40_fअगरo_dma_engn(काष्ठा nv04_fअगरo_chan *chan, काष्ठा nvkm_engine *engine)
अणु
	पूर्णांक engi = chan->base.fअगरo->func->engine_id(chan->base.fअगरo, engine);
	अगर (engi >= 0)
		वापस &chan->engn[engi];
	वापस शून्य;
पूर्ण

अटल पूर्णांक
nv40_fअगरo_dma_engine_fini(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nv04_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	अचिन्हित दीर्घ flags;
	u32 reg, ctx;
	पूर्णांक chid;

	अगर (!nv40_fअगरo_dma_engine(engine, &reg, &ctx))
		वापस 0;

	spin_lock_irqsave(&fअगरo->base.lock, flags);
	nvkm_mask(device, 0x002500, 0x00000001, 0x00000000);

	chid = nvkm_rd32(device, 0x003204) & (fअगरo->base.nr - 1);
	अगर (chid == chan->base.chid)
		nvkm_wr32(device, reg, 0x00000000);
	nvkm_kmap(imem->ramfc);
	nvkm_wo32(imem->ramfc, chan->ramfc + ctx, 0x00000000);
	nvkm_करोne(imem->ramfc);

	nvkm_mask(device, 0x002500, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv40_fअगरo_dma_engine_init(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nv04_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	अचिन्हित दीर्घ flags;
	u32 inst, reg, ctx;
	पूर्णांक chid;

	अगर (!nv40_fअगरo_dma_engine(engine, &reg, &ctx))
		वापस 0;
	inst = (*nv40_fअगरo_dma_engn(chan, engine))->addr >> 4;

	spin_lock_irqsave(&fअगरo->base.lock, flags);
	nvkm_mask(device, 0x002500, 0x00000001, 0x00000000);

	chid = nvkm_rd32(device, 0x003204) & (fअगरo->base.nr - 1);
	अगर (chid == chan->base.chid)
		nvkm_wr32(device, reg, inst);
	nvkm_kmap(imem->ramfc);
	nvkm_wo32(imem->ramfc, chan->ramfc + ctx, inst);
	nvkm_करोne(imem->ramfc);

	nvkm_mask(device, 0x002500, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
	वापस 0;
पूर्ण

अटल व्योम
nv40_fअगरo_dma_engine_dtor(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	nvkm_gpuobj_del(nv40_fअगरo_dma_engn(chan, engine));
पूर्ण

अटल पूर्णांक
nv40_fअगरo_dma_engine_ctor(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_engine *engine,
			  काष्ठा nvkm_object *object)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	u32 reg, ctx;

	अगर (!nv40_fअगरo_dma_engine(engine, &reg, &ctx))
		वापस 0;

	वापस nvkm_object_bind(object, शून्य, 0, nv40_fअगरo_dma_engn(chan, engine));
पूर्ण

अटल पूर्णांक
nv40_fअगरo_dma_object_ctor(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_object *object)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nvkm_insपंचांगem *imem = chan->fअगरo->base.engine.subdev.device->imem;
	u32 context = chan->base.chid << 23;
	u32 handle  = object->handle;
	पूर्णांक hash;

	चयन (object->engine->subdev.type) अणु
	हाल NVKM_ENGINE_DMAOBJ:
	हाल NVKM_ENGINE_SW    : context |= 0x00000000; अवरोध;
	हाल NVKM_ENGINE_GR    : context |= 0x00100000; अवरोध;
	हाल NVKM_ENGINE_MPEG  : context |= 0x00200000; अवरोध;
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&chan->fअगरo->base.mutex);
	hash = nvkm_ramht_insert(imem->ramht, object, chan->base.chid, 4,
				 handle, context);
	mutex_unlock(&chan->fअगरo->base.mutex);
	वापस hash;
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_chan_func
nv40_fअगरo_dma_func = अणु
	.dtor = nv04_fअगरo_dma_dtor,
	.init = nv04_fअगरo_dma_init,
	.fini = nv04_fअगरo_dma_fini,
	.engine_ctor = nv40_fअगरo_dma_engine_ctor,
	.engine_dtor = nv40_fअगरo_dma_engine_dtor,
	.engine_init = nv40_fअगरo_dma_engine_init,
	.engine_fini = nv40_fअगरo_dma_engine_fini,
	.object_ctor = nv40_fअगरo_dma_object_ctor,
	.object_dtor = nv04_fअगरo_dma_object_dtor,
पूर्ण;

अटल पूर्णांक
nv40_fअगरo_dma_new(काष्ठा nvkm_fअगरo *base, स्थिर काष्ठा nvkm_oclass *oclass,
		  व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_object *parent = oclass->parent;
	जोड़ अणु
		काष्ठा nv03_channel_dma_v0 v0;
	पूर्ण *args = data;
	काष्ठा nv04_fअगरo *fअगरo = nv04_fअगरo(base);
	काष्ठा nv04_fअगरo_chan *chan = शून्य;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(parent, "create channel dma size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create channel dma vers %d pushbuf %llx "
				   "offset %08x\n", args->v0.version,
			   args->v0.pushbuf, args->v0.offset);
		अगर (!args->v0.pushbuf)
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस ret;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &chan->base.object;

	ret = nvkm_fअगरo_chan_ctor(&nv40_fअगरo_dma_func, &fअगरo->base,
				  0x1000, 0x1000, false, 0, args->v0.pushbuf,
				  BIT(NV04_FIFO_ENGN_SW) |
				  BIT(NV04_FIFO_ENGN_GR) |
				  BIT(NV04_FIFO_ENGN_MPEG) |
				  BIT(NV04_FIFO_ENGN_DMA),
				  0, 0xc00000, 0x1000, oclass, &chan->base);
	chan->fअगरo = fअगरo;
	अगर (ret)
		वापस ret;

	args->v0.chid = chan->base.chid;
	chan->ramfc = chan->base.chid * 128;

	nvkm_kmap(imem->ramfc);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x00, args->v0.offset);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x04, args->v0.offset);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x0c, chan->base.push->addr >> 4);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x18, 0x30000000 |
			       NV_PFIFO_CACHE1_DMA_FETCH_TRIG_128_BYTES |
			       NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES |
#अगर_घोषित __BIG_ENDIAN
			       NV_PFIFO_CACHE1_BIG_ENDIAN |
#पूर्ण_अगर
			       NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_8);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x3c, 0x0001ffff);
	nvkm_करोne(imem->ramfc);
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_fअगरo_chan_oclass
nv40_fअगरo_dma_oclass = अणु
	.base.oclass = NV40_CHANNEL_DMA,
	.base.minver = 0,
	.base.maxver = 0,
	.ctor = nv40_fअगरo_dma_new,
पूर्ण;
