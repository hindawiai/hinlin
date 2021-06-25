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

#समावेश "reg_helper.h"
#समावेश "dcn30_mpc.h"
#समावेश "dcn30_cm_common.h"
#समावेश "basics/conversion.h"
#समावेश "dcn10/dcn10_cm_common.h"
#समावेश "dc.h"

#घोषणा REG(reg)\
	mpc30->mpc_regs->reg

#घोषणा CTX \
	mpc30->base.ctx

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	mpc30->mpc_shअगरt->field_name, mpc30->mpc_mask->field_name


#घोषणा NUM_ELEMENTS(a) (माप(a) / माप((a)[0]))


अटल bool mpc3_is_dwb_idle(
	काष्ठा mpc *mpc,
	पूर्णांक dwb_id)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	अचिन्हित पूर्णांक status;

	REG_GET(DWB_MUX[dwb_id], MPC_DWB0_MUX_STATUS, &status);

	अगर (status == 0xf)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम mpc3_set_dwb_mux(
	काष्ठा mpc *mpc,
	पूर्णांक dwb_id,
	पूर्णांक mpcc_id)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_SET(DWB_MUX[dwb_id], 0,
		MPC_DWB0_MUX, mpcc_id);
पूर्ण

अटल व्योम mpc3_disable_dwb_mux(
	काष्ठा mpc *mpc,
	पूर्णांक dwb_id)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_SET(DWB_MUX[dwb_id], 0,
		MPC_DWB0_MUX, 0xf);
पूर्ण

अटल व्योम mpc3_set_out_rate_control(
	काष्ठा mpc *mpc,
	पूर्णांक opp_id,
	bool enable,
	bool rate_2x_mode,
	काष्ठा mpc_dwb_flow_control *flow_control)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_UPDATE_2(MUX[opp_id],
			MPC_OUT_RATE_CONTROL_DISABLE, !enable,
			MPC_OUT_RATE_CONTROL, rate_2x_mode);

	अगर (flow_control)
		REG_UPDATE_2(MUX[opp_id],
			MPC_OUT_FLOW_CONTROL_MODE, flow_control->flow_ctrl_mode,
			MPC_OUT_FLOW_CONTROL_COUNT, flow_control->flow_ctrl_cnt1);
पूर्ण

अटल क्रमागत dc_lut_mode mpc3_get_ogam_current(काष्ठा mpc *mpc, पूर्णांक mpcc_id)
अणु
	/*Contrary to DCN2 and DCN1 wherein a single status रेजिस्टर field holds this info;
	 *in DCN3/3AG, we need to पढ़ो two separate fields to retrieve the same info
	 */
	क्रमागत dc_lut_mode mode;
	uपूर्णांक32_t state_mode;
	uपूर्णांक32_t state_ram_lut_in_use;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_GET_2(MPCC_OGAM_CONTROL[mpcc_id],
			MPCC_OGAM_MODE_CURRENT, &state_mode,
			MPCC_OGAM_SELECT_CURRENT, &state_ram_lut_in_use);

		चयन (state_mode) अणु
		हाल 0:
			mode = LUT_BYPASS;
			अवरोध;
		हाल 2:
			चयन (state_ram_lut_in_use) अणु
			हाल 0:
				mode = LUT_RAM_A;
				अवरोध;
			हाल 1:
				mode = LUT_RAM_B;
				अवरोध;
			शेष:
				mode = LUT_BYPASS;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			mode = LUT_BYPASS;
			अवरोध;
		पूर्ण
		वापस mode;
पूर्ण

अटल व्योम mpc3_घातer_on_ogam_lut(
		काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		bool घातer_on)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	/*
	 * Powering on: क्रमce memory active so the LUT can be updated.
	 * Powering off: allow entering memory low घातer mode
	 *
	 * Memory low घातer mode is controlled during MPC OGAM LUT init.
	 */
	REG_UPDATE(MPCC_MEM_PWR_CTRL[mpcc_id],
		   MPCC_OGAM_MEM_PWR_DIS, घातer_on != 0);

	/* Wait क्रम memory to be घातered on - we won't be able to ग_लिखो to it otherwise. */
	अगर (घातer_on)
		REG_WAIT(MPCC_MEM_PWR_CTRL[mpcc_id], MPCC_OGAM_MEM_PWR_STATE, 0, 10, 10);
पूर्ण

अटल व्योम mpc3_configure_ogam_lut(
		काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		bool is_ram_a)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_UPDATE_2(MPCC_OGAM_LUT_CONTROL[mpcc_id],
			MPCC_OGAM_LUT_WRITE_COLOR_MASK, 7,
			MPCC_OGAM_LUT_HOST_SEL, is_ram_a == true ? 0:1);

	REG_SET(MPCC_OGAM_LUT_INDEX[mpcc_id], 0, MPCC_OGAM_LUT_INDEX, 0);
पूर्ण

अटल व्योम mpc3_ogam_get_reg_field(
		काष्ठा mpc *mpc,
		काष्ठा dcn3_xfer_func_reg *reg)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	reg->shअगरts.field_region_start_base = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_START_BASE_B;
	reg->masks.field_region_start_base = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_START_BASE_B;
	reg->shअगरts.field_offset = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_OFFSET_B;
	reg->masks.field_offset = mpc30->mpc_mask->MPCC_OGAM_RAMA_OFFSET_B;

	reg->shअगरts.exp_region0_lut_offset = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shअगरts.exp_region0_num_segments = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shअगरts.exp_region1_lut_offset = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shअगरts.exp_region1_num_segments = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;

	reg->shअगरts.field_region_end = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_END_B;
	reg->masks.field_region_end = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_END_B;
	reg->shअगरts.field_region_end_slope = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_END_SLOPE_B;
	reg->shअगरts.field_region_end_base = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_END_BASE_B;
	reg->shअगरts.field_region_linear_slope = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_START_SLOPE_B;
	reg->masks.field_region_linear_slope = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_START_SLOPE_B;
	reg->shअगरts.exp_region_start = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_START_B;
	reg->masks.exp_region_start = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_START_B;
	reg->shअगरts.exp_resion_start_segment = mpc30->mpc_shअगरt->MPCC_OGAM_RAMA_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = mpc30->mpc_mask->MPCC_OGAM_RAMA_EXP_REGION_START_SEGMENT_B;
पूर्ण

अटल व्योम mpc3_program_luta(काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	काष्ठा dcn3_xfer_func_reg gam_regs;

	mpc3_ogam_get_reg_field(mpc, &gam_regs);

	gam_regs.start_cntl_b = REG(MPCC_OGAM_RAMA_START_CNTL_B[mpcc_id]);
	gam_regs.start_cntl_g = REG(MPCC_OGAM_RAMA_START_CNTL_G[mpcc_id]);
	gam_regs.start_cntl_r = REG(MPCC_OGAM_RAMA_START_CNTL_R[mpcc_id]);
	gam_regs.start_slope_cntl_b = REG(MPCC_OGAM_RAMA_START_SLOPE_CNTL_B[mpcc_id]);
	gam_regs.start_slope_cntl_g = REG(MPCC_OGAM_RAMA_START_SLOPE_CNTL_G[mpcc_id]);
	gam_regs.start_slope_cntl_r = REG(MPCC_OGAM_RAMA_START_SLOPE_CNTL_R[mpcc_id]);
	gam_regs.start_end_cntl1_b = REG(MPCC_OGAM_RAMA_END_CNTL1_B[mpcc_id]);
	gam_regs.start_end_cntl2_b = REG(MPCC_OGAM_RAMA_END_CNTL2_B[mpcc_id]);
	gam_regs.start_end_cntl1_g = REG(MPCC_OGAM_RAMA_END_CNTL1_G[mpcc_id]);
	gam_regs.start_end_cntl2_g = REG(MPCC_OGAM_RAMA_END_CNTL2_G[mpcc_id]);
	gam_regs.start_end_cntl1_r = REG(MPCC_OGAM_RAMA_END_CNTL1_R[mpcc_id]);
	gam_regs.start_end_cntl2_r = REG(MPCC_OGAM_RAMA_END_CNTL2_R[mpcc_id]);
	gam_regs.region_start = REG(MPCC_OGAM_RAMA_REGION_0_1[mpcc_id]);
	gam_regs.region_end = REG(MPCC_OGAM_RAMA_REGION_32_33[mpcc_id]);
	//New रेजिस्टरs in DCN3AG/DCN OGAM block
	gam_regs.offset_b =  REG(MPCC_OGAM_RAMA_OFFSET_B[mpcc_id]);
	gam_regs.offset_g =  REG(MPCC_OGAM_RAMA_OFFSET_G[mpcc_id]);
	gam_regs.offset_r =  REG(MPCC_OGAM_RAMA_OFFSET_R[mpcc_id]);
	gam_regs.start_base_cntl_b = REG(MPCC_OGAM_RAMA_START_BASE_CNTL_B[mpcc_id]);
	gam_regs.start_base_cntl_g = REG(MPCC_OGAM_RAMA_START_BASE_CNTL_G[mpcc_id]);
	gam_regs.start_base_cntl_r = REG(MPCC_OGAM_RAMA_START_BASE_CNTL_R[mpcc_id]);

	cm_helper_program_gamcor_xfer_func(mpc30->base.ctx, params, &gam_regs);
पूर्ण

अटल व्योम mpc3_program_lutb(काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		स्थिर काष्ठा pwl_params *params)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	काष्ठा dcn3_xfer_func_reg gam_regs;

	mpc3_ogam_get_reg_field(mpc, &gam_regs);

	gam_regs.start_cntl_b = REG(MPCC_OGAM_RAMB_START_CNTL_B[mpcc_id]);
	gam_regs.start_cntl_g = REG(MPCC_OGAM_RAMB_START_CNTL_G[mpcc_id]);
	gam_regs.start_cntl_r = REG(MPCC_OGAM_RAMB_START_CNTL_R[mpcc_id]);
	gam_regs.start_slope_cntl_b = REG(MPCC_OGAM_RAMB_START_SLOPE_CNTL_B[mpcc_id]);
	gam_regs.start_slope_cntl_g = REG(MPCC_OGAM_RAMB_START_SLOPE_CNTL_G[mpcc_id]);
	gam_regs.start_slope_cntl_r = REG(MPCC_OGAM_RAMB_START_SLOPE_CNTL_R[mpcc_id]);
	gam_regs.start_end_cntl1_b = REG(MPCC_OGAM_RAMB_END_CNTL1_B[mpcc_id]);
	gam_regs.start_end_cntl2_b = REG(MPCC_OGAM_RAMB_END_CNTL2_B[mpcc_id]);
	gam_regs.start_end_cntl1_g = REG(MPCC_OGAM_RAMB_END_CNTL1_G[mpcc_id]);
	gam_regs.start_end_cntl2_g = REG(MPCC_OGAM_RAMB_END_CNTL2_G[mpcc_id]);
	gam_regs.start_end_cntl1_r = REG(MPCC_OGAM_RAMB_END_CNTL1_R[mpcc_id]);
	gam_regs.start_end_cntl2_r = REG(MPCC_OGAM_RAMB_END_CNTL2_R[mpcc_id]);
	gam_regs.region_start = REG(MPCC_OGAM_RAMB_REGION_0_1[mpcc_id]);
	gam_regs.region_end = REG(MPCC_OGAM_RAMB_REGION_32_33[mpcc_id]);
	//New रेजिस्टरs in DCN3AG/DCN OGAM block
	gam_regs.offset_b =  REG(MPCC_OGAM_RAMB_OFFSET_B[mpcc_id]);
	gam_regs.offset_g =  REG(MPCC_OGAM_RAMB_OFFSET_G[mpcc_id]);
	gam_regs.offset_r =  REG(MPCC_OGAM_RAMB_OFFSET_R[mpcc_id]);
	gam_regs.start_base_cntl_b = REG(MPCC_OGAM_RAMB_START_BASE_CNTL_B[mpcc_id]);
	gam_regs.start_base_cntl_g = REG(MPCC_OGAM_RAMB_START_BASE_CNTL_G[mpcc_id]);
	gam_regs.start_base_cntl_r = REG(MPCC_OGAM_RAMB_START_BASE_CNTL_R[mpcc_id]);

	cm_helper_program_gamcor_xfer_func(mpc30->base.ctx, params, &gam_regs);
पूर्ण


अटल व्योम mpc3_program_ogam_pwl(
		काष्ठा mpc *mpc, पूर्णांक mpcc_id,
		स्थिर काष्ठा pwl_result_data *rgb,
		uपूर्णांक32_t num)
अणु
	uपूर्णांक32_t i;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	uपूर्णांक32_t last_base_value_red = rgb[num-1].red_reg + rgb[num-1].delta_red_reg;
	uपूर्णांक32_t last_base_value_green = rgb[num-1].green_reg + rgb[num-1].delta_green_reg;
	uपूर्णांक32_t last_base_value_blue = rgb[num-1].blue_reg + rgb[num-1].delta_blue_reg;

	/*the entries of DCN3AG gamma LUTs take 18bit base values as opposed to
	 *38 base+delta values per entry in earlier DCN architectures
	 *last base value क्रम our lut is compute by adding the last base value
	 *in our data + last delta
	 */

	अगर (is_rgb_equal(rgb,  num)) अणु
		क्रम (i = 0 ; i < num; i++)
			REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, rgb[i].red_reg);

		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, last_base_value_red);

	पूर्ण अन्यथा अणु

		REG_UPDATE(MPCC_OGAM_LUT_CONTROL[mpcc_id],
				MPCC_OGAM_LUT_WRITE_COLOR_MASK, 4);

		क्रम (i = 0 ; i < num; i++)
			REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, rgb[i].red_reg);

		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, last_base_value_red);

		REG_SET(MPCC_OGAM_LUT_INDEX[mpcc_id], 0, MPCC_OGAM_LUT_INDEX, 0);

		REG_UPDATE(MPCC_OGAM_LUT_CONTROL[mpcc_id],
				MPCC_OGAM_LUT_WRITE_COLOR_MASK, 2);

		क्रम (i = 0 ; i < num; i++)
			REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, rgb[i].green_reg);

		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, last_base_value_green);

		REG_SET(MPCC_OGAM_LUT_INDEX[mpcc_id], 0, MPCC_OGAM_LUT_INDEX, 0);

		REG_UPDATE(MPCC_OGAM_LUT_CONTROL[mpcc_id],
				MPCC_OGAM_LUT_WRITE_COLOR_MASK, 1);

		क्रम (i = 0 ; i < num; i++)
			REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, rgb[i].blue_reg);

		REG_SET(MPCC_OGAM_LUT_DATA[mpcc_id], 0, MPCC_OGAM_LUT_DATA, last_base_value_blue);
	पूर्ण

पूर्ण

व्योम mpc3_set_output_gamma(
		काष्ठा mpc *mpc,
		पूर्णांक mpcc_id,
		स्थिर काष्ठा pwl_params *params)
अणु
	क्रमागत dc_lut_mode current_mode;
	क्रमागत dc_lut_mode next_mode;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	अगर (mpc->ctx->dc->debug.cm_in_bypass) अणु
		REG_SET(MPCC_OGAM_MODE[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		वापस;
	पूर्ण

	अगर (params == शून्य) अणु //disable OGAM
		REG_SET(MPCC_OGAM_CONTROL[mpcc_id], 0, MPCC_OGAM_MODE, 0);
		वापस;
	पूर्ण
	//enable OGAM
	REG_SET(MPCC_OGAM_CONTROL[mpcc_id], 0, MPCC_OGAM_MODE, 2);

	current_mode = mpc3_get_ogam_current(mpc, mpcc_id);
	अगर (current_mode == LUT_BYPASS)
		next_mode = LUT_RAM_A;
	अन्यथा अगर (current_mode == LUT_RAM_A)
		next_mode = LUT_RAM_B;
	अन्यथा
		next_mode = LUT_RAM_A;

	mpc3_घातer_on_ogam_lut(mpc, mpcc_id, true);
	mpc3_configure_ogam_lut(mpc, mpcc_id, next_mode == LUT_RAM_A);

	अगर (next_mode == LUT_RAM_A)
		mpc3_program_luta(mpc, mpcc_id, params);
	अन्यथा
		mpc3_program_lutb(mpc, mpcc_id, params);

	mpc3_program_ogam_pwl(
			mpc, mpcc_id, params->rgb_resulted, params->hw_poपूर्णांकs_num);

	/*we need to program 2 fields here as apposed to 1*/
	REG_UPDATE(MPCC_OGAM_CONTROL[mpcc_id],
			MPCC_OGAM_SELECT, next_mode == LUT_RAM_A ? 0:1);

	अगर (mpc->ctx->dc->debug.enable_mem_low_घातer.bits.mpc)
		mpc3_घातer_on_ogam_lut(mpc, mpcc_id, false);
पूर्ण

व्योम mpc3_set_denorm(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		क्रमागत dc_color_depth output_depth)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	/* De-normalize Fixed U1.13 color data to dअगरferent target bit depths. 0 is bypass*/
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

व्योम mpc3_set_denorm_clamp(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		काष्ठा mpc_denorm_clamp denorm_clamp)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	/*program min and max clamp values क्रम the pixel components*/
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

अटल क्रमागत dc_lut_mode mpc3_get_shaper_current(काष्ठा mpc *mpc, uपूर्णांक32_t rmu_idx)
अणु
	क्रमागत dc_lut_mode mode;
	uपूर्णांक32_t state_mode;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_GET(SHAPER_CONTROL[rmu_idx],
			MPC_RMU_SHAPER_LUT_MODE_CURRENT, &state_mode);

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

अटल व्योम mpc3_configure_shaper_lut(
		काष्ठा mpc *mpc,
		bool is_ram_a,
		uपूर्णांक32_t rmu_idx)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_UPDATE(SHAPER_LUT_WRITE_EN_MASK[rmu_idx],
			MPC_RMU_SHAPER_LUT_WRITE_EN_MASK, 7);
	REG_UPDATE(SHAPER_LUT_WRITE_EN_MASK[rmu_idx],
			MPC_RMU_SHAPER_LUT_WRITE_SEL, is_ram_a == true ? 0:1);
	REG_SET(SHAPER_LUT_INDEX[rmu_idx], 0, MPC_RMU_SHAPER_LUT_INDEX, 0);
पूर्ण

अटल व्योम mpc3_program_shaper_luta_settings(
		काष्ठा mpc *mpc,
		स्थिर काष्ठा pwl_params *params,
		uपूर्णांक32_t rmu_idx)
अणु
	स्थिर काष्ठा gamma_curve *curve;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_SET_2(SHAPER_RAMA_START_CNTL_B[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].blue.custom_भग्न_x,
		MPC_RMU_SHAPER_RAMA_EXP_REGION_START_SEGMENT_B, 0);
	REG_SET_2(SHAPER_RAMA_START_CNTL_G[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].green.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_SEGMENT_B, 0);
	REG_SET_2(SHAPER_RAMA_START_CNTL_R[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].red.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_SEGMENT_B, 0);

	REG_SET_2(SHAPER_RAMA_END_CNTL_B[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_y);
	REG_SET_2(SHAPER_RAMA_END_CNTL_G[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].green.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].green.custom_भग्न_y);
	REG_SET_2(SHAPER_RAMA_END_CNTL_R[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].red.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].red.custom_भग्न_y);

	curve = params->arr_curve_poपूर्णांकs;
	REG_SET_4(SHAPER_RAMA_REGION_0_1[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_2_3[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_4_5[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_6_7[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_8_9[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_10_11[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_12_13[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_14_15[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);


	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_16_17[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_18_19[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_20_21[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_22_23[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_24_25[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_26_27[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_28_29[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_30_31[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMA_REGION_32_33[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
पूर्ण

अटल व्योम mpc3_program_shaper_lutb_settings(
		काष्ठा mpc *mpc,
		स्थिर काष्ठा pwl_params *params,
		uपूर्णांक32_t rmu_idx)
अणु
	स्थिर काष्ठा gamma_curve *curve;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_SET_2(SHAPER_RAMB_START_CNTL_B[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].blue.custom_भग्न_x,
		MPC_RMU_SHAPER_RAMA_EXP_REGION_START_SEGMENT_B, 0);
	REG_SET_2(SHAPER_RAMB_START_CNTL_G[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].green.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_SEGMENT_B, 0);
	REG_SET_2(SHAPER_RAMB_START_CNTL_R[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_B, params->corner_poपूर्णांकs[0].red.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_START_SEGMENT_B, 0);

	REG_SET_2(SHAPER_RAMB_END_CNTL_B[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].blue.custom_भग्न_y);
	REG_SET_2(SHAPER_RAMB_END_CNTL_G[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].green.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].green.custom_भग्न_y);
	REG_SET_2(SHAPER_RAMB_END_CNTL_R[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_B, params->corner_poपूर्णांकs[1].red.custom_भग्न_x,
			MPC_RMU_SHAPER_RAMA_EXP_REGION_END_BASE_B, params->corner_poपूर्णांकs[1].red.custom_भग्न_y);

	curve = params->arr_curve_poपूर्णांकs;
	REG_SET_4(SHAPER_RAMB_REGION_0_1[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_2_3[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);


	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_4_5[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_6_7[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_8_9[rmu_idx], 0,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_10_11[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_12_13[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_14_15[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);


	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_16_17[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_18_19[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_20_21[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_22_23[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_24_25[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_26_27[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_28_29[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_30_31[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(SHAPER_RAMB_REGION_32_33[rmu_idx], 0,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_LUT_OFFSET, curve[0].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_LUT_OFFSET, curve[1].offset,
			MPC_RMU_SHAPER_RAMA_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);
पूर्ण


अटल व्योम mpc3_program_shaper_lut(
		काष्ठा mpc *mpc,
		स्थिर काष्ठा pwl_result_data *rgb,
		uपूर्णांक32_t num,
		uपूर्णांक32_t rmu_idx)
अणु
	uपूर्णांक32_t i, red, green, blue;
	uपूर्णांक32_t  red_delta, green_delta, blue_delta;
	uपूर्णांक32_t  red_value, green_value, blue_value;

	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	क्रम (i = 0 ; i < num; i++) अणु

		red   = rgb[i].red_reg;
		green = rgb[i].green_reg;
		blue  = rgb[i].blue_reg;

		red_delta   = rgb[i].delta_red_reg;
		green_delta = rgb[i].delta_green_reg;
		blue_delta  = rgb[i].delta_blue_reg;

		red_value   = ((red_delta   & 0x3ff) << 14) | (red   & 0x3fff);
		green_value = ((green_delta & 0x3ff) << 14) | (green & 0x3fff);
		blue_value  = ((blue_delta  & 0x3ff) << 14) | (blue  & 0x3fff);

		REG_SET(SHAPER_LUT_DATA[rmu_idx], 0, MPC_RMU_SHAPER_LUT_DATA, red_value);
		REG_SET(SHAPER_LUT_DATA[rmu_idx], 0, MPC_RMU_SHAPER_LUT_DATA, green_value);
		REG_SET(SHAPER_LUT_DATA[rmu_idx], 0, MPC_RMU_SHAPER_LUT_DATA, blue_value);
	पूर्ण

पूर्ण

अटल व्योम mpc3_घातer_on_shaper_3dlut(
		काष्ठा mpc *mpc,
		uपूर्णांक32_t rmu_idx,
	bool घातer_on)
अणु
	uपूर्णांक32_t घातer_status_shaper = 2;
	uपूर्णांक32_t घातer_status_3dlut  = 2;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	पूर्णांक max_retries = 10;

	अगर (rmu_idx == 0) अणु
		REG_SET(MPC_RMU_MEM_PWR_CTRL, 0,
			MPC_RMU0_MEM_PWR_DIS, घातer_on == true ? 1:0);
		/* रुको क्रम memory to fully घातer up */
		अगर (घातer_on && mpc->ctx->dc->debug.enable_mem_low_घातer.bits.mpc) अणु
			REG_WAIT(MPC_RMU_MEM_PWR_CTRL, MPC_RMU0_SHAPER_MEM_PWR_STATE, 0, 1, max_retries);
			REG_WAIT(MPC_RMU_MEM_PWR_CTRL, MPC_RMU0_3DLUT_MEM_PWR_STATE, 0, 1, max_retries);
		पूर्ण

		/*पढ़ो status is not mandatory, it is just क्रम debugging*/
		REG_GET(MPC_RMU_MEM_PWR_CTRL, MPC_RMU0_SHAPER_MEM_PWR_STATE, &घातer_status_shaper);
		REG_GET(MPC_RMU_MEM_PWR_CTRL, MPC_RMU0_3DLUT_MEM_PWR_STATE, &घातer_status_3dlut);
	पूर्ण अन्यथा अगर (rmu_idx == 1) अणु
		REG_SET(MPC_RMU_MEM_PWR_CTRL, 0,
			MPC_RMU1_MEM_PWR_DIS, घातer_on == true ? 1:0);
		अगर (घातer_on && mpc->ctx->dc->debug.enable_mem_low_घातer.bits.mpc) अणु
			REG_WAIT(MPC_RMU_MEM_PWR_CTRL, MPC_RMU1_SHAPER_MEM_PWR_STATE, 0, 1, max_retries);
			REG_WAIT(MPC_RMU_MEM_PWR_CTRL, MPC_RMU1_3DLUT_MEM_PWR_STATE, 0, 1, max_retries);
		पूर्ण

		REG_GET(MPC_RMU_MEM_PWR_CTRL, MPC_RMU1_SHAPER_MEM_PWR_STATE, &घातer_status_shaper);
		REG_GET(MPC_RMU_MEM_PWR_CTRL, MPC_RMU1_3DLUT_MEM_PWR_STATE, &घातer_status_3dlut);
	पूर्ण
	/*TODO Add rmu_idx == 2 क्रम SIENNA_CICHLID */
	अगर (घातer_status_shaper != 0 && घातer_on == true)
		BREAK_TO_DEBUGGER();

	अगर (घातer_status_3dlut != 0 && घातer_on == true)
		BREAK_TO_DEBUGGER();
पूर्ण



bool mpc3_program_shaper(
		काष्ठा mpc *mpc,
		स्थिर काष्ठा pwl_params *params,
		uपूर्णांक32_t rmu_idx)
अणु
	क्रमागत dc_lut_mode current_mode;
	क्रमागत dc_lut_mode next_mode;

	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	अगर (params == शून्य) अणु
		REG_SET(SHAPER_CONTROL[rmu_idx], 0, MPC_RMU_SHAPER_LUT_MODE, 0);
		वापस false;
	पूर्ण

	अगर (mpc->ctx->dc->debug.enable_mem_low_घातer.bits.mpc)
		mpc3_घातer_on_shaper_3dlut(mpc, rmu_idx, true);

	current_mode = mpc3_get_shaper_current(mpc, rmu_idx);

	अगर (current_mode == LUT_BYPASS || current_mode == LUT_RAM_A)
		next_mode = LUT_RAM_B;
	अन्यथा
		next_mode = LUT_RAM_A;

	mpc3_configure_shaper_lut(mpc, next_mode == LUT_RAM_A ? true:false, rmu_idx);

	अगर (next_mode == LUT_RAM_A)
		mpc3_program_shaper_luta_settings(mpc, params, rmu_idx);
	अन्यथा
		mpc3_program_shaper_lutb_settings(mpc, params, rmu_idx);

	mpc3_program_shaper_lut(
			mpc, params->rgb_resulted, params->hw_poपूर्णांकs_num, rmu_idx);

	REG_SET(SHAPER_CONTROL[rmu_idx], 0, MPC_RMU_SHAPER_LUT_MODE, next_mode == LUT_RAM_A ? 1:2);
	mpc3_घातer_on_shaper_3dlut(mpc, rmu_idx, false);

	वापस true;
पूर्ण

अटल व्योम mpc3_set_3dlut_mode(
		काष्ठा mpc *mpc,
		क्रमागत dc_lut_mode mode,
		bool is_color_channel_12bits,
		bool is_lut_size17x17x17,
		uपूर्णांक32_t rmu_idx)
अणु
	uपूर्णांक32_t lut_mode;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	अगर (mode == LUT_BYPASS)
		lut_mode = 0;
	अन्यथा अगर (mode == LUT_RAM_A)
		lut_mode = 1;
	अन्यथा
		lut_mode = 2;

	REG_UPDATE_2(RMU_3DLUT_MODE[rmu_idx],
			MPC_RMU_3DLUT_MODE, lut_mode,
			MPC_RMU_3DLUT_SIZE, is_lut_size17x17x17 == true ? 0 : 1);
पूर्ण

अटल क्रमागत dc_lut_mode get3dlut_config(
			काष्ठा mpc *mpc,
			bool *is_17x17x17,
			bool *is_12bits_color_channel,
			पूर्णांक rmu_idx)
अणु
	uपूर्णांक32_t i_mode, i_enable_10bits, lut_size;
	क्रमागत dc_lut_mode mode;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_GET(RMU_3DLUT_MODE[rmu_idx],
			MPC_RMU_3DLUT_MODE_CURRENT,  &i_mode);

	REG_GET(RMU_3DLUT_READ_WRITE_CONTROL[rmu_idx],
			MPC_RMU_3DLUT_30BIT_EN, &i_enable_10bits);

	चयन (i_mode) अणु
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
	अगर (i_enable_10bits > 0)
		*is_12bits_color_channel = false;
	अन्यथा
		*is_12bits_color_channel = true;

	REG_GET(RMU_3DLUT_MODE[rmu_idx], MPC_RMU_3DLUT_SIZE, &lut_size);

	अगर (lut_size == 0)
		*is_17x17x17 = true;
	अन्यथा
		*is_17x17x17 = false;

	वापस mode;
पूर्ण

अटल व्योम mpc3_select_3dlut_ram(
		काष्ठा mpc *mpc,
		क्रमागत dc_lut_mode mode,
		bool is_color_channel_12bits,
		uपूर्णांक32_t rmu_idx)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_UPDATE_2(RMU_3DLUT_READ_WRITE_CONTROL[rmu_idx],
		MPC_RMU_3DLUT_RAM_SEL, mode == LUT_RAM_A ? 0 : 1,
		MPC_RMU_3DLUT_30BIT_EN, is_color_channel_12bits == true ? 0:1);
पूर्ण

अटल व्योम mpc3_select_3dlut_ram_mask(
		काष्ठा mpc *mpc,
		uपूर्णांक32_t ram_selection_mask,
		uपूर्णांक32_t rmu_idx)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	REG_UPDATE(RMU_3DLUT_READ_WRITE_CONTROL[rmu_idx], MPC_RMU_3DLUT_WRITE_EN_MASK,
			ram_selection_mask);
	REG_SET(RMU_3DLUT_INDEX[rmu_idx], 0, MPC_RMU_3DLUT_INDEX, 0);
पूर्ण

अटल व्योम mpc3_set3dlut_ram12(
		काष्ठा mpc *mpc,
		स्थिर काष्ठा dc_rgb *lut,
		uपूर्णांक32_t entries,
		uपूर्णांक32_t rmu_idx)
अणु
	uपूर्णांक32_t i, red, green, blue, red1, green1, blue1;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	क्रम (i = 0 ; i < entries; i += 2) अणु
		red   = lut[i].red<<4;
		green = lut[i].green<<4;
		blue  = lut[i].blue<<4;
		red1   = lut[i+1].red<<4;
		green1 = lut[i+1].green<<4;
		blue1  = lut[i+1].blue<<4;

		REG_SET_2(RMU_3DLUT_DATA[rmu_idx], 0,
				MPC_RMU_3DLUT_DATA0, red,
				MPC_RMU_3DLUT_DATA1, red1);

		REG_SET_2(RMU_3DLUT_DATA[rmu_idx], 0,
				MPC_RMU_3DLUT_DATA0, green,
				MPC_RMU_3DLUT_DATA1, green1);

		REG_SET_2(RMU_3DLUT_DATA[rmu_idx], 0,
				MPC_RMU_3DLUT_DATA0, blue,
				MPC_RMU_3DLUT_DATA1, blue1);
	पूर्ण
पूर्ण

अटल व्योम mpc3_set3dlut_ram10(
		काष्ठा mpc *mpc,
		स्थिर काष्ठा dc_rgb *lut,
		uपूर्णांक32_t entries,
		uपूर्णांक32_t rmu_idx)
अणु
	uपूर्णांक32_t i, red, green, blue, value;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	क्रम (i = 0; i < entries; i++) अणु
		red   = lut[i].red;
		green = lut[i].green;
		blue  = lut[i].blue;
		//should we shअगरt red 22bit and green 12? ask Nvenko
		value = (red<<20) | (green<<10) | blue;

		REG_SET(RMU_3DLUT_DATA_30BIT[rmu_idx], 0, MPC_RMU_3DLUT_DATA_30BIT, value);
	पूर्ण

पूर्ण


अटल व्योम mpc3_init_mpcc(काष्ठा mpcc *mpcc, पूर्णांक mpcc_inst)
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
	mpcc->shared_bottom = false;
पूर्ण

अटल व्योम program_gamut_remap(
		काष्ठा dcn30_mpc *mpc30,
		पूर्णांक mpcc_id,
		स्थिर uपूर्णांक16_t *regval,
		पूर्णांक select)
अणु
	uपूर्णांक16_t selection = 0;
	काष्ठा color_matrices_reg gam_regs;

	अगर (regval == शून्य || select == GAMUT_REMAP_BYPASS) अणु
		REG_SET(MPCC_GAMUT_REMAP_MODE[mpcc_id], 0,
				MPCC_GAMUT_REMAP_MODE, GAMUT_REMAP_BYPASS);
		वापस;
	पूर्ण
	चयन (select) अणु
	हाल GAMUT_REMAP_COEFF:
		selection = 1;
		अवरोध;
		/*this corresponds to GAMUT_REMAP coefficients set B
		 * we करोn't have common coefficient sets in dcn3ag/dcn3
		 */
	हाल GAMUT_REMAP_COMA_COEFF:
		selection = 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	gam_regs.shअगरts.csc_c11 = mpc30->mpc_shअगरt->MPCC_GAMUT_REMAP_C11_A;
	gam_regs.masks.csc_c11  = mpc30->mpc_mask->MPCC_GAMUT_REMAP_C11_A;
	gam_regs.shअगरts.csc_c12 = mpc30->mpc_shअगरt->MPCC_GAMUT_REMAP_C12_A;
	gam_regs.masks.csc_c12 = mpc30->mpc_mask->MPCC_GAMUT_REMAP_C12_A;


	अगर (select == GAMUT_REMAP_COEFF) अणु
		gam_regs.csc_c11_c12 = REG(MPC_GAMUT_REMAP_C11_C12_A[mpcc_id]);
		gam_regs.csc_c33_c34 = REG(MPC_GAMUT_REMAP_C33_C34_A[mpcc_id]);

		cm_helper_program_color_matrices(
				mpc30->base.ctx,
				regval,
				&gam_regs);

	पूर्ण अन्यथा  अगर (select == GAMUT_REMAP_COMA_COEFF) अणु

		gam_regs.csc_c11_c12 = REG(MPC_GAMUT_REMAP_C11_C12_B[mpcc_id]);
		gam_regs.csc_c33_c34 = REG(MPC_GAMUT_REMAP_C33_C34_B[mpcc_id]);

		cm_helper_program_color_matrices(
				mpc30->base.ctx,
				regval,
				&gam_regs);

	पूर्ण
	//select coefficient set to use
	REG_SET(MPCC_GAMUT_REMAP_MODE[mpcc_id], 0,
					MPCC_GAMUT_REMAP_MODE, selection);
पूर्ण

व्योम mpc3_set_gamut_remap(
		काष्ठा mpc *mpc,
		पूर्णांक mpcc_id,
		स्थिर काष्ठा mpc_grph_gamut_adjusपंचांगent *adjust)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	पूर्णांक i = 0;
	पूर्णांक gamut_mode;

	अगर (adjust->gamut_adjust_type != GRAPHICS_GAMUT_ADJUST_TYPE_SW)
		program_gamut_remap(mpc30, mpcc_id, शून्य, GAMUT_REMAP_BYPASS);
	अन्यथा अणु
		काष्ठा fixed31_32 arr_matrix[12];
		uपूर्णांक16_t arr_reg_val[12];

		क्रम (i = 0; i < 12; i++)
			arr_matrix[i] = adjust->temperature_matrix[i];

		convert_भग्न_matrix(
			arr_reg_val, arr_matrix, 12);

		//current coefficient set in use
		REG_GET(MPCC_GAMUT_REMAP_MODE[mpcc_id], MPCC_GAMUT_REMAP_MODE_CURRENT, &gamut_mode);

		अगर (gamut_mode == 0)
			gamut_mode = 1; //use coefficient set A
		अन्यथा अगर (gamut_mode == 1)
			gamut_mode = 2;
		अन्यथा
			gamut_mode = 1;

		program_gamut_remap(mpc30, mpcc_id, arr_reg_val, gamut_mode);
	पूर्ण
पूर्ण

bool mpc3_program_3dlut(
		काष्ठा mpc *mpc,
		स्थिर काष्ठा tetrahedral_params *params,
		पूर्णांक rmu_idx)
अणु
	क्रमागत dc_lut_mode mode;
	bool is_17x17x17;
	bool is_12bits_color_channel;
	स्थिर काष्ठा dc_rgb *lut0;
	स्थिर काष्ठा dc_rgb *lut1;
	स्थिर काष्ठा dc_rgb *lut2;
	स्थिर काष्ठा dc_rgb *lut3;
	पूर्णांक lut_size0;
	पूर्णांक lut_size;

	अगर (params == शून्य) अणु
		mpc3_set_3dlut_mode(mpc, LUT_BYPASS, false, false, rmu_idx);
		वापस false;
	पूर्ण
	mpc3_घातer_on_shaper_3dlut(mpc, rmu_idx, true);

	mode = get3dlut_config(mpc, &is_17x17x17, &is_12bits_color_channel, rmu_idx);

	अगर (mode == LUT_BYPASS || mode == LUT_RAM_B)
		mode = LUT_RAM_A;
	अन्यथा
		mode = LUT_RAM_B;

	is_17x17x17 = !params->use_tetrahedral_9;
	is_12bits_color_channel = params->use_12bits;
	अगर (is_17x17x17) अणु
		lut0 = params->tetrahedral_17.lut0;
		lut1 = params->tetrahedral_17.lut1;
		lut2 = params->tetrahedral_17.lut2;
		lut3 = params->tetrahedral_17.lut3;
		lut_size0 = माप(params->tetrahedral_17.lut0)/
					माप(params->tetrahedral_17.lut0[0]);
		lut_size  = माप(params->tetrahedral_17.lut1)/
					माप(params->tetrahedral_17.lut1[0]);
	पूर्ण अन्यथा अणु
		lut0 = params->tetrahedral_9.lut0;
		lut1 = params->tetrahedral_9.lut1;
		lut2 = params->tetrahedral_9.lut2;
		lut3 = params->tetrahedral_9.lut3;
		lut_size0 = माप(params->tetrahedral_9.lut0)/
				माप(params->tetrahedral_9.lut0[0]);
		lut_size  = माप(params->tetrahedral_9.lut1)/
				माप(params->tetrahedral_9.lut1[0]);
		पूर्ण

	mpc3_select_3dlut_ram(mpc, mode,
				is_12bits_color_channel, rmu_idx);
	mpc3_select_3dlut_ram_mask(mpc, 0x1, rmu_idx);
	अगर (is_12bits_color_channel)
		mpc3_set3dlut_ram12(mpc, lut0, lut_size0, rmu_idx);
	अन्यथा
		mpc3_set3dlut_ram10(mpc, lut0, lut_size0, rmu_idx);

	mpc3_select_3dlut_ram_mask(mpc, 0x2, rmu_idx);
	अगर (is_12bits_color_channel)
		mpc3_set3dlut_ram12(mpc, lut1, lut_size, rmu_idx);
	अन्यथा
		mpc3_set3dlut_ram10(mpc, lut1, lut_size, rmu_idx);

	mpc3_select_3dlut_ram_mask(mpc, 0x4, rmu_idx);
	अगर (is_12bits_color_channel)
		mpc3_set3dlut_ram12(mpc, lut2, lut_size, rmu_idx);
	अन्यथा
		mpc3_set3dlut_ram10(mpc, lut2, lut_size, rmu_idx);

	mpc3_select_3dlut_ram_mask(mpc, 0x8, rmu_idx);
	अगर (is_12bits_color_channel)
		mpc3_set3dlut_ram12(mpc, lut3, lut_size, rmu_idx);
	अन्यथा
		mpc3_set3dlut_ram10(mpc, lut3, lut_size, rmu_idx);

	mpc3_set_3dlut_mode(mpc, mode, is_12bits_color_channel,
					is_17x17x17, rmu_idx);

	अगर (mpc->ctx->dc->debug.enable_mem_low_घातer.bits.mpc)
		mpc3_घातer_on_shaper_3dlut(mpc, rmu_idx, false);

	वापस true;
पूर्ण

व्योम mpc3_set_output_csc(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		स्थिर uपूर्णांक16_t *regval,
		क्रमागत mpc_output_csc_mode ocsc_mode)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	काष्ठा color_matrices_reg ocsc_regs;

	REG_WRITE(MPC_OUT_CSC_COEF_FORMAT, 0);

	REG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);

	अगर (ocsc_mode == MPC_OUTPUT_CSC_DISABLE)
		वापस;

	अगर (regval == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	ocsc_regs.shअगरts.csc_c11 = mpc30->mpc_shअगरt->MPC_OCSC_C11_A;
	ocsc_regs.masks.csc_c11  = mpc30->mpc_mask->MPC_OCSC_C11_A;
	ocsc_regs.shअगरts.csc_c12 = mpc30->mpc_shअगरt->MPC_OCSC_C12_A;
	ocsc_regs.masks.csc_c12 = mpc30->mpc_mask->MPC_OCSC_C12_A;

	अगर (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_A[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_A[opp_id]);
	पूर्ण अन्यथा अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_B[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_B[opp_id]);
	पूर्ण
	cm_helper_program_color_matrices(
			mpc30->base.ctx,
			regval,
			&ocsc_regs);
पूर्ण

व्योम mpc3_set_ocsc_शेष(
		काष्ठा mpc *mpc,
		पूर्णांक opp_id,
		क्रमागत dc_color_space color_space,
		क्रमागत mpc_output_csc_mode ocsc_mode)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	uपूर्णांक32_t arr_size;
	काष्ठा color_matrices_reg ocsc_regs;
	स्थिर uपूर्णांक16_t *regval = शून्य;

	REG_WRITE(MPC_OUT_CSC_COEF_FORMAT, 0);

	REG_SET(CSC_MODE[opp_id], 0, MPC_OCSC_MODE, ocsc_mode);
	अगर (ocsc_mode == MPC_OUTPUT_CSC_DISABLE)
		वापस;

	regval = find_color_matrix(color_space, &arr_size);

	अगर (regval == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	ocsc_regs.shअगरts.csc_c11 = mpc30->mpc_shअगरt->MPC_OCSC_C11_A;
	ocsc_regs.masks.csc_c11  = mpc30->mpc_mask->MPC_OCSC_C11_A;
	ocsc_regs.shअगरts.csc_c12 = mpc30->mpc_shअगरt->MPC_OCSC_C12_A;
	ocsc_regs.masks.csc_c12 = mpc30->mpc_mask->MPC_OCSC_C12_A;


	अगर (ocsc_mode == MPC_OUTPUT_CSC_COEF_A) अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_A[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_A[opp_id]);
	पूर्ण अन्यथा अणु
		ocsc_regs.csc_c11_c12 = REG(CSC_C11_C12_B[opp_id]);
		ocsc_regs.csc_c33_c34 = REG(CSC_C33_C34_B[opp_id]);
	पूर्ण

	cm_helper_program_color_matrices(
			mpc30->base.ctx,
			regval,
			&ocsc_regs);
पूर्ण

व्योम mpc3_set_rmu_mux(
	काष्ठा mpc *mpc,
	पूर्णांक rmu_idx,
	पूर्णांक value)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	अगर (rmu_idx == 0)
		REG_UPDATE(MPC_RMU_CONTROL, MPC_RMU0_MUX, value);
	अन्यथा अगर (rmu_idx == 1)
		REG_UPDATE(MPC_RMU_CONTROL, MPC_RMU1_MUX, value);

पूर्ण

uपूर्णांक32_t mpc3_get_rmu_mux_status(
	काष्ठा mpc *mpc,
	पूर्णांक rmu_idx)
अणु
	uपूर्णांक32_t status = 0xf;
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);

	अगर (rmu_idx == 0)
		REG_GET(MPC_RMU_CONTROL, MPC_RMU0_MUX_STATUS, &status);
	अन्यथा अगर (rmu_idx == 1)
		REG_GET(MPC_RMU_CONTROL, MPC_RMU1_MUX_STATUS, &status);

	वापस status;
पूर्ण

uपूर्णांक32_t mpcc3_acquire_rmu(काष्ठा mpc *mpc, पूर्णांक mpcc_id, पूर्णांक rmu_idx)
अणु
	uपूर्णांक32_t rmu_status;

	//determine अगर this mpcc is alपढ़ोy multiplexed to an RMU unit
	rmu_status = mpc3_get_rmu_mux_status(mpc, rmu_idx);
	अगर (rmu_status == mpcc_id)
		//वापस rmu_idx of pre_acquired rmu unit
		वापस rmu_idx;

	अगर (rmu_status == 0xf) अणु//rmu unit is disabled
		mpc3_set_rmu_mux(mpc, rmu_idx, mpcc_id);
		वापस rmu_idx;
	पूर्ण

	//no vacant RMU units or invalid parameters acquire_post_bldn_3dlut
	वापस -1;
पूर्ण

पूर्णांक mpcc3_release_rmu(काष्ठा mpc *mpc, पूर्णांक mpcc_id)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	पूर्णांक rmu_idx;
	uपूर्णांक32_t rmu_status;
	पूर्णांक released_rmu = -1;

	क्रम (rmu_idx = 0; rmu_idx < mpc30->num_rmu; rmu_idx++) अणु
		rmu_status = mpc3_get_rmu_mux_status(mpc, rmu_idx);
		अगर (rmu_status == mpcc_id) अणु
			mpc3_set_rmu_mux(mpc, rmu_idx, 0xf);
			released_rmu = rmu_idx;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस released_rmu;

पूर्ण

अटल व्योम mpc3_mpc_init(काष्ठा mpc *mpc)
अणु
	काष्ठा dcn30_mpc *mpc30 = TO_DCN30_MPC(mpc);
	पूर्णांक mpcc_id;

	mpc1_mpc_init(mpc);

	अगर (mpc->ctx->dc->debug.enable_mem_low_घातer.bits.mpc) अणु
		अगर (mpc30->mpc_mask->MPC_RMU0_MEM_LOW_PWR_MODE && mpc30->mpc_mask->MPC_RMU1_MEM_LOW_PWR_MODE) अणु
			REG_UPDATE(MPC_RMU_MEM_PWR_CTRL, MPC_RMU0_MEM_LOW_PWR_MODE, 3);
			REG_UPDATE(MPC_RMU_MEM_PWR_CTRL, MPC_RMU1_MEM_LOW_PWR_MODE, 3);
		पूर्ण

		अगर (mpc30->mpc_mask->MPCC_OGAM_MEM_LOW_PWR_MODE) अणु
			क्रम (mpcc_id = 0; mpcc_id < mpc30->num_mpcc; mpcc_id++)
				REG_UPDATE(MPCC_MEM_PWR_CTRL[mpcc_id], MPCC_OGAM_MEM_LOW_PWR_MODE, 3);
		पूर्ण
	पूर्ण
पूर्ण

स्थिर काष्ठा mpc_funcs dcn30_mpc_funcs = अणु
	.पढ़ो_mpcc_state = mpc1_पढ़ो_mpcc_state,
	.insert_plane = mpc1_insert_plane,
	.हटाओ_mpcc = mpc1_हटाओ_mpcc,
	.mpc_init = mpc3_mpc_init,
	.mpc_init_single_inst = mpc1_mpc_init_single_inst,
	.update_blending = mpc2_update_blending,
	.cursor_lock = mpc1_cursor_lock,
	.get_mpcc_क्रम_dpp = mpc1_get_mpcc_क्रम_dpp,
	.रुको_क्रम_idle = mpc2_निश्चित_idle_mpcc,
	.निश्चित_mpcc_idle_beक्रमe_connect = mpc2_निश्चित_mpcc_idle_beक्रमe_connect,
	.init_mpcc_list_from_hw = mpc1_init_mpcc_list_from_hw,
	.set_denorm =  mpc3_set_denorm,
	.set_denorm_clamp = mpc3_set_denorm_clamp,
	.set_output_csc = mpc3_set_output_csc,
	.set_ocsc_शेष = mpc3_set_ocsc_शेष,
	.set_output_gamma = mpc3_set_output_gamma,
	.insert_plane_to_secondary = शून्य,
	.हटाओ_mpcc_from_secondary =  शून्य,
	.set_dwb_mux = mpc3_set_dwb_mux,
	.disable_dwb_mux = mpc3_disable_dwb_mux,
	.is_dwb_idle = mpc3_is_dwb_idle,
	.set_out_rate_control = mpc3_set_out_rate_control,
	.set_gamut_remap = mpc3_set_gamut_remap,
	.program_shaper = mpc3_program_shaper,
	.acquire_rmu = mpcc3_acquire_rmu,
	.program_3dlut = mpc3_program_3dlut,
	.release_rmu = mpcc3_release_rmu,
	.घातer_on_mpc_mem_pwr = mpc3_घातer_on_ogam_lut,
	.get_mpc_out_mux = mpc1_get_mpc_out_mux,

पूर्ण;

व्योम dcn30_mpc_स्थिरruct(काष्ठा dcn30_mpc *mpc30,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn30_mpc_रेजिस्टरs *mpc_regs,
	स्थिर काष्ठा dcn30_mpc_shअगरt *mpc_shअगरt,
	स्थिर काष्ठा dcn30_mpc_mask *mpc_mask,
	पूर्णांक num_mpcc,
	पूर्णांक num_rmu)
अणु
	पूर्णांक i;

	mpc30->base.ctx = ctx;

	mpc30->base.funcs = &dcn30_mpc_funcs;

	mpc30->mpc_regs = mpc_regs;
	mpc30->mpc_shअगरt = mpc_shअगरt;
	mpc30->mpc_mask = mpc_mask;

	mpc30->mpcc_in_use_mask = 0;
	mpc30->num_mpcc = num_mpcc;
	mpc30->num_rmu = num_rmu;

	क्रम (i = 0; i < MAX_MPCC; i++)
		mpc3_init_mpcc(&mpc30->base.mpcc_array[i], i);
पूर्ण

