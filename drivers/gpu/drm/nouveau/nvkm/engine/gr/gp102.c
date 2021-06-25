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
#समावेश "gf100.h"
#समावेश "ctxgf100.h"

#समावेश <nvअगर/class.h>

अटल व्योम
gp102_gr_zbc_clear_stencil(काष्ठा gf100_gr *gr, पूर्णांक zbc)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	स्थिर पूर्णांक znum =  zbc - 1;
	स्थिर u32 zoff = znum * 4;

	अगर (gr->zbc_stencil[zbc].क्रमmat)
		nvkm_wr32(device, 0x41815c + zoff, gr->zbc_stencil[zbc].ds);
	nvkm_mask(device, 0x418198 + ((znum / 4) * 4),
			  0x0000007f << ((znum % 4) * 7),
			  gr->zbc_stencil[zbc].क्रमmat << ((znum % 4) * 7));
पूर्ण

अटल पूर्णांक
gp102_gr_zbc_stencil_get(काष्ठा gf100_gr *gr, पूर्णांक क्रमmat,
			 स्थिर u32 ds, स्थिर u32 l2)
अणु
	काष्ठा nvkm_ltc *ltc = gr->base.engine.subdev.device->ltc;
	पूर्णांक zbc = -ENOSPC, i;

	क्रम (i = ltc->zbc_min; i <= ltc->zbc_max; i++) अणु
		अगर (gr->zbc_stencil[i].क्रमmat) अणु
			अगर (gr->zbc_stencil[i].क्रमmat != क्रमmat)
				जारी;
			अगर (gr->zbc_stencil[i].ds != ds)
				जारी;
			अगर (gr->zbc_stencil[i].l2 != l2) अणु
				WARN_ON(1);
				वापस -EINVAL;
			पूर्ण
			वापस i;
		पूर्ण अन्यथा अणु
			zbc = (zbc < 0) ? i : zbc;
		पूर्ण
	पूर्ण

	अगर (zbc < 0)
		वापस zbc;

	gr->zbc_stencil[zbc].क्रमmat = क्रमmat;
	gr->zbc_stencil[zbc].ds = ds;
	gr->zbc_stencil[zbc].l2 = l2;
	nvkm_ltc_zbc_stencil_get(ltc, zbc, l2);
	gr->func->zbc->clear_stencil(gr, zbc);
	वापस zbc;
पूर्ण

स्थिर काष्ठा gf100_gr_func_zbc
gp102_gr_zbc = अणु
	.clear_color = gp100_gr_zbc_clear_color,
	.clear_depth = gp100_gr_zbc_clear_depth,
	.stencil_get = gp102_gr_zbc_stencil_get,
	.clear_stencil = gp102_gr_zbc_clear_stencil,
पूर्ण;

व्योम
gp102_gr_init_swdx_pes_mask(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	u32 mask = 0, data, gpc;

	क्रम (gpc = 0; gpc < gr->gpc_nr; gpc++) अणु
		data = nvkm_rd32(device, GPC_UNIT(gpc, 0x0c50)) & 0x0000000f;
		mask |= data << (gpc * 4);
	पूर्ण

	nvkm_wr32(device, 0x4181d0, mask);
पूर्ण

अटल स्थिर काष्ठा gf100_gr_func
gp102_gr = अणु
	.oneinit_tiles = gm200_gr_oneinit_tiles,
	.oneinit_sm_id = gm200_gr_oneinit_sm_id,
	.init = gf100_gr_init,
	.init_gpc_mmu = gm200_gr_init_gpc_mmu,
	.init_vsc_stream_master = gk104_gr_init_vsc_stream_master,
	.init_zcull = gf117_gr_init_zcull,
	.init_num_active_ltcs = gm200_gr_init_num_active_ltcs,
	.init_rop_active_fbps = gp100_gr_init_rop_active_fbps,
	.init_swdx_pes_mask = gp102_gr_init_swdx_pes_mask,
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
	.gpc_nr = 6,
	.tpc_nr = 5,
	.ppc_nr = 3,
	.grctx = &gp102_grctx,
	.zbc = &gp102_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, KEPLER_INLINE_TO_MEMORY_B पूर्ण,
		अणु -1, -1, PASCAL_B, &gf100_fermi पूर्ण,
		अणु -1, -1, PASCAL_COMPUTE_B पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

MODULE_FIRMWARE("nvidia/gp102/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/gpccs_bl.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/gpccs_sig.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gp102/gr/sw_method_init.bin");

अटल स्थिर काष्ठा gf100_gr_fwअगर
gp102_gr_fwअगर[] = अणु
	अणु  0, gm200_gr_load, &gp102_gr, &gm200_gr_fecs_acr, &gm200_gr_gpccs_acr पूर्ण,
	अणु -1, gm200_gr_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gp102_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gp102_gr_fwअगर, device, type, inst, pgr);
पूर्ण
