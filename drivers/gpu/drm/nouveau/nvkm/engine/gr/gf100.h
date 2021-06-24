<शैली गुरु>
/*
 * Copyright 2010 Red Hat Inc.
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
 * Authors: Ben Skeggs
 */
#अगर_अघोषित __GF100_GR_H__
#घोषणा __GF100_GR_H__
#घोषणा gf100_gr(p) container_of((p), काष्ठा gf100_gr, base)
#समावेश "priv.h"

#समावेश <core/gpuobj.h>
#समावेश <subdev/ltc.h>
#समावेश <subdev/mmu.h>
#समावेश <engine/falcon.h>

काष्ठा nvkm_acr_lsfw;

#घोषणा GPC_MAX 32
#घोषणा TPC_MAX_PER_GPC 8
#घोषणा TPC_MAX (GPC_MAX * TPC_MAX_PER_GPC)

#घोषणा ROP_BCAST(r)      (0x408800 + (r))
#घोषणा ROP_UNIT(u, r)    (0x410000 + (u) * 0x400 + (r))
#घोषणा GPC_BCAST(r)      (0x418000 + (r))
#घोषणा GPC_UNIT(t, r)    (0x500000 + (t) * 0x8000 + (r))
#घोषणा PPC_UNIT(t, m, r) (0x503000 + (t) * 0x8000 + (m) * 0x200 + (r))
#घोषणा TPC_UNIT(t, m, r) (0x504000 + (t) * 0x8000 + (m) * 0x800 + (r))

काष्ठा gf100_gr_data अणु
	u32 size;
	u32 align;
	bool priv;
पूर्ण;

काष्ठा gf100_gr_mmio अणु
	u32 addr;
	u32 data;
	u32 shअगरt;
	पूर्णांक buffer;
पूर्ण;

काष्ठा gf100_gr_zbc_color अणु
	u32 क्रमmat;
	u32 ds[4];
	u32 l2[4];
पूर्ण;

काष्ठा gf100_gr_zbc_depth अणु
	u32 क्रमmat;
	u32 ds;
	u32 l2;
पूर्ण;

काष्ठा gf100_gr_zbc_stencil अणु
	u32 क्रमmat;
	u32 ds;
	u32 l2;
पूर्ण;

काष्ठा gf100_gr अणु
	स्थिर काष्ठा gf100_gr_func *func;
	काष्ठा nvkm_gr base;

	काष्ठा अणु
		काष्ठा nvkm_falcon falcon;
		काष्ठा nvkm_blob inst;
		काष्ठा nvkm_blob data;

		काष्ठा mutex mutex;
		u32 disable;
	पूर्ण fecs;

	काष्ठा अणु
		काष्ठा nvkm_falcon falcon;
		काष्ठा nvkm_blob inst;
		काष्ठा nvkm_blob data;
	पूर्ण gpccs;

	bool firmware;

	/*
	 * Used अगर the रेजिस्टर packs are loaded from NVIDIA fw instead of
	 * using hardcoded arrays. To be allocated with vzalloc().
	 */
	काष्ठा gf100_gr_pack *sw_nonctx;
	काष्ठा gf100_gr_pack *sw_ctx;
	काष्ठा gf100_gr_pack *bundle;
	काष्ठा gf100_gr_pack *method;

	काष्ठा gf100_gr_zbc_color zbc_color[NVKM_LTC_MAX_ZBC_CNT];
	काष्ठा gf100_gr_zbc_depth zbc_depth[NVKM_LTC_MAX_ZBC_CNT];
	काष्ठा gf100_gr_zbc_stencil zbc_stencil[NVKM_LTC_MAX_ZBC_CNT];

	u8 rop_nr;
	u8 gpc_nr;
	u8 tpc_nr[GPC_MAX];
	u8 tpc_max;
	u8 tpc_total;
	u8 ppc_nr[GPC_MAX];
	u8 ppc_mask[GPC_MAX];
	u8 ppc_tpc_mask[GPC_MAX][4];
	u8 ppc_tpc_nr[GPC_MAX][4];
	u8 ppc_tpc_min;
	u8 ppc_tpc_max;

	u8 screen_tile_row_offset;
	u8 tile[TPC_MAX];

	काष्ठा अणु
		u8 gpc;
		u8 tpc;
	पूर्ण sm[TPC_MAX];
	u8 sm_nr;

	काष्ठा gf100_gr_data mmio_data[4];
	काष्ठा gf100_gr_mmio mmio_list[4096/8];
	u32  size;
	u32 *data;
	u32 size_zcull;
	u32 size_pm;
पूर्ण;

पूर्णांक gf100_gr_fecs_bind_poपूर्णांकer(काष्ठा gf100_gr *, u32 inst);

काष्ठा gf100_gr_func_zbc अणु
	व्योम (*clear_color)(काष्ठा gf100_gr *, पूर्णांक zbc);
	व्योम (*clear_depth)(काष्ठा gf100_gr *, पूर्णांक zbc);
	पूर्णांक (*stencil_get)(काष्ठा gf100_gr *, पूर्णांक क्रमmat,
			   स्थिर u32 ds, स्थिर u32 l2);
	व्योम (*clear_stencil)(काष्ठा gf100_gr *, पूर्णांक zbc);
पूर्ण;

काष्ठा gf100_gr_func अणु
	व्योम (*oneinit_tiles)(काष्ठा gf100_gr *);
	व्योम (*oneinit_sm_id)(काष्ठा gf100_gr *);
	पूर्णांक (*init)(काष्ठा gf100_gr *);
	व्योम (*init_419bd8)(काष्ठा gf100_gr *);
	व्योम (*init_gpc_mmu)(काष्ठा gf100_gr *);
	व्योम (*init_r405a14)(काष्ठा gf100_gr *);
	व्योम (*init_bios)(काष्ठा gf100_gr *);
	व्योम (*init_vsc_stream_master)(काष्ठा gf100_gr *);
	व्योम (*init_zcull)(काष्ठा gf100_gr *);
	व्योम (*init_num_active_ltcs)(काष्ठा gf100_gr *);
	व्योम (*init_rop_active_fbps)(काष्ठा gf100_gr *);
	व्योम (*init_bios_2)(काष्ठा gf100_gr *);
	व्योम (*init_swdx_pes_mask)(काष्ठा gf100_gr *);
	व्योम (*init_fs)(काष्ठा gf100_gr *);
	व्योम (*init_fecs_exceptions)(काष्ठा gf100_gr *);
	व्योम (*init_ds_hww_esr_2)(काष्ठा gf100_gr *);
	व्योम (*init_40601c)(काष्ठा gf100_gr *);
	व्योम (*init_sked_hww_esr)(काष्ठा gf100_gr *);
	व्योम (*init_419cc0)(काष्ठा gf100_gr *);
	व्योम (*init_419eb4)(काष्ठा gf100_gr *);
	व्योम (*init_419c9c)(काष्ठा gf100_gr *);
	व्योम (*init_ppc_exceptions)(काष्ठा gf100_gr *);
	व्योम (*init_tex_hww_esr)(काष्ठा gf100_gr *, पूर्णांक gpc, पूर्णांक tpc);
	व्योम (*init_504430)(काष्ठा gf100_gr *, पूर्णांक gpc, पूर्णांक tpc);
	व्योम (*init_shader_exceptions)(काष्ठा gf100_gr *, पूर्णांक gpc, पूर्णांक tpc);
	व्योम (*init_400054)(काष्ठा gf100_gr *);
	व्योम (*init_4188a4)(काष्ठा gf100_gr *);
	व्योम (*trap_mp)(काष्ठा gf100_gr *, पूर्णांक gpc, पूर्णांक tpc);
	व्योम (*set_hww_esr_report_mask)(काष्ठा gf100_gr *);
	स्थिर काष्ठा gf100_gr_pack *mmio;
	काष्ठा अणु
		काष्ठा gf100_gr_ucode *ucode;
	पूर्ण fecs;
	काष्ठा अणु
		काष्ठा gf100_gr_ucode *ucode;
	पूर्ण gpccs;
	पूर्णांक (*rops)(काष्ठा gf100_gr *);
	पूर्णांक gpc_nr;
	पूर्णांक tpc_nr;
	पूर्णांक ppc_nr;
	स्थिर काष्ठा gf100_grctx_func *grctx;
	स्थिर काष्ठा nvkm_therm_clkgate_pack *clkgate_pack;
	स्थिर काष्ठा gf100_gr_func_zbc *zbc;
	काष्ठा nvkm_sclass sclass[];
पूर्ण;

पूर्णांक gf100_gr_rops(काष्ठा gf100_gr *);
व्योम gf100_gr_oneinit_tiles(काष्ठा gf100_gr *);
व्योम gf100_gr_oneinit_sm_id(काष्ठा gf100_gr *);
पूर्णांक gf100_gr_init(काष्ठा gf100_gr *);
व्योम gf100_gr_init_vsc_stream_master(काष्ठा gf100_gr *);
व्योम gf100_gr_init_zcull(काष्ठा gf100_gr *);
व्योम gf100_gr_init_num_active_ltcs(काष्ठा gf100_gr *);
व्योम gf100_gr_init_fecs_exceptions(काष्ठा gf100_gr *);
व्योम gf100_gr_init_40601c(काष्ठा gf100_gr *);
व्योम gf100_gr_init_419cc0(काष्ठा gf100_gr *);
व्योम gf100_gr_init_419eb4(काष्ठा gf100_gr *);
व्योम gf100_gr_init_tex_hww_esr(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
व्योम gf100_gr_init_shader_exceptions(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
व्योम gf100_gr_init_400054(काष्ठा gf100_gr *);
व्योम gf100_gr_init_num_tpc_per_gpc(काष्ठा gf100_gr *, bool, bool);
बाह्य स्थिर काष्ठा gf100_gr_func_zbc gf100_gr_zbc;

व्योम gf117_gr_init_zcull(काष्ठा gf100_gr *);

व्योम gk104_gr_init_vsc_stream_master(काष्ठा gf100_gr *);
व्योम gk104_gr_init_rop_active_fbps(काष्ठा gf100_gr *);
व्योम gk104_gr_init_ppc_exceptions(काष्ठा gf100_gr *);
व्योम gk104_gr_init_sked_hww_esr(काष्ठा gf100_gr *);

व्योम gk110_gr_init_419eb4(काष्ठा gf100_gr *);

व्योम gm107_gr_init_504430(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
व्योम gm107_gr_init_shader_exceptions(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
व्योम gm107_gr_init_400054(काष्ठा gf100_gr *);

पूर्णांक gk20a_gr_init(काष्ठा gf100_gr *);

व्योम gm200_gr_oneinit_tiles(काष्ठा gf100_gr *);
व्योम gm200_gr_oneinit_sm_id(काष्ठा gf100_gr *);
पूर्णांक gm200_gr_rops(काष्ठा gf100_gr *);
व्योम gm200_gr_init_num_active_ltcs(काष्ठा gf100_gr *);
व्योम gm200_gr_init_ds_hww_esr_2(काष्ठा gf100_gr *);

व्योम gp100_gr_init_rop_active_fbps(काष्ठा gf100_gr *);
व्योम gp100_gr_init_fecs_exceptions(काष्ठा gf100_gr *);
व्योम gp100_gr_init_shader_exceptions(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
व्योम gp100_gr_zbc_clear_color(काष्ठा gf100_gr *, पूर्णांक);
व्योम gp100_gr_zbc_clear_depth(काष्ठा gf100_gr *, पूर्णांक);
बाह्य स्थिर काष्ठा gf100_gr_func_zbc gp100_gr_zbc;

व्योम gp102_gr_init_swdx_pes_mask(काष्ठा gf100_gr *);
बाह्य स्थिर काष्ठा gf100_gr_func_zbc gp102_gr_zbc;

बाह्य स्थिर काष्ठा gf100_gr_func gp107_gr;

व्योम gv100_gr_init_419bd8(काष्ठा gf100_gr *);
व्योम gv100_gr_init_504430(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
व्योम gv100_gr_init_shader_exceptions(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
व्योम gv100_gr_trap_mp(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);

#घोषणा gf100_gr_chan(p) container_of((p), काष्ठा gf100_gr_chan, object)
#समावेश <core/object.h>

काष्ठा gf100_gr_chan अणु
	काष्ठा nvkm_object object;
	काष्ठा gf100_gr *gr;
	काष्ठा nvkm_vmm *vmm;

	काष्ठा nvkm_memory *mmio;
	काष्ठा nvkm_vma *mmio_vma;
	पूर्णांक mmio_nr;

	काष्ठा अणु
		काष्ठा nvkm_memory *mem;
		काष्ठा nvkm_vma *vma;
	पूर्ण data[4];
पूर्ण;

व्योम gf100_gr_ctxctl_debug(काष्ठा gf100_gr *);

u64  gf100_gr_units(काष्ठा nvkm_gr *);
व्योम gf100_gr_zbc_init(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा nvkm_object_func gf100_fermi;

काष्ठा gf100_gr_init अणु
	u32 addr;
	u8  count;
	u32 pitch;
	u32 data;
पूर्ण;

काष्ठा gf100_gr_pack अणु
	स्थिर काष्ठा gf100_gr_init *init;
	u32 type;
पूर्ण;

#घोषणा pack_क्रम_each_init(init, pack, head)                                   \
	क्रम (pack = head; pack && pack->init; pack++)                          \
		  क्रम (init = pack->init; init && init->count; init++)

काष्ठा gf100_gr_ucode अणु
	काष्ठा nvkm_blob code;
	काष्ठा nvkm_blob data;
पूर्ण;

बाह्य काष्ठा gf100_gr_ucode gf100_gr_fecs_ucode;
बाह्य काष्ठा gf100_gr_ucode gf100_gr_gpccs_ucode;

बाह्य काष्ठा gf100_gr_ucode gk110_gr_fecs_ucode;
बाह्य काष्ठा gf100_gr_ucode gk110_gr_gpccs_ucode;

पूर्णांक  gf100_gr_रुको_idle(काष्ठा gf100_gr *);
व्योम gf100_gr_mmio(काष्ठा gf100_gr *, स्थिर काष्ठा gf100_gr_pack *);
व्योम gf100_gr_icmd(काष्ठा gf100_gr *, स्थिर काष्ठा gf100_gr_pack *);
व्योम gf100_gr_mthd(काष्ठा gf100_gr *, स्थिर काष्ठा gf100_gr_pack *);
पूर्णांक  gf100_gr_init_ctxctl(काष्ठा gf100_gr *);

/* रेजिस्टर init value lists */

बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_मुख्य_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_fe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_pri_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_rstr2d_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_pd_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_ds_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_scc_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_prop_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_gpc_unk_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_setup_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_crstr_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_setup_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_zcull_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_gpm_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_gpc_unk_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_gcc_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_tpccs_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_tex_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_pe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_l1c_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_wwdx_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_tpccs_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_mpc_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_be_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_fe_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_gr_init_pe_1[];
व्योम gf100_gr_init_gpc_mmu(काष्ठा gf100_gr *);
व्योम gf100_gr_trap_mp(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक);
बाह्य स्थिर काष्ठा nvkm_bitfield gf100_mp_global_error[];
बाह्य स्थिर काष्ठा nvkm_क्रमागत gf100_mp_warp_error[];

बाह्य स्थिर काष्ठा gf100_gr_init gf104_gr_init_ds_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf104_gr_init_tex_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf104_gr_init_sm_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf108_gr_init_gpc_unk_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf108_gr_init_setup_1[];

बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_pd_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_ds_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_prop_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_gpm_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_gpc_unk_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_tex_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_sm_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_gr_init_fe_1[];

बाह्य स्थिर काष्ठा gf100_gr_init gf117_gr_init_pes_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf117_gr_init_wwdx_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf117_gr_init_cbm_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gk104_gr_init_मुख्य_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk104_gr_init_gpc_unk_2[];
बाह्य स्थिर काष्ठा gf100_gr_init gk104_gr_init_tpccs_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk104_gr_init_pe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk104_gr_init_be_0[];
बाह्य स्थिर काष्ठा gf100_gr_pack gk104_gr_pack_mmio[];

बाह्य स्थिर काष्ठा gf100_gr_init gk110_gr_init_fe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_gr_init_ds_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_gr_init_sked_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_gr_init_cwd_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_gr_init_gpc_unk_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_gr_init_tex_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_gr_init_sm_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gk208_gr_init_gpc_unk_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_scc_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_prop_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_setup_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_zcull_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_gpc_unk_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_tex_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_l1c_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_wwdx_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_gr_init_cbm_0[];
व्योम gm107_gr_init_bios(काष्ठा gf100_gr *);

व्योम gm200_gr_init_gpc_mmu(काष्ठा gf100_gr *);

काष्ठा gf100_gr_fwअगर अणु
	पूर्णांक version;
	पूर्णांक (*load)(काष्ठा gf100_gr *, पूर्णांक ver, स्थिर काष्ठा gf100_gr_fwअगर *);
	स्थिर काष्ठा gf100_gr_func *func;
	स्थिर काष्ठा nvkm_acr_lsf_func *fecs;
	स्थिर काष्ठा nvkm_acr_lsf_func *gpccs;
पूर्ण;

पूर्णांक gf100_gr_load(काष्ठा gf100_gr *, पूर्णांक, स्थिर काष्ठा gf100_gr_fwअगर *);
पूर्णांक gf100_gr_nofw(काष्ठा gf100_gr *, पूर्णांक, स्थिर काष्ठा gf100_gr_fwअगर *);

पूर्णांक gk20a_gr_load_sw(काष्ठा gf100_gr *, स्थिर अक्षर *path, पूर्णांक ver);

पूर्णांक gm200_gr_nofw(काष्ठा gf100_gr *, पूर्णांक, स्थिर काष्ठा gf100_gr_fwअगर *);
पूर्णांक gm200_gr_load(काष्ठा gf100_gr *, पूर्णांक, स्थिर काष्ठा gf100_gr_fwअगर *);
बाह्य स्थिर काष्ठा nvkm_acr_lsf_func gm200_gr_gpccs_acr;
बाह्य स्थिर काष्ठा nvkm_acr_lsf_func gm200_gr_fecs_acr;

बाह्य स्थिर काष्ठा nvkm_acr_lsf_func gm20b_gr_fecs_acr;
व्योम gm20b_gr_acr_bld_ग_लिखो(काष्ठा nvkm_acr *, u32, काष्ठा nvkm_acr_lsfw *);
व्योम gm20b_gr_acr_bld_patch(काष्ठा nvkm_acr *, u32, s64);

बाह्य स्थिर काष्ठा nvkm_acr_lsf_func gp108_gr_gpccs_acr;
बाह्य स्थिर काष्ठा nvkm_acr_lsf_func gp108_gr_fecs_acr;

पूर्णांक gf100_gr_new_(स्थिर काष्ठा gf100_gr_fwअगर *, काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक,
		  काष्ठा nvkm_gr **);
#पूर्ण_अगर
