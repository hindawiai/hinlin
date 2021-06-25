<शैली गुरु>
/*
 * Copyright 2018 Red Hat Inc.
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
#समावेश "ctxgf100.h"

#समावेश <nvअगर/class.h>

अटल व्योम
gv100_gr_trap_sm(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc, पूर्णांक sm)
अणु
	काष्ठा nvkm_subdev *subdev = &gr->base.engine.subdev;
	काष्ठा nvkm_device *device = subdev->device;
	u32 werr = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x730 + (sm * 0x80)));
	u32 gerr = nvkm_rd32(device, TPC_UNIT(gpc, tpc, 0x734 + (sm * 0x80)));
	स्थिर काष्ठा nvkm_क्रमागत *warp;
	अक्षर glob[128];

	nvkm_snprपूर्णांकbf(glob, माप(glob), gf100_mp_global_error, gerr);
	warp = nvkm_क्रमागत_find(gf100_mp_warp_error, werr & 0xffff);

	nvkm_error(subdev, "GPC%i/TPC%i/SM%d trap: "
			   "global %08x [%s] warp %04x [%s]\n",
		   gpc, tpc, sm, gerr, glob, werr, warp ? warp->name : "");

	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x730 + sm * 0x80), 0x00000000);
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x734 + sm * 0x80), gerr);
पूर्ण

व्योम
gv100_gr_trap_mp(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc)
अणु
	gv100_gr_trap_sm(gr, gpc, tpc, 0);
	gv100_gr_trap_sm(gr, gpc, tpc, 1);
पूर्ण

अटल व्योम
gv100_gr_init_4188a4(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_mask(device, 0x4188a4, 0x03000000, 0x03000000);
पूर्ण

व्योम
gv100_gr_init_shader_exceptions(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	पूर्णांक sm;
	क्रम (sm = 0; sm < 0x100; sm += 0x80) अणु
		nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x728 + sm), 0x0085eb64);
		nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x610), 0x00000001);
		nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x72c + sm), 0x00000004);
	पूर्ण
पूर्ण

व्योम
gv100_gr_init_504430(काष्ठा gf100_gr *gr, पूर्णांक gpc, पूर्णांक tpc)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_wr32(device, TPC_UNIT(gpc, tpc, 0x430), 0x403f0000);
पूर्ण

व्योम
gv100_gr_init_419bd8(काष्ठा gf100_gr *gr)
अणु
	काष्ठा nvkm_device *device = gr->base.engine.subdev.device;
	nvkm_mask(device, 0x419bd8, 0x00000700, 0x00000000);
पूर्ण

अटल स्थिर काष्ठा gf100_gr_func
gv100_gr = अणु
	.oneinit_tiles = gm200_gr_oneinit_tiles,
	.oneinit_sm_id = gm200_gr_oneinit_sm_id,
	.init = gf100_gr_init,
	.init_419bd8 = gv100_gr_init_419bd8,
	.init_gpc_mmu = gm200_gr_init_gpc_mmu,
	.init_vsc_stream_master = gk104_gr_init_vsc_stream_master,
	.init_zcull = gf117_gr_init_zcull,
	.init_num_active_ltcs = gm200_gr_init_num_active_ltcs,
	.init_rop_active_fbps = gp100_gr_init_rop_active_fbps,
	.init_swdx_pes_mask = gp102_gr_init_swdx_pes_mask,
	.init_fecs_exceptions = gp100_gr_init_fecs_exceptions,
	.init_ds_hww_esr_2 = gm200_gr_init_ds_hww_esr_2,
	.init_sked_hww_esr = gk104_gr_init_sked_hww_esr,
	.init_ppc_exceptions = gk104_gr_init_ppc_exceptions,
	.init_504430 = gv100_gr_init_504430,
	.init_shader_exceptions = gv100_gr_init_shader_exceptions,
	.init_4188a4 = gv100_gr_init_4188a4,
	.trap_mp = gv100_gr_trap_mp,
	.rops = gm200_gr_rops,
	.gpc_nr = 6,
	.tpc_nr = 5,
	.ppc_nr = 3,
	.grctx = &gv100_grctx,
	.zbc = &gp102_gr_zbc,
	.sclass = अणु
		अणु -1, -1, FERMI_TWOD_A पूर्ण,
		अणु -1, -1, KEPLER_INLINE_TO_MEMORY_B पूर्ण,
		अणु -1, -1, VOLTA_A, &gf100_fermi पूर्ण,
		अणु -1, -1, VOLTA_COMPUTE_A पूर्ण,
		अणुपूर्ण
	पूर्ण
पूर्ण;

MODULE_FIRMWARE("nvidia/gv100/gr/fecs_bl.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/fecs_inst.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/fecs_data.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/fecs_sig.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/gpccs_bl.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/gpccs_inst.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/gpccs_data.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/gpccs_sig.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/sw_ctx.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/sw_nonctx.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/sw_bundle_init.bin");
MODULE_FIRMWARE("nvidia/gv100/gr/sw_method_init.bin");

अटल स्थिर काष्ठा gf100_gr_fwअगर
gv100_gr_fwअगर[] = अणु
	अणु  0, gm200_gr_load, &gv100_gr, &gp108_gr_fecs_acr, &gp108_gr_gpccs_acr पूर्ण,
	अणु -1, gm200_gr_nofw पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक
gv100_gr_new(काष्ठा nvkm_device *device, क्रमागत nvkm_subdev_type type, पूर्णांक inst, काष्ठा nvkm_gr **pgr)
अणु
	वापस gf100_gr_new_(gv100_gr_fwअगर, device, type, inst, pgr);
पूर्ण
