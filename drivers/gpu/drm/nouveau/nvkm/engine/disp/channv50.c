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
#समावेश "rootnv50.h"

#समावेश <core/client.h>
#समावेश <core/notअगरy.h>
#समावेश <core/oproxy.h>
#समावेश <core/ramht.h>
#समावेश <engine/dma.h>

#समावेश <nvअगर/cl507d.h>
#समावेश <nvअगर/event.h>
#समावेश <nvअगर/unpack.h>

अटल व्योम
nv50_disp_mthd_list(काष्ठा nv50_disp *disp, पूर्णांक debug, u32 base, पूर्णांक c,
		    स्थिर काष्ठा nv50_disp_mthd_list *list, पूर्णांक inst)
अणु
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक i;

	क्रम (i = 0; list->data[i].mthd; i++) अणु
		अगर (list->data[i].addr) अणु
			u32 next = nvkm_rd32(device, list->data[i].addr + base + 0);
			u32 prev = nvkm_rd32(device, list->data[i].addr + base + c);
			u32 mthd = list->data[i].mthd + (list->mthd * inst);
			स्थिर अक्षर *name = list->data[i].name;
			अक्षर mods[16];

			अगर (prev != next)
				snम_लिखो(mods, माप(mods), "-> %08x", next);
			अन्यथा
				snम_लिखो(mods, माप(mods), "%13c", ' ');

			nvkm_prपूर्णांकk_(subdev, debug, info,
				     "\t%04x: %08x %s%s%s\n",
				     mthd, prev, mods, name ? " // " : "",
				     name ? name : "");
		पूर्ण
	पूर्ण
पूर्ण

व्योम
nv50_disp_chan_mthd(काष्ठा nv50_disp_chan *chan, पूर्णांक debug)
अणु
	काष्ठा nv50_disp *disp = chan->disp;
	काष्ठा nvkm_subdev *subdev = &disp->base.engine.subdev;
	स्थिर काष्ठा nv50_disp_chan_mthd *mthd = chan->mthd;
	स्थिर काष्ठा nv50_disp_mthd_list *list;
	पूर्णांक i, j;

	अगर (debug > subdev->debug)
		वापस;
	अगर (!mthd)
		वापस;

	क्रम (i = 0; (list = mthd->data[i].mthd) != शून्य; i++) अणु
		u32 base = chan->head * mthd->addr;
		क्रम (j = 0; j < mthd->data[i].nr; j++, base += list->addr) अणु
			स्थिर अक्षर *cname = mthd->name;
			स्थिर अक्षर *sname = "";
			अक्षर cname_[16], sname_[16];

			अगर (mthd->addr) अणु
				snम_लिखो(cname_, माप(cname_), "%s %d",
					 mthd->name, chan->chid.user);
				cname = cname_;
			पूर्ण

			अगर (mthd->data[i].nr > 1) अणु
				snम_लिखो(sname_, माप(sname_), " - %s %d",
					 mthd->data[i].name, j);
				sname = sname_;
			पूर्ण

			nvkm_prपूर्णांकk_(subdev, debug, info, "%s%s:\n", cname, sname);
			nv50_disp_mthd_list(disp, debug, base, mthd->prev,
					    list, j);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
nv50_disp_chan_uevent_fini(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nv50_disp *disp = container_of(event, typeof(*disp), uevent);
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	nvkm_mask(device, 0x610028, 0x00000001 << index, 0x00000000 << index);
	nvkm_wr32(device, 0x610020, 0x00000001 << index);
पूर्ण

अटल व्योम
nv50_disp_chan_uevent_init(काष्ठा nvkm_event *event, पूर्णांक types, पूर्णांक index)
अणु
	काष्ठा nv50_disp *disp = container_of(event, typeof(*disp), uevent);
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	nvkm_wr32(device, 0x610020, 0x00000001 << index);
	nvkm_mask(device, 0x610028, 0x00000001 << index, 0x00000001 << index);
पूर्ण

व्योम
nv50_disp_chan_uevent_send(काष्ठा nv50_disp *disp, पूर्णांक chid)
अणु
	काष्ठा nvअगर_notअगरy_uevent_rep अणु
	पूर्ण rep;

	nvkm_event_send(&disp->uevent, 1, chid, &rep, माप(rep));
पूर्ण

पूर्णांक
nv50_disp_chan_uevent_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
			   काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_uevent_req none;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unvers(ret, &data, &size, args->none))) अणु
		notअगरy->size  = माप(काष्ठा nvअगर_notअगरy_uevent_rep);
		notअगरy->types = 1;
		notअगरy->index = chan->chid.user;
		वापस 0;
	पूर्ण

	वापस ret;
पूर्ण

स्थिर काष्ठा nvkm_event_func
nv50_disp_chan_uevent = अणु
	.ctor = nv50_disp_chan_uevent_ctor,
	.init = nv50_disp_chan_uevent_init,
	.fini = nv50_disp_chan_uevent_fini,
पूर्ण;

u64
nv50_disp_chan_user(काष्ठा nv50_disp_chan *chan, u64 *psize)
अणु
	*psize = 0x1000;
	वापस 0x640000 + (chan->chid.user * 0x1000);
पूर्ण

व्योम
nv50_disp_chan_पूर्णांकr(काष्ठा nv50_disp_chan *chan, bool en)
अणु
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u32 mask = 0x00010001 << chan->chid.user;
	स्थिर u32 data = en ? 0x00010000 << chan->chid.user : 0x00000000;
	nvkm_mask(device, 0x610028, mask, data);
पूर्ण

अटल पूर्णांक
nv50_disp_chan_rd32(काष्ठा nvkm_object *object, u64 addr, u32 *data)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	u64 size, base = chan->func->user(chan, &size);
	*data = nvkm_rd32(device, base + addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_disp_chan_wr32(काष्ठा nvkm_object *object, u64 addr, u32 data)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	u64 size, base = chan->func->user(chan, &size);
	nvkm_wr32(device, base + addr, data);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_disp_chan_ntfy(काष्ठा nvkm_object *object, u32 type,
		    काष्ठा nvkm_event **pevent)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	काष्ठा nv50_disp *disp = chan->disp;
	चयन (type) अणु
	हाल NV50_DISP_CORE_CHANNEL_DMA_V0_NTFY_UEVENT:
		*pevent = &disp->uevent;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nv50_disp_chan_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		   क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर u64 base = device->func->resource_addr(device, 0);
	*type = NVKM_OBJECT_MAP_IO;
	*addr = base + chan->func->user(chan, size);
	वापस 0;
पूर्ण

काष्ठा nv50_disp_chan_object अणु
	काष्ठा nvkm_oproxy oproxy;
	काष्ठा nv50_disp *disp;
	पूर्णांक hash;
पूर्ण;

अटल व्योम
nv50_disp_chan_child_del_(काष्ठा nvkm_oproxy *base)
अणु
	काष्ठा nv50_disp_chan_object *object =
		container_of(base, typeof(*object), oproxy);
	nvkm_ramht_हटाओ(object->disp->ramht, object->hash);
पूर्ण

अटल स्थिर काष्ठा nvkm_oproxy_func
nv50_disp_chan_child_func_ = अणु
	.dtor[0] = nv50_disp_chan_child_del_,
पूर्ण;

अटल पूर्णांक
nv50_disp_chan_child_new(स्थिर काष्ठा nvkm_oclass *oclass,
			 व्योम *argv, u32 argc, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(oclass->parent);
	काष्ठा nv50_disp *disp = chan->disp;
	काष्ठा nvkm_device *device = disp->base.engine.subdev.device;
	स्थिर काष्ठा nvkm_device_oclass *sclass = oclass->priv;
	काष्ठा nv50_disp_chan_object *object;
	पूर्णांक ret;

	अगर (!(object = kzalloc(माप(*object), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_oproxy_ctor(&nv50_disp_chan_child_func_, oclass, &object->oproxy);
	object->disp = disp;
	*pobject = &object->oproxy.base;

	ret = sclass->ctor(device, oclass, argv, argc, &object->oproxy.object);
	अगर (ret)
		वापस ret;

	object->hash = chan->func->bind(chan, object->oproxy.object,
					      oclass->handle);
	अगर (object->hash < 0)
		वापस object->hash;

	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_disp_chan_child_get(काष्ठा nvkm_object *object, पूर्णांक index,
			 काष्ठा nvkm_oclass *sclass)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	काष्ठा nvkm_device *device = chan->disp->base.engine.subdev.device;
	स्थिर काष्ठा nvkm_device_oclass *oclass = शून्य;

	अगर (chan->func->bind)
		sclass->engine = nvkm_device_engine(device, NVKM_ENGINE_DMAOBJ, 0);
	अन्यथा
		sclass->engine = शून्य;

	अगर (sclass->engine && sclass->engine->func->base.sclass) अणु
		sclass->engine->func->base.sclass(sclass, index, &oclass);
		अगर (oclass) अणु
			sclass->ctor = nv50_disp_chan_child_new,
			sclass->priv = oclass;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nv50_disp_chan_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	chan->func->fini(chan);
	chan->func->पूर्णांकr(chan, false);
	वापस 0;
पूर्ण

अटल पूर्णांक
nv50_disp_chan_init(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	chan->func->पूर्णांकr(chan, true);
	वापस chan->func->init(chan);
पूर्ण

अटल व्योम *
nv50_disp_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nv50_disp_chan *chan = nv50_disp_chan(object);
	काष्ठा nv50_disp *disp = chan->disp;
	अगर (chan->chid.user >= 0)
		disp->chan[chan->chid.user] = शून्य;
	nvkm_memory_unref(&chan->memory);
	वापस chan;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nv50_disp_chan = अणु
	.dtor = nv50_disp_chan_dtor,
	.init = nv50_disp_chan_init,
	.fini = nv50_disp_chan_fini,
	.rd32 = nv50_disp_chan_rd32,
	.wr32 = nv50_disp_chan_wr32,
	.ntfy = nv50_disp_chan_ntfy,
	.map = nv50_disp_chan_map,
	.sclass = nv50_disp_chan_child_get,
पूर्ण;

पूर्णांक
nv50_disp_chan_new_(स्थिर काष्ठा nv50_disp_chan_func *func,
		    स्थिर काष्ठा nv50_disp_chan_mthd *mthd,
		    काष्ठा nv50_disp *disp, पूर्णांक ctrl, पूर्णांक user, पूर्णांक head,
		    स्थिर काष्ठा nvkm_oclass *oclass,
		    काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nv50_disp_chan *chan;

	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &chan->object;

	nvkm_object_ctor(&nv50_disp_chan, oclass, &chan->object);
	chan->func = func;
	chan->mthd = mthd;
	chan->disp = disp;
	chan->chid.ctrl = ctrl;
	chan->chid.user = user;
	chan->head = head;

	अगर (disp->chan[chan->chid.user]) अणु
		chan->chid.user = -1;
		वापस -EBUSY;
	पूर्ण
	disp->chan[chan->chid.user] = chan;
	वापस 0;
पूर्ण
