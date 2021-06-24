<शैली गुरु>
/* Copyright 2012-17 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __DC_DWBC_DCN20_H__
#घोषणा __DC_DWBC_DCN20_H__

#घोषणा TO_DCN20_DWBC(dwbc_base) \
	container_of(dwbc_base, काष्ठा dcn20_dwbc, base)

/* DCN */
#घोषणा BASE_INNER(seg) \
	DCE_BASE__INST0_SEG ## seg

#घोषणा BASE(seg) \
	BASE_INNER(seg)

#घोषणा SR(reg_name)\
		.reg_name = BASE(mm ## reg_name ## _BASE_IDX) +  \
					mm ## reg_name

#घोषणा SRI(reg_name, block, id)\
	.reg_name = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा SRI2(reg_name, block, id)\
	.reg_name = BASE(mm ## reg_name ## _BASE_IDX) + \
					mm ## reg_name

#घोषणा SRII(reg_name, block, id)\
	.reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix


#घोषणा DWBC_COMMON_REG_LIST_DCN2_0(inst) \
	SRI2(WB_ENABLE, CNV, inst),\
	SRI2(WB_EC_CONFIG, CNV, inst),\
	SRI2(CNV_MODE, CNV, inst),\
	SRI2(CNV_WINDOW_START, CNV, inst),\
	SRI2(CNV_WINDOW_SIZE, CNV, inst),\
	SRI2(CNV_UPDATE, CNV, inst),\
	SRI2(CNV_SOURCE_SIZE, CNV, inst),\
	SRI2(CNV_TEST_CNTL, CNV, inst),\
	SRI2(CNV_TEST_CRC_RED, CNV, inst),\
	SRI2(CNV_TEST_CRC_GREEN, CNV, inst),\
	SRI2(CNV_TEST_CRC_BLUE, CNV, inst),\
	SRI2(WBSCL_COEF_RAM_SELECT, WBSCL, inst),\
	SRI2(WBSCL_COEF_RAM_TAP_DATA, WBSCL, inst),\
	SRI2(WBSCL_MODE, WBSCL, inst),\
	SRI2(WBSCL_TAP_CONTROL, WBSCL, inst),\
	SRI2(WBSCL_DEST_SIZE, WBSCL, inst),\
	SRI2(WBSCL_HORZ_FILTER_SCALE_RATIO, WBSCL, inst),\
	SRI2(WBSCL_HORZ_FILTER_INIT_Y_RGB, WBSCL, inst),\
	SRI2(WBSCL_HORZ_FILTER_INIT_CBCR, WBSCL, inst),\
	SRI2(WBSCL_VERT_FILTER_SCALE_RATIO, WBSCL, inst),\
	SRI2(WBSCL_VERT_FILTER_INIT_Y_RGB, WBSCL, inst),\
	SRI2(WBSCL_VERT_FILTER_INIT_CBCR, WBSCL, inst),\
	SRI2(WBSCL_ROUND_OFFSET, WBSCL, inst),\
	SRI2(WBSCL_OVERFLOW_STATUS, WBSCL, inst),\
	SRI2(WBSCL_COEF_RAM_CONFLICT_STATUS, WBSCL, inst),\
	SRI2(WBSCL_TEST_CNTL, WBSCL, inst),\
	SRI2(WBSCL_TEST_CRC_RED, WBSCL, inst),\
	SRI2(WBSCL_TEST_CRC_GREEN, WBSCL, inst),\
	SRI2(WBSCL_TEST_CRC_BLUE, WBSCL, inst),\
	SRI2(WBSCL_BACKPRESSURE_CNT_EN, WBSCL, inst),\
	SRI2(WB_MCIF_BACKPRESSURE_CNT, WBSCL, inst),\
	SRI2(WBSCL_CLAMP_Y_RGB, WBSCL, inst),\
	SRI2(WBSCL_CLAMP_CBCR, WBSCL, inst),\
	SRI2(WBSCL_OUTSIDE_PIX_STRATEGY, WBSCL, inst),\
	SRI2(WBSCL_OUTSIDE_PIX_STRATEGY_CBCR, WBSCL, inst),\
	SRI2(WBSCL_DEBUG, WBSCL, inst),\
	SRI2(WBSCL_TEST_DEBUG_INDEX, WBSCL, inst),\
	SRI2(WBSCL_TEST_DEBUG_DATA, WBSCL, inst),\
	SRI2(WB_DEBUG_CTRL, CNV, inst),\
	SRI2(WB_DBG_MODE, CNV, inst),\
	SRI2(WB_HW_DEBUG, CNV, inst),\
	SRI2(CNV_TEST_DEBUG_INDEX, CNV, inst),\
	SRI2(CNV_TEST_DEBUG_DATA, CNV, inst),\
	SRI2(WB_SOFT_RESET, CNV, inst),\
	SRI2(WB_WARM_UP_MODE_CTL1, CNV, inst),\
	SRI2(WB_WARM_UP_MODE_CTL2, CNV, inst)

#घोषणा DWBC_COMMON_MASK_SH_LIST_DCN2_0(mask_sh) \
	SF(WB_ENABLE, WB_ENABLE, mask_sh),\
	SF(WB_EC_CONFIG, DISPCLK_R_WB_GATE_DIS, mask_sh),\
	SF(WB_EC_CONFIG, DISPCLK_G_WB_GATE_DIS, mask_sh),\
	SF(WB_EC_CONFIG, DISPCLK_G_WBSCL_GATE_DIS, mask_sh),\
	SF(WB_EC_CONFIG, WB_TEST_CLK_SEL, mask_sh),\
	SF(WB_EC_CONFIG, WB_LB_LS_DIS, mask_sh),\
	SF(WB_EC_CONFIG, WB_LB_SD_DIS, mask_sh),\
	SF(WB_EC_CONFIG, WB_LUT_LS_DIS, mask_sh),\
	SF(WB_EC_CONFIG, WBSCL_LB_MEM_PWR_MODE_SEL, mask_sh),\
	SF(WB_EC_CONFIG, WBSCL_LB_MEM_PWR_DIS, mask_sh),\
	SF(WB_EC_CONFIG, WBSCL_LB_MEM_PWR_FORCE, mask_sh),\
	SF(WB_EC_CONFIG, WBSCL_LB_MEM_PWR_STATE, mask_sh),\
	SF(WB_EC_CONFIG, WB_RAM_PW_SAVE_MODE, mask_sh),\
	SF(WB_EC_CONFIG, WBSCL_LUT_MEM_PWR_STATE, mask_sh),\
	SF(CNV_MODE, CNV_OUT_BPC, mask_sh),\
	SF(CNV_MODE, CNV_FRAME_CAPTURE_RATE, mask_sh),\
	SF(CNV_MODE, CNV_WINDOW_CROP_EN, mask_sh),\
	SF(CNV_MODE, CNV_STEREO_TYPE, mask_sh),\
	SF(CNV_MODE, CNV_INTERLACED_MODE, mask_sh),\
	SF(CNV_MODE, CNV_EYE_SELECTION, mask_sh),\
	SF(CNV_MODE, CNV_STEREO_POLARITY, mask_sh),\
	SF(CNV_MODE, CNV_INTERLACED_FIELD_ORDER, mask_sh),\
	SF(CNV_MODE, CNV_STEREO_SPLIT, mask_sh),\
	SF(CNV_MODE, CNV_NEW_CONTENT, mask_sh),\
	SF(CNV_MODE, CNV_FRAME_CAPTURE_EN_CURRENT, mask_sh),\
	SF(CNV_MODE, CNV_FRAME_CAPTURE_EN, mask_sh),\
	SF(CNV_WINDOW_START, CNV_WINDOW_START_X, mask_sh),\
	SF(CNV_WINDOW_START, CNV_WINDOW_START_Y, mask_sh),\
	SF(CNV_WINDOW_SIZE, CNV_WINDOW_WIDTH, mask_sh),\
	SF(CNV_WINDOW_SIZE, CNV_WINDOW_HEIGHT, mask_sh),\
	SF(CNV_UPDATE, CNV_UPDATE_PENDING, mask_sh),\
	SF(CNV_UPDATE, CNV_UPDATE_TAKEN, mask_sh),\
	SF(CNV_UPDATE, CNV_UPDATE_LOCK, mask_sh),\
	SF(CNV_SOURCE_SIZE, CNV_SOURCE_WIDTH, mask_sh),\
	SF(CNV_SOURCE_SIZE, CNV_SOURCE_HEIGHT, mask_sh),\
	SF(CNV_TEST_CNTL, CNV_TEST_CRC_EN, mask_sh),\
	SF(CNV_TEST_CNTL, CNV_TEST_CRC_CONT_EN, mask_sh),\
	SF(CNV_TEST_CRC_RED, CNV_TEST_CRC_RED_MASK, mask_sh),\
	SF(CNV_TEST_CRC_RED, CNV_TEST_CRC_SIG_RED, mask_sh),\
	SF(CNV_TEST_CRC_GREEN, CNV_TEST_CRC_GREEN_MASK, mask_sh),\
	SF(CNV_TEST_CRC_GREEN, CNV_TEST_CRC_SIG_GREEN, mask_sh),\
	SF(CNV_TEST_CRC_BLUE, CNV_TEST_CRC_BLUE_MASK, mask_sh),\
	SF(CNV_TEST_CRC_BLUE, CNV_TEST_CRC_SIG_BLUE, mask_sh),\
	SF(WB_DEBUG_CTRL, WB_DEBUG_EN, mask_sh),\
	SF(WB_DEBUG_CTRL, WB_DEBUG_SEL, mask_sh),\
	SF(WB_DBG_MODE, WB_DBG_MODE_EN, mask_sh),\
	SF(WB_DBG_MODE, WB_DBG_DIN_FMT, mask_sh),\
	SF(WB_DBG_MODE, WB_DBG_36MODE, mask_sh),\
	SF(WB_DBG_MODE, WB_DBG_CMAP, mask_sh),\
	SF(WB_DBG_MODE, WB_DBG_PXLRATE_ERROR, mask_sh),\
	SF(WB_DBG_MODE, WB_DBG_SOURCE_WIDTH, mask_sh),\
	SF(WB_HW_DEBUG, WB_HW_DEBUG, mask_sh),\
	SF(WB_SOFT_RESET, WB_SOFT_RESET, mask_sh),\
	SF(CNV_TEST_DEBUG_INDEX, CNV_TEST_DEBUG_INDEX, mask_sh),\
	SF(CNV_TEST_DEBUG_INDEX, CNV_TEST_DEBUG_WRITE_EN, mask_sh),\
	SF(CNV_TEST_DEBUG_DATA, CNV_TEST_DEBUG_DATA, mask_sh),\
	SF(WBSCL_COEF_RAM_SELECT, WBSCL_COEF_RAM_TAP_PAIR_IDX, mask_sh),\
	SF(WBSCL_COEF_RAM_SELECT, WBSCL_COEF_RAM_PHASE, mask_sh),\
	SF(WBSCL_COEF_RAM_SELECT, WBSCL_COEF_RAM_FILTER_TYPE, mask_sh),\
	SF(WBSCL_COEF_RAM_TAP_DATA, WBSCL_COEF_RAM_EVEN_TAP_COEF, mask_sh),\
	SF(WBSCL_COEF_RAM_TAP_DATA, WBSCL_COEF_RAM_EVEN_TAP_COEF_EN, mask_sh),\
	SF(WBSCL_COEF_RAM_TAP_DATA, WBSCL_COEF_RAM_ODD_TAP_COEF, mask_sh),\
	SF(WBSCL_COEF_RAM_TAP_DATA, WBSCL_COEF_RAM_ODD_TAP_COEF_EN, mask_sh),\
	SF(WBSCL_MODE, WBSCL_MODE, mask_sh),\
	SF(WBSCL_MODE, WBSCL_OUT_BIT_DEPTH, mask_sh),\
	SF(WBSCL_TAP_CONTROL, WBSCL_V_NUM_OF_TAPS_Y_RGB, mask_sh),\
	SF(WBSCL_TAP_CONTROL, WBSCL_V_NUM_OF_TAPS_CBCR, mask_sh),\
	SF(WBSCL_TAP_CONTROL, WBSCL_H_NUM_OF_TAPS_Y_RGB, mask_sh),\
	SF(WBSCL_TAP_CONTROL, WBSCL_H_NUM_OF_TAPS_CBCR, mask_sh),\
	SF(WBSCL_DEST_SIZE, WBSCL_DEST_HEIGHT, mask_sh),\
	SF(WBSCL_DEST_SIZE, WBSCL_DEST_WIDTH, mask_sh),\
	SF(WBSCL_HORZ_FILTER_SCALE_RATIO, WBSCL_H_SCALE_RATIO, mask_sh),\
	SF(WBSCL_HORZ_FILTER_INIT_Y_RGB, WBSCL_H_INIT_FRAC_Y_RGB, mask_sh),\
	SF(WBSCL_HORZ_FILTER_INIT_Y_RGB, WBSCL_H_INIT_INT_Y_RGB, mask_sh),\
	SF(WBSCL_HORZ_FILTER_INIT_CBCR, WBSCL_H_INIT_FRAC_CBCR, mask_sh),\
	SF(WBSCL_HORZ_FILTER_INIT_CBCR, WBSCL_H_INIT_INT_CBCR, mask_sh),\
	SF(WBSCL_VERT_FILTER_SCALE_RATIO, WBSCL_V_SCALE_RATIO, mask_sh),\
	SF(WBSCL_VERT_FILTER_INIT_Y_RGB, WBSCL_V_INIT_FRAC_Y_RGB, mask_sh),\
	SF(WBSCL_VERT_FILTER_INIT_Y_RGB, WBSCL_V_INIT_INT_Y_RGB, mask_sh),\
	SF(WBSCL_VERT_FILTER_INIT_CBCR, WBSCL_V_INIT_FRAC_CBCR, mask_sh),\
	SF(WBSCL_VERT_FILTER_INIT_CBCR, WBSCL_V_INIT_INT_CBCR, mask_sh),\
	SF(WBSCL_ROUND_OFFSET, WBSCL_ROUND_OFFSET_Y_RGB, mask_sh),\
	SF(WBSCL_ROUND_OFFSET, WBSCL_ROUND_OFFSET_CBCR, mask_sh),\
	SF(WBSCL_OVERFLOW_STATUS, WBSCL_DATA_OVERFLOW_FLAG, mask_sh),\
	SF(WBSCL_OVERFLOW_STATUS, WBSCL_DATA_OVERFLOW_ACK, mask_sh),\
	SF(WBSCL_OVERFLOW_STATUS, WBSCL_DATA_OVERFLOW_MASK, mask_sh),\
	SF(WBSCL_OVERFLOW_STATUS, WBSCL_DATA_OVERFLOW_INT_STATUS, mask_sh),\
	SF(WBSCL_OVERFLOW_STATUS, WBSCL_DATA_OVERFLOW_INT_TYPE, mask_sh),\
	SF(WBSCL_COEF_RAM_CONFLICT_STATUS, WBSCL_HOST_CONFLICT_FLAG, mask_sh),\
	SF(WBSCL_COEF_RAM_CONFLICT_STATUS, WBSCL_HOST_CONFLICT_ACK, mask_sh),\
	SF(WBSCL_COEF_RAM_CONFLICT_STATUS, WBSCL_HOST_CONFLICT_MASK, mask_sh),\
	SF(WBSCL_COEF_RAM_CONFLICT_STATUS, WBSCL_HOST_CONFLICT_INT_STATUS, mask_sh),\
	SF(WBSCL_COEF_RAM_CONFLICT_STATUS, WBSCL_HOST_CONFLICT_INT_TYPE, mask_sh),\
	SF(WBSCL_TEST_CNTL, WBSCL_TEST_CRC_EN, mask_sh),\
	SF(WBSCL_TEST_CNTL, WBSCL_TEST_CRC_CONT_EN, mask_sh),\
	SF(WBSCL_TEST_CRC_RED, WBSCL_TEST_CRC_RED_MASK, mask_sh),\
	SF(WBSCL_TEST_CRC_RED, WBSCL_TEST_CRC_SIG_RED, mask_sh),\
	SF(WBSCL_TEST_CRC_GREEN, WBSCL_TEST_CRC_GREEN_MASK, mask_sh),\
	SF(WBSCL_TEST_CRC_GREEN, WBSCL_TEST_CRC_SIG_GREEN, mask_sh),\
	SF(WBSCL_TEST_CRC_BLUE, WBSCL_TEST_CRC_BLUE_MASK, mask_sh),\
	SF(WBSCL_TEST_CRC_BLUE, WBSCL_TEST_CRC_SIG_BLUE, mask_sh),\
	SF(WBSCL_BACKPRESSURE_CNT_EN, WBSCL_BACKPRESSURE_CNT_EN, mask_sh),\
	SF(WB_MCIF_BACKPRESSURE_CNT, WB_MCIF_Y_MAX_BACKPRESSURE, mask_sh),\
	SF(WB_MCIF_BACKPRESSURE_CNT, WB_MCIF_C_MAX_BACKPRESSURE, mask_sh),\
	SF(WBSCL_CLAMP_Y_RGB, WBSCL_CLAMP_UPPER_Y_RGB, mask_sh),\
	SF(WBSCL_CLAMP_Y_RGB, WBSCL_CLAMP_LOWER_Y_RGB, mask_sh),\
	SF(WBSCL_CLAMP_CBCR, WBSCL_CLAMP_UPPER_CBCR, mask_sh),\
	SF(WBSCL_CLAMP_CBCR, WBSCL_CLAMP_LOWER_CBCR, mask_sh),\
	SF(WBSCL_OUTSIDE_PIX_STRATEGY, WBSCL_OUTSIDE_PIX_STRATEGY, mask_sh),\
	SF(WBSCL_OUTSIDE_PIX_STRATEGY, WBSCL_BLACK_COLOR_G_Y, mask_sh),\
	SF(WBSCL_OUTSIDE_PIX_STRATEGY_CBCR, WBSCL_BLACK_COLOR_B_CB, mask_sh),\
	SF(WBSCL_OUTSIDE_PIX_STRATEGY_CBCR, WBSCL_BLACK_COLOR_R_CR, mask_sh),\
	SF(WBSCL_DEBUG, WBSCL_DEBUG, mask_sh),\
	SF(WBSCL_TEST_DEBUG_INDEX, WBSCL_TEST_DEBUG_INDEX, mask_sh),\
	SF(WBSCL_TEST_DEBUG_INDEX, WBSCL_TEST_DEBUG_WRITE_EN, mask_sh),\
	SF(WBSCL_TEST_DEBUG_DATA, WBSCL_TEST_DEBUG_DATA, mask_sh),\
	SF(WB_WARM_UP_MODE_CTL1, WIDTH_WARMUP, mask_sh),\
	SF(WB_WARM_UP_MODE_CTL1, HEIGHT_WARMUP, mask_sh),\
	SF(WB_WARM_UP_MODE_CTL1, GMC_WARM_UP_ENABLE, mask_sh),\
	SF(WB_WARM_UP_MODE_CTL2, DATA_VALUE_WARMUP, mask_sh),\
	SF(WB_WARM_UP_MODE_CTL2, MODE_WARMUP, mask_sh),\
	SF(WB_WARM_UP_MODE_CTL2, DATA_DEPTH_WARMUP, mask_sh)

#घोषणा DWBC_REG_FIELD_LIST_DCN2_0(type) \
	type WB_ENABLE;\
	type DISPCLK_R_WB_GATE_DIS;\
	type DISPCLK_G_WB_GATE_DIS;\
	type DISPCLK_G_WBSCL_GATE_DIS;\
	type WB_TEST_CLK_SEL;\
	type WB_LB_LS_DIS;\
	type WB_LB_SD_DIS;\
	type WB_LUT_LS_DIS;\
	type WBSCL_LB_MEM_PWR_MODE_SEL;\
	type WBSCL_LB_MEM_PWR_DIS;\
	type WBSCL_LB_MEM_PWR_FORCE;\
	type WBSCL_LB_MEM_PWR_STATE;\
	type WB_RAM_PW_SAVE_MODE;\
	type WBSCL_LUT_MEM_PWR_STATE;\
	type CNV_OUT_BPC;\
	type CNV_FRAME_CAPTURE_RATE;\
	type CNV_WINDOW_CROP_EN;\
	type CNV_STEREO_TYPE;\
	type CNV_INTERLACED_MODE;\
	type CNV_EYE_SELECTION;\
	type CNV_STEREO_POLARITY;\
	type CNV_INTERLACED_FIELD_ORDER;\
	type CNV_STEREO_SPLIT;\
	type CNV_NEW_CONTENT;\
	type CNV_FRAME_CAPTURE_EN_CURRENT;\
	type CNV_FRAME_CAPTURE_EN;\
	type CNV_WINDOW_START_X;\
	type CNV_WINDOW_START_Y;\
	type CNV_WINDOW_WIDTH;\
	type CNV_WINDOW_HEIGHT;\
	type CNV_UPDATE_PENDING;\
	type CNV_UPDATE_TAKEN;\
	type CNV_UPDATE_LOCK;\
	type CNV_SOURCE_WIDTH;\
	type CNV_SOURCE_HEIGHT;\
	type CNV_TEST_CRC_EN;\
	type CNV_TEST_CRC_CONT_EN;\
	type CNV_TEST_CRC_RED_MASK;\
	type CNV_TEST_CRC_SIG_RED;\
	type CNV_TEST_CRC_GREEN_MASK;\
	type CNV_TEST_CRC_SIG_GREEN;\
	type CNV_TEST_CRC_BLUE_MASK;\
	type CNV_TEST_CRC_SIG_BLUE;\
	type WB_DEBUG_EN;\
	type WB_DEBUG_SEL;\
	type WB_DBG_MODE_EN;\
	type WB_DBG_DIN_FMT;\
	type WB_DBG_36MODE;\
	type WB_DBG_CMAP;\
	type WB_DBG_PXLRATE_ERROR;\
	type WB_DBG_SOURCE_WIDTH;\
	type WB_HW_DEBUG;\
	type CNV_TEST_DEBUG_INDEX;\
	type CNV_TEST_DEBUG_WRITE_EN;\
	type CNV_TEST_DEBUG_DATA;\
	type WB_SOFT_RESET;\
	type WBSCL_COEF_RAM_TAP_PAIR_IDX;\
	type WBSCL_COEF_RAM_PHASE;\
	type WBSCL_COEF_RAM_FILTER_TYPE;\
	type WBSCL_COEF_RAM_SEL;\
	type WBSCL_COEF_RAM_SEL_CURRENT;\
	type WBSCL_COEF_RAM_RD_SEL;\
	type WBSCL_COEF_RAM_EVEN_TAP_COEF;\
	type WBSCL_COEF_RAM_EVEN_TAP_COEF_EN;\
	type WBSCL_COEF_RAM_ODD_TAP_COEF;\
	type WBSCL_COEF_RAM_ODD_TAP_COEF_EN;\
	type WBSCL_MODE;\
	type WBSCL_OUT_BIT_DEPTH;\
	type WBSCL_V_NUM_OF_TAPS_Y_RGB;\
	type WBSCL_V_NUM_OF_TAPS_CBCR;\
	type WBSCL_H_NUM_OF_TAPS_Y_RGB;\
	type WBSCL_H_NUM_OF_TAPS_CBCR;\
	type WBSCL_DEST_HEIGHT;\
	type WBSCL_DEST_WIDTH;\
	type WBSCL_H_SCALE_RATIO;\
	type WBSCL_H_INIT_FRAC_Y_RGB;\
	type WBSCL_H_INIT_INT_Y_RGB;\
	type WBSCL_H_INIT_FRAC_CBCR;\
	type WBSCL_H_INIT_INT_CBCR;\
	type WBSCL_V_SCALE_RATIO;\
	type WBSCL_V_INIT_FRAC_Y_RGB;\
	type WBSCL_V_INIT_INT_Y_RGB;\
	type WBSCL_V_INIT_FRAC_CBCR;\
	type WBSCL_V_INIT_INT_CBCR;\
	type WBSCL_ROUND_OFFSET_Y_RGB;\
	type WBSCL_ROUND_OFFSET_CBCR;\
	type WBSCL_DATA_OVERFLOW_FLAG;\
	type WBSCL_DATA_OVERFLOW_ACK;\
	type WBSCL_DATA_OVERFLOW_MASK;\
	type WBSCL_DATA_OVERFLOW_INT_STATUS;\
	type WBSCL_DATA_OVERFLOW_INT_TYPE;\
	type WBSCL_HOST_CONFLICT_FLAG;\
	type WBSCL_HOST_CONFLICT_ACK;\
	type WBSCL_HOST_CONFLICT_MASK;\
	type WBSCL_HOST_CONFLICT_INT_STATUS;\
	type WBSCL_HOST_CONFLICT_INT_TYPE;\
	type WBSCL_TEST_CRC_EN;\
	type WBSCL_TEST_CRC_CONT_EN;\
	type WBSCL_TEST_CRC_RED_MASK;\
	type WBSCL_TEST_CRC_SIG_RED;\
	type WBSCL_TEST_CRC_GREEN_MASK;\
	type WBSCL_TEST_CRC_SIG_GREEN;\
	type WBSCL_TEST_CRC_BLUE_MASK;\
	type WBSCL_TEST_CRC_SIG_BLUE;\
	type WBSCL_BACKPRESSURE_CNT_EN;\
	type WB_MCIF_Y_MAX_BACKPRESSURE;\
	type WB_MCIF_C_MAX_BACKPRESSURE;\
	type WBSCL_CLAMP_UPPER_Y_RGB;\
	type WBSCL_CLAMP_LOWER_Y_RGB;\
	type WBSCL_CLAMP_UPPER_CBCR;\
	type WBSCL_CLAMP_LOWER_CBCR;\
	type WBSCL_OUTSIDE_PIX_STRATEGY;\
	type WBSCL_BLACK_COLOR_G_Y;\
	type WBSCL_BLACK_COLOR_B_CB;\
	type WBSCL_BLACK_COLOR_R_CR;\
	type WBSCL_DEBUG;\
	type WBSCL_TEST_DEBUG_INDEX;\
	type WBSCL_TEST_DEBUG_WRITE_EN;\
	type WBSCL_TEST_DEBUG_DATA;\
	type WIDTH_WARMUP;\
	type HEIGHT_WARMUP;\
	type GMC_WARM_UP_ENABLE;\
	type DATA_VALUE_WARMUP;\
	type MODE_WARMUP;\
	type DATA_DEPTH_WARMUP; \

काष्ठा dcn20_dwbc_रेजिस्टरs अणु
	/* DCN2.0 */
	uपूर्णांक32_t WB_ENABLE;
	uपूर्णांक32_t WB_EC_CONFIG;
	uपूर्णांक32_t CNV_MODE;
	uपूर्णांक32_t CNV_WINDOW_START;
	uपूर्णांक32_t CNV_WINDOW_SIZE;
	uपूर्णांक32_t CNV_UPDATE;
	uपूर्णांक32_t CNV_SOURCE_SIZE;
	uपूर्णांक32_t CNV_TEST_CNTL;
	uपूर्णांक32_t CNV_TEST_CRC_RED;
	uपूर्णांक32_t CNV_TEST_CRC_GREEN;
	uपूर्णांक32_t CNV_TEST_CRC_BLUE;
	uपूर्णांक32_t WB_DEBUG_CTRL;
	uपूर्णांक32_t WB_DBG_MODE;
	uपूर्णांक32_t WB_HW_DEBUG;
	uपूर्णांक32_t CNV_TEST_DEBUG_INDEX;
	uपूर्णांक32_t CNV_TEST_DEBUG_DATA;
	uपूर्णांक32_t WB_SOFT_RESET;
	uपूर्णांक32_t WBSCL_COEF_RAM_SELECT;
	uपूर्णांक32_t WBSCL_COEF_RAM_TAP_DATA;
	uपूर्णांक32_t WBSCL_MODE;
	uपूर्णांक32_t WBSCL_TAP_CONTROL;
	uपूर्णांक32_t WBSCL_DEST_SIZE;
	uपूर्णांक32_t WBSCL_HORZ_FILTER_SCALE_RATIO;
	uपूर्णांक32_t WBSCL_HORZ_FILTER_INIT_Y_RGB;
	uपूर्णांक32_t WBSCL_HORZ_FILTER_INIT_CBCR;
	uपूर्णांक32_t WBSCL_VERT_FILTER_SCALE_RATIO;
	uपूर्णांक32_t WBSCL_VERT_FILTER_INIT_Y_RGB;
	uपूर्णांक32_t WBSCL_VERT_FILTER_INIT_CBCR;
	uपूर्णांक32_t WBSCL_ROUND_OFFSET;
	uपूर्णांक32_t WBSCL_OVERFLOW_STATUS;
	uपूर्णांक32_t WBSCL_COEF_RAM_CONFLICT_STATUS;
	uपूर्णांक32_t WBSCL_TEST_CNTL;
	uपूर्णांक32_t WBSCL_TEST_CRC_RED;
	uपूर्णांक32_t WBSCL_TEST_CRC_GREEN;
	uपूर्णांक32_t WBSCL_TEST_CRC_BLUE;
	uपूर्णांक32_t WBSCL_BACKPRESSURE_CNT_EN;
	uपूर्णांक32_t WB_MCIF_BACKPRESSURE_CNT;
	uपूर्णांक32_t WBSCL_CLAMP_Y_RGB;
	uपूर्णांक32_t WBSCL_CLAMP_CBCR;
	uपूर्णांक32_t WBSCL_OUTSIDE_PIX_STRATEGY;
	uपूर्णांक32_t WBSCL_OUTSIDE_PIX_STRATEGY_CBCR;
	uपूर्णांक32_t WBSCL_DEBUG;
	uपूर्णांक32_t WBSCL_TEST_DEBUG_INDEX;
	uपूर्णांक32_t WBSCL_TEST_DEBUG_DATA;
	uपूर्णांक32_t WB_WARM_UP_MODE_CTL1;
	uपूर्णांक32_t WB_WARM_UP_MODE_CTL2;
पूर्ण;


काष्ठा dcn20_dwbc_mask अणु
	DWBC_REG_FIELD_LIST_DCN2_0(uपूर्णांक32_t)
पूर्ण;

काष्ठा dcn20_dwbc_shअगरt अणु
	DWBC_REG_FIELD_LIST_DCN2_0(uपूर्णांक8_t)
पूर्ण;

काष्ठा dcn20_dwbc अणु
	काष्ठा dwbc base;
	स्थिर काष्ठा dcn20_dwbc_रेजिस्टरs *dwbc_regs;
	स्थिर काष्ठा dcn20_dwbc_shअगरt *dwbc_shअगरt;
	स्थिर काष्ठा dcn20_dwbc_mask *dwbc_mask;
पूर्ण;

व्योम dcn20_dwbc_स्थिरruct(काष्ठा dcn20_dwbc *dwbc20,
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dcn20_dwbc_रेजिस्टरs *dwbc_regs,
	स्थिर काष्ठा dcn20_dwbc_shअगरt *dwbc_shअगरt,
	स्थिर काष्ठा dcn20_dwbc_mask *dwbc_mask,
	पूर्णांक inst);

bool dwb2_disable(काष्ठा dwbc *dwbc);

bool dwb2_is_enabled(काष्ठा dwbc *dwbc);

व्योम dwb2_set_stereo(काष्ठा dwbc *dwbc,
	काष्ठा dwb_stereo_params *stereo_params);

व्योम dwb2_set_new_content(काष्ठा dwbc *dwbc,
	bool is_new_content);

व्योम dwb2_config_dwb_cnv(काष्ठा dwbc *dwbc,
	काष्ठा dc_dwb_params *params);

व्योम dwb2_set_scaler(काष्ठा dwbc *dwbc, काष्ठा dc_dwb_params *params);

bool dwb_program_vert_scalar(काष्ठा dcn20_dwbc *dwbc20,
	uपूर्णांक32_t src_height,
	uपूर्णांक32_t dest_height,
	काष्ठा scaling_taps num_taps,
	क्रमागत dwb_subsample_position subsample_position);

bool dwb_program_horz_scalar(काष्ठा dcn20_dwbc *dwbc20,
	uपूर्णांक32_t src_width,
	uपूर्णांक32_t dest_width,
	काष्ठा scaling_taps num_taps);


#पूर्ण_अगर


