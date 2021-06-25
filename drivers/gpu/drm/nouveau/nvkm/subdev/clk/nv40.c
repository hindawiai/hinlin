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
#घोषणा nv40_clk(p) container_of((p), काष्ठा nv40_clk, base)
#समावेश "priv.h"
#समावेश "pll.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>

काष्ठा nv40_clk अणु
	काष्ठा nvkm_clk base;
	u32 ctrl;
	u32 npll_ctrl;
	u32 npll_coef;
	u32 spll;
पूर्ण;

अटल u32
पढ़ो_pll_1(काष्ठा nv40_clk *clk, u32 reg)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 ctrl = nvkm_rd32(device, reg + 0x00);
	पूर्णांक P = (ctrl & 0x00070000) >> 16;
	पूर्णांक N = (ctrl & 0x0000ff00) >> 8;
	पूर्णांक M = (ctrl & 0x000000ff) >> 0;
	u32 ref = 27000, khz = 0;

	अगर (ctrl & 0x80000000)
		khz = ref * N / M;

	वापस khz >> P;
पूर्ण

अटल u32
पढ़ो_pll_2(काष्ठा nv40_clk *clk, u32 reg)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 ctrl = nvkm_rd32(device, reg + 0x00);
	u32 coef = nvkm_rd32(device, reg + 0x04);
	पूर्णांक N2 = (coef & 0xff000000) >> 24;
	पूर्णांक M2 = (coef & 0x00ff0000) >> 16;
	पूर्णांक N1 = (coef & 0x0000ff00) >> 8;
	पूर्णांक M1 = (coef & 0x000000ff) >> 0;
	पूर्णांक P = (ctrl & 0x00070000) >> 16;
	u32 ref = 27000, khz = 0;

	अगर ((ctrl & 0x80000000) && M1) अणु
		khz = ref * N1 / M1;
		अगर ((ctrl & 0x40000100) == 0x40000000) अणु
			अगर (M2)
				khz = khz * N2 / M2;
			अन्यथा
				khz = 0;
		पूर्ण
	पूर्ण

	वापस khz >> P;
पूर्ण

अटल u32
पढ़ो_clk(काष्ठा nv40_clk *clk, u32 src)
अणु
	चयन (src) अणु
	हाल 3:
		वापस पढ़ो_pll_2(clk, 0x004000);
	हाल 2:
		वापस पढ़ो_pll_1(clk, 0x004008);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv40_clk_पढ़ो(काष्ठा nvkm_clk *base, क्रमागत nv_clk_src src)
अणु
	काष्ठा nv40_clk *clk = nv40_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mast = nvkm_rd32(device, 0x00c040);

	चयन (src) अणु
	हाल nv_clk_src_crystal:
		वापस device->crystal;
	हाल nv_clk_src_href:
		वापस 100000; /*XXX: PCIE/AGP dअगरfer*/
	हाल nv_clk_src_core:
		वापस पढ़ो_clk(clk, (mast & 0x00000003) >> 0);
	हाल nv_clk_src_shader:
		वापस पढ़ो_clk(clk, (mast & 0x00000030) >> 4);
	हाल nv_clk_src_mem:
		वापस पढ़ो_pll_2(clk, 0x4020);
	शेष:
		अवरोध;
	पूर्ण

	nvkm_debug(subdev, "unknown clock source %d %08x\n", src, mast);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
nv40_clk_calc_pll(काष्ठा nv40_clk *clk, u32 reg, u32 khz,
		  पूर्णांक *N1, पूर्णांक *M1, पूर्णांक *N2, पूर्णांक *M2, पूर्णांक *log2P)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvbios_pll pll;
	पूर्णांक ret;

	ret = nvbios_pll_parse(subdev->device->bios, reg, &pll);
	अगर (ret)
		वापस ret;

	अगर (khz < pll.vco1.max_freq)
		pll.vco2.max_freq = 0;

	ret = nv04_pll_calc(subdev, &pll, khz, N1, M1, N2, M2, log2P);
	अगर (ret == 0)
		वापस -दुस्फल;

	वापस ret;
पूर्ण

अटल पूर्णांक
nv40_clk_calc(काष्ठा nvkm_clk *base, काष्ठा nvkm_cstate *cstate)
अणु
	काष्ठा nv40_clk *clk = nv40_clk(base);
	पूर्णांक gclk = cstate->करोमुख्य[nv_clk_src_core];
	पूर्णांक sclk = cstate->करोमुख्य[nv_clk_src_shader];
	पूर्णांक N1, M1, N2, M2, log2P;
	पूर्णांक ret;

	/* core/geometric घड़ी */
	ret = nv40_clk_calc_pll(clk, 0x004000, gclk,
				&N1, &M1, &N2, &M2, &log2P);
	अगर (ret < 0)
		वापस ret;

	अगर (N2 == M2) अणु
		clk->npll_ctrl = 0x80000100 | (log2P << 16);
		clk->npll_coef = (N1 << 8) | M1;
	पूर्ण अन्यथा अणु
		clk->npll_ctrl = 0xc0000000 | (log2P << 16);
		clk->npll_coef = (N2 << 24) | (M2 << 16) | (N1 << 8) | M1;
	पूर्ण

	/* use the second pll क्रम shader/rop घड़ी, अगर it dअगरfers from core */
	अगर (sclk && sclk != gclk) अणु
		ret = nv40_clk_calc_pll(clk, 0x004008, sclk,
					&N1, &M1, शून्य, शून्य, &log2P);
		अगर (ret < 0)
			वापस ret;

		clk->spll = 0xc0000000 | (log2P << 16) | (N1 << 8) | M1;
		clk->ctrl = 0x00000223;
	पूर्ण अन्यथा अणु
		clk->spll = 0x00000000;
		clk->ctrl = 0x00000333;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nv40_clk_prog(काष्ठा nvkm_clk *base)
अणु
	काष्ठा nv40_clk *clk = nv40_clk(base);
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	nvkm_mask(device, 0x00c040, 0x00000333, 0x00000000);
	nvkm_wr32(device, 0x004004, clk->npll_coef);
	nvkm_mask(device, 0x004000, 0xc0070100, clk->npll_ctrl);
	nvkm_mask(device, 0x004008, 0xc007ffff, clk->spll);
	mdelay(5);
	nvkm_mask(device, 0x00c040, 0x00000333, clk->ctrl);
	वापस 0;
पूर्ण

अटल व्योम
nv40_clk_tidy(काष्ठा nvkm_clk *obj)
अणु
पूर्ण

अटल स्थिर काष्ठा nvkm_clk_func
nv40_clk = अणु
	.पढ़ो = nv40_clk_पढ़ो,
	.calc = nv40_clk_calc,
	.prog = nv40_clk_prog,
	.tidy = nv40_clk_tidy,
	.करोमुख्यs = अणु
		अणु nv_clk_src_crystal, 0xff पूर्ण,
		अणु nv_clk_src_href   , 0xff पूर्ण,
		अणु nv_clk_src_core   , 0xff, 0, "core", 1000 पूर्ण,
		अणु nv_clk_src_shader , 0xff, 0, "shader", 1000 पूर्ण,
		अणु nv_clk_src_mem    , 0xff, 0, "memory", 1000 पूर्ण,
		अणु nv_clk_src_max पूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
nv40_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_clk **pclk)
अणु
	काष्ठा nv40_clk *clk;

	अगर (!(clk = kzalloc(माप(*clk), GFP_KERNEL)))
		वापस -ENOMEM;
	clk->base.pll_calc = nv04_clk_pll_calc;
	clk->base.pll_prog = nv04_clk_pll_prog;
	*pclk = &clk->base;

	वापस nvkm_clk_ctor(&nv40_clk, device, type, inst, true, &clk->base);
पूर्ण
