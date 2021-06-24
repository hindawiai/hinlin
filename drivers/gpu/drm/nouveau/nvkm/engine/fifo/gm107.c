<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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
#समावेश "changk104.h"

#समावेश <core/gpuobj.h>
#समावेश <subdev/fault.h>

#समावेश <nvअगर/class.h>

अटल व्योम
gm107_fअगरo_runlist_chan(काष्ठा gk104_fअगरo_chan *chan,
			काष्ठा nvkm_memory *memory, u32 offset)
अणु
	nvkm_wo32(memory, offset + 0, chan->base.chid);
	nvkm_wo32(memory, offset + 4, chan->base.inst->addr >> 12);
पूर्ण

स्थिर काष्ठा gk104_fअगरo_runlist_func
gm107_fअगरo_runlist = अणु
	.size = 8,
	.cgrp = gk110_fअगरo_runlist_cgrp,
	.chan = gm107_fअगरo_runlist_chan,
	.commit = gk104_fअगरo_runlist_commit,
पूर्ण;

स्थिर काष्ठा nvkm_क्रमागत
gm107_fअगरo_fault_engine[] = अणु
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
	अणु 0x13, "PERF" पूर्ण,
	अणु 0x17, "PMU" पूर्ण,
	अणु 0x18, "PTP" पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
gm107_fअगरo_पूर्णांकr_fault(काष्ठा nvkm_fअगरo *fअगरo, पूर्णांक unit)
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
	info.client = (type & 0x00003f00) >> 8;
	info.access = (type & 0x00000080) >> 7;
	info.hub    = (type & 0x00000040) >> 6;
	info.reason = (type & 0x0000000f);

	nvkm_fअगरo_fault(fअगरo, &info);
पूर्ण

अटल स्थिर काष्ठा gk104_fअगरo_func
gm107_fअगरo = अणु
	.पूर्णांकr.fault = gm107_fअगरo_पूर्णांकr_fault,
	.pbdma = &gk208_fअगरo_pbdma,
	.fault.access = gk104_fअगरo_fault_access,
	.fault.engine = gm107_fअगरo_fault_engine,
	.fault.reason = gk104_fअगरo_fault_reason,
	.fault.hubclient = gk104_fअगरo_fault_hubclient,
	.fault.gpcclient = gk104_fअगरo_fault_gpcclient,
	.runlist = &gm107_fअगरo_runlist,
	.chan = अणुअणु0,0,KEPLER_CHANNEL_GPFIFO_Bपूर्ण, gk104_fअगरo_gpfअगरo_new पूर्ण,
पूर्ण;

पूर्णांक
gm107_fअगरo_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	       काष्ठा nvkm_fअगरo **pfअगरo)
अणु
	वापस gk104_fअगरo_new_(&gm107_fअगरo, device, type, inst, 2048, pfअगरo);
पूर्ण
