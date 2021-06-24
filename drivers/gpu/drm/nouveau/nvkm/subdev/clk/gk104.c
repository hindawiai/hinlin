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
#घोषणा gk104_clk(p) container_of((p), काष्ठा gk104_clk, base)
#समावेश "priv.h"
#समावेश "pll.h"

#समावेश <subdev/समयr.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>

काष्ठा gk104_clk_info अणु
	u32 freq;
	u32 ssel;
	u32 mभाग;
	u32 dsrc;
	u32 dभाग;
	u32 coef;
पूर्ण;

काष्ठा gk104_clk अणु
	काष्ठा nvkm_clk base;
	काष्ठा gk104_clk_info eng[16];
पूर्ण;

अटल u32 पढ़ो_भाग(काष्ठा gk104_clk *, पूर्णांक, u32, u32);
अटल u32 पढ़ो_pll(काष्ठा gk104_clk *, u32);

अटल u32
पढ़ो_vco(काष्ठा gk104_clk *clk, u32 dsrc)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 ssrc = nvkm_rd32(device, dsrc);
	अगर (!(ssrc & 0x00000100))
		वापस पढ़ो_pll(clk, 0x00e800);
	वापस पढ़ो_pll(clk, 0x00e820);
पूर्ण

अटल u32
पढ़ो_pll(काष्ठा gk104_clk *clk, u32 pll)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 ctrl = nvkm_rd32(device, pll + 0x00);
	u32 coef = nvkm_rd32(device, pll + 0x04);
	u32 P = (coef & 0x003f0000) >> 16;
	u32 N = (coef & 0x0000ff00) >> 8;
	u32 M = (coef & 0x000000ff) >> 0;
	u32 sclk;
	u16 fN = 0xf000;

	अगर (!(ctrl & 0x00000001))
		वापस 0;

	चयन (pll) अणु
	हाल 0x00e800:
	हाल 0x00e820:
		sclk = device->crystal;
		P = 1;
		अवरोध;
	हाल 0x132000:
		sclk = पढ़ो_pll(clk, 0x132020);
		P = (coef & 0x10000000) ? 2 : 1;
		अवरोध;
	हाल 0x132020:
		sclk = पढ़ो_भाग(clk, 0, 0x137320, 0x137330);
		fN   = nvkm_rd32(device, pll + 0x10) >> 16;
		अवरोध;
	हाल 0x137000:
	हाल 0x137020:
	हाल 0x137040:
	हाल 0x1370e0:
		sclk = पढ़ो_भाग(clk, (pll & 0xff) / 0x20, 0x137120, 0x137140);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (P == 0)
		P = 1;

	sclk = (sclk * N) + (((u16)(fN + 4096) * sclk) >> 13);
	वापस sclk / (M * P);
पूर्ण

अटल u32
पढ़ो_भाग(काष्ठा gk104_clk *clk, पूर्णांक करोff, u32 dsrc, u32 dctl)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 ssrc = nvkm_rd32(device, dsrc + (करोff * 4));
	u32 sctl = nvkm_rd32(device, dctl + (करोff * 4));

	चयन (ssrc & 0x00000003) अणु
	हाल 0:
		अगर ((ssrc & 0x00030000) != 0x00030000)
			वापस device->crystal;
		वापस 108000;
	हाल 2:
		वापस 100000;
	हाल 3:
		अगर (sctl & 0x80000000) अणु
			u32 sclk = पढ़ो_vco(clk, dsrc + (करोff * 4));
			u32 sभाग = (sctl & 0x0000003f) + 2;
			वापस (sclk * 2) / sभाग;
		पूर्ण

		वापस पढ़ो_vco(clk, dsrc + (करोff * 4));
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32
पढ़ो_mem(काष्ठा gk104_clk *clk)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	चयन (nvkm_rd32(device, 0x1373f4) & 0x0000000f) अणु
	हाल 1: वापस पढ़ो_pll(clk, 0x132020);
	हाल 2: वापस पढ़ो_pll(clk, 0x132000);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32
पढ़ो_clk(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 sctl = nvkm_rd32(device, 0x137250 + (idx * 4));
	u32 sclk, sभाग;

	अगर (idx < 7) अणु
		u32 ssel = nvkm_rd32(device, 0x137100);
		अगर (ssel & (1 << idx)) अणु
			sclk = पढ़ो_pll(clk, 0x137000 + (idx * 0x20));
			sभाग = 1;
		पूर्ण अन्यथा अणु
			sclk = पढ़ो_भाग(clk, idx, 0x137160, 0x1371d0);
			sभाग = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 ssrc = nvkm_rd32(device, 0x137160 + (idx * 0x04));
		अगर ((ssrc & 0x00000003) == 0x00000003) अणु
			sclk = पढ़ो_भाग(clk, idx, 0x137160, 0x1371d0);
			अगर (ssrc & 0x00000100) अणु
				अगर (ssrc & 0x40000000)
					sclk = पढ़ो_pll(clk, 0x1370e0);
				sभाग = 1;
			पूर्ण अन्यथा अणु
				sभाग = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			sclk = पढ़ो_भाग(clk, idx, 0x137160, 0x1371d0);
			sभाग = 0;
		पूर्ण
	पूर्ण

	अगर (sctl & 0x80000000) अणु
		अगर (sभाग)
			sभाग = ((sctl & 0x00003f00) >> 8) + 2;
		अन्यथा
			sभाग = ((sctl & 0x0000003f) >> 0) + 2;
		वापस (sclk * 2) / sभाग;
	पूर्ण

	वापस sclk;
पूर्ण

अटल पूर्णांक
gk104_clk_पढ़ो(काष्ठा nvkm_clk *base, क्रमागत nv_clk_src src)
अणु
	काष्ठा gk104_clk *clk = gk104_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;

	चयन (src) अणु
	हाल nv_clk_src_crystal:
		वापस device->crystal;
	हाल nv_clk_src_href:
		वापस 100000;
	हाल nv_clk_src_mem:
		वापस पढ़ो_mem(clk);
	हाल nv_clk_src_gpc:
		वापस पढ़ो_clk(clk, 0x00);
	हाल nv_clk_src_rop:
		वापस पढ़ो_clk(clk, 0x01);
	हाल nv_clk_src_hubk07:
		वापस पढ़ो_clk(clk, 0x02);
	हाल nv_clk_src_hubk06:
		वापस पढ़ो_clk(clk, 0x07);
	हाल nv_clk_src_hubk01:
		वापस पढ़ो_clk(clk, 0x08);
	हाल nv_clk_src_pmu:
		वापस पढ़ो_clk(clk, 0x0c);
	हाल nv_clk_src_vdec:
		वापस पढ़ो_clk(clk, 0x0e);
	शेष:
		nvkm_error(subdev, "invalid clock source %d\n", src);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32
calc_भाग(काष्ठा gk104_clk *clk, पूर्णांक idx, u32 ref, u32 freq, u32 *dभाग)
अणु
	u32 भाग = min((ref * 2) / freq, (u32)65);
	अगर (भाग < 2)
		भाग = 2;

	*dभाग = भाग - 2;
	वापस (ref * 2) / भाग;
पूर्ण

अटल u32
calc_src(काष्ठा gk104_clk *clk, पूर्णांक idx, u32 freq, u32 *dsrc, u32 *dभाग)
अणु
	u32 sclk;

	/* use one of the fixed frequencies अगर possible */
	*dभाग = 0x00000000;
	चयन (freq) अणु
	हाल  27000:
	हाल 108000:
		*dsrc = 0x00000000;
		अगर (freq == 108000)
			*dsrc |= 0x00030000;
		वापस freq;
	हाल 100000:
		*dsrc = 0x00000002;
		वापस freq;
	शेष:
		*dsrc = 0x00000003;
		अवरोध;
	पूर्ण

	/* otherwise, calculate the बंदst भागider */
	sclk = पढ़ो_vco(clk, 0x137160 + (idx * 4));
	अगर (idx < 7)
		sclk = calc_भाग(clk, idx, sclk, freq, dभाग);
	वापस sclk;
पूर्ण

अटल u32
calc_pll(काष्ठा gk104_clk *clk, पूर्णांक idx, u32 freq, u32 *coef)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	काष्ठा nvbios_pll limits;
	पूर्णांक N, M, P, ret;

	ret = nvbios_pll_parse(bios, 0x137000 + (idx * 0x20), &limits);
	अगर (ret)
		वापस 0;

	limits.refclk = पढ़ो_भाग(clk, idx, 0x137120, 0x137140);
	अगर (!limits.refclk)
		वापस 0;

	ret = gt215_pll_calc(subdev, &limits, freq, &N, शून्य, &M, &P);
	अगर (ret <= 0)
		वापस 0;

	*coef = (P << 16) | (N << 8) | M;
	वापस ret;
पूर्ण

अटल पूर्णांक
calc_clk(काष्ठा gk104_clk *clk,
	 काष्ठा nvkm_cstate *cstate, पूर्णांक idx, पूर्णांक करोm)
अणु
	काष्ठा gk104_clk_info *info = &clk->eng[idx];
	u32 freq = cstate->करोमुख्य[करोm];
	u32 src0, भाग0, भाग1D, भाग1P = 0;
	u32 clk0, clk1 = 0;

	/* invalid घड़ी करोमुख्य */
	अगर (!freq)
		वापस 0;

	/* first possible path, using only भागiders */
	clk0 = calc_src(clk, idx, freq, &src0, &भाग0);
	clk0 = calc_भाग(clk, idx, clk0, freq, &भाग1D);

	/* see अगर we can get any बंदr using PLLs */
	अगर (clk0 != freq && (0x0000ff87 & (1 << idx))) अणु
		अगर (idx <= 7)
			clk1 = calc_pll(clk, idx, freq, &info->coef);
		अन्यथा
			clk1 = cstate->करोमुख्य[nv_clk_src_hubk06];
		clk1 = calc_भाग(clk, idx, clk1, freq, &भाग1P);
	पूर्ण

	/* select the method which माला_लो बंदst to target freq */
	अगर (असल((पूर्णांक)freq - clk0) <= असल((पूर्णांक)freq - clk1)) अणु
		info->dsrc = src0;
		अगर (भाग0) अणु
			info->dभाग |= 0x80000000;
			info->dभाग |= भाग0;
		पूर्ण
		अगर (भाग1D) अणु
			info->mभाग |= 0x80000000;
			info->mभाग |= भाग1D;
		पूर्ण
		info->ssel = 0;
		info->freq = clk0;
	पूर्ण अन्यथा अणु
		अगर (भाग1P) अणु
			info->mभाग |= 0x80000000;
			info->mभाग |= भाग1P << 8;
		पूर्ण
		info->ssel = (1 << idx);
		info->dsrc = 0x40000100;
		info->freq = clk1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gk104_clk_calc(काष्ठा nvkm_clk *base, काष्ठा nvkm_cstate *cstate)
अणु
	काष्ठा gk104_clk *clk = gk104_clk(base);
	पूर्णांक ret;

	अगर ((ret = calc_clk(clk, cstate, 0x00, nv_clk_src_gpc)) ||
	    (ret = calc_clk(clk, cstate, 0x01, nv_clk_src_rop)) ||
	    (ret = calc_clk(clk, cstate, 0x02, nv_clk_src_hubk07)) ||
	    (ret = calc_clk(clk, cstate, 0x07, nv_clk_src_hubk06)) ||
	    (ret = calc_clk(clk, cstate, 0x08, nv_clk_src_hubk01)) ||
	    (ret = calc_clk(clk, cstate, 0x0c, nv_clk_src_pmu)) ||
	    (ret = calc_clk(clk, cstate, 0x0e, nv_clk_src_vdec)))
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम
gk104_clk_prog_0(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा gk104_clk_info *info = &clk->eng[idx];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	अगर (!info->ssel) अणु
		nvkm_mask(device, 0x1371d0 + (idx * 0x04), 0x8000003f, info->dभाग);
		nvkm_wr32(device, 0x137160 + (idx * 0x04), info->dsrc);
	पूर्ण
पूर्ण

अटल व्योम
gk104_clk_prog_1_0(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	nvkm_mask(device, 0x137100, (1 << idx), 0x00000000);
	nvkm_msec(device, 2000,
		अगर (!(nvkm_rd32(device, 0x137100) & (1 << idx)))
			अवरोध;
	);
पूर्ण

अटल व्योम
gk104_clk_prog_1_1(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	nvkm_mask(device, 0x137160 + (idx * 0x04), 0x00000100, 0x00000000);
पूर्ण

अटल व्योम
gk104_clk_prog_2(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा gk104_clk_info *info = &clk->eng[idx];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	स्थिर u32 addr = 0x137000 + (idx * 0x20);
	nvkm_mask(device, addr + 0x00, 0x00000004, 0x00000000);
	nvkm_mask(device, addr + 0x00, 0x00000001, 0x00000000);
	अगर (info->coef) अणु
		nvkm_wr32(device, addr + 0x04, info->coef);
		nvkm_mask(device, addr + 0x00, 0x00000001, 0x00000001);

		/* Test PLL lock */
		nvkm_mask(device, addr + 0x00, 0x00000010, 0x00000000);
		nvkm_msec(device, 2000,
			अगर (nvkm_rd32(device, addr + 0x00) & 0x00020000)
				अवरोध;
		);
		nvkm_mask(device, addr + 0x00, 0x00000010, 0x00000010);

		/* Enable sync mode */
		nvkm_mask(device, addr + 0x00, 0x00000004, 0x00000004);
	पूर्ण
पूर्ण

अटल व्योम
gk104_clk_prog_3(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा gk104_clk_info *info = &clk->eng[idx];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	अगर (info->ssel)
		nvkm_mask(device, 0x137250 + (idx * 0x04), 0x00003f00, info->mभाग);
	अन्यथा
		nvkm_mask(device, 0x137250 + (idx * 0x04), 0x0000003f, info->mभाग);
पूर्ण

अटल व्योम
gk104_clk_prog_4_0(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा gk104_clk_info *info = &clk->eng[idx];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	अगर (info->ssel) अणु
		nvkm_mask(device, 0x137100, (1 << idx), info->ssel);
		nvkm_msec(device, 2000,
			u32 पंचांगp = nvkm_rd32(device, 0x137100) & (1 << idx);
			अगर (पंचांगp == info->ssel)
				अवरोध;
		);
	पूर्ण
पूर्ण

अटल व्योम
gk104_clk_prog_4_1(काष्ठा gk104_clk *clk, पूर्णांक idx)
अणु
	काष्ठा gk104_clk_info *info = &clk->eng[idx];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	अगर (info->ssel) अणु
		nvkm_mask(device, 0x137160 + (idx * 0x04), 0x40000000, 0x40000000);
		nvkm_mask(device, 0x137160 + (idx * 0x04), 0x00000100, 0x00000100);
	पूर्ण
पूर्ण

अटल पूर्णांक
gk104_clk_prog(काष्ठा nvkm_clk *base)
अणु
	काष्ठा gk104_clk *clk = gk104_clk(base);
	काष्ठा अणु
		u32 mask;
		व्योम (*exec)(काष्ठा gk104_clk *, पूर्णांक);
	पूर्ण stage[] = अणु
		अणु 0x007f, gk104_clk_prog_0   पूर्ण, /* भाग programming */
		अणु 0x007f, gk104_clk_prog_1_0 पूर्ण, /* select भाग mode */
		अणु 0xff80, gk104_clk_prog_1_1 पूर्ण,
		अणु 0x00ff, gk104_clk_prog_2   पूर्ण, /* (maybe) program pll */
		अणु 0xff80, gk104_clk_prog_3   पूर्ण, /* final भागider */
		अणु 0x007f, gk104_clk_prog_4_0 पूर्ण, /* (maybe) select pll mode */
		अणु 0xff80, gk104_clk_prog_4_1 पूर्ण,
	पूर्ण;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(stage); i++) अणु
		क्रम (j = 0; j < ARRAY_SIZE(clk->eng); j++) अणु
			अगर (!(stage[i].mask & (1 << j)))
				जारी;
			अगर (!clk->eng[j].freq)
				जारी;
			stage[i].exec(clk, j);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
gk104_clk_tidy(काष्ठा nvkm_clk *base)
अणु
	काष्ठा gk104_clk *clk = gk104_clk(base);
	स_रखो(clk->eng, 0x00, माप(clk->eng));
पूर्ण

अटल स्थिर काष्ठा nvkm_clk_func
gk104_clk = अणु
	.पढ़ो = gk104_clk_पढ़ो,
	.calc = gk104_clk_calc,
	.prog = gk104_clk_prog,
	.tidy = gk104_clk_tidy,
	.करोमुख्यs = अणु
		अणु nv_clk_src_crystal, 0xff पूर्ण,
		अणु nv_clk_src_href   , 0xff पूर्ण,
		अणु nv_clk_src_gpc    , 0x00, NVKM_CLK_DOM_FLAG_CORE | NVKM_CLK_DOM_FLAG_VPSTATE, "core", 2000 पूर्ण,
		अणु nv_clk_src_hubk07 , 0x01, NVKM_CLK_DOM_FLAG_CORE पूर्ण,
		अणु nv_clk_src_rop    , 0x02, NVKM_CLK_DOM_FLAG_CORE पूर्ण,
		अणु nv_clk_src_mem    , 0x03, 0, "memory", 500 पूर्ण,
		अणु nv_clk_src_hubk06 , 0x04, NVKM_CLK_DOM_FLAG_CORE पूर्ण,
		अणु nv_clk_src_hubk01 , 0x05 पूर्ण,
		अणु nv_clk_src_vdec   , 0x06 पूर्ण,
		अणु nv_clk_src_pmu    , 0x07 पूर्ण,
		अणु nv_clk_src_max पूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gk104_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_clk **pclk)
अणु
	काष्ठा gk104_clk *clk;

	अगर (!(clk = kzalloc(माप(*clk), GFP_KERNEL)))
		वापस -ENOMEM;
	*pclk = &clk->base;

	वापस nvkm_clk_ctor(&gk104_clk, device, type, inst, true, &clk->base);
पूर्ण
