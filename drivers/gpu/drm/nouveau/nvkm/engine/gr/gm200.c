<शैली गुरु>
/*
 * Copyright 2015 Red Hat Inc.
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

#समावेश <core/firmware.h>
#समावेश <subdev/acr.h>
#समावेश <subdev/secboot.h>

#समावेश <nvfw/flcn.h>

#समावेश <nvअगर/class.h>

पूर्णांक
gm200_gr_nofw(काष्ठा gf100_gr *gr, पूर्णांक ver, स्थिर काष्ठा gf100_gr_fwअगर *fwअगर)
अणु
	nvkm_warn(&gr->base.engine.subdev, "firmware unavailable\n");
	वापस -ENODEV;
पूर्ण

/*******************************************************************************
 * PGRAPH engine/subdev functions
 ******************************************************************************/

अटल व्योम
gm200_gr_acr_bld_patch(काष्ठा nvkm_acr *acr, u32 bld, s64 adjust)
अणु
	काष्ठा flcn_bl_dmem_desc_v1 hdr;
	nvkm_robj(acr->wpr, bld, &hdr, माप(hdr));
	hdr.code_dma_base = hdr.code_dma_base + adjust;
	hdr.data_dma_base = hdr.data_dma_base + adjust;
	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
	flcn_bl_dmem_desc_v1_dump(&acr->subdev, &hdr);
पूर्ण

अटल व्योम
gm200_gr_acr_bld_ग_लिखो(काष्ठा nvkm_acr *acr, u32 bld,
		       काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	स्थिर u64 base = lsfw->offset.img + lsfw->app_start_offset;
	स्थिर u64 code = base + lsfw->app_resident_code_offset;
	स्थिर u64 data = base + lsfw->app_resident_data_offset;
	स्थिर काष्ठा flcn_bl_dmem_desc_v1 hdr = अणु
		.ctx_dma = FALCON_DMAIDX_UCODE,
		.code_dma_base = code,
		.non_sec_code_off = lsfw->app_resident_code_offset,
		.non_sec_code_size = lsfw->app_resident_code_size,
		.code_entry_poपूर्णांक = lsfw->app_imem_entry,
		.data_dma_base = data,
		.data_size = lsfw->app_resident_data_size,
	पूर्ण;

	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
पूर्ण

स्थिर काष्ठा nvkm_acr_lsf_func
gm200_gr_gpccs_acr = अणु
	.flags = NVKM_ACR_LSF_FORCE_PRIV_LOAD,
	.bld_size = माप(काष्ठा flcn_bl_dmem_desc_v1),
	.bld_ग_लिखो = gm200_gr_acr_bld_ग_लिखो,
	.bld_patch = gm200_gr_acr_bld_patch,
पूर्ण;

स्थिर काष्ठा nvkm_acr_lsf_func
gm200_gr_fecs_acr = अणु
	.bld_size = माप(काष्ठा flcn_bl_dmem_desc_v1),
	.bld_ग_लिखो = gm200_gr_acr_bld_ग_लिखो,
	.bld_patch = gm200_gr_acr_bld_patch,
पूर्ण;

पूर्णांक
gm200_gr_rops(काष्ठा gf100_gr *gr)
अणु
	वापस nvkm_rd32(gr->base.engine.subdev.device, 0x12006c);
पूर्ण

व्योम
gm200_gr_init_ds_hww_esr_2(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, 0x405848, 0xc0000000);
	nvkm_mask(device, 0x40584c, 0x00000001, 0x00000001);
पूर्ण

व्योम
gm200_gr_init_num_active_ltcs(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, GPC_BCAST(0x08ac), nvkm_rd32(device, 0x100800));
	nvkm_wr32(device, GPC_BCAST(0x033c), nvkm_rd32(device, 0x100804));
पूर्ण

व्योम
gm200_gr_init_gpc_mmu(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;

	nvkm_wr32(device, 0x418880, nvkm_rd32(device, 0x100c80) & 0xf0001fff);
	nvkm_wr32(device, 0x418890, 0x00000000);
	nvkm_wr32(device, 0x418894, 0x00000000);

	nvkm_wr32(device, 0x4188b4, nvkm_rd32(device, 0x100cc8));
	nvkm_wr32(device, 0x4188b8, nvkm_rd32(device, 0x100ccc));
	nvkm_wr32(device, 0x4188b0, nvkm_rd32(device, 0x100cc4));
पूर्ण

अटल व्योम
gm200_gr_init_rop_active_fbps(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर u32 fbp_count = nvkm_rd32(device, 0x12006c);
	nvkm_mask(device, 0x408850, 0x0000000f, fbp_count); /* zrop */
	nvkm_mask(device, 0x408958, 0x0000000f, fbp_count); /* crop */
पूर्ण

अटल u8
gm200_gr_tile_map_6_24[] = अणु
	0, 1, 2, 3, 4, 5, 3, 4, 5, 0, 1, 2, 0, 1, 2, 3, 4, 5, 3, 4, 5, 0, 1, 2,
पूर्ण;

अटल u8
gm200_gr_tile_map_4_16[] = अणु
	0, 1, 2, 3, 2, 3, 0, 1, 3, 0, 1, 2, 1, 2, 3, 0,
पूर्ण;

अटल u8
gm200_gr_tile_map_2_8[] = अणु
	0, 1, 1, 0, 0, 1, 1, 0,
पूर्ण;

व्योम
gm200_gr_oneinit_sm_id(काष्ठा gf100_gr *gr)
अणु
	/*XXX: There's a different algorithm here I've not yet figured out. */
	gf100_gr_oneinit_sm_id(gr);
पूर्ण

व्योम
gm200_gr_oneinit_tiles(काष्ठा gf100_gr *gr)
अणु
	/*XXX: Not sure what this is about.  The algorithm from NVGPU
	 *     seems to work क्रम all boards I tried from earlier (and
	 *     later) GPUs except in these specअगरic configurations.
	 *
	 *     Let's just hardcode them क्रम now.
	 */
	अगर (gr->gpc_nr == 2 && gr->tpc_total == 8) अणु
		स_नकल(gr->tile, gm200_gr_tile_map_2_8, gr->tpc_total);
		gr->screen_tile_row_offset = 1;
	पूर्ण अन्यथा
	अगर (gr->gpc_nr == 4 && gr->tpc_total == 16) अणु
		स_नकल(gr->tile, gm200_gr_tile_map_4_16, gr->tpc_total);
		gr->screen_tile_row_offset = 4;
	पूर्ण अन्यथा
	अगर (gr->gpc_nr == 6 && gr->tpc_total == 24) अणु
		स_नकल(gr->tile, gm200_gr_tile_map_6_24, gr->tpc_total);
		gr->screen_tile_row_offset = 5;
	पूर्ण अन्यथा अणु
		gf100_gr_oneinit_tiles(gr);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा gf100_gr_func
gm200_gr = अणु
	.oneinit_tiles = gm200_gr_oneinit_tiles,
	.oneinit_sm_id = gm200_gr_oneinit_sm_id,
	.init = gf100_gr_init,
	.init_gpc_mmu = gm200_gr_init_gpc_mmu,
	.init_bios = gm107_gr_init_bios,
	.init_vsc_stream_master = gk104_gr_init_vsc_stream_master,
	.init_zcull = gf117_gr_init_zcull,
	.init_num_active_ltcs = gm200_gr_init_num_active_ltcs,
	.init_rop_active_fbps = gm200_gr_init_rop_active_fbps,
	.init_fecs_exceptions = gf100_gr_init_fecs_exceptions,
	.init_ds_hww_esr_2 = gm200_gr_init_ds_hww_esr_2,
	.init_sked_hww_esr = gk104_gr_init_sked_hww_esr,
	.init_419cc0 = gf100_gr_init_419cc0,
	.init_ppc_exceptions = gk104_gr_init_ppc_exceptions,
	.init_tex_hww_esr = gf100_gr_init_tex_hww_esr,
	.init_504430 = gm107_gr_init_504430,
	.init_shader_exceptions = gm107_gr_init_shader_exceptions,
	.init_400054 = gm107_gr_init_400054,
	.trap_mp = gf100_gr_trap_mp,
	.rops = gm200_gr_rops,
	.tpc_nr = 4,
	.ppc_nr = 2,
	.grctx = &gm200_grctx,
	.zbc = &gf100_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, KEPLER_INLINE_TO_MEMORY_B पूर्ण,
		अणु -1, -1, MAXWELL_B, &gf100_fermi पूर्ण,
		अणु -1, -1, MAXWELL_COMPUTE_B पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

पूर्णांक
gm200_gr_load(काष्ठा gf100_gr *gr, पूर्णांक ver, स्थिर काष्ठा gf100_gr_fwअगर *fwअगर)
अणु
	पूर्णांक ret;

	ret = nvkm_acr_lsfw_load_bl_inst_data_sig(&gr->base.engine.subdev,
						  &gr->fecs.falcon,
						  NVKM_ACR_LSF_FECS,
						  "gr/fecs_", ver, fwअगर->fecs);
	अगर (ret)
		वापस ret;

	ret = nvkm_acr_lsfw_load_bl_inst_data_sig(&gr->base.engine.subdev,
						  &gr->gpccs.falcon,
						  NVKM_ACR_LSF_GPCCS,
						  "gr/gpccs_", ver,
						  fwअगर->gpccs);
	अगर (ret)
		वापस ret;

	gr->firmware = true;

	वापस gk20a_gr_load_sw(gr, "gr/", ver);
पूर्ण

MODULE_FIRMWARE("nvidia/gm200/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/gpccs_bl.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/gpccs_sig.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gm200/gr/sw_method_init.bin");

MODULE_FIRMWARE("nvidia/gm204/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/gpccs_bl.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/gpccs_sig.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gm204/gr/sw_method_init.bin");

MODULE_FIRMWARE("nvidia/gm206/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/gpccs_bl.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/gpccs_sig.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gm206/gr/sw_method_init.bin");

अटल स्थिर काष्ठा gf100_gr_fwअगर
gm200_gr_fwअगर[] = अणु
	अणु  0, gm200_gr_load, &gm200_gr, &gm200_gr_fecs_acr, &gm200_gr_gpccs_acr पूर्ण,
	अणु -1, gm200_gr_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm200_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gm200_gr_fwअगर, device, type, inst, pgr);
पूर्ण
