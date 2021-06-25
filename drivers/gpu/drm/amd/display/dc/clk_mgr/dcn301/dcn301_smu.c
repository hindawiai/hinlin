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

#समावेश "core_types.h"
#समावेश "clk_mgr_internal.h"
#समावेश "reg_helper.h"
#समावेश <linux/delay.h>

#समावेश "dcn301_smu.h"

#समावेश "vangogh_ip_offset.h"

#समावेश "mp/mp_11_5_0_offset.h"
#समावेश "mp/mp_11_5_0_sh_mask.h"

#घोषणा REG(reg_name) \
	(MP0_BASE.instance[0].segment[mm ## reg_name ## _BASE_IDX] + mm ## reg_name)

#घोषणा FN(reg_name, field) \
	FD(reg_name##__##field)

#घोषणा VBIOSSMC_MSG_GetSmuVersion                0x2
#घोषणा VBIOSSMC_MSG_SetDispclkFreq               0x4
#घोषणा VBIOSSMC_MSG_SetDprefclkFreq              0x5
#घोषणा VBIOSSMC_MSG_SetDppclkFreq                0x6
#घोषणा VBIOSSMC_MSG_SetHardMinDcfclkByFreq       0x7
#घोषणा VBIOSSMC_MSG_SetMinDeepSleepDcfclk        0x8
//#घोषणा VBIOSSMC_MSG_SetPhyclkVoltageByFreq       0xA
#घोषणा VBIOSSMC_MSG_GetFclkFrequency             0xA
//#घोषणा VBIOSSMC_MSG_SetDisplayCount              0xC
//#घोषणा VBIOSSMC_MSG_EnableTmdp48MHzRefclkPwrDown 0xD
#घोषणा VBIOSSMC_MSG_UpdatePmeRestore			  0xD
#घोषणा VBIOSSMC_MSG_SetVbiosDramAddrHigh         0xE   //Used क्रम WM table txfr
#घोषणा VBIOSSMC_MSG_SetVbiosDramAddrLow          0xF
#घोषणा VBIOSSMC_MSG_TransferTableSmu2Dram        0x10
#घोषणा VBIOSSMC_MSG_TransferTableDram2Smu        0x11
#घोषणा VBIOSSMC_MSG_SetDisplayIdleOptimizations  0x12

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
अटल uपूर्णांक32_t dcn301_smu_रुको_क्रम_response(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक delay_us, अचिन्हित पूर्णांक max_retries)
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

पूर्णांक dcn301_smu_send_msg_with_param(
		काष्ठा clk_mgr_पूर्णांकernal *clk_mgr,
		अचिन्हित पूर्णांक msg_id, अचिन्हित पूर्णांक param)
अणु
	uपूर्णांक32_t result;

	/* First clear response रेजिस्टर */
	REG_WRITE(MP1_SMN_C2PMSG_91, VBIOSSMC_Status_BUSY);

	/* Set the parameter रेजिस्टर क्रम the SMU message, unit is Mhz */
	REG_WRITE(MP1_SMN_C2PMSG_83, param);

	/* Trigger the message transaction by writing the message ID */
	REG_WRITE(MP1_SMN_C2PMSG_67, msg_id);

	result = dcn301_smu_रुको_क्रम_response(clk_mgr, 10, 200000);

	ASSERT(result == VBIOSSMC_Result_OK);

	/* Actual dispclk set is वापसed in the parameter रेजिस्टर */
	वापस REG_READ(MP1_SMN_C2PMSG_83);
पूर्ण

पूर्णांक dcn301_smu_get_smu_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	पूर्णांक smu_version = dcn301_smu_send_msg_with_param(clk_mgr,
							 VBIOSSMC_MSG_GetSmuVersion,
							 0);

	DC_LOG_DEBUG("%s %x\n", __func__, smu_version);

	वापस smu_version;
पूर्ण


पूर्णांक dcn301_smu_set_dispclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dispclk_khz)
अणु
	पूर्णांक actual_dispclk_set_mhz = -1;

	DC_LOG_DEBUG("%s(%d)\n", __func__, requested_dispclk_khz);

	/*  Unit of SMU msg parameter is Mhz */
	actual_dispclk_set_mhz = dcn301_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDispclkFreq,
			requested_dispclk_khz / 1000);

	वापस actual_dispclk_set_mhz * 1000;
पूर्ण

पूर्णांक dcn301_smu_set_dprefclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	पूर्णांक actual_dprefclk_set_mhz = -1;

	DC_LOG_DEBUG("%s %d\n", __func__, clk_mgr->base.dprefclk_khz / 1000);

	actual_dprefclk_set_mhz = dcn301_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDprefclkFreq,
			clk_mgr->base.dprefclk_khz / 1000);

	/* TODO: add code क्रम programing DP DTO, currently this is करोwn by command table */

	वापस actual_dprefclk_set_mhz * 1000;
पूर्ण

पूर्णांक dcn301_smu_set_hard_min_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dcfclk_khz)
अणु
	पूर्णांक actual_dcfclk_set_mhz = -1;

	DC_LOG_DEBUG("%s(%d)\n", __func__, requested_dcfclk_khz);

	actual_dcfclk_set_mhz = dcn301_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetHardMinDcfclkByFreq,
			requested_dcfclk_khz / 1000);

	वापस actual_dcfclk_set_mhz * 1000;
पूर्ण

पूर्णांक dcn301_smu_set_min_deep_sleep_dcfclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_min_ds_dcfclk_khz)
अणु
	पूर्णांक actual_min_ds_dcfclk_mhz = -1;

	DC_LOG_DEBUG("%s(%d)\n", __func__, requested_min_ds_dcfclk_khz);

	actual_min_ds_dcfclk_mhz = dcn301_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetMinDeepSleepDcfclk,
			requested_min_ds_dcfclk_khz / 1000);

	वापस actual_min_ds_dcfclk_mhz * 1000;
पूर्ण

पूर्णांक dcn301_smu_set_dppclk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, पूर्णांक requested_dpp_khz)
अणु
	पूर्णांक actual_dppclk_set_mhz = -1;

	DC_LOG_DEBUG("%s(%d)\n", __func__, requested_dpp_khz);

	actual_dppclk_set_mhz = dcn301_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDppclkFreq,
			requested_dpp_khz / 1000);

	वापस actual_dppclk_set_mhz * 1000;
पूर्ण

व्योम dcn301_smu_set_display_idle_optimization(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t idle_info)
अणु
	//TODO: Work with smu team to define optimization options.

	DC_LOG_DEBUG("%s(%x)\n", __func__, idle_info);

	dcn301_smu_send_msg_with_param(
		clk_mgr,
		VBIOSSMC_MSG_SetDisplayIdleOptimizations,
		idle_info);
पूर्ण

व्योम dcn301_smu_enable_phy_refclk_pwrdwn(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable)
अणु
	जोड़ display_idle_optimization_u idle_info = अणु 0 पूर्ण;

	अगर (enable) अणु
		idle_info.idle_info.df_request_disabled = 1;
		idle_info.idle_info.phy_ref_clk_off = 1;
	पूर्ण

	DC_LOG_DEBUG("%s(%d)\n", __func__, enable);

	dcn301_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_SetDisplayIdleOptimizations,
			idle_info.data);
पूर्ण

व्योम dcn301_smu_enable_pme_wa(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dcn301_smu_send_msg_with_param(
			clk_mgr,
			VBIOSSMC_MSG_UpdatePmeRestore,
			0);
पूर्ण

व्योम dcn301_smu_set_dram_addr_high(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_high)
अणु
	DC_LOG_DEBUG("%s(%x)\n", __func__, addr_high);

	dcn301_smu_send_msg_with_param(clk_mgr,
			VBIOSSMC_MSG_SetVbiosDramAddrHigh, addr_high);
पूर्ण

व्योम dcn301_smu_set_dram_addr_low(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_low)
अणु
	DC_LOG_DEBUG("%s(%x)\n", __func__, addr_low);

	dcn301_smu_send_msg_with_param(clk_mgr,
			VBIOSSMC_MSG_SetVbiosDramAddrLow, addr_low);
पूर्ण

व्योम dcn301_smu_transfer_dpm_table_smu_2_dram(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dcn301_smu_send_msg_with_param(clk_mgr,
			VBIOSSMC_MSG_TransferTableSmu2Dram, TABLE_DPMCLOCKS);
पूर्ण

व्योम dcn301_smu_transfer_wm_table_dram_2_smu(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	dcn301_smu_send_msg_with_param(clk_mgr,
			VBIOSSMC_MSG_TransferTableDram2Smu, TABLE_WATERMARKS);
पूर्ण
