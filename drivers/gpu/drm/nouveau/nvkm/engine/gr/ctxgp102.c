<शैली गुरु>
/*
 * Copyright 2016 Red Hat Inc.
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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "ctxgf100.h"

#समावेश <subdev/fb.h>

/*******************************************************************************
 * PGRAPH context implementation
 ******************************************************************************/

अटल व्योम
gp102_grctx_generate_r408840(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_mask(device, 0x408840, 0x00000003, 0x00000000);
पूर्ण

व्योम
gp102_grctx_generate_attrib(काष्ठा gf100_grctx *info)
अणु
	काष्ठा gf100_gr *gr = info->gr;
	स्थिर काष्ठा gf100_grctx_func *grctx = gr->func->grctx;
	स्थिर u32  alpha = grctx->alpha_nr;
	स्थिर u32 attrib = grctx->attrib_nr;
	स्थिर u32   gfxp = grctx->gfxp_nr;
	स्थिर पूर्णांक s = 12;
	स्थिर पूर्णांक max_batches = 0xffff;
	u32 size = grctx->alpha_nr_max * gr->tpc_total;
	u32 ao = 0;
	u32 bo = ao + size;
	पूर्णांक gpc, ppc, b, n = 0;

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++)
		size += grctx->gfxp_nr * gr->ppc_nr[gpc] * gr->ppc_tpc_max;
	size = ((size * 0x20) + 128) & ~127;
	b = mmio_vram(info, size, (1 << s), false);

	mmio_refn(info, 0x418810, 0x80000000, s, b);
	mmio_refn(info, 0x419848, 0x10000000, s, b);
	mmio_refn(info, 0x419c2c, 0x10000000, s, b);
	mmio_refn(info, 0x419b00, 0x00000000, s, b);
	mmio_wr32(info, 0x419b04, 0x80000000 | size >> 7);
	mmio_wr32(info, 0x405830, attrib);
	mmio_wr32(info, 0x40585c, alpha);
	mmio_wr32(info, 0x4064c4, ((alpha / 4) << 16) | max_batches);

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
		क्रम (ppc = 0; ppc < gr->ppc_nr[gpc]; ppc++, n++) अणु
			स्थिर u32 as =  alpha * gr->ppc_tpc_nr[gpc][ppc];
			स्थिर u32 bs = attrib * gr->ppc_tpc_max;
			स्थिर u32 gs =   gfxp * gr->ppc_tpc_max;
			स्थिर u32 u = 0x418ea0 + (n * 0x04);
			स्थिर u32 o = PPC_UNIT(gpc, ppc, 0);
			स्थिर u32 p = GPC_UNIT(gpc, 0xc44 + (ppc * 4));
			अगर (!(gr->ppc_mask[gpc] & (1 << ppc)))
				जारी;
			mmio_wr32(info, o + 0xc0, gs);
			mmio_wr32(info, p, bs);
			mmio_wr32(info, o + 0xf4, bo);
			mmio_wr32(info, o + 0xf0, bs);
			bo += gs;
			mmio_wr32(info, o + 0xe4, as);
			mmio_wr32(info, o + 0xf8, ao);
			ao += grctx->alpha_nr_max * gr->ppc_tpc_nr[gpc][ppc];
			mmio_wr32(info, u, bs);
		पूर्ण
	पूर्ण

	mmio_wr32(info, 0x4181e4, 0x00000100);
	mmio_wr32(info, 0x41befc, 0x00000100);
पूर्ण

स्थिर काष्ठा gf100_grctx_func
gp102_grctx = अणु
	.मुख्य = gf100_grctx_generate_मुख्य,
	.unkn = gk104_grctx_generate_unkn,
	.bundle = gm107_grctx_generate_bundle,
	.bundle_size = 0x3000,
	.bundle_min_gpm_fअगरo_depth = 0x180,
	.bundle_token_limit = 0x900,
	.pagepool = gp100_grctx_generate_pagepool,
	.pagepool_size = 0x20000,
	.attrib = gp102_grctx_generate_attrib,
	.attrib_nr_max = 0x4b0,
	.attrib_nr = 0x320,
	.alpha_nr_max = 0xc00,
	.alpha_nr = 0x800,
	.gfxp_nr = 0xba8,
	.sm_id = gm107_grctx_generate_sm_id,
	.rop_mapping = gf117_grctx_generate_rop_mapping,
	.dist_skip_table = gm200_grctx_generate_dist_skip_table,
	.r406500 = gm200_grctx_generate_r406500,
	.gpc_tpc_nr = gk104_grctx_generate_gpc_tpc_nr,
	.tpc_mask = gm200_grctx_generate_tpc_mask,
	.smid_config = gp100_grctx_generate_smid_config,
	.r419a3c = gm200_grctx_generate_r419a3c,
	.r408840 = gp102_grctx_generate_r408840,
पूर्ण;
