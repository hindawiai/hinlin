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

#अगर_अघोषित __DAL_AUX_ENGINE_DCE110_H__
#घोषणा __DAL_AUX_ENGINE_DCE110_H__

#समावेश "i2caux_interface.h"
#समावेश "inc/hw/aux_engine.h"

क्रमागत aux_वापस_code_type;

#घोषणा AUX_COMMON_REG_LIST0(id)\
	SRI(AUX_CONTROL, DP_AUX, id), \
	SRI(AUX_ARB_CONTROL, DP_AUX, id), \
	SRI(AUX_SW_DATA, DP_AUX, id), \
	SRI(AUX_SW_CONTROL, DP_AUX, id), \
	SRI(AUX_INTERRUPT_CONTROL, DP_AUX, id), \
	SRI(AUX_DPHY_RX_CONTROL1, DP_AUX, id), \
	SRI(AUX_SW_STATUS, DP_AUX, id)

#घोषणा AUX_COMMON_REG_LIST(id)\
	SRI(AUX_CONTROL, DP_AUX, id), \
	SRI(AUX_ARB_CONTROL, DP_AUX, id), \
	SRI(AUX_SW_DATA, DP_AUX, id), \
	SRI(AUX_SW_CONTROL, DP_AUX, id), \
	SRI(AUX_INTERRUPT_CONTROL, DP_AUX, id), \
	SRI(AUX_SW_STATUS, DP_AUX, id), \
	SR(AUXN_IMPCAL), \
	SR(AUXP_IMPCAL)

काष्ठा dce110_aux_रेजिस्टरs अणु
	uपूर्णांक32_t AUX_CONTROL;
	uपूर्णांक32_t AUX_ARB_CONTROL;
	uपूर्णांक32_t AUX_SW_DATA;
	uपूर्णांक32_t AUX_SW_CONTROL;
	uपूर्णांक32_t AUX_INTERRUPT_CONTROL;
	uपूर्णांक32_t AUX_DPHY_RX_CONTROL1;
	uपूर्णांक32_t AUX_SW_STATUS;
	uपूर्णांक32_t AUXN_IMPCAL;
	uपूर्णांक32_t AUXP_IMPCAL;

	uपूर्णांक32_t AUX_RESET_MASK;
पूर्ण;

#घोषणा DCE_AUX_REG_FIELD_LIST(type)\
	type AUX_EN;\
	type AUX_RESET;\
	type AUX_RESET_DONE;\
	type AUX_REG_RW_CNTL_STATUS;\
	type AUX_SW_USE_AUX_REG_REQ;\
	type AUX_SW_DONE_USING_AUX_REG;\
	type AUX_SW_AUTOINCREMENT_DISABLE;\
	type AUX_SW_DATA_RW;\
	type AUX_SW_INDEX;\
	type AUX_SW_GO;\
	type AUX_SW_DATA;\
	type AUX_SW_REPLY_BYTE_COUNT;\
	type AUX_SW_DONE;\
	type AUX_SW_DONE_ACK;\
	type AUXN_IMPCAL_ENABLE;\
	type AUXP_IMPCAL_ENABLE;\
	type AUXN_IMPCAL_OVERRIDE_ENABLE;\
	type AUXP_IMPCAL_OVERRIDE_ENABLE;\
	type AUX_RX_TIMEOUT_LEN;\
	type AUX_RX_TIMEOUT_LEN_MUL;\
	type AUXN_CALOUT_ERROR_AK;\
	type AUXP_CALOUT_ERROR_AK;\
	type AUX_SW_START_DELAY;\
	type AUX_SW_WR_BYTES

#घोषणा DCE10_AUX_MASK_SH_LIST(mask_sh)\
	AUX_SF(AUX_CONTROL, AUX_EN, mask_sh),\
	AUX_SF(AUX_ARB_CONTROL, AUX_REG_RW_CNTL_STATUS, mask_sh),\
	AUX_SF(AUX_ARB_CONTROL, AUX_SW_USE_AUX_REG_REQ, mask_sh),\
	AUX_SF(AUX_ARB_CONTROL, AUX_SW_DONE_USING_AUX_REG, mask_sh),\
	AUX_SF(AUX_SW_CONTROL, AUX_SW_START_DELAY, mask_sh),\
	AUX_SF(AUX_SW_CONTROL, AUX_SW_WR_BYTES, mask_sh),\
	AUX_SF(AUX_SW_CONTROL, AUX_SW_GO, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA_RW, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_REPLY_BYTE_COUNT, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(AUX_INTERRUPT_CONTROL, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_OVERRIDE_ENABLE, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_OVERRIDE_ENABLE, mask_sh)

#घोषणा DCE_AUX_MASK_SH_LIST(mask_sh)\
	AUX_SF(AUX_CONTROL, AUX_EN, mask_sh),\
	AUX_SF(AUX_CONTROL, AUX_RESET, mask_sh),\
	AUX_SF(AUX_CONTROL, AUX_RESET_DONE, mask_sh),\
	AUX_SF(AUX_ARB_CONTROL, AUX_REG_RW_CNTL_STATUS, mask_sh),\
	AUX_SF(AUX_ARB_CONTROL, AUX_SW_USE_AUX_REG_REQ, mask_sh),\
	AUX_SF(AUX_ARB_CONTROL, AUX_SW_DONE_USING_AUX_REG, mask_sh),\
	AUX_SF(AUX_SW_CONTROL, AUX_SW_START_DELAY, mask_sh),\
	AUX_SF(AUX_SW_CONTROL, AUX_SW_WR_BYTES, mask_sh),\
	AUX_SF(AUX_SW_CONTROL, AUX_SW_GO, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA_RW, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_REPLY_BYTE_COUNT, mask_sh),\
	AUX_SF(AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(AUX_INTERRUPT_CONTROL, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_OVERRIDE_ENABLE, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_OVERRIDE_ENABLE, mask_sh)

#घोषणा DCE12_AUX_MASK_SH_LIST(mask_sh)\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_EN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_RESET, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_RESET_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_REG_RW_CNTL_STATUS, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_SW_USE_AUX_REG_REQ, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_SW_DONE_USING_AUX_REG, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_START_DELAY, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_WR_BYTES, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_GO, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA_RW, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_REPLY_BYTE_COUNT, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_INTERRUPT_CONTROL, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_OVERRIDE_ENABLE, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_OVERRIDE_ENABLE, mask_sh)

/* DCN10 MASK */
#घोषणा DCN10_AUX_MASK_SH_LIST(mask_sh)\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_EN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_RESET, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_RESET_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_REG_RW_CNTL_STATUS, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_SW_USE_AUX_REG_REQ, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_SW_DONE_USING_AUX_REG, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_START_DELAY, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_WR_BYTES, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_GO, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA_RW, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_REPLY_BYTE_COUNT, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_INTERRUPT_CONTROL, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_CALOUT_ERROR_AK, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_ENABLE, mask_sh),\
	AUX_SF(AUXP_IMPCAL, AUXP_IMPCAL_OVERRIDE_ENABLE, mask_sh),\
	AUX_SF(AUXN_IMPCAL, AUXN_IMPCAL_OVERRIDE_ENABLE, mask_sh)

/* क्रम all other DCN */
#घोषणा DCN_AUX_MASK_SH_LIST(mask_sh)\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_EN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_RESET, mask_sh),\
	AUX_SF(DP_AUX0_AUX_CONTROL, AUX_RESET_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_REG_RW_CNTL_STATUS, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_SW_USE_AUX_REG_REQ, mask_sh),\
	AUX_SF(DP_AUX0_AUX_ARB_CONTROL, AUX_SW_DONE_USING_AUX_REG, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_START_DELAY, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_WR_BYTES, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_CONTROL, AUX_SW_GO, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA_RW, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_AUTOINCREMENT_DISABLE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_INDEX, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_DATA, AUX_SW_DATA, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_REPLY_BYTE_COUNT, mask_sh),\
	AUX_SF(DP_AUX0_AUX_SW_STATUS, AUX_SW_DONE, mask_sh),\
	AUX_SF(DP_AUX0_AUX_INTERRUPT_CONTROL, AUX_SW_DONE_ACK, mask_sh),\
	AUX_SF(DP_AUX0_AUX_DPHY_RX_CONTROL1, AUX_RX_TIMEOUT_LEN, mask_sh),\
	AUX_SF(DP_AUX0_AUX_DPHY_RX_CONTROL1, AUX_RX_TIMEOUT_LEN_MUL, mask_sh)

#घोषणा AUX_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

क्रमागत अणु	/* This is the समयout as defined in DP 1.2a,
	 * 2.3.4 "Detailed uPacket TX AUX CH State Description".
	 */
	AUX_TIMEOUT_PERIOD = 400,

	/* Ideally, the SW समयout should be just above 550usec
	 * which is programmed in HW.
	 * But the SW समयout of 600usec is not reliable,
	 * because on some प्रणालीs, delay_in_microseconds()
	 * वापसs faster than it should.
	 * EPR #379763: by trial-and-error on dअगरferent प्रणालीs,
	 * 700usec is the minimum reliable SW समयout क्रम polling
	 * the AUX_SW_STATUS.AUX_SW_DONE bit.
	 * This समयout expires *only* when there is
	 * AUX Error or AUX Timeout conditions - not during normal operation.
	 * During normal operation, AUX_SW_STATUS.AUX_SW_DONE bit is set
	 * at most within ~240usec. That means,
	 * increasing this समयout will not affect normal operation,
	 * and we'll समयout after
	 * SW_AUX_TIMEOUT_PERIOD_MULTIPLIER * AUX_TIMEOUT_PERIOD = 2400usec.
	 * This समयout is especially important क्रम
	 * converters, resume from S3, and CTS.
	 */
	SW_AUX_TIMEOUT_PERIOD_MULTIPLIER = 6
पूर्ण;

काष्ठा dce_aux अणु
	uपूर्णांक32_t inst;
	काष्ठा ddc *ddc;
	काष्ठा dc_context *ctx;
	/* following values are expressed in milliseconds */
	uपूर्णांक32_t delay;
	uपूर्णांक32_t max_defer_ग_लिखो_retry;

	bool acquire_reset;
	काष्ठा dce_aux_funcs *funcs;
पूर्ण;

काष्ठा dce110_aux_रेजिस्टरs_mask अणु
	DCE_AUX_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dce110_aux_रेजिस्टरs_shअगरt अणु
	DCE_AUX_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;


काष्ठा aux_engine_dce110 अणु
	काष्ठा dce_aux base;
	स्थिर काष्ठा dce110_aux_रेजिस्टरs *regs;
	स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask *mask;
	स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt *shअगरt;
	काष्ठा अणु
		uपूर्णांक32_t aux_control;
		uपूर्णांक32_t aux_arb_control;
		uपूर्णांक32_t aux_sw_data;
		uपूर्णांक32_t aux_sw_control;
		uपूर्णांक32_t aux_पूर्णांकerrupt_control;
		uपूर्णांक32_t aux_dphy_rx_control1;
		uपूर्णांक32_t aux_dphy_rx_control0;
		uपूर्णांक32_t aux_sw_status;
	पूर्ण addr;
	uपूर्णांक32_t polling_समयout_period;
पूर्ण;

काष्ठा aux_engine_dce110_init_data अणु
	uपूर्णांक32_t engine_id;
	uपूर्णांक32_t समयout_period;
	काष्ठा dc_context *ctx;
	स्थिर काष्ठा dce110_aux_रेजिस्टरs *regs;
पूर्ण;

काष्ठा dce_aux *dce110_aux_engine_स्थिरruct(काष्ठा aux_engine_dce110 *aux_engine110,
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t inst,
		uपूर्णांक32_t समयout_period,
		स्थिर काष्ठा dce110_aux_रेजिस्टरs *regs,

		स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask *mask,
		स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt *shअगरt,
		bool is_ext_aux_समयout_configurable);

व्योम dce110_engine_destroy(काष्ठा dce_aux **engine);

bool dce110_aux_engine_acquire(
	काष्ठा dce_aux *aux_engine,
	काष्ठा ddc *ddc);

पूर्णांक dce_aux_transfer_raw(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *cmd,
		क्रमागत aux_वापस_code_type *operation_result);

bool dce_aux_transfer_with_retries(काष्ठा ddc_service *ddc,
		काष्ठा aux_payload *cmd);

काष्ठा dce_aux_funcs अणु
	uपूर्णांक32_t (*configure_समयout)
		(काष्ठा ddc_service *ddc,
		 uपूर्णांक32_t समयout);
	व्योम (*destroy)
		(काष्ठा aux_engine **ptr);
पूर्ण;

#पूर्ण_अगर
