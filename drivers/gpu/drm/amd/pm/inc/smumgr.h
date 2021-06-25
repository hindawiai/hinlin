<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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
 */
#अगर_अघोषित _SMUMGR_H_
#घोषणा _SMUMGR_H_
#समावेश <linux/types.h>
#समावेश "amd_powerplay.h"
#समावेश "hwmgr.h"

क्रमागत SMU_TABLE अणु
	SMU_UVD_TABLE = 0,
	SMU_VCE_TABLE,
	SMU_BIF_TABLE,
पूर्ण;

क्रमागत SMU_TYPE अणु
	SMU_SoftRegisters = 0,
	SMU_Discrete_DpmTable,
पूर्ण;

क्रमागत SMU_MEMBER अणु
	HandshakeDisables = 0,
	VoltageChangeTimeout,
	AverageGraphicsActivity,
	AverageMemoryActivity,
	PreVBlankGap,
	VBlankTimeout,
	UcodeLoadStatus,
	UvdBootLevel,
	VceBootLevel,
	LowSclkInterruptThreshold,
	DRAM_LOG_ADDR_H,
	DRAM_LOG_ADDR_L,
	DRAM_LOG_PHY_ADDR_H,
	DRAM_LOG_PHY_ADDR_L,
	DRAM_LOG_BUFF_SIZE,
पूर्ण;


क्रमागत SMU_MAC_DEFINITION अणु
	SMU_MAX_LEVELS_GRAPHICS = 0,
	SMU_MAX_LEVELS_MEMORY,
	SMU_MAX_LEVELS_LINK,
	SMU_MAX_ENTRIES_SMIO,
	SMU_MAX_LEVELS_VDDC,
	SMU_MAX_LEVELS_VDDGFX,
	SMU_MAX_LEVELS_VDDCI,
	SMU_MAX_LEVELS_MVDD,
	SMU_UVD_MCLK_HANDSHAKE_DISABLE,
पूर्ण;

क्रमागत SMU9_TABLE_ID अणु
	PPTABLE = 0,
	WMTABLE,
	AVFSTABLE,
	TOOLSTABLE,
	AVFSFUSETABLE
पूर्ण;

क्रमागत SMU10_TABLE_ID अणु
	SMU10_WMTABLE = 0,
	SMU10_CLOCKTABLE,
पूर्ण;

बाह्य पूर्णांक smum_करोwnload_घातerplay_table(काष्ठा pp_hwmgr *hwmgr, व्योम **table);

बाह्य पूर्णांक smum_upload_घातerplay_table(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक smum_send_msg_to_smc(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक16_t msg, uपूर्णांक32_t *resp);

बाह्य पूर्णांक smum_send_msg_to_smc_with_parameter(काष्ठा pp_hwmgr *hwmgr,
					uपूर्णांक16_t msg, uपूर्णांक32_t parameter,
					uपूर्णांक32_t *resp);

बाह्य पूर्णांक smum_update_sclk_threshold(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक smum_update_smc_table(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t type);
बाह्य पूर्णांक smum_process_firmware_header(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smum_thermal_avfs_enable(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smum_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smum_init_smc_table(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smum_populate_all_graphic_levels(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smum_populate_all_memory_levels(काष्ठा pp_hwmgr *hwmgr);
बाह्य पूर्णांक smum_initialize_mc_reg_table(काष्ठा pp_hwmgr *hwmgr);
बाह्य uपूर्णांक32_t smum_get_दुरत्व(काष्ठा pp_hwmgr *hwmgr,
				uपूर्णांक32_t type, uपूर्णांक32_t member);
बाह्य uपूर्णांक32_t smum_get_mac_definition(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t value);

बाह्य bool smum_is_dpm_running(काष्ठा pp_hwmgr *hwmgr);

बाह्य bool smum_is_hw_avfs_present(काष्ठा pp_hwmgr *hwmgr);

बाह्य पूर्णांक smum_update_dpm_settings(काष्ठा pp_hwmgr *hwmgr, व्योम *profile_setting);

बाह्य पूर्णांक smum_smc_table_manager(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक8_t *table, uपूर्णांक16_t table_id, bool rw);

बाह्य पूर्णांक smum_stop_smc(काष्ठा pp_hwmgr *hwmgr);

#पूर्ण_अगर
