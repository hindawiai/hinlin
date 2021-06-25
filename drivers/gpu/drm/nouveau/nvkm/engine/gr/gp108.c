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
#समावेश "gf100.h"

#समावेश <subdev/acr.h>

#समावेश <nvfw/flcn.h>

अटल व्योम
gp108_gr_acr_bld_patch(काष्ठा nvkm_acr *acr, u32 bld, s64 adjust)
अणु
	काष्ठा flcn_bl_dmem_desc_v2 hdr;
	nvkm_robj(acr->wpr, bld, &hdr, माप(hdr));
	hdr.code_dma_base = hdr.code_dma_base + adjust;
	hdr.data_dma_base = hdr.data_dma_base + adjust;
	nvkm_wobj(acr->wpr, bld, &hdr, माप(hdr));
	flcn_bl_dmem_desc_v2_dump(&acr->subdev, &hdr);
पूर्ण

अटल व्योम
gp108_gr_acr_bld_ग_लिखो(काष्ठा nvkm_acr *acr, u32 bld,
		       काष्ठा nvkm_acr_lsfw *lsfw)
अणु
	स्थिर u64 base = lsfw->offset.img + lsfw->app_start_offset;
	स्थिर u64 code = base + lsfw->app_resident_code_offset;
	स्थिर u64 data = base + lsfw->app_resident_data_offset;
	स्थिर काष्ठा flcn_bl_dmem_desc_v2 hdr = अणु
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
gp108_gr_gpccs_acr = अणु
	.flags = NVKM_ACR_LSF_FORCE_PRIV_LOAD,
	.bld_size = माप(काष्ठा flcn_bl_dmem_desc_v2),
	.bld_ग_लिखो = gp108_gr_acr_bld_ग_लिखो,
	.bld_patch = gp108_gr_acr_bld_patch,
पूर्ण;

स्थिर काष्ठा nvkm_acr_lsf_func
gp108_gr_fecs_acr = अणु
	.bld_size = माप(काष्ठा flcn_bl_dmem_desc_v2),
	.bld_ग_लिखो = gp108_gr_acr_bld_ग_लिखो,
	.bld_patch = gp108_gr_acr_bld_patch,
पूर्ण;

MODULE_FIRMWARE("nvidia/gp108/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/gpccs_bl.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/gpccs_sig.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gp108/gr/sw_method_init.bin");

अटल स्थिर काष्ठा gf100_gr_fwअगर
gp108_gr_fwअगर[] = अणु
	अणु  0, gm200_gr_load, &gp107_gr, &gp108_gr_fecs_acr, &gp108_gr_gpccs_acr पूर्ण,
	अणु -1, gm200_gr_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp108_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gp108_gr_fwअगर, device, type, inst, pgr);
पूर्ण
