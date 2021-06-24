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

#अगर_अघोषित __DCE_I2C_HW_H__
#घोषणा __DCE_I2C_HW_H__

क्रमागत dc_i2c_status अणु
	DC_I2C_STATUS__DC_I2C_STATUS_IDLE,
	DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_SW,
	DC_I2C_STATUS__DC_I2C_STATUS_USED_BY_HW,
	DC_I2C_REG_RW_CNTL_STATUS_DMCU_ONLY = 2,
पूर्ण;

क्रमागत dc_i2c_arbitration अणु
	DC_I2C_ARBITRATION__DC_I2C_SW_PRIORITY_NORMAL,
	DC_I2C_ARBITRATION__DC_I2C_SW_PRIORITY_HIGH
पूर्ण;

क्रमागत i2c_channel_operation_result अणु
	I2C_CHANNEL_OPERATION_SUCCEEDED,
	I2C_CHANNEL_OPERATION_FAILED,
	I2C_CHANNEL_OPERATION_NOT_GRANTED,
	I2C_CHANNEL_OPERATION_IS_BUSY,
	I2C_CHANNEL_OPERATION_NO_HANDLE_PROVIDED,
	I2C_CHANNEL_OPERATION_CHANNEL_IN_USE,
	I2C_CHANNEL_OPERATION_CHANNEL_CLIENT_MAX_ALLOWED,
	I2C_CHANNEL_OPERATION_ENGINE_BUSY,
	I2C_CHANNEL_OPERATION_TIMEOUT,
	I2C_CHANNEL_OPERATION_NO_RESPONSE,
	I2C_CHANNEL_OPERATION_HW_REQUEST_I2C_BUS,
	I2C_CHANNEL_OPERATION_WRONG_PARAMETER,
	I2C_CHANNEL_OPERATION_OUT_NB_OF_RETRIES,
	I2C_CHANNEL_OPERATION_NOT_STARTED
पूर्ण;


क्रमागत dce_i2c_transaction_action अणु
	DCE_I2C_TRANSACTION_ACTION_I2C_WRITE = 0x00,
	DCE_I2C_TRANSACTION_ACTION_I2C_READ = 0x10,
	DCE_I2C_TRANSACTION_ACTION_I2C_STATUS_REQUEST = 0x20,

	DCE_I2C_TRANSACTION_ACTION_I2C_WRITE_MOT = 0x40,
	DCE_I2C_TRANSACTION_ACTION_I2C_READ_MOT = 0x50,
	DCE_I2C_TRANSACTION_ACTION_I2C_STATUS_REQUEST_MOT = 0x60,

	DCE_I2C_TRANSACTION_ACTION_DP_WRITE = 0x80,
	DCE_I2C_TRANSACTION_ACTION_DP_READ = 0x90
पूर्ण;

क्रमागत अणु
	I2C_SETUP_TIME_LIMIT_DCE = 255,
	I2C_SETUP_TIME_LIMIT_DCN = 3,
	I2C_HW_BUFFER_SIZE_DCE100 = 538,
	I2C_HW_BUFFER_SIZE_DCE = 144,
	I2C_SEND_RESET_LENGTH_9 = 9,
	I2C_SEND_RESET_LENGTH_10 = 10,
	DEFAULT_I2C_HW_SPEED = 50,
	DEFAULT_I2C_HW_SPEED_100KHZ = 100,
	TRANSACTION_TIMEOUT_IN_I2C_CLOCKS = 32,
पूर्ण;

#घोषणा I2C_HW_ENGINE_COMMON_REG_LIST(id)\
	SRI(SETUP, DC_I2C_DDC, id),\
	SRI(SPEED, DC_I2C_DDC, id),\
	SRI(HW_STATUS, DC_I2C_DDC, id),\
	SR(DC_I2C_ARBITRATION),\
	SR(DC_I2C_CONTROL),\
	SR(DC_I2C_SW_STATUS),\
	SR(DC_I2C_TRANSACTION0),\
	SR(DC_I2C_TRANSACTION1),\
	SR(DC_I2C_TRANSACTION2),\
	SR(DC_I2C_TRANSACTION3),\
	SR(DC_I2C_DATA),\
	SR(MICROSECOND_TIME_BASE_DIV)

#घोषणा I2C_HW_ENGINE_COMMON_REG_LIST_DCN30(id)\
	I2C_HW_ENGINE_COMMON_REG_LIST(id),\
	SR(DIO_MEM_PWR_CTRL),\
	SR(DIO_MEM_PWR_STATUS)

#घोषणा I2C_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा I2C_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(mask_sh)\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_ENABLE, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_TIME_LIMIT, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DRIVE_EN, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_CLK_DRIVE_EN, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_DATA_DRIVE_SEL, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTRA_TRANSACTION_DELAY, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_INTRA_BYTE_DELAY, mask_sh),\
	I2C_SF(DC_I2C_DDC1_HW_STATUS, DC_I2C_DDC1_HW_STATUS, mask_sh),\
	I2C_SF(DC_I2C_ARBITRATION, DC_I2C_SW_USE_I2C_REG_REQ, mask_sh),\
	I2C_SF(DC_I2C_ARBITRATION, DC_I2C_SW_DONE_USING_I2C_REG, mask_sh),\
	I2C_SF(DC_I2C_ARBITRATION, DC_I2C_NO_QUEUED_SW_GO, mask_sh),\
	I2C_SF(DC_I2C_ARBITRATION, DC_I2C_SW_PRIORITY, mask_sh),\
	I2C_SF(DC_I2C_CONTROL, DC_I2C_SOFT_RESET, mask_sh),\
	I2C_SF(DC_I2C_CONTROL, DC_I2C_SW_STATUS_RESET, mask_sh),\
	I2C_SF(DC_I2C_CONTROL, DC_I2C_GO, mask_sh),\
	I2C_SF(DC_I2C_CONTROL, DC_I2C_SEND_RESET, mask_sh),\
	I2C_SF(DC_I2C_CONTROL, DC_I2C_TRANSACTION_COUNT, mask_sh),\
	I2C_SF(DC_I2C_CONTROL, DC_I2C_DDC_SELECT, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_PRESCALE, mask_sh),\
	I2C_SF(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_THRESHOLD, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_STOPPED_ON_NACK, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_TIMEOUT, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_ABORTED, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_DONE, mask_sh),\
	I2C_SF(DC_I2C_SW_STATUS, DC_I2C_SW_STATUS, mask_sh),\
	I2C_SF(DC_I2C_TRANSACTION0, DC_I2C_STOP_ON_NACK0, mask_sh),\
	I2C_SF(DC_I2C_TRANSACTION0, DC_I2C_START0, mask_sh),\
	I2C_SF(DC_I2C_TRANSACTION0, DC_I2C_RW0, mask_sh),\
	I2C_SF(DC_I2C_TRANSACTION0, DC_I2C_STOP0, mask_sh),\
	I2C_SF(DC_I2C_TRANSACTION0, DC_I2C_COUNT0, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_DATA_RW, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_DATA, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_INDEX, mask_sh),\
	I2C_SF(DC_I2C_DATA, DC_I2C_INDEX_WRITE, mask_sh),\
	I2C_SF(MICROSECOND_TIME_BASE_DIV, XTAL_REF_DIV, mask_sh),\
	I2C_SF(DC_I2C_ARBITRATION, DC_I2C_REG_RW_CNTL_STATUS, mask_sh)

#घोषणा I2C_COMMON_MASK_SH_LIST_DCE110(mask_sh)\
	I2C_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(mask_sh),\
	I2C_SF(DC_I2C_DDC1_SPEED, DC_I2C_DDC1_START_STOP_TIMING_CNTL, mask_sh)

काष्ठा dce_i2c_shअगरt अणु
	uपूर्णांक8_t DC_I2C_DDC1_ENABLE;
	uपूर्णांक8_t DC_I2C_DDC1_TIME_LIMIT;
	uपूर्णांक8_t DC_I2C_DDC1_DATA_DRIVE_EN;
	uपूर्णांक8_t DC_I2C_DDC1_CLK_DRIVE_EN;
	uपूर्णांक8_t DC_I2C_DDC1_DATA_DRIVE_SEL;
	uपूर्णांक8_t DC_I2C_DDC1_INTRA_TRANSACTION_DELAY;
	uपूर्णांक8_t DC_I2C_DDC1_INTRA_BYTE_DELAY;
	uपूर्णांक8_t DC_I2C_DDC1_HW_STATUS;
	uपूर्णांक8_t DC_I2C_SW_DONE_USING_I2C_REG;
	uपूर्णांक8_t DC_I2C_SW_USE_I2C_REG_REQ;
	uपूर्णांक8_t DC_I2C_NO_QUEUED_SW_GO;
	uपूर्णांक8_t DC_I2C_SW_PRIORITY;
	uपूर्णांक8_t DC_I2C_SOFT_RESET;
	uपूर्णांक8_t DC_I2C_SW_STATUS_RESET;
	uपूर्णांक8_t DC_I2C_GO;
	uपूर्णांक8_t DC_I2C_SEND_RESET;
	uपूर्णांक8_t DC_I2C_TRANSACTION_COUNT;
	uपूर्णांक8_t DC_I2C_DDC_SELECT;
	uपूर्णांक8_t DC_I2C_DDC1_PRESCALE;
	uपूर्णांक8_t DC_I2C_DDC1_THRESHOLD;
	uपूर्णांक8_t DC_I2C_DDC1_START_STOP_TIMING_CNTL;
	uपूर्णांक8_t DC_I2C_SW_STOPPED_ON_NACK;
	uपूर्णांक8_t DC_I2C_SW_TIMEOUT;
	uपूर्णांक8_t DC_I2C_SW_ABORTED;
	uपूर्णांक8_t DC_I2C_SW_DONE;
	uपूर्णांक8_t DC_I2C_SW_STATUS;
	uपूर्णांक8_t DC_I2C_STOP_ON_NACK0;
	uपूर्णांक8_t DC_I2C_START0;
	uपूर्णांक8_t DC_I2C_RW0;
	uपूर्णांक8_t DC_I2C_STOP0;
	uपूर्णांक8_t DC_I2C_COUNT0;
	uपूर्णांक8_t DC_I2C_DATA_RW;
	uपूर्णांक8_t DC_I2C_DATA;
	uपूर्णांक8_t DC_I2C_INDEX;
	uपूर्णांक8_t DC_I2C_INDEX_WRITE;
	uपूर्णांक8_t XTAL_REF_DIV;
	uपूर्णांक8_t DC_I2C_DDC1_SEND_RESET_LENGTH;
	uपूर्णांक8_t DC_I2C_REG_RW_CNTL_STATUS;
	uपूर्णांक8_t I2C_LIGHT_SLEEP_FORCE;
	uपूर्णांक8_t I2C_MEM_PWR_STATE;
पूर्ण;

काष्ठा dce_i2c_mask अणु
	uपूर्णांक32_t DC_I2C_DDC1_ENABLE;
	uपूर्णांक32_t DC_I2C_DDC1_TIME_LIMIT;
	uपूर्णांक32_t DC_I2C_DDC1_DATA_DRIVE_EN;
	uपूर्णांक32_t DC_I2C_DDC1_CLK_DRIVE_EN;
	uपूर्णांक32_t DC_I2C_DDC1_DATA_DRIVE_SEL;
	uपूर्णांक32_t DC_I2C_DDC1_INTRA_TRANSACTION_DELAY;
	uपूर्णांक32_t DC_I2C_DDC1_INTRA_BYTE_DELAY;
	uपूर्णांक32_t DC_I2C_DDC1_HW_STATUS;
	uपूर्णांक32_t DC_I2C_SW_DONE_USING_I2C_REG;
	uपूर्णांक32_t DC_I2C_SW_USE_I2C_REG_REQ;
	uपूर्णांक32_t DC_I2C_NO_QUEUED_SW_GO;
	uपूर्णांक32_t DC_I2C_SW_PRIORITY;
	uपूर्णांक32_t DC_I2C_SOFT_RESET;
	uपूर्णांक32_t DC_I2C_SW_STATUS_RESET;
	uपूर्णांक32_t DC_I2C_GO;
	uपूर्णांक32_t DC_I2C_SEND_RESET;
	uपूर्णांक32_t DC_I2C_TRANSACTION_COUNT;
	uपूर्णांक32_t DC_I2C_DDC_SELECT;
	uपूर्णांक32_t DC_I2C_DDC1_PRESCALE;
	uपूर्णांक32_t DC_I2C_DDC1_THRESHOLD;
	uपूर्णांक32_t DC_I2C_DDC1_START_STOP_TIMING_CNTL;
	uपूर्णांक32_t DC_I2C_SW_STOPPED_ON_NACK;
	uपूर्णांक32_t DC_I2C_SW_TIMEOUT;
	uपूर्णांक32_t DC_I2C_SW_ABORTED;
	uपूर्णांक32_t DC_I2C_SW_DONE;
	uपूर्णांक32_t DC_I2C_SW_STATUS;
	uपूर्णांक32_t DC_I2C_STOP_ON_NACK0;
	uपूर्णांक32_t DC_I2C_START0;
	uपूर्णांक32_t DC_I2C_RW0;
	uपूर्णांक32_t DC_I2C_STOP0;
	uपूर्णांक32_t DC_I2C_COUNT0;
	uपूर्णांक32_t DC_I2C_DATA_RW;
	uपूर्णांक32_t DC_I2C_DATA;
	uपूर्णांक32_t DC_I2C_INDEX;
	uपूर्णांक32_t DC_I2C_INDEX_WRITE;
	uपूर्णांक32_t XTAL_REF_DIV;
	uपूर्णांक32_t DC_I2C_DDC1_SEND_RESET_LENGTH;
	uपूर्णांक32_t DC_I2C_REG_RW_CNTL_STATUS;
	uपूर्णांक32_t I2C_LIGHT_SLEEP_FORCE;
	uपूर्णांक32_t I2C_MEM_PWR_STATE;
पूर्ण;

#घोषणा I2C_COMMON_MASK_SH_LIST_DCN2(mask_sh)\
	I2C_COMMON_MASK_SH_LIST_DCE110(mask_sh),\
	I2C_SF(DC_I2C_DDC1_SETUP, DC_I2C_DDC1_SEND_RESET_LENGTH, mask_sh)

#घोषणा I2C_COMMON_MASK_SH_LIST_DCN30(mask_sh)\
	I2C_COMMON_MASK_SH_LIST_DCN2(mask_sh),\
	I2C_SF(DIO_MEM_PWR_CTRL, I2C_LIGHT_SLEEP_FORCE, mask_sh),\
	I2C_SF(DIO_MEM_PWR_STATUS, I2C_MEM_PWR_STATE, mask_sh)

काष्ठा dce_i2c_रेजिस्टरs अणु
	uपूर्णांक32_t SETUP;
	uपूर्णांक32_t SPEED;
	uपूर्णांक32_t HW_STATUS;
	uपूर्णांक32_t DC_I2C_ARBITRATION;
	uपूर्णांक32_t DC_I2C_CONTROL;
	uपूर्णांक32_t DC_I2C_SW_STATUS;
	uपूर्णांक32_t DC_I2C_TRANSACTION0;
	uपूर्णांक32_t DC_I2C_TRANSACTION1;
	uपूर्णांक32_t DC_I2C_TRANSACTION2;
	uपूर्णांक32_t DC_I2C_TRANSACTION3;
	uपूर्णांक32_t DC_I2C_DATA;
	uपूर्णांक32_t MICROSECOND_TIME_BASE_DIV;
	uपूर्णांक32_t DIO_MEM_PWR_CTRL;
	uपूर्णांक32_t DIO_MEM_PWR_STATUS;
पूर्ण;

क्रमागत dce_i2c_transaction_address_space अणु
	DCE_I2C_TRANSACTION_ADDRESS_SPACE_I2C = 1,
	DCE_I2C_TRANSACTION_ADDRESS_SPACE_DPCD
पूर्ण;

काष्ठा i2c_request_transaction_data अणु
	क्रमागत dce_i2c_transaction_action action;
	क्रमागत i2c_channel_operation_result status;
	uपूर्णांक8_t address;
	uपूर्णांक32_t length;
	uपूर्णांक8_t *data;
पूर्ण;

काष्ठा dce_i2c_hw अणु
	काष्ठा ddc *ddc;
	uपूर्णांक32_t engine_keep_घातer_up_count;
	uपूर्णांक32_t transaction_count;
	uपूर्णांक32_t buffer_used_bytes;
	uपूर्णांक32_t buffer_used_ग_लिखो;
	uपूर्णांक32_t reference_frequency;
	uपूर्णांक32_t शेष_speed;
	uपूर्णांक32_t engine_id;
	uपूर्णांक32_t setup_limit;
	uपूर्णांक32_t send_reset_length;
	uपूर्णांक32_t buffer_size;
	काष्ठा dc_context *ctx;

	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs;
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts;
	स्थिर काष्ठा dce_i2c_mask *masks;
पूर्ण;

व्योम dce_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks);

व्योम dce100_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks);

व्योम dce112_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks);

व्योम dcn1_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks);

व्योम dcn2_i2c_hw_स्थिरruct(
	काष्ठा dce_i2c_hw *dce_i2c_hw,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t engine_id,
	स्थिर काष्ठा dce_i2c_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_i2c_shअगरt *shअगरts,
	स्थिर काष्ठा dce_i2c_mask *masks);

bool dce_i2c_submit_command_hw(
	काष्ठा resource_pool *pool,
	काष्ठा ddc *ddc,
	काष्ठा i2c_command *cmd,
	काष्ठा dce_i2c_hw *dce_i2c_hw);

काष्ठा dce_i2c_hw *acquire_i2c_hw_engine(
	काष्ठा resource_pool *pool,
	काष्ठा ddc *ddc);

#पूर्ण_अगर
