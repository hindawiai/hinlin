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
#समावेश <core/क्रमागत.h>

#समावेश <nvअगर/class.h>

अटल स्थिर काष्ठा nvkm_क्रमागत
gk104_ce_launcherr_report[] = अणु
	अणु 0x0, "NO_ERR" पूर्ण,
	अणु 0x1, "2D_LAYER_EXCEEDS_DEPTH" पूर्ण,
	अणु 0x2, "INVALID_ARGUMENT" पूर्ण,
	अणु 0x3, "MEM2MEM_RECT_OUT_OF_BOUNDS" पूर्ण,
	अणु 0x4, "SRC_LINE_EXCEEDS_PITCH" पूर्ण,
	अणु 0x5, "SRC_LINE_EXCEEDS_NEG_PITCH" पूर्ण,
	अणु 0x6, "DST_LINE_EXCEEDS_PITCH" पूर्ण,
	अणु 0x7, "DST_LINE_EXCEEDS_NEG_PITCH" पूर्ण,
	अणु 0x8, "BAD_SRC_PIXEL_COMP_REF" पूर्ण,
	अणु 0x9, "INVALID_VALUE" पूर्ण,
	अणु 0xa, "UNUSED_FIELD" पूर्ण,
	अणु 0xb, "INVALID_OPERATION" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
gk104_ce_पूर्णांकr_launcherr(काष्ठा nvkm_engine *ce, स्थिर u32 base)
अणु
	काष्ठा nvkm_subdev *subdev = &ce->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, 0x104f14 + base);
	स्थिर काष्ठा nvkm_क्रमागत *en =
		nvkm_क्रमागत_find(gk104_ce_launcherr_report, stat & 0x0000000f);
	nvkm_warn(subdev, "LAUNCHERR %08x [%s]\n", stat, en ? en->name : "");
	nvkm_wr32(device, 0x104f14 + base, 0x00000000);
पूर्ण

व्योम
gk104_ce_पूर्णांकr(काष्ठा nvkm_engine *ce)
अणु
	काष्ठा nvkm_subdev *subdev = &ce->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर u32 base = subdev->inst * 0x1000;
	u32 mask = nvkm_rd32(device, 0x104904 + base);
	u32 पूर्णांकr = nvkm_rd32(device, 0x104908 + base) & mask;
	अगर (पूर्णांकr & 0x00000001) अणु
		nvkm_warn(subdev, "BLOCKPIPE\n");
		nvkm_wr32(device, 0x104908 + base, 0x00000001);
		पूर्णांकr &= ~0x00000001;
	पूर्ण
	अगर (पूर्णांकr & 0x00000002) अणु
		nvkm_warn(subdev, "NONBLOCKPIPE\n");
		nvkm_wr32(device, 0x104908 + base, 0x00000002);
		पूर्णांकr &= ~0x00000002;
	पूर्ण
	अगर (पूर्णांकr & 0x00000004) अणु
		gk104_ce_पूर्णांकr_launcherr(ce, base);
		nvkm_wr32(device, 0x104908 + base, 0x00000004);
		पूर्णांकr &= ~0x00000004;
	पूर्ण
	अगर (पूर्णांकr) अणु
		nvkm_warn(subdev, "intr %08x\n", पूर्णांकr);
		nvkm_wr32(device, 0x104908 + base, पूर्णांकr);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा nvkm_engine_func
gk104_ce = अणु
	.पूर्णांकr = gk104_ce_पूर्णांकr,
	.sclass = अणु
		अणु -1, -1, KEPLER_DMA_COPY_A पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gk104_ce_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_engine **pengine)
अणु
	वापस nvkm_engine_new_(&gk104_ce, device, type, inst, true, pengine);
पूर्ण
