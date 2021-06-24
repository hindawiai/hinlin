<शैली गुरु>
/*
 * Copyright 2019 Red Hat Inc.
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
#समावेश "ctxgf100.h"

अटल व्योम
tu102_grctx_generate_r419c0c(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_mask(device, 0x419c0c, 0x80000000, 0x80000000);
	nvkm_mask(device, 0x40584c, 0x00000008, 0x00000000);
	nvkm_mask(device, 0x400080, 0x00000000, 0x00000000);
पूर्ण

अटल व्योम
tu102_grctx_generate_sm_id(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc, पूर्णांक sm)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x608), sm);
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x088), sm);
पूर्ण

अटल स्थिर काष्ठा gf100_gr_init
tu102_grctx_init_unknown_bundle_init_0[] = अणु
	अणु 0x00001000,  1, 0x00000001, 0x00000004 पूर्ण,
	अणु 0x00002020, 64, 0x00000001, 0x00000000 पूर्ण,
	अणु 0x0001e100,  1, 0x00000001, 0x00000001 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
tu102_grctx_pack_sw_veid_bundle_init[] = अणु
	अणु gv100_grctx_init_sw_veid_bundle_init_0 पूर्ण,
	अणु tu102_grctx_init_unknown_bundle_init_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल व्योम
tu102_grctx_generate_attrib(काष्ठा gf100_grctx *info)
अणु
	स्थिर u64 size = 0x80000; /*XXX: educated guess */
	स्थिर पूर्णांक s = 8;
	स्थिर पूर्णांक b = mmio_vram(info, size, (1 << s), true);

	gv100_grctx_generate_attrib(info);

	mmio_refn(info, 0x408070, 0x00000000, s, b);
	mmio_wr32(info, 0x408074, size >> s); /*XXX: guess */
	mmio_refn(info, 0x419034, 0x00000000, s, b);
	mmio_wr32(info, 0x408078, 0x00000000);
पूर्ण

स्थिर काष्ठा gf100_grctx_func
tu102_grctx = अणु
	.unkn88c = gv100_grctx_unkn88c,
	.मुख्य = gf100_grctx_generate_मुख्य,
	.unkn = gv100_grctx_generate_unkn,
	.sw_veid_bundle_init = tu102_grctx_pack_sw_veid_bundle_init,
	.bundle = gm107_grctx_generate_bundle,
	.bundle_size = 0x3000,
	.bundle_min_gpm_fअगरo_depth = 0x180,
	.bundle_token_limit = 0xa80,
	.pagepool = gp100_grctx_generate_pagepool,
	.pagepool_size = 0x20000,
	.attrib = tu102_grctx_generate_attrib,
	.attrib_nr_max = 0x800,
	.attrib_nr = 0x700,
	.alpha_nr_max = 0xc00,
	.alpha_nr = 0x800,
	.gfxp_nr = 0xfa8,
	.sm_id = tu102_grctx_generate_sm_id,
	.skip_pd_num_tpc_per_gpc = true,
	.rop_mapping = gv100_grctx_generate_rop_mapping,
	.r406500 = gm200_grctx_generate_r406500,
	.r400088 = gv100_grctx_generate_r400088,
	.r419c0c = tu102_grctx_generate_r419c0c,
पूर्ण;
