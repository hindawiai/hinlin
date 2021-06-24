<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#समावेश "dcn20_mpc.h"

#समावेश "reg_helper.h"
#समावेश "dc.h"
#समावेश "mem_input.h"
#समावेश "dcn10/dcn10_cm_common.h"

#घोषणा REG(reg)\
	mpc20->mpc_regs->reg

#घोषणा IND_REG(index) \
	(index)

#घोषणा CTX \
	mpc20->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	mpc20->mpc_shअगरt->field_name, mpc20->mpc_mask->field_name

#घोषणा NUM_ELEMENTS(a) (माप(a) / माप((a)[0]))

व्योम mpc2_update_blending(
	काष्ठा mpc *mpc,
	काष्ठा mpcc_blnd_cfg *blnd_cfg,
	पूर्णांक mpcc_id)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	काष्ठा mpcc *mpcc = mpc1_get_mpcc(mpc, mpcc_id);

	REG_UPDATE_7(MPCC_CONTROL[mpcc_id],
			MPCC_ALPHA_BLND_MODE,		blnd_cfg->alpha_mode,
			MPCC_ALPHA_MULTIPLIED_MODE,	blnd_cfg->pre_multiplied_alpha,
			MPCC_BLND_ACTIVE_OVERLAP_ONLY,	blnd_cfg->overlap_only,
			MPCC_GLOBAL_ALPHA,		blnd_cfg->global_alpha,
			MPCC_GLOBAL_GAIN,		blnd_cfg->global_gain,
			MPCC_BG_BPC,			blnd_cfg->background_color_bpc,
			MPCC_BOT_GAIN_MODE,		blnd_cfg->bottom_gain_mode);

	REG_SET(MPCC_TOP_GAIN[mpcc_id], 0, MPCC_TOP_GAIN, blnd_cfg->top_gain);
	REG_SET(MPCC_BOT_GAIN_INSIDE[mpcc_id], 0, MPCC_BOT_GAIN_INSIDE, blnd_cfg->bottom_inside_gain);
	REG_SET(MPCC_BOT_GAIN_OUTSIDE[mpcc_id], 0, MPCC_BOT_GAIN_OUTSIDE, blnd_cfg->bottom_outside_gain);

	mpc1_set_bg_color(mpc, &blnd_cfg->black_color, mpcc_id);
	mpcc->blnd_cfg = *blnd_cfg;
पूर्ण

व्योम mpc2_set_denorm(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		क्रमागत dc_color_depth output_depth)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	पूर्णांक denorm_mode = 0;

	चयन (output_depth) अणु
	हाल COLOR_DEPTH_666:
		denorm_mode = 1;
		अवरोध;
	हाल COLOR_DEPTH_888:
		denorm_mode = 2;
		अवरोध;
	हाल COLOR_DEPTH_999:
		denorm_mode = 3;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		denorm_mode = 4;
		अवरोध;
	हाल COLOR_DEPTH_111111:
		denorm_mode = 5;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		denorm_mode = 6;
		अवरोध;
	हाल COLOR_DEPTH_141414:
	हाल COLOR_DEPTH_161616:
	शेष:
		/* not valid used हाल! */
		अवरोध;
	पूर्ण

	REG_UPDATE(DENORM_CONTROL[opp_id],
			MPC_OUT_DENORM_MODE, denorm_mode);
पूर्ण

व्योम mpc2_set_denorm_clamp(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		काष्ठा mpc_denorm_clamp denorm_clamp)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	REG_UPDATE_2(DENORM_CONTROL[opp_id],
			MPC_OUT_DENORM_CLAMP_MAX_R_CR, denorm_clamp.clamp_max_r_cr,
			MPC_OUT_DENORM_CLAMP_MIN_R_CR, denorm_clamp.clamp_min_r_cr);
	REG_UPDATE_2(DENORM_CLAMP_G_Y[opp_id],
			MPC_OUT_DENORM_CLAMP_MAX_G_Y, denorm_clamp.clamp_max_g_y,
			MPC_OUT_DENORM_CLAMP_MIN_G_Y, denorm_clamp.clamp_min_g_y);
	REG_UPDATE_2(DENORM_CLAMP_B_CB[opp_id],
			MPC_OUT_DENORM_CLAMP_MAX_B_CB, denorm_clamp.clamp_max_b_cb,
			MPC_OUT_DENORM_CLAMP_MIN_B_CB, denorm_clamp.clamp_min_b_cb);
पूर्ण



व्योम mpc2_set_output_csc(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		स्थिर uपूर्णांक16_t *regval,
		क्रमागत mpc_output_csc_mode ocsc_mode)
अणु
	uपूर्णांक32_t cur_mode;
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	काष्ठा color_matrices_reg ocsc_regs;

	अगर (ocsc_mode == MPC_OUTPUT_CSC_DISABLE) अणु
		REG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
		वापस;
	पूर्ण

	अगर (regval == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	/* determine which CSC coefficients (A or B) we are using
	 * currently.  select the alternate set to द्विगुन buffer
	 * the CSC update so CSC is updated on frame boundary
	 */
	IX_REG_GET(MPC_OCSC_TEST_DEBUG_INDEX, MPC_OCSC_TEST_DEBUG_DATA,
						MPC_OCSC_TEST_DEBUG_DATA_STATUS_IDX,
						MPC_OCSC_TEST_DEBUG_DATA_OCSC_MODE, &cur_mode);

	अगर (cur_mode != MPC_OUTPUT_CSC_COEF_A)
		ocsc_mode = MPC_OUTPUT_CSC_COEF_A;
	अन्यथा
		ocsc_mode = MPC_OUTPUT_CSC_COEF_B;

	ocsc_regs.shअगरts.csc_c11 = mpc20->mpc_shअगरt->MPC_OCSC_C11_A;
	ocsc_regs.masks.csc_c11  = mpc20->mpc_mask->MPC_OCSC_C11_A;
	ocsc_regs.shअगरts.csc_c12 = mpc20->mpc_shअगरt->MPC_OCSC_C12_A;
	ocsc_regs.masks.csc_c12 = mpc20->mpc_mask->MPC_OCSC_C12_A;

	अगर (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_A[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_A[opp_id]);
	पूर्ण अन्यथा अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_B[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_B[opp_id]);
	पूर्ण

	cm_helper_program_color_matrices(
			mpc20->base.ctx,
			regval,
			&ocsc_regs);

	REG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
पूर्ण

व्योम mpc2_set_ocsc_शेष(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		क्रमागत dc_color_space color_space,
		क्रमागत mpc_output_csc_mode ocsc_mode)
अणु
	uपूर्णांक32_t cur_mode;
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	uपूर्णांक32_t arr_size;
	काष्ठा color_matrices_reg ocsc_regs;
	स्थिर uपूर्णांक16_t *regval = शून्य;

	अगर (ocsc_mode == MPC_OUTPUT_CSC_DISABLE) अणु
		REG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
		वापस;
	पूर्ण

	regval = find_color_matrix(color_space, &arr_size);

	अगर (regval == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	/* determine which CSC coefficients (A or B) we are using
	 * currently.  select the alternate set to द्विगुन buffer
	 * the CSC update so CSC is updated on frame boundary
	 */
	IX_REG_GET(MPC_OCSC_TEST_DEBUG_INDEX, MPC_OCSC_TEST_DEBUG_DATA,
						MPC_OCSC_TEST_DEBUG_DATA_STATUS_IDX,
						MPC_OCSC_TEST_DEBUG_DATA_OCSC_MODE, &cur_mode);

	अगर (cur_mode != MPC_OUTPUT_CSC_COEF_A)
		ocsc_mode = MPC_OUTPUT_CSC_COEF_A;
	अन्यथा
		ocsc_mode = MPC_OUTPUT_CSC_COEF_B;

	ocsc_regs.shअगरts.csc_c11 = mpc20->mpc_shअगरt->MPC_OCSC_C11_A;
	ocsc_regs.masks.csc_c11  = mpc20->mpc_mask->MPC_OCSC_C11_A;
	ocsc_regs.shअगरts.csc_c12 = mpc20->mpc_shअगरt->MPC_OCSC_C12_A;
	ocsc_regs.masks.csc_c12 = mpc20->mpc_mask->MPC_OCSC_C12_A;


	अगर (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_A[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_A[opp_id]);
	पूर्ण अन्यथा अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_B[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_B[opp_id]);
	पूर्ण

	cm_helper_program_color_matrices(
			mpc20->base.ctx,
			regval,
			&ocsc_regs);

	REG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
पूर्ण

अटल व्योम mpc2_ogam_get_reg_field(
		काष्ठा mpc *mpc,
		काष्ठा xfer_func_reg *reg)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	reg->shअगरts.exp_region0_lut_offset = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shअगरts.exp_region0_num_segments = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shअगरts.exp_region1_lut_offset = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shअगरts.exp_region1_num_segments = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->shअगरts.field_region_end = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_END_B;
	reg->masks.field_region_end = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_END_B;
	reg->shअगरts.field_region_end_slope = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->shअगरts.field_region_end_base = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->shअगरts.field_region_linear_slope = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_LINEAR_SLOPE_B;
	reg->masks.field_region_linear_slope = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_LINEAR_SLOPE_B;
	reg->shअगरts.exp_region_start = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_START_B;
	reg->masks.exp_region_start = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_START_B;
	reg->shअगरts.exp_resion_start_segment = mpc20->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = mpc20->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_START_SEGMENT_B;
पूर्ण

व्योम mpc20_घातer_on_ogam_lut(
		काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		bool घातer_on)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	REG_SET(MPCC_MEM_PWR_CTRL[mpcc_id], 0,
			MPCC_OGAM_MEM_PWR_DIS, घातer_on == true ? 1:0);

पूर्ण

अटल व्योम mpc20_configure_ogam_lut(
		काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		bool is_ram_a)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	REG_UPDATE_2(MPCC_OGAM_LUT_RAM_CONTROL[mpcc_id],
			MPCC_OGAM_LUT_WRITE_EN_MASK, 7,
			MPCC_OGAM_LUT_RAM_SEL, is_ram_a == true ? 0:1);

	REG_SET(MPCC_OGAM_LUT_INDEX[mpcc_id], 0, MPCC_OGAM_LUT_INDEX, 0);
पूर्ण

अटल क्रमागत dc_lut_mode mpc20_get_ogam_current(काष्ठा mpc *mpc, पूर्णांक mpcc_id)
अणु
	क्रमागत dc_lut_mode mode;
	uपूर्णांक32_t state_mode;
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	REG_GET(MPCC_OGAM_LUT_RAM_CONTROL[mpcc_id],
			MPCC_OGAM_CONFIG_STATUS, &state_mode);

		चयन (state_mode) अणु
		हाल 0:
			mode = LUT_BYPASS;
			अवरोध;
		हाल 1:
			mode = LUT_RAM_A;
			अवरोध;
		हाल 2:
			mode = LUT_RAM_B;
			अवरोध;
		शेष:
			mode = LUT_BYPASS;
			अवरोध;
		पूर्ण
		वापस mode;
पूर्ण

अटल व्योम mpc2_program_lutb(काष्ठा mpc *mpc, पूर्णांक mpcc_id,
			स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	काष्ठा xfer_func_reg gam_regs;

	mpc2_ogam_get_reg_field(mpc, &gam_regs);

	gam_regs.start_cntl_b = REG(MPCC_OGAM_RAMB_START_CNTL_B[mpcc_id]);
	gam_regs.start_cntl_g = REG(MPCC_OGAM_RAMB_START_CNTL_G[mpcc_id]);
	gam_regs.start_cntl_r = REG(MPCC_OGAM_RAMB_START_CNTL_R[mpcc_id]);
	gam_regs.start_slope_cntl_b = REG(MPCC_OGAM_RAMB_SLOPE_CNTL_B[mpcc_id]);
	gam_regs.start_slope_cntl_g = REG(MPCC_OGAM_RAMB_SLOPE_CNTL_G[mpcc_id]);
	gam_regs.start_slope_cntl_r = REG(MPCC_OGAM_RAMB_SLOPE_CNTL_R[mpcc_id]);
	gam_regs.start_end_cntl1_b = REG(MPCC_OGAM_RAMB_END_CNTL1_B[mpcc_id]);
	gam_regs.start_end_cntl2_b = REG(MPCC_OGAM_RAMB_END_CNTL2_B[mpcc_id]);
	gam_regs.start_end_cntl1_g = REG(MPCC_OGAM_RAMB_END_CNTL1_G[mpcc_id]);
	gam_regs.start_end_cntl2_g = REG(MPCC_OGAM_RAMB_END_CNTL2_G[mpcc_id]);
	gam_regs.start_end_cntl1_r = REG(MPCC_OGAM_RAMB_END_CNTL1_R[mpcc_id]);
	gam_regs.start_end_cntl2_r = REG(MPCC_OGAM_RAMB_END_CNTL2_R[mpcc_id]);
	gam_regs.region_start = REG(MPCC_OGAM_RAMB_REGION_0_1[mpcc_id]);
	gam_regs.region_end = REG(MPCC_OGAM_RAMB_REGION_32_33[mpcc_id]);

	cm_helper_program_xfer_func(mpc20->base.ctx, params, &gam_regs);

पूर्ण

अटल व्योम mpc2_program_luta(काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	काष्ठा xfer_func_reg gam_regs;

	mpc2_ogam_get_reg_field(mpc, &gam_regs);

	gam_regs.start_cntl_b = REG(MPCC_OGAM_RAMA_START_CNTL_B[mpcc_id]);
	gam_regs.start_cntl_g = REG(MPCC_OGAM_RAMA_START_CNTL_G[mpcc_id]);
	gam_regs.start_cntl_r = REG(MPCC_OGAM_RAMA_START_CNTL_R[mpcc_id]);
	gam_regs.start_slope_cntl_b = REG(MPCC_OGAM_RAMA_SLOPE_CNTL_B[mpcc_id]);
	gam_regs.start_slope_cntl_g = REG(MPCC_OGAM_RAMA_SLOPE_CNTL_G[mpcc_id]);
	gam_regs.start_slope_cntl_r = REG(MPCC_OGAM_RAMA_SLOPE_CNTL_R[mpcc_id]);
	gam_regs.start_end_cntl1_b = REG(MPCC_OGAM_RAMA_END_CNTL1_B[mpcc_id]);
	gam_regs.start_end_cntl2_b = REG(MPCC_OGAM_RAMA_END_CNTL2_B[mpcc_id]);
	gam_regs.start_end_cntl1_g = REG(MPCC_OGAM_RAMA_END_CNTL1_G[mpcc_id]);
	gam_regs.start_end_cntl2_g = REG(MPCC_OGAM_RAMA_END_CNTL2_G[mpcc_id]);
	gam_regs.start_end_cntl1_r = REG(MPCC_OGAM_RAMA_END_CNTL1_R[mpcc_id]);
	gam_regs.start_end_cntl2_r = REG(MPCC_OGAM_RAMA_END_CNTL2_R[mpcc_id]);
	gam_regs.region_start = REG(MPCC_OGAM_RAMA_REGION_0_1[mpcc_id]);
	gam_regs.region_end = REG(MPCC_OGAM_RAMA_REGION_32_33[mpcc_id]);

	cm_helper_program_xfer_func(mpc20->base.ctx, params, &gam_regs);

पूर्ण

अटल व्योम mpc20_program_ogam_pwl(
		काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		स्थिर काष्ठा pwl_result_data *rgb,
		uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t i;
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	PERF_TRACE();
	REG_SEQ_START();

	क्रम (i = 0 ; i < num; i++) अणु
		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, rgb[i].red_reg);
		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, rgb[i].green_reg);
		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, rgb[i].blue_reg);

		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0,
				MPCC_OGAM_LUT_DATA, rgb[i].delta_red_reg);
		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0,
				MPCC_OGAM_LUT_DATA, rgb[i].delta_green_reg);
		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0,
				MPCC_OGAM_LUT_DATA, rgb[i].delta_blue_reg);

	पूर्ण

पूर्ण

व्योम apply_DEDCN20_305_wa(
		काष्ठा mpc *mpc,
		पूर्णांक mpcc_id, क्रमागत dc_lut_mode current_mode,
		क्रमागत dc_lut_mode next_mode)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	अगर (mpc->ctx->dc->debug.cm_in_bypass) अणु
		REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		वापस;
	पूर्ण

	अगर (mpc->ctx->dc->work_arounds.dedcn20_305_wa == false) अणु
		/*hw fixed in new review*/
		वापस;
	पूर्ण
	अगर (current_mode == LUT_BYPASS)
		/*this will only work अगर OTG is locked.
		 *अगर we were to support OTG unlock हाल,
		 *the workaround will be more complex
		 */
		REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE,
			next_mode == LUT_RAM_A ? 1:2);
पूर्ण

व्योम mpc2_set_output_gamma(
		काष्ठा mpc *mpc,
		पूर्णांक mpcc_id,
		स्थिर काष्ठा pwl_params *params)
अणु
	क्रमागत dc_lut_mode current_mode;
	क्रमागत dc_lut_mode next_mode;
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);

	अगर (mpc->ctx->dc->debug.cm_in_bypass) अणु
		REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		वापस;
	पूर्ण

	अगर (params == शून्य) अणु
		REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		वापस;
	पूर्ण

	current_mode = mpc20_get_ogam_current(mpc, mpcc_id);
	अगर (current_mode == LUT_BYPASS || current_mode == LUT_RAM_A)
		next_mode = LUT_RAM_B;
	अन्यथा
		next_mode = LUT_RAM_A;

	mpc20_घातer_on_ogam_lut(mpc, mpcc_id, true);
	mpc20_configure_ogam_lut(mpc, mpcc_id, next_mode == LUT_RAM_A);

	अगर (next_mode == LUT_RAM_A)
		mpc2_program_luta(mpc, mpcc_id, params);
	अन्यथा
		mpc2_program_lutb(mpc, mpcc_id, params);

	apply_DEDCN20_305_wa(mpc, mpcc_id, current_mode, next_mode);

	mpc20_program_ogam_pwl(
			mpc, mpcc_id, params->rgb_resulted, params->hw_poपूर्णांकs_num);

	REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE,
		next_mode == LUT_RAM_A ? 1:2);
पूर्ण
व्योम mpc2_निश्चित_idle_mpcc(काष्ठा mpc *mpc, पूर्णांक id)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	अचिन्हित पूर्णांक mpc_disabled;

	ASSERT(!(mpc20->mpcc_in_use_mask & 1 << id));
	REG_GET(MPCC_STATUS[id], MPCC_DISABLED, &mpc_disabled);
	अगर (mpc_disabled)
		वापस;

	REG_WAIT(MPCC_STATUS[id],
			MPCC_IDLE, 1,
			1, 100000);
पूर्ण

व्योम mpc2_निश्चित_mpcc_idle_beक्रमe_connect(काष्ठा mpc *mpc, पूर्णांक mpcc_id)
अणु
	काष्ठा dcn20_mpc *mpc20 = TO_DCN20_MPC(mpc);
	अचिन्हित पूर्णांक top_sel, mpc_busy, mpc_idle, mpc_disabled;

	REG_GET(MPCC_TOP_SEL[mpcc_id],
			MPCC_TOP_SEL, &top_sel);

	REG_GET_3(MPCC_STATUS[mpcc_id],
			MPCC_BUSY, &mpc_busy,
			MPCC_IDLE, &mpc_idle,
			MPCC_DISABLED, &mpc_disabled);

	अगर (top_sel == 0xf) अणु
		ASSERT(!mpc_busy);
		ASSERT(mpc_idle);
		ASSERT(mpc_disabled);
	पूर्ण अन्यथा अणु
		ASSERT(!mpc_disabled);
		ASSERT(!mpc_idle);
	पूर्ण

	REG_SEQ_SUBMIT();
	PERF_TRACE();
	REG_SEQ_WAIT_DONE();
	PERF_TRACE();
पूर्ण

अटल व्योम mpc2_init_mpcc(काष्ठा mpcc *mpcc, पूर्णांक mpcc_inst)
अणु
	mpcc->mpcc_id = mpcc_inst;
	mpcc->dpp_id = 0xf;
	mpcc->mpcc_bot = शून्य;
	mpcc->blnd_cfg.overlap_only = false;
	mpcc->blnd_cfg.global_alpha = 0xff;
	mpcc->blnd_cfg.global_gain = 0xff;
	mpcc->blnd_cfg.background_color_bpc = 4;
	mpcc->blnd_cfg.bottom_gain_mode = 0;
	mpcc->blnd_cfg.top_gain = 0x1f000;
	mpcc->blnd_cfg.bottom_inside_gain = 0x1f000;
	mpcc->blnd_cfg.bottom_outside_gain = 0x1f000;
	mpcc->sm_cfg.enable = false;
पूर्ण

काष्ठा mpcc *mpc2_get_mpcc_क्रम_dpp(काष्ठा mpc_tree *tree, पूर्णांक dpp_id)
अणु
	काष्ठा mpcc *पंचांगp_mpcc = tree->opp_list;

	जबतक (पंचांगp_mpcc != शून्य) अणु
		अगर (पंचांगp_mpcc->dpp_id == 0xf || पंचांगp_mpcc->dpp_id == dpp_id)
			वापस पंचांगp_mpcc;
		पंचांगp_mpcc = पंचांगp_mpcc->mpcc_bot;
	पूर्ण
	वापस शून्य;
पूर्ण

स्थिर काष्ठा mpc_funcs dcn20_mpc_funcs = अणु
	.पढ़ो_mpcc_state = mpc1_पढ़ो_mpcc_state,
	.insert_plane = mpc1_insert_plane,
	.हटाओ_mpcc = mpc1_हटाओ_mpcc,
	.mpc_init = mpc1_mpc_init,
	.mpc_init_single_inst = mpc1_mpc_init_single_inst,
	.update_blending = mpc2_update_blending,
	.cursor_lock = mpc1_cursor_lock,
	.get_mpcc_क्रम_dpp = mpc2_get_mpcc_क्रम_dpp,
	.रुको_क्रम_idle = mpc2_निश्चित_idle_mpcc,
	.निश्चित_mpcc_idle_beक्रमe_connect = mpc2_निश्चित_mpcc_idle_beक्रमe_connect,
	.init_mpcc_list_from_hw = mpc1_init_mpcc_list_from_hw,
	.set_denorm = mpc2_set_denorm,
	.set_denorm_clamp = mpc2_set_denorm_clamp,
	.set_output_csc = mpc2_set_output_csc,
	.set_ocsc_शेष = mpc2_set_ocsc_शेष,
	.set_output_gamma = mpc2_set_output_gamma,
	.घातer_on_mpc_mem_pwr = mpc20_घातer_on_ogam_lut,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,
पूर्ण;

व्योम dcn20_mpc_स्थिरruct(काष्ठा dcn20_mpc *mpc20,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn20_mpc_रेजिस्टरs *mpc_regs,
	स्थिर काष्ठा dcn20_mpc_shअगरt *mpc_shअगरt,
	स्थिर काष्ठा dcn20_mpc_mask *mpc_mask,
	पूर्णांक num_mpcc)
अणु
	पूर्णांक i;

	mpc20->base.ctx = ctx;

	mpc20->base.funcs = &dcn20_mpc_funcs;

	mpc20->mpc_regs = mpc_regs;
	mpc20->mpc_shअगरt = mpc_shअगरt;
	mpc20->mpc_mask = mpc_mask;

	mpc20->mpcc_in_use_mask = 0;
	mpc20->num_mpcc = num_mpcc;

	क्रम (i = 0; i < MAX_MPCC; i++)
		mpc2_init_mpcc(&mpc20->base.mpcc_array[i], i);
पूर्ण

