<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
 */
#समावेश "changk104.h"
#समावेश "cgrp.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>

#समावेश <nvअगर/clc36f.h>
#समावेश <nvअगर/unpack.h>

अटल u32
gv100_fअगरo_gpfअगरo_submit_token(काष्ठा nvkm_fअगरo_chan *chan)
अणु
	वापस chan->chid;
पूर्ण

अटल पूर्णांक
gv100_fअगरo_gpfअगरo_engine_valid(काष्ठा gk104_fअगरo_chan *chan, bool ce, bool valid)
अणु
	काष्ठा nvkm_subdev *subdev = &chan->base.fअगरo->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 mask = ce ? 0x00020000 : 0x00010000;
	स्थिर u32 data = valid ? mask : 0x00000000;
	पूर्णांक ret;

	/* Block runlist to prevent the channel from being rescheduled. */
	mutex_lock(&chan->fअगरo->base.mutex);
	nvkm_mask(device, 0x002630, BIT(chan->runl), BIT(chan->runl));

	/* Preempt the channel. */
	ret = gk104_fअगरo_gpfअगरo_kick_locked(chan);
	अगर (ret == 0) अणु
		/* Update engine context validity. */
		nvkm_kmap(chan->base.inst);
		nvkm_mo32(chan->base.inst, 0x0ac, mask, data);
		nvkm_करोne(chan->base.inst);
	पूर्ण

	/* Resume runlist. */
	nvkm_mask(device, 0x002630, BIT(chan->runl), 0);
	mutex_unlock(&chan->fअगरo->base.mutex);
	वापस ret;
पूर्ण

पूर्णांक
gv100_fअगरo_gpfअगरo_engine_fini(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा nvkm_gpuobj *inst = chan->base.inst;
	पूर्णांक ret;

	अगर (engine->subdev.type == NVKM_ENGINE_CE)
		वापस gk104_fअगरo_gpfअगरo_kick(chan);

	ret = gv100_fअगरo_gpfअगरo_engine_valid(chan, false, false);
	अगर (ret && suspend)
		वापस ret;

	nvkm_kmap(inst);
	nvkm_wo32(inst, 0x0210, 0x00000000);
	nvkm_wo32(inst, 0x0214, 0x00000000);
	nvkm_करोne(inst);
	वापस ret;
पूर्ण

पूर्णांक
gv100_fअगरo_gpfअगरo_engine_init(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine)
अणु
	काष्ठा gk104_fअगरo_chan *chan = gk104_fअगरo_chan(base);
	काष्ठा gk104_fअगरo_engn *engn = gk104_fअगरo_gpfअगरo_engine(chan, engine);
	काष्ठा nvkm_gpuobj *inst = chan->base.inst;

	अगर (engine->subdev.type == NVKM_ENGINE_CE)
		वापस 0;

	nvkm_kmap(inst);
	nvkm_wo32(inst, 0x210, lower_32_bits(engn->vma->addr) | 0x00000004);
	nvkm_wo32(inst, 0x214, upper_32_bits(engn->vma->addr));
	nvkm_करोne(inst);

	वापस gv100_fअगरo_gpfअगरo_engine_valid(chan, false, true);
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_chan_func
gv100_fअगरo_gpfअगरo = अणु
	.dtor = gk104_fअगरo_gpfअगरo_dtor,
	.init = gk104_fअगरo_gpfअगरo_init,
	.fini = gk104_fअगरo_gpfअगरo_fini,
	.ntfy = gf100_fअगरo_chan_ntfy,
	.engine_ctor = gk104_fअगरo_gpfअगरo_engine_ctor,
	.engine_dtor = gk104_fअगरo_gpfअगरo_engine_dtor,
	.engine_init = gv100_fअगरo_gpfअगरo_engine_init,
	.engine_fini = gv100_fअगरo_gpfअगरo_engine_fini,
	.submit_token = gv100_fअगरo_gpfअगरo_submit_token,
पूर्ण;

पूर्णांक
gv100_fअगरo_gpfअगरo_new_(स्थिर काष्ठा nvkm_fअगरo_chan_func *func,
		       काष्ठा gk104_fअगरo *fअगरo, u64 *runlists, u16 *chid,
		       u64 vmm, u64 ioffset, u64 ilength, u64 *inst, bool priv,
		       u32 *token, स्थिर काष्ठा nvkm_oclass *oclass,
		       काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा gk104_fअगरo_chan *chan;
	पूर्णांक runlist = ffs(*runlists) -1, ret, i;
	u64 usermem, mthd;
	u32 size;

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

	ret = nvkm_fअगरo_chan_ctor(func, &fअगरo->base, 0x1000, 0x1000, true, vmm,
				  0, fअगरo->runlist[runlist].engm, 1, fअगरo->user.bar->addr, 0x200,
				  oclass, &chan->base);
	अगर (ret)
		वापस ret;

	*chid = chan->base.chid;
	*inst = chan->base.inst->addr;
	*token = chan->base.func->submit_token(&chan->base);

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

	/* Allocate fault method buffer (magics come from nvgpu). */
	size = nvkm_rd32(device, 0x104028); /* NV_PCE_PCE_MAP */
	size = 27 * 5 * (((9 + 1 + 3) * hweight32(size)) + 2);
	size = roundup(size, PAGE_SIZE);

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, size, 0x1000, true,
			      &chan->mthd);
	अगर (ret)
		वापस ret;

	mthd = nvkm_memory_bar2(chan->mthd);
	अगर (mthd == ~0ULL)
		वापस -EFAULT;

	/* RAMFC */
	nvkm_kmap(chan->base.inst);
	nvkm_wo32(chan->base.inst, 0x008, lower_32_bits(usermem));
	nvkm_wo32(chan->base.inst, 0x00c, upper_32_bits(usermem));
	nvkm_wo32(chan->base.inst, 0x010, 0x0000face);
	nvkm_wo32(chan->base.inst, 0x030, 0x7ffff902);
	nvkm_wo32(chan->base.inst, 0x048, lower_32_bits(ioffset));
	nvkm_wo32(chan->base.inst, 0x04c, upper_32_bits(ioffset) |
					  (ilength << 16));
	nvkm_wo32(chan->base.inst, 0x084, 0x20400000);
	nvkm_wo32(chan->base.inst, 0x094, 0x30000001);
	nvkm_wo32(chan->base.inst, 0x0e4, priv ? 0x00000020 : 0x00000000);
	nvkm_wo32(chan->base.inst, 0x0e8, chan->base.chid);
	nvkm_wo32(chan->base.inst, 0x0f4, 0x00001000);
	nvkm_wo32(chan->base.inst, 0x0f8, 0x10003080);
	nvkm_mo32(chan->base.inst, 0x218, 0x00000000, 0x00000000);
	nvkm_wo32(chan->base.inst, 0x220, lower_32_bits(mthd));
	nvkm_wo32(chan->base.inst, 0x224, upper_32_bits(mthd));
	nvkm_करोne(chan->base.inst);
	वापस gv100_fअगरo_gpfअगरo_engine_valid(chan, true, true);
पूर्ण

पूर्णांक
gv100_fअगरo_gpfअगरo_new(काष्ठा gk104_fअगरo *fअगरo, स्थिर काष्ठा nvkm_oclass *oclass,
		      व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा nvkm_object *parent = oclass->parent;
	जोड़ अणु
		काष्ठा volta_channel_gpfअगरo_a_v0 v0;
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
		वापस gv100_fअगरo_gpfअगरo_new_(&gv100_fअगरo_gpfअगरo, fअगरo,
					      &args->v0.runlist,
					      &args->v0.chid,
					       args->v0.vmm,
					       args->v0.ioffset,
					       args->v0.ilength,
					      &args->v0.inst,
					       args->v0.priv,
					      &args->v0.token,
					      oclass, pobject);
	पूर्ण

	वापस ret;
पूर्ण
