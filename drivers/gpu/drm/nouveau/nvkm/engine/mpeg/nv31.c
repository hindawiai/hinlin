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
#समावेश "nv31.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>

/*******************************************************************************
 * MPEG object classes
 ******************************************************************************/

अटल पूर्णांक
nv31_mpeg_object_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		      पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	पूर्णांक ret = nvkm_gpuobj_new(object->engine->subdev.device, 16, align,
				  false, parent, pgpuobj);
	अगर (ret == 0) अणु
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x00, object->oclass);
		nvkm_wo32(*pgpuobj, 0x04, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x08, 0x00000000);
		nvkm_wo32(*pgpuobj, 0x0c, 0x00000000);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा nvkm_object_func
nv31_mpeg_object = अणु
	.bind = nv31_mpeg_object_bind,
पूर्ण;

/*******************************************************************************
 * PMPEG context
 ******************************************************************************/

अटल व्योम *
nv31_mpeg_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv31_mpeg_chan *chan = nv31_mpeg_chan(object);
	काष्ठा nv31_mpeg *mpeg = chan->mpeg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mpeg->engine.lock, flags);
	अगर (mpeg->chan == chan)
		mpeg->chan = शून्य;
	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv31_mpeg_chan = अणु
	.dtor = nv31_mpeg_chan_dtor,
पूर्ण;

पूर्णांक
nv31_mpeg_chan_new(काष्ठा nvkm_fअगरo_chan *fअगरoch,
		   स्थिर काष्ठा nvkm_oclass *oclass,
		   काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv31_mpeg *mpeg = nv31_mpeg(oclass->engine);
	काष्ठा nv31_mpeg_chan *chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EBUSY;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv31_mpeg_chan, oclass, &chan->object);
	chan->mpeg = mpeg;
	chan->fअगरo = fअगरoch;
	*pobject = &chan->object;

	spin_lock_irqsave(&mpeg->engine.lock, flags);
	अगर (!mpeg->chan) अणु
		mpeg->chan = chan;
		ret = 0;
	पूर्ण
	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
	वापस ret;
पूर्ण

/*******************************************************************************
 * PMPEG engine/subdev functions
 ******************************************************************************/

व्योम
nv31_mpeg_tile(काष्ठा nvkm_engine *engine, पूर्णांक i, काष्ठा nvkm_fb_tile *tile)
अणु
	काष्ठा nv31_mpeg *mpeg = nv31_mpeg(engine);
	काष्ठा nvkm_device *device = mpeg->engine.subdev.device;

	nvkm_wr32(device, 0x00b008 + (i * 0x10), tile->pitch);
	nvkm_wr32(device, 0x00b004 + (i * 0x10), tile->limit);
	nvkm_wr32(device, 0x00b000 + (i * 0x10), tile->addr);
पूर्ण

अटल bool
nv31_mpeg_mthd_dma(काष्ठा nvkm_device *device, u32 mthd, u32 data)
अणु
	काष्ठा nv31_mpeg *mpeg = nv31_mpeg(device->mpeg);
	काष्ठा nvkm_subdev *subdev = &mpeg->engine.subdev;
	u32 inst = data << 4;
	u32 dma0 = nvkm_rd32(device, 0x700000 + inst);
	u32 dma1 = nvkm_rd32(device, 0x700004 + inst);
	u32 dma2 = nvkm_rd32(device, 0x700008 + inst);
	u32 base = (dma2 & 0xfffff000) | (dma0 >> 20);
	u32 size = dma1 + 1;

	/* only allow linear DMA objects */
	अगर (!(dma0 & 0x00002000)) अणु
		nvkm_error(subdev, "inst %08x dma0 %08x dma1 %08x dma2 %08x\n",
			   inst, dma0, dma1, dma2);
		वापस false;
	पूर्ण

	अगर (mthd == 0x0190) अणु
		/* DMA_CMD */
		nvkm_mask(device, 0x00b300, 0x00010000,
				  (dma0 & 0x00030000) ? 0x00010000 : 0);
		nvkm_wr32(device, 0x00b334, base);
		nvkm_wr32(device, 0x00b324, size);
	पूर्ण अन्यथा
	अगर (mthd == 0x01a0) अणु
		/* DMA_DATA */
		nvkm_mask(device, 0x00b300, 0x00020000,
				  (dma0 & 0x00030000) ? 0x00020000 : 0);
		nvkm_wr32(device, 0x00b360, base);
		nvkm_wr32(device, 0x00b364, size);
	पूर्ण अन्यथा अणु
		/* DMA_IMAGE, VRAM only */
		अगर (dma0 & 0x00030000)
			वापस false;

		nvkm_wr32(device, 0x00b370, base);
		nvkm_wr32(device, 0x00b374, size);
	पूर्ण

	वापस true;
पूर्ण

अटल bool
nv31_mpeg_mthd(काष्ठा nv31_mpeg *mpeg, u32 mthd, u32 data)
अणु
	काष्ठा nvkm_device *device = mpeg->engine.subdev.device;
	चयन (mthd) अणु
	हाल 0x190:
	हाल 0x1a0:
	हाल 0x1b0:
		वापस mpeg->func->mthd_dma(device, mthd, data);
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम
nv31_mpeg_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nv31_mpeg *mpeg = nv31_mpeg(engine);
	काष्ठा nvkm_subdev *subdev = &mpeg->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x00b100);
	u32 type = nvkm_rd32(device, 0x00b230);
	u32 mthd = nvkm_rd32(device, 0x00b234);
	u32 data = nvkm_rd32(device, 0x00b238);
	u32 show = stat;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mpeg->engine.lock, flags);

	अगर (stat & 0x01000000) अणु
		/* happens on initial binding of the object */
		अगर (type == 0x00000020 && mthd == 0x0000) अणु
			nvkm_mask(device, 0x00b308, 0x00000000, 0x00000000);
			show &= ~0x01000000;
		पूर्ण

		अगर (type == 0x00000010) अणु
			अगर (nv31_mpeg_mthd(mpeg, mthd, data))
				show &= ~0x01000000;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x00b100, stat);
	nvkm_wr32(device, 0x00b230, 0x00000001);

	अगर (show) अणु
		nvkm_error(subdev, "ch %d [%s] %08x %08x %08x %08x\n",
			   mpeg->chan ? mpeg->chan->fअगरo->chid : -1,
			   mpeg->chan ? mpeg->chan->object.client->name :
			   "unknown", stat, type, mthd, data);
	पूर्ण

	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
पूर्ण

पूर्णांक
nv31_mpeg_init(काष्ठा nvkm_engine *mpeg)
अणु
	काष्ठा nvkm_subdev *subdev = &mpeg->subdev;
	काष्ठा nvkm_device *device = subdev->device;

	/* VPE init */
	nvkm_wr32(device, 0x00b0e0, 0x00000020); /* nvidia: rd 0x01, wr 0x20 */
	nvkm_wr32(device, 0x00b0e8, 0x00000020); /* nvidia: rd 0x01, wr 0x20 */

	/* PMPEG init */
	nvkm_wr32(device, 0x00b32c, 0x00000000);
	nvkm_wr32(device, 0x00b314, 0x00000100);
	nvkm_wr32(device, 0x00b220, 0x00000031);
	nvkm_wr32(device, 0x00b300, 0x02001ec1);
	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000001);

	nvkm_wr32(device, 0x00b100, 0xffffffff);
	nvkm_wr32(device, 0x00b140, 0xffffffff);

	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x00b200) & 0x00000001))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "timeout %08x\n",
			   nvkm_rd32(device, 0x00b200));
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *
nv31_mpeg_dtor(काष्ठा nvkm_engine *engine)
अणु
	वापस nv31_mpeg(engine);
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nv31_mpeg_ = अणु
	.dtor = nv31_mpeg_dtor,
	.init = nv31_mpeg_init,
	.पूर्णांकr = nv31_mpeg_पूर्णांकr,
	.tile = nv31_mpeg_tile,
	.fअगरo.cclass = nv31_mpeg_chan_new,
	.sclass = अणु
		अणु -1, -1, NV31_MPEG, &nv31_mpeg_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv31_mpeg_new_(स्थिर काष्ठा nv31_mpeg_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_engine **pmpeg)
अणु
	काष्ठा nv31_mpeg *mpeg;

	अगर (!(mpeg = kzalloc(माप(*mpeg), GFP_KERNEL)))
		वापस -ENOMEM;
	mpeg->func = func;
	*pmpeg = &mpeg->engine;

	वापस nvkm_engine_ctor(&nv31_mpeg_, device, type, inst, true, &mpeg->engine);
पूर्ण

अटल स्थिर काष्ठा nv31_mpeg_func
nv31_mpeg = अणु
	.mthd_dma = nv31_mpeg_mthd_dma,
पूर्ण;

पूर्णांक
nv31_mpeg_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_engine **pmpeg)
अणु
	वापस nv31_mpeg_new_(&nv31_mpeg, device, type, inst, pmpeg);
पूर्ण
