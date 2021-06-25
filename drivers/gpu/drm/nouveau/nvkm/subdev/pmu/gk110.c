<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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
#घोषणा gf119_pmu_code gk110_pmu_code
#घोषणा gf119_pmu_data gk110_pmu_data
#समावेश "priv.h"
#समावेश "fuc/gf119.fuc4.h"

#समावेश <subdev/समयr.h>

व्योम
gk110_pmu_pgob(काष्ठा nvkm_pmu *pmu, bool enable)
अणु
	काष्ठा nvkm_device *device = pmu->subdev.device;
	अटल स्थिर काष्ठा अणु
		u32 addr;
		u32 data;
	पूर्ण magic[] = अणु
		अणु 0x020520, 0xfffffffc पूर्ण,
		अणु 0x020524, 0xfffffffe पूर्ण,
		अणु 0x020524, 0xfffffffc पूर्ण,
		अणु 0x020524, 0xfffffff8 पूर्ण,
		अणु 0x020524, 0xffffffe0 पूर्ण,
		अणु 0x020530, 0xfffffffe पूर्ण,
		अणु 0x02052c, 0xfffffffa पूर्ण,
		अणु 0x02052c, 0xfffffff0 पूर्ण,
		अणु 0x02052c, 0xffffffc0 पूर्ण,
		अणु 0x02052c, 0xffffff00 पूर्ण,
		अणु 0x02052c, 0xfffffc00 पूर्ण,
		अणु 0x02052c, 0xfffcfc00 पूर्ण,
		अणु 0x02052c, 0xfff0fc00 पूर्ण,
		अणु 0x02052c, 0xff80fc00 पूर्ण,
		अणु 0x020528, 0xfffffffe पूर्ण,
		अणु 0x020528, 0xfffffffc पूर्ण,
	पूर्ण;
	पूर्णांक i;

	nvkm_mask(device, 0x000200, 0x00001000, 0x00000000);
	nvkm_rd32(device, 0x000200);
	nvkm_mask(device, 0x000200, 0x08000000, 0x08000000);
	msleep(50);

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000002);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x0206b4, 0x00000000, 0x00000000);
	क्रम (i = 0; i < ARRAY_SIZE(magic); i++) अणु
		nvkm_wr32(device, magic[i].addr, magic[i].data);
		nvkm_msec(device, 2000,
			अगर (!(nvkm_rd32(device, magic[i].addr) & 0x80000000))
				अवरोध;
		);
	पूर्ण

	nvkm_mask(device, 0x10a78c, 0x00000002, 0x00000000);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000001);
	nvkm_mask(device, 0x10a78c, 0x00000001, 0x00000000);

	nvkm_mask(device, 0x000200, 0x08000000, 0x00000000);
	nvkm_mask(device, 0x000200, 0x00001000, 0x00001000);
	nvkm_rd32(device, 0x000200);
पूर्ण

अटल स्थिर काष्ठा nvkm_pmu_func
gk110_pmu = अणु
	.flcn = &gt215_pmu_flcn,
	.code.data = gk110_pmu_code,
	.code.size = माप(gk110_pmu_code),
	.data.data = gk110_pmu_data,
	.data.size = माप(gk110_pmu_data),
	.enabled = gf100_pmu_enabled,
	.reset = gf100_pmu_reset,
	.init = gt215_pmu_init,
	.fini = gt215_pmu_fini,
	.पूर्णांकr = gt215_pmu_पूर्णांकr,
	.send = gt215_pmu_send,
	.recv = gt215_pmu_recv,
	.pgob = gk110_pmu_pgob,
पूर्ण;

अटल स्थिर काष्ठा nvkm_pmu_fwअगर
gk110_pmu_fwअगर[] = अणु
	अणु -1, gf100_pmu_nofw, &gk110_pmu पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gk110_pmu_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_pmu **ppmu)
अणु
	वापस nvkm_pmu_new_(gk110_pmu_fwअगर, device, type, inst, ppmu);
पूर्ण
