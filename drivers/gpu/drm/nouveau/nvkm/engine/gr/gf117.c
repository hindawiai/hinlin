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
#समावेश "gf100.h"
#समावेश "ctxgf100.h"

#समावेश <nvअगर/class.h>

/*******************************************************************************
 * PGRAPH रेजिस्टर lists
 ******************************************************************************/

अटल स्थिर काष्ठा gf100_gr_init
gf117_gr_init_pe_0[] = अणु
	अणु 0x41980c,   1, 0x04, 0x00000010 पूर्ण,
	अणु 0x419844,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x41984c,   1, 0x04, 0x00005bc8 पूर्ण,
	अणु 0x419850,   3, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf117_gr_init_pes_0[] = अणु
	अणु 0x41be04,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x41be08,   1, 0x04, 0x00000004 पूर्ण,
	अणु 0x41be0c,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x41be10,   1, 0x04, 0x003b8bc7 पूर्ण,
	अणु 0x41be14,   2, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf117_gr_init_wwdx_0[] = अणु
	अणु 0x41bfd4,   1, 0x04, 0x00800000 पूर्ण,
	अणु 0x41bfdc,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x41bff8,   2, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

स्थिर काष्ठा gf100_gr_init
gf117_gr_init_cbm_0[] = अणु
	अणु 0x41becc,   1, 0x04, 0x00000000 पूर्ण,
	अणु 0x41bee8,   2, 0x04, 0x00000000 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_pack
gf117_gr_pack_mmio[] = अणु
	अणु gf100_gr_init_मुख्य_0 पूर्ण,
	अणु gf100_gr_init_fe_0 पूर्ण,
	अणु gf100_gr_init_pri_0 पूर्ण,
	अणु gf100_gr_init_rstr2d_0 पूर्ण,
	अणु gf119_gr_init_pd_0 पूर्ण,
	अणु gf119_gr_init_ds_0 पूर्ण,
	अणु gf100_gr_init_scc_0 पूर्ण,
	अणु gf119_gr_init_prop_0 पूर्ण,
	अणु gf108_gr_init_gpc_unk_0 पूर्ण,
	अणु gf100_gr_init_setup_0 पूर्ण,
	अणु gf100_gr_init_crstr_0 पूर्ण,
	अणु gf108_gr_init_setup_1 पूर्ण,
	अणु gf100_gr_init_zcull_0 पूर्ण,
	अणु gf119_gr_init_gpm_0 पूर्ण,
	अणु gf119_gr_init_gpc_unk_1 पूर्ण,
	अणु gf100_gr_init_gcc_0 पूर्ण,
	अणु gf100_gr_init_tpccs_0 पूर्ण,
	अणु gf119_gr_init_tex_0 पूर्ण,
	अणु gf117_gr_init_pe_0 पूर्ण,
	अणु gf100_gr_init_l1c_0 पूर्ण,
	अणु gf100_gr_init_mpc_0 पूर्ण,
	अणु gf119_gr_init_sm_0 पूर्ण,
	अणु gf117_gr_init_pes_0 पूर्ण,
	अणु gf117_gr_init_wwdx_0 पूर्ण,
	अणु gf117_gr_init_cbm_0 पूर्ण,
	अणु gf100_gr_init_be_0 पूर्ण,
	अणु gf119_gr_init_fe_1 पूर्ण,
	अणुपूर्ण
पूर्ण;

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

#समावेश "fuc/hubgf117.fuc3.h"

अटल काष्ठा gf100_gr_ucode
gf117_gr_fecs_ucode = अणु
	.code.data = gf117_grhub_code,
	.code.size = माप(gf117_grhub_code),
	.data.data = gf117_grhub_data,
	.data.size = माप(gf117_grhub_data),
पूर्ण;

#समावेश "fuc/gpcgf117.fuc3.h"

अटल काष्ठा gf100_gr_ucode
gf117_gr_gpccs_ucode = अणु
	.code.data = gf117_grgpc_code,
	.code.size = माप(gf117_grgpc_code),
	.data.data = gf117_grgpc_data,
	.data.size = माप(gf117_grgpc_data),
पूर्ण;

व्योम
gf117_gr_init_zcull(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर u32 magicgpc918 = DIV_ROUND_UP(0x00800000, gr->tpc_total);
	स्थिर u8 tile_nr = ALIGN(gr->tpc_total, 32);
	u8 bank[GPC_MAX] = अणुपूर्ण, gpc, i, j;
	u32 data;

	क्रम (i = 0; i < tile_nr; i += 8) अणु
		क्रम (data = 0, j = 0; j < 8 && i + j < gr->tpc_total; j++) अणु
			data |= bank[gr->tile[i + j]] << (j * 4);
			bank[gr->tile[i + j]]++;
		पूर्ण
		nvkm_wr32(device, GPC_BCAST(0x0980 + ((i / 8) * 4)), data);
	पूर्ण

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0914),
			  gr->screen_tile_row_offset << 8 | gr->tpc_nr[gpc]);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0910), 0x00040000 |
							 gr->tpc_total);
		nvkm_wr32(device, GPC_UNIT(gpc, 0x0918), magicgpc918);
	पूर्ण

	nvkm_wr32(device, GPC_BCAST(0x3fd4), magicgpc918);
पूर्ण

अटल स्थिर काष्ठा gf100_gr_func
gf117_gr = अणु
	.oneinit_tiles = gf100_gr_oneinit_tiles,
	.oneinit_sm_id = gf100_gr_oneinit_sm_id,
	.init = gf100_gr_init,
	.init_gpc_mmu = gf100_gr_init_gpc_mmu,
	.init_vsc_stream_master = gf100_gr_init_vsc_stream_master,
	.init_zcull = gf117_gr_init_zcull,
	.init_num_active_ltcs = gf100_gr_init_num_active_ltcs,
	.init_fecs_exceptions = gf100_gr_init_fecs_exceptions,
	.init_40601c = gf100_gr_init_40601c,
	.init_419cc0 = gf100_gr_init_419cc0,
	.init_419eb4 = gf100_gr_init_419eb4,
	.init_tex_hww_esr = gf100_gr_init_tex_hww_esr,
	.init_shader_exceptions = gf100_gr_init_shader_exceptions,
	.init_400054 = gf100_gr_init_400054,
	.trap_mp = gf100_gr_trap_mp,
	.mmio = gf117_gr_pack_mmio,
	.fecs.ucode = &gf117_gr_fecs_ucode,
	.gpccs.ucode = &gf117_gr_gpccs_ucode,
	.rops = gf100_gr_rops,
	.ppc_nr = 1,
	.grctx = &gf117_grctx,
	.zbc = &gf100_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, FERMI_MEMORY_TO_MEMORY_FORMAT_A पूर्ण,
		अणु -1, -1, FERMI_A, &gf100_fermi पूर्ण,
		अणु -1, -1, FERMI_B, &gf100_fermi पूर्ण,
		अणु -1, -1, FERMI_C, &gf100_fermi पूर्ण,
		अणु -1, -1, FERMI_COMPUTE_A पूर्ण,
		अणु -1, -1, FERMI_COMPUTE_B पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_fwअगर
gf117_gr_fwअगर[] = अणु
	अणु -1, gf100_gr_load, &gf117_gr पूर्ण,
	अणु -1, gf100_gr_nofw, &gf117_gr पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gf117_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gf117_gr_fwअगर, device, type, inst, pgr);
पूर्ण
