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

अटल स्थिर काष्ठा nvkm_mc_map
gf100_mc_reset[] = अणु
	अणु 0x00020000, NVKM_ENGINE_MSPDEC पूर्ण,
	अणु 0x00008000, NVKM_ENGINE_MSVLD पूर्ण,
	अणु 0x00002000, NVKM_SUBDEV_PMU, 0, true पूर्ण,
	अणु 0x00001000, NVKM_ENGINE_GR पूर्ण,
	अणु 0x00000100, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x00000080, NVKM_ENGINE_CE, 1 पूर्ण,
	अणु 0x00000040, NVKM_ENGINE_CE, 0 पूर्ण,
	अणु 0x00000002, NVKM_ENGINE_MSPPP पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_mc_map
gf100_mc_पूर्णांकr[] = अणु
	अणु 0x04000000, NVKM_ENGINE_DISP पूर्ण,
	अणु 0x00020000, NVKM_ENGINE_MSPDEC पूर्ण,
	अणु 0x00008000, NVKM_ENGINE_MSVLD पूर्ण,
	अणु 0x00001000, NVKM_ENGINE_GR पूर्ण,
	अणु 0x00000100, NVKM_ENGINE_FIFO पूर्ण,
	अणु 0x00000040, NVKM_ENGINE_CE, 1 पूर्ण,
	अणु 0x00000020, NVKM_ENGINE_CE, 0 पूर्ण,
	अणु 0x00000001, NVKM_ENGINE_MSPPP पूर्ण,
	अणु 0x40000000, NVKM_SUBDEV_PRIVRING पूर्ण,
	अणु 0x10000000, NVKM_SUBDEV_BUS पूर्ण,
	अणु 0x08000000, NVKM_SUBDEV_FB पूर्ण,
	अणु 0x02000000, NVKM_SUBDEV_LTC पूर्ण,
	अणु 0x01000000, NVKM_SUBDEV_PMU पूर्ण,
	अणु 0x00200000, NVKM_SUBDEV_GPIO पूर्ण,
	अणु 0x00200000, NVKM_SUBDEV_I2C पूर्ण,
	अणु 0x00100000, NVKM_SUBDEV_TIMER पूर्ण,
	अणु 0x00040000, NVKM_SUBDEV_THERM पूर्ण,
	अणु 0x00002000, NVKM_SUBDEV_FB पूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम
gf100_mc_पूर्णांकr_unarm(काष्ठा nvkm_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->subdev.device;
	nvkm_wr32(device, 0x000140, 0x00000000);
	nvkm_wr32(device, 0x000144, 0x00000000);
	nvkm_rd32(device, 0x000140);
पूर्ण

व्योम
gf100_mc_पूर्णांकr_rearm(काष्ठा nvkm_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->subdev.device;
	nvkm_wr32(device, 0x000140, 0x00000001);
	nvkm_wr32(device, 0x000144, 0x00000001);
पूर्ण

u32
gf100_mc_पूर्णांकr_stat(काष्ठा nvkm_mc *mc)
अणु
	काष्ठा nvkm_device *device = mc->subdev.device;
	u32 पूर्णांकr0 = nvkm_rd32(device, 0x000100);
	u32 पूर्णांकr1 = nvkm_rd32(device, 0x000104);
	वापस पूर्णांकr0 | पूर्णांकr1;
पूर्ण

व्योम
gf100_mc_पूर्णांकr_mask(काष्ठा nvkm_mc *mc, u32 mask, u32 stat)
अणु
	काष्ठा nvkm_device *device = mc->subdev.device;
	nvkm_mask(device, 0x000640, mask, stat);
	nvkm_mask(device, 0x000644, mask, stat);
पूर्ण

व्योम
gf100_mc_unk260(काष्ठा nvkm_mc *mc, u32 data)
अणु
	nvkm_wr32(mc->subdev.device, 0x000260, data);
पूर्ण

अटल स्थिर काष्ठा nvkm_mc_func
gf100_mc = अणु
	.init = nv50_mc_init,
	.पूर्णांकr = gf100_mc_पूर्णांकr,
	.पूर्णांकr_unarm = gf100_mc_पूर्णांकr_unarm,
	.पूर्णांकr_rearm = gf100_mc_पूर्णांकr_rearm,
	.पूर्णांकr_mask = gf100_mc_पूर्णांकr_mask,
	.पूर्णांकr_stat = gf100_mc_पूर्णांकr_stat,
	.reset = gf100_mc_reset,
	.unk260 = gf100_mc_unk260,
पूर्ण;

पूर्णांक
gf100_mc_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_mc **pmc)
अणु
	वापस nvkm_mc_new_(&gf100_mc, device, type, inst, pmc);
पूर्ण
