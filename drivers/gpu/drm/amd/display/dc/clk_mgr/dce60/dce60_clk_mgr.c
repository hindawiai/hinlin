<शैली गुरु>
/*
 * Copyright 2020 Mauro Rossi <issor.oruam@gmail.com>
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
#समावेश "dce100/dce_clk_mgr.h"
#समावेश "dce110/dce110_clk_mgr.h"
#समावेश "dce60_clk_mgr.h"
#समावेश "reg_helper.h"
#समावेश "dmcu.h"
#समावेश "core_types.h"
#समावेश "dal_asic_id.h"

/*
 * Currently the रेजिस्टर shअगरts and masks in this file are used क्रम dce60
 * which has no DPREFCLK_CNTL रेजिस्टर
 * TODO: हटाओ this when DENTIST_DISPCLK_CNTL
 * is moved to dccg, where it beदीर्घs
 */
#समावेश "dce/dce_6_0_d.h"
#समावेश "dce/dce_6_0_sh_mask.h"

#घोषणा REG(reg) \
	(clk_mgr->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	clk_mgr->clk_mgr_shअगरt->field_name, clk_mgr->clk_mgr_mask->field_name

/* set रेजिस्टर offset */
#घोषणा SR(reg_name)\
	.reg_name = mm ## reg_name

अटल स्थिर काष्ठा clk_mgr_रेजिस्टरs disp_clk_regs = अणु
		CLK_COMMON_REG_LIST_DCE60_BASE()
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_shअगरt disp_clk_shअगरt = अणु
		CLK_COMMON_MASK_SH_LIST_DCE60_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा clk_mgr_mask disp_clk_mask = अणु
		CLK_COMMON_MASK_SH_LIST_DCE60_COMMON_BASE(_MASK)
पूर्ण;


/* Max घड़ी values क्रम each state indexed by "enum clocks_state": */
अटल स्थिर काष्ठा state_dependent_घड़ीs dce60_max_clks_by_state[] = अणु
/* ClocksStateInvalid - should not be used */
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/* ClocksStateUltraLow - not expected to be used क्रम DCE 6.0 */
अणु .display_clk_khz = 0, .pixel_clk_khz = 0 पूर्ण,
/* ClocksStateLow */
अणु .display_clk_khz = 352000, .pixel_clk_khz = 330000पूर्ण,
/* ClocksStateNominal */
अणु .display_clk_khz = 600000, .pixel_clk_khz = 400000 पूर्ण,
/* ClocksStatePerक्रमmance */
अणु .display_clk_khz = 600000, .pixel_clk_khz = 400000 पूर्ण पूर्ण;

अटल पूर्णांक dce60_get_dp_ref_freq_khz(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	पूर्णांक dprefclk_wभागider;
	पूर्णांक dp_ref_clk_khz;
	पूर्णांक target_भाग;

	/* DCE6 has no DPREFCLK_CNTL to पढ़ो DP Reference Clock source */

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

अटल व्योम dce60_pplib_apply_display_requirements(
	काष्ठा dc *dc,
	काष्ठा dc_state *context)
अणु
	काष्ठा dm_pp_display_configuration *pp_display_cfg = &context->pp_display_cfg;

	pp_display_cfg->avail_mclk_चयन_समय_us = dce110_get_min_vblank_समय_us(context);

	dce110_fill_display_configs(context, pp_display_cfg);

	अगर (स_भेद(&dc->current_state->pp_display_cfg, pp_display_cfg, माप(*pp_display_cfg)) !=  0)
		dm_pp_apply_display_requirements(dc->ctx, pp_display_cfg);
पूर्ण

अटल व्योम dce60_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
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
	dce60_pplib_apply_display_requirements(clk_mgr_base->ctx->dc, context);
पूर्ण








अटल काष्ठा clk_mgr_funcs dce60_funcs = अणु
	.get_dp_ref_clk_frequency = dce60_get_dp_ref_freq_khz,
	.update_घड़ीs = dce60_update_घड़ीs
पूर्ण;

व्योम dce60_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dce_clk_mgr_स्थिरruct(ctx, clk_mgr);

	स_नकल(clk_mgr->max_clks_by_state,
		dce60_max_clks_by_state,
		माप(dce60_max_clks_by_state));

	clk_mgr->regs = &disp_clk_regs;
	clk_mgr->clk_mgr_shअगरt = &disp_clk_shअगरt;
	clk_mgr->clk_mgr_mask = &disp_clk_mask;
	clk_mgr->base.funcs = &dce60_funcs;
पूर्ण

