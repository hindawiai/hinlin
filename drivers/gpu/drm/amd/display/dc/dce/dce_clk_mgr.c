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

#समावेश <linux/slab.h>

#समावेश "dce_clk_mgr.h"

#समावेश "reg_helper.h"
#समावेश "dmcu.h"
#समावेश "core_types.h"
#समावेश "dal_asic_id.h"

#घोषणा TO_DCE_CLK_MGR(घड़ीs)\
	container_of(घड़ीs, काष्ठा dce_clk_mgr, base)

#घोषणा REG(reg) \
	(clk_mgr_dce->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	clk_mgr_dce->clk_mgr_shअगरt->field_name, clk_mgr_dce->clk_mgr_mask->field_name

#घोषणा CTX \
	clk_mgr_dce->base.ctx
#घोषणा DC_LOGGER \
	clk_mgr->ctx->logger

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

अटल स्थिर काष्ठा state_dependent_घड़ीs dce110_max_clks_by_state[] = अणु
/*ClocksStateInvalid - should not be used*/
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/*ClocksStateUltraLow - currently by HW design team not supposed to be used*/
अणु .display_clk_khz = 352000, .pixel_clk_khz = 330000 पूर्ण,
/*ClocksStateLow*/
अणु .display_clk_khz = 352000, .pixel_clk_khz = 330000 पूर्ण,
/*ClocksStateNominal*/
अणु .display_clk_khz = 467000, .pixel_clk_khz = 400000 पूर्ण,
/*ClocksStatePerक्रमmance*/
अणु .display_clk_khz = 643000, .pixel_clk_khz = 400000 पूर्ण पूर्ण;

अटल स्थिर काष्ठा state_dependent_घड़ीs dce112_max_clks_by_state[] = अणु
/*ClocksStateInvalid - should not be used*/
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/*ClocksStateUltraLow - currently by HW design team not supposed to be used*/
अणु .display_clk_khz = 389189, .pixel_clk_khz = 346672 पूर्ण,
/*ClocksStateLow*/
अणु .display_clk_khz = 459000, .pixel_clk_khz = 400000 पूर्ण,
/*ClocksStateNominal*/
अणु .display_clk_khz = 667000, .pixel_clk_khz = 600000 पूर्ण,
/*ClocksStatePerक्रमmance*/
अणु .display_clk_khz = 1132000, .pixel_clk_khz = 600000 पूर्ण पूर्ण;

अटल स्थिर काष्ठा state_dependent_घड़ीs dce120_max_clks_by_state[] = अणु
/*ClocksStateInvalid - should not be used*/
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/*ClocksStateUltraLow - currently by HW design team not supposed to be used*/
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/*ClocksStateLow*/
अणु .display_clk_khz = 460000, .pixel_clk_khz = 400000 पूर्ण,
/*ClocksStateNominal*/
अणु .display_clk_khz = 670000, .pixel_clk_khz = 600000 पूर्ण,
/*ClocksStatePerक्रमmance*/
अणु .display_clk_khz = 1133000, .pixel_clk_khz = 600000 पूर्ण पूर्ण;

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
अटल पूर्णांक clk_mgr_adjust_dp_ref_freq_क्रम_ss(काष्ठा dce_clk_mgr *clk_mgr_dce, पूर्णांक dp_ref_clk_khz)
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

अटल पूर्णांक dce_get_dp_ref_freq_khz(काष्ठा clk_mgr *clk_mgr)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	पूर्णांक dprefclk_wभागider;
	पूर्णांक dprefclk_src_sel;
	पूर्णांक dp_ref_clk_khz = 600000;
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
		* clk_mgr_dce->dentist_vco_freq_khz) / target_भाग;

	वापस clk_mgr_adjust_dp_ref_freq_क्रम_ss(clk_mgr_dce, dp_ref_clk_khz);
पूर्ण

पूर्णांक dce12_get_dp_ref_freq_khz(काष्ठा clk_mgr *clk_mgr)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);

	वापस clk_mgr_adjust_dp_ref_freq_क्रम_ss(clk_mgr_dce, clk_mgr_dce->dprefclk_khz);
पूर्ण

/* unit: in_khz beक्रमe mode set, get pixel घड़ी from context. ASIC रेजिस्टर
 * may not be programmed yet
 */
अटल uपूर्णांक32_t get_max_pixel_घड़ी_क्रम_all_paths(काष्ठा dc_state *context)
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

अटल क्रमागत dm_pp_घड़ीs_state dce_get_required_घड़ीs_state(
	काष्ठा clk_mgr *clk_mgr,
	काष्ठा dc_state *context)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	पूर्णांक i;
	क्रमागत dm_pp_घड़ीs_state low_req_clk;
	पूर्णांक max_pix_clk = get_max_pixel_घड़ी_क्रम_all_paths(context);

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

अटल पूर्णांक dce_set_घड़ी(
	काष्ठा clk_mgr *clk_mgr,
	पूर्णांक requested_clk_khz)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	काष्ठा bp_pixel_घड़ी_parameters pxl_clk_params = अणु 0 पूर्ण;
	काष्ठा dc_bios *bp = clk_mgr->ctx->dc_bios;
	पूर्णांक actual_घड़ी = requested_clk_khz;
	काष्ठा dmcu *dmcu = clk_mgr_dce->base.ctx->dc->res_pool->dmcu;

	/* Make sure requested घड़ी isn't lower than minimum threshold*/
	अगर (requested_clk_khz > 0)
		requested_clk_khz = max(requested_clk_khz,
				clk_mgr_dce->dentist_vco_freq_khz / 64);

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

पूर्णांक dce112_set_घड़ी(काष्ठा clk_mgr *clk_mgr, पूर्णांक requested_clk_khz)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	काष्ठा bp_set_dce_घड़ी_parameters dce_clk_params;
	काष्ठा dc_bios *bp = clk_mgr->ctx->dc_bios;
	काष्ठा dc *core_dc = clk_mgr->ctx->dc;
	काष्ठा dmcu *dmcu = core_dc->res_pool->dmcu;
	पूर्णांक actual_घड़ी = requested_clk_khz;
	/* Prepare to program display घड़ी*/
	स_रखो(&dce_clk_params, 0, माप(dce_clk_params));

	/* Make sure requested घड़ी isn't lower than minimum threshold*/
	अगर (requested_clk_khz > 0)
		requested_clk_khz = max(requested_clk_khz,
				clk_mgr_dce->dentist_vco_freq_khz / 62);

	dce_clk_params.target_घड़ी_frequency = requested_clk_khz;
	dce_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;
	dce_clk_params.घड़ी_प्रकारype = DCECLOCK_TYPE_DISPLAY_CLOCK;

	bp->funcs->set_dce_घड़ी(bp, &dce_clk_params);
	actual_घड़ी = dce_clk_params.target_घड़ी_frequency;

	/* from घातer करोwn, we need mark the घड़ी state as ClocksStateNominal
	 * from HWReset, so when resume we will call pplib voltage regulator.*/
	अगर (requested_clk_khz == 0)
		clk_mgr_dce->cur_min_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;

	/*Program DP ref Clock*/
	/*VBIOS will determine DPREFCLK frequency, so we करोn't set it*/
	dce_clk_params.target_घड़ी_frequency = 0;
	dce_clk_params.घड़ी_प्रकारype = DCECLOCK_TYPE_DPREFCLK;

	अगर (!((clk_mgr->ctx->asic_id.chip_family == FAMILY_AI) &&
	       ASICREV_IS_VEGA20_P(clk_mgr->ctx->asic_id.hw_पूर्णांकernal_rev)))
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK =
			(dce_clk_params.pll_id ==
					CLOCK_SOURCE_COMBO_DISPLAY_PLL0);
	अन्यथा
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK = false;

	bp->funcs->set_dce_घड़ी(bp, &dce_clk_params);

	अगर (!IS_FPGA_MAXIMUS_DC(core_dc->ctx->dce_environment)) अणु
		अगर (dmcu && dmcu->funcs->is_dmcu_initialized(dmcu)) अणु
			अगर (clk_mgr_dce->dfs_bypass_disp_clk != actual_घड़ी)
				dmcu->funcs->set_psr_रुको_loop(dmcu,
						actual_घड़ी / 1000 / 7);
		पूर्ण
	पूर्ण

	clk_mgr_dce->dfs_bypass_disp_clk = actual_घड़ी;
	वापस actual_घड़ी;
पूर्ण

अटल व्योम dce_घड़ी_पढ़ो_पूर्णांकegrated_info(काष्ठा dce_clk_mgr *clk_mgr_dce)
अणु
	काष्ठा dc_debug_options *debug = &clk_mgr_dce->base.ctx->dc->debug;
	काष्ठा dc_bios *bp = clk_mgr_dce->base.ctx->dc_bios;
	काष्ठा पूर्णांकegrated_info info = अणु अणु अणु 0 पूर्ण पूर्ण पूर्ण;
	काष्ठा dc_firmware_info fw_info = अणु अणु 0 पूर्ण पूर्ण;
	पूर्णांक i;

	अगर (bp->पूर्णांकegrated_info)
		info = *bp->पूर्णांकegrated_info;

	clk_mgr_dce->dentist_vco_freq_khz = info.dentist_vco_freq;
	अगर (clk_mgr_dce->dentist_vco_freq_khz == 0) अणु
		bp->funcs->get_firmware_info(bp, &fw_info);
		clk_mgr_dce->dentist_vco_freq_khz =
			fw_info.smu_gpu_pll_output_freq;
		अगर (clk_mgr_dce->dentist_vco_freq_khz == 0)
			clk_mgr_dce->dentist_vco_freq_khz = 3600000;
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
		अगर (info.disp_clk_voltage[i].max_supported_clk >= 100000)
			clk_mgr_dce->max_clks_by_state[clk_state].display_clk_khz =
				info.disp_clk_voltage[i].max_supported_clk;
	पूर्ण

	अगर (!debug->disable_dfs_bypass && bp->पूर्णांकegrated_info)
		अगर (bp->पूर्णांकegrated_info->gpu_cap_info & DFS_BYPASS_ENABLE)
			clk_mgr_dce->dfs_bypass_enabled = true;
पूर्ण

व्योम dce_घड़ी_पढ़ो_ss_info(काष्ठा dce_clk_mgr *clk_mgr_dce)
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

/**
 * dce121_घड़ी_patch_xgmi_ss_info() - Save XGMI spपढ़ो spectrum info
 * @clk_mgr: घड़ी manager base काष्ठाure
 *
 * Reads from VBIOS the XGMI spपढ़ो spectrum info and saves it within
 * the dce घड़ी manager. This operation will overग_लिखो the existing dprefclk
 * SS values अगर the vBIOS query succeeds. Otherwise, it करोes nothing. It also
 * sets the ->xgmi_enabled flag.
 */
व्योम dce121_घड़ी_patch_xgmi_ss_info(काष्ठा clk_mgr *clk_mgr)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	क्रमागत bp_result result;
	काष्ठा spपढ़ो_spectrum_info info = अणु अणु 0 पूर्ण पूर्ण;
	काष्ठा dc_bios *bp = clk_mgr_dce->base.ctx->dc_bios;

	clk_mgr_dce->xgmi_enabled = false;

	result = bp->funcs->get_spपढ़ो_spectrum_info(bp, AS_SIGNAL_TYPE_XGMI,
						     0, &info);
	अगर (result == BP_RESULT_OK && info.spपढ़ो_spectrum_percentage != 0) अणु
		clk_mgr_dce->xgmi_enabled = true;
		clk_mgr_dce->ss_on_dprefclk = true;
		clk_mgr_dce->dprefclk_ss_भागider =
				info.spपढ़ो_percentage_भागider;

		अगर (info.type.CENTER_MODE == 0) अणु
			/* Currently क्रम DP Reference घड़ी we
			 * need only SS percentage क्रम
			 * करोwnspपढ़ो */
			clk_mgr_dce->dprefclk_ss_percentage =
					info.spपढ़ो_spectrum_percentage;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dce110_fill_display_configs(
	स्थिर काष्ठा dc_state *context,
	काष्ठा dm_pp_display_configuration *pp_display_cfg)
अणु
	पूर्णांक j;
	पूर्णांक num_cfgs = 0;

	क्रम (j = 0; j < context->stream_count; j++) अणु
		पूर्णांक k;

		स्थिर काष्ठा dc_stream_state *stream = context->streams[j];
		काष्ठा dm_pp_single_disp_config *cfg =
			&pp_display_cfg->disp_configs[num_cfgs];
		स्थिर काष्ठा pipe_ctx *pipe_ctx = शून्य;

		क्रम (k = 0; k < MAX_PIPES; k++)
			अगर (stream == context->res_ctx.pipe_ctx[k].stream) अणु
				pipe_ctx = &context->res_ctx.pipe_ctx[k];
				अवरोध;
			पूर्ण

		ASSERT(pipe_ctx != शून्य);

		/* only notअगरy active stream */
		अगर (stream->dpms_off)
			जारी;

		num_cfgs++;
		cfg->संकेत = pipe_ctx->stream->संकेत;
		cfg->pipe_idx = pipe_ctx->stream_res.tg->inst;
		cfg->src_height = stream->src.height;
		cfg->src_width = stream->src.width;
		cfg->ddi_channel_mapping =
			stream->link->ddi_channel_mapping.raw;
		cfg->transmitter =
			stream->link->link_enc->transmitter;
		cfg->link_settings.lane_count =
			stream->link->cur_link_settings.lane_count;
		cfg->link_settings.link_rate =
			stream->link->cur_link_settings.link_rate;
		cfg->link_settings.link_spपढ़ो =
			stream->link->cur_link_settings.link_spपढ़ो;
		cfg->sym_घड़ी = stream->phy_pix_clk;
		/* Round v_refresh*/
		cfg->v_refresh = stream->timing.pix_clk_100hz * 100;
		cfg->v_refresh /= stream->timing.h_total;
		cfg->v_refresh = (cfg->v_refresh + stream->timing.v_total / 2)
							/ stream->timing.v_total;
	पूर्ण

	pp_display_cfg->display_count = num_cfgs;
पूर्ण

अटल uपूर्णांक32_t dce110_get_min_vblank_समय_us(स्थिर काष्ठा dc_state *context)
अणु
	uपूर्णांक8_t j;
	uपूर्णांक32_t min_vertical_blank_समय = -1;

	क्रम (j = 0; j < context->stream_count; j++) अणु
		काष्ठा dc_stream_state *stream = context->streams[j];
		uपूर्णांक32_t vertical_blank_in_pixels = 0;
		uपूर्णांक32_t vertical_blank_समय = 0;

		vertical_blank_in_pixels = stream->timing.h_total *
			(stream->timing.v_total
			 - stream->timing.v_addressable);

		vertical_blank_समय = vertical_blank_in_pixels
			* 10000 / stream->timing.pix_clk_100hz;

		अगर (min_vertical_blank_समय > vertical_blank_समय)
			min_vertical_blank_समय = vertical_blank_समय;
	पूर्ण

	वापस min_vertical_blank_समय;
पूर्ण

अटल पूर्णांक determine_sclk_from_bounding_box(
		स्थिर काष्ठा dc *dc,
		पूर्णांक required_sclk)
अणु
	पूर्णांक i;

	/*
	 * Some asics करो not give us sclk levels, so we just report the actual
	 * required sclk
	 */
	अगर (dc->sclk_lvls.num_levels == 0)
		वापस required_sclk;

	क्रम (i = 0; i < dc->sclk_lvls.num_levels; i++) अणु
		अगर (dc->sclk_lvls.घड़ीs_in_khz[i] >= required_sclk)
			वापस dc->sclk_lvls.घड़ीs_in_khz[i];
	पूर्ण
	/*
	 * even maximum level could not satisfy requirement, this
	 * is unexpected at this stage, should have been caught at
	 * validation समय
	 */
	ASSERT(0);
	वापस dc->sclk_lvls.घड़ीs_in_khz[dc->sclk_lvls.num_levels - 1];
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

अटल व्योम dce11_pplib_apply_display_requirements(
	काष्ठा dc *dc,
	काष्ठा dc_state *context)
अणु
	काष्ठा dm_pp_display_configuration *pp_display_cfg = &context->pp_display_cfg;

	pp_display_cfg->all_displays_in_sync =
		context->bw_ctx.bw.dce.all_displays_in_sync;
	pp_display_cfg->nb_pstate_चयन_disable =
			context->bw_ctx.bw.dce.nbp_state_change_enable == false;
	pp_display_cfg->cpu_cc6_disable =
			context->bw_ctx.bw.dce.cpuc_state_change_enable == false;
	pp_display_cfg->cpu_pstate_disable =
			context->bw_ctx.bw.dce.cpup_state_change_enable == false;
	pp_display_cfg->cpu_pstate_separation_समय =
			context->bw_ctx.bw.dce.blackout_recovery_समय_us;

	pp_display_cfg->min_memory_घड़ी_khz = context->bw_ctx.bw.dce.yclk_khz
		/ MEMORY_TYPE_MULTIPLIER_CZ;

	pp_display_cfg->min_engine_घड़ी_khz = determine_sclk_from_bounding_box(
			dc,
			context->bw_ctx.bw.dce.sclk_khz);

	/*
	 * As workaround क्रम >4x4K lightup set dcfघड़ी to min_engine_घड़ी value.
	 * This is not required क्रम less than 5 displays,
	 * thus करोn't request decfclk in dc to aव्योम impact
	 * on घातer saving.
	 *
	 */
	pp_display_cfg->min_dcfघड़ी_khz = (context->stream_count > 4)?
			pp_display_cfg->min_engine_घड़ी_khz : 0;

	pp_display_cfg->min_engine_घड़ी_deep_sleep_khz
			= context->bw_ctx.bw.dce.sclk_deep_sleep_khz;

	pp_display_cfg->avail_mclk_चयन_समय_us =
						dce110_get_min_vblank_समय_us(context);
	/* TODO: dce11.2*/
	pp_display_cfg->avail_mclk_चयन_समय_in_disp_active_us = 0;

	pp_display_cfg->disp_clk_khz = dc->res_pool->clk_mgr->clks.dispclk_khz;

	dce110_fill_display_configs(context, pp_display_cfg);

	/* TODO: is this still applicable?*/
	अगर (pp_display_cfg->display_count == 1) अणु
		स्थिर काष्ठा dc_crtc_timing *timing =
			&context->streams[0]->timing;

		pp_display_cfg->crtc_index =
			pp_display_cfg->disp_configs[0].pipe_idx;
		pp_display_cfg->line_समय_in_us = timing->h_total * 10000 / timing->pix_clk_100hz;
	पूर्ण

	अगर (स_भेद(&dc->current_state->pp_display_cfg, pp_display_cfg, माप(*pp_display_cfg)) !=  0)
		dm_pp_apply_display_requirements(dc->ctx, pp_display_cfg);
पूर्ण

अटल व्योम dce_update_घड़ीs(काष्ठा clk_mgr *clk_mgr,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	काष्ठा dm_pp_घातer_level_change_request level_change_req;
	पूर्णांक patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A क्रम dal3 linux, investigate why this works */
	अगर (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	level_change_req.घातer_level = dce_get_required_घड़ीs_state(clk_mgr, context);
	/* get max घड़ी state from PPLIB */
	अगर ((level_change_req.घातer_level < clk_mgr_dce->cur_min_clks_state && safe_to_lower)
			|| level_change_req.घातer_level > clk_mgr_dce->cur_min_clks_state) अणु
		अगर (dm_pp_apply_घातer_level_change_request(clk_mgr->ctx, &level_change_req))
			clk_mgr_dce->cur_min_clks_state = level_change_req.घातer_level;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, patched_disp_clk, clk_mgr->clks.dispclk_khz)) अणु
		patched_disp_clk = dce_set_घड़ी(clk_mgr, patched_disp_clk);
		clk_mgr->clks.dispclk_khz = patched_disp_clk;
	पूर्ण
	dce_pplib_apply_display_requirements(clk_mgr->ctx->dc, context);
पूर्ण

अटल व्योम dce11_update_घड़ीs(काष्ठा clk_mgr *clk_mgr,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	काष्ठा dm_pp_घातer_level_change_request level_change_req;
	पूर्णांक patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A क्रम dal3 linux, investigate why this works */
	अगर (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	level_change_req.घातer_level = dce_get_required_घड़ीs_state(clk_mgr, context);
	/* get max घड़ी state from PPLIB */
	अगर ((level_change_req.घातer_level < clk_mgr_dce->cur_min_clks_state && safe_to_lower)
			|| level_change_req.घातer_level > clk_mgr_dce->cur_min_clks_state) अणु
		अगर (dm_pp_apply_घातer_level_change_request(clk_mgr->ctx, &level_change_req))
			clk_mgr_dce->cur_min_clks_state = level_change_req.घातer_level;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, patched_disp_clk, clk_mgr->clks.dispclk_khz)) अणु
		context->bw_ctx.bw.dce.dispclk_khz = dce_set_घड़ी(clk_mgr, patched_disp_clk);
		clk_mgr->clks.dispclk_khz = patched_disp_clk;
	पूर्ण
	dce11_pplib_apply_display_requirements(clk_mgr->ctx->dc, context);
पूर्ण

अटल व्योम dce112_update_घड़ीs(काष्ठा clk_mgr *clk_mgr,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	काष्ठा dm_pp_घातer_level_change_request level_change_req;
	पूर्णांक patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A क्रम dal3 linux, investigate why this works */
	अगर (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	level_change_req.घातer_level = dce_get_required_घड़ीs_state(clk_mgr, context);
	/* get max घड़ी state from PPLIB */
	अगर ((level_change_req.घातer_level < clk_mgr_dce->cur_min_clks_state && safe_to_lower)
			|| level_change_req.घातer_level > clk_mgr_dce->cur_min_clks_state) अणु
		अगर (dm_pp_apply_घातer_level_change_request(clk_mgr->ctx, &level_change_req))
			clk_mgr_dce->cur_min_clks_state = level_change_req.घातer_level;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, patched_disp_clk, clk_mgr->clks.dispclk_khz)) अणु
		patched_disp_clk = dce112_set_घड़ी(clk_mgr, patched_disp_clk);
		clk_mgr->clks.dispclk_khz = patched_disp_clk;
	पूर्ण
	dce11_pplib_apply_display_requirements(clk_mgr->ctx->dc, context);
पूर्ण

अटल व्योम dce12_update_घड़ीs(काष्ठा clk_mgr *clk_mgr,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(clk_mgr);
	काष्ठा dm_pp_घड़ी_क्रम_voltage_req घड़ी_voltage_req = अणु0पूर्ण;
	पूर्णांक max_pix_clk = get_max_pixel_घड़ी_क्रम_all_paths(context);
	पूर्णांक patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A क्रम dal3 linux, investigate why this works */
	अगर (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	अगर (should_set_घड़ी(safe_to_lower, patched_disp_clk, clk_mgr->clks.dispclk_khz)) अणु
		घड़ी_voltage_req.clk_type = DM_PP_CLOCK_TYPE_DISPLAY_CLK;
		/*
		 * When xGMI is enabled, the display clk needs to be adjusted
		 * with the WAFL link's SS percentage.
		 */
		अगर (clk_mgr_dce->xgmi_enabled)
			patched_disp_clk = clk_mgr_adjust_dp_ref_freq_क्रम_ss(
					clk_mgr_dce, patched_disp_clk);
		घड़ी_voltage_req.घड़ीs_in_khz = patched_disp_clk;
		clk_mgr->clks.dispclk_khz = dce112_set_घड़ी(clk_mgr, patched_disp_clk);

		dm_pp_apply_घड़ी_क्रम_voltage_request(clk_mgr->ctx, &घड़ी_voltage_req);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, max_pix_clk, clk_mgr->clks.phyclk_khz)) अणु
		घड़ी_voltage_req.clk_type = DM_PP_CLOCK_TYPE_DISPLAYPHYCLK;
		घड़ी_voltage_req.घड़ीs_in_khz = max_pix_clk;
		clk_mgr->clks.phyclk_khz = max_pix_clk;

		dm_pp_apply_घड़ी_क्रम_voltage_request(clk_mgr->ctx, &घड़ी_voltage_req);
	पूर्ण
	dce11_pplib_apply_display_requirements(clk_mgr->ctx->dc, context);
पूर्ण

अटल स्थिर काष्ठा clk_mgr_funcs dce120_funcs = अणु
	.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
	.update_घड़ीs = dce12_update_घड़ीs
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_funcs dce112_funcs = अणु
	.get_dp_ref_clk_frequency = dce_get_dp_ref_freq_khz,
	.update_घड़ीs = dce112_update_घड़ीs
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_funcs dce110_funcs = अणु
	.get_dp_ref_clk_frequency = dce_get_dp_ref_freq_khz,
	.update_घड़ीs = dce11_update_घड़ीs,
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_funcs dce_funcs = अणु
	.get_dp_ref_clk_frequency = dce_get_dp_ref_freq_khz,
	.update_घड़ीs = dce_update_घड़ीs
पूर्ण;

अटल व्योम dce_clk_mgr_स्थिरruct(
	काष्ठा dce_clk_mgr *clk_mgr_dce,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा clk_mgr_रेजिस्टरs *regs,
	स्थिर काष्ठा clk_mgr_shअगरt *clk_shअगरt,
	स्थिर काष्ठा clk_mgr_mask *clk_mask)
अणु
	काष्ठा clk_mgr *base = &clk_mgr_dce->base;
	काष्ठा dm_pp_अटल_घड़ी_info अटल_clk_info = अणु0पूर्ण;

	base->ctx = ctx;
	base->funcs = &dce_funcs;

	clk_mgr_dce->regs = regs;
	clk_mgr_dce->clk_mgr_shअगरt = clk_shअगरt;
	clk_mgr_dce->clk_mgr_mask = clk_mask;

	clk_mgr_dce->dfs_bypass_disp_clk = 0;

	clk_mgr_dce->dprefclk_ss_percentage = 0;
	clk_mgr_dce->dprefclk_ss_भागider = 1000;
	clk_mgr_dce->ss_on_dprefclk = false;


	अगर (dm_pp_get_अटल_घड़ीs(ctx, &अटल_clk_info))
		clk_mgr_dce->max_clks_state = अटल_clk_info.max_घड़ीs_state;
	अन्यथा
		clk_mgr_dce->max_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;
	clk_mgr_dce->cur_min_clks_state = DM_PP_CLOCKS_STATE_INVALID;

	dce_घड़ी_पढ़ो_पूर्णांकegrated_info(clk_mgr_dce);
	dce_घड़ी_पढ़ो_ss_info(clk_mgr_dce);
पूर्ण

काष्ठा clk_mgr *dce_clk_mgr_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा clk_mgr_रेजिस्टरs *regs,
	स्थिर काष्ठा clk_mgr_shअगरt *clk_shअगरt,
	स्थिर काष्ठा clk_mgr_mask *clk_mask)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = kzalloc(माप(*clk_mgr_dce), GFP_KERNEL);

	अगर (clk_mgr_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	स_नकल(clk_mgr_dce->max_clks_by_state,
		dce80_max_clks_by_state,
		माप(dce80_max_clks_by_state));

	dce_clk_mgr_स्थिरruct(
		clk_mgr_dce, ctx, regs, clk_shअगरt, clk_mask);

	वापस &clk_mgr_dce->base;
पूर्ण

काष्ठा clk_mgr *dce110_clk_mgr_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा clk_mgr_रेजिस्टरs *regs,
	स्थिर काष्ठा clk_mgr_shअगरt *clk_shअगरt,
	स्थिर काष्ठा clk_mgr_mask *clk_mask)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = kzalloc(माप(*clk_mgr_dce), GFP_KERNEL);

	अगर (clk_mgr_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	स_नकल(clk_mgr_dce->max_clks_by_state,
		dce110_max_clks_by_state,
		माप(dce110_max_clks_by_state));

	dce_clk_mgr_स्थिरruct(
		clk_mgr_dce, ctx, regs, clk_shअगरt, clk_mask);

	clk_mgr_dce->base.funcs = &dce110_funcs;

	वापस &clk_mgr_dce->base;
पूर्ण

काष्ठा clk_mgr *dce112_clk_mgr_create(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा clk_mgr_रेजिस्टरs *regs,
	स्थिर काष्ठा clk_mgr_shअगरt *clk_shअगरt,
	स्थिर काष्ठा clk_mgr_mask *clk_mask)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = kzalloc(माप(*clk_mgr_dce), GFP_KERNEL);

	अगर (clk_mgr_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	स_नकल(clk_mgr_dce->max_clks_by_state,
		dce112_max_clks_by_state,
		माप(dce112_max_clks_by_state));

	dce_clk_mgr_स्थिरruct(
		clk_mgr_dce, ctx, regs, clk_shअगरt, clk_mask);

	clk_mgr_dce->base.funcs = &dce112_funcs;

	वापस &clk_mgr_dce->base;
पूर्ण

काष्ठा clk_mgr *dce120_clk_mgr_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = kzalloc(माप(*clk_mgr_dce), GFP_KERNEL);

	अगर (clk_mgr_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	स_नकल(clk_mgr_dce->max_clks_by_state,
		dce120_max_clks_by_state,
		माप(dce120_max_clks_by_state));

	dce_clk_mgr_स्थिरruct(
		clk_mgr_dce, ctx, शून्य, शून्य, शून्य);

	clk_mgr_dce->dprefclk_khz = 600000;
	clk_mgr_dce->base.funcs = &dce120_funcs;

	वापस &clk_mgr_dce->base;
पूर्ण

काष्ठा clk_mgr *dce121_clk_mgr_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = kzalloc(माप(*clk_mgr_dce),
						  GFP_KERNEL);

	अगर (clk_mgr_dce == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	स_नकल(clk_mgr_dce->max_clks_by_state, dce120_max_clks_by_state,
	       माप(dce120_max_clks_by_state));

	dce_clk_mgr_स्थिरruct(clk_mgr_dce, ctx, शून्य, शून्य, शून्य);

	clk_mgr_dce->dprefclk_khz = 625000;
	clk_mgr_dce->base.funcs = &dce120_funcs;

	वापस &clk_mgr_dce->base;
पूर्ण

व्योम dce_clk_mgr_destroy(काष्ठा clk_mgr **clk_mgr)
अणु
	काष्ठा dce_clk_mgr *clk_mgr_dce = TO_DCE_CLK_MGR(*clk_mgr);

	kमुक्त(clk_mgr_dce);
	*clk_mgr = शून्य;
पूर्ण
