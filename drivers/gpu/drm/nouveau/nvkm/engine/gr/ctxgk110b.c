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
 * Authors: Ben Skeggs <bskeggs@redhat.com>
 */
#समावेश "ctxgf100.h"

/*******************************************************************************
 * PGRAPH context रेजिस्टर lists
 ******************************************************************************/

अटल स्थिर काष्ठा gf100_gr_init
gk110b_grctx_init_sm_0[] = अणु
	अणु 0x419e04,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419e08,   1, 0x04, 0x0000001d पूर्ण,
	अणु 0x419e0c,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419e10,   1, 0x04, 0x00001c02 पूर्ण,
	अणु 0x419e44,   1, 0x04, 0x0013eff2 पूर्ण,
	अणु 0x419e48,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419e4c,   1, 0x04, 0x0000007f पूर्ण,
	अणु 0x419e50,   2, 0x04, 0x00000000 पूर्ण,
	अणु 0x419e58,   1, 0x04, 0x00000001 पूर्ण,
	अणु 0x419e5c,   3, 0x04, 0x00000000 पूर्ण,
	अणु 0x419e68,   1, 0x04, 0x00000002 पूर्ण,
	अणु 0x419e6c,  12, 0x04, 0x00000000 पूर्ण,
	अणु 0x419eac,   1, 0x04, 0x00001f8f पूर्ण,
	अणु 0x419eb0,   1, 0x04, 0x0db00d2f पूर्ण,
	अणु 0x419eb8,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419ec8,   1, 0x04, 0x0001304f पूर्ण,
	अणु 0x419f30,   4, 0x04, 0x00000000 पूर्ण,
	अणु 0x419f40,   1, 0x04, 0x00000018 पूर्ण,
	अणु 0x419f44,   3, 0x04, 0x00000000 पूर्ण,
	अणु 0x419f58,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419f70,   1, 0x04, 0x00006300 पूर्ण,
	अणु 0x419f78,   1, 0x04, 0x000000eb पूर्ण,
	अणु 0x419f7c,   1, 0x04, 0x00000404 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
gk110b_grctx_pack_tpc[] = अणु
	अणु gf117_grctx_init_pe_0 पूर्ण,
	अणु gk110_grctx_init_tex_0 पूर्ण,
	अणु gk110_grctx_init_mpc_0 पूर्ण,
	अणु gk110_grctx_init_l1c_0 पूर्ण,
	अणु gk110b_grctx_init_sm_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*******************************************************************************
 * PGRAPH context implementation
 ******************************************************************************/

स्थिर काष्ठा gf100_grctx_func
gk110b_grctx = अणु
	.मुख्य  = gf100_grctx_generate_मुख्य,
	.unkn  = gk104_grctx_generate_unkn,
	.hub   = gk110_grctx_pack_hub,
	.gpc_0 = gk110_grctx_pack_gpc_0,
	.gpc_1 = gk110_grctx_pack_gpc_1,
	.zcull = gf100_grctx_pack_zcull,
	.tpc   = gk110b_grctx_pack_tpc,
	.ppc   = gk110_grctx_pack_ppc,
	.icmd  = gk110_grctx_pack_icmd,
	.mthd  = gk110_grctx_pack_mthd,
	.bundle = gk104_grctx_generate_bundle,
	.bundle_size = 0x3000,
	.bundle_min_gpm_fअगरo_depth = 0x180,
	.bundle_token_limit = 0x600,
	.pagepool = gk104_grctx_generate_pagepool,
	.pagepool_size = 0x8000,
	.attrib = gf117_grctx_generate_attrib,
	.attrib_nr_max = 0x324,
	.attrib_nr = 0x218,
	.alpha_nr_max = 0x7ff,
	.alpha_nr = 0x648,
	.patch_ltc = gk104_grctx_generate_patch_ltc,
	.sm_id = gf100_grctx_generate_sm_id,
	.tpc_nr = gf100_grctx_generate_tpc_nr,
	.rop_mapping = gf117_grctx_generate_rop_mapping,
	.alpha_beta_tables = gk104_grctx_generate_alpha_beta_tables,
	.dist_skip_table = gf117_grctx_generate_dist_skip_table,
	.gpc_tpc_nr = gk104_grctx_generate_gpc_tpc_nr,
	.r418800 = gk104_grctx_generate_r418800,
	.r419eb0 = gk110_grctx_generate_r419eb0,
पूर्ण;
