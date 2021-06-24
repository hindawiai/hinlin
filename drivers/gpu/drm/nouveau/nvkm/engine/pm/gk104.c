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

अटल स्थिर काष्ठा nvkm_specsrc
gk104_pmfb_sources[] = अणु
	अणु 0x140028, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3fff, 0, "unk0" पूर्ण,
			अणु 0x7, 16, "unk16" पूर्ण,
			अणु 0x3, 24, "unk24" पूर्ण,
			अणु 0x2, 28, "unk28" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pmfb0_pm_unk28" पूर्ण,
	अणु 0x14125c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3fff, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pmfb0_subp0_pm_unk25c" पूर्ण,
	अणु 0x14165c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3fff, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pmfb0_subp1_pm_unk25c" पूर्ण,
	अणु 0x141a5c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3fff, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pmfb0_subp2_pm_unk25c" पूर्ण,
	अणु 0x141e5c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3fff, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pmfb0_subp3_pm_unk25c" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
gk104_tex_sources[] = अणु
	अणु 0x5042c0, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0xf, 0, "sel0", true पूर्ण,
			अणु 0x7, 8, "sel1", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_gpc0_tpc0_tex_pm_mux_c_d" पूर्ण,
	अणु 0x5042c8, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x1f, 0, "sel", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_gpc0_tpc0_tex_pm_unkc8" पूर्ण,
	अणु 0x5042b8, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0xff, 0, "sel", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_gpc0_tpc0_tex_pm_unkb8" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
gk104_pm_hub[] = अणु
	अणु 0x60, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x47, "hub00_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x40, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x27, "hub01_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x60, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x47, "hub02_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x60, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x47, "hub03_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x40, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x03, "host_mmio_rd" पूर्ण,
			अणु 0x27, "hub04_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x60, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x47, "hub05_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0xc0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x74, "host_fb_rd3x" पूर्ण,
			अणु 0x75, "host_fb_rd3x_2" पूर्ण,
			अणु 0xa7, "hub06_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x60, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x47, "hub07_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
gk104_pm_gpc[] = अणु
	अणु 0xe0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0xc7, "gpc00_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x00, "gpc02_tex_00", gk104_tex_sources पूर्ण,
			अणु 0x01, "gpc02_tex_01", gk104_tex_sources पूर्ण,
			अणु 0x02, "gpc02_tex_02", gk104_tex_sources पूर्ण,
			अणु 0x03, "gpc02_tex_03", gk104_tex_sources पूर्ण,
			अणु 0x04, "gpc02_tex_04", gk104_tex_sources पूर्ण,
			अणु 0x05, "gpc02_tex_05", gk104_tex_sources पूर्ण,
			अणु 0x06, "gpc02_tex_06", gk104_tex_sources पूर्ण,
			अणु 0x07, "gpc02_tex_07", gk104_tex_sources पूर्ण,
			अणु 0x08, "gpc02_tex_08", gk104_tex_sources पूर्ण,
			अणु 0x0a, "gpc02_tex_0a", gk104_tex_sources पूर्ण,
			अणु 0x0b, "gpc02_tex_0b", gk104_tex_sources पूर्ण,
			अणु 0x0d, "gpc02_tex_0c", gk104_tex_sources पूर्ण,
			अणु 0x0c, "gpc02_tex_0d", gk104_tex_sources पूर्ण,
			अणु 0x0e, "gpc02_tex_0e", gk104_tex_sources पूर्ण,
			अणु 0x0f, "gpc02_tex_0f", gk104_tex_sources पूर्ण,
			अणु 0x10, "gpc02_tex_10", gk104_tex_sources पूर्ण,
			अणु 0x11, "gpc02_tex_11", gk104_tex_sources पूर्ण,
			अणु 0x12, "gpc02_tex_12", gk104_tex_sources पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
gk104_pm_part[] = अणु
	अणु 0x60, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x00, "part00_pbfb_00", gf100_pbfb_sources पूर्ण,
			अणु 0x01, "part00_pbfb_01", gf100_pbfb_sources पूर्ण,
			अणु 0x0c, "part00_pmfb_00", gk104_pmfb_sources पूर्ण,
			अणु 0x0d, "part00_pmfb_01", gk104_pmfb_sources पूर्ण,
			अणु 0x0e, "part00_pmfb_02", gk104_pmfb_sources पूर्ण,
			अणु 0x0f, "part00_pmfb_03", gk104_pmfb_sources पूर्ण,
			अणु 0x10, "part00_pmfb_04", gk104_pmfb_sources पूर्ण,
			अणु 0x12, "part00_pmfb_05", gk104_pmfb_sources पूर्ण,
			अणु 0x15, "part00_pmfb_06", gk104_pmfb_sources पूर्ण,
			अणु 0x16, "part00_pmfb_07", gk104_pmfb_sources पूर्ण,
			अणु 0x18, "part00_pmfb_08", gk104_pmfb_sources पूर्ण,
			अणु 0x21, "part00_pmfb_09", gk104_pmfb_sources पूर्ण,
			अणु 0x25, "part00_pmfb_0a", gk104_pmfb_sources पूर्ण,
			अणु 0x26, "part00_pmfb_0b", gk104_pmfb_sources पूर्ण,
			अणु 0x27, "part00_pmfb_0c", gk104_pmfb_sources पूर्ण,
			अणु 0x47, "part00_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणु 0x60, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x47, "part01_user_0" पूर्ण,
			अणुपूर्ण
		पूर्ण, &gf100_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_pm_func
gk104_pm = अणु
	.करोms_gpc = gk104_pm_gpc,
	.करोms_hub = gk104_pm_hub,
	.करोms_part = gk104_pm_part,
पूर्ण;

पूर्णांक
gk104_pm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	वापस gf100_pm_new_(&gk104_pm, device, type, inst, ppm);
पूर्ण
