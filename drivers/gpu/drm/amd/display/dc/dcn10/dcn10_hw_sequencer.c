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

#समावेश <linux/delay.h>
#समावेश "dm_services.h"
#समावेश "basics/dc_common.h"
#समावेश "core_types.h"
#समावेश "resource.h"
#समावेश "custom_float.h"
#समावेश "dcn10_hw_sequencer.h"
#समावेश "dcn10_hw_sequencer_debug.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "abm.h"
#समावेश "dmcu.h"
#समावेश "dcn10_optc.h"
#समावेश "dcn10_dpp.h"
#समावेश "dcn10_mpc.h"
#समावेश "timing_generator.h"
#समावेश "opp.h"
#समावेश "ipp.h"
#समावेश "mpc.h"
#समावेश "reg_helper.h"
#समावेश "dcn10_hubp.h"
#समावेश "dcn10_hubbub.h"
#समावेश "dcn10_cm_common.h"
#समावेश "dc_link_dp.h"
#समावेश "dccg.h"
#समावेश "clk_mgr.h"
#समावेश "link_hwss.h"
#समावेश "dpcd_defs.h"
#समावेश "dsc.h"
#समावेश "dce/dmub_hw_lock_mgr.h"
#समावेश "dc_trace.h"
#समावेश "dce/dmub_outbox.h"

#घोषणा DC_LOGGER_INIT(logger)

#घोषणा CTX \
	hws->ctx
#घोषणा REG(reg)\
	hws->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name

/*prपूर्णांक is 17 wide, first two अक्षरacters are spaces*/
#घोषणा DTN_INFO_MICRO_SEC(ref_cycle) \
	prपूर्णांक_microsec(dc_ctx, log_ctx, ref_cycle)

#घोषणा GAMMA_HW_POINTS_NUM 256

व्योम prपूर्णांक_microsec(काष्ठा dc_context *dc_ctx,
	काष्ठा dc_log_buffer_ctx *log_ctx,
	uपूर्णांक32_t ref_cycle)
अणु
	स्थिर uपूर्णांक32_t ref_clk_mhz = dc_ctx->dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000;
	अटल स्थिर अचिन्हित पूर्णांक frac = 1000;
	uपूर्णांक32_t us_x10 = (ref_cycle * frac) / ref_clk_mhz;

	DTN_INFO("  %11d.%03d",
			us_x10 / frac,
			us_x10 % frac);
पूर्ण

व्योम dcn10_lock_all_pipes(काष्ठा dc *dc,
	काष्ठा dc_state *context,
	bool lock)
अणु
	काष्ठा pipe_ctx *pipe_ctx;
	काष्ठा timing_generator *tg;
	पूर्णांक i;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		pipe_ctx = &context->res_ctx.pipe_ctx[i];
		tg = pipe_ctx->stream_res.tg;

		/*
		 * Only lock the top pipe's tg to prevent redundant
		 * (un)locking. Also skip अगर pipe is disabled.
		 */
		अगर (pipe_ctx->top_pipe ||
		    !pipe_ctx->stream || !pipe_ctx->plane_state ||
		    !tg->funcs->is_tg_enabled(tg))
			जारी;

		अगर (lock)
			dc->hwss.pipe_control_lock(dc, pipe_ctx, true);
		अन्यथा
			dc->hwss.pipe_control_lock(dc, pipe_ctx, false);
	पूर्ण
पूर्ण

अटल व्योम log_mpc_crc(काष्ठा dc *dc,
	काष्ठा dc_log_buffer_ctx *log_ctx)
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	अगर (REG(MPC_CRC_RESULT_GB))
		DTN_INFO("MPC_CRC_RESULT_GB:%d MPC_CRC_RESULT_C:%d MPC_CRC_RESULT_AR:%d\n",
		REG_READ(MPC_CRC_RESULT_GB), REG_READ(MPC_CRC_RESULT_C), REG_READ(MPC_CRC_RESULT_AR));
	अगर (REG(DPP_TOP0_DPP_CRC_VAL_B_A))
		DTN_INFO("DPP_TOP0_DPP_CRC_VAL_B_A:%d DPP_TOP0_DPP_CRC_VAL_R_G:%d\n",
		REG_READ(DPP_TOP0_DPP_CRC_VAL_B_A), REG_READ(DPP_TOP0_DPP_CRC_VAL_R_G));
पूर्ण

व्योम dcn10_log_hubbub_state(काष्ठा dc *dc, काष्ठा dc_log_buffer_ctx *log_ctx)
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा dcn_hubbub_wm wm;
	पूर्णांक i;

	स_रखो(&wm, 0, माप(काष्ठा dcn_hubbub_wm));
	dc->res_pool->hubbub->funcs->wm_पढ़ो_state(dc->res_pool->hubbub, &wm);

	DTN_INFO("HUBBUB WM:      data_urgent  pte_meta_urgent"
			"         sr_enter          sr_exit  dram_clk_change\n");

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा dcn_hubbub_wm_set *s;

		s = &wm.sets[i];
		DTN_INFO("WM_Set[%d]:", s->wm_set);
		DTN_INFO_MICRO_SEC(s->data_urgent);
		DTN_INFO_MICRO_SEC(s->pte_meta_urgent);
		DTN_INFO_MICRO_SEC(s->sr_enter);
		DTN_INFO_MICRO_SEC(s->sr_निकास);
		DTN_INFO_MICRO_SEC(s->dram_clk_chanage);
		DTN_INFO("\n");
	पूर्ण

	DTN_INFO("\n");
पूर्ण

अटल व्योम dcn10_log_hubp_states(काष्ठा dc *dc, व्योम *log_ctx)
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	DTN_INFO(
		"HUBP:  format  addr_hi  width  height  rot  mir  sw_mode  dcc_en  blank_en  clock_en  ttu_dis  underflow   min_ttu_vblank       qos_low_wm      qos_high_wm\n");
	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा hubp *hubp = pool->hubps[i];
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_पढ़ो_state(hubp);

		अगर (!s->blank_en) अणु
			DTN_INFO("[%2d]:  %5xh  %6xh  %5d  %6d  %2xh  %2xh  %6xh  %6d  %8d  %8d  %7d  %8xh",
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
					s->घड़ी_en,
					s->ttu_disable,
					s->underflow_status);
			DTN_INFO_MICRO_SEC(s->min_ttu_vblank);
			DTN_INFO_MICRO_SEC(s->qos_level_low_wm);
			DTN_INFO_MICRO_SEC(s->qos_level_high_wm);
			DTN_INFO("\n");
		पूर्ण
	पूर्ण

	DTN_INFO("\n=========RQ========\n");
	DTN_INFO("HUBP:  drq_exp_m  prq_exp_m  mrq_exp_m  crq_exp_m  plane1_ba  L:chunk_s  min_chu_s  meta_ch_s"
		"  min_m_c_s  dpte_gr_s  mpte_gr_s  swath_hei  pte_row_h  C:chunk_s  min_chu_s  meta_ch_s"
		"  min_m_c_s  dpte_gr_s  mpte_gr_s  swath_hei  pte_row_h\n");
	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(pool->hubps[i])->state);
		काष्ठा _vcs_dpi_display_rq_regs_st *rq_regs = &s->rq_regs;

		अगर (!s->blank_en)
			DTN_INFO("[%2d]:  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh\n",
				pool->hubps[i]->inst, rq_regs->drq_expansion_mode, rq_regs->prq_expansion_mode, rq_regs->mrq_expansion_mode,
				rq_regs->crq_expansion_mode, rq_regs->plane1_base_address, rq_regs->rq_regs_l.chunk_size,
				rq_regs->rq_regs_l.min_chunk_size, rq_regs->rq_regs_l.meta_chunk_size,
				rq_regs->rq_regs_l.min_meta_chunk_size, rq_regs->rq_regs_l.dpte_group_size,
				rq_regs->rq_regs_l.mpte_group_size, rq_regs->rq_regs_l.swath_height,
				rq_regs->rq_regs_l.pte_row_height_linear, rq_regs->rq_regs_c.chunk_size, rq_regs->rq_regs_c.min_chunk_size,
				rq_regs->rq_regs_c.meta_chunk_size, rq_regs->rq_regs_c.min_meta_chunk_size,
				rq_regs->rq_regs_c.dpte_group_size, rq_regs->rq_regs_c.mpte_group_size,
				rq_regs->rq_regs_c.swath_height, rq_regs->rq_regs_c.pte_row_height_linear);
	पूर्ण

	DTN_INFO("========DLG========\n");
	DTN_INFO("HUBP:  rc_hbe     dlg_vbe    min_d_y_n  rc_per_ht  rc_x_a_s "
			"  dst_y_a_s  dst_y_pf   dst_y_vvb  dst_y_rvb  dst_y_vfl  dst_y_rfl  rf_pix_fq"
			"  vratio_pf  vrat_pf_c  rc_pg_vbl  rc_pg_vbc  rc_mc_vbl  rc_mc_vbc  rc_pg_fll"
			"  rc_pg_flc  rc_mc_fll  rc_mc_flc  pr_nom_l   pr_nom_c   rc_pg_nl   rc_pg_nc "
			"  mr_nom_l   mr_nom_c   rc_mc_nl   rc_mc_nc   rc_ld_pl   rc_ld_pc   rc_ld_l  "
			"  rc_ld_c    cha_cur0   ofst_cur1  cha_cur1   vr_af_vc0  ddrq_limt  x_rt_dlay"
			"  x_rp_dlay  x_rr_sfl\n");
	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(pool->hubps[i])->state);
		काष्ठा _vcs_dpi_display_dlg_regs_st *dlg_regs = &s->dlg_attr;

		अगर (!s->blank_en)
			DTN_INFO("[%2d]:  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh"
				"%  8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh"
				"  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh\n",
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
	पूर्ण

	DTN_INFO("========TTU========\n");
	DTN_INFO("HUBP:  qos_ll_wm  qos_lh_wm  mn_ttu_vb  qos_l_flp  rc_rd_p_l  rc_rd_l    rc_rd_p_c"
			"  rc_rd_c    rc_rd_c0   rc_rd_pc0  rc_rd_c1   rc_rd_pc1  qos_lf_l   qos_rds_l"
			"  qos_lf_c   qos_rds_c  qos_lf_c0  qos_rds_c0 qos_lf_c1  qos_rds_c1\n");
	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(pool->hubps[i])->state);
		काष्ठा _vcs_dpi_display_ttu_regs_st *ttu_regs = &s->ttu_attr;

		अगर (!s->blank_en)
			DTN_INFO("[%2d]:  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh  %8xh\n",
				pool->hubps[i]->inst, ttu_regs->qos_level_low_wm, ttu_regs->qos_level_high_wm, ttu_regs->min_ttu_vblank,
				ttu_regs->qos_level_flip, ttu_regs->refcyc_per_req_delivery_pre_l, ttu_regs->refcyc_per_req_delivery_l,
				ttu_regs->refcyc_per_req_delivery_pre_c, ttu_regs->refcyc_per_req_delivery_c, ttu_regs->refcyc_per_req_delivery_cur0,
				ttu_regs->refcyc_per_req_delivery_pre_cur0, ttu_regs->refcyc_per_req_delivery_cur1,
				ttu_regs->refcyc_per_req_delivery_pre_cur1, ttu_regs->qos_level_fixed_l, ttu_regs->qos_ramp_disable_l,
				ttu_regs->qos_level_fixed_c, ttu_regs->qos_ramp_disable_c, ttu_regs->qos_level_fixed_cur0,
				ttu_regs->qos_ramp_disable_cur0, ttu_regs->qos_level_fixed_cur1, ttu_regs->qos_ramp_disable_cur1);
	पूर्ण
	DTN_INFO("\n");
पूर्ण

व्योम dcn10_log_hw_state(काष्ठा dc *dc,
	काष्ठा dc_log_buffer_ctx *log_ctx)
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	DTN_INFO_BEGIN();

	dcn10_log_hubbub_state(dc, log_ctx);

	dcn10_log_hubp_states(dc, log_ctx);

	DTN_INFO("DPP:    IGAM format  IGAM mode    DGAM mode    RGAM mode"
			"  GAMUT mode  C11 C12   C13 C14   C21 C22   C23 C24   "
			"C31 C32   C33 C34\n");
	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा dpp *dpp = pool->dpps[i];
		काष्ठा dcn_dpp_state s = अणु0पूर्ण;

		dpp->funcs->dpp_पढ़ो_state(dpp, &s);

		अगर (!s.is_enabled)
			जारी;

		DTN_INFO("[%2d]:  %11xh  %-11s  %-11s  %-11s"
				"%8x    %08xh %08xh %08xh %08xh %08xh %08xh",
				dpp->inst,
				s.igam_input_क्रमmat,
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
				s.gamut_remap_mode,
				s.gamut_remap_c11_c12,
				s.gamut_remap_c13_c14,
				s.gamut_remap_c21_c22,
				s.gamut_remap_c23_c24,
				s.gamut_remap_c31_c32,
				s.gamut_remap_c33_c34);
		DTN_INFO("\n");
	पूर्ण
	DTN_INFO("\n");

	DTN_INFO("MPCC:  OPP  DPP  MPCCBOT  MODE  ALPHA_MODE  PREMULT  OVERLAP_ONLY  IDLE\n");
	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा mpcc_state s = अणु0पूर्ण;

		pool->mpc->funcs->पढ़ो_mpcc_state(pool->mpc, i, &s);
		अगर (s.opp_id != 0xf)
			DTN_INFO("[%2d]:  %2xh  %2xh  %6xh  %4d  %10d  %7d  %12d  %4d\n",
				i, s.opp_id, s.dpp_id, s.bot_mpcc_id,
				s.mode, s.alpha_mode, s.pre_multiplied_alpha, s.overlap_only,
				s.idle);
	पूर्ण
	DTN_INFO("\n");

	DTN_INFO("OTG:  v_bs  v_be  v_ss  v_se  vpol  vmax  vmin  vmax_sel  vmin_sel  h_bs  h_be  h_ss  h_se  hpol  htot  vtot  underflow blank_en\n");

	क्रम (i = 0; i < pool->timing_generator_count; i++) अणु
		काष्ठा timing_generator *tg = pool->timing_generators[i];
		काष्ठा dcn_otg_state s = अणु0पूर्ण;
		/* Read shared OTG state रेजिस्टरs क्रम all DCNx */
		optc1_पढ़ो_otg_state(DCN10TG_FROM_TG(tg), &s);

		/*
		 * For DCN2 and greater, a रेजिस्टर on the OPP is used to
		 * determine अगर the CRTC is blanked instead of the OTG. So use
		 * dpg_is_blanked() अगर exists, otherwise fallback on otg.
		 *
		 * TODO: Implement DCN-specअगरic पढ़ो_otg_state hooks.
		 */
		अगर (pool->opps[i]->funcs->dpg_is_blanked)
			s.blank_enabled = pool->opps[i]->funcs->dpg_is_blanked(pool->opps[i]);
		अन्यथा
			s.blank_enabled = tg->funcs->is_blanked(tg);

		//only prपूर्णांक अगर OTG master is enabled
		अगर ((s.otg_enabled & 1) == 0)
			जारी;

		DTN_INFO("[%d]: %5d %5d %5d %5d %5d %5d %5d %9d %9d %5d %5d %5d %5d %5d %5d %5d  %9d %8d\n",
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
				s.blank_enabled);

		// Clear underflow क्रम debug purposes
		// We want to keep underflow sticky bit on क्रम the दीर्घevity tests outside of test environment.
		// This function is called only from Winकरोws or Diags test environment, hence it's safe to clear
		// it from here without affecting the original पूर्णांकent.
		tg->funcs->clear_optc_underflow(tg);
	पूर्ण
	DTN_INFO("\n");

	// dcn_dsc_state काष्ठा field bytes_per_pixel was नामd to bits_per_pixel
	// TODO: Update golden log header to reflect this name change
	DTN_INFO("DSC: CLOCK_EN  SLICE_WIDTH  Bytes_pp\n");
	क्रम (i = 0; i < pool->res_cap->num_dsc; i++) अणु
		काष्ठा display_stream_compressor *dsc = pool->dscs[i];
		काष्ठा dcn_dsc_state s = अणु0पूर्ण;

		dsc->funcs->dsc_पढ़ो_state(dsc, &s);
		DTN_INFO("[%d]: %-9d %-12d %-10d\n",
		dsc->inst,
			s.dsc_घड़ी_en,
			s.dsc_slice_width,
			s.dsc_bits_per_pixel);
		DTN_INFO("\n");
	पूर्ण
	DTN_INFO("\n");

	DTN_INFO("S_ENC: DSC_MODE  SEC_GSP7_LINE_NUM"
			"  VBID6_LINE_REFERENCE  VBID6_LINE_NUM  SEC_GSP7_ENABLE  SEC_STREAM_ENABLE\n");
	क्रम (i = 0; i < pool->stream_enc_count; i++) अणु
		काष्ठा stream_encoder *enc = pool->stream_enc[i];
		काष्ठा enc_state s = अणु0पूर्ण;

		अगर (enc->funcs->enc_पढ़ो_state) अणु
			enc->funcs->enc_पढ़ो_state(enc, &s);
			DTN_INFO("[%-3d]: %-9d %-18d %-21d %-15d %-16d %-17d\n",
				enc->id,
				s.dsc_mode,
				s.sec_gsp_pps_line_num,
				s.vbid6_line_reference,
				s.vbid6_line_num,
				s.sec_gsp_pps_enable,
				s.sec_stream_enable);
			DTN_INFO("\n");
		पूर्ण
	पूर्ण
	DTN_INFO("\n");

	DTN_INFO("L_ENC: DPHY_FEC_EN  DPHY_FEC_READY_SHADOW  DPHY_FEC_ACTIVE_STATUS  DP_LINK_TRAINING_COMPLETE\n");
	क्रम (i = 0; i < dc->link_count; i++) अणु
		काष्ठा link_encoder *lenc = dc->links[i]->link_enc;

		काष्ठा link_enc_state s = अणु0पूर्ण;

		अगर (lenc->funcs->पढ़ो_state) अणु
			lenc->funcs->पढ़ो_state(lenc, &s);
			DTN_INFO("[%-3d]: %-12d %-22d %-22d %-25d\n",
				i,
				s.dphy_fec_en,
				s.dphy_fec_पढ़ोy_shaकरोw,
				s.dphy_fec_active_status,
				s.dp_link_training_complete);
			DTN_INFO("\n");
		पूर्ण
	पूर्ण
	DTN_INFO("\n");

	DTN_INFO("\nCALCULATED Clocks: dcfclk_khz:%d  dcfclk_deep_sleep_khz:%d  dispclk_khz:%d\n"
		"dppclk_khz:%d  max_supported_dppclk_khz:%d  fclk_khz:%d  socclk_khz:%d\n\n",
			dc->current_state->bw_ctx.bw.dcn.clk.dcfclk_khz,
			dc->current_state->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz,
			dc->current_state->bw_ctx.bw.dcn.clk.dispclk_khz,
			dc->current_state->bw_ctx.bw.dcn.clk.dppclk_khz,
			dc->current_state->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz,
			dc->current_state->bw_ctx.bw.dcn.clk.fclk_khz,
			dc->current_state->bw_ctx.bw.dcn.clk.socclk_khz);

	log_mpc_crc(dc, log_ctx);

	DTN_INFO_END();
पूर्ण

bool dcn10_did_underflow_occur(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;

	अगर (tg->funcs->is_optc_underflow_occurred(tg)) अणु
		tg->funcs->clear_optc_underflow(tg);
		वापस true;
	पूर्ण

	अगर (hubp->funcs->hubp_get_underflow_status(hubp)) अणु
		hubp->funcs->hubp_clear_underflow(hubp);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम dcn10_enable_घातer_gating_plane(
	काष्ठा dce_hwseq *hws,
	bool enable)
अणु
	bool क्रमce_on = true; /* disable घातer gating */

	अगर (enable)
		क्रमce_on = false;

	/* DCHUBP0/1/2/3 */
	REG_UPDATE(DOMAIN0_PG_CONFIG, DOMAIN0_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN2_PG_CONFIG, DOMAIN2_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN4_PG_CONFIG, DOMAIN4_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN6_PG_CONFIG, DOMAIN6_POWER_FORCEON, क्रमce_on);

	/* DPP0/1/2/3 */
	REG_UPDATE(DOMAIN1_PG_CONFIG, DOMAIN1_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN3_PG_CONFIG, DOMAIN3_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN5_PG_CONFIG, DOMAIN5_POWER_FORCEON, क्रमce_on);
	REG_UPDATE(DOMAIN7_PG_CONFIG, DOMAIN7_POWER_FORCEON, क्रमce_on);
पूर्ण

व्योम dcn10_disable_vga(
	काष्ठा dce_hwseq *hws)
अणु
	अचिन्हित पूर्णांक in_vga1_mode = 0;
	अचिन्हित पूर्णांक in_vga2_mode = 0;
	अचिन्हित पूर्णांक in_vga3_mode = 0;
	अचिन्हित पूर्णांक in_vga4_mode = 0;

	REG_GET(D1VGA_CONTROL, D1VGA_MODE_ENABLE, &in_vga1_mode);
	REG_GET(D2VGA_CONTROL, D2VGA_MODE_ENABLE, &in_vga2_mode);
	REG_GET(D3VGA_CONTROL, D3VGA_MODE_ENABLE, &in_vga3_mode);
	REG_GET(D4VGA_CONTROL, D4VGA_MODE_ENABLE, &in_vga4_mode);

	अगर (in_vga1_mode == 0 && in_vga2_mode == 0 &&
			in_vga3_mode == 0 && in_vga4_mode == 0)
		वापस;

	REG_WRITE(D1VGA_CONTROL, 0);
	REG_WRITE(D2VGA_CONTROL, 0);
	REG_WRITE(D3VGA_CONTROL, 0);
	REG_WRITE(D4VGA_CONTROL, 0);

	/* HW Engineer's Notes:
	 *  During चयन from vga->extended, अगर we set the VGA_TEST_ENABLE and
	 *  then hit the VGA_TEST_RENDER_START, then the DCHUBP timing माला_लो updated correctly.
	 *
	 *  Then vBIOS will have it poll क्रम the VGA_TEST_RENDER_DONE and unset
	 *  VGA_TEST_ENABLE, to leave it in the same state as beक्रमe.
	 */
	REG_UPDATE(VGA_TEST_CONTROL, VGA_TEST_ENABLE, 1);
	REG_UPDATE(VGA_TEST_CONTROL, VGA_TEST_RENDER_START, 1);
पूर्ण

व्योम dcn10_dpp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक dpp_inst,
		bool घातer_on)
अणु
	uपूर्णांक32_t घातer_gate = घातer_on ? 0 : 1;
	uपूर्णांक32_t pwr_status = घातer_on ? 0 : 2;

	अगर (hws->ctx->dc->debug.disable_dpp_घातer_gate)
		वापस;
	अगर (REG(DOMAIN1_PG_CONFIG) == 0)
		वापस;

	चयन (dpp_inst) अणु
	हाल 0: /* DPP0 */
		REG_UPDATE(DOMAIN1_PG_CONFIG,
				DOMAIN1_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN1_PG_STATUS,
				DOMAIN1_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 1: /* DPP1 */
		REG_UPDATE(DOMAIN3_PG_CONFIG,
				DOMAIN3_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN3_PG_STATUS,
				DOMAIN3_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 2: /* DPP2 */
		REG_UPDATE(DOMAIN5_PG_CONFIG,
				DOMAIN5_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN5_PG_STATUS,
				DOMAIN5_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 3: /* DPP3 */
		REG_UPDATE(DOMAIN7_PG_CONFIG,
				DOMAIN7_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN7_PG_STATUS,
				DOMAIN7_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण
पूर्ण

व्योम dcn10_hubp_pg_control(
		काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक hubp_inst,
		bool घातer_on)
अणु
	uपूर्णांक32_t घातer_gate = घातer_on ? 0 : 1;
	uपूर्णांक32_t pwr_status = घातer_on ? 0 : 2;

	अगर (hws->ctx->dc->debug.disable_hubp_घातer_gate)
		वापस;
	अगर (REG(DOMAIN0_PG_CONFIG) == 0)
		वापस;

	चयन (hubp_inst) अणु
	हाल 0: /* DCHUBP0 */
		REG_UPDATE(DOMAIN0_PG_CONFIG,
				DOMAIN0_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN0_PG_STATUS,
				DOMAIN0_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 1: /* DCHUBP1 */
		REG_UPDATE(DOMAIN2_PG_CONFIG,
				DOMAIN2_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN2_PG_STATUS,
				DOMAIN2_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 2: /* DCHUBP2 */
		REG_UPDATE(DOMAIN4_PG_CONFIG,
				DOMAIN4_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN4_PG_STATUS,
				DOMAIN4_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	हाल 3: /* DCHUBP3 */
		REG_UPDATE(DOMAIN6_PG_CONFIG,
				DOMAIN6_POWER_GATE, घातer_gate);

		REG_WAIT(DOMAIN6_PG_STATUS,
				DOMAIN6_PGFSM_PWR_STATUS, pwr_status,
				1, 1000);
		अवरोध;
	शेष:
		BREAK_TO_DEBUGGER();
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम घातer_on_plane(
	काष्ठा dce_hwseq *hws,
	पूर्णांक plane_id)
अणु
	DC_LOGGER_INIT(hws->ctx->logger);
	अगर (REG(DC_IP_REQUEST_CNTL)) अणु
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 1);

		अगर (hws->funcs.dpp_pg_control)
			hws->funcs.dpp_pg_control(hws, plane_id, true);

		अगर (hws->funcs.hubp_pg_control)
			hws->funcs.hubp_pg_control(hws, plane_id, true);

		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 0);
		DC_LOG_DEBUG(
				"Un-gated front end for pipe %d\n", plane_id);
	पूर्ण
पूर्ण

अटल व्योम unकरो_DEGVIDCN10_253_wa(काष्ठा dc *dc)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = dc->res_pool->hubps[0];

	अगर (!hws->wa_state.DEGVIDCN10_253_applied)
		वापस;

	hubp->funcs->set_blank(hubp, true);

	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 1);

	hws->funcs.hubp_pg_control(hws, 0, false);
	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 0);

	hws->wa_state.DEGVIDCN10_253_applied = false;
पूर्ण

अटल व्योम apply_DEGVIDCN10_253_wa(काष्ठा dc *dc)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = dc->res_pool->hubps[0];
	पूर्णांक i;

	अगर (dc->debug.disable_stutter)
		वापस;

	अगर (!hws->wa.DEGVIDCN10_253)
		वापस;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (!dc->res_pool->hubps[i]->घातer_gated)
			वापस;
	पूर्ण

	/* all pipe घातer gated, apply work around to enable stutter. */

	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 1);

	hws->funcs.hubp_pg_control(hws, 0, true);
	REG_SET(DC_IP_REQUEST_CNTL, 0,
			IP_REQUEST_EN, 0);

	hubp->funcs->set_hubp_blank_en(hubp, false);
	hws->wa_state.DEGVIDCN10_253_applied = true;
पूर्ण

व्योम dcn10_bios_golden_init(काष्ठा dc *dc)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा dc_bios *bp = dc->ctx->dc_bios;
	पूर्णांक i;
	bool allow_self_fresh_क्रमce_enable = true;

	अगर (hws->funcs.s0i3_golden_init_wa && hws->funcs.s0i3_golden_init_wa(dc))
		वापस;

	अगर (dc->res_pool->hubbub->funcs->is_allow_self_refresh_enabled)
		allow_self_fresh_क्रमce_enable =
				dc->res_pool->hubbub->funcs->is_allow_self_refresh_enabled(dc->res_pool->hubbub);


	/* WA क्रम making DF sleep when idle after resume from S0i3.
	 * DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE is set to 1 by
	 * command table, अगर DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE = 0
	 * beक्रमe calling command table and it changed to 1 after,
	 * it should be set back to 0.
	 */

	/* initialize dcn global */
	bp->funcs->enable_disp_घातer_gating(bp,
			CONTROLLER_ID_D0, ASIC_PIPE_INIT);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		/* initialize dcn per pipe */
		bp->funcs->enable_disp_घातer_gating(bp,
				CONTROLLER_ID_D0 + i, ASIC_PIPE_DISABLE);
	पूर्ण

	अगर (dc->res_pool->hubbub->funcs->allow_self_refresh_control)
		अगर (allow_self_fresh_क्रमce_enable == false &&
				dc->res_pool->hubbub->funcs->is_allow_self_refresh_enabled(dc->res_pool->hubbub))
			dc->res_pool->hubbub->funcs->allow_self_refresh_control(dc->res_pool->hubbub,
										!dc->res_pool->hubbub->ctx->dc->debug.disable_stutter);

पूर्ण

अटल व्योम false_optc_underflow_wa(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा timing_generator *tg)
अणु
	पूर्णांक i;
	bool underflow;

	अगर (!dc->hwseq->wa.false_optc_underflow)
		वापस;

	underflow = tg->funcs->is_optc_underflow_occurred(tg);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *old_pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];

		अगर (old_pipe_ctx->stream != stream)
			जारी;

		dc->hwss.रुको_क्रम_mpcc_disconnect(dc, dc->res_pool, old_pipe_ctx);
	पूर्ण

	अगर (tg->funcs->set_blank_data_द्विगुन_buffer)
		tg->funcs->set_blank_data_द्विगुन_buffer(tg, true);

	अगर (tg->funcs->is_optc_underflow_occurred(tg) && !underflow)
		tg->funcs->clear_optc_underflow(tg);
पूर्ण

क्रमागत dc_status dcn10_enable_stream_timing(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context,
		काष्ठा dc *dc)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	क्रमागत dc_color_space color_space;
	काष्ठा tg_color black_color = अणु0पूर्ण;

	/* by upper caller loop, pipe0 is parent pipe and be called first.
	 * back end is set up by क्रम pipe0. Other children pipe share back end
	 * with pipe 0. No program is needed.
	 */
	अगर (pipe_ctx->top_pipe != शून्य)
		वापस DC_OK;

	/* TODO check अगर timing_changed, disable stream अगर timing changed */

	/* HW program guide assume display alपढ़ोy disable
	 * by unplug sequence. OTG assume stop.
	 */
	pipe_ctx->stream_res.tg->funcs->enable_optc_घड़ी(pipe_ctx->stream_res.tg, true);

	अगर (false == pipe_ctx->घड़ी_source->funcs->program_pix_clk(
			pipe_ctx->घड़ी_source,
			&pipe_ctx->stream_res.pix_clk_params,
			&pipe_ctx->pll_settings)) अणु
		BREAK_TO_DEBUGGER();
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	pipe_ctx->stream_res.tg->funcs->program_timing(
			pipe_ctx->stream_res.tg,
			&stream->timing,
			pipe_ctx->pipe_dlg_param.vपढ़ोy_offset,
			pipe_ctx->pipe_dlg_param.vstartup_start,
			pipe_ctx->pipe_dlg_param.vupdate_offset,
			pipe_ctx->pipe_dlg_param.vupdate_width,
			pipe_ctx->stream->संकेत,
			true);

#अगर 0 /* move to after enable_crtc */
	/* TODO: OPP FMT, ABM. etc. should be करोne here. */
	/* or FPGA now. instance 0 only. TODO: move to opp.c */

	inst_offset = reg_offsets[pipe_ctx->stream_res.tg->inst].fmt;

	pipe_ctx->stream_res.opp->funcs->opp_program_fmt(
				pipe_ctx->stream_res.opp,
				&stream->bit_depth_params,
				&stream->clamping);
#पूर्ण_अगर
	/* program otg blank color */
	color_space = stream->output_color_space;
	color_space_to_black_color(dc, color_space, &black_color);

	/*
	 * The way 420 is packed, 2 channels carry Y component, 1 channel
	 * alternate between Cb and Cr, so both channels need the pixel
	 * value क्रम Y
	 */
	अगर (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
		black_color.color_r_cr = black_color.color_g_y;

	अगर (pipe_ctx->stream_res.tg->funcs->set_blank_color)
		pipe_ctx->stream_res.tg->funcs->set_blank_color(
				pipe_ctx->stream_res.tg,
				&black_color);

	अगर (pipe_ctx->stream_res.tg->funcs->is_blanked &&
			!pipe_ctx->stream_res.tg->funcs->is_blanked(pipe_ctx->stream_res.tg)) अणु
		pipe_ctx->stream_res.tg->funcs->set_blank(pipe_ctx->stream_res.tg, true);
		hwss_रुको_क्रम_blank_complete(pipe_ctx->stream_res.tg);
		false_optc_underflow_wa(dc, pipe_ctx->stream, pipe_ctx->stream_res.tg);
	पूर्ण

	/* VTG is  within DCHUB command block. DCFCLK is always on */
	अगर (false == pipe_ctx->stream_res.tg->funcs->enable_crtc(pipe_ctx->stream_res.tg)) अणु
		BREAK_TO_DEBUGGER();
		वापस DC_ERROR_UNEXPECTED;
	पूर्ण

	/* TODO program crtc source select क्रम non-भव संकेत*/
	/* TODO program FMT */
	/* TODO setup link_enc */
	/* TODO set stream attributes */
	/* TODO program audio */
	/* TODO enable stream अगर timing changed */
	/* TODO unblank stream अगर DP */

	वापस DC_OK;
पूर्ण

अटल व्योम dcn10_reset_back_end_क्रम_pipe(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dc_link *link;
	DC_LOGGER_INIT(dc->ctx->logger);
	अगर (pipe_ctx->stream_res.stream_enc == शून्य) अणु
		pipe_ctx->stream = शून्य;
		वापस;
	पूर्ण

	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		link = pipe_ctx->stream->link;
		/* DPMS may alपढ़ोy disable or */
		/* dpms_off status is incorrect due to fastboot
		 * feature. When प्रणाली resume from S4 with second
		 * screen only, the dpms_off would be true but
		 * VBIOS lit up eDP, so check link status too.
		 */
		अगर (!pipe_ctx->stream->dpms_off || link->link_status.link_active)
			core_link_disable_stream(pipe_ctx);
		अन्यथा अगर (pipe_ctx->stream_res.audio)
			dc->hwss.disable_audio_stream(pipe_ctx);

		अगर (pipe_ctx->stream_res.audio) अणु
			/*disable az_endpoपूर्णांक*/
			pipe_ctx->stream_res.audio->funcs->az_disable(pipe_ctx->stream_res.audio);

			/*मुक्त audio*/
			अगर (dc->caps.dynamic_audio == true) अणु
				/*we have to dynamic arbitrate the audio endpoपूर्णांकs*/
				/*we मुक्त the resource, need reset is_audio_acquired*/
				update_audio_usage(&dc->current_state->res_ctx, dc->res_pool,
						pipe_ctx->stream_res.audio, false);
				pipe_ctx->stream_res.audio = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	/* by upper caller loop, parent pipe: pipe0, will be reset last.
	 * back end share by all pipes and will be disable only when disable
	 * parent pipe.
	 */
	अगर (pipe_ctx->top_pipe == शून्य) अणु

		अगर (pipe_ctx->stream_res.abm)
			dc->hwss.set_abm_immediate_disable(pipe_ctx);

		pipe_ctx->stream_res.tg->funcs->disable_crtc(pipe_ctx->stream_res.tg);

		pipe_ctx->stream_res.tg->funcs->enable_optc_घड़ी(pipe_ctx->stream_res.tg, false);
		अगर (pipe_ctx->stream_res.tg->funcs->set_drr)
			pipe_ctx->stream_res.tg->funcs->set_drr(
					pipe_ctx->stream_res.tg, शून्य);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (&dc->current_state->res_ctx.pipe_ctx[i] == pipe_ctx)
			अवरोध;

	अगर (i == dc->res_pool->pipe_count)
		वापस;

	pipe_ctx->stream = शून्य;
	DC_LOG_DEBUG("Reset back end for pipe %d, tg:%d\n",
					pipe_ctx->pipe_idx, pipe_ctx->stream_res.tg->inst);
पूर्ण

अटल bool dcn10_hw_wa_क्रमce_recovery(काष्ठा dc *dc)
अणु
	काष्ठा hubp *hubp ;
	अचिन्हित पूर्णांक i;
	bool need_recover = true;

	अगर (!dc->debug.recovery_enabled)
		वापस false;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe_ctx != शून्य) अणु
			hubp = pipe_ctx->plane_res.hubp;
			अगर (hubp != शून्य && hubp->funcs->hubp_get_underflow_status) अणु
				अगर (hubp->funcs->hubp_get_underflow_status(hubp) != 0) अणु
					/* one pipe underflow, we will reset all the pipes*/
					need_recover = true;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!need_recover)
		वापस false;
	/*
	DCHUBP_CNTL:HUBP_BLANK_EN=1
	DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=1
	DCHUBP_CNTL:HUBP_DISABLE=1
	DCHUBP_CNTL:HUBP_DISABLE=0
	DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=0
	DCSURF_PRIMARY_SURFACE_ADDRESS
	DCHUBP_CNTL:HUBP_BLANK_EN=0
	*/

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe_ctx != शून्य) अणु
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_BLANK_EN=1*/
			अगर (hubp != शून्य && hubp->funcs->set_hubp_blank_en)
				hubp->funcs->set_hubp_blank_en(hubp, true);
		पूर्ण
	पूर्ण
	/*DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=1*/
	hubbub1_soft_reset(dc->res_pool->hubbub, true);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe_ctx != शून्य) अणु
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_DISABLE=1*/
			अगर (hubp != शून्य && hubp->funcs->hubp_disable_control)
				hubp->funcs->hubp_disable_control(hubp, true);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe_ctx != शून्य) अणु
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_DISABLE=0*/
			अगर (hubp != शून्य && hubp->funcs->hubp_disable_control)
				hubp->funcs->hubp_disable_control(hubp, true);
		पूर्ण
	पूर्ण
	/*DCHUBBUB_SOFT_RESET:DCHUBBUB_GLOBAL_SOFT_RESET=0*/
	hubbub1_soft_reset(dc->res_pool->hubbub, false);
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx =
			&dc->current_state->res_ctx.pipe_ctx[i];
		अगर (pipe_ctx != शून्य) अणु
			hubp = pipe_ctx->plane_res.hubp;
			/*DCHUBP_CNTL:HUBP_BLANK_EN=0*/
			अगर (hubp != शून्य && hubp->funcs->set_hubp_blank_en)
				hubp->funcs->set_hubp_blank_en(hubp, true);
		पूर्ण
	पूर्ण
	वापस true;

पूर्ण

व्योम dcn10_verअगरy_allow_pstate_change_high(काष्ठा dc *dc)
अणु
	अटल bool should_log_hw_state; /* prevent hw state log by शेष */

	अगर (!hubbub1_verअगरy_allow_pstate_change_high(dc->res_pool->hubbub)) अणु
		पूर्णांक i = 0;

		अगर (should_log_hw_state)
			dcn10_log_hw_state(dc, शून्य);

		TRACE_DC_PIPE_STATE(pipe_ctx, i, MAX_PIPES);
		BREAK_TO_DEBUGGER();
		अगर (dcn10_hw_wa_क्रमce_recovery(dc)) अणु
		/*check again*/
			अगर (!hubbub1_verअगरy_allow_pstate_change_high(dc->res_pool->hubbub))
				BREAK_TO_DEBUGGER();
		पूर्ण
	पूर्ण
पूर्ण

/* trigger HW to start disconnect plane from stream on the next vsync */
व्योम dcn10_plane_atomic_disconnect(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	पूर्णांक dpp_id = pipe_ctx->plane_res.dpp->inst;
	काष्ठा mpc *mpc = dc->res_pool->mpc;
	काष्ठा mpc_tree *mpc_tree_params;
	काष्ठा mpcc *mpcc_to_हटाओ = शून्य;
	काष्ठा output_pixel_processor *opp = pipe_ctx->stream_res.opp;

	mpc_tree_params = &(opp->mpc_tree_params);
	mpcc_to_हटाओ = mpc->funcs->get_mpcc_क्रम_dpp(mpc_tree_params, dpp_id);

	/*Alपढ़ोy reset*/
	अगर (mpcc_to_हटाओ == शून्य)
		वापस;

	mpc->funcs->हटाओ_mpcc(mpc, mpc_tree_params, mpcc_to_हटाओ);
	अगर (opp != शून्य)
		opp->mpcc_disconnect_pending[pipe_ctx->plane_res.mpcc_inst] = true;

	dc->optimized_required = true;

	अगर (hubp->funcs->hubp_disconnect)
		hubp->funcs->hubp_disconnect(hubp);

	अगर (dc->debug.sanity_checks)
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
पूर्ण

व्योम dcn10_plane_atomic_घातer_करोwn(काष्ठा dc *dc,
		काष्ठा dpp *dpp,
		काष्ठा hubp *hubp)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (REG(DC_IP_REQUEST_CNTL)) अणु
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 1);

		अगर (hws->funcs.dpp_pg_control)
			hws->funcs.dpp_pg_control(hws, dpp->inst, false);

		अगर (hws->funcs.hubp_pg_control)
			hws->funcs.hubp_pg_control(hws, hubp->inst, false);

		dpp->funcs->dpp_reset(dpp);
		REG_SET(DC_IP_REQUEST_CNTL, 0,
				IP_REQUEST_EN, 0);
		DC_LOG_DEBUG(
				"Power gated front end %d\n", hubp->inst);
	पूर्ण
पूर्ण

/* disable HW used by plane.
 * note:  cannot disable until disconnect is complete
 */
व्योम dcn10_plane_atomic_disable(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा dpp *dpp = pipe_ctx->plane_res.dpp;
	पूर्णांक opp_id = hubp->opp_id;

	dc->hwss.रुको_क्रम_mpcc_disconnect(dc, dc->res_pool, pipe_ctx);

	hubp->funcs->hubp_clk_cntl(hubp, false);

	dpp->funcs->dpp_dppclk_control(dpp, false, false);

	अगर (opp_id != 0xf && pipe_ctx->stream_res.opp->mpc_tree_params.opp_list == शून्य)
		pipe_ctx->stream_res.opp->funcs->opp_pipe_घड़ी_control(
				pipe_ctx->stream_res.opp,
				false);

	hubp->घातer_gated = true;
	dc->optimized_required = false; /* We're घातering off, no need to optimize */

	hws->funcs.plane_atomic_घातer_करोwn(dc,
			pipe_ctx->plane_res.dpp,
			pipe_ctx->plane_res.hubp);

	pipe_ctx->stream = शून्य;
	स_रखो(&pipe_ctx->stream_res, 0, माप(pipe_ctx->stream_res));
	स_रखो(&pipe_ctx->plane_res, 0, माप(pipe_ctx->plane_res));
	pipe_ctx->top_pipe = शून्य;
	pipe_ctx->bottom_pipe = शून्य;
	pipe_ctx->plane_state = शून्य;
पूर्ण

व्योम dcn10_disable_plane(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (!pipe_ctx->plane_res.hubp || pipe_ctx->plane_res.hubp->घातer_gated)
		वापस;

	hws->funcs.plane_atomic_disable(dc, pipe_ctx);

	apply_DEGVIDCN10_253_wa(dc);

	DC_LOG_DC("Power down front end %d\n",
					pipe_ctx->pipe_idx);
पूर्ण

व्योम dcn10_init_pipes(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	bool can_apply_seamless_boot = false;

	क्रम (i = 0; i < context->stream_count; i++) अणु
		अगर (context->streams[i]->apply_seamless_boot_optimization) अणु
			can_apply_seamless_boot = true;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		/* There is assumption that pipe_ctx is not mapping irregularly
		 * to non-preferred front end. If pipe_ctx->stream is not शून्य,
		 * we will use the pipe, so करोn't disable
		 */
		अगर (pipe_ctx->stream != शून्य && can_apply_seamless_boot)
			जारी;

		/* Blank controller using driver code instead of
		 * command table.
		 */
		अगर (tg->funcs->is_tg_enabled(tg)) अणु
			अगर (hws->funcs.init_blank != शून्य) अणु
				hws->funcs.init_blank(dc, tg);
				tg->funcs->lock(tg);
			पूर्ण अन्यथा अणु
				tg->funcs->lock(tg);
				tg->funcs->set_blank(tg, true);
				hwss_रुको_क्रम_blank_complete(tg);
			पूर्ण
		पूर्ण
	पूर्ण

	/* num_opp will be equal to number of mpcc */
	क्रम (i = 0; i < dc->res_pool->res_cap->num_opp; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		/* Cannot reset the MPC mux अगर seamless boot */
		अगर (pipe_ctx->stream != शून्य && can_apply_seamless_boot)
			जारी;

		dc->res_pool->mpc->funcs->mpc_init_single_inst(
				dc->res_pool->mpc, i);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[i];
		काष्ठा hubp *hubp = dc->res_pool->hubps[i];
		काष्ठा dpp *dpp = dc->res_pool->dpps[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		/* There is assumption that pipe_ctx is not mapping irregularly
		 * to non-preferred front end. If pipe_ctx->stream is not शून्य,
		 * we will use the pipe, so करोn't disable
		 */
		अगर (can_apply_seamless_boot &&
			pipe_ctx->stream != शून्य &&
			pipe_ctx->stream_res.tg->funcs->is_tg_enabled(
				pipe_ctx->stream_res.tg)) अणु
			// Enable द्विगुन buffering क्रम OTG_BLANK no matter अगर
			// seamless boot is enabled or not to suppress global sync
			// संकेतs when OTG blanked. This is to prevent pipe from
			// requesting data जबतक in PSR.
			tg->funcs->tg_init(tg);
			hubp->घातer_gated = true;
			जारी;
		पूर्ण

		/* Disable on the current state so the new one isn't cleared. */
		pipe_ctx = &dc->current_state->res_ctx.pipe_ctx[i];

		dpp->funcs->dpp_reset(dpp);

		pipe_ctx->stream_res.tg = tg;
		pipe_ctx->pipe_idx = i;

		pipe_ctx->plane_res.hubp = hubp;
		pipe_ctx->plane_res.dpp = dpp;
		pipe_ctx->plane_res.mpcc_inst = dpp->inst;
		hubp->mpcc_id = dpp->inst;
		hubp->opp_id = OPP_ID_INVALID;
		hubp->घातer_gated = false;

		dc->res_pool->opps[i]->mpc_tree_params.opp_id = dc->res_pool->opps[i]->inst;
		dc->res_pool->opps[i]->mpc_tree_params.opp_list = शून्य;
		dc->res_pool->opps[i]->mpcc_disconnect_pending[pipe_ctx->plane_res.mpcc_inst] = true;
		pipe_ctx->stream_res.opp = dc->res_pool->opps[i];

		hws->funcs.plane_atomic_disconnect(dc, pipe_ctx);

		अगर (tg->funcs->is_tg_enabled(tg))
			tg->funcs->unlock(tg);

		dc->hwss.disable_plane(dc, pipe_ctx);

		pipe_ctx->stream_res.tg = शून्य;
		pipe_ctx->plane_res.hubp = शून्य;

		tg->funcs->tg_init(tg);
	पूर्ण
पूर्ण

व्योम dcn10_init_hw(काष्ठा dc *dc)
अणु
	पूर्णांक i, j;
	काष्ठा abm *abm = dc->res_pool->abm;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा dc_bios *dcb = dc->ctx->dc_bios;
	काष्ठा resource_pool *res_pool = dc->res_pool;
	uपूर्णांक32_t backlight = MAX_BACKLIGHT_LEVEL;
	bool   is_optimized_init_करोne = false;

	अगर (dc->clk_mgr && dc->clk_mgr->funcs->init_घड़ीs)
		dc->clk_mgr->funcs->init_घड़ीs(dc->clk_mgr);

	// Initialize the dccg
	अगर (dc->res_pool->dccg && dc->res_pool->dccg->funcs->dccg_init)
		dc->res_pool->dccg->funcs->dccg_init(res_pool->dccg);

	अगर (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु

		REG_WRITE(REFCLK_CNTL, 0);
		REG_UPDATE(DCHUBBUB_GLOBAL_TIMER_CNTL, DCHUBBUB_GLOBAL_TIMER_ENABLE, 1);
		REG_WRITE(DIO_MEM_PWR_CTRL, 0);

		अगर (!dc->debug.disable_घड़ी_gate) अणु
			/* enable all DCN घड़ी gating */
			REG_WRITE(DCCG_GATE_DISABLE_CNTL, 0);

			REG_WRITE(DCCG_GATE_DISABLE_CNTL2, 0);

			REG_UPDATE(DCFCLK_CNTL, DCFCLK_GATE_DIS, 0);
		पूर्ण

		//Enable ability to घातer gate / करोn't क्रमce घातer on permanently
		अगर (hws->funcs.enable_घातer_gating_plane)
			hws->funcs.enable_घातer_gating_plane(hws, true);

		वापस;
	पूर्ण

	अगर (!dcb->funcs->is_accelerated_mode(dcb))
		hws->funcs.disable_vga(dc->hwseq);

	hws->funcs.bios_golden_init(dc);

	अगर (dc->ctx->dc_bios->fw_info_valid) अणु
		res_pool->ref_घड़ीs.xtalin_घड़ी_inKhz =
				dc->ctx->dc_bios->fw_info.pll_info.crystal_frequency;

		अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
			अगर (res_pool->dccg && res_pool->hubbub) अणु

				(res_pool->dccg->funcs->get_dccg_ref_freq)(res_pool->dccg,
						dc->ctx->dc_bios->fw_info.pll_info.crystal_frequency,
						&res_pool->ref_घड़ीs.dccg_ref_घड़ी_inKhz);

				(res_pool->hubbub->funcs->get_dchub_ref_freq)(res_pool->hubbub,
						res_pool->ref_घड़ीs.dccg_ref_घड़ी_inKhz,
						&res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz);
			पूर्ण अन्यथा अणु
				// Not all ASICs have DCCG sw component
				res_pool->ref_घड़ीs.dccg_ref_घड़ी_inKhz =
						res_pool->ref_घड़ीs.xtalin_घड़ी_inKhz;
				res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz =
						res_pool->ref_घड़ीs.xtalin_घड़ी_inKhz;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		ASSERT_CRITICAL(false);

	क्रम (i = 0; i < dc->link_count; i++) अणु
		/* Power up AND update implementation according to the
		 * required संकेत (which may be dअगरferent from the
		 * शेष संकेत on connector).
		 */
		काष्ठा dc_link *link = dc->links[i];

		अगर (!is_optimized_init_करोne)
			link->link_enc->funcs->hw_init(link->link_enc);

		/* Check क्रम enabled DIG to identअगरy enabled display */
		अगर (link->link_enc->funcs->is_dig_enabled &&
			link->link_enc->funcs->is_dig_enabled(link->link_enc))
			link->link_status.link_active = true;
	पूर्ण

	/* Power gate DSCs */
	अगर (!is_optimized_init_करोne) अणु
		क्रम (i = 0; i < res_pool->res_cap->num_dsc; i++)
			अगर (hws->funcs.dsc_pg_control != शून्य)
				hws->funcs.dsc_pg_control(hws, res_pool->dscs[i]->inst, false);
	पूर्ण

	/* Enable outbox notअगरication feature of dmub */
	अगर (dc->debug.enable_dmub_aux_क्रम_legacy_ddc)
		dmub_enable_outbox_notअगरication(dc);

	/* we want to turn off all dp displays beक्रमe करोing detection */
	अगर (dc->config.घातer_करोwn_display_on_boot) अणु
		uपूर्णांक8_t dpcd_घातer_state = '\0';
		क्रमागत dc_status status = DC_ERROR_UNEXPECTED;

		क्रम (i = 0; i < dc->link_count; i++) अणु
			अगर (dc->links[i]->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT)
				जारी;

			/*
			 * If any of the displays are lit up turn them off.
			 * The reason is that some MST hubs cannot be turned off
			 * completely until we tell them to करो so.
			 * If not turned off, then displays connected to MST hub
			 * won't light up.
			 */
			status = core_link_पढ़ो_dpcd(dc->links[i], DP_SET_POWER,
							&dpcd_घातer_state, माप(dpcd_घातer_state));
			अगर (status == DC_OK && dpcd_घातer_state == DP_POWER_STATE_D0) अणु
				/* blank dp stream beक्रमe घातer off receiver*/
				अगर (dc->links[i]->link_enc->funcs->get_dig_frontend) अणु
					अचिन्हित पूर्णांक fe = dc->links[i]->link_enc->funcs->get_dig_frontend(dc->links[i]->link_enc);

					क्रम (j = 0; j < dc->res_pool->stream_enc_count; j++) अणु
						अगर (fe == dc->res_pool->stream_enc[j]->id) अणु
							dc->res_pool->stream_enc[j]->funcs->dp_blank(
										dc->res_pool->stream_enc[j]);
							अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				dp_receiver_घातer_ctrl(dc->links[i], false);
			पूर्ण
		पूर्ण
	पूर्ण

	/* If taking control over from VBIOS, we may want to optimize our first
	 * mode set, so we need to skip घातering करोwn pipes until we know which
	 * pipes we want to use.
	 * Otherwise, अगर taking control is not possible, we need to घातer
	 * everything करोwn.
	 */
	अगर (dcb->funcs->is_accelerated_mode(dcb) || dc->config.घातer_करोwn_display_on_boot) अणु
		अगर (!is_optimized_init_करोne) अणु
			hws->funcs.init_pipes(dc, dc->current_state);
			अगर (dc->res_pool->hubbub->funcs->allow_self_refresh_control)
				dc->res_pool->hubbub->funcs->allow_self_refresh_control(dc->res_pool->hubbub,
						!dc->res_pool->hubbub->ctx->dc->debug.disable_stutter);
		पूर्ण
	पूर्ण

	अगर (!is_optimized_init_करोne) अणु

		क्रम (i = 0; i < res_pool->audio_count; i++) अणु
			काष्ठा audio *audio = res_pool->audios[i];

			audio->funcs->hw_init(audio);
		पूर्ण

		क्रम (i = 0; i < dc->link_count; i++) अणु
			काष्ठा dc_link *link = dc->links[i];

			अगर (link->panel_cntl)
				backlight = link->panel_cntl->funcs->hw_init(link->panel_cntl);
		पूर्ण

		अगर (abm != शून्य)
			abm->funcs->abm_init(abm, backlight);

		अगर (dmcu != शून्य && !dmcu->स्वतः_load_dmcu)
			dmcu->funcs->dmcu_init(dmcu);
	पूर्ण

	अगर (abm != शून्य && dmcu != शून्य)
		abm->dmcu_is_running = dmcu->funcs->is_dmcu_initialized(dmcu);

	/* घातer AFMT HDMI memory TODO: may move to dis/en output save घातer*/
	अगर (!is_optimized_init_करोne)
		REG_WRITE(DIO_MEM_PWR_CTRL, 0);

	अगर (!dc->debug.disable_घड़ी_gate) अणु
		/* enable all DCN घड़ी gating */
		REG_WRITE(DCCG_GATE_DISABLE_CNTL, 0);

		REG_WRITE(DCCG_GATE_DISABLE_CNTL2, 0);

		REG_UPDATE(DCFCLK_CNTL, DCFCLK_GATE_DIS, 0);
	पूर्ण
	अगर (hws->funcs.enable_घातer_gating_plane)
		hws->funcs.enable_घातer_gating_plane(dc->hwseq, true);

	अगर (dc->clk_mgr->funcs->notअगरy_wm_ranges)
		dc->clk_mgr->funcs->notअगरy_wm_ranges(dc->clk_mgr);
पूर्ण

/* In headless boot हालs, DIG may be turned
 * on which causes HW/SW discrepancies.
 * To aव्योम this, घातer करोwn hardware on boot
 * अगर DIG is turned on
 */
व्योम dcn10_घातer_करोwn_on_boot(काष्ठा dc *dc)
अणु
	काष्ठा dc_link *edp_links[MAX_NUM_EDP];
	काष्ठा dc_link *edp_link;
	पूर्णांक edp_num;
	पूर्णांक i = 0;

	get_edp_links(dc, edp_links, &edp_num);

	अगर (edp_num) अणु
		क्रम (i = 0; i < edp_num; i++) अणु
			edp_link = edp_links[i];
			अगर (edp_link->link_enc->funcs->is_dig_enabled &&
					edp_link->link_enc->funcs->is_dig_enabled(edp_link->link_enc) &&
					dc->hwseq->funcs.edp_backlight_control &&
					dc->hwss.घातer_करोwn &&
					dc->hwss.edp_घातer_control) अणु
				dc->hwseq->funcs.edp_backlight_control(edp_link, false);
				dc->hwss.घातer_करोwn(dc);
				dc->hwss.edp_घातer_control(edp_link, false);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < dc->link_count; i++) अणु
			काष्ठा dc_link *link = dc->links[i];

			अगर (link->link_enc->funcs->is_dig_enabled &&
					link->link_enc->funcs->is_dig_enabled(link->link_enc) &&
					dc->hwss.घातer_करोwn) अणु
				dc->hwss.घातer_करोwn(dc);
				अवरोध;
			पूर्ण

		पूर्ण
	पूर्ण

	/*
	 * Call update_घड़ीs with empty context
	 * to send DISPLAY_OFF
	 * Otherwise DISPLAY_OFF may not be निश्चितed
	 */
	अगर (dc->clk_mgr->funcs->set_low_घातer_state)
		dc->clk_mgr->funcs->set_low_घातer_state(dc->clk_mgr);
पूर्ण

व्योम dcn10_reset_hw_ctx_wrap(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	/* Reset Back End*/
	क्रम (i = dc->res_pool->pipe_count - 1; i >= 0 ; i--) अणु
		काष्ठा pipe_ctx *pipe_ctx_old =
			&dc->current_state->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (!pipe_ctx_old->stream)
			जारी;

		अगर (pipe_ctx_old->top_pipe)
			जारी;

		अगर (!pipe_ctx->stream ||
				pipe_need_reprogram(pipe_ctx_old, pipe_ctx)) अणु
			काष्ठा घड़ी_source *old_clk = pipe_ctx_old->घड़ी_source;

			dcn10_reset_back_end_क्रम_pipe(dc, pipe_ctx_old, dc->current_state);
			अगर (hws->funcs.enable_stream_gating)
				hws->funcs.enable_stream_gating(dc, pipe_ctx);
			अगर (old_clk)
				old_clk->funcs->cs_घातer_करोwn(old_clk);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool patch_address_क्रम_sbs_tb_stereo(
		काष्ठा pipe_ctx *pipe_ctx, PHYSICAL_ADDRESS_LOC *addr)
अणु
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	bool sec_split = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->plane_state == pipe_ctx->plane_state;
	अगर (sec_split && plane_state->address.type == PLN_ADDR_TYPE_GRPH_STEREO &&
		(pipe_ctx->stream->timing.timing_3d_क्रमmat ==
		 TIMING_3D_FORMAT_SIDE_BY_SIDE ||
		 pipe_ctx->stream->timing.timing_3d_क्रमmat ==
		 TIMING_3D_FORMAT_TOP_AND_BOTTOM)) अणु
		*addr = plane_state->address.grph_stereo.left_addr;
		plane_state->address.grph_stereo.left_addr =
		plane_state->address.grph_stereo.right_addr;
		वापस true;
	पूर्ण अन्यथा अणु
		अगर (pipe_ctx->stream->view_क्रमmat != VIEW_3D_FORMAT_NONE &&
			plane_state->address.type != PLN_ADDR_TYPE_GRPH_STEREO) अणु
			plane_state->address.type = PLN_ADDR_TYPE_GRPH_STEREO;
			plane_state->address.grph_stereo.right_addr =
			plane_state->address.grph_stereo.left_addr;
			plane_state->address.grph_stereo.right_meta_addr =
			plane_state->address.grph_stereo.left_meta_addr;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

व्योम dcn10_update_plane_addr(स्थिर काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	bool addr_patched = false;
	PHYSICAL_ADDRESS_LOC addr;
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;

	अगर (plane_state == शून्य)
		वापस;

	addr_patched = patch_address_क्रम_sbs_tb_stereo(pipe_ctx, &addr);

	pipe_ctx->plane_res.hubp->funcs->hubp_program_surface_flip_and_addr(
			pipe_ctx->plane_res.hubp,
			&plane_state->address,
			plane_state->flip_immediate);

	plane_state->status.requested_address = plane_state->address;

	अगर (plane_state->flip_immediate)
		plane_state->status.current_address = plane_state->address;

	अगर (addr_patched)
		pipe_ctx->plane_state->address.grph_stereo.left_addr = addr;
पूर्ण

bool dcn10_set_input_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
			स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा dpp *dpp_base = pipe_ctx->plane_res.dpp;
	स्थिर काष्ठा dc_transfer_func *tf = शून्य;
	bool result = true;

	अगर (dpp_base == शून्य)
		वापस false;

	अगर (plane_state->in_transfer_func)
		tf = plane_state->in_transfer_func;

	अगर (plane_state->gamma_correction &&
		!dpp_base->ctx->dc->debug.always_use_regamma
		&& !plane_state->gamma_correction->is_identity
			&& dce_use_lut(plane_state->क्रमmat))
		dpp_base->funcs->dpp_program_input_lut(dpp_base, plane_state->gamma_correction);

	अगर (tf == शून्य)
		dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
	अन्यथा अगर (tf->type == TF_TYPE_PREDEFINED) अणु
		चयन (tf->tf) अणु
		हाल TRANSFER_FUNCTION_SRGB:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_HW_sRGB);
			अवरोध;
		हाल TRANSFER_FUNCTION_BT709:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_HW_xvYCC);
			अवरोध;
		हाल TRANSFER_FUNCTION_LINEAR:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
			अवरोध;
		हाल TRANSFER_FUNCTION_PQ:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_USER_PWL);
			cm_helper_translate_curve_to_degamma_hw_क्रमmat(tf, &dpp_base->degamma_params);
			dpp_base->funcs->dpp_program_degamma_pwl(dpp_base, &dpp_base->degamma_params);
			result = true;
			अवरोध;
		शेष:
			result = false;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (tf->type == TF_TYPE_BYPASS) अणु
		dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
	पूर्ण अन्यथा अणु
		cm_helper_translate_curve_to_degamma_hw_क्रमmat(tf,
					&dpp_base->degamma_params);
		dpp_base->funcs->dpp_program_degamma_pwl(dpp_base,
				&dpp_base->degamma_params);
		result = true;
	पूर्ण

	वापस result;
पूर्ण

#घोषणा MAX_NUM_HW_POINTS 0x200

अटल व्योम log_tf(काष्ठा dc_context *ctx,
				काष्ठा dc_transfer_func *tf, uपूर्णांक32_t hw_poपूर्णांकs_num)
अणु
	// DC_LOG_GAMMA is शेष logging of all hw poपूर्णांकs
	// DC_LOG_ALL_GAMMA logs all poपूर्णांकs, not only hw poपूर्णांकs
	// DC_LOG_ALL_TF_POINTS logs all channels of the tf
	पूर्णांक i = 0;

	DC_LOGGER_INIT(ctx->logger);
	DC_LOG_GAMMA("Gamma Correction TF");
	DC_LOG_ALL_GAMMA("Logging all tf points...");
	DC_LOG_ALL_TF_CHANNELS("Logging all channels...");

	क्रम (i = 0; i < hw_poपूर्णांकs_num; i++) अणु
		DC_LOG_GAMMA("R\t%d\t%llu", i, tf->tf_pts.red[i].value);
		DC_LOG_ALL_TF_CHANNELS("G\t%d\t%llu", i, tf->tf_pts.green[i].value);
		DC_LOG_ALL_TF_CHANNELS("B\t%d\t%llu", i, tf->tf_pts.blue[i].value);
	पूर्ण

	क्रम (i = hw_poपूर्णांकs_num; i < MAX_NUM_HW_POINTS; i++) अणु
		DC_LOG_ALL_GAMMA("R\t%d\t%llu", i, tf->tf_pts.red[i].value);
		DC_LOG_ALL_TF_CHANNELS("G\t%d\t%llu", i, tf->tf_pts.green[i].value);
		DC_LOG_ALL_TF_CHANNELS("B\t%d\t%llu", i, tf->tf_pts.blue[i].value);
	पूर्ण
पूर्ण

bool dcn10_set_output_transfer_func(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dpp *dpp = pipe_ctx->plane_res.dpp;

	अगर (dpp == शून्य)
		वापस false;

	dpp->regamma_params.hw_poपूर्णांकs_num = GAMMA_HW_POINTS_NUM;

	अगर (stream->out_transfer_func &&
	    stream->out_transfer_func->type == TF_TYPE_PREDEFINED &&
	    stream->out_transfer_func->tf == TRANSFER_FUNCTION_SRGB)
		dpp->funcs->dpp_program_regamma_pwl(dpp, शून्य, OPP_REGAMMA_SRGB);

	/* dcn10_translate_regamma_to_hw_क्रमmat takes 750us, only करो it when full
	 * update.
	 */
	अन्यथा अगर (cm_helper_translate_curve_to_hw_क्रमmat(
			stream->out_transfer_func,
			&dpp->regamma_params, false)) अणु
		dpp->funcs->dpp_program_regamma_pwl(
				dpp,
				&dpp->regamma_params, OPP_REGAMMA_USER);
	पूर्ण अन्यथा
		dpp->funcs->dpp_program_regamma_pwl(dpp, शून्य, OPP_REGAMMA_BYPASS);

	अगर (stream != शून्य && stream->ctx != शून्य &&
			stream->out_transfer_func != शून्य) अणु
		log_tf(stream->ctx,
				stream->out_transfer_func,
				dpp->regamma_params.hw_poपूर्णांकs_num);
	पूर्ण

	वापस true;
पूर्ण

व्योम dcn10_pipe_control_lock(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe,
	bool lock)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;

	/* use TG master update lock to lock everything on the TG
	 * thereक्रमe only top pipe need to lock
	 */
	अगर (!pipe || pipe->top_pipe)
		वापस;

	अगर (dc->debug.sanity_checks)
		hws->funcs.verअगरy_allow_pstate_change_high(dc);

	अगर (lock)
		pipe->stream_res.tg->funcs->lock(pipe->stream_res.tg);
	अन्यथा
		pipe->stream_res.tg->funcs->unlock(pipe->stream_res.tg);

	अगर (dc->debug.sanity_checks)
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
पूर्ण

/**
 * delay_cursor_until_vupdate() - Delay cursor update अगर too बंद to VUPDATE.
 *
 * Software keepout workaround to prevent cursor update locking from stalling
 * out cursor updates indefinitely or from old values from being retained in
 * the हाल where the viewport changes in the same frame as the cursor.
 *
 * The idea is to calculate the reमुख्यing समय from VPOS to VUPDATE. If it's
 * too बंद to VUPDATE, then stall out until VUPDATE finishes.
 *
 * TODO: Optimize cursor programming to be once per frame beक्रमe VUPDATE
 *       to aव्योम the need क्रम this workaround.
 */
अटल व्योम delay_cursor_until_vupdate(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा crtc_position position;
	uपूर्णांक32_t vupdate_start, vupdate_end;
	अचिन्हित पूर्णांक lines_to_vupdate, us_to_vupdate, vpos;
	अचिन्हित पूर्णांक us_per_line, us_vupdate;

	अगर (!dc->hwss.calc_vupdate_position || !dc->hwss.get_position)
		वापस;

	अगर (!pipe_ctx->stream_res.stream_enc || !pipe_ctx->stream_res.tg)
		वापस;

	dc->hwss.calc_vupdate_position(dc, pipe_ctx, &vupdate_start,
				       &vupdate_end);

	dc->hwss.get_position(&pipe_ctx, 1, &position);
	vpos = position.vertical_count;

	/* Aव्योम wraparound calculation issues */
	vupdate_start += stream->timing.v_total;
	vupdate_end += stream->timing.v_total;
	vpos += stream->timing.v_total;

	अगर (vpos <= vupdate_start) अणु
		/* VPOS is in VACTIVE or back porch. */
		lines_to_vupdate = vupdate_start - vpos;
	पूर्ण अन्यथा अगर (vpos > vupdate_end) अणु
		/* VPOS is in the front porch. */
		वापस;
	पूर्ण अन्यथा अणु
		/* VPOS is in VUPDATE. */
		lines_to_vupdate = 0;
	पूर्ण

	/* Calculate समय until VUPDATE in microseconds. */
	us_per_line =
		stream->timing.h_total * 10000u / stream->timing.pix_clk_100hz;
	us_to_vupdate = lines_to_vupdate * us_per_line;

	/* 70 us is a conservative estimate of cursor update समय*/
	अगर (us_to_vupdate > 70)
		वापस;

	/* Stall out until the cursor update completes. */
	अगर (vupdate_end < vupdate_start)
		vupdate_end += stream->timing.v_total;
	us_vupdate = (vupdate_end - vupdate_start + 1) * us_per_line;
	udelay(us_to_vupdate + us_vupdate);
पूर्ण

व्योम dcn10_cursor_lock(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe, bool lock)
अणु
	/* cursor lock is per MPCC tree, so only need to lock one pipe per stream */
	अगर (!pipe || pipe->top_pipe)
		वापस;

	/* Prevent cursor lock from stalling out cursor updates. */
	अगर (lock)
		delay_cursor_until_vupdate(dc, pipe);

	अगर (pipe->stream && should_use_dmub_lock(pipe->stream->link)) अणु
		जोड़ dmub_hw_lock_flags hw_locks = अणु 0 पूर्ण;
		काष्ठा dmub_hw_lock_inst_flags inst_flags = अणु 0 पूर्ण;

		hw_locks.bits.lock_cursor = 1;
		inst_flags.opp_inst = pipe->stream_res.opp->inst;

		dmub_hw_lock_mgr_cmd(dc->ctx->dmub_srv,
					lock,
					&hw_locks,
					&inst_flags);
	पूर्ण अन्यथा
		dc->res_pool->mpc->funcs->cursor_lock(dc->res_pool->mpc,
				pipe->stream_res.opp->inst, lock);
पूर्ण

अटल bool रुको_क्रम_reset_trigger_to_occur(
	काष्ठा dc_context *dc_ctx,
	काष्ठा timing_generator *tg)
अणु
	bool rc = false;

	/* To aव्योम endless loop we रुको at most
	 * frames_to_रुको_on_triggered_reset frames क्रम the reset to occur. */
	स्थिर uपूर्णांक32_t frames_to_रुको_on_triggered_reset = 10;
	पूर्णांक i;

	क्रम (i = 0; i < frames_to_रुको_on_triggered_reset; i++) अणु

		अगर (!tg->funcs->is_counter_moving(tg)) अणु
			DC_ERROR("TG counter is not moving!\n");
			अवरोध;
		पूर्ण

		अगर (tg->funcs->did_triggered_reset_occur(tg)) अणु
			rc = true;
			/* usually occurs at i=1 */
			DC_SYNC_INFO("GSL: reset occurred at wait count: %d\n",
					i);
			अवरोध;
		पूर्ण

		/* Wait क्रम one frame. */
		tg->funcs->रुको_क्रम_state(tg, CRTC_STATE_VACTIVE);
		tg->funcs->रुको_क्रम_state(tg, CRTC_STATE_VBLANK);
	पूर्ण

	अगर (false == rc)
		DC_ERROR("GSL: Timeout on reset trigger!\n");

	वापस rc;
पूर्ण

uपूर्णांक64_t reduceSizeAndFraction(
	uपूर्णांक64_t *numerator,
	uपूर्णांक64_t *denominator,
	bool checkUपूर्णांक32Bounary)
अणु
	पूर्णांक i;
	bool ret = checkUपूर्णांक32Bounary == false;
	uपूर्णांक64_t max_पूर्णांक32 = 0xffffffff;
	uपूर्णांक64_t num, denom;
	अटल स्थिर uपूर्णांक16_t prime_numbers[] = अणु
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
		47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
		107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
		167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227,
		229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
		283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353,
		359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421,
		431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487,
		491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569,
		571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631,
		641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
		709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773,
		787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857,
		859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
		941, 947, 953, 967, 971, 977, 983, 991, 997पूर्ण;
	पूर्णांक count = ARRAY_SIZE(prime_numbers);

	num = *numerator;
	denom = *denominator;
	क्रम (i = 0; i < count; i++) अणु
		uपूर्णांक32_t num_reमुख्यder, denom_reमुख्यder;
		uपूर्णांक64_t num_result, denom_result;
		अगर (checkUपूर्णांक32Bounary &&
			num <= max_पूर्णांक32 && denom <= max_पूर्णांक32) अणु
			ret = true;
			अवरोध;
		पूर्ण
		करो अणु
			num_result = भाग_u64_rem(num, prime_numbers[i], &num_reमुख्यder);
			denom_result = भाग_u64_rem(denom, prime_numbers[i], &denom_reमुख्यder);
			अगर (num_reमुख्यder == 0 && denom_reमुख्यder == 0) अणु
				num = num_result;
				denom = denom_result;
			पूर्ण
		पूर्ण जबतक (num_reमुख्यder == 0 && denom_reमुख्यder == 0);
	पूर्ण
	*numerator = num;
	*denominator = denom;
	वापस ret;
पूर्ण

bool is_low_refresh_rate(काष्ठा pipe_ctx *pipe)
अणु
	uपूर्णांक32_t master_pipe_refresh_rate =
		pipe->stream->timing.pix_clk_100hz * 100 /
		pipe->stream->timing.h_total /
		pipe->stream->timing.v_total;
	वापस master_pipe_refresh_rate <= 30;
पूर्ण

uपूर्णांक8_t get_घड़ी_भागider(काष्ठा pipe_ctx *pipe, bool account_low_refresh_rate)
अणु
	uपूर्णांक32_t घड़ी_भागider = 1;
	uपूर्णांक32_t numpipes = 1;

	अगर (account_low_refresh_rate && is_low_refresh_rate(pipe))
		घड़ी_भागider *= 2;

	अगर (pipe->stream_res.pix_clk_params.pixel_encoding == PIXEL_ENCODING_YCBCR420)
		घड़ी_भागider *= 2;

	जबतक (pipe->next_odm_pipe) अणु
		pipe = pipe->next_odm_pipe;
		numpipes++;
	पूर्ण
	घड़ी_भागider *= numpipes;

	वापस घड़ी_भागider;
पूर्ण

पूर्णांक dcn10_align_pixel_घड़ीs(
	काष्ठा dc *dc,
	पूर्णांक group_size,
	काष्ठा pipe_ctx *grouped_pipes[])
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	पूर्णांक i, master = -1, embedded = -1;
	काष्ठा dc_crtc_timing hw_crtc_timing[MAX_PIPES] = अणु0पूर्ण;
	uपूर्णांक64_t phase[MAX_PIPES];
	uपूर्णांक64_t modulo[MAX_PIPES];
	अचिन्हित पूर्णांक pclk;

	uपूर्णांक32_t embedded_pix_clk_100hz;
	uपूर्णांक16_t embedded_h_total;
	uपूर्णांक16_t embedded_v_total;
	bool clamshell_बंदd = false;
	uपूर्णांक32_t dp_ref_clk_100hz =
		dc->res_pool->dp_घड़ी_source->ctx->dc->clk_mgr->dprefclk_khz*10;

	अगर (dc->config.vblank_alignment_dto_params &&
		dc->res_pool->dp_घड़ी_source->funcs->override_dp_pix_clk) अणु
		clamshell_बंदd =
			(dc->config.vblank_alignment_dto_params >> 63);
		embedded_h_total =
			(dc->config.vblank_alignment_dto_params >> 32) & 0x7FFF;
		embedded_v_total =
			(dc->config.vblank_alignment_dto_params >> 48) & 0x7FFF;
		embedded_pix_clk_100hz =
			dc->config.vblank_alignment_dto_params & 0xFFFFFFFF;

		क्रम (i = 0; i < group_size; i++) अणु
			grouped_pipes[i]->stream_res.tg->funcs->get_hw_timing(
					grouped_pipes[i]->stream_res.tg,
					&hw_crtc_timing[i]);
			dc->res_pool->dp_घड़ी_source->funcs->get_pixel_clk_frequency_100hz(
				dc->res_pool->dp_घड़ी_source,
				grouped_pipes[i]->stream_res.tg->inst,
				&pclk);
			hw_crtc_timing[i].pix_clk_100hz = pclk;
			अगर (dc_is_embedded_संकेत(
					grouped_pipes[i]->stream->संकेत)) अणु
				embedded = i;
				master = i;
				phase[i] = embedded_pix_clk_100hz*100;
				modulo[i] = dp_ref_clk_100hz*100;
			पूर्ण अन्यथा अणु

				phase[i] = (uपूर्णांक64_t)embedded_pix_clk_100hz*
					hw_crtc_timing[i].h_total*
					hw_crtc_timing[i].v_total;
				phase[i] = भाग_u64(phase[i], get_घड़ी_भागider(grouped_pipes[i], true));
				modulo[i] = (uपूर्णांक64_t)dp_ref_clk_100hz*
					embedded_h_total*
					embedded_v_total;

				अगर (reduceSizeAndFraction(&phase[i],
						&modulo[i], true) == false) अणु
					/*
					 * this will help to stop reporting
					 * this timing synchronizable
					 */
					DC_SYNC_INFO("Failed to reduce DTO parameters\n");
					grouped_pipes[i]->stream->has_non_synchronizable_pclk = true;
				पूर्ण
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < group_size; i++) अणु
			अगर (i != embedded && !grouped_pipes[i]->stream->has_non_synchronizable_pclk) अणु
				dc->res_pool->dp_घड़ी_source->funcs->override_dp_pix_clk(
					dc->res_pool->dp_घड़ी_source,
					grouped_pipes[i]->stream_res.tg->inst,
					phase[i], modulo[i]);
				dc->res_pool->dp_घड़ी_source->funcs->get_pixel_clk_frequency_100hz(
					dc->res_pool->dp_घड़ी_source,
					grouped_pipes[i]->stream_res.tg->inst, &pclk);
					grouped_pipes[i]->stream->timing.pix_clk_100hz =
						pclk*get_घड़ी_भागider(grouped_pipes[i], false);
				अगर (master == -1)
					master = i;
			पूर्ण
		पूर्ण

	पूर्ण
	वापस master;
पूर्ण

व्योम dcn10_enable_vblanks_synchronization(
	काष्ठा dc *dc,
	पूर्णांक group_index,
	पूर्णांक group_size,
	काष्ठा pipe_ctx *grouped_pipes[])
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा output_pixel_processor *opp;
	काष्ठा timing_generator *tg;
	पूर्णांक i, width, height, master;

	क्रम (i = 1; i < group_size; i++) अणु
		opp = grouped_pipes[i]->stream_res.opp;
		tg = grouped_pipes[i]->stream_res.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);
		अगर (opp->funcs->opp_program_dpg_dimensions)
			opp->funcs->opp_program_dpg_dimensions(opp, width, 2*(height) + 1);
	पूर्ण

	क्रम (i = 0; i < group_size; i++) अणु
		अगर (grouped_pipes[i]->stream == शून्य)
			जारी;
		grouped_pipes[i]->stream->vblank_synchronized = false;
		grouped_pipes[i]->stream->has_non_synchronizable_pclk = false;
	पूर्ण

	DC_SYNC_INFO("Aligning DP DTOs\n");

	master = dcn10_align_pixel_घड़ीs(dc, group_size, grouped_pipes);

	DC_SYNC_INFO("Synchronizing VBlanks\n");

	अगर (master >= 0) अणु
		क्रम (i = 0; i < group_size; i++) अणु
			अगर (i != master && !grouped_pipes[i]->stream->has_non_synchronizable_pclk)
			grouped_pipes[i]->stream_res.tg->funcs->align_vblanks(
				grouped_pipes[master]->stream_res.tg,
				grouped_pipes[i]->stream_res.tg,
				grouped_pipes[master]->stream->timing.pix_clk_100hz,
				grouped_pipes[i]->stream->timing.pix_clk_100hz,
				get_घड़ी_भागider(grouped_pipes[master], false),
				get_घड़ी_भागider(grouped_pipes[i], false));
				grouped_pipes[i]->stream->vblank_synchronized = true;
		पूर्ण
		grouped_pipes[master]->stream->vblank_synchronized = true;
		DC_SYNC_INFO("Sync complete\n");
	पूर्ण

	क्रम (i = 1; i < group_size; i++) अणु
		opp = grouped_pipes[i]->stream_res.opp;
		tg = grouped_pipes[i]->stream_res.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);
		अगर (opp->funcs->opp_program_dpg_dimensions)
			opp->funcs->opp_program_dpg_dimensions(opp, width, height);
	पूर्ण
पूर्ण

व्योम dcn10_enable_timing_synchronization(
	काष्ठा dc *dc,
	पूर्णांक group_index,
	पूर्णांक group_size,
	काष्ठा pipe_ctx *grouped_pipes[])
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	काष्ठा output_pixel_processor *opp;
	काष्ठा timing_generator *tg;
	पूर्णांक i, width, height;

	DC_SYNC_INFO("Setting up OTG reset trigger\n");

	क्रम (i = 1; i < group_size; i++) अणु
		opp = grouped_pipes[i]->stream_res.opp;
		tg = grouped_pipes[i]->stream_res.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);
		अगर (opp->funcs->opp_program_dpg_dimensions)
			opp->funcs->opp_program_dpg_dimensions(opp, width, 2*(height) + 1);
	पूर्ण

	क्रम (i = 0; i < group_size; i++) अणु
		अगर (grouped_pipes[i]->stream == शून्य)
			जारी;
		grouped_pipes[i]->stream->vblank_synchronized = false;
	पूर्ण

	क्रम (i = 1; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->enable_reset_trigger(
				grouped_pipes[i]->stream_res.tg,
				grouped_pipes[0]->stream_res.tg->inst);

	DC_SYNC_INFO("Waiting for trigger\n");

	/* Need to get only check 1 pipe क्रम having reset as all the others are
	 * synchronized. Look at last pipe programmed to reset.
	 */

	रुको_क्रम_reset_trigger_to_occur(dc_ctx, grouped_pipes[1]->stream_res.tg);
	क्रम (i = 1; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->disable_reset_trigger(
				grouped_pipes[i]->stream_res.tg);

	क्रम (i = 1; i < group_size; i++) अणु
		opp = grouped_pipes[i]->stream_res.opp;
		tg = grouped_pipes[i]->stream_res.tg;
		tg->funcs->get_otg_active_size(tg, &width, &height);
		अगर (opp->funcs->opp_program_dpg_dimensions)
			opp->funcs->opp_program_dpg_dimensions(opp, width, height);
	पूर्ण

	DC_SYNC_INFO("Sync complete\n");
पूर्ण

व्योम dcn10_enable_per_frame_crtc_position_reset(
	काष्ठा dc *dc,
	पूर्णांक group_size,
	काष्ठा pipe_ctx *grouped_pipes[])
अणु
	काष्ठा dc_context *dc_ctx = dc->ctx;
	पूर्णांक i;

	DC_SYNC_INFO("Setting up\n");
	क्रम (i = 0; i < group_size; i++)
		अगर (grouped_pipes[i]->stream_res.tg->funcs->enable_crtc_reset)
			grouped_pipes[i]->stream_res.tg->funcs->enable_crtc_reset(
					grouped_pipes[i]->stream_res.tg,
					0,
					&grouped_pipes[i]->stream->triggered_crtc_reset);

	DC_SYNC_INFO("Waiting for trigger\n");

	क्रम (i = 0; i < group_size; i++)
		रुको_क्रम_reset_trigger_to_occur(dc_ctx, grouped_pipes[i]->stream_res.tg);

	DC_SYNC_INFO("Multi-display sync is complete\n");
पूर्ण

/*अटल व्योम prपूर्णांक_rq_dlg_ttu(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	DC_LOG_BANDWIDTH_CALCS(dc->ctx->logger,
			"\n============== DML TTU Output parameters [%d] ==============\n"
			"qos_level_low_wm: %d, \n"
			"qos_level_high_wm: %d, \n"
			"min_ttu_vblank: %d, \n"
			"qos_level_flip: %d, \n"
			"refcyc_per_req_delivery_l: %d, \n"
			"qos_level_fixed_l: %d, \n"
			"qos_ramp_disable_l: %d, \n"
			"refcyc_per_req_delivery_pre_l: %d, \n"
			"refcyc_per_req_delivery_c: %d, \n"
			"qos_level_fixed_c: %d, \n"
			"qos_ramp_disable_c: %d, \n"
			"refcyc_per_req_delivery_pre_c: %d\n"
			"=============================================================\n",
			pipe_ctx->pipe_idx,
			pipe_ctx->ttu_regs.qos_level_low_wm,
			pipe_ctx->ttu_regs.qos_level_high_wm,
			pipe_ctx->ttu_regs.min_ttu_vblank,
			pipe_ctx->ttu_regs.qos_level_flip,
			pipe_ctx->ttu_regs.refcyc_per_req_delivery_l,
			pipe_ctx->ttu_regs.qos_level_fixed_l,
			pipe_ctx->ttu_regs.qos_ramp_disable_l,
			pipe_ctx->ttu_regs.refcyc_per_req_delivery_pre_l,
			pipe_ctx->ttu_regs.refcyc_per_req_delivery_c,
			pipe_ctx->ttu_regs.qos_level_fixed_c,
			pipe_ctx->ttu_regs.qos_ramp_disable_c,
			pipe_ctx->ttu_regs.refcyc_per_req_delivery_pre_c
			);

	DC_LOG_BANDWIDTH_CALCS(dc->ctx->logger,
			"\n============== DML DLG Output parameters [%d] ==============\n"
			"refcyc_h_blank_end: %d, \n"
			"dlg_vblank_end: %d, \n"
			"min_dst_y_next_start: %d, \n"
			"refcyc_per_htotal: %d, \n"
			"refcyc_x_after_scaler: %d, \n"
			"dst_y_after_scaler: %d, \n"
			"dst_y_prefetch: %d, \n"
			"dst_y_per_vm_vblank: %d, \n"
			"dst_y_per_row_vblank: %d, \n"
			"ref_freq_to_pix_freq: %d, \n"
			"vratio_prefetch: %d, \n"
			"refcyc_per_pte_group_vblank_l: %d, \n"
			"refcyc_per_meta_chunk_vblank_l: %d, \n"
			"dst_y_per_pte_row_nom_l: %d, \n"
			"refcyc_per_pte_group_nom_l: %d, \n",
			pipe_ctx->pipe_idx,
			pipe_ctx->dlg_regs.refcyc_h_blank_end,
			pipe_ctx->dlg_regs.dlg_vblank_end,
			pipe_ctx->dlg_regs.min_dst_y_next_start,
			pipe_ctx->dlg_regs.refcyc_per_htotal,
			pipe_ctx->dlg_regs.refcyc_x_after_scaler,
			pipe_ctx->dlg_regs.dst_y_after_scaler,
			pipe_ctx->dlg_regs.dst_y_prefetch,
			pipe_ctx->dlg_regs.dst_y_per_vm_vblank,
			pipe_ctx->dlg_regs.dst_y_per_row_vblank,
			pipe_ctx->dlg_regs.ref_freq_to_pix_freq,
			pipe_ctx->dlg_regs.vratio_prefetch,
			pipe_ctx->dlg_regs.refcyc_per_pte_group_vblank_l,
			pipe_ctx->dlg_regs.refcyc_per_meta_chunk_vblank_l,
			pipe_ctx->dlg_regs.dst_y_per_pte_row_nom_l,
			pipe_ctx->dlg_regs.refcyc_per_pte_group_nom_l
			);

	DC_LOG_BANDWIDTH_CALCS(dc->ctx->logger,
			"\ndst_y_per_meta_row_nom_l: %d, \n"
			"refcyc_per_meta_chunk_nom_l: %d, \n"
			"refcyc_per_line_delivery_pre_l: %d, \n"
			"refcyc_per_line_delivery_l: %d, \n"
			"vratio_prefetch_c: %d, \n"
			"refcyc_per_pte_group_vblank_c: %d, \n"
			"refcyc_per_meta_chunk_vblank_c: %d, \n"
			"dst_y_per_pte_row_nom_c: %d, \n"
			"refcyc_per_pte_group_nom_c: %d, \n"
			"dst_y_per_meta_row_nom_c: %d, \n"
			"refcyc_per_meta_chunk_nom_c: %d, \n"
			"refcyc_per_line_delivery_pre_c: %d, \n"
			"refcyc_per_line_delivery_c: %d \n"
			"========================================================\n",
			pipe_ctx->dlg_regs.dst_y_per_meta_row_nom_l,
			pipe_ctx->dlg_regs.refcyc_per_meta_chunk_nom_l,
			pipe_ctx->dlg_regs.refcyc_per_line_delivery_pre_l,
			pipe_ctx->dlg_regs.refcyc_per_line_delivery_l,
			pipe_ctx->dlg_regs.vratio_prefetch_c,
			pipe_ctx->dlg_regs.refcyc_per_pte_group_vblank_c,
			pipe_ctx->dlg_regs.refcyc_per_meta_chunk_vblank_c,
			pipe_ctx->dlg_regs.dst_y_per_pte_row_nom_c,
			pipe_ctx->dlg_regs.refcyc_per_pte_group_nom_c,
			pipe_ctx->dlg_regs.dst_y_per_meta_row_nom_c,
			pipe_ctx->dlg_regs.refcyc_per_meta_chunk_nom_c,
			pipe_ctx->dlg_regs.refcyc_per_line_delivery_pre_c,
			pipe_ctx->dlg_regs.refcyc_per_line_delivery_c
			);

	DC_LOG_BANDWIDTH_CALCS(dc->ctx->logger,
			"\n============== DML RQ Output parameters [%d] ==============\n"
			"chunk_size: %d \n"
			"min_chunk_size: %d \n"
			"meta_chunk_size: %d \n"
			"min_meta_chunk_size: %d \n"
			"dpte_group_size: %d \n"
			"mpte_group_size: %d \n"
			"swath_height: %d \n"
			"pte_row_height_linear: %d \n"
			"========================================================\n",
			pipe_ctx->pipe_idx,
			pipe_ctx->rq_regs.rq_regs_l.chunk_size,
			pipe_ctx->rq_regs.rq_regs_l.min_chunk_size,
			pipe_ctx->rq_regs.rq_regs_l.meta_chunk_size,
			pipe_ctx->rq_regs.rq_regs_l.min_meta_chunk_size,
			pipe_ctx->rq_regs.rq_regs_l.dpte_group_size,
			pipe_ctx->rq_regs.rq_regs_l.mpte_group_size,
			pipe_ctx->rq_regs.rq_regs_l.swath_height,
			pipe_ctx->rq_regs.rq_regs_l.pte_row_height_linear
			);
पूर्ण
*/

अटल व्योम mmhub_पढ़ो_vm_प्रणाली_aperture_settings(काष्ठा dcn10_hubp *hubp1,
		काष्ठा vm_प्रणाली_aperture_param *apt,
		काष्ठा dce_hwseq *hws)
अणु
	PHYSICAL_ADDRESS_LOC physical_page_number;
	uपूर्णांक32_t logical_addr_low;
	uपूर्णांक32_t logical_addr_high;

	REG_GET(MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_MSB,
			PHYSICAL_PAGE_NUMBER_MSB, &physical_page_number.high_part);
	REG_GET(MC_VM_SYSTEM_APERTURE_DEFAULT_ADDR_LSB,
			PHYSICAL_PAGE_NUMBER_LSB, &physical_page_number.low_part);

	REG_GET(MC_VM_SYSTEM_APERTURE_LOW_ADDR,
			LOGICAL_ADDR, &logical_addr_low);

	REG_GET(MC_VM_SYSTEM_APERTURE_HIGH_ADDR,
			LOGICAL_ADDR, &logical_addr_high);

	apt->sys_शेष.quad_part =  physical_page_number.quad_part << 12;
	apt->sys_low.quad_part =  (पूर्णांक64_t)logical_addr_low << 18;
	apt->sys_high.quad_part =  (पूर्णांक64_t)logical_addr_high << 18;
पूर्ण

/* Temporary पढ़ो settings, future will get values from kmd directly */
अटल व्योम mmhub_पढ़ो_vm_context0_settings(काष्ठा dcn10_hubp *hubp1,
		काष्ठा vm_context0_param *vm0,
		काष्ठा dce_hwseq *hws)
अणु
	PHYSICAL_ADDRESS_LOC fb_base;
	PHYSICAL_ADDRESS_LOC fb_offset;
	uपूर्णांक32_t fb_base_value;
	uपूर्णांक32_t fb_offset_value;

	REG_GET(DCHUBBUB_SDPIF_FB_BASE, SDPIF_FB_BASE, &fb_base_value);
	REG_GET(DCHUBBUB_SDPIF_FB_OFFSET, SDPIF_FB_OFFSET, &fb_offset_value);

	REG_GET(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_HI32,
			PAGE_सूचीECTORY_ENTRY_HI32, &vm0->pte_base.high_part);
	REG_GET(VM_CONTEXT0_PAGE_TABLE_BASE_ADDR_LO32,
			PAGE_सूचीECTORY_ENTRY_LO32, &vm0->pte_base.low_part);

	REG_GET(VM_CONTEXT0_PAGE_TABLE_START_ADDR_HI32,
			LOGICAL_PAGE_NUMBER_HI4, &vm0->pte_start.high_part);
	REG_GET(VM_CONTEXT0_PAGE_TABLE_START_ADDR_LO32,
			LOGICAL_PAGE_NUMBER_LO32, &vm0->pte_start.low_part);

	REG_GET(VM_CONTEXT0_PAGE_TABLE_END_ADDR_HI32,
			LOGICAL_PAGE_NUMBER_HI4, &vm0->pte_end.high_part);
	REG_GET(VM_CONTEXT0_PAGE_TABLE_END_ADDR_LO32,
			LOGICAL_PAGE_NUMBER_LO32, &vm0->pte_end.low_part);

	REG_GET(VM_L2_PROTECTION_FAULT_DEFAULT_ADDR_HI32,
			PHYSICAL_PAGE_ADDR_HI4, &vm0->fault_शेष.high_part);
	REG_GET(VM_L2_PROTECTION_FAULT_DEFAULT_ADDR_LO32,
			PHYSICAL_PAGE_ADDR_LO32, &vm0->fault_शेष.low_part);

	/*
	 * The values in VM_CONTEXT0_PAGE_TABLE_BASE_ADDR is in UMA space.
	 * Thereक्रमe we need to करो
	 * DCN_VM_CONTEXT0_PAGE_TABLE_BASE_ADDR = VM_CONTEXT0_PAGE_TABLE_BASE_ADDR
	 * - DCHUBBUB_SDPIF_FB_OFFSET + DCHUBBUB_SDPIF_FB_BASE
	 */
	fb_base.quad_part = (uपूर्णांक64_t)fb_base_value << 24;
	fb_offset.quad_part = (uपूर्णांक64_t)fb_offset_value << 24;
	vm0->pte_base.quad_part += fb_base.quad_part;
	vm0->pte_base.quad_part -= fb_offset.quad_part;
पूर्ण


व्योम dcn10_program_pte_vm(काष्ठा dce_hwseq *hws, काष्ठा hubp *hubp)
अणु
	काष्ठा dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	काष्ठा vm_प्रणाली_aperture_param apt = अणु अणुअणु 0 पूर्ण पूर्ण पूर्ण;
	काष्ठा vm_context0_param vm0 = अणु अणु अणु 0 पूर्ण पूर्ण पूर्ण;

	mmhub_पढ़ो_vm_प्रणाली_aperture_settings(hubp1, &apt, hws);
	mmhub_पढ़ो_vm_context0_settings(hubp1, &vm0, hws);

	hubp->funcs->hubp_set_vm_प्रणाली_aperture_settings(hubp, &apt);
	hubp->funcs->hubp_set_vm_context0_settings(hubp, &vm0);
पूर्ण

अटल व्योम dcn10_enable_plane(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;

	अगर (dc->debug.sanity_checks) अणु
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
	पूर्ण

	unकरो_DEGVIDCN10_253_wa(dc);

	घातer_on_plane(dc->hwseq,
		pipe_ctx->plane_res.hubp->inst);

	/* enable DCFCLK current DCHUB */
	pipe_ctx->plane_res.hubp->funcs->hubp_clk_cntl(pipe_ctx->plane_res.hubp, true);

	/* make sure OPP_PIPE_CLOCK_EN = 1 */
	pipe_ctx->stream_res.opp->funcs->opp_pipe_घड़ी_control(
			pipe_ctx->stream_res.opp,
			true);

/* TODO: enable/disable in dm as per update type.
	अगर (plane_state) अणु
		DC_LOG_DC(dc->ctx->logger,
				"Pipe:%d 0x%x: addr hi:0x%x, "
				"addr low:0x%x, "
				"src: %d, %d, %d,"
				" %d; dst: %d, %d, %d, %d;\n",
				pipe_ctx->pipe_idx,
				plane_state,
				plane_state->address.grph.addr.high_part,
				plane_state->address.grph.addr.low_part,
				plane_state->src_rect.x,
				plane_state->src_rect.y,
				plane_state->src_rect.width,
				plane_state->src_rect.height,
				plane_state->dst_rect.x,
				plane_state->dst_rect.y,
				plane_state->dst_rect.width,
				plane_state->dst_rect.height);

		DC_LOG_DC(dc->ctx->logger,
				"Pipe %d: width, height, x, y         format:%d\n"
				"viewport:%d, %d, %d, %d\n"
				"recout:  %d, %d, %d, %d\n",
				pipe_ctx->pipe_idx,
				plane_state->क्रमmat,
				pipe_ctx->plane_res.scl_data.viewport.width,
				pipe_ctx->plane_res.scl_data.viewport.height,
				pipe_ctx->plane_res.scl_data.viewport.x,
				pipe_ctx->plane_res.scl_data.viewport.y,
				pipe_ctx->plane_res.scl_data.recout.width,
				pipe_ctx->plane_res.scl_data.recout.height,
				pipe_ctx->plane_res.scl_data.recout.x,
				pipe_ctx->plane_res.scl_data.recout.y);
		prपूर्णांक_rq_dlg_ttu(dc, pipe_ctx);
	पूर्ण
*/
	अगर (dc->config.gpu_vm_support)
		dcn10_program_pte_vm(hws, pipe_ctx->plane_res.hubp);

	अगर (dc->debug.sanity_checks) अणु
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
	पूर्ण

	अगर (!pipe_ctx->top_pipe
		&& pipe_ctx->plane_state
		&& pipe_ctx->plane_state->flip_पूर्णांक_enabled
		&& pipe_ctx->plane_res.hubp->funcs->hubp_set_flip_पूर्णांक)
			pipe_ctx->plane_res.hubp->funcs->hubp_set_flip_पूर्णांक(pipe_ctx->plane_res.hubp);

पूर्ण

व्योम dcn10_program_gamut_remap(काष्ठा pipe_ctx *pipe_ctx)
अणु
	पूर्णांक i = 0;
	काष्ठा dpp_grph_csc_adjusपंचांगent adjust;
	स_रखो(&adjust, 0, माप(adjust));
	adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS;


	अगर (pipe_ctx->stream->gamut_remap_matrix.enable_remap == true) अणु
		adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_SW;
		क्रम (i = 0; i < CSC_TEMPERATURE_MATRIX_SIZE; i++)
			adjust.temperature_matrix[i] =
				pipe_ctx->stream->gamut_remap_matrix.matrix[i];
	पूर्ण अन्यथा अगर (pipe_ctx->plane_state &&
		   pipe_ctx->plane_state->gamut_remap_matrix.enable_remap == true) अणु
		adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_SW;
		क्रम (i = 0; i < CSC_TEMPERATURE_MATRIX_SIZE; i++)
			adjust.temperature_matrix[i] =
				pipe_ctx->plane_state->gamut_remap_matrix.matrix[i];
	पूर्ण

	pipe_ctx->plane_res.dpp->funcs->dpp_set_gamut_remap(pipe_ctx->plane_res.dpp, &adjust);
पूर्ण


अटल bool dcn10_is_rear_mpo_fix_required(काष्ठा pipe_ctx *pipe_ctx, क्रमागत dc_color_space colorspace)
अणु
	अगर (pipe_ctx->plane_state && pipe_ctx->plane_state->layer_index > 0 && is_rgb_cspace(colorspace)) अणु
		अगर (pipe_ctx->top_pipe) अणु
			काष्ठा pipe_ctx *top = pipe_ctx->top_pipe;

			जबतक (top->top_pipe)
				top = top->top_pipe; // Traverse to top pipe_ctx
			अगर (top->plane_state && top->plane_state->layer_index == 0)
				वापस true; // Front MPO plane not hidden
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम dcn10_set_csc_adjusपंचांगent_rgb_mpo_fix(काष्ठा pipe_ctx *pipe_ctx, uपूर्णांक16_t *matrix)
अणु
	// Override rear plane RGB bias to fix MPO brightness
	uपूर्णांक16_t rgb_bias = matrix[3];

	matrix[3] = 0;
	matrix[7] = 0;
	matrix[11] = 0;
	pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjusपंचांगent(pipe_ctx->plane_res.dpp, matrix);
	matrix[3] = rgb_bias;
	matrix[7] = rgb_bias;
	matrix[11] = rgb_bias;
पूर्ण

व्योम dcn10_program_output_csc(काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत dc_color_space colorspace,
		uपूर्णांक16_t *matrix,
		पूर्णांक opp_id)
अणु
	अगर (pipe_ctx->stream->csc_color_matrix.enable_adjusपंचांगent == true) अणु
		अगर (pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjusपंचांगent != शून्य) अणु

			/* MPO is broken with RGB colorspaces when OCSC matrix
			 * brightness offset >= 0 on DCN1 due to OCSC beक्रमe MPC
			 * Blending adds offsets from front + rear to rear plane
			 *
			 * Fix is to set RGB bias to 0 on rear plane, top plane
			 * black value pixels add offset instead of rear + front
			 */

			पूर्णांक16_t rgb_bias = matrix[3];
			// matrix[3/7/11] are all the same offset value

			अगर (rgb_bias > 0 && dcn10_is_rear_mpo_fix_required(pipe_ctx, colorspace)) अणु
				dcn10_set_csc_adjusपंचांगent_rgb_mpo_fix(pipe_ctx, matrix);
			पूर्ण अन्यथा अणु
				pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjusपंचांगent(pipe_ctx->plane_res.dpp, matrix);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_शेष != शून्य)
			pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_शेष(pipe_ctx->plane_res.dpp, colorspace);
	पूर्ण
पूर्ण

व्योम dcn10_get_surface_visual_confirm_color(
		स्थिर काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा tg_color *color)
अणु
	uपूर्णांक32_t color_value = MAX_TG_COLOR_VALUE;

	चयन (pipe_ctx->plane_res.scl_data.क्रमmat) अणु
	हाल PIXEL_FORMAT_ARGB8888:
		/* set border color to red */
		color->color_r_cr = color_value;
		अवरोध;

	हाल PIXEL_FORMAT_ARGB2101010:
		/* set border color to blue */
		color->color_b_cb = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_420BPP8:
		/* set border color to green */
		color->color_g_y = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_420BPP10:
		/* set border color to yellow */
		color->color_g_y = color_value;
		color->color_r_cr = color_value;
		अवरोध;
	हाल PIXEL_FORMAT_FP16:
		/* set border color to white */
		color->color_r_cr = color_value;
		color->color_b_cb = color_value;
		color->color_g_y = color_value;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम dcn10_get_hdr_visual_confirm_color(
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा tg_color *color)
अणु
	uपूर्णांक32_t color_value = MAX_TG_COLOR_VALUE;

	// Determine the overscan color based on the top-most (desktop) plane's context
	काष्ठा pipe_ctx *top_pipe_ctx  = pipe_ctx;

	जबतक (top_pipe_ctx->top_pipe != शून्य)
		top_pipe_ctx = top_pipe_ctx->top_pipe;

	चयन (top_pipe_ctx->plane_res.scl_data.क्रमmat) अणु
	हाल PIXEL_FORMAT_ARGB2101010:
		अगर (top_pipe_ctx->stream->out_transfer_func->tf == TRANSFER_FUNCTION_PQ) अणु
			/* HDR10, ARGB2101010 - set border color to red */
			color->color_r_cr = color_value;
		पूर्ण अन्यथा अगर (top_pipe_ctx->stream->out_transfer_func->tf == TRANSFER_FUNCTION_GAMMA22) अणु
			/* FreeSync 2 ARGB2101010 - set border color to pink */
			color->color_r_cr = color_value;
			color->color_b_cb = color_value;
		पूर्ण
		अवरोध;
	हाल PIXEL_FORMAT_FP16:
		अगर (top_pipe_ctx->stream->out_transfer_func->tf == TRANSFER_FUNCTION_PQ) अणु
			/* HDR10, FP16 - set border color to blue */
			color->color_b_cb = color_value;
		पूर्ण अन्यथा अगर (top_pipe_ctx->stream->out_transfer_func->tf == TRANSFER_FUNCTION_GAMMA22) अणु
			/* FreeSync 2 HDR - set border color to green */
			color->color_g_y = color_value;
		पूर्ण
		अवरोध;
	शेष:
		/* SDR - set border color to Gray */
		color->color_r_cr = color_value/2;
		color->color_b_cb = color_value/2;
		color->color_g_y = color_value/2;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dcn10_update_dpp(काष्ठा dpp *dpp, काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा dc_bias_and_scale bns_params = अणु0पूर्ण;

	// program the input csc
	dpp->funcs->dpp_setup(dpp,
			plane_state->क्रमmat,
			EXPANSION_MODE_ZERO,
			plane_state->input_csc_color_matrix,
			plane_state->color_space,
			शून्य);

	//set scale and bias रेजिस्टरs
	build_prescale_params(&bns_params, plane_state);
	अगर (dpp->funcs->dpp_program_bias_and_scale)
		dpp->funcs->dpp_program_bias_and_scale(dpp, &bns_params);
पूर्ण

व्योम dcn10_update_mpcc(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा mpcc_blnd_cfg blnd_cfg = अणुअणु0पूर्णपूर्ण;
	bool per_pixel_alpha = pipe_ctx->plane_state->per_pixel_alpha && pipe_ctx->bottom_pipe;
	पूर्णांक mpcc_id;
	काष्ठा mpcc *new_mpcc;
	काष्ठा mpc *mpc = dc->res_pool->mpc;
	काष्ठा mpc_tree *mpc_tree_params = &(pipe_ctx->stream_res.opp->mpc_tree_params);

	अगर (dc->debug.visual_confirm == VISUAL_CONFIRM_HDR) अणु
		hws->funcs.get_hdr_visual_confirm_color(
				pipe_ctx, &blnd_cfg.black_color);
	पूर्ण अन्यथा अगर (dc->debug.visual_confirm == VISUAL_CONFIRM_SURFACE) अणु
		hws->funcs.get_surface_visual_confirm_color(
				pipe_ctx, &blnd_cfg.black_color);
	पूर्ण अन्यथा अणु
		color_space_to_black_color(
				dc, pipe_ctx->stream->output_color_space,
				&blnd_cfg.black_color);
	पूर्ण

	अगर (per_pixel_alpha)
		blnd_cfg.alpha_mode = MPCC_ALPHA_BLEND_MODE_PER_PIXEL_ALPHA;
	अन्यथा
		blnd_cfg.alpha_mode = MPCC_ALPHA_BLEND_MODE_GLOBAL_ALPHA;

	blnd_cfg.overlap_only = false;
	blnd_cfg.global_gain = 0xff;

	अगर (pipe_ctx->plane_state->global_alpha)
		blnd_cfg.global_alpha = pipe_ctx->plane_state->global_alpha_value;
	अन्यथा
		blnd_cfg.global_alpha = 0xff;

	/* DCN1.0 has output CM beक्रमe MPC which seems to screw with
	 * pre-multiplied alpha.
	 */
	blnd_cfg.pre_multiplied_alpha = is_rgb_cspace(
			pipe_ctx->stream->output_color_space)
					&& per_pixel_alpha;


	/*
	 * TODO: हटाओ hack
	 * Note: currently there is a bug in init_hw such that
	 * on resume from hibernate, BIOS sets up MPCC0, and
	 * we करो mpcc_हटाओ but the mpcc cannot go to idle
	 * after हटाओ. This cause us to pick mpcc1 here,
	 * which causes a pstate hang क्रम yet unknown reason.
	 */
	mpcc_id = hubp->inst;

	/* If there is no full update, करोn't need to touch MPC tree*/
	अगर (!pipe_ctx->plane_state->update_flags.bits.full_update) अणु
		mpc->funcs->update_blending(mpc, &blnd_cfg, mpcc_id);
		वापस;
	पूर्ण

	/* check अगर this MPCC is alपढ़ोy being used */
	new_mpcc = mpc->funcs->get_mpcc_क्रम_dpp(mpc_tree_params, mpcc_id);
	/* हटाओ MPCC अगर being used */
	अगर (new_mpcc != शून्य)
		mpc->funcs->हटाओ_mpcc(mpc, mpc_tree_params, new_mpcc);
	अन्यथा
		अगर (dc->debug.sanity_checks)
			mpc->funcs->निश्चित_mpcc_idle_beक्रमe_connect(
					dc->res_pool->mpc, mpcc_id);

	/* Call MPC to insert new plane */
	new_mpcc = mpc->funcs->insert_plane(dc->res_pool->mpc,
			mpc_tree_params,
			&blnd_cfg,
			शून्य,
			शून्य,
			hubp->inst,
			mpcc_id);

	ASSERT(new_mpcc != शून्य);

	hubp->opp_id = pipe_ctx->stream_res.opp->inst;
	hubp->mpcc_id = mpcc_id;
पूर्ण

अटल व्योम update_scaler(काष्ठा pipe_ctx *pipe_ctx)
अणु
	bool per_pixel_alpha =
			pipe_ctx->plane_state->per_pixel_alpha && pipe_ctx->bottom_pipe;

	pipe_ctx->plane_res.scl_data.lb_params.alpha_en = per_pixel_alpha;
	pipe_ctx->plane_res.scl_data.lb_params.depth = LB_PIXEL_DEPTH_30BPP;
	/* scaler configuration */
	pipe_ctx->plane_res.dpp->funcs->dpp_set_scaler(
			pipe_ctx->plane_res.dpp, &pipe_ctx->plane_res.scl_data);
पूर्ण

अटल व्योम dcn10_update_dchubp_dpp(
	काष्ठा dc *dc,
	काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा dpp *dpp = pipe_ctx->plane_res.dpp;
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	काष्ठा plane_size size = plane_state->plane_size;
	अचिन्हित पूर्णांक compat_level = 0;
	bool should_भागided_by_2 = false;

	/* depends on DML calculation, DPP घड़ी value may change dynamically */
	/* If request max dpp clk is lower than current dispclk, no need to
	 * भागided by 2
	 */
	अगर (plane_state->update_flags.bits.full_update) अणु

		/* new calculated dispclk, dppclk are stored in
		 * context->bw_ctx.bw.dcn.clk.dispclk_khz / dppclk_khz. current
		 * dispclk, dppclk are from dc->clk_mgr->clks.dispclk_khz.
		 * dcn_validate_bandwidth compute new dispclk, dppclk.
		 * dispclk will put in use after optimize_bandwidth when
		 * ramp_up_dispclk_with_dpp is called.
		 * there are two places क्रम dppclk be put in use. One location
		 * is the same as the location as dispclk. Another is within
		 * update_dchubp_dpp which happens between pre_bandwidth and
		 * optimize_bandwidth.
		 * dppclk updated within update_dchubp_dpp will cause new
		 * घड़ी values of dispclk and dppclk not be in use at the same
		 * समय. when घड़ीs are decreased, this may cause dppclk is
		 * lower than previous configuration and let pipe stuck.
		 * क्रम example, eDP + बाह्यal dp,  change resolution of DP from
		 * 1920x1080x144hz to 1280x960x60hz.
		 * beक्रमe change: dispclk = 337889 dppclk = 337889
		 * change mode, dcn_validate_bandwidth calculate
		 *                dispclk = 143122 dppclk = 143122
		 * update_dchubp_dpp be executed beक्रमe dispclk be updated,
		 * dispclk = 337889, but dppclk use new value dispclk /2 =
		 * 168944. this will cause pipe pstate warning issue.
		 * solution: between pre_bandwidth and optimize_bandwidth, जबतक
		 * dispclk is going to be decreased, keep dppclk = dispclk
		 **/
		अगर (context->bw_ctx.bw.dcn.clk.dispclk_khz <
				dc->clk_mgr->clks.dispclk_khz)
			should_भागided_by_2 = false;
		अन्यथा
			should_भागided_by_2 =
					context->bw_ctx.bw.dcn.clk.dppclk_khz <=
					dc->clk_mgr->clks.dispclk_khz / 2;

		dpp->funcs->dpp_dppclk_control(
				dpp,
				should_भागided_by_2,
				true);

		अगर (dc->res_pool->dccg)
			dc->res_pool->dccg->funcs->update_dpp_dto(
					dc->res_pool->dccg,
					dpp->inst,
					pipe_ctx->plane_res.bw.dppclk_khz);
		अन्यथा
			dc->clk_mgr->clks.dppclk_khz = should_भागided_by_2 ?
						dc->clk_mgr->clks.dispclk_khz / 2 :
							dc->clk_mgr->clks.dispclk_khz;
	पूर्ण

	/* TODO: Need input parameter to tell current DCHUB pipe tie to which OTG
	 * VTG is within DCHUBBUB which is commond block share by each pipe HUBP.
	 * VTG is 1:1 mapping with OTG. Each pipe HUBP will select which VTG
	 */
	अगर (plane_state->update_flags.bits.full_update) अणु
		hubp->funcs->hubp_vtg_sel(hubp, pipe_ctx->stream_res.tg->inst);

		hubp->funcs->hubp_setup(
			hubp,
			&pipe_ctx->dlg_regs,
			&pipe_ctx->ttu_regs,
			&pipe_ctx->rq_regs,
			&pipe_ctx->pipe_dlg_param);
		hubp->funcs->hubp_setup_पूर्णांकerdependent(
			hubp,
			&pipe_ctx->dlg_regs,
			&pipe_ctx->ttu_regs);
	पूर्ण

	size.surface_size = pipe_ctx->plane_res.scl_data.viewport;

	अगर (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.bpp_change)
		dcn10_update_dpp(dpp, plane_state);

	अगर (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.per_pixel_alpha_change ||
		plane_state->update_flags.bits.global_alpha_change)
		hws->funcs.update_mpcc(dc, pipe_ctx);

	अगर (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.per_pixel_alpha_change ||
		plane_state->update_flags.bits.global_alpha_change ||
		plane_state->update_flags.bits.scaling_change ||
		plane_state->update_flags.bits.position_change) अणु
		update_scaler(pipe_ctx);
	पूर्ण

	अगर (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.scaling_change ||
		plane_state->update_flags.bits.position_change) अणु
		hubp->funcs->mem_program_viewport(
			hubp,
			&pipe_ctx->plane_res.scl_data.viewport,
			&pipe_ctx->plane_res.scl_data.viewport_c);
	पूर्ण

	अगर (pipe_ctx->stream->cursor_attributes.address.quad_part != 0) अणु
		dc->hwss.set_cursor_position(pipe_ctx);
		dc->hwss.set_cursor_attribute(pipe_ctx);

		अगर (dc->hwss.set_cursor_sdr_white_level)
			dc->hwss.set_cursor_sdr_white_level(pipe_ctx);
	पूर्ण

	अगर (plane_state->update_flags.bits.full_update) अणु
		/*gamut remap*/
		dc->hwss.program_gamut_remap(pipe_ctx);

		dc->hwss.program_output_csc(dc,
				pipe_ctx,
				pipe_ctx->stream->output_color_space,
				pipe_ctx->stream->csc_color_matrix.matrix,
				pipe_ctx->stream_res.opp->inst);
	पूर्ण

	अगर (plane_state->update_flags.bits.full_update ||
		plane_state->update_flags.bits.pixel_क्रमmat_change ||
		plane_state->update_flags.bits.horizontal_mirror_change ||
		plane_state->update_flags.bits.rotation_change ||
		plane_state->update_flags.bits.swizzle_change ||
		plane_state->update_flags.bits.dcc_change ||
		plane_state->update_flags.bits.bpp_change ||
		plane_state->update_flags.bits.scaling_change ||
		plane_state->update_flags.bits.plane_size_change) अणु
		hubp->funcs->hubp_program_surface_config(
			hubp,
			plane_state->क्रमmat,
			&plane_state->tiling_info,
			&size,
			plane_state->rotation,
			&plane_state->dcc,
			plane_state->horizontal_mirror,
			compat_level);
	पूर्ण

	hubp->घातer_gated = false;

	hws->funcs.update_plane_addr(dc, pipe_ctx);

	अगर (is_pipe_tree_visible(pipe_ctx))
		hubp->funcs->set_blank(hubp, false);
पूर्ण

व्योम dcn10_blank_pixel_data(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		bool blank)
अणु
	क्रमागत dc_color_space color_space;
	काष्ठा tg_color black_color = अणु0पूर्ण;
	काष्ठा stream_resource *stream_res = &pipe_ctx->stream_res;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;

	/* program otg blank color */
	color_space = stream->output_color_space;
	color_space_to_black_color(dc, color_space, &black_color);

	/*
	 * The way 420 is packed, 2 channels carry Y component, 1 channel
	 * alternate between Cb and Cr, so both channels need the pixel
	 * value क्रम Y
	 */
	अगर (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
		black_color.color_r_cr = black_color.color_g_y;


	अगर (stream_res->tg->funcs->set_blank_color)
		stream_res->tg->funcs->set_blank_color(
				stream_res->tg,
				&black_color);

	अगर (!blank) अणु
		अगर (stream_res->tg->funcs->set_blank)
			stream_res->tg->funcs->set_blank(stream_res->tg, blank);
		अगर (stream_res->abm) अणु
			dc->hwss.set_pipe(pipe_ctx);
			stream_res->abm->funcs->set_abm_level(stream_res->abm, stream->abm_level);
		पूर्ण
	पूर्ण अन्यथा अगर (blank) अणु
		dc->hwss.set_abm_immediate_disable(pipe_ctx);
		अगर (stream_res->tg->funcs->set_blank) अणु
			stream_res->tg->funcs->रुको_क्रम_state(stream_res->tg, CRTC_STATE_VBLANK);
			stream_res->tg->funcs->set_blank(stream_res->tg, blank);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn10_set_hdr_multiplier(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा fixed31_32 multiplier = pipe_ctx->plane_state->hdr_mult;
	uपूर्णांक32_t hw_mult = 0x1f000; // 1.0 शेष multiplier
	काष्ठा custom_भग्न_क्रमmat fmt;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = true;


	अगर (!dc_fixpt_eq(multiplier, dc_fixpt_from_पूर्णांक(0))) // check != 0
		convert_to_custom_भग्न_क्रमmat(multiplier, &fmt, &hw_mult);

	pipe_ctx->plane_res.dpp->funcs->dpp_set_hdr_multiplier(
			pipe_ctx->plane_res.dpp, hw_mult);
पूर्ण

व्योम dcn10_program_pipe(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;

	अगर (pipe_ctx->plane_state->update_flags.bits.full_update)
		dcn10_enable_plane(dc, pipe_ctx, context);

	dcn10_update_dchubp_dpp(dc, pipe_ctx, context);

	hws->funcs.set_hdr_multiplier(pipe_ctx);

	अगर (pipe_ctx->plane_state->update_flags.bits.full_update ||
			pipe_ctx->plane_state->update_flags.bits.in_transfer_func_change ||
			pipe_ctx->plane_state->update_flags.bits.gamma_change)
		hws->funcs.set_input_transfer_func(dc, pipe_ctx, pipe_ctx->plane_state);

	/* dcn10_translate_regamma_to_hw_क्रमmat takes 750us to finish
	 * only करो gamma programming क्रम full update.
	 * TODO: This can be further optimized/cleaned up
	 * Always call this क्रम now since it करोes स_भेद inside beक्रमe
	 * करोing heavy calculation and programming
	 */
	अगर (pipe_ctx->plane_state->update_flags.bits.full_update)
		hws->funcs.set_output_transfer_func(dc, pipe_ctx, pipe_ctx->stream);
पूर्ण

अटल व्योम dcn10_program_all_pipe_in_tree(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;

	अगर (pipe_ctx->top_pipe == शून्य) अणु
		bool blank = !is_pipe_tree_visible(pipe_ctx);

		pipe_ctx->stream_res.tg->funcs->program_global_sync(
				pipe_ctx->stream_res.tg,
				pipe_ctx->pipe_dlg_param.vपढ़ोy_offset,
				pipe_ctx->pipe_dlg_param.vstartup_start,
				pipe_ctx->pipe_dlg_param.vupdate_offset,
				pipe_ctx->pipe_dlg_param.vupdate_width);

		pipe_ctx->stream_res.tg->funcs->set_vtg_params(
				pipe_ctx->stream_res.tg, &pipe_ctx->stream->timing, true);

		अगर (hws->funcs.setup_vupdate_पूर्णांकerrupt)
			hws->funcs.setup_vupdate_पूर्णांकerrupt(dc, pipe_ctx);

		hws->funcs.blank_pixel_data(dc, pipe_ctx, blank);
	पूर्ण

	अगर (pipe_ctx->plane_state != शून्य)
		hws->funcs.program_pipe(dc, pipe_ctx, context);

	अगर (pipe_ctx->bottom_pipe != शून्य && pipe_ctx->bottom_pipe != pipe_ctx)
		dcn10_program_all_pipe_in_tree(dc, pipe_ctx->bottom_pipe, context);
पूर्ण

अटल काष्ठा pipe_ctx *dcn10_find_top_pipe_क्रम_stream(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		स्थिर काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *old_pipe_ctx =
				&dc->current_state->res_ctx.pipe_ctx[i];

		अगर (!pipe_ctx->plane_state && !old_pipe_ctx->plane_state)
			जारी;

		अगर (pipe_ctx->stream != stream)
			जारी;

		अगर (!pipe_ctx->top_pipe && !pipe_ctx->prev_odm_pipe)
			वापस pipe_ctx;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम dcn10_रुको_क्रम_pending_cleared(काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
		काष्ठा pipe_ctx *pipe_ctx;
		काष्ठा timing_generator *tg;
		पूर्णांक i;

		क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
			pipe_ctx = &context->res_ctx.pipe_ctx[i];
			tg = pipe_ctx->stream_res.tg;

			/*
			 * Only रुको क्रम top pipe's tg penindg bit
			 * Also skip अगर pipe is disabled.
			 */
			अगर (pipe_ctx->top_pipe ||
			    !pipe_ctx->stream || !pipe_ctx->plane_state ||
			    !tg->funcs->is_tg_enabled(tg))
				जारी;

			/*
			 * Wait क्रम VBLANK then VACTIVE to ensure we get VUPDATE.
			 * For some reason रुकोing क्रम OTG_UPDATE_PENDING cleared
			 * seems to not trigger the update right away, and अगर we
			 * lock again beक्रमe VUPDATE then we करोn't get a separated
			 * operation.
			 */
			pipe_ctx->stream_res.tg->funcs->रुको_क्रम_state(pipe_ctx->stream_res.tg, CRTC_STATE_VBLANK);
			pipe_ctx->stream_res.tg->funcs->रुको_क्रम_state(pipe_ctx->stream_res.tg, CRTC_STATE_VACTIVE);
		पूर्ण
पूर्ण

व्योम dcn10_apply_ctx_क्रम_surface(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_stream_state *stream,
		पूर्णांक num_planes,
		काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	पूर्णांक i;
	काष्ठा timing_generator *tg;
	uपूर्णांक32_t underflow_check_delay_us;
	bool पूर्णांकerdependent_update = false;
	काष्ठा pipe_ctx *top_pipe_to_program =
			dcn10_find_top_pipe_क्रम_stream(dc, context, stream);
	DC_LOGGER_INIT(dc->ctx->logger);

	// Clear pipe_ctx flag
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		pipe_ctx->update_flags.raw = 0;
	पूर्ण

	अगर (!top_pipe_to_program)
		वापस;

	tg = top_pipe_to_program->stream_res.tg;

	पूर्णांकerdependent_update = top_pipe_to_program->plane_state &&
		top_pipe_to_program->plane_state->update_flags.bits.full_update;

	underflow_check_delay_us = dc->debug.underflow_निश्चित_delay_us;

	अगर (underflow_check_delay_us != 0xFFFFFFFF && hws->funcs.did_underflow_occur)
		ASSERT(hws->funcs.did_underflow_occur(dc, top_pipe_to_program));

	अगर (underflow_check_delay_us != 0xFFFFFFFF)
		udelay(underflow_check_delay_us);

	अगर (underflow_check_delay_us != 0xFFFFFFFF && hws->funcs.did_underflow_occur)
		ASSERT(hws->funcs.did_underflow_occur(dc, top_pipe_to_program));

	अगर (num_planes == 0) अणु
		/* OTG blank beक्रमe हटाओ all front end */
		hws->funcs.blank_pixel_data(dc, top_pipe_to_program, true);
	पूर्ण

	/* Disconnect unused mpcc */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *old_pipe_ctx =
				&dc->current_state->res_ctx.pipe_ctx[i];

		अगर ((!pipe_ctx->plane_state ||
		     pipe_ctx->stream_res.tg != old_pipe_ctx->stream_res.tg) &&
		    old_pipe_ctx->plane_state &&
		    old_pipe_ctx->stream_res.tg == tg) अणु

			hws->funcs.plane_atomic_disconnect(dc, old_pipe_ctx);
			pipe_ctx->update_flags.bits.disable = 1;

			DC_LOG_DC("Reset mpcc for pipe %d\n",
					old_pipe_ctx->pipe_idx);
		पूर्ण
	पूर्ण

	अगर (num_planes > 0)
		dcn10_program_all_pipe_in_tree(dc, top_pipe_to_program, context);

	/* Program secondary blending tree and ग_लिखोback pipes */
	अगर ((stream->num_wb_info > 0) && (hws->funcs.program_all_ग_लिखोback_pipes_in_tree))
		hws->funcs.program_all_ग_लिखोback_pipes_in_tree(dc, stream, context);
	अगर (पूर्णांकerdependent_update)
		क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
			काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];
			/* Skip inactive pipes and ones alपढ़ोy updated */
			अगर (!pipe_ctx->stream || pipe_ctx->stream == stream ||
			    !pipe_ctx->plane_state || !tg->funcs->is_tg_enabled(tg))
				जारी;

			pipe_ctx->plane_res.hubp->funcs->hubp_setup_पूर्णांकerdependent(
				pipe_ctx->plane_res.hubp,
				&pipe_ctx->dlg_regs,
				&pipe_ctx->ttu_regs);
		पूर्ण
पूर्ण

व्योम dcn10_post_unlock_program_front_end(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	DC_LOGGER_INIT(dc->ctx->logger);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (!pipe_ctx->top_pipe &&
			!pipe_ctx->prev_odm_pipe &&
			pipe_ctx->stream) अणु
			काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;

			अगर (context->stream_status[i].plane_count == 0)
				false_optc_underflow_wa(dc, pipe_ctx->stream, tg);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (context->res_ctx.pipe_ctx[i].update_flags.bits.disable)
			dc->hwss.disable_plane(dc, &dc->current_state->res_ctx.pipe_ctx[i]);

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++)
		अगर (context->res_ctx.pipe_ctx[i].update_flags.bits.disable) अणु
			dc->hwss.optimize_bandwidth(dc, context);
			अवरोध;
		पूर्ण

	अगर (dc->hwseq->wa.DEGVIDCN10_254)
		hubbub1_wm_change_req_wa(dc->res_pool->hubbub);
पूर्ण

अटल व्योम dcn10_stereo_hw_frame_pack_wa(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	uपूर्णांक8_t i;

	क्रम (i = 0; i < context->stream_count; i++) अणु
		अगर (context->streams[i]->timing.timing_3d_क्रमmat
				== TIMING_3D_FORMAT_HW_FRAME_PACKING) अणु
			/*
			 * Disable stutter
			 */
			hubbub1_allow_self_refresh_control(dc->res_pool->hubbub, false);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn10_prepare_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubbub *hubbub = dc->res_pool->hubbub;

	अगर (dc->debug.sanity_checks)
		hws->funcs.verअगरy_allow_pstate_change_high(dc);

	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		अगर (context->stream_count == 0)
			context->bw_ctx.bw.dcn.clk.phyclk_khz = 0;

		dc->clk_mgr->funcs->update_घड़ीs(
				dc->clk_mgr,
				context,
				false);
	पूर्ण

	dc->wm_optimized_required = hubbub->funcs->program_watermarks(hubbub,
			&context->bw_ctx.bw.dcn.watermarks,
			dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000,
			true);
	dcn10_stereo_hw_frame_pack_wa(dc, context);

	अगर (dc->debug.pplib_wm_report_mode == WM_REPORT_OVERRIDE)
		dcn_bw_notअगरy_pplib_of_wm_ranges(dc);

	अगर (dc->debug.sanity_checks)
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
पूर्ण

व्योम dcn10_optimize_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा hubbub *hubbub = dc->res_pool->hubbub;

	अगर (dc->debug.sanity_checks)
		hws->funcs.verअगरy_allow_pstate_change_high(dc);

	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		अगर (context->stream_count == 0)
			context->bw_ctx.bw.dcn.clk.phyclk_khz = 0;

		dc->clk_mgr->funcs->update_घड़ीs(
				dc->clk_mgr,
				context,
				true);
	पूर्ण

	hubbub->funcs->program_watermarks(hubbub,
			&context->bw_ctx.bw.dcn.watermarks,
			dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000,
			true);

	dcn10_stereo_hw_frame_pack_wa(dc, context);

	अगर (dc->debug.pplib_wm_report_mode == WM_REPORT_OVERRIDE)
		dcn_bw_notअगरy_pplib_of_wm_ranges(dc);

	अगर (dc->debug.sanity_checks)
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
पूर्ण

व्योम dcn10_set_drr(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes, काष्ठा dc_crtc_timing_adjust adjust)
अणु
	पूर्णांक i = 0;
	काष्ठा drr_params params = अणु0पूर्ण;
	// DRR set trigger event mapped to OTG_TRIG_A (bit 11) क्रम manual control flow
	अचिन्हित पूर्णांक event_triggers = 0x800;
	// Note DRR trigger events are generated regardless of whether num frames met.
	अचिन्हित पूर्णांक num_frames = 2;

	params.vertical_total_max = adjust.v_total_max;
	params.vertical_total_min = adjust.v_total_min;
	params.vertical_total_mid = adjust.v_total_mid;
	params.vertical_total_mid_frame_num = adjust.v_total_mid_frame_num;
	/* TODO: If multiple pipes are to be supported, you need
	 * some GSL stuff. Static screen triggers may be programmed dअगरferently
	 * as well.
	 */
	क्रम (i = 0; i < num_pipes; i++) अणु
		pipe_ctx[i]->stream_res.tg->funcs->set_drr(
			pipe_ctx[i]->stream_res.tg, &params);
		अगर (adjust.v_total_max != 0 && adjust.v_total_min != 0)
			pipe_ctx[i]->stream_res.tg->funcs->set_अटल_screen_control(
					pipe_ctx[i]->stream_res.tg,
					event_triggers, num_frames);
	पूर्ण
पूर्ण

व्योम dcn10_get_position(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes,
		काष्ठा crtc_position *position)
अणु
	पूर्णांक i = 0;

	/* TODO: handle pipes > 1
	 */
	क्रम (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stream_res.tg->funcs->get_position(pipe_ctx[i]->stream_res.tg, position);
पूर्ण

व्योम dcn10_set_अटल_screen_control(काष्ठा pipe_ctx **pipe_ctx,
		पूर्णांक num_pipes, स्थिर काष्ठा dc_अटल_screen_params *params)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक triggers = 0;

	अगर (params->triggers.surface_update)
		triggers |= 0x80;
	अगर (params->triggers.cursor_update)
		triggers |= 0x2;
	अगर (params->triggers.क्रमce_trigger)
		triggers |= 0x1;

	क्रम (i = 0; i < num_pipes; i++)
		pipe_ctx[i]->stream_res.tg->funcs->
			set_अटल_screen_control(pipe_ctx[i]->stream_res.tg,
					triggers, params->num_frames);
पूर्ण

अटल व्योम dcn10_config_stereo_parameters(
		काष्ठा dc_stream_state *stream, काष्ठा crtc_stereo_flags *flags)
अणु
	क्रमागत view_3d_क्रमmat view_क्रमmat = stream->view_क्रमmat;
	क्रमागत dc_timing_3d_क्रमmat timing_3d_क्रमmat =\
			stream->timing.timing_3d_क्रमmat;
	bool non_stereo_timing = false;

	अगर (timing_3d_क्रमmat == TIMING_3D_FORMAT_NONE ||
		timing_3d_क्रमmat == TIMING_3D_FORMAT_SIDE_BY_SIDE ||
		timing_3d_क्रमmat == TIMING_3D_FORMAT_TOP_AND_BOTTOM)
		non_stereo_timing = true;

	अगर (non_stereo_timing == false &&
		view_क्रमmat == VIEW_3D_FORMAT_FRAME_SEQUENTIAL) अणु

		flags->PROGRAM_STEREO         = 1;
		flags->PROGRAM_POLARITY       = 1;
		अगर (timing_3d_क्रमmat == TIMING_3D_FORMAT_INBAND_FA ||
			timing_3d_क्रमmat == TIMING_3D_FORMAT_DP_HDMI_INBAND_FA ||
			timing_3d_क्रमmat == TIMING_3D_FORMAT_SIDEBAND_FA) अणु
			क्रमागत display_करोngle_type करोngle = \
					stream->link->ddc->करोngle_type;
			अगर (करोngle == DISPLAY_DONGLE_DP_VGA_CONVERTER ||
				करोngle == DISPLAY_DONGLE_DP_DVI_CONVERTER ||
				करोngle == DISPLAY_DONGLE_DP_HDMI_CONVERTER)
				flags->DISABLE_STEREO_DP_SYNC = 1;
		पूर्ण
		flags->RIGHT_EYE_POLARITY =\
				stream->timing.flags.RIGHT_EYE_3D_POLARITY;
		अगर (timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
			flags->FRAME_PACKED = 1;
	पूर्ण

	वापस;
पूर्ण

व्योम dcn10_setup_stereo(काष्ठा pipe_ctx *pipe_ctx, काष्ठा dc *dc)
अणु
	काष्ठा crtc_stereo_flags flags = अणु 0 पूर्ण;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;

	dcn10_config_stereo_parameters(stream, &flags);

	अगर (stream->timing.timing_3d_क्रमmat == TIMING_3D_FORMAT_SIDEBAND_FA) अणु
		अगर (!dc_set_generic_gpio_क्रम_stereo(true, dc->ctx->gpio_service))
			dc_set_generic_gpio_क्रम_stereo(false, dc->ctx->gpio_service);
	पूर्ण अन्यथा अणु
		dc_set_generic_gpio_क्रम_stereo(false, dc->ctx->gpio_service);
	पूर्ण

	pipe_ctx->stream_res.opp->funcs->opp_program_stereo(
		pipe_ctx->stream_res.opp,
		flags.PROGRAM_STEREO == 1,
		&stream->timing);

	pipe_ctx->stream_res.tg->funcs->program_stereo(
		pipe_ctx->stream_res.tg,
		&stream->timing,
		&flags);

	वापस;
पूर्ण

अटल काष्ठा hubp *get_hubp_by_inst(काष्ठा resource_pool *res_pool, पूर्णांक mpcc_inst)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < res_pool->pipe_count; i++) अणु
		अगर (res_pool->hubps[i]->inst == mpcc_inst)
			वापस res_pool->hubps[i];
	पूर्ण
	ASSERT(false);
	वापस शून्य;
पूर्ण

व्योम dcn10_रुको_क्रम_mpcc_disconnect(
		काष्ठा dc *dc,
		काष्ठा resource_pool *res_pool,
		काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	पूर्णांक mpcc_inst;

	अगर (dc->debug.sanity_checks) अणु
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
	पूर्ण

	अगर (!pipe_ctx->stream_res.opp)
		वापस;

	क्रम (mpcc_inst = 0; mpcc_inst < MAX_PIPES; mpcc_inst++) अणु
		अगर (pipe_ctx->stream_res.opp->mpcc_disconnect_pending[mpcc_inst]) अणु
			काष्ठा hubp *hubp = get_hubp_by_inst(res_pool, mpcc_inst);

			res_pool->mpc->funcs->रुको_क्रम_idle(res_pool->mpc, mpcc_inst);
			pipe_ctx->stream_res.opp->mpcc_disconnect_pending[mpcc_inst] = false;
			hubp->funcs->set_blank(hubp, true);
		पूर्ण
	पूर्ण

	अगर (dc->debug.sanity_checks) अणु
		hws->funcs.verअगरy_allow_pstate_change_high(dc);
	पूर्ण

पूर्ण

bool dcn10_dummy_display_घातer_gating(
	काष्ठा dc *dc,
	uपूर्णांक8_t controller_id,
	काष्ठा dc_bios *dcb,
	क्रमागत pipe_gating_control घातer_gating)
अणु
	वापस true;
पूर्ण

व्योम dcn10_update_pending_status(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_plane_state *plane_state = pipe_ctx->plane_state;
	काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;
	bool flip_pending;
	काष्ठा dc *dc = plane_state->ctx->dc;

	अगर (plane_state == शून्य)
		वापस;

	flip_pending = pipe_ctx->plane_res.hubp->funcs->hubp_is_flip_pending(
					pipe_ctx->plane_res.hubp);

	plane_state->status.is_flip_pending = plane_state->status.is_flip_pending || flip_pending;

	अगर (!flip_pending)
		plane_state->status.current_address = plane_state->status.requested_address;

	अगर (plane_state->status.current_address.type == PLN_ADDR_TYPE_GRPH_STEREO &&
			tg->funcs->is_stereo_left_eye) अणु
		plane_state->status.is_right_eye =
				!tg->funcs->is_stereo_left_eye(pipe_ctx->stream_res.tg);
	पूर्ण

	अगर (dc->hwseq->wa_state.disallow_self_refresh_during_multi_plane_transition_applied) अणु
		काष्ठा dce_hwseq *hwseq = dc->hwseq;
		काष्ठा timing_generator *tg = dc->res_pool->timing_generators[0];
		अचिन्हित पूर्णांक cur_frame = tg->funcs->get_frame_count(tg);

		अगर (cur_frame != hwseq->wa_state.disallow_self_refresh_during_multi_plane_transition_applied_on_frame) अणु
			काष्ठा hubbub *hubbub = dc->res_pool->hubbub;

			hubbub->funcs->allow_self_refresh_control(hubbub, !dc->debug.disable_stutter);
			hwseq->wa_state.disallow_self_refresh_during_multi_plane_transition_applied = false;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn10_update_dchub(काष्ठा dce_hwseq *hws, काष्ठा dchub_init_data *dh_data)
अणु
	काष्ठा hubbub *hubbub = hws->ctx->dc->res_pool->hubbub;

	/* In DCN, this programming sequence is owned by the hubbub */
	hubbub->funcs->update_dchub(hubbub, dh_data);
पूर्ण

अटल bool dcn10_can_pipe_disable_cursor(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा pipe_ctx *test_pipe;
	स्थिर काष्ठा rect *r1 = &pipe_ctx->plane_res.scl_data.recout, *r2;
	पूर्णांक r1_r = r1->x + r1->width, r1_b = r1->y + r1->height, r2_r, r2_b;

	/**
	 * Disable the cursor अगर there's another pipe above this with a
	 * plane that contains this pipe's viewport to prevent द्विगुन cursor
	 * and incorrect scaling artअगरacts.
	 */
	क्रम (test_pipe = pipe_ctx->top_pipe; test_pipe;
	     test_pipe = test_pipe->top_pipe) अणु
		अगर (!test_pipe->plane_state->visible)
			जारी;

		r2 = &test_pipe->plane_res.scl_data.recout;
		r2_r = r2->x + r2->width;
		r2_b = r2->y + r2->height;

		अगर (r1->x >= r2->x && r1->y >= r2->y && r1_r <= r2_r && r1_b <= r2_b)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम dcn10_set_cursor_position(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_cursor_position pos_cpy = pipe_ctx->stream->cursor_position;
	काष्ठा hubp *hubp = pipe_ctx->plane_res.hubp;
	काष्ठा dpp *dpp = pipe_ctx->plane_res.dpp;
	काष्ठा dc_cursor_mi_param param = अणु
		.pixel_clk_khz = pipe_ctx->stream->timing.pix_clk_100hz / 10,
		.ref_clk_khz = pipe_ctx->stream->ctx->dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz,
		.viewport = pipe_ctx->plane_res.scl_data.viewport,
		.h_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.horz,
		.v_scale_ratio = pipe_ctx->plane_res.scl_data.ratios.vert,
		.rotation = pipe_ctx->plane_state->rotation,
		.mirror = pipe_ctx->plane_state->horizontal_mirror
	पूर्ण;
	bool pipe_split_on = (pipe_ctx->top_pipe != शून्य) ||
		(pipe_ctx->bottom_pipe != शून्य);
	bool odm_combine_on = (pipe_ctx->next_odm_pipe != शून्य) ||
		(pipe_ctx->prev_odm_pipe != शून्य);

	पूर्णांक x_plane = pipe_ctx->plane_state->dst_rect.x;
	पूर्णांक y_plane = pipe_ctx->plane_state->dst_rect.y;
	पूर्णांक x_pos = pos_cpy.x;
	पूर्णांक y_pos = pos_cpy.y;

	/**
	 * DC cursor is stream space, HW cursor is plane space and drawn
	 * as part of the framebuffer.
	 *
	 * Cursor position can't be negative, but hotspot can be used to
	 * shअगरt cursor out of the plane bounds. Hotspot must be smaller
	 * than the cursor size.
	 */

	/**
	 * Translate cursor from stream space to plane space.
	 *
	 * If the cursor is scaled then we need to scale the position
	 * to be in the approximately correct place. We can't करो anything
	 * about the actual size being incorrect, that's a limitation of
	 * the hardware.
	 */
	x_pos = (x_pos - x_plane) * pipe_ctx->plane_state->src_rect.width /
			pipe_ctx->plane_state->dst_rect.width;
	y_pos = (y_pos - y_plane) * pipe_ctx->plane_state->src_rect.height /
			pipe_ctx->plane_state->dst_rect.height;

	/**
	 * If the cursor's source viewport is clipped then we need to
	 * translate the cursor to appear in the correct position on
	 * the screen.
	 *
	 * This translation isn't affected by scaling so it needs to be
	 * करोne *after* we adjust the position क्रम the scale factor.
	 *
	 * This is only करोne by opt-in क्रम now since there are still
	 * some useहालs like tiled display that might enable the
	 * cursor on both streams जबतक expecting dc to clip it.
	 */
	अगर (pos_cpy.translate_by_source) अणु
		x_pos += pipe_ctx->plane_state->src_rect.x;
		y_pos += pipe_ctx->plane_state->src_rect.y;
	पूर्ण

	/**
	 * If the position is negative then we need to add to the hotspot
	 * to shअगरt the cursor outside the plane.
	 */

	अगर (x_pos < 0) अणु
		pos_cpy.x_hotspot -= x_pos;
		x_pos = 0;
	पूर्ण

	अगर (y_pos < 0) अणु
		pos_cpy.y_hotspot -= y_pos;
		y_pos = 0;
	पूर्ण

	pos_cpy.x = (uपूर्णांक32_t)x_pos;
	pos_cpy.y = (uपूर्णांक32_t)y_pos;

	अगर (pipe_ctx->plane_state->address.type
			== PLN_ADDR_TYPE_VIDEO_PROGRESSIVE)
		pos_cpy.enable = false;

	अगर (pos_cpy.enable && dcn10_can_pipe_disable_cursor(pipe_ctx))
		pos_cpy.enable = false;

	// Swap axis and mirror horizontally
	अगर (param.rotation == ROTATION_ANGLE_90) अणु
		uपूर्णांक32_t temp_x = pos_cpy.x;

		pos_cpy.x = pipe_ctx->plane_res.scl_data.viewport.width -
				(pos_cpy.y - pipe_ctx->plane_res.scl_data.viewport.x) + pipe_ctx->plane_res.scl_data.viewport.x;
		pos_cpy.y = temp_x;
	पूर्ण
	// Swap axis and mirror vertically
	अन्यथा अगर (param.rotation == ROTATION_ANGLE_270) अणु
		uपूर्णांक32_t temp_y = pos_cpy.y;
		पूर्णांक viewport_height =
			pipe_ctx->plane_res.scl_data.viewport.height;
		पूर्णांक viewport_y =
			pipe_ctx->plane_res.scl_data.viewport.y;

		/**
		 * Display groups that are 1xnY, have pos_cpy.x > 2 * viewport.height
		 * For pipe split हालs:
		 * - apply offset of viewport.y to normalize pos_cpy.x
		 * - calculate the pos_cpy.y as beक्रमe
		 * - shअगरt pos_cpy.y back by same offset to get final value
		 * - since we iterate through both pipes, use the lower
		 *   viewport.y क्रम offset
		 * For non pipe split हालs, use the same calculation क्रम
		 *  pos_cpy.y as the 180 degree rotation हाल below,
		 *  but use pos_cpy.x as our input because we are rotating
		 *  270 degrees
		 */
		अगर (pipe_split_on || odm_combine_on) अणु
			पूर्णांक pos_cpy_x_offset;
			पूर्णांक other_pipe_viewport_y;

			अगर (pipe_split_on) अणु
				अगर (pipe_ctx->bottom_pipe) अणु
					other_pipe_viewport_y =
						pipe_ctx->bottom_pipe->plane_res.scl_data.viewport.y;
				पूर्ण अन्यथा अणु
					other_pipe_viewport_y =
						pipe_ctx->top_pipe->plane_res.scl_data.viewport.y;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (pipe_ctx->next_odm_pipe) अणु
					other_pipe_viewport_y =
						pipe_ctx->next_odm_pipe->plane_res.scl_data.viewport.y;
				पूर्ण अन्यथा अणु
					other_pipe_viewport_y =
						pipe_ctx->prev_odm_pipe->plane_res.scl_data.viewport.y;
				पूर्ण
			पूर्ण
			pos_cpy_x_offset = (viewport_y > other_pipe_viewport_y) ?
				other_pipe_viewport_y : viewport_y;
			pos_cpy.x -= pos_cpy_x_offset;
			अगर (pos_cpy.x > viewport_height) अणु
				pos_cpy.x = pos_cpy.x - viewport_height;
				pos_cpy.y = viewport_height - pos_cpy.x;
			पूर्ण अन्यथा अणु
				pos_cpy.y = 2 * viewport_height - pos_cpy.x;
			पूर्ण
			pos_cpy.y += pos_cpy_x_offset;
		पूर्ण अन्यथा अणु
			pos_cpy.y = (2 * viewport_y) + viewport_height - pos_cpy.x;
		पूर्ण
		pos_cpy.x = temp_y;
	पूर्ण
	// Mirror horizontally and vertically
	अन्यथा अगर (param.rotation == ROTATION_ANGLE_180) अणु
		पूर्णांक viewport_width =
			pipe_ctx->plane_res.scl_data.viewport.width;
		पूर्णांक viewport_x =
			pipe_ctx->plane_res.scl_data.viewport.x;

		अगर (pipe_split_on || odm_combine_on) अणु
			अगर (pos_cpy.x >= viewport_width + viewport_x) अणु
				pos_cpy.x = 2 * viewport_width
						- pos_cpy.x + 2 * viewport_x;
			पूर्ण अन्यथा अणु
				uपूर्णांक32_t temp_x = pos_cpy.x;

				pos_cpy.x = 2 * viewport_x - pos_cpy.x;
				अगर (temp_x >= viewport_x +
					(पूर्णांक)hubp->curs_attr.width || pos_cpy.x
					<= (पूर्णांक)hubp->curs_attr.width +
					pipe_ctx->plane_state->src_rect.x) अणु
					pos_cpy.x = temp_x + viewport_width;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			pos_cpy.x = viewport_width - pos_cpy.x + 2 * viewport_x;
		पूर्ण

		/**
		 * Display groups that are 1xnY, have pos_cpy.y > viewport.height
		 * Calculation:
		 *   delta_from_bottom = viewport.y + viewport.height - pos_cpy.y
		 *   pos_cpy.y_new = viewport.y + delta_from_bottom
		 * Simplअगरy it as:
		 *   pos_cpy.y = viewport.y * 2 + viewport.height - pos_cpy.y
		 */
		pos_cpy.y = (2 * pipe_ctx->plane_res.scl_data.viewport.y) +
			pipe_ctx->plane_res.scl_data.viewport.height - pos_cpy.y;
	पूर्ण

	hubp->funcs->set_cursor_position(hubp, &pos_cpy, &param);
	dpp->funcs->set_cursor_position(dpp, &pos_cpy, &param, hubp->curs_attr.width, hubp->curs_attr.height);
पूर्ण

व्योम dcn10_set_cursor_attribute(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_cursor_attributes *attributes = &pipe_ctx->stream->cursor_attributes;

	pipe_ctx->plane_res.hubp->funcs->set_cursor_attributes(
			pipe_ctx->plane_res.hubp, attributes);
	pipe_ctx->plane_res.dpp->funcs->set_cursor_attributes(
		pipe_ctx->plane_res.dpp, attributes);
पूर्ण

व्योम dcn10_set_cursor_sdr_white_level(काष्ठा pipe_ctx *pipe_ctx)
अणु
	uपूर्णांक32_t sdr_white_level = pipe_ctx->stream->cursor_attributes.sdr_white_level;
	काष्ठा fixed31_32 multiplier;
	काष्ठा dpp_cursor_attributes opt_attr = अणु 0 पूर्ण;
	uपूर्णांक32_t hw_scale = 0x3c00; // 1.0 शेष multiplier
	काष्ठा custom_भग्न_क्रमmat fmt;

	अगर (!pipe_ctx->plane_res.dpp->funcs->set_optional_cursor_attributes)
		वापस;

	fmt.exponenta_bits = 5;
	fmt.mantissa_bits = 10;
	fmt.sign = true;

	अगर (sdr_white_level > 80) अणु
		multiplier = dc_fixpt_from_fraction(sdr_white_level, 80);
		convert_to_custom_भग्न_क्रमmat(multiplier, &fmt, &hw_scale);
	पूर्ण

	opt_attr.scale = hw_scale;
	opt_attr.bias = 0;

	pipe_ctx->plane_res.dpp->funcs->set_optional_cursor_attributes(
			pipe_ctx->plane_res.dpp, &opt_attr);
पूर्ण

/*
 * apply_front_porch_workaround  TODO FPGA still need?
 *
 * This is a workaround क्रम a bug that has existed since R5xx and has not been
 * fixed keep Front porch at minimum 2 क्रम Interlaced mode or 1 क्रम progressive.
 */
अटल व्योम apply_front_porch_workaround(
	काष्ठा dc_crtc_timing *timing)
अणु
	अगर (timing->flags.INTERLACE == 1) अणु
		अगर (timing->v_front_porch < 2)
			timing->v_front_porch = 2;
	पूर्ण अन्यथा अणु
		अगर (timing->v_front_porch < 1)
			timing->v_front_porch = 1;
	पूर्ण
पूर्ण

पूर्णांक dcn10_get_vupdate_offset_from_vsync(काष्ठा pipe_ctx *pipe_ctx)
अणु
	स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing = &pipe_ctx->stream->timing;
	काष्ठा dc_crtc_timing patched_crtc_timing;
	पूर्णांक vesa_sync_start;
	पूर्णांक asic_blank_end;
	पूर्णांक पूर्णांकerlace_factor;
	पूर्णांक vertical_line_start;

	patched_crtc_timing = *dc_crtc_timing;
	apply_front_porch_workaround(&patched_crtc_timing);

	पूर्णांकerlace_factor = patched_crtc_timing.flags.INTERLACE ? 2 : 1;

	vesa_sync_start = patched_crtc_timing.v_addressable +
			patched_crtc_timing.v_border_bottom +
			patched_crtc_timing.v_front_porch;

	asic_blank_end = (patched_crtc_timing.v_total -
			vesa_sync_start -
			patched_crtc_timing.v_border_top)
			* पूर्णांकerlace_factor;

	vertical_line_start = asic_blank_end -
			pipe_ctx->pipe_dlg_param.vstartup_start + 1;

	वापस vertical_line_start;
पूर्ण

व्योम dcn10_calc_vupdate_position(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		uपूर्णांक32_t *start_line,
		uपूर्णांक32_t *end_line)
अणु
	स्थिर काष्ठा dc_crtc_timing *dc_crtc_timing = &pipe_ctx->stream->timing;
	पूर्णांक vline_पूर्णांक_offset_from_vupdate =
			pipe_ctx->stream->periodic_पूर्णांकerrupt0.lines_offset;
	पूर्णांक vupdate_offset_from_vsync = dc->hwss.get_vupdate_offset_from_vsync(pipe_ctx);
	पूर्णांक start_position;

	अगर (vline_पूर्णांक_offset_from_vupdate > 0)
		vline_पूर्णांक_offset_from_vupdate--;
	अन्यथा अगर (vline_पूर्णांक_offset_from_vupdate < 0)
		vline_पूर्णांक_offset_from_vupdate++;

	start_position = vline_पूर्णांक_offset_from_vupdate + vupdate_offset_from_vsync;

	अगर (start_position >= 0)
		*start_line = start_position;
	अन्यथा
		*start_line = dc_crtc_timing->v_total + start_position - 1;

	*end_line = *start_line + 2;

	अगर (*end_line >= dc_crtc_timing->v_total)
		*end_line = 2;
पूर्ण

अटल व्योम dcn10_cal_vline_position(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत vline_select vline,
		uपूर्णांक32_t *start_line,
		uपूर्णांक32_t *end_line)
अणु
	क्रमागत vertical_पूर्णांकerrupt_ref_poपूर्णांक ref_poपूर्णांक = INVALID_POINT;

	अगर (vline == VLINE0)
		ref_poपूर्णांक = pipe_ctx->stream->periodic_पूर्णांकerrupt0.ref_poपूर्णांक;
	अन्यथा अगर (vline == VLINE1)
		ref_poपूर्णांक = pipe_ctx->stream->periodic_पूर्णांकerrupt1.ref_poपूर्णांक;

	चयन (ref_poपूर्णांक) अणु
	हाल START_V_UPDATE:
		dcn10_calc_vupdate_position(
				dc,
				pipe_ctx,
				start_line,
				end_line);
		अवरोध;
	हाल START_V_SYNC:
		// Suppose to करो nothing because vsync is 0;
		अवरोध;
	शेष:
		ASSERT(0);
		अवरोध;
	पूर्ण
पूर्ण

व्योम dcn10_setup_periodic_पूर्णांकerrupt(
		काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत vline_select vline)
अणु
	काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;

	अगर (vline == VLINE0) अणु
		uपूर्णांक32_t start_line = 0;
		uपूर्णांक32_t end_line = 0;

		dcn10_cal_vline_position(dc, pipe_ctx, vline, &start_line, &end_line);

		tg->funcs->setup_vertical_पूर्णांकerrupt0(tg, start_line, end_line);

	पूर्ण अन्यथा अगर (vline == VLINE1) अणु
		pipe_ctx->stream_res.tg->funcs->setup_vertical_पूर्णांकerrupt1(
				tg,
				pipe_ctx->stream->periodic_पूर्णांकerrupt1.lines_offset);
	पूर्ण
पूर्ण

व्योम dcn10_setup_vupdate_पूर्णांकerrupt(काष्ठा dc *dc, काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा timing_generator *tg = pipe_ctx->stream_res.tg;
	पूर्णांक start_line = dc->hwss.get_vupdate_offset_from_vsync(pipe_ctx);

	अगर (start_line < 0) अणु
		ASSERT(0);
		start_line = 0;
	पूर्ण

	अगर (tg->funcs->setup_vertical_पूर्णांकerrupt2)
		tg->funcs->setup_vertical_पूर्णांकerrupt2(tg, start_line);
पूर्ण

व्योम dcn10_unblank_stream(काष्ठा pipe_ctx *pipe_ctx,
		काष्ठा dc_link_settings *link_settings)
अणु
	काष्ठा encoder_unblank_param params = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा dc_link *link = stream->link;
	काष्ठा dce_hwseq *hws = link->dc->hwseq;

	/* only 3 items below are used by unblank */
	params.timing = pipe_ctx->stream->timing;

	params.link_settings.link_rate = link_settings->link_rate;

	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत)) अणु
		अगर (params.timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
			params.timing.pix_clk_100hz /= 2;
		pipe_ctx->stream_res.stream_enc->funcs->dp_unblank(pipe_ctx->stream_res.stream_enc, &params);
	पूर्ण

	अगर (link->local_sink && link->local_sink->sink_संकेत == SIGNAL_TYPE_EDP) अणु
		hws->funcs.edp_backlight_control(link, true);
	पूर्ण
पूर्ण

व्योम dcn10_send_immediate_sdp_message(काष्ठा pipe_ctx *pipe_ctx,
				स्थिर uपूर्णांक8_t *custom_sdp_message,
				अचिन्हित पूर्णांक sdp_message_size)
अणु
	अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत)) अणु
		pipe_ctx->stream_res.stream_enc->funcs->send_immediate_sdp_message(
				pipe_ctx->stream_res.stream_enc,
				custom_sdp_message,
				sdp_message_size);
	पूर्ण
पूर्ण
क्रमागत dc_status dcn10_set_घड़ी(काष्ठा dc *dc,
			क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
			uपूर्णांक32_t clk_khz,
			uपूर्णांक32_t stepping)
अणु
	काष्ठा dc_state *context = dc->current_state;
	काष्ठा dc_घड़ी_config घड़ी_cfg = अणु0पूर्ण;
	काष्ठा dc_घड़ीs *current_घड़ीs = &context->bw_ctx.bw.dcn.clk;

	अगर (dc->clk_mgr && dc->clk_mgr->funcs->get_घड़ी)
				dc->clk_mgr->funcs->get_घड़ी(dc->clk_mgr,
						context, घड़ी_प्रकारype, &घड़ी_cfg);

	अगर (!dc->clk_mgr->funcs->get_घड़ी)
		वापस DC_FAIL_UNSUPPORTED_1;

	अगर (clk_khz > घड़ी_cfg.max_घड़ी_khz)
		वापस DC_FAIL_CLK_EXCEED_MAX;

	अगर (clk_khz < घड़ी_cfg.min_घड़ी_khz)
		वापस DC_FAIL_CLK_BELOW_MIN;

	अगर (clk_khz < घड़ी_cfg.bw_requirequired_घड़ी_khz)
		वापस DC_FAIL_CLK_BELOW_CFG_REQUIRED;

	/*update पूर्णांकernal request घड़ी क्रम update घड़ी use*/
	अगर (घड़ी_प्रकारype == DC_CLOCK_TYPE_DISPCLK)
		current_घड़ीs->dispclk_khz = clk_khz;
	अन्यथा अगर (घड़ी_प्रकारype == DC_CLOCK_TYPE_DPPCLK)
		current_घड़ीs->dppclk_khz = clk_khz;
	अन्यथा
		वापस DC_ERROR_UNEXPECTED;

	अगर (dc->clk_mgr && dc->clk_mgr->funcs->update_घड़ीs)
				dc->clk_mgr->funcs->update_घड़ीs(dc->clk_mgr,
				context, true);
	वापस DC_OK;

पूर्ण

व्योम dcn10_get_घड़ी(काष्ठा dc *dc,
			क्रमागत dc_घड़ी_प्रकारype घड़ी_प्रकारype,
			काष्ठा dc_घड़ी_config *घड़ी_cfg)
अणु
	काष्ठा dc_state *context = dc->current_state;

	अगर (dc->clk_mgr && dc->clk_mgr->funcs->get_घड़ी)
				dc->clk_mgr->funcs->get_घड़ी(dc->clk_mgr, context, घड़ी_प्रकारype, घड़ी_cfg);

पूर्ण

व्योम dcn10_get_dcc_en_bits(काष्ठा dc *dc, पूर्णांक *dcc_en_bits)
अणु
	काष्ठा resource_pool *pool = dc->res_pool;
	पूर्णांक i;

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		काष्ठा hubp *hubp = pool->hubps[i];
		काष्ठा dcn_hubp_state *s = &(TO_DCN10_HUBP(hubp)->state);

		hubp->funcs->hubp_पढ़ो_state(hubp);

		अगर (!s->blank_en)
			dcc_en_bits[i] = s->dcc_en ? 1 : 0;
	पूर्ण
पूर्ण
