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
#समावेश "gf100.h"

स्थिर काष्ठा nvkm_specsrc
gf100_pbfb_sources[] = अणु
	अणु 0x10f100, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x1, 0, "unk0" पूर्ण,
			अणु 0x3f, 4, "unk4" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pbfb_broadcast_pm_unk100" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_specsrc
gf100_pmfb_sources[] = अणु
	अणु 0x140028, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3fff, 0, "unk0" पूर्ण,
			अणु 0x7, 16, "unk16" पूर्ण,
			अणु 0x3, 24, "unk24" पूर्ण,
			अणु 0x2, 29, "unk29" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pmfb0_pm_unk28" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
gf100_l1_sources[] = अणु
	अणु 0x5044a8, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3f, 0, "sel", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_gpc0_tpc0_l1_pm_mux" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
gf100_tex_sources[] = अणु
	अणु 0x5042c0, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0xf, 0, "sel0", true पूर्ण,
			अणु 0x7, 8, "sel1", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_gpc0_tpc0_tex_pm_mux_c_d" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
gf100_unk400_sources[] = अणु
	अणु 0x50440c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3f, 0, "sel", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_gpc0_tpc0_unk400_pm_mux" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
gf100_pm_hub[] = अणु
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_specकरोm
gf100_pm_gpc[] = अणु
	अणु 0xe0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x00, "gpc00_l1_00", gf100_l1_sources पूर्ण,
			अणु 0x01, "gpc00_l1_01", gf100_l1_sources पूर्ण,
			अणु 0x02, "gpc00_l1_02", gf100_l1_sources पूर्ण,
			अणु 0x03, "gpc00_l1_03", gf100_l1_sources पूर्ण,
			अणु 0x05, "gpc00_l1_04", gf100_l1_sources पूर्ण,
			अणु 0x06, "gpc00_l1_05", gf100_l1_sources पूर्ण,
			अणु 0x0a, "gpc00_tex_00", gf100_tex_sources पूर्ण,
			अणु 0x0b, "gpc00_tex_01", gf100_tex_sources पूर्ण,
			अणु 0x0c, "gpc00_tex_02", gf100_tex_sources पूर्ण,
			अणु 0x0d, "gpc00_tex_03", gf100_tex_sources पूर्ण,
			अणु 0x0e, "gpc00_tex_04", gf100_tex_sources पूर्ण,
			अणु 0x0f, "gpc00_tex_05", gf100_tex_sources पूर्ण,
			अणु 0x10, "gpc00_tex_06", gf100_tex_sources पूर्ण,
			अणु 0x11, "gpc00_tex_07", gf100_tex_sources पूर्ण,
			अणु 0x12, "gpc00_tex_08", gf100_tex_sources पूर्ण,
			अणु 0x26, "gpc00_unk400_00", gf100_unk400_sources पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
gf100_pm_part[] = अणु
	अणु 0xe0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x0f, "part00_pbfb_00", gf100_pbfb_sources पूर्ण,
			अणु 0x10, "part00_pbfb_01", gf100_pbfb_sources पूर्ण,
			अणु 0x21, "part00_pmfb_00", gf100_pmfb_sources पूर्ण,
			अणु 0x04, "part00_pmfb_01", gf100_pmfb_sources पूर्ण,
			अणु 0x00, "part00_pmfb_02", gf100_pmfb_sources पूर्ण,
			अणु 0x02, "part00_pmfb_03", gf100_pmfb_sources पूर्ण,
			अणु 0x01, "part00_pmfb_04", gf100_pmfb_sources पूर्ण,
			अणु 0x2e, "part00_pmfb_05", gf100_pmfb_sources पूर्ण,
			अणु 0x2f, "part00_pmfb_06", gf100_pmfb_sources पूर्ण,
			अणु 0x1b, "part00_pmfb_07", gf100_pmfb_sources पूर्ण,
			अणु 0x1c, "part00_pmfb_08", gf100_pmfb_sources पूर्ण,
			अणु 0x1d, "part00_pmfb_09", gf100_pmfb_sources पूर्ण,
			अणु 0x1e, "part00_pmfb_0a", gf100_pmfb_sources पूर्ण,
			अणु 0x1f, "part00_pmfb_0b", gf100_pmfb_sources पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
gf100_perfctr_init(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfकरोm *करोm,
		   काष्ठा nvkm_perfctr *ctr)
अणु
	काष्ठा nvkm_device *device = pm->engine.subdev.device;
	u32 log = ctr->logic_op;
	u32 src = 0x00000000;
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++)
		src |= ctr->संकेत[i] << (i * 8);

	nvkm_wr32(device, करोm->addr + 0x09c, 0x00040002 | (करोm->mode << 3));
	nvkm_wr32(device, करोm->addr + 0x100, 0x00000000);
	nvkm_wr32(device, करोm->addr + 0x040 + (ctr->slot * 0x08), src);
	nvkm_wr32(device, करोm->addr + 0x044 + (ctr->slot * 0x08), log);
पूर्ण

अटल व्योम
gf100_perfctr_पढ़ो(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfकरोm *करोm,
		   काष्ठा nvkm_perfctr *ctr)
अणु
	काष्ठा nvkm_device *device = pm->engine.subdev.device;

	चयन (ctr->slot) अणु
	हाल 0: ctr->ctr = nvkm_rd32(device, करोm->addr + 0x08c); अवरोध;
	हाल 1: ctr->ctr = nvkm_rd32(device, करोm->addr + 0x088); अवरोध;
	हाल 2: ctr->ctr = nvkm_rd32(device, करोm->addr + 0x080); अवरोध;
	हाल 3: ctr->ctr = nvkm_rd32(device, करोm->addr + 0x090); अवरोध;
	पूर्ण
	करोm->clk = nvkm_rd32(device, करोm->addr + 0x070);
पूर्ण

अटल व्योम
gf100_perfctr_next(काष्ठा nvkm_pm *pm, काष्ठा nvkm_perfकरोm *करोm)
अणु
	काष्ठा nvkm_device *device = pm->engine.subdev.device;
	nvkm_wr32(device, करोm->addr + 0x06c, करोm->संकेत_nr - 0x40 + 0x27);
	nvkm_wr32(device, करोm->addr + 0x0ec, 0x00000011);
पूर्ण

स्थिर काष्ठा nvkm_funcकरोm
gf100_perfctr_func = अणु
	.init = gf100_perfctr_init,
	.पढ़ो = gf100_perfctr_पढ़ो,
	.next = gf100_perfctr_next,
पूर्ण;

अटल व्योम
gf100_pm_fini(काष्ठा nvkm_pm *pm)
अणु
	काष्ठा nvkm_device *device = pm->engine.subdev.device;
	nvkm_mask(device, 0x000200, 0x10000000, 0x00000000);
	nvkm_mask(device, 0x000200, 0x10000000, 0x10000000);
पूर्ण

अटल स्थिर काष्ठा nvkm_pm_func
gf100_pm_ = अणु
	.fini = gf100_pm_fini,
पूर्ण;

पूर्णांक
gf100_pm_new_(स्थिर काष्ठा gf100_pm_func *func, काष्ठा nvkm_device *device,
	      क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	काष्ठा nvkm_pm *pm;
	u32 mask;
	पूर्णांक ret;

	अगर (!(pm = *ppm = kzalloc(माप(*pm), GFP_KERNEL)))
		वापस -ENOMEM;

	ret = nvkm_pm_ctor(&gf100_pm_, device, type, inst, pm);
	अगर (ret)
		वापस ret;

	/* HUB */
	ret = nvkm_perfकरोm_new(pm, "hub", 0, 0x1b0000, 0, 0x200,
			       func->करोms_hub);
	अगर (ret)
		वापस ret;

	/* GPC */
	mask  = (1 << nvkm_rd32(device, 0x022430)) - 1;
	mask &= ~nvkm_rd32(device, 0x022504);
	mask &= ~nvkm_rd32(device, 0x022584);

	ret = nvkm_perfकरोm_new(pm, "gpc", mask, 0x180000,
			       0x1000, 0x200, func->करोms_gpc);
	अगर (ret)
		वापस ret;

	/* PART */
	mask  = (1 << nvkm_rd32(device, 0x022438)) - 1;
	mask &= ~nvkm_rd32(device, 0x022548);
	mask &= ~nvkm_rd32(device, 0x0225c8);

	ret = nvkm_perfकरोm_new(pm, "part", mask, 0x1a0000,
			       0x1000, 0x200, func->करोms_part);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा gf100_pm_func
gf100_pm = अणु
	.करोms_gpc = gf100_pm_gpc,
	.करोms_hub = gf100_pm_hub,
	.करोms_part = gf100_pm_part,
पूर्ण;

पूर्णांक
gf100_pm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	वापस gf100_pm_new_(&gf100_pm, device, type, inst, ppm);
पूर्ण
