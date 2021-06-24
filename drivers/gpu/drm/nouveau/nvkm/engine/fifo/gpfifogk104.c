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
#समावेश "changk104.h"
#समावेश "cgrp.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/mmu.h>
#समावेश <subdev/समयr.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cla06f.h>
#समावेश <nvअगर/unpack.h>

पूर्णांक
gk104_fअगरo_gpfअगरo_kick_locked(काष्ठा gk104_fअगरo_chan *chan)
अणु
	काष्ठा gk104_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_client *client = chan->base.object.client;
	काष्ठा nvkm_fअगरo_cgrp *cgrp = chan->cgrp;
	पूर्णांक ret = 0;

	अगर (cgrp)
		nvkm_wr32(device, 0x002634, cgrp->id | 0x01000000);
	अन्यथा
		nvkm_wr32(device, 0x002634, chan->base.chid);
	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x002634) & 0x00100000))
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "%s %d [%s] kick timeout\n",
			   cgrp ? "tsg" : "channel",
			   cgrp ? cgrp->id : chan->base.chid, client->name);
		nvkm_fअगरo_recover_chan(&fअगरo->base, chan->base.chid);
		ret = -ETIMEDOUT;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
gk104_fअगरo_gpfअगरo_kick(काष्ठा gk104_fअगरo_chan *chan)
अणु
	पूर्णांक ret;
	mutex_lock(&chan->base.fअगरo->mutex);
	ret = gk104_fअगरo_gpfअगरo_kick_locked(chan);
	mutex_unlock(&chan->base.fअगरo->mutex);
	वापस ret;
पूर्ण

अटल u32
gk104_fअगरo_gpfअगरo_engine_addr(काष्ठा nvkm_engine *engine)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_SW    :
	हाल NVKM_ENGINE_CE    : वापस 0;
	हाल NVKM_ENGINE_GR    : वापस 0x0210;
	हाल NVKM_ENGINE_SEC   : वापस 0x0220;
	हाल NVKM_ENGINE_MSPDEC: वापस 0x0250;
	हाल NVKM_ENGINE_MSPPP : वापस 0x0260;
	हाल NVKM_ENGINE_MSVLD : वापस 0x0270;
	हाल NVKM_ENGINE_VIC   : वापस 0x0280;
	हाल NVKM_ENGINE_MSENC : वापस 0x0290;
	हाल NVKM_ENGINE_NVDEC : वापस 0x02100270;
	हाल NVKM_ENGINE_NVENC :
		अगर (engine->subdev.inst)
			वापस 0x0210;
		वापस 0x02100290;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

काष्ठा gk104_fअगरo_engn *
gk104_fअगरo_gpfअगरo_engine(काष्ठा gk104_fअगरo_chan *chan, काष्ठा nvkm_engine *engine)
अणु
	पूर्णांक engi = chan->base.fअगरo->func->engine_id(chan->base.fअगरo, engine);
	अगर (engi >= 0)
		वापस &chan->engn[engi];
	वापस शून्य;
पूर्ण

अटल पूर्णांक
gk104_fअगरo_gpfअगरo_engine_fini(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा nvkm_gpuobj *inst = chan->base.inst;
	u32 offset = gk104_fअगरo_gpfअगरo_engine_addr(engine);
	पूर्णांक ret;

	ret = gk104_fअगरo_gpfअगरo_kick(chan);
	अगर (ret && suspend)
		वापस ret;

	अगर (offset) अणु
		nvkm_kmap(inst);
		nvkm_wo32(inst, (offset & 0xffff) + 0x00, 0x00000000);
		nvkm_wo32(inst, (offset & 0xffff) + 0x04, 0x00000000);
		अगर ((offset >>= 16)) अणु
			nvkm_wo32(inst, offset + 0x00, 0x00000000);
			nvkm_wo32(inst, offset + 0x04, 0x00000000);
		पूर्ण
		nvkm_करोne(inst);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
gk104_fअगरo_gpfअगरo_engine_init(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा gk104_fअगरo_engn *engn = gk104_fअगरo_gpfअगरo_engine(chan, engine);
	काष्ठा nvkm_gpuobj *inst = chan->base.inst;
	u32 offset = gk104_fअगरo_gpfअगरo_engine_addr(engine);

	अगर (offset) अणु
		u32 datalo = lower_32_bits(engn->vma->addr) | 0x00000004;
		u32 datahi = upper_32_bits(engn->vma->addr);
		nvkm_kmap(inst);
		nvkm_wo32(inst, (offset & 0xffff) + 0x00, datalo);
		nvkm_wo32(inst, (offset & 0xffff) + 0x04, datahi);
		अगर ((offset >>= 16)) अणु
			nvkm_wo32(inst, offset + 0x00, datalo);
			nvkm_wo32(inst, offset + 0x04, datahi);
		पूर्ण
		nvkm_करोne(inst);
	पूर्ण

	वापस 0;
पूर्ण

व्योम
gk104_fअगरo_gpfअगरo_engine_dtor(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा gk104_fअगरo_engn *engn = gk104_fअगरo_gpfअगरo_engine(chan, engine);
	nvkm_vmm_put(chan->base.vmm, &engn->vma);
	nvkm_gpuobj_del(&engn->inst);
पूर्ण

पूर्णांक
gk104_fअगरo_gpfअगरo_engine_ctor(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine,
			      काष्ठा nvkm_object *object)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा gk104_fअगरo_engn *engn = gk104_fअगरo_gpfअगरo_engine(chan, engine);
	पूर्णांक ret;

	अगर (!gk104_fअगरo_gpfअगरo_engine_addr(engine))
		वापस 0;

	ret = nvkm_object_bind(object, शून्य, 0, &engn->inst);
	अगर (ret)
		वापस ret;

	ret = nvkm_vmm_get(chan->base.vmm, 12, engn->inst->size, &engn->vma);
	अगर (ret)
		वापस ret;

	वापस nvkm_memory_map(engn->inst, 0, chan->base.vmm, engn->vma, शून्य, 0);
पूर्ण

व्योम
gk104_fअगरo_gpfअगरo_fini(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा gk104_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 coff = chan->base.chid * 8;

	अगर (!list_empty(&chan->head)) अणु
		gk104_fअगरo_runlist_हटाओ(fअगरo, chan);
		nvkm_mask(device, 0x800004 + coff, 0x00000800, 0x00000800);
		gk104_fअगरo_gpfअगरo_kick(chan);
		gk104_fअगरo_runlist_update(fअगरo, chan->runl);
	पूर्ण

	nvkm_wr32(device, 0x800000 + coff, 0x00000000);
पूर्ण

व्योम
gk104_fअगरo_gpfअगरo_init(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा gk104_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 addr = chan->base.inst->addr >> 12;
	u32 coff = chan->base.chid * 8;

	nvkm_mask(device, 0x800004 + coff, 0x000f0000, chan->runl << 16);
	nvkm_wr32(device, 0x800000 + coff, 0x80000000 | addr);

	अगर (list_empty(&chan->head) && !chan->समाप्तed) अणु
		gk104_fअगरo_runlist_insert(fअगरo, chan);
		nvkm_mask(device, 0x800004 + coff, 0x00000400, 0x00000400);
		gk104_fअगरo_runlist_update(fअगरo, chan->runl);
		nvkm_mask(device, 0x800004 + coff, 0x00000400, 0x00000400);
	पूर्ण
पूर्ण

व्योम *
gk104_fअगरo_gpfअगरo_dtor(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	nvkm_memory_unref(&chan->mthd);
	kमुक्त(chan->cgrp);
	वापस chan;
पूर्ण

स्थिर काष्ठा nvkm_fअगरo_chan_func
gk104_fअगरo_gpfअगरo_func = अणु
	.dtor = gk104_fअगरo_gpfअगरo_dtor,
	.init = gk104_fअगरo_gpfअगरo_init,
	.fini = gk104_fअगरo_gpfअगरo_fini,
	.ntfy = gf100_fअगरo_chan_ntfy,
	.engine_ctor = gk104_fअगरo_gpfअगरo_engine_ctor,
	.engine_dtor = gk104_fअगरo_gpfअगरo_engine_dtor,
	.engine_init = gk104_fअगरo_gpfअगरo_engine_init,
	.engine_fini = gk104_fअगरo_gpfअगरo_engine_fini,
पूर्ण;

अटल पूर्णांक
gk104_fअगरo_gpfअगरo_new_(काष्ठा gk104_fअगरo *fअगरo, u64 *runlists, u16 *chid,
		       u64 vmm, u64 ioffset, u64 ilength, u64 *inst, bool priv,
		       स्थिर काष्ठा nvkm_oclass *oclass,
		       काष्ठा nvkm_object **pobject)
अणु
	काष्ठा gk104_fअगरo_chan *chan;
	पूर्णांक runlist = ffs(*runlists) -1, ret, i;
	u64 usermem;

	अगर (!vmm || runlist < 0 || runlist >= fअगरo->runlist_nr)
		वापस -EINVAL;
	*runlists = BIT_ULL(runlist);

	/* Allocate the channel. */
	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &chan->base.object;
	chan->fअगरo = fअगरo;
	chan->runl = runlist;
	INIT_LIST_HEAD(&chan->head);

	ret = nvkm_fअगरo_chan_ctor(&gk104_fअगरo_gpfअगरo_func, &fअगरo->base,
				  0x1000, 0x1000, true, vmm, 0, fअगरo->runlist[runlist].engm_sw,
				  1, fअगरo->user.bar->addr, 0x200,
				  oclass, &chan->base);
	अगर (ret)
		वापस ret;

	*chid = chan->base.chid;
	*inst = chan->base.inst->addr;

	/* Hack to support GPUs where even inभागidual channels should be
	 * part of a channel group.
	 */
	अगर (fअगरo->func->cgrp_क्रमce) अणु
		अगर (!(chan->cgrp = kदो_स्मृति(माप(*chan->cgrp), GFP_KERNEL)))
			वापस -ENOMEM;
		chan->cgrp->id = chan->base.chid;
		INIT_LIST_HEAD(&chan->cgrp->head);
		INIT_LIST_HEAD(&chan->cgrp->chan);
		chan->cgrp->chan_nr = 0;
	पूर्ण

	/* Clear channel control रेजिस्टरs. */
	usermem = chan->base.chid * 0x200;
	ilength = order_base_2(ilength / 8);

	nvkm_kmap(fअगरo->user.mem);
	क्रम (i = 0; i < 0x200; i += 4)
		nvkm_wo32(fअगरo->user.mem, usermem + i, 0x00000000);
	nvkm_करोne(fअगरo->user.mem);
	usermem = nvkm_memory_addr(fअगरo->user.mem) + usermem;

	/* RAMFC */
	nvkm_kmap(chan->base.inst);
	nvkm_wo32(chan->base.inst, 0x08, lower_32_bits(usermem));
	nvkm_wo32(chan->base.inst, 0x0c, upper_32_bits(usermem));
	nvkm_wo32(chan->base.inst, 0x10, 0x0000face);
	nvkm_wo32(chan->base.inst, 0x30, 0xfffff902);
	nvkm_wo32(chan->base.inst, 0x48, lower_32_bits(ioffset));
	nvkm_wo32(chan->base.inst, 0x4c, upper_32_bits(ioffset) |
					 (ilength << 16));
	nvkm_wo32(chan->base.inst, 0x84, 0x20400000);
	nvkm_wo32(chan->base.inst, 0x94, 0x30000001);
	nvkm_wo32(chan->base.inst, 0x9c, 0x00000100);
	nvkm_wo32(chan->base.inst, 0xac, 0x0000001f);
	nvkm_wo32(chan->base.inst, 0xe4, priv ? 0x00000020 : 0x00000000);
	nvkm_wo32(chan->base.inst, 0xe8, chan->base.chid);
	nvkm_wo32(chan->base.inst, 0xb8, 0xf8000000);
	nvkm_wo32(chan->base.inst, 0xf8, 0x10003080); /* 0x002310 */
	nvkm_wo32(chan->base.inst, 0xfc, 0x10000010); /* 0x002350 */
	nvkm_करोne(chan->base.inst);
	वापस 0;
पूर्ण

पूर्णांक
gk104_fअगरo_gpfअगरo_new(काष्ठा gk104_fअगरo *fअगरo, स्थिर काष्ठा nvkm_oclass *oclass,
		      व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_object *parent = oclass->parent;
	जोड़ अणु
		काष्ठा kepler_channel_gpfअगरo_a_v0 v0;
	पूर्ण *args = data;
	पूर्णांक ret = -ENOSYS;

	nvअगर_ioctl(parent, "create channel gpfifo size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create channel gpfifo vers %d vmm %llx "
				   "ioffset %016llx ilength %08x "
				   "runlist %016llx priv %d\n",
			   args->v0.version, args->v0.vmm, args->v0.ioffset,
			   args->v0.ilength, args->v0.runlist, args->v0.priv);
		अगर (args->v0.priv && !oclass->client->super)
			वापस -EINVAL;
		वापस gk104_fअगरo_gpfअगरo_new_(fअगरo,
					      &args->v0.runlist,
					      &args->v0.chid,
					       args->v0.vmm,
					       args->v0.ioffset,
					       args->v0.ilength,
					      &args->v0.inst,
					       args->v0.priv,
					      oclass, pobject);
	पूर्ण

	वापस ret;
पूर्ण
