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
#समावेश "priv.h"
#समावेश "chan.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <core/notअगरy.h>
#समावेश <subdev/mc.h>

#समावेश <nvअगर/event.h>
#समावेश <nvअगर/cl0080.h>
#समावेश <nvअगर/unpack.h>

व्योम
nvkm_fअगरo_recover_chan(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक chid)
अणु
	अचिन्हित दीर्घ flags;
	अगर (WARN_ON(!fअगरo->func->recover_chan))
		वापस;
	spin_lock_irqsave(&fअगरo->lock, flags);
	fअगरo->func->recover_chan(fअगरo, chid);
	spin_unlock_irqrestore(&fअगरo->lock, flags);
पूर्ण

व्योम
nvkm_fअगरo_छोड़ो(काष्ठा nvkm_fअगरo *fअगरo, अचिन्हित दीर्घ *flags)
अणु
	वापस fअगरo->func->छोड़ो(fअगरo, flags);
पूर्ण

व्योम
nvkm_fअगरo_start(काष्ठा nvkm_fअगरo *fअगरo, अचिन्हित दीर्घ *flags)
अणु
	वापस fअगरo->func->start(fअगरo, flags);
पूर्ण

व्योम
nvkm_fअगरo_fault(काष्ठा nvkm_fअगरo *fअगरo, काष्ठा nvkm_fault_data *info)
अणु
	वापस fअगरo->func->fault(fअगरo, info);
पूर्ण

व्योम
nvkm_fअगरo_chan_put(काष्ठा nvkm_fअगरo *fअगरo, अचिन्हित दीर्घ flags,
		   काष्ठा nvkm_fअगरo_chan **pchan)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = *pchan;
	अगर (likely(chan)) अणु
		*pchan = शून्य;
		spin_unlock_irqrestore(&fअगरo->lock, flags);
	पूर्ण
पूर्ण

काष्ठा nvkm_fअगरo_chan *
nvkm_fअगरo_chan_inst_locked(काष्ठा nvkm_fअगरo *fअगरo, u64 inst)
अणु
	काष्ठा nvkm_fअगरo_chan *chan;
	list_क्रम_each_entry(chan, &fअगरo->chan, head) अणु
		अगर (chan->inst->addr == inst) अणु
			list_del(&chan->head);
			list_add(&chan->head, &fअगरo->chan);
			वापस chan;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा nvkm_fअगरo_chan *
nvkm_fअगरo_chan_inst(काष्ठा nvkm_fअगरo *fअगरo, u64 inst, अचिन्हित दीर्घ *rflags)
अणु
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&fअगरo->lock, flags);
	अगर ((chan = nvkm_fअगरo_chan_inst_locked(fअगरo, inst))) अणु
		*rflags = flags;
		वापस chan;
	पूर्ण
	spin_unlock_irqrestore(&fअगरo->lock, flags);
	वापस शून्य;
पूर्ण

काष्ठा nvkm_fअगरo_chan *
nvkm_fअगरo_chan_chid(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक chid, अचिन्हित दीर्घ *rflags)
अणु
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&fअगरo->lock, flags);
	list_क्रम_each_entry(chan, &fअगरo->chan, head) अणु
		अगर (chan->chid == chid) अणु
			list_del(&chan->head);
			list_add(&chan->head, &fअगरo->chan);
			*rflags = flags;
			वापस chan;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&fअगरo->lock, flags);
	वापस शून्य;
पूर्ण

व्योम
nvkm_fअगरo_kevent(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक chid)
अणु
	nvkm_event_send(&fअगरo->kevent, 1, chid, शून्य, 0);
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_kevent_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		      काष्ठा nvkm_notअगरy *notअगरy)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	अगर (size == 0) अणु
		notअगरy->size  = 0;
		notअगरy->types = 1;
		notअगरy->index = chan->chid;
		वापस 0;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_fअगरo_kevent_func = अणु
	.ctor = nvkm_fअगरo_kevent_ctor,
पूर्ण;

अटल पूर्णांक
nvkm_fअगरo_cevent_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		      काष्ठा nvkm_notअगरy *notअगरy)
अणु
	अगर (size == 0) अणु
		notअगरy->size  = 0;
		notअगरy->types = 1;
		notअगरy->index = 0;
		वापस 0;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_fअगरo_cevent_func = अणु
	.ctor = nvkm_fअगरo_cevent_ctor,
पूर्ण;

व्योम
nvkm_fअगरo_cevent(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	nvkm_event_send(&fअगरo->cevent, 1, 0, शून्य, 0);
पूर्ण

अटल व्योम
nvkm_fअगरo_uevent_fini(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = container_of(event, typeof(*fअगरo), uevent);
	fअगरo->func->uevent_fini(fअगरo);
पूर्ण

अटल व्योम
nvkm_fअगरo_uevent_init(काष्ठा nvkm_event *event, पूर्णांक type, पूर्णांक index)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = container_of(event, typeof(*fअगरo), uevent);
	fअगरo->func->uevent_init(fअगरo);
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_uevent_ctor(काष्ठा nvkm_object *object, व्योम *data, u32 size,
		      काष्ठा nvkm_notअगरy *notअगरy)
अणु
	जोड़ अणु
		काष्ठा nvअगर_notअगरy_uevent_req none;
	पूर्ण *req = data;
	पूर्णांक ret = -ENOSYS;

	अगर (!(ret = nvअगर_unvers(ret, &data, &size, req->none))) अणु
		notअगरy->size  = माप(काष्ठा nvअगर_notअगरy_uevent_rep);
		notअगरy->types = 1;
		notअगरy->index = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_event_func
nvkm_fअगरo_uevent_func = अणु
	.ctor = nvkm_fअगरo_uevent_ctor,
	.init = nvkm_fअगरo_uevent_init,
	.fini = nvkm_fअगरo_uevent_fini,
पूर्ण;

व्योम
nvkm_fअगरo_uevent(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	काष्ठा nvअगर_notअगरy_uevent_rep rep = अणु
	पूर्ण;
	nvkm_event_send(&fअगरo->uevent, 1, 0, &rep, माप(rep));
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_class_new_(काष्ठा nvkm_device *device,
		     स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		     काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(oclass->engine);
	वापस fअगरo->func->class_new(fअगरo, oclass, data, size, pobject);
पूर्ण

अटल स्थिर काष्ठा nvkm_device_oclass
nvkm_fअगरo_class_ = अणु
	.ctor = nvkm_fअगरo_class_new_,
पूर्ण;

अटल पूर्णांक
nvkm_fअगरo_class_new(काष्ठा nvkm_device *device,
		    स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
		    काष्ठा nvkm_object **pobject)
अणु
	स्थिर काष्ठा nvkm_fअगरo_chan_oclass *sclass = oclass->engn;
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(oclass->engine);
	वापस sclass->ctor(fअगरo, oclass, data, size, pobject);
पूर्ण

अटल स्थिर काष्ठा nvkm_device_oclass
nvkm_fअगरo_class = अणु
	.ctor = nvkm_fअगरo_class_new,
पूर्ण;

अटल पूर्णांक
nvkm_fअगरo_class_get(काष्ठा nvkm_oclass *oclass, पूर्णांक index,
		    स्थिर काष्ठा nvkm_device_oclass **class)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(oclass->engine);
	स्थिर काष्ठा nvkm_fअगरo_chan_oclass *sclass;
	पूर्णांक c = 0;

	अगर (fअगरo->func->class_get) अणु
		पूर्णांक ret = fअगरo->func->class_get(fअगरo, index, oclass);
		अगर (ret == 0)
			*class = &nvkm_fअगरo_class_;
		वापस ret;
	पूर्ण

	जबतक ((sclass = fअगरo->func->chan[c])) अणु
		अगर (c++ == index) अणु
			oclass->base = sclass->base;
			oclass->engn = sclass;
			*class = &nvkm_fअगरo_class;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण

अटल व्योम
nvkm_fअगरo_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(engine);
	fअगरo->func->पूर्णांकr(fअगरo);
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_fini(काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(engine);
	अगर (fअगरo->func->fini)
		fअगरo->func->fini(fअगरo);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_info(काष्ठा nvkm_engine *engine, u64 mthd, u64 *data)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(engine);
	चयन (mthd) अणु
	हाल NV_DEVICE_HOST_CHANNELS: *data = fअगरo->nr; वापस 0;
	शेष:
		अगर (fअगरo->func->info)
			वापस fअगरo->func->info(fअगरo, mthd, data);
		अवरोध;
	पूर्ण
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_oneinit(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(engine);
	अगर (fअगरo->func->oneinit)
		वापस fअगरo->func->oneinit(fअगरo);
	वापस 0;
पूर्ण

अटल व्योम
nvkm_fअगरo_preinit(काष्ठा nvkm_engine *engine)
अणु
	nvkm_mc_reset(engine->subdev.device, NVKM_ENGINE_FIFO, 0);
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_init(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(engine);
	fअगरo->func->init(fअगरo);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_fअगरo_dtor(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_fअगरo *fअगरo = nvkm_fअगरo(engine);
	व्योम *data = fअगरo;
	अगर (fअगरo->func->dtor)
		data = fअगरo->func->dtor(fअगरo);
	nvkm_event_fini(&fअगरo->kevent);
	nvkm_event_fini(&fअगरo->cevent);
	nvkm_event_fini(&fअगरo->uevent);
	mutex_destroy(&fअगरo->mutex);
	वापस data;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_fअगरo = अणु
	.dtor = nvkm_fअगरo_dtor,
	.preinit = nvkm_fअगरo_preinit,
	.oneinit = nvkm_fअगरo_oneinit,
	.info = nvkm_fअगरo_info,
	.init = nvkm_fअगरo_init,
	.fini = nvkm_fअगरo_fini,
	.पूर्णांकr = nvkm_fअगरo_पूर्णांकr,
	.base.sclass = nvkm_fअगरo_class_get,
पूर्ण;

पूर्णांक
nvkm_fअगरo_ctor(स्थिर काष्ठा nvkm_fअगरo_func *func, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, पूर्णांक nr, काष्ठा nvkm_fअगरo *fअगरo)
अणु
	पूर्णांक ret;

	fअगरo->func = func;
	INIT_LIST_HEAD(&fअगरo->chan);
	spin_lock_init(&fअगरo->lock);
	mutex_init(&fअगरo->mutex);

	अगर (WARN_ON(fअगरo->nr > NVKM_FIFO_CHID_NR))
		fअगरo->nr = NVKM_FIFO_CHID_NR;
	अन्यथा
		fअगरo->nr = nr;
	biपंचांगap_clear(fअगरo->mask, 0, fअगरo->nr);

	ret = nvkm_engine_ctor(&nvkm_fअगरo, device, type, inst, true, &fअगरo->engine);
	अगर (ret)
		वापस ret;

	अगर (func->uevent_init) अणु
		ret = nvkm_event_init(&nvkm_fअगरo_uevent_func, 1, 1,
				      &fअगरo->uevent);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = nvkm_event_init(&nvkm_fअगरo_cevent_func, 1, 1, &fअगरo->cevent);
	अगर (ret)
		वापस ret;

	वापस nvkm_event_init(&nvkm_fअगरo_kevent_func, 1, nr, &fअगरo->kevent);
पूर्ण
