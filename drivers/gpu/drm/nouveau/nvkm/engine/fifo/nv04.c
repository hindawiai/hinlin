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

#समावेश <core/client.h>
#समावेश <core/ramht.h>
#समावेश <subdev/insपंचांगem.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/sw.h>

अटल स्थिर काष्ठा nv04_fअगरo_ramfc
nv04_fअगरo_ramfc[] = अणु
	अणु 32,  0, 0x00,  0, NV04_PFIFO_CACHE1_DMA_PUT पूर्ण,
	अणु 32,  0, 0x04,  0, NV04_PFIFO_CACHE1_DMA_GET पूर्ण,
	अणु 16,  0, 0x08,  0, NV04_PFIFO_CACHE1_DMA_INSTANCE पूर्ण,
	अणु 16, 16, 0x08,  0, NV04_PFIFO_CACHE1_DMA_DCOUNT पूर्ण,
	अणु 32,  0, 0x0c,  0, NV04_PFIFO_CACHE1_DMA_STATE पूर्ण,
	अणु 32,  0, 0x10,  0, NV04_PFIFO_CACHE1_DMA_FETCH पूर्ण,
	अणु 32,  0, 0x14,  0, NV04_PFIFO_CACHE1_ENGINE पूर्ण,
	अणु 32,  0, 0x18,  0, NV04_PFIFO_CACHE1_PULL1 पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
nv04_fअगरo_छोड़ो(काष्ठा nvkm_fअगरo *base, अचिन्हित दीर्घ *pflags)
__acquires(fअगरo->base.lock)
अणु
	काष्ठा nv04_fअगरo *fअगरo = nv04_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fअगरo->base.lock, flags);
	*pflags = flags;

	nvkm_wr32(device, NV03_PFIFO_CACHES, 0x00000000);
	nvkm_mask(device, NV04_PFIFO_CACHE1_PULL0, 0x00000001, 0x00000000);

	/* in some हालs the puller may be left in an inconsistent state
	 * अगर you try to stop it जबतक it's busy translating handles.
	 * someबार you get a CACHE_ERROR, someबार it just fails
	 * silently; sending incorrect instance offsets to PGRAPH after
	 * it's started up again.
	 *
	 * to aव्योम this, we invalidate the most recently calculated
	 * instance.
	 */
	nvkm_msec(device, 2000,
		u32 पंचांगp = nvkm_rd32(device, NV04_PFIFO_CACHE1_PULL0);
		अगर (!(पंचांगp & NV04_PFIFO_CACHE1_PULL0_HASH_BUSY))
			अवरोध;
	);

	अगर (nvkm_rd32(device, NV04_PFIFO_CACHE1_PULL0) &
			  NV04_PFIFO_CACHE1_PULL0_HASH_FAILED)
		nvkm_wr32(device, NV03_PFIFO_INTR_0, NV_PFIFO_INTR_CACHE_ERROR);

	nvkm_wr32(device, NV04_PFIFO_CACHE1_HASH, 0x00000000);
पूर्ण

व्योम
nv04_fअगरo_start(काष्ठा nvkm_fअगरo *base, अचिन्हित दीर्घ *pflags)
__releases(fअगरo->base.lock)
अणु
	काष्ठा nv04_fअगरo *fअगरo = nv04_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	अचिन्हित दीर्घ flags = *pflags;

	nvkm_mask(device, NV04_PFIFO_CACHE1_PULL0, 0x00000001, 0x00000001);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 0x00000001);

	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

काष्ठा nvkm_engine *
nv04_fअगरo_id_engine(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक engi)
अणु
	क्रमागत nvkm_subdev_type type;

	चयन (engi) अणु
	हाल NV04_FIFO_ENGN_SW  : type = NVKM_ENGINE_SW; अवरोध;
	हाल NV04_FIFO_ENGN_GR  : type = NVKM_ENGINE_GR; अवरोध;
	हाल NV04_FIFO_ENGN_MPEG: type = NVKM_ENGINE_MPEG; अवरोध;
	हाल NV04_FIFO_ENGN_DMA : type = NVKM_ENGINE_DMAOBJ; अवरोध;
	शेष:
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	वापस nvkm_device_engine(fअगरo->engine.subdev.device, type, 0);
पूर्ण

पूर्णांक
nv04_fअगरo_engine_id(काष्ठा nvkm_fअगरo *base, काष्ठा nvkm_engine *engine)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_SW    : वापस NV04_FIFO_ENGN_SW;
	हाल NVKM_ENGINE_GR    : वापस NV04_FIFO_ENGN_GR;
	हाल NVKM_ENGINE_MPEG  : वापस NV04_FIFO_ENGN_MPEG;
	हाल NVKM_ENGINE_DMAOBJ: वापस NV04_FIFO_ENGN_DMA;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
nv_dma_state_err(u32 state)
अणु
	अटल स्थिर अक्षर * स्थिर desc[] = अणु
		"NONE", "CALL_SUBR_ACTIVE", "INVALID_MTHD", "RET_SUBR_INACTIVE",
		"INVALID_CMD", "IB_EMPTY"/* NV50+ */, "MEM_FAULT", "UNK"
	पूर्ण;
	वापस desc[(state >> 29) & 0x7];
पूर्ण

अटल bool
nv04_fअगरo_swmthd(काष्ठा nvkm_device *device, u32 chid, u32 addr, u32 data)
अणु
	काष्ठा nvkm_sw *sw = device->sw;
	स्थिर पूर्णांक subc = (addr & 0x0000e000) >> 13;
	स्थिर पूर्णांक mthd = (addr & 0x00001ffc);
	स्थिर u32 mask = 0x0000000f << (subc * 4);
	u32 engine = nvkm_rd32(device, 0x003280);
	bool handled = false;

	चयन (mthd) अणु
	हाल 0x0000 ... 0x0000: /* subchannel's engine -> software */
		nvkm_wr32(device, 0x003280, (engine &= ~mask));
		fallthrough;
	हाल 0x0180 ... 0x01fc: /* handle -> instance */
		data = nvkm_rd32(device, 0x003258) & 0x0000ffff;
		fallthrough;
	हाल 0x0100 ... 0x017c:
	हाल 0x0200 ... 0x1ffc: /* pass method करोwn to sw */
		अगर (!(engine & mask) && sw)
			handled = nvkm_sw_mthd(sw, chid, subc, mthd, data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस handled;
पूर्ण

अटल व्योम
nv04_fअगरo_cache_error(काष्ठा nv04_fअगरo *fअगरo, u32 chid, u32 get)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	u32 pull0 = nvkm_rd32(device, 0x003250);
	u32 mthd, data;
	पूर्णांक ptr;

	/* NV_PFIFO_CACHE1_GET actually goes to 0xffc beक्रमe wrapping on my
	 * G80 chips, but CACHE1 isn't big enough क्रम this much data.. Tests
	 * show that it wraps around to the start at GET=0x800.. No clue as to
	 * why..
	 */
	ptr = (get & 0x7ff) >> 2;

	अगर (device->card_type < NV_40) अणु
		mthd = nvkm_rd32(device, NV04_PFIFO_CACHE1_METHOD(ptr));
		data = nvkm_rd32(device, NV04_PFIFO_CACHE1_DATA(ptr));
	पूर्ण अन्यथा अणु
		mthd = nvkm_rd32(device, NV40_PFIFO_CACHE1_METHOD(ptr));
		data = nvkm_rd32(device, NV40_PFIFO_CACHE1_DATA(ptr));
	पूर्ण

	अगर (!(pull0 & 0x00000100) ||
	    !nv04_fअगरo_swmthd(device, chid, mthd, data)) अणु
		chan = nvkm_fअगरo_chan_chid(&fअगरo->base, chid, &flags);
		nvkm_error(subdev, "CACHE_ERROR - "
			   "ch %d [%s] subc %d mthd %04x data %08x\n",
			   chid, chan ? chan->object.client->name : "unknown",
			   (mthd >> 13) & 7, mthd & 0x1ffc, data);
		nvkm_fअगरo_chan_put(&fअगरo->base, flags, &chan);
	पूर्ण

	nvkm_wr32(device, NV04_PFIFO_CACHE1_DMA_PUSH, 0);
	nvkm_wr32(device, NV03_PFIFO_INTR_0, NV_PFIFO_INTR_CACHE_ERROR);

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0,
		nvkm_rd32(device, NV03_PFIFO_CACHE1_PUSH0) & ~1);
	nvkm_wr32(device, NV03_PFIFO_CACHE1_GET, get + 4);
	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0,
		nvkm_rd32(device, NV03_PFIFO_CACHE1_PUSH0) | 1);
	nvkm_wr32(device, NV04_PFIFO_CACHE1_HASH, 0);

	nvkm_wr32(device, NV04_PFIFO_CACHE1_DMA_PUSH,
		nvkm_rd32(device, NV04_PFIFO_CACHE1_DMA_PUSH) | 1);
	nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
पूर्ण

अटल व्योम
nv04_fअगरo_dma_pusher(काष्ठा nv04_fअगरo *fअगरo, u32 chid)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 dma_get = nvkm_rd32(device, 0x003244);
	u32 dma_put = nvkm_rd32(device, 0x003240);
	u32 push = nvkm_rd32(device, 0x003220);
	u32 state = nvkm_rd32(device, 0x003228);
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *name;

	chan = nvkm_fअगरo_chan_chid(&fअगरo->base, chid, &flags);
	name = chan ? chan->object.client->name : "unknown";
	अगर (device->card_type == NV_50) अणु
		u32 ho_get = nvkm_rd32(device, 0x003328);
		u32 ho_put = nvkm_rd32(device, 0x003320);
		u32 ib_get = nvkm_rd32(device, 0x003334);
		u32 ib_put = nvkm_rd32(device, 0x003330);

		nvkm_error(subdev, "DMA_PUSHER - "
			   "ch %d [%s] get %02x%08x put %02x%08x ib_get %08x "
			   "ib_put %08x state %08x (err: %s) push %08x\n",
			   chid, name, ho_get, dma_get, ho_put, dma_put,
			   ib_get, ib_put, state, nv_dma_state_err(state),
			   push);

		/* METHOD_COUNT, in DMA_STATE on earlier chipsets */
		nvkm_wr32(device, 0x003364, 0x00000000);
		अगर (dma_get != dma_put || ho_get != ho_put) अणु
			nvkm_wr32(device, 0x003244, dma_put);
			nvkm_wr32(device, 0x003328, ho_put);
		पूर्ण अन्यथा
		अगर (ib_get != ib_put)
			nvkm_wr32(device, 0x003334, ib_put);
	पूर्ण अन्यथा अणु
		nvkm_error(subdev, "DMA_PUSHER - ch %d [%s] get %08x put %08x "
				   "state %08x (err: %s) push %08x\n",
			   chid, name, dma_get, dma_put, state,
			   nv_dma_state_err(state), push);

		अगर (dma_get != dma_put)
			nvkm_wr32(device, 0x003244, dma_put);
	पूर्ण
	nvkm_fअगरo_chan_put(&fअगरo->base, flags, &chan);

	nvkm_wr32(device, 0x003228, 0x00000000);
	nvkm_wr32(device, 0x003220, 0x00000001);
	nvkm_wr32(device, 0x002100, NV_PFIFO_INTR_DMA_PUSHER);
पूर्ण

व्योम
nv04_fअगरo_पूर्णांकr(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा nv04_fअगरo *fअगरo = nv04_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, NV03_PFIFO_INTR_EN_0);
	u32 stat = nvkm_rd32(device, NV03_PFIFO_INTR_0) & mask;
	u32 reassign, chid, get, sem;

	reassign = nvkm_rd32(device, NV03_PFIFO_CACHES) & 1;
	nvkm_wr32(device, NV03_PFIFO_CACHES, 0);

	chid = nvkm_rd32(device, NV03_PFIFO_CACHE1_PUSH1) & (fअगरo->base.nr - 1);
	get  = nvkm_rd32(device, NV03_PFIFO_CACHE1_GET);

	अगर (stat & NV_PFIFO_INTR_CACHE_ERROR) अणु
		nv04_fअगरo_cache_error(fअगरo, chid, get);
		stat &= ~NV_PFIFO_INTR_CACHE_ERROR;
	पूर्ण

	अगर (stat & NV_PFIFO_INTR_DMA_PUSHER) अणु
		nv04_fअगरo_dma_pusher(fअगरo, chid);
		stat &= ~NV_PFIFO_INTR_DMA_PUSHER;
	पूर्ण

	अगर (stat & NV_PFIFO_INTR_SEMAPHORE) अणु
		stat &= ~NV_PFIFO_INTR_SEMAPHORE;
		nvkm_wr32(device, NV03_PFIFO_INTR_0, NV_PFIFO_INTR_SEMAPHORE);

		sem = nvkm_rd32(device, NV10_PFIFO_CACHE1_SEMAPHORE);
		nvkm_wr32(device, NV10_PFIFO_CACHE1_SEMAPHORE, sem | 0x1);

		nvkm_wr32(device, NV03_PFIFO_CACHE1_GET, get + 4);
		nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
	पूर्ण

	अगर (device->card_type == NV_50) अणु
		अगर (stat & 0x00000010) अणु
			stat &= ~0x00000010;
			nvkm_wr32(device, 0x002100, 0x00000010);
		पूर्ण

		अगर (stat & 0x40000000) अणु
			nvkm_wr32(device, 0x002100, 0x40000000);
			nvkm_fअगरo_uevent(&fअगरo->base);
			stat &= ~0x40000000;
		पूर्ण
	पूर्ण

	अगर (stat) अणु
		nvkm_warn(subdev, "intr %08x\n", stat);
		nvkm_mask(device, NV03_PFIFO_INTR_EN_0, stat, 0x00000000);
		nvkm_wr32(device, NV03_PFIFO_INTR_0, stat);
	पूर्ण

	nvkm_wr32(device, NV03_PFIFO_CACHES, reassign);
पूर्ण

व्योम
nv04_fअगरo_init(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा nv04_fअगरo *fअगरo = nv04_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_insपंचांगem *imem = device->imem;
	काष्ठा nvkm_ramht *ramht = imem->ramht;
	काष्ठा nvkm_memory *ramro = imem->ramro;
	काष्ठा nvkm_memory *ramfc = imem->ramfc;

	nvkm_wr32(device, NV04_PFIFO_DELAY_0, 0x000000ff);
	nvkm_wr32(device, NV04_PFIFO_DMA_TIMESLICE, 0x0101ffff);

	nvkm_wr32(device, NV03_PFIFO_RAMHT, (0x03 << 24) /* search 128 */ |
					    ((ramht->bits - 9) << 16) |
					    (ramht->gpuobj->addr >> 8));
	nvkm_wr32(device, NV03_PFIFO_RAMRO, nvkm_memory_addr(ramro) >> 8);
	nvkm_wr32(device, NV03_PFIFO_RAMFC, nvkm_memory_addr(ramfc) >> 8);

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH1, fअगरo->base.nr - 1);

	nvkm_wr32(device, NV03_PFIFO_INTR_0, 0xffffffff);
	nvkm_wr32(device, NV03_PFIFO_INTR_EN_0, 0xffffffff);

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
	nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 1);
पूर्ण

पूर्णांक
nv04_fअगरo_new_(स्थिर काष्ठा nvkm_fअगरo_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, पूर्णांक nr, स्थिर काष्ठा nv04_fअगरo_ramfc *ramfc,
	       काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	काष्ठा nv04_fअगरo *fअगरo;
	पूर्णांक ret;

	अगर (!(fअगरo = kzalloc(माप(*fअगरo), GFP_KERNEL)))
		वापस -ENOMEM;
	fअगरo->ramfc = ramfc;
	*pfअगरo = &fअगरo->base;

	ret = nvkm_fअगरo_ctor(func, device, type, inst, nr, &fअगरo->base);
	अगर (ret)
		वापस ret;

	set_bit(nr - 1, fअगरo->base.mask); /* inactive channel */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_func
nv04_fअगरo = अणु
	.init = nv04_fअगरo_init,
	.पूर्णांकr = nv04_fअगरo_पूर्णांकr,
	.engine_id = nv04_fअगरo_engine_id,
	.id_engine = nv04_fअगरo_id_engine,
	.छोड़ो = nv04_fअगरo_छोड़ो,
	.start = nv04_fअगरo_start,
	.chan = अणु
		&nv04_fअगरo_dma_oclass,
		शून्य
	पूर्ण,
पूर्ण;

पूर्णांक
nv04_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस nv04_fअगरo_new_(&nv04_fअगरo, device, type, inst, 16, nv04_fअगरo_ramfc, pfअगरo);
पूर्ण
