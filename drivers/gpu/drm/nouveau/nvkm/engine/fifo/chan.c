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
#समावेश "chan.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <core/oproxy.h>
#समावेश <subdev/mmu.h>
#समावेश <engine/dma.h>

काष्ठा nvkm_fअगरo_chan_object अणु
	काष्ठा nvkm_oproxy oproxy;
	काष्ठा nvkm_fअगरo_chan *chan;
	पूर्णांक hash;
पूर्ण;

अटल काष्ठा nvkm_fअगरo_engn *
nvkm_fअगरo_chan_engn(काष्ठा nvkm_fअगरo_chan *chan, काष्ठा nvkm_engine *engine)
अणु
	पूर्णांक engi = chan->fअगरo->func->engine_id(chan->fअगरo, engine);
	अगर (engi >= 0)
		वापस &chan->engn[engi];
	वापस शून्य;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_child_fini(काष्ठा nvkm_oproxy *base, bool suspend)
अणु
	काष्ठा nvkm_fअगरo_chan_object *object =
		container_of(base, typeof(*object), oproxy);
	काष्ठा nvkm_engine *engine  = object->oproxy.object->engine;
	काष्ठा nvkm_fअगरo_chan *chan = object->chan;
	काष्ठा nvkm_fअगरo_engn *engn = nvkm_fअगरo_chan_engn(chan, engine);
	स्थिर अक्षर *name = engine->subdev.name;
	पूर्णांक ret = 0;

	अगर (--engn->usecount)
		वापस 0;

	अगर (chan->func->engine_fini) अणु
		ret = chan->func->engine_fini(chan, engine, suspend);
		अगर (ret) अणु
			nvअगर_error(&chan->object,
				   "detach %s failed, %d\n", name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (engn->object) अणु
		ret = nvkm_object_fini(engn->object, suspend);
		अगर (ret && suspend)
			वापस ret;
	पूर्ण

	nvअगर_trace(&chan->object, "detached %s\n", name);
	वापस ret;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_child_init(काष्ठा nvkm_oproxy *base)
अणु
	काष्ठा nvkm_fअगरo_chan_object *object =
		container_of(base, typeof(*object), oproxy);
	काष्ठा nvkm_engine *engine  = object->oproxy.object->engine;
	काष्ठा nvkm_fअगरo_chan *chan = object->chan;
	काष्ठा nvkm_fअगरo_engn *engn = nvkm_fअगरo_chan_engn(chan, engine);
	स्थिर अक्षर *name = engine->subdev.name;
	पूर्णांक ret;

	अगर (engn->usecount++)
		वापस 0;

	अगर (engn->object) अणु
		ret = nvkm_object_init(engn->object);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (chan->func->engine_init) अणु
		ret = chan->func->engine_init(chan, engine);
		अगर (ret) अणु
			nvअगर_error(&chan->object,
				   "attach %s failed, %d\n", name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	nvअगर_trace(&chan->object, "attached %s\n", name);
	वापस 0;
पूर्ण

अटल व्योम
nvkm_fअगरo_chan_child_del(काष्ठा nvkm_oproxy *base)
अणु
	काष्ठा nvkm_fअगरo_chan_object *object =
		container_of(base, typeof(*object), oproxy);
	काष्ठा nvkm_engine *engine  = object->oproxy.base.engine;
	काष्ठा nvkm_fअगरo_chan *chan = object->chan;
	काष्ठा nvkm_fअगरo_engn *engn = nvkm_fअगरo_chan_engn(chan, engine);

	अगर (chan->func->object_dtor)
		chan->func->object_dtor(chan, object->hash);

	अगर (!--engn->refcount) अणु
		अगर (chan->func->engine_dtor)
			chan->func->engine_dtor(chan, engine);
		nvkm_object_del(&engn->object);
		अगर (chan->vmm)
			atomic_dec(&chan->vmm->engref[engine->subdev.type]);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_oproxy_func
nvkm_fअगरo_chan_child_func = अणु
	.dtor[0] = nvkm_fअगरo_chan_child_del,
	.init[0] = nvkm_fअगरo_chan_child_init,
	.fini[0] = nvkm_fअगरo_chan_child_fini,
पूर्ण;

अटल पूर्णांक
nvkm_fअगरo_chan_child_new(स्थिर काष्ठा nvkm_oclass *oclass, व्योम *data, u32 size,
			 काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_engine *engine = oclass->engine;
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(oclass->parent);
	काष्ठा nvkm_fअगरo_engn *engn = nvkm_fअगरo_chan_engn(chan, engine);
	काष्ठा nvkm_fअगरo_chan_object *object;
	पूर्णांक ret = 0;

	अगर (!(object = kzalloc(माप(*object), GFP_KERNEL)))
		वापस -ENOMEM;
	nvkm_oproxy_ctor(&nvkm_fअगरo_chan_child_func, oclass, &object->oproxy);
	object->chan = chan;
	*pobject = &object->oproxy.base;

	अगर (!engn->refcount++) अणु
		काष्ठा nvkm_oclass cclass = अणु
			.client = oclass->client,
			.engine = oclass->engine,
		पूर्ण;

		अगर (chan->vmm)
			atomic_inc(&chan->vmm->engref[engine->subdev.type]);

		अगर (engine->func->fअगरo.cclass) अणु
			ret = engine->func->fअगरo.cclass(chan, &cclass,
							&engn->object);
		पूर्ण अन्यथा
		अगर (engine->func->cclass) अणु
			ret = nvkm_object_new_(engine->func->cclass, &cclass,
					       शून्य, 0, &engn->object);
		पूर्ण
		अगर (ret)
			वापस ret;

		अगर (chan->func->engine_ctor) अणु
			ret = chan->func->engine_ctor(chan, oclass->engine,
						      engn->object);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	ret = oclass->base.ctor(&(स्थिर काष्ठा nvkm_oclass) अणु
					.base = oclass->base,
					.engn = oclass->engn,
					.handle = oclass->handle,
					.object = oclass->object,
					.client = oclass->client,
					.parent = engn->object ?
						  engn->object :
						  oclass->parent,
					.engine = engine,
				पूर्ण, data, size, &object->oproxy.object);
	अगर (ret)
		वापस ret;

	अगर (chan->func->object_ctor) अणु
		object->hash =
			chan->func->object_ctor(chan, object->oproxy.object);
		अगर (object->hash < 0)
			वापस object->hash;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_child_get(काष्ठा nvkm_object *object, पूर्णांक index,
			 काष्ठा nvkm_oclass *oclass)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	काष्ठा nvkm_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_engine *engine;
	u32 engm = chan->engm;
	पूर्णांक engi, ret, c;

	क्रम (; c = 0, engi = __ffs(engm), engm; engm &= ~(1ULL << engi)) अणु
		अगर (!(engine = fअगरo->func->id_engine(fअगरo, engi)))
			जारी;
		oclass->engine = engine;
		oclass->base.oclass = 0;

		अगर (engine->func->fअगरo.sclass) अणु
			ret = engine->func->fअगरo.sclass(oclass, index);
			अगर (oclass->base.oclass) अणु
				अगर (!oclass->base.ctor)
					oclass->base.ctor = nvkm_object_new;
				oclass->ctor = nvkm_fअगरo_chan_child_new;
				वापस 0;
			पूर्ण

			index -= ret;
			जारी;
		पूर्ण

		जबतक (engine->func->sclass[c].oclass) अणु
			अगर (c++ == index) अणु
				oclass->base = engine->func->sclass[index];
				अगर (!oclass->base.ctor)
					oclass->base.ctor = nvkm_object_new;
				oclass->ctor = nvkm_fअगरo_chan_child_new;
				वापस 0;
			पूर्ण
		पूर्ण
		index -= c;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_ntfy(काष्ठा nvkm_object *object, u32 type,
		    काष्ठा nvkm_event **pevent)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	अगर (chan->func->ntfy)
		वापस chan->func->ntfy(chan, type, pevent);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_map(काष्ठा nvkm_object *object, व्योम *argv, u32 argc,
		   क्रमागत nvkm_object_map *type, u64 *addr, u64 *size)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	*type = NVKM_OBJECT_MAP_IO;
	*addr = chan->addr;
	*size = chan->size;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_rd32(काष्ठा nvkm_object *object, u64 addr, u32 *data)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	अगर (unlikely(!chan->user)) अणु
		chan->user = ioremap(chan->addr, chan->size);
		अगर (!chan->user)
			वापस -ENOMEM;
	पूर्ण
	अगर (unlikely(addr + 4 > chan->size))
		वापस -EINVAL;
	*data = ioपढ़ो32_native(chan->user + addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_wr32(काष्ठा nvkm_object *object, u64 addr, u32 data)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	अगर (unlikely(!chan->user)) अणु
		chan->user = ioremap(chan->addr, chan->size);
		अगर (!chan->user)
			वापस -ENOMEM;
	पूर्ण
	अगर (unlikely(addr + 4 > chan->size))
		वापस -EINVAL;
	ioग_लिखो32_native(data, chan->user + addr);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_fini(काष्ठा nvkm_object *object, bool suspend)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	chan->func->fini(chan);
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_fअगरo_chan_init(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	chan->func->init(chan);
	वापस 0;
पूर्ण

अटल व्योम *
nvkm_fअगरo_chan_dtor(काष्ठा nvkm_object *object)
अणु
	काष्ठा nvkm_fअगरo_chan *chan = nvkm_fअगरo_chan(object);
	काष्ठा nvkm_fअगरo *fअगरo = chan->fअगरo;
	व्योम *data = chan->func->dtor(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fअगरo->lock, flags);
	अगर (!list_empty(&chan->head)) अणु
		__clear_bit(chan->chid, fअगरo->mask);
		list_del(&chan->head);
	पूर्ण
	spin_unlock_irqrestore(&fअगरo->lock, flags);

	अगर (chan->user)
		iounmap(chan->user);

	अगर (chan->vmm) अणु
		nvkm_vmm_part(chan->vmm, chan->inst->memory);
		nvkm_vmm_unref(&chan->vmm);
	पूर्ण

	nvkm_gpuobj_del(&chan->push);
	nvkm_gpuobj_del(&chan->inst);
	वापस data;
पूर्ण

अटल स्थिर काष्ठा nvkm_object_func
nvkm_fअगरo_chan_func = अणु
	.dtor = nvkm_fअगरo_chan_dtor,
	.init = nvkm_fअगरo_chan_init,
	.fini = nvkm_fअगरo_chan_fini,
	.ntfy = nvkm_fअगरo_chan_ntfy,
	.map = nvkm_fअगरo_chan_map,
	.rd32 = nvkm_fअगरo_chan_rd32,
	.wr32 = nvkm_fअगरo_chan_wr32,
	.sclass = nvkm_fअगरo_chan_child_get,
पूर्ण;

पूर्णांक
nvkm_fअगरo_chan_ctor(स्थिर काष्ठा nvkm_fअगरo_chan_func *func,
		    काष्ठा nvkm_fअगरo *fअगरo, u32 size, u32 align, bool zero,
		    u64 hvmm, u64 push, u32 engm, पूर्णांक bar, u32 base,
		    u32 user, स्थिर काष्ठा nvkm_oclass *oclass,
		    काष्ठा nvkm_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_client *client = oclass->client;
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	काष्ठा nvkm_dmaobj *dmaobj;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	nvkm_object_ctor(&nvkm_fअगरo_chan_func, oclass, &chan->object);
	chan->func = func;
	chan->fअगरo = fअगरo;
	chan->engm = engm;
	INIT_LIST_HEAD(&chan->head);

	/* instance memory */
	ret = nvkm_gpuobj_new(device, size, align, zero, शून्य, &chan->inst);
	अगर (ret)
		वापस ret;

	/* allocate push buffer ctxdma instance */
	अगर (push) अणु
		dmaobj = nvkm_dmaobj_search(client, push);
		अगर (IS_ERR(dmaobj))
			वापस PTR_ERR(dmaobj);

		ret = nvkm_object_bind(&dmaobj->object, chan->inst, -16,
				       &chan->push);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* channel address space */
	अगर (hvmm) अणु
		काष्ठा nvkm_vmm *vmm = nvkm_uvmm_search(client, hvmm);
		अगर (IS_ERR(vmm))
			वापस PTR_ERR(vmm);

		अगर (vmm->mmu != device->mmu)
			वापस -EINVAL;

		ret = nvkm_vmm_join(vmm, chan->inst->memory);
		अगर (ret)
			वापस ret;

		chan->vmm = nvkm_vmm_ref(vmm);
	पूर्ण

	/* allocate channel id */
	spin_lock_irqsave(&fअगरo->lock, flags);
	chan->chid = find_first_zero_bit(fअगरo->mask, NVKM_FIFO_CHID_NR);
	अगर (chan->chid >= NVKM_FIFO_CHID_NR) अणु
		spin_unlock_irqrestore(&fअगरo->lock, flags);
		वापस -ENOSPC;
	पूर्ण
	list_add(&chan->head, &fअगरo->chan);
	__set_bit(chan->chid, fअगरo->mask);
	spin_unlock_irqrestore(&fअगरo->lock, flags);

	/* determine address of this channel's user रेजिस्टरs */
	chan->addr = device->func->resource_addr(device, bar) +
		     base + user * chan->chid;
	chan->size = user;

	nvkm_fअगरo_cevent(fअगरo);
	वापस 0;
पूर्ण
