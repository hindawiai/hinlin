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
#समावेश "gf100.h"
#समावेश "changf100.h"

#समावेश <core/client.h>
#समावेश <core/क्रमागत.h>
#समावेश <core/gpuobj.h>
#समावेश <subdev/bar.h>
#समावेश <subdev/fault.h>
#समावेश <engine/sw.h>

#समावेश <nvअगर/class.h>

अटल व्योम
gf100_fअगरo_uevent_init(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	nvkm_mask(device, 0x002140, 0x80000000, 0x80000000);
पूर्ण

अटल व्योम
gf100_fअगरo_uevent_fini(काष्ठा nvkm_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	nvkm_mask(device, 0x002140, 0x80000000, 0x00000000);
पूर्ण

व्योम
gf100_fअगरo_runlist_commit(काष्ठा gf100_fअगरo *fअगरo)
अणु
	काष्ठा gf100_fअगरo_chan *chan;
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_memory *cur;
	पूर्णांक nr = 0;
	पूर्णांक target;

	mutex_lock(&fअगरo->base.mutex);
	cur = fअगरo->runlist.mem[fअगरo->runlist.active];
	fअगरo->runlist.active = !fअगरo->runlist.active;

	nvkm_kmap(cur);
	list_क्रम_each_entry(chan, &fअगरo->chan, head) अणु
		nvkm_wo32(cur, (nr * 8) + 0, chan->base.chid);
		nvkm_wo32(cur, (nr * 8) + 4, 0x00000004);
		nr++;
	पूर्ण
	nvkm_करोne(cur);

	चयन (nvkm_memory_target(cur)) अणु
	हाल NVKM_MEM_TARGET_VRAM: target = 0; अवरोध;
	हाल NVKM_MEM_TARGET_NCOH: target = 3; अवरोध;
	शेष:
		mutex_unlock(&fअगरo->base.mutex);
		WARN_ON(1);
		वापस;
	पूर्ण

	nvkm_wr32(device, 0x002270, (nvkm_memory_addr(cur) >> 12) |
				    (target << 28));
	nvkm_wr32(device, 0x002274, 0x01f00000 | nr);

	अगर (रुको_event_समयout(fअगरo->runlist.रुको,
			       !(nvkm_rd32(device, 0x00227c) & 0x00100000),
			       msecs_to_jअगरfies(2000)) == 0)
		nvkm_error(subdev, "runlist update timeout\n");
	mutex_unlock(&fअगरo->base.mutex);
पूर्ण

व्योम
gf100_fअगरo_runlist_हटाओ(काष्ठा gf100_fअगरo *fअगरo, काष्ठा gf100_fअगरo_chan *chan)
अणु
	mutex_lock(&fअगरo->base.mutex);
	list_del_init(&chan->head);
	mutex_unlock(&fअगरo->base.mutex);
पूर्ण

व्योम
gf100_fअगरo_runlist_insert(काष्ठा gf100_fअगरo *fअगरo, काष्ठा gf100_fअगरo_chan *chan)
अणु
	mutex_lock(&fअगरo->base.mutex);
	list_add_tail(&chan->head, &fअगरo->chan);
	mutex_unlock(&fअगरo->base.mutex);
पूर्ण

अटल काष्ठा nvkm_engine *
gf100_fअगरo_id_engine(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक engi)
अणु
	क्रमागत nvkm_subdev_type type;
	पूर्णांक inst;

	चयन (engi) अणु
	हाल GF100_FIFO_ENGN_GR    : type = NVKM_ENGINE_GR    ; inst = 0; अवरोध;
	हाल GF100_FIFO_ENGN_MSPDEC: type = NVKM_ENGINE_MSPDEC; inst = 0; अवरोध;
	हाल GF100_FIFO_ENGN_MSPPP : type = NVKM_ENGINE_MSPPP ; inst = 0; अवरोध;
	हाल GF100_FIFO_ENGN_MSVLD : type = NVKM_ENGINE_MSVLD ; inst = 0; अवरोध;
	हाल GF100_FIFO_ENGN_CE0   : type = NVKM_ENGINE_CE    ; inst = 0; अवरोध;
	हाल GF100_FIFO_ENGN_CE1   : type = NVKM_ENGINE_CE    ; inst = 1; अवरोध;
	हाल GF100_FIFO_ENGN_SW    : type = NVKM_ENGINE_SW    ; inst = 0; अवरोध;
	शेष:
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	वापस nvkm_device_engine(fअगरo->engine.subdev.device, type, inst);
पूर्ण

अटल पूर्णांक
gf100_fअगरo_engine_id(काष्ठा nvkm_fअगरo *base, काष्ठा nvkm_engine *engine)
अणु
	चयन (engine->subdev.type) अणु
	हाल NVKM_ENGINE_GR    : वापस GF100_FIFO_ENGN_GR;
	हाल NVKM_ENGINE_MSPDEC: वापस GF100_FIFO_ENGN_MSPDEC;
	हाल NVKM_ENGINE_MSPPP : वापस GF100_FIFO_ENGN_MSPPP;
	हाल NVKM_ENGINE_MSVLD : वापस GF100_FIFO_ENGN_MSVLD;
	हाल NVKM_ENGINE_CE    : वापस GF100_FIFO_ENGN_CE0 + engine->subdev.inst;
	हाल NVKM_ENGINE_SW    : वापस GF100_FIFO_ENGN_SW;
	शेष:
		WARN_ON(1);
		वापस -1;
	पूर्ण
पूर्ण

अटल व्योम
gf100_fअगरo_recover_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा gf100_fअगरo *fअगरo = container_of(w, typeof(*fअगरo), recover.work);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_engine *engine;
	अचिन्हित दीर्घ flags;
	u32 engm, engn, toकरो;

	spin_lock_irqsave(&fअगरo->base.lock, flags);
	engm = fअगरo->recover.mask;
	fअगरo->recover.mask = 0ULL;
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);

	nvkm_mask(device, 0x002630, engm, engm);

	क्रम (toकरो = engm; engn = __ffs(toकरो), toकरो; toकरो &= ~BIT_ULL(engn)) अणु
		अगर ((engine = gf100_fअगरo_id_engine(&fअगरo->base, engn))) अणु
			nvkm_subdev_fini(&engine->subdev, false);
			WARN_ON(nvkm_subdev_init(&engine->subdev));
		पूर्ण
	पूर्ण

	gf100_fअगरo_runlist_commit(fअगरo);
	nvkm_wr32(device, 0x00262c, engm);
	nvkm_mask(device, 0x002630, engm, 0x00000000);
पूर्ण

अटल व्योम
gf100_fअगरo_recover(काष्ठा gf100_fअगरo *fअगरo, काष्ठा nvkm_engine *engine,
		   काष्ठा gf100_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 chid = chan->base.chid;
	पूर्णांक engi = gf100_fअगरo_engine_id(&fअगरo->base, engine);

	nvkm_error(subdev, "%s engine fault on channel %d, recovering...\n",
		   engine->subdev.name, chid);
	निश्चित_spin_locked(&fअगरo->base.lock);

	nvkm_mask(device, 0x003004 + (chid * 0x08), 0x00000001, 0x00000000);
	list_del_init(&chan->head);
	chan->समाप्तed = true;

	अगर (engi >= 0 && engi != GF100_FIFO_ENGN_SW)
		fअगरo->recover.mask |= BIT(engi);
	schedule_work(&fअगरo->recover.work);
	nvkm_fअगरo_kevent(&fअगरo->base, chid);
पूर्ण

अटल स्थिर काष्ठा nvkm_क्रमागत
gf100_fअगरo_fault_engine[] = अणु
	अणु 0x00, "PGRAPH", शून्य, NVKM_ENGINE_GR पूर्ण,
	अणु 0x03, "PEEPHOLE", शून्य, NVKM_ENGINE_IFB पूर्ण,
	अणु 0x04, "BAR1", शून्य, NVKM_SUBDEV_BAR पूर्ण,
	अणु 0x05, "BAR3", शून्य, NVKM_SUBDEV_INSTMEM पूर्ण,
	अणु 0x07, "PFIFO", शून्य, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x10, "PMSVLD", शून्य, NVKM_ENGINE_MSVLD पूर्ण,
	अणु 0x11, "PMSPPP", शून्य, NVKM_ENGINE_MSPPP पूर्ण,
	अणु 0x13, "PCOUNTER" पूर्ण,
	अणु 0x14, "PMSPDEC", शून्य, NVKM_ENGINE_MSPDEC पूर्ण,
	अणु 0x15, "PCE0", शून्य, NVKM_ENGINE_CE, 0 पूर्ण,
	अणु 0x16, "PCE1", शून्य, NVKM_ENGINE_CE, 1 पूर्ण,
	अणु 0x17, "PMU" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत
gf100_fअगरo_fault_reason[] = अणु
	अणु 0x00, "PT_NOT_PRESENT" पूर्ण,
	अणु 0x01, "PT_TOO_SHORT" पूर्ण,
	अणु 0x02, "PAGE_NOT_PRESENT" पूर्ण,
	अणु 0x03, "VM_LIMIT_EXCEEDED" पूर्ण,
	अणु 0x04, "NO_CHANNEL" पूर्ण,
	अणु 0x05, "PAGE_SYSTEM_ONLY" पूर्ण,
	अणु 0x06, "PAGE_READ_ONLY" पूर्ण,
	अणु 0x0a, "COMPRESSED_SYSRAM" पूर्ण,
	अणु 0x0c, "INVALID_STORAGE_TYPE" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत
gf100_fअगरo_fault_hubclient[] = अणु
	अणु 0x01, "PCOPY0" पूर्ण,
	अणु 0x02, "PCOPY1" पूर्ण,
	अणु 0x04, "DISPATCH" पूर्ण,
	अणु 0x05, "CTXCTL" पूर्ण,
	अणु 0x06, "PFIFO" पूर्ण,
	अणु 0x07, "BAR_READ" पूर्ण,
	अणु 0x08, "BAR_WRITE" पूर्ण,
	अणु 0x0b, "PVP" पूर्ण,
	अणु 0x0c, "PMSPPP" पूर्ण,
	अणु 0x0d, "PMSVLD" पूर्ण,
	अणु 0x11, "PCOUNTER" पूर्ण,
	अणु 0x12, "PMU" पूर्ण,
	अणु 0x14, "CCACHE" पूर्ण,
	अणु 0x15, "CCACHE_POST" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_क्रमागत
gf100_fअगरo_fault_gpcclient[] = अणु
	अणु 0x01, "TEX" पूर्ण,
	अणु 0x0c, "ESETUP" पूर्ण,
	अणु 0x0e, "CTXCTL" पूर्ण,
	अणु 0x0f, "PROP" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
gf100_fअगरo_fault(काष्ठा nvkm_fअगरo *base, काष्ठा nvkm_fault_data *info)
अणु
	काष्ठा gf100_fअगरo *fअगरo = gf100_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर काष्ठा nvkm_क्रमागत *er, *eu, *ec;
	काष्ठा nvkm_engine *engine = शून्य;
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	अक्षर gpcid[8] = "";

	er = nvkm_क्रमागत_find(gf100_fअगरo_fault_reason, info->reason);
	eu = nvkm_क्रमागत_find(gf100_fअगरo_fault_engine, info->engine);
	अगर (info->hub) अणु
		ec = nvkm_क्रमागत_find(gf100_fअगरo_fault_hubclient, info->client);
	पूर्ण अन्यथा अणु
		ec = nvkm_क्रमागत_find(gf100_fअगरo_fault_gpcclient, info->client);
		snम_लिखो(gpcid, माप(gpcid), "GPC%d/", info->gpc);
	पूर्ण

	अगर (eu && eu->data2) अणु
		चयन (eu->data2) अणु
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
			engine = nvkm_device_engine(device, eu->data2, eu->inst);
			अवरोध;
		पूर्ण
	पूर्ण

	chan = nvkm_fअगरo_chan_inst(&fअगरo->base, info->inst, &flags);

	nvkm_error(subdev,
		   "%s fault at %010llx engine %02x [%s] client %02x [%s%s] "
		   "reason %02x [%s] on channel %d [%010llx %s]\n",
		   info->access ? "write" : "read", info->addr,
		   info->engine, eu ? eu->name : "",
		   info->client, gpcid, ec ? ec->name : "",
		   info->reason, er ? er->name : "", chan ? chan->chid : -1,
		   info->inst, chan ? chan->object.client->name : "unknown");

	अगर (engine && chan)
		gf100_fअगरo_recover(fअगरo, engine, (व्योम *)chan);
	nvkm_fअगरo_chan_put(&fअगरo->base, flags, &chan);
पूर्ण

अटल स्थिर काष्ठा nvkm_क्रमागत
gf100_fअगरo_sched_reason[] = अणु
	अणु 0x0a, "CTXSW_TIMEOUT" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
gf100_fअगरo_पूर्णांकr_sched_ctxsw(काष्ठा gf100_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	काष्ठा nvkm_engine *engine;
	काष्ठा gf100_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	u32 engn;

	spin_lock_irqsave(&fअगरo->base.lock, flags);
	क्रम (engn = 0; engn < 6; engn++) अणु
		u32 stat = nvkm_rd32(device, 0x002640 + (engn * 0x04));
		u32 busy = (stat & 0x80000000);
		u32 save = (stat & 0x00100000); /* maybe? */
		u32 unk0 = (stat & 0x00040000);
		u32 unk1 = (stat & 0x00001000);
		u32 chid = (stat & 0x0000007f);
		(व्योम)save;

		अगर (busy && unk0 && unk1) अणु
			list_क्रम_each_entry(chan, &fअगरo->chan, head) अणु
				अगर (chan->base.chid == chid) अणु
					engine = gf100_fअगरo_id_engine(&fअगरo->base, engn);
					अगर (!engine)
						अवरोध;
					gf100_fअगरo_recover(fअगरo, engine, chan);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&fअगरo->base.lock, flags);
पूर्ण

अटल व्योम
gf100_fअगरo_पूर्णांकr_sched(काष्ठा gf100_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x00254c);
	u32 code = पूर्णांकr & 0x000000ff;
	स्थिर काष्ठा nvkm_क्रमागत *en;

	en = nvkm_क्रमागत_find(gf100_fअगरo_sched_reason, code);

	nvkm_error(subdev, "SCHED_ERROR %02x [%s]\n", code, en ? en->name : "");

	चयन (code) अणु
	हाल 0x0a:
		gf100_fअगरo_पूर्णांकr_sched_ctxsw(fअगरo);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम
gf100_fअगरo_पूर्णांकr_fault(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक unit)
अणु
	काष्ठा nvkm_device *device = fअगरo->engine.subdev.device;
	u32 inst = nvkm_rd32(device, 0x002800 + (unit * 0x10));
	u32 valo = nvkm_rd32(device, 0x002804 + (unit * 0x10));
	u32 vahi = nvkm_rd32(device, 0x002808 + (unit * 0x10));
	u32 type = nvkm_rd32(device, 0x00280c + (unit * 0x10));
	काष्ठा nvkm_fault_data info;

	info.inst   =  (u64)inst << 12;
	info.addr   = ((u64)vahi << 32) | valo;
	info.समय   = 0;
	info.engine = unit;
	info.valid  = 1;
	info.gpc    = (type & 0x1f000000) >> 24;
	info.client = (type & 0x00001f00) >> 8;
	info.access = (type & 0x00000080) >> 7;
	info.hub    = (type & 0x00000040) >> 6;
	info.reason = (type & 0x0000000f);

	nvkm_fअगरo_fault(fअगरo, &info);
पूर्ण

अटल स्थिर काष्ठा nvkm_bitfield
gf100_fअगरo_pbdma_पूर्णांकr[] = अणु
/*	अणु 0x00008000, "" पूर्ण	seen with null ib push */
	अणु 0x00200000, "ILLEGAL_MTHD" पूर्ण,
	अणु 0x00800000, "EMPTY_SUBC" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
gf100_fअगरo_पूर्णांकr_pbdma(काष्ठा gf100_fअगरo *fअगरo, पूर्णांक unit)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x040108 + (unit * 0x2000));
	u32 addr = nvkm_rd32(device, 0x0400c0 + (unit * 0x2000));
	u32 data = nvkm_rd32(device, 0x0400c4 + (unit * 0x2000));
	u32 chid = nvkm_rd32(device, 0x040120 + (unit * 0x2000)) & 0x7f;
	u32 subc = (addr & 0x00070000) >> 16;
	u32 mthd = (addr & 0x00003ffc);
	काष्ठा nvkm_fअगरo_chan *chan;
	अचिन्हित दीर्घ flags;
	u32 show= stat;
	अक्षर msg[128];

	अगर (stat & 0x00800000) अणु
		अगर (device->sw) अणु
			अगर (nvkm_sw_mthd(device->sw, chid, subc, mthd, data))
				show &= ~0x00800000;
		पूर्ण
	पूर्ण

	अगर (show) अणु
		nvkm_snprपूर्णांकbf(msg, माप(msg), gf100_fअगरo_pbdma_पूर्णांकr, show);
		chan = nvkm_fअगरo_chan_chid(&fअगरo->base, chid, &flags);
		nvkm_error(subdev, "PBDMA%d: %08x [%s] ch %d [%010llx %s] "
				   "subc %d mthd %04x data %08x\n",
			   unit, show, msg, chid, chan ? chan->inst->addr : 0,
			   chan ? chan->object.client->name : "unknown",
			   subc, mthd, data);
		nvkm_fअगरo_chan_put(&fअगरo->base, flags, &chan);
	पूर्ण

	nvkm_wr32(device, 0x0400c0 + (unit * 0x2000), 0x80600008);
	nvkm_wr32(device, 0x040108 + (unit * 0x2000), stat);
पूर्ण

अटल व्योम
gf100_fअगरo_पूर्णांकr_runlist(काष्ठा gf100_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x002a00);

	अगर (पूर्णांकr & 0x10000000) अणु
		wake_up(&fअगरo->runlist.रुको);
		nvkm_wr32(device, 0x002a00, 0x10000000);
		पूर्णांकr &= ~0x10000000;
	पूर्ण

	अगर (पूर्णांकr) अणु
		nvkm_error(subdev, "RUNLIST %08x\n", पूर्णांकr);
		nvkm_wr32(device, 0x002a00, पूर्णांकr);
	पूर्ण
पूर्ण

अटल व्योम
gf100_fअगरo_पूर्णांकr_engine_unit(काष्ठा gf100_fअगरo *fअगरo, पूर्णांक engn)
अणु
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 पूर्णांकr = nvkm_rd32(device, 0x0025a8 + (engn * 0x04));
	u32 पूर्णांकe = nvkm_rd32(device, 0x002628);
	u32 unkn;

	nvkm_wr32(device, 0x0025a8 + (engn * 0x04), पूर्णांकr);

	क्रम (unkn = 0; unkn < 8; unkn++) अणु
		u32 पूर्णांकs = (पूर्णांकr >> (unkn * 0x04)) & पूर्णांकe;
		अगर (पूर्णांकs & 0x1) अणु
			nvkm_fअगरo_uevent(&fअगरo->base);
			पूर्णांकs &= ~1;
		पूर्ण
		अगर (पूर्णांकs) अणु
			nvkm_error(subdev, "ENGINE %d %d %01x",
				   engn, unkn, पूर्णांकs);
			nvkm_mask(device, 0x002628, पूर्णांकs, 0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
gf100_fअगरo_पूर्णांकr_engine(काष्ठा gf100_fअगरo *fअगरo)
अणु
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	u32 mask = nvkm_rd32(device, 0x0025a4);
	जबतक (mask) अणु
		u32 unit = __ffs(mask);
		gf100_fअगरo_पूर्णांकr_engine_unit(fअगरo, unit);
		mask &= ~(1 << unit);
	पूर्ण
पूर्ण

अटल व्योम
gf100_fअगरo_पूर्णांकr(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gf100_fअगरo *fअगरo = gf100_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mask = nvkm_rd32(device, 0x002140);
	u32 stat = nvkm_rd32(device, 0x002100) & mask;

	अगर (stat & 0x00000001) अणु
		u32 पूर्णांकr = nvkm_rd32(device, 0x00252c);
		nvkm_warn(subdev, "INTR 00000001: %08x\n", पूर्णांकr);
		nvkm_wr32(device, 0x002100, 0x00000001);
		stat &= ~0x00000001;
	पूर्ण

	अगर (stat & 0x00000100) अणु
		gf100_fअगरo_पूर्णांकr_sched(fअगरo);
		nvkm_wr32(device, 0x002100, 0x00000100);
		stat &= ~0x00000100;
	पूर्ण

	अगर (stat & 0x00010000) अणु
		u32 पूर्णांकr = nvkm_rd32(device, 0x00256c);
		nvkm_warn(subdev, "INTR 00010000: %08x\n", पूर्णांकr);
		nvkm_wr32(device, 0x002100, 0x00010000);
		stat &= ~0x00010000;
	पूर्ण

	अगर (stat & 0x01000000) अणु
		u32 पूर्णांकr = nvkm_rd32(device, 0x00258c);
		nvkm_warn(subdev, "INTR 01000000: %08x\n", पूर्णांकr);
		nvkm_wr32(device, 0x002100, 0x01000000);
		stat &= ~0x01000000;
	पूर्ण

	अगर (stat & 0x10000000) अणु
		u32 mask = nvkm_rd32(device, 0x00259c);
		जबतक (mask) अणु
			u32 unit = __ffs(mask);
			gf100_fअगरo_पूर्णांकr_fault(&fअगरo->base, unit);
			nvkm_wr32(device, 0x00259c, (1 << unit));
			mask &= ~(1 << unit);
		पूर्ण
		stat &= ~0x10000000;
	पूर्ण

	अगर (stat & 0x20000000) अणु
		u32 mask = nvkm_rd32(device, 0x0025a0);
		जबतक (mask) अणु
			u32 unit = __ffs(mask);
			gf100_fअगरo_पूर्णांकr_pbdma(fअगरo, unit);
			nvkm_wr32(device, 0x0025a0, (1 << unit));
			mask &= ~(1 << unit);
		पूर्ण
		stat &= ~0x20000000;
	पूर्ण

	अगर (stat & 0x40000000) अणु
		gf100_fअगरo_पूर्णांकr_runlist(fअगरo);
		stat &= ~0x40000000;
	पूर्ण

	अगर (stat & 0x80000000) अणु
		gf100_fअगरo_पूर्णांकr_engine(fअगरo);
		stat &= ~0x80000000;
	पूर्ण

	अगर (stat) अणु
		nvkm_error(subdev, "INTR %08x\n", stat);
		nvkm_mask(device, 0x002140, stat, 0x00000000);
		nvkm_wr32(device, 0x002100, stat);
	पूर्ण
पूर्ण

अटल पूर्णांक
gf100_fअगरo_oneinit(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gf100_fअगरo *fअगरo = gf100_fअगरo(base);
	काष्ठा nvkm_subdev *subdev = &fअगरo->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_vmm *bar = nvkm_bar_bar1_vmm(device);
	पूर्णांक ret;

	/* Determine number of PBDMAs by checking valid enable bits. */
	nvkm_wr32(device, 0x002204, 0xffffffff);
	fअगरo->pbdma_nr = hweight32(nvkm_rd32(device, 0x002204));
	nvkm_debug(subdev, "%d PBDMA(s)\n", fअगरo->pbdma_nr);


	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0x1000,
			      false, &fअगरo->runlist.mem[0]);
	अगर (ret)
		वापस ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 0x1000, 0x1000,
			      false, &fअगरo->runlist.mem[1]);
	अगर (ret)
		वापस ret;

	init_रुकोqueue_head(&fअगरo->runlist.रुको);

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 128 * 0x1000,
			      0x1000, false, &fअगरo->user.mem);
	अगर (ret)
		वापस ret;

	ret = nvkm_vmm_get(bar, 12, nvkm_memory_size(fअगरo->user.mem),
			   &fअगरo->user.bar);
	अगर (ret)
		वापस ret;

	वापस nvkm_memory_map(fअगरo->user.mem, 0, bar, fअगरo->user.bar, शून्य, 0);
पूर्ण

अटल व्योम
gf100_fअगरo_fini(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gf100_fअगरo *fअगरo = gf100_fअगरo(base);
	flush_work(&fअगरo->recover.work);
पूर्ण

अटल व्योम
gf100_fअगरo_init(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gf100_fअगरo *fअगरo = gf100_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	पूर्णांक i;

	/* Enable PBDMAs. */
	nvkm_wr32(device, 0x000204, (1 << fअगरo->pbdma_nr) - 1);
	nvkm_wr32(device, 0x002204, (1 << fअगरo->pbdma_nr) - 1);

	/* Assign engines to PBDMAs. */
	अगर (fअगरo->pbdma_nr >= 3) अणु
		nvkm_wr32(device, 0x002208, ~(1 << 0)); /* PGRAPH */
		nvkm_wr32(device, 0x00220c, ~(1 << 1)); /* PVP */
		nvkm_wr32(device, 0x002210, ~(1 << 1)); /* PMSPP */
		nvkm_wr32(device, 0x002214, ~(1 << 1)); /* PMSVLD */
		nvkm_wr32(device, 0x002218, ~(1 << 2)); /* PCE0 */
		nvkm_wr32(device, 0x00221c, ~(1 << 1)); /* PCE1 */
	पूर्ण

	/* PBDMA[n] */
	क्रम (i = 0; i < fअगरo->pbdma_nr; i++) अणु
		nvkm_mask(device, 0x04013c + (i * 0x2000), 0x10000100, 0x00000000);
		nvkm_wr32(device, 0x040108 + (i * 0x2000), 0xffffffff); /* INTR */
		nvkm_wr32(device, 0x04010c + (i * 0x2000), 0xfffffeff); /* INTREN */
	पूर्ण

	nvkm_mask(device, 0x002200, 0x00000001, 0x00000001);
	nvkm_wr32(device, 0x002254, 0x10000000 | fअगरo->user.bar->addr >> 12);

	nvkm_wr32(device, 0x002100, 0xffffffff);
	nvkm_wr32(device, 0x002140, 0x7fffffff);
	nvkm_wr32(device, 0x002628, 0x00000001); /* ENGINE_INTR_EN */
पूर्ण

अटल व्योम *
gf100_fअगरo_dtor(काष्ठा nvkm_fअगरo *base)
अणु
	काष्ठा gf100_fअगरo *fअगरo = gf100_fअगरo(base);
	काष्ठा nvkm_device *device = fअगरo->base.engine.subdev.device;
	nvkm_vmm_put(nvkm_bar_bar1_vmm(device), &fअगरo->user.bar);
	nvkm_memory_unref(&fअगरo->user.mem);
	nvkm_memory_unref(&fअगरo->runlist.mem[0]);
	nvkm_memory_unref(&fअगरo->runlist.mem[1]);
	वापस fअगरo;
पूर्ण

अटल स्थिर काष्ठा nvkm_fअगरo_func
gf100_fअगरo = अणु
	.dtor = gf100_fअगरo_dtor,
	.oneinit = gf100_fअगरo_oneinit,
	.init = gf100_fअगरo_init,
	.fini = gf100_fअगरo_fini,
	.पूर्णांकr = gf100_fअगरo_पूर्णांकr,
	.fault = gf100_fअगरo_fault,
	.engine_id = gf100_fअगरo_engine_id,
	.id_engine = gf100_fअगरo_id_engine,
	.uevent_init = gf100_fअगरo_uevent_init,
	.uevent_fini = gf100_fअगरo_uevent_fini,
	.chan = अणु
		&gf100_fअगरo_gpfअगरo_oclass,
		शून्य
	पूर्ण,
पूर्ण;

पूर्णांक
gf100_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	काष्ठा gf100_fअगरo *fअगरo;

	अगर (!(fअगरo = kzalloc(माप(*fअगरo), GFP_KERNEL)))
		वापस -ENOMEM;
	INIT_LIST_HEAD(&fअगरo->chan);
	INIT_WORK(&fअगरo->recover.work, gf100_fअगरo_recover_work);
	*pfअगरo = &fअगरo->base;

	वापस nvkm_fअगरo_ctor(&gf100_fअगरo, device, type, inst, 128, &fअगरo->base);
पूर्ण
