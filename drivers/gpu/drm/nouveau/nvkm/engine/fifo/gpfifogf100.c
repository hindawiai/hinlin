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
#समावेश "changf100.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/fb.h>
#समावेश <subdev/समयr.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl906f.h>
#समावेश <nvअगर/unpack.h>

पूर्णांक
gf100_fअगरo_chan_ntfy(काष्ठा nvkm_fअगरo_chan *chan, u32 type,
		     काष्ठा nvkm_event **pevent)
अणु
	चयन (type) अणु
	हाल NV906F_V0_NTFY_NON_STALL_INTERRUPT:
		*pevent = &chan->fअगरo->uevent;
		वापस 0;
	हाल NV906F_V0_NTFY_KILLED:
		*pevent = &chan->fअगरo->kevent;
		वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल u32
gf100_fअगरo_gpfअगरo_engine_addr(काष्ठा nvkm_engine *engine)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_SW    : वापस 0;
	हाल NVKM_ENGINE_GR    : वापस 0x0210;
	हाल NVKM_ENGINE_CE    : वापस 0x0230 + (engine->subdev.inst * 0x10);
	हाल NVKM_ENGINE_MSPDEC: वापस 0x0250;
	हाल NVKM_ENGINE_MSPPP : वापस 0x0260;
	हाल NVKM_ENGINE_MSVLD : वापस 0x0270;
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा gf100_fअगरo_engn *
gf100_fअगरo_gpfअगरo_engine(काष्ठा gf100_fअगरo_chan *chan, काष्ठा nvkm_engine *engine)
अणु
	पूर्णांक engi = chan->base.fअगरo->func->engine_id(chan->base.fअगरo, engine);
	अगर (engi >= 0)
		वापस &chan->engn[engi];
	वापस शून्य;
पूर्ण

अटल पूर्णांक
gf100_fअगरo_gpfअगरo_engine_fini(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine, bool suspend)
अणु
	स्थिर u32 offset = gf100_fअगरo_gpfअगरo_engine_addr(engine);
	काष्ठा gf100_fअगरo_chan *chan = gf100_fअगरo_chan(base);
	काष्ठा nvkm_subdev *subdev = &chan->fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_gpuobj *inst = chan->base.inst;
	पूर्णांक ret = 0;

	mutex_lock(&chan->fअगरo->base.mutex);
	nvkm_wr32(device, 0x002634, chan->base.chid);
	अगर (nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x002634) == chan->base.chid)
			अवरोध;
	) < 0) अणु
		nvkm_error(subdev, "channel %d [%s] kick timeout\n",
			   chan->base.chid, chan->base.object.client->name);
		ret = -ETIMEDOUT;
	पूर्ण
	mutex_unlock(&chan->fअगरo->base.mutex);

	अगर (ret && suspend)
		वापस ret;

	अगर (offset) अणु
		nvkm_kmap(inst);
		nvkm_wo32(inst, offset + 0x00, 0x00000000);
		nvkm_wo32(inst, offset + 0x04, 0x00000000);
		nvkm_करोne(inst);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
gf100_fअगरo_gpfअगरo_engine_init(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine)
अणु
	स्थिर u32 offset = gf100_fअगरo_gpfअगरo_engine_addr(engine);
	काष्ठा gf100_fअगरo_chan *chan = gf100_fअगरo_chan(base);
	काष्ठा gf100_fअगरo_engn *engn = gf100_fअगरo_gpfअगरo_engine(chan, engine);
	काष्ठा nvkm_gpuobj *inst = chan->base.inst;

	अगर (offset) अणु
		nvkm_kmap(inst);
		nvkm_wo32(inst, offset + 0x00, lower_32_bits(engn->vma->addr) | 4);
		nvkm_wo32(inst, offset + 0x04, upper_32_bits(engn->vma->addr));
		nvkm_करोne(inst);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
gf100_fअगरo_gpfअगरo_engine_dtor(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine)
अणु
	काष्ठा gf100_fअगरo_chan *chan = gf100_fअगरo_chan(base);
	काष्ठा gf100_fअगरo_engn *engn = gf100_fअगरo_gpfअगरo_engine(chan, engine);
	nvkm_vmm_put(chan->base.vmm, &engn->vma);
	nvkm_gpuobj_del(&engn->inst);
पूर्ण

अटल पूर्णांक
gf100_fअगरo_gpfअगरo_engine_ctor(काष्ठा nvkm_fअगरo_chan *base,
			      काष्ठा nvkm_engine *engine,
			      काष्ठा nvkm_object *object)
अणु
	काष्ठा gf100_fअगरo_chan *chan = gf100_fअगरo_chan(base);
	काष्ठा gf100_fअगरo_engn *engn = gf100_fअगरo_gpfअगरo_engine(chan, engine);
	पूर्णांक ret;

	अगर (!gf100_fअगरo_gpfअगरo_engine_addr(engine))
		वापस 0;

	ret = nvkm_object_bind(object, शून्य, 0, &engn->inst);
	अगर (ret)
		वापस ret;

	ret = nvkm_vmm_get(chan->base.vmm, 12, engn->inst->size, &engn->vma);
	अगर (ret)
		वापस ret;

	वापस nvkm_memory_map(engn->inst, 0, chan->base.vmm, engn->vma, शून्य, 0);
पूर्ण

अटल व्योम
gf100_fअगरo_gpfअगरo_fini(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा gf100_fअगरo_chan *chan = gf100_fअगरo_chan(base);
	काष्ठा gf100_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 coff = chan->base.chid * 8;

	अगर (!list_empty(&chan->head) && !chan->समाप्तed) अणु
		gf100_fअगरo_runlist_हटाओ(fअगरo, chan);
		nvkm_mask(device, 0x003004 + coff, 0x00000001, 0x00000000);
		gf100_fअगरo_runlist_commit(fअगरo);
	पूर्ण

	gf100_fअगरo_पूर्णांकr_engine(fअगरo);

	nvkm_wr32(device, 0x003000 + coff, 0x00000000);
पूर्ण

अटल व्योम
gf100_fअगरo_gpfअगरo_init(काष्ठा nvkm_fअगरo_chan *base)
अणु
	काष्ठा gf100_fअगरo_chan *chan = gf100_fअगरo_chan(base);
	काष्ठा gf100_fअगरo *fअगरo = chan->fअगरo;
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 addr = chan->base.inst->addr >> 12;
	u32 coff = chan->base.chid * 8;

	nvkm_wr32(device, 0x003000 + coff, 0xc0000000 | addr);

	अगर (list_empty(&chan->head) && !chan->समाप्तed) अणु
		gf100_fअगरo_runlist_insert(fअगरo, chan);
		nvkm_wr32(device, 0x003004 + coff, 0x001f0001);
		gf100_fअगरo_runlist_commit(fअगरo);
	पूर्ण
पूर्ण

अटल व्योम *
gf100_fअगरo_gpfअगरo_dtor(काष्ठा nvkm_fअगरo_chan *base)
अणु
	वापस gf100_fअगरo_chan(base);
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_chan_func
gf100_fअगरo_gpfअगरo_func = अणु
	.dtor = gf100_fअगरo_gpfअगरo_dtor,
	.init = gf100_fअगरo_gpfअगरo_init,
	.fini = gf100_fअगरo_gpfअगरo_fini,
	.ntfy = gf100_fअगरo_chan_ntfy,
	.engine_ctor = gf100_fअगरo_gpfअगरo_engine_ctor,
	.engine_dtor = gf100_fअगरo_gpfअगरo_engine_dtor,
	.engine_init = gf100_fअगरo_gpfअगरo_engine_init,
	.engine_fini = gf100_fअगरo_gpfअगरo_engine_fini,
पूर्ण;

अटल पूर्णांक
gf100_fअगरo_gpfअगरo_new(काष्ठा nvkm_fअगरo *base, स्थिर काष्ठा nvkm_oclass *oclass,
		      व्योम *data, u32 size, काष्ठा nvkm_object **pobject)
अणु
	जोड़ अणु
		काष्ठा fermi_channel_gpfअगरo_v0 v0;
	पूर्ण *args = data;
	काष्ठा gf100_fअगरo *fअगरo = gf100_fअगरo(base);
	काष्ठा nvkm_object *parent = oclass->parent;
	काष्ठा gf100_fअगरo_chan *chan;
	u64 usermem, ioffset, ilength;
	पूर्णांक ret = -ENOSYS, i;

	nvअगर_ioctl(parent, "create channel gpfifo size %d\n", size);
	अगर (!(ret = nvअगर_unpack(ret, &data, &size, args->v0, 0, 0, false))) अणु
		nvअगर_ioctl(parent, "create channel gpfifo vers %d vmm %llx "
				   "ioffset %016llx ilength %08x\n",
			   args->v0.version, args->v0.vmm, args->v0.ioffset,
			   args->v0.ilength);
		अगर (!args->v0.vmm)
			वापस -EINVAL;
	पूर्ण अन्यथा
		वापस ret;

	/* allocate channel */
	अगर (!(chan = kzalloc(माप(*chan), GFP_KERNEL)))
		वापस -ENOMEM;
	*pobject = &chan->base.object;
	chan->fअगरo = fअगरo;
	INIT_LIST_HEAD(&chan->head);

	ret = nvkm_fअगरo_chan_ctor(&gf100_fअगरo_gpfअगरo_func, &fअगरo->base,
				  0x1000, 0x1000, true, args->v0.vmm, 0,
				  BIT(GF100_FIFO_ENGN_GR) |
				  BIT(GF100_FIFO_ENGN_MSPDEC) |
				  BIT(GF100_FIFO_ENGN_MSPPP) |
				  BIT(GF100_FIFO_ENGN_MSVLD) |
				  BIT(GF100_FIFO_ENGN_CE0) |
				  BIT(GF100_FIFO_ENGN_CE1) |
				  BIT(GF100_FIFO_ENGN_SW),
				  1, fअगरo->user.bar->addr, 0x1000,
				  oclass, &chan->base);
	अगर (ret)
		वापस ret;

	args->v0.chid = chan->base.chid;

	/* clear channel control रेजिस्टरs */

	usermem = chan->base.chid * 0x1000;
	ioffset = args->v0.ioffset;
	ilength = order_base_2(args->v0.ilength / 8);

	nvkm_kmap(fअगरo->user.mem);
	क्रम (i = 0; i < 0x1000; i += 4)
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
	nvkm_wo32(chan->base.inst, 0x54, 0x00000002);
	nvkm_wo32(chan->base.inst, 0x84, 0x20400000);
	nvkm_wo32(chan->base.inst, 0x94, 0x30000001);
	nvkm_wo32(chan->base.inst, 0x9c, 0x00000100);
	nvkm_wo32(chan->base.inst, 0xa4, 0x1f1f1f1f);
	nvkm_wo32(chan->base.inst, 0xa8, 0x1f1f1f1f);
	nvkm_wo32(chan->base.inst, 0xac, 0x0000001f);
	nvkm_wo32(chan->base.inst, 0xb8, 0xf8000000);
	nvkm_wo32(chan->base.inst, 0xf8, 0x10003080); /* 0x002310 */
	nvkm_wo32(chan->base.inst, 0xfc, 0x10000010); /* 0x002350 */
	nvkm_करोne(chan->base.inst);
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_fअगरo_chan_oclass
gf100_fअगरo_gpfअगरo_oclass = अणु
	.base.oclass = FERMI_CHANNEL_GPFIFO,
	.base.minver = 0,
	.base.maxver = 0,
	.ctor = gf100_fअगरo_gpfअगरo_new,
पूर्ण;
