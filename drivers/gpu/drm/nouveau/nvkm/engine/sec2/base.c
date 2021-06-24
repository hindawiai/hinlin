<शैली गुरु>
/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "priv.h"

#समावेश <core/firmware.h>
#समावेश <subdev/top.h>

अटल व्योम
nvkm_sec2_recv(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nvkm_sec2 *sec2 = container_of(work, typeof(*sec2), work);

	अगर (!sec2->iniपंचांगsg_received) अणु
		पूर्णांक ret = sec2->func->iniपंचांगsg(sec2);
		अगर (ret) अणु
			nvkm_error(&sec2->engine.subdev,
				   "error parsing init message: %d\n", ret);
			वापस;
		पूर्ण

		sec2->iniपंचांगsg_received = true;
	पूर्ण

	nvkm_falcon_msgq_recv(sec2->msgq);
पूर्ण

अटल व्योम
nvkm_sec2_पूर्णांकr(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_sec2 *sec2 = nvkm_sec2(engine);
	sec2->func->पूर्णांकr(sec2);
पूर्ण

अटल पूर्णांक
nvkm_sec2_fini(काष्ठा nvkm_engine *engine, bool suspend)
अणु
	काष्ठा nvkm_sec2 *sec2 = nvkm_sec2(engine);

	flush_work(&sec2->work);

	अगर (suspend) अणु
		nvkm_falcon_cmdq_fini(sec2->cmdq);
		sec2->iniपंचांगsg_received = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *
nvkm_sec2_dtor(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_sec2 *sec2 = nvkm_sec2(engine);
	nvkm_falcon_msgq_del(&sec2->msgq);
	nvkm_falcon_cmdq_del(&sec2->cmdq);
	nvkm_falcon_qmgr_del(&sec2->qmgr);
	nvkm_falcon_dtor(&sec2->falcon);
	वापस sec2;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_sec2 = अणु
	.dtor = nvkm_sec2_dtor,
	.fini = nvkm_sec2_fini,
	.पूर्णांकr = nvkm_sec2_पूर्णांकr,
पूर्ण;

पूर्णांक
nvkm_sec2_new_(स्थिर काष्ठा nvkm_sec2_fwअगर *fwअगर, काष्ठा nvkm_device *device,
	       क्रमागत nvkm_subdev_type type, पूर्णांक inst, u32 addr, काष्ठा nvkm_sec2 **psec2)
अणु
	काष्ठा nvkm_sec2 *sec2;
	पूर्णांक ret;

	अगर (!(sec2 = *psec2 = kzalloc(माप(*sec2), GFP_KERNEL)))
		वापस -ENOMEM;

	ret = nvkm_engine_ctor(&nvkm_sec2, device, type, inst, true, &sec2->engine);
	अगर (ret)
		वापस ret;

	fwअगर = nvkm_firmware_load(&sec2->engine.subdev, fwअगर, "Sec2", sec2);
	अगर (IS_ERR(fwअगर))
		वापस PTR_ERR(fwअगर);

	sec2->func = fwअगर->func;

	ret = nvkm_falcon_ctor(sec2->func->flcn, &sec2->engine.subdev,
			       sec2->engine.subdev.name, addr, &sec2->falcon);
	अगर (ret)
		वापस ret;

	अगर ((ret = nvkm_falcon_qmgr_new(&sec2->falcon, &sec2->qmgr)) ||
	    (ret = nvkm_falcon_cmdq_new(sec2->qmgr, "cmdq", &sec2->cmdq)) ||
	    (ret = nvkm_falcon_msgq_new(sec2->qmgr, "msgq", &sec2->msgq)))
		वापस ret;

	INIT_WORK(&sec2->work, nvkm_sec2_recv);
	वापस 0;
पूर्ण;
