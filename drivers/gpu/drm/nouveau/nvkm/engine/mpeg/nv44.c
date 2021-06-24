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
#घोषणा nv44_mpeg(p) container_of((p), काष्ठा nv44_mpeg, engine)
#समावेश "priv.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>

काष्ठा nv44_mpeg अणु
	काष्ठा nvkm_engine engine;
	काष्ठा list_head chan;
पूर्ण;

/*******************************************************************************
 * PMPEG context
 ******************************************************************************/
#घोषणा nv44_mpeg_chan(p) container_of((p), काष्ठा nv44_mpeg_chan, object)

काष्ठा nv44_mpeg_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा nv44_mpeg *mpeg;
	काष्ठा nvkm_fअगरo_chan *fअगरo;
	काष्ठा list_head head;
	u32 inst;
पूर्ण;

अटल पूर्णांक
nv44_mpeg_chan_bind(काष्ठा nvkm_object *object, काष्ठा nvkm_gpuobj *parent,
		    पूर्णांक align, काष्ठा nvkm_gpuobj **pgpuobj)
अणु
	काष्ठा nv44_mpeg_chan *chan = nv44_mpeg_chan(object);
	पूर्णांक ret = nvkm_gpuobj_new(chan->object.engine->subdev.device, 264 * 4,
				  align, true, parent, pgpuobj);
	अगर (ret == 0) अणु
		chan->inst = (*pgpuobj)->addr;
		nvkm_kmap(*pgpuobj);
		nvkm_wo32(*pgpuobj, 0x78, 0x02001ec1);
		nvkm_करोne(*pgpuobj);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
nv44_mpeg_chan_fini(काष्ठा nvkm_object *object, bool suspend)
अणु

	काष्ठा nv44_mpeg_chan *chan = nv44_mpeg_chan(object);
	काष्ठा nv44_mpeg *mpeg = chan->mpeg;
	काष्ठा nvkm_device *device = mpeg->engine.subdev.device;
	u32 inst = 0x80000000 | (chan->inst >> 4);

	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000000);
	अगर (nvkm_rd32(device, 0x00b318) == inst)
		nvkm_mask(device, 0x00b318, 0x80000000, 0x00000000);
	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000001);
	वापस 0;
पूर्ण

अटल व्योम *
nv44_mpeg_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv44_mpeg_chan *chan = nv44_mpeg_chan(object);
	काष्ठा nv44_mpeg *mpeg = chan->mpeg;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&mpeg->engine.lock, flags);
	list_del(&chan->head);
	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv44_mpeg_chan = अणु
	.dtor = nv44_mpeg_chan_dtor,
	.fini = nv44_mpeg_chan_fini,
	.bind = nv44_mpeg_chan_bind,
पूर्ण;

अटल पूर्णांक
nv44_mpeg_chan_new(काष्ठा nvkm_fअगरo_chan *fअगरoch,
		   स्थिर काष्ठा nvkm_oclass *oclass,
		   काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv44_mpeg *mpeg = nv44_mpeg(oclass->engine);
	काष्ठा nv44_mpeg_chan *chan;
	अचिन्हित दीर्घ flags;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_object_ctor(&nv44_mpeg_chan, oclass, &chan->object);
	chan->mpeg = mpeg;
	chan->fअगरo = fअगरoch;
	*pobject = &chan->object;

	spin_lock_irqsave(&mpeg->engine.lock, flags);
	list_add(&chan->head, &mpeg->chan);
	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
	वापस 0;
पूर्ण

/*******************************************************************************
 * PMPEG engine/subdev functions
 ******************************************************************************/

अटल bool
nv44_mpeg_mthd(काष्ठा nvkm_device *device, u32 mthd, u32 data)
अणु
	चयन (mthd) अणु
	हाल 0x190:
	हाल 0x1a0:
	हाल 0x1b0:
		वापस nv40_mpeg_mthd_dma(device, mthd, data);
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम
nv44_mpeg_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nv44_mpeg *mpeg = nv44_mpeg(engine);
	काष्ठा nvkm_subdev *subdev = &mpeg->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nv44_mpeg_chan *temp, *chan = शून्य;
	अचिन्हित दीर्घ flags;
	u32 inst = nvkm_rd32(device, 0x00b318) & 0x000fffff;
	u32 stat = nvkm_rd32(device, 0x00b100);
	u32 type = nvkm_rd32(device, 0x00b230);
	u32 mthd = nvkm_rd32(device, 0x00b234);
	u32 data = nvkm_rd32(device, 0x00b238);
	u32 show = stat;

	spin_lock_irqsave(&mpeg->engine.lock, flags);
	list_क्रम_each_entry(temp, &mpeg->chan, head) अणु
		अगर (temp->inst >> 4 == inst) अणु
			chan = temp;
			list_del(&chan->head);
			list_add(&chan->head, &mpeg->chan);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stat & 0x01000000) अणु
		/* happens on initial binding of the object */
		अगर (type == 0x00000020 && mthd == 0x0000) अणु
			nvkm_mask(device, 0x00b308, 0x00000000, 0x00000000);
			show &= ~0x01000000;
		पूर्ण

		अगर (type == 0x00000010) अणु
			अगर (nv44_mpeg_mthd(subdev->device, mthd, data))
				show &= ~0x01000000;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x00b100, stat);
	nvkm_wr32(device, 0x00b230, 0x00000001);

	अगर (show) अणु
		nvkm_error(subdev, "ch %d [%08x %s] %08x %08x %08x %08x\n",
			   chan ? chan->fअगरo->chid : -1, inst << 4,
			   chan ? chan->object.client->name : "unknown",
			   stat, type, mthd, data);
	पूर्ण

	spin_unlock_irqrestore(&mpeg->engine.lock, flags);
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nv44_mpeg = अणु
	.init = nv31_mpeg_init,
	.पूर्णांकr = nv44_mpeg_पूर्णांकr,
	.tile = nv31_mpeg_tile,
	.fअगरo.cclass = nv44_mpeg_chan_new,
	.sclass = अणु
		अणु -1, -1, NV31_MPEG, &nv31_mpeg_object पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv44_mpeg_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_engine **pmpeg)
अणु
	काष्ठा nv44_mpeg *mpeg;

	अगर (!(mpeg = kzalloc(माप(*mpeg), GFP_KERNEL)))
		वापस -ENOMEM;
	INIT_LIST_HEAD(&mpeg->chan);
	*pmpeg = &mpeg->engine;

	वापस nvkm_engine_ctor(&nv44_mpeg, device, type, inst, true, &mpeg->engine);
पूर्ण
