<शैली गुरु>
/* Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_MPCC_DCN20_H__
#घोषणा __DC_MPCC_DCN20_H__

#समावेश "dcn10/dcn10_mpc.h"

#घोषणा TO_DCN20_MPC(mpc_base) \
	container_of(mpc_base, काष्ठा dcn20_mpc, base)

#घोषणा MPC_REG_LIST_DCN2_0(inst)\
	MPC_COMMON_REG_LIST_DCN1_0(inst),\
	SRII(MPCC_TOP_GAIN, MPCC, inst),\
	SRII(MPCC_BOT_GAIN_INSIDE, MPCC, inst),\
	SRII(MPCC_BOT_GAIN_OUTSIDE, MPCC, inst),\
	SRII(MPCC_OGAM_RAMA_START_CNTL_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_START_CNTL_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_START_CNTL_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_SLOPE_CNTL_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_SLOPE_CNTL_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_SLOPE_CNTL_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_END_CNTL1_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_END_CNTL2_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_END_CNTL1_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_END_CNTL2_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_END_CNTL1_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_END_CNTL2_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_REGION_0_1, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMA_REGION_32_33, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_START_CNTL_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_START_CNTL_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_START_CNTL_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_SLOPE_CNTL_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_SLOPE_CNTL_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_SLOPE_CNTL_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_END_CNTL1_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_END_CNTL2_B, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_END_CNTL1_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_END_CNTL2_G, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_END_CNTL1_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_END_CNTL2_R, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_REGION_0_1, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_RAMB_REGION_32_33, MPCC_OGAM, inst),\
	SRII(MPCC_MEM_PWR_CTRL, MPCC, inst),\
	SRII(MPCC_OGAM_LUT_INDEX, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_LUT_RAM_CONTROL, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_LUT_DATA, MPCC_OGAM, inst),\
	SRII(MPCC_OGAM_MODE, MPCC_OGAM, inst)

#घोषणा MPC_OUT_MUX_REG_LIST_DCN2_0(inst) \
	MPC_OUT_MUX_COMMON_REG_LIST_DCN1_0(inst),\
	SRII(CSC_MODE, MPC_OUT, inst),\
	SRII(CSC_C11_C12_A, MPC_OUT, inst),\
	SRII(CSC_C33_C34_A, MPC_OUT, inst),\
	SRII(CSC_C11_C12_B, MPC_OUT, inst),\
	SRII(CSC_C33_C34_B, MPC_OUT, inst),\
	SRII(DENORM_CONTROL, MPC_OUT, inst),\
	SRII(DENORM_CLAMP_G_Y, MPC_OUT, inst),\
	SRII(DENORM_CLAMP_B_CB, MPC_OUT, inst)

#घोषणा MPC_DBG_REG_LIST_DCN2_0() \
	SR(MPC_OCSC_TEST_DEBUG_DATA),\
	SR(MPC_OCSC_TEST_DEBUG_INDEX)

#घोषणा MPC_REG_VARIABLE_LIST_DCN2_0 \
	MPC_COMMON_REG_VARIABLE_LIST \
	uपूर्णांक32_t MPCC_TOP_GAIN[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_BOT_GAIN_INSIDE[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_BOT_GAIN_OUTSIDE[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_START_CNTL_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_START_CNTL_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_START_CNTL_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_SLOPE_CNTL_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_SLOPE_CNTL_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_SLOPE_CNTL_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_END_CNTL1_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_END_CNTL2_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_END_CNTL1_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_END_CNTL2_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_END_CNTL1_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_END_CNTL2_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_REGION_0_1[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMA_REGION_32_33[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_START_CNTL_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_START_CNTL_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_START_CNTL_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_SLOPE_CNTL_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_SLOPE_CNTL_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_SLOPE_CNTL_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_END_CNTL1_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_END_CNTL2_B[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_END_CNTL1_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_END_CNTL2_G[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_END_CNTL1_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_END_CNTL2_R[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_REGION_0_1[MAX_MPCC]; \
	uपूर्णांक32_t MPCC_OGAM_RAMB_REGION_32_33[MAX_MPCC];\
	uपूर्णांक32_t MPCC_MEM_PWR_CTRL[MAX_MPCC];\
	uपूर्णांक32_t MPCC_OGAM_LUT_INDEX[MAX_MPCC];\
	uपूर्णांक32_t MPCC_OGAM_LUT_RAM_CONTROL[MAX_MPCC];\
	uपूर्णांक32_t MPCC_OGAM_LUT_DATA[MAX_MPCC];\
	uपूर्णांक32_t MPCC_OGAM_MODE[MAX_MPCC];\
	uपूर्णांक32_t MPC_OCSC_TEST_DEBUG_DATA;\
	uपूर्णांक32_t MPC_OCSC_TEST_DEBUG_INDEX;\
	uपूर्णांक32_t CSC_MODE[MAX_OPP]; \
	uपूर्णांक32_t CSC_C11_C12_A[MAX_OPP]; \
	uपूर्णांक32_t CSC_C33_C34_A[MAX_OPP]; \
	uपूर्णांक32_t CSC_C11_C12_B[MAX_OPP]; \
	uपूर्णांक32_t CSC_C33_C34_B[MAX_OPP]; \
	uपूर्णांक32_t DENORM_CONTROL[MAX_OPP]; \
	uपूर्णांक32_t DENORM_CLAMP_G_Y[MAX_OPP]; \
	uपूर्णांक32_t DENORM_CLAMP_B_CB[MAX_OPP];

#घोषणा MPC_COMMON_MASK_SH_LIST_DCN2_0(mask_sh) \
	MPC_COMMON_MASK_SH_LIST_DCN1_0(mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_BG_BPC, mask_sh),\
	SF(MPCC0_MPCC_CONTROL, MPCC_BOT_GAIN_MODE, mask_sh),\
	SF(MPCC0_MPCC_TOP_GAIN, MPCC_TOP_GAIN, mask_sh),\
	SF(MPCC0_MPCC_BOT_GAIN_INSIDE, MPCC_BOT_GAIN_INSIDE, mask_sh),\
	SF(MPCC0_MPCC_BOT_GAIN_OUTSIDE, MPCC_BOT_GAIN_OUTSIDE, mask_sh),\
	SF(MPC_OCSC_TEST_DEBUG_INDEX, MPC_OCSC_TEST_DEBUG_INDEX, mask_sh),\
	SF(MPC_OUT0_CSC_MODE, MPC_OCSC_MODE, mask_sh),\
	SF(MPC_OUT0_CSC_C11_C12_A, MPC_OCSC_C11_A, mask_sh),\
	SF(MPC_OUT0_CSC_C11_C12_A, MPC_OCSC_C12_A, mask_sh),\
	SF(MPCC0_MPCC_STATUS, MPCC_DISABLED, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_REGION_0_1, MPCC_OGAM_RAMA_EXP_REGION0_LUT_OFFSET, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_REGION_0_1, MPCC_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_REGION_0_1, MPCC_OGAM_RAMA_EXP_REGION1_LUT_OFFSET, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_REGION_0_1, MPCC_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_END_CNTL1_B, MPCC_OGAM_RAMA_EXP_REGION_END_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_END_CNTL2_B, MPCC_OGAM_RAMA_EXP_REGION_END_SLOPE_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_END_CNTL2_B, MPCC_OGAM_RAMA_EXP_REGION_END_BASE_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_SLOPE_CNTL_B, MPCC_OGAM_RAMA_EXP_REGION_LINEAR_SLOPE_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_START_CNTL_B, MPCC_OGAM_RAMA_EXP_REGION_START_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMA_START_CNTL_B, MPCC_OGAM_RAMA_EXP_REGION_START_SEGMENT_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_REGION_0_1, MPCC_OGAM_RAMB_EXP_REGION0_LUT_OFFSET, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_REGION_0_1, MPCC_OGAM_RAMB_EXP_REGION0_NUM_SEGMENTS, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_REGION_0_1, MPCC_OGAM_RAMB_EXP_REGION1_LUT_OFFSET, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_REGION_0_1, MPCC_OGAM_RAMB_EXP_REGION1_NUM_SEGMENTS, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_END_CNTL1_B, MPCC_OGAM_RAMB_EXP_REGION_END_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_END_CNTL2_B, MPCC_OGAM_RAMB_EXP_REGION_END_SLOPE_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_END_CNTL2_B, MPCC_OGAM_RAMB_EXP_REGION_END_BASE_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_SLOPE_CNTL_B, MPCC_OGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_START_CNTL_B, MPCC_OGAM_RAMB_EXP_REGION_START_B, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_RAMB_START_CNTL_B, MPCC_OGAM_RAMB_EXP_REGION_START_SEGMENT_B, mask_sh),\
	SF(MPCC0_MPCC_MEM_PWR_CTRL, MPCC_OGAM_MEM_PWR_FORCE, mask_sh),\
	SF(MPCC0_MPCC_MEM_PWR_CTRL, MPCC_OGAM_MEM_PWR_DIS, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_LUT_INDEX, MPCC_OGAM_LUT_INDEX, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_LUT_RAM_CONTROL, MPCC_OGAM_LUT_WRITE_EN_MASK, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_LUT_RAM_CONTROL, MPCC_OGAM_LUT_RAM_SEL, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_LUT_RAM_CONTROL, MPCC_OGAM_CONFIG_STATUS, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_LUT_DATA, MPCC_OGAM_LUT_DATA, mask_sh),\
	SF(MPCC_OGAM0_MPCC_OGAM_MODE, MPCC_OGAM_MODE, mask_sh),\
	SF(MPC_OUT0_DENORM_CONTROL, MPC_OUT_DENORM_MODE, mask_sh),\
	SF(MPC_OUT0_DENORM_CONTROL, MPC_OUT_DENORM_CLAMP_MAX_R_CR, mask_sh),\
	SF(MPC_OUT0_DENORM_CONTROL, MPC_OUT_DENORM_CLAMP_MIN_R_CR, mask_sh),\
	SF(MPC_OUT0_DENORM_CLAMP_G_Y, MPC_OUT_DENORM_CLAMP_MAX_G_Y, mask_sh),\
	SF(MPC_OUT0_DENORM_CLAMP_G_Y, MPC_OUT_DENORM_CLAMP_MIN_G_Y, mask_sh),\
	SF(MPC_OUT0_DENORM_CLAMP_B_CB, MPC_OUT_DENORM_CLAMP_MAX_B_CB, mask_sh),\
	SF(MPC_OUT0_DENORM_CLAMP_B_CB, MPC_OUT_DENORM_CLAMP_MIN_B_CB, mask_sh),\
	SF(CUR_VUPDATE_LOCK_SET0, CUR_VUPDATE_LOCK_SET, mask_sh)

/*
 *	DCN2 MPC_OCSC debug status रेजिस्टर:
 *
 *		Status index including current OCSC Mode is 1
 *			OCSC Mode: [1..0]
 */
#घोषणा MPC_OCSC_TEST_DEBUG_DATA_STATUS_IDX 1

#घोषणा MPC_DEBUG_REG_LIST_SH_DCN20 \
	.MPC_OCSC_TEST_DEBUG_DATA_OCSC_MODE = 0

#घोषणा MPC_DEBUG_REG_LIST_MASK_DCN20 \
	.MPC_OCSC_TEST_DEBUG_DATA_OCSC_MODE = 0x3

#घोषणा MPC_REG_FIELD_LIST_DCN2_0(type) \
	MPC_REG_FIELD_LIST(type)\
	type MPCC_BG_BPC;\
	type MPCC_BOT_GAIN_MODE;\
	type MPCC_TOP_GAIN;\
	type MPCC_BOT_GAIN_INSIDE;\
	type MPCC_BOT_GAIN_OUTSIDE;\
	type MPC_OCSC_TEST_DEBUG_DATA_OCSC_MODE;\
	type MPC_OCSC_TEST_DEBUG_INDEX;\
	type MPC_OCSC_MODE;\
	type MPC_OCSC_C11_A;\
	type MPC_OCSC_C12_A;\
	type MPCC_OGAM_RAMA_EXP_REGION0_LUT_OFFSET;\
	type MPCC_OGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;\
	type MPCC_OGAM_RAMA_EXP_REGION1_LUT_OFFSET;\
	type MPCC_OGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;\
	type MPCC_OGAM_RAMA_EXP_REGION_END_B;\
	type MPCC_OGAM_RAMA_EXP_REGION_END_SLOPE_B;\
	type MPCC_OGAM_RAMA_EXP_REGION_END_BASE_B;\
	type MPCC_OGAM_RAMA_EXP_REGION_LINEAR_SLOPE_B;\
	type MPCC_OGAM_RAMA_EXP_REGION_START_B;\
	type MPCC_OGAM_RAMA_EXP_REGION_START_SEGMENT_B;\
	type MPCC_OGAM_RAMB_EXP_REGION0_LUT_OFFSET;\
	type MPCC_OGAM_RAMB_EXP_REGION0_NUM_SEGMENTS;\
	type MPCC_OGAM_RAMB_EXP_REGION1_LUT_OFFSET;\
	type MPCC_OGAM_RAMB_EXP_REGION1_NUM_SEGMENTS;\
	type MPCC_OGAM_RAMB_EXP_REGION_END_B;\
	type MPCC_OGAM_RAMB_EXP_REGION_END_SLOPE_B;\
	type MPCC_OGAM_RAMB_EXP_REGION_END_BASE_B;\
	type MPCC_OGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B;\
	type MPCC_OGAM_RAMB_EXP_REGION_START_B;\
	type MPCC_OGAM_RAMB_EXP_REGION_START_SEGMENT_B;\
	type MPCC_OGAM_MEM_PWR_FORCE;\
	type MPCC_OGAM_LUT_INDEX;\
	type MPCC_OGAM_LUT_WRITE_EN_MASK;\
	type MPCC_OGAM_LUT_RAM_SEL;\
	type MPCC_OGAM_CONFIG_STATUS;\
	type MPCC_OGAM_LUT_DATA;\
	type MPCC_OGAM_MODE;\
	type MPC_OUT_DENORM_MODE;\
	type MPC_OUT_DENORM_CLAMP_MAX_R_CR;\
	type MPC_OUT_DENORM_CLAMP_MIN_R_CR;\
	type MPC_OUT_DENORM_CLAMP_MAX_G_Y;\
	type MPC_OUT_DENORM_CLAMP_MIN_G_Y;\
	type MPC_OUT_DENORM_CLAMP_MAX_B_CB;\
	type MPC_OUT_DENORM_CLAMP_MIN_B_CB;\
	type MPCC_DISABLED;\
	type MPCC_OGAM_MEM_PWR_DIS;

काष्ठा dcn20_mpc_रेजिस्टरs अणु
	MPC_REG_VARIABLE_LIST_DCN2_0
पूर्ण;

काष्ठा dcn20_mpc_shअगरt अणु
	MPC_REG_FIELD_LIST_DCN2_0(uपूर्णांक8_t)
पूर्ण;

काष्ठा dcn20_mpc_mask अणु
	MPC_REG_FIELD_LIST_DCN2_0(uपूर्णांक32_t)
पूर्ण;

काष्ठा dcn20_mpc अणु
	काष्ठा mpc base;

	पूर्णांक mpcc_in_use_mask;
	पूर्णांक num_mpcc;
	स्थिर काष्ठा dcn20_mpc_रेजिस्टरs *mpc_regs;
	स्थिर काष्ठा dcn20_mpc_shअगरt *mpc_shअगरt;
	स्थिर काष्ठा dcn20_mpc_mask *mpc_mask;
पूर्ण;

व्योम dcn20_mpc_स्थिरruct(काष्ठा dcn20_mpc *mpcc20,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn20_mpc_रेजिस्टरs *mpc_regs,
	स्थिर काष्ठा dcn20_mpc_shअगरt *mpc_shअगरt,
	स्थिर काष्ठा dcn20_mpc_mask *mpc_mask,
	पूर्णांक num_mpcc);

व्योम mpc2_update_blending(
	काष्ठा mpc *mpc,
	काष्ठा mpcc_blnd_cfg *blnd_cfg,
	पूर्णांक mpcc_id);

व्योम mpc2_set_denorm(
	काष्ठा mpc *mpc,
	पूर्णांक opp_id,
	क्रमागत dc_color_depth output_depth);

व्योम mpc2_set_denorm_clamp(
	काष्ठा mpc *mpc,
	पूर्णांक opp_id,
	काष्ठा mpc_denorm_clamp denorm_clamp);

व्योम mpc2_set_output_csc(
	काष्ठा mpc *mpc,
	पूर्णांक opp_id,
	स्थिर uपूर्णांक16_t *regval,
	क्रमागत mpc_output_csc_mode ocsc_mode);

व्योम mpc2_set_ocsc_शेष(
	काष्ठा mpc *mpc,
	पूर्णांक opp_id,
	क्रमागत dc_color_space color_space,
	क्रमागत mpc_output_csc_mode ocsc_mode);

व्योम mpc2_set_output_gamma(
	काष्ठा mpc *mpc,
	पूर्णांक mpcc_id,
	स्थिर काष्ठा pwl_params *params);

व्योम mpc2_निश्चित_idle_mpcc(काष्ठा mpc *mpc, पूर्णांक id);
व्योम mpc2_निश्चित_mpcc_idle_beक्रमe_connect(काष्ठा mpc *mpc, पूर्णांक mpcc_id);
व्योम mpc20_घातer_on_ogam_lut(काष्ठा mpc *mpc, पूर्णांक mpcc_id, bool घातer_on);
#पूर्ण_अगर
