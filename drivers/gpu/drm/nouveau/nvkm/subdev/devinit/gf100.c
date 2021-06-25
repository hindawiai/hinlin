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
#समावेश "nv50.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/clk/pll.h>

पूर्णांक
gf100_devinit_pll_set(काष्ठा nvkm_devinit *init, u32 type, u32 freq)
अणु
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvbios_pll info;
	पूर्णांक N, fN, M, P;
	पूर्णांक ret;

	ret = nvbios_pll_parse(device->bios, type, &info);
	अगर (ret)
		वापस ret;

	ret = gt215_pll_calc(subdev, &info, freq, &N, &fN, &M, &P);
	अगर (ret < 0)
		वापस ret;

	चयन (info.type) अणु
	हाल PLL_VPLL0:
	हाल PLL_VPLL1:
	हाल PLL_VPLL2:
	हाल PLL_VPLL3:
		nvkm_mask(device, info.reg + 0x0c, 0x00000000, 0x00000100);
		nvkm_wr32(device, info.reg + 0x04, (P << 16) | (N << 8) | M);
		nvkm_wr32(device, info.reg + 0x10, fN << 16);
		अवरोध;
	शेष:
		nvkm_warn(subdev, "%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u64
gf100_devinit_disable(काष्ठा nvkm_devinit *init)
अणु
	काष्ठा nvkm_device *device = init->subdev.device;
	u32 r022500 = nvkm_rd32(device, 0x022500);
	u64 disable = 0ULL;

	अगर (r022500 & 0x00000001)
		nvkm_subdev_disable(device, NVKM_ENGINE_DISP, 0);

	अगर (r022500 & 0x00000002) अणु
		nvkm_subdev_disable(device, NVKM_ENGINE_MSPDEC, 0);
		nvkm_subdev_disable(device, NVKM_ENGINE_MSPPP, 0);
	पूर्ण

	अगर (r022500 & 0x00000004)
		nvkm_subdev_disable(device, NVKM_ENGINE_MSVLD, 0);
	अगर (r022500 & 0x00000008)
		nvkm_subdev_disable(device, NVKM_ENGINE_MSENC, 0);
	अगर (r022500 & 0x00000100)
		nvkm_subdev_disable(device, NVKM_ENGINE_CE, 0);
	अगर (r022500 & 0x00000200)
		nvkm_subdev_disable(device, NVKM_ENGINE_CE, 1);

	वापस disable;
पूर्ण

व्योम
gf100_devinit_preinit(काष्ठा nvkm_devinit *base)
अणु
	काष्ठा nv50_devinit *init = nv50_devinit(base);
	काष्ठा nvkm_subdev *subdev = &init->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;

	/*
	 * This bit is set by devinit, and flips back to 0 on suspend. We
	 * can use it as a reliable way to know whether we should run devinit.
	 */
	base->post = ((nvkm_rd32(device, 0x2240c) & BIT(1)) == 0);
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
gf100_devinit = अणु
	.preinit = gf100_devinit_preinit,
	.init = nv50_devinit_init,
	.post = nv04_devinit_post,
	.pll_set = gf100_devinit_pll_set,
	.disable = gf100_devinit_disable,
पूर्ण;

पूर्णांक
gf100_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		  काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv50_devinit_new_(&gf100_devinit, device, type, inst, pinit);
पूर्ण
