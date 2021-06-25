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
 * Authors: Ben Skeggs
 */
#समावेश "priv.h"

अटल स्थिर काष्ठा nvkm_mc_map
gt215_mc_reset[] = अणु
	अणु 0x04008000, NVKM_ENGINE_MSVLD पूर्ण,
	अणु 0x01020000, NVKM_ENGINE_MSPDEC पूर्ण,
	अणु 0x00802000, NVKM_ENGINE_CE, 0 पूर्ण,
	अणु 0x00400002, NVKM_ENGINE_MSPPP पूर्ण,
	अणु 0x00201000, NVKM_ENGINE_GR पूर्ण,
	अणु 0x00000100, NVKM_ENGINE_FIFO पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_mc_map
gt215_mc_पूर्णांकr[] = अणु
	अणु 0x04000000, NVKM_ENGINE_DISP पूर्ण,
	अणु 0x00400000, NVKM_ENGINE_CE, 0 पूर्ण,
	अणु 0x00020000, NVKM_ENGINE_MSPDEC पूर्ण,
	अणु 0x00008000, NVKM_ENGINE_MSVLD पूर्ण,
	अणु 0x00001000, NVKM_ENGINE_GR पूर्ण,
	अणु 0x00000100, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x00000001, NVKM_ENGINE_MSPPP पूर्ण,
	अणु 0x00429101, NVKM_SUBDEV_FB पूर्ण,
	अणु 0x10000000, NVKM_SUBDEV_BUS पूर्ण,
	अणु 0x00200000, NVKM_SUBDEV_GPIO पूर्ण,
	अणु 0x00200000, NVKM_SUBDEV_I2C पूर्ण,
	अणु 0x00100000, NVKM_SUBDEV_TIMER पूर्ण,
	अणु 0x00080000, NVKM_SUBDEV_THERM पूर्ण,
	अणु 0x00040000, NVKM_SUBDEV_PMU पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम
gt215_mc_पूर्णांकr_mask(काष्ठा nvkm_mc *mc, u32 mask, u32 stat)
अणु
	nvkm_mask(mc->subdev.device, 0x000640, mask, stat);
पूर्ण

अटल स्थिर काष्ठा nvkm_mc_func
gt215_mc = अणु
	.init = nv50_mc_init,
	.पूर्णांकr = gt215_mc_पूर्णांकr,
	.पूर्णांकr_unarm = nv04_mc_पूर्णांकr_unarm,
	.पूर्णांकr_rearm = nv04_mc_पूर्णांकr_rearm,
	.पूर्णांकr_mask = gt215_mc_पूर्णांकr_mask,
	.पूर्णांकr_stat = nv04_mc_पूर्णांकr_stat,
	.reset = gt215_mc_reset,
पूर्ण;

पूर्णांक
gt215_mc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	वापस nvkm_mc_new_(&gt215_mc, device, type, inst, pmc);
पूर्ण
