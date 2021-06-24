<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * Authors: AMD
 *
 */

#समावेश "dm_services.h"
#समावेश "core_types.h"
#समावेश "resource.h"
#समावेश "custom_float.h"
#समावेश "dcn10_hw_sequencer.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "abm.h"
#समावेश "dmcu.h"
#समावेश "dcn10_optc.h"
#समावेश "dcn10/dcn10_dpp.h"
#समावेश "dcn10/dcn10_mpc.h"
#समावेश "timing_generator.h"
#समावेश "opp.h"
#समावेश "ipp.h"
#समावेश "mpc.h"
#समावेश "reg_helper.h"
#समावेश "dcn10_hubp.h"
#समावेश "dcn10_hubbub.h"
#समावेश "dcn10_cm_common.h"
#समावेश "clk_mgr.h"

अचिन्हित पूर्णांक snम_लिखो_count(अक्षर *pBuf, अचिन्हित पूर्णांक bufSize, अक्षर *fmt, ...)
अणु
	पूर्णांक ret_vsnम_लिखो;
	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed;

	बहु_सूची args;
	बहु_शुरू(args, fmt);

	ret_vsnम_लिखो = vsnम_लिखो(pBuf, bufSize, fmt, args);

	बहु_पूर्ण(args);

	अगर (ret_vsnम_लिखो > 0) अणु
		अगर (ret_vsnम_लिखो < bufSize)
			अक्षरs_prपूर्णांकed = ret_vsnम_लिखो;
		अन्यथा
			अक्षरs_prपूर्णांकed = bufSize - 1;
	पूर्ण अन्यथा
		अक्षरs_prपूर्णांकed = 0;

	वापस अक्षरs_prपूर्णांकed;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_hubbub_state(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा dcn_hubbub_wm wm;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	स्थिर uपूर्णांक32_t ref_clk_mhz = dc_ctx->dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000;
	अटल स्थिर अचिन्हित पूर्णांक frac = 1000;

	स_रखो(&wm, 0, माप(काष्ठा dcn_hubbub_wm));
	dc->res_pool->hubbub->funcs->wm_पढ़ो_state(dc->res_pool->hubbub, &wm);

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "wm_set_index,data_urgent,pte_meta_urgent,sr_enter,sr_exit,dram_clk_chanage\n");
	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा dcn_hubbub_wm_set *s;

		s = &wm.sets[i];

		अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%d.%03d,%d.%03d,%d.%03d,%d.%03d,%d.%03d\n",
			s->wm_set,
			(s->data_urgent * frac) / ref_clk_mhz / frac, (s->data_urgent * frac) / ref_clk_mhz % frac,
			(s->pte_meta_urgent * frac) / ref_clk_mhz / frac, (s->pte_meta_urgent * frac) / ref_clk_mhz % frac,
			(s->sr_enter * frac) / ref_clk_mhz / frac, (s->sr_enter * frac) / ref_clk_mhz % frac,
			(s->sr_निकास * frac) / ref_clk_mhz / frac, (s->sr_निकास * frac) / ref_clk_mhz % frac,
			(s->dram_clk_chanage * frac) / ref_clk_mhz / frac, (s->dram_clk_chanage * frac) / ref_clk_mhz % frac);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		pBuf += अक्षरs_prपूर्णांकed;
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_hubp_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize, bool invarOnly)
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	स्थिर uपूर्णांक32_t ref_clk_mhz = dc_ctx->dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000;
	अटल स्थिर अचिन्हित पूर्णांक frac = 1000;

	अगर (invarOnly)
		अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,format,addr_hi,width,height,rotation,mirror,sw_mode,dcc_en,blank_en,ttu_dis,underflow,"
			"min_ttu_vblank,qos_low_wm,qos_high_wm"
			"\n");
	अन्यथा
		अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,format,addr_hi,addr_lo,width,height,rotation,mirror,sw_mode,dcc_en,blank_en,ttu_dis,underflow,"
					"min_ttu_vblank,qos_low_wm,qos_high_wm"
					"\n");

	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा hubp *hubp = pool->hubps[i];
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_पढ़ो_state(hubp);

		अगर (!s->blank_en) अणु
			अगर (invarOnly)
				अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%x,%x,%d,%d,%x,%x,%x,%x,%x,%x,%x,"
					"%d.%03d,%d.%03d,%d.%03d"
					"\n",
					hubp->inst,
					s->pixel_क्रमmat,
					s->inuse_addr_hi,
					s->viewport_width,
					s->viewport_height,
					s->rotation_angle,
					s->h_mirror_en,
					s->sw_mode,
					s->dcc_en,
					s->blank_en,
					s->ttu_disable,
					s->underflow_status,
					(s->min_ttu_vblank * frac) / ref_clk_mhz / frac, (s->min_ttu_vblank * frac) / ref_clk_mhz % frac,
					(s->qos_level_low_wm * frac) / ref_clk_mhz / frac, (s->qos_level_low_wm * frac) / ref_clk_mhz % frac,
					(s->qos_level_high_wm * frac) / ref_clk_mhz / frac, (s->qos_level_high_wm * frac) / ref_clk_mhz % frac);
			अन्यथा
				अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%x,%x,%x,%d,%d,%x,%x,%x,%x,%x,%x,%x,"
					"%d.%03d,%d.%03d,%d.%03d"
					"\n",
					hubp->inst,
					s->pixel_क्रमmat,
					s->inuse_addr_hi,
					s->inuse_addr_lo,
					s->viewport_width,
					s->viewport_height,
					s->rotation_angle,
					s->h_mirror_en,
					s->sw_mode,
					s->dcc_en,
					s->blank_en,
					s->ttu_disable,
					s->underflow_status,
					(s->min_ttu_vblank * frac) / ref_clk_mhz / frac, (s->min_ttu_vblank * frac) / ref_clk_mhz % frac,
					(s->qos_level_low_wm * frac) / ref_clk_mhz / frac, (s->qos_level_low_wm * frac) / ref_clk_mhz % frac,
					(s->qos_level_high_wm * frac) / ref_clk_mhz / frac, (s->qos_level_high_wm * frac) / ref_clk_mhz % frac);

			reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
			pBuf += अक्षरs_prपूर्णांकed;
		पूर्ण
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_rq_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,drq_exp_m,prq_exp_m,mrq_exp_m,crq_exp_m,plane1_ba,"
		"luma_chunk_s,luma_min_chu_s,luma_meta_ch_s,luma_min_m_c_s,luma_dpte_gr_s,luma_mpte_gr_s,luma_swath_hei,luma_pte_row_h,"
		"chroma_chunk_s,chroma_min_chu_s,chroma_meta_ch_s,chroma_min_m_c_s,chroma_dpte_gr_s,chroma_mpte_gr_s,chroma_swath_hei,chroma_pte_row_h"
		"\n");
	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(pool->hubps[i])->state);
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs = &s->rq_regs;

		अगर (!s->blank_en) अणु
			अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,%x"
				"\n",
				pool->hubps[i]->inst, rq_regs->drq_expansion_mode, rq_regs->prq_expansion_mode, rq_regs->mrq_expansion_mode,
				rq_regs->crq_expansion_mode, rq_regs->plane1_base_address, rq_regs->rq_regs_l.chunk_size,
				rq_regs->rq_regs_l.min_chunk_size, rq_regs->rq_regs_l.meta_chunk_size,
				rq_regs->rq_regs_l.min_meta_chunk_size, rq_regs->rq_regs_l.dpte_group_size,
				rq_regs->rq_regs_l.mpte_group_size, rq_regs->rq_regs_l.swath_height,
				rq_regs->rq_regs_l.pte_row_height_linear, rq_regs->rq_regs_c.chunk_size, rq_regs->rq_regs_c.min_chunk_size,
				rq_regs->rq_regs_c.meta_chunk_size, rq_regs->rq_regs_c.min_meta_chunk_size,
				rq_regs->rq_regs_c.dpte_group_size, rq_regs->rq_regs_c.mpte_group_size,
				rq_regs->rq_regs_c.swath_height, rq_regs->rq_regs_c.pte_row_height_linear);

			reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
			pBuf += अक्षरs_prपूर्णांकed;
		पूर्ण
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_dlg_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,rc_hbe,dlg_vbe,min_d_y_n,rc_per_ht,rc_x_a_s,"
		"dst_y_a_s,dst_y_pf,dst_y_vvb,dst_y_rvb,dst_y_vfl,dst_y_rfl,rf_pix_fq,"
		"vratio_pf,vrat_pf_c,rc_pg_vbl,rc_pg_vbc,rc_mc_vbl,rc_mc_vbc,rc_pg_fll,"
		"rc_pg_flc,rc_mc_fll,rc_mc_flc,pr_nom_l,pr_nom_c,rc_pg_nl,rc_pg_nc,"
		"mr_nom_l,mr_nom_c,rc_mc_nl,rc_mc_nc,rc_ld_pl,rc_ld_pc,rc_ld_l,"
		"rc_ld_c,cha_cur0,ofst_cur1,cha_cur1,vr_af_vc0,ddrq_limt,x_rt_dlay,x_rp_dlay,x_rr_sfl"
		"\n");
	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(pool->hubps[i])->state);
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_regs = &s->dlg_attr;

		अगर (!s->blank_en) अणु
			अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,%x,%x,%x"
				"\n",
				pool->hubps[i]->inst, dlg_regs->refcyc_h_blank_end, dlg_regs->dlg_vblank_end, dlg_regs->min_dst_y_next_start,
				dlg_regs->refcyc_per_htotal, dlg_regs->refcyc_x_after_scaler, dlg_regs->dst_y_after_scaler,
				dlg_regs->dst_y_prefetch, dlg_regs->dst_y_per_vm_vblank, dlg_regs->dst_y_per_row_vblank,
				dlg_regs->dst_y_per_vm_flip, dlg_regs->dst_y_per_row_flip, dlg_regs->ref_freq_to_pix_freq,
				dlg_regs->vratio_prefetch, dlg_regs->vratio_prefetch_c, dlg_regs->refcyc_per_pte_group_vblank_l,
				dlg_regs->refcyc_per_pte_group_vblank_c, dlg_regs->refcyc_per_meta_chunk_vblank_l,
				dlg_regs->refcyc_per_meta_chunk_vblank_c, dlg_regs->refcyc_per_pte_group_flip_l,
				dlg_regs->refcyc_per_pte_group_flip_c, dlg_regs->refcyc_per_meta_chunk_flip_l,
				dlg_regs->refcyc_per_meta_chunk_flip_c, dlg_regs->dst_y_per_pte_row_nom_l,
				dlg_regs->dst_y_per_pte_row_nom_c, dlg_regs->refcyc_per_pte_group_nom_l,
				dlg_regs->refcyc_per_pte_group_nom_c, dlg_regs->dst_y_per_meta_row_nom_l,
				dlg_regs->dst_y_per_meta_row_nom_c, dlg_regs->refcyc_per_meta_chunk_nom_l,
				dlg_regs->refcyc_per_meta_chunk_nom_c, dlg_regs->refcyc_per_line_delivery_pre_l,
				dlg_regs->refcyc_per_line_delivery_pre_c, dlg_regs->refcyc_per_line_delivery_l,
				dlg_regs->refcyc_per_line_delivery_c, dlg_regs->chunk_hdl_adjust_cur0, dlg_regs->dst_y_offset_cur1,
				dlg_regs->chunk_hdl_adjust_cur1, dlg_regs->vपढ़ोy_after_vcount0, dlg_regs->dst_y_delta_drq_limit,
				dlg_regs->xfc_reg_transfer_delay, dlg_regs->xfc_reg_preअक्षरge_delay,
				dlg_regs->xfc_reg_remote_surface_flip_latency);

			reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
			pBuf += अक्षरs_prपूर्णांकed;
		पूर्ण
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_ttu_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,qos_ll_wm,qos_lh_wm,mn_ttu_vb,qos_l_flp,rc_rd_p_l,rc_rd_l,rc_rd_p_c,"
		"rc_rd_c,rc_rd_c0,rc_rd_pc0,rc_rd_c1,rc_rd_pc1,qos_lf_l,qos_rds_l,"
		"qos_lf_c,qos_rds_c,qos_lf_c0,qos_rds_c0,qos_lf_c1,qos_rds_c1"
		"\n");
	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(pool->hubps[i])->state);
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_regs = &s->ttu_attr;

		अगर (!s->blank_en) अणु
			अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x,%x,"
				"%x,%x,%x,%x,%x,%x"
				"\n",
				pool->hubps[i]->inst, ttu_regs->qos_level_low_wm, ttu_regs->qos_level_high_wm, ttu_regs->min_ttu_vblank,
				ttu_regs->qos_level_flip, ttu_regs->refcyc_per_req_delivery_pre_l, ttu_regs->refcyc_per_req_delivery_l,
				ttu_regs->refcyc_per_req_delivery_pre_c, ttu_regs->refcyc_per_req_delivery_c, ttu_regs->refcyc_per_req_delivery_cur0,
				ttu_regs->refcyc_per_req_delivery_pre_cur0, ttu_regs->refcyc_per_req_delivery_cur1,
				ttu_regs->refcyc_per_req_delivery_pre_cur1, ttu_regs->qos_level_fixed_l, ttu_regs->qos_ramp_disable_l,
				ttu_regs->qos_level_fixed_c, ttu_regs->qos_ramp_disable_c, ttu_regs->qos_level_fixed_cur0,
				ttu_regs->qos_ramp_disable_cur0, ttu_regs->qos_level_fixed_cur1, ttu_regs->qos_ramp_disable_cur1);

			reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
			pBuf += अक्षरs_prपूर्णांकed;
		पूर्ण
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_cm_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,igam_format,igam_mode,dgam_mode,rgam_mode,gamut_mode,"
		"c11_c12,c13_c14,c21_c22,c23_c24,c31_c32,c33_c34"
		"\n");
	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dpp *dpp = pool->dpps[i];
		काष्ठा dcn_dpp_state s = अणु0पूर्ण;

		dpp->funcs->dpp_पढ़ो_state(dpp, &s);

		अगर (s.is_enabled) अणु
			अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%x,"
					"%s,%s,%s,"
					"%x,%08x,%08x,%08x,%08x,%08x,%08x"
				"\n",
				dpp->inst, s.igam_input_क्रमmat,
				(s.igam_lut_mode == 0) ? "BypassFixed" :
					((s.igam_lut_mode == 1) ? "BypassFloat" :
					((s.igam_lut_mode == 2) ? "RAM" :
					((s.igam_lut_mode == 3) ? "RAM" :
								 "Unknown"))),
				(s.dgam_lut_mode == 0) ? "Bypass" :
					((s.dgam_lut_mode == 1) ? "sRGB" :
					((s.dgam_lut_mode == 2) ? "Ycc" :
					((s.dgam_lut_mode == 3) ? "RAM" :
					((s.dgam_lut_mode == 4) ? "RAM" :
								 "Unknown")))),
				(s.rgam_lut_mode == 0) ? "Bypass" :
					((s.rgam_lut_mode == 1) ? "sRGB" :
					((s.rgam_lut_mode == 2) ? "Ycc" :
					((s.rgam_lut_mode == 3) ? "RAM" :
					((s.rgam_lut_mode == 4) ? "RAM" :
								 "Unknown")))),
				s.gamut_remap_mode, s.gamut_remap_c11_c12,
				s.gamut_remap_c13_c14, s.gamut_remap_c21_c22, s.gamut_remap_c23_c24,
				s.gamut_remap_c31_c32, s.gamut_remap_c33_c34);

			reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
			pBuf += अक्षरs_prपूर्णांकed;
		पूर्ण
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_mpcc_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,opp,dpp,mpccbot,mode,alpha_mode,premult,overlap_only,idle\n");
	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा mpcc_state s = अणु0पूर्ण;

		pool->mpc->funcs->पढ़ो_mpcc_state(pool->mpc, i, &s);

		अगर (s.opp_id != 0xf) अणु
			अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%x,%x,%x,%x,%x,%x,%x,%x\n",
				i, s.opp_id, s.dpp_id, s.bot_mpcc_id,
				s.mode, s.alpha_mode, s.pre_multiplied_alpha, s.overlap_only,
				s.idle);

			reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
			pBuf += अक्षरs_prपूर्णांकed;
		पूर्ण
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_otg_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "instance,v_bs,v_be,v_ss,v_se,vpol,vmax,vmin,vmax_sel,vmin_sel,"
			"h_bs,h_be,h_ss,h_se,hpol,htot,vtot,underflow,pixelclk[khz]\n");
	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	क्रम (i = 0; i < pool->timing_generator_count; i++) अणु
		काष्ठा timing_generator *tg = pool->timing_generators[i];
		काष्ठा dcn_otg_state s = अणु0पूर्ण;
		पूर्णांक pix_clk = 0;

		optc1_पढ़ो_otg_state(DCN10TG_FROM_TG(tg), &s);
		pix_clk = dc->current_state->res_ctx.pipe_ctx[i].stream_res.pix_clk_params.requested_pix_clk_100hz / 10;

		//only prपूर्णांक अगर OTG master is enabled
		अगर (s.otg_enabled & 1) अणु
			अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, reमुख्यing_buffer, "%x,%d,%d,%d,%d,%d,%d,%d,%d,%d,"
				"%d,%d,%d,%d,%d,%d,%d,%d,%d"
				"\n",
				tg->inst,
				s.v_blank_start,
				s.v_blank_end,
				s.v_sync_a_start,
				s.v_sync_a_end,
				s.v_sync_a_pol,
				s.v_total_max,
				s.v_total_min,
				s.v_total_max_sel,
				s.v_total_min_sel,
				s.h_blank_start,
				s.h_blank_end,
				s.h_sync_a_start,
				s.h_sync_a_end,
				s.h_sync_a_pol,
				s.h_total,
				s.v_total,
				s.underflow_occurred_status,
				pix_clk);

			reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
			pBuf += अक्षरs_prपूर्णांकed;
		पूर्ण
	पूर्ण

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल अचिन्हित पूर्णांक dcn10_get_घड़ी_states(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize)
अणु
	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = bufSize;

	अक्षरs_prपूर्णांकed = snम_लिखो_count(pBuf, bufSize, "dcfclk,dcfclk_deep_sleep,dispclk,"
		"dppclk,fclk,socclk\n"
		"%d,%d,%d,%d,%d,%d\n",
		dc->current_state->bw_ctx.bw.dcn.clk.dcfclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.dispclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.dppclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.fclk_khz,
		dc->current_state->bw_ctx.bw.dcn.clk.socclk_khz);

	reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
	pBuf += अक्षरs_prपूर्णांकed;

	वापस bufSize - reमुख्यing_buffer;
पूर्ण

अटल व्योम dcn10_clear_otpc_underflow(काष्ठा dc *dc)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	क्रम (i = 0; i < pool->timing_generator_count; i++) अणु
		काष्ठा timing_generator *tg = pool->timing_generators[i];
		काष्ठा dcn_otg_state s = अणु0पूर्ण;

		optc1_पढ़ो_otg_state(DCN10TG_FROM_TG(tg), &s);

		अगर (s.otg_enabled & 1)
			tg->funcs->clear_optc_underflow(tg);
	पूर्ण
पूर्ण

अटल व्योम dcn10_clear_hubp_underflow(काष्ठा dc *dc)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा hubp *hubp = pool->hubps[i];
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_पढ़ो_state(hubp);

		अगर (!s->blank_en)
			hubp->funcs->hubp_clear_underflow(hubp);
	पूर्ण
पूर्ण

व्योम dcn10_clear_status_bits(काष्ठा dc *dc, अचिन्हित पूर्णांक mask)
अणु
	/*
	 *  Mask Format
	 *  Bit 0 - 31: Status bit to clear
	 *
	 *  Mask = 0x0 means clear all status bits
	 */
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_HUBP_UNDERFLOW	= 0x1;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_OTPC_UNDERFLOW	= 0x2;

	अगर (mask == 0x0)
		mask = 0xFFFFFFFF;

	अगर (mask & DC_HW_STATE_MASK_HUBP_UNDERFLOW)
		dcn10_clear_hubp_underflow(dc);

	अगर (mask & DC_HW_STATE_MASK_OTPC_UNDERFLOW)
		dcn10_clear_otpc_underflow(dc);
पूर्ण

व्योम dcn10_get_hw_state(काष्ठा dc *dc, अक्षर *pBuf, अचिन्हित पूर्णांक bufSize, अचिन्हित पूर्णांक mask)
अणु
	/*
	 *  Mask Format
	 *  Bit 0 - 15: Hardware block mask
	 *  Bit 15: 1 = Invariant Only, 0 = All
	 */
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_HUBBUB			= 0x1;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_HUBP			= 0x2;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_RQ				= 0x4;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_DLG				= 0x8;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_TTU				= 0x10;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_CM				= 0x20;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_MPCC			= 0x40;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_OTG				= 0x80;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_MASK_CLOCKS			= 0x100;
	स्थिर अचिन्हित पूर्णांक DC_HW_STATE_INVAR_ONLY			= 0x8000;

	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buf_size = bufSize;

	अगर (mask == 0x0)
		mask = 0xFFFF; // Default, capture all, invariant only

	अगर ((mask & DC_HW_STATE_MASK_HUBBUB) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_hubbub_state(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_HUBP) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_hubp_states(dc, pBuf, reमुख्यing_buf_size, mask & DC_HW_STATE_INVAR_ONLY);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_RQ) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_rq_states(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_DLG) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_dlg_states(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_TTU) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_ttu_states(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_CM) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_cm_states(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_MPCC) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_mpcc_states(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_OTG) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_otg_states(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण

	अगर ((mask & DC_HW_STATE_MASK_CLOCKS) && reमुख्यing_buf_size > 0) अणु
		अक्षरs_prपूर्णांकed = dcn10_get_घड़ी_states(dc, pBuf, reमुख्यing_buf_size);
		pBuf += अक्षरs_prपूर्णांकed;
		reमुख्यing_buf_size -= अक्षरs_prपूर्णांकed;
	पूर्ण
पूर्ण
