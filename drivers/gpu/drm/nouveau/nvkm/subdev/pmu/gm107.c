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
#घोषणा gk208_pmu_code gm107_pmu_code
#घोषणा gk208_pmu_data gm107_pmu_data
#समावेश "fuc/gk208.fuc5.h"

अटल स्थिर काष्ठा nvkm_pmu_func
gm107_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.code.data = gm107_pmu_code,
	.code.size = माप(gm107_pmu_code),
	.data.data = gm107_pmu_data,
	.data.size = माप(gm107_pmu_data),
	.enabled = gf100_pmu_enabled,
	.reset = gf100_pmu_reset,
	.init = gt215_pmu_init,
	.fini = gt215_pmu_fini,
	.पूर्णांकr = gt215_pmu_पूर्णांकr,
	.send = gt215_pmu_send,
	.recv = gt215_pmu_recv,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gm107_pmu_fwअगर[] = अणु
	अणु -1, gf100_pmu_nofw, &gm107_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm107_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gm107_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
