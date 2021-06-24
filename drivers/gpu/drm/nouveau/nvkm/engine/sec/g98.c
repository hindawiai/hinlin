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
#समावेश <engine/sec.h>
#समावेश <engine/fअगरo.h>
#समावेश "fuc/g98.fuc0s.h"

#समावेश <core/client.h>
#समावेश <core/क्रमागत.h>
#समावेश <core/gpuobj.h>

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nvkm_क्रमागत g98_sec_isr_error_name[] = अणु
	अणु 0x0000, "ILLEGAL_MTHD" पूर्ण,
	अणु 0x0001, "INVALID_BITFIELD" पूर्ण,
	अणु 0x0002, "INVALID_ENUM" पूर्ण,
	अणु 0x0003, "QUERY" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
g98_sec_पूर्णांकr(काष्ठा nvkm_falcon *sec, काष्ठा nvkm_fअगरo_chan *chan)
अणु
	काष्ठा nvkm_subdev *subdev = &sec->engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 ssta = nvkm_rd32(device, 0x087040) & 0x0000ffff;
	u32 addr = nvkm_rd32(device, 0x087040) >> 16;
	u32 mthd = (addr & 0x07ff) << 2;
	u32 subc = (addr & 0x3800) >> 11;
	u32 data = nvkm_rd32(device, 0x087044);
	स्थिर काष्ठा nvkm_क्रमागत *en =
		nvkm_क्रमागत_find(g98_sec_isr_error_name, ssta);

	nvkm_error(subdev, "DISPATCH_ERROR %04x [%s] ch %d [%010llx %s] "
			   "subc %d mthd %04x data %08x\n", ssta,
		   en ? en->name : "UNKNOWN", chan ? chan->chid : -1,
		   chan ? chan->inst->addr : 0,
		   chan ? chan->object.client->name : "unknown",
		   subc, mthd, data);
पूर्ण

अटल स्थिर काष्ठा nvkm_falcon_func
g98_sec = अणु
	.code.data = g98_sec_code,
	.code.size = माप(g98_sec_code),
	.data.data = g98_sec_data,
	.data.size = माप(g98_sec_data),
	.पूर्णांकr = g98_sec_पूर्णांकr,
	.sclass = अणु
		अणु -1, -1, G98_SEC पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
g98_sec_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	    काष्ठा nvkm_engine **pengine)
अणु
	वापस nvkm_falcon_new_(&g98_sec, device, type, inst, true, 0x087000, pengine);
पूर्ण
