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

अटल पूर्णांक
gk104_top_oneinit(काष्ठा nvkm_top *top)
अणु
	काष्ठा nvkm_subdev *subdev = &top->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_top_device *info = शून्य;
	u32 data, type, inst;
	पूर्णांक i;

	क्रम (i = 0; i < 64; i++) अणु
		अगर (!info) अणु
			अगर (!(info = nvkm_top_device_new(top)))
				वापस -ENOMEM;
			type = ~0;
			inst = 0;
		पूर्ण

		data = nvkm_rd32(device, 0x022700 + (i * 0x04));
		nvkm_trace(subdev, "%02x: %08x\n", i, data);
		चयन (data & 0x00000003) अणु
		हाल 0x00000000: /* NOT_VALID */
			जारी;
		हाल 0x00000001: /* DATA */
			inst        = (data & 0x3c000000) >> 26;
			info->addr  = (data & 0x00fff000);
			अगर (data & 0x00000004)
				info->fault = (data & 0x000003f8) >> 3;
			अवरोध;
		हाल 0x00000002: /* ENUM */
			अगर (data & 0x00000020)
				info->engine  = (data & 0x3c000000) >> 26;
			अगर (data & 0x00000010)
				info->runlist = (data & 0x01e00000) >> 21;
			अगर (data & 0x00000008)
				info->पूर्णांकr    = (data & 0x000f8000) >> 15;
			अगर (data & 0x00000004)
				info->reset   = (data & 0x00003e00) >> 9;
			अवरोध;
		हाल 0x00000003: /* ENGINE_TYPE */
			type = (data & 0x7ffffffc) >> 2;
			अवरोध;
		पूर्ण

		अगर (data & 0x80000000)
			जारी;

		/* Translate engine type to NVKM engine identअगरier. */
#घोषणा I_(T,I) करो अणु info->type = (T); info->inst = (I); पूर्ण जबतक(0)
#घोषणा O_(T,I) करो अणु WARN_ON(inst); I_(T, I); पूर्ण जबतक (0)
		चयन (type) अणु
		हाल 0x00000000: O_(NVKM_ENGINE_GR    ,    0); अवरोध;
		हाल 0x00000001: O_(NVKM_ENGINE_CE    ,    0); अवरोध;
		हाल 0x00000002: O_(NVKM_ENGINE_CE    ,    1); अवरोध;
		हाल 0x00000003: O_(NVKM_ENGINE_CE    ,    2); अवरोध;
		हाल 0x00000008: O_(NVKM_ENGINE_MSPDEC,    0); अवरोध;
		हाल 0x00000009: O_(NVKM_ENGINE_MSPPP ,    0); अवरोध;
		हाल 0x0000000a: O_(NVKM_ENGINE_MSVLD ,    0); अवरोध;
		हाल 0x0000000b: O_(NVKM_ENGINE_MSENC ,    0); अवरोध;
		हाल 0x0000000c: O_(NVKM_ENGINE_VIC   ,    0); अवरोध;
		हाल 0x0000000d: O_(NVKM_ENGINE_SEC2  ,    0); अवरोध;
		हाल 0x0000000e: I_(NVKM_ENGINE_NVENC , inst); अवरोध;
		हाल 0x0000000f: O_(NVKM_ENGINE_NVENC ,    1); अवरोध;
		हाल 0x00000010: I_(NVKM_ENGINE_NVDEC , inst); अवरोध;
		हाल 0x00000012: I_(NVKM_SUBDEV_IOCTRL, inst); अवरोध;
		हाल 0x00000013: I_(NVKM_ENGINE_CE    , inst); अवरोध;
		हाल 0x00000014: O_(NVKM_SUBDEV_GSP   ,    0); अवरोध;
		हाल 0x00000015: O_(NVKM_ENGINE_NVJPG ,    0); अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		nvkm_debug(subdev, "%02x.%d (%8s): addr %06x fault %2d "
				   "engine %2d runlist %2d intr %2d "
				   "reset %2d\n", type, inst,
			   info->type == NVKM_SUBDEV_NR ? "????????" : nvkm_subdev_type[info->type],
			   info->addr, info->fault, info->engine, info->runlist,
			   info->पूर्णांकr, info->reset);
		info = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_top_func
gk104_top = अणु
	.oneinit = gk104_top_oneinit,
पूर्ण;

पूर्णांक
gk104_top_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_top **ptop)
अणु
	वापस nvkm_top_new_(&gk104_top, device, type, inst, ptop);
पूर्ण
