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
#घोषणा gf119_pmu_code gk104_pmu_code
#घोषणा gf119_pmu_data gk104_pmu_data
#समावेश "priv.h"
#समावेश "fuc/gf119.fuc4.h"

#समावेश <core/option.h>
#समावेश <subdev/fuse.h>
#समावेश <subdev/समयr.h>

अटल व्योम
magic_(काष्ठा nvkm_device *device, u32 ctrl, पूर्णांक size)
अणु
	nvkm_wr32(device, 0x00c800, 0x00000000);
	nvkm_wr32(device, 0x00c808, 0x00000000);
	nvkm_wr32(device, 0x00c800, ctrl);
	nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x00c800) & 0x40000000) अणु
			जबतक (size--)
				nvkm_wr32(device, 0x00c804, 0x00000000);
			अवरोध;
		पूर्ण
	);
	nvkm_wr32(device, 0x00c800, 0x00000000);
पूर्ण

अटल व्योम
magic(काष्ठा nvkm_device *device, u32 ctrl)
अणु
	magic_(device, 0x8000a41f | ctrl, 6);
	magic_(device, 0x80000421 | ctrl, 1);
पूर्ण

अटल व्योम
gk104_pmu_pgob(काष्ठा nvkm_pmu *pmu, bool enable)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;

	अगर (!(nvkm_fuse_पढ़ो(device->fuse, 0x31c) & 0x00000001))
		वापस;

	nvkm_mask(device, 0x000200, 0x00001000, 0x00000000);
	nvkm_rd32(device, 0x000200);
	nvkm_mask(device, 0x000200, 0x08000000, 0x08000000);
	msleep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000002);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x020004, 0xc0000000, enable ? 0xc0000000 : 0x40000000);
	msleep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000000);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x000200, 0x08000000, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00001000, 0x00001000);
	nvkm_rd32(device, 0x000200);

	अगर (nvkm_boolopt(device->cfgopt, "War00C800_0", true)) अणु
		चयन (device->chipset) अणु
		हाल 0xe4:
			magic(device, 0x04000000);
			magic(device, 0x06000000);
			magic(device, 0x0c000000);
			magic(device, 0x0e000000);
			अवरोध;
		हाल 0xe6:
			magic(device, 0x02000000);
			magic(device, 0x04000000);
			magic(device, 0x0a000000);
			अवरोध;
		हाल 0xe7:
			magic(device, 0x02000000);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_pmu_func
gk104_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.code.data = gk104_pmu_code,
	.code.size = माप(gk104_pmu_code),
	.data.data = gk104_pmu_data,
	.data.size = माप(gk104_pmu_data),
	.enabled = gf100_pmu_enabled,
	.reset = gf100_pmu_reset,
	.init = gt215_pmu_init,
	.fini = gt215_pmu_fini,
	.पूर्णांकr = gt215_pmu_पूर्णांकr,
	.send = gt215_pmu_send,
	.recv = gt215_pmu_recv,
	.pgob = gk104_pmu_pgob,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gk104_pmu_fwअगर[] = अणु
	अणु -1, gf100_pmu_nofw, &gk104_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gk104_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gk104_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
