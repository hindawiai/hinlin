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

#समावेश "dce112/dce112_clk_mgr.h"
#समावेश "dce110/dce110_clk_mgr.h"
#समावेश "dce120_clk_mgr.h"
#समावेश "dce100/dce_clk_mgr.h"
#समावेश "dce120/dce120_hw_sequencer.h"

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

/**
 * dce121_घड़ी_patch_xgmi_ss_info() - Save XGMI spपढ़ो spectrum info
 * @clk_mgr_dce: घड़ी manager पूर्णांकernal काष्ठाure
 *
 * Reads from VBIOS the XGMI spपढ़ो spectrum info and saves it within
 * the dce घड़ी manager. This operation will overग_लिखो the existing dprefclk
 * SS values अगर the vBIOS query succeeds. Otherwise, it करोes nothing. It also
 * sets the ->xgmi_enabled flag.
 */
अटल व्योम dce121_घड़ी_patch_xgmi_ss_info(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce)
अणु
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
			/*
			 * Currently क्रम DP Reference घड़ी we
			 * need only SS percentage क्रम
			 * करोwnspपढ़ो
			 */
			clk_mgr_dce->dprefclk_ss_percentage =
					info.spपढ़ो_spectrum_percentage;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dce12_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_dce = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dm_pp_घड़ी_क्रम_voltage_req घड़ी_voltage_req = अणु0पूर्ण;
	पूर्णांक max_pix_clk = dce_get_max_pixel_घड़ी_क्रम_all_paths(context);
	पूर्णांक patched_disp_clk = context->bw_ctx.bw.dce.dispclk_khz;

	/*TODO: W/A क्रम dal3 linux, investigate why this works */
	अगर (!clk_mgr_dce->dfs_bypass_active)
		patched_disp_clk = patched_disp_clk * 115 / 100;

	अगर (should_set_घड़ी(safe_to_lower, patched_disp_clk, clk_mgr_base->clks.dispclk_khz)) अणु
		घड़ी_voltage_req.clk_type = DM_PP_CLOCK_TYPE_DISPLAY_CLK;
		/*
		 * When xGMI is enabled, the display clk needs to be adjusted
		 * with the WAFL link's SS percentage.
		 */
		अगर (clk_mgr_dce->xgmi_enabled)
			patched_disp_clk = dce_adjust_dp_ref_freq_क्रम_ss(
					clk_mgr_dce, patched_disp_clk);
		घड़ी_voltage_req.घड़ीs_in_khz = patched_disp_clk;
		clk_mgr_base->clks.dispclk_khz = dce112_set_घड़ी(clk_mgr_base, patched_disp_clk);

		dm_pp_apply_घड़ी_क्रम_voltage_request(clk_mgr_base->ctx, &घड़ी_voltage_req);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, max_pix_clk, clk_mgr_base->clks.phyclk_khz)) अणु
		घड़ी_voltage_req.clk_type = DM_PP_CLOCK_TYPE_DISPLAYPHYCLK;
		घड़ी_voltage_req.घड़ीs_in_khz = max_pix_clk;
		clk_mgr_base->clks.phyclk_khz = max_pix_clk;

		dm_pp_apply_घड़ी_क्रम_voltage_request(clk_mgr_base->ctx, &घड़ी_voltage_req);
	पूर्ण
	dce11_pplib_apply_display_requirements(clk_mgr_base->ctx->dc, context);
पूर्ण


अटल काष्ठा clk_mgr_funcs dce120_funcs = अणु
	.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
	.update_घड़ीs = dce12_update_घड़ीs
पूर्ण;

व्योम dce120_clk_mgr_स्थिरruct(काष्ठा dc_context *ctx, काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dce_clk_mgr_स्थिरruct(ctx, clk_mgr);

	स_नकल(clk_mgr->max_clks_by_state,
		dce120_max_clks_by_state,
		माप(dce120_max_clks_by_state));

	clk_mgr->base.dprefclk_khz = 600000;
	clk_mgr->base.funcs = &dce120_funcs;
पूर्ण

व्योम dce121_clk_mgr_स्थिरruct(काष्ठा dc_context *ctx, काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dce120_clk_mgr_स्थिरruct(ctx, clk_mgr);
	clk_mgr->base.dprefclk_khz = 625000;

	/*
	 * The xGMI enabled info is used to determine अगर audio and display
	 * घड़ीs need to be adjusted with the WAFL link's SS info.
	 */
	अगर (dce121_xgmi_enabled(ctx->dc->hwseq))
		dce121_घड़ी_patch_xgmi_ss_info(clk_mgr);

पूर्ण

