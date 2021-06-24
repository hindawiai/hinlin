<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
#समावेश "fuc/gt215.fuc3.h"

#समावेश <subdev/समयr.h>

पूर्णांक
gt215_pmu_send(काष्ठा nvkm_pmu *pmu, u32 reply[2],
	       u32 process, u32 message, u32 data0, u32 data1)
अणु
	काष्ठा nvkm_subdev *subdev = &pmu->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 addr;

	mutex_lock(&pmu->send.mutex);
	/* रुको क्रम a मुक्त slot in the fअगरo */
	addr  = nvkm_rd32(device, 0x10a4a0);
	अगर (nvkm_msec(device, 2000,
		u32 पंचांगp = nvkm_rd32(device, 0x10a4b0);
		अगर (पंचांगp != (addr ^ 8))
			अवरोध;
	) < 0) अणु
		mutex_unlock(&pmu->send.mutex);
		वापस -EBUSY;
	पूर्ण

	/* we currently only support a single process at a समय रुकोing
	 * on a synchronous reply, take the PMU mutex and tell the
	 * receive handler what we're रुकोing क्रम
	 */
	अगर (reply) अणु
		pmu->recv.message = message;
		pmu->recv.process = process;
	पूर्ण

	/* acquire data segment access */
	करो अणु
		nvkm_wr32(device, 0x10a580, 0x00000001);
	पूर्ण जबतक (nvkm_rd32(device, 0x10a580) != 0x00000001);

	/* ग_लिखो the packet */
	nvkm_wr32(device, 0x10a1c0, 0x01000000 | (((addr & 0x07) << 4) +
				pmu->send.base));
	nvkm_wr32(device, 0x10a1c4, process);
	nvkm_wr32(device, 0x10a1c4, message);
	nvkm_wr32(device, 0x10a1c4, data0);
	nvkm_wr32(device, 0x10a1c4, data1);
	nvkm_wr32(device, 0x10a4a0, (addr + 1) & 0x0f);

	/* release data segment access */
	nvkm_wr32(device, 0x10a580, 0x00000000);

	/* रुको क्रम reply, अगर requested */
	अगर (reply) अणु
		रुको_event(pmu->recv.रुको, (pmu->recv.process == 0));
		reply[0] = pmu->recv.data[0];
		reply[1] = pmu->recv.data[1];
	पूर्ण

	mutex_unlock(&pmu->send.mutex);
	वापस 0;
पूर्ण

व्योम
gt215_pmu_recv(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nvkm_subdev *subdev = &pmu->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 process, message, data0, data1;

	/* nothing to करो अगर GET == PUT */
	u32 addr =  nvkm_rd32(device, 0x10a4cc);
	अगर (addr == nvkm_rd32(device, 0x10a4c8))
		वापस;

	/* acquire data segment access */
	करो अणु
		nvkm_wr32(device, 0x10a580, 0x00000002);
	पूर्ण जबतक (nvkm_rd32(device, 0x10a580) != 0x00000002);

	/* पढ़ो the packet */
	nvkm_wr32(device, 0x10a1c0, 0x02000000 | (((addr & 0x07) << 4) +
				pmu->recv.base));
	process = nvkm_rd32(device, 0x10a1c4);
	message = nvkm_rd32(device, 0x10a1c4);
	data0   = nvkm_rd32(device, 0x10a1c4);
	data1   = nvkm_rd32(device, 0x10a1c4);
	nvkm_wr32(device, 0x10a4cc, (addr + 1) & 0x0f);

	/* release data segment access */
	nvkm_wr32(device, 0x10a580, 0x00000000);

	/* wake process अगर it's रुकोing on a synchronous reply */
	अगर (pmu->recv.process) अणु
		अगर (process == pmu->recv.process &&
		    message == pmu->recv.message) अणु
			pmu->recv.data[0] = data0;
			pmu->recv.data[1] = data1;
			pmu->recv.process = 0;
			wake_up(&pmu->recv.रुको);
			वापस;
		पूर्ण
	पूर्ण

	/* right now there's no other expected responses from the engine,
	 * so assume that any unexpected message is an error.
	 */
	nvkm_warn(subdev, "%c%c%c%c %08x %08x %08x %08x\n",
		  (अक्षर)((process & 0x000000ff) >>  0),
		  (अक्षर)((process & 0x0000ff00) >>  8),
		  (अक्षर)((process & 0x00ff0000) >> 16),
		  (अक्षर)((process & 0xff000000) >> 24),
		  process, message, data0, data1);
पूर्ण

व्योम
gt215_pmu_पूर्णांकr(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nvkm_subdev *subdev = &pmu->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 disp = nvkm_rd32(device, 0x10a01c);
	u32 पूर्णांकr = nvkm_rd32(device, 0x10a008) & disp & ~(disp >> 16);

	अगर (पूर्णांकr & 0x00000020) अणु
		u32 stat = nvkm_rd32(device, 0x10a16c);
		अगर (stat & 0x80000000) अणु
			nvkm_error(subdev, "UAS fault at %06x addr %08x\n",
				   stat & 0x00ffffff,
				   nvkm_rd32(device, 0x10a168));
			nvkm_wr32(device, 0x10a16c, 0x00000000);
			पूर्णांकr &= ~0x00000020;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकr & 0x00000040) अणु
		schedule_work(&pmu->recv.work);
		nvkm_wr32(device, 0x10a004, 0x00000040);
		पूर्णांकr &= ~0x00000040;
	पूर्ण

	अगर (पूर्णांकr & 0x00000080) अणु
		nvkm_info(subdev, "wr32 %06x %08x\n",
			  nvkm_rd32(device, 0x10a7a0),
			  nvkm_rd32(device, 0x10a7a4));
		nvkm_wr32(device, 0x10a004, 0x00000080);
		पूर्णांकr &= ~0x00000080;
	पूर्ण

	अगर (पूर्णांकr) अणु
		nvkm_error(subdev, "intr %08x\n", पूर्णांकr);
		nvkm_wr32(device, 0x10a004, पूर्णांकr);
	पूर्ण
पूर्ण

व्योम
gt215_pmu_fini(काष्ठा nvkm_pmu *pmu)
अणु
	nvkm_wr32(pmu->subdev.device, 0x10a014, 0x00000060);
पूर्ण

अटल व्योम
gt215_pmu_reset(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;
	nvkm_mask(device, 0x022210, 0x00000001, 0x00000000);
	nvkm_mask(device, 0x022210, 0x00000001, 0x00000001);
	nvkm_rd32(device, 0x022210);
पूर्ण

अटल bool
gt215_pmu_enabled(काष्ठा nvkm_pmu *pmu)
अणु
	वापस nvkm_rd32(pmu->subdev.device, 0x022210) & 0x00000001;
पूर्ण

पूर्णांक
gt215_pmu_init(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;
	पूर्णांक i;

	/* upload data segment */
	nvkm_wr32(device, 0x10a1c0, 0x01000000);
	क्रम (i = 0; i < pmu->func->data.size / 4; i++)
		nvkm_wr32(device, 0x10a1c4, pmu->func->data.data[i]);

	/* upload code segment */
	nvkm_wr32(device, 0x10a180, 0x01000000);
	क्रम (i = 0; i < pmu->func->code.size / 4; i++) अणु
		अगर ((i & 0x3f) == 0)
			nvkm_wr32(device, 0x10a188, i >> 6);
		nvkm_wr32(device, 0x10a184, pmu->func->code.data[i]);
	पूर्ण

	/* start it running */
	nvkm_wr32(device, 0x10a10c, 0x00000000);
	nvkm_wr32(device, 0x10a104, 0x00000000);
	nvkm_wr32(device, 0x10a100, 0x00000002);

	/* रुको क्रम valid host->pmu ring configuration */
	अगर (nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x10a4d0))
			अवरोध;
	) < 0)
		वापस -EBUSY;
	pmu->send.base = nvkm_rd32(device, 0x10a4d0) & 0x0000ffff;
	pmu->send.size = nvkm_rd32(device, 0x10a4d0) >> 16;

	/* रुको क्रम valid pmu->host ring configuration */
	अगर (nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x10a4dc))
			अवरोध;
	) < 0)
		वापस -EBUSY;
	pmu->recv.base = nvkm_rd32(device, 0x10a4dc) & 0x0000ffff;
	pmu->recv.size = nvkm_rd32(device, 0x10a4dc) >> 16;

	nvkm_wr32(device, 0x10a010, 0x000000e0);
	वापस 0;
पूर्ण

स्थिर काष्ठा nvkm_falcon_func
gt215_pmu_flcn = अणु
	.debug = 0xc08,
	.fbअगर = 0xe00,
	.load_imem = nvkm_falcon_v1_load_imem,
	.load_dmem = nvkm_falcon_v1_load_dmem,
	.पढ़ो_dmem = nvkm_falcon_v1_पढ़ो_dmem,
	.bind_context = nvkm_falcon_v1_bind_context,
	.रुको_क्रम_halt = nvkm_falcon_v1_रुको_क्रम_halt,
	.clear_पूर्णांकerrupt = nvkm_falcon_v1_clear_पूर्णांकerrupt,
	.set_start_addr = nvkm_falcon_v1_set_start_addr,
	.start = nvkm_falcon_v1_start,
	.enable = nvkm_falcon_v1_enable,
	.disable = nvkm_falcon_v1_disable,
	.cmdq = अणु 0x4a0, 0x4b0, 4 पूर्ण,
	.msgq = अणु 0x4c8, 0x4cc, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_func
gt215_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.code.data = gt215_pmu_code,
	.code.size = माप(gt215_pmu_code),
	.data.data = gt215_pmu_data,
	.data.size = माप(gt215_pmu_data),
	.enabled = gt215_pmu_enabled,
	.reset = gt215_pmu_reset,
	.init = gt215_pmu_init,
	.fini = gt215_pmu_fini,
	.पूर्णांकr = gt215_pmu_पूर्णांकr,
	.send = gt215_pmu_send,
	.recv = gt215_pmu_recv,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gt215_pmu_fwअगर[] = अणु
	अणु -1, gf100_pmu_nofw, &gt215_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gt215_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gt215_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
