<शैली गुरु>
/*
 * Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#समावेश "ctxgf100.h"

अटल व्योम
gm20b_grctx_generate_मुख्य(काष्ठा gf100_gr *gr, काष्ठा gf100_grctx *info)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर काष्ठा gf100_grctx_func *grctx = gr->func->grctx;
	u32 idle_समयout;
	पूर्णांक i, पंचांगp;

	gf100_gr_mmio(gr, gr->sw_ctx);

	gf100_gr_रुको_idle(gr);

	idle_समयout = nvkm_mask(device, 0x404154, 0xffffffff, 0x00000000);

	grctx->attrib(info);

	grctx->unkn(gr);

	gf100_grctx_generate_न्यूनमानsweep(gr);

	क्रम (i = 0; i < 8; i++)
		nvkm_wr32(device, 0x4064d0 + (i * 0x04), 0x00000000);

	nvkm_wr32(device, 0x405b00, (gr->tpc_total << 8) | gr->gpc_nr);

	nvkm_wr32(device, 0x408908, nvkm_rd32(device, 0x410108) | 0x80000000);

	क्रम (पंचांगp = 0, i = 0; i < gr->gpc_nr; i++)
		पंचांगp |= ((1 << gr->tpc_nr[i]) - 1) << (i * 4);
	nvkm_wr32(device, 0x4041c4, पंचांगp);

	gm200_grctx_generate_smid_config(gr);

	gf100_gr_रुको_idle(gr);

	nvkm_wr32(device, 0x404154, idle_समयout);
	gf100_gr_रुको_idle(gr);

	gf100_gr_mthd(gr, gr->method);
	gf100_gr_रुको_idle(gr);

	gf100_gr_icmd(gr, gr->bundle);
	grctx->pagepool(info);
	grctx->bundle(info);
पूर्ण

स्थिर काष्ठा gf100_grctx_func
gm20b_grctx = अणु
	.मुख्य  = gm20b_grctx_generate_मुख्य,
	.unkn  = gk104_grctx_generate_unkn,
	.bundle = gm107_grctx_generate_bundle,
	.bundle_size = 0x1800,
	.bundle_min_gpm_fअगरo_depth = 0x182,
	.bundle_token_limit = 0x1c0,
	.pagepool = gm107_grctx_generate_pagepool,
	.pagepool_size = 0x8000,
	.attrib = gm107_grctx_generate_attrib,
	.attrib_nr_max = 0x600,
	.attrib_nr = 0x400,
	.alpha_nr_max = 0xc00,
	.alpha_nr = 0x800,
	.sm_id = gm107_grctx_generate_sm_id,
	.rop_mapping = gf117_grctx_generate_rop_mapping,
पूर्ण;
