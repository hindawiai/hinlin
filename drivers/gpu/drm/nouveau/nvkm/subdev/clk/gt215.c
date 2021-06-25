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
 *          Roy Spliet
 */
#घोषणा gt215_clk(p) container_of((p), काष्ठा gt215_clk, base)
#समावेश "gt215.h"
#समावेश "pll.h"

#समावेश <engine/fअगरo.h>
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>
#समावेश <subdev/समयr.h>

काष्ठा gt215_clk अणु
	काष्ठा nvkm_clk base;
	काष्ठा gt215_clk_info eng[nv_clk_src_max];
पूर्ण;

अटल u32 पढ़ो_clk(काष्ठा gt215_clk *, पूर्णांक, bool);
अटल u32 पढ़ो_pll(काष्ठा gt215_clk *, पूर्णांक, u32);

अटल u32
पढ़ो_vco(काष्ठा gt215_clk *clk, पूर्णांक idx)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 sctl = nvkm_rd32(device, 0x4120 + (idx * 4));

	चयन (sctl & 0x00000030) अणु
	हाल 0x00000000:
		वापस device->crystal;
	हाल 0x00000020:
		वापस पढ़ो_pll(clk, 0x41, 0x00e820);
	हाल 0x00000030:
		वापस पढ़ो_pll(clk, 0x42, 0x00e8a0);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32
पढ़ो_clk(काष्ठा gt215_clk *clk, पूर्णांक idx, bool ignore_en)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 sctl, sभाग, sclk;

	/* refclk क्रम the 0xe8xx plls is a fixed frequency */
	अगर (idx >= 0x40) अणु
		अगर (device->chipset == 0xaf) अणु
			/* no joke.. seriously.. sigh.. */
			वापस nvkm_rd32(device, 0x00471c) * 1000;
		पूर्ण

		वापस device->crystal;
	पूर्ण

	sctl = nvkm_rd32(device, 0x4120 + (idx * 4));
	अगर (!ignore_en && !(sctl & 0x00000100))
		वापस 0;

	/* out_alt */
	अगर (sctl & 0x00000400)
		वापस 108000;

	/* vco_out */
	चयन (sctl & 0x00003000) अणु
	हाल 0x00000000:
		अगर (!(sctl & 0x00000200))
			वापस device->crystal;
		वापस 0;
	हाल 0x00002000:
		अगर (sctl & 0x00000040)
			वापस 108000;
		वापस 100000;
	हाल 0x00003000:
		/* vco_enable */
		अगर (!(sctl & 0x00000001))
			वापस 0;

		sclk = पढ़ो_vco(clk, idx);
		sभाग = ((sctl & 0x003f0000) >> 16) + 2;
		वापस (sclk * 2) / sभाग;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल u32
पढ़ो_pll(काष्ठा gt215_clk *clk, पूर्णांक idx, u32 pll)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 ctrl = nvkm_rd32(device, pll + 0);
	u32 sclk = 0, P = 1, N = 1, M = 1;
	u32 MP;

	अगर (!(ctrl & 0x00000008)) अणु
		अगर (ctrl & 0x00000001) अणु
			u32 coef = nvkm_rd32(device, pll + 4);
			M = (coef & 0x000000ff) >> 0;
			N = (coef & 0x0000ff00) >> 8;
			P = (coef & 0x003f0000) >> 16;

			/* no post-भागider on these..
			 * XXX: it looks more like two post-"dividers" that
			 * cross each other out in the शेष RPLL config */
			अगर ((pll & 0x00ff00) == 0x00e800)
				P = 1;

			sclk = पढ़ो_clk(clk, 0x00 + idx, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		sclk = पढ़ो_clk(clk, 0x10 + idx, false);
	पूर्ण

	MP = M * P;

	अगर (!MP)
		वापस 0;

	वापस sclk * N / MP;
पूर्ण

अटल पूर्णांक
gt215_clk_पढ़ो(काष्ठा nvkm_clk *base, क्रमागत nv_clk_src src)
अणु
	काष्ठा gt215_clk *clk = gt215_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 hsrc;

	चयन (src) अणु
	हाल nv_clk_src_crystal:
		वापस device->crystal;
	हाल nv_clk_src_core:
	हाल nv_clk_src_core_पूर्णांकm:
		वापस पढ़ो_pll(clk, 0x00, 0x4200);
	हाल nv_clk_src_shader:
		वापस पढ़ो_pll(clk, 0x01, 0x4220);
	हाल nv_clk_src_mem:
		वापस पढ़ो_pll(clk, 0x02, 0x4000);
	हाल nv_clk_src_disp:
		वापस पढ़ो_clk(clk, 0x20, false);
	हाल nv_clk_src_vdec:
		वापस पढ़ो_clk(clk, 0x21, false);
	हाल nv_clk_src_pmu:
		वापस पढ़ो_clk(clk, 0x25, false);
	हाल nv_clk_src_host:
		hsrc = (nvkm_rd32(device, 0xc040) & 0x30000000) >> 28;
		चयन (hsrc) अणु
		हाल 0:
			वापस पढ़ो_clk(clk, 0x1d, false);
		हाल 2:
		हाल 3:
			वापस 277000;
		शेष:
			nvkm_error(subdev, "unknown HOST clock source %d\n", hsrc);
			वापस -EINVAL;
		पूर्ण
	शेष:
		nvkm_error(subdev, "invalid clock source %d\n", src);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gt215_clk_info(काष्ठा nvkm_clk *base, पूर्णांक idx, u32 khz,
	       काष्ठा gt215_clk_info *info)
अणु
	काष्ठा gt215_clk *clk = gt215_clk(base);
	u32 oclk, sclk, sभाग;
	s32 dअगरf;

	info->clk = 0;

	चयन (khz) अणु
	हाल 27000:
		info->clk = 0x00000100;
		वापस khz;
	हाल 100000:
		info->clk = 0x00002100;
		वापस khz;
	हाल 108000:
		info->clk = 0x00002140;
		वापस khz;
	शेष:
		sclk = पढ़ो_vco(clk, idx);
		sभाग = min((sclk * 2) / khz, (u32)65);
		oclk = (sclk * 2) / sभाग;
		dअगरf = ((khz + 3000) - oclk);

		/* When imprecise, play it safe and aim क्रम a घड़ी lower than
		 * desired rather than higher */
		अगर (dअगरf < 0) अणु
			sभाग++;
			oclk = (sclk * 2) / sभाग;
		पूर्ण

		/* भागider can go as low as 2, limited here because NVIDIA
		 * and the VBIOS on my NVA8 seem to prefer using the PLL
		 * क्रम 810MHz - is there a good reason?
		 * XXX: PLLs with refclk 810MHz?  */
		अगर (sभाग > 4) अणु
			info->clk = (((sभाग - 2) << 16) | 0x00003100);
			वापस oclk;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस -दुस्फल;
पूर्ण

पूर्णांक
gt215_pll_info(काष्ठा nvkm_clk *base, पूर्णांक idx, u32 pll, u32 khz,
	       काष्ठा gt215_clk_info *info)
अणु
	काष्ठा gt215_clk *clk = gt215_clk(base);
	काष्ठा nvkm_subdev *subdev = &clk->base.subdev;
	काष्ठा nvbios_pll limits;
	पूर्णांक P, N, M, dअगरf;
	पूर्णांक ret;

	info->pll = 0;

	/* If we can get a within [-2, 3) MHz of a भागider, we'll disable the
	 * PLL and use the भागider instead. */
	ret = gt215_clk_info(&clk->base, idx, khz, info);
	dअगरf = khz - ret;
	अगर (!pll || (dअगरf >= -2000 && dअगरf < 3000)) अणु
		जाओ out;
	पूर्ण

	/* Try with PLL */
	ret = nvbios_pll_parse(subdev->device->bios, pll, &limits);
	अगर (ret)
		वापस ret;

	ret = gt215_clk_info(&clk->base, idx - 0x10, limits.refclk, info);
	अगर (ret != limits.refclk)
		वापस -EINVAL;

	ret = gt215_pll_calc(subdev, &limits, khz, &N, शून्य, &M, &P);
	अगर (ret >= 0) अणु
		info->pll = (P << 16) | (N << 8) | M;
	पूर्ण

out:
	info->fb_delay = max(((khz + 7566) / 15133), (u32) 18);
	वापस ret ? ret : -दुस्फल;
पूर्ण

अटल पूर्णांक
calc_clk(काष्ठा gt215_clk *clk, काष्ठा nvkm_cstate *cstate,
	 पूर्णांक idx, u32 pll, पूर्णांक करोm)
अणु
	पूर्णांक ret = gt215_pll_info(&clk->base, idx, pll, cstate->करोमुख्य[करोm],
				 &clk->eng[करोm]);
	अगर (ret >= 0)
		वापस 0;
	वापस ret;
पूर्ण

अटल पूर्णांक
calc_host(काष्ठा gt215_clk *clk, काष्ठा nvkm_cstate *cstate)
अणु
	पूर्णांक ret = 0;
	u32 kHz = cstate->करोमुख्य[nv_clk_src_host];
	काष्ठा gt215_clk_info *info = &clk->eng[nv_clk_src_host];

	अगर (kHz == 277000) अणु
		info->clk = 0;
		info->host_out = NVA3_HOST_277;
		वापस 0;
	पूर्ण

	info->host_out = NVA3_HOST_CLK;

	ret = gt215_clk_info(&clk->base, 0x1d, kHz, info);
	अगर (ret >= 0)
		वापस 0;

	वापस ret;
पूर्ण

पूर्णांक
gt215_clk_pre(काष्ठा nvkm_clk *clk, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा nvkm_device *device = clk->subdev.device;
	काष्ठा nvkm_fअगरo *fअगरo = device->fअगरo;

	/* halt and idle execution engines */
	nvkm_mask(device, 0x020060, 0x00070000, 0x00000000);
	nvkm_mask(device, 0x002504, 0x00000001, 0x00000001);
	/* Wait until the पूर्णांकerrupt handler is finished */
	अगर (nvkm_msec(device, 2000,
		अगर (!nvkm_rd32(device, 0x000100))
			अवरोध;
	) < 0)
		वापस -EBUSY;

	अगर (fअगरo)
		nvkm_fअगरo_छोड़ो(fअगरo, flags);

	अगर (nvkm_msec(device, 2000,
		अगर (nvkm_rd32(device, 0x002504) & 0x00000010)
			अवरोध;
	) < 0)
		वापस -EIO;

	अगर (nvkm_msec(device, 2000,
		u32 पंचांगp = nvkm_rd32(device, 0x00251c) & 0x0000003f;
		अगर (पंचांगp == 0x0000003f)
			अवरोध;
	) < 0)
		वापस -EIO;

	वापस 0;
पूर्ण

व्योम
gt215_clk_post(काष्ठा nvkm_clk *clk, अचिन्हित दीर्घ *flags)
अणु
	काष्ठा nvkm_device *device = clk->subdev.device;
	काष्ठा nvkm_fअगरo *fअगरo = device->fअगरo;

	अगर (fअगरo && flags)
		nvkm_fअगरo_start(fअगरo, flags);

	nvkm_mask(device, 0x002504, 0x00000001, 0x00000000);
	nvkm_mask(device, 0x020060, 0x00070000, 0x00040000);
पूर्ण

अटल व्योम
disable_clk_src(काष्ठा gt215_clk *clk, u32 src)
अणु
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	nvkm_mask(device, src, 0x00000100, 0x00000000);
	nvkm_mask(device, src, 0x00000001, 0x00000000);
पूर्ण

अटल व्योम
prog_pll(काष्ठा gt215_clk *clk, पूर्णांक idx, u32 pll, पूर्णांक करोm)
अणु
	काष्ठा gt215_clk_info *info = &clk->eng[करोm];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	स्थिर u32 src0 = 0x004120 + (idx * 4);
	स्थिर u32 src1 = 0x004160 + (idx * 4);
	स्थिर u32 ctrl = pll + 0;
	स्थिर u32 coef = pll + 4;
	u32 bypass;

	अगर (info->pll) अणु
		/* Always start from a non-PLL घड़ी */
		bypass = nvkm_rd32(device, ctrl)  & 0x00000008;
		अगर (!bypass) अणु
			nvkm_mask(device, src1, 0x00000101, 0x00000101);
			nvkm_mask(device, ctrl, 0x00000008, 0x00000008);
			udelay(20);
		पूर्ण

		nvkm_mask(device, src0, 0x003f3141, 0x00000101 | info->clk);
		nvkm_wr32(device, coef, info->pll);
		nvkm_mask(device, ctrl, 0x00000015, 0x00000015);
		nvkm_mask(device, ctrl, 0x00000010, 0x00000000);
		अगर (nvkm_msec(device, 2000,
			अगर (nvkm_rd32(device, ctrl) & 0x00020000)
				अवरोध;
		) < 0) अणु
			nvkm_mask(device, ctrl, 0x00000010, 0x00000010);
			nvkm_mask(device, src0, 0x00000101, 0x00000000);
			वापस;
		पूर्ण
		nvkm_mask(device, ctrl, 0x00000010, 0x00000010);
		nvkm_mask(device, ctrl, 0x00000008, 0x00000000);
		disable_clk_src(clk, src1);
	पूर्ण अन्यथा अणु
		nvkm_mask(device, src1, 0x003f3141, 0x00000101 | info->clk);
		nvkm_mask(device, ctrl, 0x00000018, 0x00000018);
		udelay(20);
		nvkm_mask(device, ctrl, 0x00000001, 0x00000000);
		disable_clk_src(clk, src0);
	पूर्ण
पूर्ण

अटल व्योम
prog_clk(काष्ठा gt215_clk *clk, पूर्णांक idx, पूर्णांक करोm)
अणु
	काष्ठा gt215_clk_info *info = &clk->eng[करोm];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	nvkm_mask(device, 0x004120 + (idx * 4), 0x003f3141, 0x00000101 | info->clk);
पूर्ण

अटल व्योम
prog_host(काष्ठा gt215_clk *clk)
अणु
	काष्ठा gt215_clk_info *info = &clk->eng[nv_clk_src_host];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 hsrc = (nvkm_rd32(device, 0xc040));

	चयन (info->host_out) अणु
	हाल NVA3_HOST_277:
		अगर ((hsrc & 0x30000000) == 0) अणु
			nvkm_wr32(device, 0xc040, hsrc | 0x20000000);
			disable_clk_src(clk, 0x4194);
		पूर्ण
		अवरोध;
	हाल NVA3_HOST_CLK:
		prog_clk(clk, 0x1d, nv_clk_src_host);
		अगर ((hsrc & 0x30000000) >= 0x20000000) अणु
			nvkm_wr32(device, 0xc040, hsrc & ~0x30000000);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* This seems to be a घड़ी gating factor on idle, always set to 64 */
	nvkm_wr32(device, 0xc044, 0x3e);
पूर्ण

अटल व्योम
prog_core(काष्ठा gt215_clk *clk, पूर्णांक करोm)
अणु
	काष्ठा gt215_clk_info *info = &clk->eng[करोm];
	काष्ठा nvkm_device *device = clk->base.subdev.device;
	u32 fb_delay = nvkm_rd32(device, 0x10002c);

	अगर (fb_delay < info->fb_delay)
		nvkm_wr32(device, 0x10002c, info->fb_delay);

	prog_pll(clk, 0x00, 0x004200, करोm);

	अगर (fb_delay > info->fb_delay)
		nvkm_wr32(device, 0x10002c, info->fb_delay);
पूर्ण

अटल पूर्णांक
gt215_clk_calc(काष्ठा nvkm_clk *base, काष्ठा nvkm_cstate *cstate)
अणु
	काष्ठा gt215_clk *clk = gt215_clk(base);
	काष्ठा gt215_clk_info *core = &clk->eng[nv_clk_src_core];
	पूर्णांक ret;

	अगर ((ret = calc_clk(clk, cstate, 0x10, 0x4200, nv_clk_src_core)) ||
	    (ret = calc_clk(clk, cstate, 0x11, 0x4220, nv_clk_src_shader)) ||
	    (ret = calc_clk(clk, cstate, 0x20, 0x0000, nv_clk_src_disp)) ||
	    (ret = calc_clk(clk, cstate, 0x21, 0x0000, nv_clk_src_vdec)) ||
	    (ret = calc_host(clk, cstate)))
		वापस ret;

	/* XXX: Should be पढ़ोing the highest bit in the VBIOS घड़ी to decide
	 * whether to use a PLL or not... but using a PLL defeats the purpose */
	अगर (core->pll) अणु
		ret = gt215_clk_info(&clk->base, 0x10,
				     cstate->करोमुख्य[nv_clk_src_core_पूर्णांकm],
				     &clk->eng[nv_clk_src_core_पूर्णांकm]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
gt215_clk_prog(काष्ठा nvkm_clk *base)
अणु
	काष्ठा gt215_clk *clk = gt215_clk(base);
	काष्ठा gt215_clk_info *core = &clk->eng[nv_clk_src_core];
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ *f = &flags;

	ret = gt215_clk_pre(&clk->base, f);
	अगर (ret)
		जाओ out;

	अगर (core->pll)
		prog_core(clk, nv_clk_src_core_पूर्णांकm);

	prog_core(clk,  nv_clk_src_core);
	prog_pll(clk, 0x01, 0x004220, nv_clk_src_shader);
	prog_clk(clk, 0x20, nv_clk_src_disp);
	prog_clk(clk, 0x21, nv_clk_src_vdec);
	prog_host(clk);

out:
	अगर (ret == -EBUSY)
		f = शून्य;

	gt215_clk_post(&clk->base, f);
	वापस ret;
पूर्ण

अटल व्योम
gt215_clk_tidy(काष्ठा nvkm_clk *base)
अणु
पूर्ण

अटल स्थिर काष्ठा nvkm_clk_func
gt215_clk = अणु
	.पढ़ो = gt215_clk_पढ़ो,
	.calc = gt215_clk_calc,
	.prog = gt215_clk_prog,
	.tidy = gt215_clk_tidy,
	.करोमुख्यs = अणु
		अणु nv_clk_src_crystal  , 0xff पूर्ण,
		अणु nv_clk_src_core     , 0x00, 0, "core", 1000 पूर्ण,
		अणु nv_clk_src_shader   , 0x01, 0, "shader", 1000 पूर्ण,
		अणु nv_clk_src_mem      , 0x02, 0, "memory", 1000 पूर्ण,
		अणु nv_clk_src_vdec     , 0x03 पूर्ण,
		अणु nv_clk_src_disp     , 0x04 पूर्ण,
		अणु nv_clk_src_host     , 0x05 पूर्ण,
		अणु nv_clk_src_core_पूर्णांकm, 0x06 पूर्ण,
		अणु nv_clk_src_max पूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gt215_clk_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst,
	      काष्ठा nvkm_clk **pclk)
अणु
	काष्ठा gt215_clk *clk;

	अगर (!(clk = kzalloc(माप(*clk), GFP_KERNEL)))
		वापस -ENOMEM;
	*pclk = &clk->base;

	वापस nvkm_clk_ctor(&gt215_clk, device, type, inst, true, &clk->base);
पूर्ण
