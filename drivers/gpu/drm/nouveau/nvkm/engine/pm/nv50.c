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
nv50_zcull_sources[] = अणु
	अणु 0x402ca4, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x7fff, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_zcull_pm_unka4" पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा nvkm_specsrc
nv50_zrop_sources[] = अणु
	अणु 0x40708c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0xf, 0, "sel0", true पूर्ण,
			अणु 0xf, 16, "sel1", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_rop0_zrop_pm_mux" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
nv50_prop_sources[] = अणु
	अणु 0x40be50, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x1f, 0, "sel", true पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_tpc3_prop_pm_mux" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
nv50_crop_sources[] = अणु
        अणु 0x407008, (स्थिर काष्ठा nvkm_specmux[]) अणु
                        अणु 0x7, 0, "sel0", true पूर्ण,
                        अणु 0x7, 16, "sel1", true पूर्ण,
                        अणुपूर्ण
                पूर्ण, "pgraph_rop0_crop_pm_mux" पूर्ण,
        अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
nv50_tex_sources[] = अणु
	अणु 0x40b808, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x3fff, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_tpc3_tex_unk08" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specsrc
nv50_vfetch_sources[] = अणु
	अणु 0x400c0c, (स्थिर काष्ठा nvkm_specmux[]) अणु
			अणु 0x1, 0, "unk0" पूर्ण,
			अणुपूर्ण
		पूर्ण, "pgraph_vfetch_unk0c" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा nvkm_specकरोm
nv50_pm[] = अणु
	अणु 0x20, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0xf0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0xc8, "pc01_gr_idle" पूर्ण,
			अणु 0x7f, "pc01_strmout_00" पूर्ण,
			अणु 0x80, "pc01_strmout_01" पूर्ण,
			अणु 0xdc, "pc01_trast_00" पूर्ण,
			अणु 0xdd, "pc01_trast_01" पूर्ण,
			अणु 0xde, "pc01_trast_02" पूर्ण,
			अणु 0xdf, "pc01_trast_03" पूर्ण,
			अणु 0xe2, "pc01_trast_04" पूर्ण,
			अणु 0xe3, "pc01_trast_05" पूर्ण,
			अणु 0x7c, "pc01_vattr_00" पूर्ण,
			अणु 0x7d, "pc01_vattr_01" पूर्ण,
			अणु 0x26, "pc01_vfetch_00", nv50_vfetch_sources पूर्ण,
			अणु 0x27, "pc01_vfetch_01", nv50_vfetch_sources पूर्ण,
			अणु 0x28, "pc01_vfetch_02", nv50_vfetch_sources पूर्ण,
			अणु 0x29, "pc01_vfetch_03", nv50_vfetch_sources पूर्ण,
			अणु 0x2a, "pc01_vfetch_04", nv50_vfetch_sources पूर्ण,
			अणु 0x2b, "pc01_vfetch_05", nv50_vfetch_sources पूर्ण,
			अणु 0x2c, "pc01_vfetch_06", nv50_vfetch_sources पूर्ण,
			अणु 0x2d, "pc01_vfetch_07", nv50_vfetch_sources पूर्ण,
			अणु 0x2e, "pc01_vfetch_08", nv50_vfetch_sources पूर्ण,
			अणु 0x2f, "pc01_vfetch_09", nv50_vfetch_sources पूर्ण,
			अणु 0x30, "pc01_vfetch_0a", nv50_vfetch_sources पूर्ण,
			अणु 0x31, "pc01_vfetch_0b", nv50_vfetch_sources पूर्ण,
			अणु 0x32, "pc01_vfetch_0c", nv50_vfetch_sources पूर्ण,
			अणु 0x33, "pc01_vfetch_0d", nv50_vfetch_sources पूर्ण,
			अणु 0x34, "pc01_vfetch_0e", nv50_vfetch_sources पूर्ण,
			अणु 0x35, "pc01_vfetch_0f", nv50_vfetch_sources पूर्ण,
			अणु 0x36, "pc01_vfetch_10", nv50_vfetch_sources पूर्ण,
			अणु 0x37, "pc01_vfetch_11", nv50_vfetch_sources पूर्ण,
			अणु 0x38, "pc01_vfetch_12", nv50_vfetch_sources पूर्ण,
			अणु 0x39, "pc01_vfetch_13", nv50_vfetch_sources पूर्ण,
			अणु 0x3a, "pc01_vfetch_14", nv50_vfetch_sources पूर्ण,
			अणु 0x3b, "pc01_vfetch_15", nv50_vfetch_sources पूर्ण,
			अणु 0x3c, "pc01_vfetch_16", nv50_vfetch_sources पूर्ण,
			अणु 0x3d, "pc01_vfetch_17", nv50_vfetch_sources पूर्ण,
			अणु 0x3e, "pc01_vfetch_18", nv50_vfetch_sources पूर्ण,
			अणु 0x3f, "pc01_vfetch_19", nv50_vfetch_sources पूर्ण,
			अणु 0x20, "pc01_zcull_00", nv50_zcull_sources पूर्ण,
			अणु 0x21, "pc01_zcull_01", nv50_zcull_sources पूर्ण,
			अणु 0x22, "pc01_zcull_02", nv50_zcull_sources पूर्ण,
			अणु 0x23, "pc01_zcull_03", nv50_zcull_sources पूर्ण,
			अणु 0x24, "pc01_zcull_04", nv50_zcull_sources पूर्ण,
			अणु 0x25, "pc01_zcull_05", nv50_zcull_sources पूर्ण,
			अणु 0xae, "pc01_unk00" पूर्ण,
			अणु 0xee, "pc01_trailer" पूर्ण,
			अणुपूर्ण
		पूर्ण, &nv40_perfctr_func पूर्ण,
	अणु 0xf0, (स्थिर काष्ठा nvkm_specsig[]) अणु
			अणु 0x52, "pc02_crop_00", nv50_crop_sources पूर्ण,
			अणु 0x53, "pc02_crop_01", nv50_crop_sources पूर्ण,
			अणु 0x54, "pc02_crop_02", nv50_crop_sources पूर्ण,
			अणु 0x55, "pc02_crop_03", nv50_crop_sources पूर्ण,
			अणु 0x00, "pc02_prop_00", nv50_prop_sources पूर्ण,
			अणु 0x01, "pc02_prop_01", nv50_prop_sources पूर्ण,
			अणु 0x02, "pc02_prop_02", nv50_prop_sources पूर्ण,
			अणु 0x03, "pc02_prop_03", nv50_prop_sources पूर्ण,
			अणु 0x04, "pc02_prop_04", nv50_prop_sources पूर्ण,
			अणु 0x05, "pc02_prop_05", nv50_prop_sources पूर्ण,
			अणु 0x06, "pc02_prop_06", nv50_prop_sources पूर्ण,
			अणु 0x07, "pc02_prop_07", nv50_prop_sources पूर्ण,
			अणु 0x70, "pc02_tex_00", nv50_tex_sources पूर्ण,
			अणु 0x71, "pc02_tex_01", nv50_tex_sources पूर्ण,
			अणु 0x72, "pc02_tex_02", nv50_tex_sources पूर्ण,
			अणु 0x73, "pc02_tex_03", nv50_tex_sources पूर्ण,
			अणु 0x40, "pc02_tex_04", nv50_tex_sources पूर्ण,
			अणु 0x41, "pc02_tex_05", nv50_tex_sources पूर्ण,
			अणु 0x42, "pc02_tex_06", nv50_tex_sources पूर्ण,
			अणु 0x6c, "pc02_zrop_00", nv50_zrop_sources पूर्ण,
			अणु 0x6d, "pc02_zrop_01", nv50_zrop_sources पूर्ण,
			अणु 0x6e, "pc02_zrop_02", nv50_zrop_sources पूर्ण,
			अणु 0x6f, "pc02_zrop_03", nv50_zrop_sources पूर्ण,
			अणु 0xee, "pc02_trailer" पूर्ण,
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
nv50_pm_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_pm **ppm)
अणु
	वापस nv40_pm_new_(nv50_pm, device, type, inst, ppm);
पूर्ण
