<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#समावेश "core_types.h"
#समावेश "clk_mgr_internal.h"
#समावेश "reg_helper.h"
#समावेश <linux/delay.h>

#घोषणा MAX_INSTANCE	5
#घोषणा MAX_SEGMENT		5

काष्ठा IP_BASE_INSTANCE अणु
	अचिन्हित पूर्णांक segment[MAX_SEGMENT];
पूर्ण;

काष्ठा IP_BASE अणु
	काष्ठा IP_BASE_INSTANCE instance[MAX_INSTANCE];
पूर्ण;


अटल स्थिर काष्ठा IP_BASE MP1_BASE  = अणु अणु अणु अणु 0x00016000, 0, 0, 0, 0 पूर्ण पूर्ण,
											 अणु अणु 0, 0, 0, 0, 0 पूर्ण पूर्ण,
											 अणु अणु 0, 0, 0, 0, 0 पूर्ण पूर्ण,
											 अणु अणु 0, 0, 0, 0, 0 पूर्ण पूर्ण,
											 अणु अणु 0, 0, 0, 0, 0 पूर्ण पूर्ण पूर्ण पूर्ण;

#घोषणा mmMP1_SMN_C2PMSG_91            0x29B
#घोषणा mmMP1_SMN_C2PMSG_83            0x293
#घोषणा mmMP1_SMN_C2PMSG_67            0x283
#घोषणा mmMP1_SMN_C2PMSG_91_BASE_IDX   0
#घोषणा mmMP1_SMN_C2PMSG_83_BASE_IDX   0
#घोषणा mmMP1_SMN_C2PMSG_67_BASE_IDX   0

#घोषणा MP1_SMN_C2PMSG_91__CONTENT_MASK                    0xffffffffL
#घोषणा MP1_SMN_C2PMSG_83__CONTENT_MASK                    0xffffffffL
#घोषणा MP1_SMN_C2PMSG_67__CONTENT_MASK                    0xffffffffL
#घोषणा MP1_SMN_C2PMSG_91__CONTENT__SHIFT                  0x00000000
#घोषणा MP1_SMN_C2PMSG_83__CONTENT__SHIFT                  0x00000000
#घोषणा MP1_SMN_C2PMSG_67__CONTENT__SHIFT                  0x00000000

#घोषणा REG(reg_name) \
	(MP1_BASE.instance[0].segment[mm ## reg_name ## _BASE_IDX] + mm ## reg_name)

#घोषणा FN(reg_name, field) \
	FD(reg_name##__##field)

#घोषणा VBIOSSMC_MSG_SetDispclkFreq           0x4
#घोषणा VBIOSSMC_MSG_SetDprefclkFreq          0x5

#घोषणा VBIOSSMC_Status_BUSY                      0x0
#घोषणा VBIOSSMC_Result_OK                        0x1
#घोषणा VBIOSSMC_Result_Failed                    0xFF
#घोषणा VBIOSSMC_Result_UnknownCmd                0xFE
#घोषणा VBIOSSMC_Result_CmdRejectedPrereq         0xFD
#घोषणा VBIOSSMC_Result_CmdRejectedBusy           0xFC

/*
 * Function to be used instead of REG_WAIT macro because the रुको ends when
 * the रेजिस्टर is NOT EQUAL to zero, and because the translation in msg_अगर.h
 * won't work with REG_WAIT.
 */
अटल uपूर्णांक32_t rv1_smu_रुको_क्रम_response(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक delay_us, अचिन्हित पूर्णांक max_retries)
अणु
	uपूर्णांक32_t res_val = VBIOSSMC_Status_BUSY;

	करो अणु
		res_val = REG_READ(MP1_SMN_C2PMSG_91);
		अगर (res_val != VBIOSSMC_Status_BUSY)
			अवरोध;

		अगर (delay_us >= 1000)
			msleep(delay_us/1000);
		अन्यथा अगर (delay_us > 0)
			udelay(delay_us);
	पूर्ण जबतक (max_retries--);

	वापस res_val;
पूर्ण

पूर्णांक rv1_vbios_smu_send_msg_with_param(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक msg_id, अचिन्हित पूर्णांक param)
अणु
	uपूर्णांक32_t result;

	/* First clear response रेजिस्टर */
	REG_WRITE(MP1_SMN_C2PMSG_91, VBIOSSMC_Status_BUSY);

	/* Set the parameter रेजिस्टर क्रम the SMU message, unit is Mhz */
	REG_WRITE(MP1_SMN_C2PMSG_83, param);

	/* Trigger the message transaction by writing the message ID */
	REG_WRITE(MP1_SMN_C2PMSG_67, msg_id);

	result = rv1_smu_रुको_क्रम_response(clk_mgr, 10, 1000);

	ASSERT(result == VBIOSSMC_Result_OK);

	/* Actual dispclk set is वापसed in the parameter रेजिस्टर */
	वापस REG_READ(MP1_SMN_C2PMSG_83);
पूर्ण

पूर्णांक rv1_vbios_smu_set_dispclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dispclk_khz)
अणु
	पूर्णांक actual_dispclk_set_mhz = -1;
	काष्ठा dc *dc = clk_mgr->base.ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;

	/*  Unit of SMU msg parameter is Mhz */
	actual_dispclk_set_mhz = rv1_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDispclkFreq,
			requested_dispclk_khz / 1000);

	अगर (!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment)) अणु
		अगर (dmcu && dmcu->funcs->is_dmcu_initialized(dmcu)) अणु
			अगर (clk_mgr->dfs_bypass_disp_clk != actual_dispclk_set_mhz)
				dmcu->funcs->set_psr_रुको_loop(dmcu,
						actual_dispclk_set_mhz / 7);
		पूर्ण
	पूर्ण

	वापस actual_dispclk_set_mhz * 1000;
पूर्ण

पूर्णांक rv1_vbios_smu_set_dprefclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	पूर्णांक actual_dprefclk_set_mhz = -1;

	actual_dprefclk_set_mhz = rv1_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDprefclkFreq,
			clk_mgr->base.dprefclk_khz / 1000);

	/* TODO: add code क्रम programing DP DTO, currently this is करोwn by command table */

	वापस actual_dprefclk_set_mhz * 1000;
पूर्ण
