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
#समावेश "nv50.h"
#समावेश "pll.h"
#समावेश "seq.h"

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>

अटल u32
पढ़ो_भाग(काष्ठा nv50_clk *clk)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	चयन (device->chipset) अणु
	हाल 0x50: /* it exists, but only has bit 31, not the भागiders.. */
	हाल 0x84:
	हाल 0x86:
	हाल 0x98:
	हाल 0xa0:
		वापस nvkm_rd32(device, 0x004700);
	हाल 0x92:
	हाल 0x94:
	हाल 0x96:
		वापस nvkm_rd32(device, 0x004800);
	शेष:
		वापस 0x00000000;
	पूर्ण
पूर्ण

अटल u32
पढ़ो_pll_src(काष्ठा nv50_clk *clk, u32 base)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 coef, ref = nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal);
	u32 rsel = nvkm_rd32(device, 0x00e18c);
	पूर्णांक P, N, M, id;

	चयन (device->chipset) अणु
	हाल 0x50:
	हाल 0xa0:
		चयन (base) अणु
		हाल 0x4020:
		हाल 0x4028: id = !!(rsel & 0x00000004); अवरोध;
		हाल 0x4008: id = !!(rsel & 0x00000008); अवरोध;
		हाल 0x4030: id = 0; अवरोध;
		शेष:
			nvkm_error(subdev, "ref: bad pll %06x\n", base);
			वापस 0;
		पूर्ण

		coef = nvkm_rd32(device, 0x00e81c + (id * 0x0c));
		ref *=  (coef & 0x01000000) ? 2 : 4;
		P    =  (coef & 0x00070000) >> 16;
		N    = ((coef & 0x0000ff00) >> 8) + 1;
		M    = ((coef & 0x000000ff) >> 0) + 1;
		अवरोध;
	हाल 0x84:
	हाल 0x86:
	हाल 0x92:
		coef = nvkm_rd32(device, 0x00e81c);
		P    = (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		अवरोध;
	हाल 0x94:
	हाल 0x96:
	हाल 0x98:
		rsel = nvkm_rd32(device, 0x00c050);
		चयन (base) अणु
		हाल 0x4020: rsel = (rsel & 0x00000003) >> 0; अवरोध;
		हाल 0x4008: rsel = (rsel & 0x0000000c) >> 2; अवरोध;
		हाल 0x4028: rsel = (rsel & 0x00001800) >> 11; अवरोध;
		हाल 0x4030: rsel = 3; अवरोध;
		शेष:
			nvkm_error(subdev, "ref: bad pll %06x\n", base);
			वापस 0;
		पूर्ण

		चयन (rsel) अणु
		हाल 0: id = 1; अवरोध;
		हाल 1: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal);
		हाल 2: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href);
		हाल 3: id = 0; अवरोध;
		पूर्ण

		coef =  nvkm_rd32(device, 0x00e81c + (id * 0x28));
		P    = (nvkm_rd32(device, 0x00e824 + (id * 0x28)) >> 16) & 7;
		P   += (coef & 0x00070000) >> 16;
		N    = (coef & 0x0000ff00) >> 8;
		M    = (coef & 0x000000ff) >> 0;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (M)
		वापस (ref * N / M) >> P;

	वापस 0;
पूर्ण

अटल u32
पढ़ो_pll_ref(काष्ठा nv50_clk *clk, u32 base)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 src, mast = nvkm_rd32(device, 0x00c040);

	चयन (base) अणु
	हाल 0x004028:
		src = !!(mast & 0x00200000);
		अवरोध;
	हाल 0x004020:
		src = !!(mast & 0x00400000);
		अवरोध;
	हाल 0x004008:
		src = !!(mast & 0x00010000);
		अवरोध;
	हाल 0x004030:
		src = !!(mast & 0x02000000);
		अवरोध;
	हाल 0x00e810:
		वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal);
	शेष:
		nvkm_error(subdev, "bad pll %06x\n", base);
		वापस 0;
	पूर्ण

	अगर (src)
		वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href);

	वापस पढ़ो_pll_src(clk, base);
पूर्ण

अटल u32
पढ़ो_pll(काष्ठा nv50_clk *clk, u32 base)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 mast = nvkm_rd32(device, 0x00c040);
	u32 ctrl = nvkm_rd32(device, base + 0);
	u32 coef = nvkm_rd32(device, base + 4);
	u32 ref = पढ़ो_pll_ref(clk, base);
	u32 freq = 0;
	पूर्णांक N1, N2, M1, M2;

	अगर (base == 0x004028 && (mast & 0x00100000)) अणु
		/* wtf, appears to only disable post-भागider on gt200 */
		अगर (device->chipset != 0xa0)
			वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_करोm6);
	पूर्ण

	N2 = (coef & 0xff000000) >> 24;
	M2 = (coef & 0x00ff0000) >> 16;
	N1 = (coef & 0x0000ff00) >> 8;
	M1 = (coef & 0x000000ff);
	अगर ((ctrl & 0x80000000) && M1) अणु
		freq = ref * N1 / M1;
		अगर ((ctrl & 0x40000100) == 0x40000000) अणु
			अगर (M2)
				freq = freq * N2 / M2;
			अन्यथा
				freq = 0;
		पूर्ण
	पूर्ण

	वापस freq;
पूर्ण

पूर्णांक
nv50_clk_पढ़ो(काष्ठा nvkm_clk *base, क्रमागत nv_clk_src src)
अणु
	काष्ठा nv50_clk *clk = nv50_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 mast = nvkm_rd32(device, 0x00c040);
	u32 P = 0;

	चयन (src) अणु
	हाल nv_clk_src_crystal:
		वापस device->crystal;
	हाल nv_clk_src_href:
		वापस 100000; /* PCIE reference घड़ी */
	हाल nv_clk_src_hclk:
		वापस भाग_u64((u64)nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href) * 27778, 10000);
	हाल nv_clk_src_hclkm3:
		वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclk) * 3;
	हाल nv_clk_src_hclkm3d2:
		वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclk) * 3 / 2;
	हाल nv_clk_src_host:
		चयन (mast & 0x30000000) अणु
		हाल 0x00000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href);
		हाल 0x10000000: अवरोध;
		हाल 0x20000000: /* !0x50 */
		हाल 0x30000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclk);
		पूर्ण
		अवरोध;
	हाल nv_clk_src_core:
		अगर (!(mast & 0x00100000))
			P = (nvkm_rd32(device, 0x004028) & 0x00070000) >> 16;
		चयन (mast & 0x00000003) अणु
		हाल 0x00000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal) >> P;
		हाल 0x00000001: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_करोm6);
		हाल 0x00000002: वापस पढ़ो_pll(clk, 0x004020) >> P;
		हाल 0x00000003: वापस पढ़ो_pll(clk, 0x004028) >> P;
		पूर्ण
		अवरोध;
	हाल nv_clk_src_shader:
		P = (nvkm_rd32(device, 0x004020) & 0x00070000) >> 16;
		चयन (mast & 0x00000030) अणु
		हाल 0x00000000:
			अगर (mast & 0x00000080)
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_host) >> P;
			वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal) >> P;
		हाल 0x00000010: अवरोध;
		हाल 0x00000020: वापस पढ़ो_pll(clk, 0x004028) >> P;
		हाल 0x00000030: वापस पढ़ो_pll(clk, 0x004020) >> P;
		पूर्ण
		अवरोध;
	हाल nv_clk_src_mem:
		P = (nvkm_rd32(device, 0x004008) & 0x00070000) >> 16;
		अगर (nvkm_rd32(device, 0x004008) & 0x00000200) अणु
			चयन (mast & 0x0000c000) अणु
			हाल 0x00000000:
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal) >> P;
			हाल 0x00008000:
			हाल 0x0000c000:
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href) >> P;
			पूर्ण
		पूर्ण अन्यथा अणु
			वापस पढ़ो_pll(clk, 0x004008) >> P;
		पूर्ण
		अवरोध;
	हाल nv_clk_src_vdec:
		P = (पढ़ो_भाग(clk) & 0x00000700) >> 8;
		चयन (device->chipset) अणु
		हाल 0x84:
		हाल 0x86:
		हाल 0x92:
		हाल 0x94:
		हाल 0x96:
		हाल 0xa0:
			चयन (mast & 0x00000c00) अणु
			हाल 0x00000000:
				अगर (device->chipset == 0xa0) /* wtf?? */
					वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_core) >> P;
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_crystal) >> P;
			हाल 0x00000400:
				वापस 0;
			हाल 0x00000800:
				अगर (mast & 0x01000000)
					वापस पढ़ो_pll(clk, 0x004028) >> P;
				वापस पढ़ो_pll(clk, 0x004030) >> P;
			हाल 0x00000c00:
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_core) >> P;
			पूर्ण
			अवरोध;
		हाल 0x98:
			चयन (mast & 0x00000c00) अणु
			हाल 0x00000000:
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_core) >> P;
			हाल 0x00000400:
				वापस 0;
			हाल 0x00000800:
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm3d2) >> P;
			हाल 0x00000c00:
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_mem) >> P;
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;
	हाल nv_clk_src_करोm6:
		चयन (device->chipset) अणु
		हाल 0x50:
		हाल 0xa0:
			वापस पढ़ो_pll(clk, 0x00e810) >> 2;
		हाल 0x84:
		हाल 0x86:
		हाल 0x92:
		हाल 0x94:
		हाल 0x96:
		हाल 0x98:
			P = (पढ़ो_भाग(clk) & 0x00000007) >> 0;
			चयन (mast & 0x0c000000) अणु
			हाल 0x00000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href);
			हाल 0x04000000: अवरोध;
			हाल 0x08000000: वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclk);
			हाल 0x0c000000:
				वापस nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm3) >> P;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	nvkm_debug(subdev, "unknown clock source %d %08x\n", src, mast);
	वापस -EINVAL;
पूर्ण

अटल u32
calc_pll(काष्ठा nv50_clk *clk, u32 reg, u32 idx, पूर्णांक *N, पूर्णांक *M, पूर्णांक *P)
अणु
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvbios_pll pll;
	पूर्णांक ret;

	ret = nvbios_pll_parse(subdev->device->bios, reg, &pll);
	अगर (ret)
		वापस 0;

	pll.vco2.max_freq = 0;
	pll.refclk = पढ़ो_pll_ref(clk, reg);
	अगर (!pll.refclk)
		वापस 0;

	वापस nv04_pll_calc(subdev, &pll, idx, N, M, शून्य, शून्य, P);
पूर्ण

अटल अंतरभूत u32
calc_भाग(u32 src, u32 target, पूर्णांक *भाग)
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

अटल अंतरभूत u32
clk_same(u32 a, u32 b)
अणु
	वापस ((a / 1000) == (b / 1000));
पूर्ण

पूर्णांक
nv50_clk_calc(काष्ठा nvkm_clk *base, काष्ठा nvkm_cstate *cstate)
अणु
	काष्ठा nv50_clk *clk = nv50_clk(base);
	काष्ठा nv50_clk_hwsq *hwsq = &clk->hwsq;
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	स्थिर पूर्णांक shader = cstate->करोमुख्य[nv_clk_src_shader];
	स्थिर पूर्णांक core = cstate->करोमुख्य[nv_clk_src_core];
	स्थिर पूर्णांक vdec = cstate->करोमुख्य[nv_clk_src_vdec];
	स्थिर पूर्णांक करोm6 = cstate->करोमुख्य[nv_clk_src_करोm6];
	u32 masपंचांग = 0, mastv = 0;
	u32 भागsm = 0, भागsv = 0;
	पूर्णांक N, M, P1, P2;
	पूर्णांक freq, out;

	/* prepare a hwsq script from which we'll perक्रमm the reघड़ी */
	out = clk_init(hwsq, subdev);
	अगर (out)
		वापस out;

	clk_wr32(hwsq, fअगरo, 0x00000001); /* block fअगरo */
	clk_nsec(hwsq, 8000);
	clk_setf(hwsq, 0x10, 0x00); /* disable fb */
	clk_रुको(hwsq, 0x00, 0x01); /* रुको क्रम fb disabled */

	/* vdec: aव्योम modअगरying xpll until we know exactly how the other
	 * घड़ी करोमुख्यs work, i suspect at least some of them can also be
	 * tied to xpll...
	 */
	अगर (vdec) अणु
		/* see how बंद we can get using nvclk as a source */
		freq = calc_भाग(core, vdec, &P1);

		/* see how बंद we can get using xpll/hclk as a source */
		अगर (device->chipset != 0x98)
			out = पढ़ो_pll(clk, 0x004030);
		अन्यथा
			out = nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclkm3d2);
		out = calc_भाग(out, vdec, &P2);

		/* select whichever माला_लो us बंदst */
		अगर (असल(vdec - freq) <= असल(vdec - out)) अणु
			अगर (device->chipset != 0x98)
				mastv |= 0x00000c00;
			भागsv |= P1 << 8;
		पूर्ण अन्यथा अणु
			mastv |= 0x00000800;
			भागsv |= P2 << 8;
		पूर्ण

		masपंचांग |= 0x00000c00;
		भागsm |= 0x00000700;
	पूर्ण

	/* करोm6: nfi what this is, but we're limited to various combinations
	 * of the host घड़ी frequency
	 */
	अगर (करोm6) अणु
		अगर (clk_same(करोm6, nvkm_clk_पढ़ो(&clk->base, nv_clk_src_href))) अणु
			mastv |= 0x00000000;
		पूर्ण अन्यथा
		अगर (clk_same(करोm6, nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclk))) अणु
			mastv |= 0x08000000;
		पूर्ण अन्यथा अणु
			freq = nvkm_clk_पढ़ो(&clk->base, nv_clk_src_hclk) * 3;
			calc_भाग(freq, करोm6, &P1);

			mastv |= 0x0c000000;
			भागsv |= P1;
		पूर्ण

		masपंचांग |= 0x0c000000;
		भागsm |= 0x00000007;
	पूर्ण

	/* vdec/करोm6: चयन to "safe" घड़ीs temporarily, update भागiders
	 * and then चयन to target घड़ीs
	 */
	clk_mask(hwsq, mast, masपंचांग, 0x00000000);
	clk_mask(hwsq, भागs, भागsm, भागsv);
	clk_mask(hwsq, mast, masपंचांग, mastv);

	/* core/shader: disconnect nvclk/sclk from their PLLs (nvclk to करोm6,
	 * sclk to hclk) beक्रमe reprogramming
	 */
	अगर (device->chipset < 0x92)
		clk_mask(hwsq, mast, 0x001000b0, 0x00100080);
	अन्यथा
		clk_mask(hwsq, mast, 0x000000b3, 0x00000081);

	/* core: क्रम the moment at least, always use nvpll */
	freq = calc_pll(clk, 0x4028, core, &N, &M, &P1);
	अगर (freq == 0)
		वापस -दुस्फल;

	clk_mask(hwsq, nvpll[0], 0xc03f0100,
				 0x80000000 | (P1 << 19) | (P1 << 16));
	clk_mask(hwsq, nvpll[1], 0x0000ffff, (N << 8) | M);

	/* shader: tie to nvclk अगर possible, otherwise use spll.  have to be
	 * very careful that the shader घड़ी is at least twice the core, or
	 * some chipsets will be very unhappy.  i expect most or all of these
	 * हालs will be handled by tying to nvclk, but it's possible there's
	 * corners
	 */
	अगर (P1-- && shader == (core << 1)) अणु
		clk_mask(hwsq, spll[0], 0xc03f0100, (P1 << 19) | (P1 << 16));
		clk_mask(hwsq, mast, 0x00100033, 0x00000023);
	पूर्ण अन्यथा अणु
		freq = calc_pll(clk, 0x4020, shader, &N, &M, &P1);
		अगर (freq == 0)
			वापस -दुस्फल;

		clk_mask(hwsq, spll[0], 0xc03f0100,
					0x80000000 | (P1 << 19) | (P1 << 16));
		clk_mask(hwsq, spll[1], 0x0000ffff, (N << 8) | M);
		clk_mask(hwsq, mast, 0x00100033, 0x00000033);
	पूर्ण

	/* restore normal operation */
	clk_setf(hwsq, 0x10, 0x01); /* enable fb */
	clk_रुको(hwsq, 0x00, 0x00); /* रुको क्रम fb enabled */
	clk_wr32(hwsq, fअगरo, 0x00000000); /* un-block fअगरo */
	वापस 0;
पूर्ण

पूर्णांक
nv50_clk_prog(काष्ठा nvkm_clk *base)
अणु
	काष्ठा nv50_clk *clk = nv50_clk(base);
	वापस clk_exec(&clk->hwsq, true);
पूर्ण

व्योम
nv50_clk_tidy(काष्ठा nvkm_clk *base)
अणु
	काष्ठा nv50_clk *clk = nv50_clk(base);
	clk_exec(&clk->hwsq, false);
पूर्ण

पूर्णांक
nv50_clk_new_(स्थिर काष्ठा nvkm_clk_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, bool allow_reघड़ी, काष्ठा nvkm_clk **pclk)
अणु
	काष्ठा nv50_clk *clk;
	पूर्णांक ret;

	अगर (!(clk = kzalloc(माप(*clk), GFP_KERNEL)))
		वापस -ENOMEM;
	ret = nvkm_clk_ctor(func, device, type, inst, allow_reघड़ी, &clk->base);
	*pclk = &clk->base;
	अगर (ret)
		वापस ret;

	clk->hwsq.r_fअगरo = hwsq_reg(0x002504);
	clk->hwsq.r_spll[0] = hwsq_reg(0x004020);
	clk->hwsq.r_spll[1] = hwsq_reg(0x004024);
	clk->hwsq.r_nvpll[0] = hwsq_reg(0x004028);
	clk->hwsq.r_nvpll[1] = hwsq_reg(0x00402c);
	चयन (device->chipset) अणु
	हाल 0x92:
	हाल 0x94:
	हाल 0x96:
		clk->hwsq.r_भागs = hwsq_reg(0x004800);
		अवरोध;
	शेष:
		clk->hwsq.r_भागs = hwsq_reg(0x004700);
		अवरोध;
	पूर्ण
	clk->hwsq.r_mast = hwsq_reg(0x00c040);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nvkm_clk_func
nv50_clk = अणु
	.पढ़ो = nv50_clk_पढ़ो,
	.calc = nv50_clk_calc,
	.prog = nv50_clk_prog,
	.tidy = nv50_clk_tidy,
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
nv50_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	     काष्ठा nvkm_clk **pclk)
अणु
	वापस nv50_clk_new_(&nv50_clk, device, type, inst, false, pclk);
पूर्ण
