<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "dm_helpers.h"
#समावेश "core_types.h"
#समावेश "resource.h"
#समावेश "dcn30_hwseq.h"
#समावेश "dccg.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "dcn30_mpc.h"
#समावेश "dcn30_dpp.h"
#समावेश "dcn10/dcn10_cm_common.h"
#समावेश "dcn30_cm_common.h"
#समावेश "reg_helper.h"
#समावेश "abm.h"
#समावेश "clk_mgr.h"
#समावेश "hubp.h"
#समावेश "dchubbub.h"
#समावेश "timing_generator.h"
#समावेश "opp.h"
#समावेश "ipp.h"
#समावेश "mpc.h"
#समावेश "mcif_wb.h"
#समावेश "dc_dmub_srv.h"
#समावेश "link_hwss.h"
#समावेश "dpcd_defs.h"




#घोषणा DC_LOGGER_INIT(logger)

#घोषणा CTX \
	hws->ctx
#घोषणा REG(reg)\
	hws->regs->reg
#घोषणा DC_LOGGER \
		dc->ctx->logger


#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name

bool dcn30_set_blend_lut(
	काष्ठा pipe_ctx *pipe_ctx, स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा dpp *dpp_base = pipe_ctx->plane_res.dpp;
	bool result = true;
	काष्ठा pwl_params *blend_lut = शून्य;

	अगर (plane_state->blend_tf) अणु
		अगर (plane_state->blend_tf->type == TF_TYPE_HWPWL)
			blend_lut = &plane_state->blend_tf->pwl;
		अन्यथा अगर (plane_state->blend_tf->type == TF_TYPE_DISTRIBUTED_POINTS) अणु
			cm3_helper_translate_curve_to_hw_क्रमmat(
					plane_state->blend_tf, &dpp_base->regamma_params, false);
			blend_lut = &dpp_base->regamma_params;
		पूर्ण
	पूर्ण
	result = dpp_base->funcs->dpp_program_blnd_lut(dpp_base, blend_lut);

	वापस result;
पूर्ण

अटल bool dcn30_set_mpc_shaper_3dlut(
	काष्ठा pipe_ctx *pipe_ctx, स्थिर काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dpp *dpp_base = pipe_ctx->plane_res.dpp;
	पूर्णांक mpcc_id = pipe_ctx->plane_res.hubp->inst;
	काष्ठा mpc *mpc = pipe_ctx->stream_res.opp->ctx->dc->res_pool->mpc;
	bool result = false;
	पूर्णांक acquired_rmu = 0;
	पूर्णांक mpcc_id_projected = 0;

	स्थिर काष्ठा pwl_params *shaper_lut = शून्य;
	//get the shaper lut params
	अगर (stream->func_shaper) अणु
		अगर (stream->func_shaper->type == TF_TYPE_HWPWL)
			shaper_lut = &stream->func_shaper->pwl;
		अन्यथा अगर (stream->func_shaper->type == TF_TYPE_DISTRIBUTED_POINTS) अणु
			cm_helper_translate_curve_to_hw_क्रमmat(
					stream->func_shaper,
					&dpp_base->shaper_params, true);
			shaper_lut = &dpp_base->shaper_params;
		पूर्ण
	पूर्ण

	अगर (stream->lut3d_func &&
		stream->lut3d_func->state.bits.initialized == 1 &&
		stream->lut3d_func->state.bits.rmu_idx_valid == 1) अणु
		अगर (stream->lut3d_func->state.bits.rmu_mux_num == 0)
			mpcc_id_projected = stream->lut3d_func->state.bits.mpc_rmu0_mux;
		अन्यथा अगर (stream->lut3d_func->state.bits.rmu_mux_num == 1)
			mpcc_id_projected = stream->lut3d_func->state.bits.mpc_rmu1_mux;
		अन्यथा अगर (stream->lut3d_func->state.bits.rmu_mux_num == 2)
			mpcc_id_projected = stream->lut3d_func->state.bits.mpc_rmu2_mux;
		अगर (mpcc_id_projected != mpcc_id)
			BREAK_TO_DEBUGGER();
		/*find the reason why logical layer asचिन्हित a dअगरferant mpcc_id पूर्णांकo acquire_post_bldn_3dlut*/
		acquired_rmu = mpc->funcs->acquire_rmu(mpc, mpcc_id,
				stream->lut3d_func->state.bits.rmu_mux_num);
		अगर (acquired_rmu != stream->lut3d_func->state.bits.rmu_mux_num)
			BREAK_TO_DEBUGGER();
		result = mpc->funcs->program_3dlut(mpc,
								&stream->lut3d_func->lut_3d,
								stream->lut3d_func->state.bits.rmu_mux_num);
		result = mpc->funcs->program_shaper(mpc, shaper_lut,
				stream->lut3d_func->state.bits.rmu_mux_num);
	पूर्ण अन्यथा
		/*loop through the available mux and release the requested mpcc_id*/
		mpc->funcs->release_rmu(mpc, mpcc_id);


	वापस result;
पूर्ण

bool dcn30_set_input_transfer_func(काष्ठा dc *dc,
				काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_plane_state *plane_state)
अणु
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा dpp *dpp_base = pipe_ctx->plane_res.dpp;
	क्रमागत dc_transfer_func_predefined tf;
	bool result = true;
	काष्ठा pwl_params *params = शून्य;

	अगर (dpp_base == शून्य || plane_state == शून्य)
		वापस false;

	tf = TRANSFER_FUNCTION_UNITY;

	अगर (plane_state->in_transfer_func &&
		plane_state->in_transfer_func->type == TF_TYPE_PREDEFINED)
		tf = plane_state->in_transfer_func->tf;

	dpp_base->funcs->dpp_set_pre_degam(dpp_base, tf);

	अगर (plane_state->in_transfer_func) अणु
		अगर (plane_state->in_transfer_func->type == TF_TYPE_HWPWL)
			params = &plane_state->in_transfer_func->pwl;
		अन्यथा अगर (plane_state->in_transfer_func->type == TF_TYPE_DISTRIBUTED_POINTS &&
			cm3_helper_translate_curve_to_hw_क्रमmat(plane_state->in_transfer_func,
					&dpp_base->degamma_params, false))
			params = &dpp_base->degamma_params;
	पूर्ण

	result = dpp_base->funcs->dpp_program_gamcor_lut(dpp_base, params);

	अगर (pipe_ctx->stream_res.opp && pipe_ctx->stream_res.opp->ctx) अणु
		अगर (dpp_base->funcs->dpp_program_blnd_lut)
			hws->funcs.set_blend_lut(pipe_ctx, plane_state);
		अगर (dpp_base->funcs->dpp_program_shaper_lut &&
				dpp_base->funcs->dpp_program_3dlut)
			hws->funcs.set_shaper_3dlut(pipe_ctx, plane_state);
	पूर्ण

	वापस result;
पूर्ण

bool dcn30_set_output_transfer_func(काष्ठा dc *dc,
				काष्ठा pipe_ctx *pipe_ctx,
				स्थिर काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक mpcc_id = pipe_ctx->plane_res.hubp->inst;
	काष्ठा mpc *mpc = pipe_ctx->stream_res.opp->ctx->dc->res_pool->mpc;
	काष्ठा pwl_params *params = शून्य;
	bool ret = false;

	/* program OGAM or 3DLUT only क्रम the top pipe*/
	अगर (pipe_ctx->top_pipe == शून्य) अणु
		/*program rmu shaper and 3dlut in MPC*/
		ret = dcn30_set_mpc_shaper_3dlut(pipe_ctx, stream);
		अगर (ret == false && mpc->funcs->set_output_gamma && stream->out_transfer_func) अणु
			अगर (stream->out_transfer_func->type == TF_TYPE_HWPWL)
				params = &stream->out_transfer_func->pwl;
			अन्यथा अगर (pipe_ctx->stream->out_transfer_func->type ==
					TF_TYPE_DISTRIBUTED_POINTS &&
					cm3_helper_translate_curve_to_hw_क्रमmat(
					stream->out_transfer_func,
					&mpc->blender_params, false))
				params = &mpc->blender_params;
			 /* there are no ROM LUTs in OUTGAM */
			अगर (stream->out_transfer_func->type == TF_TYPE_PREDEFINED)
				BREAK_TO_DEBUGGER();
		पूर्ण
	पूर्ण

	mpc->funcs->set_output_gamma(mpc, mpcc_id, params);
	वापस ret;
पूर्ण

अटल व्योम dcn30_set_ग_लिखोback(
		काष्ठा dc *dc,
		काष्ठा dc_ग_लिखोback_info *wb_info,
		काष्ठा dc_state *context)
अणु
	काष्ठा mcअगर_wb *mcअगर_wb;
	काष्ठा mcअगर_buf_params *mcअगर_buf_params;

	ASSERT(wb_info->dwb_pipe_inst < MAX_DWB_PIPES);
	ASSERT(wb_info->wb_enabled);
	ASSERT(wb_info->mpcc_inst >= 0);
	ASSERT(wb_info->mpcc_inst < dc->res_pool->mpcc_count);
	mcअगर_wb = dc->res_pool->mcअगर_wb[wb_info->dwb_pipe_inst];
	mcअगर_buf_params = &wb_info->mcअगर_buf_params;

	/* set DWB MPC mux */
	dc->res_pool->mpc->funcs->set_dwb_mux(dc->res_pool->mpc,
			wb_info->dwb_pipe_inst, wb_info->mpcc_inst);
	/* set MCIF_WB buffer and arbitration configuration */
	mcअगर_wb->funcs->config_mcअगर_buf(mcअगर_wb, mcअगर_buf_params, wb_info->dwb_params.dest_height);
	mcअगर_wb->funcs->config_mcअगर_arb(mcअगर_wb, &context->bw_ctx.bw.dcn.bw_ग_लिखोback.mcअगर_wb_arb[wb_info->dwb_pipe_inst]);
पूर्ण

व्योम dcn30_update_ग_लिखोback(
		काष्ठा dc *dc,
		काष्ठा dc_ग_लिखोback_info *wb_info,
		काष्ठा dc_state *context)
अणु
	काष्ठा dwbc *dwb;
	dwb = dc->res_pool->dwbc[wb_info->dwb_pipe_inst];
	DC_LOG_DWB("%s dwb_pipe_inst = %d, mpcc_inst = %d",\
		__func__, wb_info->dwb_pipe_inst,\
		wb_info->mpcc_inst);

	dcn30_set_ग_लिखोback(dc, wb_info, context);

	/* update DWB */
	dwb->funcs->update(dwb, &wb_info->dwb_params);
पूर्ण

bool dcn30_mmhubbub_warmup(
	काष्ठा dc *dc,
	अचिन्हित पूर्णांक num_dwb,
	काष्ठा dc_ग_लिखोback_info *wb_info)
अणु
	काष्ठा dwbc *dwb;
	काष्ठा mcअगर_wb *mcअगर_wb;
	काष्ठा mcअगर_warmup_params warmup_params = अणु0पूर्ण;
	अचिन्हित पूर्णांक  i, i_buf;
	/*make sure there is no active DWB eanbled */
	क्रम (i = 0; i < num_dwb; i++) अणु
		dwb = dc->res_pool->dwbc[wb_info[i].dwb_pipe_inst];
		अगर (dwb->dwb_is_efc_transition || dwb->dwb_is_drc) अणु
			/*can not करो warmup जबतक any dwb enabled*/
			वापस false;
		पूर्ण
	पूर्ण

	अगर (wb_info->mcअगर_warmup_params.p_vmid == 0)
		वापस false;

	/*check whether this is new पूर्णांकerface: warmup big buffer once*/
	अगर (wb_info->mcअगर_warmup_params.start_address.quad_part != 0 &&
		wb_info->mcअगर_warmup_params.region_size != 0) अणु
		/*mmhubbub is shared, so it करोes not matter which MCIF*/
		mcअगर_wb = dc->res_pool->mcअगर_wb[0];
		/*warmup a big chunk of VM buffer at once*/
		warmup_params.start_address.quad_part = wb_info->mcअगर_warmup_params.start_address.quad_part;
		warmup_params.address_increment =  wb_info->mcअगर_warmup_params.region_size;
		warmup_params.region_size = wb_info->mcअगर_warmup_params.region_size;
		warmup_params.p_vmid = wb_info->mcअगर_warmup_params.p_vmid;

		अगर (warmup_params.address_increment == 0)
			warmup_params.address_increment = dc->dml.soc.vmm_page_size_bytes;

		mcअगर_wb->funcs->warmup_mcअगर(mcअगर_wb, &warmup_params);
		वापस true;
	पूर्ण
	/*following is the original: warmup each DWB's mcअगर buffer*/
	क्रम (i = 0; i < num_dwb; i++) अणु
		dwb = dc->res_pool->dwbc[wb_info[i].dwb_pipe_inst];
		mcअगर_wb = dc->res_pool->mcअगर_wb[wb_info[i].dwb_pipe_inst];
		/*warmup is क्रम VM mode only*/
		अगर (wb_info[i].mcअगर_buf_params.p_vmid == 0)
			वापस false;

		/* Warmup MCIF_WB */
		क्रम (i_buf = 0; i_buf < MCIF_BUF_COUNT; i_buf++) अणु
			warmup_params.start_address.quad_part = wb_info[i].mcअगर_buf_params.luma_address[i_buf];
			warmup_params.address_increment = dc->dml.soc.vmm_page_size_bytes;
			warmup_params.region_size = wb_info[i].mcअगर_buf_params.luma_pitch * wb_info[i].dwb_params.dest_height;
			warmup_params.p_vmid = wb_info[i].mcअगर_buf_params.p_vmid;
			mcअगर_wb->funcs->warmup_mcअगर(mcअगर_wb, &warmup_params);
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

व्योम dcn30_enable_ग_लिखोback(
		काष्ठा dc *dc,
		काष्ठा dc_ग_लिखोback_info *wb_info,
		काष्ठा dc_state *context)
अणु
	काष्ठा dwbc *dwb;
	काष्ठा mcअगर_wb *mcअगर_wb;
	काष्ठा timing_generator *optc;

	dwb = dc->res_pool->dwbc[wb_info->dwb_pipe_inst];
	mcअगर_wb = dc->res_pool->mcअगर_wb[wb_info->dwb_pipe_inst];

	/* set the OPTC source mux */
	optc = dc->res_pool->timing_generators[dwb->otg_inst];
	DC_LOG_DWB("%s dwb_pipe_inst = %d, mpcc_inst = %d",\
		__func__, wb_info->dwb_pipe_inst,\
		wb_info->mpcc_inst);
	अगर (IS_DIAG_DC(dc->ctx->dce_environment)) अणु
		/*till diags चयन to warmup पूर्णांकerface*/
		dcn30_mmhubbub_warmup(dc, 1, wb_info);
	पूर्ण
	/* Update ग_लिखोback pipe */
	dcn30_set_ग_लिखोback(dc, wb_info, context);

	/* Enable MCIF_WB */
	mcअगर_wb->funcs->enable_mcअगर(mcअगर_wb);
	/* Enable DWB */
	dwb->funcs->enable(dwb, &wb_info->dwb_params);
पूर्ण

व्योम dcn30_disable_ग_लिखोback(
		काष्ठा dc *dc,
		अचिन्हित पूर्णांक dwb_pipe_inst)
अणु
	काष्ठा dwbc *dwb;
	काष्ठा mcअगर_wb *mcअगर_wb;

	ASSERT(dwb_pipe_inst < MAX_DWB_PIPES);
	dwb = dc->res_pool->dwbc[dwb_pipe_inst];
	mcअगर_wb = dc->res_pool->mcअगर_wb[dwb_pipe_inst];
	DC_LOG_DWB("%s dwb_pipe_inst = %d",\
		__func__, dwb_pipe_inst);

	/* disable DWB */
	dwb->funcs->disable(dwb);
	/* disable MCIF */
	mcअगर_wb->funcs->disable_mcअगर(mcअगर_wb);
	/* disable MPC DWB mux */
	dc->res_pool->mpc->funcs->disable_dwb_mux(dc->res_pool->mpc, dwb_pipe_inst);
पूर्ण

व्योम dcn30_program_all_ग_लिखोback_pipes_in_tree(
		काष्ठा dc *dc,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dc_state *context)
अणु
	काष्ठा dc_ग_लिखोback_info wb_info;
	काष्ठा dwbc *dwb;
	काष्ठा dc_stream_status *stream_status = शून्य;
	पूर्णांक i_wb, i_pipe, i_stream;
	DC_LOG_DWB("%s", __func__);

	ASSERT(stream);
	क्रम (i_stream = 0; i_stream < context->stream_count; i_stream++) अणु
		अगर (context->streams[i_stream] == stream) अणु
			stream_status = &context->stream_status[i_stream];
			अवरोध;
		पूर्ण
	पूर्ण
	ASSERT(stream_status);

	ASSERT(stream->num_wb_info <= dc->res_pool->res_cap->num_dwb);
	/* For each ग_लिखोback pipe */
	क्रम (i_wb = 0; i_wb < stream->num_wb_info; i_wb++) अणु

		/* copy ग_लिखोback info to local non-स्थिर so mpcc_inst can be set */
		wb_info = stream->ग_लिखोback_info[i_wb];
		अगर (wb_info.wb_enabled) अणु

			/* get the MPCC instance क्रम ग_लिखोback_source_plane */
			wb_info.mpcc_inst = -1;
			क्रम (i_pipe = 0; i_pipe < dc->res_pool->pipe_count; i_pipe++) अणु
				काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i_pipe];

				अगर (pipe_ctx->plane_state == wb_info.ग_लिखोback_source_plane) अणु
					wb_info.mpcc_inst = pipe_ctx->plane_res.mpcc_inst;
					अवरोध;
				पूर्ण
			पूर्ण
			ASSERT(wb_info.mpcc_inst != -1);

			ASSERT(wb_info.dwb_pipe_inst < dc->res_pool->res_cap->num_dwb);
			dwb = dc->res_pool->dwbc[wb_info.dwb_pipe_inst];
			अगर (dwb->funcs->is_enabled(dwb)) अणु
				/* ग_लिखोback pipe alपढ़ोy enabled, only need to update */
				dc->hwss.update_ग_लिखोback(dc, &wb_info, context);
			पूर्ण अन्यथा अणु
				/* Enable ग_लिखोback pipe and connect to MPCC */
				dc->hwss.enable_ग_लिखोback(dc, &wb_info, context);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Disable ग_लिखोback pipe and disconnect from MPCC */
			dc->hwss.disable_ग_लिखोback(dc, wb_info.dwb_pipe_inst);
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn30_init_hw(काष्ठा dc *dc)
अणु
	काष्ठा abm **abms = dc->res_pool->multiple_abms;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा dc_bios *dcb = dc->ctx->dc_bios;
	काष्ठा resource_pool *res_pool = dc->res_pool;
	पूर्णांक i, j;
	पूर्णांक edp_num;
	uपूर्णांक32_t backlight = MAX_BACKLIGHT_LEVEL;

	अगर (dc->clk_mgr && dc->clk_mgr->funcs->init_घड़ीs)
		dc->clk_mgr->funcs->init_घड़ीs(dc->clk_mgr);

	// Initialize the dccg
	अगर (res_pool->dccg->funcs->dccg_init)
		res_pool->dccg->funcs->dccg_init(res_pool->dccg);

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

	अगर (!dcb->funcs->is_accelerated_mode(dcb)) अणु
		hws->funcs.bios_golden_init(dc);
		hws->funcs.disable_vga(dc->hwseq);
	पूर्ण

	अगर (dc->debug.enable_mem_low_घातer.bits.dmcu) अणु
		// Force ERAM to shutकरोwn अगर DMCU is not enabled
		अगर (dc->debug.disable_dmcu || dc->config.disable_dmcu) अणु
			REG_UPDATE(DMU_MEM_PWR_CNTL, DMCU_ERAM_MEM_PWR_FORCE, 3);
		पूर्ण
	पूर्ण

	// Set शेष OPTC memory घातer states
	अगर (dc->debug.enable_mem_low_घातer.bits.optc) अणु
		// Shutकरोwn when unasचिन्हित and light sleep in VBLANK
		REG_SET_2(ODM_MEM_PWR_CTRL3, 0, ODM_MEM_UNASSIGNED_PWR_MODE, 3, ODM_MEM_VBLANK_PWR_MODE, 1);
	पूर्ण

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

		link->link_enc->funcs->hw_init(link->link_enc);

		/* Check क्रम enabled DIG to identअगरy enabled display */
		अगर (link->link_enc->funcs->is_dig_enabled &&
			link->link_enc->funcs->is_dig_enabled(link->link_enc))
			link->link_status.link_active = true;
	पूर्ण

	/* Power gate DSCs */
	क्रम (i = 0; i < res_pool->res_cap->num_dsc; i++)
		अगर (hws->funcs.dsc_pg_control != शून्य)
			hws->funcs.dsc_pg_control(hws, res_pool->dscs[i]->inst, false);

	/* we want to turn off all dp displays beक्रमe करोing detection */
	अगर (dc->config.घातer_करोwn_display_on_boot) अणु
		uपूर्णांक8_t dpcd_घातer_state = '\0';
		क्रमागत dc_status status = DC_ERROR_UNEXPECTED;

		क्रम (i = 0; i < dc->link_count; i++) अणु
			अगर (dc->links[i]->connector_संकेत != SIGNAL_TYPE_DISPLAY_PORT)
				जारी;

			/* अगर any of the displays are lit up turn them off */
			status = core_link_पढ़ो_dpcd(dc->links[i], DP_SET_POWER,
						     &dpcd_घातer_state, माप(dpcd_घातer_state));
			अगर (status == DC_OK && dpcd_घातer_state == DP_POWER_STATE_D0) अणु
				/* blank dp stream beक्रमe घातer off receiver*/
				अगर (dc->links[i]->link_enc->funcs->get_dig_frontend) अणु
					अचिन्हित पूर्णांक fe;

					fe = dc->links[i]->link_enc->funcs->get_dig_frontend(
										dc->links[i]->link_enc);
					अगर (fe == ENGINE_ID_UNKNOWN)
						जारी;

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
		hws->funcs.init_pipes(dc, dc->current_state);
		अगर (dc->res_pool->hubbub->funcs->allow_self_refresh_control)
			dc->res_pool->hubbub->funcs->allow_self_refresh_control(dc->res_pool->hubbub,
					!dc->res_pool->hubbub->ctx->dc->debug.disable_stutter);
	पूर्ण

	/* In headless boot हालs, DIG may be turned
	 * on which causes HW/SW discrepancies.
	 * To aव्योम this, घातer करोwn hardware on boot
	 * अगर DIG is turned on and seamless boot not enabled
	 */
	अगर (dc->config.घातer_करोwn_display_on_boot) अणु
		काष्ठा dc_link *edp_links[MAX_NUM_EDP];
		काष्ठा dc_link *edp_link;

		get_edp_links(dc, edp_links, &edp_num);
		अगर (edp_num) अणु
			क्रम (i = 0; i < edp_num; i++) अणु
				edp_link = edp_links[i];
				अगर (edp_link->link_enc->funcs->is_dig_enabled &&
						edp_link->link_enc->funcs->is_dig_enabled(edp_link->link_enc) &&
						dc->hwss.edp_backlight_control &&
						dc->hwss.घातer_करोwn &&
						dc->hwss.edp_घातer_control) अणु
					dc->hwss.edp_backlight_control(edp_link, false);
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
	पूर्ण

	क्रम (i = 0; i < res_pool->audio_count; i++) अणु
		काष्ठा audio *audio = res_pool->audios[i];

		audio->funcs->hw_init(audio);
	पूर्ण

	क्रम (i = 0; i < dc->link_count; i++) अणु
		काष्ठा dc_link *link = dc->links[i];

		अगर (link->panel_cntl)
			backlight = link->panel_cntl->funcs->hw_init(link->panel_cntl);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (abms[i] != शून्य)
			abms[i]->funcs->abm_init(abms[i], backlight);
	पूर्ण

	/* घातer AFMT HDMI memory TODO: may move to dis/en output save घातer*/
	REG_WRITE(DIO_MEM_PWR_CTRL, 0);

	अगर (!dc->debug.disable_घड़ी_gate) अणु
		/* enable all DCN घड़ी gating */
		REG_WRITE(DCCG_GATE_DISABLE_CNTL, 0);

		REG_WRITE(DCCG_GATE_DISABLE_CNTL2, 0);

		REG_UPDATE(DCFCLK_CNTL, DCFCLK_GATE_DIS, 0);
	पूर्ण
	अगर (hws->funcs.enable_घातer_gating_plane)
		hws->funcs.enable_घातer_gating_plane(dc->hwseq, true);

	अगर (!dcb->funcs->is_accelerated_mode(dcb) && dc->res_pool->hubbub->funcs->init_watermarks)
		dc->res_pool->hubbub->funcs->init_watermarks(dc->res_pool->hubbub);

	अगर (dc->clk_mgr->funcs->notअगरy_wm_ranges)
		dc->clk_mgr->funcs->notअगरy_wm_ranges(dc->clk_mgr);

	अगर (dc->clk_mgr->funcs->set_hard_max_memclk)
		dc->clk_mgr->funcs->set_hard_max_memclk(dc->clk_mgr);

	अगर (dc->res_pool->hubbub->funcs->क्रमce_pstate_change_control)
		dc->res_pool->hubbub->funcs->क्रमce_pstate_change_control(
				dc->res_pool->hubbub, false, false);
पूर्ण

व्योम dcn30_set_avmute(काष्ठा pipe_ctx *pipe_ctx, bool enable)
अणु
	अगर (pipe_ctx == शून्य)
		वापस;

	अगर (dc_is_hdmi_संकेत(pipe_ctx->stream->संकेत) && pipe_ctx->stream_res.stream_enc != शून्य)
		pipe_ctx->stream_res.stream_enc->funcs->set_avmute(
				pipe_ctx->stream_res.stream_enc,
				enable);
पूर्ण

व्योम dcn30_update_info_frame(काष्ठा pipe_ctx *pipe_ctx)
अणु
	bool is_hdmi_पंचांगds;
	bool is_dp;

	ASSERT(pipe_ctx->stream);

	अगर (pipe_ctx->stream_res.stream_enc == शून्य)
		वापस;  /* this is not root pipe */

	is_hdmi_पंचांगds = dc_is_hdmi_पंचांगds_संकेत(pipe_ctx->stream->संकेत);
	is_dp = dc_is_dp_संकेत(pipe_ctx->stream->संकेत);

	अगर (!is_hdmi_पंचांगds && !is_dp)
		वापस;

	अगर (is_hdmi_पंचांगds)
		pipe_ctx->stream_res.stream_enc->funcs->update_hdmi_info_packets(
			pipe_ctx->stream_res.stream_enc,
			&pipe_ctx->stream_res.encoder_info_frame);
	अन्यथा
		pipe_ctx->stream_res.stream_enc->funcs->update_dp_info_packets(
			pipe_ctx->stream_res.stream_enc,
			&pipe_ctx->stream_res.encoder_info_frame);
पूर्ण

व्योम dcn30_program_dmdata_engine(काष्ठा pipe_ctx *pipe_ctx)
अणु
	काष्ठा dc_stream_state    *stream     = pipe_ctx->stream;
	काष्ठा hubp               *hubp       = pipe_ctx->plane_res.hubp;
	bool                       enable     = false;
	काष्ठा stream_encoder     *stream_enc = pipe_ctx->stream_res.stream_enc;
	क्रमागत dynamic_metadata_mode mode       = dc_is_dp_संकेत(stream->संकेत)
							? dmdata_dp
							: dmdata_hdmi;

	/* अगर using dynamic meta, करोn't set up generic infopackets */
	अगर (pipe_ctx->stream->dmdata_address.quad_part != 0) अणु
		pipe_ctx->stream_res.encoder_info_frame.hdrsmd.valid = false;
		enable = true;
	पूर्ण

	अगर (!hubp)
		वापस;

	अगर (!stream_enc || !stream_enc->funcs->set_dynamic_metadata)
		वापस;

	stream_enc->funcs->set_dynamic_metadata(stream_enc, enable,
							hubp->inst, mode);
पूर्ण

bool dcn30_apply_idle_घातer_optimizations(काष्ठा dc *dc, bool enable)
अणु
	जोड़ dmub_rb_cmd cmd;
	uपूर्णांक32_t पंचांगr_delay = 0, पंचांगr_scale = 0;
	काष्ठा dc_cursor_attributes cursor_attr;
	bool cursor_cache_enable = false;
	काष्ठा dc_stream_state *stream = शून्य;
	काष्ठा dc_plane_state *plane = शून्य;

	अगर (!dc->ctx->dmub_srv)
		वापस false;

	अगर (enable) अणु
		अगर (dc->current_state) अणु
			पूर्णांक i;

			/* First, check no-memory-requests हाल */
			क्रम (i = 0; i < dc->current_state->stream_count; i++) अणु
				अगर (dc->current_state->stream_status[i].plane_count)
					/* Fail eligibility on a visible stream */
					अवरोध;
			पूर्ण

			अगर (i == dc->current_state->stream_count) अणु
				/* Enable no-memory-requests हाल */
				स_रखो(&cmd, 0, माप(cmd));
				cmd.mall.header.type = DMUB_CMD__MALL;
				cmd.mall.header.sub_type = DMUB_CMD__MALL_ACTION_NO_DF_REQ;
				cmd.mall.header.payload_bytes = माप(cmd.mall) - माप(cmd.mall.header);

				dc_dmub_srv_cmd_queue(dc->ctx->dmub_srv, &cmd);
				dc_dmub_srv_cmd_execute(dc->ctx->dmub_srv);

				वापस true;
			पूर्ण

			stream = dc->current_state->streams[0];
			plane = (stream ? dc->current_state->stream_status[0].plane_states[0] : शून्य);

			अगर (stream && plane) अणु
				cursor_cache_enable = stream->cursor_position.enable &&
						plane->address.grph.cursor_cache_addr.quad_part;
				cursor_attr = stream->cursor_attributes;
			पूर्ण

			/*
			 * Second, check MALL eligibility
			 *
			 * single display only, single surface only, 8 and 16 bit क्रमmats only, no VM,
			 * करो not use MALL क्रम displays that support PSR as they use D0i3.2 in DMCUB FW
			 *
			 * TODO: When we implement multi-display, PSR displays will be allowed अगर there is
			 * a non-PSR display present, since in that हाल we can't करो D0i3.2
			 */
			अगर (dc->current_state->stream_count == 1 &&
					stream->link->psr_settings.psr_version == DC_PSR_VERSION_UNSUPPORTED &&
					dc->current_state->stream_status[0].plane_count == 1 &&
					plane->क्रमmat <= SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F &&
					plane->क्रमmat >= SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 &&
					plane->address.page_table_base.quad_part == 0 &&
					dc->hwss.करोes_plane_fit_in_mall &&
					dc->hwss.करोes_plane_fit_in_mall(dc, plane,
							cursor_cache_enable ? &cursor_attr : शून्य)) अणु
				अचिन्हित पूर्णांक v_total = stream->adjust.v_total_max ?
						stream->adjust.v_total_max : stream->timing.v_total;
				अचिन्हित पूर्णांक refresh_hz = भाग_u64((अचिन्हित दीर्घ दीर्घ) stream->timing.pix_clk_100hz *
						100LL, (v_total * stream->timing.h_total));

				/*
				 * one frame समय in microsec:
				 * Delay_Us = 1000000 / refresh
				 * dynamic_delay_us = 1000000 / refresh + 2 * stutter_period
				 *
				 * one frame समय modअगरied by 'additional timer percent' (p):
				 * Delay_Us_modअगरied = dynamic_delay_us + dynamic_delay_us * p / 100
				 *                   = dynamic_delay_us * (1 + p / 100)
				 *                   = (1000000 / refresh + 2 * stutter_period) * (100 + p) / 100
				 *                   = (1000000 + 2 * stutter_period * refresh) * (100 + p) / (100 * refresh)
				 *
				 * क्रमmula क्रम समयr duration based on parameters, from regspec:
				 * dynamic_delay_us = 65.28 * (64 + MallFrameCacheTmrDly) * 2^MallFrameCacheTmrScale
				 *
				 * dynamic_delay_us / 65.28 = (64 + MallFrameCacheTmrDly) * 2^MallFrameCacheTmrScale
				 * (dynamic_delay_us / 65.28) / 2^MallFrameCacheTmrScale = 64 + MallFrameCacheTmrDly
				 * MallFrameCacheTmrDly = ((dynamic_delay_us / 65.28) / 2^MallFrameCacheTmrScale) - 64
				 *                      = (1000000 + 2 * stutter_period * refresh) * (100 + p) / (100 * refresh) / 65.28 / 2^MallFrameCacheTmrScale - 64
				 *                      = (1000000 + 2 * stutter_period * refresh) * (100 + p) / (refresh * 6528 * 2^MallFrameCacheTmrScale) - 64
				 *
				 * need to round up the result of the भागision beक्रमe the subtraction
				 */
				अचिन्हित पूर्णांक denom = refresh_hz * 6528;
				अचिन्हित पूर्णांक stutter_period = dc->current_state->perf_params.stutter_period_us;

				पंचांगr_delay = भाग_u64(((1000000LL + 2 * stutter_period * refresh_hz) *
						(100LL + dc->debug.mall_additional_समयr_percent) + denom - 1),
						denom) - 64LL;

				/* scale should be increased until it fits पूर्णांकo 6 bits */
				जबतक (पंचांगr_delay & ~0x3F) अणु
					पंचांगr_scale++;

					अगर (पंचांगr_scale > 3) अणु
						/* Delay exceeds range of hysteresis समयr */
						ASSERT(false);
						वापस false;
					पूर्ण

					denom *= 2;
					पंचांगr_delay = भाग_u64(((1000000LL + 2 * stutter_period * refresh_hz) *
							(100LL + dc->debug.mall_additional_समयr_percent) + denom - 1),
							denom) - 64LL;
				पूर्ण

				/* Copy HW cursor */
				अगर (cursor_cache_enable) अणु
					स_रखो(&cmd, 0, माप(cmd));
					cmd.mall.header.type = DMUB_CMD__MALL;
					cmd.mall.header.sub_type = DMUB_CMD__MALL_ACTION_COPY_CURSOR;
					cmd.mall.header.payload_bytes =
							माप(cmd.mall) - माप(cmd.mall.header);

					चयन (cursor_attr.color_क्रमmat) अणु
					हाल CURSOR_MODE_MONO:
						cmd.mall.cursor_bpp = 2;
						अवरोध;
					हाल CURSOR_MODE_COLOR_1BIT_AND:
					हाल CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA:
					हाल CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA:
						cmd.mall.cursor_bpp = 32;
						अवरोध;

					हाल CURSOR_MODE_COLOR_64BIT_FP_PRE_MULTIPLIED:
					हाल CURSOR_MODE_COLOR_64BIT_FP_UN_PRE_MULTIPLIED:
						cmd.mall.cursor_bpp = 64;
						अवरोध;
					पूर्ण

					cmd.mall.cursor_copy_src.quad_part = cursor_attr.address.quad_part;
					cmd.mall.cursor_copy_dst.quad_part =
							(plane->address.grph.cursor_cache_addr.quad_part + 2047) & ~2047;
					cmd.mall.cursor_width = cursor_attr.width;
					cmd.mall.cursor_height = cursor_attr.height;
					cmd.mall.cursor_pitch = cursor_attr.pitch;

					dc_dmub_srv_cmd_queue(dc->ctx->dmub_srv, &cmd);
					dc_dmub_srv_cmd_execute(dc->ctx->dmub_srv);
					dc_dmub_srv_रुको_idle(dc->ctx->dmub_srv);

					/* Use copied cursor, and it's okay to not चयन back */
					cursor_attr.address.quad_part = cmd.mall.cursor_copy_dst.quad_part;
					dc_stream_set_cursor_attributes(stream, &cursor_attr);
				पूर्ण

				/* Enable MALL */
				स_रखो(&cmd, 0, माप(cmd));
				cmd.mall.header.type = DMUB_CMD__MALL;
				cmd.mall.header.sub_type = DMUB_CMD__MALL_ACTION_ALLOW;
				cmd.mall.header.payload_bytes = माप(cmd.mall) - माप(cmd.mall.header);
				cmd.mall.पंचांगr_delay = पंचांगr_delay;
				cmd.mall.पंचांगr_scale = पंचांगr_scale;
				cmd.mall.debug_bits = dc->debug.mall_error_as_fatal;

				dc_dmub_srv_cmd_queue(dc->ctx->dmub_srv, &cmd);
				dc_dmub_srv_cmd_execute(dc->ctx->dmub_srv);

				वापस true;
			पूर्ण
		पूर्ण

		/* No applicable optimizations */
		वापस false;
	पूर्ण

	/* Disable MALL */
	स_रखो(&cmd, 0, माप(cmd));
	cmd.mall.header.type = DMUB_CMD__MALL;
	cmd.mall.header.sub_type = DMUB_CMD__MALL_ACTION_DISALLOW;
	cmd.mall.header.payload_bytes =
		माप(cmd.mall) - माप(cmd.mall.header);

	dc_dmub_srv_cmd_queue(dc->ctx->dmub_srv, &cmd);
	dc_dmub_srv_cmd_execute(dc->ctx->dmub_srv);
	dc_dmub_srv_रुको_idle(dc->ctx->dmub_srv);

	वापस true;
पूर्ण

bool dcn30_करोes_plane_fit_in_mall(काष्ठा dc *dc, काष्ठा dc_plane_state *plane, काष्ठा dc_cursor_attributes *cursor_attr)
अणु
	// add meta size?
	अचिन्हित पूर्णांक surface_size = plane->plane_size.surface_pitch * plane->plane_size.surface_size.height *
			(plane->क्रमmat >= SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 ? 8 : 4);
	अचिन्हित पूर्णांक mall_size = dc->caps.mall_माप_प्रकारotal;
	अचिन्हित पूर्णांक cursor_size = 0;

	अगर (dc->debug.mall_size_override)
		mall_size = 1024 * 1024 * dc->debug.mall_size_override;

	अगर (cursor_attr) अणु
		cursor_size = dc->caps.max_cursor_size * dc->caps.max_cursor_size;

		चयन (cursor_attr->color_क्रमmat) अणु
		हाल CURSOR_MODE_MONO:
			cursor_size /= 2;
			अवरोध;
		हाल CURSOR_MODE_COLOR_1BIT_AND:
		हाल CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA:
		हाल CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA:
			cursor_size *= 4;
			अवरोध;

		हाल CURSOR_MODE_COLOR_64BIT_FP_PRE_MULTIPLIED:
		हाल CURSOR_MODE_COLOR_64BIT_FP_UN_PRE_MULTIPLIED:
			cursor_size *= 8;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (surface_size + cursor_size) < mall_size;
पूर्ण

व्योम dcn30_hardware_release(काष्ठा dc *dc)
अणु
	/* अगर pstate unsupported, क्रमce it supported */
	अगर (!dc->clk_mgr->clks.p_state_change_support &&
			dc->res_pool->hubbub->funcs->क्रमce_pstate_change_control)
		dc->res_pool->hubbub->funcs->क्रमce_pstate_change_control(
				dc->res_pool->hubbub, true, true);
पूर्ण

व्योम dcn30_set_disp_pattern_generator(स्थिर काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe_ctx,
		क्रमागत controller_dp_test_pattern test_pattern,
		क्रमागत controller_dp_color_space color_space,
		क्रमागत dc_color_depth color_depth,
		स्थिर काष्ठा tg_color *solid_color,
		पूर्णांक width, पूर्णांक height, पूर्णांक offset)
अणु
	काष्ठा stream_resource *stream_res = &pipe_ctx->stream_res;
	काष्ठा pipe_ctx *mpcc_pipe;

	अगर (test_pattern != CONTROLLER_DP_TEST_PATTERN_VIDEOMODE) अणु
		pipe_ctx->vtp_locked = false;
		/* turning on DPG */
		stream_res->opp->funcs->opp_set_disp_pattern_generator(stream_res->opp, test_pattern, color_space,
				color_depth, solid_color, width, height, offset);

		/* Defer hubp blank अगर tg is locked */
		अगर (stream_res->tg->funcs->is_tg_enabled(stream_res->tg)) अणु
			अगर (stream_res->tg->funcs->is_locked(stream_res->tg))
				pipe_ctx->vtp_locked = true;
			अन्यथा अणु
				/* Blank HUBP to allow p-state during blank on all timings */
				pipe_ctx->plane_res.hubp->funcs->set_blank(pipe_ctx->plane_res.hubp, true);

				क्रम (mpcc_pipe = pipe_ctx->bottom_pipe; mpcc_pipe; mpcc_pipe = mpcc_pipe->bottom_pipe)
					mpcc_pipe->plane_res.hubp->funcs->set_blank(mpcc_pipe->plane_res.hubp, true);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* turning off DPG */
		pipe_ctx->plane_res.hubp->funcs->set_blank(pipe_ctx->plane_res.hubp, false);
		क्रम (mpcc_pipe = pipe_ctx->bottom_pipe; mpcc_pipe; mpcc_pipe = mpcc_pipe->bottom_pipe)
			mpcc_pipe->plane_res.hubp->funcs->set_blank(mpcc_pipe->plane_res.hubp, false);

		stream_res->opp->funcs->opp_set_disp_pattern_generator(stream_res->opp, test_pattern, color_space,
				color_depth, solid_color, width, height, offset);
	पूर्ण
पूर्ण
