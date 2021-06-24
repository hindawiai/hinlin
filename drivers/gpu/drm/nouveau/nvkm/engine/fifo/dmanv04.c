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

व्योम
nv04_fअगरo_dma_object_dtor(काष्ठा nvkm_fअगरo_chan *base, पूर्णांक cookie)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nvkm_insपंचांगem *imem = chan->fअगरo->base.engine.subdev.device->imem;

	mutex_lock(&chan->fअगरo->base.mutex);
	nvkm_ramht_हटाओ(imem->ramht, cookie);
	mutex_unlock(&chan->fअगरo->base.mutex);
पूर्ण

अटल पूर्णांक
nv04_fअगरo_dma_object_ctor(काष्ठा nvkm_fअगरo_chan *base,
			  काष्ठा nvkm_object *object)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nvkm_insपंचांगem *imem = chan->fअगरo->base.engine.subdev.device->imem;
	u32 context = 0x80000000 | chan->base.chid << 24;
	u32 handle  = object->handle;
	पूर्णांक hash;

	चयन (object->engine->subdev.type) अणु
	हाल NVKM_ENGINE_DMAOBJ:
	हाल NVKM_ENGINE_SW    : context |= 0x00000000; अवरोध;
	हाल NVKM_ENGINE_GR    : context |= 0x00010000; अवरोध;
	हाल NVKM_ENGINE_MPEG  : context |= 0x00020000; अवरोध;
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

व्योम
nv04_fअगरo_dma_fini(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nv04_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_memory *fctx = device->imem->ramfc;
	स्थिर काष्ठा nv04_fअगरo_ramfc *c;
	अचिन्हित दीर्घ flags;
	u32 mask = fअगरo->base.nr - 1;
	u32 data = chan->ramfc;
	u32 chid;

	/* prevent fअगरo context चयनes */
	spin_lock_irqsave(&fअगरo->base.lock, flags);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 0);

	/* अगर this channel is active, replace it with a null context */
	chid = nvkm_rd32(device, NV03_PFIFO_CACHE1_PUSH1) & mask;
	अगर (chid == chan->base.chid) अणु
		nvkm_mask(device, NV04_PFIFO_CACHE1_DMA_PUSH, 0x00000001, 0);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 0);
		nvkm_mask(device, NV04_PFIFO_CACHE1_PULL0, 0x00000001, 0);

		c = fअगरo->ramfc;
		nvkm_kmap(fctx);
		करो अणु
			u32 rm = ((1ULL << c->bits) - 1) << c->regs;
			u32 cm = ((1ULL << c->bits) - 1) << c->ctxs;
			u32 rv = (nvkm_rd32(device, c->regp) &  rm) >> c->regs;
			u32 cv = (nvkm_ro32(fctx, c->ctxp + data) & ~cm);
			nvkm_wo32(fctx, c->ctxp + data, cv | (rv << c->ctxs));
		पूर्ण जबतक ((++c)->bits);
		nvkm_करोne(fctx);

		c = fअगरo->ramfc;
		करो अणु
			nvkm_wr32(device, c->regp, 0x00000000);
		पूर्ण जबतक ((++c)->bits);

		nvkm_wr32(device, NV03_PFIFO_CACHE1_GET, 0);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUT, 0);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH1, mask);
		nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
		nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
	पूर्ण

	/* restore normal operation, after disabling dma mode */
	nvkm_mask(device, NV04_PFIFO_MODE, 1 << chan->base.chid, 0);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 1);
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

व्योम
nv04_fअगरo_dma_init(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nv04_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 mask = 1 << chan->base.chid;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&fअगरo->base.lock, flags);
	nvkm_mask(device, NV04_PFIFO_MODE, mask, mask);
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

व्योम *
nv04_fअगरo_dma_dtor(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा nv04_fअगरo_chan *chan = nv04_fअगरo_chan(base);
	काष्ठा nv04_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_insपंचांगem *imem = fअगरo->base.engine.subdev.device->imem;
	स्थिर काष्ठा nv04_fअगरo_ramfc *c = fअगरo->ramfc;

	nvkm_kmap(imem->ramfc);
	करो अणु
		nvkm_wo32(imem->ramfc, chan->ramfc + c->ctxp, 0x00000000);
	पूर्ण जबतक ((++c)->bits);
	nvkm_करोne(imem->ramfc);
	वापस chan;
पूर्ण

स्थिर काष्ठा nvkm_fअगरo_chan_func
nv04_fअगरo_dma_func = अणु
	.dtor = nv04_fअगरo_dma_dtor,
	.init = nv04_fअगरo_dma_init,
	.fini = nv04_fअगरo_dma_fini,
	.object_ctor = nv04_fअगरo_dma_object_ctor,
	.object_dtor = nv04_fअगरo_dma_object_dtor,
पूर्ण;

अटल पूर्णांक
nv04_fअगरo_dma_new(काष्ठा nvkm_fअगरo *base, स्थिर काष्ठा nvkm_oclass *oclass,
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

	ret = nvkm_fअगरo_chan_ctor(&nv04_fअगरo_dma_func, &fअगरo->base,
				  0x1000, 0x1000, false, 0, args->v0.pushbuf,
				  BIT(NV04_FIFO_ENGN_SW) |
				  BIT(NV04_FIFO_ENGN_GR) |
				  BIT(NV04_FIFO_ENGN_DMA),
				  0, 0x800000, 0x10000, oclass, &chan->base);
	chan->fअगरo = fअगरo;
	अगर (ret)
		वापस ret;

	args->v0.chid = chan->base.chid;
	chan->ramfc = chan->base.chid * 32;

	nvkm_kmap(imem->ramfc);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x00, args->v0.offset);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x04, args->v0.offset);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x08, chan->base.push->addr >> 4);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x10,
			       NV_PFIFO_CACHE1_DMA_FETCH_TRIG_128_BYTES |
			       NV_PFIFO_CACHE1_DMA_FETCH_SIZE_128_BYTES |
#अगर_घोषित __BIG_ENDIAN
			       NV_PFIFO_CACHE1_BIG_ENDIAN |
#पूर्ण_अगर
			       NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_8);
	nvkm_करोne(imem->ramfc);
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_fअगरo_chan_oclass
nv04_fअगरo_dma_oclass = अणु
	.base.oclass = NV03_CHANNEL_DMA,
	.base.minver = 0,
	.base.maxver = 0,
	.ctor = nv04_fअगरo_dma_new,
पूर्ण;
