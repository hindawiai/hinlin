<शैली गुरु>
/*
 * Copyright (c) 2014-2015, NVIDIA CORPORATION. All rights reserved.
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
#समावेश "gf100.h"

#समावेश <subdev/mc.h>

अटल व्योम
gk20a_grctx_generate_मुख्य(काष्ठा gf100_gr *gr, काष्ठा gf100_grctx *info)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर काष्ठा gf100_grctx_func *grctx = gr->func->grctx;
	u32 idle_समयout;
	पूर्णांक i;

	gf100_gr_mmio(gr, gr->sw_ctx);

	gf100_gr_रुको_idle(gr);

	idle_समयout = nvkm_mask(device, 0x404154, 0xffffffff, 0x00000000);

	grctx->attrib(info);

	grctx->unkn(gr);

	gf100_grctx_generate_न्यूनमानsweep(gr);

	क्रम (i = 0; i < 8; i++)
		nvkm_wr32(device, 0x4064d0 + (i * 0x04), 0x00000000);

	nvkm_wr32(device, 0x405b00, (gr->tpc_total << 8) | gr->gpc_nr);

	nvkm_mask(device, 0x5044b0, 0x08000000, 0x08000000);

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
gk20a_grctx = अणु
	.मुख्य  = gk20a_grctx_generate_मुख्य,
	.unkn  = gk104_grctx_generate_unkn,
	.bundle = gk104_grctx_generate_bundle,
	.bundle_size = 0x1800,
	.bundle_min_gpm_fअगरo_depth = 0x62,
	.bundle_token_limit = 0x100,
	.pagepool = gk104_grctx_generate_pagepool,
	.pagepool_size = 0x8000,
	.attrib = gf117_grctx_generate_attrib,
	.attrib_nr_max = 0x240,
	.attrib_nr = 0x240,
	.alpha_nr_max = 0x648 + (0x648 / 2),
	.alpha_nr = 0x648,
	.sm_id = gf100_grctx_generate_sm_id,
	.tpc_nr = gf100_grctx_generate_tpc_nr,
	.rop_mapping = gf117_grctx_generate_rop_mapping,
	.alpha_beta_tables = gk104_grctx_generate_alpha_beta_tables,
पूर्ण;
