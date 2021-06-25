<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_GRCTX_NVC0_H__
#घोषणा __NVKM_GRCTX_NVC0_H__
#समावेश "gf100.h"

काष्ठा gf100_grctx अणु
	काष्ठा gf100_gr *gr;
	काष्ठा gf100_gr_data *data;
	काष्ठा gf100_gr_mmio *mmio;
	पूर्णांक buffer_nr;
	u64 buffer[4];
	u64 addr;
पूर्ण;

पूर्णांक  gf100_grctx_mmio_data(काष्ठा gf100_grctx *, u32 size, u32 align, bool priv);
व्योम gf100_grctx_mmio_item(काष्ठा gf100_grctx *, u32 addr, u32 data, पूर्णांक s, पूर्णांक);

#घोषणा mmio_vram(a,b,c,d) gf100_grctx_mmio_data((a), (b), (c), (d))
#घोषणा mmio_refn(a,b,c,d,e) gf100_grctx_mmio_item((a), (b), (c), (d), (e))
#घोषणा mmio_skip(a,b,c) mmio_refn((a), (b), (c), -1, -1)
#घोषणा mmio_wr32(a,b,c) mmio_refn((a), (b), (c),  0, -1)

काष्ठा gf100_grctx_func अणु
	व्योम (*unkn88c)(काष्ठा gf100_gr *, bool on);
	/* मुख्य context generation function */
	व्योम  (*मुख्य)(काष्ठा gf100_gr *, काष्ठा gf100_grctx *);
	/* context-specअगरic modअगरy-on-first-load list generation function */
	व्योम  (*unkn)(काष्ठा gf100_gr *);
	/* mmio context data */
	स्थिर काष्ठा gf100_gr_pack *hub;
	स्थिर काष्ठा gf100_gr_pack *gpc_0;
	स्थिर काष्ठा gf100_gr_pack *gpc_1;
	स्थिर काष्ठा gf100_gr_pack *zcull;
	स्थिर काष्ठा gf100_gr_pack *tpc;
	स्थिर काष्ठा gf100_gr_pack *ppc;
	/* indirect context data, generated with icmds/mthds */
	स्थिर काष्ठा gf100_gr_pack *icmd;
	स्थिर काष्ठा gf100_gr_pack *mthd;
	स्थिर काष्ठा gf100_gr_pack *sw_veid_bundle_init;
	/* bundle circular buffer */
	व्योम (*bundle)(काष्ठा gf100_grctx *);
	u32 bundle_size;
	u32 bundle_min_gpm_fअगरo_depth;
	u32 bundle_token_limit;
	/* pagepool */
	व्योम (*pagepool)(काष्ठा gf100_grctx *);
	u32 pagepool_size;
	/* attribute(/alpha) circular buffer */
	व्योम (*attrib)(काष्ठा gf100_grctx *);
	u32 attrib_nr_max;
	u32 attrib_nr;
	u32 alpha_nr_max;
	u32 alpha_nr;
	u32 gfxp_nr;
	/* other patch buffer stuff */
	व्योम (*patch_ltc)(काष्ठा gf100_grctx *);
	/* न्यूनमानsweeping */
	व्योम (*sm_id)(काष्ठा gf100_gr *, पूर्णांक gpc, पूर्णांक tpc, पूर्णांक sm);
	व्योम (*tpc_nr)(काष्ठा gf100_gr *, पूर्णांक gpc);
	bool skip_pd_num_tpc_per_gpc;
	व्योम (*r4060a8)(काष्ठा gf100_gr *);
	व्योम (*rop_mapping)(काष्ठा gf100_gr *);
	व्योम (*alpha_beta_tables)(काष्ठा gf100_gr *);
	व्योम (*max_ways_evict)(काष्ठा gf100_gr *);
	व्योम (*dist_skip_table)(काष्ठा gf100_gr *);
	व्योम (*r406500)(काष्ठा gf100_gr *);
	व्योम (*gpc_tpc_nr)(काष्ठा gf100_gr *);
	व्योम (*r419f78)(काष्ठा gf100_gr *);
	व्योम (*tpc_mask)(काष्ठा gf100_gr *);
	व्योम (*smid_config)(काष्ठा gf100_gr *);
	/* misc other things */
	व्योम (*r400088)(काष्ठा gf100_gr *, bool);
	व्योम (*r419cb8)(काष्ठा gf100_gr *);
	व्योम (*r418800)(काष्ठा gf100_gr *);
	व्योम (*r419eb0)(काष्ठा gf100_gr *);
	व्योम (*r419e00)(काष्ठा gf100_gr *);
	व्योम (*r418e94)(काष्ठा gf100_gr *);
	व्योम (*r419a3c)(काष्ठा gf100_gr *);
	व्योम (*r408840)(काष्ठा gf100_gr *);
	व्योम (*r419c0c)(काष्ठा gf100_gr *);
पूर्ण;

बाह्य स्थिर काष्ठा gf100_grctx_func gf100_grctx;
पूर्णांक  gf100_grctx_generate(काष्ठा gf100_gr *);
व्योम gf100_grctx_generate_मुख्य(काष्ठा gf100_gr *, काष्ठा gf100_grctx *);
व्योम gf100_grctx_generate_bundle(काष्ठा gf100_grctx *);
व्योम gf100_grctx_generate_pagepool(काष्ठा gf100_grctx *);
व्योम gf100_grctx_generate_attrib(काष्ठा gf100_grctx *);
व्योम gf100_grctx_generate_unkn(काष्ठा gf100_gr *);
व्योम gf100_grctx_generate_न्यूनमानsweep(काष्ठा gf100_gr *);
व्योम gf100_grctx_generate_sm_id(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक, पूर्णांक);
व्योम gf100_grctx_generate_tpc_nr(काष्ठा gf100_gr *, पूर्णांक);
व्योम gf100_grctx_generate_r4060a8(काष्ठा gf100_gr *);
व्योम gf100_grctx_generate_rop_mapping(काष्ठा gf100_gr *);
व्योम gf100_grctx_generate_alpha_beta_tables(काष्ठा gf100_gr *);
व्योम gf100_grctx_generate_max_ways_evict(काष्ठा gf100_gr *);
व्योम gf100_grctx_generate_r419cb8(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gf108_grctx;
व्योम gf108_grctx_generate_attrib(काष्ठा gf100_grctx *);
व्योम gf108_grctx_generate_unkn(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gf104_grctx;
बाह्य स्थिर काष्ठा gf100_grctx_func gf110_grctx;

बाह्य स्थिर काष्ठा gf100_grctx_func gf117_grctx;
व्योम gf117_grctx_generate_attrib(काष्ठा gf100_grctx *);
व्योम gf117_grctx_generate_rop_mapping(काष्ठा gf100_gr *);
व्योम gf117_grctx_generate_dist_skip_table(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gf119_grctx;

बाह्य स्थिर काष्ठा gf100_grctx_func gk104_grctx;
व्योम gk104_grctx_generate_alpha_beta_tables(काष्ठा gf100_gr *);
व्योम gk104_grctx_generate_gpc_tpc_nr(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gk20a_grctx;
व्योम gk104_grctx_generate_bundle(काष्ठा gf100_grctx *);
व्योम gk104_grctx_generate_pagepool(काष्ठा gf100_grctx *);
व्योम gk104_grctx_generate_patch_ltc(काष्ठा gf100_grctx *);
व्योम gk104_grctx_generate_unkn(काष्ठा gf100_gr *);
व्योम gk104_grctx_generate_r418800(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gk110_grctx;
व्योम gk110_grctx_generate_r419eb0(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gk110b_grctx;
बाह्य स्थिर काष्ठा gf100_grctx_func gk208_grctx;

बाह्य स्थिर काष्ठा gf100_grctx_func gm107_grctx;
व्योम gm107_grctx_generate_bundle(काष्ठा gf100_grctx *);
व्योम gm107_grctx_generate_pagepool(काष्ठा gf100_grctx *);
व्योम gm107_grctx_generate_attrib(काष्ठा gf100_grctx *);
व्योम gm107_grctx_generate_sm_id(काष्ठा gf100_gr *, पूर्णांक, पूर्णांक, पूर्णांक);

बाह्य स्थिर काष्ठा gf100_grctx_func gm200_grctx;
व्योम gm200_grctx_generate_dist_skip_table(काष्ठा gf100_gr *);
व्योम gm200_grctx_generate_r406500(काष्ठा gf100_gr *);
व्योम gm200_grctx_generate_tpc_mask(काष्ठा gf100_gr *);
व्योम gm200_grctx_generate_smid_config(काष्ठा gf100_gr *);
व्योम gm200_grctx_generate_r419a3c(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gm20b_grctx;

बाह्य स्थिर काष्ठा gf100_grctx_func gp100_grctx;
व्योम gp100_grctx_generate_pagepool(काष्ठा gf100_grctx *);
व्योम gp100_grctx_generate_smid_config(काष्ठा gf100_gr *);

बाह्य स्थिर काष्ठा gf100_grctx_func gp102_grctx;
व्योम gp102_grctx_generate_attrib(काष्ठा gf100_grctx *);

बाह्य स्थिर काष्ठा gf100_grctx_func gp104_grctx;

बाह्य स्थिर काष्ठा gf100_grctx_func gp107_grctx;

बाह्य स्थिर काष्ठा gf100_grctx_func gv100_grctx;

बाह्य स्थिर काष्ठा gf100_grctx_func tu102_grctx;
व्योम gv100_grctx_unkn88c(काष्ठा gf100_gr *, bool);
व्योम gv100_grctx_generate_unkn(काष्ठा gf100_gr *);
बाह्य स्थिर काष्ठा gf100_gr_init gv100_grctx_init_sw_veid_bundle_init_0[];
व्योम gv100_grctx_generate_attrib(काष्ठा gf100_grctx *);
व्योम gv100_grctx_generate_rop_mapping(काष्ठा gf100_gr *);
व्योम gv100_grctx_generate_r400088(काष्ठा gf100_gr *, bool);

/* context init value lists */

बाह्य स्थिर काष्ठा gf100_gr_pack gf100_grctx_pack_icmd[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf100_grctx_pack_mthd[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_902d_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_9039_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_90c0_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf100_grctx_pack_hub[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_मुख्य_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_fe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_pri_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_memfmt_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_rstr2d_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_scc_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf100_grctx_pack_gpc_0[];
बाह्य स्थिर काष्ठा gf100_gr_pack gf100_grctx_pack_gpc_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_gpc_unk_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_prop_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_gpc_unk_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_zcull_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_crstr_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_gpm_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_gcc_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf100_grctx_pack_zcull[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf100_grctx_pack_tpc[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_pe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_wwdx_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_mpc_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf100_grctx_init_tpccs_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf104_grctx_init_tex_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf104_grctx_init_l1c_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf104_grctx_init_sm_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf108_grctx_init_9097_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf108_grctx_init_gpm_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf108_grctx_init_pe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf108_grctx_init_wwdx_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf108_grctx_init_tpccs_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf110_grctx_init_9197_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf110_grctx_init_9297_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf119_grctx_pack_icmd[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf119_grctx_pack_mthd[];

बाह्य स्थिर काष्ठा gf100_gr_init gf119_grctx_init_fe_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_grctx_init_be_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf119_grctx_init_prop_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_grctx_init_gpc_unk_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gf119_grctx_init_crstr_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf119_grctx_init_sm_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf117_grctx_init_pe_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gf117_grctx_init_wwdx_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gf117_grctx_pack_gpc_1[];

बाह्य स्थिर काष्ठा gf100_gr_init gk104_grctx_init_memfmt_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk104_grctx_init_ds_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk104_grctx_init_scc_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gk104_grctx_init_gpm_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gk104_grctx_init_pes_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gk104_grctx_pack_hub[];
बाह्य स्थिर काष्ठा gf100_gr_pack gk104_grctx_pack_tpc[];
बाह्य स्थिर काष्ठा gf100_gr_pack gk104_grctx_pack_ppc[];
बाह्य स्थिर काष्ठा gf100_gr_pack gk104_grctx_pack_icmd[];
बाह्य स्थिर काष्ठा gf100_gr_init gk104_grctx_init_a097_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gk110_grctx_pack_icmd[];

बाह्य स्थिर काष्ठा gf100_gr_pack gk110_grctx_pack_mthd[];

बाह्य स्थिर काष्ठा gf100_gr_pack gk110_grctx_pack_hub[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_grctx_init_pri_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_grctx_init_cwd_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gk110_grctx_pack_gpc_0[];
बाह्य स्थिर काष्ठा gf100_gr_pack gk110_grctx_pack_gpc_1[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_grctx_init_gpc_unk_2[];

बाह्य स्थिर काष्ठा gf100_gr_init gk110_grctx_init_tex_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_grctx_init_mpc_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk110_grctx_init_l1c_0[];

बाह्य स्थिर काष्ठा gf100_gr_pack gk110_grctx_pack_ppc[];

बाह्य स्थिर काष्ठा gf100_gr_init gk208_grctx_init_rstr2d_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gk208_grctx_init_prop_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gk208_grctx_init_crstr_0[];

बाह्य स्थिर काष्ठा gf100_gr_init gm107_grctx_init_gpc_unk_0[];
बाह्य स्थिर काष्ठा gf100_gr_init gm107_grctx_init_wwdx_0[];
#पूर्ण_अगर
