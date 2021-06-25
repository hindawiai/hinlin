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

#समावेश <linux/delay.h>
#समावेश "dcn30_clk_mgr_smu_msg.h"

#समावेश "clk_mgr_internal.h"
#समावेश "reg_helper.h"
#समावेश "dalsmc.h"

#घोषणा mmDAL_MSG_REG  0x1628A
#घोषणा mmDAL_ARG_REG  0x16273
#घोषणा mmDAL_RESP_REG 0x16274

#घोषणा REG(reg_name) \
	mm ## reg_name

#समावेश "logger_types.h"
#अघोषित DC_LOGGER
#घोषणा DC_LOGGER \
	CTX->logger
#घोषणा smu_prपूर्णांक(str, ...) अणुDC_LOG_SMU(str, ##__VA_ARGS__); पूर्ण


/*
 * Function to be used instead of REG_WAIT macro because the रुको ends when
 * the रेजिस्टर is NOT EQUAL to zero, and because the translation in msg_अगर.h
 * won't work with REG_WAIT.
 */
अटल uपूर्णांक32_t dcn30_smu_रुको_क्रम_response(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक delay_us, अचिन्हित पूर्णांक max_retries)
अणु
	uपूर्णांक32_t reg = 0;

	करो अणु
		reg = REG_READ(DAL_RESP_REG);
		अगर (reg)
			अवरोध;

		अगर (delay_us >= 1000)
			msleep(delay_us/1000);
		अन्यथा अगर (delay_us > 0)
			udelay(delay_us);
	पूर्ण जबतक (max_retries--);

	/* handle DALSMC_Result_CmdRejectedBusy? */

	/* Log? */

	वापस reg;
पूर्ण

अटल bool dcn30_smu_send_msg_with_param(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t msg_id, uपूर्णांक32_t param_in, uपूर्णांक32_t *param_out)
अणु
	/* Wait क्रम response रेजिस्टर to be पढ़ोy */
	dcn30_smu_रुको_क्रम_response(clk_mgr, 10, 200000);

	/* Clear response रेजिस्टर */
	REG_WRITE(DAL_RESP_REG, 0);

	/* Set the parameter रेजिस्टर क्रम the SMU message */
	REG_WRITE(DAL_ARG_REG, param_in);

	/* Trigger the message transaction by writing the message ID */
	REG_WRITE(DAL_MSG_REG, msg_id);

	/* Wait क्रम response */
	अगर (dcn30_smu_रुको_क्रम_response(clk_mgr, 10, 200000) == DALSMC_Result_OK) अणु
		अगर (param_out)
			*param_out = REG_READ(DAL_ARG_REG);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Test message should वापस input + 1 */
bool dcn30_smu_test_message(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t input)
अणु
	uपूर्णांक32_t response = 0;

	smu_prपूर्णांक("SMU Test message: %d\n", input);

	अगर (dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_TestMessage, input, &response))
		अगर (response == input + 1)
			वापस true;

	वापस false;
पूर्ण

bool dcn30_smu_get_smu_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, अचिन्हित पूर्णांक *version)
अणु
	smu_prपूर्णांक("SMU Get SMU version\n");

	अगर (dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_GetSmuVersion, 0, version)) अणु

		smu_prपूर्णांक("SMU version: %d\n", *version);

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Message output should match SMU11_DRIVER_IF_VERSION in smu11_driver_अगर.h */
bool dcn30_smu_check_driver_अगर_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	uपूर्णांक32_t response = 0;

	smu_prपूर्णांक("SMU Check driver if version\n");

	अगर (dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_GetDriverIfVersion, 0, &response)) अणु

		smu_prपूर्णांक("SMU driver if version: %d\n", response);

		अगर (response == SMU11_DRIVER_IF_VERSION)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Message output should match DALSMC_VERSION in dalsmc.h */
bool dcn30_smu_check_msg_header_version(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	uपूर्णांक32_t response = 0;

	smu_prपूर्णांक("SMU Check msg header version\n");

	अगर (dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_GetMsgHeaderVersion, 0, &response)) अणु

		smu_prपूर्णांक("SMU msg header version: %d\n", response);

		अगर (response == DALSMC_VERSION)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम dcn30_smu_set_dram_addr_high(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_high)
अणु
	smu_prपूर्णांक("SMU Set DRAM addr high: %d\n", addr_high);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_SetDalDramAddrHigh, addr_high, शून्य);
पूर्ण

व्योम dcn30_smu_set_dram_addr_low(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t addr_low)
अणु
	smu_prपूर्णांक("SMU Set DRAM addr low: %d\n", addr_low);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_SetDalDramAddrLow, addr_low, शून्य);
पूर्ण

व्योम dcn30_smu_transfer_wm_table_smu_2_dram(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	smu_prपूर्णांक("SMU Transfer WM table SMU 2 DRAM\n");

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_TransferTableSmu2Dram, TABLE_WATERMARKS, शून्य);
पूर्ण

व्योम dcn30_smu_transfer_wm_table_dram_2_smu(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	smu_prपूर्णांक("SMU Transfer WM table DRAM 2 SMU\n");

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_TransferTableDram2Smu, TABLE_WATERMARKS, शून्य);
पूर्ण

/* Returns the actual frequency that was set in MHz, 0 on failure */
अचिन्हित पूर्णांक dcn30_smu_set_hard_min_by_freq(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk, uपूर्णांक16_t freq_mhz)
अणु
	uपूर्णांक32_t response = 0;

	/* bits 23:16 क्रम घड़ी type, lower 16 bits क्रम frequency in MHz */
	uपूर्णांक32_t param = (clk << 16) | freq_mhz;

	smu_prपूर्णांक("SMU Set hard min by freq: clk = %d, freq_mhz = %d MHz\n", clk, freq_mhz);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_SetHardMinByFreq, param, &response);

	smu_prपूर्णांक("SMU Frequency set = %d MHz\n", response);

	वापस response;
पूर्ण

/* Returns the actual frequency that was set in MHz, 0 on failure */
अचिन्हित पूर्णांक dcn30_smu_set_hard_max_by_freq(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk, uपूर्णांक16_t freq_mhz)
अणु
	uपूर्णांक32_t response = 0;

	/* bits 23:16 क्रम घड़ी type, lower 16 bits क्रम frequency in MHz */
	uपूर्णांक32_t param = (clk << 16) | freq_mhz;

	smu_prपूर्णांक("SMU Set hard max by freq: clk = %d, freq_mhz = %d MHz\n", clk, freq_mhz);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_SetHardMaxByFreq, param, &response);

	smu_prपूर्णांक("SMU Frequency set = %d MHz\n", response);

	वापस response;
पूर्ण

/*
 * Frequency in MHz वापसed in lower 16 bits क्रम valid DPM level
 *
 * Call with dpm_level = 0xFF to query features, वापस value will be:
 *     Bits 7:0 - number of DPM levels
 *     Bit   28 - 1 = स्वतः DPM on
 *     Bit   29 - 1 = sweep DPM on
 *     Bit   30 - 1 = क्रमced DPM on
 *     Bit   31 - 0 = discrete, 1 = fine-grained
 *
 * With fine-grained DPM, only min and max frequencies will be reported
 *
 * Returns 0 on failure
 */
अचिन्हित पूर्णांक dcn30_smu_get_dpm_freq_by_index(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk, uपूर्णांक8_t dpm_level)
अणु
	uपूर्णांक32_t response = 0;

	/* bits 23:16 क्रम घड़ी type, lower 8 bits क्रम DPM level */
	uपूर्णांक32_t param = (clk << 16) | dpm_level;

	smu_prपूर्णांक("SMU Get dpm freq by index: clk = %d, dpm_level = %d\n", clk, dpm_level);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_GetDpmFreqByIndex, param, &response);

	smu_prपूर्णांक("SMU dpm freq: %d MHz\n", response);

	वापस response;
पूर्ण

/* Returns the max DPM frequency in DC mode in MHz, 0 on failure */
अचिन्हित पूर्णांक dcn30_smu_get_dc_mode_max_dpm_freq(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, PPCLK_e clk)
अणु
	uपूर्णांक32_t response = 0;

	/* bits 23:16 क्रम घड़ी type */
	uपूर्णांक32_t param = clk << 16;

	smu_prपूर्णांक("SMU Get DC mode max DPM freq: clk = %d\n", clk);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_GetDcModeMaxDpmFreq, param, &response);

	smu_prपूर्णांक("SMU DC mode max DMP freq: %d MHz\n", response);

	वापस response;
पूर्ण

व्योम dcn30_smu_set_min_deep_sleep_dcef_clk(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t freq_mhz)
अणु
	smu_prपूर्णांक("SMU Set min deep sleep dcef clk: freq_mhz = %d MHz\n", freq_mhz);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_SetMinDeepSleepDcefclk, freq_mhz, शून्य);
पूर्ण

व्योम dcn30_smu_set_num_of_displays(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, uपूर्णांक32_t num_displays)
अणु
	smu_prपूर्णांक("SMU Set num of displays: num_displays = %d\n", num_displays);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_NumOfDisplays, num_displays, शून्य);
पूर्ण

व्योम dcn30_smu_set_display_refresh_from_mall(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable, uपूर्णांक8_t cache_समयr_delay, uपूर्णांक8_t cache_समयr_scale)
अणु
	/* bits 8:7 क्रम cache समयr scale, bits 6:1 क्रम cache समयr delay, bit 0 = 1 क्रम enable, = 0 क्रम disable */
	uपूर्णांक32_t param = (cache_समयr_scale << 7) | (cache_समयr_delay << 1) | (enable ? 1 : 0);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_SetDisplayRefreshFromMall, param, शून्य);
पूर्ण

व्योम dcn30_smu_set_बाह्यal_client_df_cstate_allow(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr, bool enable)
अणु
	smu_prपूर्णांक("SMU Set external client df cstate allow: enable = %d\n", enable);

	dcn30_smu_send_msg_with_param(clk_mgr,
			DALSMC_MSG_SetExternalClientDfCstateAllow, enable ? 1 : 0, शून्य);
पूर्ण

व्योम dcn30_smu_set_pme_workaround(काष्ठा clk_mgr_पूर्णांकernal *clk_mgr)
अणु
	smu_prपूर्णांक("SMU Set PME workaround\n");

	dcn30_smu_send_msg_with_param(clk_mgr,
	DALSMC_MSG_BacoAudioD3PME, 0, शून्य);
पूर्ण
