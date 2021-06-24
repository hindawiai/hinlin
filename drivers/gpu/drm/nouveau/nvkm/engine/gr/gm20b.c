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
#समावेश "gf100.h"
#समावेश "ctxgf100.h"

#समावेश <core/firmware.h>
#समावेश <subdev/acr.h>
#समावेश <subdev/समयr.h>

#समावेश <nvfw/flcn.h>

#समावेश <nvअगर/class.h>

व्योम
gm20b_gr_acr_bld_patch(काष्ठा nvkm_acr *acr, u32 bld, s64 adjust)
अणु
	काष्ठा flcn_bl_dmem_desc hdr;
	u64 addr;

	nvkm_robj(acr->wpr, bld, &hdr, माप(hdr));
	addr = ((u64)hdr.code_dma_base1 << 40 | hdr.code_dma_base << 8);
	hdr.code_dma_base  = lower_32_bits((addr + adjust) >> 8);
	hdr.code_dma_base1 = upper_32_bits((addr + adjust) >> 8);
	addr = ((u64)hdr.data_dma_base1 << 40 | hdr.data_dma_base << 8);
	hdr.data_dma_base  = lower_32_bits((addr + adjust) >> 8);
	hdr.data_dma_base1 = upper_32_bits((addr + adjust) >> 8);
	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));

	flcn_bl_dmem_desc_dump(&acr->subdev, &hdr);
पूर्ण

व्योम
gm20b_gr_acr_bld_ग_लिखो(काष्ठा nvkm_acr *acr, u32 bld,
		       काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	स्थिर u64 base = lsfw->offset.img + lsfw->app_start_offset;
	स्थिर u64 code = (base + lsfw->app_resident_code_offset) >> 8;
	स्थिर u64 data = (base + lsfw->app_resident_data_offset) >> 8;
	स्थिर काष्ठा flcn_bl_dmem_desc hdr = अणु
		.ctx_dma = FALCON_DMAIDX_UCODE,
		.code_dma_base = lower_32_bits(code),
		.non_sec_code_off = lsfw->app_resident_code_offset,
		.non_sec_code_size = lsfw->app_resident_code_size,
		.code_entry_poपूर्णांक = lsfw->app_imem_entry,
		.data_dma_base = lower_32_bits(data),
		.data_size = lsfw->app_resident_data_size,
		.code_dma_base1 = upper_32_bits(code),
		.data_dma_base1 = upper_32_bits(data),
	पूर्ण;

	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
पूर्ण

स्थिर काष्ठा nvkm_acr_lsf_func
gm20b_gr_fecs_acr = अणु
	.bld_size = माप(काष्ठा flcn_bl_dmem_desc),
	.bld_ग_लिखो = gm20b_gr_acr_bld_ग_लिखो,
	.bld_patch = gm20b_gr_acr_bld_patch,
पूर्ण;

अटल व्योम
gm20b_gr_init_gpc_mmu(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	u32 val;

	/* Bypass MMU check क्रम non-secure boot */
	अगर (!device->acr) अणु
		nvkm_wr32(device, 0x100ce4, 0xffffffff);

		अगर (nvkm_rd32(device, 0x100ce4) != 0xffffffff)
			nvdev_warn(device,
			  "cannot bypass secure boot - expect failure soon!\n");
	पूर्ण

	val = nvkm_rd32(device, 0x100c80);
	val &= 0xf000187f;
	nvkm_wr32(device, 0x418880, val);
	nvkm_wr32(device, 0x418890, 0);
	nvkm_wr32(device, 0x418894, 0);

	nvkm_wr32(device, 0x4188b0, nvkm_rd32(device, 0x100cc4));
	nvkm_wr32(device, 0x4188b4, nvkm_rd32(device, 0x100cc8));
	nvkm_wr32(device, 0x4188b8, nvkm_rd32(device, 0x100ccc));

	nvkm_wr32(device, 0x4188ac, nvkm_rd32(device, 0x100800));
पूर्ण

अटल व्योम
gm20b_gr_set_hww_esr_report_mask(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, 0x419e44, 0xdffffe);
	nvkm_wr32(device, 0x419e4c, 0x5);
पूर्ण

अटल स्थिर काष्ठा gf100_gr_func
gm20b_gr = अणु
	.oneinit_tiles = gm200_gr_oneinit_tiles,
	.oneinit_sm_id = gm200_gr_oneinit_sm_id,
	.init = gk20a_gr_init,
	.init_zcull = gf117_gr_init_zcull,
	.init_gpc_mmu = gm20b_gr_init_gpc_mmu,
	.init_rop_active_fbps = gk104_gr_init_rop_active_fbps,
	.trap_mp = gf100_gr_trap_mp,
	.set_hww_esr_report_mask = gm20b_gr_set_hww_esr_report_mask,
	.rops = gm200_gr_rops,
	.ppc_nr = 1,
	.grctx = &gm20b_grctx,
	.zbc = &gf100_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, KEPLER_INLINE_TO_MEMORY_B पूर्ण,
		अणु -1, -1, MAXWELL_B, &gf100_fermi पूर्ण,
		अणु -1, -1, MAXWELL_COMPUTE_B पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक
gm20b_gr_load(काष्ठा gf100_gr *gr, पूर्णांक ver, स्थिर काष्ठा gf100_gr_fwअगर *fwअगर)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	पूर्णांक ret;

	ret = nvkm_acr_lsfw_load_bl_inst_data_sig(subdev, &gr->fecs.falcon,
						  NVKM_ACR_LSF_FECS,
						  "gr/fecs_", ver, fwअगर->fecs);
	अगर (ret)
		वापस ret;


	अगर (nvkm_firmware_load_blob(subdev, "gr/", "gpccs_inst", ver,
				    &gr->gpccs.inst) ||
	    nvkm_firmware_load_blob(subdev, "gr/", "gpccs_data", ver,
				    &gr->gpccs.data))
		वापस -ENOENT;

	gr->firmware = true;

	वापस gk20a_gr_load_sw(gr, "gr/", ver);
पूर्ण

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_210_SOC)
MODULE_FIRMWARE("nvidia/gm20b/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gm20b/gr/sw_method_init.bin");
#पूर्ण_अगर

अटल स्थिर काष्ठा gf100_gr_fwअगर
gm20b_gr_fwअगर[] = अणु
	अणु  0, gm20b_gr_load, &gm20b_gr, &gm20b_gr_fecs_acr पूर्ण,
	अणु -1, gm200_gr_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gm20b_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gm20b_gr_fwअगर, device, type, inst, pgr);
पूर्ण
