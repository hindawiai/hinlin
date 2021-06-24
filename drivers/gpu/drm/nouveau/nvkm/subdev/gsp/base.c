<शैली गुरु>
/*
 * Copyright 2019 Red Hat Inc.
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
#समावेश "priv.h"
#समावेश <core/falcon.h>
#समावेश <core/firmware.h>
#समावेश <subdev/acr.h>
#समावेश <subdev/top.h>

अटल व्योम *
nvkm_gsp_dtor(काष्ठा nvkm_subdev *subdev)
अणु
	काष्ठा nvkm_gsp *gsp = nvkm_gsp(subdev);
	nvkm_falcon_dtor(&gsp->falcon);
	वापस gsp;
पूर्ण

अटल स्थिर काष्ठा nvkm_subdev_func
nvkm_gsp = अणु
	.dtor = nvkm_gsp_dtor,
पूर्ण;

पूर्णांक
nvkm_gsp_new_(स्थिर काष्ठा nvkm_gsp_fwअगर *fwअगर, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gsp **pgsp)
अणु
	काष्ठा nvkm_gsp *gsp;

	अगर (!(gsp = *pgsp = kzalloc(माप(*gsp), GFP_KERNEL)))
		वापस -ENOMEM;

	nvkm_subdev_ctor(&nvkm_gsp, device, type, inst, &gsp->subdev);

	fwअगर = nvkm_firmware_load(&gsp->subdev, fwअगर, "Gsp", gsp);
	अगर (IS_ERR(fwअगर))
		वापस PTR_ERR(fwअगर);

	वापस nvkm_falcon_ctor(fwअगर->flcn, &gsp->subdev, gsp->subdev.name, 0, &gsp->falcon);
पूर्ण
