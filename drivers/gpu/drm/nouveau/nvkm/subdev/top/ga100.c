<शैली गुरु>
/*
 * Copyright 2021 Red Hat Inc.
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

अटल पूर्णांक
ga100_top_oneinit(काष्ठा nvkm_top *top)
अणु
	काष्ठा nvkm_subdev *subdev = &top->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvkm_top_device *info = शून्य;
	u32 data, type, inst;
	पूर्णांक i, n, size = nvkm_rd32(device, 0x0224fc) >> 20;

	क्रम (i = 0, n = 0; i < size; i++) अणु
		अगर (!info) अणु
			अगर (!(info = nvkm_top_device_new(top)))
				वापस -ENOMEM;
			type = ~0;
			inst = 0;
		पूर्ण

		data = nvkm_rd32(device, 0x022800 + (i * 0x04));
		nvkm_trace(subdev, "%02x: %08x\n", i, data);
		अगर (!data && n == 0)
			जारी;

		चयन (n++) अणु
		हाल 0:
			type	      = (data & 0x3f000000) >> 24;
			inst	      = (data & 0x000f0000) >> 16;
			info->fault   = (data & 0x0000007f);
			अवरोध;
		हाल 1:
			info->addr    = (data & 0x00fff000);
			info->reset   = (data & 0x0000001f);
			अवरोध;
		हाल 2:
			info->runlist = (data & 0x0000fc00) >> 10;
			info->engine  = (data & 0x00000003);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		अगर (data & 0x80000000)
			जारी;
		n = 0;

		/* Translate engine type to NVKM engine identअगरier. */
#घोषणा I_(T,I) करो अणु info->type = (T); info->inst = (I); पूर्ण जबतक(0)
#घोषणा O_(T,I) करो अणु WARN_ON(inst); I_(T, I); पूर्ण जबतक (0)
		चयन (type) अणु
		हाल 0x00000000: O_(NVKM_ENGINE_GR    ,    0); अवरोध;
		हाल 0x0000000d: O_(NVKM_ENGINE_SEC2  ,    0); अवरोध;
		हाल 0x0000000e: I_(NVKM_ENGINE_NVENC , inst); अवरोध;
		हाल 0x00000010: I_(NVKM_ENGINE_NVDEC , inst); अवरोध;
		हाल 0x00000012: I_(NVKM_SUBDEV_IOCTRL, inst); अवरोध;
		हाल 0x00000013: I_(NVKM_ENGINE_CE    , inst); अवरोध;
		हाल 0x00000014: O_(NVKM_SUBDEV_GSP   ,    0); अवरोध;
		हाल 0x00000015: O_(NVKM_ENGINE_NVJPG ,    0); अवरोध;
		हाल 0x00000016: O_(NVKM_ENGINE_OFA   ,    0); अवरोध;
		हाल 0x00000017: O_(NVKM_SUBDEV_FLA   ,    0); अवरोध;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		nvkm_debug(subdev, "%02x.%d (%8s): addr %06x fault %2d "
				   "runlist %2d engine %2d reset %2d\n", type, inst,
			   info->type == NVKM_SUBDEV_NR ? "????????" : nvkm_subdev_type[info->type],
			   info->addr, info->fault, info->runlist, info->engine, info->reset);
		info = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_top_func
ga100_top = अणु
	.oneinit = ga100_top_oneinit,
पूर्ण;

पूर्णांक
ga100_top_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_top **ptop)
अणु
	वापस nvkm_top_new_(&ga100_top, device, type, inst, ptop);
पूर्ण
