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

#समावेश <core/firmware.h>
#समावेश <subdev/समयr.h>

bool
nvkm_pmu_fan_controlled(काष्ठा nvkm_device *device)
अणु
	काष्ठा nvkm_pmu *pmu = device->pmu;

	/* Internal PMU FW करोes not currently control fans in any way,
	 * allow SW control of fans instead.
	 */
	अगर (pmu && pmu->func->code.size)
		वापस false;

	/* Default (board-loaded, or VBIOS PMU/PREOS) PMU FW on Fermi
	 * and newer स्वतःmatically control the fan speed, which would
	 * पूर्णांकerfere with SW control.
	 */
	वापस (device->chipset >= 0xc0);
पूर्ण

व्योम
nvkm_pmu_pgob(काष्ठा nvkm_pmu *pmu, bool enable)
अणु
	अगर (pmu && pmu->func->pgob)
		pmu->func->pgob(pmu, enable);
पूर्ण

अटल व्योम
nvkm_pmu_recv(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvkm_pmu *pmu = container_of(work, typeof(*pmu), recv.work);
	वापस pmu->func->recv(pmu);
पूर्ण

पूर्णांक
nvkm_pmu_send(काष्ठा nvkm_pmu *pmu, u32 reply[2],
	      u32 process, u32 message, u32 data0, u32 data1)
अणु
	अगर (!pmu || !pmu->func->send)
		वापस -ENODEV;
	वापस pmu->func->send(pmu, reply, process, message, data0, data1);
पूर्ण

अटल व्योम
nvkm_pmu_पूर्णांकr(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pmu *pmu = nvkm_pmu(subdev);
	अगर (!pmu->func->पूर्णांकr)
		वापस;
	pmu->func->पूर्णांकr(pmu);
पूर्ण

अटल पूर्णांक
nvkm_pmu_fini(काष्ठा nvkm_subdev *subdev, bool suspend)
अणु
	काष्ठा nvkm_pmu *pmu = nvkm_pmu(subdev);

	अगर (pmu->func->fini)
		pmu->func->fini(pmu);

	flush_work(&pmu->recv.work);

	reinit_completion(&pmu->wpr_पढ़ोy);

	nvkm_falcon_cmdq_fini(pmu->lpq);
	nvkm_falcon_cmdq_fini(pmu->hpq);
	pmu->iniपंचांगsg_received = false;
	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_pmu_reset(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;

	अगर (!pmu->func->enabled(pmu))
		वापस 0;

	/* Inhibit पूर्णांकerrupts, and रुको क्रम idle. */
	nvkm_wr32(device, 0x10a014, 0x0000ffff);
	nvkm_msec(device, 2000,
		अगर (!nvkm_rd32(device, 0x10a04c))
			अवरोध;
	);

	/* Reset. */
	अगर (pmu->func->reset)
		pmu->func->reset(pmu);

	/* Wait क्रम IMEM/DMEM scrubbing to be complete. */
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x10a10c) & 0x00000006))
			अवरोध;
	);

	वापस 0;
पूर्ण

अटल पूर्णांक
nvkm_pmu_preinit(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pmu *pmu = nvkm_pmu(subdev);
	वापस nvkm_pmu_reset(pmu);
पूर्ण

अटल पूर्णांक
nvkm_pmu_init(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pmu *pmu = nvkm_pmu(subdev);
	पूर्णांक ret = nvkm_pmu_reset(pmu);
	अगर (ret == 0 && pmu->func->init)
		ret = pmu->func->init(pmu);
	वापस ret;
पूर्ण

अटल व्योम *
nvkm_pmu_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_pmu *pmu = nvkm_pmu(subdev);
	nvkm_falcon_msgq_del(&pmu->msgq);
	nvkm_falcon_cmdq_del(&pmu->lpq);
	nvkm_falcon_cmdq_del(&pmu->hpq);
	nvkm_falcon_qmgr_del(&pmu->qmgr);
	nvkm_falcon_dtor(&pmu->falcon);
	mutex_destroy(&pmu->send.mutex);
	वापस nvkm_pmu(subdev);
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_pmu = अणु
	.dtor = nvkm_pmu_dtor,
	.preinit = nvkm_pmu_preinit,
	.init = nvkm_pmu_init,
	.fini = nvkm_pmu_fini,
	.पूर्णांकr = nvkm_pmu_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_pmu_ctor(स्थिर काष्ठा nvkm_pmu_fwअगर *fwअगर, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pmu *pmu)
अणु
	पूर्णांक ret;

	nvkm_subdev_ctor(&nvkm_pmu, device, type, inst, &pmu->subdev);

	mutex_init(&pmu->send.mutex);

	INIT_WORK(&pmu->recv.work, nvkm_pmu_recv);
	init_रुकोqueue_head(&pmu->recv.रुको);

	fwअगर = nvkm_firmware_load(&pmu->subdev, fwअगर, "Pmu", pmu);
	अगर (IS_ERR(fwअगर))
		वापस PTR_ERR(fwअगर);

	pmu->func = fwअगर->func;

	ret = nvkm_falcon_ctor(pmu->func->flcn, &pmu->subdev, pmu->subdev.name,
			       0x10a000, &pmu->falcon);
	अगर (ret)
		वापस ret;

	अगर ((ret = nvkm_falcon_qmgr_new(&pmu->falcon, &pmu->qmgr)) ||
	    (ret = nvkm_falcon_cmdq_new(pmu->qmgr, "hpq", &pmu->hpq)) ||
	    (ret = nvkm_falcon_cmdq_new(pmu->qmgr, "lpq", &pmu->lpq)) ||
	    (ret = nvkm_falcon_msgq_new(pmu->qmgr, "msgq", &pmu->msgq)))
		वापस ret;

	init_completion(&pmu->wpr_पढ़ोy);
	वापस 0;
पूर्ण

पूर्णांक
nvkm_pmu_new_(स्थिर काष्ठा nvkm_pmu_fwअगर *fwअगर, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pmu **ppmu)
अणु
	काष्ठा nvkm_pmu *pmu;
	अगर (!(pmu = *ppmu = kzalloc(माप(*pmu), GFP_KERNEL)))
		वापस -ENOMEM;
	वापस nvkm_pmu_ctor(fwअगर, device, type, inst, *ppmu);
पूर्ण
