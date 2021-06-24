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

#समावेश "dce_hwseq.h"
#समावेश "reg_helper.h"
#समावेश "hw_sequencer_private.h"
#समावेश "core_types.h"

#घोषणा CTX \
	hws->ctx
#घोषणा REG(reg)\
	hws->regs->reg

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hws->shअगरts->field_name, hws->masks->field_name

व्योम dce_enable_fe_घड़ी(काष्ठा dce_hwseq *hws,
		अचिन्हित पूर्णांक fe_inst, bool enable)
अणु
	REG_UPDATE(DCFE_CLOCK_CONTROL[fe_inst],
			DCFE_CLOCK_ENABLE, enable);
पूर्ण

व्योम dce_pipe_control_lock(काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe,
		bool lock)
अणु
	uपूर्णांक32_t lock_val = lock ? 1 : 0;
	uपूर्णांक32_t dcp_grph, scl, blnd, update_lock_mode, val;
	काष्ठा dce_hwseq *hws = dc->hwseq;

	/* Not lock pipe when blank */
	अगर (lock && pipe->stream_res.tg->funcs->is_blanked &&
	    pipe->stream_res.tg->funcs->is_blanked(pipe->stream_res.tg))
		वापस;

	val = REG_GET_4(BLND_V_UPDATE_LOCK[pipe->stream_res.tg->inst],
			BLND_DCP_GRPH_V_UPDATE_LOCK, &dcp_grph,
			BLND_SCL_V_UPDATE_LOCK, &scl,
			BLND_BLND_V_UPDATE_LOCK, &blnd,
			BLND_V_UPDATE_LOCK_MODE, &update_lock_mode);

	dcp_grph = lock_val;
	scl = lock_val;
	blnd = lock_val;
	update_lock_mode = lock_val;

	REG_SET_2(BLND_V_UPDATE_LOCK[pipe->stream_res.tg->inst], val,
			BLND_DCP_GRPH_V_UPDATE_LOCK, dcp_grph,
			BLND_SCL_V_UPDATE_LOCK, scl);

	अगर (hws->masks->BLND_BLND_V_UPDATE_LOCK != 0)
		REG_SET_2(BLND_V_UPDATE_LOCK[pipe->stream_res.tg->inst], val,
				BLND_BLND_V_UPDATE_LOCK, blnd,
				BLND_V_UPDATE_LOCK_MODE, update_lock_mode);

	अगर (hws->wa.blnd_crtc_trigger) अणु
		अगर (!lock) अणु
			uपूर्णांक32_t value = REG_READ(CRTC_H_BLANK_START_END[pipe->stream_res.tg->inst]);
			REG_WRITE(CRTC_H_BLANK_START_END[pipe->stream_res.tg->inst], value);
		पूर्ण
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
व्योम dce60_pipe_control_lock(काष्ठा dc *dc,
		काष्ठा pipe_ctx *pipe,
		bool lock)
अणु
	/* DCE6 has noत BLND_V_UPDATE_LOCKत रेजिस्टरत */
पूर्ण
#पूर्ण_अगर

व्योम dce_set_blender_mode(काष्ठा dce_hwseq *hws,
	अचिन्हित पूर्णांक blnd_inst,
	क्रमागत blnd_mode mode)
अणु
	uपूर्णांक32_t feedthrough = 1;
	uपूर्णांक32_t blnd_mode = 0;
	uपूर्णांक32_t multiplied_mode = 0;
	uपूर्णांक32_t alpha_mode = 2;

	चयन (mode) अणु
	हाल BLND_MODE_OTHER_PIPE:
		feedthrough = 0;
		blnd_mode = 1;
		alpha_mode = 0;
		अवरोध;
	हाल BLND_MODE_BLENDING:
		feedthrough = 0;
		blnd_mode = 2;
		alpha_mode = 0;
		multiplied_mode = 1;
		अवरोध;
	हाल BLND_MODE_CURRENT_PIPE:
	शेष:
		अगर (REG(BLND_CONTROL[blnd_inst]) == REG(BLNDV_CONTROL) ||
				blnd_inst == 0)
			feedthrough = 0;
		अवरोध;
	पूर्ण

	REG_UPDATE(BLND_CONTROL[blnd_inst],
		BLND_MODE, blnd_mode);

	अगर (hws->masks->BLND_ALPHA_MODE != 0) अणु
		REG_UPDATE_3(BLND_CONTROL[blnd_inst],
			BLND_FEEDTHROUGH_EN, feedthrough,
			BLND_ALPHA_MODE, alpha_mode,
			BLND_MULTIPLIED_MODE, multiplied_mode);
	पूर्ण
पूर्ण


अटल व्योम dce_disable_sram_shut_करोwn(काष्ठा dce_hwseq *hws)
अणु
	अगर (REG(DC_MEM_GLOBAL_PWR_REQ_CNTL))
		REG_UPDATE(DC_MEM_GLOBAL_PWR_REQ_CNTL,
				DC_MEM_GLOBAL_PWR_REQ_DIS, 1);
पूर्ण

अटल व्योम dce_underlay_घड़ी_enable(काष्ठा dce_hwseq *hws)
अणु
	/* toकरो: why करो we need this at boot? is dce_enable_fe_घड़ी enough? */
	अगर (REG(DCFEV_CLOCK_CONTROL))
		REG_UPDATE(DCFEV_CLOCK_CONTROL,
				DCFEV_CLOCK_ENABLE, 1);
पूर्ण

अटल व्योम enable_hw_base_light_sleep(व्योम)
अणु
	/* TODO: implement */
पूर्ण

अटल व्योम disable_sw_manual_control_light_sleep(व्योम)
अणु
	/* TODO: implement */
पूर्ण

व्योम dce_घड़ी_gating_घातer_up(काष्ठा dce_hwseq *hws,
		bool enable)
अणु
	अगर (enable) अणु
		enable_hw_base_light_sleep();
		disable_sw_manual_control_light_sleep();
	पूर्ण अन्यथा अणु
		dce_disable_sram_shut_करोwn(hws);
		dce_underlay_घड़ी_enable(hws);
	पूर्ण
पूर्ण

व्योम dce_crtc_चयन_to_clk_src(काष्ठा dce_hwseq *hws,
		काष्ठा घड़ी_source *clk_src,
		अचिन्हित पूर्णांक tg_inst)
अणु
	अगर (clk_src->id == CLOCK_SOURCE_ID_DP_DTO || clk_src->dp_clk_src) अणु
		REG_UPDATE(PIXEL_RATE_CNTL[tg_inst],
				DP_DTO0_ENABLE, 1);

	पूर्ण अन्यथा अगर (clk_src->id >= CLOCK_SOURCE_COMBO_PHY_PLL0) अणु
		uपूर्णांक32_t rate_source = clk_src->id - CLOCK_SOURCE_COMBO_PHY_PLL0;

		REG_UPDATE_2(PHYPLL_PIXEL_RATE_CNTL[tg_inst],
				PHYPLL_PIXEL_RATE_SOURCE, rate_source,
				PIXEL_RATE_PLL_SOURCE, 0);

		REG_UPDATE(PIXEL_RATE_CNTL[tg_inst],
				DP_DTO0_ENABLE, 0);

	पूर्ण अन्यथा अगर (clk_src->id <= CLOCK_SOURCE_ID_PLL2) अणु
		uपूर्णांक32_t rate_source = clk_src->id - CLOCK_SOURCE_ID_PLL0;

		REG_UPDATE_2(PIXEL_RATE_CNTL[tg_inst],
				PIXEL_RATE_SOURCE, rate_source,
				DP_DTO0_ENABLE, 0);

		अगर (REG(PHYPLL_PIXEL_RATE_CNTL[tg_inst]))
			REG_UPDATE(PHYPLL_PIXEL_RATE_CNTL[tg_inst],
					PIXEL_RATE_PLL_SOURCE, 1);
	पूर्ण अन्यथा अणु
		DC_ERR("Unknown clock source. clk_src id: %d, TG_inst: %d",
		       clk_src->id, tg_inst);
	पूर्ण
पूर्ण

/* Only use LUT क्रम 8 bit क्रमmats */
bool dce_use_lut(क्रमागत surface_pixel_क्रमmat क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
