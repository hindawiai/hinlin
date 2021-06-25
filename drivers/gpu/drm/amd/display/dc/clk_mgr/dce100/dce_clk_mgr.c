<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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


#समावेश "dccg.h"
#समावेश "clk_mgr_internal.h"
#समावेश "dce_clk_mgr.h"
#समावेश "dce110/dce110_clk_mgr.h"
#समावेश "dce112/dce112_clk_mgr.h"
#समावेश "reg_helper.h"
#समावेश "dmcu.h"
#समावेश "core_types.h"
#समावेश "dal_asic_id.h"

/*
 * Currently the रेजिस्टर shअगरts and masks in this file are used क्रम dce100 and dce80
 * which has identical definitions.
 * TODO: हटाओ this when DPREFCLK_CNTL and dpref DENTIST_DISPCLK_CNTL
 * is moved to dccg, where it beदीर्घs
 */
#समावेश "dce/dce_8_0_d.h"
#समावेश "dce/dce_8_0_sh_mask.h"

#घोषणा REG(reg) \
	(clk_mgr->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	clk_mgr->clk_mgr_shअगरt->field_name, clk_mgr->clk_mgr_mask->field_name

अटल स्थिर काष्ठा clk_mgr_रेजिस्टरs disp_clk_regs = अणु
		CLK_COMMON_REG_LIST_DCE_BASE()
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_shअगरt disp_clk_shअगरt = अणु
		CLK_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_mask disp_clk_mask = अणु
		CLK_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(_MASK)
पूर्ण;


/* Max घड़ी values क्रम each state indexed by "enum clocks_state": */
अटल स्थिर काष्ठा state_dependent_घड़ीs dce80_max_clks_by_state[] = अणु
/* ClocksStateInvalid - should not be used */
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/* ClocksStateUltraLow - not expected to be used क्रम DCE 8.0 */
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/* ClocksStateLow */
अणु .display_clk_khz = 352000, .pixel_clk_khz = 330000पूर्ण,
/* ClocksStateNominal */
अणु .display_clk_khz = 600000, .pixel_clk_khz = 400000 पूर्ण,
/* ClocksStatePerक्रमmance */
अणु .display_clk_khz = 600000, .pixel_clk_khz = 400000 पूर्ण पूर्ण;

पूर्णांक dentist_get_भागider_from_did(पूर्णांक did)
अणु
	अगर (did < DENTIST_BASE_DID_1)
		did = DENTIST_BASE_DID_1;
	अगर (did > DENTIST_MAX_DID)
		did = DENTIST_MAX_DID;

	अगर (did < DENTIST_BASE_DID_2) अणु
		वापस DENTIST_DIVIDER_RANGE_1_START + DENTIST_DIVIDER_RANGE_1_STEP
							* (did - DENTIST_BASE_DID_1);
	पूर्ण अन्यथा अगर (did < DENTIST_BASE_DID_3) अणु
		वापस DENTIST_DIVIDER_RANGE_2_START + DENTIST_DIVIDER_RANGE_2_STEP
							* (did - DENTIST_BASE_DID_2);
	पूर्ण अन्यथा अगर (did < DENTIST_BASE_DID_4) अणु
		वापस DENTIST_DIVIDER_RANGE_3_START + DENTIST_DIVIDER_RANGE_3_STEP
							* (did - DENTIST_BASE_DID_3);
	पूर्ण अन्यथा अणु
		वापस DENTIST_DIVIDER_RANGE_4_START + DENTIST_DIVIDER_RANGE_4_STEP
							* (did - DENTIST_BASE_DID_4);
	पूर्ण
पूर्ण

/* SW will adjust DP REF Clock average value क्रम all purposes
 * (DP DTO / DP Audio DTO and DP GTC)
 अगर घड़ी is spपढ़ो क्रम all हालs:
 -अगर SS enabled on DP Ref घड़ी and HW de-spपढ़ोing enabled with SW
 calculations क्रम DS_INCR/DS_MODULO (this is planned to be शेष हाल)
 -अगर SS enabled on DP Ref घड़ी and HW de-spपढ़ोing enabled with HW
 calculations (not planned to be used, but average घड़ी should still
 be valid)
 -अगर SS enabled on DP Ref घड़ी and HW de-spपढ़ोing disabled
 (should not be हाल with CIK) then SW should program all rates
 generated according to average value (हाल as with previous ASICs)
  */

पूर्णांक dce_adjust_dp_ref_freq_क्रम_ss(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce, पूर्णांक dp_ref_clk_khz)
अणु
	अगर (clk_mgr_dce->ss_on_dprefclk && clk_mgr_dce->dprefclk_ss_भागider != 0) अणु
		काष्ठा fixed31_32 ss_percentage = dc_fixpt_भाग_पूर्णांक(
				dc_fixpt_from_fraction(clk_mgr_dce->dprefclk_ss_percentage,
							clk_mgr_dce->dprefclk_ss_भागider), 200);
		काष्ठा fixed31_32 adj_dp_ref_clk_khz;

		ss_percentage = dc_fixpt_sub(dc_fixpt_one, ss_percentage);
		adj_dp_ref_clk_khz = dc_fixpt_mul_पूर्णांक(ss_percentage, dp_ref_clk_khz);
		dp_ref_clk_khz = dc_fixpt_न्यूनमान(adj_dp_ref_clk_khz);
	पूर्ण
	वापस dp_ref_clk_khz;
पूर्ण

पूर्णांक dce_get_dp_ref_freq_khz(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	पूर्णांक dprefclk_wभागider;
	पूर्णांक dprefclk_src_sel;
	पूर्णांक dp_ref_clk_khz;
	पूर्णांक target_भाग;

	/* ASSERT DP Reference Clock source is from DFS*/
	REG_GET(DPREFCLK_CNTL, DPREFCLK_SRC_SEL, &dprefclk_src_sel);
	ASSERT(dprefclk_src_sel == 0);

	/* Read the mmDENTIST_DISPCLK_CNTL to get the currently
	 * programmed DID DENTIST_DPREFCLK_WDIVIDER*/
	REG_GET(DENTIST_DISPCLK_CNTL, DENTIST_DPREFCLK_WDIVIDER, &dprefclk_wभागider);

	/* Convert DENTIST_DPREFCLK_WDIVIDERto actual भागider*/
	target_भाग = dentist_get_भागider_from_did(dprefclk_wभागider);

	/* Calculate the current DFS घड़ी, in kHz.*/
	dp_ref_clk_khz = (DENTIST_DIVIDER_RANGE_SCALE_FACTOR
		* clk_mgr->base.dentist_vco_freq_khz) / target_भाग;

	वापस dce_adjust_dp_ref_freq_क्रम_ss(clk_mgr, dp_ref_clk_khz);
पूर्ण

पूर्णांक dce12_get_dp_ref_freq_khz(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	वापस dce_adjust_dp_ref_freq_क्रम_ss(clk_mgr_dce, clk_mgr_base->dprefclk_khz);
पूर्ण

/* unit: in_khz beक्रमe mode set, get pixel घड़ी from context. ASIC रेजिस्टर
 * may not be programmed yet
 */
uपूर्णांक32_t dce_get_max_pixel_घड़ी_क्रम_all_paths(काष्ठा dc_state *context)
अणु
	uपूर्णांक32_t max_pix_clk = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &context->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream == शून्य)
			जारी;

		/* करो not check under lay */
		अगर (pipe_ctx->top_pipe)
			जारी;

		अगर (pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz / 10 > max_pix_clk)
			max_pix_clk = pipe_ctx->stream_res.pix_clk_params.requested_pix_clk_100hz / 10;

		/* उठाओ घड़ी state क्रम HBR3/2 अगर required. Confirmed with HW DCE/DPCS
		 * logic क्रम HBR3 still needs Nominal (0.8V) on VDDC rail
		 */
		अगर (dc_is_dp_संकेत(pipe_ctx->stream->संकेत) &&
				pipe_ctx->stream_res.pix_clk_params.requested_sym_clk > max_pix_clk)
			max_pix_clk = pipe_ctx->stream_res.pix_clk_params.requested_sym_clk;
	पूर्ण

	वापस max_pix_clk;
पूर्ण

क्रमागत dm_pp_घड़ीs_state dce_get_required_घड़ीs_state(
	काष्ठा clk_mgr *clk_mgr_base,
	काष्ठा dc_state *context)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	पूर्णांक i;
	क्रमागत dm_pp_घड़ीs_state low_req_clk;
	पूर्णांक max_pix_clk = dce_get_max_pixel_घड़ी_क्रम_all_paths(context);

	/* Iterate from highest supported to lowest valid state, and update
	 * lowest RequiredState with the lowest state that satisfies
	 * all required घड़ीs
	 */
	क्रम (i = clk_mgr_dce->max_clks_state; i >= DM_PP_CLOCKS_STATE_ULTRA_LOW; i--)
		अगर (context->bw_ctx.bw.dce.dispclk_khz >
				clk_mgr_dce->max_clks_by_state[i].display_clk_khz
			|| max_pix_clk >
				clk_mgr_dce->max_clks_by_state[i].pixel_clk_khz)
			अवरोध;

	low_req_clk = i + 1;
	अगर (low_req_clk > clk_mgr_dce->max_clks_state) अणु
		/* set max घड़ी state क्रम high phyघड़ी, invalid on exceeding display घड़ी */
		अगर (clk_mgr_dce->max_clks_by_state[clk_mgr_dce->max_clks_state].display_clk_khz
				< context->bw_ctx.bw.dce.dispclk_khz)
			low_req_clk = DM_PP_CLOCKS_STATE_INVALID;
		अन्यथा
			low_req_clk = clk_mgr_dce->max_clks_state;
	पूर्ण

	वापस low_req_clk;
पूर्ण


/* TODO: हटाओ use the two broken करोwn functions */
पूर्णांक dce_set_घड़ी(
	काष्ठा clk_mgr *clk_mgr_base,
	पूर्णांक requested_clk_khz)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा bp_pixel_घड़ी_parameters pxl_clk_params = अणु 0 पूर्ण;
	काष्ठा dc_bios *bp = clk_mgr_base->ctx->dc_bios;
	पूर्णांक actual_घड़ी = requested_clk_khz;
	काष्ठा dmcu *dmcu = clk_mgr_dce->base.ctx->dc->res_pool->dmcu;

	/* Make sure requested घड़ी isn't lower than minimum threshold*/
	अगर (requested_clk_khz > 0)
		requested_clk_khz = max(requested_clk_khz,
				clk_mgr_dce->base.dentist_vco_freq_khz / 64);

	/* Prepare to program display घड़ी*/
	pxl_clk_params.target_pixel_घड़ी_100hz = requested_clk_khz * 10;
	pxl_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;

	अगर (clk_mgr_dce->dfs_bypass_active)
		pxl_clk_params.flags.SET_DISPCLK_DFS_BYPASS = true;

	bp->funcs->program_display_engine_pll(bp, &pxl_clk_params);

	अगर (clk_mgr_dce->dfs_bypass_active) अणु
		/* Cache the fixed display घड़ी*/
		clk_mgr_dce->dfs_bypass_disp_clk =
			pxl_clk_params.dfs_bypass_display_घड़ी;
		actual_घड़ी = pxl_clk_params.dfs_bypass_display_घड़ी;
	पूर्ण

	/* from घातer करोwn, we need mark the घड़ी state as ClocksStateNominal
	 * from HWReset, so when resume we will call pplib voltage regulator.*/
	अगर (requested_clk_khz == 0)
		clk_mgr_dce->cur_min_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;

	अगर (dmcu && dmcu->funcs->is_dmcu_initialized(dmcu))
		dmcu->funcs->set_psr_रुको_loop(dmcu, actual_घड़ी / 1000 / 7);

	वापस actual_घड़ी;
पूर्ण


अटल व्योम dce_घड़ी_पढ़ो_पूर्णांकegrated_info(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce)
अणु
	काष्ठा dc_debug_options *debug = &clk_mgr_dce->base.ctx->dc->debug;
	काष्ठा dc_bios *bp = clk_mgr_dce->base.ctx->dc_bios;
	पूर्णांक i;

	अगर (bp->पूर्णांकegrated_info)
		clk_mgr_dce->base.dentist_vco_freq_khz = bp->पूर्णांकegrated_info->dentist_vco_freq;
	अगर (clk_mgr_dce->base.dentist_vco_freq_khz == 0) अणु
		clk_mgr_dce->base.dentist_vco_freq_khz = bp->fw_info.smu_gpu_pll_output_freq;
		अगर (clk_mgr_dce->base.dentist_vco_freq_khz == 0)
			clk_mgr_dce->base.dentist_vco_freq_khz = 3600000;
	पूर्ण

	/*update the maximum display घड़ी क्रम each घातer state*/
	क्रम (i = 0; i < NUMBER_OF_DISP_CLK_VOLTAGE; ++i) अणु
		क्रमागत dm_pp_घड़ीs_state clk_state = DM_PP_CLOCKS_STATE_INVALID;

		चयन (i) अणु
		हाल 0:
			clk_state = DM_PP_CLOCKS_STATE_ULTRA_LOW;
			अवरोध;

		हाल 1:
			clk_state = DM_PP_CLOCKS_STATE_LOW;
			अवरोध;

		हाल 2:
			clk_state = DM_PP_CLOCKS_STATE_NOMINAL;
			अवरोध;

		हाल 3:
			clk_state = DM_PP_CLOCKS_STATE_PERFORMANCE;
			अवरोध;

		शेष:
			clk_state = DM_PP_CLOCKS_STATE_INVALID;
			अवरोध;
		पूर्ण

		/*Do not allow bad VBIOS/SBIOS to override with invalid values,
		 * check क्रम > 100MHz*/
		अगर (bp->पूर्णांकegrated_info)
			अगर (bp->पूर्णांकegrated_info->disp_clk_voltage[i].max_supported_clk >= 100000)
				clk_mgr_dce->max_clks_by_state[clk_state].display_clk_khz =
					bp->पूर्णांकegrated_info->disp_clk_voltage[i].max_supported_clk;
	पूर्ण

	अगर (!debug->disable_dfs_bypass && bp->पूर्णांकegrated_info)
		अगर (bp->पूर्णांकegrated_info->gpu_cap_info & DFS_BYPASS_ENABLE)
			clk_mgr_dce->dfs_bypass_enabled = true;
पूर्ण

व्योम dce_घड़ी_पढ़ो_ss_info(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce)
अणु
	काष्ठा dc_bios *bp = clk_mgr_dce->base.ctx->dc_bios;
	पूर्णांक ss_info_num = bp->funcs->get_ss_entry_number(
			bp, AS_SIGNAL_TYPE_GPU_PLL);

	अगर (ss_info_num) अणु
		काष्ठा spपढ़ो_spectrum_info info = अणु अणु 0 पूर्ण पूर्ण;
		क्रमागत bp_result result = bp->funcs->get_spपढ़ो_spectrum_info(
				bp, AS_SIGNAL_TYPE_GPU_PLL, 0, &info);

		/* Based on VBIOS, VBIOS will keep entry क्रम GPU PLL SS
		 * even अगर SS not enabled and in that हाल
		 * SSInfo.spपढ़ोSpectrumPercentage !=0 would be sign
		 * that SS is enabled
		 */
		अगर (result == BP_RESULT_OK &&
				info.spपढ़ो_spectrum_percentage != 0) अणु
			clk_mgr_dce->ss_on_dprefclk = true;
			clk_mgr_dce->dprefclk_ss_भागider = info.spपढ़ो_percentage_भागider;

			अगर (info.type.CENTER_MODE == 0) अणु
				/* TODO: Currently क्रम DP Reference घड़ी we
				 * need only SS percentage क्रम
				 * करोwnspपढ़ो */
				clk_mgr_dce->dprefclk_ss_percentage =
						info.spपढ़ो_spectrum_percentage;
			पूर्ण

			वापस;
		पूर्ण

		result = bp->funcs->get_spपढ़ो_spectrum_info(
				bp, AS_SIGNAL_TYPE_DISPLAY_PORT, 0, &info);

		/* Based on VBIOS, VBIOS will keep entry क्रम DPREFCLK SS
		 * even अगर SS not enabled and in that हाल
		 * SSInfo.spपढ़ोSpectrumPercentage !=0 would be sign
		 * that SS is enabled
		 */
		अगर (result == BP_RESULT_OK &&
				info.spपढ़ो_spectrum_percentage != 0) अणु
			clk_mgr_dce->ss_on_dprefclk = true;
			clk_mgr_dce->dprefclk_ss_भागider = info.spपढ़ो_percentage_भागider;

			अगर (info.type.CENTER_MODE == 0) अणु
				/* Currently क्रम DP Reference घड़ी we
				 * need only SS percentage क्रम
				 * करोwnspपढ़ो */
				clk_mgr_dce->dprefclk_ss_percentage =
						info.spपढ़ो_spectrum_percentage;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dce_pplib_apply_display_requirements(
	काष्ठा dc *dc,
	काष्ठा dc_state *context)
अणु
	काष्ठा dm_pp_display_configuration *pp_display_cfg = &context->pp_display_cfg;

	pp_display_cfg->avail_mclk_चयन_समय_us = dce110_get_min_vblank_समय_us(context);

	dce110_fill_display_configs(context, pp_display_cfg);

	अगर (स_भेद(&dc->current_state->pp_display_cfg, pp_display_cfg, माप(*pp_display_cfg)) !=  0)
		dm_pp_apply_display_requirements(dc->ctx, pp_display_cfg);
पूर्ण

अटल व्योम dce_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dm_pp_घातer_level_change_request level_change_req;
	पूर्णांक patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A क्रम dal3 linux, investigate why this works */
	अगर (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	level_change_req.घातer_level = dce_get_required_घड़ीs_state(clk_mgr_base, context);
	/* get max घड़ी state from PPLIB */
	अगर ((level_change_req.घातer_level < clk_mgr_dce->cur_min_clks_state && safe_to_lower)
			|| level_change_req.घातer_level > clk_mgr_dce->cur_min_clks_state) अणु
		अगर (dm_pp_apply_घातer_level_change_request(clk_mgr_base->ctx, &level_change_req))
			clk_mgr_dce->cur_min_clks_state = level_change_req.घातer_level;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, patched_disp_clk, clk_mgr_base->clks.dispclk_khz)) अणु
		patched_disp_clk = dce_set_घड़ी(clk_mgr_base, patched_disp_clk);
		clk_mgr_base->clks.dispclk_khz = patched_disp_clk;
	पूर्ण
	dce_pplib_apply_display_requirements(clk_mgr_base->ctx->dc, context);
पूर्ण








अटल काष्ठा clk_mgr_funcs dce_funcs = अणु
	.get_dp_ref_clk_frequency = dce_get_dp_ref_freq_khz,
	.update_घड़ीs = dce_update_घड़ीs
पूर्ण;

व्योम dce_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	काष्ठा clk_mgr *base = &clk_mgr->base;
	काष्ठा dm_pp_अटल_घड़ी_info अटल_clk_info = अणु0पूर्ण;

	स_नकल(clk_mgr->max_clks_by_state,
		dce80_max_clks_by_state,
		माप(dce80_max_clks_by_state));

	base->ctx = ctx;
	base->funcs = &dce_funcs;

	clk_mgr->regs = &disp_clk_regs;
	clk_mgr->clk_mgr_shअगरt = &disp_clk_shअगरt;
	clk_mgr->clk_mgr_mask = &disp_clk_mask;
	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_भागider = 1000;
	clk_mgr->ss_on_dprefclk = false;

	अगर (dm_pp_get_अटल_घड़ीs(ctx, &अटल_clk_info))
		clk_mgr->max_clks_state = अटल_clk_info.max_घड़ीs_state;
	अन्यथा
		clk_mgr->max_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;
	clk_mgr->cur_min_clks_state = DM_PP_CLOCKS_STATE_INVALID;

	dce_घड़ी_पढ़ो_पूर्णांकegrated_info(clk_mgr);
	dce_घड़ी_पढ़ो_ss_info(clk_mgr);
पूर्ण

