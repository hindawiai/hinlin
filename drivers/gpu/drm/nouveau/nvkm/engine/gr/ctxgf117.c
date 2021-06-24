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

#समावेश <subdev/fb.h>
#समावेश <subdev/mc.h>

/*******************************************************************************
 * PGRAPH context रेजिस्टर lists
 ******************************************************************************/

अटल स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_ds_0[] = अणु
	अणु 0x405800,   1, 0x04, 0x0f8000bf पूर्ण,
	अणु 0x405830,   1, 0x04, 0x02180324 पूर्ण,
	अणु 0x405834,   1, 0x04, 0x08000000 पूर्ण,
	अणु 0x405838,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x405854,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x405870,   4, 0x04, 0x00000001 पूर्ण,
	अणु 0x405a00,   2, 0x04, 0x00000000 पूर्ण,
	अणु 0x405a18,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_pd_0[] = अणु
	अणु 0x406020,   1, 0x04, 0x000103c1 पूर्ण,
	अणु 0x406028,   4, 0x04, 0x00000001 पूर्ण,
	अणु 0x4064a8,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x4064ac,   1, 0x04, 0x00003fff पूर्ण,
	अणु 0x4064b4,   3, 0x04, 0x00000000 पूर्ण,
	अणु 0x4064c0,   1, 0x04, 0x801a0078 पूर्ण,
	अणु 0x4064c4,   1, 0x04, 0x00c9ffff पूर्ण,
	अणु 0x4064d0,   8, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
gf117_grctx_pack_hub[] = अणु
	अणु gf100_grctx_init_मुख्य_0 पूर्ण,
	अणु gf119_grctx_init_fe_0 पूर्ण,
	अणु gf100_grctx_init_pri_0 पूर्ण,
	अणु gf100_grctx_init_memfmt_0 पूर्ण,
	अणु gf117_grctx_init_ds_0 पूर्ण,
	अणु gf117_grctx_init_pd_0 पूर्ण,
	अणु gf100_grctx_init_rstr2d_0 पूर्ण,
	अणु gf100_grctx_init_scc_0 पूर्ण,
	अणु gf119_grctx_init_be_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_setup_0[] = अणु
	अणु 0x418800,   1, 0x04, 0x7006860a पूर्ण,
	अणु 0x418808,   3, 0x04, 0x00000000 पूर्ण,
	अणु 0x418828,   1, 0x04, 0x00008442 पूर्ण,
	अणु 0x418830,   1, 0x04, 0x10000001 पूर्ण,
	अणु 0x4188d8,   1, 0x04, 0x00000008 पूर्ण,
	अणु 0x4188e0,   1, 0x04, 0x01000000 पूर्ण,
	अणु 0x4188e8,   5, 0x04, 0x00000000 पूर्ण,
	अणु 0x4188fc,   1, 0x04, 0x20100018 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
gf117_grctx_pack_gpc_0[] = अणु
	अणु gf100_grctx_init_gpc_unk_0 पूर्ण,
	अणु gf119_grctx_init_prop_0 पूर्ण,
	अणु gf119_grctx_init_gpc_unk_1 पूर्ण,
	अणु gf117_grctx_init_setup_0 पूर्ण,
	अणु gf100_grctx_init_zcull_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_pack
gf117_grctx_pack_gpc_1[] = अणु
	अणु gf119_grctx_init_crstr_0 पूर्ण,
	अणु gf108_grctx_init_gpm_0 पूर्ण,
	अणु gf100_grctx_init_gcc_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_pe_0[] = अणु
	अणु 0x419848,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419864,   1, 0x04, 0x00000129 पूर्ण,
	अणु 0x419888,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_tex_0[] = अणु
	अणु 0x419a00,   1, 0x04, 0x000001f0 पूर्ण,
	अणु 0x419a04,   1, 0x04, 0x00000001 पूर्ण,
	अणु 0x419a08,   1, 0x04, 0x00000023 पूर्ण,
	अणु 0x419a0c,   1, 0x04, 0x00020000 पूर्ण,
	अणु 0x419a10,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419a14,   1, 0x04, 0x00000200 पूर्ण,
	अणु 0x419a1c,   1, 0x04, 0x00008000 पूर्ण,
	अणु 0x419a20,   1, 0x04, 0x00000800 पूर्ण,
	अणु 0x419ac4,   1, 0x04, 0x0017f440 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_mpc_0[] = अणु
	अणु 0x419c00,   1, 0x04, 0x0000000a पूर्ण,
	अणु 0x419c04,   1, 0x04, 0x00000006 पूर्ण,
	अणु 0x419c08,   1, 0x04, 0x00000002 पूर्ण,
	अणु 0x419c20,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x419c24,   1, 0x04, 0x00084210 पूर्ण,
	अणु 0x419c28,   1, 0x04, 0x3efbefbe पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
gf117_grctx_pack_tpc[] = अणु
	अणु gf117_grctx_init_pe_0 पूर्ण,
	अणु gf117_grctx_init_tex_0 पूर्ण,
	अणु gf117_grctx_init_mpc_0 पूर्ण,
	अणु gf104_grctx_init_l1c_0 पूर्ण,
	अणु gf119_grctx_init_sm_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_pes_0[] = अणु
	अणु 0x41be24,   1, 0x04, 0x00000002 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_cbm_0[] = अणु
	अणु 0x41bec0,   1, 0x04, 0x12180000 पूर्ण,
	अणु 0x41bec4,   1, 0x04, 0x00003fff पूर्ण,
	अणु 0x41bee4,   1, 0x04, 0x03240218 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf117_grctx_init_wwdx_0[] = अणु
	अणु 0x41bf00,   1, 0x04, 0x0a418820 पूर्ण,
	अणु 0x41bf04,   1, 0x04, 0x062080e6 पूर्ण,
	अणु 0x41bf08,   1, 0x04, 0x020398a4 पूर्ण,
	अणु 0x41bf0c,   1, 0x04, 0x0e629062 पूर्ण,
	अणु 0x41bf10,   1, 0x04, 0x0a418820 पूर्ण,
	अणु 0x41bf14,   1, 0x04, 0x000000e6 पूर्ण,
	अणु 0x41bfd0,   1, 0x04, 0x00900103 पूर्ण,
	अणु 0x41bfe0,   1, 0x04, 0x00400001 पूर्ण,
	अणु 0x41bfe4,   1, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
gf117_grctx_pack_ppc[] = अणु
	अणु gf117_grctx_init_pes_0 पूर्ण,
	अणु gf117_grctx_init_cbm_0 पूर्ण,
	अणु gf117_grctx_init_wwdx_0 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*******************************************************************************
 * PGRAPH context implementation
 ******************************************************************************/

व्योम
gf117_grctx_generate_dist_skip_table(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++)
		nvkm_wr32(device, 0x4064d0 + (i * 0x04), 0x00000000);
पूर्ण

व्योम
gf117_grctx_generate_rop_mapping(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	u32 data[6] = अणुपूर्ण, data2[2] = अणुपूर्ण;
	u8  shअगरt, ntpcv;
	पूर्णांक i;

	/* Pack tile map पूर्णांकo रेजिस्टर क्रमmat. */
	क्रम (i = 0; i < 32; i++)
		data[i / 6] |= (gr->tile[i] & 0x07) << ((i % 6) * 5);

	/* Magic. */
	shअगरt = 0;
	ntpcv = gr->tpc_total;
	जबतक (!(ntpcv & (1 << 4))) अणु
		ntpcv <<= 1;
		shअगरt++;
	पूर्ण

	data2[0]  = (ntpcv << 16);
	data2[0] |= (shअगरt << 21);
	data2[0] |= (((1 << (0 + 5)) % ntpcv) << 24);
	क्रम (i = 1; i < 7; i++)
		data2[1] |= ((1 << (i + 5)) % ntpcv) << ((i - 1) * 5);

	/* GPC_BROADCAST */
	nvkm_wr32(device, 0x418bb8, (gr->tpc_total << 8) |
				     gr->screen_tile_row_offset);
	क्रम (i = 0; i < 6; i++)
		nvkm_wr32(device, 0x418b08 + (i * 4), data[i]);

	/* GPC_BROADCAST.TP_BROADCAST */
	nvkm_wr32(device, 0x41bfd0, (gr->tpc_total << 8) |
				     gr->screen_tile_row_offset | data2[0]);
	nvkm_wr32(device, 0x41bfe4, data2[1]);
	क्रम (i = 0; i < 6; i++)
		nvkm_wr32(device, 0x41bf00 + (i * 4), data[i]);

	/* UNK78xx */
	nvkm_wr32(device, 0x4078bc, (gr->tpc_total << 8) |
				     gr->screen_tile_row_offset);
	क्रम (i = 0; i < 6; i++)
		nvkm_wr32(device, 0x40780c + (i * 4), data[i]);
पूर्ण

व्योम
gf117_grctx_generate_attrib(काष्ठा gf100_grctx *info)
अणु
	काष्ठा gf100_gr *gr = info->gr;
	स्थिर काष्ठा gf100_grctx_func *grctx = gr->func->grctx;
	स्थिर u32  alpha = grctx->alpha_nr;
	स्थिर u32   beta = grctx->attrib_nr;
	स्थिर u32   size = 0x20 * (grctx->attrib_nr_max + grctx->alpha_nr_max);
	स्थिर पूर्णांक s = 12;
	स्थिर पूर्णांक b = mmio_vram(info, size * gr->tpc_total, (1 << s), false);
	स्थिर पूर्णांक बारlice_mode = 1;
	स्थिर पूर्णांक max_batches = 0xffff;
	u32 bo = 0;
	u32 ao = bo + grctx->attrib_nr_max * gr->tpc_total;
	पूर्णांक gpc, ppc;

	mmio_refn(info, 0x418810, 0x80000000, s, b);
	mmio_refn(info, 0x419848, 0x10000000, s, b);
	mmio_wr32(info, 0x405830, (beta << 16) | alpha);
	mmio_wr32(info, 0x4064c4, ((alpha / 4) << 16) | max_batches);

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
		क्रम (ppc = 0; ppc < gr->ppc_nr[gpc]; ppc++) अणु
			स्थिर u32 a = alpha * gr->ppc_tpc_nr[gpc][ppc];
			स्थिर u32 b =  beta * gr->ppc_tpc_nr[gpc][ppc];
			स्थिर u32 t = बारlice_mode;
			स्थिर u32 o = PPC_UNIT(gpc, ppc, 0);
			अगर (!(gr->ppc_mask[gpc] & (1 << ppc)))
				जारी;
			mmio_skip(info, o + 0xc0, (t << 28) | (b << 16) | ++bo);
			mmio_wr32(info, o + 0xc0, (t << 28) | (b << 16) | --bo);
			bo += grctx->attrib_nr_max * gr->ppc_tpc_nr[gpc][ppc];
			mmio_wr32(info, o + 0xe4, (a << 16) | ao);
			ao += grctx->alpha_nr_max * gr->ppc_tpc_nr[gpc][ppc];
		पूर्ण
	पूर्ण
पूर्ण

स्थिर काष्ठा gf100_grctx_func
gf117_grctx = अणु
	.मुख्य  = gf100_grctx_generate_मुख्य,
	.unkn  = gk104_grctx_generate_unkn,
	.hub   = gf117_grctx_pack_hub,
	.gpc_0 = gf117_grctx_pack_gpc_0,
	.gpc_1 = gf117_grctx_pack_gpc_1,
	.zcull = gf100_grctx_pack_zcull,
	.tpc   = gf117_grctx_pack_tpc,
	.ppc   = gf117_grctx_pack_ppc,
	.icmd  = gf119_grctx_pack_icmd,
	.mthd  = gf119_grctx_pack_mthd,
	.bundle = gf100_grctx_generate_bundle,
	.bundle_size = 0x1800,
	.pagepool = gf100_grctx_generate_pagepool,
	.pagepool_size = 0x8000,
	.attrib = gf117_grctx_generate_attrib,
	.attrib_nr_max = 0x324,
	.attrib_nr = 0x218,
	.alpha_nr_max = 0x7ff,
	.alpha_nr = 0x324,
	.sm_id = gf100_grctx_generate_sm_id,
	.tpc_nr = gf100_grctx_generate_tpc_nr,
	.r4060a8 = gf100_grctx_generate_r4060a8,
	.rop_mapping = gf117_grctx_generate_rop_mapping,
	.alpha_beta_tables = gf100_grctx_generate_alpha_beta_tables,
	.max_ways_evict = gf100_grctx_generate_max_ways_evict,
	.dist_skip_table = gf117_grctx_generate_dist_skip_table,
	.r419cb8 = gf100_grctx_generate_r419cb8,
पूर्ण;
