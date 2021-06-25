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

#समावेश "dccg.h"
#समावेश "clk_mgr_internal.h"

// For dce12_get_dp_ref_freq_khz
#समावेश "dce100/dce_clk_mgr.h"

// For dcn20_update_घड़ीs_update_dpp_dto
#समावेश "dcn20/dcn20_clk_mgr.h"

#समावेश "vg_clk_mgr.h"
#समावेश "dcn301_smu.h"
#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dm_helpers.h"

#समावेश "atomfirmware.h"
#समावेश "vangogh_ip_offset.h"
#समावेश "clk/clk_11_5_0_offset.h"
#समावेश "clk/clk_11_5_0_sh_mask.h"

/* Constants */

#घोषणा LPDDR_MEM_RETRAIN_LATENCY 4.977 /* Number obtained from LPDDR4 Training Counter Requirement करोc */

/* Macros */

#घोषणा TO_CLK_MGR_VGH(clk_mgr)\
	container_of(clk_mgr, काष्ठा clk_mgr_vgh, base)

#घोषणा REG(reg_name) \
	(CLK_BASE.instance[0].segment[mm ## reg_name ## _BASE_IDX] + mm ## reg_name)

/* TODO: evaluate how to lower or disable all dcn घड़ीs in screen off हाल */
अटल पूर्णांक vg_get_active_display_cnt_wa(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i, display_count;
	bool पंचांगds_present = false;

	display_count = 0;
	क्रम (i = 0; i < context->stream_count; i++) अणु
		स्थिर काष्ठा dc_stream_state *stream = context->streams[i];

		अगर (stream->संकेत == SIGNAL_TYPE_HDMI_TYPE_A ||
				stream->संकेत == SIGNAL_TYPE_DVI_SINGLE_LINK ||
				stream->संकेत == SIGNAL_TYPE_DVI_DUAL_LINK)
			पंचांगds_present = true;
	पूर्ण

	क्रम (i = 0; i < dc->link_count; i++) अणु
		स्थिर काष्ठा dc_link *link = dc->links[i];

		/* abusing the fact that the dig and phy are coupled to see अगर the phy is enabled */
		अगर (link->link_enc->funcs->is_dig_enabled &&
				link->link_enc->funcs->is_dig_enabled(link->link_enc))
			display_count++;
	पूर्ण

	/* WA क्रम hang on HDMI after display off back back on*/
	अगर (display_count == 0 && पंचांगds_present)
		display_count = 1;

	वापस display_count;
पूर्ण

व्योम vg_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dc_घड़ीs *new_घड़ीs = &context->bw_ctx.bw.dcn.clk;
	काष्ठा dc *dc = clk_mgr_base->ctx->dc;
	पूर्णांक display_count;
	bool update_dppclk = false;
	bool update_dispclk = false;
	bool dpp_घड़ी_lowered = false;

	अगर (dc->work_arounds.skip_घड़ी_update)
		वापस;

	/*
	 * अगर it is safe to lower, but we are alपढ़ोy in the lower state, we करोn't have to करो anything
	 * also अगर safe to lower is false, we just go in the higher state
	 */
	अगर (safe_to_lower) अणु
		/* check that we're not alपढ़ोy in lower */
		अगर (clk_mgr_base->clks.pwr_state != DCN_PWR_STATE_LOW_POWER) अणु

			display_count = vg_get_active_display_cnt_wa(dc, context);
			/* अगर we can go lower, go lower */
			अगर (display_count == 0) अणु
				जोड़ display_idle_optimization_u idle_info = अणु 0 पूर्ण;

				idle_info.idle_info.df_request_disabled = 1;
				idle_info.idle_info.phy_ref_clk_off = 1;

				dcn301_smu_set_display_idle_optimization(clk_mgr, idle_info.data);
				/* update घातer state */
				clk_mgr_base->clks.pwr_state = DCN_PWR_STATE_LOW_POWER;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* check that we're not alपढ़ोy in D0 */
		अगर (clk_mgr_base->clks.pwr_state != DCN_PWR_STATE_MISSION_MODE) अणु
			जोड़ display_idle_optimization_u idle_info = अणु 0 पूर्ण;

			dcn301_smu_set_display_idle_optimization(clk_mgr, idle_info.data);
			/* update घातer state */
			clk_mgr_base->clks.pwr_state = DCN_PWR_STATE_MISSION_MODE;
		पूर्ण
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dcfclk_khz, clk_mgr_base->clks.dcfclk_khz) && !dc->debug.disable_min_fclk) अणु
		clk_mgr_base->clks.dcfclk_khz = new_घड़ीs->dcfclk_khz;
		dcn301_smu_set_hard_min_dcfclk(clk_mgr, clk_mgr_base->clks.dcfclk_khz);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower,
			new_घड़ीs->dcfclk_deep_sleep_khz, clk_mgr_base->clks.dcfclk_deep_sleep_khz) && !dc->debug.disable_min_fclk) अणु
		clk_mgr_base->clks.dcfclk_deep_sleep_khz = new_घड़ीs->dcfclk_deep_sleep_khz;
		dcn301_smu_set_min_deep_sleep_dcfclk(clk_mgr, clk_mgr_base->clks.dcfclk_deep_sleep_khz);
	पूर्ण

	// workaround: Limit dppclk to 100Mhz to aव्योम lower eDP panel चयन to plus 4K monitor underflow.
	अगर (!IS_DIAG_DC(dc->ctx->dce_environment)) अणु
		अगर (new_घड़ीs->dppclk_khz < 100000)
			new_घड़ीs->dppclk_khz = 100000;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dppclk_khz, clk_mgr->base.clks.dppclk_khz)) अणु
		अगर (clk_mgr->base.clks.dppclk_khz > new_घड़ीs->dppclk_khz)
			dpp_घड़ी_lowered = true;
		clk_mgr_base->clks.dppclk_khz = new_घड़ीs->dppclk_khz;
		update_dppclk = true;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dispclk_khz, clk_mgr_base->clks.dispclk_khz)) अणु
		clk_mgr_base->clks.dispclk_khz = new_घड़ीs->dispclk_khz;
		dcn301_smu_set_dispclk(clk_mgr, clk_mgr_base->clks.dispclk_khz);

		update_dispclk = true;
	पूर्ण

	अगर (dpp_घड़ी_lowered) अणु
		// increase per DPP DTO beक्रमe lowering global dppclk
		dcn20_update_घड़ीs_update_dpp_dto(clk_mgr, context, safe_to_lower);
		dcn301_smu_set_dppclk(clk_mgr, clk_mgr_base->clks.dppclk_khz);
	पूर्ण अन्यथा अणु
		// increase global DPPCLK beक्रमe lowering per DPP DTO
		अगर (update_dppclk || update_dispclk)
			dcn301_smu_set_dppclk(clk_mgr, clk_mgr_base->clks.dppclk_khz);
		// always update dtos unless घड़ी is lowered and not safe to lower
		अगर (new_घड़ीs->dppclk_khz >= dc->current_state->bw_ctx.bw.dcn.clk.dppclk_khz)
			dcn20_update_घड़ीs_update_dpp_dto(clk_mgr, context, safe_to_lower);
	पूर्ण
पूर्ण


अटल पूर्णांक get_vco_frequency_from_reg(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	/* get FbMult value */
	काष्ठा fixed31_32 pll_req;
	अचिन्हित पूर्णांक fbmult_frac_val = 0;
	अचिन्हित पूर्णांक fbmult_पूर्णांक_val = 0;


	/*
	 * Register value of fbmult is in 8.16 क्रमmat, we are converting to 31.32
	 * to leverage the fix poपूर्णांक operations available in driver
	 */

	REG_GET(CLK1_0_CLK1_CLK_PLL_REQ, FbMult_frac, &fbmult_frac_val); /* 16 bit fractional part*/
	REG_GET(CLK1_0_CLK1_CLK_PLL_REQ, FbMult_पूर्णांक, &fbmult_पूर्णांक_val); /* 8 bit पूर्णांकeger part */

	pll_req = dc_fixpt_from_पूर्णांक(fbmult_पूर्णांक_val);

	/*
	 * since fractional part is only 16 bit in रेजिस्टर definition but is 32 bit
	 * in our fix poपूर्णांक definiton, need to shअगरt left by 16 to obtain correct value
	 */
	pll_req.value |= fbmult_frac_val << 16;

	/* multiply by REFCLK period */
	pll_req = dc_fixpt_mul_पूर्णांक(pll_req, clk_mgr->dfs_ref_freq_khz);

	/* पूर्णांकeger part is now VCO frequency in kHz */
	वापस dc_fixpt_न्यूनमान(pll_req);
पूर्ण

अटल व्योम vg_dump_clk_रेजिस्टरs_पूर्णांकernal(काष्ठा dcn301_clk_पूर्णांकernal *पूर्णांकernal, काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	पूर्णांकernal->CLK1_CLK3_CURRENT_CNT = REG_READ(CLK1_0_CLK1_CLK3_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK3_BYPASS_CNTL = REG_READ(CLK1_0_CLK1_CLK3_BYPASS_CNTL);

	पूर्णांकernal->CLK1_CLK3_DS_CNTL = REG_READ(CLK1_0_CLK1_CLK3_DS_CNTL);	//dcf deep sleep भागider
	पूर्णांकernal->CLK1_CLK3_ALLOW_DS = REG_READ(CLK1_0_CLK1_CLK3_ALLOW_DS);

	पूर्णांकernal->CLK1_CLK1_CURRENT_CNT = REG_READ(CLK1_0_CLK1_CLK1_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK1_BYPASS_CNTL = REG_READ(CLK1_0_CLK1_CLK1_BYPASS_CNTL);

	पूर्णांकernal->CLK1_CLK2_CURRENT_CNT = REG_READ(CLK1_0_CLK1_CLK2_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK2_BYPASS_CNTL = REG_READ(CLK1_0_CLK1_CLK2_BYPASS_CNTL);

	पूर्णांकernal->CLK1_CLK0_CURRENT_CNT = REG_READ(CLK1_0_CLK1_CLK0_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK0_BYPASS_CNTL = REG_READ(CLK1_0_CLK1_CLK0_BYPASS_CNTL);
पूर्ण

/* This function collect raw clk रेजिस्टर values */
अटल व्योम vg_dump_clk_रेजिस्टरs(काष्ठा clk_state_रेजिस्टरs_and_bypass *regs_and_bypass,
		काष्ठा clk_mgr *clk_mgr_base, काष्ठा clk_log_info *log_info)
अणु
	काष्ठा dcn301_clk_पूर्णांकernal पूर्णांकernal = अणु0पूर्ण;
	अक्षर *bypass_clks[5] = अणु"0x0 DFS", "0x1 REFCLK", "0x2 ERROR", "0x3 400 FCH", "0x4 600 FCH"पूर्ण;
	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = log_info->bufSize;

	vg_dump_clk_रेजिस्टरs_पूर्णांकernal(&पूर्णांकernal, clk_mgr_base);

	regs_and_bypass->dcfclk = पूर्णांकernal.CLK1_CLK3_CURRENT_CNT / 10;
	regs_and_bypass->dcf_deep_sleep_भागider = पूर्णांकernal.CLK1_CLK3_DS_CNTL / 10;
	regs_and_bypass->dcf_deep_sleep_allow = पूर्णांकernal.CLK1_CLK3_ALLOW_DS;
	regs_and_bypass->dprefclk = पूर्णांकernal.CLK1_CLK2_CURRENT_CNT / 10;
	regs_and_bypass->dispclk = पूर्णांकernal.CLK1_CLK0_CURRENT_CNT / 10;
	regs_and_bypass->dppclk = पूर्णांकernal.CLK1_CLK1_CURRENT_CNT / 10;

	regs_and_bypass->dppclk_bypass = पूर्णांकernal.CLK1_CLK1_BYPASS_CNTL & 0x0007;
	अगर (regs_and_bypass->dppclk_bypass < 0 || regs_and_bypass->dppclk_bypass > 4)
		regs_and_bypass->dppclk_bypass = 0;
	regs_and_bypass->dcfclk_bypass = पूर्णांकernal.CLK1_CLK3_BYPASS_CNTL & 0x0007;
	अगर (regs_and_bypass->dcfclk_bypass < 0 || regs_and_bypass->dcfclk_bypass > 4)
		regs_and_bypass->dcfclk_bypass = 0;
	regs_and_bypass->dispclk_bypass = पूर्णांकernal.CLK1_CLK0_BYPASS_CNTL & 0x0007;
	अगर (regs_and_bypass->dispclk_bypass < 0 || regs_and_bypass->dispclk_bypass > 4)
		regs_and_bypass->dispclk_bypass = 0;
	regs_and_bypass->dprefclk_bypass = पूर्णांकernal.CLK1_CLK2_BYPASS_CNTL & 0x0007;
	अगर (regs_and_bypass->dprefclk_bypass < 0 || regs_and_bypass->dprefclk_bypass > 4)
		regs_and_bypass->dprefclk_bypass = 0;

	अगर (log_info->enabled) अणु
		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "clk_type,clk_value,deepsleep_cntl,deepsleep_allow,bypass\n");
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "dcfclk,%d,%d,%d,%s\n",
			regs_and_bypass->dcfclk,
			regs_and_bypass->dcf_deep_sleep_भागider,
			regs_and_bypass->dcf_deep_sleep_allow,
			bypass_clks[(पूर्णांक) regs_and_bypass->dcfclk_bypass]);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "dprefclk,%d,N/A,N/A,%s\n",
			regs_and_bypass->dprefclk,
			bypass_clks[(पूर्णांक) regs_and_bypass->dprefclk_bypass]);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "dispclk,%d,N/A,N/A,%s\n",
			regs_and_bypass->dispclk,
			bypass_clks[(पूर्णांक) regs_and_bypass->dispclk_bypass]);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		//split
		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "SPLIT\n");
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		// REGISTER VALUES
		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "reg_name,value,clk_type\n");
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK3_CURRENT_CNT,%d,dcfclk\n",
				पूर्णांकernal.CLK1_CLK3_CURRENT_CNT);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK3_DS_CNTL,%d,dcf_deep_sleep_divider\n",
					पूर्णांकernal.CLK1_CLK3_DS_CNTL);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK3_ALLOW_DS,%d,dcf_deep_sleep_allow\n",
					पूर्णांकernal.CLK1_CLK3_ALLOW_DS);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK2_CURRENT_CNT,%d,dprefclk\n",
					पूर्णांकernal.CLK1_CLK2_CURRENT_CNT);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK0_CURRENT_CNT,%d,dispclk\n",
					पूर्णांकernal.CLK1_CLK0_CURRENT_CNT);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK1_CURRENT_CNT,%d,dppclk\n",
					पूर्णांकernal.CLK1_CLK1_CURRENT_CNT);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK3_BYPASS_CNTL,%d,dcfclk_bypass\n",
					पूर्णांकernal.CLK1_CLK3_BYPASS_CNTL);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK2_BYPASS_CNTL,%d,dprefclk_bypass\n",
					पूर्णांकernal.CLK1_CLK2_BYPASS_CNTL);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK0_BYPASS_CNTL,%d,dispclk_bypass\n",
					पूर्णांकernal.CLK1_CLK0_BYPASS_CNTL);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;

		अक्षरs_prपूर्णांकed = snम_लिखो_count(log_info->pBuf, reमुख्यing_buffer, "CLK1_CLK1_BYPASS_CNTL,%d,dppclk_bypass\n",
					पूर्णांकernal.CLK1_CLK1_BYPASS_CNTL);
		reमुख्यing_buffer -= अक्षरs_prपूर्णांकed;
		*log_info->sum_अक्षरs_prपूर्णांकed += अक्षरs_prपूर्णांकed;
		log_info->pBuf += अक्षरs_prपूर्णांकed;
	पूर्ण
पूर्ण

/* This function produce translated logical clk state values*/
व्योम vg_get_clk_states(काष्ठा clk_mgr *clk_mgr_base, काष्ठा clk_states *s)
अणु

	काष्ठा clk_state_रेजिस्टरs_and_bypass sb = अणु 0 पूर्ण;
	काष्ठा clk_log_info log_info = अणु 0 पूर्ण;

	vg_dump_clk_रेजिस्टरs(&sb, clk_mgr_base, &log_info);

	s->dprefclk_khz = sb.dprefclk * 1000;
पूर्ण

अटल व्योम vg_enable_pme_wa(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	dcn301_smu_enable_pme_wa(clk_mgr);
पूर्ण

व्योम vg_init_घड़ीs(काष्ठा clk_mgr *clk_mgr)
अणु
	स_रखो(&(clk_mgr->clks), 0, माप(काष्ठा dc_घड़ीs));
	// Assumption is that boot state always supports pstate
	clk_mgr->clks.p_state_change_support = true;
	clk_mgr->clks.prev_p_state_change_support = true;
	clk_mgr->clks.pwr_state = DCN_PWR_STATE_UNKNOWN;
पूर्ण

अटल व्योम vg_build_watermark_ranges(काष्ठा clk_bw_params *bw_params, काष्ठा watermarks *table)
अणु
	पूर्णांक i, num_valid_sets;

	num_valid_sets = 0;

	क्रम (i = 0; i < WM_SET_COUNT; i++) अणु
		/* skip empty entries, the smu array has no holes*/
		अगर (!bw_params->wm_table.entries[i].valid)
			जारी;

		table->WatermarkRow[WM_DCFCLK][num_valid_sets].WmSetting = bw_params->wm_table.entries[i].wm_inst;
		table->WatermarkRow[WM_DCFCLK][num_valid_sets].WmType = bw_params->wm_table.entries[i].wm_type;
		/* We will not select WM based on fclk, so leave it as unस्थिरrained */
		table->WatermarkRow[WM_DCFCLK][num_valid_sets].MinClock = 0;
		table->WatermarkRow[WM_DCFCLK][num_valid_sets].MaxClock = 0xFFFF;

		अगर (table->WatermarkRow[WM_DCFCLK][num_valid_sets].WmType == WM_TYPE_PSTATE_CHG) अणु
			अगर (i == 0)
				table->WatermarkRow[WM_DCFCLK][num_valid_sets].MinMclk = 0;
			अन्यथा अणु
				/* add 1 to make it non-overlapping with next lvl */
				table->WatermarkRow[WM_DCFCLK][num_valid_sets].MinMclk =
						bw_params->clk_table.entries[i - 1].dcfclk_mhz + 1;
			पूर्ण
			table->WatermarkRow[WM_DCFCLK][num_valid_sets].MaxMclk =
					bw_params->clk_table.entries[i].dcfclk_mhz;

		पूर्ण अन्यथा अणु
			/* unस्थिरrained क्रम memory retraining */
			table->WatermarkRow[WM_DCFCLK][num_valid_sets].MinClock = 0;
			table->WatermarkRow[WM_DCFCLK][num_valid_sets].MaxClock = 0xFFFF;

			/* Modअगरy previous watermark range to cover up to max */
			table->WatermarkRow[WM_DCFCLK][num_valid_sets - 1].MaxClock = 0xFFFF;
		पूर्ण
		num_valid_sets++;
	पूर्ण

	ASSERT(num_valid_sets != 0); /* Must have at least one set of valid watermarks */

	/* modअगरy the min and max to make sure we cover the whole range*/
	table->WatermarkRow[WM_DCFCLK][0].MinMclk = 0;
	table->WatermarkRow[WM_DCFCLK][0].MinClock = 0;
	table->WatermarkRow[WM_DCFCLK][num_valid_sets - 1].MaxMclk = 0xFFFF;
	table->WatermarkRow[WM_DCFCLK][num_valid_sets - 1].MaxClock = 0xFFFF;

	/* This is क्रम ग_लिखोback only, करोes not matter currently as no ग_लिखोback support*/
	table->WatermarkRow[WM_SOCCLK][0].WmSetting = WM_A;
	table->WatermarkRow[WM_SOCCLK][0].MinClock = 0;
	table->WatermarkRow[WM_SOCCLK][0].MaxClock = 0xFFFF;
	table->WatermarkRow[WM_SOCCLK][0].MinMclk = 0;
	table->WatermarkRow[WM_SOCCLK][0].MaxMclk = 0xFFFF;
पूर्ण


अटल व्योम vg_notअगरy_wm_ranges(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा clk_mgr_vgh *clk_mgr_vgh = TO_CLK_MGR_VGH(clk_mgr);
	काष्ठा watermarks *table = clk_mgr_vgh->smu_wm_set.wm_set;

	अगर (!clk_mgr->smu_ver)
		वापस;

	अगर (!table || clk_mgr_vgh->smu_wm_set.mc_address.quad_part == 0)
		वापस;

	स_रखो(table, 0, माप(*table));

	vg_build_watermark_ranges(clk_mgr_base->bw_params, table);

	dcn301_smu_set_dram_addr_high(clk_mgr,
			clk_mgr_vgh->smu_wm_set.mc_address.high_part);
	dcn301_smu_set_dram_addr_low(clk_mgr,
			clk_mgr_vgh->smu_wm_set.mc_address.low_part);
	dcn301_smu_transfer_wm_table_dram_2_smu(clk_mgr);
पूर्ण

अटल bool vg_are_घड़ी_states_equal(काष्ठा dc_घड़ीs *a,
		काष्ठा dc_घड़ीs *b)
अणु
	अगर (a->dispclk_khz != b->dispclk_khz)
		वापस false;
	अन्यथा अगर (a->dppclk_khz != b->dppclk_khz)
		वापस false;
	अन्यथा अगर (a->dcfclk_khz != b->dcfclk_khz)
		वापस false;
	अन्यथा अगर (a->dcfclk_deep_sleep_khz != b->dcfclk_deep_sleep_khz)
		वापस false;

	वापस true;
पूर्ण


अटल काष्ठा clk_mgr_funcs vg_funcs = अणु
	.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
	.update_घड़ीs = vg_update_घड़ीs,
	.init_घड़ीs = vg_init_घड़ीs,
	.enable_pme_wa = vg_enable_pme_wa,
	.are_घड़ी_states_equal = vg_are_घड़ी_states_equal,
	.notअगरy_wm_ranges = vg_notअगरy_wm_ranges
पूर्ण;

अटल काष्ठा clk_bw_params vg_bw_params = अणु
	.vram_type = Ddr4MemType,
	.num_channels = 1,
	.clk_table = अणु
		.entries = अणु
			अणु
				.voltage = 0,
				.dcfclk_mhz = 400,
				.fclk_mhz = 400,
				.memclk_mhz = 800,
				.socclk_mhz = 0,
			पूर्ण,
			अणु
				.voltage = 0,
				.dcfclk_mhz = 483,
				.fclk_mhz = 800,
				.memclk_mhz = 1600,
				.socclk_mhz = 0,
			पूर्ण,
			अणु
				.voltage = 0,
				.dcfclk_mhz = 602,
				.fclk_mhz = 1067,
				.memclk_mhz = 1067,
				.socclk_mhz = 0,
			पूर्ण,
			अणु
				.voltage = 0,
				.dcfclk_mhz = 738,
				.fclk_mhz = 1333,
				.memclk_mhz = 1600,
				.socclk_mhz = 0,
			पूर्ण,
		पूर्ण,

		.num_entries = 4,
	पूर्ण,

पूर्ण;

अटल काष्ठा wm_table ddr4_wm_table = अणु
	.entries = अणु
		अणु
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 6.09,
			.sr_enter_plus_निकास_समय_us = 7.14,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 10.12,
			.sr_enter_plus_निकास_समय_us = 11.48,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 10.12,
			.sr_enter_plus_निकास_समय_us = 11.48,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 10.12,
			.sr_enter_plus_निकास_समय_us = 11.48,
			.valid = true,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा wm_table lpddr5_wm_table = अणु
	.entries = अणु
		अणु
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.65333,
			.sr_निकास_समय_us = 5.32,
			.sr_enter_plus_निकास_समय_us = 6.38,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.65333,
			.sr_निकास_समय_us = 9.82,
			.sr_enter_plus_निकास_समय_us = 11.196,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.65333,
			.sr_निकास_समय_us = 9.89,
			.sr_enter_plus_निकास_समय_us = 11.24,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.65333,
			.sr_निकास_समय_us = 9.748,
			.sr_enter_plus_निकास_समय_us = 11.102,
			.valid = true,
		पूर्ण,
	पूर्ण
पूर्ण;


अटल अचिन्हित पूर्णांक find_dcfclk_क्रम_voltage(स्थिर काष्ठा vg_dpm_घड़ीs *घड़ी_प्रकारable,
		अचिन्हित पूर्णांक voltage)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < VG_NUM_SOC_VOLTAGE_LEVELS; i++) अणु
		अगर (घड़ी_प्रकारable->SocVoltage[i] == voltage)
			वापस घड़ी_प्रकारable->DcfClocks[i];
	पूर्ण

	ASSERT(0);
	वापस 0;
पूर्ण

अटल व्योम vg_clk_mgr_helper_populate_bw_params(
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा पूर्णांकegrated_info *bios_info,
		स्थिर काष्ठा vg_dpm_घड़ीs *घड़ी_प्रकारable)
अणु
	पूर्णांक i, j;
	काष्ठा clk_bw_params *bw_params = clk_mgr->base.bw_params;

	j = -1;

	ASSERT(VG_NUM_FCLK_DPM_LEVELS <= MAX_NUM_DPM_LVL);

	/* Find lowest DPM, FCLK is filled in reverse order*/

	क्रम (i = VG_NUM_FCLK_DPM_LEVELS - 1; i >= 0; i--) अणु
		अगर (घड़ी_प्रकारable->DfPstateTable[i].fclk != 0) अणु
			j = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (j == -1) अणु
		/* घड़ी table is all 0s, just use our own hardcode */
		ASSERT(0);
		वापस;
	पूर्ण

	bw_params->clk_table.num_entries = j + 1;

	क्रम (i = 0; i < bw_params->clk_table.num_entries; i++, j--) अणु
		bw_params->clk_table.entries[i].fclk_mhz = घड़ी_प्रकारable->DfPstateTable[j].fclk;
		bw_params->clk_table.entries[i].memclk_mhz = घड़ी_प्रकारable->DfPstateTable[j].memclk;
		bw_params->clk_table.entries[i].voltage = घड़ी_प्रकारable->DfPstateTable[j].voltage;
		bw_params->clk_table.entries[i].dcfclk_mhz = find_dcfclk_क्रम_voltage(घड़ी_प्रकारable, घड़ी_प्रकारable->DfPstateTable[j].voltage);
	पूर्ण

	bw_params->vram_type = bios_info->memory_type;
	bw_params->num_channels = bios_info->ma_channel_number;

	क्रम (i = 0; i < WM_SET_COUNT; i++) अणु
		bw_params->wm_table.entries[i].wm_inst = i;

		अगर (i >= bw_params->clk_table.num_entries) अणु
			bw_params->wm_table.entries[i].valid = false;
			जारी;
		पूर्ण

		bw_params->wm_table.entries[i].wm_type = WM_TYPE_PSTATE_CHG;
		bw_params->wm_table.entries[i].valid = true;
	पूर्ण

	अगर (bw_params->vram_type == LpDdr4MemType) अणु
		/*
		 * WM set D will be re-purposed क्रम memory retraining
		 */
		bw_params->wm_table.entries[WM_D].pstate_latency_us = LPDDR_MEM_RETRAIN_LATENCY;
		bw_params->wm_table.entries[WM_D].wm_inst = WM_D;
		bw_params->wm_table.entries[WM_D].wm_type = WM_TYPE_RETRAINING;
		bw_params->wm_table.entries[WM_D].valid = true;
	पूर्ण

पूर्ण

/* Temporary Place holder until we can get them from fuse */
अटल काष्ठा vg_dpm_घड़ीs dummy_घड़ीs = अणु
		.DcfClocks = अणु 201, 403, 403, 403, 403, 403, 403 पूर्ण,
		.SocClocks = अणु 400, 600, 600, 600, 600, 600, 600 पूर्ण,
		.SocVoltage = अणु 2800, 2860, 2860, 2860, 2860, 2860, 2860, 2860 पूर्ण,
		.DfPstateTable = अणु
				अणु .fclk = 400,  .memclk = 400, .voltage = 2800 पूर्ण,
				अणु .fclk = 400,  .memclk = 400, .voltage = 2800 पूर्ण,
				अणु .fclk = 400,  .memclk = 400, .voltage = 2800 पूर्ण,
				अणु .fclk = 400,  .memclk = 400, .voltage = 2800 पूर्ण
		पूर्ण
पूर्ण;

अटल काष्ठा watermarks dummy_wms = अणु 0 पूर्ण;

अटल व्योम vg_get_dpm_table_from_smu(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा smu_dpm_clks *smu_dpm_clks)
अणु
	काष्ठा vg_dpm_घड़ीs *table = smu_dpm_clks->dpm_clks;

	अगर (!clk_mgr->smu_ver)
		वापस;

	अगर (!table || smu_dpm_clks->mc_address.quad_part == 0)
		वापस;

	स_रखो(table, 0, माप(*table));

	dcn301_smu_set_dram_addr_high(clk_mgr,
			smu_dpm_clks->mc_address.high_part);
	dcn301_smu_set_dram_addr_low(clk_mgr,
			smu_dpm_clks->mc_address.low_part);
	dcn301_smu_transfer_dpm_table_smu_2_dram(clk_mgr);
पूर्ण

व्योम vg_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_vgh *clk_mgr,
		काष्ठा pp_smu_funcs *pp_smu,
		काष्ठा dccg *dccg)
अणु
	काष्ठा smu_dpm_clks smu_dpm_clks = अणु 0 पूर्ण;

	clk_mgr->base.base.ctx = ctx;
	clk_mgr->base.base.funcs = &vg_funcs;

	clk_mgr->base.pp_smu = pp_smu;

	clk_mgr->base.dccg = dccg;
	clk_mgr->base.dfs_bypass_disp_clk = 0;

	clk_mgr->base.dprefclk_ss_percentage = 0;
	clk_mgr->base.dprefclk_ss_भागider = 1000;
	clk_mgr->base.ss_on_dprefclk = false;
	clk_mgr->base.dfs_ref_freq_khz = 48000;

	clk_mgr->smu_wm_set.wm_set = (काष्ठा watermarks *)dm_helpers_allocate_gpu_mem(
				clk_mgr->base.base.ctx,
				DC_MEM_ALLOC_TYPE_FRAME_BUFFER,
				माप(काष्ठा watermarks),
				&clk_mgr->smu_wm_set.mc_address.quad_part);

	अगर (clk_mgr->smu_wm_set.wm_set == 0) अणु
		clk_mgr->smu_wm_set.wm_set = &dummy_wms;
		clk_mgr->smu_wm_set.mc_address.quad_part = 0;
	पूर्ण
	ASSERT(clk_mgr->smu_wm_set.wm_set);

	smu_dpm_clks.dpm_clks = (काष्ठा vg_dpm_घड़ीs *)dm_helpers_allocate_gpu_mem(
				clk_mgr->base.base.ctx,
				DC_MEM_ALLOC_TYPE_FRAME_BUFFER,
				माप(काष्ठा vg_dpm_घड़ीs),
				&smu_dpm_clks.mc_address.quad_part);

	अगर (smu_dpm_clks.dpm_clks == शून्य) अणु
		smu_dpm_clks.dpm_clks = &dummy_घड़ीs;
		smu_dpm_clks.mc_address.quad_part = 0;
	पूर्ण

	ASSERT(smu_dpm_clks.dpm_clks);

	अगर (IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) अणु
		vg_funcs.update_घड़ीs = dcn2_update_घड़ीs_fpga;
		clk_mgr->base.base.dentist_vco_freq_khz = 3600000;
	पूर्ण अन्यथा अणु
		काष्ठा clk_log_info log_info = अणु0पूर्ण;

		clk_mgr->base.smu_ver = dcn301_smu_get_smu_version(&clk_mgr->base);

		अगर (clk_mgr->base.smu_ver)
			clk_mgr->base.smu_present = true;

		/* TODO: Check we get what we expect during bringup */
		clk_mgr->base.base.dentist_vco_freq_khz = get_vco_frequency_from_reg(&clk_mgr->base);

		/* in हाल we करोn't get a value from the रेजिस्टर, use शेष */
		अगर (clk_mgr->base.base.dentist_vco_freq_khz == 0)
			clk_mgr->base.base.dentist_vco_freq_khz = 3600000;

		अगर (ctx->dc_bios->पूर्णांकegrated_info->memory_type == LpDdr5MemType) अणु
			vg_bw_params.wm_table = lpddr5_wm_table;
		पूर्ण अन्यथा अणु
			vg_bw_params.wm_table = ddr4_wm_table;
		पूर्ण
		/* Saved घड़ीs configured at boot क्रम debug purposes */
		vg_dump_clk_रेजिस्टरs(&clk_mgr->base.base.boot_snapshot, &clk_mgr->base.base, &log_info);
	पूर्ण

	clk_mgr->base.base.dprefclk_khz = 600000;
	dce_घड़ी_पढ़ो_ss_info(&clk_mgr->base);

	clk_mgr->base.base.bw_params = &vg_bw_params;

	vg_get_dpm_table_from_smu(&clk_mgr->base, &smu_dpm_clks);
	अगर (ctx->dc_bios && ctx->dc_bios->पूर्णांकegrated_info) अणु
		vg_clk_mgr_helper_populate_bw_params(
				&clk_mgr->base,
				ctx->dc_bios->पूर्णांकegrated_info,
				smu_dpm_clks.dpm_clks);
	पूर्ण

	अगर (smu_dpm_clks.dpm_clks && smu_dpm_clks.mc_address.quad_part != 0)
		dm_helpers_मुक्त_gpu_mem(clk_mgr->base.base.ctx, DC_MEM_ALLOC_TYPE_FRAME_BUFFER,
				smu_dpm_clks.dpm_clks);
/*
	अगर (!IS_FPGA_MAXIMUS_DC(ctx->dce_environment) && clk_mgr->base.smu_ver) अणु
		 enable घातerfeatures when displaycount goes to 0
		dcn301_smu_enable_phy_refclk_pwrdwn(clk_mgr, !debug->disable_48mhz_pwrdwn);
	पूर्ण
*/
पूर्ण

व्योम vg_clk_mgr_destroy(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr_पूर्णांक)
अणु
	काष्ठा clk_mgr_vgh *clk_mgr = TO_CLK_MGR_VGH(clk_mgr_पूर्णांक);

	अगर (clk_mgr->smu_wm_set.wm_set && clk_mgr->smu_wm_set.mc_address.quad_part != 0)
		dm_helpers_मुक्त_gpu_mem(clk_mgr_पूर्णांक->base.ctx, DC_MEM_ALLOC_TYPE_FRAME_BUFFER,
				clk_mgr->smu_wm_set.wm_set);
पूर्ण
