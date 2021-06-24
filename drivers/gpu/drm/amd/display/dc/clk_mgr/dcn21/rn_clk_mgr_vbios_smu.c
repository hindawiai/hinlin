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

#समावेश "renoir_ip_offset.h"

#समावेश "mp/mp_12_0_0_offset.h"
#समावेश "mp/mp_12_0_0_sh_mask.h"

#घोषणा REG(reg_name) \
	(MP0_BASE.instance[0].segment[mm ## reg_name ## _BASE_IDX] + mm ## reg_name)

#घोषणा FN(reg_name, field) \
	FD(reg_name##__##field)

#घोषणा VBIOSSMC_MSG_TestMessage                  0x1
#घोषणा VBIOSSMC_MSG_GetSmuVersion                0x2
#घोषणा VBIOSSMC_MSG_PowerUpGfx                   0x3
#घोषणा VBIOSSMC_MSG_SetDispclkFreq               0x4
#घोषणा VBIOSSMC_MSG_SetDprefclkFreq              0x5
#घोषणा VBIOSSMC_MSG_PowerDownGfx                 0x6
#घोषणा VBIOSSMC_MSG_SetDppclkFreq                0x7
#घोषणा VBIOSSMC_MSG_SetHardMinDcfclkByFreq       0x8
#घोषणा VBIOSSMC_MSG_SetMinDeepSleepDcfclk        0x9
#घोषणा VBIOSSMC_MSG_SetPhyclkVoltageByFreq       0xA
#घोषणा VBIOSSMC_MSG_GetFclkFrequency             0xB
#घोषणा VBIOSSMC_MSG_SetDisplayCount              0xC
#घोषणा VBIOSSMC_MSG_EnableTmdp48MHzRefclkPwrDown 0xD
#घोषणा VBIOSSMC_MSG_UpdatePmeRestore             0xE
#घोषणा VBIOSSMC_MSG_IsPeriodicRetrainingDisabled 0xF

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
अटल uपूर्णांक32_t rn_smu_रुको_क्रम_response(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक delay_us, अचिन्हित पूर्णांक max_retries)
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


पूर्णांक rn_vbios_smu_send_msg_with_param(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक msg_id, अचिन्हित पूर्णांक param)
अणु
	uपूर्णांक32_t result;

	/* First clear response रेजिस्टर */
	REG_WRITE(MP1_SMN_C2PMSG_91, VBIOSSMC_Status_BUSY);

	/* Set the parameter रेजिस्टर क्रम the SMU message, unit is Mhz */
	REG_WRITE(MP1_SMN_C2PMSG_83, param);

	/* Trigger the message transaction by writing the message ID */
	REG_WRITE(MP1_SMN_C2PMSG_67, msg_id);

	result = rn_smu_रुको_क्रम_response(clk_mgr, 10, 200000);

	ASSERT(result == VBIOSSMC_Result_OK || result == VBIOSSMC_Result_UnknownCmd);

	/* Actual dispclk set is वापसed in the parameter रेजिस्टर */
	वापस REG_READ(MP1_SMN_C2PMSG_83);
पूर्ण

पूर्णांक rn_vbios_smu_get_smu_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	वापस rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_GetSmuVersion,
			0);
पूर्ण


पूर्णांक rn_vbios_smu_set_dispclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dispclk_khz)
अणु
	पूर्णांक actual_dispclk_set_mhz = -1;
	काष्ठा dc *dc = clk_mgr->base.ctx->dc;
	काष्ठा dmcu *dmcu = dc->res_pool->dmcu;

	/*  Unit of SMU msg parameter is Mhz */
	actual_dispclk_set_mhz = rn_vbios_smu_send_msg_with_param(
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

	// pmfw always set घड़ी more than or equal requested घड़ी
	अगर (!IS_DIAG_DC(dc->ctx->dce_environment))
		ASSERT(actual_dispclk_set_mhz >= requested_dispclk_khz / 1000);

	वापस actual_dispclk_set_mhz * 1000;
पूर्ण

पूर्णांक rn_vbios_smu_set_dprefclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	पूर्णांक actual_dprefclk_set_mhz = -1;

	actual_dprefclk_set_mhz = rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDprefclkFreq,
			clk_mgr->base.dprefclk_khz / 1000);

	/* TODO: add code क्रम programing DP DTO, currently this is करोwn by command table */

	वापस actual_dprefclk_set_mhz * 1000;
पूर्ण

पूर्णांक rn_vbios_smu_set_hard_min_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dcfclk_khz)
अणु
	पूर्णांक actual_dcfclk_set_mhz = -1;

	अगर (clk_mgr->smu_ver < 0x370c00)
		वापस actual_dcfclk_set_mhz;

	actual_dcfclk_set_mhz = rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetHardMinDcfclkByFreq,
			requested_dcfclk_khz / 1000);

	वापस actual_dcfclk_set_mhz * 1000;
पूर्ण

पूर्णांक rn_vbios_smu_set_min_deep_sleep_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_min_ds_dcfclk_khz)
अणु
	पूर्णांक actual_min_ds_dcfclk_mhz = -1;

	अगर (clk_mgr->smu_ver < 0x370c00)
		वापस actual_min_ds_dcfclk_mhz;

	actual_min_ds_dcfclk_mhz = rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetMinDeepSleepDcfclk,
			requested_min_ds_dcfclk_khz / 1000);

	वापस actual_min_ds_dcfclk_mhz * 1000;
पूर्ण

व्योम rn_vbios_smu_set_phyclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_phyclk_khz)
अणु
	rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetPhyclkVoltageByFreq,
			requested_phyclk_khz / 1000);
पूर्ण

पूर्णांक rn_vbios_smu_set_dppclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dpp_khz)
अणु
	पूर्णांक actual_dppclk_set_mhz = -1;
	काष्ठा dc *dc = clk_mgr->base.ctx->dc;

	actual_dppclk_set_mhz = rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDppclkFreq,
			requested_dpp_khz / 1000);

	अगर (!IS_DIAG_DC(dc->ctx->dce_environment))
		ASSERT(actual_dppclk_set_mhz >= requested_dpp_khz / 1000);

	वापस actual_dppclk_set_mhz * 1000;
पूर्ण

व्योम rn_vbios_smu_set_dcn_low_घातer_state(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, क्रमागत dcn_pwr_state state)
अणु
	पूर्णांक disp_count;

	अगर (state == DCN_PWR_STATE_LOW_POWER)
		disp_count = 0;
	अन्यथा
		disp_count = 1;

	rn_vbios_smu_send_msg_with_param(
		clk_mgr,
		VBIOSSMC_MSG_SetDisplayCount,
		disp_count);
पूर्ण

व्योम rn_vbios_smu_enable_48mhz_पंचांगdp_refclk_pwrdwn(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable)
अणु
	rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_EnableTmdp48MHzRefclkPwrDown,
			enable);
पूर्ण

व्योम rn_vbios_smu_enable_pme_wa(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_UpdatePmeRestore,
			0);
पूर्ण

पूर्णांक rn_vbios_smu_is_periodic_retraining_disabled(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	वापस rn_vbios_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_IsPeriodicRetrainingDisabled,
			1);	// अगर PMFW करोesn't support this message, assume retraining is disabled
				// so we only use most optimal watermark अगर we know retraining is enabled.
पूर्ण
