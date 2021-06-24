<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "nv50.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/clk/pll.h>

अटल पूर्णांक
gv100_devinit_pll_set(काष्ठा nvkm_devinit *init, u32 type, u32 freq)
अणु
	काष्ठा nvkm_subdev *subdev = &init->subdev;
	काष्ठा nvkm_device *device = subdev->device;
	काष्ठा nvbios_pll info;
	पूर्णांक head = type - PLL_VPLL0;
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
		nvkm_wr32(device, 0x00ef10 + (head * 0x40), fN << 16);
		nvkm_wr32(device, 0x00ef04 + (head * 0x40), (P << 16) |
							    (N <<  8) |
							    (M <<  0));
		अवरोध;
	शेष:
		nvkm_warn(subdev, "%08x/%dKhz unimplemented\n", type, freq);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा nvkm_devinit_func
gv100_devinit = अणु
	.preinit = gf100_devinit_preinit,
	.init = nv50_devinit_init,
	.post = gm200_devinit_post,
	.pll_set = gv100_devinit_pll_set,
	.disable = gm107_devinit_disable,
पूर्ण;

पूर्णांक
gv100_devinit_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
		  काष्ठा nvkm_devinit **pinit)
अणु
	वापस nv50_devinit_new_(&gv100_devinit, device, type, inst, pinit);
पूर्ण
