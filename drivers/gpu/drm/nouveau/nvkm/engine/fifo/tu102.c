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
#समावेश "gk104.h"
#समावेश "cgrp.h"
#समावेश "changk104.h"
#समावेश "user.h"

#समावेश <core/client.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/bar.h>
#समावेश <subdev/fault.h>
#समावेश <subdev/top.h>
#समावेश <subdev/समयr.h>
#समावेश <engine/sw.h>

#समावेश <nvअगर/class.h>

अटल व्योम
tu102_fअगरo_runlist_commit(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक runl,
			  काष्ठा nvkm_memory *mem, पूर्णांक nr)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u64 addr = nvkm_memory_addr(mem);
	/*XXX: target? */

	nvkm_wr32(device, 0x002b00 + (runl * 0x10), lower_32_bits(addr));
	nvkm_wr32(device, 0x002b04 + (runl * 0x10), upper_32_bits(addr));
	nvkm_wr32(device, 0x002b08 + (runl * 0x10), nr);

	/*XXX: how to रुको? can you even रुको? */
पूर्ण

स्थिर काष्ठा gk104_fअगरo_runlist_func
tu102_fअगरo_runlist = अणु
	.size = 16,
	.cgrp = gv100_fअगरo_runlist_cgrp,
	.chan = gv100_fअगरo_runlist_chan,
	.commit = tu102_fअगरo_runlist_commit,
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत
tu102_fअगरo_fault_engine[] = अणु
	अणु 0x01, "DISPLAY" पूर्ण,
	अणु 0x03, "PTP" पूर्ण,
	अणु 0x06, "PWR_PMU" पूर्ण,
	अणु 0x08, "IFB", शून्य, NVKM_ENGINE_IFB पूर्ण,
	अणु 0x09, "PERF" पूर्ण,
	अणु 0x1f, "PHYSICAL" पूर्ण,
	अणु 0x20, "HOST0" पूर्ण,
	अणु 0x21, "HOST1" पूर्ण,
	अणु 0x22, "HOST2" पूर्ण,
	अणु 0x23, "HOST3" पूर्ण,
	अणु 0x24, "HOST4" पूर्ण,
	अणु 0x25, "HOST5" पूर्ण,
	अणु 0x26, "HOST6" पूर्ण,
	अणु 0x27, "HOST7" पूर्ण,
	अणु 0x28, "HOST8" पूर्ण,
	अणु 0x29, "HOST9" पूर्ण,
	अणु 0x2a, "HOST10" पूर्ण,
	अणु 0x2b, "HOST11" पूर्ण,
	अणु 0x2c, "HOST12" पूर्ण,
	अणु 0x2d, "HOST13" पूर्ण,
	अणु 0x2e, "HOST14" पूर्ण,
	अणु 0x80, "BAR1", शून्य, NVKM_SUBDEV_BAR पूर्ण,
	अणु 0xc0, "BAR2", शून्य, NVKM_SUBDEV_INSTMEM पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
tu102_fअगरo_pbdma_init(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	स्थिर u32 mask = (1 << fअगरo->pbdma_nr) - 1;
	/*XXX: this is a bit of a guess at this poपूर्णांक in समय. */
	nvkm_mask(device, 0xb65000, 0x80000fff, 0x80000000 | mask);
पूर्ण

अटल स्थिर काष्ठा gk104_fअगरo_pbdma_func
tu102_fअगरo_pbdma = अणु
	.nr = gm200_fअगरo_pbdma_nr,
	.init = tu102_fअगरo_pbdma_init,
	.init_समयout = gk208_fअगरo_pbdma_init_समयout,
पूर्ण;

अटल स्थिर काष्ठा gk104_fअगरo_func
tu102_fअगरo = अणु
	.pbdma = &tu102_fअगरo_pbdma,
	.fault.access = gv100_fअगरo_fault_access,
	.fault.engine = tu102_fअगरo_fault_engine,
	.fault.reason = gv100_fअगरo_fault_reason,
	.fault.hubclient = gv100_fअगरo_fault_hubclient,
	.fault.gpcclient = gv100_fअगरo_fault_gpcclient,
	.runlist = &tu102_fअगरo_runlist,
	.user = अणुअणु-1,-1,VOLTA_USERMODE_A       पूर्ण, tu102_fअगरo_user_new   पूर्ण,
	.chan = अणुअणु 0, 0,TURING_CHANNEL_GPFIFO_Aपूर्ण, tu102_fअगरo_gpfअगरo_new पूर्ण,
	.cgrp_क्रमce = true,
पूर्ण;

अटल व्योम
tu102_fअगरo_recover_work(काष्ठा work_काष्ठा *w)
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

	nvkm_mask(device, 0x002630, runm, 0x00000000);
पूर्ण

अटल व्योम tu102_fअगरo_recover_engn(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक engn);

अटल व्योम
tu102_fअगरo_recover_runl(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक runl)
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
tu102_fअगरo_recover_chid(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक runl, पूर्णांक chid)
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
tu102_fअगरo_recover_chan(काष्ठा nvkm_fअगरo *base, पूर्णांक chid)
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
	chan = tu102_fअगरo_recover_chid(fअगरo, runl, chid);
	अगर (chan) अणु
		chan->समाप्तed = true;
		nvkm_fअगरo_kevent(&fअगरo->base, chid);
	पूर्ण

	/* Disable channel. */
	nvkm_wr32(device, 0x800004 + (chid * 0x08), stat | 0x00000800);
	nvkm_warn(subdev, "channel %d: killed\n", chid);

	/* Block channel assignments from changing during recovery. */
	tu102_fअगरo_recover_runl(fअगरo, runl);

	/* Schedule recovery क्रम any engines the channel is on. */
	क्रम_each_set_bit(engn, &engm, fअगरo->engine_nr) अणु
		काष्ठा gk104_fअगरo_engine_status status;

		gk104_fअगरo_engine_status(fअगरo, engn, &status);
		अगर (!status.chan || status.chan->id != chid)
			जारी;
		tu102_fअगरo_recover_engn(fअगरo, engn);
	पूर्ण
पूर्ण

अटल व्योम
tu102_fअगरo_recover_engn(काष्ठा gk104_fअगरo *fअगरo, पूर्णांक engn)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 runl = fअगरo->engine[engn].runl;
	स्थिर u32 engm = BIT(engn);
	काष्ठा gk104_fअगरo_engine_status status;

	निश्चित_spin_locked(&fअगरo->base.lock);
	अगर (fअगरo->recover.engm & engm)
		वापस;
	fअगरo->recover.engm |= engm;

	/* Block channel assignments from changing during recovery. */
	tu102_fअगरo_recover_runl(fअगरo, runl);

	/* Determine which channel (अगर any) is currently on the engine. */
	gk104_fअगरo_engine_status(fअगरo, engn, &status);
	अगर (status.chan) अणु
		/* The channel is not दीर्घer viable, समाप्त it. */
		tu102_fअगरo_recover_chan(&fअगरo->base, status.chan->id);
	पूर्ण

	/* Preempt the runlist */
	nvkm_wr32(device, 0x2638, BIT(runl));

	/* Schedule recovery. */
	nvkm_warn(subdev, "engine %d: scheduled for recovery\n", engn);
	schedule_work(&fअगरo->recover.work);
पूर्ण

अटल व्योम
tu102_fअगरo_fault(काष्ठा nvkm_fअगरo *base, काष्ठा nvkm_fault_data *info)
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
	पूर्णांक engn;

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
		tu102_fअगरo_recover_chan(&fअगरo->base, chan->chid);

	/* Channel recovery will probably have alपढ़ोy करोne this क्रम the
	 * correct engine(s), but just in हाल we can't find the channel
	 * inक्रमmation...
	 */
	क्रम (engn = 0; engn < fअगरo->engine_nr && engine; engn++) अणु
		अगर (fअगरo->engine[engn].engine == engine) अणु
			tu102_fअगरo_recover_engn(fअगरo, engn);
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

अटल व्योम
tu102_fअगरo_पूर्णांकr_ctxsw_समयout(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	अचिन्हित दीर्घ flags, engm;
	u32 engn;

	spin_lock_irqsave(&fअगरo->base.lock, flags);

	engm = nvkm_rd32(device, 0x2a30);
	nvkm_wr32(device, 0x2a30, engm);

	क्रम_each_set_bit(engn, &engm, 32)
		tu102_fअगरo_recover_engn(fअगरo, engn);

	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

अटल व्योम
tu102_fअगरo_पूर्णांकr_sched(काष्ठा gk104_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x00254c);
	u32 code = पूर्णांकr & 0x000000ff;

	nvkm_error(subdev, "SCHED_ERROR %02x\n", code);
पूर्ण

अटल व्योम
tu102_fअगरo_पूर्णांकr(काष्ठा nvkm_fअगरo *base)
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

	अगर (stat & 0x00000002) अणु
		tu102_fअगरo_पूर्णांकr_ctxsw_समयout(fअगरo);
		stat &= ~0x00000002;
	पूर्ण

	अगर (stat & 0x00000100) अणु
		tu102_fअगरo_पूर्णांकr_sched(fअगरo);
		nvkm_wr32(device, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	पूर्ण

	अगर (stat & 0x00010000) अणु
		gk104_fअगरo_पूर्णांकr_chsw(fअगरo);
		nvkm_wr32(device, 0x002100, 0x00010000);
		stat &= ~0x00010000;
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

अटल स्थिर काष्ठा nvkm_fअगरo_func
tu102_fअगरo_ = अणु
	.dtor = gk104_fअगरo_dtor,
	.oneinit = gk104_fअगरo_oneinit,
	.info = gk104_fअगरo_info,
	.init = gk104_fअगरo_init,
	.fini = gk104_fअगरo_fini,
	.पूर्णांकr = tu102_fअगरo_पूर्णांकr,
	.fault = tu102_fअगरo_fault,
	.engine_id = gk104_fअगरo_engine_id,
	.id_engine = gk104_fअगरo_id_engine,
	.uevent_init = gk104_fअगरo_uevent_init,
	.uevent_fini = gk104_fअगरo_uevent_fini,
	.recover_chan = tu102_fअगरo_recover_chan,
	.class_get = gk104_fअगरo_class_get,
	.class_new = gk104_fअगरo_class_new,
पूर्ण;

पूर्णांक
tu102_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	काष्ठा gk104_fअगरo *fअगरo;

	अगर (!(fअगरo = kzalloc(माप(*fअगरo), GFP_KERNEL)))
		वापस -ENOMEM;
	fअगरo->func = &tu102_fअगरo;
	INIT_WORK(&fअगरo->recover.work, tu102_fअगरo_recover_work);
	*pfअगरo = &fअगरo->base;

	वापस nvkm_fअगरo_ctor(&tu102_fअगरo_, device, type, inst, 4096, &fअगरo->base);
पूर्ण
