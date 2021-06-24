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
#समावेश "gk104.h"
#समावेश "cgrp.h"
#समावेश "changk104.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/bar.h>
#समावेश <subdev/fault.h>
#समावेश <subdev/समयr.h>
#समावेश <subdev/top.h>
#समावेश <engine/sw.h>

#समावेश <nvअगर/class.h>
#समावेश <nvअगर/cl0080.h>

व्योम
gk104_fअगरo_engine_status(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक engn,
			 काष्ठा gk104_fअगरo_engine_status *status)
अणु
	काष्ठा nvkm_engine *engine = fअगरo->engine[engn].engine;
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x002640 + (engn * 0x08));

	status->busy     = !!(stat & 0x80000000);
	status->faulted  = !!(stat & 0x40000000);
	status->next.tsg = !!(stat & 0x10000000);
	status->next.id  =   (stat & 0x0fff0000) >> 16;
	status->chsw     = !!(stat & 0x00008000);
	status->save     = !!(stat & 0x00004000);
	status->load     = !!(stat & 0x00002000);
	status->prev.tsg = !!(stat & 0x00001000);
	status->prev.id  =   (stat & 0x00000fff);
	status->chan     = शून्य;

	अगर (status->busy && status->chsw) अणु
		अगर (status->load && status->save) अणु
			अगर (engine && nvkm_engine_chsw_load(engine))
				status->chan = &status->next;
			अन्यथा
				status->chan = &status->prev;
		पूर्ण अन्यथा
		अगर (status->load) अणु
			status->chan = &status->next;
		पूर्ण अन्यथा अणु
			status->chan = &status->prev;
		पूर्ण
	पूर्ण अन्यथा
	अगर (status->load) अणु
		status->chan = &status->prev;
	पूर्ण

	nvkm_debug(subdev, "engine %02d: busy %d faulted %d chsw %d "
			   "save %d load %d %sid %d%s-> %sid %d%s\n",
		   engn, status->busy, status->faulted,
		   status->chsw, status->save, status->load,
		   status->prev.tsg ? "tsg" : "ch", status->prev.id,
		   status->chan == &status->prev ? "*" : " ",
		   status->next.tsg ? "tsg" : "ch", status->next.id,
		   status->chan == &status->next ? "*" : " ");
पूर्ण

पूर्णांक
gk104_fअगरo_class_new(काष्ठा nvkm_fअगरo *base, स्थिर काष्ठा nvkm_oclass *oclass,
		     व्योम *argv, u32 argc, काष्ठा nvkm_object **pobject)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	अगर (oclass->engn == &fअगरo->func->chan) अणु
		स्थिर काष्ठा gk104_fअगरo_chan_user *user = oclass->engn;
		वापस user->ctor(fअगरo, oclass, argv, argc, pobject);
	पूर्ण अन्यथा
	अगर (oclass->engn == &fअगरo->func->user) अणु
		स्थिर काष्ठा gk104_fअगरo_user_user *user = oclass->engn;
		वापस user->ctor(oclass, argv, argc, pobject);
	पूर्ण
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

पूर्णांक
gk104_fअगरo_class_get(काष्ठा nvkm_fअगरo *base, पूर्णांक index,
		     काष्ठा nvkm_oclass *oclass)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	पूर्णांक c = 0;

	अगर (fअगरo->func->user.ctor && c++ == index) अणु
		oclass->base =  fअगरo->func->user.user;
		oclass->engn = &fअगरo->func->user;
		वापस 0;
	पूर्ण

	अगर (fअगरo->func->chan.ctor && c++ == index) अणु
		oclass->base =  fअगरo->func->chan.user;
		oclass->engn = &fअगरo->func->chan;
		वापस 0;
	पूर्ण

	वापस c;
पूर्ण

व्योम
gk104_fअगरo_uevent_fini(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	nvkm_mask(device, 0x002140, 0x80000000, 0x00000000);
पूर्ण

व्योम
gk104_fअगरo_uevent_init(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	nvkm_mask(device, 0x002140, 0x80000000, 0x80000000);
पूर्ण

व्योम
gk104_fअगरo_runlist_commit(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक runl,
			  काष्ठा nvkm_memory *mem, पूर्णांक nr)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	पूर्णांक target;

	चयन (nvkm_memory_target(mem)) अणु
	हाल NVKM_MEM_TARGET_VRAM: target = 0; अवरोध;
	हाल NVKM_MEM_TARGET_NCOH: target = 3; अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	nvkm_wr32(device, 0x002270, (nvkm_memory_addr(mem) >> 12) |
				    (target << 28));
	nvkm_wr32(device, 0x002274, (runl << 20) | nr);

	अगर (nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x002284 + (runl * 0x08)) & 0x00100000))
			अवरोध;
	) < 0)
		nvkm_error(subdev, "runlist %d update timeout\n", runl);
पूर्ण

व्योम
gk104_fअगरo_runlist_update(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक runl)
अणु
	स्थिर काष्ठा gk104_fअगरo_runlist_func *func = fअगरo->func->runlist;
	काष्ठा gk104_fअगरo_chan *chan;
	काष्ठा nvkm_memory *mem;
	काष्ठा nvkm_fअगरo_cgrp *cgrp;
	पूर्णांक nr = 0;

	mutex_lock(&fअगरo->base.mutex);
	mem = fअगरo->runlist[runl].mem[fअगरo->runlist[runl].next];
	fअगरo->runlist[runl].next = !fअगरo->runlist[runl].next;

	nvkm_kmap(mem);
	list_क्रम_each_entry(chan, &fअगरo->runlist[runl].chan, head) अणु
		func->chan(chan, mem, nr++ * func->size);
	पूर्ण

	list_क्रम_each_entry(cgrp, &fअगरo->runlist[runl].cgrp, head) अणु
		func->cgrp(cgrp, mem, nr++ * func->size);
		list_क्रम_each_entry(chan, &cgrp->chan, head) अणु
			func->chan(chan, mem, nr++ * func->size);
		पूर्ण
	पूर्ण
	nvkm_करोne(mem);

	func->commit(fअगरo, runl, mem, nr);
	mutex_unlock(&fअगरo->base.mutex);
पूर्ण

व्योम
gk104_fअगरo_runlist_हटाओ(काष्ठा gk104_fअगरo *fअगरo, काष्ठा gk104_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_fअगरo_cgrp *cgrp = chan->cgrp;
	mutex_lock(&fअगरo->base.mutex);
	अगर (!list_empty(&chan->head)) अणु
		list_del_init(&chan->head);
		अगर (cgrp && !--cgrp->chan_nr)
			list_del_init(&cgrp->head);
	पूर्ण
	mutex_unlock(&fअगरo->base.mutex);
पूर्ण

व्योम
gk104_fअगरo_runlist_insert(काष्ठा gk104_fअगरo *fअगरo, काष्ठा gk104_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_fअगरo_cgrp *cgrp = chan->cgrp;
	mutex_lock(&fअगरo->base.mutex);
	अगर (cgrp) अणु
		अगर (!cgrp->chan_nr++)
			list_add_tail(&cgrp->head, &fअगरo->runlist[chan->runl].cgrp);
		list_add_tail(&chan->head, &cgrp->chan);
	पूर्ण अन्यथा अणु
		list_add_tail(&chan->head, &fअगरo->runlist[chan->runl].chan);
	पूर्ण
	mutex_unlock(&fअगरo->base.mutex);
पूर्ण

व्योम
gk104_fअगरo_runlist_chan(काष्ठा gk104_fअगरo_chan *chan,
			काष्ठा nvkm_memory *memory, u32 offset)
अणु
	nvkm_wo32(memory, offset + 0, chan->base.chid);
	nvkm_wo32(memory, offset + 4, 0x00000000);
पूर्ण

स्थिर काष्ठा gk104_fअगरo_runlist_func
gk104_fअगरo_runlist = अणु
	.size = 8,
	.chan = gk104_fअगरo_runlist_chan,
	.commit = gk104_fअगरo_runlist_commit,
पूर्ण;

व्योम
gk104_fअगरo_pbdma_init(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	nvkm_wr32(device, 0x000204, (1 << fअगरo->pbdma_nr) - 1);
पूर्ण

पूर्णांक
gk104_fअगरo_pbdma_nr(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	/* Determine number of PBDMAs by checking valid enable bits. */
	nvkm_wr32(device, 0x000204, 0xffffffff);
	वापस hweight32(nvkm_rd32(device, 0x000204));
पूर्ण

स्थिर काष्ठा gk104_fअगरo_pbdma_func
gk104_fअगरo_pbdma = अणु
	.nr = gk104_fअगरo_pbdma_nr,
	.init = gk104_fअगरo_pbdma_init,
पूर्ण;

काष्ठा nvkm_engine *
gk104_fअगरo_id_engine(काष्ठा nvkm_fअगरo *base, पूर्णांक engi)
अणु
	अगर (engi == GK104_FIFO_ENGN_SW)
		वापस nvkm_device_engine(base->engine.subdev.device, NVKM_ENGINE_SW, 0);

	वापस gk104_fअगरo(base)->engine[engi].engine;
पूर्ण

पूर्णांक
gk104_fअगरo_engine_id(काष्ठा nvkm_fअगरo *base, काष्ठा nvkm_engine *engine)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	पूर्णांक engn;

	अगर (engine->subdev.type == NVKM_ENGINE_SW)
		वापस GK104_FIFO_ENGN_SW;

	क्रम (engn = 0; engn < fअगरo->engine_nr && engine; engn++) अणु
		अगर (fअगरo->engine[engn].engine == engine)
			वापस engn;
	पूर्ण

	WARN_ON(1);
	वापस -1;
पूर्ण

अटल व्योम
gk104_fअगरo_recover_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा gk104_fअगरo *fअगरo = container_of(w, typeof(*fअगरo), recover.work);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_engine *engine;
	अचिन्हित दीर्घ flags;
	u32 engm, runm, toकरो;
	पूर्णांक engn, runl;

	spin_lock_irqsave(&fअगरo->base.lock, flags);
	runm = fअगरo->recover.runm;
	engm = fअगरo->recover.engm;
	fअगरo->recover.engm = 0;
	fअगरo->recover.runm = 0;
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);

	nvkm_mask(device, 0x002630, runm, runm);

	क्रम (toकरो = engm; engn = __ffs(toकरो), toकरो; toकरो &= ~BIT(engn)) अणु
		अगर ((engine = fअगरo->engine[engn].engine)) अणु
			nvkm_subdev_fini(&engine->subdev, false);
			WARN_ON(nvkm_subdev_init(&engine->subdev));
		पूर्ण
	पूर्ण

	क्रम (toकरो = runm; runl = __ffs(toकरो), toकरो; toकरो &= ~BIT(runl))
		gk104_fअगरo_runlist_update(fअगरo, runl);

	nvkm_wr32(device, 0x00262c, runm);
	nvkm_mask(device, 0x002630, runm, 0x00000000);
पूर्ण

अटल व्योम gk104_fअगरo_recover_engn(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक engn);

अटल व्योम
gk104_fअगरo_recover_runl(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक runl)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 runm = BIT(runl);

	निश्चित_spin_locked(&fअगरo->base.lock);
	अगर (fअगरo->recover.runm & runm)
		वापस;
	fअगरo->recover.runm |= runm;

	/* Block runlist to prevent channel assignment(s) from changing. */
	nvkm_mask(device, 0x002630, runm, runm);

	/* Schedule recovery. */
	nvkm_warn(subdev, "runlist %d: scheduled for recovery\n", runl);
	schedule_work(&fअगरo->recover.work);
पूर्ण

अटल काष्ठा gk104_fअगरo_chan *
gk104_fअगरo_recover_chid(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक runl, पूर्णांक chid)
अणु
	काष्ठा gk104_fअगरo_chan *chan;
	काष्ठा nvkm_fअगरo_cgrp *cgrp;

	list_क्रम_each_entry(chan, &fअगरo->runlist[runl].chan, head) अणु
		अगर (chan->base.chid == chid) अणु
			list_del_init(&chan->head);
			वापस chan;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(cgrp, &fअगरo->runlist[runl].cgrp, head) अणु
		अगर (cgrp->id == chid) अणु
			chan = list_first_entry(&cgrp->chan, typeof(*chan), head);
			list_del_init(&chan->head);
			अगर (!--cgrp->chan_nr)
				list_del_init(&cgrp->head);
			वापस chan;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम
gk104_fअगरo_recover_chan(काष्ठा nvkm_fअगरo *base, पूर्णांक chid)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32  stat = nvkm_rd32(device, 0x800004 + (chid * 0x08));
	स्थिर u32  runl = (stat & 0x000f0000) >> 16;
	स्थिर bool used = (stat & 0x00000001);
	अचिन्हित दीर्घ engn, engm = fअगरo->runlist[runl].engm;
	काष्ठा gk104_fअगरo_chan *chan;

	निश्चित_spin_locked(&fअगरo->base.lock);
	अगर (!used)
		वापस;

	/* Lookup SW state क्रम channel, and mark it as dead. */
	chan = gk104_fअगरo_recover_chid(fअगरo, runl, chid);
	अगर (chan) अणु
		chan->समाप्तed = true;
		nvkm_fअगरo_kevent(&fअगरo->base, chid);
	पूर्ण

	/* Disable channel. */
	nvkm_wr32(device, 0x800004 + (chid * 0x08), stat | 0x00000800);
	nvkm_warn(subdev, "channel %d: killed\n", chid);

	/* Block channel assignments from changing during recovery. */
	gk104_fअगरo_recover_runl(fअगरo, runl);

	/* Schedule recovery क्रम any engines the channel is on. */
	क्रम_each_set_bit(engn, &engm, fअगरo->engine_nr) अणु
		काष्ठा gk104_fअगरo_engine_status status;
		gk104_fअगरo_engine_status(fअगरo, engn, &status);
		अगर (!status.chan || status.chan->id != chid)
			जारी;
		gk104_fअगरo_recover_engn(fअगरo, engn);
	पूर्ण
पूर्ण

अटल व्योम
gk104_fअगरo_recover_engn(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक engn)
अणु
	काष्ठा nvkm_engine *engine = fअगरo->engine[engn].engine;
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 runl = fअगरo->engine[engn].runl;
	स्थिर u32 engm = BIT(engn);
	काष्ठा gk104_fअगरo_engine_status status;
	पूर्णांक mmui = -1;

	निश्चित_spin_locked(&fअगरo->base.lock);
	अगर (fअगरo->recover.engm & engm)
		वापस;
	fअगरo->recover.engm |= engm;

	/* Block channel assignments from changing during recovery. */
	gk104_fअगरo_recover_runl(fअगरo, runl);

	/* Determine which channel (अगर any) is currently on the engine. */
	gk104_fअगरo_engine_status(fअगरo, engn, &status);
	अगर (status.chan) अणु
		/* The channel is not दीर्घer viable, समाप्त it. */
		gk104_fअगरo_recover_chan(&fअगरo->base, status.chan->id);
	पूर्ण

	/* Determine MMU fault ID क्रम the engine, अगर we're not being
	 * called from the fault handler alपढ़ोy.
	 */
	अगर (!status.faulted && engine) अणु
		mmui = nvkm_top_fault_id(device, engine->subdev.type, engine->subdev.inst);
		अगर (mmui < 0) अणु
			स्थिर काष्ठा nvkm_क्रमागत *en = fअगरo->func->fault.engine;
			क्रम (; en && en->name; en++) अणु
				अगर (en->data2 == engine->subdev.type &&
				    en->inst  == engine->subdev.inst) अणु
					mmui = en->value;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		WARN_ON(mmui < 0);
	पूर्ण

	/* Trigger a MMU fault क्रम the engine.
	 *
	 * No good idea why this is needed, but nvgpu करोes something similar,
	 * and it makes recovery from CTXSW_TIMEOUT a lot more reliable.
	 */
	अगर (mmui >= 0) अणु
		nvkm_wr32(device, 0x002a30 + (engn * 0x04), 0x00000100 | mmui);

		/* Wait क्रम fault to trigger. */
		nvkm_msec(device, 2000,
			gk104_fअगरo_engine_status(fअगरo, engn, &status);
			अगर (status.faulted)
				अवरोध;
		);

		/* Release MMU fault trigger, and ACK the fault. */
		nvkm_wr32(device, 0x002a30 + (engn * 0x04), 0x00000000);
		nvkm_wr32(device, 0x00259c, BIT(mmui));
		nvkm_wr32(device, 0x002100, 0x10000000);
	पूर्ण

	/* Schedule recovery. */
	nvkm_warn(subdev, "engine %d: scheduled for recovery\n", engn);
	schedule_work(&fअगरo->recover.work);
पूर्ण

अटल व्योम
gk104_fअगरo_fault(काष्ठा nvkm_fअगरo *base, काष्ठा nvkm_fault_data *info)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर काष्ठा nvkm_क्रमागत *er, *ee, *ec, *ea;
	काष्ठा nvkm_engine *engine = शून्य;
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *en = "";
	अक्षर ct[8] = "HUB/";

	er = nvkm_क्रमागत_find(fअगरo->func->fault.reason, info->reason);
	ee = nvkm_क्रमागत_find(fअगरo->func->fault.engine, info->engine);
	अगर (info->hub) अणु
		ec = nvkm_क्रमागत_find(fअगरo->func->fault.hubclient, info->client);
	पूर्ण अन्यथा अणु
		ec = nvkm_क्रमागत_find(fअगरo->func->fault.gpcclient, info->client);
		snम_लिखो(ct, माप(ct), "GPC%d/", info->gpc);
	पूर्ण
	ea = nvkm_क्रमागत_find(fअगरo->func->fault.access, info->access);

	अगर (ee && ee->data2) अणु
		चयन (ee->data2) अणु
		हाल NVKM_SUBDEV_BAR:
			nvkm_bar_bar1_reset(device);
			अवरोध;
		हाल NVKM_SUBDEV_INSTMEM:
			nvkm_bar_bar2_reset(device);
			अवरोध;
		हाल NVKM_ENGINE_IFB:
			nvkm_mask(device, 0x001718, 0x00000000, 0x00000000);
			अवरोध;
		शेष:
			engine = nvkm_device_engine(device, ee->data2, 0);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ee == शून्य) अणु
		काष्ठा nvkm_subdev *subdev = nvkm_top_fault(device, info->engine);
		अगर (subdev) अणु
			अगर (subdev->func == &nvkm_engine)
				engine = container_of(subdev, typeof(*engine), subdev);
			en = engine->subdev.name;
		पूर्ण
	पूर्ण अन्यथा अणु
		en = ee->name;
	पूर्ण

	spin_lock_irqsave(&fअगरo->base.lock, flags);
	chan = nvkm_fअगरo_chan_inst_locked(&fअगरo->base, info->inst);

	nvkm_error(subdev,
		   "fault %02x [%s] at %016llx engine %02x [%s] client %02x "
		   "[%s%s] reason %02x [%s] on channel %d [%010llx %s]\n",
		   info->access, ea ? ea->name : "", info->addr,
		   info->engine, ee ? ee->name : en,
		   info->client, ct, ec ? ec->name : "",
		   info->reason, er ? er->name : "", chan ? chan->chid : -1,
		   info->inst, chan ? chan->object.client->name : "unknown");

	/* Kill the channel that caused the fault. */
	अगर (chan)
		gk104_fअगरo_recover_chan(&fअगरo->base, chan->chid);

	/* Channel recovery will probably have alपढ़ोy करोne this क्रम the
	 * correct engine(s), but just in हाल we can't find the channel
	 * inक्रमmation...
	 */
	अगर (engine) अणु
		पूर्णांक engn = fअगरo->base.func->engine_id(&fअगरo->base, engine);
		अगर (engn >= 0 && engn != GK104_FIFO_ENGN_SW)
			gk104_fअगरo_recover_engn(fअगरo, engn);
	पूर्ण

	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

अटल स्थिर काष्ठा nvkm_क्रमागत
gk104_fअगरo_bind_reason[] = अणु
	अणु 0x01, "BIND_NOT_UNBOUND" पूर्ण,
	अणु 0x02, "SNOOP_WITHOUT_BAR1" पूर्ण,
	अणु 0x03, "UNBIND_WHILE_RUNNING" पूर्ण,
	अणु 0x05, "INVALID_RUNLIST" पूर्ण,
	अणु 0x06, "INVALID_CTX_TGT" पूर्ण,
	अणु 0x0b, "UNBIND_WHILE_PARKED" पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
gk104_fअगरo_पूर्णांकr_bind(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x00252c);
	u32 code = पूर्णांकr & 0x000000ff;
	स्थिर काष्ठा nvkm_क्रमागत *en =
		nvkm_क्रमागत_find(gk104_fअगरo_bind_reason, code);

	nvkm_error(subdev, "BIND_ERROR %02x [%s]\n", code, en ? en->name : "");
पूर्ण

अटल स्थिर काष्ठा nvkm_क्रमागत
gk104_fअगरo_sched_reason[] = अणु
	अणु 0x0a, "CTXSW_TIMEOUT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
gk104_fअगरo_पूर्णांकr_sched_ctxsw(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	अचिन्हित दीर्घ flags, engm = 0;
	u32 engn;

	/* We need to ACK the SCHED_ERROR here, and prevent it reनिश्चितing,
	 * as MMU_FAULT cannot be triggered जबतक it's pending.
	 */
	spin_lock_irqsave(&fअगरo->base.lock, flags);
	nvkm_mask(device, 0x002140, 0x00000100, 0x00000000);
	nvkm_wr32(device, 0x002100, 0x00000100);

	क्रम (engn = 0; engn < fअगरo->engine_nr; engn++) अणु
		काष्ठा gk104_fअगरo_engine_status status;

		gk104_fअगरo_engine_status(fअगरo, engn, &status);
		अगर (!status.busy || !status.chsw)
			जारी;

		engm |= BIT(engn);
	पूर्ण

	क्रम_each_set_bit(engn, &engm, fअगरo->engine_nr)
		gk104_fअगरo_recover_engn(fअगरo, engn);

	nvkm_mask(device, 0x002140, 0x00000100, 0x00000100);
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

अटल व्योम
gk104_fअगरo_पूर्णांकr_sched(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x00254c);
	u32 code = पूर्णांकr & 0x000000ff;
	स्थिर काष्ठा nvkm_क्रमागत *en =
		nvkm_क्रमागत_find(gk104_fअगरo_sched_reason, code);

	nvkm_error(subdev, "SCHED_ERROR %02x [%s]\n", code, en ? en->name : "");

	चयन (code) अणु
	हाल 0x0a:
		gk104_fअगरo_पूर्णांकr_sched_ctxsw(fअगरo);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम
gk104_fअगरo_पूर्णांकr_chsw(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x00256c);
	nvkm_error(subdev, "CHSW_ERROR %08x\n", stat);
	nvkm_wr32(device, 0x00256c, stat);
पूर्ण

व्योम
gk104_fअगरo_पूर्णांकr_dropped_fault(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x00259c);
	nvkm_error(subdev, "DROPPED_MMU_FAULT %08x\n", stat);
पूर्ण

अटल स्थिर काष्ठा nvkm_bitfield gk104_fअगरo_pbdma_पूर्णांकr_0[] = अणु
	अणु 0x00000001, "MEMREQ" पूर्ण,
	अणु 0x00000002, "MEMACK_TIMEOUT" पूर्ण,
	अणु 0x00000004, "MEMACK_EXTRA" पूर्ण,
	अणु 0x00000008, "MEMDAT_TIMEOUT" पूर्ण,
	अणु 0x00000010, "MEMDAT_EXTRA" पूर्ण,
	अणु 0x00000020, "MEMFLUSH" पूर्ण,
	अणु 0x00000040, "MEMOP" पूर्ण,
	अणु 0x00000080, "LBCONNECT" पूर्ण,
	अणु 0x00000100, "LBREQ" पूर्ण,
	अणु 0x00000200, "LBACK_TIMEOUT" पूर्ण,
	अणु 0x00000400, "LBACK_EXTRA" पूर्ण,
	अणु 0x00000800, "LBDAT_TIMEOUT" पूर्ण,
	अणु 0x00001000, "LBDAT_EXTRA" पूर्ण,
	अणु 0x00002000, "GPFIFO" पूर्ण,
	अणु 0x00004000, "GPPTR" पूर्ण,
	अणु 0x00008000, "GPENTRY" पूर्ण,
	अणु 0x00010000, "GPCRC" पूर्ण,
	अणु 0x00020000, "PBPTR" पूर्ण,
	अणु 0x00040000, "PBENTRY" पूर्ण,
	अणु 0x00080000, "PBCRC" पूर्ण,
	अणु 0x00100000, "XBARCONNECT" पूर्ण,
	अणु 0x00200000, "METHOD" पूर्ण,
	अणु 0x00400000, "METHODCRC" पूर्ण,
	अणु 0x00800000, "DEVICE" पूर्ण,
	अणु 0x02000000, "SEMAPHORE" पूर्ण,
	अणु 0x04000000, "ACQUIRE" पूर्ण,
	अणु 0x08000000, "PRI" पूर्ण,
	अणु 0x20000000, "NO_CTXSW_SEG" पूर्ण,
	अणु 0x40000000, "PBSEG" पूर्ण,
	अणु 0x80000000, "SIGNATURE" पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
gk104_fअगरo_पूर्णांकr_pbdma_0(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक unit)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, 0x04010c + (unit * 0x2000));
	u32 stat = nvkm_rd32(device, 0x040108 + (unit * 0x2000)) & mask;
	u32 addr = nvkm_rd32(device, 0x0400c0 + (unit * 0x2000));
	u32 data = nvkm_rd32(device, 0x0400c4 + (unit * 0x2000));
	u32 chid = nvkm_rd32(device, 0x040120 + (unit * 0x2000)) & 0xfff;
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00003ffc);
	u32 show = stat;
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	अक्षर msg[128];

	अगर (stat & 0x00800000) अणु
		अगर (device->sw) अणु
			अगर (nvkm_sw_mthd(device->sw, chid, subc, mthd, data))
				show &= ~0x00800000;
		पूर्ण
	पूर्ण

	nvkm_wr32(device, 0x0400c0 + (unit * 0x2000), 0x80600008);

	अगर (show) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), gk104_fअगरo_pbdma_पूर्णांकr_0, show);
		chan = nvkm_fअगरo_chan_chid(&fअगरo->base, chid, &flags);
		nvkm_error(subdev, "PBDMA%d: %08x [%s] ch %d [%010llx %s] "
				   "subc %d mthd %04x data %08x\n",
			   unit, show, msg, chid, chan ? chan->inst->addr : 0,
			   chan ? chan->object.client->name : "unknown",
			   subc, mthd, data);
		nvkm_fअगरo_chan_put(&fअगरo->base, flags, &chan);
	पूर्ण

	nvkm_wr32(device, 0x040108 + (unit * 0x2000), stat);
पूर्ण

अटल स्थिर काष्ठा nvkm_bitfield gk104_fअगरo_pbdma_पूर्णांकr_1[] = अणु
	अणु 0x00000001, "HCE_RE_ILLEGAL_OP" पूर्ण,
	अणु 0x00000002, "HCE_RE_ALIGNB" पूर्ण,
	अणु 0x00000004, "HCE_PRIV" पूर्ण,
	अणु 0x00000008, "HCE_ILLEGAL_MTHD" पूर्ण,
	अणु 0x00000010, "HCE_ILLEGAL_CLASS" पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
gk104_fअगरo_पूर्णांकr_pbdma_1(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक unit)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, 0x04014c + (unit * 0x2000));
	u32 stat = nvkm_rd32(device, 0x040148 + (unit * 0x2000)) & mask;
	u32 chid = nvkm_rd32(device, 0x040120 + (unit * 0x2000)) & 0xfff;
	अक्षर msg[128];

	अगर (stat) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), gk104_fअगरo_pbdma_पूर्णांकr_1, stat);
		nvkm_error(subdev, "PBDMA%d: %08x [%s] ch %d %08x %08x\n",
			   unit, stat, msg, chid,
			   nvkm_rd32(device, 0x040150 + (unit * 0x2000)),
			   nvkm_rd32(device, 0x040154 + (unit * 0x2000)));
	पूर्ण

	nvkm_wr32(device, 0x040148 + (unit * 0x2000), stat);
पूर्ण

व्योम
gk104_fअगरo_पूर्णांकr_runlist(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 mask = nvkm_rd32(device, 0x002a00);
	जबतक (mask) अणु
		पूर्णांक runl = __ffs(mask);
		wake_up(&fअगरo->runlist[runl].रुको);
		nvkm_wr32(device, 0x002a00, 1 << runl);
		mask &= ~(1 << runl);
	पूर्ण
पूर्ण

व्योम
gk104_fअगरo_पूर्णांकr_engine(काष्ठा gk104_fअगरo *fअगरo)
अणु
	nvkm_fअगरo_uevent(&fअगरo->base);
पूर्ण

अटल व्योम
gk104_fअगरo_पूर्णांकr(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, 0x002140);
	u32 stat = nvkm_rd32(device, 0x002100) & mask;

	अगर (stat & 0x00000001) अणु
		gk104_fअगरo_पूर्णांकr_bind(fअगरo);
		nvkm_wr32(device, 0x002100, 0x00000001);
		stat &= ~0x00000001;
	पूर्ण

	अगर (stat & 0x00000010) अणु
		nvkm_error(subdev, "PIO_ERROR\n");
		nvkm_wr32(device, 0x002100, 0x00000010);
		stat &= ~0x00000010;
	पूर्ण

	अगर (stat & 0x00000100) अणु
		gk104_fअगरo_पूर्णांकr_sched(fअगरo);
		nvkm_wr32(device, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	पूर्ण

	अगर (stat & 0x00010000) अणु
		gk104_fअगरo_पूर्णांकr_chsw(fअगरo);
		nvkm_wr32(device, 0x002100, 0x00010000);
		stat &= ~0x00010000;
	पूर्ण

	अगर (stat & 0x00800000) अणु
		nvkm_error(subdev, "FB_FLUSH_TIMEOUT\n");
		nvkm_wr32(device, 0x002100, 0x00800000);
		stat &= ~0x00800000;
	पूर्ण

	अगर (stat & 0x01000000) अणु
		nvkm_error(subdev, "LB_ERROR\n");
		nvkm_wr32(device, 0x002100, 0x01000000);
		stat &= ~0x01000000;
	पूर्ण

	अगर (stat & 0x08000000) अणु
		gk104_fअगरo_पूर्णांकr_dropped_fault(fअगरo);
		nvkm_wr32(device, 0x002100, 0x08000000);
		stat &= ~0x08000000;
	पूर्ण

	अगर (stat & 0x10000000) अणु
		u32 mask = nvkm_rd32(device, 0x00259c);
		जबतक (mask) अणु
			u32 unit = __ffs(mask);
			fअगरo->func->पूर्णांकr.fault(&fअगरo->base, unit);
			nvkm_wr32(device, 0x00259c, (1 << unit));
			mask &= ~(1 << unit);
		पूर्ण
		stat &= ~0x10000000;
	पूर्ण

	अगर (stat & 0x20000000) अणु
		u32 mask = nvkm_rd32(device, 0x0025a0);
		जबतक (mask) अणु
			u32 unit = __ffs(mask);
			gk104_fअगरo_पूर्णांकr_pbdma_0(fअगरo, unit);
			gk104_fअगरo_पूर्णांकr_pbdma_1(fअगरo, unit);
			nvkm_wr32(device, 0x0025a0, (1 << unit));
			mask &= ~(1 << unit);
		पूर्ण
		stat &= ~0x20000000;
	पूर्ण

	अगर (stat & 0x40000000) अणु
		gk104_fअगरo_पूर्णांकr_runlist(fअगरo);
		stat &= ~0x40000000;
	पूर्ण

	अगर (stat & 0x80000000) अणु
		nvkm_wr32(device, 0x002100, 0x80000000);
		gk104_fअगरo_पूर्णांकr_engine(fअगरo);
		stat &= ~0x80000000;
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "INTR %08x\n", stat);
		nvkm_mask(device, 0x002140, stat, 0x00000000);
		nvkm_wr32(device, 0x002100, stat);
	पूर्ण
पूर्ण

व्योम
gk104_fअगरo_fini(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	flush_work(&fअगरo->recover.work);
	/* allow mmu fault पूर्णांकerrupts, even when we're not using fअगरo */
	nvkm_mask(device, 0x002140, 0x10000000, 0x10000000);
पूर्ण

पूर्णांक
gk104_fअगरo_info(काष्ठा nvkm_fअगरo *base, u64 mthd, u64 *data)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	चयन (mthd) अणु
	हाल NV_DEVICE_HOST_RUNLISTS:
		*data = (1ULL << fअगरo->runlist_nr) - 1;
		वापस 0;
	हाल NV_DEVICE_HOST_RUNLIST_ENGINES: अणु
		अगर (*data < fअगरo->runlist_nr) अणु
			अचिन्हित दीर्घ engm = fअगरo->runlist[*data].engm;
			काष्ठा nvkm_engine *engine;
			पूर्णांक engn;
			*data = 0;
			क्रम_each_set_bit(engn, &engm, fअगरo->engine_nr) अणु
				अगर ((engine = fअगरo->engine[engn].engine)) अणु
#घोषणा CASE(n) हाल NVKM_ENGINE_##n: *data |= NV_DEVICE_HOST_RUNLIST_ENGINES_##n; अवरोध
					चयन (engine->subdev.type) अणु
					CASE(SW    );
					CASE(GR    );
					CASE(MPEG  );
					CASE(ME    );
					CASE(CIPHER);
					CASE(BSP   );
					CASE(VP    );
					CASE(CE    );
					CASE(SEC   );
					CASE(MSVLD );
					CASE(MSPDEC);
					CASE(MSPPP );
					CASE(MSENC );
					CASE(VIC   );
					CASE(SEC2  );
					CASE(NVDEC );
					CASE(NVENC );
					शेष:
						WARN_ON(1);
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			वापस 0;
		पूर्ण
	पूर्ण
		वापस -EINVAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक
gk104_fअगरo_oneinit(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_vmm *bar = nvkm_bar_bar1_vmm(device);
	काष्ठा nvkm_top_device *tdev;
	पूर्णांक pbid, ret, i, j;
	u32 *map;

	fअगरo->pbdma_nr = fअगरo->func->pbdma->nr(fअगरo);
	nvkm_debug(subdev, "%d PBDMA(s)\n", fअगरo->pbdma_nr);

	/* Read PBDMA->runlist(s) mapping from HW. */
	अगर (!(map = kसुस्मृति(fअगरo->pbdma_nr, माप(*map), GFP_KERNEL)))
		वापस -ENOMEM;

	क्रम (i = 0; i < fअगरo->pbdma_nr; i++)
		map[i] = nvkm_rd32(device, 0x002390 + (i * 0x04));

	/* Determine runlist configuration from topology device info. */
	list_क्रम_each_entry(tdev, &device->top->device, head) अणु
		स्थिर पूर्णांक engn = tdev->engine;
		अक्षर _en[16], *en;

		अगर (engn < 0)
			जारी;

		/* Determine which PBDMA handles requests क्रम this engine. */
		क्रम (j = 0, pbid = -1; j < fअगरo->pbdma_nr; j++) अणु
			अगर (map[j] & BIT(tdev->runlist)) अणु
				pbid = j;
				अवरोध;
			पूर्ण
		पूर्ण

		fअगरo->engine[engn].engine = nvkm_device_engine(device, tdev->type, tdev->inst);
		अगर (!fअगरo->engine[engn].engine) अणु
			snम_लिखो(_en, माप(_en), "%s, %d",
				 nvkm_subdev_type[tdev->type], tdev->inst);
			en = _en;
		पूर्ण अन्यथा अणु
			en = fअगरo->engine[engn].engine->subdev.name;
		पूर्ण

		nvkm_debug(subdev, "engine %2d: runlist %2d pbdma %2d (%s)\n",
			   tdev->engine, tdev->runlist, pbid, en);

		fअगरo->engine[engn].runl = tdev->runlist;
		fअगरo->engine[engn].pbid = pbid;
		fअगरo->engine_nr = max(fअगरo->engine_nr, engn + 1);
		fअगरo->runlist[tdev->runlist].engm |= BIT(engn);
		fअगरo->runlist[tdev->runlist].engm_sw |= BIT(engn);
		अगर (tdev->type == NVKM_ENGINE_GR)
			fअगरo->runlist[tdev->runlist].engm_sw |= BIT(GK104_FIFO_ENGN_SW);
		fअगरo->runlist_nr = max(fअगरo->runlist_nr, tdev->runlist + 1);
	पूर्ण

	kमुक्त(map);

	क्रम (i = 0; i < fअगरo->runlist_nr; i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(fअगरo->runlist[i].mem); j++) अणु
			ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
					      fअगरo->base.nr * 2/* TSG+chan */ *
					      fअगरo->func->runlist->size,
					      0x1000, false,
					      &fअगरo->runlist[i].mem[j]);
			अगर (ret)
				वापस ret;
		पूर्ण

		init_रुकोqueue_head(&fअगरo->runlist[i].रुको);
		INIT_LIST_HEAD(&fअगरo->runlist[i].cgrp);
		INIT_LIST_HEAD(&fअगरo->runlist[i].chan);
	पूर्ण

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST,
			      fअगरo->base.nr * 0x200, 0x1000, true,
			      &fअगरo->user.mem);
	अगर (ret)
		वापस ret;

	ret = nvkm_vmm_get(bar, 12, nvkm_memory_size(fअगरo->user.mem),
			   &fअगरo->user.bar);
	अगर (ret)
		वापस ret;

	वापस nvkm_memory_map(fअगरo->user.mem, 0, bar, fअगरo->user.bar, शून्य, 0);
पूर्ण

व्योम
gk104_fअगरo_init(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक i;

	/* Enable PBDMAs. */
	fअगरo->func->pbdma->init(fअगरo);

	/* PBDMA[n] */
	क्रम (i = 0; i < fअगरo->pbdma_nr; i++) अणु
		nvkm_mask(device, 0x04013c + (i * 0x2000), 0x10000100, 0x00000000);
		nvkm_wr32(device, 0x040108 + (i * 0x2000), 0xffffffff); /* INTR */
		nvkm_wr32(device, 0x04010c + (i * 0x2000), 0xfffffeff); /* INTREN */
	पूर्ण

	/* PBDMA[n].HCE */
	क्रम (i = 0; i < fअगरo->pbdma_nr; i++) अणु
		nvkm_wr32(device, 0x040148 + (i * 0x2000), 0xffffffff); /* INTR */
		nvkm_wr32(device, 0x04014c + (i * 0x2000), 0xffffffff); /* INTREN */
	पूर्ण

	nvkm_wr32(device, 0x002254, 0x10000000 | fअगरo->user.bar->addr >> 12);

	अगर (fअगरo->func->pbdma->init_समयout)
		fअगरo->func->pbdma->init_समयout(fअगरo);

	nvkm_wr32(device, 0x002100, 0xffffffff);
	nvkm_wr32(device, 0x002140, 0x7fffffff);
पूर्ण

व्योम *
gk104_fअगरo_dtor(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gk104_fअगरo *fअगरo = gk104_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक i;

	nvkm_vmm_put(nvkm_bar_bar1_vmm(device), &fअगरo->user.bar);
	nvkm_memory_unref(&fअगरo->user.mem);

	क्रम (i = 0; i < fअगरo->runlist_nr; i++) अणु
		nvkm_memory_unref(&fअगरo->runlist[i].mem[1]);
		nvkm_memory_unref(&fअगरo->runlist[i].mem[0]);
	पूर्ण

	वापस fअगरo;
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_func
gk104_fअगरo_ = अणु
	.dtor = gk104_fअगरo_dtor,
	.oneinit = gk104_fअगरo_oneinit,
	.info = gk104_fअगरo_info,
	.init = gk104_fअगरo_init,
	.fini = gk104_fअगरo_fini,
	.पूर्णांकr = gk104_fअगरo_पूर्णांकr,
	.fault = gk104_fअगरo_fault,
	.engine_id = gk104_fअगरo_engine_id,
	.id_engine = gk104_fअगरo_id_engine,
	.uevent_init = gk104_fअगरo_uevent_init,
	.uevent_fini = gk104_fअगरo_uevent_fini,
	.recover_chan = gk104_fअगरo_recover_chan,
	.class_get = gk104_fअगरo_class_get,
	.class_new = gk104_fअगरo_class_new,
पूर्ण;

पूर्णांक
gk104_fअगरo_new_(स्थिर काष्ठा gk104_fअगरo_func *func, काष्ठा nvkm_device *device,
		क्रमागत nvkm_subdev_type type, पूर्णांक inst, पूर्णांक nr, काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	काष्ठा gk104_fअगरo *fअगरo;

	अगर (!(fअगरo = kzalloc(माप(*fअगरo), GFP_KERNEL)))
		वापस -ENOMEM;
	fअगरo->func = func;
	INIT_WORK(&fअगरo->recover.work, gk104_fअगरo_recover_work);
	*pfअगरo = &fअगरo->base;

	वापस nvkm_fअगरo_ctor(&gk104_fअगरo_, device, type, inst, nr, &fअगरo->base);
पूर्ण

स्थिर काष्ठा nvkm_क्रमागत
gk104_fअगरo_fault_access[] = अणु
	अणु 0x0, "READ" पूर्ण,
	अणु 0x1, "WRITE" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gk104_fअगरo_fault_engine[] = अणु
	अणु 0x00, "GR", शून्य, NVKM_ENGINE_GR पूर्ण,
	अणु 0x01, "DISPLAY" पूर्ण,
	अणु 0x02, "CAPTURE" पूर्ण,
	अणु 0x03, "IFB", शून्य, NVKM_ENGINE_IFB पूर्ण,
	अणु 0x04, "BAR1", शून्य, NVKM_SUBDEV_BAR पूर्ण,
	अणु 0x05, "BAR2", शून्य, NVKM_SUBDEV_INSTMEM पूर्ण,
	अणु 0x06, "SCHED" पूर्ण,
	अणु 0x07, "HOST0", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x08, "HOST1", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x09, "HOST2", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x0a, "HOST3", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x0b, "HOST4", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x0c, "HOST5", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x0d, "HOST6", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x0e, "HOST7", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x0f, "HOSTSR" पूर्ण,
	अणु 0x10, "MSVLD", शून्य, NVKM_ENGINE_MSVLD पूर्ण,
	अणु 0x11, "MSPPP", शून्य, NVKM_ENGINE_MSPPP पूर्ण,
	अणु 0x13, "PERF" पूर्ण,
	अणु 0x14, "MSPDEC", शून्य, NVKM_ENGINE_MSPDEC पूर्ण,
	अणु 0x15, "CE0", शून्य, NVKM_ENGINE_CE, 0 पूर्ण,
	अणु 0x16, "CE1", शून्य, NVKM_ENGINE_CE, 1 पूर्ण,
	अणु 0x17, "PMU" पूर्ण,
	अणु 0x18, "PTP" पूर्ण,
	अणु 0x19, "MSENC", शून्य, NVKM_ENGINE_MSENC पूर्ण,
	अणु 0x1b, "CE2", शून्य, NVKM_ENGINE_CE, 2 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gk104_fअगरo_fault_reason[] = अणु
	अणु 0x00, "PDE" पूर्ण,
	अणु 0x01, "PDE_SIZE" पूर्ण,
	अणु 0x02, "PTE" पूर्ण,
	अणु 0x03, "VA_LIMIT_VIOLATION" पूर्ण,
	अणु 0x04, "UNBOUND_INST_BLOCK" पूर्ण,
	अणु 0x05, "PRIV_VIOLATION" पूर्ण,
	अणु 0x06, "RO_VIOLATION" पूर्ण,
	अणु 0x07, "WO_VIOLATION" पूर्ण,
	अणु 0x08, "PITCH_MASK_VIOLATION" पूर्ण,
	अणु 0x09, "WORK_CREATION" पूर्ण,
	अणु 0x0a, "UNSUPPORTED_APERTURE" पूर्ण,
	अणु 0x0b, "COMPRESSION_FAILURE" पूर्ण,
	अणु 0x0c, "UNSUPPORTED_KIND" पूर्ण,
	अणु 0x0d, "REGION_VIOLATION" पूर्ण,
	अणु 0x0e, "BOTH_PTES_VALID" पूर्ण,
	अणु 0x0f, "INFO_TYPE_POISONED" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gk104_fअगरo_fault_hubclient[] = अणु
	अणु 0x00, "VIP" पूर्ण,
	अणु 0x01, "CE0" पूर्ण,
	अणु 0x02, "CE1" पूर्ण,
	अणु 0x03, "DNISO" पूर्ण,
	अणु 0x04, "FE" पूर्ण,
	अणु 0x05, "FECS" पूर्ण,
	अणु 0x06, "HOST" पूर्ण,
	अणु 0x07, "HOST_CPU" पूर्ण,
	अणु 0x08, "HOST_CPU_NB" पूर्ण,
	अणु 0x09, "ISO" पूर्ण,
	अणु 0x0a, "MMU" पूर्ण,
	अणु 0x0b, "MSPDEC" पूर्ण,
	अणु 0x0c, "MSPPP" पूर्ण,
	अणु 0x0d, "MSVLD" पूर्ण,
	अणु 0x0e, "NISO" पूर्ण,
	अणु 0x0f, "P2P" पूर्ण,
	अणु 0x10, "PD" पूर्ण,
	अणु 0x11, "PERF" पूर्ण,
	अणु 0x12, "PMU" पूर्ण,
	अणु 0x13, "RASTERTWOD" पूर्ण,
	अणु 0x14, "SCC" पूर्ण,
	अणु 0x15, "SCC_NB" पूर्ण,
	अणु 0x16, "SEC" पूर्ण,
	अणु 0x17, "SSYNC" पूर्ण,
	अणु 0x18, "GR_CE" पूर्ण,
	अणु 0x19, "CE2" पूर्ण,
	अणु 0x1a, "XV" पूर्ण,
	अणु 0x1b, "MMU_NB" पूर्ण,
	अणु 0x1c, "MSENC" पूर्ण,
	अणु 0x1d, "DFALCON" पूर्ण,
	अणु 0x1e, "SKED" पूर्ण,
	अणु 0x1f, "AFALCON" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gk104_fअगरo_fault_gpcclient[] = अणु
	अणु 0x00, "L1_0" पूर्ण, अणु 0x01, "T1_0" पूर्ण, अणु 0x02, "PE_0" पूर्ण,
	अणु 0x03, "L1_1" पूर्ण, अणु 0x04, "T1_1" पूर्ण, अणु 0x05, "PE_1" पूर्ण,
	अणु 0x06, "L1_2" पूर्ण, अणु 0x07, "T1_2" पूर्ण, अणु 0x08, "PE_2" पूर्ण,
	अणु 0x09, "L1_3" पूर्ण, अणु 0x0a, "T1_3" पूर्ण, अणु 0x0b, "PE_3" पूर्ण,
	अणु 0x0c, "RAST" पूर्ण,
	अणु 0x0d, "GCC" पूर्ण,
	अणु 0x0e, "GPCCS" पूर्ण,
	अणु 0x0f, "PROP_0" पूर्ण,
	अणु 0x10, "PROP_1" पूर्ण,
	अणु 0x11, "PROP_2" पूर्ण,
	अणु 0x12, "PROP_3" पूर्ण,
	अणु 0x13, "L1_4" पूर्ण, अणु 0x14, "T1_4" पूर्ण, अणु 0x15, "PE_4" पूर्ण,
	अणु 0x16, "L1_5" पूर्ण, अणु 0x17, "T1_5" पूर्ण, अणु 0x18, "PE_5" पूर्ण,
	अणु 0x19, "L1_6" पूर्ण, अणु 0x1a, "T1_6" पूर्ण, अणु 0x1b, "PE_6" पूर्ण,
	अणु 0x1c, "L1_7" पूर्ण, अणु 0x1d, "T1_7" पूर्ण, अणु 0x1e, "PE_7" पूर्ण,
	अणु 0x1f, "GPM" पूर्ण,
	अणु 0x20, "LTP_UTLB_0" पूर्ण,
	अणु 0x21, "LTP_UTLB_1" पूर्ण,
	अणु 0x22, "LTP_UTLB_2" पूर्ण,
	अणु 0x23, "LTP_UTLB_3" पूर्ण,
	अणु 0x24, "GPC_RGG_UTLB" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gk104_fअगरo_func
gk104_fअगरo = अणु
	.पूर्णांकr.fault = gf100_fअगरo_पूर्णांकr_fault,
	.pbdma = &gk104_fअगरo_pbdma,
	.fault.access = gk104_fअगरo_fault_access,
	.fault.engine = gk104_fअगरo_fault_engine,
	.fault.reason = gk104_fअगरo_fault_reason,
	.fault.hubclient = gk104_fअगरo_fault_hubclient,
	.fault.gpcclient = gk104_fअगरo_fault_gpcclient,
	.runlist = &gk104_fअगरo_runlist,
	.chan = अणुअणु0,0,KEPLER_CHANNEL_GPFIFO_Aपूर्ण, gk104_fअगरo_gpfअगरo_new पूर्ण,
पूर्ण;

पूर्णांक
gk104_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस gk104_fअगरo_new_(&gk104_fअगरo, device, type, inst, 4096, pfअगरo);
पूर्ण
