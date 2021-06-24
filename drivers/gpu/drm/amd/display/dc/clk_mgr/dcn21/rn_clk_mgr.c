<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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


#समावेश "dcn20/dcn20_clk_mgr.h"
#समावेश "rn_clk_mgr.h"


#समावेश "dce100/dce_clk_mgr.h"
#समावेश "rn_clk_mgr_vbios_smu.h"
#समावेश "reg_helper.h"
#समावेश "core_types.h"
#समावेश "dm_helpers.h"

#समावेश "atomfirmware.h"
#समावेश "clk/clk_10_0_2_offset.h"
#समावेश "clk/clk_10_0_2_sh_mask.h"
#समावेश "renoir_ip_offset.h"


/* Constants */

#घोषणा LPDDR_MEM_RETRAIN_LATENCY 4.977 /* Number obtained from LPDDR4 Training Counter Requirement करोc */
#घोषणा SMU_VER_55_51_0 0x373300 /* SMU Version that is able to set DISPCLK below 100MHz */

/* Macros */

#घोषणा REG(reg_name) \
	(CLK_BASE.instance[0].segment[mm ## reg_name ## _BASE_IDX] + mm ## reg_name)


/* TODO: evaluate how to lower or disable all dcn घड़ीs in screen off हाल */
पूर्णांक rn_get_active_display_cnt_wa(
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
		अगर (link->link_enc->funcs->is_dig_enabled(link->link_enc))
			display_count++;
	पूर्ण

	/* WA क्रम hang on HDMI after display off back back on*/
	अगर (display_count == 0 && पंचांगds_present)
		display_count = 1;

	वापस display_count;
पूर्ण

व्योम rn_set_low_घातer_state(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	rn_vbios_smu_set_dcn_low_घातer_state(clk_mgr, DCN_PWR_STATE_LOW_POWER);
	/* update घातer state */
	clk_mgr_base->clks.pwr_state = DCN_PWR_STATE_LOW_POWER;
पूर्ण

अटल व्योम rn_update_घड़ीs_update_dpp_dto(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा dc_state *context, पूर्णांक ref_dpp_clk, bool safe_to_lower)
अणु
	पूर्णांक i;

	clk_mgr->dccg->ref_dppclk = ref_dpp_clk;

	क्रम (i = 0; i < clk_mgr->base.ctx->dc->res_pool->pipe_count; i++) अणु
		पूर्णांक dpp_inst, dppclk_khz, prev_dppclk_khz;

		/* Loop index will match dpp->inst अगर resource exists,
		 * and we want to aव्योम dependency on dpp object
		 */
		dpp_inst = i;
		dppclk_khz = context->res_ctx.pipe_ctx[i].plane_res.bw.dppclk_khz;

		prev_dppclk_khz = clk_mgr->dccg->pipe_dppclk_khz[i];

		अगर (safe_to_lower || prev_dppclk_khz < dppclk_khz)
			clk_mgr->dccg->funcs->update_dpp_dto(
							clk_mgr->dccg, dpp_inst, dppclk_khz);
	पूर्ण
पूर्ण


व्योम rn_update_घड़ीs(काष्ठा clk_mgr *clk_mgr_base,
			काष्ठा dc_state *context,
			bool safe_to_lower)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा dc_घड़ीs *new_घड़ीs = &context->bw_ctx.bw.dcn.clk;
	काष्ठा dc *dc = clk_mgr_base->ctx->dc;
	पूर्णांक display_count, i;
	bool update_dppclk = false;
	bool update_dispclk = false;
	bool dpp_घड़ी_lowered = false;

	काष्ठा dmcu *dmcu = clk_mgr_base->ctx->dc->res_pool->dmcu;

	अगर (dc->work_arounds.skip_घड़ी_update)
		वापस;

	/*
	 * अगर it is safe to lower, but we are alपढ़ोy in the lower state, we करोn't have to करो anything
	 * also अगर safe to lower is false, we just go in the higher state
	 */
	अगर (safe_to_lower && !dc->debug.disable_48mhz_pwrdwn) अणु
		/* check that we're not alपढ़ोy in lower */
		अगर (clk_mgr_base->clks.pwr_state != DCN_PWR_STATE_LOW_POWER) अणु

			display_count = rn_get_active_display_cnt_wa(dc, context);
			/* अगर we can go lower, go lower */
			अगर (display_count == 0) अणु
				rn_vbios_smu_set_dcn_low_घातer_state(clk_mgr, DCN_PWR_STATE_LOW_POWER);
				/* update घातer state */
				clk_mgr_base->clks.pwr_state = DCN_PWR_STATE_LOW_POWER;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* check that we're not alपढ़ोy in D0 */
		अगर (clk_mgr_base->clks.pwr_state != DCN_PWR_STATE_MISSION_MODE) अणु
			rn_vbios_smu_set_dcn_low_घातer_state(clk_mgr, DCN_PWR_STATE_MISSION_MODE);
			/* update घातer state */
			clk_mgr_base->clks.pwr_state = DCN_PWR_STATE_MISSION_MODE;
		पूर्ण
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dcfclk_khz, clk_mgr_base->clks.dcfclk_khz)) अणु
		clk_mgr_base->clks.dcfclk_khz = new_घड़ीs->dcfclk_khz;
		rn_vbios_smu_set_hard_min_dcfclk(clk_mgr, clk_mgr_base->clks.dcfclk_khz);
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower,
			new_घड़ीs->dcfclk_deep_sleep_khz, clk_mgr_base->clks.dcfclk_deep_sleep_khz)) अणु
		clk_mgr_base->clks.dcfclk_deep_sleep_khz = new_घड़ीs->dcfclk_deep_sleep_khz;
		rn_vbios_smu_set_min_deep_sleep_dcfclk(clk_mgr, clk_mgr_base->clks.dcfclk_deep_sleep_khz);
	पूर्ण

	// workaround: Limit dppclk to 100Mhz to aव्योम lower eDP panel चयन to plus 4K monitor underflow.
	// Do not adjust dppclk अगर dppclk is 0 to aव्योम unexpected result
	अगर (new_घड़ीs->dppclk_khz < 100000 && new_घड़ीs->dppclk_khz > 0)
		new_घड़ीs->dppclk_khz = 100000;

	/*
	 * Temporally ignore thew 0 हालs क्रम disp and dpp clks.
	 * We may have a new feature that requires 0 clks in the future.
	 */
	अगर (new_घड़ीs->dppclk_khz == 0 || new_घड़ीs->dispclk_khz == 0) अणु
		new_घड़ीs->dppclk_khz = clk_mgr_base->clks.dppclk_khz;
		new_घड़ीs->dispclk_khz = clk_mgr_base->clks.dispclk_khz;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dppclk_khz, clk_mgr_base->clks.dppclk_khz)) अणु
		अगर (clk_mgr_base->clks.dppclk_khz > new_घड़ीs->dppclk_khz)
			dpp_घड़ी_lowered = true;
		clk_mgr_base->clks.dppclk_khz = new_घड़ीs->dppclk_khz;
		update_dppclk = true;
	पूर्ण

	अगर (should_set_घड़ी(safe_to_lower, new_घड़ीs->dispclk_khz, clk_mgr_base->clks.dispclk_khz)) अणु
		clk_mgr_base->clks.dispclk_khz = new_घड़ीs->dispclk_khz;
		clk_mgr_base->clks.actual_dispclk_khz = rn_vbios_smu_set_dispclk(clk_mgr, clk_mgr_base->clks.dispclk_khz);

		update_dispclk = true;
	पूर्ण

	अगर (dpp_घड़ी_lowered) अणु
		// increase per DPP DTO beक्रमe lowering global dppclk with requested dppclk
		rn_update_घड़ीs_update_dpp_dto(
				clk_mgr,
				context,
				clk_mgr_base->clks.dppclk_khz,
				safe_to_lower);

		क्रम (i = 0; i < context->stream_count; i++) अणु
			अगर (context->streams[i]->संकेत == SIGNAL_TYPE_EDP &&
				context->streams[i]->apply_seamless_boot_optimization) अणु
				dc_रुको_क्रम_vblank(dc, context->streams[i]);
				अवरोध;
			पूर्ण
		पूर्ण

		clk_mgr_base->clks.actual_dppclk_khz =
				rn_vbios_smu_set_dppclk(clk_mgr, clk_mgr_base->clks.dppclk_khz);

		//update dpp dto with actual dpp clk.
		rn_update_घड़ीs_update_dpp_dto(
				clk_mgr,
				context,
				clk_mgr_base->clks.actual_dppclk_khz,
				safe_to_lower);

	पूर्ण अन्यथा अणु
		// increase global DPPCLK beक्रमe lowering per DPP DTO
		अगर (update_dppclk || update_dispclk)
			clk_mgr_base->clks.actual_dppclk_khz =
					rn_vbios_smu_set_dppclk(clk_mgr, clk_mgr_base->clks.dppclk_khz);

		// always update dtos unless घड़ी is lowered and not safe to lower
		rn_update_घड़ीs_update_dpp_dto(
				clk_mgr,
				context,
				clk_mgr_base->clks.actual_dppclk_khz,
				safe_to_lower);
	पूर्ण

	अगर (update_dispclk &&
			dmcu && dmcu->funcs->is_dmcu_initialized(dmcu)) अणु
		/*update dmcu क्रम रुको_loop count*/
		dmcu->funcs->set_psr_रुको_loop(dmcu,
			clk_mgr_base->clks.dispclk_khz / 1000 / 7);
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

	REG_GET(CLK1_CLK_PLL_REQ, FbMult_frac, &fbmult_frac_val); /* 16 bit fractional part*/
	REG_GET(CLK1_CLK_PLL_REQ, FbMult_पूर्णांक, &fbmult_पूर्णांक_val); /* 8 bit पूर्णांकeger part */

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

अटल व्योम rn_dump_clk_रेजिस्टरs_पूर्णांकernal(काष्ठा rn_clk_पूर्णांकernal *पूर्णांकernal, काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	पूर्णांकernal->CLK1_CLK3_CURRENT_CNT = REG_READ(CLK1_CLK3_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK3_BYPASS_CNTL = REG_READ(CLK1_CLK3_BYPASS_CNTL);

	पूर्णांकernal->CLK1_CLK3_DS_CNTL = REG_READ(CLK1_CLK3_DS_CNTL);	//dcf deep sleep भागider
	पूर्णांकernal->CLK1_CLK3_ALLOW_DS = REG_READ(CLK1_CLK3_ALLOW_DS);

	पूर्णांकernal->CLK1_CLK1_CURRENT_CNT = REG_READ(CLK1_CLK1_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK1_BYPASS_CNTL = REG_READ(CLK1_CLK1_BYPASS_CNTL);

	पूर्णांकernal->CLK1_CLK2_CURRENT_CNT = REG_READ(CLK1_CLK2_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK2_BYPASS_CNTL = REG_READ(CLK1_CLK2_BYPASS_CNTL);

	पूर्णांकernal->CLK1_CLK0_CURRENT_CNT = REG_READ(CLK1_CLK0_CURRENT_CNT);
	पूर्णांकernal->CLK1_CLK0_BYPASS_CNTL = REG_READ(CLK1_CLK0_BYPASS_CNTL);
पूर्ण

/* This function collect raw clk रेजिस्टर values */
अटल व्योम rn_dump_clk_रेजिस्टरs(काष्ठा clk_state_रेजिस्टरs_and_bypass *regs_and_bypass,
		काष्ठा clk_mgr *clk_mgr_base, काष्ठा clk_log_info *log_info)
अणु
	काष्ठा rn_clk_पूर्णांकernal पूर्णांकernal = अणु0पूर्ण;
	अक्षर *bypass_clks[5] = अणु"0x0 DFS", "0x1 REFCLK", "0x2 ERROR", "0x3 400 FCH", "0x4 600 FCH"पूर्ण;
	अचिन्हित पूर्णांक अक्षरs_prपूर्णांकed = 0;
	अचिन्हित पूर्णांक reमुख्यing_buffer = log_info->bufSize;

	rn_dump_clk_रेजिस्टरs_पूर्णांकernal(&पूर्णांकernal, clk_mgr_base);

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
व्योम rn_get_clk_states(काष्ठा clk_mgr *clk_mgr_base, काष्ठा clk_states *s)
अणु
	काष्ठा clk_state_रेजिस्टरs_and_bypass sb = अणु 0 पूर्ण;
	काष्ठा clk_log_info log_info = अणु 0 पूर्ण;

	rn_dump_clk_रेजिस्टरs(&sb, clk_mgr_base, &log_info);

	s->dprefclk_khz = sb.dprefclk * 1000;
पूर्ण

व्योम rn_enable_pme_wa(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);

	rn_vbios_smu_enable_pme_wa(clk_mgr);
पूर्ण

व्योम rn_init_घड़ीs(काष्ठा clk_mgr *clk_mgr)
अणु
	स_रखो(&(clk_mgr->clks), 0, माप(काष्ठा dc_घड़ीs));
	// Assumption is that boot state always supports pstate
	clk_mgr->clks.p_state_change_support = true;
	clk_mgr->clks.prev_p_state_change_support = true;
	clk_mgr->clks.pwr_state = DCN_PWR_STATE_UNKNOWN;
पूर्ण

अटल व्योम build_watermark_ranges(काष्ठा clk_bw_params *bw_params, काष्ठा pp_smu_wm_range_sets *ranges)
अणु
	पूर्णांक i, num_valid_sets;

	num_valid_sets = 0;

	क्रम (i = 0; i < WM_SET_COUNT; i++) अणु
		/* skip empty entries, the smu array has no holes*/
		अगर (!bw_params->wm_table.entries[i].valid)
			जारी;

		ranges->पढ़ोer_wm_sets[num_valid_sets].wm_inst = bw_params->wm_table.entries[i].wm_inst;
		ranges->पढ़ोer_wm_sets[num_valid_sets].wm_type = bw_params->wm_table.entries[i].wm_type;
		/* We will not select WM based on fclk, so leave it as unस्थिरrained */
		ranges->पढ़ोer_wm_sets[num_valid_sets].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
		ranges->पढ़ोer_wm_sets[num_valid_sets].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
		/* dcfclk wil be used to select WM*/

		अगर (ranges->पढ़ोer_wm_sets[num_valid_sets].wm_type == WM_TYPE_PSTATE_CHG) अणु
			अगर (i == 0)
				ranges->पढ़ोer_wm_sets[num_valid_sets].min_drain_clk_mhz = 0;
			अन्यथा अणु
				/* add 1 to make it non-overlapping with next lvl */
				ranges->पढ़ोer_wm_sets[num_valid_sets].min_drain_clk_mhz = bw_params->clk_table.entries[i - 1].dcfclk_mhz + 1;
			पूर्ण
			ranges->पढ़ोer_wm_sets[num_valid_sets].max_drain_clk_mhz = bw_params->clk_table.entries[i].dcfclk_mhz;

		पूर्ण अन्यथा अणु
			/* unस्थिरrained क्रम memory retraining */
			ranges->पढ़ोer_wm_sets[num_valid_sets].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
			ranges->पढ़ोer_wm_sets[num_valid_sets].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

			/* Modअगरy previous watermark range to cover up to max */
			ranges->पढ़ोer_wm_sets[num_valid_sets - 1].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
		पूर्ण
		num_valid_sets++;
	पूर्ण

	ASSERT(num_valid_sets != 0); /* Must have at least one set of valid watermarks */
	ranges->num_पढ़ोer_wm_sets = num_valid_sets;

	/* modअगरy the min and max to make sure we cover the whole range*/
	ranges->पढ़ोer_wm_sets[0].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->पढ़ोer_wm_sets[0].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->पढ़ोer_wm_sets[ranges->num_पढ़ोer_wm_sets - 1].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
	ranges->पढ़ोer_wm_sets[ranges->num_पढ़ोer_wm_sets - 1].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

	/* This is क्रम ग_लिखोback only, करोes not matter currently as no ग_लिखोback support*/
	ranges->num_ग_लिखोr_wm_sets = 1;
	ranges->ग_लिखोr_wm_sets[0].wm_inst = WM_A;
	ranges->ग_लिखोr_wm_sets[0].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->ग_लिखोr_wm_sets[0].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
	ranges->ग_लिखोr_wm_sets[0].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
	ranges->ग_लिखोr_wm_sets[0].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

पूर्ण

अटल व्योम rn_notअगरy_wm_ranges(काष्ठा clk_mgr *clk_mgr_base)
अणु
	काष्ठा dc_debug_options *debug = &clk_mgr_base->ctx->dc->debug;
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	काष्ठा pp_smu_funcs *pp_smu = clk_mgr->pp_smu;

	अगर (!debug->disable_pplib_wm_range) अणु
		build_watermark_ranges(clk_mgr_base->bw_params, &clk_mgr_base->ranges);

		/* Notअगरy PP Lib/SMU which Watermarks to use क्रम which घड़ी ranges */
		अगर (pp_smu && pp_smu->rn_funcs.set_wm_ranges)
			pp_smu->rn_funcs.set_wm_ranges(&pp_smu->rn_funcs.pp_smu, &clk_mgr_base->ranges);
	पूर्ण

पूर्ण

अटल bool rn_are_घड़ी_states_equal(काष्ठा dc_घड़ीs *a,
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


/* Notअगरy clk_mgr of a change in link rate, update phyclk frequency अगर necessary */
अटल व्योम rn_notअगरy_link_rate_change(काष्ठा clk_mgr *clk_mgr_base, काष्ठा dc_link *link)
अणु
	काष्ठा clk_mgr_पूर्णांकernal *clk_mgr = TO_CLK_MGR_INTERNAL(clk_mgr_base);
	अचिन्हित पूर्णांक i, max_phyclk_req = 0;

	clk_mgr->cur_phyclk_req_table[link->link_index] = link->cur_link_settings.link_rate * LINK_RATE_REF_FREQ_IN_KHZ;

	क्रम (i = 0; i < MAX_PIPES * 2; i++) अणु
		अगर (clk_mgr->cur_phyclk_req_table[i] > max_phyclk_req)
			max_phyclk_req = clk_mgr->cur_phyclk_req_table[i];
	पूर्ण

	अगर (max_phyclk_req != clk_mgr_base->clks.phyclk_khz) अणु
		clk_mgr_base->clks.phyclk_khz = max_phyclk_req;
		rn_vbios_smu_set_phyclk(clk_mgr, clk_mgr_base->clks.phyclk_khz);
	पूर्ण
पूर्ण

अटल काष्ठा clk_mgr_funcs dcn21_funcs = अणु
	.get_dp_ref_clk_frequency = dce12_get_dp_ref_freq_khz,
	.update_घड़ीs = rn_update_घड़ीs,
	.init_घड़ीs = rn_init_घड़ीs,
	.enable_pme_wa = rn_enable_pme_wa,
	.are_घड़ी_states_equal = rn_are_घड़ी_states_equal,
	.set_low_घातer_state = rn_set_low_घातer_state,
	.notअगरy_wm_ranges = rn_notअगरy_wm_ranges,
	.notअगरy_link_rate_change = rn_notअगरy_link_rate_change,
पूर्ण;

अटल काष्ठा clk_bw_params rn_bw_params = अणु
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

अटल काष्ठा wm_table ddr4_wm_table_gs = अणु
	.entries = अणु
		अणु
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 7.09,
			.sr_enter_plus_निकास_समय_us = 8.14,
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

अटल काष्ठा wm_table lpddr4_wm_table_gs = अणु
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

अटल काष्ठा wm_table lpddr4_wm_table_with_disabled_ppt = अणु
	.entries = अणु
		अणु
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.65333,
			.sr_निकास_समय_us = 8.32,
			.sr_enter_plus_निकास_समय_us = 9.38,
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

अटल काष्ठा wm_table ddr4_wm_table_rn = अणु
	.entries = अणु
		अणु
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 11.90,
			.sr_enter_plus_निकास_समय_us = 12.80,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 13.18,
			.sr_enter_plus_निकास_समय_us = 14.30,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 13.18,
			.sr_enter_plus_निकास_समय_us = 14.30,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 13.18,
			.sr_enter_plus_निकास_समय_us = 14.30,
			.valid = true,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा wm_table ddr4_1R_wm_table_rn = अणु
	.entries = अणु
		अणु
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 13.90,
			.sr_enter_plus_निकास_समय_us = 14.80,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_B,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 13.90,
			.sr_enter_plus_निकास_समय_us = 14.80,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_C,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 13.90,
			.sr_enter_plus_निकास_समय_us = 14.80,
			.valid = true,
		पूर्ण,
		अणु
			.wm_inst = WM_D,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.72,
			.sr_निकास_समय_us = 13.90,
			.sr_enter_plus_निकास_समय_us = 14.80,
			.valid = true,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा wm_table lpddr4_wm_table_rn = अणु
	.entries = अणु
		अणु
			.wm_inst = WM_A,
			.wm_type = WM_TYPE_PSTATE_CHG,
			.pstate_latency_us = 11.65333,
			.sr_निकास_समय_us = 7.32,
			.sr_enter_plus_निकास_समय_us = 8.38,
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
अटल अचिन्हित पूर्णांक find_socclk_क्रम_voltage(काष्ठा dpm_घड़ीs *घड़ी_प्रकारable, अचिन्हित पूर्णांक voltage)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PP_SMU_NUM_SOCCLK_DPM_LEVELS; i++) अणु
		अगर (घड़ी_प्रकारable->SocClocks[i].Vol == voltage)
			वापस घड़ी_प्रकारable->SocClocks[i].Freq;
	पूर्ण

	ASSERT(0);
	वापस 0;
पूर्ण
अटल अचिन्हित पूर्णांक find_dcfclk_क्रम_voltage(काष्ठा dpm_घड़ीs *घड़ी_प्रकारable, अचिन्हित पूर्णांक voltage)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PP_SMU_NUM_DCFCLK_DPM_LEVELS; i++) अणु
		अगर (घड़ी_प्रकारable->DcfClocks[i].Vol == voltage)
			वापस घड़ी_प्रकारable->DcfClocks[i].Freq;
	पूर्ण

	ASSERT(0);
	वापस 0;
पूर्ण

अटल व्योम rn_clk_mgr_helper_populate_bw_params(काष्ठा clk_bw_params *bw_params, काष्ठा dpm_घड़ीs *घड़ी_प्रकारable, काष्ठा पूर्णांकegrated_info *bios_info)
अणु
	पूर्णांक i, j = 0;

	j = -1;

	ASSERT(PP_SMU_NUM_FCLK_DPM_LEVELS <= MAX_NUM_DPM_LVL);

	/* Find lowest DPM, FCLK is filled in reverse order*/

	क्रम (i = PP_SMU_NUM_FCLK_DPM_LEVELS - 1; i >= 0; i--) अणु
		अगर (घड़ी_प्रकारable->FClocks[i].Freq != 0 && घड़ी_प्रकारable->FClocks[i].Vol != 0) अणु
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
		bw_params->clk_table.entries[i].fclk_mhz = घड़ी_प्रकारable->FClocks[j].Freq;
		bw_params->clk_table.entries[i].memclk_mhz = घड़ी_प्रकारable->MemClocks[j].Freq;
		bw_params->clk_table.entries[i].voltage = घड़ी_प्रकारable->FClocks[j].Vol;
		bw_params->clk_table.entries[i].dcfclk_mhz = find_dcfclk_क्रम_voltage(घड़ी_प्रकारable, घड़ी_प्रकारable->FClocks[j].Vol);
		bw_params->clk_table.entries[i].socclk_mhz = find_socclk_क्रम_voltage(घड़ी_प्रकारable,
									bw_params->clk_table.entries[i].voltage);
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

व्योम rn_clk_mgr_स्थिरruct(
		काष्ठा dc_context *ctx,
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		काष्ठा pp_smu_funcs *pp_smu,
		काष्ठा dccg *dccg)
अणु
	काष्ठा dc_debug_options *debug = &ctx->dc->debug;
	काष्ठा dpm_घड़ीs घड़ी_प्रकारable = अणु 0 पूर्ण;
	क्रमागत pp_smu_status status = 0;
	पूर्णांक is_green_sardine = 0;

#अगर defined(CONFIG_DRM_AMD_DC_DCN)
	is_green_sardine = ASICREV_IS_GREEN_SARDINE(ctx->asic_id.hw_पूर्णांकernal_rev);
#पूर्ण_अगर

	clk_mgr->base.ctx = ctx;
	clk_mgr->base.funcs = &dcn21_funcs;

	clk_mgr->pp_smu = pp_smu;

	clk_mgr->dccg = dccg;
	clk_mgr->dfs_bypass_disp_clk = 0;

	clk_mgr->dprefclk_ss_percentage = 0;
	clk_mgr->dprefclk_ss_भागider = 1000;
	clk_mgr->ss_on_dprefclk = false;
	clk_mgr->dfs_ref_freq_khz = 48000;

	clk_mgr->smu_ver = rn_vbios_smu_get_smu_version(clk_mgr);

	अगर (IS_FPGA_MAXIMUS_DC(ctx->dce_environment)) अणु
		dcn21_funcs.update_घड़ीs = dcn2_update_घड़ीs_fpga;
		clk_mgr->base.dentist_vco_freq_khz = 3600000;
	पूर्ण अन्यथा अणु
		काष्ठा clk_log_info log_info = अणु0पूर्ण;

		clk_mgr->periodic_retraining_disabled = rn_vbios_smu_is_periodic_retraining_disabled(clk_mgr);

		/* SMU Version 55.51.0 and up no दीर्घer have an issue
		 * that needs to limit minimum dispclk */
		अगर (clk_mgr->smu_ver >= SMU_VER_55_51_0)
			debug->min_disp_clk_khz = 0;

		/* TODO: Check we get what we expect during bringup */
		clk_mgr->base.dentist_vco_freq_khz = get_vco_frequency_from_reg(clk_mgr);

		/* in हाल we करोn't get a value from the रेजिस्टर, use शेष */
		अगर (clk_mgr->base.dentist_vco_freq_khz == 0)
			clk_mgr->base.dentist_vco_freq_khz = 3600000;

		अगर (ctx->dc_bios->पूर्णांकegrated_info->memory_type == LpDdr4MemType) अणु
			अगर (clk_mgr->periodic_retraining_disabled) अणु
				rn_bw_params.wm_table = lpddr4_wm_table_with_disabled_ppt;
			पूर्ण अन्यथा अणु
				अगर (is_green_sardine)
					rn_bw_params.wm_table = lpddr4_wm_table_gs;
				अन्यथा
					rn_bw_params.wm_table = lpddr4_wm_table_rn;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (is_green_sardine)
				rn_bw_params.wm_table = ddr4_wm_table_gs;
			अन्यथा अणु
				अगर (ctx->dc->config.is_single_rank_dimm)
					rn_bw_params.wm_table = ddr4_1R_wm_table_rn;
				अन्यथा
					rn_bw_params.wm_table = ddr4_wm_table_rn;
			पूर्ण
		पूर्ण
		/* Saved घड़ीs configured at boot क्रम debug purposes */
		rn_dump_clk_रेजिस्टरs(&clk_mgr->base.boot_snapshot, &clk_mgr->base, &log_info);
	पूर्ण

	clk_mgr->base.dprefclk_khz = 600000;
	dce_घड़ी_पढ़ो_ss_info(clk_mgr);


	clk_mgr->base.bw_params = &rn_bw_params;

	अगर (pp_smu && pp_smu->rn_funcs.get_dpm_घड़ी_प्रकारable) अणु
		status = pp_smu->rn_funcs.get_dpm_घड़ी_प्रकारable(&pp_smu->rn_funcs.pp_smu, &घड़ी_प्रकारable);

		अगर (status == PP_SMU_RESULT_OK &&
		    ctx->dc_bios && ctx->dc_bios->पूर्णांकegrated_info) अणु
			rn_clk_mgr_helper_populate_bw_params (clk_mgr->base.bw_params, &घड़ी_प्रकारable, ctx->dc_bios->पूर्णांकegrated_info);
			/* treat memory config as single channel अगर memory is asymmetrics. */
			अगर (ctx->dc->config.is_asymmetric_memory)
				clk_mgr->base.bw_params->num_channels = 1;
		पूर्ण
	पूर्ण

	अगर (!IS_FPGA_MAXIMUS_DC(ctx->dce_environment) && clk_mgr->smu_ver >= 0x00371500) अणु
		/* enable घातerfeatures when displaycount goes to 0 */
		rn_vbios_smu_enable_48mhz_पंचांगdp_refclk_pwrdwn(clk_mgr, !debug->disable_48mhz_pwrdwn);
	पूर्ण
पूर्ण

