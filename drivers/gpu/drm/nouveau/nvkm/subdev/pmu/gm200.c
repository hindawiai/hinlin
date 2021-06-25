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

अटल स्थिर काष्ठा nvkm_pmu_func
gm200_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.enabled = gf100_pmu_enabled,
	.reset = gf100_pmu_reset,
पूर्ण;


पूर्णांक
gm200_pmu_nofw(काष्ठा nvkm_pmu *pmu, पूर्णांक ver, स्थिर काष्ठा nvkm_pmu_fwअगर *fwअगर)
अणु
	nvkm_warn(&pmu->subdev, "firmware unavailable\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gm200_pmu_fwअगर[] = अणु
	अणु -1, gm200_pmu_nofw, &gm200_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm200_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gm200_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
