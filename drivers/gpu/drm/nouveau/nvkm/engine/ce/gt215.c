<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
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

#समावेश <core/client.h>
#समावेश <core/क्रमागत.h>
#समावेश <core/gpuobj.h>
#समावेश <engine/fअगरo.h>

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nvkm_क्रमागत
gt215_ce_isr_error_name[] = अणु
	अणु 0x0001, "ILLEGAL_MTHD" पूर्ण,
	अणु 0x0002, "INVALID_ENUM" पूर्ण,
	अणु 0x0003, "INVALID_BITFIELD" पूर्ण,
	अणुपूर्ण
पूर्ण;

व्योम
gt215_ce_पूर्णांकr(काष्ठा nvkm_falcon *ce, काष्ठा nvkm_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &ce->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 base = subdev->inst * 0x1000;
	u32 ssta = nvkm_rd32(device, 0x104040 + base) & 0x0000ffff;
	u32 addr = nvkm_rd32(device, 0x104040 + base) >> 16;
	u32 mthd = (addr & 0x07ff) << 2;
	u32 subc = (addr & 0x3800) >> 11;
	u32 data = nvkm_rd32(device, 0x104044 + base);
	स्थिर काष्ठा nvkm_क्रमागत *en =
		nvkm_क्रमागत_find(gt215_ce_isr_error_name, ssta);

	nvkm_error(subdev, "DISPATCH_ERROR %04x [%s] ch %d [%010llx %s] "
			   "subc %d mthd %04x data %08x\n", ssta,
		   en ? en->name : "", chan ? chan->chid : -1,
		   chan ? chan->inst->addr : 0,
		   chan ? chan->object.client->name : "unknown",
		   subc, mthd, data);
पूर्ण

अटल स्थिर काष्ठा nvkm_falcon_func
gt215_ce = अणु
	.code.data = gt215_ce_code,
	.code.size = माप(gt215_ce_code),
	.data.data = gt215_ce_data,
	.data.size = माप(gt215_ce_data),
	.पूर्णांकr = gt215_ce_पूर्णांकr,
	.sclass = अणु
		अणु -1, -1, GT212_DMA पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gt215_ce_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_engine **pengine)
अणु
	वापस nvkm_falcon_new_(&gt215_ce, device, type, inst,
				(device->chipset != 0xaf), 0x104000, pengine);
पूर्ण
