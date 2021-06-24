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

#समावेश "core_types.h"
#समावेश "clk_mgr_internal.h"

#समावेश "dce/dce_11_2_d.h"
#समावेश "dce/dce_11_2_sh_mask.h"
#समावेश "dce100/dce_clk_mgr.h"
#समावेश "dce110/dce110_clk_mgr.h"
#समावेश "dce112_clk_mgr.h"
#समावेश "dal_asic_id.h"

/* set रेजिस्टर offset */
#घोषणा SR(reg_name)\
	.reg_name = mm ## reg_name

/* set रेजिस्टर offset with instance */
#घोषणा SRI(reg_name, block, id)\
	.reg_name = mm ## block ## id ## _ ## reg_name

अटल स्थिर काष्ठा clk_mgr_रेजिस्टरs disp_clk_regs = अणु
		CLK_COMMON_REG_LIST_DCE_BASE()
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_shअगरt disp_clk_shअगरt = अणु
		CLK_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_mask disp_clk_mask = अणु
		CLK_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(_MASK)
पूर्ण;

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


//TODO: हटाओ use the two broken करोwn functions
पूर्णांक dce112_set_घड़ी(काष्ठा clk_mgr *clk_mgr_base, पूर्णांक requested_clk_khz)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा bp_set_dce_घड़ी_parameters dce_clk_params;
	काष्ठा dc_bios *bp = clk_mgr_base->ctx->dc_bios;
	काष्ठा dc *dc = clk_mgr_base->ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	पूर्णांक actual_घड़ी = requested_clk_khz;
	/* Prepare to program display घड़ी*/
	स_रखो(&dce_clk_params, 0, माप(dce_clk_params));

	/* Make sure requested घड़ी isn't lower than minimum threshold*/
	requested_clk_khz = max(requested_clk_khz,
				clk_mgr_dce->base.dentist_vco_freq_khz / 62);

	dce_clk_params.target_घड़ी_frequency = requested_clk_khz;
	dce_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;
	dce_clk_params.घड़ी_प्रकारype = DCECLOCK_TYPE_DISPLAY_CLOCK;

	bp->funcs->set_dce_घड़ी(bp, &dce_clk_params);
	actual_घड़ी = dce_clk_params.target_घड़ी_frequency;

	/*
	 * from घातer करोwn, we need mark the घड़ी state as ClocksStateNominal
	 * from HWReset, so when resume we will call pplib voltage regulator.
	 */
	अगर (requested_clk_khz == 0)
		clk_mgr_dce->cur_min_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;

	/*Program DP ref Clock*/
	/*VBIOS will determine DPREFCLK frequency, so we करोn't set it*/
	dce_clk_params.target_घड़ी_frequency = 0;
	dce_clk_params.घड़ी_प्रकारype = DCECLOCK_TYPE_DPREFCLK;

	अगर (!((clk_mgr_base->ctx->asic_id.chip_family == FAMILY_AI) &&
	       ASICREV_IS_VEGA20_P(clk_mgr_base->ctx->asic_id.hw_पूर्णांकernal_rev)))
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK =
			(dce_clk_params.pll_id ==
					CLOCK_SOURCE_COMBO_DISPLAY_PLL0);
	अन्यथा
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK = false;

	bp->funcs->set_dce_घड़ी(bp, &dce_clk_params);

	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		अगर (dmcu && dmcu->funcs->is_dmcu_initialized(dmcu)) अणु
			अगर (clk_mgr_dce->dfs_bypass_disp_clk != actual_घड़ी)
				dmcu->funcs->set_psr_रुको_loop(dmcu,
						actual_घड़ी / 1000 / 7);
		पूर्ण
	पूर्ण

	clk_mgr_dce->dfs_bypass_disp_clk = actual_घड़ी;
	वापस actual_घड़ी;
पूर्ण

पूर्णांक dce112_set_dispclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_clk_khz)
अणु
	काष्ठा bp_set_dce_घड़ी_parameters dce_clk_params;
	काष्ठा dc_bios *bp = clk_mgr->base.ctx->dc_bios;
	काष्ठा dc *dc = clk_mgr->base.ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;
	पूर्णांक actual_घड़ी = requested_clk_khz;
	/* Prepare to program display घड़ी*/
	स_रखो(&dce_clk_params, 0, माप(dce_clk_params));

	/* Make sure requested घड़ी isn't lower than minimum threshold*/
	अगर (requested_clk_khz > 0)
		requested_clk_khz = max(requested_clk_khz,
				clk_mgr->base.dentist_vco_freq_khz / 62);

	dce_clk_params.target_घड़ी_frequency = requested_clk_khz;
	dce_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;
	dce_clk_params.घड़ी_प्रकारype = DCECLOCK_TYPE_DISPLAY_CLOCK;

	bp->funcs->set_dce_घड़ी(bp, &dce_clk_params);
	actual_घड़ी = dce_clk_params.target_घड़ी_frequency;

	/*
	 * from घातer करोwn, we need mark the घड़ी state as ClocksStateNominal
	 * from HWReset, so when resume we will call pplib voltage regulator.
	 */
	अगर (requested_clk_khz == 0)
		clk_mgr->cur_min_clks_state = DM_PP_CLOCKS_STATE_NOMINAL;


	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		अगर (dmcu && dmcu->funcs->is_dmcu_initialized(dmcu)) अणु
			अगर (clk_mgr->dfs_bypass_disp_clk != actual_घड़ी)
				dmcu->funcs->set_psr_रुको_loop(dmcu,
						actual_घड़ी / 1000 / 7);
		पूर्ण
	पूर्ण

	clk_mgr->dfs_bypass_disp_clk = actual_घड़ी;
	वापस actual_घड़ी;

पूर्ण

पूर्णांक dce112_set_dprefclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	काष्ठा bp_set_dce_घड़ी_parameters dce_clk_params;
	काष्ठा dc_bios *bp = clk_mgr->base.ctx->dc_bios;

	स_रखो(&dce_clk_params, 0, माप(dce_clk_params));

	/*Program DP ref Clock*/
	/*VBIOS will determine DPREFCLK frequency, so we करोn't set it*/
	dce_clk_params.target_घड़ी_frequency = 0;
	dce_clk_params.pll_id = CLOCK_SOURCE_ID_DFS;
	dce_clk_params.घड़ी_प्रकारype = DCECLOCK_TYPE_DPREFCLK;
	अगर (!((clk_mgr->base.ctx->asic_id.chip_family == FAMILY_AI) &&
	       ASICREV_IS_VEGA20_P(clk_mgr->base.ctx->asic_id.hw_पूर्णांकernal_rev)))
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK =
			(dce_clk_params.pll_id ==
					CLOCK_SOURCE_COMBO_DISPLAY_PLL0);
	अन्यथा
		dce_clk_params.flags.USE_GENLOCK_AS_SOURCE_FOR_DPREFCLK = false;

	bp->funcs->set_dce_घड़ी(bp, &dce_clk_params);

	/* Returns the dp_refclk that was set */
	वापस dce_clk_params.target_घड़ी_frequency;
पूर्ण

अटल व्योम dce112_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
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
		patched_disp_clk = dce112_set_घड़ी(clk_mgr_base, patched_disp_clk);
		clk_mgr_base->clks.dispclk_khz = patched_disp_clk;
	पूर्ण
	dce11_pplib_apply_display_requirements(clk_mgr_base->ctx->dc, context);
पूर्ण

अटल काष्ठा clk_mgr_funcs dce112_funcs = अणु
	.get_dp_ref_clk_frequency = dce_get_dp_ref_freq_khz,
	.update_घड़ीs = dce112_update_घड़ीs
पूर्ण;

व्योम dce112_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dce_clk_mgr_स्थिरruct(ctx, clk_mgr);

	स_नकल(clk_mgr->max_clks_by_state,
		dce112_max_clks_by_state,
		माप(dce112_max_clks_by_state));

	clk_mgr->regs = &disp_clk_regs;
	clk_mgr->clk_mgr_shअगरt = &disp_clk_shअगरt;
	clk_mgr->clk_mgr_mask = &disp_clk_mask;
	clk_mgr->base.funcs = &dce112_funcs;
पूर्ण
