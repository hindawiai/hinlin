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
#समावेश <core/gpuobj.h>
#समावेश <subdev/insपंचांगem.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl006b.h>
#समावेश <nvअगर/unpack.h>

अटल पूर्णांक
nv17_fअगरo_dma_new(काष्ठा nvkm_fअगरo *base, स्थिर काष्ठा nvkm_oclass *oclass,
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
				  BIT(NV04_FIFO_ENGN_MPEG) | /* NV31- */
				  BIT(NV04_FIFO_ENGN_DMA),
				  0, 0x800000, 0x10000, oclass, &chan->base);
	chan->fअगरo = fअगरo;
	अगर (ret)
		वापस ret;

	args->v0.chid = chan->base.chid;
	chan->ramfc = chan->base.chid * 64;

	nvkm_kmap(imem->ramfc);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x00, args->v0.offset);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x04, args->v0.offset);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x0c, chan->base.push->addr >> 4);
	nvkm_wo32(imem->ramfc, chan->ramfc + 0x14,
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
nv17_fअगरo_dma_oclass = अणु
	.base.oclass = NV17_CHANNEL_DMA,
	.base.minver = 0,
	.base.maxver = 0,
	.ctor = nv17_fअगरo_dma_new,
पूर्ण;
