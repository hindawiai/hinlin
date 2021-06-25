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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "priv.h"

अटल व्योम
gp102_pmu_reset(काष्ठा nvkm_pmu *pmu)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;
	nvkm_mask(device, 0x10a3c0, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a3c0, 0x00000001, 0x00000000);
पूर्ण

अटल bool
gp102_pmu_enabled(काष्ठा nvkm_pmu *pmu)
अणु
	वापस !(nvkm_rd32(pmu->subdev.device, 0x10a3c0) & 0x00000001);
पूर्ण

अटल स्थिर काष्ठा nvkm_pmu_func
gp102_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.enabled = gp102_pmu_enabled,
	.reset = gp102_pmu_reset,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gp102_pmu_fwअगर[] = अणु
	अणु -1, gm200_pmu_nofw, &gp102_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp102_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gp102_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
