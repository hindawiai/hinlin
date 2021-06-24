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
#समावेश "nv40.h"

स्थिर काष्ठा nvkm_specsrc
g84_vfetch_sources[] = अणु
	अणु 0x400c0c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_vfetch_unk0c" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
g84_prop_sources[] = अणु
	अणु 0x408e50, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x1f, 0, "sel", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_tpc0_prop_pm_mux" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
g84_crop_sources[] = अणु
	अणु 0x407008, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0xf, 0, "sel0", true पूर्ण,
			अणु 0x7, 16, "sel1", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_rop0_crop_pm_mux" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
g84_tex_sources[] = अणु
	अणु 0x408808, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0xfffff, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_tpc0_tex_unk08" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
g84_pm[] = अणु
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0xf0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0xbd, "pc01_gr_idle" पूर्ण,
			अणु 0x5e, "pc01_strmout_00" पूर्ण,
			अणु 0x5f, "pc01_strmout_01" पूर्ण,
			अणु 0xd2, "pc01_trast_00" पूर्ण,
			अणु 0xd3, "pc01_trast_01" पूर्ण,
			अणु 0xd4, "pc01_trast_02" पूर्ण,
			अणु 0xd5, "pc01_trast_03" पूर्ण,
			अणु 0xd8, "pc01_trast_04" पूर्ण,
			अणु 0xd9, "pc01_trast_05" पूर्ण,
			अणु 0x5c, "pc01_vattr_00" पूर्ण,
			अणु 0x5d, "pc01_vattr_01" पूर्ण,
			अणु 0x66, "pc01_vfetch_00", g84_vfetch_sources पूर्ण,
			अणु 0x67, "pc01_vfetch_01", g84_vfetch_sources पूर्ण,
			अणु 0x68, "pc01_vfetch_02", g84_vfetch_sources पूर्ण,
			अणु 0x69, "pc01_vfetch_03", g84_vfetch_sources पूर्ण,
			अणु 0x6a, "pc01_vfetch_04", g84_vfetch_sources पूर्ण,
			अणु 0x6b, "pc01_vfetch_05", g84_vfetch_sources पूर्ण,
			अणु 0x6c, "pc01_vfetch_06", g84_vfetch_sources पूर्ण,
			अणु 0x6d, "pc01_vfetch_07", g84_vfetch_sources पूर्ण,
			अणु 0x6e, "pc01_vfetch_08", g84_vfetch_sources पूर्ण,
			अणु 0x6f, "pc01_vfetch_09", g84_vfetch_sources पूर्ण,
			अणु 0x70, "pc01_vfetch_0a", g84_vfetch_sources पूर्ण,
			अणु 0x71, "pc01_vfetch_0b", g84_vfetch_sources पूर्ण,
			अणु 0x72, "pc01_vfetch_0c", g84_vfetch_sources पूर्ण,
			अणु 0x73, "pc01_vfetch_0d", g84_vfetch_sources पूर्ण,
			अणु 0x74, "pc01_vfetch_0e", g84_vfetch_sources पूर्ण,
			अणु 0x75, "pc01_vfetch_0f", g84_vfetch_sources पूर्ण,
			अणु 0x76, "pc01_vfetch_10", g84_vfetch_sources पूर्ण,
			अणु 0x77, "pc01_vfetch_11", g84_vfetch_sources पूर्ण,
			अणु 0x78, "pc01_vfetch_12", g84_vfetch_sources पूर्ण,
			अणु 0x79, "pc01_vfetch_13", g84_vfetch_sources पूर्ण,
			अणु 0x7a, "pc01_vfetch_14", g84_vfetch_sources पूर्ण,
			अणु 0x7b, "pc01_vfetch_15", g84_vfetch_sources पूर्ण,
			अणु 0x7c, "pc01_vfetch_16", g84_vfetch_sources पूर्ण,
			अणु 0x7d, "pc01_vfetch_17", g84_vfetch_sources पूर्ण,
			अणु 0x7e, "pc01_vfetch_18", g84_vfetch_sources पूर्ण,
			अणु 0x7f, "pc01_vfetch_19", g84_vfetch_sources पूर्ण,
			अणु 0x07, "pc01_zcull_00", nv50_zcull_sources पूर्ण,
			अणु 0x08, "pc01_zcull_01", nv50_zcull_sources पूर्ण,
			अणु 0x09, "pc01_zcull_02", nv50_zcull_sources पूर्ण,
			अणु 0x0a, "pc01_zcull_03", nv50_zcull_sources पूर्ण,
			अणु 0x0b, "pc01_zcull_04", nv50_zcull_sources पूर्ण,
			अणु 0x0c, "pc01_zcull_05", nv50_zcull_sources पूर्ण,
			अणु 0xa4, "pc01_unk00" पूर्ण,
			अणु 0xec, "pc01_trailer" पूर्ण,
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0xa0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x30, "pc02_crop_00", g84_crop_sources पूर्ण,
			अणु 0x31, "pc02_crop_01", g84_crop_sources पूर्ण,
			अणु 0x32, "pc02_crop_02", g84_crop_sources पूर्ण,
			अणु 0x33, "pc02_crop_03", g84_crop_sources पूर्ण,
			अणु 0x00, "pc02_prop_00", g84_prop_sources पूर्ण,
			अणु 0x01, "pc02_prop_01", g84_prop_sources पूर्ण,
			अणु 0x02, "pc02_prop_02", g84_prop_sources पूर्ण,
			अणु 0x03, "pc02_prop_03", g84_prop_sources पूर्ण,
			अणु 0x04, "pc02_prop_04", g84_prop_sources पूर्ण,
			अणु 0x05, "pc02_prop_05", g84_prop_sources पूर्ण,
			अणु 0x06, "pc02_prop_06", g84_prop_sources पूर्ण,
			अणु 0x07, "pc02_prop_07", g84_prop_sources पूर्ण,
			अणु 0x48, "pc02_tex_00", g84_tex_sources पूर्ण,
			अणु 0x49, "pc02_tex_01", g84_tex_sources पूर्ण,
			अणु 0x4a, "pc02_tex_02", g84_tex_sources पूर्ण,
			अणु 0x4b, "pc02_tex_03", g84_tex_sources पूर्ण,
			अणु 0x1a, "pc02_tex_04", g84_tex_sources पूर्ण,
			अणु 0x1b, "pc02_tex_05", g84_tex_sources पूर्ण,
			अणु 0x1c, "pc02_tex_06", g84_tex_sources पूर्ण,
			अणु 0x44, "pc02_zrop_00", nv50_zrop_sources पूर्ण,
			अणु 0x45, "pc02_zrop_01", nv50_zrop_sources पूर्ण,
			अणु 0x46, "pc02_zrop_02", nv50_zrop_sources पूर्ण,
			अणु 0x47, "pc02_zrop_03", nv50_zrop_sources पूर्ण,
			अणु 0x8c, "pc02_trailer" पूर्ण,
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
g84_pm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	वापस nv40_pm_new_(g84_pm, device, type, inst, ppm);
पूर्ण
