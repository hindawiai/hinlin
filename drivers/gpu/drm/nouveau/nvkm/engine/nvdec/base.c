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

अटल व्योम *
nvkm_nvdec_dtor(काष्ठा nvkm_engine *engine)
अणु
	काष्ठा nvkm_nvdec *nvdec = nvkm_nvdec(engine);
	nvkm_falcon_dtor(&nvdec->falcon);
	वापस nvdec;
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
nvkm_nvdec = अणु
	.dtor = nvkm_nvdec_dtor,
पूर्ण;

पूर्णांक
nvkm_nvdec_new_(स्थिर काष्ठा nvkm_nvdec_fwअगर *fwअगर, काष्ठा nvkm_device *device,
		क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_nvdec **pnvdec)
अणु
	काष्ठा nvkm_nvdec *nvdec;
	पूर्णांक ret;

	अगर (!(nvdec = *pnvdec = kzalloc(माप(*nvdec), GFP_KERNEL)))
		वापस -ENOMEM;

	ret = nvkm_engine_ctor(&nvkm_nvdec, device, type, inst, true,
			       &nvdec->engine);
	अगर (ret)
		वापस ret;

	fwअगर = nvkm_firmware_load(&nvdec->engine.subdev, fwअगर, "Nvdec", nvdec);
	अगर (IS_ERR(fwअगर))
		वापस -ENODEV;

	nvdec->func = fwअगर->func;

	वापस nvkm_falcon_ctor(nvdec->func->flcn, &nvdec->engine.subdev,
				nvdec->engine.subdev.name, 0, &nvdec->falcon);
पूर्ण;
