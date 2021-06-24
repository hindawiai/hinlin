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
#घोषणा mcp77_clk(p) container_of((p), काष्ठा mcp77_clk, base)
#समावेश "gt215.h"
#समावेश "pll.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/समयr.h>

काष्ठा mcp77_clk अणु
	काष्ठा nvkm_clk base;
	क्रमागत nv_clk_src csrc, ssrc, vsrc;
	u32 cctrl, sctrl;
	u32 ccoef, scoef;
	u32 cpost, spost;
	u32 vभाग;
पूर्ण;

अटल u32
पढ़ो_भाग(काष्ठा mcp77_clk *clk)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	वापस nvkm_rd32(device, 0x004600);
पूर्ण

अटल u32
पढ़ो_pll(काष्ठा mcp77_clk *clk, u32 base)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 ctrl = nvkm_rd32(device, base + 0);
	u32 coef = nvkm_rd32(device, base + 4);
	u32 ref = nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href);
	u32 post_भाग = 0;
	u32 घड़ी = 0;
	पूर्णांक N1, M1;

	चयन (base)अणु
	हाल 0x4020:
		post_भाग = 1 << ((nvkm_rd32(device, 0x4070) & 0x000f0000) >> 16);
		अवरोध;
	हाल 0x4028:
		post_भाग = (nvkm_rd32(device, 0x4040) & 0x000f0000) >> 16;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	N1 = (coef & 0x0000ff00) >> 8;
	M1 = (coef & 0x000000ff);
	अगर ((ctrl & 0x80000000) && M1) अणु
		घड़ी = ref * N1 / M1;
		घड़ी = घड़ी / post_भाग;
	पूर्ण

	वापस घड़ी;
पूर्ण

अटल पूर्णांक
mcp77_clk_पढ़ो(काष्ठा nvkm_clk *base, क्रमागत nv_clk_src src)
अणु
	काष्ठा mcp77_clk *clk = mcp77_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mast = nvkm_rd32(device, 0x00c054);
	u32 P = 0;

	चयन (src) अणु
	हाल nv_clk_src_crystal:
		वापस device->crystal;
	हाल nv_clk_src_href:
		वापस 100000; /* PCIE reference घड़ी */
	हाल nv_clk_src_hclkm4:
		वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href) * 4;
	हाल nv_clk_src_hclkm2d3:
		वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href) * 2 / 3;
	हाल nv_clk_src_host:
		चयन (mast & 0x000c0000) अणु
		हाल 0x00000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm2d3);
		हाल 0x00040000: अवरोध;
		हाल 0x00080000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm4);
		हाल 0x000c0000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_cclk);
		पूर्ण
		अवरोध;
	हाल nv_clk_src_core:
		P = (nvkm_rd32(device, 0x004028) & 0x00070000) >> 16;

		चयन (mast & 0x00000003) अणु
		हाल 0x00000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal) >> P;
		हाल 0x00000001: वापस 0;
		हाल 0x00000002: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm4) >> P;
		हाल 0x00000003: वापस पढ़ो_pll(clk, 0x004028) >> P;
		पूर्ण
		अवरोध;
	हाल nv_clk_src_cclk:
		अगर ((mast & 0x03000000) != 0x03000000)
			वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_core);

		अगर ((mast & 0x00000200) == 0x00000000)
			वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_core);

		चयन (mast & 0x00000c00) अणु
		हाल 0x00000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href);
		हाल 0x00000400: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm4);
		हाल 0x00000800: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm2d3);
		शेष: वापस 0;
		पूर्ण
	हाल nv_clk_src_shader:
		P = (nvkm_rd32(device, 0x004020) & 0x00070000) >> 16;
		चयन (mast & 0x00000030) अणु
		हाल 0x00000000:
			अगर (mast & 0x00000040)
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href) >> P;
			वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal) >> P;
		हाल 0x00000010: अवरोध;
		हाल 0x00000020: वापस पढ़ो_pll(clk, 0x004028) >> P;
		हाल 0x00000030: वापस पढ़ो_pll(clk, 0x004020) >> P;
		पूर्ण
		अवरोध;
	हाल nv_clk_src_mem:
		वापस 0;
	हाल nv_clk_src_vdec:
		P = (पढ़ो_भाग(clk) & 0x00000700) >> 8;

		चयन (mast & 0x00400000) अणु
		हाल 0x00400000:
			वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_core) >> P;
		शेष:
			वापस 500000 >> P;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	nvkm_debug(subdev, "unknown clock source %d %08x\n", src, mast);
	वापस 0;
पूर्ण

अटल u32
calc_pll(काष्ठा mcp77_clk *clk, u32 reg,
	 u32 घड़ी, पूर्णांक *N, पूर्णांक *M, पूर्णांक *P)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvbios_pll pll;
	पूर्णांक ret;

	ret = nvbios_pll_parse(subdev->device->bios, reg, &pll);
	अगर (ret)
		वापस 0;

	pll.vco2.max_freq = 0;
	pll.refclk = nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href);
	अगर (!pll.refclk)
		वापस 0;

	वापस nv04_pll_calc(subdev, &pll, घड़ी, N, M, शून्य, शून्य, P);
पूर्ण

अटल अंतरभूत u32
calc_P(u32 src, u32 target, पूर्णांक *भाग)
अणु
	u32 clk0 = src, clk1 = src;
	क्रम (*भाग = 0; *भाग <= 7; (*भाग)++) अणु
		अगर (clk0 <= target) अणु
			clk1 = clk0 << (*भाग ? 1 : 0);
			अवरोध;
		पूर्ण
		clk0 >>= 1;
	पूर्ण

	अगर (target - clk0 <= clk1 - target)
		वापस clk0;
	(*भाग)--;
	वापस clk1;
पूर्ण

अटल पूर्णांक
mcp77_clk_calc(काष्ठा nvkm_clk *base, काष्ठा nvkm_cstate *cstate)
अणु
	काष्ठा mcp77_clk *clk = mcp77_clk(base);
	स्थिर पूर्णांक shader = cstate->करोमुख्य[nv_clk_src_shader];
	स्थिर पूर्णांक core = cstate->करोमुख्य[nv_clk_src_core];
	स्थिर पूर्णांक vdec = cstate->करोमुख्य[nv_clk_src_vdec];
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	u32 out = 0, घड़ी = 0;
	पूर्णांक N, M, P1, P2 = 0;
	पूर्णांक भागs = 0;

	/* cclk: find suitable source, disable PLL अगर we can */
	अगर (core < nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm4))
		out = calc_P(nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm4), core, &भागs);

	/* Calculate घड़ी * 2, so shader घड़ी can use it too */
	घड़ी = calc_pll(clk, 0x4028, (core << 1), &N, &M, &P1);

	अगर (असल(core - out) <= असल(core - (घड़ी >> 1))) अणु
		clk->csrc = nv_clk_src_hclkm4;
		clk->cctrl = भागs << 16;
	पूर्ण अन्यथा अणु
		/* NVCTRL is actually used _after_ NVPOST, and after what we
		 * call NVPLL. To make matters worse, NVPOST is an पूर्णांकeger
		 * भागider instead of a right-shअगरt number. */
		अगर(P1 > 2) अणु
			P2 = P1 - 2;
			P1 = 2;
		पूर्ण

		clk->csrc = nv_clk_src_core;
		clk->ccoef = (N << 8) | M;

		clk->cctrl = (P2 + 1) << 16;
		clk->cpost = (1 << P1) << 16;
	पूर्ण

	/* sclk: nvpll + भागisor, href or spll */
	out = 0;
	अगर (shader == nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href)) अणु
		clk->ssrc = nv_clk_src_href;
	पूर्ण अन्यथा अणु
		घड़ी = calc_pll(clk, 0x4020, shader, &N, &M, &P1);
		अगर (clk->csrc == nv_clk_src_core)
			out = calc_P((core << 1), shader, &भागs);

		अगर (असल(shader - out) <=
		    असल(shader - घड़ी) &&
		   (भागs + P2) <= 7) अणु
			clk->ssrc = nv_clk_src_core;
			clk->sctrl = (भागs + P2) << 16;
		पूर्ण अन्यथा अणु
			clk->ssrc = nv_clk_src_shader;
			clk->scoef = (N << 8) | M;
			clk->sctrl = P1 << 16;
		पूर्ण
	पूर्ण

	/* vclk */
	out = calc_P(core, vdec, &भागs);
	घड़ी = calc_P(500000, vdec, &P1);
	अगर(असल(vdec - out) <= असल(vdec - घड़ी)) अणु
		clk->vsrc = nv_clk_src_cclk;
		clk->vभाग = भागs << 16;
	पूर्ण अन्यथा अणु
		clk->vsrc = nv_clk_src_vdec;
		clk->vभाग = P1 << 16;
	पूर्ण

	/* Prपूर्णांक strategy! */
	nvkm_debug(subdev, "nvpll: %08x %08x %08x\n",
		   clk->ccoef, clk->cpost, clk->cctrl);
	nvkm_debug(subdev, " spll: %08x %08x %08x\n",
		   clk->scoef, clk->spost, clk->sctrl);
	nvkm_debug(subdev, " vdiv: %08x\n", clk->vभाग);
	अगर (clk->csrc == nv_clk_src_hclkm4)
		nvkm_debug(subdev, "core: hrefm4\n");
	अन्यथा
		nvkm_debug(subdev, "core: nvpll\n");

	अगर (clk->ssrc == nv_clk_src_hclkm4)
		nvkm_debug(subdev, "shader: hrefm4\n");
	अन्यथा अगर (clk->ssrc == nv_clk_src_core)
		nvkm_debug(subdev, "shader: nvpll\n");
	अन्यथा
		nvkm_debug(subdev, "shader: spll\n");

	अगर (clk->vsrc == nv_clk_src_hclkm4)
		nvkm_debug(subdev, "vdec: 500MHz\n");
	अन्यथा
		nvkm_debug(subdev, "vdec: core\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
mcp77_clk_prog(काष्ठा nvkm_clk *base)
अणु
	काष्ठा mcp77_clk *clk = mcp77_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 pllmask = 0, mast;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *f = &flags;
	पूर्णांक ret = 0;

	ret = gt215_clk_pre(&clk->base, f);
	अगर (ret)
		जाओ out;

	/* First चयन to safe घड़ीs: href */
	mast = nvkm_mask(device, 0xc054, 0x03400e70, 0x03400640);
	mast &= ~0x00400e73;
	mast |= 0x03000000;

	चयन (clk->csrc) अणु
	हाल nv_clk_src_hclkm4:
		nvkm_mask(device, 0x4028, 0x00070000, clk->cctrl);
		mast |= 0x00000002;
		अवरोध;
	हाल nv_clk_src_core:
		nvkm_wr32(device, 0x402c, clk->ccoef);
		nvkm_wr32(device, 0x4028, 0x80000000 | clk->cctrl);
		nvkm_wr32(device, 0x4040, clk->cpost);
		pllmask |= (0x3 << 8);
		mast |= 0x00000003;
		अवरोध;
	शेष:
		nvkm_warn(subdev, "Reclocking failed: unknown core clock\n");
		जाओ resume;
	पूर्ण

	चयन (clk->ssrc) अणु
	हाल nv_clk_src_href:
		nvkm_mask(device, 0x4020, 0x00070000, 0x00000000);
		/* mast |= 0x00000000; */
		अवरोध;
	हाल nv_clk_src_core:
		nvkm_mask(device, 0x4020, 0x00070000, clk->sctrl);
		mast |= 0x00000020;
		अवरोध;
	हाल nv_clk_src_shader:
		nvkm_wr32(device, 0x4024, clk->scoef);
		nvkm_wr32(device, 0x4020, 0x80000000 | clk->sctrl);
		nvkm_wr32(device, 0x4070, clk->spost);
		pllmask |= (0x3 << 12);
		mast |= 0x00000030;
		अवरोध;
	शेष:
		nvkm_warn(subdev, "Reclocking failed: unknown sclk clock\n");
		जाओ resume;
	पूर्ण

	अगर (nvkm_msec(device, 2000,
		u32 पंचांगp = nvkm_rd32(device, 0x004080) & pllmask;
		अगर (पंचांगp == pllmask)
			अवरोध;
	) < 0)
		जाओ resume;

	चयन (clk->vsrc) अणु
	हाल nv_clk_src_cclk:
		mast |= 0x00400000;
		fallthrough;
	शेष:
		nvkm_wr32(device, 0x4600, clk->vभाग);
	पूर्ण

	nvkm_wr32(device, 0xc054, mast);

resume:
	/* Disable some PLLs and भागiders when unused */
	अगर (clk->csrc != nv_clk_src_core) अणु
		nvkm_wr32(device, 0x4040, 0x00000000);
		nvkm_mask(device, 0x4028, 0x80000000, 0x00000000);
	पूर्ण

	अगर (clk->ssrc != nv_clk_src_shader) अणु
		nvkm_wr32(device, 0x4070, 0x00000000);
		nvkm_mask(device, 0x4020, 0x80000000, 0x00000000);
	पूर्ण

out:
	अगर (ret == -EBUSY)
		f = शून्य;

	gt215_clk_post(&clk->base, f);
	वापस ret;
पूर्ण

अटल व्योम
mcp77_clk_tidy(काष्ठा nvkm_clk *base)
अणु
पूर्ण

अटल स्थिर काष्ठा nvkm_clk_func
mcp77_clk = अणु
	.पढ़ो = mcp77_clk_पढ़ो,
	.calc = mcp77_clk_calc,
	.prog = mcp77_clk_prog,
	.tidy = mcp77_clk_tidy,
	.करोमुख्यs = अणु
		अणु nv_clk_src_crystal, 0xff पूर्ण,
		अणु nv_clk_src_href   , 0xff पूर्ण,
		अणु nv_clk_src_core   , 0xff, 0, "core", 1000 पूर्ण,
		अणु nv_clk_src_shader , 0xff, 0, "shader", 1000 पूर्ण,
		अणु nv_clk_src_vdec   , 0xff, 0, "vdec", 1000 पूर्ण,
		अणु nv_clk_src_max पूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
mcp77_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_clk **pclk)
अणु
	काष्ठा mcp77_clk *clk;

	अगर (!(clk = kzalloc(माप(*clk), GFP_KERNEL)))
		वापस -ENOMEM;
	*pclk = &clk->base;

	वापस nvkm_clk_ctor(&mcp77_clk, device, type, inst, true, &clk->base);
पूर्ण
