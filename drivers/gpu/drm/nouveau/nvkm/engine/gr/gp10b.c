<शैली गुरु>
/*
 * Copyright (c) 2017, NVIDIA CORPORATION. All rights reserved.
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

#समावेश <subdev/acr.h>

#समावेश <nvअगर/class.h>

#समावेश <nvfw/flcn.h>

अटल स्थिर काष्ठा nvkm_acr_lsf_func
gp10b_gr_gpccs_acr = अणु
	.flags = NVKM_ACR_LSF_FORCE_PRIV_LOAD,
	.bld_size = माप(काष्ठा flcn_bl_dmem_desc),
	.bld_ग_लिखो = gm20b_gr_acr_bld_ग_लिखो,
	.bld_patch = gm20b_gr_acr_bld_patch,
पूर्ण;

अटल स्थिर काष्ठा gf100_gr_func
gp10b_gr = अणु
	.oneinit_tiles = gm200_gr_oneinit_tiles,
	.oneinit_sm_id = gm200_gr_oneinit_sm_id,
	.init = gf100_gr_init,
	.init_gpc_mmu = gm200_gr_init_gpc_mmu,
	.init_vsc_stream_master = gk104_gr_init_vsc_stream_master,
	.init_zcull = gf117_gr_init_zcull,
	.init_num_active_ltcs = gf100_gr_init_num_active_ltcs,
	.init_rop_active_fbps = gp100_gr_init_rop_active_fbps,
	.init_fecs_exceptions = gp100_gr_init_fecs_exceptions,
	.init_ds_hww_esr_2 = gm200_gr_init_ds_hww_esr_2,
	.init_sked_hww_esr = gk104_gr_init_sked_hww_esr,
	.init_419cc0 = gf100_gr_init_419cc0,
	.init_ppc_exceptions = gk104_gr_init_ppc_exceptions,
	.init_tex_hww_esr = gf100_gr_init_tex_hww_esr,
	.init_504430 = gm107_gr_init_504430,
	.init_shader_exceptions = gp100_gr_init_shader_exceptions,
	.trap_mp = gf100_gr_trap_mp,
	.rops = gm200_gr_rops,
	.gpc_nr = 1,
	.tpc_nr = 2,
	.ppc_nr = 1,
	.grctx = &gp100_grctx,
	.zbc = &gp100_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, KEPLER_INLINE_TO_MEMORY_B पूर्ण,
		अणु -1, -1, PASCAL_A, &gf100_fermi पूर्ण,
		अणु -1, -1, PASCAL_COMPUTE_A पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

#अगर IS_ENABLED(CONFIG_ARCH_TEGRA_186_SOC)
MODULE_FIRMWARE("nvidia/gp10b/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/gpccs_bl.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/gpccs_sig.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gp10b/gr/sw_method_init.bin");
#पूर्ण_अगर

अटल स्थिर काष्ठा gf100_gr_fwअगर
gp10b_gr_fwअगर[] = अणु
	अणु  0, gm200_gr_load, &gp10b_gr, &gm20b_gr_fecs_acr, &gp10b_gr_gpccs_acr पूर्ण,
	अणु -1, gm200_gr_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp10b_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gp10b_gr_fwअगर, device, type, inst, pgr);
पूर्ण
